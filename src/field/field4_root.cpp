// The field loaders, the sequence entries and the field root (slice field4; field4.h documents the records):
// k_fldrc.c -- the field packs (.pac = the pack cache, .fpc = the model pack), the step loader of the field resources
// (sub_1B10F0: model / world streams, clumps and collision, field objects, NPC files, FBN placement, HBN hits, the
// Tartarus layout, ENV), the material colour / property scalers, the ENV applier and the field-filter task; the boot
// data loaders (field.bf, fuka.bf, the dungeon tables, base.RMD, comutbl.bin, npccomu.bf); k_sequence.c's sequence
// entries 2 / 3 / 5; k_field.c's field root (create / update / destroy, the shutdown and exit requests).
// The bodies are p3fes_handgen's (game/include/p3fes/game/hg_cpu.h): register for register and block for block as the
// recompiled bodies -- frame, spills, $ra links, cycle charges and check points -- with each function's role on top,
// proposed names in brackets, the sField / root-work / scene / $gp offsets named (f4::), the state machines' cases and
// their goto entries annotated.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/field4.h"

namespace p3fes::recomp_gen {
void fn_H_Cdvd_CacheFindFile_001021c0(p3fes::EEContext&);
void fn_H_Cdvd_Destroy_00100ec0(p3fes::EEContext&);
void fn_H_Cdvd_FileExists_001008b0(p3fes::EEContext&);
void fn_H_Cdvd_IsFileLoaded_001016b0(p3fes::EEContext&);
void fn_H_Cdvd_ReadSync_001023a0(p3fes::EEContext&);
void fn_H_Cdvd_Request_00100d80(p3fes::EEContext&);
void fn_K_Data_LoadFldMainScript_001b7b10(p3fes::EEContext&);
void fn_K_Field_DestroyFieldRootTask_001ba3d0(p3fes::EEContext&);
void fn_K_Field_GetMajorId_001bab20(p3fes::EEContext&);
void fn_K_Field_GetMinorId_001bab30(p3fes::EEContext&);
void fn_K_Field_Get_001b9120(p3fes::EEContext&);
void fn_K_Field_Init_001b90f0(p3fes::EEContext&);
void fn_K_Field_SetShouldShutdown_001ba880(p3fes::EEContext&);
void fn_K_Field_UpdateFieldRootTask_001b9480(p3fes::EEContext&);
void fn_K_FldCamera_CreateFieldCameraControlerTask_001d5a90(p3fes::EEContext&);
void fn_K_FldDungeon_CreateTask_001bfbc0(p3fes::EEContext&);
void fn_K_FldDungeon_GetCurrentFloorData_001bffa0(p3fes::EEContext&);
void fn_K_FldDungeon_GetCurrentFloor_001bff20(p3fes::EEContext&);
void fn_K_FldDungeon_GetScrMemory_001bffe0(p3fes::EEContext&);
void fn_K_FldDungeon_GetScrSize_001c0010(p3fes::EEContext&);
void fn_K_FldDungeon_RequestShutdown_001bff00(p3fes::EEContext&);
void fn_K_FldEvent_CreateTasks_001cd5a0(p3fes::EEContext&);
void fn_K_Fldrc_RequestFieldHitTableFile_001c7e70(p3fes::EEContext&);
void fn_K_Scene_IsRandomFloor_001a0250(p3fes::EEContext&);
void fn_K_Seq_CallDungeon_001b7a50(p3fes::EEContext&);
void fn_K_Seq_CallFieldEvent_001b7900(p3fes::EEContext&);
void fn_K_Seq_CallField_001b77b0(p3fes::EEContext&);
void fn_K_Seq_ExitDungeon_001b7a90(p3fes::EEContext&);
void fn_K_Seq_ExitFieldEvent_001b79a0(p3fes::EEContext&);
void fn_K_Seq_ExitField_001b7850(p3fes::EEContext&);
void fn_MT_Scene_Load_003b5760(p3fes::EEContext&);
void fn_Y_Kyoto_CreateKyotoNpcModeReadTask_004579b0(p3fes::EEContext&);
void fn_Y_SMap_CreateSmapDrawTask_00429d40(p3fes::EEContext&);
void fn_acosf_0052e9e8(p3fes::EEContext&);
void fn_adminiChangeSeq_0027c080(p3fes::EEContext&);
void fn_atoi_0051e0f0(p3fes::EEContext&);
void fn_clndGetCurrentDay_0017da40(p3fes::EEContext&);
void fn_clndGetCurrentMonth_0017d920(p3fes::EEContext&);
void fn_clndIsDateInRange_0017e480(p3fes::EEContext&);
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_datGetTime_0016ef30(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_k_Field_CreateFieldRootTask_001ba5f0(p3fes::EEContext&);
void fn_kwlnTaskCreateWithAutoPriority_00194b80(p3fes::EEContext&);
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_kwlnTaskExists_00195460(p3fes::EEContext&);
void fn_kwlnTaskSetFlags_001956d0(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_mtEvtMain_CreateZikkiPlayModeEventViewerTask_0036f3b0(p3fes::EEContext&);
void fn_nullsub_5_00188650(p3fes::EEContext&);
void fn_printf_005225a8(p3fes::EEContext&);
void fn_scrCreateTaskFromHeader_0035bb40(p3fes::EEContext&);
void fn_scrCreateTaskFromScriptMemory_0035bc00(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strcat_00523e68(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_sub_108570_00108570(p3fes::EEContext&);
void fn_sub_1085C0_001085c0(p3fes::EEContext&);
void fn_sub_108670_00108670(p3fes::EEContext&);
void fn_sub_1086A0_001086a0(p3fes::EEContext&);
void fn_sub_108710_00108710(p3fes::EEContext&);
void fn_sub_108FD0_00108fd0(p3fes::EEContext&);
void fn_sub_109170_00109170(p3fes::EEContext&);
void fn_sub_109E30_00109e30(p3fes::EEContext&);
void fn_sub_109F60_00109f60(p3fes::EEContext&);
void fn_sub_10A720_0010a720(p3fes::EEContext&);
void fn_sub_10A770_0010a770(p3fes::EEContext&);
void fn_sub_10C1A0_0010c1a0(p3fes::EEContext&);
void fn_sub_10C3A0_0010c3a0(p3fes::EEContext&);
void fn_sub_16DBA0_0016dba0(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_17F8D0_0017f8d0(p3fes::EEContext&);
void fn_sub_187E20_00187e20(p3fes::EEContext&);
void fn_sub_187EA0_00187ea0(p3fes::EEContext&);
void fn_sub_18BFF0_0018bff0(p3fes::EEContext&);
void fn_sub_18C0A0_0018c0a0(p3fes::EEContext&);
void fn_sub_18C0C0_0018c0c0(p3fes::EEContext&);
void fn_sub_18E820_0018e820(p3fes::EEContext&);
void fn_sub_18EB30_0018eb30(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_1985B0_001985b0(p3fes::EEContext&);
void fn_sub_1985E0_001985e0(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);
void fn_sub_19FD40_0019fd40(p3fes::EEContext&);
void fn_sub_19FD70_0019fd70(p3fes::EEContext&);
void fn_sub_19FDA0_0019fda0(p3fes::EEContext&);
void fn_sub_19FDD0_0019fdd0(p3fes::EEContext&);
void fn_sub_19FE20_0019fe20(p3fes::EEContext&);
void fn_sub_19FE70_0019fe70(p3fes::EEContext&);
void fn_sub_19FEC0_0019fec0(p3fes::EEContext&);
void fn_sub_19FF10_0019ff10(p3fes::EEContext&);
void fn_sub_1A0040_001a0040(p3fes::EEContext&);
void fn_sub_1A02C0_001a02c0(p3fes::EEContext&);
void fn_sub_1A14C0_001a14c0(p3fes::EEContext&);
void fn_sub_1A1540_001a1540(p3fes::EEContext&);
void fn_sub_1A5AA0_001a5aa0(p3fes::EEContext&);
void fn_sub_1A5B30_001a5b30(p3fes::EEContext&);
void fn_sub_1A5BC0_001a5bc0(p3fes::EEContext&);
void fn_sub_1A6350_001a6350(p3fes::EEContext&);
void fn_sub_1A6400_001a6400(p3fes::EEContext&);
void fn_sub_1A64F0_001a64f0(p3fes::EEContext&);
void fn_sub_1A66F0_001a66f0(p3fes::EEContext&);
void fn_sub_1A6740_001a6740(p3fes::EEContext&);
void fn_sub_1A6C00_001a6c00(p3fes::EEContext&);
void fn_sub_1A6E90_001a6e90(p3fes::EEContext&);
void fn_sub_1A7570_001a7570(p3fes::EEContext&);
void fn_sub_1A7710_001a7710(p3fes::EEContext&);
void fn_sub_1A96C0_001a96c0(p3fes::EEContext&);
void fn_sub_1A9850_001a9850(p3fes::EEContext&);
void fn_sub_1AA1B0_001aa1b0(p3fes::EEContext&);
void fn_sub_1B00C0_001b00c0(p3fes::EEContext&);
void fn_sub_1B02C0_001b02c0(p3fes::EEContext&);
void fn_sub_1B0710_001b0710(p3fes::EEContext&);
void fn_sub_1B07D0_001b07d0(p3fes::EEContext&);
void fn_sub_1B0840_001b0840(p3fes::EEContext&);
void fn_sub_1B0870_001b0870(p3fes::EEContext&);
void fn_sub_1B08D0_001b08d0(p3fes::EEContext&);
void fn_sub_1B0910_001b0910(p3fes::EEContext&);
void fn_sub_1B0920_001b0920(p3fes::EEContext&);
void fn_sub_1B0950_001b0950(p3fes::EEContext&);
void fn_sub_1B09B0_001b09b0(p3fes::EEContext&);
void fn_sub_1B09F0_001b09f0(p3fes::EEContext&);
void fn_sub_1B0A20_001b0a20(p3fes::EEContext&);
void fn_sub_1B10F0_001b10f0(p3fes::EEContext&);
void fn_sub_1B2780_001b2780(p3fes::EEContext&);
void fn_sub_1B2860_001b2860(p3fes::EEContext&);
void fn_sub_1B2B30_001b2b30(p3fes::EEContext&);
void fn_sub_1B2B90_001b2b90(p3fes::EEContext&);
void fn_sub_1B2F00_001b2f00(p3fes::EEContext&);
void fn_sub_1B32F0_001b32f0(p3fes::EEContext&);
void fn_sub_1B3480_001b3480(p3fes::EEContext&);
void fn_sub_1B39E0_001b39e0(p3fes::EEContext&);
void fn_sub_1B3C90_001b3c90(p3fes::EEContext&);
void fn_sub_1B4E00_001b4e00(p3fes::EEContext&);
void fn_sub_1B5200_001b5200(p3fes::EEContext&);
void fn_sub_1B5380_001b5380(p3fes::EEContext&);
void fn_sub_1B5610_001b5610(p3fes::EEContext&);
void fn_sub_1B56F0_001b56f0(p3fes::EEContext&);
void fn_sub_1B5850_001b5850(p3fes::EEContext&);
void fn_sub_1B5880_001b5880(p3fes::EEContext&);
void fn_sub_1B58B0_001b58b0(p3fes::EEContext&);
void fn_sub_1B5950_001b5950(p3fes::EEContext&);
void fn_sub_1B5990_001b5990(p3fes::EEContext&);
void fn_sub_1B59C0_001b59c0(p3fes::EEContext&);
void fn_sub_1B5A00_001b5a00(p3fes::EEContext&);
void fn_sub_1B5A30_001b5a30(p3fes::EEContext&);
void fn_sub_1B5AE0_001b5ae0(p3fes::EEContext&);
void fn_sub_1B5B50_001b5b50(p3fes::EEContext&);
void fn_sub_1B5DF0_001b5df0(p3fes::EEContext&);
void fn_sub_1B5E30_001b5e30(p3fes::EEContext&);
void fn_sub_1B5E60_001b5e60(p3fes::EEContext&);
void fn_sub_1B5E90_001b5e90(p3fes::EEContext&);
void fn_sub_1B6060_001b6060(p3fes::EEContext&);
void fn_sub_1B60A0_001b60a0(p3fes::EEContext&);
void fn_sub_1B60D0_001b60d0(p3fes::EEContext&);
void fn_sub_1B6100_001b6100(p3fes::EEContext&);
void fn_sub_1B61F0_001b61f0(p3fes::EEContext&);
void fn_sub_1B6EB0_001b6eb0(p3fes::EEContext&);
void fn_sub_1B75E0_001b75e0(p3fes::EEContext&);
void fn_sub_1B76B0_001b76b0(p3fes::EEContext&);
void fn_sub_1B7700_001b7700(p3fes::EEContext&);
void fn_sub_1B7BB0_001b7bb0(p3fes::EEContext&);
void fn_sub_1B7C40_001b7c40(p3fes::EEContext&);
void fn_sub_1B7D00_001b7d00(p3fes::EEContext&);
void fn_sub_1B7D60_001b7d60(p3fes::EEContext&);
void fn_sub_1B7DC0_001b7dc0(p3fes::EEContext&);
void fn_sub_1B7E30_001b7e30(p3fes::EEContext&);
void fn_sub_1B7E60_001b7e60(p3fes::EEContext&);
void fn_sub_1B8000_001b8000(p3fes::EEContext&);
void fn_sub_1B8030_001b8030(p3fes::EEContext&);
void fn_sub_1B80C0_001b80c0(p3fes::EEContext&);
void fn_sub_1B8160_001b8160(p3fes::EEContext&);
void fn_sub_1B81F0_001b81f0(p3fes::EEContext&);
void fn_sub_1B83F0_001b83f0(p3fes::EEContext&);
void fn_sub_1B85A0_001b85a0(p3fes::EEContext&);
void fn_sub_1B8600_001b8600(p3fes::EEContext&);
void fn_sub_1B8680_001b8680(p3fes::EEContext&);
void fn_sub_1B8710_001b8710(p3fes::EEContext&);
void fn_sub_1B8870_001b8870(p3fes::EEContext&);
void fn_sub_1B88D0_001b88d0(p3fes::EEContext&);
void fn_sub_1B8960_001b8960(p3fes::EEContext&);
void fn_sub_1B8AE0_001b8ae0(p3fes::EEContext&);
void fn_sub_1B8B40_001b8b40(p3fes::EEContext&);
void fn_sub_1B8C40_001b8c40(p3fes::EEContext&);
void fn_sub_1B8CF0_001b8cf0(p3fes::EEContext&);
void fn_sub_1B8D60_001b8d60(p3fes::EEContext&);
void fn_sub_1B8DB0_001b8db0(p3fes::EEContext&);
void fn_sub_1B8FD0_001b8fd0(p3fes::EEContext&);
void fn_sub_1B9140_001b9140(p3fes::EEContext&);
void fn_sub_1BA8D0_001ba8d0(p3fes::EEContext&);
void fn_sub_1BAA50_001baa50(p3fes::EEContext&);
void fn_sub_1BAAA0_001baaa0(p3fes::EEContext&);
void fn_sub_1BD450_001bd450(p3fes::EEContext&);
void fn_sub_1BD8C0_001bd8c0(p3fes::EEContext&);
void fn_sub_1C0330_001c0330(p3fes::EEContext&);
void fn_sub_1C03B0_001c03b0(p3fes::EEContext&);
void fn_sub_1C03F0_001c03f0(p3fes::EEContext&);
void fn_sub_1C0440_001c0440(p3fes::EEContext&);
void fn_sub_1C0740_001c0740(p3fes::EEContext&);
void fn_sub_1C07F0_001c07f0(p3fes::EEContext&);
void fn_sub_1C1F30_001c1f30(p3fes::EEContext&);
void fn_sub_1C7F20_001c7f20(p3fes::EEContext&);
void fn_sub_1CD870_001cd870(p3fes::EEContext&);
void fn_sub_1CD8E0_001cd8e0(p3fes::EEContext&);
void fn_sub_1CE960_001ce960(p3fes::EEContext&);
void fn_sub_1D0270_001d0270(p3fes::EEContext&);
void fn_sub_1D0330_001d0330(p3fes::EEContext&);
void fn_sub_1D0390_001d0390(p3fes::EEContext&);
void fn_sub_1D03F0_001d03f0(p3fes::EEContext&);
void fn_sub_1D19D0_001d19d0(p3fes::EEContext&);
void fn_sub_1D1FA0_001d1fa0(p3fes::EEContext&);
void fn_sub_1D2610_001d2610(p3fes::EEContext&);
void fn_sub_1D2A10_001d2a10(p3fes::EEContext&);
void fn_sub_1D36F0_001d36f0(p3fes::EEContext&);
void fn_sub_1D3790_001d3790(p3fes::EEContext&);
void fn_sub_1D37F0_001d37f0(p3fes::EEContext&);
void fn_sub_1D4360_001d4360(p3fes::EEContext&);
void fn_sub_1D43E0_001d43e0(p3fes::EEContext&);
void fn_sub_1D4610_001d4610(p3fes::EEContext&);
void fn_sub_1D50C0_001d50c0(p3fes::EEContext&);
void fn_sub_1D5130_001d5130(p3fes::EEContext&);
void fn_sub_1D5F30_001d5f30(p3fes::EEContext&);
void fn_sub_1D6270_001d6270(p3fes::EEContext&);
void fn_sub_1D6B10_001d6b10(p3fes::EEContext&);
void fn_sub_1D6BC0_001d6bc0(p3fes::EEContext&);
void fn_sub_1D70A0_001d70a0(p3fes::EEContext&);
void fn_sub_1D8CB0_001d8cb0(p3fes::EEContext&);
void fn_sub_1D9F10_001d9f10(p3fes::EEContext&);
void fn_sub_1D9FD0_001d9fd0(p3fes::EEContext&);
void fn_sub_1DA000_001da000(p3fes::EEContext&);
void fn_sub_1DD600_001dd600(p3fes::EEContext&);
void fn_sub_1DD8E0_001dd8e0(p3fes::EEContext&);
void fn_sub_1DDCA0_001ddca0(p3fes::EEContext&);
void fn_sub_1E1230_001e1230(p3fes::EEContext&);
void fn_sub_1E2DA0_001e2da0(p3fes::EEContext&);
void fn_sub_1E2E50_001e2e50(p3fes::EEContext&);
void fn_sub_1E3940_001e3940(p3fes::EEContext&);
void fn_sub_1E6CB0_001e6cb0(p3fes::EEContext&);
void fn_sub_1E6D50_001e6d50(p3fes::EEContext&);
void fn_sub_1E6EA0_001e6ea0(p3fes::EEContext&);
void fn_sub_1E7200_001e7200(p3fes::EEContext&);
void fn_sub_1E7290_001e7290(p3fes::EEContext&);
void fn_sub_1E7410_001e7410(p3fes::EEContext&);
void fn_sub_1E7470_001e7470(p3fes::EEContext&);
void fn_sub_1E74E0_001e74e0(p3fes::EEContext&);
void fn_sub_1E7520_001e7520(p3fes::EEContext&);
void fn_sub_27C330_0027c330(p3fes::EEContext&);
void fn_sub_316B40_00316b40(p3fes::EEContext&);
void fn_sub_316BD0_00316bd0(p3fes::EEContext&);
void fn_sub_316F70_00316f70(p3fes::EEContext&);
void fn_sub_317450_00317450(p3fes::EEContext&);
void fn_sub_3174E0_003174e0(p3fes::EEContext&);
void fn_sub_3182D0_003182d0(p3fes::EEContext&);
void fn_sub_3189F0_003189f0(p3fes::EEContext&);
void fn_sub_318A30_00318a30(p3fes::EEContext&);
void fn_sub_318A50_00318a50(p3fes::EEContext&);
void fn_sub_318A70_00318a70(p3fes::EEContext&);
void fn_sub_318AD0_00318ad0(p3fes::EEContext&);
void fn_sub_318B60_00318b60(p3fes::EEContext&);
void fn_sub_318B80_00318b80(p3fes::EEContext&);
void fn_sub_319190_00319190(p3fes::EEContext&);
void fn_sub_319230_00319230(p3fes::EEContext&);
void fn_sub_34FCD0_0034fcd0(p3fes::EEContext&);
void fn_sub_34FCF0_0034fcf0(p3fes::EEContext&);
void fn_sub_34FD50_0034fd50(p3fes::EEContext&);
void fn_sub_34FDF0_0034fdf0(p3fes::EEContext&);
void fn_sub_34FE30_0034fe30(p3fes::EEContext&);
void fn_sub_350080_00350080(p3fes::EEContext&);
void fn_sub_35BFB0_0035bfb0(p3fes::EEContext&);
void fn_sub_36F480_0036f480(p3fes::EEContext&);
void fn_sub_36F4C0_0036f4c0(p3fes::EEContext&);
void fn_sub_397EC0_00397ec0(p3fes::EEContext&);
void fn_sub_398060_00398060(p3fes::EEContext&);
void fn_sub_398140_00398140(p3fes::EEContext&);
void fn_sub_3982D0_003982d0(p3fes::EEContext&);
void fn_sub_3B58C0_003b58c0(p3fes::EEContext&);
void fn_sub_3B5980_003b5980(p3fes::EEContext&);
void fn_sub_3B5A10_003b5a10(p3fes::EEContext&);
void fn_sub_3B5AB0_003b5ab0(p3fes::EEContext&);
void fn_sub_3B5D10_003b5d10(p3fes::EEContext&);
void fn_sub_3B5D50_003b5d50(p3fes::EEContext&);
void fn_sub_3B65D0_003b65d0(p3fes::EEContext&);
void fn_sub_3B66B0_003b66b0(p3fes::EEContext&);
void fn_sub_3B6790_003b6790(p3fes::EEContext&);
void fn_sub_3B6F50_003b6f50(p3fes::EEContext&);
void fn_sub_3B7090_003b7090(p3fes::EEContext&);
void fn_sub_3B78B0_003b78b0(p3fes::EEContext&);
void fn_sub_3C8F40_003c8f40(p3fes::EEContext&);
void fn_sub_3C8F70_003c8f70(p3fes::EEContext&);
void fn_sub_429E80_00429e80(p3fes::EEContext&);
void fn_sub_42BA30_0042ba30(p3fes::EEContext&);
void fn_sub_4350E0_004350e0(p3fes::EEContext&);
void fn_sub_4532D0_004532d0(p3fes::EEContext&);
void fn_sub_458BB0_00458bb0(p3fes::EEContext&);
void fn_sub_45A400_0045a400(p3fes::EEContext&);
void fn_sub_45A430_0045a430(p3fes::EEContext&);
void fn_sub_45AF70_0045af70(p3fes::EEContext&);
void fn_sub_48D0E0_0048d0e0(p3fes::EEContext&);
void fn_sub_48DA30_0048da30(p3fes::EEContext&);
void fn_sub_48EE70_0048ee70(p3fes::EEContext&);
void fn_sub_48EED0_0048eed0(p3fes::EEContext&);
void fn_sub_48EF60_0048ef60(p3fes::EEContext&);
void fn_sub_48EFA0_0048efa0(p3fes::EEContext&);
void fn_sub_48EFC0_0048efc0(p3fes::EEContext&);
void fn_sub_4916D0_004916d0(p3fes::EEContext&);
void fn_sub_491CC0_00491cc0(p3fes::EEContext&);
void fn_sub_491EA0_00491ea0(p3fes::EEContext&);
void fn_sub_4932C0_004932c0(p3fes::EEContext&);
void fn_sub_49A290_0049a290(p3fes::EEContext&);
void fn_sub_49A7C0_0049a7c0(p3fes::EEContext&);
void fn_sub_4BCBF0_004bcbf0(p3fes::EEContext&);
void fn_sub_4BDA10_004bda10(p3fes::EEContext&);
void fn_sub_4C1970_004c1970(p3fes::EEContext&);
void fn_sub_4C2CC0_004c2cc0(p3fes::EEContext&);
void fn_sub_4C2D20_004c2d20(p3fes::EEContext&);
void fn_sub_4C31B0_004c31b0(p3fes::EEContext&);
void fn_sub_4C3880_004c3880(p3fes::EEContext&);
void fn_sub_4C38C0_004c38c0(p3fes::EEContext&);
void fn_sub_4C5620_004c5620(p3fes::EEContext&);
void fn_sub_4C5780_004c5780(p3fes::EEContext&);
void fn_sub_4C58A0_004c58a0(p3fes::EEContext&);
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
void fn_sub_4C6BE0_004c6be0(p3fes::EEContext&);
void fn_sub_4C8680_004c8680(p3fes::EEContext&);
void fn_sub_4C9D70_004c9d70(p3fes::EEContext&);
void fn_sub_4C9DB0_004c9db0(p3fes::EEContext&);
void fn_sub_4CB270_004cb270(p3fes::EEContext&);
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);
void fn_sub_4CB890_004cb890(p3fes::EEContext&);
void fn_sub_4CB930_004cb930(p3fes::EEContext&);
void fn_sub_4D0D10_004d0d10(p3fes::EEContext&);
void fn_sub_4D0DC0_004d0dc0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// 0x001B00C0 sub_1B00C0 [K_Battle_ResetKosakaWork] -- 240 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B00C0(task): resets a "battle kosaka" skirmish task's work (task +60): unless its mode word (+32) is 3 or 4,
// destroys the per-unit tasks of the 24-byte slot array (+52, count +28) when bit 31 of +4 is set, releases the
// model of +12 (+296) when slots were in use, clears +32..+1184 (1,152 bytes), +28 and +1240, and sets the state +0 to
// 1. 21 callers, all in the skirmish / NPC-think / enemy-think layers.
void sub_1B00C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b00c0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, f4::kTaskWork);
    lw(a0, s0, 32);
    v1 = 3;
    if (a0 != v1) {
        // 0x001b00e8
        charge(ctx, 3);
        v1 = 4;
        if (a0 != v1) {
            // 0x001b00f4
            charge(ctx, 5);
            lw(v1, s0, 4);
            v0 = lui(0x8000);
            v0 = v1 & v0;
            if (v0 != 0) {
                // 0x001b0108
                charge(ctx, 3);
                s1 = 0;
                for (;;) {
                    // 0x001b0144
                    charge(ctx, 4);
                    lw(v0, s0, 28);
                    v0 = slt(s1, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001b0114
                    charge(ctx, 8);
                    v0 = sll(s1, 1);
                    v0 = addu(v0, s1);
                    v0 = sll(v0, 3);
                    v0 = addu(s0, v0);
                    s2 = addiu(v0, 52);
                    lw(a0, v0, 52);
                    if (a0 != 0) {
                        // 0x001b0134
                        charge(ctx, 2);
                        jal(ctx, 0x1B0134u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
                    }
                    // 0x001b013c
                    charge(ctx, 2);
                    sw(zero, s2, 0);
                    s1 = addiu(s1, 1);
                }
            }
            // 0x001b0154
            charge(ctx, 3);
            lw(v0, s0, 28);
            if (v0 != 0) {
                // 0x001b0160
                charge(ctx, 4);
                lw(v0, s0, 12);
                lw(a0, v0, 296);
                jal(ctx, 0x1B0168u, gen::fn_sub_319190_00319190);
            }
            // 0x001b0170
            charge(ctx, 9);
            a0 = addiu(s0, 32);
            a1 = 0;
            a2 = 1152;
            jal(ctx, 0x1B017Cu, gen::fn_memset_00521408);
            sw(zero, s0, 28);
            sw(zero, s0, 1240);
            v1 = 1;
            sw(v1, s0, 0);
        }
    }
    // 0x001b0194 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001B02C0 sub_1B02C0 [K_Pad_GetStickHeadingDeg] -- 1100 bytes; frame 0x30: ra sp+0x0
// sub_1B02C0(pad, rightStick) -> $f0: the heading of a pad stick in degrees (0..360, 180 = straight up) or 0.0 inside
// the dead zone. The 54-byte pad records at 0x7E094C (gPadFlags' block): with rightStick the right stick bytes
// (+21 x, +20 y), else the left stick (+19 x, +18 y) with the d-pad bits overriding (0x1000/0x4000 up/down,
// 0x8000/0x2000 left/right); each axis is centred (- 128) and zeroed inside +-48. Outside the dead zone: normalise
// (sub_4C69F0) and acosf of the dot product through ACC, scaled by the degrees-per-radian float at 0x7CB114,
// mirrored for negative x, + 180 and wrapped. Only caller: the virtual-pad task sub_1E05B0.
void sub_1B02C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x001b02c0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x0);
    v1 = addiu(sp, 0x10);
    v0 = 12;
    if (v1 != 0) {
        for (;;) {
            // 0x001b02d8
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
    // 0x001b02f4
    charge(ctx, 3);
    mtc1(zero, f0);
    if (a1 != 0) {
        // 0x001b04d8
        charge(ctx, 11);
        v0 = sll(a0, 3);
        v1 = addu(v0, a0);
        v0 = sll(v1, 2);
        v0 = subu(v0, v1);
        a0 = sll(v0, 1);
        v0 = 0x7E0000;
        v0 = addiu(v0, 2401);  // &0x7E0961
        v0 = addu(v0, a0);
        lbu(v0, v0, 0);
        if (i64(v0) < 0) {
            // 0x001b0518
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f1);
            cvt_s_w(f2, f1);
            add_s(f2, f2, f2);
        } else {
            // 0x001b0504
            charge(ctx, 5);
            mtc1(v0, f1);
            cvt_s_w(f2, f1);
        }
        // 0x001b0534
        charge(ctx, 11);
        v0 = 0x43000000;
        mtc1(v0, f1);
        sub_s(f2, f2, f1);
        swc1(f2, sp, 0x18);
        v0 = lui(0xC240);
        mtc1(v0, f1);
        c_lt_s(f2, f1);
        if (!cond(ctx)) {
            // 0x001b0560
            charge(ctx, 6);
            v0 = 0x42400000;
            mtc1(v0, f1);
            c_le_s(f2, f1);
            if (cond(ctx)) {
                // 0x001b0578
                charge(ctx, 1);
                sw(zero, sp, 0x18);
            }
        }
        // 0x001b057c
        charge(ctx, 6);
        v0 = 0x7E0000;
        v0 = addiu(v0, 2400);  // &0x7E0960
        v0 = addu(v0, a0);
        lbu(v0, v0, 0);
        if (i64(v0) < 0) {
            // 0x001b05a8
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f1);
            cvt_s_w(f2, f1);
            add_s(f2, f2, f2);
        } else {
            // 0x001b0594
            charge(ctx, 5);
            mtc1(v0, f1);
            cvt_s_w(f2, f1);
        }
        // 0x001b05c4
        charge(ctx, 11);
        v0 = 0x43000000;
        mtc1(v0, f1);
        sub_s(f2, f2, f1);
        swc1(f2, sp, 0x10);
        v0 = lui(0xC240);
        mtc1(v0, f1);
        c_lt_s(f2, f1);
        if (!cond(ctx)) {
            // 0x001b05f0
            charge(ctx, 6);
            v0 = 0x42400000;
            mtc1(v0, f1);
            c_le_s(f2, f1);
            if (cond(ctx)) {
                // 0x001b0608
                charge(ctx, 1);
                sw(zero, sp, 0x10);
            }
        }
    } else {
        // 0x001b0300
        charge(ctx, 11);
        v0 = sll(a0, 3);
        v1 = addu(v0, a0);
        v0 = sll(v1, 2);
        v0 = subu(v0, v1);
        a1 = sll(v0, 1);
        v0 = 0x7E0000;
        v0 = addiu(v0, 2399);  // &0x7E095F
        v0 = addu(v0, a1);
        lbu(v0, v0, 0);
        if (i64(v0) < 0) {
            // 0x001b0340
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f1);
            cvt_s_w(f1, f1);
            add_s(f1, f1, f1);
        } else {
            // 0x001b032c
            charge(ctx, 5);
            mtc1(v0, f1);
            cvt_s_w(f1, f1);
        }
        // 0x001b035c
        charge(ctx, 12);
        v0 = 0x43000000;
        mtc1(v0, f2);
        sub_s(f1, f1, f2);
        swc1(f1, sp, 0x18);
        v0 = 0x7E0000;
        v0 = addiu(v0, 2380);  // &0x7E094C
        v0 = addu(v0, a1);
        lhu(a1, v0, 0);
        v0 = a1 & 0x1000;
        if (v0 == 0) {
            // 0x001b039c
            charge(ctx, 3);
            v0 = a1 & 0x4000;
            if (v0 != 0) {
                // 0x001b03a8
                charge(ctx, 1);
                swc1(f2, sp, 0x18);
            }
        } else {
            // 0x001b038c
            charge(ctx, 4);
            v0 = lui(0xC300);
            sw(v0, sp, 0x18);
        }
        // 0x001b03ac
        charge(ctx, 3);
        v0 = a1 & 0xA000;
        if (v0 != 0) {
            // 0x001b03b8
            charge(ctx, 7);
            lwc1(f2, sp, 0x18);
            v0 = lui(0xC240);
            mtc1(v0, f1);
            c_lt_s(f2, f1);
            if (!cond(ctx)) {
                // 0x001b03d4
                charge(ctx, 6);
                v0 = 0x42400000;
                mtc1(v0, f1);
                c_le_s(f2, f1);
                if (cond(ctx)) {
                    // 0x001b03ec
                    charge(ctx, 1);
                    sw(zero, sp, 0x18);
                }
            }
        }
        // 0x001b03f0
        charge(ctx, 11);
        v0 = sll(a0, 3);
        v1 = addu(v0, a0);
        v0 = sll(v1, 2);
        v0 = subu(v0, v1);
        v1 = sll(v0, 1);
        v0 = 0x7E0000;
        v0 = addiu(v0, 2398);  // &0x7E095E
        v0 = addu(v0, v1);
        lbu(v0, v0, 0);
        if (i64(v0) < 0) {
            // 0x001b0430
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f1);
            cvt_s_w(f1, f1);
            add_s(f1, f1, f1);
        } else {
            // 0x001b041c
            charge(ctx, 5);
            mtc1(v0, f1);
            cvt_s_w(f1, f1);
        }
        // 0x001b044c
        charge(ctx, 8);
        v0 = 0x43000000;
        mtc1(v0, f2);
        sub_s(f1, f1, f2);
        swc1(f1, sp, 0x10);
        v0 = a1 & 0x8000;
        if (v0 == 0) {
            // 0x001b047c
            charge(ctx, 3);
            v0 = a1 & 0x2000;
            if (v0 != 0) {
                // 0x001b0488
                charge(ctx, 1);
                swc1(f2, sp, 0x10);
            }
        } else {
            // 0x001b046c
            charge(ctx, 4);
            v0 = lui(0xC300);
            sw(v0, sp, 0x10);
        }
        // 0x001b048c
        charge(ctx, 3);
        v0 = a1 & 0x5000;
        if (v0 != 0) {
            // 0x001b0498
            charge(ctx, 7);
            lwc1(f2, sp, 0x10);
            v0 = lui(0xC240);
            mtc1(v0, f1);
            c_lt_s(f2, f1);
            if (!cond(ctx)) {
                // 0x001b04b4
                charge(ctx, 6);
                v0 = 0x42400000;
                mtc1(v0, f1);
                c_le_s(f2, f1);
                if (cond(ctx)) {
                    // 0x001b04cc
                    charge(ctx, 3);
                    sw(zero, sp, 0x10);
                }
            }
        }
    }
    // 0x001b060c
    charge(ctx, 7);
    lwc1(f1, sp, 0x18);
    v0 = lui(0xC240);
    mtc1(v0, f3);
    c_lt_s(f1, f3);
    if (!cond(ctx)) {
        // 0x001b0628
        charge(ctx, 6);
        v0 = 0x42400000;
        mtc1(v0, f2);
        c_le_s(f1, f2);
        if (!cond(ctx)) {
            goto L_001b065c;
        }
        // 0x001b0640
        charge(ctx, 4);
        lwc1(f1, sp, 0x10);
        c_lt_s(f1, f3);
        if (cond(ctx)) {
            goto L_001b065c;
        }
        // 0x001b0650
        charge(ctx, 3);
        c_le_s(f1, f2);
        if (!cond(ctx)) {
            goto L_001b065c;
        }
        // 0x001b06fc (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_001b065c:
    charge(ctx, 25);
    a0 = addiu(sp, 0x20);
    a1 = addiu(sp, 0x10);
    jal(ctx, 0x1B0664u, gen::fn_sub_4C69F0_004c69f0);
    lwc1(f1, sp, 0x28);
    lwc1(f0, sp, 0x20);
    mula_s(f1, f1);
    madd_s(f0, f0, f0);
    sqrt_s(f0, f0);
    div_s(f12, f1, f0);
    jal(ctx, 0x1B0698u, gen::fn_acosf_0052e9e8);
    lwc1(f1, gp, -31708);  // 0x7CB114
    mul_s(f0, f0, f1);
    lwc1(f2, sp, 0x20);
    mtc1(zero, f1);
    c_lt_s(f2, f1);
    if (cond(ctx)) {
        // 0x001b06c0
        charge(ctx, 4);
        v0 = 0x43B40000;
        mtc1(v0, f1);
        sub_s(f0, f1, f0);
    }
    // 0x001b06d0
    charge(ctx, 10);
    v0 = 0x43340000;
    mtc1(v0, f1);
    add_s(f0, f0, f1);
    v0 = 0x43B40000;
    mtc1(v0, f1);
    c_le_s(f0, f1);
    if (!cond(ctx)) {
        // 0x001b06f8
        charge(ctx, 1);
        sub_s(f0, f0, f1);
    }
    // 0x001b06fc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001B0710 sub_1B0710 [K_Fldrc_RequestCurrentFieldPacks] -- 188 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1B0710(): with a field root alive (sField.root), requests the current field's .pac and .fpc packs again
// (sub_1B0870 / sub_1B0950 with the root's major / minor). Called by the battle at its result / exit states to
// bring the field data back.
void sub_1B0710(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b0710
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x1B071Cu, gen::fn_K_Field_Get_001b9120);
    lw(v1, v0, f4::fld::kRoot);
    if (v1 != 0) {
        // 0x001b0730
        charge(ctx, 34);
        jal(ctx, 0x1B0730u, gen::fn_K_Field_Get_001b9120);
        lw(a0, v0, f4::fld::kRoot);
        jal(ctx, 0x1B073Cu, gen::fn_K_Field_GetMajorId_001bab20);
        s0 = dsll32(v0, 16);
        s0 = dsra32(s0, 16);
        jal(ctx, 0x1B074Cu, gen::fn_K_Field_Get_001b9120);
        lw(a0, v0, f4::fld::kRoot);
        jal(ctx, 0x1B0758u, gen::fn_K_Field_GetMinorId_001bab30);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        a0 = s0;
        jal(ctx, 0x1B076Cu, gen::fn_sub_1B0870_001b0870);
        jal(ctx, 0x1B0774u, gen::fn_K_Field_Get_001b9120);
        lw(a0, v0, f4::fld::kRoot);
        jal(ctx, 0x1B0780u, gen::fn_K_Field_GetMajorId_001bab20);
        s0 = dsll32(v0, 16);
        s0 = dsra32(s0, 16);
        jal(ctx, 0x1B0790u, gen::fn_K_Field_Get_001b9120);
        lw(a0, v0, f4::fld::kRoot);
        jal(ctx, 0x1B079Cu, gen::fn_K_Field_GetMinorId_001bab30);
        a1 = dsll32(v0, 16);
        a1 = dsra32(a1, 16);
        a0 = s0;
        jal(ctx, 0x1B07B0u, gen::fn_sub_1B0950_001b0950);
    }
    // 0x001b07b8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001B07D0 sub_1B07D0 [K_Fldrc_AreFieldPacksLoaded] -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1B07D0() -> 1 when both field packs are resident (or no field root exists): sub_1B08D0 and sub_1B09B0.
void sub_1B07D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b07d0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 1;
    jal(ctx, 0x1B07E0u, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, f4::fld::kRoot);
    if (v0 != 0) {
        // 0x001b07f4
        charge(ctx, 4);
        jal(ctx, 0x1B07F4u, gen::fn_sub_1B08D0_001b08d0);
        if (v0 == 0) {
            // 0x001b0804
            charge(ctx, 1);
            s0 = 0;
        }
        // 0x001b0808
        charge(ctx, 4);
        jal(ctx, 0x1B0808u, gen::fn_sub_1B09B0_001b09b0);
        if (v0 == 0) {
            // 0x001b0818
            charge(ctx, 1);
            s0 = 0;
        }
    }
    // 0x001b081c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001B0840 sub_1B0840 [K_Fldrc_ReleaseFieldPacks] -- 40 bytes; frame 0x10: ra sp+0x0
// sub_1B0840(): releases the .pac then the .fpc pack request (sub_1B0920, sub_1B09F0).
void sub_1B0840(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x001b0840
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1B0848u, gen::fn_sub_1B0920_001b0920);
    jal(ctx, 0x1B0850u, gen::fn_sub_1B09F0_001b09f0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B0870 sub_1B0870 [K_Fldrc_RequestFldPac] -- 92 bytes; frame 0x50: ra sp+0x0
// sub_1B0870(major, minor): requests "field/pack/f%03d_%03d.pac" (H_Cdvd_Request, cached = 1) into the pack slot
// 0x7CE15C unless a request is already there. The .pac is the field's pack cache: while it is resident every
// K_Fldrc loader takes its files from it with H_Cdvd_CacheFindFile instead of reading them (sub_1B0910).
void sub_1B0870(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b0870
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x0);
    lw(v1, gp, f4::gpv::kPacRequest);  // 0x7CE15C
    if (v1 == 0) {
        // 0x001b0884
        charge(ctx, 14);
        a2 = dsll32(a0, 16);
        a2 = dsra32(a2, 16);
        a3 = dsll32(a1, 16);
        a3 = dsra32(a3, 16);
        a0 = addiu(sp, 0x10);
        a1 = 0x680000;
        a1 = addiu(a1, -29344);  // "field/pack/f%03d_%03d.pac"
        jal(ctx, 0x1B08A0u, gen::fn_sprintf_00523ac8);
        a0 = addiu(sp, 0x10);
        a1 = 1;
        jal(ctx, 0x1B08B0u, gen::fn_H_Cdvd_Request_00100d80);
        sw(v0, gp, f4::gpv::kPacRequest);  // 0x7CE15C
    }
    // 0x001b08bc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001B08D0 sub_1B08D0 [K_Fldrc_IsFldPacLoaded] -- 60 bytes; frame 0x10: ra sp+0x0
// sub_1B08D0() -> 1 when the .pac slot 0x7CE15C is empty or its request has finished loading.
void sub_1B08D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b08d0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, f4::gpv::kPacRequest);  // 0x7CE15C
    if (a0 != 0) {
        // 0x001b08f0
        charge(ctx, 3);
        jal(ctx, 0x1B08F0u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
        v0 = sltu(0, v0);
    } else {
        // 0x001b08e4
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x001b08fc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B0920 sub_1B0920 [K_Fldrc_ReleaseFldPac] -- 48 bytes; frame 0x10: ra sp+0x0
// sub_1B0920(): destroys the .pac request in 0x7CE15C and clears the slot.
void sub_1B0920(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b0920
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, f4::gpv::kPacRequest);  // 0x7CE15C
    if (a0 != 0) {
        // 0x001b0934
        charge(ctx, 3);
        jal(ctx, 0x1B0934u, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, gp, f4::gpv::kPacRequest);  // 0x7CE15C
    }
    // 0x001b0940 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B0950 sub_1B0950 [K_Fldrc_RequestFldFpc] -- 92 bytes; frame 0x50: ra sp+0x0
// sub_1B0950(major, minor): requests "field/pack/f%03d_%03d.fpc" (the field's model pack) into 0x7CE160 unless one is
// already there.
void sub_1B0950(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b0950
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x0);
    lw(v1, gp, f4::gpv::kFpcRequest);  // 0x7CE160
    if (v1 == 0) {
        // 0x001b0964
        charge(ctx, 14);
        a2 = dsll32(a0, 16);
        a2 = dsra32(a2, 16);
        a3 = dsll32(a1, 16);
        a3 = dsra32(a3, 16);
        a0 = addiu(sp, 0x10);
        a1 = 0x680000;
        a1 = addiu(a1, -29312);  // "field/pack/f%03d_%03d.fpc"
        jal(ctx, 0x1B0980u, gen::fn_sprintf_00523ac8);
        a0 = addiu(sp, 0x10);
        a1 = 1;
        jal(ctx, 0x1B0990u, gen::fn_H_Cdvd_Request_00100d80);
        sw(v0, gp, f4::gpv::kFpcRequest);  // 0x7CE160
    }
    // 0x001b099c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001B09B0 sub_1B09B0 [K_Fldrc_IsFldFpcLoaded] -- 60 bytes; frame 0x10: ra sp+0x0
// sub_1B09B0() -> 1 when the .fpc slot 0x7CE160 is empty or loaded.
void sub_1B09B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b09b0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, f4::gpv::kFpcRequest);  // 0x7CE160
    if (a0 != 0) {
        // 0x001b09d0
        charge(ctx, 3);
        jal(ctx, 0x1B09D0u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
        v0 = sltu(0, v0);
    } else {
        // 0x001b09c4
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x001b09dc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B09F0 sub_1B09F0 [K_Fldrc_ReleaseFldFpc] -- 48 bytes; frame 0x10: ra sp+0x0
// sub_1B09F0(): destroys the .fpc request in 0x7CE160 and clears the slot.
void sub_1B09F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b09f0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, f4::gpv::kFpcRequest);  // 0x7CE160
    if (a0 != 0) {
        // 0x001b0a04
        charge(ctx, 3);
        jal(ctx, 0x1B0A04u, gen::fn_H_Cdvd_Destroy_00100ec0);
        sw(zero, gp, f4::gpv::kFpcRequest);  // 0x7CE160
    }
    // 0x001b0a10 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B0A20 sub_1B0A20 [K_Fldrc_RequestFieldResources] -- 1740 bytes; frame 0xD0: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B0A20(major, minor) (from MT_Scene_Load): queues the field's model packs for the step loader sub_1B10F0.
// Clears the resource count (sField +4456) and the loader step (+4184); then
//  * an ordinary field (not a random floor 21..28 / 41..48 with minor 0, not a fixed floor 51..58 / 71..78): request
//    the .fpc and push {major, minor} on the pack queue (sField +4188 count, +4192 u16 pairs);
//  * a fixed floor 51..58 / 71..78: major - 30 is the block set, sField.flags (+56) bit 31 set, the floor map
//    "field/map/f%03d_%03d.MAP" (sub_1E7470) to +4300, the block object model fobj000 (0x7CE280);
//  * with flags bit 31 (dungeon floors; the dungeon task passes entry.flags | 0x80000000): request the .fpc of the
//    real ids and push the nine Tartarus block models {set, 18}, {set, 8}, {set, 7} .. {set, 1};
//  * a random floor of an already-loaded block set: reuse the nine block resources of dword_86BDC0 (resource list
//    +4460, count 9) and jump the loader to step 4.
// Tartarus majors also load the shared floor objects fobj001 / fobj002 (+4588 / +4592). 0x7CE164 := the frame
// counter at 0x7CDEAC (the load-time measurement of sub_1B10F0 step 4).
void sub_1B0A20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b0a20
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    jal(ctx, 0x1B0A40u, gen::fn_K_Field_Get_001b9120);
    sw(zero, v0, f4::fld::kResCount);
    jal(ctx, 0x1B0A4Cu, gen::fn_K_Field_Get_001b9120);
    sw(zero, v0, f4::fld::kLoadStep);
    s1 = dsll32(s3, 16);
    s1 = dsra32(s1, 16);
    v0 = slti(s1, 21);
    if (v0 == 0) {
        // 0x001b0a6c
        charge(ctx, 3);
        at = slti(s1, 29);
        if (at == 0) {
            goto L_001b0a88;
        }
        // 0x001b0a78
        charge(ctx, 4);
        v0 = dsll32(s2, 16);
        v0 = dsra32(v0, 16);
        if (v0 != 0) {
            goto L_001b0a88;
        }
    L_001b0ae0:
        charge(ctx, 3);
        v0 = slti(s1, 51);
        if (v0 == 0) {
            // 0x001b0aec
            charge(ctx, 3);
            at = slti(s1, 59);
            if (at == 0) {
                goto L_001b0af8;
            }
        L_001b0b10:
            charge(ctx, 20);
            v0 = addiu(s1, -30);
            s0 = dsll32(v0, 16);
            s0 = dsra32(s0, 16);
            jal(ctx, 0x1B0B1Cu, gen::fn_K_Field_Get_001b9120);
            lw(a0, v0, f4::fld::kFlags);
            v1 = lui(0x8000);
            v1 = a0 | v1;
            sw(v1, v0, f4::fld::kFlags);
            a0 = s3 & 0xFFFF;
            a1 = s2 & 0xFFFF;
            jal(ctx, 0x1B0B3Cu, gen::fn_sub_1E7470_001e7470);
            s3 = v0;
            jal(ctx, 0x1B0B48u, gen::fn_K_Field_Get_001b9120);
            sw(s3, v0, f4::fld::kMapFile);
            lw(v0, gp, f4::gpv::kFloorObj0);  // 0x7CE280
            if (v0 == 0) {
                // 0x001b0b60
                charge(ctx, 10);
                a0 = 4;
                a1 = 0xFFFF;
                a2 = 0x680000;
                a2 = addiu(a2, -29280);  // "field/grmd/fobj000.RMD"
                a3 = 0;
                jal(ctx, 0x1B0B74u, gen::fn_sub_316B40_00316b40);
                sw(v0, gp, f4::gpv::kFloorObj0);  // 0x7CE280
            }
            goto L_001b0b90;
        }
    L_001b0af8:
        charge(ctx, 3);
        v0 = slti(s1, 71);
        if (v0 == 0) {
            // 0x001b0b04
            charge(ctx, 3);
            at = slti(s1, 79);
            if (at == 0) {
                goto L_001b0b88;
            }
            goto L_001b0b10;
        }
    L_001b0b88:
        charge(ctx, 2);
        s0 = dsll32(s3, 16);
        s0 = dsra32(s0, 16);
    L_001b0b90:
        charge(ctx, 7);
        jal(ctx, 0x1B0B90u, gen::fn_K_Field_Get_001b9120);
        lw(v1, v0, f4::fld::kFlags);
        v0 = lui(0x8000);
        v0 = v1 & v0;
        if (v0 == 0) {
            // 0x001b0f10
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x001b0f44
                charge(ctx, 3);
                v0 = sltiu(s2, 9);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001b0f1c
                charge(ctx, 10);
                s0 = sll(s2, 2);
                v0 = 0x870000;
                v0 = addiu(v0, -16960);  // &0x86BDC0
                v0 = addu(v0, s0);
                lw(s3, v0, 0);
                jal(ctx, 0x1B0F30u, gen::fn_K_Field_Get_001b9120);
                v0 = addu(v0, s0);
                sw(s3, v0, f4::fld::kRes);
                s2 = addiu(s2, 1);
            }
            // 0x001b0f50
            charge(ctx, 10);
            s0 = 9;
            jal(ctx, 0x1B0F54u, gen::fn_K_Field_Get_001b9120);
            sw(s0, v0, f4::fld::kResCount);
            s0 = 4;
            jal(ctx, 0x1B0F64u, gen::fn_K_Field_Get_001b9120);
            sw(s0, v0, f4::fld::kLoadStep);
        } else {
            // 0x001b0bac
            charge(ctx, 3);
            lw(v0, gp, f4::gpv::kFpcRequest);  // 0x7CE160
            if (v0 == 0) {
                // 0x001b0bb8
                charge(ctx, 13);
                a3 = dsll32(s2, 16);
                a3 = dsra32(a3, 16);
                a0 = addiu(sp, 0x90);
                a1 = 0x680000;
                a1 = addiu(a1, -29312);  // "field/pack/f%03d_%03d.fpc"
                a2 = s1;
                jal(ctx, 0x1B0BD0u, gen::fn_sprintf_00523ac8);
                a0 = addiu(sp, 0x90);
                a1 = 1;
                jal(ctx, 0x1B0BE0u, gen::fn_H_Cdvd_Request_00100d80);
                sw(v0, gp, f4::gpv::kFpcRequest);  // 0x7CE160
            }
            // 0x001b0bec
            charge(ctx, 201);
            s0 = s0 & 0xFFFF;
            jal(ctx, 0x1B0BF0u, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kPackCount);
            s2 = sll(v0, 2);
            jal(ctx, 0x1B0C00u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s2);
            sh(s0, v0, f4::fld::kPackMajor);
            s2 = 18;
            jal(ctx, 0x1B0C14u, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kPackCount);
            s3 = sll(v0, 2);
            jal(ctx, 0x1B0C24u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s3);
            sh(s2, v0, f4::fld::kPackMinor);
            jal(ctx, 0x1B0C34u, gen::fn_K_Field_Get_001b9120);
            lw(v1, v0, f4::fld::kPackCount);
            v1 = addiu(v1, 1);
            sw(v1, v0, f4::fld::kPackCount);
            jal(ctx, 0x1B0C48u, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kPackCount);
            s2 = sll(v0, 2);
            jal(ctx, 0x1B0C58u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s2);
            sh(s0, v0, f4::fld::kPackMajor);
            s2 = 8;
            jal(ctx, 0x1B0C6Cu, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kPackCount);
            s3 = sll(v0, 2);
            jal(ctx, 0x1B0C7Cu, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s3);
            sh(s2, v0, f4::fld::kPackMinor);
            jal(ctx, 0x1B0C8Cu, gen::fn_K_Field_Get_001b9120);
            lw(v1, v0, f4::fld::kPackCount);
            v1 = addiu(v1, 1);
            sw(v1, v0, f4::fld::kPackCount);
            jal(ctx, 0x1B0CA0u, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kPackCount);
            s2 = sll(v0, 2);
            jal(ctx, 0x1B0CB0u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s2);
            sh(s0, v0, f4::fld::kPackMajor);
            s2 = 7;
            jal(ctx, 0x1B0CC4u, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kPackCount);
            s3 = sll(v0, 2);
            jal(ctx, 0x1B0CD4u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s3);
            sh(s2, v0, f4::fld::kPackMinor);
            jal(ctx, 0x1B0CE4u, gen::fn_K_Field_Get_001b9120);
            lw(v1, v0, f4::fld::kPackCount);
            v1 = addiu(v1, 1);
            sw(v1, v0, f4::fld::kPackCount);
            jal(ctx, 0x1B0CF8u, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kPackCount);
            s2 = sll(v0, 2);
            jal(ctx, 0x1B0D08u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s2);
            sh(s0, v0, f4::fld::kPackMajor);
            s2 = 6;
            jal(ctx, 0x1B0D1Cu, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kPackCount);
            s3 = sll(v0, 2);
            jal(ctx, 0x1B0D2Cu, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s3);
            sh(s2, v0, f4::fld::kPackMinor);
            jal(ctx, 0x1B0D3Cu, gen::fn_K_Field_Get_001b9120);
            lw(v1, v0, f4::fld::kPackCount);
            v1 = addiu(v1, 1);
            sw(v1, v0, f4::fld::kPackCount);
            jal(ctx, 0x1B0D50u, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kPackCount);
            s2 = sll(v0, 2);
            jal(ctx, 0x1B0D60u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s2);
            sh(s0, v0, f4::fld::kPackMajor);
            s2 = 5;
            jal(ctx, 0x1B0D74u, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kPackCount);
            s3 = sll(v0, 2);
            jal(ctx, 0x1B0D84u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s3);
            sh(s2, v0, f4::fld::kPackMinor);
            jal(ctx, 0x1B0D94u, gen::fn_K_Field_Get_001b9120);
            lw(v1, v0, f4::fld::kPackCount);
            v1 = addiu(v1, 1);
            sw(v1, v0, f4::fld::kPackCount);
            jal(ctx, 0x1B0DA8u, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kPackCount);
            s2 = sll(v0, 2);
            jal(ctx, 0x1B0DB8u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s2);
            sh(s0, v0, f4::fld::kPackMajor);
            s2 = 4;
            jal(ctx, 0x1B0DCCu, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kPackCount);
            s3 = sll(v0, 2);
            jal(ctx, 0x1B0DDCu, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s3);
            sh(s2, v0, f4::fld::kPackMinor);
            jal(ctx, 0x1B0DECu, gen::fn_K_Field_Get_001b9120);
            lw(v1, v0, f4::fld::kPackCount);
            v1 = addiu(v1, 1);
            sw(v1, v0, f4::fld::kPackCount);
            jal(ctx, 0x1B0E00u, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kPackCount);
            s2 = sll(v0, 2);
            jal(ctx, 0x1B0E10u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s2);
            sh(s0, v0, f4::fld::kPackMajor);
            s2 = 3;
            jal(ctx, 0x1B0E24u, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kPackCount);
            s3 = sll(v0, 2);
            jal(ctx, 0x1B0E34u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s3);
            sh(s2, v0, f4::fld::kPackMinor);
            jal(ctx, 0x1B0E44u, gen::fn_K_Field_Get_001b9120);
            lw(v1, v0, f4::fld::kPackCount);
            v1 = addiu(v1, 1);
            sw(v1, v0, f4::fld::kPackCount);
            jal(ctx, 0x1B0E58u, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kPackCount);
            s2 = sll(v0, 2);
            jal(ctx, 0x1B0E68u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s2);
            sh(s0, v0, f4::fld::kPackMajor);
            s2 = 2;
            jal(ctx, 0x1B0E7Cu, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kPackCount);
            s3 = sll(v0, 2);
            jal(ctx, 0x1B0E8Cu, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s3);
            sh(s2, v0, f4::fld::kPackMinor);
            jal(ctx, 0x1B0E9Cu, gen::fn_K_Field_Get_001b9120);
            lw(v1, v0, f4::fld::kPackCount);
            v1 = addiu(v1, 1);
            sw(v1, v0, f4::fld::kPackCount);
            jal(ctx, 0x1B0EB0u, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kPackCount);
            s2 = sll(v0, 2);
            jal(ctx, 0x1B0EC0u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s2);
            sh(s0, v0, f4::fld::kPackMajor);
            s2 = 1;
            jal(ctx, 0x1B0ED4u, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kPackCount);
            s0 = sll(v0, 2);
            jal(ctx, 0x1B0EE4u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s0);
            sh(s2, v0, f4::fld::kPackMinor);
            jal(ctx, 0x1B0EF4u, gen::fn_K_Field_Get_001b9120);
            lw(v1, v0, f4::fld::kPackCount);
            v1 = addiu(v1, 1);
            sw(v1, v0, f4::fld::kPackCount);
        }
        goto L_001b100c;
    }
L_001b0a88:
    charge(ctx, 3);
    v0 = slti(s1, 41);
    if (v0 == 0) {
        // 0x001b0a94
        charge(ctx, 3);
        at = slti(s1, 49);
        if (at == 0) {
            goto L_001b0ab0;
        }
        // 0x001b0aa0
        charge(ctx, 4);
        v0 = dsll32(s2, 16);
        v0 = dsra32(v0, 16);
        if (v0 == 0) {
            goto L_001b0ae0;
        }
        goto L_001b0ab0;
    }
L_001b0ab0:
    charge(ctx, 3);
    v0 = slti(s1, 51);
    if (v0 == 0) {
        // 0x001b0abc
        charge(ctx, 3);
        at = slti(s1, 59);
        if (at != 0) {
            goto L_001b0ae0;
        }
        goto L_001b0ac8;
    }
L_001b0ac8:
    charge(ctx, 3);
    v0 = slti(s1, 71);
    if (v0 == 0) {
        // 0x001b0ad4
        charge(ctx, 3);
        at = slti(s1, 79);
        if (at == 0) {
            goto L_001b0f78;
        }
        goto L_001b0ae0;
    }
L_001b0f78:
    charge(ctx, 3);
    lw(v0, gp, f4::gpv::kFpcRequest);  // 0x7CE160
    if (v0 == 0) {
        // 0x001b0f84
        charge(ctx, 13);
        a3 = dsll32(s2, 16);
        a3 = dsra32(a3, 16);
        a0 = addiu(sp, 0x50);
        a1 = 0x680000;
        a1 = addiu(a1, -29312);  // "field/pack/f%03d_%03d.fpc"
        a2 = s1;
        jal(ctx, 0x1B0F9Cu, gen::fn_sprintf_00523ac8);
        a0 = addiu(sp, 0x50);
        a1 = 1;
        jal(ctx, 0x1B0FACu, gen::fn_H_Cdvd_Request_00100d80);
        sw(v0, gp, f4::gpv::kFpcRequest);  // 0x7CE160
    }
    // 0x001b0fb8
    charge(ctx, 21);
    jal(ctx, 0x1B0FB8u, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, f4::fld::kPackCount);
    s0 = sll(v0, 2);
    jal(ctx, 0x1B0FC8u, gen::fn_K_Field_Get_001b9120);
    v0 = addu(v0, s0);
    sh(s3, v0, f4::fld::kPackMajor);
    jal(ctx, 0x1B0FD8u, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, f4::fld::kPackCount);
    s0 = sll(v0, 2);
    jal(ctx, 0x1B0FE8u, gen::fn_K_Field_Get_001b9120);
    v0 = addu(v0, s0);
    sh(s2, v0, f4::fld::kPackMinor);
    jal(ctx, 0x1B0FF8u, gen::fn_K_Field_Get_001b9120);
    lw(v1, v0, f4::fld::kPackCount);
    v1 = addiu(v1, 1);
    sw(v1, v0, f4::fld::kPackCount);
L_001b100c:
    charge(ctx, 3);
    v1 = slti(s1, 21);
    if (v1 == 0) {
        // 0x001b1018
        charge(ctx, 3);
        at = slti(s1, 29);
        if (at == 0) {
            goto L_001b1024;
        }
    L_001b106c:
        charge(ctx, 22);
        a0 = 4;
        a1 = 0xFFFE;
        a2 = 0x680000;
        a2 = addiu(a2, -29248);  // "field/grmd/fobj001.RMD"
        a3 = 0;
        jal(ctx, 0x1B1080u, gen::fn_sub_316B40_00316b40);
        s0 = v0;
        jal(ctx, 0x1B108Cu, gen::fn_K_Field_Get_001b9120);
        sw(s0, v0, f4::fld::kFloorObj1);
        a0 = 4;
        a1 = 0xFFFD;
        a2 = 0x680000;
        a2 = addiu(a2, -29216);  // "field/grmd/fobj002.RMD"
        a3 = 0;
        jal(ctx, 0x1B10ACu, gen::fn_sub_316B40_00316b40);
        s0 = v0;
        jal(ctx, 0x1B10B8u, gen::fn_K_Field_Get_001b9120);
        sw(s0, v0, f4::fld::kFloorObj2);
        // 0x001b10c4 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        lw(v1, gp, f4::gpv::kFrameCounter);  // 0x7CDEAC
        sw(v1, gp, f4::gpv::kLoadTime);  // 0x7CE164
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0xD0);
        return;
    }
L_001b1024:
    charge(ctx, 3);
    v1 = slti(s1, 41);
    if (v1 == 0) {
        // 0x001b1030
        charge(ctx, 3);
        at = slti(s1, 49);
        if (at != 0) {
            goto L_001b106c;
        }
        goto L_001b103c;
    }
L_001b103c:
    charge(ctx, 3);
    v1 = slti(s1, 51);
    if (v1 == 0) {
        // 0x001b1048
        charge(ctx, 3);
        at = slti(s1, 59);
        if (at != 0) {
            goto L_001b106c;
        }
        goto L_001b1054;
    }
L_001b1054:
    charge(ctx, 3);
    v1 = slti(s1, 71);
    if (v1 == 0) {
        // 0x001b1060
        charge(ctx, 3);
        at = slti(s1, 79);
        if (at != 0) {
            goto L_001b106c;
        }
    }
    // 0x001b10c4 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    lw(v1, gp, f4::gpv::kFrameCounter);  // 0x7CDEAC
    sw(v1, gp, f4::gpv::kLoadTime);  // 0x7CE164
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// 0x001B10F0 sub_1B10F0 [K_Fldrc_TryLoadFieldResources] -- 5776 bytes; frame 0xE0: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B10F0() -> 1 when the field's resources are complete (from MT_Scene_TryLoadFinish 0x3B5A10, once a frame).
// A step machine on sField +4184 (999 = done, which also releases the .pac):
//   0  both packs resident: pop a {major, minor} pair from the pack queue and open its model file
//      (sub_1B2780 -> a 2,636-byte field resource record, appended to the list sField +4460 / count +4456)  -> 1
//   1  file loaded: parse the RW stream (sub_1B2B90)                                                     -> 2
//   2  clumps / worlds / collision ready (sub_1B2F00); more pairs queued -> 0; else take the scene ids from the
//      first record when the scene asks (+12 bit 31) and create every record's field objects (sub_1B3480) -> 3
//   3  all objects loaded (sub_1B39E0), release the .fpc                                                     -> 4
//   4  floor objects fobj001 / fobj002 loaded; the load time (frames, + 204800 below major 200) to 0x7CE164; open
//      the NPC table, NPC messages and NPC script (sub_1B8160 / sub_1B8680 / sub_1B88D0 -> 0x867EF8.. )      -> 5
//   5  the three NPC files copied into the field (sub_1B81F0 / sub_1B8710 / sub_1B8960); request the NPC placement
//      FBN of the fixed floor (one) or of every record (sub_1E2DA0 -> record +2628)                         -> 6
//   6  FBN headers parsed and NPC models requested (sub_1E2E50)                                              -> 7
//   7  models ready: NPCs placed (sub_1E3940); fixed floors: the map file and the 16 x 16 grid copied from it into
//      sField +72; HBN hit files requested (sub_1E6CB0 -> +2616)                                            -> 8
//   8  hit files copied (sub_1E6D50 -> +2620) and their hits created (sub_1E6EA0); then the layout: a random floor
//      generates its grid (sub_1BD450(major - 20, or - 40 for The Answer)) and builds the blocks (sub_1BD8C0),
//      a fixed floor builds them from the map grid, an ordinary field registers its single world and its field
//      objects in the scene (models -> MT_Scene_CreateResModelFld 0x3B65D0, EPL -> 0x3B66B0); ENV file
//      requested (sub_1B6100 -> scene +16)                                                                  -> 9
//   9  ENV applied (sub_1B61F0); the camera file (sub_1D6B10) when there is one                         -> 10 / 999
//  10  CMR camera ready (sub_1D6BC0 -> sub_3B6F50)                                                           -> 999
//  30..32 / 40 / 41 the reload path for scene refreshes (NPC FBN again, ENV again; +12 bit 2 asks for the ENV).
// K_Assert (k_fldrc.c 740 / 773) on a failed object registration (it returns in retail).
void sub_1B10F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x001b10f0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x1B1110u, gen::fn_K_Field_Get_001b9120);
    lw(v1, v0, f4::fld::kLoadStep);
    v0 = 999;
    if (v1 == v0) {
        // 0x001b2730
        charge(ctx, 3);
        lw(a0, gp, f4::gpv::kPacRequest);  // 0x7CE15C
        if (a0 != 0) {
            // 0x001b273c
            charge(ctx, 3);
            jal(ctx, 0x1B273Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
            sw(zero, gp, f4::gpv::kPacRequest);  // 0x7CE15C
        }
        // 0x001b2748
        charge(ctx, 3);
        v0 = 1;
    } else {
        // 0x001b1128
        charge(ctx, 3);
        v0 = 41;
        if (v1 != v0) {
            // 0x001b1134
            charge(ctx, 3);
            v0 = 40;
            if (v1 != v0) {
                // 0x001b1140
                charge(ctx, 3);
                v0 = 32;
                if (v1 != v0) {
                    // 0x001b114c
                    charge(ctx, 3);
                    v0 = 31;
                    if (v1 != v0) {
                        // 0x001b1158
                        charge(ctx, 3);
                        v0 = 30;
                        if (v1 == v0) {
                            // 0x001b2314
                            charge(ctx, 10);
                            a0 = 3;
                            jal(ctx, 0x1B2318u, gen::fn_sub_3B5D50_003b5d50);
                            s2 = v0;
                            a0 = 8;
                            jal(ctx, 0x1B2328u, gen::fn_sub_3B5D50_003b5d50);
                            s1 = v0;
                            for (;;) {
                                // 0x001b2350
                                charge(ctx, 3);
                                if (s2 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x001b233c
                                charge(ctx, 5);
                                lw(s0, s2, 248);
                                lhu(a0, s2, 0);
                                jal(ctx, 0x1B2344u, gen::fn_sub_3B7090_003b7090);
                                s2 = s0;
                            }
                            // 0x001b235c
                            charge(ctx, 2);
                            for (;;) {
                                // 0x001b2378
                                charge(ctx, 3);
                                if (s1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x001b2364
                                charge(ctx, 5);
                                lw(s0, s1, 248);
                                lhu(a0, s1, 0);
                                jal(ctx, 0x1B236Cu, gen::fn_sub_3B7090_003b7090);
                                s1 = s0;
                            }
                            // 0x001b2384
                            charge(ctx, 5);
                            jal(ctx, 0x1B2384u, gen::fn_sub_1A02C0_001a02c0);
                            v1 = 1;
                            if (v0 != v1) {
                                // 0x001b23cc
                                charge(ctx, 3);
                                s2 = 0;
                                for (;;) {
                                    // 0x001b2434
                                    charge(ctx, 6);
                                    jal(ctx, 0x1B2434u, gen::fn_K_Field_Get_001b9120);
                                    lw(v0, v0, f4::fld::kResCount);
                                    v0 = slt(s2, v0);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x001b23d8
                                    charge(ctx, 23);
                                    s1 = sll(s2, 2);
                                    jal(ctx, 0x1B23DCu, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s1);
                                    lw(v0, v0, f4::fld::kRes);
                                    lhu(s0, v0, 4);
                                    jal(ctx, 0x1B23F0u, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s1);
                                    lw(v0, v0, f4::fld::kRes);
                                    lhu(a1, v0, 6);
                                    lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                    a0 = s0;
                                    lh(a2, v0, f4::scene::kNpcSet);
                                    jal(ctx, 0x1B2410u, gen::fn_sub_1E2DA0_001e2da0);
                                    s0 = v0;
                                    jal(ctx, 0x1B241Cu, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s1);
                                    lw(v0, v0, f4::fld::kRes);
                                    sw(s0, v0, 2628);
                                    s2 = addiu(s2, 1);
                                }
                            } else {
                                // 0x001b2398
                                charge(ctx, 13);
                                lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                lhu(a0, v0, f4::scene::kMajor);
                                lhu(a1, v0, f4::scene::kMinor);
                                lh(a2, v0, f4::scene::kNpcSet);
                                jal(ctx, 0x1B23A8u, gen::fn_sub_1E2DA0_001e2da0);
                                s0 = v0;
                                jal(ctx, 0x1B23B4u, gen::fn_K_Field_Get_001b9120);
                                lw(v0, v0, f4::fld::kRes);
                                sw(s0, v0, 2628);
                            }
                            // 0x001b244c
                            charge(ctx, 4);
                            s0 = 31;
                            jal(ctx, 0x1B2450u, gen::fn_K_Field_Get_001b9120);
                            sw(s0, v0, f4::fld::kLoadStep);
                            goto L_001b245c;
                        }
                        // 0x001b1164
                        charge(ctx, 3);
                        v0 = 10;
                        if (v1 != v0) {
                            // 0x001b1170
                            charge(ctx, 3);
                            v0 = 9;
                            if (v1 != v0) {
                                // 0x001b117c
                                charge(ctx, 3);
                                v0 = 8;
                                if (v1 != v0) {
                                    // 0x001b1188
                                    charge(ctx, 3);
                                    v0 = 7;
                                    if (v1 != v0) {
                                        // 0x001b1194
                                        charge(ctx, 3);
                                        v0 = 6;
                                        if (v1 != v0) {
                                            // 0x001b11a0
                                            charge(ctx, 3);
                                            v0 = 5;
                                            if (v1 != v0) {
                                                // 0x001b11ac
                                                charge(ctx, 3);
                                                v0 = 4;
                                                if (v1 != v0) {
                                                    // 0x001b11b8
                                                    charge(ctx, 3);
                                                    v0 = 3;
                                                    if (v1 != v0) {
                                                        // 0x001b11c4
                                                        charge(ctx, 3);
                                                        v0 = 2;
                                                        if (v1 != v0) {
                                                            // 0x001b11d0
                                                            charge(ctx, 3);
                                                            v0 = 1;
                                                            if (v1 != v0) {
                                                                // 0x001b11dc
                                                                charge(ctx, 2);
                                                                if (v1 == 0) {
                                                                    // 0x001b11ec
                                                                    charge(ctx, 3);
                                                                    lw(a0, gp, f4::gpv::kPacRequest);  // 0x7CE15C
                                                                    if (a0 != 0) {
                                                                        // 0x001b1200
                                                                        charge(ctx, 4);
                                                                        jal(ctx, 0x1B1200u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                                                                        if (v0 == 0) {
                                                                            // 0x001b121c
                                                                            charge(ctx, 1);
                                                                            v0 = 0;
                                                                        } else {
                                                                            // 0x001b1210
                                                                            charge(ctx, 3);
                                                                            v0 = 1;
                                                                        }
                                                                    } else {
                                                                        // 0x001b11f8
                                                                        charge(ctx, 2);
                                                                    }
                                                                    // 0x001b1220
                                                                    charge(ctx, 2);
                                                                    if (v0 != 0) {
                                                                        // 0x001b1234
                                                                        charge(ctx, 3);
                                                                        lw(a0, gp, f4::gpv::kFpcRequest);  // 0x7CE160
                                                                        if (a0 != 0) {
                                                                            // 0x001b124c
                                                                            charge(ctx, 4);
                                                                            jal(ctx, 0x1B124Cu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                                                                            if (v0 == 0) {
                                                                                // 0x001b1268
                                                                                charge(ctx, 1);
                                                                                v0 = 0;
                                                                            } else {
                                                                                // 0x001b125c
                                                                                charge(ctx, 3);
                                                                                v0 = 1;
                                                                            }
                                                                        } else {
                                                                            // 0x001b1240
                                                                            charge(ctx, 3);
                                                                            v0 = 1;
                                                                        }
                                                                        // 0x001b126c
                                                                        charge(ctx, 2);
                                                                        if (v0 != 0) {
                                                                            // 0x001b1280
                                                                            charge(ctx, 37);
                                                                            jal(ctx, 0x1B1280u, gen::fn_K_Field_Get_001b9120);
                                                                            lw(v1, v0, f4::fld::kPackCount);
                                                                            v1 = addiu(v1, -1);
                                                                            sw(v1, v0, f4::fld::kPackCount);
                                                                            jal(ctx, 0x1B1294u, gen::fn_K_Field_Get_001b9120);
                                                                            lw(v0, v0, f4::fld::kPackCount);
                                                                            s0 = sll(v0, 2);
                                                                            jal(ctx, 0x1B12A4u, gen::fn_K_Field_Get_001b9120);
                                                                            v0 = addu(v0, s0);
                                                                            lh(s1, v0, f4::fld::kPackMajor);
                                                                            jal(ctx, 0x1B12B4u, gen::fn_K_Field_Get_001b9120);
                                                                            lw(v0, v0, f4::fld::kPackCount);
                                                                            s0 = sll(v0, 2);
                                                                            jal(ctx, 0x1B12C4u, gen::fn_K_Field_Get_001b9120);
                                                                            v0 = addu(v0, s0);
                                                                            lh(a1, v0, f4::fld::kPackMinor);
                                                                            a0 = s1;
                                                                            jal(ctx, 0x1B12D8u, gen::fn_sub_1B2780_001b2780);
                                                                            s1 = v0;
                                                                            jal(ctx, 0x1B12E4u, gen::fn_K_Field_Get_001b9120);
                                                                            lw(v0, v0, f4::fld::kResCount);
                                                                            s0 = sll(v0, 2);
                                                                            jal(ctx, 0x1B12F4u, gen::fn_K_Field_Get_001b9120);
                                                                            v0 = addu(v0, s0);
                                                                            sw(s1, v0, f4::fld::kRes);
                                                                            s0 = 1;
                                                                            jal(ctx, 0x1B1308u, gen::fn_K_Field_Get_001b9120);
                                                                            sw(s0, v0, f4::fld::kLoadStep);
                                                                            goto L_001b1314;
                                                                        }
                                                                        // 0x001b1274
                                                                        charge(ctx, 3);
                                                                        v0 = 0;
                                                                    } else {
                                                                        // 0x001b1228
                                                                        charge(ctx, 3);
                                                                        v0 = 0;
                                                                    }
                                                                } else {
                                                                    // 0x001b11e4
                                                                    charge(ctx, 2);
                                                                L_001b2754:
                                                                    charge(ctx, 1);
                                                                    v0 = 0;
                                                                }
                                                                // 0x001b2758 (the shared epilogue, written out on this path)
                                                                charge(ctx, 10);
                                                                ld(ra, sp, 0x60);
                                                                lq(s5, sp, 0x50);
                                                                lq(s4, sp, 0x40);
                                                                lq(s3, sp, 0x30);
                                                                lq(s2, sp, 0x20);
                                                                lq(s1, sp, 0x10);
                                                                lq(s0, sp, 0x0);
                                                                sp = addiu(sp, 0xE0);
                                                                return;
                                                            }
                                                        L_001b1314:
                                                            charge(ctx, 12);
                                                            jal(ctx, 0x1B1314u, gen::fn_K_Field_Get_001b9120);
                                                            lw(v0, v0, f4::fld::kResCount);
                                                            s0 = sll(v0, 2);
                                                            jal(ctx, 0x1B1324u, gen::fn_K_Field_Get_001b9120);
                                                            v0 = addu(v0, s0);
                                                            lw(a0, v0, f4::fld::kRes);
                                                            jal(ctx, 0x1B1334u, gen::fn_sub_1B2B30_001b2b30);
                                                            if (v0 != 0) {
                                                                // 0x001b1350
                                                                charge(ctx, 14);
                                                                jal(ctx, 0x1B1350u, gen::fn_K_Field_Get_001b9120);
                                                                lw(v0, v0, f4::fld::kResCount);
                                                                s0 = sll(v0, 2);
                                                                jal(ctx, 0x1B1360u, gen::fn_K_Field_Get_001b9120);
                                                                v0 = addu(v0, s0);
                                                                lw(a0, v0, f4::fld::kRes);
                                                                jal(ctx, 0x1B1370u, gen::fn_sub_1B2B90_001b2b90);
                                                                s0 = 2;
                                                                jal(ctx, 0x1B137Cu, gen::fn_K_Field_Get_001b9120);
                                                                sw(s0, v0, f4::fld::kLoadStep);
                                                                goto L_001b1388;
                                                            }
                                                            // 0x001b1344
                                                            charge(ctx, 3);
                                                            v0 = 0;
                                                            // 0x001b2758 (the shared epilogue, written out on this path)
                                                            charge(ctx, 10);
                                                            ld(ra, sp, 0x60);
                                                            lq(s5, sp, 0x50);
                                                            lq(s4, sp, 0x40);
                                                            lq(s3, sp, 0x30);
                                                            lq(s2, sp, 0x20);
                                                            lq(s1, sp, 0x10);
                                                            lq(s0, sp, 0x0);
                                                            sp = addiu(sp, 0xE0);
                                                            return;
                                                        }
                                                    L_001b1388:
                                                        charge(ctx, 12);
                                                        jal(ctx, 0x1B1388u, gen::fn_K_Field_Get_001b9120);
                                                        lw(v0, v0, f4::fld::kResCount);
                                                        s0 = sll(v0, 2);
                                                        jal(ctx, 0x1B1398u, gen::fn_K_Field_Get_001b9120);
                                                        v0 = addu(v0, s0);
                                                        lw(a0, v0, f4::fld::kRes);
                                                        jal(ctx, 0x1B13A8u, gen::fn_sub_1B2F00_001b2f00);
                                                        if (v0 != 0) {
                                                            // 0x001b13c4
                                                            charge(ctx, 10);
                                                            jal(ctx, 0x1B13C4u, gen::fn_K_Field_Get_001b9120);
                                                            lw(v1, v0, f4::fld::kResCount);
                                                            v1 = addiu(v1, 1);
                                                            sw(v1, v0, f4::fld::kResCount);
                                                            jal(ctx, 0x1B13D8u, gen::fn_K_Field_Get_001b9120);
                                                            lw(v0, v0, f4::fld::kPackCount);
                                                            if (i64(v0) <= 0) {
                                                                // 0x001b1404
                                                                charge(ctx, 6);
                                                                lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                                                lw(v1, v0, f4::scene::kFlags);
                                                                v0 = lui(0x8000);
                                                                v0 = v1 & v0;
                                                                if (v0 != 0) {
                                                                    // 0x001b141c
                                                                    charge(ctx, 12);
                                                                    jal(ctx, 0x1B141Cu, gen::fn_K_Field_Get_001b9120);
                                                                    lw(v0, v0, f4::fld::kRes);
                                                                    lh(v1, v0, 4);
                                                                    lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                                                    sw(v1, v0, f4::scene::kMajor);
                                                                    jal(ctx, 0x1B1434u, gen::fn_K_Field_Get_001b9120);
                                                                    lw(v0, v0, f4::fld::kRes);
                                                                    lh(v1, v0, 6);
                                                                    lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                                                    sw(v1, v0, f4::scene::kMinor);
                                                                }
                                                                // 0x001b144c
                                                                charge(ctx, 3);
                                                                s0 = 0;
                                                                for (;;) {
                                                                    // 0x001b1478
                                                                    charge(ctx, 6);
                                                                    jal(ctx, 0x1B1478u, gen::fn_K_Field_Get_001b9120);
                                                                    lw(v0, v0, f4::fld::kResCount);
                                                                    v0 = slt(s0, v0);
                                                                    if (v0 == 0) {
                                                                        break;
                                                                    }
                                                                    backedge(ctx);
                                                                    // 0x001b1458
                                                                    charge(ctx, 8);
                                                                    jal(ctx, 0x1B1458u, gen::fn_K_Field_Get_001b9120);
                                                                    v1 = sll(s0, 2);
                                                                    v0 = addu(v0, v1);
                                                                    lw(a0, v0, f4::fld::kRes);
                                                                    jal(ctx, 0x1B146Cu, gen::fn_sub_1B3480_001b3480);
                                                                    s0 = addiu(s0, 1);
                                                                }
                                                                // 0x001b1490
                                                                charge(ctx, 4);
                                                                s0 = 3;
                                                                jal(ctx, 0x1B1494u, gen::fn_K_Field_Get_001b9120);
                                                                sw(s0, v0, f4::fld::kLoadStep);
                                                                goto L_001b14a0;
                                                            }
                                                            // 0x001b13ec
                                                            charge(ctx, 6);
                                                            jal(ctx, 0x1B13ECu, gen::fn_K_Field_Get_001b9120);
                                                            sw(zero, v0, f4::fld::kLoadStep);
                                                            v0 = 0;
                                                        } else {
                                                            // 0x001b13b8
                                                            charge(ctx, 3);
                                                            v0 = 0;
                                                        }
                                                        // 0x001b2758 (the shared epilogue, written out on this path)
                                                        charge(ctx, 10);
                                                        ld(ra, sp, 0x60);
                                                        lq(s5, sp, 0x50);
                                                        lq(s4, sp, 0x40);
                                                        lq(s3, sp, 0x30);
                                                        lq(s2, sp, 0x20);
                                                        lq(s1, sp, 0x10);
                                                        lq(s0, sp, 0x0);
                                                        sp = addiu(sp, 0xE0);
                                                        return;
                                                    }
                                                L_001b14a0:
                                                    charge(ctx, 4);
                                                    s1 = 0;
                                                    s0 = 0;
                                                    for (;;) {
                                                        // 0x001b14dc
                                                        charge(ctx, 6);
                                                        jal(ctx, 0x1B14DCu, gen::fn_K_Field_Get_001b9120);
                                                        lw(v0, v0, f4::fld::kResCount);
                                                        v0 = slt(s0, v0);
                                                        if (v0 == 0) {
                                                            break;
                                                        }
                                                        backedge(ctx);
                                                        // 0x001b14b0
                                                        charge(ctx, 9);
                                                        jal(ctx, 0x1B14B0u, gen::fn_K_Field_Get_001b9120);
                                                        v1 = sll(s0, 2);
                                                        v0 = addu(v0, v1);
                                                        lw(a0, v0, f4::fld::kRes);
                                                        jal(ctx, 0x1B14C4u, gen::fn_sub_1B39E0_001b39e0);
                                                        if (v0 == 0) {
                                                            // 0x001b14d4
                                                            charge(ctx, 1);
                                                            s1 = addiu(s1, 1);
                                                        }
                                                        // 0x001b14d8
                                                        charge(ctx, 1);
                                                        s0 = addiu(s0, 1);
                                                    }
                                                    // 0x001b14f4
                                                    charge(ctx, 2);
                                                    if (s1 == 0) {
                                                        // 0x001b1508
                                                        charge(ctx, 3);
                                                        lw(a0, gp, f4::gpv::kFpcRequest);  // 0x7CE160
                                                        if (a0 != 0) {
                                                            // 0x001b1514
                                                            charge(ctx, 3);
                                                            jal(ctx, 0x1B1514u, gen::fn_H_Cdvd_Destroy_00100ec0);
                                                            sw(zero, gp, f4::gpv::kFpcRequest);  // 0x7CE160
                                                        }
                                                        // 0x001b1520
                                                        charge(ctx, 4);
                                                        s0 = 4;
                                                        jal(ctx, 0x1B1524u, gen::fn_K_Field_Get_001b9120);
                                                        sw(s0, v0, f4::fld::kLoadStep);
                                                        goto L_001b1530;
                                                    }
                                                    // 0x001b14fc
                                                    charge(ctx, 3);
                                                    v0 = 0;
                                                    // 0x001b2758 (the shared epilogue, written out on this path)
                                                    charge(ctx, 10);
                                                    ld(ra, sp, 0x60);
                                                    lq(s5, sp, 0x50);
                                                    lq(s4, sp, 0x40);
                                                    lq(s3, sp, 0x30);
                                                    lq(s2, sp, 0x20);
                                                    lq(s1, sp, 0x10);
                                                    lq(s0, sp, 0x0);
                                                    sp = addiu(sp, 0xE0);
                                                    return;
                                                }
                                            L_001b1530:
                                                charge(ctx, 5);
                                                jal(ctx, 0x1B1530u, gen::fn_K_Field_Get_001b9120);
                                                lw(v0, v0, f4::fld::kFloorObj1);
                                                if (v0 != 0) {
                                                    // 0x001b1544
                                                    charge(ctx, 7);
                                                    jal(ctx, 0x1B1544u, gen::fn_K_Field_Get_001b9120);
                                                    lw(a0, v0, f4::fld::kFloorObj1);
                                                    jal(ctx, 0x1B1550u, gen::fn_sub_316F70_00316f70);
                                                    if (v0 != 0) {
                                                        goto L_001b156c;
                                                    }
                                                    // 0x001b1560
                                                    charge(ctx, 3);
                                                    v0 = 0;
                                                    // 0x001b2758 (the shared epilogue, written out on this path)
                                                    charge(ctx, 10);
                                                    ld(ra, sp, 0x60);
                                                    lq(s5, sp, 0x50);
                                                    lq(s4, sp, 0x40);
                                                    lq(s3, sp, 0x30);
                                                    lq(s2, sp, 0x20);
                                                    lq(s1, sp, 0x10);
                                                    lq(s0, sp, 0x0);
                                                    sp = addiu(sp, 0xE0);
                                                    return;
                                                }
                                            L_001b156c:
                                                charge(ctx, 5);
                                                jal(ctx, 0x1B156Cu, gen::fn_K_Field_Get_001b9120);
                                                lw(v0, v0, f4::fld::kFloorObj2);
                                                if (v0 != 0) {
                                                    // 0x001b1580
                                                    charge(ctx, 7);
                                                    jal(ctx, 0x1B1580u, gen::fn_K_Field_Get_001b9120);
                                                    lw(a0, v0, f4::fld::kFloorObj2);
                                                    jal(ctx, 0x1B158Cu, gen::fn_sub_316F70_00316f70);
                                                    if (v0 != 0) {
                                                        goto L_001b15a8;
                                                    }
                                                    // 0x001b159c
                                                    charge(ctx, 3);
                                                    v0 = 0;
                                                    // 0x001b2758 (the shared epilogue, written out on this path)
                                                    charge(ctx, 10);
                                                    ld(ra, sp, 0x60);
                                                    lq(s5, sp, 0x50);
                                                    lq(s4, sp, 0x40);
                                                    lq(s3, sp, 0x30);
                                                    lq(s2, sp, 0x20);
                                                    lq(s1, sp, 0x10);
                                                    lq(s0, sp, 0x0);
                                                    sp = addiu(sp, 0xE0);
                                                    return;
                                                }
                                            L_001b15a8:
                                                charge(ctx, 9);
                                                lw(v1, gp, f4::gpv::kFrameCounter);  // 0x7CDEAC
                                                lw(v0, gp, f4::gpv::kLoadTime);  // 0x7CE164
                                                v1 = subu(v1, v0);
                                                sw(v1, gp, f4::gpv::kLoadTime);  // 0x7CE164
                                                lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                                lw(v0, v0, f4::scene::kMajor);
                                                at = slti(v0, 200);
                                                if (at != 0) {
                                                    // 0x001b15cc
                                                    charge(ctx, 4);
                                                    v0 = 0x30000;
                                                    v0 = v0 | 0x2000;
                                                    v0 = addu(v1, v0);
                                                    sw(v0, gp, f4::gpv::kLoadTime);  // 0x7CE164
                                                }
                                                // 0x001b15dc
                                                charge(ctx, 16);
                                                jal(ctx, 0x1B15DCu, gen::fn_sub_1B8160_001b8160);
                                                v1 = 0x860000;
                                                sw(v0, v1, 32504);  // 0x867EF8
                                                jal(ctx, 0x1B15ECu, gen::fn_sub_1B8680_001b8680);
                                                v1 = 0x860000;
                                                sw(v0, v1, 32508);  // 0x867EFC
                                                jal(ctx, 0x1B15FCu, gen::fn_sub_1B88D0_001b88d0);
                                                v1 = 0x860000;
                                                sw(v0, v1, 32512);  // 0x867F00
                                                s0 = 5;
                                                jal(ctx, 0x1B1610u, gen::fn_K_Field_Get_001b9120);
                                                sw(s0, v0, f4::fld::kLoadStep);
                                            }
                                            // 0x001b161c
                                            charge(ctx, 6);
                                            v0 = 0x860000;
                                            lw(a0, v0, 32504);  // 0x867EF8
                                            jal(ctx, 0x1B1624u, gen::fn_sub_1B81F0_001b81f0);
                                            if (v0 != 0) {
                                                // 0x001b1640
                                                charge(ctx, 8);
                                                v0 = 0x860000;
                                                sw(zero, v0, 32504);  // 0x867EF8
                                                v0 = 0x860000;
                                                lw(a0, v0, 32508);  // 0x867EFC
                                                jal(ctx, 0x1B1650u, gen::fn_sub_1B8710_001b8710);
                                                if (v0 != 0) {
                                                    // 0x001b166c
                                                    charge(ctx, 8);
                                                    v0 = 0x860000;
                                                    sw(zero, v0, 32508);  // 0x867EFC
                                                    v0 = 0x860000;
                                                    lw(a0, v0, 32512);  // 0x867F00
                                                    jal(ctx, 0x1B167Cu, gen::fn_sub_1B8960_001b8960);
                                                    if (v0 != 0) {
                                                        // 0x001b1698
                                                        charge(ctx, 7);
                                                        v0 = 0x860000;
                                                        sw(zero, v0, 32512);  // 0x867F00
                                                        jal(ctx, 0x1B16A0u, gen::fn_sub_1A02C0_001a02c0);
                                                        v1 = 1;
                                                        if (v0 != v1) {
                                                            // 0x001b16e8
                                                            charge(ctx, 3);
                                                            s2 = 0;
                                                            for (;;) {
                                                                // 0x001b1750
                                                                charge(ctx, 6);
                                                                jal(ctx, 0x1B1750u, gen::fn_K_Field_Get_001b9120);
                                                                lw(v0, v0, f4::fld::kResCount);
                                                                v0 = slt(s2, v0);
                                                                if (v0 == 0) {
                                                                    break;
                                                                }
                                                                backedge(ctx);
                                                                // 0x001b16f4
                                                                charge(ctx, 23);
                                                                s1 = sll(s2, 2);
                                                                jal(ctx, 0x1B16F8u, gen::fn_K_Field_Get_001b9120);
                                                                v0 = addu(v0, s1);
                                                                lw(v0, v0, f4::fld::kRes);
                                                                lhu(s0, v0, 4);
                                                                jal(ctx, 0x1B170Cu, gen::fn_K_Field_Get_001b9120);
                                                                v0 = addu(v0, s1);
                                                                lw(v0, v0, f4::fld::kRes);
                                                                lhu(a1, v0, 6);
                                                                lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                                                a0 = s0;
                                                                lh(a2, v0, f4::scene::kNpcSet);
                                                                jal(ctx, 0x1B172Cu, gen::fn_sub_1E2DA0_001e2da0);
                                                                s0 = v0;
                                                                jal(ctx, 0x1B1738u, gen::fn_K_Field_Get_001b9120);
                                                                v0 = addu(v0, s1);
                                                                lw(v0, v0, f4::fld::kRes);
                                                                sw(s0, v0, 2628);
                                                                s2 = addiu(s2, 1);
                                                            }
                                                        } else {
                                                            // 0x001b16b4
                                                            charge(ctx, 13);
                                                            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                                            lhu(a0, v0, f4::scene::kMajor);
                                                            lhu(a1, v0, f4::scene::kMinor);
                                                            lh(a2, v0, f4::scene::kNpcSet);
                                                            jal(ctx, 0x1B16C4u, gen::fn_sub_1E2DA0_001e2da0);
                                                            s0 = v0;
                                                            jal(ctx, 0x1B16D0u, gen::fn_K_Field_Get_001b9120);
                                                            lw(v0, v0, f4::fld::kRes);
                                                            sw(s0, v0, 2628);
                                                        }
                                                        // 0x001b1768
                                                        charge(ctx, 4);
                                                        s0 = 6;
                                                        jal(ctx, 0x1B176Cu, gen::fn_K_Field_Get_001b9120);
                                                        sw(s0, v0, f4::fld::kLoadStep);
                                                        goto L_001b1778;
                                                    }
                                                    // 0x001b168c
                                                    charge(ctx, 3);
                                                    v0 = 0;
                                                } else {
                                                    // 0x001b1660
                                                    charge(ctx, 3);
                                                    v0 = 0;
                                                }
                                            } else {
                                                // 0x001b1634
                                                charge(ctx, 3);
                                                v0 = 0;
                                            }
                                            // 0x001b2758 (the shared epilogue, written out on this path)
                                            charge(ctx, 10);
                                            ld(ra, sp, 0x60);
                                            lq(s5, sp, 0x50);
                                            lq(s4, sp, 0x40);
                                            lq(s3, sp, 0x30);
                                            lq(s2, sp, 0x20);
                                            lq(s1, sp, 0x10);
                                            lq(s0, sp, 0x0);
                                            sp = addiu(sp, 0xE0);
                                            return;
                                        }
                                    L_001b1778:
                                        charge(ctx, 6);
                                        s3 = 0;
                                        jal(ctx, 0x1B177Cu, gen::fn_sub_1A02C0_001a02c0);
                                        v1 = 1;
                                        if (v0 != v1) {
                                            // 0x001b17dc
                                            charge(ctx, 3);
                                            s4 = 0;
                                            for (;;) {
                                                // 0x001b1860
                                                charge(ctx, 6);
                                                jal(ctx, 0x1B1860u, gen::fn_K_Field_Get_001b9120);
                                                lw(v0, v0, f4::fld::kResCount);
                                                v0 = slt(s4, v0);
                                                if (v0 == 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                                // 0x001b17e8
                                                charge(ctx, 28);
                                                s2 = sll(s4, 2);
                                                jal(ctx, 0x1B17ECu, gen::fn_K_Field_Get_001b9120);
                                                v0 = addu(v0, s2);
                                                lw(s1, v0, f4::fld::kRes);
                                                jal(ctx, 0x1B17FCu, gen::fn_K_Field_Get_001b9120);
                                                v0 = addu(v0, s2);
                                                lw(s0, v0, f4::fld::kRes);
                                                jal(ctx, 0x1B180Cu, gen::fn_K_Field_Get_001b9120);
                                                v0 = addu(v0, s2);
                                                lw(v0, v0, f4::fld::kRes);
                                                lhu(s5, v0, 4);
                                                jal(ctx, 0x1B1820u, gen::fn_K_Field_Get_001b9120);
                                                v0 = addu(v0, s2);
                                                lw(v0, v0, f4::fld::kRes);
                                                lhu(a3, v0, 6);
                                                lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                                lw(a0, s1, 2628);
                                                a1 = addiu(s0, 2632);
                                                a2 = s5;
                                                lh(t0, v0, f4::scene::kNpcSet);
                                                jal(ctx, 0x1B1848u, gen::fn_sub_1E2E50_001e2e50);
                                                if (v0 == 0) {
                                                    // 0x001b1858
                                                    charge(ctx, 1);
                                                    s3 = addiu(s3, 1);
                                                }
                                                // 0x001b185c
                                                charge(ctx, 1);
                                                s4 = addiu(s4, 1);
                                            }
                                        } else {
                                            // 0x001b1790
                                            charge(ctx, 16);
                                            lw(s1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                            jal(ctx, 0x1B1794u, gen::fn_K_Field_Get_001b9120);
                                            lw(s0, v0, f4::fld::kRes);
                                            jal(ctx, 0x1B17A0u, gen::fn_K_Field_Get_001b9120);
                                            lw(v0, v0, f4::fld::kRes);
                                            lhu(a2, s1, f4::scene::kMajor);
                                            lhu(a3, s1, f4::scene::kMinor);
                                            lw(a0, s0, 2628);
                                            a1 = addiu(v0, 2632);
                                            lh(t0, s1, f4::scene::kNpcSet);
                                            jal(ctx, 0x1B17C0u, gen::fn_sub_1E2E50_001e2e50);
                                            if (v0 == 0) {
                                                // 0x001b17d0
                                                charge(ctx, 3);
                                                s3 = addiu(s3, 1);
                                            }
                                        }
                                        // 0x001b1878
                                        charge(ctx, 2);
                                        if (s3 == 0) {
                                            // 0x001b188c
                                            charge(ctx, 4);
                                            s0 = 7;
                                            jal(ctx, 0x1B1890u, gen::fn_K_Field_Get_001b9120);
                                            sw(s0, v0, f4::fld::kLoadStep);
                                            goto L_001b189c;
                                        }
                                        // 0x001b1880
                                        charge(ctx, 3);
                                        v0 = 0;
                                        // 0x001b2758 (the shared epilogue, written out on this path)
                                        charge(ctx, 10);
                                        ld(ra, sp, 0x60);
                                        lq(s5, sp, 0x50);
                                        lq(s4, sp, 0x40);
                                        lq(s3, sp, 0x30);
                                        lq(s2, sp, 0x20);
                                        lq(s1, sp, 0x10);
                                        lq(s0, sp, 0x0);
                                        sp = addiu(sp, 0xE0);
                                        return;
                                    }
                                L_001b189c:
                                    charge(ctx, 6);
                                    s2 = 0;
                                    lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                    lw(v1, v0, f4::scene::kMajor);
                                    v0 = slti(v1, 51);
                                    if (v0 == 0) {
                                        // 0x001b18b4
                                        charge(ctx, 3);
                                        at = slti(v1, 59);
                                        if (at == 0) {
                                            goto L_001b18c0;
                                        }
                                    L_001b18d8:
                                        charge(ctx, 5);
                                        lw(a0, gp, f4::gpv::kFloorObj0);  // 0x7CE280
                                        jal(ctx, 0x1B18DCu, gen::fn_sub_316F70_00316f70);
                                        if (v0 == 0) {
                                            // 0x001b18ec
                                            charge(ctx, 1);
                                            s2 = addiu(s2, 1);
                                        }
                                        goto L_001b18f0;
                                    }
                                L_001b18c0:
                                    charge(ctx, 3);
                                    v0 = slti(v1, 71);
                                    if (v0 == 0) {
                                        // 0x001b18cc
                                        charge(ctx, 3);
                                        at = slti(v1, 79);
                                        if (at != 0) {
                                            goto L_001b18d8;
                                        }
                                    }
                                L_001b18f0:
                                    charge(ctx, 7);
                                    jal(ctx, 0x1B18F0u, gen::fn_K_Field_Get_001b9120);
                                    lw(a0, v0, f4::fld::kMapFile);
                                    jal(ctx, 0x1B18FCu, gen::fn_sub_1E74E0_001e74e0);
                                    if (v0 == 0) {
                                        // 0x001b190c
                                        charge(ctx, 1);
                                        s2 = addiu(s2, 1);
                                    }
                                    // 0x001b1910
                                    charge(ctx, 3);
                                    s3 = 0;
                                    for (;;) {
                                        // 0x001b197c
                                        charge(ctx, 6);
                                        jal(ctx, 0x1B197Cu, gen::fn_K_Field_Get_001b9120);
                                        lw(v0, v0, f4::fld::kResCount);
                                        v0 = slt(s3, v0);
                                        if (v0 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                        // 0x001b191c
                                        charge(ctx, 15);
                                        s1 = sll(s3, 2);
                                        jal(ctx, 0x1B1920u, gen::fn_K_Field_Get_001b9120);
                                        v0 = addu(v0, s1);
                                        lw(s0, v0, f4::fld::kRes);
                                        jal(ctx, 0x1B1930u, gen::fn_K_Field_Get_001b9120);
                                        v0 = addu(v0, s1);
                                        lw(v0, v0, f4::fld::kRes);
                                        lw(a0, s0, 2628);
                                        lw(a1, v0, 2632);
                                        jal(ctx, 0x1B1948u, gen::fn_sub_1E3940_001e3940);
                                        if (v0 != 0) {
                                            // 0x001b1964
                                            charge(ctx, 5);
                                            jal(ctx, 0x1B1964u, gen::fn_K_Field_Get_001b9120);
                                            v0 = addu(v0, s1);
                                            lw(v0, v0, f4::fld::kRes);
                                            sw(zero, v0, 2628);
                                        } else {
                                            // 0x001b1958
                                            charge(ctx, 3);
                                            s2 = addiu(s2, 1);
                                        }
                                        // 0x001b1978
                                        charge(ctx, 1);
                                        s3 = addiu(s3, 1);
                                    }
                                    // 0x001b1994
                                    charge(ctx, 2);
                                    if (s2 == 0) {
                                        // 0x001b19a8
                                        charge(ctx, 3);
                                        s1 = 0;
                                        for (;;) {
                                            // 0x001b1a24
                                            charge(ctx, 6);
                                            jal(ctx, 0x1B1A24u, gen::fn_K_Field_Get_001b9120);
                                            lw(v0, v0, f4::fld::kResCount);
                                            v0 = slt(s1, v0);
                                            if (v0 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                            // 0x001b19b4
                                            charge(ctx, 8);
                                            s0 = sll(s1, 2);
                                            jal(ctx, 0x1B19B8u, gen::fn_K_Field_Get_001b9120);
                                            v0 = addu(v0, s0);
                                            lw(v0, v0, f4::fld::kRes);
                                            lw(v0, v0, 2620);
                                            if (v0 == 0) {
                                                // 0x001b19d4
                                                charge(ctx, 19);
                                                jal(ctx, 0x1B19D4u, gen::fn_K_Field_Get_001b9120);
                                                v0 = addu(v0, s0);
                                                lw(v0, v0, f4::fld::kRes);
                                                lhu(s2, v0, 4);
                                                jal(ctx, 0x1B19E8u, gen::fn_K_Field_Get_001b9120);
                                                v0 = addu(v0, s0);
                                                lw(v0, v0, f4::fld::kRes);
                                                lhu(a1, v0, 6);
                                                a0 = s2;
                                                jal(ctx, 0x1B1A00u, gen::fn_sub_1E6CB0_001e6cb0);
                                                s2 = v0;
                                                jal(ctx, 0x1B1A0Cu, gen::fn_K_Field_Get_001b9120);
                                                v0 = addu(v0, s0);
                                                lw(v0, v0, f4::fld::kRes);
                                                sw(s2, v0, 2616);
                                            }
                                            // 0x001b1a20
                                            charge(ctx, 1);
                                            s1 = addiu(s1, 1);
                                        }
                                        // 0x001b1a3c
                                        charge(ctx, 5);
                                        lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                        lw(v1, v0, f4::scene::kMajor);
                                        v0 = slti(v1, 51);
                                        if (v0 == 0) {
                                            // 0x001b1a50
                                            charge(ctx, 3);
                                            at = slti(v1, 59);
                                            if (at == 0) {
                                                goto L_001b1a5c;
                                            }
                                        L_001b1a74:
                                            charge(ctx, 25);
                                            jal(ctx, 0x1B1A74u, gen::fn_K_Field_Get_001b9120);
                                            lw(v0, v0, f4::fld::kMapFile);
                                            lw(s0, v0, 272);
                                            jal(ctx, 0x1B1A84u, gen::fn_K_Field_Get_001b9120);
                                            a0 = addiu(v0, f4::fld::kGrid);
                                            a1 = addiu(s0, 4);
                                            a2 = 4096;
                                            jal(ctx, 0x1B1A98u, gen::fn_memcpy_00521250);
                                            jal(ctx, 0x1B1AA0u, gen::fn_K_Field_Get_001b9120);
                                            lw(a0, v0, f4::fld::kMapFile);
                                            jal(ctx, 0x1B1AACu, gen::fn_sub_1E7520_001e7520);
                                            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                            lhu(a0, v0, f4::scene::kMajor);
                                            lhu(a1, v0, f4::scene::kMinor);
                                            jal(ctx, 0x1B1AC0u, gen::fn_sub_1E6CB0_001e6cb0);
                                            s0 = v0;
                                            jal(ctx, 0x1B1ACCu, gen::fn_K_Field_Get_001b9120);
                                            sw(s0, v0, f4::fld::kMapFile);
                                            goto L_001b1ad8;
                                        }
                                    L_001b1a5c:
                                        charge(ctx, 3);
                                        v0 = slti(v1, 71);
                                        if (v0 == 0) {
                                            // 0x001b1a68
                                            charge(ctx, 3);
                                            at = slti(v1, 79);
                                            if (at != 0) {
                                                goto L_001b1a74;
                                            }
                                        }
                                    L_001b1ad8:
                                        charge(ctx, 4);
                                        s0 = 8;
                                        jal(ctx, 0x1B1ADCu, gen::fn_K_Field_Get_001b9120);
                                        sw(s0, v0, f4::fld::kLoadStep);
                                        goto L_001b1ae8;
                                    }
                                    // 0x001b199c
                                    charge(ctx, 3);
                                    v0 = 0;
                                    // 0x001b2758 (the shared epilogue, written out on this path)
                                    charge(ctx, 10);
                                    ld(ra, sp, 0x60);
                                    lq(s5, sp, 0x50);
                                    lq(s4, sp, 0x40);
                                    lq(s3, sp, 0x30);
                                    lq(s2, sp, 0x20);
                                    lq(s1, sp, 0x10);
                                    lq(s0, sp, 0x0);
                                    sp = addiu(sp, 0xE0);
                                    return;
                                }
                            L_001b1ae8:
                                charge(ctx, 5);
                                lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                lw(v1, v0, f4::scene::kMajor);
                                v0 = slti(v1, 51);
                                if (v0 == 0) {
                                    // 0x001b1afc
                                    charge(ctx, 3);
                                    at = slti(v1, 59);
                                    if (at == 0) {
                                        goto L_001b1b08;
                                    }
                                L_001b1b20:
                                    charge(ctx, 3);
                                    s4 = 0;
                                    for (;;) {
                                        // 0x001b1bb8
                                        charge(ctx, 6);
                                        jal(ctx, 0x1B1BB8u, gen::fn_K_Field_Get_001b9120);
                                        lw(v0, v0, f4::fld::kResCount);
                                        v0 = slt(s4, v0);
                                        if (v0 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                        // 0x001b1b2c
                                        charge(ctx, 26);
                                        s3 = sll(s4, 2);
                                        jal(ctx, 0x1B1B30u, gen::fn_K_Field_Get_001b9120);
                                        v0 = addu(v0, s3);
                                        lw(s2, v0, f4::fld::kRes);
                                        jal(ctx, 0x1B1B40u, gen::fn_K_Field_Get_001b9120);
                                        v0 = addu(v0, s3);
                                        lw(s1, v0, f4::fld::kRes);
                                        jal(ctx, 0x1B1B50u, gen::fn_K_Field_Get_001b9120);
                                        v0 = addu(v0, s3);
                                        lw(v0, v0, f4::fld::kRes);
                                        lhu(s0, v0, 4);
                                        jal(ctx, 0x1B1B64u, gen::fn_K_Field_Get_001b9120);
                                        v0 = addu(v0, s3);
                                        lw(v0, v0, f4::fld::kRes);
                                        lhu(a3, v0, 6);
                                        lw(a0, s2, 2616);
                                        a1 = addiu(s1, 2620);
                                        a2 = s0;
                                        jal(ctx, 0x1B1B84u, gen::fn_sub_1E6D50_001e6d50);
                                        if (v0 == 0) {
                                            goto L_001b1b94_121;
                                        }
                                        // 0x001b1ba0
                                        charge(ctx, 6);
                                        jal(ctx, 0x1B1BA0u, gen::fn_K_Field_Get_001b9120);
                                        v0 = addu(v0, s3);
                                        lw(v0, v0, f4::fld::kRes);
                                        sw(zero, v0, 2616);
                                        s4 = addiu(s4, 1);
                                    }
                                    // 0x001b1bd0
                                    charge(ctx, 11);
                                    lw(s0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                    jal(ctx, 0x1B1BD4u, gen::fn_K_Field_Get_001b9120);
                                    lhu(a2, s0, f4::scene::kMajor);
                                    lhu(a3, s0, f4::scene::kMinor);
                                    lw(a0, v0, f4::fld::kMapFile);
                                    a1 = addiu(sp, 0xDC);
                                    jal(ctx, 0x1B1BECu, gen::fn_sub_1E6D50_001e6d50);
                                    if (v0 != 0) {
                                        // 0x001b1c08
                                        charge(ctx, 3);
                                        lw(a0, sp, 0xDC);
                                        if (a0 != 0) {
                                            // 0x001b1c14
                                            charge(ctx, 12);
                                            jal(ctx, 0x1B1C14u, gen::fn_sub_1E6EA0_001e6ea0);
                                            lw(a0, sp, 0xDC);
                                            v0 = 0x960000;
                                            lw(v0, v0, 380);  // 0x96017C
                                            jalr(ctx, 0x1B1C28u, v0.u());
                                            jal(ctx, 0x1B1C30u, gen::fn_K_Field_Get_001b9120);
                                            sw(zero, v0, f4::fld::kMapFile);
                                        }
                                    L_001b1d50:
                                        charge(ctx, 5);
                                        jal(ctx, 0x1B1D50u, gen::fn_K_Scene_IsRandomFloor_001a0250);
                                        v1 = 1;
                                        if (v0 != v1) {
                                            // 0x001b1dfc
                                            charge(ctx, 5);
                                            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                            lw(v1, v0, f4::scene::kMajor);
                                            v0 = slti(v1, 51);
                                            if (v0 == 0) {
                                                // 0x001b1e10
                                                charge(ctx, 3);
                                                at = slti(v1, 59);
                                                if (at == 0) {
                                                    goto L_001b1e1c;
                                                }
                                            L_001b1e34:
                                                charge(ctx, 3);
                                                s0 = 0;
                                                for (;;) {
                                                    // 0x001b1e68
                                                    charge(ctx, 3);
                                                    v0 = slti(s0, 9);
                                                    if (v0 == 0) {
                                                        break;
                                                    }
                                                    backedge(ctx);
                                                    // 0x001b1e40
                                                    charge(ctx, 10);
                                                    s1 = sll(s0, 2);
                                                    jal(ctx, 0x1B1E44u, gen::fn_K_Field_Get_001b9120);
                                                    v0 = addu(v0, s1);
                                                    lw(v1, v0, f4::fld::kRes);
                                                    v0 = 0x870000;
                                                    v0 = addiu(v0, -16960);  // &0x86BDC0
                                                    v0 = addu(v0, s1);
                                                    sw(v1, v0, 0);
                                                    s0 = addiu(s0, 1);
                                                }
                                                // 0x001b1e74
                                                charge(ctx, 4);
                                                jal(ctx, 0x1B1E74u, gen::fn_sub_1BD8C0_001bd8c0);
                                                goto L_001b213c;
                                            }
                                        L_001b1e1c:
                                            charge(ctx, 3);
                                            v0 = slti(v1, 71);
                                            if (v0 == 0) {
                                                // 0x001b1e28
                                                charge(ctx, 3);
                                                at = slti(v1, 79);
                                                if (at == 0) {
                                                    goto L_001b1e84;
                                                }
                                                goto L_001b1e34;
                                            }
                                        L_001b1e84:
                                            charge(ctx, 9);
                                            jal(ctx, 0x1B1E84u, gen::fn_K_Field_Get_001b9120);
                                            a0 = 0;
                                            lw(a1, v0, f4::fld::kRes);
                                            jal(ctx, 0x1B1E94u, gen::fn_sub_3B6790_003b6790);
                                            s3 = 0;
                                            for (;;) {
                                                // 0x001b1ffc
                                                charge(ctx, 7);
                                                jal(ctx, 0x1B1FFCu, gen::fn_K_Field_Get_001b9120);
                                                lw(v0, v0, f4::fld::kRes);
                                                lw(v0, v0, 280);
                                                v0 = sltu(s3, v0);
                                                if (v0 == 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                                // 0x001b1ea8
                                                charge(ctx, 18);
                                                v0 = sll(s3, 1);
                                                v0 = addu(v0, s3);
                                                s2 = sll(v0, 3);
                                                jal(ctx, 0x1B1EB4u, gen::fn_K_Field_Get_001b9120);
                                                lw(v0, v0, f4::fld::kRes);
                                                v0 = addu(v0, s2);
                                                lw(a0, v0, 292);
                                                jal(ctx, 0x1B1EC8u, gen::fn_sub_4CB2F0_004cb2f0);
                                                s4 = v0;
                                                jal(ctx, 0x1B1ED4u, gen::fn_K_Field_Get_001b9120);
                                                lw(v0, v0, f4::fld::kRes);
                                                v0 = addu(v0, s2);
                                                lhu(v0, v0, 284);
                                                if (v0 != 0) {
                                                    // 0x001b1ef0
                                                    charge(ctx, 8);
                                                    jal(ctx, 0x1B1EF0u, gen::fn_K_Field_Get_001b9120);
                                                    lw(v0, v0, f4::fld::kRes);
                                                    v0 = addu(v0, s2);
                                                    lhu(v1, v0, 284);
                                                    v0 = 2;
                                                    if (v1 == v0) {
                                                        goto L_001b1f10;
                                                    }
                                                    goto L_001b1ff8;
                                                }
                                            L_001b1f10:
                                                charge(ctx, 18);
                                                v0 = sll(s3, 1);
                                                v0 = addu(v0, s3);
                                                s1 = sll(v0, 3);
                                                jal(ctx, 0x1B1F1Cu, gen::fn_K_Field_Get_001b9120);
                                                lw(v0, v0, f4::fld::kRes);
                                                s0 = addu(v0, s1);
                                                jal(ctx, 0x1B1F2Cu, gen::fn_K_Field_Get_001b9120);
                                                lw(v0, v0, f4::fld::kRes);
                                                v0 = addu(v0, s1);
                                                lhu(a0, s0, 288);
                                                lw(a1, v0, 296);
                                                jal(ctx, 0x1B1F44u, gen::fn_sub_3B65D0_003b65d0);
                                                s0 = v0 & 0xFFFF;
                                                if (s0 == 0) {
                                                    // 0x001b1f58
                                                    charge(ctx, 5);
                                                    a0 = 0x680000;
                                                    a0 = addiu(a0, -29192);  // "k_fldrc.c"
                                                    a1 = 740;
                                                    jal(ctx, 0x1B1F64u, gen::fn_sub_19D3F0_0019d3f0);
                                                }
                                                // 0x001b1f6c
                                                charge(ctx, 25);
                                                a0 = s4;
                                                jal(ctx, 0x1B1F70u, gen::fn_sub_1A5B30_001a5b30);
                                                swc1(f0, sp, 0xC0);
                                                a0 = s4;
                                                jal(ctx, 0x1B1F80u, gen::fn_sub_1A5AA0_001a5aa0);
                                                swc1(f0, sp, 0xC4);
                                                a0 = s4;
                                                jal(ctx, 0x1B1F90u, gen::fn_sub_1A5BC0_001a5bc0);
                                                swc1(f0, sp, 0xC8);
                                                a0 = s0;
                                                a1 = addiu(s4, 48);
                                                a2 = addiu(sp, 0xC0);
                                                jal(ctx, 0x1B1FA8u, gen::fn_sub_3B78B0_003b78b0);
                                                jal(ctx, 0x1B1FB0u, gen::fn_K_Field_Get_001b9120);
                                                lw(v0, v0, f4::fld::kRes);
                                                v0 = addu(v0, s2);
                                                lhu(v0, v0, 286);
                                                v0 = v0 & 0x2;
                                                if (v0 != 0) {
                                                    // 0x001b1fd0
                                                    charge(ctx, 5);
                                                    a0 = s0;
                                                    jal(ctx, 0x1B1FD4u, gen::fn_sub_3B5D10_003b5d10);
                                                    v1 = 1;
                                                    sw(v1, v0, 272);
                                                }
                                                // 0x001b1fe4
                                                charge(ctx, 5);
                                                jal(ctx, 0x1B1FE4u, gen::fn_K_Field_Get_001b9120);
                                                lw(v0, v0, f4::fld::kRes);
                                                v0 = addu(v0, s2);
                                                sw(zero, v0, 296);
                                            L_001b1ff8:
                                                charge(ctx, 1);
                                                s3 = addiu(s3, 1);
                                            }
                                            // 0x001b2018
                                            charge(ctx, 3);
                                            s3 = 0;
                                            for (;;) {
                                                // 0x001b20f8
                                                charge(ctx, 7);
                                                jal(ctx, 0x1B20F8u, gen::fn_K_Field_Get_001b9120);
                                                lw(v0, v0, f4::fld::kRes);
                                                lw(v0, v0, 280);
                                                v0 = sltu(s3, v0);
                                                if (v0 == 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                                // 0x001b2024
                                                charge(ctx, 18);
                                                v0 = sll(s3, 1);
                                                v0 = addu(v0, s3);
                                                s2 = sll(v0, 3);
                                                jal(ctx, 0x1B2030u, gen::fn_K_Field_Get_001b9120);
                                                lw(v0, v0, f4::fld::kRes);
                                                v0 = addu(v0, s2);
                                                lw(a0, v0, 292);
                                                jal(ctx, 0x1B2044u, gen::fn_sub_4CB2F0_004cb2f0);
                                                jal(ctx, 0x1B204Cu, gen::fn_K_Field_Get_001b9120);
                                                lw(v0, v0, f4::fld::kRes);
                                                v0 = addu(v0, s2);
                                                lhu(v1, v0, 284);
                                                v0 = 1;
                                                if (v1 == v0) {
                                                    // 0x001b206c
                                                    charge(ctx, 18);
                                                    v0 = sll(s3, 1);
                                                    v0 = addu(v0, s3);
                                                    s1 = sll(v0, 3);
                                                    jal(ctx, 0x1B2078u, gen::fn_K_Field_Get_001b9120);
                                                    lw(v0, v0, f4::fld::kRes);
                                                    s0 = addu(v0, s1);
                                                    jal(ctx, 0x1B2088u, gen::fn_K_Field_Get_001b9120);
                                                    lw(v0, v0, f4::fld::kRes);
                                                    v0 = addu(v0, s1);
                                                    lhu(a0, s0, 288);
                                                    lw(a1, v0, 300);
                                                    jal(ctx, 0x1B20A0u, gen::fn_sub_3B66B0_003b66b0);
                                                    s0 = v0 & 0xFFFF;
                                                    if (s0 == 0) {
                                                        // 0x001b20b4
                                                        charge(ctx, 5);
                                                        a0 = 0x680000;
                                                        a0 = addiu(a0, -29192);  // "k_fldrc.c"
                                                        a1 = 773;
                                                        jal(ctx, 0x1B20C0u, gen::fn_sub_19D3F0_0019d3f0);
                                                    }
                                                    // 0x001b20c8
                                                    charge(ctx, 11);
                                                    jal(ctx, 0x1B20C8u, gen::fn_K_Field_Get_001b9120);
                                                    lw(v0, v0, f4::fld::kRes);
                                                    v0 = addu(v0, s2);
                                                    sw(zero, v0, 300);
                                                    a0 = s0;
                                                    jal(ctx, 0x1B20E0u, gen::fn_sub_3B5D10_003b5d10);
                                                    lw(v1, v0, 40);
                                                    v1 = v1 | 0x2;
                                                    sw(v1, v0, 40);
                                                }
                                                // 0x001b20f4
                                                charge(ctx, 1);
                                                s3 = addiu(s3, 1);
                                            }
                                            // 0x001b2114
                                            charge(ctx, 10);
                                            jal(ctx, 0x1B2114u, gen::fn_K_Field_Get_001b9120);
                                            lw(v0, v0, f4::fld::kRes);
                                            sw(zero, v0, 280);
                                            jal(ctx, 0x1B2124u, gen::fn_sub_19FF10_0019ff10);
                                            a0 = 1;
                                            a1 = a0;
                                            jal(ctx, 0x1B2134u, gen::fn_sub_1A0040_001a0040);
                                        } else {
                                            // 0x001b1d64
                                            charge(ctx, 3);
                                            s0 = 0;
                                            for (;;) {
                                                // 0x001b1d98
                                                charge(ctx, 3);
                                                v0 = slti(s0, 9);
                                                if (v0 == 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                                // 0x001b1d70
                                                charge(ctx, 10);
                                                s1 = sll(s0, 2);
                                                jal(ctx, 0x1B1D74u, gen::fn_K_Field_Get_001b9120);
                                                v0 = addu(v0, s1);
                                                lw(v1, v0, f4::fld::kRes);
                                                v0 = 0x870000;
                                                v0 = addiu(v0, -16960);  // &0x86BDC0
                                                v0 = addu(v0, s1);
                                                sw(v1, v0, 0);
                                                s0 = addiu(s0, 1);
                                            }
                                            // 0x001b1da4
                                            charge(ctx, 4);
                                            jal(ctx, 0x1B1DA4u, gen::fn_sub_17D800_0017d800);
                                            if (v0 != 0) {
                                                // 0x001b1dd4
                                                charge(ctx, 6);
                                                lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                                lw(v0, v0, f4::scene::kMajor);
                                                a0 = addiu(v0, -40);
                                                a1 = 1;
                                                jal(ctx, 0x1B1DE4u, gen::fn_sub_1BD450_001bd450);
                                            } else {
                                                // 0x001b1db4
                                                charge(ctx, 8);
                                                lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                                lw(v0, v0, f4::scene::kMajor);
                                                a0 = addiu(v0, -20);
                                                a1 = 1;
                                                jal(ctx, 0x1B1DC4u, gen::fn_sub_1BD450_001bd450);
                                            }
                                            // 0x001b1dec
                                            charge(ctx, 4);
                                            jal(ctx, 0x1B1DECu, gen::fn_sub_1BD8C0_001bd8c0);
                                        }
                                    L_001b213c:
                                        charge(ctx, 11);
                                        lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                        lh(a0, v0, f4::scene::kEnvSub);
                                        jal(ctx, 0x1B2144u, gen::fn_sub_1B6100_001b6100);
                                        lw(v1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                        sw(v0, v1, f4::scene::kEnv);
                                        lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                        lw(v0, v0, f4::scene::kMajor);
                                        v0 = slti(v0, 200);
                                        if (v0 == 0) {
                                            // 0x001b2168
                                            charge(ctx, 7);
                                            jal(ctx, 0x1B2168u, gen::fn_sub_198590_00198590);
                                            v1 = 0x420C0000;
                                            mtc1(v1, f12);
                                            a0 = v0;
                                            jal(ctx, 0x1B217Cu, gen::fn_sub_4C9D70_004c9d70);
                                        }
                                        // 0x001b2184
                                        charge(ctx, 5);
                                        lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                        lw(v0, v0, f4::scene::kMajor);
                                        at = slti(v0, 200);
                                        if (at != 0) {
                                            // 0x001b2198
                                            charge(ctx, 7);
                                            jal(ctx, 0x1B2198u, gen::fn_sub_198590_00198590);
                                            v1 = 0x42C80000;
                                            mtc1(v1, f12);
                                            a0 = v0;
                                            jal(ctx, 0x1B21ACu, gen::fn_sub_4C9D70_004c9d70);
                                        }
                                        // 0x001b21b4
                                        charge(ctx, 4);
                                        lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                        lw(v0, v0, f4::scene::kEnv);
                                        if (v0 != 0) {
                                            // 0x001b2214
                                            charge(ctx, 4);
                                            s0 = 9;
                                            jal(ctx, 0x1B2218u, gen::fn_K_Field_Get_001b9120);
                                            sw(s0, v0, f4::fld::kLoadStep);
                                            goto L_001b2224;
                                        }
                                        // 0x001b21c4
                                        charge(ctx, 8);
                                        jal(ctx, 0x1B21C4u, gen::fn_sub_1D6B10_001d6b10);
                                        lw(v1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                        sw(v0, v1, f4::scene::kEnv);
                                        lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                        lw(v0, v0, f4::scene::kEnv);
                                        if (v0 == 0) {
                                            // 0x001b21fc
                                            charge(ctx, 6);
                                            s0 = 999;
                                            jal(ctx, 0x1B2200u, gen::fn_K_Field_Get_001b9120);
                                            sw(s0, v0, f4::fld::kLoadStep);
                                        } else {
                                            // 0x001b21e4
                                            charge(ctx, 6);
                                            s0 = 10;
                                            jal(ctx, 0x1B21E8u, gen::fn_K_Field_Get_001b9120);
                                            sw(s0, v0, f4::fld::kLoadStep);
                                        }
                                        goto L_001b2754;
                                    }
                                    // 0x001b1bfc
                                    charge(ctx, 3);
                                    v0 = 0;
                                    // 0x001b2758 (the shared epilogue, written out on this path)
                                    charge(ctx, 10);
                                    ld(ra, sp, 0x60);
                                    lq(s5, sp, 0x50);
                                    lq(s4, sp, 0x40);
                                    lq(s3, sp, 0x30);
                                    lq(s2, sp, 0x20);
                                    lq(s1, sp, 0x10);
                                    lq(s0, sp, 0x0);
                                    sp = addiu(sp, 0xE0);
                                    return;
                                }
                            L_001b1b08:
                                charge(ctx, 3);
                                v0 = slti(v1, 71);
                                if (v0 == 0) {
                                    // 0x001b1b14
                                    charge(ctx, 3);
                                    at = slti(v1, 79);
                                    if (at == 0) {
                                        goto L_001b1c44;
                                    }
                                    goto L_001b1b20;
                                }
                            L_001b1c44:
                                charge(ctx, 3);
                                s4 = 0;
                                for (;;) {
                                    // 0x001b1cdc
                                    charge(ctx, 6);
                                    jal(ctx, 0x1B1CDCu, gen::fn_K_Field_Get_001b9120);
                                    lw(v0, v0, f4::fld::kResCount);
                                    v0 = slt(s4, v0);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x001b1c50
                                    charge(ctx, 26);
                                    s3 = sll(s4, 2);
                                    jal(ctx, 0x1B1C54u, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s3);
                                    lw(s2, v0, f4::fld::kRes);
                                    jal(ctx, 0x1B1C64u, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s3);
                                    lw(s1, v0, f4::fld::kRes);
                                    jal(ctx, 0x1B1C74u, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s3);
                                    lw(v0, v0, f4::fld::kRes);
                                    lhu(s0, v0, 4);
                                    jal(ctx, 0x1B1C88u, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s3);
                                    lw(v0, v0, f4::fld::kRes);
                                    lhu(a3, v0, 6);
                                    lw(a0, s2, 2616);
                                    a1 = addiu(s1, 2620);
                                    a2 = s0;
                                    jal(ctx, 0x1B1CA8u, gen::fn_sub_1E6D50_001e6d50);
                                    if (v0 == 0) {
                                        goto L_001b1cb8_130;
                                    }
                                    // 0x001b1cc4
                                    charge(ctx, 6);
                                    jal(ctx, 0x1B1CC4u, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s3);
                                    lw(v0, v0, f4::fld::kRes);
                                    sw(zero, v0, 2616);
                                    s4 = addiu(s4, 1);
                                }
                                // 0x001b1cf4
                                charge(ctx, 3);
                                s0 = 0;
                                for (;;) {
                                    // 0x001b1d38
                                    charge(ctx, 6);
                                    jal(ctx, 0x1B1D38u, gen::fn_K_Field_Get_001b9120);
                                    lw(v0, v0, f4::fld::kResCount);
                                    v0 = slt(s0, v0);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x001b1d00
                                    charge(ctx, 14);
                                    s1 = sll(s0, 2);
                                    jal(ctx, 0x1B1D04u, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s1);
                                    lw(v0, v0, f4::fld::kRes);
                                    lw(a0, v0, 2620);
                                    jal(ctx, 0x1B1D18u, gen::fn_sub_1E6EA0_001e6ea0);
                                    jal(ctx, 0x1B1D20u, gen::fn_K_Field_Get_001b9120);
                                    v0 = addu(v0, s1);
                                    lw(v0, v0, f4::fld::kRes);
                                    sw(zero, v0, 2616);
                                    s0 = addiu(s0, 1);
                                }
                                goto L_001b1d50;
                            }
                        L_001b2224:
                            charge(ctx, 7);
                            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                            lh(a1, v0, f4::scene::kEnvSub);
                            lw(a0, v0, f4::scene::kEnv);
                            jal(ctx, 0x1B2230u, gen::fn_sub_1B61F0_001b61f0);
                            if (v0 != 0) {
                                // 0x001b2240
                                charge(ctx, 8);
                                jal(ctx, 0x1B2240u, gen::fn_sub_1D6B10_001d6b10);
                                lw(v1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                sw(v0, v1, f4::scene::kEnv);
                                lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                                lw(v0, v0, f4::scene::kEnv);
                                if (v0 == 0) {
                                    // 0x001b2278
                                    charge(ctx, 6);
                                    s0 = 999;
                                    jal(ctx, 0x1B227Cu, gen::fn_K_Field_Get_001b9120);
                                    sw(s0, v0, f4::fld::kLoadStep);
                                    goto L_001b2754;
                                }
                                // 0x001b2260
                                charge(ctx, 6);
                                s0 = 10;
                                jal(ctx, 0x1B2264u, gen::fn_K_Field_Get_001b9120);
                                sw(s0, v0, f4::fld::kLoadStep);
                                goto L_001b229c;
                            }
                            // 0x001b2290
                            charge(ctx, 3);
                            v0 = 0;
                            // 0x001b2758 (the shared epilogue, written out on this path)
                            charge(ctx, 10);
                            ld(ra, sp, 0x60);
                            lq(s5, sp, 0x50);
                            lq(s4, sp, 0x40);
                            lq(s3, sp, 0x30);
                            lq(s2, sp, 0x20);
                            lq(s1, sp, 0x10);
                            lq(s0, sp, 0x0);
                            sp = addiu(sp, 0xE0);
                            return;
                        }
                    L_001b229c:
                        charge(ctx, 12);
                        lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                        lw(a0, v0, f4::scene::kEnv);
                        a1 = addiu(sp, 0x70);
                        a2 = addiu(sp, 0xD8);
                        a3 = addiu(sp, 0xD4);
                        t0 = addiu(sp, 0xB0);
                        t1 = addiu(sp, 0xD0);
                        t2 = addiu(sp, 0xCC);
                        jal(ctx, 0x1B22BCu, gen::fn_sub_1D6BC0_001d6bc0);
                        if (v0 != 0) {
                            // 0x001b22cc
                            charge(ctx, 15);
                            a0 = 0;
                            lw(a1, sp, 0xD4);
                            lwc1(f12, sp, 0xD8);
                            a2 = addiu(sp, 0x70);
                            a3 = addiu(sp, 0xB0);
                            lwc1(f13, sp, 0xD0);
                            lwc1(f14, sp, 0xCC);
                            jal(ctx, 0x1B22E8u, gen::fn_sub_3B6F50_003b6f50);
                            s0 = 999;
                            jal(ctx, 0x1B22F4u, gen::fn_K_Field_Get_001b9120);
                            sw(s0, v0, f4::fld::kLoadStep);
                            goto L_001b2754;
                        }
                        // 0x001b2308
                        charge(ctx, 3);
                        v0 = 0;
                        // 0x001b2758 (the shared epilogue, written out on this path)
                        charge(ctx, 10);
                        ld(ra, sp, 0x60);
                        lq(s5, sp, 0x50);
                        lq(s4, sp, 0x40);
                        lq(s3, sp, 0x30);
                        lq(s2, sp, 0x20);
                        lq(s1, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0xE0);
                        return;
                    }
                L_001b245c:
                    charge(ctx, 6);
                    s3 = 0;
                    jal(ctx, 0x1B2460u, gen::fn_sub_1A02C0_001a02c0);
                    v1 = 1;
                    if (v0 != v1) {
                        // 0x001b24c0
                        charge(ctx, 3);
                        s4 = 0;
                        for (;;) {
                            // 0x001b2544
                            charge(ctx, 6);
                            jal(ctx, 0x1B2544u, gen::fn_K_Field_Get_001b9120);
                            lw(v0, v0, f4::fld::kResCount);
                            v0 = slt(s4, v0);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                            // 0x001b24cc
                            charge(ctx, 28);
                            s2 = sll(s4, 2);
                            jal(ctx, 0x1B24D0u, gen::fn_K_Field_Get_001b9120);
                            v0 = addu(v0, s2);
                            lw(s1, v0, f4::fld::kRes);
                            jal(ctx, 0x1B24E0u, gen::fn_K_Field_Get_001b9120);
                            v0 = addu(v0, s2);
                            lw(s0, v0, f4::fld::kRes);
                            jal(ctx, 0x1B24F0u, gen::fn_K_Field_Get_001b9120);
                            v0 = addu(v0, s2);
                            lw(v0, v0, f4::fld::kRes);
                            lhu(s5, v0, 4);
                            jal(ctx, 0x1B2504u, gen::fn_K_Field_Get_001b9120);
                            v0 = addu(v0, s2);
                            lw(v0, v0, f4::fld::kRes);
                            lhu(a3, v0, 6);
                            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                            lw(a0, s1, 2628);
                            a1 = addiu(s0, 2632);
                            a2 = s5;
                            lh(t0, v0, f4::scene::kNpcSet);
                            jal(ctx, 0x1B252Cu, gen::fn_sub_1E2E50_001e2e50);
                            if (v0 == 0) {
                                // 0x001b253c
                                charge(ctx, 1);
                                s3 = addiu(s3, 1);
                            }
                            // 0x001b2540
                            charge(ctx, 1);
                            s4 = addiu(s4, 1);
                        }
                    } else {
                        // 0x001b2474
                        charge(ctx, 16);
                        lw(s1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                        jal(ctx, 0x1B2478u, gen::fn_K_Field_Get_001b9120);
                        lw(s0, v0, f4::fld::kRes);
                        jal(ctx, 0x1B2484u, gen::fn_K_Field_Get_001b9120);
                        lw(v0, v0, f4::fld::kRes);
                        lhu(a2, s1, f4::scene::kMajor);
                        lhu(a3, s1, f4::scene::kMinor);
                        lw(a0, s0, 2628);
                        a1 = addiu(v0, 2632);
                        lh(t0, s1, f4::scene::kNpcSet);
                        jal(ctx, 0x1B24A4u, gen::fn_sub_1E2E50_001e2e50);
                        if (v0 == 0) {
                            // 0x001b24b4
                            charge(ctx, 3);
                            s3 = addiu(s3, 1);
                        }
                    }
                    // 0x001b255c
                    charge(ctx, 2);
                    if (s3 == 0) {
                        // 0x001b2570
                        charge(ctx, 4);
                        s0 = 32;
                        jal(ctx, 0x1B2574u, gen::fn_K_Field_Get_001b9120);
                        sw(s0, v0, f4::fld::kLoadStep);
                        goto L_001b2580;
                    }
                    // 0x001b2564
                    charge(ctx, 3);
                    v0 = 0;
                    // 0x001b2758 (the shared epilogue, written out on this path)
                    charge(ctx, 10);
                    ld(ra, sp, 0x60);
                    lq(s5, sp, 0x50);
                    lq(s4, sp, 0x40);
                    lq(s3, sp, 0x30);
                    lq(s2, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0xE0);
                    return;
                }
            L_001b2580:
                charge(ctx, 6);
                s2 = 0;
                jal(ctx, 0x1B2584u, gen::fn_sub_1A02C0_001a02c0);
                v1 = 1;
                if (v0 != v1) {
                    // 0x001b25ec
                    charge(ctx, 3);
                    s3 = 0;
                    for (;;) {
                        // 0x001b2658
                        charge(ctx, 6);
                        jal(ctx, 0x1B2658u, gen::fn_K_Field_Get_001b9120);
                        lw(v0, v0, f4::fld::kResCount);
                        v0 = slt(s3, v0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001b25f8
                        charge(ctx, 15);
                        s1 = sll(s3, 2);
                        jal(ctx, 0x1B25FCu, gen::fn_K_Field_Get_001b9120);
                        v0 = addu(v0, s1);
                        lw(s0, v0, f4::fld::kRes);
                        jal(ctx, 0x1B260Cu, gen::fn_K_Field_Get_001b9120);
                        v0 = addu(v0, s1);
                        lw(v0, v0, f4::fld::kRes);
                        lw(a0, s0, 2628);
                        lw(a1, v0, 2632);
                        jal(ctx, 0x1B2624u, gen::fn_sub_1E3940_001e3940);
                        if (v0 != 0) {
                            // 0x001b2640
                            charge(ctx, 5);
                            jal(ctx, 0x1B2640u, gen::fn_K_Field_Get_001b9120);
                            v0 = addu(v0, s1);
                            lw(v0, v0, f4::fld::kRes);
                            sw(zero, v0, 2628);
                        } else {
                            // 0x001b2634
                            charge(ctx, 3);
                            s2 = addiu(s2, 1);
                        }
                        // 0x001b2654
                        charge(ctx, 1);
                        s3 = addiu(s3, 1);
                    }
                } else {
                    // 0x001b2598
                    charge(ctx, 12);
                    jal(ctx, 0x1B2598u, gen::fn_K_Field_Get_001b9120);
                    lw(s0, v0, f4::fld::kRes);
                    jal(ctx, 0x1B25A4u, gen::fn_K_Field_Get_001b9120);
                    lw(v0, v0, f4::fld::kRes);
                    lw(a0, s0, 2628);
                    lw(a1, v0, 2632);
                    jal(ctx, 0x1B25B8u, gen::fn_sub_1E3940_001e3940);
                    if (v0 != 0) {
                        // 0x001b25d4
                        charge(ctx, 6);
                        jal(ctx, 0x1B25D4u, gen::fn_K_Field_Get_001b9120);
                        lw(v0, v0, f4::fld::kRes);
                        sw(zero, v0, 2628);
                    } else {
                        // 0x001b25c8
                        charge(ctx, 3);
                        s2 = addiu(s2, 1);
                    }
                }
                // 0x001b2670
                charge(ctx, 2);
                if (s2 == 0) {
                    // 0x001b2684
                    charge(ctx, 5);
                    lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
                    lw(v0, v0, f4::scene::kFlags);
                    v0 = v0 & 0x4;
                    if (v0 == 0) {
                        // 0x001b26b0
                        charge(ctx, 6);
                        s0 = 999;
                        jal(ctx, 0x1B26B4u, gen::fn_K_Field_Get_001b9120);
                        sw(s0, v0, f4::fld::kLoadStep);
                        goto L_001b2754;
                    }
                    // 0x001b2698
                    charge(ctx, 6);
                    s0 = 40;
                    jal(ctx, 0x1B269Cu, gen::fn_K_Field_Get_001b9120);
                    sw(s0, v0, f4::fld::kLoadStep);
                    goto L_001b26c8;
                }
                // 0x001b2678
                charge(ctx, 3);
                v0 = 0;
                // 0x001b2758 (the shared epilogue, written out on this path)
                charge(ctx, 10);
                ld(ra, sp, 0x60);
                lq(s5, sp, 0x50);
                lq(s4, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0xE0);
                return;
            }
        L_001b26c8:
            charge(ctx, 10);
            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            lh(a0, v0, f4::scene::kEnvSub);
            jal(ctx, 0x1B26D0u, gen::fn_sub_1B6100_001b6100);
            lw(v1, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            sw(v0, v1, f4::scene::kEnv);
            s0 = 41;
            jal(ctx, 0x1B26E4u, gen::fn_K_Field_Get_001b9120);
            sw(s0, v0, f4::fld::kLoadStep);
        }
        // 0x001b26f0
        charge(ctx, 7);
        lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
        lh(a1, v0, f4::scene::kEnvSub);
        lw(a0, v0, f4::scene::kEnv);
        jal(ctx, 0x1B26FCu, gen::fn_sub_1B61F0_001b61f0);
        if (v0 != 0) {
            // 0x001b270c
            charge(ctx, 6);
            s0 = 999;
            jal(ctx, 0x1B2710u, gen::fn_K_Field_Get_001b9120);
            sw(s0, v0, f4::fld::kLoadStep);
            goto L_001b2754;
        }
        // 0x001b2724
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001b2758 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xE0);
    return;
L_001b1b94_121:
    charge(ctx, 3);
    v0 = 0;
    // 0x001b2758 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xE0);
    return;
L_001b1cb8_130:
    charge(ctx, 3);
    v0 = 0;
    // 0x001b2758 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xE0);
}

// 0x001B2780 sub_1B2780 [K_Fldrc_OpenFieldModel] -- 216 bytes; frame 0x60: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B2780(major, minor) -> a new field resource record for "field/pack/f%03d_%03d.rws" when the .fpc is resident
// (its "%03d" from 0x7CC228), else "field/model/f%03d_%03d.rws" (sub_1B2860).
void sub_1B2780(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b2780
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    lw(v0, gp, f4::gpv::kFpcRequest);  // 0x7CE160
    if (v0 != 0) {
        // 0x001b27c0
        charge(ctx, 5);
        a0 = addiu(sp, 0x30);
        a1 = 0x680000;
        a1 = addiu(a1, -29160);  // "field/pack/f"
        jal(ctx, 0x1B27CCu, gen::fn_strcpy_00524270);
    } else {
        // 0x001b27a4
        charge(ctx, 7);
        a0 = addiu(sp, 0x30);
        a1 = 0x680000;
        a1 = addiu(a1, -29176);  // "field/model/f"
        jal(ctx, 0x1B27B0u, gen::fn_strcpy_00524270);
    }
    // 0x001b27d4
    charge(ctx, 33);
    a2 = dsll32(s1, 16);
    a2 = dsra32(a2, 16);
    a0 = addiu(sp, 0x58);
    a1 = addiu(gp, -27336);  // "%03d"
    jal(ctx, 0x1B27E4u, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0x30);
    a1 = addiu(sp, 0x58);
    jal(ctx, 0x1B27F4u, gen::fn_strcat_00523e68);
    a2 = dsll32(s0, 16);
    a2 = dsra32(a2, 16);
    a0 = addiu(sp, 0x58);
    a1 = addiu(gp, -27328);  // "_%03d"
    jal(ctx, 0x1B280Cu, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0x30);
    a1 = addiu(sp, 0x58);
    jal(ctx, 0x1B281Cu, gen::fn_strcat_00523e68);
    a0 = addiu(sp, 0x30);
    a1 = addiu(gp, -27320);  // ".rws"
    jal(ctx, 0x1B282Cu, gen::fn_strcat_00523e68);
    a0 = addiu(sp, 0x30);
    jal(ctx, 0x1B2838u, gen::fn_sub_1B2860_001b2860);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001B2860 sub_1B2860 [K_Fldrc_CreateFieldResource] -- 716 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B2860(path) -> a field resource record (RwMalloc'd 2,636 bytes; NULL when out of memory): its file record
// (+2624, 292 bytes: the path, the H_Cdvd node at +128, or 1 when the model comes from the .fpc cache) and the ids
// parsed back out of the path: ".../fMMM_NNN" with three digits each (ctype table 0x7BE9C8 bit 4) -> u16 +4 major,
// +6 minor; anything else -> 0xFFFF, 0xFFFF.
void sub_1B2860(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b2860
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = a0;
    s0 = 1;
    s3 = 0x960000;
    s3 = addiu(s3, 388);  // &0x960184
    a0 = s0;
    a1 = 2636;
    a2 = 0x40000;
    lw(v0, s3, 0);  // 0x960184
    jalr(ctx, 0x1B2898u, v0.u());
    s1 = v0;
    if (s1 != 0) {
        // 0x001b28b4
        charge(ctx, 9);
        a0 = s0;
        a1 = 292;
        a2 = 0x40000;
        lw(v0, s3, 0);
        jalr(ctx, 0x1B28C4u, v0.u());
        sw(v0, s1, 2624);
        if (v0 != 0) {
            // 0x001b28f8
            charge(ctx, 6);
            a0 = v0;
            a1 = s2;
            jal(ctx, 0x1B2900u, gen::fn_strcpy_00524270);
            for (;;) {
                // 0x001b2914
                charge(ctx, 6);
                lb(v0, s2, 0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001b2910
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x001b292c
            charge(ctx, 3);
            v0 = 47;
            for (;;) {
                // 0x001b293c
                charge(ctx, 6);
                lb(v1, s2, 0);
                if (v1 == v0) {
                    break;
                }
                backedge(ctx);
                // 0x001b2938
                charge(ctx, 1);
                s2 = addiu(s2, -1);
            }
            // 0x001b2954
            charge(ctx, 4);
            lb(v1, s2, 1);
            v0 = 102;
            if (v1 != v0) {
                // 0x001b2a58
                charge(ctx, 1);
                s0 = 0;
            } else {
                // 0x001b2964
                charge(ctx, 8);
                lb(v1, s2, 2);
                v0 = 0x7C0000;
                v0 = addiu(v0, -5688);  // &0x7BE9C8
                v0 = addu(v0, v1);
                lb(v0, v0, 0);
                v0 = v0 & 0x4;
                if (v0 == 0) {
                    // 0x001b2984
                    charge(ctx, 1);
                    s0 = 0;
                }
                // 0x001b2988
                charge(ctx, 8);
                lb(v1, s2, 3);
                v0 = 0x7C0000;
                v0 = addiu(v0, -5688);  // &0x7BE9C8
                v0 = addu(v0, v1);
                lb(v0, v0, 0);
                v0 = v0 & 0x4;
                if (v0 == 0) {
                    // 0x001b29a8
                    charge(ctx, 1);
                    s0 = 0;
                }
                // 0x001b29ac
                charge(ctx, 8);
                lb(v1, s2, 4);
                v0 = 0x7C0000;
                v0 = addiu(v0, -5688);  // &0x7BE9C8
                v0 = addu(v0, v1);
                lb(v0, v0, 0);
                v0 = v0 & 0x4;
                if (v0 == 0) {
                    // 0x001b29cc
                    charge(ctx, 1);
                    s0 = 0;
                }
                // 0x001b29d0
                charge(ctx, 4);
                lb(v1, s2, 5);
                v0 = 95;
                if (v1 != v0) {
                    // 0x001b29e0
                    charge(ctx, 1);
                    s0 = 0;
                }
                // 0x001b29e4
                charge(ctx, 8);
                lb(v1, s2, 6);
                v0 = 0x7C0000;
                v0 = addiu(v0, -5688);  // &0x7BE9C8
                v0 = addu(v0, v1);
                lb(v0, v0, 0);
                v0 = v0 & 0x4;
                if (v0 == 0) {
                    // 0x001b2a04
                    charge(ctx, 1);
                    s0 = 0;
                }
                // 0x001b2a08
                charge(ctx, 8);
                lb(v1, s2, 7);
                v0 = 0x7C0000;
                v0 = addiu(v0, -5688);  // &0x7BE9C8
                v0 = addu(v0, v1);
                lb(v0, v0, 0);
                v0 = v0 & 0x4;
                if (v0 == 0) {
                    // 0x001b2a28
                    charge(ctx, 1);
                    s0 = 0;
                }
                // 0x001b2a2c
                charge(ctx, 8);
                lb(v1, s2, 8);
                v0 = 0x7C0000;
                v0 = addiu(v0, -5688);  // &0x7BE9C8
                v0 = addu(v0, v1);
                lb(v0, v0, 0);
                v0 = v0 & 0x4;
                if (v0 == 0) {
                    // 0x001b2a4c
                    charge(ctx, 3);
                    s0 = 0;
                }
            }
            // 0x001b2a5c
            charge(ctx, 2);
            if (s0 == 0) {
                // 0x001b2ac4
                charge(ctx, 3);
                v0 = si(-1);
                sh(v0, s1, 4);
                sh(v0, s1, 6);
            } else {
                // 0x001b2a64
                charge(ctx, 24);
                lb(v0, s2, 2);
                sb(v0, sp, 0x58);
                lb(v0, s2, 3);
                sb(v0, sp, 0x59);
                lb(v0, s2, 4);
                sb(v0, sp, 0x5A);
                sb(zero, sp, 0x5B);
                a0 = addiu(sp, 0x58);
                jal(ctx, 0x1B2A84u, gen::fn_atoi_0051e0f0);
                sh(v0, s1, 4);
                lb(v0, s2, 6);
                sb(v0, sp, 0x58);
                lb(v0, s2, 7);
                sb(v0, sp, 0x59);
                lb(v0, s2, 8);
                sb(v0, sp, 0x5A);
                sb(zero, sp, 0x5B);
                a0 = addiu(sp, 0x58);
                jal(ctx, 0x1B2AB0u, gen::fn_atoi_0051e0f0);
                sh(v0, s1, 6);
            }
            // 0x001b2ad0
            charge(ctx, 3);
            lw(v0, gp, f4::gpv::kFpcRequest);  // 0x7CE160
            if (v0 != 0) {
                // 0x001b2afc
                charge(ctx, 3);
                v1 = 1;
                lw(v0, s1, 2624);
                sw(v1, v0, 128);
            } else {
                // 0x001b2adc
                charge(ctx, 8);
                lw(a0, s1, 2624);
                a1 = 0;
                jal(ctx, 0x1B2AE4u, gen::fn_H_Cdvd_Request_00100d80);
                lw(v1, s1, 2624);
                sw(v0, v1, 128);
            }
            // 0x001b2b08
            charge(ctx, 1);
            v0 = s1;
        } else {
            // 0x001b28d8
            charge(ctx, 8);
            a0 = s1;
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            jalr(ctx, 0x1B28E4u, v0.u());
            v0 = 0;
        }
    } else {
        // 0x001b28ac
        charge(ctx, 2);
    }
    // 0x001b2b0c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001B2B30 sub_1B2B30 [K_Fldrc_IsFieldResourceLoaded] -- 88 bytes; frame 0x10: ra sp+0x0
// sub_1B2B30(res) -> 1 when the record's model file is ready: no node, the .fpc cache, or H_Cdvd_IsFileLoaded.
void sub_1B2B30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b2b30
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 2624);
    lw(a0, v0, 128);
    if (a0 != 0) {
        // 0x001b2b54
        charge(ctx, 3);
        lw(v0, gp, f4::gpv::kFpcRequest);  // 0x7CE160
        if (v0 != 0) {
            // 0x001b2b74
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x001b2b60
            charge(ctx, 5);
            jal(ctx, 0x1B2B60u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            v0 = sltu(0, v0);
        }
    } else {
        // 0x001b2b48
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x001b2b78 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B2B90 sub_1B2B90 [K_Fldrc_ParseFieldModelStream] -- 868 bytes; frame 0x90: ra sp+0x50, s2 sp+0x40 (sq), s1 sp+0x30 (sq), s0 sp+0x20 (sq)
// sub_1B2B90(res): walks the RW chunks of the loaded model (H_Cdvd_CacheFindFile, RwStreamOpen sub_4C58A0,
// RwStreamFindChunk-style sub_4C1970): 12 -> UV animation dictionary (+2588); 22 / 35 -> texture dictionaries read
// and registered through the callback sub_1A13B0 into the file record's dictionary +288; 16 -> a clump read request
// (sub_10C1A0 type 2) into the file record's clump list (+152 count, +156..); 11 -> a world read request (type 1,
// +140 count, +144..); anything else skipped. Without a stream the record and its file record are freed.
void sub_1B2B90(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b2b90
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x50);
    sq(s2, sp, 0x40);
    sq(s1, sp, 0x30);
    sq(s0, sp, 0x20);
    s2 = a0;
    lw(a0, a0, 2624);
    a1 = addiu(sp, 0x8C);
    jal(ctx, 0x1B2BB0u, gen::fn_H_Cdvd_CacheFindFile_001021c0);
    sw(v0, sp, 0x80);
    lw(v1, sp, 0x8C);
    sw(v1, sp, 0x84);
    if (v0 != 0) {
        // 0x001b2bcc
        charge(ctx, 8);
        a0 = 3;
        a1 = 1;
        a2 = addiu(sp, 0x80);
        jal(ctx, 0x1B2BD8u, gen::fn_sub_4C58A0_004c58a0);
        s1 = v0;
        if (s1 == 0) {
            // 0x001b2e90
            charge(ctx, 3);
            lw(v1, s2, 2624);
            if (v1 != 0) {
                // 0x001b2e9c
                charge(ctx, 8);
                lw(a0, v1, 128);
                jal(ctx, 0x1B2EA0u, gen::fn_H_Cdvd_Destroy_00100ec0);
                lw(a0, s2, 2624);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C
                jalr(ctx, 0x1B2EB4u, v0.u());
            }
            // 0x001b2ebc
            charge(ctx, 2);
            if (s2 != 0) {
                // 0x001b2ec4
                charge(ctx, 5);
                a0 = s2;
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C
                jalr(ctx, 0x1B2ED0u, v0.u());
            }
        } else {
            // 0x001b2bec
            charge(ctx, 2);
            for (;;) {
                // 0x001b2e58
                charge(ctx, 6);
                a0 = s1;
                a1 = addiu(sp, 0x60);
                jal(ctx, 0x1B2E60u, gen::fn_sub_4C1970_004c1970);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001b2bf4
                charge(ctx, 4);
                lw(v1, sp, 0x60);
                v0 = 12;
                if (v1 == v0) {
                    // 0x001b2e30
                    charge(ctx, 6);
                    a0 = s1;
                    jal(ctx, 0x1B2E34u, gen::fn_sub_48D0E0_0048d0e0);
                    sw(v0, s2, 2588);
                } else {
                    // 0x001b2c04
                    charge(ctx, 3);
                    v0 = 22;
                    if (v1 == v0) {
                        // 0x001b2df0
                        charge(ctx, 16);
                        a0 = s1;
                        jal(ctx, 0x1B2DF4u, gen::fn_sub_4C8680_004c8680);
                        s0 = v0;
                        lw(v0, s2, 2624);
                        a0 = s0;
                        a1 = 0x1A0000;
                        a1 = addiu(a1, 5040);  // &sub_1A13B0
                        a2 = addiu(v0, 288);
                        jal(ctx, 0x1B2E14u, gen::fn_sub_4D0DC0_004d0dc0);
                        a0 = s0;
                        jal(ctx, 0x1B2E20u, gen::fn_sub_4D0D10_004d0d10);
                    } else {
                        // 0x001b2c10
                        charge(ctx, 3);
                        v0 = 35;
                        if (v1 == v0) {
                            // 0x001b2db0
                            charge(ctx, 16);
                            a0 = s1;
                            jal(ctx, 0x1B2DB4u, gen::fn_sub_4BDA10_004bda10);
                            s0 = v0;
                            lw(v0, s2, 2624);
                            a0 = s0;
                            a1 = 0x1A0000;
                            a1 = addiu(a1, 5040);  // &sub_1A13B0
                            a2 = addiu(v0, 288);
                            jal(ctx, 0x1B2DD4u, gen::fn_sub_4D0DC0_004d0dc0);
                            a0 = s0;
                            jal(ctx, 0x1B2DE0u, gen::fn_sub_4D0D10_004d0d10);
                        } else {
                            // 0x001b2c1c
                            charge(ctx, 3);
                            v0 = 16;
                            if (v1 == v0) {
                                // 0x001b2d04
                                charge(ctx, 43);
                                lw(v1, sp, 0x80);
                                lw(v0, s1, 12);
                                v0 = addu(v1, v0);
                                sw(v0, sp, 0x78);
                                lw(v0, sp, 0x84);
                                sw(v0, sp, 0x7C);
                                a0 = 3;
                                a1 = 1;
                                a2 = addiu(sp, 0x78);
                                jal(ctx, 0x1B2D28u, gen::fn_sub_4C58A0_004c58a0);
                                lw(s0, s2, 2624);
                                sd(zero, sp, 0x0);
                                sd(zero, sp, 0x8);
                                v1 = 0x680000;
                                v1 = addiu(v1, -29192);  // "k_fldrc.c"
                                sd(v1, sp, 0x10);
                                v1 = 1238;
                                sd(v1, sp, 0x18);
                                a0 = 2;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                t0 = v0;
                                t1 = 0;
                                t2 = 0;
                                t3 = 0;
                                jal(ctx, 0x1B2D70u, gen::fn_sub_10C1A0_0010c1a0);
                                lw(v1, s0, 152);
                                v1 = sll(v1, 2);
                                v1 = addu(s0, v1);
                                sw(v0, v1, 156);
                                a0 = s1;
                                lw(a1, sp, 0x64);
                                jal(ctx, 0x1B2D90u, gen::fn_sub_4C5620_004c5620);
                                lw(v1, s2, 2624);
                                lw(v0, v1, 152);
                                v0 = addiu(v0, 1);
                                sw(v0, v1, 152);
                            } else {
                                // 0x001b2c28
                                charge(ctx, 3);
                                v0 = 11;
                                if (v1 == v0) {
                                    // 0x001b2c3c
                                    charge(ctx, 7);
                                    lw(v1, s2, 2624);
                                    lw(v0, v1, 140);
                                    v0 = sll(v0, 2);
                                    v0 = addu(v1, v0);
                                    lw(v0, v0, 144);
                                    if (v0 == 0) {
                                        // 0x001b2c58
                                        charge(ctx, 4);
                                        lw(v1, sp, 0x80);
                                        lw(v0, s1, 12);
                                        v0 = addu(v1, v0);
                                        sw(v0, sp, 0x78);
                                    }
                                    // 0x001b2c68
                                    charge(ctx, 39);
                                    lw(v0, sp, 0x84);
                                    sw(v0, sp, 0x7C);
                                    a0 = 3;
                                    a1 = 1;
                                    a2 = addiu(sp, 0x78);
                                    jal(ctx, 0x1B2C7Cu, gen::fn_sub_4C58A0_004c58a0);
                                    lw(s0, s2, 2624);
                                    sd(zero, sp, 0x0);
                                    sd(zero, sp, 0x8);
                                    v1 = 0x680000;
                                    v1 = addiu(v1, -29192);  // "k_fldrc.c"
                                    sd(v1, sp, 0x10);
                                    v1 = 1224;
                                    sd(v1, sp, 0x18);
                                    a0 = 1;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    t0 = v0;
                                    t1 = 0;
                                    t2 = 0;
                                    t3 = 0;
                                    jal(ctx, 0x1B2CC4u, gen::fn_sub_10C1A0_0010c1a0);
                                    lw(v1, s0, 140);
                                    v1 = sll(v1, 2);
                                    v1 = addu(s0, v1);
                                    sw(v0, v1, 144);
                                    a0 = s1;
                                    lw(a1, sp, 0x64);
                                    jal(ctx, 0x1B2CE4u, gen::fn_sub_4C5620_004c5620);
                                    lw(v1, s2, 2624);
                                    lw(v0, v1, 140);
                                    v0 = addiu(v0, 1);
                                    sw(v0, v1, 140);
                                } else {
                                    // 0x001b2c34
                                    charge(ctx, 2);
                                    // 0x001b2e48
                                    charge(ctx, 4);
                                    a0 = s1;
                                    lw(a1, sp, 0x64);
                                    jal(ctx, 0x1B2E50u, gen::fn_sub_4C5620_004c5620);
                                }
                            }
                        }
                    }
                }
            }
            // 0x001b2e70
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x001b2e78
                charge(ctx, 6);
                a0 = s1;
                a1 = 0;
                jal(ctx, 0x1B2E80u, gen::fn_sub_4C5780_004c5780);
            }
        }
    }
    // 0x001b2ed8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x50);
    lq(s2, sp, 0x40);
    lq(s1, sp, 0x30);
    lq(s0, sp, 0x20);
    sp = addiu(sp, 0x90);
}

// 0x001B2F00 sub_1B2F00 [K_Fldrc_TryFinishFieldModels] -- 1004 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B2F00(res) -> 1 when every world / clump read request of the record has finished (sub_10C3A0): texture
// dictionaries registered; a world named "per3ShadowCollis" (user data) becomes the shadow collision (+16), the
// first other world the collision world (+12, flags bit 0 set, inserted in the main world), the next ones +8; clumps:
// the shadow clump, else the collision clump (+8, +12 = its atomic list sub_1A7570) or a draw clump appended to +24
// [count +20] with its atomic list at +152. Ends with flags bit 29 when no collision mesh exists, the scale
// +2592..+2600 = 1.0 and the file node destroyed (unless it was the .fpc cache).
void sub_1B2F00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b2f00
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = 0;
    lw(v1, a0, 2624);
    if (v1 != 0) {
        // 0x001b2f3c
        charge(ctx, 3);
        lw(v0, v1, 132);
        if (v0 != 0) {
            // 0x001b2f48
            charge(ctx, 3);
            lw(v0, v1, 288);
            if (v0 != 0) {
                // 0x001b2f54
                charge(ctx, 5);
                a0 = 0x680000;
                a0 = addiu(a0, -29192);  // "k_fldrc.c"
                a1 = 1332;
                jal(ctx, 0x1B2F60u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x001b2f68
            charge(ctx, 10);
            lw(a0, s1, 2624);
            a1 = addiu(sp, 0x68);
            a2 = addiu(sp, 0x6C);
            jal(ctx, 0x1B2F74u, gen::fn_sub_10C3A0_0010c3a0);
            s2 = v0;
            lw(v1, sp, 0x68);
            v0 = 1;
            if (v1 != v0) {
                // 0x001b2fe0
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            } else {
                // 0x001b2f90
                charge(ctx, 15);
                lw(v0, s1, 2624);
                a0 = s2;
                a1 = 0x1A0000;
                a1 = addiu(a1, 5040);  // &sub_1A13B0
                a2 = addiu(v0, 288);
                jal(ctx, 0x1B2FA4u, gen::fn_sub_4D0DC0_004d0dc0);
                a0 = s2;
                jal(ctx, 0x1B2FB0u, gen::fn_sub_4D0D10_004d0d10);
                lw(v0, s1, 2624);
                sw(zero, v0, 132);
                lw(a0, sp, 0x6C);
                if (a0 != 0) {
                    // 0x001b2fcc
                    charge(ctx, 5);
                    a1 = 0;
                    jal(ctx, 0x1B2FD0u, gen::fn_sub_4C5780_004c5780);
                }
            }
        }
        // 0x001b2fe4
        charge(ctx, 3);
        s4 = 0;
        for (;;) {
            // 0x001b30e0
            charge(ctx, 5);
            lw(v1, s1, 2624);
            lw(v0, v1, 140);
            v0 = sltu(s4, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001b2ff0
            charge(ctx, 5);
            s2 = sll(s4, 2);
            v0 = addu(v1, s2);
            lw(a0, v0, 144);
            if (a0 != 0) {
                // 0x001b3004
                charge(ctx, 9);
                a1 = addiu(sp, 0x68);
                a2 = addiu(sp, 0x6C);
                jal(ctx, 0x1B300Cu, gen::fn_sub_10C3A0_0010c3a0);
                s3 = v0;
                lw(v1, sp, 0x68);
                v0 = 1;
                if (v1 != v0) {
                    // 0x001b30d8
                    charge(ctx, 1);
                    s0 = addiu(s0, 1);
                } else {
                    // 0x001b3028
                    charge(ctx, 2);
                    if (s3 == 0) {
                        // 0x001b3030
                        charge(ctx, 5);
                        a0 = 0x680000;
                        a0 = addiu(a0, -29192);  // "k_fldrc.c"
                        a1 = 1360;
                        jal(ctx, 0x1B303Cu, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    // 0x001b3044
                    charge(ctx, 7);
                    a0 = s3;
                    a1 = 0x680000;
                    a1 = addiu(a1, -29136);  // "per3ShadowCollis"
                    jal(ctx, 0x1B3050u, gen::fn_sub_1A6740_001a6740);
                    if (v0 == 0) {
                        // 0x001b306c
                        charge(ctx, 3);
                        lw(v0, s1, 12);
                        if (v0 != 0) {
                            // 0x001b309c
                            charge(ctx, 1);
                            sw(s3, s1, 8);
                        } else {
                            // 0x001b3078
                            charge(ctx, 9);
                            sw(s3, s1, 12);
                            jal(ctx, 0x1B307Cu, gen::fn_sub_198590_00198590);
                            a0 = s3;
                            a1 = v0;
                            jal(ctx, 0x1B308Cu, gen::fn_sub_4BCBF0_004bcbf0);
                        }
                    } else {
                        // 0x001b3060
                        charge(ctx, 3);
                        sw(s3, s1, 16);
                    }
                    // 0x001b30a0
                    charge(ctx, 9);
                    lw(v0, s1, 2624);
                    v0 = addu(v0, s2);
                    sw(zero, v0, 144);
                    lw(v0, s1, 0);
                    v0 = v0 | 0x1;
                    sw(v0, s1, 0);
                    lw(a0, sp, 0x6C);
                    if (a0 != 0) {
                        // 0x001b30c4
                        charge(ctx, 5);
                        a1 = 0;
                        jal(ctx, 0x1B30C8u, gen::fn_sub_4C5780_004c5780);
                    }
                }
            }
            // 0x001b30dc
            charge(ctx, 1);
            s4 = addiu(s4, 1);
        }
        // 0x001b30f4
        charge(ctx, 3);
        s3 = 0;
        for (;;) {
            // 0x001b3220
            charge(ctx, 5);
            lw(v1, s1, 2624);
            lw(v0, v1, 152);
            v0 = sltu(s3, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001b3100
            charge(ctx, 5);
            s2 = sll(s3, 2);
            v0 = addu(v1, s2);
            lw(a0, v0, 156);
            if (a0 != 0) {
                // 0x001b3114
                charge(ctx, 9);
                a1 = addiu(sp, 0x68);
                a2 = addiu(sp, 0x6C);
                jal(ctx, 0x1B311Cu, gen::fn_sub_10C3A0_0010c3a0);
                s4 = v0;
                lw(v1, sp, 0x68);
                v0 = 1;
                if (v1 != v0) {
                    // 0x001b3218
                    charge(ctx, 1);
                    s0 = addiu(s0, 1);
                } else {
                    // 0x001b3138
                    charge(ctx, 2);
                    if (s4 == 0) {
                        // 0x001b3140
                        charge(ctx, 5);
                        a0 = 0x680000;
                        a0 = addiu(a0, -29192);  // "k_fldrc.c"
                        a1 = 1393;
                        jal(ctx, 0x1B314Cu, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    // 0x001b3154
                    charge(ctx, 7);
                    a0 = s4;
                    a1 = 0x680000;
                    a1 = addiu(a1, -29136);  // "per3ShadowCollis"
                    jal(ctx, 0x1B3160u, gen::fn_sub_1A66F0_001a66f0);
                    if (v0 == 0) {
                        // 0x001b317c
                        charge(ctx, 4);
                        lw(v0, s1, 0);
                        v0 = v0 & 0x1;
                        if (v0 == 0) {
                            // 0x001b318c
                            charge(ctx, 3);
                            lw(v0, s1, 8);
                            if (v0 != 0) {
                                goto L_001b31b4;
                            }
                            // 0x001b3198
                            charge(ctx, 7);
                            sw(s4, s1, 8);
                            a0 = s4;
                            jal(ctx, 0x1B31A0u, gen::fn_sub_1A7570_001a7570);
                            sw(v0, s1, 12);
                            goto L_001b31ec;
                        }
                    L_001b31b4:
                        charge(ctx, 14);
                        lw(v0, s1, 20);
                        v0 = sll(v0, 2);
                        v0 = addu(s1, v0);
                        sw(s4, v0, 24);
                        a0 = s4;
                        jal(ctx, 0x1B31C8u, gen::fn_sub_1A7570_001a7570);
                        lw(v1, s1, 20);
                        v1 = sll(v1, 2);
                        v1 = addu(s1, v1);
                        sw(v0, v1, 152);
                        lw(v0, s1, 20);
                        v0 = addiu(v0, 1);
                        sw(v0, s1, 20);
                    } else {
                        // 0x001b3170
                        charge(ctx, 3);
                        sw(s4, s1, 16);
                    }
                L_001b31ec:
                    charge(ctx, 6);
                    lw(v0, s1, 2624);
                    v0 = addu(v0, s2);
                    sw(zero, v0, 156);
                    lw(a0, sp, 0x6C);
                    if (a0 != 0) {
                        // 0x001b3204
                        charge(ctx, 5);
                        a1 = 0;
                        jal(ctx, 0x1B3208u, gen::fn_sub_4C5780_004c5780);
                    }
                }
            }
            // 0x001b321c
            charge(ctx, 1);
            s3 = addiu(s3, 1);
        }
        // 0x001b3234
        charge(ctx, 3);
        sw(zero, v1, 284);
        if (s0 != 0) {
            // 0x001b32c4
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x001b3240
            charge(ctx, 3);
            lw(v0, s1, 8);
            if (v0 == 0) {
                // 0x001b324c
                charge(ctx, 6);
                lw(v1, s1, 0);
                v0 = 0x20000000;
                v0 = v1 | v0;
                sw(v0, s1, 0);
                lw(v0, s1, 12);
                sw(v0, s1, 8);
            }
            // 0x001b3264
            charge(ctx, 4);
            lw(v1, s1, 0);
            v0 = v1 & 0x1;
            if (v0 == 0) {
                // 0x001b3274
                charge(ctx, 3);
                lw(v0, s1, 20);
                if (v0 == 0) {
                    // 0x001b3280
                    charge(ctx, 3);
                    v0 = 0x20000000;
                    v0 = v1 | v0;
                    sw(v0, s1, 0);
                }
            }
            // 0x001b328c
            charge(ctx, 3);
            lw(v0, gp, f4::gpv::kFpcRequest);  // 0x7CE160
            if (v0 == 0) {
                // 0x001b3298
                charge(ctx, 4);
                lw(v0, s1, 2624);
                lw(a0, v0, 128);
                jal(ctx, 0x1B32A0u, gen::fn_H_Cdvd_Destroy_00100ec0);
            }
            // 0x001b32a8
            charge(ctx, 7);
            v0 = 0x3F800000;
            sw(v0, s1, 2592);
            sw(v0, s1, 2596);
            sw(v0, s1, 2600);
            v0 = 1;
        }
    } else {
        // 0x001b2f30
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x001b32c8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x001B32F0 sub_1B32F0 [K_Fldrc_FindFieldObjectFrame] -- 388 bytes; frame 0xB0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B32F0(res, resid, &collis) -> the frame index of field object `resid` among the record's clumps' user data
// ("per3FieldObjectResid", "per3FieldObjectType" != 1, "per3FieldObjectCollis" -> *collis), 0 when absent;
// K_Assert k_fldrc.c 1490 on an object without a resource id. Caller: the K_Cmd field-object commands (sub_1C4700).
void sub_1B32F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b32f0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
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
    s6 = 0;
    s1 = 0;
    for (;;) {
        // 0x001b3430
        charge(ctx, 4);
        lw(v0, s4, 20);
        v0 = sltu(s1, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001b3334
        charge(ctx, 11);
        v0 = sll(s1, 2);
        s5 = addu(s4, v0);
        lw(a0, s5, 24);
        a1 = 0x680000;
        a1 = addiu(a1, -29104);  // "per3FieldObjectType"
        jal(ctx, 0x1B3348u, gen::fn_sub_1A6C00_001a6c00);
        s7 = v0;
        s0 = 0;
        for (;;) {
            // 0x001b3420
            charge(ctx, 3);
            v0 = slt(s0, s7);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001b3360
            charge(ctx, 10);
            a0 = addiu(sp, 0xA0);
            lw(a1, s5, 24);
            a2 = 0x680000;
            a2 = addiu(a2, -29072);  // "per3FieldObjectResid"
            a3 = s0;
            jal(ctx, 0x1B3374u, gen::fn_sub_1A6E90_001a6e90);
            lw(v0, sp, 0xA0);
            if (v0 == 0) {
                // 0x001b3388
                charge(ctx, 5);
                a0 = 0x680000;
                a0 = addiu(a0, -29192);  // "k_fldrc.c"
                a1 = 1490;
                jal(ctx, 0x1B3394u, gen::fn_sub_19D3F0_0019d3f0);
            }
            // 0x001b339c
            charge(ctx, 17);
            a0 = addiu(sp, 0xA8);
            lw(a1, s5, 24);
            a2 = 0x680000;
            a2 = addiu(a2, -29104);  // "per3FieldObjectType"
            a3 = s0;
            jal(ctx, 0x1B33B0u, gen::fn_sub_1A6E90_001a6e90);
            a0 = addiu(sp, 0x98);
            lw(a1, s5, 24);
            a2 = 0x680000;
            a2 = addiu(a2, -29040);  // "per3FieldObjectCollis"
            a3 = s0;
            jal(ctx, 0x1B33CCu, gen::fn_sub_1A6E90_001a6e90);
            lw(v0, sp, 0x98);
            if (v0 == 0) {
                // 0x001b33f0
                charge(ctx, 1);
                sw(zero, s2, 0);
            } else {
                // 0x001b33e0
                charge(ctx, 4);
                v0 = 1;
                sw(v0, s2, 0);
            }
            // 0x001b33f4
            charge(ctx, 4);
            lw(v1, sp, 0xA8);
            v0 = 1;
            if (v1 != v0) {
                // 0x001b3404
                charge(ctx, 3);
                lw(v0, sp, 0xA0);
                if (s3 != v0) {
                    goto L_001b341c;
                }
                goto L_001b3410_9;
            }
        L_001b341c:
            charge(ctx, 1);
            s0 = addiu(s0, 1);
        }
        // 0x001b342c
        charge(ctx, 1);
        s1 = addiu(s1, 1);
    }
    // 0x001b3440 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    v0 = s6;
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
    return;
L_001b3410_9:
    charge(ctx, 3);
    lw(s6, sp, 0xAC);
    // 0x001b3440 (the shared epilogue, written out on this path)
    charge(ctx, 13);
    v0 = s6;
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x001B3480 sub_1B3480 [K_Fldrc_CreateFieldObjects] -- 1368 bytes; frame 0x210: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B3480(res): builds the record's field-object table (+280 count, 24-byte entries at +284) from the clumps' user
// data, one entry per object with a non-zero "per3FieldObjectId" (field4.h FldObject): +4 u16 resource id
// ("per3FieldObjectResid", K_Assert 1546 when 0), +2 u16 flags (2 with "per3FieldObjectCollis", or-ed with
// "per3FieldObjectAnim" for models), +0 u16 type ("per3FieldObjectType"): 0 a model "field/rmd/mMMM_ID.RMD" (from the
// .pac "field/pack/m..." with sub_316BD0, else read with sub_316B40) -> +12, 1 an EPL effect "field/effect/MMM_ID.EPL"
// (the request -> +20, K_Assert 1616; from the .pac cache when resident), 2 a shared object model
// "field/grmd/fobjID.RMD" (model id ID + 1000) -> +12; +8 the type's second word (the frame index of the object).
void sub_1B3480(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b3480
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x210);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    s3 = 0;
    for (;;) {
        // 0x001b39a4
        charge(ctx, 4);
        lw(v1, s4, 20);
        v1 = sltu(s3, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001b34ac
        charge(ctx, 11);
        v0 = sll(s3, 2);
        s1 = addu(s4, v0);
        lw(a0, s1, 24);
        a1 = 0x680000;
        a1 = addiu(a1, -29104);  // "per3FieldObjectType"
        jal(ctx, 0x1B34C0u, gen::fn_sub_1A6C00_001a6c00);
        s0 = v0;
        s2 = 0;
        for (;;) {
            // 0x001b3994
            charge(ctx, 3);
            v1 = slt(s2, s0);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001b34d8
            charge(ctx, 10);
            a0 = addiu(sp, 0x1F8);
            lw(a1, s1, 24);
            a2 = 0x680000;
            a2 = addiu(a2, -29008);  // "per3FieldObjectId"
            a3 = s2;
            jal(ctx, 0x1B34ECu, gen::fn_sub_1A6E90_001a6e90);
            lw(v1, sp, 0x1F8);
            if (v1 != 0) {
                // 0x001b3500
                charge(ctx, 10);
                a0 = addiu(sp, 0x1E8);
                lw(a1, s1, 24);
                a2 = 0x680000;
                a2 = addiu(a2, -29072);  // "per3FieldObjectResid"
                a3 = s2;
                jal(ctx, 0x1B3514u, gen::fn_sub_1A6E90_001a6e90);
                lw(v0, sp, 0x1E8);
                if (v0 == 0) {
                    // 0x001b3528
                    charge(ctx, 5);
                    a0 = 0x680000;
                    a0 = addiu(a0, -29192);  // "k_fldrc.c"
                    a1 = 1546;
                    jal(ctx, 0x1B3534u, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x001b353c
                charge(ctx, 17);
                lw(a0, sp, 0x1E8);
                lw(v1, s4, 280);
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                v0 = sll(v0, 3);
                v0 = addu(s4, v0);
                sh(a0, v0, 288);
                a0 = addiu(sp, 0x1E0);
                lw(a1, s1, 24);
                a2 = 0x680000;
                a2 = addiu(a2, -29040);  // "per3FieldObjectCollis"
                a3 = s2;
                jal(ctx, 0x1B356Cu, gen::fn_sub_1A6E90_001a6e90);
                lw(v0, sp, 0x1E0);
                if (v0 != 0) {
                    // 0x001b3580
                    charge(ctx, 7);
                    a0 = 2;
                    lw(v1, s4, 280);
                    v0 = sll(v1, 1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 3);
                    v0 = addu(s4, v0);
                    sh(a0, v0, 286);
                }
                // 0x001b359c
                charge(ctx, 17);
                a0 = addiu(sp, 0x200);
                lw(a1, s1, 24);
                a2 = 0x680000;
                a2 = addiu(a2, -29104);  // "per3FieldObjectType"
                a3 = s2;
                jal(ctx, 0x1B35B0u, gen::fn_sub_1A6E90_001a6e90);
                lw(a0, sp, 0x200);
                lw(v1, s4, 280);
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                v0 = sll(v0, 3);
                v0 = addu(s4, v0);
                sh(a0, v0, 284);
                lw(v1, sp, 0x200);
                if (v1 != 0) {
                    // 0x001b3730
                    charge(ctx, 3);
                    v0 = 1;
                    if (v1 != v0) {
                        // 0x001b389c
                        charge(ctx, 3);
                        v0 = 2;
                        if (v1 == v0) {
                            // 0x001b38a8
                            charge(ctx, 29);
                            a0 = addiu(sp, 0xA0);
                            a1 = 0x680000;
                            a1 = addiu(a1, -28880);  // "field/grmd/fobj"
                            jal(ctx, 0x1B38B4u, gen::fn_strcpy_00524270);
                            a0 = addiu(sp, 0x60);
                            a1 = 0x680000;
                            a1 = addiu(a1, -28968);  // "%03d.RMD"
                            lw(a2, sp, 0x1F8);
                            jal(ctx, 0x1B38CCu, gen::fn_sprintf_00523ac8);
                            a0 = addiu(sp, 0xA0);
                            a1 = addiu(sp, 0x60);
                            jal(ctx, 0x1B38DCu, gen::fn_strcat_00523e68);
                            lw(v0, sp, 0x1F8);
                            v0 = addiu(v0, 1000);
                            a1 = v0 & 0xFFFF;
                            a0 = 4;
                            a2 = addiu(sp, 0xA0);
                            a3 = 0;
                            jal(ctx, 0x1B38FCu, gen::fn_sub_316B40_00316b40);
                            lw(a0, s4, 280);
                            v1 = sll(a0, 1);
                            v1 = addu(v1, a0);
                            v1 = sll(v1, 3);
                            v1 = addu(s4, v1);
                            sw(v0, v1, 296);
                        }
                    } else {
                        // 0x001b373c
                        charge(ctx, 3);
                        lw(v0, gp, f4::gpv::kFpcRequest);  // 0x7CE160
                        if (v0 != 0) {
                            // 0x001b380c
                            charge(ctx, 36);
                            a0 = addiu(sp, 0x120);
                            a1 = 0x680000;
                            a1 = addiu(a1, -28904);  // "field/pack/"
                            jal(ctx, 0x1B3818u, gen::fn_strcpy_00524270);
                            lh(a2, s4, 4);
                            a0 = addiu(sp, 0xE0);
                            a1 = addiu(gp, -27312);  // "%03d_"
                            jal(ctx, 0x1B382Cu, gen::fn_sprintf_00523ac8);
                            a0 = addiu(sp, 0x120);
                            a1 = addiu(sp, 0xE0);
                            jal(ctx, 0x1B383Cu, gen::fn_strcat_00523e68);
                            a0 = addiu(sp, 0xE0);
                            a1 = 0x680000;
                            a1 = addiu(a1, -28920);  // "%03d.EPL"
                            lw(a2, sp, 0x1F8);
                            jal(ctx, 0x1B3854u, gen::fn_sprintf_00523ac8);
                            a0 = addiu(sp, 0x120);
                            a1 = addiu(sp, 0xE0);
                            jal(ctx, 0x1B3864u, gen::fn_strcat_00523e68);
                            a0 = addiu(sp, 0x120);
                            a1 = addiu(sp, 0x208);
                            jal(ctx, 0x1B3874u, gen::fn_H_Cdvd_CacheFindFile_001021c0);
                            lw(a0, s4, 280);
                            v1 = sll(a0, 1);
                            v1 = addu(v1, a0);
                            v1 = sll(v1, 3);
                            v1 = addu(s4, v1);
                            sw(v0, v1, 304);
                        } else {
                            // 0x001b3748
                            charge(ctx, 42);
                            a0 = addiu(sp, 0x120);
                            a1 = 0x680000;
                            a1 = addiu(a1, -28936);  // "field/effect/"
                            jal(ctx, 0x1B3754u, gen::fn_strcpy_00524270);
                            lh(a2, s4, 4);
                            a0 = addiu(sp, 0xE0);
                            a1 = addiu(gp, -27312);  // "%03d_"
                            jal(ctx, 0x1B3768u, gen::fn_sprintf_00523ac8);
                            a0 = addiu(sp, 0x120);
                            a1 = addiu(sp, 0xE0);
                            jal(ctx, 0x1B3778u, gen::fn_strcat_00523e68);
                            a0 = addiu(sp, 0xE0);
                            a1 = 0x680000;
                            a1 = addiu(a1, -28920);  // "%03d.EPL"
                            lw(a2, sp, 0x1F8);
                            jal(ctx, 0x1B3790u, gen::fn_sprintf_00523ac8);
                            a0 = addiu(sp, 0x120);
                            a1 = addiu(sp, 0xE0);
                            jal(ctx, 0x1B37A0u, gen::fn_strcat_00523e68);
                            a0 = addiu(sp, 0x120);
                            a1 = 0;
                            jal(ctx, 0x1B37B0u, gen::fn_H_Cdvd_Request_00100d80);
                            lw(a0, s4, 280);
                            v1 = sll(a0, 1);
                            v1 = addu(v1, a0);
                            v1 = sll(v1, 3);
                            v1 = addu(s4, v1);
                            sw(v0, v1, 304);
                            lw(v1, s4, 280);
                            v0 = sll(v1, 1);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 3);
                            v0 = addu(s4, v0);
                            lw(v0, v0, 304);
                            if (v0 == 0) {
                                // 0x001b37f0
                                charge(ctx, 7);
                                a0 = 0x680000;
                                a0 = addiu(a0, -29192);  // "k_fldrc.c"
                                a1 = 1616;
                                jal(ctx, 0x1B37FCu, gen::fn_sub_19D3F0_0019d3f0);
                            }
                        }
                    }
                } else {
                    // 0x001b35e0
                    charge(ctx, 3);
                    lw(v0, gp, f4::gpv::kFpcRequest);  // 0x7CE160
                    if (v0 != 0) {
                        // 0x001b3684
                        charge(ctx, 43);
                        a0 = addiu(sp, 0x1A0);
                        a1 = 0x680000;
                        a1 = addiu(a1, -28952);  // "field/pack/m"
                        jal(ctx, 0x1B3690u, gen::fn_strcpy_00524270);
                        lh(a2, s4, 4);
                        a0 = addiu(sp, 0x160);
                        a1 = addiu(gp, -27312);  // "%03d_"
                        jal(ctx, 0x1B36A4u, gen::fn_sprintf_00523ac8);
                        a0 = addiu(sp, 0x1A0);
                        a1 = addiu(sp, 0x160);
                        jal(ctx, 0x1B36B4u, gen::fn_strcat_00523e68);
                        a0 = addiu(sp, 0x160);
                        a1 = 0x680000;
                        a1 = addiu(a1, -28968);  // "%03d.RMD"
                        lw(a2, sp, 0x1F8);
                        jal(ctx, 0x1B36CCu, gen::fn_sprintf_00523ac8);
                        a0 = addiu(sp, 0x1A0);
                        a1 = addiu(sp, 0x160);
                        jal(ctx, 0x1B36DCu, gen::fn_strcat_00523e68);
                        a0 = addiu(sp, 0x1A0);
                        a1 = addiu(sp, 0x20C);
                        jal(ctx, 0x1B36ECu, gen::fn_H_Cdvd_CacheFindFile_001021c0);
                        lhu(a1, sp, 0x1F8);
                        a0 = 4;
                        a2 = v0;
                        lw(a3, sp, 0x20C);
                        t0 = 0;
                        jal(ctx, 0x1B3708u, gen::fn_sub_316BD0_00316bd0);
                        lw(a0, s4, 280);
                        v1 = sll(a0, 1);
                        v1 = addu(v1, a0);
                        v1 = sll(v1, 3);
                        v1 = addu(s4, v1);
                        sw(v0, v1, 296);
                    } else {
                        // 0x001b35ec
                        charge(ctx, 38);
                        a0 = addiu(sp, 0x1A0);
                        a1 = 0x680000;
                        a1 = addiu(a1, -28984);  // "field/rmd/m"
                        jal(ctx, 0x1B35F8u, gen::fn_strcpy_00524270);
                        lh(a2, s4, 4);
                        a0 = addiu(sp, 0x160);
                        a1 = addiu(gp, -27312);  // "%03d_"
                        jal(ctx, 0x1B360Cu, gen::fn_sprintf_00523ac8);
                        a0 = addiu(sp, 0x1A0);
                        a1 = addiu(sp, 0x160);
                        jal(ctx, 0x1B361Cu, gen::fn_strcat_00523e68);
                        a0 = addiu(sp, 0x160);
                        a1 = 0x680000;
                        a1 = addiu(a1, -28968);  // "%03d.RMD"
                        lw(a2, sp, 0x1F8);
                        jal(ctx, 0x1B3634u, gen::fn_sprintf_00523ac8);
                        a0 = addiu(sp, 0x1A0);
                        a1 = addiu(sp, 0x160);
                        jal(ctx, 0x1B3644u, gen::fn_strcat_00523e68);
                        lhu(a1, sp, 0x1F8);
                        a0 = 4;
                        a2 = addiu(sp, 0x1A0);
                        a3 = 0;
                        jal(ctx, 0x1B365Cu, gen::fn_sub_316B40_00316b40);
                        lw(a0, s4, 280);
                        v1 = sll(a0, 1);
                        v1 = addu(v1, a0);
                        v1 = sll(v1, 3);
                        v1 = addu(s4, v1);
                        sw(v0, v1, 296);
                    }
                }
                // 0x001b391c
                charge(ctx, 10);
                a0 = addiu(sp, 0x1F0);
                lw(a1, s1, 24);
                a2 = 0x680000;
                a2 = addiu(a2, -28864);  // "per3FieldObjectAnim"
                a3 = s2;
                jal(ctx, 0x1B3930u, gen::fn_sub_1A6E90_001a6e90);
                lw(v1, sp, 0x200);
                if (v1 == 0) {
                    // 0x001b3944
                    charge(ctx, 9);
                    lw(a0, s4, 280);
                    v1 = sll(a0, 1);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 3);
                    a1 = addu(s4, v1);
                    lhu(a0, sp, 0x1F0);
                    lhu(v1, a1, 286);
                    v1 = v1 | a0;
                    sh(v1, a1, 286);
                }
                // 0x001b3968
                charge(ctx, 10);
                lw(a1, sp, 0x204);
                lw(a0, s4, 280);
                v1 = sll(a0, 1);
                v1 = addu(v1, a0);
                v1 = sll(v1, 3);
                v1 = addu(s4, v1);
                sw(a1, v1, 292);
                lw(v1, s4, 280);
                v1 = addiu(v1, 1);
                sw(v1, s4, 280);
            }
            // 0x001b3990
            charge(ctx, 1);
            s2 = addiu(s2, 1);
        }
        // 0x001b39a0
        charge(ctx, 1);
        s3 = addiu(s3, 1);
    }
    // 0x001b39b4
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x210);
}

// 0x001B39E0 sub_1B39E0 [K_Fldrc_TryFinishFieldObjects] -- 684 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B39E0(res) -> 1 when every field object of the record is ready (models loaded, EPL files read); then places
// them: models attached at their frame's LTM (sub_318A70), lit (sub_319230 3) and animated (flag bit 0: sub_3189F0)
// or posed (sub_3182D0); EPLs created (sub_34FCD0) and moved to the frame; finally the file record (+2624) and its
// texture dictionary are released.
void sub_1B39E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x001b39e0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s0 = 0;
    for (;;) {
        // 0x001b3a98
        charge(ctx, 4);
        lw(v0, s3, 280);
        v0 = sltu(s0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001b3a0c
        charge(ctx, 7);
        v0 = sll(s0, 1);
        v0 = addu(v0, s0);
        v0 = sll(v0, 3);
        a0 = addu(s3, v0);
        lhu(v1, a0, 284);
        if (v1 != 0) {
            // 0x001b3a28
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                goto L_001b3a34;
            }
            // 0x001b3a54
            charge(ctx, 3);
            v0 = 1;
            if (v1 != v0) {
            L_001b3a94:
                charge(ctx, 1);
                s0 = addiu(s0, 1);
                continue;
            }
            // 0x001b3a60
            charge(ctx, 3);
            lw(v0, gp, f4::gpv::kFpcRequest);  // 0x7CE160
            if (v0 != 0) {
                goto L_001b3a94;
            }
            // 0x001b3a6c
            charge(ctx, 3);
            lw(a0, a0, 304);
            if (a0 == 0) {
                goto L_001b3a94;
            }
            // 0x001b3a78
            charge(ctx, 4);
            jal(ctx, 0x1B3A78u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                goto L_001b3a94;
            }
            goto L_001b3a88_9;
        }
    L_001b3a34:
        charge(ctx, 5);
        lw(a0, a0, 296);
        jal(ctx, 0x1B3A38u, gen::fn_sub_316F70_00316f70);
        if (v0 != 0) {
            goto L_001b3a94;
        }
        goto L_001b3a48_4;
    }
    // 0x001b3aa8
    charge(ctx, 3);
    s2 = 0;
    for (;;) {
        // 0x001b3c24
        charge(ctx, 4);
        lw(v0, s3, 280);
        v0 = sltu(s2, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001b3ab4
        charge(ctx, 7);
        v0 = sll(s2, 1);
        v0 = addu(v0, s2);
        v0 = sll(v0, 3);
        s1 = addu(s3, v0);
        lhu(v1, s1, 284);
        if (v1 != 0) {
            // 0x001b3ad0
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                goto L_001b3adc;
            }
            // 0x001b3b70
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x001b3b7c
                charge(ctx, 3);
                lw(v0, gp, f4::gpv::kFpcRequest);  // 0x7CE160
                if (v0 != 0) {
                    // 0x001b3be0
                    charge(ctx, 4);
                    s4 = addiu(s1, 304);
                    lw(a0, s1, 304);
                    if (a0 != 0) {
                        // 0x001b3bf0
                        charge(ctx, 12);
                        s0 = addiu(s1, 300);
                        jal(ctx, 0x1B3BF4u, gen::fn_sub_34FCD0_0034fcd0);
                        sw(v0, s0, 0);
                        lw(a0, s1, 292);
                        jal(ctx, 0x1B3C04u, gen::fn_sub_4CB2F0_004cb2f0);
                        lw(a0, s0, 0);
                        a1 = addiu(v0, 48);
                        jal(ctx, 0x1B3C14u, gen::fn_sub_34FDF0_0034fdf0);
                        sw(zero, s4, 0);
                    }
                } else {
                    // 0x001b3b88
                    charge(ctx, 4);
                    s0 = addiu(s1, 304);
                    lw(v0, s1, 304);
                    if (v0 != 0) {
                        // 0x001b3b98
                        charge(ctx, 18);
                        s4 = addiu(s1, 300);
                        lw(a0, v0, 272);
                        jal(ctx, 0x1B3BA0u, gen::fn_sub_34FCD0_0034fcd0);
                        sw(v0, s4, 0);
                        lw(a0, s1, 292);
                        jal(ctx, 0x1B3BB0u, gen::fn_sub_4CB2F0_004cb2f0);
                        lw(a0, s4, 0);
                        a1 = addiu(v0, 48);
                        jal(ctx, 0x1B3BC0u, gen::fn_sub_34FDF0_0034fdf0);
                        lw(a0, s0, 0);
                        jal(ctx, 0x1B3BCCu, gen::fn_H_Cdvd_Destroy_00100ec0);
                        sw(zero, s0, 0);
                    }
                }
            }
            goto L_001b3c20;
        }
    L_001b3adc:
        charge(ctx, 21);
        v0 = sll(s2, 1);
        v0 = addu(v0, s2);
        v0 = sll(v0, 3);
        s1 = addu(s3, v0);
        s0 = addiu(s1, 296);
        lw(a0, s1, 292);
        jal(ctx, 0x1B3AF4u, gen::fn_sub_4CB2F0_004cb2f0);
        lw(a0, s0, 0);
        a1 = v0;
        a2 = 0;
        jal(ctx, 0x1B3B08u, gen::fn_sub_318A70_00318a70);
        lw(a0, s0, 0);
        a1 = 3;
        jal(ctx, 0x1B3B18u, gen::fn_sub_319230_00319230);
        lhu(v0, s1, 286);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x001b3b4c
            charge(ctx, 9);
            lw(a0, s0, 0);
            a1 = 0;
            a2 = 0;
            a3 = 8;
            t0 = 1;
            jal(ctx, 0x1B3B60u, gen::fn_sub_3182D0_003182d0);
        } else {
            // 0x001b3b30
            charge(ctx, 7);
            mtc1(zero, f12);
            lw(a0, s0, 0);
            a1 = 0;
            jal(ctx, 0x1B3B3Cu, gen::fn_sub_3189F0_003189f0);
        }
    L_001b3c20:
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x001b3c34
    charge(ctx, 3);
    lw(v0, s3, 2624);
    if (v0 != 0) {
        // 0x001b3c40
        charge(ctx, 9);
        lw(a0, v0, 288);
        jal(ctx, 0x1B3C44u, gen::fn_sub_1A14C0_001a14c0);
        lw(a0, s3, 2624);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x1B3C58u, v0.u());
        sw(zero, s3, 2624);
    }
    // 0x001b3c64
    charge(ctx, 1);
    v0 = 1;
    // 0x001b3c68 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_001b3a48_4:
    charge(ctx, 3);
    v0 = 0;
    // 0x001b3c68 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_001b3a88_9:
    charge(ctx, 3);
    v0 = 0;
    // 0x001b3c68 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001B3C90 sub_1B3C90 [K_Fldrc_DestroyFieldResource] -- 448 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B3C90(res): frees a field resource record: its worlds (collision world removed from the main world when flags
// bit 0) or clumps, the draw clumps and their atomic lists, the field objects (models sub_3174E0, EPLs sub_34FCF0),
// the UV animation dictionary, the hit data (+2620) and the record itself.
void sub_1B3C90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b3c90
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v0, a0, 0);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x001b3d08
        charge(ctx, 6);
        lw(a0, s1, 12);
        jal(ctx, 0x1B3D0Cu, gen::fn_sub_1A7710_001a7710);
        lw(a0, s1, 8);
        if (a0 != 0) {
            // 0x001b3d20
            charge(ctx, 2);
            jal(ctx, 0x1B3D20u, gen::fn_sub_491EA0_00491ea0);
        }
        // 0x001b3d28
        charge(ctx, 3);
        lw(a0, s1, 16);
        if (a0 != 0) {
            // 0x001b3d34
            charge(ctx, 2);
            jal(ctx, 0x1B3D34u, gen::fn_sub_491EA0_00491ea0);
        }
    } else {
        // 0x001b3cb8
        charge(ctx, 3);
        lw(a0, s1, 8);
        if (a0 != 0) {
            // 0x001b3cc4
            charge(ctx, 3);
            lw(v0, s1, 12);
            if (a0 != v0) {
                // 0x001b3cd0
                charge(ctx, 2);
                jal(ctx, 0x1B3CD0u, gen::fn_sub_49A290_0049a290);
            }
        }
        // 0x001b3cd8
        charge(ctx, 3);
        lw(a0, s1, 12);
        if (a0 != 0) {
            // 0x001b3ce4
            charge(ctx, 2);
            jal(ctx, 0x1B3CE4u, gen::fn_sub_49A290_0049a290);
        }
        // 0x001b3cec
        charge(ctx, 3);
        lw(a0, s1, 16);
        if (a0 != 0) {
            // 0x001b3cf8
            charge(ctx, 4);
            jal(ctx, 0x1B3CF8u, gen::fn_sub_49A290_0049a290);
        }
    }
    // 0x001b3d3c
    charge(ctx, 3);
    s2 = 0;
    for (;;) {
        // 0x001b3d6c
        charge(ctx, 4);
        lw(v0, s1, 20);
        v0 = sltu(s2, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001b3d48
        charge(ctx, 9);
        v0 = sll(s2, 2);
        s0 = addu(s1, v0);
        lw(a0, s0, 152);
        jal(ctx, 0x1B3D54u, gen::fn_sub_1A7710_001a7710);
        lw(a0, s0, 24);
        jal(ctx, 0x1B3D60u, gen::fn_sub_491EA0_00491ea0);
        s2 = addiu(s2, 1);
    }
    // 0x001b3d7c
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x001b3de0
        charge(ctx, 4);
        lw(v0, s1, 280);
        v0 = sltu(s0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001b3d88
        charge(ctx, 7);
        v0 = sll(s0, 1);
        v0 = addu(v0, s0);
        v0 = sll(v0, 3);
        a0 = addu(s1, v0);
        lhu(v1, a0, 284);
        if (v1 != 0) {
            // 0x001b3da4
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                goto L_001b3db0;
            }
            // 0x001b3dc4
            charge(ctx, 3);
            v0 = 1;
            if (v1 == v0) {
                // 0x001b3dd0
                charge(ctx, 3);
                lw(a0, a0, 300);
                jal(ctx, 0x1B3DD4u, gen::fn_sub_34FCF0_0034fcf0);
            }
            goto L_001b3ddc;
        }
    L_001b3db0:
        charge(ctx, 5);
        lw(a0, a0, 296);
        jal(ctx, 0x1B3DB4u, gen::fn_sub_3174E0_003174e0);
    L_001b3ddc:
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x001b3df0
    charge(ctx, 3);
    lw(a0, s1, 2588);
    if (a0 != 0) {
        // 0x001b3dfc
        charge(ctx, 2);
        jal(ctx, 0x1B3DFCu, gen::fn_sub_48DA30_0048da30);
    }
    // 0x001b3e04
    charge(ctx, 3);
    lw(a0, s1, 2620);
    if (a0 != 0) {
        // 0x001b3e10
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x1B3E18u, v0.u());
    }
    // 0x001b3e20
    charge(ctx, 12);
    a0 = s1;
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1B3E2Cu, v0.u());
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001B4E00 sub_1B4E00 [K_Fldrc_TranslateFieldResource] -- 1024 bytes; frame 0xF0: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_1B4E00(res, offset): moves a (cloned) field resource by offset: the collision and shadow clumps' frames
// (translation += offset, RwFrameUpdateObjects), every draw clump, every model object (sub_318A30) and every EPL
// object (rotated by the block rotation of 0x678F58 and offset). Used for Tartarus blocks.
void sub_1B4E00(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x001b4e00
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
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
    lw(v1, a0, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x001b4e3c
        charge(ctx, 3);
        lw(v1, s3, 8);
        if (v1 != 0) {
            // 0x001b4e48
            charge(ctx, 38);
            lw(s0, v1, 4);
            a0 = s0;
            jal(ctx, 0x1B4E50u, gen::fn_sub_4CB2F0_004cb2f0);
            lwc1(f2, v0, 48);
            lwc1(f1, v0, 52);
            lwc1(f0, v0, 56);
            swc1(f2, sp, 0xE0);
            swc1(f1, sp, 0xE4);
            swc1(f0, sp, 0xE8);
            lwc1(f1, sp, 0xE0);
            lwc1(f0, s2, 0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xE0);
            lwc1(f1, s2, 4);
            lwc1(f0, sp, 0xE4);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0xE4);
            lwc1(f1, s2, 8);
            lwc1(f0, sp, 0xE8);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0xE8);
            lwc1(f2, sp, 0xE0);
            lwc1(f1, sp, 0xE4);
            lwc1(f0, sp, 0xE8);
            swc1(f2, s0, 64);
            swc1(f1, s0, 68);
            swc1(f0, s0, 72);
            a0 = addiu(sp, 0xD0);
            jal(ctx, 0x1B4EBCu, gen::fn_sub_4C2CC0_004c2cc0);
            a0 = addiu(s0, 16);
            a1 = addiu(sp, 0xD0);
            jal(ctx, 0x1B4ECCu, gen::fn_sub_4C2D20_004c2d20);
            a0 = s0;
            jal(ctx, 0x1B4ED8u, gen::fn_sub_4CB270_004cb270);
        }
        // 0x001b4ee0
        charge(ctx, 3);
        lw(v1, s3, 16);
        if (v1 != 0) {
            // 0x001b4eec
            charge(ctx, 38);
            lw(s0, v1, 4);
            a0 = s0;
            jal(ctx, 0x1B4EF4u, gen::fn_sub_4CB2F0_004cb2f0);
            lwc1(f2, v0, 48);
            lwc1(f1, v0, 52);
            lwc1(f0, v0, 56);
            swc1(f2, sp, 0xC0);
            swc1(f1, sp, 0xC4);
            swc1(f0, sp, 0xC8);
            lwc1(f1, sp, 0xC0);
            lwc1(f0, s2, 0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xC0);
            lwc1(f1, s2, 4);
            lwc1(f0, sp, 0xC4);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0xC4);
            lwc1(f1, s2, 8);
            lwc1(f0, sp, 0xC8);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0xC8);
            lwc1(f2, sp, 0xC0);
            lwc1(f1, sp, 0xC4);
            lwc1(f0, sp, 0xC8);
            swc1(f2, s0, 64);
            swc1(f1, s0, 68);
            swc1(f0, s0, 72);
            a0 = addiu(sp, 0xB0);
            jal(ctx, 0x1B4F60u, gen::fn_sub_4C2CC0_004c2cc0);
            a0 = addiu(s0, 16);
            a1 = addiu(sp, 0xB0);
            jal(ctx, 0x1B4F70u, gen::fn_sub_4C2D20_004c2d20);
            a0 = s0;
            jal(ctx, 0x1B4F7Cu, gen::fn_sub_4CB270_004cb270);
        }
    }
    // 0x001b4f84
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x001b5040
        charge(ctx, 4);
        lw(v1, s3, 20);
        v1 = sltu(s0, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001b4f90
        charge(ctx, 5);
        v1 = sll(s0, 2);
        v1 = addu(s3, v1);
        lw(v1, v1, 24);
        if (v1 != 0) {
            // 0x001b4fa4
            charge(ctx, 38);
            lw(s1, v1, 4);
            a0 = s1;
            jal(ctx, 0x1B4FACu, gen::fn_sub_4CB2F0_004cb2f0);
            lwc1(f2, v0, 48);
            lwc1(f1, v0, 52);
            lwc1(f0, v0, 56);
            swc1(f2, sp, 0xA0);
            swc1(f1, sp, 0xA4);
            swc1(f0, sp, 0xA8);
            lwc1(f1, sp, 0xA0);
            lwc1(f0, s2, 0);
            add_s(f0, f1, f0);
            swc1(f0, sp, 0xA0);
            lwc1(f1, s2, 4);
            lwc1(f0, sp, 0xA4);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0xA4);
            lwc1(f1, s2, 8);
            lwc1(f0, sp, 0xA8);
            add_s(f0, f0, f1);
            swc1(f0, sp, 0xA8);
            lwc1(f2, sp, 0xA0);
            lwc1(f1, sp, 0xA4);
            lwc1(f0, sp, 0xA8);
            swc1(f2, s1, 64);
            swc1(f1, s1, 68);
            swc1(f0, s1, 72);
            a0 = addiu(sp, 0x90);
            jal(ctx, 0x1B5018u, gen::fn_sub_4C2CC0_004c2cc0);
            a0 = addiu(s1, 16);
            a1 = addiu(sp, 0x90);
            jal(ctx, 0x1B5028u, gen::fn_sub_4C2D20_004c2d20);
            a0 = s1;
            jal(ctx, 0x1B5034u, gen::fn_sub_4CB270_004cb270);
        }
        // 0x001b503c
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x001b5050
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x001b51c8
        charge(ctx, 4);
        lw(v1, s3, 280);
        v1 = sltu(s0, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001b505c
        charge(ctx, 7);
        v1 = sll(s0, 1);
        v1 = addu(v1, s0);
        v1 = sll(v1, 3);
        a1 = addu(s3, v1);
        lhu(a0, a1, 284);
        if (a0 != 0) {
            // 0x001b5078
            charge(ctx, 3);
            v1 = 2;
            if (a0 == v1) {
                goto L_001b5084;
            }
            // 0x001b50a0
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                // 0x001b50ac
                charge(ctx, 70);
                v0 = 0x680000;
                ld(v1, v0, -28840);  // 0x678F58
                v0 = 0x680000;
                lwc1(f0, v0, -28832);  // 0x678F60
                sd(v1, sp, 0x80);
                swc1(f0, sp, 0x88);
                jal(ctx, 0x1B50C4u, gen::fn_sub_4C38C0_004c38c0);
                s1 = v0;
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
                a0 = s1;
                a1 = addiu(sp, 0x80);
                mov_s(f12, f20);
                a2 = 2;
                jal(ctx, 0x1B5128u, gen::fn_sub_4C31B0_004c31b0);
                v0 = sll(s0, 1);
                v0 = addu(v0, s0);
                v0 = sll(v0, 3);
                s4 = addu(s3, v0);
                lw(a0, s4, 292);
                jal(ctx, 0x1B5144u, gen::fn_sub_4CB2F0_004cb2f0);
                a0 = addiu(sp, 0x70);
                lwc1(f2, v0, 48);
                lwc1(f1, v0, 52);
                lwc1(f0, v0, 56);
                swc1(f2, sp, 0x70);
                swc1(f1, sp, 0x74);
                swc1(f0, sp, 0x78);
                a1 = a0;
                a2 = s1;
                jal(ctx, 0x1B5170u, gen::fn_sub_4C6BE0_004c6be0);
                lwc1(f1, sp, 0x70);
                lwc1(f0, s2, 0);
                add_s(f0, f1, f0);
                swc1(f0, sp, 0x70);
                lwc1(f1, s2, 4);
                lwc1(f0, sp, 0x74);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x74);
                lwc1(f1, s2, 8);
                lwc1(f0, sp, 0x78);
                add_s(f0, f0, f1);
                swc1(f0, sp, 0x78);
                lw(a0, s4, 300);
                a1 = addiu(sp, 0x70);
                jal(ctx, 0x1B51B0u, gen::fn_sub_34FDF0_0034fdf0);
                a0 = s1;
                jal(ctx, 0x1B51BCu, gen::fn_sub_4C3880_004c3880);
            }
            goto L_001b51c4;
        }
    L_001b5084:
        charge(ctx, 7);
        lw(a0, a1, 296);
        a1 = s2;
        a2 = 2;
        jal(ctx, 0x1B5090u, gen::fn_sub_318A30_00318a30);
    L_001b51c4:
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x001b51d8
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xF0);
}

// 0x001B5200 sub_1B5200 [K_Fldrc_RotateFieldResource] -- 380 bytes; frame 0x50: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_1B5200(res, quarterTurns): rotates every frame of a cloned field resource about the axis at 0x678F68 by
// the angle in $f12 (RwFrameRotate sub_4CB890 combine 2), the model objects by the same angle and re-anchors EPLs.
void sub_1B5200(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f20{ctx, 20};
    // 0x001b5200
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a0;
    mov_s(f20, f12);
    a1 = addiu(sp, 0x40);
    v1 = 0x680000;
    ld(a2, v1, -28824);  // 0x678F68
    v1 = 0x680000;
    lwc1(f0, v1, -28816);  // 0x678F70
    sd(a2, sp, 0x40);
    swc1(f0, sp, 0x48);
    lw(v1, a0, 0);
    v1 = v1 & 0x1;
    if (v1 == 0) {
        // 0x001b5248
        charge(ctx, 3);
        lw(v1, s1, 8);
        if (v1 != 0) {
            // 0x001b5254
            charge(ctx, 4);
            lw(a0, v1, 4);
            a2 = 2;
            jal(ctx, 0x1B525Cu, gen::fn_sub_4CB890_004cb890);
        }
        // 0x001b5264
        charge(ctx, 3);
        lw(v1, s1, 16);
        if (v1 != 0) {
            // 0x001b5270
            charge(ctx, 6);
            lw(a0, v1, 4);
            a1 = addiu(sp, 0x40);
            mov_s(f12, f20);
            a2 = 2;
            jal(ctx, 0x1B5280u, gen::fn_sub_4CB890_004cb890);
        }
    }
    // 0x001b5288
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x001b52c4
        charge(ctx, 4);
        lw(v1, s1, 20);
        v1 = sltu(s0, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001b5294
        charge(ctx, 5);
        v1 = sll(s0, 2);
        v1 = addu(s1, v1);
        lw(v1, v1, 24);
        if (v1 != 0) {
            // 0x001b52a8
            charge(ctx, 6);
            lw(a0, v1, 4);
            a1 = addiu(sp, 0x40);
            mov_s(f12, f20);
            a2 = 2;
            jal(ctx, 0x1B52B8u, gen::fn_sub_4CB890_004cb890);
        }
        // 0x001b52c0
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x001b52d4
    charge(ctx, 3);
    s0 = 0;
    for (;;) {
        // 0x001b5350
        charge(ctx, 4);
        lw(v1, s1, 280);
        v1 = sltu(s0, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001b52e0
        charge(ctx, 7);
        v1 = sll(s0, 1);
        v1 = addu(v1, s0);
        v1 = sll(v1, 3);
        a1 = addu(s1, v1);
        lhu(a0, a1, 284);
        if (a0 != 0) {
            // 0x001b52fc
            charge(ctx, 3);
            v1 = 2;
            if (a0 == v1) {
                goto L_001b5308;
            }
            // 0x001b5328
            charge(ctx, 3);
            v1 = 1;
            if (a0 == v1) {
                // 0x001b5334
                charge(ctx, 6);
                mtc1(zero, f12);
                lw(a0, a1, 300);
                mov_s(f13, f20);
                mov_s(f14, f12);
                jal(ctx, 0x1B5344u, gen::fn_sub_34FE30_0034fe30);
            }
            goto L_001b534c;
        }
    L_001b5308:
        charge(ctx, 8);
        lw(a0, a1, 296);
        a1 = addiu(sp, 0x40);
        mov_s(f12, f20);
        a2 = 2;
        jal(ctx, 0x1B5318u, gen::fn_sub_318A50_00318a50);
    L_001b534c:
        charge(ctx, 1);
        s0 = addiu(s0, 1);
    }
    // 0x001b5360
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001B5380 sub_1B5380 [K_Fldrc_CloneFieldResource] -- 656 bytes; frame 0x80: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_1B5380(src, offset, quarterTurns) -> a copy of a loaded Tartarus block resource (flags | 2 = clone): its
// collision / shadow clumps and draw clumps cloned (sub_491CC0), the field-object table copied with its models and
// EPLs cloned, the scale copied; then rotated (sub_1B5200) and translated (sub_1B4E00). NULL for a world-based
// resource (flags bit 0). Caller: the block builder sub_1BB300.
void sub_1B5380(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x001b5380
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s4 = a0;
    s3 = a1;
    v0 = 0x42B40000;
    mtc1(v0, f1);
    if (i64(a2) < 0) {
        // 0x001b53d0
        charge(ctx, 7);
        v1 = srl(a2, 1);
        v0 = a2 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, f0);
        cvt_s_w(f0, f0);
        add_s(f0, f0, f0);
    } else {
        // 0x001b53bc
        charge(ctx, 5);
        mtc1(a2, f0);
        cvt_s_w(f0, f0);
    }
    // 0x001b53ec
    charge(ctx, 5);
    mul_s(f20, f1, f0);
    lw(v0, s4, 0);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        // 0x001b540c
        charge(ctx, 18);
        a0 = 1;
        a1 = 2636;
        a2 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, 388);  // 0x960184
        jalr(ctx, 0x1B5420u, v0.u());
        s2 = v0;
        lw(v1, s4, 0);
        v1 = v1 | 0x2;
        sw(v1, v0, 0);
        lh(v1, s4, 4);
        sh(v1, v0, 4);
        lh(v1, s4, 6);
        sh(v1, v0, 6);
        lw(a0, s4, 8);
        if (a0 != 0) {
            // 0x001b5454
            charge(ctx, 7);
            jal(ctx, 0x1B5454u, gen::fn_sub_491CC0_00491cc0);
            sw(v0, s2, 8);
            a0 = v0;
            jal(ctx, 0x1B5464u, gen::fn_sub_1A7570_001a7570);
            sw(v0, s2, 12);
        }
        // 0x001b5470
        charge(ctx, 3);
        lw(a0, s4, 16);
        if (a0 != 0) {
            // 0x001b547c
            charge(ctx, 3);
            jal(ctx, 0x1B547Cu, gen::fn_sub_491CC0_00491cc0);
            sw(v0, s2, 16);
        }
        // 0x001b5488
        charge(ctx, 5);
        lw(v0, s4, 20);
        sw(v0, s2, 20);
        s0 = 0;
        for (;;) {
            // 0x001b54d8
            charge(ctx, 4);
            lw(v0, s4, 20);
            v0 = sltu(s0, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001b549c
            charge(ctx, 5);
            v1 = sll(s0, 2);
            v0 = addu(s4, v1);
            lw(a0, v0, 24);
            if (a0 != 0) {
                // 0x001b54b0
                charge(ctx, 9);
                s5 = addu(s2, v1);
                s1 = addiu(s5, 24);
                jal(ctx, 0x1B54B8u, gen::fn_sub_491CC0_00491cc0);
                sw(v0, s1, 0);
                a0 = v0;
                jal(ctx, 0x1B54C8u, gen::fn_sub_1A7570_001a7570);
                sw(v0, s5, 152);
            }
            // 0x001b54d4
            charge(ctx, 1);
            s0 = addiu(s0, 1);
        }
        // 0x001b54e8
        charge(ctx, 5);
        lw(v0, s4, 280);
        sw(v0, s2, 280);
        s1 = 0;
        for (;;) {
            // 0x001b5594
            charge(ctx, 4);
            lw(v0, s4, 280);
            v0 = sltu(s1, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001b54fc
            charge(ctx, 9);
            v0 = sll(s1, 1);
            v0 = addu(v0, s1);
            v0 = sll(v0, 3);
            t0 = addu(s4, v0);
            a3 = addiu(t0, 284);
            s0 = addu(s2, v0);
            a1 = addiu(s0, 284);
            a0 = 3;
            a2 = a3;
            for (;;) {
                // 0x001b5520
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
            // 0x001b5544
            charge(ctx, 3);
            lhu(v1, a3, 0);
            if (v1 != 0) {
                // 0x001b5550
                charge(ctx, 3);
                v0 = 2;
                if (v1 == v0) {
                    goto L_001b555c;
                }
                // 0x001b5574
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x001b5580
                    charge(ctx, 4);
                    lw(a0, t0, 300);
                    jal(ctx, 0x1B5584u, gen::fn_sub_34FD50_0034fd50);
                    sw(v0, s0, 300);
                }
                goto L_001b5590;
            }
        L_001b555c:
            charge(ctx, 6);
            lw(a0, t0, 296);
            jal(ctx, 0x1B5560u, gen::fn_sub_317450_00317450);
            sw(v0, s0, 296);
        L_001b5590:
            charge(ctx, 1);
            s1 = addiu(s1, 1);
        }
        // 0x001b55a4
        charge(ctx, 16);
        lwc1(f2, s4, 2592);
        lwc1(f1, s4, 2596);
        lwc1(f0, s4, 2600);
        swc1(f2, s2, 2592);
        swc1(f1, s2, 2596);
        swc1(f0, s2, 2600);
        a0 = s2;
        mov_s(f12, f20);
        jal(ctx, 0x1B55C4u, gen::fn_sub_1B5200_001b5200);
        a0 = s2;
        a1 = s3;
        mov_s(f12, f20);
        jal(ctx, 0x1B55D8u, gen::fn_sub_1B4E00_001b4e00);
        v0 = s2;
    } else {
        // 0x001b5400
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001b55e4 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x001B5610 sub_1B5610 [K_Fldrc_ApplyMatPropToField] -- 216 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B5610(res, scale): applies a material-property scale (sub_1B60A0 / sub_1B60D0: the "per3modelMatProp"
// ambient/diffuse/specular floats) to the record's world (flags bit 0), its draw clumps and every type-10 scene
// resource's model.
void sub_1B5610(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b5610
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    a0 = 10;
    jal(ctx, 0x1B5634u, gen::fn_sub_3B5D50_003b5d50);
    s0 = v0;
    lw(v1, s3, 0);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x001b5650
        charge(ctx, 4);
        lw(a0, s3, 8);
        a1 = s2;
        jal(ctx, 0x1B5658u, gen::fn_sub_1B60D0_001b60d0);
    }
    // 0x001b5660
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x001b5688
        charge(ctx, 4);
        lw(v1, s3, 20);
        v1 = sltu(s1, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001b566c
        charge(ctx, 7);
        v0 = sll(s1, 2);
        v0 = addu(s3, v0);
        lw(a0, v0, 24);
        a1 = s2;
        jal(ctx, 0x1B567Cu, gen::fn_sub_1B60A0_001b60a0);
        s1 = addiu(s1, 1);
    }
    // 0x001b5698
    charge(ctx, 2);
    for (;;) {
        // 0x001b56c0
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001b56a0
        charge(ctx, 8);
        lw(a0, s0, 260);
        jal(ctx, 0x1B56A4u, gen::fn_sub_318B80_00318b80);
        a0 = v0;
        a1 = s2;
        jal(ctx, 0x1B56B4u, gen::fn_sub_1B60A0_001b60a0);
        lw(s0, s0, 248);
    }
    // 0x001b56c8
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001B56F0 sub_1B56F0 [K_Fldrc_ApplyMatColorToField] -- 340 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B56F0(res, rgbaScale): the same for the "per3modelMatColor" material colour (sub_1B5E30 / sub_1B5E60), and the
// type-10 scene models get the colour as four bytes (scale * 255 + 0.5 through ACC).
void sub_1B56F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x001b56f0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a0;
    s2 = a1;
    a0 = 10;
    jal(ctx, 0x1B5714u, gen::fn_sub_3B5D50_003b5d50);
    s0 = v0;
    lw(v1, s3, 0);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x001b5730
        charge(ctx, 4);
        lw(a0, s3, 8);
        a1 = s2;
        jal(ctx, 0x1B5738u, gen::fn_sub_1B5E60_001b5e60);
    }
    // 0x001b5740
    charge(ctx, 3);
    s1 = 0;
    for (;;) {
        // 0x001b5768
        charge(ctx, 4);
        lw(v1, s3, 20);
        v1 = sltu(s1, v1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001b574c
        charge(ctx, 7);
        v0 = sll(s1, 2);
        v0 = addu(s3, v0);
        lw(a0, v0, 24);
        a1 = s2;
        jal(ctx, 0x1B575Cu, gen::fn_sub_1B5E30_001b5e30);
        s1 = addiu(s1, 1);
    }
    // 0x001b5778
    charge(ctx, 2);
    for (;;) {
        // 0x001b581c
        charge(ctx, 2);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001b5780
        charge(ctx, 39);
        v0 = 0x437F0000;
        mtc1(v0, f3);
        lwc1(f0, s2, 0);
        v0 = 0x3F000000;
        mtc1(v0, f2);
        mtc1(zero, f1);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        sb(v0, sp, 0x5C);
        lwc1(f0, s2, 4);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        sb(v0, sp, 0x5D);
        lwc1(f0, s2, 8);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        sb(v0, sp, 0x5E);
        lwc1(f0, s2, 12);
        adda_s(f1, f2);
        madd_s(f0, f3, f0);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        sb(v0, sp, 0x5F);
        lw(a0, s0, 260);
        a1 = addiu(sp, 0x5C);
        jal(ctx, 0x1B5810u, gen::fn_sub_318AD0_00318ad0);
        lw(s0, s0, 248);
    }
    // 0x001b5824
    charge(ctx, 8);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001B5850 sub_1B5850 [K_FieldFilter_Update] -- 36 bytes; frame 0x10: ra sp+0x0
// sub_1B5850(task) -> 0: the "field filter" task's update (sub_1D4610).
void sub_1B5850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b5850
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1B5858u, gen::fn_sub_1D4610_001d4610);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B5880 sub_1B5880 [K_FieldFilter_Destroy] -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1B5880(task): frees the "field filter" work.
void sub_1B5880(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b5880
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, f4::kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1B5894u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B58B0 sub_1B58B0 [K_FieldFilter_CreateTask] -- 156 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B58B0(parent) -> the "field filter" task (kwlnTaskCreate, priority 4197, 20-byte work, +8 = 1, +12 = 200);
// MT_Scene_Load creates it per scene.
void sub_1B58B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b58b0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 1;
    a1 = 20;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1B58D8u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001b58f8
        charge(ctx, 15);
        a0 = s1;
        a1 = 0x680000;
        a1 = addiu(a1, -28808);  // "field filter"
        a2 = 4197;
        a3 = 0x1B0000;
        a3 = addiu(a3, 22608);  // &sub_1B5850
        t0 = 0x1B0000;
        t0 = addiu(t0, 22656);  // &sub_1B5880
        t1 = s0;
        jal(ctx, 0x1B591Cu, gen::fn_kwlnTaskCreate_00194b20);
        v1 = 1;
        sw(v1, s0, 8);
        v1 = 200;
        sw(v1, s0, 12);
    } else {
        // 0x001b58ec
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001b5934 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001B5950 sub_1B5950 [K_FieldFilter_SetColor] -- 52 bytes; frame 0x10: ra sp+0x0
// sub_1B5950(task, rgba): work +4 = rgba, then sub_1D50C0(rgba, +8, +16).
void sub_1B5950(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b5950
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, f4::kTaskWork);
    sw(a1, v0, 4);
    a0 = a1;
    lw(a1, v0, 8);
    lw(a2, v0, 16);
    jal(ctx, 0x1B596Cu, gen::fn_sub_1D50C0_001d50c0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B5990 sub_1B5990 [K_FieldFilter_SetAlpha] -- 48 bytes; frame 0x10: ra sp+0x0
// sub_1B5990(task, a): work +8 = a, then sub_1D50C0(+4, a, ..).
void sub_1B5990(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b5990
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, f4::kTaskWork);
    sw(a1, v0, 8);
    lw(a0, v0, 4);
    lw(a2, v0, 16);
    jal(ctx, 0x1B59A8u, gen::fn_sub_1D50C0_001d50c0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B59C0 sub_1B59C0 [K_FieldFilter_SetMode] -- 52 bytes; frame 0x10: ra sp+0x0
// sub_1B59C0(task, m): work +16 = m, then sub_1D50C0(+4, +8, m).
void sub_1B59C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b59c0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a1;
    lw(v0, a0, f4::kTaskWork);
    sw(a2, v0, 16);
    lw(a0, v0, 4);
    lw(a1, v0, 8);
    jal(ctx, 0x1B59DCu, gen::fn_sub_1D50C0_001d50c0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B5A00 sub_1B5A00 [K_FieldFilter_SetFade] -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1B5A00(task, v): work +12 = v, then sub_1D5130(v).
void sub_1B5A00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b5a00
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, f4::kTaskWork);
    sw(a1, v0, 12);
    a0 = a1;
    jal(ctx, 0x1B5A14u, gen::fn_sub_1D5130_001d5130);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B5A30 sub_1B5A30 [K_MatColor_Init] -- 172 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B5A30(material): gives a material its "per3modelMatColor" user-data entry (when missing) holding its current
// colour as a packed RGBA u32 (bytes +4..+7).
void sub_1B5A30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b5a30
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a1 = 0x680000;
    a1 = addiu(a1, -28784);  // "per3modelMatColor"
    jal(ctx, 0x1B5A4Cu, gen::fn_sub_1A64F0_001a64f0);
    if (v0 == 0) {
        // 0x001b5a5c
        charge(ctx, 26);
        lbu(v0, s0, 7);
        v1 = sll(v0, 24);
        lbu(v0, s0, 4);
        v0 = sll(v0, 16);
        v1 = v1 | v0;
        lbu(v0, s0, 5);
        v0 = sll(v0, 8);
        v1 = v0 | v1;
        lbu(v0, s0, 6);
        s1 = v0 | v1;
        a0 = s0;
        a1 = 0x680000;
        a1 = addiu(a1, -28784);  // "per3modelMatColor"
        a2 = 1;
        a3 = a2;
        jal(ctx, 0x1B5A98u, gen::fn_sub_48EE70_0048ee70);
        a0 = s0;
        a1 = v0;
        jal(ctx, 0x1B5AA8u, gen::fn_sub_48EED0_0048eed0);
        a0 = v0;
        a1 = 0;
        a2 = s1;
        jal(ctx, 0x1B5ABCu, gen::fn_sub_48EFA0_0048efa0);
    }
    // 0x001b5ac4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001B5AE0 sub_1B5AE0 [K_MatColor_Set] -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1B5AE0(material, rgba*): stores the four colour bytes as the material's "per3modelMatColor" u32.
void sub_1B5AE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b5ae0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    a1 = 0x680000;
    a1 = addiu(a1, -28784);  // "per3modelMatColor"
    jal(ctx, 0x1B5AF8u, gen::fn_sub_1A6350_001a6350);
    lbu(v1, s0, 3);
    a0 = sll(v1, 24);
    lbu(v1, s0, 0);
    v1 = sll(v1, 16);
    a0 = a0 | v1;
    lbu(v1, s0, 1);
    v1 = sll(v1, 8);
    a0 = v1 | a0;
    lbu(v1, s0, 2);
    a2 = v1 | a0;
    a0 = v0;
    a1 = 0;
    jal(ctx, 0x1B5B30u, gen::fn_sub_48EFA0_0048efa0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001B5B50 sub_1B5B50 [K_MatColor_ScaleCb] -- 668 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B5B50(material, rgbaScale*) -> material: RpGeometryForAllMaterials callback: creates the colour entry when
// missing, then sets the material colour to the stored colour times the scale, each channel clamped to 255.
void sub_1B5B50(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x001b5b50
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a1 = 0x680000;
    a1 = addiu(a1, -28784);  // "per3modelMatColor"
    jal(ctx, 0x1B5B74u, gen::fn_sub_1A64F0_001a64f0);
    if (v0 == 0) {
        // 0x001b5b84
        charge(ctx, 26);
        lbu(v0, s1, 7);
        v1 = sll(v0, 24);
        lbu(v0, s1, 4);
        v0 = sll(v0, 16);
        v1 = v1 | v0;
        lbu(v0, s1, 5);
        v0 = sll(v0, 8);
        v1 = v0 | v1;
        lbu(v0, s1, 6);
        s2 = v0 | v1;
        a0 = s1;
        a1 = 0x680000;
        a1 = addiu(a1, -28784);  // "per3modelMatColor"
        a2 = 1;
        a3 = a2;
        jal(ctx, 0x1B5BC0u, gen::fn_sub_48EE70_0048ee70);
        a0 = s1;
        a1 = v0;
        jal(ctx, 0x1B5BD0u, gen::fn_sub_48EED0_0048eed0);
        a0 = v0;
        a1 = 0;
        a2 = s2;
        jal(ctx, 0x1B5BE4u, gen::fn_sub_48EFA0_0048efa0);
    }
    // 0x001b5bec
    charge(ctx, 8);
    a0 = s1;
    a1 = 0x680000;
    a1 = addiu(a1, -28784);  // "per3modelMatColor"
    jal(ctx, 0x1B5BF8u, gen::fn_sub_1A64F0_001a64f0);
    v1 = 1;
    if (v0 == v1) {
        // 0x001b5c0c
        charge(ctx, 9);
        a0 = s1;
        a1 = 0x680000;
        a1 = addiu(a1, -28784);  // "per3modelMatColor"
        jal(ctx, 0x1B5C18u, gen::fn_sub_1A6400_001a6400);
        v1 = srl(v0, 16);
        v1 = v1 & 0xFF;
        if (i64(v1) < 0) {
            // 0x001b5c44
            charge(ctx, 7);
            a0 = srl(v1, 1);
            v1 = v1 & 0x1;
            a0 = a0 | v1;
            mtc1(a0, f0);
            cvt_s_w(f1, f0);
            add_s(f1, f1, f1);
        } else {
            // 0x001b5c30
            charge(ctx, 5);
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
        }
        // 0x001b5c60
        charge(ctx, 8);
        lwc1(f0, s0, 0);
        mul_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(a2, f0);
        v1 = srl(v0, 8);
        v1 = v1 & 0xFF;
        if (i64(v1) < 0) {
            // 0x001b5c94
            charge(ctx, 7);
            a0 = srl(v1, 1);
            v1 = v1 & 0x1;
            a0 = a0 | v1;
            mtc1(a0, f0);
            cvt_s_w(f1, f0);
            add_s(f1, f1, f1);
        } else {
            // 0x001b5c80
            charge(ctx, 5);
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
        }
        // 0x001b5cb0
        charge(ctx, 7);
        lwc1(f0, s0, 4);
        mul_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(a1, f0);
        v1 = v0 & 0xFF;
        if (i64(v1) < 0) {
            // 0x001b5ce0
            charge(ctx, 7);
            a0 = srl(v1, 1);
            v1 = v1 & 0x1;
            a0 = a0 | v1;
            mtc1(a0, f0);
            cvt_s_w(f1, f0);
            add_s(f1, f1, f1);
        } else {
            // 0x001b5ccc
            charge(ctx, 5);
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
        }
        // 0x001b5cfc
        charge(ctx, 8);
        lwc1(f0, s0, 8);
        mul_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(a0, f0);
        v0 = srl(v0, 24);
        v0 = v0 & 0xFF;
        if (i64(v0) < 0) {
            // 0x001b5d30
            charge(ctx, 7);
            v1 = srl(v0, 1);
            v0 = v0 & 0x1;
            v1 = v1 | v0;
            mtc1(v1, f0);
            cvt_s_w(f1, f0);
            add_s(f1, f1, f1);
        } else {
            // 0x001b5d1c
            charge(ctx, 5);
            mtc1(v0, f0);
            cvt_s_w(f1, f0);
        }
        // 0x001b5d4c
        charge(ctx, 7);
        lwc1(f0, s0, 12);
        mul_s(f0, f1, f0);
        cvt_w_s(f0, f0);
        mfc1(v0, f0);
        at = sltiu(a2, 256);
        if (at == 0) {
            // 0x001b5d68
            charge(ctx, 1);
            a2 = 255;
        }
        // 0x001b5d6c
        charge(ctx, 4);
        sb(a2, sp, 0x4C);
        at = sltiu(a1, 256);
        if (at == 0) {
            // 0x001b5d7c
            charge(ctx, 1);
            a1 = 255;
        }
        // 0x001b5d80
        charge(ctx, 4);
        sb(a1, sp, 0x4D);
        at = sltiu(a0, 256);
        if (at == 0) {
            // 0x001b5d90
            charge(ctx, 1);
            a0 = 255;
        }
        // 0x001b5d94
        charge(ctx, 4);
        sb(a0, sp, 0x4E);
        at = sltiu(v0, 256);
        if (at == 0) {
            // 0x001b5da4
            charge(ctx, 1);
            v0 = 255;
        }
        // 0x001b5da8
        charge(ctx, 9);
        sb(v0, sp, 0x4F);
        lbu(a1, sp, 0x4C);
        lbu(a0, sp, 0x4D);
        lbu(v1, sp, 0x4E);
        lbu(v0, sp, 0x4F);
        sb(a1, s1, 4);
        sb(a0, s1, 5);
        sb(v1, s1, 6);
        sb(v0, s1, 7);
    }
    // 0x001b5dcc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = s1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001B5DF0 sub_1B5DF0 [K_MatColor_GeometryCb] -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1B5DF0(atomic, scale) -> atomic: runs sub_1B5B50 over the atomic's geometry's materials.
void sub_1B5DF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b5df0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a2 = a1;
    lw(a0, a0, 24);
    a1 = 0x1B0000;
    a1 = addiu(a1, 23376);  // &sub_1B5B50
    jal(ctx, 0x1B5E10u, gen::fn_sub_4932C0_004932c0);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001B5E30 sub_1B5E30 [K_MatColor_ApplyToClump] -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1B5E30(clump, scale): RpClumpForAllAtomics(clump, sub_1B5DF0, scale).
void sub_1B5E30(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b5e30
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a1;
    a1 = 0x1B0000;
    a1 = addiu(a1, 24048);  // &sub_1B5DF0
    jal(ctx, 0x1B5E44u, gen::fn_sub_4916D0_004916d0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B5E60 sub_1B5E60 [K_MatColor_ApplyToWorld] -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1B5E60(world, scale): RpWorldForAllMaterials-style walk with sub_1B5B50.
void sub_1B5E60(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b5e60
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a1;
    a1 = 0x1B0000;
    a1 = addiu(a1, 23376);  // &sub_1B5B50
    jal(ctx, 0x1B5E74u, gen::fn_sub_49A7C0_0049a7c0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B5E90 sub_1B5E90 [K_MatProp_ScaleCb] -- 456 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B5E90(material, scale*) -> material: creates the "per3modelMatProp" entry (3 floats) when missing; sets the
// material's surface properties (+12 ambient, +16 specular, +20 diffuse) to the stored values times the scale,
// each clamped to 1.0.
void sub_1B5E90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x001b5e90
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    s3 = a1;
    a1 = 0x680000;
    a1 = addiu(a1, -28752);  // "per3modelMatProp"
    jal(ctx, 0x1B5EB8u, gen::fn_sub_1A64F0_001a64f0);
    if (v0 == 0) {
        // 0x001b5ec8
        charge(ctx, 28);
        s1 = addiu(s0, 12);
        a0 = s0;
        a1 = 0x680000;
        a1 = addiu(a1, -28752);  // "per3modelMatProp"
        a2 = 2;
        a3 = 3;
        jal(ctx, 0x1B5EE0u, gen::fn_sub_48EE70_0048ee70);
        a0 = s0;
        a1 = v0;
        jal(ctx, 0x1B5EF0u, gen::fn_sub_48EED0_0048eed0);
        s2 = v0;
        a0 = s2;
        a1 = 0;
        lwc1(f12, s1, 0);
        jal(ctx, 0x1B5F08u, gen::fn_sub_48EFC0_0048efc0);
        a0 = s2;
        a1 = 1;
        lwc1(f12, s1, 4);
        jal(ctx, 0x1B5F1Cu, gen::fn_sub_48EFC0_0048efc0);
        a0 = s2;
        a1 = 2;
        lwc1(f12, s1, 8);
        jal(ctx, 0x1B5F30u, gen::fn_sub_48EFC0_0048efc0);
    }
    // 0x001b5f38
    charge(ctx, 8);
    a0 = s0;
    a1 = 0x680000;
    a1 = addiu(a1, -28752);  // "per3modelMatProp"
    jal(ctx, 0x1B5F44u, gen::fn_sub_1A6350_001a6350);
    s1 = v0;
    if (s1 != 0) {
        // 0x001b5f58
        charge(ctx, 32);
        a0 = s1;
        a1 = 0;
        jal(ctx, 0x1B5F60u, gen::fn_sub_48EF60_0048ef60);
        swc1(f0, sp, 0x50);
        a0 = s1;
        a1 = 1;
        jal(ctx, 0x1B5F74u, gen::fn_sub_48EF60_0048ef60);
        swc1(f0, sp, 0x54);
        a0 = s1;
        a1 = 2;
        jal(ctx, 0x1B5F88u, gen::fn_sub_48EF60_0048ef60);
        swc1(f0, sp, 0x58);
        lwc1(f2, sp, 0x50);
        lwc1(f1, s3, 0);
        mul_s(f3, f2, f1);
        swc1(f3, sp, 0x50);
        lwc1(f2, sp, 0x54);
        lwc1(f1, s3, 4);
        mul_s(f1, f2, f1);
        swc1(f1, sp, 0x54);
        lwc1(f1, s3, 8);
        mul_s(f0, f0, f1);
        swc1(f0, sp, 0x58);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        c_le_s(f3, f0);
        if (!cond(ctx)) {
            // 0x001b5fd8
            charge(ctx, 1);
            swc1(f0, sp, 0x50);
        }
        // 0x001b5fdc
        charge(ctx, 7);
        lwc1(f1, sp, 0x54);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        c_le_s(f1, f0);
        if (!cond(ctx)) {
            // 0x001b5ff8
            charge(ctx, 1);
            swc1(f0, sp, 0x54);
        }
        // 0x001b5ffc
        charge(ctx, 7);
        lwc1(f1, sp, 0x58);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        c_le_s(f1, f0);
        if (!cond(ctx)) {
            // 0x001b6018
            charge(ctx, 1);
            swc1(f0, sp, 0x58);
        }
        // 0x001b601c
        charge(ctx, 6);
        lwc1(f2, sp, 0x50);
        lwc1(f1, sp, 0x54);
        lwc1(f0, sp, 0x58);
        swc1(f2, s0, 12);
        swc1(f1, s0, 16);
        swc1(f0, s0, 20);
    }
    // 0x001b6034 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = s0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001B6060 sub_1B6060 [K_MatProp_GeometryCb] -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1B6060(atomic, scale) -> atomic: runs sub_1B5E90 over the atomic's geometry's materials.
void sub_1B6060(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b6060
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a2 = a1;
    lw(a0, a0, 24);
    a1 = 0x1B0000;
    a1 = addiu(a1, 24208);  // &sub_1B5E90
    jal(ctx, 0x1B6080u, gen::fn_sub_4932C0_004932c0);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001B60A0 sub_1B60A0 [K_MatProp_ApplyToClump] -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1B60A0(clump, scale): RpClumpForAllAtomics(clump, sub_1B6060, scale).
void sub_1B60A0(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b60a0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a1;
    a1 = 0x1B0000;
    a1 = addiu(a1, 24672);  // &sub_1B6060
    jal(ctx, 0x1B60B4u, gen::fn_sub_4916D0_004916d0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B60D0 sub_1B60D0 [K_MatProp_ApplyToWorld] -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1B60D0(world, scale): the world walk with sub_1B5E90.
void sub_1B60D0(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b60d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a2 = a1;
    a1 = 0x1B0000;
    a1 = addiu(a1, 24208);  // &sub_1B5E90
    jal(ctx, 0x1B60E4u, gen::fn_sub_49A7C0_0049a7c0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B6100 sub_1B6100 [K_Fldrc_RequestEnvFile] -- 236 bytes; frame 0xA0: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1B6100(sub) -> the request of the scene's ENV file "field/env/fMMM_SSS.ENV" (SSS = the scene sub-id; fixed floors
// 51..58 use major - 30 with sub 0), 1 when the .pac is resident (the file is then taken from it), 0 for no file /
// no scene (major -1).
void sub_1B6100(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b6100
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
    lw(v1, v0, f4::scene::kMajor);
    v0 = si(-1);
    if (v1 != v0) {
        // 0x001b6130
        charge(ctx, 4);
        jal(ctx, 0x1B6130u, gen::fn_sub_1B0910_001b0910);
        if (v0 != 0) {
            // 0x001b61d4
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x001b6140
            charge(ctx, 13);
            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            a0 = addiu(sp, 0x20);
            a1 = 0x680000;
            a1 = addiu(a1, -28720);  // "field/env/f%03d_%03d.ENV"
            lw(a2, v0, f4::scene::kMajor);
            a3 = s0;
            jal(ctx, 0x1B6158u, gen::fn_sprintf_00523ac8);
            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            lw(v1, v0, f4::scene::kMajor);
            v0 = slti(v1, 51);
            if (v0 == 0) {
                // 0x001b6174
                charge(ctx, 3);
                at = slti(v1, 59);
                if (at != 0) {
                    // 0x001b6180
                    charge(ctx, 7);
                    a2 = addiu(v1, -30);
                    a0 = addiu(sp, 0x20);
                    a1 = 0x680000;
                    a1 = addiu(a1, -28720);  // "field/env/f%03d_%03d.ENV"
                    a3 = 0;
                    jal(ctx, 0x1B6194u, gen::fn_sprintf_00523ac8);
                }
            }
            // 0x001b619c
            charge(ctx, 5);
            a0 = addiu(sp, 0x20);
            jal(ctx, 0x1B61A0u, gen::fn_H_Cdvd_FileExists_001008b0);
            if (v0 != 0) {
                // 0x001b61bc
                charge(ctx, 6);
                a0 = addiu(sp, 0x20);
                a1 = 0;
                jal(ctx, 0x1B61C4u, gen::fn_H_Cdvd_Request_00100d80);
            } else {
                // 0x001b61b0
                charge(ctx, 3);
                v0 = 0;
            }
        }
    } else {
        // 0x001b6124
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001b61d8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x001B61F0 sub_1B61F0 [K_Fldrc_ApplyEnvFile] -- 3252 bytes; frame 0xD0: ra sp+0x70, s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_1B61F0(request, sub) -> 1 when the ENV data is applied (0 while loading). The ENV file (from the .pac cache
// "field/pack/fMMM_SSS.ENV" or the loaded request): +4 version (0x10000..0x10004); fog / clear colours bytes
// +8..+11 (sub_19FDD0..sub_19FEC0) and +12..+14 (camera clear colours sub_1985B0 / sub_1985E0, kept in
// 0x7CE0D4..0x7CE0F4; +15 == 1 enables), the far plane +16 (camera +136), v1.4: +24 fog distance and +508.. a second
// clear colour; the light set: the ambient / directional light records +28 / +44 / +64 (sub_19FD40 / 70 / A0) and
// the type-5 scene light's colours / matrices; v1.1: per field resource the scale +304.. and the material
// colour / property scales (sub_1B56F0 / sub_1B5610). "CAUTION!! READ OLD VER ENV DATA" for v1.0 files.
void sub_1B61F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20};
    // 0x001b61f0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s2 = a0;
    s0 = a1;
    if (s2 != 0) {
        // 0x001b6230
        charge(ctx, 4);
        jal(ctx, 0x1B6230u, gen::fn_sub_1B0910_001b0910);
        if (v0 != 0) {
            // 0x001b6830
            charge(ctx, 13);
            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            a0 = addiu(sp, 0x80);
            a1 = 0x680000;
            a1 = addiu(a1, -28656);  // "field/pack/f%03d_%03d.ENV"
            lw(a2, v0, f4::scene::kMajor);
            a3 = s0;
            jal(ctx, 0x1B6848u, gen::fn_sprintf_00523ac8);
            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            lw(v1, v0, f4::scene::kMajor);
            v0 = slti(v1, 51);
            if (v0 == 0) {
                // 0x001b6864
                charge(ctx, 3);
                at = slti(v1, 59);
                if (at != 0) {
                    // 0x001b6870
                    charge(ctx, 7);
                    a2 = addiu(v1, -30);
                    a0 = addiu(sp, 0x80);
                    a1 = 0x680000;
                    a1 = addiu(a1, -28656);  // "field/pack/f%03d_%03d.ENV"
                    a3 = 0;
                    jal(ctx, 0x1B6884u, gen::fn_sprintf_00523ac8);
                }
            }
            // 0x001b688c
            charge(ctx, 7);
            a0 = addiu(sp, 0x80);
            a1 = addiu(sp, 0xCC);
            jal(ctx, 0x1B6894u, gen::fn_H_Cdvd_CacheFindFile_001021c0);
            s0 = v0;
            if (s0 != 0) {
                // 0x001b68a8
                charge(ctx, 24);
                a0 = 4;
                jal(ctx, 0x1B68ACu, gen::fn_sub_3B5D50_003b5d50);
                s3 = v0;
                a0 = 5;
                jal(ctx, 0x1B68BCu, gen::fn_sub_3B5D50_003b5d50);
                s1 = v0;
                lbu(a0, s0, 8);
                jal(ctx, 0x1B68CCu, gen::fn_sub_19FDD0_0019fdd0);
                lbu(a0, s0, 9);
                jal(ctx, 0x1B68D8u, gen::fn_sub_19FE20_0019fe20);
                lbu(a0, s0, 10);
                jal(ctx, 0x1B68E4u, gen::fn_sub_19FE70_0019fe70);
                lbu(a0, s0, 11);
                jal(ctx, 0x1B68F0u, gen::fn_sub_19FEC0_0019fec0);
                lbu(v1, s0, 15);
                v0 = 1;
                if (v1 != v0) {
                    // 0x001b6914
                    charge(ctx, 1);
                    sw(zero, gp, -19484);  // 0x7CE0D4
                } else {
                    // 0x001b6908
                    charge(ctx, 3);
                    sw(v0, gp, -19484);  // 0x7CE0D4
                }
                // 0x001b6918
                charge(ctx, 44);
                lbu(v0, s0, 12);
                sb(v0, gp, -19480);  // 0x7CE0D8
                lbu(v0, s0, 13);
                sb(v0, gp, -19476);  // 0x7CE0DC
                lbu(v0, s0, 14);
                sb(v0, gp, -19472);  // 0x7CE0E0
                sb(zero, gp, -19468);  // 0x7CE0E4
                lbu(v0, s0, 12);
                sb(v0, gp, -19464);  // 0x7CE0E8
                lbu(v0, s0, 13);
                sb(v0, gp, -19460);  // 0x7CE0EC
                lbu(v0, s0, 14);
                sb(v0, gp, -19456);  // 0x7CE0F0
                sb(zero, gp, -19452);  // 0x7CE0F4
                lbu(a0, s0, 12);
                lbu(a1, s0, 13);
                lbu(a2, s0, 14);
                a3 = 0;
                jal(ctx, 0x1B6960u, gen::fn_sub_1985B0_001985b0);
                lbu(a0, s0, 12);
                lbu(a1, s0, 13);
                lbu(a2, s0, 14);
                a3 = 0;
                jal(ctx, 0x1B6978u, gen::fn_sub_1985E0_001985e0);
                jal(ctx, 0x1B6980u, gen::fn_sub_198590_00198590);
                a0 = v0;
                lwc1(f12, s0, 20);
                jal(ctx, 0x1B6990u, gen::fn_sub_4C9DB0_004c9db0);
                lwc1(f20, s0, 16);
                jal(ctx, 0x1B699Cu, gen::fn_sub_198590_00198590);
                swc1(f20, v0, 136);
                jal(ctx, 0x1B69A8u, gen::fn_sub_198590_00198590);
                lw(v0, s0, 4);
                at = 0x10000;
                at = at | 0x4;
                at = sltu(v0, at);
                if (at == 0) {
                    // 0x001b69c8
                    charge(ctx, 7);
                    lwc1(f20, s0, 24);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    c_le_s(f20, f0);
                    if (!cond(ctx)) {
                        // 0x001b69e4
                        charge(ctx, 6);
                        jal(ctx, 0x1B69E4u, gen::fn_sub_198590_00198590);
                        a0 = v0;
                        mov_s(f12, f20);
                        jal(ctx, 0x1B69F4u, gen::fn_sub_4C9D70_004c9d70);
                    }
                    // 0x001b69fc
                    charge(ctx, 7);
                    lwc1(f1, s0, 24);
                    v0 = 0x42480000;
                    mtc1(v0, f0);
                    c_eq_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x001b6a18
                        charge(ctx, 7);
                        jal(ctx, 0x1B6A18u, gen::fn_sub_198590_00198590);
                        v1 = 0x42C80000;
                        mtc1(v1, f12);
                        a0 = v0;
                        jal(ctx, 0x1B6A2Cu, gen::fn_sub_4C9D70_004c9d70);
                    }
                    // 0x001b6a34
                    charge(ctx, 4);
                    lbu(v1, s0, 511);
                    v0 = 255;
                    if (v1 == v0) {
                        // 0x001b6a44
                        charge(ctx, 12);
                        lbu(a0, s0, 508);
                        lbu(a1, s0, 509);
                        lbu(a2, s0, 510);
                        a3 = 0;
                        jal(ctx, 0x1B6A54u, gen::fn_sub_1985B0_001985b0);
                        lbu(a0, s0, 508);
                        lbu(a1, s0, 509);
                        lbu(a2, s0, 510);
                        a3 = 0;
                        jal(ctx, 0x1B6A6Cu, gen::fn_sub_1985E0_001985e0);
                    }
                }
                // 0x001b6a74
                charge(ctx, 24);
                jal(ctx, 0x1B6A74u, gen::fn_sub_19FD40_0019fd40);
                lwc1(f3, s0, 28);
                lwc1(f2, s0, 32);
                lwc1(f1, s0, 36);
                lwc1(f0, s0, 40);
                swc1(f3, v0, 0);
                swc1(f2, v0, 4);
                swc1(f1, v0, 8);
                swc1(f0, v0, 12);
                jal(ctx, 0x1B6A9Cu, gen::fn_sub_19FD70_0019fd70);
                lwc1(f3, s0, 44);
                lwc1(f2, s0, 48);
                lwc1(f1, s0, 52);
                lwc1(f0, s0, 56);
                swc1(f3, v0, 0);
                swc1(f2, v0, 4);
                swc1(f1, v0, 8);
                swc1(f0, v0, 12);
                jal(ctx, 0x1B6AC4u, gen::fn_sub_19FDA0_0019fda0);
                a2 = addiu(s0, 64);
                a1 = 8;
                for (;;) {
                    // 0x001b6ad4
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
                // 0x001b6af8
                charge(ctx, 2);
                if (s1 != 0) {
                    // 0x001b6b00
                    charge(ctx, 19);
                    lwc1(f3, s0, 128);
                    lwc1(f2, s0, 132);
                    lwc1(f1, s0, 136);
                    lwc1(f0, s0, 140);
                    swc1(f3, s1, 256);
                    swc1(f2, s1, 260);
                    swc1(f1, s1, 264);
                    swc1(f0, s1, 268);
                    lwc1(f3, s0, 144);
                    lwc1(f2, s0, 148);
                    lwc1(f1, s0, 152);
                    lwc1(f0, s0, 156);
                    swc1(f3, s1, 272);
                    swc1(f2, s1, 276);
                    swc1(f1, s1, 280);
                    swc1(f0, s1, 284);
                    a2 = addiu(s0, 160);
                    a1 = addiu(s1, 288);
                    a0 = 8;
                    for (;;) {
                        // 0x001b6b4c
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
                    // 0x001b6b70
                    charge(ctx, 11);
                    lwc1(f3, s0, 224);
                    lwc1(f2, s0, 228);
                    lwc1(f1, s0, 232);
                    lwc1(f0, s0, 236);
                    swc1(f3, s1, 352);
                    swc1(f2, s1, 356);
                    swc1(f1, s1, 360);
                    swc1(f0, s1, 364);
                    a2 = addiu(s0, 240);
                    a1 = addiu(s1, 368);
                    a0 = 8;
                    for (;;) {
                        // 0x001b6b9c
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
                }
                // 0x001b6bc0
                charge(ctx, 6);
                lw(v0, s0, 4);
                at = 0x10000;
                at = at | 0x1;
                at = sltu(v0, at);
                if (at == 0) {
                    // 0x001b6bd8
                    charge(ctx, 3);
                    s4 = 0;
                    for (;;) {
                        // 0x001b6c40
                        charge(ctx, 6);
                        jal(ctx, 0x1B6C40u, gen::fn_K_Field_Get_001b9120);
                        lw(v0, v0, f4::fld::kResCount);
                        v0 = slt(s4, v0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001b6be4
                        charge(ctx, 23);
                        s2 = sll(s4, 2);
                        jal(ctx, 0x1B6BE8u, gen::fn_K_Field_Get_001b9120);
                        v0 = addu(v0, s2);
                        lw(v0, v0, f4::fld::kRes);
                        lwc1(f2, s0, 304);
                        lwc1(f1, s0, 308);
                        lwc1(f0, s0, 312);
                        swc1(f2, v0, 2592);
                        swc1(f1, v0, 2596);
                        swc1(f0, v0, 2600);
                        jal(ctx, 0x1B6C10u, gen::fn_K_Field_Get_001b9120);
                        s1 = addu(v0, s2);
                        jal(ctx, 0x1B6C1Cu, gen::fn_K_Field_Get_001b9120);
                        v0 = addu(v0, s2);
                        lw(v0, v0, f4::fld::kRes);
                        lw(a0, s1, f4::fld::kRes);
                        a1 = addiu(v0, 2592);
                        jal(ctx, 0x1B6C34u, gen::fn_sub_1B5610_001b5610);
                        s4 = addiu(s4, 1);
                    }
                }
                // 0x001b6c58
                charge(ctx, 6);
                lw(v0, s0, 4);
                at = 0x10000;
                at = at | 0x2;
                at = sltu(v0, at);
                if (at == 0) {
                    // 0x001b6c70
                    charge(ctx, 2);
                    if (s3 != 0) {
                        // 0x001b6c78
                        charge(ctx, 19);
                        lwc1(f3, s0, 316);
                        lwc1(f2, s0, 320);
                        lwc1(f1, s0, 324);
                        lwc1(f0, s0, 328);
                        swc1(f3, s3, 256);
                        swc1(f2, s3, 260);
                        swc1(f1, s3, 264);
                        swc1(f0, s3, 268);
                        lwc1(f3, s0, 332);
                        lwc1(f2, s0, 336);
                        lwc1(f1, s0, 340);
                        lwc1(f0, s0, 344);
                        swc1(f3, s3, 272);
                        swc1(f2, s3, 276);
                        swc1(f1, s3, 280);
                        swc1(f0, s3, 284);
                        a2 = addiu(s0, 352);
                        a1 = addiu(s3, 288);
                        a0 = 8;
                        for (;;) {
                            // 0x001b6cc4
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
                        // 0x001b6ce8
                        charge(ctx, 11);
                        lwc1(f3, s0, 416);
                        lwc1(f2, s0, 420);
                        lwc1(f1, s0, 424);
                        lwc1(f0, s0, 428);
                        swc1(f3, s3, 352);
                        swc1(f2, s3, 356);
                        swc1(f1, s3, 360);
                        swc1(f0, s3, 364);
                        a2 = addiu(s0, 432);
                        a1 = addiu(s3, 368);
                        a0 = 8;
                        for (;;) {
                            // 0x001b6d14
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
                    }
                }
                // 0x001b6d38
                charge(ctx, 6);
                lw(v0, s0, 4);
                at = 0x10000;
                at = at | 0x3;
                at = sltu(v0, at);
                if (at == 0) {
                    // 0x001b6d50
                    charge(ctx, 11);
                    a0 = 1;
                    jal(ctx, 0x1B6D54u, gen::fn_sub_3B5D50_003b5d50);
                    s3 = v0;
                    a0 = 3;
                    jal(ctx, 0x1B6D64u, gen::fn_sub_3B5D50_003b5d50);
                    s2 = v0;
                    s1 = 0;
                    for (;;) {
                        // 0x001b6dac
                        charge(ctx, 6);
                        jal(ctx, 0x1B6DACu, gen::fn_K_Field_Get_001b9120);
                        lw(v0, v0, f4::fld::kResCount);
                        v0 = slt(s1, v0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001b6d7c
                        charge(ctx, 12);
                        jal(ctx, 0x1B6D7Cu, gen::fn_K_Field_Get_001b9120);
                        v1 = sll(s1, 2);
                        v0 = addu(v0, v1);
                        lw(v0, v0, f4::fld::kRes);
                        lwc1(f2, s0, 496);
                        lwc1(f1, s0, 500);
                        lwc1(f0, s0, 504);
                        swc1(f2, v0, 2604);
                        swc1(f1, v0, 2608);
                        swc1(f0, v0, 2612);
                        s1 = addiu(s1, 1);
                    }
                    // 0x001b6dc4
                    charge(ctx, 2);
                    for (;;) {
                        // 0x001b6df4
                        charge(ctx, 2);
                        if (s3 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001b6dcc
                        charge(ctx, 10);
                        lw(a0, s3, 296);
                        jal(ctx, 0x1B6DD0u, gen::fn_sub_318B80_00318b80);
                        a0 = v0;
                        a1 = 0x1B0000;
                        a1 = addiu(a1, 24672);  // &sub_1B6060
                        a2 = addiu(s0, 496);
                        jal(ctx, 0x1B6DE8u, gen::fn_sub_4916D0_004916d0);
                        lw(s3, s3, 248);
                    }
                    // 0x001b6dfc
                    charge(ctx, 2);
                    for (;;) {
                        // 0x001b6e2c
                        charge(ctx, 2);
                        if (s2 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001b6e04
                        charge(ctx, 10);
                        lw(a0, s2, 296);
                        jal(ctx, 0x1B6E08u, gen::fn_sub_318B80_00318b80);
                        a0 = v0;
                        a1 = 0x1B0000;
                        a1 = addiu(a1, 24672);  // &sub_1B6060
                        a2 = addiu(s0, 496);
                        jal(ctx, 0x1B6E20u, gen::fn_sub_4916D0_004916d0);
                        lw(s2, s2, 248);
                    }
                }
                // 0x001b6e34
                charge(ctx, 6);
                lw(v0, s0, 4);
                at = 0x10000;
                at = at | 0x4;
                at = sltu(v0, at);
                if (at != 0) {
                    // 0x001b6e4c
                    charge(ctx, 7);
                    a0 = 0;
                    a1 = 0;
                    a2 = 376;
                    a3 = 0x680000;
                    a3 = addiu(a3, -28688);  // "CAUTION!! READ OLD VER ENV DATA"
                    jal(ctx, 0x1B6E60u, gen::fn_sub_1A1540_001a1540);
                }
            }
            // 0x001b6e68
            charge(ctx, 3);
            v0 = 1;
        } else {
            // 0x001b6240
            charge(ctx, 5);
            a0 = s2;
            jal(ctx, 0x1B6244u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 == 0) {
                // 0x001b6e74
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x001b6254
                charge(ctx, 25);
                lw(s1, s2, 272);
                a0 = 4;
                jal(ctx, 0x1B625Cu, gen::fn_sub_3B5D50_003b5d50);
                s0 = v0;
                a0 = 5;
                jal(ctx, 0x1B626Cu, gen::fn_sub_3B5D50_003b5d50);
                s3 = v0;
                lbu(a0, s1, 8);
                jal(ctx, 0x1B627Cu, gen::fn_sub_19FDD0_0019fdd0);
                lbu(a0, s1, 9);
                jal(ctx, 0x1B6288u, gen::fn_sub_19FE20_0019fe20);
                lbu(a0, s1, 10);
                jal(ctx, 0x1B6294u, gen::fn_sub_19FE70_0019fe70);
                lbu(a0, s1, 11);
                jal(ctx, 0x1B62A0u, gen::fn_sub_19FEC0_0019fec0);
                lbu(v1, s1, 15);
                v0 = 1;
                if (v1 != v0) {
                    // 0x001b62c4
                    charge(ctx, 1);
                    sw(zero, gp, -19484);  // 0x7CE0D4
                } else {
                    // 0x001b62b8
                    charge(ctx, 3);
                    sw(v0, gp, -19484);  // 0x7CE0D4
                }
                // 0x001b62c8
                charge(ctx, 44);
                lbu(v0, s1, 12);
                sb(v0, gp, -19480);  // 0x7CE0D8
                lbu(v0, s1, 13);
                sb(v0, gp, -19476);  // 0x7CE0DC
                lbu(v0, s1, 14);
                sb(v0, gp, -19472);  // 0x7CE0E0
                sb(zero, gp, -19468);  // 0x7CE0E4
                lbu(v0, s1, 12);
                sb(v0, gp, -19464);  // 0x7CE0E8
                lbu(v0, s1, 13);
                sb(v0, gp, -19460);  // 0x7CE0EC
                lbu(v0, s1, 14);
                sb(v0, gp, -19456);  // 0x7CE0F0
                sb(zero, gp, -19452);  // 0x7CE0F4
                lbu(a0, s1, 12);
                lbu(a1, s1, 13);
                lbu(a2, s1, 14);
                a3 = 0;
                jal(ctx, 0x1B6310u, gen::fn_sub_1985B0_001985b0);
                lbu(a0, s1, 12);
                lbu(a1, s1, 13);
                lbu(a2, s1, 14);
                a3 = 0;
                jal(ctx, 0x1B6328u, gen::fn_sub_1985E0_001985e0);
                jal(ctx, 0x1B6330u, gen::fn_sub_198590_00198590);
                a0 = v0;
                lwc1(f12, s1, 20);
                jal(ctx, 0x1B6340u, gen::fn_sub_4C9DB0_004c9db0);
                lwc1(f20, s1, 16);
                jal(ctx, 0x1B634Cu, gen::fn_sub_198590_00198590);
                swc1(f20, v0, 136);
                jal(ctx, 0x1B6358u, gen::fn_sub_198590_00198590);
                lw(v0, s1, 4);
                at = 0x10000;
                at = at | 0x4;
                at = sltu(v0, at);
                if (at == 0) {
                    // 0x001b6378
                    charge(ctx, 7);
                    lwc1(f20, s1, 24);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    c_le_s(f20, f0);
                    if (!cond(ctx)) {
                        // 0x001b6394
                        charge(ctx, 6);
                        jal(ctx, 0x1B6394u, gen::fn_sub_198590_00198590);
                        a0 = v0;
                        mov_s(f12, f20);
                        jal(ctx, 0x1B63A4u, gen::fn_sub_4C9D70_004c9d70);
                    }
                    // 0x001b63ac
                    charge(ctx, 7);
                    lwc1(f1, s1, 24);
                    v0 = 0x42480000;
                    mtc1(v0, f0);
                    c_eq_s(f0, f1);
                    if (cond(ctx)) {
                        // 0x001b63c8
                        charge(ctx, 7);
                        jal(ctx, 0x1B63C8u, gen::fn_sub_198590_00198590);
                        v1 = 0x42C80000;
                        mtc1(v1, f12);
                        a0 = v0;
                        jal(ctx, 0x1B63DCu, gen::fn_sub_4C9D70_004c9d70);
                    }
                    // 0x001b63e4
                    charge(ctx, 4);
                    lbu(v1, s1, 511);
                    v0 = 255;
                    if (v1 == v0) {
                        // 0x001b63f4
                        charge(ctx, 12);
                        lbu(a0, s1, 508);
                        lbu(a1, s1, 509);
                        lbu(a2, s1, 510);
                        a3 = 0;
                        jal(ctx, 0x1B6404u, gen::fn_sub_1985B0_001985b0);
                        lbu(a0, s1, 508);
                        lbu(a1, s1, 509);
                        lbu(a2, s1, 510);
                        a3 = 0;
                        jal(ctx, 0x1B641Cu, gen::fn_sub_1985E0_001985e0);
                    }
                }
                // 0x001b6424
                charge(ctx, 24);
                jal(ctx, 0x1B6424u, gen::fn_sub_19FD40_0019fd40);
                lwc1(f3, s1, 28);
                lwc1(f2, s1, 32);
                lwc1(f1, s1, 36);
                lwc1(f0, s1, 40);
                swc1(f3, v0, 0);
                swc1(f2, v0, 4);
                swc1(f1, v0, 8);
                swc1(f0, v0, 12);
                jal(ctx, 0x1B644Cu, gen::fn_sub_19FD70_0019fd70);
                lwc1(f3, s1, 44);
                lwc1(f2, s1, 48);
                lwc1(f1, s1, 52);
                lwc1(f0, s1, 56);
                swc1(f3, v0, 0);
                swc1(f2, v0, 4);
                swc1(f1, v0, 8);
                swc1(f0, v0, 12);
                jal(ctx, 0x1B6474u, gen::fn_sub_19FDA0_0019fda0);
                a2 = addiu(s1, 64);
                a1 = 8;
                for (;;) {
                    // 0x001b6484
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
                // 0x001b64a8
                charge(ctx, 2);
                if (s3 != 0) {
                    // 0x001b64b0
                    charge(ctx, 19);
                    lwc1(f3, s1, 128);
                    lwc1(f2, s1, 132);
                    lwc1(f1, s1, 136);
                    lwc1(f0, s1, 140);
                    swc1(f3, s3, 256);
                    swc1(f2, s3, 260);
                    swc1(f1, s3, 264);
                    swc1(f0, s3, 268);
                    lwc1(f3, s1, 144);
                    lwc1(f2, s1, 148);
                    lwc1(f1, s1, 152);
                    lwc1(f0, s1, 156);
                    swc1(f3, s3, 272);
                    swc1(f2, s3, 276);
                    swc1(f1, s3, 280);
                    swc1(f0, s3, 284);
                    a2 = addiu(s1, 160);
                    a1 = addiu(s3, 288);
                    a0 = 8;
                    for (;;) {
                        // 0x001b64fc
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
                    // 0x001b6520
                    charge(ctx, 11);
                    lwc1(f3, s1, 224);
                    lwc1(f2, s1, 228);
                    lwc1(f1, s1, 232);
                    lwc1(f0, s1, 236);
                    swc1(f3, s3, 352);
                    swc1(f2, s3, 356);
                    swc1(f1, s3, 360);
                    swc1(f0, s3, 364);
                    a2 = addiu(s1, 240);
                    a1 = addiu(s3, 368);
                    a0 = 8;
                    for (;;) {
                        // 0x001b654c
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
                }
                // 0x001b6570
                charge(ctx, 6);
                lw(v0, s1, 4);
                at = 0x10000;
                at = at | 0x1;
                at = sltu(v0, at);
                if (at == 0) {
                    // 0x001b6588
                    charge(ctx, 3);
                    s5 = 0;
                    for (;;) {
                        // 0x001b65f0
                        charge(ctx, 6);
                        jal(ctx, 0x1B65F0u, gen::fn_K_Field_Get_001b9120);
                        lw(v0, v0, f4::fld::kResCount);
                        v0 = slt(s5, v0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001b6594
                        charge(ctx, 23);
                        s4 = sll(s5, 2);
                        jal(ctx, 0x1B6598u, gen::fn_K_Field_Get_001b9120);
                        v0 = addu(v0, s4);
                        lw(v0, v0, f4::fld::kRes);
                        lwc1(f2, s1, 304);
                        lwc1(f1, s1, 308);
                        lwc1(f0, s1, 312);
                        swc1(f2, v0, 2592);
                        swc1(f1, v0, 2596);
                        swc1(f0, v0, 2600);
                        jal(ctx, 0x1B65C0u, gen::fn_K_Field_Get_001b9120);
                        s3 = addu(v0, s4);
                        jal(ctx, 0x1B65CCu, gen::fn_K_Field_Get_001b9120);
                        v0 = addu(v0, s4);
                        lw(v0, v0, f4::fld::kRes);
                        lw(a0, s3, f4::fld::kRes);
                        a1 = addiu(v0, 2592);
                        jal(ctx, 0x1B65E4u, gen::fn_sub_1B5610_001b5610);
                        s5 = addiu(s5, 1);
                    }
                }
                // 0x001b6608
                charge(ctx, 6);
                lw(v0, s1, 4);
                at = 0x10000;
                at = at | 0x2;
                at = sltu(v0, at);
                if (at == 0) {
                    // 0x001b6620
                    charge(ctx, 2);
                    if (s0 != 0) {
                        // 0x001b6628
                        charge(ctx, 19);
                        lwc1(f3, s1, 316);
                        lwc1(f2, s1, 320);
                        lwc1(f1, s1, 324);
                        lwc1(f0, s1, 328);
                        swc1(f3, s0, 256);
                        swc1(f2, s0, 260);
                        swc1(f1, s0, 264);
                        swc1(f0, s0, 268);
                        lwc1(f3, s1, 332);
                        lwc1(f2, s1, 336);
                        lwc1(f1, s1, 340);
                        lwc1(f0, s1, 344);
                        swc1(f3, s0, 272);
                        swc1(f2, s0, 276);
                        swc1(f1, s0, 280);
                        swc1(f0, s0, 284);
                        a2 = addiu(s1, 352);
                        a1 = addiu(s0, 288);
                        a0 = 8;
                        for (;;) {
                            // 0x001b6674
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
                        // 0x001b6698
                        charge(ctx, 11);
                        lwc1(f3, s1, 416);
                        lwc1(f2, s1, 420);
                        lwc1(f1, s1, 424);
                        lwc1(f0, s1, 428);
                        swc1(f3, s0, 352);
                        swc1(f2, s0, 356);
                        swc1(f1, s0, 360);
                        swc1(f0, s0, 364);
                        a2 = addiu(s1, 432);
                        a1 = addiu(s0, 368);
                        a0 = 8;
                        for (;;) {
                            // 0x001b66c4
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
                    }
                }
                // 0x001b66e8
                charge(ctx, 6);
                lw(v0, s1, 4);
                at = 0x10000;
                at = at | 0x3;
                at = sltu(v0, at);
                if (at == 0) {
                    // 0x001b6700
                    charge(ctx, 11);
                    a0 = 1;
                    jal(ctx, 0x1B6704u, gen::fn_sub_3B5D50_003b5d50);
                    s4 = v0;
                    a0 = 3;
                    jal(ctx, 0x1B6714u, gen::fn_sub_3B5D50_003b5d50);
                    s3 = v0;
                    s0 = 0;
                    for (;;) {
                        // 0x001b675c
                        charge(ctx, 6);
                        jal(ctx, 0x1B675Cu, gen::fn_K_Field_Get_001b9120);
                        lw(v0, v0, f4::fld::kResCount);
                        v0 = slt(s0, v0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001b672c
                        charge(ctx, 12);
                        jal(ctx, 0x1B672Cu, gen::fn_K_Field_Get_001b9120);
                        v1 = sll(s0, 2);
                        v0 = addu(v0, v1);
                        lw(v0, v0, f4::fld::kRes);
                        lwc1(f2, s1, 496);
                        lwc1(f1, s1, 500);
                        lwc1(f0, s1, 504);
                        swc1(f2, v0, 2604);
                        swc1(f1, v0, 2608);
                        swc1(f0, v0, 2612);
                        s0 = addiu(s0, 1);
                    }
                    // 0x001b6774
                    charge(ctx, 2);
                    for (;;) {
                        // 0x001b67a4
                        charge(ctx, 2);
                        if (s4 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001b677c
                        charge(ctx, 10);
                        lw(a0, s4, 296);
                        jal(ctx, 0x1B6780u, gen::fn_sub_318B80_00318b80);
                        a0 = v0;
                        a1 = 0x1B0000;
                        a1 = addiu(a1, 24672);  // &sub_1B6060
                        a2 = addiu(s1, 496);
                        jal(ctx, 0x1B6798u, gen::fn_sub_4916D0_004916d0);
                        lw(s4, s4, 248);
                    }
                    // 0x001b67ac
                    charge(ctx, 2);
                    for (;;) {
                        // 0x001b67dc
                        charge(ctx, 2);
                        if (s3 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001b67b4
                        charge(ctx, 10);
                        lw(a0, s3, 296);
                        jal(ctx, 0x1B67B8u, gen::fn_sub_318B80_00318b80);
                        a0 = v0;
                        a1 = 0x1B0000;
                        a1 = addiu(a1, 24672);  // &sub_1B6060
                        a2 = addiu(s1, 496);
                        jal(ctx, 0x1B67D0u, gen::fn_sub_4916D0_004916d0);
                        lw(s3, s3, 248);
                    }
                }
                // 0x001b67e4
                charge(ctx, 6);
                lw(v0, s1, 4);
                at = 0x10000;
                at = at | 0x4;
                at = sltu(v0, at);
                if (at != 0) {
                    // 0x001b67fc
                    charge(ctx, 7);
                    a0 = 0;
                    a1 = 0;
                    a2 = 376;
                    a3 = 0x680000;
                    a3 = addiu(a3, -28688);  // "CAUTION!! READ OLD VER ENV DATA"
                    jal(ctx, 0x1B6810u, gen::fn_sub_1A1540_001a1540);
                }
                // 0x001b6818
                charge(ctx, 6);
                a0 = s2;
                jal(ctx, 0x1B681Cu, gen::fn_H_Cdvd_Destroy_00100ec0);
                v0 = 1;
            }
        }
    } else {
        // 0x001b6224
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x001b6e78 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// 0x001B75E0 sub_1B75E0 [K_EverydayScript_Update] -- 208 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1B75E0(task): the "everyday script" task: state 0 waits for "field/script/everyday.bf" and runs it as a header
// script (scrCreateTaskFromHeader 10); 1 waits for the script task; 2 returns -1 (destroy).
void sub_1B75E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b75e0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, f4::kTaskWork);
    lw(v1, s0, 0);
    v0 = 2;
    if (v1 == v0) {
        // 0x001b768c
        charge(ctx, 3);
        v0 = si(-1);
    } else {
        // 0x001b7600
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x001b7660
            charge(ctx, 6);
            lw(a0, s0, 8);
            jal(ctx, 0x1B7664u, gen::fn_kwlnTaskExists_00195460);
            v1 = 1;
            if (v0 != v1) {
                // 0x001b7678
                charge(ctx, 5);
                lw(v0, s0, 0);
                v0 = addiu(v0, 1);
                sw(v0, s0, 0);
            }
        } else {
            // 0x001b760c
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x001b761c
                charge(ctx, 5);
                lw(a0, s0, 4);
                jal(ctx, 0x1B7620u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
                if (v0 != 0) {
                    // 0x001b7630
                    charge(ctx, 12);
                    lw(v0, s0, 4);
                    a0 = 10;
                    lw(a1, v0, 272);
                    a2 = 0;
                    jal(ctx, 0x1B7640u, gen::fn_scrCreateTaskFromHeader_0035bb40);
                    sw(v0, s0, 8);
                    lw(v0, s0, 0);
                    v0 = addiu(v0, 1);
                    sw(v0, s0, 0);
                }
            } else {
                // 0x001b7614
                charge(ctx, 2);
            }
        }
        // 0x001b7698
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x001b769c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001B76B0 sub_1B76B0 [K_EverydayScript_Destroy] -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1B76B0(task): destroys the file request (+4) and frees the work.
void sub_1B76B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b76b0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, f4::kTaskWork);
    lw(a0, v0, 4);
    jal(ctx, 0x1B76C8u, gen::fn_H_Cdvd_Destroy_00100ec0);
    lw(a0, s0, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1B76DCu, v0.u());
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001B7700 sub_1B7700 [K_EverydayScript_CreateTask] -- 172 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B7700(parent) -> the "everyday script" task (12-byte work) with "field/script/everyday.bf" requested;
// created by the calendar (sub_17FE10).
void sub_1B7700(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b7700
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 1;
    a1 = 12;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1B7728u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001b7748
        charge(ctx, 19);
        a0 = s1;
        a1 = 10;
        a2 = 0x680000;
        a2 = addiu(a2, -28624);  // "everyday script"
        a3 = 0x1B0000;
        a3 = addiu(a3, 30176);  // &sub_1B75E0
        t0 = 0x1B0000;
        t0 = addiu(t0, 30384);  // &sub_1B76B0
        t1 = s0;
        jal(ctx, 0x1B776Cu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        s1 = v0;
        a0 = 0x680000;
        a0 = addiu(a0, -28608);  // "field/script/everyday.bf"
        a1 = 0;
        jal(ctx, 0x1B7784u, gen::fn_H_Cdvd_Request_00100d80);
        sw(v0, s0, 4);
        v0 = s1;
    } else {
        // 0x001b773c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001b7794 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001B77B0 K_Seq_CallField -- 156 bytes; frame 0x50: ra sp+0x40, s0 sp+0x30 (sq)
// K_Seq_CallField(back, packet) (sequence 2 .call): asserts the packet's major (k_sequence.c 88; returns in retail)
// and creates the field root k_Field_CreateFieldRootTask(0, major, minor, entry, (s16)sub1, (s16)sub2, flags 0,
// minCells 6, maxCells 128, 0, no event) into sField.root. Packet: u16 major, minor, entry, sub1, sub2.
void K_Seq_CallField(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b77b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s0, sp, 0x30);
    s0 = a1;
    lhu(v0, a1, 0);
    if (v0 == 0) {
        // 0x001b77cc
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, -28576);  // "k_sequence.c"
        a1 = 88;
        jal(ctx, 0x1B77D8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001b77e0
    charge(ctx, 27);
    v0 = 128;
    sd(v0, sp, 0x0);
    sd(zero, sp, 0x8);
    v0 = si(-1);
    sd(v0, sp, 0x10);
    sd(v0, sp, 0x18);
    sd(v0, sp, 0x20);
    sd(v0, sp, 0x28);
    a0 = 0;
    lhu(a1, s0, 0);
    lhu(a2, s0, 2);
    lhu(a3, s0, 4);
    lh(t0, s0, 6);
    lh(t1, s0, 8);
    t2 = 0;
    t3 = 6;
    jal(ctx, 0x1B7820u, gen::fn_k_Field_CreateFieldRootTask_001ba5f0);
    s0 = v0;
    jal(ctx, 0x1B782Cu, gen::fn_K_Field_Get_001b9120);
    sw(s0, v0, f4::fld::kRoot);
    ld(ra, sp, 0x40);
    lq(s0, sp, 0x30);
    sp = addiu(sp, 0x50);
}

// 0x001B7850 K_Seq_ExitField -- 80 bytes; frame 0x10: ra sp+0x0
// K_Seq_ExitField() -> 0 (sequence 2 .exit): destroys the field root hierarchy and clears sField.root.
void K_Seq_ExitField(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b7850
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1B7858u, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, f4::fld::kRoot);
    if (v0 != 0) {
        // 0x001b786c
        charge(ctx, 8);
        jal(ctx, 0x1B786Cu, gen::fn_K_Field_Get_001b9120);
        lw(a0, v0, f4::fld::kRoot);
        jal(ctx, 0x1B7878u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
        jal(ctx, 0x1B7880u, gen::fn_K_Field_Get_001b9120);
        sw(zero, v0, f4::fld::kRoot);
    }
    // 0x001b788c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B7900 K_Seq_CallFieldEvent -- 160 bytes; frame 0x50: ra sp+0x40, s0 sp+0x30 (sq)
// K_Seq_CallFieldEvent(back, packet) (sequence 3 .call): asserts packet +12 (k_sequence.c 145) and creates a field
// root for the event PM file packet +12 (packet +16 / +20 passed on); the ids come out of the PM file (root state 0).
void K_Seq_CallFieldEvent(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b7900
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s0, sp, 0x30);
    s0 = a1;
    lw(v0, a1, 12);
    if (v0 == 0) {
        // 0x001b791c
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, -28576);  // "k_sequence.c"
        a1 = 145;
        jal(ctx, 0x1B7928u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001b7930
    charge(ctx, 28);
    sd(zero, sp, 0x0);
    sd(zero, sp, 0x8);
    lw(v0, s0, 12);
    sd(v0, sp, 0x10);
    lw(v0, s0, 16);
    sd(v0, sp, 0x18);
    lw(v0, s0, 20);
    sd(v0, sp, 0x20);
    sd(zero, sp, 0x28);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    t0 = 0;
    t1 = 0;
    t2 = 0;
    t3 = 0;
    jal(ctx, 0x1B7974u, gen::fn_k_Field_CreateFieldRootTask_001ba5f0);
    s0 = v0;
    jal(ctx, 0x1B7980u, gen::fn_K_Field_Get_001b9120);
    sw(s0, v0, f4::fld::kRoot);
    ld(ra, sp, 0x40);
    lq(s0, sp, 0x30);
    sp = addiu(sp, 0x50);
}

// 0x001B79A0 K_Seq_ExitFieldEvent -- 80 bytes; frame 0x10: ra sp+0x0
// K_Seq_ExitFieldEvent() -> 0 (sequence 3 .exit): as K_Seq_ExitField.
void K_Seq_ExitFieldEvent(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b79a0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1B79A8u, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, f4::fld::kRoot);
    if (v0 != 0) {
        // 0x001b79bc
        charge(ctx, 8);
        jal(ctx, 0x1B79BCu, gen::fn_K_Field_Get_001b9120);
        lw(a0, v0, f4::fld::kRoot);
        jal(ctx, 0x1B79C8u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
        jal(ctx, 0x1B79D0u, gen::fn_K_Field_Get_001b9120);
        sw(zero, v0, f4::fld::kRoot);
    }
    // 0x001b79dc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B7A50 K_Seq_CallDungeon -- 52 bytes; frame 0x10: ra sp+0x0
// K_Seq_CallDungeon(back, packet) (sequence 5 .call): K_FldDungeon_CreateTask(0, floor = packet +0, entry =
// packet +4) into the dungeon slot 0x7CE268.
void K_Seq_CallDungeon(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b7a50
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v0 = a1;
    a0 = 0;
    lw(a1, a1, 0);
    lw(a2, v0, 4);
    jal(ctx, 0x1B7A68u, gen::fn_K_FldDungeon_CreateTask_001bfbc0);
    sw(v0, gp, f4::gpv::kDungeonTask);  // 0x7CE268
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B7A90 K_Seq_ExitDungeon -- 48 bytes; frame 0x10: ra sp+0x0
// K_Seq_ExitDungeon() -> 0 (sequence 5 .exit): destroys the dungeon task hierarchy (the field root of the floor is
// its child).
void K_Seq_ExitDungeon(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b7a90
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, f4::gpv::kDungeonTask);  // 0x7CE268
    if (a0 != 0) {
        // 0x001b7aa4
        charge(ctx, 2);
        jal(ctx, 0x1B7AA4u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
    }
    // 0x001b7aac (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B7B10 K_Data_LoadFldMainScript -- 156 bytes; frame 0xA0: ra sp+0x10, s0 sp+0x0 (sq)
// K_Data_LoadFldMainScript() (boot, kwlnInitMain): reads "field/script/field.bf" synchronously into a heap copy:
// g_fldMainScriptPtr 0x7CE228 / g_fldMainScriptSize 0x7CE224 (the header script of the field: pad 0x80 actions).
void K_Data_LoadFldMainScript(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b7b10
    enter(ctx, 39);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = addiu(sp, 0x20);
    a1 = 0x680000;
    a1 = addiu(a1, -3136);  // "field/script/field.bf"
    jal(ctx, 0x1B7B28u, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0x20);
    a1 = 0;
    jal(ctx, 0x1B7B38u, gen::fn_H_Cdvd_Request_00100d80);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x1B7B48u, gen::fn_H_Cdvd_ReadSync_001023a0);
    lw(a1, s0, 280);
    a0 = 1;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1B7B64u, v0.u());
    sw(v0, gp, -19144);  // g_fldMainScriptPtr
    lw(v1, s0, 280);
    sw(v1, gp, -19148);  // g_fldMainScriptSize
    lw(a2, s0, 280);
    a0 = v0;
    lw(a1, s0, 272);
    jal(ctx, 0x1B7B84u, gen::fn_memcpy_00521250);
    a0 = s0;
    jal(ctx, 0x1B7B90u, gen::fn_H_Cdvd_Destroy_00100ec0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x001B7BB0 sub_1B7BB0 [K_Data_LoadFukaScript] -- 132 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1B7BB0() (boot): reads "field/script/fuka.bf" synchronously into a heap copy at 0x7CE220.
void sub_1B7BB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b7bb0
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0x680000;
    a0 = addiu(a0, -3104);  // "field/script/fuka.bf"
    a1 = 0;
    jal(ctx, 0x1B7BC8u, gen::fn_H_Cdvd_Request_00100d80);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x1B7BD8u, gen::fn_H_Cdvd_ReadSync_001023a0);
    lw(a1, s0, 280);
    a0 = 1;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1B7BF4u, v0.u());
    sw(v0, gp, -19152);  // 0x7CE220
    lw(a2, s0, 280);
    a0 = v0;
    lw(a1, s0, 272);
    jal(ctx, 0x1B7C0Cu, gen::fn_memcpy_00521250);
    a0 = s0;
    jal(ctx, 0x1B7C18u, gen::fn_H_Cdvd_Destroy_00100ec0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001B7C40 sub_1B7C40 [K_Data_LoadDungeonTable] -- 192 bytes; frame 0xA0: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1B7C40(fes) (boot): reads "field/table/dungeonFES.bin" (fes != 0) or "dungeonAT.bin" synchronously into
// gFldDngFloorsData 0x867F60 (K_Assert k_data.c 170 when the file is 8 KiB or more): the floor table of the
// automatic dungeon, 16 bytes per floor (field4.h DngFloor).
void sub_1B7C40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b7c40
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    if (a0 != 0) {
        // 0x001b7c70
        charge(ctx, 5);
        a0 = addiu(sp, 0x20);
        a1 = 0x680000;
        a1 = addiu(a1, -3040);  // "field/table/dungeonFES.bin"
        jal(ctx, 0x1B7C7Cu, gen::fn_sprintf_00523ac8);
    } else {
        // 0x001b7c54
        charge(ctx, 7);
        a0 = addiu(sp, 0x20);
        a1 = 0x680000;
        a1 = addiu(a1, -3072);  // "field/table/dungeonAT.bin"
        jal(ctx, 0x1B7C60u, gen::fn_sprintf_00523ac8);
    }
    // 0x001b7c84
    charge(ctx, 12);
    a0 = addiu(sp, 0x20);
    a1 = 0;
    jal(ctx, 0x1B7C8Cu, gen::fn_H_Cdvd_Request_00100d80);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x1B7C9Cu, gen::fn_H_Cdvd_ReadSync_001023a0);
    lw(v0, s0, 280);
    v0 = sltiu(v0, 8192);
    if (v0 == 0) {
        // 0x001b7cb4
        charge(ctx, 5);
        a0 = 0x680000;
        a0 = addiu(a0, -3008);  // "k_data.c"
        a1 = 170;
        jal(ctx, 0x1B7CC0u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x001b7cc8
    charge(ctx, 14);
    lw(a2, s0, 280);
    a0 = 0x860000;
    a0 = addiu(a0, 32608);  // &gFldDngFloorsData
    lw(a1, s0, 272);
    jal(ctx, 0x1B7CD8u, gen::fn_memcpy_00521250);
    a0 = s0;
    jal(ctx, 0x1B7CE4u, gen::fn_H_Cdvd_Destroy_00100ec0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x001B7D00 sub_1B7D00 [K_Data_StartFieldBgmStream] -- 92 bytes; frame 0x10: ra sp+0x0
// sub_1B7D00() (boot): allocates 844 bytes (0x7CE218) and starts the sound-stream request sub_10A770(0, 6, buf, 2,
// 490, 1) -> 0x7CE214.
void sub_1B7D00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b7d00
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 1;
    a1 = 844;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1B7D1Cu, v0.u());
    sw(v0, gp, -19160);  // 0x7CE218
    a0 = 0;
    a1 = 6;
    a2 = v0;
    a3 = 2;
    t0 = 490;
    t1 = 1;
    jal(ctx, 0x1B7D40u, gen::fn_sub_10A770_0010a770);
    sw(v0, gp, -19164);  // 0x7CE214
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B7D60 sub_1B7D60 [K_Data_IsFieldBgmStreamReady] -- 84 bytes; frame 0x10: ra sp+0x0
// sub_1B7D60() -> 1 when the boot stream request 0x7CE214 is absent or finished (sub_10A720; then cleared).
void sub_1B7D60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b7d60
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, -19164);  // 0x7CE214
    if (a0 != 0) {
        // 0x001b7d80
        charge(ctx, 4);
        jal(ctx, 0x1B7D80u, gen::fn_sub_10A720_0010a720);
        if (v0 != 0) {
            // 0x001b7d9c
            charge(ctx, 2);
            sw(zero, gp, -19164);  // 0x7CE214
            v0 = 1;
        } else {
            // 0x001b7d90
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x001b7d74
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x001b7da4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B7DC0 sub_1B7DC0 [K_Data_LoadFieldBaseModel] -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1B7DC0() (boot): reads "field/base.RMD" synchronously and creates model 2000 from it (sub_316BD0) -> 0x7CE21C
// (the base model the NPC placer clones shadows from).
void sub_1B7DC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b7dc0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0x680000;
    a0 = addiu(a0, -2992);  // "field/base.RMD"
    a1 = 0;
    jal(ctx, 0x1B7DD8u, gen::fn_H_Cdvd_Request_00100d80);
    s0 = v0;
    a0 = s0;
    jal(ctx, 0x1B7DE8u, gen::fn_H_Cdvd_ReadSync_001023a0);
    a0 = 4;
    a1 = 2000;
    lw(a2, s0, 272);
    lw(a3, s0, 280);
    t0 = 0;
    jal(ctx, 0x1B7E04u, gen::fn_sub_316BD0_00316bd0);
    sw(v0, gp, -19156);  // 0x7CE21C
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001B7E30 sub_1B7E30 [K_Data_IsFieldBaseModelReady] -- 40 bytes; frame 0x10: ra sp+0x0
// sub_1B7E30() -> 1 when the base model 0x7CE21C is ready (sub_316F70).
void sub_1B7E30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b7e30
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, -19156);  // 0x7CE21C
    jal(ctx, 0x1B7E3Cu, gen::fn_sub_316F70_00316f70);
    v0 = sltu(0, v0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B7E60 sub_1B7E60 [K_StartupData_Update] -- 416 bytes; frame 0xB0: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B7E60(task): the "read startup data" task: state 0 requests the dungeon table (dungeonFES.bin when work +4,
// else dungeonAT.bin) and sub_1D4360; state 1 copies the table to gFldDngFloorsData when loaded (K_Assert k_data.c
// 205 for 8 KiB or more) and waits for sub_1D43E0; state 2 returns -1.
void sub_1B7E60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b7e60
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, f4::kTaskWork);
    lw(v1, s0, 0);
    v0 = 2;
    if (v1 == v0) {
        // 0x001b7fd8
        charge(ctx, 3);
        v0 = si(-1);
    } else {
        // 0x001b7e84
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x001b7e90
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x001b7ea0
                charge(ctx, 3);
                lw(v0, s0, 4);
                if (v0 != 0) {
                    // 0x001b7ec8
                    charge(ctx, 5);
                    a0 = addiu(sp, 0x30);
                    a1 = 0x680000;
                    a1 = addiu(a1, -3040);  // "field/table/dungeonFES.bin"
                    jal(ctx, 0x1B7ED4u, gen::fn_sprintf_00523ac8);
                } else {
                    // 0x001b7eac
                    charge(ctx, 7);
                    a0 = addiu(sp, 0x30);
                    a1 = 0x680000;
                    a1 = addiu(a1, -3072);  // "field/table/dungeonAT.bin"
                    jal(ctx, 0x1B7EB8u, gen::fn_sprintf_00523ac8);
                }
                // 0x001b7edc
                charge(ctx, 11);
                a0 = addiu(sp, 0x30);
                a1 = 0;
                jal(ctx, 0x1B7EE4u, gen::fn_H_Cdvd_Request_00100d80);
                sw(v0, s0, 8);
                jal(ctx, 0x1B7EF0u, gen::fn_sub_1D4360_001d4360);
                sw(v0, s0, 12);
                lw(v0, s0, 0);
                v0 = addiu(v0, 1);
                sw(v0, s0, 0);
                goto L_001b7f08;
            }
            // 0x001b7e98
            charge(ctx, 2);
            goto L_001b7fe4;
        }
    L_001b7f08:
        charge(ctx, 3);
        lw(s1, s0, 8);
        if (s1 != 0) {
            // 0x001b7f14
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x1B7F18u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 != 0) {
                // 0x001b7f34
                charge(ctx, 4);
                lw(v0, s1, 280);
                v0 = sltiu(v0, 8192);
                if (v0 == 0) {
                    // 0x001b7f44
                    charge(ctx, 5);
                    a0 = 0x680000;
                    a0 = addiu(a0, -3008);  // "k_data.c"
                    a1 = 205;
                    jal(ctx, 0x1B7F50u, gen::fn_sub_19D3F0_0019d3f0);
                }
                // 0x001b7f58
                charge(ctx, 10);
                lw(a2, s1, 280);
                a0 = 0x860000;
                a0 = addiu(a0, 32608);  // &gFldDngFloorsData
                lw(a1, s1, 272);
                jal(ctx, 0x1B7F68u, gen::fn_memcpy_00521250);
                a0 = s1;
                jal(ctx, 0x1B7F74u, gen::fn_H_Cdvd_Destroy_00100ec0);
                v0 = 1;
            } else {
                // 0x001b7f28
                charge(ctx, 3);
                v0 = 0;
            }
            // 0x001b7f80
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x001b7f88
                charge(ctx, 1);
                sw(zero, s0, 8);
            }
        }
        // 0x001b7f8c
        charge(ctx, 3);
        lw(a0, s0, 12);
        if (a0 != 0) {
            // 0x001b7f98
            charge(ctx, 4);
            jal(ctx, 0x1B7F98u, gen::fn_sub_1D43E0_001d43e0);
            if (v0 != 0) {
                // 0x001b7fa8
                charge(ctx, 1);
                sw(zero, s0, 12);
            }
        }
        // 0x001b7fac
        charge(ctx, 3);
        lw(v0, s0, 8);
        if (v0 == 0) {
            // 0x001b7fb8
            charge(ctx, 3);
            lw(v0, s0, 12);
            if (v0 == 0) {
                // 0x001b7fc4
                charge(ctx, 5);
                lw(v0, s0, 0);
                v0 = addiu(v0, 1);
                sw(v0, s0, 0);
            }
        }
    L_001b7fe4:
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x001b7fe8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// 0x001B8000 sub_1B8000 [K_StartupData_Destroy] -- 44 bytes; frame 0x10: ra sp+0x0
// sub_1B8000(task): frees the work.
void sub_1B8000(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b8000
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, f4::kTaskWork);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1B8014u, v0.u());
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B8030 sub_1B8030 [K_StartupData_CreateTaskAT] -- 144 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B8030(parent) -> a "read startup data" task for dungeonAT.bin (work +4 = 0).
void sub_1B8030(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b8030
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 1;
    a1 = 16;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1B8058u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001b8078
        charge(ctx, 12);
        a0 = s1;
        a1 = 10;
        a2 = 0x680000;
        a2 = addiu(a2, -2976);  // "read startup data"
        a3 = 0x1B0000;
        a3 = addiu(a3, 32352);  // &sub_1B7E60
        t0 = 0x1C0000;
        t0 = addiu(t0, -32768);  // &sub_1B8000
        t1 = s0;
        jal(ctx, 0x1B809Cu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        sw(zero, s0, 4);
    } else {
        // 0x001b806c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001b80a8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001B80C0 sub_1B80C0 [K_StartupData_CreateTaskFES] -- 148 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B80C0(parent) -> a "read startup data" task for dungeonFES.bin (work +4 = 1).
void sub_1B80C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b80c0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    a0 = 1;
    a1 = 16;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1B80E8u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001b8108
        charge(ctx, 13);
        a0 = s1;
        a1 = 10;
        a2 = 0x680000;
        a2 = addiu(a2, -2976);  // "read startup data"
        a3 = 0x1B0000;
        a3 = addiu(a3, 32352);  // &sub_1B7E60
        t0 = 0x1C0000;
        t0 = addiu(t0, -32768);  // &sub_1B8000
        t1 = s0;
        jal(ctx, 0x1B812Cu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        v1 = 1;
        sw(v1, s0, 4);
    } else {
        // 0x001b80fc
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001b813c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001B8160 sub_1B8160 [K_Fldrc_RequestNpcTable] -- 132 bytes; frame 0x90: ra sp+0x0
// sub_1B8160() -> the request of "field/table/nMMM_NNN.bin" (the scene's NPC schedule table), 1 when the .pac is
// resident, 0 when the file does not exist.
void sub_1B8160(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b8160
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1B8168u, gen::fn_sub_1B0910_001b0910);
    if (v0 != 0) {
        // 0x001b81d0
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x001b8178
        charge(ctx, 13);
        lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
        a0 = addiu(sp, 0x10);
        a1 = 0x680000;
        a1 = addiu(a1, -2944);  // "field/table/n%03d_%03d.bin"
        lw(a2, v0, f4::scene::kMajor);
        lw(a3, v0, f4::scene::kMinor);
        jal(ctx, 0x1B8190u, gen::fn_sprintf_00523ac8);
        a0 = addiu(sp, 0x10);
        jal(ctx, 0x1B819Cu, gen::fn_H_Cdvd_FileExists_001008b0);
        if (v0 != 0) {
            // 0x001b81b8
            charge(ctx, 6);
            a0 = addiu(sp, 0x10);
            a1 = 0;
            jal(ctx, 0x1B81C0u, gen::fn_H_Cdvd_Request_00100d80);
        } else {
            // 0x001b81ac
            charge(ctx, 3);
            v0 = 0;
        }
    }
    // 0x001b81d4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x001B81F0 sub_1B81F0 [K_Fldrc_TryLoadNpcTable] -- 512 bytes; frame 0x90: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B81F0(request) -> 1 when the NPC table is in the field (0 while loading): copied from the .pac
// ("field/pack/nMMM_NNN.bin") or the loaded request into a heap block sField +4440; +4444 = its entry count (u32 +0),
// +4448 = the 32-byte schedule entries (+32), +4452 = the entry lists after them (32-byte records, 0xFFFF ends one).
void sub_1B81F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b81f0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (s0 != 0) {
        // 0x001b821c
        charge(ctx, 4);
        jal(ctx, 0x1B821Cu, gen::fn_sub_1B0910_001b0910);
        if (v0 != 0) {
            // 0x001b82f0
            charge(ctx, 15);
            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            a0 = addiu(sp, 0x40);
            a1 = 0x680000;
            a1 = addiu(a1, -2912);  // "field/pack/n%03d_%03d.bin"
            lw(a2, v0, f4::scene::kMajor);
            lw(a3, v0, f4::scene::kMinor);
            jal(ctx, 0x1B8308u, gen::fn_sprintf_00523ac8);
            a0 = addiu(sp, 0x40);
            a1 = addiu(sp, 0x8C);
            jal(ctx, 0x1B8318u, gen::fn_H_Cdvd_CacheFindFile_001021c0);
            s1 = v0;
            if (s1 != 0) {
                // 0x001b832c
                charge(ctx, 38);
                lw(a1, sp, 0x8C);
                a0 = 1;
                a2 = 0x40000;
                v0 = 0x960000;
                lw(v0, v0, 388);  // 0x960184
                jalr(ctx, 0x1B8340u, v0.u());
                s0 = v0;
                jal(ctx, 0x1B834Cu, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, f4::fld::kNpcTable);
                jal(ctx, 0x1B8358u, gen::fn_K_Field_Get_001b9120);
                lw(a2, sp, 0x8C);
                lw(a0, v0, f4::fld::kNpcTable);
                a1 = s1;
                jal(ctx, 0x1B836Cu, gen::fn_memcpy_00521250);
                jal(ctx, 0x1B8374u, gen::fn_K_Field_Get_001b9120);
                lw(s1, v0, f4::fld::kNpcTable);
                lw(s0, s1, 0);
                jal(ctx, 0x1B8384u, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, f4::fld::kNpcTableCount);
                s0 = addiu(s1, 32);
                jal(ctx, 0x1B8394u, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, f4::fld::kNpcTableEntries);
                jal(ctx, 0x1B83A0u, gen::fn_K_Field_Get_001b9120);
                lw(v1, s1, 0);
                v1 = sll(v1, 5);
                lw(v0, v0, f4::fld::kNpcTableEntries);
                s0 = addu(v0, v1);
                jal(ctx, 0x1B83B8u, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, f4::fld::kNpcTableLists);
            }
            // 0x001b83c4
            charge(ctx, 3);
            v0 = 1;
        } else {
            // 0x001b822c
            charge(ctx, 5);
            a0 = s0;
            jal(ctx, 0x1B8230u, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 == 0) {
                // 0x001b83d0
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x001b8240
                charge(ctx, 44);
                lw(a1, s0, 280);
                a0 = 1;
                a2 = 0x40000;
                v0 = 0x960000;
                lw(v0, v0, 388);  // 0x960184
                jalr(ctx, 0x1B8254u, v0.u());
                s1 = v0;
                jal(ctx, 0x1B8260u, gen::fn_K_Field_Get_001b9120);
                sw(s1, v0, f4::fld::kNpcTable);
                jal(ctx, 0x1B826Cu, gen::fn_K_Field_Get_001b9120);
                lw(a2, s0, 280);
                lw(a0, v0, f4::fld::kNpcTable);
                lw(a1, s0, 272);
                jal(ctx, 0x1B8280u, gen::fn_memcpy_00521250);
                jal(ctx, 0x1B8288u, gen::fn_K_Field_Get_001b9120);
                lw(s2, v0, f4::fld::kNpcTable);
                lw(s1, s2, 0);
                jal(ctx, 0x1B8298u, gen::fn_K_Field_Get_001b9120);
                sw(s1, v0, f4::fld::kNpcTableCount);
                s1 = addiu(s2, 32);
                jal(ctx, 0x1B82A8u, gen::fn_K_Field_Get_001b9120);
                sw(s1, v0, f4::fld::kNpcTableEntries);
                jal(ctx, 0x1B82B4u, gen::fn_K_Field_Get_001b9120);
                lw(v1, s2, 0);
                v1 = sll(v1, 5);
                lw(v0, v0, f4::fld::kNpcTableEntries);
                s1 = addu(v0, v1);
                jal(ctx, 0x1B82CCu, gen::fn_K_Field_Get_001b9120);
                sw(s1, v0, f4::fld::kNpcTableLists);
                a0 = s0;
                jal(ctx, 0x1B82DCu, gen::fn_H_Cdvd_Destroy_00100ec0);
                v0 = 1;
            }
        }
    } else {
        // 0x001b8210
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x001b83d4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x001B83F0 sub_1B83F0 [K_NpcTable_FindCurrentEntry] -- 424 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B83F0() -> the schedule entry of the NPC table valid now, or 0: scans the 32-byte entries from the last back
// to the first ({u16 month, u16 day, u16 time, .., s32 flag +8, u32 list +12}), each valid from its date / time
// (clndIsDateInRange against the previous entry's date, clndGetCurrentMonth / Day, datGetTime) until the next, and
// takes the first whose flag (+8) is -1 or set (datGetFlag). Caller: the NPC placer sub_1E2E50.
void sub_1B83F0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b83f0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x1B8410u, gen::fn_K_Field_Get_001b9120);
    lw(s0, v0, f4::fld::kNpcTableEntries);
    if (s0 != 0) {
        // 0x001b8430
        charge(ctx, 12);
        jal(ctx, 0x1B8430u, gen::fn_K_Field_Get_001b9120);
        lw(v0, v0, f4::fld::kNpcTableCount);
        v0 = addiu(v0, -1);
        v0 = sll(v0, 5);
        s4 = addu(s0, v0);
        s3 = 3;
        s2 = 31;
        s1 = 8;
        s0 = 0;
        for (;;) {
            // 0x001b8538
            charge(ctx, 6);
            jal(ctx, 0x1B8538u, gen::fn_K_Field_Get_001b9120);
            lw(v0, v0, f4::fld::kNpcTableCount);
            v0 = sltu(s0, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001b8460
            charge(ctx, 9);
            lhu(a0, s4, 0);
            lhu(a1, s4, 2);
            a2 = s3;
            a3 = s2;
            jal(ctx, 0x1B8470u, gen::fn_clndIsDateInRange_0017e480);
            v1 = 1;
            if (v0 == v1) {
                // 0x001b8484
                charge(ctx, 5);
                lhu(s5, s4, 0);
                jal(ctx, 0x1B8488u, gen::fn_clndGetCurrentMonth_0017d920);
                if (s5 == v0) {
                    // 0x001b8498
                    charge(ctx, 5);
                    lhu(s5, s4, 2);
                    jal(ctx, 0x1B849Cu, gen::fn_clndGetCurrentDay_0017da40);
                    if (s5 != v0) {
                        goto L_001b84c8;
                    }
                    // 0x001b84ac
                    charge(ctx, 7);
                    jal(ctx, 0x1B84ACu, gen::fn_datGetTime_0016ef30);
                    v1 = v0 & 0xFF;
                    lhu(v0, s4, 4);
                    v0 = slt(v1, v0);
                    if (v0 == 0) {
                        goto L_001b84c8;
                    }
                L_001b8530:
                    charge(ctx, 2);
                    s0 = addiu(s0, 1);
                    s4 = addiu(s4, -32);
                    continue;
                }
            L_001b84c8:
                charge(ctx, 4);
                jal(ctx, 0x1B84C8u, gen::fn_clndGetCurrentMonth_0017d920);
                if (s3 == v0) {
                    // 0x001b84d8
                    charge(ctx, 4);
                    jal(ctx, 0x1B84D8u, gen::fn_clndGetCurrentDay_0017da40);
                    if (s2 != v0) {
                        goto L_001b8500;
                    }
                    // 0x001b84e8
                    charge(ctx, 6);
                    jal(ctx, 0x1B84E8u, gen::fn_datGetTime_0016ef30);
                    v0 = v0 & 0xFF;
                    at = slt(s1, v0);
                    if (at != 0) {
                        goto L_001b8530;
                    }
                    goto L_001b8500;
                }
            L_001b8500:
                charge(ctx, 4);
                lw(a0, s4, 8);
                v0 = si(-1);
                if (a0 != v0) {
                    // 0x001b8510
                    charge(ctx, 5);
                    jal(ctx, 0x1B8510u, gen::fn_datGetFlag_0016f190);
                    v1 = 1;
                    if (v0 != v1) {
                        goto L_001b8524;
                    }
                }
                break;
            }
        L_001b8524:
            charge(ctx, 3);
            lhu(s3, s4, 0);
            lhu(s2, s4, 2);
            lhu(s1, s4, 4);
            goto L_001b8530;
        }
        // 0x001b8550
        charge(ctx, 6);
        jal(ctx, 0x1B8550u, gen::fn_K_Field_Get_001b9120);
        lw(v0, v0, f4::fld::kNpcTableCount);
        v0 = sltu(s0, v0);
        if (v0 == 0) {
            // 0x001b8568
            charge(ctx, 1);
            s4 = 0;
        }
        // 0x001b856c
        charge(ctx, 1);
        v0 = s4;
    } else {
        // 0x001b8424
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001b8570 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x001B85A0 sub_1B85A0 [K_NpcTable_GetList] -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1B85A0(n) -> the n-th entry list of the NPC table (lists are runs of 32-byte records ended by u16 0xFFFF).
void sub_1B85A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b85a0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x1B85B0u, gen::fn_K_Field_Get_001b9120);
    lw(v0, v0, f4::fld::kNpcTableLists);
    a1 = 0;
    v1 = 0xFFFF;
    for (;;) {
        // 0x001b85c4
        charge(ctx, 2);
        if (a1 == s0) {
            break;
        }
        // 0x001b85cc
        charge(ctx, 3);
        lhu(a0, v0, 0);
        if (a0 == v1) {
            // 0x001b85d8
            charge(ctx, 1);
            a1 = addiu(a1, 1);
        }
        // 0x001b85dc
        charge(ctx, 3);
        v0 = addiu(v0, 32);
        backedge(ctx);
    }
    // 0x001b85e8
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001B8600 sub_1B8600 [K_Fldrc_FreeNpcTable] -- 120 bytes; frame 0x10: ra sp+0x0
// sub_1B8600(): frees the NPC table (sField +4440) and clears +4440..+4452 (scene unload sub_3B5AB0).
void sub_1B8600(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b8600
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1B8608u, gen::fn_K_Field_Get_001b9120);
    lw(v1, v0, f4::fld::kNpcTable);
    if (v1 != 0) {
        // 0x001b861c
        charge(ctx, 19);
        jal(ctx, 0x1B861Cu, gen::fn_K_Field_Get_001b9120);
        lw(a0, v0, f4::fld::kNpcTable);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x1B8630u, v0.u());
        jal(ctx, 0x1B8638u, gen::fn_K_Field_Get_001b9120);
        sw(zero, v0, f4::fld::kNpcTable);
        jal(ctx, 0x1B8644u, gen::fn_K_Field_Get_001b9120);
        sw(zero, v0, f4::fld::kNpcTableCount);
        jal(ctx, 0x1B8650u, gen::fn_K_Field_Get_001b9120);
        sw(zero, v0, f4::fld::kNpcTableEntries);
        jal(ctx, 0x1B865Cu, gen::fn_K_Field_Get_001b9120);
        sw(zero, v0, f4::fld::kNpcTableLists);
    }
    // 0x001b8668 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B8680 sub_1B8680 [K_Fldrc_RequestNpcMessages] -- 132 bytes; frame 0x90: ra sp+0x0
// sub_1B8680() -> the request of "field/script/nmMMM_NNN.bmd" (the NPCs' message file), 1 with the .pac, 0 if absent.
void sub_1B8680(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b8680
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1B8688u, gen::fn_sub_1B0910_001b0910);
    if (v0 != 0) {
        // 0x001b86f0
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x001b8698
        charge(ctx, 13);
        lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
        a0 = addiu(sp, 0x10);
        a1 = 0x680000;
        a1 = addiu(a1, -2880);  // "field/script/nm%03d_%03d.bmd"
        lw(a2, v0, f4::scene::kMajor);
        lw(a3, v0, f4::scene::kMinor);
        jal(ctx, 0x1B86B0u, gen::fn_sprintf_00523ac8);
        a0 = addiu(sp, 0x10);
        jal(ctx, 0x1B86BCu, gen::fn_H_Cdvd_FileExists_001008b0);
        if (v0 != 0) {
            // 0x001b86d8
            charge(ctx, 6);
            a0 = addiu(sp, 0x10);
            a1 = 0;
            jal(ctx, 0x1B86E0u, gen::fn_H_Cdvd_Request_00100d80);
        } else {
            // 0x001b86cc
            charge(ctx, 3);
            v0 = 0;
        }
    }
    // 0x001b86f4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x001B8710 sub_1B8710 [K_Fldrc_TryLoadNpcMessages] -- 344 bytes; frame 0x80: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B8710(request) -> 1 when the NPC messages are copied to the heap block sField +4436 (from the .pac
// "field/pack/nmMMM_NNN.bmd" or the request).
void sub_1B8710(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b8710
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    if (s1 != 0) {
        // 0x001b8738
        charge(ctx, 4);
        jal(ctx, 0x1B8738u, gen::fn_sub_1B0910_001b0910);
        if (v0 != 0) {
            // 0x001b87bc
            charge(ctx, 15);
            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            a0 = addiu(sp, 0x30);
            a1 = 0x680000;
            a1 = addiu(a1, -2848);  // "field/pack/nm%03d_%03d.bmd"
            lw(a2, v0, f4::scene::kMajor);
            lw(a3, v0, f4::scene::kMinor);
            jal(ctx, 0x1B87D4u, gen::fn_sprintf_00523ac8);
            a0 = addiu(sp, 0x30);
            a1 = addiu(sp, 0x7C);
            jal(ctx, 0x1B87E4u, gen::fn_H_Cdvd_CacheFindFile_001021c0);
            s1 = v0;
            if (s1 != 0) {
                // 0x001b87f8
                charge(ctx, 18);
                lw(a1, sp, 0x7C);
                a0 = 1;
                a2 = 0x40000;
                v0 = 0x960000;
                lw(v0, v0, 388);  // 0x960184
                jalr(ctx, 0x1B880Cu, v0.u());
                s0 = v0;
                jal(ctx, 0x1B8818u, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, f4::fld::kNpcMessages);
                jal(ctx, 0x1B8824u, gen::fn_K_Field_Get_001b9120);
                lw(a2, sp, 0x7C);
                lw(a0, v0, f4::fld::kNpcMessages);
                a1 = s1;
                jal(ctx, 0x1B8838u, gen::fn_memcpy_00521250);
            }
            // 0x001b8840
            charge(ctx, 3);
            v0 = 1;
        } else {
            // 0x001b8748
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x1B874Cu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 == 0) {
                // 0x001b884c
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x001b875c
                charge(ctx, 24);
                lw(a1, s1, 280);
                a0 = 1;
                a2 = 0x40000;
                v0 = 0x960000;
                lw(v0, v0, 388);  // 0x960184
                jalr(ctx, 0x1B8770u, v0.u());
                s0 = v0;
                jal(ctx, 0x1B877Cu, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, f4::fld::kNpcMessages);
                jal(ctx, 0x1B8788u, gen::fn_K_Field_Get_001b9120);
                lw(a2, s1, 280);
                lw(a0, v0, f4::fld::kNpcMessages);
                lw(a1, s1, 272);
                jal(ctx, 0x1B879Cu, gen::fn_memcpy_00521250);
                a0 = s1;
                jal(ctx, 0x1B87A8u, gen::fn_H_Cdvd_Destroy_00100ec0);
                v0 = 1;
            }
        }
    } else {
        // 0x001b872c
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x001b8850 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x001B8870 sub_1B8870 [K_Fldrc_FreeNpcMessages] -- 84 bytes; frame 0x10: ra sp+0x0
// sub_1B8870(): frees sField +4436.
void sub_1B8870(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b8870
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1B8878u, gen::fn_K_Field_Get_001b9120);
    lw(v1, v0, f4::fld::kNpcMessages);
    if (v1 != 0) {
        // 0x001b888c
        charge(ctx, 10);
        jal(ctx, 0x1B888Cu, gen::fn_K_Field_Get_001b9120);
        lw(a0, v0, f4::fld::kNpcMessages);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x1B88A0u, v0.u());
        jal(ctx, 0x1B88A8u, gen::fn_K_Field_Get_001b9120);
        sw(zero, v0, f4::fld::kNpcMessages);
    }
    // 0x001b88b4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B88D0 sub_1B88D0 [K_Fldrc_RequestNpcScript] -- 132 bytes; frame 0x90: ra sp+0x0
// sub_1B88D0() -> the request of "field/script/nsMMM_NNN.bf" (the NPCs' script), 1 with the .pac, 0 if absent.
void sub_1B88D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b88d0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1B88D8u, gen::fn_sub_1B0910_001b0910);
    if (v0 != 0) {
        // 0x001b8940
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x001b88e8
        charge(ctx, 13);
        lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
        a0 = addiu(sp, 0x10);
        a1 = 0x680000;
        a1 = addiu(a1, -2816);  // "field/script/ns%03d_%03d.bf"
        lw(a2, v0, f4::scene::kMajor);
        lw(a3, v0, f4::scene::kMinor);
        jal(ctx, 0x1B8900u, gen::fn_sprintf_00523ac8);
        a0 = addiu(sp, 0x10);
        jal(ctx, 0x1B890Cu, gen::fn_H_Cdvd_FileExists_001008b0);
        if (v0 != 0) {
            // 0x001b8928
            charge(ctx, 6);
            a0 = addiu(sp, 0x10);
            a1 = 0;
            jal(ctx, 0x1B8930u, gen::fn_H_Cdvd_Request_00100d80);
        } else {
            // 0x001b891c
            charge(ctx, 3);
            v0 = 0;
        }
    }
    // 0x001b8944 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x001B8960 sub_1B8960 [K_Fldrc_TryLoadNpcScript] -- 376 bytes; frame 0x80: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B8960(request) -> 1 when the NPC script is copied to the heap: sField +4428 = the block, +4432 = its size
// (from the .pac "field/pack/nsMMM_NNN.bf" or the request).
void sub_1B8960(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b8960
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    if (s1 != 0) {
        // 0x001b8988
        charge(ctx, 4);
        jal(ctx, 0x1B8988u, gen::fn_sub_1B0910_001b0910);
        if (v0 != 0) {
            // 0x001b8a1c
            charge(ctx, 15);
            lw(v0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            a0 = addiu(sp, 0x30);
            a1 = 0x680000;
            a1 = addiu(a1, -2784);  // "field/pack/ns%03d_%03d.bf"
            lw(a2, v0, f4::scene::kMajor);
            lw(a3, v0, f4::scene::kMinor);
            jal(ctx, 0x1B8A34u, gen::fn_sprintf_00523ac8);
            a0 = addiu(sp, 0x30);
            a1 = addiu(sp, 0x7C);
            jal(ctx, 0x1B8A44u, gen::fn_H_Cdvd_CacheFindFile_001021c0);
            s1 = v0;
            if (s1 != 0) {
                // 0x001b8a58
                charge(ctx, 22);
                lw(a1, sp, 0x7C);
                a0 = 1;
                a2 = 0x40000;
                v0 = 0x960000;
                lw(v0, v0, 388);  // 0x960184
                jalr(ctx, 0x1B8A6Cu, v0.u());
                s0 = v0;
                jal(ctx, 0x1B8A78u, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, f4::fld::kNpcScript);
                lw(s0, sp, 0x7C);
                jal(ctx, 0x1B8A88u, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, f4::fld::kNpcScriptSize);
                jal(ctx, 0x1B8A94u, gen::fn_K_Field_Get_001b9120);
                lw(a2, sp, 0x7C);
                lw(a0, v0, f4::fld::kNpcScript);
                a1 = s1;
                jal(ctx, 0x1B8AA8u, gen::fn_memcpy_00521250);
            }
            // 0x001b8ab0
            charge(ctx, 3);
            v0 = 1;
        } else {
            // 0x001b8998
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x1B899Cu, gen::fn_H_Cdvd_IsFileLoaded_001016b0);
            if (v0 == 0) {
                // 0x001b8abc
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x001b89ac
                charge(ctx, 28);
                lw(a1, s1, 280);
                a0 = 1;
                a2 = 0x40000;
                v0 = 0x960000;
                lw(v0, v0, 388);  // 0x960184
                jalr(ctx, 0x1B89C0u, v0.u());
                s0 = v0;
                jal(ctx, 0x1B89CCu, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, f4::fld::kNpcScript);
                lw(s0, s1, 280);
                jal(ctx, 0x1B89DCu, gen::fn_K_Field_Get_001b9120);
                sw(s0, v0, f4::fld::kNpcScriptSize);
                jal(ctx, 0x1B89E8u, gen::fn_K_Field_Get_001b9120);
                lw(a2, s1, 280);
                lw(a0, v0, f4::fld::kNpcScript);
                lw(a1, s1, 272);
                jal(ctx, 0x1B89FCu, gen::fn_memcpy_00521250);
                a0 = s1;
                jal(ctx, 0x1B8A08u, gen::fn_H_Cdvd_Destroy_00100ec0);
                v0 = 1;
            }
        }
    } else {
        // 0x001b897c
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x001b8ac0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x001B8AE0 sub_1B8AE0 [K_Fldrc_FreeNpcScript] -- 84 bytes; frame 0x10: ra sp+0x0
// sub_1B8AE0(): frees sField +4428.
void sub_1B8AE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b8ae0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1B8AE8u, gen::fn_K_Field_Get_001b9120);
    lw(v1, v0, f4::fld::kNpcScript);
    if (v1 != 0) {
        // 0x001b8afc
        charge(ctx, 10);
        jal(ctx, 0x1B8AFCu, gen::fn_K_Field_Get_001b9120);
        lw(a0, v0, f4::fld::kNpcScript);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x1B8B10u, v0.u());
        jal(ctx, 0x1B8B18u, gen::fn_K_Field_Get_001b9120);
        sw(zero, v0, f4::fld::kNpcScript);
    }
    // 0x001b8b24 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B8B40 sub_1B8B40 [K_Data_LoadComuTable] -- 244 bytes; frame 0xA0: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1B8B40() (boot): reads "field/table/comutbl.bin" when it exists into a heap copy 0x7CE240; 0x7CE248 = its
// 128-byte record count, 0x7CE244 = the number of lists (records with u16 0xFFFF).
void sub_1B8B40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b8b40
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = addiu(sp, 0x20);
    a1 = 0x680000;
    a1 = addiu(a1, -2752);  // "field/table/comutbl.bin"
    jal(ctx, 0x1B8B58u, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0x20);
    jal(ctx, 0x1B8B64u, gen::fn_H_Cdvd_FileExists_001008b0);
    if (v0 != 0) {
        // 0x001b8b74
        charge(ctx, 29);
        a0 = addiu(sp, 0x20);
        a1 = 0;
        jal(ctx, 0x1B8B7Cu, gen::fn_H_Cdvd_Request_00100d80);
        s0 = v0;
        a0 = s0;
        jal(ctx, 0x1B8B8Cu, gen::fn_H_Cdvd_ReadSync_001023a0);
        lw(a1, s0, 280);
        a0 = 1;
        a2 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, 388);  // 0x960184
        jalr(ctx, 0x1B8BA8u, v0.u());
        sw(v0, gp, -19120);  // 0x7CE240
        lw(a2, s0, 280);
        a0 = v0;
        lw(a1, s0, 272);
        jal(ctx, 0x1B8BC0u, gen::fn_memcpy_00521250);
        lw(v0, s0, 280);
        a0 = srl(v0, 7);
        sw(a0, gp, -19112);  // 0x7CE248
        lw(a2, gp, -19120);  // 0x7CE240
        a1 = 0;
        v1 = 0xFFFF;
        for (;;) {
            // 0x001b8c08
            charge(ctx, 3);
            v0 = slt(a1, a0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001b8be8
            charge(ctx, 3);
            lhu(v0, a2, 0);
            if (v0 == v1) {
                // 0x001b8bf4
                charge(ctx, 3);
                lw(v0, gp, -19116);  // 0x7CE244
                v0 = addiu(v0, 1);
                sw(v0, gp, -19116);  // 0x7CE244
            }
            // 0x001b8c00
            charge(ctx, 2);
            a1 = addiu(a1, 1);
            a2 = addiu(a2, 128);
        }
        // 0x001b8c14
        charge(ctx, 3);
        a0 = s0;
        jal(ctx, 0x1B8C18u, gen::fn_H_Cdvd_Destroy_00100ec0);
    }
    // 0x001b8c20 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x001B8C40 sub_1B8C40 [K_Data_LoadNpcComuScript] -- 176 bytes; frame 0xA0: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1B8C40() (boot): reads "field/script/npccomu.bf" when it exists: 0x7CE23C = the copy, 0x7CE238 = its size.
void sub_1B8C40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b8c40
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = addiu(sp, 0x20);
    a1 = 0x680000;
    a1 = addiu(a1, -2720);  // "field/script/npccomu.bf"
    jal(ctx, 0x1B8C58u, gen::fn_sprintf_00523ac8);
    a0 = addiu(sp, 0x20);
    jal(ctx, 0x1B8C64u, gen::fn_H_Cdvd_FileExists_001008b0);
    if (v0 != 0) {
        // 0x001b8c74
        charge(ctx, 26);
        a0 = addiu(sp, 0x20);
        a1 = 0;
        jal(ctx, 0x1B8C7Cu, gen::fn_H_Cdvd_Request_00100d80);
        s0 = v0;
        a0 = s0;
        jal(ctx, 0x1B8C8Cu, gen::fn_H_Cdvd_ReadSync_001023a0);
        lw(a1, s0, 280);
        a0 = 1;
        a2 = 0x40000;
        v0 = 0x960000;
        lw(v0, v0, 388);  // 0x960184
        jalr(ctx, 0x1B8CA8u, v0.u());
        sw(v0, gp, -19124);  // 0x7CE23C
        lw(v1, s0, 280);
        sw(v1, gp, -19128);  // 0x7CE238
        lw(a2, s0, 280);
        a0 = v0;
        lw(a1, s0, 272);
        jal(ctx, 0x1B8CC8u, gen::fn_memcpy_00521250);
        a0 = s0;
        jal(ctx, 0x1B8CD4u, gen::fn_H_Cdvd_Destroy_00100ec0);
    }
    // 0x001b8cdc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x001B8CF0 sub_1B8CF0 [K_NpcSlot_FreeExtra] -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_1B8CF0(slot): frees the two optional blocks of an NPC placement slot (+20 cleared then RwFree(0) -- the original
// passes 0 --, +28 freed and cleared).
void sub_1B8CF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b8cf0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, a0, 20);
    if (v1 != 0) {
        // 0x001b8d0c
        charge(ctx, 6);
        sw(zero, s0, 20);
        a0 = 0;
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x1B8D1Cu, v0.u());
    }
    // 0x001b8d24
    charge(ctx, 3);
    lw(a0, s0, 28);
    if (a0 != 0) {
        // 0x001b8d30
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x1B8D38u, v0.u());
        sw(zero, s0, 28);
    }
    // 0x001b8d44 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001B8D60 sub_1B8D60 [K_ComuTable_GetList] -- 80 bytes; leaf frame (no stack)
// sub_1B8D60(n) -> the start of the n-th list of the social-link NPC table 0x7CE240 (or the end).
void sub_1B8D60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28};
    // 0x001b8d60
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v0, gp, -19120);  // 0x7CE240
    a3 = 0;
    t0 = 0;
    lw(a2, gp, -19112);  // 0x7CE248
    a1 = 0xFFFF;
    for (;;) {
        // 0x001b8d9c
        charge(ctx, 3);
        v1 = sltu(t0, a2);
        if (v1 != 0) {
            backedge(ctx);
            // 0x001b8d7c
            charge(ctx, 2);
            if (a3 != a0) {
                // 0x001b8d84
                charge(ctx, 3);
                lhu(v1, v0, 0);
                if (v1 == a1) {
                    // 0x001b8d90
                    charge(ctx, 1);
                    a3 = addiu(a3, 1);
                }
                // 0x001b8d94
                charge(ctx, 2);
                t0 = addiu(t0, 1);
                v0 = addiu(v0, 128);
                continue;
            }
        }
        break;
    }
    // 0x001b8da8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x001B8DB0 sub_1B8DB0 [K_ComuTable_FindCurrentEntry] -- 536 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B8DB0(list) -> the record of a social-link NPC list valid in the current scene now, or 0: from the list's end
// back, records whose scene (+96 major, +98 minor) is the current one, valid from their date / time (+2 month, +4 day,
// +6 time) and whose 15 'show' flags (+36..) and 7 'require' flags (+8..) select them (-1 = unused).
void sub_1B8DB0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b8db0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a1 = a0;
    if (a0 != 0) {
        // 0x001b8de4
        charge(ctx, 2);
        s2 = 0;
        v0 = 0xFFFF;
        for (;;) {
            // 0x001b8dec
            charge(ctx, 3);
            lhu(v1, a1, 0);
            if (v1 == v0) {
                break;
            }
            // 0x001b8df8
            charge(ctx, 4);
            s2 = addiu(s2, 1);
            a1 = addiu(a1, 128);
            backedge(ctx);
        }
        // 0x001b8e08
        charge(ctx, 9);
        v0 = sll(s2, 7);
        v0 = addu(a0, v0);
        s1 = addiu(v0, -128);
        a2 = 3;
        a3 = 31;
        s0 = 8;
        s3 = 0;
        for (;;) {
            // 0x001b8f7c
            charge(ctx, 3);
            v0 = sltu(s3, s2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001b8e2c
            charge(ctx, 5);
            lw(a0, gp, f4::gpv::kSceneRecord);  // 0x7CD540
            lw(v1, a0, f4::scene::kMajor);
            lhu(v0, s1, 96);
            if (v1 == v0) {
                // 0x001b8e40
                charge(ctx, 4);
                lw(v1, a0, 4);
                lhu(v0, s1, 98);
                if (v1 != v0) {
                    goto L_001b8f74;
                }
                // 0x001b8e50
                charge(ctx, 7);
                lhu(a0, s1, 2);
                lhu(a1, s1, 4);
                jal(ctx, 0x1B8E58u, gen::fn_clndIsDateInRange_0017e480);
                v1 = 1;
                if (v0 == v1) {
                    // 0x001b8e6c
                    charge(ctx, 5);
                    lhu(s4, s1, 2);
                    jal(ctx, 0x1B8E70u, gen::fn_clndGetCurrentMonth_0017d920);
                    if (s4 == v0) {
                        // 0x001b8e80
                        charge(ctx, 5);
                        lhu(s4, s1, 4);
                        jal(ctx, 0x1B8E84u, gen::fn_clndGetCurrentDay_0017da40);
                        if (s4 != v0) {
                            goto L_001b8ec0;
                        }
                        // 0x001b8e94
                        charge(ctx, 6);
                        jal(ctx, 0x1B8E94u, gen::fn_datGetTime_0016ef30);
                        v0 = v0 & 0xFF;
                        at = slt(v0, s0);
                        if (at == 0) {
                            goto L_001b8ec0;
                        }
                        // 0x001b8eac
                        charge(ctx, 5);
                        lhu(a2, s1, 2);
                        lhu(a3, s1, 4);
                        lhu(s0, s1, 6);
                        goto L_001b8f74;
                    }
                L_001b8ec0:
                    charge(ctx, 3);
                    s0 = 0;
                    for (;;) {
                        // 0x001b8efc
                        charge(ctx, 3);
                        v0 = sltiu(s0, 15);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001b8ecc
                        charge(ctx, 6);
                        v0 = sll(s0, 2);
                        v0 = addu(s1, v0);
                        lw(a0, v0, 36);
                        v0 = si(-1);
                        if (a0 != v0) {
                            // 0x001b8ee4
                            charge(ctx, 5);
                            jal(ctx, 0x1B8EE4u, gen::fn_datGetFlag_0016f190);
                            v1 = 1;
                            if (v0 == v1) {
                                break;
                            }
                            goto L_001b8ef8;
                        }
                    L_001b8ef8:
                        charge(ctx, 1);
                        s0 = addiu(s0, 1);
                    }
                    // 0x001b8f08
                    charge(ctx, 3);
                    v0 = sltiu(s0, 15);
                    if (v0 != 0) {
                        goto L_001b8f68;
                    }
                    // 0x001b8f14
                    charge(ctx, 3);
                    s0 = 0;
                    for (;;) {
                        // 0x001b8f50
                        charge(ctx, 3);
                        v0 = sltiu(s0, 7);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001b8f20
                        charge(ctx, 6);
                        v0 = sll(s0, 2);
                        v0 = addu(s1, v0);
                        lw(a0, v0, 8);
                        v0 = si(-1);
                        if (a0 != v0) {
                            // 0x001b8f38
                            charge(ctx, 5);
                            jal(ctx, 0x1B8F38u, gen::fn_datGetFlag_0016f190);
                            v1 = 1;
                            if (v0 == v1) {
                                break;
                            }
                            goto L_001b8f4c;
                        }
                    L_001b8f4c:
                        charge(ctx, 1);
                        s0 = addiu(s0, 1);
                    }
                    // 0x001b8f5c
                    charge(ctx, 3);
                    v0 = sltiu(s0, 7);
                    if (v0 == 0) {
                        goto L_001b8f68;
                    }
                    break;
                }
            L_001b8f68:
                charge(ctx, 3);
                lhu(a2, s1, 2);
                lhu(a3, s1, 4);
                lhu(s0, s1, 6);
                goto L_001b8f74;
            }
        L_001b8f74:
            charge(ctx, 2);
            s3 = addiu(s3, 1);
            s1 = addiu(s1, -128);
        }
        // 0x001b8f88
        charge(ctx, 3);
        v0 = sltu(s3, s2);
        if (v0 != 0) {
            // 0x001b8fa0
            charge(ctx, 1);
            v0 = s1;
        } else {
            // 0x001b8f94
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x001b8dd8
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001b8fa4 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x001B8FD0 sub_1B8FD0 [K_FldEvent_PickConditionalValue] -- 276 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B8FD0(unit, table, size) -> the value of the last matching 12-byte rule {u32 kind, u32 value, u32 arg}, from
// the end: kind 1 always, 2 when flag arg is set, 3 when the party member's condition (sub_16DBA0(unit +108)) equals
// arg; 0 when none matches. Caller: the field event task.
void sub_1B8FD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b8fd0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    v0 = 12;
    divu(a2, v0);
    mflo(s2);
    v0 = sll(s2, 1);
    v0 = addu(v0, s2);
    v0 = sll(v0, 2);
    v0 = addu(a1, v0);
    s1 = addiu(v0, -12);
    s3 = 0;
    s4 = 0;
    for (;;) {
        // 0x001b90ac
        charge(ctx, 3);
        v0 = sltu(s4, s2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001b9024
        charge(ctx, 4);
        lw(v1, s1, 0);
        v0 = 1;
        if (v1 == v0) {
            goto L_001b9034_2;
        }
        // 0x001b9040
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x001b904c
            charge(ctx, 6);
            lw(a0, s1, 8);
            jal(ctx, 0x1B9050u, gen::fn_datGetFlag_0016f190);
            v1 = 1;
            if (v0 != v1) {
                goto L_001b90a8;
            }
            goto L_001b9064_5;
        }
        // 0x001b9070
        charge(ctx, 3);
        v0 = 3;
        if (v1 != v0) {
        L_001b90a8:
            charge(ctx, 1);
            s4 = addiu(s4, 1);
            continue;
        }
        // 0x001b907c
        charge(ctx, 8);
        lw(s0, s1, 8);
        lh(a0, s5, 108);
        jal(ctx, 0x1B9084u, gen::fn_sub_16DBA0_0016dba0);
        v0 = dsll32(v0, 24);
        v0 = dsra32(v0, 24);
        if (s0 != v0) {
            goto L_001b90a8;
        }
        goto L_001b909c_8;
    }
    // 0x001b90b8 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    v0 = s3;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_001b9034_2:
    charge(ctx, 3);
    lw(s3, s1, 4);
    // 0x001b90b8 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    v0 = s3;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_001b9064_5:
    charge(ctx, 3);
    lw(s3, s1, 4);
    // 0x001b90b8 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    v0 = s3;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_001b909c_8:
    charge(ctx, 3);
    lw(s3, s1, 4);
    // 0x001b90b8 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    v0 = s3;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x001B90F0 K_Field_Init -- 48 bytes; frame 0x10: ra sp+0x0
// K_Field_Init(): memset(sField, 0, 4636) -- the whole field table (field4.h FieldTable).
void K_Field_Init(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b90f0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0x870000;
    a0 = addiu(a0, -24736);  // &sField
    a1 = 0;
    a2 = 4636;
    jal(ctx, 0x1B9108u, gen::fn_memset_00521408);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001B9140 sub_1B9140 [K_Field_SetupShadowCamera] -- 820 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1B9140(major, minor): sets the field's shadow / far parameters 0x7CE22C..0x7CE234 from the distance between the
// main camera and the hero's model (clamped 720..1100, scaled by 0x7CAFEC), with fixed values for field 14/5 and the
// rooms 6/1, 6/2, 6/4, 6/7, 6/11, 6/16, 6/20, 7/2..7/5; 0x7CE22C = 4.0f.
void sub_1B9140(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x001b9140
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    mtc1(zero, f1);
    v1 = 0x870000;
    lw(v1, v1, 6120);  // 0x8717E8
    v1 = sltu(0, v1);
    if (v1 != 0) {
        // 0x001b9170
        charge(ctx, 3);
        v1 = 0x870000;
        lw(v1, v1, 6132);  // 0x8717F4
        v1 = sltu(0, v1);
    }
    // 0x001b917c
    charge(ctx, 2);
    if (v1 != 0) {
        // 0x001b9184
        charge(ctx, 44);
        jal(ctx, 0x1B9184u, gen::fn_sub_198590_00198590);
        lw(a0, v0, 4);
        jal(ctx, 0x1B9190u, gen::fn_sub_4CB2F0_004cb2f0);
        lwc1(f2, v0, 48);
        lwc1(f1, v0, 52);
        lwc1(f0, v0, 56);
        swc1(f2, sp, 0x40);
        swc1(f1, sp, 0x44);
        swc1(f0, sp, 0x48);
        v0 = 0x870000;
        lw(a0, v0, 6128);  // 0x8717F0
        jal(ctx, 0x1B91B8u, gen::fn_sub_318B60_00318b60);
        lwc1(f1, v0, 48);
        lwc1(f0, sp, 0x40);
        sub_s(f0, f1, f0);
        swc1(f0, sp, 0x30);
        v0 = 0x870000;
        lw(a0, v0, 6128);  // 0x8717F0
        jal(ctx, 0x1B91D8u, gen::fn_sub_318B60_00318b60);
        lwc1(f1, v0, 52);
        lwc1(f0, sp, 0x44);
        sub_s(f0, f1, f0);
        swc1(f0, sp, 0x34);
        v0 = 0x870000;
        lw(a0, v0, 6128);  // 0x8717F0
        jal(ctx, 0x1B91F8u, gen::fn_sub_318B60_00318b60);
        lwc1(f1, v0, 56);
        lwc1(f0, sp, 0x48);
        sub_s(f0, f1, f0);
        swc1(f0, sp, 0x38);
        a0 = addiu(sp, 0x30);
        jal(ctx, 0x1B9214u, gen::fn_sub_4C6AC0_004c6ac0);
        v1 = 0x44340000;
        mtc1(v1, f1);
        c_lt_s(f0, f1);
        if (cond(ctx)) {
            // 0x001b9234
            charge(ctx, 1);
            mov_s(f0, f1);
        }
        // 0x001b9238
        charge(ctx, 7);
        v1 = 1100;
        mtc1(v1, f1);
        cvt_s_w(f1, f1);
        c_le_s(f0, f1);
        if (!cond(ctx)) {
            // 0x001b9254
            charge(ctx, 1);
            mov_s(f0, f1);
        }
        // 0x001b9258
        charge(ctx, 7);
        v1 = 1100;
        mtc1(v1, f1);
        cvt_s_w(f1, f1);
        div_s(f1, f0, f1);
        lwc1(f0, gp, -32004);  // 0x7CAFEC
        mul_s(f1, f0, f1);
    }
    // 0x001b9274
    charge(ctx, 4);
    v1 = s1 & 0xFFFF;
    a0 = 14;
    if (v1 == a0) {
        // 0x001b9284
        charge(ctx, 4);
        a1 = s0 & 0xFFFF;
        a0 = 5;
        if (a1 != a0) {
            goto L_001b92b4;
        }
        // 0x001b9294
        charge(ctx, 8);
        lwc1(f0, gp, -31668);  // 0x7CB13C
        swc1(f0, gp, -19132);  // 0x7CE234
        lwc1(f0, gp, -31664);  // 0x7CB140
        swc1(f0, gp, -19136);  // 0x7CE230
        v1 = 0x40800000;
        sw(v1, gp, -19140);  // 0x7CE22C
        // 0x001b945c (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_001b92b4:
    charge(ctx, 3);
    a0 = 6;
    if (v1 == a0) {
        // 0x001b92c0
        charge(ctx, 4);
        a1 = s0 & 0xFFFF;
        a0 = 1;
        if (a1 != a0) {
            goto L_001b92d0;
        }
    L_001b93e8:
        charge(ctx, 8);
        lwc1(f0, gp, -32004);  // 0x7CAFEC
        swc1(f0, gp, -19132);  // 0x7CE234
        lwc1(f0, gp, -32072);  // 0x7CAFA8
        swc1(f0, gp, -19136);  // 0x7CE230
        v1 = 0x40800000;
        sw(v1, gp, -19140);  // 0x7CE22C
        // 0x001b945c (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
L_001b92d0:
    charge(ctx, 3);
    a0 = 6;
    if (v1 == a0) {
        // 0x001b92dc
        charge(ctx, 4);
        a1 = s0 & 0xFFFF;
        a0 = 2;
        if (a1 == a0) {
            goto L_001b93e8;
        }
        goto L_001b92ec;
    }
L_001b92ec:
    charge(ctx, 3);
    a0 = 6;
    if (v1 == a0) {
        // 0x001b92f8
        charge(ctx, 4);
        a1 = s0 & 0xFFFF;
        a0 = 4;
        if (a1 == a0) {
            goto L_001b93e8;
        }
        goto L_001b9308;
    }
L_001b9308:
    charge(ctx, 3);
    a0 = 6;
    if (v1 == a0) {
        // 0x001b9314
        charge(ctx, 4);
        a1 = s0 & 0xFFFF;
        a0 = 7;
        if (a1 == a0) {
            goto L_001b93e8;
        }
        goto L_001b9324;
    }
L_001b9324:
    charge(ctx, 3);
    a0 = 6;
    if (v1 == a0) {
        // 0x001b9330
        charge(ctx, 4);
        a1 = s0 & 0xFFFF;
        a0 = 11;
        if (a1 == a0) {
            goto L_001b93e8;
        }
        goto L_001b9340;
    }
L_001b9340:
    charge(ctx, 3);
    a0 = 6;
    if (v1 == a0) {
        // 0x001b934c
        charge(ctx, 4);
        a1 = s0 & 0xFFFF;
        a0 = 16;
        if (a1 == a0) {
            goto L_001b93e8;
        }
        goto L_001b935c;
    }
L_001b935c:
    charge(ctx, 3);
    a0 = 6;
    if (v1 == a0) {
        // 0x001b9368
        charge(ctx, 4);
        a1 = s0 & 0xFFFF;
        a0 = 20;
        if (a1 == a0) {
            goto L_001b93e8;
        }
        goto L_001b9378;
    }
L_001b9378:
    charge(ctx, 3);
    a0 = 7;
    if (v1 == a0) {
        // 0x001b9384
        charge(ctx, 4);
        a1 = s0 & 0xFFFF;
        a0 = 2;
        if (a1 == a0) {
            goto L_001b93e8;
        }
        goto L_001b9394;
    }
L_001b9394:
    charge(ctx, 3);
    a0 = 7;
    if (v1 == a0) {
        // 0x001b93a0
        charge(ctx, 4);
        a1 = s0 & 0xFFFF;
        a0 = 3;
        if (a1 == a0) {
            goto L_001b93e8;
        }
        goto L_001b93b0;
    }
L_001b93b0:
    charge(ctx, 3);
    a0 = 7;
    if (v1 == a0) {
        // 0x001b93bc
        charge(ctx, 4);
        a1 = s0 & 0xFFFF;
        a0 = 4;
        if (a1 == a0) {
            goto L_001b93e8;
        }
        goto L_001b93cc;
    }
L_001b93cc:
    charge(ctx, 3);
    a0 = 7;
    if (v1 == a0) {
        // 0x001b93d8
        charge(ctx, 4);
        a0 = s0 & 0xFFFF;
        v1 = 5;
        if (a0 != v1) {
            goto L_001b9408;
        }
        goto L_001b93e8;
    }
L_001b9408:
    charge(ctx, 5);
    mtc1(zero, f0);
    c_le_s(f1, f0);
    if (cond(ctx)) {
        // 0x001b9444
        charge(ctx, 6);
        lwc1(f0, gp, -32004);  // 0x7CAFEC
        swc1(f0, gp, -19132);  // 0x7CE234
        lwc1(f0, gp, -32072);  // 0x7CAFA8
        swc1(f0, gp, -19136);  // 0x7CE230
        v1 = 0x40800000;
        sw(v1, gp, -19140);  // 0x7CE22C
    } else {
        // 0x001b941c
        charge(ctx, 10);
        swc1(f1, gp, -19132);  // 0x7CE234
        v1 = 0x43000000;
        mtc1(v1, f0);
        mul_s(f0, f0, f1);
        swc1(f0, gp, -19136);  // 0x7CE230
        v1 = 0x40800000;
        sw(v1, gp, -19140);  // 0x7CE22C
    }
    // 0x001b945c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001B9480 K_Field_UpdateFieldRootTask -- 3920 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// K_Field_UpdateFieldRootTask(task) -> 0, or -1 to be destroyed: the 19-state field root (26_field.md 2.2; work:
// field4.h FieldRootWork). The jump table 0x7B6B30 dispatches; states fall through into the next as the original:
//   0 event PM file ready -> ids (K_Assert k_field.c 293 / 309), .pac requested, the four PC models freed     -> 2
//   1 boot data ready (stream, base model, battle-effect pack + EPLs)                                         -> 2
//   2 .pac resident -> field script request (sub_1E7200)                                                      -> 3
//   3 field script copied (sub_1E7290) -> phase 0; script procedure minor - 1 (or minor - 50 on 20..28 / 40..48)
//   4 script done -> hit table, MT_Scene_Load, sub-ids (sub_3B58C0 / sub_3B5980; time-of-day variant sub_1B6EB0),
//     "NOW LOADING" (sub_187E20)                                                                             -> 5
//   5 hit table + scene ready -> phase 3, script procedure                                                    -> 6
//   6 script done -> camera controller (sField +4), sub_1D70A0, the party's field units (sub_1D03F0(entry))   -> 7
//   7 PC models ready: event -> BGM / ambience, event viewer (+60) -> 14; else the camera follows the hero    -> 8
//   8 phase 1; field script (random floors: the dungeon script procedure 2 and the block script request)      -> 9
//   9 transparent walls, enemy pop scheduler, treasure, footsteps, panels, mini-map                          -> 10
//  10 all of them ready: shadows placed, BGM, ambience, sub_1B9140, fade in (40 frames for the entrance 32/2) -> 11
//  11 fade done -> phase 2 (running), script procedure                                                        -> 12
//  12 script done -> virtual pad (sField +12), field event task (sField +8), unpause                         -> 13
//  13 running: the shutdown word +8 -> 18
//  14..16 the event viewer, then PCs / camera / header script / walls                                        -> 11
//  17 exit fade done -> adminiChangeSeq(2, work +76, 28, 0)                                                   -> 18
//  18 -> -1.
void K_Field_UpdateFieldRootTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001b9480
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, f4::kTaskWork);
    lw(v0, s0, f4::root::kState);
    at = sltiu(v0, 19);
    if (at != 0) {
        // 0x001b94ac
        charge(ctx, 7);
        v1 = 0x7B0000;
        v1 = addiu(v1, 27440);  // &0x7B6B30
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x1B94C8u:  // table[0]  -- state 0: the event PM file read -> the field ids (K_Assert 293 / 309), the .pac, the PC models freed -> 2
            // 0x001b94c8
            charge(ctx, 5);
            lw(a0, s0, f4::root::kPmReader);
            jal(ctx, 0x1B94CCu, gen::fn_sub_398060_00398060);
            if (v0 != 0) {
                // 0x001b94dc
                charge(ctx, 10);
                lw(a0, s0, f4::root::kPmReader);
                a1 = addiu(sp, 0x4C);
                a2 = addiu(sp, 0x48);
                a3 = addiu(sp, 0x44);
                t0 = addiu(sp, 0x40);
                jal(ctx, 0x1B94F0u, gen::fn_sub_398140_00398140);
                v1 = 1;
                if (v0 != v1) {
                    // 0x001b9590
                    charge(ctx, 7);
                    a0 = 0x680000;
                    a0 = addiu(a0, -2696);  // "k_field.c"
                    a1 = 309;
                    jal(ctx, 0x1B959Cu, gen::fn_sub_19D3F0_0019d3f0);
                } else {
                    // 0x001b9504
                    charge(ctx, 3);
                    lw(v0, sp, 0x4C);
                    if (v0 == 0) {
                        // 0x001b9510
                        charge(ctx, 5);
                        a0 = 0x680000;
                        a0 = addiu(a0, -2696);  // "k_field.c"
                        a1 = 293;
                        jal(ctx, 0x1B951Cu, gen::fn_sub_19D3F0_0019d3f0);
                    }
                    // 0x001b9524
                    charge(ctx, 15);
                    lw(v0, sp, 0x4C);
                    sh(v0, s0, f4::root::kMajor);
                    lw(v0, sp, 0x48);
                    sh(v0, s0, f4::root::kMinor);
                    lw(v0, sp, 0x44);
                    sh(v0, s0, f4::root::kSub1);
                    lw(v0, sp, 0x40);
                    sh(v0, s0, f4::root::kSub2);
                    lh(a0, s0, f4::root::kMajor);
                    lh(a1, s0, f4::root::kMinor);
                    jal(ctx, 0x1B954Cu, gen::fn_sub_1B0870_001b0870);
                    s1 = 0;
                    for (;;) {
                        // 0x001b9570
                        charge(ctx, 4);
                        v0 = slti(s1, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001b9560
                        charge(ctx, 4);
                        a0 = s1;
                        jal(ctx, 0x1B9564u, gen::fn_sub_1CD870_001cd870);
                        s1 = addiu(s1, 1);
                    }
                    // 0x001b9580
                    charge(ctx, 4);
                    v0 = 2;
                    sw(v0, s0, f4::root::kState);
                }
            }
        L_001ba3b0:
            charge(ctx, 1);
            v0 = 0;
            break;
        case 0x1B95ACu:  // table[1]  -- state 1: boot data, battle-effect pack and EPLs ready; then falls into 2..7 as the original's gotos
            // 0x001b95ac
            charge(ctx, 4);
            jal(ctx, 0x1B95ACu, gen::fn_sub_1B7D60_001b7d60);
            if (v0 != 0) {
                // 0x001b95bc
                charge(ctx, 4);
                jal(ctx, 0x1B95BCu, gen::fn_sub_1B7E30_001b7e30);
                if (v0 != 0) {
                    // 0x001b95cc
                    charge(ctx, 4);
                    jal(ctx, 0x1B95CCu, gen::fn_sub_1C0440_001c0440);
                    if (v0 != 0) {
                        // 0x001b95dc
                        charge(ctx, 4);
                        jal(ctx, 0x1B95DCu, gen::fn_sub_1C0740_001c0740);
                        if (v0 != 0) {
                            // 0x001b95ec
                            charge(ctx, 3);
                            lw(v0, s0, f4::root::kState);
                            v0 = addiu(v0, 1);
                            sw(v0, s0, f4::root::kState);
                        // state 2: (falls in from 1) .pac resident -> the field script request (the state's entry)
                        L_001b95f8:
                            charge(ctx, 4);
                            jal(ctx, 0x1B95F8u, gen::fn_sub_1B08D0_001b08d0);
                            if (v0 != 0) {
                                // 0x001b9608
                                charge(ctx, 7);
                                lhu(a0, s0, f4::root::kMajor);
                                jal(ctx, 0x1B960Cu, gen::fn_sub_1E7200_001e7200);
                                sw(v0, s0, f4::root::kScriptRequest);
                                lw(v0, s0, f4::root::kState);
                                v0 = addiu(v0, 1);
                                sw(v0, s0, f4::root::kState);
                            // state 3: the field script copied -> phase 0, script procedure (minor - 1 / minor - 50) (the state's entry)
                            L_001b9624:
                                charge(ctx, 6);
                                lw(a0, s0, f4::root::kScriptRequest);
                                lhu(a1, s0, f4::root::kMajor);
                                jal(ctx, 0x1B962Cu, gen::fn_sub_1E7290_001e7290);
                                if (v0 != 0) {
                                    // 0x001b963c
                                    charge(ctx, 5);
                                    sw(zero, s0, f4::root::kScriptRequest);
                                    sw(zero, gp, f4::gpv::kPhase);  // 0x7CE24C
                                    lw(v0, s0, f4::root::kPmReader);
                                    if (v0 == 0) {
                                        // 0x001b9650
                                        charge(ctx, 4);
                                        v0 = 0x870000;
                                        lw(a1, v0, -20568);  // 0x86AFA8
                                        if (a1 != 0) {
                                            // 0x001b9660
                                            charge(ctx, 4);
                                            lhu(v1, s0, f4::root::kMajor);
                                            v0 = slti(v1, 20);
                                            if (v0 == 0) {
                                                // 0x001b9670
                                                charge(ctx, 3);
                                                at = slti(v1, 29);
                                                if (at == 0) {
                                                    goto L_001b968c;
                                                }
                                                // 0x001b967c
                                                charge(ctx, 4);
                                                lhu(a0, s0, f4::root::kMinor);
                                                at = slti(a0, 50);
                                                if (at != 0) {
                                                    goto L_001b968c;
                                                }
                                            L_001b96b4:
                                                charge(ctx, 9);
                                                v0 = 0x870000;
                                                lw(a2, v0, -20564);  // 0x86AFAC
                                                a3 = addiu(a0, -50);
                                                a0 = 10;
                                                jal(ctx, 0x1B96C4u, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                                                sw(v0, s0, f4::root::kScriptTask);
                                                goto L_001b9728;
                                            }
                                        L_001b968c:
                                            charge(ctx, 3);
                                            v0 = slti(v1, 40);
                                            if (v0 == 0) {
                                                // 0x001b9698
                                                charge(ctx, 3);
                                                at = slti(v1, 49);
                                                if (at == 0) {
                                                    goto L_001b96d8;
                                                }
                                                // 0x001b96a4
                                                charge(ctx, 4);
                                                lhu(a0, s0, f4::root::kMinor);
                                                v0 = slti(a0, 50);
                                                if (v0 != 0) {
                                                    goto L_001b96d8;
                                                }
                                                goto L_001b96b4;
                                            }
                                        L_001b96d8:
                                            charge(ctx, 3);
                                            v0 = slti(v1, 20);
                                            if (v0 == 0) {
                                                // 0x001b96e4
                                                charge(ctx, 3);
                                                at = slti(v1, 29);
                                                if (at == 0) {
                                                    // 0x001b96f0
                                                    charge(ctx, 3);
                                                    v0 = slti(v1, 40);
                                                    if (v0 != 0) {
                                                        goto L_001b9708;
                                                    }
                                                    goto L_001b96fc;
                                                }
                                            L_001b96fc:
                                                charge(ctx, 3);
                                                at = slti(v1, 49);
                                                if (at == 0) {
                                                    goto L_001b9708;
                                                }
                                                goto L_001b9728;
                                            }
                                        L_001b9708:
                                            charge(ctx, 8);
                                            v0 = 0x870000;
                                            lw(a2, v0, -20564);  // 0x86AFAC
                                            lhu(v0, s0, f4::root::kMinor);
                                            a3 = addiu(v0, -1);
                                            a0 = 10;
                                            jal(ctx, 0x1B971Cu, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                                            sw(v0, s0, f4::root::kScriptTask);
                                        }
                                    }
                                L_001b9728:
                                    charge(ctx, 3);
                                    lw(v0, s0, f4::root::kState);
                                    v0 = addiu(v0, 1);
                                    sw(v0, s0, f4::root::kState);
                                // state 4: the script done -> hit table, MT_Scene_Load, sub-ids, NOW LOADING (the state's entry)
                                L_001b9734:
                                    charge(ctx, 3);
                                    lw(v0, s0, f4::root::kPmReader);
                                    if (v0 == 0) {
                                        // 0x001b9740
                                        charge(ctx, 3);
                                        lw(a0, s0, f4::root::kScriptTask);
                                        if (a0 == 0) {
                                            goto L_001b9760;
                                        }
                                        // 0x001b974c
                                        charge(ctx, 5);
                                        jal(ctx, 0x1B974Cu, gen::fn_kwlnTaskExists_00195460);
                                        v1 = 1;
                                        if (v0 != v1) {
                                            goto L_001b9760;
                                        }
                                        goto L_001ba3b0;
                                    }
                                L_001b9760:
                                    charge(ctx, 15);
                                    lhu(a0, s0, f4::root::kMajor);
                                    lhu(a1, s0, f4::root::kMinor);
                                    jal(ctx, 0x1B9768u, gen::fn_K_Fldrc_RequestFieldHitTableFile_001c7e70);
                                    sw(v0, s0, f4::root::kHitRequest);
                                    lhu(a0, s0, f4::root::kMajor);
                                    lhu(a1, s0, f4::root::kMinor);
                                    jal(ctx, 0x1B977Cu, gen::fn_MT_Scene_Load_003b5760);
                                    lh(a0, s0, f4::root::kSub1);
                                    jal(ctx, 0x1B9788u, gen::fn_sub_3B58C0_003b58c0);
                                    lh(a0, s0, f4::root::kSub2);
                                    if (a0 == 0) {
                                        // 0x001b97ac
                                        charge(ctx, 9);
                                        lhu(a0, s0, f4::root::kMajor);
                                        lhu(a1, s0, f4::root::kMinor);
                                        jal(ctx, 0x1B97B4u, gen::fn_sub_1B6EB0_001b6eb0);
                                        sh(v0, s0, f4::root::kSub2);
                                        a0 = dsll32(v0, 16);
                                        a0 = dsra32(a0, 16);
                                        jal(ctx, 0x1B97C8u, gen::fn_sub_3B5980_003b5980);
                                    } else {
                                        // 0x001b979c
                                        charge(ctx, 4);
                                        jal(ctx, 0x1B979Cu, gen::fn_sub_3B5980_003b5980);
                                    }
                                    // 0x001b97d0
                                    charge(ctx, 6);
                                    jal(ctx, 0x1B97D0u, gen::fn_sub_187E20_00187e20);
                                    sw(v0, s0, f4::root::kNowLoading);
                                    lw(v0, s0, f4::root::kState);
                                    v0 = addiu(v0, 1);
                                    sw(v0, s0, f4::root::kState);
                                // state 5: hit table + scene loaded -> phase 3, script procedure (the state's entry)
                                L_001b97e8:
                                    charge(ctx, 5);
                                    lw(a0, s0, f4::root::kHitRequest);
                                    jal(ctx, 0x1B97ECu, gen::fn_sub_1C7F20_001c7f20);
                                    if (v0 != 0) {
                                        // 0x001b97fc
                                        charge(ctx, 5);
                                        sw(zero, s0, f4::root::kHitRequest);
                                        jal(ctx, 0x1B9800u, gen::fn_sub_3B5A10_003b5a10);
                                        if (v0 != 0) {
                                            // 0x001b9810
                                            charge(ctx, 6);
                                            v0 = 3;
                                            sw(v0, gp, f4::gpv::kPhase);  // 0x7CE24C
                                            v0 = 0x870000;
                                            lw(a1, v0, -20568);  // 0x86AFA8
                                            if (a1 != 0) {
                                                // 0x001b9828
                                                charge(ctx, 4);
                                                lhu(v1, s0, f4::root::kMajor);
                                                v0 = slti(v1, 20);
                                                if (v0 == 0) {
                                                    // 0x001b9838
                                                    charge(ctx, 3);
                                                    at = slti(v1, 29);
                                                    if (at == 0) {
                                                        goto L_001b9854;
                                                    }
                                                    // 0x001b9844
                                                    charge(ctx, 4);
                                                    lhu(a0, s0, f4::root::kMinor);
                                                    at = slti(a0, 50);
                                                    if (at != 0) {
                                                        goto L_001b9854;
                                                    }
                                                L_001b987c:
                                                    charge(ctx, 9);
                                                    v0 = 0x870000;
                                                    lw(a2, v0, -20564);  // 0x86AFAC
                                                    a3 = addiu(a0, -50);
                                                    a0 = 10;
                                                    jal(ctx, 0x1B988Cu, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                                                    sw(v0, s0, f4::root::kScriptTask);
                                                    goto L_001b98f0;
                                                }
                                            L_001b9854:
                                                charge(ctx, 3);
                                                v0 = slti(v1, 40);
                                                if (v0 == 0) {
                                                    // 0x001b9860
                                                    charge(ctx, 3);
                                                    at = slti(v1, 49);
                                                    if (at == 0) {
                                                        goto L_001b98a0;
                                                    }
                                                    // 0x001b986c
                                                    charge(ctx, 4);
                                                    lhu(a0, s0, f4::root::kMinor);
                                                    v0 = slti(a0, 50);
                                                    if (v0 != 0) {
                                                        goto L_001b98a0;
                                                    }
                                                    goto L_001b987c;
                                                }
                                            L_001b98a0:
                                                charge(ctx, 3);
                                                v0 = slti(v1, 20);
                                                if (v0 == 0) {
                                                    // 0x001b98ac
                                                    charge(ctx, 3);
                                                    at = slti(v1, 29);
                                                    if (at == 0) {
                                                        // 0x001b98b8
                                                        charge(ctx, 3);
                                                        v0 = slti(v1, 40);
                                                        if (v0 != 0) {
                                                            goto L_001b98d0;
                                                        }
                                                        goto L_001b98c4;
                                                    }
                                                L_001b98c4:
                                                    charge(ctx, 3);
                                                    at = slti(v1, 49);
                                                    if (at == 0) {
                                                        goto L_001b98d0;
                                                    }
                                                    goto L_001b98f0;
                                                }
                                            L_001b98d0:
                                                charge(ctx, 8);
                                                v0 = 0x870000;
                                                lw(a2, v0, -20564);  // 0x86AFAC
                                                lhu(v0, s0, f4::root::kMinor);
                                                a3 = addiu(v0, -1);
                                                a0 = 10;
                                                jal(ctx, 0x1B98E4u, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                                                sw(v0, s0, f4::root::kScriptTask);
                                            }
                                        L_001b98f0:
                                            charge(ctx, 3);
                                            lw(v0, s0, f4::root::kState);
                                            v0 = addiu(v0, 1);
                                            sw(v0, s0, f4::root::kState);
                                        // state 6: the script done -> camera controller, party field units (the state's entry)
                                        L_001b98fc:
                                            charge(ctx, 3);
                                            lw(a0, s0, f4::root::kScriptTask);
                                            if (a0 != 0) {
                                                // 0x001b9908
                                                charge(ctx, 5);
                                                jal(ctx, 0x1B9908u, gen::fn_kwlnTaskExists_00195460);
                                                v1 = 1;
                                                if (v0 != v1) {
                                                    goto L_001b991c;
                                                }
                                                goto L_001ba3b0;
                                            }
                                        L_001b991c:
                                            charge(ctx, 10);
                                            a0 = s1;
                                            jal(ctx, 0x1B9920u, gen::fn_K_FldCamera_CreateFieldCameraControlerTask_001d5a90);
                                            v1 = 0x870000;
                                            sw(v0, v1, -24732);  // 0x869F64
                                            jal(ctx, 0x1B9930u, gen::fn_sub_1D70A0_001d70a0);
                                            lw(v0, s0, f4::root::kPmReader);
                                            if (v0 == 0) {
                                                // 0x001b9944
                                                charge(ctx, 3);
                                                lhu(a0, s0, f4::root::kEntry);
                                                jal(ctx, 0x1B9948u, gen::fn_sub_1D03F0_001d03f0);
                                            }
                                            // 0x001b9950
                                            charge(ctx, 3);
                                            lw(v0, s0, f4::root::kState);
                                            v0 = addiu(v0, 1);
                                            sw(v0, s0, f4::root::kState);
                                        // state 7: PC models ready -> event viewer (14) or the camera follows the hero (8) (the state's entry)
                                        L_001b995c:
                                            charge(ctx, 4);
                                            jal(ctx, 0x1B995Cu, gen::fn_sub_1CE960_001ce960);
                                            if (v0 != 0) {
                                                // 0x001b996c
                                                charge(ctx, 5);
                                                jal(ctx, 0x1B996Cu, gen::fn_sub_1D19D0_001d19d0);
                                                lw(v0, s0, f4::root::kPmReader);
                                                if (v0 == 0) {
                                                    // 0x001b99fc
                                                    charge(ctx, 17);
                                                    v0 = 0x870000;
                                                    lw(v1, v0, 6132);  // 0x8717F4
                                                    v0 = 0x870000;
                                                    lw(a0, v0, -24732);  // 0x869F64
                                                    lhu(a1, v1, 0);
                                                    jal(ctx, 0x1B9A10u, gen::fn_sub_1D5F30_001d5f30);
                                                    a0 = s1;
                                                    a1 = 1;
                                                    a2 = si(-1);
                                                    jal(ctx, 0x1B9A24u, gen::fn_sub_1D6270_001d6270);
                                                    lw(v0, s0, f4::root::kState);
                                                    v0 = addiu(v0, 1);
                                                    sw(v0, s0, f4::root::kState);
                                                } else {
                                                    // 0x001b9980
                                                    charge(ctx, 6);
                                                    a0 = 5136;
                                                    jal(ctx, 0x1B9984u, gen::fn_datGetFlag_0016f190);
                                                    v1 = 1;
                                                    if (v0 != v1) {
                                                        // 0x001b9998
                                                        charge(ctx, 3);
                                                        lw(v0, s0, f4::root::kHold);
                                                        if (v0 != v1) {
                                                            // 0x001b99a4
                                                            charge(ctx, 5);
                                                            lw(a0, s0, f4::root::kPmReader);
                                                            jal(ctx, 0x1B99A8u, gen::fn_sub_3982D0_003982d0);
                                                            if (v0 == 0) {
                                                                // 0x001b99b8
                                                                charge(ctx, 2);
                                                                jal(ctx, 0x1B99B8u, gen::fn_sub_1A9850_001a9850);
                                                            }
                                                            // 0x001b99c0
                                                            charge(ctx, 15);
                                                            jal(ctx, 0x1B99C0u, gen::fn_sub_1AA1B0_001aa1b0);
                                                            lw(a0, s0, f4::root::kNowLoading);
                                                            jal(ctx, 0x1B99CCu, gen::fn_sub_187EA0_00187ea0);
                                                            sw(zero, s0, f4::root::kNowLoading);
                                                            a0 = s1;
                                                            lw(a1, s0, f4::root::kPmReader);
                                                            jal(ctx, 0x1B99E0u, gen::fn_mtEvtMain_CreateZikkiPlayModeEventViewerTask_0036f3b0);
                                                            sw(v0, s0, f4::root::kEventViewer);
                                                            v0 = 14;
                                                            sw(v0, s0, f4::root::kState);
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
            goto L_001ba3b0;
        case 0x1B95F8u:  // table[2]  -- state 2: (falls in from 1) .pac resident -> the field script request
            goto L_001b95f8;
        case 0x1B9624u:  // table[3]  -- state 3: the field script copied -> phase 0, script procedure (minor - 1 / minor - 50)
            goto L_001b9624;
        case 0x1B9734u:  // table[4]  -- state 4: the script done -> hit table, MT_Scene_Load, sub-ids, NOW LOADING
            goto L_001b9734;
        case 0x1B97E8u:  // table[5]  -- state 5: hit table + scene loaded -> phase 3, script procedure
            goto L_001b97e8;
        case 0x1B98FCu:  // table[6]  -- state 6: the script done -> camera controller, party field units
            goto L_001b98fc;
        case 0x1B995Cu:  // table[7]  -- state 7: PC models ready -> event viewer (14) or the camera follows the hero (8)
            goto L_001b995c;
        case 0x1B9A40u:  // table[8]  -- state 8: phase 1; the field / dungeon block script
            // 0x001b9a40
            charge(ctx, 5);
            v0 = 1;
            sw(v0, gp, f4::gpv::kPhase);  // 0x7CE24C
            lw(v0, s0, f4::root::kPmReader);
            if (v0 == 0) {
                // 0x001b9a54
                charge(ctx, 4);
                v0 = 0x870000;
                lw(a1, v0, -20568);  // 0x86AFA8
                if (a1 != 0) {
                    // 0x001b9a64
                    charge(ctx, 4);
                    lhu(v1, s0, f4::root::kMajor);
                    v0 = slti(v1, 20);
                    if (v0 == 0) {
                        // 0x001b9a74
                        charge(ctx, 3);
                        at = slti(v1, 29);
                        if (at == 0) {
                            goto L_001b9a90;
                        }
                        // 0x001b9a80
                        charge(ctx, 4);
                        lhu(a0, s0, f4::root::kMinor);
                        at = slti(a0, 50);
                        if (at != 0) {
                            goto L_001b9a90;
                        }
                    L_001b9ab8:
                        charge(ctx, 7);
                        a2 = addiu(a0, -50);
                        a0 = 10;
                        jal(ctx, 0x1B9AC0u, gen::fn_scrCreateTaskFromHeader_0035bb40);
                        sw(v0, s0, f4::root::kScriptTask);
                        goto L_001b9b88;
                    }
                L_001b9a90:
                    charge(ctx, 3);
                    v0 = slti(v1, 40);
                    if (v0 == 0) {
                        // 0x001b9a9c
                        charge(ctx, 3);
                        at = slti(v1, 49);
                        if (at == 0) {
                            goto L_001b9ad4;
                        }
                        // 0x001b9aa8
                        charge(ctx, 4);
                        lhu(a0, s0, f4::root::kMinor);
                        v0 = slti(a0, 50);
                        if (v0 != 0) {
                            goto L_001b9ad4;
                        }
                        goto L_001b9ab8;
                    }
                L_001b9ad4:
                    charge(ctx, 3);
                    v0 = slti(v1, 20);
                    if (v0 == 0) {
                        // 0x001b9ae0
                        charge(ctx, 3);
                        at = slti(v1, 29);
                        if (at == 0) {
                            // 0x001b9aec
                            charge(ctx, 3);
                            v0 = slti(v1, 40);
                            if (v0 != 0) {
                                goto L_001b9b04;
                            }
                            goto L_001b9af8;
                        }
                    L_001b9af8:
                        charge(ctx, 3);
                        at = slti(v1, 49);
                        if (at == 0) {
                            goto L_001b9b04;
                        }
                        // 0x001b9b24
                        charge(ctx, 3);
                        lhu(v0, s0, f4::root::kMinor);
                        if (v0 == 0) {
                            // 0x001b9b30
                            charge(ctx, 4);
                            jal(ctx, 0x1B9B30u, gen::fn_K_FldDungeon_GetScrMemory_001bffe0);
                            if (v0 != 0) {
                                // 0x001b9b40
                                charge(ctx, 12);
                                jal(ctx, 0x1B9B40u, gen::fn_K_FldDungeon_GetScrMemory_001bffe0);
                                s2 = v0;
                                jal(ctx, 0x1B9B4Cu, gen::fn_K_FldDungeon_GetScrSize_001c0010);
                                a0 = 10;
                                a1 = s2;
                                a2 = v0;
                                a3 = 2;
                                jal(ctx, 0x1B9B64u, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                                sw(v0, s0, f4::root::kScriptTask);
                            }
                            // 0x001b9b70
                            charge(ctx, 6);
                            jal(ctx, 0x1B9B70u, gen::fn_K_FldDungeon_GetCurrentFloorData_001bffa0);
                            lbu(a0, v0, 12);
                            jal(ctx, 0x1B9B7Cu, gen::fn_sub_1C0330_001c0330);
                            sw(v0, s0, f4::root::kBlockScript);
                        }
                        goto L_001b9b88;
                    }
                L_001b9b04:
                    charge(ctx, 8);
                    lhu(v0, s0, f4::root::kMinor);
                    a2 = addiu(v0, -1);
                    a0 = 10;
                    jal(ctx, 0x1B9B10u, gen::fn_scrCreateTaskFromHeader_0035bb40);
                    sw(v0, s0, f4::root::kScriptTask);
                }
            }
        L_001b9b88:
            charge(ctx, 3);
            lw(v0, s0, f4::root::kState);
            v0 = addiu(v0, 1);
            sw(v0, s0, f4::root::kState);
        // state 9: walls, enemy scheduler, treasure, footsteps, panels, mini-map; then 10 (the state's entry)
        L_001b9b94:
            charge(ctx, 3);
            lw(v0, s0, f4::root::kPmReader);
            if (v0 == 0) {
                // 0x001b9ba0
                charge(ctx, 3);
                lw(a0, s0, f4::root::kScriptTask);
                if (a0 == 0) {
                    goto L_001b9bc0;
                }
                // 0x001b9bac
                charge(ctx, 5);
                jal(ctx, 0x1B9BACu, gen::fn_kwlnTaskExists_00195460);
                v1 = 1;
                if (v0 != v1) {
                    goto L_001b9bc0;
                }
                goto L_001ba3b0;
            }
        L_001b9bc0:
            charge(ctx, 31);
            v0 = 0x870000;
            lw(v0, v0, 6132);  // 0x8717F4
            a0 = s1;
            lw(a1, v0, 480);
            jal(ctx, 0x1B9BD0u, gen::fn_sub_1C1F30_001c1f30);
            v1 = 0x870000;
            sw(v0, v1, -24708);  // 0x869F7C
            a0 = 5137;
            a1 = 0;
            jal(ctx, 0x1B9BE8u, gen::fn_datSetFlag_0016f1f0);
            a0 = s1;
            jal(ctx, 0x1B9BF4u, gen::fn_sub_1D36F0_001d36f0);
            v1 = 0x870000;
            sw(v0, v1, -24700);  // 0x869F84
            jal(ctx, 0x1B9C04u, gen::fn_sub_1D2610_001d2610);
            jal(ctx, 0x1B9C0Cu, gen::fn_sub_1D1FA0_001d1fa0);
            a0 = s1;
            jal(ctx, 0x1B9C18u, gen::fn_sub_1D9F10_001d9f10);
            v1 = 0x870000;
            sw(v0, v1, -24704);  // 0x869F80
            jal(ctx, 0x1B9C28u, gen::fn_sub_1DD600_001dd600);
            v1 = 1;
            if (v0 == v1) {
                // 0x001b9c3c
                charge(ctx, 9);
                a0 = s1;
                jal(ctx, 0x1B9C40u, gen::fn_sub_18BFF0_0018bff0);
                v1 = 0x870000;
                sw(v0, v1, -24696);  // 0x869F88
                a0 = v0;
                a1 = 0;
                jal(ctx, 0x1B9C58u, gen::fn_sub_18C0C0_0018c0c0);
            }
            // 0x001b9c60
            charge(ctx, 4);
            lhu(v0, s0, f4::root::kMajor);
            at = slti(v0, 200);
            if (at != 0) {
                // 0x001b9c70
                charge(ctx, 13);
                a0 = s1;
                jal(ctx, 0x1B9C74u, gen::fn_sub_18E820_0018e820);
                v1 = 0x870000;
                sw(v0, v1, -24692);  // 0x869F8C
                a0 = si(-1);
                jal(ctx, 0x1B9C88u, gen::fn_sub_1DDCA0_001ddca0);
                v0 = 0x870000;
                lw(a0, v0, -24692);  // 0x869F8C
                a1 = 0;
                jal(ctx, 0x1B9C9Cu, gen::fn_sub_18EB30_0018eb30);
            }
            // 0x001b9ca4
            charge(ctx, 4);
            lhu(v1, s0, f4::root::kMajor);
            v0 = 14;
            if (v1 == v0) {
                // 0x001b9cb4
                charge(ctx, 4);
                lhu(v1, s0, f4::root::kMinor);
                v0 = 5;
                if (v1 == v0) {
                    // 0x001b9cc4
                    charge(ctx, 4);
                    a0 = s1;
                    jal(ctx, 0x1B9CC8u, gen::fn_Y_Kyoto_CreateKyotoNpcModeReadTask_004579b0);
                    sw(v0, s0, f4::root::kNpcMode);
                }
            }
            // 0x001b9cd4
            charge(ctx, 9);
            a0 = s1;
            ld(a1, gp, -27216);  // 0x7CC2A0
            jal(ctx, 0x1B9CDCu, gen::fn_Y_SMap_CreateSmapDrawTask_00429d40);
            v1 = 0x870000;
            sw(v0, v1, -24712);  // 0x869F78
            lw(v0, s0, f4::root::kState);
            v0 = addiu(v0, 1);
            sw(v0, s0, f4::root::kState);
        // state 10: all ready -> shadows, BGM, ambience, sub_1B9140, fade in -> 11 (the state's entry)
        L_001b9cf8:
            charge(ctx, 6);
            v0 = 0x870000;
            lw(a0, v0, -24700);  // 0x869F84
            jal(ctx, 0x1B9D00u, gen::fn_sub_1D3790_001d3790);
            if (v0 != 0) {
                // 0x001b9d10
                charge(ctx, 13);
                v0 = 0x870000;
                lw(a0, v0, -24700);  // 0x869F84
                a1 = 1;
                jal(ctx, 0x1B9D1Cu, gen::fn_sub_1D37F0_001d37f0);
                a0 = 1;
                jal(ctx, 0x1B9D28u, gen::fn_sub_4532D0_004532d0);
                lw(a0, s0, f4::root::kBlockScript);
                jal(ctx, 0x1B9D34u, gen::fn_sub_1C03B0_001c03b0);
                if (v0 != 0) {
                    // 0x001b9d44
                    charge(ctx, 6);
                    v0 = 0x870000;
                    lw(a0, v0, -24704);  // 0x869F80
                    jal(ctx, 0x1B9D4Cu, gen::fn_sub_1D9FD0_001d9fd0);
                    if (v0 != 0) {
                        // 0x001b9d5c
                        charge(ctx, 10);
                        v0 = 0x870000;
                        lw(a0, v0, -24704);  // 0x869F80
                        a1 = 1;
                        jal(ctx, 0x1B9D68u, gen::fn_sub_1DA000_001da000);
                        jal(ctx, 0x1B9D70u, gen::fn_sub_1DD600_001dd600);
                        v1 = 1;
                        if (v0 == v1) {
                            // 0x001b9d84
                            charge(ctx, 6);
                            v0 = 0x870000;
                            lw(a0, v0, -24696);  // 0x869F88
                            jal(ctx, 0x1B9D8Cu, gen::fn_sub_18C0A0_0018c0a0);
                            if (v0 != 0) {
                                // 0x001b9d9c
                                charge(ctx, 2);
                                jal(ctx, 0x1B9D9Cu, gen::fn_sub_1DD8E0_001dd8e0);
                                goto L_001b9da4;
                            }
                            goto L_001ba3b0;
                        }
                    L_001b9da4:
                        charge(ctx, 4);
                        lhu(v1, s0, f4::root::kMajor);
                        v0 = 14;
                        if (v1 == v0) {
                            // 0x001b9db4
                            charge(ctx, 4);
                            lhu(v1, s0, f4::root::kMinor);
                            v0 = 5;
                            if (v1 != v0) {
                                goto L_001b9ddc;
                            }
                            // 0x001b9dc4
                            charge(ctx, 6);
                            lw(a0, s0, f4::root::kNpcMode);
                            jal(ctx, 0x1B9DC8u, gen::fn_kwlnTaskExists_00195460);
                            v1 = 1;
                            if (v0 != v1) {
                                goto L_001b9ddc;
                            }
                            goto L_001ba3b0;
                        }
                    L_001b9ddc:
                        charge(ctx, 4);
                        v0 = 0x870000;
                        lw(v0, v0, -24712);  // 0x869F78
                        if (v0 != 0) {
                            // 0x001b9dec
                            charge(ctx, 4);
                            jal(ctx, 0x1B9DECu, gen::fn_sub_42BA30_0042ba30);
                            if (v0 != 0) {
                                goto L_001b9dfc;
                            }
                            goto L_001ba3b0;
                        }
                    L_001b9dfc:
                        charge(ctx, 6);
                        a0 = 5136;
                        jal(ctx, 0x1B9E00u, gen::fn_datGetFlag_0016f190);
                        v1 = 1;
                        if (v0 != v1) {
                            // 0x001b9e14
                            charge(ctx, 3);
                            lw(v0, s0, f4::root::kHold);
                            if (v0 != v1) {
                                // 0x001b9e20
                                charge(ctx, 10);
                                jal(ctx, 0x1B9E20u, gen::fn_sub_1D2A10_001d2a10);
                                jal(ctx, 0x1B9E28u, gen::fn_sub_1A9850_001a9850);
                                jal(ctx, 0x1B9E30u, gen::fn_sub_1AA1B0_001aa1b0);
                                lhu(v1, s0, f4::root::kMajor);
                                v0 = 32;
                                if (v1 == v0) {
                                    // 0x001b9e48
                                    charge(ctx, 4);
                                    lhu(v1, s0, f4::root::kMinor);
                                    v0 = 2;
                                    if (v1 == v0) {
                                        // 0x001b9e58
                                        charge(ctx, 2);
                                        jal(ctx, 0x1B9E58u, gen::fn_nullsub_5_00188650);
                                    }
                                }
                                // 0x001b9e60
                                charge(ctx, 14);
                                lhu(a0, s0, f4::root::kMajor);
                                lhu(a1, s0, f4::root::kMinor);
                                jal(ctx, 0x1B9E68u, gen::fn_sub_1B9140_001b9140);
                                lw(a0, s0, f4::root::kNowLoading);
                                jal(ctx, 0x1B9E74u, gen::fn_sub_187EA0_00187ea0);
                                sw(zero, s0, f4::root::kNowLoading);
                                jal(ctx, 0x1B9E80u, gen::fn_sub_1085C0_001085c0);
                                lhu(v1, s0, f4::root::kMajor);
                                v0 = 32;
                                if (v1 == v0) {
                                    // 0x001b9e98
                                    charge(ctx, 4);
                                    lhu(v1, s0, f4::root::kMinor);
                                    v0 = 2;
                                    if (v1 == v0) {
                                        // 0x001b9ea8
                                        charge(ctx, 3);
                                        a0 = 40;
                                        jal(ctx, 0x1B9EACu, gen::fn_sub_1086A0_001086a0);
                                    }
                                }
                                // 0x001b9eb4
                                charge(ctx, 5);
                                lw(v0, s0, f4::root::kState);
                                v0 = addiu(v0, 1);
                                sw(v0, s0, f4::root::kState);
                            }
                        }
                    }
                }
            }
            goto L_001ba3b0;
        case 0x1B9B94u:  // table[9]  -- state 9: walls, enemy scheduler, treasure, footsteps, panels, mini-map; then 10
            goto L_001b9b94;
        case 0x1B9CF8u:  // table[10]  -- state 10: all ready -> shadows, BGM, ambience, sub_1B9140, fade in -> 11
            goto L_001b9cf8;
        case 0x1B9EC8u:  // table[11]  -- state 11: fade done -> phase 2 (running), script procedure -> 12
            // 0x001b9ec8
            charge(ctx, 4);
            jal(ctx, 0x1B9EC8u, gen::fn_sub_108710_00108710);
            if (v0 != 0) {
                // 0x001b9ed8
                charge(ctx, 6);
                v0 = 2;
                sw(v0, gp, f4::gpv::kPhase);  // 0x7CE24C
                v0 = 0x870000;
                lw(a1, v0, -20568);  // 0x86AFA8
                if (a1 != 0) {
                    // 0x001b9ef0
                    charge(ctx, 4);
                    lhu(v1, s0, f4::root::kMajor);
                    v0 = slti(v1, 20);
                    if (v0 == 0) {
                        // 0x001b9f00
                        charge(ctx, 3);
                        at = slti(v1, 29);
                        if (at == 0) {
                            goto L_001b9f1c;
                        }
                        // 0x001b9f0c
                        charge(ctx, 4);
                        lhu(a0, s0, f4::root::kMinor);
                        at = slti(a0, 50);
                        if (at != 0) {
                            goto L_001b9f1c;
                        }
                    L_001b9f44:
                        charge(ctx, 9);
                        v0 = 0x870000;
                        lw(a2, v0, -20564);  // 0x86AFAC
                        a3 = addiu(a0, -50);
                        a0 = 10;
                        jal(ctx, 0x1B9F54u, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                        sw(v0, s0, f4::root::kScriptTask);
                        goto L_001ba048;
                    }
                L_001b9f1c:
                    charge(ctx, 3);
                    v0 = slti(v1, 40);
                    if (v0 == 0) {
                        // 0x001b9f28
                        charge(ctx, 3);
                        at = slti(v1, 49);
                        if (at == 0) {
                            goto L_001b9f68;
                        }
                        // 0x001b9f34
                        charge(ctx, 4);
                        lhu(a0, s0, f4::root::kMinor);
                        v0 = slti(a0, 50);
                        if (v0 != 0) {
                            goto L_001b9f68;
                        }
                        goto L_001b9f44;
                    }
                L_001b9f68:
                    charge(ctx, 3);
                    v0 = slti(v1, 20);
                    if (v0 == 0) {
                        // 0x001b9f74
                        charge(ctx, 3);
                        at = slti(v1, 29);
                        if (at == 0) {
                            goto L_001b9fb0;
                        }
                        // 0x001b9f80
                        charge(ctx, 3);
                        lhu(v0, s0, f4::root::kMinor);
                        if (v0 != 0) {
                            goto L_001b9fb0;
                        }
                        // 0x001b9f8c
                        charge(ctx, 9);
                        lw(v0, s0, f4::root::kBlockScript);
                        a0 = 10;
                        lw(a1, v0, 272);
                        a2 = 0;
                        jal(ctx, 0x1B9F9Cu, gen::fn_scrCreateTaskFromHeader_0035bb40);
                        sw(v0, s0, f4::root::kScriptTask);
                        goto L_001ba048;
                    }
                L_001b9fb0:
                    charge(ctx, 3);
                    v0 = slti(v1, 40);
                    if (v0 == 0) {
                        // 0x001b9fbc
                        charge(ctx, 3);
                        at = slti(v1, 49);
                        if (at == 0) {
                            goto L_001b9ff8;
                        }
                        // 0x001b9fc8
                        charge(ctx, 3);
                        lhu(v0, s0, f4::root::kMinor);
                        if (v0 != 0) {
                            goto L_001b9ff8;
                        }
                        // 0x001b9fd4
                        charge(ctx, 9);
                        lw(v0, s0, f4::root::kBlockScript);
                        a0 = 10;
                        lw(a1, v0, 272);
                        a2 = 0;
                        jal(ctx, 0x1B9FE4u, gen::fn_scrCreateTaskFromHeader_0035bb40);
                        sw(v0, s0, f4::root::kScriptTask);
                        goto L_001ba048;
                    }
                L_001b9ff8:
                    charge(ctx, 3);
                    v0 = slti(v1, 20);
                    if (v0 == 0) {
                        // 0x001ba004
                        charge(ctx, 3);
                        at = slti(v1, 29);
                        if (at == 0) {
                            // 0x001ba010
                            charge(ctx, 3);
                            v0 = slti(v1, 40);
                            if (v0 != 0) {
                                goto L_001ba028;
                            }
                            goto L_001ba01c;
                        }
                    L_001ba01c:
                        charge(ctx, 3);
                        at = slti(v1, 49);
                        if (at == 0) {
                            goto L_001ba028;
                        }
                        goto L_001ba048;
                    }
                L_001ba028:
                    charge(ctx, 8);
                    v0 = 0x870000;
                    lw(a2, v0, -20564);  // 0x86AFAC
                    lhu(v0, s0, f4::root::kMinor);
                    a3 = addiu(v0, -1);
                    a0 = 10;
                    jal(ctx, 0x1BA03Cu, gen::fn_scrCreateTaskFromScriptMemory_0035bc00);
                    sw(v0, s0, f4::root::kScriptTask);
                }
            L_001ba048:
                charge(ctx, 5);
                lw(v0, s0, f4::root::kState);
                v0 = addiu(v0, 1);
                sw(v0, s0, f4::root::kState);
            }
            goto L_001ba3b0;
        case 0x1BA05Cu:  // table[12]  -- state 12: the script done -> virtual pad (sField +12), field event task (sField +8) -> 13
            // 0x001ba05c
            charge(ctx, 3);
            lw(a0, s0, f4::root::kScriptTask);
            if (a0 != 0) {
                // 0x001ba068
                charge(ctx, 5);
                jal(ctx, 0x1BA068u, gen::fn_kwlnTaskExists_00195460);
                v1 = 1;
                if (v0 != v1) {
                    // 0x001ba07c
                    charge(ctx, 3);
                    lw(a0, s0, f4::root::kBlockScript);
                    if (a0 != 0) {
                        // 0x001ba088
                        charge(ctx, 3);
                        jal(ctx, 0x1BA088u, gen::fn_H_Cdvd_Destroy_00100ec0);
                        sw(zero, s0, f4::root::kBlockScript);
                    }
                    goto L_001ba094;
                }
                goto L_001ba3b0;
            }
        L_001ba094:
            charge(ctx, 36);
            v0 = 0x870000;
            lw(v0, v0, 6132);  // 0x8717F4
            a0 = s1;
            lw(a1, v0, 480);
            v0 = 0x870000;
            lw(a2, v0, 6128);  // 0x8717F0
            jal(ctx, 0x1BA0ACu, gen::fn_sub_1E1230_001e1230);
            v1 = 0x870000;
            sw(v0, v1, -24724);  // 0x869F6C
            a0 = s1;
            jal(ctx, 0x1BA0C0u, gen::fn_K_FldEvent_CreateTasks_001cd5a0);
            v1 = 0x870000;
            sw(v0, v1, -24728);  // 0x869F68
            v0 = 0x870000;
            lw(a0, v0, -24700);  // 0x869F84
            a1 = 0;
            jal(ctx, 0x1BA0DCu, gen::fn_sub_1D37F0_001d37f0);
            v0 = 0x870000;
            lw(a0, v0, -24704);  // 0x869F80
            a1 = 0;
            jal(ctx, 0x1BA0F0u, gen::fn_sub_1DA000_001da000);
            a0 = 0;
            jal(ctx, 0x1BA0FCu, gen::fn_sub_4532D0_004532d0);
            a0 = 0;
            a1 = 0;
            jal(ctx, 0x1BA10Cu, gen::fn_sub_4350E0_004350e0);
            v0 = 0x870000;
            lw(a0, v0, -24712);  // 0x869F78
            if (a0 != 0) {
                // 0x001ba124
                charge(ctx, 4);
                v0 = 0x870000;
                lw(v0, v0, -24716);  // 0x869F74
                if (v0 == 0) {
                    // 0x001ba134
                    charge(ctx, 3);
                    a1 = 1;
                    jal(ctx, 0x1BA138u, gen::fn_sub_429E80_00429e80);
                }
            }
            // 0x001ba140
            charge(ctx, 4);
            v0 = 0x870000;
            lw(a0, v0, -24696);  // 0x869F88
            if (a0 != 0) {
                // 0x001ba150
                charge(ctx, 3);
                a1 = 1;
                jal(ctx, 0x1BA154u, gen::fn_sub_18C0C0_0018c0c0);
            }
            // 0x001ba15c
            charge(ctx, 4);
            v0 = 0x870000;
            lw(a0, v0, -24692);  // 0x869F8C
            if (a0 != 0) {
                // 0x001ba16c
                charge(ctx, 3);
                a1 = 1;
                jal(ctx, 0x1BA170u, gen::fn_sub_18EB30_0018eb30);
            }
            // 0x001ba178
            charge(ctx, 11);
            a0 = 0;
            jal(ctx, 0x1BA17Cu, gen::fn_sub_45A430_0045a430);
            a0 = 0;
            jal(ctx, 0x1BA188u, gen::fn_sub_45AF70_0045af70);
            lw(v0, s0, f4::root::kState);
            v0 = addiu(v0, 1);
            sw(v0, s0, f4::root::kState);
            goto L_001ba3b0;
        case 0x1BA1A4u:  // table[13]  -- state 13: running; the shutdown word +8 -> 18
            // 0x001ba1a4
            charge(ctx, 3);
            lw(v0, s0, f4::root::kShutdown);
            if (v0 != 0) {
                // 0x001ba1b0
                charge(ctx, 4);
                v0 = 18;
                sw(v0, s0, f4::root::kState);
            }
            goto L_001ba3b0;
        case 0x1BA1C0u:  // table[14]  -- state 14: the event viewer ran: PCs and camera again -> 15 (or 18 when the field ends)
            // 0x001ba1c0
            charge(ctx, 6);
            lw(a0, s0, f4::root::kEventViewer);
            jal(ctx, 0x1BA1C4u, gen::fn_kwlnTaskExists_00195460);
            v1 = 1;
            if (v0 != v1) {
                // 0x001ba1d8
                charge(ctx, 4);
                jal(ctx, 0x1BA1D8u, gen::fn_sub_36F480_0036f480);
                if (v0 != 0) {
                    // 0x001ba1f8
                    charge(ctx, 20);
                    jal(ctx, 0x1BA1F8u, gen::fn_sub_1A9850_001a9850);
                    jal(ctx, 0x1BA200u, gen::fn_sub_1AA1B0_001aa1b0);
                    jal(ctx, 0x1BA208u, gen::fn_sub_17F8D0_0017f8d0);
                    jal(ctx, 0x1BA210u, gen::fn_sub_35BFB0_0035bfb0);
                    jal(ctx, 0x1BA218u, gen::fn_sub_36F4C0_0036f4c0);
                    sh(v0, s0, f4::root::kEntry);
                    lhu(a0, s0, f4::root::kEntry);
                    jal(ctx, 0x1BA228u, gen::fn_sub_1D03F0_001d03f0);
                    jal(ctx, 0x1BA230u, gen::fn_sub_1D70A0_001d70a0);
                    lhu(v0, s0, f4::root::kMajor);
                    at = slti(v0, 200);
                    if (at != 0) {
                        // 0x001ba248
                        charge(ctx, 8);
                        a0 = s1;
                        jal(ctx, 0x1BA24Cu, gen::fn_sub_18E820_0018e820);
                        v1 = 0x870000;
                        sw(v0, v1, -24692);  // 0x869F8C
                        a0 = si(-1);
                        jal(ctx, 0x1BA260u, gen::fn_sub_1DDCA0_001ddca0);
                    }
                    // 0x001ba268
                    charge(ctx, 4);
                    v0 = 15;
                    sw(v0, s0, f4::root::kState);
                } else {
                    // 0x001ba1e8
                    charge(ctx, 4);
                    v0 = 18;
                    sw(v0, s0, f4::root::kState);
                }
            }
            goto L_001ba3b0;
        case 0x1BA278u:  // table[15]  -- state 15: PC models ready -> header script, phase 1 -> 16
            // 0x001ba278
            charge(ctx, 4);
            jal(ctx, 0x1BA278u, gen::fn_sub_1CE960_001ce960);
            if (v0 != 0) {
                // 0x001ba288
                charge(ctx, 20);
                jal(ctx, 0x1BA288u, gen::fn_sub_1D2A10_001d2a10);
                v0 = 0x870000;
                lw(v1, v0, 6132);  // 0x8717F4
                v0 = 0x870000;
                lw(a0, v0, -24732);  // 0x869F64
                lhu(a1, v1, 0);
                jal(ctx, 0x1BA2A4u, gen::fn_sub_1D5F30_001d5f30);
                a0 = s1;
                a1 = 1;
                a2 = si(-1);
                jal(ctx, 0x1BA2B8u, gen::fn_sub_1D6270_001d6270);
                v0 = 1;
                sw(v0, gp, f4::gpv::kPhase);  // 0x7CE24C
                v0 = 0x870000;
                lw(a1, v0, -20568);  // 0x86AFA8
                if (a1 != 0) {
                    // 0x001ba2d8
                    charge(ctx, 6);
                    lhu(v0, s0, f4::root::kMinor);
                    a2 = addiu(v0, -1);
                    a0 = 10;
                    jal(ctx, 0x1BA2E4u, gen::fn_scrCreateTaskFromHeader_0035bb40);
                    sw(v0, s0, f4::root::kScriptTask);
                }
                // 0x001ba2f0
                charge(ctx, 4);
                v0 = 16;
                sw(v0, s0, f4::root::kState);
            }
            goto L_001ba3b0;
        case 0x1BA300u:  // table[16]  -- state 16: the script done -> walls, sub_1B9140, fade in -> 11
            // 0x001ba300
            charge(ctx, 3);
            lw(a0, s0, f4::root::kScriptTask);
            if (a0 != 0) {
                // 0x001ba30c
                charge(ctx, 5);
                jal(ctx, 0x1BA30Cu, gen::fn_kwlnTaskExists_00195460);
                v1 = 1;
                if (v0 != v1) {
                    goto L_001ba320;
                }
                goto L_001ba3b0;
            }
        L_001ba320:
            charge(ctx, 18);
            v0 = 0x870000;
            lw(v0, v0, 6132);  // 0x8717F4
            a0 = s1;
            lw(a1, v0, 480);
            jal(ctx, 0x1BA330u, gen::fn_sub_1C1F30_001c1f30);
            v1 = 0x870000;
            sw(v0, v1, -24708);  // 0x869F7C
            lhu(a0, s0, f4::root::kMajor);
            lhu(a1, s0, f4::root::kMinor);
            jal(ctx, 0x1BA348u, gen::fn_sub_1B9140_001b9140);
            jal(ctx, 0x1BA350u, gen::fn_sub_1085C0_001085c0);
            v0 = 11;
            sw(v0, s0, f4::root::kState);
            goto L_001ba3b0;
        case 0x1BA368u:  // table[17]  -- state 17: exit fade done -> adminiChangeSeq(2, +76, 28, 0) -> 18
            // 0x001ba368
            charge(ctx, 4);
            jal(ctx, 0x1BA368u, gen::fn_sub_108710_00108710);
            if (v0 != 0) {
                // 0x001ba378
                charge(ctx, 11);
                a0 = 2;
                a1 = addiu(s0, 76);
                a2 = 28;
                a3 = 0;
                jal(ctx, 0x1BA388u, gen::fn_adminiChangeSeq_0027c080);
                lw(v0, s0, f4::root::kState);
                v0 = addiu(v0, 1);
                sw(v0, s0, f4::root::kState);
            }
            goto L_001ba3b0;
        case 0x1BA3A4u:  // table[18]  -- state 18: -> -1 (destroyed)
            // 0x001ba3a4
            charge(ctx, 3);
            v0 = si(-1);
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x001ba3b4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
        return;
    }
    goto L_001ba3b0;
}

// 0x001BA3D0 K_Field_DestroyFieldRootTask -- 544 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// K_Field_DestroyFieldRootTask(task): the field root's destroy (26_field.md 2.3): "NOW LOADING", pauses off, sounds,
// the party / enemy field units (sub_1D0330 / sub_1D0390), the PM reader, the exit table (sub_1E7410), the .pac;
// prints "next seq--------------------->%d" and unloads the scene unless the next sequence is 2, 3 or 5 (also for
// field 4/10 or a pending dungeon reload 0x7CE26C); the battle-effect EPLs off the dungeon; resets the main camera
// frame; sField.root = 0; frees the work.
void K_Field_DestroyFieldRootTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001ba3d0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(s0, a0, f4::kTaskWork);
    lw(a0, s0, f4::root::kNowLoading);
    if (a0 != 0) {
        // 0x001ba3f4
        charge(ctx, 2);
        jal(ctx, 0x1BA3F4u, gen::fn_sub_187EA0_00187ea0);
    }
    // 0x001ba3fc
    charge(ctx, 20);
    a0 = 1;
    jal(ctx, 0x1BA400u, gen::fn_sub_45A430_0045a430);
    a0 = 1;
    jal(ctx, 0x1BA40Cu, gen::fn_sub_45AF70_0045af70);
    jal(ctx, 0x1BA414u, gen::fn_sub_3C8F70_003c8f70);
    jal(ctx, 0x1BA41Cu, gen::fn_sub_3C8F40_003c8f40);
    jal(ctx, 0x1BA424u, gen::fn_sub_109170_00109170);
    a0 = 4;
    a1 = 0;
    jal(ctx, 0x1BA434u, gen::fn_sub_109E30_00109e30);
    lhu(v1, s0, f4::root::kMajor);
    v0 = 4;
    if (v1 == v0) {
        // 0x001ba44c
        charge(ctx, 4);
        lhu(v1, s0, f4::root::kMinor);
        v0 = 10;
        if (v1 != v0) {
            goto L_001ba45c;
        }
    L_001ba468:
        charge(ctx, 2);
        jal(ctx, 0x1BA468u, gen::fn_sub_1CD8E0_001cd8e0);
        goto L_001ba470;
    }
L_001ba45c:
    charge(ctx, 3);
    lw(v0, gp, f4::gpv::kDungeonReload);  // 0x7CE26C
    if (v0 != 0) {
        goto L_001ba468;
    }
L_001ba470:
    charge(ctx, 9);
    jal(ctx, 0x1BA470u, gen::fn_sub_1D0330_001d0330);
    jal(ctx, 0x1BA478u, gen::fn_sub_1D0390_001d0390);
    jal(ctx, 0x1BA480u, gen::fn_sub_458BB0_00458bb0);
    lw(a0, s0, f4::root::kPmReader);
    if (a0 != 0) {
        // 0x001ba494
        charge(ctx, 2);
        jal(ctx, 0x1BA494u, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
    }
    // 0x001ba49c
    charge(ctx, 16);
    jal(ctx, 0x1BA49Cu, gen::fn_sub_1E7410_001e7410);
    jal(ctx, 0x1BA4A4u, gen::fn_sub_1B0920_001b0920);
    jal(ctx, 0x1BA4ACu, gen::fn_sub_27C330_0027c330);
    a0 = 0x680000;
    a0 = addiu(a0, -2672);  // "next seq--------------------->%d\n"
    a1 = v0;
    jal(ctx, 0x1BA4C0u, gen::fn_printf_005225a8);
    jal(ctx, 0x1BA4C8u, gen::fn_sub_27C330_0027c330);
    v1 = 2;
    if (v0 != v1) {
        // 0x001ba4dc
        charge(ctx, 5);
        jal(ctx, 0x1BA4DCu, gen::fn_sub_27C330_0027c330);
        v1 = 3;
        if (v0 != v1) {
            // 0x001ba4f0
            charge(ctx, 5);
            jal(ctx, 0x1BA4F0u, gen::fn_sub_27C330_0027c330);
            v1 = 5;
            if (v0 != v1) {
                // 0x001ba504
                charge(ctx, 2);
                jal(ctx, 0x1BA504u, gen::fn_sub_3B5AB0_003b5ab0);
            }
        }
    }
    // 0x001ba50c
    charge(ctx, 4);
    lhu(v1, s0, f4::root::kMajor);
    v0 = 4;
    if (v1 == v0) {
        // 0x001ba51c
        charge(ctx, 4);
        lhu(v1, s0, f4::root::kMinor);
        v0 = 10;
        if (v1 != v0) {
            goto L_001ba52c;
        }
    L_001ba538:
        charge(ctx, 3);
        jal(ctx, 0x1BA538u, gen::fn_sub_3B5AB0_003b5ab0);
        sw(zero, gp, f4::gpv::kDungeonReload);  // 0x7CE26C
        goto L_001ba544;
    }
L_001ba52c:
    charge(ctx, 3);
    lw(v0, gp, f4::gpv::kDungeonReload);  // 0x7CE26C
    if (v0 != 0) {
        goto L_001ba538;
    }
L_001ba544:
    charge(ctx, 4);
    lhu(v1, s0, f4::root::kMajor);
    v0 = slti(v1, 30);
    if (v0 == 0) {
        // 0x001ba554
        charge(ctx, 3);
        at = slti(v1, 40);
        if (at != 0) {
            // 0x001ba560
            charge(ctx, 4);
            jal(ctx, 0x1BA560u, gen::fn_K_FldDungeon_GetCurrentFloor_001bff20);
            if (v0 == 0) {
                // 0x001ba570
                charge(ctx, 2);
                jal(ctx, 0x1BA570u, gen::fn_sub_1C07F0_001c07f0);
            }
        }
    }
    // 0x001ba578
    charge(ctx, 30);
    a0 = 0;
    jal(ctx, 0x1BA57Cu, gen::fn_sub_350080_00350080);
    a0 = 2;
    jal(ctx, 0x1BA588u, gen::fn_sub_350080_00350080);
    a0 = 3;
    jal(ctx, 0x1BA594u, gen::fn_sub_350080_00350080);
    a0 = 5;
    jal(ctx, 0x1BA5A0u, gen::fn_sub_350080_00350080);
    jal(ctx, 0x1BA5A8u, gen::fn_sub_198590_00198590);
    lw(a0, v0, 4);
    jal(ctx, 0x1BA5B4u, gen::fn_sub_4CB930_004cb930);
    v0 = 0x870000;
    sw(zero, v0, -24736);  // sField
    lw(a0, s1, 60);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    jalr(ctx, 0x1BA5D0u, v0.u());
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001BA5F0 k_Field_CreateFieldRootTask -- 648 bytes; frame 0xC0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// k_Field_CreateFieldRootTask(parent, major, minor, entry, sub1, sub2, flags, minCells, maxCells, s10, pmEvent) ->
// the "field root" task (104-byte work, priority 10) or 0: memset(sField, 0, 4424) (the grid and the task table;
// the tail +4424.. is kept), sField.root = the task. Without an event (pmEvent <= 0): sub_17F8D0, scrAllReleaseScript,
// the ids to the work, sField +56 flags, +66 / +67 the floor's cell-count bounds, +68 s10; .pac requested; the
// battle-effect pack for majors 30..39 outside the dungeon; state 1. With an event: the PM reader (+56), event id
// (+12), state 0. Then the main camera frame reset to (0x67F5B8, 0x67F5C0), sub_1D8CB0, the EPL delay task -> +16.
void k_Field_CreateFieldRootTask(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x001ba5f0
    enter(ctx, 35);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
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
    s1 = a0;
    s5 = a1;
    s4 = a2;
    s3 = a3;
    s2 = t0;
    s6 = t1;
    s7 = t2;
    fp = t3;
    a0 = 0x870000;
    a0 = addiu(a0, -24736);  // &sField
    a1 = 0;
    a2 = 4424;
    jal(ctx, 0x1BA64Cu, gen::fn_memset_00521408);
    a0 = 1;
    a1 = 104;
    a2 = 0x40000;
    v0 = 0x960000;
    lw(v0, v0, 388);  // 0x960184
    jalr(ctx, 0x1BA668u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x001ba688
        charge(ctx, 17);
        a0 = s1;
        a1 = 10;
        a2 = 0x680000;
        a2 = addiu(a2, -2616);  // "field root"
        a3 = 0x1C0000;
        a3 = addiu(a3, -27520);  // &K_Field_UpdateFieldRootTask
        t0 = 0x1C0000;
        t0 = addiu(t0, -23600);  // &K_Field_DestroyFieldRootTask
        t1 = s0;
        jal(ctx, 0x1BA6ACu, gen::fn_kwlnTaskCreateWithAutoPriority_00194b80);
        s1 = v0;
        v0 = 0x870000;
        sw(s1, v0, -24736);  // sField
        lw(a0, sp, 0xD0);
        if (i64(a0) <= 0) {
            // 0x001ba6f8
            charge(ctx, 29);
            jal(ctx, 0x1BA6F8u, gen::fn_sub_17F8D0_0017f8d0);
            jal(ctx, 0x1BA700u, gen::fn_sub_35BFB0_0035bfb0);
            sh(s5, s0, 16);
            sh(s4, s0, 18);
            sh(s2, s0, 24);
            sh(s6, s0, 26);
            sh(s3, s0, 20);
            v0 = 0x870000;
            sw(s7, v0, -24680);  // 0x869F98
            v0 = 0x870000;
            sb(fp, v0, -24670);  // 0x869FA2
            lbu(v1, sp, 0xC0);
            v0 = 0x870000;
            sb(v1, v0, -24669);  // 0x869FA3
            lh(v1, sp, 0xC8);
            v0 = 0x870000;
            sh(v1, v0, -24668);  // 0x869FA4
            a0 = dsll32(s5, 16);
            a0 = dsra32(a0, 16);
            a1 = dsll32(s4, 16);
            a1 = dsra32(a1, 16);
            jal(ctx, 0x1BA754u, gen::fn_sub_1B0870_001b0870);
            v1 = s5 & 0xFFFF;
            v0 = slti(v1, 30);
            if (v0 == 0) {
                // 0x001ba76c
                charge(ctx, 3);
                at = slti(v1, 40);
                if (at != 0) {
                    // 0x001ba778
                    charge(ctx, 4);
                    jal(ctx, 0x1BA778u, gen::fn_K_FldDungeon_GetCurrentFloor_001bff20);
                    if (v0 == 0) {
                        // 0x001ba788
                        charge(ctx, 2);
                        jal(ctx, 0x1BA788u, gen::fn_sub_1C03F0_001c03f0);
                    }
                }
            }
            // 0x001ba790
            charge(ctx, 2);
            v0 = 1;
            sw(v0, s0, 0);
        } else {
            // 0x001ba6cc
            charge(ctx, 11);
            lw(a1, sp, 0xD8);
            lw(a2, sp, 0xE0);
            lw(a3, sp, 0xE8);
            jal(ctx, 0x1BA6D8u, gen::fn_sub_397EC0_00397ec0);
            sw(v0, s0, 56);
            sw(zero, s0, 0);
            lw(v0, sp, 0xD0);
            sw(v0, s0, 12);
        }
        // 0x001ba798
        charge(ctx, 43);
        v0 = 0x680000;
        ld(v1, v0, -2632);  // 0x67F5B8
        v0 = 0x680000;
        lwc1(f0, v0, -2624);  // 0x67F5C0
        sd(v1, sp, 0xB0);
        swc1(f0, sp, 0xB8);
        jal(ctx, 0x1BA7B0u, gen::fn_sub_198590_00198590);
        lw(a0, v0, 4);
        jal(ctx, 0x1BA7BCu, gen::fn_sub_4CB930_004cb930);
        jal(ctx, 0x1BA7C4u, gen::fn_sub_198590_00198590);
        lw(v0, v0, 4);
        lwc1(f2, sp, 0xB0);
        lwc1(f1, sp, 0xB4);
        lwc1(f0, sp, 0xB8);
        swc1(f2, v0, 64);
        swc1(f1, v0, 68);
        swc1(f0, v0, 72);
        a0 = addiu(sp, 0xA0);
        jal(ctx, 0x1BA7ECu, gen::fn_sub_4C2CC0_004c2cc0);
        jal(ctx, 0x1BA7F4u, gen::fn_sub_198590_00198590);
        lw(v0, v0, 4);
        a0 = addiu(v0, 16);
        a1 = addiu(sp, 0xA0);
        jal(ctx, 0x1BA808u, gen::fn_sub_4C2D20_004c2d20);
        jal(ctx, 0x1BA810u, gen::fn_sub_198590_00198590);
        lw(a0, v0, 4);
        jal(ctx, 0x1BA81Cu, gen::fn_sub_4CB270_004cb270);
        jal(ctx, 0x1BA824u, gen::fn_sub_1D8CB0_001d8cb0);
        a0 = s1;
        jal(ctx, 0x1BA830u, gen::fn_sub_1A96C0_001a96c0);
        v1 = 0x870000;
        sw(v0, v1, -24720);  // 0x869F70
        v0 = s1;
    } else {
        // 0x001ba67c
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001ba844 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xC0);
}

// 0x001BA880 K_Field_SetShouldShutdown -- 68 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// K_Field_SetShouldShutdown(task, v): prints "shutdown field proc" and sets the root work's shutdown word +8 (state 13
// then moves to 18).
void K_Field_SetShouldShutdown(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001ba880
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(s0, a0, f4::kTaskWork);
    a0 = 0x680000;
    a0 = addiu(a0, -2592);  // "shutdown field proc\n"
    jal(ctx, 0x1BA8A0u, gen::fn_printf_005225a8);
    sw(s1, s0, f4::root::kShutdown);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001BA8D0 sub_1BA8D0 [K_Field_RequestQuit] -- 376 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1BA8D0() (from the reset / quit path sub_14F7D0): clears flag 2 of every object (type 3) and type-11 scene
// resource and their tasks' flags, resets the fog / clear colours, then asks the dungeon task (K_FldDungeon_
// RequestShutdown) or the field root (work +8 = 1, "shutdown field proc") to end; sounds and the pad off.
void sub_1BA8D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001ba8d0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 3;
    jal(ctx, 0x1BA8E4u, gen::fn_sub_3B5D50_003b5d50);
    s1 = v0;
    a0 = 11;
    jal(ctx, 0x1BA8F4u, gen::fn_sub_3B5D50_003b5d50);
    s0 = v0;
    jal(ctx, 0x1BA900u, gen::fn_sub_45A400_0045a400);
    a0 = 0;
    a1 = 1;
    jal(ctx, 0x1BA910u, gen::fn_sub_1A0040_001a0040);
    for (;;) {
        // 0x001ba950
        charge(ctx, 2);
        if (s1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001ba920
        charge(ctx, 7);
        lw(v1, s1, 40);
        v0 = si(-3);
        v0 = v1 & v0;
        sw(v0, s1, 40);
        lw(a0, s1, 528);
        if (a0 != 0) {
            // 0x001ba93c
            charge(ctx, 4);
            a1 = 32;
            a2 = 0;
            jal(ctx, 0x1BA944u, gen::fn_kwlnTaskSetFlags_001956d0);
        }
        // 0x001ba94c
        charge(ctx, 1);
        lw(s1, s1, 248);
    }
    // 0x001ba958
    charge(ctx, 3);
    v1 = si(-3);
    for (;;) {
        // 0x001ba974
        charge(ctx, 3);
        if (s0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001ba964
        charge(ctx, 4);
        lw(v0, s0, 40);
        v0 = v0 & v1;
        sw(v0, s0, 40);
        lw(s0, s0, 248);
    }
    // 0x001ba980
    charge(ctx, 18);
    a0 = 0;
    jal(ctx, 0x1BA984u, gen::fn_sub_19FEC0_0019fec0);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x1BA99Cu, gen::fn_sub_1985B0_001985b0);
    a0 = 0;
    a1 = 0;
    a2 = 0;
    a3 = 0;
    jal(ctx, 0x1BA9B4u, gen::fn_sub_1985E0_001985e0);
    lw(v0, gp, f4::gpv::kDungeonTask);  // 0x7CE268
    if (v0 == 0) {
        // 0x001ba9d8
        charge(ctx, 9);
        v0 = 0x870000;
        lw(v0, v0, -24736);  // sField
        lw(s0, v0, 60);
        a0 = 0x680000;
        a0 = addiu(a0, -2592);  // "shutdown field proc\n"
        jal(ctx, 0x1BA9ECu, gen::fn_printf_005225a8);
        v0 = 1;
        sw(v0, s0, 8);
    } else {
        // 0x001ba9c8
        charge(ctx, 4);
        jal(ctx, 0x1BA9C8u, gen::fn_K_FldDungeon_RequestShutdown_001bff00);
    }
    // 0x001ba9fc
    charge(ctx, 19);
    jal(ctx, 0x1BA9FCu, gen::fn_sub_1CD8E0_001cd8e0);
    a0 = 10;
    jal(ctx, 0x1BAA08u, gen::fn_sub_108FD0_00108fd0);
    a0 = 3;
    a1 = 0;
    jal(ctx, 0x1BAA18u, gen::fn_sub_109F60_00109f60);
    a0 = 4;
    a1 = 0;
    jal(ctx, 0x1BAA28u, gen::fn_sub_109F60_00109f60);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001BAA50 sub_1BAA50 [K_Field_SetShutdownHold] -- 68 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1BAA50(task, v): prints "shutdown field proc" and sets the root work's +4 (the hold word state 7 / 10 test:
// the dungeon task sets it while the stratum title runs).
void sub_1BAA50(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001baa50
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(s0, a0, f4::kTaskWork);
    a0 = 0x680000;
    a0 = addiu(a0, -2592);  // "shutdown field proc\n"
    jal(ctx, 0x1BAA70u, gen::fn_printf_005225a8);
    sw(s1, s0, f4::root::kHold);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001BAAA0 sub_1BAAA0 [K_Field_RequestNextField] -- 128 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_1BAAA0(task, major, minor, entry): the exit to another field: sub_1D0270, root work +76/+78/+80 = the next ids
// (+82 / +84 = 0), fade out (sub_108570, sub_108670(2)), state 17 -> sequence 2 with that packet.
void sub_1BAAA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001baaa0
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s3 = a1;
    s2 = a2;
    s1 = a3;
    lw(s0, a0, f4::kTaskWork);
    jal(ctx, 0x1BAAC8u, gen::fn_sub_1D0270_001d0270);
    sh(s3, s0, f4::root::kNextMajor);
    sh(s2, s0, f4::root::kNextMinor);
    sh(s1, s0, f4::root::kNextEntry);
    sh(zero, s0, f4::root::kNextSub1);
    sh(zero, s0, f4::root::kNextSub2);
    jal(ctx, 0x1BAAE4u, gen::fn_sub_108570_00108570);
    a0 = 2;
    jal(ctx, 0x1BAAF0u, gen::fn_sub_108670_00108670);
    v1 = 17;
    sw(v1, s0, f4::root::kState);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

}  // namespace p3fes::game
