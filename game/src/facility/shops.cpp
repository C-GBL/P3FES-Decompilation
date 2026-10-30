// The shop code of the facilities band 0x3DF4A0-0x417158 (slice shops; game/include/p3fes/game/shops.h has the map,
// the shop types and the record layouts). docs/ANALYSIS/27_unmapped_bands.md section 8.
//
// The bodies are p3fes_handgen's (game/include/p3fes/game/hg_cpu.h): one statement per instruction on the guest
// registers, the original's frame, spills, $ra links, cycle charges and check points, so every register the original
// leaves at a check point, call or return is left the same way (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen").
// This readability pass adds the role of each function above it (a proposed name in brackets), names the record
// offsets where one register holds one record for the whole body (shop::kShop* the shop work record, shop::kElem* a
// facility element, shop::kBg* the background manager, shop::kBank* the sprite bank, shop::kStep* / kLoad* a sequence
// step's payload), and labels every state of the shop's root state machine (sub_3E6E80) at its jump-table case. It
// changes no statement. `// 0x00xxxxxx` lines name the original basic block a C++ block comes from.
//
// Kept as the original has them: the K_Assert calls (sub_19D3F0, `jr $ra` in retail: a failed check continues), the
// greeting's "random" index that is always 0 (sub_3F0830), the stack copies of the template / descriptor tables.
// Left recompiled in the band: the 20 KB element-template builder sub_3E0C20 and the big list / menu bodies (see
// docs/INTEGRATION_LOG.md), sub_40E360 (the fusion pair tests stand it in), the bank, the debug editors, fusion.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/shops.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_CacheFindFile_001021c0(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_MT_Scene_Load_003b5760(p3fes::EEContext&);
void fn_adminiChangeSeq_0027c080(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_datGetEquipmentIdx_0016cb80(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_fclMisc_CreatePsStatusTasks_003c9850(p3fes::EEContext&);
void fn_fclShopMisc_CreateShopDrawBGLowTasks_00400d60(p3fes::EEContext&);
void fn_fclShopMisc_UpdateShopDrawBGHighLowTask_004012c0(p3fes::EEContext&);
void fn_fclShopMisc_UpdateShopDrawBGHighTopTask_00401370(p3fes::EEContext&);
void fn_fclShopMisc_UpdateShopDrawBGLowTask_00401210(p3fes::EEContext&);
void fn_fclShop_CreateShopDrawTasks_003e0780(p3fes::EEContext&);
void fn_fclShop_UpdateShopDraw2Task_003e08e0(p3fes::EEContext&);
void fn_fclShop_UpdateShopDrawTask_003e0870(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskGetState_00195290(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_msgWinLastSelection_003c7610(p3fes::EEContext&);
void fn_msgWinRequestMessage_003c7430(p3fes::EEContext&);
void fn_msgWinSetType_003c7560(p3fes::EEContext&);
void fn_nmCmdListAddRow_003c5a40(p3fes::EEContext&);
void fn_nmCmdListDestroy_003c5a20(p3fes::EEContext&);
void fn_nmCmdListDraw_003c6380(p3fes::EEContext&);
void fn_nmCmdListMovedDownRow_003c6ce0(p3fes::EEContext&);
void fn_nmCmdListMovedUp_003c6cc0(p3fes::EEContext&);
void fn_nmCmdListPagedDown_003c6ca0(p3fes::EEContext&);
void fn_nmCmdListRelease_003c6ec0(p3fes::EEContext&);
void fn_nmCmdListRemoveRow_003c5fa0(p3fes::EEContext&);
void fn_nmCmdListScrolledRow_003c6d10(p3fes::EEContext&);
void fn_nmCmdListStatus28_003c6e10(p3fes::EEContext&);
void fn_nmCmdListUpdate_003c6270(p3fes::EEContext&);
void fn_nmListAppendNew_003c4910(p3fes::EEContext&);
void fn_nmListFindByWord4_003c4bf0(p3fes::EEContext&);
void fn_nmListRemoveFiltered_003c4e70(p3fes::EEContext&);
void fn_nmObjPayloadWord12_003c5460(p3fes::EEContext&);
void fn_nmSequenceAddStep_003c5240(p3fes::EEContext&);
void fn_nmSequenceCallAll36_003c5760(p3fes::EEContext&);
void fn_nmSequenceCreate_003c5180(p3fes::EEContext&);
void fn_nmSequenceDestroy_003c5220(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_scrGetCmdTimer_0035f130(p3fes::EEContext&);
void fn_scrGetIntPara_0035ed20(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_sprCreateHandleFromData_00112420(p3fes::EEContext&);
void fn_sprCreateHandle_001158b0(p3fes::EEContext&);
void fn_sprFontGetFile_001120a0(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_sub_1052B0_001052b0(p3fes::EEContext&);
void fn_sub_108570_00108570(p3fes::EEContext&);
void fn_sub_1085C0_001085c0(p3fes::EEContext&);
void fn_sub_108670_00108670(p3fes::EEContext&);
void fn_sub_108710_00108710(p3fes::EEContext&);
void fn_sub_1099D0_001099d0(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sub_111C50_00111c50(p3fes::EEContext&);
void fn_sub_111CA0_00111ca0(p3fes::EEContext&);
void fn_sub_111CB0_00111cb0(p3fes::EEContext&);
void fn_sub_111D50_00111d50(p3fes::EEContext&);
void fn_sub_111DD0_00111dd0(p3fes::EEContext&);
void fn_sub_111EC0_00111ec0(p3fes::EEContext&);
void fn_sub_111EE0_00111ee0(p3fes::EEContext&);
void fn_sub_111F00_00111f00(p3fes::EEContext&);
void fn_sub_111F10_00111f10(p3fes::EEContext&);
void fn_sub_111F20_00111f20(p3fes::EEContext&);
void fn_sub_1124B0_001124b0(p3fes::EEContext&);
void fn_sub_1127D0_001127d0(p3fes::EEContext&);
void fn_sub_115980_00115980(p3fes::EEContext&);
void fn_sub_16C470_0016c470(p3fes::EEContext&);
void fn_sub_16DBA0_0016dba0(p3fes::EEContext&);
void fn_sub_16DD50_0016dd50(p3fes::EEContext&);
void fn_sub_16E100_0016e100(p3fes::EEContext&);
void fn_sub_16E2B0_0016e2b0(p3fes::EEContext&);
void fn_sub_16E930_0016e930(p3fes::EEContext&);
void fn_sub_16F490_0016f490(p3fes::EEContext&);
void fn_sub_16F630_0016f630(p3fes::EEContext&);
void fn_sub_16F720_0016f720(p3fes::EEContext&);
void fn_sub_16FEA0_0016fea0(p3fes::EEContext&);
void fn_sub_170760_00170760(p3fes::EEContext&);
void fn_sub_170C00_00170c00(p3fes::EEContext&);
void fn_sub_170E90_00170e90(p3fes::EEContext&);
void fn_sub_170ED0_00170ed0(p3fes::EEContext&);
void fn_sub_172660_00172660(p3fes::EEContext&);
void fn_sub_17C190_0017c190(p3fes::EEContext&);
void fn_sub_17C220_0017c220(p3fes::EEContext&);
void fn_sub_17C670_0017c670(p3fes::EEContext&);
void fn_sub_17D040_0017d040(p3fes::EEContext&);
void fn_sub_17D1A0_0017d1a0(p3fes::EEContext&);
void fn_sub_17D250_0017d250(p3fes::EEContext&);
void fn_sub_17D610_0017d610(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_1828D0_001828d0(p3fes::EEContext&);
void fn_sub_1830C0_001830c0(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_1A0040_001a0040(p3fes::EEContext&);
void fn_sub_1A0150_001a0150(p3fes::EEContext&);
void fn_sub_1A1150_001a1150(p3fes::EEContext&);
void fn_sub_1A1190_001a1190(p3fes::EEContext&);
void fn_sub_1A4580_001a4580(p3fes::EEContext&);
void fn_sub_3A2090_003a2090(p3fes::EEContext&);
void fn_sub_3B5A10_003b5a10(p3fes::EEContext&);
void fn_sub_3C44D0_003c44d0(p3fes::EEContext&);
void fn_sub_3C45F0_003c45f0(p3fes::EEContext&);
void fn_sub_3C49E0_003c49e0(p3fes::EEContext&);
void fn_sub_3C5470_003c5470(p3fes::EEContext&);
void fn_sub_3C5490_003c5490(p3fes::EEContext&);
void fn_sub_3C6EE0_003c6ee0(p3fes::EEContext&);
void fn_sub_3C72D0_003c72d0(p3fes::EEContext&);
void fn_sub_3C74E0_003c74e0(p3fes::EEContext&);
void fn_sub_3C7700_003c7700(p3fes::EEContext&);
void fn_sub_3C7850_003c7850(p3fes::EEContext&);
void fn_sub_3C7B90_003c7b90(p3fes::EEContext&);
void fn_sub_3C7BC0_003c7bc0(p3fes::EEContext&);
void fn_sub_3C7C20_003c7c20(p3fes::EEContext&);
void fn_sub_3C7D80_003c7d80(p3fes::EEContext&);
void fn_sub_3C82E0_003c82e0(p3fes::EEContext&);
void fn_sub_3C83B0_003c83b0(p3fes::EEContext&);
void fn_sub_3C9790_003c9790(p3fes::EEContext&);
void fn_sub_3C9AB0_003c9ab0(p3fes::EEContext&);
void fn_sub_3D02F0_003d02f0(p3fes::EEContext&);
void fn_sub_3D04B0_003d04b0(p3fes::EEContext&);
void fn_sub_3DF100_003df100(p3fes::EEContext&);
void fn_sub_3DF4A0_003df4a0(p3fes::EEContext&);
void fn_sub_3DFAC0_003dfac0(p3fes::EEContext&);
void fn_sub_3DFAE0_003dfae0(p3fes::EEContext&);
void fn_sub_3DFEB0_003dfeb0(p3fes::EEContext&);
void fn_sub_3DFF00_003dff00(p3fes::EEContext&);
void fn_sub_3DFF30_003dff30(p3fes::EEContext&);
void fn_sub_3DFF80_003dff80(p3fes::EEContext&);
void fn_sub_3DFFC0_003dffc0(p3fes::EEContext&);
void fn_sub_3E0080_003e0080(p3fes::EEContext&);
void fn_sub_3E0260_003e0260(p3fes::EEContext&);
void fn_sub_3E0330_003e0330(p3fes::EEContext&);
void fn_sub_3E04E0_003e04e0(p3fes::EEContext&);
void fn_sub_3E0650_003e0650(p3fes::EEContext&);
void fn_sub_3E0680_003e0680(p3fes::EEContext&);
void fn_sub_3E0700_003e0700(p3fes::EEContext&);
void fn_sub_3E0830_003e0830(p3fes::EEContext&);
void fn_sub_3E0920_003e0920(p3fes::EEContext&);
void fn_sub_3E0950_003e0950(p3fes::EEContext&);
void fn_sub_3E0A10_003e0a10(p3fes::EEContext&);
void fn_sub_3E0BB0_003e0bb0(p3fes::EEContext&);
void fn_sub_3E0BC0_003e0bc0(p3fes::EEContext&);
void fn_sub_3E0C20_003e0c20(p3fes::EEContext&);
void fn_sub_3E6130_003e6130(p3fes::EEContext&);
void fn_sub_3E6400_003e6400(p3fes::EEContext&);
void fn_sub_3E6D40_003e6d40(p3fes::EEContext&);
void fn_sub_3E6D70_003e6d70(p3fes::EEContext&);
void fn_sub_3E6DC0_003e6dc0(p3fes::EEContext&);
void fn_sub_3E6E80_003e6e80(p3fes::EEContext&);
void fn_sub_3E86C0_003e86c0(p3fes::EEContext&);
void fn_sub_3E8740_003e8740(p3fes::EEContext&);
void fn_sub_3E87C0_003e87c0(p3fes::EEContext&);
void fn_sub_3E8830_003e8830(p3fes::EEContext&);
void fn_sub_3E8860_003e8860(p3fes::EEContext&);
void fn_sub_3E8E10_003e8e10(p3fes::EEContext&);
void fn_sub_3E8E20_003e8e20(p3fes::EEContext&);
void fn_sub_3E8FF0_003e8ff0(p3fes::EEContext&);
void fn_sub_3E90B0_003e90b0(p3fes::EEContext&);
void fn_sub_3E9200_003e9200(p3fes::EEContext&);
void fn_sub_3E94F0_003e94f0(p3fes::EEContext&);
void fn_sub_3E96F0_003e96f0(p3fes::EEContext&);
void fn_sub_3E9790_003e9790(p3fes::EEContext&);
void fn_sub_3E97F0_003e97f0(p3fes::EEContext&);
void fn_sub_3E98B0_003e98b0(p3fes::EEContext&);
void fn_sub_3E9970_003e9970(p3fes::EEContext&);
void fn_sub_3E9A90_003e9a90(p3fes::EEContext&);
void fn_sub_3EA4D0_003ea4d0(p3fes::EEContext&);
void fn_sub_3EA560_003ea560(p3fes::EEContext&);
void fn_sub_3EA600_003ea600(p3fes::EEContext&);
void fn_sub_3EA6B0_003ea6b0(p3fes::EEContext&);
void fn_sub_3EA770_003ea770(p3fes::EEContext&);
void fn_sub_3EA7E0_003ea7e0(p3fes::EEContext&);
void fn_sub_3EAC40_003eac40(p3fes::EEContext&);
void fn_sub_3EACB0_003eacb0(p3fes::EEContext&);
void fn_sub_3EAD10_003ead10(p3fes::EEContext&);
void fn_sub_3EADD0_003eadd0(p3fes::EEContext&);
void fn_sub_3EB9B0_003eb9b0(p3fes::EEContext&);
void fn_sub_3EBA10_003eba10(p3fes::EEContext&);
void fn_sub_3EBAD0_003ebad0(p3fes::EEContext&);
void fn_sub_3EC030_003ec030(p3fes::EEContext&);
void fn_sub_3EC090_003ec090(p3fes::EEContext&);
void fn_sub_3EC150_003ec150(p3fes::EEContext&);
void fn_sub_3EC6F0_003ec6f0(p3fes::EEContext&);
void fn_sub_3EC7B0_003ec7b0(p3fes::EEContext&);
void fn_sub_3ECD30_003ecd30(p3fes::EEContext&);
void fn_sub_3ECDF0_003ecdf0(p3fes::EEContext&);
void fn_sub_3ED380_003ed380(p3fes::EEContext&);
void fn_sub_3ED420_003ed420(p3fes::EEContext&);
void fn_sub_3EDDD0_003eddd0(p3fes::EEContext&);
void fn_sub_3EDE80_003ede80(p3fes::EEContext&);
void fn_sub_3EE310_003ee310(p3fes::EEContext&);
void fn_sub_3EE3D0_003ee3d0(p3fes::EEContext&);
void fn_sub_3EE480_003ee480(p3fes::EEContext&);
void fn_sub_3EE510_003ee510(p3fes::EEContext&);
void fn_sub_3EE560_003ee560(p3fes::EEContext&);
void fn_sub_3EE570_003ee570(p3fes::EEContext&);
void fn_sub_3EE5F0_003ee5f0(p3fes::EEContext&);
void fn_sub_3EEC60_003eec60(p3fes::EEContext&);
void fn_sub_3EED10_003eed10(p3fes::EEContext&);
void fn_sub_3EED50_003eed50(p3fes::EEContext&);
void fn_sub_3EED90_003eed90(p3fes::EEContext&);
void fn_sub_3EEE10_003eee10(p3fes::EEContext&);
void fn_sub_3EF970_003ef970(p3fes::EEContext&);
void fn_sub_3EFB40_003efb40(p3fes::EEContext&);
void fn_sub_3EFBC0_003efbc0(p3fes::EEContext&);
void fn_sub_3EFC60_003efc60(p3fes::EEContext&);
void fn_sub_3EFCA0_003efca0(p3fes::EEContext&);
void fn_sub_3EFCE0_003efce0(p3fes::EEContext&);
void fn_sub_3EFD70_003efd70(p3fes::EEContext&);
void fn_sub_3EFDE0_003efde0(p3fes::EEContext&);
void fn_sub_3EFE60_003efe60(p3fes::EEContext&);
void fn_sub_3EFED0_003efed0(p3fes::EEContext&);
void fn_sub_3EFEF0_003efef0(p3fes::EEContext&);
void fn_sub_3EFF00_003eff00(p3fes::EEContext&);
void fn_sub_3EFFF0_003efff0(p3fes::EEContext&);
void fn_sub_3F0090_003f0090(p3fes::EEContext&);
void fn_sub_3F00B0_003f00b0(p3fes::EEContext&);
void fn_sub_3F00D0_003f00d0(p3fes::EEContext&);
void fn_sub_3F01D0_003f01d0(p3fes::EEContext&);
void fn_sub_3F0240_003f0240(p3fes::EEContext&);
void fn_sub_3F0350_003f0350(p3fes::EEContext&);
void fn_sub_3F03E0_003f03e0(p3fes::EEContext&);
void fn_sub_3F04F0_003f04f0(p3fes::EEContext&);
void fn_sub_3F06E0_003f06e0(p3fes::EEContext&);
void fn_sub_3F0830_003f0830(p3fes::EEContext&);
void fn_sub_3F0AC0_003f0ac0(p3fes::EEContext&);
void fn_sub_3F0D60_003f0d60(p3fes::EEContext&);
void fn_sub_3F0EC0_003f0ec0(p3fes::EEContext&);
void fn_sub_3F10B0_003f10b0(p3fes::EEContext&);
void fn_sub_3F12A0_003f12a0(p3fes::EEContext&);
void fn_sub_3F1470_003f1470(p3fes::EEContext&);
void fn_sub_3F1520_003f1520(p3fes::EEContext&);
void fn_sub_3F15D0_003f15d0(p3fes::EEContext&);
void fn_sub_3F1690_003f1690(p3fes::EEContext&);
void fn_sub_3F1720_003f1720(p3fes::EEContext&);
void fn_sub_3F1830_003f1830(p3fes::EEContext&);
void fn_sub_3F1A10_003f1a10(p3fes::EEContext&);
void fn_sub_3F1DC0_003f1dc0(p3fes::EEContext&);
void fn_sub_3F2240_003f2240(p3fes::EEContext&);
void fn_sub_3F2510_003f2510(p3fes::EEContext&);
void fn_sub_3F2D60_003f2d60(p3fes::EEContext&);
void fn_sub_3F2DC0_003f2dc0(p3fes::EEContext&);
void fn_sub_3F3280_003f3280(p3fes::EEContext&);
void fn_sub_3F33D0_003f33d0(p3fes::EEContext&);
void fn_sub_3F3970_003f3970(p3fes::EEContext&);
void fn_sub_3F39A0_003f39a0(p3fes::EEContext&);
void fn_sub_3F3DC0_003f3dc0(p3fes::EEContext&);
void fn_sub_3F3F00_003f3f00(p3fes::EEContext&);
void fn_sub_3F7730_003f7730(p3fes::EEContext&);
void fn_sub_3F98F0_003f98f0(p3fes::EEContext&);
void fn_sub_3F99D0_003f99d0(p3fes::EEContext&);
void fn_sub_3F9B20_003f9b20(p3fes::EEContext&);
void fn_sub_3F9CB0_003f9cb0(p3fes::EEContext&);
void fn_sub_3F9E30_003f9e30(p3fes::EEContext&);
void fn_sub_3FA0D0_003fa0d0(p3fes::EEContext&);
void fn_sub_3FA190_003fa190(p3fes::EEContext&);
void fn_sub_3FA1B0_003fa1b0(p3fes::EEContext&);
void fn_sub_3FA1E0_003fa1e0(p3fes::EEContext&);
void fn_sub_3FB290_003fb290(p3fes::EEContext&);
void fn_sub_3FBC00_003fbc00(p3fes::EEContext&);
void fn_sub_3FBF20_003fbf20(p3fes::EEContext&);
void fn_sub_3FC060_003fc060(p3fes::EEContext&);
void fn_sub_3FC540_003fc540(p3fes::EEContext&);
void fn_sub_3FC980_003fc980(p3fes::EEContext&);
void fn_sub_3FD820_003fd820(p3fes::EEContext&);
void fn_sub_3FD8A0_003fd8a0(p3fes::EEContext&);
void fn_sub_3FDF80_003fdf80(p3fes::EEContext&);
void fn_sub_3FE2B0_003fe2b0(p3fes::EEContext&);
void fn_sub_3FF630_003ff630(p3fes::EEContext&);
void fn_sub_3FFA20_003ffa20(p3fes::EEContext&);
void fn_sub_3FFBB0_003ffbb0(p3fes::EEContext&);
void fn_sub_3FFE00_003ffe00(p3fes::EEContext&);
void fn_sub_3FFE60_003ffe60(p3fes::EEContext&);
void fn_sub_4003F0_004003f0(p3fes::EEContext&);
void fn_sub_400690_00400690(p3fes::EEContext&);
void fn_sub_400740_00400740(p3fes::EEContext&);
void fn_sub_400A90_00400a90(p3fes::EEContext&);
void fn_sub_400B90_00400b90(p3fes::EEContext&);
void fn_sub_400E90_00400e90(p3fes::EEContext&);
void fn_sub_401170_00401170(p3fes::EEContext&);
void fn_sub_401420_00401420(p3fes::EEContext&);
void fn_sub_4014E0_004014e0(p3fes::EEContext&);
void fn_sub_4015A0_004015a0(p3fes::EEContext&);
void fn_sub_4015E0_004015e0(p3fes::EEContext&);
void fn_sub_401600_00401600(p3fes::EEContext&);
void fn_sub_401890_00401890(p3fes::EEContext&);
void fn_sub_401950_00401950(p3fes::EEContext&);
void fn_sub_402480_00402480(p3fes::EEContext&);
void fn_sub_4030B0_004030b0(p3fes::EEContext&);
void fn_sub_4030F0_004030f0(p3fes::EEContext&);
void fn_sub_403520_00403520(p3fes::EEContext&);
void fn_sub_403610_00403610(p3fes::EEContext&);
void fn_sub_4038A0_004038a0(p3fes::EEContext&);
void fn_sub_403970_00403970(p3fes::EEContext&);
void fn_sub_403E40_00403e40(p3fes::EEContext&);
void fn_sub_403F20_00403f20(p3fes::EEContext&);
void fn_sub_404120_00404120(p3fes::EEContext&);
void fn_sub_4044C0_004044c0(p3fes::EEContext&);
void fn_sub_40C170_0040c170(p3fes::EEContext&);
void fn_sub_40C310_0040c310(p3fes::EEContext&);
void fn_sub_40C490_0040c490(p3fes::EEContext&);
void fn_sub_40C6F0_0040c6f0(p3fes::EEContext&);
void fn_sub_40CAD0_0040cad0(p3fes::EEContext&);
void fn_sub_40D410_0040d410(p3fes::EEContext&);
void fn_sub_40D490_0040d490(p3fes::EEContext&);
void fn_sub_40D5E0_0040d5e0(p3fes::EEContext&);
void fn_sub_40D610_0040d610(p3fes::EEContext&);
void fn_sub_40D640_0040d640(p3fes::EEContext&);
void fn_sub_40E300_0040e300(p3fes::EEContext&);
void fn_sub_40E390_0040e390(p3fes::EEContext&);
void fn_sub_40E3C0_0040e3c0(p3fes::EEContext&);
void fn_sub_40E3F0_0040e3f0(p3fes::EEContext&);
void fn_sub_40E450_0040e450(p3fes::EEContext&);
void fn_sub_40E4F0_0040e4f0(p3fes::EEContext&);
void fn_sub_40E580_0040e580(p3fes::EEContext&);
void fn_sub_40E610_0040e610(p3fes::EEContext&);
void fn_sub_40E710_0040e710(p3fes::EEContext&);
void fn_sub_40EB50_0040eb50(p3fes::EEContext&);
void fn_sub_40EC20_0040ec20(p3fes::EEContext&);
void fn_sub_40EC50_0040ec50(p3fes::EEContext&);
void fn_sub_40EEF0_0040eef0(p3fes::EEContext&);
void fn_sub_410D30_00410d30(p3fes::EEContext&);
void fn_sub_410E70_00410e70(p3fes::EEContext&);
void fn_sub_4110F0_004110f0(p3fes::EEContext&);
void fn_sub_411190_00411190(p3fes::EEContext&);
void fn_sub_411340_00411340(p3fes::EEContext&);
void fn_sub_412580_00412580(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);
void fn_sub_4CB7F0_004cb7f0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x003DF4A0 sub_3DF4A0 -- 1568 bytes; frame 0x40: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
// [fclElementAnimate] The per-node callback of an element set (sub_3DFEB0 hands it to the nm list;
// nmListRemoveFiltered runs it every frame through sub_3E0650): $a1 the node, its payload (+20) the element. State 1
// counts the delay (+44) down, then goes to 2 (eased move) or, with element flag 2, to 3 (arc). 2 / 3 reset the frame
// counter and fall into 4 / 5. 4: frame += 1; x, y and the second pair (+32) move from their start to their end
// values along a sine ease (sinf of the frame fraction, through the constant pool 0x7CAE00 / 0x7CAF14), alpha (+38)
// linearly; 5: the second pair eased, x / y on an arc of radius 464 around (320, 504) (cosf / sinf). When the frame
// count reaches the duration (+48) every value snaps to its end, state 6 and flag 4 (done). Returns 0 (keep the
// node). A jump table of 6 cases (states 0..5; 0 and 6+ do nothing).
void sub_3DF4A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20}, f21{ctx, 21};
    // 0x003df4a0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    lw(s1, a1, 20);
    lw(v0, s1, shop::kElemState);
    at = sltiu(v0, 7);
    if (at != 0) {
        // 0x003df4cc
        charge(ctx, 7);
        v1 = 0x7C0000;
        v1 = addiu(v1, -18208);  // &0x7BB8E0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x3DF4E8u:  // table[1]: state 1 -- the delay countdown
            // 0x003df4e8
            charge(ctx, 7);
            lh(v0, s1, shop::kElemDelay);
            v0 = addiu(v0, -1);
            sh(v0, s1, shop::kElemDelay);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            if (i64(v0) <= 0) {
                // 0x003df504
                charge(ctx, 5);
                sh(zero, s1, shop::kElemDelay);
                lw(v0, s1, shop::kElemFlags);
                v0 = v0 & 0x2;
                if (v0 == 0) {
                    // 0x003df528
                    charge(ctx, 4);
                    v0 = 2;
                    sw(v0, s1, shop::kElemState);
                } else {
                    // 0x003df518
                    charge(ctx, 4);
                    v0 = 3;
                    sw(v0, s1, shop::kElemState);
                }
            }
            break;
        case 0x3DF538u:  // table[2]: state 2 -- start the eased move
            // 0x003df538
            charge(ctx, 3);
            v0 = 4;
            sw(v0, s1, shop::kElemState);
            sh(zero, s1, shop::kElemFrame);
        L_003df544:
            charge(ctx, 7);
            lhu(v0, s1, shop::kElemFrame);
            v0 = addiu(v0, 1);
            sh(v0, s1, shop::kElemFrame);
            lh(s0, s1, shop::kElemX0);
            lhu(v0, s1, shop::kElemFrame);
            if (i64(v0) < 0) {
                // 0x003df574
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                add_s(f1, f1, f1);
            } else {
                // 0x003df560
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
            }
            // 0x003df590
            charge(ctx, 5);
            lwc1(f0, gp, -32496);  // 0x7CAE00
            mul_s(f1, f0, f1);
            lhu(v0, s1, shop::kElemFrames);
            if (i64(v0) < 0) {
                // 0x003df5b8
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x003df5a4
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x003df5d4
            charge(ctx, 30);
            div_s(f12, f1, f0);
            jal(ctx, 0x3DF5ECu, gen::fn_sinf_0052e878);
            lh(v1, s1, shop::kElemX1);
            v0 = dsll32(s0, 16);
            v0 = dsra32(v0, 16);
            v0 = subu(v1, v0);
            mtc1(v0, f1);
            cvt_s_w(f3, f1);
            mtc1(s0, f1);
            cvt_s_w(f2, f1);
            mtc1(zero, f1);
            adda_s(f1, f2);
            madd_s(f0, f3, f0);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sh(v0, s1, shop::kElemX);
            lh(s0, s1, shop::kElemY0);
            lhu(v0, s1, shop::kElemFrame);
            if (i64(v0) < 0) {
                // 0x003df660
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                add_s(f1, f1, f1);
            } else {
                // 0x003df64c
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
            }
            // 0x003df67c
            charge(ctx, 5);
            lwc1(f0, gp, -32496);  // 0x7CAE00
            mul_s(f1, f0, f1);
            lhu(v0, s1, shop::kElemFrames);
            if (i64(v0) < 0) {
                // 0x003df6a4
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x003df690
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x003df6c0
            charge(ctx, 30);
            div_s(f12, f1, f0);
            jal(ctx, 0x3DF6D8u, gen::fn_sinf_0052e878);
            lh(v1, s1, shop::kElemY1);
            v0 = dsll32(s0, 16);
            v0 = dsra32(v0, 16);
            v0 = subu(v1, v0);
            mtc1(v0, f1);
            cvt_s_w(f3, f1);
            mtc1(s0, f1);
            cvt_s_w(f2, f1);
            mtc1(zero, f1);
            adda_s(f1, f2);
            madd_s(f0, f3, f0);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sh(v0, s1, shop::kElemY);
            lh(s0, s1, shop::kElemScale0);
            lhu(v0, s1, shop::kElemFrame);
            if (i64(v0) < 0) {
                // 0x003df74c
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                add_s(f1, f1, f1);
            } else {
                // 0x003df738
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
            }
            // 0x003df768
            charge(ctx, 5);
            lwc1(f0, gp, -32496);  // 0x7CAE00
            mul_s(f1, f0, f1);
            lhu(v0, s1, shop::kElemFrames);
            if (i64(v0) < 0) {
                // 0x003df790
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x003df77c
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x003df7ac
            charge(ctx, 41);
            div_s(f12, f1, f0);
            jal(ctx, 0x3DF7C4u, gen::fn_sinf_0052e878);
            lh(v1, s1, shop::kElemScale1);
            v0 = dsll32(s0, 16);
            v0 = dsra32(v0, 16);
            v0 = subu(v1, v0);
            mtc1(v0, f1);
            cvt_s_w(f3, f1);
            mtc1(s0, f1);
            cvt_s_w(f2, f1);
            mtc1(zero, f1);
            adda_s(f1, f2);
            madd_s(f0, f3, f0);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sh(v0, s1, shop::kElemScale);
            lh(a0, s1, shop::kElemAlpha0);
            lhu(v1, s1, shop::kElemFrame);
            lh(v0, s1, shop::kElemAlpha1);
            v0 = subu(v0, a0);
            mult(v1, v1, v0);
            lhu(v0, s1, shop::kElemFrames);
            div(v1, v0);
            mflo(v0);
            v0 = addu(a0, v0);
            sh(v0, s1, shop::kElemAlpha);
            lhu(v1, s1, shop::kElemFrame);
            lhu(v0, s1, shop::kElemFrames);
            v0 = slt(v1, v0);
            if (v0 == 0) {
                // 0x003df850
                charge(ctx, 16);
                lh(v0, s1, shop::kElemX1);
                sh(v0, s1, shop::kElemX);
                lh(v0, s1, shop::kElemY1);
                sh(v0, s1, shop::kElemY);
                lh(v0, s1, shop::kElemScale1);
                sh(v0, s1, shop::kElemScale);
                lh(v0, s1, shop::kElemAlpha1);
                sh(v0, s1, shop::kElemAlpha);
                sh(zero, s1, shop::kElemFrame);
                v0 = 6;
                sw(v0, s1, shop::kElemState);
                lw(v0, s1, shop::kElemFlags);
                v0 = v0 | 0x4;
                sw(v0, s1, shop::kElemFlags);
            }
            break;
        case 0x3DF544u:  // table[4]: state 4 -- the eased move
            goto L_003df544;
        case 0x3DF890u:  // table[3]: state 3 -- start the arc
            // 0x003df890
            charge(ctx, 3);
            v0 = 5;
            sw(v0, s1, shop::kElemState);
            sh(zero, s1, shop::kElemFrame);
        L_003df89c:
            charge(ctx, 7);
            lhu(v0, s1, shop::kElemFrame);
            v0 = addiu(v0, 1);
            sh(v0, s1, shop::kElemFrame);
            lh(s0, s1, shop::kElemScale0);
            lhu(v0, s1, shop::kElemFrame);
            if (i64(v0) < 0) {
                // 0x003df8cc
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                add_s(f1, f1, f1);
            } else {
                // 0x003df8b8
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
            }
            // 0x003df8e8
            charge(ctx, 5);
            lwc1(f0, gp, -32496);  // 0x7CAE00
            mul_s(f1, f0, f1);
            lhu(v0, s1, shop::kElemFrames);
            if (i64(v0) < 0) {
                // 0x003df910
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                add_s(f0, f0, f0);
            } else {
                // 0x003df8fc
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
            }
            // 0x003df92c
            charge(ctx, 78);
            div_s(f12, f1, f0);
            jal(ctx, 0x3DF944u, gen::fn_sinf_0052e878);
            lh(v1, s1, shop::kElemScale1);
            v0 = dsll32(s0, 16);
            v0 = dsra32(v0, 16);
            v0 = subu(v1, v0);
            mtc1(v0, f1);
            cvt_s_w(f3, f1);
            mtc1(s0, f1);
            cvt_s_w(f2, f1);
            mtc1(zero, f1);
            adda_s(f1, f2);
            madd_s(f0, f3, f0);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sh(v0, s1, shop::kElemScale);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, gp, -32220);  // 0x7CAF14
            mul_s(f21, f0, f1);
            mov_s(f12, f21);
            jal(ctx, 0x3DF9B4u, gen::fn_cosf_0052e6d8);
            v0 = 0x43E80000;
            mtc1(v0, f1);
            mul_s(f20, f1, f0);
            mov_s(f12, f21);
            jal(ctx, 0x3DF9D0u, gen::fn_sinf_0052e878);
            v0 = 0x43E80000;
            mtc1(v0, f1);
            mul_s(f1, f1, f0);
            v0 = 0x43A00000;
            mtc1(v0, f0);
            add_s(f0, f0, f20);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sh(v0, s1, shop::kElemX);
            v0 = 0x43FC0000;
            mtc1(v0, f0);
            sub_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sh(v0, s1, shop::kElemY);
            lh(a0, s1, shop::kElemAlpha0);
            lhu(v1, s1, shop::kElemFrame);
            lh(v0, s1, shop::kElemAlpha1);
            v0 = subu(v0, a0);
            mult(v1, v1, v0);
            lhu(v0, s1, shop::kElemFrames);
            div(v1, v0);
            mflo(v0);
            v0 = addu(a0, v0);
            sh(v0, s1, shop::kElemAlpha);
            lhu(v1, s1, shop::kElemFrame);
            lhu(v0, s1, shop::kElemFrames);
            v0 = slt(v1, v0);
            if (v0 == 0) {
                // 0x003dfa64
                charge(ctx, 14);
                lh(v0, s1, shop::kElemX1);
                sh(v0, s1, shop::kElemX);
                lh(v0, s1, shop::kElemY1);
                sh(v0, s1, shop::kElemY);
                lh(v0, s1, shop::kElemScale1);
                sh(v0, s1, shop::kElemScale);
                lh(v0, s1, shop::kElemAlpha1);
                sh(v0, s1, shop::kElemAlpha);
                sh(zero, s1, shop::kElemFrame);
                v0 = 6;
                sw(v0, s1, shop::kElemState);
                lw(v0, s1, shop::kElemFlags);
                v0 = v0 | 0x4;
                sw(v0, s1, shop::kElemFlags);
            }
            break;
        case 0x3DF89Cu:  // table[5]: state 5 -- the arc
            goto L_003df89c;
        case 0x3DFA9Cu:  // table[0, 6]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    }
    // 0x003dfa9c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = 0;
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003DFAC0 sub_3DFAC0 -- 28 bytes; leaf frame (no stack)
// [fclListCursorRecordWord] $a0 a holder whose +0 is an nm list: returns the first word of the record the list
// cursor's row points to (**(cursor->payload + 28)); the fusion menus read their selected row's id with it.
void sub_3DFAC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x003dfac0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v0, a0, 0);
    lw(v0, v0, 12);
    lw(v0, v0, 20);
    lw(v0, v0, 28);
    lw(v0, v0, 0);
}

// 0x003DFAE0 sub_3DFAE0 -- 968 bytes; frame 0xA0: ra sp+0x90, s6 sp+0x80 (sq), s5 sp+0x70 (sq), s4 sp+0x60 (sq), s3 sp+0x50 (sq), s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq), f25 sp+0x14, f24 sp+0x10, f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [fclCombineElementDraw] The fusion list element drawer (only caller: fusion's sub_3DEDA0): $a0 the holder, $a1 the
// element. The cursor element (holder's list cursor == element) gets the highlight frame (sprite 2), an arrow that
// orbits by the element's angle (two cos / sin products, radius 41 / 42 or 68 / 36 for row kind 6) unless element
// flag 2, the row plate (sprite 6) and, except for kinds 6 / 7, the label (sprite 7); other elements draw sprites 2,
// 3 and 5. All through sub_40E3F0 (the scaled sprite draw of the current sprite bank), at the element's x / y /
// alpha.
void sub_3DFAE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23}, f24{ctx, 24}, f25{ctx, 25};
    // 0x003dfae0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x90);
    sq(s6, sp, 0x80);
    sq(s5, sp, 0x70);
    sq(s4, sp, 0x60);
    sq(s3, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    swc1(f25, sp, 0x14);
    swc1(f24, sp, 0x10);
    swc1(f23, sp, 0xC);
    swc1(f22, sp, 0x8);
    swc1(f21, sp, 0x4);
    swc1(f20, sp, 0x0);
    s6 = a1;
    v0 = 0x3F800000;
    mtc1(v0, f21);
    s2 = 0;
    lw(s5, a1, 16);
    lw(v0, a0, 0);
    lw(v1, v0, 12);
    lw(v0, a1, 0);
    if (v1 == v0) {
        // 0x003dfb44
        charge(ctx, 2);
        s2 = 1;
        lwc1(f21, gp, -31988);  // 0x7CAFFC
    }
    // 0x003dfb4c
    charge(ctx, 8);
    lh(s4, s6, shop::kElemX);
    lh(s3, s6, shop::kElemY);
    lh(s1, s6, shop::kElemAlpha);
    lh(v0, s6, shop::kElemScale);
    v0 = addiu(v0, -90);
    s0 = subu(0, v0);
    if (s2 == 0) {
        // 0x003dfd9c
        charge(ctx, 50);
        mtc1(s0, f0);
        cvt_s_w(f13, f0);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = s4;
        a1 = s3;
        a3 = 2;
        t0 = s2;
        t1 = 38;
        t2 = 0;
        mov_s(f15, f14);
        jal(ctx, 0x3DFDD4u, gen::fn_sub_40E3F0_0040e3f0);
        v0 = addiu(s5, -1);
        s5 = sll(v0, 1);
        mtc1(s0, f0);
        cvt_s_w(f13, f0);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        t0 = addu(s5, s2);
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = s4;
        a1 = s3;
        a3 = 3;
        t1 = 34;
        t2 = 0;
        mov_s(f15, f14);
        jal(ctx, 0x3DFE1Cu, gen::fn_sub_40E3F0_0040e3f0);
        mtc1(s0, f0);
        cvt_s_w(f13, f0);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        a3 = addiu(s2, 5);
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = s4;
        a1 = s3;
        t0 = s5;
        t1 = 29;
        t2 = si(-79);
        mov_s(f15, f14);
        jal(ctx, 0x3DFE5Cu, gen::fn_sub_40E3F0_0040e3f0);
    } else {
        // 0x003dfb6c
        charge(ctx, 20);
        mtc1(s0, f0);
        cvt_s_w(f13, f0);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = s4;
        a1 = s3;
        a3 = 2;
        t0 = s2;
        t1 = 38;
        t2 = 0;
        mov_s(f15, f14);
        jal(ctx, 0x3DFBA4u, gen::fn_sub_40E3F0_0040e3f0);
        lw(v0, s6, shop::kElemFlags);
        v0 = v0 & 0x2;
        if (v0 == 0) {
            // 0x003dfbbc
            charge(ctx, 3);
            v0 = 6;
            if (s5 != v0) {
                // 0x003dfc00
                charge(ctx, 12);
                v0 = lui(0xC208);
                mtc1(v0, f0);
                mul_s(f20, f0, f21);
                v0 = 0x42240000;
                mtc1(v0, f2);
                v0 = 0x42280000;
                mtc1(v0, f1);
                mtc1(zero, f0);
                adda_s(f0, f1);
                msub_s(f24, f2, f21);
            } else {
                // 0x003dfbc8
                charge(ctx, 14);
                v0 = 0x42880000;
                mtc1(v0, f2);
                v0 = 0x42100000;
                mtc1(v0, f1);
                mtc1(zero, f0);
                adda_s(f0, f1);
                msub_s(f20, f2, f21);
                v0 = lui(0xC000);
                mtc1(v0, f0);
                sub_s(f24, f0, f21);
            }
            // 0x003dfc30
            charge(ctx, 51);
            v0 = subu(0, s0);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, gp, -32220);  // 0x7CAF14
            mul_s(f25, f0, f1);
            mov_s(f12, f25);
            jal(ctx, 0x3DFC4Cu, gen::fn_cosf_0052e6d8);
            mov_s(f22, f0);
            mov_s(f12, f25);
            jal(ctx, 0x3DFC5Cu, gen::fn_sinf_0052e878);
            mula_s(f24, f0);
            madd_s(f23, f20, f22);
            mov_s(f12, f25);
            jal(ctx, 0x3DFC70u, gen::fn_sinf_0052e878);
            mov_s(f22, f0);
            neg_s(f20, f20);
            mov_s(f12, f25);
            jal(ctx, 0x3DFC84u, gen::fn_cosf_0052e6d8);
            mula_s(f24, f0);
            mtc1(zero, f12);
            madd_s(f1, f20, f22);
            mtc1(s4, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f23);
            cvt_w_s(f0, f0);
            mfc1(a0, f0);
            mtc1(s3, f0);
            cvt_s_w(f0, f0);
            add_s(f0, f0, f1);
            cvt_w_s(f0, f0);
            mfc1(a1, f0);
            mtc1(s0, f0);
            cvt_s_w(f13, f0);
            a2 = s1 & 0xFF;
            v0 = addiu(s5, -1);
            t0 = sll(v0, 1);
            a3 = 4;
            t1 = 0;
            t2 = 0;
            mov_s(f14, f21);
            mov_s(f15, f21);
            jal(ctx, 0x3DFCF4u, gen::fn_sub_40E3F0_0040e3f0);
        }
        // 0x003dfcfc
        charge(ctx, 20);
        mtc1(s0, f0);
        cvt_s_w(f13, f0);
        mtc1(zero, f12);
        a2 = s1 & 0xFF;
        v0 = addiu(s5, -1);
        t0 = sll(v0, 1);
        v0 = 0x3F800000;
        mtc1(v0, f14);
        a0 = s4;
        a1 = s3;
        a3 = 6;
        t1 = 50;
        t2 = si(-96);
        mov_s(f15, f14);
        jal(ctx, 0x3DFD38u, gen::fn_sub_40E3F0_0040e3f0);
        v1 = 6;
        if (s5 != v1) {
            // 0x003dfd4c
            charge(ctx, 3);
            a3 = 7;
            if (s5 != a3) {
                // 0x003dfd58
                charge(ctx, 17);
                mtc1(s0, f0);
                cvt_s_w(f13, f0);
                mtc1(zero, f12);
                a2 = s1 & 0xFF;
                v0 = 0x3F800000;
                mtc1(v0, f14);
                a0 = s4;
                a1 = s3;
                t0 = 0;
                t1 = 50;
                t2 = si(-113);
                mov_s(f15, f14);
                jal(ctx, 0x3DFD8Cu, gen::fn_sub_40E3F0_0040e3f0);
            }
        }
    }
    // 0x003dfe64 (the shared epilogue, written out on this path)
    charge(ctx, 17);
    ld(ra, sp, 0x90);
    lq(s6, sp, 0x80);
    lq(s5, sp, 0x70);
    lq(s4, sp, 0x60);
    lq(s3, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    lwc1(f25, sp, 0x14);
    lwc1(f24, sp, 0x10);
    lwc1(f23, sp, 0xC);
    lwc1(f22, sp, 0x8);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x003DFEB0 sub_3DFEB0 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclElementSetCreate] Creates an element set: an nm list (sub_3C44D0) with 8-byte payloads and the node callback
// sub_3DF4A0; the list object's payload (+36) gets {the list, $a0 the owner}; returns that payload (the set).
void sub_3DFEB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003dfeb0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 8;
    a1 = 0;
    a2 = 0;
    a3 = 0x3E0000;
    a3 = addiu(a3, -2912);  // &sub_3DF4A0
    jal(ctx, 0x3DFED4u, gen::fn_sub_3C44D0_003c44d0);
    lw(v1, v0, 36);
    sw(v0, v1, 0);
    sw(s0, v1, 4);
    v0 = v1;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003DFF00 sub_3DFF00 -- 44 bytes; frame 0x10: ra sp+0x0
// [fclElementSetDestroy] Destroys the set's nm list (sub_3C45F0) when $a0 is not null.
void sub_3DFF00(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003dff00
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x003dff10
        charge(ctx, 3);
        lw(a0, a0, 0);
        jal(ctx, 0x3DFF14u, gen::fn_sub_3C45F0_003c45f0);
    }
    // 0x003dff1c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003DFF30 sub_3DFF30 -- 72 bytes; leaf frame (no stack)
// [fclElementSetAllDone] 1 when every element of the set has flag 4 (idle / done), else 0.
void sub_3DFF30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003dff30
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 0);
    lw(v1, v0, 4);
    for (;;) {
        // 0x003dff64
        charge(ctx, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003dff40
        charge(ctx, 5);
        lw(v0, v1, 20);
        lw(v0, v0, 8);
        v0 = v0 & 0x4;
        if (v0 == 0) {
            goto L_003dff54_2;
        }
        // 0x003dff60
        charge(ctx, 1);
        lw(v1, v1, 16);
    }
    // 0x003dff6c
    charge(ctx, 1);
    v0 = 1;
    // 0x003dff70 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_003dff54_2:
    charge(ctx, 3);
    v0 = 0;
    // 0x003dff70 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003DFF80 sub_3DFF80 -- 64 bytes; leaf frame (no stack)
// [fclElementSetFind] The element whose id (+16) is $a1, or 0.
void sub_3DFF80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x003dff80
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 0);
    lw(a0, v0, 4);
    for (;;) {
        // 0x003dffac
        charge(ctx, 2);
        if (a0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003dff90
        charge(ctx, 4);
        lw(v0, a0, 20);
        lw(v1, v0, 16);
        if (v1 == a1) {
            goto L_003dffa0_2;
        }
        // 0x003dffa8
        charge(ctx, 1);
        lw(a0, a0, 16);
    }
    // 0x003dffb4
    charge(ctx, 1);
    v0 = 0;
    // 0x003dffb8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_003dffa0_2:
    charge(ctx, 2);
    // 0x003dffb8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003DFFC0 sub_3DFFC0 -- 188 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclElementSetStart] Finds the element with id $a1 or appends a new node (nmListAppendNew; element +4 = the node,
// +52 = +56 when $a2 asks for the extra area, state 0, flag 4; the id is not stored here: the caller's descriptor,
// sub_3DF100, sets it); then starts it: state 1, flag 4 cleared. Returns the element.
void sub_3DFFC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003dffc0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a2;
    lw(a0, a0, 0);
    lw(v1, a0, 4);
    for (;;) {
        // 0x003dfffc
        charge(ctx, 2);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003dffe0
        charge(ctx, 4);
        lw(a2, v1, 20);
        lw(v0, a2, 16);
        if (v0 == a1) {
            goto L_003dfff0_2;
        }
        // 0x003dfff8
        charge(ctx, 1);
        lw(v1, v1, 16);
    }
    // 0x003e0004
    charge(ctx, 1);
    a2 = 0;
L_003e0008:
    charge(ctx, 2);
    if (a2 == 0) {
        // 0x003e0010
        charge(ctx, 9);
        lhu(v0, a0, 16);
        a1 = addiu(v0, 1);
        a2 = addiu(s0, 56);
        jal(ctx, 0x3E001Cu, gen::fn_nmListAppendNew_003c4910);
        lw(a2, v0, 20);
        sw(v0, a2, 4);
        if (s0 != 0) {
            // 0x003e0034
            charge(ctx, 2);
            v0 = addiu(a2, 56);
            sw(v0, a2, 52);
        }
        // 0x003e003c
        charge(ctx, 4);
        sw(zero, a2, 12);
        lw(v0, a2, 8);
        v0 = v0 | 0x4;
        sw(v0, a2, 8);
    }
    // 0x003e004c (the shared epilogue, written out on this path)
    charge(ctx, 12);
    v0 = 1;
    sw(v0, a2, 12);
    lw(v1, a2, 8);
    v0 = si(-5);
    v0 = v1 & v0;
    sw(v0, a2, 8);
    v0 = a2;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    return;
L_003dfff0_2:
    charge(ctx, 2);
    goto L_003e0008;
}

// 0x003E0080 sub_3E0080 -- 476 bytes; frame 0x4E0: ra sp+0x0
// [fclElementTemplate22] Copies the 22-id template table 0x6A6040 (two 28-byte records per id: in / out) to the stack
// (154 doublewords), stamps the id and the s16 $a3 into every record, and copies record [$a1][$a2] to $a0 (memcpy, 28
// bytes). The only caller is sub_3E0260.
void sub_3E0080(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e0080
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x4E0);
    sd(ra, sp, 0x0);
    t2 = 0x6A0000;
    t2 = addiu(t2, 24640);  // &0x6A6040
    t1 = addiu(sp, 0x10);
    t0 = 154;
    for (;;) {
        // 0x003e0098
        charge(ctx, 9);
        lw(v1, t2, 0);
        lw(v0, t2, 4);
        t2 = addiu(t2, 8);
        t0 = addiu(t0, -1);
        sw(v1, t1, 0);
        sw(v0, t1, 4);
        t1 = addiu(t1, 8);
        if (i64(t0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003e00bc
    charge(ctx, 104);
    sw(a1, sp, 0x10);
    sh(a3, sp, 0x28);
    sw(a1, sp, 0x2C);
    sh(a3, sp, 0x44);
    sw(a1, sp, 0x48);
    sh(a3, sp, 0x60);
    sw(a1, sp, 0x64);
    sh(a3, sp, 0x7C);
    sw(a1, sp, 0x80);
    sh(a3, sp, 0x98);
    sw(a1, sp, 0x9C);
    sh(a3, sp, 0xB4);
    sw(a1, sp, 0xB8);
    sh(a3, sp, 0xD0);
    sw(a1, sp, 0xD4);
    sh(a3, sp, 0xEC);
    sw(a1, sp, 0xF0);
    sh(a3, sp, 0x108);
    sw(a1, sp, 0x10C);
    sh(a3, sp, 0x124);
    sw(a1, sp, 0x128);
    sh(a3, sp, 0x140);
    sw(a1, sp, 0x144);
    sh(a3, sp, 0x15C);
    sw(a1, sp, 0x160);
    sh(a3, sp, 0x178);
    sw(a1, sp, 0x17C);
    sh(a3, sp, 0x194);
    sw(a1, sp, 0x198);
    sh(a3, sp, 0x1B0);
    sw(a1, sp, 0x1B4);
    sh(a3, sp, 0x1CC);
    sw(a1, sp, 0x1D0);
    sh(a3, sp, 0x1E8);
    sw(a1, sp, 0x1EC);
    sh(a3, sp, 0x204);
    sw(a1, sp, 0x208);
    sh(a3, sp, 0x220);
    sw(a1, sp, 0x224);
    sh(a3, sp, 0x23C);
    sw(a1, sp, 0x240);
    sh(a3, sp, 0x258);
    sw(a1, sp, 0x25C);
    sh(a3, sp, 0x274);
    sw(a1, sp, 0x278);
    sh(a3, sp, 0x290);
    sw(a1, sp, 0x294);
    sh(a3, sp, 0x2AC);
    sw(a1, sp, 0x2B0);
    sh(a3, sp, 0x2C8);
    sw(a1, sp, 0x2CC);
    sh(a3, sp, 0x2E4);
    sw(a1, sp, 0x2E8);
    sh(a3, sp, 0x300);
    sw(a1, sp, 0x304);
    sh(a3, sp, 0x31C);
    sw(a1, sp, 0x320);
    sh(a3, sp, 0x338);
    sw(a1, sp, 0x33C);
    sh(a3, sp, 0x354);
    sw(a1, sp, 0x358);
    sh(a3, sp, 0x370);
    sw(a1, sp, 0x374);
    sh(a3, sp, 0x38C);
    sw(a1, sp, 0x390);
    sh(a3, sp, 0x3A8);
    sw(a1, sp, 0x3AC);
    sh(a3, sp, 0x3C4);
    sw(a1, sp, 0x3C8);
    sh(a3, sp, 0x3E0);
    sw(a1, sp, 0x3E4);
    sh(a3, sp, 0x3FC);
    sw(a1, sp, 0x400);
    sh(a3, sp, 0x418);
    sw(a1, sp, 0x41C);
    sh(a3, sp, 0x434);
    sw(a1, sp, 0x438);
    sh(a3, sp, 0x450);
    sw(a1, sp, 0x454);
    sh(a3, sp, 0x46C);
    sw(a1, sp, 0x470);
    sh(a3, sp, 0x488);
    sw(a1, sp, 0x48C);
    sh(a3, sp, 0x4A4);
    sw(a1, sp, 0x4A8);
    sh(a3, sp, 0x4C0);
    sw(a1, sp, 0x4C4);
    sh(a3, sp, 0x4DC);
    v0 = sll(a1, 3);
    v0 = subu(v0, a1);
    v0 = sll(v0, 3);
    v1 = addu(v0, sp);
    v0 = sll(a2, 3);
    v0 = subu(v0, a2);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    a1 = addiu(v0, 16);
    a2 = 28;
    jal(ctx, 0x3E0244u, gen::fn_memcpy_00521250);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x4E0);
}

// 0x003E0260 sub_3E0260 -- 208 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclElementStartTemplate22] Builds a descriptor from table 0x6A6040 (sub_3E0080) on the stack, finds or appends the
// element $a1 in set $a0 (the inline copy of sub_3DFFC0), starts it and applies the descriptor (fusion's sub_3DF100).
// Returns the element. Caller: fusion's sub_3D8850.
void sub_3E0260(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e0260
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s0 = a1;
    a0 = addiu(sp, 0x40);
    jal(ctx, 0x3E0280u, gen::fn_sub_3E0080_003e0080);
    lw(s1, sp, 0x44);
    a0 = s2;
    a1 = s0;
    jal(ctx, 0x3E0294u, gen::fn_sub_3DFF80_003dff80);
    s0 = v0;
    if (s0 == 0) {
        // 0x003e02a8
        charge(ctx, 10);
        lw(a0, s2, 0);
        lhu(v0, a0, 16);
        a1 = addiu(v0, 1);
        a2 = addiu(s1, 56);
        jal(ctx, 0x3E02B8u, gen::fn_nmListAppendNew_003c4910);
        lw(s0, v0, 20);
        sw(v0, s0, 4);
        if (s1 != 0) {
            // 0x003e02d0
            charge(ctx, 2);
            v0 = addiu(s0, 56);
            sw(v0, s0, 52);
        }
        // 0x003e02d8
        charge(ctx, 4);
        sw(zero, s0, 12);
        lw(v0, s0, 8);
        v0 = v0 | 0x4;
        sw(v0, s0, 8);
    }
    // 0x003e02e8
    charge(ctx, 18);
    v0 = 1;
    sw(v0, s0, 12);
    lw(v1, s0, 8);
    v0 = si(-5);
    v0 = v1 & v0;
    sw(v0, s0, 8);
    a0 = s0;
    a1 = addiu(sp, 0x40);
    jal(ctx, 0x3E0308u, gen::fn_sub_3DF100_003df100);
    v0 = s0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003E0330 sub_3E0330 -- 428 bytes; frame 0x220: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclElementStartTemplate8] As sub_3E0260 with the 8-id table 0x6A6510 copied inline (56 doublewords): record
// [$a1][$a2], id / $a3 stamped, then find-or-append, start and sub_3DF100. Caller: fusion's sub_3D9820.
void sub_3E0330(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e0330
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x220);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    t0 = 0x6A0000;
    t0 = addiu(t0, 25872);  // &0x6A6510
    a1 = addiu(sp, 0x40);
    a0 = 56;
    for (;;) {
        // 0x003e035c
        charge(ctx, 9);
        lw(v1, t0, 0);
        lw(v0, t0, 4);
        t0 = addiu(t0, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003e0380
    charge(ctx, 53);
    sw(s0, sp, 0x40);
    sh(a3, sp, 0x58);
    sw(s0, sp, 0x5C);
    sh(a3, sp, 0x74);
    sw(s0, sp, 0x78);
    sh(a3, sp, 0x90);
    sw(s0, sp, 0x94);
    sh(a3, sp, 0xAC);
    sw(s0, sp, 0xB0);
    sh(a3, sp, 0xC8);
    sw(s0, sp, 0xCC);
    sh(a3, sp, 0xE4);
    sw(s0, sp, 0xE8);
    sh(a3, sp, 0x100);
    sw(s0, sp, 0x104);
    sh(a3, sp, 0x11C);
    sw(s0, sp, 0x120);
    sh(a3, sp, 0x138);
    sw(s0, sp, 0x13C);
    sh(a3, sp, 0x154);
    sw(s0, sp, 0x158);
    sh(a3, sp, 0x170);
    sw(s0, sp, 0x174);
    sh(a3, sp, 0x18C);
    sw(s0, sp, 0x190);
    sh(a3, sp, 0x1A8);
    sw(s0, sp, 0x1AC);
    sh(a3, sp, 0x1C4);
    sw(s0, sp, 0x1C8);
    sh(a3, sp, 0x1E0);
    sw(s0, sp, 0x1E4);
    sh(a3, sp, 0x1FC);
    v0 = sll(s0, 3);
    v0 = subu(v0, s0);
    v0 = sll(v0, 3);
    v1 = addu(v0, sp);
    v0 = sll(a2, 3);
    v0 = subu(v0, a2);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    a0 = addiu(sp, 0x200);
    a1 = addiu(v0, 64);
    a2 = 28;
    jal(ctx, 0x3E042Cu, gen::fn_memcpy_00521250);
    lw(s2, sp, 0x204);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x3E0440u, gen::fn_sub_3DFF80_003dff80);
    s0 = v0;
    if (s0 == 0) {
        // 0x003e0454
        charge(ctx, 10);
        lw(a0, s1, 0);
        lhu(v0, a0, 16);
        a1 = addiu(v0, 1);
        a2 = addiu(s2, 56);
        jal(ctx, 0x3E0464u, gen::fn_nmListAppendNew_003c4910);
        lw(s0, v0, 20);
        sw(v0, s0, 4);
        if (s2 != 0) {
            // 0x003e047c
            charge(ctx, 2);
            v0 = addiu(s0, 56);
            sw(v0, s0, 52);
        }
        // 0x003e0484
        charge(ctx, 4);
        sw(zero, s0, 12);
        lw(v0, s0, 8);
        v0 = v0 | 0x4;
        sw(v0, s0, 8);
    }
    // 0x003e0494
    charge(ctx, 18);
    v0 = 1;
    sw(v0, s0, 12);
    lw(v1, s0, 8);
    v0 = si(-5);
    v0 = v1 & v0;
    sw(v0, s0, 8);
    a0 = s0;
    a1 = addiu(sp, 0x200);
    jal(ctx, 0x3E04B4u, gen::fn_sub_3DF100_003df100);
    v0 = s0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x220);
}

// 0x003E04E0 sub_3E04E0 -- 364 bytes; frame 0x140: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclElementStartTemplate4] As sub_3E0330 with the 4-id table 0x6A66D0 (28 doublewords). Callers: the shop's
// sub_3FD8E0 / sub_3FD990.
void sub_3E04E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e04e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    t0 = 0x6A0000;
    t0 = addiu(t0, 26320);  // &0x6A66D0
    a1 = addiu(sp, 0x40);
    a0 = 28;
    for (;;) {
        // 0x003e050c
        charge(ctx, 9);
        lw(v1, t0, 0);
        lw(v0, t0, 4);
        t0 = addiu(t0, 8);
        a0 = addiu(a0, -1);
        sw(v1, a1, 0);
        sw(v0, a1, 4);
        a1 = addiu(a1, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003e0530
    charge(ctx, 37);
    sw(s0, sp, 0x40);
    sh(a3, sp, 0x58);
    sw(s0, sp, 0x5C);
    sh(a3, sp, 0x74);
    sw(s0, sp, 0x78);
    sh(a3, sp, 0x90);
    sw(s0, sp, 0x94);
    sh(a3, sp, 0xAC);
    sw(s0, sp, 0xB0);
    sh(a3, sp, 0xC8);
    sw(s0, sp, 0xCC);
    sh(a3, sp, 0xE4);
    sw(s0, sp, 0xE8);
    sh(a3, sp, 0x100);
    sw(s0, sp, 0x104);
    sh(a3, sp, 0x11C);
    v0 = sll(s0, 3);
    v0 = subu(v0, s0);
    v0 = sll(v0, 3);
    v1 = addu(v0, sp);
    v0 = sll(a2, 3);
    v0 = subu(v0, a2);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    a0 = addiu(sp, 0x120);
    a1 = addiu(v0, 64);
    a2 = 28;
    jal(ctx, 0x3E059Cu, gen::fn_memcpy_00521250);
    lw(s2, sp, 0x124);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x3E05B0u, gen::fn_sub_3DFF80_003dff80);
    s0 = v0;
    if (s0 == 0) {
        // 0x003e05c4
        charge(ctx, 10);
        lw(a0, s1, 0);
        lhu(v0, a0, 16);
        a1 = addiu(v0, 1);
        a2 = addiu(s2, 56);
        jal(ctx, 0x3E05D4u, gen::fn_nmListAppendNew_003c4910);
        lw(s0, v0, 20);
        sw(v0, s0, 4);
        if (s2 != 0) {
            // 0x003e05ec
            charge(ctx, 2);
            v0 = addiu(s0, 56);
            sw(v0, s0, 52);
        }
        // 0x003e05f4
        charge(ctx, 4);
        sw(zero, s0, 12);
        lw(v0, s0, 8);
        v0 = v0 | 0x4;
        sw(v0, s0, 8);
    }
    // 0x003e0604
    charge(ctx, 18);
    v0 = 1;
    sw(v0, s0, 12);
    lw(v1, s0, 8);
    v0 = si(-5);
    v0 = v1 & v0;
    sw(v0, s0, 8);
    a0 = s0;
    a1 = addiu(sp, 0x120);
    jal(ctx, 0x3E0624u, gen::fn_sub_3DF100_003df100);
    v0 = s0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x140);
}

// 0x003E0650 sub_3E0650 -- 40 bytes; frame 0x10: ra sp+0x0
// [fclElementSetUpdate] One frame of a set: nmListRemoveFiltered over its list (the node callback sub_3DF4A0 animates
// each element). Returns 0.
void sub_3E0650(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e0650
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 0);
    jal(ctx, 0x3E065Cu, gen::fn_nmListRemoveFiltered_003c4e70);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003E0680 sub_3E0680 -- 116 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclElementSetForEach] Calls $a1(set, element, $a2) through jalr for every node of the set, in list order (the draw
// tasks pass their element drawers).
void sub_3E0680(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e0680
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    lw(v1, a0, 0);
    lw(s0, v1, 4);
    for (;;) {
        // 0x003e06cc
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003e06b4
        charge(ctx, 6);
        a0 = s3;
        lw(a1, s0, 20);
        a2 = s1;
        jalr(ctx, 0x3E06C0u, s2.u());
        lw(s0, s0, 16);
    }
    // 0x003e06d4
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003E0700 sub_3E0700 -- 120 bytes; frame 0x20: ra sp+0x0
// [fclShopStart] $a0 the shop type: types 0, 1, 2 and 4 go through the sequence manager (adminiChangeSeq(7, &type, 4,
// 0): sequence 7 is the shop, the type its 4-byte parameter, which later calls fclShop_CreateShopDrawTasks); the
// others (3, 5, 6, 8) create the shop directly. Caller: the COMM handler sub_40D410.
void sub_3E0700(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e0700
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x0);
    sw(a0, sp, 0x1C);
    v0 = 4;
    if (a0 != v0) {
        // 0x003e0718
        charge(ctx, 3);
        v0 = 2;
        if (a0 == v0) {
            goto L_003e0740;
        }
        // 0x003e0724
        charge(ctx, 3);
        v0 = 1;
        if (a0 == v0) {
            goto L_003e0740;
        }
        // 0x003e0730
        charge(ctx, 2);
        if (a0 == 0) {
            goto L_003e0740;
        }
        // 0x003e0738
        charge(ctx, 2);
        // 0x003e0760
        charge(ctx, 2);
        jal(ctx, 0x3E0760u, gen::fn_fclShop_CreateShopDrawTasks_003e0780);
        // 0x003e0768 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_003e0740:
    charge(ctx, 8);
    a0 = 7;
    a1 = addiu(sp, 0x1C);
    a2 = 4;
    a3 = 0;
    jal(ctx, 0x3E0750u, gen::fn_adminiChangeSeq_0027c080);
    // 0x003e0768 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003E0780 fclShop_CreateShopDrawTasks -- 176 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Creates the shop: the sequence and its work record (sub_3E0950, $a0 the type), then the task "fclShop" (priority
// 10, update sub_3E0830; kept in work +128) with its children "fclShopDraw" (6326, fclShop_UpdateShopDrawTask) and
// "fclShopDraw2" (4207, fclShop_UpdateShopDraw2Task). Returns the last task.
void fclShop_CreateShopDrawTasks(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e0780
    enter(ctx, 44);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3E078Cu, gen::fn_sub_3E0950_003e0950);
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    jal(ctx, 0x3E0798u, gen::fn_nmObjPayloadWord12_003c5460);
    s0 = v0;
    a0 = 0;
    a1 = addiu(gp, -21816);  // "fclShop"
    a2 = 10;
    a3 = 0x3E0000;
    a3 = addiu(a3, 2096);  // &sub_3E0830
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x3E07C0u, gen::fn_kwlnTaskCreate_00194b20);
    sw(v0, s0, shop::kShopTask);
    a0 = v0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 27352);  // "fclShopDraw"
    a2 = 6326;
    a3 = 0x3E0000;
    a3 = addiu(a3, 2160);  // &fclShop_UpdateShopDrawTask
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x3E07ECu, gen::fn_kwlnTaskCreate_00194b20);
    a0 = v0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 27368);  // "fclShopDraw2"
    a2 = 4207;
    a3 = 0x3E0000;
    a3 = addiu(a3, 2272);  // &fclShop_UpdateShopDraw2Task
    t0 = 0;
    t1 = 0;
    jal(ctx, 0x3E0814u, gen::fn_kwlnTaskCreate_00194b20);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003E0830 sub_3E0830 -- 56 bytes; frame 0x10: ra sp+0x0
// [fclShop_UpdateShopTask] The "fclShop" task: -1 (the task ends) once sub_3E0BC0 has torn the finished sequence
// down, else 0.
void sub_3E0830(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e0830
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3E0838u, gen::fn_sub_3E0BC0_003e0bc0);
    if (v0 == 0) {
        // 0x003e0854
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003e0848
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x003e0858 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003E0870 fclShop_UpdateShopDrawTask -- 112 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// The "fclShopDraw" task: the steps' draw callbacks (sub_3E6D40), then every shop element through sub_3E6400 with
// work flag 0x20 set (the high layer), the flag cleared afterwards. Returns 0.
void fclShop_UpdateShopDrawTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e0870
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    jal(ctx, 0x3E0880u, gen::fn_nmObjPayloadWord12_003c5460);
    s0 = v0;
    jal(ctx, 0x3E088Cu, gen::fn_sub_3E6D40_003e6d40);
    lw(v0, s0, shop::kShopFlags);
    v0 = v0 | 0x20;
    sw(v0, s0, shop::kShopFlags);
    lw(a0, s0, shop::kShopElements);
    a1 = 0x3E0000;
    a1 = addiu(a1, 25600);  // &sub_3E6400
    a2 = 0;
    jal(ctx, 0x3E08B0u, gen::fn_sub_3E0680_003e0680);
    lw(v1, s0, shop::kShopFlags);
    v0 = si(-33);
    v0 = v1 & v0;
    sw(v0, s0, shop::kShopFlags);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003E08E0 fclShop_UpdateShopDraw2Task -- 64 bytes; frame 0x10: ra sp+0x0
// The "fclShopDraw2" task: every shop element through sub_3E6400 without flag 0x20 (the low layer). Returns 0.
void fclShop_UpdateShopDraw2Task(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e08e0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    jal(ctx, 0x3E08ECu, gen::fn_nmObjPayloadWord12_003c5460);
    lw(a0, v0, 152);
    a1 = 0x3E0000;
    a1 = addiu(a1, 25600);  // &sub_3E6400
    a2 = 0;
    jal(ctx, 0x3E0904u, gen::fn_sub_3E0680_003e0680);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003E0920 sub_3E0920 -- 32 bytes; frame 0x10: ra sp+0x0
// [fclShopIsOpen] sub_3E0BB0: 1 while the shop sequence exists. Callers: the sequence table's 0x27CB50, the COMM wait
// handler sub_40D490.
void sub_3E0920(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x003e0920
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3E0928u, gen::fn_sub_3E0BB0_003e0bb0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003E0950 sub_3E0950 -- 188 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopCreateSequence] When no shop is open: nmSequenceCreate(root sub_3E6E80, 156-byte work), stores it in
// 0x7CE688, sets the work's type ($a0), its element set (sub_3DFEB0, +152) and state 1, then logs "[fclShop.c:425]"
// and "SHOP TYPE%d" through printf and sub_1052B0.
void sub_3E0950(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e0950
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v1, gp, -18024);  // 0x7CE688: the shop sequence
    if (v1 == 0) {
        // 0x003e0970
        charge(ctx, 33);
        a0 = 0x3E0000;
        a0 = addiu(a0, 28288);  // &sub_3E6E80
        a1 = 156;
        jal(ctx, 0x3E097Cu, gen::fn_nmSequenceCreate_003c5180);
        sw(v0, gp, -18024);  // 0x7CE688: the shop sequence
        a0 = v0;
        jal(ctx, 0x3E098Cu, gen::fn_nmObjPayloadWord12_003c5460);
        s0 = v0;
        sw(s1, v0, 0);
        a0 = s0;
        jal(ctx, 0x3E09A0u, gen::fn_sub_3DFEB0_003dfeb0);
        sw(v0, s0, shop::kShopElements);
        v0 = 1;
        sw(v0, s0, shop::kShopState);
        a0 = addiu(gp, -21808);  // "[%s:%d]"
        a1 = 0x6A0000;
        a1 = addiu(a1, 27384);  // "fclShop.c"
        a2 = 425;
        jal(ctx, 0x3E09C4u, gen::fn_printf_005225a8);
        a0 = 0x6A0000;
        a0 = addiu(a0, 27400);  // "SHOP TYPE%d\n"
        a1 = s1;
        jal(ctx, 0x3E09D8u, gen::fn_printf_005225a8);
        a0 = 0x6A0000;
        a0 = addiu(a0, 27400);  // "SHOP TYPE%d\n"
        a1 = s1;
        jal(ctx, 0x3E09ECu, gen::fn_sub_1052B0_001052b0);
    }
    // 0x003e09f4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003E0BB0 sub_3E0BB0 -- 16 bytes; leaf frame (no stack)
// [fclShopExists] 0x7CE688 != 0.
void sub_3E0BB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, gp{ctx, 28};
    // 0x003e0bb0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, gp, -18024);  // 0x7CE688: the shop sequence
    v0 = sltu(0, v0);
}

// 0x003E0BC0 sub_3E0BC0 -- 88 bytes; frame 0x10: ra sp+0x0
// [fclShopPollEnd] When the sequence reports its end (sub_3C5490): the teardown sub_3E0A10 (still recompiled),
// nmSequenceDestroy, 0x7CE688 = 0, returns 1; else 0.
void sub_3E0BC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e0bc0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    jal(ctx, 0x3E0BCCu, gen::fn_sub_3C5490_003c5490);
    if (v0 == 0) {
        // 0x003e0c04
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003e0bdc
        charge(ctx, 10);
        lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
        jal(ctx, 0x3E0BE0u, gen::fn_sub_3E0A10_003e0a10);
        lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
        jal(ctx, 0x3E0BECu, gen::fn_nmSequenceDestroy_003c5220);
        sw(zero, gp, -18024);  // 0x7CE688: the shop sequence
        v0 = 1;
    }
    // 0x003e0c08 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003E6400 sub_3E6400 -- 2356 bytes; frame 0x140: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopDrawElement] The shop's element drawer (passed to sub_3E0680 by both draw tasks): $a1 the element. Copies
// the per-type sprite tables (floats 0x6A6F10.., 0x7CD7D0, words 0x6A6F50 / 0x6A6F70) to its frame, then switches on
// the element id (+16, 18 cases): 0 the backdrop (sprite 156 for type 8, else 2) and 1 (sprite 166) in the low pass
// only; 2 / 3 the money frames with the MONEY step's yen (+8, sub_3EED50) as "%d" (sprintf, sub_40EB50) in the high
// pass; 4..16 the type-dependent labels at (+342..563, +388..409) chosen by the shop type (sub_3E6DC0) from the
// copied tables; 17 the antique shop's panel (sub_3E6130). Positions from +20 / +22, alpha from +38.
void sub_3E6400(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x003e6400
    enter(ctx, 54);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a1;
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    jal(ctx, 0x3E6420u, gen::fn_nmObjPayloadWord12_003c5460);
    v1 = 0x6A0000;
    lwc1(f2, v1, 28432);  // 0x6A6F10
    v1 = 0x6A0000;
    lwc1(f1, v1, 28436);  // 0x6A6F14
    v1 = 0x6A0000;
    lwc1(f0, v1, 28440);  // 0x6A6F18
    swc1(f2, sp, 0x130);
    swc1(f1, sp, 0x134);
    swc1(f0, sp, 0x138);
    v1 = 0x6A0000;
    lwc1(f2, v1, 28448);  // 0x6A6F20
    v1 = 0x6A0000;
    lwc1(f1, v1, 28452);  // 0x6A6F24
    v1 = 0x6A0000;
    lwc1(f0, v1, 28456);  // 0x6A6F28
    swc1(f2, sp, 0x120);
    swc1(f1, sp, 0x124);
    swc1(f0, sp, 0x128);
    v1 = 0x6A0000;
    lwc1(f2, v1, 28464);  // 0x6A6F30
    v1 = 0x6A0000;
    lwc1(f1, v1, 28468);  // 0x6A6F34
    v1 = 0x6A0000;
    lwc1(f0, v1, 28472);  // 0x6A6F38
    swc1(f2, sp, 0x110);
    swc1(f1, sp, 0x114);
    swc1(f0, sp, 0x118);
    lwc1(f1, gp, -21792);  // 0x7CD7D0
    lwc1(f0, gp, -21788);  // 0x7CD7D4
    swc1(f1, sp, 0x108);
    swc1(f0, sp, 0x10C);
    v1 = 0x6A0000;
    lwc1(f2, v1, 28480);  // 0x6A6F40
    v1 = 0x6A0000;
    lwc1(f1, v1, 28484);  // 0x6A6F44
    v1 = 0x6A0000;
    lwc1(f0, v1, 28488);  // 0x6A6F48
    swc1(f2, sp, 0xF8);
    swc1(f1, sp, 0xFC);
    swc1(f0, sp, 0x100);
    a3 = 0x6A0000;
    a3 = addiu(a3, 28496);  // &0x6A6F50
    a2 = addiu(sp, 0xE0);
    a1 = 3;
    for (;;) {
        // 0x003e64d8
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
    // 0x003e64fc
    charge(ctx, 4);
    a3 = 0x6A0000;
    a3 = addiu(a3, 28528);  // &0x6A6F70
    a2 = addiu(sp, 0x90);
    a1 = 9;
    for (;;) {
        // 0x003e650c
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
    // 0x003e6530
    charge(ctx, 22);
    v1 = addiu(sp, 0x130);
    sw(v1, sp, 0x90);
    v1 = addiu(sp, 0x120);
    sw(v1, sp, 0x98);
    v1 = addiu(sp, 0x110);
    sw(v1, sp, 0xA0);
    v1 = addiu(sp, 0x108);
    sw(v1, sp, 0xA8);
    v1 = addiu(sp, 0xF8);
    sw(v1, sp, 0xB0);
    sw(v1, sp, 0xB8);
    sw(v1, sp, 0xC0);
    sw(v1, sp, 0xC8);
    v1 = addiu(sp, 0xE0);
    sw(v1, sp, 0xD0);
    lh(s2, s3, 20);
    lh(s1, s3, 22);
    lh(s0, s3, 38);
    lw(v1, s3, 16);
    at = sltiu(v1, 18);
    if (at != 0) {
        // 0x003e6588
        charge(ctx, 7);
        a0 = 0x7C0000;
        a0 = addiu(a0, -18096);  // &0x7BB950
        v1 = sll(v1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x3E65A4u:  // table[0]: id 0 -- the backdrop (low pass)
            // 0x003e65a4
            charge(ctx, 4);
            lw(v1, v0, 8);
            v1 = v1 & 0x20;
            if (v1 == 0) {
                // 0x003e65b4
                charge(ctx, 7);
                lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
                jal(ctx, 0x3E65B8u, gen::fn_nmObjPayloadWord12_003c5460);
                lw(v1, v0, 0);
                v0 = 8;
                if (v1 == v0) {
                    // 0x003e6620
                    charge(ctx, 19);
                    v0 = 0x42C80000;
                    mtc1(v0, f12);
                    v0 = dsll32(s0, 16);
                    v0 = dsra32(v0, 16);
                    a2 = v0 & 0xFF;
                    mtc1(zero, f13);
                    v0 = 0x40200000;
                    mtc1(v0, f14);
                    a0 = s2;
                    a1 = s1;
                    a3 = 156;
                    t0 = 0;
                    t1 = 0;
                    t2 = 0;
                    mov_s(f15, f14);
                    jal(ctx, 0x3E665Cu, gen::fn_sub_40E3F0_0040e3f0);
                } else {
                    // 0x003e65d0
                    charge(ctx, 20);
                    v0 = 0x42C80000;
                    mtc1(v0, f12);
                    v0 = dsll32(s0, 16);
                    v0 = dsra32(v0, 16);
                    a2 = v0 & 0xFF;
                    mtc1(zero, f13);
                    v0 = 0x40A00000;
                    mtc1(v0, f14);
                    v0 = 0x40600000;
                    mtc1(v0, f15);
                    a0 = s2;
                    a1 = s1;
                    a3 = 2;
                    t0 = 0;
                    t1 = 0;
                    t2 = 0;
                    jal(ctx, 0x3E6610u, gen::fn_sub_40E3F0_0040e3f0);
                }
            }
            break;
        case 0x3E666Cu:  // table[1]: id 1 (low pass)
            // 0x003e666c
            charge(ctx, 4);
            lw(v1, v0, 8);
            v1 = v1 & 0x20;
            if (v1 == 0) {
                // 0x003e667c
                charge(ctx, 10);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a1 = s1;
                a3 = 166;
                t0 = 0;
                jal(ctx, 0x3E6694u, gen::fn_sub_40E3C0_0040e3c0);
            }
            break;
        case 0x3E66A4u:  // table[2]: id 2 -- money frame and yen (high pass)
            // 0x003e66a4
            charge(ctx, 4);
            lw(v1, v0, 8);
            v1 = v1 & 0x20;
            if (v1 != 0) {
                // 0x003e66b4
                charge(ctx, 44);
                s0 = dsll32(s0, 16);
                s0 = dsra32(s0, 16);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a1 = s1;
                a3 = 111;
                t0 = 0;
                jal(ctx, 0x3E66D4u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a1 = s1;
                a3 = 112;
                t0 = 0;
                jal(ctx, 0x3E66F4u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a1 = s1;
                a3 = 113;
                t0 = 0;
                jal(ctx, 0x3E6714u, gen::fn_sub_40E3C0_0040e3c0);
                jal(ctx, 0x3E671Cu, gen::fn_sub_3EED50_003eed50);
                a0 = addiu(sp, 0x70);
                a1 = addiu(gp, -21800);  // "%d"
                a2 = v0;
                jal(ctx, 0x3E6730u, gen::fn_sprintf_00523ac8);
                a0 = addiu(s2, 591);
                a1 = addiu(s1, 25);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a3 = 3;
                t0 = addiu(sp, 0x70);
                t1 = 9;
                jal(ctx, 0x3E6754u, gen::fn_sub_40EB50_0040eb50);
            }
            break;
        case 0x3E6764u:  // table[3]: id 3 -- money frame and yen (high pass)
            // 0x003e6764
            charge(ctx, 4);
            lw(v1, v0, 8);
            v1 = v1 & 0x20;
            if (v1 != 0) {
                // 0x003e6774
                charge(ctx, 60);
                s0 = dsll32(s0, 16);
                s0 = dsra32(s0, 16);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a1 = s1;
                a3 = 114;
                t0 = 0;
                jal(ctx, 0x3E6794u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a1 = s1;
                a3 = 115;
                t0 = 0;
                jal(ctx, 0x3E67B4u, gen::fn_sub_40E3C0_0040e3c0);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a1 = s1;
                a3 = 116;
                t0 = 0;
                jal(ctx, 0x3E67D4u, gen::fn_sub_40E3C0_0040e3c0);
                a1 = addiu(s1, -1);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a3 = 112;
                t0 = 0;
                jal(ctx, 0x3E67F4u, gen::fn_sub_40E3C0_0040e3c0);
                a1 = addiu(s1, -1);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a0 = s2;
                a3 = 113;
                t0 = 0;
                jal(ctx, 0x3E6814u, gen::fn_sub_40E3C0_0040e3c0);
                jal(ctx, 0x3E681Cu, gen::fn_sub_3EED50_003eed50);
                a0 = addiu(sp, 0x50);
                a1 = addiu(gp, -21800);  // "%d"
                a2 = v0;
                jal(ctx, 0x3E6830u, gen::fn_sprintf_00523ac8);
                a0 = addiu(s2, 591);
                a1 = addiu(s1, 24);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                a3 = 3;
                t0 = addiu(sp, 0x50);
                t1 = 9;
                jal(ctx, 0x3E6854u, gen::fn_sub_40EB50_0040eb50);
            }
            break;
        case 0x3E6864u:  // table[4, 6, 7, 11]
            // 0x003e6864
            charge(ctx, 4);
            lw(v1, v0, 8);
            v1 = v1 & 0x20;
            if (v1 != 0) {
                // 0x003e6874
                charge(ctx, 23);
                jal(ctx, 0x3E6874u, gen::fn_sub_3E6DC0_003e6dc0);
                v0 = sll(v0, 3);
                v0 = addu(v0, sp);
                lw(s3, v0, 144);
                a0 = addiu(s2, 495);
                a1 = addiu(s1, 409);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                lw(a3, s3, 0);
                t0 = 0;
                jal(ctx, 0x3E68A0u, gen::fn_sub_40E3C0_0040e3c0);
                a0 = addiu(s2, 563);
                a1 = addiu(s1, 409);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                lw(a3, s3, 4);
                t0 = 0;
                jal(ctx, 0x3E68C0u, gen::fn_sub_40E3C0_0040e3c0);
            }
            break;
        case 0x3E68D0u:  // table[5]
            // 0x003e68d0
            charge(ctx, 4);
            lw(v1, v0, 8);
            v1 = v1 & 0x20;
            if (v1 != 0) {
                // 0x003e68e0
                charge(ctx, 10);
                jal(ctx, 0x3E68E0u, gen::fn_sub_3E6DC0_003e6dc0);
                v0 = sll(v0, 3);
                v0 = addu(v0, sp);
                lw(s3, v0, 144);
                jal(ctx, 0x3E68F4u, gen::fn_sub_3E6DC0_003e6dc0);
                v1 = 1;
                if (v0 != v1) {
                    // 0x003e6908
                    charge(ctx, 2);
                    if (v0 == 0) {
                        goto L_003e6918;
                    }
                    // 0x003e6910
                    charge(ctx, 2);
                    // 0x003e6980
                    charge(ctx, 18);
                    a0 = addiu(s2, 495);
                    a1 = addiu(s1, 409);
                    mtc1(zero, f12);
                    a2 = s0 & 0xFF;
                    lw(a3, s3, 0);
                    t0 = 0;
                    jal(ctx, 0x3E6998u, gen::fn_sub_40E3C0_0040e3c0);
                    a0 = addiu(s2, 563);
                    a1 = addiu(s1, 409);
                    mtc1(zero, f12);
                    a2 = s0 & 0xFF;
                    lw(a3, s3, 4);
                    t0 = 0;
                    jal(ctx, 0x3E69B8u, gen::fn_sub_40E3C0_0040e3c0);
                    break;
                }
            L_003e6918:
                charge(ctx, 26);
                a0 = addiu(s2, 342);
                a1 = addiu(s1, 409);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                lw(a3, s3, 8);
                t0 = 0;
                jal(ctx, 0x3E6930u, gen::fn_sub_40E3C0_0040e3c0);
                a0 = addiu(s2, 495);
                a1 = addiu(s1, 409);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                lw(a3, s3, 0);
                t0 = 0;
                jal(ctx, 0x3E6950u, gen::fn_sub_40E3C0_0040e3c0);
                a0 = addiu(s2, 563);
                a1 = addiu(s1, 409);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                lw(a3, s3, 4);
                t0 = 0;
                jal(ctx, 0x3E6970u, gen::fn_sub_40E3C0_0040e3c0);
            }
            break;
        case 0x3E69C8u:  // table[8]
            // 0x003e69c8
            charge(ctx, 4);
            lw(v1, v0, 8);
            v1 = v1 & 0x20;
            if (v1 != 0) {
                // 0x003e69d8
                charge(ctx, 23);
                jal(ctx, 0x3E69D8u, gen::fn_sub_3E6DC0_003e6dc0);
                v0 = sll(v0, 3);
                v0 = addu(v0, sp);
                lw(s3, v0, 144);
                a0 = addiu(s2, 402);
                a1 = addiu(s1, 409);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                lw(a3, s3, 8);
                t0 = 0;
                jal(ctx, 0x3E6A04u, gen::fn_sub_40E3C0_0040e3c0);
                a0 = addiu(s2, 563);
                a1 = addiu(s1, 409);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                lw(a3, s3, 4);
                t0 = 0;
                jal(ctx, 0x3E6A24u, gen::fn_sub_40E3C0_0040e3c0);
            }
            break;
        case 0x3E6A34u:  // table[9]
            // 0x003e6a34
            charge(ctx, 4);
            lw(v1, v0, 8);
            v1 = v1 & 0x20;
            if (v1 != 0) {
                // 0x003e6a44
                charge(ctx, 31);
                jal(ctx, 0x3E6A44u, gen::fn_sub_3E6DC0_003e6dc0);
                v0 = sll(v0, 3);
                v0 = addu(v0, sp);
                lw(s3, v0, 144);
                a0 = addiu(s2, 498);
                a1 = addiu(s1, 388);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                lw(a3, s3, 8);
                t0 = 0;
                jal(ctx, 0x3E6A70u, gen::fn_sub_40E3C0_0040e3c0);
                a0 = addiu(s2, 495);
                a1 = addiu(s1, 409);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                lw(a3, s3, 0);
                t0 = 0;
                jal(ctx, 0x3E6A90u, gen::fn_sub_40E3C0_0040e3c0);
                a0 = addiu(s2, 563);
                a1 = addiu(s1, 409);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                lw(a3, s3, 4);
                t0 = 0;
                jal(ctx, 0x3E6AB0u, gen::fn_sub_40E3C0_0040e3c0);
            }
            break;
        case 0x3E6AC0u:  // table[10]
            // 0x003e6ac0
            charge(ctx, 4);
            lw(v1, v0, 8);
            v1 = v1 & 0x20;
            if (v1 != 0) {
                // 0x003e6ad0
                charge(ctx, 15);
                jal(ctx, 0x3E6AD0u, gen::fn_sub_3E6DC0_003e6dc0);
                v0 = sll(v0, 3);
                v0 = addu(v0, sp);
                lw(v0, v0, 144);
                a0 = addiu(s2, 563);
                a1 = addiu(s1, 409);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                lw(a3, v0, 4);
                t0 = 0;
                jal(ctx, 0x3E6AFCu, gen::fn_sub_40E3C0_0040e3c0);
            }
            break;
        case 0x3E6B0Cu:  // table[12]
            // 0x003e6b0c
            charge(ctx, 4);
            lw(v1, v0, 8);
            v1 = v1 & 0x20;
            if (v1 != 0) {
                // 0x003e6b1c
                charge(ctx, 23);
                jal(ctx, 0x3E6B1Cu, gen::fn_sub_3E6DC0_003e6dc0);
                v0 = sll(v0, 3);
                v0 = addu(v0, sp);
                lw(s3, v0, 144);
                a0 = addiu(s2, 495);
                a1 = addiu(s1, 409);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                lw(a3, s3, 0);
                t0 = 0;
                jal(ctx, 0x3E6B48u, gen::fn_sub_40E3C0_0040e3c0);
                a0 = addiu(s2, 563);
                a1 = addiu(s1, 409);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                lw(a3, s3, 4);
                t0 = 0;
                jal(ctx, 0x3E6B68u, gen::fn_sub_40E3C0_0040e3c0);
            }
            break;
        case 0x3E6B78u:  // table[13]
            // 0x003e6b78
            charge(ctx, 4);
            lw(v1, v0, 8);
            v1 = v1 & 0x20;
            if (v1 != 0) {
                // 0x003e6b88
                charge(ctx, 23);
                jal(ctx, 0x3E6B88u, gen::fn_sub_3E6DC0_003e6dc0);
                v0 = sll(v0, 3);
                v0 = addu(v0, sp);
                lw(s3, v0, 144);
                a0 = addiu(s2, 495);
                a1 = addiu(s1, 409);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                lw(a3, s3, 16);
                t0 = 0;
                jal(ctx, 0x3E6BB4u, gen::fn_sub_40E3C0_0040e3c0);
                a0 = addiu(s2, 563);
                a1 = addiu(s1, 409);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                lw(a3, s3, 4);
                t0 = 0;
                jal(ctx, 0x3E6BD4u, gen::fn_sub_40E3C0_0040e3c0);
            }
            break;
        case 0x3E6BE4u:  // table[14]
            // 0x003e6be4
            charge(ctx, 4);
            lw(v1, v0, 8);
            v1 = v1 & 0x20;
            if (v1 != 0) {
                // 0x003e6bf4
                charge(ctx, 15);
                jal(ctx, 0x3E6BF4u, gen::fn_sub_3E6DC0_003e6dc0);
                v0 = sll(v0, 3);
                v0 = addu(v0, sp);
                lw(v0, v0, 144);
                a0 = addiu(s2, 563);
                a1 = addiu(s1, 409);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                lw(a3, v0, 4);
                t0 = 0;
                jal(ctx, 0x3E6C20u, gen::fn_sub_40E3C0_0040e3c0);
            }
            break;
        case 0x3E6C30u:  // table[15]
            // 0x003e6c30
            charge(ctx, 4);
            lw(v1, v0, 8);
            v1 = v1 & 0x20;
            if (v1 != 0) {
                // 0x003e6c40
                charge(ctx, 23);
                jal(ctx, 0x3E6C40u, gen::fn_sub_3E6DC0_003e6dc0);
                v0 = sll(v0, 3);
                v0 = addu(v0, sp);
                lw(s3, v0, 144);
                a0 = addiu(s2, 495);
                a1 = addiu(s1, 409);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                lw(a3, s3, 0);
                t0 = 0;
                jal(ctx, 0x3E6C6Cu, gen::fn_sub_40E3C0_0040e3c0);
                a0 = addiu(s2, 563);
                a1 = addiu(s1, 409);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                lw(a3, s3, 4);
                t0 = 0;
                jal(ctx, 0x3E6C8Cu, gen::fn_sub_40E3C0_0040e3c0);
            }
            break;
        case 0x3E6C9Cu:  // table[16]
            // 0x003e6c9c
            charge(ctx, 4);
            lw(v1, v0, 8);
            v1 = v1 & 0x20;
            if (v1 != 0) {
                // 0x003e6cac
                charge(ctx, 23);
                jal(ctx, 0x3E6CACu, gen::fn_sub_3E6DC0_003e6dc0);
                v0 = sll(v0, 3);
                v0 = addu(v0, sp);
                lw(s3, v0, 144);
                a0 = addiu(s2, 495);
                a1 = addiu(s1, 409);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                lw(a3, s3, 20);
                t0 = 0;
                jal(ctx, 0x3E6CD8u, gen::fn_sub_40E3C0_0040e3c0);
                a0 = addiu(s2, 563);
                a1 = addiu(s1, 409);
                mtc1(zero, f12);
                a2 = s0 & 0xFF;
                lw(a3, s3, 4);
                t0 = 0;
                jal(ctx, 0x3E6CF8u, gen::fn_sub_40E3C0_0040e3c0);
            }
            break;
        case 0x3E6D08u:  // table[17]: id 17 -- the antique panel (sub_3E6130)
            // 0x003e6d08
            charge(ctx, 3);
            a0 = s3;
            jal(ctx, 0x3E6D0Cu, gen::fn_sub_3E6130_003e6130);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x003e6d14 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x140);
}

// 0x003E6D40 sub_3E6D40 -- 40 bytes; frame 0x10: ra sp+0x0
// [fclShopDrawSteps] nmSequenceCallAll36 on the shop sequence (every step's draw callback). Returns 0.
void sub_3E6D40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e6d40
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    jal(ctx, 0x3E6D4Cu, gen::fn_nmSequenceCallAll36_003c5760);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003E6D70 sub_3E6D70 -- 76 bytes; frame 0x10: ra sp+0x0
// [fclShopHasLineup] 1 when the shop is open and its work flag 4 is set (the type sells something, state 6). Callers:
// the BG manager's sub_40F030 / sub_40F430.
void sub_3E6D70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e6d70
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    if (a0 != 0) {
        // 0x003e6d84
        charge(ctx, 6);
        jal(ctx, 0x3E6D84u, gen::fn_nmObjPayloadWord12_003c5460);
        lw(v0, v0, 8);
        v0 = v0 & 0x4;
        if (v0 == 0) {
            goto L_003e6da8;
        }
        // 0x003e6d9c
        charge(ctx, 3);
        v0 = 1;
        // 0x003e6dac (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_003e6da8:
    charge(ctx, 1);
    v0 = 0;
    // 0x003e6dac (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003E6DC0 sub_3E6DC0 -- 92 bytes; frame 0x10: ra sp+0x0
// [fclShopGetType] The open shop's type, -1 without a shop (K_Assert fclShop.c:1186 first, `jr $ra` in retail).
void sub_3E6DC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e6dc0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -18024);  // 0x7CE688: the shop sequence
    if (v0 == 0) {
        // 0x003e6dd4
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 27384);  // "fclShop.c"
        a1 = 1186;
        jal(ctx, 0x3E6DE0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003e6de8
    charge(ctx, 3);
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    if (a0 == 0) {
        // 0x003e6e08
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x003e6df4
        charge(ctx, 5);
        jal(ctx, 0x3E6DF4u, gen::fn_nmObjPayloadWord12_003c5460);
        lw(v0, v0, 0);
    }
    // 0x003e6e0c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003E6E80 sub_3E6E80 -- 6208 bytes; frame 0xC0: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopRoot] The root of the shop sequence, once per frame (nmSequence callback): $s2 = the work record. Runs the
// element set (sub_3E0650), then a jump table over the state (+4, 81 entries; the case comments name each state).
// Outline: 1 add the BG step; 4 / 5 the LOAD step (the type's load script); 6 set-up (MONEY / SUBTITLE steps, the
// message window, the lineup flag, the BGM for types 0-2 / 4, a once-only intro message); 7 / 8 wait for it; 9 / 10
// the greeting (sub_3F0830); 11 / 12 message 1; 13 the hub: quest requests for type 8 (party members' requests,
// sub_17C670 / sub_403970) or the antique shop's offer (sub_402480), else 39; 14..32 the request / trade-in dialogue
// (messages 8..16, the item checks sub_404120 / sub_403F20, the purchase log sub_4044C0); 33..38 the antique offer
// (300 - sub_16F490(1)), the reward and its messages 20..24; 39 / 40 / 41 leave or message 3; 42 / 43 the ROOT menu
// (sub_3E8E20 / sub_3E8FF0) and its 13 choices; 44..47 BUY, 48 / 49 SELL, 50 / 51 the type-8 list, 52 / 53 TALK, 54 /
// 55 leave -> 2; 2 / 3 fade out and return 1 (the sequence ends); 56..62 the social-link scene of the shop's link
// (sub_3F12A0 messages, the task sub_3A2090); 63..80 the other menu choices (messages 21 / 25, the steps sub_3EAD10 /
// sub_3EBA10 / sub_3EC090 / sub_3EC6F0 / sub_3ECD30 / sub_3ED380). Every exit returns 0 except state 3.
void sub_3E6E80(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e6e80
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x3E6E94u, gen::fn_nmObjPayloadWord12_003c5460);
    s2 = v0;
    jal(ctx, 0x3E6EA0u, gen::fn_sub_3C7B90_003c7b90);
    lw(a0, s2, shop::kShopElements);
    jal(ctx, 0x3E6EACu, gen::fn_sub_3E0650_003e0650);
    lw(v0, s2, shop::kShopState);
    at = sltiu(v0, 81);
    if (at != 0) {
        // 0x003e6ec4
        charge(ctx, 7);
        v1 = 0x7C0000;
        v1 = addiu(v1, -17952);  // &0x7BB9E0
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x3E6EE0u:  // table[1]: state 1 -- start: add the BG step -> 4
            // 0x003e6ee0
            charge(ctx, 7);
            v0 = 4;
            sw(v0, s2, shop::kShopState);
            a0 = s2;
            jal(ctx, 0x3E6EECu, gen::fn_sub_3EFB40_003efb40);
        L_003e86a0:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x3E6EFCu:  // table[2]: state 2 -- leaving: fade out (BGM for types 0-2 / 4) -> 3
            // 0x003e6efc
            charge(ctx, 4);
            lw(v1, s2, shop::kShopType);
            v0 = 4;
            if (v1 != v0) {
                // 0x003e6f0c
                charge(ctx, 3);
                v0 = 2;
                if (v1 == v0) {
                    goto L_003e6f34;
                }
                // 0x003e6f18
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    goto L_003e6f34;
                }
                // 0x003e6f24
                charge(ctx, 2);
                if (v1 == 0) {
                    goto L_003e6f34;
                }
                // 0x003e6f2c
                charge(ctx, 2);
                goto L_003e6f48;
            }
        L_003e6f34:
            charge(ctx, 5);
            jal(ctx, 0x3E6F34u, gen::fn_sub_108570_00108570);
            a0 = 2;
            jal(ctx, 0x3E6F40u, gen::fn_sub_108670_00108670);
        L_003e6f48:
            charge(ctx, 2);
            v0 = 3;
            sw(v0, s2, shop::kShopState);
        L_003e6f50:
            charge(ctx, 5);
            jal(ctx, 0x3E6F50u, gen::fn_sub_108710_00108710);
            v1 = 1;
            if (v0 != v1) {
                goto L_003e86a0;
            }
            // 0x003e6f64
            charge(ctx, 3);
            v0 = v1;
            break;
        case 0x3E6F50u:  // table[3]: state 3 -- wait for the fade, then return 1 (the sequence ends)
            goto L_003e6f50;
        case 0x3E6F70u:  // table[4]: state 4 -- add the LOAD step -> 5
            // 0x003e6f70
            charge(ctx, 5);
            v0 = 5;
            sw(v0, s2, shop::kShopState);
            a0 = s2;
            jal(ctx, 0x3E6F7Cu, gen::fn_sub_3E86C0_003e86c0);
        L_003e6f84:
            charge(ctx, 6);
            a0 = s2;
            jal(ctx, 0x3E6F88u, gen::fn_sub_3E8740_003e8740);
            v1 = si(-1);
            if (v0 != v1) {
                // 0x003e6f9c
                charge(ctx, 4);
                v0 = 6;
                sw(v0, s2, shop::kShopState);
            }
            goto L_003e86a0;
        case 0x3E6F84u:  // table[5]: state 5 -- wait for the load script -> 6
            goto L_003e6f84;
        case 0x3E6FACu:  // table[6]: state 6 -- set-up: MONEY / SUBTITLE steps, message window, lineup flag 4, BGM, the once-only intro (-> 7) else -> 9
            // 0x003e6fac
            charge(ctx, 21);
            v0 = 9;
            sw(v0, s2, shop::kShopState);
            a0 = addiu(s2, 140);
            a1 = 0;
            a2 = 8;
            jal(ctx, 0x3E6FC0u, gen::fn_memset_00521408);
            a0 = s2;
            jal(ctx, 0x3E6FCCu, gen::fn_sub_3EE570_003ee570);
            a0 = s2;
            jal(ctx, 0x3E6FD8u, gen::fn_sub_3EED90_003eed90);
            lw(a0, s2, 100);
            jal(ctx, 0x3E6FE4u, gen::fn_sub_3C72D0_003c72d0);
            lw(a0, s2, shop::kShopType);
            jal(ctx, 0x3E6FF0u, gen::fn_sub_3F0240_003f0240);
            if (v0 != 0) {
                // 0x003e7000
                charge(ctx, 3);
                lw(v0, s2, shop::kShopFlags);
                v0 = v0 | 0x4;
                sw(v0, s2, shop::kShopFlags);
            }
            // 0x003e700c
            charge(ctx, 4);
            lw(v1, s2, shop::kShopType);
            v0 = 4;
            if (v1 != v0) {
                // 0x003e701c
                charge(ctx, 3);
                v0 = 2;
                if (v1 == v0) {
                    goto L_003e7044;
                }
                // 0x003e7028
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    goto L_003e7044;
                }
                // 0x003e7034
                charge(ctx, 2);
                if (v1 == 0) {
                    goto L_003e7044;
                }
                // 0x003e703c
                charge(ctx, 2);
                goto L_003e7068;
            }
        L_003e7044:
            charge(ctx, 9);
            a0 = 56;
            a1 = 1;
            jal(ctx, 0x3E704Cu, gen::fn_sub_1099D0_001099d0);
            jal(ctx, 0x3E7054u, gen::fn_sub_1085C0_001085c0);
            a0 = 2;
            jal(ctx, 0x3E7060u, gen::fn_sub_108670_00108670);
        L_003e7068:
            charge(ctx, 8);
            lw(a0, s2, shop::kShopType);
            jal(ctx, 0x3E706Cu, gen::fn_sub_3F0090_003f0090);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
            v0 = si(-1);
            if (s0 != v0) {
                // 0x003e7088
                charge(ctx, 9);
                lw(a0, s2, shop::kShopType);
                jal(ctx, 0x3E708Cu, gen::fn_sub_3F00B0_003f00b0);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x3E709Cu, gen::fn_datGetFlag_0016f190);
                if (v0 == 0) {
                    // 0x003e70ac
                    charge(ctx, 18);
                    v0 = 7;
                    sw(v0, s2, shop::kShopState);
                    a0 = 2;
                    jal(ctx, 0x3E70B8u, gen::fn_sub_3C82E0_003c82e0);
                    a0 = s0;
                    jal(ctx, 0x3E70C4u, gen::fn_sub_3C9790_003c9790);
                    lw(a0, s2, shop::kShopType);
                    jal(ctx, 0x3E70D0u, gen::fn_sub_3F00B0_003f00b0);
                    a0 = dsll32(v0, 16);
                    a0 = dsra32(a0, 16);
                    a1 = 1;
                    jal(ctx, 0x3E70E4u, gen::fn_datSetFlag_0016f1f0);
                }
            }
            goto L_003e86a0;
        case 0x3E70F4u:  // table[7]: state 7 -- wait for the intro message -> 8
            // 0x003e70f4
            charge(ctx, 4);
            jal(ctx, 0x3E70F4u, gen::fn_sub_3C7850_003c7850);
            if (v0 == 0) {
                // 0x003e7104
                charge(ctx, 6);
                jal(ctx, 0x3E7104u, gen::fn_sub_3C7700_003c7700);
                v0 = 8;
                sw(v0, s2, shop::kShopState);
            }
            goto L_003e86a0;
        case 0x3E711Cu:  // table[8]: state 8 -- wait (sub_3C83B0) -> 9
            // 0x003e711c
            charge(ctx, 4);
            jal(ctx, 0x3E711Cu, gen::fn_sub_3C83B0_003c83b0);
            if (v0 == 0) {
                // 0x003e712c
                charge(ctx, 7);
                a0 = 0;
                jal(ctx, 0x3E7130u, gen::fn_sub_3C82E0_003c82e0);
                v0 = 9;
                sw(v0, s2, shop::kShopState);
            }
            goto L_003e86a0;
        case 0x3E7148u:  // table[9]: state 9 -- the greeting (sub_3F0830) -> 10, none -> 13
            // 0x003e7148
            charge(ctx, 8);
            v0 = 10;
            sw(v0, s2, shop::kShopState);
            lw(a0, s2, shop::kShopType);
            jal(ctx, 0x3E7154u, gen::fn_sub_3F0830_003f0830);
            v1 = si(-1);
            if (v0 == v1) {
                // 0x003e717c
                charge(ctx, 4);
                v0 = 13;
                sw(v0, s2, shop::kShopState);
            } else {
                // 0x003e7168
                charge(ctx, 5);
                a0 = v0;
                jal(ctx, 0x3E716Cu, gen::fn_msgWinRequestMessage_003c7430);
            L_003e718c:
                charge(ctx, 4);
                jal(ctx, 0x3E718Cu, gen::fn_sub_3C7850_003c7850);
                if (v0 == 0) {
                    // 0x003e719c
                    charge(ctx, 7);
                    jal(ctx, 0x3E719Cu, gen::fn_sub_3C7700_003c7700);
                    lw(a0, s2, shop::kShopType);
                    jal(ctx, 0x3E71A8u, gen::fn_sub_3F0240_003f0240);
                    if (v0 == 0) {
                        // 0x003e71c8
                        charge(ctx, 4);
                        v0 = 13;
                        sw(v0, s2, shop::kShopState);
                    } else {
                        // 0x003e71b8
                        charge(ctx, 4);
                        v0 = 11;
                        sw(v0, s2, shop::kShopState);
                    }
                }
            }
            goto L_003e86a0;
        case 0x3E718Cu:  // table[10]: state 10 -- wait for the greeting; a lineup -> 11 else 13
            goto L_003e718c;
        case 0x3E71D8u:  // table[11]: state 11 -- message 1 -> 12
            // 0x003e71d8
            charge(ctx, 5);
            v0 = 12;
            sw(v0, s2, shop::kShopState);
            a0 = 1;
            jal(ctx, 0x3E71E4u, gen::fn_msgWinRequestMessage_003c7430);
        L_003e71ec:
            charge(ctx, 4);
            jal(ctx, 0x3E71ECu, gen::fn_sub_3C7850_003c7850);
            if (v0 == 0) {
                // 0x003e71fc
                charge(ctx, 6);
                jal(ctx, 0x3E71FCu, gen::fn_sub_3C7700_003c7700);
                v0 = 13;
                sw(v0, s2, shop::kShopState);
            }
            goto L_003e86a0;
        case 0x3E71ECu:  // table[12]: state 12 -- wait -> 13
            goto L_003e71ec;
        case 0x3E7214u:  // table[13]: state 13 -- the hub: party requests (type 8) / the antique offer (type 4) -> 14 / 18 / 31 / 33, else 39
            // 0x003e7214
            charge(ctx, 4);
            lw(v1, s2, shop::kShopType);
            v0 = 8;
            if (v1 == v0) {
                // 0x003e7274
                charge(ctx, 4);
                lw(v0, s2, shop::kShopFlags);
                v0 = v0 & 0x8;
                if (v0 == 0) {
                    // 0x003e7284
                    charge(ctx, 4);
                    jal(ctx, 0x3E7284u, gen::fn_sub_403520_00403520);
                    if (v0 == 0) {
                        goto L_003e72c8;
                    }
                    // 0x003e7294
                    charge(ctx, 13);
                    jal(ctx, 0x3E7294u, gen::fn_sub_403610_00403610);
                    lw(v0, s2, shop::kShopFlags);
                    v0 = v0 | 0x8;
                    sw(v0, s2, shop::kShopFlags);
                    v0 = 14;
                    sw(v0, s2, shop::kShopState);
                    lw(v0, s2, shop::kShopFlags);
                    v0 = v0 | 0x2;
                    sw(v0, s2, shop::kShopFlags);
                    v0 = 0;
                    break;
                }
            L_003e72c8:
                charge(ctx, 3);
                s1 = 0;
                for (;;) {
                    // 0x003e7374
                    charge(ctx, 3);
                    v0 = slti(s1, 3);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x003e72d4
                    charge(ctx, 6);
                    a0 = s1;
                    jal(ctx, 0x3E72D8u, gen::fn_sub_17C670_0017c670);
                    s0 = v0;
                    if (s0 != 0) {
                        // 0x003e72ec
                        charge(ctx, 4);
                        lh(a0, s0, 0);
                        v1 = 0;
                        for (;;) {
                            // 0x003e7320
                            charge(ctx, 3);
                            v0 = slti(v1, 4);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x003e72fc
                            charge(ctx, 5);
                            v0 = sll(v1, 1);
                            v0 = addu(s2, v0);
                            lh(v0, v0, 140);
                            if (v0 == a0) {
                                goto L_003e7310_53;
                            }
                            // 0x003e731c
                            charge(ctx, 1);
                            v1 = addiu(v1, 1);
                        }
                        // 0x003e732c
                        charge(ctx, 1);
                        v0 = 0;
                    L_003e7330:
                        charge(ctx, 2);
                        if (v0 != 0) {
                            goto L_003e7370;
                        }
                        // 0x003e7338
                        charge(ctx, 4);
                        jal(ctx, 0x3E7338u, gen::fn_sub_403970_00403970);
                        if (v0 == 0) {
                            goto L_003e7370;
                        }
                        goto L_003e7348_59;
                    }
                L_003e7370:
                    charge(ctx, 1);
                    s1 = addiu(s1, 1);
                }
                // 0x003e7380
                charge(ctx, 4);
                lw(v1, s2, shop::kShopFlags);
                v0 = v1 & 0x2;
                if (v0 == 0) {
                L_003e73cc:
                    charge(ctx, 4);
                    v0 = 39;
                    sw(v0, s2, shop::kShopState);
                } else {
                    // 0x003e7390
                    charge(ctx, 15);
                    v0 = si(-3);
                    v0 = v1 & v0;
                    sw(v0, s2, shop::kShopFlags);
                    v0 = 31;
                    sw(v0, s2, shop::kShopState);
                    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
                    jal(ctx, 0x3E73A8u, gen::fn_nmObjPayloadWord12_003c5460);
                    a0 = v0;
                    a1 = 1;
                    a2 = 0;
                    jal(ctx, 0x3E73BCu, gen::fn_sub_3E0C20_003e0c20);
                }
                goto L_003e86a0;
            }
            // 0x003e7224
            charge(ctx, 3);
            v0 = 4;
            if (v1 != v0) {
                // 0x003e7230
                charge(ctx, 2);
                goto L_003e73cc;
            }
            // 0x003e7238
            charge(ctx, 6);
            a0 = addiu(sp, 0x80);
            jal(ctx, 0x3E723Cu, gen::fn_sub_402480_00402480);
            v1 = 1;
            if (v0 != v1) {
                // 0x003e7264
                charge(ctx, 4);
                v0 = 39;
                sw(v0, s2, shop::kShopState);
                goto L_003e86a0;
            }
            // 0x003e7250
            charge(ctx, 5);
            v0 = 33;
            sw(v0, s2, shop::kShopState);
            v0 = 0;
            break;
        case 0x3E73DCu:  // table[14]: state 14 -- message 15 -> 15
            // 0x003e73dc
            charge(ctx, 4);
            a0 = 15;
            sw(a0, s2, shop::kShopState);
            jal(ctx, 0x3E73E4u, gen::fn_msgWinRequestMessage_003c7430);
        L_003e73ec:
            charge(ctx, 4);
            jal(ctx, 0x3E73ECu, gen::fn_sub_3C7850_003c7850);
            if (v0 == 0) {
                // 0x003e73fc
                charge(ctx, 6);
                jal(ctx, 0x3E73FCu, gen::fn_sub_3C7700_003c7700);
                v0 = 16;
                sw(v0, s2, shop::kShopState);
            }
            goto L_003e86a0;
        case 0x3E73ECu:  // table[15]: state 15 -- wait -> 16
            goto L_003e73ec;
        case 0x3E7414u:  // table[16]: state 16 -- message sub_40C170 -> 17
            // 0x003e7414
            charge(ctx, 9);
            v0 = 17;
            sw(v0, s2, shop::kShopState);
            jal(ctx, 0x3E741Cu, gen::fn_sub_40C170_0040c170);
            a0 = v0;
            jal(ctx, 0x3E7428u, gen::fn_msgWinRequestMessage_003c7430);
            jal(ctx, 0x3E7430u, gen::fn_sub_17D040_0017d040);
        L_003e7438:
            charge(ctx, 4);
            jal(ctx, 0x3E7438u, gen::fn_sub_3C7850_003c7850);
            if (v0 == 0) {
                // 0x003e7448
                charge(ctx, 6);
                jal(ctx, 0x3E7448u, gen::fn_sub_3C7700_003c7700);
                v0 = 13;
                sw(v0, s2, shop::kShopState);
            }
            goto L_003e86a0;
        case 0x3E7438u:  // table[17]: state 17 -- wait -> 13
            goto L_003e7438;
        case 0x3E7460u:  // table[18]: state 18 -- a request: message 14 / 8 -> 19
            // 0x003e7460
            charge(ctx, 14);
            lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
            jal(ctx, 0x3E7464u, gen::fn_nmObjPayloadWord12_003c5460);
            a0 = v0;
            a1 = 1;
            a2 = 0;
            jal(ctx, 0x3E7478u, gen::fn_sub_3E0C20_003e0c20);
            v0 = 19;
            sw(v0, s2, shop::kShopState);
            lw(v0, s2, shop::kShopFlags);
            v0 = v0 & 0x10;
            if (v0 != 0) {
                // 0x003e74ac
                charge(ctx, 3);
                a0 = 14;
                jal(ctx, 0x3E74B0u, gen::fn_msgWinRequestMessage_003c7430);
            } else {
                // 0x003e7498
                charge(ctx, 5);
                a0 = 8;
                jal(ctx, 0x3E749Cu, gen::fn_msgWinRequestMessage_003c7430);
            }
            // 0x003e74b8
            charge(ctx, 3);
            lw(v0, s2, shop::kShopFlags);
            v0 = v0 | 0x10;
            sw(v0, s2, shop::kShopFlags);
        L_003e74c4:
            charge(ctx, 4);
            jal(ctx, 0x3E74C4u, gen::fn_sub_3C7850_003c7850);
            if (v0 == 0) {
                // 0x003e74d4
                charge(ctx, 6);
                jal(ctx, 0x3E74D4u, gen::fn_sub_3C7700_003c7700);
                v0 = 20;
                sw(v0, s2, shop::kShopState);
            }
            goto L_003e86a0;
        case 0x3E74C4u:  // table[19]: state 19 -- wait -> 20
            goto L_003e74c4;
        case 0x3E74ECu:  // table[20]: state 20 -- message of the item (sub_4030F0) -> 21
            // 0x003e74ec
            charge(ctx, 9);
            v0 = 21;
            sw(v0, s2, shop::kShopState);
            lhu(a0, s2, shop::kShopItemId);
            jal(ctx, 0x3E74F8u, gen::fn_sub_4030F0_004030f0);
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x3E7508u, gen::fn_msgWinRequestMessage_003c7430);
        L_003e7510:
            charge(ctx, 4);
            jal(ctx, 0x3E7510u, gen::fn_sub_3C7850_003c7850);
            if (v0 == 0) {
                // 0x003e7520
                charge(ctx, 6);
                jal(ctx, 0x3E7520u, gen::fn_sub_3C7700_003c7700);
                v0 = 22;
                sw(v0, s2, shop::kShopState);
            }
            goto L_003e86a0;
        case 0x3E7510u:  // table[21]: state 21 -- wait -> 22
            goto L_003e7510;
        case 0x3E7538u:  // table[22]: state 22 -- check the item (sub_404120 / sub_403F20) -> 23 / 24 / 25
            // 0x003e7538
            charge(ctx, 6);
            lh(a0, s2, shop::kShopItemId);
            a1 = 0;
            jal(ctx, 0x3E7540u, gen::fn_sub_404120_00404120);
            if (v0 == 0) {
                // 0x003e7550
                charge(ctx, 7);
                v0 = 23;
                sw(v0, s2, shop::kShopState);
                a0 = 12;
                jal(ctx, 0x3E755Cu, gen::fn_msgWinRequestMessage_003c7430);
                goto L_003e86a0;
            }
            // 0x003e756c
            charge(ctx, 7);
            lh(a0, s2, shop::kShopItemId);
            a1 = 0;
            jal(ctx, 0x3E7574u, gen::fn_sub_403F20_00403f20);
            v1 = 2;
            if (v0 == v1) {
                // 0x003e75bc
                charge(ctx, 14);
                v0 = 24;
                sw(v0, s2, shop::kShopState);
                a0 = 10;
                jal(ctx, 0x3E75C8u, gen::fn_msgWinRequestMessage_003c7430);
                a0 = 0;
                jal(ctx, 0x3E75D4u, gen::fn_sub_3C74E0_003c74e0);
                a0 = 0;
                jal(ctx, 0x3E75E0u, gen::fn_msgWinSetType_003c7560);
                v0 = 0;
            } else {
                // 0x003e7588
                charge(ctx, 3);
                v1 = 1;
                if (v0 != v1) {
                    // 0x003e7594
                    charge(ctx, 2);
                    // 0x003e75f4
                    charge(ctx, 7);
                    v0 = 25;
                    sw(v0, s2, shop::kShopState);
                    a0 = 9;
                    jal(ctx, 0x3E7600u, gen::fn_msgWinRequestMessage_003c7430);
                    goto L_003e86a0;
                }
                // 0x003e759c
                charge(ctx, 8);
                v0 = 23;
                sw(v0, s2, shop::kShopState);
                a0 = 11;
                jal(ctx, 0x3E75A8u, gen::fn_msgWinRequestMessage_003c7430);
                v0 = 0;
            }
            break;
        case 0x3E7610u:  // table[23]: state 23 -- wait -> 29
            // 0x003e7610
            charge(ctx, 4);
            jal(ctx, 0x3E7610u, gen::fn_sub_3C7850_003c7850);
            if (v0 == 0) {
                // 0x003e7620
                charge(ctx, 6);
                jal(ctx, 0x3E7620u, gen::fn_sub_3C7700_003c7700);
                v0 = 29;
                sw(v0, s2, shop::kShopState);
            }
            goto L_003e86a0;
        case 0x3E7638u:  // table[24]: state 24 -- wait; the choice -> 29 / 26
            // 0x003e7638
            charge(ctx, 4);
            jal(ctx, 0x3E7638u, gen::fn_sub_3C7850_003c7850);
            if (v0 == 0) {
                // 0x003e7648
                charge(ctx, 6);
                jal(ctx, 0x3E7648u, gen::fn_sub_3C7700_003c7700);
                jal(ctx, 0x3E7650u, gen::fn_msgWinLastSelection_003c7610);
                if (v0 != 0) {
                    // 0x003e7670
                    charge(ctx, 4);
                    v0 = 29;
                    sw(v0, s2, shop::kShopState);
                } else {
                    // 0x003e7660
                    charge(ctx, 4);
                    v0 = 26;
                    sw(v0, s2, shop::kShopState);
                }
            }
            goto L_003e86a0;
        case 0x3E7680u:  // table[25]: state 25 -- wait -> 26
            // 0x003e7680
            charge(ctx, 4);
            jal(ctx, 0x3E7680u, gen::fn_sub_3C7850_003c7850);
            if (v0 == 0) {
                // 0x003e7690
                charge(ctx, 6);
                jal(ctx, 0x3E7690u, gen::fn_sub_3C7700_003c7700);
                v0 = 26;
                sw(v0, s2, shop::kShopState);
            }
            goto L_003e86a0;
        case 0x3E76A8u:  // table[26]: state 26 -- hand over: message sub_4030B0 -> 27
            // 0x003e76a8
            charge(ctx, 4);
            jal(ctx, 0x3E76A8u, gen::fn_sub_3C83B0_003c83b0);
            if (v0 == 0) {
                // 0x003e76c4
                charge(ctx, 22);
                lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
                jal(ctx, 0x3E76C8u, gen::fn_nmObjPayloadWord12_003c5460);
                a0 = v0;
                a1 = 1;
                a2 = a1;
                jal(ctx, 0x3E76DCu, gen::fn_sub_3E0C20_003e0c20);
                v0 = 27;
                sw(v0, s2, shop::kShopState);
                lhu(a0, s2, shop::kShopItemId);
                jal(ctx, 0x3E76F0u, gen::fn_sub_4030B0_004030b0);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x3E7700u, gen::fn_msgWinRequestMessage_003c7430);
                lh(a0, s2, shop::kShopItemId);
                jal(ctx, 0x3E770Cu, gen::fn_sub_4038A0_004038a0);
                if (v0 != 0) {
                    // 0x003e771c
                    charge(ctx, 8);
                    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
                    jal(ctx, 0x3E7720u, gen::fn_nmObjPayloadWord12_003c5460);
                    a0 = v0;
                    a1 = 2;
                    a2 = 0;
                    jal(ctx, 0x3E7734u, gen::fn_sub_3E0C20_003e0c20);
                }
            L_003e773c:
                charge(ctx, 4);
                jal(ctx, 0x3E773Cu, gen::fn_sub_3C7850_003c7850);
                if (v0 == 0) {
                    // 0x003e774c
                    charge(ctx, 6);
                    jal(ctx, 0x3E774Cu, gen::fn_sub_3C7700_003c7700);
                    v0 = 28;
                    sw(v0, s2, shop::kShopState);
                }
                goto L_003e86a0;
            }
            // 0x003e76b8
            charge(ctx, 3);
            v0 = 0;
            break;
        case 0x3E773Cu:  // table[27]: state 27 -- wait -> 28
            goto L_003e773c;
        case 0x3E7764u:  // table[28]: state 28 -- finish (sub_403F20(item, 1), sub_4044C0) -> 56 / 13
            // 0x003e7764
            charge(ctx, 4);
            jal(ctx, 0x3E7764u, gen::fn_sub_3C83B0_003c83b0);
            if (v0 == 0) {
                // 0x003e7780
                charge(ctx, 5);
                lh(a0, s2, shop::kShopItemId);
                jal(ctx, 0x3E7784u, gen::fn_sub_4038A0_004038a0);
                if (v0 == 0) {
                    // 0x003e77bc
                    charge(ctx, 6);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 6;
                    jal(ctx, 0x3E77CCu, gen::fn_sub_10A4E0_0010a4e0);
                } else {
                    // 0x003e7794
                    charge(ctx, 10);
                    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
                    jal(ctx, 0x3E7798u, gen::fn_nmObjPayloadWord12_003c5460);
                    a0 = v0;
                    a1 = 2;
                    a2 = 1;
                    jal(ctx, 0x3E77ACu, gen::fn_sub_3E0C20_003e0c20);
                }
                // 0x003e77d4
                charge(ctx, 12);
                lh(a0, s2, shop::kShopItemId);
                a1 = 1;
                jal(ctx, 0x3E77DCu, gen::fn_sub_403F20_00403f20);
                lh(a0, s2, shop::kShopItemId);
                jal(ctx, 0x3E77E8u, gen::fn_sub_4044C0_004044c0);
                lw(a0, s2, shop::kShopType);
                jal(ctx, 0x3E77F4u, gen::fn_sub_3F1470_003f1470);
                if (v0 == 0) {
                    // 0x003e7814
                    charge(ctx, 4);
                    v0 = 13;
                    sw(v0, s2, shop::kShopState);
                } else {
                    // 0x003e7804
                    charge(ctx, 4);
                    v0 = 56;
                    sw(v0, s2, shop::kShopState);
                }
                goto L_003e86a0;
            }
            // 0x003e7774
            charge(ctx, 3);
            v0 = 0;
            break;
        case 0x3E7824u:  // table[29]: state 29 -- message 13 -> 30
            // 0x003e7824
            charge(ctx, 5);
            v0 = 30;
            sw(v0, s2, shop::kShopState);
            a0 = 13;
            jal(ctx, 0x3E7830u, gen::fn_msgWinRequestMessage_003c7430);
        L_003e7838:
            charge(ctx, 4);
            jal(ctx, 0x3E7838u, gen::fn_sub_3C7850_003c7850);
            if (v0 == 0) {
                // 0x003e7848
                charge(ctx, 8);
                jal(ctx, 0x3E7848u, gen::fn_sub_3C7700_003c7700);
                v0 = 13;
                sw(v0, s2, shop::kShopState);
                lh(a0, s2, shop::kShopItemId);
                v1 = 0;
                for (;;) {
                    // 0x003e788c
                    charge(ctx, 3);
                    v0 = slti(v1, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x003e7868
                    charge(ctx, 5);
                    v0 = sll(v1, 1);
                    v0 = addu(s2, v0);
                    lh(v0, v0, 140);
                    if (v0 == a0) {
                        goto L_003e787c_114;
                    }
                    // 0x003e7888
                    charge(ctx, 1);
                    v1 = addiu(v1, 1);
                }
                // 0x003e7898
                charge(ctx, 1);
                v0 = 0;
            L_003e789c:
                charge(ctx, 2);
                if (v0 == 0) {
                    // 0x003e78a4
                    charge(ctx, 3);
                    a1 = 0;
                    for (;;) {
                        // 0x003e78d8
                        charge(ctx, 3);
                        v0 = slti(a1, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x003e78b0
                        charge(ctx, 6);
                        v0 = sll(a1, 1);
                        v0 = addu(s2, v0);
                        v1 = addiu(v0, 140);
                        lh(v0, v0, 140);
                        if (v0 == 0) {
                            goto L_003e78c8_121;
                        }
                        // 0x003e78d4
                        charge(ctx, 1);
                        a1 = addiu(a1, 1);
                    }
                }
            L_003e78e4:
                charge(ctx, 10);
                lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
                jal(ctx, 0x3E78E8u, gen::fn_nmObjPayloadWord12_003c5460);
                a0 = v0;
                a1 = 1;
                a2 = a1;
                jal(ctx, 0x3E78FCu, gen::fn_sub_3E0C20_003e0c20);
            }
            goto L_003e86a0;
        case 0x3E7838u:  // table[30]: state 30 -- wait; note the member -> 13
            goto L_003e7838;
        case 0x3E790Cu:  // table[31]: state 31 -- message 16 -> 32
            // 0x003e790c
            charge(ctx, 12);
            v0 = 32;
            sw(v0, s2, shop::kShopState);
            lw(v1, s2, shop::kShopFlags);
            v0 = si(-9);
            v1 = v1 & v0;
            sw(v1, s2, shop::kShopFlags);
            v0 = si(-17);
            v0 = v1 & v0;
            sw(v0, s2, shop::kShopFlags);
            a0 = 16;
            jal(ctx, 0x3E7934u, gen::fn_msgWinRequestMessage_003c7430);
        L_003e793c:
            charge(ctx, 4);
            jal(ctx, 0x3E793Cu, gen::fn_sub_3C7850_003c7850);
            if (v0 == 0) {
                // 0x003e794c
                charge(ctx, 14);
                jal(ctx, 0x3E794Cu, gen::fn_sub_3C7700_003c7700);
                v0 = 39;
                sw(v0, s2, shop::kShopState);
                lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
                jal(ctx, 0x3E7960u, gen::fn_nmObjPayloadWord12_003c5460);
                a0 = v0;
                a1 = 1;
                a2 = a1;
                jal(ctx, 0x3E7974u, gen::fn_sub_3E0C20_003e0c20);
            }
            goto L_003e86a0;
        case 0x3E793Cu:  // table[32]: state 32 -- wait -> 39
            goto L_003e793c;
        case 0x3E7984u:  // table[33]: state 33 -- message 20 -> 34
            // 0x003e7984
            charge(ctx, 5);
            v0 = 34;
            sw(v0, s2, shop::kShopState);
            a0 = 20;
            jal(ctx, 0x3E7990u, gen::fn_msgWinRequestMessage_003c7430);
        L_003e7998:
            charge(ctx, 4);
            jal(ctx, 0x3E7998u, gen::fn_sub_3C7850_003c7850);
            if (v0 == 0) {
                // 0x003e79a8
                charge(ctx, 6);
                jal(ctx, 0x3E79A8u, gen::fn_sub_3C7700_003c7700);
                v0 = 35;
                sw(v0, s2, shop::kShopState);
            }
            goto L_003e86a0;
        case 0x3E7998u:  // table[34]: state 34 -- wait -> 35
            goto L_003e7998;
        case 0x3E79C0u:  // table[35]: state 35 -- 300 - sub_16F490(1) > 0 -> 37, else message 22 -> 36
            // 0x003e79c0
            charge(ctx, 7);
            a0 = 1;
            jal(ctx, 0x3E79C4u, gen::fn_sub_16F490_0016f490);
            v1 = 300;
            v0 = subu(v1, v0);
            if (i64(v0) > 0) {
                // 0x003e79ec
                charge(ctx, 4);
                v0 = 37;
                sw(v0, s2, shop::kShopState);
            } else {
                // 0x003e79dc
                charge(ctx, 4);
                v0 = 36;
                sw(v0, s2, shop::kShopState);
                // 0x003e79fc
                charge(ctx, 3);
                a0 = 22;
                jal(ctx, 0x3E7A00u, gen::fn_msgWinRequestMessage_003c7430);
            L_003e7a08:
                charge(ctx, 4);
                jal(ctx, 0x3E7A08u, gen::fn_sub_3C7850_003c7850);
                if (v0 == 0) {
                    // 0x003e7a18
                    charge(ctx, 6);
                    jal(ctx, 0x3E7A18u, gen::fn_sub_3C7700_003c7700);
                    v0 = 39;
                    sw(v0, s2, shop::kShopState);
                }
            }
            goto L_003e86a0;
        case 0x3E7A08u:  // table[36]: state 36 -- wait -> 39
            goto L_003e7a08;
        case 0x3E7A30u:  // table[37]: state 37 -- the reward (sub_17C220 / sub_1830C0 / sub_3F0D60), message 23 / 24 -> 38
            // 0x003e7a30
            charge(ctx, 29);
            v0 = 38;
            sw(v0, s2, shop::kShopState);
            a0 = addiu(sp, 0x60);
            jal(ctx, 0x3E7A3Cu, gen::fn_sub_17C220_0017c220);
            a0 = addiu(sp, 0x64);
            jal(ctx, 0x3E7A48u, gen::fn_sub_1830C0_001830c0);
            jal(ctx, 0x3E7A50u, gen::fn_sub_17C190_0017c190);
            lh(a1, sp, 0x78);
            lw(a0, s2, shop::kShopType);
            jal(ctx, 0x3E7A60u, gen::fn_sub_3F0D60_003f0d60);
            lbu(a1, sp, 0x6C);
            a0 = 0;
            a2 = 17;
            jal(ctx, 0x3E7A74u, gen::fn_sub_3C7C20_003c7c20);
            lhu(a1, sp, 0x64);
            a0 = 1;
            a2 = 17;
            jal(ctx, 0x3E7A88u, gen::fn_sub_3C7C20_003c7c20);
            lhu(a0, sp, 0x64);
            jal(ctx, 0x3E7A94u, gen::fn_sub_401890_00401890);
            if (v0 == 0) {
                // 0x003e7ab8
                charge(ctx, 3);
                a0 = 24;
                jal(ctx, 0x3E7ABCu, gen::fn_msgWinRequestMessage_003c7430);
            } else {
                // 0x003e7aa4
                charge(ctx, 5);
                a0 = 23;
                jal(ctx, 0x3E7AA8u, gen::fn_msgWinRequestMessage_003c7430);
            }
            // 0x003e7ac4
            charge(ctx, 3);
            lhu(a0, sp, 0x64);
            jal(ctx, 0x3E7AC8u, gen::fn_sub_401950_00401950);
        L_003e7ad0:
            charge(ctx, 4);
            jal(ctx, 0x3E7AD0u, gen::fn_sub_3C7850_003c7850);
            if (v0 == 0) {
                // 0x003e7ae0
                charge(ctx, 6);
                jal(ctx, 0x3E7AE0u, gen::fn_sub_3C7700_003c7700);
                v0 = 39;
                sw(v0, s2, shop::kShopState);
            }
            goto L_003e86a0;
        case 0x3E7AD0u:  // table[38]: state 38 -- wait -> 39
            goto L_003e7ad0;
        case 0x3E7AF8u:  // table[39]: state 39 -- leave? (flag 4639 / sub_17D610) -> 40, else the menu (42)
            // 0x003e7af8
            charge(ctx, 6);
            a0 = 4639;
            jal(ctx, 0x3E7AFCu, gen::fn_datGetFlag_0016f190);
            a1 = 1;
            if (v0 == a1) {
                // 0x003e7b10
                charge(ctx, 3);
                a0 = 5127;
                jal(ctx, 0x3E7B14u, gen::fn_datSetFlag_0016f1f0);
            }
            // 0x003e7b1c
            charge(ctx, 5);
            lw(a0, s2, shop::kShopType);
            jal(ctx, 0x3E7B20u, gen::fn_sub_17D610_0017d610);
            if (v0 == 0) {
                // 0x003e7b40
                charge(ctx, 8);
                v0 = 42;
                sw(v0, s2, shop::kShopState);
                a0 = 0;
                a1 = 0;
                jal(ctx, 0x3E7B50u, gen::fn_sub_3EFDE0_003efde0);
            } else {
                // 0x003e7b30
                charge(ctx, 4);
                v0 = 40;
                sw(v0, s2, shop::kShopState);
            }
            goto L_003e86a0;
        case 0x3E7B60u:  // table[40]: state 40 -- message 3 -> 41
            // 0x003e7b60
            charge(ctx, 5);
            v0 = 41;
            sw(v0, s2, shop::kShopState);
            a0 = 3;
            jal(ctx, 0x3E7B6Cu, gen::fn_msgWinRequestMessage_003c7430);
        L_003e7b74:
            charge(ctx, 4);
            jal(ctx, 0x3E7B74u, gen::fn_sub_3C7850_003c7850);
            if (v0 == 0) {
                // 0x003e7b84
                charge(ctx, 6);
                jal(ctx, 0x3E7B84u, gen::fn_sub_3C7700_003c7700);
                v0 = 39;
                sw(v0, s2, shop::kShopState);
            }
            goto L_003e86a0;
        case 0x3E7B74u:  // table[41]: state 41 -- wait -> 39
            goto L_003e7b74;
        case 0x3E7B9Cu:  // table[42]: state 42 -- open the ROOT menu (sub_3E8E20) -> 43
            // 0x003e7b9c
            charge(ctx, 4);
            lw(v0, s2, shop::kShopFlags);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x003e7be0
                charge(ctx, 4);
                lw(v1, s2, shop::kShopType);
                v0 = 8;
                if (v1 == v0) {
                    // 0x003e7bf0
                    charge(ctx, 6);
                    a0 = addiu(s2, 140);
                    a1 = 4;
                    jal(ctx, 0x3E7BF8u, gen::fn_sub_403E40_00403e40);
                    if (v0 == 0) {
                        goto L_003e7c3c;
                    }
                    // 0x003e7c08
                    charge(ctx, 5);
                    a0 = 0;
                    jal(ctx, 0x3E7C0Cu, gen::fn_sub_3EFE60_003efe60);
                    if (v0 == 0) {
                        // 0x003e7c1c
                        charge(ctx, 8);
                        a0 = 0;
                        a1 = 1;
                        jal(ctx, 0x3E7C24u, gen::fn_sub_3EFDE0_003efde0);
                        v0 = 13;
                        sw(v0, s2, shop::kShopState);
                    }
                    goto L_003e86a0;
                }
            L_003e7c3c:
                charge(ctx, 5);
                lw(a0, s2, shop::kShopType);
                jal(ctx, 0x3E7C40u, gen::fn_sub_17D610_0017d610);
                if (v0 == 0) {
                    // 0x003e7c74
                    charge(ctx, 5);
                    v0 = 43;
                    sw(v0, s2, shop::kShopState);
                    a0 = s2;
                    jal(ctx, 0x3E7C80u, gen::fn_sub_3E8E20_003e8e20);
                L_003e7c88:
                    charge(ctx, 6);
                    a0 = s2;
                    jal(ctx, 0x3E7C8Cu, gen::fn_sub_3E8FF0_003e8ff0);
                    at = sltiu(v0, 14);
                    if (at != 0) {
                        // 0x003e7ca0
                        charge(ctx, 7);
                        v1 = 0x7C0000;
                        v1 = addiu(v1, -18016);  // &0x7BB9A0
                        v0 = sll(v0, 2);
                        v0 = addu(v0, v1);
                        lw(v0, v0, 0);
                        switch (v0.u()) {
                        case 0x3E7CBCu:  // table[1]: state 1 -- start: add the BG step -> 4
                            // 0x003e7cbc
                            charge(ctx, 8);
                            v0 = 44;
                            sw(v0, s2, shop::kShopState);
                            a0 = 0;
                            a1 = 2;
                            jal(ctx, 0x3E7CCCu, gen::fn_sub_3EFDE0_003efde0);
                            break;
                        case 0x3E7CDCu:  // table[5]: state 5 -- wait for the load script -> 6
                            // 0x003e7cdc
                            charge(ctx, 8);
                            v0 = 45;
                            sw(v0, s2, shop::kShopState);
                            a0 = 0;
                            a1 = 2;
                            jal(ctx, 0x3E7CECu, gen::fn_sub_3EFDE0_003efde0);
                            break;
                        case 0x3E7CFCu:  // table[6]: state 6 -- set-up: MONEY / SUBTITLE steps, message window, lineup flag 4, BGM, the once-only intro (-> 7) else -> 9
                            // 0x003e7cfc
                            charge(ctx, 8);
                            v0 = 46;
                            sw(v0, s2, shop::kShopState);
                            a0 = 0;
                            a1 = 2;
                            jal(ctx, 0x3E7D0Cu, gen::fn_sub_3EFDE0_003efde0);
                            break;
                        case 0x3E7D1Cu:  // table[2]: state 2 -- leaving: fade out (BGM for types 0-2 / 4) -> 3
                            // 0x003e7d1c
                            charge(ctx, 8);
                            v0 = 48;
                            sw(v0, s2, shop::kShopState);
                            a0 = 0;
                            a1 = 3;
                            jal(ctx, 0x3E7D2Cu, gen::fn_sub_3EFDE0_003efde0);
                            break;
                        case 0x3E7D3Cu:  // table[3]: state 3 -- wait for the fade, then return 1 (the sequence ends)
                            // 0x003e7d3c
                            charge(ctx, 4);
                            lw(v1, s2, shop::kShopType);
                            v0 = 8;
                            if (v1 != v0) {
                                // 0x003e7d6c
                                charge(ctx, 8);
                                v0 = 52;
                                sw(v0, s2, shop::kShopState);
                                a0 = 0;
                                a1 = 1;
                                jal(ctx, 0x3E7D7Cu, gen::fn_sub_3EFDE0_003efde0);
                            } else {
                                // 0x003e7d4c
                                charge(ctx, 8);
                                v0 = 50;
                                sw(v0, s2, shop::kShopState);
                                a0 = 0;
                                a1 = 1;
                                jal(ctx, 0x3E7D5Cu, gen::fn_sub_3EFDE0_003efde0);
                            }
                            break;
                        case 0x3E7D8Cu:  // table[4]: state 4 -- add the LOAD step -> 5
                            // 0x003e7d8c
                            charge(ctx, 8);
                            v0 = 54;
                            sw(v0, s2, shop::kShopState);
                            a0 = 0;
                            a1 = 1;
                            jal(ctx, 0x3E7D9Cu, gen::fn_sub_3EFDE0_003efde0);
                            break;
                        case 0x3E7DACu:  // table[8]: state 8 -- wait (sub_3C83B0) -> 9
                            // 0x003e7dac
                            charge(ctx, 8);
                            v0 = 69;
                            sw(v0, s2, shop::kShopState);
                            a0 = 0;
                            a1 = 6;
                            jal(ctx, 0x3E7DBCu, gen::fn_sub_3EFDE0_003efde0);
                            break;
                        case 0x3E7DCCu:  // table[9]: state 9 -- the greeting (sub_3F0830) -> 10, none -> 13
                            // 0x003e7dcc
                            charge(ctx, 8);
                            v0 = 71;
                            sw(v0, s2, shop::kShopState);
                            a0 = 0;
                            a1 = 7;
                            jal(ctx, 0x3E7DDCu, gen::fn_sub_3EFDE0_003efde0);
                            break;
                        case 0x3E7DECu:  // table[7]: state 7 -- wait for the intro message -> 8
                            // 0x003e7dec
                            charge(ctx, 6);
                            a0 = 0;
                            jal(ctx, 0x3E7DF0u, gen::fn_sub_402480_00402480);
                            v1 = si(-1);
                            if (v0 != v1) {
                                // 0x003e7e44
                                charge(ctx, 4);
                                jal(ctx, 0x3E7E44u, gen::fn_sub_3FE2B0_003fe2b0);
                                if (v0 != 0) {
                                    // 0x003e7e94
                                    charge(ctx, 8);
                                    v0 = 63;
                                    sw(v0, s2, shop::kShopState);
                                    a0 = 0;
                                    a1 = 10;
                                    jal(ctx, 0x3E7EA4u, gen::fn_sub_3EFDE0_003efde0);
                                } else {
                                    // 0x003e7e54
                                    charge(ctx, 16);
                                    v0 = 67;
                                    sw(v0, s2, shop::kShopState);
                                    a0 = 0;
                                    a1 = 1;
                                    jal(ctx, 0x3E7E64u, gen::fn_sub_3EFDE0_003efde0);
                                    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
                                    jal(ctx, 0x3E7E70u, gen::fn_nmObjPayloadWord12_003c5460);
                                    a0 = v0;
                                    a1 = 0;
                                    a2 = 1;
                                    jal(ctx, 0x3E7E84u, gen::fn_sub_3E0C20_003e0c20);
                                }
                            } else {
                                // 0x003e7e04
                                charge(ctx, 16);
                                v0 = 65;
                                sw(v0, s2, shop::kShopState);
                                a0 = 0;
                                a1 = 1;
                                jal(ctx, 0x3E7E14u, gen::fn_sub_3EFDE0_003efde0);
                                lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
                                jal(ctx, 0x3E7E20u, gen::fn_nmObjPayloadWord12_003c5460);
                                a0 = v0;
                                a1 = 0;
                                a2 = 1;
                                jal(ctx, 0x3E7E34u, gen::fn_sub_3E0C20_003e0c20);
                            }
                            break;
                        case 0x3E7EB4u:  // table[10]: state 10 -- wait for the greeting; a lineup -> 11 else 13
                            // 0x003e7eb4
                            charge(ctx, 8);
                            v0 = 73;
                            sw(v0, s2, shop::kShopState);
                            a0 = 0;
                            a1 = 1;
                            jal(ctx, 0x3E7EC4u, gen::fn_sub_3EFDE0_003efde0);
                            break;
                        case 0x3E7ED4u:  // table[11]: state 11 -- message 1 -> 12
                            // 0x003e7ed4
                            charge(ctx, 8);
                            v0 = 75;
                            sw(v0, s2, shop::kShopState);
                            a0 = 0;
                            a1 = 1;
                            jal(ctx, 0x3E7EE4u, gen::fn_sub_3EFDE0_003efde0);
                            break;
                        case 0x3E7EF4u:  // table[12]: state 12 -- wait -> 13
                            // 0x003e7ef4
                            charge(ctx, 8);
                            v0 = 77;
                            sw(v0, s2, shop::kShopState);
                            a0 = 0;
                            a1 = 1;
                            jal(ctx, 0x3E7F04u, gen::fn_sub_3EFDE0_003efde0);
                            break;
                        case 0x3E7F14u:  // table[13]: state 13 -- the hub: party requests (type 8) / the antique offer (type 4) -> 14 / 18 / 31 / 33, else 39
                            // 0x003e7f14
                            charge(ctx, 8);
                            v0 = 79;
                            sw(v0, s2, shop::kShopState);
                            a0 = 0;
                            a1 = 1;
                            jal(ctx, 0x3E7F24u, gen::fn_sub_3EFDE0_003efde0);
                            break;
                        case 0x3E86A0u:  // table[0]
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, v0.u());
                            return;
                        }
                    }
                } else {
                    // 0x003e7c50
                    charge(ctx, 5);
                    a0 = 0;
                    jal(ctx, 0x3E7C54u, gen::fn_sub_3EFE60_003efe60);
                    if (v0 == 0) {
                        // 0x003e7c64
                        charge(ctx, 4);
                        v0 = 40;
                        sw(v0, s2, shop::kShopState);
                    }
                }
            } else {
                // 0x003e7bac
                charge(ctx, 5);
                a0 = 0;
                jal(ctx, 0x3E7BB0u, gen::fn_sub_3EFE60_003efe60);
                if (v0 == 0) {
                    // 0x003e7bc0
                    charge(ctx, 8);
                    a0 = 0;
                    a1 = 1;
                    jal(ctx, 0x3E7BC8u, gen::fn_sub_3EFDE0_003efde0);
                    v0 = 56;
                    sw(v0, s2, shop::kShopState);
                }
            }
            goto L_003e86a0;
        case 0x3E7C88u:  // table[43]: state 43 -- poll the ROOT menu: choice 1..13 -> 44 / 48 / 50 / 52 / 54 / 45 / 46 / 63..79
            goto L_003e7c88;
        case 0x3E7F34u:  // table[44, 45, 46]
            // 0x003e7f34
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x3E7F38u, gen::fn_sub_3E97F0_003e97f0);
            v0 = 47;
            sw(v0, s2, shop::kShopState);
        L_003e7f48:
            charge(ctx, 6);
            a0 = s2;
            jal(ctx, 0x3E7F4Cu, gen::fn_sub_3E98B0_003e98b0);
            v1 = si(-1);
            if (v0 != v1) {
                // 0x003e7f60
                charge(ctx, 8);
                v0 = 42;
                sw(v0, s2, shop::kShopState);
                a0 = 0;
                a1 = 4;
                jal(ctx, 0x3E7F70u, gen::fn_sub_3EFDE0_003efde0);
            }
            goto L_003e86a0;
        case 0x3E7F48u:  // table[47]: state 47 -- poll BUY -> 42
            goto L_003e7f48;
        case 0x3E7F80u:  // table[48]: state 48 -- open SELL -> 49
            // 0x003e7f80
            charge(ctx, 5);
            v0 = 49;
            sw(v0, s2, shop::kShopState);
            a0 = s2;
            jal(ctx, 0x3E7F8Cu, gen::fn_sub_3EA600_003ea600);
        L_003e7f94:
            charge(ctx, 6);
            a0 = s2;
            jal(ctx, 0x3E7F98u, gen::fn_sub_3EA6B0_003ea6b0);
            v1 = si(-1);
            if (v0 != v1) {
                // 0x003e7fac
                charge(ctx, 8);
                v0 = 42;
                sw(v0, s2, shop::kShopState);
                a0 = 0;
                a1 = 5;
                jal(ctx, 0x3E7FBCu, gen::fn_sub_3EFDE0_003efde0);
            }
            goto L_003e86a0;
        case 0x3E7F94u:  // table[49]: state 49 -- poll SELL -> 42
            goto L_003e7f94;
        case 0x3E7FCCu:  // table[50]: state 50 -- open the list of sub_3EDDD0 -> 51
            // 0x003e7fcc
            charge(ctx, 5);
            v0 = 51;
            sw(v0, s2, shop::kShopState);
            a0 = s2;
            jal(ctx, 0x3E7FD8u, gen::fn_sub_3EDDD0_003eddd0);
        L_003e7fe0:
            charge(ctx, 6);
            a0 = s2;
            jal(ctx, 0x3E7FE4u, gen::fn_sub_3EDE80_003ede80);
            v1 = si(-1);
            if (v0 != v1) {
                // 0x003e7ff8
                charge(ctx, 8);
                v0 = 42;
                sw(v0, s2, shop::kShopState);
                a0 = 0;
                a1 = 0;
                jal(ctx, 0x3E8008u, gen::fn_sub_3EFDE0_003efde0);
            }
            goto L_003e86a0;
        case 0x3E7FE0u:  // table[51]: state 51 -- poll it -> 42
            goto L_003e7fe0;
        case 0x3E8018u:  // table[52]: state 52 -- open TALK (when the BG is idle) -> 53
            // 0x003e8018
            charge(ctx, 5);
            a0 = 0;
            jal(ctx, 0x3E801Cu, gen::fn_sub_3EFE60_003efe60);
            if (v0 == 0) {
                // 0x003e802c
                charge(ctx, 5);
                v0 = 53;
                sw(v0, s2, shop::kShopState);
                a0 = s2;
                jal(ctx, 0x3E8038u, gen::fn_sub_3EE310_003ee310);
            L_003e8040:
                charge(ctx, 6);
                a0 = s2;
                jal(ctx, 0x3E8044u, gen::fn_sub_3EE3D0_003ee3d0);
                v1 = si(-1);
                if (v0 != v1) {
                    // 0x003e8058
                    charge(ctx, 6);
                    v0 = 42;
                    sw(v0, s2, shop::kShopState);
                    lw(v0, s2, shop::kShopFlags);
                    v0 = v0 & 0x1;
                    if (v0 == 0) {
                        // 0x003e8070
                        charge(ctx, 6);
                        a0 = 0;
                        a1 = 0;
                        jal(ctx, 0x3E8078u, gen::fn_sub_3EFDE0_003efde0);
                    }
                }
            }
            goto L_003e86a0;
        case 0x3E8040u:  // table[53]: state 53 -- poll TALK -> 42
            goto L_003e8040;
        case 0x3E8088u:  // table[54]: state 54 -- -> 55, then (falling into 55) -> 2 in the same frame
            // 0x003e8088
            charge(ctx, 2);
            v0 = 55;
            sw(v0, s2, shop::kShopState);
        L_003e8090:
            charge(ctx, 4);
            v0 = 2;
            sw(v0, s2, shop::kShopState);
            goto L_003e86a0;
        case 0x3E8090u:  // table[55]: state 55 -- -> 2 (leave)
            goto L_003e8090;
        case 0x3E80A0u:  // table[56]: state 56 -- the shop link: message sub_3F12A0(type, 1) -> 57 / 58
            // 0x003e80a0
            charge(ctx, 16);
            v0 = 57;
            sw(v0, s2, shop::kShopState);
            lw(v1, s2, shop::kShopFlags);
            v0 = si(-2);
            v0 = v1 & v0;
            sw(v0, s2, shop::kShopFlags);
            lw(a0, s2, shop::kShopType);
            jal(ctx, 0x3E80BCu, gen::fn_sub_3F1520_003f1520);
            lw(a0, s2, shop::kShopType);
            a1 = 1;
            jal(ctx, 0x3E80CCu, gen::fn_sub_3F12A0_003f12a0);
            v1 = si(-1);
            if (v0 != v1) {
                // 0x003e80f0
                charge(ctx, 3);
                a0 = v0;
                jal(ctx, 0x3E80F4u, gen::fn_msgWinRequestMessage_003c7430);
            L_003e80fc:
                charge(ctx, 4);
                jal(ctx, 0x3E80FCu, gen::fn_sub_3C7850_003c7850);
                if (v0 == 0) {
                    // 0x003e810c
                    charge(ctx, 6);
                    jal(ctx, 0x3E810Cu, gen::fn_sub_3C7700_003c7700);
                    v0 = 58;
                    sw(v0, s2, shop::kShopState);
                }
            } else {
                // 0x003e80e0
                charge(ctx, 4);
                v0 = 58;
                sw(v0, s2, shop::kShopState);
            }
            goto L_003e86a0;
        case 0x3E80FCu:  // table[57]: state 57 -- wait -> 58
            goto L_003e80fc;
        case 0x3E8124u:  // table[58]: state 58 -- start the link task (sub_3A2090) -> 59
            // 0x003e8124
            charge(ctx, 5);
            s1 = si(-1);
            s0 = 1;
            lw(v1, s2, shop::kShopType);
            if (v1 != 0) {
                // 0x003e8144
                charge(ctx, 3);
                v0 = 4;
                if (v1 != v0) {
                    // 0x003e815c
                    charge(ctx, 3);
                    v0 = 8;
                    if (v1 == v0) {
                        // 0x003e8168
                        charge(ctx, 1);
                        s1 = 2;
                    }
                } else {
                    // 0x003e8150
                    charge(ctx, 3);
                    s1 = 3;
                }
            } else {
                // 0x003e8138
                charge(ctx, 3);
                s1 = 15;
            }
            // 0x003e816c
            charge(ctx, 3);
            v0 = si(-1);
            if (s1 == v0) {
                // 0x003e8178
                charge(ctx, 5);
                a0 = 0x6A0000;
                a0 = addiu(a0, 27384);  // "fclShop.c"
                a1 = 1932;
                jal(ctx, 0x3E8184u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x003e818c
            charge(ctx, 6);
            lw(a0, s2, shop::kShopType);
            jal(ctx, 0x3E8190u, gen::fn_sub_3F03E0_003f03e0);
            v1 = 1;
            if (v0 == v1) {
                // 0x003e81a4
                charge(ctx, 1);
                s0 = 0;
            }
            // 0x003e81a8
            charge(ctx, 9);
            a0 = 0;
            a1 = s1;
            a2 = s0;
            a3 = 3072;
            jal(ctx, 0x3E81B8u, gen::fn_sub_3A2090_003a2090);
            sw(v0, s2, shop::kShopSubTask);
            v0 = 59;
            sw(v0, s2, shop::kShopState);
        L_003e81cc:
            charge(ctx, 6);
            lw(a0, s2, shop::kShopSubTask);
            jal(ctx, 0x3E81D0u, gen::fn_kwlnTaskGetState_00195290);
            v1 = 3;
            if (v0 == v1) {
                // 0x003e81e4
                charge(ctx, 4);
                v0 = 60;
                sw(v0, s2, shop::kShopState);
            }
            goto L_003e86a0;
        case 0x3E81CCu:  // table[59]: state 59 -- wait for the task (state 3) -> 60
            goto L_003e81cc;
        case 0x3E81F4u:  // table[60]: state 60 -- message sub_3F12A0(type, 2) -> 61 / 62
            // 0x003e81f4
            charge(ctx, 9);
            v0 = 61;
            sw(v0, s2, shop::kShopState);
            lw(a0, s2, shop::kShopType);
            a1 = 2;
            jal(ctx, 0x3E8204u, gen::fn_sub_3F12A0_003f12a0);
            v1 = si(-1);
            if (v0 != v1) {
                // 0x003e8228
                charge(ctx, 3);
                a0 = v0;
                jal(ctx, 0x3E822Cu, gen::fn_msgWinRequestMessage_003c7430);
            L_003e8234:
                charge(ctx, 4);
                jal(ctx, 0x3E8234u, gen::fn_sub_3C7850_003c7850);
                if (v0 == 0) {
                    // 0x003e8244
                    charge(ctx, 6);
                    jal(ctx, 0x3E8244u, gen::fn_sub_3C7700_003c7700);
                    v0 = 62;
                    sw(v0, s2, shop::kShopState);
                }
            } else {
                // 0x003e8218
                charge(ctx, 4);
                v0 = 62;
                sw(v0, s2, shop::kShopState);
            }
            goto L_003e86a0;
        case 0x3E8234u:  // table[61]: state 61 -- wait -> 62
            goto L_003e8234;
        case 0x3E825Cu:  // table[62]: state 62 -- flag 2 -> 13, else 42
            // 0x003e825c
            charge(ctx, 4);
            lw(v0, s2, shop::kShopFlags);
            v0 = v0 & 0x2;
            if (v0 == 0) {
                // 0x003e827c
                charge(ctx, 8);
                v0 = 42;
                sw(v0, s2, shop::kShopState);
                a0 = 0;
                a1 = 0;
                jal(ctx, 0x3E828Cu, gen::fn_sub_3EFDE0_003efde0);
            } else {
                // 0x003e826c
                charge(ctx, 4);
                v0 = 13;
                sw(v0, s2, shop::kShopState);
            }
            goto L_003e86a0;
        case 0x3E829Cu:  // table[63]: state 63 -- open sub_3EAD10 -> 64
            // 0x003e829c
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x3E82A0u, gen::fn_sub_3EAD10_003ead10);
            v0 = 64;
            sw(v0, s2, shop::kShopState);
        L_003e82b0:
            charge(ctx, 6);
            a0 = s2;
            jal(ctx, 0x3E82B4u, gen::fn_sub_3EADD0_003eadd0);
            v1 = 1;
            if (v0 == v1) {
                // 0x003e82dc
                charge(ctx, 4);
                v0 = 42;
                sw(v0, s2, shop::kShopState);
            } else {
                // 0x003e82c8
                charge(ctx, 3);
                v1 = si(-1);
                if (v0 != v1) {
                    // 0x003e82d4
                    charge(ctx, 2);
                    // 0x003e82ec
                    charge(ctx, 8);
                    v0 = 42;
                    sw(v0, s2, shop::kShopState);
                    a0 = 0;
                    a1 = 13;
                    jal(ctx, 0x3E82FCu, gen::fn_sub_3EFDE0_003efde0);
                }
            }
            goto L_003e86a0;
        case 0x3E82B0u:  // table[64]: state 64 -- poll it -> 42
            goto L_003e82b0;
        case 0x3E830Cu:  // table[65]: state 65 -- message 21 with the counts of sub_402480 -> 66
            // 0x003e830c
            charge(ctx, 5);
            a0 = 0;
            jal(ctx, 0x3E8310u, gen::fn_sub_3EFE60_003efe60);
            if (v0 == 0) {
                // 0x003e8320
                charge(ctx, 30);
                v0 = 66;
                sw(v0, s2, shop::kShopState);
                a0 = addiu(sp, 0x40);
                jal(ctx, 0x3E832Cu, gen::fn_sub_402480_00402480);
                lb(a2, sp, 0x42);
                a0 = addiu(sp, 0xA0);
                a1 = addiu(gp, -21800);  // "%d"
                jal(ctx, 0x3E8340u, gen::fn_sprintf_00523ac8);
                a0 = 0;
                a1 = addiu(sp, 0xA0);
                jal(ctx, 0x3E8350u, gen::fn_sub_3C7BC0_003c7bc0);
                lb(a2, sp, 0x43);
                a0 = addiu(sp, 0xA0);
                a1 = addiu(gp, -21800);  // "%d"
                jal(ctx, 0x3E8364u, gen::fn_sprintf_00523ac8);
                a0 = 1;
                a1 = addiu(sp, 0xA0);
                jal(ctx, 0x3E8374u, gen::fn_sub_3C7BC0_003c7bc0);
                a0 = 21;
                jal(ctx, 0x3E8380u, gen::fn_msgWinRequestMessage_003c7430);
                lw(v1, s2, shop::kShopType);
                v0 = 4;
                if (v1 == v0) {
                    // 0x003e8398
                    charge(ctx, 8);
                    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
                    jal(ctx, 0x3E839Cu, gen::fn_nmObjPayloadWord12_003c5460);
                    a0 = v0;
                    a1 = 17;
                    a2 = 1;
                    jal(ctx, 0x3E83B0u, gen::fn_sub_3E0C20_003e0c20);
                }
            L_003e83b8:
                charge(ctx, 4);
                jal(ctx, 0x3E83B8u, gen::fn_sub_3C7850_003c7850);
                if (v0 == 0) {
                    // 0x003e83c8
                    charge(ctx, 12);
                    jal(ctx, 0x3E83C8u, gen::fn_sub_3C7700_003c7700);
                    v0 = 42;
                    sw(v0, s2, shop::kShopState);
                    a0 = 0;
                    a1 = 0;
                    jal(ctx, 0x3E83E0u, gen::fn_sub_3EFDE0_003efde0);
                    lw(v1, s2, shop::kShopType);
                    v0 = 4;
                    if (v1 == v0) {
                        // 0x003e83f8
                        charge(ctx, 10);
                        lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
                        jal(ctx, 0x3E83FCu, gen::fn_nmObjPayloadWord12_003c5460);
                        a0 = v0;
                        a1 = 17;
                        a2 = 0;
                        jal(ctx, 0x3E8410u, gen::fn_sub_3E0C20_003e0c20);
                    }
                }
            }
            goto L_003e86a0;
        case 0x3E83B8u:  // table[66]: state 66 -- wait -> 42
            goto L_003e83b8;
        case 0x3E8420u:  // table[67]: state 67 -- message 25 -> 68
            // 0x003e8420
            charge(ctx, 5);
            a0 = 0;
            jal(ctx, 0x3E8424u, gen::fn_sub_3EFE60_003efe60);
            if (v0 == 0) {
                // 0x003e8434
                charge(ctx, 9);
                v0 = 68;
                sw(v0, s2, shop::kShopState);
                a0 = 25;
                jal(ctx, 0x3E8440u, gen::fn_msgWinRequestMessage_003c7430);
                lw(v1, s2, shop::kShopType);
                v0 = 4;
                if (v1 == v0) {
                    // 0x003e8458
                    charge(ctx, 8);
                    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
                    jal(ctx, 0x3E845Cu, gen::fn_nmObjPayloadWord12_003c5460);
                    a0 = v0;
                    a1 = 17;
                    a2 = 1;
                    jal(ctx, 0x3E8470u, gen::fn_sub_3E0C20_003e0c20);
                }
            L_003e8478:
                charge(ctx, 4);
                jal(ctx, 0x3E8478u, gen::fn_sub_3C7850_003c7850);
                if (v0 == 0) {
                    // 0x003e8488
                    charge(ctx, 12);
                    jal(ctx, 0x3E8488u, gen::fn_sub_3C7700_003c7700);
                    v0 = 42;
                    sw(v0, s2, shop::kShopState);
                    a0 = 0;
                    a1 = 0;
                    jal(ctx, 0x3E84A0u, gen::fn_sub_3EFDE0_003efde0);
                    lw(v1, s2, shop::kShopType);
                    v0 = 4;
                    if (v1 == v0) {
                        // 0x003e84b8
                        charge(ctx, 10);
                        lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
                        jal(ctx, 0x3E84BCu, gen::fn_nmObjPayloadWord12_003c5460);
                        a0 = v0;
                        a1 = 17;
                        a2 = 0;
                        jal(ctx, 0x3E84D0u, gen::fn_sub_3E0C20_003e0c20);
                    }
                }
            }
            goto L_003e86a0;
        case 0x3E8478u:  // table[68]: state 68 -- wait -> 42
            goto L_003e8478;
        case 0x3E84E0u:  // table[69]: state 69 -- open sub_3EBA10 -> 70
            // 0x003e84e0
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x3E84E4u, gen::fn_sub_3EBA10_003eba10);
            v0 = 70;
            sw(v0, s2, shop::kShopState);
        L_003e84f4:
            charge(ctx, 6);
            a0 = s2;
            jal(ctx, 0x3E84F8u, gen::fn_sub_3EBAD0_003ebad0);
            v1 = si(-1);
            if (v0 != v1) {
                // 0x003e850c
                charge(ctx, 8);
                v0 = 42;
                sw(v0, s2, shop::kShopState);
                a0 = 0;
                a1 = 8;
                jal(ctx, 0x3E851Cu, gen::fn_sub_3EFDE0_003efde0);
            }
            goto L_003e86a0;
        case 0x3E84F4u:  // table[70]: state 70 -- poll it -> 42 (BG mode 8)
            goto L_003e84f4;
        case 0x3E852Cu:  // table[71]: state 71 -- open sub_3EBA10 -> 72
            // 0x003e852c
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x3E8530u, gen::fn_sub_3EBA10_003eba10);
            v0 = 72;
            sw(v0, s2, shop::kShopState);
        L_003e8540:
            charge(ctx, 6);
            a0 = s2;
            jal(ctx, 0x3E8544u, gen::fn_sub_3EBAD0_003ebad0);
            v1 = si(-1);
            if (v0 != v1) {
                // 0x003e8558
                charge(ctx, 8);
                v0 = 42;
                sw(v0, s2, shop::kShopState);
                a0 = 0;
                a1 = 9;
                jal(ctx, 0x3E8568u, gen::fn_sub_3EFDE0_003efde0);
            }
            goto L_003e86a0;
        case 0x3E8540u:  // table[72]: state 72 -- poll it -> 42 (BG mode 9)
            goto L_003e8540;
        case 0x3E8578u:  // table[73]: state 73 -- open sub_3EC090 -> 74
            // 0x003e8578
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x3E857Cu, gen::fn_sub_3EC090_003ec090);
            v0 = 74;
            sw(v0, s2, shop::kShopState);
        L_003e858c:
            charge(ctx, 6);
            a0 = s2;
            jal(ctx, 0x3E8590u, gen::fn_sub_3EC150_003ec150);
            v1 = si(-1);
            if (v0 != v1) {
                // 0x003e85a4
                charge(ctx, 8);
                v0 = 42;
                sw(v0, s2, shop::kShopState);
                a0 = 0;
                a1 = 0;
                jal(ctx, 0x3E85B4u, gen::fn_sub_3EFDE0_003efde0);
            }
            goto L_003e86a0;
        case 0x3E858Cu:  // table[74]: state 74 -- poll it -> 42
            goto L_003e858c;
        case 0x3E85C4u:  // table[75]: state 75 -- open sub_3EC6F0 -> 76
            // 0x003e85c4
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x3E85C8u, gen::fn_sub_3EC6F0_003ec6f0);
            v0 = 76;
            sw(v0, s2, shop::kShopState);
        L_003e85d8:
            charge(ctx, 6);
            a0 = s2;
            jal(ctx, 0x3E85DCu, gen::fn_sub_3EC7B0_003ec7b0);
            v1 = si(-1);
            if (v0 != v1) {
                // 0x003e85f0
                charge(ctx, 8);
                v0 = 42;
                sw(v0, s2, shop::kShopState);
                a0 = 0;
                a1 = 0;
                jal(ctx, 0x3E8600u, gen::fn_sub_3EFDE0_003efde0);
            }
            goto L_003e86a0;
        case 0x3E85D8u:  // table[76]: state 76 -- poll it -> 42
            goto L_003e85d8;
        case 0x3E8610u:  // table[77]: state 77 -- open sub_3ECD30 -> 78
            // 0x003e8610
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x3E8614u, gen::fn_sub_3ECD30_003ecd30);
            v0 = 78;
            sw(v0, s2, shop::kShopState);
        L_003e8624:
            charge(ctx, 6);
            a0 = s2;
            jal(ctx, 0x3E8628u, gen::fn_sub_3ECDF0_003ecdf0);
            v1 = si(-1);
            if (v0 != v1) {
                // 0x003e863c
                charge(ctx, 8);
                v0 = 42;
                sw(v0, s2, shop::kShopState);
                a0 = 0;
                a1 = 0;
                jal(ctx, 0x3E864Cu, gen::fn_sub_3EFDE0_003efde0);
            }
            goto L_003e86a0;
        case 0x3E8624u:  // table[78]: state 78 -- poll it -> 42
            goto L_003e8624;
        case 0x3E865Cu:  // table[79]: state 79 -- open sub_3ED380 -> 80
            // 0x003e865c
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x3E8660u, gen::fn_sub_3ED380_003ed380);
            v0 = 80;
            sw(v0, s2, shop::kShopState);
        L_003e8670:
            charge(ctx, 6);
            a0 = s2;
            jal(ctx, 0x3E8674u, gen::fn_sub_3ED420_003ed420);
            v1 = si(-1);
            if (v0 != v1) {
                // 0x003e8688
                charge(ctx, 6);
                v0 = 42;
                sw(v0, s2, shop::kShopState);
                a0 = 0;
                a1 = 0;
                jal(ctx, 0x3E8698u, gen::fn_sub_3EFDE0_003efde0);
            }
            goto L_003e86a0;
        case 0x3E8670u:  // table[80]: state 80 -- poll it -> 42
            goto L_003e8670;
        case 0x3E86A0u:  // table[0]
            goto L_003e86a0;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x003e86a4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0xC0);
        return;
    }
    goto L_003e86a0;
L_003e7310_53:
    charge(ctx, 3);
    v0 = 1;
    goto L_003e7330;
L_003e7348_59:
    charge(ctx, 10);
    lh(v0, s0, 0);
    sh(v0, s2, shop::kShopItemId);
    lw(v0, s2, shop::kShopFlags);
    v0 = v0 | 0x2;
    sw(v0, s2, shop::kShopFlags);
    v0 = 18;
    sw(v0, s2, shop::kShopState);
    v0 = 0;
    // 0x003e86a4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xC0);
    return;
L_003e787c_114:
    charge(ctx, 3);
    v0 = 1;
    goto L_003e789c;
L_003e78c8_121:
    charge(ctx, 3);
    sh(a0, v1, 0);
    goto L_003e78e4;
}

// 0x003E86C0 sub_3E86C0 -- 128 bytes; frame 0x50: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopOpenLoad] Adds the LOAD step (id 16, descriptor 0x6A6FC0 copied to the stack: two quadwords + a word) to
// the sequence; the step node goes to $a0 +76 when $a0 is not null. Returns the node.
void sub_3E86C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x003e86c0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 28608);  // &0x6A6FC0: the LOAD step descriptor
    a0 = addiu(sp, 0x20);
    v1 = 2;
    for (;;) {
        // 0x003e86e0
        charge(ctx, 7);
        lq(v0, a1, 0);
        a1 = addiu(a1, 16);
        v1 = addiu(v1, -1);
        sq(v0, a0, 0);
        a0 = addiu(a0, 16);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003e86fc
    charge(ctx, 11);
    lwc1(f0, a1, 0);
    swc1(f0, a0, 0);
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    a1 = 16;
    a2 = addiu(sp, 0x20);
    a3 = 0;
    t0 = 2;
    jal(ctx, 0x3E8718u, gen::fn_nmSequenceAddStep_003c5240);
    if (s0 != 0) {
        // 0x003e8728
        charge(ctx, 1);
        sw(v0, s0, shop::kShopStepLoad);
    }
    // 0x003e872c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003E8740 sub_3E8740 -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopPollLoad] $a0 the work: when the LOAD step's node reports finished (flag 8 at its state +20), clears +76
// and returns the step's result word; else -1.
void sub_3E8740(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e8740
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 76);
    if (a0 != 0) {
        // 0x003e875c
        charge(ctx, 3);
        lw(v0, a0, 20);
        if (v0 == 0) {
            goto L_003e8768;
        }
        // 0x003e8774
        charge(ctx, 4);
        lw(v0, v0, 20);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            // 0x003e879c
            charge(ctx, 1);
            v0 = si(-1);
        } else {
            // 0x003e8784
            charge(ctx, 6);
            jal(ctx, 0x3E8784u, gen::fn_sub_3C5470_003c5470);
            sw(zero, s0, shop::kShopStepLoad);
            lw(v0, v0, 0);
        }
        // 0x003e87a0 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_003e8768:
    charge(ctx, 3);
    v0 = si(-1);
    // 0x003e87a0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003E87C0 sub_3E87C0 -- 112 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [LOAD init] The LOAD step's init: payload +4 = the shop type, +80 = &load scripts[type] (0x6A6A90 + 8 * type: {ops,
// count}; a doubleword store), +76 = 0, phase (+8) = 0. Returns 0.
void sub_3E87C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e87c0
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    jal(ctx, 0x3E87D4u, gen::fn_nmObjPayloadWord12_003c5460);
    s0 = v0;
    a0 = s1;
    jal(ctx, 0x3E87E4u, gen::fn_sub_3C5470_003c5470);
    lw(v1, s0, shop::kShopType);
    sw(v1, v0, 4);
    a0 = sll(v1, 3);
    v1 = 0x6A0000;
    v1 = addiu(v1, 27280);  // &0x6A6A90
    v1 = addu(v1, a0);
    sw(v1, v0, 80);
    sw(zero, v0, 84);
    sw(zero, v0, 76);
    sw(zero, v0, 8);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003E8830 sub_3E8830 -- 40 bytes; frame 0x10: ra sp+0x0
// [LOAD fini] Nothing to free. Returns 0.
void sub_3E8830(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e8830
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3E883Cu, gen::fn_sub_3C5470_003c5470);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003E8860 sub_3E8860 -- 1444 bytes; frame 0xE0: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [LOAD update] Runs the shop type's load script, as many ops per frame as complete at once: phase 0 starts op [+84],
// phase 1 waits for it. Ops (8 bytes: u16 op, s8 a, s8 slot, word): 1 the persona-status tasks
// (fclMisc_CreatePsStatusTasks(task, 4 for type 8 else 3, 5, 5) -> +132; wait sub_3C9AB0); 2 the sprite bank of
// descriptor n (sub_3EFED0, sub_40E300; wait sub_40E390); 3 the message BMD "facility/msg/[AGS_]%s" from the file
// cache into slot s (+96 + 8s; K_Asserts lines 2210 / 2221); 4 a numbered file (format at 0x7CD7D8) into slot s, then
// registered with sub_3C7D80(a, data) (lines 2227 / 2233); 5 MT_Scene_Load(a, s), wait sub_3B5A10, then the camera /
// light set-up (sub_1A1150 copied, sub_4CB7F0, sub_1A4580, sub_1A0040(1, 1)); 6 the background scene (sub_3EFCE0;
// wait sub_3EFD70); 7 the PAK "facility/[AGS_]%s" (H_Cdvd_Request -> +88; wait, then +92 = node +272). After the last
// op returns nmSeqNullStep (the step ends), else 0. 'AGS_' when sub_17D800() is set.
void sub_3E8860(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x003e8860
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3E887Cu, gen::fn_nmObjPayloadWord12_003c5460);
    s2 = v0;
    a0 = s0;
    jal(ctx, 0x3E888Cu, gen::fn_sub_3C5470_003c5470);
    s1 = v0;
    for (;;) {
        // 0x003e8898
        charge(ctx, 10);
        s3 = 0;
        lw(a0, s1, shop::kLoadScript);
        lw(v0, s1, shop::kLoadIndex);
        v1 = sll(v0, 3);
        lw(v0, a0, 0);
        s0 = addu(v0, v1);
        lw(v1, s1, shop::kLoadPhase);
        v0 = 1;
        if (v1 != v0) {
            // 0x003e88c0
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x003e88c8
                charge(ctx, 2);
            L_003e8dd8:
                charge(ctx, 2);
                if (s3 == 0) {
                    break;
                }
                backedge(ctx);
                continue;
            }
            // 0x003e88d0
            charge(ctx, 4);
            lh(v0, s0, 0);
            at = sltiu(v0, 8);
            if (at != 0) {
                // 0x003e88e0
                charge(ctx, 7);
                v1 = 0x7C0000;
                v1 = addiu(v1, -17584);  // &0x7BBB50
                v0 = sll(v0, 2);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                switch (v0.u()) {
                case 0x3E88FCu:  // table[1]
                    // 0x003e88fc
                    charge(ctx, 4);
                    lw(v1, s2, shop::kShopType);
                    a1 = 4;
                    if (v1 != a1) {
                        // 0x003e890c
                        charge(ctx, 3);
                        v0 = 8;
                        if (v1 != v0) {
                            // 0x003e8918
                            charge(ctx, 2);
                            goto L_003e8940;
                        }
                        // 0x003e8920
                        charge(ctx, 8);
                        lw(a0, s2, shop::kShopTask);
                        a2 = 5;
                        a3 = a2;
                        jal(ctx, 0x3E892Cu, gen::fn_fclMisc_CreatePsStatusTasks_003c9850);
                        sw(v0, s2, shop::kShopPsStatus);
                        break;
                    }
                L_003e8940:
                    charge(ctx, 9);
                    lw(a0, s2, shop::kShopTask);
                    a1 = 3;
                    a2 = 5;
                    a3 = a2;
                    jal(ctx, 0x3E8950u, gen::fn_fclMisc_CreatePsStatusTasks_003c9850);
                    sw(v0, s2, shop::kShopPsStatus);
                    break;
                case 0x3E8964u:  // table[2]
                    // 0x003e8964
                    charge(ctx, 9);
                    lw(a0, s1, shop::kLoadType);
                    jal(ctx, 0x3E8968u, gen::fn_sub_3EFED0_003efed0);
                    a0 = v0;
                    lw(a1, s2, shop::kShopPakNode);
                    jal(ctx, 0x3E8978u, gen::fn_sub_40E300_0040e300);
                    break;
                case 0x3E8988u:  // table[3]
                    // 0x003e8988
                    charge(ctx, 6);
                    lb(v0, s0, 3);
                    v0 = sll(v0, 3);
                    v0 = addu(s2, v0);
                    lw(v0, v0, 96);
                    if (v0 != 0) {
                        // 0x003e89a0
                        charge(ctx, 5);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, 27384);  // "fclShop.c"
                        a1 = 2210;
                        jal(ctx, 0x3E89ACu, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    // 0x003e89b4
                    charge(ctx, 4);
                    jal(ctx, 0x3E89B4u, gen::fn_sub_17D800_0017d800);
                    if (v0 == 0) {
                        // 0x003e89e4
                        charge(ctx, 6);
                        a0 = addiu(sp, 0x90);
                        a1 = 0x6A0000;
                        a1 = addiu(a1, 28688);  // "facility/msg/%s"
                        lw(a2, s0, 4);
                        jal(ctx, 0x3E89F4u, gen::fn_sprintf_00523ac8);
                    } else {
                        // 0x003e89c4
                        charge(ctx, 8);
                        a0 = addiu(sp, 0x90);
                        a1 = 0x6A0000;
                        a1 = addiu(a1, 28656);  // "facility/msg/AGS_%s"
                        lw(a2, s0, 4);
                        jal(ctx, 0x3E89D4u, gen::fn_sprintf_00523ac8);
                    }
                    // 0x003e89fc
                    charge(ctx, 15);
                    s3 = 1;
                    a0 = addiu(sp, 0x90);
                    a1 = addiu(sp, 0xDC);
                    jal(ctx, 0x3E8A08u, gen::fn_H_Cdvd_CacheFindFile_001021c0);
                    lb(v1, s0, 3);
                    v1 = sll(v1, 3);
                    v1 = addu(s2, v1);
                    sw(v0, v1, 100);
                    lb(v0, s0, 3);
                    v0 = sll(v0, 3);
                    v0 = addu(s2, v0);
                    lw(v0, v0, 100);
                    if (v0 == 0) {
                        // 0x003e8a38
                        charge(ctx, 7);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, 27384);  // "fclShop.c"
                        a1 = 2221;
                        jal(ctx, 0x3E8A44u, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    break;
                case 0x3E8A54u:  // table[4]
                    // 0x003e8a54
                    charge(ctx, 6);
                    lb(v0, s0, 3);
                    v0 = sll(v0, 3);
                    v0 = addu(s2, v0);
                    lw(v0, v0, 96);
                    if (v0 != 0) {
                        // 0x003e8a6c
                        charge(ctx, 5);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, 27384);  // "fclShop.c"
                        a1 = 2227;
                        jal(ctx, 0x3E8A78u, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    // 0x003e8a80
                    charge(ctx, 20);
                    a0 = addiu(sp, 0x90);
                    a1 = addiu(gp, -21784);  // "%s"
                    lw(a2, s0, 4);
                    jal(ctx, 0x3E8A8Cu, gen::fn_sprintf_00523ac8);
                    s3 = 1;
                    a0 = addiu(sp, 0x90);
                    a1 = addiu(sp, 0xDC);
                    jal(ctx, 0x3E8AA0u, gen::fn_H_Cdvd_CacheFindFile_001021c0);
                    lb(v1, s0, 3);
                    v1 = sll(v1, 3);
                    v1 = addu(s2, v1);
                    sw(v0, v1, 100);
                    lb(v0, s0, 3);
                    v0 = sll(v0, 3);
                    v0 = addu(s2, v0);
                    lw(v0, v0, 100);
                    if (v0 == 0) {
                        // 0x003e8ad0
                        charge(ctx, 7);
                        a0 = 0x6A0000;
                        a0 = addiu(a0, 27384);  // "fclShop.c"
                        a1 = 2233;
                        jal(ctx, 0x3E8ADCu, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    break;
                case 0x3E8AECu:  // table[5]
                    // 0x003e8aec
                    charge(ctx, 6);
                    lb(a0, s0, 2);
                    lb(a1, s0, 3);
                    jal(ctx, 0x3E8AF4u, gen::fn_MT_Scene_Load_003b5760);
                    break;
                case 0x3E8B04u:  // table[6]
                    // 0x003e8b04
                    charge(ctx, 5);
                    a0 = 0;
                    jal(ctx, 0x3E8B08u, gen::fn_sub_3EFCE0_003efce0);
                    break;
                case 0x3E8B18u:  // table[7]
                    // 0x003e8b18
                    charge(ctx, 4);
                    jal(ctx, 0x3E8B18u, gen::fn_sub_17D800_0017d800);
                    if (v0 == 0) {
                        // 0x003e8b48
                        charge(ctx, 6);
                        a0 = addiu(sp, 0x90);
                        a1 = 0x6A0000;
                        a1 = addiu(a1, 28720);  // "facility/%s"
                        lw(a2, s0, 4);
                        jal(ctx, 0x3E8B58u, gen::fn_sprintf_00523ac8);
                    } else {
                        // 0x003e8b28
                        charge(ctx, 8);
                        a0 = addiu(sp, 0x90);
                        a1 = 0x6A0000;
                        a1 = addiu(a1, 28704);  // "facility/AGS_%s"
                        lw(a2, s0, 4);
                        jal(ctx, 0x3E8B38u, gen::fn_sprintf_00523ac8);
                    }
                    // 0x003e8b60
                    charge(ctx, 5);
                    a0 = addiu(sp, 0x90);
                    a1 = 1;
                    jal(ctx, 0x3E8B68u, gen::fn_H_Cdvd_Request_00100d80);
                    sw(v0, s2, shop::kShopPakNode);
                    break;
                case 0x3E8B74u:  // table[0]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v0.u());
                    return;
                }
            }
            // 0x003e8b74
            charge(ctx, 2);
            v0 = 1;
            sw(v0, s1, shop::kLoadPhase);
            goto L_003e8b7c;
        }
    L_003e8b7c:
        charge(ctx, 4);
        lh(v0, s0, 0);
        at = sltiu(v0, 8);
        if (at != 0) {
            // 0x003e8b8c
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -17616);  // &0x7BBB30
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x3E8BA8u:  // table[1]
                // 0x003e8ba8
                charge(ctx, 5);
                lw(a0, s2, shop::kShopPsStatus);
                jal(ctx, 0x3E8BACu, gen::fn_sub_3C9AB0_003c9ab0);
                if (v0 != 0) {
                    // 0x003e8bbc
                    charge(ctx, 3);
                    s3 = 1;
                }
                break;
            case 0x3E8BC8u:  // table[2]
                // 0x003e8bc8
                charge(ctx, 4);
                jal(ctx, 0x3E8BC8u, gen::fn_sub_40E390_0040e390);
                if (v0 != 0) {
                    // 0x003e8bd8
                    charge(ctx, 3);
                    s3 = 1;
                }
                break;
            case 0x3E8BE4u:  // table[3]
                // 0x003e8be4
                charge(ctx, 2);
                if (s3 == 0) {
                    // 0x003e8bec
                    charge(ctx, 8);
                    lb(v0, s0, 3);
                    v0 = sll(v0, 3);
                    v0 = addu(s2, v0);
                    lw(a0, v0, 96);
                    jal(ctx, 0x3E8BFCu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                    if (v0 != 0) {
                        goto L_003e8c0c;
                    }
                    break;
                }
            L_003e8c0c:
                charge(ctx, 6);
                lb(v0, s0, 3);
                v0 = sll(v0, 3);
                v1 = addu(s2, v0);
                lw(v0, v1, 96);
                if (v0 != 0) {
                    // 0x003e8c24
                    charge(ctx, 2);
                    lw(v0, v0, 272);
                    sw(v0, v1, 100);
                }
                // 0x003e8c2c
                charge(ctx, 3);
                s3 = 1;
                break;
            case 0x3E8C38u:  // table[4]
                // 0x003e8c38
                charge(ctx, 2);
                if (s3 == 0) {
                    // 0x003e8c40
                    charge(ctx, 8);
                    lb(v0, s0, 3);
                    v0 = sll(v0, 3);
                    v0 = addu(s2, v0);
                    lw(a0, v0, 96);
                    jal(ctx, 0x3E8C50u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                    if (v0 != 0) {
                        goto L_003e8c60;
                    }
                    break;
                }
            L_003e8c60:
                charge(ctx, 6);
                lb(v0, s0, 3);
                v0 = sll(v0, 3);
                v1 = addu(s2, v0);
                lw(v0, v1, 96);
                if (v0 != 0) {
                    // 0x003e8c78
                    charge(ctx, 2);
                    lw(v0, v0, 272);
                    sw(v0, v1, 100);
                }
                // 0x003e8c80
                charge(ctx, 10);
                s3 = 1;
                lb(a0, s0, 2);
                lb(v0, s0, 3);
                v0 = sll(v0, 3);
                v0 = addu(s2, v0);
                lw(a1, v0, 100);
                jal(ctx, 0x3E8C98u, gen::fn_sub_3C7D80_003c7d80);
                break;
            case 0x3E8CA8u:  // table[5]
                // 0x003e8ca8
                charge(ctx, 4);
                jal(ctx, 0x3E8CA8u, gen::fn_sub_3B5A10_003b5a10);
                if (v0 != 0) {
                    // 0x003e8cb8
                    charge(ctx, 4);
                    jal(ctx, 0x3E8CB8u, gen::fn_sub_1A1150_001a1150);
                    a2 = addiu(sp, 0x50);
                    a1 = 8;
                    for (;;) {
                        // 0x003e8cc8
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
                    // 0x003e8cec
                    charge(ctx, 23);
                    jal(ctx, 0x3E8CECu, gen::fn_sub_198590_00198590);
                    lw(a0, v0, 4);
                    a1 = addiu(sp, 0x50);
                    a2 = 0;
                    jal(ctx, 0x3E8D00u, gen::fn_sub_4CB7F0_004cb7f0);
                    jal(ctx, 0x3E8D08u, gen::fn_sub_198590_00198590);
                    s0 = v0;
                    jal(ctx, 0x3E8D14u, gen::fn_sub_1A1190_001a1190);
                    a0 = s0;
                    mov_s(f12, f0);
                    jal(ctx, 0x3E8D24u, gen::fn_sub_1A4580_001a4580);
                    a0 = 1;
                    a1 = a0;
                    jal(ctx, 0x3E8D34u, gen::fn_sub_1A0040_001a0040);
                    s3 = 1;
                }
                break;
            case 0x3E8D48u:  // table[6]
                // 0x003e8d48
                charge(ctx, 5);
                a0 = 0;
                jal(ctx, 0x3E8D4Cu, gen::fn_sub_3EFD70_003efd70);
                if (v0 != 0) {
                    // 0x003e8d5c
                    charge(ctx, 3);
                    s3 = 1;
                }
                break;
            case 0x3E8D68u:  // table[7]
                // 0x003e8d68
                charge(ctx, 2);
                if (s3 == 0) {
                    // 0x003e8d70
                    charge(ctx, 5);
                    lw(a0, s2, shop::kShopPakNode);
                    jal(ctx, 0x3E8D74u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                    if (v0 != 0) {
                        goto L_003e8d84;
                    }
                    break;
                }
            L_003e8d84:
                charge(ctx, 3);
                lw(v0, s2, shop::kShopPakNode);
                if (v0 != 0) {
                    // 0x003e8d90
                    charge(ctx, 2);
                    lw(v0, v0, 272);
                    sw(v0, s2, shop::kShopPakData);
                }
                // 0x003e8d98
                charge(ctx, 1);
                s3 = 1;
                break;
            case 0x3E8D9Cu:  // table[0]
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
        // 0x003e8d9c
        charge(ctx, 2);
        if (s3 == 0) {
            goto L_003e8dd8;
        }
        // 0x003e8da4
        charge(ctx, 8);
        lw(v0, s1, shop::kLoadIndex);
        v1 = addiu(v0, 1);
        sw(v1, s1, shop::kLoadIndex);
        lw(v0, s1, shop::kLoadScript);
        lw(v0, v0, 4);
        v0 = slt(v1, v0);
        if (v0 == 0) {
            goto L_003e8dc4_59;
        }
        // 0x003e8dd4
        charge(ctx, 1);
        sw(zero, s1, shop::kLoadPhase);
        goto L_003e8dd8;
    }
    // 0x003e8de0
    charge(ctx, 1);
    v0 = 0;
    // 0x003e8de4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xE0);
    return;
L_003e8dc4_59:
    charge(ctx, 4);
    v0 = 0x3C0000;
    v0 = addiu(v0, 20848);  // &nmSeqNullStep
    // 0x003e8de4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xE0);
}

// 0x003E8E10 sub_3E8E10 -- 12 bytes; leaf frame (no stack)
// [LOAD draw] Nothing to draw. Returns 0.
void sub_3E8E10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003e8e10
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x003E8E20 sub_3E8E20 -- 460 bytes; frame 0x70: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopOpenRoot] Opens the ROOT menu (K_Assert fclShop.c:2338 on a null work): element 4 out (sub_3E0C20(work, 4,
// 0)); without a ROOT step adds one (id 1, descriptor 0x6A7040) into +16 and, for the antique shop, element 17; with
// one, re-shows it: type 8 releases its command list, refreshes (sub_3C6EE0) and rebuilds the quest background
// (sub_40C310 / sub_40C490); the others release and refresh the menu rows (nmCmdListRelease, sub_3FFE00, sub_3C6EE0),
// set the step's flag 2 and bring element 0 in. Returns the step node.
void sub_3E8E20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x003e8e20
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    if (s2 == 0) {
        // 0x003e8e40
        charge(ctx, 5);
        a0 = 0x6A0000;
        a0 = addiu(a0, 27384);  // "fclShop.c"
        a1 = 2338;
        jal(ctx, 0x3E8E4Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003e8e54
    charge(ctx, 11);
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    jal(ctx, 0x3E8E58u, gen::fn_nmObjPayloadWord12_003c5460);
    a0 = v0;
    a1 = 4;
    a2 = 0;
    jal(ctx, 0x3E8E6Cu, gen::fn_sub_3E0C20_003e0c20);
    lw(s1, s2, shop::kShopStepRoot);
    if (s1 != 0) {
        // 0x003e8f10
        charge(ctx, 8);
        a0 = s1;
        jal(ctx, 0x3E8F14u, gen::fn_sub_3C5470_003c5470);
        s0 = v0;
        lw(v1, s2, shop::kShopType);
        v0 = 8;
        if (v1 != v0) {
            // 0x003e8f74
            charge(ctx, 22);
            lw(v0, s0, 12);
            lw(a0, v0, 0);
            jal(ctx, 0x3E8F7Cu, gen::fn_nmCmdListRelease_003c6ec0);
            lw(a0, s0, 12);
            jal(ctx, 0x3E8F88u, gen::fn_sub_3FFE00_003ffe00);
            lw(v0, s0, 12);
            lw(a0, v0, 0);
            jal(ctx, 0x3E8F98u, gen::fn_sub_3C6EE0_003c6ee0);
            lw(v0, s0, shop::kStepFlags);
            v0 = v0 | 0x2;
            sw(v0, s0, shop::kStepFlags);
            lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
            jal(ctx, 0x3E8FB0u, gen::fn_nmObjPayloadWord12_003c5460);
            a0 = v0;
            a1 = 0;
            a2 = 1;
            jal(ctx, 0x3E8FC4u, gen::fn_sub_3E0C20_003e0c20);
        } else {
            // 0x003e8f30
            charge(ctx, 17);
            lw(v0, s0, 16);
            lw(a0, v0, 12);
            jal(ctx, 0x3E8F38u, gen::fn_nmCmdListRelease_003c6ec0);
            lw(v0, s0, 16);
            lw(a0, v0, 12);
            jal(ctx, 0x3E8F48u, gen::fn_sub_3C6EE0_003c6ee0);
            lw(a0, s0, 16);
            jal(ctx, 0x3E8F54u, gen::fn_sub_40C310_0040c310);
            lw(a0, s0, 16);
            jal(ctx, 0x3E8F60u, gen::fn_sub_40C490_0040c490);
            sw(zero, s0, shop::kStepPhase);
        }
    } else {
        // 0x003e8e80
        charge(ctx, 4);
        a1 = 0x6A0000;
        a1 = addiu(a1, 28736);  // &0x6A7040: the ROOT step descriptor
        a0 = addiu(sp, 0x40);
        v1 = 2;
        for (;;) {
            // 0x003e8e90
            charge(ctx, 7);
            lq(v0, a1, 0);
            a1 = addiu(a1, 16);
            v1 = addiu(v1, -1);
            sq(v0, a0, 0);
            a0 = addiu(a0, 16);
            if (i64(v1) <= 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x003e8eac
        charge(ctx, 15);
        lwc1(f0, a1, 0);
        swc1(f0, a0, 0);
        lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
        a1 = 1;
        a2 = addiu(sp, 0x40);
        a3 = 0;
        t0 = 2;
        jal(ctx, 0x3E8EC8u, gen::fn_nmSequenceAddStep_003c5240);
        s1 = v0;
        sw(s1, s2, shop::kShopStepRoot);
        lw(v1, s2, shop::kShopType);
        v0 = 4;
        if (v1 == v0) {
            // 0x003e8ee8
            charge(ctx, 10);
            lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
            jal(ctx, 0x3E8EECu, gen::fn_nmObjPayloadWord12_003c5460);
            a0 = v0;
            a1 = 17;
            a2 = 0;
            jal(ctx, 0x3E8F00u, gen::fn_sub_3E0C20_003e0c20);
        }
    }
    // 0x003e8fcc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = s1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003E8FF0 sub_3E8FF0 -- 184 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopPollRoot] When the ROOT step finished or decided (node flag 8 or payload flag 1): element 4 in, flag 1
// cleared, returns the choice (payload +0); else -1.
void sub_3E8FF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e8ff0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, a0, 16);
    if (a0 != 0) {
        // 0x003e900c
        charge(ctx, 3);
        lw(s1, a0, 20);
        if (s1 == 0) {
            goto L_003e9018;
        }
        // 0x003e9024
        charge(ctx, 7);
        jal(ctx, 0x3E9024u, gen::fn_sub_3C5470_003c5470);
        s0 = v0;
        lw(v0, s1, 20);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            // 0x003e9040
            charge(ctx, 4);
            lw(v0, s0, shop::kStepFlags);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                goto L_003e9050;
            }
            // 0x003e908c
            charge(ctx, 1);
            v0 = si(-1);
            // 0x003e9090 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
    L_003e9050:
        charge(ctx, 15);
        lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
        jal(ctx, 0x3E9054u, gen::fn_nmObjPayloadWord12_003c5460);
        a0 = v0;
        a1 = 4;
        a2 = 1;
        jal(ctx, 0x3E9068u, gen::fn_sub_3E0C20_003e0c20);
        lw(v1, s0, shop::kStepFlags);
        v0 = si(-2);
        v0 = v1 & v0;
        sw(v0, s0, shop::kStepFlags);
        lw(v0, s0, shop::kStepResult);
        // 0x003e9090 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_003e9018:
    charge(ctx, 3);
    v0 = si(-1);
    // 0x003e9090 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003E90B0 sub_3E90B0 -- 176 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [ROOT init] Type 8: the quest menu sub_40C6F0(2) -> +16 and element 0; the others: the command menu sub_3FFE60 ->
// +12 and flag 2 (hidden until the background shows it). Returns 0.
void sub_3E90B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e90b0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3E90C4u, gen::fn_nmObjPayloadWord12_003c5460);
    s1 = v0;
    a0 = s0;
    jal(ctx, 0x3E90D4u, gen::fn_sub_3C5470_003c5470);
    s0 = v0;
    lw(a0, s1, shop::kShopType);
    v0 = 8;
    if (a0 != v0) {
        // 0x003e912c
        charge(ctx, 6);
        jal(ctx, 0x3E912Cu, gen::fn_sub_3FFE60_003ffe60);
        sw(v0, s0, 12);
        lw(v0, s0, 4);
        v0 = v0 | 0x2;
        sw(v0, s0, 4);
    } else {
        // 0x003e90f0
        charge(ctx, 15);
        a0 = 2;
        jal(ctx, 0x3E90F4u, gen::fn_sub_40C6F0_0040c6f0);
        sw(v0, s0, 16);
        lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
        jal(ctx, 0x3E9104u, gen::fn_nmObjPayloadWord12_003c5460);
        a0 = v0;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x3E9118u, gen::fn_sub_3E0C20_003e0c20);
        sw(zero, s0, 8);
    }
    // 0x003e9144 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003E94F0 sub_3E94F0 -- 508 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [ROOT update] Type 8: the quest menu's update sub_3E9200 (-1 with flag 2: close, result 4; 4: the BGM / sound
// set-up sub_1A0040 / sub_1A0150(3072..3074) and element 0; other non-zero: decided). The others, unless hidden: the
// command menu sub_4003F0 (-1: flag 2; n: decided with result n, element 0 out unless n == 3). Returns 0.
void sub_3E94F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e94f0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    jal(ctx, 0x3E9510u, gen::fn_nmObjPayloadWord12_003c5460);
    s3 = v0;
    a0 = s1;
    jal(ctx, 0x3E9520u, gen::fn_sub_3C5470_003c5470);
    s0 = v0;
    lw(v1, s3, shop::kShopType);
    v0 = 8;
    if (v1 == v0) {
        // 0x003e953c
        charge(ctx, 7);
        a0 = s2;
        a1 = s1;
        jal(ctx, 0x3E9544u, gen::fn_sub_3E9200_003e9200);
        v1 = si(-1);
        if (v0 == v1) {
            // 0x003e9568
            charge(ctx, 4);
            lw(v1, s0, shop::kStepFlags);
            v0 = v1 & 0x2;
            if (v0 != 0) {
                // 0x003e9578
                charge(ctx, 9);
                v0 = si(-3);
                v0 = v1 & v0;
                sw(v0, s0, shop::kStepFlags);
                v0 = v0 | 0x1;
                sw(v0, s0, shop::kStepFlags);
                v0 = 4;
                sw(v0, s0, shop::kStepResult);
            }
        } else {
            // 0x003e9558
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x003e9560
                charge(ctx, 2);
                // 0x003e959c
                charge(ctx, 3);
                v1 = 4;
                if (v0 != v1) {
                    // 0x003e961c
                    charge(ctx, 6);
                    lw(v1, s0, shop::kStepFlags);
                    v1 = v1 | 0x1;
                    sw(v1, s0, shop::kStepFlags);
                    sw(v0, s0, shop::kStepResult);
                } else {
                    // 0x003e95a8
                    charge(ctx, 29);
                    a0 = 1;
                    a1 = a0;
                    jal(ctx, 0x3E95B0u, gen::fn_sub_1A0040_001a0040);
                    a0 = 3072;
                    a1 = 1;
                    jal(ctx, 0x3E95C0u, gen::fn_sub_1A0150_001a0150);
                    a0 = 3073;
                    a1 = 1;
                    jal(ctx, 0x3E95D0u, gen::fn_sub_1A0150_001a0150);
                    a0 = 3074;
                    a1 = 1;
                    jal(ctx, 0x3E95E0u, gen::fn_sub_1A0150_001a0150);
                    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
                    jal(ctx, 0x3E95ECu, gen::fn_nmObjPayloadWord12_003c5460);
                    a0 = v0;
                    a1 = 0;
                    a2 = 1;
                    jal(ctx, 0x3E9600u, gen::fn_sub_3E0C20_003e0c20);
                    lw(v0, s0, shop::kStepFlags);
                    v0 = v0 | 0x2;
                    sw(v0, s0, shop::kStepFlags);
                }
            }
        }
        goto L_003e96c8;
    }
    // 0x003e9634
    charge(ctx, 4);
    lw(v0, s0, shop::kStepFlags);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x003e9650
        charge(ctx, 6);
        lw(a0, s0, 12);
        jal(ctx, 0x3E9654u, gen::fn_sub_4003F0_004003f0);
        v1 = si(-1);
        if (v0 == v1) {
            // 0x003e9678
            charge(ctx, 5);
            lw(v0, s0, shop::kStepFlags);
            v0 = v0 | 0x2;
            sw(v0, s0, shop::kStepFlags);
        } else {
            // 0x003e9668
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x003e9670
                charge(ctx, 2);
                // 0x003e968c
                charge(ctx, 7);
                lw(v1, s0, shop::kStepFlags);
                v1 = v1 | 0x1;
                sw(v1, s0, shop::kStepFlags);
                sw(v0, s0, shop::kStepResult);
                v1 = 3;
                if (v0 != v1) {
                    // 0x003e96a8
                    charge(ctx, 8);
                    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
                    jal(ctx, 0x3E96ACu, gen::fn_nmObjPayloadWord12_003c5460);
                    a0 = v0;
                    a1 = 0;
                    a2 = 0;
                    jal(ctx, 0x3E96C0u, gen::fn_sub_3E0C20_003e0c20);
                }
            }
        }
    L_003e96c8:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003e9644
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003e96cc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003E96F0 sub_3E96F0 -- 148 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [ROOT draw] Type 8: sub_40CAD0 (the quest background); the others, unless hidden: the command list (sub_400690).
// Returns 0.
void sub_3E96F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e96f0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    jal(ctx, 0x3E9704u, gen::fn_nmObjPayloadWord12_003c5460);
    s0 = v0;
    a0 = s1;
    jal(ctx, 0x3E9714u, gen::fn_sub_3C5470_003c5470);
    lw(a0, s0, shop::kShopType);
    v1 = 8;
    if (a0 == v1) {
        // 0x003e972c
        charge(ctx, 5);
        lw(a0, v0, 16);
        jal(ctx, 0x3E9730u, gen::fn_sub_40CAD0_0040cad0);
        goto L_003e9768;
    }
    // 0x003e9740
    charge(ctx, 4);
    lw(v1, v0, 4);
    v1 = v1 & 0x2;
    if (v1 == 0) {
        // 0x003e975c
        charge(ctx, 3);
        lw(a0, v0, 12);
        jal(ctx, 0x3E9760u, gen::fn_sub_400690_00400690);
    L_003e9768:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003e9750
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003e976c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003E9790 sub_3E9790 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopShowRoot] The ROOT step's payload; $a0 == 0 clears its flag 2 (shows the menu). Caller: the BG event
// handler sub_411340.
void sub_3E9790(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e9790
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    jal(ctx, 0x3E97A4u, gen::fn_nmObjPayloadWord12_003c5460);
    lw(a0, v0, 16);
    jal(ctx, 0x3E97B0u, gen::fn_sub_3C5470_003c5470);
    if (s0 == 0) {
        // 0x003e97c0
        charge(ctx, 4);
        lw(a0, v0, 4);
        v1 = si(-3);
        v1 = a0 & v1;
        sw(v1, v0, 4);
    }
    // 0x003e97d0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003E97F0 sub_3E97F0 -- 188 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopOpenBuy] Adds the BUY step (id 2, descriptor 0x6A7070) into $a0 +20 and brings element 5 in. Returns the
// node.
void sub_3E97F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x003e97f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 28784);  // &0x6A7070: the BUY step descriptor
    a0 = addiu(sp, 0x30);
    v1 = 2;
    for (;;) {
        // 0x003e9814
        charge(ctx, 7);
        lq(v0, a1, 0);
        a1 = addiu(a1, 16);
        v1 = addiu(v1, -1);
        sq(v0, a0, 0);
        a0 = addiu(a0, 16);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003e9830
    charge(ctx, 12);
    lwc1(f0, a1, 0);
    swc1(f0, a0, 0);
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    a1 = 2;
    a2 = addiu(sp, 0x30);
    a3 = 0;
    t0 = a1;
    jal(ctx, 0x3E984Cu, gen::fn_nmSequenceAddStep_003c5240);
    s1 = v0;
    if (s0 != 0) {
        // 0x003e9860
        charge(ctx, 1);
        sw(s1, s0, shop::kShopStepBuy);
    }
    // 0x003e9864
    charge(ctx, 18);
    a0 = s1;
    jal(ctx, 0x3E9868u, gen::fn_sub_3C5470_003c5470);
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    jal(ctx, 0x3E9874u, gen::fn_nmObjPayloadWord12_003c5460);
    a0 = v0;
    a1 = 5;
    a2 = 0;
    jal(ctx, 0x3E9888u, gen::fn_sub_3E0C20_003e0c20);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003E98B0 sub_3E98B0 -- 184 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopPollBuy] When the BUY step finished or decided: clears +20, element 5 out, returns the result; else -1.
void sub_3E98B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e98b0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, 20);
    if (a0 != 0) {
        // 0x003e98d4
        charge(ctx, 3);
        lw(s2, a0, 20);
        if (s2 == 0) {
            goto L_003e98e0;
        }
        // 0x003e98ec
        charge(ctx, 7);
        jal(ctx, 0x3E98ECu, gen::fn_sub_3C5470_003c5470);
        s0 = v0;
        lw(v0, s2, 20);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            // 0x003e9908
            charge(ctx, 4);
            lw(v0, s0, shop::kStepFlags);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                goto L_003e9918;
            }
            // 0x003e9948
            charge(ctx, 1);
            v0 = si(-1);
            // 0x003e994c (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_003e9918:
        charge(ctx, 12);
        sw(zero, s1, shop::kShopStepBuy);
        lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
        jal(ctx, 0x3E9920u, gen::fn_nmObjPayloadWord12_003c5460);
        a0 = v0;
        a1 = 5;
        a2 = 1;
        jal(ctx, 0x3E9934u, gen::fn_sub_3E0C20_003e0c20);
        lw(v0, s0, shop::kStepResult);
        // 0x003e994c (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_003e98e0:
    charge(ctx, 3);
    v0 = si(-1);
    // 0x003e994c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003E9970 sub_3E9970 -- 276 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [BUY init] Builds the lineup for root states 44 / 45 / 46 (sub_3F33D0(type, 0 / 1 / 2) -> +16); weapons and
// accessories (types 0, 1) also get the equipment comparison panel (sub_3FD820 -> +228; 0 otherwise); phase 1, flag
// 2. Returns 0.
void sub_3E9970(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e9970
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3E9988u, gen::fn_nmObjPayloadWord12_003c5460);
    s1 = v0;
    lw(s2, v0, 0);
    a0 = s0;
    jal(ctx, 0x3E999Cu, gen::fn_sub_3C5470_003c5470);
    s0 = v0;
    lw(v1, s1, shop::kShopState);
    v0 = 44;
    if (v1 != v0) {
        // 0x003e99d4
        charge(ctx, 3);
        v0 = 45;
        if (v1 != v0) {
            // 0x003e99fc
            charge(ctx, 3);
            v0 = 46;
            if (v1 == v0) {
                // 0x003e9a08
                charge(ctx, 5);
                a0 = s2;
                a1 = 2;
                jal(ctx, 0x3E9A10u, gen::fn_sub_3F33D0_003f33d0);
                sw(v0, s0, 16);
            }
        } else {
            // 0x003e99e0
            charge(ctx, 7);
            a0 = s2;
            a1 = 1;
            jal(ctx, 0x3E99E8u, gen::fn_sub_3F33D0_003f33d0);
            sw(v0, s0, 16);
        }
    } else {
        // 0x003e99b8
        charge(ctx, 7);
        a0 = s2;
        a1 = 0;
        jal(ctx, 0x3E99C0u, gen::fn_sub_3F33D0_003f33d0);
        sw(v0, s0, 16);
    }
    // 0x003e9a1c
    charge(ctx, 3);
    lw(v1, s1, shop::kShopType);
    if (v1 != 0) {
        // 0x003e9a28
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            goto L_003e9a34;
        }
        // 0x003e9a4c
        charge(ctx, 1);
        sw(zero, s0, 228);
        // 0x003e9a50 (the shared epilogue, written out on this path)
        charge(ctx, 13);
        v0 = 1;
        sw(v0, s0, 8);
        lw(v0, s0, 4);
        v0 = v0 | 0x2;
        sw(v0, s0, 4);
        v0 = 0;
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_003e9a34:
    charge(ctx, 6);
    a0 = s2;
    jal(ctx, 0x3E9A38u, gen::fn_sub_3FD820_003fd820);
    sw(v0, s0, 228);
    // 0x003e9a50 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    v0 = 1;
    sw(v0, s0, 8);
    lw(v0, s0, 4);
    v0 = v0 | 0x2;
    sw(v0, s0, 4);
    v0 = 0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003E9A90 sub_3E9A90 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [BUY fini] Destroys the lineup list (nmCmdListDestroy) and the comparison panel when there is one (sub_3FD8A0).
// Returns 0.
void sub_3E9A90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003e9a90
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3E9AA0u, gen::fn_sub_3C5470_003c5470);
    s0 = v0;
    lw(a0, v0, 16);
    jal(ctx, 0x3E9AB0u, gen::fn_nmCmdListDestroy_003c5a20);
    lw(a0, s0, 228);
    if (a0 != 0) {
        // 0x003e9ac4
        charge(ctx, 2);
        jal(ctx, 0x3E9AC4u, gen::fn_sub_3FD8A0_003fd8a0);
    }
    // 0x003e9acc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003EA4D0 sub_3EA4D0 -- 136 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [BUY draw] Unless hidden: the lineup (nmCmdListDraw), the comparison panel (sub_3FDF80), the item description
// (sub_3FBC00 on +24) and the per-type info (sub_3FC980 on +76). Returns 0.
void sub_3EA4D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ea4d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3EA4E0u, gen::fn_sub_3C5470_003c5470);
    s0 = v0;
    lw(v0, v0, 4);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x003ea508
        charge(ctx, 6);
        lw(a0, s0, 16);
        jal(ctx, 0x3EA50Cu, gen::fn_nmCmdListDraw_003c6380);
        lw(a0, s0, 228);
        if (a0 != 0) {
            // 0x003ea520
            charge(ctx, 2);
            jal(ctx, 0x3EA520u, gen::fn_sub_3FDF80_003fdf80);
        }
        // 0x003ea528
        charge(ctx, 7);
        a0 = addiu(s0, 24);
        jal(ctx, 0x3EA52Cu, gen::fn_sub_3FBC00_003fbc00);
        a0 = addiu(s0, 76);
        jal(ctx, 0x3EA538u, gen::fn_sub_3FC980_003fc980);
        v0 = 0;
    } else {
        // 0x003ea4fc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003ea544 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003EA560 sub_3EA560 -- 156 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopBuyQuery] The BUY step's payload: $a0 == 1 returns bit 1 of the lineup list's view word (list +36 -> +68 ->
// +0; 1 / 0); $a0 == 0 clears the step's flag 2 (shows it) and returns 0. Caller: sub_411340.
void sub_3EA560(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ea560
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    jal(ctx, 0x3EA574u, gen::fn_nmObjPayloadWord12_003c5460);
    lw(a0, v0, 20);
    jal(ctx, 0x3EA580u, gen::fn_sub_3C5470_003c5470);
    v1 = 1;
    if (s0 != v1) {
        // 0x003ea594
        charge(ctx, 2);
        if (s0 == 0) {
            // 0x003ea5a4
            charge(ctx, 6);
            lw(a0, v0, 4);
            v1 = si(-3);
            v1 = a0 & v1;
            sw(v1, v0, 4);
        } else {
            // 0x003ea59c
            charge(ctx, 2);
        }
        goto L_003ea5e4;
    }
    // 0x003ea5bc
    charge(ctx, 7);
    lw(v0, v0, 16);
    lw(v0, v0, 36);
    lw(v0, v0, 68);
    lw(v0, v0, 0);
    v0 = v0 & 0x2;
    if (v0 == 0) {
    L_003ea5e4:
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003ea5d8
        charge(ctx, 3);
        v0 = v1;
    }
    // 0x003ea5e8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003EA600 sub_3EA600 -- 176 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopOpenSell] Adds the SELL step (id 3, descriptor 0x6A70B0) into $a0 +24 and brings element 6 in. Returns the
// node.
void sub_3EA600(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x003ea600
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 28848);  // &0x6A70B0: the SELL step descriptor
    a0 = addiu(sp, 0x30);
    v1 = 2;
    for (;;) {
        // 0x003ea624
        charge(ctx, 7);
        lq(v0, a1, 0);
        a1 = addiu(a1, 16);
        v1 = addiu(v1, -1);
        sq(v0, a0, 0);
        a0 = addiu(a0, 16);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003ea640
    charge(ctx, 12);
    lwc1(f0, a1, 0);
    swc1(f0, a0, 0);
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    a1 = 3;
    a2 = addiu(sp, 0x30);
    a3 = 0;
    t0 = 2;
    jal(ctx, 0x3EA65Cu, gen::fn_nmSequenceAddStep_003c5240);
    s1 = v0;
    if (s0 != 0) {
        // 0x003ea670
        charge(ctx, 1);
        sw(s1, s0, shop::kShopStepSell);
    }
    // 0x003ea674
    charge(ctx, 15);
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    jal(ctx, 0x3EA678u, gen::fn_nmObjPayloadWord12_003c5460);
    a0 = v0;
    a1 = 6;
    a2 = 0;
    jal(ctx, 0x3EA68Cu, gen::fn_sub_3E0C20_003e0c20);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003EA6B0 sub_3EA6B0 -- 184 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopPollSell] When the SELL step finished or decided: element 6 out, clears +24, returns the result; else -1.
void sub_3EA6B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ea6b0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, 24);
    if (a0 != 0) {
        // 0x003ea6d4
        charge(ctx, 3);
        lw(s2, a0, 20);
        if (s2 == 0) {
            goto L_003ea6e0;
        }
        // 0x003ea6ec
        charge(ctx, 7);
        jal(ctx, 0x3EA6ECu, gen::fn_sub_3C5470_003c5470);
        s0 = v0;
        lw(v0, s2, 20);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            // 0x003ea708
            charge(ctx, 4);
            lw(v0, s0, shop::kStepFlags);
            v0 = v0 & 0x1;
            if (v0 != 0) {
                goto L_003ea718;
            }
            // 0x003ea748
            charge(ctx, 1);
            v0 = si(-1);
            // 0x003ea74c (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_003ea718:
        charge(ctx, 12);
        lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
        jal(ctx, 0x3EA71Cu, gen::fn_nmObjPayloadWord12_003c5460);
        a0 = v0;
        a1 = 6;
        a2 = 1;
        jal(ctx, 0x3EA730u, gen::fn_sub_3E0C20_003e0c20);
        sw(zero, s1, shop::kShopStepSell);
        lw(v0, s0, shop::kStepResult);
        // 0x003ea74c (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_003ea6e0:
    charge(ctx, 3);
    v0 = si(-1);
    // 0x003ea74c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003EA770 sub_3EA770 -- 112 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [SELL init] The sell list of the shop type (sub_3F9E30 -> +12), phase 1, flag 2. Returns 0.
void sub_3EA770(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ea770
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3EA784u, gen::fn_nmObjPayloadWord12_003c5460);
    s1 = v0;
    a0 = s0;
    jal(ctx, 0x3EA794u, gen::fn_sub_3C5470_003c5470);
    s0 = v0;
    lw(a0, s1, shop::kShopType);
    jal(ctx, 0x3EA7A4u, gen::fn_sub_3F9E30_003f9e30);
    sw(v0, s0, 12);
    v0 = 1;
    sw(v0, s0, 8);
    lw(v0, s0, 4);
    v0 = v0 | 0x2;
    sw(v0, s0, 4);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003EA7E0 sub_3EA7E0 -- 52 bytes; frame 0x10: ra sp+0x0
// [SELL fini] Destroys the sell list. Returns 0.
void sub_3EA7E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ea7e0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3EA7ECu, gen::fn_sub_3C5470_003c5470);
    lw(a0, v0, 12);
    jal(ctx, 0x3EA7F8u, gen::fn_nmCmdListDestroy_003c5a20);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003EAC40 sub_3EAC40 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [SELL draw] Unless hidden: the sell list and the item description (sub_3FBC00 on +20). Returns 0.
void sub_3EAC40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003eac40
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3EAC50u, gen::fn_sub_3C5470_003c5470);
    s0 = v0;
    lw(v0, v0, 4);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        // 0x003eac78
        charge(ctx, 7);
        lw(a0, s0, 12);
        jal(ctx, 0x3EAC7Cu, gen::fn_nmCmdListDraw_003c6380);
        a0 = addiu(s0, 20);
        jal(ctx, 0x3EAC88u, gen::fn_sub_3FBC00_003fbc00);
        v0 = 0;
    } else {
        // 0x003eac6c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003eac94 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003EACB0 sub_3EACB0 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopShowSell] The SELL step's payload; $a0 == 0 clears its flag 2. Caller: sub_411340.
void sub_3EACB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003eacb0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    jal(ctx, 0x3EACC4u, gen::fn_nmObjPayloadWord12_003c5460);
    lw(a0, v0, 24);
    jal(ctx, 0x3EACD0u, gen::fn_sub_3C5470_003c5470);
    if (s0 == 0) {
        // 0x003eace0
        charge(ctx, 4);
        lw(a0, v0, 4);
        v1 = si(-3);
        v1 = a0 & v1;
        sw(v1, v0, 4);
    }
    // 0x003eacf0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003EE310 sub_3EE310 -- 192 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopOpenTalk] Adds the TALK step (id 4, descriptor 0x6A7230) into $a0 +28; the antique shop brings element 17
// in. Returns the node.
void sub_3EE310(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x003ee310
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 29232);  // &0x6A7230: the TALK step descriptor
    a0 = addiu(sp, 0x30);
    v1 = 2;
    for (;;) {
        // 0x003ee334
        charge(ctx, 7);
        lq(v0, a1, 0);
        a1 = addiu(a1, 16);
        v1 = addiu(v1, -1);
        sq(v0, a0, 0);
        a0 = addiu(a0, 16);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003ee350
    charge(ctx, 12);
    lwc1(f0, a1, 0);
    swc1(f0, a0, 0);
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    a1 = 4;
    a2 = addiu(sp, 0x30);
    a3 = 0;
    t0 = 2;
    jal(ctx, 0x3EE36Cu, gen::fn_nmSequenceAddStep_003c5240);
    s1 = v0;
    if (s0 != 0) {
        // 0x003ee380
        charge(ctx, 1);
        sw(s1, s0, shop::kShopStepTalk);
    }
    // 0x003ee384
    charge(ctx, 4);
    lw(v1, s0, shop::kShopType);
    v0 = 4;
    if (v1 == v0) {
        // 0x003ee394
        charge(ctx, 8);
        lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
        jal(ctx, 0x3EE398u, gen::fn_nmObjPayloadWord12_003c5460);
        a0 = v0;
        a1 = 17;
        a2 = 1;
        jal(ctx, 0x3EE3ACu, gen::fn_sub_3E0C20_003e0c20);
    }
    // 0x003ee3b4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003EE3D0 sub_3EE3D0 -- 176 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopPollTalk] When the TALK step finished: clears +28, the antique shop's element 17 out, returns the result;
// else -1.
void sub_3EE3D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ee3d0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, a0, 28);
    if (a0 != 0) {
        // 0x003ee3f0
        charge(ctx, 3);
        lw(v0, a0, 20);
        if (v0 == 0) {
            goto L_003ee3fc;
        }
        // 0x003ee408
        charge(ctx, 4);
        lw(v0, v0, 20);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            // 0x003ee464
            charge(ctx, 1);
            v0 = si(-1);
        } else {
            // 0x003ee418
            charge(ctx, 8);
            jal(ctx, 0x3EE418u, gen::fn_sub_3C5470_003c5470);
            s0 = v0;
            sw(zero, s1, shop::kShopStepTalk);
            lw(v1, s1, shop::kShopType);
            v0 = 4;
            if (v1 == v0) {
                // 0x003ee438
                charge(ctx, 8);
                lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
                jal(ctx, 0x3EE43Cu, gen::fn_nmObjPayloadWord12_003c5460);
                a0 = v0;
                a1 = 17;
                a2 = 0;
                jal(ctx, 0x3EE450u, gen::fn_sub_3E0C20_003e0c20);
            }
            // 0x003ee458
            charge(ctx, 3);
            lw(v0, s0, shop::kStepResult);
        }
        // 0x003ee468 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_003ee3fc:
    charge(ctx, 3);
    v0 = si(-1);
    // 0x003ee468 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003EE480 sub_3EE480 -- 96 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [TALK init] Requests the type's chat message (sub_3F0AC0(type) -> msgWinRequestMessage). Returns 0.
void sub_3EE480(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ee480
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    jal(ctx, 0x3EE494u, gen::fn_nmObjPayloadWord12_003c5460);
    s0 = v0;
    a0 = s1;
    jal(ctx, 0x3EE4A4u, gen::fn_sub_3C5470_003c5470);
    lw(a0, s0, shop::kShopType);
    jal(ctx, 0x3EE4B0u, gen::fn_sub_3F0AC0_003f0ac0);
    a0 = v0;
    jal(ctx, 0x3EE4BCu, gen::fn_msgWinRequestMessage_003c7430);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003EE510 sub_3EE510 -- 68 bytes; frame 0x10: ra sp+0x0
// [TALK update] Waits for the message window (sub_3C7850), closes it (sub_3C7700) and ends the step (nmSeqNullStep).
void sub_3EE510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ee510
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3EE518u, gen::fn_sub_3C7850_003c7850);
    if (v0 != 0) {
        // 0x003ee540
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003ee528
        charge(ctx, 6);
        jal(ctx, 0x3EE528u, gen::fn_sub_3C7700_003c7700);
        v0 = 0x3C0000;
        v0 = addiu(v0, 20848);  // &nmSeqNullStep
    }
    // 0x003ee544 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003EE560 sub_3EE560 -- 12 bytes; leaf frame (no stack)
// [TALK draw] Nothing. Returns 0.
void sub_3EE560(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003ee560
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x003EE570 sub_3EE570 -- 128 bytes; frame 0x50: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopOpenMoney] Adds the MONEY step (id 14, descriptor 0x6A7260) into $a0 +68. Returns the node.
void sub_3EE570(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x003ee570
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 29280);  // &0x6A7260: the MONEY step descriptor
    a0 = addiu(sp, 0x20);
    v1 = 2;
    for (;;) {
        // 0x003ee590
        charge(ctx, 7);
        lq(v0, a1, 0);
        a1 = addiu(a1, 16);
        v1 = addiu(v1, -1);
        sq(v0, a0, 0);
        a0 = addiu(a0, 16);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003ee5ac
    charge(ctx, 11);
    lwc1(f0, a1, 0);
    swc1(f0, a0, 0);
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    a1 = 14;
    a2 = addiu(sp, 0x20);
    a3 = 0;
    t0 = 2;
    jal(ctx, 0x3EE5C8u, gen::fn_nmSequenceAddStep_003c5240);
    if (s0 != 0) {
        // 0x003ee5d8
        charge(ctx, 1);
        sw(v0, s0, shop::kShopStepMoney);
    }
    // 0x003ee5dc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003EE5F0 sub_3EE5F0 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [MONEY init] Both yen words of the payload (+12, +8; sub_3E6400 draws +8) = the current yen (sub_16DD50). Returns
// 0.
void sub_3EE5F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ee5f0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3EE600u, gen::fn_nmObjPayloadWord12_003c5460);
    a0 = s0;
    jal(ctx, 0x3EE60Cu, gen::fn_sub_3C5470_003c5470);
    s0 = v0;
    jal(ctx, 0x3EE618u, gen::fn_sub_16DD50_0016dd50);
    sw(v0, s0, 12);
    sw(v0, s0, 8);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003EEC60 sub_3EEC60 -- 176 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopMoneyFlag] Sets a display bit on the MONEY step's payload +4: $a0 0 -> 1, 1 -> 2, 2 -> 4, 3 -> 8. Returns
// the payload. Callers: BUY (sub_3E9AF0), the BG event handler sub_4110F0.
void sub_3EEC60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003eec60
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    jal(ctx, 0x3EEC74u, gen::fn_nmObjPayloadWord12_003c5460);
    lw(a0, v0, 68);
    jal(ctx, 0x3EEC80u, gen::fn_sub_3C5470_003c5470);
    if (s0 != 0) {
        // 0x003eeca4
        charge(ctx, 3);
        v1 = 1;
        if (s0 != v1) {
            // 0x003eecc4
            charge(ctx, 3);
            v1 = 2;
            if (s0 != v1) {
                // 0x003eece4
                charge(ctx, 3);
                v1 = 3;
                if (s0 == v1) {
                    // 0x003eecf0
                    charge(ctx, 3);
                    lw(v1, v0, 4);
                    v1 = v1 | 0x8;
                    sw(v1, v0, 4);
                }
            } else {
                // 0x003eecd0
                charge(ctx, 5);
                lw(v1, v0, 4);
                v1 = v1 | 0x4;
                sw(v1, v0, 4);
            }
        } else {
            // 0x003eecb0
            charge(ctx, 5);
            lw(v1, v0, 4);
            v1 = v1 | 0x2;
            sw(v1, v0, 4);
        }
    } else {
        // 0x003eec90
        charge(ctx, 5);
        lw(v1, v0, 4);
        v1 = v1 | 0x1;
        sw(v1, v0, 4);
    }
    // 0x003eecfc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003EED10 sub_3EED10 -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopMoneySetDelta] The MONEY step's payload +20 = $a0 (the amount shown beside the yen). Returns the payload.
void sub_3EED10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003eed10
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    jal(ctx, 0x3EED24u, gen::fn_nmObjPayloadWord12_003c5460);
    lw(a0, v0, 68);
    jal(ctx, 0x3EED30u, gen::fn_sub_3C5470_003c5470);
    sw(s0, v0, 20);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003EED90 sub_3EED90 -- 128 bytes; frame 0x50: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopOpenSubtitle] Adds the SUBTITLE step (id 15, descriptor 0x6A72E0) into $a0 +72. Returns the node.
void sub_3EED90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x003eed90
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 29408);  // &0x6A72E0: the SUBTITLE step descriptor
    a0 = addiu(sp, 0x20);
    v1 = 2;
    for (;;) {
        // 0x003eedb0
        charge(ctx, 7);
        lq(v0, a1, 0);
        a1 = addiu(a1, 16);
        v1 = addiu(v1, -1);
        sq(v0, a0, 0);
        a0 = addiu(a0, 16);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003eedcc
    charge(ctx, 11);
    lwc1(f0, a1, 0);
    swc1(f0, a0, 0);
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    a1 = 15;
    a2 = addiu(sp, 0x20);
    a3 = 0;
    t0 = 2;
    jal(ctx, 0x3EEDE8u, gen::fn_nmSequenceAddStep_003c5240);
    if (s0 != 0) {
        // 0x003eedf8
        charge(ctx, 1);
        sw(v0, s0, shop::kShopStepSubtitle);
    }
    // 0x003eedfc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003EEE10 sub_3EEE10 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [SUBTITLE init] Nothing beyond fetching the payloads. Returns 0.
void sub_3EEE10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003eee10
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3EEE20u, gen::fn_nmObjPayloadWord12_003c5460);
    a0 = s0;
    jal(ctx, 0x3EEE2Cu, gen::fn_sub_3C5470_003c5470);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003EFB40 sub_3EFB40 -- 128 bytes; frame 0x50: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopOpenBg] Adds the BG step (id 13, descriptor 0x6A75E0) into $a0 +64. Returns the node.
void sub_3EFB40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x003efb40
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0x6A0000;
    a1 = addiu(a1, 30176);  // &0x6A75E0: the BG step descriptor
    a0 = addiu(sp, 0x20);
    v1 = 2;
    for (;;) {
        // 0x003efb60
        charge(ctx, 7);
        lq(v0, a1, 0);
        a1 = addiu(a1, 16);
        v1 = addiu(v1, -1);
        sq(v0, a0, 0);
        a0 = addiu(a0, 16);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003efb7c
    charge(ctx, 11);
    lwc1(f0, a1, 0);
    swc1(f0, a0, 0);
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    a1 = 13;
    a2 = addiu(sp, 0x20);
    a3 = 0;
    t0 = 2;
    jal(ctx, 0x3EFB98u, gen::fn_nmSequenceAddStep_003c5240);
    if (s0 != 0) {
        // 0x003efba8
        charge(ctx, 1);
        sw(v0, s0, shop::kShopStepBg);
    }
    // 0x003efbac (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003EFBC0 sub_3EFBC0 -- 96 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [BG init] Creates the background manager and its three draw tasks (fclShopMisc_CreateShopDrawBGLowTasks -> payload
// +8) and gives it the shop type (+28). Returns 0.
void sub_3EFBC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003efbc0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    jal(ctx, 0x3EFBD4u, gen::fn_nmObjPayloadWord12_003c5460);
    s1 = v0;
    a0 = s0;
    jal(ctx, 0x3EFBE4u, gen::fn_sub_3C5470_003c5470);
    s0 = v0;
    jal(ctx, 0x3EFBF0u, gen::fn_fclShopMisc_CreateShopDrawBGLowTasks_00400d60);
    sw(v0, s0, 8);
    lw(v1, s1, shop::kShopType);
    sw(v1, v0, 28);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003EFC60 sub_3EFC60 -- 52 bytes; frame 0x10: ra sp+0x0
// [BG update] sub_400E90 on the manager (still recompiled). Returns 0.
void sub_3EFC60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003efc60
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3EFC6Cu, gen::fn_sub_3C5470_003c5470);
    lw(a0, v0, 8);
    jal(ctx, 0x3EFC78u, gen::fn_sub_400E90_00400e90);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003EFCA0 sub_3EFCA0 -- 52 bytes; frame 0x10: ra sp+0x0
// [BG draw] sub_401170: the manager's layer-3 draw handlers. Returns 0.
void sub_3EFCA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003efca0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = a1;
    jal(ctx, 0x3EFCACu, gen::fn_sub_3C5470_003c5470);
    lw(a0, v0, 8);
    jal(ctx, 0x3EFCB8u, gen::fn_sub_401170_00401170);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003EFCE0 sub_3EFCE0 -- 140 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopBgSetScene] When the BG step exists: the manager's scene = off_6B1F30 + 16 * type (sub_401420). Load op 6.
// Returns 0.
void sub_3EFCE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003efce0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    jal(ctx, 0x3EFCF8u, gen::fn_nmObjPayloadWord12_003c5460);
    s0 = v0;
    if (s0 != 0) {
        // 0x003efd0c
        charge(ctx, 1);
        lw(s1, s0, shop::kShopStepBg);
    }
    // 0x003efd10
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x003efd24
        charge(ctx, 12);
        a0 = s1;
        jal(ctx, 0x3EFD28u, gen::fn_sub_3C5470_003c5470);
        lw(v1, s0, shop::kShopType);
        a0 = sll(v1, 4);
        v1 = 0x6B0000;
        v1 = addiu(v1, 7984);  // &0x6B1F30
        a1 = addu(v1, a0);
        lw(a0, v0, 8);
        jal(ctx, 0x3EFD48u, gen::fn_sub_401420_00401420);
        v0 = 0;
    } else {
        // 0x003efd18
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003efd54 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003EFD70 sub_3EFD70 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopBgLoaded] When the BG step exists: sub_4014E0 (the scene's load handlers done) != 0; else 0.
void sub_3EFD70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003efd70
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    jal(ctx, 0x3EFD84u, gen::fn_nmObjPayloadWord12_003c5460);
    if (v0 != 0) {
        // 0x003efd94
        charge(ctx, 1);
        lw(s0, v0, 64);
    }
    // 0x003efd98
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x003efdac
        charge(ctx, 7);
        a0 = s0;
        jal(ctx, 0x3EFDB0u, gen::fn_sub_3C5470_003c5470);
        lw(a0, v0, 8);
        jal(ctx, 0x3EFDBCu, gen::fn_sub_4014E0_004014e0);
        v0 = sltu(0, v0);
    } else {
        // 0x003efda0
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003efdc8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003EFDE0 sub_3EFDE0 -- 124 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopBgSetMode] Except for type 8: the manager's mode = $a1 (sub_4015A0; the backgrounds react to it). The root
// sets it on every menu change.
void sub_3EFDE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003efde0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = 0;
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    jal(ctx, 0x3EFDFCu, gen::fn_nmObjPayloadWord12_003c5460);
    lw(a0, v0, 0);
    v1 = 8;
    if (a0 != v1) {
        // 0x003efe14
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x003efe1c
            charge(ctx, 1);
            lw(s0, v0, 64);
        }
        // 0x003efe20
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x003efe28
            charge(ctx, 7);
            a0 = s0;
            jal(ctx, 0x3EFE2Cu, gen::fn_sub_3C5470_003c5470);
            lw(a0, v0, 8);
            a1 = s1;
            jal(ctx, 0x3EFE3Cu, gen::fn_sub_4015A0_004015a0);
        }
    }
    // 0x003efe44 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003EFE60 sub_3EFE60 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopBgBusy] When the BG step exists: the manager's flag 2 (sub_4015E0); else 0. The root waits on it before
// changing the mode.
void sub_3EFE60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003efe60
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    lw(a0, gp, -18024);  // 0x7CE688: the shop sequence
    jal(ctx, 0x3EFE74u, gen::fn_nmObjPayloadWord12_003c5460);
    if (v0 != 0) {
        // 0x003efe84
        charge(ctx, 1);
        lw(s0, v0, 64);
    }
    // 0x003efe88
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x003efe9c
        charge(ctx, 6);
        a0 = s0;
        jal(ctx, 0x3EFEA0u, gen::fn_sub_3C5470_003c5470);
        lw(a0, v0, 8);
        jal(ctx, 0x3EFEACu, gen::fn_sub_4015E0_004015e0);
    } else {
        // 0x003efe90
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003efeb4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003EFED0 sub_3EFED0 -- 24 bytes; leaf frame (no stack)
// [fclSpriteBankDesc] &descriptors[$a0] (0x6A9930, 16 bytes each). Callers: load op 2, fusion's sub_3D2740.
void sub_3EFED0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003efed0
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = sll(a0, 4);
    v0 = 0x6B0000;
    v0 = addiu(v0, -26320);  // &0x6A9930
    v0 = addu(v0, v1);
}

// 0x003EFEF0 sub_3EFEF0 -- 16 bytes; leaf frame (no stack)
// [fclSpriteBankDescMc] The memory-card UI's descriptor 0x6A99C0.
void sub_3EFEF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x003efef0
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x6B0000;
    v0 = addiu(v0, -26176);  // &0x6A99C0
}

// 0x003EFF00 sub_3EFF00 -- 232 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopSummary] For the field (caller sub_17D610): fills the 8-byte record $a1 for shop $a0: byte 0 = the number
// of 12-byte level entries of the type's record (sub_3F0350) the protagonist's level (sub_16C470(1)) reaches, minus
// one; byte 1 = the shop's social-link rank (sub_3F03E0); u16 2 = the flag mask (sub_3F2510); word 4 = the index of
// the first lineup that matches (sub_3F01D0).
void sub_3EFF00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003eff00
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    jal(ctx, 0x3EFF20u, gen::fn_sub_3EFFF0_003efff0);
    s0 = v0;
    sw(zero, sp, 0x5C);
    for (;;) {
        // 0x003eff6c
        charge(ctx, 6);
        a0 = s0;
        a1 = addiu(sp, 0x5C);
        jal(ctx, 0x3EFF74u, gen::fn_sub_3F0350_003f0350);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003eff38
        charge(ctx, 8);
        lw(s3, v0, 0);
        a0 = 1;
        jal(ctx, 0x3EFF40u, gen::fn_sub_16C470_0016c470);
        v0 = v0 & 0xFF;
        at = slt(v0, s3);
        if (at == 0) {
            continue;
        }
        goto L_003eff58_2;
    }
L_003eff84:
    charge(ctx, 25);
    lw(v0, sp, 0x5C);
    sb(v0, s1, 0);
    a0 = s2;
    jal(ctx, 0x3EFF90u, gen::fn_sub_3F03E0_003f03e0);
    sb(v0, s1, 1);
    jal(ctx, 0x3EFF9Cu, gen::fn_sub_3F2510_003f2510);
    sh(v0, s1, 2);
    sw(zero, sp, 0x5C);
    a0 = s0;
    a1 = 0;
    a2 = addiu(sp, 0x5C);
    jal(ctx, 0x3EFFB8u, gen::fn_sub_3F01D0_003f01d0);
    lw(v1, sp, 0x5C);
    sw(v1, s1, 4);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_003eff58_2:
    charge(ctx, 5);
    lw(v0, sp, 0x5C);
    v0 = addiu(v0, -1);
    sw(v0, sp, 0x5C);
    goto L_003eff84;
}

// 0x003EFFF0 sub_3EFFF0 -- 152 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopRecord] &record[type] in 0x6AC9D0 (9 words each; the second set of 9 when sub_17D800() is set); K_Assert
// fclShopMisc.c:185 for a type above 8.
void sub_3EFFF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003efff0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (i64(s0) >= 0) {
        // 0x003f0008
        charge(ctx, 3);
        v0 = slti(s0, 9);
        if (v0 == 0) {
            goto L_003f0014;
        }
        goto L_003f0028;
    }
L_003f0014:
    charge(ctx, 5);
    a0 = 0x6B0000;
    a0 = addiu(a0, -4632);  // "fclShopMisc.c"
    a1 = 185;
    jal(ctx, 0x3F0020u, gen::fn_sub_19D3F0_0019d3f0);
L_003f0028:
    charge(ctx, 4);
    jal(ctx, 0x3F0028u, gen::fn_sub_17D800_0017d800);
    if (v0 != 0) {
        // 0x003f0058
        charge(ctx, 7);
        v1 = addiu(s0, 9);
        v0 = sll(v1, 3);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x6B0000;
        v0 = addiu(v0, -13872);  // &0x6AC9D0
        v0 = addu(v0, v1);
    } else {
        // 0x003f0038
        charge(ctx, 8);
        v0 = sll(s0, 3);
        v0 = addu(v0, s0);
        v1 = sll(v0, 2);
        v0 = 0x6B0000;
        v0 = addiu(v0, -13872);  // &0x6AC9D0
        v0 = addu(v0, v1);
    }
    // 0x003f0074 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003F0090 sub_3F0090 -- 28 bytes; leaf frame (no stack)
// [fclShopIntroMessage] The s16 intro message of type $a0 (0x6ACC70 + 4 * type; -1 = none).
void sub_3F0090(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003f0090
    enter(ctx, 7);  // entry check point + this block's cycles
    v1 = sll(a0, 2);
    v0 = 0x6B0000;
    v0 = addiu(v0, -13200);  // &0x6ACC70
    v0 = addu(v0, v1);
    lh(v0, v0, 0);
}

// 0x003F00D0 sub_3F00D0 -- 248 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclLineupFind] $a0 a lineup list {count, entries}: from index *$a2 (0 when $a2 is null) finds the first 20-byte
// entry whose minimum level (u16 +4, 0 = any) the protagonist reaches and whose conditions (+12) pass sub_3F04F0(..,
// $a1); stores its index (-1 when none) and returns it (or 0).
void sub_3F00D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f00d0
    enter(ctx, 13);  // entry check point + this block's cycles
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
    sw(zero, sp, 0x7C);
    if (a2 != 0) {
        // 0x003f0110
        charge(ctx, 1);
        s1 = a2;
    } else {
        // 0x003f0104
        charge(ctx, 3);
        s1 = addiu(sp, 0x7C);
    }
    // 0x003f0114
    charge(ctx, 4);
    lw(s3, s5, 4);
    lw(s2, s1, 0);
    for (;;) {
        // 0x003f0184
        charge(ctx, 4);
        lw(v0, s5, 0);
        v0 = slt(s2, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003f0124
        charge(ctx, 3);
        lh(v0, s3, 4);
        if (v0 != 0) {
            // 0x003f0130
            charge(ctx, 9);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
            a0 = 1;
            jal(ctx, 0x3F013Cu, gen::fn_sub_16C470_0016c470);
            v0 = v0 & 0xFF;
            at = slt(v0, s0);
            if (at == 0) {
                goto L_003f0154;
            }
        L_003f0180:
            charge(ctx, 1);
            s2 = addiu(s2, 1);
            continue;
        }
    L_003f0154:
        charge(ctx, 6);
        a0 = addiu(s3, 12);
        a1 = s4;
        jal(ctx, 0x3F015Cu, gen::fn_sub_3F04F0_003f04f0);
        if (v0 != 0) {
            goto L_003f016c_7;
        }
        // 0x003f017c
        charge(ctx, 1);
        s3 = addiu(s3, 20);
        goto L_003f0180;
    }
    // 0x003f0194
    charge(ctx, 3);
    v0 = si(-1);
    sw(v0, s1, 0);
    v0 = 0;
    // 0x003f01a0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_003f016c_7:
    charge(ctx, 4);
    sw(s2, s1, 0);
    v0 = s3;
    // 0x003f01a0 (the shared epilogue, written out on this path)
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

// 0x003F01D0 sub_3F01D0 -- 100 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclLineupFindAny] Lineup list $a1 of record $a0 (+8 * $a1): sub_3F00D0 with conditions mode 1, then from index 0
// with mode 0.
void sub_3F01D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f01d0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a2;
    v0 = sll(a1, 3);
    s0 = addu(a0, v0);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x3F01F4u, gen::fn_sub_3F00D0_003f00d0);
    if (v0 == 0) {
        // 0x003f0204
        charge(ctx, 6);
        sw(zero, s1, 0);
        a0 = s0;
        a1 = 0;
        a2 = s1;
        jal(ctx, 0x3F0214u, gen::fn_sub_3F00D0_003f00d0);
    }
    // 0x003f021c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003F0240 sub_3F0240 -- 272 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopTypeHasLineup] Types 0..2 only: 1 when lineup list 1 of the record (+8) has an entry for mode 1 or 0; else 0
// (K_Assert line 185 above 8).
void sub_3F0240(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f0240
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (i64(s0) >= 0) {
        // 0x003f025c
        charge(ctx, 3);
        v0 = slti(s0, 9);
        if (v0 == 0) {
            goto L_003f0268;
        }
        goto L_003f027c;
    }
L_003f0268:
    charge(ctx, 5);
    a0 = 0x6B0000;
    a0 = addiu(a0, -4632);  // "fclShopMisc.c"
    a1 = 185;
    jal(ctx, 0x3F0274u, gen::fn_sub_19D3F0_0019d3f0);
L_003f027c:
    charge(ctx, 4);
    jal(ctx, 0x3F027Cu, gen::fn_sub_17D800_0017d800);
    if (v0 != 0) {
        // 0x003f02ac
        charge(ctx, 7);
        v1 = addiu(s0, 9);
        v0 = sll(v1, 3);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x6B0000;
        v0 = addiu(v0, -13872);  // &0x6AC9D0
        s1 = addu(v0, v1);
    } else {
        // 0x003f028c
        charge(ctx, 8);
        v0 = sll(s0, 3);
        v0 = addu(v0, s0);
        v1 = sll(v0, 2);
        v0 = 0x6B0000;
        v0 = addiu(v0, -13872);  // &0x6AC9D0
        s1 = addu(v0, v1);
    }
    // 0x003f02c8
    charge(ctx, 3);
    v0 = 2;
    if (s0 != v0) {
        // 0x003f02d4
        charge(ctx, 3);
        v0 = 1;
        if (s0 == v0) {
            goto L_003f02f0;
        }
        // 0x003f02e0
        charge(ctx, 2);
        if (s0 == 0) {
            goto L_003f02f0;
        }
        // 0x003f02e8
        charge(ctx, 2);
    L_003f0334:
        charge(ctx, 1);
        v0 = 0;
        // 0x003f0338 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_003f02f0:
    charge(ctx, 7);
    a0 = addiu(s1, 8);
    a1 = 1;
    a2 = 0;
    jal(ctx, 0x3F02FCu, gen::fn_sub_3F00D0_003f00d0);
    if (v0 == 0) {
        // 0x003f030c
        charge(ctx, 5);
        a0 = addiu(s1, 8);
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x3F0318u, gen::fn_sub_3F00D0_003f00d0);
    }
    // 0x003f0320
    charge(ctx, 2);
    if (v0 == 0) {
        goto L_003f0334;
    }
    // 0x003f0328
    charge(ctx, 3);
    v0 = 1;
    // 0x003f0338 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003F0350 sub_3F0350 -- 136 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclLevelEntryNext] The next 12-byte level entry of record $a0 (count +24, entries +28) at index *$a1, which it
// advances; 0 at the end. K_Assert fclShopMisc.c:315 on a null index.
void sub_3F0350(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f0350
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s1 = a1;
    if (s1 == 0) {
        // 0x003f0370
        charge(ctx, 5);
        a0 = 0x6B0000;
        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
        a1 = 315;
        jal(ctx, 0x3F037Cu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003f0384
    charge(ctx, 5);
    lw(v1, s1, 0);
    lw(v0, s0, 24);
    v0 = slt(v1, v0);
    if (v0 != 0) {
        // 0x003f03a4
        charge(ctx, 7);
        v0 = addiu(v1, 1);
        sw(v0, s1, 0);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        lw(v0, s0, 28);
        v0 = addu(v0, v1);
    } else {
        // 0x003f0398
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003f03c0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003F03E0 sub_3F03E0 -- 268 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopLinkRank] The social link of the shop (type 8 -> link 2, 4 -> 3, 0 -> 15; others 0): its rank (sub_16DBA0;
// K_Assert 348 outside 1..10) when the link is active (sub_16E100), else 0.
void sub_3F03E0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f03e0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = 8;
    if (a0 == v0) {
        // 0x003f042c
        charge(ctx, 3);
        s0 = 2;
    L_003f0444:
        charge(ctx, 3);
        v0 = 255;
        if (s0 != v0) {
            // 0x003f045c
            charge(ctx, 6);
            a0 = dsll32(s0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x3F0464u, gen::fn_sub_16E100_0016e100);
            if (v0 != 0) {
                // 0x003f0480
                charge(ctx, 8);
                a0 = dsll32(s0, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x3F0488u, gen::fn_sub_16DBA0_0016dba0);
                s0 = dsll32(v0, 24);
                s0 = dsra32(s0, 24);
                if (s0 != 0) {
                    // 0x003f04ac
                    charge(ctx, 2);
                    if (i64(s0) > 0) {
                        // 0x003f04b4
                        charge(ctx, 3);
                        at = slti(s0, 11);
                        if (at == 0) {
                            goto L_003f04c0;
                        }
                        goto L_003f04d4;
                    }
                L_003f04c0:
                    charge(ctx, 5);
                    a0 = 0x6B0000;
                    a0 = addiu(a0, -4632);  // "fclShopMisc.c"
                    a1 = 348;
                    jal(ctx, 0x3F04CCu, gen::fn_sub_19D3F0_0019d3f0);
                L_003f04d4:
                    charge(ctx, 1);
                    v0 = s0;
                } else {
                    // 0x003f04a0
                    charge(ctx, 3);
                    v0 = 0;
                }
            } else {
                // 0x003f0474
                charge(ctx, 3);
                v0 = 0;
            }
        } else {
            // 0x003f0450
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003f03f8
        charge(ctx, 3);
        v0 = 4;
        if (a0 == v0) {
            // 0x003f0420
            charge(ctx, 3);
            s0 = 3;
            goto L_003f0444;
        }
        // 0x003f0404
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x003f0414
            charge(ctx, 3);
            s0 = 15;
            goto L_003f0444;
        }
        // 0x003f040c
        charge(ctx, 2);
        // 0x003f0438
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003f04d8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003F06E0 sub_3F06E0 -- 332 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclMessageSelect] $a0 a message list {count, 24-byte entries}: the first entry that passes -- entries flagged 4 or
// 1 are skipped while the shop's link has a rank, the story flag (u16 +4; 0xFFFF none) must be set (datGetFlag), the
// conditions (+16) must pass sub_3F04F0(.., $a1); an entry with flag 2 sets its story flag (datSetFlag: said once).
// Returns the entry or 0.
void sub_3F06E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f06e0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    lw(s1, a0, 4);
    s0 = 0;
    for (;;) {
        // 0x003f07f8
        charge(ctx, 4);
        lw(v0, s3, 0);
        v0 = slt(s0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003f0710
        charge(ctx, 4);
        lw(v0, s1, 0);
        v0 = v0 & 0x4;
        if (v0 != 0) {
            // 0x003f0720
            charge(ctx, 7);
            jal(ctx, 0x3F0720u, gen::fn_sub_3E6DC0_003e6dc0);
            a0 = v0;
            jal(ctx, 0x3F072Cu, gen::fn_sub_3F03E0_003f03e0);
            if (v0 == 0) {
                goto L_003f0748;
            }
            // 0x003f073c
            charge(ctx, 3);
            s1 = addiu(s1, 24);
        L_003f07f4:
            charge(ctx, 1);
            s0 = addiu(s0, 1);
            continue;
        }
    L_003f0748:
        charge(ctx, 4);
        lw(v0, s1, 0);
        v0 = v0 & 0x1;
        if (v0 != 0) {
            // 0x003f0758
            charge(ctx, 7);
            jal(ctx, 0x3F0758u, gen::fn_sub_3E6DC0_003e6dc0);
            a0 = v0;
            jal(ctx, 0x3F0764u, gen::fn_sub_3F03E0_003f03e0);
            if (v0 == 0) {
                goto L_003f0780;
            }
            // 0x003f0774
            charge(ctx, 3);
            s1 = addiu(s1, 24);
            goto L_003f07f4;
        }
    L_003f0780:
        charge(ctx, 4);
        lhu(a0, s1, 4);
        v0 = 0xFFFF;
        if (a0 != v0) {
            // 0x003f0790
            charge(ctx, 4);
            jal(ctx, 0x3F0790u, gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                goto L_003f07a0;
            }
        L_003f07f0:
            charge(ctx, 1);
            s1 = addiu(s1, 24);
            goto L_003f07f4;
        }
    L_003f07a0:
        charge(ctx, 6);
        a0 = addiu(s1, 16);
        a1 = s2;
        jal(ctx, 0x3F07A8u, gen::fn_sub_3F04F0_003f04f0);
        if (v0 == 0) {
            goto L_003f07f0;
        }
        goto L_003f07b8_10;
    }
    // 0x003f0808
    charge(ctx, 1);
    v0 = 0;
    // 0x003f080c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_003f07b8_10:
    charge(ctx, 4);
    lhu(a0, s1, 4);
    v0 = 0xFFFF;
    if (a0 != v0) {
        // 0x003f07c8
        charge(ctx, 4);
        lw(v0, s1, 0);
        v0 = v0 & 0x2;
        if (v0 != 0) {
            // 0x003f07d8
            charge(ctx, 3);
            a1 = 0;
            jal(ctx, 0x3F07DCu, gen::fn_datSetFlag_0016f1f0);
        }
    }
    // 0x003f07e4
    charge(ctx, 3);
    v0 = s1;
    // 0x003f080c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003F0830 sub_3F0830 -- 644 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopGreeting] The greeting message of type $a0: the conditional list (record +32 -> +20, mode 1); else, for
// types 0 / 4 / others, the link-rank table (+8, 32 bytes per rank; s16 +12); else the list with mode 0. The entry's
// message is picked at index rand() % 0xFFFF / 0xFFFF (sub_488F30), which is always 0. Returns the message id or -1.
// K_Asserts lines 185 / 412 / 418.
void sub_3F0830(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f0830
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = 4;
    if (s0 == v0) {
        // 0x003f0870
        charge(ctx, 3);
        s2 = 3;
    } else {
        // 0x003f0854
        charge(ctx, 2);
        if (s0 == 0) {
            // 0x003f0864
            charge(ctx, 3);
            s2 = 15;
        } else {
            // 0x003f085c
            charge(ctx, 2);
            // 0x003f087c
            charge(ctx, 1);
            s2 = 255;
        }
    }
    // 0x003f0880
    charge(ctx, 2);
    if (i64(s0) >= 0) {
        // 0x003f0888
        charge(ctx, 3);
        v0 = slti(s0, 9);
        if (v0 == 0) {
            goto L_003f0894;
        }
        goto L_003f08a8;
    }
L_003f0894:
    charge(ctx, 5);
    a0 = 0x6B0000;
    a0 = addiu(a0, -4632);  // "fclShopMisc.c"
    a1 = 185;
    jal(ctx, 0x3F08A0u, gen::fn_sub_19D3F0_0019d3f0);
L_003f08a8:
    charge(ctx, 4);
    jal(ctx, 0x3F08A8u, gen::fn_sub_17D800_0017d800);
    if (v0 != 0) {
        // 0x003f08d8
        charge(ctx, 7);
        v1 = addiu(s0, 9);
        v0 = sll(v1, 3);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x6B0000;
        v0 = addiu(v0, -13872);  // &0x6AC9D0
        v0 = addu(v0, v1);
    } else {
        // 0x003f08b8
        charge(ctx, 8);
        v0 = sll(s0, 3);
        v0 = addu(v0, s0);
        v1 = sll(v0, 2);
        v0 = 0x6B0000;
        v0 = addiu(v0, -13872);  // &0x6AC9D0
        v0 = addu(v0, v1);
    }
    // 0x003f08f4
    charge(ctx, 8);
    lw(s1, v0, 32);
    a0 = addiu(s1, 20);
    a1 = 1;
    jal(ctx, 0x3F0900u, gen::fn_sub_3F06E0_003f06e0);
    s0 = v0;
    if (s0 == 0) {
        // 0x003f0954
        charge(ctx, 3);
        v0 = 255;
        if (s2 != v0) {
            // 0x003f0960
            charge(ctx, 3);
            lw(v0, s1, 8);
            if (v0 == 0) {
                // 0x003f096c
                charge(ctx, 5);
                a0 = 0x6B0000;
                a0 = addiu(a0, -4632);  // "fclShopMisc.c"
                a1 = 412;
                jal(ctx, 0x3F0978u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x003f0980
            charge(ctx, 3);
            v0 = 255;
            if (s2 != v0) {
                // 0x003f0998
                charge(ctx, 6);
                a0 = dsll32(s2, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x3F09A0u, gen::fn_sub_16E100_0016e100);
                if (v0 != 0) {
                    // 0x003f09bc
                    charge(ctx, 8);
                    a0 = dsll32(s2, 16);
                    a0 = dsra32(a0, 16);
                    jal(ctx, 0x3F09C4u, gen::fn_sub_16DBA0_0016dba0);
                    s0 = dsll32(v0, 24);
                    s0 = dsra32(s0, 24);
                    if (s0 != 0) {
                        // 0x003f09e8
                        charge(ctx, 2);
                        if (i64(s0) > 0) {
                            // 0x003f09f0
                            charge(ctx, 3);
                            at = slti(s0, 11);
                            if (at == 0) {
                                goto L_003f09fc;
                            }
                            goto L_003f0a10;
                        }
                    L_003f09fc:
                        charge(ctx, 5);
                        a0 = 0x6B0000;
                        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
                        a1 = 418;
                        jal(ctx, 0x3F0A08u, gen::fn_sub_19D3F0_0019d3f0);
                    L_003f0a10:
                        charge(ctx, 3);
                        v1 = sll(s0, 5);
                        lw(v0, s1, 8);
                        v0 = addu(v0, v1);
                    } else {
                        // 0x003f09dc
                        charge(ctx, 3);
                        lw(v0, s1, 8);
                    }
                } else {
                    // 0x003f09b0
                    charge(ctx, 3);
                    lw(v0, s1, 8);
                }
            } else {
                // 0x003f098c
                charge(ctx, 3);
                lw(v0, s1, 8);
            }
            // 0x003f0a1c
            charge(ctx, 2);
            if (v0 == 0) {
                goto L_003f0a3c;
            }
            // 0x003f0a24
            charge(ctx, 4);
            lh(v0, v0, 12);
            v1 = si(-1);
            if (v0 == v1) {
                goto L_003f0a3c;
            }
            // 0x003f0a34
            charge(ctx, 2);
            // 0x003f0a98 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_003f0a3c:
        charge(ctx, 7);
        a0 = addiu(s1, 20);
        a1 = 0;
        jal(ctx, 0x3F0A44u, gen::fn_sub_3F06E0_003f06e0);
        s0 = v0;
        if (s0 == 0) {
        L_003f0a94:
            charge(ctx, 1);
            v0 = si(-1);
        } else {
            // 0x003f0a58
            charge(ctx, 13);
            jal(ctx, 0x3F0A58u, gen::fn_sub_488F30_00488f30);
            v1 = 0xFFFF;
            divu(v0, v1);
            mfhi(v0);
            divu(v0, v1);
            mflo(v0);
            v0 = sll(v0, 1);
            v0 = addu(v0, s0);
            lh(v0, v0, 8);
            v1 = si(-1);
            if (v0 == v1) {
                goto L_003f0a94;
            }
            // 0x003f0a8c
            charge(ctx, 2);
        }
    } else {
        // 0x003f0914
        charge(ctx, 13);
        jal(ctx, 0x3F0914u, gen::fn_sub_488F30_00488f30);
        v1 = 0xFFFF;
        divu(v0, v1);
        mfhi(v0);
        divu(v0, v1);
        mflo(v0);
        v0 = sll(v0, 1);
        v0 = addu(v0, s0);
        lh(v1, v0, 8);
        v0 = si(-1);
        if (v1 == v0) {
            goto L_003f0a94;
        }
        // 0x003f0948
        charge(ctx, 3);
        lh(v0, s0, 8);
    }
    // 0x003f0a98 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003F0D60 sub_3F0D60 -- 340 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopLinkPurchase] Tells the shop's social link about a purchase: type 8 / 4 pass $a1, type 0 a value from the
// item's record (sub_170ED0; field by item kind 0..4) -- sub_16E2B0(link, value) when the link is active; returns the
// value (0 without a link).
void sub_3F0D60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f0d60
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = 8;
    if (a0 == v0) {
        // 0x003f0e40
        charge(ctx, 5);
        s0 = 2;
        s1 = dsll32(a1, 16);
        s1 = dsra32(s1, 16);
    L_003f0e60:
        charge(ctx, 6);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x3F0E68u, gen::fn_sub_16E100_0016e100);
        if (v0 != 0) {
            // 0x003f0e84
            charge(ctx, 6);
            a0 = dsll32(s0, 16);
            a0 = dsra32(a0, 16);
            a1 = s1;
            jal(ctx, 0x3F0E90u, gen::fn_sub_16E2B0_0016e2b0);
            v0 = s1;
        } else {
            // 0x003f0e78
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003f0d7c
        charge(ctx, 3);
        v0 = 4;
        if (a0 == v0) {
            // 0x003f0e2c
            charge(ctx, 5);
            s0 = 3;
            s1 = dsll32(a1, 16);
            s1 = dsra32(s1, 16);
            goto L_003f0e60;
        }
        // 0x003f0d88
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x003f0d98
            charge(ctx, 9);
            s0 = 15;
            a0 = a1;
            a1 = addiu(sp, 0x3C);
            jal(ctx, 0x3F0DA4u, gen::fn_sub_170ED0_00170ed0);
            lw(a0, sp, 0x3C);
            v1 = 4;
            if (a0 == v1) {
                // 0x003f0e20
                charge(ctx, 1);
                lw(s1, v0, 24);
            } else {
                // 0x003f0dbc
                charge(ctx, 3);
                v1 = 3;
                if (a0 == v1) {
                    // 0x003f0e14
                    charge(ctx, 3);
                    lw(s1, v0, 32);
                } else {
                    // 0x003f0dc8
                    charge(ctx, 3);
                    v1 = 2;
                    if (a0 == v1) {
                        // 0x003f0e08
                        charge(ctx, 3);
                        lw(s1, v0, 28);
                    } else {
                        // 0x003f0dd4
                        charge(ctx, 3);
                        v1 = 1;
                        if (a0 == v1) {
                            // 0x003f0dfc
                            charge(ctx, 3);
                            lw(s1, v0, 28);
                        } else {
                            // 0x003f0de0
                            charge(ctx, 2);
                            if (a0 == 0) {
                                // 0x003f0df0
                                charge(ctx, 3);
                                lw(s1, v0, 36);
                            } else {
                                // 0x003f0de8
                                charge(ctx, 2);
                            }
                        }
                    }
                }
            }
            // 0x003f0e24
            charge(ctx, 2);
            goto L_003f0e60;
        }
        // 0x003f0d90
        charge(ctx, 2);
        // 0x003f0e54
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003f0e9c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003F10B0 sub_3F10B0 -- 484 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopRankItemMessage] Types 0 / 4: the message for item $a1 in the link-rank table (rank row s16 +14 + 2 *
// sub_3F0EC0(item)); -1 otherwise.
void sub_3F10B0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f10b0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s2 = a1;
    v0 = 4;
    if (s0 == v0) {
        // 0x003f10f4
        charge(ctx, 3);
        s1 = 3;
    L_003f110c:
        charge(ctx, 2);
        if (i64(s0) >= 0) {
            // 0x003f1114
            charge(ctx, 3);
            v0 = slti(s0, 9);
            if (v0 == 0) {
                goto L_003f1120;
            }
            goto L_003f1134;
        }
    L_003f1120:
        charge(ctx, 5);
        a0 = 0x6B0000;
        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
        a1 = 185;
        jal(ctx, 0x3F112Cu, gen::fn_sub_19D3F0_0019d3f0);
    L_003f1134:
        charge(ctx, 4);
        jal(ctx, 0x3F1134u, gen::fn_sub_17D800_0017d800);
        if (v0 != 0) {
            // 0x003f1164
            charge(ctx, 7);
            v1 = addiu(s0, 9);
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v1 = sll(v0, 2);
            v0 = 0x6B0000;
            v0 = addiu(v0, -13872);  // &0x6AC9D0
            v0 = addu(v0, v1);
        } else {
            // 0x003f1144
            charge(ctx, 8);
            v0 = sll(s0, 3);
            v0 = addu(v0, s0);
            v1 = sll(v0, 2);
            v0 = 0x6B0000;
            v0 = addiu(v0, -13872);  // &0x6AC9D0
            v0 = addu(v0, v1);
        }
        // 0x003f1180
        charge(ctx, 4);
        lw(s0, v0, 32);
        lw(v0, s0, 8);
        if (v0 == 0) {
            // 0x003f1190
            charge(ctx, 5);
            a0 = 0x6B0000;
            a0 = addiu(a0, -4632);  // "fclShopMisc.c"
            a1 = 412;
            jal(ctx, 0x3F119Cu, gen::fn_sub_19D3F0_0019d3f0);
        }
        // 0x003f11a4
        charge(ctx, 3);
        v0 = 255;
        if (s1 != v0) {
            // 0x003f11bc
            charge(ctx, 6);
            a0 = dsll32(s1, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x3F11C4u, gen::fn_sub_16E100_0016e100);
            if (v0 != 0) {
                // 0x003f11e0
                charge(ctx, 8);
                a0 = dsll32(s1, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x3F11E8u, gen::fn_sub_16DBA0_0016dba0);
                s1 = dsll32(v0, 24);
                s1 = dsra32(s1, 24);
                if (s1 != 0) {
                    // 0x003f120c
                    charge(ctx, 2);
                    if (i64(s1) > 0) {
                        // 0x003f1214
                        charge(ctx, 3);
                        at = slti(s1, 11);
                        if (at == 0) {
                            goto L_003f1220;
                        }
                        goto L_003f1234;
                    }
                L_003f1220:
                    charge(ctx, 5);
                    a0 = 0x6B0000;
                    a0 = addiu(a0, -4632);  // "fclShopMisc.c"
                    a1 = 418;
                    jal(ctx, 0x3F122Cu, gen::fn_sub_19D3F0_0019d3f0);
                L_003f1234:
                    charge(ctx, 3);
                    v1 = sll(s1, 5);
                    lw(v0, s0, 8);
                    s0 = addu(v0, v1);
                } else {
                    // 0x003f1200
                    charge(ctx, 3);
                    lw(s0, s0, 8);
                }
            } else {
                // 0x003f11d4
                charge(ctx, 3);
                lw(s0, s0, 8);
            }
        } else {
            // 0x003f11b0
            charge(ctx, 3);
            lw(s0, s0, 8);
        }
        // 0x003f1240
        charge(ctx, 2);
        if (s0 != 0) {
            // 0x003f1248
            charge(ctx, 6);
            a0 = dsll32(s2, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x3F1250u, gen::fn_sub_3F0EC0_003f0ec0);
            if (v0 == 0) {
                goto L_003f1274;
            }
            // 0x003f1260
            charge(ctx, 5);
            v0 = sll(v0, 1);
            v0 = addu(v0, s0);
            lh(v0, v0, 14);
            // 0x003f1278 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_003f1274:
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x003f10d8
        charge(ctx, 2);
        if (s0 == 0) {
            // 0x003f10e8
            charge(ctx, 3);
            s1 = 15;
            goto L_003f110c;
        }
        // 0x003f10e0
        charge(ctx, 2);
        // 0x003f1100
        charge(ctx, 3);
        v0 = si(-1);
    }
    // 0x003f1278 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003F1470 sub_3F1470 -- 168 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclShopLinkCanAdvance] The shop's social link (8 -> 2, 4 -> 3, 0 -> 15): sub_172660(link) when active, else 0.
void sub_3F1470(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f1470
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    v0 = 8;
    if (a0 == v0) {
        // 0x003f14bc
        charge(ctx, 3);
        s0 = 2;
    L_003f14d4:
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x3F14D8u, gen::fn_sub_16E100_0016e100);
        if (v0 != 0) {
            // 0x003f14f4
            charge(ctx, 4);
            a0 = dsll32(s0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x3F14FCu, gen::fn_sub_172660_00172660);
        } else {
            // 0x003f14e8
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x003f1488
        charge(ctx, 3);
        v0 = 4;
        if (a0 == v0) {
            // 0x003f14b0
            charge(ctx, 3);
            s0 = 3;
            goto L_003f14d4;
        }
        // 0x003f1494
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x003f14a4
            charge(ctx, 3);
            s0 = 15;
            goto L_003f14d4;
        }
        // 0x003f149c
        charge(ctx, 2);
        // 0x003f14c8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003f1504 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003F15D0 sub_3F15D0 -- 180 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclAddMoney] yen += $a0 * $a1, clamped to 0..9,999,999 (sub_16DD50 / sub_16E930); returns the change applied.
// Buying passes a negative price.
void sub_3F15D0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f15d0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    jal(ctx, 0x3F15F0u, gen::fn_sub_16DD50_0016dd50);
    s1 = v0;
    s0 = s1;
    mult(a0, s3, s2);
    v1 = addu(s1, a0);
    at = 0x980000;
    at = at | 0x9680;  // 10,000,000 (a constant, not an address)
    at = slt(v1, at);
    if (at == 0) {
        // 0x003f161c
        charge(ctx, 2);
        v0 = 0x980000;
        s0 = v0 | 0x967F;  // 9,999,999 = shop::kYenMax (a constant, not an address)
    }
    // 0x003f1624
    charge(ctx, 2);
    if (i64(v1) >= 0) {
        // 0x003f1638
        charge(ctx, 1);
        s0 = addu(s0, a0);
    } else {
        // 0x003f162c
        charge(ctx, 3);
        s0 = 0;
    }
    // 0x003f163c
    charge(ctx, 5);
    v0 = 0x980000;
    v1 = v0 | 0x967F;  // 9,999,999 = shop::kYenMax (a constant, not an address)
    v0 = slt(s0, v1);
    if (v0 == 0) {
        // 0x003f1650
        charge(ctx, 1);
        s0 = v1;
    }
    // 0x003f1654
    charge(ctx, 12);
    a0 = s0;
    jal(ctx, 0x3F1658u, gen::fn_sub_16E930_0016e930);
    v0 = subu(s0, s1);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003F1720 sub_3F1720 -- 260 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclGiveItem] Gives $a1 of item $a0: consumables (kind 4, sub_170ED0) through sub_170C00(1, item, n); equipment
// (kinds 0..3) as a new instance (sub_1828D0, sub_3F1690); then the purchase log sub_17D1A0(type, item, n). Returns
// the item / instance.
void sub_3F1720(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f1720
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    v0 = si(-1);
    sw(v0, sp, 0x5C);
    a1 = addiu(sp, 0x5C);
    jal(ctx, 0x3F1748u, gen::fn_sub_170ED0_00170ed0);
    lw(v1, sp, 0x5C);
    v0 = 4;
    if (v1 == v0) {
        // 0x003f17bc
        charge(ctx, 8);
        a2 = dsll32(s1, 16);
        a2 = dsra32(a2, 16);
        a0 = 1;
        a1 = s2;
        jal(ctx, 0x3F17CCu, gen::fn_sub_170C00_00170c00);
        s0 = dsll32(s2, 16);
        s0 = dsra32(s0, 16);
    } else {
        // 0x003f1760
        charge(ctx, 3);
        v0 = 3;
        if (v1 != v0) {
            // 0x003f176c
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                goto L_003f1794;
            }
            // 0x003f1778
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_003f1794;
            }
            // 0x003f1784
            charge(ctx, 2);
            if (v1 == 0) {
                goto L_003f1794;
            }
            // 0x003f178c
            charge(ctx, 2);
            goto L_003f17dc;
        }
    L_003f1794:
        charge(ctx, 10);
        a0 = s2;
        a1 = addiu(sp, 0x40);
        jal(ctx, 0x3F179Cu, gen::fn_sub_1828D0_001828d0);
        a0 = addiu(sp, 0x40);
        jal(ctx, 0x3F17A8u, gen::fn_sub_3F1690_003f1690);
        s0 = v0;
    }
L_003f17dc:
    charge(ctx, 18);
    jal(ctx, 0x3F17DCu, gen::fn_sub_3E6DC0_003e6dc0);
    sh(v0, sp, 0x58);
    sh(zero, sp, 0x5A);
    a1 = s2 & 0xFFFF;
    a2 = dsll32(s1, 16);
    a2 = dsra32(a2, 16);
    lw(a0, sp, 0x58);
    jal(ctx, 0x3F17FCu, gen::fn_sub_17D1A0_0017d1a0);
    v0 = s0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003F1830 sub_3F1830 -- 212 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclTakeItem] Takes $a1 of the row's item: consumables sub_170C00(1, item, -n), equipment sub_16FEA0(1, slot, 0).
// Returns 1.
void sub_3F1830(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f1830
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s2 = a1;
    v0 = si(-1);
    sw(v0, sp, 0x4C);
    lh(s1, a0, 0);
    a0 = s1;
    a1 = addiu(sp, 0x4C);
    jal(ctx, 0x3F1860u, gen::fn_sub_170ED0_00170ed0);
    lw(v1, sp, 0x4C);
    v0 = 4;
    if (v1 == v0) {
        // 0x003f18c8
        charge(ctx, 7);
        v0 = subu(0, s2);
        a2 = dsll32(v0, 16);
        a2 = dsra32(a2, 16);
        a0 = 1;
        a1 = s1;
        jal(ctx, 0x3F18DCu, gen::fn_sub_170C00_00170c00);
    } else {
        // 0x003f1878
        charge(ctx, 3);
        v0 = 3;
        if (v1 != v0) {
            // 0x003f1884
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                goto L_003f18ac;
            }
            // 0x003f1890
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_003f18ac;
            }
            // 0x003f189c
            charge(ctx, 2);
            if (v1 == 0) {
                goto L_003f18ac;
            }
            // 0x003f18a4
            charge(ctx, 2);
            // 0x003f18e4 (the shared epilogue, written out on this path)
            charge(ctx, 8);
            v0 = 1;
            ld(ra, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x50);
            return;
        }
    L_003f18ac:
        charge(ctx, 7);
        lh(a1, s0, 2);
        a0 = 1;
        a2 = 0;
        jal(ctx, 0x3F18B8u, gen::fn_sub_16FEA0_0016fea0);
    }
    // 0x003f18e4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = 1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003F1A10 sub_3F1A10 -- 396 bytes; leaf frame (no stack)
// [fclItemCategory] The sort / category code of an item's flag word: base 0x4000 (0x1000 when any of the low 19 bits
// is set), 0x2000 and the high byte for flags in 0xFF00, then the first set flag bit 1..7 or 0x10000.. 0x100000
// mapped to 1..7 / 0x109 / 0x20A / 0x30B / 0x40D / 0x40E; 0 for none. A leaf.
void sub_3F1A10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003f1a10
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0;
    v1 = dsll32(a0, 13);
    v1 = dsrl32(v1, 13);
    if (v1 == 0) {
        // 0x003f1a30
        charge(ctx, 1);
        v0 = v0 | 0x4000;
    } else {
        // 0x003f1a24
        charge(ctx, 3);
        v0 = v0 | 0x1000;
    }
    // 0x003f1a34
    charge(ctx, 3);
    v1 = a0 & 0xFF00;
    if (v1 != 0) {
        // 0x003f1a40
        charge(ctx, 2);
        a0 = srl(a0, 8);
        v0 = v0 | 0x2000;
    }
    // 0x003f1a48
    charge(ctx, 3);
    v1 = a0 & 0x1;
    if (v1 == 0) {
        // 0x003f1a5c
        charge(ctx, 3);
        v1 = a0 & 0x2;
        if (v1 == 0) {
            // 0x003f1a74
            charge(ctx, 3);
            v1 = a0 & 0x4;
            if (v1 == 0) {
                // 0x003f1a8c
                charge(ctx, 3);
                v1 = a0 & 0x8;
                if (v1 == 0) {
                    // 0x003f1aa4
                    charge(ctx, 3);
                    v1 = a0 & 0x10;
                    if (v1 == 0) {
                        // 0x003f1abc
                        charge(ctx, 3);
                        v1 = a0 & 0x20;
                        if (v1 == 0) {
                            // 0x003f1ad4
                            charge(ctx, 3);
                            v1 = a0 & 0x40;
                            if (v1 == 0) {
                                // 0x003f1aec
                                charge(ctx, 3);
                                v1 = a0 & 0x80;
                                if (v1 == 0) {
                                    // 0x003f1b04
                                    charge(ctx, 4);
                                    v1 = 0x10000;
                                    v1 = a0 & v1;
                                    if (v1 == 0) {
                                        // 0x003f1b20
                                        charge(ctx, 4);
                                        v1 = 0x20000;
                                        v1 = a0 & v1;
                                        if (v1 == 0) {
                                            // 0x003f1b3c
                                            charge(ctx, 4);
                                            v1 = 0x40000;
                                            v1 = a0 & v1;
                                            if (v1 == 0) {
                                                // 0x003f1b58
                                                charge(ctx, 4);
                                                v1 = 0x80000;
                                                v1 = a0 & v1;
                                                if (v1 == 0) {
                                                    // 0x003f1b74
                                                    charge(ctx, 4);
                                                    v1 = 0x100000;
                                                    v1 = a0 & v1;
                                                    if (v1 == 0) {
                                                        // 0x003f1b90
                                                        charge(ctx, 1);
                                                        v0 = 0;
                                                    } else {
                                                        // 0x003f1b84
                                                        charge(ctx, 3);
                                                        v0 = v0 | 0x40E;
                                                    }
                                                } else {
                                                    // 0x003f1b68
                                                    charge(ctx, 3);
                                                    v0 = v0 | 0x40D;
                                                }
                                            } else {
                                                // 0x003f1b4c
                                                charge(ctx, 3);
                                                v0 = v0 | 0x30B;
                                            }
                                        } else {
                                            // 0x003f1b30
                                            charge(ctx, 3);
                                            v0 = v0 | 0x20A;
                                        }
                                    } else {
                                        // 0x003f1b14
                                        charge(ctx, 3);
                                        v0 = v0 | 0x109;
                                    }
                                } else {
                                    // 0x003f1af8
                                    charge(ctx, 3);
                                    v0 = v0 | 0x7;
                                }
                            } else {
                                // 0x003f1ae0
                                charge(ctx, 3);
                                v0 = v0 | 0x6;
                            }
                        } else {
                            // 0x003f1ac8
                            charge(ctx, 3);
                            v0 = v0 | 0x5;
                        }
                    } else {
                        // 0x003f1ab0
                        charge(ctx, 3);
                        v0 = v0 | 0x4;
                    }
                } else {
                    // 0x003f1a98
                    charge(ctx, 3);
                    v0 = v0 | 0x3;
                }
            } else {
                // 0x003f1a80
                charge(ctx, 3);
                v0 = v0 | 0x2;
            }
        } else {
            // 0x003f1a68
            charge(ctx, 3);
            v0 = v0 | 0x1;
        }
    } else {
        // 0x003f1a54
        charge(ctx, 2);
    }
    // 0x003f1b94 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003F2240 sub_3F2240 -- 216 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclInventoryRow] Fills the 28-byte row $a0 for item $a1 (memset first; K_Assert 1104 on null): when owned
// (sub_170760(1, item)): the id, the category (sub_3F1A10 of the item record's flags), the price (+12) and the count
// (+10). Returns 1 / 0.
void sub_3F2240(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f2240
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    if (s3 == 0) {
        // 0x003f2268
        charge(ctx, 5);
        a0 = 0x6B0000;
        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
        a1 = 1104;
        jal(ctx, 0x3F2274u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003f227c
    charge(ctx, 14);
    a0 = s3;
    a1 = 0;
    a2 = 28;
    jal(ctx, 0x3F2288u, gen::fn_memset_00521408);
    a1 = dsll32(s2, 16);
    a1 = dsra32(a1, 16);
    a0 = 1;
    jal(ctx, 0x3F229Cu, gen::fn_sub_170760_00170760);
    s1 = dsll32(v0, 16);
    s1 = dsra32(s1, 16);
    if (s1 != 0) {
        // 0x003f22c0
        charge(ctx, 14);
        a0 = dsll32(s2, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x3F22C8u, gen::fn_sub_170E90_00170e90);
        s0 = v0;
        sh(s2, s3, 0);
        lw(a0, v0, 0);
        jal(ctx, 0x3F22DCu, gen::fn_sub_3F1A10_003f1a10);
        sw(v0, s3, 4);
        lw(v0, s0, 12);
        sw(v0, s3, 12);
        sh(s1, s3, 10);
        v0 = 1;
    } else {
        // 0x003f22b4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x003f22f8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x003F2510 sub_3F2510 -- 200 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclShopFlagMask] The 8 story flags of 0x6ACC60 as a bit mask (0xFFFF entries skipped); bit 6 is also set in the
// 'AGS_' variant.
void sub_3F2510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f2510
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    s0 = 0;
    for (;;) {
        // 0x003f25b0
        charge(ctx, 3);
        v0 = sltiu(s0, 8);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003f2530
        charge(ctx, 8);
        v1 = sll(s0, 1);
        v0 = 0x6B0000;
        v0 = addiu(v0, -13216);  // &0x6ACC60
        v0 = addu(v0, v1);
        lh(a0, v0, 0);
        v0 = si(-1);
        if (a0 != v0) {
            // 0x003f2550
            charge(ctx, 4);
            jal(ctx, 0x3F2550u, gen::fn_datGetFlag_0016f190);
            if (v0 == 0) {
                goto L_003f257c;
            }
            // 0x003f2560
            charge(ctx, 7);
            v0 = 1;
            v0 = sllv(v0, s0);
            v0 = v0 & 0xFFFF;
            v0 = s1 | v0;
            s1 = v0 & 0xFFFF;
            goto L_003f25ac;
        }
    L_003f257c:
        charge(ctx, 3);
        v0 = 6;
        if (s0 == v0) {
            // 0x003f2588
            charge(ctx, 4);
            jal(ctx, 0x3F2588u, gen::fn_sub_17D800_0017d800);
            if (v0 != 0) {
                // 0x003f2598
                charge(ctx, 5);
                v0 = 1;
                v0 = sllv(v0, s0);
                v0 = v0 & 0xFFFF;
                v0 = s1 | v0;
                s1 = v0 & 0xFFFF;
            }
        }
    L_003f25ac:
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x003f25bc
    charge(ctx, 7);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003F2D60 sub_3F2D60 -- 92 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBuyRowsRefresh] sub_3F2DC0 for every row of list $a0. Returns 0.
void sub_3F2D60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f2d60
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, 4);
    for (;;) {
        // 0x003f2d94
        charge(ctx, 3);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003f2d80
        charge(ctx, 5);
        a0 = s1;
        a1 = s0;
        jal(ctx, 0x3F2D88u, gen::fn_sub_3F2DC0_003f2dc0);
        lw(s0, s0, 16);
    }
    // 0x003f2da0
    charge(ctx, 7);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003F2DC0 sub_3F2DC0 -- 428 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBuyRowRefresh] Recounts a lineup row: owned count (+14; consumables sub_170760, equipment by walking the 300
// inventory slots), then flag 0x10 (greyed) at 99 owned, when the price (+16) exceeds the yen, or when
// sub_17D250(type, item) refuses (also flag 0x20). Returns 0.
void sub_3F2DC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f2dc0
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a1, 20);
    lw(s0, v0, 28);
    lw(v1, s0, 0);
    v0 = si(-17);
    v0 = v1 & v0;
    sw(v0, s0, 0);
    lh(s2, s0, 4);
    v0 = si(-1);
    sw(v0, sp, 0x5C);
    s3 = 0;
    a0 = s2;
    a1 = addiu(sp, 0x5C);
    jal(ctx, 0x3F2E08u, gen::fn_sub_170ED0_00170ed0);
    lw(v1, sp, 0x5C);
    v0 = 4;
    if (v1 == v0) {
        // 0x003f2ea0
        charge(ctx, 5);
        a0 = 1;
        a1 = s2;
        jal(ctx, 0x3F2EA8u, gen::fn_sub_170760_00170760);
        s3 = v0 & 0xFFFF;
    } else {
        // 0x003f2e20
        charge(ctx, 3);
        v0 = 3;
        if (v1 != v0) {
            // 0x003f2e2c
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                goto L_003f2e54;
            }
            // 0x003f2e38
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                goto L_003f2e54;
            }
            // 0x003f2e44
            charge(ctx, 2);
            if (v1 == 0) {
                goto L_003f2e54;
            }
            // 0x003f2e4c
            charge(ctx, 2);
            goto L_003f2eb4;
        }
    L_003f2e54:
        charge(ctx, 5);
        s1 = 0;
        s2 = dsll32(s2, 16);
        s2 = dsra32(s2, 16);
        for (;;) {
            // 0x003f2e8c
            charge(ctx, 3);
            v0 = slti(s1, 300);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003f2e68
            charge(ctx, 7);
            a0 = 1;
            a1 = s1;
            jal(ctx, 0x3F2E70u, gen::fn_sub_16F630_0016f630);
            v0 = v0 & 0xFFFF;
            if (s2 == v0) {
                // 0x003f2e84
                charge(ctx, 1);
                s3 = addiu(s3, 1);
            }
            // 0x003f2e88
            charge(ctx, 1);
            s1 = addiu(s1, 1);
        }
        // 0x003f2e98
        charge(ctx, 2);
    }
L_003f2eb4:
    charge(ctx, 6);
    sh(s3, s0, 14);
    v0 = dsll32(s3, 16);
    v0 = dsra32(v0, 16);
    v0 = slti(v0, 99);
    if (v0 == 0) {
        // 0x003f2ecc
        charge(ctx, 3);
        lw(v0, s0, 0);
        v0 = v0 | 0x10;
        sw(v0, s0, 0);
    }
    // 0x003f2ed8
    charge(ctx, 6);
    lw(s1, s0, 16);
    jal(ctx, 0x3F2EDCu, gen::fn_sub_16DD50_0016dd50);
    at = sltu(v0, s1);
    if (at != 0) {
        // 0x003f2ef0
        charge(ctx, 3);
        lw(v0, s0, 0);
        v0 = v0 | 0x10;
        sw(v0, s0, 0);
    }
    // 0x003f2efc
    charge(ctx, 10);
    jal(ctx, 0x3F2EFCu, gen::fn_sub_3E6DC0_003e6dc0);
    sh(v0, sp, 0x58);
    sh(zero, sp, 0x5A);
    lhu(a1, s0, 4);
    lw(a0, sp, 0x58);
    jal(ctx, 0x3F2F14u, gen::fn_sub_17D250_0017d250);
    if (v0 == 0) {
        // 0x003f2f24
        charge(ctx, 3);
        lw(v0, s0, 0);
        v0 = v0 | 0x20;
        sw(v0, s0, 0);
    }
    // 0x003f2f30
    charge(ctx, 4);
    lw(v1, s0, 0);
    v0 = v1 & 0x20;
    if (v0 != 0) {
        // 0x003f2f40
        charge(ctx, 2);
        v0 = v1 | 0x10;
        sw(v0, s0, 0);
    }
    // 0x003f2f48 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = 0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x003F3280 sub_3F3280 -- 332 bytes; leaf frame (no stack)
// [fclBuyRowCompare] The lineup sort comparator (nm list sort): by category byte, then by the key the category's
// nibble selects (4: 9,999,999 - price, 2: +26, 1: +24, 0: +20), then by item id.
void sub_3F3280(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x003f3280
    enter(ctx, 13);  // entry check point + this block's cycles
    lw(v0, a0, 0);
    lw(v0, v0, 20);
    lw(v1, v0, 28);
    lw(v0, a1, 0);
    lw(v0, v0, 20);
    lw(a3, v0, 28);
    lw(a2, a3, 8);
    lw(a1, v1, 8);
    a0 = a1 & 0xFF;
    v0 = a2 & 0xFF;
    v0 = subu(a0, v0);
    if (v0 == 0) {
        // 0x003f32b4
        charge(ctx, 5);
        v0 = a2 & 0xF00;
        a0 = sra(v0, 8);
        v0 = 4;
        if (a0 == v0) {
            // 0x003f3314
            charge(ctx, 6);
            lw(a0, a3, 16);
            v0 = 0x980000;
            v0 = v0 | 0x967F;  // 9,999,999 = shop::kYenMax (a constant, not an address)
            a2 = subu(v0, a0);
        } else {
            // 0x003f32c8
            charge(ctx, 3);
            v0 = 2;
            if (a0 == v0) {
                // 0x003f3308
                charge(ctx, 3);
                lh(a2, a3, 26);
            } else {
                // 0x003f32d4
                charge(ctx, 3);
                v0 = 1;
                if (a0 == v0) {
                    // 0x003f32fc
                    charge(ctx, 3);
                    lh(a2, a3, 24);
                } else {
                    // 0x003f32e0
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x003f32f0
                        charge(ctx, 3);
                        lh(a2, a3, 20);
                    } else {
                        // 0x003f32e8
                        charge(ctx, 2);
                        // 0x003f332c
                        charge(ctx, 1);
                        a2 = 0;
                    }
                }
            }
        }
        // 0x003f3330
        charge(ctx, 5);
        v0 = a1 & 0xF00;
        a0 = sra(v0, 8);
        v0 = 4;
        if (a0 == v0) {
            // 0x003f3390
            charge(ctx, 6);
            lw(a0, v1, 16);
            v0 = 0x980000;
            v0 = v0 | 0x967F;  // 9,999,999 = shop::kYenMax (a constant, not an address)
            v0 = subu(v0, a0);
        } else {
            // 0x003f3344
            charge(ctx, 3);
            v0 = 2;
            if (a0 == v0) {
                // 0x003f3384
                charge(ctx, 3);
                lh(v0, v1, 26);
            } else {
                // 0x003f3350
                charge(ctx, 3);
                v0 = 1;
                if (a0 == v0) {
                    // 0x003f3378
                    charge(ctx, 3);
                    lh(v0, v1, 24);
                } else {
                    // 0x003f335c
                    charge(ctx, 2);
                    if (a0 == 0) {
                        // 0x003f336c
                        charge(ctx, 3);
                        lh(v0, v1, 20);
                    } else {
                        // 0x003f3364
                        charge(ctx, 2);
                        // 0x003f33a8
                        charge(ctx, 1);
                        v0 = 0;
                    }
                }
            }
        }
        // 0x003f33ac
        charge(ctx, 3);
        v0 = subu(a2, v0);
        if (v0 == 0) {
            // 0x003f33b8
            charge(ctx, 3);
            lh(a0, a3, 4);
            lh(v0, v1, 4);
            v0 = subu(a0, v0);
        }
    }
    // 0x003f33c4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003F3970 sub_3F3970 -- 40 bytes; frame 0x10: ra sp+0x0
// [fclBuyListSort] sub_3F39A0($a0, 0, $a1).
void sub_3F3970(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f3970
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a1;
    a1 = 0;
    jal(ctx, 0x3F3980u, gen::fn_sub_3F39A0_003f39a0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003F3DC0 sub_3F3DC0 -- 152 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBuyRowsMarkNew] For every row: if its item is in list $a1 (nmListFindByWord4) that entry is removed, else the
// row gets flag 0x80 (new).
void sub_3F3DC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f3dc0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a1;
    lw(s1, a0, 4);
    for (;;) {
        // 0x003f3e34
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003f3de4
        charge(ctx, 10);
        lw(v0, s1, 20);
        lw(s0, v0, 28);
        lh(a2, s0, 4);
        a0 = s2;
        a1 = addiu(s2, 4);
        jal(ctx, 0x3F3DF8u, gen::fn_nmListFindByWord4_003c4bf0);
        a2 = v0;
        if (v0 == 0) {
            // 0x003f3e24
            charge(ctx, 3);
            lw(v1, s0, 0);
            v1 = v1 | 0x80;
            sw(v1, s0, 0);
        } else {
            // 0x003f3e0c
            charge(ctx, 6);
            a0 = s2;
            a1 = addiu(s2, 4);
            jal(ctx, 0x3F3E14u, gen::fn_sub_3C49E0_003c49e0);
        }
        // 0x003f3e30
        charge(ctx, 1);
        lw(s1, s1, 16);
    }
    // 0x003f3e3c
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003F3F00 sub_3F3F00 -- 188 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBuyListInput] One frame of the lineup's input (sub_3FA1E0: 1 when decided), with the cursor sounds: moved /
// scrolled -> sound 0, paged / moved up -> sound 5 (sub_10A4E0). Returns the decision.
void sub_3F3F00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f3f00
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    jal(ctx, 0x3F3F14u, gen::fn_sub_3FA1E0_003fa1e0);
    s0 = v0;
    a0 = s1;
    jal(ctx, 0x3F3F24u, gen::fn_nmCmdListMovedDownRow_003c6ce0);
    if (v0 == 0) {
        // 0x003f3f34
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x3F3F38u, gen::fn_nmCmdListScrolledRow_003c6d10);
        if (v0 != 0) {
            goto L_003f3f48;
        }
        goto L_003f3f60;
    }
L_003f3f48:
    charge(ctx, 6);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x3F3F58u, gen::fn_sub_10A4E0_0010a4e0);
L_003f3f60:
    charge(ctx, 5);
    a0 = s1;
    jal(ctx, 0x3F3F64u, gen::fn_nmCmdListPagedDown_003c6ca0);
    if (v0 == 0) {
        // 0x003f3f74
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x3F3F78u, gen::fn_nmCmdListMovedUp_003c6cc0);
        if (v0 != 0) {
            goto L_003f3f88;
        }
        // 0x003f3fa0 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        v0 = s0;
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_003f3f88:
    charge(ctx, 6);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 5;
    jal(ctx, 0x3F3F98u, gen::fn_sub_10A4E0_0010a4e0);
    // 0x003f3fa0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003F7730 sub_3F7730 -- 348 bytes; frame 0x90: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclRowDrawCount] Draws a row's three frame sprites (table 0x6AEFD0 by the list mode) and its owned count ("%d" at
// +139, +12).
void sub_3F7730(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x003f7730
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    a1 = 0x6B0000;
    a1 = addiu(a1, -4144);  // &0x6AEFD0
    a0 = addiu(sp, 0x60);
    v1 = 15;
    for (;;) {
        // 0x003f7768
        charge(ctx, 7);
        lh(v0, a1, 0);
        a1 = addiu(a1, 2);
        v1 = addiu(v1, -1);
        sh(v0, a0, 0);
        a0 = addiu(a0, 2);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x003f7784
    charge(ctx, 66);
    lw(v0, a3, 36);
    lw(s1, v0, 68);
    lw(v0, t0, 20);
    lw(s0, v0, 28);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    lh(v1, s1, 4);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, sp);
    lh(a3, v0, 96);
    a0 = s4;
    a1 = s3;
    t0 = 0;
    jal(ctx, 0x3F77C0u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    lh(v1, s1, 4);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, sp);
    lh(a3, v0, 98);
    a0 = s4;
    a1 = s3;
    t0 = 0;
    jal(ctx, 0x3F77F4u, gen::fn_sub_40E3C0_0040e3c0);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    lh(v1, s1, 4);
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, sp);
    lh(a3, v0, 100);
    a0 = s4;
    a1 = s3;
    t0 = 0;
    jal(ctx, 0x3F7828u, gen::fn_sub_40E3C0_0040e3c0);
    lh(a2, s0, 14);
    a0 = addiu(sp, 0x80);
    a1 = addiu(gp, -21404);  // "%2d"
    jal(ctx, 0x3F783Cu, gen::fn_sprintf_00523ac8);
    a0 = addiu(s4, 139);
    a1 = addiu(s3, 12);
    mtc1(zero, f12);
    a2 = s2 & 0xFF;
    a3 = 1;
    t0 = addiu(sp, 0x80);
    t1 = a3;
    jal(ctx, 0x3F7860u, gen::fn_sub_40EB50_0040eb50);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x003F98F0 sub_3F98F0 -- 220 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclItemSellable] 0 when item $a0 is in one of the 16 unsellable ranges of 0x6ACCA0 ({first, last}; last 0 = a
// single id; K_Assert 3602 on {0, n}), else 1.
void sub_3F98F0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f98f0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = 0x6B0000;
    s2 = addiu(s2, -13152);  // &0x6ACCA0
    s1 = 0;
    s0 = a0 & 0xFFFF;
    for (;;) {
        // 0x003f99a0
        charge(ctx, 3);
        v0 = sltiu(s1, 16);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003f991c
        charge(ctx, 3);
        lhu(v0, s2, 0);
        if (v0 == 0) {
            // 0x003f9928
            charge(ctx, 3);
            lhu(v0, s2, 2);
            if (v0 != 0) {
                // 0x003f9934
                charge(ctx, 5);
                a0 = 0x6B0000;
                a0 = addiu(a0, -4632);  // "fclShopMisc.c"
                a1 = 3602;
                jal(ctx, 0x3F9940u, gen::fn_sub_19D3F0_0019d3f0);
            }
        }
        // 0x003f9948
        charge(ctx, 3);
        lhu(v1, s2, 2);
        if (v1 == 0) {
            // 0x003f9980
            charge(ctx, 3);
            lhu(v0, s2, 0);
            if (s0 == v0) {
                goto L_003f998c_9;
            }
        L_003f9998:
            charge(ctx, 2);
            s2 = addiu(s2, 4);
            s1 = addiu(s1, 1);
            continue;
        }
        // 0x003f9954
        charge(ctx, 4);
        lhu(v0, s2, 0);
        v0 = slt(s0, v0);
        if (v0 != 0) {
            goto L_003f9998;
        }
        // 0x003f9964
        charge(ctx, 4);
        v0 = v1 & 0xFFFF;
        at = slt(v0, s0);
        if (at != 0) {
            goto L_003f9998;
        }
        goto L_003f9974_7;
    }
    // 0x003f99ac
    charge(ctx, 1);
    v0 = 1;
    // 0x003f99b0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_003f9974_7:
    charge(ctx, 3);
    v0 = 0;
    // 0x003f99b0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_003f998c_9:
    charge(ctx, 3);
    v0 = 0;
    // 0x003f99b0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003F99D0 sub_3F99D0 -- 336 bytes; frame 0x70: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclSellRowsAdd] Adds a row (32 bytes) to list $a0 for every inventory slot (300) of the kinds in mask $a1 that
// sub_3F1DC0 fills and sub_3F98F0 allows; the protagonist's equipped piece gets flags 0x10 | 0x40; the sell price is
// the price / 4, at least 1. Returns 0.
void sub_3F99D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f99d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = 0;
    for (;;) {
        // 0x003f9af0
        charge(ctx, 3);
        v0 = slti(s1, 300);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x003f99fc
        charge(ctx, 7);
        a0 = 1;
        a1 = s1;
        jal(ctx, 0x3F9A04u, gen::fn_sub_16F720_0016f720);
        v0 = s2 & v0;
        if (v0 != 0) {
            // 0x003f9a18
            charge(ctx, 7);
            a0 = 1;
            a1 = addiu(sp, 0x50);
            a2 = s1;
            jal(ctx, 0x3F9A24u, gen::fn_sub_3F1DC0_003f1dc0);
            if (v0 != 0) {
                // 0x003f9a34
                charge(ctx, 5);
                a0 = s1 & 0xFFFF;
                jal(ctx, 0x3F9A38u, gen::fn_sub_3F98F0_003f98f0);
                if (v0 != 0) {
                    // 0x003f9a48
                    charge(ctx, 18);
                    lhu(v0, s3, 16);
                    a1 = addiu(v0, 1);
                    a0 = s3;
                    a2 = 32;
                    a3 = 0;
                    jal(ctx, 0x3F9A5Cu, gen::fn_nmCmdListAddRow_003c5a40);
                    lw(v0, v0, 20);
                    lw(s0, v0, 28);
                    a0 = addiu(s0, 4);
                    a1 = addiu(sp, 0x50);
                    a2 = 28;
                    jal(ctx, 0x3F9A78u, gen::fn_memcpy_00521250);
                    lw(v1, sp, 0x54);
                    v0 = v1 & 0x1000;
                    if (v0 != 0) {
                        // 0x003f9a90
                        charge(ctx, 11);
                        v0 = v1 & 0xF00;
                        v0 = sra(v0, 8);
                        a1 = dsll32(v0, 16);
                        a1 = dsra32(a1, 16);
                        a0 = 1;
                        jal(ctx, 0x3F9AA4u, gen::fn_datGetEquipmentIdx_0016cb80);
                        v0 = dsll32(v0, 16);
                        v0 = dsra32(v0, 16);
                        if (s1 == v0) {
                            // 0x003f9abc
                            charge(ctx, 5);
                            lw(v0, s0, 0);
                            v0 = v0 | 0x10;
                            sw(v0, s0, 0);
                            v0 = v0 | 0x40;
                            sw(v0, s0, 0);
                        }
                    }
                    // 0x003f9ad0
                    charge(ctx, 5);
                    lw(v0, s0, 16);
                    v0 = sra(v0, 2);
                    sw(v0, s0, 16);
                    if (i64(v0) <= 0) {
                        // 0x003f9ae4
                        charge(ctx, 2);
                        v0 = 1;
                        sw(v0, s0, 16);
                    }
                }
            }
        }
        // 0x003f9aec
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x003f9afc
    charge(ctx, 9);
    v0 = 0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x003F9B20 sub_3F9B20 -- 388 bytes; frame 0x80: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclSellRowRefresh] Recounts a sell row (flag 0x4000: consumable count, else whether the slot still holds it) and
// removes the row when none is left. Returns 0.
void sub_3F9B20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003f9b20
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    lw(v0, a1, 20);
    lw(s4, v0, 28);
    lw(v0, s4, 8);
    v0 = v0 & 0x4000;
    if (v0 == 0) {
        // 0x003f9c30
        charge(ctx, 6);
        lh(a1, s4, 6);
        a0 = 1;
        jal(ctx, 0x3F9C38u, gen::fn_sub_16F630_0016f630);
        if (v0 == 0) {
            // 0x003f9c58
            charge(ctx, 1);
            sh(zero, s4, 14);
        } else {
            // 0x003f9c48
            charge(ctx, 4);
            v0 = 1;
            sh(v0, s4, 14);
        }
    } else {
        // 0x003f9b60
        charge(ctx, 12);
        lh(s3, s4, 4);
        v0 = si(-1);
        sw(v0, sp, 0x7C);
        s0 = 0;
        a0 = s3;
        a1 = addiu(sp, 0x7C);
        jal(ctx, 0x3F9B78u, gen::fn_sub_170ED0_00170ed0);
        lw(v1, sp, 0x7C);
        v0 = 4;
        if (v1 == v0) {
            // 0x003f9c10
            charge(ctx, 5);
            a0 = 1;
            a1 = s3;
            jal(ctx, 0x3F9C18u, gen::fn_sub_170760_00170760);
            s0 = v0 & 0xFFFF;
        } else {
            // 0x003f9b90
            charge(ctx, 3);
            v0 = 3;
            if (v1 != v0) {
                // 0x003f9b9c
                charge(ctx, 3);
                v0 = 2;
                if (v1 == v0) {
                    goto L_003f9bc4;
                }
                // 0x003f9ba8
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    goto L_003f9bc4;
                }
                // 0x003f9bb4
                charge(ctx, 2);
                if (v1 == 0) {
                    goto L_003f9bc4;
                }
                // 0x003f9bbc
                charge(ctx, 2);
                goto L_003f9c24;
            }
        L_003f9bc4:
            charge(ctx, 5);
            s5 = 0;
            s3 = dsll32(s3, 16);
            s3 = dsra32(s3, 16);
            for (;;) {
                // 0x003f9bfc
                charge(ctx, 3);
                v0 = slti(s5, 300);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x003f9bd8
                charge(ctx, 7);
                a0 = 1;
                a1 = s5;
                jal(ctx, 0x3F9BE0u, gen::fn_sub_16F630_0016f630);
                v0 = v0 & 0xFFFF;
                if (s3 == v0) {
                    // 0x003f9bf4
                    charge(ctx, 1);
                    s0 = addiu(s0, 1);
                }
                // 0x003f9bf8
                charge(ctx, 1);
                s5 = addiu(s5, 1);
            }
            // 0x003f9c08
            charge(ctx, 2);
        }
    L_003f9c24:
        charge(ctx, 3);
        sh(s0, s4, 14);
    }
    // 0x003f9c5c
    charge(ctx, 3);
    lh(v0, s4, 14);
    if (v0 == 0) {
        // 0x003f9c68
        charge(ctx, 4);
        a0 = s2;
        a1 = s1;
        jal(ctx, 0x3F9C70u, gen::fn_nmCmdListRemoveRow_003c5fa0);
    }
    // 0x003f9c78 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    v0 = 0;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x003F9CB0 sub_3F9CB0 -- 376 bytes; leaf frame (no stack)
// [fclSellRowCompare] The sell list comparator: equipped rows (flag 0x40) first, then as sub_3F3280.
void sub_3F9CB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x003f9cb0
    enter(ctx, 17);  // entry check point + this block's cycles
    lw(v0, a0, 0);
    lw(v0, v0, 20);
    lw(a0, v0, 28);
    lw(v0, a1, 0);
    lw(v0, v0, 20);
    lw(v1, v0, 28);
    lw(v0, v1, 0);
    v0 = v0 & 0x40;
    a1 = v0;
    a1 = sltiu(a1, 1);
    lw(v0, a0, 0);
    v0 = v0 & 0x40;
    // xor v0: a 64-bit move to itself (no effect)
    v0 = sltiu(v0, 1);
    v0 = subu(a1, v0);
    if (v0 == 0) {
        // 0x003f9cf4
        charge(ctx, 7);
        lw(a3, v1, 8);
        lw(a2, a0, 8);
        a1 = a2 & 0xFF;
        v0 = a3 & 0xFF;
        v0 = subu(a1, v0);
        if (v0 == 0) {
            // 0x003f9d10
            charge(ctx, 5);
            v0 = a3 & 0xF00;
            a1 = sra(v0, 8);
            v0 = 4;
            if (a1 == v0) {
                // 0x003f9d70
                charge(ctx, 6);
                lw(a1, v1, 16);
                v0 = 0x980000;
                v0 = v0 | 0x967F;  // 9,999,999 = shop::kYenMax (a constant, not an address)
                a3 = subu(v0, a1);
            } else {
                // 0x003f9d24
                charge(ctx, 3);
                v0 = 2;
                if (a1 == v0) {
                    // 0x003f9d64
                    charge(ctx, 3);
                    lh(a3, v1, 26);
                } else {
                    // 0x003f9d30
                    charge(ctx, 3);
                    v0 = 1;
                    if (a1 == v0) {
                        // 0x003f9d58
                        charge(ctx, 3);
                        lh(a3, v1, 24);
                    } else {
                        // 0x003f9d3c
                        charge(ctx, 2);
                        if (a1 == 0) {
                            // 0x003f9d4c
                            charge(ctx, 3);
                            lh(a3, v1, 20);
                        } else {
                            // 0x003f9d44
                            charge(ctx, 2);
                            // 0x003f9d88
                            charge(ctx, 1);
                            a3 = 0;
                        }
                    }
                }
            }
            // 0x003f9d8c
            charge(ctx, 5);
            v0 = a2 & 0xF00;
            a1 = sra(v0, 8);
            v0 = 4;
            if (a1 == v0) {
                // 0x003f9dec
                charge(ctx, 6);
                lw(a1, a0, 16);
                v0 = 0x980000;
                v0 = v0 | 0x967F;  // 9,999,999 = shop::kYenMax (a constant, not an address)
                v0 = subu(v0, a1);
            } else {
                // 0x003f9da0
                charge(ctx, 3);
                v0 = 2;
                if (a1 == v0) {
                    // 0x003f9de0
                    charge(ctx, 3);
                    lh(v0, a0, 26);
                } else {
                    // 0x003f9dac
                    charge(ctx, 3);
                    v0 = 1;
                    if (a1 == v0) {
                        // 0x003f9dd4
                        charge(ctx, 3);
                        lh(v0, a0, 24);
                    } else {
                        // 0x003f9db8
                        charge(ctx, 2);
                        if (a1 == 0) {
                            // 0x003f9dc8
                            charge(ctx, 3);
                            lh(v0, a0, 20);
                        } else {
                            // 0x003f9dc0
                            charge(ctx, 2);
                            // 0x003f9e04
                            charge(ctx, 1);
                            v0 = 0;
                        }
                    }
                }
            }
            // 0x003f9e08
            charge(ctx, 3);
            v0 = subu(a3, v0);
            if (v0 == 0) {
                // 0x003f9e14
                charge(ctx, 3);
                lh(v1, v1, 4);
                lh(v0, a0, 4);
                v0 = subu(v1, v0);
            }
        }
    }
    // 0x003f9e20 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x003FA0D0 sub_3FA0D0 -- 188 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclSellListInput] As sub_3F3F00 for the sell list.
void sub_3FA0D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fa0d0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    jal(ctx, 0x3FA0E4u, gen::fn_sub_3FA1E0_003fa1e0);
    s0 = v0;
    a0 = s1;
    jal(ctx, 0x3FA0F4u, gen::fn_nmCmdListMovedDownRow_003c6ce0);
    if (v0 == 0) {
        // 0x003fa104
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x3FA108u, gen::fn_nmCmdListScrolledRow_003c6d10);
        if (v0 != 0) {
            goto L_003fa118;
        }
        goto L_003fa130;
    }
L_003fa118:
    charge(ctx, 6);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x3FA128u, gen::fn_sub_10A4E0_0010a4e0);
L_003fa130:
    charge(ctx, 5);
    a0 = s1;
    jal(ctx, 0x3FA134u, gen::fn_nmCmdListPagedDown_003c6ca0);
    if (v0 == 0) {
        // 0x003fa144
        charge(ctx, 5);
        a0 = s1;
        jal(ctx, 0x3FA148u, gen::fn_nmCmdListMovedUp_003c6cc0);
        if (v0 != 0) {
            goto L_003fa158;
        }
        // 0x003fa170 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        v0 = s0;
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_003fa158:
    charge(ctx, 6);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 5;
    jal(ctx, 0x3FA168u, gen::fn_sub_10A4E0_0010a4e0);
    // 0x003fa170 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003FA190 sub_3FA190 -- 32 bytes; leaf frame (no stack)
// [fclListViewSet1] Sets bit 0 of the list view word (list +36 -> +68 -> +0). Returns 0.
void sub_3FA190(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003fa190
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v0, a0, 36);
    lw(v1, v0, 68);
    lw(v0, v1, 0);
    v0 = v0 | 0x1;
    sw(v0, v1, 0);
    v0 = 0;
}

// 0x003FA1B0 sub_3FA1B0 -- 36 bytes; leaf frame (no stack)
// [fclListViewClear1] Clears it. Returns 0.
void sub_3FA1B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x003fa1b0
    enter(ctx, 9);  // entry check point + this block's cycles
    lw(v0, a0, 36);
    lw(a0, v0, 68);
    lw(v1, a0, 0);
    v0 = si(-2);
    v0 = v1 & v0;
    sw(v0, a0, 0);
    v0 = 0;
}

// 0x003FA1E0 sub_3FA1E0 -- 40 bytes; frame 0x10: ra sp+0x0
// [fclListDecided] nmCmdListUpdate == 3.
void sub_3FA1E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fa1e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x3FA1E8u, gen::fn_nmCmdListUpdate_003c6270);
    v0 = v0 ^ 0x3;
    v0 = sltiu(v0, 1);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x003FB290 sub_3FB290 -- 96 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclDescSetRow] Copies the 28-byte row $a1 to the description panel $a0 +12 (K_Assert 4120 on null).
void sub_3FB290(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fb290
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    if (s1 == 0) {
        // 0x003fb2b0
        charge(ctx, 5);
        a0 = 0x6B0000;
        a0 = addiu(a0, -4632);  // "fclShopMisc.c"
        a1 = 4120;
        jal(ctx, 0x3FB2BCu, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x003fb2c4
    charge(ctx, 11);
    a0 = addiu(s1, 12);
    a1 = s0;
    a2 = 28;
    jal(ctx, 0x3FB2D0u, gen::fn_memcpy_00521250);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x003FBF20 sub_3FBF20 -- 316 bytes; leaf frame (no stack)
// [fclDescFade] The description panel's fade: states 1 / 2 fade in over 10 frames (alpha +148 = 255 * n / 10), 3 / 4
// fade out, 5 shown. Returns 0. A leaf.
void sub_3FBF20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x003fbf20
    enter(ctx, 4);  // entry check point + this block's cycles
    lh(a1, a0, 0);
    v0 = 5;
    if (a1 != v0) {
        // 0x003fbf30
        charge(ctx, 3);
        v1 = 4;
        if (a1 != v1) {
            // 0x003fbf3c
            charge(ctx, 3);
            v0 = 3;
            if (a1 == v0) {
                // 0x003fbfd4
                charge(ctx, 2);
                sh(v1, a0, 0);
                sw(zero, a0, 8);
                goto L_003fbfdc;
            }
            // 0x003fbf48
            charge(ctx, 3);
            v1 = 2;
            if (a1 != v1) {
                // 0x003fbf54
                charge(ctx, 3);
                v0 = 1;
                if (a1 == v0) {
                    // 0x003fbf68
                    charge(ctx, 2);
                    sh(v1, a0, 0);
                    sw(zero, a0, 8);
                    goto L_003fbf70;
                }
                // 0x003fbf60
                charge(ctx, 2);
                // 0x003fc050 (the shared epilogue, written out on this path)
                charge(ctx, 3);
                v0 = 0;
                return;
            }
        L_003fbf70:
            charge(ctx, 20);
            lw(v0, a0, 8);
            v1 = addiu(v0, 1);
            sw(v1, a0, 8);
            v0 = sll(v1, 8);
            v0 = subu(v0, v1);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
            v0 = 0x41200000;
            mtc1(v0, f0);
            div_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sh(v0, a0, 148);
            lw(v0, a0, 8);
            v0 = slti(v0, 10);
            if (v0 == 0) {
                // 0x003fbfc0
                charge(ctx, 5);
                v0 = 5;
                sh(v0, a0, 0);
                sw(zero, a0, 8);
            }
            // 0x003fc050 (the shared epilogue, written out on this path)
            charge(ctx, 3);
            v0 = 0;
            return;
        }
    L_003fbfdc:
        charge(ctx, 24);
        lw(v0, a0, 8);
        v1 = addiu(v0, 1);
        sw(v1, a0, 8);
        v0 = sll(v1, 8);
        v0 = subu(v1, v0);
        mtc1(v0, f0);
        cvt_s_w(f1, f0);
        v0 = 0x41200000;
        mtc1(v0, f0);
        div_s(f1, f1, f0);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        add_s(f0, f0, f1);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        sh(v0, a0, 148);
        lw(v0, a0, 8);
        v0 = slti(v0, 10);
        if (v0 == 0) {
            // 0x003fc03c
            charge(ctx, 5);
            lw(v1, a0, 4);
            v0 = si(-2);
            v0 = v1 & v0;
            sw(v0, a0, 4);
            sw(zero, a0, 8);
        }
    }
    // 0x003fc050 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = 0;
}

// 0x003FC980 sub_3FC980 -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclBuyTypeInfo] Weapons: sub_3FC060; accessories: sub_3FC540; others nothing.
void sub_3FC980(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003fc980
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x3FC990u, gen::fn_sub_3E6DC0_003e6dc0);
    if (v0 != 0) {
        // 0x003fc9b4
        charge(ctx, 5);
        jal(ctx, 0x3FC9B4u, gen::fn_sub_3E6DC0_003e6dc0);
        v1 = 1;
        if (v0 != v1) {
            // 0x003fc9dc
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x003fc9c8
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x3FC9CCu, gen::fn_sub_3FC540_003fc540);
        }
    } else {
        // 0x003fc9a0
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x3FC9A4u, gen::fn_sub_3FC060_003fc060);
    }
    // 0x003fc9e0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x003FFA20 sub_3FFA20 -- 392 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclRootRowFade] Draws a fading menu row (sub_3FF630; alpha 255 -> 0 over +12 frames, or a cosine pulse when +14 is
// set); counts +10 up; returns 1 when done.
void sub_3FFA20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x003ffa20
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    lh(v0, a2, 14);
    if (v0 != 0) {
        // 0x003ffaac
        charge(ctx, 32);
        lh(v0, s0, 10);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        lwc1(f2, gp, -32496);  // 0x7CAE00
        mul_s(f1, f2, f0);
        lh(v0, s0, 12);
        mtc1(v0, f0);
        cvt_s_w(f0, f0);
        div_s(f0, f1, f0);
        add_s(f12, f2, f0);
        jal(ctx, 0x3FFAE4u, gen::fn_cosf_0052e6d8);
        neg_s(f3, f0);
        v0 = 0x3E800000;
        mtc1(v0, f2);
        v0 = 0x3F800000;
        mtc1(v0, f1);
        mtc1(zero, f0);
        adda_s(f0, f1);
        madd_s(f12, f2, f3);
        lh(v0, s0, 10);
        v1 = sll(v0, 7);
        lh(v0, s0, 12);
        div(v1, v0);
        mflo(v1);
        v0 = 128;
        a3 = subu(v0, v1);
    } else {
        // 0x003ffa4c
        charge(ctx, 24);
        lh(a0, s0, 12);
        lh(v1, s0, 10);
        v0 = 0x3F000000;
        mtc1(v0, f1);
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        mul_s(f1, f1, f0);
        mtc1(a0, f0);
        cvt_s_w(f0, f0);
        div_s(f1, f1, f0);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        add_s(f12, f0, f1);
        v0 = sll(v1, 8);
        v0 = subu(v0, v1);
        div(v0, a0);
        mflo(v1);
        v0 = 255;
        a3 = subu(v0, v1);
    }
    // 0x003ffb2c
    charge(ctx, 20);
    lh(t0, s0, 16);
    lh(v0, s0, 8);
    v0 = addiu(v0, -1);
    t1 = dsll32(v0, 16);
    t1 = dsra32(t1, 16);
    a0 = s2;
    a1 = s1;
    a2 = 0;
    t2 = 1;
    jal(ctx, 0x3FFB50u, gen::fn_sub_3FF630_003ff630);
    lh(v0, s0, 10);
    v0 = addiu(v0, 1);
    sh(v0, s0, 10);
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    lh(v0, s0, 12);
    v0 = slt(v1, v0);
    if (v0 != 0) {
        // 0x003ffb88
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x003ffb7c
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x003ffb8c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x003FFE00 sub_3FFE00 -- 96 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclRootRowsRefresh] sub_3FFBB0 for every row of the menu list $a0 ->+0 (nothing when null).
void sub_3FFE00(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x003ffe00
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (a0 != 0) {
        // 0x003ffe18
        charge(ctx, 4);
        lw(s1, a0, 0);
        lw(s0, s1, 4);
        for (;;) {
            // 0x003ffe3c
            charge(ctx, 3);
            if (s0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x003ffe28
            charge(ctx, 5);
            a0 = s1;
            a1 = s0;
            jal(ctx, 0x3FFE30u, gen::fn_sub_3FFBB0_003ffbb0);
            lw(s0, s0, 16);
        }
    }
    // 0x003ffe48 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00400690 sub_400690 -- 40 bytes; frame 0x10: ra sp+0x0
// [fclRootDraw] nmCmdListDraw(menu ->+0). Returns 0.
void sub_400690(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00400690
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, 0);
    jal(ctx, 0x40069Cu, gen::fn_nmCmdListDraw_003c6380);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00400740 sub_400740 -- 432 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclRootFrameDraw] The ROOT menu frame (sprites 21..24 at 0 / 112 / 224 / 349) and its fading rows (sub_3FFA20),
// each removed from the fade list when done (sub_3C49E0).
void sub_400740(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00400740
    enter(ctx, 85);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    lw(v0, a3, 36);
    lw(s0, v0, 68);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a2 = s1 & 0xFF;
    a3 = 21;
    t0 = 0;
    jal(ctx, 0x400780u, gen::fn_sub_40E3C0_0040e3c0);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a2 = s1 & 0xFF;
    a0 = s3;
    a1 = s2;
    a3 = 22;
    t0 = 0;
    jal(ctx, 0x4007A4u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s3, 349);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a2 = s1 & 0xFF;
    a1 = s2;
    a3 = 21;
    t0 = 0;
    jal(ctx, 0x4007C8u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s3, 349);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a2 = s1 & 0xFF;
    a1 = s2;
    a3 = 22;
    t0 = 0;
    jal(ctx, 0x4007ECu, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s3, 112);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a2 = s1 & 0xFF;
    a1 = s2;
    a3 = 23;
    t0 = 0;
    jal(ctx, 0x400810u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s3, 112);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a2 = s1 & 0xFF;
    a1 = s2;
    a3 = 24;
    t0 = 0;
    jal(ctx, 0x400834u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s3, 224);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a2 = s1 & 0xFF;
    a1 = s2;
    a3 = 23;
    t0 = 0;
    jal(ctx, 0x400858u, gen::fn_sub_40E3C0_0040e3c0);
    a0 = addiu(s3, 224);
    v0 = 0x3F800000;
    mtc1(v0, f12);
    a2 = s1 & 0xFF;
    a1 = s2;
    a3 = 24;
    t0 = 0;
    jal(ctx, 0x40087Cu, gen::fn_sub_40E3C0_0040e3c0);
    lw(s1, s0, 4);
    lw(s0, s1, 4);
    for (;;) {
        // 0x004008c8
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00400894
        charge(ctx, 9);
        lw(a2, s0, 20);
        lh(a0, a2, 4);
        lh(a1, a2, 6);
        jal(ctx, 0x4008A0u, gen::fn_sub_3FFA20_003ffa20);
        a2 = s0;
        lw(s0, s0, 16);
        if (v0 != 0) {
            // 0x004008b8
            charge(ctx, 4);
            a0 = s1;
            a1 = addiu(s1, 4);
            jal(ctx, 0x4008C0u, gen::fn_sub_3C49E0_003c49e0);
        }
    }
    // 0x004008d0
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00400A90 sub_400A90 -- 244 bytes; frame 0x10: ra sp+0x0
// [fclRootRowSlide] A ROOT row sliding in: the cursor row is offset by 600 * frame / frames at full alpha; greyed
// rows (flag 1) use the dim factor of 0x7CAD80; drawn by sub_3FF630.
void sub_400A90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x00400a90
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = a2;
    lw(a2, a3, 36);
    lw(t4, a2, 68);
    lw(v0, t0, 20);
    lw(t3, v0, 28);
    v0 = 0;
    t5 = 0;
    lh(t2, a2, 4);
    lh(t1, a2, 8);
    lw(a2, a3, 12);
    if (t0 == a2) {
        // 0x00400ac8
        charge(ctx, 1);
        v0 = 1;
    }
    // 0x00400acc
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x00400ad4
        charge(ctx, 15);
        v1 = sll(t2, 4);
        a2 = subu(v1, t2);
        v1 = sll(a2, 2);
        v1 = addu(a2, v1);
        v1 = sll(v1, 3);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
        mtc1(t1, f0);
        cvt_s_w(f0, f0);
        div_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(t5, f0);
        v1 = 255;
    }
    // 0x00400b10
    charge(ctx, 4);
    lw(a2, t3, 0);
    a2 = a2 & 0x1;
    if (a2 != 0) {
        // 0x00400b20
        charge(ctx, 7);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
        lwc1(f0, gp, -32624);  // 0x7CAD80
        mul_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
    }
    // 0x00400b3c
    charge(ctx, 18);
    a0 = addu(a0, t5);
    a2 = 0x3F800000;
    mtc1(a2, f12);
    lh(t3, t4, 8);
    lw(a2, t0, 0);
    a2 = addiu(a2, -1);
    t1 = dsll32(a2, 16);
    t1 = dsra32(t1, 16);
    t2 = v0 | 0x2;
    a2 = 0;
    a3 = v1;
    t0 = t3;
    jal(ctx, 0x400B6Cu, gen::fn_sub_3FF630_003ff630);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00400B90 sub_400B90 -- 456 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclRootRowDraw] The ROOT rows' draw callback by the list status (nmCmdListStatus28): 1 / 12 the plain row (dimmed
// when flag 1, highlighted when the cursor row), 20 the slide (sub_400A90).
void sub_400B90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x00400b90
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
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
    a0 = s1;
    jal(ctx, 0x400BC4u, gen::fn_nmCmdListStatus28_003c6e10);
    a1 = 1;
    if (v0 == a1) {
        // 0x00400cac
        charge(ctx, 8);
        lw(v0, s1, 36);
        lw(a0, v0, 68);
        lw(v0, s0, 20);
        lw(v1, v0, 28);
        a2 = 0;
        lw(v0, s1, 12);
        if (s0 == v0) {
            // 0x00400ccc
            charge(ctx, 1);
            a2 = a1;
        }
        // 0x00400cd0
        charge(ctx, 4);
        lw(v0, v1, 0);
        v0 = v0 & 0x1;
        if (v0 != 0) {
            // 0x00400ce0
            charge(ctx, 7);
            mtc1(s2, f0);
            cvt_s_w(f1, f0);
            lwc1(f0, gp, -32624);  // 0x7CAD80
            mul_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(s2, f0);
        }
        // 0x00400cfc
        charge(ctx, 14);
        v0 = 0x3F800000;
        mtc1(v0, f12);
        lh(t0, a0, 8);
        lw(v0, s0, 0);
        v0 = addiu(v0, -1);
        t1 = dsll32(v0, 16);
        t1 = dsra32(t1, 16);
        t2 = a2 | 0x2;
        a0 = s4;
        a1 = s3;
        a2 = 0;
        a3 = s2;
        jal(ctx, 0x400D2Cu, gen::fn_sub_3FF630_003ff630);
    } else {
        // 0x00400bd8
        charge(ctx, 3);
        v1 = 20;
        if (v0 == v1) {
            // 0x00400c88
            charge(ctx, 9);
            a0 = s4;
            a1 = s3;
            a2 = s2;
            a3 = s1;
            t0 = s0;
            jal(ctx, 0x400C9Cu, gen::fn_sub_400A90_00400a90);
        } else {
            // 0x00400be4
            charge(ctx, 3);
            v1 = 12;
            if (v0 == v1) {
                // 0x00400bf8
                charge(ctx, 8);
                lw(v0, s1, 36);
                lw(a0, v0, 68);
                lw(v0, s0, 20);
                lw(v1, v0, 28);
                a2 = 0;
                lw(v0, s1, 12);
                if (s0 == v0) {
                    // 0x00400c18
                    charge(ctx, 1);
                    a2 = a1;
                }
                // 0x00400c1c
                charge(ctx, 4);
                lw(v0, v1, 0);
                v0 = v0 & 0x1;
                if (v0 != 0) {
                    // 0x00400c2c
                    charge(ctx, 7);
                    mtc1(s2, f0);
                    cvt_s_w(f1, f0);
                    lwc1(f0, gp, -32624);  // 0x7CAD80
                    mul_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(s2, f0);
                }
                // 0x00400c48
                charge(ctx, 16);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                lh(t0, a0, 8);
                lw(v0, s0, 0);
                v0 = addiu(v0, -1);
                t1 = dsll32(v0, 16);
                t1 = dsra32(t1, 16);
                t2 = a2 | 0x2;
                a0 = s4;
                a1 = s3;
                a2 = 0;
                a3 = s2;
                jal(ctx, 0x400C78u, gen::fn_sub_3FF630_003ff630);
            } else {
                // 0x00400bf0
                charge(ctx, 2);
            }
        }
    }
    // 0x00400d34 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00400D60 fclShopMisc_CreateShopDrawBGLowTasks -- 200 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// Creates the background manager: an nm list with 32-byte payloads (sub_3C44D0), the payload = the manager (+8 the
// list); the tasks "fclShopDrawBGLow" (6323) -> +12, its child "fclShopDrawBGHighLow" (6325) and that one's child
// "fclShopDrawBGHighTop" (6327), all with the manager as work; mode -1. Returns the manager.
void fclShopMisc_CreateShopDrawBGLowTasks(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00400d60
    enter(ctx, 50);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 32;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x400D7Cu, gen::fn_sub_3C44D0_003c44d0);
    lw(s0, v0, 36);
    sw(v0, s0, shop::kBgList);
    a0 = 0;
    a1 = 0x6B0000;
    a1 = addiu(a1, -3264);  // "fclShopDrawBGLow"
    a2 = 6323;
    a3 = 0x400000;
    a3 = addiu(a3, 4624);  // &fclShopMisc_UpdateShopDrawBGLowTask
    t0 = 0;
    t1 = s0;
    jal(ctx, 0x400DACu, gen::fn_kwlnTaskCreate_00194b20);
    sw(v0, s0, shop::kBgTask);
    a0 = v0;
    a1 = 0x6B0000;
    a1 = addiu(a1, -3232);  // "fclShopDrawBGHighLow"
    a2 = 6325;
    a3 = 0x400000;
    a3 = addiu(a3, 4800);  // &fclShopMisc_UpdateShopDrawBGHighLowTask
    t0 = 0;
    t1 = s0;
    jal(ctx, 0x400DD8u, gen::fn_kwlnTaskCreate_00194b20);
    a0 = v0;
    a1 = 0x6B0000;
    a1 = addiu(a1, -3200);  // "fclShopDrawBGHighTop"
    a2 = 6327;
    a3 = 0x400000;
    a3 = addiu(a3, 4976);  // &fclShopMisc_UpdateShopDrawBGHighTopTask
    t0 = 0;
    t1 = s0;
    jal(ctx, 0x400E00u, gen::fn_kwlnTaskCreate_00194b20);
    v0 = si(-1);
    sw(v0, s0, shop::kBgMode);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00401170 sub_401170 -- 160 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgDrawLayer3] While the manager is active (flag 1): calls the draw handler (+4) of every active element whose
// scene entry is on layer 3 (+20) through jalr with the manager.
void sub_401170(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00401170
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v1, a0, 0);
    a0 = v1 & 0x1;
    if (a0 != 0) {
        // 0x00401194
        charge(ctx, 3);
        lw(v1, s1, shop::kBgList);
        if (a0 != 0) {
            // 0x004011a0
            charge(ctx, 3);
            lw(s0, v1, 4);
            for (;;) {
                // 0x004011f0
                charge(ctx, 2);
                if (s0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x004011ac
                charge(ctx, 6);
                lw(a1, s0, 20);
                lw(a2, a1, 8);
                lw(a0, a2, 20);
                v1 = 3;
                if (a0 == v1) {
                    // 0x004011c4
                    charge(ctx, 4);
                    lw(v1, a1, 0);
                    v1 = v1 & 0x1;
                    if (v1 != 0) {
                        // 0x004011d4
                        charge(ctx, 3);
                        lw(v1, a2, 4);
                        if (v1 != 0) {
                            // 0x004011e0
                            charge(ctx, 3);
                            a0 = s1;
                            jalr(ctx, 0x4011E4u, v1.u());
                        }
                    }
                }
                // 0x004011ec
                charge(ctx, 1);
                lw(s0, s0, 16);
            }
        }
    }
    // 0x004011f8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00401210 fclShopMisc_UpdateShopDrawBGLowTask -- 172 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Layer 0 of the background (as sub_401170 with layer 0). Returns 0.
void fclShopMisc_UpdateShopDrawBGLowTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00401210
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 60);
    lw(v0, s1, shop::kBgFlags);
    v1 = v0 & 0x1;
    if (v1 != 0) {
        // 0x00401240
        charge(ctx, 3);
        lw(v0, s1, shop::kBgList);
        if (v1 != 0) {
            // 0x0040124c
            charge(ctx, 3);
            lw(s0, v0, 4);
            for (;;) {
                // 0x00401298
                charge(ctx, 2);
                if (s0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00401258
                charge(ctx, 5);
                lw(a1, s0, 20);
                lw(v1, a1, 8);
                lw(v0, v1, 20);
                if (v0 == 0) {
                    // 0x0040126c
                    charge(ctx, 4);
                    lw(v0, a1, 0);
                    v0 = v0 & 0x1;
                    if (v0 != 0) {
                        // 0x0040127c
                        charge(ctx, 3);
                        lw(v0, v1, 4);
                        if (v0 != 0) {
                            // 0x00401288
                            charge(ctx, 3);
                            a0 = s1;
                            jalr(ctx, 0x40128Cu, v0.u());
                        }
                    }
                }
                // 0x00401294
                charge(ctx, 1);
                lw(s0, s0, 16);
            }
        }
        // 0x004012a0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00401234
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x004012a4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004012C0 fclShopMisc_UpdateShopDrawBGHighLowTask -- 176 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Layer 2 of the background. Returns 0.
void fclShopMisc_UpdateShopDrawBGHighLowTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004012c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 60);
    lw(v0, s1, shop::kBgFlags);
    v1 = v0 & 0x1;
    if (v1 != 0) {
        // 0x004012f0
        charge(ctx, 3);
        lw(v0, s1, shop::kBgList);
        if (v1 != 0) {
            // 0x004012fc
            charge(ctx, 3);
            lw(s0, v0, 4);
            for (;;) {
                // 0x0040134c
                charge(ctx, 2);
                if (s0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00401308
                charge(ctx, 6);
                lw(a1, s0, 20);
                lw(a0, a1, 8);
                lw(v1, a0, 20);
                v0 = 2;
                if (v1 == v0) {
                    // 0x00401320
                    charge(ctx, 4);
                    lw(v0, a1, 0);
                    v0 = v0 & 0x1;
                    if (v0 != 0) {
                        // 0x00401330
                        charge(ctx, 3);
                        lw(v0, a0, 4);
                        if (v0 != 0) {
                            // 0x0040133c
                            charge(ctx, 3);
                            a0 = s1;
                            jalr(ctx, 0x401340u, v0.u());
                        }
                    }
                }
                // 0x00401348
                charge(ctx, 1);
                lw(s0, s0, 16);
            }
        }
        // 0x00401354
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004012e4
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00401358 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00401370 fclShopMisc_UpdateShopDrawBGHighTopTask -- 176 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Layer 4 of the background. Returns 0.
void fclShopMisc_UpdateShopDrawBGHighTopTask(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00401370
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 60);
    lw(v0, s1, shop::kBgFlags);
    v1 = v0 & 0x1;
    if (v1 != 0) {
        // 0x004013a0
        charge(ctx, 3);
        lw(v0, s1, shop::kBgList);
        if (v1 != 0) {
            // 0x004013ac
            charge(ctx, 3);
            lw(s0, v0, 4);
            for (;;) {
                // 0x004013fc
                charge(ctx, 2);
                if (s0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x004013b8
                charge(ctx, 6);
                lw(a1, s0, 20);
                lw(a0, a1, 8);
                lw(v1, a0, 20);
                v0 = 4;
                if (v1 == v0) {
                    // 0x004013d0
                    charge(ctx, 4);
                    lw(v0, a1, 0);
                    v0 = v0 & 0x1;
                    if (v0 != 0) {
                        // 0x004013e0
                        charge(ctx, 3);
                        lw(v0, a0, 4);
                        if (v0 != 0) {
                            // 0x004013ec
                            charge(ctx, 3);
                            a0 = s1;
                            jalr(ctx, 0x4013F0u, v0.u());
                        }
                    }
                }
                // 0x004013f8
                charge(ctx, 1);
                lw(s0, s0, 16);
            }
        }
        // 0x00401404
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00401394
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00401408 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00401420 sub_401420 -- 192 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgSetScene] Manager $a0 gets scene $a1 (+16): one list node per scene entry (28 bytes at +8, +12 of them) with
// an entry-sized data area (entry +8, plus 16); node data +8 = the entry, +12 = its area when it has one.
void sub_401420(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00401420
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a1;
    sw(s3, a0, 16);
    lw(s2, a0, 8);
    s1 = 0;
    for (;;) {
        // 0x004014b0
        charge(ctx, 4);
        lw(v1, s3, 12);
        v1 = slt(s1, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00401450
        charge(ctx, 21);
        v0 = sll(s1, 3);
        v0 = subu(v0, s1);
        s0 = sll(v0, 2);
        lhu(v0, s2, 16);
        a1 = addiu(v0, 1);
        lw(v0, s3, 8);
        v0 = addu(v0, s0);
        lw(v0, v0, 8);
        a2 = addiu(v0, 16);
        a0 = s2;
        jal(ctx, 0x401478u, gen::fn_nmListAppendNew_003c4910);
        lw(a0, v0, 20);
        lw(v1, s3, 8);
        v1 = addu(v1, s0);
        sw(v1, a0, 8);
        lw(v1, s3, 8);
        v1 = addu(v1, s0);
        lw(v1, v1, 8);
        if (v1 != 0) {
            // 0x004014a4
            charge(ctx, 2);
            v1 = addiu(a0, 16);
            sw(v1, a0, 12);
        }
        // 0x004014ac
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x004014c0
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004014E0 sub_4014E0 -- 192 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgLoadPoll] Calls the load handler (+16) of every element not yet loaded (flag 4); returns 0 at the first that
// is not ready; when all are: flags = (flags & ~3) | 2, returns 1.
void sub_4014E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004014e0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    lw(v0, a0, 8);
    lw(s1, v0, 4);
    for (;;) {
        // 0x00401560
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x00401508
        charge(ctx, 5);
        lw(s0, s1, 20);
        lw(v0, s0, 8);
        lw(v1, v0, 16);
        if (v1 != 0) {
            // 0x0040151c
            charge(ctx, 4);
            lw(v0, s0, 0);
            v0 = v0 & 0x4;
            if (v0 != 0) {
                goto L_0040155c;
            }
            // 0x0040152c
            charge(ctx, 6);
            a0 = s2;
            a1 = s0;
            jalr(ctx, 0x401534u, v1.u());
            if (v0 == 0) {
                goto L_00401544_4;
            }
            // 0x00401550
            charge(ctx, 3);
            lw(v0, s0, 0);
            v0 = v0 | 0x4;
            sw(v0, s0, 0);
            goto L_0040155c;
        }
    L_0040155c:
        charge(ctx, 1);
        lw(s1, s1, 16);
    }
    // 0x00401568
    charge(ctx, 7);
    lw(v1, s2, shop::kBgFlags);
    v0 = si(-2);
    v0 = v1 & v0;
    sw(v0, s2, shop::kBgFlags);
    v0 = v0 | 0x2;
    sw(v0, s2, shop::kBgFlags);
    v0 = 1;
    // 0x00401584 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_00401544_4:
    charge(ctx, 3);
    v0 = 0;
    // 0x00401584 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004015A0 sub_4015A0 -- 60 bytes; leaf frame (no stack)
// [fclBgSetMode] When the mode changes: flag 1 (plus 4 if a change was already pending) and +24 = mode.
void sub_4015A0(EEContext& ctx) {
    using namespace hg;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x004015a0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a0, shop::kBgMode);
    if (v1 != a1) {
        // 0x004015ac
        charge(ctx, 4);
        lw(a2, a0, shop::kBgFlags);
        v1 = a2 & 0x1;
        if (v1 != 0) {
            // 0x004015bc
            charge(ctx, 2);
            v1 = a2 | 0x4;
            sw(v1, a0, shop::kBgFlags);
        }
        // 0x004015c4
        charge(ctx, 4);
        lw(v1, a0, shop::kBgFlags);
        v1 = v1 | 0x1;
        sw(v1, a0, shop::kBgFlags);
        sw(a1, a0, shop::kBgMode);
    }
    // 0x004015d4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004015E0 sub_4015E0 -- 20 bytes; leaf frame (no stack)
// [fclBgFlag2] (flags & 2) != 0.
void sub_4015E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004015e0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, shop::kBgFlags);
    v0 = v0 & 0x2;
    v0 = sltu(0, v0);
}

// 0x00401600 sub_401600 -- 200 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgAnimEvent] Applies an animation event to handle $a1: 2 / 35 start (sub_111C50), 36 stop and start
// (sub_111D50, sub_111C50), 1 / 3 start and sub_111EE0. Returns the event.
void sub_401600(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x00401600
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    v0 = 35;
    if (s0 != v0) {
        // 0x00401624
        charge(ctx, 3);
        v0 = 2;
        if (s0 == v0) {
            goto L_004016a0;
        }
        // 0x00401630
        charge(ctx, 3);
        v0 = 36;
        if (s0 == v0) {
            // 0x0040167c
            charge(ctx, 9);
            mtc1(zero, f12);
            a0 = s1;
            jal(ctx, 0x401684u, gen::fn_sub_111D50_00111d50);
            a0 = s1;
            jal(ctx, 0x401690u, gen::fn_sub_111C50_00111c50);
        } else {
            // 0x0040163c
            charge(ctx, 3);
            v0 = 3;
            if (s0 != v0) {
                // 0x00401648
                charge(ctx, 3);
                v0 = 1;
                if (s0 == v0) {
                    goto L_0040165c;
                }
                // 0x00401654
                charge(ctx, 2);
                // 0x004016ac (the shared epilogue, written out on this path)
                charge(ctx, 7);
                v0 = s0;
                ld(ra, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x30);
                return;
            }
        L_0040165c:
            charge(ctx, 8);
            a0 = s1;
            jal(ctx, 0x401660u, gen::fn_sub_111C50_00111c50);
            a0 = s1;
            jal(ctx, 0x40166Cu, gen::fn_sub_111EE0_00111ee0);
        }
        // 0x004016ac (the shared epilogue, written out on this path)
        charge(ctx, 7);
        v0 = s0;
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_004016a0:
    charge(ctx, 3);
    a0 = s1;
    jal(ctx, 0x4016A4u, gen::fn_sub_111C50_00111c50);
    // 0x004016ac (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0040D410 sub_40D410 -- 128 bytes; frame 0x10: ra sp+0x0
// [COMM: facility start] The script command that opens a facility: scrGetIntPara(0) -> 0x7CDA00; 0..6 and 8 the shop
// of that type (sub_3E0700), 7 the Velvet Room (fusion's sub_3D02F0), others -1. Returns 1.
void sub_40D410(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040d410
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x40D41Cu, gen::fn_scrGetIntPara_0035ed20);
    sw(v0, gp, -21232);  // 0x7CDA00
    at = sltiu(v0, 9);
    if (at == 0) {
        // 0x0040d474
        charge(ctx, 2);
        v0 = si(-1);
        sw(v0, gp, -21232);  // 0x7CDA00
    } else {
        // 0x0040d434
        charge(ctx, 7);
        a0 = 0x7C0000;
        a0 = addiu(a0, -16720);  // &0x7BBEB0
        v1 = sll(v0, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x40D450u:  // table[0, 1, 2, 3, 4, 5, 6, 8]
            // 0x0040d450
            charge(ctx, 5);
            a0 = v0;
            jal(ctx, 0x40D454u, gen::fn_sub_3E0700_003e0700);
            break;
        case 0x40D464u:  // table[7]
            // 0x0040d464
            charge(ctx, 4);
            jal(ctx, 0x40D464u, gen::fn_sub_3D02F0_003d02f0);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x0040d47c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0040D490 sub_40D490 -- 168 bytes; frame 0x10: ra sp+0x0
// [COMM: facility wait] After 4 frames (scrGetCmdTimer): 1 when the facility of 0x7CDA00 has closed (shops
// sub_3E0920, the Velvet Room sub_3D04B0), else 0 (the command repeats).
void sub_40D490(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040d490
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x40D498u, gen::fn_scrGetCmdTimer_0035f130);
    at = slti(v0, 4);
    if (at == 0) {
        // 0x0040d4b8
        charge(ctx, 4);
        lw(v0, gp, -21232);  // 0x7CDA00
        at = sltiu(v0, 9);
        if (at == 0) {
            // 0x0040d51c
            charge(ctx, 2);
            v0 = si(-1);
            sw(v0, gp, -21232);  // 0x7CDA00
        L_0040d524:
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0040d4c8
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -16672);  // &0x7BBEE0
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x40D4E4u:  // table[0, 1, 2, 3, 4, 5, 6, 8]
                // 0x0040d4e4
                charge(ctx, 4);
                jal(ctx, 0x40D4E4u, gen::fn_sub_3E0920_003e0920);
                if (v0 != 0) {
                    goto L_0040d524;
                }
                // 0x0040d4f4
                charge(ctx, 3);
                v0 = 1;
                break;
            case 0x40D500u:  // table[7]
                // 0x0040d500
                charge(ctx, 4);
                jal(ctx, 0x40D500u, gen::fn_sub_3D04B0_003d04b0);
                if (v0 != 0) {
                    goto L_0040d524;
                }
                // 0x0040d510
                charge(ctx, 3);
                v0 = 1;
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
    } else {
        // 0x0040d4ac
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x0040d528 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0040D5E0 sub_40D5E0 -- 36 bytes; frame 0x10: ra sp+0x0
// [fclDrawNumberA] sub_40D610 with $t1 = 0 (its sixth argument).
void sub_40D5E0(EEContext& ctx) {
    using namespace hg;
    Gpr t1{ctx, 9}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040d5e0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    t1 = 0;
    jal(ctx, 0x40D5ECu, gen::fn_sub_40D610_0040d610);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0040D610 sub_40D610 -- 36 bytes; frame 0x10: ra sp+0x0
// [fclDrawNumberB] sub_40D640 (still recompiled) with $t2 = 0 (its seventh argument).
void sub_40D610(EEContext& ctx) {
    using namespace hg;
    Gpr t2{ctx, 10}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040d610
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    t2 = 0;
    jal(ctx, 0x40D61Cu, gen::fn_sub_40D640_0040d640);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0040E300 sub_40E300 -- 88 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclSpriteBankLoad] Frees the current bank (sub_40E580), creates one for descriptor $a0 (sub_40E450) into 0x7CE6A0
// and keeps $a1 in 0x7CE69C.
void sub_40E300(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040e300
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(a0, gp, -18000);  // 0x7CE6A0: the facility sprite bank
    if (a0 != 0) {
        // 0x0040e324
        charge(ctx, 2);
        jal(ctx, 0x40E324u, gen::fn_sub_40E580_0040e580);
    }
    // 0x0040e32c
    charge(ctx, 11);
    a0 = s1;
    jal(ctx, 0x40E330u, gen::fn_sub_40E450_0040e450);
    sw(v0, gp, -18000);  // 0x7CE6A0: the facility sprite bank
    sw(s0, gp, -18004);  // 0x7CE69C
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0040E390 sub_40E390 -- 36 bytes; frame 0x10: ra sp+0x0
// [fclSpriteBankReady] sub_40E4F0 on the current bank.
void sub_40E390(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040e390
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, -18000);  // 0x7CE6A0: the facility sprite bank
    jal(ctx, 0x40E39Cu, gen::fn_sub_40E4F0_0040e4f0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0040E3C0 sub_40E3C0 -- 36 bytes; frame 0x10: ra sp+0x0
// [fclSpriteDraw] Draws sprite $a3 (frame + $t0) of the current bank at ($a0, $a1), alpha 255 - $a2 (sub_40E610).
void sub_40E3C0(EEContext& ctx) {
    using namespace hg;
    Gpr t1{ctx, 9}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040e3c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(t1, gp, -18000);  // 0x7CE6A0: the facility sprite bank
    jal(ctx, 0x40E3CCu, gen::fn_sub_40E610_0040e610);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0040E3F0 sub_40E3F0 -- 48 bytes; frame 0x10: ra sp+0x0
// [fclSpriteDrawEx] The scaled / rotated draw (sub_40E710) with the current bank.
void sub_40E3F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040e3f0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = t1;
    t3 = t2;
    lw(t1, gp, -18000);  // 0x7CE6A0: the facility sprite bank
    t2 = v0;
    jal(ctx, 0x40E408u, gen::fn_sub_40E710_0040e710);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0040E450 sub_40E450 -- 148 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclSpriteBankCreate] RwMalloc(20 + 4 * file count) (the RW slot 0x960178, flags 0x40000), zeroed: +4 descriptor,
// +8 handles (the block's +20), +12 / +16 from the descriptor, +0 loaded = 0. Returns the bank.
void sub_40E450(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040e450
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, 4);
    v0 = sll(v0, 2);
    s1 = addiu(v0, 20);
    a0 = s1;
    a1 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    jalr(ctx, 0x40E484u, v0.u());
    s2 = v0;
    a0 = s2;
    a1 = 0;
    a2 = s1;
    jal(ctx, 0x40E49Cu, gen::fn_memset_00521408);
    sw(s0, s2, shop::kBankDesc);
    v0 = addiu(s2, 20);
    sw(v0, s2, shop::kBankHandles);
    lw(v0, s0, 8);
    sw(v0, s2, shop::kBankSprites);
    lw(v0, s0, 12);
    sw(v0, s2, shop::kBankExtra);
    sw(zero, s2, shop::kBankLoaded);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0040E4F0 sub_40E4F0 -- 140 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclSpriteBankLoadAll] Turns every file of the descriptor into a sprite handle (H_Cdvd_CacheFindFile,
// sprCreateHandleFromData), counting +0; returns 1.
void sub_40E4F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040e4f0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    for (;;) {
        // 0x0040e504
        charge(ctx, 23);
        lw(v0, s0, shop::kBankLoaded);
        s1 = sll(v0, 2);
        lw(v0, s0, shop::kBankDesc);
        lw(v0, v0, 0);
        v0 = addu(v0, s1);
        lw(a0, v0, 0);
        a1 = addiu(sp, 0x3C);
        jal(ctx, 0x40E520u, gen::fn_H_Cdvd_CacheFindFile_001021c0);
        a0 = v0;
        jal(ctx, 0x40E52Cu, gen::fn_sprCreateHandleFromData_00112420);
        lw(v1, s0, shop::kBankHandles);
        v1 = addu(v1, s1);
        sw(v0, v1, 0);
        lw(v0, s0, shop::kBankLoaded);
        v1 = addiu(v0, 1);
        sw(v1, s0, shop::kBankLoaded);
        lw(v0, s0, shop::kBankDesc);
        lw(v0, v0, 4);
        v0 = slt(v1, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0040e560
    charge(ctx, 7);
    v0 = 1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0040E580 sub_40E580 -- 132 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclSpriteBankFree] Frees each handle (sub_1124B0) and the block (the RW slot 0x96017C) when $a0 is not null.
void sub_40E580(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040e580
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    if (s1 != 0) {
        // 0x0040e59c
        charge(ctx, 3);
        s0 = 0;
        for (;;) {
            // 0x0040e5c4
            charge(ctx, 5);
            lw(v0, s1, shop::kBankDesc);
            lw(v0, v0, 4);
            v0 = slt(s0, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0040e5a8
            charge(ctx, 7);
            v1 = sll(s0, 2);
            lw(v0, s1, shop::kBankHandles);
            v0 = addu(v0, v1);
            lw(a0, v0, 0);
            jal(ctx, 0x40E5B8u, gen::fn_sub_1124B0_001124b0);
            s0 = addiu(s0, 1);
        }
        // 0x0040e5d8
        charge(ctx, 5);
        a0 = s1;
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x40E5E4u, v0.u());
    }
    // 0x0040e5ec (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0040E610 sub_40E610 -- 244 bytes; frame 0x70: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [fclBankSpriteDraw] $t1 the bank: sprite $a3 {s8 file, s16 frame, s16 dx, s16 dy}: sprCreateHandle(0, file, frame +
// $t0), position ($a0 + dx, $a1 + dy) as floats, depth $f12, alpha byte 255 - $a2, sub_1127D0 / sub_115980 (submit).
void sub_40E610(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f20{ctx, 20};
    // 0x0040e610
    enter(ctx, 61);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s4 = a0;
    s3 = a1;
    mov_s(f20, f12);
    s2 = a2;
    v1 = sll(a3, 3);
    lw(v0, t1, 12);
    s0 = addu(v0, v1);
    lb(v0, s0, 0);
    v1 = sll(v0, 2);
    lw(v0, t1, 8);
    v1 = addu(v0, v1);
    lh(v0, s0, 2);
    a2 = addu(v0, t0);
    a0 = 0;
    lw(a1, v1, 0);
    jal(ctx, 0x40E66Cu, gen::fn_sprCreateHandle_001158b0);
    s1 = v0;
    lh(v1, s0, 4);
    v1 = addu(s4, v1);
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, v0, 16);
    lh(v1, s0, 6);
    v1 = addu(s3, v1);
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    swc1(f0, v0, 20);
    swc1(f20, v0, 44);
    a0 = 255;
    v1 = s2 & 0xFF;
    v1 = subu(a0, v1);
    sb(v1, v0, 25);
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x40E6C4u, gen::fn_sub_1127D0_001127d0);
    a0 = s1;
    jal(ctx, 0x40E6D0u, gen::fn_sub_115980_00115980);
    v0 = 0;
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x0040E710 sub_40E710 -- 540 bytes; frame 0x90: ra sp+0x80, s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f23 sp+0xC, f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
// [fclBankSpriteDrawEx] As sub_40E610 with scale ($f13 / $f15: position offsets scaled, the u16 scale words +40 / +42
// = 4096 * scale), rotation $f12 (+32) and pivot $t2 / $t3 (+36 / +38).
void sub_40E710(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22}, f23{ctx, 23};
    // 0x0040e710
    enter(ctx, 76);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x80);
    sq(s6, sp, 0x70);
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
    s5 = a0;
    s4 = a1;
    mov_s(f23, f12);
    s3 = a2;
    s2 = t2;
    s6 = t3;
    mov_s(f22, f13);
    mov_s(f21, f14);
    mov_s(f20, f15);
    v1 = sll(a3, 3);
    lw(v0, t1, 12);
    s0 = addu(v0, v1);
    lb(v0, s0, 0);
    v1 = sll(v0, 2);
    lw(v0, t1, 8);
    v1 = addu(v0, v1);
    lh(v0, s0, 2);
    a2 = addu(v0, t0);
    a0 = 0;
    lw(a1, v1, 0);
    jal(ctx, 0x40E794u, gen::fn_sprCreateHandle_001158b0);
    s1 = v0;
    lh(v1, s0, 4);
    mtc1(v1, f0);
    cvt_s_w(f1, f0);
    mtc1(s5, f0);
    cvt_s_w(f0, f0);
    mtc1(zero, f2);
    adda_s(f2, f0);
    madd_s(f0, f1, f21);
    swc1(f0, v0, 16);
    lh(v1, s0, 6);
    mtc1(v1, f0);
    cvt_s_w(f1, f0);
    mtc1(s4, f0);
    cvt_s_w(f0, f0);
    adda_s(f2, f0);
    madd_s(f0, f1, f20);
    swc1(f0, v0, 20);
    swc1(f23, v0, 44);
    a0 = 255;
    v1 = s3 & 0xFF;
    v1 = subu(a0, v1);
    sb(v1, v0, 25);
    sh(s2, v0, 36);
    sh(s6, v0, 38);
    swc1(f22, v0, 32);
    v0 = 0x45800000;
    mtc1(v0, f0);
    mul_s(f1, f0, f21);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x0040e858
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFFFF;
    } else {
        // 0x0040e840
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFFFF;
    }
    // 0x0040e870
    charge(ctx, 11);
    sh(v1, s1, 40);
    v0 = 0x45800000;
    mtc1(v0, f0);
    mul_s(f1, f0, f20);
    v0 = 0x4F000000;
    mtc1(v0, f0);
    c_le_s(f0, f1);
    if (cond(ctx)) {
        // 0x0040e8b4
        charge(ctx, 6);
        sub_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        v0 = lui(0x8000);
        v1 = v1 | v0;
        v1 = v1 & 0xFFFF;
    } else {
        // 0x0040e89c
        charge(ctx, 6);
        cvt_w_s(f0, f1);
        mfc1(v1, f0);
        v1 = v1 & 0xFFFF;
    }
    // 0x0040e8cc
    charge(ctx, 24);
    sh(v1, s1, 42);
    a0 = s1;
    a1 = 1;
    jal(ctx, 0x40E8D8u, gen::fn_sub_1127D0_001127d0);
    a0 = s1;
    jal(ctx, 0x40E8E4u, gen::fn_sub_115980_00115980);
    v0 = 0;
    ld(ra, sp, 0x80);
    lq(s6, sp, 0x70);
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
    sp = addiu(sp, 0x90);
}

// 0x0040EB50 sub_40EB50 -- 108 bytes; frame 0x30: ra sp+0x0
// [fclDrawNumber] Draws the digit string $t0 at ($a0, $a1), size class $a3 (widths 0x6AF960), alignment $t1:
// sub_40EC20 with the digit drawer sub_40EEF0 (color $a2 | ~0xFF).
void sub_40EB50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a2{ctx, 6}, a3{ctx, 7}, t2{ctx, 10}, t3{ctx, 11}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040eb50
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x0);
    t3 = 0x6B0000;
    t3 = addiu(t3, -1696);  // &0x6AF960
    t2 = addiu(sp, 0x10);
    v1 = 5;
    for (;;) {
        // 0x0040eb68
        charge(ctx, 7);
        lw(v0, t3, 0);
        t3 = addiu(t3, 4);
        v1 = addiu(v1, -1);
        sw(v0, t2, 0);
        t2 = addiu(t2, 4);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0040eb84
    charge(ctx, 14);
    v1 = a2 & 0xFF;
    v0 = si(-256);
    a2 = v1 | v0;
    v0 = sll(a3, 2);
    v0 = addu(v0, sp);
    lw(t2, v0, 16);
    t3 = 0x410000;
    t3 = addiu(t3, -4368);  // &sub_40EEF0
    jal(ctx, 0x40EBA4u, gen::fn_sub_40EC20_0040ec20);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0040EC20 sub_40EC20 -- 36 bytes; frame 0x20: ra sp+0x10
// [fclDrawDigits] sub_40EC50 (the stack arguments passed through).
void sub_40EC20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0040ec20
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sd(zero, sp, 0x0);
    jal(ctx, 0x40EC2Cu, gen::fn_sub_40EC50_0040ec50);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0040EC50 sub_40EC50 -- 660 bytes; frame 0x110: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [fclDrawDigitsImpl] Parses the digit string: spaces skip a cell, flag 8 inserts a separator every three digits
// (K_Asserts fclDrawSprite.c:277 / 278 on non-digits); alignment flag 1 right, 2 centre; calls the digit callback
// (jalr) per cell with the advance. Returns the width.
void sub_40EC50(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    // 0x0040ec50
    enter(ctx, 39);  // entry check point + this block's cycles
    sp = addiu(sp, -0x110);
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
    swc1(f20, sp, 0x0);
    s5 = a0;
    sw(a1, sp, 0xEC);
    mov_s(f20, f12);
    sw(a2, sp, 0xE8);
    sw(a3, sp, 0xE4);
    s7 = t0;
    s6 = t1;
    sw(t2, sp, 0xE0);
    sw(t3, sp, 0xDC);
    s3 = 0;
    s1 = 0;
    a0 = addiu(sp, 0xF0);
    a1 = 0;
    a2 = 32;
    jal(ctx, 0x40ECB8u, gen::fn_memset_00521408);
    a0 = s7;
    jal(ctx, 0x40ECC4u, gen::fn_strlen_00524388);
    s0 = v0;
    lw(v0, sp, 0xE0);
    mult(v0, s0, v0);
    sq(v0, sp, 0xC0);
    s2 = 0;
    s4 = 0;
    v0 = s6 & 0x8;
    sq(v0, sp, 0xB0);
    for (;;) {
        // 0x0040ecec
        charge(ctx, 5);
        a0 = addu(s7, s2);
        lb(v1, a0, 0);
        v0 = 32;
        if (v1 != v0) {
            // 0x0040ed18
            charge(ctx, 3);
            lq(v0, sp, 0xB0);
            if (v0 != 0) {
                // 0x0040ed24
                charge(ctx, 3);
                at = sltiu(s0, 4);
                if (at == 0) {
                    // 0x0040ed30
                    charge(ctx, 2);
                    if (s2 != 0) {
                        // 0x0040ed38
                        charge(ctx, 6);
                        v1 = subu(s0, s2);
                        v0 = 3;
                        divu(v1, v0);
                        mfhi(v0);
                        if (v0 == 0) {
                            // 0x0040ed50
                            charge(ctx, 5);
                            v1 = 10;
                            v0 = addu(s4, sp);
                            sb(v1, v0, 240);
                            s1 = addiu(s1, 1);
                            s4 = addiu(s4, 1);
                        }
                    }
                }
            }
            // 0x0040ed64
            charge(ctx, 9);
            v0 = addu(s4, sp);
            fp = addiu(v0, 0xF0);
            lb(v0, a0, 0);
            v0 = addiu(v0, -48);
            sb(v0, fp, 0x0);
            v0 = dsll32(v0, 24);
            v0 = dsra32(v0, 24);
            if (i64(v0) < 0) {
                // 0x0040ed88
                charge(ctx, 5);
                a0 = 0x6B0000;
                a0 = addiu(a0, -1712);  // "fclDrawSprite.c"
                a1 = 277;
                jal(ctx, 0x40ED94u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x0040ed9c
            charge(ctx, 4);
            lb(v0, fp, 0x0);
            v0 = slti(v0, 10);
            if (v0 == 0) {
                // 0x0040edac
                charge(ctx, 5);
                a0 = 0x6B0000;
                a0 = addiu(a0, -1712);  // "fclDrawSprite.c"
                a1 = 278;
                jal(ctx, 0x40EDB8u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x0040edc0
            charge(ctx, 1);
            s2 = addiu(s2, 1);
        } else {
            // 0x0040ed00
            charge(ctx, 6);
            v1 = si(-1);
            v0 = addu(s4, sp);
            sb(v1, v0, 240);
            s2 = addiu(s2, 1);
        }
        // 0x0040edc4
        charge(ctx, 4);
        s4 = addiu(s4, 1);
        v0 = sltu(s2, s0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0040edd4
    charge(ctx, 8);
    v0 = sll(s1, 1);
    v0 = addu(v0, s1);
    v1 = sll(v0, 1);
    lq(v0, sp, 0xC0);
    s0 = addu(v0, v1);
    v0 = s6 & 0x1;
    if (v0 == 0) {
        // 0x0040ee00
        charge(ctx, 3);
        v0 = s6 & 0x2;
        if (v0 != 0) {
            // 0x0040ee0c
            charge(ctx, 2);
            v0 = srl(s0, 1);
            s5 = subu(s5, v0);
        }
    } else {
        // 0x0040edf4
        charge(ctx, 3);
        s5 = subu(s5, s0);
    }
    // 0x0040ee14
    charge(ctx, 3);
    s2 = 0;
    for (;;) {
        // 0x0040ee9c
        charge(ctx, 3);
        v0 = slt(s2, s4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0040ee20
        charge(ctx, 6);
        v0 = addu(s2, sp);
        s1 = addiu(v0, 240);
        lb(t0, s1, 0);
        v0 = si(-1);
        if (t0 != v0) {
            // 0x0040ee38
            charge(ctx, 11);
            a0 = addu(s5, s3);
            lw(a1, sp, 0xEC);
            mov_s(f12, f20);
            lw(a2, sp, 0xE8);
            lw(a3, sp, 0xE4);
            t1 = s2;
            t2 = s4;
            lw(t3, sp, 0x110);
            lw(v0, sp, 0xDC);
            jalr(ctx, 0x40EE5Cu, v0.u());
        }
        // 0x0040ee64
        charge(ctx, 4);
        lb(v0, s1, 0);
        v1 = 10;
        if (v0 != v1) {
            // 0x0040ee80
            charge(ctx, 3);
            lb(v0, s1, 1);
            if (v0 == v1) {
                // 0x0040ee8c
                charge(ctx, 1);
                s3 = addiu(s3, 1);
            }
            // 0x0040ee90
            charge(ctx, 2);
            lw(v0, sp, 0xE0);
            s3 = addu(s3, v0);
        } else {
            // 0x0040ee74
            charge(ctx, 3);
            s3 = addiu(s3, 5);
        }
        // 0x0040ee98
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x0040eea8
    charge(ctx, 15);
    v0 = s0;
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
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x110);
}

// 0x0040EEF0 sub_40EEF0 -- 308 bytes; frame 0x90: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// [fclDrawDigit] One digit sprite: the font file of size class $a3 (0x6AF9A0, sprFontGetFile), frame $t0 (+11 for
// classes 3 / 4), position, depth, alpha and the RGB bytes of $a2.
void sub_40EEF0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f20{ctx, 20};
    // 0x0040eef0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s4 = a0;
    s3 = a1;
    mov_s(f20, f12);
    s2 = a2;
    s1 = a3;
    s0 = t0;
    a1 = 0x6B0000;
    a1 = addiu(a1, -1632);  // &0x6AF9A0
    a0 = addiu(sp, 0x70);
    v1 = 5;
    for (;;) {
        // 0x0040ef38
        charge(ctx, 7);
        lw(v0, a1, 0);
        a1 = addiu(a1, 4);
        v1 = addiu(v1, -1);
        sw(v0, a0, 0);
        a0 = addiu(a0, 4);
        if (i64(v1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0040ef54
    charge(ctx, 9);
    v0 = sll(s1, 2);
    v0 = addu(v0, sp);
    lw(a0, v0, 112);
    jal(ctx, 0x40EF60u, gen::fn_sprFontGetFile_001120a0);
    v1 = addiu(s1, -3);
    at = sltiu(v1, 2);
    if (at != 0) {
        // 0x0040ef78
        charge(ctx, 1);
        s0 = addiu(s0, 11);
    }
    // 0x0040ef7c
    charge(ctx, 42);
    a0 = 0;
    a1 = v0;
    a2 = s0;
    jal(ctx, 0x40EF88u, gen::fn_sprCreateHandle_001158b0);
    s0 = v0;
    mtc1(s4, f0);
    cvt_s_w(f0, f0);
    swc1(f0, v0, 16);
    mtc1(s3, f0);
    cvt_s_w(f0, f0);
    swc1(f0, v0, 20);
    swc1(f20, v0, 44);
    a0 = 255;
    v1 = s2 & 0xFF;
    v1 = subu(a0, v1);
    sb(v1, v0, 25);
    v1 = srl(s2, 24);
    sb(v1, v0, 48);
    v1 = srl(s2, 16);
    sb(v1, v0, 49);
    v1 = srl(s2, 8);
    sb(v1, v0, 50);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x40EFE8u, gen::fn_sub_1127D0_001127d0);
    a0 = s0;
    jal(ctx, 0x40EFF4u, gen::fn_sub_115980_00115980);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00410D30 sub_410D30 -- 320 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgAnimLoad] A background element's load handler: creates its animation (sub_111DD0 with priority 6324 and the
// entry's file +24) once, and when it is ready sets its loop / visibility switches from the entry's flags (+12: 1
// enables bits 2 / 4 / 8 / 0x10). Returns 1 when ready.
void sub_410D30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00410d30
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(s0, a1, 12);
    lw(v0, s0, 12);
    if (v0 == 0) {
        // 0x00410d54
        charge(ctx, 7);
        lw(v0, s1, 8);
        lw(a0, a0, 12);
        a1 = 6324;
        lw(a2, v0, 24);
        jal(ctx, 0x410D64u, gen::fn_sub_111DD0_00111dd0);
        sw(v0, s0, 12);
    }
    // 0x00410d70
    charge(ctx, 5);
    lw(a0, s0, 12);
    jal(ctx, 0x410D74u, gen::fn_sub_111EC0_00111ec0);
    if (v0 == 0) {
        // 0x00410e54
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00410d84
        charge(ctx, 21);
        lw(a0, s0, 12);
        a1 = 0;
        jal(ctx, 0x410D8Cu, gen::fn_sub_111F00_00111f00);
        lw(a0, s0, 12);
        a1 = 0;
        jal(ctx, 0x410D9Cu, gen::fn_sub_111F10_00111f10);
        lw(a0, s0, 12);
        a1 = 1;
        jal(ctx, 0x410DACu, gen::fn_sub_111F20_00111f20);
        lw(a0, s0, 12);
        a1 = 1;
        jal(ctx, 0x410DBCu, gen::fn_sub_111CA0_00111ca0);
        lw(v0, s1, 8);
        lw(s1, v0, 12);
        v0 = s1 & 0x1;
        if (v0 != 0) {
            // 0x00410dd8
            charge(ctx, 3);
            v0 = s1 & 0x2;
            if (v0 != 0) {
                // 0x00410de4
                charge(ctx, 4);
                lw(a0, s0, 12);
                a1 = 1;
                jal(ctx, 0x410DECu, gen::fn_sub_111F00_00111f00);
            }
            // 0x00410df4
            charge(ctx, 3);
            v0 = s1 & 0x4;
            if (v0 != 0) {
                // 0x00410e00
                charge(ctx, 4);
                lw(a0, s0, 12);
                a1 = 1;
                jal(ctx, 0x410E08u, gen::fn_sub_111F10_00111f10);
            }
            // 0x00410e10
            charge(ctx, 3);
            v0 = s1 & 0x8;
            if (v0 != 0) {
                // 0x00410e1c
                charge(ctx, 4);
                lw(a0, s0, 12);
                a1 = 0;
                jal(ctx, 0x410E24u, gen::fn_sub_111F20_00111f20);
            }
            // 0x00410e2c
            charge(ctx, 3);
            v0 = s1 & 0x10;
            if (v0 != 0) {
                // 0x00410e38
                charge(ctx, 4);
                lw(a0, s0, 12);
                a1 = 0;
                jal(ctx, 0x410E40u, gen::fn_sub_111CA0_00111ca0);
            }
        }
        // 0x00410e48
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x00410e58 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00410E70 sub_410E70 -- 612 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// [fclBgAnimUpdate] A background element's handler: without an event, advances its fade-in (flag 1) or fade-out (flag
// 2, then stops: returns 2) counters (+6 against +8 / +10) and ticks the animation; with event $a2 (+6): sub_401600,
// and 4 starts a 10-frame fade-out, 3 a fade-in. K_Assert fclShopBGManager.c:828.
void sub_410E70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x00410e70
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a1, 12);
    if (a2 == 0) {
        // 0x00410f54
        charge(ctx, 3);
        lw(a0, s0, 12);
        if (a0 == 0) {
            // 0x004110bc
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x00410f60
            charge(ctx, 5);
            jal(ctx, 0x410F60u, gen::fn_kwlnTaskGetState_00195290);
            v1 = 3;
            if (v0 == v1) {
                // 0x00410f74
                charge(ctx, 5);
                a0 = 0x6B0000;
                a0 = addiu(a0, -1056);  // "fclShopBGManager.c"
                a1 = 828;
                jal(ctx, 0x410F80u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x00410f88
            charge(ctx, 4);
            lw(v1, s0, 0);
            v0 = v1 & 0x1;
            if (v0 != 0) {
                // 0x00410f98
                charge(ctx, 23);
                lh(v0, s0, 6);
                v0 = addiu(v0, 1);
                sh(v0, s0, 6);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lh(v0, s0, 8);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                div_s(f12, f1, f0);
                lw(a0, s0, 12);
                jal(ctx, 0x410FD8u, gen::fn_sub_111D50_00111d50);
                lh(v1, s0, 6);
                lh(v0, s0, 8);
                v0 = slt(v1, v0);
                if (v0 == 0) {
                    // 0x00410ff4
                    charge(ctx, 6);
                    lw(v1, s0, 0);
                    v0 = si(-2);
                    v0 = v1 & v0;
                    sw(v0, s0, 0);
                }
                goto L_004110a4;
            }
            // 0x0041100c
            charge(ctx, 3);
            v0 = v1 & 0x2;
            if (v0 == 0) {
            L_004110a4:
                charge(ctx, 6);
                lw(a0, s0, 12);
                jal(ctx, 0x4110A8u, gen::fn_sub_111CB0_00111cb0);
                v0 = 1;
            } else {
                // 0x00411018
                charge(ctx, 25);
                lh(v0, s0, 6);
                v0 = addiu(v0, 1);
                sh(v0, s0, 6);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lh(v0, s0, 10);
                mtc1(v0, f0);
                cvt_s_w(f0, f0);
                div_s(f1, f1, f0);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                sub_s(f12, f0, f1);
                lw(a0, s0, 12);
                jal(ctx, 0x411060u, gen::fn_sub_111D50_00111d50);
                lh(v1, s0, 6);
                lh(v0, s0, 10);
                v0 = slt(v1, v0);
                if (v0 != 0) {
                    goto L_004110a4;
                }
                // 0x0041107c
                charge(ctx, 10);
                lw(v1, s0, 0);
                v0 = si(-3);
                v0 = v1 & v0;
                sw(v0, s0, 0);
                lw(a0, s0, 12);
                jal(ctx, 0x411090u, gen::fn_sub_111C50_00111c50);
                v0 = 2;
            }
        }
    } else {
        // 0x00410e88
        charge(ctx, 7);
        lh(a2, a2, 6);
        lw(a1, s0, 12);
        jal(ctx, 0x410E90u, gen::fn_sub_401600_00401600);
        v1 = 4;
        if (v0 == v1) {
            // 0x00410f1c
            charge(ctx, 11);
            v0 = 0x3F800000;
            mtc1(v0, f12);
            lw(a0, s0, 12);
            jal(ctx, 0x410F28u, gen::fn_sub_111D50_00111d50);
            lw(v0, s0, 0);
            v0 = v0 | 0x2;
            sw(v0, s0, 0);
            v0 = 10;
            sh(v0, s0, 10);
            sh(zero, s0, 6);
        } else {
            // 0x00410ea4
            charge(ctx, 3);
            v1 = 3;
            if (v0 == v1) {
                // 0x00410eec
                charge(ctx, 12);
                mtc1(zero, f12);
                lw(a0, s0, 12);
                jal(ctx, 0x410EF4u, gen::fn_sub_111D50_00111d50);
                lw(v0, s0, 0);
                v0 = v0 | 0x1;
                sw(v0, s0, 0);
                v0 = 10;
                sh(v0, s0, 8);
                sh(zero, s0, 6);
            } else {
                // 0x00410eb0
                charge(ctx, 3);
                v1 = 2;
                if (v0 != v1) {
                    // 0x00410ebc
                    charge(ctx, 3);
                    v1 = 1;
                    if (v0 == v1) {
                        // 0x00410ed0
                        charge(ctx, 7);
                        v0 = 0x3F800000;
                        mtc1(v0, f12);
                        lw(a0, s0, 12);
                        jal(ctx, 0x410EDCu, gen::fn_sub_111D50_00111d50);
                    } else {
                        // 0x00410ec8
                        charge(ctx, 2);
                    }
                }
            }
        }
        // 0x00410f48
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x004110c0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004110F0 sub_4110F0 -- 152 bytes; frame 0x10: ra sp+0x0
// [fclBgEventMoney] Background events 1 / 3 -> MONEY bit 0, 2 / 4 -> bit 1, 5 -> 2, 6 -> 3 (sub_3EEC60). Returns 1.
void sub_4110F0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004110f0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a2 != 0) {
        // 0x00411100
        charge(ctx, 4);
        lh(v0, a2, 6);
        at = sltiu(v0, 7);
        if (at != 0) {
            // 0x00411110
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -16528);  // &0x7BBF70
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x41112Cu:  // table[2, 4]
                // 0x0041112c
                charge(ctx, 5);
                a0 = 1;
                jal(ctx, 0x411130u, gen::fn_sub_3EEC60_003eec60);
                break;
            case 0x411140u:  // table[1, 3]
                // 0x00411140
                charge(ctx, 5);
                a0 = 0;
                jal(ctx, 0x411144u, gen::fn_sub_3EEC60_003eec60);
                break;
            case 0x411154u:  // table[5]
                // 0x00411154
                charge(ctx, 5);
                a0 = 2;
                jal(ctx, 0x411158u, gen::fn_sub_3EEC60_003eec60);
                break;
            case 0x411168u:  // table[6]
                // 0x00411168
                charge(ctx, 3);
                a0 = 3;
                jal(ctx, 0x41116Cu, gen::fn_sub_3EEC60_003eec60);
                break;
            case 0x411174u:  // table[0]
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
    }
    // 0x00411174 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00411190 sub_411190 -- 432 bytes; frame 0x10: ra sp+0x0
// [fclBgEventSubtitle] Events 5..22 -> subtitle line 0, 2, 4, 6, 8, 1, 3, 5, 7, 9, 10..17 (sub_3EF970). Returns 1.
void sub_411190(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00411190
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a2 != 0) {
        // 0x004111a0
        charge(ctx, 4);
        lh(v0, a2, 6);
        at = sltiu(v0, 23);
        if (at != 0) {
            // 0x004111b0
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -16496);  // &0x7BBF90
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x4111CCu:  // table[5]
                // 0x004111cc
                charge(ctx, 5);
                a0 = 0;
                jal(ctx, 0x4111D0u, gen::fn_sub_3EF970_003ef970);
                break;
            case 0x4111E0u:  // table[10]
                // 0x004111e0
                charge(ctx, 5);
                a0 = 1;
                jal(ctx, 0x4111E4u, gen::fn_sub_3EF970_003ef970);
                break;
            case 0x4111F4u:  // table[6]
                // 0x004111f4
                charge(ctx, 5);
                a0 = 2;
                jal(ctx, 0x4111F8u, gen::fn_sub_3EF970_003ef970);
                break;
            case 0x411208u:  // table[11]
                // 0x00411208
                charge(ctx, 5);
                a0 = 3;
                jal(ctx, 0x41120Cu, gen::fn_sub_3EF970_003ef970);
                break;
            case 0x41121Cu:  // table[7]
                // 0x0041121c
                charge(ctx, 5);
                a0 = 4;
                jal(ctx, 0x411220u, gen::fn_sub_3EF970_003ef970);
                break;
            case 0x411230u:  // table[12]
                // 0x00411230
                charge(ctx, 5);
                a0 = 5;
                jal(ctx, 0x411234u, gen::fn_sub_3EF970_003ef970);
                break;
            case 0x411244u:  // table[8]
                // 0x00411244
                charge(ctx, 5);
                a0 = 6;
                jal(ctx, 0x411248u, gen::fn_sub_3EF970_003ef970);
                break;
            case 0x411258u:  // table[13]
                // 0x00411258
                charge(ctx, 5);
                a0 = 7;
                jal(ctx, 0x41125Cu, gen::fn_sub_3EF970_003ef970);
                break;
            case 0x41126Cu:  // table[9]
                // 0x0041126c
                charge(ctx, 5);
                a0 = 8;
                jal(ctx, 0x411270u, gen::fn_sub_3EF970_003ef970);
                break;
            case 0x411280u:  // table[14]
                // 0x00411280
                charge(ctx, 5);
                a0 = 9;
                jal(ctx, 0x411284u, gen::fn_sub_3EF970_003ef970);
                break;
            case 0x411294u:  // table[15]
                // 0x00411294
                charge(ctx, 5);
                a0 = 10;
                jal(ctx, 0x411298u, gen::fn_sub_3EF970_003ef970);
                break;
            case 0x4112A8u:  // table[16]
                // 0x004112a8
                charge(ctx, 5);
                a0 = 11;
                jal(ctx, 0x4112ACu, gen::fn_sub_3EF970_003ef970);
                break;
            case 0x4112BCu:  // table[17]
                // 0x004112bc
                charge(ctx, 5);
                a0 = 12;
                jal(ctx, 0x4112C0u, gen::fn_sub_3EF970_003ef970);
                break;
            case 0x4112D0u:  // table[18]
                // 0x004112d0
                charge(ctx, 5);
                a0 = 13;
                jal(ctx, 0x4112D4u, gen::fn_sub_3EF970_003ef970);
                break;
            case 0x4112E4u:  // table[19]
                // 0x004112e4
                charge(ctx, 5);
                a0 = 14;
                jal(ctx, 0x4112E8u, gen::fn_sub_3EF970_003ef970);
                break;
            case 0x4112F8u:  // table[20]
                // 0x004112f8
                charge(ctx, 5);
                a0 = 15;
                jal(ctx, 0x4112FCu, gen::fn_sub_3EF970_003ef970);
                break;
            case 0x41130Cu:  // table[21]
                // 0x0041130c
                charge(ctx, 5);
                a0 = 16;
                jal(ctx, 0x411310u, gen::fn_sub_3EF970_003ef970);
                break;
            case 0x411320u:  // table[22]
                // 0x00411320
                charge(ctx, 3);
                a0 = 17;
                jal(ctx, 0x411324u, gen::fn_sub_3EF970_003ef970);
                break;
            case 0x41132Cu:  // table[0, 1, 2, 3, 4]
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
    }
    // 0x0041132c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00411340 sub_411340 -- 172 bytes; frame 0x10: ra sp+0x0
// [fclBgEventShowStep] Events 5..9 show the ROOT / BUY / SELL / ARMSCOMBINE / TRADE step (sub_3E9790, sub_3EA560,
// sub_3EACB0, sub_3EB9B0, sub_3EC030 with 0). Returns 1.
void sub_411340(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00411340
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a2 != 0) {
        // 0x00411350
        charge(ctx, 4);
        lh(v0, a2, 6);
        at = sltiu(v0, 10);
        if (at != 0) {
            // 0x00411360
            charge(ctx, 7);
            v1 = 0x7C0000;
            v1 = addiu(v1, -16400);  // &0x7BBFF0
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x41137Cu:  // table[5]
                // 0x0041137c
                charge(ctx, 5);
                a0 = 0;
                jal(ctx, 0x411380u, gen::fn_sub_3E9790_003e9790);
                break;
            case 0x411390u:  // table[6]
                // 0x00411390
                charge(ctx, 5);
                a0 = 0;
                jal(ctx, 0x411394u, gen::fn_sub_3EA560_003ea560);
                break;
            case 0x4113A4u:  // table[7]
                // 0x004113a4
                charge(ctx, 5);
                a0 = 0;
                jal(ctx, 0x4113A8u, gen::fn_sub_3EACB0_003eacb0);
                break;
            case 0x4113B8u:  // table[8]
                // 0x004113b8
                charge(ctx, 5);
                a0 = 0;
                jal(ctx, 0x4113BCu, gen::fn_sub_3EB9B0_003eb9b0);
                break;
            case 0x4113CCu:  // table[9]
                // 0x004113cc
                charge(ctx, 3);
                a0 = 0;
                jal(ctx, 0x4113D0u, gen::fn_sub_3EC030_003ec030);
                break;
            case 0x4113D8u:  // table[0, 1, 2, 3, 4]
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
    }
    // 0x004113d8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 1;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00412580 sub_412580 -- 144 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// [fclBgDraw5] Draws the five sprites 81..85 of a background element at its five 12-byte positions (sub_40E3F0).
// Returns 0.
void sub_412580(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15};
    // 0x00412580
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a1, 12);
    s1 = 0;
    for (;;) {
        // 0x004125e8
        charge(ctx, 3);
        v0 = slti(s1, 5);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x004125a0
        charge(ctx, 18);
        v0 = sll(s1, 1);
        v0 = addu(v0, s1);
        v0 = sll(v0, 2);
        v0 = addu(s0, v0);
        lwc1(f14, v0, 8);
        lh(a0, v0, 0);
        lh(a1, v0, 2);
        mtc1(zero, f12);
        lbu(a2, v0, 4);
        a3 = addiu(s1, 81);
        t0 = 0;
        t1 = 0;
        t2 = 0;
        mov_s(f13, f12);
        mov_s(f15, f14);
        jal(ctx, 0x4125DCu, gen::fn_sub_40E3F0_0040e3f0);
        s1 = addiu(s1, 1);
    }
    // 0x004125f4
    charge(ctx, 7);
    v0 = 0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

}  // namespace p3fes::game
