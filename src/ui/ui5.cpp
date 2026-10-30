// The camp menu's screens, fifth UI pass (slice ui5; game/include/p3fes/game/ui5.h has the role of every function and
// the records they work on): the camp root's loaders, the main list's tweens, the flash-control task and its 28
// transition players, the side-portrait tasks, the status / equipment / persona / social-link / item / system / skill
// / party-status / trade screens' leaves, task creators and destroys. docs/ANALYSIS/20_menu_ui.md section 2.
//
// The bodies are p3fes_handgen's (game/include/p3fes/game/hg_cpu.h): one statement per instruction on the guest
// registers, the original's frame, spills, $ra links, cycle charges and check points, so every register the original
// leaves at a check point, call or return is left the same way (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen").
// This readability pass states each function's role above it, names the record offsets and globals (ui5.h: ui5::task
// / rw / g / fl / tw / sf / ptc / pdc / kani -- each constant equals the literal it replaces) and notes what the
// callees do; it changes no statement. `// 0x00xxxxxx` lines name the original basic block a C++ block comes from.
// The remaining `goto`s jump to blocks the original shares between paths (written once, as there).
//
// Kept as the original has them: the debug printfs ("*** RELEASE KEY", "camp comu free" ...), nullsub_3, the
// duplicated bodies (sub_11D3A0 / sub_11DA80, the four "four frames of slots 1 and 2" players).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/ui5.h"

namespace p3fes::recomp_gen {
void fn_H_Camp_CreateDrawTask_0011a770(p3fes::EEContext&);
void fn_H_Camp_CreateRootDrawTask_0011bad0(p3fes::EEContext&);
void fn_H_Cdvd_ArchiveGetFile_00102100(p3fes::EEContext&);
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_datGetEquipmentIdx_0016cb80(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datPersonaGetByPcId_00174800(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_kwlnTaskGetState_00195290(p3fes::EEContext&);
void fn_kwlnTaskMoveAfter_001957b0(p3fes::EEContext&);
void fn_kwlnTaskMoveBefore_001958a0(p3fes::EEContext&);
void fn_nullsub_3_0011bba0(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_qsort_005225f8(p3fes::EEContext&);
void fn_scrGetIntPara_0035ed20(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sprCreateHandleFromData_00112420(p3fes::EEContext&);
void fn_sprCreateHandle_001158b0(p3fes::EEContext&);
void fn_sprDrawSpriteBasic_001159f0(p3fes::EEContext&);
void fn_sprFileIsReady_00111f30(p3fes::EEContext&);
void fn_sprFontGetFile_001120a0(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_10C1A0_0010c1a0(p3fes::EEContext&);
void fn_sub_10C3A0_0010c3a0(p3fes::EEContext&);
void fn_sub_111CB0_00111cb0(p3fes::EEContext&);
void fn_sub_111D50_00111d50(p3fes::EEContext&);
void fn_sub_111DD0_00111dd0(p3fes::EEContext&);
void fn_sub_111EC0_00111ec0(p3fes::EEContext&);
void fn_sub_111EE0_00111ee0(p3fes::EEContext&);
void fn_sub_111F20_00111f20(p3fes::EEContext&);
void fn_sub_1124B0_001124b0(p3fes::EEContext&);
void fn_sub_1127D0_001127d0(p3fes::EEContext&);
void fn_sub_113A30_00113a30(p3fes::EEContext&);
void fn_sub_1140D0_001140d0(p3fes::EEContext&);
void fn_sub_114450_00114450(p3fes::EEContext&);
void fn_sub_114E70_00114e70(p3fes::EEContext&);
void fn_sub_115980_00115980(p3fes::EEContext&);
void fn_sub_115AD0_00115ad0(p3fes::EEContext&);
void fn_sub_115BC0_00115bc0(p3fes::EEContext&);
void fn_sub_119AA0_00119aa0(p3fes::EEContext&);
void fn_sub_119E00_00119e00(p3fes::EEContext&);
void fn_sub_119F10_00119f10(p3fes::EEContext&);
void fn_sub_11A710_0011a710(p3fes::EEContext&);
void fn_sub_11A8A0_0011a8a0(p3fes::EEContext&);
void fn_sub_11AAE0_0011aae0(p3fes::EEContext&);
void fn_sub_11B0B0_0011b0b0(p3fes::EEContext&);
void fn_sub_11B210_0011b210(p3fes::EEContext&);
void fn_sub_11B2B0_0011b2b0(p3fes::EEContext&);
void fn_sub_11B370_0011b370(p3fes::EEContext&);
void fn_sub_11BAA0_0011baa0(p3fes::EEContext&);
void fn_sub_11C550_0011c550(p3fes::EEContext&);
void fn_sub_11CC80_0011cc80(p3fes::EEContext&);
void fn_sub_11D3A0_0011d3a0(p3fes::EEContext&);
void fn_sub_11DA80_0011da80(p3fes::EEContext&);
void fn_sub_11E380_0011e380(p3fes::EEContext&);
void fn_sub_11EA20_0011ea20(p3fes::EEContext&);
void fn_sub_11F120_0011f120(p3fes::EEContext&);
void fn_sub_11F1B0_0011f1b0(p3fes::EEContext&);
void fn_sub_11F260_0011f260(p3fes::EEContext&);
void fn_sub_11F400_0011f400(p3fes::EEContext&);
void fn_sub_11F5C0_0011f5c0(p3fes::EEContext&);
void fn_sub_11F760_0011f760(p3fes::EEContext&);
void fn_sub_11F900_0011f900(p3fes::EEContext&);
void fn_sub_11FAF0_0011faf0(p3fes::EEContext&);
void fn_sub_11FCA0_0011fca0(p3fes::EEContext&);
void fn_sub_11FE50_0011fe50(p3fes::EEContext&);
void fn_sub_11FFD0_0011ffd0(p3fes::EEContext&);
void fn_sub_120150_00120150(p3fes::EEContext&);
void fn_sub_1202B0_001202b0(p3fes::EEContext&);
void fn_sub_120410_00120410(p3fes::EEContext&);
void fn_sub_120570_00120570(p3fes::EEContext&);
void fn_sub_1206D0_001206d0(p3fes::EEContext&);
void fn_sub_120830_00120830(p3fes::EEContext&);
void fn_sub_120990_00120990(p3fes::EEContext&);
void fn_sub_120B10_00120b10(p3fes::EEContext&);
void fn_sub_120CA0_00120ca0(p3fes::EEContext&);
void fn_sub_120E20_00120e20(p3fes::EEContext&);
void fn_sub_120FD0_00120fd0(p3fes::EEContext&);
void fn_sub_121180_00121180(p3fes::EEContext&);
void fn_sub_121300_00121300(p3fes::EEContext&);
void fn_sub_121480_00121480(p3fes::EEContext&);
void fn_sub_121600_00121600(p3fes::EEContext&);
void fn_sub_121780_00121780(p3fes::EEContext&);
void fn_sub_121930_00121930(p3fes::EEContext&);
void fn_sub_121AB0_00121ab0(p3fes::EEContext&);
void fn_sub_121C30_00121c30(p3fes::EEContext&);
void fn_sub_121FF0_00121ff0(p3fes::EEContext&);
void fn_sub_122630_00122630(p3fes::EEContext&);
void fn_sub_122660_00122660(p3fes::EEContext&);
void fn_sub_122940_00122940(p3fes::EEContext&);
void fn_sub_122FD0_00122fd0(p3fes::EEContext&);
void fn_sub_123000_00123000(p3fes::EEContext&);
void fn_sub_1230C0_001230c0(p3fes::EEContext&);
void fn_sub_123540_00123540(p3fes::EEContext&);
void fn_sub_123570_00123570(p3fes::EEContext&);
void fn_sub_123640_00123640(p3fes::EEContext&);
void fn_sub_123B70_00123b70(p3fes::EEContext&);
void fn_sub_123F80_00123f80(p3fes::EEContext&);
void fn_sub_124090_00124090(p3fes::EEContext&);
void fn_sub_124E00_00124e00(p3fes::EEContext&);
void fn_sub_124E60_00124e60(p3fes::EEContext&);
void fn_sub_124FD0_00124fd0(p3fes::EEContext&);
void fn_sub_125740_00125740(p3fes::EEContext&);
void fn_sub_125B40_00125b40(p3fes::EEContext&);
void fn_sub_1266E0_001266e0(p3fes::EEContext&);
void fn_sub_127A40_00127a40(p3fes::EEContext&);
void fn_sub_127AB0_00127ab0(p3fes::EEContext&);
void fn_sub_127AD0_00127ad0(p3fes::EEContext&);
void fn_sub_127AF0_00127af0(p3fes::EEContext&);
void fn_sub_127B00_00127b00(p3fes::EEContext&);
void fn_sub_127FC0_00127fc0(p3fes::EEContext&);
void fn_sub_127FF0_00127ff0(p3fes::EEContext&);
void fn_sub_128010_00128010(p3fes::EEContext&);
void fn_sub_128030_00128030(p3fes::EEContext&);
void fn_sub_128040_00128040(p3fes::EEContext&);
void fn_sub_1281E0_001281e0(p3fes::EEContext&);
void fn_sub_128480_00128480(p3fes::EEContext&);
void fn_sub_129160_00129160(p3fes::EEContext&);
void fn_sub_12BCE0_0012bce0(p3fes::EEContext&);
void fn_sub_12DDC0_0012ddc0(p3fes::EEContext&);
void fn_sub_12DF50_0012df50(p3fes::EEContext&);
void fn_sub_12E170_0012e170(p3fes::EEContext&);
void fn_sub_130E40_00130e40(p3fes::EEContext&);
void fn_sub_130F20_00130f20(p3fes::EEContext&);
void fn_sub_131000_00131000(p3fes::EEContext&);
void fn_sub_131090_00131090(p3fes::EEContext&);
void fn_sub_1332F0_001332f0(p3fes::EEContext&);
void fn_sub_1335D0_001335d0(p3fes::EEContext&);
void fn_sub_1336B0_001336b0(p3fes::EEContext&);
void fn_sub_133780_00133780(p3fes::EEContext&);
void fn_sub_133900_00133900(p3fes::EEContext&);
void fn_sub_1339A0_001339a0(p3fes::EEContext&);
void fn_sub_133A80_00133a80(p3fes::EEContext&);
void fn_sub_133B80_00133b80(p3fes::EEContext&);
void fn_sub_133C40_00133c40(p3fes::EEContext&);
void fn_sub_133D00_00133d00(p3fes::EEContext&);
void fn_sub_133D30_00133d30(p3fes::EEContext&);
void fn_sub_134A10_00134a10(p3fes::EEContext&);
void fn_sub_134D80_00134d80(p3fes::EEContext&);
void fn_sub_135120_00135120(p3fes::EEContext&);
void fn_sub_135460_00135460(p3fes::EEContext&);
void fn_sub_1365B0_001365b0(p3fes::EEContext&);
void fn_sub_136750_00136750(p3fes::EEContext&);
void fn_sub_1368A0_001368a0(p3fes::EEContext&);
void fn_sub_137300_00137300(p3fes::EEContext&);
void fn_sub_138EE0_00138ee0(p3fes::EEContext&);
void fn_sub_1392D0_001392d0(p3fes::EEContext&);
void fn_sub_13BCE0_0013bce0(p3fes::EEContext&);
void fn_sub_13BE50_0013be50(p3fes::EEContext&);
void fn_sub_13C240_0013c240(p3fes::EEContext&);
void fn_sub_13C6A0_0013c6a0(p3fes::EEContext&);
void fn_sub_13CC90_0013cc90(p3fes::EEContext&);
void fn_sub_13CF80_0013cf80(p3fes::EEContext&);
void fn_sub_141590_00141590(p3fes::EEContext&);
void fn_sub_145350_00145350(p3fes::EEContext&);
void fn_sub_14ED20_0014ed20(p3fes::EEContext&);
void fn_sub_14EE80_0014ee80(p3fes::EEContext&);
void fn_sub_14EF60_0014ef60(p3fes::EEContext&);
void fn_sub_14F320_0014f320(p3fes::EEContext&);
void fn_sub_14F680_0014f680(p3fes::EEContext&);
void fn_sub_154770_00154770(p3fes::EEContext&);
void fn_sub_1548A0_001548a0(p3fes::EEContext&);
void fn_sub_15C460_0015c460(p3fes::EEContext&);
void fn_sub_15C520_0015c520(p3fes::EEContext&);
void fn_sub_15D8E0_0015d8e0(p3fes::EEContext&);
void fn_sub_1616D0_001616d0(p3fes::EEContext&);
void fn_sub_1617D0_001617d0(p3fes::EEContext&);
void fn_sub_161D60_00161d60(p3fes::EEContext&);
void fn_sub_1669B0_001669b0(p3fes::EEContext&);
void fn_sub_166A50_00166a50(p3fes::EEContext&);
void fn_sub_1675B0_001675b0(p3fes::EEContext&);
void fn_sub_1675E0_001675e0(p3fes::EEContext&);
void fn_sub_1678E0_001678e0(p3fes::EEContext&);
void fn_sub_167EC0_00167ec0(p3fes::EEContext&);
void fn_sub_167F40_00167f40(p3fes::EEContext&);
void fn_sub_168040_00168040(p3fes::EEContext&);
void fn_sub_168100_00168100(p3fes::EEContext&);
void fn_sub_168220_00168220(p3fes::EEContext&);
void fn_sub_1685B0_001685b0(p3fes::EEContext&);
void fn_sub_1685E0_001685e0(p3fes::EEContext&);
void fn_sub_168720_00168720(p3fes::EEContext&);
void fn_sub_168770_00168770(p3fes::EEContext&);
void fn_sub_169040_00169040(p3fes::EEContext&);
void fn_sub_169330_00169330(p3fes::EEContext&);
void fn_sub_169AE0_00169ae0(p3fes::EEContext&);
void fn_sub_16A6A0_0016a6a0(p3fes::EEContext&);
void fn_sub_16C4F0_0016c4f0(p3fes::EEContext&);
void fn_sub_16C570_0016c570(p3fes::EEContext&);
void fn_sub_16C670_0016c670(p3fes::EEContext&);
void fn_sub_16C920_0016c920(p3fes::EEContext&);
void fn_sub_16C970_0016c970(p3fes::EEContext&);
void fn_sub_16CF40_0016cf40(p3fes::EEContext&);
void fn_sub_16CF90_0016cf90(p3fes::EEContext&);
void fn_sub_16DBA0_0016dba0(p3fes::EEContext&);
void fn_sub_16DD60_0016dd60(p3fes::EEContext&);
void fn_sub_16DF30_0016df30(p3fes::EEContext&);
void fn_sub_16F630_0016f630(p3fes::EEContext&);
void fn_sub_16F720_0016f720(p3fes::EEContext&);
void fn_sub_16F810_0016f810(p3fes::EEContext&);
void fn_sub_16F900_0016f900(p3fes::EEContext&);
void fn_sub_16F9F0_0016f9f0(p3fes::EEContext&);
void fn_sub_16FAE0_0016fae0(p3fes::EEContext&);
void fn_sub_16FBD0_0016fbd0(p3fes::EEContext&);
void fn_sub_16FCC0_0016fcc0(p3fes::EEContext&);
void fn_sub_16FEA0_0016fea0(p3fes::EEContext&);
void fn_sub_170860_00170860(p3fes::EEContext&);
void fn_sub_170E90_00170e90(p3fes::EEContext&);
void fn_sub_170ED0_00170ed0(p3fes::EEContext&);
void fn_sub_171250_00171250(p3fes::EEContext&);
void fn_sub_1712D0_001712d0(p3fes::EEContext&);
void fn_sub_1717C0_001717c0(p3fes::EEContext&);
void fn_sub_172160_00172160(p3fes::EEContext&);
void fn_sub_173280_00173280(p3fes::EEContext&);
void fn_sub_173330_00173330(p3fes::EEContext&);
void fn_sub_173340_00173340(p3fes::EEContext&);
void fn_sub_1733B0_001733b0(p3fes::EEContext&);
void fn_sub_175200_00175200(p3fes::EEContext&);
void fn_sub_17AE30_0017ae30(p3fes::EEContext&);
void fn_sub_17B660_0017b660(p3fes::EEContext&);
void fn_sub_17B860_0017b860(p3fes::EEContext&);
void fn_sub_17BC20_0017bc20(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_18B6D0_0018b6d0(p3fes::EEContext&);
void fn_sub_18B700_0018b700(p3fes::EEContext&);
void fn_sub_18BC10_0018bc10(p3fes::EEContext&);
void fn_sub_1C7CE0_001c7ce0(p3fes::EEContext&);
void fn_sub_3C72D0_003c72d0(p3fes::EEContext&);
void fn_sub_3C77A0_003c77a0(p3fes::EEContext&);
void fn_sub_3C7B90_003c7b90(p3fes::EEContext&);
void fn_sub_3C7DD0_003c7dd0(p3fes::EEContext&);
void fn_sub_40EB50_0040eb50(p3fes::EEContext&);
void fn_sub_4D0F00_004d0f00(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace ui5;  // task / rw / g / fl / tw / sf / ptc / pdc / kani: the named offsets of ui5.h

// 0x00119AA0 sub_119AA0 -- 856 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_UpdateCampSprSetupFileTask] Update of "H_CampSprSetupFile" (20_menu_ui.md 2.2 state 0). State 0: once
// camp_all.pak (work +60) is loaded, makes sprite files of its entries 0..13 (H_Cdvd_ArchiveGetFile +
// sprCreateHandleFromData) into +4..+56, allocates the 200 tween records of the camp screens (sub_18B6D0(200) -> +68
// and gp-19876 0x7CDF4C) and goes to 1; 1: once every file is ready (sprFileIsReady) copies the 14 handles to the camp
// sprite-file table 0x833B70 and goes to 3 (loaded: the camp root waits for it); 2: waits for the pak alone. Every
// frame ends with sub_3C7B90; returns 0.
void sub_119AA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00119aa0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(v1, s0, 0);
    v0 = 3;
    if (v1 != v0) {
        // 0x00119ac8
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x00119db4
            charge(ctx, 5);
            lw(a0, s0, 60);
            jal(ctx, 0x119DB8u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                // 0x00119dc8
                charge(ctx, 2);
                v0 = 3;
                sw(v0, s0, 0);
            }
        } else {
            // 0x00119ad4
            charge(ctx, 3);
            s1 = 1;
            if (v1 == s1) {
                // 0x00119d20
                charge(ctx, 3);
                s2 = 0;
                for (;;) {
                    // 0x00119d58
                    charge(ctx, 3);
                    v0 = slti(s2, 14);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00119d2c
                    charge(ctx, 5);
                    v0 = sll(s2, 2);
                    v0 = addu(s0, v0);
                    lw(a0, v0, 4);
                    if (a0 != 0) {
                        // 0x00119d40
                        charge(ctx, 4);
                        jal(ctx, 0x119D40u, gen::fn_sprFileIsReady_00111f30);
                        if (v0 == 0) {
                            // 0x00119d50
                            charge(ctx, 1);
                            s1 = 0;
                        }
                    }
                    // 0x00119d54
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x00119d64
                charge(ctx, 2);
                if (s1 != 0) {
                    // 0x00119d6c
                    charge(ctx, 5);
                    a2 = 0;
                    v1 = 0x830000;
                    v1 = addiu(v1, 15216);  // &0x833B70
                    for (;;) {
                        // 0x00119d98
                        charge(ctx, 3);
                        v0 = slti(a2, 14);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x00119d80
                        charge(ctx, 6);
                        a1 = sll(a2, 2);
                        v0 = addu(s0, a1);
                        lw(a0, v0, 4);
                        v0 = addu(v1, a1);
                        sw(a0, v0, 0);
                        a2 = addiu(a2, 1);
                    }
                    // 0x00119da4
                    charge(ctx, 4);
                    v0 = 3;
                    sw(v0, s0, 0);
                }
            } else {
                // 0x00119ae0
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x00119af0
                    charge(ctx, 5);
                    lw(a0, s0, 60);
                    jal(ctx, 0x119AF4u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                    if (v0 != 0) {
                        // 0x00119b04
                        charge(ctx, 135);
                        lw(a0, s0, 60);
                        a1 = 0;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x119B10u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        a0 = v0;
                        jal(ctx, 0x119B1Cu, gen::fn_sprCreateHandleFromData_00112420);
                        sw(v0, s0, 4);
                        lw(a0, s0, 60);
                        a1 = s1;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x119B34u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        a0 = v0;
                        jal(ctx, 0x119B40u, gen::fn_sprCreateHandleFromData_00112420);
                        sw(v0, s0, 8);
                        lw(a0, s0, 60);
                        a1 = 2;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x119B58u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        a0 = v0;
                        jal(ctx, 0x119B64u, gen::fn_sprCreateHandleFromData_00112420);
                        sw(v0, s0, 12);
                        lw(a0, s0, 60);
                        a1 = 3;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x119B7Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        a0 = v0;
                        jal(ctx, 0x119B88u, gen::fn_sprCreateHandleFromData_00112420);
                        sw(v0, s0, 16);
                        lw(a0, s0, 60);
                        a1 = 4;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x119BA0u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        a0 = v0;
                        jal(ctx, 0x119BACu, gen::fn_sprCreateHandleFromData_00112420);
                        sw(v0, s0, 20);
                        lw(a0, s0, 60);
                        a1 = 5;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x119BC4u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        a0 = v0;
                        jal(ctx, 0x119BD0u, gen::fn_sprCreateHandleFromData_00112420);
                        sw(v0, s0, 24);
                        lw(a0, s0, 60);
                        a1 = 6;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x119BE8u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        a0 = v0;
                        jal(ctx, 0x119BF4u, gen::fn_sprCreateHandleFromData_00112420);
                        sw(v0, s0, 28);
                        lw(a0, s0, 60);
                        a1 = 7;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x119C0Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        a0 = v0;
                        jal(ctx, 0x119C18u, gen::fn_sprCreateHandleFromData_00112420);
                        sw(v0, s0, 32);
                        lw(a0, s0, 60);
                        a1 = 8;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x119C30u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        a0 = v0;
                        jal(ctx, 0x119C3Cu, gen::fn_sprCreateHandleFromData_00112420);
                        sw(v0, s0, 36);
                        lw(a0, s0, 60);
                        a1 = 9;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x119C54u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        a0 = v0;
                        jal(ctx, 0x119C60u, gen::fn_sprCreateHandleFromData_00112420);
                        sw(v0, s0, 40);
                        lw(a0, s0, 60);
                        a1 = 10;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x119C78u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        a0 = v0;
                        jal(ctx, 0x119C84u, gen::fn_sprCreateHandleFromData_00112420);
                        sw(v0, s0, 44);
                        lw(a0, s0, 60);
                        a1 = 11;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x119C9Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        a0 = v0;
                        jal(ctx, 0x119CA8u, gen::fn_sprCreateHandleFromData_00112420);
                        sw(v0, s0, 48);
                        lw(a0, s0, 60);
                        a1 = 12;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x119CC0u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        a0 = v0;
                        jal(ctx, 0x119CCCu, gen::fn_sprCreateHandleFromData_00112420);
                        sw(v0, s0, 52);
                        lw(a0, s0, 60);
                        a1 = 13;
                        a2 = addiu(sp, 0x4C);
                        jal(ctx, 0x119CE4u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                        a0 = v0;
                        jal(ctx, 0x119CF0u, gen::fn_sprCreateHandleFromData_00112420);
                        sw(v0, s0, 56);
                        a0 = 200;
                        jal(ctx, 0x119D00u, gen::fn_sub_18B6D0_0018b6d0);
                        sw(v0, s0, 68);
                        sw(v0, gp, g::kCampTweens);  // 0x7CDF4C
                        v0 = s1;
                        sw(v0, s0, 0);
                    }
                } else {
                    // 0x00119ae8
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x00119dd0
    charge(ctx, 10);
    jal(ctx, 0x119DD0u, gen::fn_sub_3C7B90_003c7b90);
    v0 = 0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00119E00 sub_119E00 -- 260 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_DestroyCampSprSetupFileTask] Destroy of "H_CampSprSetupFile": releases the 14 sprite files (sub_1124B0), the
// pak (H_Cdvd_Destroy), the tween records (RwFree, and clears gp-19876), clears 0x833B70[0..13], frees the work,
// closes the message of +64 (sub_3C77A0, fclDestroyMessage) and forgets the task (gp-19880 = 0).
void sub_119E00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00119e00
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, task::kWork);
    s0 = 0;
    for (;;) {
        // 0x00119e4c
        charge(ctx, 3);
        v0 = slti(s0, 14);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00119e24
        charge(ctx, 6);
        v0 = sll(s0, 2);
        v0 = addu(s1, v0);
        s2 = addiu(v0, 4);
        lw(a0, v0, 4);
        if (a0 != 0) {
            // 0x00119e3c
            charge(ctx, 2);
            jal(ctx, 0x119E3Cu, gen::fn_sub_1124B0_001124b0);  // release a sprite file
        }
        // 0x00119e44
        charge(ctx, 2);
        sw(zero, s2, 0);
        s0 = addiu(s0, 1);
    }
    // 0x00119e58
    charge(ctx, 3);
    lw(a0, s1, 60);
    if (a0 != 0) {
        // 0x00119e64
        charge(ctx, 2);
        jal(ctx, 0x119E64u, gen::fn_H_Cdvd_Destroy_00100ec0);
    }
    // 0x00119e6c
    charge(ctx, 3);
    lw(a0, s1, 68);
    if (a0 != 0) {
        // 0x00119e78
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x119E80u, v0.u());
        sw(zero, gp, g::kCampTweens);  // 0x7CDF4C
    }
    // 0x00119e8c
    charge(ctx, 5);
    a0 = 0;
    v1 = 0x830000;
    v1 = addiu(v1, 15216);  // &0x833B70
    for (;;) {
        // 0x00119eb0
        charge(ctx, 3);
        v0 = slti(a0, 14);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00119ea0
        charge(ctx, 4);
        v0 = sll(a0, 2);
        v0 = addu(v1, v0);
        sw(zero, v0, 0);
        a0 = addiu(a0, 1);
    }
    // 0x00119ebc
    charge(ctx, 8);
    a0 = s1;
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x119EC8u, v0.u());
    lw(v1, s1, 64);
    if (v1 != 0) {
        // 0x00119edc
        charge(ctx, 2);
        jal(ctx, 0x119EDCu, gen::fn_sub_3C77A0_003c77a0);  // fclDestroyMessage
    }
    // 0x00119ee4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    sw(zero, gp, g::kCampSetupTask);  // 0x7CDF48
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00119F10 sub_119F10 -- 308 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_CreateCampSprSetupFileTask] (parent, message): creates "H_CampSprSetupFile" (72-byte work, priority 6335)
// unless one exists (gp-19880), requests camp/camp_all2.pak in The Answer (sub_17D800() != 0) else camp/camp_all.pak
// into +60, keeps the message flag in +64 and opens message 0x5D7AE0 (sub_3C72D0) when it is set. Returns the task, 0
// when it exists or allocation fails.
void sub_119F10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00119f10
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v0, gp, g::kCampSetupTask);  // 0x7CDF48
    if (v0 == 0) {
        // 0x00119f44
        charge(ctx, 10);
        a0 = 1;
        a1 = 72;
        a2 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
        jalr(ctx, 0x119F58u, v0.u());
        s2 = v0;
        if (s2 != 0) {
            // 0x00119f78
            charge(ctx, 14);
            a0 = s1;
            a1 = 0x5E0000;
            a1 = addiu(a1, -21504);  // "H_CampSprSetupFile"
            a2 = 6335;
            a3 = 0x120000;
            a3 = addiu(a3, -25952);  // &sub_119AA0
            t0 = 0x120000;
            t0 = addiu(t0, -25088);  // &sub_119E00
            t1 = s2;
            jal(ctx, 0x119F9Cu, gen::fn_kwlnTaskCreate_00194b20);
            s1 = v0;
            if (s1 != 0) {
                // 0x00119fbc
                charge(ctx, 5);
                sw(s1, gp, g::kCampSetupTask);  // 0x7CDF48
                jal(ctx, 0x119FC0u, gen::fn_sub_17D800_0017d800);  // datGetScenarioMode (1 = The Answer)
                if (v0 == 0) {
                    // 0x00119ff0
                    charge(ctx, 6);
                    a0 = 0x5E0000;
                    a0 = addiu(a0, -21440);  // "camp/camp_all.pak"
                    a1 = 1;
                    jal(ctx, 0x119FFCu, gen::fn_H_Cdvd_Request_00100d80);
                    sw(v0, s2, 60);
                } else {
                    // 0x00119fd0
                    charge(ctx, 8);
                    a0 = 0x5E0000;
                    a0 = addiu(a0, -21472);  // "camp/camp_all2.pak"
                    a1 = 1;
                    jal(ctx, 0x119FDCu, gen::fn_H_Cdvd_Request_00100d80);
                    sw(v0, s2, 60);
                }
                // 0x0011a008
                charge(ctx, 3);
                sw(s0, s2, 64);
                if (s0 != 0) {
                    // 0x0011a014
                    charge(ctx, 4);
                    a0 = 0x5D0000;
                    a0 = addiu(a0, 31456);  // &0x5D7AE0
                    jal(ctx, 0x11A01Cu, gen::fn_sub_3C72D0_003c72d0);  // msgWinOpen
                }
                // 0x0011a024
                charge(ctx, 1);
                v0 = s1;
            } else {
                // 0x00119fb0
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x00119f6c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00119f38
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0011a028 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0011A710 sub_11A710 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [H_Camp_DestroyDrawTask] Destroy of "H_CampDraw": forgets the side-portrait, flash and root-list tasks (gp-19868,
// -19864, -19872, -19860), clears flag 0x1407 (camp open, read by the date HUD) and frees the work.
void sub_11A710(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0011a710
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    sw(zero, gp, g::kCampPcKani);  // 0x7CDF54
    sw(zero, gp, g::kCampPersonaKani);  // 0x7CDF58
    sw(zero, gp, g::kCampFlashTask);  // 0x7CDF50
    sw(zero, gp, g::kCampRootTask);  // 0x7CDF5C
    a0 = 5127;
    a1 = 0;
    jal(ctx, 0x11A738u, gen::fn_datSetFlag_0016f1f0);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x11A74Cu, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0011A770 H_Camp_CreateDrawTask -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// (parent): creates the camp menu root "H_CampDraw" (72-byte work, priority 6335, update H_Camp_UpdateDrawTask,
// destroy sub_11A710). Returns the task or 0.
void H_Camp_CreateDrawTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0011a770
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 1;
    a1 = 72;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x11A794u, v0.u());
    if (v0 != 0) {
        // 0x0011a7b0
        charge(ctx, 13);
        a0 = s0;
        a1 = 0x5E0000;
        a1 = addiu(a1, -21416);  // "H_CampDraw"
        a2 = 6335;
        a3 = 0x120000;
        a3 = addiu(a3, -24496);  // &H_Camp_UpdateDrawTask
        t0 = 0x120000;
        t0 = addiu(t0, -22768);  // &sub_11A710
        t1 = v0;
        jal(ctx, 0x11A7D4u, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 == 0) {
            // 0x0011a7e4
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0011a7a4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0011a7f0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0011A8A0 sub_11A8A0 -- 564 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_UpdateStatusSprSetupFileTask] Update of "H_CampStatusSprSetupFile" (created by sub_1675E0): as sub_119AA0
// for camp/camp_status.pak: its 8 entries become sprite files 1, 2, 7, 9..13 of the table; no tween records, no
// message.
void sub_11A8A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0011a8a0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(v1, s0, 0);
    v0 = 3;
    if (v1 != v0) {
        // 0x0011a8c8
        charge(ctx, 3);
        s1 = 1;
        if (v1 == s1) {
            // 0x0011aa28
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x0011aa60
                charge(ctx, 3);
                v0 = slti(s2, 14);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0011aa34
                charge(ctx, 5);
                v0 = sll(s2, 2);
                v0 = addu(s0, v0);
                lw(a0, v0, 4);
                if (a0 != 0) {
                    // 0x0011aa48
                    charge(ctx, 4);
                    jal(ctx, 0x11AA48u, gen::fn_sprFileIsReady_00111f30);
                    if (v0 == 0) {
                        // 0x0011aa58
                        charge(ctx, 1);
                        s1 = 0;
                    }
                }
                // 0x0011aa5c
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x0011aa6c
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x0011aa74
                charge(ctx, 5);
                a2 = 0;
                v1 = 0x830000;
                v1 = addiu(v1, 15216);  // &0x833B70
                for (;;) {
                    // 0x0011aaa0
                    charge(ctx, 3);
                    v0 = slti(a2, 14);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0011aa88
                    charge(ctx, 6);
                    a1 = sll(a2, 2);
                    v0 = addu(s0, a1);
                    lw(a0, v0, 4);
                    v0 = addu(v1, a1);
                    sw(a0, v0, 0);
                    a2 = addiu(a2, 1);
                }
                // 0x0011aaac
                charge(ctx, 2);
                v0 = 3;
                sw(v0, s0, 0);
            }
        } else {
            // 0x0011a8d4
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x0011a8e4
                charge(ctx, 5);
                lw(a0, s0, 60);
                jal(ctx, 0x11A8E8u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                if (v0 != 0) {
                    // 0x0011a8f8
                    charge(ctx, 76);
                    lw(a0, s0, 60);
                    a1 = 0;
                    a2 = addiu(sp, 0x4C);
                    jal(ctx, 0x11A904u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                    a0 = v0;
                    jal(ctx, 0x11A910u, gen::fn_sprCreateHandleFromData_00112420);
                    sw(v0, s0, 4);
                    lw(a0, s0, 60);
                    a1 = s1;
                    a2 = addiu(sp, 0x4C);
                    jal(ctx, 0x11A928u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                    a0 = v0;
                    jal(ctx, 0x11A934u, gen::fn_sprCreateHandleFromData_00112420);
                    sw(v0, s0, 8);
                    lw(a0, s0, 60);
                    a1 = 2;
                    a2 = addiu(sp, 0x4C);
                    jal(ctx, 0x11A94Cu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                    a0 = v0;
                    jal(ctx, 0x11A958u, gen::fn_sprCreateHandleFromData_00112420);
                    sw(v0, s0, 28);
                    lw(a0, s0, 60);
                    a1 = 3;
                    a2 = addiu(sp, 0x4C);
                    jal(ctx, 0x11A970u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                    a0 = v0;
                    jal(ctx, 0x11A97Cu, gen::fn_sprCreateHandleFromData_00112420);
                    sw(v0, s0, 36);
                    lw(a0, s0, 60);
                    a1 = 4;
                    a2 = addiu(sp, 0x4C);
                    jal(ctx, 0x11A994u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                    a0 = v0;
                    jal(ctx, 0x11A9A0u, gen::fn_sprCreateHandleFromData_00112420);
                    sw(v0, s0, 40);
                    lw(a0, s0, 60);
                    a1 = 5;
                    a2 = addiu(sp, 0x4C);
                    jal(ctx, 0x11A9B8u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                    a0 = v0;
                    jal(ctx, 0x11A9C4u, gen::fn_sprCreateHandleFromData_00112420);
                    sw(v0, s0, 44);
                    lw(a0, s0, 60);
                    a1 = 6;
                    a2 = addiu(sp, 0x4C);
                    jal(ctx, 0x11A9DCu, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                    a0 = v0;
                    jal(ctx, 0x11A9E8u, gen::fn_sprCreateHandleFromData_00112420);
                    sw(v0, s0, 48);
                    lw(a0, s0, 60);
                    a1 = 7;
                    a2 = addiu(sp, 0x4C);
                    jal(ctx, 0x11AA00u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                    a0 = v0;
                    jal(ctx, 0x11AA0Cu, gen::fn_sprCreateHandleFromData_00112420);
                    sw(v0, s0, 52);
                    v0 = s1;
                    sw(v0, s0, 0);
                }
            } else {
                // 0x0011a8dc
                charge(ctx, 2);
            }
        }
    }
    // 0x0011aab4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = 0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0011AAE0 sub_11AAE0 -- 240 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_DestroyStatusSprSetupFileTask] Destroy of "H_CampStatusSprSetupFile": as sub_119E00 without the message.
void sub_11AAE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0011aae0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, task::kWork);
    s0 = 0;
    for (;;) {
        // 0x0011ab2c
        charge(ctx, 3);
        v0 = slti(s0, 14);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0011ab04
        charge(ctx, 6);
        v0 = sll(s0, 2);
        v0 = addu(s1, v0);
        s2 = addiu(v0, 4);
        lw(a0, v0, 4);
        if (a0 != 0) {
            // 0x0011ab1c
            charge(ctx, 2);
            jal(ctx, 0x11AB1Cu, gen::fn_sub_1124B0_001124b0);  // release a sprite file
        }
        // 0x0011ab24
        charge(ctx, 2);
        sw(zero, s2, 0);
        s0 = addiu(s0, 1);
    }
    // 0x0011ab38
    charge(ctx, 3);
    lw(a0, s1, 60);
    if (a0 != 0) {
        // 0x0011ab44
        charge(ctx, 2);
        jal(ctx, 0x11AB44u, gen::fn_H_Cdvd_Destroy_00100ec0);
    }
    // 0x0011ab4c
    charge(ctx, 3);
    lw(a0, s1, 68);
    if (a0 != 0) {
        // 0x0011ab58
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x11AB60u, v0.u());
        sw(zero, gp, g::kCampTweens);  // 0x7CDF4C
    }
    // 0x0011ab6c
    charge(ctx, 5);
    a0 = 0;
    v1 = 0x830000;
    v1 = addiu(v1, 15216);  // &0x833B70
    for (;;) {
        // 0x0011ab90
        charge(ctx, 3);
        v0 = slti(a0, 14);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0011ab80
        charge(ctx, 4);
        v0 = sll(a0, 2);
        v0 = addu(v1, v0);
        sw(zero, v0, 0);
        a0 = addiu(a0, 1);
    }
    // 0x0011ab9c
    charge(ctx, 13);
    a0 = s1;
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x11ABA8u, v0.u());
    sw(zero, gp, g::kCampSetupTask);  // 0x7CDF48
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0011B0B0 sub_11B0B0 -- 348 bytes; frame 0x50: ra sp+0x30, s0 sp+0x20 (sq)
// [H_Camp_UpdatePersonaTexControlTask] Update of "CampPersonaTexControl": state 0 formats camp/persona/pst_%03X.tmx
// from the persona id (+4) into +20 and requests it (+8; id 0: straight to 3); 1: once loaded, starts the texture
// build sub_10C1A0(.., "h_camp.c", 1089) -> +16; 2: polls it (sub_10C3A0) until done -- the texture lands in +12 and
// the file is destroyed; 3: idle. Returns 0.
void sub_11B0B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0011b0b0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s0, sp, 0x20);
    lw(s0, a0, task::kWork);
    lw(a0, s0, 0);
    v1 = 3;
    if (a0 != v1) {
        // 0x0011b0d0
        charge(ctx, 3);
        v0 = 2;
        if (a0 == v0) {
            // 0x0011b1b4
            charge(ctx, 9);
            lw(a0, s0, 16);
            a1 = addiu(sp, 0x4C);
            a2 = 0;
            jal(ctx, 0x11B1C0u, gen::fn_sub_10C3A0_0010c3a0);  // poll a texture build
            sw(v0, s0, 12);
            lw(v0, sp, 0x4C);
            if (v0 != 0) {
                // 0x0011b1d8
                charge(ctx, 7);
                sw(zero, s0, 16);
                lw(a0, s0, 8);
                jal(ctx, 0x11B1E0u, gen::fn_H_Cdvd_Destroy_00100ec0);
                sw(zero, s0, 8);
                v0 = 3;
                sw(v0, s0, 0);
            }
        } else {
            // 0x0011b0dc
            charge(ctx, 3);
            v0 = 1;
            if (a0 == v0) {
                // 0x0011b148
                charge(ctx, 5);
                lw(a0, s0, 8);
                jal(ctx, 0x11B14Cu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                if (v0 != 0) {
                    // 0x0011b15c
                    charge(ctx, 22);
                    sd(zero, sp, 0x0);
                    sd(zero, sp, 0x8);
                    v0 = 0x5E0000;
                    v0 = addiu(v0, -21296);  // "h_camp.c"
                    sd(v0, sp, 0x10);
                    v0 = 1089;
                    sd(v0, sp, 0x18);
                    a0 = 0;
                    a1 = addiu(s0, 20);
                    a2 = 0;
                    a3 = 0;
                    t0 = 0;
                    t1 = 0;
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x11B198u, gen::fn_sub_10C1A0_0010c1a0);  // start a texture build
                    sw(v0, s0, 16);
                    v0 = 2;
                    sw(v0, s0, 0);
                }
            } else {
                // 0x0011b0e8
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x0011b0f8
                    charge(ctx, 3);
                    lw(a2, s0, 4);
                    if (a2 == 0) {
                        // 0x0011b13c
                        charge(ctx, 3);
                        sw(v1, s0, 0);
                    } else {
                        // 0x0011b104
                        charge(ctx, 14);
                        a0 = addiu(s0, 20);
                        a1 = 0x5E0000;
                        a1 = addiu(a1, -21328);  // "camp/persona/pst_%03X.tmx"
                        jal(ctx, 0x11B110u, gen::fn_sprintf_00523ac8);
                        a0 = addiu(s0, 20);
                        a1 = 0;
                        jal(ctx, 0x11B120u, gen::fn_H_Cdvd_Request_00100d80);
                        sw(v0, s0, 8);
                        v0 = 1;
                        sw(v0, s0, 0);
                    }
                } else {
                    // 0x0011b0f0
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x0011b1f4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 0;
    ld(ra, sp, 0x30);
    lq(s0, sp, 0x20);
    sp = addiu(sp, 0x50);
}

// 0x0011B210 sub_11B210 -- 152 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [H_Camp_DestroyPersonaTexControlTask] Destroy of "CampPersonaTexControl": a build still running (+16) is handed to a
// "CampPersonaDispCtlFree" task (sub_133D30) that releases it when done; otherwise the file (+8) and the texture (+12,
// sub_4D0F00) are released. Frees the work, gp-19856 = 0.
void sub_11B210(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0011b210
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a0, s0, 16);
    if (a0 == 0) {
        // 0x0011b24c
        charge(ctx, 3);
        lw(a0, s0, 8);
        if (a0 != 0) {
            // 0x0011b258
            charge(ctx, 3);
            jal(ctx, 0x11B258u, gen::fn_H_Cdvd_Destroy_00100ec0);
            sw(zero, s0, 8);
        }
        // 0x0011b264
        charge(ctx, 3);
        lw(a0, s0, 12);
        if (a0 != 0) {
            // 0x0011b270
            charge(ctx, 3);
            jal(ctx, 0x11B270u, gen::fn_sub_4D0F00_004d0f00);  // textureDestroy
            sw(zero, s0, 12);
        }
    } else {
        // 0x0011b22c
        charge(ctx, 8);
        lw(a1, s0, 8);
        jal(ctx, 0x11B230u, gen::fn_sub_133D30_00133d30);  // hand the build to a "CampPersonaDispCtlFree" task
        sw(zero, s0, 16);
        sw(zero, s0, 8);
        sw(zero, s0, 12);
    }
    // 0x0011b27c
    charge(ctx, 11);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x11B288u, v0.u());
    sw(zero, gp, g::kPersonaTexTask);  // 0x7CDF60
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0011B2B0 sub_11B2B0 -- 180 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_CreatePersonaTexControlTask] (parent, persona id): creates "CampPersonaTexControl" (276-byte work, priority
// 6335), +4 = the id, gp-19856 = the task. Returns the task or 0.
void sub_11B2B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0011b2b0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 1;
    a1 = 276;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x11B2E0u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x0011b300
        charge(ctx, 13);
        a0 = s2;
        a1 = 0x5E0000;
        a1 = addiu(a1, -21280);  // "CampPersonaTexControl"
        a2 = 6335;
        a3 = 0x120000;
        a3 = addiu(a3, -20304);  // &sub_11B0B0
        t0 = 0x120000;
        t0 = addiu(t0, -19952);  // &sub_11B210
        t1 = s0;
        jal(ctx, 0x11B324u, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x0011b340
            charge(ctx, 2);
            sw(s1, s0, 4);
            sw(v0, gp, g::kPersonaTexTask);  // 0x7CDF60
        } else {
            // 0x0011b334
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0011b2f4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0011b348 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0011B370 sub_11B370 -- 164 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_PersonaTexSetPersona] (persona id): when the id differs from the shown one, releases the current texture as
// sub_11B210 does and restarts the loader on the new id (state 0).
void sub_11B370(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0011b370
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v1, gp, g::kPersonaTexTask);  // 0x7CDF60
    lw(s0, v1, 60);
    lw(v1, s0, 4);
    if (v1 != s1) {
        // 0x0011b398
        charge(ctx, 3);
        lw(a0, s0, 16);
        if (a0 == 0) {
            // 0x0011b3c4
            charge(ctx, 3);
            lw(a0, s0, 8);
            if (a0 != 0) {
                // 0x0011b3d0
                charge(ctx, 3);
                jal(ctx, 0x11B3D0u, gen::fn_H_Cdvd_Destroy_00100ec0);
                sw(zero, s0, 8);
            }
            // 0x0011b3dc
            charge(ctx, 3);
            lw(a0, s0, 12);
            if (a0 != 0) {
                // 0x0011b3e8
                charge(ctx, 3);
                jal(ctx, 0x11B3E8u, gen::fn_sub_4D0F00_004d0f00);  // textureDestroy
                sw(zero, s0, 12);
            }
        } else {
            // 0x0011b3a4
            charge(ctx, 8);
            lw(a1, s0, 8);
            jal(ctx, 0x11B3A8u, gen::fn_sub_133D30_00133d30);  // hand the build to a "CampPersonaDispCtlFree" task
            sw(zero, s0, 16);
            sw(zero, s0, 8);
            sw(zero, s0, 12);
        }
        // 0x0011b3f4
        charge(ctx, 2);
        sw(s1, s0, 4);
        sw(zero, s0, 0);
    }
    // 0x0011b3fc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0011BAA0 sub_11BAA0 -- 48 bytes; frame 0x10: ra sp+0x0
// [H_Camp_DestroyRootDrawTask] Destroy of "H_CampRootDraw": frees the work, gp-19860 = 0.
void sub_11BAA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0011baa0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, task::kWork);
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x11BAB4u, v0.u());
    sw(zero, gp, g::kCampRootTask);  // 0x7CDF5C
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0011BAD0 H_Camp_CreateRootDrawTask -- 200 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// (parent, flash task, open mode): creates the main list "H_CampRootDraw" (44-byte work, priority 6335, update
// H_Camp_UpdateRootDrawTask): +36 flash, +12 selection = -1 (none), +8 open mode.
void H_Camp_CreateRootDrawTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0011bad0
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
    a1 = 44;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x11BB08u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x0011bb28
        charge(ctx, 13);
        a0 = s3;
        a1 = 0x5E0000;
        a1 = addiu(a1, -21256);  // "H_CampRootDraw"
        a2 = 6335;
        a3 = 0x120000;
        a3 = addiu(a3, -19424);  // &H_Camp_UpdateRootDrawTask
        t0 = 0x120000;
        t0 = addiu(t0, -17760);  // &sub_11BAA0
        t1 = s0;
        jal(ctx, 0x11BB4Cu, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x0011bb68
            charge(ctx, 4);
            sw(s2, s0, 36);
            v1 = si(-1);
            sw(v1, s0, 12);
            sw(s1, s0, 8);
        } else {
            // 0x0011bb5c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0011bb1c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0011bb78 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0011BBA0 nullsub_3 -- 8 bytes; leaf frame (no stack)
// Empty hook called by the list draws (sub_11C880 and five others).
void nullsub_3(EEContext& ctx) {
    using namespace hg;
    // 0x0011bba0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0011C550 sub_11C550 -- 816 bytes; frame 0x60: ra sp+0x40, s1 sp+0x30 (sq), s0 sp+0x20 (sq), f20 sp+0x10
// [H_Camp_RootSlideIn] (root work): starts the main list's slide-in on the tween records at gp-19876 (sub_18BC10 with
// mode 2, curve 1): records 0..6 = the seven rows from x 46 - 200 to 46 at y 59 + 19 i over frames i + 4 .. i + 10;
// record 10 = the highlight from x -19 to 181 at y 57 + 19 cursor (frames 10..16); records 11..14 = the cursor bar,
// the title and the two footer panels (y 415 / 395). The records' z is whatever the caller left in $f12.
void sub_11C550(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x0011c550
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f20, sp, 0x10);
    s1 = a0;
    mov_s(f20, f12);
    v0 = 0x42380000;
    mtc1(v0, f1);
    sw(v0, sp, 0x50);
    v0 = 0x426C0000;
    sw(v0, sp, 0x54);
    v0 = 0x43480000;
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x58);
    s0 = 0;
    for (;;) {
        // 0x0011c610
        charge(ctx, 3);
        v0 = slti(s0, 7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0011c5a0
        charge(ctx, 28);
        lwc1(f0, sp, 0x54);
        swc1(f0, sp, 0x5C);
        v0 = addiu(s0, 4);
        sd(v0, sp, 0x0);
        v0 = addiu(s0, 10);
        sd(v0, sp, 0x8);
        v0 = sll(s0, 4);
        v0 = addu(v0, s0);
        v1 = sll(v0, 2);
        lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
        a0 = addu(v0, v1);
        a1 = 0;
        a2 = 2;
        a3 = 1;
        ld(t0, sp, 0x58);
        ld(t1, sp, 0x50);
        t2 = 0;
        t3 = 0;
        mov_s(f12, f20);
        jal(ctx, 0x11C5ECu, gen::fn_sub_18BC10_0018bc10);
        lwc1(f1, sp, 0x54);
        v0 = 0x41980000;
        mtc1(v0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0x54);
        s0 = addiu(s0, 1);
    }
    // 0x0011c61c
    charge(ctx, 153);
    v0 = lui(0xC198);
    sw(v0, sp, 0x58);
    lwc1(f0, s1, 16);
    v0 = 0x41980000;
    mtc1(v0, f1);
    cvt_s_w(f0, f0);
    mul_s(f1, f1, f0);
    v0 = 0x42640000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    swc1(f0, sp, 0x5C);
    v0 = 0x43350000;
    sw(v0, sp, 0x50);
    swc1(f0, sp, 0x54);
    v0 = 10;
    sd(v0, sp, 0x0);
    v0 = 16;
    sd(v0, sp, 0x8);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 680);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x50);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x11C694u, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x42380000;
    mtc1(v0, f1);
    sw(v0, sp, 0x50);
    v1 = 0x426C0000;
    sw(v1, sp, 0x54);
    v0 = 0x43480000;
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x58);
    sw(v1, sp, 0x5C);
    v0 = 10;
    sd(v0, sp, 0x0);
    v0 = 16;
    sd(v0, sp, 0x8);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 748);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x50);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x11C700u, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x42240000;
    mtc1(v0, f1);
    sw(v0, sp, 0x50);
    v1 = 0x41300000;
    sw(v1, sp, 0x54);
    v0 = 0x42200000;
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x58);
    sw(v1, sp, 0x5C);
    v0 = 11;
    sd(v0, sp, 0x0);
    v0 = 16;
    sd(v0, sp, 0x8);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 816);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x50);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x11C76Cu, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x42300000;
    mtc1(v0, f2);
    sw(v0, sp, 0x50);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0x54);
    v0 = 0x43480000;
    mtc1(v0, f0);
    sub_s(f0, f2, f0);
    swc1(f0, sp, 0x58);
    swc1(f1, sp, 0x5C);
    v0 = 15;
    sd(v0, sp, 0x0);
    v0 = 21;
    sd(v0, sp, 0x8);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 884);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x50);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x11C7E4u, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x42300000;
    mtc1(v0, f2);
    sw(v0, sp, 0x50);
    v0 = 395;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0x54);
    v0 = 0x43480000;
    mtc1(v0, f0);
    sub_s(f0, f2, f0);
    swc1(f0, sp, 0x58);
    swc1(f1, sp, 0x5C);
    v0 = 15;
    sd(v0, sp, 0x0);
    v0 = 21;
    sd(v0, sp, 0x8);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 952);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x50);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x11C85Cu, gen::fn_sub_18BC10_0018bc10);
    ld(ra, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0x60);
}

// 0x0011CC80 sub_11CC80 -- 808 bytes; frame 0x60: ra sp+0x40, s1 sp+0x30 (sq), s0 sp+0x20 (sq), f20 sp+0x10
// [H_Camp_RootFadeIn] (root work): the same records as sub_11C550 over frames 0..10 with mode 0 (fade in); the cursor
// bar's y 59 + 19 cursor through adda.s / madd.s.
void sub_11CC80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f12{ctx, 12}, f20{ctx, 20};
    // 0x0011cc80
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f20, sp, 0x10);
    s1 = a0;
    mov_s(f20, f12);
    v0 = 0x42380000;
    mtc1(v0, f1);
    sw(v0, sp, 0x50);
    v0 = 0x426C0000;
    sw(v0, sp, 0x54);
    v0 = 0x43480000;
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x58);
    s0 = 0;
    for (;;) {
        // 0x0011cd3c
        charge(ctx, 3);
        v0 = slti(s0, 7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0011ccd0
        charge(ctx, 27);
        lwc1(f0, sp, 0x54);
        swc1(f0, sp, 0x5C);
        sd(zero, sp, 0x0);
        v0 = 10;
        sd(v0, sp, 0x8);
        v0 = sll(s0, 4);
        v0 = addu(v0, s0);
        v1 = sll(v0, 2);
        lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
        a0 = addu(v0, v1);
        a1 = 0;
        a2 = 0;
        a3 = 1;
        ld(t0, sp, 0x58);
        ld(t1, sp, 0x50);
        t2 = 0;
        t3 = 0;
        mov_s(f12, f20);
        jal(ctx, 0x11CD18u, gen::fn_sub_18BC10_0018bc10);
        lwc1(f1, sp, 0x54);
        v0 = 0x41980000;
        mtc1(v0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0x54);
        s0 = addiu(s0, 1);
    }
    // 0x0011cd48
    charge(ctx, 152);
    v0 = lui(0xC198);
    sw(v0, sp, 0x58);
    lwc1(f0, s1, 16);
    v0 = 0x41980000;
    mtc1(v0, f1);
    cvt_s_w(f0, f0);
    mul_s(f1, f1, f0);
    v0 = 0x42640000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    swc1(f0, sp, 0x5C);
    v0 = 0x43350000;
    sw(v0, sp, 0x50);
    swc1(f0, sp, 0x54);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 680);
    a1 = 0;
    a2 = 0;
    a3 = 1;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x50);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x11CDBCu, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x42380000;
    mtc1(v0, f4);
    sw(v0, sp, 0x50);
    lwc1(f0, s1, 16);
    cvt_s_w(f3, f0);
    v0 = 0x41980000;
    mtc1(v0, f2);
    v0 = 0x426C0000;
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f1, f2, f3);
    swc1(f1, sp, 0x54);
    v0 = 0x43480000;
    mtc1(v0, f0);
    sub_s(f0, f4, f0);
    swc1(f0, sp, 0x58);
    swc1(f1, sp, 0x5C);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 748);
    a1 = 0;
    a2 = 0;
    a3 = 1;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x50);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x11CE48u, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x42240000;
    mtc1(v0, f1);
    sw(v0, sp, 0x50);
    v1 = 0x41300000;
    sw(v1, sp, 0x54);
    v0 = 0x42200000;
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x58);
    sw(v1, sp, 0x5C);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 816);
    a1 = 0;
    a2 = 0;
    a3 = 1;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x50);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x11CEB0u, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x42300000;
    mtc1(v0, f2);
    sw(v0, sp, 0x50);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0x54);
    v0 = 0x43480000;
    mtc1(v0, f0);
    sub_s(f0, f2, f0);
    swc1(f0, sp, 0x58);
    swc1(f1, sp, 0x5C);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 884);
    a1 = 0;
    a2 = 0;
    a3 = 1;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x50);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x11CF24u, gen::fn_sub_18BC10_0018bc10);
    v1 = 0x42300000;
    sw(v1, sp, 0x50);
    v0 = 395;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x54);
    sw(v1, sp, 0x58);
    swc1(f0, sp, 0x5C);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 952);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x50);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x11CF84u, gen::fn_sub_18BC10_0018bc10);
    ld(ra, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0x60);
}

// 0x0011D3A0 sub_11D3A0 -- 808 bytes; frame 0x60: ra sp+0x40, s1 sp+0x30 (sq), s0 sp+0x20 (sq), f20 sp+0x10
// [H_Camp_RootFadeOut] (root work): the same records over frames 0..10, mode 0 / curve 2 (fade out) -- the close of
// the list (sub_11B9B0 / sub_11BA00).
void sub_11D3A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f12{ctx, 12}, f20{ctx, 20};
    // 0x0011d3a0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f20, sp, 0x10);
    s1 = a0;
    mov_s(f20, f12);
    v0 = 0x42380000;
    mtc1(v0, f1);
    sw(v0, sp, 0x50);
    v0 = 0x426C0000;
    sw(v0, sp, 0x54);
    v0 = 0x43480000;
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x58);
    s0 = 0;
    for (;;) {
        // 0x0011d45c
        charge(ctx, 3);
        v0 = slti(s0, 7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0011d3f0
        charge(ctx, 27);
        lwc1(f0, sp, 0x54);
        swc1(f0, sp, 0x5C);
        sd(zero, sp, 0x0);
        v0 = 10;
        sd(v0, sp, 0x8);
        v0 = sll(s0, 4);
        v0 = addu(v0, s0);
        v1 = sll(v0, 2);
        lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
        a0 = addu(v0, v1);
        a1 = 0;
        a2 = 0;
        a3 = 2;
        ld(t0, sp, 0x58);
        ld(t1, sp, 0x50);
        t2 = 0;
        t3 = 0;
        mov_s(f12, f20);
        jal(ctx, 0x11D438u, gen::fn_sub_18BC10_0018bc10);
        lwc1(f1, sp, 0x54);
        v0 = 0x41980000;
        mtc1(v0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0x54);
        s0 = addiu(s0, 1);
    }
    // 0x0011d468
    charge(ctx, 152);
    v0 = lui(0xC198);
    sw(v0, sp, 0x58);
    lwc1(f0, s1, 16);
    v0 = 0x41980000;
    mtc1(v0, f1);
    cvt_s_w(f0, f0);
    mul_s(f1, f1, f0);
    v0 = 0x42640000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    swc1(f0, sp, 0x5C);
    v0 = 0x43350000;
    sw(v0, sp, 0x50);
    swc1(f0, sp, 0x54);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 680);
    a1 = 0;
    a2 = 0;
    a3 = 2;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x50);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x11D4DCu, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x42380000;
    mtc1(v0, f4);
    sw(v0, sp, 0x50);
    lwc1(f0, s1, 16);
    cvt_s_w(f3, f0);
    v0 = 0x41980000;
    mtc1(v0, f2);
    v0 = 0x426C0000;
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f1, f2, f3);
    swc1(f1, sp, 0x54);
    v0 = 0x43480000;
    mtc1(v0, f0);
    sub_s(f0, f4, f0);
    swc1(f0, sp, 0x58);
    swc1(f1, sp, 0x5C);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 748);
    a1 = 0;
    a2 = 0;
    a3 = 2;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x50);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x11D568u, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x42240000;
    mtc1(v0, f1);
    sw(v0, sp, 0x50);
    v1 = 0x41300000;
    sw(v1, sp, 0x54);
    v0 = 0x42200000;
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x58);
    sw(v1, sp, 0x5C);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 816);
    a1 = 0;
    a2 = 0;
    a3 = 2;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x50);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x11D5D0u, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x42300000;
    mtc1(v0, f2);
    sw(v0, sp, 0x50);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0x54);
    v0 = 0x43480000;
    mtc1(v0, f0);
    sub_s(f0, f2, f0);
    swc1(f0, sp, 0x58);
    swc1(f1, sp, 0x5C);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 884);
    a1 = 0;
    a2 = 0;
    a3 = 2;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x50);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x11D644u, gen::fn_sub_18BC10_0018bc10);
    v1 = 0x42300000;
    sw(v1, sp, 0x50);
    v0 = 395;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x54);
    sw(v1, sp, 0x58);
    swc1(f0, sp, 0x5C);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 952);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x50);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x11D6A4u, gen::fn_sub_18BC10_0018bc10);
    ld(ra, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0x60);
}

// 0x0011DA80 sub_11DA80 -- 808 bytes; frame 0x60: ra sp+0x40, s1 sp+0x30 (sq), s0 sp+0x20 (sq), f20 sp+0x10
// [H_Camp_RootFadeOut2] (root work): a copy of sub_11D3A0 used by the item and skill screens (the same records from
// the same input).
void sub_11DA80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f12{ctx, 12}, f20{ctx, 20};
    // 0x0011da80
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f20, sp, 0x10);
    s1 = a0;
    mov_s(f20, f12);
    v0 = 0x42380000;
    mtc1(v0, f1);
    sw(v0, sp, 0x50);
    v0 = 0x426C0000;
    sw(v0, sp, 0x54);
    v0 = 0x43480000;
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x58);
    s0 = 0;
    for (;;) {
        // 0x0011db3c
        charge(ctx, 3);
        v0 = slti(s0, 7);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0011dad0
        charge(ctx, 27);
        lwc1(f0, sp, 0x54);
        swc1(f0, sp, 0x5C);
        sd(zero, sp, 0x0);
        v0 = 10;
        sd(v0, sp, 0x8);
        v0 = sll(s0, 4);
        v0 = addu(v0, s0);
        v1 = sll(v0, 2);
        lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
        a0 = addu(v0, v1);
        a1 = 0;
        a2 = 0;
        a3 = 2;
        ld(t0, sp, 0x58);
        ld(t1, sp, 0x50);
        t2 = 0;
        t3 = 0;
        mov_s(f12, f20);
        jal(ctx, 0x11DB18u, gen::fn_sub_18BC10_0018bc10);
        lwc1(f1, sp, 0x54);
        v0 = 0x41980000;
        mtc1(v0, f0);
        add_s(f0, f1, f0);
        swc1(f0, sp, 0x54);
        s0 = addiu(s0, 1);
    }
    // 0x0011db48
    charge(ctx, 152);
    v0 = lui(0xC198);
    sw(v0, sp, 0x58);
    lwc1(f0, s1, 16);
    v0 = 0x41980000;
    mtc1(v0, f1);
    cvt_s_w(f0, f0);
    mul_s(f1, f1, f0);
    v0 = 0x42640000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    swc1(f0, sp, 0x5C);
    v0 = 0x43350000;
    sw(v0, sp, 0x50);
    swc1(f0, sp, 0x54);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 680);
    a1 = 0;
    a2 = 0;
    a3 = 2;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x50);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x11DBBCu, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x42380000;
    mtc1(v0, f4);
    sw(v0, sp, 0x50);
    lwc1(f0, s1, 16);
    cvt_s_w(f3, f0);
    v0 = 0x41980000;
    mtc1(v0, f2);
    v0 = 0x426C0000;
    mtc1(v0, f1);
    mtc1(zero, f0);
    adda_s(f0, f1);
    madd_s(f1, f2, f3);
    swc1(f1, sp, 0x54);
    v0 = 0x43480000;
    mtc1(v0, f0);
    sub_s(f0, f4, f0);
    swc1(f0, sp, 0x58);
    swc1(f1, sp, 0x5C);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 748);
    a1 = 0;
    a2 = 0;
    a3 = 2;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x50);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x11DC48u, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x42240000;
    mtc1(v0, f1);
    sw(v0, sp, 0x50);
    v1 = 0x41300000;
    sw(v1, sp, 0x54);
    v0 = 0x42200000;
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x58);
    sw(v1, sp, 0x5C);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 816);
    a1 = 0;
    a2 = 0;
    a3 = 2;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x50);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x11DCB0u, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x42300000;
    mtc1(v0, f2);
    sw(v0, sp, 0x50);
    v0 = 415;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    swc1(f1, sp, 0x54);
    v0 = 0x43480000;
    mtc1(v0, f0);
    sub_s(f0, f2, f0);
    swc1(f0, sp, 0x58);
    swc1(f1, sp, 0x5C);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 884);
    a1 = 0;
    a2 = 0;
    a3 = 2;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x50);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x11DD24u, gen::fn_sub_18BC10_0018bc10);
    v1 = 0x42300000;
    sw(v1, sp, 0x50);
    v0 = 395;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x54);
    sw(v1, sp, 0x58);
    swc1(f0, sp, 0x5C);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v0, gp, g::kCampTweens);  // 0x7CDF4C
    a0 = addiu(v0, 952);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x58);
    ld(t1, sp, 0x50);
    t2 = 0;
    t3 = 0;
    mov_s(f12, f20);
    jal(ctx, 0x11DD84u, gen::fn_sub_18BC10_0018bc10);
    ld(ra, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f20, sp, 0x10);
    sp = addiu(sp, 0x60);
}

// 0x0011E380 sub_11E380 -- 1696 bytes; leaf frame (no stack)
// [H_CampFlash_Request] (flash task, screen): when the flash task is idle (state 0) picks the transition for (the
// screen shown, +8; the requested one) through three jump tables -- the dispatcher state of sub_11EA20 -- or just
// raises the done flag (+16) when no animation is needed; does nothing while a transition runs.
void sub_11E380(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0011e380
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, task::kWork);
    lw(v1, v0, fl::kState);
    if (v1 == 0) {
        // 0x0011e39c
        charge(ctx, 4);
        sw(zero, v0, fl::kDone);
        at = sltiu(a1, 17);
        if (at != 0) {
            // 0x0011e3ac
            charge(ctx, 7);
            a0 = 0x7B0000;
            a0 = addiu(a0, 21904);  // &0x7B5590
            v1 = sll(a1, 2);
            v1 = addu(v1, a0);
            lw(v1, v1, 0);
            switch (v1.u()) {
            case 0x11E3C8u:  // table[0]
                // 0x0011e3c8
                charge(ctx, 4);
                v1 = 13;
                sw(v1, v0, fl::kState);
                break;
            case 0x11E3D8u:  // table[1]
                // 0x0011e3d8
                charge(ctx, 4);
                lw(v1, v0, fl::kScreen);
                at = sltiu(v1, 17);
                if (at != 0) {
                    // 0x0011e3e8
                    charge(ctx, 7);
                    a0 = 0x7B0000;
                    a0 = addiu(a0, 21824);  // &0x7B5540
                    v1 = sll(v1, 2);
                    v1 = addu(v1, a0);
                    lw(v1, v1, 0);
                    switch (v1.u()) {
                    case 0x11E404u:  // table[0]
                        // 0x0011e404
                        charge(ctx, 4);
                        v1 = 1;
                        sw(v1, v0, fl::kState);
                        break;
                    case 0x11E414u:  // table[1]
                        // 0x0011e414
                        charge(ctx, 4);
                        v1 = 1;
                        sw(v1, v0, fl::kDone);
                        break;
                    case 0x11E424u:  // table[2]
                        // 0x0011e424
                        charge(ctx, 4);
                        v1 = 11;
                        sw(v1, v0, fl::kState);
                        break;
                    case 0x11E434u:  // table[3]
                        // 0x0011e434
                        charge(ctx, 4);
                        v1 = 11;
                        sw(v1, v0, fl::kState);
                        break;
                    case 0x11E444u:  // table[4, 6, 7, 8, 9, 11, 12, 15, 16]
                        // 0x0011e444
                        charge(ctx, 4);
                        v1 = 11;
                        sw(v1, v0, fl::kState);
                        break;
                    case 0x11E454u:  // table[13]
                        // 0x0011e454
                        charge(ctx, 4);
                        v1 = 11;
                        sw(v1, v0, fl::kState);
                        break;
                    case 0x11EA10u:  // table[5, 10, 14]
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v1.u());
                        return;
                    }
                }
                break;
            case 0x11E464u:  // table[2]
                // 0x0011e464
                charge(ctx, 4);
                lw(a2, v0, fl::kScreen);
                v1 = 13;
                if (a2 == v1) {
                    // 0x0011e4f8
                    charge(ctx, 4);
                    v1 = 1;
                    sw(v1, v0, fl::kDone);
                } else {
                    // 0x0011e474
                    charge(ctx, 3);
                    v1 = 9;
                    if (a2 == v1) {
                        // 0x0011e4e8
                        charge(ctx, 4);
                        v1 = 1;
                        sw(v1, v0, fl::kDone);
                    } else {
                        // 0x0011e480
                        charge(ctx, 3);
                        a0 = 3;
                        if (a2 == a0) {
                            // 0x0011e4dc
                            charge(ctx, 3);
                            sw(v1, v0, fl::kState);
                        } else {
                            // 0x0011e48c
                            charge(ctx, 3);
                            v1 = 2;
                            if (a2 == v1) {
                                // 0x0011e4cc
                                charge(ctx, 4);
                                v1 = 1;
                                sw(v1, v0, fl::kDone);
                            } else {
                                // 0x0011e498
                                charge(ctx, 3);
                                v1 = 1;
                                if (a2 == v1) {
                                    // 0x0011e4c0
                                    charge(ctx, 3);
                                    sw(a0, v0, fl::kState);
                                } else {
                                    // 0x0011e4a4
                                    charge(ctx, 2);
                                    if (a2 == 0) {
                                        // 0x0011e4b4
                                        charge(ctx, 3);
                                        sw(a0, v0, fl::kState);
                                    } else {
                                        // 0x0011e4ac
                                        charge(ctx, 2);
                                    }
                                }
                            }
                        }
                    }
                }
                break;
            case 0x11E508u:  // table[3]
                // 0x0011e508
                charge(ctx, 4);
                lw(a0, v0, fl::kScreen);
                v1 = 13;
                if (a0 == v1) {
                    // 0x0011e5a8
                    charge(ctx, 4);
                    v1 = 1;
                    sw(v1, v0, fl::kDone);
                } else {
                    // 0x0011e518
                    charge(ctx, 3);
                    v1 = 9;
                    if (a0 == v1) {
                        // 0x0011e598
                        charge(ctx, 4);
                        v1 = 1;
                        sw(v1, v0, fl::kDone);
                    } else {
                        // 0x0011e524
                        charge(ctx, 3);
                        v1 = 3;
                        if (a0 == v1) {
                            // 0x0011e588
                            charge(ctx, 4);
                            v1 = 7;
                            sw(v1, v0, fl::kState);
                        } else {
                            // 0x0011e530
                            charge(ctx, 3);
                            v1 = 2;
                            if (a0 == v1) {
                                // 0x0011e578
                                charge(ctx, 4);
                                v1 = 7;
                                sw(v1, v0, fl::kState);
                            } else {
                                // 0x0011e53c
                                charge(ctx, 3);
                                v1 = 1;
                                if (a0 == v1) {
                                    // 0x0011e568
                                    charge(ctx, 4);
                                    v1 = 7;
                                    sw(v1, v0, fl::kState);
                                } else {
                                    // 0x0011e548
                                    charge(ctx, 2);
                                    if (a0 == 0) {
                                        // 0x0011e558
                                        charge(ctx, 4);
                                        v1 = 7;
                                        sw(v1, v0, fl::kState);
                                    } else {
                                        // 0x0011e550
                                        charge(ctx, 2);
                                    }
                                }
                            }
                        }
                    }
                }
                break;
            case 0x11E5B8u:  // table[9]
                // 0x0011e5b8
                charge(ctx, 4);
                lw(v1, v0, fl::kScreen);
                at = sltiu(v1, 15);
                if (at != 0) {
                    // 0x0011e5c8
                    charge(ctx, 7);
                    a0 = 0x7B0000;
                    a0 = addiu(a0, 21760);  // &0x7B5500
                    v1 = sll(v1, 2);
                    v1 = addu(v1, a0);
                    lw(v1, v1, 0);
                    switch (v1.u()) {
                    case 0x11E5E4u:  // table[0]
                        // 0x0011e5e4
                        charge(ctx, 4);
                        v1 = 1;
                        sw(v1, v0, fl::kDone);
                        break;
                    case 0x11E5F4u:  // table[1]
                        // 0x0011e5f4
                        charge(ctx, 4);
                        v1 = 15;
                        sw(v1, v0, fl::kState);
                        break;
                    case 0x11E604u:  // table[2]
                        // 0x0011e604
                        charge(ctx, 4);
                        v1 = 1;
                        sw(v1, v0, fl::kDone);
                        break;
                    case 0x11E614u:  // table[3]
                        // 0x0011e614
                        charge(ctx, 4);
                        v1 = 1;
                        sw(v1, v0, fl::kDone);
                        break;
                    case 0x11E624u:  // table[9]
                        // 0x0011e624
                        charge(ctx, 4);
                        v1 = 1;
                        sw(v1, v0, fl::kDone);
                        break;
                    case 0x11E634u:  // table[10]
                        // 0x0011e634
                        charge(ctx, 4);
                        v1 = 19;
                        sw(v1, v0, fl::kState);
                        break;
                    case 0x11E644u:  // table[13]
                        // 0x0011e644
                        charge(ctx, 4);
                        v1 = 1;
                        sw(v1, v0, fl::kDone);
                        break;
                    case 0x11E654u:  // table[14]
                        // 0x0011e654
                        charge(ctx, 4);
                        v1 = 19;
                        sw(v1, v0, fl::kState);
                        break;
                    case 0x11E664u:  // table[11]
                        // 0x0011e664
                        charge(ctx, 4);
                        v1 = 23;
                        sw(v1, v0, fl::kState);
                        break;
                    case 0x11E674u:  // table[12]
                        // 0x0011e674
                        charge(ctx, 4);
                        v1 = 29;
                        sw(v1, v0, fl::kState);
                        break;
                    case 0x11EA10u:  // table[4, 5, 6, 7, 8]
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v1.u());
                        return;
                    }
                }
                break;
            case 0x11E684u:  // table[10]
                // 0x0011e684
                charge(ctx, 4);
                lw(a0, v0, fl::kScreen);
                v1 = 13;
                if (a0 == v1) {
                    // 0x0011e6b8
                    charge(ctx, 4);
                    v1 = 17;
                    sw(v1, v0, fl::kState);
                } else {
                    // 0x0011e694
                    charge(ctx, 3);
                    v1 = 9;
                    if (a0 == v1) {
                        // 0x0011e6a8
                        charge(ctx, 4);
                        v1 = 17;
                        sw(v1, v0, fl::kState);
                    } else {
                        // 0x0011e6a0
                        charge(ctx, 2);
                    }
                }
                break;
            case 0x11E6C8u:  // table[11]
                // 0x0011e6c8
                charge(ctx, 4);
                lw(a0, v0, fl::kScreen);
                v1 = 12;
                if (a0 == v1) {
                    // 0x0011e718
                    charge(ctx, 4);
                    v1 = 31;
                    sw(v1, v0, fl::kState);
                } else {
                    // 0x0011e6d8
                    charge(ctx, 3);
                    v1 = 9;
                    if (a0 == v1) {
                        // 0x0011e708
                        charge(ctx, 4);
                        v1 = 21;
                        sw(v1, v0, fl::kState);
                    } else {
                        // 0x0011e6e4
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x0011e6f8
                            charge(ctx, 4);
                            v1 = 15;
                            sw(v1, v0, fl::kState);
                        } else {
                            // 0x0011e6f0
                            charge(ctx, 2);
                        }
                    }
                }
                break;
            case 0x11E728u:  // table[12]
                // 0x0011e728
                charge(ctx, 4);
                lw(a0, v0, fl::kScreen);
                v1 = 11;
                if (a0 == v1) {
                    // 0x0011e778
                    charge(ctx, 4);
                    v1 = 27;
                    sw(v1, v0, fl::kState);
                } else {
                    // 0x0011e738
                    charge(ctx, 3);
                    v1 = 9;
                    if (a0 == v1) {
                        // 0x0011e768
                        charge(ctx, 4);
                        v1 = 25;
                        sw(v1, v0, fl::kState);
                    } else {
                        // 0x0011e744
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x0011e758
                            charge(ctx, 4);
                            v1 = 15;
                            sw(v1, v0, fl::kState);
                        } else {
                            // 0x0011e750
                            charge(ctx, 2);
                        }
                    }
                }
                break;
            case 0x11E788u:  // table[13]
                // 0x0011e788
                charge(ctx, 4);
                lw(a0, v0, fl::kScreen);
                v1 = 14;
                if (a0 == v1) {
                    // 0x0011e85c
                    charge(ctx, 4);
                    v1 = 43;
                    sw(v1, v0, fl::kState);
                } else {
                    // 0x0011e798
                    charge(ctx, 3);
                    v1 = 13;
                    if (a0 == v1) {
                        // 0x0011e84c
                        charge(ctx, 4);
                        v1 = 1;
                        sw(v1, v0, fl::kDone);
                    } else {
                        // 0x0011e7a4
                        charge(ctx, 3);
                        v1 = 10;
                        if (a0 == v1) {
                            // 0x0011e83c
                            charge(ctx, 4);
                            v1 = 1;
                            sw(v1, v0, fl::kDone);
                        } else {
                            // 0x0011e7b0
                            charge(ctx, 3);
                            v1 = 9;
                            if (a0 == v1) {
                                // 0x0011e82c
                                charge(ctx, 4);
                                v1 = 1;
                                sw(v1, v0, fl::kDone);
                            } else {
                                // 0x0011e7bc
                                charge(ctx, 3);
                                v1 = 3;
                                if (a0 == v1) {
                                    // 0x0011e81c
                                    charge(ctx, 4);
                                    v1 = 1;
                                    sw(v1, v0, fl::kDone);
                                } else {
                                    // 0x0011e7c8
                                    charge(ctx, 3);
                                    v1 = 2;
                                    if (a0 == v1) {
                                        // 0x0011e80c
                                        charge(ctx, 4);
                                        v1 = 1;
                                        sw(v1, v0, fl::kDone);
                                    } else {
                                        // 0x0011e7d4
                                        charge(ctx, 3);
                                        v1 = 1;
                                        if (a0 == v1) {
                                            // 0x0011e7fc
                                            charge(ctx, 4);
                                            v1 = 39;
                                            sw(v1, v0, fl::kState);
                                        } else {
                                            // 0x0011e7e0
                                            charge(ctx, 2);
                                            if (a0 == 0) {
                                                // 0x0011e7f0
                                                charge(ctx, 3);
                                                sw(v1, v0, fl::kDone);
                                            } else {
                                                // 0x0011e7e8
                                                charge(ctx, 2);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                break;
            case 0x11E86Cu:  // table[14]
                // 0x0011e86c
                charge(ctx, 4);
                lw(a0, v0, fl::kScreen);
                v1 = 13;
                if (a0 == v1) {
                    // 0x0011e884
                    charge(ctx, 4);
                    v1 = 41;
                    sw(v1, v0, fl::kState);
                } else {
                    // 0x0011e87c
                    charge(ctx, 2);
                }
                break;
            case 0x11E894u:  // table[7]
                // 0x0011e894
                charge(ctx, 4);
                lw(a0, v0, fl::kScreen);
                v1 = 8;
                if (a0 == v1) {
                    // 0x0011e8d4
                    charge(ctx, 4);
                    v1 = 37;
                    sw(v1, v0, fl::kState);
                } else {
                    // 0x0011e8a4
                    charge(ctx, 3);
                    v1 = 7;
                    if (a0 != v1) {
                        // 0x0011e8b0
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x0011e8c4
                            charge(ctx, 4);
                            v1 = 33;
                            sw(v1, v0, fl::kState);
                        } else {
                            // 0x0011e8bc
                            charge(ctx, 2);
                        }
                    }
                }
                break;
            case 0x11E8E4u:  // table[8]
                // 0x0011e8e4
                charge(ctx, 4);
                lw(a0, v0, fl::kScreen);
                v1 = 8;
                if (a0 != v1) {
                    // 0x0011e8f4
                    charge(ctx, 3);
                    v1 = 7;
                    if (a0 == v1) {
                        // 0x0011e908
                        charge(ctx, 4);
                        v1 = 35;
                        sw(v1, v0, fl::kState);
                    } else {
                        // 0x0011e900
                        charge(ctx, 2);
                    }
                }
                break;
            case 0x11E918u:  // table[15]
                // 0x0011e918
                charge(ctx, 4);
                lw(a0, v0, fl::kScreen);
                v1 = 16;
                if (a0 == v1) {
                    // 0x0011e94c
                    charge(ctx, 4);
                    v1 = 49;
                    sw(v1, v0, fl::kState);
                } else {
                    // 0x0011e928
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x0011e93c
                        charge(ctx, 4);
                        v1 = 45;
                        sw(v1, v0, fl::kState);
                    } else {
                        // 0x0011e934
                        charge(ctx, 2);
                    }
                }
                break;
            case 0x11E95Cu:  // table[16]
                // 0x0011e95c
                charge(ctx, 4);
                lw(a0, v0, fl::kScreen);
                v1 = 15;
                if (a0 == v1) {
                    // 0x0011e974
                    charge(ctx, 4);
                    v1 = 47;
                    sw(v1, v0, fl::kState);
                } else {
                    // 0x0011e96c
                    charge(ctx, 2);
                }
                break;
            case 0x11E984u:  // table[4]
                // 0x0011e984
                charge(ctx, 4);
                lw(a0, v0, fl::kScreen);
                v1 = 5;
                if (a0 == v1) {
                    // 0x0011e9b8
                    charge(ctx, 4);
                    v1 = 55;
                    sw(v1, v0, fl::kState);
                } else {
                    // 0x0011e994
                    charge(ctx, 3);
                    v1 = 1;
                    if (a0 == v1) {
                        // 0x0011e9a8
                        charge(ctx, 4);
                        v1 = 45;
                        sw(v1, v0, fl::kState);
                    } else {
                        // 0x0011e9a0
                        charge(ctx, 2);
                    }
                }
                break;
            case 0x11E9C8u:  // table[5]
                // 0x0011e9c8
                charge(ctx, 4);
                lw(a0, v0, fl::kScreen);
                v1 = 4;
                if (a0 == v1) {
                    // 0x0011e9e0
                    charge(ctx, 4);
                    v1 = 53;
                    sw(v1, v0, fl::kState);
                } else {
                    // 0x0011e9d8
                    charge(ctx, 2);
                }
                break;
            case 0x11E9F0u:  // table[6]
                // 0x0011e9f0
                charge(ctx, 4);
                lw(a0, v0, fl::kScreen);
                v1 = 1;
                if (a0 == v1) {
                    // 0x0011ea08
                    charge(ctx, 2);
                    v1 = 57;
                    sw(v1, v0, fl::kState);
                } else {
                    // 0x0011ea00
                    charge(ctx, 2);
                }
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v1.u());
                return;
            }
        }
        // 0x0011ea10
        charge(ctx, 2);
        sw(a1, v0, fl::kScreen);
        v0 = 1;
    } else {
        // 0x0011e390
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0011ea18 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0011EA20 sub_11EA20 -- 1792 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [H_CampFlash_UpdateTask] Update of "h_camp_flash_control" (jump table 0x7B55E0, 59 states): an odd state arms a
// transition (state + 1, done +16 = 0, step +4 = 0), an even state runs its player (sub_11F260 .. sub_121C30) once per
// frame and returns to 0 when the player's step is 999; state 6 finishes the task (-1). Returns 0.
void sub_11EA20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0011ea20
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(v0, s0, fl::kState);
    at = sltiu(v0, 59);
    if (at != 0) {
        // 0x0011ea40
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 21984);  // &0x7B55E0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x11EA5Cu:  // table[1]
            // 0x0011ea5c
            charge(ctx, 6);
            v0 = 2;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108: the "return 0" block every arm below ends with
            v0 = 0;
            break;
        case 0x11EA74u:  // table[2]
            // 0x0011ea74
            charge(ctx, 6);
            jal(ctx, 0x11EA74u, gen::fn_sub_11F260_0011f260);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011ea8c
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EA98u:  // table[3]
            // 0x0011ea98
            charge(ctx, 6);
            v0 = 4;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EAB0u:  // table[4]
            // 0x0011eab0
            charge(ctx, 6);
            jal(ctx, 0x11EAB0u, gen::fn_sub_11F400_0011f400);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011eac8
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EAD4u:  // table[5]
            // 0x0011ead4
            charge(ctx, 6);
            v0 = 6;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EAECu:  // table[6]
            // 0x0011eaec
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x11EAF8u:  // table[7]
            // 0x0011eaf8
            charge(ctx, 6);
            v0 = 8;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EB10u:  // table[8]
            // 0x0011eb10
            charge(ctx, 6);
            jal(ctx, 0x11EB10u, gen::fn_sub_11F5C0_0011f5c0);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011eb28
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EB34u:  // table[9]
            // 0x0011eb34
            charge(ctx, 6);
            v0 = 10;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EB4Cu:  // table[10]
            // 0x0011eb4c
            charge(ctx, 6);
            jal(ctx, 0x11EB4Cu, gen::fn_sub_11F760_0011f760);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011eb64
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EB70u:  // table[11]
            // 0x0011eb70
            charge(ctx, 6);
            v0 = 12;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EB88u:  // table[12]
            // 0x0011eb88
            charge(ctx, 6);
            jal(ctx, 0x11EB88u, gen::fn_sub_11F900_0011f900);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011eba0
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EBACu:  // table[13]
            // 0x0011ebac
            charge(ctx, 6);
            v0 = 14;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EBC4u:  // table[14]
            // 0x0011ebc4
            charge(ctx, 6);
            jal(ctx, 0x11EBC4u, gen::fn_sub_11FAF0_0011faf0);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011ebdc
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EBE8u:  // table[15]
            // 0x0011ebe8
            charge(ctx, 6);
            v0 = 16;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EC00u:  // table[16]
            // 0x0011ec00
            charge(ctx, 6);
            jal(ctx, 0x11EC00u, gen::fn_sub_11FCA0_0011fca0);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011ec18
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EC24u:  // table[17]
            // 0x0011ec24
            charge(ctx, 6);
            v0 = 18;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EC3Cu:  // table[18]
            // 0x0011ec3c
            charge(ctx, 6);
            jal(ctx, 0x11EC3Cu, gen::fn_sub_11FE50_0011fe50);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011ec54
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EC60u:  // table[19]
            // 0x0011ec60
            charge(ctx, 6);
            v0 = 20;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EC78u:  // table[20]
            // 0x0011ec78
            charge(ctx, 6);
            jal(ctx, 0x11EC78u, gen::fn_sub_11FFD0_0011ffd0);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011ec90
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EC9Cu:  // table[21]
            // 0x0011ec9c
            charge(ctx, 6);
            v0 = 22;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11ECB4u:  // table[22]
            // 0x0011ecb4
            charge(ctx, 6);
            jal(ctx, 0x11ECB4u, gen::fn_sub_120150_00120150);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011eccc
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11ECD8u:  // table[23]
            // 0x0011ecd8
            charge(ctx, 6);
            v0 = 24;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11ECF0u:  // table[24]
            // 0x0011ecf0
            charge(ctx, 6);
            jal(ctx, 0x11ECF0u, gen::fn_sub_1202B0_001202b0);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011ed08
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11ED14u:  // table[25]
            // 0x0011ed14
            charge(ctx, 6);
            v0 = 26;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11ED2Cu:  // table[26]
            // 0x0011ed2c
            charge(ctx, 6);
            jal(ctx, 0x11ED2Cu, gen::fn_sub_120410_00120410);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011ed44
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11ED50u:  // table[29]
            // 0x0011ed50
            charge(ctx, 6);
            v0 = 30;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11ED68u:  // table[30]
            // 0x0011ed68
            charge(ctx, 6);
            jal(ctx, 0x11ED68u, gen::fn_sub_120570_00120570);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011ed80
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11ED8Cu:  // table[27]
            // 0x0011ed8c
            charge(ctx, 6);
            v0 = 28;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EDA4u:  // table[28]
            // 0x0011eda4
            charge(ctx, 6);
            jal(ctx, 0x11EDA4u, gen::fn_sub_1206D0_001206d0);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011edbc
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EDC8u:  // table[31]
            // 0x0011edc8
            charge(ctx, 6);
            v0 = 32;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EDE0u:  // table[32]
            // 0x0011ede0
            charge(ctx, 6);
            jal(ctx, 0x11EDE0u, gen::fn_sub_120830_00120830);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011edf8
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EE04u:  // table[33]
            // 0x0011ee04
            charge(ctx, 6);
            v0 = 34;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EE1Cu:  // table[34]
            // 0x0011ee1c
            charge(ctx, 6);
            jal(ctx, 0x11EE1Cu, gen::fn_sub_120990_00120990);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011ee34
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EE40u:  // table[35]
            // 0x0011ee40
            charge(ctx, 6);
            v0 = 36;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EE58u:  // table[36]
            // 0x0011ee58
            charge(ctx, 6);
            jal(ctx, 0x11EE58u, gen::fn_sub_120B10_00120b10);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011ee70
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EE7Cu:  // table[37]
            // 0x0011ee7c
            charge(ctx, 6);
            v0 = 38;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EE94u:  // table[38]
            // 0x0011ee94
            charge(ctx, 6);
            jal(ctx, 0x11EE94u, gen::fn_sub_120CA0_00120ca0);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011eeac
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EEB8u:  // table[39]
            // 0x0011eeb8
            charge(ctx, 6);
            v0 = 40;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EED0u:  // table[40]
            // 0x0011eed0
            charge(ctx, 6);
            jal(ctx, 0x11EED0u, gen::fn_sub_120E20_00120e20);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011eee8
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EEF4u:  // table[41]
            // 0x0011eef4
            charge(ctx, 6);
            v0 = 42;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EF0Cu:  // table[42]
            // 0x0011ef0c
            charge(ctx, 6);
            jal(ctx, 0x11EF0Cu, gen::fn_sub_121180_00121180);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011ef24
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EF30u:  // table[43]
            // 0x0011ef30
            charge(ctx, 6);
            v0 = 44;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EF48u:  // table[44]
            // 0x0011ef48
            charge(ctx, 6);
            jal(ctx, 0x11EF48u, gen::fn_sub_121480_00121480);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011ef60
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EF6Cu:  // table[45]
            // 0x0011ef6c
            charge(ctx, 6);
            v0 = 46;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EF84u:  // table[46]
            // 0x0011ef84
            charge(ctx, 6);
            jal(ctx, 0x11EF84u, gen::fn_sub_120FD0_00120fd0);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011ef9c
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EFA8u:  // table[47]
            // 0x0011efa8
            charge(ctx, 6);
            v0 = 48;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EFC0u:  // table[48]
            // 0x0011efc0
            charge(ctx, 6);
            jal(ctx, 0x11EFC0u, gen::fn_sub_121300_00121300);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011efd8
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EFE4u:  // table[49]
            // 0x0011efe4
            charge(ctx, 6);
            v0 = 50;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11EFFCu:  // table[50]
            // 0x0011effc
            charge(ctx, 6);
            jal(ctx, 0x11EFFCu, gen::fn_sub_121600_00121600);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011f014
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11F020u:  // table[51]
            // 0x0011f020
            charge(ctx, 6);
            v0 = 52;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11F038u:  // table[52]
            // 0x0011f038
            charge(ctx, 6);
            jal(ctx, 0x11F038u, gen::fn_sub_121780_00121780);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011f050
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11F05Cu:  // table[53]
            // 0x0011f05c
            charge(ctx, 6);
            v0 = 54;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11F074u:  // table[54]
            // 0x0011f074
            charge(ctx, 6);
            jal(ctx, 0x11F074u, gen::fn_sub_121930_00121930);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011f08c
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11F098u:  // table[55]
            // 0x0011f098
            charge(ctx, 6);
            v0 = 56;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11F0B0u:  // table[56]
            // 0x0011f0b0
            charge(ctx, 6);
            jal(ctx, 0x11F0B0u, gen::fn_sub_121AB0_00121ab0);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011f0c8
                charge(ctx, 3);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11F0D4u:  // table[57]
            // 0x0011f0d4
            charge(ctx, 6);
            v0 = 58;
            sw(v0, s0, fl::kState);
            sw(zero, s0, fl::kDone);
            sw(zero, s0, fl::kStep);
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11F0ECu:  // table[58]
            // 0x0011f0ec
            charge(ctx, 6);
            jal(ctx, 0x11F0ECu, gen::fn_sub_121C30_00121c30);
            lw(v1, s0, fl::kStep);
            v0 = 999;
            if (v1 == v0) {
                // 0x0011f104
                charge(ctx, 1);
                sw(zero, s0, fl::kState);
            }
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        case 0x11F108u:  // table[0]: idle
            charge(ctx, 1);  // 0x0011f108
            v0 = 0;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x0011f10c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0011f108 (a state >= 59: the "return 0" block and the epilogue, written out on this path)
    charge(ctx, 1);
    v0 = 0;
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0011F120 sub_11F120 -- 136 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_CampFlash_DestroyTask] Destroy of "h_camp_flash_control": the two files +100 / +104, the work.
void sub_11F120(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0011f120
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, task::kWork);
    s2 = 0;
    for (;;) {
        // 0x0011f16c
        charge(ctx, 3);
        v0 = slti(s2, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0011f144
        charge(ctx, 6);
        v0 = sll(s2, 2);
        v0 = addu(s1, v0);
        s0 = addiu(v0, 100);
        lw(a0, v0, 100);
        if (a0 != 0) {
            // 0x0011f15c
            charge(ctx, 3);
            jal(ctx, 0x11F15Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
            sw(zero, s0, 0);
        }
        // 0x0011f168
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x0011f178
    charge(ctx, 12);
    a0 = s1;
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x11F184u, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0011F1B0 sub_11F1B0 -- 164 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_CreateFlashControlTask] (parent): creates "h_camp_flash_control" (108-byte work, priority 6335, update
// sub_11EA20), +8 = 0 (main list).
void sub_11F1B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0011f1b0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 1;
    a1 = 108;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x11F1D8u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x0011f1f8
        charge(ctx, 13);
        a0 = s1;
        a1 = 0x5E0000;
        a1 = addiu(a1, -21232);  // "h_camp_flash_control"
        a2 = 6335;
        a3 = 0x120000;
        a3 = addiu(a3, -5600);  // &sub_11EA20
        t0 = 0x120000;
        t0 = addiu(t0, -3808);  // &sub_11F120
        t1 = s0;
        jal(ctx, 0x11F21Cu, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x0011f238
            charge(ctx, 1);
            sw(zero, s0, 8);
        } else {
            // 0x0011f22c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0011f1ec
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0011f23c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0011F260 sub_11F260 -- 416 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/main_all/if_c_mai01.anm (the main list): an anm already in slot 0 just draws; else load, start (24
// frames, sound 3), then it replaces slots 0..9.
void sub_11F260(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0011f260
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a1, s0, fl::kStep);
    v1 = 999;
    if (a1 != v1) {
        // 0x0011f288
        charge(ctx, 3);
        v1 = 2;
        if (a1 == v1) {
            // 0x0011f37c
            charge(ctx, 5);
            lw(v1, s0, fl::kTimer);
            v1 = addiu(v1, -1);
            sw(v1, s0, fl::kTimer);
            if (v1 == 0) {
                // 0x0011f390
                charge(ctx, 3);
                s2 = 0;
                for (;;) {
                    // 0x0011f3c4
                    charge(ctx, 3);
                    v1 = slti(s2, 10);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0011f39c
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v1 = addu(s0, v1);
                    s1 = addiu(v1, fl::kAnmSlots);
                    lw(a0, v1, fl::kAnmSlots);
                    if (a0 != 0) {
                        // 0x0011f3b4
                        charge(ctx, 3);
                        jal(ctx, 0x11F3B4u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x0011f3c0
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x0011f3d0
                charge(ctx, 5);
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnmSlots);
                sw(zero, s0, fl::kLoading);
                v1 = 999;
                sw(v1, s0, fl::kStep);
            }
        } else {
            // 0x0011f294
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x0011f310
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x11F314u, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x0011f328
                    charge(ctx, 21);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x11F32Cu, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x11F33Cu, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 1;
                    sw(v0, s0, fl::kDone);
                    v0 = 24;
                    sw(v0, s0, fl::kTimer);
                    v0 = 2;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 3;
                    jal(ctx, 0x11F36Cu, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x0011f2a0
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x0011f2b0
                    charge(ctx, 3);
                    lw(v1, s0, fl::kAnmSlots);
                    if (v1 != 0) {
                        // 0x0011f2e4
                        charge(ctx, 11);
                        v0 = 0x3F800000;
                        mtc1(v0, f12);
                        a0 = v1;
                        jal(ctx, 0x11F2F0u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                        v1 = 1;
                        sw(v1, s0, fl::kDone);
                        v1 = 999;
                        sw(v1, s0, fl::kStep);
                    } else {
                        // 0x0011f2bc
                        charge(ctx, 10);
                        a1 = 6333;
                        a2 = 0x5E0000;
                        a2 = addiu(a2, -21200);  // "camp/main_all/if_c_mai01.anm"
                        jal(ctx, 0x11F2C8u, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                        sw(v0, s0, fl::kLoading);
                        v1 = 1;
                        sw(v1, s0, fl::kStep);
                    }
                } else {
                    // 0x0011f2a8
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x0011f3e4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0011F400 sub_11F400 -- 436 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/status/anm/if_c_sta01.anm into slot 1 (status screen open; 24 frames, sound 3).
void sub_11F400(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0011f400
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a2, s0, fl::kStep);
    v1 = 999;
    if (a2 != v1) {
        // 0x0011f428
        charge(ctx, 3);
        v1 = 4;
        if (a2 == v1) {
            // 0x0011f514
            charge(ctx, 5);
            lw(v1, s0, fl::kTimer);
            v1 = addiu(v1, -1);
            sw(v1, s0, fl::kTimer);
            if (v1 == 0) {
                // 0x0011f528
                charge(ctx, 3);
                lw(a0, s0, fl::kAnmSlots);
                if (a0 != 0) {
                    // 0x0011f534
                    charge(ctx, 3);
                    mtc1(zero, f12);
                    jal(ctx, 0x11F538u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                }
                // 0x0011f540
                charge(ctx, 3);
                s2 = 1;
                for (;;) {
                    // 0x0011f574
                    charge(ctx, 3);
                    v1 = slti(s2, 10);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0011f54c
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v1 = addu(s0, v1);
                    s1 = addiu(v1, fl::kAnmSlots);
                    lw(a0, v1, fl::kAnmSlots);
                    if (a0 != 0) {
                        // 0x0011f564
                        charge(ctx, 3);
                        jal(ctx, 0x11F564u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x0011f570
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x0011f580
                charge(ctx, 6);
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnm1);
                sw(zero, s0, fl::kLoading);
                sw(zero, s0, fl::kLoading2);
                v1 = 999;
                sw(v1, s0, fl::kStep);
            }
        } else {
            // 0x0011f434
            charge(ctx, 3);
            v1 = 3;
            if (a2 == v1) {
                // 0x0011f4a8
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x11F4ACu, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x0011f4c0
                    charge(ctx, 21);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x11F4C4u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x11F4D4u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 1;
                    sw(v0, s0, fl::kDone);
                    v0 = 24;
                    sw(v0, s0, fl::kTimer);
                    v0 = 4;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 3;
                    jal(ctx, 0x11F504u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x0011f440
                charge(ctx, 3);
                a1 = 2;
                if (a2 == a1) {
                    // 0x0011f480
                    charge(ctx, 10);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -21168);  // "camp/status/anm/if_c_sta01.anm"
                    jal(ctx, 0x11F48Cu, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, fl::kLoading);
                    v1 = 3;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x0011f44c
                    charge(ctx, 3);
                    v1 = 1;
                    if (a2 == v1) {
                        // 0x0011f474
                        charge(ctx, 3);
                        sw(a1, s0, fl::kStep);
                    } else {
                        // 0x0011f458
                        charge(ctx, 2);
                        if (a2 == 0) {
                            // 0x0011f468
                            charge(ctx, 3);
                            sw(v1, s0, fl::kStep);
                        } else {
                            // 0x0011f460
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
    }
    // 0x0011f598 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0011F5C0 sub_11F5C0 -- 404 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/status/anm/if_c_sta07.anm into slot 1 (sound 5).
void sub_11F5C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0011f5c0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a1, s0, fl::kStep);
    v1 = 999;
    if (a1 != v1) {
        // 0x0011f5e8
        charge(ctx, 3);
        v1 = 2;
        if (a1 == v1) {
            // 0x0011f6b8
            charge(ctx, 5);
            lw(v1, s0, fl::kTimer);
            v1 = addiu(v1, -1);
            sw(v1, s0, fl::kTimer);
            if (v1 == 0) {
                // 0x0011f6cc
                charge(ctx, 3);
                lw(a0, s0, fl::kAnmSlots);
                if (a0 != 0) {
                    // 0x0011f6d8
                    charge(ctx, 3);
                    mtc1(zero, f12);
                    jal(ctx, 0x11F6DCu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                }
                // 0x0011f6e4
                charge(ctx, 3);
                s2 = 1;
                for (;;) {
                    // 0x0011f718
                    charge(ctx, 3);
                    v1 = slti(s2, 10);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0011f6f0
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v1 = addu(s0, v1);
                    s1 = addiu(v1, fl::kAnmSlots);
                    lw(a0, v1, fl::kAnmSlots);
                    if (a0 != 0) {
                        // 0x0011f708
                        charge(ctx, 3);
                        jal(ctx, 0x11F708u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x0011f714
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x0011f724
                charge(ctx, 5);
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnm1);
                sw(zero, s0, fl::kLoading);
                v1 = 999;
                sw(v1, s0, fl::kStep);
            }
        } else {
            // 0x0011f5f4
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x0011f638
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x11F63Cu, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x0011f650
                    charge(ctx, 26);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x11F654u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x11F664u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 0x3F800000;
                    mtc1(v0, f12);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x11F678u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                    v0 = 1;
                    sw(v0, s0, fl::kDone);
                    v0 = 24;
                    sw(v0, s0, fl::kTimer);
                    v0 = 2;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 5;
                    jal(ctx, 0x11F6A8u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x0011f600
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x0011f610
                    charge(ctx, 10);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -21136);  // "camp/status/anm/if_c_sta07.anm"
                    jal(ctx, 0x11F61Cu, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, fl::kLoading);
                    v1 = 1;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x0011f608
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x0011f738 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0011F760 sub_11F760 -- 404 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/status/anm/if_c_sta09.anm into slot 1.
void sub_11F760(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0011f760
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a1, s0, fl::kStep);
    v1 = 999;
    if (a1 != v1) {
        // 0x0011f788
        charge(ctx, 3);
        v1 = 2;
        if (a1 == v1) {
            // 0x0011f858
            charge(ctx, 5);
            lw(v1, s0, fl::kTimer);
            v1 = addiu(v1, -1);
            sw(v1, s0, fl::kTimer);
            if (v1 == 0) {
                // 0x0011f86c
                charge(ctx, 3);
                lw(a0, s0, fl::kAnmSlots);
                if (a0 != 0) {
                    // 0x0011f878
                    charge(ctx, 3);
                    mtc1(zero, f12);
                    jal(ctx, 0x11F87Cu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                }
                // 0x0011f884
                charge(ctx, 3);
                s2 = 1;
                for (;;) {
                    // 0x0011f8b8
                    charge(ctx, 3);
                    v1 = slti(s2, 10);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0011f890
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v1 = addu(s0, v1);
                    s1 = addiu(v1, fl::kAnmSlots);
                    lw(a0, v1, fl::kAnmSlots);
                    if (a0 != 0) {
                        // 0x0011f8a8
                        charge(ctx, 3);
                        jal(ctx, 0x11F8A8u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x0011f8b4
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x0011f8c4
                charge(ctx, 5);
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnm1);
                sw(zero, s0, fl::kLoading);
                v1 = 999;
                sw(v1, s0, fl::kStep);
            }
        } else {
            // 0x0011f794
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x0011f7d8
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x11F7DCu, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x0011f7f0
                    charge(ctx, 26);
                    v0 = 0x3F800000;
                    mtc1(v0, f12);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x11F7FCu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x11F808u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x11F818u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 1;
                    sw(v0, s0, fl::kDone);
                    v0 = 24;
                    sw(v0, s0, fl::kTimer);
                    v0 = 2;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 5;
                    jal(ctx, 0x11F848u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x0011f7a0
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x0011f7b0
                    charge(ctx, 10);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -21104);  // "camp/status/anm/if_c_sta09.anm"
                    jal(ctx, 0x11F7BCu, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, fl::kLoading);
                    v1 = 1;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x0011f7a8
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x0011f8d8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0011F900 sub_11F900 -- 488 bytes; frame 0x60: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// Closes a screen: moves the flash task before slot 0 (kwlnTaskMoveBefore), 10 frames drawing slots 1..9, then
// destroys them (sound 4).
void sub_11F900(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x0011f900
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a1, s0, fl::kStep);
    v1 = 999;
    if (a1 != v1) {
        // 0x0011f930
        charge(ctx, 3);
        a0 = 2;
        if (a1 == a0) {
            // 0x0011f9a4
            charge(ctx, 6);
            s1 = 0;
            lw(v0, s0, fl::kTimer);
            v0 = addiu(v0, -1);
            sw(v0, s0, fl::kTimer);
            if (v0 != 0) {
                // 0x0011fa4c
                charge(ctx, 13);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                v0 = 0x41200000;
                mtc1(v0, f1);
                sub_s(f0, f1, f0);
                div_s(f20, f0, f1);
                s1 = 1;
                for (;;) {
                    // 0x0011faa8
                    charge(ctx, 3);
                    v0 = slti(s1, 10);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0011fa80
                    charge(ctx, 5);
                    v0 = sll(s1, 2);
                    v0 = addu(s0, v0);
                    lw(a0, v0, 20);
                    if (a0 != 0) {
                        // 0x0011fa94
                        charge(ctx, 4);
                        v0 = 0x3F800000;
                        mtc1(v0, f12);
                        jal(ctx, 0x11FA9Cu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                    }
                    // 0x0011faa4
                    charge(ctx, 1);
                    s1 = addiu(s1, 1);
                }
                // 0x0011fab4
                charge(ctx, 4);
                lw(a0, s0, fl::kAnmSlots);
                mov_s(f12, f20);
                jal(ctx, 0x11FABCu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
            } else {
                // 0x0011f9bc
                charge(ctx, 3);
                s2 = 1;
                for (;;) {
                    // 0x0011fa14
                    charge(ctx, 3);
                    v0 = slti(s2, 10);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0011f9c8
                    charge(ctx, 5);
                    v0 = sll(s2, 2);
                    v0 = addu(s0, v0);
                    lw(a0, v0, 20);
                    if (a0 != 0) {
                        // 0x0011f9dc
                        charge(ctx, 2);
                        if (s1 == 0) {
                            // 0x0011f9e4
                            charge(ctx, 3);
                            lw(a1, s0, fl::kAnmSlots);
                            jal(ctx, 0x11F9E8u, gen::fn_kwlnTaskMoveAfter_001957b0);
                        }
                        // 0x0011f9f0
                        charge(ctx, 8);
                        s1 = 1;
                        v0 = sll(s2, 2);
                        v0 = addu(s0, v0);
                        s3 = addiu(v0, 20);
                        lw(a0, v0, 20);
                        jal(ctx, 0x11FA04u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s3, 0);
                    }
                    // 0x0011fa10
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x0011fa20
                charge(ctx, 11);
                sw(zero, s0, fl::kLoading);
                sw(zero, s0, fl::kLoading2);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                lw(a0, s0, fl::kAnmSlots);
                jal(ctx, 0x11FA34u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                v1 = 999;
                sw(v1, s0, fl::kStep);
            }
        } else {
            // 0x0011f93c
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x0011f964
                charge(ctx, 16);
                sw(v1, s0, fl::kDone);
                v0 = 10;
                sw(v0, s0, fl::kTimer);
                sw(a0, s0, fl::kStep);
                lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
                lw(a1, s0, fl::kAnmSlots);
                jal(ctx, 0x11F97Cu, gen::fn_kwlnTaskMoveBefore_001958a0);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 4;
                jal(ctx, 0x11F994u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
            } else {
                // 0x0011f948
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x0011f958
                    charge(ctx, 3);
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x0011f950
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x0011fac4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0011FAF0 sub_11FAF0 -- 432 bytes; frame 0x50: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// Closes a screen over 20 frames, then destroys slots 1..9 (sound 4).
void sub_11FAF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0011faf0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a1, s0, fl::kStep);
    v1 = 999;
    if (a1 != v1) {
        // 0x0011fb20
        charge(ctx, 3);
        a0 = 2;
        if (a1 == a0) {
            // 0x0011fb80
            charge(ctx, 6);
            lw(v0, s0, fl::kTimer);
            v1 = addiu(v0, 1);
            sw(v1, s0, fl::kTimer);
            v0 = 20;
            if (v1 != v0) {
                // 0x0011fc00
                charge(ctx, 15);
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                v0 = 0x41A00000;
                mtc1(v0, f1);
                sub_s(f0, f1, f0);
                div_s(f20, f0, f1);
                s1 = 1;
                v0 = 0x3F800000;
                mtc1(v0, f0);
                sub_s(f21, f0, f20);
                for (;;) {
                    // 0x0011fc60
                    charge(ctx, 3);
                    v0 = slti(s1, 10);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0011fc3c
                    charge(ctx, 5);
                    v0 = sll(s1, 2);
                    v0 = addu(s0, v0);
                    lw(a0, v0, 20);
                    if (a0 != 0) {
                        // 0x0011fc50
                        charge(ctx, 3);
                        mov_s(f12, f21);
                        jal(ctx, 0x11FC54u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                    }
                    // 0x0011fc5c
                    charge(ctx, 1);
                    s1 = addiu(s1, 1);
                }
                // 0x0011fc6c
                charge(ctx, 4);
                lw(a0, s0, fl::kAnmSlots);
                mov_s(f12, f20);
                jal(ctx, 0x11FC74u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
            } else {
                // 0x0011fb98
                charge(ctx, 3);
                s2 = 1;
                for (;;) {
                    // 0x0011fbcc
                    charge(ctx, 3);
                    v0 = slti(s2, 10);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0011fba4
                    charge(ctx, 6);
                    v0 = sll(s2, 2);
                    v0 = addu(s0, v0);
                    s1 = addiu(v0, 20);
                    lw(a0, v0, 20);
                    if (a0 != 0) {
                        // 0x0011fbbc
                        charge(ctx, 3);
                        jal(ctx, 0x11FBBCu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x0011fbc8
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x0011fbd8
                charge(ctx, 10);
                sw(zero, s0, fl::kLoading);
                sw(zero, s0, fl::kLoading2);
                mtc1(zero, f12);
                lw(a0, s0, fl::kAnmSlots);
                jal(ctx, 0x11FBE8u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                v1 = 999;
                sw(v1, s0, fl::kStep);
            }
        } else {
            // 0x0011fb2c
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x0011fb54
                charge(ctx, 11);
                sw(v1, s0, fl::kDone);
                sw(zero, s0, fl::kTimer);
                sw(a0, s0, fl::kStep);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 4;
                jal(ctx, 0x11FB70u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
            } else {
                // 0x0011fb38
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x0011fb48
                    charge(ctx, 3);
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x0011fb40
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x0011fc7c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0011FCA0 sub_11FCA0 -- 432 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/item/anm/i_c_ite01.anm into slot 1 until it ends (item screen open; sound 3).
void sub_11FCA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0011fca0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a2, s0, fl::kStep);
    v1 = 999;
    if (a2 != v1) {
        // 0x0011fcc8
        charge(ctx, 3);
        v1 = 4;
        if (a2 == v1) {
            // 0x0011fdb4
            charge(ctx, 5);
            lw(a0, s0, fl::kLoading);
            jal(ctx, 0x11FDB8u, gen::fn_sub_111CB0_00111cb0);  // non-zero when the .anm ended
            if (v0 != 0) {
                // 0x0011fdc8
                charge(ctx, 3);
                lw(a0, s0, fl::kAnmSlots);
                if (a0 != 0) {
                    // 0x0011fdd4
                    charge(ctx, 3);
                    mtc1(zero, f12);
                    jal(ctx, 0x11FDD8u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                }
                // 0x0011fde0
                charge(ctx, 3);
                s2 = 1;
                for (;;) {
                    // 0x0011fe14
                    charge(ctx, 3);
                    v1 = slti(s2, 10);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0011fdec
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v1 = addu(s0, v1);
                    s1 = addiu(v1, fl::kAnmSlots);
                    lw(a0, v1, fl::kAnmSlots);
                    if (a0 != 0) {
                        // 0x0011fe04
                        charge(ctx, 3);
                        jal(ctx, 0x11FE04u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x0011fe10
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x0011fe20
                charge(ctx, 5);
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnm1);
                sw(zero, s0, fl::kLoading);
                v1 = 999;
                sw(v1, s0, fl::kStep);
            }
        } else {
            // 0x0011fcd4
            charge(ctx, 3);
            v1 = 3;
            if (a2 == v1) {
                // 0x0011fd48
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x11FD4Cu, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x0011fd60
                    charge(ctx, 21);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x11FD64u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x11FD74u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 1;
                    sw(v0, s0, fl::kDone);
                    v0 = 24;
                    sw(v0, s0, fl::kTimer);
                    v0 = 4;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 3;
                    jal(ctx, 0x11FDA4u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x0011fce0
                charge(ctx, 3);
                a1 = 2;
                if (a2 == a1) {
                    // 0x0011fd20
                    charge(ctx, 10);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -21072);  // "camp/item/anm/i_c_ite01.anm"
                    jal(ctx, 0x11FD2Cu, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, fl::kLoading);
                    v1 = 3;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x0011fcec
                    charge(ctx, 3);
                    v1 = 1;
                    if (a2 == v1) {
                        // 0x0011fd14
                        charge(ctx, 3);
                        sw(a1, s0, fl::kStep);
                    } else {
                        // 0x0011fcf8
                        charge(ctx, 2);
                        if (a2 == 0) {
                            // 0x0011fd08
                            charge(ctx, 3);
                            sw(v1, s0, fl::kStep);
                        } else {
                            // 0x0011fd00
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
    }
    // 0x0011fe34 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0011FE50 sub_11FE50 -- 376 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/item/anm/i_c_ite02.anm into slot 2 (sound 5).
void sub_11FE50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0011fe50
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a1, s0, fl::kStep);
    v1 = 999;
    if (a1 != v1) {
        // 0x0011fe78
        charge(ctx, 3);
        v1 = 2;
        if (a1 == v1) {
            // 0x0011ff24
            charge(ctx, 5);
            lw(a0, s0, fl::kLoading);
            jal(ctx, 0x11FF28u, gen::fn_sub_111CB0_00111cb0);  // non-zero when the .anm ended
            if (v0 != 0) {
                // 0x0011ff38
                charge(ctx, 3);
                lw(a0, s0, fl::kAnm1);
                if (a0 != 0) {
                    // 0x0011ff44
                    charge(ctx, 3);
                    mtc1(zero, f12);
                    jal(ctx, 0x11FF48u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                }
                // 0x0011ff50
                charge(ctx, 3);
                s2 = 2;
                for (;;) {
                    // 0x0011ff84
                    charge(ctx, 3);
                    v1 = slti(s2, 10);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0011ff5c
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v1 = addu(s0, v1);
                    s1 = addiu(v1, fl::kAnmSlots);
                    lw(a0, v1, fl::kAnmSlots);
                    if (a0 != 0) {
                        // 0x0011ff74
                        charge(ctx, 3);
                        jal(ctx, 0x11FF74u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x0011ff80
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x0011ff90
                charge(ctx, 7);
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnm2);
                sw(zero, s0, fl::kLoading);
                v1 = 999;
                sw(v1, s0, fl::kStep);
                v1 = 1;
                sw(v1, s0, fl::kDone);
            }
        } else {
            // 0x0011fe84
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x0011fec8
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x11FECCu, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x0011fee0
                    charge(ctx, 17);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x11FEE4u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x11FEF4u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 2;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 5;
                    jal(ctx, 0x11FF14u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x0011fe90
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x0011fea0
                    charge(ctx, 10);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -21040);  // "camp/item/anm/i_c_ite02.anm"
                    jal(ctx, 0x11FEACu, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, fl::kLoading);
                    v1 = 1;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x0011fe98
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x0011ffac (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0011FFD0 sub_11FFD0 -- 376 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Four frames of slots 1 and 2, then destroys slot 2 (item sub-window close).
void sub_11FFD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0011ffd0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a0, s0, fl::kStep);
    v1 = 999;
    if (a0 != v1) {
        // 0x0011fff0
        charge(ctx, 3);
        v1 = 4;
        if (a0 != v1) {
            // 0x0011fffc
            charge(ctx, 3);
            v1 = 3;
            if (a0 != v1) {
                // 0x00120008
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    // 0x00120098
                    charge(ctx, 11);
                    v0 = 0x3F800000;
                    mtc1(v0, f12);
                    lw(a0, s0, fl::kAnm1);
                    jal(ctx, 0x1200A4u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                    lw(a0, s0, fl::kAnm2);
                    lwc1(f12, gp, -32632);  // 0x7CAD78
                    jal(ctx, 0x1200B4u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                    v0 = 3;
                    sw(v0, s0, fl::kStep);
                    goto L_001200c4;
                }
                // 0x00120014
                charge(ctx, 3);
                v1 = 1;
                if (a0 == v1) {
                    // 0x00120064
                    charge(ctx, 13);
                    v0 = 0x3F800000;
                    mtc1(v0, f12);
                    lw(a0, s0, fl::kAnm1);
                    jal(ctx, 0x120070u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                    lw(a0, s0, fl::kAnm2);
                    lwc1(f12, gp, -32572);  // 0x7CADB4
                    jal(ctx, 0x120080u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                    v1 = 2;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x00120020
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x00120030
                        charge(ctx, 13);
                        v0 = 0x3F800000;
                        mtc1(v0, f12);
                        lw(a0, s0, fl::kAnm1);
                        jal(ctx, 0x12003Cu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                        lw(a0, s0, fl::kAnm2);
                        lwc1(f12, gp, -31844);  // 0x7CB08C
                        jal(ctx, 0x12004Cu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                        v1 = 1;
                        sw(v1, s0, fl::kStep);
                    } else {
                        // 0x00120028
                        charge(ctx, 2);
                    }
                }
                // 0x00120134 (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(ra, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x20);
                return;
            }
        L_001200c4:
            charge(ctx, 11);
            v0 = 0x3F800000;
            mtc1(v0, f12);
            lw(a0, s0, fl::kAnm1);
            jal(ctx, 0x1200D0u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
            lw(a0, s0, fl::kAnm2);
            lwc1(f12, gp, -32004);  // 0x7CAFEC
            jal(ctx, 0x1200E0u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
            v0 = 4;
            sw(v0, s0, fl::kStep);
        }
        // 0x001200f0
        charge(ctx, 17);
        v0 = 0x3F800000;
        mtc1(v0, f12);
        lw(a0, s0, fl::kAnm1);
        jal(ctx, 0x1200FCu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
        mtc1(zero, f12);
        lw(a0, s0, fl::kAnm2);
        jal(ctx, 0x12010Cu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
        lw(a0, s0, fl::kAnm2);
        jal(ctx, 0x120118u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
        sw(zero, s0, fl::kAnm2);
        v1 = 1;
        sw(v1, s0, fl::kDone);
        v1 = 999;
        sw(v1, s0, fl::kStep);
    }
    // 0x00120134 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00120150 sub_120150 -- 348 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/item/anm/i_c_ite03.anm.
void sub_120150(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00120150
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a1, s0, fl::kStep);
    v1 = 999;
    if (a1 != v1) {
        // 0x00120178
        charge(ctx, 3);
        v1 = 2;
        if (a1 == v1) {
            // 0x00120228
            charge(ctx, 5);
            lw(a0, s0, fl::kLoading);
            jal(ctx, 0x12022Cu, gen::fn_sub_111CB0_00111cb0);  // non-zero when the .anm ended
            if (v0 != 0) {
                // 0x0012023c
                charge(ctx, 3);
                s2 = 1;
                for (;;) {
                    // 0x00120270
                    charge(ctx, 3);
                    v1 = slti(s2, 10);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00120248
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v1 = addu(s0, v1);
                    s1 = addiu(v1, fl::kAnmSlots);
                    lw(a0, v1, fl::kAnmSlots);
                    if (a0 != 0) {
                        // 0x00120260
                        charge(ctx, 3);
                        jal(ctx, 0x120260u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x0012026c
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x0012027c
                charge(ctx, 5);
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnm1);
                sw(zero, s0, fl::kLoading);
                v1 = 999;
                sw(v1, s0, fl::kStep);
            }
        } else {
            // 0x00120184
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x001201c8
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x1201CCu, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x001201e0
                    charge(ctx, 18);
                    sw(v1, s0, fl::kDone);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x1201E8u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x1201F8u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 2;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 5;
                    jal(ctx, 0x120218u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x00120190
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x001201a0
                    charge(ctx, 10);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -21008);  // "camp/item/anm/i_c_ite03.anm"
                    jal(ctx, 0x1201ACu, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, fl::kLoading);
                    v1 = 1;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x00120198
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x00120290 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001202B0 sub_1202B0 -- 352 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/item/anm/i_c_ite08.anm.
void sub_1202B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001202b0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a1, s0, fl::kStep);
    v1 = 999;
    if (a1 != v1) {
        // 0x001202d8
        charge(ctx, 3);
        v1 = 2;
        if (a1 == v1) {
            // 0x0012038c
            charge(ctx, 5);
            lw(a0, s0, fl::kLoading);
            jal(ctx, 0x120390u, gen::fn_sub_111CB0_00111cb0);  // non-zero when the .anm ended
            if (v0 != 0) {
                // 0x001203a0
                charge(ctx, 3);
                s2 = 1;
                for (;;) {
                    // 0x001203d4
                    charge(ctx, 3);
                    v1 = slti(s2, 10);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001203ac
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v1 = addu(s0, v1);
                    s1 = addiu(v1, fl::kAnmSlots);
                    lw(a0, v1, fl::kAnmSlots);
                    if (a0 != 0) {
                        // 0x001203c4
                        charge(ctx, 3);
                        jal(ctx, 0x1203C4u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x001203d0
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x001203e0
                charge(ctx, 5);
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnm1);
                sw(zero, s0, fl::kLoading);
                v1 = 999;
                sw(v1, s0, fl::kStep);
            }
        } else {
            // 0x001202e4
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x00120328
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x12032Cu, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x00120340
                    charge(ctx, 19);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x120344u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x120354u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 1;
                    sw(v0, s0, fl::kDone);
                    v0 = 2;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 5;
                    jal(ctx, 0x12037Cu, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x001202f0
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x00120300
                    charge(ctx, 10);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -20976);  // "camp/item/anm/i_c_ite08.anm"
                    jal(ctx, 0x12030Cu, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, fl::kLoading);
                    v1 = 1;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x001202f8
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x001203f4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00120410 sub_120410 -- 348 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/item/anm/i_c_ite06.anm.
void sub_120410(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00120410
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a1, s0, fl::kStep);
    v1 = 999;
    if (a1 != v1) {
        // 0x00120438
        charge(ctx, 3);
        v1 = 2;
        if (a1 == v1) {
            // 0x001204e8
            charge(ctx, 5);
            lw(a0, s0, fl::kLoading);
            jal(ctx, 0x1204ECu, gen::fn_sub_111CB0_00111cb0);  // non-zero when the .anm ended
            if (v0 != 0) {
                // 0x001204fc
                charge(ctx, 3);
                s2 = 1;
                for (;;) {
                    // 0x00120530
                    charge(ctx, 3);
                    v1 = slti(s2, 10);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00120508
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v1 = addu(s0, v1);
                    s1 = addiu(v1, fl::kAnmSlots);
                    lw(a0, v1, fl::kAnmSlots);
                    if (a0 != 0) {
                        // 0x00120520
                        charge(ctx, 3);
                        jal(ctx, 0x120520u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x0012052c
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x0012053c
                charge(ctx, 5);
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnm1);
                sw(zero, s0, fl::kLoading);
                v1 = 999;
                sw(v1, s0, fl::kStep);
            }
        } else {
            // 0x00120444
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x00120488
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x12048Cu, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x001204a0
                    charge(ctx, 18);
                    sw(v1, s0, fl::kDone);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x1204A8u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x1204B8u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 2;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 5;
                    jal(ctx, 0x1204D8u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x00120450
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x00120460
                    charge(ctx, 10);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -20944);  // "camp/item/anm/i_c_ite06.anm"
                    jal(ctx, 0x12046Cu, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, fl::kLoading);
                    v1 = 1;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x00120458
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x00120550 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00120570 sub_120570 -- 348 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/item/anm/i_c_ite05.anm.
void sub_120570(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00120570
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a1, s0, fl::kStep);
    v1 = 999;
    if (a1 != v1) {
        // 0x00120598
        charge(ctx, 3);
        v1 = 2;
        if (a1 == v1) {
            // 0x00120648
            charge(ctx, 5);
            lw(a0, s0, fl::kLoading);
            jal(ctx, 0x12064Cu, gen::fn_sub_111CB0_00111cb0);  // non-zero when the .anm ended
            if (v0 != 0) {
                // 0x0012065c
                charge(ctx, 3);
                s2 = 1;
                for (;;) {
                    // 0x00120690
                    charge(ctx, 3);
                    v1 = slti(s2, 10);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00120668
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v1 = addu(s0, v1);
                    s1 = addiu(v1, fl::kAnmSlots);
                    lw(a0, v1, fl::kAnmSlots);
                    if (a0 != 0) {
                        // 0x00120680
                        charge(ctx, 3);
                        jal(ctx, 0x120680u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x0012068c
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x0012069c
                charge(ctx, 5);
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnm1);
                sw(zero, s0, fl::kLoading);
                v1 = 999;
                sw(v1, s0, fl::kStep);
            }
        } else {
            // 0x001205a4
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x001205e8
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x1205ECu, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x00120600
                    charge(ctx, 18);
                    sw(v1, s0, fl::kDone);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x120608u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x120618u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 2;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 5;
                    jal(ctx, 0x120638u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x001205b0
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x001205c0
                    charge(ctx, 10);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -20912);  // "camp/item/anm/i_c_ite05.anm"
                    jal(ctx, 0x1205CCu, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, fl::kLoading);
                    v1 = 1;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x001205b8
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x001206b0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001206D0 sub_1206D0 -- 348 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/item/anm/i_c_ite04.anm.
void sub_1206D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001206d0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a1, s0, fl::kStep);
    v1 = 999;
    if (a1 != v1) {
        // 0x001206f8
        charge(ctx, 3);
        v1 = 2;
        if (a1 == v1) {
            // 0x001207a8
            charge(ctx, 5);
            lw(a0, s0, fl::kLoading);
            jal(ctx, 0x1207ACu, gen::fn_sub_111CB0_00111cb0);  // non-zero when the .anm ended
            if (v0 != 0) {
                // 0x001207bc
                charge(ctx, 3);
                s2 = 1;
                for (;;) {
                    // 0x001207f0
                    charge(ctx, 3);
                    v1 = slti(s2, 10);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001207c8
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v1 = addu(s0, v1);
                    s1 = addiu(v1, fl::kAnmSlots);
                    lw(a0, v1, fl::kAnmSlots);
                    if (a0 != 0) {
                        // 0x001207e0
                        charge(ctx, 3);
                        jal(ctx, 0x1207E0u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x001207ec
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x001207fc
                charge(ctx, 5);
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnm1);
                sw(zero, s0, fl::kLoading);
                v1 = 999;
                sw(v1, s0, fl::kStep);
            }
        } else {
            // 0x00120704
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x00120748
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x12074Cu, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x00120760
                    charge(ctx, 18);
                    sw(v1, s0, fl::kDone);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x120768u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x120778u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 2;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 5;
                    jal(ctx, 0x120798u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x00120710
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x00120720
                    charge(ctx, 10);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -20880);  // "camp/item/anm/i_c_ite04.anm"
                    jal(ctx, 0x12072Cu, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, fl::kLoading);
                    v1 = 1;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x00120718
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x00120810 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00120830 sub_120830 -- 348 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/item/anm/i_c_ite07.anm.
void sub_120830(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00120830
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a1, s0, fl::kStep);
    v1 = 999;
    if (a1 != v1) {
        // 0x00120858
        charge(ctx, 3);
        v1 = 2;
        if (a1 == v1) {
            // 0x00120908
            charge(ctx, 5);
            lw(a0, s0, fl::kLoading);
            jal(ctx, 0x12090Cu, gen::fn_sub_111CB0_00111cb0);  // non-zero when the .anm ended
            if (v0 != 0) {
                // 0x0012091c
                charge(ctx, 3);
                s2 = 1;
                for (;;) {
                    // 0x00120950
                    charge(ctx, 3);
                    v1 = slti(s2, 10);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00120928
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v1 = addu(s0, v1);
                    s1 = addiu(v1, fl::kAnmSlots);
                    lw(a0, v1, fl::kAnmSlots);
                    if (a0 != 0) {
                        // 0x00120940
                        charge(ctx, 3);
                        jal(ctx, 0x120940u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x0012094c
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x0012095c
                charge(ctx, 5);
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnm1);
                sw(zero, s0, fl::kLoading);
                v1 = 999;
                sw(v1, s0, fl::kStep);
            }
        } else {
            // 0x00120864
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x001208a8
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x1208ACu, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x001208c0
                    charge(ctx, 18);
                    sw(v1, s0, fl::kDone);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x1208C8u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x1208D8u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 2;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 5;
                    jal(ctx, 0x1208F8u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x00120870
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x00120880
                    charge(ctx, 10);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -20848);  // "camp/item/anm/i_c_ite07.anm"
                    jal(ctx, 0x12088Cu, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, fl::kLoading);
                    v1 = 1;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x00120878
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x00120970 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00120990 sub_120990 -- 376 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/commu/anm/i_c_com01.anm (social-link screen open).
void sub_120990(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00120990
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a1, s0, fl::kStep);
    v1 = 999;
    if (a1 != v1) {
        // 0x001209b8
        charge(ctx, 3);
        v1 = 2;
        if (a1 == v1) {
            // 0x00120a6c
            charge(ctx, 5);
            lw(a0, s0, fl::kLoading);
            jal(ctx, 0x120A70u, gen::fn_sub_111CB0_00111cb0);  // non-zero when the .anm ended
            if (v0 != 0) {
                // 0x00120a80
                charge(ctx, 3);
                lw(a0, s0, fl::kAnmSlots);
                if (a0 != 0) {
                    // 0x00120a8c
                    charge(ctx, 3);
                    mtc1(zero, f12);
                    jal(ctx, 0x120A90u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                }
                // 0x00120a98
                charge(ctx, 3);
                s2 = 1;
                for (;;) {
                    // 0x00120acc
                    charge(ctx, 3);
                    v1 = slti(s2, 10);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00120aa4
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v1 = addu(s0, v1);
                    s1 = addiu(v1, fl::kAnmSlots);
                    lw(a0, v1, fl::kAnmSlots);
                    if (a0 != 0) {
                        // 0x00120abc
                        charge(ctx, 3);
                        jal(ctx, 0x120ABCu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x00120ac8
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x00120ad8
                charge(ctx, 5);
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnm1);
                sw(zero, s0, fl::kLoading);
                v1 = 999;
                sw(v1, s0, fl::kStep);
            }
        } else {
            // 0x001209c4
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x00120a08
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x120A0Cu, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x00120a20
                    charge(ctx, 19);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x120A24u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x120A34u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 1;
                    sw(v0, s0, fl::kDone);
                    v0 = 2;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 3;
                    jal(ctx, 0x120A5Cu, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x001209d0
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x001209e0
                    charge(ctx, 10);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -20816);  // "camp/commu/anm/i_c_com01.anm"
                    jal(ctx, 0x1209ECu, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, fl::kLoading);
                    v1 = 1;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x001209d8
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x00120aec (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00120B10 sub_120B10 -- 392 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/commu/anm/i_c_com02.anm.
void sub_120B10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00120b10
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a1, s0, fl::kStep);
    v1 = 999;
    if (a1 != v1) {
        // 0x00120b38
        charge(ctx, 3);
        v1 = 2;
        if (a1 == v1) {
            // 0x00120bec
            charge(ctx, 5);
            lw(a0, s0, fl::kLoading);
            jal(ctx, 0x120BF0u, gen::fn_sub_111CB0_00111cb0);  // non-zero when the .anm ended
            if (v0 != 0) {
                // 0x00120c00
                charge(ctx, 3);
                lw(a0, s0, fl::kAnmSlots);
                if (a0 != 0) {
                    // 0x00120c0c
                    charge(ctx, 3);
                    mtc1(zero, f12);
                    jal(ctx, 0x120C10u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                }
                // 0x00120c18
                charge(ctx, 3);
                s2 = 2;
                for (;;) {
                    // 0x00120c4c
                    charge(ctx, 3);
                    v0 = slti(s2, 10);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00120c24
                    charge(ctx, 6);
                    v0 = sll(s2, 2);
                    v0 = addu(s0, v0);
                    s1 = addiu(v0, 20);
                    lw(a0, v0, 20);
                    if (a0 != 0) {
                        // 0x00120c3c
                        charge(ctx, 3);
                        jal(ctx, 0x120C3Cu, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x00120c48
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x00120c58
                charge(ctx, 9);
                mtc1(zero, f12);
                lw(a0, s0, fl::kAnm1);
                jal(ctx, 0x120C60u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnm2);
                sw(zero, s0, fl::kLoading);
                v1 = 999;
                sw(v1, s0, fl::kStep);
            }
        } else {
            // 0x00120b44
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x00120b88
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x120B8Cu, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x00120ba0
                    charge(ctx, 19);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x120BA4u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x120BB4u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 1;
                    sw(v0, s0, fl::kDone);
                    v0 = 2;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 3;
                    jal(ctx, 0x120BDCu, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x00120b50
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x00120b60
                    charge(ctx, 10);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -20784);  // "camp/commu/anm/i_c_com02.anm"
                    jal(ctx, 0x120B6Cu, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, fl::kLoading);
                    v1 = 1;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x00120b58
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x00120c7c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00120CA0 sub_120CA0 -- 372 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Five frames of slot 1 with slot 2 moved before it, then destroys slots 2..9 (sound 4).
void sub_120CA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x00120ca0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a1, s0, fl::kStep);
    v1 = 999;
    if (a1 != v1) {
        // 0x00120cc8
        charge(ctx, 3);
        a0 = 2;
        if (a1 == a0) {
            // 0x00120d34
            charge(ctx, 6);
            lw(v0, s0, fl::kTimer);
            v1 = addiu(v0, 1);
            sw(v1, s0, fl::kTimer);
            v0 = 5;
            if (v1 != v0) {
                // 0x00120dc8
                charge(ctx, 12);
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                v0 = 0x40A00000;
                mtc1(v0, f0);
                div_s(f12, f1, f0);
                lw(a0, s0, fl::kAnm1);
                jal(ctx, 0x120DF0u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
            } else {
                // 0x00120d4c
                charge(ctx, 7);
                lw(a0, s0, fl::kAnm2);
                lw(a1, s0, fl::kAnm1);
                jal(ctx, 0x120D54u, gen::fn_kwlnTaskMoveBefore_001958a0);
                s2 = 2;
                for (;;) {
                    // 0x00120d90
                    charge(ctx, 3);
                    v0 = slti(s2, 10);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00120d68
                    charge(ctx, 6);
                    v0 = sll(s2, 2);
                    v0 = addu(s0, v0);
                    s1 = addiu(v0, 20);
                    lw(a0, v0, 20);
                    if (a0 != 0) {
                        // 0x00120d80
                        charge(ctx, 3);
                        jal(ctx, 0x120D80u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x00120d8c
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x00120d9c
                charge(ctx, 11);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                lw(a0, s0, fl::kAnm1);
                jal(ctx, 0x120DA8u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                v1 = 1;
                sw(v1, s0, fl::kDone);
                v1 = 999;
                sw(v1, s0, fl::kStep);
            }
        } else {
            // 0x00120cd4
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x00120cfc
                charge(ctx, 14);
                sw(zero, s0, fl::kTimer);
                sw(a0, s0, fl::kStep);
                lw(a0, gp, g::kCampFlashTask);  // 0x7CDF50
                lw(a1, s0, fl::kAnm1);
                jal(ctx, 0x120D0Cu, gen::fn_kwlnTaskMoveBefore_001958a0);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 4;
                jal(ctx, 0x120D24u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
            } else {
                // 0x00120ce0
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x00120cf0
                    charge(ctx, 3);
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x00120ce8
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x00120df8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00120E20 sub_120E20 -- 432 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/skill/anm/if_c_skl01.anm (skill screen open).
void sub_120E20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00120e20
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a2, s0, fl::kStep);
    v1 = 999;
    if (a2 != v1) {
        // 0x00120e48
        charge(ctx, 3);
        v1 = 4;
        if (a2 == v1) {
            // 0x00120f34
            charge(ctx, 5);
            lw(a0, s0, fl::kLoading);
            jal(ctx, 0x120F38u, gen::fn_sub_111CB0_00111cb0);  // non-zero when the .anm ended
            if (v0 != 0) {
                // 0x00120f48
                charge(ctx, 3);
                lw(a0, s0, fl::kAnmSlots);
                if (a0 != 0) {
                    // 0x00120f54
                    charge(ctx, 3);
                    mtc1(zero, f12);
                    jal(ctx, 0x120F58u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                }
                // 0x00120f60
                charge(ctx, 3);
                s2 = 1;
                for (;;) {
                    // 0x00120f94
                    charge(ctx, 3);
                    v1 = slti(s2, 10);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00120f6c
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v1 = addu(s0, v1);
                    s1 = addiu(v1, fl::kAnmSlots);
                    lw(a0, v1, fl::kAnmSlots);
                    if (a0 != 0) {
                        // 0x00120f84
                        charge(ctx, 3);
                        jal(ctx, 0x120F84u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x00120f90
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x00120fa0
                charge(ctx, 5);
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnm1);
                sw(zero, s0, fl::kLoading);
                v1 = 999;
                sw(v1, s0, fl::kStep);
            }
        } else {
            // 0x00120e54
            charge(ctx, 3);
            v1 = 3;
            if (a2 == v1) {
                // 0x00120ec8
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x120ECCu, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x00120ee0
                    charge(ctx, 21);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x120EE4u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x120EF4u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 1;
                    sw(v0, s0, fl::kDone);
                    v0 = 24;
                    sw(v0, s0, fl::kTimer);
                    v0 = 4;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 3;
                    jal(ctx, 0x120F24u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x00120e60
                charge(ctx, 3);
                a1 = 2;
                if (a2 == a1) {
                    // 0x00120ea0
                    charge(ctx, 10);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -20752);  // "camp/skill/anm/if_c_skl01.anm"
                    jal(ctx, 0x120EACu, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, fl::kLoading);
                    v1 = 3;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x00120e6c
                    charge(ctx, 3);
                    v1 = 1;
                    if (a2 == v1) {
                        // 0x00120e94
                        charge(ctx, 3);
                        sw(a1, s0, fl::kStep);
                    } else {
                        // 0x00120e78
                        charge(ctx, 2);
                        if (a2 == 0) {
                            // 0x00120e88
                            charge(ctx, 3);
                            sw(v1, s0, fl::kStep);
                        } else {
                            // 0x00120e80
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
    }
    // 0x00120fb4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00120FD0 sub_120FD0 -- 432 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/EQUIP/anm/if_c_equ01.anm (equipment screen open).
void sub_120FD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00120fd0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a2, s0, fl::kStep);
    v1 = 999;
    if (a2 != v1) {
        // 0x00120ff8
        charge(ctx, 3);
        v1 = 4;
        if (a2 == v1) {
            // 0x001210e4
            charge(ctx, 5);
            lw(a0, s0, fl::kLoading);
            jal(ctx, 0x1210E8u, gen::fn_sub_111CB0_00111cb0);  // non-zero when the .anm ended
            if (v0 != 0) {
                // 0x001210f8
                charge(ctx, 3);
                lw(a0, s0, fl::kAnmSlots);
                if (a0 != 0) {
                    // 0x00121104
                    charge(ctx, 3);
                    mtc1(zero, f12);
                    jal(ctx, 0x121108u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                }
                // 0x00121110
                charge(ctx, 3);
                s2 = 1;
                for (;;) {
                    // 0x00121144
                    charge(ctx, 3);
                    v1 = slti(s2, 10);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0012111c
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v1 = addu(s0, v1);
                    s1 = addiu(v1, fl::kAnmSlots);
                    lw(a0, v1, fl::kAnmSlots);
                    if (a0 != 0) {
                        // 0x00121134
                        charge(ctx, 3);
                        jal(ctx, 0x121134u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x00121140
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x00121150
                charge(ctx, 5);
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnm1);
                sw(zero, s0, fl::kLoading);
                v1 = 999;
                sw(v1, s0, fl::kStep);
            }
        } else {
            // 0x00121004
            charge(ctx, 3);
            v1 = 3;
            if (a2 == v1) {
                // 0x00121078
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x12107Cu, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x00121090
                    charge(ctx, 21);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x121094u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x1210A4u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 1;
                    sw(v0, s0, fl::kDone);
                    v0 = 24;
                    sw(v0, s0, fl::kTimer);
                    v0 = 4;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 3;
                    jal(ctx, 0x1210D4u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x00121010
                charge(ctx, 3);
                a1 = 2;
                if (a2 == a1) {
                    // 0x00121050
                    charge(ctx, 10);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -20720);  // "camp/EQUIP/anm/if_c_equ01.anm"
                    jal(ctx, 0x12105Cu, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, fl::kLoading);
                    v1 = 3;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x0012101c
                    charge(ctx, 3);
                    v1 = 1;
                    if (a2 == v1) {
                        // 0x00121044
                        charge(ctx, 3);
                        sw(a1, s0, fl::kStep);
                    } else {
                        // 0x00121028
                        charge(ctx, 2);
                        if (a2 == 0) {
                            // 0x00121038
                            charge(ctx, 3);
                            sw(v1, s0, fl::kStep);
                        } else {
                            // 0x00121030
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
    }
    // 0x00121164 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00121180 sub_121180 -- 376 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/skill/anm/if_c_skl02.anm.
void sub_121180(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00121180
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a1, s0, fl::kStep);
    v1 = 999;
    if (a1 != v1) {
        // 0x001211a8
        charge(ctx, 3);
        v1 = 2;
        if (a1 == v1) {
            // 0x00121254
            charge(ctx, 5);
            lw(a0, s0, fl::kLoading);
            jal(ctx, 0x121258u, gen::fn_sub_111CB0_00111cb0);  // non-zero when the .anm ended
            if (v0 != 0) {
                // 0x00121268
                charge(ctx, 3);
                lw(a0, s0, fl::kAnm1);
                if (a0 != 0) {
                    // 0x00121274
                    charge(ctx, 3);
                    mtc1(zero, f12);
                    jal(ctx, 0x121278u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                }
                // 0x00121280
                charge(ctx, 3);
                s2 = 2;
                for (;;) {
                    // 0x001212b4
                    charge(ctx, 3);
                    v1 = slti(s2, 10);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0012128c
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v1 = addu(s0, v1);
                    s1 = addiu(v1, fl::kAnmSlots);
                    lw(a0, v1, fl::kAnmSlots);
                    if (a0 != 0) {
                        // 0x001212a4
                        charge(ctx, 3);
                        jal(ctx, 0x1212A4u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x001212b0
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x001212c0
                charge(ctx, 7);
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnm2);
                sw(zero, s0, fl::kLoading);
                v1 = 999;
                sw(v1, s0, fl::kStep);
                v1 = 1;
                sw(v1, s0, fl::kDone);
            }
        } else {
            // 0x001211b4
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x001211f8
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x1211FCu, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x00121210
                    charge(ctx, 17);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x121214u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x121224u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 2;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 5;
                    jal(ctx, 0x121244u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x001211c0
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x001211d0
                    charge(ctx, 10);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -20688);  // "camp/skill/anm/if_c_skl02.anm"
                    jal(ctx, 0x1211DCu, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, fl::kLoading);
                    v1 = 1;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x001211c8
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x001212dc (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00121300 sub_121300 -- 376 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/EQUIP/anm/if_c_equ02.anm.
void sub_121300(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00121300
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a1, s0, fl::kStep);
    v1 = 999;
    if (a1 != v1) {
        // 0x00121328
        charge(ctx, 3);
        v1 = 2;
        if (a1 == v1) {
            // 0x001213d4
            charge(ctx, 5);
            lw(a0, s0, fl::kLoading);
            jal(ctx, 0x1213D8u, gen::fn_sub_111CB0_00111cb0);  // non-zero when the .anm ended
            if (v0 != 0) {
                // 0x001213e8
                charge(ctx, 3);
                lw(a0, s0, fl::kAnm1);
                if (a0 != 0) {
                    // 0x001213f4
                    charge(ctx, 3);
                    mtc1(zero, f12);
                    jal(ctx, 0x1213F8u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                }
                // 0x00121400
                charge(ctx, 3);
                s2 = 2;
                for (;;) {
                    // 0x00121434
                    charge(ctx, 3);
                    v1 = slti(s2, 10);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0012140c
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v1 = addu(s0, v1);
                    s1 = addiu(v1, fl::kAnmSlots);
                    lw(a0, v1, fl::kAnmSlots);
                    if (a0 != 0) {
                        // 0x00121424
                        charge(ctx, 3);
                        jal(ctx, 0x121424u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x00121430
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x00121440
                charge(ctx, 7);
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnm2);
                sw(zero, s0, fl::kLoading);
                v1 = 999;
                sw(v1, s0, fl::kStep);
                v1 = 1;
                sw(v1, s0, fl::kDone);
            }
        } else {
            // 0x00121334
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x00121378
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x12137Cu, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x00121390
                    charge(ctx, 17);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x121394u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x1213A4u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 2;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 5;
                    jal(ctx, 0x1213C4u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x00121340
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x00121350
                    charge(ctx, 10);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -20656);  // "camp/EQUIP/anm/if_c_equ02.anm"
                    jal(ctx, 0x12135Cu, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, fl::kLoading);
                    v1 = 1;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x00121348
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x0012145c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00121480 sub_121480 -- 376 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Four frames of slots 1 and 2, then destroys slot 2 (skill sub-window close).
void sub_121480(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00121480
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a0, s0, fl::kStep);
    v1 = 999;
    if (a0 != v1) {
        // 0x001214a0
        charge(ctx, 3);
        v1 = 4;
        if (a0 != v1) {
            // 0x001214ac
            charge(ctx, 3);
            v1 = 3;
            if (a0 != v1) {
                // 0x001214b8
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    // 0x00121548
                    charge(ctx, 11);
                    v0 = 0x3F800000;
                    mtc1(v0, f12);
                    lw(a0, s0, fl::kAnm1);
                    jal(ctx, 0x121554u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                    lw(a0, s0, fl::kAnm2);
                    lwc1(f12, gp, -32632);  // 0x7CAD78
                    jal(ctx, 0x121564u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                    v0 = 3;
                    sw(v0, s0, fl::kStep);
                    goto L_00121574;
                }
                // 0x001214c4
                charge(ctx, 3);
                v1 = 1;
                if (a0 == v1) {
                    // 0x00121514
                    charge(ctx, 13);
                    v0 = 0x3F800000;
                    mtc1(v0, f12);
                    lw(a0, s0, fl::kAnm1);
                    jal(ctx, 0x121520u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                    lw(a0, s0, fl::kAnm2);
                    lwc1(f12, gp, -32572);  // 0x7CADB4
                    jal(ctx, 0x121530u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                    v1 = 2;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x001214d0
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x001214e0
                        charge(ctx, 13);
                        v0 = 0x3F800000;
                        mtc1(v0, f12);
                        lw(a0, s0, fl::kAnm1);
                        jal(ctx, 0x1214ECu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                        lw(a0, s0, fl::kAnm2);
                        lwc1(f12, gp, -31844);  // 0x7CB08C
                        jal(ctx, 0x1214FCu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                        v1 = 1;
                        sw(v1, s0, fl::kStep);
                    } else {
                        // 0x001214d8
                        charge(ctx, 2);
                    }
                }
                // 0x001215e4 (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(ra, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x20);
                return;
            }
        L_00121574:
            charge(ctx, 11);
            v0 = 0x3F800000;
            mtc1(v0, f12);
            lw(a0, s0, fl::kAnm1);
            jal(ctx, 0x121580u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
            lw(a0, s0, fl::kAnm2);
            lwc1(f12, gp, -32004);  // 0x7CAFEC
            jal(ctx, 0x121590u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
            v0 = 4;
            sw(v0, s0, fl::kStep);
        }
        // 0x001215a0
        charge(ctx, 17);
        v0 = 0x3F800000;
        mtc1(v0, f12);
        lw(a0, s0, fl::kAnm1);
        jal(ctx, 0x1215ACu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
        mtc1(zero, f12);
        lw(a0, s0, fl::kAnm2);
        jal(ctx, 0x1215BCu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
        lw(a0, s0, fl::kAnm2);
        jal(ctx, 0x1215C8u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
        sw(zero, s0, fl::kAnm2);
        v1 = 1;
        sw(v1, s0, fl::kDone);
        v1 = 999;
        sw(v1, s0, fl::kStep);
    }
    // 0x001215e4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00121600 sub_121600 -- 376 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Four frames of slots 1 and 2, then destroys slot 2 (equipment sub-window close).
void sub_121600(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00121600
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a0, s0, fl::kStep);
    v1 = 999;
    if (a0 != v1) {
        // 0x00121620
        charge(ctx, 3);
        v1 = 4;
        if (a0 != v1) {
            // 0x0012162c
            charge(ctx, 3);
            v1 = 3;
            if (a0 != v1) {
                // 0x00121638
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    // 0x001216c8
                    charge(ctx, 11);
                    v0 = 0x3F800000;
                    mtc1(v0, f12);
                    lw(a0, s0, fl::kAnm1);
                    jal(ctx, 0x1216D4u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                    lw(a0, s0, fl::kAnm2);
                    lwc1(f12, gp, -32632);  // 0x7CAD78
                    jal(ctx, 0x1216E4u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                    v0 = 3;
                    sw(v0, s0, fl::kStep);
                    goto L_001216f4;
                }
                // 0x00121644
                charge(ctx, 3);
                v1 = 1;
                if (a0 == v1) {
                    // 0x00121694
                    charge(ctx, 13);
                    v0 = 0x3F800000;
                    mtc1(v0, f12);
                    lw(a0, s0, fl::kAnm1);
                    jal(ctx, 0x1216A0u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                    lw(a0, s0, fl::kAnm2);
                    lwc1(f12, gp, -32572);  // 0x7CADB4
                    jal(ctx, 0x1216B0u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                    v1 = 2;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x00121650
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x00121660
                        charge(ctx, 13);
                        v0 = 0x3F800000;
                        mtc1(v0, f12);
                        lw(a0, s0, fl::kAnm1);
                        jal(ctx, 0x12166Cu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                        lw(a0, s0, fl::kAnm2);
                        lwc1(f12, gp, -31844);  // 0x7CB08C
                        jal(ctx, 0x12167Cu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                        v1 = 1;
                        sw(v1, s0, fl::kStep);
                    } else {
                        // 0x00121658
                        charge(ctx, 2);
                    }
                }
                // 0x00121764 (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(ra, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x20);
                return;
            }
        L_001216f4:
            charge(ctx, 11);
            v0 = 0x3F800000;
            mtc1(v0, f12);
            lw(a0, s0, fl::kAnm1);
            jal(ctx, 0x121700u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
            lw(a0, s0, fl::kAnm2);
            lwc1(f12, gp, -32004);  // 0x7CAFEC
            jal(ctx, 0x121710u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
            v0 = 4;
            sw(v0, s0, fl::kStep);
        }
        // 0x00121720
        charge(ctx, 17);
        v0 = 0x3F800000;
        mtc1(v0, f12);
        lw(a0, s0, fl::kAnm1);
        jal(ctx, 0x12172Cu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
        mtc1(zero, f12);
        lw(a0, s0, fl::kAnm2);
        jal(ctx, 0x12173Cu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
        lw(a0, s0, fl::kAnm2);
        jal(ctx, 0x121748u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
        sw(zero, s0, fl::kAnm2);
        v1 = 1;
        sw(v1, s0, fl::kDone);
        v1 = 999;
        sw(v1, s0, fl::kStep);
    }
    // 0x00121764 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00121780 sub_121780 -- 432 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/persona/anm/if_c_per01.anm (persona screen open).
void sub_121780(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00121780
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a2, s0, fl::kStep);
    v1 = 999;
    if (a2 != v1) {
        // 0x001217a8
        charge(ctx, 3);
        v1 = 4;
        if (a2 == v1) {
            // 0x00121894
            charge(ctx, 5);
            lw(a0, s0, fl::kLoading);
            jal(ctx, 0x121898u, gen::fn_sub_111CB0_00111cb0);  // non-zero when the .anm ended
            if (v0 != 0) {
                // 0x001218a8
                charge(ctx, 3);
                lw(a0, s0, fl::kAnmSlots);
                if (a0 != 0) {
                    // 0x001218b4
                    charge(ctx, 3);
                    mtc1(zero, f12);
                    jal(ctx, 0x1218B8u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                }
                // 0x001218c0
                charge(ctx, 3);
                s2 = 1;
                for (;;) {
                    // 0x001218f4
                    charge(ctx, 3);
                    v1 = slti(s2, 10);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001218cc
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v1 = addu(s0, v1);
                    s1 = addiu(v1, fl::kAnmSlots);
                    lw(a0, v1, fl::kAnmSlots);
                    if (a0 != 0) {
                        // 0x001218e4
                        charge(ctx, 3);
                        jal(ctx, 0x1218E4u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x001218f0
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x00121900
                charge(ctx, 5);
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnm1);
                sw(zero, s0, fl::kLoading);
                v1 = 999;
                sw(v1, s0, fl::kStep);
            }
        } else {
            // 0x001217b4
            charge(ctx, 3);
            v1 = 3;
            if (a2 == v1) {
                // 0x00121828
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x12182Cu, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x00121840
                    charge(ctx, 21);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x121844u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x121854u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 1;
                    sw(v0, s0, fl::kDone);
                    v0 = 24;
                    sw(v0, s0, fl::kTimer);
                    v0 = 4;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 3;
                    jal(ctx, 0x121884u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x001217c0
                charge(ctx, 3);
                a1 = 2;
                if (a2 == a1) {
                    // 0x00121800
                    charge(ctx, 10);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -20624);  // "camp/persona/anm/if_c_per01.anm"
                    jal(ctx, 0x12180Cu, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, fl::kLoading);
                    v1 = 3;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x001217cc
                    charge(ctx, 3);
                    v1 = 1;
                    if (a2 == v1) {
                        // 0x001217f4
                        charge(ctx, 3);
                        sw(a1, s0, fl::kStep);
                    } else {
                        // 0x001217d8
                        charge(ctx, 2);
                        if (a2 == 0) {
                            // 0x001217e8
                            charge(ctx, 3);
                            sw(v1, s0, fl::kStep);
                        } else {
                            // 0x001217e0
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
    }
    // 0x00121914 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00121930 sub_121930 -- 376 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/persona/anm/if_c_per02.anm.
void sub_121930(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00121930
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a1, s0, fl::kStep);
    v1 = 999;
    if (a1 != v1) {
        // 0x00121958
        charge(ctx, 3);
        v1 = 2;
        if (a1 == v1) {
            // 0x00121a04
            charge(ctx, 5);
            lw(a0, s0, fl::kLoading);
            jal(ctx, 0x121A08u, gen::fn_sub_111CB0_00111cb0);  // non-zero when the .anm ended
            if (v0 != 0) {
                // 0x00121a18
                charge(ctx, 3);
                lw(a0, s0, fl::kAnm1);
                if (a0 != 0) {
                    // 0x00121a24
                    charge(ctx, 3);
                    mtc1(zero, f12);
                    jal(ctx, 0x121A28u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                }
                // 0x00121a30
                charge(ctx, 3);
                s2 = 2;
                for (;;) {
                    // 0x00121a64
                    charge(ctx, 3);
                    v1 = slti(s2, 10);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00121a3c
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v1 = addu(s0, v1);
                    s1 = addiu(v1, fl::kAnmSlots);
                    lw(a0, v1, fl::kAnmSlots);
                    if (a0 != 0) {
                        // 0x00121a54
                        charge(ctx, 3);
                        jal(ctx, 0x121A54u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x00121a60
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x00121a70
                charge(ctx, 7);
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnm2);
                sw(zero, s0, fl::kLoading);
                v1 = 999;
                sw(v1, s0, fl::kStep);
                v1 = 1;
                sw(v1, s0, fl::kDone);
            }
        } else {
            // 0x00121964
            charge(ctx, 3);
            v1 = 1;
            if (a1 == v1) {
                // 0x001219a8
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x1219ACu, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x001219c0
                    charge(ctx, 17);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x1219C4u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x1219D4u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 2;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 5;
                    jal(ctx, 0x1219F4u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x00121970
                charge(ctx, 2);
                if (a1 == 0) {
                    // 0x00121980
                    charge(ctx, 10);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -20592);  // "camp/persona/anm/if_c_per02.anm"
                    jal(ctx, 0x12198Cu, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, fl::kLoading);
                    v1 = 1;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x00121978
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x00121a8c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00121AB0 sub_121AB0 -- 376 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Four frames of slots 1 and 2, then destroys slot 2 (persona sub-window close).
void sub_121AB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00121ab0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a0, s0, fl::kStep);
    v1 = 999;
    if (a0 != v1) {
        // 0x00121ad0
        charge(ctx, 3);
        v1 = 4;
        if (a0 != v1) {
            // 0x00121adc
            charge(ctx, 3);
            v1 = 3;
            if (a0 != v1) {
                // 0x00121ae8
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    // 0x00121b78
                    charge(ctx, 11);
                    v0 = 0x3F800000;
                    mtc1(v0, f12);
                    lw(a0, s0, fl::kAnm1);
                    jal(ctx, 0x121B84u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                    lw(a0, s0, fl::kAnm2);
                    lwc1(f12, gp, -32632);  // 0x7CAD78
                    jal(ctx, 0x121B94u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                    v0 = 3;
                    sw(v0, s0, fl::kStep);
                    goto L_00121ba4;
                }
                // 0x00121af4
                charge(ctx, 3);
                v1 = 1;
                if (a0 == v1) {
                    // 0x00121b44
                    charge(ctx, 13);
                    v0 = 0x3F800000;
                    mtc1(v0, f12);
                    lw(a0, s0, fl::kAnm1);
                    jal(ctx, 0x121B50u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                    lw(a0, s0, fl::kAnm2);
                    lwc1(f12, gp, -32572);  // 0x7CADB4
                    jal(ctx, 0x121B60u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                    v1 = 2;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x00121b00
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x00121b10
                        charge(ctx, 13);
                        v0 = 0x3F800000;
                        mtc1(v0, f12);
                        lw(a0, s0, fl::kAnm1);
                        jal(ctx, 0x121B1Cu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                        lw(a0, s0, fl::kAnm2);
                        lwc1(f12, gp, -31844);  // 0x7CB08C
                        jal(ctx, 0x121B2Cu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                        v1 = 1;
                        sw(v1, s0, fl::kStep);
                    } else {
                        // 0x00121b08
                        charge(ctx, 2);
                    }
                }
                // 0x00121c14 (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(ra, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x20);
                return;
            }
        L_00121ba4:
            charge(ctx, 11);
            v0 = 0x3F800000;
            mtc1(v0, f12);
            lw(a0, s0, fl::kAnm1);
            jal(ctx, 0x121BB0u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
            lw(a0, s0, fl::kAnm2);
            lwc1(f12, gp, -32004);  // 0x7CAFEC
            jal(ctx, 0x121BC0u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
            v0 = 4;
            sw(v0, s0, fl::kStep);
        }
        // 0x00121bd0
        charge(ctx, 17);
        v0 = 0x3F800000;
        mtc1(v0, f12);
        lw(a0, s0, fl::kAnm1);
        jal(ctx, 0x121BDCu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
        mtc1(zero, f12);
        lw(a0, s0, fl::kAnm2);
        jal(ctx, 0x121BECu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
        lw(a0, s0, fl::kAnm2);
        jal(ctx, 0x121BF8u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
        sw(zero, s0, fl::kAnm2);
        v1 = 1;
        sw(v1, s0, fl::kDone);
        v1 = 999;
        sw(v1, s0, fl::kStep);
    }
    // 0x00121c14 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00121C30 sub_121C30 -- 432 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Plays camp/system/anm/if_c_sys01.anm (system screen open).
void sub_121C30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00121c30
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a2, s0, fl::kStep);
    v1 = 999;
    if (a2 != v1) {
        // 0x00121c58
        charge(ctx, 3);
        v1 = 4;
        if (a2 == v1) {
            // 0x00121d44
            charge(ctx, 5);
            lw(a0, s0, fl::kLoading);
            jal(ctx, 0x121D48u, gen::fn_sub_111CB0_00111cb0);  // non-zero when the .anm ended
            if (v0 != 0) {
                // 0x00121d58
                charge(ctx, 3);
                lw(a0, s0, fl::kAnmSlots);
                if (a0 != 0) {
                    // 0x00121d64
                    charge(ctx, 3);
                    mtc1(zero, f12);
                    jal(ctx, 0x121D68u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                }
                // 0x00121d70
                charge(ctx, 3);
                s2 = 1;
                for (;;) {
                    // 0x00121da4
                    charge(ctx, 3);
                    v1 = slti(s2, 10);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00121d7c
                    charge(ctx, 6);
                    v1 = sll(s2, 2);
                    v1 = addu(s0, v1);
                    s1 = addiu(v1, fl::kAnmSlots);
                    lw(a0, v1, fl::kAnmSlots);
                    if (a0 != 0) {
                        // 0x00121d94
                        charge(ctx, 3);
                        jal(ctx, 0x121D94u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                        sw(zero, s1, 0);
                    }
                    // 0x00121da0
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x00121db0
                charge(ctx, 5);
                lw(v1, s0, fl::kLoading);
                sw(v1, s0, fl::kAnm1);
                sw(zero, s0, fl::kLoading);
                v1 = 999;
                sw(v1, s0, fl::kStep);
            }
        } else {
            // 0x00121c64
            charge(ctx, 3);
            v1 = 3;
            if (a2 == v1) {
                // 0x00121cd8
                charge(ctx, 6);
                lw(a0, s0, fl::kLoading);
                jal(ctx, 0x121CDCu, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
                v1 = 1;
                if (v0 == v1) {
                    // 0x00121cf0
                    charge(ctx, 21);
                    lw(a0, s0, fl::kLoading);
                    jal(ctx, 0x121CF4u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                    lw(a0, s0, fl::kLoading);
                    a1 = 1;
                    jal(ctx, 0x121D04u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                    v0 = 1;
                    sw(v0, s0, fl::kDone);
                    v0 = 24;
                    sw(v0, s0, fl::kTimer);
                    v0 = 4;
                    sw(v0, s0, fl::kStep);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 3;
                    jal(ctx, 0x121D34u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                }
            } else {
                // 0x00121c70
                charge(ctx, 3);
                a1 = 2;
                if (a2 == a1) {
                    // 0x00121cb0
                    charge(ctx, 10);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -20560);  // "camp/system/anm/if_c_sys01.anm"
                    jal(ctx, 0x121CBCu, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, fl::kLoading);
                    v1 = 3;
                    sw(v1, s0, fl::kStep);
                } else {
                    // 0x00121c7c
                    charge(ctx, 3);
                    v1 = 1;
                    if (a2 == v1) {
                        // 0x00121ca4
                        charge(ctx, 3);
                        sw(a1, s0, fl::kStep);
                    } else {
                        // 0x00121c88
                        charge(ctx, 2);
                        if (a2 == 0) {
                            // 0x00121c98
                            charge(ctx, 3);
                            sw(v1, s0, fl::kStep);
                        } else {
                            // 0x00121c90
                            charge(ctx, 2);
                        }
                    }
                }
            }
        }
    }
    // 0x00121dc4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00121FF0 sub_121FF0 -- 1592 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// [H_Camp_UpdatePcKaniControlTask] Update of "h_camp_pc_kani_control" (the protagonist side portrait; jump table
// 0x7B58B0): every state draws the pose through sub_123640 at (30, 219) with the pose of +20; states 1/2 (21-frame
// pose change), 5/6 and 7/8 (8-frame slide out / in: x 30 - 500 t / 8, alpha 255 t / 8) and the instant states; +16 =
// shown. Returns 0.
void sub_121FF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x00121ff0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(v0, s0, 0);
    at = sltiu(v0, 15);
    if (at != 0) {
        // 0x00122010
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 22704);  // &0x7B58B0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x12202Cu:  // table[0]
            // 0x0012202c
            charge(ctx, 3);
            lw(v0, s0, 16);
            if (v0 != 0) {
                // 0x00122038
                charge(ctx, 16);
                v0 = 0x41F00000;
                sw(v0, sp, 0x28);
                v0 = 0x435B0000;
                sw(v0, sp, 0x2C);
                v0 = 0x42C80000;
                mtc1(v0, f12);
                ld(a0, sp, 0x28);
                a1 = a0;
                lh(a2, s0, 20);
                a3 = 1;
                t0 = 0;
                t1 = 0;
                jal(ctx, 0x122068u, gen::fn_sub_123640_00123640);
            }
            break;
        case 0x122078u:  // table[1]
            // 0x00122078
            charge(ctx, 5);
            v0 = 2;
            sw(v0, s0, 0);
            sw(zero, s0, 8);
            break;
        case 0x12208Cu:  // table[2]
            // 0x0012208c
            charge(ctx, 6);
            lw(v0, s0, 8);
            v1 = addiu(v0, 1);
            sw(v1, s0, 8);
            v0 = 21;
            if (v1 == v0) {
                // 0x001220a4
                charge(ctx, 1);
                sw(zero, s0, 0);
            }
            // 0x001220a8
            charge(ctx, 18);
            v0 = 0x41F00000;
            sw(v0, sp, 0x28);
            v0 = 0x435B0000;
            sw(v0, sp, 0x2C);
            v0 = 0x42C80000;
            mtc1(v0, f12);
            ld(a0, sp, 0x28);
            a1 = a0;
            lh(a2, s0, 20);
            a3 = 0;
            lw(t0, s0, 8);
            t1 = 0;
            jal(ctx, 0x1220D8u, gen::fn_sub_123640_00123640);
            v0 = 1;
            sw(v0, s0, 16);
            break;
        case 0x1220F0u:  // table[3]
            // 0x001220f0
            charge(ctx, 18);
            v0 = 0x41F00000;
            sw(v0, sp, 0x28);
            v0 = 0x435B0000;
            sw(v0, sp, 0x2C);
            v0 = 0x42C80000;
            mtc1(v0, f12);
            ld(a0, sp, 0x28);
            a1 = a0;
            lh(a2, s0, 20);
            a3 = 1;
            t0 = 0;
            t1 = 0;
            jal(ctx, 0x122120u, gen::fn_sub_123640_00123640);
            v0 = 4;
            sw(v0, s0, 0);
            break;
        case 0x122138u:  // table[4]
            // 0x00122138
            charge(ctx, 19);
            v0 = 0x41F00000;
            sw(v0, sp, 0x28);
            v0 = 0x435B0000;
            sw(v0, sp, 0x2C);
            v0 = 0x42C80000;
            mtc1(v0, f12);
            ld(a0, sp, 0x28);
            a1 = a0;
            lh(a2, s0, 20);
            a3 = 1;
            t0 = 0;
            t1 = 0;
            jal(ctx, 0x122168u, gen::fn_sub_123640_00123640);
            sw(zero, s0, 0);
            v0 = 1;
            sw(v0, s0, 16);
            break;
        case 0x122184u:  // table[5]
            // 0x00122184
            charge(ctx, 19);
            v0 = 0x41F00000;
            sw(v0, sp, 0x28);
            v0 = 0x435B0000;
            sw(v0, sp, 0x2C);
            v0 = 0x42C80000;
            mtc1(v0, f12);
            ld(a0, sp, 0x28);
            a1 = a0;
            lh(a2, s0, 20);
            a3 = 1;
            t0 = 0;
            t1 = 0;
            jal(ctx, 0x1221B4u, gen::fn_sub_123640_00123640);
            sw(zero, s0, 8);
            v0 = 6;
            sw(v0, s0, 0);
            break;
        case 0x1221D0u:  // table[6]
            // 0x001221d0
            charge(ctx, 6);
            lw(v0, s0, 8);
            v1 = addiu(v0, 1);
            sw(v1, s0, 8);
            v0 = 8;
            if (v1 == v0) {
                // 0x001221e8
                charge(ctx, 2);
                sw(zero, s0, 16);
                sw(zero, s0, 0);
            }
            // 0x001221f0
            charge(ctx, 9);
            lw(a0, s0, 8);
            v0 = sll(a0, 5);
            v0 = subu(v0, a0);
            v0 = sll(v0, 2);
            v0 = addu(v0, a0);
            v1 = sll(v0, 2);
            v0 = sra(v1, 3);
            if (i64(v1) < 0) {
                // 0x00122214
                charge(ctx, 2);
                v0 = addiu(v1, 7);
                v0 = sra(v0, 3);
            }
            // 0x0012221c
            charge(ctx, 17);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41F00000;
            mtc1(v0, f0);
            sub_s(f0, f0, f1);
            swc1(f0, sp, 0x28);
            v0 = 0x435B0000;
            sw(v0, sp, 0x2C);
            v0 = 0x42C80000;
            mtc1(v0, f12);
            v0 = sll(a0, 8);
            v0 = subu(v0, a0);
            t1 = sra(v0, 3);
            if (i64(v0) < 0) {
                // 0x00122260
                charge(ctx, 2);
                v0 = addiu(v0, 7);
                t1 = sra(v0, 3);
            }
            // 0x00122268
            charge(ctx, 9);
            ld(a0, sp, 0x28);
            a1 = a0;
            lh(a2, s0, 20);
            a3 = 1;
            t0 = 0;
            jal(ctx, 0x12227Cu, gen::fn_sub_123640_00123640);
            break;
        case 0x12228Cu:  // table[7]
            // 0x0012228c
            charge(ctx, 5);
            sw(zero, s0, 8);
            v0 = 8;
            sw(v0, s0, 0);
            break;
        case 0x1222A0u:  // table[8]
            // 0x001222a0
            charge(ctx, 6);
            lw(v0, s0, 8);
            v1 = addiu(v0, 1);
            sw(v1, s0, 8);
            v0 = 8;
            if (v1 == v0) {
                // 0x001222b8
                charge(ctx, 3);
                v0 = 1;
                sw(v0, s0, 16);
                sw(zero, s0, 0);
            }
            // 0x001222c4
            charge(ctx, 9);
            lw(a0, s0, 8);
            v0 = sll(a0, 5);
            v0 = subu(v0, a0);
            v0 = sll(v0, 2);
            v0 = addu(v0, a0);
            v0 = sll(v0, 2);
            v1 = sra(v0, 3);
            if (i64(v0) < 0) {
                // 0x001222e8
                charge(ctx, 2);
                v0 = addiu(v0, 7);
                v1 = sra(v0, 3);
            }
            // 0x001222f0
            charge(ctx, 19);
            v0 = 500;
            v0 = subu(v0, v1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41F00000;
            mtc1(v0, f0);
            sub_s(f0, f0, f1);
            swc1(f0, sp, 0x28);
            v0 = 0x435B0000;
            sw(v0, sp, 0x2C);
            v0 = 0x42C80000;
            mtc1(v0, f12);
            v0 = sll(a0, 8);
            v0 = subu(v0, a0);
            v1 = sra(v0, 3);
            if (i64(v0) < 0) {
                // 0x0012233c
                charge(ctx, 2);
                v0 = addiu(v0, 7);
                v1 = sra(v0, 3);
            }
            // 0x00122344
            charge(ctx, 11);
            v0 = 255;
            t1 = subu(v0, v1);
            ld(a0, sp, 0x28);
            a1 = a0;
            lh(a2, s0, 20);
            a3 = 1;
            t0 = 0;
            jal(ctx, 0x122360u, gen::fn_sub_123640_00123640);
            break;
        case 0x122370u:  // table[9]
            // 0x00122370
            charge(ctx, 5);
            v0 = 10;
            sw(v0, s0, 0);
            sw(zero, s0, 8);
            break;
        case 0x122384u:  // table[10]
            // 0x00122384
            charge(ctx, 6);
            lw(v0, s0, 8);
            v1 = addiu(v0, 1);
            sw(v1, s0, 8);
            v0 = 20;
            if (v1 == v0) {
                // 0x0012239c
                charge(ctx, 3);
                v0 = 1;
                sw(v0, s0, 16);
                sw(zero, s0, 0);
            }
            // 0x001223a8
            charge(ctx, 23);
            lw(v1, s0, 8);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 20;
            div(v1, v0);
            mflo(v1);
            v0 = 255;
            t1 = subu(v0, v1);
            v0 = 0x41F00000;
            sw(v0, sp, 0x28);
            v0 = 0x435B0000;
            sw(v0, sp, 0x2C);
            v0 = 0x42C80000;
            mtc1(v0, f12);
            ld(a0, sp, 0x28);
            a1 = a0;
            lh(a2, s0, 20);
            a3 = 1;
            t0 = 0;
            jal(ctx, 0x1223F4u, gen::fn_sub_123640_00123640);
            break;
        case 0x122404u:  // table[11]
            // 0x00122404
            charge(ctx, 3);
            lw(v0, s0, 16);
            if (v0 != 0) {
                // 0x0012241c
                charge(ctx, 19);
                v0 = 0x41F00000;
                sw(v0, sp, 0x28);
                v0 = 0x435B0000;
                sw(v0, sp, 0x2C);
                sw(zero, s0, 8);
                v0 = 0x42C80000;
                mtc1(v0, f12);
                ld(a0, sp, 0x28);
                a1 = a0;
                lh(a2, s0, 20);
                a3 = 1;
                t0 = 0;
                t1 = 0;
                jal(ctx, 0x122450u, gen::fn_sub_123640_00123640);
                v0 = 12;
                sw(v0, s0, 0);
            } else {
                // 0x00122410
                charge(ctx, 3);
                sw(zero, s0, 0);
            }
            break;
        case 0x122468u:  // table[12]
            // 0x00122468
            charge(ctx, 6);
            lw(v0, s0, 8);
            v1 = addiu(v0, 1);
            sw(v1, s0, 8);
            v0 = 10;
            if (v1 == v0) {
                // 0x00122480
                charge(ctx, 2);
                sw(zero, s0, 16);
                sw(zero, s0, 0);
            }
            // 0x00122488
            charge(ctx, 21);
            v0 = 0x41F00000;
            sw(v0, sp, 0x28);
            v0 = 0x435B0000;
            sw(v0, sp, 0x2C);
            v0 = 0x42C80000;
            mtc1(v0, f12);
            lw(v1, s0, 8);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 10;
            div(v1, v0);
            mflo(t1);
            ld(a0, sp, 0x28);
            a1 = a0;
            lh(a2, s0, 20);
            a3 = 1;
            t0 = 0;
            jal(ctx, 0x1224CCu, gen::fn_sub_123640_00123640);
            break;
        case 0x1224DCu:  // table[13]
            // 0x001224dc
            charge(ctx, 3);
            lw(v0, s0, 16);
            if (v0 != 0) {
                // 0x001224f4
                charge(ctx, 19);
                v0 = 0x41F00000;
                sw(v0, sp, 0x28);
                v0 = 0x435B0000;
                sw(v0, sp, 0x2C);
                sw(zero, s0, 8);
                v0 = 0x42C80000;
                mtc1(v0, f12);
                ld(a0, sp, 0x28);
                a1 = a0;
                lh(a2, s0, 20);
                a3 = 1;
                t0 = 0;
                t1 = 0;
                jal(ctx, 0x122528u, gen::fn_sub_123640_00123640);
                v0 = 14;
                sw(v0, s0, 0);
            } else {
                // 0x001224e8
                charge(ctx, 3);
                sw(zero, s0, 0);
            }
            break;
        case 0x122540u:  // table[14]
            // 0x00122540
            charge(ctx, 6);
            lw(v0, s0, 8);
            v1 = addiu(v0, 1);
            sw(v1, s0, 8);
            v0 = 8;
            if (v1 != v0) {
                // 0x00122568
                charge(ctx, 10);
                v0 = 0x41F00000;
                mtc1(v0, f2);
                sw(v0, sp, 0x28);
                v0 = 0x435B0000;
                mtc1(v0, f1);
                sw(v0, sp, 0x2C);
                t1 = 0;
                v0 = slti(v1, 3);
                if (v0 == 0) {
                    // 0x00122590
                    charge(ctx, 19);
                    a0 = addiu(v1, -3);
                    v0 = sll(a0, 2);
                    v1 = addu(v0, a0);
                    v0 = sll(v1, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 4);
                    v1 = 5;
                    div(v0, v1);
                    mflo(v0);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, sp, 0x28);
                    swc1(f1, sp, 0x2C);
                    v0 = sll(a0, 8);
                    v0 = subu(v0, a0);
                    div1(v0, v1);
                    mflo1(t1);
                }
                // 0x001225dc
                charge(ctx, 13);
                v0 = 0x41F00000;
                sw(v0, sp, 0x20);
                v0 = 0x435B0000;
                sw(v0, sp, 0x24);
                v0 = 0x42C80000;
                mtc1(v0, f12);
                ld(a0, sp, 0x28);
                ld(a1, sp, 0x20);
                lh(a2, s0, 20);
                a3 = 1;
                t0 = 0;
                jal(ctx, 0x122608u, gen::fn_sub_123640_00123640);
            } else {
                // 0x00122558
                charge(ctx, 4);
                sw(zero, s0, 16);
                sw(zero, s0, 0);
            }
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    }
    // 0x00122610 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00122630 sub_122630 -- 44 bytes; frame 0x10: ra sp+0x0
// Destroy of "h_camp_pc_kani_control": frees the work.
void sub_122630(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00122630
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, task::kWork);
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x122644u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00122660 sub_122660 -- 172 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_CreatePcKaniControlTask] (parent): creates "h_camp_pc_kani_control" (24-byte work, priority 6337, update
// sub_121FF0): +12 screen 0, +20 pose 1.
void sub_122660(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00122660
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 1;
    a1 = 24;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x122688u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001226a8
        charge(ctx, 13);
        a0 = s1;
        a1 = 0x5E0000;
        a1 = addiu(a1, -20528);  // "h_camp_pc_kani_control"
        a2 = 6337;
        a3 = 0x120000;
        a3 = addiu(a3, 8176);  // &sub_121FF0
        t0 = 0x120000;
        t0 = addiu(t0, 9776);  // &sub_122630
        t1 = s0;
        jal(ctx, 0x1226CCu, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x001226e8
            charge(ctx, 3);
            sw(zero, s0, 12);
            v1 = 1;
            sh(v1, s0, 20);
        } else {
            // 0x001226dc
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0012269c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001226f4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00122940 sub_122940 -- 1672 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_UpdatePersonaKaniControlTask] Update of "h_camp_persona_kani_control" (the persona side portrait; jump table
// 0x7B5AB0): as sub_121FF0 for the persona of +16 (datPersonaGetByPcId when it changes), drawn through sub_124E00.
// Returns 0.
void sub_122940(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x00122940
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lhu(a0, s0, 24);
    jal(ctx, 0x122958u, gen::fn_datPersonaGetByPcId_00174800);
    sw(v0, s0, 16);
    lw(v0, s0, 0);
    at = sltiu(v0, 15);
    if (at != 0) {
        // 0x00122974
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 23216);  // &0x7B5AB0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x122990u:  // table[0]
            // 0x00122990
            charge(ctx, 3);
            lw(v0, s0, 20);
            if (v0 != 0) {
                // 0x0012299c
                charge(ctx, 4);
                lh(v0, s0, 26);
                a3 = 1;
                if (v0 == a3) {
                    // 0x001229f8
                    charge(ctx, 15);
                    v0 = 0x41400000;
                    sw(v0, sp, 0x38);
                    v0 = 0x42C00000;
                    sw(v0, sp, 0x3C);
                    v0 = 0x42C80000;
                    mtc1(v0, f12);
                    ld(a0, sp, 0x38);
                    a1 = a0;
                    lw(a2, s0, 16);
                    t0 = 0;
                    t1 = 0;
                    jal(ctx, 0x122A24u, gen::fn_sub_124E00_00124e00);
                } else {
                    // 0x001229ac
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x001229bc
                        charge(ctx, 15);
                        v0 = 0x41F00000;
                        sw(v0, sp, 0x38);
                        v0 = 0x435B0000;
                        sw(v0, sp, 0x3C);
                        v0 = 0x42C80000;
                        mtc1(v0, f12);
                        ld(a0, sp, 0x38);
                        a1 = a0;
                        lw(a2, s0, 16);
                        t0 = 0;
                        t1 = 0;
                        jal(ctx, 0x1229E8u, gen::fn_sub_124E00_00124e00);
                    } else {
                        // 0x001229b4
                        charge(ctx, 2);
                    }
                }
            }
            break;
        case 0x122A34u:  // table[1]
            // 0x00122a34
            charge(ctx, 5);
            v0 = 2;
            sw(v0, s0, 0);
            sw(zero, s0, 8);
            break;
        case 0x122A48u:  // table[2]
            // 0x00122a48
            charge(ctx, 6);
            lw(v0, s0, 8);
            v1 = addiu(v0, 1);
            sw(v1, s0, 8);
            v0 = 30;
            if (v1 == v0) {
                // 0x00122a60
                charge(ctx, 2);
                sh(zero, s0, 26);
                sw(zero, s0, 0);
            }
            // 0x00122a68
            charge(ctx, 18);
            v0 = 0x41F00000;
            sw(v0, sp, 0x38);
            v0 = 0x435B0000;
            sw(v0, sp, 0x3C);
            v0 = 0x42C80000;
            mtc1(v0, f12);
            ld(a0, sp, 0x38);
            a1 = a0;
            lw(a2, s0, 16);
            a3 = 0;
            lw(t0, s0, 8);
            t1 = 0;
            jal(ctx, 0x122A98u, gen::fn_sub_124E00_00124e00);
            v0 = 1;
            sw(v0, s0, 20);
            break;
        case 0x122AB0u:  // table[3]
            // 0x00122ab0
            charge(ctx, 5);
            v0 = 4;
            sw(v0, s0, 0);
            sw(zero, s0, 8);
            break;
        case 0x122AC4u:  // table[4]
            // 0x00122ac4
            charge(ctx, 6);
            lw(v0, s0, 8);
            v1 = addiu(v0, 1);
            sw(v1, s0, 8);
            v0 = 20;
            if (v1 == v0) {
                // 0x00122adc
                charge(ctx, 4);
                v0 = 1;
                sw(v0, s0, 20);
                sw(zero, s0, 0);
                sh(zero, s0, 26);
            }
            // 0x00122aec
            charge(ctx, 23);
            lw(v1, s0, 8);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 20;
            div(v1, v0);
            mflo(v1);
            v0 = 255;
            t1 = subu(v0, v1);
            v0 = 0x41F00000;
            sw(v0, sp, 0x38);
            v0 = 0x435B0000;
            sw(v0, sp, 0x3C);
            v0 = 0x42C80000;
            mtc1(v0, f12);
            ld(a0, sp, 0x38);
            a1 = a0;
            lw(a2, s0, 16);
            a3 = 1;
            t0 = 0;
            jal(ctx, 0x122B38u, gen::fn_sub_124E00_00124e00);
            break;
        case 0x122B48u:  // table[5]
            // 0x00122b48
            charge(ctx, 3);
            lw(v0, s0, 20);
            if (v0 != 0) {
                // 0x00122b60
                charge(ctx, 19);
                v0 = 0x41F00000;
                sw(v0, sp, 0x38);
                v0 = 0x435B0000;
                sw(v0, sp, 0x3C);
                sw(zero, s0, 8);
                v0 = 0x42C80000;
                mtc1(v0, f12);
                ld(a0, sp, 0x38);
                a1 = a0;
                lw(a2, s0, 16);
                a3 = 1;
                t0 = 0;
                t1 = 0;
                jal(ctx, 0x122B94u, gen::fn_sub_124E00_00124e00);
                v0 = 6;
                sw(v0, s0, 0);
            } else {
                // 0x00122b54
                charge(ctx, 3);
                sw(zero, s0, 0);
            }
            break;
        case 0x122BACu:  // table[6]
            // 0x00122bac
            charge(ctx, 6);
            lw(v0, s0, 8);
            v1 = addiu(v0, 1);
            sw(v1, s0, 8);
            v0 = 20;
            if (v1 == v0) {
                // 0x00122bc4
                charge(ctx, 3);
                sw(zero, s0, 20);
                sw(zero, s0, 0);
                sh(zero, s0, 26);
            }
            // 0x00122bd0
            charge(ctx, 21);
            v0 = 0x41F00000;
            sw(v0, sp, 0x38);
            v0 = 0x435B0000;
            sw(v0, sp, 0x3C);
            v0 = 0x42C80000;
            mtc1(v0, f12);
            lw(v1, s0, 8);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 20;
            div(v1, v0);
            mflo(t1);
            ld(a0, sp, 0x38);
            a1 = a0;
            lw(a2, s0, 16);
            a3 = 1;
            t0 = 0;
            jal(ctx, 0x122C14u, gen::fn_sub_124E00_00124e00);
            break;
        case 0x122C24u:  // table[7]
            // 0x00122c24
            charge(ctx, 3);
            lw(v0, s0, 20);
            if (v0 != 0) {
                // 0x00122c3c
                charge(ctx, 19);
                v0 = 0x41F00000;
                sw(v0, sp, 0x38);
                v0 = 0x435B0000;
                sw(v0, sp, 0x3C);
                sw(zero, s0, 8);
                v0 = 0x42C80000;
                mtc1(v0, f12);
                ld(a0, sp, 0x38);
                a1 = a0;
                lw(a2, s0, 16);
                a3 = 1;
                t0 = 0;
                t1 = 0;
                jal(ctx, 0x122C70u, gen::fn_sub_124E00_00124e00);
                v0 = 8;
                sw(v0, s0, 0);
            } else {
                // 0x00122c30
                charge(ctx, 3);
                sw(zero, s0, 0);
            }
            break;
        case 0x122C88u:  // table[8]
            // 0x00122c88
            charge(ctx, 6);
            lw(v0, s0, 8);
            v1 = addiu(v0, 1);
            sw(v1, s0, 8);
            v0 = 8;
            if (v1 != v0) {
                // 0x00122cb4
                charge(ctx, 10);
                v0 = 0x41F00000;
                mtc1(v0, f2);
                sw(v0, sp, 0x38);
                v0 = 0x435B0000;
                mtc1(v0, f1);
                sw(v0, sp, 0x3C);
                t1 = 0;
                v0 = slti(v1, 3);
                if (v0 == 0) {
                    // 0x00122cdc
                    charge(ctx, 19);
                    a0 = addiu(v1, -3);
                    v0 = sll(a0, 2);
                    v1 = addu(v0, a0);
                    v0 = sll(v1, 2);
                    v0 = addu(v1, v0);
                    v0 = sll(v0, 4);
                    v1 = 5;
                    div(v0, v1);
                    mflo(v0);
                    mtc1(v0, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f2, f0);
                    swc1(f0, sp, 0x38);
                    swc1(f1, sp, 0x3C);
                    v0 = sll(a0, 8);
                    v0 = subu(v0, a0);
                    div1(v0, v1);
                    mflo1(t1);
                }
                // 0x00122d28
                charge(ctx, 15);
                v0 = 0x41F00000;
                sw(v0, sp, 0x30);
                v0 = 0x435B0000;
                sw(v0, sp, 0x34);
                v0 = 0x42C80000;
                mtc1(v0, f12);
                ld(a0, sp, 0x38);
                ld(a1, sp, 0x30);
                lw(a2, s0, 16);
                a3 = 1;
                t0 = 0;
                jal(ctx, 0x122D54u, gen::fn_sub_124E00_00124e00);
            } else {
                // 0x00122ca0
                charge(ctx, 5);
                sw(zero, s0, 20);
                sw(zero, s0, 0);
                sh(zero, s0, 26);
            }
            break;
        case 0x122D64u:  // table[9]
            // 0x00122d64
            charge(ctx, 3);
            v0 = 10;
            sw(v0, s0, 0);
            sw(zero, s0, 8);
        L_00122d70:
            charge(ctx, 6);
            lw(v0, s0, 8);
            v1 = addiu(v0, 1);
            sw(v1, s0, 8);
            v0 = 10;
            if (v1 == v0) {
                // 0x00122d88
                charge(ctx, 4);
                v0 = 1;
                sw(v0, s0, 20);
                sw(zero, s0, 0);
                sh(v0, s0, 26);
            }
            // 0x00122d98
            charge(ctx, 38);
            lw(a1, s0, 8);
            v0 = sll(a1, 8);
            v0 = subu(v0, a1);
            a0 = 10;
            div(v0, a0);
            mflo(v1);
            v0 = 255;
            t1 = subu(v0, v1);
            v1 = subu(a0, a1);
            v0 = sll(v1, 2);
            v1 = addu(v0, v1);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v1 = sll(v0, 5);
            v0 = 20;
            div1(v1, v0);
            mflo1(v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41400000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x38);
            v0 = 0x42C00000;
            sw(v0, sp, 0x3C);
            v0 = 0x42C80000;
            mtc1(v0, f12);
            ld(a0, sp, 0x38);
            a1 = a0;
            lw(a2, s0, 16);
            a3 = 1;
            t0 = 0;
            jal(ctx, 0x122E20u, gen::fn_sub_124E00_00124e00);
            break;
        case 0x122D70u:  // table[10]
            goto L_00122d70;
        case 0x122E30u:  // table[11]
            // 0x00122e30
            charge(ctx, 3);
            v0 = 12;
            sw(v0, s0, 0);
            sw(zero, s0, 8);
        L_00122e3c:
            charge(ctx, 6);
            lw(v0, s0, 8);
            v1 = addiu(v0, 1);
            sw(v1, s0, 8);
            v0 = 10;
            if (v1 == v0) {
                // 0x00122e54
                charge(ctx, 4);
                sw(zero, s0, 20);
                sw(zero, s0, 0);
                v0 = 1;
                sh(v0, s0, 26);
            }
            // 0x00122e64
            charge(ctx, 34);
            lw(a0, s0, 8);
            v0 = sll(a0, 2);
            v1 = addu(v0, a0);
            v0 = sll(v1, 2);
            v0 = addu(v1, v0);
            v0 = sll(v0, 5);
            v1 = 10;
            div(v0, v1);
            mflo(v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41400000;
            mtc1(v0, f0);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0x38);
            v0 = 0x42C00000;
            sw(v0, sp, 0x3C);
            v0 = 0x42C80000;
            mtc1(v0, f12);
            v0 = sll(a0, 8);
            v0 = subu(v0, a0);
            div1(v0, v1);
            mflo1(t1);
            ld(a0, sp, 0x38);
            a1 = a0;
            lw(a2, s0, 16);
            a3 = 1;
            t0 = 0;
            jal(ctx, 0x122EDCu, gen::fn_sub_124E00_00124e00);
            break;
        case 0x122E3Cu:  // table[12]
            goto L_00122e3c;
        case 0x122EECu:  // table[13]
            // 0x00122eec
            charge(ctx, 3);
            v0 = 14;
            sw(v0, s0, 0);
            sw(zero, s0, 8);
        L_00122ef8:
            charge(ctx, 6);
            lw(v0, s0, 8);
            v1 = addiu(v0, 1);
            sw(v1, s0, 8);
            v0 = 20;
            if (v1 == v0) {
                // 0x00122f10
                charge(ctx, 4);
                v0 = 1;
                sw(v0, s0, 20);
                sw(zero, s0, 0);
                sh(zero, s0, 26);
            }
            // 0x00122f20
            charge(ctx, 35);
            lw(v1, s0, 8);
            v0 = sll(v1, 8);
            v1 = subu(v0, v1);
            v0 = 20;
            div(v1, v0);
            mflo(s1);
            v0 = 0x41400000;
            sw(v0, sp, 0x38);
            v0 = 0x42C00000;
            sw(v0, sp, 0x3C);
            v0 = 0x42C80000;
            mtc1(v0, f12);
            ld(a0, sp, 0x38);
            a1 = a0;
            lw(a2, s0, 16);
            a3 = 1;
            t0 = 0;
            t1 = s1;
            jal(ctx, 0x122F68u, gen::fn_sub_124E00_00124e00);
            v0 = 255;
            t1 = subu(v0, s1);
            v0 = 0x41F00000;
            sw(v0, sp, 0x38);
            v0 = 0x435B0000;
            sw(v0, sp, 0x3C);
            v0 = 0x42C80000;
            mtc1(v0, f12);
            ld(a0, sp, 0x38);
            a1 = a0;
            lw(a2, s0, 16);
            a3 = 1;
            t0 = 0;
            jal(ctx, 0x122FA4u, gen::fn_sub_124E00_00124e00);
            break;
        case 0x122EF8u:  // table[14]
            goto L_00122ef8;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    }
    // 0x00122fac (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00122FD0 sub_122FD0 -- 44 bytes; frame 0x10: ra sp+0x0
// Destroy of "h_camp_persona_kani_control": frees the work.
void sub_122FD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00122fd0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, task::kWork);
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x122FE4u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00123000 sub_123000 -- 188 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_CreatePersonaKaniControlTask] (parent, persona): creates "h_camp_persona_kani_control" (28-byte work,
// priority 6337, update sub_122940): +12 screen 0, +16 persona, +24 pose 1.
void sub_123000(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00123000
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 1;
    a1 = 28;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x123030u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00123050
        charge(ctx, 13);
        a0 = s2;
        a1 = 0x5E0000;
        a1 = addiu(a1, -20496);  // "h_camp_persona_kani_control"
        a2 = 6337;
        a3 = 0x120000;
        a3 = addiu(a3, 10560);  // &sub_122940
        t0 = 0x120000;
        t0 = addiu(t0, 12240);  // &sub_122FD0
        t1 = s0;
        jal(ctx, 0x123074u, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x00123090
            charge(ctx, 4);
            sw(zero, s0, 12);
            sw(s1, s0, 16);
            v1 = 1;
            sh(v1, s0, 24);
        } else {
            // 0x00123084
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00123044
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001230a0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001230C0 sub_1230C0 -- 1144 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_UpdatePcStatusRootTask] Update of "H_CampPcStatusRoot" (the Status screen root): state 0 creates the status
// draw (sub_127B00, page 0) and starts the scrolling strip (gp-19792 = 320); 1 waits for the page's answer (sub_127AF0
// / sub_128030): -1 closes (state 4), 1 switches page; 2 swaps the status page (sub_127B00) and the persona page
// (sub_128040); 4 fades out and returns -1 once the page task is finished. Every state draws the strip (sprite 30 of
// file 0x833B98 twice, scrolling by -1 per frame, wrapping at -400 by +640) with the alpha of +16 (fading by 5).
void sub_1230C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x001230c0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(s2, a0, task::kWork);
    lw(v1, s2, 0);
    v0 = 4;
    if (v1 != v0) {
        // 0x001230f0
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x001232d8
            charge(ctx, 3);
            lw(v0, s2, 16);
            if (v0 != 0) {
                // 0x001232e4
                charge(ctx, 4);
                v0 = addiu(v0, -5);
                sw(v0, s2, 16);
                if (i64(v0) < 0) {
                    // 0x001232f4
                    charge(ctx, 1);
                    sw(zero, s2, 16);
                }
            }
            // 0x001232f8
            charge(ctx, 34);
            lh(s1, s2, 16);
            lwc1(f0, gp, g::kStatusStripX);  // 0x7CDFA0
            cvt_s_w(f12, f0);
            mtc1(zero, f13);
            a3 = s1 & 0xFF;
            v0 = 0x42D00000;
            mtc1(v0, f14);
            a0 = s3;
            v0 = 0x830000;
            lw(a1, v0, 15256);  // 0x833B98
            a2 = 30;
            jal(ctx, 0x123324u, gen::fn_sprDrawSpriteBasic_001159f0);
            lw(v0, gp, g::kStatusStripX);  // 0x7CDFA0
            v0 = addiu(v0, 640);
            mtc1(v0, f0);
            cvt_s_w(f12, f0);
            mtc1(zero, f13);
            a3 = s1 & 0xFF;
            v0 = 0x42D00000;
            mtc1(v0, f14);
            a0 = s3;
            v0 = 0x830000;
            lw(a1, v0, 15256);  // 0x833B98
            a2 = 30;
            jal(ctx, 0x123360u, gen::fn_sprDrawSpriteBasic_001159f0);
            lw(v0, gp, g::kStatusStripX);  // 0x7CDFA0
            v0 = addiu(v0, -1);
            sw(v0, gp, g::kStatusStripX);  // 0x7CDFA0
            at = slti(v0, -400);
            if (at != 0) {
                // 0x00123380
                charge(ctx, 2);
                v0 = addiu(v0, 640);
                sw(v0, gp, g::kStatusStripX);  // 0x7CDFA0
            }
            // 0x00123388
            charge(ctx, 4);
            lw(v1, s2, 4);
            v0 = 1;
            if (v1 == v0) {
                // 0x001233ec
                charge(ctx, 15);
                lw(a0, s2, 20);
                jal(ctx, 0x1233F0u, gen::fn_sub_128010_00128010);
                mtc1(zero, f12);
                sw(zero, sp, 0x58);
                sw(zero, sp, 0x5C);
                sw(zero, s2, 4);
                a0 = s0;
                a1 = 6334;
                ld(a2, sp, 0x58);
                a3 = 1;
                t0 = a3;
                jal(ctx, 0x12341Cu, gen::fn_sub_127B00_00127b00);
                sw(v0, s2, 20);
            } else {
                // 0x00123398
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x001233a8
                    charge(ctx, 17);
                    lw(a0, s2, 20);
                    jal(ctx, 0x1233ACu, gen::fn_sub_127AD0_00127ad0);
                    mtc1(zero, f12);
                    sw(zero, sp, 0x58);
                    sw(zero, sp, 0x5C);
                    a3 = 1;
                    sw(a3, s2, 4);
                    a0 = s0;
                    a1 = 6334;
                    ld(a2, sp, 0x58);
                    t0 = 0;
                    jal(ctx, 0x1233D8u, gen::fn_sub_128040_00128040);
                    sw(v0, s2, 20);
                } else {
                    // 0x001233a0
                    charge(ctx, 2);
                }
            }
            // 0x00123428
            charge(ctx, 4);
            v0 = 1;
            sw(v0, s2, 0);
        } else {
            // 0x001230fc
            charge(ctx, 3);
            a3 = 1;
            if (v1 == a3) {
                // 0x00123164
                charge(ctx, 3);
                lw(v0, s2, 16);
                if (v0 != 0) {
                    // 0x00123170
                    charge(ctx, 4);
                    v0 = addiu(v0, -5);
                    sw(v0, s2, 16);
                    if (i64(v0) < 0) {
                        // 0x00123180
                        charge(ctx, 1);
                        sw(zero, s2, 16);
                    }
                }
                // 0x00123184
                charge(ctx, 34);
                lh(s0, s2, 16);
                lwc1(f0, gp, g::kStatusStripX);  // 0x7CDFA0
                cvt_s_w(f12, f0);
                mtc1(zero, f13);
                a3 = s0 & 0xFF;
                v0 = 0x42D00000;
                mtc1(v0, f14);
                a0 = s1;
                v0 = 0x830000;
                lw(a1, v0, 15256);  // 0x833B98
                a2 = 30;
                jal(ctx, 0x1231B0u, gen::fn_sprDrawSpriteBasic_001159f0);
                lw(v0, gp, g::kStatusStripX);  // 0x7CDFA0
                v0 = addiu(v0, 640);
                mtc1(v0, f0);
                cvt_s_w(f12, f0);
                mtc1(zero, f13);
                a3 = s0 & 0xFF;
                v0 = 0x42D00000;
                mtc1(v0, f14);
                a0 = s1;
                v0 = 0x830000;
                lw(a1, v0, 15256);  // 0x833B98
                a2 = 30;
                jal(ctx, 0x1231ECu, gen::fn_sprDrawSpriteBasic_001159f0);
                lw(v0, gp, g::kStatusStripX);  // 0x7CDFA0
                v0 = addiu(v0, -1);
                sw(v0, gp, g::kStatusStripX);  // 0x7CDFA0
                at = slti(v0, -400);
                if (at != 0) {
                    // 0x0012320c
                    charge(ctx, 2);
                    v0 = addiu(v0, 640);
                    sw(v0, gp, g::kStatusStripX);  // 0x7CDFA0
                }
                // 0x00123214
                charge(ctx, 3);
                lw(v0, s2, 4);
                if (v0 != 0) {
                    // 0x00123234
                    charge(ctx, 3);
                    lw(a0, s2, 20);
                    jal(ctx, 0x123238u, gen::fn_sub_128030_00128030);
                } else {
                    // 0x00123220
                    charge(ctx, 5);
                    lw(a0, s2, 20);
                    jal(ctx, 0x123224u, gen::fn_sub_127AF0_00127af0);
                }
                // 0x00123240
                charge(ctx, 3);
                v1 = si(-1);
                if (v0 != v1) {
                    // 0x0012329c
                    charge(ctx, 3);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x001232a8
                        charge(ctx, 3);
                        lw(v0, s2, 4);
                        if (v0 != v1) {
                            // 0x001232b4
                            charge(ctx, 2);
                            if (v0 == 0) {
                                goto L_001232c4;
                            }
                            // 0x001232bc
                            charge(ctx, 2);
                            goto L_001232c8;
                        }
                    L_001232c4:
                        charge(ctx, 1);
                        sw(zero, s2, 28);
                    L_001232c8:
                        charge(ctx, 4);
                        v0 = 2;
                        sw(v0, s2, 0);
                    }
                } else {
                    // 0x0012324c
                    charge(ctx, 4);
                    lw(v1, s2, 4);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x00123280
                        charge(ctx, 3);
                        lw(a0, s2, 20);
                        jal(ctx, 0x123284u, gen::fn_sub_127FF0_00127ff0);
                    } else {
                        // 0x0012325c
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x0012326c
                            charge(ctx, 5);
                            lw(a0, s2, 20);
                            jal(ctx, 0x123270u, gen::fn_sub_127AB0_00127ab0);
                        } else {
                            // 0x00123264
                            charge(ctx, 2);
                        }
                    }
                    // 0x0012328c
                    charge(ctx, 4);
                    v0 = 4;
                    sw(v0, s2, 0);
                }
            } else {
                // 0x00123108
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x00123118
                    charge(ctx, 19);
                    mtc1(zero, f12);
                    sw(zero, sp, 0x58);
                    sw(zero, sp, 0x5C);
                    v0 = 320;
                    sw(v0, gp, g::kStatusStripX);  // 0x7CDFA0
                    sw(zero, s2, 4);
                    a1 = 6334;
                    ld(a2, sp, 0x58);
                    t0 = 0;
                    jal(ctx, 0x12313Cu, gen::fn_sub_127B00_00127b00);
                    sw(v0, s2, 20);
                    v0 = 30;
                    sw(v0, s2, 8);
                    sw(zero, s2, 16);
                    v0 = 1;
                    sw(v0, s2, 0);
                } else {
                    // 0x00123110
                    charge(ctx, 2);
                }
            }
        }
        goto L_00123514;
    }
    // 0x00123438
    charge(ctx, 4);
    lw(v0, s2, 16);
    v1 = 255;
    if (v0 != v1) {
        // 0x00123448
        charge(ctx, 5);
        v0 = addiu(v0, 5);
        sw(v0, s2, 16);
        at = slti(v0, 256);
        if (at == 0) {
            // 0x0012345c
            charge(ctx, 1);
            sw(v1, s2, 16);
        }
    }
    // 0x00123460
    charge(ctx, 34);
    lh(s0, s2, 16);
    lwc1(f0, gp, g::kStatusStripX);  // 0x7CDFA0
    cvt_s_w(f12, f0);
    mtc1(zero, f13);
    a3 = s0 & 0xFF;
    v0 = 0x42D00000;
    mtc1(v0, f14);
    a0 = s1;
    v0 = 0x830000;
    lw(a1, v0, 15256);  // 0x833B98
    a2 = 30;
    jal(ctx, 0x12348Cu, gen::fn_sprDrawSpriteBasic_001159f0);
    lw(v0, gp, g::kStatusStripX);  // 0x7CDFA0
    v0 = addiu(v0, 640);
    mtc1(v0, f0);
    cvt_s_w(f12, f0);
    mtc1(zero, f13);
    a3 = s0 & 0xFF;
    v0 = 0x42D00000;
    mtc1(v0, f14);
    a0 = s1;
    v0 = 0x830000;
    lw(a1, v0, 15256);  // 0x833B98
    a2 = 30;
    jal(ctx, 0x1234C8u, gen::fn_sprDrawSpriteBasic_001159f0);
    lw(v0, gp, g::kStatusStripX);  // 0x7CDFA0
    v0 = addiu(v0, -1);
    sw(v0, gp, g::kStatusStripX);  // 0x7CDFA0
    at = slti(v0, -400);
    if (at != 0) {
        // 0x001234e8
        charge(ctx, 2);
        v0 = addiu(v0, 640);
        sw(v0, gp, g::kStatusStripX);  // 0x7CDFA0
    }
    // 0x001234f0
    charge(ctx, 6);
    lw(a0, s2, 20);
    jal(ctx, 0x1234F4u, gen::fn_kwlnTaskGetState_00195290);
    v1 = 3;
    if (v0 != v1) {
    L_00123514:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00123508
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x00123518 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00123540 sub_123540 -- 44 bytes; frame 0x10: ra sp+0x0
// Destroy of "H_CampPcStatusRoot": frees the work.
void sub_123540(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00123540
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, task::kWork);
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x123554u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00123570 sub_123570 -- 196 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_CreatePcStatusRootTask] (parent, priority, pc): creates "H_CampPcStatusRoot" (36-byte work, update
// sub_1230C0), +12 = the party member.
void sub_123570(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00123570
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
    a1 = 36;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x1235A8u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001235c8
        charge(ctx, 13);
        a0 = s3;
        a1 = 0x5E0000;
        a1 = addiu(a1, -20464);  // "H_CampPcStatusRoot"
        a2 = s2;
        a3 = 0x120000;
        a3 = addiu(a3, 12480);  // &sub_1230C0
        t0 = 0x120000;
        t0 = addiu(t0, 13632);  // &sub_123540
        t1 = s0;
        jal(ctx, 0x1235ECu, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x00123608
            charge(ctx, 3);
            v1 = dsll32(s1, 16);
            v1 = dsra32(v1, 16);
            sw(v1, s0, 12);
        } else {
            // 0x001235fc
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x001235bc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00123614 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00123B70 sub_123B70 -- 1032 bytes; frame 0x80: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// (xy, pc, extra, alpha): the SP numbers of a party member: the frame (sprite 5 of 0x833B90), the current SP
// (sub_16C570, datGetPcSp) and the maximum (sub_16C670, datGetPcMaxSp) as up to three digits of sprite font 2 (sprite
// 11 + digit; leading zeros suppressed), the maximum tinted (sub_115AD0, 102); a non-zero `extra` is drawn first by
// sub_113A30(-256, extra, 10).
void sub_123B70(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00123b70
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x78);
    mov_s(f21, f12);
    s4 = a1;
    s3 = a3;
    if (a2 != 0) {
        // 0x00123bac
        charge(ctx, 27);
        v0 = 0x43440000;
        mtc1(v0, f1);
        lwc1(f0, sp, 0x78);
        add_s(f1, f1, f0);
        v0 = 76;
        v0 = subu(v0, a2);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        add_s(f13, f1, f0);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        sub_s(f12, f21, f0);
        v0 = 0x42AE0000;
        mtc1(v0, f1);
        lwc1(f0, sp, 0x7C);
        add_s(f1, f1, f0);
        v0 = 0x41400000;
        mtc1(v0, f0);
        sub_s(f14, f1, f0);
        a0 = si(-256);
        a1 = a2;
        a2 = 10;
        jal(ctx, 0x123C10u, gen::fn_sub_113A30_00113a30);
    }
    // 0x00123c18
    charge(ctx, 30);
    lwc1(f20, sp, 0x7C);
    v0 = 0x43430000;
    mtc1(v0, f1);
    lwc1(f0, sp, 0x78);
    add_s(f12, f1, f0);
    v0 = 0x42AE0000;
    mtc1(v0, f0);
    add_s(f1, f0, f20);
    v0 = 0x41400000;
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s3 & 0xFF;
    a0 = s2;
    v0 = 0x830000;
    lw(a1, v0, 15248);  // 0x833B90
    a2 = 5;
    mov_s(f14, f21);
    jal(ctx, 0x123C64u, gen::fn_sprDrawSpriteBasic_001159f0);
    a0 = dsll32(s4, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x123C74u, gen::fn_sub_16C570_0016c570);
    s0 = v0 & 0xFFFF;
    s1 = 0;
    v0 = slti(s0, 100);
    if (v0 == 0) {
        // 0x00123c90
        charge(ctx, 29);
        s1 = 1;
        a0 = 2;
        jal(ctx, 0x123C98u, gen::fn_sprFontGetFile_001120a0);
        v1 = 100;
        div(s0, v1);
        mflo(v1);
        a2 = addiu(v1, 11);
        v1 = 0x429E0000;
        mtc1(v1, f1);
        lwc1(f0, sp, 0x78);
        add_s(f12, f1, f0);
        v1 = 0x42AA0000;
        mtc1(v1, f0);
        add_s(f1, f0, f20);
        v1 = 0x41400000;
        mtc1(v1, f0);
        sub_s(f13, f1, f0);
        a3 = s3 & 0xFF;
        a0 = s2;
        a1 = v0;
        mov_s(f14, f21);
        jal(ctx, 0x123CF0u, gen::fn_sprDrawSpriteBasic_001159f0);
        v0 = 100;
        div(s0, v0);
        mfhi(s0);
    }
    // 0x00123d04
    charge(ctx, 3);
    at = slti(s0, 10);
    if (at != 0) {
        // 0x00123d10
        charge(ctx, 2);
        if (s1 != 0) {
            goto L_00123d18;
        }
        goto L_00123d94;
    }
L_00123d18:
    charge(ctx, 31);
    a0 = 2;
    jal(ctx, 0x123D1Cu, gen::fn_sprFontGetFile_001120a0);
    v1 = 10;
    div(s0, v1);
    mflo(v1);
    a2 = addiu(v1, 11);
    v1 = 0x41700000;
    mtc1(v1, f2);
    v1 = 0x429E0000;
    mtc1(v1, f1);
    lwc1(f0, sp, 0x78);
    add_s(f0, f1, f0);
    add_s(f12, f2, f0);
    v1 = 0x42AA0000;
    mtc1(v1, f0);
    add_s(f1, f0, f20);
    v1 = 0x41400000;
    mtc1(v1, f0);
    sub_s(f13, f1, f0);
    a3 = s3 & 0xFF;
    a0 = s2;
    a1 = v0;
    mov_s(f14, f21);
    jal(ctx, 0x123D80u, gen::fn_sprDrawSpriteBasic_001159f0);
    v0 = 10;
    div(s0, v0);
    mfhi(s0);
L_00123d94:
    charge(ctx, 38);
    v0 = 0x42AA0000;
    mtc1(v0, f0);
    add_s(f1, f0, f20);
    v0 = 0x41400000;
    mtc1(v0, f0);
    sub_s(f20, f1, f0);
    a0 = 2;
    jal(ctx, 0x123DB8u, gen::fn_sprFontGetFile_001120a0);
    v1 = 10;
    div(s0, v1);
    mfhi(v1);
    a2 = addiu(v1, 11);
    v1 = 0x41F00000;
    mtc1(v1, f2);
    v1 = 0x429E0000;
    mtc1(v1, f1);
    lwc1(f0, sp, 0x78);
    add_s(f0, f1, f0);
    add_s(f12, f2, f0);
    a3 = s3 & 0xFF;
    a0 = s2;
    a1 = v0;
    mov_s(f13, f20);
    mov_s(f14, f21);
    jal(ctx, 0x123E00u, gen::fn_sprDrawSpriteBasic_001159f0);
    a0 = dsll32(s4, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x123E10u, gen::fn_sub_16C670_0016c670);
    s1 = v0 & 0xFFFF;
    s0 = 0;
    v0 = slti(s1, 100);
    if (v0 == 0) {
        // 0x00123e2c
        charge(ctx, 23);
        s0 = 1;
        a0 = 2;
        jal(ctx, 0x123E34u, gen::fn_sprFontGetFile_001120a0);
        v1 = 100;
        div(s1, v1);
        mflo(v1);
        a2 = addiu(v1, 11);
        v1 = 0x430A0000;
        mtc1(v1, f1);
        lwc1(f0, sp, 0x78);
        add_s(f12, f1, f0);
        a3 = s3 & 0xFF;
        a0 = s2;
        a1 = v0;
        mov_s(f13, f20);
        t0 = 102;
        mov_s(f14, f21);
        jal(ctx, 0x123E74u, gen::fn_sub_115AD0_00115ad0);  // sprite draw with a tint
        v0 = 100;
        div(s1, v0);
        mfhi(s1);
    }
    // 0x00123e88
    charge(ctx, 3);
    at = slti(s1, 10);
    if (at != 0) {
        // 0x00123e94
        charge(ctx, 2);
        if (s0 != 0) {
            goto L_00123e9c;
        }
        goto L_00123ef4;
    }
L_00123e9c:
    charge(ctx, 22);
    a0 = 2;
    jal(ctx, 0x123EA0u, gen::fn_sprFontGetFile_001120a0);
    v1 = 10;
    div(s1, v1);
    mflo(v1);
    a2 = addiu(v1, 11);
    v1 = 0x41700000;
    mtc1(v1, f2);
    v1 = 0x430A0000;
    mtc1(v1, f1);
    lwc1(f0, sp, 0x78);
    add_s(f0, f1, f0);
    add_s(f12, f2, f0);
    a3 = s3 & 0xFF;
    a0 = s2;
    a1 = v0;
    mov_s(f13, f20);
    t0 = 102;
    mov_s(f14, f21);
    jal(ctx, 0x123EECu, gen::fn_sub_115AD0_00115ad0);  // sprite draw with a tint
L_00123ef4:
    charge(ctx, 33);
    a0 = 2;
    jal(ctx, 0x123EF8u, gen::fn_sprFontGetFile_001120a0);
    v1 = 10;
    div(s1, v1);
    mfhi(v1);
    a2 = addiu(v1, 11);
    v1 = 0x41F00000;
    mtc1(v1, f2);
    v1 = 0x430A0000;
    mtc1(v1, f1);
    lwc1(f0, sp, 0x78);
    add_s(f0, f1, f0);
    add_s(f12, f2, f0);
    a3 = s3 & 0xFF;
    a0 = s2;
    a1 = v0;
    mov_s(f13, f20);
    t0 = 102;
    mov_s(f14, f21);
    jal(ctx, 0x123F44u, gen::fn_sub_115AD0_00115ad0);  // sprite draw with a tint
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00123F80 sub_123F80 -- 272 bytes; frame 0x60: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// (xy, pc, alpha): the condition icon of a party member: sub_16C920 (0..5) -> sprite 11, 13, 12, 16, 14, 15 of
// 0x833B90, else 43 (jump table 0x7B5AF0).
void sub_123F80(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20};
    // 0x00123f80
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x58);
    mov_s(f20, f12);
    s2 = a2;
    s0 = 43;
    a0 = a1;
    jal(ctx, 0x123FACu, gen::fn_sub_16C920_0016c920);
    v0 = v0 & 0xFFFF;
    at = sltiu(v0, 6);
    if (at != 0) {
        // 0x00123fc4
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 23280);  // &0x7B5AF0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x123FE0u:  // table[0]
            // 0x00123fe0
            charge(ctx, 3);
            s0 = 11;
            break;
        case 0x123FECu:  // table[1]
            // 0x00123fec
            charge(ctx, 3);
            s0 = 13;
            break;
        case 0x123FF8u:  // table[2]
            // 0x00123ff8
            charge(ctx, 3);
            s0 = 12;
            break;
        case 0x124004u:  // table[3]
            // 0x00124004
            charge(ctx, 3);
            s0 = 16;
            break;
        case 0x124010u:  // table[4]
            // 0x00124010
            charge(ctx, 3);
            s0 = 14;
            break;
        case 0x12401Cu:  // table[5]
            // 0x0012401c
            charge(ctx, 1);
            s0 = 15;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    }
    // 0x00124020
    charge(ctx, 28);
    v0 = 0x43380000;
    mtc1(v0, f1);
    lwc1(f0, sp, 0x58);
    add_s(f12, f1, f0);
    v0 = 0x42B00000;
    mtc1(v0, f1);
    lwc1(f0, sp, 0x5C);
    add_s(f1, f1, f0);
    v0 = 0x41400000;
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s2 & 0xFF;
    a0 = s1;
    v0 = 0x830000;
    lw(a1, v0, 15248);  // 0x833B90
    a2 = s0;
    mov_s(f14, f20);
    jal(ctx, 0x124068u, gen::fn_sprDrawSpriteBasic_001159f0);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00124090 sub_124090 -- 732 bytes; frame 0x90: ra sp+0x70, s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// (xy, pc, z in $f12): the sparkle ring of a party member whose status byte (sub_16C970) has bit 0x80: 12 particles on
// a 100-frame cycle (gp-19852), each in its second half moving outward on a circle (sinf / cosf) and fading, sprites
// 7..9 of 0x833B90 through sprCreateHandle / sub_1127D0 / sub_115980.
void sub_124090(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24};
    // 0x00124090
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x70);
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
    sd(a0, sp, 0x88);
    mov_s(f22, f12);
    lwc1(f20, sp, 0x8C);
    a0 = a1;
    jal(ctx, 0x1240D0u, gen::fn_sub_16C970_0016c970);
    v1 = v0 & 0x80;
    if (v1 != 0) {
        // 0x001240e4
        charge(ctx, 18);
        v1 = 0x43780000;
        mtc1(v1, f1);
        lwc1(f0, sp, 0x88);
        add_s(f2, f1, f0);
        v1 = 0x434E0000;
        mtc1(v1, f0);
        add_s(f1, f0, f20);
        v1 = 0x435B0000;
        mtc1(v1, f0);
        sub_s(f1, f1, f0);
        lw(v1, gp, g::kSparkleFrame);  // 0x7CDF64
        v1 = addiu(v1, 1);
        sw(v1, gp, g::kSparkleFrame);  // 0x7CDF64
        v1 = slti(v1, 100);
        if (v1 == 0) {
            // 0x0012412c
            charge(ctx, 1);
            sw(zero, gp, g::kSparkleFrame);  // 0x7CDF64
        }
        // 0x00124130
        charge(ctx, 11);
        s3 = 0;
        v1 = 0x41880000;
        mtc1(v1, f0);
        add_s(f21, f0, f2);
        v1 = 0x42640000;
        mtc1(v1, f0);
        add_s(f20, f0, f1);
        for (;;) {
            // 0x00124328
            charge(ctx, 3);
            v1 = slti(s3, 12);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0012415c
            charge(ctx, 10);
            v1 = sll(s3, 4);
            a0 = subu(v1, s3);
            lw(v1, gp, g::kSparkleFrame);  // 0x7CDF64
            a0 = addu(v1, a0);
            v1 = 100;
            div(a0, v1);
            mfhi(s2);
            at = slti(s2, 51);
            if (at == 0) {
                // 0x00124184
                charge(ctx, 9);
                v0 = 3;
                div(s3, v0);
                mflo(v1);
                v0 = sll(v1, 2);
                v0 = addu(v0, v1);
                v1 = sll(v0, 3);
                v0 = sra(v1, 2);
                if (i64(v1) < 0) {
                    // 0x001241a8
                    charge(ctx, 2);
                    v0 = addiu(v1, 3);
                    v0 = sra(v0, 2);
                }
                // 0x001241b0
                charge(ctx, 43);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x42200000;
                mtc1(v0, f0);
                add_s(f1, f0, f1);
                lwc1(f0, gp, -32184);  // 0x7CAF38
                mul_s(f1, f0, f1);
                v0 = 0x43340000;
                mtc1(v0, f0);
                div_s(f24, f1, f0);
                mov_s(f12, f24);
                jal(ctx, 0x1241F0u, gen::fn_sinf_0052e878);
                mov_s(f23, f0);
                mov_s(f12, f24);
                jal(ctx, 0x124200u, gen::fn_cosf_0052e6d8);
                a0 = addiu(s2, -50);
                v0 = sll(a0, 2);
                v1 = addu(v0, a0);
                v0 = sll(v1, 2);
                v0 = addu(v1, v0);
                v1 = sll(v0, 1);
                v0 = 50;
                div(v1, v0);
                mflo(v0);
                mtc1(v0, f1);
                cvt_s_w(f1, f1);
                mul_s(f0, f1, f0);
                cvt_w_s(f0, f0);
                mfc1(s1, f0);
                mul_s(f0, f1, f23);
                cvt_w_s(f0, f0);
                mfc1(s0, f0);
                at = slti(a0, 10);
                if (at == 0) {
                    // 0x00124280
                    charge(ctx, 3);
                    at = slti(a0, 40);
                    if (at == 0) {
                        // 0x00124298
                        charge(ctx, 6);
                        v1 = addiu(s2, -90);
                        v0 = sll(v1, 8);
                        v1 = subu(v0, v1);
                        v0 = 10;
                        div(v1, v0);
                        mflo(s2);
                    } else {
                        // 0x0012428c
                        charge(ctx, 3);
                        s2 = 0;
                    }
                } else {
                    // 0x0012425c
                    charge(ctx, 9);
                    v0 = sll(a0, 8);
                    v1 = subu(v0, a0);
                    v0 = 10;
                    div(v1, v0);
                    mflo(v1);
                    v0 = 255;
                    s2 = subu(v0, v1);
                }
                // 0x001242b0
                charge(ctx, 29);
                v0 = 3;
                div(s3, v0);
                mfhi(v0);
                a2 = addiu(v0, 7);
                a0 = 0;
                v0 = 0x830000;
                lw(a1, v0, 15248);  // 0x833B90
                jal(ctx, 0x1242CCu, gen::fn_sprCreateHandle_001158b0);
                s4 = v0;
                swc1(f22, v0, 44);
                mtc1(s1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f21, f0);
                swc1(f0, v0, 16);
                mtc1(s0, f0);
                cvt_s_w(f0, f0);
                sub_s(f0, f20, f0);
                swc1(f0, v0, 20);
                sb(s2, v0, 24);
                a0 = s4;
                a1 = 1;
                jal(ctx, 0x124310u, gen::fn_sub_1127D0_001127d0);  // sprDrawSprite
                a0 = s4;
                jal(ctx, 0x12431Cu, gen::fn_sub_115980_00115980);  // release the sprite handle
            }
            // 0x00124324
            charge(ctx, 1);
            s3 = addiu(s3, 1);
        }
    }
    // 0x00124334 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    ld(ra, sp, 0x70);
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
    sp = addiu(sp, 0x90);
}

// 0x00124E60 sub_124E60 -- 364 bytes; frame 0x70: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// (xy, persona record, alpha): the persona level (+4) as one or two digits of sprite font 2.
void sub_124E60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00124e60
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x68);
    mov_s(f21, f12);
    s3 = a1;
    s2 = a2;
    lbu(s0, a1, 4);
    v0 = slti(s0, 10);
    if (v0 != 0) {
        // 0x00124f50
        charge(ctx, 21);
        a0 = 2;
        jal(ctx, 0x124F54u, gen::fn_sprFontGetFile_001120a0);
        v1 = 10;
        div(s0, v1);
        mfhi(v1);
        a2 = addiu(v1, 11);
        v1 = 0x42960000;
        mtc1(v1, f1);
        lwc1(f0, sp, 0x68);
        add_s(f12, f1, f0);
        v1 = 0x42FE0000;
        mtc1(v1, f1);
        lwc1(f0, sp, 0x6C);
        add_s(f13, f1, f0);
        a3 = s2 & 0xFF;
        a0 = s1;
        a1 = v0;
        mov_s(f14, f21);
        jal(ctx, 0x124F9Cu, gen::fn_sprDrawSpriteBasic_001159f0);
    } else {
        // 0x00124ea0
        charge(ctx, 44);
        lwc1(f1, sp, 0x6C);
        v0 = 0x42FE0000;
        mtc1(v0, f0);
        add_s(f20, f0, f1);
        a0 = 2;
        jal(ctx, 0x124EB8u, gen::fn_sprFontGetFile_001120a0);
        v1 = 10;
        div(s0, v1);
        mflo(v1);
        a2 = addiu(v1, 11);
        v1 = 0x42860000;
        mtc1(v1, f1);
        lwc1(f0, sp, 0x68);
        add_s(f12, f1, f0);
        a3 = s2 & 0xFF;
        a0 = s1;
        a1 = v0;
        mov_s(f13, f20);
        mov_s(f14, f21);
        jal(ctx, 0x124EF4u, gen::fn_sprDrawSpriteBasic_001159f0);
        a0 = 2;
        jal(ctx, 0x124F00u, gen::fn_sprFontGetFile_001120a0);
        lbu(a0, s3, 4);
        v1 = 10;
        div(a0, v1);
        mfhi(v1);
        a2 = addiu(v1, 11);
        v1 = 0x42A40000;
        mtc1(v1, f1);
        lwc1(f0, sp, 0x68);
        add_s(f12, f1, f0);
        a3 = s2 & 0xFF;
        a0 = s1;
        a1 = v0;
        mov_s(f13, f20);
        mov_s(f14, f21);
        jal(ctx, 0x124F40u, gen::fn_sprDrawSpriteBasic_001159f0);
    }
    // 0x00124fa4 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00125740 sub_125740 -- 1016 bytes; frame 0xA0: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// (xy, persona record, frame): the persona panel's 9-frame reveal from frame 15: the frame (sprite 1, sliding in), the
// arcana card (file 0x833B88, sprite sub_173280(id) - 1), the level digits and the name (sub_124FD0) with their own
// fades.
void sub_125740(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00125740
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x78);
    mov_s(f20, f12);
    s0 = a1;
    a1 = dsll32(a2, 16);
    a1 = dsra32(a1, 16);
    v1 = slti(a1, 15);
    if (v1 == 0) {
        // 0x00125784
        charge(ctx, 6);
        v0 = addiu(a1, -15);
        s2 = dsll32(v0, 16);
        s2 = dsra32(s2, 16);
        at = slti(s2, 3);
        if (at == 0) {
            // 0x001257fc
            charge(ctx, 2);
            a2 = 0;
            sd(a0, sp, 0x98);
        } else {
            // 0x0012579c
            charge(ctx, 24);
            v0 = sll(s2, 8);
            v0 = subu(v0, s2);
            a1 = 3;
            div(v0, a1);
            mflo(v1);
            v0 = 255;
            a2 = subu(v0, v1);
            v1 = subu(a1, s2);
            v0 = sll(v1, 2);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);
            div1(v0, a1);
            mflo1(v0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            swc1(f1, sp, 0x98);
            lwc1(f0, sp, 0x78);
            sub_s(f0, f0, f1);
            swc1(f0, sp, 0x98);
            lwc1(f0, sp, 0x7C);
            swc1(f0, sp, 0x9C);
        }
        // 0x00125804
        charge(ctx, 19);
        ld(v0, sp, 0x98);
        sd(v0, sp, 0x90);
        v0 = 0x41B00000;
        mtc1(v0, f1);
        lwc1(f0, sp, 0x90);
        add_s(f12, f1, f0);
        v0 = 0x42EA0000;
        mtc1(v0, f1);
        lwc1(f0, sp, 0x94);
        add_s(f13, f1, f0);
        a3 = a2 & 0xFF;
        v0 = 0x830000;
        lw(a1, v0, 15248);  // 0x833B90
        a2 = 1;
        mov_s(f14, f20);
        jal(ctx, 0x125840u, gen::fn_sprDrawSpriteBasic_001159f0);
        if (i64(s2) > 0) {
            // 0x00125850
            charge(ctx, 3);
            at = slti(s2, 5);
            if (at == 0) {
                // 0x001258e4
                charge(ctx, 3);
                s1 = 0;
                ld(v0, sp, 0x78);
                sd(v0, sp, 0x98);
            } else {
                // 0x0012585c
                charge(ctx, 8);
                a0 = dsll32(s2, 16);
                a0 = dsra32(a0, 16);
                v1 = addiu(a0, -1);
                v0 = sll(v1, 8);
                v0 = subu(v0, v1);
                v1 = sra(v0, 2);
                if (i64(v0) < 0) {
                    // 0x0012587c
                    charge(ctx, 2);
                    v0 = addiu(v0, 3);
                    v1 = sra(v0, 2);
                }
                // 0x00125884
                charge(ctx, 11);
                v0 = 255;
                s1 = subu(v0, v1);
                v0 = 5;
                v1 = subu(v0, a0);
                v0 = sll(v1, 4);
                v0 = subu(v0, v1);
                v1 = sll(v0, 2);
                v0 = dsll32(v0, 2);
                v0 = dsra32(v0, 2);
                if (i64(v1) < 0) {
                    // 0x001258b0
                    charge(ctx, 2);
                    v0 = addiu(v1, 3);
                    v0 = sra(v0, 2);
                }
                // 0x001258b8
                charge(ctx, 11);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                swc1(f1, sp, 0x98);
                lwc1(f0, sp, 0x78);
                sub_s(f0, f0, f1);
                swc1(f0, sp, 0x98);
                lwc1(f0, sp, 0x7C);
                swc1(f0, sp, 0x9C);
            }
            // 0x001258f0
            charge(ctx, 23);
            ld(v0, sp, 0x98);
            sd(v0, sp, 0x88);
            v0 = 0x830000;
            lw(s3, v0, 15240);  // 0x833B88
            lhu(a0, s0, 2);
            jal(ctx, 0x125904u, gen::fn_sub_173280_00173280);
            v0 = v0 & 0xFF;
            a2 = addiu(v0, -1);
            v0 = 0x42D20000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x88);
            add_s(f12, f1, f0);
            v0 = 0x430E0000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x8C);
            add_s(f13, f1, f0);
            a3 = s1 & 0xFF;
            a0 = s4;
            a1 = s3;
            mov_s(f14, f20);
            jal(ctx, 0x125944u, gen::fn_sprDrawSpriteBasic_001159f0);
        }
        // 0x0012594c
        charge(ctx, 3);
        v1 = slti(s2, 5);
        if (v1 == 0) {
            // 0x00125958
            charge(ctx, 3);
            at = slti(s2, 9);
            if (at == 0) {
                // 0x00125994
                charge(ctx, 1);
                s3 = 0;
            } else {
                // 0x00125964
                charge(ctx, 6);
                v1 = addiu(s2, -5);
                v0 = sll(v1, 8);
                v0 = subu(v0, v1);
                v1 = sra(v0, 2);
                if (i64(v0) < 0) {
                    // 0x0012597c
                    charge(ctx, 2);
                    v0 = addiu(v0, 3);
                    v1 = sra(v0, 2);
                }
                // 0x00125984
                charge(ctx, 4);
                v0 = 255;
                s3 = subu(v0, v1);
            }
            // 0x00125998
            charge(ctx, 6);
            ld(v0, sp, 0x78);
            sd(v0, sp, 0x80);
            lbu(s1, s0, 4);
            v0 = slti(s1, 10);
            if (v0 != 0) {
                // 0x00125a60
                charge(ctx, 21);
                a0 = 2;
                jal(ctx, 0x125A64u, gen::fn_sprFontGetFile_001120a0);
                v1 = 10;
                div(s1, v1);
                mfhi(v1);
                a2 = addiu(v1, 11);
                v1 = 0x42960000;
                mtc1(v1, f1);
                lwc1(f0, sp, 0x80);
                add_s(f12, f1, f0);
                v1 = 0x42FE0000;
                mtc1(v1, f1);
                lwc1(f0, sp, 0x84);
                add_s(f13, f1, f0);
                a3 = s3 & 0xFF;
                a0 = s4;
                a1 = v0;
                mov_s(f14, f20);
                jal(ctx, 0x125AACu, gen::fn_sprDrawSpriteBasic_001159f0);
            } else {
                // 0x001259b0
                charge(ctx, 44);
                lwc1(f1, sp, 0x84);
                v0 = 0x42FE0000;
                mtc1(v0, f0);
                add_s(f21, f0, f1);
                a0 = 2;
                jal(ctx, 0x1259C8u, gen::fn_sprFontGetFile_001120a0);
                v1 = 10;
                div(s1, v1);
                mflo(v1);
                a2 = addiu(v1, 11);
                v1 = 0x42860000;
                mtc1(v1, f1);
                lwc1(f0, sp, 0x80);
                add_s(f12, f1, f0);
                a3 = s3 & 0xFF;
                a0 = s4;
                a1 = v0;
                mov_s(f13, f21);
                mov_s(f14, f20);
                jal(ctx, 0x125A04u, gen::fn_sprDrawSpriteBasic_001159f0);
                a0 = 2;
                jal(ctx, 0x125A10u, gen::fn_sprFontGetFile_001120a0);
                lbu(a0, s0, 4);
                v1 = 10;
                div(a0, v1);
                mfhi(v1);
                a2 = addiu(v1, 11);
                v1 = 0x42A40000;
                mtc1(v1, f1);
                lwc1(f0, sp, 0x80);
                add_s(f12, f1, f0);
                a3 = s3 & 0xFF;
                a0 = s4;
                a1 = v0;
                mov_s(f13, f21);
                mov_s(f14, f20);
                jal(ctx, 0x125A50u, gen::fn_sprDrawSpriteBasic_001159f0);
            }
        }
        // 0x00125ab4
        charge(ctx, 3);
        v1 = slti(s2, 6);
        if (v1 == 0) {
            // 0x00125ac0
            charge(ctx, 3);
            at = slti(s2, 9);
            if (at == 0) {
                // 0x00125af4
                charge(ctx, 1);
                a2 = 0;
            } else {
                // 0x00125acc
                charge(ctx, 10);
                v1 = addiu(s2, -6);
                v0 = sll(v1, 8);
                v1 = subu(v0, v1);
                v0 = 3;
                div(v1, v0);
                mflo(v1);
                v0 = 255;
                a2 = subu(v0, v1);
            }
            // 0x00125af8
            charge(ctx, 5);
            ld(a0, sp, 0x78);
            mov_s(f12, f20);
            a1 = s0;
            jal(ctx, 0x125B04u, gen::fn_sub_124FD0_00124fd0);
        }
    }
    // 0x00125b0c (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x00125B40 sub_125B40 -- 552 bytes; frame 0x90: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// (xy, ?, persona record, alpha): the persona panel drawn at once: frame, arcana, level, name (sub_124FD0).
void sub_125B40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00125b40
    enter(ctx, 57);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x68);
    mov_s(f20, f12);
    s3 = a2;
    s2 = a3;
    sd(a0, sp, 0x88);
    v0 = 0x41B00000;
    mtc1(v0, f1);
    lwc1(f0, sp, 0x88);
    add_s(f12, f1, f0);
    v0 = 0x42EA0000;
    mtc1(v0, f1);
    lwc1(f0, sp, 0x8C);
    add_s(f13, f1, f0);
    a3 = s2 & 0xFF;
    v0 = 0x830000;
    lw(a1, v0, 15248);  // 0x833B90
    a2 = 1;
    mov_s(f14, f20);
    jal(ctx, 0x125BA8u, gen::fn_sprDrawSpriteBasic_001159f0);
    ld(v0, sp, 0x68);
    sd(v0, sp, 0x80);
    v0 = 0x830000;
    lw(s0, v0, 15240);  // 0x833B88
    lhu(a0, s3, 2);
    jal(ctx, 0x125BC4u, gen::fn_sub_173280_00173280);
    v0 = v0 & 0xFF;
    a2 = addiu(v0, -1);
    v0 = 0x42D20000;
    mtc1(v0, f1);
    lwc1(f0, sp, 0x80);
    add_s(f12, f1, f0);
    v0 = 0x430E0000;
    mtc1(v0, f1);
    lwc1(f0, sp, 0x84);
    add_s(f13, f1, f0);
    a3 = s2 & 0xFF;
    a0 = s1;
    a1 = s0;
    mov_s(f14, f20);
    jal(ctx, 0x125C04u, gen::fn_sprDrawSpriteBasic_001159f0);
    ld(v0, sp, 0x68);
    sd(v0, sp, 0x78);
    lbu(s0, s3, 4);
    v0 = slti(s0, 10);
    if (v0 != 0) {
        // 0x00125cd4
        charge(ctx, 21);
        a0 = 2;
        jal(ctx, 0x125CD8u, gen::fn_sprFontGetFile_001120a0);
        v1 = 10;
        div(s0, v1);
        mfhi(v1);
        a2 = addiu(v1, 11);
        v1 = 0x42960000;
        mtc1(v1, f1);
        lwc1(f0, sp, 0x78);
        add_s(f12, f1, f0);
        v1 = 0x42FE0000;
        mtc1(v1, f1);
        lwc1(f0, sp, 0x7C);
        add_s(f13, f1, f0);
        a3 = s2 & 0xFF;
        a0 = s1;
        a1 = v0;
        mov_s(f14, f20);
        jal(ctx, 0x125D20u, gen::fn_sprDrawSpriteBasic_001159f0);
    } else {
        // 0x00125c24
        charge(ctx, 44);
        lwc1(f1, sp, 0x7C);
        v0 = 0x42FE0000;
        mtc1(v0, f0);
        add_s(f21, f0, f1);
        a0 = 2;
        jal(ctx, 0x125C3Cu, gen::fn_sprFontGetFile_001120a0);
        v1 = 10;
        div(s0, v1);
        mflo(v1);
        a2 = addiu(v1, 11);
        v1 = 0x42860000;
        mtc1(v1, f1);
        lwc1(f0, sp, 0x78);
        add_s(f12, f1, f0);
        a3 = s2 & 0xFF;
        a0 = s1;
        a1 = v0;
        mov_s(f13, f21);
        mov_s(f14, f20);
        jal(ctx, 0x125C78u, gen::fn_sprDrawSpriteBasic_001159f0);
        a0 = 2;
        jal(ctx, 0x125C84u, gen::fn_sprFontGetFile_001120a0);
        lbu(a0, s3, 4);
        v1 = 10;
        div(a0, v1);
        mfhi(v1);
        a2 = addiu(v1, 11);
        v1 = 0x42A40000;
        mtc1(v1, f1);
        lwc1(f0, sp, 0x78);
        add_s(f12, f1, f0);
        a3 = s2 & 0xFF;
        a0 = s1;
        a1 = v0;
        mov_s(f13, f21);
        mov_s(f14, f20);
        jal(ctx, 0x125CC4u, gen::fn_sprDrawSpriteBasic_001159f0);
    }
    // 0x00125d28
    charge(ctx, 16);
    ld(a0, sp, 0x68);
    mov_s(f12, f20);
    a1 = s3;
    a2 = s2;
    jal(ctx, 0x125D38u, gen::fn_sub_124FD0_00124fd0);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x001266E0 sub_1266E0 -- 44 bytes; frame 0x10: ra sp+0x0
// Destroy of a status-page task: frees the work.
void sub_1266E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001266e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, task::kWork);
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x1266F4u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00127A40 sub_127A40 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Destroy of "H_CampStatusDraw": the file +56, the texture +64 (sub_4D0F00), the work.
void sub_127A40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00127a40
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a0, s0, 56);
    if (a0 != 0) {
        // 0x00127a5c
        charge(ctx, 3);
        jal(ctx, 0x127A5Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, s0, 56);
    }
    // 0x00127a68
    charge(ctx, 3);
    lw(a0, s0, 64);
    if (a0 != 0) {
        // 0x00127a74
        charge(ctx, 3);
        jal(ctx, 0x127A74u, gen::fn_sub_4D0F00_004d0f00);  // textureDestroy
        sw(zero, s0, 64);
    }
    // 0x00127a80
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x127A8Cu, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00127B00 sub_127B00 -- 244 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_CreateStatusDrawTask] (parent, priority, xy, a, b): creates "H_CampStatusDraw" (72-byte work, update
// sub_1269A0): +4/+8 position, +14 / +16 the two arguments, +32 = 1; clears the flash task's done flag (flash work
// +16).
void sub_127B00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00127b00
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    sd(a2, sp, 0x68);
    s2 = a3;
    s1 = t0;
    a0 = 1;
    a1 = 72;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x127B44u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00127b64
        charge(ctx, 13);
        a0 = s4;
        a1 = 0x5E0000;
        a1 = addiu(a1, -20288);  // "H_CampStatusDraw"
        a2 = s3;
        a3 = 0x120000;
        a3 = addiu(a3, 27040);  // &sub_1269A0
        t0 = 0x120000;
        t0 = addiu(t0, 31296);  // &sub_127A40
        t1 = s0;
        jal(ctx, 0x127B88u, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x00127ba4
            charge(ctx, 11);
            lwc1(f1, sp, 0x68);
            lwc1(f0, sp, 0x6C);
            swc1(f1, s0, 4);
            swc1(f0, s0, 8);
            v1 = 1;
            sw(v1, s0, 32);
            sh(s2, s0, 14);
            sh(s1, s0, 16);
            lw(v1, gp, g::kCampFlashTask);  // 0x7CDF50
            lw(v1, v1, 60);
            sw(zero, v1, 16);
        } else {
            // 0x00127b98
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00127b58
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00127bd0 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00127FC0 sub_127FC0 -- 44 bytes; frame 0x10: ra sp+0x0
// Destroy of "H_CampStatusPersonaDraw": frees the work.
void sub_127FC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00127fc0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, task::kWork);
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x127FD4u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00128040 sub_128040 -- 244 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_CreateStatusPersonaDrawTask] (parent, priority, xy, a, b): creates "H_CampStatusPersonaDraw" (32-byte work,
// update sub_127C00): +4/+8 position, +14 / +18 the two arguments, +24 = 1; clears the flash done flag.
void sub_128040(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00128040
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    sd(a2, sp, 0x68);
    s2 = a3;
    s1 = t0;
    a0 = 1;
    a1 = 32;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x128084u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001280a4
        charge(ctx, 13);
        a0 = s4;
        a1 = 0x5E0000;
        a1 = addiu(a1, -20256);  // "H_CampStatusPersonaDraw"
        a2 = s3;
        a3 = 0x120000;
        a3 = addiu(a3, 31744);  // &sub_127C00
        t0 = 0x120000;
        t0 = addiu(t0, 32704);  // &sub_127FC0
        t1 = s0;
        jal(ctx, 0x1280C8u, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x001280e4
            charge(ctx, 11);
            lwc1(f1, sp, 0x68);
            lwc1(f0, sp, 0x6C);
            swc1(f1, s0, 4);
            swc1(f0, s0, 8);
            v1 = 1;
            sw(v1, s0, 24);
            sh(s2, s0, 14);
            lw(v1, gp, g::kCampFlashTask);  // 0x7CDF50
            lw(v1, v1, 60);
            sw(zero, v1, 16);
            sh(s1, s0, 18);
        } else {
            // 0x001280d8
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00128098
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00128110 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x001281E0 sub_1281E0 -- 664 bytes; frame 0x20: ra sp+0x0
// (xy, row 0..8, alpha): one label of the persona stat table: sprite row of 0x833B98 (jump table 0x7B5B60).
void sub_1281E0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x001281e0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    sd(a0, sp, 0x18);
    mov_s(f14, f12);
    at = sltiu(a1, 9);
    if (at != 0) {
        // 0x001281fc
        charge(ctx, 7);
        a3 = 0x7B0000;
        a3 = addiu(a3, 23392);  // &0x7B5B60
        v1 = sll(a1, 2);
        v1 = addu(v1, a3);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x128218u:  // table[0]
            // 0x00128218
            charge(ctx, 16);
            v0 = 0x41E80000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x18);
            add_s(f12, f1, f0);
            v0 = 0x42300000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x1C);
            add_s(f13, f1, f0);
            a3 = a2 & 0xFF;
            v0 = 0x830000;
            lw(a1, v0, 15256);  // 0x833B98
            a2 = 0;
            jal(ctx, 0x128248u, gen::fn_sprDrawSpriteBasic_001159f0);
            break;
        case 0x128258u:  // table[1]
            // 0x00128258
            charge(ctx, 16);
            v0 = 0x428A0000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x18);
            add_s(f12, f1, f0);
            v0 = 0x42300000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x1C);
            add_s(f13, f1, f0);
            a3 = a2 & 0xFF;
            v0 = 0x830000;
            lw(a1, v0, 15256);  // 0x833B98
            a2 = 1;
            jal(ctx, 0x128288u, gen::fn_sprDrawSpriteBasic_001159f0);
            break;
        case 0x128298u:  // table[2]
            // 0x00128298
            charge(ctx, 16);
            v0 = 0x42DA0000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x18);
            add_s(f12, f1, f0);
            v0 = 0x42300000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x1C);
            add_s(f13, f1, f0);
            a3 = a2 & 0xFF;
            v0 = 0x830000;
            lw(a1, v0, 15256);  // 0x833B98
            a2 = 2;
            jal(ctx, 0x1282C8u, gen::fn_sprDrawSpriteBasic_001159f0);
            break;
        case 0x1282D8u:  // table[3]
            // 0x001282d8
            charge(ctx, 16);
            v0 = 0x431F0000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x18);
            add_s(f12, f1, f0);
            v0 = 0x42300000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x1C);
            add_s(f13, f1, f0);
            a3 = a2 & 0xFF;
            v0 = 0x830000;
            lw(a1, v0, 15256);  // 0x833B98
            a2 = 3;
            jal(ctx, 0x128308u, gen::fn_sprDrawSpriteBasic_001159f0);
            break;
        case 0x128318u:  // table[4]
            // 0x00128318
            charge(ctx, 16);
            v0 = 0x43470000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x18);
            add_s(f12, f1, f0);
            v0 = 0x42300000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x1C);
            add_s(f13, f1, f0);
            a3 = a2 & 0xFF;
            v0 = 0x830000;
            lw(a1, v0, 15256);  // 0x833B98
            a2 = 4;
            jal(ctx, 0x128348u, gen::fn_sprDrawSpriteBasic_001159f0);
            break;
        case 0x128358u:  // table[5]
            // 0x00128358
            charge(ctx, 16);
            v0 = 0x436F0000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x18);
            add_s(f12, f1, f0);
            v0 = 0x42300000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x1C);
            add_s(f13, f1, f0);
            a3 = a2 & 0xFF;
            v0 = 0x830000;
            lw(a1, v0, 15256);  // 0x833B98
            a2 = 5;
            jal(ctx, 0x128388u, gen::fn_sprDrawSpriteBasic_001159f0);
            break;
        case 0x128398u:  // table[6]
            // 0x00128398
            charge(ctx, 18);
            v0 = 279;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, sp, 0x18);
            add_s(f12, f1, f0);
            v0 = 0x42300000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x1C);
            add_s(f13, f1, f0);
            a3 = a2 & 0xFF;
            v0 = 0x830000;
            lw(a1, v0, 15256);  // 0x833B98
            a2 = 6;
            jal(ctx, 0x1283D0u, gen::fn_sprDrawSpriteBasic_001159f0);
            break;
        case 0x1283E0u:  // table[7]
            // 0x001283e0
            charge(ctx, 18);
            v0 = 319;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, sp, 0x18);
            add_s(f12, f1, f0);
            v0 = 0x42300000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x1C);
            add_s(f13, f1, f0);
            a3 = a2 & 0xFF;
            v0 = 0x830000;
            lw(a1, v0, 15256);  // 0x833B98
            a2 = 7;
            jal(ctx, 0x128418u, gen::fn_sprDrawSpriteBasic_001159f0);
            break;
        case 0x128428u:  // table[8]
            // 0x00128428
            charge(ctx, 16);
            v0 = 359;
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, sp, 0x18);
            add_s(f12, f1, f0);
            v0 = 0x42300000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x1C);
            add_s(f13, f1, f0);
            a3 = a2 & 0xFF;
            v0 = 0x830000;
            lw(a1, v0, 15256);  // 0x833B98
            a2 = 8;
            jal(ctx, 0x128460u, gen::fn_sprDrawSpriteBasic_001159f0);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x00128468 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00128480 sub_128480 -- 664 bytes; frame 0x80: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// (xy, persona, alpha): the nine resistance marks of a persona: for elements 0..6, 8, 9 the affinity word (sub_1733B0)
// -> sprite 13 (bit 26), 14 (25), 12 (24), 11 (28), 10 (27), else 15 of 0x833B98 (jump table 0x7B5B90).
void sub_128480(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x00128480
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x78);
    mov_s(f22, f12);
    s4 = a1;
    s3 = a2;
    v1 = 0x42000000;
    mtc1(v1, f1);
    lwc1(f0, sp, 0x78);
    add_s(f21, f1, f0);
    v1 = 0x42900000;
    mtc1(v1, f1);
    lwc1(f0, sp, 0x7C);
    add_s(f20, f1, f0);
    s1 = 0;
    for (;;) {
        // 0x001286dc
        charge(ctx, 3);
        v1 = sltiu(s1, 9);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001284e4
        charge(ctx, 3);
        at = sltiu(s1, 9);
        if (at != 0) {
            // 0x001284f0
            charge(ctx, 7);
            v1 = 0x7B0000;
            v1 = addiu(v1, 23440);  // &0x7B5B90
            v0 = sll(s1, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x12850Cu:  // table[0]
                // 0x0012850c
                charge(ctx, 7);
                a0 = s4;
                a1 = 0;
                jal(ctx, 0x128514u, gen::fn_sub_1733B0_001733b0);
                s0 = v0;
                break;
            case 0x128528u:  // table[1]
                // 0x00128528
                charge(ctx, 7);
                a0 = s4;
                a1 = 1;
                jal(ctx, 0x128530u, gen::fn_sub_1733B0_001733b0);
                s0 = v0;
                break;
            case 0x128544u:  // table[2]
                // 0x00128544
                charge(ctx, 7);
                a0 = s4;
                a1 = 2;
                jal(ctx, 0x12854Cu, gen::fn_sub_1733B0_001733b0);
                s0 = v0;
                break;
            case 0x128560u:  // table[3]
                // 0x00128560
                charge(ctx, 7);
                a0 = s4;
                a1 = 3;
                jal(ctx, 0x128568u, gen::fn_sub_1733B0_001733b0);
                s0 = v0;
                break;
            case 0x12857Cu:  // table[4]
                // 0x0012857c
                charge(ctx, 7);
                a0 = s4;
                a1 = 4;
                jal(ctx, 0x128584u, gen::fn_sub_1733B0_001733b0);
                s0 = v0;
                break;
            case 0x128598u:  // table[5]
                // 0x00128598
                charge(ctx, 7);
                a0 = s4;
                a1 = 5;
                jal(ctx, 0x1285A0u, gen::fn_sub_1733B0_001733b0);
                s0 = v0;
                break;
            case 0x1285B4u:  // table[6]
                // 0x001285b4
                charge(ctx, 7);
                a0 = s4;
                a1 = 6;
                jal(ctx, 0x1285BCu, gen::fn_sub_1733B0_001733b0);
                s0 = v0;
                break;
            case 0x1285D0u:  // table[7]
                // 0x001285d0
                charge(ctx, 7);
                a0 = s4;
                a1 = 8;
                jal(ctx, 0x1285D8u, gen::fn_sub_1733B0_001733b0);
                s0 = v0;
                break;
            case 0x1285ECu:  // table[8]
                // 0x001285ec
                charge(ctx, 5);
                a0 = s4;
                a1 = 9;
                jal(ctx, 0x1285F4u, gen::fn_sub_1733B0_001733b0);
                s0 = v0;
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
        // 0x00128600
        charge(ctx, 5);
        a2 = 15;
        v0 = 0x4000000;
        v0 = s0 & v0;
        if (v0 == 0) {
            // 0x00128620
            charge(ctx, 4);
            v0 = 0x2000000;
            v0 = s0 & v0;
            if (v0 == 0) {
                // 0x0012863c
                charge(ctx, 4);
                v0 = 0x1000000;
                v0 = s0 & v0;
                if (v0 == 0) {
                    // 0x00128658
                    charge(ctx, 4);
                    v0 = 0x10000000;
                    v0 = s0 & v0;
                    if (v0 == 0) {
                        // 0x00128674
                        charge(ctx, 4);
                        v0 = 0x8000000;
                        v0 = s0 & v0;
                        if (v0 != 0) {
                            // 0x00128684
                            charge(ctx, 1);
                            a2 = 10;
                        }
                    } else {
                        // 0x00128668
                        charge(ctx, 3);
                        a2 = 11;
                    }
                } else {
                    // 0x0012864c
                    charge(ctx, 3);
                    a2 = 12;
                }
            } else {
                // 0x00128630
                charge(ctx, 3);
                a2 = 14;
            }
        } else {
            // 0x00128614
            charge(ctx, 3);
            a2 = 13;
        }
        // 0x00128688
        charge(ctx, 12);
        a3 = s3 & 0xFF;
        a0 = s2;
        v0 = 0x830000;
        lw(a1, v0, 15256);  // 0x833B98
        mov_s(f12, f21);
        mov_s(f13, f20);
        mov_s(f14, f22);
        jal(ctx, 0x1286A4u, gen::fn_sprDrawSpriteBasic_001159f0);
        v1 = 2;
        if (s1 != v1) {
            // 0x001286c8
            charge(ctx, 4);
            v1 = 0x42200000;
            mtc1(v1, f0);
            add_s(f21, f21, f0);
        } else {
            // 0x001286b8
            charge(ctx, 4);
            v1 = 0x43220000;
            mtc1(v1, f21);
        }
        // 0x001286d8
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x001286e8
    charge(ctx, 12);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00129160 sub_129160 -- 584 bytes; frame 0x80: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// (xy, row, value, next, alpha): a stat bar: labels 20 / 21, the bar sprite 24 scaled to 227 * value / 99, and when
// `next` is non-zero the gain bar 16 after it.
void sub_129160(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x00129160
    enter(ctx, 102);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x78);
    mov_s(f21, f12);
    s0 = a2;
    s4 = a3;
    s3 = t0;
    v0 = sll(a1, 3);
    v0 = addu(v0, a1);
    v0 = sll(v0, 1);
    s1 = addu(v0, a1);
    lwc1(f20, sp, 0x7C);
    v0 = 0x43010000;
    mtc1(v0, f0);
    add_s(f1, f0, f20);
    mtc1(s1, f0);
    cvt_s_w(f0, f0);
    add_s(f1, f1, f0);
    v0 = 0x41C80000;
    mtc1(v0, f0);
    sub_s(f22, f1, f0);
    v0 = 0x42D00000;
    mtc1(v0, f1);
    lwc1(f0, sp, 0x78);
    add_s(f12, f1, f0);
    a3 = s3 & 0xFF;
    a0 = s2;
    v0 = 0x830000;
    lw(a1, v0, 15256);  // 0x833B98
    a2 = 20;
    mov_s(f13, f22);
    mov_s(f14, f21);
    jal(ctx, 0x12920Cu, gen::fn_sprDrawSpriteBasic_001159f0);
    v0 = 333;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x78);
    add_s(f12, f1, f0);
    a3 = s3 & 0xFF;
    a0 = s2;
    v0 = 0x830000;
    lw(a1, v0, 15256);  // 0x833B98
    a2 = 21;
    mov_s(f13, f22);
    mov_s(f14, f21);
    jal(ctx, 0x129248u, gen::fn_sprDrawSpriteBasic_001159f0);
    v0 = 227;
    mult(v1, s0, v0);
    v0 = 99;
    div(v1, v0);
    mflo(s0);
    a0 = 0;
    v0 = 0x830000;
    lw(a1, v0, 15256);  // 0x833B98
    a2 = 24;
    jal(ctx, 0x129274u, gen::fn_sprCreateHandle_001158b0);
    s2 = v0;
    swc1(f21, v0, 44);
    v1 = 0x42D80000;
    mtc1(v1, f1);
    lwc1(f0, sp, 0x78);
    add_s(f22, f1, f0);
    swc1(f22, v0, 16);
    v1 = 0x43020000;
    mtc1(v1, f0);
    add_s(f1, f0, f20);
    mtc1(s1, f0);
    cvt_s_w(f0, f0);
    add_s(f1, f1, f0);
    v1 = 0x41C80000;
    mtc1(v1, f0);
    sub_s(f20, f1, f0);
    swc1(f20, v0, 20);
    sb(s3, v0, 24);
    sh(s0, v0, 28);
    a0 = s2;
    a1 = 1;
    jal(ctx, 0x1292DCu, gen::fn_sub_1127D0_001127d0);  // sprDrawSprite
    a0 = s2;
    jal(ctx, 0x1292E8u, gen::fn_sub_115980_00115980);  // release the sprite handle
    if (s4 != 0) {
        // 0x001292f8
        charge(ctx, 32);
        v0 = 227;
        mult(v1, s4, v0);
        v0 = 99;
        div(v1, v0);
        mflo(s1);
        a0 = 0;
        v0 = 0x830000;
        lw(a1, v0, 15256);  // 0x833B98
        a2 = 16;
        jal(ctx, 0x12931Cu, gen::fn_sprCreateHandle_001158b0);
        s2 = v0;
        swc1(f21, v0, 44);
        mtc1(s0, f0);
        cvt_s_w(f0, f0);
        add_s(f1, f22, f0);
        v1 = 0x40000000;
        mtc1(v1, f0);
        add_s(f0, f0, f1);
        swc1(f0, v0, 16);
        swc1(f20, v0, 20);
        sb(s3, v0, 24);
        sh(s1, v0, 28);
        a0 = s2;
        a1 = 1;
        jal(ctx, 0x129364u, gen::fn_sub_1127D0_001127d0);  // sprDrawSprite
        a0 = s2;
        jal(ctx, 0x129370u, gen::fn_sub_115980_00115980);  // release the sprite handle
    }
    // 0x00129378 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x0012BCE0 sub_12BCE0 -- 712 bytes; frame 0x190: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// (xy, ?, persona, alpha): the persona status table: the nine labels (sub_1281E0), the resistances (sub_128480), the
// frame sprites, and the "next exp" text (sprintf of the level-99 string or of sub_173340 - sub_173330) drawn through
// sub_40EB50.
void sub_12BCE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x0012bce0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x190);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x78);
    mov_s(f20, f12);
    s1 = a2;
    s0 = a3;
    s4 = 0;
    for (;;) {
        // 0x0012bd44
        charge(ctx, 3);
        v0 = sltiu(s4, 9);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0012bd28
        charge(ctx, 7);
        ld(a0, sp, 0x78);
        mov_s(f12, f20);
        a1 = s4;
        a2 = s0;
        jal(ctx, 0x12BD38u, gen::fn_sub_1281E0_001281e0);
        s4 = addiu(s4, 1);
    }
    // 0x0012bd50
    charge(ctx, 108);
    ld(a0, sp, 0x78);
    mov_s(f12, f20);
    a1 = s1;
    a2 = s0;
    jal(ctx, 0x12BD60u, gen::fn_sub_128480_00128480);
    ld(v0, sp, 0x78);
    sd(v0, sp, 0x188);
    lwc1(f22, sp, 0x18C);
    v0 = 0x41F00000;
    mtc1(v0, f1);
    lwc1(f0, sp, 0x188);
    add_s(f21, f1, f0);
    v0 = 0x42FA0000;
    mtc1(v0, f0);
    add_s(f1, f0, f22);
    v0 = 0x41C80000;
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s0 & 0xFF;
    a0 = s2;
    v0 = 0x830000;
    lw(a1, v0, 15256);  // 0x833B98
    a2 = 18;
    mov_s(f12, f21);
    mov_s(f14, f20);
    jal(ctx, 0x12BDC0u, gen::fn_sprDrawSpriteBasic_001159f0);
    v0 = 0x43380000;
    mtc1(v0, f0);
    add_s(f1, f0, f22);
    v0 = 0x41C80000;
    mtc1(v0, f0);
    sub_s(f13, f1, f0);
    a3 = s0 & 0xFF;
    a0 = s2;
    v0 = 0x830000;
    lw(a1, v0, 15256);  // 0x833B98
    a2 = 19;
    mov_s(f12, f21);
    mov_s(f14, f20);
    jal(ctx, 0x12BE04u, gen::fn_sprDrawSpriteBasic_001159f0);
    ld(v0, sp, 0x78);
    sd(v0, sp, 0x180);
    v0 = 255;
    s2 = subu(v0, s0);
    lwc1(f1, sp, 0x180);
    v0 = 0x41400000;
    mtc1(v0, f0);
    add_s(f2, f1, f0);
    swc1(f2, sp, 0x180);
    lwc1(f1, sp, 0x184);
    v0 = 0x42C00000;
    mtc1(v0, f0);
    add_s(f1, f1, f0);
    swc1(f1, sp, 0x184);
    v0 = 0x43360000;
    mtc1(v0, f0);
    add_s(f22, f0, f1);
    v0 = 0x41A80000;
    mtc1(v0, f0);
    add_s(f21, f0, f2);
    a3 = s0 & 0xFF;
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, 15248);  // 0x833B90
    a2 = 17;
    mov_s(f12, f21);
    mov_s(f13, f22);
    mov_s(f14, f20);
    jal(ctx, 0x12BE8Cu, gen::fn_sprDrawSpriteBasic_001159f0);
    v0 = 275;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, sp, 0x180);
    add_s(f12, f1, f0);
    a3 = s0 & 0xFF;
    a0 = s3;
    v0 = 0x830000;
    lw(a1, v0, 15248);  // 0x833B90
    a2 = 34;
    mov_s(f13, f22);
    mov_s(f14, f20);
    jal(ctx, 0x12BEC8u, gen::fn_sprDrawSpriteBasic_001159f0);
    v0 = 0x437E0000;
    mtc1(v0, f0);
    add_s(f23, f0, f21);
    v0 = 0x40000000;
    mtc1(v0, f0);
    add_s(f21, f0, f22);
    lbu(v1, s1, 4);
    v0 = 99;
    if (v1 != v0) {
        // 0x0012bf18
        charge(ctx, 12);
        a0 = s1;
        jal(ctx, 0x12BF1Cu, gen::fn_sub_173340_00173340);
        s0 = v0;
        a0 = s1;
        jal(ctx, 0x12BF2Cu, gen::fn_sub_173330_00173330);
        a2 = subu(s0, v0);
        a0 = addiu(sp, 0x80);
        a1 = addiu(gp, -30344);  // "%d"
        jal(ctx, 0x12BF40u, gen::fn_sprintf_00523ac8);
    } else {
        // 0x0012bf00
        charge(ctx, 6);
        a0 = addiu(sp, 0x80);
        a1 = addiu(gp, -30336);  // &0x7CB670
        jal(ctx, 0x12BF08u, gen::fn_sprintf_00523ac8);
    }
    // 0x0012bf48
    charge(ctx, 24);
    cvt_w_s(f0, f23);
    mfc1(a0, f0);
    cvt_w_s(f0, f21);
    mfc1(a1, f0);
    a2 = s2 & 0xFF;
    mov_s(f12, f20);
    a3 = 4;
    t0 = addiu(sp, 0x80);
    t1 = 1;
    jal(ctx, 0x12BF6Cu, gen::fn_sub_40EB50_0040eb50);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x190);
}

// 0x0012DDC0 sub_12DDC0 -- 396 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// (equip work): the equipment screen's scrolling backdrop: while its tween (work +704, sub_18B700) is active, sprite
// 29 of file +688 twice, 700 px apart, the scroll x (tween +48) moving by -1 and wrapping at -700.
void sub_12DDC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0012ddc0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, 704);
    jal(ctx, 0x12DDD8u, gen::fn_sub_18B700_0018b700);  // run a tween record
    if (v0 != 0) {
        // 0x0012dde8
        charge(ctx, 78);
        a0 = 0;
        lw(a1, s1, 688);
        a2 = 29;
        jal(ctx, 0x12DDF4u, gen::fn_sprCreateHandle_001158b0);
        s0 = v0;
        lw(v1, s1, 704);
        lwc1(f0, v1, 36);
        swc1(f0, v0, 44);
        lw(v1, s1, 704);
        lwc1(f1, v1, 56);
        v1 = 0x43860000;
        mtc1(v1, f0);
        add_s(f0, f0, f1);
        swc1(f0, v0, 16);
        lw(v1, s1, 704);
        lwc1(f0, v1, 60);
        swc1(f0, v0, 20);
        lw(v1, s1, 704);
        lw(v1, v1, 64);
        sb(v1, v0, 24);
        a0 = s0;
        a1 = 1;
        jal(ctx, 0x12DE48u, gen::fn_sub_1127D0_001127d0);  // sprDrawSprite
        a0 = s0;
        jal(ctx, 0x12DE54u, gen::fn_sub_115980_00115980);  // release the sprite handle
        a0 = 0;
        lw(a1, s1, 688);
        a2 = 29;
        jal(ctx, 0x12DE68u, gen::fn_sprCreateHandle_001158b0);
        s0 = v0;
        lw(v1, s1, 704);
        lwc1(f0, v1, 36);
        swc1(f0, v0, 44);
        lw(v1, s1, 704);
        lwc1(f1, v1, 56);
        v1 = 0x43860000;
        mtc1(v1, f0);
        add_s(f1, f0, f1);
        v1 = 0x442F0000;
        mtc1(v1, f0);
        add_s(f0, f0, f1);
        swc1(f0, v0, 16);
        lw(v1, s1, 704);
        lwc1(f0, v1, 60);
        swc1(f0, v0, 20);
        lw(v1, s1, 704);
        lw(v1, v1, 64);
        sb(v1, v0, 24);
        a0 = s0;
        a1 = 1;
        jal(ctx, 0x12DECCu, gen::fn_sub_1127D0_001127d0);  // sprDrawSprite
        a0 = s0;
        jal(ctx, 0x12DED8u, gen::fn_sub_115980_00115980);  // release the sprite handle
        lw(a0, s1, 704);
        lwc1(f1, a0, 48);
        v1 = 0x3F800000;
        mtc1(v1, f0);
        sub_s(f0, f1, f0);
        swc1(f0, a0, 48);
        lw(v1, s1, 704);
        a0 = addiu(v1, 48);
        lwc1(f1, v1, 48);
        v1 = lui(0xC42F);
        mtc1(v1, f0);
        c_lt_s(f1, f0);
        if (cond(ctx)) {
            // 0x0012df20
            charge(ctx, 5);
            v1 = 0x442F0000;
            mtc1(v1, f0);
            add_s(f0, f1, f0);
            swc1(f0, a0, 0);
        }
    }
    // 0x0012df34 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0012DF50 sub_12DF50 -- 536 bytes; leaf frame (no stack)
// (bits): the index of the lowest set flag of an equipment mask: bits 0..7 and 8..15 -> 0..7, bit 16 -> 9, 17 -> 10,
// 18 -> 11, 19 / 20 -> 13, none -> 0.
void sub_12DF50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0012df50
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = a0 & 0x1;
    if (v0 == 0) {
        // 0x0012df68
        charge(ctx, 3);
        v0 = a0 & 0x2;
        if (v0 == 0) {
            // 0x0012df80
            charge(ctx, 3);
            v0 = a0 & 0x4;
            if (v0 == 0) {
                // 0x0012df98
                charge(ctx, 3);
                v0 = a0 & 0x8;
                if (v0 == 0) {
                    // 0x0012dfb0
                    charge(ctx, 3);
                    v0 = a0 & 0x10;
                    if (v0 == 0) {
                        // 0x0012dfc8
                        charge(ctx, 3);
                        v0 = a0 & 0x20;
                        if (v0 == 0) {
                            // 0x0012dfe0
                            charge(ctx, 3);
                            v0 = a0 & 0x40;
                            if (v0 == 0) {
                                // 0x0012dff8
                                charge(ctx, 3);
                                v0 = a0 & 0x80;
                                if (v0 == 0) {
                                    // 0x0012e010
                                    charge(ctx, 3);
                                    v0 = a0 & 0x100;
                                    if (v0 == 0) {
                                        // 0x0012e028
                                        charge(ctx, 3);
                                        v0 = a0 & 0x200;
                                        if (v0 == 0) {
                                            // 0x0012e040
                                            charge(ctx, 3);
                                            v0 = a0 & 0x400;
                                            if (v0 == 0) {
                                                // 0x0012e058
                                                charge(ctx, 3);
                                                v0 = a0 & 0x800;
                                                if (v0 == 0) {
                                                    // 0x0012e070
                                                    charge(ctx, 3);
                                                    v0 = a0 & 0x1000;
                                                    if (v0 == 0) {
                                                        // 0x0012e088
                                                        charge(ctx, 3);
                                                        v0 = a0 & 0x2000;
                                                        if (v0 == 0) {
                                                            // 0x0012e0a0
                                                            charge(ctx, 3);
                                                            v0 = a0 & 0x4000;
                                                            if (v0 == 0) {
                                                                // 0x0012e0b8
                                                                charge(ctx, 3);
                                                                v0 = a0 & 0x8000;
                                                                if (v0 == 0) {
                                                                    // 0x0012e0d0
                                                                    charge(ctx, 4);
                                                                    v0 = 0x10000;
                                                                    v0 = a0 & v0;
                                                                    if (v0 == 0) {
                                                                        // 0x0012e0ec
                                                                        charge(ctx, 4);
                                                                        v0 = 0x20000;
                                                                        v0 = a0 & v0;
                                                                        if (v0 == 0) {
                                                                            // 0x0012e108
                                                                            charge(ctx, 4);
                                                                            v0 = 0x40000;
                                                                            v0 = a0 & v0;
                                                                            if (v0 == 0) {
                                                                                // 0x0012e124
                                                                                charge(ctx, 4);
                                                                                v0 = 0x80000;
                                                                                v0 = a0 & v0;
                                                                                if (v0 == 0) {
                                                                                    // 0x0012e140
                                                                                    charge(ctx, 4);
                                                                                    v0 = 0x100000;
                                                                                    v0 = a0 & v0;
                                                                                    if (v0 == 0) {
                                                                                        // 0x0012e15c
                                                                                        charge(ctx, 1);
                                                                                        v0 = 0;
                                                                                    } else {
                                                                                        // 0x0012e150
                                                                                        charge(ctx, 3);
                                                                                        v0 = 13;
                                                                                    }
                                                                                } else {
                                                                                    // 0x0012e134
                                                                                    charge(ctx, 3);
                                                                                    v0 = 13;
                                                                                }
                                                                            } else {
                                                                                // 0x0012e118
                                                                                charge(ctx, 3);
                                                                                v0 = 11;
                                                                            }
                                                                        } else {
                                                                            // 0x0012e0fc
                                                                            charge(ctx, 3);
                                                                            v0 = 10;
                                                                        }
                                                                    } else {
                                                                        // 0x0012e0e0
                                                                        charge(ctx, 3);
                                                                        v0 = 9;
                                                                    }
                                                                } else {
                                                                    // 0x0012e0c4
                                                                    charge(ctx, 3);
                                                                    v0 = 7;
                                                                }
                                                            } else {
                                                                // 0x0012e0ac
                                                                charge(ctx, 3);
                                                                v0 = 6;
                                                            }
                                                        } else {
                                                            // 0x0012e094
                                                            charge(ctx, 3);
                                                            v0 = 5;
                                                        }
                                                    } else {
                                                        // 0x0012e07c
                                                        charge(ctx, 3);
                                                        v0 = 4;
                                                    }
                                                } else {
                                                    // 0x0012e064
                                                    charge(ctx, 3);
                                                    v0 = 3;
                                                }
                                            } else {
                                                // 0x0012e04c
                                                charge(ctx, 3);
                                                v0 = 2;
                                            }
                                        } else {
                                            // 0x0012e034
                                            charge(ctx, 3);
                                            v0 = 1;
                                        }
                                    } else {
                                        // 0x0012e01c
                                        charge(ctx, 3);
                                        v0 = 0;
                                    }
                                } else {
                                    // 0x0012e004
                                    charge(ctx, 3);
                                    v0 = 7;
                                }
                            } else {
                                // 0x0012dfec
                                charge(ctx, 3);
                                v0 = 6;
                            }
                        } else {
                            // 0x0012dfd4
                            charge(ctx, 3);
                            v0 = 5;
                        }
                    } else {
                        // 0x0012dfbc
                        charge(ctx, 3);
                        v0 = 4;
                    }
                } else {
                    // 0x0012dfa4
                    charge(ctx, 3);
                    v0 = 3;
                }
            } else {
                // 0x0012df8c
                charge(ctx, 3);
                v0 = 2;
            }
        } else {
            // 0x0012df74
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x0012df5c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0012e160 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0012E170 sub_12E170 -- 568 bytes; frame 0xC0: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// (file, first sprite, xy, z, r, g, b, alpha, value, digits): draws `value` with 1..3 digit sprites (first + digit),
// colour bytes +48..+50 of each handle; digits 3 forces the hundreds, 2 the tens.
void sub_12E170(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f20{ctx, 20}, f21{ctx, 21};
    // 0x0012e170
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s5 = a0;
    s4 = a1;
    sd(a2, sp, 0xB8);
    s3 = a3;
    s2 = t0;
    s1 = t1;
    s0 = t2;
    s6 = t3;
    lw(s7, sp, 0xC0);
    lw(fp, sp, 0xC8);
    lwc1(f20, sp, 0xBC);
    lwc1(f21, sp, 0xB8);
    v0 = 3;
    if (fp == v0) {
        // 0x0012e1e0
        charge(ctx, 3);
        v0 = slti(s7, 100);
        if (v0 == 0) {
            // 0x0012e1ec
            charge(ctx, 27);
            v0 = 100;
            div(s7, v0);
            mflo(v0);
            a2 = addu(s4, v0);
            a0 = 0;
            a1 = s5;
            jal(ctx, 0x12E204u, gen::fn_sprCreateHandle_001158b0);
            sw(v0, sp, 0xB4);
            mtc1(s3, f0);
            cvt_s_w(f0, f0);
            swc1(f0, v0, 44);
            mov_s(f0, f21);
            swc1(f0, v0, 16);
            swc1(f20, v0, 20);
            sb(s6, v0, 24);
            sb(s2, v0, 48);
            sb(s1, v0, 49);
            sb(s0, v0, 50);
            a0 = v0;
            a1 = 1;
            jal(ctx, 0x12E244u, gen::fn_sub_1127D0_001127d0);  // sprDrawSprite
            lw(a0, sp, 0xB4);
            jal(ctx, 0x12E250u, gen::fn_sub_115980_00115980);  // release the sprite handle
        }
        // 0x0012e258
        charge(ctx, 5);
        v0 = 0x41800000;
        mtc1(v0, f0);
        add_s(f21, f21, f0);
        fp = addiu(fp, -0x1);
    }
    // 0x0012e26c
    charge(ctx, 3);
    v0 = 2;
    if (fp == v0) {
        // 0x0012e278
        charge(ctx, 3);
        v0 = slti(s7, 10);
        if (v0 == 0) {
            // 0x0012e284
            charge(ctx, 28);
            v1 = 10;
            div(s7, v1);
            mflo(v0);
            div(v0, v1);
            mfhi(v0);
            a2 = addu(s4, v0);
            a0 = 0;
            a1 = s5;
            jal(ctx, 0x12E2A4u, gen::fn_sprCreateHandle_001158b0);
            fp = v0;
            mtc1(s3, f0);
            cvt_s_w(f0, f0);
            swc1(f0, v0, 44);
            swc1(f21, v0, 16);
            swc1(f20, v0, 20);
            sb(s6, v0, 24);
            sb(s2, v0, 48);
            sb(s1, v0, 49);
            sb(s0, v0, 50);
            a0 = fp;
            a1 = 1;
            jal(ctx, 0x12E2E0u, gen::fn_sub_1127D0_001127d0);  // sprDrawSprite
            a0 = fp;
            jal(ctx, 0x12E2ECu, gen::fn_sub_115980_00115980);  // release the sprite handle
        }
        // 0x0012e2f4
        charge(ctx, 4);
        v0 = 0x41800000;
        mtc1(v0, f0);
        add_s(f21, f21, f0);
    }
    // 0x0012e304
    charge(ctx, 41);
    v0 = 10;
    div(s7, v0);
    mfhi(v0);
    a2 = addu(s4, v0);
    a0 = 0;
    a1 = s5;
    jal(ctx, 0x12E31Cu, gen::fn_sprCreateHandle_001158b0);
    s4 = v0;
    mtc1(s3, f0);
    cvt_s_w(f0, f0);
    swc1(f0, v0, 44);
    swc1(f21, v0, 16);
    swc1(f20, v0, 20);
    sb(s6, v0, 24);
    sb(s2, v0, 48);
    sb(s1, v0, 49);
    sb(s0, v0, 50);
    a0 = s4;
    a1 = 1;
    jal(ctx, 0x12E358u, gen::fn_sub_1127D0_001127d0);  // sprDrawSprite
    a0 = s4;
    jal(ctx, 0x12E364u, gen::fn_sub_115980_00115980);  // release the sprite handle
    ld(ra, sp, 0xA0);
    lq(fp, sp, 0x90);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xC0);
}

// 0x00130E40 sub_130E40 -- 224 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Destroy of "H_CampSoubi1Draw": the three tween / list blocks +696..+704 (RwFree), the two sprite files +688 / +692,
// the file +0, the work.
void sub_130E40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00130e40
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a0, s0, 696);
    if (a0 != 0) {
        // 0x00130e5c
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x130E64u, v0.u());
    }
    // 0x00130e6c
    charge(ctx, 4);
    sw(zero, s0, 696);
    lw(a0, s0, 700);
    if (a0 != 0) {
        // 0x00130e7c
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x130E84u, v0.u());
    }
    // 0x00130e8c
    charge(ctx, 4);
    sw(zero, s0, 700);
    lw(a0, s0, 704);
    if (a0 != 0) {
        // 0x00130e9c
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x130EA4u, v0.u());
    }
    // 0x00130eac
    charge(ctx, 4);
    sw(zero, s0, 704);
    lw(a0, s0, 688);
    if (a0 != 0) {
        // 0x00130ebc
        charge(ctx, 2);
        jal(ctx, 0x130EBCu, gen::fn_sub_1124B0_001124b0);  // release a sprite file
    }
    // 0x00130ec4
    charge(ctx, 4);
    sw(zero, s0, 688);
    lw(a0, s0, 692);
    if (a0 != 0) {
        // 0x00130ed4
        charge(ctx, 2);
        jal(ctx, 0x130ED4u, gen::fn_sub_1124B0_001124b0);  // release a sprite file
    }
    // 0x00130edc
    charge(ctx, 4);
    sw(zero, s0, 692);
    lw(a0, s0, 0);
    if (a0 != 0) {
        // 0x00130eec
        charge(ctx, 2);
        jal(ctx, 0x130EECu, gen::fn_H_Cdvd_Destroy_00100ec0);
    }
    // 0x00130ef4
    charge(ctx, 11);
    sw(zero, s0, 0);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x130F04u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00130F20 sub_130F20 -- 216 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_CreateSoubi1DrawTask] (parent, priority, xy, pc): creates the equipment screen "H_CampSoubi1Draw" (708-byte
// work, update sub_12C430): +8/+12 position, +18 the party member, +20 = 1.
void sub_130F20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00130f20
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    sd(a2, sp, 0x58);
    s1 = a3;
    a0 = 1;
    a1 = 708;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x130F5Cu, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00130f7c
        charge(ctx, 13);
        a0 = s3;
        a1 = 0x5E0000;
        a1 = addiu(a1, -20192);  // "H_CampSoubi1Draw"
        a2 = s2;
        a3 = 0x130000;
        a3 = addiu(a3, -15312);  // &sub_12C430
        t0 = 0x130000;
        t0 = addiu(t0, 3648);  // &sub_130E40
        t1 = s0;
        jal(ctx, 0x130FA0u, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x00130fbc
            charge(ctx, 7);
            lwc1(f1, sp, 0x58);
            lwc1(f0, sp, 0x5C);
            swc1(f1, s0, 8);
            swc1(f0, s0, 12);
            v1 = 1;
            sw(v1, s0, 20);
            sh(s1, s0, 18);
        } else {
            // 0x00130fb0
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00130f70
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00130fd8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00131000 sub_131000 -- 136 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// qsort comparator of equipment-stock indices (u16 pointers): by the item id of the hero stock entry (sub_16F630(1,
// index), datGetEquipmentItemId); -1 / 0 / 1.
void sub_131000(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00131000
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    lhu(a1, a0, 0);
    a0 = 1;
    jal(ctx, 0x13101Cu, gen::fn_sub_16F630_0016f630);
    s0 = v0 & 0xFFFF;
    lhu(a1, s1, 0);
    a0 = 1;
    jal(ctx, 0x131030u, gen::fn_sub_16F630_0016f630);
    v1 = v0 & 0xFFFF;
    v0 = s0 & 0xFFFF;
    if (v0 != v1) {
        // 0x00131054
        charge(ctx, 3);
        at = slt(v0, v1);
        if (at == 0) {
            // 0x0013106c
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x00131060
            charge(ctx, 3);
            v0 = si(-1);
        }
    } else {
        // 0x00131048
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00131070 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00131090 sub_131090 -- 308 bytes; frame 0x2D0: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// (out, ?, owner, kind): collects the indices 0..299 of the owner's equipment stock (sub_16F630) holding an item whose
// flags (sub_1712D0) have bit 0x20 (usable by the hero: 32 << (pc - 1)) and whose kind (sub_171250: id / 1000) is
// `kind`, orders them by item id (qsort, sub_131000), stores them as u16 in `out` and returns the count.
void sub_131090(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00131090
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x2D0);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a3;
    s2 = 0;
    s3 = 0;
    s1 = dsll32(a2, 16);
    s1 = dsra32(s1, 16);
    for (;;) {
        // 0x00131134
        charge(ctx, 3);
        v0 = slti(s3, 300);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001310d0
        charge(ctx, 7);
        a0 = s1;
        a1 = s3;
        jal(ctx, 0x1310D8u, gen::fn_sub_16F630_0016f630);
        v0 = v0 & 0xFFFF;
        if (v0 != 0) {
            // 0x001310ec
            charge(ctx, 8);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
            a0 = s0;
            jal(ctx, 0x1310F8u, gen::fn_sub_1712D0_001712d0);
            v0 = v0 & 0x20;
            if (v0 != 0) {
                // 0x0013110c
                charge(ctx, 5);
                a0 = s0;
                jal(ctx, 0x131110u, gen::fn_sub_171250_00171250);
                if (s4 == v0) {
                    // 0x00131120
                    charge(ctx, 4);
                    v0 = sll(s2, 1);
                    v0 = addu(v0, sp);
                    sh(s3, v0, 112);
                    s2 = addiu(s2, 1);
                }
            }
        }
        // 0x00131130
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x00131140
    charge(ctx, 3);
    at = slti(s2, 2);
    if (at == 0) {
        // 0x0013114c
        charge(ctx, 7);
        a0 = addiu(sp, 0x70);
        a1 = s2;
        a2 = 2;
        a3 = 0x130000;
        a3 = addiu(a3, 4096);  // &sub_131000
        jal(ctx, 0x131160u, gen::fn_qsort_005225f8);
    }
    // 0x00131168
    charge(ctx, 3);
    a1 = 0;
    for (;;) {
        // 0x0013118c
        charge(ctx, 3);
        v0 = slt(a1, s2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00131174
        charge(ctx, 6);
        a0 = sll(a1, 1);
        v0 = addu(a0, sp);
        lhu(v1, v0, 112);
        v0 = addu(s5, a0);
        sh(v1, v0, 0);
        a1 = addiu(a1, 1);
    }
    // 0x00131198
    charge(ctx, 11);
    v0 = s2;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x2D0);
}

// 0x001332F0 sub_1332F0 -- 356 bytes; frame 0x80: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// (xy, ?, persona, fade): the persona status page used by the facility screens: the table (sub_12BCE0), the frame, the
// arcana card, the level (sub_124E60) and the name (sub_124FD0) at alpha 255 - fade.
void sub_1332F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20};
    // 0x001332f0
    enter(ctx, 89);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x68);
    mov_s(f20, f12);
    s2 = a2;
    v0 = 255;
    s0 = subu(v0, a3);
    a3 = s0;
    jal(ctx, 0x133324u, gen::fn_sub_12BCE0_0012bce0);
    lwc1(f1, sp, 0x68);
    v0 = 0x41400000;
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x68);
    lwc1(f1, sp, 0x6C);
    v0 = 0x42C00000;
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x6C);
    ld(v0, sp, 0x68);
    sd(v0, sp, 0x78);
    v0 = 0x41B00000;
    mtc1(v0, f1);
    lwc1(f0, sp, 0x78);
    add_s(f12, f1, f0);
    v0 = 0x42EA0000;
    mtc1(v0, f1);
    lwc1(f0, sp, 0x7C);
    add_s(f13, f1, f0);
    a3 = s0 & 0xFF;
    a0 = s1;
    v0 = 0x830000;
    lw(a1, v0, 15248);  // 0x833B90
    a2 = 1;
    mov_s(f14, f20);
    jal(ctx, 0x13339Cu, gen::fn_sprDrawSpriteBasic_001159f0);
    ld(v0, sp, 0x68);
    sd(v0, sp, 0x70);
    v0 = 0x830000;
    lw(s3, v0, 15240);  // 0x833B88
    lhu(a0, s2, 2);
    jal(ctx, 0x1333B8u, gen::fn_sub_173280_00173280);
    v0 = v0 & 0xFF;
    a2 = addiu(v0, -1);
    v0 = 0x42D20000;
    mtc1(v0, f1);
    lwc1(f0, sp, 0x70);
    add_s(f12, f1, f0);
    v0 = 0x430E0000;
    mtc1(v0, f1);
    lwc1(f0, sp, 0x74);
    add_s(f13, f1, f0);
    a3 = s0 & 0xFF;
    a0 = s1;
    a1 = s3;
    mov_s(f14, f20);
    jal(ctx, 0x1333F8u, gen::fn_sprDrawSpriteBasic_001159f0);
    ld(a0, sp, 0x68);
    mov_s(f12, f20);
    a1 = s2;
    a2 = s0;
    jal(ctx, 0x133410u, gen::fn_sub_124E60_00124e60);
    ld(a0, sp, 0x68);
    mov_s(f12, f20);
    a1 = s2;
    a2 = s0;
    jal(ctx, 0x133428u, gen::fn_sub_124FD0_00124fd0);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x001335D0 sub_1335D0 -- 224 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Destroy of "H_CampStatusPersonaDraw" (persona screen): the three sprite files +88.., two blocks +100 / +104, the
// file +80, the work.
void sub_1335D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001335d0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    s2 = 0;
    for (;;) {
        // 0x0013361c
        charge(ctx, 3);
        v0 = slti(s2, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001335f4
        charge(ctx, 6);
        v0 = sll(s2, 2);
        v0 = addu(s0, v0);
        s1 = addiu(v0, 88);
        lw(a0, v0, 88);
        if (a0 != 0) {
            // 0x0013360c
            charge(ctx, 2);
            jal(ctx, 0x13360Cu, gen::fn_sub_1124B0_001124b0);  // release a sprite file
        }
        // 0x00133614
        charge(ctx, 2);
        sw(zero, s1, 0);
        s2 = addiu(s2, 1);
    }
    // 0x00133628
    charge(ctx, 3);
    lw(a0, s0, 100);
    if (a0 != 0) {
        // 0x00133634
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x13363Cu, v0.u());
    }
    // 0x00133644
    charge(ctx, 4);
    sw(zero, s0, 100);
    lw(a0, s0, 104);
    if (a0 != 0) {
        // 0x00133654
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x13365Cu, v0.u());
    }
    // 0x00133664
    charge(ctx, 4);
    sw(zero, s0, 104);
    lw(a0, s0, 80);
    if (a0 != 0) {
        // 0x00133674
        charge(ctx, 2);
        jal(ctx, 0x133674u, gen::fn_H_Cdvd_Destroy_00100ec0);
    }
    // 0x0013367c
    charge(ctx, 13);
    sw(zero, s0, 80);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x13368Cu, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001336B0 sub_1336B0 -- 208 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_CreateCampStatusPersonaDrawTask] (parent, priority, xy, pc): creates the persona screen
// "H_CampStatusPersonaDraw" (108-byte work, update sub_1311D0): +16/+20 position, +24 the party member.
void sub_1336B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x001336b0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    sd(a2, sp, 0x58);
    s1 = a3;
    a0 = 1;
    a1 = 108;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x1336ECu, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x0013370c
        charge(ctx, 13);
        a0 = s3;
        a1 = 0x5E0000;
        a1 = addiu(a1, -20256);  // "H_CampStatusPersonaDraw"
        a2 = s2;
        a3 = 0x130000;
        a3 = addiu(a3, 4560);  // &sub_1311D0
        t0 = 0x130000;
        t0 = addiu(t0, 13776);  // &sub_1335D0
        t1 = s0;
        jal(ctx, 0x133730u, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x0013374c
            charge(ctx, 5);
            lwc1(f1, sp, 0x58);
            lwc1(f0, sp, 0x5C);
            swc1(f1, s0, 16);
            swc1(f0, s0, 20);
            sh(s1, s0, 24);
        } else {
            // 0x00133740
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00133700
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00133760 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00133780 sub_133780 -- 372 bytes; frame 0x50: ra sp+0x30, s0 sp+0x20 (sq)
// [H_Camp_UpdatePersonaDispCtlDrawTask] Update of "CampPersonaDispCtlDraw" (a persona picture): as sub_11B0B0 with the
// build at +32, the file at +36, the texture at +40 and the path at +44 ("_h_camp_persona.c", 960); starting a load
// also sets the slide-in floats +20 / +24 / +28 (10.0, 640.0, -1500.0).
void sub_133780(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00133780
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s0, sp, 0x20);
    lw(s0, a0, task::kWork);
    lw(a0, s0, 0);
    v1 = 3;
    if (a0 != v1) {
        // 0x001337a0
        charge(ctx, 3);
        v0 = 2;
        if (a0 == v0) {
            // 0x0013389c
            charge(ctx, 9);
            lw(a0, s0, 32);
            a1 = addiu(sp, 0x4C);
            a2 = 0;
            jal(ctx, 0x1338A8u, gen::fn_sub_10C3A0_0010c3a0);  // poll a texture build
            sw(v0, s0, 40);
            lw(v0, sp, 0x4C);
            if (v0 != 0) {
                // 0x001338c0
                charge(ctx, 7);
                sw(zero, s0, 32);
                lw(a0, s0, 36);
                jal(ctx, 0x1338C8u, gen::fn_H_Cdvd_Destroy_00100ec0);
                sw(zero, s0, 36);
                v0 = 3;
                sw(v0, s0, 0);
            }
        } else {
            // 0x001337ac
            charge(ctx, 3);
            v0 = 1;
            if (a0 == v0) {
                // 0x00133830
                charge(ctx, 5);
                lw(a0, s0, 36);
                jal(ctx, 0x133834u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                if (v0 != 0) {
                    // 0x00133844
                    charge(ctx, 22);
                    sd(zero, sp, 0x0);
                    sd(zero, sp, 0x8);
                    v0 = 0x5E0000;
                    v0 = addiu(v0, -20112);  // "_h_camp_persona.c"
                    sd(v0, sp, 0x10);
                    v0 = 960;
                    sd(v0, sp, 0x18);
                    a0 = 0;
                    a1 = addiu(s0, 44);
                    a2 = 0;
                    a3 = 0;
                    t0 = 0;
                    t1 = 0;
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x133880u, gen::fn_sub_10C1A0_0010c1a0);  // start a texture build
                    sw(v0, s0, 32);
                    v0 = 2;
                    sw(v0, s0, 0);
                }
            } else {
                // 0x001337b8
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x001337c8
                    charge(ctx, 3);
                    lw(a2, s0, 4);
                    if (a2 == 0) {
                        // 0x00133824
                        charge(ctx, 3);
                        sw(v1, s0, 0);
                    } else {
                        // 0x001337d4
                        charge(ctx, 20);
                        a0 = addiu(s0, 44);
                        a1 = 0x5E0000;
                        a1 = addiu(a1, -21328);  // "camp/persona/pst_%03X.tmx"
                        jal(ctx, 0x1337E0u, gen::fn_sprintf_00523ac8);
                        a0 = addiu(s0, 44);
                        a1 = 0;
                        jal(ctx, 0x1337F0u, gen::fn_H_Cdvd_Request_00100d80);
                        sw(v0, s0, 36);
                        v0 = 1;
                        sw(v0, s0, 0);
                        v0 = 0x442F0000;
                        sw(v0, s0, 24);
                        v0 = lui(0xC2EA);
                        sw(v0, s0, 28);
                        v0 = 0x41200000;
                        sw(v0, s0, 20);
                    }
                } else {
                    // 0x001337c0
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x001338dc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 0;
    ld(ra, sp, 0x30);
    lq(s0, sp, 0x20);
    sp = addiu(sp, 0x50);
}

// 0x00133900 sub_133900 -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Destroy of "CampPersonaDispCtlDraw": as sub_11B210 on its offsets.
void sub_133900(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00133900
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a0, s0, 32);
    if (a0 == 0) {
        // 0x0013393c
        charge(ctx, 3);
        lw(a0, s0, 36);
        if (a0 != 0) {
            // 0x00133948
            charge(ctx, 3);
            jal(ctx, 0x133948u, gen::fn_H_Cdvd_Destroy_00100ec0);
            sw(zero, s0, 36);
        }
        // 0x00133954
        charge(ctx, 3);
        lw(a0, s0, 40);
        if (a0 != 0) {
            // 0x00133960
            charge(ctx, 3);
            jal(ctx, 0x133960u, gen::fn_sub_4D0F00_004d0f00);  // textureDestroy
            sw(zero, s0, 40);
        }
    } else {
        // 0x0013391c
        charge(ctx, 8);
        lw(a1, s0, 36);
        jal(ctx, 0x133920u, gen::fn_sub_133D30_00133d30);  // hand the build to a "CampPersonaDispCtlFree" task
        sw(zero, s0, 32);
        sw(zero, s0, 36);
        sw(zero, s0, 40);
    }
    // 0x0013396c
    charge(ctx, 10);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x133978u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001339A0 sub_1339A0 -- 220 bytes; frame 0x70: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [H_Camp_CreatePersonaDispCtlDrawTask] (parent, priority, persona, ?, z in $f12): creates "CampPersonaDispCtlDraw"
// (300-byte work): +4 persona, +12, +16 z.
void sub_1339A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    // 0x001339a0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s3 = a0;
    s2 = a1;
    mov_s(f20, f12);
    s1 = a2;
    s0 = a3;
    a0 = 1;
    a1 = 300;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x1339E8u, v0.u());
    s4 = v0;
    if (s4 != 0) {
        // 0x00133a08
        charge(ctx, 13);
        a0 = s3;
        a1 = 0x5E0000;
        a1 = addiu(a1, -20080);  // "CampPersonaDispCtlDraw"
        a2 = s2;
        a3 = 0x130000;
        a3 = addiu(a3, 14208);  // &sub_133780
        t0 = 0x130000;
        t0 = addiu(t0, 14592);  // &sub_133900
        t1 = s4;
        jal(ctx, 0x133A2Cu, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x00133a48
            charge(ctx, 3);
            sw(s1, s4, 4);
            sw(s0, s4, 12);
            swc1(f20, s4, 16);
        } else {
            // 0x00133a3c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x001339fc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00133a54 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x00133A80 sub_133A80 -- 184 bytes; frame 0x10: ra sp+0x0
// (task): draws the persona picture once loaded (state 3, persona set): the slide value +24 eases toward 60.0 by the
// growing step +20 (+5 per frame), then sub_114450(texture +12, .., 640, 640, +40).
void sub_133A80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x00133a80
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(t0, a0, task::kWork);
    lw(a0, t0, 0);
    v1 = 3;
    if (a0 == v1) {
        // 0x00133a9c
        charge(ctx, 3);
        lw(v1, t0, 4);
        if (v1 != 0) {
            // 0x00133aa8
            charge(ctx, 7);
            lwc1(f1, t0, 24);
            v0 = 0x42700000;
            mtc1(v0, f2);
            c_eq_s(f2, f1);
            if (!cond(ctx)) {
                // 0x00133ac4
                charge(ctx, 13);
                lwc1(f0, t0, 20);
                sub_s(f0, f1, f0);
                swc1(f0, t0, 24);
                lwc1(f1, t0, 20);
                v0 = 0x40A00000;
                mtc1(v0, f0);
                add_s(f0, f1, f0);
                swc1(f0, t0, 20);
                lwc1(f0, t0, 24);
                c_lt_s(f0, f2);
                if (cond(ctx)) {
                    // 0x00133af8
                    charge(ctx, 1);
                    swc1(f2, t0, 24);
                }
            }
            // 0x00133afc
            charge(ctx, 11);
            lwc1(f12, t0, 16);
            lw(a0, t0, 12);
            v0 = 0x4FA40000;
            a1 = v0 | 0xFF19;
            lwc1(f13, t0, 24);
            lwc1(f14, t0, 28);
            a2 = 640;
            a3 = a2;
            lw(t0, t0, 40);
            jal(ctx, 0x133B20u, gen::fn_sub_114450_00114450);
        }
    }
    // 0x00133b28 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00133B80 sub_133B80 -- 188 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_PersonaDispCtlSetPersona] (task, persona, ?): when either value changed, releases the current picture as
// sub_133900 and restarts the loader.
void sub_133B80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00133b80
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    s1 = a2;
    lw(s0, a0, task::kWork);
    lw(v1, s0, 4);
    if (v1 == s2) {
        // 0x00133bac
        charge(ctx, 3);
        lw(v1, s0, 12);
        if (v1 != s1) {
            goto L_00133bb8;
        }
        // 0x00133c20 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_00133bb8:
    charge(ctx, 3);
    lw(a0, s0, 32);
    if (a0 == 0) {
        // 0x00133be4
        charge(ctx, 3);
        lw(a0, s0, 36);
        if (a0 != 0) {
            // 0x00133bf0
            charge(ctx, 3);
            jal(ctx, 0x133BF0u, gen::fn_H_Cdvd_Destroy_00100ec0);
            sw(zero, s0, 36);
        }
        // 0x00133bfc
        charge(ctx, 3);
        lw(a0, s0, 40);
        if (a0 != 0) {
            // 0x00133c08
            charge(ctx, 3);
            jal(ctx, 0x133C08u, gen::fn_sub_4D0F00_004d0f00);  // textureDestroy
            sw(zero, s0, 40);
        }
    } else {
        // 0x00133bc4
        charge(ctx, 8);
        lw(a1, s0, 36);
        jal(ctx, 0x133BC8u, gen::fn_sub_133D30_00133d30);  // hand the build to a "CampPersonaDispCtlFree" task
        sw(zero, s0, 32);
        sw(zero, s0, 36);
        sw(zero, s0, 40);
    }
    // 0x00133c14
    charge(ctx, 3);
    sw(s1, s0, 12);
    sw(s2, s0, 4);
    sw(zero, s0, 0);
    // 0x00133c20 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00133C40 sub_133C40 -- 192 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Update of "CampPersonaDispCtlFree": polls the texture build (sub_10C3A0); when done prints "*** RELEASE KEY",
// releases the texture (sub_4D0F00) and the file (H_Cdvd_Destroy) and returns -1; 0 while it runs.
void sub_133C40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00133c40
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a0, s0, 0);
    a1 = addiu(sp, 0x3C);
    a2 = 0;
    jal(ctx, 0x133C60u, gen::fn_sub_10C3A0_0010c3a0);  // poll a texture build
    s1 = v0;
    lw(v0, sp, 0x3C);
    if (v0 == 0) {
        // 0x00133ce4
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00133c78
        charge(ctx, 3);
        lw(v0, s0, 4);
        if (v0 == 0) {
            // 0x00133ca0
            charge(ctx, 4);
            a0 = 0x5E0000;
            a0 = addiu(a0, -20016);  // "*** RELEASE KEY  \n"
            jal(ctx, 0x133CA8u, gen::fn_printf_005225a8);
        } else {
            // 0x00133c84
            charge(ctx, 7);
            a0 = 0x5E0000;
            a0 = addiu(a0, -20048);  // "*** RELEASE KEY = %s \n"
            a1 = addiu(v0, 16);
            jal(ctx, 0x133C90u, gen::fn_printf_005225a8);
        }
        // 0x00133cb0
        charge(ctx, 2);
        if (s1 != 0) {
            // 0x00133cb8
            charge(ctx, 3);
            a0 = s1;
            jal(ctx, 0x133CBCu, gen::fn_sub_4D0F00_004d0f00);  // textureDestroy
        }
        // 0x00133cc4
        charge(ctx, 3);
        lw(a0, s0, 4);
        if (a0 != 0) {
            // 0x00133cd0
            charge(ctx, 2);
            jal(ctx, 0x133CD0u, gen::fn_H_Cdvd_Destroy_00100ec0);
        }
        // 0x00133cd8
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x00133ce8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00133D00 sub_133D00 -- 44 bytes; frame 0x10: ra sp+0x0
// Destroy of "CampPersonaDispCtlFree": frees the work.
void sub_133D00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00133d00
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, task::kWork);
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x133D14u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00133D30 sub_133D30 -- 224 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_CreatePersonaDispCtlFreeTask] (build, file): creates a parentless "CampPersonaDispCtlFree" task (8-byte
// work: build, file) that waits for a texture build and releases it; prints "*** REQ KEY RELEASE".
void sub_133D30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00133d30
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    a0 = 1;
    a1 = 8;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x133D64u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00133d84
        charge(ctx, 14);
        a0 = 0;
        a1 = 0x5E0000;
        a1 = addiu(a1, -19984);  // "CampPersonaDispCtlFree"
        a2 = 6335;
        a3 = 0x130000;
        a3 = addiu(a3, 15424);  // &sub_133C40
        t0 = 0x130000;
        t0 = addiu(t0, 15616);  // &sub_133D00
        t1 = s0;
        jal(ctx, 0x133DA8u, gen::fn_kwlnTaskCreate_00194b20);
        s1 = v0;
        if (s1 != 0) {
            // 0x00133dc8
            charge(ctx, 2);
            if (s2 != 0) {
                // 0x00133dd0
                charge(ctx, 5);
                a0 = 0x5E0000;
                a0 = addiu(a0, -19952);  // "*** REQ KEY RELEASE = %s \n"
                a1 = addiu(s2, 16);
                jal(ctx, 0x133DDCu, gen::fn_printf_005225a8);
            }
            // 0x00133de4
            charge(ctx, 3);
            sw(s3, s0, 0);
            sw(s2, s0, 4);
            v0 = s1;
        } else {
            // 0x00133dbc
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00133d78
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00133df0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00134A10 sub_134A10 -- 872 bytes; frame 0x90: ra sp+0x70, s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq)
// [H_Camp_UpdateComuFileTask] The social-link screen's file loader (jump table 0x7B5CA0): camp/camp_comu.pak -> 11
// sprite files (work +208.., then the table 0x833B40), camp/camp_card.pak -> 23 card texture builds (sub_10C1A0,
// "_h_camp_comu.c" 203) whose results go to +100.. and 0x833A80; state 9 = loaded. Returns 0.
void sub_134A10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00134a10
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    lw(s2, a0, task::kWork);
    lw(v0, s2, 0);
    at = sltiu(v0, 10);
    if (at != 0) {
        // 0x00134a40
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 23712);  // &0x7B5CA0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x134A5Cu:  // table[0]
            // 0x00134a5c
            charge(ctx, 10);
            a0 = 0x5E0000;
            a0 = addiu(a0, -17920);  // "camp/camp_comu.pak"
            a1 = 1;
            jal(ctx, 0x134A68u, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s2, 192);
            v0 = 1;
            sw(v0, s2, 0);
            break;
        case 0x134A84u:  // table[1]
            // 0x00134a84
            charge(ctx, 5);
            lw(a0, s2, 192);
            jal(ctx, 0x134A88u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                // 0x00134a98
                charge(ctx, 3);
                s0 = 0;
                for (;;) {
                    // 0x00134ad4
                    charge(ctx, 3);
                    v0 = slti(s0, 11);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00134aa4
                    charge(ctx, 12);
                    lw(a0, s2, 192);
                    a1 = s0;
                    a2 = addiu(sp, 0x8C);
                    jal(ctx, 0x134AB0u, gen::fn_H_Cdvd_ArchiveGetFile_00102100);
                    a0 = v0;
                    jal(ctx, 0x134ABCu, gen::fn_sprCreateHandleFromData_00112420);
                    v1 = sll(s0, 2);
                    v1 = addu(s2, v1);
                    sw(v0, v1, 208);
                    s0 = addiu(s0, 1);
                }
                // 0x00134ae0
                charge(ctx, 4);
                v0 = 2;
                sw(v0, s2, 0);
            }
            break;
        case 0x134AF0u:  // table[2]
            // 0x00134af0
            charge(ctx, 4);
            s1 = 1;
            s0 = 0;
            for (;;) {
                // 0x00134b24
                charge(ctx, 3);
                v0 = slti(s0, 11);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00134b00
                charge(ctx, 7);
                v0 = sll(s0, 2);
                v0 = addu(s2, v0);
                lw(a0, v0, 208);
                jal(ctx, 0x134B0Cu, gen::fn_sprFileIsReady_00111f30);
                if (v0 == 0) {
                    // 0x00134b1c
                    charge(ctx, 1);
                    s1 = 0;
                }
                // 0x00134b20
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x00134b30
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x00134b38
                charge(ctx, 5);
                a2 = 0;
                v1 = 0x830000;
                v1 = addiu(v1, 15168);  // &0x833B40
                for (;;) {
                    // 0x00134b64
                    charge(ctx, 3);
                    v0 = slti(a2, 11);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00134b4c
                    charge(ctx, 6);
                    a1 = sll(a2, 2);
                    v0 = addu(s2, a1);
                    lw(a0, v0, 208);
                    v0 = addu(v1, a1);
                    sw(a0, v0, 0);
                    a2 = addiu(a2, 1);
                }
                // 0x00134b70
                charge(ctx, 8);
                lw(a0, s2, 192);
                jal(ctx, 0x134B74u, gen::fn_H_Cdvd_Destroy_00100ec0);
                sw(zero, s2, 192);
                v0 = 3;
                sw(v0, s2, 0);
            }
            break;
        case 0x134B90u:  // table[3]
            // 0x00134b90
            charge(ctx, 10);
            a0 = 0x5E0000;
            a0 = addiu(a0, -17888);  // "camp/camp_card.pak"
            a1 = 1;
            jal(ctx, 0x134B9Cu, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s2, 192);
            v0 = 4;
            sw(v0, s2, 0);
            break;
        case 0x134BB8u:  // table[4]
            // 0x00134bb8
            charge(ctx, 5);
            lw(a0, s2, 192);
            jal(ctx, 0x134BBCu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                // 0x00134bcc
                charge(ctx, 3);
                s1 = 0;
                for (;;) {
                    // 0x00134c38
                    charge(ctx, 3);
                    v0 = slti(s1, 23);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00134bd8
                    charge(ctx, 24);
                    s0 = sll(s1, 2);
                    sd(zero, sp, 0x0);
                    sd(zero, sp, 0x8);
                    v0 = 0x5E0000;
                    v0 = addiu(v0, -17864);  // "_h_camp_comu.c"
                    sd(v0, sp, 0x10);
                    v0 = 203;
                    sd(v0, sp, 0x18);
                    v0 = 0x5E0000;
                    v0 = addiu(v0, -18112);  // &0x5DB940
                    v0 = addu(v0, s0);
                    a0 = 0;
                    lw(a1, v0, 0);
                    a2 = 0;
                    a3 = 0;
                    t0 = 0;
                    t1 = 0;
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x134C24u, gen::fn_sub_10C1A0_0010c1a0);  // start a texture build
                    v1 = addu(s2, s0);
                    sw(v0, v1, 8);
                    s1 = addiu(s1, 1);
                }
                // 0x00134c44
                charge(ctx, 4);
                v0 = 5;
                sw(v0, s2, 0);
            }
            break;
        case 0x134C54u:  // table[5]
            // 0x00134c54
            charge(ctx, 4);
            s4 = 1;
            s3 = 0;
            for (;;) {
                // 0x00134cfc
                charge(ctx, 3);
                v0 = slti(s3, 23);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00134c64
                charge(ctx, 6);
                v0 = sll(s3, 2);
                v1 = addu(s2, v0);
                s1 = addiu(v1, 100);
                lw(v0, v1, 100);
                if (v0 == 0) {
                    // 0x00134c7c
                    charge(ctx, 10);
                    s0 = addiu(v1, 8);
                    lw(a0, v1, 8);
                    a1 = addiu(sp, 0x88);
                    a2 = 0;
                    jal(ctx, 0x134C8Cu, gen::fn_sub_10C3A0_0010c3a0);  // poll a texture build
                    sw(v0, s1, 0);
                    lw(v0, sp, 0x88);
                    if (v0 != 0) {
                        // 0x00134cc8
                        charge(ctx, 12);
                        a0 = sll(s3, 2);
                        sw(zero, s0, 0);
                        lw(v1, s1, 0);
                        v0 = 0x830000;
                        v0 = addiu(v0, 14976);  // &0x833A80
                        v0 = addu(v0, a0);
                        sw(v1, v0, 0);
                        a0 = 0x5E0000;
                        a0 = addiu(a0, -17840);  // "#!#!#!#! comu card tex end %d\n"
                        a1 = s3;
                        jal(ctx, 0x134CF0u, gen::fn_printf_005225a8);
                    } else {
                        // 0x00134ca4
                        charge(ctx, 9);
                        s4 = 0;
                        v1 = sll(s3, 2);
                        sw(zero, s1, 0);
                        v0 = 0x830000;
                        v0 = addiu(v0, 14976);  // &0x833A80
                        v0 = addu(v0, v1);
                        sw(zero, v0, 0);
                    }
                }
                // 0x00134cf8
                charge(ctx, 1);
                s3 = addiu(s3, 1);
            }
            // 0x00134d08
            charge(ctx, 2);
            if (s4 != 0) {
                // 0x00134d10
                charge(ctx, 16);
                v0 = 23;
                sw(v0, s2, 4);
                a0 = 0x5E0000;
                a0 = addiu(a0, -17808);  // "camp comu free\n"
                jal(ctx, 0x134D20u, gen::fn_printf_005225a8);
                lw(a0, s2, 192);
                jal(ctx, 0x134D2Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
                sw(zero, s2, 192);
                a0 = 0x5E0000;
                a0 = addiu(a0, -17792);  // "camp comu free end \n"
                jal(ctx, 0x134D40u, gen::fn_printf_005225a8);
                v0 = 9;
                sw(v0, s2, 0);
            }
            break;
        case 0x134D50u:  // table[6, 7, 8, 9]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    }
    // 0x00134d50 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v0 = 0;
    ld(ra, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    sp = addiu(sp, 0x90);
}

// 0x00134D80 sub_134D80 -- 920 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Destroy of the social-link file loader: the 23 card textures and 11 sprite files, any build still running handed to
// "CampPersonaDispCtlFree" tasks, the pak; frees the work.
void sub_134D80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00134d80
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, task::kWork);
    s0 = 0;
    for (;;) {
        // 0x00134de4
        charge(ctx, 3);
        v0 = slti(s0, 23);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00134dac
        charge(ctx, 6);
        s3 = sll(s0, 2);
        v0 = addu(s1, s3);
        s2 = addiu(v0, 100);
        lw(a0, v0, 100);
        if (a0 != 0) {
            // 0x00134dc4
            charge(ctx, 3);
            jal(ctx, 0x134DC4u, gen::fn_sub_4D0F00_004d0f00);  // textureDestroy
            sw(zero, s2, 0);
        }
        // 0x00134dd0
        charge(ctx, 5);
        v0 = 0x830000;
        v0 = addiu(v0, 14976);  // &0x833A80
        v0 = addu(v0, s3);
        sw(zero, v0, 0);
        s0 = addiu(s0, 1);
    }
    // 0x00134df0
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x00134e2c
        charge(ctx, 3);
        v0 = slti(s0, 11);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00134dfc
        charge(ctx, 5);
        s2 = sll(s0, 2);
        v0 = addu(s1, s2);
        lw(a0, v0, 208);
        if (a0 != 0) {
            // 0x00134e10
            charge(ctx, 2);
            jal(ctx, 0x134E10u, gen::fn_sub_1124B0_001124b0);  // release a sprite file
        }
        // 0x00134e18
        charge(ctx, 5);
        v0 = 0x830000;
        v0 = addiu(v0, 15168);  // &0x833B40
        v0 = addu(v0, s2);
        sw(zero, v0, 0);
        s0 = addiu(s0, 1);
    }
    // 0x00134e38
    charge(ctx, 4);
    lw(v1, s1, 0);
    v0 = 5;
    if (v1 != v0) {
        // 0x00134fc8
        charge(ctx, 3);
        v0 = 9;
        if (v1 != v0) {
            // 0x00134ff4
            charge(ctx, 3);
            at = slti(v1, 6);
            if (at == 0) {
                // 0x00135020
                charge(ctx, 6);
                lw(v0, s1, 4);
                v0 = sll(v0, 2);
                v0 = addu(v0, s1);
                lw(s2, v0, 8);
                if (s2 == 0) {
                    // 0x001350c8
                    charge(ctx, 3);
                    lw(a0, s1, 192);
                    if (a0 != 0) {
                        // 0x001350d4
                        charge(ctx, 3);
                        jal(ctx, 0x1350D4u, gen::fn_H_Cdvd_Destroy_00100ec0);
                        sw(zero, s1, 192);
                    }
                } else {
                    // 0x00135038
                    charge(ctx, 11);
                    lw(s0, s1, 192);
                    a0 = 1;
                    a1 = 8;
                    a2 = 0x40000;
                    v0 = 0x960000;
                    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
                    jalr(ctx, 0x135050u, v0.u());
                    s3 = v0;
                    if (s3 != 0) {
                        // 0x00135064
                        charge(ctx, 13);
                        a0 = 0;
                        a1 = 0x5E0000;
                        a1 = addiu(a1, -19984);  // "CampPersonaDispCtlFree"
                        a2 = 6335;
                        a3 = 0x130000;
                        a3 = addiu(a3, 15424);  // &sub_133C40
                        t0 = 0x130000;
                        t0 = addiu(t0, 15616);  // &sub_133D00
                        t1 = s3;
                        jal(ctx, 0x135088u, gen::fn_kwlnTaskCreate_00194b20);
                        if (v0 != 0) {
                            // 0x00135098
                            charge(ctx, 2);
                            if (s0 != 0) {
                                // 0x001350a0
                                charge(ctx, 5);
                                a0 = 0x5E0000;
                                a0 = addiu(a0, -19952);  // "*** REQ KEY RELEASE = %s \n"
                                a1 = addiu(s0, 16);
                                jal(ctx, 0x1350ACu, gen::fn_printf_005225a8);
                            }
                            // 0x001350b4
                            charge(ctx, 2);
                            sw(s2, s3, 0);
                            sw(s0, s3, 4);
                        }
                    }
                    // 0x001350bc
                    charge(ctx, 3);
                    sw(zero, s1, 192);
                }
            } else {
                // 0x00135000
                charge(ctx, 3);
                lw(a0, s1, 192);
                if (a0 != 0) {
                    // 0x0013500c
                    charge(ctx, 5);
                    jal(ctx, 0x13500Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
                    sw(zero, s1, 192);
                }
            }
        } else {
            // 0x00134fd4
            charge(ctx, 3);
            lw(a0, s1, 192);
            if (a0 != 0) {
                // 0x00134fe0
                charge(ctx, 5);
                jal(ctx, 0x134FE0u, gen::fn_H_Cdvd_Destroy_00100ec0);
                sw(zero, s1, 192);
            }
        }
    } else {
        // 0x00134e48
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x00134f8c
            charge(ctx, 3);
            v0 = slti(s0, 23);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00134e54
            charge(ctx, 6);
            v0 = sll(s0, 2);
            v0 = addu(s1, v0);
            s2 = addiu(v0, 8);
            lw(v0, v0, 8);
            if (v0 != 0) {
                // 0x00134e6c
                charge(ctx, 8);
                a0 = 0x5E0000;
                a0 = addiu(a0, -17760);  // "#!#!#!#! tex is active = [%d]\n"
                a1 = s0;
                jal(ctx, 0x134E78u, gen::fn_printf_005225a8);
                v0 = 44;
                if (s0 != v0) {
                    // 0x00134f20
                    charge(ctx, 11);
                    lw(s2, s2, 0);
                    a0 = 1;
                    a1 = 8;
                    a2 = 0x40000;
                    v0 = 0x960000;
                    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
                    jalr(ctx, 0x134F38u, v0.u());
                    s3 = v0;
                    if (s3 != 0) {
                        // 0x00134f4c
                        charge(ctx, 13);
                        a0 = 0;
                        a1 = 0x5E0000;
                        a1 = addiu(a1, -19984);  // "CampPersonaDispCtlFree"
                        a2 = 6335;
                        a3 = 0x130000;
                        a3 = addiu(a3, 15424);  // &sub_133C40
                        t0 = 0x130000;
                        t0 = addiu(t0, 15616);  // &sub_133D00
                        t1 = s3;
                        jal(ctx, 0x134F70u, gen::fn_kwlnTaskCreate_00194b20);
                        if (v0 != 0) {
                            // 0x00134f80
                            charge(ctx, 2);
                            sw(s2, s3, 0);
                            sw(zero, s3, 4);
                        }
                    }
                } else {
                    // 0x00134e8c
                    charge(ctx, 12);
                    lw(s3, s1, 192);
                    lw(s2, s2, 0);
                    a0 = 1;
                    a1 = 8;
                    a2 = 0x40000;
                    v0 = 0x960000;
                    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
                    jalr(ctx, 0x134EA8u, v0.u());
                    s4 = v0;
                    if (s4 != 0) {
                        // 0x00134ebc
                        charge(ctx, 13);
                        a0 = 0;
                        a1 = 0x5E0000;
                        a1 = addiu(a1, -19984);  // "CampPersonaDispCtlFree"
                        a2 = 6335;
                        a3 = 0x130000;
                        a3 = addiu(a3, 15424);  // &sub_133C40
                        t0 = 0x130000;
                        t0 = addiu(t0, 15616);  // &sub_133D00
                        t1 = s4;
                        jal(ctx, 0x134EE0u, gen::fn_kwlnTaskCreate_00194b20);
                        if (v0 != 0) {
                            // 0x00134ef0
                            charge(ctx, 2);
                            if (s3 != 0) {
                                // 0x00134ef8
                                charge(ctx, 5);
                                a0 = 0x5E0000;
                                a0 = addiu(a0, -19952);  // "*** REQ KEY RELEASE = %s \n"
                                a1 = addiu(s3, 16);
                                jal(ctx, 0x134F04u, gen::fn_printf_005225a8);
                            }
                            // 0x00134f0c
                            charge(ctx, 2);
                            sw(s2, s4, 0);
                            sw(s3, s4, 4);
                        }
                    }
                    // 0x00134f14
                    charge(ctx, 3);
                    sw(zero, s1, 192);
                }
            }
            // 0x00134f88
            charge(ctx, 1);
            s0 = addiu(s0, 1);
        }
        // 0x00134f98
        charge(ctx, 7);
        a0 = 0x5E0000;
        a0 = addiu(a0, -17728);  // " comu file free \n"
        jal(ctx, 0x134FA0u, gen::fn_printf_005225a8);
        lw(a0, s1, 192);
        if (a0 != 0) {
            // 0x00134fb4
            charge(ctx, 5);
            jal(ctx, 0x134FB4u, gen::fn_H_Cdvd_Destroy_00100ec0);
            sw(zero, s1, 192);
        }
    }
    // 0x001350e0
    charge(ctx, 14);
    a0 = s1;
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x1350ECu, v0.u());
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00135120 sub_135120 -- 820 bytes; frame 0x150: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// (comu task): requests the bust-up picture of the selected social link: releases the previous one (or hands its build
// to a "CampPersonaDispCtlFree" task), then camp/commu/tim2_bustup/i_bust%02X_{a,b}.tmx from the tables 0x833A60 /
// 0x5DBB00 ("b" for sub_172160 / sub_1717C0 links) into +344.
void sub_135120(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00135120
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    sw(zero, gp, g::kComuBustBuild);  // 0x7CDF70
    lw(s2, s0, 356);
    if (s2 == 0) {
        // 0x001351e0
        charge(ctx, 3);
        lw(a0, s0, 344);
        if (a0 != 0) {
            // 0x001351ec
            charge(ctx, 3);
            jal(ctx, 0x1351ECu, gen::fn_H_Cdvd_Destroy_00100ec0);
            sw(zero, s0, 344);
        }
        // 0x001351f8
        charge(ctx, 3);
        lw(a0, s0, 364);
        if (a0 != 0) {
            // 0x00135204
            charge(ctx, 3);
            jal(ctx, 0x135204u, gen::fn_sub_4D0F00_004d0f00);  // textureDestroy
            sw(zero, s0, 364);
        }
    } else {
        // 0x0013514c
        charge(ctx, 11);
        lw(s1, s0, 344);
        a0 = 1;
        a1 = 8;
        a2 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
        jalr(ctx, 0x135164u, v0.u());
        s3 = v0;
        if (s3 != 0) {
            // 0x00135178
            charge(ctx, 13);
            a0 = 0;
            a1 = 0x5E0000;
            a1 = addiu(a1, -19984);  // "CampPersonaDispCtlFree"
            a2 = 6335;
            a3 = 0x130000;
            a3 = addiu(a3, 15424);  // &sub_133C40
            t0 = 0x130000;
            t0 = addiu(t0, 15616);  // &sub_133D00
            t1 = s3;
            jal(ctx, 0x13519Cu, gen::fn_kwlnTaskCreate_00194b20);
            if (v0 != 0) {
                // 0x001351ac
                charge(ctx, 2);
                if (s1 != 0) {
                    // 0x001351b4
                    charge(ctx, 5);
                    a0 = 0x5E0000;
                    a0 = addiu(a0, -19952);  // "*** REQ KEY RELEASE = %s \n"
                    a1 = addiu(s1, 16);
                    jal(ctx, 0x1351C0u, gen::fn_printf_005225a8);
                }
                // 0x001351c8
                charge(ctx, 2);
                sw(s2, s3, 0);
                sw(s1, s3, 4);
            }
        }
        // 0x001351d0
        charge(ctx, 4);
        sw(zero, s0, 356);
        sw(zero, s0, 344);
    }
    // 0x00135210
    charge(ctx, 8);
    lw(a0, s0, 4);
    lw(v1, s0, 8);
    v1 = addu(a0, v1);
    v1 = sll(v1, 2);
    v1 = addu(v1, s0);
    lw(s1, v1, 32);
    if (s1 != 0) {
        // 0x00135230
        charge(ctx, 3);
        v1 = 29;
        if (s1 == v1) {
            goto L_0013536c;
        }
        // 0x0013523c
        charge(ctx, 12);
        v1 = sll(s1, 1);
        v1 = addu(v1, s1);
        a0 = sll(v1, 1);
        v1 = 0x5E0000;
        v1 = addiu(v1, -17664);  // &0x5DBB00
        a0 = addu(v1, a0);
        lw(v1, s0, 20);
        v1 = sll(v1, 1);
        v1 = addu(v1, a0);
        lhu(v1, v1, 0);
        if (v1 == 0) {
            // 0x00135360
            charge(ctx, 3);
            sw(zero, s0, 344);
        } else {
            // 0x0013526c
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x135270u, gen::fn_sub_172160_00172160);
            if (v0 == 0) {
                // 0x00135280
                charge(ctx, 5);
                a0 = s1;
                jal(ctx, 0x135284u, gen::fn_sub_1717C0_001717c0);
                if (v0 != 0) {
                    goto L_00135294;
                }
                // 0x001352f0
                charge(ctx, 21);
                lw(v1, s0, 4);
                lw(v0, s0, 8);
                v0 = addu(v1, v0);
                v0 = sll(v0, 2);
                v0 = addu(v0, s0);
                lw(v1, v0, 32);
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                v1 = sll(v0, 1);
                v0 = 0x5E0000;
                v0 = addiu(v0, -17664);  // &0x5DBB00
                v1 = addu(v0, v1);
                lw(v0, s0, 20);
                v0 = sll(v0, 1);
                v0 = addu(v0, v1);
                lhu(a2, v0, 0);
                a0 = addiu(sp, 0x50);
                a1 = 0x5E0000;
                a1 = addiu(a1, -17424);  // "camp/commu/tim2_bustup/i_bust%02X_a.tmx"
                jal(ctx, 0x13533Cu, gen::fn_sprintf_00523ac8);
                goto L_00135344;
            }
        L_00135294:
            charge(ctx, 23);
            lw(v1, s0, 4);
            lw(v0, s0, 8);
            v0 = addu(v1, v0);
            v0 = sll(v0, 2);
            v0 = addu(v0, s0);
            lw(v1, v0, 32);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v1 = sll(v0, 1);
            v0 = 0x5E0000;
            v0 = addiu(v0, -17664);  // &0x5DBB00
            v1 = addu(v0, v1);
            lw(v0, s0, 20);
            v0 = sll(v0, 1);
            v0 = addu(v0, v1);
            lhu(a2, v0, 0);
            a0 = addiu(sp, 0x50);
            a1 = 0x5E0000;
            a1 = addiu(a1, -17472);  // "camp/commu/tim2_bustup/i_bust%02X_b.tmx"
            jal(ctx, 0x1352E0u, gen::fn_sprintf_00523ac8);
        L_00135344:
            charge(ctx, 7);
            a0 = addiu(sp, 0x50);
            a1 = 0;
            jal(ctx, 0x13534Cu, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s0, 344);
        }
        // 0x00135434 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x150);
        return;
    }
L_0013536c:
    charge(ctx, 8);
    lw(v1, s0, 20);
    a0 = sll(v1, 1);
    v1 = 0x830000;
    v1 = addiu(v1, 14944);  // &0x833A60
    v1 = addu(v1, a0);
    lh(v1, v1, 0);
    if (v1 == 0) {
        // 0x00135430
        charge(ctx, 1);
        sw(zero, s0, 344);
    } else {
        // 0x0013538c
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x135390u, gen::fn_sub_172160_00172160);
        if (v0 == 0) {
            // 0x001353a0
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x1353A4u, gen::fn_sub_1717C0_001717c0);
            if (v0 != 0) {
                goto L_001353b4;
            }
            // 0x001353e8
            charge(ctx, 11);
            lw(v0, s0, 20);
            v1 = sll(v0, 1);
            v0 = 0x830000;
            v0 = addiu(v0, 14944);  // &0x833A60
            v0 = addu(v0, v1);
            lh(a2, v0, 0);
            a0 = addiu(sp, 0x50);
            a1 = 0x5E0000;
            a1 = addiu(a1, -17424);  // "camp/commu/tim2_bustup/i_bust%02X_a.tmx"
            jal(ctx, 0x13540Cu, gen::fn_sprintf_00523ac8);
            goto L_00135414;
        }
    L_001353b4:
        charge(ctx, 13);
        lw(v0, s0, 20);
        v1 = sll(v0, 1);
        v0 = 0x830000;
        v0 = addiu(v0, 14944);  // &0x833A60
        v0 = addu(v0, v1);
        lh(a2, v0, 0);
        a0 = addiu(sp, 0x50);
        a1 = 0x5E0000;
        a1 = addiu(a1, -17472);  // "camp/commu/tim2_bustup/i_bust%02X_b.tmx"
        jal(ctx, 0x1353D8u, gen::fn_sprintf_00523ac8);
    L_00135414:
        charge(ctx, 7);
        a0 = addiu(sp, 0x50);
        a1 = 0;
        jal(ctx, 0x13541Cu, gen::fn_H_Cdvd_Request_00100d80);
        sw(v0, s0, 344);
    }
    // 0x00135434 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x150);
}

// 0x00135460 sub_135460 -- 348 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// (comu task): the same for the arcana picture: releases the previous one, requests off_5DB998[sub_16DF30(link)] into
// +348.
void sub_135460(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00135460
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    sw(zero, gp, g::kComuArcanaBuild);  // 0x7CDF74
    lw(s2, s0, 360);
    if (s2 == 0) {
        // 0x00135520
        charge(ctx, 3);
        lw(a0, s0, 348);
        if (a0 != 0) {
            // 0x0013552c
            charge(ctx, 3);
            jal(ctx, 0x13552Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
            sw(zero, s0, 348);
        }
        // 0x00135538
        charge(ctx, 3);
        lw(a0, s0, 368);
        if (a0 != 0) {
            // 0x00135544
            charge(ctx, 3);
            jal(ctx, 0x135544u, gen::fn_sub_4D0F00_004d0f00);  // textureDestroy
            sw(zero, s0, 368);
        }
    } else {
        // 0x0013548c
        charge(ctx, 11);
        lw(s1, s0, 348);
        a0 = 1;
        a1 = 8;
        a2 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
        jalr(ctx, 0x1354A4u, v0.u());
        s3 = v0;
        if (s3 != 0) {
            // 0x001354b8
            charge(ctx, 13);
            a0 = 0;
            a1 = 0x5E0000;
            a1 = addiu(a1, -19984);  // "CampPersonaDispCtlFree"
            a2 = 6335;
            a3 = 0x130000;
            a3 = addiu(a3, 15424);  // &sub_133C40
            t0 = 0x130000;
            t0 = addiu(t0, 15616);  // &sub_133D00
            t1 = s3;
            jal(ctx, 0x1354DCu, gen::fn_kwlnTaskCreate_00194b20);
            if (v0 != 0) {
                // 0x001354ec
                charge(ctx, 2);
                if (s1 != 0) {
                    // 0x001354f4
                    charge(ctx, 5);
                    a0 = 0x5E0000;
                    a0 = addiu(a0, -19952);  // "*** REQ KEY RELEASE = %s \n"
                    a1 = addiu(s1, 16);
                    jal(ctx, 0x135500u, gen::fn_printf_005225a8);
                }
                // 0x00135508
                charge(ctx, 2);
                sw(s2, s3, 0);
                sw(s1, s3, 4);
            }
        }
        // 0x00135510
        charge(ctx, 4);
        sw(zero, s0, 360);
        sw(zero, s0, 348);
    }
    // 0x00135550
    charge(ctx, 27);
    lw(v1, s0, 4);
    lw(v0, s0, 8);
    v0 = addu(v1, v0);
    v0 = sll(v0, 2);
    v0 = addu(v0, s0);
    lh(a0, v0, 32);
    jal(ctx, 0x135568u, gen::fn_sub_16DF30_0016df30);
    v0 = dsll32(v0, 24);
    v0 = dsra32(v0, 24);
    v1 = sll(v0, 2);
    v0 = 0x5E0000;
    v0 = addiu(v0, -18024);  // &0x5DB998
    v0 = addu(v0, v1);
    lw(a0, v0, 0);
    a1 = 0;
    jal(ctx, 0x135590u, gen::fn_H_Cdvd_Request_00100d80);
    sw(v0, s0, 348);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001365B0 sub_1365B0 -- 416 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Destroy of "H_CampComuDraw": both pictures (or their builds), the help file +336, message 11 (sub_3C7DD0), the work.
void sub_1365B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001365b0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s4, a0, task::kWork);
    sw(zero, gp, g::kComuBustBuild);  // 0x7CDF70
    sw(zero, gp, g::kComuArcanaBuild);  // 0x7CDF74
    s5 = 0;
    for (;;) {
        // 0x001366e0
        charge(ctx, 3);
        v0 = slti(s5, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001365ec
        charge(ctx, 6);
        v0 = sll(s5, 2);
        s0 = addu(s4, v0);
        s2 = addiu(s0, 356);
        lw(s1, s0, 356);
        if (s1 == 0) {
            // 0x0013669c
            charge(ctx, 4);
            s1 = addiu(s0, 344);
            lw(a0, s0, 344);
            if (a0 != 0) {
                // 0x001366ac
                charge(ctx, 3);
                jal(ctx, 0x1366ACu, gen::fn_H_Cdvd_Destroy_00100ec0);
                sw(zero, s1, 0);
            }
            // 0x001366b8
            charge(ctx, 3);
            lw(a0, s0, 364);
            if (a0 != 0) {
                // 0x001366c4
                charge(ctx, 6);
                v0 = sll(s5, 2);
                v0 = addu(s4, v0);
                s0 = addiu(v0, 364);
                jal(ctx, 0x1366D0u, gen::fn_sub_4D0F00_004d0f00);  // textureDestroy
                sw(zero, s0, 0);
            }
        } else {
            // 0x00136604
            charge(ctx, 12);
            s6 = addiu(s0, 344);
            lw(s0, s0, 344);
            a0 = 1;
            a1 = 8;
            a2 = 0x40000;
            v0 = 0x960000;
            lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
            jalr(ctx, 0x136620u, v0.u());
            s3 = v0;
            if (s3 != 0) {
                // 0x00136634
                charge(ctx, 13);
                a0 = 0;
                a1 = 0x5E0000;
                a1 = addiu(a1, -19984);  // "CampPersonaDispCtlFree"
                a2 = 6335;
                a3 = 0x130000;
                a3 = addiu(a3, 15424);  // &sub_133C40
                t0 = 0x130000;
                t0 = addiu(t0, 15616);  // &sub_133D00
                t1 = s3;
                jal(ctx, 0x136658u, gen::fn_kwlnTaskCreate_00194b20);
                if (v0 != 0) {
                    // 0x00136668
                    charge(ctx, 2);
                    if (s0 != 0) {
                        // 0x00136670
                        charge(ctx, 5);
                        a0 = 0x5E0000;
                        a0 = addiu(a0, -19952);  // "*** REQ KEY RELEASE = %s \n"
                        a1 = addiu(s0, 16);
                        jal(ctx, 0x13667Cu, gen::fn_printf_005225a8);
                    }
                    // 0x00136684
                    charge(ctx, 2);
                    sw(s1, s3, 0);
                    sw(s0, s3, 4);
                }
            }
            // 0x0013668c
            charge(ctx, 4);
            sw(zero, s2, 0);
            sw(zero, s6, 0);
        }
        // 0x001366dc
        charge(ctx, 1);
        s5 = addiu(s5, 1);
    }
    // 0x001366ec
    charge(ctx, 3);
    lw(a0, s4, 336);
    if (a0 != 0) {
        // 0x001366f8
        charge(ctx, 3);
        jal(ctx, 0x1366F8u, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, s4, 336);
    }
    // 0x00136704
    charge(ctx, 19);
    a0 = 11;
    jal(ctx, 0x136708u, gen::fn_sub_3C7DD0_003c7dd0);
    a0 = s4;
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x13671Cu, v0.u());
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00136750 sub_136750 -- 204 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_CreateComuDrawTask] (parent, priority): creates the social-link screen "H_CampComuDraw" (416-byte work,
// update sub_1355C0) and requests camp/comu/datComuHelp.bmd into +336.
void sub_136750(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00136750
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 1;
    a1 = 416;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x136780u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001367a0
        charge(ctx, 14);
        a0 = s2;
        a1 = 0x5E0000;
        a1 = addiu(a1, -17384);  // "H_CampComuDraw"
        a2 = s1;
        a3 = 0x130000;
        a3 = addiu(a3, 21952);  // &sub_1355C0
        t0 = 0x130000;
        t0 = addiu(t0, 26032);  // &sub_1365B0
        t1 = s0;
        jal(ctx, 0x1367C4u, gen::fn_kwlnTaskCreate_00194b20);
        s1 = v0;
        if (s1 != 0) {
            // 0x001367e4
            charge(ctx, 7);
            a0 = 0x5E0000;
            a0 = addiu(a0, -17360);  // "camp/comu/datComuHelp.bmd"
            a1 = 0;
            jal(ctx, 0x1367F0u, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s0, 336);
            v0 = s1;
        } else {
            // 0x001367d8
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00136794
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00136800 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001368A0 sub_1368A0 -- 364 bytes; frame 0x50: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// (xy, alpha, z): the social-link screen's scrolling ribbon: sprite 1 of 0x833B40 twice (1006 px apart, vertical), the
// offset gp-19796 moving by -1 and wrapping at -1106.
void sub_1368A0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x001368a0
    enter(ctx, 80);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x48);
    mov_s(f22, f12);
    s0 = a1;
    lwc1(f20, sp, 0x4C);
    a0 = 0;
    v0 = 0x830000;
    lw(a1, v0, 15168);  // 0x833B40
    a2 = 1;
    jal(ctx, 0x1368DCu, gen::fn_sprCreateHandle_001158b0);
    s1 = v0;
    swc1(f22, v0, 44);
    v1 = 0x439F0000;
    mtc1(v1, f1);
    lwc1(f0, sp, 0x48);
    add_s(f1, f1, f0);
    v1 = 0x42C80000;
    mtc1(v1, f0);
    sub_s(f21, f1, f0);
    swc1(f21, v0, 16);
    v1 = 0x41A00000;
    mtc1(v1, f0);
    add_s(f20, f0, f20);
    lwc1(f0, gp, g::kComuRibbonY);  // 0x7CDF9C
    cvt_s_w(f0, f0);
    add_s(f0, f20, f0);
    swc1(f0, v0, 20);
    sb(s0, v0, 24);
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x13693Cu, gen::fn_sub_1127D0_001127d0);  // sprDrawSprite
    a0 = s1;
    jal(ctx, 0x136948u, gen::fn_sub_115980_00115980);  // release the sprite handle
    a0 = 0;
    v0 = 0x830000;
    lw(a1, v0, 15168);  // 0x833B40
    a2 = 1;
    jal(ctx, 0x136960u, gen::fn_sprCreateHandle_001158b0);
    s1 = v0;
    swc1(f22, v0, 44);
    swc1(f21, v0, 16);
    v1 = 1006;
    mtc1(v1, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, gp, g::kComuRibbonY);  // 0x7CDF9C
    cvt_s_w(f0, f0);
    add_s(f0, f1, f0);
    add_s(f1, f20, f0);
    v1 = 0x42C80000;
    mtc1(v1, f0);
    add_s(f0, f0, f1);
    swc1(f0, v0, 20);
    sb(s0, v0, 24);
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x1369B4u, gen::fn_sub_1127D0_001127d0);  // sprDrawSprite
    a0 = s1;
    jal(ctx, 0x1369C0u, gen::fn_sub_115980_00115980);  // release the sprite handle
    lw(v1, gp, g::kComuRibbonY);  // 0x7CDF9C
    v1 = addiu(v1, -1);
    sw(v1, gp, g::kComuRibbonY);  // 0x7CDF9C
    at = slti(v1, -1106);
    if (at != 0) {
        // 0x001369e0
        charge(ctx, 2);
        v1 = addiu(v1, 1106);
        sw(v1, gp, g::kComuRibbonY);  // 0x7CDF9C
    }
    // 0x001369e8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00137300 sub_137300 -- 628 bytes; frame 0x80: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// (xy, link, ?, ?, alpha): the card of a social link: its texture (0x833A80[table 0x5E3220[link] - 1]) through
// sub_114E70 / sub_1140D0, then the "max" / "reversed" / rank-10 overlay sprite.
void sub_137300(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f20{ctx, 20}, f21{ctx, 21};
    // 0x00137300
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x78);
    mov_s(f21, f12);
    s4 = a1;
    s3 = t0;
    a0 = s4;
    jal(ctx, 0x137338u, gen::fn_sub_172160_00172160);
    v1 = 0x5E0000;
    v1 = addiu(v1, 12832);  // &0x5E3220
    v1 = addu(v1, s4);
    lb(v1, v1, 0);
    v1 = addiu(v1, -1);
    a0 = sll(v1, 2);
    v1 = 0x830000;
    v1 = addiu(v1, 14976);  // &0x833A80
    s1 = addu(v1, a0);
    lw(v1, s1, 0);
    if (v1 != 0) {
        // 0x00137370
        charge(ctx, 7);
        v0 = 255;
        s0 = subu(v0, s3);
        a0 = s4;
        jal(ctx, 0x13737Cu, gen::fn_sub_1717C0_001717c0);
        if (v0 == 0) {
            // 0x001373e8
            charge(ctx, 17);
            lwc1(f20, sp, 0x7C);
            v0 = si(-256);
            a0 = s0 | v0;
            v0 = 0x41C00000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x78);
            add_s(f13, f1, f0);
            v0 = 0x41B80000;
            mtc1(v0, f0);
            add_s(f14, f0, f20);
            mov_s(f12, f21);
            a1 = 64;
            a2 = a1;
            lw(a3, s1, 0);
            jal(ctx, 0x137424u, gen::fn_sub_1140D0_001140d0);
        } else {
            // 0x0013738c
            charge(ctx, 23);
            lwc1(f20, sp, 0x7C);
            v0 = si(-256);
            a1 = s0 | v0;
            v0 = 0x41C00000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x78);
            add_s(f13, f1, f0);
            v0 = 0x41B80000;
            mtc1(v0, f0);
            add_s(f14, f0, f20);
            v0 = 0x3F800000;
            mtc1(v0, f15);
            a0 = 2;
            mov_s(f12, f21);
            mov_s(f16, f15);
            a2 = 64;
            a3 = a2;
            lw(t0, s1, 0);
            jal(ctx, 0x1373D8u, gen::fn_sub_114E70_00114e70);
        }
        // 0x0013742c
        charge(ctx, 5);
        a0 = s4;
        jal(ctx, 0x137430u, gen::fn_sub_172160_00172160);
        if (v0 == 0) {
            // 0x00137488
            charge(ctx, 5);
            a0 = s4;
            jal(ctx, 0x13748Cu, gen::fn_sub_1717C0_001717c0);
            if (v0 == 0) {
                // 0x001374e4
                charge(ctx, 9);
                a0 = dsll32(s4, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x1374ECu, gen::fn_sub_16DBA0_0016dba0);
                a0 = dsll32(v0, 24);
                a0 = dsra32(a0, 24);
                v1 = 10;
                if (a0 == v1) {
                    // 0x00137508
                    charge(ctx, 16);
                    v0 = 0x41880000;
                    mtc1(v0, f1);
                    lwc1(f0, sp, 0x78);
                    add_s(f12, f1, f0);
                    v0 = 0x41200000;
                    mtc1(v0, f0);
                    add_s(f13, f0, f20);
                    a3 = s3 & 0xFF;
                    a0 = s2;
                    v0 = 0x830000;
                    lw(a1, v0, 15180);  // 0x833B4C
                    a2 = 0;
                    mov_s(f14, f21);
                    jal(ctx, 0x137540u, gen::fn_sprDrawSpriteBasic_001159f0);
                }
            } else {
                // 0x0013749c
                charge(ctx, 18);
                v0 = 0x41880000;
                mtc1(v0, f1);
                lwc1(f0, sp, 0x78);
                add_s(f12, f1, f0);
                v0 = 0x41200000;
                mtc1(v0, f0);
                add_s(f13, f0, f20);
                a3 = s3 & 0xFF;
                a0 = s2;
                v0 = 0x830000;
                lw(a1, v0, 15184);  // 0x833B50
                a2 = 0;
                mov_s(f14, f21);
                jal(ctx, 0x1374D4u, gen::fn_sprDrawSpriteBasic_001159f0);
            }
        } else {
            // 0x00137440
            charge(ctx, 18);
            v0 = 0x41200000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x78);
            add_s(f12, f1, f0);
            v0 = 0x40A00000;
            mtc1(v0, f0);
            add_s(f13, f0, f20);
            a3 = s3 & 0xFF;
            a0 = s2;
            v0 = 0x830000;
            lw(a1, v0, 15188);  // 0x833B54
            a2 = 0;
            mov_s(f14, f21);
            jal(ctx, 0x137478u, gen::fn_sprDrawSpriteBasic_001159f0);
        }
    }
    // 0x00137548 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00138EE0 sub_138EE0 -- 1000 bytes; frame 0x70: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// (xy, link, alpha): the rank block: two coloured bars (sub_115BC0; grey for sub_172160 / sub_1717C0 links, blue
// otherwise) and "MAX" (rank 10) or the rank digit of sprite font 1.
void sub_138EE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x00138ee0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x68);
    mov_s(f22, f12);
    s2 = a1;
    s1 = a2;
    a0 = s2;
    jal(ctx, 0x138F1Cu, gen::fn_sub_172160_00172160);
    if (v0 == 0) {
        // 0x00138f2c
        charge(ctx, 5);
        a0 = s2;
        jal(ctx, 0x138F30u, gen::fn_sub_1717C0_001717c0);
        if (v0 != 0) {
            goto L_00138f40;
        }
        // 0x0013906c
        charge(ctx, 73);
        lwc1(f21, sp, 0x6C);
        v0 = 0x41C00000;
        mtc1(v0, f20);
        lwc1(f0, sp, 0x68);
        add_s(f23, f20, f0);
        v0 = 0x42140000;
        mtc1(v0, f0);
        add_s(f13, f0, f21);
        a3 = s1 & 0xFF;
        a0 = s0;
        v0 = 0x830000;
        lw(a1, v0, 15192);  // 0x833B58
        a2 = 22;
        mov_s(f12, f23);
        t0 = 1;
        t1 = 47;
        t2 = 73;
        mov_s(f14, f22);
        jal(ctx, 0x1390B8u, gen::fn_sub_115BC0_00115bc0);  // sprite draw with a colour
        v0 = 0x43290000;
        mtc1(v0, f0);
        add_s(f13, f0, f21);
        a3 = s1 & 0xFF;
        a0 = s0;
        v0 = 0x830000;
        lw(a1, v0, 15192);  // 0x833B58
        a2 = 23;
        mov_s(f12, f23);
        t0 = 1;
        t1 = 47;
        t2 = 73;
        mov_s(f14, f22);
        jal(ctx, 0x1390F8u, gen::fn_sub_115BC0_00115bc0);  // sprite draw with a colour
        v0 = 0x42080000;
        mtc1(v0, f1);
        lwc1(f0, sp, 0x68);
        add_s(f23, f1, f0);
        v0 = 0x41900000;
        mtc1(v0, f0);
        add_s(f13, f0, f21);
        a3 = s1 & 0xFF;
        a0 = s0;
        v0 = 0x830000;
        lw(a1, v0, 15192);  // 0x833B58
        a2 = 22;
        mov_s(f12, f23);
        t0 = 1;
        t1 = 47;
        t2 = 73;
        mov_s(f14, f22);
        jal(ctx, 0x139148u, gen::fn_sub_115BC0_00115bc0);  // sprite draw with a colour
        v0 = 0x43160000;
        mtc1(v0, f0);
        add_s(f13, f0, f21);
        a3 = s1 & 0xFF;
        a0 = s0;
        v0 = 0x830000;
        lw(a1, v0, 15192);  // 0x833B58
        a2 = 23;
        mov_s(f12, f23);
        t0 = 1;
        t1 = 47;
        t2 = 73;
        mov_s(f14, f22);
        jal(ctx, 0x139188u, gen::fn_sub_115BC0_00115bc0);  // sprite draw with a colour
        goto L_00139190;
    }
L_00138f40:
    charge(ctx, 75);
    lwc1(f21, sp, 0x6C);
    v0 = 0x41C00000;
    mtc1(v0, f20);
    lwc1(f0, sp, 0x68);
    add_s(f23, f20, f0);
    v0 = 0x42140000;
    mtc1(v0, f0);
    add_s(f13, f0, f21);
    a3 = s1 & 0xFF;
    a0 = s0;
    v0 = 0x830000;
    lw(a1, v0, 15192);  // 0x833B58
    a2 = 22;
    mov_s(f12, f23);
    t0 = 85;
    t1 = 3;
    t2 = 0;
    mov_s(f14, f22);
    jal(ctx, 0x138F8Cu, gen::fn_sub_115BC0_00115bc0);  // sprite draw with a colour
    v0 = 0x43290000;
    mtc1(v0, f0);
    add_s(f13, f0, f21);
    a3 = s1 & 0xFF;
    a0 = s0;
    v0 = 0x830000;
    lw(a1, v0, 15192);  // 0x833B58
    a2 = 23;
    mov_s(f12, f23);
    t0 = 85;
    t1 = 3;
    t2 = 0;
    mov_s(f14, f22);
    jal(ctx, 0x138FCCu, gen::fn_sub_115BC0_00115bc0);  // sprite draw with a colour
    v0 = 0x42080000;
    mtc1(v0, f1);
    lwc1(f0, sp, 0x68);
    add_s(f23, f1, f0);
    v0 = 0x41900000;
    mtc1(v0, f0);
    add_s(f13, f0, f21);
    a3 = s1 & 0xFF;
    a0 = s0;
    v0 = 0x830000;
    lw(a1, v0, 15192);  // 0x833B58
    a2 = 22;
    mov_s(f12, f23);
    t0 = 85;
    t1 = 3;
    t2 = 0;
    mov_s(f14, f22);
    jal(ctx, 0x13901Cu, gen::fn_sub_115BC0_00115bc0);  // sprite draw with a colour
    v0 = 0x43160000;
    mtc1(v0, f0);
    add_s(f13, f0, f21);
    a3 = s1 & 0xFF;
    a0 = s0;
    v0 = 0x830000;
    lw(a1, v0, 15192);  // 0x833B58
    a2 = 23;
    mov_s(f12, f23);
    t0 = 255;
    t1 = t0;
    t2 = 0;
    mov_s(f14, f22);
    jal(ctx, 0x13905Cu, gen::fn_sub_115BC0_00115bc0);  // sprite draw with a colour
L_00139190:
    charge(ctx, 9);
    a0 = dsll32(s2, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x139198u, gen::fn_sub_16DBA0_0016dba0);
    v1 = dsll32(v0, 24);
    v1 = dsra32(v1, 24);
    v0 = 10;
    if (v1 != v0) {
        // 0x001391fc
        charge(ctx, 39);
        lwc1(f21, sp, 0x6C);
        v0 = 0x42280000;
        mtc1(v0, f1);
        lwc1(f0, sp, 0x68);
        add_s(f12, f1, f0);
        v0 = 0x41B80000;
        mtc1(v0, f0);
        add_s(f13, f0, f21);
        a3 = s1 & 0xFF;
        a0 = s0;
        v0 = 0x830000;
        lw(a1, v0, 15172);  // 0x833B44
        a2 = 44;
        mov_s(f14, f22);
        jal(ctx, 0x139238u, gen::fn_sprDrawSpriteBasic_001159f0);
        a0 = 1;
        jal(ctx, 0x139244u, gen::fn_sprFontGetFile_001120a0);
        s3 = v0;
        a0 = dsll32(s2, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x139258u, gen::fn_sub_16DBA0_0016dba0);
        v0 = dsll32(v0, 24);
        v0 = dsra32(v0, 24);
        a2 = addiu(v0, 11);
        v0 = 0x42D20000;
        mtc1(v0, f1);
        lwc1(f0, sp, 0x68);
        add_s(f12, f1, f0);
        add_s(f13, f20, f21);
        a3 = s1 & 0xFF;
        a0 = s0;
        a1 = s3;
        mov_s(f14, f22);
        jal(ctx, 0x139290u, gen::fn_sprDrawSpriteBasic_001159f0);
    } else {
        // 0x001391b4
        charge(ctx, 18);
        v0 = 0x424C0000;
        mtc1(v0, f1);
        lwc1(f0, sp, 0x68);
        add_s(f12, f1, f0);
        v0 = 0x41B80000;
        mtc1(v0, f0);
        add_s(f13, f0, f21);
        a3 = s1 & 0xFF;
        a0 = s0;
        v0 = 0x830000;
        lw(a1, v0, 15172);  // 0x833B44
        a2 = 46;
        mov_s(f14, f22);
        jal(ctx, 0x1391ECu, gen::fn_sprDrawSpriteBasic_001159f0);
    }
    // 0x00139298 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x001392D0 sub_1392D0 -- 900 bytes; frame 0x80: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// (xy, ?, alpha, link): the bust-up picture with a 20-frame pulse (gp-19800) for the special links.
void sub_1392D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x001392d0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x78);
    mov_s(f21, f12);
    s4 = a2;
    s3 = a3;
    lw(v1, gp, g::kComuPulse);  // 0x7CDF98
    v1 = addiu(v1, 1);
    sw(v1, gp, g::kComuPulse);  // 0x7CDF98
    v1 = slti(v1, 20);
    if (v1 == 0) {
        // 0x00139320
        charge(ctx, 1);
        sw(zero, gp, g::kComuPulse);  // 0x7CDF98
    }
    // 0x00139324
    charge(ctx, 4);
    lw(a0, gp, g::kComuPulse);  // 0x7CDF98
    at = slti(a0, 11);
    if (at == 0) {
        // 0x00139334
        charge(ctx, 2);
        v1 = 20;
        a0 = subu(v1, a0);
    }
    // 0x0013933c
    charge(ctx, 7);
    a0 = sll(a0, 7);
    v1 = 10;
    div(a0, v1);
    mflo(s1);
    lw(v1, gp, g::kComuArcanaBuild);  // 0x7CDF74
    if (v1 != 0) {
        // 0x00139358
        charge(ctx, 7);
        v0 = 255;
        s0 = subu(v0, s4);
        a0 = s3;
        jal(ctx, 0x139364u, gen::fn_sub_172160_00172160);
        if (v0 == 0) {
            // 0x00139450
            charge(ctx, 5);
            a0 = s3;
            jal(ctx, 0x139454u, gen::fn_sub_1717C0_001717c0);
            if (v0 == 0) {
                // 0x001395d4
                charge(ctx, 20);
                v0 = si(-256);
                a1 = s0 | v0;
                v0 = 0x41E00000;
                mtc1(v0, f1);
                lwc1(f0, sp, 0x78);
                add_s(f13, f1, f0);
                v0 = 0x422C0000;
                mtc1(v0, f1);
                lwc1(f0, sp, 0x7C);
                add_s(f14, f1, f0);
                v0 = 0x3F800000;
                mtc1(v0, f15);
                a0 = 0;
                mov_s(f12, f21);
                mov_s(f16, f15);
                a2 = 98;
                a3 = 126;
                lw(t0, gp, g::kComuArcanaBuild);  // 0x7CDF74
                jal(ctx, 0x13961Cu, gen::fn_sub_114E70_00114e70);
            } else {
                // 0x00139464
                charge(ctx, 92);
                lwc1(f20, sp, 0x7C);
                v0 = si(-256);
                a1 = s0 | v0;
                v0 = 0x41E00000;
                mtc1(v0, f1);
                lwc1(f0, sp, 0x78);
                add_s(f13, f1, f0);
                v0 = 0x422C0000;
                mtc1(v0, f0);
                add_s(f14, f0, f20);
                v0 = 0x3F800000;
                mtc1(v0, f15);
                a0 = 2;
                mov_s(f12, f21);
                mov_s(f16, f15);
                a2 = 98;
                a3 = 126;
                lw(t0, gp, g::kComuArcanaBuild);  // 0x7CDF74
                jal(ctx, 0x1394B0u, gen::fn_sub_114E70_00114e70);
                v0 = 0x41C00000;
                mtc1(v0, f1);
                lwc1(f0, sp, 0x78);
                add_s(f22, f1, f0);
                v0 = 0x42140000;
                mtc1(v0, f0);
                add_s(f13, f0, f20);
                a3 = s4 & 0xFF;
                v0 = addiu(s1, 127);
                t0 = v0 & 0xFF;
                a0 = s2;
                v0 = 0x830000;
                lw(a1, v0, 15192);  // 0x833B58
                a2 = 41;
                mov_s(f12, f22);
                mov_s(f14, f21);
                jal(ctx, 0x1394FCu, gen::fn_sub_115AD0_00115ad0);  // sprite draw with a tint
                v0 = 0x43290000;
                mtc1(v0, f0);
                add_s(f13, f0, f20);
                a3 = s4 & 0xFF;
                v0 = addiu(s1, 127);
                t0 = v0 & 0xFF;
                a0 = s2;
                v0 = 0x830000;
                lw(a1, v0, 15192);  // 0x833B58
                a2 = 42;
                mov_s(f12, f22);
                mov_s(f14, f21);
                jal(ctx, 0x139538u, gen::fn_sub_115AD0_00115ad0);  // sprite draw with a tint
                lwc1(f1, sp, 0x78);
                v0 = 0x41400000;
                mtc1(v0, f0);
                sub_s(f12, f1, f0);
                v0 = 0x41100000;
                mtc1(v0, f0);
                sub_s(f13, f20, f0);
                a3 = s4 & 0xFF;
                v0 = addiu(s1, 127);
                t0 = v0 & 0xFF;
                a0 = s2;
                v0 = 0x830000;
                lw(a1, v0, 15196);  // 0x833B5C
                a2 = 0;
                mov_s(f14, f21);
                jal(ctx, 0x139584u, gen::fn_sub_115AD0_00115ad0);  // sprite draw with a tint
                v0 = 0x41D00000;
                mtc1(v0, f1);
                lwc1(f0, sp, 0x78);
                add_s(f12, f1, f0);
                v0 = 0x43140000;
                mtc1(v0, f0);
                add_s(f13, f0, f20);
                a3 = s4 & 0xFF;
                a0 = s2;
                v0 = 0x830000;
                lw(a1, v0, 15192);  // 0x833B58
                a2 = 39;
                mov_s(f14, f21);
                jal(ctx, 0x1395C4u, gen::fn_sprDrawSpriteBasic_001159f0);
            }
        } else {
            // 0x00139374
            charge(ctx, 55);
            lwc1(f20, sp, 0x7C);
            v0 = si(-256);
            a1 = s0 | v0;
            v0 = 0x41E00000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x78);
            add_s(f13, f1, f0);
            v0 = 0x422C0000;
            mtc1(v0, f0);
            add_s(f14, f0, f20);
            v0 = 0x3F800000;
            mtc1(v0, f15);
            a0 = 0;
            mov_s(f12, f21);
            mov_s(f16, f15);
            a2 = 98;
            a3 = 126;
            lw(t0, gp, g::kComuArcanaBuild);  // 0x7CDF74
            jal(ctx, 0x1393C0u, gen::fn_sub_114E70_00114e70);
            v0 = 0x41700000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x78);
            add_s(f12, f1, f0);
            v0 = 0x42040000;
            mtc1(v0, f0);
            add_s(f13, f0, f20);
            a3 = s4 & 0xFF;
            a0 = s2;
            v0 = 0x830000;
            lw(a1, v0, 15204);  // 0x833B64
            a2 = 0;
            mov_s(f14, f21);
            jal(ctx, 0x139400u, gen::fn_sprDrawSpriteBasic_001159f0);
            v0 = 0x41D00000;
            mtc1(v0, f1);
            lwc1(f0, sp, 0x78);
            add_s(f12, f1, f0);
            v0 = 0x43140000;
            mtc1(v0, f0);
            add_s(f13, f0, f20);
            a3 = s4 & 0xFF;
            a0 = s2;
            v0 = 0x830000;
            lw(a1, v0, 15192);  // 0x833B58
            a2 = 40;
            mov_s(f14, f21);
            jal(ctx, 0x139440u, gen::fn_sprDrawSpriteBasic_001159f0);
        }
    }
    // 0x00139624 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x0013BCE0 sub_13BCE0 -- 356 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// (alpha): the item screen's scrolling ribbon: sprite 58 of 0x833A50 (twice near the wrap), x gp-19808 moving by -1,
// wrapping at -720.
void sub_13BCE0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f20{ctx, 20};
    // 0x0013bce0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s0 = a0;
    lw(v0, gp, g::kItemRibbonX);  // 0x7CDF90
    at = slti(v0, -100);
    if (at != 0) {
        // 0x0013bd08
        charge(ctx, 27);
        v0 = addiu(v0, 720);
        mtc1(v0, f0);
        cvt_s_w(f20, f0);
        a0 = 0;
        v0 = 0x830000;
        lw(a1, v0, 14928);  // 0x833A50
        a2 = 58;
        jal(ctx, 0x13BD28u, gen::fn_sprCreateHandle_001158b0);
        s1 = v0;
        v1 = 0x42D00000;
        sw(v1, v0, 44);
        swc1(f20, v0, 16);
        v1 = 309;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        swc1(f0, v0, 20);
        sb(s0, v0, 24);
        a0 = s1;
        a1 = 1;
        jal(ctx, 0x13BD60u, gen::fn_sub_1127D0_001127d0);  // sprDrawSprite
        a0 = s1;
        jal(ctx, 0x13BD6Cu, gen::fn_sub_115980_00115980);  // release the sprite handle
    }
    // 0x0013bd74
    charge(ctx, 37);
    lwc1(f0, gp, g::kItemRibbonX);  // 0x7CDF90
    cvt_s_w(f20, f0);
    a0 = 0;
    v0 = 0x830000;
    lw(a1, v0, 14928);  // 0x833A50
    a2 = 58;
    jal(ctx, 0x13BD8Cu, gen::fn_sprCreateHandle_001158b0);
    s1 = v0;
    v1 = 0x42D00000;
    sw(v1, v0, 44);
    swc1(f20, v0, 16);
    v1 = 309;
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, v0, 20);
    sb(s0, v0, 24);
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x13BDC4u, gen::fn_sub_1127D0_001127d0);  // sprDrawSprite
    a0 = s1;
    jal(ctx, 0x13BDD0u, gen::fn_sub_115980_00115980);  // release the sprite handle
    lw(v1, gp, g::kItemRibbonX);  // 0x7CDF90
    v1 = addiu(v1, -1);
    sw(v1, gp, g::kItemRibbonX);  // 0x7CDF90
    mtc1(v1, f0);
    cvt_s_w(f1, f0);
    v1 = lui(0xC434);
    mtc1(v1, f0);
    c_lt_s(f1, f0);
    if (cond(ctx)) {
        // 0x0013be08
        charge(ctx, 8);
        v1 = 0x44340000;
        mtc1(v1, f0);
        add_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sw(v1, gp, g::kItemRibbonX);  // 0x7CDF90
    }
    // 0x0013be28 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0013BE50 sub_13BE50 -- 996 bytes; frame 0xA0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_ItemUseOnTarget] (item work, target): uses the selected item on the protagonist (0), the n-th party member
// (n) or everyone (-2): sub_17BC20 / sub_17B860 per member (skipping those sub_1C7CE0 rejects); when anything happened
// the stock count drops (sub_170860) and a used-up row leaves the list (scroll / cursor clamped). Returns 1 when used.
void sub_13BE50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0013be50
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
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
    s5 = a0;
    s4 = a1;
    lw(v1, a0, 2416);
    lw(v0, a0, 2420);
    s3 = addu(v1, v0);
    fp = sll(s3, 3);
    v0 = addu(fp, s5);
    lw(s7, v0, 12);
    a0 = dsll32(s7, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x13BEA4u, gen::fn_sub_170E90_00170e90);
    s0 = v0;
    v0 = si(-2);
    if (s4 != v0) {
        // 0x0013bfb4
        charge(ctx, 3);
        s2 = 0;
        if (s4 != 0) {
            // 0x0013c004
            charge(ctx, 4);
            s6 = 0;
            s1 = 0;
            for (;;) {
                // 0x0013c0c0
                charge(ctx, 3);
                v0 = slti(s1, 3);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0013c014
                charge(ctx, 7);
                a0 = s1;
                jal(ctx, 0x13C018u, gen::fn_sub_16DD60_0016dd60);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                if (v0 != 0) {
                    // 0x0013c030
                    charge(ctx, 3);
                    s6 = addiu(s6, 1);
                    if (s4 != s6) {
                        goto L_0013c0bc;
                    }
                    goto L_0013c03c_17;
                }
            L_0013c0bc:
                charge(ctx, 1);
                s1 = addiu(s1, 1);
            }
        } else {
            // 0x0013bfc0
            charge(ctx, 8);
            lhu(a2, s0, 8);
            a0 = 1;
            a1 = a0;
            a3 = a0;
            jal(ctx, 0x13BFD0u, gen::fn_sub_17BC20_0017bc20);
            if (v0 == 0) {
                // 0x0013bfe0
                charge(ctx, 9);
                s2 = 1;
                lhu(a2, s0, 8);
                a0 = s2;
                a1 = s2;
                a3 = s2;
                jal(ctx, 0x13BFF4u, gen::fn_sub_17B860_0017b860);
            }
        }
    } else {
        // 0x0013bebc
        charge(ctx, 9);
        s2 = 0;
        lhu(a2, s0, 8);
        a0 = 1;
        a1 = a0;
        a3 = a0;
        jal(ctx, 0x13BED0u, gen::fn_sub_17BC20_0017bc20);
        if (v0 == 0) {
            // 0x0013bee0
            charge(ctx, 7);
            s2 = 1;
            lhu(a2, s0, 8);
            a0 = s2;
            a1 = s2;
            a3 = s2;
            jal(ctx, 0x13BEF4u, gen::fn_sub_17B860_0017b860);
        }
        // 0x0013befc
        charge(ctx, 3);
        s1 = 0;
        for (;;) {
            // 0x0013bfa0
            charge(ctx, 3);
            v0 = slti(s1, 3);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0013bf08
            charge(ctx, 7);
            a0 = s1;
            jal(ctx, 0x13BF0Cu, gen::fn_sub_16DD60_0016dd60);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            if (v0 != 0) {
                // 0x0013bf24
                charge(ctx, 9);
                a0 = s1;
                jal(ctx, 0x13BF28u, gen::fn_sub_16DD60_0016dd60);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x13BF38u, gen::fn_sub_1C7CE0_001c7ce0);
                if (v0 != 0) {
                    // 0x0013bf48
                    charge(ctx, 11);
                    a0 = s1;
                    jal(ctx, 0x13BF4Cu, gen::fn_sub_16DD60_0016dd60);
                    lhu(a2, s0, 8);
                    a0 = 1;
                    a1 = v0;
                    a3 = a0;
                    jal(ctx, 0x13BF64u, gen::fn_sub_17BC20_0017bc20);
                    if (v0 == 0) {
                        // 0x0013bf74
                        charge(ctx, 10);
                        s2 = 1;
                        a0 = s1;
                        jal(ctx, 0x13BF7Cu, gen::fn_sub_16DD60_0016dd60);
                        lhu(a2, s0, 8);
                        a0 = s2;
                        a1 = v0;
                        a3 = a0;
                        jal(ctx, 0x13BF94u, gen::fn_sub_17B860_0017b860);
                    }
                }
            }
            // 0x0013bf9c
            charge(ctx, 1);
            s1 = addiu(s1, 1);
        }
        // 0x0013bfac
        charge(ctx, 2);
    }
L_0013c0cc:
    charge(ctx, 2);
    if (s2 != 0) {
        // 0x0013c0d4
        charge(ctx, 5);
        v0 = addu(fp, s5);
        lw(v0, v0, 16);
        a0 = 1;
        if (v0 != a0) {
            // 0x0013c1d4
            charge(ctx, 10);
            v0 = sll(s3, 3);
            v1 = addu(v0, s5);
            lw(v0, v1, 16);
            v0 = addiu(v0, -1);
            sw(v0, v1, 16);
            a1 = dsll32(s7, 16);
            a1 = dsra32(a1, 16);
            lhu(a2, v1, 16);
            jal(ctx, 0x13C1F4u, gen::fn_sub_170860_00170860);
        } else {
            // 0x0013c0e8
            charge(ctx, 7);
            a1 = dsll32(s7, 16);
            a1 = dsra32(a1, 16);
            a2 = 0;
            jal(ctx, 0x13C0F4u, gen::fn_sub_170860_00170860);
            for (;;) {
                // 0x0013c120
                charge(ctx, 5);
                lw(a0, s5, 2412);
                v0 = addiu(a0, -1);
                v0 = slt(s3, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0013c104
                charge(ctx, 7);
                v0 = sll(s3, 3);
                v0 = addu(s5, v0);
                lwc1(f1, v0, 20);
                lwc1(f0, v0, 24);
                swc1(f1, v0, 12);
                swc1(f0, v0, 16);
                s3 = addiu(s3, 1);
            }
            // 0x0013c134
            charge(ctx, 13);
            v1 = si(-1);
            v0 = sll(a0, 3);
            v0 = addu(v0, s5);
            sw(v1, v0, 12);
            lw(v0, s5, 2412);
            v0 = sll(v0, 3);
            v0 = addu(v0, s5);
            sw(zero, v0, 16);
            lw(v0, s5, 2412);
            v1 = addiu(v0, -1);
            sw(v1, s5, 2412);
            if (v1 != 0) {
                // 0x0013c178
                charge(ctx, 4);
                lw(v0, s5, 2416);
                v0 = slt(v0, v1);
                if (v0 != 0) {
                    // 0x0013c19c
                    charge(ctx, 3);
                    at = slti(v1, 5);
                    if (at == 0) {
                        // 0x0013c1b4
                        charge(ctx, 5);
                        v1 = addiu(v1, -5);
                        lw(v0, s5, 2420);
                        at = slt(v1, v0);
                        if (at != 0) {
                            // 0x0013c1c8
                            charge(ctx, 3);
                            sw(v1, s5, 2420);
                        }
                    } else {
                        // 0x0013c1a8
                        charge(ctx, 3);
                        sw(zero, s5, 2420);
                    }
                } else {
                    // 0x0013c188
                    charge(ctx, 5);
                    v0 = addiu(v1, -1);
                    sw(v0, s5, 2416);
                    sw(zero, s5, 2420);
                }
            } else {
                // 0x0013c168
                charge(ctx, 4);
                sw(zero, s5, 2420);
                sw(zero, s5, 2416);
            }
        }
    }
    // 0x0013c1fc (the shared epilogue, written out on this path)
    charge(ctx, 14);
    v0 = s2;
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
    sp = addiu(sp, 0xA0);
    return;
L_0013c03c_17:
    charge(ctx, 9);
    a0 = s1;
    jal(ctx, 0x13C040u, gen::fn_sub_16DD60_0016dd60);
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x13C050u, gen::fn_sub_1C7CE0_001c7ce0);
    if (v0 != 0) {
        // 0x0013c060
        charge(ctx, 11);
        a0 = s1;
        jal(ctx, 0x13C064u, gen::fn_sub_16DD60_0016dd60);
        lhu(a2, s0, 8);
        a0 = 1;
        a1 = v0;
        a3 = a0;
        jal(ctx, 0x13C07Cu, gen::fn_sub_17BC20_0017bc20);
        if (v0 == 0) {
            // 0x0013c08c
            charge(ctx, 12);
            s2 = 1;
            a0 = s1;
            jal(ctx, 0x13C094u, gen::fn_sub_16DD60_0016dd60);
            lhu(a2, s0, 8);
            a0 = s2;
            a1 = v0;
            a3 = a0;
            jal(ctx, 0x13C0ACu, gen::fn_sub_17B860_0017b860);
        }
    }
    goto L_0013c0cc;
}

// 0x0013C240 sub_13C240 -- 1120 bytes; frame 0x330: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// (list, pc, slot): builds the equipment candidate list of a member's slot: the equipped entry first
// (datGetEquipmentIdx(pc, slot)), then every held hero-stock entry the member may use (item flags bit 32 << (pc - 1),
// sub_1712D0) whose kind (sub_171250) is the slot (0 weapon, 1 armour, 2 accessory) and that is not the equipped one,
// as 36-byte rows from +100 (the sub_13CC90 layout); +11620 = the count.
void sub_13C240(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0013c240
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x330);
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
    s5 = a0;
    s0 = a1;
    s7 = a2;
    s3 = 0;
    s1 = 0;
    for (;;) {
        // 0x0013c2b8
        charge(ctx, 3);
        v0 = slti(s1, 300);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0013c288
        charge(ctx, 7);
        a0 = 1;
        a1 = s1;
        jal(ctx, 0x13C290u, gen::fn_sub_16F630_0016f630);
        v0 = v0 & 0xFFFF;
        if (v0 != 0) {
            // 0x0013c2a4
            charge(ctx, 4);
            v0 = sll(s3, 1);
            v0 = addu(v0, sp);
            sh(s1, v0, 208);
            s3 = addiu(s3, 1);
        }
        // 0x0013c2b4
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0013c2c4
    charge(ctx, 3);
    at = slti(s3, 2);
    if (at == 0) {
        // 0x0013c2d0
        charge(ctx, 7);
        a0 = addiu(sp, 0xD0);
        a1 = s3;
        a2 = 2;
        a3 = 0x130000;
        a3 = addiu(a3, 4096);  // &sub_131000
        jal(ctx, 0x13C2E4u, gen::fn_qsort_005225f8);
    }
    // 0x0013c2ec
    charge(ctx, 43);
    s4 = 0;
    v0 = dsll32(s0, 16);
    v0 = dsra32(v0, 16);
    v1 = addiu(v0, -1);
    v0 = 32;
    v0 = sllv(v0, v1);
    sq(v0, sp, 0xC0);
    a0 = s0;
    a1 = s7;
    jal(ctx, 0x13C310u, gen::fn_datGetEquipmentIdx_0016cb80);
    s1 = dsll32(v0, 16);
    s1 = dsra32(s1, 16);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x13C328u, gen::fn_sub_16F630_0016f630);
    v0 = v0 & 0xFFFF;
    sw(v0, s5, 100);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x13C340u, gen::fn_sub_16F720_0016f720);
    sw(v0, s5, 120);
    lh(a0, s5, 100);
    jal(ctx, 0x13C350u, gen::fn_sub_171250_00171250);
    sb(v0, s5, 126);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x13C364u, gen::fn_sub_16F900_0016f900);
    sb(v0, s5, 124);
    a0 = s0;
    a1 = s1;
    jal(ctx, 0x13C378u, gen::fn_sub_16F810_0016f810);
    sb(v0, s5, 125);
    sw(s1, s5, 104);
    lbu(a0, s5, 126);
    v1 = 3;
    if (a0 != v1) {
        // 0x0013c398
        charge(ctx, 3);
        v1 = 2;
        if (a0 == v1) {
            // 0x0013c40c
            charge(ctx, 5);
            a0 = s0;
            a1 = s1;
            jal(ctx, 0x13C414u, gen::fn_sub_16FCC0_0016fcc0);
            sh(v0, s5, 134);
        } else {
            // 0x0013c3a4
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                // 0x0013c3f0
                charge(ctx, 7);
                a0 = s0;
                a1 = s1;
                jal(ctx, 0x13C3F8u, gen::fn_sub_16FBD0_0016fbd0);
                sh(v0, s5, 132);
            } else {
                // 0x0013c3b0
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x0013c3c0
                    charge(ctx, 12);
                    a0 = s0;
                    a1 = s1;
                    jal(ctx, 0x13C3C8u, gen::fn_sub_16F9F0_0016f9f0);
                    sh(v0, s5, 128);
                    a0 = s0;
                    a1 = s1;
                    jal(ctx, 0x13C3DCu, gen::fn_sub_16FAE0_0016fae0);
                    sh(v0, s5, 130);
                } else {
                    // 0x0013c3b8
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x0013c420
    charge(ctx, 7);
    s4 = addiu(s4, 1);
    s2 = 0;
    v1 = dsll32(s7, 16);
    v1 = dsra32(v1, 16);
    sq(v1, sp, 0xB0);
    for (;;) {
        // 0x0013c634
        charge(ctx, 3);
        v1 = slt(s2, s3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0013c43c
        charge(ctx, 10);
        v0 = sll(s2, 1);
        v0 = addu(v0, sp);
        s1 = addiu(v0, 208);
        lhu(a1, s1, 0);
        a0 = 1;
        jal(ctx, 0x13C450u, gen::fn_sub_16F630_0016f630);
        v1 = v0 & 0xFFFF;
        if (v1 != 0) {
            // 0x0013c464
            charge(ctx, 12);
            lhu(a1, s1, 0);
            a0 = 1;
            jal(ctx, 0x13C46Cu, gen::fn_sub_16F630_0016f630);
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x13C47Cu, gen::fn_sub_1712D0_001712d0);
            lq(v1, sp, 0xC0);
            v1 = v1 & v0;
            if (v1 != 0) {
                // 0x0013c494
                charge(ctx, 11);
                lhu(a1, s1, 0);
                a0 = 1;
                jal(ctx, 0x13C49Cu, gen::fn_sub_16F630_0016f630);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x13C4ACu, gen::fn_sub_171250_00171250);
                lq(v1, sp, 0xB0);
                if (v1 == v0) {
                    // 0x0013c4c0
                    charge(ctx, 9);
                    lhu(fp, s1, 0);
                    a0 = 1;
                    a1 = s7;
                    jal(ctx, 0x13C4CCu, gen::fn_datGetEquipmentIdx_0016cb80);
                    v1 = dsll32(v0, 16);
                    v1 = dsra32(v1, 16);
                    if (fp != v1) {
                        // 0x0013c4e4
                        charge(ctx, 43);
                        v0 = sll(s2, 1);
                        v0 = addu(v0, sp);
                        s6 = addiu(v0, 208);
                        v0 = sll(s4, 3);
                        v0 = addu(v0, s4);
                        v0 = sll(v0, 2);
                        s0 = addu(s5, v0);
                        v0 = addiu(s0, 100);
                        sq(v0, sp, 0xA0);
                        a0 = 1;
                        a1 = fp;
                        jal(ctx, 0x13C510u, gen::fn_sub_16F630_0016f630);
                        v1 = v0 & 0xFFFF;
                        lq(v0, sp, 0xA0);
                        sw(v1, v0, 0);
                        lhu(a1, s6, 0);
                        a0 = 1;
                        jal(ctx, 0x13C52Cu, gen::fn_sub_16F720_0016f720);
                        sw(v0, s0, 120);
                        fp = addiu(s0, 0x7E);
                        lq(v0, sp, 0xA0);
                        lh(a0, v0, 0);
                        jal(ctx, 0x13C544u, gen::fn_sub_171250_00171250);
                        sb(v0, fp, 0x0);
                        lhu(a1, s6, 0);
                        a0 = 1;
                        jal(ctx, 0x13C558u, gen::fn_sub_16F900_0016f900);
                        sb(v0, s0, 124);
                        lhu(a1, s6, 0);
                        a0 = 1;
                        jal(ctx, 0x13C56Cu, gen::fn_sub_16F810_0016f810);
                        sb(v0, s0, 125);
                        lhu(v1, s6, 0);
                        sw(v1, s0, 104);
                        lbu(a1, fp, 0x0);
                        v1 = 3;
                        if (a1 != v1) {
                            // 0x0013c590
                            charge(ctx, 3);
                            v1 = 2;
                            if (a1 == v1) {
                                // 0x0013c618
                                charge(ctx, 5);
                                lhu(a1, s1, 0);
                                a0 = 1;
                                jal(ctx, 0x13C620u, gen::fn_sub_16FCC0_0016fcc0);
                                sh(v0, s0, 134);
                            } else {
                                // 0x0013c59c
                                charge(ctx, 3);
                                a0 = 1;
                                if (a1 == a0) {
                                    // 0x0013c600
                                    charge(ctx, 6);
                                    lhu(a1, s1, 0);
                                    jal(ctx, 0x13C604u, gen::fn_sub_16FBD0_0016fbd0);
                                    sh(v0, s0, 132);
                                } else {
                                    // 0x0013c5a8
                                    charge(ctx, 2);
                                    if (a1 == 0) {
                                        // 0x0013c5b8
                                        charge(ctx, 18);
                                        v0 = sll(s2, 1);
                                        v0 = addu(v0, sp);
                                        s0 = addiu(v0, 208);
                                        v0 = sll(s4, 3);
                                        v0 = addu(v0, s4);
                                        v0 = sll(v0, 2);
                                        s1 = addu(s5, v0);
                                        lhu(a1, s0, 0);
                                        jal(ctx, 0x13C5D8u, gen::fn_sub_16F9F0_0016f9f0);
                                        sh(v0, s1, 128);
                                        lhu(a1, s0, 0);
                                        a0 = 1;
                                        jal(ctx, 0x13C5ECu, gen::fn_sub_16FAE0_0016fae0);
                                        sh(v0, s1, 130);
                                    } else {
                                        // 0x0013c5b0
                                        charge(ctx, 2);
                                    }
                                }
                            }
                        }
                        // 0x0013c62c
                        charge(ctx, 1);
                        s4 = addiu(s4, 1);
                    }
                }
            }
        }
        // 0x0013c630
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x0013c640
    charge(ctx, 3);
    a0 = 0;
    for (;;) {
        // 0x0013c65c
        charge(ctx, 3);
        v1 = slti(a0, 21);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0013c64c
        charge(ctx, 4);
        v1 = sll(a0, 2);
        v1 = addu(s5, v1);
        sw(zero, v1, 12);
        a0 = addiu(a0, 1);
    }
    // 0x0013c668
    charge(ctx, 14);
    sw(s4, s5, 11620);
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
    sp = addiu(sp, 0x330);
}

// 0x0013C6A0 sub_13C6A0 -- 212 bytes; frame 0x20: ra sp+0x0
// (id): the lowest set bit of an item's target / attribute word (sub_170ED0 by kind 0..3); 0 when none.
void sub_13C6A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0013c6a0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    a1 = addiu(sp, 0x1C);
    jal(ctx, 0x13C6ACu, gen::fn_sub_170ED0_00170ed0);
    lw(a0, sp, 0x1C);
    v1 = 3;
    if (a0 == v1) {
        // 0x0013c710
        charge(ctx, 3);
        lw(a1, v0, 0);
    L_0013c728:
        charge(ctx, 4);
        v0 = 0;
        a0 = 1;
        for (;;) {
            // 0x0013c754
            charge(ctx, 3);
            v1 = slti(v0, 32);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0013c738
            charge(ctx, 4);
            v1 = sllv(a0, v0);
            v1 = a1 & v1;
            if (v1 != 0) {
                goto L_0013c748_12;
            }
            // 0x0013c750
            charge(ctx, 1);
            v0 = addiu(v0, 1);
        }
        // 0x0013c760
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0013c6c4
        charge(ctx, 3);
        v1 = 2;
        if (a0 == v1) {
            // 0x0013c704
            charge(ctx, 3);
            lw(a1, v0, 4);
            goto L_0013c728;
        }
        // 0x0013c6d0
        charge(ctx, 3);
        v1 = 1;
        if (a0 == v1) {
            // 0x0013c6f8
            charge(ctx, 3);
            lw(a1, v0, 4);
            goto L_0013c728;
        }
        // 0x0013c6dc
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x0013c6ec
            charge(ctx, 3);
            lw(a1, v0, 4);
            goto L_0013c728;
        }
        // 0x0013c6e4
        charge(ctx, 2);
        // 0x0013c71c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0013c764 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
    return;
L_0013c748_12:
    charge(ctx, 2);
    // 0x0013c764 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0013CC90 sub_13CC90 -- 748 bytes; frame 0x310: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// (list): builds the equipment-stock list: every held entry of the hero stock (indices 0..299 with an item, ordered by
// item id through qsort / sub_131000) as a 36-byte row from +100: +0 item id, +4 stock index, +20 the lowest of the 21
// slot bits of the entry's word +4, +24 effect, +25 byte +8, +26 kind, +28 / +30 power / accuracy (weapons), +32
// evasion (kind 1), +34 defense (kind 2); clears the 21 words at +12; +11620 = the count.
void sub_13CC90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0013cc90
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x310);
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
    s5 = a0;
    s3 = 0;
    s0 = 0;
    for (;;) {
        // 0x0013cd00
        charge(ctx, 3);
        v1 = slti(s0, 300);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0013ccd0
        charge(ctx, 7);
        a0 = 1;
        a1 = s0;
        jal(ctx, 0x13CCD8u, gen::fn_sub_16F630_0016f630);
        v1 = v0 & 0xFFFF;
        if (v1 != 0) {
            // 0x0013ccec
            charge(ctx, 4);
            v1 = sll(s3, 1);
            v1 = addu(v1, sp);
            sh(s0, v1, 176);
            s3 = addiu(s3, 1);
        }
        // 0x0013ccfc
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x0013cd0c
    charge(ctx, 3);
    at = slti(s3, 2);
    if (at == 0) {
        // 0x0013cd18
        charge(ctx, 7);
        a0 = addiu(sp, 0xB0);
        a1 = s3;
        a2 = 2;
        a3 = 0x130000;
        a3 = addiu(a3, 4096);  // &sub_131000
        jal(ctx, 0x13CD2Cu, gen::fn_qsort_005225f8);
    }
    // 0x0013cd34
    charge(ctx, 4);
    s4 = 0;
    s2 = 0;
    for (;;) {
        // 0x0013cf10
        charge(ctx, 3);
        v1 = slt(s2, s3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0013cd44
        charge(ctx, 10);
        v0 = sll(s2, 1);
        v0 = addu(v0, sp);
        s7 = addiu(v0, 176);
        lhu(a1, s7, 0);
        a0 = 1;
        jal(ctx, 0x13CD58u, gen::fn_sub_16F630_0016f630);
        v1 = v0 & 0xFFFF;
        if (v1 != 0) {
            // 0x0013cd6c
            charge(ctx, 19);
            v0 = sll(s2, 1);
            v0 = addu(v0, sp);
            s6 = addiu(v0, 176);
            v0 = sll(s4, 3);
            v0 = addu(v0, s4);
            v0 = sll(v0, 2);
            s1 = addu(s5, v0);
            v0 = addiu(s1, 100);
            sq(v0, sp, 0xA0);
            lhu(a1, s6, 0);
            a0 = 1;
            jal(ctx, 0x13CD98u, gen::fn_sub_16F630_0016f630);
            v1 = v0 & 0xFFFF;
            lq(v0, sp, 0xA0);
            sw(v1, v0, 0);
            s0 = 0;
            for (;;) {
                // 0x0013cdec
                charge(ctx, 3);
                v0 = slti(s0, 21);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0013cdb8
                charge(ctx, 9);
                lhu(a1, s6, 0);
                a0 = 1;
                jal(ctx, 0x13CDC0u, gen::fn_sub_16F720_0016f720);
                v1 = 1;
                v1 = sllv(v1, s0);
                v0 = v1 & v0;
                if (v0 != 0) {
                    goto L_0013cddc_11;
                }
                // 0x0013cde8
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
        L_0013cdf8:
            charge(ctx, 29);
            v0 = sll(s4, 3);
            v0 = addu(v0, s4);
            v0 = sll(v0, 2);
            s0 = addu(s5, v0);
            fp = addiu(s0, 0x7E);
            lq(v0, sp, 0xA0);
            lh(a0, v0, 0);
            jal(ctx, 0x13CE14u, gen::fn_sub_171250_00171250);
            sb(v0, fp, 0x0);
            v0 = sll(s2, 1);
            v0 = addu(v0, sp);
            s6 = addiu(v0, 176);
            lhu(a1, s6, 0);
            a0 = 1;
            jal(ctx, 0x13CE34u, gen::fn_sub_16F900_0016f900);
            sb(v0, s0, 124);
            lhu(a1, s6, 0);
            a0 = 1;
            jal(ctx, 0x13CE48u, gen::fn_sub_16F810_0016f810);
            sb(v0, s0, 125);
            lhu(v1, s6, 0);
            sw(v1, s0, 104);
            lbu(a1, fp, 0x0);
            v1 = 3;
            if (a1 != v1) {
                // 0x0013ce6c
                charge(ctx, 3);
                v1 = 2;
                if (a1 == v1) {
                    // 0x0013cef4
                    charge(ctx, 5);
                    lhu(a1, s7, 0);
                    a0 = 1;
                    jal(ctx, 0x13CEFCu, gen::fn_sub_16FCC0_0016fcc0);
                    sh(v0, s1, 134);
                } else {
                    // 0x0013ce78
                    charge(ctx, 3);
                    a0 = 1;
                    if (a1 == a0) {
                        // 0x0013cedc
                        charge(ctx, 6);
                        lhu(a1, s7, 0);
                        jal(ctx, 0x13CEE0u, gen::fn_sub_16FBD0_0016fbd0);
                        sh(v0, s1, 132);
                    } else {
                        // 0x0013ce84
                        charge(ctx, 2);
                        if (a1 == 0) {
                            // 0x0013ce94
                            charge(ctx, 18);
                            v0 = sll(s2, 1);
                            v0 = addu(v0, sp);
                            s0 = addiu(v0, 176);
                            v0 = sll(s4, 3);
                            v0 = addu(v0, s4);
                            v0 = sll(v0, 2);
                            s1 = addu(s5, v0);
                            lhu(a1, s0, 0);
                            jal(ctx, 0x13CEB4u, gen::fn_sub_16F9F0_0016f9f0);
                            sh(v0, s1, 128);
                            lhu(a1, s0, 0);
                            a0 = 1;
                            jal(ctx, 0x13CEC8u, gen::fn_sub_16FAE0_0016fae0);
                            sh(v0, s1, 130);
                        } else {
                            // 0x0013ce8c
                            charge(ctx, 2);
                        }
                    }
                }
            }
            // 0x0013cf08
            charge(ctx, 1);
            s4 = addiu(s4, 1);
        }
        // 0x0013cf0c
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x0013cf1c
    charge(ctx, 3);
    a0 = 0;
    for (;;) {
        // 0x0013cf38
        charge(ctx, 3);
        v1 = slti(a0, 21);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0013cf28
        charge(ctx, 4);
        v1 = sll(a0, 2);
        v1 = addu(s5, v1);
        sw(zero, v1, 12);
        a0 = addiu(a0, 1);
    }
    // 0x0013cf44
    charge(ctx, 14);
    sw(s4, s5, 11620);
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
    sp = addiu(sp, 0x310);
    return;
L_0013cddc_11:
    charge(ctx, 3);
    sw(s0, s1, 120);
    goto L_0013cdf8;
}

// 0x0013CF80 sub_13CF80 -- 532 bytes; frame 0xA0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// (pc, list): builds a member's equipment list by slot (21 categories x 4 slots); +11620 = the count.
void sub_13CF80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0013cf80
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
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
    s5 = a0;
    s4 = a1;
    s2 = 0;
    s1 = 0;
    for (;;) {
        // 0x0013d150
        charge(ctx, 3);
        v1 = slti(s1, 21);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0013cfc4
        charge(ctx, 8);
        v1 = sll(s1, 2);
        v1 = addu(s4, v1);
        sw(s2, v1, 12);
        v1 = 1;
        fp = sllv(v1, s1);
        s3 = 0;
        for (;;) {
            // 0x0013d140
            charge(ctx, 3);
            v1 = slti(s3, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0013cfe4
            charge(ctx, 8);
            a0 = dsll32(s5, 16);
            a0 = dsra32(a0, 16);
            a1 = s3;
            jal(ctx, 0x13CFF0u, gen::fn_sub_16F720_0016f720);
            v1 = fp & v0;
            if (v1 != 0) {
                // 0x0013d004
                charge(ctx, 35);
                v0 = sll(s2, 3);
                v0 = addu(v0, s2);
                v0 = sll(v0, 2);
                s0 = addu(s4, v0);
                s6 = addiu(s0, 100);
                a0 = dsll32(s5, 16);
                a0 = dsra32(a0, 16);
                a1 = s3;
                jal(ctx, 0x13D024u, gen::fn_sub_16F630_0016f630);
                v0 = v0 & 0xFFFF;
                sw(v0, s6, 0);
                sw(s1, s0, 120);
                s7 = addiu(s0, 126);
                lh(a0, s6, 0);
                jal(ctx, 0x13D040u, gen::fn_sub_171250_00171250);
                sb(v0, s7, 0);
                a0 = dsll32(s5, 16);
                a0 = dsra32(a0, 16);
                a1 = s3;
                jal(ctx, 0x13D058u, gen::fn_sub_16F900_0016f900);
                sb(v0, s0, 124);
                a0 = dsll32(s5, 16);
                a0 = dsra32(a0, 16);
                a1 = s3;
                jal(ctx, 0x13D070u, gen::fn_sub_16F810_0016f810);
                sb(v0, s0, 125);
                sw(s3, s0, 104);
                lbu(a0, s7, 0);
                v1 = 3;
                if (a0 != v1) {
                    // 0x0013d090
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 == v1) {
                        // 0x0013d120
                        charge(ctx, 6);
                        a0 = dsll32(s5, 16);
                        a0 = dsra32(a0, 16);
                        a1 = s3;
                        jal(ctx, 0x13D12Cu, gen::fn_sub_16FCC0_0016fcc0);
                        sh(v0, s0, 134);
                    } else {
                        // 0x0013d09c
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x0013d100
                            charge(ctx, 8);
                            a0 = dsll32(s5, 16);
                            a0 = dsra32(a0, 16);
                            a1 = s3;
                            jal(ctx, 0x13D10Cu, gen::fn_sub_16FBD0_0016fbd0);
                            sh(v0, s0, 132);
                        } else {
                            // 0x0013d0a8
                            charge(ctx, 2);
                            if (a0 == 0) {
                                // 0x0013d0b8
                                charge(ctx, 18);
                                v0 = sll(s2, 3);
                                v0 = addu(v0, s2);
                                v0 = sll(v0, 2);
                                s0 = addu(s4, v0);
                                a0 = dsll32(s5, 16);
                                a0 = dsra32(a0, 16);
                                a1 = s3;
                                jal(ctx, 0x13D0D4u, gen::fn_sub_16F9F0_0016f9f0);
                                sh(v0, s0, 128);
                                a0 = dsll32(s5, 16);
                                a0 = dsra32(a0, 16);
                                a1 = s3;
                                jal(ctx, 0x13D0ECu, gen::fn_sub_16FAE0_0016fae0);
                                sh(v0, s0, 130);
                            } else {
                                // 0x0013d0b0
                                charge(ctx, 2);
                            }
                        }
                    }
                }
                // 0x0013d138
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x0013d13c
            charge(ctx, 1);
            s3 = addiu(s3, 1);
        }
        // 0x0013d14c
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0013d15c
    charge(ctx, 14);
    sw(s2, s4, 11620);
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
    sp = addiu(sp, 0xA0);
}

// 0x00141590 sub_141590 -- 200 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// (item work): after a stock change: rebuilds the list (sub_13CC90) and clamps the scroll (+11628) and cursor (+11624)
// to the new count (5 rows a page).
void sub_141590(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00141590
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(s1, a0, 11628);
    lw(s0, a0, 11624);
    v1 = addu(s1, s0);
    v0 = sll(v1, 3);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(v0, s2);
    a0 = 1;
    lw(a1, v0, 104);
    a2 = 0;
    jal(ctx, 0x1415D0u, gen::fn_sub_16FEA0_0016fea0);
    a0 = s2;
    jal(ctx, 0x1415DCu, gen::fn_sub_13CC90_0013cc90);
    lw(v1, s2, 11620);
    at = slti(v1, 5);
    if (at == 0) {
        // 0x00141624
        charge(ctx, 4);
        v1 = addiu(v1, -5);
        at = slt(v1, s1);
        if (at != 0) {
            // 0x00141634
            charge(ctx, 2);
            sw(v1, s2, 11628);
            sw(s0, s2, 11624);
        }
    } else {
        // 0x001415f4
        charge(ctx, 6);
        sw(zero, s2, 11628);
        lw(v1, s2, 11620);
        v1 = addiu(v1, -1);
        at = slt(v1, s0);
        if (at == 0) {
            // 0x00141618
            charge(ctx, 3);
            sw(s0, s2, 11624);
        } else {
            // 0x0014160c
            charge(ctx, 3);
            sw(v1, s2, 11624);
        }
    }
    // 0x0014163c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00145350 sub_145350 -- 452 bytes; frame 0x70: ra sp+0x40, s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq)
// (item work, row): restarts the highlight tweens of the cursor row and of row `row` (12 visible rows, y 61 + 29 i).
void sub_145350(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x00145350
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    s2 = a0;
    s1 = a1;
    s0 = 0;
    for (;;) {
        // 0x001454ec
        charge(ctx, 3);
        v1 = slti(s0, 12);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00145378
        charge(ctx, 4);
        lw(v1, s2, 80);
        at = slt(s0, v1);
        if (at != 0) {
            // 0x00145388
            charge(ctx, 3);
            lw(v1, s2, 88);
            if (s0 != v1) {
                // 0x00145440
                charge(ctx, 2);
                if (s0 == s1) {
                    // 0x00145448
                    charge(ctx, 40);
                    sw(zero, sp, 0x60);
                    v0 = sll(s0, 3);
                    v0 = subu(v0, s0);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, s0);
                    mtc1(v0, f0);
                    cvt_s_w(f1, f0);
                    v0 = 0x42740000;
                    mtc1(v0, f0);
                    add_s(f0, f0, f1);
                    swc1(f0, sp, 0x64);
                    lw(a0, s2, 188);
                    v0 = sll(s0, 4);
                    v0 = addu(v0, s0);
                    v0 = sll(v0, 2);
                    v0 = addu(a0, v0);
                    lwc1(f1, v0, 736);
                    lwc1(f0, v0, 740);
                    swc1(f1, sp, 0x58);
                    swc1(f0, sp, 0x5C);
                    sd(zero, sp, 0x0);
                    a2 = 2;
                    sd(a2, sp, 0x8);
                    v1 = addiu(s0, 10);
                    v0 = sll(v1, 4);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 2);
                    a0 = addu(a0, v0);
                    v0 = 0x42CE0000;
                    mtc1(v0, f12);
                    a1 = 0;
                    a3 = 0;
                    ld(t0, sp, 0x58);
                    ld(t1, sp, 0x60);
                    t2 = 0;
                    t3 = 0;
                    jal(ctx, 0x1454E0u, gen::fn_sub_18BC10_0018bc10);
                }
            } else {
                // 0x00145394
                charge(ctx, 43);
                v0 = 0x41A80000;
                sw(v0, sp, 0x60);
                v0 = sll(s0, 3);
                v0 = subu(v0, s0);
                v0 = sll(v0, 2);
                v0 = addu(v0, s0);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x42740000;
                mtc1(v0, f0);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x64);
                lw(a0, s2, 188);
                v0 = sll(s0, 4);
                v0 = addu(v0, s0);
                v0 = sll(v0, 2);
                v0 = addu(a0, v0);
                lwc1(f1, v0, 736);
                lwc1(f0, v0, 740);
                swc1(f1, sp, 0x68);
                swc1(f0, sp, 0x6C);
                sd(zero, sp, 0x0);
                a2 = 2;
                sd(a2, sp, 0x8);
                v1 = addiu(s0, 10);
                v0 = sll(v1, 4);
                v0 = addu(v0, v1);
                v0 = sll(v0, 2);
                a0 = addu(a0, v0);
                v0 = 0x42CE0000;
                mtc1(v0, f12);
                a1 = 0;
                a3 = 0;
                ld(t0, sp, 0x68);
                ld(t1, sp, 0x60);
                t2 = 0;
                t3 = 0;
                jal(ctx, 0x145430u, gen::fn_sub_18BC10_0018bc10);
            }
        }
        // 0x001454e8
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x001454f8
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x70);
}

// 0x0014ED20 sub_14ED20 -- 352 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Destroy of "H_CampNewItem": the three sprite files +176.. (and 0x833A50), the pak +8, six blocks, the work.
void sub_14ED20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0014ed20
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, task::kWork);
    s0 = 0;
    for (;;) {
        // 0x0014ed80
        charge(ctx, 3);
        v0 = slti(s0, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0014ed48
        charge(ctx, 6);
        s3 = sll(s0, 2);
        v0 = addu(s1, s3);
        s2 = addiu(v0, 176);
        lw(a0, v0, 176);
        if (a0 != 0) {
            // 0x0014ed60
            charge(ctx, 7);
            jal(ctx, 0x14ED60u, gen::fn_sub_1124B0_001124b0);  // release a sprite file
            sw(zero, s2, 0);
            v0 = 0x830000;
            v0 = addiu(v0, 14928);  // &0x833A50
            v0 = addu(v0, s3);
            sw(zero, v0, 0);
        }
        // 0x0014ed7c
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x0014ed8c
    charge(ctx, 3);
    lw(a0, s1, 8);
    if (a0 != 0) {
        // 0x0014ed98
        charge(ctx, 3);
        jal(ctx, 0x14ED98u, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, s1, 8);
    }
    // 0x0014eda4
    charge(ctx, 3);
    lw(a0, s1, 164);
    if (a0 != 0) {
        // 0x0014edb0
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x14EDB8u, v0.u());
    }
    // 0x0014edc0
    charge(ctx, 3);
    lw(a0, s1, 168);
    if (a0 != 0) {
        // 0x0014edcc
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x14EDD4u, v0.u());
    }
    // 0x0014eddc
    charge(ctx, 3);
    lw(a0, s1, 172);
    if (a0 != 0) {
        // 0x0014ede8
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x14EDF0u, v0.u());
    }
    // 0x0014edf8
    charge(ctx, 3);
    lw(a0, s1, 188);
    if (a0 != 0) {
        // 0x0014ee04
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x14EE0Cu, v0.u());
    }
    // 0x0014ee14
    charge(ctx, 3);
    lw(a0, s1, 192);
    if (a0 != 0) {
        // 0x0014ee20
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x14EE28u, v0.u());
    }
    // 0x0014ee30
    charge(ctx, 3);
    lw(a0, s1, 196);
    if (a0 != 0) {
        // 0x0014ee3c
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x14EE44u, v0.u());
    }
    // 0x0014ee4c
    charge(ctx, 13);
    a0 = s1;
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x14EE58u, v0.u());
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0014EE80 sub_14EE80 -- 212 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_CreateNewItemTask] (parent, priority): creates the item screen "H_CampNewItem" (200-byte work, update
// sub_14C5C0), requests camp/camp_item.pak (+8), state 2.
void sub_14EE80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0014ee80
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 1;
    a1 = 200;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x14EEB0u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x0014eed0
        charge(ctx, 14);
        a0 = s2;
        a1 = 0x5E0000;
        a1 = addiu(a1, -17328);  // "H_CampNewItem"
        a2 = s1;
        a3 = 0x150000;
        a3 = addiu(a3, -14912);  // &sub_14C5C0
        t0 = 0x150000;
        t0 = addiu(t0, -4832);  // &sub_14ED20
        t1 = s0;
        jal(ctx, 0x14EEF4u, gen::fn_kwlnTaskCreate_00194b20);
        s1 = v0;
        if (s1 != 0) {
            // 0x0014ef14
            charge(ctx, 9);
            a0 = 0x5E0000;
            a0 = addiu(a0, -17312);  // "camp/camp_item.pak"
            a1 = 1;
            jal(ctx, 0x14EF20u, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s0, 8);
            v0 = 2;
            sw(v0, s0, 0);
            v0 = s1;
        } else {
            // 0x0014ef08
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0014eec4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0014ef38 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0014EF60 sub_14EF60 -- 956 bytes; frame 0x60: ra sp+0x20, s0 sp+0x10 (sq)
// (system work): the system menu's slide-in tweens (eight panels, mode 2 / kind 1; the cursor at y 124 + 33 row).
void sub_14EF60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x0014ef60
    enter(ctx, 239);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    s0 = a0;
    v0 = 0x423C0000;
    sw(v0, sp, 0x58);
    v0 = lui(0xC160);
    sw(v0, sp, 0x5C);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;
    mtc1(v0, f12);
    lw(a0, a0, 12);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x58);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14EFB4u, gen::fn_sub_18BC10_0018bc10);
    v0 = 590;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x58);
    lw(v1, s0, 4);
    v0 = sll(v1, 5);
    v0 = addu(v0, v1);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    v0 = 0x42F80000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    swc1(f0, sp, 0x5C);
    ld(v0, sp, 0x58);
    sd(v0, sp, 0x50);
    lwc1(f1, sp, 0x54);
    v0 = 0x43960000;
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x54);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s0, 12);
    v0 = 0x42C80000;
    mtc1(v0, f12);
    a0 = addiu(v1, 136);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x50);
    ld(t1, sp, 0x58);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14F054u, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x43C50000;
    sw(v0, sp, 0x58);
    v0 = 0x42FA0000;
    sw(v0, sp, 0x5C);
    ld(v0, sp, 0x58);
    sd(v0, sp, 0x30);
    lwc1(f1, sp, 0x34);
    v0 = 0x44160000;
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x34);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s0, 12);
    v0 = 0x42C80000;
    mtc1(v0, f12);
    a0 = addiu(v1, 68);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x30);
    ld(t1, sp, 0x58);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14F0C4u, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x43C90000;
    sw(v0, sp, 0x58);
    v0 = 0x42FC0000;
    sw(v0, sp, 0x5C);
    ld(v0, sp, 0x58);
    sd(v0, sp, 0x38);
    lwc1(f1, sp, 0x38);
    v0 = 0x43960000;
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x38);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s0, 12);
    v0 = 0x42C80000;
    mtc1(v0, f12);
    a0 = addiu(v1, 204);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x38);
    ld(t1, sp, 0x58);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14F134u, gen::fn_sub_18BC10_0018bc10);
    v0 = 321;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x58);
    v0 = 0x41700000;
    sw(v0, sp, 0x5C);
    ld(v0, sp, 0x58);
    sd(v0, sp, 0x40);
    lwc1(f1, sp, 0x44);
    v0 = 0x43960000;
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x44);
    lw(v0, s0, 12);
    sw(zero, v0, 336);
    v0 = 4;
    sd(v0, sp, 0x0);
    v0 = 7;
    sd(v0, sp, 0x8);
    lw(v1, s0, 12);
    v0 = 0x42C80000;
    mtc1(v0, f12);
    a0 = addiu(v1, 272);
    a1 = 0;
    a2 = 2;
    a3 = 0;
    ld(t0, sp, 0x40);
    ld(t1, sp, 0x58);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14F1BCu, gen::fn_sub_18BC10_0018bc10);
    v0 = 355;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x58);
    v0 = 0x42F80000;
    sw(v0, sp, 0x5C);
    ld(v0, sp, 0x58);
    sd(v0, sp, 0x48);
    lwc1(f1, sp, 0x4C);
    v0 = 0x43960000;
    mtc1(v0, f0);
    sub_s(f0, f1, f0);
    swc1(f0, sp, 0x4C);
    lw(v0, s0, 12);
    sw(zero, v0, 404);
    sd(zero, sp, 0x0);
    v0 = 7;
    sd(v0, sp, 0x8);
    lw(v1, s0, 12);
    v0 = 0x42C80000;
    mtc1(v0, f12);
    a0 = addiu(v1, 340);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x48);
    ld(t1, sp, 0x58);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14F240u, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x423C0000;
    sw(v0, sp, 0x58);
    v0 = 385;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x5C);
    lw(v0, s0, 12);
    sw(zero, v0, 404);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s0, 12);
    v0 = 0x42C80000;
    mtc1(v0, f12);
    a0 = addiu(v1, 408);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x58);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14F2A4u, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x43C40000;
    sw(v0, sp, 0x58);
    v0 = 385;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x5C);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s0, 12);
    v0 = 0x42C80000;
    mtc1(v0, f12);
    a0 = addiu(v1, 476);
    a1 = 0;
    a2 = 2;
    a3 = 1;
    ld(t0, sp, 0x58);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14F300u, gen::fn_sub_18BC10_0018bc10);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x60);
}

// 0x0014F320 sub_14F320 -- 856 bytes; frame 0x50: ra sp+0x20, s0 sp+0x10 (sq)
// (system work): the system menu's slide-out tweens on the same records.
void sub_14F320(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x0014f320
    enter(ctx, 214);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    s0 = a0;
    lw(a0, a0, 12);
    lwc1(f1, a0, 48);
    lwc1(f0, a0, 52);
    swc1(f1, sp, 0x48);
    swc1(f0, sp, 0x4C);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    v0 = 0x42C80000;
    mtc1(v0, f12);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x48);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14F374u, gen::fn_sub_18BC10_0018bc10);
    v0 = 590;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x48);
    lw(v1, s0, 4);
    v0 = sll(v1, 5);
    v0 = addu(v0, v1);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    v0 = 0x42F80000;
    mtc1(v0, f0);
    add_s(f0, f0, f1);
    swc1(f0, sp, 0x4C);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s0, 12);
    v0 = 0x42C80000;
    mtc1(v0, f12);
    a0 = addiu(v1, 136);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x48);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14F3F4u, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x43C50000;
    sw(v0, sp, 0x48);
    v0 = 0x42FA0000;
    sw(v0, sp, 0x4C);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s0, 12);
    v0 = 0x42C80000;
    mtc1(v0, f12);
    a0 = addiu(v1, 68);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x48);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14F444u, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x43C90000;
    sw(v0, sp, 0x48);
    v0 = 0x42FC0000;
    sw(v0, sp, 0x4C);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s0, 12);
    v0 = 0x42C80000;
    mtc1(v0, f12);
    a0 = addiu(v1, 204);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x48);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14F494u, gen::fn_sub_18BC10_0018bc10);
    v0 = 321;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x48);
    v0 = 0x41700000;
    mtc1(v0, f1);
    sw(v0, sp, 0x4C);
    ld(t0, sp, 0x48);
    sd(t0, sp, 0x40);
    v0 = 0x44160000;
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x4C);
    lw(v0, s0, 12);
    sw(zero, v0, 336);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s0, 12);
    v0 = 0x42C80000;
    mtc1(v0, f12);
    a0 = addiu(v1, 272);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x48);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14F514u, gen::fn_sub_18BC10_0018bc10);
    v0 = 355;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x48);
    v0 = 0x42F80000;
    mtc1(v0, f1);
    sw(v0, sp, 0x4C);
    ld(t0, sp, 0x48);
    sd(t0, sp, 0x38);
    v0 = 0x44160000;
    mtc1(v0, f0);
    add_s(f0, f1, f0);
    swc1(f0, sp, 0x4C);
    lw(v0, s0, 12);
    sw(zero, v0, 404);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s0, 12);
    v0 = 0x42C80000;
    mtc1(v0, f12);
    a0 = addiu(v1, 340);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t1, sp, 0x48);
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14F594u, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x423C0000;
    sw(v0, sp, 0x48);
    v0 = 385;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x4C);
    lw(v0, s0, 12);
    sw(zero, v0, 404);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s0, 12);
    v0 = 0x42C80000;
    mtc1(v0, f12);
    a0 = addiu(v1, 408);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x48);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14F5F8u, gen::fn_sub_18BC10_0018bc10);
    v0 = 0x43C40000;
    sw(v0, sp, 0x48);
    v0 = 385;
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    swc1(f0, sp, 0x4C);
    lw(v0, s0, 12);
    sw(zero, v0, 404);
    sd(zero, sp, 0x0);
    v0 = 10;
    sd(v0, sp, 0x8);
    lw(v1, s0, 12);
    v0 = 0x42C80000;
    mtc1(v0, f12);
    a0 = addiu(v1, 476);
    a1 = 0;
    a2 = 2;
    a3 = a2;
    ld(t0, sp, 0x48);
    t1 = t0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x14F65Cu, gen::fn_sub_18BC10_0018bc10);
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x50);
}

// 0x0014F680 sub_14F680 -- 336 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// (kind, id): whether an entry is unlocked: the table at gp-19768 (12-byte rows, 0-terminated: kind, id, flag) with
// datGetFlag, kind 3 / +8 == 19 always; then the 256 day-event records (sub_17AE30). 1 / 0.
void sub_14F680(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0014f680
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    lw(a1, gp, g::kUnlockTable);  // 0x7CDFB8
    s1 = 0;
    for (;;) {
        // 0x0014f74c
        charge(ctx, 3);
        v0 = slti(s1, 9999);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0014f6b0
        charge(ctx, 7);
        v0 = sll(s1, 1);
        v0 = addu(v0, s1);
        s0 = sll(v0, 2);
        v1 = addu(a1, s0);
        lh(v0, v1, 0);
        if (v0 == 0) {
            break;
        }
        // 0x0014f6cc
        charge(ctx, 2);
        if (s3 == v0) {
            // 0x0014f6d4
            charge(ctx, 3);
            lh(v0, v1, 2);
            if (s2 != v0) {
                goto L_0014f748;
            }
            // 0x0014f6e0
            charge(ctx, 3);
            lw(a0, v1, 4);
            if (a0 == 0) {
                goto L_0014f6ec_5;
            }
            // 0x0014f6f8
            charge(ctx, 4);
            jal(ctx, 0x14F6F8u, gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                goto L_0014f708_7;
            }
            // 0x0014f714
            charge(ctx, 6);
            lw(a1, gp, g::kUnlockTable);  // 0x7CDFB8
            a0 = addu(a1, s0);
            lh(v1, a0, 0);
            v0 = 3;
            if (v1 != v0) {
                goto L_0014f748;
            }
            // 0x0014f72c
            charge(ctx, 4);
            lh(v1, a0, 8);
            v0 = 19;
            if (v1 != v0) {
                goto L_0014f748;
            }
            goto L_0014f73c_10;
        }
    L_0014f748:
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x0014f758
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x0014f7a0
        charge(ctx, 3);
        v0 = slti(s0, 256);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0014f764
        charge(ctx, 6);
        a0 = s0;
        jal(ctx, 0x14F768u, gen::fn_sub_17AE30_0017ae30);
        lbu(v1, v0, 0);
        if (v1 == 0) {
            break;
        }
        // 0x0014f77c
        charge(ctx, 2);
        if (v1 == s3) {
            // 0x0014f784
            charge(ctx, 3);
            lbu(v0, v0, 1);
            if (v0 != s2) {
                goto L_0014f79c;
            }
            goto L_0014f790_17;
        }
    L_0014f79c:
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x0014f7ac
    charge(ctx, 1);
    v0 = 0;
    // 0x0014f7b0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_0014f6ec_5:
    charge(ctx, 3);
    v0 = 1;
    // 0x0014f7b0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_0014f708_7:
    charge(ctx, 3);
    v0 = 1;
    // 0x0014f7b0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_0014f73c_10:
    charge(ctx, 3);
    v0 = 1;
    // 0x0014f7b0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_0014f790_17:
    charge(ctx, 3);
    v0 = 1;
    // 0x0014f7b0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00154770 sub_154770 -- 292 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Destroy of "H_CampSystemMenuDraw" / "H_ConfigMenuDraw": texture +32, sprite files +20 / +24, blocks +12 / +16,
// messages 8 and 12, the three files +36.., the work.
void sub_154770(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00154770
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a0, s0, 32);
    if (a0 != 0) {
        // 0x00154794
        charge(ctx, 2);
        jal(ctx, 0x154794u, gen::fn_sub_4D0F00_004d0f00);  // textureDestroy
    }
    // 0x0015479c
    charge(ctx, 3);
    lw(a0, s0, 20);
    if (a0 != 0) {
        // 0x001547a8
        charge(ctx, 2);
        jal(ctx, 0x1547A8u, gen::fn_sub_1124B0_001124b0);  // release a sprite file
    }
    // 0x001547b0
    charge(ctx, 4);
    sw(zero, s0, 20);
    lw(a0, s0, 24);
    if (a0 != 0) {
        // 0x001547c0
        charge(ctx, 2);
        jal(ctx, 0x1547C0u, gen::fn_sub_1124B0_001124b0);  // release a sprite file
    }
    // 0x001547c8
    charge(ctx, 4);
    sw(zero, s0, 24);
    lw(a0, s0, 12);
    if (a0 != 0) {
        // 0x001547d8
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x1547E0u, v0.u());
    }
    // 0x001547e8
    charge(ctx, 4);
    sw(zero, s0, 12);
    lw(a0, s0, 16);
    if (a0 != 0) {
        // 0x001547f8
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x154800u, v0.u());
    }
    // 0x00154808
    charge(ctx, 10);
    sw(zero, s0, 16);
    a0 = 8;
    jal(ctx, 0x154810u, gen::fn_sub_3C7DD0_003c7dd0);
    a0 = 12;
    jal(ctx, 0x15481Cu, gen::fn_sub_3C7DD0_003c7dd0);
    s2 = 0;
    for (;;) {
        // 0x00154858
        charge(ctx, 3);
        v0 = slti(s2, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00154830
        charge(ctx, 6);
        v0 = sll(s2, 2);
        v0 = addu(s0, v0);
        s1 = addiu(v0, 36);
        lw(a0, v0, 36);
        if (a0 != 0) {
            // 0x00154848
            charge(ctx, 2);
            jal(ctx, 0x154848u, gen::fn_H_Cdvd_Destroy_00100ec0);
        }
        // 0x00154850
        charge(ctx, 2);
        sw(zero, s1, 0);
        s2 = addiu(s2, 1);
    }
    // 0x00154864
    charge(ctx, 12);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x154870u, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001548A0 sub_1548A0 -- 204 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_CreateSystemMenuDrawTask] (parent, priority): creates "H_CampSystemMenuDraw" (380-byte work, update
// sub_14F7D0); The Answer starts on entry 4.
void sub_1548A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001548a0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 1;
    a1 = 380;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x1548D0u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001548f0
        charge(ctx, 14);
        a0 = s2;
        a1 = 0x5E0000;
        a1 = addiu(a1, -17152);  // "H_CampSystemMenuDraw"
        a2 = s1;
        a3 = 0x150000;
        a3 = addiu(a3, -2096);  // &sub_14F7D0
        t0 = 0x150000;
        t0 = addiu(t0, 18288);  // &sub_154770
        t1 = s0;
        jal(ctx, 0x154914u, gen::fn_kwlnTaskCreate_00194b20);
        s1 = v0;
        if (s1 != 0) {
            // 0x00154934
            charge(ctx, 4);
            jal(ctx, 0x154934u, gen::fn_sub_17D800_0017d800);  // datGetScenarioMode (1 = The Answer)
            if (v0 != 0) {
                // 0x00154944
                charge(ctx, 2);
                v0 = 4;
                sw(v0, s0, 4);
            }
            // 0x0015494c
            charge(ctx, 1);
            v0 = s1;
        } else {
            // 0x00154928
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x001548e4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00154950 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0015C460 sub_15C460 -- 188 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_CreateConfigMenuDrawTask] (parent): creates "H_ConfigMenuDraw" (the title screen's config, update
// sub_15B430) and its own camp sprite set-up (sub_119F10(task, 1)).
void sub_15C460(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0015c460
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 1;
    a1 = 380;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x15C488u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x0015c4a8
        charge(ctx, 14);
        a0 = s1;
        a1 = 0x5E0000;
        a1 = addiu(a1, -17120);  // "H_ConfigMenuDraw"
        a2 = 6334;
        a3 = 0x160000;
        a3 = addiu(a3, -19408);  // &sub_15B430
        t0 = 0x150000;
        t0 = addiu(t0, 18288);  // &sub_154770
        t1 = s0;
        jal(ctx, 0x15C4CCu, gen::fn_kwlnTaskCreate_00194b20);
        s1 = v0;
        if (s1 != 0) {
            // 0x0015c4ec
            charge(ctx, 6);
            a0 = s1;
            a1 = 1;
            jal(ctx, 0x15C4F4u, gen::fn_sub_119F10_00119f10);
            sw(v0, s0, 8);
            v0 = s1;
        } else {
            // 0x0015c4e0
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0015c49c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0015c504 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0015C520 sub_15C520 -- 788 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_SkillUseOnTarget] (skill work, target): casts the selected healing skill from the camp (protagonist 0, the
// n-th member, everyone -2): sub_17B860 per member, then the caster pays the cost (HP / SP through sub_16CF40 /
// sub_16CF90).
void sub_15C520(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0015c520
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    lw(v1, a0, 2016);
    lw(v0, a0, 2020);
    s1 = addu(v1, v0);
    v0 = sll(s1, 2);
    v0 = addu(v0, s1);
    v0 = sll(v0, 2);
    v1 = addu(v0, s5);
    lw(s0, v1, 12);
    v0 = 0x830000;
    lh(s6, v0, 27560);  // 0x836BA8
    lh(a0, v1, 20);
    jal(ctx, 0x15C578u, gen::fn_sub_175200_00175200);
    a1 = s0 & 0xFFFF;
    a0 = 1;
    jal(ctx, 0x15C588u, gen::fn_sub_17B660_0017b660);
    if (v0 == 0) {
        // 0x0015c598
        charge(ctx, 3);
        v0 = si(-2);
        if (s4 != v0) {
            // 0x0015c670
            charge(ctx, 2);
            if (s4 != 0) {
                // 0x0015c6cc
                charge(ctx, 4);
                s3 = 0;
                s2 = 0;
                for (;;) {
                    // 0x0015c784
                    charge(ctx, 3);
                    v0 = slti(s2, 3);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x0015c6dc
                    charge(ctx, 7);
                    a0 = s2;
                    jal(ctx, 0x15C6E0u, gen::fn_sub_16DD60_0016dd60);
                    v0 = dsll32(v0, 16);
                    v0 = dsra32(v0, 16);
                    if (v0 != 0) {
                        // 0x0015c6f8
                        charge(ctx, 3);
                        s3 = addiu(s3, 1);
                        if (s4 != s3) {
                            goto L_0015c780;
                        }
                        goto L_0015c704_17;
                    }
                L_0015c780:
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
            } else {
                // 0x0015c678
                charge(ctx, 5);
                a0 = 1;
                jal(ctx, 0x15C67Cu, gen::fn_sub_1C7CE0_001c7ce0);
                if (v0 != 0) {
                    // 0x0015c68c
                    charge(ctx, 8);
                    a2 = s0 & 0xFFFF;
                    a0 = 1;
                    a1 = a0;
                    a3 = 0;
                    jal(ctx, 0x15C69Cu, gen::fn_sub_17BC20_0017bc20);
                    if (v0 == 0) {
                        // 0x0015c6ac
                        charge(ctx, 8);
                        a2 = s0 & 0xFFFF;
                        a0 = 1;
                        a1 = a0;
                        a3 = 0;
                        jal(ctx, 0x15C6BCu, gen::fn_sub_17B860_0017b860);
                    }
                }
            }
        } else {
            // 0x0015c5a4
            charge(ctx, 9);
            a2 = s0 & 0xFFFF;
            a0 = 1;
            a1 = a0;
            a3 = 0;
            jal(ctx, 0x15C5B4u, gen::fn_sub_17B860_0017b860);
            s2 = 0;
            for (;;) {
                // 0x0015c65c
                charge(ctx, 3);
                v0 = slti(s2, 3);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x0015c5c8
                charge(ctx, 7);
                a0 = s2;
                jal(ctx, 0x15C5CCu, gen::fn_sub_16DD60_0016dd60);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                if (v0 != 0) {
                    // 0x0015c5e4
                    charge(ctx, 9);
                    a0 = s2;
                    jal(ctx, 0x15C5E8u, gen::fn_sub_16DD60_0016dd60);
                    a0 = dsll32(v0, 16);
                    a0 = dsra32(a0, 16);
                    jal(ctx, 0x15C5F8u, gen::fn_sub_1C7CE0_001c7ce0);
                    if (v0 != 0) {
                        // 0x0015c608
                        charge(ctx, 11);
                        a0 = s2;
                        jal(ctx, 0x15C60Cu, gen::fn_sub_16DD60_0016dd60);
                        a2 = s0 & 0xFFFF;
                        a0 = 1;
                        a1 = v0;
                        a3 = 0;
                        jal(ctx, 0x15C624u, gen::fn_sub_17BC20_0017bc20);
                        if (v0 == 0) {
                            // 0x0015c634
                            charge(ctx, 9);
                            a0 = s2;
                            jal(ctx, 0x15C638u, gen::fn_sub_16DD60_0016dd60);
                            a2 = s0 & 0xFFFF;
                            a0 = 1;
                            a1 = v0;
                            a3 = 0;
                            jal(ctx, 0x15C650u, gen::fn_sub_17B860_0017b860);
                        }
                    }
                }
                // 0x0015c658
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x0015c668
            charge(ctx, 2);
        }
    L_0015c790:
        charge(ctx, 27);
        v0 = sll(s1, 2);
        v0 = addu(v0, s1);
        s0 = sll(v0, 2);
        a0 = 1;
        jal(ctx, 0x15C7A0u, gen::fn_sub_16C4F0_0016c4f0);
        v1 = v0 & 0xFFFF;
        v0 = addu(s0, s5);
        lw(v0, v0, 28);
        v0 = subu(v1, v0);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        a0 = 1;
        jal(ctx, 0x15C7C4u, gen::fn_sub_16CF40_0016cf40);
        a0 = 1;
        jal(ctx, 0x15C7D0u, gen::fn_sub_16C570_0016c570);
        v1 = v0 & 0xFFFF;
        v0 = addu(s0, s5);
        lw(v0, v0, 24);
        v0 = subu(v1, v0);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        a0 = 1;
        jal(ctx, 0x15C7F4u, gen::fn_sub_16CF90_0016cf90);
    }
    // 0x0015c7fc
    charge(ctx, 14);
    a0 = s6;
    jal(ctx, 0x15C800u, gen::fn_sub_175200_00175200);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_0015c704_17:
    charge(ctx, 9);
    a0 = s2;
    jal(ctx, 0x15C708u, gen::fn_sub_16DD60_0016dd60);
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x15C718u, gen::fn_sub_1C7CE0_001c7ce0);
    if (v0 != 0) {
        // 0x0015c728
        charge(ctx, 11);
        a0 = s2;
        jal(ctx, 0x15C72Cu, gen::fn_sub_16DD60_0016dd60);
        a2 = s0 & 0xFFFF;
        a0 = 1;
        a1 = v0;
        a3 = 0;
        jal(ctx, 0x15C744u, gen::fn_sub_17BC20_0017bc20);
        if (v0 == 0) {
            // 0x0015c754
            charge(ctx, 11);
            a0 = s2;
            jal(ctx, 0x15C758u, gen::fn_sub_16DD60_0016dd60);
            a2 = s0 & 0xFFFF;
            a0 = 1;
            a1 = v0;
            a3 = 0;
            jal(ctx, 0x15C770u, gen::fn_sub_17B860_0017b860);
        }
    }
    goto L_0015c790;
}

// 0x0015D8E0 sub_15D8E0 -- 392 bytes; frame 0x50: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// (xy, alpha, z): the skill screen's scrolling ribbon: sprite 12 of 0x833A50, x gp-19812 moving by -1, wrapping at
// -640.
void sub_15D8E0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x0015d8e0
    enter(ctx, 44);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    sd(a0, sp, 0x48);
    mov_s(f22, f12);
    s0 = a1;
    lwc1(f20, sp, 0x4C);
    a0 = 0;
    v0 = 0x830000;
    lw(a1, v0, 14928);  // 0x833A50
    a2 = 12;
    jal(ctx, 0x15D91Cu, gen::fn_sprCreateHandle_001158b0);
    s1 = v0;
    swc1(f22, v0, 44);
    v1 = 0x435A0000;
    mtc1(v1, f1);
    lwc1(f0, sp, 0x48);
    add_s(f21, f1, f0);
    lwc1(f0, gp, g::kSkillRibbonX);  // 0x7CDF8C
    cvt_s_w(f0, f0);
    add_s(f0, f21, f0);
    swc1(f0, v0, 16);
    v1 = 0x43BF0000;
    mtc1(v1, f0);
    add_s(f20, f0, f20);
    swc1(f20, v0, 20);
    sb(s0, v0, 24);
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x15D96Cu, gen::fn_sub_1127D0_001127d0);  // sprDrawSprite
    a0 = s1;
    jal(ctx, 0x15D978u, gen::fn_sub_115980_00115980);  // release the sprite handle
    lw(v1, gp, g::kSkillRibbonX);  // 0x7CDF8C
    at = slti(v1, -200);
    if (at != 0) {
        // 0x0015d990
        charge(ctx, 25);
        a0 = 0;
        v0 = 0x830000;
        lw(a1, v0, 14928);  // 0x833A50
        a2 = 12;
        jal(ctx, 0x15D9A0u, gen::fn_sprCreateHandle_001158b0);
        s1 = v0;
        swc1(f22, v0, 44);
        lwc1(f0, gp, g::kSkillRibbonX);  // 0x7CDF8C
        cvt_s_w(f0, f0);
        add_s(f1, f21, f0);
        v1 = 0x44200000;
        mtc1(v1, f0);
        add_s(f0, f0, f1);
        swc1(f0, v0, 16);
        swc1(f20, v0, 20);
        sb(s0, v0, 24);
        a0 = s1;
        a1 = 1;
        jal(ctx, 0x15D9E0u, gen::fn_sub_1127D0_001127d0);  // sprDrawSprite
        a0 = s1;
        jal(ctx, 0x15D9ECu, gen::fn_sub_115980_00115980);  // release the sprite handle
    }
    // 0x0015d9f4
    charge(ctx, 12);
    lw(v1, gp, g::kSkillRibbonX);  // 0x7CDF8C
    v1 = addiu(v1, -1);
    sw(v1, gp, g::kSkillRibbonX);  // 0x7CDF8C
    mtc1(v1, f0);
    cvt_s_w(f1, f0);
    v1 = lui(0xC420);
    mtc1(v1, f0);
    c_lt_s(f1, f0);
    if (cond(ctx)) {
        // 0x0015da24
        charge(ctx, 8);
        v1 = 0x44200000;
        mtc1(v1, f0);
        add_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        sw(v1, gp, g::kSkillRibbonX);  // 0x7CDF8C
    }
    // 0x0015da44 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001616D0 sub_1616D0 -- 244 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Destroy of "H_NewCampSkillDraw": blocks +56 / +40, the three sprite files +28.. (and 0x833A50), the pak +48, the
// work.
void sub_1616D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001616d0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, task::kWork);
    lw(a0, s1, 56);
    if (a0 != 0) {
        // 0x001616f4
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x1616FCu, v0.u());
    }
    // 0x00161704
    charge(ctx, 4);
    sw(zero, s1, 56);
    lw(a0, s1, 40);
    if (a0 != 0) {
        // 0x00161714
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x16171Cu, v0.u());
    }
    // 0x00161724
    charge(ctx, 4);
    sw(zero, s1, 40);
    s0 = 0;
    for (;;) {
        // 0x00161770
        charge(ctx, 3);
        v0 = slti(s0, 3);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00161734
        charge(ctx, 6);
        v0 = sll(s0, 2);
        v0 = addu(s1, v0);
        s2 = addiu(v0, 28);
        lw(a0, v0, 28);
        if (a0 != 0) {
            // 0x0016174c
            charge(ctx, 2);
            jal(ctx, 0x16174Cu, gen::fn_sub_1124B0_001124b0);  // release a sprite file
        }
        // 0x00161754
        charge(ctx, 7);
        v1 = sll(s0, 2);
        sw(zero, s2, 0);
        v0 = 0x830000;
        v0 = addiu(v0, 14928);  // &0x833A50
        v0 = addu(v0, v1);
        sw(zero, v0, 0);
        s0 = addiu(s0, 1);
    }
    // 0x0016177c
    charge(ctx, 3);
    lw(a0, s1, 48);
    if (a0 != 0) {
        // 0x00161788
        charge(ctx, 2);
        jal(ctx, 0x161788u, gen::fn_H_Cdvd_Destroy_00100ec0);
    }
    // 0x00161790
    charge(ctx, 13);
    sw(zero, s1, 48);
    a0 = s1;
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x1617A0u, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001617D0 sub_1617D0 -- 204 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_CreateNewCampSkillDrawTask] (parent, priority): creates the skill screen "H_NewCampSkillDraw" (80-byte work,
// update sub_160800) and requests camp/camp_skil.pak (+48).
void sub_1617D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001617d0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    a0 = 1;
    a1 = 80;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x161800u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00161820
        charge(ctx, 14);
        a0 = s2;
        a1 = 0x5E0000;
        a1 = addiu(a1, -17088);  // "H_NewCampSkillDraw"
        a2 = s1;
        a3 = 0x160000;
        a3 = addiu(a3, 2048);  // &sub_160800
        t0 = 0x160000;
        t0 = addiu(t0, 5840);  // &sub_1616D0
        t1 = s0;
        jal(ctx, 0x161844u, gen::fn_kwlnTaskCreate_00194b20);
        s1 = v0;
        if (s1 != 0) {
            // 0x00161864
            charge(ctx, 7);
            a0 = 0x5E0000;
            a0 = addiu(a0, -17056);  // "camp/camp_skil.pak"
            a1 = 1;
            jal(ctx, 0x161870u, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s0, 48);
            v0 = s1;
        } else {
            // 0x00161858
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00161814
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00161880 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00161D60 sub_161D60 -- 44 bytes; frame 0x10: ra sp+0x0
// Destroy of "H_CampFrStatusRoot": frees the work.
void sub_161D60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00161d60
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, task::kWork);
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x161D74u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001669B0 sub_1669B0 -- 148 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Destroy of "H_CampPartyStatusDraw": texture +28, sprite files +32 / +36, the pak +24, blocks +44 / +48, the work.
void sub_1669B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001669b0
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, task::kWork);
    lw(a0, s1, 28);
    jal(ctx, 0x1669C8u, gen::fn_sub_4D0F00_004d0f00);  // textureDestroy
    lw(a0, s1, 32);
    jal(ctx, 0x1669D4u, gen::fn_sub_1124B0_001124b0);  // release a sprite file
    lw(a0, s1, 36);
    jal(ctx, 0x1669E0u, gen::fn_sub_1124B0_001124b0);  // release a sprite file
    lw(a0, s1, 24);
    jal(ctx, 0x1669ECu, gen::fn_H_Cdvd_Destroy_00100ec0);
    s0 = 0x960000;
    s0 = addiu(s0, 380);  // &0x96017C
    lw(a0, s1, 44);
    lw(v0, s0, 0);  // 0x96017C
    jalr(ctx, 0x166A04u, v0.u());
    lw(a0, s1, 48);
    lw(v0, s0, 0);  // 0x96017C
    jalr(ctx, 0x166A14u, v0.u());
    a0 = s1;
    lw(v0, s0, 0);  // 0x96017C
    jalr(ctx, 0x166A24u, v0.u());
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00166A50 sub_166A50 -- 432 bytes; frame 0x170: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_CreatePartyStatusDrawTask] (parent, priority, member, ?, mode): creates "H_CampPartyStatusDraw" (56-byte
// work, update sub_164920) and requests the member's camp/camp_fr%02d.pak (The Answer: AGS_camp_fr03 for members 1 /
// 3, AGS_camp_fr09 for 9).
void sub_166A50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00166a50
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x170);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s2 = a1;
    s4 = a2;
    s0 = a3;
    s3 = t0;
    a0 = 1;
    a1 = 56;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x166A98u, v0.u());
    s1 = v0;
    if (s1 != 0) {
        // 0x00166ab8
        charge(ctx, 14);
        a0 = s5;
        a1 = 0x5E0000;
        a1 = addiu(a1, -16816);  // "H_CampPartyStatusDraw"
        a2 = s2;
        a3 = 0x160000;
        a3 = addiu(a3, 18720);  // &sub_164920
        t0 = 0x160000;
        t0 = addiu(t0, 27056);  // &sub_1669B0
        t1 = s1;
        jal(ctx, 0x166ADCu, gen::fn_kwlnTaskCreate_00194b20);
        s2 = v0;
        if (s2 != 0) {
            // 0x00166afc
            charge(ctx, 8);
            sw(s0, s1, 20);
            s0 = dsll32(s4, 16);
            s0 = dsra32(s0, 16);
            sw(s0, s1, 8);
            jal(ctx, 0x166B0Cu, gen::fn_sub_17D800_0017d800);  // datGetScenarioMode (1 = The Answer)
            if (v0 == 0) {
                // 0x00166ba4
                charge(ctx, 6);
                a0 = addiu(sp, 0x70);
                a1 = 0x5E0000;
                a1 = addiu(a1, -16720);  // "camp/camp_fr%02d.pak"
                a2 = s0;
                jal(ctx, 0x166BB4u, gen::fn_sprintf_00523ac8);
            } else {
                // 0x00166b1c
                charge(ctx, 3);
                v0 = 9;
                if (s0 == v0) {
                    // 0x00166b64
                    charge(ctx, 8);
                    a0 = addiu(sp, 0x70);
                    a1 = 0x5E0000;
                    a1 = addiu(a1, -16752);  // "camp/AGS_camp_fr%02d.pak"
                    a2 = s0;
                    jal(ctx, 0x166B74u, gen::fn_sprintf_00523ac8);
                } else {
                    // 0x00166b28
                    charge(ctx, 3);
                    v0 = 3;
                    if (s0 != v0) {
                        // 0x00166b34
                        charge(ctx, 3);
                        v0 = 1;
                        if (s0 == v0) {
                            goto L_00166b48;
                        }
                        // 0x00166b40
                        charge(ctx, 2);
                        // 0x00166b84
                        charge(ctx, 8);
                        a0 = addiu(sp, 0x70);
                        a1 = 0x5E0000;
                        a1 = addiu(a1, -16720);  // "camp/camp_fr%02d.pak"
                        a2 = s0;
                        jal(ctx, 0x166B94u, gen::fn_sprintf_00523ac8);
                        goto L_00166bbc;
                    }
                L_00166b48:
                    charge(ctx, 7);
                    a0 = addiu(sp, 0x70);
                    a1 = 0x5E0000;
                    a1 = addiu(a1, -16784);  // "camp/AGS_camp_fr03.pak"
                    jal(ctx, 0x166B54u, gen::fn_sprintf_00523ac8);
                }
            }
        L_00166bbc:
            charge(ctx, 7);
            a0 = addiu(sp, 0x70);
            a1 = 1;
            jal(ctx, 0x166BC4u, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s1, 24);
            sw(s3, s1, 4);
            v0 = s2;
        } else {
            // 0x00166af0
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00166aac
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00166bd8 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x170);
}

// 0x001675B0 sub_1675B0 -- 44 bytes; frame 0x10: ra sp+0x0
// Destroy of "H_CampPartyStatusRoot": frees the work.
void sub_1675B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001675b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, task::kWork);
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x1675C4u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001675E0 sub_1675E0 -- 768 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_UpdateFrStatusDispTask] Update of "H_FRStatusDisp" (the party-status screen a script opens): state 0 sets
// flag 0x1407, the camp_status.pak set-up ("H_CampStatusSprSetupFile") and the flash draw (sub_168770); 1 waits for
// both, then creates "H_CampPartyStatusRoot" (+4 set) or "H_CampFrStatusRoot"; 2 returns -1 once that task finished.
void sub_1675E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001675e0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, task::kWork);
    lw(v1, s0, 0);
    v0 = 2;
    if (v1 != v0) {
        // 0x00167610
        charge(ctx, 3);
        a1 = 1;
        if (v1 == a1) {
            // 0x00167710
            charge(ctx, 3);
            lw(v0, gp, g::kCampSetupTask);  // 0x7CDF48
            if (v0 != 0) {
                // 0x00167728
                charge(ctx, 5);
                lw(v0, v0, 60);
                lw(v1, v0, 0);
                v0 = 3;
                if (v1 != v0) {
                    // 0x00167744
                    charge(ctx, 1);
                    a1 = 0;
                } else {
                    // 0x0016773c
                    charge(ctx, 2);
                }
            } else {
                // 0x0016771c
                charge(ctx, 3);
                a1 = si(-1);
            }
            // 0x00167748
            charge(ctx, 2);
            if (a1 != 0) {
                // 0x00167750
                charge(ctx, 5);
                lw(a0, s0, 12);
                jal(ctx, 0x167754u, gen::fn_sub_1685B0_001685b0);
                if (v0 != 0) {
                    // 0x00167764
                    charge(ctx, 3);
                    lw(v0, s0, 4);
                    if (v0 != 0) {
                        // 0x00167800
                        charge(ctx, 11);
                        lh(s2, s0, 16);
                        a0 = 1;
                        a1 = 72;
                        a2 = 0x40000;
                        v0 = 0x960000;
                        lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
                        jalr(ctx, 0x167818u, v0.u());
                        s3 = v0;
                        if (s3 != 0) {
                            // 0x00167838
                            charge(ctx, 13);
                            a0 = s1;
                            a1 = 0x5E0000;
                            a1 = addiu(a1, -16688);  // "H_CampPartyStatusRoot"
                            a2 = 6334;
                            a3 = 0x160000;
                            a3 = addiu(a3, 27760);  // &sub_166C70
                            t0 = 0x160000;
                            t0 = addiu(t0, 30128);  // &sub_1675B0
                            t1 = s3;
                            jal(ctx, 0x16785Cu, gen::fn_kwlnTaskCreate_00194b20);
                            if (v0 != 0) {
                                // 0x00167878
                                charge(ctx, 3);
                                v1 = dsll32(s2, 16);
                                v1 = dsra32(v1, 16);
                                sw(v1, s3, 12);
                            } else {
                                // 0x0016786c
                                charge(ctx, 3);
                                v0 = 0;
                            }
                        } else {
                            // 0x0016782c
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x00167884
                        charge(ctx, 1);
                        sw(v0, s0, 12);
                    } else {
                        // 0x00167770
                        charge(ctx, 11);
                        lh(s2, s0, 16);
                        a0 = 1;
                        a1 = 48;
                        a2 = 0x40000;
                        v0 = 0x960000;
                        lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
                        jalr(ctx, 0x167788u, v0.u());
                        s3 = v0;
                        if (s3 != 0) {
                            // 0x001677a8
                            charge(ctx, 13);
                            a0 = s1;
                            a1 = 0x5E0000;
                            a1 = addiu(a1, -17024);  // "H_CampFrStatusRoot"
                            a2 = 6334;
                            a3 = 0x160000;
                            a3 = addiu(a3, 6304);  // &sub_1618A0
                            t0 = 0x160000;
                            t0 = addiu(t0, 7520);  // &sub_161D60
                            t1 = s3;
                            jal(ctx, 0x1677CCu, gen::fn_kwlnTaskCreate_00194b20);
                            if (v0 != 0) {
                                // 0x001677e8
                                charge(ctx, 3);
                                v1 = dsll32(s2, 16);
                                v1 = dsra32(v1, 16);
                                sw(v1, s3, 12);
                            } else {
                                // 0x001677dc
                                charge(ctx, 3);
                                v0 = 0;
                            }
                        } else {
                            // 0x0016779c
                            charge(ctx, 3);
                            v0 = 0;
                        }
                        // 0x001677f4
                        charge(ctx, 3);
                        sw(v0, s0, 12);
                    }
                    // 0x00167888
                    charge(ctx, 4);
                    v0 = 2;
                    sw(v0, s0, 0);
                }
            }
        } else {
            // 0x0016761c
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x0016762c
                charge(ctx, 6);
                a0 = 5127;
                jal(ctx, 0x167630u, gen::fn_datSetFlag_0016f1f0);
                lw(v0, gp, g::kCampSetupTask);  // 0x7CDF48
                if (v0 == 0) {
                    // 0x00167650
                    charge(ctx, 10);
                    a0 = 1;
                    a1 = 72;
                    a2 = 0x40000;
                    v0 = 0x960000;
                    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
                    jalr(ctx, 0x167664u, v0.u());
                    s2 = v0;
                    if (s2 != 0) {
                        // 0x00167684
                        charge(ctx, 14);
                        a0 = s1;
                        a1 = 0x5E0000;
                        a1 = addiu(a1, -21392);  // "H_CampStatusSprSetupFile"
                        a2 = 6335;
                        a3 = 0x120000;
                        a3 = addiu(a3, -22368);  // &sub_11A8A0
                        t0 = 0x120000;
                        t0 = addiu(t0, -21792);  // &sub_11AAE0
                        t1 = s2;
                        jal(ctx, 0x1676A8u, gen::fn_kwlnTaskCreate_00194b20);
                        s3 = v0;
                        if (s3 != 0) {
                            // 0x001676c8
                            charge(ctx, 7);
                            sw(s3, gp, g::kCampSetupTask);  // 0x7CDF48
                            a0 = 0x5E0000;
                            a0 = addiu(a0, -21360);  // "camp/camp_status.pak"
                            a1 = 1;
                            jal(ctx, 0x1676D8u, gen::fn_H_Cdvd_Request_00100d80);
                            sw(v0, s2, 60);
                        } else {
                            // 0x001676bc
                            charge(ctx, 3);
                            s3 = 0;
                        }
                    } else {
                        // 0x00167678
                        charge(ctx, 3);
                        s3 = 0;
                    }
                } else {
                    // 0x00167644
                    charge(ctx, 3);
                    s3 = 0;
                }
                // 0x001676e4
                charge(ctx, 11);
                sw(s3, s0, 8);
                a0 = s1;
                a1 = 6335;
                jal(ctx, 0x1676F0u, gen::fn_sub_168770_00168770);
                sw(v0, s0, 12);
                sw(v0, gp, g::kFrStatusFlashTask);  // 0x7CDF88
                v0 = 1;
                sw(v0, s0, 0);
            } else {
                // 0x00167624
                charge(ctx, 2);
            }
        }
        goto L_001678bc;
    }
    // 0x00167898
    charge(ctx, 6);
    lw(a0, s0, 12);
    jal(ctx, 0x16789Cu, gen::fn_kwlnTaskGetState_00195290);
    v1 = 3;
    if (v0 != v1) {
    L_001678bc:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x001678b0
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x001678c0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001678E0 sub_1678E0 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Destroy of "H_FRStatusDisp": gp-19816 = 0, flag 0x1407 cleared, the work freed.
void sub_1678E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001678e0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    sw(zero, gp, g::kFrStatusFlashTask);  // 0x7CDF88
    a0 = 5127;
    a1 = 0;
    jal(ctx, 0x1678FCu, gen::fn_datSetFlag_0016f1f0);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x167910u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00167EC0 sub_167EC0 -- 44 bytes; frame 0x10: ra sp+0x0
// Destroy of "H_CampFrStatusPersonaDraw": frees the work.
void sub_167EC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00167ec0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, task::kWork);
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x167ED4u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00167F40 sub_167F40 -- 248 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_CreateFrStatusPersonaDrawTask] (parent, priority, xy, a, b, c): creates "H_CampFrStatusPersonaDraw" (44-byte
// work, update sub_167930).
void sub_167F40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00167f40
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    sd(a2, sp, 0x78);
    s3 = a3;
    s2 = t0;
    s1 = t1;
    a0 = 1;
    a1 = 44;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x167F8Cu, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x00167fac
        charge(ctx, 13);
        a0 = s5;
        a1 = 0x5E0000;
        a1 = addiu(a1, -16640);  // "H_CampFrStatusPersonaDraw"
        a2 = s4;
        a3 = 0x160000;
        a3 = addiu(a3, 31024);  // &sub_167930
        t0 = 0x160000;
        t0 = addiu(t0, 32448);  // &sub_167EC0
        t1 = s0;
        jal(ctx, 0x167FD0u, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x00167fec
            charge(ctx, 9);
            lwc1(f1, sp, 0x78);
            lwc1(f0, sp, 0x7C);
            swc1(f1, s0, 4);
            swc1(f0, s0, 8);
            v1 = 1;
            sw(v1, s0, 24);
            sh(s3, s0, 14);
            sh(s2, s0, 18);
            sh(s1, s0, 28);
        } else {
            // 0x00167fe0
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x00167fa0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00168010 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x00168040 sub_168040 -- 192 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM: opens the party-status screen of member scrGetIntPara(0) ("H_FRStatusDisp", mode 0) into gp-19820; returns 1.
void sub_168040(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00168040
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x168054u, gen::fn_scrGetIntPara_0035ed20);
    s0 = dsll32(v0, 16);
    s0 = dsra32(s0, 16);
    a0 = 1;
    a1 = 20;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x168078u, v0.u());
    s1 = v0;
    if (s1 != 0) {
        // 0x00168098
        charge(ctx, 13);
        a0 = 0;
        a1 = 0x5E0000;
        a1 = addiu(a1, -16664);  // "H_FRStatusDisp"
        a2 = 100;
        a3 = 0x160000;
        a3 = addiu(a3, 30176);  // &sub_1675E0
        t0 = 0x160000;
        t0 = addiu(t0, 30944);  // &sub_1678E0
        t1 = s1;
        jal(ctx, 0x1680BCu, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x001680d8
            charge(ctx, 2);
            sh(s0, s1, 16);
            sw(zero, s1, 4);
        } else {
            // 0x001680cc
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0016808c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001680e0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    sw(v0, gp, g::kFrStatusDispTask);  // 0x7CDF84
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00168100 sub_168100 -- 196 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM: the same with mode 1 (the party-status root).
void sub_168100(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00168100
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x168114u, gen::fn_scrGetIntPara_0035ed20);
    s0 = dsll32(v0, 16);
    s0 = dsra32(s0, 16);
    a0 = 1;
    a1 = 20;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x168138u, v0.u());
    s1 = v0;
    if (s1 != 0) {
        // 0x00168158
        charge(ctx, 13);
        a0 = 0;
        a1 = 0x5E0000;
        a1 = addiu(a1, -16664);  // "H_FRStatusDisp"
        a2 = 100;
        a3 = 0x160000;
        a3 = addiu(a3, 30176);  // &sub_1675E0
        t0 = 0x160000;
        t0 = addiu(t0, 30944);  // &sub_1678E0
        t1 = s1;
        jal(ctx, 0x16817Cu, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 != 0) {
            // 0x00168198
            charge(ctx, 3);
            sh(s0, s1, 16);
            v1 = 1;
            sw(v1, s1, 4);
        } else {
            // 0x0016818c
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x0016814c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001681a4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    sw(v0, gp, g::kFrStatusDispTask);  // 0x7CDF84
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00168220 sub_168220 -- 900 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10 (sq), f20 sp+0x0
// [H_Camp_UpdateFrStatusFlashTask] Update of "H_FrStatusFlashDraw" (jump table 0x7B62E0): loads camp/anm_status.pak,
// then plays the nakama01 / 07 / 09 / equ_trade01 transitions chosen by sub_1685E0 (+12), keeps the shown .anm (+20),
// counts the close (+4).
void sub_168220(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f20{ctx, 20};
    // 0x00168220
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(v0, s0, 0);
    at = sltiu(v0, 8);
    if (at != 0) {
        // 0x00168244
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 25312);  // &0x7B62E0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x168260u:  // table[0]
            // 0x00168260
            charge(ctx, 10);
            a0 = 0x5E0000;
            a0 = addiu(a0, -16608);  // "camp/anm_status.pak"
            a1 = 1;
            jal(ctx, 0x16826Cu, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s0, 16);
            v0 = 1;
            sw(v0, s0, 0);
        L_00168588:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x168288u:  // table[1]
            // 0x00168288
            charge(ctx, 5);
            lw(a0, s0, 16);
            jal(ctx, 0x16828Cu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                // 0x0016829c
                charge(ctx, 4);
                v0 = 2;
                sw(v0, s0, 0);
            }
            goto L_00168588;
        case 0x1682ACu:  // table[3]
            // 0x001682ac
            charge(ctx, 4);
            lw(v1, s0, 12);
            v0 = 3;
            if (v1 == v0) {
                // 0x00168344
                charge(ctx, 6);
                a1 = 6333;
                a2 = 0x5E0000;
                a2 = addiu(a2, -16432);  // "camp/status/anm/if_c_equ_trade01.anm"
                jal(ctx, 0x168350u, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                sw(v0, s0, 24);
            } else {
                // 0x001682bc
                charge(ctx, 3);
                v0 = 2;
                if (v1 == v0) {
                    // 0x00168324
                    charge(ctx, 8);
                    a1 = 6333;
                    a2 = 0x5E0000;
                    a2 = addiu(a2, -16480);  // "camp/status/anm/if_c_sta_nakama09.anm"
                    jal(ctx, 0x168330u, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                    sw(v0, s0, 24);
                } else {
                    // 0x001682c8
                    charge(ctx, 3);
                    v0 = 1;
                    if (v1 == v0) {
                        // 0x00168304
                        charge(ctx, 8);
                        a1 = 6333;
                        a2 = 0x5E0000;
                        a2 = addiu(a2, -16528);  // "camp/status/anm/if_c_sta_nakama07.anm"
                        jal(ctx, 0x168310u, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                        sw(v0, s0, 24);
                    } else {
                        // 0x001682d4
                        charge(ctx, 2);
                        if (v1 == 0) {
                            // 0x001682e4
                            charge(ctx, 8);
                            a1 = 6333;
                            a2 = 0x5E0000;
                            a2 = addiu(a2, -16576);  // "camp/status/anm/if_c_sta_nakama01.anm"
                            jal(ctx, 0x1682F0u, gen::fn_sub_111DD0_00111dd0);  // create an .anm task ("H_DrawMaestro")
                            sw(v0, s0, 24);
                        } else {
                            // 0x001682dc
                            charge(ctx, 2);
                        }
                    }
                }
            }
            // 0x0016835c
            charge(ctx, 5);
            sw(zero, s0, 4);
            v0 = 4;
            sw(v0, s0, 0);
            goto L_00168588;
        case 0x168370u:  // table[4]
            // 0x00168370
            charge(ctx, 6);
            lw(a0, s0, 24);
            jal(ctx, 0x168374u, gen::fn_sub_111EC0_00111ec0);  // 1 when the .anm is loaded
            v1 = 1;
            if (v0 == v1) {
                // 0x00168388
                charge(ctx, 17);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 5;
                jal(ctx, 0x168398u, gen::fn_sub_10A4E0_0010a4e0);  // the sound request (a3 = sound id)
                lw(a0, s0, 24);
                jal(ctx, 0x1683A4u, gen::fn_sub_111EE0_00111ee0);  // start the .anm
                lw(a0, s0, 24);
                a1 = 1;
                jal(ctx, 0x1683B4u, gen::fn_sub_111F20_00111f20);  // set the .anm's play flag
                v0 = 5;
                sw(v0, s0, 0);
            }
            goto L_00168588;
        case 0x1683CCu:  // table[5]
            // 0x001683cc
            charge(ctx, 4);
            lw(v1, s0, 12);
            v0 = 3;
            if (v1 == v0) {
                // 0x001683dc
                charge(ctx, 4);
                lw(v1, s0, 4);
                v0 = 10;
                if (v1 != v0) {
                    // 0x001683ec
                    charge(ctx, 2);
                    v0 = addiu(v1, 1);
                    sw(v0, s0, 4);
                }
                // 0x001683f4
                charge(ctx, 13);
                lwc1(f0, s0, 4);
                cvt_s_w(f1, f0);
                v0 = 0x41200000;
                mtc1(v0, f0);
                div_s(f1, f1, f0);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                sub_s(f12, f0, f1);
                lw(a0, s0, 20);
                jal(ctx, 0x168420u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
            }
            // 0x00168428
            charge(ctx, 5);
            lw(a0, s0, 24);
            jal(ctx, 0x16842Cu, gen::fn_sub_111CB0_00111cb0);  // non-zero when the .anm ended
            if (v0 != 0) {
                // 0x0016843c
                charge(ctx, 4);
                lw(v1, s0, 12);
                v0 = 3;
                if (v1 == v0) {
                    // 0x00168474
                    charge(ctx, 4);
                    mtc1(zero, f12);
                    lw(a0, s0, 20);
                    jal(ctx, 0x16847Cu, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                } else {
                    // 0x0016844c
                    charge(ctx, 3);
                    lw(a0, s0, 20);
                    if (a0 != 0) {
                        // 0x00168458
                        charge(ctx, 2);
                        jal(ctx, 0x168458u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                    }
                    // 0x00168460
                    charge(ctx, 5);
                    lw(v0, s0, 24);
                    sw(v0, s0, 20);
                    sw(zero, s0, 24);
                }
                // 0x00168484
                charge(ctx, 4);
                v0 = 2;
                sw(v0, s0, 0);
            }
            goto L_00168588;
        case 0x168494u:  // table[6]
            // 0x00168494
            charge(ctx, 5);
            lw(v0, s0, 4);
            v0 = addiu(v0, -1);
            sw(v0, s0, 4);
            if (v0 != 0) {
                // 0x001684a8
                charge(ctx, 14);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41200000;
                mtc1(v0, f0);
                div_s(f12, f1, f0);
                lw(a0, s0, 20);
                jal(ctx, 0x1684D0u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                goto L_00168588;
            }
            // 0x001684e0
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x1684ECu:  // table[7]
            // 0x001684ec
            charge(ctx, 5);
            lw(v0, s0, 4);
            v0 = addiu(v0, -1);
            sw(v0, s0, 4);
            if (v0 == 0) {
                // 0x00168554
                charge(ctx, 3);
                lw(a0, s0, 24);
                if (a0 != 0) {
                    // 0x00168560
                    charge(ctx, 2);
                    jal(ctx, 0x168560u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                }
                // 0x00168568
                charge(ctx, 8);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                lw(a0, s0, 20);
                jal(ctx, 0x168574u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                sw(zero, s0, 24);
                v0 = 2;
                sw(v0, s0, 0);
            } else {
                // 0x00168500
                charge(ctx, 21);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                v0 = 0x41200000;
                mtc1(v0, f0);
                div_s(f20, f1, f0);
                lw(a0, s0, 24);
                mov_s(f12, f20);
                jal(ctx, 0x168528u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
                v0 = 0x3F800000;
                mtc1(v0, f0);
                sub_s(f12, f0, f20);
                lw(a0, s0, 20);
                jal(ctx, 0x168544u, gen::fn_sub_111D50_00111d50);  // draw one frame of an .anm task ($f12 = step)
            }
            goto L_00168588;
        case 0x168588u:  // table[2]
            goto L_00168588;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x0016858c (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s0, sp, 0x10);
        lwc1(f20, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
    goto L_00168588;
}

// 0x001685E0 sub_1685E0 -- 312 bytes; leaf frame (no stack)
// [H_Camp_FrStatusFlashRequest] (task, screen): picks the party-status transition for (shown screen +8, new screen)
// and sets the state / kind.
void sub_1685E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x001685e0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(t0, a0, task::kWork);
    lw(a3, t0, 8);
    v1 = 4;
    if (a3 == v1) {
        // 0x001686fc
        charge(ctx, 5);
        v1 = 10;
        sw(v1, t0, 4);
        v1 = 7;
        sw(v1, t0, 0);
        sw(a1, t0, 8);
    } else {
        // 0x001685f4
        charge(ctx, 3);
        a2 = 2;
        if (a3 == a2) {
            // 0x001686a8
            charge(ctx, 3);
            a0 = 3;
            if (a1 == a0) {
                // 0x001686e0
                charge(ctx, 4);
                v1 = 10;
                sw(v1, t0, 4);
                v1 = 6;
                sw(v1, t0, 0);
            } else {
                // 0x001686b4
                charge(ctx, 2);
                if (a1 != a2) {
                    // 0x001686bc
                    charge(ctx, 3);
                    v1 = 1;
                    if (a1 == v1) {
                        // 0x001686d0
                        charge(ctx, 4);
                        sw(a2, t0, 12);
                        sw(a0, t0, 0);
                    } else {
                        // 0x001686c8
                        charge(ctx, 2);
                    }
                }
            }
            // 0x001686f0
            charge(ctx, 3);
            sw(a1, t0, 8);
        } else {
            // 0x00168600
            charge(ctx, 3);
            a0 = 1;
            if (a3 == a0) {
                // 0x0016863c
                charge(ctx, 2);
                if (a1 == v1) {
                    // 0x00168690
                    charge(ctx, 3);
                    v1 = 3;
                    sw(v1, t0, 12);
                    sw(v1, t0, 0);
                } else {
                    // 0x00168644
                    charge(ctx, 3);
                    v1 = 3;
                    if (a1 == v1) {
                        // 0x00168678
                        charge(ctx, 6);
                        v1 = 10;
                        sw(v1, t0, 4);
                        v1 = 6;
                        sw(v1, t0, 0);
                    } else {
                        // 0x00168650
                        charge(ctx, 2);
                        if (a1 == a2) {
                            // 0x00168668
                            charge(ctx, 4);
                            sw(a0, t0, 12);
                            sw(v1, t0, 0);
                        } else {
                            // 0x00168658
                            charge(ctx, 2);
                            if (a1 != a0) {
                                // 0x00168660
                                charge(ctx, 2);
                            }
                        }
                    }
                }
                // 0x0016869c
                charge(ctx, 3);
                sw(a1, t0, 8);
            } else {
                // 0x0016860c
                charge(ctx, 2);
                if (a3 == 0) {
                    // 0x0016861c
                    charge(ctx, 2);
                    if (a1 == a0) {
                        // 0x00168624
                        charge(ctx, 6);
                        sw(zero, t0, 12);
                        v1 = 3;
                        sw(v1, t0, 0);
                        sw(a1, t0, 8);
                    }
                } else {
                    // 0x00168614
                    charge(ctx, 2);
                }
            }
        }
    }
    // 0x00168710 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00168720 sub_168720 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Destroy of "H_FrStatusFlashDraw": the pak +16, the work.
void sub_168720(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00168720
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a0, s0, 16);
    if (a0 != 0) {
        // 0x0016873c
        charge(ctx, 2);
        jal(ctx, 0x16873Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
    }
    // 0x00168744
    charge(ctx, 11);
    sw(zero, s0, 16);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x168754u, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00168770 sub_168770 -- 160 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [H_Camp_CreateFrStatusFlashTask] (parent, priority): creates "H_FrStatusFlashDraw" (28-byte work, update
// sub_168220).
void sub_168770(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00168770
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = 1;
    a1 = 28;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x16879Cu, v0.u());
    if (v0 != 0) {
        // 0x001687b8
        charge(ctx, 13);
        a0 = s1;
        a1 = 0x5E0000;
        a1 = addiu(a1, -16384);  // "H_FrStatusFlashDraw"
        a2 = s0;
        a3 = 0x170000;
        a3 = addiu(a3, -32224);  // &sub_168220
        t0 = 0x170000;
        t0 = addiu(t0, -30944);  // &sub_168720
        t1 = v0;
        jal(ctx, 0x1687DCu, gen::fn_kwlnTaskCreate_00194b20);
        if (v0 == 0) {
            // 0x001687ec
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x001687ac
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001687f8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00169040 sub_169040 -- 208 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Destroy of "H_CampTradeDraw": blocks +28 / +32, the two sprite files +20.. (and 0x833A50), the work.
void sub_169040(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00169040
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, task::kWork);
    lw(a0, s1, 28);
    if (a0 != 0) {
        // 0x00169064
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x16906Cu, v0.u());
        sw(zero, s1, 28);
    }
    // 0x00169078
    charge(ctx, 3);
    lw(a0, s1, 32);
    if (a0 != 0) {
        // 0x00169084
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x16908Cu, v0.u());
        sw(zero, s1, 32);
    }
    // 0x00169098
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x001690d4
        charge(ctx, 3);
        v0 = slti(s0, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001690a4
        charge(ctx, 5);
        s2 = sll(s0, 2);
        v0 = addu(s1, s2);
        lw(a0, v0, 20);
        if (a0 != 0) {
            // 0x001690b8
            charge(ctx, 2);
            jal(ctx, 0x1690B8u, gen::fn_sub_1124B0_001124b0);  // release a sprite file
        }
        // 0x001690c0
        charge(ctx, 5);
        v0 = 0x830000;
        v0 = addiu(v0, 14928);  // &0x833A50
        v0 = addu(v0, s2);
        sw(zero, v0, 0);
        s0 = addiu(s0, 1);
    }
    // 0x001690e0
    charge(ctx, 12);
    a0 = s1;
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x1690ECu, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00169330 sub_169330 -- 232 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM: opens the equipment trade screen "H_CampTradeDraw" for member scrGetIntPara(0) (camp_item.pak) into gp-19824;
// returns 1.
void sub_169330(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00169330
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x169348u, gen::fn_scrGetIntPara_0035ed20);
    s0 = dsll32(v0, 16);
    s0 = dsra32(s0, 16);
    a0 = 1;
    a1 = 40;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x16936Cu, v0.u());
    s1 = v0;
    if (s1 != 0) {
        // 0x0016938c
        charge(ctx, 14);
        a0 = 0;
        a1 = 0x5E0000;
        a1 = addiu(a1, -16352);  // "H_CampTradeDraw"
        a2 = 6335;
        a3 = 0x170000;
        a3 = addiu(a3, -30704);  // &sub_168810
        t0 = 0x170000;
        t0 = addiu(t0, -28608);  // &sub_169040
        t1 = s1;
        jal(ctx, 0x1693B0u, gen::fn_kwlnTaskCreate_00194b20);
        s2 = v0;
        if (s2 != 0) {
            // 0x001693d0
            charge(ctx, 9);
            v0 = dsll32(s0, 16);
            v0 = dsra32(v0, 16);
            sw(v0, s1, 12);
            a0 = 0x5E0000;
            a0 = addiu(a0, -17312);  // "camp/camp_item.pak"
            a1 = 1;
            jal(ctx, 0x1693E8u, gen::fn_H_Cdvd_Request_00100d80);
            sw(v0, s1, 16);
        } else {
            // 0x001693c4
            charge(ctx, 3);
            s2 = 0;
        }
    } else {
        // 0x00169380
        charge(ctx, 3);
        s2 = 0;
    }
    // 0x001693f4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    sw(s2, gp, g::kTradeTask);  // 0x7CDF80
    v0 = 1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00169AE0 sub_169AE0 -- 176 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Destroy of a trade sub-task: block +24, the two sprite files +16.., the file +12, the work.
void sub_169AE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00169ae0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, task::kWork);
    lw(a0, s0, 24);
    if (a0 != 0) {
        // 0x00169b00
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
        jalr(ctx, 0x169B08u, v0.u());
        sw(zero, s0, 24);
    }
    // 0x00169b14
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x00169b40
        charge(ctx, 3);
        v0 = slti(s1, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00169b20
        charge(ctx, 5);
        v0 = sll(s1, 2);
        v0 = addu(s0, v0);
        lw(a0, v0, 16);
        if (a0 != 0) {
            // 0x00169b34
            charge(ctx, 2);
            jal(ctx, 0x169B34u, gen::fn_sub_1124B0_001124b0);  // release a sprite file
        }
        // 0x00169b3c
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x00169b4c
    charge(ctx, 3);
    lw(a0, s0, 12);
    if (a0 != 0) {
        // 0x00169b58
        charge(ctx, 2);
        jal(ctx, 0x169B58u, gen::fn_H_Cdvd_Destroy_00100ec0);
    }
    // 0x00169b60
    charge(ctx, 12);
    sw(zero, s0, 12);
    a0 = s0;
    v0 = 0x960000;
    lw(v0, v0, rw::kFreeSlot);  // 0x96017C RwFree
    jalr(ctx, 0x169B70u, v0.u());
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0016A6A0 sub_16A6A0 -- 88 bytes; frame 0x10: ra sp+0x0
// COMM: 1 when the task of gp-19828 is gone or finished (and forgets it), else 0.
void sub_16A6A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0016a6a0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, g::kScreenTaskC);  // 0x7CDF7C
    if (a0 != 0) {
        // 0x0016a6c0
        charge(ctx, 5);
        jal(ctx, 0x16A6C0u, gen::fn_kwlnTaskGetState_00195290);
        v1 = 3;
        if (v0 != v1) {
            // 0x0016a6e4
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0016a6d4
            charge(ctx, 4);
            sw(zero, gp, g::kScreenTaskC);  // 0x7CDF7C
            v0 = 1;
        }
    } else {
        // 0x0016a6b4
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0016a6e8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0018B6D0 sub_18B6D0 -- 48 bytes; frame 0x10: ra sp+0x0
// [H_Camp_AllocTweens] (count): RwCalloc(count, 68, 0x40000) -- an array of 68-byte tween records.
void sub_18B6D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0018b6d0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 68;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, rw::kCallocSlot);  // 0x960184 RwCalloc
    jalr(ctx, 0x18B6E8u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0018BC10 sub_18BC10 -- 108 bytes; frame 0x10
// [H_Camp_TweenStart] (record, kind, mode, curve, from xy, to xy, a, b, z in $f12, first frame, last frame): starts a
// tween record: +4 = 1 active, +8 kind, +12 mode, +16 curve, +40 / +48 from / to (two floats each), +0 / +20 the two
// extra words, +36 z, +28 / +32 the frame range, +24 frame = 0.
void sub_18BC10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x0018bc10
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(t0, sp, 0x0);
    sd(t1, sp, 0x8);
    v1 = 1;
    sw(v1, a0, tw::kActive);
    sw(a1, a0, tw::kKind);
    sw(a2, a0, tw::kMode);
    sw(a3, a0, tw::kCurve);
    lwc1(f1, sp, 0x0);
    lwc1(f0, sp, 0x4);
    swc1(f1, a0, tw::kFromX);
    swc1(f0, a0, tw::kFromY);
    lwc1(f1, sp, 0x8);
    lwc1(f0, sp, 0xC);
    swc1(f1, a0, tw::kToX);
    swc1(f0, a0, tw::kToY);
    sw(t2, a0, tw::kExtraA);
    sw(t3, a0, tw::kExtraB);
    swc1(f12, a0, tw::kZ);
    lw(v1, sp, 0x10);
    sw(v1, a0, tw::kFirst);
    lw(v1, sp, 0x18);
    sw(v1, a0, tw::kLast);
    sw(zero, a0, tw::kFrame);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
