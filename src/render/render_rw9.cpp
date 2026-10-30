// Slice render_rw9: RenderWare, ninth pass -- the clump / atomic / geometry core and their stream readers, the material
// list, the world's create / destroy, RpMatFX's material effects, PTank's geometry set-up, Rt2d's paths / shapes / scenes
// / maestro, the RtFS helpers, the memory module, the RW strings and vector transforms, the image module and the texture
// readers, and the sky driver's raster / texture formats, native stream readers, SkySystem, palette upload and texture
// cache (the group overview and the record layouts are in game/include/p3fes/game/render_rw9.h). Every body started as
// p3fes_handgen's output and keeps the recompiled body's registers, frame, spills, $ra links, cycle charges and check
// points statement for statement (game/include/p3fes/game/hg_cpu.h); what was added is the role of each function and
// the names of the record offsets (rw9::) where one base register holds one record throughout. sub_* keep their
// symbols/functions.json names; proposed names are in brackets (symbols/deltas/render_rw9.sym).
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/render_rw9.h"

namespace p3fes::recomp_gen {
void fn_DIntr_0050d3a0(p3fes::EEContext&);
void fn_EIntr_0050d3f0(p3fes::EEContext&);
void fn_RpSkySelectDeepZBuffer_004d82a0(p3fes::EEContext&);
void fn_RwFsInit_004bfbb0(p3fes::EEContext&);
void fn_SkyCreateDBRaster_004e3320(p3fes::EEContext&);
void fn_SkyCreateFBRaster_004e3100(p3fes::EEContext&);
void fn_SkyOpen_004e01b0(p3fes::EEContext&);
void fn_SkyStart_004e1060(p3fes::EEContext&);
void fn_SkySystem_004e2b70(p3fes::EEContext&);
void fn_SkyUseMode_004dff20(p3fes::EEContext&);
void fn_SyncDCache_00503a58(p3fes::EEContext&);
void fn___udivdi3_0052fe98(p3fes::EEContext&);
void fn___umoddi3_00530578(p3fes::EEContext&);
void fn__rwDMAAddPURef_004d51c0(p3fes::EEContext&);
void fn__rwDMADmaClose_004d6a50(p3fes::EEContext&);
void fn__rwDMAForceBufferSwap_004d4df0(p3fes::EEContext&);
void fn__rwDMAOpenGIFPkt_004d54e0(p3fes::EEContext&);
void fn__rwSkyOverloadPipelines_004eebc0(p3fes::EEContext&);
void fn__sceCreateSema_00503160(p3fes::EEContext&);
void fn__sceSignalSema_00503180(p3fes::EEContext&);
void fn__sceWaitSema_005031a0(p3fes::EEContext&);
void fn_calloc_0051e150(p3fes::EEContext&);
void fn_geometryLock_00493370(p3fes::EEContext&);
void fn_j_calloc_004c4440(p3fes::EEContext&);
void fn_j_malloc_004c4420(p3fes::EEContext&);
void fn_j_realloc_004c4430(p3fes::EEContext&);
void fn_malloc_00520728(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_powf_0052ea48(p3fes::EEContext&);
void fn_realloc_00522f98(p3fes::EEContext&);
void fn_rt2dPS2PipeOpen_004b1100(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_1_004c0060(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_2_004e2f00(p3fes::EEContext&);
void fn_skyFillInPktForUpLoadAlignedContiguousRectangle_004ef020(p3fes::EEContext&);
void fn_strncpy_00524828(p3fes::EEContext&);
void fn_sub_4676C0_004676c0(p3fes::EEContext&);
void fn_sub_467B40_00467b40(p3fes::EEContext&);
void fn_sub_467FD0_00467fd0(p3fes::EEContext&);
void fn_sub_468560_00468560(p3fes::EEContext&);
void fn_sub_468DC0_00468dc0(p3fes::EEContext&);
void fn_sub_468EA0_00468ea0(p3fes::EEContext&);
void fn_sub_469060_00469060(p3fes::EEContext&);
void fn_sub_4692E0_004692e0(p3fes::EEContext&);
void fn_sub_469400_00469400(p3fes::EEContext&);
void fn_sub_469510_00469510(p3fes::EEContext&);
void fn_sub_469590_00469590(p3fes::EEContext&);
void fn_sub_469770_00469770(p3fes::EEContext&);
void fn_sub_469840_00469840(p3fes::EEContext&);
void fn_sub_469A90_00469a90(p3fes::EEContext&);
void fn_sub_469AA0_00469aa0(p3fes::EEContext&);
void fn_sub_469BC0_00469bc0(p3fes::EEContext&);
void fn_sub_4734D0_004734d0(p3fes::EEContext&);
void fn_sub_473600_00473600(p3fes::EEContext&);
void fn_sub_473B10_00473b10(p3fes::EEContext&);
void fn_sub_474260_00474260(p3fes::EEContext&);
void fn_sub_474630_00474630(p3fes::EEContext&);
void fn_sub_474820_00474820(p3fes::EEContext&);
void fn_sub_474D30_00474d30(p3fes::EEContext&);
void fn_sub_474F20_00474f20(p3fes::EEContext&);
void fn_sub_475C20_00475c20(p3fes::EEContext&);
void fn_sub_475CB0_00475cb0(p3fes::EEContext&);
void fn_sub_475D60_00475d60(p3fes::EEContext&);
void fn_sub_478E80_00478e80(p3fes::EEContext&);
void fn_sub_47A210_0047a210(p3fes::EEContext&);
void fn_sub_47BF80_0047bf80(p3fes::EEContext&);
void fn_sub_486340_00486340(p3fes::EEContext&);
void fn_sub_48F580_0048f580(p3fes::EEContext&);
void fn_sub_48FBD0_0048fbd0(p3fes::EEContext&);
void fn_sub_490050_00490050(p3fes::EEContext&);
void fn_sub_4908D0_004908d0(p3fes::EEContext&);
void fn_sub_490980_00490980(p3fes::EEContext&);
void fn_sub_490D90_00490d90(p3fes::EEContext&);
void fn_sub_490DC0_00490dc0(p3fes::EEContext&);
void fn_sub_4916D0_004916d0(p3fes::EEContext&);
void fn_sub_491760_00491760(p3fes::EEContext&);
void fn_sub_4917F0_004917f0(p3fes::EEContext&);
void fn_sub_491880_00491880(p3fes::EEContext&);
void fn_sub_4919B0_004919b0(p3fes::EEContext&);
void fn_sub_491A80_00491a80(p3fes::EEContext&);
void fn_sub_491B40_00491b40(p3fes::EEContext&);
void fn_sub_491CC0_00491cc0(p3fes::EEContext&);
void fn_sub_491DE0_00491de0(p3fes::EEContext&);
void fn_sub_491EA0_00491ea0(p3fes::EEContext&);
void fn_sub_491FF0_00491ff0(p3fes::EEContext&);
void fn_sub_4920A0_004920a0(p3fes::EEContext&);
void fn_sub_492D10_00492d10(p3fes::EEContext&);
void fn_sub_492D50_00492d50(p3fes::EEContext&);
void fn_sub_492E20_00492e20(p3fes::EEContext&);
void fn_sub_492F80_00492f80(p3fes::EEContext&);
void fn_sub_493210_00493210(p3fes::EEContext&);
void fn_sub_493230_00493230(p3fes::EEContext&);
void fn_sub_4933D0_004933d0(p3fes::EEContext&);
void fn_sub_493710_00493710(p3fes::EEContext&);
void fn_sub_493B40_00493b40(p3fes::EEContext&);
void fn_sub_493B60_00493b60(p3fes::EEContext&);
void fn_sub_493CB0_00493cb0(p3fes::EEContext&);
void fn_sub_494580_00494580(p3fes::EEContext&);
void fn_sub_494BE0_00494be0(p3fes::EEContext&);
void fn_sub_494CC0_00494cc0(p3fes::EEContext&);
void fn_sub_494D50_00494d50(p3fes::EEContext&);
void fn_sub_494E30_00494e30(p3fes::EEContext&);
void fn_sub_495260_00495260(p3fes::EEContext&);
void fn_sub_495300_00495300(p3fes::EEContext&);
void fn_sub_495340_00495340(p3fes::EEContext&);
void fn_sub_4954C0_004954c0(p3fes::EEContext&);
void fn_sub_4959C0_004959c0(p3fes::EEContext&);
void fn_sub_495C80_00495c80(p3fes::EEContext&);
void fn_sub_496580_00496580(p3fes::EEContext&);
void fn_sub_498E40_00498e40(p3fes::EEContext&);
void fn_sub_499720_00499720(p3fes::EEContext&);
void fn_sub_499850_00499850(p3fes::EEContext&);
void fn_sub_499D30_00499d30(p3fes::EEContext&);
void fn_sub_499E90_00499e90(p3fes::EEContext&);
void fn_sub_499F40_00499f40(p3fes::EEContext&);
void fn_sub_499FD0_00499fd0(p3fes::EEContext&);
void fn_sub_49A080_0049a080(p3fes::EEContext&);
void fn_sub_49A290_0049a290(p3fes::EEContext&);
void fn_sub_49A400_0049a400(p3fes::EEContext&);
void fn_sub_49B3F0_0049b3f0(p3fes::EEContext&);
void fn_sub_49C230_0049c230(p3fes::EEContext&);
void fn_sub_49C240_0049c240(p3fes::EEContext&);
void fn_sub_49CC30_0049cc30(p3fes::EEContext&);
void fn_sub_49E4F0_0049e4f0(p3fes::EEContext&);
void fn_sub_4A4D60_004a4d60(p3fes::EEContext&);
void fn_sub_4A53B0_004a53b0(p3fes::EEContext&);
void fn_sub_4A5400_004a5400(p3fes::EEContext&);
void fn_sub_4A5470_004a5470(p3fes::EEContext&);
void fn_sub_4A5540_004a5540(p3fes::EEContext&);
void fn_sub_4A6530_004a6530(p3fes::EEContext&);
void fn_sub_4A6630_004a6630(p3fes::EEContext&);
void fn_sub_4A91F0_004a91f0(p3fes::EEContext&);
void fn_sub_4A9330_004a9330(p3fes::EEContext&);
void fn_sub_4AA410_004aa410(p3fes::EEContext&);
void fn_sub_4AA550_004aa550(p3fes::EEContext&);
void fn_sub_4AA5C0_004aa5c0(p3fes::EEContext&);
void fn_sub_4AA620_004aa620(p3fes::EEContext&);
void fn_sub_4AA6C0_004aa6c0(p3fes::EEContext&);
void fn_sub_4AAE60_004aae60(p3fes::EEContext&);
void fn_sub_4AB0E0_004ab0e0(p3fes::EEContext&);
void fn_sub_4AB200_004ab200(p3fes::EEContext&);
void fn_sub_4ABD50_004abd50(p3fes::EEContext&);
void fn_sub_4AC020_004ac020(p3fes::EEContext&);
void fn_sub_4AC390_004ac390(p3fes::EEContext&);
void fn_sub_4AC410_004ac410(p3fes::EEContext&);
void fn_sub_4AC570_004ac570(p3fes::EEContext&);
void fn_sub_4AC5F0_004ac5f0(p3fes::EEContext&);
void fn_sub_4AC710_004ac710(p3fes::EEContext&);
void fn_sub_4AC7F0_004ac7f0(p3fes::EEContext&);
void fn_sub_4AC870_004ac870(p3fes::EEContext&);
void fn_sub_4AC920_004ac920(p3fes::EEContext&);
void fn_sub_4ACB10_004acb10(p3fes::EEContext&);
void fn_sub_4ACB90_004acb90(p3fes::EEContext&);
void fn_sub_4ACE80_004ace80(p3fes::EEContext&);
void fn_sub_4AD6A0_004ad6a0(p3fes::EEContext&);
void fn_sub_4AD940_004ad940(p3fes::EEContext&);
void fn_sub_4ADB50_004adb50(p3fes::EEContext&);
void fn_sub_4ADB80_004adb80(p3fes::EEContext&);
void fn_sub_4ADBD0_004adbd0(p3fes::EEContext&);
void fn_sub_4ADC70_004adc70(p3fes::EEContext&);
void fn_sub_4ADC90_004adc90(p3fes::EEContext&);
void fn_sub_4ADCA0_004adca0(p3fes::EEContext&);
void fn_sub_4ADCC0_004adcc0(p3fes::EEContext&);
void fn_sub_4ADDB0_004addb0(p3fes::EEContext&);
void fn_sub_4ADE90_004ade90(p3fes::EEContext&);
void fn_sub_4ADFD0_004adfd0(p3fes::EEContext&);
void fn_sub_4AE010_004ae010(p3fes::EEContext&);
void fn_sub_4AE020_004ae020(p3fes::EEContext&);
void fn_sub_4AE110_004ae110(p3fes::EEContext&);
void fn_sub_4AE150_004ae150(p3fes::EEContext&);
void fn_sub_4AE1D0_004ae1d0(p3fes::EEContext&);
void fn_sub_4AE1E0_004ae1e0(p3fes::EEContext&);
void fn_sub_4AE270_004ae270(p3fes::EEContext&);
void fn_sub_4AE3B0_004ae3b0(p3fes::EEContext&);
void fn_sub_4AE4E0_004ae4e0(p3fes::EEContext&);
void fn_sub_4AE5A0_004ae5a0(p3fes::EEContext&);
void fn_sub_4AE690_004ae690(p3fes::EEContext&);
void fn_sub_4AE790_004ae790(p3fes::EEContext&);
void fn_sub_4AE900_004ae900(p3fes::EEContext&);
void fn_sub_4AEB60_004aeb60(p3fes::EEContext&);
void fn_sub_4AEBF0_004aebf0(p3fes::EEContext&);
void fn_sub_4AEEA0_004aeea0(p3fes::EEContext&);
void fn_sub_4AEF50_004aef50(p3fes::EEContext&);
void fn_sub_4AF130_004af130(p3fes::EEContext&);
void fn_sub_4AF210_004af210(p3fes::EEContext&);
void fn_sub_4AF340_004af340(p3fes::EEContext&);
void fn_sub_4AF760_004af760(p3fes::EEContext&);
void fn_sub_4AF940_004af940(p3fes::EEContext&);
void fn_sub_4AFFE0_004affe0(p3fes::EEContext&);
void fn_sub_4B0FA0_004b0fa0(p3fes::EEContext&);
void fn_sub_4B1050_004b1050(p3fes::EEContext&);
void fn_sub_4B1090_004b1090(p3fes::EEContext&);
void fn_sub_4B11A0_004b11a0(p3fes::EEContext&);
void fn_sub_4B1290_004b1290(p3fes::EEContext&);
void fn_sub_4B14C0_004b14c0(p3fes::EEContext&);
void fn_sub_4B1620_004b1620(p3fes::EEContext&);
void fn_sub_4B1870_004b1870(p3fes::EEContext&);
void fn_sub_4B1A70_004b1a70(p3fes::EEContext&);
void fn_sub_4B1A80_004b1a80(p3fes::EEContext&);
void fn_sub_4B1B90_004b1b90(p3fes::EEContext&);
void fn_sub_4B1BA0_004b1ba0(p3fes::EEContext&);
void fn_sub_4B22B0_004b22b0(p3fes::EEContext&);
void fn_sub_4B24C0_004b24c0(p3fes::EEContext&);
void fn_sub_4B26A0_004b26a0(p3fes::EEContext&);
void fn_sub_4B2810_004b2810(p3fes::EEContext&);
void fn_sub_4B2AD0_004b2ad0(p3fes::EEContext&);
void fn_sub_4B2BC0_004b2bc0(p3fes::EEContext&);
void fn_sub_4B2BD0_004b2bd0(p3fes::EEContext&);
void fn_sub_4B2C80_004b2c80(p3fes::EEContext&);
void fn_sub_4B2E20_004b2e20(p3fes::EEContext&);
void fn_sub_4B2E70_004b2e70(p3fes::EEContext&);
void fn_sub_4B2F10_004b2f10(p3fes::EEContext&);
void fn_sub_4B30A0_004b30a0(p3fes::EEContext&);
void fn_sub_4B3100_004b3100(p3fes::EEContext&);
void fn_sub_4B3160_004b3160(p3fes::EEContext&);
void fn_sub_4B3440_004b3440(p3fes::EEContext&);
void fn_sub_4B3490_004b3490(p3fes::EEContext&);
void fn_sub_4B34E0_004b34e0(p3fes::EEContext&);
void fn_sub_4B3730_004b3730(p3fes::EEContext&);
void fn_sub_4B3790_004b3790(p3fes::EEContext&);
void fn_sub_4B3900_004b3900(p3fes::EEContext&);
void fn_sub_4B39F0_004b39f0(p3fes::EEContext&);
void fn_sub_4B3AC0_004b3ac0(p3fes::EEContext&);
void fn_sub_4B3CC0_004b3cc0(p3fes::EEContext&);
void fn_sub_4B40F0_004b40f0(p3fes::EEContext&);
void fn_sub_4B41B0_004b41b0(p3fes::EEContext&);
void fn_sub_4B4230_004b4230(p3fes::EEContext&);
void fn_sub_4B42E0_004b42e0(p3fes::EEContext&);
void fn_sub_4B43C0_004b43c0(p3fes::EEContext&);
void fn_sub_4B4410_004b4410(p3fes::EEContext&);
void fn_sub_4B4790_004b4790(p3fes::EEContext&);
void fn_sub_4B47D0_004b47d0(p3fes::EEContext&);
void fn_sub_4B4810_004b4810(p3fes::EEContext&);
void fn_sub_4B4860_004b4860(p3fes::EEContext&);
void fn_sub_4B4CC0_004b4cc0(p3fes::EEContext&);
void fn_sub_4B4D70_004b4d70(p3fes::EEContext&);
void fn_sub_4B4EB0_004b4eb0(p3fes::EEContext&);
void fn_sub_4B5270_004b5270(p3fes::EEContext&);
void fn_sub_4B5380_004b5380(p3fes::EEContext&);
void fn_sub_4B5D80_004b5d80(p3fes::EEContext&);
void fn_sub_4B5EC0_004b5ec0(p3fes::EEContext&);
void fn_sub_4B6040_004b6040(p3fes::EEContext&);
void fn_sub_4B6270_004b6270(p3fes::EEContext&);
void fn_sub_4B7630_004b7630(p3fes::EEContext&);
void fn_sub_4B7690_004b7690(p3fes::EEContext&);
void fn_sub_4BFEA0_004bfea0(p3fes::EEContext&);
void fn_sub_4C00F0_004c00f0(p3fes::EEContext&);
void fn_sub_4C06C0_004c06c0(p3fes::EEContext&);
void fn_sub_4C1450_004c1450(p3fes::EEContext&);
void fn_sub_4C1600_004c1600(p3fes::EEContext&);
void fn_sub_4C18B0_004c18b0(p3fes::EEContext&);
void fn_sub_4C1910_004c1910(p3fes::EEContext&);
void fn_sub_4C1970_004c1970(p3fes::EEContext&);
void fn_sub_4C1C50_004c1c50(p3fes::EEContext&);
void fn_sub_4C1D10_004c1d10(p3fes::EEContext&);
void fn_sub_4C1D50_004c1d50(p3fes::EEContext&);
void fn_sub_4C1E70_004c1e70(p3fes::EEContext&);
void fn_sub_4C1F70_004c1f70(p3fes::EEContext&);
void fn_sub_4C2090_004c2090(p3fes::EEContext&);
void fn_sub_4C20B0_004c20b0(p3fes::EEContext&);
void fn_sub_4C2120_004c2120(p3fes::EEContext&);
void fn_sub_4C21B0_004c21b0(p3fes::EEContext&);
void fn_sub_4C21E0_004c21e0(p3fes::EEContext&);
void fn_sub_4C2A30_004c2a30(p3fes::EEContext&);
void fn_sub_4C3970_004c3970(p3fes::EEContext&);
void fn_sub_4C3B60_004c3b60(p3fes::EEContext&);
void fn_sub_4C3B70_004c3b70(p3fes::EEContext&);
void fn_sub_4C3C30_004c3c30(p3fes::EEContext&);
void fn_sub_4C4450_004c4450(p3fes::EEContext&);
void fn_sub_4C4570_004c4570(p3fes::EEContext&);
void fn_sub_4C47E0_004c47e0(p3fes::EEContext&);
void fn_sub_4C5250_004c5250(p3fes::EEContext&);
void fn_sub_4C5620_004c5620(p3fes::EEContext&);
void fn_sub_4C5A50_004c5a50(p3fes::EEContext&);
void fn_sub_4C5C30_004c5c30(p3fes::EEContext&);
void fn_sub_4C64B0_004c64b0(p3fes::EEContext&);
void fn_sub_4C6560_004c6560(p3fes::EEContext&);
void fn_sub_4C65D0_004c65d0(p3fes::EEContext&);
void fn_sub_4C6640_004c6640(p3fes::EEContext&);
void fn_sub_4C6700_004c6700(p3fes::EEContext&);
void fn_sub_4C67A0_004c67a0(p3fes::EEContext&);
void fn_sub_4C6840_004c6840(p3fes::EEContext&);
void fn_sub_4C68C0_004c68c0(p3fes::EEContext&);
void fn_sub_4C6D00_004c6d00(p3fes::EEContext&);
void fn_sub_4C7020_004c7020(p3fes::EEContext&);
void fn_sub_4C70A0_004c70a0(p3fes::EEContext&);
void fn_sub_4C71C0_004c71c0(p3fes::EEContext&);
void fn_sub_4C7208_004c7208(p3fes::EEContext&);
void fn_sub_4C7210_004c7210(p3fes::EEContext&);
void fn_sub_4C7258_004c7258(p3fes::EEContext&);
void fn_sub_4C7260_004c7260(p3fes::EEContext&);
void fn_sub_4C72A0_004c72a0(p3fes::EEContext&);
void fn_sub_4C7400_004c7400(p3fes::EEContext&);
void fn_sub_4C7410_004c7410(p3fes::EEContext&);
void fn_sub_4C7520_004c7520(p3fes::EEContext&);
void fn_sub_4C76C0_004c76c0(p3fes::EEContext&);
void fn_sub_4C78A0_004c78a0(p3fes::EEContext&);
void fn_sub_4C79E0_004c79e0(p3fes::EEContext&);
void fn_sub_4C7B60_004c7b60(p3fes::EEContext&);
void fn_sub_4C7B90_004c7b90(p3fes::EEContext&);
void fn_sub_4C7D30_004c7d30(p3fes::EEContext&);
void fn_sub_4C7D80_004c7d80(p3fes::EEContext&);
void fn_sub_4C81A0_004c81a0(p3fes::EEContext&);
void fn_sub_4CA000_004ca000(p3fes::EEContext&);
void fn_sub_4CA190_004ca190(p3fes::EEContext&);
void fn_sub_4CA520_004ca520(p3fes::EEContext&);
void fn_sub_4CA560_004ca560(p3fes::EEContext&);
void fn_sub_4CA5B0_004ca5b0(p3fes::EEContext&);
void fn_sub_4CAAC0_004caac0(p3fes::EEContext&);
void fn_sub_4CACE0_004cace0(p3fes::EEContext&);
void fn_sub_4CAD30_004cad30(p3fes::EEContext&);
void fn_sub_4CAF10_004caf10(p3fes::EEContext&);
void fn_sub_4CAF80_004caf80(p3fes::EEContext&);
void fn_sub_4CB1B0_004cb1b0(p3fes::EEContext&);
void fn_sub_4CB270_004cb270(p3fes::EEContext&);
void fn_sub_4CB7F0_004cb7f0(p3fes::EEContext&);
void fn_sub_4CBA20_004cba20(p3fes::EEContext&);
void fn_sub_4CBE00_004cbe00(p3fes::EEContext&);
void fn_sub_4CBEB0_004cbeb0(p3fes::EEContext&);
void fn_sub_4CBF20_004cbf20(p3fes::EEContext&);
void fn_sub_4CC050_004cc050(p3fes::EEContext&);
void fn_sub_4CC0A0_004cc0a0(p3fes::EEContext&);
void fn_sub_4CC1D0_004cc1d0(p3fes::EEContext&);
void fn_sub_4CC5C0_004cc5c0(p3fes::EEContext&);
void fn_sub_4CC6D0_004cc6d0(p3fes::EEContext&);
void fn_sub_4CCA60_004cca60(p3fes::EEContext&);
void fn_sub_4CCAC0_004ccac0(p3fes::EEContext&);
void fn_sub_4CCC30_004ccc30(p3fes::EEContext&);
void fn_sub_4CCD20_004ccd20(p3fes::EEContext&);
void fn_sub_4CCD50_004ccd50(p3fes::EEContext&);
void fn_sub_4CCF10_004ccf10(p3fes::EEContext&);
void fn_sub_4CD260_004cd260(p3fes::EEContext&);
void fn_sub_4CD620_004cd620(p3fes::EEContext&);
void fn_sub_4CD940_004cd940(p3fes::EEContext&);
void fn_sub_4CDB50_004cdb50(p3fes::EEContext&);
void fn_sub_4CDC70_004cdc70(p3fes::EEContext&);
void fn_sub_4CDCE0_004cdce0(p3fes::EEContext&);
void fn_sub_4CDD50_004cdd50(p3fes::EEContext&);
void fn_sub_4CDE00_004cde00(p3fes::EEContext&);
void fn_sub_4CDE90_004cde90(p3fes::EEContext&);
void fn_sub_4CDF00_004cdf00(p3fes::EEContext&);
void fn_sub_4CDF80_004cdf80(p3fes::EEContext&);
void fn_sub_4CE0F0_004ce0f0(p3fes::EEContext&);
void fn_sub_4CE200_004ce200(p3fes::EEContext&);
void fn_sub_4CEC10_004cec10(p3fes::EEContext&);
void fn_sub_4CEE30_004cee30(p3fes::EEContext&);
void fn_sub_4CF690_004cf690(p3fes::EEContext&);
void fn_sub_4CF790_004cf790(p3fes::EEContext&);
void fn_sub_4CF9B0_004cf9b0(p3fes::EEContext&);
void fn_sub_4CFD30_004cfd30(p3fes::EEContext&);
void fn_sub_4CFFD0_004cffd0(p3fes::EEContext&);
void fn_sub_4D05F0_004d05f0(p3fes::EEContext&);
void fn_sub_4D0640_004d0640(p3fes::EEContext&);
void fn_sub_4D0AC0_004d0ac0(p3fes::EEContext&);
void fn_sub_4D0E40_004d0e40(p3fes::EEContext&);
void fn_sub_4D0F00_004d0f00(p3fes::EEContext&);
void fn_sub_4D0FD0_004d0fd0(p3fes::EEContext&);
void fn_sub_4D1070_004d1070(p3fes::EEContext&);
void fn_sub_4D1170_004d1170(p3fes::EEContext&);
void fn_sub_4D11D0_004d11d0(p3fes::EEContext&);
void fn_sub_4D1210_004d1210(p3fes::EEContext&);
void fn_sub_4D13B0_004d13b0(p3fes::EEContext&);
void fn_sub_4D1840_004d1840(p3fes::EEContext&);
void fn_sub_4D1900_004d1900(p3fes::EEContext&);
void fn_sub_4D22F0_004d22f0(p3fes::EEContext&);
void fn_sub_4D3300_004d3300(p3fes::EEContext&);
void fn_sub_4D3800_004d3800(p3fes::EEContext&);
void fn_sub_4D3FC0_004d3fc0(p3fes::EEContext&);
void fn_sub_4D41E0_004d41e0(p3fes::EEContext&);
void fn_sub_4D5FE0_004d5fe0(p3fes::EEContext&);
void fn_sub_4D6B60_004d6b60(p3fes::EEContext&);
void fn_sub_4D8300_004d8300(p3fes::EEContext&);
void fn_sub_4D8310_004d8310(p3fes::EEContext&);
void fn_sub_4D83C0_004d83c0(p3fes::EEContext&);
void fn_sub_4D9520_004d9520(p3fes::EEContext&);
void fn_sub_4D9BC0_004d9bc0(p3fes::EEContext&);
void fn_sub_4DCEA0_004dcea0(p3fes::EEContext&);
void fn_sub_4DF0E0_004df0e0(p3fes::EEContext&);
void fn_sub_4DF3F0_004df3f0(p3fes::EEContext&);
void fn_sub_4DF9D0_004df9d0(p3fes::EEContext&);
void fn_sub_4DFCA0_004dfca0(p3fes::EEContext&);
void fn_sub_4DFCC0_004dfcc0(p3fes::EEContext&);
void fn_sub_4E00E0_004e00e0(p3fes::EEContext&);
void fn_sub_4E2F10_004e2f10(p3fes::EEContext&);
void fn_sub_4E3090_004e3090(p3fes::EEContext&);
void fn_sub_4E3550_004e3550(p3fes::EEContext&);
void fn_sub_4E40B0_004e40b0(p3fes::EEContext&);
void fn_sub_4E4130_004e4130(p3fes::EEContext&);
void fn_sub_4E98A0_004e98a0(p3fes::EEContext&);
void fn_sub_4EAC00_004eac00(p3fes::EEContext&);
void fn_sub_4EB7E0_004eb7e0(p3fes::EEContext&);
void fn_sub_4EB8C0_004eb8c0(p3fes::EEContext&);
void fn_sub_4EEC10_004eec10(p3fes::EEContext&);
void fn_sub_4EF1D0_004ef1d0(p3fes::EEContext&);
void fn_sub_4EF9F0_004ef9f0(p3fes::EEContext&);
void fn_sub_4EFA00_004efa00(p3fes::EEContext&);
void fn_sub_4F02E0_004f02e0(p3fes::EEContext&);
void fn_sub_4F0AD0_004f0ad0(p3fes::EEContext&);
void fn_sub_4F1E10_004f1e10(p3fes::EEContext&);
void fn_sub_4F28D0_004f28d0(p3fes::EEContext&);
void fn_worldSetSectorRenderCallBack_0049a3d0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;

// sub_467FD0 [matFXMaterialStreamRead] -- RpMatFX's material stream read: the effect type (sub_468EA0), then two slots,
//   each a type word and its data -- dual texture 4 (the two blend modes, a texture), environment map 2 (coefficient,
//   frame-buffer alpha, a texture), bump map 1 (coefficient, two textures; 1 / texture width kept at +16); the stream, or
//   0
// 0x00467FD0 sub_467FD0 -- 888 bytes; frame 0xA0: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_467FD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12};
    // 0x00467fd0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17848);  // 0x7CE738
    s0 = a2;
    v0 = addu(s0, v0);
    lw(s3, v0, 0);
    s1 = a0;
    if (s3 == 0) {
        // 0x00468030
        charge(ctx, 10);
        v0 = 0x960000;
        v1 = 0x30000;
        lw(a0, v0, -15360);  // 0x95C400
        v0 = 0x960000;
        lw(v0, v0, 392);  // 0x960188
        a1 = v1 | 0x120;
        jalr(ctx, 0x468044u, v0.u());
        s3 = v0;
        if (s3 == 0) {
            // 0x00468078
            charge(ctx, 2);
            s3 = 0;
            backedge(ctx);
        } else {
            // 0x00468058
            charge(ctx, 8);
            a0 = s3;
            a1 = 0;
            a2 = 144;
            jal(ctx, 0x468060u, gen::fn_memset_00521408);
            lw(v0, gp, -17848);  // 0x7CE738
            v0 = addu(s0, v0);
            sw(s3, v0, 0);
            backedge(ctx);
        }
    }
    // 0x00468008
    charge(ctx, 2);
    if (s3 == 0) {
        // 0x00468080
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x00468010
        charge(ctx, 6);
        a0 = s1;
        a1 = addiu(sp, 0x9C);
        a2 = 4;
        jal(ctx, 0x468018u, gen::fn_sub_4C1910_004c1910);
        if (v0 != 0) {
            // 0x00468088
            charge(ctx, 5);
            lw(a1, sp, 0x9C);
            a0 = s0;
            jal(ctx, 0x46808Cu, gen::fn_sub_468EA0_00468ea0);
            s5 = 0;
            s2 = addiu(sp, 0x74);
            for (;;) {
                // 0x0046809c
                charge(ctx, 6);
                a0 = s1;
                a1 = addiu(sp, 0x98);
                a2 = 4;
                jal(ctx, 0x4680A4u, gen::fn_sub_4C1910_004c1910);
                if (v0 == 0) {
                    goto L_004680b4_10;
                }
                // 0x004680bc
                charge(ctx, 4);
                lw(v1, sp, 0x98);
                a2 = 4;
                if (v1 == a2) {
                    // 0x00468220
                    charge(ctx, 7);
                    a0 = s1;
                    a1 = addiu(sp, 0x70);
                    a2 = 8;
                    link(ctx, 0x46822Cu);  // $ra first: the delay slot below depends on it
                    sw(zero, sp, 0x7C);
                    call(ctx, gen::fn_sub_4C1910_004c1910);
                    if (v0 == 0) {
                        goto L_00468318;
                    }
                    // 0x0046823c
                    charge(ctx, 5);
                    a0 = s1;
                    a1 = addiu(sp, 0x7C);
                    jal(ctx, 0x468240u, gen::fn_sub_467B40_00467b40);
                    if (v0 == 0) {
                        goto L_00468320;
                    }
                    // 0x00468250
                    charge(ctx, 3);
                    lw(a1, sp, 0x7C);
                    if (a1 != 0) {
                        // 0x0046825c
                        charge(ctx, 5);
                        a0 = s0;
                        jal(ctx, 0x46825Cu, gen::fn_sub_469770_00469770);
                        link(ctx, 0x468264u);  // $ra first: the delay slot below depends on it
                        lw(a0, sp, 0x7C);
                        call(ctx, gen::fn_sub_4D0F00_004d0f00);
                    }
                    // 0x00468270
                    charge(ctx, 4);
                    lw(a1, sp, 0x70);
                    lw(a2, s2, 0);
                    a0 = s0;
                    jal(ctx, 0x468278u, gen::fn_sub_469840_00469840);
                L_00468280:
                    charge(ctx, 5);
                    v0 = addiu(s5, 1);
                    s5 = v0 & 0xFF;
                    v0 = slti(s5, 2);
                    if (v0 == 0) {
                        goto L_00468294_35;
                    }
                    backedge(ctx);
                    continue;
                }
                // 0x004680cc
                charge(ctx, 3);
                v0 = 2;
                if (v1 == v0) {
                    // 0x004681a0
                    charge(ctx, 6);
                    a0 = s1;
                    a1 = addiu(sp, 0x88);
                    link(ctx, 0x4681A8u);  // $ra first: the delay slot below depends on it
                    sw(zero, sp, 0x80);
                    call(ctx, gen::fn_sub_4C18B0_004c18b0);
                    if (v0 == 0) {
                        break;
                    }
                    // 0x004681b8
                    charge(ctx, 6);
                    a0 = s1;
                    a1 = addiu(sp, 0x84);
                    a2 = 4;
                    jal(ctx, 0x4681C0u, gen::fn_sub_4C1910_004c1910);
                    if (v0 == 0) {
                        goto L_00468308;
                    }
                    // 0x004681d0
                    charge(ctx, 5);
                    a0 = s1;
                    a1 = addiu(sp, 0x80);
                    jal(ctx, 0x4681D4u, gen::fn_sub_467B40_00467b40);
                    if (v0 == 0) {
                        goto L_00468310;
                    }
                    // 0x004681e4
                    charge(ctx, 3);
                    lw(a1, sp, 0x80);
                    if (a1 != 0) {
                        // 0x004681f0
                        charge(ctx, 4);
                        a0 = s0;
                        jal(ctx, 0x4681F0u, gen::fn_sub_469400_00469400);
                        link(ctx, 0x4681F8u);  // $ra first: the delay slot below depends on it
                        lw(a0, sp, 0x80);
                        call(ctx, gen::fn_sub_4D0F00_004d0f00);
                    }
                    // 0x00468200
                    charge(ctx, 8);
                    lwc1(f12, sp, 0x88);
                    a0 = s0;
                    jal(ctx, 0x468204u, gen::fn_sub_469590_00469590);
                    lw(a1, sp, 0x84);
                    a0 = s0;
                    jal(ctx, 0x468210u, gen::fn_sub_469510_00469510);
                    goto L_00468280;
                }
                // 0x004680d8
                charge(ctx, 3);
                v0 = 1;
                if (v1 != v0) {
                    // 0x004680e4
                    charge(ctx, 3);
                    v0 = 5;
                    if (v1 != v0) {
                        // 0x004680f0
                        charge(ctx, 2);
                        if (v1 != 0) {
                            // 0x004680f8
                            charge(ctx, 2);
                        }
                    }
                    goto L_00468280;
                }
                // 0x00468100
                charge(ctx, 10);
                v0 = s5 & 0xFF;
                v0 = sll(v0, 6);
                a0 = s1;
                s4 = addu(s3, v0);
                a1 = addiu(sp, 0x94);
                sw(zero, sp, 0x90);
                link(ctx, 0x468118u);  // $ra first: the delay slot below depends on it
                sw(zero, sp, 0x8C);
                call(ctx, gen::fn_sub_4C18B0_004c18b0);
                if (v0 == 0) {
                    goto L_0046829c;
                }
                // 0x00468128
                charge(ctx, 5);
                a0 = s1;
                a1 = addiu(sp, 0x90);
                jal(ctx, 0x46812Cu, gen::fn_sub_467B40_00467b40);
                if (v0 == 0) {
                    goto L_004682a4;
                }
                // 0x0046813c
                charge(ctx, 5);
                a0 = s1;
                a1 = addiu(sp, 0x8C);
                jal(ctx, 0x468140u, gen::fn_sub_467B40_00467b40);
                if (v0 == 0) {
                    goto L_004682ac;
                }
                // 0x00468150
                charge(ctx, 3);
                lw(v0, sp, 0x90);
                if (v0 == 0) {
                    // 0x004682c8
                    charge(ctx, 3);
                    lw(a1, sp, 0x8C);
                    if (a1 == 0) {
                        // 0x004682f0
                        charge(ctx, 3);
                        sw(zero, s4, 4);
                        sw(zero, s4, 8);
                        backedge(ctx);
                    } else {
                        // 0x004682d4
                        charge(ctx, 6);
                        a0 = s0;
                        jal(ctx, 0x4682D4u, gen::fn_sub_469060_00469060);
                        link(ctx, 0x4682DCu);  // $ra first: the delay slot below depends on it
                        lw(a0, sp, 0x8C);
                        call(ctx, gen::fn_sub_4D0F00_004d0f00);
                        backedge(ctx);
                    }
                } else {
                    // 0x0046815c
                    charge(ctx, 11);
                    sw(v0, s4, 4);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    lw(v0, sp, 0x8C);
                    sw(v0, s4, 8);
                    lw(v0, s4, 4);
                    lw(v0, v0, 0);
                    lwc1(f1, v0, 12);
                    cvt_s_w(f1, f1);
                    div_s(f0, f0, f1);
                    swc1(f0, s4, 16);
                }
                // 0x00468188
                charge(ctx, 5);
                lwc1(f12, sp, 0x94);
                a0 = s0;
                jal(ctx, 0x46818Cu, gen::fn_sub_4692E0_004692e0);
                goto L_00468280;
            }
            // 0x00468300
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x00468028
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x00468324 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
    return;
L_004680b4_10:
    charge(ctx, 2);
    v0 = 0;
    // 0x00468324 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
    return;
L_00468294_35:
    charge(ctx, 2);
    v0 = s1;
    // 0x00468324 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
    return;
L_0046829c:
    charge(ctx, 2);
    v0 = 0;
    // 0x00468324 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
    return;
L_004682a4:
    charge(ctx, 2);
    v0 = 0;
    // 0x00468324 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
    return;
L_004682ac:
    charge(ctx, 3);
    lw(a0, sp, 0x90);
    if (a0 != 0) {
        // 0x004682b8
        charge(ctx, 2);
        jal(ctx, 0x4682B8u, gen::fn_sub_4D0F00_004d0f00);
    }
    // 0x004682c0
    charge(ctx, 2);
    v0 = 0;
    // 0x00468324 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
    return;
L_00468308:
    charge(ctx, 2);
    v0 = 0;
    // 0x00468324 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
    return;
L_00468310:
    charge(ctx, 2);
    v0 = 0;
    // 0x00468324 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
    return;
L_00468318:
    charge(ctx, 2);
    v0 = 0;
    // 0x00468324 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
    return;
L_00468320:
    charge(ctx, 1);
    v0 = 0;
    // 0x00468324 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// sub_468560 [matFXAtomicStreamRead] -- RpMatFX's atomic / world-sector stream read: a 4-byte flag; when set the
//   object's effects are enabled (sub_468DC0); the stream, or 0
// 0x00468560 sub_468560 -- 108 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_468560(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00468560
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    a1 = addiu(sp, 0x3C);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    a2 = 4;
    jal(ctx, 0x46857Cu, gen::fn_sub_4C1910_004c1910);
    if (v0 == 0) {
        // 0x004685a0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0046858c
        charge(ctx, 3);
        lw(v0, sp, 0x3C);
        if (v0 != 0) {
            // 0x004685a8
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x4685A8u, gen::fn_sub_468DC0_00468dc0);
            backedge(ctx);
        }
        // 0x00468598
        charge(ctx, 2);
        v0 = s1;
    }
    // 0x004685b8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_468EA0 [RpMatFXMaterialSetEffects] -- sets a material's effect type: the extension allocated (144 bytes, cleared)
//   on first use; a changed type releases the old effects (sub_4676C0); the slot types for the type (1 bump, 2 env, 3
//   bump + env, 4 dual -- blend modes 5 / 6 --, 5 UV transform, 6 UV transform + dual), then sub_469AA0; the material, or
//   0
// 0x00468EA0 sub_468EA0 -- 392 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_468EA0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00468ea0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(v0, gp, -17848);  // 0x7CE738
    v0 = addu(s2, v0);
    lw(s0, v0, 0);
    s1 = a1;
    if (s0 == 0) {
        // 0x00468fa8
        charge(ctx, 10);
        v0 = 0x960000;
        v1 = 0x30000;
        lw(a0, v0, -15360);  // 0x95C400
        v0 = 0x960000;
        lw(v0, v0, 392);  // 0x960188
        a1 = v1 | 0x120;
        jalr(ctx, 0x468FBCu, v0.u());
        s0 = v0;
        if (s0 == 0) {
            // 0x00468ff0
            charge(ctx, 2);
            s0 = 0;
            backedge(ctx);
        } else {
            // 0x00468fd0
            charge(ctx, 8);
            a0 = s0;
            a1 = 0;
            a2 = 144;
            jal(ctx, 0x468FD8u, gen::fn_memset_00521408);
            lw(v0, gp, -17848);  // 0x7CE738
            v0 = addu(s2, v0);
            sw(s0, v0, 0);
            backedge(ctx);
        }
    }
    // 0x00468ecc
    charge(ctx, 2);
    if (s0 != 0) {
        // 0x00468ed4
        charge(ctx, 2);
        if (s1 != 0) {
            // 0x00468edc
            charge(ctx, 3);
            lw(v0, s0, 128);
            if (v0 != 0) {
                // 0x00468ee8
                charge(ctx, 2);
                if (v0 != s1) {
                    goto L_00469000;
                }
                goto L_00468ef0;
            }
        L_00468ef0:
            charge(ctx, 1);
            sw(s1, s0, 128);
            goto L_00468ef4;
        }
    L_00469000:
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x469000u, gen::fn_sub_4676C0_004676c0);
        sw(s1, s0, 128);
        backedge(ctx);
    L_00468ef4:
        charge(ctx, 4);
        lw(v0, s0, 128);
        at = sltiu(v0, 7);
        if (at != 0) {
            // 0x00468f04
            charge(ctx, 7);
            v1 = 0x7C0000;
            v0 = sll(v0, 2);
            v1 = addiu(v1, -14272);  // &0x7BC840
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x468F20u:  // table[1]
                // 0x00468f20
                charge(ctx, 3);
                v0 = 1;
                sw(v0, s0, 32);
            L_00468f94:
                charge(ctx, 1);
                a0 = s2;
                break;
            case 0x468F2Cu:  // table[2]
                // 0x00468f2c
                charge(ctx, 3);
                v0 = 2;
                sw(v0, s0, 32);
                goto L_00468f94;
            case 0x468F38u:  // table[3]
                // 0x00468f38
                charge(ctx, 5);
                v1 = 1;
                v0 = 2;
                sw(v1, s0, 32);
                sw(v0, s0, 96);
                goto L_00468f94;
            case 0x468F4Cu:  // table[4]
                // 0x00468f4c
                charge(ctx, 8);
                v0 = 4;
                a0 = s2;
                sw(v0, s0, 32);
                a1 = 5;
                a2 = 6;
                jal(ctx, 0x468F5Cu, gen::fn_sub_469840_00469840);
                a0 = s2;
                break;
            case 0x468F6Cu:  // table[5]
                // 0x00468f6c
                charge(ctx, 3);
                v0 = 5;
                sw(v0, s0, 32);
                goto L_00468f94;
            case 0x468F78u:  // table[6]
                // 0x00468f78
                charge(ctx, 7);
                a1 = 5;
                v0 = 4;
                sw(a1, s0, 32);
                a0 = s2;
                sw(v0, s0, 96);
                a2 = 6;
                jal(ctx, 0x468F8Cu, gen::fn_sub_469840_00469840);
                goto L_00468f94;
            case 0x468F94u:  // table[0]
                goto L_00468f94;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
            goto L_00468f98;
        }
        goto L_00468f94;
    }
    // 0x00468ff8
    charge(ctx, 2);
    v0 = 0;
    // 0x00469010 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_00468f98:
    charge(ctx, 4);
    jal(ctx, 0x468F98u, gen::fn_sub_469AA0_00469aa0);
    v0 = s2;
    // 0x00469010 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_469770 [RpMatFXMaterialSetDualTexture] -- sets the dual-texture slot's texture: the slot of type 4 (or 0), the
//   texture's reference count up (+84), the old one destroyed (sub_4D0F00), then the slot's two dirty bits (sub_469A90 2
//   / 1); the material
// 0x00469770 sub_469770 -- 196 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_469770(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00469770
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(v0, gp, -17848);  // 0x7CE738
    a1 = 0;
    v0 = addu(s2, v0);
    lw(a0, v0, 0);
    v1 = 4;
    for (;;) {
        // 0x004697a0
        charge(ctx, 6);
        v0 = a1 & 0xFF;
        v0 = sll(v0, 6);
        s0 = addu(a0, v0);
        lw(v0, s0, 32);
        if (v0 == v1) {
            goto L_004697b8_2;
        }
        // 0x004697c0
        charge(ctx, 5);
        v0 = addiu(a1, 1);
        a1 = v0 & 0xFF;
        v0 = slti(a1, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004697d4
    charge(ctx, 2);
    s0 = 0;
    lw(v0, s1, 84);
L_004697dc:
    charge(ctx, 5);
    v0 = addiu(v0, 1);
    sw(v0, s1, 84);
    lw(a0, s0, 0);
    if (a0 != 0) {
        // 0x004697f0
        charge(ctx, 3);
        jal(ctx, 0x4697F0u, gen::fn_sub_4D0F00_004d0f00);
        sw(zero, s0, 0);
    }
    // 0x004697fc
    charge(ctx, 14);
    a0 = s0;
    a1 = 2;
    link(ctx, 0x469804u);  // $ra first: the delay slot below depends on it
    sw(s1, s0, 0);
    call(ctx, gen::fn_sub_469A90_00469a90);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x469810u, gen::fn_sub_469A90_00469a90);
    v0 = s2;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_004697b8_2:
    charge(ctx, 2);
    lw(v0, s1, 84);
    goto L_004697dc;
}

// sub_469840 [RpMatFXMaterialSetDualBlendModes] -- sets the dual-texture slot's source / destination blend modes (+4 /
//   +8), the slot's dirty bits 10 / 11 (sub_469A90), sub_469BC0; the material
// 0x00469840 sub_469840 -- 160 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_469840(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00469840
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a3 = 0;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17848);  // 0x7CE738
    s0 = a0;
    v0 = addu(s0, v0);
    lw(a0, v0, 0);
    v1 = 4;
    for (;;) {
        // 0x00469868
        charge(ctx, 6);
        v0 = a3 & 0xFF;
        v0 = sll(v0, 6);
        s1 = addu(a0, v0);
        lw(v0, s1, 32);
        if (v0 == v1) {
            goto L_00469880_2;
        }
        // 0x00469888
        charge(ctx, 5);
        v0 = addiu(a3, 1);
        a3 = v0 & 0xFF;
        v0 = slti(a3, 2);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0046989c
    charge(ctx, 2);
    s1 = 0;
    sw(a1, s1, 4);  // 0x4
L_004698a4:
    charge(ctx, 15);
    a0 = s1;
    sw(a2, s1, 8);
    a1 = 10;
    jal(ctx, 0x4698ACu, gen::fn_sub_469A90_00469a90);
    a0 = s1;
    a1 = 11;
    jal(ctx, 0x4698B8u, gen::fn_sub_469A90_00469a90);
    a0 = s0;
    jal(ctx, 0x4698C0u, gen::fn_sub_469BC0_00469bc0);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
    return;
L_00469880_2:
    charge(ctx, 2);
    sw(a1, s1, 4);
    goto L_004698a4;
}

// sub_4734D0 [ptankAtomicDestructor] -- PTank's atomic extension destructor (atomic + gp 0x7CE770): the first
//   material's texture cleared (sub_494D50), the instance data's packets flushed (sub_475CB0 / sub_475C20) and freed, the
//   extension freed (RwFree) and cleared; $a0
// 0x004734D0 sub_4734D0 -- 180 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4734D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004734d0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17792);  // 0x7CE770
    s0 = a0;
    v0 = addu(s0, v0);
    lw(v0, v0, 0);
    if (v0 != 0) {
        // 0x004734f4
        charge(ctx, 11);
        lw(v0, s0, 24);
        lw(v0, v0, 32);
        lw(a0, v0, 0);
        a1 = 0;
        jal(ctx, 0x473500u, gen::fn_sub_494D50_00494d50);
        lw(v0, gp, -17792);  // 0x7CE770
        v0 = addu(s0, v0);
        lw(v0, v0, 0);
        lw(v0, v0, 12);
        if (v0 != 0) {
            // 0x00473520
            charge(ctx, 11);
            a0 = s0;
            jal(ctx, 0x473520u, gen::fn_sub_475CB0_00475cb0);
            a0 = s0;
            jal(ctx, 0x473528u, gen::fn_sub_475C20_00475c20);
            lw(v1, gp, -17792);  // 0x7CE770
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            v1 = addu(s0, v1);
            lw(v1, v1, 0);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x473544u);  // $ra = the return address
            lw(a0, v1, 12);
            call_ptr(ctx, jt);
        }
        // 0x0047354c
        charge(ctx, 9);
        lw(v1, gp, -17792);  // 0x7CE770
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        v1 = addu(s0, v1);
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x47355Cu);  // $ra = the return address
        lw(a0, v1, 0);
        call_ptr(ctx, jt);
        lw(v0, gp, -17792);  // 0x7CE770
        v0 = addu(s0, v0);
        sw(zero, v0, 0);
    }
    // 0x00473570 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_474260 [RpPTankAtomicCreate] -- creates a PTank atomic: an atomic (sub_491880) with a 320-byte extension
//   (RwMalloc), the render callback chained (sub_474160), the data / platform flags, the instance callback or the default
//   layout (sub_473B10 / sub_473600), the create callback (+24), the default constant colour / matrix / UV, the three
//   current render states; the atomic, or 0 (the atomic destroyed)
// 0x00474260 sub_474260 -- 968 bytes; frame 0xC0: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_474260(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7};
    // 0x00474260
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a3;
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    s2 = 0;
    link(ctx, 0x474294u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_491880_00491880);
    s1 = v0;
    if (s1 != 0) {
        // 0x004742a8
        charge(ctx, 9);
        v0 = 0x30000;
        a1 = v0 | 0x12F;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178
        a0 = 320;
        jalr(ctx, 0x4742B8u, v0.u());
        s0 = v0;
        if (s0 == 0) {
            goto L_004745f4;
        }
        // 0x004742cc
        charge(ctx, 8);
        lw(v1, s1, 72);
        v0 = 0x470000;
        v0 = addiu(v0, 16736);  // &sub_474160
        sw(v1, s0, 16);
        sw(v0, s1, 72);
        lw(v0, s1, 72);
        if (v0 == 0) {
            // 0x0047436c
            charge(ctx, 4);
            v0 = 0x490000;
            v0 = addiu(v0, 2144);  // &AtomicDefaultRenderCallBack
            sw(v0, s1, 72);
            backedge(ctx);
        }
        // 0x004742ec
        charge(ctx, 18);
        sw(s5, s0, 0);
        v0 = si(-1);
        sw(zero, s0, 4);
        a1 = s6;
        sw(s4, s0, 168);
        a0 = addiu(s0, 20);
        sw(s3, s0, 68);
        a2 = 16;
        sw(v0, s0, 64);
        sw(zero, s0, 60);
        sw(zero, s0, 12);
        lw(v0, gp, -17792);  // 0x7CE770
        v0 = addu(s1, v0);
        link(ctx, 0x474320u);  // $ra first: the delay slot below depends on it
        sw(s0, v0, 0);
        call(ctx, gen::fn_memcpy_00521250);
        lw(v0, s0, 20);
        if (v0 == 0) {
            // 0x0047437c
            charge(ctx, 4);
            v1 = 0x20000000;
            v0 = s4 & v1;
            if (v0 != v1) {
                // 0x004743a4
                charge(ctx, 6);
                a0 = s0;
                a1 = s4;
                a2 = s3;
                jal(ctx, 0x4743ACu, gen::fn_sub_473600_00473600);
                s2 = v0;
                backedge(ctx);
            } else {
                // 0x0047438c
                charge(ctx, 6);
                a0 = s0;
                a1 = s4;
                a2 = s3;
                jal(ctx, 0x474394u, gen::fn_sub_473B10_00473b10);
                s2 = v0;
                backedge(ctx);
            }
        } else {
            // 0x00474334
            charge(ctx, 6);
            lw(a1, s0, 0);
            a0 = addiu(s0, 80);
            a2 = s4;
            a3 = s3;
            jalr(ctx, 0x474340u, v0.u());
            sw(v0, s0, 12);
        }
        // 0x0047434c
        charge(ctx, 3);
        v0 = 1;
        if (s2 != v0) {
            // 0x00474358
            charge(ctx, 3);
            lw(v0, s0, 12);
            if (v0 == 0) {
                goto L_004745f4;
            }
            // 0x00474364
            charge(ctx, 2);
            lw(a2, s0, 0);
            goto L_004743c0;
        }
        // 0x004743bc
        charge(ctx, 1);
        lw(a2, s0, 0);
    L_004743c0:
        charge(ctx, 9);
        a3 = s4;
        lw(v0, s0, 24);
        t0 = s3;
        a0 = s1;
        a1 = addiu(s0, 80);
        jalr(ctx, 0x4743D0u, v0.u());
        v1 = 1;
        if (v0 != v1) {
            goto L_004745f4;
        }
        // 0x004743e4
        charge(ctx, 3);
        v1 = addiu(sp, 0xB0);
        v0 = 8;
        if (v1 != 0) {
            for (;;) {
                // 0x004743f0
                charge(ctx, 7);
                sb(zero, v1, 0);
                v0 = addiu(v0, -1);
                v1 = addiu(v1, 1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0047440c
        charge(ctx, 122);
        v0 = 0x780000;
        v1 = 0x780000;
        lwc1(f5, v0, -21568);  // 0x77ABC0
        lbu(a0, gp, -20781);  // 0x7CDBC3
        lwc1(f0, v1, -21556);  // 0x77ABCC
        lbu(a1, gp, -20782);  // 0x7CDBC2
        lbu(a3, gp, -20784);  // 0x7CDBC0
        lbu(a2, gp, -20783);  // 0x7CDBC1
        v0 = 0x780000;
        sb(a0, sp, 0xBF);
        lwc1(f1, v0, -21564);  // 0x77ABC4
        sb(a1, sp, 0xBE);
        swc1(f0, sp, 0x8C);
        sb(a3, sp, 0xBC);
        sb(a2, sp, 0xBD);
        swc1(f5, sp, 0x80);
        a1 = 0;
        v0 = 0x780000;
        lwc1(f4, v0, -21560);  // 0x77ABC8
        swc1(f1, sp, 0x84);
        v0 = 0x780000;
        lwc1(f3, v0, -21552);  // 0x77ABD0
        swc1(f4, sp, 0x88);
        v0 = 0x780000;
        lwc1(f2, v0, -21548);  // 0x77ABD4
        swc1(f3, sp, 0x90);
        v0 = 0x780000;
        lwc1(f1, v0, -21544);  // 0x77ABD8
        swc1(f2, sp, 0x94);
        v0 = 0x780000;
        lwc1(f0, v0, -21540);  // 0x77ABDC
        swc1(f1, sp, 0x98);
        lw(v0, s1, 24);
        lw(v0, v0, 32);
        lw(a0, v0, 0);
        link(ctx, 0x474498u);  // $ra first: the delay slot below depends on it
        swc1(f0, sp, 0x9C);
        call(ctx, gen::fn_sub_494D50_00494d50);
        ld(t2, gp, -20792);  // 0x7CDBB8
        v0 = 0x20000;
        t0 = v0 | 0x3;
        s2 = 0x960000;
        lwc1(f1, sp, 0xB0);
        t1 = 0x3F800000;
        lwc1(f0, sp, 0xB4);
        lbu(a3, sp, 0xBC);
        lbu(a2, sp, 0xBD);
        lwc1(f7, sp, 0x80);
        lbu(v1, sp, 0xBE);
        lwc1(f6, sp, 0x84);
        sd(t2, sp, 0xA8);
        lwc1(f5, sp, 0x88);
        lwc1(f3, sp, 0xA8);
        lbu(v0, sp, 0xBF);
        lwc1(f2, sp, 0xAC);
        s2 = addiu(s2, 148);  // &pfn_RwRenderStateGet
        lwc1(f4, sp, 0x8C);
        a0 = 10;
        swc1(f3, s0, 192);
        swc1(f2, s0, 196);
        sw(zero, s0, 200);
        lwc1(f3, sp, 0x90);
        swc1(f1, s0, 184);
        swc1(f0, s0, 188);
        sw(t1, s0, 296);
        lwc1(f2, sp, 0x94);
        sw(t1, s0, 276);
        lwc1(f1, sp, 0x98);
        sw(t1, s0, 256);
        lwc1(f0, sp, 0x9C);
        sw(zero, s0, 272);
        sw(zero, s0, 264);
        sw(zero, s0, 260);
        sw(zero, s0, 292);
        sw(zero, s0, 288);
        sw(zero, s0, 280);
        sw(zero, s0, 312);
        sw(zero, s0, 308);
        sw(zero, s0, 304);
        lw(t1, s0, 268);
        t0 = t1 | t0;
        sw(t0, s0, 268);
        sb(a3, s0, 204);
        sb(a2, s0, 205);
        sb(v1, s0, 206);
        sb(v0, s0, 207);
        sb(a3, s0, 208);
        sb(a2, s0, 209);
        sb(v1, s0, 210);
        sb(v0, s0, 211);
        sb(a3, s0, 212);
        sb(a2, s0, 213);
        sb(v1, s0, 214);
        sb(v0, s0, 215);
        sb(a3, s0, 216);
        sb(a2, s0, 217);
        sb(v1, s0, 218);
        sb(v0, s0, 219);
        sb(a3, s0, 220);
        sb(a2, s0, 221);
        sb(v1, s0, 222);
        sb(v0, s0, 223);
        swc1(f7, s0, 224);
        swc1(f6, s0, 228);
        swc1(f5, s0, 232);
        swc1(f4, s0, 236);
        swc1(f3, s0, 240);
        swc1(f2, s0, 244);
        swc1(f1, s0, 248);
        swc1(f0, s0, 252);
        lw(v0, s2, 0);  // pfn_RwRenderStateGet
        a1 = addiu(s0, 172);
        jalr(ctx, 0x4745C4u, v0.u());
        lw(v0, s2, 0);  // pfn_RwRenderStateGet
        a0 = 11;
        a1 = addiu(s0, 176);
        jalr(ctx, 0x4745D4u, v0.u());
        lw(v0, s2, 0);  // pfn_RwRenderStateGet
        a1 = addiu(s0, 180);
        a0 = 12;
        jalr(ctx, 0x4745E4u, v0.u());
        v0 = s1;
        // 0x00474600 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(ra, sp, 0x70);
        lq(s6, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0xC0);
        return;
    }
L_004745f4:
    charge(ctx, 3);
    a0 = s1;
    jal(ctx, 0x4745F4u, gen::fn_sub_491A80_00491a80);
    v0 = 0;
    // 0x00474600 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xC0);
}

// sub_474630 [RpPTankAtomicDestroy] -- destroys a PTank atomic (a tail call into the atomic destroy sub_491A80)
// 0x00474630 sub_474630 -- 8 bytes; leaf frame (no stack)
void sub_474630(EEContext& ctx) {
    using namespace hg;
    // 0x00474630
    enter(ctx, 2);  // entry check point + this block's cycles
    gen::fn_sub_491A80_00491a80(ctx);  // tail call
}

// sub_474820 [ptankSetGsPacketField] -- writes one field of a PTank atomic's GS packet: kind 2 the low 16 bits of the
//   64-bit word +200, kind 1 the word +184 (the low byte and the top byte) and clears flag 0x10000000; 1, or 0 for
//   another kind
// 0x00474820 sub_474820 -- 152 bytes; leaf frame (no stack)
void sub_474820(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28};
    // 0x00474820
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, gp, -17792);  // 0x7CE770
    v0 = 2;
    v1 = addu(a0, v1);
    lw(t0, v1, 0);
    lw(a3, t0, 156);
    if (a1 == v0) {
        // 0x00474888
        charge(ctx, 9);
        ld(a0, a3, 200);
        v0 = lui(0xFFFF);
        pcpyld(v0, zero, v0);
        v1 = a2 & 0xFFFF;
        v0 = a0 & v0;
        sd(v0, a3, 200);
        ld(v0, a3, 200);
        v0 = v0 | v1;
        sd(v0, a3, 200);
    L_004748ac:
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x00474838
        charge(ctx, 3);
        v0 = 1;
        if (a1 == v0) {
            // 0x0047484c
            charge(ctx, 15);
            a1 = dsll32(a2, 0);
            a0 = 0xFF00;
            a1 = dsrl32(a1, 0);
            a0 = dsll(a0, 16);
            a0 = a1 & a0;
            v0 = lui(0xEFFF);
            v1 = a2 & 0xFF;
            a0 = dsll(a0, 8);
            v1 = v1 | a0;
            v0 = v0 | 0xFFFF;
            sd(v1, a3, 184);
            lw(v1, t0, 64);
            v0 = v1 & v0;
            sw(v0, t0, 64);
            goto L_004748ac;
        }
        // 0x00474844
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004748b0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// sub_474F20 [ptankInstanceLayout] -- lays out a PTank atomic's instance buffer from $a1: with a material pipe the
//   per-packet DMA headers and the cluster offsets of each batch (sub_474D30), else the per-property offsets (+84.. +148)
//   for the flags in +168 (the property strides 0x7BC904..)
// 0x00474F20 sub_474F20 -- 1188 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_474F20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00474f20
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, -17792);  // 0x7CE770
    s0 = a1;
    v1 = addu(a0, v1);
    lw(a1, v1, 0);
    lw(s4, a1, 156);
    lw(a0, a1, 168);
    lw(v1, s4, 216);
    s5 = addiu(a1, 80);
    if (v1 == 0) {
        // 0x004750f8
        charge(ctx, 4);
        v1 = 0x20000000;
        v1 = a0 & v1;
        if (v1 == 0) {
            // 0x0047517c
            charge(ctx, 4);
            lw(v1, a1, 0);
            a1 = a0 & 0x1;
            if (a1 != 0) {
                // 0x0047528c
                charge(ctx, 7);
                a1 = sll(v1, 4);
                sw(s0, s5, 4);
                a2 = addiu(a1, 15);
                a1 = si(-16);
                a2 = addu(s0, a2);
                s0 = a2 & a1;
                backedge(ctx);
            }
            // 0x0047518c
            charge(ctx, 3);
            a1 = a0 & 0x8;
            if (a1 != 0) {
                // 0x004752a8
                charge(ctx, 9);
                a1 = 0x7C0000;
                sw(s0, s5, 12);
                lw(a1, a1, -14076);  // 0x7BC904
                mult(a2, v1, a1);
                a2 = addiu(a2, 15);
                a1 = si(-16);
                a2 = addu(s0, a2);
                s0 = a2 & a1;
                backedge(ctx);
            }
            // 0x00475198
            charge(ctx, 3);
            a1 = a0 & 0x10;
            if (a1 != 0) {
                // 0x004752cc
                charge(ctx, 9);
                a1 = 0x7C0000;
                sw(s0, s5, 20);
                lw(a1, a1, -14072);  // 0x7BC908
                mult(a2, v1, a1);
                a2 = addiu(a2, 15);
                a1 = si(-16);
                a2 = addu(s0, a2);
                s0 = a2 & a1;
                backedge(ctx);
            }
            // 0x004751a4
            charge(ctx, 3);
            a1 = a0 & 0x4;
            if (a1 != 0) {
                // 0x004752f0
                charge(ctx, 9);
                a1 = 0x7C0000;
                sw(s0, s5, 28);
                lw(a1, a1, -14068);  // 0x7BC90C
                mult(a2, v1, a1);
                a2 = addiu(a2, 79);
                a1 = si(-16);
                a2 = addu(s0, a2);
                s0 = a2 & a1;
                backedge(ctx);
            }
            // 0x004751b0
            charge(ctx, 3);
            a1 = a0 & 0x2;
            if (a1 != 0) {
                // 0x00475314
                charge(ctx, 9);
                a1 = 0x7C0000;
                sw(s0, s5, 36);
                lw(a1, a1, -14064);  // 0x7BC910
                mult(a2, v1, a1);
                a2 = addiu(a2, 79);
                a1 = si(-16);
                a2 = addu(s0, a2);
                s0 = a2 & a1;
                backedge(ctx);
            }
            // 0x004751bc
            charge(ctx, 3);
            a1 = a0 & 0x40;
            if (a1 != 0) {
                // 0x00475338
                charge(ctx, 9);
                a1 = 0x7C0000;
                sw(s0, s5, 44);
                lw(a1, a1, -14060);  // 0x7BC914
                mult(a2, v1, a1);
                a2 = addiu(a2, 15);
                a1 = si(-16);
                a2 = addu(s0, a2);
                s0 = a2 & a1;
                backedge(ctx);
            }
            // 0x004751c8
            charge(ctx, 3);
            a1 = a0 & 0x20;
            if (a1 != 0) {
                // 0x0047535c
                charge(ctx, 9);
                a1 = 0x7C0000;
                sw(s0, s5, 52);
                lw(a1, a1, -14056);  // 0x7BC918
                mult(a2, v1, a1);
                a2 = addiu(a2, 15);
                a1 = si(-16);
                a2 = addu(s0, a2);
                s0 = a2 & a1;
                backedge(ctx);
            }
            // 0x004751d4
            charge(ctx, 3);
            a1 = a0 & 0x80;
            if (a1 != 0) {
                // 0x00475380
                charge(ctx, 9);
                a1 = 0x7C0000;
                sw(s0, s5, 60);
                lw(a1, a1, -14052);  // 0x7BC91C
                mult(a1, v1, a1);
                a1 = addiu(a1, 15);
                v1 = si(-16);
                a1 = addu(s0, a1);
                s0 = a1 & v1;
                backedge(ctx);
            }
            // 0x004751e0
            charge(ctx, 3);
            v1 = a0 & 0x100;
            if (v1 == 0) {
                backedge(ctx);
            } else {
                // 0x004751ec
                charge(ctx, 2);
                sw(s0, s5, 68);
                backedge(ctx);
            }
        } else {
            // 0x00475108
            charge(ctx, 3);
            v1 = a0 & 0x1;
            if (v1 != 0) {
                // 0x004751f4
                charge(ctx, 3);
                sw(s0, s5, 4);
                s0 = addiu(s0, 16);
                backedge(ctx);
            }
            // 0x00475114
            charge(ctx, 3);
            v1 = a0 & 0x8;
            if (v1 != 0) {
                // 0x00475200
                charge(ctx, 5);
                v1 = 0x7C0000;
                sw(s0, s5, 12);
                lw(v1, v1, -14076);  // 0x7BC904
                s0 = addu(v1, s0);
                backedge(ctx);
            }
            // 0x00475120
            charge(ctx, 3);
            v1 = a0 & 0x10;
            if (v1 != 0) {
                // 0x00475214
                charge(ctx, 5);
                v1 = 0x7C0000;
                sw(s0, s5, 20);
                lw(v1, v1, -14072);  // 0x7BC908
                s0 = addu(v1, s0);
                backedge(ctx);
            }
            // 0x0047512c
            charge(ctx, 3);
            v1 = a0 & 0x4;
            if (v1 != 0) {
                // 0x00475228
                charge(ctx, 5);
                v1 = 0x7C0000;
                sw(s0, s5, 28);
                lw(v1, v1, -14068);  // 0x7BC90C
                s0 = addu(v1, s0);
                backedge(ctx);
            }
            // 0x00475138
            charge(ctx, 3);
            v1 = a0 & 0x2;
            if (v1 != 0) {
                // 0x0047523c
                charge(ctx, 5);
                v1 = 0x7C0000;
                sw(s0, s5, 36);
                lw(v1, v1, -14064);  // 0x7BC910
                s0 = addu(v1, s0);
                backedge(ctx);
            }
            // 0x00475144
            charge(ctx, 3);
            v1 = a0 & 0x40;
            if (v1 != 0) {
                // 0x00475250
                charge(ctx, 5);
                v1 = 0x7C0000;
                sw(s0, s5, 44);
                lw(v1, v1, -14060);  // 0x7BC914
                s0 = addu(v1, s0);
                backedge(ctx);
            }
            // 0x00475150
            charge(ctx, 3);
            v1 = a0 & 0x20;
            if (v1 != 0) {
                // 0x00475264
                charge(ctx, 5);
                v1 = 0x7C0000;
                sw(s0, s5, 52);
                lw(v1, v1, -14056);  // 0x7BC918
                s0 = addu(v1, s0);
                backedge(ctx);
            }
            // 0x0047515c
            charge(ctx, 3);
            v1 = a0 & 0x80;
            if (v1 != 0) {
                // 0x00475278
                charge(ctx, 5);
                v1 = 0x7C0000;
                sw(s0, s5, 60);
                lw(v1, v1, -14052);  // 0x7BC91C
                s0 = addu(v1, s0);
                backedge(ctx);
            }
            // 0x00475168
            charge(ctx, 3);
            v1 = a0 & 0x100;
            if (v1 == 0) {
                backedge(ctx);
            } else {
                // 0x00475174
                charge(ctx, 2);
                sw(s0, s5, 68);
                backedge(ctx);
            }
        }
    } else {
        // 0x00474f64
        charge(ctx, 3);
        s3 = 0;
        s2 = s4;
        s1 = 0;
        for (;;) {
            // 0x00474f70
            charge(ctx, 32);
            v1 = 0x50000000;
            a0 = 0x3000000;
            sw(v1, s2, 0);
            sw(s0, s2, 4);
            v1 = 0x2000000;
            sw(a0, s2, 8);
            lw(a0, s4, 252);
            lwu(a0, a0, 20);
            v1 = a0 | v1;
            v1 = dsll32(v1, 0);
            v1 = dsra32(v1, 0);
            sw(v1, s2, 12);
            sw(zero, s2, 16);
            sw(zero, s2, 20);
            lw(a0, s4, 304);
            lw(v1, s4, 296);
            a0 = addu(s0, a0);
            v1 = addu(v1, a0);
            v1 = addiu(v1, -32);
            sw(v1, s2, 24);
            sw(v1, s2, 28);
            lw(a0, s4, 292);
            lw(v1, s4, 296);
            mult(a0, a0, v1);
            lw(a1, s4, 252);
            lw(v1, s4, 304);
            v1 = addu(s0, v1);
            s0 = addu(v1, a0);
            lw(v1, a1, 24);
            at = sltu(0, v1);
            t0 = 0;
            if (at != 0) {
                // 0x00474ff0
                charge(ctx, 4);
                a3 = 0;
                a2 = s4;
                a0 = addu(s4, s1);
                for (;;) {
                    // 0x00475000
                    charge(ctx, 10);
                    v1 = addu(a1, a3);
                    lw(v1, v1, 36);
                    a1 = sll(v1, 2);
                    t1 = addu(a0, a1);
                    sw(s0, t1, 320);
                    a1 = addu(s4, a1);
                    sw(s0, a2, 68);
                    lw(t4, a1, 256);
                    if (t4 == 0) {
                        // 0x00475040
                        charge(ctx, 8);
                        lw(a1, s4, 252);
                        lw(t1, s4, 292);
                        t3 = addu(a1, a3);
                        t2 = sll(t1, 4);
                        lw(t1, t3, 40);
                        mult(t1, t1, t2);
                        s0 = addu(s0, t1);
                    } else {
                        // 0x00475028
                        charge(ctx, 6);
                        lw(a1, s4, 252);
                        t1 = addu(a1, a3);
                        lw(t1, t1, 44);
                        t1 = sll(t1, 4);
                        s0 = addu(s0, t1);
                    }
                    // 0x00475060
                    charge(ctx, 4);
                    v1 = addiu(v1, -3);
                    at = sltiu(v1, 2);
                    if (at != 0) {
                        // 0x00475070
                        charge(ctx, 2);
                        if (t4 == 0) {
                            // 0x00475078
                            charge(ctx, 2);
                            s0 = addiu(s0, 64);
                        }
                    }
                    // 0x00475080
                    charge(ctx, 6);
                    lw(v1, a1, 24);
                    t0 = addiu(t0, 1);
                    a3 = addiu(a3, 24);
                    v1 = sltu(t0, v1);
                    a2 = addiu(a2, 16);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x00475098
            charge(ctx, 9);
            a0 = s4;
            a1 = s3;
            jal(ctx, 0x47509Cu, gen::fn_sub_474D30_00474d30);
            lw(v1, s4, 232);
            s3 = addiu(s3, 1);
            s2 = addiu(s2, 32);
            at = sltu(v1, s3);
            s1 = addiu(s1, 36);
            if (at != 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004750bc
        charge(ctx, 1);
        a1 = 0;
        for (;;) {
            // 0x004750c0
            charge(ctx, 11);
            lw(a0, s4, 320);
            a1 = addiu(a1, 3);
            v1 = sltiu(a1, 9);
            sw(a0, s5, 4);
            lw(a0, s4, 324);
            sw(a0, s5, 12);
            lw(a0, s4, 328);
            sw(a0, s5, 20);
            s4 = addiu(s4, 12);
            s5 = addiu(s5, 24);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004750ec
        charge(ctx, 1);
    }
    // 0x004750f0
    charge(ctx, 2);
    ld(ra, sp, 0x60);
    // 0x004753a4
    charge(ctx, 8);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// sub_475CB0 [ptankFlushPackets] -- flushes a PTank atomic's DMA packets: for each used batch two forced buffer swaps
//   (_rwDMAForceBufferSwap), unless flag 0x10 of +68
// 0x00475CB0 sub_475CB0 -- 168 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_475CB0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00475cb0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, -17792);  // 0x7CE770
    v1 = addu(a0, v1);
    lw(a0, v1, 0);
    lw(v1, a0, 68);
    v1 = v1 & 0x10;
    if (v1 == 0) {
        // 0x00475ce0
        charge(ctx, 4);
        lw(s0, a0, 156);
        lw(v1, s0, 216);
        if (v1 != 0) {
            // 0x00475cf0
            charge(ctx, 2);
            s2 = 0;
            s1 = s0;
            for (;;) {
                // 0x00475cf8
                charge(ctx, 3);
                lw(v1, s1, 16);
                if (v1 != 0) {
                    // 0x00475d28
                    charge(ctx, 6);
                    jal(ctx, 0x475D28u, gen::fn__rwDMAForceBufferSwap_004d4df0);
                    jal(ctx, 0x475D30u, gen::fn__rwDMAForceBufferSwap_004d4df0);
                    backedge(ctx);
                } else {
                    // 0x00475d04
                    charge(ctx, 1);
                }
                // 0x00475d08
                charge(ctx, 5);
                lw(v1, s0, 232);
                s2 = addiu(s2, 1);
                at = sltu(v1, s2);
                s1 = addiu(s1, 32);
                if (at != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00475d1c
            charge(ctx, 1);
        }
    }
    // 0x00475d20
    charge(ctx, 2);
    // 0x00475d40
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_475D60 [ptankAtomicSetup] -- PTank's per-atomic set-up: picks the geometry and pipeline by the data / platform
//   flags -- the instancing pipe (an empty geometry, render callback sub_47A510), the 2D sprite (sub_478E80) or 3D sprite
//   (sub_47A210) geometry with their callbacks, the generic quads (sub_486340, pipe +20), a custom path through the
//   callback 0x77B254 -- then the instance layout (sub_474F20); 1 / 0
// 0x00475D60 sub_475D60 -- 980 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_475D60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00475d60
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v0 = lui(0xCFF7);
    sd(ra, sp, 0x60);
    v1 = v0 | 0xFF78;
    sq(s5, sp, 0x50);
    v0 = lui(0xCEE1);
    sq(s4, sp, 0x40);
    v0 = v0 | 0x7E10;
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s5 = t0;
    sq(s0, sp, 0x0);
    s1 = a3;
    lw(s0, a1, 76);
    v1 = s1 & v1;
    v0 = s1 & v0;
    v1 = sltu(0, v1);
    v0 = sltu(0, v0);
    s2 = a2;
    a0 = v0 ^ 0x1;
    v0 = 4;
    a1 = v1 ^ 0x1;
    v1 = s5 & 0x4;
    a2 = s5 & 0x10;
    if (v1 == v0) {
        // 0x00475dd0
        charge(ctx, 3);
        a1 = 0;
        a0 = 0;
        a2 = 0;
    }
    // 0x00475ddc
    charge(ctx, 2);
    if (a2 != 0) {
        // 0x00475ec0
        charge(ctx, 18);
        lw(v0, gp, -17792);  // 0x7CE770
        a1 = 0x780000;
        a1 = addiu(a1, -19888);  // &0x77B250
        a2 = 16;
        v0 = addu(s4, v0);
        lw(v0, v0, 0);
        a0 = addiu(v0, 20);
        jal(ctx, 0x475ED8u, gen::fn_memcpy_00521250);
        v0 = 0x780000;
        a0 = s4;
        lw(v0, v0, -19884);  // 0x77B254
        a1 = s3;
        a2 = s2;
        a3 = s1;
        t0 = s5;
        jalr(ctx, 0x475EF8u, v0.u());
    L_00476110:
        charge(ctx, 1);
        ld(ra, sp, 0x60);
    } else {
        // 0x00475de4
        charge(ctx, 3);
        lw(v0, s0, 216);
        if (v0 == 0) {
            // 0x00475df0
            charge(ctx, 2);
            if (a1 != 0) {
                // 0x0047600c
                charge(ctx, 8);
                a1 = s2;
                a2 = s1;
                a0 = s4;
                jal(ctx, 0x476014u, gen::fn_sub_478E80_00478e80);
                s1 = v0;
                v0 = 1;
                if (s1 != v0) {
                    backedge(ctx);
                } else {
                    // 0x0047602c
                    charge(ctx, 14);
                    lw(v0, gp, -17792);  // 0x7CE770
                    a1 = 0x470000;
                    a0 = 0x470000;
                    a1 = addiu(a1, 29008);  // &sub_477150
                    a0 = addiu(a0, 30224);  // &sub_477610
                    v1 = 4;
                    v0 = addu(s4, v0);
                    lw(v0, v0, 0);
                    sw(a1, v0, 36);
                    sw(a0, v0, 40);
                    lw(a0, s3, 88);
                    a0 = a0 & 0x4;
                    if (a0 != v1) {
                        // 0x00476074
                        charge(ctx, 3);
                        v1 = 0x480000;
                        v1 = addiu(v1, -32512);  // &sub_478100
                        sw(v1, v0, 52);
                    } else {
                        // 0x00476064
                        charge(ctx, 4);
                        v1 = 0x480000;
                        v1 = addiu(v1, -32128);  // &sub_478280
                        sw(v1, v0, 52);
                    }
                    // 0x00476080
                    charge(ctx, 5);
                    lw(a1, s3, 88);
                    v1 = 128;
                    a0 = a1 & 0x80;
                    if (a0 == v1) {
                        // 0x00476100
                        charge(ctx, 4);
                        v1 = 0x470000;
                        v1 = addiu(v1, 32432);  // &sub_477EB0
                        sw(v1, v0, 44);
                        backedge(ctx);
                    } else {
                        // 0x00476094
                        charge(ctx, 4);
                        a0 = 0x80000;
                        v1 = a1 & a0;
                        if (v1 != a0) {
                            // 0x004760b4
                            charge(ctx, 1);
                            sw(zero, v0, 44);
                        } else {
                            // 0x004760a4
                            charge(ctx, 4);
                            v1 = 0x470000;
                            v1 = addiu(v1, 31888);  // &sub_477C90
                            sw(v1, v0, 44);
                        }
                    }
                    // 0x004760b8
                    charge(ctx, 5);
                    lw(a0, s3, 88);
                    v1 = 2;
                    a0 = a0 & 0x2;
                    if (a0 != v1) {
                        // 0x004760dc
                        charge(ctx, 3);
                        v1 = 0x470000;
                        v1 = addiu(v1, 30736);  // &sub_477810
                        sw(v1, v0, 48);
                    } else {
                        // 0x004760cc
                        charge(ctx, 4);
                        v1 = 0x470000;
                        v1 = addiu(v1, 31264);  // &sub_477A20
                        sw(v1, v0, 48);
                    }
                    // 0x004760e8
                    charge(ctx, 6);
                    sw(zero, v0, 56);
                    a1 = addiu(s0, 400);
                    a0 = s4;
                    jal(ctx, 0x4760F0u, gen::fn_sub_474F20_00474f20);
                    backedge(ctx);
                }
                goto L_00475eb4;
            }
            // 0x00475df8
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x00475e58
                charge(ctx, 10);
                a1 = addiu(s0, 400);
                a0 = s4;
                jal(ctx, 0x475E5Cu, gen::fn_sub_474F20_00474f20);
                a1 = s2;
                a2 = s1;
                a0 = s4;
                jal(ctx, 0x475E6Cu, gen::fn_sub_486340_00486340);
                s1 = v0;
                if (s1 != 0) {
                    // 0x00475e80
                    charge(ctx, 13);
                    lw(a0, gp, -17788);  // 0x7CE774
                    v0 = 0x960000;
                    v0 = addiu(v0, 112);  // &0x960070
                    v1 = 0x490000;
                    v1 = addiu(v1, -29808);  // &sub_488B90
                    v0 = addu(v0, a0);
                    lw(v0, v0, 0);
                    lw(v0, v0, 20);
                    sw(v0, s4, 108);
                    lw(v0, gp, -17792);  // 0x7CE770
                    v0 = addu(s4, v0);
                    lw(v0, v0, 0);
                    sw(v1, v0, 32);
                }
                goto L_00475eb4;
            }
            // 0x00475e00
            charge(ctx, 8);
            a1 = s2;
            a2 = s1;
            a0 = s4;
            jal(ctx, 0x475E08u, gen::fn_sub_47A210_0047a210);
            s1 = v0;
            v0 = 1;
            if (s1 != v0) {
                goto L_00475eb4;
            }
            // 0x00475e20
            charge(ctx, 14);
            a0 = s4;
            jal(ctx, 0x475E20u, gen::fn_sub_47BF80_0047bf80);
            lw(v1, gp, -17792);  // 0x7CE770
            v0 = 0x480000;
            v0 = addiu(v0, -28304);  // &sub_479170
            a1 = addiu(s0, 400);
            a0 = s4;
            v1 = addu(s4, v1);
            lw(v1, v1, 0);
            sw(v0, v1, 36);
            link(ctx, 0x475E48u);  // $ra first: the delay slot below depends on it
            sw(zero, v1, 56);
            call(ctx, gen::fn_sub_474F20_00474f20);
            v0 = s1;
            goto L_00475eb8;
        }
        // 0x00475f08
        charge(ctx, 7);
        a0 = 0;
        a1 = 0;
        a2 = 0;
        jal(ctx, 0x475F10u, gen::fn_sub_493710_00493710);
        s1 = v0;
        if (s1 == 0) {
            // 0x00475f54
            charge(ctx, 2);
            v0 = 0;
            goto L_00476110;
        }
        // 0x00475f24
        charge(ctx, 10);
        lw(v1, s1, 92);
        v0 = 0x3F800000;
        a0 = s1;
        sw(zero, v1, 4);
        sw(zero, v1, 8);
        sw(zero, v1, 12);
        link(ctx, 0x475F3Cu);  // $ra first: the delay slot below depends on it
        sw(v0, v1, 16);
        call(ctx, gen::fn_sub_4933D0_004933d0);
        if (v0 == 0) {
            // 0x00475f4c
            charge(ctx, 2);
            v0 = 0;
            goto L_00476110;
        }
        // 0x00475f5c
        charge(ctx, 37);
        a0 = s4;
        a1 = s1;
        a2 = 0;
        jal(ctx, 0x475F64u, gen::fn_sub_4919B0_004919b0);
        a0 = s1;
        jal(ctx, 0x475F6Cu, gen::fn_sub_493B60_00493b60);
        jal(ctx, 0x475F74u, gen::fn_sub_494BE0_00494be0);
        s2 = v0;
        a0 = addiu(s1, 32);
        a1 = s2;
        jal(ctx, 0x475F84u, gen::fn_sub_495340_00495340);
        a0 = s2;
        jal(ctx, 0x475F8Cu, gen::fn_sub_494CC0_00494cc0);
        lw(a0, gp, -17792);  // 0x7CE770
        v1 = 0x480000;
        v0 = 0x960000;
        v1 = addiu(v1, -23280);  // &sub_47A510
        v0 = addiu(v0, 112);  // &0x960070
        a0 = addu(s4, a0);
        lw(a0, a0, 0);
        sw(v1, a0, 28);
        sw(zero, a0, 36);
        sw(zero, a0, 40);
        sw(zero, a0, 44);
        sw(zero, a0, 48);
        sw(zero, a0, 52);
        sw(zero, a0, 56);
        lw(v1, gp, -17788);  // 0x7CE774
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        lw(v0, v0, 0);
        sw(v0, s4, 108);
        lw(v0, a0, 68);
        v0 = v0 & 0x8;
        if (v0 == 0) {
            // 0x00475ff8
            charge(ctx, 5);
            a1 = addiu(s0, 400);
            a0 = s4;
            jal(ctx, 0x475FFCu, gen::fn_sub_474F20_00474f20);
            backedge(ctx);
        }
        // 0x00475ff0
        charge(ctx, 2);
        s1 = 1;
        backedge(ctx);
    L_00475eb4:
        charge(ctx, 1);
        v0 = s1;
    L_00475eb8:
        charge(ctx, 2);
        ld(ra, sp, 0x60);
    }
    // 0x00476114 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// sub_478E80 [ptankSpr2dGeometryCreate] -- builds a PTank atomic's 2D-sprite geometry: an empty geometry, a material
//   (colour 0.3 / 1 / 1), a one-entry mesh header (sub_4959C0) of $a1 primitives with the material, the material pipe
//   PTank +4, the atomic's pipe PTank +8; 1 / 0
// 0x00478E80 sub_478E80 -- 432 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_478E80(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00478e80
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    a2 = 0;
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    a0 = 0;
    a1 = 0;
    link(ctx, 0x478EACu);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_493710_00493710);
    s2 = v0;
    if (s2 == 0) {
        // 0x00478ef0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x00478ec0
        charge(ctx, 10);
        lw(v1, s2, 92);
        v0 = 0x3F800000;
        a0 = s2;
        sw(zero, v1, 4);
        sw(zero, v1, 8);
        sw(zero, v1, 12);
        link(ctx, 0x478ED8u);  // $ra first: the delay slot below depends on it
        sw(v0, v1, 16);
        call(ctx, gen::fn_sub_4933D0_004933d0);
        if (v0 != 0) {
            // 0x00478ef8
            charge(ctx, 49);
            jal(ctx, 0x478EF8u, gen::fn_sub_494BE0_00494be0);
            v1 = 0x3E990000;
            s1 = v0;
            a1 = v1 | 0x999A;
            a0 = 28;
            v1 = 0x3F800000;
            sw(a1, v0, 12);
            sw(v1, v0, 16);
            sw(a1, sp, 0x60);
            sw(v1, sp, 0x68);
            sw(v1, sp, 0x64);
            link(ctx, 0x478F28u);  // $ra first: the delay slot below depends on it
            sw(v1, v0, 20);
            call(ctx, gen::fn_sub_4959C0_004959c0);
            lw(a3, gp, -17568);  // 0x7CE850
            a2 = 0x960000;
            lw(a1, v0, 0);
            a2 = addiu(a2, 112);  // &0x960070
            a0 = si(-256);
            v1 = 1;
            s0 = v0;
            a2 = addu(a2, a3);
            a0 = a1 & a0;
            lbu(a1, a2, 45);
            a0 = a0 | a1;
            sw(a0, v0, 0);
            lw(a0, v0, 0);
            a0 = a0 | 0x100;
            sw(a0, v0, 0);
            link(ctx, 0x478F6Cu);  // $ra first: the delay slot below depends on it
            sh(v1, v0, 4);
            call(ctx, gen::fn_sub_496580_00496580);
            sh(v0, s0, 6);
            v1 = 0x960000;
            sw(zero, s0, 12);
            v1 = addiu(v1, 112);  // &0x960070
            sw(zero, s0, 8);
            sw(s3, s0, 20);
            sw(zero, s0, 16);
            sw(s1, s0, 24);
            sw(s0, s2, 84);
            lw(a0, gp, -17788);  // 0x7CE774
            lw(v0, s0, 24);
            v1 = addu(v1, a0);
            lw(v1, v1, 0);
            lw(v1, v1, 4);
            sw(v1, v0, 8);
            lw(v0, s0, 24);
            if (v0 == 0) {
                // 0x0047900c
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x00478fbc
                charge(ctx, 20);
                a0 = addiu(s2, 32);
                a1 = s1;
                jal(ctx, 0x478FC0u, gen::fn_sub_495340_00495340);
                a0 = s1;
                jal(ctx, 0x478FC8u, gen::fn_sub_494CC0_00494cc0);
                a0 = s4;
                a1 = s2;
                a2 = 0;
                jal(ctx, 0x478FD8u, gen::fn_sub_4919B0_004919b0);
                lw(v1, gp, -17788);  // 0x7CE774
                v0 = 0x960000;
                v0 = addiu(v0, 112);  // &0x960070
                a0 = s2;
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                lw(v0, v0, 8);
                link(ctx, 0x478FFCu);  // $ra first: the delay slot below depends on it
                sw(v0, s4, 108);
                call(ctx, gen::fn_sub_493B60_00493b60);
                v0 = 1;
            }
        } else {
            // 0x00478ee8
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x00479010 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// sub_47A210 [ptankSpr3dGeometryCreate] -- builds a PTank atomic's 3D-sprite geometry: as the 2D one with 4 x $a1
//   indices, the material pipe PTank +12 and the atomic's pipe PTank +16; 1 / 0
// 0x0047A210 sub_47A210 -- 436 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_47A210(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0047a210
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    a2 = 0;
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    a0 = 0;
    a1 = 0;
    link(ctx, 0x47A23Cu);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_493710_00493710);
    s2 = v0;
    if (s2 == 0) {
        // 0x0047a280
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0047a250
        charge(ctx, 10);
        lw(v1, s2, 92);
        v0 = 0x3F800000;
        a0 = s2;
        sw(zero, v1, 4);
        sw(zero, v1, 8);
        sw(zero, v1, 12);
        link(ctx, 0x47A268u);  // $ra first: the delay slot below depends on it
        sw(v0, v1, 16);
        call(ctx, gen::fn_sub_4933D0_004933d0);
        if (v0 != 0) {
            // 0x0047a288
            charge(ctx, 50);
            jal(ctx, 0x47A288u, gen::fn_sub_494BE0_00494be0);
            v1 = 0x3E990000;
            s1 = v0;
            a1 = v1 | 0x999A;
            a0 = 28;
            v1 = 0x3F800000;
            sw(a1, v0, 12);
            sw(v1, v0, 16);
            sw(a1, sp, 0x60);
            sw(v1, sp, 0x68);
            sw(v1, sp, 0x64);
            link(ctx, 0x47A2B8u);  // $ra first: the delay slot below depends on it
            sw(v1, v0, 20);
            call(ctx, gen::fn_sub_4959C0_004959c0);
            lw(a3, gp, -17568);  // 0x7CE850
            a2 = 0x960000;
            lw(a1, v0, 0);
            a2 = addiu(a2, 112);  // &0x960070
            a0 = si(-256);
            v1 = 1;
            s0 = v0;
            a2 = addu(a2, a3);
            a0 = a1 & a0;
            lbu(a1, a2, 45);
            a0 = a0 | a1;
            sw(a0, v0, 0);
            lw(a0, v0, 0);
            a0 = a0 | 0x100;
            sw(a0, v0, 0);
            link(ctx, 0x47A2FCu);  // $ra first: the delay slot below depends on it
            sh(v1, v0, 4);
            call(ctx, gen::fn_sub_496580_00496580);
            sh(v0, s0, 6);
            v1 = 0x960000;
            sw(zero, s0, 12);
            v0 = sll(s3, 2);
            sw(zero, s0, 8);
            v1 = addiu(v1, 112);  // &0x960070
            sw(v0, s0, 20);
            sw(zero, s0, 16);
            sw(s1, s0, 24);
            sw(s0, s2, 84);
            lw(a0, gp, -17788);  // 0x7CE774
            lw(v0, s0, 24);
            v1 = addu(v1, a0);
            lw(v1, v1, 0);
            lw(v1, v1, 12);
            sw(v1, v0, 8);
            lw(v0, s0, 24);
            if (v0 == 0) {
                // 0x0047a3a0
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x0047a350
                charge(ctx, 20);
                a0 = addiu(s2, 32);
                a1 = s1;
                jal(ctx, 0x47A354u, gen::fn_sub_495340_00495340);
                a0 = s1;
                jal(ctx, 0x47A35Cu, gen::fn_sub_494CC0_00494cc0);
                a0 = s4;
                a1 = s2;
                a2 = 0;
                jal(ctx, 0x47A36Cu, gen::fn_sub_4919B0_004919b0);
                lw(v1, gp, -17788);  // 0x7CE774
                v0 = 0x960000;
                v0 = addiu(v0, 112);  // &0x960070
                a0 = s2;
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                lw(v0, v0, 16);
                link(ctx, 0x47A390u);  // $ra first: the delay slot below depends on it
                sw(v0, s4, 108);
                call(ctx, gen::fn_sub_493B60_00493b60);
                v0 = 1;
            }
        } else {
            // 0x0047a278
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x0047a3a4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// sub_490050 [RpWorldStreamRead] -- reads a world chunk: the struct (version 0x35000..0x37002; a world with an extra
//   count refused, error 0x80000004), one block (RwMalloc, cleared) sized for the world record, its sectors, vertices,
//   pre-lit colours, normals, UV sets and triangles by the format flags, the record (type 7, flags, root type 2, the
//   negated origin, the texture-coordinate set count, empty lists), the material list (chunk 8, sub_4954C0), the root
//   sector -- an atomic sector (chunk 9, sub_48F580) or a plane sector (chunk 10, sub_48FBD0) --, the bounding box, the
//   sectors' set-up (sub_499D30) and render callback, every sector's plugin constructors, the world's extensions
//   (sub_4C5A50 / sub_4C5C30 on 0x77DDD0) and sub_49A080; on a failure the world is destroyed (RpWorldDestroy); the
//   world, or 0
// 0x00490050 sub_490050 -- 1588 bytes; frame 0xE0: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_490050(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x00490050
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    a1 = 1;
    sd(ra, sp, 0x50);
    a2 = addiu(sp, 0xD8);
    sq(s4, sp, 0x40);
    a3 = addiu(sp, 0xD4);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s1 = a0;
    link(ctx, 0x490078u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1600_004c1600);
    if (v0 == 0) {
        // 0x004900dc
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x00490088
        charge(ctx, 6);
        lw(v1, sp, 0xD4);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x004900a0
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_004900b4;
            }
            // 0x004900e4
            charge(ctx, 11);
            a0 = addiu(sp, 0x60);
            a1 = 0;
            a2 = 64;
            jal(ctx, 0x4900ECu, gen::fn_memset_00521408);
            lw(s0, sp, 0xD8);
            a0 = s1;
            a1 = addiu(sp, 0x60);
            a2 = s0;
            jal(ctx, 0x490100u, gen::fn_sub_4C5250_004c5250);
            if (s0 != v0) {
                // 0x00490338
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x00490110
                charge(ctx, 3);
                lw(v0, sp, 0x80);
                if (i64(v0) > 0) {
                    // 0x00490340
                    charge(ctx, 10);
                    v1 = 2;
                    v0 = lui(0x8000);
                    sw(v1, sp, 0xC0);
                    a0 = v0 | 0x4;
                    jal(ctx, 0x49034Cu, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0xC4);
                    a0 = addiu(sp, 0xC0);
                    jal(ctx, 0x490358u, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                } else {
                    // 0x0049011c
                    charge(ctx, 16);
                    v0 = 0x780000;
                    lw(a1, sp, 0x78);
                    lw(a2, v0, -8752);  // 0x77DDD0
                    lw(v1, sp, 0x7C);
                    a0 = sll(a1, 1);
                    v0 = 0x780000;
                    a0 = addu(a0, a1);
                    lw(v0, v0, -8784);  // 0x77DDB0
                    a0 = sll(a0, 3);
                    a0 = addu(a2, a0);
                    mult(v1, v1, v0);
                    lw(s3, sp, 0x84);
                    v0 = 0xFF0000;
                    v0 = s3 & v0;
                    s4 = addu(a0, v1);
                    if (v0 == 0) {
                        // 0x00490164
                        charge(ctx, 3);
                        v0 = s3 & 0x80;
                        if (v0 == 0) {
                            // 0x00490178
                            charge(ctx, 2);
                            v0 = s3 & 0x4;
                            s2 = sltu(0, v0);
                        } else {
                            // 0x00490170
                            charge(ctx, 2);
                            s2 = 2;
                        }
                    } else {
                        // 0x0049015c
                        charge(ctx, 2);
                        s2 = sra(v0, 16);
                    }
                    // 0x00490180
                    charge(ctx, 4);
                    v0 = 0x1000000;
                    v0 = s3 & v0;
                    if (v0 == 0) {
                        // 0x00490190
                        charge(ctx, 7);
                        lw(a0, sp, 0x74);
                        v0 = s3 & 0x10;
                        v1 = sll(a0, 1);
                        v1 = addu(v1, a0);
                        v1 = sll(v1, 2);
                        s4 = addu(s4, v1);
                        if (v0 != 0) {
                            // 0x004901ac
                            charge(ctx, 2);
                            v0 = sll(a0, 2);
                            s4 = addu(s4, v0);
                        }
                        // 0x004901b4
                        charge(ctx, 3);
                        v0 = s3 & 0x8;
                        if (v0 != 0) {
                            // 0x004901c0
                            charge(ctx, 2);
                            v0 = sll(a0, 2);
                            s4 = addu(s4, v0);
                        }
                        // 0x004901c8
                        charge(ctx, 2);
                        if (s2 != 0) {
                            // 0x004901d0
                            charge(ctx, 3);
                            mult(v0, s2, a0);
                            v0 = sll(v0, 3);
                            s4 = addu(s4, v0);
                        }
                        // 0x004901dc
                        charge(ctx, 3);
                        lw(v0, sp, 0x70);
                        v0 = sll(v0, 3);
                        s4 = addu(s4, v0);
                    }
                    // 0x004901e8
                    charge(ctx, 9);
                    v0 = 0x30000;
                    a1 = v0 | 0xB;
                    v0 = 0x960000;
                    lw(v0, v0, 376);  // 0x960178
                    a0 = s4;
                    jalr(ctx, 0x4901F8u, v0.u());
                    s0 = v0;
                    if (s0 == 0) {
                        // 0x00490368
                        charge(ctx, 11);
                        v0 = 2;
                        a1 = s4;
                        sw(v0, sp, 0xB8);
                        v0 = lui(0x8000);
                        a0 = v0 | 0x13;
                        jal(ctx, 0x490378u, gen::fn_sub_4C1D10_004c1d10);
                        sw(v0, sp, 0xBC);
                        a0 = addiu(sp, 0xB8);
                        jal(ctx, 0x490384u, gen::fn_sub_4C1C50_004c1c50);
                        v0 = 0;
                    } else {
                        // 0x0049020c
                        charge(ctx, 52);
                        a0 = s0;
                        a1 = 0;
                        a2 = s4;
                        jal(ctx, 0x490214u, gen::fn_memset_00521408);
                        v0 = 0x780000;
                        v1 = 7;
                        lw(a2, v0, -8752);  // 0x77DDD0
                        a1 = s4;
                        a0 = s0;
                        a2 = addu(s0, a2);
                        v0 = 1;
                        sw(a2, sp, 0xDC);
                        sb(v1, s0, 0);
                        sb(zero, s0, 1);
                        sb(zero, s0, 2);
                        sb(zero, s0, 3);
                        sw(zero, s0, 4);
                        link(ctx, 0x490250u);  // $ra first: the delay slot below depends on it
                        sb(v0, s0, 3);
                        call(ctx, gen::fn_sub_499E90_00499e90);
                        sw(s3, s0, 8);
                        v0 = 2;
                        sw(v0, s0, 12);
                        t0 = addiu(s0, 44);
                        lwc1(f0, sp, 0x64);
                        v0 = lui(0xBF80);
                        mtc1(v0, f1);
                        v1 = addiu(s0, 52);
                        a0 = s1;
                        a1 = 8;
                        v0 = addiu(s0, 60);
                        a2 = 0;
                        a3 = addiu(sp, 0xD0);
                        mul_s(f0, f1, f0);
                        swc1(f0, s0, 68);
                        lwc1(f0, sp, 0x68);
                        mul_s(f0, f1, f0);
                        swc1(f0, s0, 72);
                        lwc1(f0, sp, 0x6C);
                        mul_s(f0, f1, f0);
                        swc1(f0, s0, 76);
                        sw(s2, s0, 32);
                        sw(zero, s0, 28);
                        sw(zero, s0, 108);
                        sw(t0, s0, 44);
                        sw(t0, s0, 48);
                        sw(v1, s0, 52);
                        sw(v1, s0, 56);
                        sw(v0, s0, 60);
                        link(ctx, 0x4902CCu);  // $ra first: the delay slot below depends on it
                        sw(v0, s0, 64);
                        call(ctx, gen::fn_sub_4C1600_004c1600);
                        if (v0 == 0) {
                            // 0x00490394
                            charge(ctx, 4);
                            a0 = s0;
                            jal(ctx, 0x490394u, gen::fn_sub_49A290_0049a290);
                            v0 = 0;
                        } else {
                            // 0x004902dc
                            charge(ctx, 6);
                            lw(v1, sp, 0xD0);
                            v0 = 0x30000;
                            v0 = v0 | 0x5000;
                            v0 = sltu(v1, v0);
                            if (v0 == 0) {
                                // 0x004902f4
                                charge(ctx, 5);
                                at = 0x30000;
                                at = at | 0x7003;
                                at = sltu(v1, at);
                                if (at == 0) {
                                    goto L_00490308;
                                }
                                // 0x004903a4
                                charge(ctx, 5);
                                a0 = s1;
                                a1 = addiu(s0, 16);
                                jal(ctx, 0x4903A8u, gen::fn_sub_4954C0_004954c0);
                                if (v0 == 0) {
                                    // 0x004904b4
                                    charge(ctx, 4);
                                    a0 = s0;
                                    jal(ctx, 0x4904B4u, gen::fn_sub_49A290_0049a290);
                                    v0 = 0;
                                } else {
                                    // 0x004903b8
                                    charge(ctx, 3);
                                    lw(v0, sp, 0x60);
                                    if (v0 == 0) {
                                        // 0x0049043c
                                        charge(ctx, 7);
                                        a0 = s1;
                                        a1 = 10;
                                        a2 = 0;
                                        a3 = addiu(sp, 0xD0);
                                        jal(ctx, 0x490448u, gen::fn_sub_4C1600_004c1600);
                                        if (v0 == 0) {
                                            // 0x0049060c
                                            charge(ctx, 4);
                                            a0 = s0;
                                            jal(ctx, 0x49060Cu, gen::fn_sub_49A290_0049a290);
                                            v0 = 0;
                                        } else {
                                            // 0x00490458
                                            charge(ctx, 6);
                                            lw(v1, sp, 0xD0);
                                            v0 = 0x30000;
                                            v0 = v0 | 0x5000;
                                            v0 = sltu(v1, v0);
                                            if (v0 == 0) {
                                                // 0x00490470
                                                charge(ctx, 5);
                                                at = 0x30000;
                                                at = at | 0x7003;
                                                at = sltu(v1, at);
                                                if (at == 0) {
                                                    goto L_00490484;
                                                }
                                                // 0x0049061c
                                                charge(ctx, 7);
                                                a3 = s3;
                                                a0 = s1;
                                                a1 = addiu(sp, 0xDC);
                                                a2 = s0;
                                                jal(ctx, 0x490628u, gen::fn_sub_48FBD0_0048fbd0);
                                                sw(v0, s0, 28);
                                                if (v0 != 0) {
                                                    backedge(ctx);
                                                L_00490500:
                                                    charge(ctx, 24);
                                                    sw(zero, s0, 36);
                                                    v0 = addiu(s0, 44);
                                                    sw(v0, s0, 40);
                                                    a0 = s0;
                                                    lwc1(f3, sp, 0x88);
                                                    lwc1(f2, sp, 0x8C);
                                                    lwc1(f1, sp, 0x90);
                                                    lwc1(f0, sp, 0x94);
                                                    swc1(f3, s0, 80);
                                                    swc1(f2, s0, 84);
                                                    swc1(f1, s0, 88);
                                                    swc1(f0, s0, 92);
                                                    lwc1(f1, sp, 0x98);
                                                    lwc1(f0, sp, 0x9C);
                                                    swc1(f1, s0, 96);
                                                    link(ctx, 0x49053Cu);  // $ra first: the delay slot below depends on it
                                                    swc1(f0, s0, 100);
                                                    call(ctx, gen::fn_sub_499D30_00499d30);
                                                    a0 = s0;
                                                    a1 = 0;
                                                    jal(ctx, 0x490548u, gen::fn_worldSetSectorRenderCallBack_0049a3d0);
                                                    lw(v0, s0, 20);
                                                    at = slt(0, v0);
                                                    s3 = 0;
                                                    if (at != 0) {
                                                        // 0x00490560
                                                        charge(ctx, 1);
                                                        s2 = 0;
                                                        for (;;) {
                                                            // 0x00490564
                                                            charge(ctx, 6);
                                                            lw(v0, s0, 16);
                                                            v0 = addu(v0, s2);
                                                            lw(a0, v0, 0);
                                                            lw(a1, a0, 0);
                                                            if (a1 != 0) {
                                                                // 0x0049057c
                                                                charge(ctx, 3);
                                                                jal(ctx, 0x49057Cu, gen::fn_sub_494D50_00494d50);
                                                            }
                                                            // 0x00490588
                                                            charge(ctx, 5);
                                                            lw(v0, s0, 20);
                                                            s3 = addiu(s3, 1);
                                                            v0 = slt(s3, v0);
                                                            s2 = addiu(s2, 4);
                                                            if (v0 == 0) {
                                                                break;
                                                            }
                                                            backedge(ctx);
                                                        }
                                                        // 0x0049059c
                                                        charge(ctx, 1);
                                                    }
                                                    // 0x004905a0
                                                    charge(ctx, 13);
                                                    a0 = 0x780000;
                                                    a0 = addiu(a0, -8752);  // &0x77DDD0
                                                    a1 = s0;
                                                    jal(ctx, 0x4905A8u, gen::fn_sub_4C64B0_004c64b0);
                                                    a0 = 0x780000;
                                                    a1 = s1;
                                                    a0 = addiu(a0, -8752);  // &0x77DDD0
                                                    a2 = s0;
                                                    sw(zero, gp, -17644);  // 0x7CE804
                                                    link(ctx, 0x4905C4u);  // $ra first: the delay slot below depends on it
                                                    sw(zero, gp, -17648);  // 0x7CE800
                                                    call(ctx, gen::fn_sub_4C5A50_004c5a50);
                                                    if (v0 == 0) {
                                                        // 0x00490648
                                                        charge(ctx, 4);
                                                        a0 = s0;
                                                        jal(ctx, 0x490648u, gen::fn_sub_49A290_0049a290);
                                                        v0 = 0;
                                                    } else {
                                                        // 0x004905d4
                                                        charge(ctx, 3);
                                                        lw(a1, gp, -17644);  // 0x7CE804
                                                        if (a1 != 0) {
                                                            // 0x004905e0
                                                            charge(ctx, 5);
                                                            lw(a3, gp, -17648);  // 0x7CE800
                                                            a0 = 0x780000;
                                                            a0 = addiu(a0, -8752);  // &0x77DDD0
                                                            a2 = s0;
                                                            jal(ctx, 0x4905ECu, gen::fn_sub_4C5C30_004c5c30);
                                                        }
                                                        // 0x004905f4
                                                        charge(ctx, 4);
                                                        a0 = s0;
                                                        jal(ctx, 0x4905F4u, gen::fn_sub_49A080_0049a080);
                                                        if (v0 == 0) {
                                                            // 0x00490658
                                                            charge(ctx, 3);
                                                            a0 = s0;
                                                            jal(ctx, 0x490658u, gen::fn_sub_49A290_0049a290);
                                                            v0 = 0;
                                                        } else {
                                                            // 0x00490604
                                                            charge(ctx, 2);
                                                            v0 = s0;
                                                        }
                                                    }
                                                } else {
                                                    // 0x00490638
                                                    charge(ctx, 4);
                                                    a0 = s0;
                                                    jal(ctx, 0x490638u, gen::fn_sub_49A290_0049a290);
                                                    v0 = 0;
                                                }
                                                // 0x00490664 (the shared epilogue, written out on this path)
                                                charge(ctx, 8);
                                                ld(ra, sp, 0x50);
                                                lq(s4, sp, 0x40);
                                                lq(s3, sp, 0x30);
                                                lq(s2, sp, 0x20);
                                                lq(s1, sp, 0x10);
                                                lq(s0, sp, 0x0);
                                                sp = addiu(sp, 0xE0);
                                                return;
                                            }
                                        L_00490484:
                                            charge(ctx, 12);
                                            v1 = 2;
                                            v0 = lui(0x8000);
                                            sw(v1, sp, 0xA0);
                                            a0 = v0 | 0x4;
                                            jal(ctx, 0x490490u, gen::fn_sub_4C1D10_004c1d10);
                                            sw(v0, sp, 0xA4);
                                            a0 = addiu(sp, 0xA0);
                                            jal(ctx, 0x49049Cu, gen::fn_sub_4C1C50_004c1c50);
                                            a0 = s0;
                                            jal(ctx, 0x4904A4u, gen::fn_sub_49A290_0049a290);
                                            v0 = 0;
                                        }
                                    } else {
                                        // 0x004903c4
                                        charge(ctx, 7);
                                        a0 = s1;
                                        a1 = 9;
                                        a2 = 0;
                                        a3 = addiu(sp, 0xD0);
                                        jal(ctx, 0x4903D0u, gen::fn_sub_4C1600_004c1600);
                                        if (v0 == 0) {
                                            // 0x004904c4
                                            charge(ctx, 4);
                                            a0 = s0;
                                            jal(ctx, 0x4904C4u, gen::fn_sub_49A290_0049a290);
                                            v0 = 0;
                                        } else {
                                            // 0x004903e0
                                            charge(ctx, 6);
                                            lw(v1, sp, 0xD0);
                                            v0 = 0x30000;
                                            v0 = v0 | 0x5000;
                                            v0 = sltu(v1, v0);
                                            if (v0 == 0) {
                                                // 0x004903f8
                                                charge(ctx, 5);
                                                at = 0x30000;
                                                at = at | 0x7003;
                                                at = sltu(v1, at);
                                                if (at == 0) {
                                                    goto L_0049040c;
                                                }
                                                // 0x004904d4
                                                charge(ctx, 7);
                                                a3 = s3;
                                                a0 = s1;
                                                a1 = addiu(sp, 0xDC);
                                                a2 = s0;
                                                jal(ctx, 0x4904E0u, gen::fn_sub_48F580_0048f580);
                                                sw(v0, s0, 28);
                                                if (v0 != 0) {
                                                    goto L_00490500;
                                                }
                                                // 0x004904f0
                                                charge(ctx, 4);
                                                a0 = s0;
                                                jal(ctx, 0x4904F0u, gen::fn_sub_49A290_0049a290);
                                                v0 = 0;
                                                // 0x00490664 (the shared epilogue, written out on this path)
                                                charge(ctx, 8);
                                                ld(ra, sp, 0x50);
                                                lq(s4, sp, 0x40);
                                                lq(s3, sp, 0x30);
                                                lq(s2, sp, 0x20);
                                                lq(s1, sp, 0x10);
                                                lq(s0, sp, 0x0);
                                                sp = addiu(sp, 0xE0);
                                                return;
                                            }
                                        L_0049040c:
                                            charge(ctx, 12);
                                            v1 = 2;
                                            v0 = lui(0x8000);
                                            sw(v1, sp, 0xA8);
                                            a0 = v0 | 0x4;
                                            jal(ctx, 0x490418u, gen::fn_sub_4C1D10_004c1d10);
                                            sw(v0, sp, 0xAC);
                                            a0 = addiu(sp, 0xA8);
                                            jal(ctx, 0x490424u, gen::fn_sub_4C1C50_004c1c50);
                                            a0 = s0;
                                            jal(ctx, 0x49042Cu, gen::fn_sub_49A290_0049a290);
                                            v0 = 0;
                                        }
                                    }
                                }
                                // 0x00490664 (the shared epilogue, written out on this path)
                                charge(ctx, 8);
                                ld(ra, sp, 0x50);
                                lq(s4, sp, 0x40);
                                lq(s3, sp, 0x30);
                                lq(s2, sp, 0x20);
                                lq(s1, sp, 0x10);
                                lq(s0, sp, 0x0);
                                sp = addiu(sp, 0xE0);
                                return;
                            }
                        L_00490308:
                            charge(ctx, 12);
                            v1 = 2;
                            v0 = lui(0x8000);
                            sw(v1, sp, 0xB0);
                            a0 = v0 | 0x4;
                            jal(ctx, 0x490314u, gen::fn_sub_4C1D10_004c1d10);
                            sw(v0, sp, 0xB4);
                            a0 = addiu(sp, 0xB0);
                            jal(ctx, 0x490320u, gen::fn_sub_4C1C50_004c1c50);
                            a0 = s0;
                            jal(ctx, 0x490328u, gen::fn_sub_49A290_0049a290);
                            v0 = 0;
                        }
                    }
                }
            }
            // 0x00490664 (the shared epilogue, written out on this path)
            charge(ctx, 8);
            ld(ra, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0xE0);
            return;
        }
    L_004900b4:
        charge(ctx, 10);
        v1 = 2;
        v0 = lui(0x8000);
        sw(v1, sp, 0xC8);
        a0 = v0 | 0x4;
        jal(ctx, 0x4900C0u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0xCC);
        a0 = addiu(sp, 0xC8);
        jal(ctx, 0x4900CCu, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x00490664 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xE0);
}

// sub_4908D0 [clumpCloneAtomicCB] -- RpClumpClone's per-atomic callback: the atomic cloned (sub_491B40), its frame set
//   to the clone of its frame (the frame's +160 link), added to the new clump (sub_491FF0); on a missing frame the clone
//   is destroyed and error 5 set; a failed clone clears the context's ok flag (+8); the atomic, or 0
// 0x004908D0 sub_4908D0 -- 164 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4908D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004908d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    s1 = a1;
    link(ctx, 0x4908E8u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_491B40_00491b40);
    s0 = v0;
    if (s0 == 0) {
        // 0x00490928
        charge(ctx, 3);
        sw(zero, s1, 8);
        v0 = 0;
    } else {
        // 0x004908fc
        charge(ctx, 3);
        lw(v0, s2, 4);
        if (v0 == 0) {
            // 0x00490934
            charge(ctx, 10);
            a0 = s0;
            jal(ctx, 0x490934u, gen::fn_sub_491A80_00491a80);
            v0 = 2;
            a0 = 5;
            link(ctx, 0x490944u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x48);
            call(ctx, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x4C);
            a0 = addiu(sp, 0x48);
            jal(ctx, 0x490950u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        } else {
            // 0x00490908
            charge(ctx, 8);
            lw(a1, v0, 160);
            a0 = s0;
            jal(ctx, 0x49090Cu, gen::fn_sub_492D10_00492d10);
            lw(a0, s1, 4);
            a1 = s0;
            jal(ctx, 0x490918u, gen::fn_sub_491FF0_00491ff0);
            v0 = s2;
        }
    }
    // 0x0049095c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_490980 [clumpGeometryListStreamRead] -- reads a clump's geometry list (chunk 26 body): the struct chunk (version
//   0x35000..0x37002), the count, a pointer array (RwMalloc), each geometry chunk (15) read (sub_493CB0); on any failure
//   the geometries read so far are released (sub_493B60) and the array freed; the list, or 0
// 0x00490980 sub_490980 -- 796 bytes; frame 0x70: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_490980(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00490980
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x40);
    a2 = addiu(sp, 0x68);
    sq(s3, sp, 0x30);
    a3 = addiu(sp, 0x64);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    a1 = 1;
    jal(ctx, 0x4909A8u, gen::fn_sub_4C1600_004c1600);
    if (v0 == 0) {
        // 0x00490a2c
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004909b8
        charge(ctx, 6);
        lw(v1, sp, 0x64);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x004909d0
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_00490c5c;
            }
            // 0x004909e4
            charge(ctx, 7);
            a0 = s3;
            a1 = addiu(sp, 0x6C);
            a2 = 4;
            jal(ctx, 0x4909ECu, gen::fn_sub_4C5250_004c5250);
            v1 = 4;
            if (v0 != v1) {
                // 0x00490a34
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x00490a00
                charge(ctx, 4);
                sw(zero, s0, 4);
                lw(v0, sp, 0x6C);
                if (i64(v0) <= 0) {
                    // 0x00490a10
                    charge(ctx, 1);
                    sw(zero, s0, 0);
                    goto L_00490a14;
                }
                // 0x00490a3c
                charge(ctx, 11);
                a0 = sll(v0, 2);
                v0 = 0x30000;
                a1 = v0 | 0xF;
                v0 = 0x960000;
                lw(v0, v0, 376);  // 0x960178
                jalr(ctx, 0x490A50u, v0.u());
                sw(v0, s0, 0);
                lw(v0, s0, 0);
                if (v0 != 0) {
                    backedge(ctx);
                L_00490a14:
                    charge(ctx, 4);
                    lw(v0, sp, 0x6C);
                    v0 = slt(0, v0);
                    s2 = 0;
                    if (v0 != 0) {
                        // 0x00490a98
                        charge(ctx, 1);
                        s1 = 0;
                        for (;;) {
                            // 0x00490a9c
                            charge(ctx, 7);
                            a0 = s3;
                            a1 = 15;
                            a2 = 0;
                            a3 = addiu(sp, 0x64);
                            jal(ctx, 0x490AA8u, gen::fn_sub_4C1600_004c1600);
                            if (v0 == 0) {
                                goto L_00490ab8_14;
                            }
                            // 0x00490af0
                            charge(ctx, 6);
                            lw(v1, sp, 0x64);
                            v0 = 0x30000;
                            v0 = v0 | 0x5000;
                            v0 = sltu(v1, v0);
                            if (v0 != 0) {
                                goto L_00490bf4;
                            }
                            // 0x00490b08
                            charge(ctx, 5);
                            at = 0x30000;
                            at = at | 0x7003;
                            at = sltu(v1, at);
                            if (at == 0) {
                                goto L_00490bf4;
                            }
                            // 0x00490b1c
                            charge(ctx, 6);
                            a0 = s3;
                            jal(ctx, 0x490B1Cu, gen::fn_sub_493CB0_00493cb0);
                            lw(v1, s0, 0);
                            v1 = addu(v1, s1);
                            sw(v0, v1, 0);
                            if (v0 == 0) {
                                goto L_00490b8c;
                            }
                            // 0x00490b34
                            charge(ctx, 8);
                            lw(v0, s0, 4);
                            s2 = addiu(s2, 1);
                            v0 = addiu(v0, 1);
                            sw(v0, s0, 4);
                            lw(v0, sp, 0x6C);
                            v0 = slt(s2, v0);
                            s1 = addiu(s1, 4);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x00490b54
                        charge(ctx, 2);
                        backedge(ctx);
                    }
                    // 0x00490a24
                    charge(ctx, 2);
                    v0 = s0;
                } else {
                    // 0x00490a68
                    charge(ctx, 12);
                    lw(v1, sp, 0x6C);
                    v0 = 2;
                    sw(v0, sp, 0x58);
                    v0 = lui(0x8000);
                    a0 = v0 | 0x13;
                    a1 = sll(v1, 2);
                    jal(ctx, 0x490A7Cu, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0x5C);
                    a0 = addiu(sp, 0x58);
                    jal(ctx, 0x490A88u, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                }
            }
            // 0x00490c80 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x70);
            return;
        }
    L_00490c5c:
        charge(ctx, 9);
        v1 = 2;
        v0 = lui(0x8000);
        sw(v1, sp, 0x50);
        a0 = v0 | 0x4;
        jal(ctx, 0x490C68u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x54);
        a0 = addiu(sp, 0x50);
        jal(ctx, 0x490C74u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x00490c80 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_00490ab8_14:
    charge(ctx, 4);
    lw(v0, s0, 4);
    v0 = slt(0, v0);
    s2 = 0;
    if (v0 != 0) {
        // 0x00490b5c
        charge(ctx, 1);
        s1 = 0;
        for (;;) {
            // 0x00490b60
            charge(ctx, 9);
            lw(v0, s0, 0);
            v0 = addu(v0, s1);
            link(ctx, 0x490B68u);  // $ra first: the delay slot below depends on it
            lw(a0, v0, 0);
            call(ctx, gen::fn_sub_493B60_00493b60);
            lw(v0, s0, 4);
            s2 = addiu(s2, 1);
            v0 = slt(s2, v0);
            s1 = addiu(s1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00490b84
        charge(ctx, 2);
        lw(a0, s0, 0);
        backedge(ctx);
    } else {
        // 0x00490ac8
        charge(ctx, 1);
        lw(a0, s0, 0);
    }
    // 0x00490acc
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x00490ad4
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x490ADCu, v0.u());
        sw(zero, s0, 0);
    }
    // 0x00490ae8
    charge(ctx, 2);
    v0 = 0;
    // 0x00490c80 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_00490b8c:
    charge(ctx, 4);
    lw(v0, s0, 4);
    v0 = slt(0, v0);
    s2 = 0;
    if (v0 != 0) {
        // 0x00490bc4
        charge(ctx, 1);
        s1 = 0;
        for (;;) {
            // 0x00490bc8
            charge(ctx, 9);
            lw(v0, s0, 0);
            v0 = addu(v0, s1);
            link(ctx, 0x490BD0u);  // $ra first: the delay slot below depends on it
            lw(a0, v0, 0);
            call(ctx, gen::fn_sub_493B60_00493b60);
            lw(v0, s0, 4);
            s2 = addiu(s2, 1);
            v0 = slt(s2, v0);
            s1 = addiu(s1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00490bec
        charge(ctx, 2);
        lw(a0, s0, 0);
        backedge(ctx);
    } else {
        // 0x00490b9c
        charge(ctx, 1);
        lw(a0, s0, 0);
    }
    // 0x00490ba0
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x00490ba8
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x490BB0u, v0.u());
        sw(zero, s0, 0);
    }
    // 0x00490bbc
    charge(ctx, 2);
    v0 = 0;
    // 0x00490c80 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_00490bf4:
    charge(ctx, 4);
    lw(v0, s0, 4);
    v0 = slt(0, v0);
    s2 = 0;
    if (v0 != 0) {
        // 0x00490c2c
        charge(ctx, 1);
        s1 = 0;
        for (;;) {
            // 0x00490c30
            charge(ctx, 9);
            lw(v0, s0, 0);
            v0 = addu(v0, s1);
            link(ctx, 0x490C38u);  // $ra first: the delay slot below depends on it
            lw(a0, v0, 0);
            call(ctx, gen::fn_sub_493B60_00493b60);
            lw(v0, s0, 4);
            s2 = addiu(s2, 1);
            v0 = slt(s2, v0);
            s1 = addiu(s1, 4);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00490c54
        charge(ctx, 2);
        lw(a0, s0, 0);
        backedge(ctx);
    } else {
        // 0x00490c04
        charge(ctx, 1);
        lw(a0, s0, 0);
    }
    // 0x00490c08
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x00490c10
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x490C18u, v0.u());
        sw(zero, s0, 0);
    }
    // 0x00490c24
    charge(ctx, 2);
    v0 = 0;
    // 0x00490c80 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// sub_490D90 [atomicDestroyCB] -- a per-atomic callback that destroys the atomic (sub_491A80) and returns it
// 0x00490D90 sub_490D90 -- 40 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_490D90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00490d90
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x490D9Cu, gen::fn_sub_491A80_00491a80);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_490DC0 [clumpAtomicStreamRead] -- reads one atomic chunk of a clump: the struct (frame index, geometry index,
//   flags, 16 bytes), a new atomic (sub_491880) with the flags, its frame from the frame list and its geometry from the
//   geometry list -- or a geometry chunk (15) of its own --, then its extensions (sub_4C5A50 on the atomic plugin
//   registry 0x77DCE0) and the right-to-render callback (sub_4C5C30) when one was read; the atomic, or 0 (errors
//   0x80000004 / 0x8000001A)
// 0x00490DC0 sub_490DC0 -- 828 bytes; frame 0xA0: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_490DC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00490dc0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x40);
    a3 = addiu(sp, 0x98);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    s1 = a2;
    a1 = 1;
    a2 = addiu(sp, 0x9C);
    link(ctx, 0x490DECu);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1600_004c1600);
    if (v0 == 0) {
        // 0x00490eec
        charge(ctx, 10);
        v1 = 2;
        v0 = lui(0x8000);
        sw(v1, sp, 0x90);
        a0 = v0 | 0x1A;
        jal(ctx, 0x490EF8u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x94);
        a0 = addiu(sp, 0x90);
        jal(ctx, 0x490F04u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x00490dfc
        charge(ctx, 6);
        lw(v1, sp, 0x98);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x00490e14
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_004910bc;
            }
            // 0x00490e28
            charge(ctx, 13);
            a0 = addiu(sp, 0x50);
            a1 = 0;
            a2 = 16;
            jal(ctx, 0x490E30u, gen::fn_memset_00521408);
            lw(a2, sp, 0x9C);
            a0 = s3;
            a1 = addiu(sp, 0x50);
            jal(ctx, 0x490E40u, gen::fn_sub_4C5250_004c5250);
            lw(v1, sp, 0x9C);
            v0 = v1 ^ v0;
            v0 = sltiu(v0, 1);
            if (v0 == 0) {
                // 0x00490f14
                charge(ctx, 10);
                v1 = 2;
                v0 = lui(0x8000);
                sw(v1, sp, 0x88);
                a0 = v0 | 0x1A;
                jal(ctx, 0x490F20u, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x8C);
                a0 = addiu(sp, 0x88);
                jal(ctx, 0x490F2Cu, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
            } else {
                // 0x00490e5c
                charge(ctx, 5);
                jal(ctx, 0x490E5Cu, gen::fn_sub_491880_00491880);
                s0 = v0;
                if (s0 == 0) {
                    // 0x00490f3c
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x00490e70
                    charge(ctx, 5);
                    lw(v0, sp, 0x58);
                    sb(v0, s0, 2);
                    lw(v0, s2, 4);
                    if (v0 != 0) {
                        // 0x00490f44
                        charge(ctx, 9);
                        lw(v1, sp, 0x50);
                        lw(v0, s2, 0);
                        v1 = sll(v1, 2);
                        v0 = addu(v0, v1);
                        lw(a1, v0, 0);
                        a0 = s0;
                        jal(ctx, 0x490F58u, gen::fn_sub_492D10_00492d10);
                        lw(v0, s1, 4);
                        backedge(ctx);
                    } else {
                        // 0x00490e84
                        charge(ctx, 1);
                        lw(v0, s1, 4);
                    }
                    // 0x00490e88
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x00490e90
                        charge(ctx, 8);
                        lw(v1, sp, 0x54);
                        a0 = s0;
                        lw(v0, s1, 0);
                        v1 = sll(v1, 2);
                        v0 = addu(v0, v1);
                        lw(a1, v0, 0);
                        a2 = 0;
                        jal(ctx, 0x490EA8u, gen::fn_sub_4919B0_004919b0);
                        goto L_00490eb0;
                    }
                    // 0x00490f68
                    charge(ctx, 7);
                    a0 = s3;
                    a1 = 15;
                    a2 = 0;
                    a3 = addiu(sp, 0x98);
                    jal(ctx, 0x490F74u, gen::fn_sub_4C1600_004c1600);
                    if (v0 == 0) {
                        // 0x00490fe8
                        charge(ctx, 12);
                        a0 = s0;
                        jal(ctx, 0x490FE8u, gen::fn_sub_491A80_00491a80);
                        v1 = 2;
                        v0 = lui(0x8000);
                        sw(v1, sp, 0x80);
                        a0 = v0 | 0x1A;
                        jal(ctx, 0x490FFCu, gen::fn_sub_4C1D10_004c1d10);
                        sw(v0, sp, 0x84);
                        a0 = addiu(sp, 0x80);
                        jal(ctx, 0x491008u, gen::fn_sub_4C1C50_004c1c50);
                        v0 = 0;
                    } else {
                        // 0x00490f84
                        charge(ctx, 6);
                        lw(v1, sp, 0x98);
                        v0 = 0x30000;
                        v0 = v0 | 0x5000;
                        v0 = sltu(v1, v0);
                        if (v0 == 0) {
                            // 0x00490f9c
                            charge(ctx, 5);
                            at = 0x30000;
                            at = at | 0x7003;
                            at = sltu(v1, at);
                            if (at == 0) {
                                goto L_00491048;
                            }
                            // 0x00490fb0
                            charge(ctx, 6);
                            a0 = s3;
                            jal(ctx, 0x490FB0u, gen::fn_sub_493CB0_00493cb0);
                            s1 = v0;
                            v0 = sltu(0, s1);
                            if (v0 == 0) {
                                // 0x00491018
                                charge(ctx, 12);
                                a0 = s0;
                                jal(ctx, 0x491018u, gen::fn_sub_491A80_00491a80);
                                v1 = 2;
                                v0 = lui(0x8000);
                                sw(v1, sp, 0x78);
                                a0 = v0 | 0x1A;
                                jal(ctx, 0x49102Cu, gen::fn_sub_4C1D10_004c1d10);
                                sw(v0, sp, 0x7C);
                                a0 = addiu(sp, 0x78);
                                jal(ctx, 0x491038u, gen::fn_sub_4C1C50_004c1c50);
                                v0 = 0;
                            } else {
                                // 0x00490fc8
                                charge(ctx, 8);
                                a0 = s0;
                                a1 = s1;
                                a2 = 0;
                                jal(ctx, 0x490FD0u, gen::fn_sub_4919B0_004919b0);
                                a0 = s1;
                                jal(ctx, 0x490FD8u, gen::fn_sub_493B60_00493b60);
                                backedge(ctx);
                            L_00490eb0:
                                charge(ctx, 10);
                                a0 = 0x780000;
                                a1 = s3;
                                a0 = addiu(a0, -8992);  // &0x77DCE0
                                a2 = s0;
                                sw(zero, gp, -17620);  // 0x7CE81C
                                link(ctx, 0x490EC4u);  // $ra first: the delay slot below depends on it
                                sw(zero, gp, -17624);  // 0x7CE818
                                call(ctx, gen::fn_sub_4C5A50_004c5a50);
                                v0 = sltu(0, v0);
                                if (v0 == 0) {
                                    // 0x00491078
                                    charge(ctx, 10);
                                    v1 = 2;
                                    v0 = lui(0x8000);
                                    sw(v1, sp, 0x68);
                                    a0 = v0 | 0x1A;
                                    jal(ctx, 0x491084u, gen::fn_sub_4C1D10_004c1d10);
                                    sw(v0, sp, 0x6C);
                                    a0 = addiu(sp, 0x68);
                                    jal(ctx, 0x491090u, gen::fn_sub_4C1C50_004c1c50);
                                    v0 = 0;
                                } else {
                                    // 0x00490ed8
                                    charge(ctx, 3);
                                    lw(a1, gp, -17620);  // 0x7CE81C
                                    if (a1 != 0) {
                                        // 0x004910a0
                                        charge(ctx, 7);
                                        lw(a3, gp, -17624);  // 0x7CE818
                                        a0 = 0x780000;
                                        a0 = addiu(a0, -8992);  // &0x77DCE0
                                        a2 = s0;
                                        jal(ctx, 0x4910ACu, gen::fn_sub_4C5C30_004c5c30);
                                        backedge(ctx);
                                    }
                                    // 0x00490ee4
                                    charge(ctx, 2);
                                    v0 = s0;
                                }
                            }
                            // 0x004910e0 (the shared epilogue, written out on this path)
                            charge(ctx, 7);
                            ld(ra, sp, 0x40);
                            lq(s3, sp, 0x30);
                            lq(s2, sp, 0x20);
                            lq(s1, sp, 0x10);
                            lq(s0, sp, 0x0);
                            sp = addiu(sp, 0xA0);
                            return;
                        }
                    L_00491048:
                        charge(ctx, 12);
                        a0 = s0;
                        jal(ctx, 0x491048u, gen::fn_sub_491A80_00491a80);
                        v1 = 2;
                        v0 = lui(0x8000);
                        sw(v1, sp, 0x70);
                        a0 = v0 | 0x4;
                        jal(ctx, 0x49105Cu, gen::fn_sub_4C1D10_004c1d10);
                        sw(v0, sp, 0x74);
                        a0 = addiu(sp, 0x70);
                        jal(ctx, 0x491068u, gen::fn_sub_4C1C50_004c1c50);
                        v0 = 0;
                    }
                }
            }
            // 0x004910e0 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0xA0);
            return;
        }
    L_004910bc:
        charge(ctx, 9);
        v1 = 2;
        v0 = lui(0x8000);
        sw(v1, sp, 0x60);
        a0 = v0 | 0x4;
        jal(ctx, 0x4910C8u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x64);
        a0 = addiu(sp, 0x60);
        jal(ctx, 0x4910D4u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x004910e0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// sub_491880 [RpAtomicCreate] -- creates an atomic from the atomic free list (engine + gp 0x7CE820): type 1, flags 5
//   (collision test | render), private flags 1, no frame, the default sync / render callbacks, no geometry, interpolator
//   0..0 with times 1.0, the world-sector link list empty, then the plugin constructors (sub_4C64B0 on 0x77DCE0); the
//   atomic, or 0
// 0x00491880 sub_491880 -- 304 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_491880(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00491880
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x30000;
    sq(s0, sp, 0x0);
    a1 = v0 | 0x14;
    lw(a0, gp, -17616);  // 0x7CE820
    v1 = addiu(v1, 112);  // &0x960070
    v0 = 0x960000;
    lw(v0, v0, 392);  // 0x960188
    v1 = addu(v1, a0);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4918ACu);  // $ra = the return address
    lw(a0, v1, 0);
    call_ptr(ctx, jt);
    s0 = v0;
    if (s0 == 0) {
        // 0x00491990
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004918c0
        charge(ctx, 31);
        a2 = 1;
        v1 = 0x490000;
        sb(a2, s0, rw9::atomic::kType);
        v1 = addiu(v1, 2064);  // &sub_490810
        sb(zero, s0, rw9::atomic::kSubType);
        v0 = 5;
        sb(zero, s0, rw9::atomic::kFlags);
        a0 = s0;
        sb(zero, s0, rw9::atomic::kPrivateFlags);
        a1 = 0;
        sw(zero, s0, rw9::atomic::kFrame);
        sw(v1, s0, rw9::atomic::kSync);
        sw(zero, s0, rw9::atomic::kRepEntry);
        sb(v0, s0, rw9::atomic::kFlags);
        link(ctx, 0x4918F8u);  // $ra first: the delay slot below depends on it
        sb(a2, s0, rw9::atomic::kPrivateFlags);
        call(ctx, gen::fn_sub_492D10_00492d10);
        sw(zero, s0, rw9::atomic::kGeometry);
        v1 = 0x490000;
        sw(zero, s0, rw9::atomic::kSphereRadius);
        v1 = addiu(v1, 2144);  // &AtomicDefaultRenderCallBack
        sw(zero, s0, rw9::atomic::kSphereX);
        sw(zero, s0, rw9::atomic::kSphereY);
        sw(zero, s0, rw9::atomic::kSphereZ);
        sw(zero, s0, rw9::atomic::kWorldSphereRadius);
        sw(zero, s0, rw9::atomic::kWorldSphereX);
        sw(zero, s0, rw9::atomic::kWorldSphereY);
        sw(zero, s0, rw9::atomic::kWorldSphereZ);
        sw(v1, s0, rw9::atomic::kRenderCallback);
        lw(v0, s0, rw9::atomic::kRenderCallback);
        if (v0 == 0) {
            // 0x00491998
            charge(ctx, 2);
            sw(v1, s0, rw9::atomic::kRenderCallback);
            backedge(ctx);
        }
        // 0x0049193c
        charge(ctx, 21);
        sh(zero, s0, rw9::atomic::kInterpStartMorph);
        a0 = 0x3F800000;
        sh(zero, s0, rw9::atomic::kInterpEndMorph);
        v1 = 3;
        sw(a0, s0, rw9::atomic::kInterpTime);
        v0 = addiu(s0, 100);
        sw(a0, s0, rw9::atomic::kInterpRecipTime);
        a1 = s0;
        sw(zero, s0, rw9::atomic::kInterpPosition);
        a0 = 0x780000;
        sw(v1, s0, rw9::atomic::kInterpFlags);
        a0 = addiu(a0, -8992);  // &0x77DCE0
        sw(zero, s0, rw9::atomic::kClumpPrev);
        sw(zero, s0, rw9::atomic::kClumpNext);
        sw(zero, s0, rw9::atomic::kClump);
        sw(zero, s0, rw9::atomic::kPipeline);
        sw(v0, s0, rw9::atomic::kSectorsNext);
        link(ctx, 0x491980u);  // $ra first: the delay slot below depends on it
        sw(v0, s0, rw9::atomic::kSectorsPrev);
        call(ctx, gen::fn_sub_4C64B0_004c64b0);
        v0 = s0;
    }
    // 0x004919a0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4919B0 [RpAtomicSetGeometry] -- sets an atomic's geometry: the new one referenced (sub_493B40), the old one
//   released (sub_493B60); unless flag 1 of $a2 the bounding sphere copied from the geometry's first morph target and,
//   with a frame, the atomic re-synced (sub_49C230 / sub_4CB270); the atomic
// 0x004919B0 sub_4919B0 -- 196 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4919B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x004919b0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = a2;
    lw(v0, a0, 24);
    s0 = a0;
    if (s2 != v0) {
        // 0x004919d8
        charge(ctx, 2);
        if (s2 != 0) {
            // 0x004919e0
            charge(ctx, 2);
            a0 = s2;
            jal(ctx, 0x4919E0u, gen::fn_sub_493B40_00493b40);
        }
        // 0x004919e8
        charge(ctx, 3);
        lw(a0, s0, rw9::atomic::kGeometry);
        if (a0 != 0) {
            // 0x004919f4
            charge(ctx, 2);
            jal(ctx, 0x4919F4u, gen::fn_sub_493B60_00493b60);
        }
        // 0x004919fc
        charge(ctx, 3);
        v0 = s1 & 0x1;
        sw(s2, s0, rw9::atomic::kGeometry);
        if (v0 == 0) {
            // 0x00491a08
            charge(ctx, 2);
            if (s2 != 0) {
                // 0x00491a10
                charge(ctx, 9);
                lw(v0, s2, rw9::geometry::kMorphTargets);
                lwc1(f3, v0, 4);
                lwc1(f2, v0, 8);
                lwc1(f1, v0, 12);
                lwc1(f0, v0, 16);
                swc1(f3, s0, rw9::atomic::kSphereX);
                swc1(f2, s0, rw9::atomic::kSphereY);
                swc1(f1, s0, rw9::atomic::kSphereZ);
                swc1(f0, s0, rw9::atomic::kSphereRadius);
            }
            // 0x00491a34
            charge(ctx, 3);
            lw(s1, s0, rw9::atomic::kFrame);
            if (s1 != 0) {
                // 0x00491a40
                charge(ctx, 4);
                a0 = s0;
                jal(ctx, 0x491A40u, gen::fn_sub_49C230_0049c230);
                if (v0 != 0) {
                    // 0x00491a50
                    charge(ctx, 2);
                    a0 = s1;
                    jal(ctx, 0x491A50u, gen::fn_sub_4CB270_004cb270);
                }
            }
        }
    }
    // 0x00491a58 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_491B40 [RpAtomicClone] -- clones an atomic: a new atomic (sub_491880) with the type, flags, the geometry
//   (referenced) and its bounding sphere, the render callback, the interpolator, the pipeline, then the plugin copy
//   constructors (sub_4C65D0 on 0x77DCE0); the clone, or 0
// 0x00491B40 sub_491B40 -- 372 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_491B40(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x00491b40
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s1 = a0;
    link(ctx, 0x491B54u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_491880_00491880);
    s0 = v0;
    if (s0 == 0) {
        // 0x00491c98
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00491b68
        charge(ctx, 18);
        lbu(v0, s1, rw9::atomic::kType);
        a0 = s0;
        a1 = 0;
        sb(v0, s0, rw9::atomic::kType);
        lbu(v0, s1, rw9::atomic::kSubType);
        sb(v0, s0, rw9::atomic::kSubType);
        lbu(v0, s1, rw9::atomic::kFlags);
        sb(v0, s0, rw9::atomic::kFlags);
        lbu(v0, s1, rw9::atomic::kPrivateFlags);
        sb(v0, s0, rw9::atomic::kPrivateFlags);
        sw(zero, s0, rw9::atomic::kFrame);
        lbu(v0, s1, rw9::atomic::kFlags);
        link(ctx, 0x491B98u);  // $ra first: the delay slot below depends on it
        sb(v0, s0, rw9::atomic::kFlags);
        call(ctx, gen::fn_sub_492D10_00492d10);
        lw(s2, s1, rw9::atomic::kGeometry);
        lw(v0, s0, rw9::atomic::kGeometry);
        if (s2 != v0) {
            // 0x00491bb0
            charge(ctx, 2);
            if (s2 != 0) {
                // 0x00491bb8
                charge(ctx, 2);
                a0 = s2;
                jal(ctx, 0x491BB8u, gen::fn_sub_493B40_00493b40);
            }
            // 0x00491bc0
            charge(ctx, 3);
            lw(a0, s0, rw9::atomic::kGeometry);
            if (a0 != 0) {
                // 0x00491bcc
                charge(ctx, 2);
                jal(ctx, 0x491BCCu, gen::fn_sub_493B60_00493b60);
            }
            // 0x00491bd4
            charge(ctx, 2);
            sw(s2, s0, rw9::atomic::kGeometry);
            if (s2 != 0) {
                // 0x00491bdc
                charge(ctx, 9);
                lw(v0, s2, 92);
                lwc1(f3, v0, 4);
                lwc1(f2, v0, 8);
                lwc1(f1, v0, 12);
                lwc1(f0, v0, 16);
                swc1(f3, s0, rw9::atomic::kSphereX);
                swc1(f2, s0, rw9::atomic::kSphereY);
                swc1(f1, s0, rw9::atomic::kSphereZ);
                swc1(f0, s0, rw9::atomic::kSphereRadius);
            }
            // 0x00491c00
            charge(ctx, 3);
            lw(s2, s0, rw9::atomic::kFrame);
            if (s2 != 0) {
                // 0x00491c0c
                charge(ctx, 4);
                a0 = s0;
                jal(ctx, 0x491C0Cu, gen::fn_sub_49C230_0049c230);
                if (v0 != 0) {
                    // 0x00491c1c
                    charge(ctx, 2);
                    a0 = s2;
                    jal(ctx, 0x491C1Cu, gen::fn_sub_4CB270_004cb270);
                }
            }
        }
        // 0x00491c24
        charge(ctx, 29);
        lwc1(f3, s1, rw9::atomic::kSphereX);
        a0 = 0x780000;
        lwc1(f2, s1, rw9::atomic::kSphereY);
        a0 = addiu(a0, -8992);  // &0x77DCE0
        lwc1(f1, s1, rw9::atomic::kSphereZ);
        a1 = s0;
        lwc1(f0, s1, rw9::atomic::kSphereRadius);
        a2 = s1;
        swc1(f3, s0, rw9::atomic::kSphereX);
        swc1(f2, s0, rw9::atomic::kSphereY);
        swc1(f1, s0, rw9::atomic::kSphereZ);
        swc1(f0, s0, rw9::atomic::kSphereRadius);
        lw(v0, s1, rw9::atomic::kRenderCallback);
        sw(v0, s0, rw9::atomic::kRenderCallback);
        lw(v0, s1, rw9::atomic::kPipeline);
        sw(v0, s0, rw9::atomic::kPipeline);
        lwc1(f3, s1, rw9::atomic::kInterpFlags);
        lwc1(f2, s1, rw9::atomic::kInterpStartMorph);
        lwc1(f1, s1, rw9::atomic::kInterpTime);
        lwc1(f0, s1, rw9::atomic::kInterpRecipTime);
        swc1(f3, s0, rw9::atomic::kInterpFlags);
        swc1(f2, s0, rw9::atomic::kInterpStartMorph);
        swc1(f1, s0, rw9::atomic::kInterpTime);
        swc1(f0, s0, rw9::atomic::kInterpRecipTime);
        lwc1(f0, s1, rw9::atomic::kInterpPosition);
        link(ctx, 0x491C88u);  // $ra first: the delay slot below depends on it
        swc1(f0, s0, rw9::atomic::kInterpPosition);
        call(ctx, gen::fn_sub_4C65D0_004c65d0);
        v0 = s0;
    }
    // 0x00491c9c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_491CC0 [RpClumpClone] -- clones a clump: a new clump (sub_491DE0), its frame hierarchy cloned (sub_4CACE0), every
//   atomic cloned onto the new frames (sub_4908D0 over the atomic list), the frame clone links cleared (sub_4CAD30), the
//   callback (+40) and the plugin copy constructors (sub_4C65D0 on 0x77DD00); the clone, or 0 (destroyed on a failure)
// 0x00491CC0 sub_491CC0 -- 276 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_491CC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00491cc0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = addiu(sp, 0x54);
    link(ctx, 0x491CDCu);  // $ra first: the delay slot below depends on it
    sw(a0, sp, 0x50);
    call(ctx, gen::fn_sub_491DE0_00491de0);
    sw(v0, s1, 0);
    if (v0 != 0) {
        // 0x00491cf4
        charge(ctx, 9);
        lw(v0, sp, 0x50);
        link(ctx, 0x491CF8u);  // $ra first: the delay slot below depends on it
        lw(a0, v0, 4);
        call(ctx, gen::fn_sub_4CACE0_004cace0);
        lw(v1, s1, 0);
        sw(v0, v1, 4);
        lw(a0, s1, 0);
        lw(v0, a0, 4);
        if (v0 == 0) {
            // 0x00491d80
            charge(ctx, 4);
            jal(ctx, 0x491D80u, gen::fn_sub_491EA0_00491ea0);
            v0 = 0;
        } else {
            // 0x00491d18
            charge(ctx, 8);
            s0 = addiu(sp, 0x58);
            v0 = 1;
            sw(v0, s0, 0);
            lw(v0, sp, 0x50);
            s3 = addiu(v0, 8);
            lw(v0, v0, 8);
            if (v0 != s3) {
                for (;;) {
                    // 0x00491d38
                    charge(ctx, 6);
                    lw(s2, v0, 0);
                    a0 = addiu(v0, -64);
                    a1 = addiu(sp, 0x50);
                    jal(ctx, 0x491D40u, gen::fn_sub_4908D0_004908d0);
                    if (v0 != 0) {
                        // 0x00491d50
                        charge(ctx, 2);
                        v0 = s2;
                        if (s2 != s3) {
                            backedge(ctx);
                            continue;
                        }
                    }
                    break;
                }
            }
            // 0x00491d58
            charge(ctx, 6);
            lw(v0, sp, 0x50);
            link(ctx, 0x491D5Cu);  // $ra first: the delay slot below depends on it
            lw(a0, v0, 4);
            call(ctx, gen::fn_sub_4CAD30_004cad30);
            lw(v0, s0, 0);
            if (v0 != 0) {
                // 0x00491d90
                charge(ctx, 10);
                lw(v1, sp, 0x50);
                a0 = 0x780000;
                lw(v0, s1, 0);
                lw(v1, v1, 40);
                sw(v1, v0, 40);
                lw(a1, s1, 0);
                lw(a2, sp, 0x50);
                a0 = addiu(a0, -8960);  // &0x77DD00
                jal(ctx, 0x491DACu, gen::fn_sub_4C65D0_004c65d0);
                lw(v0, s1, 0);
            } else {
                // 0x00491d70
                charge(ctx, 4);
                link(ctx, 0x491D70u);  // $ra first: the delay slot below depends on it
                lw(a0, s1, 0);
                call(ctx, gen::fn_sub_491EA0_00491ea0);
                v0 = 0;
            }
        }
    } else {
        // 0x00491cec
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x00491db8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4920A0 [RpClumpStreamRead] -- reads a clump chunk: the struct (version 0x35000..0x37002; atomic, light and camera
//   counts), a new clump (sub_491DE0), the frame list (chunk 14, sub_4C7D80) whose first frame becomes the clump's, the
//   geometry list (chunk 26, sub_490980), each atomic (chunk 20, sub_490DC0) linked into the clump, each light (chunk 18
//   after its frame index, sub_494580) and camera (chunk 5, sub_4C7B90) given its frame and linked, the geometry list
//   released, the frame list freed (sub_4C7D30), the clump's extensions (sub_4C5A50 on 0x77DD00); on any failure the
//   clump is torn down (plugin destructors, its atomics / lights / cameras destroyed, the frame hierarchy destroyed,
//   freed) and error 0x8000001A set; the clump, or 0
// 0x004920A0 sub_4920A0 -- 2948 bytes; frame 0x100: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4920A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004920a0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    a1 = 1;
    sd(ra, sp, 0x60);
    a2 = addiu(sp, 0xFC);
    sq(s5, sp, 0x50);
    a3 = addiu(sp, 0xF8);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    link(ctx, 0x4920CCu);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1600_004c1600);
    if (v0 == 0) {
        // 0x004922c8
        charge(ctx, 10);
        v1 = 2;
        v0 = lui(0x8000);
        sw(v1, sp, 0xE0);
        a0 = v0 | 0x1A;
        jal(ctx, 0x4922D4u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0xE4);
        a0 = addiu(sp, 0xE0);
        jal(ctx, 0x4922E0u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x004920dc
        charge(ctx, 6);
        lw(v1, sp, 0xF8);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x004920f4
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_00492bdc;
            }
            // 0x00492108
            charge(ctx, 8);
            a0 = s4;
            a1 = addiu(sp, 0xD0);
            a2 = 12;
            jal(ctx, 0x492110u, gen::fn_sub_4C5250_004c5250);
            v0 = v0 ^ 0xC;
            v0 = sltiu(v0, 1);
            if (v0 == 0) {
                // 0x004922f0
                charge(ctx, 10);
                v1 = 2;
                v0 = lui(0x8000);
                sw(v1, sp, 0xB8);
                a0 = v0 | 0x1A;
                jal(ctx, 0x4922FCu, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0xBC);
                a0 = addiu(sp, 0xB8);
                jal(ctx, 0x492308u, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
            } else {
                // 0x00492128
                charge(ctx, 5);
                jal(ctx, 0x492128u, gen::fn_sub_491DE0_00491de0);
                s3 = v0;
                if (s3 == 0) {
                    // 0x00492318
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x0049213c
                    charge(ctx, 7);
                    a0 = s4;
                    a1 = 14;
                    a2 = 0;
                    a3 = addiu(sp, 0xF4);
                    jal(ctx, 0x492148u, gen::fn_sub_4C1600_004c1600);
                    if (v0 != 0) {
                        // 0x00492204
                        charge(ctx, 6);
                        a0 = s4;
                        a1 = addiu(sp, 0xC8);
                        jal(ctx, 0x492208u, gen::fn_sub_4C7D80_004c7d80);
                        v0 = sltu(0, v0);
                        if (v0 != 0) {
                            // 0x00492320
                            charge(ctx, 10);
                            lw(v0, sp, 0xC8);
                            a0 = s4;
                            a1 = 26;
                            a2 = 0;
                            a3 = addiu(sp, 0xF4);
                            lw(v0, v0, 0);
                            link(ctx, 0x492338u);  // $ra first: the delay slot below depends on it
                            sw(v0, s3, 4);
                            call(ctx, gen::fn_sub_4C1600_004c1600);
                            if (v0 != 0) {
                                // 0x004923fc
                                charge(ctx, 6);
                                a0 = s4;
                                a1 = addiu(sp, 0xC0);
                                jal(ctx, 0x492400u, gen::fn_sub_490980_00490980);
                                v0 = sltu(0, v0);
                                if (v0 == 0) {
                                    // 0x004924b0
                                    charge(ctx, 24);
                                    a0 = addiu(sp, 0xC8);
                                    jal(ctx, 0x4924B0u, gen::fn_sub_4C7D30_004c7d30);
                                    a0 = 0x780000;
                                    a1 = s3;
                                    a0 = addiu(a0, -8960);  // &0x77DD00
                                    jal(ctx, 0x4924C0u, gen::fn_sub_4C6560_004c6560);
                                    a1 = 0x490000;
                                    a0 = s3;
                                    a1 = addiu(a1, 3472);  // &sub_490D90
                                    a2 = 0;
                                    jal(ctx, 0x4924D4u, gen::fn_sub_4916D0_004916d0);
                                    a1 = 0x490000;
                                    a0 = s3;
                                    a1 = addiu(a1, 3328);  // &sub_490D00
                                    a2 = 0;
                                    jal(ctx, 0x4924E8u, gen::fn_sub_4917F0_004917f0);
                                    a1 = 0x490000;
                                    a0 = s3;
                                    a1 = addiu(a1, 3392);  // &sub_490D40
                                    a2 = 0;
                                    jal(ctx, 0x4924FCu, gen::fn_sub_491760_00491760);
                                    lw(a0, s3, 4);
                                    if (a0 != 0) {
                                        // 0x00492510
                                        charge(ctx, 2);
                                        jal(ctx, 0x492510u, gen::fn_sub_4CB1B0_004cb1b0);
                                    }
                                    // 0x00492518
                                    charge(ctx, 19);
                                    lw(a0, gp, -17616);  // 0x7CE820
                                    v1 = 0x960000;
                                    v1 = addiu(v1, 112);  // &0x960070
                                    v0 = 0x960000;
                                    lw(v0, v0, 396);  // 0x96018C
                                    v1 = addu(v1, a0);
                                    lw(a0, v1, 4);
                                    a1 = s3;
                                    jalr(ctx, 0x492534u, v0.u());
                                    v1 = 2;
                                    v0 = lui(0x8000);
                                    sw(v1, sp, 0x98);
                                    a0 = v0 | 0x1A;
                                    jal(ctx, 0x492548u, gen::fn_sub_4C1D10_004c1d10);
                                    sw(v0, sp, 0x9C);
                                    a0 = addiu(sp, 0x98);
                                    jal(ctx, 0x492554u, gen::fn_sub_4C1C50_004c1c50);
                                    v0 = 0;
                                } else {
                                    // 0x00492414
                                    charge(ctx, 4);
                                    lw(v0, sp, 0xD0);
                                    v0 = slt(0, v0);
                                    s5 = 0;
                                    if (v0 != 0) {
                                        for (;;) {
                                            // 0x00492564
                                            charge(ctx, 7);
                                            a0 = s4;
                                            a1 = 20;
                                            a2 = 0;
                                            a3 = addiu(sp, 0xF8);
                                            jal(ctx, 0x492570u, gen::fn_sub_4C1600_004c1600);
                                            if (v0 != 0) {
                                                // 0x004925c8
                                                charge(ctx, 7);
                                                a0 = s4;
                                                a1 = addiu(sp, 0xC8);
                                                a2 = addiu(sp, 0xC0);
                                                jal(ctx, 0x4925D0u, gen::fn_sub_490DC0_00490dc0);
                                                s2 = v0;
                                                v0 = sltu(0, s2);
                                                backedge(ctx);
                                            }
                                            // 0x00492580
                                            charge(ctx, 2);
                                            if (v0 == 0) {
                                                break;
                                            }
                                            // 0x00492588
                                            charge(ctx, 14);
                                            lw(a0, s3, 8);
                                            v0 = addiu(s3, 8);
                                            v1 = addiu(s2, 64);
                                            s5 = addiu(s5, 1);
                                            sw(a0, s2, 64);
                                            sw(v0, s2, 68);
                                            lw(v0, s3, 8);
                                            sw(v1, v0, 4);
                                            sw(v1, s3, 8);
                                            sw(s3, s2, 60);
                                            lw(v0, sp, 0xD0);
                                            v0 = slt(s5, v0);
                                            if (v0 == 0) {
                                                goto L_004925c0_39;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x004925e8
                                        charge(ctx, 5);
                                        s0 = addiu(sp, 0xC4);
                                        lw(v0, s0, 0);
                                        v0 = slt(0, v0);
                                        s2 = 0;
                                        if (v0 != 0) {
                                            // 0x004926d0
                                            charge(ctx, 1);
                                            s1 = 0;
                                            for (;;) {
                                                // 0x004926d4
                                                charge(ctx, 9);
                                                lw(v0, sp, 0xC0);
                                                v0 = addu(v0, s1);
                                                link(ctx, 0x4926DCu);  // $ra first: the delay slot below depends on it
                                                lw(a0, v0, 0);
                                                call(ctx, gen::fn_sub_493B60_00493b60);
                                                lw(v0, s0, 0);
                                                s2 = addiu(s2, 1);
                                                v0 = slt(s2, v0);
                                                s1 = addiu(s1, 4);
                                                if (v0 == 0) {
                                                    break;
                                                }
                                                backedge(ctx);
                                            }
                                            // 0x004926f8
                                            charge(ctx, 2);
                                            lw(a0, sp, 0xC0);
                                            backedge(ctx);
                                        } else {
                                            // 0x004925fc
                                            charge(ctx, 1);
                                            lw(a0, sp, 0xC0);
                                        }
                                        // 0x00492600
                                        charge(ctx, 2);
                                        if (a0 != 0) {
                                            // 0x00492608
                                            charge(ctx, 5);
                                            v0 = 0x960000;
                                            lw(v0, v0, 380);  // 0x96017C
                                            jalr(ctx, 0x492610u, v0.u());
                                            sw(zero, sp, 0xC0);
                                        }
                                        // 0x0049261c
                                        charge(ctx, 24);
                                        a0 = addiu(sp, 0xC8);
                                        jal(ctx, 0x49261Cu, gen::fn_sub_4C7D30_004c7d30);
                                        a0 = 0x780000;
                                        a1 = s3;
                                        a0 = addiu(a0, -8960);  // &0x77DD00
                                        jal(ctx, 0x49262Cu, gen::fn_sub_4C6560_004c6560);
                                        a1 = 0x490000;
                                        a0 = s3;
                                        a1 = addiu(a1, 3472);  // &sub_490D90
                                        a2 = 0;
                                        jal(ctx, 0x492640u, gen::fn_sub_4916D0_004916d0);
                                        a1 = 0x490000;
                                        a0 = s3;
                                        a1 = addiu(a1, 3328);  // &sub_490D00
                                        a2 = 0;
                                        jal(ctx, 0x492654u, gen::fn_sub_4917F0_004917f0);
                                        a1 = 0x490000;
                                        a0 = s3;
                                        a1 = addiu(a1, 3392);  // &sub_490D40
                                        a2 = 0;
                                        jal(ctx, 0x492668u, gen::fn_sub_491760_00491760);
                                        lw(a0, s3, 4);
                                        if (a0 != 0) {
                                            // 0x0049267c
                                            charge(ctx, 2);
                                            jal(ctx, 0x49267Cu, gen::fn_sub_4CB1B0_004cb1b0);
                                        }
                                        // 0x00492684
                                        charge(ctx, 19);
                                        lw(a0, gp, -17616);  // 0x7CE820
                                        v1 = 0x960000;
                                        v1 = addiu(v1, 112);  // &0x960070
                                        v0 = 0x960000;
                                        lw(v0, v0, 396);  // 0x96018C
                                        v1 = addu(v1, a0);
                                        lw(a0, v1, 4);
                                        a1 = s3;
                                        jalr(ctx, 0x4926A0u, v0.u());
                                        v1 = 2;
                                        v0 = lui(0x8000);
                                        sw(v1, sp, 0x90);
                                        a0 = v0 | 0x1A;
                                        jal(ctx, 0x4926B4u, gen::fn_sub_4C1D10_004c1d10);
                                        sw(v0, sp, 0x94);
                                        a0 = addiu(sp, 0x90);
                                        jal(ctx, 0x4926C0u, gen::fn_sub_4C1C50_004c1c50);
                                        v0 = 0;
                                    } else {
                                        // 0x00492424
                                        charge(ctx, 1);
                                        s5 = addiu(sp, 0xD4);
                                    L_00492428:
                                        charge(ctx, 4);
                                        lw(v0, s5, 0);
                                        v0 = slt(0, v0);
                                        s2 = 0;
                                        if (v0 != 0) {
                                            for (;;) {
                                                // 0x00492700
                                                charge(ctx, 8);
                                                a0 = s4;
                                                a1 = 1;
                                                a2 = 0;
                                                a3 = 0;
                                                jal(ctx, 0x49270Cu, gen::fn_sub_4C1600_004c1600);
                                                v0 = sltu(0, v0);
                                                if (v0 != 0) {
                                                    // 0x00492720
                                                    charge(ctx, 5);
                                                    a0 = s4;
                                                    a1 = addiu(sp, 0xF0);
                                                    a2 = 4;
                                                    jal(ctx, 0x492728u, gen::fn_sub_4C1910_004c1910);
                                                    v0 = sltu(0, v0);
                                                }
                                                // 0x00492734
                                                charge(ctx, 2);
                                                if (v0 != 0) {
                                                    // 0x004927b4
                                                    charge(ctx, 7);
                                                    a0 = s4;
                                                    a1 = 18;
                                                    a2 = 0;
                                                    a3 = 0;
                                                    jal(ctx, 0x4927C0u, gen::fn_sub_4C1600_004c1600);
                                                    backedge(ctx);
                                                } else {
                                                    // 0x0049273c
                                                    charge(ctx, 1);
                                                }
                                                // 0x00492740
                                                charge(ctx, 2);
                                                if (v0 != 0) {
                                                    // 0x004927d0
                                                    charge(ctx, 5);
                                                    a0 = s4;
                                                    jal(ctx, 0x4927D0u, gen::fn_sub_494580_00494580);
                                                    s1 = v0;
                                                    v0 = sltu(0, s1);
                                                    backedge(ctx);
                                                }
                                                // 0x00492748
                                                charge(ctx, 2);
                                                if (v0 == 0) {
                                                    break;
                                                }
                                                // 0x00492750
                                                charge(ctx, 23);
                                                lw(v1, sp, 0xF0);
                                                lw(v0, sp, 0xC8);
                                                v1 = sll(v1, 2);
                                                v0 = addu(v0, v1);
                                                lw(a1, v0, 0);
                                                a0 = s1;
                                                jal(ctx, 0x492764u, gen::fn_sub_4D1840_004d1840);
                                                lw(a0, gp, -17628);  // 0x7CE814
                                                v0 = addiu(s3, 16);
                                                lw(v1, s3, 16);
                                                s2 = addiu(s2, 1);
                                                a0 = addu(s1, a0);
                                                sw(v1, a0, 4);
                                                sw(v0, a0, 8);
                                                v1 = addiu(a0, 4);
                                                lw(v0, s3, 16);
                                                sw(v1, v0, 4);
                                                sw(v1, s3, 16);
                                                sw(s3, a0, 0);
                                                lw(v0, s5, 0);
                                                v0 = slt(s2, v0);
                                                if (v0 == 0) {
                                                    goto L_004927ac_58;
                                                }
                                                backedge(ctx);
                                            }
                                            // 0x004927e8
                                            charge(ctx, 5);
                                            s0 = addiu(sp, 0xC4);
                                            lw(v0, s0, 0);
                                            v0 = slt(0, v0);
                                            s2 = 0;
                                            if (v0 != 0) {
                                                // 0x004928d0
                                                charge(ctx, 1);
                                                s1 = 0;
                                                for (;;) {
                                                    // 0x004928d4
                                                    charge(ctx, 9);
                                                    lw(v0, sp, 0xC0);
                                                    v0 = addu(v0, s1);
                                                    link(ctx, 0x4928DCu);  // $ra first: the delay slot below depends on it
                                                    lw(a0, v0, 0);
                                                    call(ctx, gen::fn_sub_493B60_00493b60);
                                                    lw(v0, s0, 0);
                                                    s2 = addiu(s2, 1);
                                                    v0 = slt(s2, v0);
                                                    s1 = addiu(s1, 4);
                                                    if (v0 == 0) {
                                                        break;
                                                    }
                                                    backedge(ctx);
                                                }
                                                // 0x004928f8
                                                charge(ctx, 2);
                                                lw(a0, sp, 0xC0);
                                                backedge(ctx);
                                            } else {
                                                // 0x004927fc
                                                charge(ctx, 1);
                                                lw(a0, sp, 0xC0);
                                            }
                                            // 0x00492800
                                            charge(ctx, 2);
                                            if (a0 != 0) {
                                                // 0x00492808
                                                charge(ctx, 5);
                                                v0 = 0x960000;
                                                lw(v0, v0, 380);  // 0x96017C
                                                jalr(ctx, 0x492810u, v0.u());
                                                sw(zero, sp, 0xC0);
                                            }
                                            // 0x0049281c
                                            charge(ctx, 24);
                                            a0 = addiu(sp, 0xC8);
                                            jal(ctx, 0x49281Cu, gen::fn_sub_4C7D30_004c7d30);
                                            a0 = 0x780000;
                                            a1 = s3;
                                            a0 = addiu(a0, -8960);  // &0x77DD00
                                            jal(ctx, 0x49282Cu, gen::fn_sub_4C6560_004c6560);
                                            a1 = 0x490000;
                                            a0 = s3;
                                            a1 = addiu(a1, 3472);  // &sub_490D90
                                            a2 = 0;
                                            jal(ctx, 0x492840u, gen::fn_sub_4916D0_004916d0);
                                            a1 = 0x490000;
                                            a0 = s3;
                                            a1 = addiu(a1, 3328);  // &sub_490D00
                                            a2 = 0;
                                            jal(ctx, 0x492854u, gen::fn_sub_4917F0_004917f0);
                                            a1 = 0x490000;
                                            a0 = s3;
                                            a1 = addiu(a1, 3392);  // &sub_490D40
                                            a2 = 0;
                                            jal(ctx, 0x492868u, gen::fn_sub_491760_00491760);
                                            lw(a0, s3, 4);
                                            if (a0 != 0) {
                                                // 0x0049287c
                                                charge(ctx, 2);
                                                jal(ctx, 0x49287Cu, gen::fn_sub_4CB1B0_004cb1b0);
                                            }
                                            // 0x00492884
                                            charge(ctx, 19);
                                            lw(a0, gp, -17616);  // 0x7CE820
                                            v1 = 0x960000;
                                            v1 = addiu(v1, 112);  // &0x960070
                                            v0 = 0x960000;
                                            lw(v0, v0, 396);  // 0x96018C
                                            v1 = addu(v1, a0);
                                            lw(a0, v1, 4);
                                            a1 = s3;
                                            jalr(ctx, 0x4928A0u, v0.u());
                                            v1 = 2;
                                            v0 = lui(0x8000);
                                            sw(v1, sp, 0x88);
                                            a0 = v0 | 0x1A;
                                            jal(ctx, 0x4928B4u, gen::fn_sub_4C1D10_004c1d10);
                                            sw(v0, sp, 0x8C);
                                            a0 = addiu(sp, 0x88);
                                            jal(ctx, 0x4928C0u, gen::fn_sub_4C1C50_004c1c50);
                                            v0 = 0;
                                        } else {
                                            // 0x00492438
                                            charge(ctx, 1);
                                            s1 = addiu(sp, 0xD8);
                                        L_0049243c:
                                            charge(ctx, 4);
                                            lw(v0, s1, 0);
                                            v0 = slt(0, v0);
                                            s2 = 0;
                                            if (v0 != 0) {
                                                for (;;) {
                                                    // 0x00492900
                                                    charge(ctx, 8);
                                                    a0 = s4;
                                                    a1 = 1;
                                                    a2 = 0;
                                                    a3 = 0;
                                                    jal(ctx, 0x49290Cu, gen::fn_sub_4C1600_004c1600);
                                                    v0 = sltu(0, v0);
                                                    if (v0 != 0) {
                                                        // 0x00492920
                                                        charge(ctx, 5);
                                                        a0 = s4;
                                                        a1 = addiu(sp, 0xEC);
                                                        a2 = 4;
                                                        jal(ctx, 0x492928u, gen::fn_sub_4C1910_004c1910);
                                                        v0 = sltu(0, v0);
                                                    }
                                                    // 0x00492934
                                                    charge(ctx, 2);
                                                    if (v0 != 0) {
                                                        // 0x004929b4
                                                        charge(ctx, 7);
                                                        a0 = s4;
                                                        a1 = 5;
                                                        a2 = 0;
                                                        a3 = 0;
                                                        jal(ctx, 0x4929C0u, gen::fn_sub_4C1600_004c1600);
                                                        backedge(ctx);
                                                    } else {
                                                        // 0x0049293c
                                                        charge(ctx, 1);
                                                    }
                                                    // 0x00492940
                                                    charge(ctx, 2);
                                                    if (v0 != 0) {
                                                        // 0x004929d0
                                                        charge(ctx, 5);
                                                        a0 = s4;
                                                        jal(ctx, 0x4929D0u, gen::fn_sub_4C7B90_004c7b90);
                                                        s0 = v0;
                                                        v0 = sltu(0, s0);
                                                        backedge(ctx);
                                                    }
                                                    // 0x00492948
                                                    charge(ctx, 2);
                                                    if (v0 == 0) {
                                                        break;
                                                    }
                                                    // 0x00492950
                                                    charge(ctx, 23);
                                                    lw(v1, sp, 0xEC);
                                                    lw(v0, sp, 0xC8);
                                                    v1 = sll(v1, 2);
                                                    v0 = addu(v0, v1);
                                                    lw(a1, v0, 0);
                                                    a0 = s0;
                                                    jal(ctx, 0x492964u, gen::fn_sub_4D1840_004d1840);
                                                    lw(a0, gp, -17632);  // 0x7CE810
                                                    v0 = addiu(s3, 24);
                                                    lw(v1, s3, 24);
                                                    s2 = addiu(s2, 1);
                                                    a0 = addu(s0, a0);
                                                    sw(v1, a0, 4);
                                                    sw(v0, a0, 8);
                                                    v1 = addiu(a0, 4);
                                                    lw(v0, s3, 24);
                                                    sw(v1, v0, 4);
                                                    sw(v1, s3, 24);
                                                    sw(s3, a0, 0);
                                                    lw(v0, s1, 0);
                                                    v0 = slt(s2, v0);
                                                    if (v0 == 0) {
                                                        goto L_004929ac_78;
                                                    }
                                                    backedge(ctx);
                                                }
                                                // 0x004929e8
                                                charge(ctx, 5);
                                                s0 = addiu(sp, 0xC4);
                                                lw(v0, s0, 0);
                                                v0 = slt(0, v0);
                                                s2 = 0;
                                                if (v0 != 0) {
                                                    // 0x00492ad0
                                                    charge(ctx, 1);
                                                    s1 = 0;
                                                    for (;;) {
                                                        // 0x00492ad4
                                                        charge(ctx, 9);
                                                        lw(v0, sp, 0xC0);
                                                        v0 = addu(v0, s1);
                                                        link(ctx, 0x492ADCu);  // $ra first: the delay slot below depends on it
                                                        lw(a0, v0, 0);
                                                        call(ctx, gen::fn_sub_493B60_00493b60);
                                                        lw(v0, s0, 0);
                                                        s2 = addiu(s2, 1);
                                                        v0 = slt(s2, v0);
                                                        s1 = addiu(s1, 4);
                                                        if (v0 == 0) {
                                                            break;
                                                        }
                                                        backedge(ctx);
                                                    }
                                                    // 0x00492af8
                                                    charge(ctx, 2);
                                                    lw(a0, sp, 0xC0);
                                                    backedge(ctx);
                                                } else {
                                                    // 0x004929fc
                                                    charge(ctx, 1);
                                                    lw(a0, sp, 0xC0);
                                                }
                                                // 0x00492a00
                                                charge(ctx, 2);
                                                if (a0 != 0) {
                                                    // 0x00492a08
                                                    charge(ctx, 5);
                                                    v0 = 0x960000;
                                                    lw(v0, v0, 380);  // 0x96017C
                                                    jalr(ctx, 0x492A10u, v0.u());
                                                    sw(zero, sp, 0xC0);
                                                }
                                                // 0x00492a1c
                                                charge(ctx, 24);
                                                a0 = addiu(sp, 0xC8);
                                                jal(ctx, 0x492A1Cu, gen::fn_sub_4C7D30_004c7d30);
                                                a0 = 0x780000;
                                                a1 = s3;
                                                a0 = addiu(a0, -8960);  // &0x77DD00
                                                jal(ctx, 0x492A2Cu, gen::fn_sub_4C6560_004c6560);
                                                a1 = 0x490000;
                                                a0 = s3;
                                                a1 = addiu(a1, 3472);  // &sub_490D90
                                                a2 = 0;
                                                jal(ctx, 0x492A40u, gen::fn_sub_4916D0_004916d0);
                                                a1 = 0x490000;
                                                a0 = s3;
                                                a1 = addiu(a1, 3328);  // &sub_490D00
                                                a2 = 0;
                                                jal(ctx, 0x492A54u, gen::fn_sub_4917F0_004917f0);
                                                a1 = 0x490000;
                                                a0 = s3;
                                                a1 = addiu(a1, 3392);  // &sub_490D40
                                                a2 = 0;
                                                jal(ctx, 0x492A68u, gen::fn_sub_491760_00491760);
                                                lw(a0, s3, 4);
                                                if (a0 != 0) {
                                                    // 0x00492a7c
                                                    charge(ctx, 2);
                                                    jal(ctx, 0x492A7Cu, gen::fn_sub_4CB1B0_004cb1b0);
                                                }
                                                // 0x00492a84
                                                charge(ctx, 19);
                                                lw(a0, gp, -17616);  // 0x7CE820
                                                v1 = 0x960000;
                                                v1 = addiu(v1, 112);  // &0x960070
                                                v0 = 0x960000;
                                                lw(v0, v0, 396);  // 0x96018C
                                                v1 = addu(v1, a0);
                                                lw(a0, v1, 4);
                                                a1 = s3;
                                                jalr(ctx, 0x492AA0u, v0.u());
                                                v1 = 2;
                                                v0 = lui(0x8000);
                                                sw(v1, sp, 0x80);
                                                a0 = v0 | 0x1A;
                                                jal(ctx, 0x492AB4u, gen::fn_sub_4C1D10_004c1d10);
                                                sw(v0, sp, 0x84);
                                                a0 = addiu(sp, 0x80);
                                                jal(ctx, 0x492AC0u, gen::fn_sub_4C1C50_004c1c50);
                                                v0 = 0;
                                            } else {
                                                // 0x0049244c
                                                charge(ctx, 1);
                                                s0 = addiu(sp, 0xC4);
                                            L_00492450:
                                                charge(ctx, 4);
                                                lw(v0, s0, 0);
                                                v0 = slt(0, v0);
                                                s2 = 0;
                                                if (v0 != 0) {
                                                    // 0x00492b00
                                                    charge(ctx, 1);
                                                    s1 = 0;
                                                    for (;;) {
                                                        // 0x00492b04
                                                        charge(ctx, 9);
                                                        lw(v0, sp, 0xC0);
                                                        v0 = addu(v0, s1);
                                                        link(ctx, 0x492B0Cu);  // $ra first: the delay slot below depends on it
                                                        lw(a0, v0, 0);
                                                        call(ctx, gen::fn_sub_493B60_00493b60);
                                                        lw(v0, s0, 0);
                                                        s2 = addiu(s2, 1);
                                                        v0 = slt(s2, v0);
                                                        s1 = addiu(s1, 4);
                                                        if (v0 == 0) {
                                                            break;
                                                        }
                                                        backedge(ctx);
                                                    }
                                                    // 0x00492b28
                                                    charge(ctx, 2);
                                                    lw(a0, sp, 0xC0);
                                                    backedge(ctx);
                                                } else {
                                                    // 0x00492460
                                                    charge(ctx, 1);
                                                    lw(a0, sp, 0xC0);
                                                }
                                                // 0x00492464
                                                charge(ctx, 2);
                                                if (a0 != 0) {
                                                    // 0x0049246c
                                                    charge(ctx, 5);
                                                    v0 = 0x960000;
                                                    lw(v0, v0, 380);  // 0x96017C
                                                    jalr(ctx, 0x492474u, v0.u());
                                                    sw(zero, sp, 0xC0);
                                                }
                                                // 0x00492480
                                                charge(ctx, 10);
                                                a0 = addiu(sp, 0xC8);
                                                jal(ctx, 0x492480u, gen::fn_sub_4C7D30_004c7d30);
                                                a0 = 0x780000;
                                                a1 = s4;
                                                a0 = addiu(a0, -8960);  // &0x77DD00
                                                a2 = s3;
                                                jal(ctx, 0x492494u, gen::fn_sub_4C5A50_004c5a50);
                                                v0 = sltu(0, v0);
                                                if (v0 == 0) {
                                                    // 0x00492b30
                                                    charge(ctx, 22);
                                                    a0 = 0x780000;
                                                    a1 = s3;
                                                    a0 = addiu(a0, -8960);  // &0x77DD00
                                                    jal(ctx, 0x492B38u, gen::fn_sub_4C6560_004c6560);
                                                    a1 = 0x490000;
                                                    a0 = s3;
                                                    a1 = addiu(a1, 3472);  // &sub_490D90
                                                    a2 = 0;
                                                    jal(ctx, 0x492B4Cu, gen::fn_sub_4916D0_004916d0);
                                                    a1 = 0x490000;
                                                    a0 = s3;
                                                    a1 = addiu(a1, 3328);  // &sub_490D00
                                                    a2 = 0;
                                                    jal(ctx, 0x492B60u, gen::fn_sub_4917F0_004917f0);
                                                    a1 = 0x490000;
                                                    a0 = s3;
                                                    a1 = addiu(a1, 3392);  // &sub_490D40
                                                    a2 = 0;
                                                    jal(ctx, 0x492B74u, gen::fn_sub_491760_00491760);
                                                    lw(a0, s3, 4);
                                                    if (a0 != 0) {
                                                        // 0x00492b88
                                                        charge(ctx, 2);
                                                        jal(ctx, 0x492B88u, gen::fn_sub_4CB1B0_004cb1b0);
                                                    }
                                                    // 0x00492b90
                                                    charge(ctx, 19);
                                                    lw(a0, gp, -17616);  // 0x7CE820
                                                    v1 = 0x960000;
                                                    v1 = addiu(v1, 112);  // &0x960070
                                                    v0 = 0x960000;
                                                    lw(v0, v0, 396);  // 0x96018C
                                                    v1 = addu(v1, a0);
                                                    lw(a0, v1, 4);
                                                    a1 = s3;
                                                    jalr(ctx, 0x492BACu, v0.u());
                                                    v1 = 2;
                                                    v0 = lui(0x8000);
                                                    sw(v1, sp, 0x78);
                                                    a0 = v0 | 0x1A;
                                                    jal(ctx, 0x492BC0u, gen::fn_sub_4C1D10_004c1d10);
                                                    sw(v0, sp, 0x7C);
                                                    a0 = addiu(sp, 0x78);
                                                    jal(ctx, 0x492BCCu, gen::fn_sub_4C1C50_004c1c50);
                                                    v0 = 0;
                                                } else {
                                                    // 0x004924a8
                                                    charge(ctx, 2);
                                                    v0 = s3;
                                                }
                                            }
                                        }
                                    }
                                }
                            } else {
                                // 0x00492348
                                charge(ctx, 24);
                                a0 = addiu(sp, 0xC8);
                                jal(ctx, 0x492348u, gen::fn_sub_4C7D30_004c7d30);
                                a0 = 0x780000;
                                a1 = s3;
                                a0 = addiu(a0, -8960);  // &0x77DD00
                                jal(ctx, 0x492358u, gen::fn_sub_4C6560_004c6560);
                                a1 = 0x490000;
                                a0 = s3;
                                a1 = addiu(a1, 3472);  // &sub_490D90
                                a2 = 0;
                                jal(ctx, 0x49236Cu, gen::fn_sub_4916D0_004916d0);
                                a1 = 0x490000;
                                a0 = s3;
                                a1 = addiu(a1, 3328);  // &sub_490D00
                                a2 = 0;
                                jal(ctx, 0x492380u, gen::fn_sub_4917F0_004917f0);
                                a1 = 0x490000;
                                a0 = s3;
                                a1 = addiu(a1, 3392);  // &sub_490D40
                                a2 = 0;
                                jal(ctx, 0x492394u, gen::fn_sub_491760_00491760);
                                lw(a0, s3, 4);
                                if (a0 != 0) {
                                    // 0x004923a8
                                    charge(ctx, 2);
                                    jal(ctx, 0x4923A8u, gen::fn_sub_4CB1B0_004cb1b0);
                                }
                                // 0x004923b0
                                charge(ctx, 19);
                                lw(a0, gp, -17616);  // 0x7CE820
                                v1 = 0x960000;
                                v1 = addiu(v1, 112);  // &0x960070
                                v0 = 0x960000;
                                lw(v0, v0, 396);  // 0x96018C
                                v1 = addu(v1, a0);
                                lw(a0, v1, 4);
                                a1 = s3;
                                jalr(ctx, 0x4923CCu, v0.u());
                                v1 = 2;
                                v0 = lui(0x8000);
                                sw(v1, sp, 0xA0);
                                a0 = v0 | 0x1A;
                                jal(ctx, 0x4923E0u, gen::fn_sub_4C1D10_004c1d10);
                                sw(v0, sp, 0xA4);
                                a0 = addiu(sp, 0xA0);
                                jal(ctx, 0x4923ECu, gen::fn_sub_4C1C50_004c1c50);
                                v0 = 0;
                            }
                        } else {
                            // 0x0049221c
                            charge(ctx, 22);
                            a0 = 0x780000;
                            a1 = s3;
                            a0 = addiu(a0, -8960);  // &0x77DD00
                            jal(ctx, 0x492224u, gen::fn_sub_4C6560_004c6560);
                            a1 = 0x490000;
                            a0 = s3;
                            a1 = addiu(a1, 3472);  // &sub_490D90
                            a2 = 0;
                            jal(ctx, 0x492238u, gen::fn_sub_4916D0_004916d0);
                            a1 = 0x490000;
                            a0 = s3;
                            a1 = addiu(a1, 3328);  // &sub_490D00
                            a2 = 0;
                            jal(ctx, 0x49224Cu, gen::fn_sub_4917F0_004917f0);
                            a1 = 0x490000;
                            a0 = s3;
                            a1 = addiu(a1, 3392);  // &sub_490D40
                            a2 = 0;
                            jal(ctx, 0x492260u, gen::fn_sub_491760_00491760);
                            lw(a0, s3, 4);
                            if (a0 != 0) {
                                // 0x00492274
                                charge(ctx, 2);
                                jal(ctx, 0x492274u, gen::fn_sub_4CB1B0_004cb1b0);
                            }
                            // 0x0049227c
                            charge(ctx, 19);
                            lw(a0, gp, -17616);  // 0x7CE820
                            v1 = 0x960000;
                            v1 = addiu(v1, 112);  // &0x960070
                            v0 = 0x960000;
                            lw(v0, v0, 396);  // 0x96018C
                            v1 = addu(v1, a0);
                            lw(a0, v1, 4);
                            a1 = s3;
                            jalr(ctx, 0x492298u, v0.u());
                            v1 = 2;
                            v0 = lui(0x8000);
                            sw(v1, sp, 0xA8);
                            a0 = v0 | 0x1A;
                            jal(ctx, 0x4922ACu, gen::fn_sub_4C1D10_004c1d10);
                            sw(v0, sp, 0xAC);
                            a0 = addiu(sp, 0xA8);
                            jal(ctx, 0x4922B8u, gen::fn_sub_4C1C50_004c1c50);
                            v0 = 0;
                        }
                    } else {
                        // 0x00492158
                        charge(ctx, 22);
                        a0 = 0x780000;
                        a1 = s3;
                        a0 = addiu(a0, -8960);  // &0x77DD00
                        jal(ctx, 0x492160u, gen::fn_sub_4C6560_004c6560);
                        a1 = 0x490000;
                        a0 = s3;
                        a1 = addiu(a1, 3472);  // &sub_490D90
                        a2 = 0;
                        jal(ctx, 0x492174u, gen::fn_sub_4916D0_004916d0);
                        a1 = 0x490000;
                        a0 = s3;
                        a1 = addiu(a1, 3328);  // &sub_490D00
                        a2 = 0;
                        jal(ctx, 0x492188u, gen::fn_sub_4917F0_004917f0);
                        a1 = 0x490000;
                        a0 = s3;
                        a1 = addiu(a1, 3392);  // &sub_490D40
                        a2 = 0;
                        jal(ctx, 0x49219Cu, gen::fn_sub_491760_00491760);
                        lw(a0, s3, 4);
                        if (a0 != 0) {
                            // 0x004921b0
                            charge(ctx, 2);
                            jal(ctx, 0x4921B0u, gen::fn_sub_4CB1B0_004cb1b0);
                        }
                        // 0x004921b8
                        charge(ctx, 19);
                        lw(a0, gp, -17616);  // 0x7CE820
                        v1 = 0x960000;
                        v1 = addiu(v1, 112);  // &0x960070
                        v0 = 0x960000;
                        lw(v0, v0, 396);  // 0x96018C
                        v1 = addu(v1, a0);
                        lw(a0, v1, 4);
                        a1 = s3;
                        jalr(ctx, 0x4921D4u, v0.u());
                        v1 = 2;
                        v0 = lui(0x8000);
                        sw(v1, sp, 0xB0);
                        a0 = v0 | 0x1A;
                        jal(ctx, 0x4921E8u, gen::fn_sub_4C1D10_004c1d10);
                        sw(v0, sp, 0xB4);
                        a0 = addiu(sp, 0xB0);
                        jal(ctx, 0x4921F4u, gen::fn_sub_4C1C50_004c1c50);
                        v0 = 0;
                    }
                }
            }
            // 0x00492c00 (the shared epilogue, written out on this path)
            charge(ctx, 9);
            ld(ra, sp, 0x60);
            lq(s5, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x100);
            return;
        }
    L_00492bdc:
        charge(ctx, 9);
        v1 = 2;
        v0 = lui(0x8000);
        sw(v1, sp, 0x70);
        a0 = v0 | 0x4;
        jal(ctx, 0x492BE8u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x74);
        a0 = addiu(sp, 0x70);
        jal(ctx, 0x492BF4u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x00492c00 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x100);
    return;
L_004925c0_39:
    charge(ctx, 2);
    s5 = addiu(sp, 0xD4);
    backedge(ctx);
    goto L_00492428;
L_004927ac_58:
    charge(ctx, 2);
    s1 = addiu(sp, 0xD8);
    backedge(ctx);
    goto L_0049243c;
L_004929ac_78:
    charge(ctx, 2);
    s0 = addiu(sp, 0xC4);
    backedge(ctx);
    goto L_00492450;
}

// sub_492D50 [geometryFree] -- frees a geometry (reference count about to reach 0): the count held up, its instance
//   data unlocked (geometryLock 0x493370), the plugin destructors (sub_4C6560 on 0x77DD20), the morph-target block (+92)
//   and the mesh header (+32, sub_495260) freed, the geometry freed; 1
// 0x00492D50 sub_492D50 -- 140 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_492D50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00492d50
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 4095;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lh(v0, a0, 14);
    s0 = a0;
    v0 = addiu(v0, 1);
    link(ctx, 0x492D6Cu);  // $ra first: the delay slot below depends on it
    sh(v0, a0, 14);
    call(ctx, gen::fn_geometryLock_00493370);
    a0 = 0x780000;
    a1 = s0;
    a0 = addiu(a0, -8928);  // &0x77DD20
    jal(ctx, 0x492D7Cu, gen::fn_sub_4C6560_004c6560);
    lw(a0, s0, rw9::geometry::kMorphTargets);
    if (a0 != 0) {
        // 0x00492d90
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x492D98u, v0.u());
        sw(zero, s0, rw9::geometry::kMorphTargets);
    }
    // 0x00492da4
    charge(ctx, 14);
    a0 = addiu(s0, 32);
    jal(ctx, 0x492DA4u, gen::fn_sub_495260_00495260);
    lh(v1, s0, rw9::geometry::kRefCount);
    v0 = 0x960000;
    v1 = addiu(v1, -1);
    sh(v1, s0, rw9::geometry::kRefCount);
    lw(v0, v0, 380);  // 0x96017C
    a0 = s0;
    jalr(ctx, 0x492DC0u, v0.u());
    ld(ra, sp, 0x10);
    v0 = 1;
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_493710 [RpGeometryCreate] -- creates a geometry of $a0 vertices and $a1 triangles with format flags $a2: refused
//   above 65535 vertices (error 6) or below 0 triangles; the number of texture-coordinate sets from the flags (bits
//   16..23, else 2 for 0x80, 1 for 0x04), one block (RwMalloc) sized for the pre-lit colours, the UV sets and the
//   triangles unless native (0x01000000), the mesh header (sub_495300), type 8, reference count 1, the arrays laid out
//   after the plugin-extended record (the registry size; triangle material indices -1), one morph target (sub_492F80),
//   the plugin constructors (sub_4C64B0 on 0x77DD20); the geometry, or 0
// 0x00493710 sub_493710 -- 1072 bytes; frame 0x90: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_493710(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00493710
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (i64(s5) >= 0) {
        // 0x00493744
        charge(ctx, 4);
        at = 0x10000;
        at = slt(s5, at);
        if (at == 0) {
            goto L_00493844;
        }
        // 0x00493754
        charge(ctx, 2);
        if (i64(s4) < 0) {
            goto L_00493844;
        }
        // 0x0049375c
        charge(ctx, 6);
        v0 = 0x780000;
        lw(a0, v0, -8928);  // 0x77DD20
        v0 = 0xFF0000;
        v0 = s3 & v0;
        a2 = s3 & 0xFF;
        if (v0 == 0) {
            // 0x0049377c
            charge(ctx, 3);
            v0 = s3 & 0x80;
            if (v0 == 0) {
                // 0x00493790
                charge(ctx, 2);
                v0 = s3 & 0x4;
                s1 = sltu(0, v0);
            } else {
                // 0x00493788
                charge(ctx, 2);
                s1 = 2;
            }
        } else {
            // 0x00493774
            charge(ctx, 2);
            s1 = srl(v0, 16);
        }
        // 0x00493798
        charge(ctx, 3);
        v0 = 1;
        if (s1 != v0) {
            // 0x004937ac
            charge(ctx, 3);
            at = sltiu(s1, 2);
            if (at != 0) {
                // 0x004937c0
                charge(ctx, 1);
                a1 = 0;
            } else {
                // 0x004937b8
                charge(ctx, 2);
                a1 = 128;
            }
        } else {
            // 0x004937a4
            charge(ctx, 2);
            a1 = 4;
        }
        // 0x004937c4
        charge(ctx, 6);
        v1 = si(-133);
        v0 = 0x1000000;
        v1 = a2 & v1;
        s6 = s3 & v0;
        s0 = v1 | a1;
        if (s6 == 0) {
            // 0x004937dc
            charge(ctx, 3);
            v0 = s0 & 0x8;
            if (v0 != 0) {
                // 0x004937e8
                charge(ctx, 2);
                v0 = sll(s5, 2);
                a0 = addu(a0, v0);
            }
            // 0x004937f0
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x004937f8
                charge(ctx, 3);
                v0 = sll(s5, 3);
                mult(v0, s1, v0);
                a0 = addu(a0, v0);
            }
            // 0x00493804
            charge(ctx, 2);
            v0 = sll(s4, 3);
            a0 = addu(a0, v0);
        }
        // 0x0049380c
        charge(ctx, 8);
        v0 = 0x960000;
        v1 = 0x30000;
        lw(v0, v0, 376);  // 0x960178
        a1 = v1 | 0xF;
        jalr(ctx, 0x493818u, v0.u());
        s2 = v0;
        if (s2 == 0) {
            // 0x00493880
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x0049382c
            charge(ctx, 4);
            a0 = addiu(s2, 32);
            jal(ctx, 0x49382Cu, gen::fn_sub_495300_00495300);
            if (v0 != 0) {
                // 0x00493888
                charge(ctx, 27);
                sw(zero, s2, rw9::geometry::kMorphTargets);
                v1 = 8;
                sw(zero, s2, rw9::geometry::kNumMorphTargets);
                v0 = 1;
                sb(v1, s2, rw9::geometry::kType);
                a0 = addiu(s2, 52);
                sb(zero, s2, rw9::geometry::kSubType);
                a1 = 0;
                sb(zero, s2, rw9::geometry::kObjFlags);
                a2 = 32;
                sb(zero, s2, rw9::geometry::kPrivateFlags);
                sw(zero, s2, rw9::geometry::kParent);
                sw(zero, s2, rw9::geometry::kRepEntry);
                sh(zero, s2, rw9::geometry::kLockedSinceInst);
                sh(v0, s2, rw9::geometry::kRefCount);
                sw(zero, s2, rw9::geometry::kMesh);
                link(ctx, 0x4938C8u);  // $ra first: the delay slot below depends on it
                sw(s1, s2, rw9::geometry::kNumTexCoordSets);
                call(ctx, gen::fn_memset_00521408);
                sw(zero, s2, rw9::geometry::kPreLit);
                v0 = 0xF000000;
                v0 = s3 & v0;
                sw(zero, s2, rw9::geometry::kTriangles);
                v0 = s0 | v0;
                sw(s4, s2, rw9::geometry::kNumTriangles);
                sw(v0, s2, rw9::geometry::kFlags);
                sw(s5, s2, rw9::geometry::kNumVertices);
                if (s6 == 0) {
                    // 0x004938f4
                    charge(ctx, 5);
                    v0 = 0x780000;
                    v1 = s0 & 0x8;
                    lw(v0, v0, -8928);  // 0x77DD20
                    a3 = addu(s2, v0);
                    if (v1 != 0) {
                        // 0x00493908
                        charge(ctx, 2);
                        if (s5 != 0) {
                            // 0x00493910
                            charge(ctx, 3);
                            sw(a3, s2, rw9::geometry::kPreLit);
                            v0 = sll(s5, 2);
                            a3 = addu(a3, v0);
                        }
                    }
                    // 0x0049391c
                    charge(ctx, 2);
                    if (s1 != 0) {
                        // 0x00493924
                        charge(ctx, 2);
                        if (s5 != 0) {
                            // 0x0049392c
                            charge(ctx, 3);
                            at = sltu(0, s1);
                            a2 = 0;
                            if (at != 0) {
                                // 0x00493938
                                charge(ctx, 3);
                                at = sltiu(s1, 9);
                                a0 = addiu(s1, -8);
                                if (at == 0) {
                                    // 0x00493944
                                    charge(ctx, 2);
                                    a1 = s2;
                                    v1 = sll(s5, 3);
                                    for (;;) {
                                        // 0x0049394c
                                        charge(ctx, 20);
                                        sw(a3, a1, 52);
                                        v0 = addu(a3, v1);
                                        sw(v0, a1, 56);
                                        a2 = addiu(a2, 8);
                                        v0 = addu(v0, v1);
                                        sw(v0, a1, 60);
                                        v0 = addu(v0, v1);
                                        sw(v0, a1, 64);
                                        v0 = addu(v0, v1);
                                        sw(v0, a1, 68);
                                        v0 = addu(v0, v1);
                                        sw(v0, a1, 72);
                                        v0 = addu(v0, v1);
                                        sw(v0, a1, 76);
                                        v0 = addu(v0, v1);
                                        sw(v0, a1, 80);
                                        a3 = addu(v0, v1);
                                        v0 = sltu(a2, a0);
                                        a1 = addiu(a1, 32);
                                        if (v0 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x0049399c
                                    charge(ctx, 1);
                                }
                                // 0x004939a0
                                charge(ctx, 3);
                                at = sltu(a2, s1);
                                if (at != 0) {
                                    // 0x004939ac
                                    charge(ctx, 3);
                                    v0 = sll(a2, 2);
                                    v1 = sll(s5, 3);
                                    a0 = addu(s2, v0);
                                    for (;;) {
                                        // 0x004939b8
                                        charge(ctx, 7);
                                        a2 = addiu(a2, 1);
                                        sw(a3, a0, 52);
                                        v0 = sltu(a2, s1);
                                        a3 = addu(a3, v1);
                                        a0 = addiu(a0, 4);
                                        if (v0 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004939d4
                                    charge(ctx, 1);
                                }
                            }
                        }
                    }
                    // 0x004939d8
                    charge(ctx, 2);
                    if (s4 != 0) {
                        // 0x004939e0
                        charge(ctx, 4);
                        at = slt(0, s4);
                        sw(a3, s2, rw9::geometry::kTriangles);
                        v0 = 0;
                        if (at != 0) {
                            // 0x004939f0
                            charge(ctx, 3);
                            at = slti(s4, 9);
                            a2 = addiu(s4, -8);
                            if (at == 0) {
                                // 0x004939fc
                                charge(ctx, 3);
                                at = slt(s4, 0);
                                v1 = 0;
                                if (at == 0) {
                                    // 0x00493a08
                                    charge(ctx, 5);
                                    at = 0x7FFF0000;
                                    at = at | 0xFFFF;
                                    at = slt(s4, at);
                                    if (at != 0) {
                                        // 0x00493a1c
                                        charge(ctx, 1);
                                        v1 = 1;
                                    }
                                }
                                // 0x00493a20
                                charge(ctx, 2);
                                if (v1 != 0) {
                                    // 0x00493a28
                                    charge(ctx, 2);
                                    a3 = 0;
                                    a1 = 0xFFFF;
                                    for (;;) {
                                        // 0x00493a30
                                        charge(ctx, 28);
                                        lw(a0, s2, rw9::geometry::kTriangles);
                                        v0 = addiu(v0, 8);
                                        v1 = slt(v0, a2);
                                        a0 = addu(a0, a3);
                                        sh(a1, a0, 6);
                                        lw(a0, s2, rw9::geometry::kTriangles);
                                        a0 = addu(a0, a3);
                                        sh(a1, a0, 14);
                                        lw(a0, s2, rw9::geometry::kTriangles);
                                        a0 = addu(a0, a3);
                                        sh(a1, a0, 22);
                                        lw(a0, s2, rw9::geometry::kTriangles);
                                        a0 = addu(a0, a3);
                                        sh(a1, a0, 30);
                                        lw(a0, s2, rw9::geometry::kTriangles);
                                        a0 = addu(a0, a3);
                                        sh(a1, a0, 38);
                                        lw(a0, s2, rw9::geometry::kTriangles);
                                        a0 = addu(a0, a3);
                                        sh(a1, a0, 46);
                                        lw(a0, s2, rw9::geometry::kTriangles);
                                        a0 = addu(a0, a3);
                                        sh(a1, a0, 54);
                                        lw(a0, s2, rw9::geometry::kTriangles);
                                        a0 = addu(a0, a3);
                                        sh(a1, a0, 62);
                                        a3 = addiu(a3, 64);
                                        if (v1 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                }
                            }
                            // 0x00493aa0
                            charge(ctx, 3);
                            at = slt(v0, s4);
                            if (at != 0) {
                                // 0x00493aac
                                charge(ctx, 2);
                                a2 = sll(v0, 3);
                                a1 = 0xFFFF;
                                for (;;) {
                                    // 0x00493ab4
                                    charge(ctx, 7);
                                    lw(a0, s2, rw9::geometry::kTriangles);
                                    v0 = addiu(v0, 1);
                                    v1 = slt(v0, s4);
                                    a0 = addu(a0, a2);
                                    sh(a1, a0, 6);
                                    a2 = addiu(a2, 8);
                                    if (v1 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                            }
                        }
                    }
                }
                // 0x00493ad0
                charge(ctx, 5);
                a0 = s2;
                a1 = 1;
                jal(ctx, 0x493AD4u, gen::fn_sub_492F80_00492f80);
                if (i64(v0) < 0) {
                    // 0x00493afc
                    charge(ctx, 7);
                    a0 = addiu(s2, 32);
                    jal(ctx, 0x493AFCu, gen::fn_sub_495260_00495260);
                    v0 = 0x960000;
                    lw(v0, v0, 380);  // 0x96017C
                    a0 = s2;
                    jalr(ctx, 0x493B0Cu, v0.u());
                    v0 = 0;
                } else {
                    // 0x00493ae4
                    charge(ctx, 6);
                    a0 = 0x780000;
                    a1 = s2;
                    a0 = addiu(a0, -8928);  // &0x77DD20
                    jal(ctx, 0x493AECu, gen::fn_sub_4C64B0_004c64b0);
                    v0 = s2;
                }
            } else {
                // 0x0049383c
                charge(ctx, 2);
                v0 = 0;
            }
        }
        // 0x00493b18 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(ra, sp, 0x70);
        lq(s6, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x90);
        return;
    }
L_00493844:
    charge(ctx, 2);
    if (i64(s5) >= 0) {
        // 0x0049384c
        charge(ctx, 4);
        v0 = 0x10000;
        v0 = slt(s5, v0);
        if (v0 == 0) {
            // 0x0049385c
            charge(ctx, 7);
            v0 = 2;
            a0 = 6;
            link(ctx, 0x493864u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0x88);
            call(ctx, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x8C);
            a0 = addiu(sp, 0x88);
            jal(ctx, 0x493870u, gen::fn_sub_4C1C50_004c1c50);
        }
    }
    // 0x00493878
    charge(ctx, 2);
    v0 = 0;
    // 0x00493b18 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// sub_493B60 [RpGeometryDestroy] -- releases a geometry: the reference count (+14) down; at the last reference the
//   instance data unlocked (sub_4C47E0), the mesh (+84, sub_495C80), the plugin destructors (sub_4C6560 on 0x77DD20), the
//   morph targets and mesh header freed and the geometry freed; 1
// 0x00493B60 sub_493B60 -- 236 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_493B60(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00493b60
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 1;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lh(v1, a0, 14);
    v1 = addiu(v1, -1);
    s0 = a0;
    if (i64(v1) <= 0) {
        // 0x00493b94
        charge(ctx, 3);
        lw(a0, s0, rw9::geometry::kRepEntry);
        if (a0 != 0) {
            // 0x00493ba0
            charge(ctx, 2);
            jal(ctx, 0x493BA0u, gen::fn_sub_4C47E0_004c47e0);
        }
        // 0x00493ba8
        charge(ctx, 12);
        lh(v0, s0, rw9::geometry::kRefCount);
        v0 = addiu(v0, -1);
        sh(v0, s0, rw9::geometry::kRefCount);
        lh(v0, s0, rw9::geometry::kRefCount);
        v0 = addiu(v0, 1);
        sh(v0, s0, rw9::geometry::kRefCount);
        lhu(v0, s0, rw9::geometry::kLockedSinceInst);
        v0 = v0 | 0xFFF;
        sh(v0, s0, rw9::geometry::kLockedSinceInst);
        lw(a0, s0, rw9::geometry::kMesh);
        if (a0 != 0) {
            // 0x00493bd8
            charge(ctx, 3);
            jal(ctx, 0x493BD8u, gen::fn_sub_495C80_00495c80);
            sw(zero, s0, rw9::geometry::kMesh);
        }
        // 0x00493be4
        charge(ctx, 7);
        a0 = 0x780000;
        a1 = s0;
        a0 = addiu(a0, -8928);  // &0x77DD20
        jal(ctx, 0x493BECu, gen::fn_sub_4C6560_004c6560);
        lw(a0, s0, rw9::geometry::kMorphTargets);
        if (a0 != 0) {
            // 0x00493c00
            charge(ctx, 5);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            jalr(ctx, 0x493C08u, v0.u());
            sw(zero, s0, rw9::geometry::kMorphTargets);
        }
        // 0x00493c14
        charge(ctx, 11);
        a0 = addiu(s0, 32);
        jal(ctx, 0x493C14u, gen::fn_sub_495260_00495260);
        lh(v1, s0, rw9::geometry::kRefCount);
        v0 = 0x960000;
        v1 = addiu(v1, -1);
        sh(v1, s0, rw9::geometry::kRefCount);
        lw(v0, v0, 380);  // 0x96017C
        a0 = s0;
        jalr(ctx, 0x493C30u, v0.u());
        v0 = 1;
        backedge(ctx);
    } else {
        // 0x00493b80
        charge(ctx, 3);
        lh(v1, s0, rw9::geometry::kRefCount);
        v1 = addiu(v1, -1);
        sh(v1, s0, rw9::geometry::kRefCount);
    }
    // 0x00493b8c
    charge(ctx, 2);
    ld(ra, sp, 0x10);
    // 0x00493c40
    charge(ctx, 3);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_493CB0 [geometryStreamRead] -- reads a geometry chunk: the struct (version 0x35000..0x37002, format / triangle /
//   vertex / morph-target counts), the geometry (RpGeometryCreate) with its extra morph targets, the pre-lit colours, the
//   UV sets, the triangles (vertex indices swapped into place), each morph target's bounding sphere, points and normals,
//   the material list (chunk 8, sub_4954C0), the mesh / extensions (sub_4C5A50 on 0x77DD20) and the unlock (sub_4933D0);
//   the geometry, or 0 (released on a failure)
// 0x00493CB0 sub_493CB0 -- 2016 bytes; frame 0xD0: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_493CB0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x00493cb0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    a1 = 1;
    sd(ra, sp, 0x70);
    a2 = 0;
    sq(s6, sp, 0x60);
    a3 = addiu(sp, 0xCC);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    link(ctx, 0x493CE0u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1600_004c1600);
    if (v0 == 0) {
        // 0x00493d44
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x00493cf0
        charge(ctx, 6);
        lw(v1, sp, 0xCC);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x00493d08
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_00493d1c;
            }
            // 0x00493d4c
            charge(ctx, 7);
            a0 = s5;
            a1 = addiu(sp, 0xA0);
            a2 = 16;
            jal(ctx, 0x493D54u, gen::fn_sub_4C5250_004c5250);
            v1 = 16;
            if (v0 == v1) {
                // 0x00493d70
                charge(ctx, 7);
                lw(a0, sp, 0xA8);
                lw(a1, sp, 0xA4);
                link(ctx, 0x493D78u);  // $ra first: the delay slot below depends on it
                lw(a2, sp, 0xA0);
                call(ctx, gen::fn_sub_493710_00493710);
                s4 = v0;
                if (s4 == 0) {
                    // 0x00494048
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x00493d8c
                    charge(ctx, 4);
                    lw(v0, sp, 0xAC);
                    at = slti(v0, 2);
                    if (at == 0) {
                        // 0x00494050
                        charge(ctx, 5);
                        a1 = addiu(v0, -1);
                        a0 = s4;
                        jal(ctx, 0x494054u, gen::fn_sub_492F80_00492f80);
                        if (i64(v0) >= 0) {
                            backedge(ctx);
                            goto L_00493d9c;
                        }
                        // 0x00494064
                        charge(ctx, 4);
                        lh(v0, s4, rw9::geometry::kRefCount);
                        v0 = addiu(v0, -1);
                        if (i64(v0) <= 0) {
                            // 0x00494088
                            charge(ctx, 3);
                            lw(a0, s4, rw9::geometry::kRepEntry);
                            if (a0 != 0) {
                                // 0x00494094
                                charge(ctx, 2);
                                jal(ctx, 0x494094u, gen::fn_sub_4C47E0_004c47e0);
                            }
                            // 0x0049409c
                            charge(ctx, 7);
                            lh(v0, s4, rw9::geometry::kRefCount);
                            a0 = s4;
                            v0 = addiu(v0, -1);
                            link(ctx, 0x4940A8u);  // $ra first: the delay slot below depends on it
                            sh(v0, s4, rw9::geometry::kRefCount);
                            call(ctx, gen::fn_sub_492D50_00492d50);
                            backedge(ctx);
                        } else {
                            // 0x00494074
                            charge(ctx, 3);
                            lh(v0, s4, rw9::geometry::kRefCount);
                            v0 = addiu(v0, -1);
                            sh(v0, s4, rw9::geometry::kRefCount);
                        }
                        // 0x00494080
                        charge(ctx, 2);
                        v0 = 0;
                        // 0x00494468 (the shared epilogue, written out on this path)
                        charge(ctx, 10);
                        ld(ra, sp, 0x70);
                        lq(s6, sp, 0x60);
                        lq(s5, sp, 0x50);
                        lq(s4, sp, 0x40);
                        lq(s3, sp, 0x30);
                        lq(s2, sp, 0x20);
                        lq(s1, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0xD0);
                        return;
                    }
                L_00493d9c:
                    charge(ctx, 5);
                    lw(v1, s4, rw9::geometry::kFlags);
                    v0 = 0x1000000;
                    v0 = v1 & v0;
                    if (v0 == 0) {
                        // 0x00493db0
                        charge(ctx, 3);
                        lw(v1, s4, rw9::geometry::kNumVertices);
                        if (v1 == 0) {
                            goto L_00493ec8;
                        }
                        // 0x00493dbc
                        charge(ctx, 4);
                        lw(v0, sp, 0xA0);
                        v0 = v0 & 0x8;
                        if (v0 != 0) {
                            // 0x004940b8
                            charge(ctx, 7);
                            lw(a1, s4, rw9::geometry::kPreLit);
                            s0 = sll(v1, 2);
                            a0 = s5;
                            a2 = s0;
                            jal(ctx, 0x4940C4u, gen::fn_sub_4C5250_004c5250);
                            if (s0 == v0) {
                                backedge(ctx);
                                goto L_00493dcc;
                            }
                            // 0x004940d4
                            charge(ctx, 4);
                            lh(v0, s4, rw9::geometry::kRefCount);
                            v0 = addiu(v0, -1);
                            if (i64(v0) <= 0) {
                                // 0x004940f8
                                charge(ctx, 3);
                                lw(a0, s4, rw9::geometry::kRepEntry);
                                if (a0 != 0) {
                                    // 0x00494104
                                    charge(ctx, 2);
                                    jal(ctx, 0x494104u, gen::fn_sub_4C47E0_004c47e0);
                                }
                                // 0x0049410c
                                charge(ctx, 7);
                                lh(v0, s4, rw9::geometry::kRefCount);
                                a0 = s4;
                                v0 = addiu(v0, -1);
                                link(ctx, 0x494118u);  // $ra first: the delay slot below depends on it
                                sh(v0, s4, rw9::geometry::kRefCount);
                                call(ctx, gen::fn_sub_492D50_00492d50);
                                backedge(ctx);
                            } else {
                                // 0x004940e4
                                charge(ctx, 3);
                                lh(v0, s4, rw9::geometry::kRefCount);
                                v0 = addiu(v0, -1);
                                sh(v0, s4, rw9::geometry::kRefCount);
                            }
                            // 0x004940f0
                            charge(ctx, 2);
                            v0 = 0;
                            // 0x00494468 (the shared epilogue, written out on this path)
                            charge(ctx, 10);
                            ld(ra, sp, 0x70);
                            lq(s6, sp, 0x60);
                            lq(s5, sp, 0x50);
                            lq(s4, sp, 0x40);
                            lq(s3, sp, 0x30);
                            lq(s2, sp, 0x20);
                            lq(s1, sp, 0x10);
                            lq(s0, sp, 0x0);
                            sp = addiu(sp, 0xD0);
                            return;
                        }
                    L_00493dcc:
                        charge(ctx, 3);
                        lw(v1, s4, rw9::geometry::kNumTexCoordSets);
                        if (i64(v1) > 0) {
                            // 0x00493dd8
                            charge(ctx, 5);
                            lw(v0, s4, rw9::geometry::kNumVertices);
                            at = slt(0, v1);
                            s2 = 0;
                            s0 = sll(v0, 3);
                            if (at == 0) {
                                goto L_00493e40;
                            }
                            // 0x00493dec
                            charge(ctx, 1);
                            s1 = s4;
                            for (;;) {
                                // 0x00493df0
                                charge(ctx, 6);
                                lw(a1, s1, 52);
                                a0 = s5;
                                a2 = s0;
                                jal(ctx, 0x493DF8u, gen::fn_sub_4C18B0_004c18b0);
                                if (v0 == 0) {
                                    goto L_00493e08_16;
                                }
                                // 0x00493e2c
                                charge(ctx, 5);
                                lw(v0, s4, rw9::geometry::kNumTexCoordSets);
                                s2 = addiu(s2, 1);
                                v0 = slt(s2, v0);
                                s1 = addiu(s1, 4);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            goto L_00493e40;
                        }
                    L_00493e40:
                        charge(ctx, 3);
                        lw(s2, s4, rw9::geometry::kNumTriangles);
                        if (s2 == 0) {
                            goto L_00493ec8;
                        }
                        // 0x00493e4c
                        charge(ctx, 8);
                        lw(s0, s4, rw9::geometry::kTriangles);
                        s1 = sll(s2, 3);
                        a0 = s5;
                        a2 = s1;
                        a1 = s0;
                        jal(ctx, 0x493E5Cu, gen::fn_sub_4C5250_004c5250);
                        if (s1 == v0) {
                            // 0x00493e90
                            charge(ctx, 2);
                            a1 = addiu(s2, -1);
                            if (s2 != 0) {
                                for (;;) {
                                    // 0x00493e98
                                    charge(ctx, 12);
                                    lw(a0, s0, 0);
                                    v0 = a1;
                                    a1 = addiu(a1, -1);
                                    v1 = srl(a0, 16);
                                    sh(v1, s0, 0);
                                    sh(a0, s0, 2);
                                    lw(a0, s0, 4);
                                    v1 = srl(a0, 16);
                                    sh(v1, s0, 4);
                                    sh(a0, s0, 6);
                                    s0 = addiu(s0, 8);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                            }
                            goto L_00493ec8;
                        }
                        // 0x00493e6c
                        charge(ctx, 4);
                        lh(v0, s4, rw9::geometry::kRefCount);
                        v0 = addiu(v0, -1);
                        if (i64(v0) <= 0) {
                            // 0x00494158
                            charge(ctx, 3);
                            lw(a0, s4, rw9::geometry::kRepEntry);
                            if (a0 != 0) {
                                // 0x00494164
                                charge(ctx, 2);
                                jal(ctx, 0x494164u, gen::fn_sub_4C47E0_004c47e0);
                            }
                            // 0x0049416c
                            charge(ctx, 7);
                            lh(v0, s4, rw9::geometry::kRefCount);
                            a0 = s4;
                            v0 = addiu(v0, -1);
                            link(ctx, 0x494178u);  // $ra first: the delay slot below depends on it
                            sh(v0, s4, rw9::geometry::kRefCount);
                            call(ctx, gen::fn_sub_492D50_00492d50);
                            backedge(ctx);
                        } else {
                            // 0x00493e7c
                            charge(ctx, 3);
                            lh(v0, s4, rw9::geometry::kRefCount);
                            v0 = addiu(v0, -1);
                            sh(v0, s4, rw9::geometry::kRefCount);
                        }
                        // 0x00493e88
                        charge(ctx, 2);
                        v0 = 0;
                        // 0x00494468 (the shared epilogue, written out on this path)
                        charge(ctx, 10);
                        ld(ra, sp, 0x70);
                        lq(s6, sp, 0x60);
                        lq(s5, sp, 0x50);
                        lq(s4, sp, 0x40);
                        lq(s3, sp, 0x30);
                        lq(s2, sp, 0x20);
                        lq(s1, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0xD0);
                        return;
                    }
                L_00493ec8:
                    charge(ctx, 4);
                    lw(v0, s4, rw9::geometry::kNumMorphTargets);
                    at = slt(0, v0);
                    s3 = 0;
                    if (at != 0) {
                        // 0x00493ed8
                        charge(ctx, 3);
                        s2 = 0;
                        s6 = addiu(sp, 0x90);
                        s1 = addiu(sp, 0x94);
                        for (;;) {
                            // 0x00493ee4
                            charge(ctx, 9);
                            lw(v0, s4, rw9::geometry::kMorphTargets);
                            a0 = s5;
                            a1 = addiu(sp, 0x80);
                            a2 = 24;
                            s0 = addu(v0, s2);
                            jal(ctx, 0x493EF4u, gen::fn_sub_4C5250_004c5250);
                            v1 = 24;
                            if (v0 != v1) {
                                goto L_00493f08_30;
                            }
                            // 0x00493f2c
                            charge(ctx, 11);
                            lwc1(f3, sp, 0x80);
                            lwc1(f2, sp, 0x84);
                            lwc1(f1, sp, 0x88);
                            lwc1(f0, sp, 0x8C);
                            swc1(f3, s0, 4);
                            swc1(f2, s0, 8);
                            swc1(f1, s0, 12);
                            swc1(f0, s0, 16);
                            lw(v1, s6, 0);
                            if (v1 != 0) {
                                // 0x004941b8
                                charge(ctx, 3);
                                lw(v0, s1, 0);
                                if (v0 == 0) {
                                    backedge(ctx);
                                    goto L_00493f58;
                                }
                                // 0x004941c4
                                charge(ctx, 9);
                                lw(v1, s4, rw9::geometry::kNumVertices);
                                a0 = s5;
                                lw(a1, s0, 20);
                                v0 = sll(v1, 1);
                                v0 = addu(v0, v1);
                                a2 = sll(v0, 3);
                                jal(ctx, 0x4941D8u, gen::fn_sub_4C18B0_004c18b0);
                                if (v0 == 0) {
                                    goto L_004941e8_74;
                                }
                                backedge(ctx);
                            L_00493fb4:
                                charge(ctx, 5);
                                lw(v0, s4, rw9::geometry::kNumMorphTargets);
                                s3 = addiu(s3, 1);
                                v0 = slt(s3, v0);
                                s2 = addiu(s2, 28);
                                if (v0 == 0) {
                                    goto L_00493fc8;
                                }
                                backedge(ctx);
                                continue;
                            }
                        L_00493f58:
                            charge(ctx, 2);
                            if (v1 != 0) {
                                // 0x0049423c
                                charge(ctx, 9);
                                lw(v1, s4, rw9::geometry::kNumVertices);
                                a0 = s5;
                                lw(a1, s0, 20);
                                v0 = sll(v1, 1);
                                v0 = addu(v0, v1);
                                a2 = sll(v0, 2);
                                jal(ctx, 0x494250u, gen::fn_sub_4C18B0_004c18b0);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                goto L_00493f60;
                            }
                        L_00493f60:
                            charge(ctx, 3);
                            lw(v0, s1, 0);
                            if (v0 == 0) {
                                goto L_00493fb4;
                            }
                            // 0x00493f6c
                            charge(ctx, 9);
                            lw(v1, s4, rw9::geometry::kNumVertices);
                            a0 = s5;
                            lw(a1, s0, 24);
                            v0 = sll(v1, 1);
                            v0 = addu(v0, v1);
                            a2 = sll(v0, 2);
                            jal(ctx, 0x493F80u, gen::fn_sub_4C18B0_004c18b0);
                            if (v0 != 0) {
                                goto L_00493fb4;
                            }
                            goto L_00493f90_37;
                        }
                        // 0x00494260
                        charge(ctx, 4);
                        lh(v0, s4, rw9::geometry::kRefCount);
                        v0 = addiu(v0, -1);
                        if (i64(v0) <= 0) {
                            // 0x00494284
                            charge(ctx, 3);
                            lw(a0, s4, rw9::geometry::kRepEntry);
                            if (a0 != 0) {
                                // 0x00494290
                                charge(ctx, 2);
                                jal(ctx, 0x494290u, gen::fn_sub_4C47E0_004c47e0);
                            }
                            // 0x00494298
                            charge(ctx, 7);
                            lh(v0, s4, rw9::geometry::kRefCount);
                            a0 = s4;
                            v0 = addiu(v0, -1);
                            link(ctx, 0x4942A4u);  // $ra first: the delay slot below depends on it
                            sh(v0, s4, rw9::geometry::kRefCount);
                            call(ctx, gen::fn_sub_492D50_00492d50);
                            backedge(ctx);
                        } else {
                            // 0x00494270
                            charge(ctx, 3);
                            lh(v0, s4, rw9::geometry::kRefCount);
                            v0 = addiu(v0, -1);
                            sh(v0, s4, rw9::geometry::kRefCount);
                        }
                        // 0x0049427c
                        charge(ctx, 2);
                        v0 = 0;
                        // 0x00494468 (the shared epilogue, written out on this path)
                        charge(ctx, 10);
                        ld(ra, sp, 0x70);
                        lq(s6, sp, 0x60);
                        lq(s5, sp, 0x50);
                        lq(s4, sp, 0x40);
                        lq(s3, sp, 0x30);
                        lq(s2, sp, 0x20);
                        lq(s1, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0xD0);
                        return;
                    }
                L_00493fc8:
                    charge(ctx, 7);
                    a0 = s5;
                    a1 = 8;
                    a2 = 0;
                    a3 = addiu(sp, 0xCC);
                    jal(ctx, 0x493FD4u, gen::fn_sub_4C1600_004c1600);
                    if (v0 == 0) {
                        // 0x004942e4
                        charge(ctx, 2);
                        v0 = 0;
                    } else {
                        // 0x00493fe4
                        charge(ctx, 6);
                        lw(v1, sp, 0xCC);
                        v0 = 0x30000;
                        v0 = v0 | 0x5000;
                        v0 = sltu(v1, v0);
                        if (v0 == 0) {
                            // 0x00493ffc
                            charge(ctx, 5);
                            at = 0x30000;
                            at = at | 0x7003;
                            at = sltu(v1, at);
                            if (at == 0) {
                                goto L_004942ec;
                            }
                            // 0x00494010
                            charge(ctx, 5);
                            a0 = s5;
                            a1 = addiu(s4, 32);
                            jal(ctx, 0x494014u, gen::fn_sub_4954C0_004954c0);
                            if (v0 != 0) {
                                // 0x00494390
                                charge(ctx, 7);
                                a0 = 0x780000;
                                a1 = s5;
                                a0 = addiu(a0, -8928);  // &0x77DD20
                                a2 = s4;
                                jal(ctx, 0x49439Cu, gen::fn_sub_4C5A50_004c5a50);
                                if (v0 != 0) {
                                    // 0x00494400
                                    charge(ctx, 4);
                                    a0 = s4;
                                    jal(ctx, 0x494400u, gen::fn_sub_4933D0_004933d0);
                                    if (v0 != 0) {
                                        // 0x00494464
                                        charge(ctx, 1);
                                        v0 = s4;
                                    } else {
                                        // 0x00494410
                                        charge(ctx, 4);
                                        lh(v0, s4, rw9::geometry::kRefCount);
                                        v0 = addiu(v0, -1);
                                        if (i64(v0) <= 0) {
                                            // 0x00494434
                                            charge(ctx, 3);
                                            lw(a0, s4, rw9::geometry::kRepEntry);
                                            if (a0 != 0) {
                                                // 0x00494440
                                                charge(ctx, 2);
                                                jal(ctx, 0x494440u, gen::fn_sub_4C47E0_004c47e0);
                                            }
                                            // 0x00494448
                                            charge(ctx, 7);
                                            lh(v0, s4, rw9::geometry::kRefCount);
                                            a0 = s4;
                                            v0 = addiu(v0, -1);
                                            link(ctx, 0x494454u);  // $ra first: the delay slot below depends on it
                                            sh(v0, s4, rw9::geometry::kRefCount);
                                            call(ctx, gen::fn_sub_492D50_00492d50);
                                            backedge(ctx);
                                        } else {
                                            // 0x00494420
                                            charge(ctx, 3);
                                            lh(v0, s4, rw9::geometry::kRefCount);
                                            v0 = addiu(v0, -1);
                                            sh(v0, s4, rw9::geometry::kRefCount);
                                        }
                                        // 0x0049442c
                                        charge(ctx, 2);
                                        v0 = 0;
                                    }
                                } else {
                                    // 0x004943ac
                                    charge(ctx, 4);
                                    lh(v0, s4, rw9::geometry::kRefCount);
                                    v0 = addiu(v0, -1);
                                    if (i64(v0) <= 0) {
                                        // 0x004943d0
                                        charge(ctx, 3);
                                        lw(a0, s4, rw9::geometry::kRepEntry);
                                        if (a0 != 0) {
                                            // 0x004943dc
                                            charge(ctx, 2);
                                            jal(ctx, 0x4943DCu, gen::fn_sub_4C47E0_004c47e0);
                                        }
                                        // 0x004943e4
                                        charge(ctx, 7);
                                        lh(v0, s4, rw9::geometry::kRefCount);
                                        a0 = s4;
                                        v0 = addiu(v0, -1);
                                        link(ctx, 0x4943F0u);  // $ra first: the delay slot below depends on it
                                        sh(v0, s4, rw9::geometry::kRefCount);
                                        call(ctx, gen::fn_sub_492D50_00492d50);
                                        backedge(ctx);
                                    } else {
                                        // 0x004943bc
                                        charge(ctx, 3);
                                        lh(v0, s4, rw9::geometry::kRefCount);
                                        v0 = addiu(v0, -1);
                                        sh(v0, s4, rw9::geometry::kRefCount);
                                    }
                                    // 0x004943c8
                                    charge(ctx, 2);
                                    v0 = 0;
                                }
                            } else {
                                // 0x00494024
                                charge(ctx, 4);
                                lh(v0, s4, rw9::geometry::kRefCount);
                                v0 = addiu(v0, -1);
                                if (i64(v0) <= 0) {
                                    // 0x00494360
                                    charge(ctx, 3);
                                    lw(a0, s4, rw9::geometry::kRepEntry);
                                    if (a0 != 0) {
                                        // 0x0049436c
                                        charge(ctx, 2);
                                        jal(ctx, 0x49436Cu, gen::fn_sub_4C47E0_004c47e0);
                                    }
                                    // 0x00494374
                                    charge(ctx, 7);
                                    lh(v0, s4, rw9::geometry::kRefCount);
                                    a0 = s4;
                                    v0 = addiu(v0, -1);
                                    link(ctx, 0x494380u);  // $ra first: the delay slot below depends on it
                                    sh(v0, s4, rw9::geometry::kRefCount);
                                    call(ctx, gen::fn_sub_492D50_00492d50);
                                    backedge(ctx);
                                } else {
                                    // 0x00494034
                                    charge(ctx, 3);
                                    lh(v0, s4, rw9::geometry::kRefCount);
                                    v0 = addiu(v0, -1);
                                    sh(v0, s4, rw9::geometry::kRefCount);
                                }
                                // 0x00494040
                                charge(ctx, 2);
                                v0 = 0;
                            }
                            // 0x00494468 (the shared epilogue, written out on this path)
                            charge(ctx, 10);
                            ld(ra, sp, 0x70);
                            lq(s6, sp, 0x60);
                            lq(s5, sp, 0x50);
                            lq(s4, sp, 0x40);
                            lq(s3, sp, 0x30);
                            lq(s2, sp, 0x20);
                            lq(s1, sp, 0x10);
                            lq(s0, sp, 0x0);
                            sp = addiu(sp, 0xD0);
                            return;
                        }
                    L_004942ec:
                        charge(ctx, 4);
                        lh(v0, s4, rw9::geometry::kRefCount);
                        v0 = addiu(v0, -1);
                        if (i64(v0) <= 0) {
                            // 0x00494330
                            charge(ctx, 3);
                            lw(a0, s4, rw9::geometry::kRepEntry);
                            if (a0 != 0) {
                                // 0x0049433c
                                charge(ctx, 2);
                                jal(ctx, 0x49433Cu, gen::fn_sub_4C47E0_004c47e0);
                            }
                            // 0x00494344
                            charge(ctx, 7);
                            lh(v0, s4, rw9::geometry::kRefCount);
                            a0 = s4;
                            v0 = addiu(v0, -1);
                            link(ctx, 0x494350u);  // $ra first: the delay slot below depends on it
                            sh(v0, s4, rw9::geometry::kRefCount);
                            call(ctx, gen::fn_sub_492D50_00492d50);
                            v1 = 2;
                            backedge(ctx);
                        } else {
                            // 0x004942fc
                            charge(ctx, 4);
                            lh(v0, s4, rw9::geometry::kRefCount);
                            v0 = addiu(v0, -1);
                            sh(v0, s4, rw9::geometry::kRefCount);
                            v1 = 2;
                        }
                        // 0x0049430c
                        charge(ctx, 9);
                        v0 = lui(0x8000);
                        sw(v1, sp, 0xB8);
                        a0 = v0 | 0x4;
                        jal(ctx, 0x494314u, gen::fn_sub_4C1D10_004c1d10);
                        sw(v0, sp, 0xBC);
                        a0 = addiu(sp, 0xB8);
                        jal(ctx, 0x494320u, gen::fn_sub_4C1C50_004c1c50);
                        v0 = 0;
                    }
                }
            } else {
                // 0x00493d68
                charge(ctx, 2);
                v0 = 0;
            }
            // 0x00494468 (the shared epilogue, written out on this path)
            charge(ctx, 10);
            ld(ra, sp, 0x70);
            lq(s6, sp, 0x60);
            lq(s5, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0xD0);
            return;
        }
    L_00493d1c:
        charge(ctx, 10);
        v1 = 2;
        v0 = lui(0x8000);
        sw(v1, sp, 0xC0);
        a0 = v0 | 0x4;
        jal(ctx, 0x493D28u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0xC4);
        a0 = addiu(sp, 0xC0);
        jal(ctx, 0x493D34u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x00494468 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
    return;
L_00493e08_16:
    charge(ctx, 4);
    lh(v0, s4, rw9::geometry::kRefCount);
    v0 = addiu(v0, -1);
    if (i64(v0) <= 0) {
        // 0x00494128
        charge(ctx, 3);
        lw(a0, s4, rw9::geometry::kRepEntry);
        if (a0 != 0) {
            // 0x00494134
            charge(ctx, 2);
            jal(ctx, 0x494134u, gen::fn_sub_4C47E0_004c47e0);
        }
        // 0x0049413c
        charge(ctx, 7);
        lh(v0, s4, rw9::geometry::kRefCount);
        a0 = s4;
        v0 = addiu(v0, -1);
        link(ctx, 0x494148u);  // $ra first: the delay slot below depends on it
        sh(v0, s4, rw9::geometry::kRefCount);
        call(ctx, gen::fn_sub_492D50_00492d50);
        backedge(ctx);
    } else {
        // 0x00493e18
        charge(ctx, 3);
        lh(v0, s4, rw9::geometry::kRefCount);
        v0 = addiu(v0, -1);
        sh(v0, s4, rw9::geometry::kRefCount);
    }
    // 0x00493e24
    charge(ctx, 2);
    v0 = 0;
    // 0x00494468 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
    return;
L_00493f08_30:
    charge(ctx, 4);
    lh(v0, s4, rw9::geometry::kRefCount);
    v0 = addiu(v0, -1);
    if (i64(v0) <= 0) {
        // 0x00494188
        charge(ctx, 3);
        lw(a0, s4, rw9::geometry::kRepEntry);
        if (a0 != 0) {
            // 0x00494194
            charge(ctx, 2);
            jal(ctx, 0x494194u, gen::fn_sub_4C47E0_004c47e0);
        }
        // 0x0049419c
        charge(ctx, 7);
        lh(v0, s4, rw9::geometry::kRefCount);
        a0 = s4;
        v0 = addiu(v0, -1);
        link(ctx, 0x4941A8u);  // $ra first: the delay slot below depends on it
        sh(v0, s4, rw9::geometry::kRefCount);
        call(ctx, gen::fn_sub_492D50_00492d50);
        backedge(ctx);
    } else {
        // 0x00493f18
        charge(ctx, 3);
        lh(v0, s4, rw9::geometry::kRefCount);
        v0 = addiu(v0, -1);
        sh(v0, s4, rw9::geometry::kRefCount);
    }
    // 0x00493f24
    charge(ctx, 2);
    v0 = 0;
    // 0x00494468 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
    return;
L_00493f90_37:
    charge(ctx, 4);
    lh(v0, s4, rw9::geometry::kRefCount);
    v0 = addiu(v0, -1);
    if (i64(v0) <= 0) {
        // 0x004942b4
        charge(ctx, 3);
        lw(a0, s4, rw9::geometry::kRepEntry);
        if (a0 != 0) {
            // 0x004942c0
            charge(ctx, 2);
            jal(ctx, 0x4942C0u, gen::fn_sub_4C47E0_004c47e0);
        }
        // 0x004942c8
        charge(ctx, 7);
        lh(v0, s4, rw9::geometry::kRefCount);
        a0 = s4;
        v0 = addiu(v0, -1);
        link(ctx, 0x4942D4u);  // $ra first: the delay slot below depends on it
        sh(v0, s4, rw9::geometry::kRefCount);
        call(ctx, gen::fn_sub_492D50_00492d50);
        backedge(ctx);
    } else {
        // 0x00493fa0
        charge(ctx, 3);
        lh(v0, s4, rw9::geometry::kRefCount);
        v0 = addiu(v0, -1);
        sh(v0, s4, rw9::geometry::kRefCount);
    }
    // 0x00493fac
    charge(ctx, 2);
    v0 = 0;
    // 0x00494468 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
    return;
L_004941e8_74:
    charge(ctx, 4);
    lh(v0, s4, rw9::geometry::kRefCount);
    v0 = addiu(v0, -1);
    if (i64(v0) <= 0) {
        // 0x0049420c
        charge(ctx, 3);
        lw(a0, s4, rw9::geometry::kRepEntry);
        if (a0 != 0) {
            // 0x00494218
            charge(ctx, 2);
            jal(ctx, 0x494218u, gen::fn_sub_4C47E0_004c47e0);
        }
        // 0x00494220
        charge(ctx, 7);
        lh(v0, s4, rw9::geometry::kRefCount);
        a0 = s4;
        v0 = addiu(v0, -1);
        link(ctx, 0x49422Cu);  // $ra first: the delay slot below depends on it
        sh(v0, s4, rw9::geometry::kRefCount);
        call(ctx, gen::fn_sub_492D50_00492d50);
        backedge(ctx);
    } else {
        // 0x004941f8
        charge(ctx, 3);
        lh(v0, s4, rw9::geometry::kRefCount);
        v0 = addiu(v0, -1);
        sh(v0, s4, rw9::geometry::kRefCount);
    }
    // 0x00494204
    charge(ctx, 2);
    v0 = 0;
    // 0x00494468 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// sub_495260 [materialListDeinit] -- frees a material list: each material released (sub_494CC0) and its slot cleared,
//   the array freed (RwFree), the count and capacity zeroed; the list
// 0x00495260 sub_495260 -- 152 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_495260(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00495260
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s4, a0, 0);
    s0 = a0;
    if (s4 != 0) {
        // 0x00495288
        charge(ctx, 4);
        lw(s1, s0, rw9::matlist::kCount);
        at = slt(0, s1);
        s3 = 0;
        if (at != 0) {
            // 0x00495298
            charge(ctx, 1);
            s2 = s4;
            for (;;) {
                // 0x0049529c
                charge(ctx, 7);
                link(ctx, 0x49529Cu);  // $ra first: the delay slot below depends on it
                lw(a0, s2, 0);
                call(ctx, gen::fn_sub_494CC0_00494cc0);
                s3 = addiu(s3, 1);
                sw(zero, s2, 0);
                v0 = slt(s3, s1);
                s2 = addiu(s2, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004952b8
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        a0 = s4;
        jalr(ctx, 0x4952C0u, v0.u());
        sw(zero, s0, rw9::matlist::kMaterials);
    }
    // 0x004952cc (the shared epilogue, written out on this path)
    charge(ctx, 11);
    sw(zero, s0, rw9::matlist::kCount);
    v0 = s0;
    sw(zero, s0, rw9::matlist::kSpace);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4954C0 [materialListStreamRead] -- reads a material list chunk: the struct (version 0x35000..0x37002) and count,
//   the array grown (RwRealloc / RwMalloc), the index array; per entry a new material chunk (index < 0: chunk 7,
//   sub_494E30) or a reference to an earlier one (its reference count +24 up), appended (sub_495340) and released once
//   (sub_494CC0); on a failure the list is emptied; the list, or 0
// 0x004954C0 sub_4954C0 -- 1280 bytes; frame 0xA0: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4954C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004954c0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x60);
    a2 = addiu(sp, 0x98);
    sq(s5, sp, 0x50);
    a3 = addiu(sp, 0x94);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a1 = 1;
    jal(ctx, 0x4954F0u, gen::fn_sub_4C1600_004c1600);
    if (v0 == 0) {
        // 0x00495690
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x00495500
        charge(ctx, 6);
        lw(v1, sp, 0x94);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x00495518
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_00495978;
            }
            // 0x0049552c
            charge(ctx, 7);
            a0 = s1;
            a1 = addiu(sp, 0x9C);
            a2 = 4;
            jal(ctx, 0x495534u, gen::fn_sub_4C1910_004c1910);
            v0 = sltu(0, v0);
            if (v0 == 0) {
                // 0x00495698
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x00495548
                charge(ctx, 6);
                sw(zero, s0, rw9::matlist::kSpace);
                sw(zero, s0, rw9::matlist::kMaterials);
                sw(zero, s0, rw9::matlist::kCount);
                lw(s2, sp, 0x9C);
                if (s2 == 0) {
                    // 0x004956a0
                    charge(ctx, 2);
                    v0 = s0;
                } else {
                    // 0x00495560
                    charge(ctx, 4);
                    lw(v0, s0, rw9::matlist::kSpace);
                    at = slt(v0, s2);
                    if (at != 0) {
                        // 0x00495570
                        charge(ctx, 3);
                        lw(a0, s0, rw9::matlist::kMaterials);
                        s3 = sll(s2, 2);
                        if (a0 == 0) {
                            // 0x0049559c
                            charge(ctx, 6);
                            v0 = 0x1030000;
                            a1 = v0 | 0x8;  // &0x1030008
                            v0 = 0x960000;
                            lw(v0, v0, 376);  // 0x960178
                            a0 = s3;
                            jalr(ctx, 0x4955ACu, v0.u());
                        } else {
                            // 0x0049557c
                            charge(ctx, 8);
                            v0 = 0x1030000;
                            a2 = v0 | 0x8;  // &0x1030008
                            v0 = 0x960000;
                            lw(v0, v0, 384);  // 0x960180
                            a1 = s3;
                            jalr(ctx, 0x49558Cu, v0.u());
                        }
                        // 0x004955b4
                        charge(ctx, 2);
                        if (v0 != 0) {
                            // 0x004955bc
                            charge(ctx, 2);
                            sw(v0, s0, rw9::matlist::kMaterials);
                            sw(s2, s0, rw9::matlist::kSpace);
                            goto L_004955c4;
                        }
                        // 0x004956a8
                        charge(ctx, 11);
                        v0 = 2;
                        a1 = s3;
                        sw(v0, sp, 0x78);
                        v0 = lui(0x8000);
                        a0 = v0 | 0x13;
                        jal(ctx, 0x4956B8u, gen::fn_sub_4C1D10_004c1d10);
                        sw(v0, sp, 0x7C);
                        a0 = addiu(sp, 0x78);
                        jal(ctx, 0x4956C4u, gen::fn_sub_4C1C50_004c1c50);
                        v0 = 0;
                        backedge(ctx);
                        goto L_004955c8;
                    }
                L_004955c4:
                    charge(ctx, 1);
                    v0 = s0;
                L_004955c8:
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x004956d4
                        charge(ctx, 3);
                        lw(s4, s0, rw9::matlist::kMaterials);
                        if (s4 != 0) {
                            // 0x004956e0
                            charge(ctx, 4);
                            lw(s1, s0, rw9::matlist::kCount);
                            at = slt(0, s1);
                            s3 = 0;
                            if (at != 0) {
                                // 0x004956f0
                                charge(ctx, 1);
                                s2 = s4;
                                for (;;) {
                                    // 0x004956f4
                                    charge(ctx, 7);
                                    link(ctx, 0x4956F4u);  // $ra first: the delay slot below depends on it
                                    lw(a0, s2, 0);
                                    call(ctx, gen::fn_sub_494CC0_00494cc0);
                                    s3 = addiu(s3, 1);
                                    sw(zero, s2, 0);
                                    v0 = slt(s3, s1);
                                    s2 = addiu(s2, 4);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                            }
                            // 0x00495710
                            charge(ctx, 5);
                            v0 = 0x960000;
                            lw(v0, v0, 380);  // 0x96017C
                            a0 = s4;
                            jalr(ctx, 0x495718u, v0.u());
                            sw(zero, s0, rw9::matlist::kMaterials);
                        }
                        // 0x00495724
                        charge(ctx, 4);
                        sw(zero, s0, rw9::matlist::kCount);
                        v0 = 0;
                        sw(zero, s0, rw9::matlist::kSpace);
                    } else {
                        // 0x004955d0
                        charge(ctx, 16);
                        v0 = 0x10000;
                        lw(v1, sp, 0x9C);
                        a1 = v0 | 0x501;
                        v0 = 0x960000;
                        lw(v0, v0, 376);  // 0x960178
                        a0 = sll(v1, 2);
                        jalr(ctx, 0x4955E4u, v0.u());
                        s4 = v0;
                        a0 = s1;
                        lw(v0, sp, 0x9C);
                        a1 = s4;
                        a2 = sll(v0, 2);
                        jal(ctx, 0x4955FCu, gen::fn_sub_4C1910_004c1910);
                        v0 = sltu(0, v0);
                        if (v0 == 0) {
                            // 0x00495734
                            charge(ctx, 8);
                            s2 = 0x960000;
                            s2 = addiu(s2, 380);  // &0x96017C
                            lw(v0, s2, 0);  // 0x96017C
                            a0 = s4;
                            jalr(ctx, 0x495740u, v0.u());
                            lw(s5, s0, rw9::matlist::kMaterials);
                            if (s5 != 0) {
                                // 0x00495754
                                charge(ctx, 4);
                                lw(s1, s0, rw9::matlist::kCount);
                                at = slt(0, s1);
                                s4 = 0;
                                if (at != 0) {
                                    // 0x00495764
                                    charge(ctx, 1);
                                    s3 = s5;
                                    for (;;) {
                                        // 0x00495768
                                        charge(ctx, 7);
                                        link(ctx, 0x495768u);  // $ra first: the delay slot below depends on it
                                        lw(a0, s3, 0);
                                        call(ctx, gen::fn_sub_494CC0_00494cc0);
                                        s4 = addiu(s4, 1);
                                        sw(zero, s3, 0);
                                        v0 = slt(s4, s1);
                                        s3 = addiu(s3, 4);
                                        if (v0 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x00495784
                                    charge(ctx, 1);
                                }
                                // 0x00495788
                                charge(ctx, 4);
                                lw(v0, s2, 0);
                                a0 = s5;
                                jalr(ctx, 0x49578Cu, v0.u());
                                sw(zero, s0, rw9::matlist::kMaterials);
                            }
                            // 0x00495798
                            charge(ctx, 4);
                            sw(zero, s0, rw9::matlist::kCount);
                            v0 = 0;
                            sw(zero, s0, rw9::matlist::kSpace);
                        } else {
                            // 0x00495610
                            charge(ctx, 4);
                            lw(v0, sp, 0x9C);
                            at = slt(0, v0);
                            s5 = 0;
                            if (at != 0) {
                                // 0x00495620
                                charge(ctx, 1);
                                s2 = s4;
                                for (;;) {
                                    // 0x00495624
                                    charge(ctx, 3);
                                    lw(v0, s2, 0);
                                    if (i64(v0) >= 0) {
                                        // 0x00495630
                                        charge(ctx, 8);
                                        v1 = sll(v0, 2);
                                        lw(v0, s0, rw9::matlist::kMaterials);
                                        v0 = addu(v0, v1);
                                        lw(s3, v0, 0);
                                        lh(v0, s3, 24);
                                        v0 = addiu(v0, 1);
                                        sh(v0, s3, 24);
                                        goto L_00495650;
                                    }
                                    // 0x004957a8
                                    charge(ctx, 7);
                                    a0 = s1;
                                    a1 = 7;
                                    a2 = 0;
                                    a3 = addiu(sp, 0x94);
                                    jal(ctx, 0x4957B4u, gen::fn_sub_4C1600_004c1600);
                                    if (v0 == 0) {
                                        goto L_00495858;
                                    }
                                    // 0x004957c4
                                    charge(ctx, 6);
                                    lw(v1, sp, 0x94);
                                    v0 = 0x30000;
                                    v0 = v0 | 0x5000;
                                    v0 = sltu(v1, v0);
                                    if (v0 != 0) {
                                        goto L_004958e8;
                                    }
                                    // 0x004957dc
                                    charge(ctx, 5);
                                    at = 0x30000;
                                    at = at | 0x7003;
                                    at = sltu(v1, at);
                                    if (at == 0) {
                                        goto L_004958e8;
                                    }
                                    // 0x004957f0
                                    charge(ctx, 4);
                                    a0 = s1;
                                    jal(ctx, 0x4957F0u, gen::fn_sub_494E30_00494e30);
                                    s3 = v0;
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                L_00495650:
                                    charge(ctx, 10);
                                    a0 = s0;
                                    a1 = s3;
                                    jal(ctx, 0x495654u, gen::fn_sub_495340_00495340);
                                    a0 = s3;
                                    jal(ctx, 0x49565Cu, gen::fn_sub_494CC0_00494cc0);
                                    lw(v0, sp, 0x9C);
                                    s5 = addiu(s5, 1);
                                    v0 = slt(s5, v0);
                                    s2 = addiu(s2, 4);
                                    if (v0 == 0) {
                                        goto L_00495678;
                                    }
                                    backedge(ctx);
                                }
                                // 0x00495800
                                charge(ctx, 8);
                                s2 = 0x960000;
                                s2 = addiu(s2, 380);  // &0x96017C
                                lw(v0, s2, 0);  // 0x96017C
                                a0 = s4;
                                jalr(ctx, 0x49580Cu, v0.u());
                                lw(s5, s0, rw9::matlist::kMaterials);
                                if (s5 != 0) {
                                    // 0x00495820
                                    charge(ctx, 4);
                                    lw(s1, s0, rw9::matlist::kCount);
                                    at = slt(0, s1);
                                    s4 = 0;
                                    if (at == 0) {
                                        // 0x004958c8
                                        charge(ctx, 1);
                                        lw(v0, s2, 0);
                                    } else {
                                        // 0x00495830
                                        charge(ctx, 1);
                                        s3 = s5;
                                        for (;;) {
                                            // 0x00495834
                                            charge(ctx, 7);
                                            link(ctx, 0x495834u);  // $ra first: the delay slot below depends on it
                                            lw(a0, s3, 0);
                                            call(ctx, gen::fn_sub_494CC0_00494cc0);
                                            s4 = addiu(s4, 1);
                                            sw(zero, s3, 0);
                                            v0 = slt(s4, s1);
                                            s3 = addiu(s3, 4);
                                            if (v0 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                        // 0x00495850
                                        charge(ctx, 2);
                                        lw(v0, s2, 0);
                                    }
                                    // 0x004958cc
                                    charge(ctx, 3);
                                    a0 = s5;
                                    jalr(ctx, 0x4958CCu, v0.u());
                                    sw(zero, s0, rw9::matlist::kMaterials);
                                }
                                // 0x004958d8
                                charge(ctx, 4);
                                sw(zero, s0, rw9::matlist::kCount);
                                v0 = 0;
                                sw(zero, s0, rw9::matlist::kSpace);
                                // 0x0049599c (the shared epilogue, written out on this path)
                                charge(ctx, 9);
                                ld(ra, sp, 0x60);
                                lq(s5, sp, 0x50);
                                lq(s4, sp, 0x40);
                                lq(s3, sp, 0x30);
                                lq(s2, sp, 0x20);
                                lq(s1, sp, 0x10);
                                lq(s0, sp, 0x0);
                                sp = addiu(sp, 0xA0);
                                return;
                            }
                        L_00495678:
                            charge(ctx, 6);
                            v0 = 0x960000;
                            lw(v0, v0, 380);  // 0x96017C
                            a0 = s4;
                            jalr(ctx, 0x495680u, v0.u());
                            v0 = s0;
                        }
                    }
                }
            }
            // 0x0049599c (the shared epilogue, written out on this path)
            charge(ctx, 9);
            ld(ra, sp, 0x60);
            lq(s5, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0xA0);
            return;
        }
    L_00495978:
        charge(ctx, 9);
        v1 = 2;
        v0 = lui(0x8000);
        sw(v1, sp, 0x80);
        a0 = v0 | 0x4;
        jal(ctx, 0x495984u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x84);
        a0 = addiu(sp, 0x80);
        jal(ctx, 0x495990u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x0049599c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
    return;
L_00495858:
    charge(ctx, 8);
    s2 = 0x960000;
    s2 = addiu(s2, 380);  // &0x96017C
    lw(v0, s2, 0);  // 0x96017C
    a0 = s4;
    jalr(ctx, 0x495864u, v0.u());
    lw(s5, s0, rw9::matlist::kMaterials);
    if (s5 != 0) {
        // 0x00495878
        charge(ctx, 4);
        lw(s1, s0, rw9::matlist::kCount);
        at = slt(0, s1);
        s4 = 0;
        if (at != 0) {
            // 0x00495888
            charge(ctx, 1);
            s3 = s5;
            for (;;) {
                // 0x0049588c
                charge(ctx, 7);
                link(ctx, 0x49588Cu);  // $ra first: the delay slot below depends on it
                lw(a0, s3, 0);
                call(ctx, gen::fn_sub_494CC0_00494cc0);
                s4 = addiu(s4, 1);
                sw(zero, s3, 0);
                v0 = slt(s4, s1);
                s3 = addiu(s3, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004958a8
        charge(ctx, 4);
        lw(v0, s2, 0);
        a0 = s5;
        jalr(ctx, 0x4958ACu, v0.u());
        sw(zero, s0, rw9::matlist::kMaterials);
    }
    // 0x004958b8
    charge(ctx, 4);
    sw(zero, s0, rw9::matlist::kCount);
    v0 = 0;
    sw(zero, s0, rw9::matlist::kSpace);
    // 0x0049599c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
    return;
L_004958e8:
    charge(ctx, 16);
    v1 = 2;
    v0 = lui(0x8000);
    sw(v1, sp, 0x88);
    a0 = v0 | 0x4;
    jal(ctx, 0x4958F4u, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0x8C);
    a0 = addiu(sp, 0x88);
    jal(ctx, 0x495900u, gen::fn_sub_4C1C50_004c1c50);
    s2 = 0x960000;
    s2 = addiu(s2, 380);  // &0x96017C
    lw(v0, s2, 0);  // 0x96017C
    a0 = s4;
    jalr(ctx, 0x495914u, v0.u());
    lw(s5, s0, rw9::matlist::kMaterials);
    if (s5 != 0) {
        // 0x00495928
        charge(ctx, 4);
        lw(s1, s0, rw9::matlist::kCount);
        at = slt(0, s1);
        s4 = 0;
        if (at != 0) {
            // 0x00495938
            charge(ctx, 1);
            s3 = s5;
            for (;;) {
                // 0x0049593c
                charge(ctx, 7);
                link(ctx, 0x49593Cu);  // $ra first: the delay slot below depends on it
                lw(a0, s3, 0);
                call(ctx, gen::fn_sub_494CC0_00494cc0);
                s4 = addiu(s4, 1);
                sw(zero, s3, 0);
                v0 = slt(s4, s1);
                s3 = addiu(s3, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x00495958
        charge(ctx, 4);
        lw(v0, s2, 0);
        a0 = s5;
        jalr(ctx, 0x49595Cu, v0.u());
        sw(zero, s0, rw9::matlist::kMaterials);
    }
    // 0x00495968
    charge(ctx, 4);
    sw(zero, s0, rw9::matlist::kCount);
    v0 = 0;
    sw(zero, s0, rw9::matlist::kSpace);
    // 0x0049599c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// sub_49A290 [RpWorldDestroy] -- destroys a world: unlinked from the engine's world list (engine + gp 0x7CE860, the
//   link freed), its sectors torn down (sub_499FD0), the material list freed, the root sector freed (an atomic sector
//   sub_499720, a plane sector sub_499850), the plugin destructors (sub_4C6560 on 0x77DDD0), the world freed; 1
// 0x0049A290 sub_49A290 -- 320 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_49A290(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0049a290
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, 112);  // &0x960070
    sq(s0, sp, 0x0);
    lw(v1, gp, -17552);  // 0x7CE860
    s0 = a0;
    v0 = addu(v0, v1);
    lw(a0, v0, 4);
    v1 = addiu(v0, 4);
    if (a0 != v1) {
        for (;;) {
            // 0x0049a2c0
            charge(ctx, 3);
            lw(v0, a0, -8);
            a1 = addiu(a0, -8);
            if (v0 == s0) {
                goto L_0049a2cc_2;
            }
            // 0x0049a30c
            charge(ctx, 3);
            lw(a0, a0, 0);
            if (a0 == v1) {
                break;
            }
            backedge(ctx);
        }
        // 0x0049a318
        charge(ctx, 2);
    }
    // 0x0049a398
    charge(ctx, 1);
    a0 = s0;
L_0049a39c:
    charge(ctx, 8);
    jal(ctx, 0x49A39Cu, gen::fn_sub_499FD0_00499fd0);
    a0 = addiu(s0, 16);
    jal(ctx, 0x49A3A4u, gen::fn_sub_495260_00495260);
    lbu(v0, s0, 3);
    v0 = v0 & 0x1;
    if (v0 == 0) {
        backedge(ctx);
        // 0x0049a358
        charge(ctx, 3);
        lw(a0, s0, 28);
        if (a0 != 0) {
            // 0x0049a364
            charge(ctx, 2);
            jal(ctx, 0x49A364u, gen::fn_sub_499850_00499850);
        }
        // 0x0049a36c
        charge(ctx, 9);
        a0 = 0x780000;
        a1 = s0;
        a0 = addiu(a0, -8752);  // &0x77DDD0
        jal(ctx, 0x49A374u, gen::fn_sub_4C6560_004c6560);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        a0 = s0;
        jalr(ctx, 0x49A384u, v0.u());
        v0 = 1;
    } else {
        // 0x0049a3bc
        charge(ctx, 2);
        lw(a0, s0, 28);
        backedge(ctx);
        // 0x0049a320
        charge(ctx, 2);
        if (a0 != 0) {
            // 0x0049a328
            charge(ctx, 2);
            jal(ctx, 0x49A328u, gen::fn_sub_499720_00499720);
        }
        // 0x0049a330
        charge(ctx, 10);
        a0 = 0x780000;
        a1 = s0;
        a0 = addiu(a0, -8752);  // &0x77DDD0
        jal(ctx, 0x49A338u, gen::fn_sub_4C6560_004c6560);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        a0 = s0;
        jalr(ctx, 0x49A348u, v0.u());
        v0 = 1;
    }
    // 0x0049a390
    charge(ctx, 2);
    ld(ra, sp, 0x10);
    // 0x0049a3c4
    charge(ctx, 3);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
    return;
L_0049a2cc_2:
    charge(ctx, 16);
    lw(a2, a1, 8);
    v1 = 0x960000;
    lw(a0, a1, 12);
    v1 = addiu(v1, 112);  // &0x960070
    v0 = 0x960000;
    sw(a2, a0, 0);
    lw(a2, a1, 12);
    lw(a0, a1, 8);
    sw(a2, a0, 4);
    lw(a0, gp, -17552);  // 0x7CE860
    lw(v0, v0, 396);  // 0x96018C
    v1 = addu(v1, a0);
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x49A2FCu);  // $ra = the return address
    lw(a0, v1, 0);
    call_ptr(ctx, jt);
    a0 = s0;
    goto L_0049a39c;
}

// sub_49A400 [RpWorldCreate] -- creates an empty world over the box $a0: the world record (type 7, the material list,
//   root type 2) and one atomic sector covering the box (its lists empty, its bounding boxes = the box), the default
//   sector render callback, linked into the engine's world list, the plugin constructors of world and sector (0x77DDD0 /
//   0x77DDB0), then sub_49A080; the world, or 0 (torn down on a failure; error 0x80000013 on an allocation)
// 0x0049A400 sub_49A400 -- 948 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49A400(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0049a400
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 0x780000;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, v0, -8752);  // 0x77DDD0
    s0 = 0x960000;
    s0 = addiu(s0, 376);  // &0x960178
    v0 = 0x30000;
    a1 = v0 | 0xB;
    lw(v0, s0, 0);  // 0x960178
    jalr(ctx, 0x49A438u, v0.u());
    s2 = v0;
    if (s2 == 0) {
        // 0x0049a690
        charge(ctx, 12);
        v0 = lui(0x8000);
        v1 = 2;
        a0 = v0 | 0x13;
        v0 = 0x780000;
        lw(a1, v0, -8752);  // 0x77DDD0
        link(ctx, 0x49A6A4u);  // $ra first: the delay slot below depends on it
        sw(v1, sp, 0x58);
        call(ctx, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x5C);
        a0 = addiu(sp, 0x58);
        jal(ctx, 0x49A6B0u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    } else {
        // 0x0049a44c
        charge(ctx, 20);
        v0 = 7;
        a0 = addiu(s2, 16);
        sb(v0, s2, 0);
        sb(zero, s2, 1);
        sb(zero, s2, 2);
        sb(zero, s2, 3);
        link(ctx, 0x49A464u);  // $ra first: the delay slot below depends on it
        sw(zero, s2, 4);
        call(ctx, gen::fn_sub_495300_00495300);
        v1 = 2;
        v0 = 0x780000;
        sw(v1, s2, 12);
        sw(zero, s2, 8);
        v1 = 0x30000;
        lw(a0, v0, -8784);  // 0x77DDB0
        lw(v0, s0, 0);
        a1 = v1 | 0xB;
        jalr(ctx, 0x49A488u, v0.u());
        s1 = v0;
        if (s1 == 0) {
            // 0x0049a6c0
            charge(ctx, 15);
            v1 = 2;
            v0 = lui(0x8000);
            sw(v1, sp, 0x50);
            a0 = v0 | 0x13;
            a1 = 4;
            jal(ctx, 0x49A6D0u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x54);
            a0 = addiu(sp, 0x50);
            jal(ctx, 0x49A6DCu, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            a0 = s2;
            jalr(ctx, 0x49A6ECu, v0.u());
            v0 = 0;
        } else {
            // 0x0049a49c
            charge(ctx, 91);
            v0 = si(-1);
            v1 = addiu(s1, 56);
            sw(v0, s1, 0);
            a0 = addiu(s1, 16);
            sw(zero, s1, 52);
            v0 = addiu(s1, 64);
            sw(zero, s1, 120);
            a1 = 0;
            sw(v1, s1, 56);
            a2 = 32;
            sw(v1, s1, 60);
            sw(v0, s1, 64);
            sw(v0, s1, 68);
            sh(zero, s1, 130);
            sh(zero, s1, 132);
            sw(zero, s1, 8);
            sw(zero, s1, 4);
            link(ctx, 0x49A4E0u);  // $ra first: the delay slot below depends on it
            sw(zero, s1, 12);
            call(ctx, gen::fn_memset_00521408);
            sw(zero, s1, 48);
            a3 = 0x4A0000;
            lwc1(f2, s3, 12);
            a2 = 0x960000;
            lwc1(f1, s3, 16);
            a0 = 0x40000;
            lwc1(f0, s3, 20);
            t2 = addiu(s2, 44);
            t1 = addiu(s2, 52);
            t0 = addiu(s2, 60);
            a3 = addiu(a3, -25712);  // &_rpSectorDefaultRenderCallBack
            v1 = 0x780000;
            a2 = addiu(a2, 112);  // &0x960070
            v0 = 0x960000;
            a1 = a0 | 0x507;
            swc1(f2, s1, 84);
            swc1(f1, s1, 88);
            swc1(f0, s1, 92);
            lwc1(f2, s3, 0);
            lwc1(f1, s3, 4);
            lwc1(f0, s3, 8);
            swc1(f2, s1, 72);
            swc1(f1, s1, 76);
            swc1(f0, s1, 80);
            lwc1(f2, s3, 12);
            lwc1(f1, s3, 16);
            lwc1(f0, s3, 20);
            swc1(f2, s1, 108);
            swc1(f1, s1, 112);
            swc1(f0, s1, 116);
            lwc1(f2, s3, 0);
            lwc1(f1, s3, 4);
            lwc1(f0, s3, 8);
            swc1(f2, s1, 96);
            swc1(f1, s1, 100);
            swc1(f0, s1, 104);
            sw(zero, s1, 124);
            sw(s1, s2, 28);
            sw(zero, s2, 32);
            sw(zero, s2, 76);
            sw(zero, s2, 72);
            sw(zero, s2, 68);
            lwc1(f2, s3, 12);
            lwc1(f1, s3, 16);
            lwc1(f0, s3, 20);
            swc1(f2, s2, 92);
            swc1(f1, s2, 96);
            swc1(f0, s2, 100);
            lwc1(f2, s3, 0);
            lwc1(f1, s3, 4);
            lwc1(f0, s3, 8);
            swc1(f2, s2, 80);
            swc1(f1, s2, 84);
            swc1(f0, s2, 88);
            sw(t2, s2, 44);
            sw(t2, s2, 48);
            sw(zero, s2, 36);
            sw(t2, s2, 40);
            sw(t1, s2, 52);
            sw(t1, s2, 56);
            sw(t0, s2, 60);
            sw(t0, s2, 64);
            sw(a3, s2, 104);
            sw(zero, s2, 108);
            lw(s0, v1, -8752);  // 0x77DDD0
            lw(v0, v0, 392);  // 0x960188
            lw(v1, gp, -17552);  // 0x7CE860
            v1 = addu(a2, v1);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x49A5F8u);  // $ra = the return address
            lw(a0, v1, 0);
            call_ptr(ctx, jt);
            if (v0 != 0) {
                // 0x0049a608
                charge(ctx, 20);
                sw(s2, v0, 0);
                a1 = 0x960000;
                sw(s0, v0, 4);
                a1 = addiu(a1, 112);  // &0x960070
                lw(a0, gp, -17552);  // 0x7CE860
                v1 = addiu(v0, 8);
                a0 = addu(a1, a0);
                lw(a0, a0, 4);
                sw(a0, v0, 8);
                lw(a0, gp, -17552);  // 0x7CE860
                a0 = addu(a1, a0);
                a0 = addiu(a0, 4);
                sw(a0, v0, 12);
                lw(v0, gp, -17552);  // 0x7CE860
                v0 = addu(a1, v0);
                lw(v0, v0, 4);
                sw(v1, v0, 4);
                lw(v0, gp, -17552);  // 0x7CE860
                v0 = addu(a1, v0);
                sw(v1, v0, 4);
            }
            // 0x0049a658
            charge(ctx, 12);
            a0 = 0x780000;
            a1 = s2;
            a0 = addiu(a0, -8752);  // &0x77DDD0
            jal(ctx, 0x49A660u, gen::fn_sub_4C64B0_004c64b0);
            a0 = 0x780000;
            a1 = s1;
            a0 = addiu(a0, -8784);  // &0x77DDB0
            jal(ctx, 0x49A670u, gen::fn_sub_4C64B0_004c64b0);
            a0 = s2;
            jal(ctx, 0x49A678u, gen::fn_sub_49A080_0049a080);
            if (v0 == 0) {
                // 0x0049a6fc
                charge(ctx, 10);
                a0 = s2;
                jal(ctx, 0x49A6FCu, gen::fn_sub_499F40_00499f40);
                a0 = s2;
                jal(ctx, 0x49A704u, gen::fn_sub_499FD0_00499fd0);
                a0 = addiu(s2, 16);
                jal(ctx, 0x49A70Cu, gen::fn_sub_495260_00495260);
                lbu(v0, s2, 3);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    // 0x0049a760
                    charge(ctx, 3);
                    lw(a0, s2, 28);
                    if (a0 != 0) {
                        // 0x0049a76c
                        charge(ctx, 2);
                        jal(ctx, 0x49A76Cu, gen::fn_sub_499850_00499850);
                    }
                    // 0x0049a774
                    charge(ctx, 9);
                    a0 = 0x780000;
                    a1 = s2;
                    a0 = addiu(a0, -8752);  // &0x77DDD0
                    jal(ctx, 0x49A77Cu, gen::fn_sub_4C6560_004c6560);
                    v0 = 0x960000;
                    lw(v0, v0, 380);  // 0x96017C
                    a0 = s2;
                    jalr(ctx, 0x49A78Cu, v0.u());
                    v0 = 0;
                } else {
                    // 0x0049a724
                    charge(ctx, 3);
                    lw(a0, s2, 28);
                    if (a0 != 0) {
                        // 0x0049a730
                        charge(ctx, 2);
                        jal(ctx, 0x49A730u, gen::fn_sub_499720_00499720);
                    }
                    // 0x0049a738
                    charge(ctx, 10);
                    a0 = 0x780000;
                    a1 = s2;
                    a0 = addiu(a0, -8752);  // &0x77DDD0
                    jal(ctx, 0x49A740u, gen::fn_sub_4C6560_004c6560);
                    v0 = 0x960000;
                    lw(v0, v0, 380);  // 0x96017C
                    a0 = s2;
                    jalr(ctx, 0x49A750u, v0.u());
                    v0 = 0;
                }
            } else {
                // 0x0049a688
                charge(ctx, 2);
                v0 = s2;
            }
        }
    }
    // 0x0049a798 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_49B3F0 [worldClumpCopyCB] -- the world extension's clump copy callback: when the source clump is in a world (its
//   + gp 0x7CE870 word) the new clump is added to it (sub_49C240); the new clump
// 0x0049B3F0 sub_49B3F0 -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_49B3F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049b3f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, gp, -17536);  // 0x7CE870
    s0 = a0;
    v0 = addu(a1, v0);
    lw(a0, v0, 0);
    if (a0 != 0) {
        // 0x0049b414
        charge(ctx, 2);
        a1 = s0;
        jal(ctx, 0x49B414u, gen::fn_sub_49C240_0049c240);
    }
    // 0x0049b41c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_49E4F0 [nativeInstanceListFree] -- frees a PS2 native instance list (a count and the instance blocks): from the
//   last entry, a block still in use by the DMA chain (+0 / +4 set) is only detached (+16 = 0), an idle one is released
//   (sub_49CC30, sub_4C47E0); the list freed (RwFree)
// 0x0049E4F0 sub_49E4F0 -- 172 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_49E4F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049e4f0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(v0, a0, 0);
    s1 = addiu(v0, -1);
    if (v0 != 0) {
        // 0x0049e518
        charge(ctx, 2);
        v0 = sll(s1, 2);
        s0 = addu(s2, v0);
        for (;;) {
            // 0x0049e520
            charge(ctx, 3);
            lw(s3, s0, 4);
            if (s3 != 0) {
                // 0x0049e52c
                charge(ctx, 3);
                lw(v0, s3, 0);
                if (v0 == 0) {
                    // 0x0049e540
                    charge(ctx, 3);
                    lw(v0, s3, 4);
                    if (v0 != 0) {
                        backedge(ctx);
                        goto L_0049e538;
                    }
                    // 0x0049e54c
                    charge(ctx, 5);
                    a0 = s3;
                    jal(ctx, 0x49E54Cu, gen::fn_sub_49CC30_0049cc30);
                    a0 = s3;
                    jal(ctx, 0x49E554u, gen::fn_sub_4C47E0_004c47e0);
                    goto L_0049e560;
                }
            L_0049e538:
                charge(ctx, 2);
                sw(zero, s3, 16);
            }
        L_0049e560:
            charge(ctx, 4);
            v0 = s1;
            s0 = addiu(s0, -4);
            s1 = addiu(s1, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0049e570
    charge(ctx, 11);
    v0 = 0x960000;
    lw(v0, v0, 380);  // 0x96017C
    a0 = s2;
    jalr(ctx, 0x49E578u, v0.u());
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4A4D60 [nativeDataDestructor] -- the native-data plugin's destructor: the object's instance list (+ the plugin
//   offset $a1) freed (sub_49E4F0) when set; the object
// 0x004A4D60 sub_4A4D60 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4A4D60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a4d60
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    v0 = addu(s0, a1);
    lw(a0, v0, 0);
    if (a0 != 0) {
        // 0x004a4d80
        charge(ctx, 2);
        jal(ctx, 0x4A4D80u, gen::fn_sub_49E4F0_0049e4f0);
    }
    // 0x004a4d88 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4A6630 [rt2dShapeFillGeometry] -- fills an Rt2d shape's geometry from its path: the brush's material (made from
//   its texture and colour on first use, referenced after), the scratch index buffer (0x95F57C, grown as needed), then
//   per closed sub-path its vertices (inset by the path's width), pre-lit colours from the brush's four-corner gradient
//   (flag 1) or white, UVs from the brush's UV gradient, the outline triangulated (sub_4B0FA0) and the triangles added
//   with the material (sub_493210 / sub_493230); the vertex / triangle counters advanced; the shape, or 0
// 0x004A6630 sub_4A6630 -- 1708 bytes; frame 0x140: ra sp+0xA0, fp sp+0x90 (sq), s7 sp+0x80 (sq), s6 sp+0x70 (sq), s5 sp+0x60 (sq), s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
void sub_4A6630(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f20{ctx, 20}, f21{ctx, 21};
    // 0x004a6630
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x140);
    sd(ra, sp, 0xA0);
    sq(fp, sp, 0x90);
    sq(s7, sp, 0x80);
    sq(s6, sp, 0x70);
    sq(s5, sp, 0x60);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    s4 = a1;
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    sw(a0, sp, 0x11C);
    swc1(f20, sp, 0x0);
    sw(a2, sp, 0x118);
    lw(s7, a1, 108);
    sw(a3, sp, 0x114);
    sw(t0, sp, 0x110);
    if (s7 == 0) {
        // 0x004a6b28
        charge(ctx, 5);
        jal(ctx, 0x4A6B28u, gen::fn_sub_494BE0_00494be0);
        lw(a1, s4, 104);
        s7 = v0;
        if (a1 != 0) {
            // 0x004a6b3c
            charge(ctx, 2);
            a0 = s7;
            jal(ctx, 0x4A6B3Cu, gen::fn_sub_494D50_00494d50);
        }
        // 0x004a6b44
        charge(ctx, 4);
        lw(v0, s4, 100);
        v0 = v0 & 0x1;
        if (v0 != 0) {
            // 0x004a6b7c
            charge(ctx, 11);
            lwc1(f0, gp, -20612);  // 0x7CDC6C
            swc1(f0, sp, 0x138);
            lbu(a1, sp, 0x138);
            lbu(a0, sp, 0x139);
            lbu(v1, sp, 0x13A);
            lbu(v0, sp, 0x13B);
            sb(a1, s7, 4);
            sb(a0, s7, 5);
            sb(v1, s7, 6);
            sb(v0, s7, 7);
            backedge(ctx);
        } else {
            // 0x004a6b54
            charge(ctx, 8);
            lbu(a1, s4, 96);
            lbu(a0, s4, 97);
            lbu(v1, s4, 98);
            lbu(v0, s4, 99);
            sb(a1, s7, 4);
            sb(a0, s7, 5);
            sb(v1, s7, 6);
            sb(v0, s7, 7);
        }
        // 0x004a6b74
        charge(ctx, 2);
        sw(s7, s4, 108);
        backedge(ctx);
    } else {
        // 0x004a6680
        charge(ctx, 3);
        lh(v0, s7, 24);
        v0 = addiu(v0, 1);
        sh(v0, s7, 24);
    }
    // 0x004a668c
    charge(ctx, 6);
    lw(v0, sp, 0x11C);
    sw(zero, sp, 0x13C);
    sw(zero, sp, 0x100);
    sw(zero, sp, 0xF0);
    sw(zero, sp, 0xE0);
    lw(s0, v0, 20);
    for (;;) {
        // 0x004a66a4
        charge(ctx, 4);
        lw(v0, s0, 4);
        v1 = si(-1);
        if (v0 == v1) {
            // 0x004a66b4
            charge(ctx, 2);
            link(ctx, 0x4A66B4u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn_sub_4C2120_004c2120);
        }
        // 0x004a66bc
        charge(ctx, 11);
        lw(v1, sp, 0x100);
        a0 = addiu(v0, -3);
        v1 = addu(v1, v0);
        sw(v1, sp, 0x100);
        lw(v1, sp, 0xF0);
        v1 = addu(v1, a0);
        sw(v1, sp, 0xF0);
        lw(v1, sp, 0x13C);
        at = sltu(v1, v0);
        if (at != 0) {
            // 0x004a6ba8
            charge(ctx, 2);
            sw(a0, sp, 0x13C);
            backedge(ctx);
        }
        // 0x004a66e8
        charge(ctx, 5);
        lw(v0, sp, 0x11C);
        lw(s0, s0, 20);
        lw(v0, v0, 20);
        if (s0 == v0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004a66fc
    charge(ctx, 3);
    lw(a0, sp, 0x13C);
    if (a0 != 0) {
        // 0x004a6708
        charge(ctx, 7);
        v0 = 0x960000;
        v1 = sll(a0, 1);
        lw(v0, v0, -2688);  // 0x95F580
        v1 = addu(v1, a0);
        at = sltu(v0, v1);
        if (at != 0) {
            // 0x004a6724
            charge(ctx, 4);
            v0 = 0x960000;
            lw(a0, v0, -2692);  // 0x95F57C
            if (a0 != 0) {
                // 0x004a6734
                charge(ctx, 4);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C
                jalr(ctx, 0x4A673Cu, v0.u());
            }
            // 0x004a6744
            charge(ctx, 14);
            v0 = 0x960000;
            lw(a0, sp, 0x13C);
            sw(zero, v0, -2688);  // 0x95F580
            v0 = 0x30000;
            a1 = v0 | 0x190;
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178
            v1 = sll(a0, 1);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            jalr(ctx, 0x4A6768u, v0.u());
            v1 = 0x960000;
            sw(v0, v1, -2692);  // 0x95F57C
            if (v0 != 0) {
                // 0x004a677c
                charge(ctx, 5);
                lw(a0, sp, 0x13C);
                v0 = 0x960000;
                v1 = sll(a0, 1);
                v1 = addu(v1, a0);
                sw(v1, v0, -2688);  // 0x95F580
                goto L_004a6790;
            }
            // 0x004a6bb0
            charge(ctx, 2);
            v0 = 0;
            // 0x004a6ca4 (the shared epilogue, written out on this path)
            charge(ctx, 14);
            ld(ra, sp, 0xA0);
            lwc1(f21, sp, 0x4);
            lq(fp, sp, 0x90);
            lwc1(f20, sp, 0x0);
            lq(s7, sp, 0x80);
            lq(s6, sp, 0x70);
            lq(s5, sp, 0x60);
            lq(s4, sp, 0x50);
            lq(s3, sp, 0x40);
            lq(s2, sp, 0x30);
            lq(s1, sp, 0x20);
            lq(s0, sp, 0x10);
            sp = addiu(sp, 0x140);
            return;
        }
    L_004a6790:
        charge(ctx, 9);
        v0 = 0x960000;
        v1 = sll(a0, 1);
        lw(v0, v0, -2692);  // 0x95F57C
        v1 = addu(v1, a0);
        a2 = sll(v1, 2);
        a1 = 0;
        sw(v0, sp, 0xE0);
        a0 = v0;
        jal(ctx, 0x4A67ACu, gen::fn_memset_00521408);
    }
    // 0x004a67b4
    charge(ctx, 5);
    v0 = 0x960000;
    lwc1(f21, v0, -4264);  // 0x95EF58
    lw(v0, sp, 0xF0);
    if (v0 != 0) {
        // 0x004a67c8
        charge(ctx, 3);
        lw(v0, sp, 0x100);
        if (v0 != 0) {
            // 0x004a67d4
            charge(ctx, 24);
            lw(v0, sp, 0x114);
            lw(s2, v0, 0);
            lw(v0, sp, 0x118);
            a3 = sll(s2, 1);
            t0 = addu(a3, s2);
            t0 = sll(t0, 2);
            lw(t1, v0, 92);
            lw(v0, sp, 0x110);
            lw(a3, t1, 20);
            lw(a2, v0, 0);
            s1 = addu(a3, t0);
            lw(v0, sp, 0x118);
            a2 = sll(a2, 3);
            lw(a0, v0, 44);
            lw(a1, v0, 48);
            lw(v1, v0, 52);
            s3 = addu(a0, a2);
            a0 = sll(s2, 3);
            v0 = sll(s2, 2);
            s6 = addu(v1, a0);
            s0 = addu(a1, v0);
            lw(v0, sp, 0x11C);
            lw(v0, v0, 20);
            sw(v0, sp, 0xD0);
            for (;;) {
                // 0x004a6834
                charge(ctx, 6);
                lw(v0, sp, 0xD0);
                lwc1(f20, v0, 16);
                lw(v1, v0, 4);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x004a6860
                    charge(ctx, 3);
                    lw(v0, sp, 0xD0);
                    lw(v0, v0, 0);
                    s5 = v0;
                } else {
                    // 0x004a684c
                    charge(ctx, 5);
                    lw(v0, sp, 0xD0);
                    link(ctx, 0x4A6850u);  // $ra first: the delay slot below depends on it
                    lw(a0, v0, 0);
                    call(ctx, gen::fn_sub_4C2090_004c2090);
                    s5 = v0;
                }
                // 0x004a686c
                charge(ctx, 5);
                lw(v0, sp, 0xD0);
                lw(fp, v0, 4);
                v0 = si(-1);
                if (fp == v0) {
                    // 0x004a6880
                    charge(ctx, 4);
                    lw(v0, sp, 0xD0);
                    link(ctx, 0x4A6884u);  // $ra first: the delay slot below depends on it
                    lw(a0, v0, 0);
                    call(ctx, gen::fn_sub_4C2120_004c2120);
                    fp = v0;
                }
                // 0x004a6890
                charge(ctx, 38);
                v1 = addiu(fp, -0x3);
                v0 = addu(s2, fp);
                sw(v1, sp, 0x13C);
                v0 = addiu(v0, -1);
                lwc1(f0, s5, 4);
                sq(v0, sp, 0xB0);
                v0 = addiu(sp, 0x128);
                lw(a0, sp, 0xD0);
                a1 = addiu(sp, 0x120);
                swc1(f0, v0, 0);
                swc1(f0, sp, 0x120);
                v0 = addiu(sp, 0x12C);
                lwc1(f0, s5, 8);
                swc1(f0, v0, 0);
                v0 = addiu(sp, 0x124);
                link(ctx, 0x4A68CCu);  // $ra first: the delay slot below depends on it
                swc1(f0, v0, 0);
                call(ctx, gen::fn_sub_4AC020_004ac020);
                v0 = addiu(sp, 0x128);
                a1 = 0;
                lwc1(f4, v0, 0);
                lwc1(f3, sp, 0x120);
                v0 = 0x3F800000;
                mtc1(v0, f2);
                sub_s(f3, f4, f3);
                v0 = addiu(sp, 0x12C);
                lwc1(f1, v0, 0);
                div_s(f7, f2, f3);
                v0 = addiu(sp, 0x124);
                lwc1(f0, v0, 0);
                sub_s(f0, f1, f0);
                div_s(f8, f2, f0);
                at = sltu(0, fp);
                if (at != 0) {
                    // 0x004a6928
                    charge(ctx, 2);
                    mtc1(zero, f4);
                    v1 = 255;
                    for (;;) {
                        // 0x004a6930
                        charge(ctx, 23);
                        lwc1(f0, s5, 4);
                        v0 = addiu(sp, 0x124);
                        lwc1(f1, s5, 12);
                        lwc1(f2, s5, 16);
                        adda_s(f4, f0);
                        msub_s(f0, f1, f20);
                        swc1(f0, s1, 0);
                        lwc1(f0, s5, 8);
                        mul_s(f2, f2, f20);
                        sub_s(f0, f0, f2);
                        swc1(f0, s1, 4);
                        swc1(f21, s1, 8);
                        lwc1(f3, s1, 0);
                        lw(a0, s4, 100);
                        lwc1(f2, sp, 0x120);
                        lwc1(f0, v0, 0);
                        lwc1(f1, s1, 4);
                        sub_s(f2, f3, f2);
                        v0 = a0 & 0x1;
                        sub_s(f0, f1, f0);
                        mul_s(f5, f2, f7);
                        mul_s(f6, f0, f8);
                        if (v0 == 0) {
                            // 0x004a6bb8
                            charge(ctx, 6);
                            sb(v1, s0, 0);
                            sb(v1, s0, 1);
                            sb(v1, s0, 2);
                            sb(v1, s0, 3);
                            s0 = addiu(s0, 4);
                            backedge(ctx);
                        } else {
                            // 0x004a698c
                            charge(ctx, 59);
                            lwc1(f3, s4, 72);
                            lwc1(f9, s4, 84);
                            lwc1(f10, s4, 80);
                            lwc1(f11, s4, 28);
                            lwc1(f1, s4, 48);
                            lwc1(f2, s4, 76);
                            mul_s(f3, f3, f5);
                            add_s(f3, f3, f1);
                            lwc1(f0, s4, 52);
                            mul_s(f1, f2, f5);
                            add_s(f2, f1, f0);
                            mul_s(f13, f9, f5);
                            lwc1(f0, s4, 60);
                            mul_s(f14, f10, f5);
                            lwc1(f1, s4, 56);
                            lwc1(f10, s4, 32);
                            mul_s(f16, f11, f5);
                            mul_s(f15, f10, f5);
                            lwc1(f12, s4, 24);
                            add_s(f0, f13, f0);
                            lwc1(f9, s4, 36);
                            mul_s(f13, f12, f5);
                            lwc1(f12, s4, 0);
                            add_s(f1, f14, f1);
                            mul_s(f14, f9, f5);
                            lwc1(f11, s4, 4);
                            add_s(f13, f13, f12);
                            lwc1(f10, s4, 8);
                            add_s(f12, f16, f11);
                            lwc1(f9, s4, 12);
                            add_s(f11, f15, f10);
                            sub_s(f12, f12, f2);
                            add_s(f10, f14, f9);
                            sub_s(f9, f13, f3);
                            mul_s(f9, f9, f6);
                            add_s(f9, f9, f3);
                            mul_s(f3, f12, f6);
                            sub_s(f11, f11, f1);
                            add_s(f3, f3, f2);
                            mul_s(f2, f11, f6);
                            sub_s(f10, f10, f0);
                            add_s(f2, f2, f1);
                            mul_s(f1, f10, f6);
                            add_s(f1, f1, f0);
                            cvt_w_s(f0, f9);
                            mfc1(v0, f0);
                            cvt_w_s(f0, f3);
                            sb(v0, s0, 0);
                            mfc1(v0, f0);
                            cvt_w_s(f0, f2);
                            sb(v0, s0, 1);
                            mfc1(v0, f0);
                            cvt_w_s(f0, f1);
                            sb(v0, s0, 2);
                            mfc1(v0, f0);
                            sb(v0, s0, 3);
                            s0 = addiu(s0, 4);
                        }
                        // 0x004a6a78
                        charge(ctx, 3);
                        lw(v0, s4, 104);
                        if (v0 != 0) {
                            // 0x004a6bd0
                            charge(ctx, 26);
                            lwc1(f10, s4, 88);
                            lwc1(f3, s4, 64);
                            lwc1(f9, s4, 92);
                            lwc1(f2, s4, 68);
                            lwc1(f1, s4, 40);
                            lwc1(f0, s4, 44);
                            mul_s(f10, f10, f5);
                            add_s(f10, f10, f3);
                            mul_s(f3, f9, f5);
                            add_s(f9, f3, f2);
                            mul_s(f3, f1, f5);
                            mul_s(f2, f0, f5);
                            lwc1(f1, s4, 16);
                            lwc1(f0, s4, 20);
                            add_s(f1, f3, f1);
                            add_s(f0, f2, f0);
                            sub_s(f1, f1, f10);
                            sub_s(f0, f0, f9);
                            mul_s(f1, f1, f6);
                            mul_s(f0, f0, f6);
                            add_s(f1, f1, f10);
                            add_s(f0, f0, f9);
                            swc1(f1, s6, 0);
                            swc1(f0, s6, 4);
                            s6 = addiu(s6, 8);
                            backedge(ctx);
                        } else {
                            // 0x004a6a84
                            charge(ctx, 1);
                        }
                        // 0x004a6a88
                        charge(ctx, 5);
                        a1 = addiu(a1, 1);
                        v0 = sltu(a1, fp);
                        s5 = addiu(s5, 24);
                        s1 = addiu(s1, 12);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004a6a9c
                    charge(ctx, 1);
                }
                // 0x004a6aa0
                charge(ctx, 8);
                lw(a0, sp, 0xD0);
                lw(a2, sp, 0xE0);
                a1 = addiu(sp, 0x13C);
                jal(ctx, 0x4A6AA8u, gen::fn_sub_4B0FA0_004b0fa0);
                v0 = addiu(fp, -0x3);
                v0 = sltu(0, v0);
                sw(zero, sp, 0xC0);
                if (v0 != 0) {
                    // 0x004a6c38
                    charge(ctx, 1);
                    lw(s5, sp, 0xE0);
                    for (;;) {
                        // 0x004a6c3c
                        charge(ctx, 24);
                        lw(a2, s5, 0);
                        a1 = s3;
                        lw(v1, s5, 4);
                        lw(v0, s5, 8);
                        lw(a0, sp, 0x118);
                        a2 = addu(s2, a2);
                        v1 = addu(s2, v1);
                        a2 = a2 & 0xFFFF;
                        v0 = addu(s2, v0);
                        a3 = v1 & 0xFFFF;
                        t0 = v0 & 0xFFFF;
                        jal(ctx, 0x4A6C64u, gen::fn_sub_493210_00493210);
                        lw(a0, sp, 0x118);
                        a1 = s3;
                        a2 = s7;
                        jal(ctx, 0x4A6C74u, gen::fn_sub_493230_00493230);
                        lw(v0, sp, 0xC0);
                        v1 = addiu(fp, -0x3);
                        s3 = addiu(s3, 8);
                        v0 = addiu(v0, 1);
                        sw(v0, sp, 0xC0);
                        v0 = sltu(v0, v1);
                        s5 = addiu(s5, 12);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004a6c9c
                    charge(ctx, 2);
                    lq(v0, sp, 0xB0);
                    backedge(ctx);
                } else {
                    // 0x004a6ac0
                    charge(ctx, 1);
                    lq(v0, sp, 0xB0);
                }
                // 0x004a6ac4
                charge(ctx, 9);
                s2 = addiu(v0, 1);
                lw(v0, sp, 0xD0);
                lw(v0, v0, 20);
                sw(v0, sp, 0xD0);
                lw(v0, sp, 0x11C);
                lw(v1, v0, 20);
                lw(v0, sp, 0xD0);
                if (v0 == v1) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x004a6ae8
    charge(ctx, 16);
    a0 = s7;
    jal(ctx, 0x4A6AE8u, gen::fn_sub_494CC0_00494cc0);
    lw(v1, sp, 0x114);
    lw(v0, sp, 0x11C);
    lw(a0, v1, 0);
    lw(v1, sp, 0x100);
    a0 = addu(a0, v1);
    lw(v1, sp, 0x114);
    sw(a0, v1, 0);
    lw(v1, sp, 0x110);
    lw(a0, v1, 0);
    lw(v1, sp, 0xF0);
    a0 = addu(a0, v1);
    lw(v1, sp, 0x110);
    sw(a0, v1, 0);
    // 0x004a6ca4 (the shared epilogue, written out on this path)
    charge(ctx, 14);
    ld(ra, sp, 0xA0);
    lwc1(f21, sp, 0x4);
    lq(fp, sp, 0x90);
    lwc1(f20, sp, 0x0);
    lq(s7, sp, 0x80);
    lq(s6, sp, 0x70);
    lq(s5, sp, 0x60);
    lq(s4, sp, 0x50);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x140);
}

// sub_4AA550 [Rt2dOpen] -- opens Rt2d: the device-flags word cleared, then the module opens -- the PS2 pipes' globals,
//   paths (sub_4AC870), brushes, fonts, objects, the CTM stack, the PS2 pipe (rt2dPS2PipeOpen) -- and the default camera
//   (sub_4AA410 with $a0)
// 0x004AA550 sub_4AA550 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4AA550(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004aa550
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    link(ctx, 0x4AA564u);  // $ra first: the delay slot below depends on it
    sw(zero, v0, -4268);
    call(ctx, gen::fn_sub_4B1090_004b1090);
    jal(ctx, 0x4AA56Cu, gen::fn_sub_4AC870_004ac870);
    jal(ctx, 0x4AA574u, gen::fn_sub_4A5400_004a5400);
    jal(ctx, 0x4AA57Cu, gen::fn_sub_4A9330_004a9330);
    jal(ctx, 0x4AA584u, gen::fn_sub_4ADB80_004adb80);
    jal(ctx, 0x4AA58Cu, gen::fn_sub_4AA6C0_004aa6c0);
    jal(ctx, 0x4AA594u, gen::fn_rt2dPS2PipeOpen_004b1100);
    a0 = s0;
    jal(ctx, 0x4AA59Cu, gen::fn_sub_4AA410_004aa410);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4AA5C0 [Rt2dClose] -- closes Rt2d: the module closes in reverse order, then the camera cleared (sub_4AA410(0))
// 0x004AA5C0 sub_4AA5C0 -- 84 bytes; frame 0x10: ra sp+0x0
void sub_4AA5C0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004aa5c0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x4AA5C8u, gen::fn_sub_4B11A0_004b11a0);
    jal(ctx, 0x4AA5D0u, gen::fn_sub_4AA620_004aa620);
    jal(ctx, 0x4AA5D8u, gen::fn_sub_4ADB50_004adb50);
    jal(ctx, 0x4AA5E0u, gen::fn_sub_4A91F0_004a91f0);
    jal(ctx, 0x4AA5E8u, gen::fn_sub_4A53B0_004a53b0);
    jal(ctx, 0x4AA5F0u, gen::fn_sub_4AC7F0_004ac7f0);
    jal(ctx, 0x4AA5F8u, gen::fn_sub_4B1050_004b1050);
    a0 = 0;
    jal(ctx, 0x4AA600u, gen::fn_sub_4AA410_004aa410);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// sub_4AB200 [Rt2dPathMoveto] -- starts a sub-path at ($f12, $f13): when the current sub-path already has nodes a new
//   path is chained after it (sub_4AC570 / sub_4AC5F0) and made current, recursing; else a moveto node {0, x, y} appended
//   to its sList; the path
// 0x004AB200 sub_4AB200 -- 184 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10 (sq), f21 sp+0x4, f20 sp+0x0
void sub_4AB200(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21};
    // 0x004ab200
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f21, sp, 0x4);
    s0 = a0;
    swc1(f20, sp, 0x0);
    lw(v0, a0, 24);
    mov_s(f21, f12);
    lw(a0, v0, 0);
    mov_s(f20, f13);
    jal(ctx, 0x4AB224u, gen::fn_sub_4C2120_004c2120);
    if (v0 != 0) {
        // 0x004ab264
        charge(ctx, 14);
        jal(ctx, 0x4AB264u, gen::fn_sub_4AC570_004ac570);
        lw(v1, s0, 24);
        sw(v0, v1, 20);
        lw(v0, s0, 24);
        link(ctx, 0x4AB278u);  // $ra first: the delay slot below depends on it
        lw(a0, v0, 20);
        call(ctx, gen::fn_sub_4AC5F0_004ac5f0);
        lw(v0, s0, 24);
        mov_s(f12, f21);
        mov_s(f13, f20);
        a0 = s0;
        lw(v0, v0, 20);
        link(ctx, 0x4AB294u);  // $ra first: the delay slot below depends on it
        sw(v0, s0, 24);
        call(ctx, gen::fn_sub_4AB200_004ab200);
    } else {
        // 0x004ab234
        charge(ctx, 12);
        lw(v1, s0, 24);
        v0 = 0x30000;
        lw(a0, v1, 0);
        a1 = v0 | 0x190;
        jal(ctx, 0x4AB240u, gen::fn_sub_4C1E70_004c1e70);
        sw(zero, v0, 0);
        swc1(f21, v0, 4);
        swc1(f20, v0, 8);
        sw(zero, v0, 12);
        sw(zero, v0, 16);
        sw(zero, v0, 20);
    }
    // 0x004ab29c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    v0 = s0;
    ld(ra, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4AC570 [rt2dPathCreate] -- creates an empty Rt2d path from the path free list (0x95ED84): no nodes, closed 0,
//   flat 0, one reference, no next, itself as the current path; converted to its sList form (sub_4AC5F0); the path, or 0
// 0x004AC570 sub_4AC570 -- 116 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4AC570(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ac570
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a0, v0, -4732);  // 0x95ED84
    v0 = 0x30000;
    a1 = v0 | 0x1A1;
    v0 = 0x960000;
    lw(v0, v0, 392);  // 0x960188
    jalr(ctx, 0x4AC594u, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x004ac5a8
        charge(ctx, 10);
        sw(zero, s0, 0);
        v0 = 1;
        sw(zero, s0, 4);
        a0 = s0;
        sw(zero, s0, 8);
        sw(v0, s0, 12);
        sw(zero, s0, 20);
        sw(s0, s0, 24);
        link(ctx, 0x4AC5C8u);  // $ra first: the delay slot below depends on it
        sw(zero, s0, 16);
        call(ctx, gen::fn_sub_4AC5F0_004ac5f0);
    }
    // 0x004ac5d0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4AC5F0 [rt2dPathMakeSList] -- turns a path's node array (+0 / +4 count) into a 24-byte-entry sList (sub_4C1D50),
//   the nodes copied and the array freed, +4 = -1; down the chain of sub-paths (+20); the path, or 0
// 0x004AC5F0 sub_4AC5F0 -- 284 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AC5F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ac5f0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (s3 != 0) {
        // 0x004ac610
        charge(ctx, 4);
        lw(v1, s3, 4);
        v0 = si(-1);
        if (v1 != v0) {
            // 0x004ac620
            charge(ctx, 7);
            v0 = 0x30000;
            a0 = 24;
            a1 = v0 | 0x1A1;
            jal(ctx, 0x4AC628u, gen::fn_sub_4C1D50_004c1d50);
            s2 = v0;
            if (s2 == 0) {
                // 0x004ac6e8
                charge(ctx, 2);
                s3 = 0;
                backedge(ctx);
            } else {
                // 0x004ac63c
                charge(ctx, 4);
                lw(v1, s3, 4);
                v0 = si(-1);
                if (v1 != v0) {
                    // 0x004ac65c
                    charge(ctx, 2);
                    lw(v0, s3, 0);
                    lw(s0, s3, 4);
                } else {
                    // 0x004ac64c
                    charge(ctx, 4);
                    link(ctx, 0x4AC64Cu);  // $ra first: the delay slot below depends on it
                    lw(a0, s3, 0);
                    call(ctx, gen::fn_sub_4C2090_004c2090);
                    lw(s0, s3, 4);
                }
                // 0x004ac664
                charge(ctx, 4);
                s1 = v0;
                v0 = si(-1);
                if (s0 == v0) {
                    // 0x004ac674
                    charge(ctx, 3);
                    link(ctx, 0x4AC674u);  // $ra first: the delay slot below depends on it
                    lw(a0, s3, 0);
                    call(ctx, gen::fn_sub_4C2120_004c2120);
                    s0 = v0;
                }
                // 0x004ac680
                charge(ctx, 2);
                if (s0 != 0) {
                    // 0x004ac688
                    charge(ctx, 7);
                    v0 = 0x30000;
                    a0 = s2;
                    a1 = s0;
                    a2 = v0 | 0x1A1;
                    jal(ctx, 0x4AC694u, gen::fn_sub_4C1F70_004c1f70);
                    if (v0 != 0) {
                        // 0x004ac6a4
                        charge(ctx, 6);
                        a0 = v0;
                        a1 = s1;
                        v0 = sll(s0, 1);
                        v0 = addu(v0, s0);
                        a2 = sll(v0, 3);
                        jal(ctx, 0x4AC6B4u, gen::fn_memcpy_00521250);
                    }
                    // 0x004ac6bc
                    charge(ctx, 4);
                    v0 = 0x960000;
                    lw(v0, v0, 380);  // 0x96017C
                    a0 = s1;
                    jalr(ctx, 0x4AC6C4u, v0.u());
                }
                // 0x004ac6cc
                charge(ctx, 5);
                v0 = si(-1);
                sw(v0, s3, 4);
                sw(s2, s3, 0);
                link(ctx, 0x4AC6D8u);  // $ra first: the delay slot below depends on it
                lw(a0, s3, 20);
                call(ctx, gen::fn_sub_4AC5F0_004ac5f0);
            }
        }
    }
    // 0x004ac6e0
    charge(ctx, 2);
    v0 = s3;
    // 0x004ac6f0
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4AC870 [rt2dPathOpen] -- opens the path module: the 28-byte path free list (sub_4C3B60) at 0x95ED84 and the
//   scratch path 0x95ED88 made in sList form; 1
// 0x004AC870 sub_4AC870 -- 172 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4AC870(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ac870
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x40000;
    sq(s0, sp, 0x0);
    a0 = 28;
    lw(a1, gp, -20524);  // 0x7CDCC4
    a2 = 4;
    lw(a3, gp, -20520);  // 0x7CDCC8
    t0 = addiu(t0, -1648);  // &0x95F990
    t1 = v0 | 0x1A1;
    jal(ctx, 0x4AC898u, gen::fn_sub_4C3B60_004c3b60);
    v1 = 0x960000;
    a0 = v0;
    sw(v0, v1, -4732);  // 0x95ED84
    v0 = 0x30000;
    a1 = v0 | 0x1A1;
    v0 = 0x960000;
    lw(v0, v0, 392);  // 0x960188
    jalr(ctx, 0x4AC8BCu, v0.u());
    s0 = v0;
    if (s0 != 0) {
        // 0x004ac8d0
        charge(ctx, 10);
        sw(zero, s0, 0);
        v0 = 1;
        sw(zero, s0, 4);
        a0 = s0;
        sw(zero, s0, 8);
        sw(v0, s0, 12);
        sw(zero, s0, 20);
        sw(s0, s0, 24);
        link(ctx, 0x4AC8F0u);  // $ra first: the delay slot below depends on it
        sw(zero, s0, 16);
        call(ctx, gen::fn_sub_4AC5F0_004ac5f0);
    }
    // 0x004ac8f8
    charge(ctx, 9);
    v0 = 0x960000;
    a0 = s0;
    link(ctx, 0x4AC900u);  // $ra first: the delay slot below depends on it
    sw(s0, v0, -4728);
    call(ctx, gen::fn_sub_4AC5F0_004ac5f0);
    ld(ra, sp, 0x10);
    v0 = 1;
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4AC920 [rt2dPathStreamReadBody] -- reads a path's body over an existing path: the old nodes and sub-paths
//   released, the count / closed / flat flags / inset from the header, the 24-byte nodes read into a new array, the
//   chained sub-paths (chunk 417, sub_4ACB90) when flagged, each sub-path's current pointer set; the path, or 0
// 0x004AC920 sub_4AC920 -- 492 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AC920(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x004ac920
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = si(-1);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    lw(v1, a0, 4);
    s1 = a2;
    if (v1 == v0) {
        // 0x004aca70
        charge(ctx, 4);
        link(ctx, 0x4ACA70u);  // $ra first: the delay slot below depends on it
        lw(a0, s3, 0);
        call(ctx, gen::fn_sub_4C20B0_004c20b0);
        sw(zero, s3, 0);
        backedge(ctx);
    } else {
        // 0x004ac954
        charge(ctx, 3);
        lw(a0, s3, 0);
        if (a0 != 0) {
            // 0x004ac960
            charge(ctx, 4);
            v0 = 0x960000;
            lw(v0, v0, 380);  // 0x96017C
            jalr(ctx, 0x4AC968u, v0.u());
        }
        // 0x004ac970
        charge(ctx, 1);
        sw(zero, s3, 0);
    }
    // 0x004ac974
    charge(ctx, 4);
    sw(zero, s3, 4);
    lw(a0, s3, 20);
    if (a0 != 0) {
        // 0x004ac984
        charge(ctx, 5);
        jal(ctx, 0x4AC984u, gen::fn_sub_4AC410_004ac410);
        lw(a0, s3, 20);
        if (a0 != 0) {
            // 0x004ac998
            charge(ctx, 4);
            jal(ctx, 0x4AC998u, gen::fn_sub_4AB0E0_004ab0e0);
            if (v0 != 0) {
                // 0x004ac9a8
                charge(ctx, 4);
                a0 = v0;
                jal(ctx, 0x4AC9A8u, gen::fn_sub_4AB0E0_004ab0e0);
                a0 = v0;
                jal(ctx, 0x4AC9B0u, gen::fn_sub_4AC390_004ac390);
            }
        }
        // 0x004ac9b8
        charge(ctx, 1);
        sw(zero, s3, 20);
    }
    // 0x004ac9bc
    charge(ctx, 25);
    sw(s3, s3, 24);
    v0 = 0x30000;
    lw(v1, s2, 4);
    a1 = v0 | 0x1A1;
    v0 = 0x960000;
    sw(v1, s3, 4);
    lw(v1, s2, 8);
    v1 = v1 & 0x1;
    v1 = sltu(0, v1);
    sw(v1, s3, 8);
    lw(v1, s2, 8);
    v1 = v1 & 0x2;
    v1 = sltu(0, v1);
    sw(v1, s3, 12);
    lwc1(f0, s2, 12);
    swc1(f0, s3, 16);
    lw(a0, s3, 4);
    lw(v0, v0, 376);  // 0x960178
    v1 = sll(a0, 1);
    v1 = addu(v1, a0);
    a0 = sll(v1, 3);
    jalr(ctx, 0x4ACA0Cu, v0.u());
    s0 = v0;
    if (s0 == 0) {
        // 0x004aca80
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004aca20
        charge(ctx, 3);
        lw(v1, s3, 4);
        if (v1 != 0) {
            // 0x004aca88
            charge(ctx, 9);
            v0 = sll(v1, 1);
            a0 = s1;
            v0 = addu(v0, v1);
            a1 = s0;
            s4 = sll(v0, 3);
            a2 = s4;
            jal(ctx, 0x4ACA9Cu, gen::fn_sub_4C5250_004c5250);
            if (s4 == v0) {
                backedge(ctx);
                goto L_004aca2c;
            }
            // 0x004acaac
            charge(ctx, 2);
            v0 = 0;
            // 0x004acaec (the shared epilogue, written out on this path)
            charge(ctx, 8);
            ld(ra, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_004aca2c:
        charge(ctx, 5);
        sw(s0, s3, 0);
        lw(v0, s2, 8);
        v0 = v0 & 0x4;
        if (v0 != 0) {
            // 0x004acab4
            charge(ctx, 7);
            a0 = s1;
            a1 = 417;
            a2 = 0;
            a3 = 0;
            jal(ctx, 0x4ACAC0u, gen::fn_sub_4C1600_004c1600);
            if (v0 != 0) {
                // 0x004acad8
                charge(ctx, 4);
                a0 = s1;
                jal(ctx, 0x4ACAD8u, gen::fn_sub_4ACB90_004acb90);
                sw(v0, s3, 20);
                backedge(ctx);
                goto L_004aca40;
            }
            // 0x004acad0
            charge(ctx, 2);
            v0 = 0;
            // 0x004acaec (the shared epilogue, written out on this path)
            charge(ctx, 8);
            ld(ra, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_004aca40:
        charge(ctx, 3);
        lw(v0, s3, 20);
        if (v0 == 0) {
            // 0x004acae8
            charge(ctx, 1);
            v0 = s3;
        } else {
            for (;;) {
                // 0x004aca4c
                charge(ctx, 7);
                sw(s3, v0, 24);
                lw(v0, v0, 20);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004aca68
            charge(ctx, 2);
            v0 = s3;
        }
    }
    // 0x004acaec (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4ACB10 [rt2dPathStreamRead] -- reads a path: the 16-byte header, the body (sub_4AC920) when its version is 1; the
//   path, or 0
// 0x004ACB10 sub_4ACB10 -- 128 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4ACB10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004acb10
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a2 = 16;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = s0;
    a1 = addiu(sp, 0x30);
    jal(ctx, 0x4ACB30u, gen::fn_sub_4C5250_004c5250);
    v1 = 16;
    if (v0 != v1) {
        // 0x004acb5c
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004acb44
        charge(ctx, 4);
        lw(v1, sp, 0x30);
        v0 = 1;
        if (v1 == v0) {
            // 0x004acb64
            charge(ctx, 6);
            a0 = s1;
            a2 = s0;
            a1 = addiu(sp, 0x30);
            jal(ctx, 0x4ACB6Cu, gen::fn_sub_4AC920_004ac920);
            s1 = v0;
            backedge(ctx);
        }
        // 0x004acb54
        charge(ctx, 2);
        v0 = s1;
    }
    // 0x004acb7c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4ADBD0 [rt2dObjectDestroyByType] -- destroys an Rt2d object by its type: 4 text (sub_4AD6A0), 3 pick region
//   (sub_4AE1E0), 2 shape (sub_4AF940), 1 scene (sub_4AE4E0); else 0
// 0x004ADBD0 sub_4ADBD0 -- 152 bytes; frame 0x10: ra sp+0x0
void sub_4ADBD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004adbd0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 4;
    sd(ra, sp, 0x0);
    lw(v1, a0, 0);
    if (v1 == v0) {
        // 0x004adc54
        charge(ctx, 2);
        jal(ctx, 0x4ADC54u, gen::fn_sub_4AD6A0_004ad6a0);
    L_004adc5c:
        charge(ctx, 1);
        ld(ra, sp, 0x0);
    } else {
        // 0x004adbe8
        charge(ctx, 3);
        v0 = 3;
        if (v1 == v0) {
            // 0x004adc44
            charge(ctx, 4);
            jal(ctx, 0x4ADC44u, gen::fn_sub_4AE1E0_004ae1e0);
            goto L_004adc5c;
        }
        // 0x004adbf4
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x004adc34
            charge(ctx, 4);
            jal(ctx, 0x4ADC34u, gen::fn_sub_4AF940_004af940);
            goto L_004adc5c;
        }
        // 0x004adc00
        charge(ctx, 3);
        v0 = 1;
        if (v1 != v0) {
            // 0x004adc0c
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x004adc1c
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004adc14
                charge(ctx, 2);
                v0 = 0;
            }
            goto L_004adc5c;
        }
        // 0x004adc24
        charge(ctx, 4);
        jal(ctx, 0x4ADC24u, gen::fn_sub_4AE4E0_004ae4e0);
        ld(ra, sp, 0x0);
    }
    // 0x004adc60 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// sub_4ADE90 [rt2dObjectStreamReadByType] -- reads an Rt2d object's body by its type: 4 text (sub_4AD940), 3 pick
//   region (sub_4AE270), 2 shape (sub_4AFFE0), 1 scene (sub_4AEBF0); the object, or 0 for another type
// 0x004ADE90 sub_4ADE90 -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4ADE90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ade90
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 4;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 0);
    s0 = a0;
    if (v1 == v0) {
        // 0x004adf08
        charge(ctx, 2);
        jal(ctx, 0x4ADF08u, gen::fn_sub_4AD940_004ad940);
    L_004adf10:
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x004adeac
        charge(ctx, 3);
        v0 = 3;
        if (v1 == v0) {
            // 0x004adef8
            charge(ctx, 4);
            jal(ctx, 0x4ADEF8u, gen::fn_sub_4AE270_004ae270);
            goto L_004adf10;
        }
        // 0x004adeb8
        charge(ctx, 3);
        v0 = 2;
        if (v1 == v0) {
            // 0x004adee8
            charge(ctx, 4);
            jal(ctx, 0x4ADEE8u, gen::fn_sub_4AFFE0_004affe0);
            goto L_004adf10;
        }
        // 0x004adec4
        charge(ctx, 3);
        v0 = 1;
        if (v1 == v0) {
            // 0x004aded8
            charge(ctx, 4);
            jal(ctx, 0x4ADED8u, gen::fn_sub_4AEBF0_004aebf0);
            v0 = s0;
        } else {
            // 0x004aded0
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x004adf14 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4AE3B0 [rt2dShapeRepListStreamRead] -- reads a scene's shared shape representations: the count, an array
//   (RwMalloc; error 0x80000013 on failure) and each representation (sub_4AF760); the list, or 0
// 0x004AE3B0 sub_4AE3B0 -- 292 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AE3B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ae3b0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    a2 = 4;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    s2 = a1;
    sq(s1, sp, 0x10);
    a0 = s2;
    a1 = addiu(sp, 0x5C);
    link(ctx, 0x4AE3D8u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1910_004c1910);
    if (v0 == 0) {
        // 0x004ae408
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004ae3e8
        charge(ctx, 5);
        lw(v0, sp, 0x5C);
        sw(v0, s3, 4);
        lw(v0, sp, 0x5C);
        if (v0 == 0) {
            // 0x004ae3fc
            charge(ctx, 1);
            sw(zero, s3, 0);
            goto L_004ae400;
        }
        // 0x004ae410
        charge(ctx, 11);
        a0 = sll(v0, 2);
        v0 = 0x30000;
        a1 = v0 | 0x190;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178
        jalr(ctx, 0x4AE424u, v0.u());
        sw(v0, s3, 0);
        lw(v0, s3, 0);
        if (v0 == 0) {
            // 0x004ae48c
            charge(ctx, 11);
            lw(v1, sp, 0x5C);
            v0 = 400;
            sw(v0, sp, 0x50);
            v0 = lui(0x8000);
            a0 = v0 | 0x13;
            a1 = sll(v1, 2);
            jal(ctx, 0x4AE4A0u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x54);
            a0 = addiu(sp, 0x50);
            jal(ctx, 0x4AE4ACu, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        } else {
            // 0x004ae43c
            charge(ctx, 4);
            lw(v0, sp, 0x5C);
            at = sltu(0, v0);
            s1 = 0;
            if (at != 0) {
                // 0x004ae44c
                charge(ctx, 1);
                s0 = 0;
                for (;;) {
                    // 0x004ae450
                    charge(ctx, 6);
                    a0 = s2;
                    jal(ctx, 0x4AE450u, gen::fn_sub_4AF760_004af760);
                    lw(v1, s3, 0);
                    v1 = addu(v1, s0);
                    sw(v0, v1, 0);
                    if (v0 == 0) {
                        goto L_004ae468_9;
                    }
                    // 0x004ae470
                    charge(ctx, 5);
                    lw(v0, sp, 0x5C);
                    s1 = addiu(s1, 1);
                    v0 = sltu(s1, v0);
                    s0 = addiu(s0, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004ae484
                charge(ctx, 2);
                backedge(ctx);
                goto L_004ae400;
            }
            backedge(ctx);
        L_004ae400:
            charge(ctx, 2);
            v0 = s3;
        }
    }
    // 0x004ae4b8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004ae468_9:
    charge(ctx, 2);
    v0 = 0;
    // 0x004ae4b8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4AE5A0 [Rt2dSceneDestroy] -- destroys a scene: as sub_4AE4E0, then the object returned to the object free list
//   (0x95ED8C); 1 when all went well
// 0x004AE5A0 sub_4AE5A0 -- 232 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AE5A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ae5a0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = sltu(0, s1);
    if (s0 != 0) {
        // 0x004ae5c8
        charge(ctx, 3);
        lw(a0, s1, 184);
        s0 = 1;
        if (a0 != 0) {
            // 0x004ae5d4
            charge(ctx, 3);
            jal(ctx, 0x4AE5D4u, gen::fn_sub_4C20B0_004c20b0);
            s0 = v0;
        }
        // 0x004ae5e0
        charge(ctx, 12);
        link(ctx, 0x4AE5E0u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, 176);
        call(ctx, gen::fn_sub_4C2090_004c2090);
        lw(a1, s1, 180);
        lw(a0, s1, 176);
        v1 = sll(a1, 4);
        v1 = addu(v1, a1);
        v1 = sll(v1, 4);
        s2 = addu(v0, v1);
        jal(ctx, 0x4AE5FCu, gen::fn_sub_4C2090_004c2090);
        s3 = v0;
        if (s3 != s2) {
            for (;;) {
                // 0x004ae610
                charge(ctx, 3);
                s0 = sltu(0, s0);
                if (s0 != 0) {
                    // 0x004ae61c
                    charge(ctx, 3);
                    a0 = s3;
                    jal(ctx, 0x4AE61Cu, gen::fn_sub_4ADBD0_004adbd0);
                    s0 = sltu(0, v0);
                }
                // 0x004ae628
                charge(ctx, 3);
                s3 = addiu(s3, 272);
                if (s3 == s2) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004ae634
            charge(ctx, 1);
        }
        // 0x004ae638
        charge(ctx, 3);
        s0 = sltu(0, s0);
        if (s0 != 0) {
            // 0x004ae644
            charge(ctx, 3);
            link(ctx, 0x4AE644u);  // $ra first: the delay slot below depends on it
            lw(a0, s1, 176);
            call(ctx, gen::fn_sub_4C20B0_004c20b0);
            s0 = sltu(0, v0);
        }
        // 0x004ae650
        charge(ctx, 6);
        v0 = 0x960000;
        lw(a0, v0, -4724);  // 0x95ED8C
        v0 = 0x960000;
        lw(v0, v0, 396);  // 0x96018C
        a1 = s1;
        jalr(ctx, 0x4AE660u, v0.u());
    }
    // 0x004ae668 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    v0 = s0;
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4AE790 [rt2dSceneUnlock] -- unlocks a scene being built (flag 1 of +8): the child pointer array replaced by an
//   sList of 272-byte objects (each copied, sub_4ADC90, and its old record released, sub_4ADC70), the reference sList
//   (+184, 8-byte entries) pointing at each child, the scene's bounds updated (sub_4AE690); the scene
// 0x004AE790 sub_4AE790 -- 348 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AE790(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ae790
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 1;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 8);
    v1 = v1 & 0x1;
    s2 = a0;
    if (v1 == v0) {
        // 0x004ae7c4
        charge(ctx, 12);
        v0 = 0x30000;
        a0 = 272;
        a1 = v0 | 0x1A3;
        jal(ctx, 0x4AE7CCu, gen::fn_sub_4C1D50_004c1d50);
        lw(a0, s2, 176);
        s0 = v0;
        jal(ctx, 0x4AE7D8u, gen::fn_sub_4C2090_004c2090);
        lw(v1, s2, 180);
        v1 = sll(v1, 2);
        s3 = addu(v0, v1);
        s1 = v0;
        if (v0 != s3) {
            for (;;) {
                // 0x004ae7f4
                charge(ctx, 7);
                v0 = 0x30000;
                a0 = s0;
                a1 = v0 | 0x1A3;
                jal(ctx, 0x4AE7FCu, gen::fn_sub_4C1E70_004c1e70);
                lw(a1, s1, 0);
                if (a1 != 0) {
                    // 0x004ae810
                    charge(ctx, 4);
                    a0 = v0;
                    jal(ctx, 0x4AE810u, gen::fn_sub_4ADC90_004adc90);
                    link(ctx, 0x4AE818u);  // $ra first: the delay slot below depends on it
                    lw(a0, s1, 0);
                    call(ctx, gen::fn_sub_4ADC70_004adc70);
                }
                // 0x004ae820
                charge(ctx, 3);
                s1 = addiu(s1, 4);
                if (s1 == s3) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004ae82c
            charge(ctx, 1);
        }
        // 0x004ae830
        charge(ctx, 15);
        link(ctx, 0x4AE830u);  // $ra first: the delay slot below depends on it
        lw(a0, s2, 176);
        call(ctx, gen::fn_sub_4C20B0_004c20b0);
        sw(s0, s2, 176);
        v0 = 0x30000;
        lw(a2, s2, 8);
        v1 = si(-2);
        a1 = v0 | 0x190;
        a0 = 8;
        v0 = a2 & v1;
        link(ctx, 0x4AE854u);  // $ra first: the delay slot below depends on it
        sw(v0, s2, 8);
        call(ctx, gen::fn_sub_4C1D50_004c1d50);
        sw(v0, s2, 184);
        lw(a1, s2, 180);
        if (a1 == 0) {
            backedge(ctx);
        } else {
            // 0x004ae86c
            charge(ctx, 14);
            lw(a0, s2, 184);
            v0 = 0x30000;
            a2 = v0 | 0x190;
            jal(ctx, 0x4AE874u, gen::fn_sub_4C1F70_004c1f70);
            link(ctx, 0x4AE87Cu);  // $ra first: the delay slot below depends on it
            lw(a0, s2, 184);
            call(ctx, gen::fn_sub_4C2090_004c2090);
            lw(a0, s2, 176);
            s0 = v0;
            jal(ctx, 0x4AE888u, gen::fn_sub_4C2090_004c2090);
            lw(v1, s2, 180);
            v1 = sll(v1, 3);
            v1 = addu(s0, v1);
            if (s0 != v1) {
                for (;;) {
                    // 0x004ae8a4
                    charge(ctx, 7);
                    sw(v0, s0, 0);
                    s0 = addiu(s0, 8);
                    v0 = addiu(v0, 272);
                    if (s0 == v1) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004ae8c0
            charge(ctx, 4);
            a0 = s2;
            jal(ctx, 0x4AE8C0u, gen::fn_sub_4AE690_004ae690);
            sw(zero, s2, 188);
            backedge(ctx);
        }
    }
    // 0x004ae7bc
    charge(ctx, 2);
    v0 = s2;
    // 0x004ae8d0
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4AEBF0 [rt2dSceneStreamReadBody] -- reads a scene's children: the count, the child array (zeroed), the scene
//   locked then unlocked (sub_4AE790); each child's header (sub_4ADDB0) and body (sub_4ADE90) read, with the shared
//   representations of $a2 or of the scene's own list (sub_4AE3B0, released after with sub_4AF130); the reference array
//   re-pointed, the bounds (sub_4AE690); the scene, or 0
// 0x004AEBF0 sub_4AEBF0 -- 684 bytes; frame 0x70: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AEBF0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004aebf0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = a2;
    s0 = a0;
    a1 = addiu(sp, 0x6C);
    a0 = s2;
    a2 = 4;
    link(ctx, 0x4AEC20u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x6C);
    call(ctx, gen::fn_sub_4C5250_004c5250);
    a0 = 4;
    if (v0 == a0) {
        // 0x004aec3c
        charge(ctx, 7);
        lw(s3, sp, 0x6C);
        v0 = 0x30000;
        a1 = v0 | 0x190;
        link(ctx, 0x4AEC48u);  // $ra first: the delay slot below depends on it
        sw(s3, s0, 180);
        call(ctx, gen::fn_sub_4C1D50_004c1d50);
        sw(v0, s0, 176);
        if (s3 != 0) {
            // 0x004aec58
            charge(ctx, 11);
            lw(a0, s0, 176);
            v0 = 0x30000;
            a1 = s3;
            a2 = v0 | 0x190;
            jal(ctx, 0x4AEC64u, gen::fn_sub_4C1F70_004c1f70);
            link(ctx, 0x4AEC6Cu);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 176);
            call(ctx, gen::fn_sub_4C2090_004c2090);
            a2 = sll(s3, 2);
            a0 = v0;
            a1 = 0;
            jal(ctx, 0x4AEC7Cu, gen::fn_memset_00521408);
        }
        // 0x004aec84
        charge(ctx, 9);
        sw(zero, s0, 184);
        a0 = s0;
        sw(zero, s0, 188);
        lw(v0, s0, 8);
        v0 = v0 | 0x1;
        link(ctx, 0x4AEC98u);  // $ra first: the delay slot below depends on it
        sw(v0, s0, 8);
        call(ctx, gen::fn_sub_4AE790_004ae790);
        if (s1 != 0) {
            // 0x004aeca8
            charge(ctx, 11);
            lw(a0, s0, 176);
            sw(s2, sp, 0x60);
            link(ctx, 0x4AECB0u);  // $ra first: the delay slot below depends on it
            sw(s1, sp, 0x64);
            call(ctx, gen::fn_sub_4C2090_004c2090);
            lw(a0, s0, 180);
            v1 = sll(a0, 4);
            v1 = addu(v1, a0);
            v1 = sll(v1, 4);
            s2 = addu(v0, v1);
            s1 = v0;
            if (v0 != s2) {
                // 0x004aecd4
                charge(ctx, 2);
                s3 = addiu(sp, 0x60);
                if (v0 != s2) {
                    for (;;) {
                        // 0x004aecdc
                        charge(ctx, 5);
                        lw(a1, s3, 0);
                        a0 = s1;
                        jal(ctx, 0x4AECE0u, gen::fn_sub_4ADDB0_004addb0);
                        if (v0 != 0) {
                            // 0x004aed4c
                            charge(ctx, 6);
                            lw(a1, s3, 0);
                            lw(a2, s3, 4);
                            a0 = s1;
                            jal(ctx, 0x4AED54u, gen::fn_sub_4ADE90_004ade90);
                            backedge(ctx);
                        }
                        // 0x004aecf0
                        charge(ctx, 3);
                        s1 = addiu(s1, 272);
                        if (s1 == s2) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004aecfc
                    charge(ctx, 1);
                }
            }
            goto L_004aed00;
        }
        // 0x004aed68
        charge(ctx, 5);
        a0 = addiu(sp, 0x58);
        a1 = s2;
        jal(ctx, 0x4AED6Cu, gen::fn_sub_4AE3B0_004ae3b0);
        if (v0 != 0) {
            // 0x004aed84
            charge(ctx, 12);
            lw(a0, s0, 176);
            v0 = addiu(sp, 0x58);
            sw(v0, sp, 0x54);
            link(ctx, 0x4AED90u);  // $ra first: the delay slot below depends on it
            sw(s2, sp, 0x50);
            call(ctx, gen::fn_sub_4C2090_004c2090);
            lw(a0, s0, 180);
            v1 = sll(a0, 4);
            v1 = addu(v1, a0);
            v1 = sll(v1, 4);
            s2 = addu(v0, v1);
            s1 = v0;
            if (v0 != s2) {
                // 0x004aedb4
                charge(ctx, 2);
                s3 = addiu(sp, 0x50);
                if (v0 != s2) {
                    for (;;) {
                        // 0x004aedbc
                        charge(ctx, 5);
                        lw(a1, s3, 0);
                        a0 = s1;
                        jal(ctx, 0x4AEDC0u, gen::fn_sub_4ADDB0_004addb0);
                        if (v0 != 0) {
                            // 0x004aee2c
                            charge(ctx, 6);
                            lw(a1, s3, 0);
                            lw(a2, s3, 4);
                            a0 = s1;
                            jal(ctx, 0x4AEE34u, gen::fn_sub_4ADE90_004ade90);
                            backedge(ctx);
                        }
                        // 0x004aedd0
                        charge(ctx, 3);
                        s1 = addiu(s1, 272);
                        if (s1 == s2) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004aeddc
                    charge(ctx, 1);
                }
            }
            // 0x004aede0
            charge(ctx, 4);
            s1 = addiu(sp, 0x5C);
            lw(v0, s1, 0);
            if (v0 == 0) {
                backedge(ctx);
            } else {
                // 0x004aedf0
                charge(ctx, 3);
                at = sltu(0, v0);
                s3 = 0;
                if (at != 0) {
                    // 0x004aedfc
                    charge(ctx, 1);
                    s2 = 0;
                    for (;;) {
                        // 0x004aee00
                        charge(ctx, 9);
                        lw(v0, sp, 0x58);
                        v0 = addu(v0, s2);
                        link(ctx, 0x4AEE08u);  // $ra first: the delay slot below depends on it
                        lw(a0, v0, 0);
                        call(ctx, gen::fn_sub_4AF130_004af130);
                        lw(v0, s1, 0);
                        s3 = addiu(s3, 1);
                        v0 = sltu(s3, v0);
                        s2 = addiu(s2, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004aee24
                    charge(ctx, 2);
                }
                // 0x004aee48
                charge(ctx, 6);
                v0 = 0x960000;
                lw(v0, v0, 380);  // 0x96017C
                jt = v0.u();  // the target, read before the delay slot
                link(ctx, 0x4AEE50u);  // $ra = the return address
                lw(a0, sp, 0x58);
                call_ptr(ctx, jt);
                backedge(ctx);
            }
        L_004aed00:
            charge(ctx, 10);
            link(ctx, 0x4AED00u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 184);
            call(ctx, gen::fn_sub_4C2090_004c2090);
            lw(v1, s0, 180);
            s2 = v0;
            lw(a0, s0, 176);
            v1 = sll(v1, 3);
            s1 = addu(v0, v1);
            jal(ctx, 0x4AED18u, gen::fn_sub_4C2090_004c2090);
            if (s2 == s1) {
                // 0x004aee60
                charge(ctx, 1);
                a0 = s0;
            } else {
                for (;;) {
                    // 0x004aed28
                    charge(ctx, 7);
                    sw(v0, s2, 0);
                    s2 = addiu(s2, 8);
                    v0 = addiu(v0, 272);
                    if (s2 == s1) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004aed44
                charge(ctx, 2);
                a0 = s0;
            }
            // 0x004aee64
            charge(ctx, 7);
            jal(ctx, 0x4AEE64u, gen::fn_sub_4AE690_004ae690);
            lw(a0, s0, 8);
            v1 = si(-2);
            v0 = s0;
            v1 = a0 & v1;
            sw(v1, s0, 8);
        } else {
            // 0x004aed7c
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x004aec34
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004aee80 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// sub_4AEEA0 [Rt2dSceneStreamRead] -- reads a scene object: a new object (sub_4ADCA0) initialised as a scene (type 1),
//   its header (sub_4ADDB0) and body (sub_4AEBF0); a failed body destroys it (sub_4AE4E0, the free list 0x95ED8C); the
//   scene, or 0
// 0x004AEEA0 sub_4AEEA0 -- 172 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AEEA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004aeea0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x4AEEB0u, gen::fn_sub_4ADCA0_004adca0);
    s1 = v0;
    a1 = 1;
    a0 = s1;
    jal(ctx, 0x4AEEC0u, gen::fn_sub_4ADCC0_004adcc0);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x4AEECCu, gen::fn_sub_4ADDB0_004addb0);
    if (v0 != 0) {
        // 0x004aeee4
        charge(ctx, 7);
        a1 = s0;
        a0 = s1;
        a2 = 0;
        jal(ctx, 0x4AEEECu, gen::fn_sub_4AEBF0_004aebf0);
        s0 = v0;
        if (s0 == 0) {
            // 0x004aef08
            charge(ctx, 2);
            if (s1 == 0) {
                backedge(ctx);
            } else {
                // 0x004aef10
                charge(ctx, 10);
                a0 = s1;
                jal(ctx, 0x4AEF10u, gen::fn_sub_4AE4E0_004ae4e0);
                v0 = 0x960000;
                lw(a0, v0, -4724);  // 0x95ED8C
                v0 = 0x960000;
                lw(v0, v0, 396);  // 0x96018C
                a1 = s1;
                jalr(ctx, 0x4AEF28u, v0.u());
                backedge(ctx);
            }
        }
        // 0x004aef00
        charge(ctx, 2);
        v0 = s0;
    } else {
        // 0x004aeedc
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004aef38 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4AF130 [rt2dShapeRepDestroy] -- releases a shared shape representation: the reference count (+4) down; at 0 each
//   node's path and brush released (sub_4AC390 / sub_4A5540), the node sList, the geometry (RpGeometryDestroy), the
//   record freed; 1 when freed, else 0
// 0x004AF130 sub_4AF130 -- 216 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AF130(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004af130
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 4);
    s0 = a0;
    v0 = addiu(v0, -1);
    sw(v0, a0, 4);
    if (v0 == 0) {
        // 0x004af164
        charge(ctx, 9);
        link(ctx, 0x4AF164u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);
        call(ctx, gen::fn_sub_4C2120_004c2120);
        lw(a0, s0, 0);
        s1 = v0;
        jal(ctx, 0x4AF170u, gen::fn_sub_4C2090_004c2090);
        at = slt(0, s1);
        s2 = v0;
        s3 = 0;
        if (at != 0) {
            for (;;) {
                // 0x004af188
                charge(ctx, 3);
                lw(a0, s2, 4);
                if (a0 != 0) {
                    // 0x004af194
                    charge(ctx, 5);
                    jal(ctx, 0x4AF194u, gen::fn_sub_4AC390_004ac390);
                    link(ctx, 0x4AF19Cu);  // $ra first: the delay slot below depends on it
                    lw(a0, s2, 8);
                    call(ctx, gen::fn_sub_4A5540_004a5540);
                }
                // 0x004af1a8
                charge(ctx, 4);
                s3 = addiu(s3, 1);
                v0 = slt(s3, s1);
                s2 = addiu(s2, 12);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004af1b8
        charge(ctx, 5);
        link(ctx, 0x4AF1B8u);  // $ra first: the delay slot below depends on it
        lw(a0, s0, 0);
        call(ctx, gen::fn_sub_4C20B0_004c20b0);
        lw(a0, s0, 8);
        if (a0 != 0) {
            // 0x004af1cc
            charge(ctx, 3);
            jal(ctx, 0x4AF1CCu, gen::fn_sub_493B60_00493b60);
            sw(zero, s0, 8);
        }
        // 0x004af1d8
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        a0 = s0;
        jalr(ctx, 0x4AF1E0u, v0.u());
        v0 = 1;
    } else {
        // 0x004af15c
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004af1ec (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4AF210 [rt2dShapeRepBuildGeometry] -- builds a shape representation's geometry: a geometry (RpGeometryCreate) for
//   the counted vertices and triangles with the format flags $a3, each node's path filled (sub_4A6630, node flag 1) or
//   stroked (sub_4ACE80) with its brush, then the bounding sphere (sub_492E20) and the unlock (sub_4933D0); the geometry,
//   or 0
// 0x004AF210 sub_4AF210 -- 300 bytes; frame 0x70: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AF210(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x004af210
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    lw(v0, a0, 0);
    s1 = 0;
    if (v0 != 0) {
        // 0x004af284
        charge(ctx, 11);
        lw(v0, a0, 12);
        a2 = a3;
        lw(a1, a0, 8);
        a0 = v0;
        jal(ctx, 0x4AF290u, gen::fn_sub_493710_00493710);
        at = sltu(0, s2);
        s1 = v0;
        sw(zero, sp, 0x6C);
        s0 = 0;
        sw(zero, sp, 0x68);
        if (at == 0) {
            backedge(ctx);
        } else {
            for (;;) {
                // 0x004af2b0
                charge(ctx, 3);
                lw(v0, s3, 0);
                if (v0 != 0) {
                    // 0x004af2bc
                    charge(ctx, 5);
                    lw(a0, v0, 20);
                    lw(v0, s3, 16);
                    v0 = v0 & 0x1;
                    if (v0 == 0) {
                        // 0x004af2f0
                        charge(ctx, 6);
                        lw(a1, s3, 20);
                        a2 = s1;
                        a3 = addiu(sp, 0x6C);
                        t0 = addiu(sp, 0x68);
                        jal(ctx, 0x4AF2FCu, gen::fn_sub_4ACE80_004ace80);
                    } else {
                        // 0x004af2d0
                        charge(ctx, 7);
                        lw(a1, s3, 20);
                        a2 = s1;
                        a3 = addiu(sp, 0x6C);
                        t0 = addiu(sp, 0x68);
                        jal(ctx, 0x4AF2DCu, gen::fn_sub_4A6630_004a6630);
                    }
                }
                // 0x004af308
                charge(ctx, 4);
                s0 = addiu(s0, 1);
                v0 = sltu(s0, s2);
                s3 = addiu(s3, 24);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004af318
            charge(ctx, 2);
            backedge(ctx);
        }
    }
    // 0x004af23c
    charge(ctx, 2);
    if (s1 != 0) {
        // 0x004af244
        charge(ctx, 14);
        lw(s0, s1, 92);
        a1 = addiu(sp, 0x50);
        a0 = s0;
        jal(ctx, 0x4AF24Cu, gen::fn_sub_492E20_00492e20);
        lwc1(f3, sp, 0x50);
        a0 = s1;
        lwc1(f2, sp, 0x54);
        lwc1(f1, sp, 0x58);
        lwc1(f0, sp, 0x5C);
        swc1(f3, s0, 4);
        swc1(f2, s0, 8);
        swc1(f1, s0, 12);
        link(ctx, 0x4AF274u);  // $ra first: the delay slot below depends on it
        swc1(f0, s0, 16);
        call(ctx, gen::fn_sub_4933D0_004933d0);
    }
    // 0x004af27c
    charge(ctx, 2);
    v0 = s1;
    // 0x004af320
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// sub_4AF340 [rt2dShapeRepBuild] -- builds a shape representation from its nodes: per node its paths copied (shared
//   when flat, else flattened by sub_4ABD50) and chained, the vertex / triangle / index counts summed (fill: n and n - 3
//   per path, stroke: 2n and 2n - 2), the geometry built (sub_4AF210, flags 111), the temporary paths released; the
//   geometry stored at +8 and returned
// 0x004AF340 sub_4AF340 -- 1056 bytes; frame 0xC0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq), s3 sp+0xA0
void sub_4AF340(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004af340
    enter(ctx, 42);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(ra, sp, 0x90);
    a1 = addiu(sp, 0xB8);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    s7 = a0;
    sq(s5, sp, 0x50);
    a0 = addiu(sp, 0xBC);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    link(ctx, 0x4AF374u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_498E40_00498e40);
    link(ctx, 0x4AF37Cu);  // $ra first: the delay slot below depends on it
    lw(a0, s7, 0);
    call(ctx, gen::fn_sub_4C2120_004c2120);
    lw(a0, s7, 0);
    s5 = v0;
    jal(ctx, 0x4AF388u, gen::fn_sub_4C2090_004c2090);
    s4 = v0;
    v0 = sll(s5, 1);
    v1 = addu(v0, s5);
    v0 = 0x30000;
    a1 = v0 | 0x190;
    v0 = sll(v1, 2);
    fp = addu(s4, v0);
    v0 = 0x960000;
    lw(v0, v0, 376);  // 0x960178
    a0 = sll(v1, 3);
    jalr(ctx, 0x4AF3B4u, v0.u());
    s3 = v0;
    s6 = addiu(sp, 0xA4);
    v0 = addiu(sp, 0xAC);
    sw(s3, sp, 0xA0);
    sw(zero, v0, 0);
    v0 = addiu(sp, 0xB0);
    sw(s5, s6, 0);
    sw(zero, v0, 0);
    v0 = addiu(sp, 0xA8);
    sw(zero, v0, 0);
    if (s4 != fp) {
        // 0x004af3e8
        charge(ctx, 1);
        s2 = s3;
        for (;;) {
            // 0x004af3ec
            charge(ctx, 13);
            lw(s0, s4, 4);
            sw(zero, s2, 0);
            sw(zero, s2, 8);
            sw(zero, s2, 4);
            sw(zero, s2, 12);
            lw(v0, s4, 8);
            sw(v0, s2, 20);
            lw(v0, s4, 0);
            sw(v0, s2, 16);
            lw(v0, s4, 0);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x004af4e4
                charge(ctx, 2);
                if (s0 != 0) {
                    for (;;) {
                        // 0x004af4ec
                        charge(ctx, 6);
                        jal(ctx, 0x4AF4ECu, gen::fn_sub_4AC570_004ac570);
                        s1 = v0;
                        lw(v0, s0, 12);
                        if (v0 != 0) {
                            // 0x004af6d8
                            charge(ctx, 13);
                            link(ctx, 0x4AF6D8u);  // $ra first: the delay slot below depends on it
                            lw(a0, s1, 0);
                            call(ctx, gen::fn_sub_4C20B0_004c20b0);
                            lw(v0, s0, 0);
                            v1 = si(-1);
                            sw(v0, s1, 0);
                            lw(v0, s0, 4);
                            sw(v0, s1, 4);
                            lw(v0, s0, 8);
                            sw(v0, s1, 8);
                            sw(zero, s1, 12);
                            lw(v0, s0, 4);
                            if (v0 == v1) {
                                // 0x004af70c
                                charge(ctx, 2);
                                link(ctx, 0x4AF70Cu);  // $ra first: the delay slot below depends on it
                                lw(a0, s0, 0);
                                call(ctx, gen::fn_sub_4C2120_004c2120);
                            }
                            // 0x004af714
                            charge(ctx, 2);
                            lwc1(f0, s0, 16);
                            backedge(ctx);
                        } else {
                            // 0x004af504
                            charge(ctx, 7);
                            a0 = s1;
                            a1 = s0;
                            jal(ctx, 0x4AF508u, gen::fn_sub_4ABD50_004abd50);
                            lw(v0, s1, 4);
                            v1 = si(-1);
                            if (v0 == v1) {
                                // 0x004af520
                                charge(ctx, 4);
                                link(ctx, 0x4AF520u);  // $ra first: the delay slot below depends on it
                                lw(a0, s1, 0);
                                call(ctx, gen::fn_sub_4C2120_004c2120);
                            }
                            // 0x004af530
                            charge(ctx, 1);
                            lwc1(f0, s0, 16);
                        }
                        // 0x004af534
                        charge(ctx, 17);
                        a1 = sll(v0, 1);
                        a0 = addiu(a1, -2);
                        v0 = sll(a0, 1);
                        v1 = addu(v0, a0);
                        swc1(f0, s1, 16);
                        lw(v0, s2, 8);
                        v0 = addu(v0, a1);
                        sw(v0, s2, 8);
                        lw(v0, s2, 4);
                        v0 = addu(v0, a0);
                        sw(v0, s2, 4);
                        lw(v0, s2, 12);
                        v0 = addu(v0, v1);
                        sw(v0, s2, 12);
                        lw(v0, s2, 0);
                        if (v0 == 0) {
                            // 0x004af71c
                            charge(ctx, 2);
                            sw(s1, s1, 20);
                            backedge(ctx);
                        } else {
                            // 0x004af578
                            charge(ctx, 4);
                            lw(v0, v0, 20);
                            sw(v0, s1, 20);
                            lw(v0, s2, 0);
                            sw(s1, v0, 20);
                        }
                        // 0x004af588
                        charge(ctx, 4);
                        sw(s1, s2, 0);
                        lw(s0, s0, 20);
                        if (s0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            L_004af598:
                charge(ctx, 1);
                v0 = addiu(sp, 0xAC);
            } else {
                // 0x004af420
                charge(ctx, 2);
                if (s0 == 0) {
                    goto L_004af598;
                }
                for (;;) {
                    // 0x004af428
                    charge(ctx, 3);
                    lw(v0, s0, 8);
                    if (v0 != 0) {
                        // 0x004af434
                        charge(ctx, 6);
                        jal(ctx, 0x4AF434u, gen::fn_sub_4AC570_004ac570);
                        s1 = v0;
                        lw(v0, s0, 12);
                        if (v0 != 0) {
                            // 0x004af68c
                            charge(ctx, 13);
                            link(ctx, 0x4AF68Cu);  // $ra first: the delay slot below depends on it
                            lw(a0, s1, 0);
                            call(ctx, gen::fn_sub_4C20B0_004c20b0);
                            lw(v0, s0, 0);
                            v1 = si(-1);
                            sw(v0, s1, 0);
                            lw(v0, s0, 4);
                            sw(v0, s1, 4);
                            lw(v0, s0, 8);
                            sw(v0, s1, 8);
                            sw(zero, s1, 12);
                            lw(v0, s0, 4);
                            if (v0 == v1) {
                                // 0x004af6c0
                                charge(ctx, 2);
                                link(ctx, 0x4AF6C0u);  // $ra first: the delay slot below depends on it
                                lw(a0, s0, 0);
                                call(ctx, gen::fn_sub_4C2120_004c2120);
                            }
                            // 0x004af6c8
                            charge(ctx, 2);
                            lwc1(f0, s0, 16);
                            backedge(ctx);
                        } else {
                            // 0x004af44c
                            charge(ctx, 7);
                            a0 = s1;
                            a1 = s0;
                            jal(ctx, 0x4AF450u, gen::fn_sub_4ABD50_004abd50);
                            lw(v0, s1, 4);
                            v1 = si(-1);
                            if (v0 == v1) {
                                // 0x004af468
                                charge(ctx, 4);
                                link(ctx, 0x4AF468u);  // $ra first: the delay slot below depends on it
                                lw(a0, s1, 0);
                                call(ctx, gen::fn_sub_4C2120_004c2120);
                            }
                            // 0x004af478
                            charge(ctx, 1);
                            lwc1(f0, s0, 16);
                        }
                        // 0x004af47c
                        charge(ctx, 16);
                        a0 = addiu(v0, -3);
                        v1 = sll(a0, 1);
                        v1 = addu(v1, a0);
                        swc1(f0, s1, 16);
                        lw(a1, s2, 8);
                        v0 = addu(a1, v0);
                        sw(v0, s2, 8);
                        lw(v0, s2, 4);
                        v0 = addu(v0, a0);
                        sw(v0, s2, 4);
                        lw(v0, s2, 12);
                        v0 = addu(v0, v1);
                        sw(v0, s2, 12);
                        lw(v0, s2, 0);
                        if (v0 == 0) {
                            // 0x004af6d0
                            charge(ctx, 2);
                            sw(s1, s1, 20);
                            backedge(ctx);
                        } else {
                            // 0x004af4bc
                            charge(ctx, 4);
                            lw(v0, v0, 20);
                            sw(v0, s1, 20);
                            lw(v0, s2, 0);
                            sw(s1, v0, 20);
                        }
                        // 0x004af4cc
                        charge(ctx, 1);
                        sw(s1, s2, 0);
                    }
                    // 0x004af4d0
                    charge(ctx, 3);
                    lw(s0, s0, 20);
                    if (s0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004af4dc
                charge(ctx, 2);
                v0 = addiu(sp, 0xAC);
            }
            // 0x004af59c
            charge(ctx, 20);
            lw(a1, s2, 8);
            lw(a2, v0, 0);
            s4 = addiu(s4, 12);
            v0 = addiu(sp, 0xA8);
            a1 = addu(a2, a1);
            lw(a0, v0, 0);
            v0 = addiu(sp, 0xB0);
            lw(v1, v0, 0);
            v0 = addiu(sp, 0xAC);
            sw(a1, v0, 0);
            lw(v0, s2, 4);
            a0 = addu(a0, v0);
            v0 = addiu(sp, 0xA8);
            sw(a0, v0, 0);
            lw(v0, s2, 12);
            v1 = addu(v1, v0);
            s2 = addiu(s2, 24);
            v0 = addiu(sp, 0xB0);
            sw(v1, v0, 0);
            if (s4 == fp) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004af5ec
    charge(ctx, 9);
    a2 = s5;
    a0 = addiu(sp, 0xA0);
    a1 = s3;
    a3 = 111;
    jal(ctx, 0x4AF5F8u, gen::fn_sub_4AF210_004af210);
    s1 = v0;
    lw(v0, sp, 0xA0);
    if (v0 != 0) {
        // 0x004af610
        charge(ctx, 4);
        lw(v0, s6, 0);
        at = sltu(0, v0);
        s0 = 0;
        if (at != 0) {
            for (;;) {
                // 0x004af620
                charge(ctx, 2);
                lw(v0, s3, 0);
                lw(a0, v0, 20);
                for (;;) {
                    // 0x004af628
                    charge(ctx, 3);
                    lw(v0, a0, 12);
                    if (v0 == 0) {
                        // 0x004af724
                        charge(ctx, 2);
                        sw(zero, a0, 0);
                        backedge(ctx);
                    } else {
                        // 0x004af634
                        charge(ctx, 1);
                    }
                    // 0x004af638
                    charge(ctx, 6);
                    lw(v0, s3, 0);
                    lw(a0, a0, 20);
                    v1 = addiu(v0, 20);
                    lw(v0, v0, 20);
                    if (a0 == v0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004af650
                charge(ctx, 7);
                link(ctx, 0x4AF650u);  // $ra first: the delay slot below depends on it
                sw(zero, v1, 0);
                call(ctx, gen::fn_sub_4AC390_004ac390);
                lw(v0, s6, 0);
                s0 = addiu(s0, 1);
                v0 = sltu(s0, v0);
                s3 = addiu(s3, 24);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004af66c
            charge(ctx, 1);
        }
        // 0x004af670
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x4AF678u);  // $ra = the return address
        lw(a0, sp, 0xA0);
        call_ptr(ctx, jt);
    }
    // 0x004af680
    charge(ctx, 3);
    sw(s1, s7, 8);
    v0 = s1;
    // 0x004af730
    charge(ctx, 12);
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

// sub_4AF760 [rt2dShapeRepStreamRead] -- reads a shape representation: an 8-byte header, a 12-byte record (reference
//   count 1) with a 12-byte-node sList, per node its flags and, when it has a path (flag 4), the path (chunk 417:
//   sub_4AC570 / sub_4AC710 / sub_4ACB10) and the brush (chunk 418: sub_4A5470 / sub_4A6530); the geometry built
//   (sub_4AF340); the representation, or 0
// 0x004AF760 sub_4AF760 -- 468 bytes; frame 0x80: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AF760(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004af760
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    a2 = 8;
    sd(ra, sp, 0x50);
    a1 = addiu(sp, 0x68);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    link(ctx, 0x4AF784u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C5250_004c5250);
    v1 = 8;
    if (v0 == v1) {
        // 0x004af7a0
        charge(ctx, 18);
        v0 = 0x30000;
        s1 = addiu(sp, 0x6C);
        a1 = v0 | 0x190;
        lw(s0, s1, 0);
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178
        a0 = 12;
        jalr(ctx, 0x4AF7B8u, v0.u());
        v1 = 1;
        s2 = v0;
        sw(v1, v0, 4);
        a0 = 12;
        v0 = 0x30000;
        a1 = v0 | 0x1A4;
        jal(ctx, 0x4AF7D4u, gen::fn_sub_4C1D50_004c1d50);
        sw(v0, s2, 0);
        sw(zero, s2, 8);
        if (s0 != 0) {
            // 0x004af7e8
            charge(ctx, 5);
            lw(a0, s2, 0);
            v0 = 0x30000;
            a1 = s0;
            a2 = v0 | 0x1A4;
            jal(ctx, 0x4AF7F4u, gen::fn_sub_4C1F70_004c1f70);
        }
        // 0x004af7fc
        charge(ctx, 7);
        link(ctx, 0x4AF7FCu);  // $ra first: the delay slot below depends on it
        lw(a0, s2, 0);
        call(ctx, gen::fn_sub_4C2090_004c2090);
        s3 = v0;
        lw(v0, s1, 0);
        at = slt(0, v0);
        s0 = 0;
        if (at != 0) {
            for (;;) {
                // 0x004af818
                charge(ctx, 7);
                a0 = s4;
                a1 = addiu(sp, 0x7C);
                a2 = 4;
                jal(ctx, 0x4AF820u, gen::fn_sub_4C5250_004c5250);
                a2 = 4;
                if (v0 != a2) {
                    goto L_004af834_6;
                }
                // 0x004af83c
                charge(ctx, 4);
                lw(v0, sp, 0x7C);
                v0 = v0 & 0x4;
                if (v0 == 0) {
                    // 0x004af84c
                    charge(ctx, 3);
                    sw(zero, s3, 4);
                    sw(zero, s3, 8);
                    goto L_004af858;
                }
                // 0x004af884
                charge(ctx, 10);
                a0 = s4;
                a1 = s3;
                jal(ctx, 0x4AF888u, gen::fn_sub_4C1910_004c1910);
                a0 = s4;
                a1 = 417;
                a2 = addiu(sp, 0x78);
                a3 = addiu(sp, 0x74);
                jal(ctx, 0x4AF89Cu, gen::fn_sub_4C1600_004c1600);
                if (v0 == 0) {
                    break;
                }
                // 0x004af8ac
                charge(ctx, 15);
                jal(ctx, 0x4AF8ACu, gen::fn_sub_4AC570_004ac570);
                sw(v0, s3, 4);
                link(ctx, 0x4AF8B8u);  // $ra first: the delay slot below depends on it
                lw(a0, s3, 4);
                call(ctx, gen::fn_sub_4AC710_004ac710);
                lw(a0, s3, 4);
                a1 = s4;
                jal(ctx, 0x4AF8C4u, gen::fn_sub_4ACB10_004acb10);
                a0 = s4;
                a1 = 418;
                a2 = addiu(sp, 0x78);
                a3 = addiu(sp, 0x74);
                jal(ctx, 0x4AF8D8u, gen::fn_sub_4C1600_004c1600);
                if (v0 == 0) {
                    goto L_004af910;
                }
                // 0x004af8e8
                charge(ctx, 8);
                jal(ctx, 0x4AF8E8u, gen::fn_sub_4A5470_004a5470);
                sw(v0, s3, 8);
                lw(a0, s3, 8);
                a1 = s4;
                jal(ctx, 0x4AF8F8u, gen::fn_sub_4A6530_004a6530);
                backedge(ctx);
            L_004af858:
                charge(ctx, 5);
                lw(v0, s1, 0);
                s0 = addiu(s0, 1);
                v0 = slt(s0, v0);
                s3 = addiu(s3, 12);
                if (v0 == 0) {
                    goto L_004af86c_10;
                }
                backedge(ctx);
            }
            // 0x004af908
            charge(ctx, 2);
            v0 = 0;
            // 0x004af914 (the shared epilogue, written out on this path)
            charge(ctx, 8);
            ld(ra, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x80);
            return;
        }
    L_004af870:
        charge(ctx, 5);
        a0 = s2;
        jal(ctx, 0x4AF870u, gen::fn_sub_4AF340_004af340);
        sw(v0, s2, 8);
        v0 = s2;
    } else {
        // 0x004af798
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004af914 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_004af834_6:
    charge(ctx, 2);
    v0 = 0;
    // 0x004af914 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
    return;
L_004af86c_10:
    charge(ctx, 1);
    goto L_004af870;
L_004af910:
    charge(ctx, 1);
    v0 = 0;
    // 0x004af914 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// sub_4AF940 [rt2dShapeDestroyBody] -- destroys a shape's contents: its representation released (sub_4AF130), the
//   atomic's frame detached and destroyed (sub_492D10 / sub_4CAF80), the atomic destroyed (sub_491A80), the node colour
//   array freed; 1
// 0x004AF940 sub_4AF940 -- 132 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AF940(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004af940
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    link(ctx, 0x4AF954u);  // $ra first: the delay slot below depends on it
    lw(a0, a0, 176);
    call(ctx, gen::fn_sub_4AF130_004af130);
    lw(a0, s1, 184);
    if (a0 != 0) {
        // 0x004af968
        charge(ctx, 3);
        lw(s0, a0, 4);
        if (s0 != 0) {
            // 0x004af974
            charge(ctx, 4);
            a1 = 0;
            jal(ctx, 0x4AF974u, gen::fn_sub_492D10_00492d10);
            a0 = s0;
            jal(ctx, 0x4AF97Cu, gen::fn_sub_4CAF80_004caf80);
        }
        // 0x004af984
        charge(ctx, 2);
        link(ctx, 0x4AF984u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, 184);
        call(ctx, gen::fn_sub_491A80_00491a80);
    }
    // 0x004af98c
    charge(ctx, 3);
    lw(a0, s1, 180);
    if (a0 != 0) {
        // 0x004af998
        charge(ctx, 5);
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x4AF9A0u, v0.u());
        sw(zero, s1, 180);
    }
    // 0x004af9ac (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    v0 = 1;
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4AFFE0 [rt2dShapeStreamRead] -- reads a shape's body: its representation (an index into the shared list $a2, or
//   its own, sub_4AF760), the per-node colour array taken from the geometry's materials, the representation referenced
//   (or an empty one made), a frame (sub_4CAF10) with the current transform (sub_4CB7F0), an atomic (sub_491880) on the
//   frame with the representation's geometry; the shape, or 0
// 0x004AFFE0 sub_4AFFE0 -- 884 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4AFFE0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004affe0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a2;
    s1 = a0;
    if (s0 == 0) {
        // 0x004b00d4
        charge(ctx, 4);
        a0 = a1;
        jal(ctx, 0x4B00D4u, gen::fn_sub_4AF760_004af760);
        s0 = v0;
        backedge(ctx);
    L_004b0034:
        charge(ctx, 8);
        lw(v1, s1, 8);
        v0 = si(-2);
        v0 = v1 & v0;
        sw(v0, s1, 8);
        lw(s3, s0, 8);
        lw(s2, s3, 36);
        if (s2 != 0) {
            // 0x004b00e4
            charge(ctx, 9);
            v0 = 0x30000;
            a1 = v0 | 0x190;
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178
            a0 = sll(s2, 2);
            jalr(ctx, 0x4B00F4u, v0.u());
            at = sltu(0, s2);
            a2 = 0;
            if (at != 0) {
                // 0x004b0108
                charge(ctx, 3);
                at = sltiu(s2, 9);
                v1 = addiu(s2, -8);
                if (at == 0) {
                    // 0x004b0114
                    charge(ctx, 2);
                    a1 = 0;
                    a0 = v0;
                    for (;;) {
                        // 0x004b011c
                        charge(ctx, 93);
                        lw(t0, s3, 32);
                        a2 = addiu(a2, 8);
                        a3 = sltu(a2, v1);
                        t0 = addu(t0, a1);
                        lw(t0, t0, 0);
                        lbu(t3, t0, 4);
                        lbu(t2, t0, 5);
                        lbu(t1, t0, 6);
                        lbu(t0, t0, 7);
                        sb(t3, a0, 0);
                        sb(t2, a0, 1);
                        sb(t1, a0, 2);
                        sb(t0, a0, 3);
                        lw(t0, s3, 32);
                        t0 = addu(t0, a1);
                        lw(t0, t0, 4);
                        lbu(t3, t0, 4);
                        lbu(t2, t0, 5);
                        lbu(t1, t0, 6);
                        lbu(t0, t0, 7);
                        sb(t3, a0, 4);
                        sb(t2, a0, 5);
                        sb(t1, a0, 6);
                        sb(t0, a0, 7);
                        lw(t0, s3, 32);
                        t0 = addu(t0, a1);
                        lw(t0, t0, 8);
                        lbu(t3, t0, 4);
                        lbu(t2, t0, 5);
                        lbu(t1, t0, 6);
                        lbu(t0, t0, 7);
                        sb(t3, a0, 8);
                        sb(t2, a0, 9);
                        sb(t1, a0, 10);
                        sb(t0, a0, 11);
                        lw(t0, s3, 32);
                        t0 = addu(t0, a1);
                        lw(t0, t0, 12);
                        lbu(t3, t0, 4);
                        lbu(t2, t0, 5);
                        lbu(t1, t0, 6);
                        lbu(t0, t0, 7);
                        sb(t3, a0, 12);
                        sb(t2, a0, 13);
                        sb(t1, a0, 14);
                        sb(t0, a0, 15);
                        lw(t0, s3, 32);
                        t0 = addu(t0, a1);
                        lw(t0, t0, 16);
                        lbu(t3, t0, 4);
                        lbu(t2, t0, 5);
                        lbu(t1, t0, 6);
                        lbu(t0, t0, 7);
                        sb(t3, a0, 16);
                        sb(t2, a0, 17);
                        sb(t1, a0, 18);
                        sb(t0, a0, 19);
                        lw(t0, s3, 32);
                        t0 = addu(t0, a1);
                        lw(t0, t0, 20);
                        lbu(t3, t0, 4);
                        lbu(t2, t0, 5);
                        lbu(t1, t0, 6);
                        lbu(t0, t0, 7);
                        sb(t3, a0, 20);
                        sb(t2, a0, 21);
                        sb(t1, a0, 22);
                        sb(t0, a0, 23);
                        lw(t0, s3, 32);
                        t0 = addu(t0, a1);
                        lw(t0, t0, 24);
                        lbu(t3, t0, 4);
                        lbu(t2, t0, 5);
                        lbu(t1, t0, 6);
                        lbu(t0, t0, 7);
                        sb(t3, a0, 24);
                        sb(t2, a0, 25);
                        sb(t1, a0, 26);
                        sb(t0, a0, 27);
                        lw(t0, s3, 32);
                        t0 = addu(t0, a1);
                        lw(t0, t0, 28);
                        a1 = addiu(a1, 32);
                        lbu(t3, t0, 4);
                        lbu(t2, t0, 5);
                        lbu(t1, t0, 6);
                        lbu(t0, t0, 7);
                        sb(t3, a0, 28);
                        sb(t2, a0, 29);
                        sb(t1, a0, 30);
                        sb(t0, a0, 31);
                        a0 = addiu(a0, 32);
                        if (a3 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x004b0290
                charge(ctx, 3);
                at = sltu(a2, s2);
                if (at != 0) {
                    // 0x004b029c
                    charge(ctx, 2);
                    t2 = sll(a2, 2);
                    t1 = addu(v0, t2);
                    for (;;) {
                        // 0x004b02a4
                        charge(ctx, 16);
                        lw(a0, s3, 32);
                        a2 = addiu(a2, 1);
                        v1 = sltu(a2, s2);
                        a0 = addu(a0, t2);
                        lw(a0, a0, 0);
                        t2 = addiu(t2, 4);
                        lbu(t0, a0, 4);
                        lbu(a3, a0, 5);
                        lbu(a1, a0, 6);
                        lbu(a0, a0, 7);
                        sb(t0, t1, 0);
                        sb(a3, t1, 1);
                        sb(a1, t1, 2);
                        sb(a0, t1, 3);
                        t1 = addiu(t1, 4);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004b02e4
                    charge(ctx, 1);
                }
            }
            // 0x004b02e8
            charge(ctx, 2);
            backedge(ctx);
        } else {
            // 0x004b0054
            charge(ctx, 1);
            v0 = 0;
        }
        // 0x004b0058
        charge(ctx, 2);
        sw(v0, s1, 180);
        if (s0 == 0) {
            // 0x004b02f0
            charge(ctx, 18);
            v0 = 0x30000;
            a1 = v0 | 0x190;
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178
            a0 = 12;
            jalr(ctx, 0x4B0300u, v0.u());
            v1 = 1;
            s2 = v0;
            sw(v1, v0, 4);
            a0 = 12;
            v0 = 0x30000;
            a1 = v0 | 0x1A4;
            jal(ctx, 0x4B031Cu, gen::fn_sub_4C1D50_004c1d50);
            sw(v0, s2, 0);
            sw(zero, s2, 8);
            sw(s2, s1, 176);
            sw(zero, s1, 180);
            backedge(ctx);
        } else {
            // 0x004b0060
            charge(ctx, 4);
            sw(s0, s1, 176);
            lw(v0, s0, 4);
            v0 = addiu(v0, 1);
            sw(v0, s0, 4);
        }
        // 0x004b0070
        charge(ctx, 23);
        lw(v0, s1, 8);
        v0 = v0 | 0x1;
        link(ctx, 0x4B0078u);  // $ra first: the delay slot below depends on it
        sw(v0, s1, 8);
        call(ctx, gen::fn_sub_4CAF10_004caf10);
        s2 = v0;
        jal(ctx, 0x4B0080u, gen::fn_sub_4AAE60_004aae60);
        a1 = v0;
        a0 = s2;
        a2 = 0;
        jal(ctx, 0x4B0090u, gen::fn_sub_4CB7F0_004cb7f0);
        jal(ctx, 0x4B0098u, gen::fn_sub_491880_00491880);
        s3 = v0;
        a1 = s2;
        a0 = s3;
        jal(ctx, 0x4B00A8u, gen::fn_sub_492D10_00492d10);
        lw(a1, s0, 8);
        a0 = s3;
        a2 = 0;
        jal(ctx, 0x4B00B8u, gen::fn_sub_4919B0_004919b0);
        sw(s3, s1, 184);
        v0 = s1;
    } else {
        // 0x004b0004
        charge(ctx, 7);
        a0 = a1;
        a2 = 4;
        a1 = addiu(sp, 0x5C);
        jal(ctx, 0x4B000Cu, gen::fn_sub_4C5250_004c5250);
        v1 = 4;
        if (v0 == v1) {
            // 0x004b0020
            charge(ctx, 5);
            lw(v1, sp, 0x5C);
            lw(v0, s0, 0);
            v1 = sll(v1, 2);
            v0 = addu(v0, v1);
            lw(s0, v0, 0);
            goto L_004b0034;
        }
        // 0x004b00cc
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004b0338 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4B1290 [rt2dMaestroKeyListStreamRead] -- reads a maestro animation's keyed list: the count, an sList of 8-byte
//   entries {time, animation (chunk 432, sub_4B22B0)}, speed 1.0, the first entry current and the latest-starting entry
//   remembered (+24); the list, or 0
// 0x004B1290 sub_4B1290 -- 396 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B1290(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x004b1290
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    a2 = 4;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    s1 = a1;
    sq(s0, sp, 0x0);
    a0 = s1;
    a1 = addiu(sp, 0x5C);
    link(ctx, 0x4B12BCu);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x5C);
    call(ctx, gen::fn_sub_4C5250_004c5250);
    v1 = 4;
    if (v0 == v1) {
        // 0x004b12d8
        charge(ctx, 7);
        lw(s0, sp, 0x5C);
        v0 = 0x30000;
        a0 = 8;
        a1 = v0 | 0x1B0;
        jal(ctx, 0x4B12E4u, gen::fn_sub_4C1D50_004c1d50);
        sw(v0, s2, 0);
        if (s0 != 0) {
            // 0x004b12f4
            charge(ctx, 5);
            lw(a0, s2, 0);
            v0 = 0x30000;
            a1 = s0;
            a2 = v0 | 0x1B0;
            jal(ctx, 0x4B1300u, gen::fn_sub_4C1F70_004c1f70);
        }
        // 0x004b1308
        charge(ctx, 15);
        v1 = 0x3F800000;
        v0 = 1;
        sw(v1, s2, 4);
        sw(zero, s2, 8);
        sw(v0, s2, 12);
        sw(zero, s2, 16);
        sw(zero, s2, 20);
        sw(zero, s2, 24);
        link(ctx, 0x4B1328u);  // $ra first: the delay slot below depends on it
        lw(a0, s2, 0);
        call(ctx, gen::fn_sub_4C2090_004c2090);
        lw(v1, sp, 0x5C);
        v1 = sll(v1, 3);
        s3 = addu(v0, v1);
        s0 = v0;
        if (v0 != s3) {
            for (;;) {
                // 0x004b1344
                charge(ctx, 7);
                a0 = s1;
                a1 = addiu(sp, 0x58);
                a2 = 4;
                jal(ctx, 0x4B134Cu, gen::fn_sub_4C5250_004c5250);
                v1 = 4;
                if (v0 != v1) {
                    break;
                }
                // 0x004b1368
                charge(ctx, 9);
                lwc1(f0, sp, 0x58);
                a0 = s1;
                a1 = 432;
                a2 = 0;
                a3 = 0;
                link(ctx, 0x4B137Cu);  // $ra first: the delay slot below depends on it
                swc1(f0, s0, 0);
                call(ctx, gen::fn_sub_4C1600_004c1600);
                if (v0 == 0) {
                    goto L_004b13e8;
                }
                // 0x004b138c
                charge(ctx, 4);
                a0 = s1;
                jal(ctx, 0x4B138Cu, gen::fn_sub_4B22B0_004b22b0);
                if (v0 == 0) {
                    goto L_004b13f0;
                }
                // 0x004b139c
                charge(ctx, 7);
                sw(v0, s0, 4);
                link(ctx, 0x4B13A0u);  // $ra first: the delay slot below depends on it
                lw(a0, s2, 0);
                call(ctx, gen::fn_sub_4C2090_004c2090);
                sw(v0, s2, 20);
                lw(v0, s2, 24);
                if (v0 != 0) {
                    // 0x004b13b8
                    charge(ctx, 5);
                    lwc1(f0, v0, 0);
                    lwc1(f1, sp, 0x58);
                    c_le_s(f1, f0);
                    if (!cond(ctx)) {
                        goto L_004b13f8;
                    }
                    // 0x004b13cc
                    charge(ctx, 1);
                    goto L_004b13d0;
                }
            L_004b13f8:
                charge(ctx, 2);
                sw(s0, s2, 24);
                backedge(ctx);
            L_004b13d0:
                charge(ctx, 3);
                s0 = addiu(s0, 8);
                if (s0 == s3) {
                    goto L_004b13dc_13;
                }
                backedge(ctx);
            }
            // 0x004b1360
            charge(ctx, 2);
            v0 = 0;
            // 0x004b1400 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_004b13e0:
        charge(ctx, 2);
        v0 = s2;
    } else {
        // 0x004b12d0
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004b1400 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004b13dc_13:
    charge(ctx, 1);
    goto L_004b13e0;
L_004b13e8:
    charge(ctx, 2);
    v0 = 0;
    // 0x004b1400 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004b13f0:
    charge(ctx, 2);
    v0 = 0;
    // 0x004b1400 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4B1620 [rt2dMaestroAnimApply] -- applies a maestro animation's current keyframe to its props (sub_4B2810): the
//   current entry (+20), or the last one (+24) when there is none; the animation, or 0
// 0x004B1620 sub_4B1620 -- 212 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B1620(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12};
    // 0x004b1620
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    jal(ctx, 0x4B1634u, gen::fn_sub_4B1B90_004b1b90);
    if (v0 == 0) {
        // 0x004b16b0
        charge(ctx, 3);
        mtc1(zero, f12);
        backedge(ctx);
    L_004b1674:
        charge(ctx, 1);
        lw(v0, s1, 20);
    } else {
        // 0x004b1644
        charge(ctx, 3);
        lw(v1, s1, 16);
        if (v1 != 0) {
            // 0x004b1650
            charge(ctx, 3);
            lw(v0, s1, 20);
            if (v0 == 0) {
                goto L_004b16a4;
            }
            // 0x004b165c
            charge(ctx, 6);
            lwc1(f2, v1, 0);
            lwc1(f0, v0, 0);
            lwc1(f1, s1, 8);
            sub_s(f0, f0, f2);
            sub_s(f1, f1, f2);
            div_s(f12, f1, f0);
            goto L_004b1674;
        }
    L_004b16a4:
        charge(ctx, 3);
        mtc1(zero, f12);
        lw(v0, s1, 20);
        backedge(ctx);
    }
    // 0x004b1678
    charge(ctx, 2);
    if (v0 == 0) {
        // 0x004b16bc
        charge(ctx, 3);
        lw(v0, s1, 24);
        if (v0 == 0) {
            backedge(ctx);
        L_004b169c:
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004b16c8
            charge(ctx, 5);
            lw(a0, v0, 4);
            a1 = s0;
            jal(ctx, 0x4B16CCu, gen::fn_sub_4B2810_004b2810);
            if (v0 == 0) {
                backedge(ctx);
                goto L_004b169c;
            }
            // 0x004b16dc
            charge(ctx, 1);
            v0 = s1;
        }
    } else {
        // 0x004b1680
        charge(ctx, 5);
        lw(a0, v0, 4);
        a1 = s0;
        jal(ctx, 0x4B1684u, gen::fn_sub_4B2810_004b2810);
        if (v0 == 0) {
            goto L_004b169c;
        }
        // 0x004b1694
        charge(ctx, 2);
        v0 = s1;
    }
    // 0x004b16e0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4B1BA0 [rt2dAnimPropsCreate] -- creates the props of a scene for animation: a 160-byte-entry sList (sub_4C1D50),
//   one entry per object of the scene (its +4 sList), each with the object pointer and its change flags cleared; the
//   sList
// 0x004B1BA0 sub_4B1BA0 -- 224 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B1BA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b1ba0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x30000;
    sd(ra, sp, 0x30);
    a1 = v0 | 0x1A9;
    sq(s2, sp, 0x20);
    s2 = a0;
    sq(s1, sp, 0x10);
    a0 = 160;
    link(ctx, 0x4B1BC0u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1D50_004c1d50);
    lw(a0, s2, 4);
    s0 = v0;
    jal(ctx, 0x4B1BCCu, gen::fn_sub_4C2120_004c2120);
    if (v0 != 0) {
        // 0x004b1be4
        charge(ctx, 20);
        link(ctx, 0x4B1BE4u);  // $ra first: the delay slot below depends on it
        lw(a0, s2, 4);
        call(ctx, gen::fn_sub_4C2120_004c2120);
        a1 = v0;
        a0 = s0;
        v0 = 0x30000;
        a2 = v0 | 0x1A9;
        jal(ctx, 0x4B1BF8u, gen::fn_sub_4C1F70_004c1f70);
        a0 = s0;
        jal(ctx, 0x4B1C00u, gen::fn_sub_4C2090_004c2090);
        s1 = v0;
        a0 = s0;
        jal(ctx, 0x4B1C0Cu, gen::fn_sub_4C2120_004c2120);
        lw(a0, s2, 4);
        v1 = sll(v0, 2);
        v0 = addu(v1, v0);
        v0 = sll(v0, 5);
        s2 = addu(s1, v0);
        jal(ctx, 0x4B1C24u, gen::fn_sub_4C2090_004c2090);
        if (s1 == s2) {
            backedge(ctx);
        } else {
            for (;;) {
                // 0x004b1c34
                charge(ctx, 11);
                sw(zero, s1, 0);
                sw(zero, s1, 8);
                sw(zero, s1, 80);
                sw(zero, s1, 100);
                sw(zero, s1, 120);
                sw(zero, s1, 140);
                lw(v1, v0, 0);
                sw(v1, s1, 4);
                s1 = addiu(s1, 160);
                v0 = addiu(v0, 4);
                if (s1 == s2) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004b1c60
            charge(ctx, 2);
            backedge(ctx);
        }
    }
    // 0x004b1bdc
    charge(ctx, 2);
    v0 = s0;
    // 0x004b1c68
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4B26A0 [rt2dAnimPropsCommit] -- commits the changed props to their objects: for each prop marked changed, its
//   matrix (sub_4AE020), colour multiplier (sub_4AE150), colour offset (sub_4AE110) and visibility / scene position
//   (sub_4AE1D0 / sub_4AEF50 / sub_4ADFD0) when their dirty flags are set, the flags cleared
// 0x004B26A0 sub_4B26A0 -- 356 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B26A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b26a0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    link(ctx, 0x4B26BCu);  // $ra first: the delay slot below depends on it
    lw(a0, a0, 12);
    call(ctx, gen::fn_sub_4C2120_004c2120);
    lw(a0, s3, 12);
    s0 = v0;
    jal(ctx, 0x4B26C8u, gen::fn_sub_4C2090_004c2090);
    at = slt(0, s0);
    s1 = v0;
    s2 = 0;
    if (at != 0) {
        for (;;) {
            // 0x004b26e0
            charge(ctx, 4);
            lw(a0, s1, 0);
            v1 = 1;
            if (a0 == v1) {
                // 0x004b26f0
                charge(ctx, 3);
                lw(v1, s1, 8);
                if (v1 != 0) {
                    // 0x004b27a0
                    charge(ctx, 5);
                    lw(a0, s1, 4);
                    a1 = addiu(s1, 16);
                    jal(ctx, 0x4B27A4u, gen::fn_sub_4AE020_004ae020);
                    sw(zero, s1, 8);
                    backedge(ctx);
                } else {
                    // 0x004b26fc
                    charge(ctx, 1);
                }
                // 0x004b2700
                charge(ctx, 3);
                lw(v1, s1, 80);
                if (v1 != 0) {
                    // 0x004b27b8
                    charge(ctx, 5);
                    lw(a0, s1, 4);
                    a1 = addiu(s1, 84);
                    jal(ctx, 0x4B27BCu, gen::fn_sub_4AE150_004ae150);
                    sw(zero, s1, 80);
                    backedge(ctx);
                } else {
                    // 0x004b270c
                    charge(ctx, 1);
                }
                // 0x004b2710
                charge(ctx, 3);
                lw(v1, s1, 100);
                if (v1 != 0) {
                    // 0x004b27d0
                    charge(ctx, 5);
                    lw(a0, s1, 4);
                    a1 = addiu(s1, 104);
                    jal(ctx, 0x4B27D4u, gen::fn_sub_4AE110_004ae110);
                    sw(zero, s1, 100);
                    backedge(ctx);
                } else {
                    // 0x004b271c
                    charge(ctx, 1);
                }
                // 0x004b2720
                charge(ctx, 3);
                lw(v1, s1, 120);
                if (v1 != 0) {
                    // 0x004b272c
                    charge(ctx, 5);
                    lw(a0, s1, 4);
                    lw(a1, s1, 128);
                    lw(v0, a0, 4);
                    if (v0 != a1) {
                        // 0x004b2740
                        charge(ctx, 4);
                        jal(ctx, 0x4B2740u, gen::fn_sub_4AE1D0_004ae1d0);
                        link(ctx, 0x4B2748u);  // $ra first: the delay slot below depends on it
                        lw(a0, s3, 0);
                        call(ctx, gen::fn_sub_4AEF50_004aef50);
                    }
                    // 0x004b2750
                    charge(ctx, 4);
                    lw(a1, s1, 124);
                    link(ctx, 0x4B2754u);  // $ra first: the delay slot below depends on it
                    lw(a0, s1, 4);
                    call(ctx, gen::fn_sub_4ADFD0_004adfd0);
                    sw(zero, s1, 120);
                }
                // 0x004b2760
                charge(ctx, 3);
                lw(v1, s1, 140);
                if (v1 != 0) {
                    // 0x004b276c
                    charge(ctx, 3);
                    lw(v1, s1, 144);
                    if (v1 != 0) {
                        // 0x004b2778
                        charge(ctx, 2);
                        sw(zero, s1, 140);
                    }
                }
                // 0x004b2780
                charge(ctx, 2);
                sw(zero, s1, 0);
            }
            // 0x004b2788
            charge(ctx, 4);
            s2 = addiu(s2, 1);
            v1 = slt(s2, s0);
            s1 = addiu(s1, 160);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004b2798
    charge(ctx, 2);
    // 0x004b27e8
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4B2810 [rt2dKeyFrameInterpolate] -- interpolates a keyframe into the props by $f12 when 0 < t < 1: per change
//   record (until flag 0x20) the matrix blended (sub_4B24C0, flag 1), the colour multiplier (flag 2) and colour offset
//   (flag 4) lerped into the object (+160.. x 255, +144..) with its changed flag, flag 8 skipped, flag 0x10 the
//   visibility reset; then the props committed (sub_4B26A0); the keyframe list
// 0x004B2810 sub_4B2810 -- 636 bytes; frame 0x70: ra sp+0x60, s4 sp+0x50 (sq), s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
void sub_4B2810(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f20{ctx, 20};
    // 0x004b2810
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    mtc1(zero, f0);
    sq(s4, sp, 0x50);
    sq(s3, sp, 0x40);
    s4 = a0;
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    mov_s(f20, f12);
    c_le_s(f20, f0);
    s3 = a1;
    if (!cond(ctx)) {
        // 0x004b2848
        charge(ctx, 6);
        v0 = 0x3F800000;
        mtc1(v0, f0);
        c_lt_s(f20, f0);
        if (cond(ctx)) {
            // 0x004b2860
            charge(ctx, 5);
            lw(s1, s4, 8);
            lw(v0, s1, 0);
            v0 = v0 & 0x20;
            s0 = s1;
            if (v0 == 0) {
                for (;;) {
                    // 0x004b2874
                    charge(ctx, 8);
                    lw(a0, s3, 12);
                    link(ctx, 0x4B2878u);  // $ra first: the delay slot below depends on it
                    lw(a1, s0, 4);
                    call(ctx, gen::fn_sub_4C21B0_004c21b0);
                    s2 = v0;
                    lw(v0, s0, 0);
                    v0 = v0 & 0x1;
                    s1 = addiu(s1, 16);
                    if (v0 != 0) {
                        // 0x004b2900
                        charge(ctx, 6);
                        a0 = s2;
                        a1 = s1;
                        mov_s(f12, f20);
                        jal(ctx, 0x4B2908u, gen::fn_sub_4B24C0_004b24c0);
                        s1 = addiu(s1, 64);
                        backedge(ctx);
                    } else {
                        // 0x004b2894
                        charge(ctx, 1);
                    }
                    // 0x004b2898
                    charge(ctx, 4);
                    lw(v0, s0, 0);
                    v0 = v0 & 0x2;
                    if (v0 != 0) {
                        // 0x004b2918
                        charge(ctx, 42);
                        v0 = 0x437F0000;
                        lwc1(f1, s2, 84);
                        lwc1(f0, s1, 0);
                        mtc1(zero, f3);
                        mtc1(v0, f2);
                        lw(v0, s2, 4);
                        adda_s(f3, f1);
                        sub_s(f0, f0, f1);
                        madd_s(f0, f20, f0);
                        mul_s(f0, f2, f0);
                        swc1(f0, v0, 160);
                        lwc1(f1, s2, 88);
                        lw(v0, s2, 4);
                        lwc1(f0, s1, 4);
                        adda_s(f3, f1);
                        sub_s(f0, f0, f1);
                        madd_s(f0, f20, f0);
                        mul_s(f0, f2, f0);
                        swc1(f0, v0, 164);
                        lwc1(f1, s2, 92);
                        lw(v0, s2, 4);
                        lwc1(f0, s1, 8);
                        adda_s(f3, f1);
                        sub_s(f0, f0, f1);
                        madd_s(f0, f20, f0);
                        mul_s(f0, f2, f0);
                        swc1(f0, v0, 168);
                        lwc1(f1, s2, 96);
                        lw(v0, s2, 4);
                        lwc1(f0, s1, 12);
                        adda_s(f3, f1);
                        sub_s(f0, f0, f1);
                        s1 = addiu(s1, 16);
                        madd_s(f0, f20, f0);
                        mul_s(f0, f2, f0);
                        swc1(f0, v0, 172);
                        lw(v1, s2, 4);
                        lw(v0, v1, 8);
                        v0 = v0 | 0x8;
                        sw(v0, v1, 8);
                        sw(zero, s2, 80);
                        backedge(ctx);
                    }
                    // 0x004b28a8
                    charge(ctx, 4);
                    lw(v0, s0, 0);
                    v0 = v0 & 0x4;
                    if (v0 != 0) {
                        // 0x004b29c0
                        charge(ctx, 37);
                        lw(v0, s2, 4);
                        lwc1(f1, s2, 104);
                        lwc1(f0, s1, 0);
                        mtc1(zero, f2);
                        adda_s(f2, f1);
                        sub_s(f0, f0, f1);
                        madd_s(f0, f20, f0);
                        swc1(f0, v0, 144);
                        lwc1(f1, s2, 108);
                        lw(v0, s2, 4);
                        lwc1(f0, s1, 4);
                        adda_s(f2, f1);
                        sub_s(f0, f0, f1);
                        madd_s(f0, f20, f0);
                        swc1(f0, v0, 148);
                        lwc1(f1, s2, 112);
                        lw(v0, s2, 4);
                        lwc1(f0, s1, 8);
                        adda_s(f2, f1);
                        sub_s(f0, f0, f1);
                        madd_s(f0, f20, f0);
                        swc1(f0, v0, 152);
                        lwc1(f1, s2, 116);
                        lw(v0, s2, 4);
                        lwc1(f0, s1, 12);
                        adda_s(f2, f1);
                        sub_s(f0, f0, f1);
                        s1 = addiu(s1, 16);
                        madd_s(f0, f20, f0);
                        swc1(f0, v0, 156);
                        lw(v1, s2, 4);
                        lw(v0, v1, 8);
                        v0 = v0 | 0x8;
                        sw(v0, v1, 8);
                        sw(zero, s2, 100);
                        backedge(ctx);
                    }
                    // 0x004b28b8
                    charge(ctx, 4);
                    lw(v1, s0, 0);
                    v0 = v1 & 0x8;
                    if (v0 != 0) {
                        // 0x004b28c8
                        charge(ctx, 2);
                        s1 = addiu(s1, 16);
                    }
                    // 0x004b28d0
                    charge(ctx, 3);
                    v0 = v1 & 0x10;
                    if (v0 != 0) {
                        // 0x004b2a58
                        charge(ctx, 3);
                        sw(zero, s2, 140);
                        s1 = addiu(s1, 16);
                        backedge(ctx);
                    } else {
                        // 0x004b28dc
                        charge(ctx, 1);
                    }
                    // 0x004b28e0
                    charge(ctx, 4);
                    lw(v0, s1, 0);
                    v0 = v0 & 0x20;
                    s0 = s1;
                    if (v0 != 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
    }
    // 0x004b28f0
    charge(ctx, 4);
    a0 = s3;
    jal(ctx, 0x4B28F0u, gen::fn_sub_4B26A0_004b26a0);
    v0 = s4;
    // 0x004b2a68
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s4, sp, 0x50);
    lwc1(f20, sp, 0x0);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x70);
}

// sub_4B2AD0 [rt2dAnimPropsInit] -- initialises a props record for a scene: the scene, a 4-byte sList of its objects
//   (filled by the walk sub_4AEB60 with sub_4B2A90), the props sList (sub_4B1BA0); the record, or 0
// 0x004B2AD0 sub_4B2AD0 -- 112 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B2AD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b2ad0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x30000;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    sw(a1, a0, 0);
    s0 = a0;
    a1 = v0 | 0x1A9;
    a0 = 4;
    jal(ctx, 0x4B2AECu, gen::fn_sub_4C1D50_004c1d50);
    sw(v0, s0, 4);
    lw(a2, s0, 4);
    if (a2 == 0) {
        // 0x004b2b2c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004b2b04
        charge(ctx, 10);
        lw(a0, s0, 0);
        a1 = 0x4B0000;
        a1 = addiu(a1, 10896);  // &sub_4B2A90
        jal(ctx, 0x4B2B0Cu, gen::fn_sub_4AEB60_004aeb60);
        a0 = s0;
        link(ctx, 0x4B2B18u);  // $ra first: the delay slot below depends on it
        sw(zero, s0, 8);
        call(ctx, gen::fn_sub_4B1BA0_004b1ba0);
        sw(v0, s0, 12);
        v0 = s0;
    }
    // 0x004b2b30 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4B2BC0 [rt2dMaestroStringsCreate] -- creates the maestro's string buffer: a 1-byte-entry sList (a tail call into
//   sub_4C1D50)
// 0x004B2BC0 sub_4B2BC0 -- 16 bytes; leaf frame (no stack)
void sub_4B2BC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004b2bc0
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 0x30000;
    a0 = 1;
    a1 = v0 | 0x1A9;
    gen::fn_sub_4C1D50_004c1d50(ctx);  // tail call
}

// sub_4B2E20 [rt2dMaestroAnimsCreate] -- creates a maestro's animation sList (16-byte entries) at +12; the maestro, or
//   0
// 0x004B2E20 sub_4B2E20 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B2E20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b2e20
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x30000;
    sd(ra, sp, 0x10);
    a1 = v0 | 0x1A9;
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 16;
    jal(ctx, 0x4B2E38u, gen::fn_sub_4C1D50_004c1d50);
    sw(v0, s0, 12);
    lw(v0, s0, 12);
    if (v0 == 0) {
        // 0x004b2e50
        charge(ctx, 1);
        s0 = 0;
    }
    // 0x004b2e54 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4B2F10 [rt2dMaestroAnimsStreamRead] -- reads a maestro's animations: the count, the animation sList (+12, made
//   when missing) grown by it, each 16-byte entry cleared (index -1) and read (sub_4B2C80); the maestro, or 0
// 0x004B2F10 sub_4B2F10 -- 284 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B2F10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b2f10
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    a2 = 4;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    s1 = a1;
    sq(s0, sp, 0x0);
    a0 = s1;
    a1 = addiu(sp, 0x5C);
    jal(ctx, 0x4B2F38u, gen::fn_sub_4C1910_004c1910);
    if (v0 == 0) {
        // 0x004b2fe0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004b2f48
        charge(ctx, 3);
        lw(v0, sp, 0x5C);
        if (i64(v0) > 0) {
            // 0x004b2f54
            charge(ctx, 3);
            lw(a0, s2, 12);
            if (a0 == 0) {
                // 0x004b2fe8
                charge(ctx, 7);
                v0 = 0x30000;
                a0 = 16;
                a1 = v0 | 0x1A9;
                jal(ctx, 0x4B2FF0u, gen::fn_sub_4C1D50_004c1d50);
                sw(v0, s2, 12);
                lw(a0, s2, 12);
                backedge(ctx);
            }
            // 0x004b2f60
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x004b300c
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x004b2f68
                charge(ctx, 6);
                lw(a1, sp, 0x5C);
                v0 = 0x30000;
                a2 = v0 | 0x1A9;
                jal(ctx, 0x4B2F70u, gen::fn_sub_4C1F70_004c1f70);
                if (v0 != 0) {
                    // 0x004b2f80
                    charge(ctx, 5);
                    lw(v1, sp, 0x5C);
                    v1 = sll(v1, 4);
                    s3 = addu(v0, v1);
                    s0 = v0;
                    if (v0 == s3) {
                        goto L_004b2fd8;
                    }
                    for (;;) {
                        // 0x004b2f94
                        charge(ctx, 11);
                        sw(zero, s0, 0);
                        v0 = si(-1);
                        sw(v0, s0, 4);
                        a0 = s2;
                        sw(zero, s0, 8);
                        a1 = s0;
                        a2 = s1;
                        link(ctx, 0x4B2FB0u);  // $ra first: the delay slot below depends on it
                        sw(zero, s0, 12);
                        call(ctx, gen::fn_sub_4B2C80_004b2c80);
                        if (v0 == 0) {
                            goto L_004b2fc0_7;
                        }
                        // 0x004b2fc8
                        charge(ctx, 3);
                        s0 = addiu(s0, 16);
                        if (s0 == s3) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004b2fd4
                    charge(ctx, 1);
                    goto L_004b2fd8;
                }
                // 0x004b3004
                charge(ctx, 2);
                v0 = 0;
            }
            // 0x004b3010 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_004b2fd8:
        charge(ctx, 2);
        v0 = s2;
    }
    // 0x004b3010 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004b2fc0_7:
    charge(ctx, 2);
    v0 = 0;
    // 0x004b3010 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4B3160 [rt2dMaestroButtonsStreamRead] -- reads a maestro's buttons: three counts, the button sList (+16, made
//   when missing; the maestro made from the free list when $a0 is 0) grown, each 144-byte button initialised (every index
//   -1) and read (three words and its 4-byte-per-state transition table); the maestro, or 0
// 0x004B3160 sub_4B3160 -- 728 bytes; frame 0xA0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B3160(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b3160
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (s5 == 0) {
        // 0x004b3328
        charge(ctx, 4);
        jal(ctx, 0x4B3328u, gen::fn_sub_4B43C0_004b43c0);
        s5 = v0;
        backedge(ctx);
    }
    // 0x004b3194
    charge(ctx, 2);
    if (s5 == 0) {
        // 0x004b3338
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004b319c
        charge(ctx, 6);
        a0 = s4;
        a1 = addiu(sp, 0x9C);
        a2 = 4;
        jal(ctx, 0x4B31A4u, gen::fn_sub_4C1910_004c1910);
        if (v0 == 0) {
            // 0x004b3340
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004b31b4
            charge(ctx, 6);
            a0 = s4;
            a1 = addiu(sp, 0x98);
            a2 = 4;
            jal(ctx, 0x4B31BCu, gen::fn_sub_4C1910_004c1910);
            if (v0 == 0) {
                // 0x004b3348
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004b31cc
                charge(ctx, 6);
                a0 = s4;
                a1 = addiu(sp, 0x94);
                a2 = 4;
                jal(ctx, 0x4B31D4u, gen::fn_sub_4C1910_004c1910);
                if (v0 == 0) {
                    // 0x004b3350
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x004b31e4
                    charge(ctx, 3);
                    lw(v0, sp, 0x9C);
                    if (i64(v0) > 0) {
                        // 0x004b31f0
                        charge(ctx, 3);
                        lw(v0, s5, 16);
                        if (v0 == 0) {
                            // 0x004b3358
                            charge(ctx, 4);
                            a0 = s5;
                            jal(ctx, 0x4B3358u, gen::fn_sub_4B3440_004b3440);
                            lw(a0, s5, 16);
                            backedge(ctx);
                        } else {
                            // 0x004b31fc
                            charge(ctx, 1);
                            lw(a0, s5, 16);
                        }
                        // 0x004b3200
                        charge(ctx, 2);
                        if (a0 == 0) {
                            // 0x004b3408
                            charge(ctx, 1);
                            v0 = 0;
                        } else {
                            // 0x004b3208
                            charge(ctx, 6);
                            lw(a1, sp, 0x9C);
                            v0 = 0x30000;
                            a2 = v0 | 0x1B1;
                            jal(ctx, 0x4B3210u, gen::fn_sub_4C1F70_004c1f70);
                            if (v0 == 0) {
                                // 0x004b3368
                                charge(ctx, 2);
                                v0 = 0;
                            } else {
                                // 0x004b3220
                                charge(ctx, 7);
                                lw(a0, sp, 0x9C);
                                v1 = sll(a0, 3);
                                v1 = addu(v1, a0);
                                v1 = sll(v1, 4);
                                s1 = addu(v0, v1);
                                s3 = v0;
                                if (v0 == s1) {
                                    goto L_004b3320;
                                }
                                // 0x004b323c
                                charge(ctx, 4);
                                s6 = 0x960000;
                                s7 = 0x960000;
                                s6 = addiu(s6, 392);  // &0x960188
                                s7 = addiu(s7, 396);  // &0x96018C
                                for (;;) {
                                    // 0x004b324c
                                    charge(ctx, 7);
                                    v1 = si(-1);
                                    a1 = 0;
                                    sw(v1, s3, 0);
                                    a0 = s3;
                                    sw(v1, s3, 4);
                                    sw(zero, s3, 8);
                                    sw(zero, s3, 12);
                                    for (;;) {
                                        // 0x004b3268
                                        charge(ctx, 12);
                                        sw(v1, a0, 16);
                                        sw(v1, a0, 20);
                                        a1 = addiu(a1, 8);
                                        sw(v1, a0, 24);
                                        v0 = slti(a1, 32);
                                        sw(v1, a0, 28);
                                        sw(v1, a0, 32);
                                        sw(v1, a0, 36);
                                        sw(v1, a0, 40);
                                        sw(v1, a0, 44);
                                        a0 = addiu(a0, 32);
                                        if (v0 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004b3298
                                    charge(ctx, 3);
                                    lw(s0, sp, 0x94);
                                    s2 = s3;
                                    if (s3 != 0) {
                                        // 0x004b32a4
                                        charge(ctx, 1);
                                        goto L_004b32a8;
                                    }
                                    // 0x004b3370
                                    charge(ctx, 8);
                                    v0 = 0x30000;
                                    a0 = 0x960000;
                                    a1 = v0 | 0x1A9;
                                    lw(v0, s6, 0);
                                    a0 = addiu(a0, -1420);  // &0x95FA74
                                    jalr(ctx, 0x4B3380u, v0.u());
                                    s2 = v0;
                                    if (v0 == 0) {
                                        // 0x004b33b0
                                        charge(ctx, 2);
                                        s2 = 0;
                                        backedge(ctx);
                                    } else {
                                        // 0x004b3390
                                        charge(ctx, 4);
                                        a0 = s2;
                                        jal(ctx, 0x4B3390u, gen::fn_sub_4B30A0_004b30a0);
                                        if (v0 == 0) {
                                            // 0x004b33b8
                                            charge(ctx, 9);
                                            a0 = s2;
                                            jal(ctx, 0x4B33B8u, gen::fn_sub_4B3100_004b3100);
                                            lw(v0, s7, 0);
                                            a0 = 0x960000;
                                            a1 = s2;
                                            a0 = addiu(a0, -1420);  // &0x95FA74
                                            jalr(ctx, 0x4B33CCu, v0.u());
                                            s2 = 0;
                                            backedge(ctx);
                                        }
                                    }
                                    // 0x004b33a0
                                    charge(ctx, 2);
                                    if (s2 != 0) {
                                        backedge(ctx);
                                    L_004b32a8:
                                        charge(ctx, 6);
                                        a0 = s4;
                                        a1 = s2;
                                        a2 = 4;
                                        jal(ctx, 0x4B32B0u, gen::fn_sub_4C1910_004c1910);
                                        if (v0 == 0) {
                                            // 0x004b33e0
                                            charge(ctx, 2);
                                            s2 = 0;
                                            backedge(ctx);
                                        } else {
                                            // 0x004b32c0
                                            charge(ctx, 6);
                                            a0 = s4;
                                            a1 = addiu(s2, 4);
                                            a2 = 4;
                                            jal(ctx, 0x4B32C8u, gen::fn_sub_4C1910_004c1910);
                                            if (v0 == 0) {
                                                // 0x004b33e8
                                                charge(ctx, 2);
                                                s2 = 0;
                                                backedge(ctx);
                                            } else {
                                                // 0x004b32d8
                                                charge(ctx, 6);
                                                a0 = s4;
                                                a1 = addiu(s2, 8);
                                                a2 = 4;
                                                jal(ctx, 0x4B32E0u, gen::fn_sub_4C1910_004c1910);
                                                if (v0 == 0) {
                                                    // 0x004b33f0
                                                    charge(ctx, 2);
                                                    s2 = 0;
                                                    backedge(ctx);
                                                } else {
                                                    // 0x004b32f0
                                                    charge(ctx, 6);
                                                    a2 = sll(s0, 2);
                                                    a0 = s4;
                                                    a1 = addiu(s2, 16);
                                                    jal(ctx, 0x4B32F8u, gen::fn_sub_4C1910_004c1910);
                                                    if (v0 == 0) {
                                                        // 0x004b33f8
                                                        charge(ctx, 2);
                                                        s2 = 0;
                                                        backedge(ctx);
                                                    }
                                                }
                                            }
                                        }
                                    } else {
                                        // 0x004b33a8
                                        charge(ctx, 2);
                                        s2 = 0;
                                        backedge(ctx);
                                    }
                                    // 0x004b3308
                                    charge(ctx, 2);
                                    if (s2 == 0) {
                                        break;
                                    }
                                    // 0x004b3310
                                    charge(ctx, 3);
                                    s3 = addiu(s3, 144);
                                    if (s3 == s1) {
                                        goto L_004b331c_22;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004b3400
                                charge(ctx, 2);
                                v0 = 0;
                            }
                        }
                        // 0x004b340c (the shared epilogue, written out on this path)
                        charge(ctx, 11);
                        ld(ra, sp, 0x80);
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
                    }
                L_004b3320:
                    charge(ctx, 2);
                    v0 = s5;
                }
            }
        }
    }
    // 0x004b340c (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x80);
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
L_004b331c_22:
    charge(ctx, 1);
    goto L_004b3320;
}

// sub_4B3440 [rt2dMaestroButtonsCreate] -- creates a maestro's button sList (144-byte entries) at +16; the maestro, or
//   0
// 0x004B3440 sub_4B3440 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B3440(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b3440
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x30000;
    sd(ra, sp, 0x10);
    a1 = v0 | 0x1B1;
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 144;
    jal(ctx, 0x4B3458u, gen::fn_sub_4C1D50_004c1d50);
    sw(v0, s0, 16);
    lw(v0, s0, 16);
    if (v0 == 0) {
        // 0x004b3470
        charge(ctx, 1);
        s0 = 0;
    }
    // 0x004b3474 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4B3730 [rt2dMaestroLabelsCreate] -- creates a maestro's label sLists: the label index (4-byte entries) at +24 and
//   the labels (16-byte entries) at +20; the maestro, or 0
// 0x004B3730 sub_4B3730 -- 96 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B3730(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b3730
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x30000;
    sd(ra, sp, 0x10);
    a1 = v0 | 0x1A9;
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 4;
    jal(ctx, 0x4B3748u, gen::fn_sub_4C1D50_004c1d50);
    sw(v0, s0, 24);
    if (v0 == 0) {
        // 0x004b377c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004b3758
        charge(ctx, 6);
        v0 = 0x30000;
        a0 = 16;
        a1 = v0 | 0x1A9;
        jal(ctx, 0x4B3760u, gen::fn_sub_4C1D50_004c1d50);
        sw(v0, s0, 20);
        if (v0 == 0) {
            // 0x004b3770
            charge(ctx, 1);
            s0 = 0;
        }
        // 0x004b3774
        charge(ctx, 2);
        v0 = s0;
    }
    // 0x004b3780 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4B3900 [rt2dMaestroLabelIndexStreamRead] -- reads a maestro's label index: the count, the index sList (+24, the
//   label sLists made when missing) grown, the 4-byte entries read; the maestro, or 0
// 0x004B3900 sub_4B3900 -- 240 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B3900(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b3900
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a2 = 4;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = s0;
    a1 = addiu(sp, 0x3C);
    jal(ctx, 0x4B3920u, gen::fn_sub_4C1910_004c1910);
    if (v0 == 0) {
        // 0x004b3990
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004b3930
        charge(ctx, 3);
        lw(v0, sp, 0x3C);
        if (i64(v0) > 0) {
            // 0x004b393c
            charge(ctx, 3);
            lw(v0, s1, 24);
            if (v0 == 0) {
                // 0x004b3998
                charge(ctx, 6);
                v0 = 0x30000;
                a0 = 4;
                a1 = v0 | 0x1A9;
                jal(ctx, 0x4B39A0u, gen::fn_sub_4C1D50_004c1d50);
                sw(v0, s1, 24);
                if (v0 == 0) {
                    backedge(ctx);
                } else {
                    // 0x004b39b0
                    charge(ctx, 6);
                    v0 = 0x30000;
                    a0 = 16;
                    a1 = v0 | 0x1A9;
                    jal(ctx, 0x4B39B8u, gen::fn_sub_4C1D50_004c1d50);
                    sw(v0, s1, 20);
                    backedge(ctx);
                }
            }
            // 0x004b3948
            charge(ctx, 3);
            lw(a0, s1, 24);
            if (a0 == 0) {
                // 0x004b39d0
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004b3954
                charge(ctx, 6);
                lw(a1, sp, 0x3C);
                v0 = 0x30000;
                a2 = v0 | 0x1A9;
                jal(ctx, 0x4B395Cu, gen::fn_sub_4C1F70_004c1f70);
                if (v0 == 0) {
                    // 0x004b39c8
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x004b396c
                    charge(ctx, 7);
                    lw(v1, sp, 0x3C);
                    a0 = s0;
                    a1 = v0;
                    a2 = sll(v1, 2);
                    jal(ctx, 0x4B3978u, gen::fn_sub_4C1910_004c1910);
                    if (v0 != 0) {
                        goto L_004b39d8;
                    }
                    // 0x004b3988
                    charge(ctx, 2);
                    v0 = 0;
                }
            }
            // 0x004b39dc (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_004b39d8:
        charge(ctx, 1);
        v0 = s1;
    }
    // 0x004b39dc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4B3AC0 [rt2dMaestroLabelsStreamRead] -- reads a maestro's labels: the count, the label sList (+20, made when
//   missing) grown, each 16-byte label {type, index -1, ...} read and its type's reader called through the table 0x77E3F0
//   (three words per type); the maestro, or 0
// 0x004B3AC0 sub_4B3AC0 -- 512 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B3AC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b3ac0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    a2 = 4;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    s2 = a1;
    sq(s1, sp, 0x10);
    a0 = s2;
    a1 = addiu(sp, 0x5C);
    link(ctx, 0x4B3AE8u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1910_004c1910);
    if (v0 == 0) {
        // 0x004b3c10
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004b3af8
        charge(ctx, 3);
        lw(v0, sp, 0x5C);
        if (i64(v0) > 0) {
            // 0x004b3b04
            charge(ctx, 3);
            lw(v0, s3, 20);
            if (v0 == 0) {
                // 0x004b3c18
                charge(ctx, 6);
                v0 = 0x30000;
                a0 = 4;
                a1 = v0 | 0x1A9;
                jal(ctx, 0x4B3C20u, gen::fn_sub_4C1D50_004c1d50);
                sw(v0, s3, 24);
                if (v0 == 0) {
                    // 0x004b3c5c
                    charge(ctx, 2);
                    v0 = 0;
                    backedge(ctx);
                } else {
                    // 0x004b3c30
                    charge(ctx, 6);
                    v0 = 0x30000;
                    a0 = 16;
                    a1 = v0 | 0x1A9;
                    jal(ctx, 0x4B3C38u, gen::fn_sub_4C1D50_004c1d50);
                    sw(v0, s3, 20);
                    if (v0 == 0) {
                        // 0x004b3c64
                        charge(ctx, 2);
                        v0 = 0;
                        backedge(ctx);
                    } else {
                        // 0x004b3c48
                        charge(ctx, 1);
                        v0 = s3;
                    }
                }
                // 0x004b3c4c
                charge(ctx, 2);
                if (v0 != 0) {
                    backedge(ctx);
                    goto L_004b3b10;
                }
                // 0x004b3c54
                charge(ctx, 2);
                v0 = 0;
                // 0x004b3ca4 (the shared epilogue, written out on this path)
                charge(ctx, 7);
                ld(ra, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x60);
                return;
            }
        L_004b3b10:
            charge(ctx, 7);
            lw(a0, s3, 20);
            v0 = 0x30000;
            lw(a1, sp, 0x5C);
            a2 = v0 | 0x1A9;
            jal(ctx, 0x4B3B1Cu, gen::fn_sub_4C1F70_004c1f70);
            s0 = v0;
            if (v0 == 0) {
                // 0x004b3c6c
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004b3b2c
                charge(ctx, 4);
                lw(v0, sp, 0x5C);
                at = slt(0, v0);
                s1 = 0;
                if (at == 0) {
                    goto L_004b3c08;
                }
                for (;;) {
                    // 0x004b3b3c
                    charge(ctx, 10);
                    sw(zero, s0, 0);
                    v0 = si(-1);
                    sw(v0, s0, 4);
                    a0 = s2;
                    a1 = s0;
                    a2 = 4;
                    link(ctx, 0x4B3B54u);  // $ra first: the delay slot below depends on it
                    sw(zero, s0, 8);
                    call(ctx, gen::fn_sub_4C1910_004c1910);
                    if (v0 == 0) {
                        // 0x004b3c74
                        charge(ctx, 2);
                        v0 = 0;
                        backedge(ctx);
                    } else {
                        // 0x004b3b64
                        charge(ctx, 6);
                        a0 = s2;
                        a1 = addiu(s0, 4);
                        a2 = 4;
                        jal(ctx, 0x4B3B6Cu, gen::fn_sub_4C1910_004c1910);
                        if (v0 == 0) {
                            // 0x004b3c80
                            charge(ctx, 2);
                            v0 = 0;
                            backedge(ctx);
                        } else {
                            // 0x004b3b7c
                            charge(ctx, 6);
                            a0 = s2;
                            a1 = addiu(s0, 8);
                            a2 = 4;
                            jal(ctx, 0x4B3B84u, gen::fn_sub_4C1910_004c1910);
                            if (v0 == 0) {
                                // 0x004b3c88
                                charge(ctx, 2);
                                v0 = 0;
                                backedge(ctx);
                            } else {
                                // 0x004b3b94
                                charge(ctx, 6);
                                a0 = s2;
                                a1 = addiu(s0, 12);
                                a2 = 4;
                                jal(ctx, 0x4B3B9Cu, gen::fn_sub_4C1910_004c1910);
                                if (v0 == 0) {
                                    // 0x004b3c90
                                    charge(ctx, 2);
                                    v0 = 0;
                                    backedge(ctx);
                                } else {
                                    // 0x004b3bac
                                    charge(ctx, 14);
                                    lw(a3, s0, 0);
                                    v0 = 0x780000;
                                    v0 = addiu(v0, -7184);  // &0x77E3F0
                                    a0 = s3;
                                    a1 = s0;
                                    v1 = sll(a3, 1);
                                    v1 = addu(v1, a3);
                                    v1 = sll(v1, 2);
                                    v0 = addu(v0, v1);
                                    lw(v0, v0, 4);
                                    a2 = s2;
                                    jalr(ctx, 0x4B3BD4u, v0.u());
                                    if (v0 == 0) {
                                        // 0x004b3c98
                                        charge(ctx, 2);
                                        v0 = 0;
                                        backedge(ctx);
                                    } else {
                                        // 0x004b3be4
                                        charge(ctx, 1);
                                        v0 = s0;
                                    }
                                }
                            }
                        }
                    }
                    // 0x004b3be8
                    charge(ctx, 2);
                    if (v0 == 0) {
                        break;
                    }
                    // 0x004b3bf0
                    charge(ctx, 5);
                    lw(v0, sp, 0x5C);
                    s1 = addiu(s1, 1);
                    v0 = slt(s1, v0);
                    s0 = addiu(s0, 16);
                    if (v0 == 0) {
                        goto L_004b3c04_13;
                    }
                    backedge(ctx);
                }
                // 0x004b3ca0
                charge(ctx, 1);
                v0 = 0;
            }
            // 0x004b3ca4 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x60);
            return;
        }
    L_004b3c08:
        charge(ctx, 2);
        v0 = s3;
    }
    // 0x004b3ca4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004b3c04_13:
    charge(ctx, 1);
    goto L_004b3c08;
}

// sub_4B4230 [rt2dMaestroInit] -- initialises a maestro record: the lists emptied and created (animation list
//   sub_4B47D0, animations, buttons, labels, the message queue sub_4B40F0, the string buffer sub_4B2BC0), the default
//   message handler (sub_4B5B50), the bounding extent 2^32 x 2^32, the message state (sub_4B34E0 at +88); the maestro
// 0x004B4230 sub_4B4230 -- 172 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B4230(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b4230
    enter(ctx, 43);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = si(-1);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    sw(zero, a0, 0);
    s0 = a0;
    sw(zero, a0, 4);
    sw(zero, a0, 8);
    sw(zero, a0, 12);
    sw(zero, a0, 28);
    sw(zero, a0, 36);
    sw(zero, a0, 16);
    link(ctx, 0x4B4260u);  // $ra first: the delay slot below depends on it
    sw(v0, a0, 68);
    call(ctx, gen::fn_sub_4B47D0_004b47d0);
    a0 = s0;
    jal(ctx, 0x4B4268u, gen::fn_sub_4B2E20_004b2e20);
    a0 = s0;
    jal(ctx, 0x4B4270u, gen::fn_sub_4B3440_004b3440);
    a0 = s0;
    jal(ctx, 0x4B4278u, gen::fn_sub_4B3730_004b3730);
    a0 = s0;
    jal(ctx, 0x4B4280u, gen::fn_sub_4B40F0_004b40f0);
    jal(ctx, 0x4B4288u, gen::fn_sub_4B2BC0_004b2bc0);
    sw(v0, s0, 28);
    a0 = addiu(s0, 88);
    v0 = 0x4B0000;
    v0 = addiu(v0, 23376);  // &sub_4B5B50
    sw(v0, s0, 40);
    v0 = 0x4F800000;
    sw(v0, s0, 44);
    sw(v0, s0, 48);
    sw(zero, s0, 52);
    sw(zero, s0, 72);
    sw(zero, s0, 76);
    sw(zero, s0, 80);
    link(ctx, 0x4B42C0u);  // $ra first: the delay slot below depends on it
    sw(zero, s0, 84);
    call(ctx, gen::fn_sub_4B34E0_004b34e0);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4B42E0 [rt2dMaestroDestroyBody] -- destroys a maestro's contents: the animation list (sub_4B4810), animations
//   (sub_4B2E70), buttons (sub_4B3490), labels (sub_4B3790), its scene (Rt2dSceneDestroy sub_4AE5A0), the message queue
//   (sub_4B41B0), the string buffer (sub_4B2BD0); 1
// 0x004B42E0 sub_4B42E0 -- 220 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B42E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b42e0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 8);
    s0 = a0;
    if (v0 != 0) {
        // 0x004b435c
        charge(ctx, 4);
        jal(ctx, 0x4B435Cu, gen::fn_sub_4B4810_004b4810);
        lw(v0, s0, 12);
        backedge(ctx);
    } else {
        // 0x004b42f8
        charge(ctx, 1);
        lw(v0, s0, 12);
    }
    // 0x004b42fc
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x004b436c
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x4B436Cu, gen::fn_sub_4B2E70_004b2e70);
        lw(v0, s0, 16);
        backedge(ctx);
    } else {
        // 0x004b4304
        charge(ctx, 1);
        lw(v0, s0, 16);
    }
    // 0x004b4308
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x004b437c
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x4B437Cu, gen::fn_sub_4B3490_004b3490);
        lw(v0, s0, 24);
        backedge(ctx);
    } else {
        // 0x004b4310
        charge(ctx, 1);
        lw(v0, s0, 24);
    }
    // 0x004b4314
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x004b438c
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x4B438Cu, gen::fn_sub_4B3790_004b3790);
        lw(a0, s0, 36);
        backedge(ctx);
    } else {
        // 0x004b431c
        charge(ctx, 1);
        lw(a0, s0, 36);
    }
    // 0x004b4320
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x004b4328
        charge(ctx, 2);
        jal(ctx, 0x4B4328u, gen::fn_sub_4AE5A0_004ae5a0);
    }
    // 0x004b4330
    charge(ctx, 3);
    lw(v0, s0, 32);
    if (v0 != 0) {
        // 0x004b439c
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x4B439Cu, gen::fn_sub_4B41B0_004b41b0);
        lw(a0, s0, 28);
        backedge(ctx);
    } else {
        // 0x004b433c
        charge(ctx, 1);
        lw(a0, s0, 28);
    }
    // 0x004b4340
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x004b4348
        charge(ctx, 3);
        jal(ctx, 0x4B4348u, gen::fn_sub_4B2BD0_004b2bd0);
        sw(zero, s0, 28);
    }
    // 0x004b4354
    charge(ctx, 2);
    v0 = 1;
    // 0x004b43ac
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4B4410 [Rt2dMaestroDestroy] -- destroys a maestro: its contents (sub_4B42E0), the record returned to the free
//   list (0x95FA98); 1
// 0x004B4410 sub_4B4410 -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B4410(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b4410
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x4B441Cu, gen::fn_sub_4B42E0_004b42e0);
    v0 = 0x960000;
    a0 = 0x960000;
    lw(v0, v0, 396);  // 0x96018C
    a1 = s0;
    a0 = addiu(a0, -1384);  // &0x95FA98
    jalr(ctx, 0x4B4434u, v0.u());
    ld(ra, sp, 0x10);
    v0 = 1;
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4B4790 [rt2dMaestroAnimApplyCB] -- an animation-list walk callback: the entry's current keyframe applied to its
//   props (sub_4B1620 on +4 / +32); the context, or 0 on a failure
// 0x004B4790 sub_4B4790 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B4790(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b4790
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = addiu(a1, 4);
    a1 = addiu(a1, 32);
    jal(ctx, 0x4B47A4u, gen::fn_sub_4B1620_004b1620);
    if (v0 == 0) {
        // 0x004b47b4
        charge(ctx, 1);
        s0 = 0;
    }
    // 0x004b47b8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4B47D0 [rt2dMaestroAnimListCreate] -- creates a maestro's animation list (60-byte entries) at +8; the maestro, or
//   0
// 0x004B47D0 sub_4B47D0 -- 64 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B47D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b47d0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x30000;
    sd(ra, sp, 0x10);
    a1 = v0 | 0x1A9;
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 60;
    jal(ctx, 0x4B47E8u, gen::fn_sub_4C1D50_004c1d50);
    sw(v0, s0, 8);
    if (v0 == 0) {
        // 0x004b47f8
        charge(ctx, 1);
        s0 = 0;
    }
    // 0x004b47fc (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4B4860 [rt2dMaestroAnimListStreamRead] -- reads a maestro's animation list: the count, the 60-byte entries (the
//   list made when missing), each {type 2, parent / object index -1, a message list (sub_4B6040 / sub_4B5EC0), the two
//   indices, a 28-byte record (sub_4C1970), its props for the scene object (sub_4B5270 / sub_4B2AD0), its keyframes
//   (sub_4B1290)}; the first entry made current (sub_4C21B0); the maestro, or 0
// 0x004B4860 sub_4B4860 -- 500 bytes; frame 0x70: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B4860(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b4860
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    a2 = 4;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    s2 = a1;
    sq(s1, sp, 0x10);
    a0 = s2;
    a1 = addiu(sp, 0x6C);
    link(ctx, 0x4B4888u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4C1910_004c1910);
    if (v0 == 0) {
        // 0x004b49d4
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004b4898
        charge(ctx, 3);
        lw(v0, sp, 0x6C);
        if (i64(v0) > 0) {
            // 0x004b48a4
            charge(ctx, 3);
            lw(v0, s3, 8);
            if (v0 == 0) {
                // 0x004b49dc
                charge(ctx, 6);
                v0 = 0x30000;
                a0 = 60;
                a1 = v0 | 0x1A9;
                jal(ctx, 0x4B49E4u, gen::fn_sub_4C1D50_004c1d50);
                sw(v0, s3, 8);
                backedge(ctx);
            }
            // 0x004b48b0
            charge(ctx, 3);
            lw(a0, s3, 8);
            if (a0 == 0) {
                // 0x004b4a34
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x004b48bc
                charge(ctx, 6);
                lw(a1, sp, 0x6C);
                v0 = 0x30000;
                a2 = v0 | 0x1A9;
                jal(ctx, 0x4B48C4u, gen::fn_sub_4C1F70_004c1f70);
                s0 = v0;
                if (v0 != 0) {
                    // 0x004b48d4
                    charge(ctx, 4);
                    lw(v0, sp, 0x6C);
                    at = slt(0, v0);
                    s1 = 0;
                    if (at != 0) {
                        for (;;) {
                            // 0x004b48e4
                            charge(ctx, 8);
                            v1 = 2;
                            v0 = si(-1);
                            sw(v1, s0, 0);
                            sw(v0, s0, 52);
                            link(ctx, 0x4B48F4u);  // $ra first: the delay slot below depends on it
                            sw(v0, s0, 56);
                            call(ctx, gen::fn_sub_4B6040_004b6040);
                            sw(v0, s0, 48);
                            if (v0 != 0) {
                                // 0x004b490c
                                charge(ctx, 1);
                                v0 = s0;
                            } else {
                                // 0x004b4904
                                charge(ctx, 2);
                                v0 = 0;
                            }
                            // 0x004b4910
                            charge(ctx, 2);
                            if (v0 == 0) {
                                goto L_004b49fc;
                            }
                            // 0x004b4918
                            charge(ctx, 6);
                            lw(a1, s0, 48);
                            a0 = s3;
                            a2 = s2;
                            jal(ctx, 0x4B4920u, gen::fn_sub_4B5EC0_004b5ec0);
                            if (v0 == 0) {
                                goto L_004b4a04;
                            }
                            // 0x004b4930
                            charge(ctx, 6);
                            a0 = s2;
                            a1 = addiu(s0, 52);
                            a2 = 4;
                            jal(ctx, 0x4B4938u, gen::fn_sub_4C1910_004c1910);
                            if (v0 == 0) {
                                goto L_004b4a0c;
                            }
                            // 0x004b4948
                            charge(ctx, 6);
                            a0 = s2;
                            a1 = addiu(s0, 56);
                            a2 = 4;
                            jal(ctx, 0x4B4950u, gen::fn_sub_4C1910_004c1910);
                            if (v0 == 0) {
                                goto L_004b4a14;
                            }
                            // 0x004b4960
                            charge(ctx, 5);
                            a0 = s2;
                            a1 = addiu(sp, 0x50);
                            jal(ctx, 0x4B4964u, gen::fn_sub_4C1970_004c1970);
                            if (v0 == 0) {
                                goto L_004b4a1c;
                            }
                            // 0x004b4974
                            charge(ctx, 8);
                            a0 = s3;
                            a1 = s1;
                            jal(ctx, 0x4B4978u, gen::fn_sub_4B5270_004b5270);
                            a0 = addiu(s0, 32);
                            a1 = v0;
                            jal(ctx, 0x4B4984u, gen::fn_sub_4B2AD0_004b2ad0);
                            if (v0 == 0) {
                                goto L_004b4a24;
                            }
                            // 0x004b4994
                            charge(ctx, 6);
                            a0 = addiu(s0, 4);
                            a1 = s2;
                            a2 = addiu(s0, 32);
                            jal(ctx, 0x4B499Cu, gen::fn_sub_4B1290_004b1290);
                            if (v0 == 0) {
                                goto L_004b4a2c;
                            }
                            // 0x004b49ac
                            charge(ctx, 5);
                            lw(v0, sp, 0x6C);
                            s1 = addiu(s1, 1);
                            v0 = slt(s1, v0);
                            s0 = addiu(s0, 60);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                    // 0x004b49c0
                    charge(ctx, 3);
                    lw(a0, s3, 8);
                    a1 = 0;
                    jal(ctx, 0x4B49C4u, gen::fn_sub_4C21B0_004c21b0);
                    goto L_004b49cc;
                }
                // 0x004b49f4
                charge(ctx, 2);
                v0 = 0;
            }
            // 0x004b4a38 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x70);
            return;
        }
    L_004b49cc:
        charge(ctx, 2);
        v0 = s3;
    }
    // 0x004b4a38 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004b49fc:
    charge(ctx, 2);
    v0 = 0;
    // 0x004b4a38 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004b4a04:
    charge(ctx, 2);
    v0 = 0;
    // 0x004b4a38 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004b4a0c:
    charge(ctx, 2);
    v0 = 0;
    // 0x004b4a38 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004b4a14:
    charge(ctx, 2);
    v0 = 0;
    // 0x004b4a38 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004b4a1c:
    charge(ctx, 2);
    v0 = 0;
    // 0x004b4a38 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004b4a24:
    charge(ctx, 2);
    v0 = 0;
    // 0x004b4a38 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004b4a2c:
    charge(ctx, 2);
    v0 = 0;
    // 0x004b4a38 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// sub_4B4CC0 [rt2dMaestroSceneStreamRead] -- reads a maestro's scene: a flag word and, when set, the scene chunk (421)
//   read (Rt2dSceneStreamRead sub_4AEEA0) into +36; the maestro, or 0
// 0x004B4CC0 sub_4B4CC0 -- 152 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B4CC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b4cc0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a2 = 4;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = s0;
    a1 = addiu(sp, 0x3C);
    jal(ctx, 0x4B4CE0u, gen::fn_sub_4C1910_004c1910);
    if (v0 == 0) {
        // 0x004b4d04
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004b4cf0
        charge(ctx, 3);
        lw(v0, sp, 0x3C);
        if (i64(v0) > 0) {
            // 0x004b4d0c
            charge(ctx, 7);
            a0 = s0;
            a1 = 421;
            a2 = addiu(sp, 0x38);
            a3 = addiu(sp, 0x34);
            jal(ctx, 0x4B4D18u, gen::fn_sub_4C1600_004c1600);
            if (v0 != 0) {
                // 0x004b4d30
                charge(ctx, 4);
                a0 = s0;
                jal(ctx, 0x4B4D30u, gen::fn_sub_4AEEA0_004aeea0);
                sw(v0, s1, 36);
                if (v0 != 0) {
                    backedge(ctx);
                    goto L_004b4cfc;
                }
                // 0x004b4d40
                charge(ctx, 1);
                v0 = 0;
            } else {
                // 0x004b4d28
                charge(ctx, 2);
                v0 = 0;
            }
            // 0x004b4d44 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x40);
            return;
        }
    L_004b4cfc:
        charge(ctx, 2);
        v0 = s1;
    }
    // 0x004b4d44 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4B4D70 [rt2dMaestroAnimUpdateCB] -- updates one maestro animation: just restarted (flag 2): its keyframe's
//   message posted (sub_4B39F0) when it has one, the messages processed (sub_4B3CC0 / sub_4B5380); when its scene object
//   is visible (sub_4AE010) and it is not stopped (flag 1) its time advanced (sub_4B14C0) and the new keyframe's message
//   posted on a change; the maestro, or 0
// 0x004B4D70 sub_4B4D70 -- 308 bytes; frame 0x60: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
void sub_4B4D70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f20{ctx, 20};
    // 0x004b4d70
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    sq(s1, sp, 0x20);
    s2 = a0;
    sq(s0, sp, 0x10);
    s1 = a1;
    swc1(f20, sp, 0x0);
    lwc1(f20, a2, 0);
    a0 = addiu(s1, 4);
    jal(ctx, 0x4B4D98u, gen::fn_sub_4B1A80_004b1a80);
    lw(v1, s1, 0);
    s0 = v0;
    v0 = v1 & 0x2;
    if (v0 != 0) {
        // 0x004b4e30
        charge(ctx, 11);
        v0 = si(-3);
        v0 = v1 & v0;
        sw(v0, s1, 0);
        lw(v0, s1, 48);
        link(ctx, 0x4B4E40u);  // $ra first: the delay slot below depends on it
        lw(a0, v0, 0);
        call(ctx, gen::fn_sub_4C2090_004c2090);
        v1 = sll(s0, 4);
        v0 = addu(v0, v1);
        lw(a1, v0, 12);
        if (i64(a1) >= 0) {
            // 0x004b4e5c
            charge(ctx, 2);
            a0 = s2;
            jal(ctx, 0x4B4E5Cu, gen::fn_sub_4B39F0_004b39f0);
        }
        // 0x004b4e64
        charge(ctx, 7);
        a0 = s2;
        jal(ctx, 0x4B4E64u, gen::fn_sub_4B3CC0_004b3cc0);
        a0 = s2;
        a1 = addiu(s2, 44);
        jal(ctx, 0x4B4E70u, gen::fn_sub_4B5380_004b5380);
        backedge(ctx);
    }
    // 0x004b4db4
    charge(ctx, 4);
    link(ctx, 0x4B4DB4u);  // $ra first: the delay slot below depends on it
    lw(a0, s1, 32);
    call(ctx, gen::fn_sub_4AE010_004ae010);
    if (v0 != 0) {
        // 0x004b4dc4
        charge(ctx, 4);
        lw(v0, s1, 0);
        v0 = v0 & 0x1;
        if (v0 != 0) {
            goto L_004b4e28;
        }
        // 0x004b4dd4
        charge(ctx, 6);
        mov_s(f12, f20);
        a0 = addiu(s1, 4);
        a1 = addiu(s1, 32);
        jal(ctx, 0x4B4DDCu, gen::fn_sub_4B14C0_004b14c0);
        if (v0 != 0) {
            // 0x004b4dec
            charge(ctx, 5);
            a0 = addiu(s1, 4);
            jal(ctx, 0x4B4DECu, gen::fn_sub_4B1A80_004b1a80);
            s3 = v0;
            if (s0 != s3) {
                // 0x004b4e00
                charge(ctx, 8);
                lw(v0, s1, 48);
                link(ctx, 0x4B4E04u);  // $ra first: the delay slot below depends on it
                lw(a0, v0, 0);
                call(ctx, gen::fn_sub_4C2090_004c2090);
                v1 = sll(s3, 4);
                v0 = addu(v0, v1);
                lw(a1, v0, 12);
                if (i64(a1) >= 0) {
                    // 0x004b4e20
                    charge(ctx, 2);
                    a0 = s2;
                    jal(ctx, 0x4B4E20u, gen::fn_sub_4B39F0_004b39f0);
                }
            }
            goto L_004b4e28;
        }
        // 0x004b4e80
        charge(ctx, 1);
        v0 = 0;
        // 0x004b4e84 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x50);
        lwc1(f20, sp, 0x0);
        lq(s3, sp, 0x40);
        lq(s2, sp, 0x30);
        lq(s1, sp, 0x20);
        lq(s0, sp, 0x10);
        sp = addiu(sp, 0x60);
        return;
    }
L_004b4e28:
    charge(ctx, 2);
    v0 = s2;
    // 0x004b4e84 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lwc1(f20, sp, 0x0);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x60);
}

// sub_4B4EB0 [rt2dMaestroAnimRewind] -- rewinds a maestro animation that reached its end (not looping) or when forced
//   ($a2): its keyframe list to entry 0 (sub_4B1870), flag 2 set, and every later animation parented to it reset as well
//   (recursively) with its scene object's visibility cleared (sub_4AE900 / sub_4ADFD0); the maestro
// 0x004B4EB0 sub_4B4EB0 -- 336 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B4EB0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x004b4eb0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(v0, a1, 0);
    v0 = v0 & 0x1;
    s0 = a2;
    if (v0 == 0) {
        // 0x004b4f80
        charge(ctx, 6);
        a0 = addiu(s1, 4);
        jal(ctx, 0x4B4F80u, gen::fn_sub_4B1A70_004b1a70);
        lwc1(f1, s1, 12);
        c_lt_s(f1, f0);
        if (cond(ctx)) {
            // 0x004b4f98
            charge(ctx, 2);
            backedge(ctx);
            goto L_004b4ee4;
        }
        backedge(ctx);
    L_004b4eec:
        charge(ctx, 25);
        link(ctx, 0x4B4EECu);  // $ra first: the delay slot below depends on it
        lw(a0, s2, 8);
        call(ctx, gen::fn_sub_4C21E0_004c21e0);
        lw(a0, s2, 8);
        s0 = v0;
        jal(ctx, 0x4B4EF8u, gen::fn_sub_4C2090_004c2090);
        a3 = subu(s1, v0);
        v0 = lui(0x8888);
        v0 = v0 | 0x8889;
        mult(zero, v0, a3);
        v1 = srl(a3, 31);
        mfhi(v0);
        a0 = addiu(s1, 4);
        a1 = addiu(s1, 32);
        a2 = 0;
        v0 = addu(v0, a3);
        v0 = sra(v0, 5);
        s3 = addu(v0, v1);
        jal(ctx, 0x4B4F30u, gen::fn_sub_4B1870_004b1870);
        lw(v0, s1, 0);
        v0 = v0 | 0x2;
        sw(v0, s1, 0);
        s1 = addiu(s1, 60);
        if (s1 != s0) {
            for (;;) {
                // 0x004b4f50
                charge(ctx, 3);
                lw(a1, s1, 52);
                if (a1 == s3) {
                    // 0x004b4fa0
                    charge(ctx, 15);
                    a0 = s2;
                    jal(ctx, 0x4B4FA0u, gen::fn_sub_4B5270_004b5270);
                    lw(a1, s1, 56);
                    a0 = v0;
                    jal(ctx, 0x4B4FACu, gen::fn_sub_4AE900_004ae900);
                    s4 = v0;
                    a0 = s2;
                    a1 = s1;
                    a2 = 1;
                    jal(ctx, 0x4B4FC0u, gen::fn_sub_4B4EB0_004b4eb0);
                    a0 = s4;
                    a1 = 0;
                    jal(ctx, 0x4B4FCCu, gen::fn_sub_4ADFD0_004adfd0);
                    backedge(ctx);
                } else {
                    // 0x004b4f5c
                    charge(ctx, 1);
                }
                // 0x004b4f60
                charge(ctx, 5);
                s1 = addiu(s1, 60);
                if (s1 == s0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004b4f74
            charge(ctx, 1);
        }
        goto L_004b4f78;
    }
L_004b4ee4:
    charge(ctx, 2);
    if (s0 != 0) {
        goto L_004b4eec;
    }
L_004b4f78:
    charge(ctx, 2);
    v0 = s2;
    // 0x004b4fe0
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4B5D80 [rt2dMaestroMsgStreamRead] -- reads one maestro message record: two words, a count and that many 4-byte
//   entries into its sList (made when missing), a final word; the record, or 0
// 0x004B5D80 sub_4B5D80 -- 308 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B5D80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b5d80
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    a0 = s0;
    a2 = 4;
    jal(ctx, 0x4B5D9Cu, gen::fn_sub_4C1910_004c1910);
    if (v0 == 0) {
        // 0x004b5e3c
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004b5dac
        charge(ctx, 6);
        a0 = s0;
        a1 = addiu(s1, 4);
        a2 = 4;
        jal(ctx, 0x4B5DB4u, gen::fn_sub_4C1910_004c1910);
        if (v0 == 0) {
            // 0x004b5e44
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004b5dc4
            charge(ctx, 6);
            a0 = s0;
            a1 = addiu(sp, 0x3C);
            a2 = 4;
            jal(ctx, 0x4B5DCCu, gen::fn_sub_4C1910_004c1910);
            if (v0 == 0) {
                // 0x004b5e4c
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004b5ddc
                charge(ctx, 3);
                lw(v0, sp, 0x3C);
                if (i64(v0) > 0) {
                    // 0x004b5de8
                    charge(ctx, 3);
                    lw(v0, s1, 8);
                    if (v0 == 0) {
                        // 0x004b5e54
                        charge(ctx, 6);
                        v0 = 0x30000;
                        a0 = 4;
                        a1 = v0 | 0x1A9;
                        jal(ctx, 0x4B5E5Cu, gen::fn_sub_4C1D50_004c1d50);
                        sw(v0, s1, 8);
                        backedge(ctx);
                    }
                    // 0x004b5df4
                    charge(ctx, 3);
                    lw(a0, s1, 8);
                    if (a0 == 0) {
                        // 0x004b5e6c
                        charge(ctx, 2);
                        v0 = 0;
                    } else {
                        // 0x004b5e00
                        charge(ctx, 6);
                        lw(a1, sp, 0x3C);
                        v0 = 0x30000;
                        a2 = v0 | 0x1A9;
                        jal(ctx, 0x4B5E08u, gen::fn_sub_4C1F70_004c1f70);
                        if (v0 == 0) {
                            // 0x004b5e74
                            charge(ctx, 2);
                            v0 = 0;
                        } else {
                            // 0x004b5e18
                            charge(ctx, 7);
                            lw(v1, sp, 0x3C);
                            a0 = s0;
                            a1 = v0;
                            a2 = sll(v1, 2);
                            jal(ctx, 0x4B5E24u, gen::fn_sub_4C1910_004c1910);
                            if (v0 != 0) {
                                goto L_004b5e7c;
                            }
                            // 0x004b5e34
                            charge(ctx, 2);
                            v0 = 0;
                        }
                    }
                    // 0x004b5ea0 (the shared epilogue, written out on this path)
                    charge(ctx, 5);
                    ld(ra, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x40);
                    return;
                }
            L_004b5e7c:
                charge(ctx, 6);
                a0 = s0;
                a1 = addiu(s1, 12);
                a2 = 4;
                jal(ctx, 0x4B5E84u, gen::fn_sub_4C1910_004c1910);
                if (v0 == 0) {
                    // 0x004b5e9c
                    charge(ctx, 1);
                    v0 = 0;
                } else {
                    // 0x004b5e94
                    charge(ctx, 2);
                    v0 = s1;
                }
            }
        }
    }
    // 0x004b5ea0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4B5EC0 [rt2dMaestroMsgListStreamRead] -- reads a maestro message list (a new one when $a1 is 0, sub_4B6040 /
//   sub_4B6270): the count, the 16-byte records (indices -1, each with its own 4-byte sList) read by sub_4B5D80; the
//   list, or 0
// 0x004B5EC0 sub_4B5EC0 -- 308 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B5EC0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b5ec0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    if (s3 != 0) {
        // 0x004b5eec
        charge(ctx, 1);
        a0 = s2;
        goto L_004b5ef0;
    }
    // 0x004b5f18
    charge(ctx, 4);
    jal(ctx, 0x4B5F18u, gen::fn_sub_4B6040_004b6040);
    s3 = v0;
    if (v0 == 0) {
        // 0x004b5f38
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004b5f28
        charge(ctx, 4);
        a0 = s3;
        jal(ctx, 0x4B5F28u, gen::fn_sub_4B6270_004b6270);
        a0 = s2;
        backedge(ctx);
    L_004b5ef0:
        charge(ctx, 5);
        a1 = addiu(sp, 0x6C);
        a2 = 4;
        jal(ctx, 0x4B5EF4u, gen::fn_sub_4C1910_004c1910);
        if (v0 == 0) {
            // 0x004b5f40
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004b5f04
            charge(ctx, 3);
            lw(a1, sp, 0x6C);
            if (i64(a1) > 0) {
                // 0x004b5f48
                charge(ctx, 6);
                lw(a0, s3, 0);
                v0 = 0x30000;
                a2 = v0 | 0x1A9;
                jal(ctx, 0x4B5F50u, gen::fn_sub_4C1F70_004c1f70);
                s0 = v0;
                if (v0 != 0) {
                    // 0x004b5f60
                    charge(ctx, 4);
                    lw(v0, sp, 0x6C);
                    at = slt(0, v0);
                    s1 = 0;
                    if (at == 0) {
                        backedge(ctx);
                        goto L_004b5f10;
                    }
                    for (;;) {
                        // 0x004b5f70
                        charge(ctx, 15);
                        v1 = si(-1);
                        v0 = 0x30000;
                        sw(v1, s0, 0);
                        a0 = 4;
                        sw(v1, s0, 4);
                        a1 = v0 | 0x1A9;
                        link(ctx, 0x4B5F88u);  // $ra first: the delay slot below depends on it
                        sw(v1, s0, 12);
                        call(ctx, gen::fn_sub_4C1D50_004c1d50);
                        sw(v0, s0, 8);
                        a0 = s4;
                        a1 = s0;
                        a2 = s2;
                        jal(ctx, 0x4B5F9Cu, gen::fn_sub_4B5D80_004b5d80);
                        if (v0 == 0) {
                            goto L_004b5fac_12;
                        }
                        // 0x004b5fb4
                        charge(ctx, 5);
                        lw(v0, sp, 0x6C);
                        s1 = addiu(s1, 1);
                        v0 = slt(s1, v0);
                        s0 = addiu(s0, 16);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004b5fc8
                    charge(ctx, 2);
                    backedge(ctx);
                    goto L_004b5f10;
                }
                // 0x004b5fd0
                charge(ctx, 1);
                v0 = 0;
                // 0x004b5fd4 (the shared epilogue, written out on this path)
                charge(ctx, 8);
                ld(ra, sp, 0x50);
                lq(s4, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x70);
                return;
            }
        L_004b5f10:
            charge(ctx, 2);
            v0 = s3;
        }
    }
    // 0x004b5fd4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
    return;
L_004b5fac_12:
    charge(ctx, 2);
    v0 = 0;
    // 0x004b5fd4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// sub_4B6040 [rt2dMaestroMsgListCreate] -- creates a maestro message list from the free list (0x95FB94): a
//   16-byte-record sList and reference count 1; on an allocation failure the half-made list is torn down; the list, or 0
// 0x004B6040 sub_4B6040 -- 324 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4B6040(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b6040
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    a0 = 0x960000;
    sd(ra, sp, 0x40);
    v1 = 0x30000;
    sq(s3, sp, 0x30);
    v0 = 0x960000;
    sq(s2, sp, 0x20);
    a0 = addiu(a0, -1132);  // &0x95FB94
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, v0, 392);  // 0x960188
    a1 = v1 | 0x1A9;
    jalr(ctx, 0x4B606Cu, v0.u());
    s0 = v0;
    if (v0 == 0) {
        // 0x004b60b0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004b607c
        charge(ctx, 6);
        v0 = 0x30000;
        a0 = 16;
        a1 = v0 | 0x1A9;
        jal(ctx, 0x4B6084u, gen::fn_sub_4C1D50_004c1d50);
        sw(v0, s0, 0);
        if (v0 == 0) {
            // 0x004b60b8
            charge(ctx, 2);
            v1 = 0;
            backedge(ctx);
        } else {
            // 0x004b6094
            charge(ctx, 3);
            v0 = 1;
            v1 = s0;
            sw(v0, s0, 4);
        }
        // 0x004b60a0
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x004b60c0
            charge(ctx, 3);
            lw(a0, s0, 0);
            if (a0 != 0) {
                // 0x004b60cc
                charge(ctx, 7);
                jal(ctx, 0x4B60CCu, gen::fn_sub_4C2120_004c2120);
                lw(a0, s0, 0);
                s1 = v0;
                jal(ctx, 0x4B60D8u, gen::fn_sub_4C2090_004c2090);
                s2 = v0;
                if (i64(s1) > 0) {
                    // 0x004b60e8
                    charge(ctx, 2);
                    if (s2 != 0) {
                        // 0x004b60f0
                        charge(ctx, 3);
                        at = slt(0, s1);
                        s3 = 0;
                        if (at != 0) {
                            for (;;) {
                                // 0x004b60fc
                                charge(ctx, 3);
                                lw(a0, s2, 8);
                                if (a0 != 0) {
                                    // 0x004b6108
                                    charge(ctx, 2);
                                    jal(ctx, 0x4B6108u, gen::fn_sub_4C20B0_004c20b0);
                                }
                                // 0x004b6110
                                charge(ctx, 9);
                                sw(zero, s2, 8);
                                v1 = si(-1);
                                s3 = addiu(s3, 1);
                                sw(v1, s2, 0);
                                v0 = slt(s3, s1);
                                sw(v1, s2, 4);
                                sw(v1, s2, 12);
                                s2 = addiu(s2, 16);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004b6134
                            charge(ctx, 1);
                        }
                    }
                }
                // 0x004b6138
                charge(ctx, 3);
                link(ctx, 0x4B6138u);  // $ra first: the delay slot below depends on it
                lw(a0, s0, 0);
                call(ctx, gen::fn_sub_4C20B0_004c20b0);
                sw(zero, s0, 0);
            }
            // 0x004b6144
            charge(ctx, 9);
            sw(zero, s0, 4);
            v0 = 0x960000;
            lw(v0, v0, 396);  // 0x96018C
            a0 = 0x960000;
            a1 = s0;
            a0 = addiu(a0, -1132);  // &0x95FB94
            jalr(ctx, 0x4B6158u, v0.u());
            s0 = 0;
            backedge(ctx);
        }
        // 0x004b60a8
        charge(ctx, 2);
        v0 = s0;
    }
    // 0x004b6168 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4B7630 [rtDictSchemaInit] -- initialises a dictionary schema: its dictionary sList (4-byte entries, the schema's
//   memory hint | 0x40000) at +16 and no current dictionary; the schema, or 0
// 0x004B7630 sub_4B7630 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4B7630(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b7630
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x40000;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 4);
    s0 = a0;
    a1 = v1 | v0;
    a0 = 4;
    jal(ctx, 0x4B764Cu, gen::fn_sub_4C1D50_004c1d50);
    sw(v0, s0, 16);
    lw(v0, s0, 16);
    if (v0 != 0) {
        // 0x004b766c
        charge(ctx, 2);
        sw(zero, s0, 20);
        v0 = s0;
    } else {
        // 0x004b7664
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004b7674 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4B7690 [rtDictSchemaDestruct] -- destructs a dictionary schema: its dictionary sList destroyed (sub_4C20B0); 1
// 0x004B7690 sub_4B7690 -- 32 bytes; frame 0x10: ra sp+0x0
void sub_4B7690(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b7690
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    link(ctx, 0x4B7698u);  // $ra first: the delay slot below depends on it
    lw(a0, a0, 16);
    call(ctx, gen::fn_sub_4C20B0_004c20b0);
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}

// RwFsInit -- initialises the RtFS manager: the maximum file systems ($a0), no file systems, no default, no error
//   callback, the manager semaphore created (count 1, _sceCreateSema) and the initialised flag; 1
// 0x004BFBB0 RwFsInit -- 104 bytes; frame 0x10: ra sp+0x0
void RwFsInit(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004bfbb0
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x960000;
    sd(ra, sp, 0x0);
    v0 = 0x960000;
    sw(a0, v0, -236);  // 0x95FF14
    sw(zero, v1, -232);  // 0x95FF18
    v0 = 0x960000;
    v1 = 0x960000;
    sw(zero, v0, -240);  // 0x95FF10
    sw(zero, v1, -220);  // 0x95FF24
    v0 = 0x960000;
    v1 = 1;
    a0 = 0x960000;
    sw(v1, v0, -200);  // 0x95FF38
    a0 = addiu(a0, -208);  // &0x95FF30
    v0 = 0x960000;
    sw(zero, gp, -17460);  // 0x7CE8BC
    link(ctx, 0x4BFBF4u);  // $ra first: the delay slot below depends on it
    sw(v1, v0, -204);
    call(ctx, gen::fn__sceCreateSema_00503160);
    sw(v0, gp, -17456);  // 0x7CE8C0
    v1 = 0x960000;
    v0 = 1;
    sw(v0, v1, -228);  // 0x95FF1C
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// sub_4BFEA0 [rtfsFileOpenRecord] -- opens a file record of a file system: under the manager semaphore the first free
//   record (state 1, through the file system's record getter +20) marked opening (5); the async / sync mode words for
//   flag 0x10 or an always-async file system; the file system's open callback (+40) run and the record's state set (busy
//   2) or freed again on a failure; error 8 (no record) / 4 (no file system) through the error callback 0x95FF24; the
//   record, or 0
// 0x004BFEA0 sub_4BFEA0 -- 440 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4BFEA0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004bfea0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a1;
    sq(s4, sp, 0x40);
    s5 = t0;
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    s2 = a3;
    sq(s0, sp, 0x0);
    s1 = 0;
    if (s4 == 0) {
        // 0x004c0014
        charge(ctx, 4);
        v0 = 0x960000;
        lw(v0, v0, -220);  // 0x95FF24
        if (v0 != 0) {
            // 0x004c0024
            charge(ctx, 2);
            a0 = 4;
            jalr(ctx, 0x4C0024u, v0.u());
        }
        // 0x004c002c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004bfee0
        charge(ctx, 6);
        link(ctx, 0x4BFEE0u);  // $ra first: the delay slot below depends on it
        lw(a0, gp, -17456);  // 0x7CE8C0
        call(ctx, gen::fn__sceWaitSema_005031a0);
        lw(v0, s4, 4);
        at = slt(0, v0);
        s0 = 0;
        if (at != 0) {
            for (;;) {
                // 0x004bfef8
                charge(ctx, 8);
                lw(v0, s4, 20);
                a0 = s4;
                a1 = s0;
                jalr(ctx, 0x4BFF00u, v0.u());
                lw(a0, v0, 56);
                v1 = 1;
                if (a0 == v1) {
                    goto L_004bff18_3;
                }
                // 0x004bff28
                charge(ctx, 5);
                lw(v0, s4, 4);
                s0 = addiu(s0, 1);
                v0 = slt(s0, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004bff3c
            charge(ctx, 1);
        }
    L_004bff40:
        charge(ctx, 4);
        link(ctx, 0x4BFF40u);  // $ra first: the delay slot below depends on it
        lw(a0, gp, -17456);  // 0x7CE8C0
        call(ctx, gen::fn__sceSignalSema_00503180);
        if (s1 == 0) {
            // 0x004bffb0
            charge(ctx, 7);
            s0 = 8;
            jal(ctx, 0x4BFFB0u, gen::fn_sceLibgcc32GetErxEntries_1_004c0060);
            sw(s0, v0, 16);
            v0 = 0x960000;
            lw(v0, v0, -220);  // 0x95FF24
            if (v0 != 0) {
                // 0x004bffcc
                charge(ctx, 2);
                a0 = s0;
                jalr(ctx, 0x4BFFCCu, v0.u());
            }
            // 0x004bffd4
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004bff50
            charge(ctx, 3);
            v0 = s3 & 0x10;
            if (v0 == 0) {
                // 0x004bff5c
                charge(ctx, 3);
                lw(v0, s1, 48);
                if (v0 != 0) {
                    goto L_004bffdc;
                }
                goto L_004bff68;
            }
        L_004bffdc:
            charge(ctx, 5);
            v0 = 2;
            sw(v0, s1, 64);
            sw(s2, s1, 72);
            sw(s5, s1, 76);
            backedge(ctx);
        L_004bff68:
            charge(ctx, 3);
            lw(v0, s4, 16);
            if (v0 != 0) {
                // 0x004bfff0
                charge(ctx, 6);
                v0 = 2;
                s3 = s3 | 0x10;
                sw(v0, s1, 64);
                sw(s2, s1, 72);
                sw(s5, s1, 76);
                backedge(ctx);
            }
            // 0x004bff74
            charge(ctx, 9);
            lw(v0, s4, 40);
            a2 = s6;
            a3 = s3;
            a0 = s4;
            a1 = s1;
            jalr(ctx, 0x4BFF84u, v0.u());
            v1 = 1;
            if (v0 != v1) {
                // 0x004c0008
                charge(ctx, 3);
                sw(v1, s1, 56);
                s1 = 0;
                backedge(ctx);
            }
            // 0x004bff98
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x004bffa0
                charge(ctx, 2);
                v0 = 2;
                sw(v0, s1, 52);
            }
            // 0x004bffa8
            charge(ctx, 2);
            v0 = s1;
        }
    }
    // 0x004c0030 (the shared epilogue, written out on this path)
    charge(ctx, 10);
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
L_004bff18_3:
    charge(ctx, 4);
    v1 = 5;
    s1 = v0;
    sw(v1, v0, 56);
    goto L_004bff40;
}

// sub_4C00F0 [rtfsFindFileSystem] -- finds the file system of a path: when any is registered, the device prefix up to
//   each ':' compared (strncpy / strcmp slots) with the registered names (list 0x95FF10); else the default file system
//   (gp 0x7CE8BC); error 6 through the error callback when none; the file system, or 0
// 0x004C00F0 sub_4C00F0 -- 320 bytes; frame 0xE0: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C00F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c00f0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    v0 = 0x960000;
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, v0, -232);  // 0x95FF18
    s4 = a0;
    if (v0 != 0) {
        // 0x004c0140
        charge(ctx, 8);
        v0 = 0x960000;
        lw(v0, v0, 356);  // 0x960164
        jalr(ctx, 0x4C0148u, v0.u());
        s0 = v0;
        at = sltu(0, s0);
        s3 = 0;
        if (at != 0) {
            // 0x004c0160
            charge(ctx, 3);
            s5 = 0x960000;
            s1 = addiu(sp, 0x70);
            s5 = addiu(s5, 352);  // &0x960160
            for (;;) {
                // 0x004c016c
                charge(ctx, 5);
                v1 = addu(s4, s3);
                v0 = 58;
                lb(v1, v1, 0);
                if (v1 == v0) {
                    // 0x004c01a4
                    charge(ctx, 8);
                    a2 = addiu(s3, 1);
                    a0 = addiu(sp, 0x70);
                    a1 = s4;
                    jal(ctx, 0x4C01ACu, gen::fn_strncpy_00524828);
                    v0 = 0x960000;
                    lw(s2, v0, -240);  // 0x95FF10
                    sb(zero, s1, 1);
                    if (s2 != 0) {
                        // 0x004c01c4
                        charge(ctx, 1);
                        for (;;) {
                            // 0x004c01c8
                            charge(ctx, 6);
                            lw(a1, s2, 12);
                            lw(v0, s5, 0);
                            a0 = addiu(sp, 0x70);
                            jalr(ctx, 0x4C01D0u, v0.u());
                            if (v0 == 0) {
                                goto L_004c01e0_13;
                            }
                            // 0x004c01e8
                            charge(ctx, 3);
                            lw(s2, s2, 0);
                            if (s2 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004c01f4
                        charge(ctx, 1);
                    }
                    // 0x004c01f8
                    charge(ctx, 2);
                    s2 = 0;
                L_004c0200:
                    charge(ctx, 2);
                    if (s2 != 0) {
                        break;
                    }
                    backedge(ctx);
                    goto L_004c0180;
                }
            L_004c0180:
                charge(ctx, 4);
                s3 = addiu(s3, 1);
                v0 = sltu(s3, s0);
                s1 = addiu(s1, 1);
                if (v0 == 0) {
                    goto L_004c0190;
                }
                backedge(ctx);
            }
            // 0x004c0208
            charge(ctx, 1);
            v0 = s2;
        L_004c020c:
            charge(ctx, 1);
            ld(ra, sp, 0x60);
            // 0x004c0210 (the shared epilogue, written out on this path)
            charge(ctx, 8);
            lq(s5, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0xE0);
            return;
        }
    L_004c0190:
        charge(ctx, 3);
        lw(v0, gp, -17460);  // 0x7CE8BC
        if (v0 == 0) {
            backedge(ctx);
            goto L_004c0120;
        }
        // 0x004c019c
        charge(ctx, 2);
        ld(ra, sp, 0x60);
        // 0x004c0210 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0xE0);
        return;
    }
L_004c0120:
    charge(ctx, 4);
    v0 = 0x960000;
    lw(v0, v0, -220);  // 0x95FF24
    if (v0 != 0) {
        // 0x004c0130
        charge(ctx, 2);
        a0 = 6;
        jalr(ctx, 0x4C0130u, v0.u());
    }
    // 0x004c0138
    charge(ctx, 2);
    v0 = 0;
    goto L_004c020c;
L_004c01e0_13:
    charge(ctx, 2);
    goto L_004c0200;
}

// sub_4C06C0 [rtfsFileExistsByPath] -- tests whether a file exists: its file system found by the device prefix (as
//   sub_4C00F0) or the default, then that file system's exists callback (+76); its result, or 0
// 0x004C06C0 sub_4C06C0 -- 352 bytes; frame 0xE0: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C06C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c06c0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    v0 = 0x960000;
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, v0, -232);  // 0x95FF18
    s4 = a0;
    if (v0 != 0) {
        // 0x004c0730
        charge(ctx, 8);
        v0 = 0x960000;
        lw(v0, v0, 356);  // 0x960164
        jalr(ctx, 0x4C0738u, v0.u());
        s0 = v0;
        at = sltu(0, s0);
        s3 = 0;
        if (at != 0) {
            // 0x004c0750
            charge(ctx, 3);
            s5 = 0x960000;
            s1 = addiu(sp, 0x70);
            s5 = addiu(s5, 352);  // &0x960160
            for (;;) {
                // 0x004c075c
                charge(ctx, 5);
                v1 = addu(s4, s3);
                v0 = 58;
                lb(v1, v1, 0);
                if (v1 == v0) {
                    // 0x004c0794
                    charge(ctx, 8);
                    a2 = addiu(s3, 1);
                    a0 = addiu(sp, 0x70);
                    a1 = s4;
                    jal(ctx, 0x4C079Cu, gen::fn_strncpy_00524828);
                    v0 = 0x960000;
                    lw(s2, v0, -240);  // 0x95FF10
                    sb(zero, s1, 1);
                    if (s2 != 0) {
                        // 0x004c07b4
                        charge(ctx, 1);
                        for (;;) {
                            // 0x004c07b8
                            charge(ctx, 6);
                            lw(a1, s2, 12);
                            lw(v0, s5, 0);
                            a0 = addiu(sp, 0x70);
                            jalr(ctx, 0x4C07C0u, v0.u());
                            if (v0 == 0) {
                                goto L_004c07d0_17;
                            }
                            // 0x004c07d8
                            charge(ctx, 3);
                            lw(s2, s2, 0);
                            if (s2 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004c07e4
                        charge(ctx, 1);
                    }
                    // 0x004c07e8
                    charge(ctx, 2);
                    s2 = 0;
                L_004c07f0:
                    charge(ctx, 2);
                    if (s2 != 0) {
                        break;
                    }
                    backedge(ctx);
                    goto L_004c0770;
                }
            L_004c0770:
                charge(ctx, 4);
                s3 = addiu(s3, 1);
                v0 = sltu(s3, s0);
                s1 = addiu(s1, 1);
                if (v0 == 0) {
                    goto L_004c0780;
                }
                backedge(ctx);
            }
            // 0x004c07f8
            charge(ctx, 2);
            a0 = s2;
            backedge(ctx);
            goto L_004c070c;
        }
    L_004c0780:
        charge(ctx, 3);
        lw(a0, gp, -17460);  // 0x7CE8BC
        if (a0 == 0) {
            backedge(ctx);
            goto L_004c06f0;
        }
        // 0x004c078c
        charge(ctx, 2);
        backedge(ctx);
        goto L_004c070c;
    }
L_004c06f0:
    charge(ctx, 4);
    v0 = 0x960000;
    lw(v0, v0, -220);  // 0x95FF24
    if (v0 != 0) {
        // 0x004c0700
        charge(ctx, 2);
        a0 = 6;
        jalr(ctx, 0x4C0700u, v0.u());
    }
    // 0x004c0708
    charge(ctx, 1);
    a0 = 0;
L_004c070c:
    charge(ctx, 2);
    if (a0 != 0) {
        // 0x004c071c
        charge(ctx, 3);
        lw(v0, a0, 76);
        a1 = s4;
        jalr(ctx, 0x4C0720u, v0.u());
    } else {
        // 0x004c0714
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004c0728
    charge(ctx, 2);
    ld(ra, sp, 0x60);
    // 0x004c0800
    charge(ctx, 8);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xE0);
    return;
L_004c07d0_17:
    charge(ctx, 2);
    goto L_004c07f0;
}

// j_malloc -- a tail call into newlib malloc (the default RW allocation slot)
// 0x004C4420 j_malloc -- 8 bytes; leaf frame (no stack)
void j_malloc(EEContext& ctx) {
    using namespace hg;
    // 0x004c4420
    enter(ctx, 2);  // entry check point + this block's cycles
    gen::fn_malloc_00520728(ctx);  // tail call
}

// j_realloc -- a tail call into newlib realloc (the default RW reallocation slot)
// 0x004C4430 j_realloc -- 8 bytes; leaf frame (no stack)
void j_realloc(EEContext& ctx) {
    using namespace hg;
    // 0x004c4430
    enter(ctx, 2);  // entry check point + this block's cycles
    gen::fn_realloc_00522f98(ctx);  // tail call
}

// j_calloc -- a tail call into newlib calloc (the default RW zeroed-allocation slot)
// 0x004C4440 j_calloc -- 8 bytes; leaf frame (no stack)
void j_calloc(EEContext& ctx) {
    using namespace hg;
    // 0x004c4440
    enter(ctx, 2);  // entry check point + this block's cycles
    gen::fn_calloc_0051e150(ctx);  // tail call
}

// sub_4C4450 [rwMemoryOpen] -- opens RW's memory module: the free-list registry (a 36-byte free list, sub_4C3970) with
//   an empty list head, then the four memory function slots 0x960178..0x960184 set from the caller's table $a0 or the
//   newlib defaults (j_malloc, cfree, j_realloc, j_calloc); 1, or 0
// 0x004C4450 sub_4C4450 -- 284 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C4450(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x004c4450
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 16;
    sd(ra, sp, 0x10);
    t0 = 0x960000;
    sq(s0, sp, 0x0);
    v1 = addiu(gp, -17416);  // &0x7CE8E8
    s0 = a0;
    v0 = 1;
    sw(v0, gp, -17424);  // 0x7CE8E0
    a0 = 36;
    sw(v1, gp, -17416);  // 0x7CE8E8
    a2 = a1;
    sw(v1, gp, -17412);  // 0x7CE8EC
    a3 = 0;
    t0 = addiu(t0, -128);  // &0x95FF80
    t1 = 0x40000;
    jal(ctx, 0x4C448Cu, gen::fn_sub_4C3970_004c3970);
    sw(v0, gp, -17420);  // 0x7CE8E4
    if (v0 == 0) {
        // 0x004c4504
        charge(ctx, 3);
        sw(zero, gp, -17424);  // 0x7CE8E0
        a0 = 0;
        backedge(ctx);
    } else {
        // 0x004c449c
        charge(ctx, 8);
        lw(v1, v0, 28);
        a0 = 1;
        lw(v0, v0, 32);
        sw(v1, v0, 0);
        lw(v0, gp, -17420);  // 0x7CE8E4
        lw(v1, v0, 32);
        lw(v0, v0, 28);
        sw(v1, v0, 4);
    }
    // 0x004c44bc
    charge(ctx, 2);
    if (a0 == 0) {
        // 0x004c4510
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004c44c4
        charge(ctx, 2);
        if (s0 == 0) {
            // 0x004c4518
            charge(ctx, 17);
            v1 = 0x4C0000;
            a0 = 0x520000;
            v1 = addiu(v1, 17440);  // &j_malloc
            v0 = 0x960000;
            sw(v1, v0, 376);  // 0x960178
            a0 = addiu(a0, 1864);  // &cfree
            v0 = 0x960000;
            v1 = 0x4C0000;
            sw(a0, v0, 380);  // 0x96017C
            v1 = addiu(v1, 17456);  // &j_realloc
            v0 = 0x960000;
            sw(v1, v0, 384);  // 0x960180
            v1 = 0x4C0000;
            v0 = 0x960000;
            v1 = addiu(v1, 17472);  // &j_calloc
            sw(v1, v0, 388);  // 0x960184
            backedge(ctx);
        } else {
            // 0x004c44cc
            charge(ctx, 12);
            lwc1(f3, s0, 0);
            a1 = 0x960000;
            lwc1(f2, s0, 4);
            a0 = 0x960000;
            lwc1(f1, s0, 8);
            v1 = 0x960000;
            lwc1(f0, s0, 12);
            v0 = 0x960000;
            swc1(f3, a1, 376);  // 0x960178
            swc1(f2, a0, 380);  // 0x96017C
            swc1(f1, v1, 384);  // 0x960180
            swc1(f0, v0, 388);  // 0x960184
        }
        // 0x004c44fc
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x004c455c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4C4570 [rwMemoryClose] -- closes RW's memory module: every registered free list unlinked and destroyed
//   (sub_4C3B70), then the registry's own free list; the registry cleared
// 0x004C4570 sub_4C4570 -- 124 bytes; frame 0x10: ra sp+0x0
void sub_4C4570(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c4570
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = addiu(gp, -17416);  // &0x7CE8E8
    sd(ra, sp, 0x0);
    lw(a1, gp, -17416);  // 0x7CE8E8
    if (a1 != v0) {
        for (;;) {
            // 0x004c4588
            charge(ctx, 12);
            lw(v1, a1, 0);
            a0 = addiu(a1, -28);
            lw(v0, a1, 4);
            sw(v1, v0, 0);
            lw(v1, a1, 4);
            lw(v0, a1, 0);
            link(ctx, 0x4C45A0u);  // $ra first: the delay slot below depends on it
            sw(v1, v0, 4);
            call(ctx, gen::fn_sub_4C3B70_004c3b70);
            lw(a1, gp, -17416);  // 0x7CE8E8
            v0 = addiu(gp, -17416);  // &0x7CE8E8
            if (a1 == v0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004c45b8
    charge(ctx, 13);
    lw(a0, gp, -17420);  // 0x7CE8E4
    lw(v1, a0, 28);
    lw(v0, a0, 32);
    sw(v1, v0, 0);
    lw(v1, a0, 32);
    lw(v0, a0, 28);
    link(ctx, 0x4C45D0u);  // $ra first: the delay slot below depends on it
    sw(v1, v0, 4);
    call(ctx, gen::fn_sub_4C3B70_004c3b70);
    sw(zero, gp, -17420);  // 0x7CE8E4
    sw(zero, gp, -17424);  // 0x7CE8E0
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// sub_4C6640 [rwV3dTransformPointsDefault] -- the default point transform: $a2 points from $a1 times the matrix $a3
//   (rotation and translation) into $a0 (FPU multiply-accumulate); $a0
// 0x004C6640 sub_4C6640 -- 184 bytes; leaf frame (no stack)
void sub_4C6640(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14}, f15{ctx, 15}, f16{ctx, 16}, f17{ctx, 17};
    // 0x004c6640
    enter(ctx, 3);  // entry check point + this block's cycles
    a2 = addiu(a2, -1);
    v0 = a0;
    if (i64(a2) >= 0) {
        // 0x004c664c
        charge(ctx, 13);
        lwc1(f17, a3, 0);
        lwc1(f16, a3, 4);
        lwc1(f15, a3, 8);
        lwc1(f13, a3, 16);
        lwc1(f11, a3, 20);
        lwc1(f9, a3, 24);
        lwc1(f7, a3, 32);
        lwc1(f6, a3, 36);
        lwc1(f5, a3, 40);
        lwc1(f3, a3, 48);
        lwc1(f2, a3, 52);
        lwc1(f1, a3, 56);
        mtc1(zero, f12);
        for (;;) {
            // 0x004c6680
            charge(ctx, 27);
            lwc1(f0, a1, 0);
            a2 = addiu(a2, -1);
            lwc1(f8, a1, 4);
            lwc1(f4, a1, 8);
            mul_s(f10, f0, f16);
            a1 = addiu(a1, 12);
            mul_s(f14, f0, f15);
            mula_s(f0, f17);
            madd_s(f0, f8, f13);
            adda_s(f12, f10);
            madd_s(f10, f8, f11);
            adda_s(f12, f14);
            madd_s(f8, f8, f9);
            adda_s(f12, f0);
            madd_s(f0, f4, f7);
            add_s(f0, f0, f3);
            adda_s(f12, f10);
            swc1(f0, a0, 0);
            madd_s(f0, f4, f6);
            add_s(f0, f0, f2);
            adda_s(f12, f8);
            madd_s(f4, f4, f5);
            swc1(f0, a0, 4);
            add_s(f0, f4, f1);
            swc1(f0, a0, 8);
            a0 = addiu(a0, 12);
            if (i64(a2) < 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004c66ec
        charge(ctx, 1);
    }
    // 0x004c66f0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// sub_4C6700 [rwV3dTransformPointDefault] -- the default single-point transform: the point $a1 times the matrix $a2
//   (rotation and translation) into $a0; $a0
// 0x004C6700 sub_4C6700 -- 152 bytes; leaf frame (no stack)
void sub_4C6700(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10};
    // 0x004c6700
    enter(ctx, 38);  // entry check point + this block's cycles
    lwc1(f5, a1, 0);
    v0 = a0;
    lwc1(f2, a2, 4);
    lwc1(f1, a2, 8);
    lwc1(f4, a2, 0);
    lwc1(f6, a1, 4);
    lwc1(f0, a2, 16);
    mtc1(zero, f8);
    mul_s(f2, f5, f2);
    mula_s(f5, f4);
    mul_s(f10, f5, f1);
    madd_s(f9, f6, f0);
    adda_s(f8, f2);
    lwc1(f5, a2, 20);
    lwc1(f4, a2, 24);
    lwc1(f3, a1, 8);
    lwc1(f2, a2, 32);
    lwc1(f1, a2, 36);
    lwc1(f0, a2, 40);
    madd_s(f7, f6, f5);
    adda_s(f8, f10);
    madd_s(f6, f6, f4);
    adda_s(f8, f9);
    madd_s(f5, f3, f2);
    adda_s(f8, f7);
    madd_s(f4, f3, f1);
    adda_s(f8, f6);
    lwc1(f2, a2, 48);
    madd_s(f3, f3, f0);
    lwc1(f1, a2, 52);
    lwc1(f0, a2, 56);
    add_s(f2, f5, f2);
    add_s(f1, f4, f1);
    swc1(f2, a0, 0);
    add_s(f0, f3, f0);
    swc1(f1, a0, 4);
    swc1(f0, a0, 8);
}

// sub_4C67A0 [rwV3dTransformVectorsDefault] -- the default vector transform: $a2 vectors from $a1 times the matrix
//   $a3's rotation (no translation) into $a0; $a0
// 0x004C67A0 sub_4C67A0 -- 160 bytes; leaf frame (no stack)
void sub_4C67A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x004c67a0
    enter(ctx, 3);  // entry check point + this block's cycles
    a2 = addiu(a2, -1);
    v0 = a0;
    if (i64(a2) >= 0) {
        // 0x004c67ac
        charge(ctx, 10);
        lwc1(f14, a3, 0);
        lwc1(f13, a3, 4);
        lwc1(f12, a3, 8);
        lwc1(f10, a3, 16);
        lwc1(f8, a3, 20);
        lwc1(f6, a3, 24);
        lwc1(f3, a3, 32);
        lwc1(f2, a3, 36);
        lwc1(f1, a3, 40);
        mtc1(zero, f9);
        for (;;) {
            // 0x004c67d4
            charge(ctx, 24);
            lwc1(f0, a1, 0);
            a2 = addiu(a2, -1);
            lwc1(f5, a1, 4);
            lwc1(f4, a1, 8);
            mul_s(f7, f0, f13);
            a1 = addiu(a1, 12);
            mul_s(f11, f0, f12);
            mula_s(f0, f14);
            madd_s(f0, f5, f10);
            adda_s(f9, f7);
            madd_s(f7, f5, f8);
            adda_s(f9, f11);
            madd_s(f5, f5, f6);
            adda_s(f9, f0);
            madd_s(f0, f4, f3);
            swc1(f0, a0, 0);
            adda_s(f9, f7);
            madd_s(f0, f4, f2);
            swc1(f0, a0, 4);
            adda_s(f9, f5);
            madd_s(f0, f4, f1);
            swc1(f0, a0, 8);
            a0 = addiu(a0, 12);
            if (i64(a2) < 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004c6834
        charge(ctx, 1);
    }
    // 0x004c6838 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// sub_4C6840 [rwV3dTransformVectorDefault] -- the default single-vector transform: the vector $a1 times the matrix
//   $a2's rotation into $a0; $a0
// 0x004C6840 sub_4C6840 -- 128 bytes; leaf frame (no stack)
void sub_4C6840(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9};
    // 0x004c6840
    enter(ctx, 32);  // entry check point + this block's cycles
    lwc1(f5, a1, 0);
    v0 = a0;
    lwc1(f2, a2, 4);
    lwc1(f1, a2, 8);
    lwc1(f4, a2, 0);
    lwc1(f8, a1, 4);
    lwc1(f0, a2, 16);
    mtc1(zero, f6);
    mul_s(f2, f5, f2);
    mula_s(f5, f4);
    mul_s(f9, f5, f1);
    madd_s(f7, f8, f0);
    adda_s(f6, f2);
    lwc1(f5, a2, 20);
    lwc1(f4, a2, 24);
    lwc1(f3, a1, 8);
    lwc1(f2, a2, 32);
    lwc1(f1, a2, 36);
    lwc1(f0, a2, 40);
    madd_s(f5, f8, f5);
    adda_s(f6, f9);
    madd_s(f4, f8, f4);
    adda_s(f6, f7);
    madd_s(f2, f3, f2);
    adda_s(f6, f5);
    madd_s(f1, f3, f1);
    swc1(f2, a0, 0);
    adda_s(f6, f4);
    madd_s(f0, f3, f0);
    swc1(f1, a0, 4);
    swc1(f0, a0, 8);
}

// sub_4C68C0 [rwV3dSetTransformFns] -- sets the vector module's four transform functions (engine + gp 0x7CE910,
//   +8..+20), each argument or, when 0, its default (sub_4C6700 / sub_4C6640 / sub_4C6840 / sub_4C67A0); 1
// 0x004C68C0 sub_4C68C0 -- 164 bytes; leaf frame (no stack)
void sub_4C68C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x004c68c0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 == 0) {
        // 0x004c692c
        charge(ctx, 3);
        a0 = 0x4C0000;
        a0 = addiu(a0, 26368);  // &sub_4C6700
        backedge(ctx);
    }
    // 0x004c68c8
    charge(ctx, 6);
    lw(v1, gp, -17376);  // 0x7CE910
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070
    v0 = addu(v0, v1);
    sw(a0, v0, 8);
    if (a1 == 0) {
        // 0x004c6938
        charge(ctx, 3);
        a1 = 0x4C0000;
        a1 = addiu(a1, 26176);  // &sub_4C6640
        backedge(ctx);
    }
    // 0x004c68e0
    charge(ctx, 6);
    lw(v1, gp, -17376);  // 0x7CE910
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070
    v0 = addu(v0, v1);
    sw(a1, v0, 12);
    if (a2 == 0) {
        // 0x004c6944
        charge(ctx, 3);
        a2 = 0x4C0000;
        a2 = addiu(a2, 26688);  // &sub_4C6840
        backedge(ctx);
    }
    // 0x004c68f8
    charge(ctx, 6);
    lw(v1, gp, -17376);  // 0x7CE910
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070
    v0 = addu(v0, v1);
    sw(a2, v0, 16);
    if (a3 == 0) {
        // 0x004c6950
        charge(ctx, 3);
        a3 = 0x4C0000;
        a3 = addiu(a3, 26528);  // &sub_4C67A0
        backedge(ctx);
    }
    // 0x004c6910
    charge(ctx, 7);
    lw(a0, gp, -17376);  // 0x7CE910
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070
    v0 = 1;
    v1 = addu(v1, a0);
    sw(a3, v1, 20);
    // 0x004c695c
    charge(ctx, 2);
}

// sub_4C6D00 [rwV3dModuleOpen] -- the vector module's open: its engine offset (gp 0x7CE910) stored, the four default
//   transform functions installed, the open count up; $a0
// 0x004C6D00 sub_4C6D00 -- 84 bytes; leaf frame (no stack)
void sub_4C6D00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x004c6d00
    enter(ctx, 21);  // entry check point + this block's cycles
    v1 = 0x960000;
    a3 = 0x4C0000;
    sw(a1, gp, -17376);  // 0x7CE910
    v1 = addiu(v1, 112);  // &0x960070
    v0 = a0;
    a2 = 0x4C0000;
    a1 = addu(v1, a1);
    a3 = addiu(a3, 26368);  // &sub_4C6700
    a0 = 0x4C0000;
    v1 = 0x4C0000;
    a2 = addiu(a2, 26176);  // &sub_4C6640
    sw(a3, a1, 8);
    a0 = addiu(a0, 26688);  // &sub_4C6840
    sw(a2, a1, 12);
    v1 = addiu(v1, 26528);  // &sub_4C67A0
    sw(a0, a1, 16);
    sw(v1, a1, 20);
    lw(v1, gp, -17372);  // 0x7CE914
    v1 = addiu(v1, 1);
    sw(v1, gp, -17372);  // 0x7CE914
}

// sub_4C7020 [rwModule1042Open] -- the engine module 1042's open: its engine offset (gp 0x7CE918) stored, a free list
//   of 33-byte entries (sub_4C3B60, in place at 0x960010, block size and preallocation from 0x7CDD58 / 0x7CDD5C) kept at
//   engine + offset, the open count (gp 0x7CE91C) up; $a0, or 0
// 0x004C7020 sub_4C7020 -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C7020(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c7020
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    t0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = 0x40000;
    sq(s0, sp, 0x0);
    a2 = 4;
    sw(a1, gp, -17368);  // 0x7CE918
    s0 = a0;
    lw(a1, gp, -20376);  // 0x7CDD58
    a0 = 33;
    lw(a3, gp, -20372);  // 0x7CDD5C
    t0 = addiu(t0, 16);  // &0x960010
    t1 = v0 | 0x412;
    jal(ctx, 0x4C7050u, gen::fn_sub_4C3B60_004c3b60);
    lw(a0, gp, -17368);  // 0x7CE918
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070
    v1 = addu(v1, a0);
    sw(v0, v1, 0);
    lw(v0, v1, 0);
    if (v0 != 0) {
        // 0x004c7080
        charge(ctx, 4);
        lw(v1, gp, -17364);  // 0x7CE91C
        v0 = s0;
        v1 = addiu(v1, 1);
        sw(v1, gp, -17364);  // 0x7CE91C
    } else {
        // 0x004c7078
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004c7090 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4C70A0 [rwModule1042Close] -- the engine module 1042's close: its free list destroyed (sub_4C3C30) when made, the
//   open count down; $a0
// 0x004C70A0 sub_4C70A0 -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4C70A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c70a0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 0x960000;
    sd(ra, sp, 0x10);
    v0 = addiu(v0, 112);  // &0x960070
    sq(s0, sp, 0x0);
    lw(v1, gp, -17368);  // 0x7CE918
    s0 = a0;
    v0 = addu(v0, v1);
    lw(a0, v0, 0);
    if (a0 != 0) {
        // 0x004c70cc
        charge(ctx, 2);
        jal(ctx, 0x4C70CCu, gen::fn_sub_4C3C30_004c3c30);
    }
    // 0x004c70d4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    lw(v1, gp, -17364);  // 0x7CE91C
    v0 = s0;
    v1 = addiu(v1, -1);
    sw(v1, gp, -17364);  // 0x7CE91C
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4C71C0 [rwStrUpr] -- upper-cases a string in place (a..z), then returns it through the empty helper sub_4C7208
// 0x004C71C0 sub_4C71C0 -- 72 bytes; leaf frame (no stack)
void sub_4C71C0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004c71c0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 == 0) {
        gen::fn_sub_4C7208_004c7208(ctx);  // tail call
        return;
    }
    // 0x004c71c8
    charge(ctx, 3);
    lb(v0, a0, 0);
    a1 = a0;
    if (v0 == 0) {
        gen::fn_sub_4C7208_004c7208(ctx);  // tail call
        return;
    }
    for (;;) {
        // 0x004c71d4
        charge(ctx, 4);
        lb(v1, a1, 0);
        v0 = slti(v1, 97);
        if (v0 == 0) {
            // 0x004c71e4
            charge(ctx, 3);
            at = slti(v1, 123);
            if (at != 0) {
                // 0x004c71f0
                charge(ctx, 2);
                v0 = addiu(v1, -32);
                sb(v0, a1, 0);
            }
        }
        // 0x004c71f8
        charge(ctx, 4);
        a1 = addiu(a1, 1);
        lb(v0, a1, 0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004c7208
    gen::fn_sub_4C7208_004c7208(ctx);  // tail call
}

// sub_4C7208 [rwStrReturn] -- returns its argument (an empty helper)
// 0x004C7208 sub_4C7208 -- 8 bytes; leaf frame (no stack)
void sub_4C7208(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004c7208
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}

// sub_4C7210 [rwStrLwr] -- lower-cases a string in place (A..Z), then returns it through the empty helper sub_4C7258
// 0x004C7210 sub_4C7210 -- 72 bytes; leaf frame (no stack)
void sub_4C7210(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004c7210
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a0 == 0) {
        gen::fn_sub_4C7258_004c7258(ctx);  // tail call
        return;
    }
    // 0x004c7218
    charge(ctx, 3);
    lb(v0, a0, 0);
    a1 = a0;
    if (v0 == 0) {
        gen::fn_sub_4C7258_004c7258(ctx);  // tail call
        return;
    }
    for (;;) {
        // 0x004c7224
        charge(ctx, 4);
        lb(v1, a1, 0);
        v0 = slti(v1, 65);
        if (v0 == 0) {
            // 0x004c7234
            charge(ctx, 3);
            at = slti(v1, 91);
            if (at != 0) {
                // 0x004c7240
                charge(ctx, 2);
                v0 = addiu(v1, 32);
                sb(v0, a1, 0);
            }
        }
        // 0x004c7248
        charge(ctx, 4);
        a1 = addiu(a1, 1);
        lb(v0, a1, 0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004c7258
    gen::fn_sub_4C7258_004c7258(ctx);  // tail call
}

// sub_4C7258 [rwStrReturn2] -- returns its argument (an empty helper)
// 0x004C7258 sub_4C7258 -- 8 bytes; leaf frame (no stack)
void sub_4C7258(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004c7258
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = a0;
}

// sub_4C7260 [rwStrChr] -- finds the first $a1 character in a string: a pointer to it, or 0 at the terminator
// 0x004C7260 sub_4C7260 -- 60 bytes; leaf frame (no stack)
void sub_4C7260(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004c7260
    enter(ctx, 3);  // entry check point + this block's cycles
    a1 = dsll32(a1, 24);
    v0 = 0;
    a1 = dsra32(a1, 24);
    for (;;) {
        // 0x004c726c
        charge(ctx, 4);
        lb(v1, a0, 0);
        if (v1 == a1) {
            goto L_004c727c_2;
        }
        // 0x004c7284
        charge(ctx, 2);
        a0 = addiu(a0, 1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004c728c
    charge(ctx, 1);
    // 0x004c7290 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = dsll32(v0, 0);
    v0 = dsra32(v0, 0);
    return;
L_004c727c_2:
    charge(ctx, 2);
    v0 = a0;
    // 0x004c7290 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = dsll32(v0, 0);
    v0 = dsra32(v0, 0);
}

// sub_4C72A0 [rwStrRChr] -- finds the last $a1 character in a string: a pointer to it, or 0
// 0x004C72A0 sub_4C72A0 -- 56 bytes; leaf frame (no stack)
void sub_4C72A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x004c72a0
    enter(ctx, 3);  // entry check point + this block's cycles
    a1 = dsll32(a1, 24);
    v0 = 0;
    a1 = dsra32(a1, 24);
    for (;;) {
        // 0x004c72ac
        charge(ctx, 3);
        lb(v1, a0, 0);
        if (v1 == a1) {
            // 0x004c72b8
            charge(ctx, 2);
            v0 = a0;
        }
        // 0x004c72c0
        charge(ctx, 4);
        a0 = addiu(a0, 1);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004c72d0
    charge(ctx, 3);
    v0 = dsll32(v0, 0);
    v0 = dsra32(v0, 0);
}

// sub_4C7400 [rwEngineNoOp] -- an empty engine hook (returns at once)
// 0x004C7400 sub_4C7400 -- 8 bytes; leaf frame (no stack)
void sub_4C7400(EEContext& ctx) {
    using namespace hg;
    // 0x004c7400
    enter(ctx, 2);  // entry check point + this block's cycles
}

// sub_4C7410 [rwStringStreamGetSize] -- the stream size of a string chunk's body: (strlen(s) + 4) & ~3, an empty string
//   ("" at 0x7BCBE8) for 0
// 0x004C7410 sub_4C7410 -- 68 bytes; frame 0x10: ra sp+0x0
void sub_4C7410(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c7410
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    if (a0 == 0) {
        // 0x004c743c
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, -13336);  // &0x7BCBE8
        backedge(ctx);
    }
    // 0x004c741c
    charge(ctx, 8);
    v0 = 0x960000;
    lw(v0, v0, 356);  // 0x960164
    jalr(ctx, 0x4C7424u, v0.u());
    v1 = addiu(v0, 4);
    v0 = si(-4);
    v0 = v1 & v0;
    // 0x004c7448
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// sub_4C7520 [rwStringStreamReadAscii] -- reads a string chunk's body of $a2 bytes into $a0 (RwMalloc'd when 0; error
//   0x80000013) in 64-byte pieces; the string, or 0
// 0x004C7520 sub_4C7520 -- 412 bytes; frame 0xE0: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C7520(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c7520
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    if (s4 == 0) {
        // 0x004c7640
        charge(ctx, 9);
        v0 = 0x30000;
        a1 = v0 | 0x2;
        v0 = 0x960000;
        lw(v0, v0, 376);  // 0x960178
        a0 = s2;
        jalr(ctx, 0x4C7650u, v0.u());
        s4 = v0;
        if (s4 != 0) {
            backedge(ctx);
            goto L_004c754c;
        }
        // 0x004c7664
        charge(ctx, 11);
        v0 = 1;
        a1 = s2;
        sw(v0, sp, 0xD8);
        v0 = lui(0x8000);
        a0 = v0 | 0x13;
        jal(ctx, 0x4C7674u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0xDC);
        a0 = addiu(sp, 0xD8);
        jal(ctx, 0x4C7680u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
        // 0x004c769c (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0xE0);
        return;
    }
L_004c754c:
    charge(ctx, 2);
    s1 = s4;
    if (s2 != 0) {
        for (;;) {
            // 0x004c7554
            charge(ctx, 3);
            at = sltiu(s2, 65);
            if (at == 0) {
                // 0x004c7690
                charge(ctx, 2);
                s0 = 64;
                backedge(ctx);
            } else {
                // 0x004c7560
                charge(ctx, 2);
                s0 = s2;
            }
            // 0x004c7568
            charge(ctx, 6);
            a0 = s3;
            a1 = addiu(sp, 0x60);
            a2 = s0;
            jal(ctx, 0x4C7570u, gen::fn_sub_4C5250_004c5250);
            if (s0 != v0) {
                break;
            }
            // 0x004c7580
            charge(ctx, 4);
            at = sltu(0, s0);
            s2 = subu(s2, s0);
            a3 = 0;
            if (at != 0) {
                // 0x004c7590
                charge(ctx, 3);
                at = sltiu(s0, 9);
                a1 = addiu(s0, -8);
                if (at == 0) {
                    // 0x004c759c
                    charge(ctx, 1);
                    a2 = addiu(sp, 0x60);
                    for (;;) {
                        // 0x004c75a0
                        charge(ctx, 21);
                        lb(v1, a2, 0);
                        a0 = addu(s1, a3);
                        a3 = addiu(a3, 8);
                        v0 = sltu(a3, a1);
                        sb(v1, a0, 0);
                        lb(v1, a2, 1);
                        sb(v1, a0, 1);
                        lb(v1, a2, 2);
                        sb(v1, a0, 2);
                        lb(v1, a2, 3);
                        sb(v1, a0, 3);
                        lb(v1, a2, 4);
                        sb(v1, a0, 4);
                        lb(v1, a2, 5);
                        sb(v1, a0, 5);
                        lb(v1, a2, 6);
                        sb(v1, a0, 6);
                        lb(v1, a2, 7);
                        sb(v1, a0, 7);
                        a2 = addiu(a2, 8);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004c75f4
                    charge(ctx, 1);
                }
                // 0x004c75f8
                charge(ctx, 3);
                at = sltu(a3, s0);
                if (at != 0) {
                    // 0x004c7604
                    charge(ctx, 3);
                    v0 = addu(a3, sp);
                    a1 = addiu(v0, 96);
                    for (;;) {
                        // 0x004c7610
                        charge(ctx, 7);
                        lb(a0, a1, 0);
                        v1 = addu(s1, a3);
                        a3 = addiu(a3, 1);
                        v0 = sltu(a3, s0);
                        sb(a0, v1, 0);
                        a1 = addiu(a1, 1);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004c762c
                    charge(ctx, 1);
                }
            }
            // 0x004c7630
            charge(ctx, 2);
            s1 = addu(s1, s0);
            if (s2 == 0) {
                goto L_004c7638;
            }
            backedge(ctx);
        }
        // 0x004c7698
        charge(ctx, 1);
        v0 = 0;
        // 0x004c769c (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(ra, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0xE0);
        return;
    }
L_004c7638:
    charge(ctx, 2);
    v0 = s4;
    // 0x004c769c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xE0);
}

// sub_4C78A0 [rwStringStreamRead] -- reads the next string from a stream: the chunk headers walked (sub_4C1450;
//   versions 0x35000..0x37002 else error 0x80000004), other chunks skipped (sub_4C5620), a string (2, sub_4C7520) or
//   unicode string (19, sub_4C76C0) read into $a0; the string, or 0
// 0x004C78A0 sub_4C78A0 -- 312 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4C78A0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c78a0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    t0 = 0;
    sd(ra, sp, 0x20);
    a2 = addiu(sp, 0x48);
    sq(s1, sp, 0x10);
    a3 = addiu(sp, 0x44);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = s0;
    a1 = addiu(sp, 0x4C);
    jal(ctx, 0x4C78C8u, gen::fn_sub_4C1450_004c1450);
    if (v0 != 0) {
        for (;;) {
            // 0x004c78d8
            charge(ctx, 6);
            lw(v1, sp, 0x44);
            v0 = 0x30000;
            v0 = v0 | 0x5000;
            v0 = sltu(v1, v0);
            a0 = 0;
            if (v0 == 0) {
                // 0x004c78f0
                charge(ctx, 5);
                at = 0x30000;
                at = at | 0x7003;
                at = sltu(v1, at);
                if (at != 0) {
                    // 0x004c7904
                    charge(ctx, 1);
                    a0 = 1;
                }
            }
            // 0x004c7908
            charge(ctx, 2);
            if (a0 == 0) {
                goto L_004c7968;
            }
            // 0x004c7910
            charge(ctx, 4);
            lw(v1, sp, 0x4C);
            v0 = 2;
            if (v1 == v0) {
                goto L_004c7990;
            }
            // 0x004c7920
            charge(ctx, 3);
            v0 = 19;
            if (v1 == v0) {
                goto L_004c79a8;
            }
            // 0x004c792c
            charge(ctx, 5);
            lw(a1, sp, 0x48);
            a0 = s0;
            jal(ctx, 0x4C7930u, gen::fn_sub_4C5620_004c5620);
            if (v0 == 0) {
                goto L_004c79c0;
            }
            // 0x004c7940
            charge(ctx, 8);
            a0 = s0;
            a1 = addiu(sp, 0x4C);
            a2 = addiu(sp, 0x48);
            a3 = addiu(sp, 0x44);
            t0 = 0;
            jal(ctx, 0x4C7950u, gen::fn_sub_4C1450_004c1450);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004c7960
    charge(ctx, 2);
    v0 = 0;
L_004c79c4:
    charge(ctx, 1);
    ld(ra, sp, 0x20);
    // 0x004c79c8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_004c7968:
    charge(ctx, 10);
    v1 = 1;
    v0 = lui(0x8000);
    sw(v1, sp, 0x38);
    a0 = v0 | 0x4;
    jal(ctx, 0x4C7974u, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0x3C);
    a0 = addiu(sp, 0x38);
    jal(ctx, 0x4C7980u, gen::fn_sub_4C1C50_004c1c50);
    v0 = 0;
    goto L_004c79c4;
L_004c7990:
    charge(ctx, 6);
    lw(a2, sp, 0x48);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x4C7998u, gen::fn_sub_4C7520_004c7520);
    ld(ra, sp, 0x20);
    // 0x004c79c8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
    return;
L_004c79a8:
    charge(ctx, 6);
    lw(a2, sp, 0x48);
    a0 = s1;
    a1 = s0;
    jal(ctx, 0x4C79B0u, gen::fn_sub_4C76C0_004c76c0);
    goto L_004c79c4;
L_004c79c0:
    charge(ctx, 1);
    v0 = 0;
    goto L_004c79c4;
}

// sub_4C79E0 [rwPathIsAbsolute] -- whether a path is absolute: it starts with '\' or with a letter (ctype table
//   0x7BE9C8) and ':'; 1 / 0
// 0x004C79E0 sub_4C79E0 -- 100 bytes; leaf frame (no stack)
void sub_4C79E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x004c79e0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
    if (a0 != 0) {
        // 0x004c79e8
        charge(ctx, 4);
        lb(a1, a0, 0);
        v1 = 92;
        a2 = 1;
        if (a1 != v1) {
            // 0x004c79f8
            charge(ctx, 8);
            v1 = 0x7C0000;
            v1 = addiu(v1, -5688);  // &0x7BE9C8
            v1 = addu(v1, a1);
            lb(v1, v1, 0);
            v1 = v1 & 0x3;
            v1 = sltu(0, v1);
            if (v1 != 0) {
                // 0x004c7a18
                charge(ctx, 3);
                lb(v1, a0, 1);
                v1 = v1 ^ 0x3A;
                v1 = sltiu(v1, 1);
            }
            // 0x004c7a24
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x004c7a2c
                charge(ctx, 1);
                a2 = 0;
            }
        }
        // 0x004c7a30
        charge(ctx, 2);
        if (a2 != 0) {
            // 0x004c7a38
            charge(ctx, 1);
            v0 = 1;
        }
    }
    // 0x004c7a3c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// sub_4C7B60 [RwCameraRegisterPluginStream] -- registers the stream callbacks of a camera plugin: in the camera plugin
//   registry (0x77E5E0, through the shared registry tail at 0x4C5960) the entry with id $a0 gets its read / write /
//   get-size callbacks ($a1..$a3); its offset, or -1
// 0x004C7B60 sub_4C7B60 -- 116 bytes, 2 chunks; leaf frame (no stack)
void sub_4C7B60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x004c7b60
    enter(ctx, 9);  // entry check point + this block's cycles
    v1 = a1;
    v0 = a2;
    a1 = a0;
    t0 = a3;
    a0 = 0x780000;
    a2 = v1;
    a0 = addiu(a0, -6688);  // &0x77E5E0
    a3 = v0;
    backedge(ctx);
    // 0x004c5960
    charge(ctx, 3);
    lw(v1, a0, 16);
    if (v1 != 0) {
        for (;;) {
            // 0x004c596c
            charge(ctx, 3);
            lw(v0, v1, 8);
            if (v0 == a1) {
                break;
            }
            // 0x004c5978
            charge(ctx, 3);
            lw(v1, v1, 48);
            if (v1 == 0) {
                goto L_004c5984_4;
            }
            backedge(ctx);
        }
    }
L_004c5988:
    charge(ctx, 2);
    if (v1 == 0) {
        // 0x004c59a4
        charge(ctx, 1);
        v0 = si(-1);
    } else {
        // 0x004c5990
        charge(ctx, 5);
        sw(a2, v1, 12);
        sw(a3, v1, 16);
        sw(t0, v1, 20);
        lw(v0, v1, 0);
    }
    // 0x004c59a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    return;
L_004c5984_4:
    charge(ctx, 1);
    goto L_004c5988;
}

// sub_4CA190 [rwEngineRegisterModules] -- registers the engine's core modules (sub_4CA520: size, module id 1025..1042,
//   open / close functions) -- the error, vector, string, matrix, frame, stream, camera, image, raster, texture,
//   pipeline, the 0x4C7020 free list and resource modules -- and the pipeline's own (sub_4F28D0); 1 when all succeeded
// 0x004CA190 sub_4CA190 -- 496 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4CA190(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ca190
    enter(ctx, 124);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 0x4C0000;
    sd(ra, sp, 0x10);
    a3 = 0x4C0000;
    sq(s0, sp, 0x0);
    a0 = 8;
    a1 = 1039;
    a2 = addiu(a2, 7168);  // &sub_4C1C00
    a3 = addiu(a3, 7216);  // &sub_4C1C30
    s0 = 0;
    jal(ctx, 0x4CA1B4u, gen::fn_sub_4CA520_004ca520);
    a2 = 0x4C0000;
    a3 = 0x4C0000;
    s0 = s0 | v0;
    a0 = 24;
    a1 = 1025;
    a2 = addiu(a2, 27904);  // &sub_4C6D00
    a3 = addiu(a3, 27872);  // &sub_4C6CE0
    jal(ctx, 0x4CA1D4u, gen::fn_sub_4CA520_004ca520);
    a2 = 0x4C0000;
    a3 = 0x4C0000;
    s0 = s0 | v0;
    a0 = 0;
    a1 = 1037;
    a2 = addiu(a2, 7104);  // &sub_4C1BC0
    a3 = addiu(a3, 7136);  // &sub_4C1BE0
    jal(ctx, 0x4CA1F4u, gen::fn_sub_4CA520_004ca520);
    a2 = 0x4C0000;
    a3 = 0x4C0000;
    s0 = s0 | v0;
    a0 = 24;
    a1 = 1026;
    a2 = addiu(a2, 11264);  // &sub_4C2C00
    a3 = addiu(a3, 11152);  // &sub_4C2B90
    jal(ctx, 0x4CA214u, gen::fn_sub_4CA520_004ca520);
    a2 = 0x4D0000;
    a3 = 0x4D0000;
    s0 = s0 | v0;
    a0 = 4;
    a1 = 1027;
    a2 = addiu(a2, -22096);  // &sub_4CA9B0
    a3 = addiu(a3, -21936);  // &sub_4CAA50
    jal(ctx, 0x4CA234u, gen::fn_sub_4CA520_004ca520);
    a2 = 0x4C0000;
    a3 = 0x4C0000;
    s0 = s0 | v0;
    a0 = 4;
    a1 = 1028;
    a2 = addiu(a2, 20144);  // &sub_4C4EB0
    a3 = addiu(a3, 20272);  // &sub_4C4F30
    jal(ctx, 0x4CA254u, gen::fn_sub_4CA520_004ca520);
    a2 = 0x4D0000;
    a3 = 0x4D0000;
    s0 = s0 | v0;
    a0 = 4;
    a1 = 1029;
    a2 = addiu(a2, -25488);  // &sub_4C9C70
    a3 = addiu(a3, -25600);  // &sub_4C9C00
    jal(ctx, 0x4CA274u, gen::fn_sub_4CA520_004ca520);
    a2 = 0x4D0000;
    a3 = 0x4D0000;
    s0 = s0 | v0;
    a0 = 544;
    a1 = 1030;
    a2 = addiu(a2, -17888);  // &sub_4CBA20
    a3 = addiu(a3, -17296);  // &sub_4CBC70
    jal(ctx, 0x4CA294u, gen::fn_sub_4CA520_004ca520);
    a2 = 0x4D0000;
    a3 = 0x4D0000;
    s0 = s0 | v0;
    a0 = 100;
    a1 = 1031;
    a2 = addiu(a2, -7488);  // &sub_4CE2C0
    a3 = addiu(a3, -7600);  // &sub_4CE250
    jal(ctx, 0x4CA2B4u, gen::fn_sub_4CA520_004ca520);
    a2 = 0x4D0000;
    a3 = 0x4D0000;
    s0 = s0 | v0;
    a0 = 52;
    a1 = 1032;
    a2 = addiu(a2, 5600);  // &sub_4D15E0
    a3 = addiu(a3, 5152);  // &sub_4D1420
    jal(ctx, 0x4CA2D4u, gen::fn_sub_4CA520_004ca520);
    a2 = 0x4F0000;
    a3 = 0x4F0000;
    s0 = s0 | v0;
    a0 = 96;
    a1 = 1033;
    a2 = addiu(a2, 10352);  // &sub_4F2870
    a3 = addiu(a3, 10400);  // &sub_4F28A0
    jal(ctx, 0x4CA2F4u, gen::fn_sub_4CA520_004ca520);
    a2 = 0x4C0000;
    a3 = 0x4C0000;
    s0 = s0 | v0;
    a0 = 4;
    a1 = 1042;
    a2 = addiu(a2, 28704);  // &sub_4C7020
    a3 = addiu(a3, 28832);  // &sub_4C70A0
    jal(ctx, 0x4CA314u, gen::fn_sub_4CA520_004ca520);
    s0 = s0 | v0;
    jal(ctx, 0x4CA31Cu, gen::fn_sub_4F28D0_004f28d0);
    a2 = 0x4F0000;
    a3 = 0x4F0000;
    s0 = s0 | v0;
    a0 = 124;
    a1 = 1034;
    a2 = addiu(a2, 10128);  // &sub_4F2790
    a3 = addiu(a3, 10032);  // &sub_4F2730
    jal(ctx, 0x4CA33Cu, gen::fn_sub_4CA520_004ca520);
    a2 = 0x4C0000;
    a3 = 0x4C0000;
    s0 = s0 | v0;
    a0 = 40;
    a1 = 1035;
    a2 = addiu(a2, 18160);  // &sub_4C46F0
    a3 = addiu(a3, 18256);  // &sub_4C4750
    jal(ctx, 0x4CA35Cu, gen::fn_sub_4CA520_004ca520);
    v0 = s0 | v0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    v0 = slt(v0, 0);
    v0 = v0 ^ 0x1;
    sp = addiu(sp, 0x20);
}

// sub_4CAAC0 [frameSetRoot] -- sets a frame's root (+160) and, recursively, every descendant's (child +152, sibling
//   +156; two levels unrolled)
// 0x004CAAC0 sub_4CAAC0 -- 172 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CAAC0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004caac0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    sw(s2, a0, 160);
    lw(s3, a0, 152);
    if (s3 != 0) {
        for (;;) {
            // 0x004caaec
            charge(ctx, 4);
            sw(s2, s3, 160);
            lw(s1, s3, 152);
            if (s1 != 0) {
                // 0x004caafc
                charge(ctx, 1);
                for (;;) {
                    // 0x004cab00
                    charge(ctx, 4);
                    sw(s2, s1, 160);
                    lw(s0, s1, 152);
                    if (s0 != 0) {
                        for (;;) {
                            // 0x004cab10
                            charge(ctx, 7);
                            a0 = s0;
                            a1 = s2;
                            jal(ctx, 0x4CAB14u, gen::fn_sub_4CAAC0_004caac0);
                            lw(s0, s0, 156);
                            if (s0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004cab2c
                        charge(ctx, 1);
                    }
                    // 0x004cab30
                    charge(ctx, 3);
                    lw(s1, s1, 156);
                    if (s1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004cab3c
                charge(ctx, 1);
            }
            // 0x004cab40
            charge(ctx, 3);
            lw(s3, s3, 156);
            if (s3 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004cab4c
        charge(ctx, 1);
    }
    // 0x004cab50 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// sub_4CBA20 [imageModuleOpen] -- the image module's open (engine + gp 0x7CE938): the image free list and the 52-byte
//   format free list (sub_4C3B60), a 256-byte search path buffer (empty), the open count up, the default formats
//   registered (sub_4CDB50), a 256-byte scratch buffer; unwound on a failure; $a0, or 0
// 0x004CBA20 sub_4CBA20 -- 588 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CBA20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004cba20
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    t0 = 0x960000;
    sd(ra, sp, 0x20);
    v0 = 0x780000;
    sq(s1, sp, 0x10);
    a2 = 4;
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(a0, v0, -6512);  // 0x77E690
    t0 = addiu(t0, 16592);  // &0x9640D0
    sw(a1, gp, -17336);  // 0x7CE938
    lw(a1, gp, -20348);  // 0x7CDD74
    lw(a3, gp, -20344);  // 0x7CDD78
    v0 = 0x40000;
    t1 = v0 | 0x18;
    jal(ctx, 0x4CBA58u, gen::fn_sub_4C3B60_004c3b60);
    lw(a0, gp, -17336);  // 0x7CE938
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070
    v1 = addu(v1, a0);
    sw(v0, v1, 0);
    lw(v0, v1, 0);
    if (v0 != 0) {
        // 0x004cba88
        charge(ctx, 17);
        lw(a1, gp, -20348);  // 0x7CDD74
        t0 = 0x960000;
        lw(a3, gp, -20340);  // 0x7CDD7C
        v0 = 0x40000;
        a0 = 52;
        a2 = 4;
        t0 = addiu(t0, 16544);  // &0x9640A0
        t1 = v0 | 0x406;
        jal(ctx, 0x4CBAA4u, gen::fn_sub_4C3B60_004c3b60);
        lw(v1, gp, -17336);  // 0x7CE938
        a0 = 0x960000;
        a0 = addiu(a0, 112);  // &0x960070
        v1 = addu(a0, v1);
        sw(v0, v1, 536);
        lw(v0, v1, 536);
        if (v0 == 0) {
            // 0x004cbb90
            charge(ctx, 9);
            link(ctx, 0x4CBB90u);  // $ra first: the delay slot below depends on it
            lw(a0, v1, 0);
            call(ctx, gen::fn_sub_4C3C30_004c3c30);
            lw(a0, gp, -17336);  // 0x7CE938
            v1 = 0x960000;
            v1 = addiu(v1, 112);  // &0x960070
            v0 = 0;
            v1 = addu(v1, a0);
            sw(zero, v1, 0);
        } else {
            // 0x004cbacc
            charge(ctx, 19);
            v0 = 256;
            s0 = 0x960000;
            sw(v0, v1, 8);
            s0 = addiu(s0, 376);  // &0x960178
            lw(v1, gp, -17336);  // 0x7CE938
            v0 = 0x1040000;
            a1 = v0 | 0x406;  // &0x1040406
            lw(v0, s0, 0);  // 0x960178
            v1 = addu(a0, v1);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x4CBAF0u);  // $ra = the return address
            lw(a0, v1, 8);
            call_ptr(ctx, jt);
            lw(a0, gp, -17336);  // 0x7CE938
            v1 = 0x960000;
            v1 = addiu(v1, 112);  // &0x960070
            v1 = addu(v1, a0);
            sw(v0, v1, 4);
            lw(v0, v1, 4);
            if (v0 == 0) {
                // 0x004cbbb4
                charge(ctx, 16);
                link(ctx, 0x4CBBB4u);  // $ra first: the delay slot below depends on it
                lw(a0, v1, 536);
                call(ctx, gen::fn_sub_4C3C30_004c3c30);
                lw(v1, gp, -17336);  // 0x7CE938
                v0 = 0x960000;
                v0 = addiu(v0, 112);  // &0x960070
                v0 = addu(v0, v1);
                sw(zero, v0, 536);
                link(ctx, 0x4CBBD0u);  // $ra first: the delay slot below depends on it
                lw(a0, v0, 0);
                call(ctx, gen::fn_sub_4C3C30_004c3c30);
                lw(a0, gp, -17336);  // 0x7CE938
                v1 = 0x960000;
                v1 = addiu(v1, 112);  // &0x960070
                v0 = 0;
                v1 = addu(v1, a0);
                sw(zero, v1, 0);
            } else {
                // 0x004cbb18
                charge(ctx, 28);
                sb(zero, v0, 0);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                lw(v0, gp, -17332);  // 0x7CE93C
                v0 = addiu(v0, 1);
                link(ctx, 0x4CBB2Cu);  // $ra first: the delay slot below depends on it
                sw(v0, gp, -17332);  // 0x7CE93C
                call(ctx, gen::fn_sub_4CDB50_004cdb50);
                lw(a2, gp, -17336);  // 0x7CE938
                a0 = 0x960000;
                v0 = 0x1040000;
                a0 = addiu(a0, 112);  // &0x960070
                a1 = v0 | 0x18;  // &0x1040018
                v1 = 256;
                v0 = addu(a0, a2);
                sw(zero, v0, 540);
                sw(v1, v0, 532);
                lw(a0, v0, 532);
                lw(v0, s0, 0);
                jalr(ctx, 0x4CBB60u, v0.u());
                lw(a0, gp, -17336);  // 0x7CE938
                v1 = 0x960000;
                v1 = addiu(v1, 112);  // &0x960070
                v1 = addu(v1, a0);
                sw(v0, v1, 528);
                lw(v0, v1, 528);
                if (v0 == 0) {
                    // 0x004cbbf4
                    charge(ctx, 25);
                    v0 = 0x960000;
                    lw(v0, v0, 380);  // 0x96017C
                    jt = v0.u();  // the target, read before the delay slot
                    link(ctx, 0x4CBBFCu);  // $ra = the return address
                    lw(a0, v1, 4);
                    call_ptr(ctx, jt);
                    lw(v1, gp, -17336);  // 0x7CE938
                    v0 = 0x960000;
                    v0 = addiu(v0, 112);  // &0x960070
                    v0 = addu(v0, v1);
                    sw(zero, v0, 4);
                    sw(zero, v0, 8);
                    link(ctx, 0x4CBC1Cu);  // $ra first: the delay slot below depends on it
                    lw(a0, v0, 536);
                    call(ctx, gen::fn_sub_4C3C30_004c3c30);
                    lw(v1, gp, -17336);  // 0x7CE938
                    v0 = 0x960000;
                    v0 = addiu(v0, 112);  // &0x960070
                    v0 = addu(v0, v1);
                    sw(zero, v0, 536);
                    link(ctx, 0x4CBC38u);  // $ra first: the delay slot below depends on it
                    lw(a0, v0, 0);
                    call(ctx, gen::fn_sub_4C3C30_004c3c30);
                    lw(a0, gp, -17336);  // 0x7CE938
                    v1 = 0x960000;
                    v1 = addiu(v1, 112);  // &0x960070
                    v0 = 0;
                    v1 = addu(v1, a0);
                    sw(zero, v1, 0);
                } else {
                    // 0x004cbb88
                    charge(ctx, 2);
                    v0 = s1;
                }
            }
        }
    } else {
        // 0x004cba80
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004cbc58 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4CC5C0 [RwImageSetPath] -- sets the image search path: the module's buffer grown (RwRealloc; error 0x80000013) to
//   the string's length + 1 and the string copied; the path, or 0
// 0x004CC5C0 sub_4CC5C0 -- 228 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CC5C0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cc5c0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x960000;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, v0, 356);  // 0x960164
    s1 = a0;
    jalr(ctx, 0x4CC5D8u, v0.u());
    lw(v1, gp, -17336);  // 0x7CE938
    s0 = addiu(v0, 1);
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070
    v1 = addu(v0, v1);
    lw(v0, v1, 8);
    at = slt(v0, s0);
    if (at != 0) {
        // 0x004cc604
        charge(ctx, 9);
        lw(a0, v1, 4);
        v0 = 0x960000;
        lw(v0, v0, 384);  // 0x960180
        a1 = s0;
        v1 = 0x1040000;
        a2 = v1 | 0x406;  // &0x1040406
        jalr(ctx, 0x4CC618u, v0.u());
        if (v0 != 0) {
            // 0x004cc628
            charge(ctx, 6);
            lw(a0, gp, -17336);  // 0x7CE938
            v1 = 0x960000;
            v1 = addiu(v1, 112);  // &0x960070
            v1 = addu(v1, a0);
            sw(v0, v1, 4);
            sw(s0, v1, 8);
            goto L_004cc640;
        }
        // 0x004cc668
        charge(ctx, 10);
        v0 = 1;
        a1 = s0;
        sw(v0, sp, 0x38);
        v0 = lui(0x8000);
        a0 = v0 | 0x13;
        jal(ctx, 0x4CC678u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x3C);
        a0 = addiu(sp, 0x38);
        jal(ctx, 0x4CC684u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
        // 0x004cc690 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_004cc640:
    charge(ctx, 10);
    lw(v1, gp, -17336);  // 0x7CE938
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070
    a2 = s0;
    v0 = addu(v0, v1);
    lw(a0, v0, 4);
    a1 = s1;
    jal(ctx, 0x4CC658u, gen::fn_memcpy_00521250);
    v0 = s1;
    // 0x004cc690 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4CC6D0 [imageSearchPathForEach] -- calls $a2(path, $a3) for a file name: a relative name is tried after each
//   ';'-separated directory of the image search path (the module's scratch buffer grown to fit, RwRealloc / RwMalloc;
//   error 0x80000013) until the callback returns 0; an absolute name (sub_4C79E0) or an empty path is tried once as it
//   is; $a0, or 0
// 0x004CC6D0 sub_4CC6D0 -- 908 bytes; frame 0xF0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CC6D0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004cc6d0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    v0 = 0x960000;
    sd(ra, sp, 0x90);
    v0 = addiu(v0, 112);  // &0x960070
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    s7 = a3;
    sq(s5, sp, 0x50);
    s6 = a2;
    sq(s4, sp, 0x40);
    s5 = a1;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, -17336);  // 0x7CE938
    v0 = addu(v0, v1);
    lw(s2, v0, 4);
    s3 = a0;
    jal(ctx, 0x4CC71Cu, gen::fn_sub_4C79E0_004c79e0);
    if (v0 == 0) {
        // 0x004cc72c
        charge(ctx, 2);
        if (s2 == 0) {
            goto L_004cc79c;
        }
        // 0x004cc734
        charge(ctx, 3);
        lb(v0, s2, 0);
        if (v0 == 0) {
            goto L_004cc79c;
        }
        // 0x004cc740
        charge(ctx, 14);
        v0 = 0x960000;
        fp = 0x960000;
        v0 = addiu(v0, 356);  // &0x960164
        fp = addiu(fp, 0x150);
        sq(v0, sp, 0xD0);
        v0 = 0x960000;
        v0 = addiu(v0, 384);  // &0x960180
        sq(v0, sp, 0xC0);
        v0 = 0x960000;
        v0 = addiu(v0, 376);  // &0x960178
        sq(v0, sp, 0xB0);
        v0 = 0x960000;
        v0 = addiu(v0, 316);  // &0x96013C
        sq(v0, sp, 0xA0);
        for (;;) {
            // 0x004cc778
            charge(ctx, 4);
            v0 = sltu(0, s2);
            v0 = v0 ^ 0x1;
            if (v0 != 0) {
                goto L_004cc794;
            }
            // 0x004cc788
            charge(ctx, 3);
            lb(v0, s2, 0);
            if (v0 == 0) {
                goto L_004cc794;
            }
            // 0x004cc8ac
            charge(ctx, 11);
            lw(v0, fp, 0x0);
            a0 = s2;
            a1 = 59;
            jalr(ctx, 0x4CC8B4u, v0.u());
            lw(v0, fp, 0x0);
            a0 = s2;
            a1 = 59;
            jalr(ctx, 0x4CC8C4u, v0.u());
            s1 = v0;
            if (s1 == 0) {
                // 0x004cc9d8
                charge(ctx, 6);
                lq(v0, sp, 0xD0);
                lw(v0, v0, 0);
                a0 = s2;
                jalr(ctx, 0x4CC9E0u, v0.u());
                s0 = v0;
                backedge(ctx);
            } else {
                // 0x004cc8d8
                charge(ctx, 2);
                s0 = subu(s1, s2);
                s1 = addiu(s1, 1);
            }
            // 0x004cc8e0
            charge(ctx, 14);
            lq(v0, sp, 0xD0);
            lw(v0, v0, 0);
            a0 = s3;
            jalr(ctx, 0x4CC8E8u, v0.u());
            lw(v1, gp, -17336);  // 0x7CE938
            v0 = addu(s0, v0);
            s4 = addu(s5, v0);
            v0 = 0x960000;
            v0 = addiu(v0, 112);  // &0x960070
            v1 = addu(v0, v1);
            lw(v0, v1, 532);
            at = slt(v0, s4);
            if (at != 0) {
                // 0x004cc918
                charge(ctx, 3);
                lw(a0, v1, 528);
                if (a0 == 0) {
                    // 0x004cc944
                    charge(ctx, 6);
                    v0 = 0x1040000;
                    a1 = v0 | 0x18;  // &0x1040018
                    lq(v0, sp, 0xB0);
                    lw(v0, v0, 0);
                    a0 = s4;
                    jalr(ctx, 0x4CC954u, v0.u());
                } else {
                    // 0x004cc924
                    charge(ctx, 8);
                    v0 = 0x1040000;
                    a2 = v0 | 0x18;  // &0x1040018
                    lq(v0, sp, 0xC0);
                    lw(v0, v0, 0);
                    a1 = s4;
                    jalr(ctx, 0x4CC934u, v0.u());
                }
                // 0x004cc95c
                charge(ctx, 2);
                if (v0 != 0) {
                    // 0x004cc964
                    charge(ctx, 6);
                    lw(a0, gp, -17336);  // 0x7CE938
                    v1 = 0x960000;
                    v1 = addiu(v1, 112);  // &0x960070
                    v1 = addu(v1, a0);
                    sw(v0, v1, 528);
                    sw(s4, v1, 532);
                    goto L_004cc97c;
                }
                // 0x004cc9f0
                charge(ctx, 12);
                v0 = 1;
                a1 = s4;
                sw(v0, sp, 0xE0);
                v0 = lui(0x8000);
                a0 = v0 | 0x13;
                jal(ctx, 0x4CCA00u, gen::fn_sub_4C1D10_004c1d10);
                v1 = addiu(sp, 0xE4);
                a0 = addiu(sp, 0xE0);
                link(ctx, 0x4CCA10u);  // $ra first: the delay slot below depends on it
                sw(v0, v1, 0);
                call(ctx, gen::fn_sub_4C1C50_004c1c50);
                s4 = 0;
                backedge(ctx);
                goto L_004cc990;
            }
        L_004cc97c:
            charge(ctx, 5);
            lw(v1, gp, -17336);  // 0x7CE938
            v0 = 0x960000;
            v0 = addiu(v0, 112);  // &0x960070
            v0 = addu(v0, v1);
            lw(s4, v0, 528);
        L_004cc990:
            charge(ctx, 2);
            if (s4 == 0) {
                break;
            }
            // 0x004cc998
            charge(ctx, 14);
            a1 = s2;
            a0 = s4;
            a2 = s0;
            jal(ctx, 0x4CC9A0u, gen::fn_memcpy_00521250);
            lq(v0, sp, 0xA0);
            a0 = addu(s4, s0);
            lw(v0, v0, 0);
            a1 = s3;
            jalr(ctx, 0x4CC9B4u, v0.u());
            a0 = s4;
            a1 = s7;
            jalr(ctx, 0x4CC9C0u, s6.u());
            if (v0 == 0) {
                goto L_004cca28;
            }
            // 0x004cc9d0
            charge(ctx, 2);
            s2 = s1;
            backedge(ctx);
        }
        // 0x004cca20
        charge(ctx, 2);
        v0 = 0;
        // 0x004cca2c (the shared epilogue, written out on this path)
        charge(ctx, 12);
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
        sp = addiu(sp, 0xF0);
        return;
    }
L_004cc79c:
    charge(ctx, 13);
    v0 = 0x960000;
    lw(v0, v0, 356);  // 0x960164
    a0 = s3;
    jalr(ctx, 0x4CC7A4u, v0.u());
    lw(v1, gp, -17336);  // 0x7CE938
    s0 = addu(s5, v0);
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070
    v1 = addu(v0, v1);
    lw(v0, v1, 532);
    at = slt(v0, s0);
    if (at != 0) {
        // 0x004cc7d0
        charge(ctx, 3);
        lw(a0, v1, 528);
        if (a0 == 0) {
            // 0x004cc7fc
            charge(ctx, 6);
            v0 = 0x1040000;
            a1 = v0 | 0x18;  // &0x1040018
            v0 = 0x960000;
            lw(v0, v0, 376);  // 0x960178
            a0 = s0;
            jalr(ctx, 0x4CC80Cu, v0.u());
        } else {
            // 0x004cc7dc
            charge(ctx, 8);
            v0 = 0x1040000;
            a2 = v0 | 0x18;  // &0x1040018
            v0 = 0x960000;
            lw(v0, v0, 384);  // 0x960180
            a1 = s0;
            jalr(ctx, 0x4CC7ECu, v0.u());
        }
        // 0x004cc814
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x004cc81c
            charge(ctx, 6);
            lw(a0, gp, -17336);  // 0x7CE938
            v1 = 0x960000;
            v1 = addiu(v1, 112);  // &0x960070
            v1 = addu(v1, a0);
            sw(v0, v1, 528);
            sw(s0, v1, 532);
            goto L_004cc834;
        }
        // 0x004cc878
        charge(ctx, 11);
        v0 = 1;
        a1 = s0;
        sw(v0, sp, 0xE8);
        v0 = lui(0x8000);
        a0 = v0 | 0x13;
        jal(ctx, 0x4CC888u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0xEC);
        a0 = addiu(sp, 0xE8);
        jal(ctx, 0x4CC894u, gen::fn_sub_4C1C50_004c1c50);
        s0 = 0;
        backedge(ctx);
        goto L_004cc848;
    }
L_004cc834:
    charge(ctx, 5);
    lw(v1, gp, -17336);  // 0x7CE938
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070
    v0 = addu(v0, v1);
    lw(s0, v0, 528);
L_004cc848:
    charge(ctx, 2);
    if (s0 == 0) {
        // 0x004cc8a4
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004cc850
        charge(ctx, 10);
        v0 = 0x960000;
        a0 = s0;
        lw(v0, v0, 316);  // 0x96013C
        a1 = s3;
        jalr(ctx, 0x4CC85Cu, v0.u());
        a0 = s0;
        a1 = s7;
        jalr(ctx, 0x4CC868u, s6.u());
        backedge(ctx);
    L_004cc794:
        charge(ctx, 2);
        v0 = s3;
    }
    // 0x004cca2c (the shared epilogue, written out on this path)
    charge(ctx, 12);
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
    sp = addiu(sp, 0xF0);
    return;
L_004cca28:
    charge(ctx, 1);
    v0 = s3;
    // 0x004cca2c (the shared epilogue, written out on this path)
    charge(ctx, 12);
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
    sp = addiu(sp, 0xF0);
}

// sub_4CCA60 [imageReadCB] -- the image read's search-path callback: when the file exists (sub_4C06C0) the format's
//   reader (*$a1) is called and its image stored in $a1[1]; 0 (stop) once an image was read, else the path
// 0x004CCA60 sub_4CCA60 -- 96 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CCA60(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cca60
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    jal(ctx, 0x4CCA74u, gen::fn_sub_4C06C0_004c06c0);
    if (v0 != 0) {
        // 0x004cca8c
        charge(ctx, 7);
        lw(v0, s0, 0);
        a0 = s1;
        jalr(ctx, 0x4CCA90u, v0.u());
        sw(v0, s0, 4);
        lw(v0, s0, 4);
        if (v0 == 0) {
            backedge(ctx);
            goto L_004cca84;
        }
        // 0x004ccaa8
        charge(ctx, 1);
        v0 = 0;
        // 0x004ccaac (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
L_004cca84:
    charge(ctx, 2);
    v0 = s1;
    // 0x004ccaac (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4CCAC0 [RwImageRead] -- reads an image file: the extension found after the last ':', '/', '\' and '.', the
//   registered format with that extension (lower- or upper-case, strcmp slot), its reader run over the search path
//   (sub_4CC6D0 with sub_4CCA60); the image, or 0
// 0x004CCAC0 sub_4CCAC0 -- 360 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CCAC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ccac0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    a1 = 58;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0x960000;
    s0 = addiu(s0, 332);  // &0x96014C
    lw(v0, s0, 0);  // 0x96014C
    s1 = a0;
    jalr(ctx, 0x4CCAE8u, v0.u());
    if (v0 == 0) {
        // 0x004ccb00
        charge(ctx, 1);
        s2 = s1;
    } else {
        // 0x004ccaf8
        charge(ctx, 2);
        s2 = v0;
    }
    // 0x004ccb04
    charge(ctx, 6);
    lw(v0, s0, 0);
    a0 = s2;
    a1 = 47;
    jalr(ctx, 0x4CCB0Cu, v0.u());
    if (v0 != 0) {
        // 0x004ccb1c
        charge(ctx, 1);
        s2 = v0;
    }
    // 0x004ccb20
    charge(ctx, 6);
    lw(v0, s0, 0);
    a0 = s2;
    a1 = 92;
    jalr(ctx, 0x4CCB28u, v0.u());
    if (v0 == 0) {
        // 0x004ccb40
        charge(ctx, 2);
        v0 = s2;
        lw(v1, s0, 0);
    } else {
        // 0x004ccb38
        charge(ctx, 2);
        lw(v1, s0, 0);
    }
    // 0x004ccb48
    charge(ctx, 6);
    a0 = v0;
    a1 = 46;
    jalr(ctx, 0x4CCB4Cu, v1.u());
    s0 = v0;
    if (s0 == 0) {
        // 0x004ccc08
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004ccb60
        charge(ctx, 7);
        lw(v1, gp, -17336);  // 0x7CE938
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070
        v0 = addu(v0, v1);
        lw(s3, v0, 540);
        if (s3 != 0) {
            // 0x004ccb7c
            charge(ctx, 2);
            s2 = 0x960000;
            s2 = addiu(s2, 344);  // &0x960158
            for (;;) {
                // 0x004ccb84
                charge(ctx, 6);
                lw(v0, s2, 0);
                a0 = s3;
                a1 = s0;
                jalr(ctx, 0x4CCB8Cu, v0.u());
                if (v0 == 0) {
                    goto L_004ccbc8;
                }
                // 0x004ccb9c
                charge(ctx, 6);
                lw(v0, s2, 0);
                a0 = addiu(s3, 20);
                a1 = s0;
                jalr(ctx, 0x4CCBA4u, v0.u());
                if (v0 == 0) {
                    goto L_004ccbc8;
                }
                // 0x004ccbb4
                charge(ctx, 3);
                lw(s3, s3, 48);
                if (s3 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004ccbc0
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004ccc0c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004ccbc8:
    charge(ctx, 3);
    lw(v0, s3, 40);
    if (v0 == 0) {
        // 0x004ccc00
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004ccbd4
        charge(ctx, 11);
        a2 = 0x4D0000;
        s0 = addiu(sp, 0x5C);
        sw(v0, sp, 0x58);
        a0 = s1;
        a1 = 5;
        a2 = addiu(a2, -13728);  // &sub_4CCA60
        a3 = addiu(sp, 0x58);
        link(ctx, 0x4CCBF0u);  // $ra first: the delay slot below depends on it
        sw(zero, s0, 0);
        call(ctx, gen::fn_sub_4CC6D0_004cc6d0);
        lw(v0, s0, 0);
    }
    // 0x004ccc0c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4CCC30 [imageFindFileCB] -- the image find's search-path callback: the path with each registered format's lower-
//   and upper-case extension appended tested (sub_4C06C0); on a hit the extension's address stored in *$a1 and 0 returned
//   (stop), else the path
// 0x004CCC30 sub_4CCC30 -- 236 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CCC30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ccc30
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 0x960000;
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, v0, 356);  // 0x960164
    s3 = a1;
    jalr(ctx, 0x4CCC58u, v0.u());
    lw(v1, gp, -17336);  // 0x7CE938
    s1 = addu(s4, v0);
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070
    v0 = addu(v0, v1);
    lw(s2, v0, 540);
    if (s2 != 0) {
        // 0x004ccc80
        charge(ctx, 2);
        s0 = 0x960000;
        s0 = addiu(s0, 316);  // &0x96013C
        for (;;) {
            // 0x004ccc88
            charge(ctx, 10);
            lw(v0, s0, 0);
            a0 = s1;
            a1 = s2;
            jalr(ctx, 0x4CCC90u, v0.u());
            a0 = s4;
            jal(ctx, 0x4CCC98u, gen::fn_sub_4C06C0_004c06c0);
            v0 = sltu(0, v0);
            v0 = v0 ^ 0x1;
            if (v0 == 0) {
                goto L_004cccb0_3;
            }
            // 0x004cccbc
            charge(ctx, 8);
            lw(v0, s0, 0);
            a0 = s1;
            a1 = addiu(s2, 20);
            jalr(ctx, 0x4CCCC4u, v0.u());
            a0 = s4;
            jal(ctx, 0x4CCCCCu, gen::fn_sub_4C06C0_004c06c0);
            if (v0 != 0) {
                goto L_004cccf0;
            }
            // 0x004cccdc
            charge(ctx, 3);
            lw(s2, s2, 48);
            if (s2 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004ccce8
    charge(ctx, 2);
    v0 = s4;
    // 0x004cccfc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004cccb0_3:
    charge(ctx, 3);
    sw(s2, s3, 0);
    v0 = 0;
    // 0x004cccfc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004cccf0:
    charge(ctx, 3);
    v1 = addiu(s2, 20);
    v0 = 0;
    sw(v1, s3, 0);
    // 0x004cccfc (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// sub_4CCD20 [imageFindFile] -- finds an image file over the search path trying every registered extension (sub_4CC6D0
//   with sub_4CCC30); the extension found, or 0
// 0x004CCD20 sub_4CCD20 -- 48 bytes; frame 0x20: ra sp+0x0
void sub_4CCD20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ccd20
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 0x4D0000;
    sd(ra, sp, 0x0);
    a1 = 20;
    a2 = addiu(a2, -13264);  // &sub_4CCC30
    a3 = addiu(sp, 0x1C);
    link(ctx, 0x4CCD38u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x1C);
    call(ctx, gen::fn_sub_4CC6D0_004cc6d0);
    lw(v0, sp, 0x1C);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4CCD50 [RwImageRegisterImageFormat] -- registers an image file format: the extension as ".ext" (18 characters)
//   lower-cased; an existing entry is reused, else a 52-byte entry from the format free list with the lower- and
//   upper-case extensions, linked at the head; the reader ($a1) and writer ($a2) set when given; 1, or 0
// 0x004CCD50 sub_4CCD50 -- 448 bytes; frame 0xA0: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CCD50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004ccd50
    enter(ctx, 34);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    v0 = 46;
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = 0x960000;
    sq(s4, sp, 0x40);
    s5 = a2;
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s6 = addiu(s6, 320);  // &0x960140
    sq(s0, sp, 0x0);
    a0 = addiu(sp, 0x81);
    sb(v0, sp, 0x80);
    a1 = s4;
    lw(v0, s6, 0);  // 0x960140
    a2 = 18;
    jalr(ctx, 0x4CCD9Cu, v0.u());
    v0 = 0x960000;
    a0 = addiu(sp, 0x80);
    lw(v0, v0, 364);  // 0x96016C
    jt = v0.u();  // the target, read before the delay slot
    link(ctx, 0x4CCDB0u);  // $ra = the return address
    sb(zero, sp, 0x93);
    call_ptr(ctx, jt);
    lw(v1, gp, -17336);  // 0x7CE938
    v0 = 0x960000;
    v0 = addiu(v0, 112);  // &0x960070
    s0 = 0x960000;
    s2 = 0;
    s0 = addiu(s0, 344);  // &0x960158
    v0 = addu(v0, v1);
    lw(s1, v0, 540);
    for (;;) {
        // 0x004ccdd8
        charge(ctx, 4);
        v0 = sltu(0, s1);
        v0 = v0 ^ 0x1;
        if (v0 == 0) {
            // 0x004ccde8
            charge(ctx, 2);
            if (s2 == 0) {
                // 0x004ccdf0
                charge(ctx, 6);
                lw(v0, s0, 0);
                a0 = s1;
                a1 = addiu(sp, 0x80);
                jalr(ctx, 0x4CCDF8u, v0.u());
                if (v0 != 0) {
                    // 0x004cce10
                    charge(ctx, 2);
                    lw(s1, s1, 48);
                    backedge(ctx);
                } else {
                    // 0x004cce08
                    charge(ctx, 2);
                    s2 = s1;
                    backedge(ctx);
                }
                continue;
            }
        }
        break;
    }
    // 0x004cce18
    charge(ctx, 2);
    if (s2 == 0) {
        // 0x004cce40
        charge(ctx, 13);
        lw(a2, gp, -17336);  // 0x7CE938
        a0 = 0x960000;
        v1 = 0x30000;
        v0 = 0x960000;
        a0 = addiu(a0, 112);  // &0x960070
        a1 = v1 | 0x406;
        lw(v0, v0, 392);  // 0x960188
        v1 = addu(a0, a2);
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x4CCE60u);  // $ra = the return address
        lw(a0, v1, 536);
        call_ptr(ctx, jt);
        s2 = v0;
        if (s2 != 0) {
            // 0x004cce74
            charge(ctx, 28);
            a0 = s2;
            a1 = addiu(sp, 0x80);
            a2 = 20;
            jal(ctx, 0x4CCE7Cu, gen::fn_memcpy_00521250);
            v0 = 46;
            a1 = s4;
            sb(v0, s2, 20);
            a0 = addiu(s2, 21);
            lw(v0, s6, 0);
            a2 = 18;
            jalr(ctx, 0x4CCE98u, v0.u());
            sb(zero, s2, 39);
            v0 = 0x960000;
            lw(v0, v0, 360);  // 0x960168
            a0 = addiu(s2, 20);
            jalr(ctx, 0x4CCEACu, v0.u());
            sw(zero, s2, 40);
            v1 = 0x960000;
            sw(zero, s2, 44);
            v1 = addiu(v1, 112);  // &0x960070
            lw(v0, gp, -17336);  // 0x7CE938
            v0 = addu(v1, v0);
            lw(v0, v0, 540);
            sw(v0, s2, 48);
            lw(v0, gp, -17336);  // 0x7CE938
            v0 = addu(v1, v0);
            sw(s2, v0, 540);
            backedge(ctx);
            goto L_004cce20;
        }
        // 0x004ccee4
        charge(ctx, 1);
        v0 = 0;
        // 0x004ccee8 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(ra, sp, 0x70);
        lq(s6, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0xA0);
        return;
    }
L_004cce20:
    charge(ctx, 2);
    if (s3 != 0) {
        // 0x004cce28
        charge(ctx, 1);
        sw(s3, s2, 40);
    }
    // 0x004cce2c
    charge(ctx, 2);
    if (s5 != 0) {
        // 0x004cce34
        charge(ctx, 1);
        sw(s5, s2, 44);
    }
    // 0x004cce38
    charge(ctx, 2);
    v0 = 1;
    // 0x004ccee8 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// sub_4CCF10 [RwImageReadMaskedImage] -- reads an image and, when a mask name is given, its mask (RwImageRead each),
//   the mask turned into alpha (sub_4CC0A0 / sub_4CC1D0) and the mask image destroyed (pixels freed, plugin destructors
//   on 0x77E690, the free list); on a failure both are destroyed; the image, or 0
// 0x004CCF10 sub_4CCF10 -- 836 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CCF10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x004ccf10
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    s1 = a1;
    link(ctx, 0x4CCF20u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4CCAC0_004ccac0);
    s0 = v0;
    if (s0 == 0) {
        // 0x004cd23c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004ccf34
        charge(ctx, 2);
        if (s1 != 0) {
            // 0x004ccf3c
            charge(ctx, 3);
            lb(v0, s1, 0);
            if (v0 == 0) {
                goto L_004cd1dc;
            }
            // 0x004ccf48
            charge(ctx, 5);
            a0 = s1;
            jal(ctx, 0x4CCF48u, gen::fn_sub_4CCAC0_004ccac0);
            s1 = v0;
            if (s1 == 0) {
                // 0x004ccffc
                charge(ctx, 4);
                lw(v0, s0, 0);
                v0 = v0 & 0x1;
                if (v0 != 0) {
                    // 0x004cd048
                    charge(ctx, 11);
                    v0 = 0x960000;
                    lw(v0, v0, 380);  // 0x96017C
                    jt = v0.u();  // the target, read before the delay slot
                    link(ctx, 0x4CD050u);  // $ra = the return address
                    lw(a0, s0, 20);
                    call_ptr(ctx, jt);
                    sw(zero, s0, 20);
                    v0 = si(-2);
                    sw(zero, s0, 24);
                    lw(v1, s0, 0);
                    v0 = v1 & v0;
                    sw(v0, s0, 0);
                    backedge(ctx);
                }
                // 0x004cd00c
                charge(ctx, 15);
                a0 = 0x780000;
                a1 = s0;
                a0 = addiu(a0, -6512);  // &0x77E690
                jal(ctx, 0x4CD014u, gen::fn_sub_4C6560_004c6560);
                lw(a0, gp, -17336);  // 0x7CE938
                v1 = 0x960000;
                v1 = addiu(v1, 112);  // &0x960070
                v0 = 0x960000;
                lw(v0, v0, 396);  // 0x96018C
                v1 = addu(v1, a0);
                lw(a0, v1, 0);
                a1 = s0;
                jalr(ctx, 0x4CD038u, v0.u());
                v0 = 0;
            } else {
                // 0x004ccf5c
                charge(ctx, 4);
                a0 = s1;
                jal(ctx, 0x4CCF5Cu, gen::fn_sub_4CC0A0_004cc0a0);
                if (v0 != 0) {
                    // 0x004cd0cc
                    charge(ctx, 5);
                    a0 = s0;
                    a1 = s1;
                    jal(ctx, 0x4CD0D0u, gen::fn_sub_4CC1D0_004cc1d0);
                    if (v0 != 0) {
                        // 0x004cd170
                        charge(ctx, 4);
                        lw(v0, s1, 0);
                        v0 = v0 & 0x1;
                        if (v0 != 0) {
                            // 0x004cd180
                            charge(ctx, 10);
                            v0 = 0x960000;
                            lw(v0, v0, 380);  // 0x96017C
                            jt = v0.u();  // the target, read before the delay slot
                            link(ctx, 0x4CD188u);  // $ra = the return address
                            lw(a0, s1, 20);
                            call_ptr(ctx, jt);
                            sw(zero, s1, 20);
                            v0 = si(-2);
                            sw(zero, s1, 24);
                            lw(v1, s1, 0);
                            v0 = v1 & v0;
                            sw(v0, s1, 0);
                        }
                        // 0x004cd1a8
                        charge(ctx, 13);
                        a0 = 0x780000;
                        a1 = s1;
                        a0 = addiu(a0, -6512);  // &0x77E690
                        jal(ctx, 0x4CD1B0u, gen::fn_sub_4C6560_004c6560);
                        lw(a0, gp, -17336);  // 0x7CE938
                        v1 = 0x960000;
                        v1 = addiu(v1, 112);  // &0x960070
                        v0 = 0x960000;
                        lw(v0, v0, 396);  // 0x96018C
                        v1 = addu(v1, a0);
                        lw(a0, v1, 0);
                        a1 = s1;
                        jalr(ctx, 0x4CD1D4u, v0.u());
                        goto L_004cd1dc;
                    }
                    // 0x004cd0e0
                    charge(ctx, 4);
                    lw(v0, s0, 0);
                    v0 = v0 & 0x1;
                    if (v0 != 0) {
                        // 0x004cd1e4
                        charge(ctx, 11);
                        v0 = 0x960000;
                        lw(v0, v0, 380);  // 0x96017C
                        jt = v0.u();  // the target, read before the delay slot
                        link(ctx, 0x4CD1ECu);  // $ra = the return address
                        lw(a0, s0, 20);
                        call_ptr(ctx, jt);
                        sw(zero, s0, 20);
                        v0 = si(-2);
                        sw(zero, s0, 24);
                        lw(v1, s0, 0);
                        v0 = v1 & v0;
                        sw(v0, s0, 0);
                        backedge(ctx);
                    }
                    // 0x004cd0f0
                    charge(ctx, 18);
                    a0 = 0x780000;
                    a1 = s0;
                    a0 = addiu(a0, -6512);  // &0x77E690
                    jal(ctx, 0x4CD0F8u, gen::fn_sub_4C6560_004c6560);
                    lw(a0, gp, -17336);  // 0x7CE938
                    a1 = s0;
                    v1 = 0x960000;
                    s0 = 0x960000;
                    v1 = addiu(v1, 112);  // &0x960070
                    s0 = addiu(s0, 396);  // &0x96018C
                    lw(v0, s0, 0);  // 0x96018C
                    v1 = addu(v1, a0);
                    jt = v0.u();  // the target, read before the delay slot
                    link(ctx, 0x4CD120u);  // $ra = the return address
                    lw(a0, v1, 0);
                    call_ptr(ctx, jt);
                    lw(v0, s1, 0);
                    v0 = v0 & 0x1;
                    if (v0 != 0) {
                        // 0x004cd210
                        charge(ctx, 11);
                        v0 = 0x960000;
                        lw(v0, v0, 380);  // 0x96017C
                        jt = v0.u();  // the target, read before the delay slot
                        link(ctx, 0x4CD218u);  // $ra = the return address
                        lw(a0, s1, 20);
                        call_ptr(ctx, jt);
                        sw(zero, s1, 20);
                        v0 = si(-2);
                        sw(zero, s1, 24);
                        lw(v1, s1, 0);
                        v0 = v1 & v0;
                        sw(v0, s1, 0);
                        backedge(ctx);
                    }
                    // 0x004cd138
                    charge(ctx, 14);
                    a0 = 0x780000;
                    a1 = s1;
                    a0 = addiu(a0, -6512);  // &0x77E690
                    jal(ctx, 0x4CD140u, gen::fn_sub_4C6560_004c6560);
                    lw(a0, gp, -17336);  // 0x7CE938
                    v1 = 0x960000;
                    v1 = addiu(v1, 112);  // &0x960070
                    lw(v0, s0, 0);
                    v1 = addu(v1, a0);
                    lw(a0, v1, 0);
                    a1 = s1;
                    jalr(ctx, 0x4CD160u, v0.u());
                    v0 = 0;
                } else {
                    // 0x004ccf6c
                    charge(ctx, 4);
                    lw(v0, s0, 0);
                    v0 = v0 & 0x1;
                    if (v0 != 0) {
                        // 0x004cd074
                        charge(ctx, 11);
                        v0 = 0x960000;
                        lw(v0, v0, 380);  // 0x96017C
                        jt = v0.u();  // the target, read before the delay slot
                        link(ctx, 0x4CD07Cu);  // $ra = the return address
                        lw(a0, s0, 20);
                        call_ptr(ctx, jt);
                        sw(zero, s0, 20);
                        v0 = si(-2);
                        sw(zero, s0, 24);
                        lw(v1, s0, 0);
                        v0 = v1 & v0;
                        sw(v0, s0, 0);
                        backedge(ctx);
                    }
                    // 0x004ccf7c
                    charge(ctx, 18);
                    a0 = 0x780000;
                    a1 = s0;
                    a0 = addiu(a0, -6512);  // &0x77E690
                    jal(ctx, 0x4CCF84u, gen::fn_sub_4C6560_004c6560);
                    lw(a0, gp, -17336);  // 0x7CE938
                    a1 = s0;
                    v1 = 0x960000;
                    s0 = 0x960000;
                    v1 = addiu(v1, 112);  // &0x960070
                    s0 = addiu(s0, 396);  // &0x96018C
                    lw(v0, s0, 0);  // 0x96018C
                    v1 = addu(v1, a0);
                    jt = v0.u();  // the target, read before the delay slot
                    link(ctx, 0x4CCFACu);  // $ra = the return address
                    lw(a0, v1, 0);
                    call_ptr(ctx, jt);
                    lw(v0, s1, 0);
                    v0 = v0 & 0x1;
                    if (v0 != 0) {
                        // 0x004cd0a0
                        charge(ctx, 11);
                        v0 = 0x960000;
                        lw(v0, v0, 380);  // 0x96017C
                        jt = v0.u();  // the target, read before the delay slot
                        link(ctx, 0x4CD0A8u);  // $ra = the return address
                        lw(a0, s1, 20);
                        call_ptr(ctx, jt);
                        sw(zero, s1, 20);
                        v0 = si(-2);
                        sw(zero, s1, 24);
                        lw(v1, s1, 0);
                        v0 = v1 & v0;
                        sw(v0, s1, 0);
                        backedge(ctx);
                    }
                    // 0x004ccfc4
                    charge(ctx, 14);
                    a0 = 0x780000;
                    a1 = s1;
                    a0 = addiu(a0, -6512);  // &0x77E690
                    jal(ctx, 0x4CCFCCu, gen::fn_sub_4C6560_004c6560);
                    lw(a0, gp, -17336);  // 0x7CE938
                    v1 = 0x960000;
                    v1 = addiu(v1, 112);  // &0x960070
                    lw(v0, s0, 0);
                    v1 = addu(v1, a0);
                    lw(a0, v1, 0);
                    a1 = s1;
                    jalr(ctx, 0x4CCFECu, v0.u());
                    v0 = 0;
                }
            }
            // 0x004cd240 (the shared epilogue, written out on this path)
            charge(ctx, 5);
            ld(ra, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
    L_004cd1dc:
        charge(ctx, 2);
        v0 = s0;
    }
    // 0x004cd240 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4CD260 [rwImageCopyPixels] -- copies an image's pixels into another of the same size by their depths: 8 / 4 bpp
//   to 32 bpp through the palette, 8 to 8 row by row, same-depth 32 / 4 / 8 already equal, other pairs refused (error
//   0x80000009); 1, or 0
// 0x004CD260 sub_4CD260 -- 956 bytes; frame 0x90: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CD260(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cd260
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    lw(a2, a1, 24);
    sd(ra, sp, 0x70);
    v0 = 8200;
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a1;
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    lw(s2, a1, 20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, 4);
    lw(s0, a0, 8);
    lw(s3, a0, 20);
    lw(a1, a1, 12);
    lw(v1, a0, 12);
    a0 = sll(a1, 8);
    v1 = a0 | v1;
    s4 = 0;
    if (v1 != v0) {
        // 0x004cd2bc
        charge(ctx, 3);
        v0 = 8196;
        if (v1 == v0) {
            goto L_004cd598;
        }
        // 0x004cd2c8
        charge(ctx, 3);
        v0 = 2052;
        if (v1 == v0) {
            goto L_004cd598;
        }
        // 0x004cd2d4
        charge(ctx, 3);
        v0 = 2080;
        if (v1 != v0) {
            // 0x004cd2e0
            charge(ctx, 3);
            v0 = 1056;
            if (v1 == v0) {
                goto L_004cd340;
            }
            // 0x004cd2ec
            charge(ctx, 3);
            v0 = 1032;
            if (v1 == v0) {
                // 0x004cd32c
                charge(ctx, 3);
                v0 = slt(0, s0);
                if (v0 != 0) {
                    for (;;) {
                        // 0x004cd5c0
                        charge(ctx, 11);
                        a0 = s3;
                        a1 = s2;
                        a2 = s1;
                        jal(ctx, 0x4CD5C8u, gen::fn_memcpy_00521250);
                        lw(a0, s6, 16);
                        s4 = addiu(s4, 1);
                        lw(v1, s5, 16);
                        v0 = slt(s4, s0);
                        s2 = addu(s2, a0);
                        s3 = addu(s3, v1);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004cd5ec
                    charge(ctx, 2);
                    backedge(ctx);
                }
                // 0x004cd338
                charge(ctx, 2);
                s4 = 1;
            } else {
                // 0x004cd2f8
                charge(ctx, 3);
                v0 = 8224;
                if (v1 != v0) {
                    // 0x004cd304
                    charge(ctx, 3);
                    v0 = 2056;
                    if (v1 == v0) {
                        goto L_004cd324;
                    }
                    // 0x004cd310
                    charge(ctx, 3);
                    v0 = 1028;
                    if (v1 == v0) {
                        goto L_004cd324;
                    }
                    // 0x004cd31c
                    charge(ctx, 2);
                    v1 = 1;
                L_004cd59c:
                    charge(ctx, 7);
                    v0 = lui(0x8000);
                    sw(v1, sp, 0x88);
                    a0 = v0 | 0x9;
                    jal(ctx, 0x4CD5A4u, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0x8C);
                    a0 = addiu(sp, 0x88);
                    jal(ctx, 0x4CD5B0u, gen::fn_sub_4C1C50_004c1c50);
                    goto L_004cd5b8;
                }
            L_004cd324:
                charge(ctx, 2);
                s4 = 1;
            }
            goto L_004cd5b8;
        }
    L_004cd340:
        charge(ctx, 3);
        at = slt(0, s0);
        a1 = 0;
        if (at != 0) {
            // 0x004cd34c
            charge(ctx, 3);
            lw(t1, s6, 16);
            v1 = 1;
            a0 = addiu(s1, -8);
            for (;;) {
                // 0x004cd358
                charge(ctx, 3);
                at = slt(0, s1);
                t0 = 0;
                if (at != 0) {
                    // 0x004cd364
                    charge(ctx, 3);
                    at = slti(s1, 9);
                    if (at == 0) {
                        // 0x004cd370
                        charge(ctx, 3);
                        at = slt(s1, 0);
                        v0 = 0;
                        if (at == 0) {
                            // 0x004cd37c
                            charge(ctx, 5);
                            at = 0x7FFF0000;
                            at = at | 0xFFFF;
                            at = slt(s1, at);
                            if (at != 0) {
                                // 0x004cd390
                                charge(ctx, 2);
                                v0 = v1;
                            }
                        }
                        // 0x004cd398
                        charge(ctx, 2);
                        if (v0 != 0) {
                            // 0x004cd3a0
                            charge(ctx, 2);
                            a3 = s3;
                            for (;;) {
                                // 0x004cd3a8
                                charge(ctx, 93);
                                v0 = addu(s2, t0);
                                lbu(t3, v0, 0);
                                t0 = addiu(t0, 8);
                                t2 = slt(t0, a0);
                                t3 = sll(t3, 2);
                                t3 = addu(a2, t3);
                                lbu(t6, t3, 0);
                                lbu(t5, t3, 1);
                                lbu(t4, t3, 2);
                                lbu(t3, t3, 3);
                                sb(t6, a3, 0);
                                sb(t5, a3, 1);
                                sb(t4, a3, 2);
                                sb(t3, a3, 3);
                                lbu(t3, v0, 1);
                                t3 = sll(t3, 2);
                                t3 = addu(a2, t3);
                                lbu(t6, t3, 0);
                                lbu(t5, t3, 1);
                                lbu(t4, t3, 2);
                                lbu(t3, t3, 3);
                                sb(t6, a3, 4);
                                sb(t5, a3, 5);
                                sb(t4, a3, 6);
                                sb(t3, a3, 7);
                                lbu(t3, v0, 2);
                                t3 = sll(t3, 2);
                                t3 = addu(a2, t3);
                                lbu(t6, t3, 0);
                                lbu(t5, t3, 1);
                                lbu(t4, t3, 2);
                                lbu(t3, t3, 3);
                                sb(t6, a3, 8);
                                sb(t5, a3, 9);
                                sb(t4, a3, 10);
                                sb(t3, a3, 11);
                                lbu(t3, v0, 3);
                                t3 = sll(t3, 2);
                                t3 = addu(a2, t3);
                                lbu(t6, t3, 0);
                                lbu(t5, t3, 1);
                                lbu(t4, t3, 2);
                                lbu(t3, t3, 3);
                                sb(t6, a3, 12);
                                sb(t5, a3, 13);
                                sb(t4, a3, 14);
                                sb(t3, a3, 15);
                                lbu(t3, v0, 4);
                                t3 = sll(t3, 2);
                                t3 = addu(a2, t3);
                                lbu(t6, t3, 0);
                                lbu(t5, t3, 1);
                                lbu(t4, t3, 2);
                                lbu(t3, t3, 3);
                                sb(t6, a3, 16);
                                sb(t5, a3, 17);
                                sb(t4, a3, 18);
                                sb(t3, a3, 19);
                                lbu(t3, v0, 5);
                                t3 = sll(t3, 2);
                                t3 = addu(a2, t3);
                                lbu(t6, t3, 0);
                                lbu(t5, t3, 1);
                                lbu(t4, t3, 2);
                                lbu(t3, t3, 3);
                                sb(t6, a3, 20);
                                sb(t5, a3, 21);
                                sb(t4, a3, 22);
                                sb(t3, a3, 23);
                                lbu(t3, v0, 6);
                                t3 = sll(t3, 2);
                                t3 = addu(a2, t3);
                                lbu(t6, t3, 0);
                                lbu(t5, t3, 1);
                                lbu(t4, t3, 2);
                                lbu(t3, t3, 3);
                                sb(t6, a3, 24);
                                sb(t5, a3, 25);
                                sb(t4, a3, 26);
                                sb(t3, a3, 27);
                                lbu(v0, v0, 7);
                                v0 = sll(v0, 2);
                                v0 = addu(a2, v0);
                                lbu(t5, v0, 0);
                                lbu(t4, v0, 1);
                                lbu(t3, v0, 2);
                                lbu(v0, v0, 3);
                                sb(t5, a3, 28);
                                sb(t4, a3, 29);
                                sb(t3, a3, 30);
                                sb(v0, a3, 31);
                                a3 = addiu(a3, 32);
                                if (t2 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004cd51c
                            charge(ctx, 1);
                        }
                    }
                    // 0x004cd520
                    charge(ctx, 3);
                    at = slt(t0, s1);
                    if (at != 0) {
                        // 0x004cd52c
                        charge(ctx, 3);
                        v0 = sll(t0, 2);
                        t5 = addu(s3, v0);
                        for (;;) {
                            // 0x004cd538
                            charge(ctx, 16);
                            v0 = addu(s2, t0);
                            lbu(a3, v0, 0);
                            t0 = addiu(t0, 1);
                            a3 = sll(a3, 2);
                            v0 = slt(t0, s1);
                            a3 = addu(a2, a3);
                            lbu(t4, a3, 0);
                            lbu(t3, a3, 1);
                            lbu(t2, a3, 2);
                            lbu(a3, a3, 3);
                            sb(t4, t5, 0);
                            sb(t3, t5, 1);
                            sb(t2, t5, 2);
                            sb(a3, t5, 3);
                            t5 = addiu(t5, 4);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                }
                // 0x004cd578
                charge(ctx, 6);
                lw(a3, s5, 16);
                a1 = addiu(a1, 1);
                s2 = addu(s2, t1);
                v0 = slt(a1, s0);
                s3 = addu(s3, a3);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004cd590
        charge(ctx, 2);
        s4 = 1;
        goto L_004cd5b8;
    }
L_004cd598:
    charge(ctx, 1);
    v1 = 1;
    goto L_004cd59c;
L_004cd5b8:
    charge(ctx, 2);
    v0 = s4;
    // 0x004cd5f4
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// sub_4CD940 [RwImageGammaCorrect] -- gamma-corrects an image through the module's gamma table (+12): a 32-bit image's
//   RGB per pixel (alpha kept), a 4 / 8-bit image's palette; no pixels or another depth is an error (0x80000016 /
//   0x80000009); the image, or 0
// 0x004CD940 sub_4CD940 -- 520 bytes; frame 0x30: ra sp+0x0
void sub_4CD940(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cd940
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 32;
    sd(ra, sp, 0x0);
    lw(v1, a0, 12);
    if (v1 == v0) {
        // 0x004cd9fc
        charge(ctx, 4);
        lw(t3, a0, 20);
        lw(a1, a0, 8);
        lw(t2, a0, 4);
        if (t3 == 0) {
            // 0x004cdaf8
            charge(ctx, 10);
            v1 = 1;
            v0 = lui(0x8000);
            sw(v1, sp, 0x20);
            a0 = v0 | 0x16;
            jal(ctx, 0x4CDB04u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x24);
            a0 = addiu(sp, 0x20);
            jal(ctx, 0x4CDB10u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        } else {
            // 0x004cda0c
            charge(ctx, 3);
            at = slt(0, a1);
            t1 = 0;
            if (at != 0) {
                // 0x004cda18
                charge(ctx, 3);
                v1 = 0x960000;
                v0 = addiu(t2, -1);
                v1 = addiu(v1, 112);  // &0x960070
                for (;;) {
                    // 0x004cda24
                    charge(ctx, 7);
                    lw(t4, gp, -17336);  // 0x7CE938
                    a3 = t3;
                    t0 = t3;
                    a2 = v0;
                    t4 = addu(v1, t4);
                    t6 = addiu(t4, 12);
                    if (t2 == 0) {
                        // 0x004cdb20
                        charge(ctx, 1);
                        lw(a3, a0, 16);
                    } else {
                        for (;;) {
                            // 0x004cda40
                            charge(ctx, 19);
                            lbu(t5, a3, 0);
                            t4 = a2;
                            a2 = addiu(a2, -1);
                            t5 = addu(t6, t5);
                            lbu(t5, t5, 0);
                            sb(t5, t0, 0);
                            lbu(t5, a3, 1);
                            t5 = addu(t6, t5);
                            lbu(t5, t5, 0);
                            sb(t5, t0, 1);
                            lbu(t5, a3, 2);
                            t5 = addu(t6, t5);
                            lbu(t5, t5, 0);
                            sb(t5, t0, 2);
                            lbu(t5, a3, 3);
                            sb(t5, t0, 3);
                            a3 = addiu(a3, 4);
                            t0 = addiu(t0, 4);
                            if (t4 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004cda8c
                        charge(ctx, 2);
                        lw(a3, a0, 16);
                    }
                    // 0x004cdb24
                    charge(ctx, 4);
                    t1 = addiu(t1, 1);
                    a2 = slt(t1, a1);
                    t3 = addu(t3, a3);
                    if (a2 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004cdb34
                charge(ctx, 2);
                backedge(ctx);
            }
        L_004cdac0:
            charge(ctx, 1);
            lw(v1, a0, 0);
        L_004cdac4:
            charge(ctx, 4);
            v0 = a0;
            v1 = v1 | 0x2;
            sw(v1, a0, 0);
        }
    } else {
        // 0x004cd958
        charge(ctx, 3);
        v0 = 8;
        if (v1 != v0) {
            // 0x004cd964
            charge(ctx, 3);
            v0 = 4;
            if (v1 == v0) {
                goto L_004cd978;
            }
            // 0x004cd970
            charge(ctx, 2);
            // 0x004cda98
            charge(ctx, 10);
            v0 = 1;
            sw(v0, sp, 0x18);
            v0 = lui(0x8000);
            a0 = v0 | 0x8;
            jal(ctx, 0x4CDAA4u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x1C);
            a0 = addiu(sp, 0x18);
            jal(ctx, 0x4CDAB0u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
            // 0x004cdb3c (the shared epilogue, written out on this path)
            charge(ctx, 3);
            ld(ra, sp, 0x0);
            sp = addiu(sp, 0x30);
            return;
        }
    L_004cd978:
        charge(ctx, 4);
        lw(t0, a0, 24);
        v0 = 1;
        a2 = sllv(v0, v1);
        if (t0 != 0) {
            // 0x004cd988
            charge(ctx, 8);
            lw(v1, gp, -17336);  // 0x7CE938
            v0 = 0x960000;
            v0 = addiu(v0, 112);  // &0x960070
            t1 = t0;
            a3 = addiu(a2, -1);
            v0 = addu(v0, v1);
            a1 = addiu(v0, 12);
            if (a2 == 0) {
                goto L_004cdac0;
            }
            for (;;) {
                // 0x004cd9a8
                charge(ctx, 19);
                lbu(v1, t0, 0);
                v0 = a3;
                a3 = addiu(a3, -1);
                v1 = addu(a1, v1);
                lbu(v1, v1, 0);
                sb(v1, t1, 0);
                lbu(v1, t0, 1);
                v1 = addu(a1, v1);
                lbu(v1, v1, 0);
                sb(v1, t1, 1);
                lbu(v1, t0, 2);
                v1 = addu(a1, v1);
                lbu(v1, v1, 0);
                sb(v1, t1, 2);
                lbu(v1, t0, 3);
                sb(v1, t1, 3);
                t0 = addiu(t0, 4);
                t1 = addiu(t1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004cd9f4
            charge(ctx, 2);
            lw(v1, a0, 0);
            goto L_004cdac4;
        }
        // 0x004cdad4
        charge(ctx, 9);
        sw(v0, sp, 0x28);
        v0 = lui(0x8000);
        a0 = v0 | 0x16;
        jal(ctx, 0x4CDADCu, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x2C);
        a0 = addiu(sp, 0x28);
        jal(ctx, 0x4CDAE8u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x004cdb3c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4CDB50 [RwImageSetGamma] -- sets the image gamma ($f12, kept at +524) and rebuilds the two 256-entry tables (+12
//   gamma, +268 inverse): entry i = 255 * (i / 255)^g + 0.5 (powf), entry 0 = 0; 1
// 0x004CDB50 sub_4CDB50 -- 288 bytes; frame 0x30: ra sp+0x20, s0 sp+0x10 (sq), f22 sp+0x8, f21 sp+0x4, f20 sp+0x0
void sub_4CDB50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f13{ctx, 13}, f20{ctx, 20}, f21{ctx, 21}, f22{ctx, 22};
    // 0x004cdb50
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = 0x3F800000;
    sd(ra, sp, 0x20);
    v1 = 0x960000;
    sq(s0, sp, 0x10);
    mtc1(v0, f0);
    swc1(f22, sp, 0x8);
    v1 = addiu(v1, 112);  // &0x960070
    swc1(f21, sp, 0x4);
    s0 = 1;
    swc1(f20, sp, 0x0);
    mov_s(f21, f12);
    lw(a0, gp, -17336);  // 0x7CE938
    div_s(f20, f0, f21);
    v0 = addu(v1, a0);
    swc1(f21, v0, 524);
    sb(zero, v0, 12);
    sb(zero, v0, 268);
    for (;;) {
        // 0x004cdb98
        charge(ctx, 46);
        mtc1(s0, f1);
        v0 = 0x437F0000;
        mtc1(v0, f0);
        cvt_s_w(f1, f1);
        div_s(f22, f1, f0);
        mov_s(f13, f20);
        mov_s(f12, f22);
        jal(ctx, 0x4CDBBCu, gen::fn_powf_0052ea48);
        v0 = 0x437F0000;
        lw(v1, gp, -17336);  // 0x7CE938
        mtc1(v0, f2);
        mov_s(f12, f22);
        mul_s(f0, f2, f0);
        v0 = 0x3F000000;
        mtc1(v0, f1);
        mov_s(f13, f21);
        add_s(f0, f1, f0);
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070
        v0 = addu(v0, v1);
        v0 = addu(s0, v0);
        cvt_w_s(f0, f0);
        mfc1(v1, f0);
        link(ctx, 0x4CDC00u);  // $ra first: the delay slot below depends on it
        sb(v1, v0, 12);
        call(ctx, gen::fn_powf_0052ea48);
        v1 = 0x437F0000;
        v0 = 0x3F000000;
        mtc1(v1, f2);
        mtc1(v0, f1);
        mul_s(f0, f2, f0);
        lw(v1, gp, -17336);  // 0x7CE938
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070
        add_s(f0, f1, f0);
        v0 = addu(v0, v1);
        v1 = addu(s0, v0);
        s0 = addiu(s0, 1);
        cvt_w_s(f0, f0);
        v0 = slti(s0, 256);
        mfc1(a0, f0);
        sb(a0, v1, 268);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004cdc50
    charge(ctx, 8);
    ld(ra, sp, 0x20);
    lwc1(f22, sp, 0x8);
    lq(s0, sp, 0x10);
    lwc1(f21, sp, 0x4);
    lwc1(f20, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x30);
}

// sub_4CEE30 [imageResampleTo32] -- makes a 32-bit image of $a1 x $a2 from an image: the destination allocated
//   (sub_4CBE00 / sub_4CBF20), a non-32-bit source first copied into a 32-bit one (sub_4CD620), then resampled into it
//   (sub_4CEC10); the temporary images destroyed; the new image, or 0
// 0x004CEE30 sub_4CEE30 -- 376 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CEE30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cee30
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    s2 = a0;
    sq(s1, sp, 0x10);
    a0 = a1;
    sq(s0, sp, 0x0);
    a1 = a2;
    a2 = 32;
    jal(ctx, 0x4CEE50u, gen::fn_sub_4CBE00_004cbe00);
    s1 = v0;
    if (s1 == 0) {
        // 0x004cef44
        charge(ctx, 2);
        v0 = 0;
    L_004cef90:
        charge(ctx, 1);
        ld(ra, sp, 0x30);
    } else {
        // 0x004cee64
        charge(ctx, 4);
        a0 = s1;
        jal(ctx, 0x4CEE64u, gen::fn_sub_4CBF20_004cbf20);
        if (v0 == 0) {
            // 0x004cef4c
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x4CEF4Cu, gen::fn_sub_4CBEB0_004cbeb0);
            v0 = 0;
            goto L_004cef90;
        }
        // 0x004cee74
        charge(ctx, 4);
        lw(v0, s2, rw9::image::kDepth);
        a2 = 32;
        if (v0 != a2) {
            // 0x004cee84
            charge(ctx, 6);
            lw(a1, s2, rw9::image::kHeight);
            link(ctx, 0x4CEE88u);  // $ra first: the delay slot below depends on it
            lw(a0, s2, rw9::image::kWidth);
            call(ctx, gen::fn_sub_4CBE00_004cbe00);
            s0 = v0;
            if (s0 == 0) {
                // 0x004cef5c
                charge(ctx, 6);
                a0 = s1;
                jal(ctx, 0x4CEF5Cu, gen::fn_sub_4CC050_004cc050);
                a0 = s1;
                jal(ctx, 0x4CEF64u, gen::fn_sub_4CBEB0_004cbeb0);
                v0 = 0;
                goto L_004cef90;
            }
            // 0x004cee9c
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x4CEE9Cu, gen::fn_sub_4CBF20_004cbf20);
            if (v0 == 0) {
                // 0x004cef74
                charge(ctx, 7);
                a0 = s0;
                jal(ctx, 0x4CEF74u, gen::fn_sub_4CBEB0_004cbeb0);
                a0 = s1;
                jal(ctx, 0x4CEF7Cu, gen::fn_sub_4CC050_004cc050);
                a0 = s1;
                jal(ctx, 0x4CEF84u, gen::fn_sub_4CBEB0_004cbeb0);
                v0 = 0;
                goto L_004cef90;
            }
            // 0x004ceeac
            charge(ctx, 8);
            a1 = s2;
            a0 = s0;
            jal(ctx, 0x4CEEB0u, gen::fn_sub_4CD620_004cd620);
            a0 = s1;
            a1 = s0;
            jal(ctx, 0x4CEEBCu, gen::fn_sub_4CEC10_004cec10);
            if (v0 != 0) {
                // 0x004ceef4
                charge(ctx, 6);
                a0 = s0;
                jal(ctx, 0x4CEEF4u, gen::fn_sub_4CC050_004cc050);
                a0 = s0;
                jal(ctx, 0x4CEEFCu, gen::fn_sub_4CBEB0_004cbeb0);
                v0 = s1;
                goto L_004cef3c;
            }
            // 0x004ceecc
            charge(ctx, 10);
            a0 = s0;
            jal(ctx, 0x4CEECCu, gen::fn_sub_4CC050_004cc050);
            a0 = s0;
            jal(ctx, 0x4CEED4u, gen::fn_sub_4CBEB0_004cbeb0);
            a0 = s1;
            jal(ctx, 0x4CEEDCu, gen::fn_sub_4CC050_004cc050);
            a0 = s1;
            jal(ctx, 0x4CEEE4u, gen::fn_sub_4CBEB0_004cbeb0);
            v0 = 0;
            goto L_004cef90;
        }
        // 0x004cef0c
        charge(ctx, 5);
        a1 = s2;
        a0 = s1;
        jal(ctx, 0x4CEF10u, gen::fn_sub_4CEC10_004cec10);
        if (v0 == 0) {
            // 0x004cef20
            charge(ctx, 6);
            a0 = s1;
            jal(ctx, 0x4CEF20u, gen::fn_sub_4CC050_004cc050);
            a0 = s1;
            jal(ctx, 0x4CEF28u, gen::fn_sub_4CBEB0_004cbeb0);
            v0 = 0;
            goto L_004cef90;
        }
        // 0x004cef38
        charge(ctx, 1);
        v0 = s1;
    L_004cef3c:
        charge(ctx, 2);
        ld(ra, sp, 0x30);
    }
    // 0x004cef94 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4CF690 [imagePalettise] -- reduces *$a0 to a palette of 2^$a1 colours: the quantiser initialised (sub_4D3FC0),
//   fed the image (sub_4D22F0), the palette made (sub_4D3300), a new image of that depth with the indices (sub_4D3800)
//   and palette, the old image destroyed and *$a0 replaced, the quantiser freed (sub_4D41E0); 1, or 0
// 0x004CF690 sub_4CF690 -- 248 bytes; frame 0x4450: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CF690(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x004cf690
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x4450);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = addiu(sp, 0x40);
    jal(ctx, 0x4CF6ACu, gen::fn_sub_4D3FC0_004d3fc0);
    if (v0 != 0) {
        // 0x004cf6c4
        charge(ctx, 20);
        lw(a1, s0, 0);
        v0 = 0x3F800000;
        mtc1(v0, f12);
        a0 = addiu(sp, 0x40);
        jal(ctx, 0x4CF6D0u, gen::fn_sub_4D22F0_004d22f0);
        v0 = 1;
        a0 = addiu(sp, 0x4050);
        s1 = dsllv(v0, s2);
        a2 = addiu(sp, 0x40);
        a1 = dsll32(s1, 0);
        a1 = dsra32(a1, 0);
        jal(ctx, 0x4CF6ECu, gen::fn_sub_4D3300_004d3300);
        lw(v0, s0, 0);
        lw(a0, v0, 4);
        lw(a1, v0, 8);
        a2 = s2;
        jal(ctx, 0x4CF700u, gen::fn_sub_4CBE00_004cbe00);
        s2 = v0;
        if (s2 == 0) {
            // 0x004cf76c
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x004cf714
            charge(ctx, 22);
            a0 = s2;
            jal(ctx, 0x4CF714u, gen::fn_sub_4CBF20_004cbf20);
            lw(a0, s2, 20);
            a3 = 0;
            lw(a1, s2, 16);
            lw(a2, s2, 12);
            lw(t1, s0, 0);
            t0 = addiu(sp, 0x40);
            jal(ctx, 0x4CF730u, gen::fn_sub_4D3800_004d3800);
            lw(a0, s2, 24);
            v0 = dsll(s1, 2);
            a2 = dsll32(v0, 0);
            a1 = addiu(sp, 0x4050);
            a2 = dsra32(a2, 0);
            jal(ctx, 0x4CF748u, gen::fn_memcpy_00521250);
            link(ctx, 0x4CF750u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, 0);
            call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
            a0 = addiu(sp, 0x40);
            link(ctx, 0x4CF75Cu);  // $ra first: the delay slot below depends on it
            sw(s2, s0, 0);
            call(ctx, gen::fn_sub_4D41E0_004d41e0);
            v0 = 1;
        }
    } else {
        // 0x004cf6bc
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004cf770 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x4450);
}

// sub_4CF790 [imagesPalettiseShared] -- gives a mip chain of $a3 images one palette of 2^$t0 colours in $a0: when every
//   level already carries the same palette it is copied; else all levels are fed to one quantiser, the palette made, and
//   each level replaced by a palettised image pointing at $a0 (the original $a1 kept); 1, or 0
// 0x004CF790 sub_4CF790 -- 544 bytes; frame 0x40A0: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CF790(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x004cf790
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40A0);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    s7 = a1;
    sq(s5, sp, 0x50);
    s6 = t0;
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a3;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a3, a2, 0);
    lw(a1, a3, 24);
    s4 = a2;
    if (a1 != 0) {
        // 0x004cf7d8
        charge(ctx, 3);
        at = slti(s3, 2);
        t3 = 1;
        if (at == 0) {
            // 0x004cf7e4
            charge(ctx, 2);
            a2 = sllv(t3, s6);
            v1 = 64;
            for (;;) {
                // 0x004cf7ec
                charge(ctx, 5);
                v0 = sll(t3, 2);
                v0 = addu(s4, v0);
                lw(v0, v0, 0);
                lw(t1, v0, 24);
                if (a1 == 0) {
                    goto L_004cf860;
                }
                // 0x004cf800
                charge(ctx, 2);
                if (t1 == 0) {
                    goto L_004cf860;
                }
                // 0x004cf808
                charge(ctx, 3);
                at = slt(0, a2);
                t2 = 0;
                if (at != 0) {
                    // 0x004cf814
                    charge(ctx, 1);
                    t0 = a1;
                    for (;;) {
                        // 0x004cf818
                        charge(ctx, 4);
                        lw(a0, t0, 0);
                        lw(v0, t1, 0);
                        if (a0 != v0) {
                            goto L_004cf828_8;
                        }
                        // 0x004cf830
                        charge(ctx, 5);
                        t2 = addiu(t2, 1);
                        v0 = slt(t2, a2);
                        t1 = addiu(t1, 4);
                        t0 = addiu(t0, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004cf844
                    charge(ctx, 1);
                }
            L_004cf848:
                charge(ctx, 4);
                t3 = addiu(t3, 1);
                v0 = slt(t3, s3);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004cf858
            charge(ctx, 2);
        }
    L_004cf864:
        charge(ctx, 2);
        if (t3 != s3) {
            goto L_004cf894;
        }
        // 0x004cf86c
        charge(ctx, 10);
        lw(v0, a3, 12);
        v1 = 1;
        a0 = s5;
        v0 = dsllv(v1, v0);
        v0 = dsll(v0, 2);
        a2 = dsll32(v0, 0);
        a2 = dsra32(a2, 0);
        jal(ctx, 0x4CF884u, gen::fn_memcpy_00521250);
        v0 = 1;
        // 0x004cf984 (the shared epilogue, written out on this path)
        charge(ctx, 11);
        ld(ra, sp, 0x80);
        lq(s7, sp, 0x70);
        lq(s6, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40A0);
        return;
    }
L_004cf894:
    charge(ctx, 4);
    a0 = addiu(sp, 0x90);
    jal(ctx, 0x4CF894u, gen::fn_sub_4D3FC0_004d3fc0);
    if (v0 == 0) {
        // 0x004cf8e0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004cf8a4
        charge(ctx, 3);
        at = slt(0, s3);
        s0 = 0;
        if (at == 0) {
            // 0x004cf8e8
            charge(ctx, 1);
            v0 = 1;
        } else {
            // 0x004cf8b0
            charge(ctx, 1);
            s1 = s4;
            for (;;) {
                // 0x004cf8b4
                charge(ctx, 9);
                lw(a1, s1, 0);
                v0 = 0x3F800000;
                mtc1(v0, f12);
                a0 = addiu(sp, 0x90);
                jal(ctx, 0x4CF8C0u, gen::fn_sub_4D22F0_004d22f0);
                s0 = addiu(s0, 1);
                v0 = slt(s0, s3);
                s1 = addiu(s1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004cf8d8
            charge(ctx, 2);
            v0 = 1;
        }
        // 0x004cf8ec
        charge(ctx, 7);
        a0 = s5;
        a1 = sllv(v0, s6);
        a2 = addiu(sp, 0x90);
        jal(ctx, 0x4CF8F4u, gen::fn_sub_4D3300_004d3300);
        at = slt(0, s3);
        s1 = 0;
        if (at != 0) {
            for (;;) {
                // 0x004cf908
                charge(ctx, 8);
                lw(s0, s4, 0);
                lw(a0, s0, 4);
                lw(a1, s0, 8);
                a2 = s6;
                jal(ctx, 0x4CF914u, gen::fn_sub_4CBE00_004cbe00);
                s2 = v0;
                if (s2 == 0) {
                    goto L_004cf980;
                }
                // 0x004cf928
                charge(ctx, 12);
                a0 = s2;
                jal(ctx, 0x4CF928u, gen::fn_sub_4CBF20_004cbf20);
                lw(a0, s2, 20);
                a3 = 0;
                lw(a1, s2, 16);
                t0 = addiu(sp, 0x90);
                lw(a2, s2, 12);
                t1 = s0;
                jal(ctx, 0x4CF944u, gen::fn_sub_4D3800_004d3800);
                sw(s5, s2, 24);
                sw(s2, s4, 0);
                if (s0 != s7) {
                    // 0x004cf958
                    charge(ctx, 2);
                    a0 = s0;
                    jal(ctx, 0x4CF958u, gen::fn_sub_4CBEB0_004cbeb0);
                }
                // 0x004cf960
                charge(ctx, 4);
                s1 = addiu(s1, 1);
                v0 = slt(s1, s3);
                s4 = addiu(s4, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004cf970
        charge(ctx, 4);
        a0 = addiu(sp, 0x90);
        jal(ctx, 0x4CF970u, gen::fn_sub_4D41E0_004d41e0);
        v0 = 1;
    }
    // 0x004cf984 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40A0);
    return;
L_004cf828_8:
    charge(ctx, 2);
    t3 = v1;
    goto L_004cf848;
L_004cf860:
    charge(ctx, 1);
    t3 = 64;
    goto L_004cf864;
L_004cf980:
    charge(ctx, 1);
    v0 = 0;
    // 0x004cf984 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40A0);
}

// sub_4CF9B0 [textureReadImage] -- reads the image for a texture raster: the name and mask (256 characters, error
//   0x8000001E when longer) with their found extensions (sub_4CCD20), the masked image (RwImageReadMaskedImage), the
//   raster format chosen when not given (sub_4CDD50), the image resampled to the raster size (via a 32-bit copy) and
//   palettised for 4 / 8-bit rasters (sub_4CF690); the image, or 0
// 0x004CF9B0 sub_4CF9B0 -- 888 bytes; frame 0x2C0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CF9B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004cf9b0
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x2C0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    fp = t2;
    sq(s6, sp, 0x60);
    s7 = t1;
    sq(s5, sp, 0x50);
    s6 = a2;
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    s3 = a3;
    sq(s1, sp, 0x10);
    s2 = t0;
    s1 = 0x960000;
    sq(s0, sp, 0x0);
    s1 = addiu(s1, 320);  // &0x960140
    a0 = addiu(sp, 0x1A0);
    lw(v0, s1, 0);  // 0x960140
    a1 = s5;
    a2 = 256;
    jalr(ctx, 0x4CFA0Cu, v0.u());
    s0 = 0x960000;
    s0 = addiu(s0, 356);  // &0x960164
    lw(v0, s0, 0);  // 0x960164
    a0 = s5;
    jalr(ctx, 0x4CFA20u, v0.u());
    at = sltiu(v0, 256);
    if (at == 0) {
        // 0x004cfb88
        charge(ctx, 14);
        lb(t0, s5, 255);
        v0 = 1;
        sw(v0, sp, 0x2B0);
        a1 = s5;
        v0 = lui(0x8000);
        a2 = 256;
        a0 = v0 | 0x1E;
        a3 = 255;
        jal(ctx, 0x4CFBA4u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x2B4);
        a0 = addiu(sp, 0x2B0);
        jal(ctx, 0x4CFBB0u, gen::fn_sub_4C1C50_004c1c50);
        sb(zero, sp, 0x29F);
        backedge(ctx);
    }
    // 0x004cfa34
    charge(ctx, 4);
    a0 = s5;
    jal(ctx, 0x4CFA34u, gen::fn_sub_4CCD20_004ccd20);
    if (v0 != 0) {
        // 0x004cfa44
        charge(ctx, 5);
        a1 = v0;
        v0 = 0x960000;
        lw(v0, v0, 324);  // 0x960144
        a0 = addiu(sp, 0x1A0);
        jalr(ctx, 0x4CFA50u, v0.u());
    }
    // 0x004cfa58
    charge(ctx, 2);
    sb(zero, sp, 0xA0);
    if (s4 != 0) {
        // 0x004cfa60
        charge(ctx, 3);
        lb(v0, s4, 0);
        if (v0 != 0) {
            // 0x004cfa6c
            charge(ctx, 11);
            lw(v0, s1, 0);
            a0 = addiu(sp, 0xA0);
            a1 = s4;
            a2 = 256;
            jalr(ctx, 0x4CFA78u, v0.u());
            lw(v0, s0, 0);
            a0 = s4;
            jalr(ctx, 0x4CFA84u, v0.u());
            at = sltiu(v0, 256);
            if (at == 0) {
                // 0x004cfbc0
                charge(ctx, 14);
                lb(t0, s4, 255);
                v0 = 1;
                sw(v0, sp, 0x2A8);
                a1 = s4;
                v0 = lui(0x8000);
                a2 = 256;
                a0 = v0 | 0x1E;
                a3 = 255;
                jal(ctx, 0x4CFBDCu, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x2AC);
                a0 = addiu(sp, 0x2A8);
                jal(ctx, 0x4CFBE8u, gen::fn_sub_4C1C50_004c1c50);
                sb(zero, sp, 0x19F);
                backedge(ctx);
            }
            // 0x004cfa98
            charge(ctx, 4);
            a0 = s4;
            jal(ctx, 0x4CFA98u, gen::fn_sub_4CCD20_004ccd20);
            if (v0 != 0) {
                // 0x004cfaa8
                charge(ctx, 5);
                a1 = v0;
                v0 = 0x960000;
                lw(v0, v0, 324);  // 0x960144
                a0 = addiu(sp, 0xA0);
                jalr(ctx, 0x4CFAB4u, v0.u());
            }
        }
    }
    // 0x004cfabc
    charge(ctx, 5);
    a0 = addiu(sp, 0x1A0);
    a1 = addiu(sp, 0xA0);
    jal(ctx, 0x4CFAC0u, gen::fn_sub_4CCF10_004ccf10);
    sw(v0, sp, 0x2BC);
    if (v0 == 0) {
        // 0x004cfbf8
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004cfad0
        charge(ctx, 3);
        lw(v1, s3, 0);
        if (v1 != 0) {
            // 0x004cfadc
            charge(ctx, 3);
            lw(v1, s2, 0);
            if (v1 == 0) {
                goto L_004cfc00;
            }
        L_004cfae8:
            charge(ctx, 5);
            lw(a1, sp, 0x2BC);
            lw(v0, s3, 0);
            lw(a0, a1, 4);
            if (a0 == v0) {
                // 0x004cfafc
                charge(ctx, 4);
                lw(v1, a1, 8);
                lw(v0, s2, 0);
                if (v1 != v0) {
                    goto L_004cfb0c;
                }
            L_004cfb80:
                charge(ctx, 2);
                lw(v0, sp, 0x2BC);
                // 0x004cfcf8 (the shared epilogue, written out on this path)
                charge(ctx, 12);
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
                sp = addiu(sp, 0x2C0);
                return;
            }
        L_004cfb0c:
            charge(ctx, 4);
            lw(s1, a1, 12);
            a2 = 32;
            if (s1 == a2) {
                // 0x004cfb1c
                charge(ctx, 1);
                lw(a0, s3, 0);
                goto L_004cfb20;
            }
            // 0x004cfc54
            charge(ctx, 5);
            lw(s0, sp, 0x2BC);
            link(ctx, 0x4CFC58u);  // $ra first: the delay slot below depends on it
            lw(a1, s0, 8);
            call(ctx, gen::fn_sub_4CBE00_004cbe00);
            sw(v0, sp, 0x2BC);
            if (v0 == 0) {
                // 0x004cfc94
                charge(ctx, 4);
                a0 = s0;
                jal(ctx, 0x4CFC94u, gen::fn_sub_4CBEB0_004cbeb0);
                v0 = 0;
            } else {
                // 0x004cfc68
                charge(ctx, 4);
                a0 = v0;
                jal(ctx, 0x4CFC68u, gen::fn_sub_4CBF20_004cbf20);
                if (v0 == 0) {
                    // 0x004cfca4
                    charge(ctx, 6);
                    link(ctx, 0x4CFCA4u);  // $ra first: the delay slot below depends on it
                    lw(a0, sp, 0x2BC);
                    call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                    a0 = s0;
                    jal(ctx, 0x4CFCACu, gen::fn_sub_4CBEB0_004cbeb0);
                    v0 = 0;
                } else {
                    // 0x004cfc78
                    charge(ctx, 7);
                    lw(a0, sp, 0x2BC);
                    a1 = s0;
                    jal(ctx, 0x4CFC7Cu, gen::fn_sub_4CD620_004cd620);
                    a0 = s0;
                    jal(ctx, 0x4CFC84u, gen::fn_sub_4CBEB0_004cbeb0);
                    lw(a0, s3, 0);
                    backedge(ctx);
                L_004cfb20:
                    charge(ctx, 6);
                    lw(a1, s2, 0);
                    a2 = 32;
                    jal(ctx, 0x4CFB24u, gen::fn_sub_4CBE00_004cbe00);
                    s0 = v0;
                    if (s0 == 0) {
                        // 0x004cfcbc
                        charge(ctx, 4);
                        link(ctx, 0x4CFCBCu);  // $ra first: the delay slot below depends on it
                        lw(a0, sp, 0x2BC);
                        call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                        v0 = 0;
                    } else {
                        // 0x004cfb38
                        charge(ctx, 4);
                        a0 = s0;
                        jal(ctx, 0x4CFB38u, gen::fn_sub_4CBF20_004cbf20);
                        if (v0 != 0) {
                            // 0x004cfb48
                            charge(ctx, 8);
                            lw(a1, sp, 0x2BC);
                            a0 = s0;
                            jal(ctx, 0x4CFB4Cu, gen::fn_sub_4CEC10_004cec10);
                            link(ctx, 0x4CFB54u);  // $ra first: the delay slot below depends on it
                            lw(a0, sp, 0x2BC);
                            call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                            v0 = 4;
                            sw(s0, sp, 0x2BC);
                            if (s1 == v0) {
                                // 0x004cfce4
                                charge(ctx, 5);
                                a1 = s1;
                                a0 = addiu(sp, 0x2BC);
                                jal(ctx, 0x4CFCE8u, gen::fn_sub_4CF690_004cf690);
                                backedge(ctx);
                            } else {
                                // 0x004cfb68
                                charge(ctx, 3);
                                v0 = 8;
                                if (s1 == v0) {
                                    // 0x004cfb74
                                    charge(ctx, 3);
                                    a1 = s1;
                                    a0 = addiu(sp, 0x2BC);
                                    jal(ctx, 0x4CFB78u, gen::fn_sub_4CF690_004cf690);
                                }
                            }
                            goto L_004cfb80;
                        }
                        // 0x004cfccc
                        charge(ctx, 6);
                        a0 = s0;
                        jal(ctx, 0x4CFCCCu, gen::fn_sub_4CBEB0_004cbeb0);
                        link(ctx, 0x4CFCD4u);  // $ra first: the delay slot below depends on it
                        lw(a0, sp, 0x2BC);
                        call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                        v0 = 0;
                    }
                }
            }
            // 0x004cfcf8 (the shared epilogue, written out on this path)
            charge(ctx, 12);
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
            sp = addiu(sp, 0x2C0);
            return;
        }
    L_004cfc00:
        charge(ctx, 9);
        a1 = s6;
        t0 = s7;
        t1 = fp;
        a0 = v0;
        a2 = s3;
        a3 = s2;
        jal(ctx, 0x4CFC14u, gen::fn_sub_4CDD50_004cdd50);
        if (v0 != 0) {
            backedge(ctx);
            goto L_004cfae8;
        }
        // 0x004cfc24
        charge(ctx, 12);
        link(ctx, 0x4CFC24u);  // $ra first: the delay slot below depends on it
        lw(a0, sp, 0x2BC);
        call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
        v1 = 1;
        v0 = lui(0x8000);
        sw(v1, sp, 0x2A0);
        a0 = v0 | 0x9;
        jal(ctx, 0x4CFC38u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x2A4);
        a0 = addiu(sp, 0x2A0);
        jal(ctx, 0x4CFC44u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x004cfcf8 (the shared epilogue, written out on this path)
    charge(ctx, 12);
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
    sp = addiu(sp, 0x2C0);
}

// sub_4CFD30 [textureReadDefault] -- the default texture reader without mipmaps: the names copied, the level-name hook
//   (sub_4D1210), the image (sub_4CF9B0) for a 4-bit-capable raster, the raster created (RwRasterCreate), a palettised
//   raster's palette made (sub_4CF790), the image gamma-corrected and copied into the raster (sub_4CDCE0), the texture
//   (sub_4D0E40) with its names; the texture, or 0
// 0x004CFD30 sub_4CFD30 -- 672 bytes; frame 0x680: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4CFD30(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cfd30
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x680);
    a2 = 256;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    s1 = 0x960000;
    sq(s0, sp, 0x0);
    s1 = addiu(s1, 320);  // &0x960140
    a0 = addiu(sp, 0x150);
    lw(v0, s1, 0);  // 0x960140
    a1 = s3;
    jalr(ctx, 0x4CFD64u, v0.u());
    s0 = 0x960000;
    s0 = addiu(s0, 356);  // &0x960164
    lw(v0, s0, 0);  // 0x960164
    a0 = s3;
    jalr(ctx, 0x4CFD78u, v0.u());
    at = sltiu(v0, 256);
    if (at == 0) {
        // 0x004cff28
        charge(ctx, 14);
        lb(t0, s3, 255);
        v0 = 1;
        sw(v0, sp, 0x660);
        a1 = s3;
        v0 = lui(0x8000);
        a2 = 256;
        a0 = v0 | 0x1E;
        a3 = 255;
        jal(ctx, 0x4CFF44u, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x664);
        a0 = addiu(sp, 0x660);
        jal(ctx, 0x4CFF50u, gen::fn_sub_4C1C50_004c1c50);
        sb(zero, sp, 0x24F);
        backedge(ctx);
    }
    // 0x004cfd8c
    charge(ctx, 2);
    sb(zero, sp, 0x50);
    if (s2 != 0) {
        // 0x004cfd94
        charge(ctx, 3);
        lb(v0, s2, 0);
        if (v0 != 0) {
            // 0x004cfda0
            charge(ctx, 11);
            lw(v0, s1, 0);
            a0 = addiu(sp, 0x50);
            a1 = s2;
            a2 = 256;
            jalr(ctx, 0x4CFDACu, v0.u());
            lw(v0, s0, 0);
            a0 = s2;
            jalr(ctx, 0x4CFDB8u, v0.u());
            v0 = sltiu(v0, 256);
            if (v0 == 0) {
                // 0x004cfdcc
                charge(ctx, 13);
                lb(t0, s2, 255);
                v0 = 1;
                sw(v0, sp, 0x658);
                a1 = s2;
                v0 = lui(0x8000);
                a2 = 256;
                a0 = v0 | 0x1E;
                a3 = 255;
                jal(ctx, 0x4CFDE8u, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x65C);
                a0 = addiu(sp, 0x658);
                jal(ctx, 0x4CFDF4u, gen::fn_sub_4C1C50_004c1c50);
                sb(zero, sp, 0x14F);
            }
        }
    }
    // 0x004cfe00
    charge(ctx, 17);
    a0 = addiu(sp, 0x150);
    a1 = addiu(sp, 0x50);
    a2 = 0;
    a3 = 4;
    jal(ctx, 0x4CFE0Cu, gen::fn_sub_4D1210_004d1210);
    a0 = addiu(sp, 0x150);
    a1 = addiu(sp, 0x50);
    a2 = 4;
    a3 = addiu(sp, 0x678);
    t0 = addiu(sp, 0x674);
    t1 = addiu(sp, 0x670);
    t2 = addiu(sp, 0x66C);
    sw(zero, sp, 0x678);
    link(ctx, 0x4CFE34u);  // $ra first: the delay slot below depends on it
    sw(zero, sp, 0x674);
    call(ctx, gen::fn_sub_4CF9B0_004cf9b0);
    sw(v0, sp, 0x67C);
    if (v0 == 0) {
        // 0x004cff60
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004cfe44
        charge(ctx, 8);
        lw(a1, sp, 0x674);
        lw(a2, sp, 0x670);
        lw(a3, sp, 0x66C);
        link(ctx, 0x4CFE50u);  // $ra first: the delay slot below depends on it
        lw(a0, sp, 0x678);
        call(ctx, gen::fn_sub_4CE0F0_004ce0f0);
        s0 = v0;
        if (s0 == 0) {
            // 0x004cff68
            charge(ctx, 4);
            link(ctx, 0x4CFF68u);  // $ra first: the delay slot below depends on it
            lw(a0, sp, 0x67C);
            call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
            v0 = 0;
        } else {
            // 0x004cfe64
            charge(ctx, 5);
            lbu(v0, s0, 35);
            v1 = sll(v0, 8);
            v0 = v1 & 0x6000;
            if (v0 != 0) {
                // 0x004cfe78
                charge(ctx, 3);
                v0 = v1 & 0x4000;
                if (v0 == 0) {
                    // 0x004cfea4
                    charge(ctx, 7);
                    a0 = addiu(sp, 0x250);
                    a1 = 0;
                    a2 = addiu(sp, 0x67C);
                    a3 = 1;
                    t0 = 8;
                    jal(ctx, 0x4CFEB4u, gen::fn_sub_4CF790_004cf790);
                    lw(v0, sp, 0x67C);
                } else {
                    // 0x004cfe84
                    charge(ctx, 8);
                    a0 = addiu(sp, 0x250);
                    a1 = 0;
                    a2 = addiu(sp, 0x67C);
                    a3 = 1;
                    t0 = 4;
                    jal(ctx, 0x4CFE94u, gen::fn_sub_4CF790_004cf790);
                    lw(v0, sp, 0x67C);
                }
                // 0x004cfec0
                charge(ctx, 2);
                v1 = addiu(sp, 0x250);
                sw(v1, v0, 24);
            }
            // 0x004cfec8
            charge(ctx, 7);
            link(ctx, 0x4CFEC8u);  // $ra first: the delay slot below depends on it
            lw(a0, sp, 0x67C);
            call(ctx, gen::fn_sub_4CD940_004cd940);
            lw(a1, sp, 0x67C);
            a0 = s0;
            jal(ctx, 0x4CFED4u, gen::fn_sub_4CDCE0_004cdce0);
            if (v0 == 0) {
                // 0x004cff78
                charge(ctx, 6);
                a0 = s0;
                jal(ctx, 0x4CFF78u, gen::fn_sub_4CDE90_004cde90);
                link(ctx, 0x4CFF80u);  // $ra first: the delay slot below depends on it
                lw(a0, sp, 0x67C);
                call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                v0 = 0;
            } else {
                // 0x004cfee4
                charge(ctx, 7);
                link(ctx, 0x4CFEE4u);  // $ra first: the delay slot below depends on it
                lw(a0, sp, 0x67C);
                call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
                a0 = s0;
                jal(ctx, 0x4CFEECu, gen::fn_sub_4D0E40_004d0e40);
                s1 = v0;
                if (s1 == 0) {
                    // 0x004cff90
                    charge(ctx, 4);
                    a0 = s0;
                    jal(ctx, 0x4CFF90u, gen::fn_sub_4CDE90_004cde90);
                    v0 = 0;
                } else {
                    // 0x004cff00
                    charge(ctx, 5);
                    a1 = s3;
                    a0 = s1;
                    jal(ctx, 0x4CFF04u, gen::fn_sub_4D0FD0_004d0fd0);
                    if (s2 == 0) {
                        // 0x004cffa0
                        charge(ctx, 5);
                        a0 = s1;
                        a1 = addiu(gp, -20328);  // &0x7CDD88
                        jal(ctx, 0x4CFFA4u, gen::fn_sub_4D1070_004d1070);
                        backedge(ctx);
                    } else {
                        // 0x004cff14
                        charge(ctx, 3);
                        a1 = s2;
                        a0 = s1;
                        jal(ctx, 0x4CFF18u, gen::fn_sub_4D1070_004d1070);
                    }
                    // 0x004cff20
                    charge(ctx, 2);
                    v0 = s1;
                }
            }
        }
    }
    // 0x004cffb4 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x680);
}

// sub_4D05F0 [textureReadDefaultCB] -- the texture module's default read callback: the mipmapped reader (sub_4CFFD0)
//   when the module's mipmapping flag (+28) is set, else sub_4CFD30 (a tail call)
// 0x004D05F0 sub_4D05F0 -- 72 bytes; frame 0x10: ra sp+0x0
void sub_4D05F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d05f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x960000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, 112);  // &0x960070
    lw(v1, gp, -17312);  // 0x7CE950
    v0 = addu(v0, v1);
    lw(v0, v0, 28);
    if (v0 == 0) {
        // 0x004d0624
        charge(ctx, 3);
        jal(ctx, 0x4D0624u, gen::fn_sub_4CFD30_004cfd30);
        ld(ra, sp, 0x0);
    } else {
        // 0x004d0614
        charge(ctx, 4);
        jal(ctx, 0x4D0614u, gen::fn_sub_4CFFD0_004cffd0);
        ld(ra, sp, 0x0);
    }
    // 0x004d0630 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// sub_4D0640 [rasterSetImageMipmaps] -- fills a raster's mip levels from an image ($a1, or read back from the raster
//   when 0, sub_4CDC70; converted to 32-bit when needed): level 0 from it, each further level resampled from the previous
//   one at the locked level's size (sub_4CEE30), the levels palettised together for 4 / 8-bit rasters (sub_4CF790) or
//   gamma-corrected, each copied into its locked level (sub_4CDCE0); the raster's automatic-mipmap flag held off
//   meanwhile; the raster, or 0
// 0x004D0640 sub_4D0640 -- 908 bytes; frame 0x4B0: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4D0640(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d0640
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x4B0);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(v1, a0, 12);
    lw(a1, a0, 16);
    s2 = a0;
    if (s1 == 0) {
        // 0x004d07c0
        charge(ctx, 5);
        a0 = v1;
        a2 = 32;
        jal(ctx, 0x4D07C4u, gen::fn_sub_4CBE00_004cbe00);
        sw(v0, sp, 0x470);
        if (v0 == 0) {
            backedge(ctx);
        L_004d0688:
            charge(ctx, 1);
            lw(v0, sp, 0x470);
        L_004d068c:
            charge(ctx, 2);
            if (v0 == 0) {
                // 0x004d083c
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004d0694
                charge(ctx, 12);
                lbu(v1, s2, 35);
                a0 = s2;
                s3 = v1 & 0x10;
                v0 = nor(s3, 0);
                v0 = v0 & 0xFF;
                v0 = v1 & v0;
                link(ctx, 0x4D06ACu);  // $ra first: the delay slot below depends on it
                sb(v0, s2, 35);
                call(ctx, gen::fn_sub_4CDF80_004cdf80);
                s0 = v0;
                at = slti(s0, 2);
                s5 = 1;
                if (at == 0) {
                    // 0x004d0844
                    charge(ctx, 1);
                    s4 = addiu(sp, 0x474);
                    for (;;) {
                        // 0x004d0848
                        charge(ctx, 7);
                        a1 = s5 & 0xFF;
                        a0 = s2;
                        a2 = 2;
                        link(ctx, 0x4D0854u);  // $ra first: the delay slot below depends on it
                        sw(zero, s4, 0);
                        call(ctx, gen::fn_sub_4CE200_004ce200);
                        if (v0 != 0) {
                            // 0x004d088c
                            charge(ctx, 9);
                            lw(a1, s2, 12);
                            lw(a2, s2, 16);
                            link(ctx, 0x4D0894u);  // $ra first: the delay slot below depends on it
                            lw(a0, s4, -4);
                            call(ctx, gen::fn_sub_4CEE30_004cee30);
                            sw(v0, s4, 0);
                            a0 = s2;
                            jal(ctx, 0x4D08A0u, gen::fn_sub_4CDE00_004cde00);
                            backedge(ctx);
                        } else {
                            // 0x004d0864
                            charge(ctx, 1);
                        }
                        // 0x004d0868
                        charge(ctx, 3);
                        lw(v0, s4, 0);
                        if (v0 == 0) {
                            break;
                        }
                        // 0x004d0874
                        charge(ctx, 4);
                        s5 = addiu(s5, 1);
                        v0 = slt(s5, s0);
                        s4 = addiu(s4, 4);
                        if (v0 == 0) {
                            goto L_004d0884_38;
                        }
                        backedge(ctx);
                    }
                    // 0x004d08b0
                    charge(ctx, 3);
                    s5 = addiu(s5, -1);
                    if (i64(s5) >= 0) {
                        // 0x004d08bc
                        charge(ctx, 3);
                        v0 = sll(s5, 2);
                        v0 = addu(v0, sp);
                        s0 = addiu(v0, 1136);
                        for (;;) {
                            // 0x004d08c8
                            charge(ctx, 3);
                            lw(a0, s0, 0);
                            if (a0 != s1) {
                                // 0x004d08d4
                                charge(ctx, 3);
                                jal(ctx, 0x4D08D4u, gen::fn_sub_4CBEB0_004cbeb0);
                            }
                            // 0x004d08e0
                            charge(ctx, 3);
                            s5 = addiu(s5, -1);
                            s0 = addiu(s0, -4);
                            if (i64(s5) < 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004d08ec
                        charge(ctx, 1);
                    }
                    // 0x004d08f0
                    charge(ctx, 6);
                    lbu(v1, s2, 35);
                    a0 = s3 & 0xFF;
                    v0 = 0;
                    v1 = v1 | a0;
                    sb(v1, s2, 35);
                } else {
                    // 0x004d06c4
                    charge(ctx, 1);
                    lbu(v0, s2, 35);
                L_004d06c8:
                    charge(ctx, 4);
                    v1 = sll(v0, 8);
                    v0 = v1 & 0x6000;
                    if (v0 == 0) {
                        // 0x004d0908
                        charge(ctx, 3);
                        at = slt(0, s0);
                        s4 = 0;
                        if (at == 0) {
                            backedge(ctx);
                        L_004d079c:
                            charge(ctx, 1);
                            v0 = slt(0, s0);
                        } else {
                            // 0x004d0914
                            charge(ctx, 1);
                            s5 = addiu(sp, 0x470);
                            for (;;) {
                                // 0x004d0918
                                charge(ctx, 7);
                                link(ctx, 0x4D0918u);  // $ra first: the delay slot below depends on it
                                lw(a0, s5, 0);
                                call(ctx, gen::fn_sub_4CD940_004cd940);
                                s4 = addiu(s4, 1);
                                s5 = addiu(s5, 4);
                                v0 = slt(s4, s0);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004d0934
                            charge(ctx, 2);
                            v0 = slt(0, s0);
                            backedge(ctx);
                        }
                        // 0x004d07a0
                        charge(ctx, 2);
                        s4 = 0;
                        if (v0 != 0) {
                            // 0x004d093c
                            charge(ctx, 1);
                            s5 = addiu(sp, 0x470);
                            for (;;) {
                                // 0x004d0940
                                charge(ctx, 6);
                                a1 = s4 & 0xFF;
                                a0 = s2;
                                a2 = 5;
                                jal(ctx, 0x4D0948u, gen::fn_sub_4CE200_004ce200);
                                if (v0 != 0) {
                                    // 0x004d0988
                                    charge(ctx, 7);
                                    lw(a1, s5, 0);
                                    a0 = s2;
                                    jal(ctx, 0x4D098Cu, gen::fn_sub_4CDCE0_004cdce0);
                                    a0 = s2;
                                    jal(ctx, 0x4D0994u, gen::fn_sub_4CDE00_004cde00);
                                    backedge(ctx);
                                }
                                // 0x004d0958
                                charge(ctx, 3);
                                lw(a0, s5, 0);
                                if (a0 != s1) {
                                    // 0x004d0964
                                    charge(ctx, 3);
                                    jal(ctx, 0x4D0964u, gen::fn_sub_4CBEB0_004cbeb0);
                                }
                                // 0x004d0970
                                charge(ctx, 4);
                                s4 = addiu(s4, 1);
                                v0 = slt(s4, s0);
                                s5 = addiu(s5, 4);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004d0980
                            charge(ctx, 2);
                            lbu(v1, s2, 35);
                            backedge(ctx);
                        } else {
                            // 0x004d07a8
                            charge(ctx, 1);
                            lbu(v1, s2, 35);
                        }
                        // 0x004d07ac
                        charge(ctx, 5);
                        a0 = s3 & 0xFF;
                        v0 = s2;
                        v1 = v1 | a0;
                        sb(v1, s2, 35);
                    } else {
                        // 0x004d06d8
                        charge(ctx, 3);
                        v0 = v1 & 0x4000;
                        if (v0 == 0) {
                            // 0x004d073c
                            charge(ctx, 8);
                            a0 = addiu(sp, 0x70);
                            a1 = s1;
                            a2 = addiu(sp, 0x470);
                            a3 = s0;
                            t0 = 8;
                            jal(ctx, 0x4D074Cu, gen::fn_sub_4CF790_004cf790);
                            if (v0 != 0) {
                            L_004d0794:
                                charge(ctx, 2);
                                link(ctx, 0x4D0794u);  // $ra first: the delay slot below depends on it
                                lw(a0, sp, 0x470);
                                call(ctx, gen::fn_sub_4CD940_004cd940);
                                goto L_004d079c;
                            }
                            // 0x004d075c
                            charge(ctx, 3);
                            at = slt(0, s0);
                            if (at == 0) {
                                goto L_004d0794;
                            }
                            // 0x004d0768
                            charge(ctx, 3);
                            lw(a0, sp, 0x470);
                            if (a0 != s1) {
                                // 0x004d0774
                                charge(ctx, 2);
                                jal(ctx, 0x4D0774u, gen::fn_sub_4CBEB0_004cbeb0);
                            }
                            // 0x004d077c
                            charge(ctx, 6);
                            lbu(v1, s2, 35);
                            a0 = s3 & 0xFF;
                            v0 = 0;
                            v1 = v1 | a0;
                            sb(v1, s2, 35);
                        } else {
                            // 0x004d06e4
                            charge(ctx, 8);
                            a0 = addiu(sp, 0x70);
                            a1 = s1;
                            a2 = addiu(sp, 0x470);
                            a3 = s0;
                            t0 = 4;
                            jal(ctx, 0x4D06F4u, gen::fn_sub_4CF790_004cf790);
                            if (v0 != 0) {
                                goto L_004d0794;
                            }
                            // 0x004d0704
                            charge(ctx, 3);
                            at = slt(0, s0);
                            if (at == 0) {
                                goto L_004d0794;
                            }
                            // 0x004d0710
                            charge(ctx, 3);
                            lw(a0, sp, 0x470);
                            if (a0 != s1) {
                                // 0x004d071c
                                charge(ctx, 2);
                                jal(ctx, 0x4D071Cu, gen::fn_sub_4CBEB0_004cbeb0);
                            }
                            // 0x004d0724
                            charge(ctx, 6);
                            lbu(v1, s2, 35);
                            a0 = s3 & 0xFF;
                            v0 = 0;
                            v1 = v1 | a0;
                            sb(v1, s2, 35);
                        }
                    }
                }
            }
        } else {
            // 0x004d07d4
            charge(ctx, 4);
            a0 = v0;
            jal(ctx, 0x4D07D4u, gen::fn_sub_4CBF20_004cbf20);
            if (v0 != 0) {
                // 0x004d07e4
                charge(ctx, 5);
                lw(a0, sp, 0x470);
                a1 = s2;
                jal(ctx, 0x4D07E8u, gen::fn_sub_4CDC70_004cdc70);
                lw(v0, sp, 0x470);
                backedge(ctx);
                goto L_004d068c;
            }
            // 0x004d07f8
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x004d0674
        charge(ctx, 4);
        lw(v0, s1, 12);
        a2 = 32;
        if (v0 == a2) {
            // 0x004d0684
            charge(ctx, 1);
            sw(s1, sp, 0x470);
            goto L_004d0688;
        }
        // 0x004d0800
        charge(ctx, 4);
        a0 = v1;
        jal(ctx, 0x4D0800u, gen::fn_sub_4CBE00_004cbe00);
        sw(v0, sp, 0x470);
        if (v0 == 0) {
            backedge(ctx);
            goto L_004d0688;
        }
        // 0x004d0810
        charge(ctx, 4);
        a0 = v0;
        jal(ctx, 0x4D0810u, gen::fn_sub_4CBF20_004cbf20);
        if (v0 != 0) {
            // 0x004d0820
            charge(ctx, 5);
            lw(a0, sp, 0x470);
            a1 = s1;
            jal(ctx, 0x4D0824u, gen::fn_sub_4CD620_004cd620);
            backedge(ctx);
            goto L_004d0688;
        }
        // 0x004d0834
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004d09a8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x4B0);
    return;
L_004d0884_38:
    charge(ctx, 2);
    lbu(v0, s2, 35);
    backedge(ctx);
    goto L_004d06c8;
}

// sub_4D0AC0 [textureFindNamedAnyDict] -- finds a texture by name: in the current dictionary (the module's +16,
//   sub_4D1170) when there is one, else in every dictionary of the module's list; the texture, or 0
// 0x004D0AC0 sub_4D0AC0 -- 156 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4D0AC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d0ac0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x960000;
    sd(ra, sp, 0x30);
    v0 = addiu(v0, 112);  // &0x960070
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, -17312);  // 0x7CE950
    s0 = a0;
    s1 = addu(v0, v1);
    lw(a0, s1, 16);
    if (a0 == 0) {
        // 0x004d0b04
        charge(ctx, 3);
        lw(s2, s1, 0);
        if (s2 != s1) {
            for (;;) {
                // 0x004d0b10
                charge(ctx, 7);
                a0 = addiu(s2, -16);
                a1 = s0;
                jal(ctx, 0x4D0B14u, gen::fn_sub_4D1170_004d1170);
                v1 = sltu(0, v0);
                v1 = v1 ^ 0x1;
                if (v1 == 0) {
                    goto L_004d0b2c_4;
                }
                // 0x004d0b34
                charge(ctx, 3);
                lw(s2, s2, 0);
                if (s2 == s1) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004d0b40
        charge(ctx, 1);
        v0 = 0;
    L_004d0b44:
        charge(ctx, 1);
        ld(ra, sp, 0x30);
    } else {
        // 0x004d0af4
        charge(ctx, 4);
        a1 = s0;
        jal(ctx, 0x4D0AF4u, gen::fn_sub_4D1170_004d1170);
        ld(ra, sp, 0x30);
    }
    // 0x004d0b48 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
    return;
L_004d0b2c_4:
    charge(ctx, 2);
    goto L_004d0b44;
}

// sub_4D11D0 [RwTexDictionarySetCurrent] -- sets the current texture dictionary (the texture module's +16); the
//   dictionary
// 0x004D11D0 sub_4D11D0 -- 28 bytes; leaf frame (no stack)
void sub_4D11D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x004d11d0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(a1, gp, -17312);  // 0x7CE950
    v1 = 0x960000;
    v1 = addiu(v1, 112);  // &0x960070
    v0 = a0;
    v1 = addu(v1, a1);
    sw(a0, v1, 16);
}

// RpSkySelectDeepZBuffer -- selects the sky driver's Z buffer depth before the engine starts: 32 bits (Im2D near screen
//   Z 16777215) for a non-zero $a0, else 16 bits (65535); refused (0) once the engine is started (0x7CEAC8); 1
// 0x004D82A0 RpSkySelectDeepZBuffer -- 92 bytes; leaf frame (no stack)
void RpSkySelectDeepZBuffer(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x004d82a0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, gp, -16936);  // 0x7CEAC8
    if (v0 != 0) {
        // 0x004d82f0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004d82ac
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x004d82d0
            charge(ctx, 6);
            v1 = 16;
            v0 = 0x477F0000;
            sw(v1, gp, -20248);  // g_skyZBufferDepth
            v1 = v0 | 0xFF00;
            v0 = 0x960000;
            sw(v1, v0, 136);  // g_rwIm2DNearScreenZ
        } else {
            // 0x004d82b4
            charge(ctx, 7);
            v1 = 32;
            v0 = 0x4B7F0000;
            sw(v1, gp, -20248);  // g_skyZBufferDepth
            v1 = v0 | 0xFFFF;
            v0 = 0x960000;
            sw(v1, v0, 136);  // g_rwIm2DNearScreenZ
        }
        // 0x004d82e8
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x004d82f4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// sub_4D8300 [skySetFlag7CEB04] -- stores a sky driver option word (gp 0x7CEB04); 1
// 0x004D8300 sub_4D8300 -- 12 bytes; leaf frame (no stack)
void sub_4D8300(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28};
    // 0x004d8300
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a0, gp, -16876);  // 0x7CEB04
    v0 = 1;
}

// sub_4D8310 [skySetFlag7CDDE8] -- stores a sky driver option word (0x7CDDE8); 1
// 0x004D8310 sub_4D8310 -- 12 bytes; leaf frame (no stack)
void sub_4D8310(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28};
    // 0x004d8310
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(a0, gp, -20232);  // 0x7CDDE8
    v0 = 1;
}

// sub_4D83C0 [skyTextureKLStreamRead] -- the sky texture plugin's stream read: for a 4-byte extension of a texture with
//   a raster, the raster's mipmap K / L halfword (raster + gp 0x7CEAA8 + 20) read; the stream, or 0
// 0x004D83C0 sub_4D83C0 -- 128 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4D83C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d83c0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a2;
    a2 = 4;
    s1 = a0;
    if (a1 == a2) {
        // 0x004d83e0
        charge(ctx, 2);
        if (s0 == 0) {
            goto L_004d8428;
        }
        // 0x004d83e8
        charge(ctx, 3);
        lw(v0, s0, 0);
        if (v0 == 0) {
            goto L_004d8428;
        }
        // 0x004d83f4
        charge(ctx, 4);
        a1 = addiu(sp, 0x3C);
        jal(ctx, 0x4D83F4u, gen::fn_sub_4C1910_004c1910);
        if (v0 != 0) {
            // 0x004d840c
            charge(ctx, 7);
            lw(a0, s0, 0);
            v0 = s1;
            lw(v1, gp, -16968);  // 0x7CEAA8
            lw(a1, sp, 0x3C);
            v1 = addu(a0, v1);
            sh(a1, v1, 20);
        } else {
            // 0x004d8404
            charge(ctx, 2);
            v0 = 0;
        }
        // 0x004d842c (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_004d8428:
    charge(ctx, 1);
    v0 = 0;
    // 0x004d842c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// sub_4D9520 [skyRasterValidateFormat] -- checks and completes a raster's format for the sky driver: the type (+32) and
//   flags (+33) from $a2; a Z buffer must match the selected Z depth (format 0x700 / 0x900), a camera raster the display
//   / custom mode's depth and format (0x500 for 32-bit, 0x100 for 16-bit), a texture / normal raster gets its format from
//   its depth (16 / 24 / 32 / 8 palettised / 4 palettised) or has its depth checked against its format; the private
//   format byte (+35) set; 1, or 0 (errors 0x8000000C / 0x8000000D)
// 0x004D9520 sub_4D9520 -- 1688 bytes; frame 0xB0: ra sp+0x0
void sub_4D9520(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d9520
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    a0 = si(-8);
    sd(ra, sp, 0x0);
    a3 = a2 & 0x7;
    a0 = a2 & a0;
    sb(a3, a1, rw9::raster::kType);
    sb(a0, a1, rw9::raster::kFlags);
    v1 = a2 & 0xF00;
    lbu(a3, a1, rw9::raster::kType);
    t0 = a2 & 0x9000;
    v0 = a2 & 0x6000;
    a2 = 1;
    if (a3 != a2) {
        // 0x004d9558
        charge(ctx, 3);
        a0 = 2;
        if (a3 == a0) {
            // 0x004d9858
            charge(ctx, 2);
            if (t0 == 0) {
                // 0x004d9860
                charge(ctx, 2);
                if (v0 != 0) {
                    goto L_004d9acc;
                }
                // 0x004d9868
                charge(ctx, 3);
                lw(a0, a1, rw9::raster::kDepth);
                if (a0 != 0) {
                    // 0x004d9874
                    charge(ctx, 4);
                    v0 = 0x960000;
                    lw(v0, v0, 22328);  // customMode+0x8
                    if (a0 == v0) {
                        goto L_004d98b8;
                    }
                    // 0x004d9884
                    charge(ctx, 4);
                    v0 = 0x960000;
                    lw(v0, v0, 22352);  // g_skyDisplayMode+0x8
                    if (a0 == v0) {
                        goto L_004d98b8;
                    }
                    // 0x004d9894
                    charge(ctx, 9);
                    v0 = lui(0x8000);
                    sw(a2, sp, 0x48);
                    a0 = v0 | 0xC;
                    jal(ctx, 0x4D989Cu, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0x4C);
                    a0 = addiu(sp, 0x48);
                    jal(ctx, 0x4D98A8u, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                    goto L_004d9bac;
                }
            L_004d98b8:
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x004d9af4
                    charge(ctx, 4);
                    lw(v0, gp, -17120);  // 0x7CEA10
                    lw(v0, v0, 8);
                    sw(v0, a1, rw9::raster::kDepth);
                    backedge(ctx);
                }
                // 0x004d98c0
                charge(ctx, 2);
                if (v1 != 0) {
                    // 0x004d98c8
                    charge(ctx, 3);
                    lw(v0, gp, -16932);  // 0x7CEACC
                    if (v1 == v0) {
                        goto L_004d991c;
                    }
                    // 0x004d98d4
                    charge(ctx, 4);
                    v0 = 0x960000;
                    lw(v0, v0, 22340);  // customMode+0x14
                    if (v1 == v0) {
                        goto L_004d991c;
                    }
                    // 0x004d98e4
                    charge(ctx, 4);
                    v0 = 0x960000;
                    lw(v0, v0, 22364);  // g_skyDisplayMode+0x14
                    if (v1 == v0) {
                        goto L_004d991c;
                    }
                    // 0x004d98f4
                    charge(ctx, 10);
                    v1 = 1;
                    v0 = lui(0x8000);
                    sw(v1, sp, 0x40);
                    a0 = v0 | 0xD;
                    jal(ctx, 0x4D9900u, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0x44);
                    a0 = addiu(sp, 0x40);
                    jal(ctx, 0x4D990Cu, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                    goto L_004d9bac;
                }
            L_004d991c:
                charge(ctx, 2);
                if (v1 == 0) {
                    // 0x004d9924
                    charge(ctx, 1);
                    lw(v1, gp, -16932);  // 0x7CEACC
                }
                // 0x004d9928
                charge(ctx, 4);
                lw(a0, a1, rw9::raster::kDepth);
                v0 = 32;
                if (a0 != v0) {
                    // 0x004d996c
                    charge(ctx, 3);
                    v0 = 256;
                    if (v1 == v0) {
                    L_004d99a0:
                        charge(ctx, 3);
                        v0 = sra(v1, 8);
                        sb(v0, a1, rw9::raster::kFormat);
                        goto L_004d9a00;
                    }
                    // 0x004d9978
                    charge(ctx, 10);
                    v1 = 1;
                    v0 = lui(0x8000);
                    sw(v1, sp, 0x30);
                    a0 = v0 | 0xD;
                    jal(ctx, 0x4D9984u, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0x34);
                    a0 = addiu(sp, 0x30);
                    jal(ctx, 0x4D9990u, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                } else {
                    // 0x004d9938
                    charge(ctx, 3);
                    v0 = 1280;
                    if (v1 == v0) {
                        goto L_004d99a0;
                    }
                    // 0x004d9944
                    charge(ctx, 10);
                    v1 = 1;
                    v0 = lui(0x8000);
                    sw(v1, sp, 0x38);
                    a0 = v0 | 0xD;
                    jal(ctx, 0x4D9950u, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0x3C);
                    a0 = addiu(sp, 0x38);
                    jal(ctx, 0x4D995Cu, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                }
                goto L_004d9bac;
            }
        L_004d9acc:
            charge(ctx, 10);
            v1 = 1;
            v0 = lui(0x8000);
            sw(v1, sp, 0x50);
            a0 = v0 | 0xD;
            jal(ctx, 0x4D9AD8u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x54);
            a0 = addiu(sp, 0x50);
            jal(ctx, 0x4D9AE4u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
            goto L_004d9bac;
        }
        // 0x004d9564
        charge(ctx, 3);
        a0 = 4;
        if (a3 != a0) {
            // 0x004d9570
            charge(ctx, 3);
            a0 = 5;
            if (a3 != a0) {
                // 0x004d957c
                charge(ctx, 2);
                if (a3 == 0) {
                    // 0x004d958c
                    charge(ctx, 2);
                    if (v0 == 0) {
                        // 0x004d9594
                        charge(ctx, 2);
                        if (t0 == 0) {
                            goto L_004d95c4;
                        }
                        goto L_004d959c;
                    }
                L_004d959c:
                    charge(ctx, 10);
                    v1 = 1;
                    v0 = lui(0x8000);
                    sw(v1, sp, 0xA8);
                    a0 = v0 | 0xD;
                    jal(ctx, 0x4D95A8u, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0xAC);
                    a0 = addiu(sp, 0xA8);
                    jal(ctx, 0x4D95B4u, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                    goto L_004d9bac;
                }
                // 0x004d9584
                charge(ctx, 2);
                v0 = 0;
                // 0x004d99f8
                charge(ctx, 2);
                ld(ra, sp, 0x0);
                // 0x004d9bb0 (the shared epilogue, written out on this path)
                charge(ctx, 2);
                sp = addiu(sp, 0xB0);
                return;
            }
        L_004d95c4:
            charge(ctx, 2);
            if (v0 == 0) {
                goto L_004d95f4;
            }
            // 0x004d95cc
            charge(ctx, 10);
            v1 = 1;
            v0 = lui(0x8000);
            sw(v1, sp, 0xA0);
            a0 = v0 | 0xD;
            jal(ctx, 0x4D95D8u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0xA4);
            a0 = addiu(sp, 0xA0);
            jal(ctx, 0x4D95E4u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
            goto L_004d9bac;
        }
    L_004d95f4:
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x004d95fc
            charge(ctx, 4);
            lw(a0, a1, rw9::raster::kDepth);
            v1 = 16;
            if (a0 == v1) {
                // 0x004d966c
                charge(ctx, 1);
                v1 = 256;
            } else {
                // 0x004d960c
                charge(ctx, 3);
                v1 = 32;
                if (a0 == v1) {
                    // 0x004d9664
                    charge(ctx, 2);
                    v1 = 1280;
                } else {
                    // 0x004d9618
                    charge(ctx, 3);
                    v1 = 24;
                    if (a0 == v1) {
                        // 0x004d965c
                        charge(ctx, 2);
                        v1 = 1536;
                    } else {
                        // 0x004d9624
                        charge(ctx, 3);
                        v1 = 8;
                        if (a0 == v1) {
                            // 0x004d9650
                            charge(ctx, 3);
                            v1 = 256;
                            v0 = 8192;
                        } else {
                            // 0x004d9630
                            charge(ctx, 3);
                            v1 = 4;
                            if (a0 == v1) {
                                // 0x004d9644
                                charge(ctx, 3);
                                v1 = 256;
                                v0 = 16384;
                            } else {
                                // 0x004d963c
                                charge(ctx, 2);
                                v1 = 256;
                            }
                        }
                    }
                }
            }
        }
        // 0x004d9670
        charge(ctx, 6);
        a2 = v1 | t0;
        a0 = 8192;
        a2 = v0 | a2;
        a2 = sra(a2, 8);
        sb(a2, a1, rw9::raster::kFormat);
        if (v0 == a0) {
            // 0x004d97f4
            charge(ctx, 3);
            lw(a0, a1, rw9::raster::kDepth);
            if (a0 != 0) {
                // 0x004d9800
                charge(ctx, 3);
                v0 = 8;
                if (a0 == v0) {
                    goto L_004d9a7c;
                }
                // 0x004d980c
                charge(ctx, 10);
                v1 = 1;
                v0 = lui(0x8000);
                sw(v1, sp, 0x68);
                a0 = v0 | 0xC;
                jal(ctx, 0x4D9818u, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x6C);
                a0 = addiu(sp, 0x68);
                jal(ctx, 0x4D9824u, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
                goto L_004d9bac;
            }
        L_004d9a7c:
            charge(ctx, 6);
            v0 = 8;
            v1 = v1 & 0xF00;
            sw(v0, a1, rw9::raster::kDepth);
            v0 = 1280;
            if (v1 == v0) {
                backedge(ctx);
                goto L_004d9a00;
            }
            // 0x004d9a94
            charge(ctx, 3);
            v0 = 256;
            if (v1 == v0) {
                backedge(ctx);
                goto L_004d9a00;
            }
            // 0x004d9aa0
            charge(ctx, 11);
            v1 = 1;
            v0 = lui(0x8000);
            sw(v1, sp, 0x60);
            a0 = v0 | 0xD;
            jal(ctx, 0x4D9AB0u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x64);
            a0 = addiu(sp, 0x60);
            jal(ctx, 0x4D9ABCu, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
        } else {
            // 0x004d9688
            charge(ctx, 3);
            a0 = 16384;
            if (v0 == a0) {
                // 0x004d97b4
                charge(ctx, 3);
                lw(a0, a1, rw9::raster::kDepth);
                if (a0 != 0) {
                    // 0x004d97c0
                    charge(ctx, 3);
                    v0 = 4;
                    if (a0 == v0) {
                        goto L_004d9a2c;
                    }
                    // 0x004d97cc
                    charge(ctx, 10);
                    v1 = 1;
                    v0 = lui(0x8000);
                    sw(v1, sp, 0x78);
                    a0 = v0 | 0xC;
                    jal(ctx, 0x4D97D8u, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0x7C);
                    a0 = addiu(sp, 0x78);
                    jal(ctx, 0x4D97E4u, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                    goto L_004d9bac;
                }
            L_004d9a2c:
                charge(ctx, 6);
                v0 = 4;
                v1 = v1 & 0xF00;
                sw(v0, a1, rw9::raster::kDepth);
                v0 = 1280;
                if (v1 == v0) {
                    backedge(ctx);
                    goto L_004d9a00;
                }
                // 0x004d9a44
                charge(ctx, 3);
                v0 = 256;
                if (v1 == v0) {
                    backedge(ctx);
                    goto L_004d9a00;
                }
                // 0x004d9a50
                charge(ctx, 11);
                v1 = 1;
                v0 = lui(0x8000);
                sw(v1, sp, 0x70);
                a0 = v0 | 0xD;
                jal(ctx, 0x4D9A60u, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x74);
                a0 = addiu(sp, 0x70);
                jal(ctx, 0x4D9A6Cu, gen::fn_sub_4C1C50_004c1c50);
                v0 = 0;
            } else {
                // 0x004d9694
                charge(ctx, 2);
                if (v0 == 0) {
                    // 0x004d96a4
                    charge(ctx, 3);
                    v0 = 1280;
                    if (v1 == v0) {
                        // 0x004d9750
                        charge(ctx, 3);
                        lw(v1, a1, rw9::raster::kDepth);
                        if (v1 != 0) {
                            // 0x004d975c
                            charge(ctx, 3);
                            v0 = 32;
                            if (v1 == v0) {
                                goto L_004d9a20;
                            }
                            // 0x004d9768
                            charge(ctx, 10);
                            v1 = 1;
                            v0 = lui(0x8000);
                            sw(v1, sp, 0x88);
                            a0 = v0 | 0xC;
                            jal(ctx, 0x4D9774u, gen::fn_sub_4C1D10_004c1d10);
                            sw(v0, sp, 0x8C);
                            a0 = addiu(sp, 0x88);
                            jal(ctx, 0x4D9780u, gen::fn_sub_4C1C50_004c1c50);
                            v0 = 0;
                            goto L_004d9bac;
                        }
                    L_004d9a20:
                        charge(ctx, 3);
                        v0 = 32;
                        sw(v0, a1, rw9::raster::kDepth);
                        backedge(ctx);
                        goto L_004d9a00;
                    }
                    // 0x004d96b0
                    charge(ctx, 3);
                    v0 = 1536;
                    if (v1 == v0) {
                        // 0x004d9710
                        charge(ctx, 3);
                        lw(v1, a1, rw9::raster::kDepth);
                        if (v1 != 0) {
                            // 0x004d971c
                            charge(ctx, 3);
                            v0 = 24;
                            if (v1 == v0) {
                                goto L_004d9a14;
                            }
                            // 0x004d9728
                            charge(ctx, 10);
                            v1 = 1;
                            v0 = lui(0x8000);
                            sw(v1, sp, 0x90);
                            a0 = v0 | 0xC;
                            jal(ctx, 0x4D9734u, gen::fn_sub_4C1D10_004c1d10);
                            sw(v0, sp, 0x94);
                            a0 = addiu(sp, 0x90);
                            jal(ctx, 0x4D9740u, gen::fn_sub_4C1C50_004c1c50);
                            v0 = 0;
                            goto L_004d9bac;
                        }
                    L_004d9a14:
                        charge(ctx, 3);
                        v0 = 24;
                        sw(v0, a1, rw9::raster::kDepth);
                        backedge(ctx);
                        goto L_004d9a00;
                    }
                    // 0x004d96bc
                    charge(ctx, 3);
                    v0 = 256;
                    if (v1 == v0) {
                        // 0x004d96d0
                        charge(ctx, 3);
                        lw(v1, a1, rw9::raster::kDepth);
                        if (v1 != 0) {
                            // 0x004d96dc
                            charge(ctx, 3);
                            v0 = 16;
                            if (v1 == v0) {
                                goto L_004d9a08;
                            }
                            // 0x004d96e8
                            charge(ctx, 10);
                            v1 = 1;
                            v0 = lui(0x8000);
                            sw(v1, sp, 0x98);
                            a0 = v0 | 0xC;
                            jal(ctx, 0x4D96F4u, gen::fn_sub_4C1D10_004c1d10);
                            sw(v0, sp, 0x9C);
                            a0 = addiu(sp, 0x98);
                            jal(ctx, 0x4D9700u, gen::fn_sub_4C1C50_004c1c50);
                            v0 = 0;
                            goto L_004d9bac;
                        }
                    L_004d9a08:
                        charge(ctx, 3);
                        v0 = 16;
                        sw(v0, a1, rw9::raster::kDepth);
                        backedge(ctx);
                        goto L_004d9a00;
                    }
                    // 0x004d96c8
                    charge(ctx, 2);
                    v1 = 1;
                    // 0x004d9790
                    charge(ctx, 9);
                    v0 = lui(0x8000);
                    sw(v1, sp, 0x80);
                    a0 = v0 | 0xD;
                    jal(ctx, 0x4D9798u, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0x84);
                    a0 = addiu(sp, 0x80);
                    jal(ctx, 0x4D97A4u, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                } else {
                    // 0x004d969c
                    charge(ctx, 2);
                    v1 = 1;
                    // 0x004d9834
                    charge(ctx, 9);
                    v0 = lui(0x8000);
                    sw(v1, sp, 0x58);
                    a0 = v0 | 0xD;
                    jal(ctx, 0x4D983Cu, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0x5C);
                    a0 = addiu(sp, 0x58);
                    jal(ctx, 0x4D9848u, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                }
            }
        }
        goto L_004d9bac;
    }
    // 0x004d99ac
    charge(ctx, 2);
    if (t0 == 0) {
        // 0x004d99b4
        charge(ctx, 2);
        if (v0 != 0) {
            goto L_004d9b04;
        }
        // 0x004d99bc
        charge(ctx, 3);
        lw(a0, a1, rw9::raster::kDepth);
        if (a0 != 0) {
            // 0x004d99c8
            charge(ctx, 3);
            lw(v0, gp, -20248);  // g_skyZBufferDepth
            if (a0 == v0) {
                goto L_004d9b2c;
            }
            // 0x004d99d4
            charge(ctx, 9);
            v0 = lui(0x8000);
            sw(a2, sp, 0x20);
            a0 = v0 | 0xC;
            jal(ctx, 0x4D99DCu, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x24);
            a0 = addiu(sp, 0x20);
            jal(ctx, 0x4D99E8u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
            goto L_004d9bac;
        }
    L_004d9b2c:
        charge(ctx, 3);
        lw(v0, gp, -20248);  // g_skyZBufferDepth
        sw(v0, a1, rw9::raster::kDepth);
        if (v1 != 0) {
            // 0x004d9b38
            charge(ctx, 4);
            lw(a0, gp, -20248);  // g_skyZBufferDepth
            v0 = 16;
            if (a0 != v0) {
                // 0x004d9b50
                charge(ctx, 1);
                v0 = 2304;
            } else {
                // 0x004d9b48
                charge(ctx, 2);
                v0 = 1792;
            }
            // 0x004d9b54
            charge(ctx, 2);
            if (v1 == v0) {
                goto L_004d9b84;
            }
            // 0x004d9b5c
            charge(ctx, 10);
            v1 = 1;
            v0 = lui(0x8000);
            sw(v1, sp, 0x18);
            a0 = v0 | 0xD;
            jal(ctx, 0x4D9B68u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x1C);
            a0 = addiu(sp, 0x18);
            jal(ctx, 0x4D9B74u, gen::fn_sub_4C1C50_004c1c50);
            v0 = 0;
            goto L_004d9bac;
        }
    L_004d9b84:
        charge(ctx, 4);
        lw(v1, gp, -20248);  // g_skyZBufferDepth
        v0 = 16;
        if (v1 != v0) {
            // 0x004d9b9c
            charge(ctx, 1);
            v0 = 2304;
        } else {
            // 0x004d9b94
            charge(ctx, 2);
            v0 = 1792;
        }
        // 0x004d9ba0
        charge(ctx, 3);
        v0 = sra(v0, 8);
        sb(v0, a1, rw9::raster::kFormat);
        backedge(ctx);
    L_004d9a00:
        charge(ctx, 2);
        v0 = 1;
        goto L_004d9bac;
    }
L_004d9b04:
    charge(ctx, 10);
    v1 = 1;
    v0 = lui(0x8000);
    sw(v1, sp, 0x28);
    a0 = v0 | 0xD;
    jal(ctx, 0x4D9B10u, gen::fn_sub_4C1D10_004c1d10);
    sw(v0, sp, 0x2C);
    a0 = addiu(sp, 0x28);
    jal(ctx, 0x4D9B1Cu, gen::fn_sub_4C1C50_004c1c50);
    v0 = 0;
L_004d9bac:
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    // 0x004d9bb0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0xB0);
}

// sub_4D9BC0 [skyTextureMipLayout] -- computes the GS memory layout of a texture's mip chain for the sky driver: the
//   page / block / column sizes of the pixel storage mode $a2 (PSMCT32 / 24 / 16 / 16S, PSMT8 / 4 and the Z modes), the
//   level count (halving while both sides stay above 8, up to the driver's limit), then level by level each level's
//   page-aligned position and buffer width packed beside the previous ones (the corner cases of levels smaller than a
//   page), the per-level offsets and widths written to the caller's arrays, the last block number converted to the GS
//   block numbering of the storage mode (*$t3) and the total size (*$t2; 64-bit products through __udivdi3 / __umoddi3)
// 0x004D9BC0 sub_4D9BC0 -- 5696 bytes; frame 0x2E0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4D9BC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004d9bc0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x2E0);
    v0 = 58;
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    fp = t0;
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    s2 = a3;
    sq(s0, sp, 0x0);
    sw(t1, sp, 0x230);
    sw(t2, sp, 0x22C);
    sw(t3, sp, 0x228);
    if (s3 == v0) {
        // 0x004d9d40
        charge(ctx, 1);
        s0 = 64;
    L_004d9d44:
        charge(ctx, 3);
        s1 = 16;
        s6 = 8;
        sw(s0, sp, 0x210);
    } else {
        // 0x004d9c14
        charge(ctx, 3);
        v0 = 50;
        if (s3 == v0) {
            // 0x004d9d2c
            charge(ctx, 5);
            s0 = 64;
            s1 = 16;
            s6 = 8;
            sw(s0, sp, 0x210);
        } else {
            // 0x004d9c20
            charge(ctx, 3);
            v0 = 49;
            if (s3 != v0) {
                // 0x004d9c2c
                charge(ctx, 3);
                v0 = 48;
                if (s3 == v0) {
                    goto L_004d9d14;
                }
                // 0x004d9c38
                charge(ctx, 3);
                v0 = 20;
                if (s3 == v0) {
                    // 0x004d9d00
                    charge(ctx, 5);
                    s0 = 128;
                    s1 = 32;
                    s6 = 16;
                    sw(s0, sp, 0x210);
                } else {
                    // 0x004d9c44
                    charge(ctx, 3);
                    v0 = 19;
                    if (s3 == v0) {
                        // 0x004d9ce8
                        charge(ctx, 6);
                        s1 = 16;
                        v0 = 64;
                        s0 = 128;
                        s6 = s1;
                        sw(v0, sp, 0x210);
                    } else {
                        // 0x004d9c50
                        charge(ctx, 3);
                        v0 = 10;
                        if (s3 == v0) {
                            // 0x004d9cd4
                            charge(ctx, 5);
                            s0 = 64;
                            s1 = 16;
                            s6 = 8;
                            sw(s0, sp, 0x210);
                        } else {
                            // 0x004d9c5c
                            charge(ctx, 3);
                            v0 = 2;
                            if (s3 == v0) {
                                // 0x004d9cc0
                                charge(ctx, 5);
                                s0 = 64;
                                s1 = 16;
                                s6 = 8;
                                sw(s0, sp, 0x210);
                            } else {
                                // 0x004d9c68
                                charge(ctx, 3);
                                v0 = 44;
                                if (s3 != v0) {
                                    // 0x004d9c74
                                    charge(ctx, 3);
                                    v0 = 36;
                                    if (s3 == v0) {
                                        goto L_004d9ca8;
                                    }
                                    // 0x004d9c80
                                    charge(ctx, 3);
                                    v0 = 27;
                                    if (s3 == v0) {
                                        goto L_004d9ca8;
                                    }
                                    // 0x004d9c8c
                                    charge(ctx, 3);
                                    v0 = 1;
                                    if (s3 == v0) {
                                        goto L_004d9ca8;
                                    }
                                    // 0x004d9c98
                                    charge(ctx, 2);
                                    if (s3 == 0) {
                                        goto L_004d9ca8;
                                    }
                                    // 0x004d9ca0
                                    charge(ctx, 2);
                                    s0 = 64;
                                    goto L_004d9d44;
                                }
                            L_004d9ca8:
                                charge(ctx, 6);
                                s1 = 8;
                                v0 = 32;
                                s0 = 64;
                                s6 = s1;
                                sw(v0, sp, 0x210);
                            }
                        }
                    }
                }
                goto L_004d9d50;
            }
        L_004d9d14:
            charge(ctx, 6);
            s1 = 8;
            v0 = 32;
            s0 = 64;
            s6 = s1;
            sw(v0, sp, 0x210);
        }
    }
L_004d9d50:
    charge(ctx, 3);
    at = sltu(s5, s4);
    s7 = 1;
    if (at == 0) {
        // 0x004d9d64
        charge(ctx, 1);
        v1 = s4;
    } else {
        // 0x004d9d5c
        charge(ctx, 2);
        v1 = s5;
    }
    // 0x004d9d68
    charge(ctx, 1);
    lw(v0, gp, -20256);  // 0x7CDDD0
    for (;;) {
        // 0x004d9d6c
        charge(ctx, 3);
        at = slti(v1, 9);
        if (at == 0) {
            // 0x004d9d78
            charge(ctx, 3);
            at = slt(s7, v0);
            if (at != 0) {
                // 0x004d9d84
                charge(ctx, 3);
                s7 = addiu(s7, 1);
                v1 = sra(v1, 1);
                backedge(ctx);
                continue;
            }
        }
        break;
    }
    // 0x004d9d90
    charge(ctx, 29);
    v0 = srl(s0, 6);
    sq(v0, sp, 0x110);
    v0 = addu(s5, s0);
    sd(zero, s2, 0);
    v0 = addiu(v0, -1);
    divu(v0, s0);
    lq(v0, sp, 0x110);
    mflo(v1);
    mult(a0, v0, v1);
    at = slti(s7, 2);
    sw(zero, sp, 0x2A0);
    sw(zero, sp, 0x200);
    sw(zero, sp, 0x1F0);
    lw(v0, sp, 0x210);
    sw(zero, sp, 0x1E0);
    sw(zero, sp, 0x1D0);
    v0 = addu(s4, v0);
    v1 = addiu(v0, -1);
    v0 = dsll32(a0, 0);
    v0 = dsrl32(v0, 0);
    sd(v0, fp, 0x0);
    lw(v0, sp, 0x210);
    divu(v1, v0);
    mflo(v1);
    v0 = 1;
    sw(v0, sp, 0x120);
    sw(v1, sp, 0x2C0);
    if (at == 0) {
        // 0x004d9e04
        charge(ctx, 12);
        v0 = addiu(s2, 8);
        sw(v0, sp, 0x1A0);
        v0 = addiu(fp, 0x8);
        sw(v0, sp, 0x190);
        v0 = addiu(sp, 0x2C4);
        sw(v0, sp, 0x180);
        v0 = addiu(sp, 0x2A4);
        sw(v0, sp, 0x170);
        lq(v0, sp, 0x110);
        v0 = dsll32(v0, 0);
        v0 = dsrl32(v0, 0);
        sd(v0, sp, 0x160);
        for (;;) {
            // 0x004d9e34
            charge(ctx, 3);
            at = sltu(s5, s0);
            if (at == 0) {
                // 0x004da8f4
                charge(ctx, 4);
                lw(v0, sp, 0x210);
                v0 = sltu(s4, v0);
                if (v0 != 0) {
                    backedge(ctx);
                    goto L_004d9e40;
                }
                // 0x004da904
                charge(ctx, 40);
                divu(s5, s1);
                mflo(v1);
                divu(s4, s6);
                mflo(v0);
                mult(a1, v1, v0);
                lw(v0, sp, 0x1A0);
                ld(a0, v0, -8);
                v0 = srl(s5, 1);
                v0 = addu(v0, s0);
                v1 = addiu(v0, -1);
                divu(v1, s0);
                v0 = dsll32(a1, 0);
                v0 = dsrl32(v0, 0);
                a0 = a0 + v0;
                lw(v0, sp, 0x1A0);
                sd(a0, v0, 0);
                lq(v0, sp, 0x110);
                mflo(v1);
                mult1(v0, v0, v1);
                sw(zero, sp, 0x200);
                a0 = dsll32(v0, 0);
                v1 = srl(s4, 1);
                lw(v0, sp, 0x210);
                a0 = dsrl32(a0, 0);
                sw(zero, sp, 0x1F0);
                v1 = addu(v1, v0);
                lw(v0, sp, 0x190);
                v1 = addiu(v1, -1);
                sd(a0, v0, 0);
                lw(v0, sp, 0x210);
                divu(v1, v0);
                lw(v0, sp, 0x1A0);
                mflo(a0);
                lw(v1, v0, 0);
                lw(v0, sp, 0x170);
                sw(v1, v0, 0);
                lw(v0, sp, 0x180);
                sw(a0, v0, 0);
                backedge(ctx);
                goto L_004d9f54;
            }
        L_004d9e40:
            charge(ctx, 3);
            v0 = sltu(s5, s0);
            if (v0 != 0) {
                // 0x004da9a4
                charge(ctx, 4);
                lw(v0, sp, 0x210);
                v0 = sltu(s4, v0);
                if (v0 != 0) {
                    backedge(ctx);
                    goto L_004d9e4c;
                }
                // 0x004da9b4
                charge(ctx, 14);
                lw(v0, sp, 0x170);
                at = sltu(s1, s5);
                lw(a1, v0, -4);
                lw(v0, sp, 0x190);
                ld(a0, v0, -8);
                lw(v0, sp, 0x180);
                lw(v1, v0, -4);
                lw(v0, sp, 0x170);
                sw(a1, v0, 0);
                lw(v0, sp, 0x190);
                sd(a0, v0, 0);
                lw(v0, sp, 0x180);
                sw(v1, v0, 0);
                if (at == 0) {
                    // 0x004da9f4
                    charge(ctx, 1);
                    v1 = s1;
                } else {
                    // 0x004da9ec
                    charge(ctx, 2);
                    v1 = s5;
                }
                // 0x004da9f8
                charge(ctx, 5);
                lw(v0, sp, 0x200);
                v0 = addu(v0, v1);
                at = sltu(v0, s0);
                if (at == 0) {
                    // 0x004daae4
                    charge(ctx, 3);
                    lw(v0, sp, 0x1D0);
                    if (v0 != 0) {
                        // 0x004dab50
                        charge(ctx, 9);
                        a3 = sll(v0, 2);
                        v1 = srl(s5, 1);
                        v0 = addu(a3, sp);
                        lw(a0, sp, 0x1A0);
                        v0 = addiu(v0, 572);
                        at = sltu(s1, v1);
                        lwu(a1, v0, 0);
                        sd(a1, a0, 0);
                        if (at == 0) {
                            // 0x004dab7c
                            charge(ctx, 1);
                            a1 = s1;
                        } else {
                            // 0x004dab74
                            charge(ctx, 2);
                            a1 = v1;
                        }
                        // 0x004dab80
                        charge(ctx, 6);
                        a0 = addu(a3, sp);
                        a2 = addiu(a0, 604);
                        lw(a0, a2, 0);
                        a0 = sltu(a1, a0);
                        if (a0 != 0) {
                            // 0x004dabe4
                            charge(ctx, 14);
                            a0 = addu(v1, s1);
                            at = sltu(s1, v1);
                            a0 = addiu(a0, -1);
                            if (at == 0) v1 = s1;
                            divu(a0, s1);
                            lw(a0, v0, 0);
                            mflo(a1);
                            a0 = addu(a0, a1);
                            sw(a0, v0, 0);
                            lw(v0, a2, 0);
                            v0 = subu(v0, v1);
                            sw(v0, a2, 0);
                            backedge(ctx);
                        } else {
                            // 0x004dab98
                            charge(ctx, 4);
                            v1 = srl(s4, 1);
                            at = sltu(s6, v1);
                            if (at == 0) {
                                // 0x004dabb0
                                charge(ctx, 1);
                                a1 = s6;
                            } else {
                                // 0x004daba8
                                charge(ctx, 2);
                                a1 = v1;
                            }
                            // 0x004dabb4
                            charge(ctx, 6);
                            a0 = addu(a3, sp);
                            a2 = addiu(a0, 636);
                            lw(a0, a2, 0);
                            a0 = sltu(a1, a0);
                            if (a0 != 0) {
                                // 0x004dac1c
                                charge(ctx, 16);
                                a0 = addu(v1, s6);
                                a0 = addiu(a0, -1);
                                divu(a0, s6);
                                mflo(a1);
                                divu(s0, s1);
                                mflo(a0);
                                mult(a1, a1, a0);
                                at = sltu(s6, v1);
                                if (at == 0) v1 = s6;
                                lw(a0, v0, 0);
                                a0 = addu(a0, a1);
                                sw(a0, v0, 0);
                                lw(v0, a2, 0);
                                v0 = subu(v0, v1);
                                sw(v0, a2, 0);
                                backedge(ctx);
                            } else {
                                // 0x004dabcc
                                charge(ctx, 3);
                                lw(v0, sp, 0x1D0);
                                v0 = addiu(v0, -1);
                                sw(v0, sp, 0x1D0);
                            }
                        }
                        // 0x004dabd8
                        charge(ctx, 3);
                        v0 = 1;
                        sw(v0, sp, 0x1E0);
                        backedge(ctx);
                    } else {
                        // 0x004daaf0
                        charge(ctx, 3);
                        at = sltu(s6, s4);
                        if (at == 0) {
                            // 0x004dab04
                            charge(ctx, 1);
                            v1 = s6;
                        } else {
                            // 0x004daafc
                            charge(ctx, 2);
                            v1 = s4;
                        }
                        // 0x004dab08
                        charge(ctx, 18);
                        lw(v0, sp, 0x1F0);
                        v0 = addu(v0, v1);
                        sw(v0, sp, 0x1F0);
                        v0 = addu(s4, s6);
                        v0 = addiu(v0, -1);
                        divu(v0, s6);
                        mflo(v1);
                        divu(s0, s1);
                        mflo(v0);
                        mult(v1, v1, v0);
                        lw(v0, sp, 0x1A0);
                        v1 = dsll32(v1, 0);
                        v1 = dsrl32(v1, 0);
                        ld(v0, v0, -8);
                        v1 = v0 + v1;
                        lw(v0, sp, 0x1A0);
                        sd(v1, v0, 0);
                        backedge(ctx);
                    }
                } else {
                    // 0x004daa0c
                    charge(ctx, 3);
                    at = sltu(s6, s4);
                    if (at == 0) {
                        // 0x004daa20
                        charge(ctx, 1);
                        v1 = s6;
                    } else {
                        // 0x004daa18
                        charge(ctx, 2);
                        v1 = s4;
                    }
                    // 0x004daa24
                    charge(ctx, 6);
                    lw(v0, sp, 0x1D0);
                    at = sltu(s1, s5);
                    a0 = sll(v0, 2);
                    v0 = addu(a0, sp);
                    sw(v1, v0, 640);
                    if (at == 0) {
                        // 0x004daa44
                        charge(ctx, 1);
                        v1 = s1;
                    } else {
                        // 0x004daa3c
                        charge(ctx, 2);
                        v1 = s5;
                    }
                    // 0x004daa48
                    charge(ctx, 23);
                    a1 = addu(a0, sp);
                    lw(v0, sp, 0x1A0);
                    sw(v1, a1, 608);
                    v1 = addu(s4, s6);
                    v1 = addiu(v1, -1);
                    divu(v1, s6);
                    ld(v0, v0, -8);
                    mflo(a0);
                    divu(s0, s1);
                    mflo(v1);
                    mult(a0, a0, v1);
                    at = sltu(s1, s5);
                    lw(v1, sp, 0x1D0);
                    v1 = addiu(v1, 1);
                    sw(v1, sp, 0x1D0);
                    v1 = dsll32(a0, 0);
                    v1 = dsrl32(v1, 0);
                    v1 = v0 + v1;
                    v1 = dsll32(v1, 0);
                    v1 = dsra32(v1, 0);
                    sw(v1, a1, 576);
                    if (at == 0) {
                        // 0x004daaac
                        charge(ctx, 1);
                        a0 = s1;
                    } else {
                        // 0x004daaa4
                        charge(ctx, 2);
                        a0 = s5;
                    }
                    // 0x004daab0
                    charge(ctx, 13);
                    lw(v1, sp, 0x200);
                    v1 = addu(v1, a0);
                    sw(v1, sp, 0x200);
                    v1 = addu(s5, s1);
                    v1 = addiu(v1, -1);
                    divu(v1, s1);
                    mflo(v1);
                    v1 = dsll32(v1, 0);
                    v1 = dsrl32(v1, 0);
                    v1 = v0 + v1;
                    lw(v0, sp, 0x1A0);
                    sd(v1, v0, 0);
                    backedge(ctx);
                }
                goto L_004d9f54;
            }
        L_004d9e4c:
            charge(ctx, 3);
            v0 = sltu(s5, s0);
            if (v0 == 0) {
                // 0x004d9e58
                charge(ctx, 4);
                lw(v0, sp, 0x210);
                at = sltu(s4, v0);
                if (at == 0) {
                    goto L_004dacb4;
                }
                // 0x004d9e68
                charge(ctx, 14);
                lw(v0, sp, 0x170);
                at = sltu(s6, s4);
                lw(a1, v0, -4);
                lw(v0, sp, 0x190);
                ld(a0, v0, -8);
                lw(v0, sp, 0x180);
                lw(v1, v0, -4);
                lw(v0, sp, 0x170);
                sw(a1, v0, 0);
                lw(v0, sp, 0x190);
                sd(a0, v0, 0);
                lw(v0, sp, 0x180);
                sw(v1, v0, 0);
                if (at == 0) {
                    // 0x004d9ea8
                    charge(ctx, 1);
                    v1 = s6;
                } else {
                    // 0x004d9ea0
                    charge(ctx, 2);
                    v1 = s4;
                }
                // 0x004d9eac
                charge(ctx, 6);
                lw(v0, sp, 0x1F0);
                v1 = addu(v0, v1);
                lw(v0, sp, 0x210);
                at = sltu(v1, v0);
                if (at == 0) {
                    // 0x004dac5c
                    charge(ctx, 3);
                    at = sltu(s1, s5);
                    if (at == 0) {
                        // 0x004dac70
                        charge(ctx, 1);
                        v1 = s1;
                    } else {
                        // 0x004dac68
                        charge(ctx, 2);
                        v1 = s5;
                    }
                    // 0x004dac74
                    charge(ctx, 16);
                    lw(v0, sp, 0x200);
                    v0 = addu(v0, v1);
                    sw(v0, sp, 0x200);
                    v0 = addu(s5, s1);
                    v0 = addiu(v0, -1);
                    divu(v0, s1);
                    lw(v0, sp, 0x1A0);
                    mflo(v1);
                    v1 = dsll32(v1, 0);
                    v1 = dsrl32(v1, 0);
                    ld(v0, v0, -8);
                    v1 = v0 + v1;
                    lw(v0, sp, 0x1A0);
                    sd(v1, v0, 0);
                    backedge(ctx);
                } else {
                    // 0x004d9ec4
                    charge(ctx, 3);
                    at = sltu(s6, s4);
                    if (at == 0) {
                        // 0x004d9ed8
                        charge(ctx, 1);
                        v1 = s6;
                    } else {
                        // 0x004d9ed0
                        charge(ctx, 2);
                        v1 = s4;
                    }
                    // 0x004d9edc
                    charge(ctx, 30);
                    lw(v0, sp, 0x1F0);
                    v0 = addu(v0, v1);
                    sw(v0, sp, 0x1F0);
                    lw(v0, sp, 0x190);
                    ld(a0, v0, 0);
                    link(ctx, 0x4D9EF0u);  // $ra first: the delay slot below depends on it
                    ld(a1, sp, 0x160);
                    call(ctx, gen::fn___udivdi3_0052fe98);
                    v1 = addu(s4, s6);
                    v1 = addiu(v1, -1);
                    divu(v1, s6);
                    mflo(a0);
                    divu(s0, s1);
                    mflo(v1);
                    mult(a0, a0, v1);
                    v1 = dsll32(v0, 0);
                    a1 = dsll32(a0, 0);
                    v1 = dsra32(v1, 0);
                    a1 = dsrl32(a1, 0);
                    multu(a0, v1, a1);
                    mfhi(v1);
                    v0 = dsra32(v0, 0);
                    pextlw(a0, v1, a0);
                    mult(v1, a1, v0);
                    lw(v0, sp, 0x1A0);
                    v1 = dsll32(v1, 0);
                    v1 = v1 + a0;
                    ld(v0, v0, -8);
                    v1 = v0 + v1;
                    lw(v0, sp, 0x1A0);
                    sd(v1, v0, 0);
                }
                goto L_004d9f54;
            }
        L_004dacb4:
            charge(ctx, 14);
            lw(v0, sp, 0x170);
            at = sltu(s1, s5);
            lw(a1, v0, -4);
            lw(v0, sp, 0x190);
            ld(a0, v0, -8);
            lw(v0, sp, 0x180);
            lw(v1, v0, -4);
            lw(v0, sp, 0x170);
            sw(a1, v0, 0);
            lw(v0, sp, 0x190);
            sd(a0, v0, 0);
            lw(v0, sp, 0x180);
            sw(v1, v0, 0);
            if (at == 0) {
                // 0x004dacf4
                charge(ctx, 1);
                v1 = s1;
            } else {
                // 0x004dacec
                charge(ctx, 2);
                v1 = s5;
            }
            // 0x004dacf8
            charge(ctx, 10);
            lw(v0, sp, 0x200);
            v1 = addu(v0, v1);
            lw(v0, sp, 0x190);
            v1 = dsll32(v1, 0);
            v1 = dsrl32(v1, 0);
            ld(v0, v0, 0);
            v0 = dsll(v0, 6);
            at = sltu(v1, v0);
            if (at == 0) {
                // 0x004dadf8
                charge(ctx, 3);
                at = sltu(s6, s4);
                if (at == 0) {
                    // 0x004dae0c
                    charge(ctx, 1);
                    v1 = s6;
                } else {
                    // 0x004dae04
                    charge(ctx, 2);
                    v1 = s4;
                }
                // 0x004dae10
                charge(ctx, 9);
                lw(v0, sp, 0x1F0);
                a0 = addu(v0, v1);
                lw(v0, sp, 0x180);
                lw(v1, v0, 0);
                lw(v0, sp, 0x210);
                mult(v0, v0, v1);
                at = sltu(a0, v0);
                if (at != 0) {
                    // 0x004dae34
                    charge(ctx, 3);
                    lw(v0, sp, 0x1E0);
                    if (v0 != 0) {
                        goto L_004daea4;
                    }
                    // 0x004dae40
                    charge(ctx, 2);
                    if (s6 == 0) {
                        // 0x004dae50
                        charge(ctx, 1);
                        v1 = s6;
                    } else {
                        // 0x004dae48
                        charge(ctx, 2);
                        v1 = s4;
                    }
                    // 0x004dae54
                    charge(ctx, 20);
                    lw(v0, sp, 0x1F0);
                    v0 = addu(v0, v1);
                    sw(v0, sp, 0x1F0);
                    v0 = addu(s4, s6);
                    v0 = addiu(v0, -1);
                    divu(v0, s6);
                    mflo(v1);
                    divu(s0, s1);
                    mflo(v0);
                    mult(a0, v1, v0);
                    lw(v0, sp, 0x1A0);
                    ld(v1, v0, -8);
                    lw(v0, sp, 0x120);
                    sw(v0, sp, 0x1E0);
                    v0 = dsll32(a0, 0);
                    v0 = dsrl32(v0, 0);
                    v1 = v1 + v0;
                    lw(v0, sp, 0x1A0);
                    sd(v1, v0, 0);
                    backedge(ctx);
                    goto L_004d9f54;
                }
            L_004daea4:
                charge(ctx, 10);
                lw(v0, sp, 0x1D0);
                v1 = srl(s5, 1);
                lw(a0, sp, 0x1A0);
                at = sltu(s1, v1);
                a3 = sll(v0, 2);
                v0 = addu(a3, sp);
                v0 = addiu(v0, 572);
                lwu(a1, v0, 0);
                sd(a1, a0, 0);
                if (at == 0) {
                    // 0x004daed4
                    charge(ctx, 1);
                    a1 = s1;
                } else {
                    // 0x004daecc
                    charge(ctx, 2);
                    a1 = v1;
                }
                // 0x004daed8
                charge(ctx, 6);
                a0 = addu(a3, sp);
                a2 = addiu(a0, 604);
                lw(a0, a2, 0);
                a0 = sltu(a1, a0);
                if (a0 != 0) {
                    // 0x004daf34
                    charge(ctx, 14);
                    a0 = addu(v1, s1);
                    at = sltu(s1, v1);
                    a0 = addiu(a0, -1);
                    if (at == 0) v1 = s1;
                    divu(a0, s1);
                    lw(a0, v0, 0);
                    mflo(a1);
                    a0 = addu(a0, a1);
                    sw(a0, v0, 0);
                    lw(v0, a2, 0);
                    v0 = subu(v0, v1);
                    sw(v0, a2, 0);
                    backedge(ctx);
                } else {
                    // 0x004daef0
                    charge(ctx, 4);
                    v1 = srl(s4, 1);
                    at = sltu(s6, v1);
                    if (at == 0) {
                        // 0x004daf08
                        charge(ctx, 1);
                        a1 = s6;
                    } else {
                        // 0x004daf00
                        charge(ctx, 2);
                        a1 = v1;
                    }
                    // 0x004daf0c
                    charge(ctx, 6);
                    a0 = addu(a3, sp);
                    a2 = addiu(a0, 636);
                    lw(a0, a2, 0);
                    a0 = sltu(a1, a0);
                    if (a0 != 0) {
                        // 0x004daf6c
                        charge(ctx, 16);
                        a0 = addu(v1, s6);
                        a0 = addiu(a0, -1);
                        divu(a0, s6);
                        mflo(a1);
                        divu(s0, s1);
                        mflo(a0);
                        mult(a1, a1, a0);
                        at = sltu(s6, v1);
                        if (at == 0) v1 = s6;
                        lw(a0, v0, 0);
                        a0 = addu(a0, a1);
                        sw(a0, v0, 0);
                        lw(v0, a2, 0);
                        v0 = subu(v0, v1);
                        sw(v0, a2, 0);
                        backedge(ctx);
                    } else {
                        // 0x004daf24
                        charge(ctx, 4);
                        lw(v0, sp, 0x1D0);
                        v0 = addiu(v0, -1);
                        sw(v0, sp, 0x1D0);
                        backedge(ctx);
                    }
                }
            } else {
                // 0x004dad20
                charge(ctx, 3);
                at = sltu(s6, s4);
                if (at == 0) {
                    // 0x004dad34
                    charge(ctx, 1);
                    v1 = s6;
                } else {
                    // 0x004dad2c
                    charge(ctx, 2);
                    v1 = s4;
                }
                // 0x004dad38
                charge(ctx, 6);
                lw(v0, sp, 0x1D0);
                at = sltu(s1, s5);
                a0 = sll(v0, 2);
                v0 = addu(a0, sp);
                sw(v1, v0, 640);
                if (at == 0) {
                    // 0x004dad58
                    charge(ctx, 1);
                    v1 = s1;
                } else {
                    // 0x004dad50
                    charge(ctx, 2);
                    v1 = s5;
                }
                // 0x004dad5c
                charge(ctx, 23);
                a1 = addu(a0, sp);
                lw(v0, sp, 0x1A0);
                sw(v1, a1, 608);
                v1 = addu(s4, s6);
                v1 = addiu(v1, -1);
                divu(v1, s6);
                ld(v0, v0, -8);
                mflo(a0);
                divu(s0, s1);
                mflo(v1);
                mult(a0, a0, v1);
                at = sltu(s1, s5);
                lw(v1, sp, 0x1D0);
                v1 = addiu(v1, 1);
                sw(v1, sp, 0x1D0);
                v1 = dsll32(a0, 0);
                v1 = dsrl32(v1, 0);
                v1 = v0 + v1;
                v1 = dsll32(v1, 0);
                v1 = dsra32(v1, 0);
                sw(v1, a1, 576);
                if (at == 0) {
                    // 0x004dadc0
                    charge(ctx, 1);
                    a0 = s1;
                } else {
                    // 0x004dadb8
                    charge(ctx, 2);
                    a0 = s5;
                }
                // 0x004dadc4
                charge(ctx, 13);
                lw(v1, sp, 0x200);
                v1 = addu(v1, a0);
                sw(v1, sp, 0x200);
                v1 = addu(s5, s1);
                v1 = addiu(v1, -1);
                divu(v1, s1);
                mflo(v1);
                v1 = dsll32(v1, 0);
                v1 = dsrl32(v1, 0);
                v1 = v0 + v1;
                lw(v0, sp, 0x1A0);
                sd(v1, v0, 0);
                backedge(ctx);
            }
        L_004d9f54:
            charge(ctx, 19);
            lw(v0, sp, 0x1A0);
            s5 = srl(s5, 1);
            v0 = addiu(v0, 8);
            sw(v0, sp, 0x1A0);
            lw(v0, sp, 0x190);
            v0 = addiu(v0, 8);
            sw(v0, sp, 0x190);
            lw(v0, sp, 0x180);
            v0 = addiu(v0, 4);
            sw(v0, sp, 0x180);
            lw(v0, sp, 0x170);
            v0 = addiu(v0, 4);
            sw(v0, sp, 0x170);
            lw(v0, sp, 0x120);
            v0 = addiu(v0, 1);
            sw(v0, sp, 0x120);
            v0 = slt(v0, s7);
            s4 = srl(s4, 1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004d9fa0
    charge(ctx, 10);
    v0 = sll(s7, 3);
    v1 = dsll32(s5, 0);
    a0 = addu(v0, fp);
    v1 = dsrl32(v1, 0);
    v0 = addiu(a0, -8);
    sq(v0, sp, 0x100);
    ld(v0, a0, -8);
    a0 = dsll(v0, 6);
    if (v1 == a0) {
        // 0x004d9fc8
        charge(ctx, 7);
        s5 = sll(s7, 2);
        v0 = addu(s5, sp);
        lw(v1, v0, 700);
        lw(v0, sp, 0x210);
        mult(v0, v0, v1);
        sq(v0, sp, 0xF0);
        if (s4 != v0) {
            goto L_004da05c;
        }
        // 0x004d9fe4
        charge(ctx, 4);
        v0 = addiu(s3, -19);
        at = sltiu(v0, 2);
        if (at == 0) {
            // 0x004da054
            charge(ctx, 2);
            s5 = 0;
        } else {
            // 0x004d9ff4
            charge(ctx, 24);
            a1 = dsll32(s1, 0);
            a1 = dsrl32(a1, 0);
            jal(ctx, 0x4D9FF8u, gen::fn___udivdi3_0052fe98);
            lq(v1, sp, 0xF0);
            a1 = dsll32(v1, 0);
            v1 = dsll32(v0, 0);
            a1 = dsrl32(a1, 0);
            v1 = dsra32(v1, 0);
            multu(a0, v1, a1);
            mfhi(v1);
            v0 = dsra32(v0, 0);
            pextlw(v1, v1, a0);
            mult1(v0, a1, v0);
            a1 = dsll32(s6, 0);
            v0 = dsll32(v0, 0);
            a1 = dsrl32(a1, 0);
            a0 = v0 + v1;
            jal(ctx, 0x4DA034u, gen::fn___udivdi3_0052fe98);
            v1 = addu(s5, sp);
            lw(v1, v1, 668);
            v0 = v1 + v0;
            s5 = dsll32(v0, 0);
            s5 = dsra32(s5, 0);
        }
        goto L_004da0f0;
    }
L_004da05c:
    charge(ctx, 3);
    v0 = 19;
    if (s3 == v0) {
        // 0x004dafac
        charge(ctx, 41);
        lq(v0, sp, 0x100);
        a1 = dsll32(s0, 0);
        a1 = dsrl32(a1, 0);
        ld(v0, v0, 0);
        a0 = dsll(v0, 6);
        jal(ctx, 0x4DAFBCu, gen::fn___udivdi3_0052fe98);
        v1 = sll(s7, 2);
        t0 = dsll32(v0, 0);
        t1 = addu(v1, sp);
        t0 = dsra32(t0, 0);
        lw(a2, t1, 700);
        multu(a0, a2, t0);
        mfhi(v1);
        a3 = dsra32(v0, 0);
        pextlw(a1, v1, a0);
        mult1(a0, a3, a2);
        v0 = dsra32(a2, 0);
        mult(v1, t0, v0);
        divu(s0, s1);
        v1 = a0 + v1;
        v1 = dsll32(v1, 0);
        lw(v0, t1, 668);
        v1 = v1 + a1;
        v1 = dsll(v1, 5);
        a2 = v0 + v1;
        mflo(v0);
        a1 = dsll32(v0, 0);
        a1 = dsrl32(a1, 0);
        multu1(v1, t0, a1);
        mfhi1(v0);
        pextlw(a0, v0, v1);
        mult(v1, a1, a3);
        v0 = si(-2);
        pcpyld(v0, zero, v0);
        v1 = dsll32(v1, 0);
        v1 = v1 + a0;
        v1 = a2 - v1;
        v0 = v1 + v0;
        s5 = dsll32(v0, 0);
        s5 = dsra32(s5, 0);
        backedge(ctx);
    } else {
        // 0x004da068
        charge(ctx, 3);
        v0 = 20;
        if (s3 != v0) {
            // 0x004da0ec
            charge(ctx, 1);
            s5 = 0;
        } else {
            // 0x004da074
            charge(ctx, 30);
            s4 = sll(s7, 2);
            a1 = dsll32(s0, 0);
            v0 = addu(s4, sp);
            lw(s5, v0, 700);
            a1 = dsrl32(a1, 0);
            jal(ctx, 0x4DA084u, gen::fn___udivdi3_0052fe98);
            a1 = dsll32(s5, 0);
            a3 = dsll32(v0, 0);
            a1 = dsra32(a1, 0);
            a3 = dsra32(a3, 0);
            multu(a0, a1, a3);
            mfhi(v1);
            v0 = dsra32(v0, 0);
            pextlw(a2, v1, a0);
            mult1(a1, v0, a1);
            v0 = dsra32(s5, 0);
            mult(a0, a3, v0);
            v0 = addu(s4, sp);
            a0 = a1 + a0;
            lw(v1, v0, 668);
            a0 = dsll32(a0, 0);
            a0 = a0 + a2;
            a0 = dsll(a0, 5);
            v0 = si(-1);
            v1 = v1 + a0;
            pcpyld(v0, zero, v0);
            v0 = v1 + v0;
            s5 = dsll32(v0, 0);
            s5 = dsra32(s5, 0);
        }
    }
L_004da0f0:
    charge(ctx, 6);
    lw(v0, sp, 0x2A0);
    at = slt(0, s7);
    lw(s4, fp, 0x0);
    sw(zero, sp, 0x130);
    sw(v0, sp, 0x1C0);
    if (at != 0) {
        // 0x004da108
        charge(ctx, 8);
        v0 = addiu(sp, 0x2A0);
        sw(v0, sp, 0x1B0);
        v0 = dsll32(s1, 0);
        v0 = dsrl32(v0, 0);
        sq(v0, sp, 0xE0);
        v0 = dsll32(s6, 0);
        v0 = dsrl32(v0, 0);
        sq(v0, sp, 0xD0);
        for (;;) {
            // 0x004da128
            charge(ctx, 5);
            ld(v0, fp, 0x0);
            v1 = dsll32(s4, 0);
            v1 = dsrl32(v1, 0);
            sq(v0, sp, 0xC0);
            if (v1 == v0) {
                // 0x004da13c
                charge(ctx, 47);
                lwu(v0, sp, 0x1C0);
                ld(a0, s2, 0);
                v1 = v0;
                lq(v0, sp, 0xE0);
                a3 = dsll32(v0, 0);
                v0 = a0 - v1;
                a3 = dsra32(a3, 0);
                a1 = dsll32(v0, 0);
                a1 = dsra32(a1, 0);
                multu(a0, a3, a1);
                mfhi(v1);
                v0 = dsra32(v0, 0);
                pextlw(a2, v1, a0);
                mult1(a0, v0, a3);
                lq(v0, sp, 0xE0);
                v0 = dsra32(v0, 0);
                mult(v1, a1, v0);
                v0 = sll(s4, 6);
                v0 = dsll32(v0, 0);
                v0 = dsrl32(v0, 0);
                sd(v0, sp, 0x140);
                a1 = v0;
                v0 = a0 + v1;
                v0 = dsll32(v0, 0);
                v0 = v0 + a2;
                sd(v0, sp, 0x150);
                a0 = v0;
                jal(ctx, 0x4DA1A4u, gen::fn___udivdi3_0052fe98);
                lq(v1, sp, 0xD0);
                a1 = dsll32(v0, 0);
                a1 = dsra32(a1, 0);
                a2 = dsll32(v1, 0);
                a2 = dsra32(a2, 0);
                multu(a0, a2, a1);
                mfhi(v1);
                v0 = dsra32(v0, 0);
                pextlw(a0, v1, a0);
                mult1(v1, v0, a2);
                lq(v0, sp, 0xD0);
                v0 = dsra32(v0, 0);
                mult(v0, a1, v0);
                v0 = v1 + v0;
                v0 = dsll32(v0, 0);
                v0 = v0 + a0;
                at = sltiu(v0, 2048);
                if (at == 0) {
                    goto L_004db050;
                }
                // 0x004da1f8
                charge(ctx, 14);
                ld(a0, sp, 0x150);
                v0 = dsll32(v0, 0);
                ld(a1, sp, 0x140);
                v0 = dsra32(v0, 0);
                v0 = sll(v0, 16);
                link(ctx, 0x4DA20Cu);  // $ra first: the delay slot below depends on it
                sq(v0, sp, 0xB0);
                call(ctx, gen::fn___umoddi3_00530578);
                v1 = dsll32(v0, 0);
                lq(v0, sp, 0xB0);
                v1 = dsra32(v1, 0);
                v1 = v0 | v1;
                lw(v0, sp, 0x230);
                sw(v1, v0, 0);
                goto L_004da230;
            }
        L_004db050:
            charge(ctx, 9);
            lq(v0, sp, 0xC0);
            s4 = dsll32(v0, 0);
            lw(v0, sp, 0x230);
            s4 = dsra32(s4, 0);
            sw(zero, v0, 0);
            lw(v0, sp, 0x1B0);
            lw(v0, v0, 0);
            sw(v0, sp, 0x1C0);
            backedge(ctx);
        L_004da230:
            charge(ctx, 6);
            v1 = sll(s4, 6);
            divu(v1, s0);
            mflo(v0);
            at = sltiu(v0, 2);
            if (at == 0) {
                // 0x004db078
                charge(ctx, 45);
                v0 = sll(s4, 11);
                divu(v1, s1);
                mflo(a1);
                divu(v0, s0);
                mflo(a0);
                ld(v0, s2, 0);
                divu(s0, s1);
                mflo(v1);
                divu(a0, a1);
                a2 = subu(a1, v1);
                a2 = dsll32(a2, 0);
                a2 = dsrl32(a2, 0);
                t2 = v0 & a2;
                a2 = dsll32(t2, 0);
                a2 = dsra32(a2, 0);
                mflo(a3);
                t1 = dsll32(a3, 0);
                t1 = dsrl32(t1, 0);
                multu(t0, a2, t1);
                mfhi(a3);
                a2 = dsra32(t2, 0);
                pextlw(t0, a3, t0);
                mult1(a3, t1, a2);
                divu(a1, v1);
                a2 = subu(a0, v1);
                a3 = dsll32(a3, 0);
                a2 = nor(a2, 0);
                t0 = a3 + t0;
                a2 = dsll32(a2, 0);
                a2 = dsrl32(a2, 0);
                a3 = v0 & a2;
                a2 = subu(a0, a1);
                a0 = a3 | t0;
                sq(a0, sp, 0xA0);
                a0 = dsll32(a2, 0);
                a0 = dsrl32(a0, 0);
                a0 = v0 & a0;
                mflo(v0);
                a1 = dsll32(v0, 0);
                a1 = dsrl32(a1, 0);
                jal(ctx, 0x4DB114u, gen::fn___udivdi3_0052fe98);
                lq(v1, sp, 0xA0);
                v0 = v0 | v1;
                sd(v0, s2, 0);
                backedge(ctx);
            }
            // 0x004da248
            charge(ctx, 3);
            v0 = 58;
            if (s3 == v0) {
                // 0x004da538
                charge(ctx, 22);
                ld(a1, s2, 0);
                v0 = si(-32);
                pcpyld(v0, zero, v0);
                a0 = a1 & v0;
                v0 = a1 & 0x1;
                v1 = dsll(v0, 1);
                v0 = a1 & 0x2;
                v1 = a0 | v1;
                v0 = dsll(v0, 3);
                a0 = v0 | v1;
                v0 = a1 & 0x4;
                v1 = a1 & 0x8;
                v0 = dsrl(v0, 2);
                a0 = v0 | a0;
                v0 = a1 & 0x10;
                v1 = v1 | a0;
                v0 = dsrl(v0, 2);
                v0 = v0 | v1;
                v0 = v0 ^ 0x18;
                v0 = dsll32(v0, 0);
                v0 = dsra32(v0, 0);
            } else {
                // 0x004da254
                charge(ctx, 3);
                v0 = 50;
                if (s3 == v0) {
                    // 0x004da4e0
                    charge(ctx, 22);
                    ld(v0, s2, 0);
                    v1 = si(-32);
                    pcpyld(v1, zero, v1);
                    a1 = v0 & v1;
                    v1 = v0 & 0x1;
                    a0 = dsll(v1, 1);
                    v1 = v0 & 0x2;
                    a0 = a1 | a0;
                    v1 = dsll(v1, 2);
                    a1 = v1 | a0;
                    v1 = v0 & 0x4;
                    a0 = dsrl(v1, 2);
                    v1 = v0 & 0x8;
                    a0 = a0 | a1;
                    v1 = dsrl(v1, 1);
                    v0 = v0 & 0x10;
                    v1 = v1 | a0;
                    v0 = v0 | v1;
                    v0 = v0 ^ 0x18;
                    v0 = dsll32(v0, 0);
                    v0 = dsra32(v0, 0);
                } else {
                    // 0x004da260
                    charge(ctx, 3);
                    v0 = 49;
                    if (s3 != v0) {
                        // 0x004da26c
                        charge(ctx, 3);
                        v0 = 48;
                        if (s3 == v0) {
                            goto L_004da490;
                        }
                        // 0x004da278
                        charge(ctx, 3);
                        v0 = 20;
                        if (s3 == v0) {
                            // 0x004da438
                            charge(ctx, 21);
                            ld(v0, s2, 0);
                            v1 = si(-32);
                            pcpyld(v1, zero, v1);
                            a1 = v0 & v1;
                            v1 = v0 & 0x1;
                            a0 = dsll(v1, 1);
                            v1 = v0 & 0x2;
                            a0 = a1 | a0;
                            v1 = dsll(v1, 2);
                            a1 = v1 | a0;
                            v1 = v0 & 0x4;
                            a0 = dsrl(v1, 2);
                            v1 = v0 & 0x8;
                            a0 = a0 | a1;
                            v1 = dsrl(v1, 1);
                            v0 = v0 & 0x10;
                            v1 = v1 | a0;
                            v0 = v0 | v1;
                            v0 = dsll32(v0, 0);
                            v0 = dsra32(v0, 0);
                        } else {
                            // 0x004da284
                            charge(ctx, 3);
                            v0 = 19;
                            if (s3 == v0) {
                                // 0x004da3e8
                                charge(ctx, 19);
                                ld(a1, s2, 0);
                                v0 = si(-31);
                                pcpyld(v0, zero, v0);
                                v1 = a1 & v0;
                                v0 = a1 & 0x2;
                                a0 = dsll(v0, 1);
                                v0 = a1 & 0x4;
                                v1 = a0 | v1;
                                v0 = dsll(v0, 2);
                                a0 = v0 | v1;
                                v0 = a1 & 0x8;
                                v1 = dsrl(v0, 2);
                                v0 = a1 & 0x10;
                                v1 = v1 | a0;
                                v0 = dsrl(v0, 1);
                                v0 = v0 | v1;
                                v0 = dsll32(v0, 0);
                                v0 = dsra32(v0, 0);
                            } else {
                                // 0x004da290
                                charge(ctx, 3);
                                v0 = 10;
                                if (s3 == v0) {
                                    // 0x004da390
                                    charge(ctx, 21);
                                    ld(a1, s2, 0);
                                    v0 = si(-32);
                                    pcpyld(v0, zero, v0);
                                    a0 = a1 & v0;
                                    v0 = a1 & 0x1;
                                    v1 = dsll(v0, 1);
                                    v0 = a1 & 0x2;
                                    v1 = a0 | v1;
                                    v0 = dsll(v0, 3);
                                    a0 = v0 | v1;
                                    v0 = a1 & 0x4;
                                    v1 = a1 & 0x8;
                                    v0 = dsrl(v0, 2);
                                    a0 = v0 | a0;
                                    v0 = a1 & 0x10;
                                    v1 = v1 | a0;
                                    v0 = dsrl(v0, 2);
                                    v0 = v0 | v1;
                                    v0 = dsll32(v0, 0);
                                    v0 = dsra32(v0, 0);
                                } else {
                                    // 0x004da29c
                                    charge(ctx, 3);
                                    v0 = 2;
                                    if (s3 == v0) {
                                        // 0x004da338
                                        charge(ctx, 21);
                                        ld(v0, s2, 0);
                                        v1 = si(-32);
                                        pcpyld(v1, zero, v1);
                                        a1 = v0 & v1;
                                        v1 = v0 & 0x1;
                                        a0 = dsll(v1, 1);
                                        v1 = v0 & 0x2;
                                        a0 = a1 | a0;
                                        v1 = dsll(v1, 2);
                                        a1 = v1 | a0;
                                        v1 = v0 & 0x4;
                                        a0 = dsrl(v1, 2);
                                        v1 = v0 & 0x8;
                                        a0 = a0 | a1;
                                        v1 = dsrl(v1, 1);
                                        v0 = v0 & 0x10;
                                        v1 = v1 | a0;
                                        v0 = v0 | v1;
                                        v0 = dsll32(v0, 0);
                                        v0 = dsra32(v0, 0);
                                    } else {
                                        // 0x004da2a8
                                        charge(ctx, 3);
                                        v0 = 44;
                                        if (s3 != v0) {
                                            // 0x004da2b4
                                            charge(ctx, 3);
                                            v0 = 36;
                                            if (s3 == v0) {
                                                goto L_004da2e8;
                                            }
                                            // 0x004da2c0
                                            charge(ctx, 3);
                                            v0 = 27;
                                            if (s3 == v0) {
                                                goto L_004da2e8;
                                            }
                                            // 0x004da2cc
                                            charge(ctx, 3);
                                            v0 = 1;
                                            if (s3 == v0) {
                                                goto L_004da2e8;
                                            }
                                            // 0x004da2d8
                                            charge(ctx, 2);
                                            if (s3 == 0) {
                                                goto L_004da2e8;
                                            }
                                            // 0x004da2e0
                                            charge(ctx, 2);
                                            // 0x004da590
                                            charge(ctx, 2);
                                            lw(v0, s2, 0);
                                            goto L_004da598;
                                        }
                                    L_004da2e8:
                                        charge(ctx, 19);
                                        ld(a1, s2, 0);
                                        v0 = si(-31);
                                        pcpyld(v0, zero, v0);
                                        v1 = a1 & v0;
                                        v0 = a1 & 0x2;
                                        a0 = dsll(v0, 1);
                                        v0 = a1 & 0x4;
                                        v1 = a0 | v1;
                                        v0 = dsll(v0, 2);
                                        a0 = v0 | v1;
                                        v0 = a1 & 0x8;
                                        v1 = dsrl(v0, 2);
                                        v0 = a1 & 0x10;
                                        v1 = v1 | a0;
                                        v0 = dsrl(v0, 1);
                                        v0 = v0 | v1;
                                        v0 = dsll32(v0, 0);
                                        v0 = dsra32(v0, 0);
                                    }
                                }
                            }
                        }
                        goto L_004da598;
                    }
                L_004da490:
                    charge(ctx, 20);
                    ld(a1, s2, 0);
                    v0 = si(-31);
                    pcpyld(v0, zero, v0);
                    v1 = a1 & v0;
                    v0 = a1 & 0x2;
                    a0 = dsll(v0, 1);
                    v0 = a1 & 0x4;
                    v1 = a0 | v1;
                    v0 = dsll(v0, 2);
                    a0 = v0 | v1;
                    v0 = a1 & 0x8;
                    v1 = dsrl(v0, 2);
                    v0 = a1 & 0x10;
                    v1 = v1 | a0;
                    v0 = dsrl(v0, 1);
                    v0 = v0 | v1;
                    v0 = v0 ^ 0x18;
                    v0 = dsll32(v0, 0);
                    v0 = dsra32(v0, 0);
                }
            }
        L_004da598:
            charge(ctx, 16);
            v0 = dsll32(v0, 0);
            v0 = dsra32(v0, 0);
            fp = addiu(fp, 0x8);
            sd(v0, s2, 0);
            lw(v0, sp, 0x1B0);
            v0 = addiu(v0, 4);
            sw(v0, sp, 0x1B0);
            lw(v0, sp, 0x230);
            v0 = addiu(v0, 4);
            sw(v0, sp, 0x230);
            lw(v0, sp, 0x130);
            v0 = addiu(v0, 1);
            sw(v0, sp, 0x130);
            v0 = slt(v0, s7);
            s2 = addiu(s2, 8);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004da5d8
    charge(ctx, 6);
    v1 = sll(s4, 6);
    divu(v1, s0);
    mflo(v0);
    at = sltiu(v0, 2);
    if (at == 0) {
        // 0x004da5f0
        charge(ctx, 25);
        divu(v1, s1);
        v0 = sll(s4, 11);
        mflo(a3);
        divu(v0, s0);
        mflo(a0);
        divu(s0, s1);
        mflo(a2);
        divu(a0, a3);
        v0 = subu(a3, a2);
        v1 = s5 & v0;
        mflo(v0);
        mult(a1, v1, v0);
        divu(a3, a2);
        v0 = subu(a0, a2);
        v1 = nor(v0, 0);
        v0 = subu(a0, a3);
        a0 = s5 & v1;
        v1 = s5 & v0;
        a0 = a0 | a1;
        mflo(v0);
        divu(v1, v0);
        mflo(v0);
        s5 = v0 | a0;
    }
    // 0x004db130
    charge(ctx, 3);
    v0 = 58;
    if (s3 == v0) {
        backedge(ctx);
        // 0x004da820
        charge(ctx, 17);
        v1 = si(-32);
        v0 = s5 & 0x1;
        v1 = s5 & v1;
        v0 = sll(v0, 1);
        a0 = v1 | v0;
        v0 = s5 & 0x2;
        v1 = sll(v0, 3);
        v0 = s5 & 0x4;
        v1 = v1 | a0;
        v0 = sra(v0, 2);
        v1 = v0 | v1;
        v0 = s5 & 0x8;
        v1 = v0 | v1;
        v0 = s5 & 0x10;
        v0 = sra(v0, 2);
        v0 = v0 | v1;
        s5 = v0 ^ 0x18;
    } else {
        // 0x004db13c
        charge(ctx, 3);
        v0 = 50;
        if (s3 == v0) {
            backedge(ctx);
            // 0x004da7d8
            charge(ctx, 18);
            v1 = si(-32);
            v0 = s5 & 0x1;
            v1 = s5 & v1;
            v0 = sll(v0, 1);
            a0 = v1 | v0;
            v0 = s5 & 0x2;
            v1 = sll(v0, 2);
            v0 = s5 & 0x4;
            v1 = v1 | a0;
            v0 = sra(v0, 2);
            a0 = v0 | v1;
            v0 = s5 & 0x8;
            v1 = sra(v0, 1);
            v0 = s5 & 0x10;
            v1 = v1 | a0;
            v0 = v0 | v1;
            s5 = v0 ^ 0x18;
        } else {
            // 0x004db148
            charge(ctx, 3);
            v0 = 49;
            if (s3 == v0) {
                backedge(ctx);
            } else {
                // 0x004db154
                charge(ctx, 3);
                v0 = 48;
                if (s3 == v0) {
                    backedge(ctx);
                    goto L_004da798;
                }
                // 0x004db160
                charge(ctx, 3);
                v0 = 20;
                if (s3 == v0) {
                    backedge(ctx);
                    // 0x004da754
                    charge(ctx, 17);
                    v1 = si(-32);
                    v0 = s5 & 0x1;
                    v1 = s5 & v1;
                    v0 = sll(v0, 1);
                    a0 = v1 | v0;
                    v0 = s5 & 0x2;
                    v1 = sll(v0, 2);
                    v0 = s5 & 0x4;
                    v1 = v1 | a0;
                    v0 = sra(v0, 2);
                    a0 = v0 | v1;
                    v0 = s5 & 0x8;
                    v1 = sra(v0, 1);
                    v0 = s5 & 0x10;
                    v1 = v1 | a0;
                    s5 = v0 | v1;
                } else {
                    // 0x004db16c
                    charge(ctx, 3);
                    v0 = 19;
                    if (s3 == v0) {
                        backedge(ctx);
                        // 0x004da718
                        charge(ctx, 15);
                        v1 = s5 & 0x2;
                        v0 = si(-31);
                        v1 = sll(v1, 1);
                        v0 = s5 & v0;
                        a0 = v1 | v0;
                        v0 = s5 & 0x4;
                        v1 = sll(v0, 2);
                        v0 = s5 & 0x8;
                        v1 = v1 | a0;
                        v0 = sra(v0, 2);
                        v1 = v0 | v1;
                        v0 = s5 & 0x10;
                        v0 = sra(v0, 1);
                        s5 = v0 | v1;
                    } else {
                        // 0x004db178
                        charge(ctx, 3);
                        v0 = 10;
                        if (s3 == v0) {
                            backedge(ctx);
                            // 0x004da6d4
                            charge(ctx, 17);
                            v1 = si(-32);
                            v0 = s5 & 0x1;
                            v1 = s5 & v1;
                            v0 = sll(v0, 1);
                            a0 = v1 | v0;
                            v0 = s5 & 0x2;
                            v1 = sll(v0, 3);
                            v0 = s5 & 0x4;
                            v1 = v1 | a0;
                            v0 = sra(v0, 2);
                            v1 = v0 | v1;
                            v0 = s5 & 0x8;
                            v1 = v0 | v1;
                            v0 = s5 & 0x10;
                            v0 = sra(v0, 2);
                            s5 = v0 | v1;
                        } else {
                            // 0x004db184
                            charge(ctx, 3);
                            v0 = 2;
                            if (s3 == v0) {
                                backedge(ctx);
                                // 0x004da690
                                charge(ctx, 17);
                                v1 = si(-32);
                                v0 = s5 & 0x1;
                                v1 = s5 & v1;
                                v0 = sll(v0, 1);
                                a0 = v1 | v0;
                                v0 = s5 & 0x2;
                                v1 = sll(v0, 2);
                                v0 = s5 & 0x4;
                                v1 = v1 | a0;
                                v0 = sra(v0, 2);
                                a0 = v0 | v1;
                                v0 = s5 & 0x8;
                                v1 = sra(v0, 1);
                                v0 = s5 & 0x10;
                                v1 = v1 | a0;
                                s5 = v0 | v1;
                            } else {
                                // 0x004db190
                                charge(ctx, 3);
                                v0 = 44;
                                if (s3 == v0) {
                                    backedge(ctx);
                                } else {
                                    // 0x004db19c
                                    charge(ctx, 3);
                                    v0 = 36;
                                    if (s3 == v0) {
                                        backedge(ctx);
                                        goto L_004da654;
                                    }
                                    // 0x004db1a8
                                    charge(ctx, 3);
                                    v0 = 27;
                                    if (s3 == v0) {
                                        backedge(ctx);
                                        goto L_004da654;
                                    }
                                    // 0x004db1b4
                                    charge(ctx, 3);
                                    v0 = 1;
                                    if (s3 == v0) {
                                        backedge(ctx);
                                        goto L_004da654;
                                    }
                                    // 0x004db1c0
                                    charge(ctx, 2);
                                    if (s3 == 0) {
                                        backedge(ctx);
                                        goto L_004da654;
                                    }
                                    // 0x004db1c8
                                    charge(ctx, 2);
                                    backedge(ctx);
                                    goto L_004da864;
                                }
                            L_004da654:
                                charge(ctx, 15);
                                v1 = s5 & 0x2;
                                v0 = si(-31);
                                v1 = sll(v1, 1);
                                v0 = s5 & v0;
                                a0 = v1 | v0;
                                v0 = s5 & 0x4;
                                v1 = sll(v0, 2);
                                v0 = s5 & 0x8;
                                v1 = v1 | a0;
                                v0 = sra(v0, 2);
                                v1 = v0 | v1;
                                v0 = s5 & 0x10;
                                v0 = sra(v0, 1);
                                s5 = v0 | v1;
                            }
                        }
                    }
                }
                goto L_004da864;
            }
        L_004da798:
            charge(ctx, 16);
            v1 = s5 & 0x2;
            v0 = si(-31);
            v1 = sll(v1, 1);
            v0 = s5 & v0;
            a0 = v1 | v0;
            v0 = s5 & 0x4;
            v1 = sll(v0, 2);
            v0 = s5 & 0x8;
            v1 = v1 | a0;
            v0 = sra(v0, 2);
            v1 = v0 | v1;
            v0 = s5 & 0x10;
            v0 = sra(v0, 1);
            v0 = v0 | v1;
            s5 = v0 ^ 0x18;
        }
    }
L_004da864:
    charge(ctx, 36);
    lw(v0, sp, 0x228);
    a1 = dsll32(s1, 0);
    a1 = dsrl32(a1, 0);
    s0 = sll(s7, 2);
    sw(s5, v0, 0);
    lq(v0, sp, 0x100);
    ld(v0, v0, 0);
    a0 = dsll(v0, 6);
    jal(ctx, 0x4DA880u, gen::fn___udivdi3_0052fe98);
    a3 = addu(s0, sp);
    lw(v1, sp, 0x210);
    lw(a0, a3, 700);
    mult(v1, v1, a0);
    divu(v1, s6);
    mflo(a0);
    v1 = dsll32(v0, 0);
    v1 = dsra32(v1, 0);
    a2 = dsll32(a0, 0);
    a2 = dsrl32(a2, 0);
    multu(a1, v1, a2);
    mfhi(a0);
    v1 = dsra32(v0, 0);
    pextlw(a1, a0, a1);
    mult(a0, a2, v1);
    lw(v1, a3, 668);
    a0 = dsll32(a0, 0);
    a0 = a0 + a1;
    v1 = v1 + a0;
    v1 = dsll(v1, 6);
    a0 = dsll32(v1, 0);
    lw(v1, sp, 0x22C);
    a0 = dsra32(a0, 0);
    sw(a0, v1, 0);
    // 0x004db1d0
    charge(ctx, 12);
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
    sp = addiu(sp, 0x2E0);
}

// sub_4DCEA0 [skyRasterSubRaster] -- the sky driver's sub-raster set-up: the sub-raster ($a0) takes its parent's ($a1)
//   format, depth and stride; a sub-raster of a camera raster used as a texture (type 5 of type 2) gets its offset / size
//   rounded to the GS page grid and its own TEX0 words (base pointer, buffer width, log2 width / height); the pixel
//   pointer from the parent's position; the original rectangle kept (+36..+48); 1, or 0 when the parent is unaligned for
//   it
// 0x004DCEA0 sub_4DCEA0 -- 1076 bytes; leaf frame (no stack)
void sub_4DCEA0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28};
    // 0x004dcea0
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v0, gp, -16968);  // 0x7CEAA8
    a2 = 4;
    lbu(a3, a0, rw9::raster::kType);
    lw(v1, a1, 0);
    t0 = addu(a1, v0);
    a3 = a3 & 0x7;
    v0 = addu(a0, v0);
    if (a3 == a2) {
        // 0x004dcf9c
        charge(ctx, 7);
        lbu(a2, v0, 54);
        a2 = a2 & 0xFE;
        sb(a2, v0, 54);
        lbu(a2, t0, 54);
        a2 = a2 & 0x2;
        if (a2 == 0) {
            // 0x004dcfc8
            charge(ctx, 4);
            lbu(a2, v0, 54);
            a2 = a2 & 0xFD;
            sb(a2, v0, 54);
            backedge(ctx);
        } else {
            // 0x004dcfb8
            charge(ctx, 4);
            lbu(a2, v0, 54);
            a2 = a2 | 0x2;
            sb(a2, v0, 54);
            backedge(ctx);
        }
    }
    // 0x004dcec0
    charge(ctx, 4);
    lbu(a2, t0, 54);
    a2 = a2 & 0x2;
    if (a2 != 0) {
        // 0x004dced0
        charge(ctx, 4);
        lh(a2, a0, rw9::raster::kOffsetX);
        a2 = a2 & 0x15;
        if (a2 == 0) {
            // 0x004dcee0
            charge(ctx, 4);
            lh(a2, a0, rw9::raster::kOffsetY);
            a2 = a2 & 0x7;
            if (a2 != 0) {
                goto L_004dcfd8;
            }
            // 0x004dcef0
            charge(ctx, 3);
            lbu(a2, v0, 54);
            a2 = a2 | 0x2;
            sb(a2, v0, 54);
            goto L_004dcefc;
        }
    L_004dcfd8:
        charge(ctx, 2);
        v0 = 0;
        // 0x004dd2cc (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_004dcefc:
    charge(ctx, 11);
    lbu(a2, a1, 35);
    v0 = 2;
    sb(a2, a0, rw9::raster::kFormat);
    lw(a2, a1, 24);
    sw(a2, a0, rw9::raster::kStride);
    lw(a2, a1, 20);
    sw(a2, a0, rw9::raster::kDepth);
    lbu(a3, a1, 32);
    a2 = a3 & 0x7;
    if (a2 == v0) {
        // 0x004dcf28
        charge(ctx, 5);
        lbu(a2, a0, rw9::raster::kType);
        v0 = 5;
        a2 = a2 & 0x7;
        if (a2 != v0) {
            goto L_004dd2c4;
        }
        // 0x004dcf3c
        charge(ctx, 15);
        v0 = a3 | 0x80;
        t0 = si(-1);
        sb(v0, a0, rw9::raster::kType);
        lh(a3, a0, rw9::raster::kOffsetX);
        a2 = a3 & 0x3F;
        v0 = dsll32(a2, 16);
        v0 = dsra32(v0, 16);
        v0 = subu(a3, v0);
        sh(v0, a0, rw9::raster::kOffsetX);
        lw(v0, a0, rw9::raster::kWidth);
        v0 = addu(v0, a2);
        sw(v0, a0, rw9::raster::kWidth);
        lw(a2, a0, rw9::raster::kWidth);
        v0 = a2;
        if (a2 == 0) {
            // 0x004dcfe0
            charge(ctx, 1);
            v0 = 1;
        } else {
            for (;;) {
                // 0x004dcf78
                charge(ctx, 7);
                v0 = srl(v0, 1);
                t0 = addiu(t0, 1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004dcf94
            charge(ctx, 2);
            v0 = 1;
        }
        // 0x004dcfe4
        charge(ctx, 5);
        v0 = sllv(v0, t0);
        v0 = addiu(v0, -1);
        v0 = a2 & v0;
        if (v0 != 0) {
            // 0x004dd0a0
            charge(ctx, 4);
            v0 = subu(a2, v0);
            v0 = sll(v0, 1);
            sw(v0, a0, rw9::raster::kWidth);
            backedge(ctx);
        }
        // 0x004dcff8
        charge(ctx, 7);
        lh(a3, a0, rw9::raster::kOffsetX);
        lw(a2, a0, rw9::raster::kWidth);
        lw(v0, a1, 12);
        a2 = addu(a3, a2);
        v0 = subu(a2, v0);
        if (i64(v0) > 0) {
            // 0x004dd014
            charge(ctx, 3);
            at = slt(v0, a3);
            if (at != 0) {
                // 0x004dd020
                charge(ctx, 4);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                v0 = subu(a3, v0);
                sh(v0, a0, rw9::raster::kOffsetX);
            }
        }
        // 0x004dd030
        charge(ctx, 19);
        lw(a2, a1, 24);
        v0 = 320;
        lh(a3, a0, rw9::raster::kOffsetY);
        t0 = si(-1);
        a2 = sra(a2, 8);
        div(v0, a2);
        mflo(v0);
        v0 = addiu(v0, -1);
        a2 = a3 & v0;
        v0 = dsll32(a2, 16);
        v0 = dsra32(v0, 16);
        v0 = subu(a3, v0);
        sh(v0, a0, rw9::raster::kOffsetY);
        lw(v0, a0, rw9::raster::kHeight);
        v0 = addu(v0, a2);
        sw(v0, a0, rw9::raster::kHeight);
        lw(a2, a0, rw9::raster::kHeight);
        v0 = a2;
        if (a2 == 0) {
            // 0x004dd0b0
            charge(ctx, 1);
            v0 = 1;
        } else {
            for (;;) {
                // 0x004dd07c
                charge(ctx, 7);
                v0 = srl(v0, 1);
                t0 = addiu(t0, 1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004dd098
            charge(ctx, 2);
            v0 = 1;
        }
        // 0x004dd0b4
        charge(ctx, 5);
        v0 = sllv(v0, t0);
        v0 = addiu(v0, -1);
        v0 = a2 & v0;
        if (v0 != 0) {
            // 0x004dd1b8
            charge(ctx, 4);
            v0 = subu(a2, v0);
            v0 = sll(v0, 1);
            sw(v0, a0, rw9::raster::kHeight);
            backedge(ctx);
        }
        // 0x004dd0c8
        charge(ctx, 7);
        lh(a3, a0, rw9::raster::kOffsetY);
        lw(a2, a0, rw9::raster::kHeight);
        lw(v0, a1, 16);
        a2 = addu(a3, a2);
        v0 = subu(a2, v0);
        if (i64(v0) > 0) {
            // 0x004dd0e4
            charge(ctx, 3);
            at = slt(v0, a3);
            if (at != 0) {
                // 0x004dd0f0
                charge(ctx, 4);
                v0 = dsll32(v0, 16);
                v0 = dsra32(v0, 16);
                v0 = subu(a3, v0);
                sh(v0, a0, rw9::raster::kOffsetY);
            }
        }
        // 0x004dd100
        charge(ctx, 37);
        lw(v0, a1, 24);
        lw(a3, gp, -16968);  // 0x7CEAA8
        lh(a2, a0, rw9::raster::kOffsetY);
        a1 = sra(v0, 8);
        v0 = addu(a0, a3);
        mult(a3, a2, a1);
        lh(a2, a0, rw9::raster::kOffsetX);
        a3 = dsll32(a3, 0);
        a3 = dsra32(a3, 0);
        a2 = a2 & 0xFFF;
        a2 = dsra(a2, 1);
        a2 = a2 + a3;
        a2 = a2 & 0x1FF;
        a2 = dsll32(a2, 0);
        a2 = dsra32(a2, 0);
        sw(a2, v0, 8);
        ld(a3, gp, -17080);  // 0x7CEA38
        lw(a2, v0, 8);
        a3 = dsra(a3, 16);
        a3 = a3 & 0x3F;
        a3 = dsll(a3, 14);
        a3 = dsll32(a3, 0);
        a3 = dsra32(a3, 0);
        a2 = a2 | a3;
        sw(a2, v0, 8);
        ld(a3, gp, -17080);  // 0x7CEA38
        lw(a2, v0, 8);
        a3 = dsra(a3, 24);
        a3 = a3 & 0x3F;
        a3 = dsll(a3, 20);
        a3 = dsll32(a3, 0);
        a3 = dsra32(a3, 0);
        a2 = a2 | a3;
        sw(a2, v0, 8);
        lw(a2, a0, rw9::raster::kWidth);
        a1 = si(-1);
        if (a2 == 0) {
            // 0x004dd1c8
            charge(ctx, 1);
            a2 = a1 & 0xF;
        } else {
            for (;;) {
                // 0x004dd194
                charge(ctx, 7);
                a2 = srl(a2, 1);
                a1 = addiu(a1, 1);
                if (a2 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004dd1b0
            charge(ctx, 2);
            a2 = a1 & 0xF;
        }
        // 0x004dd1cc
        charge(ctx, 8);
        lw(a1, v0, 8);
        a2 = sll(a2, 26);
        a1 = a1 | a2;
        sw(a1, v0, 8);
        sw(zero, v0, 12);
        lw(a1, a0, rw9::raster::kHeight);
        a3 = si(-1);
        if (a1 != 0) {
            for (;;) {
                // 0x004dd1ec
                charge(ctx, 7);
                a1 = srl(a1, 1);
                a3 = addiu(a3, 1);
                if (a1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004dd208
        charge(ctx, 8);
        a1 = a3 & 0xF;
        a2 = sll(a1, 30);
        lw(a1, v0, 8);
        a1 = a1 | a2;
        sw(a1, v0, 8);
        lw(a1, a0, rw9::raster::kHeight);
        a3 = si(-1);
        if (a1 != 0) {
            for (;;) {
                // 0x004dd228
                charge(ctx, 7);
                a1 = srl(a1, 1);
                a3 = addiu(a3, 1);
                if (a1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004dd244
            charge(ctx, 1);
        }
        // 0x004dd248
        charge(ctx, 6);
        a1 = a3 & 0xF;
        a2 = sra(a1, 2);
        lw(a1, v0, 12);
        a1 = a1 | a2;
        sw(a1, v0, 12);
        sb(zero, v0, 22);
        goto L_004dd260;
    }
L_004dd2c4:
    charge(ctx, 2);
    sb(a3, a0, rw9::raster::kType);
    backedge(ctx);
L_004dd260:
    charge(ctx, 25);
    lh(a1, a0, rw9::raster::kOffsetY);
    lw(v0, v1, 24);
    mult(a3, v0, a1);
    lw(a2, v1, 4);
    lw(a1, v1, 20);
    lh(v0, a0, rw9::raster::kOffsetX);
    a2 = addu(a2, a3);
    a1 = addiu(a1, 3);
    a1 = sra(a1, 2);
    mult1(a1, v0, a1);
    a1 = sra(a1, 1);
    v0 = 1;
    a1 = addu(a2, a1);
    sw(a1, a0, rw9::raster::kPixels);
    lw(v1, v1, 8);
    sw(v1, a0, rw9::raster::kPalette);
    lw(v1, a0, rw9::raster::kPixels);
    sw(v1, a0, rw9::raster::kOrigPixels);
    lw(v1, a0, rw9::raster::kWidth);
    sw(v1, a0, rw9::raster::kOrigWidth);
    lw(v1, a0, rw9::raster::kHeight);
    sw(v1, a0, rw9::raster::kOrigHeight);
    lw(v1, a0, rw9::raster::kStride);
    sw(v1, a0, rw9::raster::kOrigStride);
    // 0x004dd2cc (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// sub_4DF0E0 [skyRasterGetMipLevels] -- the sky driver's mip-level count of a raster: (the raster extension's +22 >> 2)
//   + 1 for a mipmapped raster (flag 0x80 of +35), else 1; 0 for a raster without pixels
// 0x004DF0E0 sub_4DF0E0 -- 88 bytes; leaf frame (no stack)
void sub_4DF0E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    // 0x004df0e0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, gp, -16968);  // 0x7CEAA8
    lw(v0, a1, 4);
    v1 = addu(a1, v1);
    if (v0 == 0) {
        // 0x004df12c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004df0f0
        charge(ctx, 4);
        lbu(v0, a1, 35);
        v0 = v0 & 0x80;
        if (v0 != 0) {
            // 0x004df100
            charge(ctx, 2);
            if (v1 == 0) {
                goto L_004df120;
            }
            // 0x004df108
            charge(ctx, 4);
            lbu(v0, v1, 22);
            v0 = sra(v0, 2);
            v0 = addiu(v0, 1);
            sw(v0, a0, 0);
            goto L_004df118;
        }
    L_004df120:
        charge(ctx, 3);
        v0 = 1;
        sw(v0, a0, 0);
        backedge(ctx);
    L_004df118:
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x004df130 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// sub_4DF3F0 [skyRasterNativeStreamRead] -- reads a raster's PS2 native data: the 64-byte struct, a raster created with
//   that size, depth and format (the mip-level count forced meanwhile), the raster extension's GS words restored, then
//   the pixel data (one block, or palette and pixels for a palettised texture) with the data cache written back
//   (SyncDCache); the raster, or 0 (destroyed on a failure)
// 0x004DF3F0 sub_4DF3F0 -- 964 bytes; frame 0xC0: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4DF3F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004df3f0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    a1 = 1;
    sd(ra, sp, 0x50);
    a2 = addiu(sp, 0xBC);
    sq(s4, sp, 0x40);
    a3 = addiu(sp, 0xB8);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    jal(ctx, 0x4DF418u, gen::fn_sub_4C1600_004c1600);
    if (v0 == 0) {
        // 0x004df658
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004df428
        charge(ctx, 6);
        lw(v1, sp, 0xB8);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        if (v0 == 0) {
            // 0x004df440
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at == 0) {
                goto L_004df770;
            }
            // 0x004df454
            charge(ctx, 10);
            a0 = addiu(sp, 0x60);
            a1 = 0;
            a2 = 64;
            jal(ctx, 0x4DF45Cu, gen::fn_memset_00521408);
            lw(a2, sp, 0xBC);
            a0 = s0;
            a1 = addiu(sp, 0x60);
            jal(ctx, 0x4DF46Cu, gen::fn_sub_4C1910_004c1910);
            if (v0 == 0) {
                // 0x004df660
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004df47c
                charge(ctx, 5);
                s3 = addiu(sp, 0x6E);
                lhu(v0, s3, 0);
                v0 = slti(v0, 2);
                if (v0 != 0) {
                    // 0x004df668
                    charge(ctx, 3);
                    v0 = 1;
                    sw(v0, gp, -17108);  // 0x7CEA1C
                    backedge(ctx);
                }
                // 0x004df490
                charge(ctx, 15);
                s1 = addiu(sp, 0x7C);
                lw(s2, gp, -20256);  // 0x7CDDD0
                lw(v0, s1, 0);
                lhu(a3, sp, 0x6C);
                lw(a0, sp, 0x60);
                lw(a1, sp, 0x64);
                lw(a2, sp, 0x68);
                v0 = srl(v0, 2);
                v0 = addiu(v0, 1);
                link(ctx, 0x4DF4B4u);  // $ra first: the delay slot below depends on it
                sw(v0, gp, -20256);  // 0x7CDDD0
                call(ctx, gen::fn_sub_4CE0F0_004ce0f0);
                s4 = v0;
                sw(s2, gp, -20256);  // 0x7CDDD0
                sw(zero, gp, -17108);  // 0x7CEA1C
                if (s4 == 0) {
                    // 0x004df674
                    charge(ctx, 2);
                    v0 = 0;
                } else {
                    // 0x004df4cc
                    charge(ctx, 30);
                    lw(v1, gp, -16968);  // 0x7CEAA8
                    lw(v0, sp, 0x70);
                    s2 = addu(s4, v1);
                    sw(v0, s2, 8);
                    lw(v0, sp, 0x74);
                    sw(v0, s2, 12);
                    lw(v0, sp, 0x78);
                    sw(v0, s2, 16);
                    lw(v0, s1, 0);
                    sb(v0, s2, 22);
                    lw(v0, sp, 0x80);
                    sw(v0, s2, 24);
                    lw(v0, sp, 0x84);
                    sw(v0, s2, 28);
                    lw(v0, sp, 0x88);
                    sw(v0, s2, 32);
                    lw(v0, sp, 0x8C);
                    sw(v0, s2, 36);
                    lw(v0, sp, 0x90);
                    sw(v0, s2, 40);
                    lw(v0, sp, 0x94);
                    sw(v0, s2, 44);
                    lw(v0, sp, 0x98);
                    sw(v0, s2, 48);
                    lw(v0, sp, 0x9C);
                    sh(v0, s2, 20);
                    lhu(v0, s3, 0);
                    v0 = slti(v0, 2);
                    if (v0 != 0) {
                        // 0x004df67c
                        charge(ctx, 5);
                        lw(v1, s4, rw9::raster::kPixels);
                        lw(v0, s2, 40);
                        v0 = addu(v1, v0);
                        sw(v0, s4, rw9::raster::kPalette);
                        backedge(ctx);
                    }
                    // 0x004df544
                    charge(ctx, 4);
                    lhu(v1, s3, 0);
                    at = slti(v1, 2);
                    if (at != 0) {
                        // 0x004df554
                        charge(ctx, 3);
                        v0 = 1;
                        if (v1 != v0) {
                            // 0x004df580
                            charge(ctx, 4);
                            lbu(v0, s2, 54);
                            v0 = v0 & 0x1;
                            if (v0 == 0) {
                                // 0x004df590
                                charge(ctx, 3);
                                lbu(v0, s2, 54);
                                v0 = v0 & 0xFD;
                                sb(v0, s2, 54);
                                goto L_004df59c;
                            }
                            // 0x004df6a0
                            charge(ctx, 4);
                            a0 = s4;
                            jal(ctx, 0x4DF6A0u, gen::fn_sub_4CDE90_004cde90);
                            v0 = 0;
                        } else {
                            // 0x004df560
                            charge(ctx, 4);
                            lbu(v0, s2, 54);
                            v0 = v0 & 0x1;
                            if (v0 == 0) {
                                // 0x004df570
                                charge(ctx, 4);
                                lbu(v0, s2, 54);
                                v0 = v0 | 0x2;
                                sb(v0, s2, 54);
                                goto L_004df59c;
                            }
                            // 0x004df690
                            charge(ctx, 4);
                            a0 = s4;
                            jal(ctx, 0x4DF690u, gen::fn_sub_4CDE90_004cde90);
                            v0 = 0;
                        }
                        // 0x004df794 (the shared epilogue, written out on this path)
                        charge(ctx, 8);
                        ld(ra, sp, 0x50);
                        lq(s4, sp, 0x40);
                        lq(s3, sp, 0x30);
                        lq(s2, sp, 0x20);
                        lq(s1, sp, 0x10);
                        lq(s0, sp, 0x0);
                        sp = addiu(sp, 0xC0);
                        return;
                    }
                L_004df59c:
                    charge(ctx, 7);
                    a0 = s0;
                    a1 = 1;
                    a2 = addiu(sp, 0xBC);
                    a3 = addiu(sp, 0xB8);
                    jal(ctx, 0x4DF5A8u, gen::fn_sub_4C1600_004c1600);
                    if (v0 == 0) {
                        // 0x004df6b0
                        charge(ctx, 4);
                        a0 = s4;
                        jal(ctx, 0x4DF6B0u, gen::fn_sub_4CDE90_004cde90);
                        v0 = 0;
                    } else {
                        // 0x004df5b8
                        charge(ctx, 6);
                        lw(v1, sp, 0xB8);
                        v0 = 0x30000;
                        v0 = v0 | 0x5000;
                        v0 = sltu(v1, v0);
                        if (v0 == 0) {
                            // 0x004df5d0
                            charge(ctx, 5);
                            at = 0x30000;
                            at = at | 0x7003;
                            at = sltu(v1, at);
                            if (at == 0) {
                                goto L_004df748;
                            }
                            // 0x004df5e4
                            charge(ctx, 4);
                            lhu(v1, s3, 0);
                            v0 = slti(v1, 2);
                            if (v0 != 0) {
                                // 0x004df6c0
                                charge(ctx, 7);
                                a0 = s0;
                                lw(a1, s4, rw9::raster::kPixels);
                                lw(s0, sp, 0xBC);
                                a2 = s0;
                                jal(ctx, 0x4DF6CCu, gen::fn_sub_4C5250_004c5250);
                                if (s0 == v0) {
                                    // 0x004df6ec
                                    charge(ctx, 4);
                                    lw(a0, s4, rw9::raster::kPixels);
                                    v0 = addu(a0, s0);
                                    a1 = addiu(v0, 127);
                                    jal(ctx, 0x4DF6F4u, gen::fn_SyncDCache_00503a58);
                                L_004df6fc:
                                    charge(ctx, 2);
                                    v0 = s4;
                                } else {
                                    // 0x004df6dc
                                    charge(ctx, 4);
                                    a0 = s4;
                                    jal(ctx, 0x4DF6DCu, gen::fn_sub_4CDE90_004cde90);
                                    v0 = 0;
                                }
                            } else {
                                // 0x004df5f4
                                charge(ctx, 3);
                                v0 = 2;
                                if (v1 != v0) {
                                    // 0x004df738
                                    charge(ctx, 4);
                                    a0 = s4;
                                    jal(ctx, 0x4DF738u, gen::fn_sub_4CDE90_004cde90);
                                    v0 = 0;
                                } else {
                                    // 0x004df600
                                    charge(ctx, 8);
                                    lw(v0, s4, rw9::raster::kOrigPixels);
                                    a0 = s0;
                                    lw(s1, s2, 40);
                                    lw(a1, v0, 4);
                                    a2 = s1;
                                    jal(ctx, 0x4DF610u, gen::fn_sub_4C5250_004c5250);
                                    if (s1 == v0) {
                                        // 0x004df620
                                        charge(ctx, 3);
                                        lw(s1, s2, 44);
                                        if (s1 != 0) {
                                            // 0x004df62c
                                            charge(ctx, 7);
                                            lw(v0, s4, rw9::raster::kPalette);
                                            a0 = s0;
                                            a2 = s1;
                                            a1 = addiu(v0, -80);
                                            jal(ctx, 0x4DF638u, gen::fn_sub_4C5250_004c5250);
                                            if (s1 == v0) {
                                                goto L_004df714;
                                            }
                                            // 0x004df648
                                            charge(ctx, 4);
                                            a0 = s4;
                                            jal(ctx, 0x4DF648u, gen::fn_sub_4CDE90_004cde90);
                                            v0 = 0;
                                            // 0x004df794 (the shared epilogue, written out on this path)
                                            charge(ctx, 8);
                                            ld(ra, sp, 0x50);
                                            lq(s4, sp, 0x40);
                                            lq(s3, sp, 0x30);
                                            lq(s2, sp, 0x20);
                                            lq(s1, sp, 0x10);
                                            lq(s0, sp, 0x0);
                                            sp = addiu(sp, 0xC0);
                                            return;
                                        }
                                    L_004df714:
                                        charge(ctx, 9);
                                        lw(v1, s4, rw9::raster::kOrigPixels);
                                        lw(v0, s4, rw9::raster::kPalette);
                                        lw(a0, v1, 4);
                                        v0 = addu(v0, s1);
                                        v0 = addiu(v0, -80);
                                        a1 = addiu(v0, 127);
                                        jal(ctx, 0x4DF728u, gen::fn_SyncDCache_00503a58);
                                        backedge(ctx);
                                        goto L_004df6fc;
                                    }
                                    // 0x004df704
                                    charge(ctx, 4);
                                    a0 = s4;
                                    jal(ctx, 0x4DF704u, gen::fn_sub_4CDE90_004cde90);
                                    v0 = 0;
                                }
                            }
                            // 0x004df794 (the shared epilogue, written out on this path)
                            charge(ctx, 8);
                            ld(ra, sp, 0x50);
                            lq(s4, sp, 0x40);
                            lq(s3, sp, 0x30);
                            lq(s2, sp, 0x20);
                            lq(s1, sp, 0x10);
                            lq(s0, sp, 0x0);
                            sp = addiu(sp, 0xC0);
                            return;
                        }
                    L_004df748:
                        charge(ctx, 10);
                        v1 = 1;
                        v0 = lui(0x8000);
                        sw(v1, sp, 0xB0);
                        a0 = v0 | 0x4;
                        jal(ctx, 0x4DF754u, gen::fn_sub_4C1D10_004c1d10);
                        sw(v0, sp, 0xB4);
                        a0 = addiu(sp, 0xB0);
                        jal(ctx, 0x4DF760u, gen::fn_sub_4C1C50_004c1c50);
                        v0 = 0;
                    }
                }
            }
            // 0x004df794 (the shared epilogue, written out on this path)
            charge(ctx, 8);
            ld(ra, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0xC0);
            return;
        }
    L_004df770:
        charge(ctx, 9);
        v1 = 1;
        v0 = lui(0x8000);
        sw(v1, sp, 0xA8);
        a0 = v0 | 0x4;
        jal(ctx, 0x4DF77Cu, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0xAC);
        a0 = addiu(sp, 0xA8);
        jal(ctx, 0x4DF788u, gen::fn_sub_4C1C50_004c1c50);
        v0 = 0;
    }
    // 0x004df794 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xC0);
}

// sub_4DF9D0 [skyTextureNativeStreamRead] -- reads a texture's PS2 native data: the struct (version 0x35000..0x37002,
//   the 'PS2' platform tag), the name and mask strings (sub_4C78A0), the raster (sub_4DF3F0), a texture (sub_4D0E40) with
//   its names and the filter / address modes (a missing V address copied from U); 1, or 0
// 0x004DF9D0 sub_4DF9D0 -- 716 bytes; frame 0x170: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4DF9D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004df9d0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x170);
    sd(ra, sp, 0x40);
    a2 = addiu(sp, 0x16C);
    sq(s3, sp, 0x30);
    a3 = addiu(sp, 0x168);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    s1 = a0;
    sw(zero, a1, 0);
    a1 = 1;
    jal(ctx, 0x4DF9FCu, gen::fn_sub_4C1600_004c1600);
    if (v0 == 0) {
        // 0x004dfac8
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004dfa0c
        charge(ctx, 6);
        lw(v1, sp, 0x168);
        v0 = 0x30000;
        v0 = v0 | 0x5000;
        v0 = sltu(v1, v0);
        s0 = 0;
        if (v0 == 0) {
            // 0x004dfa24
            charge(ctx, 5);
            at = 0x30000;
            at = at | 0x7003;
            at = sltu(v1, at);
            if (at != 0) {
                // 0x004dfa38
                charge(ctx, 1);
                s0 = 1;
            }
        }
        // 0x004dfa3c
        charge(ctx, 2);
        if (s0 == 0) {
            // 0x004dfc58
            charge(ctx, 10);
            v1 = 1;
            v0 = lui(0x8000);
            sw(v1, sp, 0x150);
            a0 = v0 | 0x4;
            jal(ctx, 0x4DFC64u, gen::fn_sub_4C1D10_004c1d10);
            sw(v0, sp, 0x154);
            a0 = addiu(sp, 0x150);
            jal(ctx, 0x4DFC70u, gen::fn_sub_4C1C50_004c1c50);
            backedge(ctx);
        L_004dfc08:
            charge(ctx, 2);
            v0 = s0;
        } else {
            // 0x004dfa44
            charge(ctx, 11);
            a0 = addiu(sp, 0x160);
            a1 = 0;
            a2 = 8;
            jal(ctx, 0x4DFA4Cu, gen::fn_memset_00521408);
            lw(s3, sp, 0x16C);
            a0 = s1;
            a1 = addiu(sp, 0x160);
            a2 = s3;
            jal(ctx, 0x4DFA60u, gen::fn_sub_4C5250_004c5250);
            if (s3 != v0) {
                // 0x004dfad0
                charge(ctx, 2);
                v0 = 0;
            } else {
                // 0x004dfa70
                charge(ctx, 4);
                lbu(v1, sp, 0x160);
                v0 = 80;
                if (v1 == v0) {
                    // 0x004dfa80
                    charge(ctx, 4);
                    lbu(v1, sp, 0x161);
                    v0 = 83;
                    if (v1 != v0) {
                        goto L_004dfad8;
                    }
                    // 0x004dfa90
                    charge(ctx, 4);
                    lbu(v1, sp, 0x162);
                    v0 = 50;
                    if (v1 != v0) {
                        goto L_004dfad8;
                    }
                    // 0x004dfaa0
                    charge(ctx, 3);
                    lbu(v0, sp, 0x163);
                    if (v0 != 0) {
                        goto L_004dfad8;
                    }
                    // 0x004dfaac
                    charge(ctx, 5);
                    a0 = addiu(sp, 0xD0);
                    a1 = s1;
                    jal(ctx, 0x4DFAB0u, gen::fn_sub_4C78A0_004c78a0);
                    if (v0 != 0) {
                        // 0x004dfae0
                        charge(ctx, 5);
                        a0 = addiu(sp, 0x50);
                        a1 = s1;
                        jal(ctx, 0x4DFAE4u, gen::fn_sub_4C78A0_004c78a0);
                        if (v0 != 0) {
                            // 0x004dfafc
                            charge(ctx, 7);
                            a0 = s1;
                            a1 = 1;
                            a2 = addiu(sp, 0x16C);
                            a3 = addiu(sp, 0x168);
                            jal(ctx, 0x4DFB08u, gen::fn_sub_4C1600_004c1600);
                            if (v0 == 0) {
                                // 0x004dfc10
                                charge(ctx, 2);
                                v0 = 0;
                            } else {
                                // 0x004dfb18
                                charge(ctx, 6);
                                lw(v1, sp, 0x168);
                                v0 = 0x30000;
                                v0 = v0 | 0x5000;
                                v0 = sltu(v1, v0);
                                if (v0 == 0) {
                                    // 0x004dfb30
                                    charge(ctx, 5);
                                    at = 0x30000;
                                    at = at | 0x7003;
                                    at = sltu(v1, at);
                                    if (at == 0) {
                                        goto L_004dfc20;
                                    }
                                    // 0x004dfb44
                                    charge(ctx, 6);
                                    lw(a1, sp, 0x16C);
                                    a0 = s1;
                                    jal(ctx, 0x4DFB48u, gen::fn_sub_4DF3F0_004df3f0);
                                    s1 = v0;
                                    if (s1 == 0) {
                                        // 0x004dfc18
                                        charge(ctx, 2);
                                        v0 = 0;
                                    } else {
                                        // 0x004dfb5c
                                        charge(ctx, 6);
                                        a0 = s1;
                                        jal(ctx, 0x4DFB5Cu, gen::fn_sub_4D0E40_004d0e40);
                                        sw(v0, s2, 0);
                                        lw(a0, s2, 0);
                                        if (a0 != 0) {
                                            // 0x004dfb74
                                            charge(ctx, 19);
                                            a1 = addiu(sp, 0xD0);
                                            jal(ctx, 0x4DFB74u, gen::fn_sub_4D0FD0_004d0fd0);
                                            lw(a0, s2, 0);
                                            a1 = addiu(sp, 0x50);
                                            jal(ctx, 0x4DFB80u, gen::fn_sub_4D1070_004d1070);
                                            lw(a0, s2, 0);
                                            a2 = addiu(sp, 0x164);
                                            lbu(a1, a2, 0);
                                            v0 = si(-256);
                                            lw(v1, a0, 80);
                                            v0 = v1 & v0;
                                            v0 = v0 | a1;
                                            sw(v0, a0, 80);
                                            lw(v0, a2, 0);
                                            v1 = sra(v0, 8);
                                            v0 = sra(v0, 12);
                                            v0 = v0 & 0xF;
                                            v1 = v1 & 0xF;
                                            if (v0 == 0) {
                                                // 0x004dfbc0
                                                charge(ctx, 1);
                                                v0 = v1;
                                            }
                                            // 0x004dfbc4
                                            charge(ctx, 17);
                                            lw(a3, s2, 0);
                                            v1 = sll(v1, 8);
                                            a0 = v1 & 0xF00;
                                            v0 = sll(v0, 12);
                                            v1 = lui(0xFFFF);
                                            a1 = si(-3841);
                                            v1 = v1 | 0xFFF;
                                            v0 = v0 & 0xF000;
                                            lw(a2, a3, 80);
                                            a1 = a2 & a1;
                                            a0 = a1 | a0;
                                            sw(a0, a3, 80);
                                            lw(a1, s2, 0);
                                            lw(a0, a1, 80);
                                            v1 = a0 & v1;
                                            v0 = v1 | v0;
                                            sw(v0, a1, 80);
                                            goto L_004dfc08;
                                        }
                                        // 0x004dfc48
                                        charge(ctx, 4);
                                        a0 = s1;
                                        jal(ctx, 0x4DFC48u, gen::fn_sub_4CDE90_004cde90);
                                        v0 = 0;
                                    }
                                    // 0x004dfc80 (the shared epilogue, written out on this path)
                                    charge(ctx, 7);
                                    ld(ra, sp, 0x40);
                                    lq(s3, sp, 0x30);
                                    lq(s2, sp, 0x20);
                                    lq(s1, sp, 0x10);
                                    lq(s0, sp, 0x0);
                                    sp = addiu(sp, 0x170);
                                    return;
                                }
                            L_004dfc20:
                                charge(ctx, 10);
                                v1 = 1;
                                v0 = lui(0x8000);
                                sw(v1, sp, 0x158);
                                a0 = v0 | 0x4;
                                jal(ctx, 0x4DFC2Cu, gen::fn_sub_4C1D10_004c1d10);
                                sw(v0, sp, 0x15C);
                                a0 = addiu(sp, 0x158);
                                jal(ctx, 0x4DFC38u, gen::fn_sub_4C1C50_004c1c50);
                                v0 = 0;
                            }
                        } else {
                            // 0x004dfaf4
                            charge(ctx, 2);
                            v0 = 0;
                        }
                    } else {
                        // 0x004dfac0
                        charge(ctx, 2);
                        v0 = 0;
                    }
                    // 0x004dfc80 (the shared epilogue, written out on this path)
                    charge(ctx, 7);
                    ld(ra, sp, 0x40);
                    lq(s3, sp, 0x30);
                    lq(s2, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x170);
                    return;
                }
            L_004dfad8:
                charge(ctx, 2);
                v0 = 0;
            }
        }
    }
    // 0x004dfc80 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x170);
}

// sub_4DFCA0 [skyReturnOne] -- returns 1 (an empty sky driver hook)
// 0x004DFCA0 sub_4DFCA0 -- 8 bytes; leaf frame (no stack)
void sub_4DFCA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x004dfca0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 1;
}

// sub_4DFCC0 [skyFillStandardTable] -- fills a device standard-function table: $a1 entries set to the default
//   sub_4DFCB0, then each of the $a3 {index, function} pairs of $a2 stored when its index is in range
// 0x004DFCC0 sub_4DFCC0 -- 264 bytes; leaf frame (no stack)
void sub_4DFCC0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x004dfcc0
    enter(ctx, 3);  // entry check point + this block's cycles
    at = slt(0, a1);
    t3 = 0;
    if (at != 0) {
        // 0x004dfccc
        charge(ctx, 3);
        at = slti(a1, 9);
        t1 = addiu(a1, -8);
        if (at == 0) {
            // 0x004dfcd8
            charge(ctx, 3);
            at = slt(a1, 0);
            v1 = 0;
            if (at == 0) {
                // 0x004dfce4
                charge(ctx, 5);
                at = 0x7FFF0000;
                at = at | 0xFFFF;
                at = slt(a1, at);
                if (at != 0) {
                    // 0x004dfcf8
                    charge(ctx, 1);
                    v1 = 1;
                }
            }
            // 0x004dfcfc
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x004dfd04
                charge(ctx, 3);
                t0 = 0x4E0000;
                t2 = a0;
                t0 = addiu(t0, -848);  // &sub_4DFCB0
                for (;;) {
                    // 0x004dfd10
                    charge(ctx, 12);
                    sw(t0, t2, 0);
                    t3 = addiu(t3, 8);
                    sw(t0, t2, 4);
                    v1 = slt(t3, t1);
                    sw(t0, t2, 8);
                    sw(t0, t2, 12);
                    sw(t0, t2, 16);
                    sw(t0, t2, 20);
                    sw(t0, t2, 24);
                    sw(t0, t2, 28);
                    t2 = addiu(t2, 32);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x004dfd40
        charge(ctx, 3);
        at = slt(t3, a1);
        if (at != 0) {
            // 0x004dfd4c
            charge(ctx, 4);
            v1 = sll(t3, 2);
            t0 = 0x4E0000;
            t1 = addu(a0, v1);
            t0 = addiu(t0, -848);  // &sub_4DFCB0
            for (;;) {
                // 0x004dfd5c
                charge(ctx, 7);
                t3 = addiu(t3, 1);
                sw(t0, t1, 0);
                v1 = slt(t3, a1);
                t1 = addiu(t1, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x004dfd78
    charge(ctx, 3);
    v1 = a3;
    a3 = addiu(a3, -1);
    if (v1 != 0) {
        for (;;) {
            // 0x004dfd84
            charge(ctx, 4);
            lw(v1, a2, 0);
            at = slt(v1, a1);
            if (at != 0) {
                // 0x004dfd94
                charge(ctx, 2);
                if (i64(v1) >= 0) {
                    // 0x004dfd9c
                    charge(ctx, 5);
                    lw(t0, a2, 4);
                    v1 = sll(v1, 2);
                    v1 = addu(a0, v1);
                    sw(t0, v1, 0);
                }
            }
            // 0x004dfdb0
            charge(ctx, 4);
            v1 = a3;
            a2 = addiu(a2, 8);
            a3 = addiu(a3, -1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004dfdc0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// sub_4E00E0 [skyPluginsAttach] -- attaches the sky driver's plugins: a 92-byte raster extension (gp 0x7CEAA8), a
//   216-byte camera extension (0x7CEAA4), a 272-byte texture extension (0x7CEAA0) with its stream callbacks (sub_4D83C0 /
//   sub_4D8440 / sub_4D84A0); 1 when all succeeded
// 0x004E00E0 sub_4E00E0 -- 208 bytes; frame 0x10: ra sp+0x0
void sub_4E00E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004e00e0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 92;
    sd(ra, sp, 0x0);
    a1 = 1036;
    a2 = 0;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x4E00F8u, gen::fn_sub_4CDF00_004cdf00);
    sw(v0, gp, -16968);  // 0x7CEAA8
    v0 = slt(v0, 0);
    v0 = v0 ^ 0x1;
    if (v0 != 0) {
        // 0x004e011c
        charge(ctx, 11);
        a0 = 216;
        a1 = 1036;
        a2 = 0;
        a3 = 0;
        t0 = 0;
        jal(ctx, 0x4E012Cu, gen::fn_sub_4CA000_004ca000);
        sw(v0, gp, -16972);  // 0x7CEAA4
        v0 = slt(v0, 0);
        v0 = v0 ^ 0x1;
        if (v0 != 0) {
            // 0x004e0148
            charge(ctx, 11);
            a0 = 0;
            a1 = 272;
            a2 = 0;
            a3 = 0;
            t0 = 0;
            jal(ctx, 0x4E0158u, gen::fn_sub_4D13B0_004d13b0);
            sw(v0, gp, -16976);  // 0x7CEAA0
            v0 = slt(v0, 0);
            v0 = v0 ^ 0x1;
            if (v0 == 0) {
                goto L_004e01a4;
            }
            // 0x004e0174
            charge(ctx, 12);
            a1 = 0x4E0000;
            a2 = 0x4E0000;
            a3 = 0x4E0000;
            a0 = 272;
            a1 = addiu(a1, -31808);  // &sub_4D83C0
            a2 = addiu(a2, -31680);  // &sub_4D8440
            a3 = addiu(a3, -31584);  // &sub_4D84A0
            jal(ctx, 0x4E018Cu, gen::fn_sub_4C81A0_004c81a0);
            sw(v0, gp, -16976);  // 0x7CEAA0
            v0 = slt(v0, 0);
            v0 = v0 ^ 0x1;
            backedge(ctx);
            goto L_004e0114;
        }
    L_004e01a4:
        charge(ctx, 1);
        ld(ra, sp, 0x0);
        // 0x004e01a8 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_004e0114:
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    // 0x004e01a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// SkySystem -- the sky driver's device-control entry (the engine's system request $a0): 0 open (SkyOpen), 1 / 8 / 9
//   nothing, 2 start (SkyStart), 3 stop (the DMA closed, the post-flip chain cleared, the texture cache closed
//   sub_4F0AD0, the started flags cleared), 4 the device's standard function table copied (7 pairs from
//   sceLibgcc32GetErxEntries_2) and the device id kept, 5 the mode count (90), 6 a video mode's record (the custom mode
//   for -1), 7 use a mode (SkyUseMode), 10 the current mode, 11 the standard functions table (sub_4DFCC0 with 28 entries
//   at 0x77F010), 12 the texture memory size, 17 the pipelines overloaded and the frame / scratch rasters made
//   (sub_4E40B0 / sub_4E3550) with the VU0 transforms installed (sub_4C2A30 / sub_4C68C0) or released (sub_4EEC10), the
//   identity matrix and the frame stamp, 18 the rasters released (sub_4E4130 / sub_4E3090 / sub_4EEC10), 19 1024, 22 the
//   halfword 6; 1 / 0
// 0x004E2B70 SkySystem -- 904 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void SkySystem(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x004e2b70
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    at = sltiu(a0, 23);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    s0 = a2;
    if (at != 0) {
        // 0x004e2b90
        charge(ctx, 7);
        v1 = 0x7C0000;
        v0 = sll(a0, 2);
        v1 = addiu(v1, -12608);  // &0x7BCEC0
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x4E2BACu:  // table[7]
            // 0x004e2bac
            charge(ctx, 4);
            a0 = a3;
            jal(ctx, 0x4E2BACu, gen::fn_SkyUseMode_004dff20);
        L_004e2e8c:
            charge(ctx, 2);
            ld(ra, sp, 0x20);
            break;
        case 0x4E2BBCu:  // table[5]
            // 0x004e2bbc
            charge(ctx, 4);
            v1 = 90;
            v0 = 1;
            sw(v1, s1, 0);
            goto L_004e2e8c;
        case 0x4E2BCCu:  // table[6]
            // 0x004e2bcc
            charge(ctx, 3);
            v0 = slti(a3, 90);
            if (v0 != 0) {
                // 0x004e2bd8
                charge(ctx, 2);
                v0 = slti(a3, -1);
                v0 = v0 ^ 0x1;
            }
            // 0x004e2be0
            charge(ctx, 2);
            if (v0 != 0) {
                // 0x004e2be8
                charge(ctx, 2);
                if (i64(a3) < 0) {
                    // 0x004e2e94
                    charge(ctx, 18);
                    a0 = 0x960000;
                    v1 = 0x960000;
                    lwc1(f3, a0, 22320);  // customMode
                    lwc1(f2, v1, 22324);  // customMode+0x4
                    a0 = 0x960000;
                    v1 = 0x960000;
                    lwc1(f1, a0, 22328);  // customMode+0x8
                    lwc1(f0, v1, 22332);  // customMode+0xC
                    a0 = 0x960000;
                    swc1(f3, s1, 0);
                    v1 = 0x960000;
                    swc1(f2, s1, 4);
                    swc1(f1, s1, 8);
                    swc1(f0, s1, 12);
                    lwc1(f1, a0, 22336);  // customMode+0x10
                    lwc1(f0, v1, 22340);  // customMode+0x14
                    swc1(f1, s1, 16);
                    swc1(f0, s1, 20);
                } else {
                    // 0x004e2bf0
                    charge(ctx, 19);
                    a0 = sll(a3, 1);
                    v1 = 0x780000;
                    a0 = addu(a0, a3);
                    v1 = addiu(v1, -6384);  // &videoModes
                    a0 = sll(a0, 3);
                    v1 = addu(v1, a0);
                    lwc1(f3, v1, 0);
                    lwc1(f2, v1, 4);
                    lwc1(f1, v1, 8);
                    lwc1(f0, v1, 12);
                    swc1(f3, s1, 0);
                    swc1(f2, s1, 4);
                    swc1(f1, s1, 8);
                    swc1(f0, s1, 12);
                    lwc1(f1, v1, 16);
                    lwc1(f0, v1, 20);
                    swc1(f1, s1, 16);
                    swc1(f0, s1, 20);
                }
                // 0x004e2edc
                charge(ctx, 2);
                backedge(ctx);
                goto L_004e2e8c;
            }
        L_004e2ee4:
            charge(ctx, 1);
            ld(ra, sp, 0x20);
            break;
        case 0x4E2C3Cu:  // table[10]
            // 0x004e2c3c
            charge(ctx, 4);
            lw(v1, gp, -16928);  // 0x7CEAD0
            v0 = 1;
            sw(v1, s1, 0);
            goto L_004e2e8c;
        case 0x4E2C4Cu:  // table[8]
            // 0x004e2c4c
            charge(ctx, 2);
            v0 = 1;
            goto L_004e2e8c;
        case 0x4E2C54u:  // table[4]
            // 0x004e2c54
            charge(ctx, 3);
            jal(ctx, 0x4E2C54u, gen::fn_sceLibgcc32GetErxEntries_2_004e2f00);
            a1 = 7;
            for (;;) {
                // 0x004e2c60
                charge(ctx, 8);
                lw(a0, v0, 0);
                a1 = addiu(a1, -1);
                lw(v1, v0, 4);
                sw(a0, s1, 0);
                v0 = addiu(v0, 8);
                sw(v1, s1, 4);
                s1 = addiu(s1, 8);
                if (i64(a1) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004e2c80
            charge(ctx, 3);
            sw(s0, gp, -16940);  // 0x7CEAC4
            v0 = 1;
            goto L_004e2e8c;
        case 0x4E2C8Cu:  // table[0]
            // 0x004e2c8c
            charge(ctx, 4);
            jal(ctx, 0x4E2C8Cu, gen::fn_SkyOpen_004e01b0);
            goto L_004e2e8c;
        case 0x4E2C9Cu:  // table[1]
            // 0x004e2c9c
            charge(ctx, 2);
            v0 = 1;
            goto L_004e2e8c;
        case 0x4E2CA4u:  // table[2]
            // 0x004e2ca4
            charge(ctx, 4);
            jal(ctx, 0x4E2CA4u, gen::fn_SkyStart_004e1060);
            goto L_004e2e8c;
        case 0x4E2CB4u:  // table[3]
            // 0x004e2cb4
            charge(ctx, 16);
            jal(ctx, 0x4E2CB4u, gen::fn__rwDMADmaClose_004d6a50);
            v1 = 0x960000;
            v0 = 0x960000;
            sw(zero, v1, 19804);  // rwDMAFlipData+0x3CC
            sw(zero, v0, 19800);  // rwDMAFlipData+0x3C8
            v1 = 0x960000;
            v0 = 0x960000;
            sw(zero, v1, 19796);  // rwDMAFlipData+0x3C4
            link(ctx, 0x4E2CD8u);  // $ra first: the delay slot below depends on it
            sw(zero, v0, 19792);
            call(ctx, gen::fn_sub_4F0AD0_004f0ad0);
            v0 = 1;
            sw(zero, gp, -16936);  // 0x7CEAC8
            sw(zero, gp, -17116);  // 0x7CEA14
            sw(v0, gp, -20276);  // 0x7CDDBC
            goto L_004e2e8c;
        case 0x4E2CF4u:  // table[17]
            // 0x004e2cf4
            charge(ctx, 7);
            jal(ctx, 0x4E2CF4u, gen::fn__rwSkyOverloadPipelines_004eebc0);
            jal(ctx, 0x4E2CFCu, gen::fn_sub_4E40B0_004e40b0);
            s0 = sltu(0, v0);
            if (s0 != 0) {
                // 0x004e2d10
                charge(ctx, 3);
                jal(ctx, 0x4E2D10u, gen::fn_sub_4E3550_004e3550);
                s0 = sltu(0, v0);
            }
            // 0x004e2d1c
            charge(ctx, 2);
            if (s0 != 0) {
                // 0x004e2d34
                charge(ctx, 13);
                a0 = 0x4E0000;
                a0 = addiu(a0, 15936);  // &sub_4E3E40
                jal(ctx, 0x4E2D38u, gen::fn_sub_4C2A30_004c2a30);
                a0 = 0x4E0000;
                a1 = 0x4E0000;
                a2 = 0x4E0000;
                a3 = 0x4E0000;
                a0 = addiu(a0, 16064);  // &sub_4E3EC0
                a1 = addiu(a1, 16160);  // &sub_4E3F20
                a2 = addiu(a2, 16320);  // &sub_4E3FC0
                a3 = addiu(a3, 16416);  // &sub_4E4020
                jal(ctx, 0x4E2D5Cu, gen::fn_sub_4C68C0_004c68c0);
                a1 = 0x3F800000;
            } else {
                // 0x004e2d24
                charge(ctx, 4);
                jal(ctx, 0x4E2D24u, gen::fn_sub_4EEC10_004eec10);
                a1 = 0x3F800000;
            }
            // 0x004e2d68
            charge(ctx, 36);
            v1 = 0x960000;
            sw(a1, v1, 21336);  // 0x965358
            a0 = 0x960000;
            v1 = 0x960000;
            sw(a1, a0, 21316);  // 0x965344
            sw(a1, v1, 21296);  // 0x965330
            a0 = 0x960000;
            v1 = 0x960000;
            sw(zero, a0, 21312);  // 0x965340
            sw(zero, v1, 21304);  // 0x965338
            a0 = 0x960000;
            v1 = 0x960000;
            sw(zero, a0, 21300);  // 0x965334
            sw(zero, v1, 21332);  // 0x965354
            a0 = 0x960000;
            v1 = 0x960000;
            sw(zero, a0, 21328);  // 0x965350
            sw(zero, v1, 21320);  // 0x965348
            a0 = 0x960000;
            v1 = 0x960000;
            sw(zero, a0, 21352);  // 0x965368
            sw(zero, v1, 21348);  // 0x965364
            a0 = 0x960000;
            v1 = 0x960000;
            sw(zero, a0, 21344);  // 0x965360
            lw(a2, v1, 21308);  // 0x96533C
            a0 = 0x20000;
            a1 = a0 | 0x3;
            v0 = s0;
            a0 = lui(0xDEAD);
            a0 = a0 | 0xDEAD;
            sw(a0, gp, -16984);  // 0x7CEA98
            v1 = 0x960000;
            a0 = a2 | a1;
            sw(a0, v1, 21308);  // 0x96533C
            goto L_004e2e8c;
        case 0x4E2DF8u:  // table[18]
            // 0x004e2df8
            charge(ctx, 8);
            jal(ctx, 0x4E2DF8u, gen::fn_sub_4E4130_004e4130);
            jal(ctx, 0x4E2E00u, gen::fn_sub_4E3090_004e3090);
            jal(ctx, 0x4E2E08u, gen::fn_sub_4EEC10_004eec10);
            v0 = 1;
            goto L_004e2e8c;
        case 0x4E2E18u:  // table[19]
            // 0x004e2e18
            charge(ctx, 4);
            v1 = 1024;
            v0 = 1;
            sw(v1, s1, 0);
            goto L_004e2e8c;
        case 0x4E2E28u:  // table[12]
            // 0x004e2e28
            charge(ctx, 3);
            lw(v0, gp, -16936);  // 0x7CEAC8
            if (v0 == 0) {
                goto L_004e2ee4;
            }
            // 0x004e2e34
            charge(ctx, 7);
            lw(v1, gp, -16980);  // g_skyTexCacheStartWord
            a0 = 0x100000;
            v1 = subu(a0, v1);
            v1 = sll(v1, 2);
            sw(v1, s1, 0);
            goto L_004e2e8c;
        case 0x4E2E50u:  // table[9]
            // 0x004e2e50
            charge(ctx, 2);
            v0 = 1;
            goto L_004e2e8c;
        case 0x4E2E58u:  // table[11]
            // 0x004e2e58
            charge(ctx, 8);
            a1 = a3;
            a2 = 0x780000;
            a0 = s1;
            a2 = addiu(a2, -4080);  // &0x77F010
            a3 = 28;
            jal(ctx, 0x4E2E68u, gen::fn_sub_4DFCC0_004dfcc0);
            v0 = 1;
            goto L_004e2e8c;
        case 0x4E2E78u:  // table[22]
            // 0x004e2e78
            charge(ctx, 4);
            v1 = 6;
            v0 = 1;
            sh(v1, s1, 0);
            goto L_004e2e8c;
        case 0x4E2E88u:  // table[13, 14, 15, 16, 20, 21]
        L_004e2e88:
            charge(ctx, 1);
            v0 = 0;
            goto L_004e2e8c;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
        // 0x004e2ee8 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
    goto L_004e2e88;
}

// sceLibgcc32GetErxEntries_2 -- returns the address of the sky device's standard-function block 0x77F0F0 (a FLIRT-named
//   three-instruction getter)
// 0x004E2F00 sceLibgcc32GetErxEntries_2 -- 12 bytes; leaf frame (no stack)
void sceLibgcc32GetErxEntries_2(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x004e2f00
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x780000;
    v0 = addiu(v0, -3856);  // &0x77F0F0
}

// sub_4E3090 [skyDestroyFrameRasters] -- releases the sky driver's frame-buffer and Z-buffer rasters (0x7CEA74 /
//   0x7CEA70, sub_4CDE90) when the engine is started; the started flag
// 0x004E3090 sub_4E3090 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
void sub_4E3090(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004e3090
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, gp, -16936);  // 0x7CEAC8
    if (s0 != 0) {
        // 0x004e30a8
        charge(ctx, 3);
        lw(a0, gp, -17020);  // 0x7CEA74
        if (a0 != 0) {
            // 0x004e30b4
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x004e30bc
                charge(ctx, 2);
                jal(ctx, 0x4E30BCu, gen::fn_sub_4CDE90_004cde90);
            }
            // 0x004e30c4
            charge(ctx, 1);
            sw(zero, gp, -17020);  // 0x7CEA74
        }
        // 0x004e30c8
        charge(ctx, 3);
        lw(a0, gp, -17024);  // 0x7CEA70
        if (a0 != 0) {
            // 0x004e30d4
            charge(ctx, 2);
            if (a0 != 0) {
                // 0x004e30dc
                charge(ctx, 2);
                jal(ctx, 0x4E30DCu, gen::fn_sub_4CDE90_004cde90);
            }
            // 0x004e30e4
            charge(ctx, 1);
            sw(zero, gp, -17024);  // 0x7CEA70
        }
    }
    // 0x004e30e8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// sub_4E3550 [skyCreateFrameRasters] -- makes the sky driver's frame-buffer and Z-buffer rasters when the engine is
//   started: the two display and draw buffer base words taken from the flip data's FRAME / DISPFB registers,
//   SkyCreateFBRaster / SkyCreateDBRaster, then sub_4E2F10; 1, or 0
// 0x004E3550 sub_4E3550 -- 224 bytes; frame 0x10: ra sp+0x0
void sub_4E3550(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004e3550
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, -16936);  // 0x7CEAC8
    if (v0 != 0) {
        // 0x004e356c
        charge(ctx, 46);
        v0 = 0x960000;
        v1 = 0x960000;
        ld(t0, v0, 18928);  // rwDMAFlipData+0x60
        a2 = 0x960000;
        sw(zero, v1, 22288);  // 0x965710
        a1 = 0x960000;
        a0 = 0x960000;
        v0 = 0x960000;
        sw(zero, v0, 22304);  // 0x965720
        v0 = 0x960000;
        ld(a3, v0, 19296);  // rwDMAFlipData+0x1D0
        v0 = 0x960000;
        a3 = a3 & 0x1FF;
        ld(v1, v0, 18848);  // rwDMAFlipData+0x10
        v0 = 0x960000;
        sw(zero, v0, 22272);  // 0x965700
        v0 = t0 & 0x1FF;
        t0 = dsll(v0, 11);
        t0 = dsll32(t0, 0);
        v0 = 0x960000;
        t0 = dsra32(t0, 0);
        sw(t0, a2, 22308);  // 0x965724
        a2 = dsll(a3, 11);
        a3 = dsll32(a2, 0);
        ld(a2, v0, 18888);  // rwDMAFlipData+0x38
        a3 = dsra32(a3, 0);
        sw(a3, a1, 22292);  // 0x965714
        v0 = v1 & 0x1FF;
        v0 = dsll(v0, 11);
        v1 = 0x960000;
        a1 = dsll32(v0, 0);
        v0 = 0x960000;
        a1 = dsra32(a1, 0);
        sw(zero, v0, 22256);  // 0x9656F0
        v0 = a2 & 0x1FF;
        sw(a1, a0, 22276);  // 0x965704
        v0 = dsll(v0, 11);
        v0 = dsll32(v0, 0);
        v0 = dsra32(v0, 0);
        link(ctx, 0x4E3608u);  // $ra first: the delay slot below depends on it
        sw(v0, v1, 22260);
        call(ctx, gen::fn_SkyCreateFBRaster_004e3100);
        link(ctx, 0x4E3610u);  // $ra first: the delay slot below depends on it
        sw(v0, gp, -17020);  // 0x7CEA74
        call(ctx, gen::fn_SkyCreateDBRaster_004e3320);
        link(ctx, 0x4E3618u);  // $ra first: the delay slot below depends on it
        sw(v0, gp, -17024);  // 0x7CEA70
        call(ctx, gen::fn_sub_4E2F10_004e2f10);
        v0 = 1;
    } else {
        // 0x004e3564
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004e3624 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// sub_4E40B0 [skyCreateScratchRasters] -- makes the sky driver's two empty type-128 rasters (0x7CEAE8 / 0x7CEAEC,
//   RwRasterCreate), the current raster cleared; 1, or 0 (the first released when the second fails)
// 0x004E40B0 sub_4E40B0 -- 116 bytes; frame 0x10: ra sp+0x0
void sub_4E40B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004e40b0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0;
    sd(ra, sp, 0x0);
    a1 = 0;
    a2 = 0;
    a3 = 128;
    link(ctx, 0x4E40C8u);  // $ra first: the delay slot below depends on it
    sw(zero, gp, -16896);  // 0x7CEAF0
    call(ctx, gen::fn_sub_4CE0F0_004ce0f0);
    sw(v0, gp, -16904);  // 0x7CEAE8
    if (v0 == 0) {
        // 0x004e4100
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004e40d8
        charge(ctx, 7);
        a0 = 0;
        a1 = 0;
        a2 = 0;
        a3 = 128;
        jal(ctx, 0x4E40E4u, gen::fn_sub_4CE0F0_004ce0f0);
        sw(v0, gp, -16900);  // 0x7CEAEC
        if (v0 == 0) {
            // 0x004e4108
            charge(ctx, 4);
            link(ctx, 0x4E4108u);  // $ra first: the delay slot below depends on it
            lw(a0, gp, -16904);  // 0x7CEAE8
            call(ctx, gen::fn_sub_4CDE90_004cde90);
            sw(zero, gp, -16904);  // 0x7CEAE8
            v0 = 0;
        } else {
            // 0x004e40f4
            charge(ctx, 3);
            sw(zero, gp, -16912);  // 0x7CEAE0
            v0 = 1;
        }
    }
    // 0x004e4118 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// sub_4E4130 [skyDestroyScratchRasters] -- releases the sky driver's two scratch rasters (sub_4CDE90) and clears their
//   slots
// 0x004E4130 sub_4E4130 -- 68 bytes; frame 0x10: ra sp+0x0
void sub_4E4130(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004e4130
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, gp, -16904);  // 0x7CEAE8
    if (a0 != 0) {
        // 0x004e4144
        charge(ctx, 3);
        jal(ctx, 0x4E4144u, gen::fn_sub_4CDE90_004cde90);
        sw(zero, gp, -16904);  // 0x7CEAE8
    }
    // 0x004e4150
    charge(ctx, 3);
    lw(a0, gp, -16900);  // 0x7CEAEC
    if (a0 != 0) {
        // 0x004e415c
        charge(ctx, 3);
        jal(ctx, 0x4E415Cu, gen::fn_sub_4CDE90_004cde90);
        sw(zero, gp, -16900);  // 0x7CEAEC
    }
    // 0x004e4168 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// sub_4E98A0 [skyRasterFormatFromImage] -- the sky driver's raster set-up from an image: width / height and type /
//   flags from $a1 / $a2; a Z buffer gets no format, a camera raster the display depth's (0x500 / 0x100), a texture the
//   format from the image's alpha class (sub_4D1900) and the frame depth, the palette bits for 4 / 8-bit images, its size
//   rounded up to powers of two (sub_4D6B60) up to 1024, a normal raster the format bits given (at least 1); 1, or 0 for
//   another type
// 0x004E98A0 sub_4E98A0 -- 504 bytes; frame 0x70: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4E98A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004e98a0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v1 = si(-8);
    sd(ra, sp, 0x40);
    a3 = a2 & 0x7;
    sq(s3, sp, 0x30);
    v1 = a2 & v1;
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    v0 = 1;
    lw(t0, a1, 4);
    sw(t0, a0, 12);
    lw(a1, a1, 8);
    sw(a1, a0, 16);
    sw(zero, a0, 20);
    sb(a3, a0, 32);
    sb(v1, a0, 33);
    lbu(a0, a0, 32);
    s1 = a2 & 0x9000;
    if (a0 != v0) {
        // 0x004e98f8
        charge(ctx, 3);
        v1 = 2;
        if (a0 != v1) {
            // 0x004e9904
            charge(ctx, 3);
            v1 = 5;
            if (a0 == v1) {
                goto L_004e9a14;
            }
            // 0x004e9910
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x004e99f4
                charge(ctx, 6);
                v1 = a2 & 0xF00;
                v1 = sra(v1, 8);
                sb(v1, s3, rw9::raster::kFormat);
                lbu(v1, s3, rw9::raster::kFormat);
                if (v1 == 0) {
                    // 0x004e9a74
                    charge(ctx, 2);
                    sb(v0, s3, rw9::raster::kFormat);
                    backedge(ctx);
                }
                // 0x004e9a0c
                charge(ctx, 2);
                v0 = 1;
                goto L_004e9a7c;
            }
            // 0x004e9918
            charge(ctx, 3);
            v0 = 4;
            if (a0 == v0) {
                // 0x004e992c
                charge(ctx, 11);
                a0 = s2;
                jal(ctx, 0x4E992Cu, gen::fn_sub_4D1900_004d1900);
                s0 = v0;
                jal(ctx, 0x4E9934u, gen::fn_sub_4CA5B0_004ca5b0);
                a1 = v0;
                a0 = addiu(sp, 0x50);
                jal(ctx, 0x4E9940u, gen::fn_sub_4CA560_004ca560);
                lw(v1, sp, 0x58);
                v0 = 16;
                a0 = 1280;
                if (v1 == v0) {
                    // 0x004e9958
                    charge(ctx, 3);
                    v0 = 3;
                    if (s0 != v0) {
                        // 0x004e9964
                        charge(ctx, 1);
                        a0 = 256;
                    }
                }
                // 0x004e9968
                charge(ctx, 4);
                lw(v1, s2, rw9::image::kDepth);
                v0 = 4;
                if (v1 == v0) {
                    // 0x004e9a54
                    charge(ctx, 2);
                    a0 = a0 | 0x4000;
                    backedge(ctx);
                } else {
                    // 0x004e9978
                    charge(ctx, 3);
                    v0 = 8;
                    if (v1 == v0) {
                        // 0x004e9984
                        charge(ctx, 1);
                        a0 = a0 | 0x2000;
                    }
                }
                // 0x004e9988
                charge(ctx, 16);
                v1 = sra(a0, 8);
                v0 = srl(s1, 8);
                sb(v1, s3, rw9::raster::kFormat);
                v1 = v0 & 0xFF;
                lbu(v0, s3, rw9::raster::kFormat);
                v0 = v0 | v1;
                sb(v0, s3, rw9::raster::kFormat);
                link(ctx, 0x4E99A4u);  // $ra first: the delay slot below depends on it
                lw(a0, s2, rw9::image::kWidth);
                call(ctx, gen::fn_sub_4D6B60_004d6b60);
                v1 = 1;
                v0 = sllv(v1, v0);
                sw(v0, s3, rw9::raster::kWidth);
                lw(v0, s3, rw9::raster::kWidth);
                at = slti(v0, 1025);
                if (at == 0) {
                    // 0x004e9a5c
                    charge(ctx, 3);
                    v0 = 1024;
                    sw(v0, s3, rw9::raster::kWidth);
                    backedge(ctx);
                }
                // 0x004e99c8
                charge(ctx, 9);
                link(ctx, 0x4E99C8u);  // $ra first: the delay slot below depends on it
                lw(a0, s2, rw9::image::kHeight);
                call(ctx, gen::fn_sub_4D6B60_004d6b60);
                v1 = 1;
                v0 = sllv(v1, v0);
                sw(v0, s3, rw9::raster::kHeight);
                lw(v0, s3, rw9::raster::kHeight);
                at = slti(v0, 1025);
                if (at == 0) {
                    // 0x004e9a68
                    charge(ctx, 3);
                    v0 = 1024;
                    sw(v0, s3, rw9::raster::kHeight);
                    backedge(ctx);
                }
                // 0x004e99ec
                charge(ctx, 2);
                v0 = 1;
                goto L_004e9a7c;
            }
            // 0x004e9924
            charge(ctx, 2);
            v0 = 0;
            // 0x004e9a4c
            charge(ctx, 2);
            ld(ra, sp, 0x40);
            // 0x004e9a80 (the shared epilogue, written out on this path)
            charge(ctx, 6);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x70);
            return;
        }
    L_004e9a14:
        charge(ctx, 5);
        lw(v1, gp, -17120);  // 0x7CEA10
        v0 = 32;
        lw(v1, v1, 8);
        if (v1 != v0) {
            // 0x004e9a30
            charge(ctx, 1);
            v0 = 256;
        } else {
            // 0x004e9a28
            charge(ctx, 2);
            v0 = 1280;
        }
        // 0x004e9a34
        charge(ctx, 4);
        v1 = sra(v0, 8);
        v0 = 1;
        sb(v1, s3, rw9::raster::kFormat);
        goto L_004e9a7c;
    }
    // 0x004e9a44
    charge(ctx, 2);
    sb(zero, s3, rw9::raster::kFormat);
L_004e9a7c:
    charge(ctx, 1);
    ld(ra, sp, 0x40);
    // 0x004e9a80 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// sub_4EAC00 [skyRasterWritePalette] -- writes a palette into a raster's palette memory (+8) in the GS CLUT layout by
//   the raster's format: 256 entries swizzled (the 0x7BCF60 table) or 16 entries, as 32-bit (alpha halved: 8421505 x a &
//   0xFF000000) or 16-bit 1555 colours; the data cache written back (SyncDCache)
// 0x004EAC00 sub_4EAC00 -- 3028 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4EAC00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004eac00
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 37;
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lbu(a2, a0, 35);
    a2 = a2 & 0x6F;
    if (a2 != v1) {
        // 0x004eac24
        charge(ctx, 3);
        v1 = 33;
        if (a2 != v1) {
            // 0x004eac30
            charge(ctx, 3);
            v1 = 32;
            if (a2 == v1) {
                goto L_004eb0d4;
            }
            // 0x004eac3c
            charge(ctx, 3);
            v1 = 69;
            if (a2 == v1) {
                // 0x004eae7c
                charge(ctx, 3);
                lw(a2, a0, 8);
                v1 = 0;
                v0 = lui(0xFF00);
                for (;;) {
                    // 0x004eae88
                    charge(ctx, 141);
                    lbu(t3, a1, 2);
                    v1 = addiu(v1, 8);
                    lbu(t2, a1, 1);
                    a3 = slti(v1, 16);
                    lbu(t0, a1, 0);
                    lbu(t1, a1, 3);
                    t3 = sll(t3, 16);
                    t2 = sll(t2, 8);
                    t2 = t3 | t2;
                    t2 = t0 | t2;
                    t0 = sll(t1, 8);
                    t0 = addu(t0, t1);
                    t0 = sll(t0, 8);
                    t0 = addu(t0, t1);
                    t0 = sll(t0, 7);
                    t0 = addu(t0, t1);
                    t0 = t0 & v0;
                    t0 = t2 | t0;
                    sw(t0, a2, 0);
                    lbu(t3, a1, 6);
                    lbu(t2, a1, 5);
                    lbu(t0, a1, 4);
                    lbu(t1, a1, 7);
                    t3 = sll(t3, 16);
                    t2 = sll(t2, 8);
                    t2 = t3 | t2;
                    t2 = t0 | t2;
                    t0 = sll(t1, 8);
                    t0 = addu(t0, t1);
                    t0 = sll(t0, 8);
                    t0 = addu(t0, t1);
                    t0 = sll(t0, 7);
                    t0 = addu(t0, t1);
                    t0 = t0 & v0;
                    t0 = t2 | t0;
                    sw(t0, a2, 4);
                    lbu(t3, a1, 10);
                    lbu(t2, a1, 9);
                    lbu(t0, a1, 8);
                    lbu(t1, a1, 11);
                    t3 = sll(t3, 16);
                    t2 = sll(t2, 8);
                    t2 = t3 | t2;
                    t2 = t0 | t2;
                    t0 = sll(t1, 8);
                    t0 = addu(t0, t1);
                    t0 = sll(t0, 8);
                    t0 = addu(t0, t1);
                    t0 = sll(t0, 7);
                    t0 = addu(t0, t1);
                    t0 = t0 & v0;
                    t0 = t2 | t0;
                    sw(t0, a2, 8);
                    lbu(t3, a1, 14);
                    lbu(t2, a1, 13);
                    lbu(t0, a1, 12);
                    lbu(t1, a1, 15);
                    t3 = sll(t3, 16);
                    t2 = sll(t2, 8);
                    t2 = t3 | t2;
                    t2 = t0 | t2;
                    t0 = sll(t1, 8);
                    t0 = addu(t0, t1);
                    t0 = sll(t0, 8);
                    t0 = addu(t0, t1);
                    t0 = sll(t0, 7);
                    t0 = addu(t0, t1);
                    t0 = t0 & v0;
                    t0 = t2 | t0;
                    sw(t0, a2, 12);
                    lbu(t3, a1, 18);
                    lbu(t2, a1, 17);
                    lbu(t0, a1, 16);
                    lbu(t1, a1, 19);
                    t3 = sll(t3, 16);
                    t2 = sll(t2, 8);
                    t2 = t3 | t2;
                    t2 = t0 | t2;
                    t0 = sll(t1, 8);
                    t0 = addu(t0, t1);
                    t0 = sll(t0, 8);
                    t0 = addu(t0, t1);
                    t0 = sll(t0, 7);
                    t0 = addu(t0, t1);
                    t0 = t0 & v0;
                    t0 = t2 | t0;
                    sw(t0, a2, 16);
                    lbu(t3, a1, 22);
                    lbu(t2, a1, 21);
                    lbu(t0, a1, 20);
                    lbu(t1, a1, 23);
                    t3 = sll(t3, 16);
                    t2 = sll(t2, 8);
                    t2 = t3 | t2;
                    t2 = t0 | t2;
                    t0 = sll(t1, 8);
                    t0 = addu(t0, t1);
                    t0 = sll(t0, 8);
                    t0 = addu(t0, t1);
                    t0 = sll(t0, 7);
                    t0 = addu(t0, t1);
                    t0 = t0 & v0;
                    t0 = t2 | t0;
                    sw(t0, a2, 20);
                    lbu(t3, a1, 26);
                    lbu(t2, a1, 25);
                    lbu(t0, a1, 24);
                    lbu(t1, a1, 27);
                    t3 = sll(t3, 16);
                    t2 = sll(t2, 8);
                    t2 = t3 | t2;
                    t2 = t0 | t2;
                    t0 = sll(t1, 8);
                    t0 = addu(t0, t1);
                    t0 = sll(t0, 8);
                    t0 = addu(t0, t1);
                    t0 = sll(t0, 7);
                    t0 = addu(t0, t1);
                    t0 = t0 & v0;
                    t0 = t2 | t0;
                    sw(t0, a2, 24);
                    lbu(t3, a1, 30);
                    lbu(t2, a1, 29);
                    lbu(t0, a1, 28);
                    lbu(t1, a1, 31);
                    t3 = sll(t3, 16);
                    t2 = sll(t2, 8);
                    t2 = t3 | t2;
                    t2 = t0 | t2;
                    a1 = addiu(a1, 32);
                    t0 = sll(t1, 8);
                    t0 = addu(t0, t1);
                    t0 = sll(t0, 8);
                    t0 = addu(t0, t1);
                    t0 = sll(t0, 7);
                    t0 = addu(t0, t1);
                    t0 = t0 & v0;
                    t0 = t2 | t0;
                    sw(t0, a2, 28);
                    a2 = addiu(a2, 32);
                    if (a3 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004eb0bc
                charge(ctx, 6);
                lw(a0, a0, 8);
                v0 = addiu(a0, 64);
                a1 = addiu(v0, 127);
                jal(ctx, 0x4EB0C4u, gen::fn_SyncDCache_00503a58);
                goto L_004eb7c0;
            }
            // 0x004eac48
            charge(ctx, 3);
            v1 = 65;
            if (a2 != v1) {
                // 0x004eac54
                charge(ctx, 3);
                v1 = 64;
                if (a2 == v1) {
                    goto L_004eac68;
                }
                // 0x004eac60
                charge(ctx, 2);
                ld(ra, sp, 0x20);
                // 0x004eb7c4 (the shared epilogue, written out on this path)
                charge(ctx, 4);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x30);
                return;
            }
        L_004eac68:
            charge(ctx, 2);
            lw(v0, a0, 8);
            v1 = 0;
            for (;;) {
                // 0x004eac70
                charge(ctx, 125);
                lbu(t2, a1, 2);
                v1 = addiu(v1, 8);
                lbu(t1, a1, 1);
                a2 = slti(v1, 16);
                lbu(t0, a1, 0);
                lbu(a3, a1, 3);
                t2 = sll(t2, 7);
                t1 = sll(t1, 2);
                t2 = t2 & 0x7C00;
                t1 = t1 & 0x3E0;
                t0 = srl(t0, 3);
                t1 = t2 | t1;
                a3 = sll(a3, 8);
                t0 = t0 | t1;
                a3 = a3 & 0x8000;
                a3 = a3 | t0;
                sh(a3, v0, 0);
                lbu(t2, a1, 6);
                lbu(t1, a1, 5);
                lbu(t0, a1, 4);
                lbu(a3, a1, 7);
                t2 = sll(t2, 7);
                t1 = sll(t1, 2);
                t2 = t2 & 0x7C00;
                t1 = t1 & 0x3E0;
                t0 = srl(t0, 3);
                t1 = t2 | t1;
                a3 = sll(a3, 8);
                t0 = t0 | t1;
                a3 = a3 & 0x8000;
                a3 = a3 | t0;
                sh(a3, v0, 2);
                lbu(t2, a1, 10);
                lbu(t1, a1, 9);
                lbu(t0, a1, 8);
                lbu(a3, a1, 11);
                t2 = sll(t2, 7);
                t1 = sll(t1, 2);
                t2 = t2 & 0x7C00;
                t1 = t1 & 0x3E0;
                t0 = srl(t0, 3);
                t1 = t2 | t1;
                a3 = sll(a3, 8);
                t0 = t0 | t1;
                a3 = a3 & 0x8000;
                a3 = a3 | t0;
                sh(a3, v0, 4);
                lbu(t2, a1, 14);
                lbu(t1, a1, 13);
                lbu(t0, a1, 12);
                lbu(a3, a1, 15);
                t2 = sll(t2, 7);
                t1 = sll(t1, 2);
                t2 = t2 & 0x7C00;
                t1 = t1 & 0x3E0;
                t0 = srl(t0, 3);
                t1 = t2 | t1;
                a3 = sll(a3, 8);
                t0 = t0 | t1;
                a3 = a3 & 0x8000;
                a3 = a3 | t0;
                sh(a3, v0, 6);
                lbu(t2, a1, 18);
                lbu(t1, a1, 17);
                lbu(t0, a1, 16);
                lbu(a3, a1, 19);
                t2 = sll(t2, 7);
                t1 = sll(t1, 2);
                t2 = t2 & 0x7C00;
                t1 = t1 & 0x3E0;
                t0 = srl(t0, 3);
                t1 = t2 | t1;
                a3 = sll(a3, 8);
                t0 = t0 | t1;
                a3 = a3 & 0x8000;
                a3 = a3 | t0;
                sh(a3, v0, 8);
                lbu(t2, a1, 22);
                lbu(t1, a1, 21);
                lbu(t0, a1, 20);
                lbu(a3, a1, 23);
                t2 = sll(t2, 7);
                t1 = sll(t1, 2);
                t2 = t2 & 0x7C00;
                t1 = t1 & 0x3E0;
                t0 = srl(t0, 3);
                t1 = t2 | t1;
                a3 = sll(a3, 8);
                t0 = t0 | t1;
                a3 = a3 & 0x8000;
                a3 = a3 | t0;
                sh(a3, v0, 10);
                lbu(t2, a1, 26);
                lbu(t1, a1, 25);
                lbu(t0, a1, 24);
                lbu(a3, a1, 27);
                t2 = sll(t2, 7);
                t1 = sll(t1, 2);
                t2 = t2 & 0x7C00;
                t1 = t1 & 0x3E0;
                t0 = srl(t0, 3);
                t1 = t2 | t1;
                a3 = sll(a3, 8);
                t0 = t0 | t1;
                a3 = a3 & 0x8000;
                a3 = a3 | t0;
                sh(a3, v0, 12);
                lbu(t2, a1, 30);
                lbu(t1, a1, 29);
                lbu(t0, a1, 28);
                lbu(a3, a1, 31);
                t2 = sll(t2, 7);
                t1 = sll(t1, 2);
                t2 = t2 & 0x7C00;
                t1 = t1 & 0x3E0;
                t0 = srl(t0, 3);
                t1 = t2 | t1;
                a3 = sll(a3, 8);
                t0 = t0 | t1;
                a3 = a3 & 0x8000;
                a3 = a3 | t0;
                a1 = addiu(a1, 32);
                sh(a3, v0, 14);
                v0 = addiu(v0, 16);
                if (a2 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004eae64
            charge(ctx, 6);
            lw(a0, a0, 8);
            v0 = addiu(a0, 32);
            a1 = addiu(v0, 127);
            jal(ctx, 0x4EAE6Cu, gen::fn_SyncDCache_00503a58);
            goto L_004eb7c0;
        }
    L_004eb0d4:
        charge(ctx, 5);
        lw(t3, a0, 8);
        t0 = 0x7C0000;
        t1 = 0;
        t2 = 0;
        t0 = addiu(t0, -12448);  // &0x7BCF60
        for (;;) {
            // 0x004eb0e8
            charge(ctx, 203);
            v0 = t2 & 0x3;
            v1 = addiu(t1, 1);
            v0 = sll(v0, 2);
            t4 = v1 & 0xE7;
            a2 = addu(t0, v0);
            t6 = t1 & 0xE7;
            lw(t5, a2, 0);
            v0 = sra(v1, 3);
            v0 = v0 & 0x3;
            v1 = addiu(t1, 2);
            v0 = sll(v0, 2);
            t7 = v1 & 0xE7;
            v0 = addu(t0, v0);
            a3 = addiu(t1, 3);
            t2 = addiu(t2, 1);
            lw(a2, v0, 0);
            v0 = sra(v1, 3);
            a2 = t4 | a2;
            v0 = v0 & 0x3;
            v1 = t6 | t5;
            v0 = sll(v0, 2);
            v1 = sll(v1, 2);
            v0 = addu(t0, v0);
            v1 = addu(a1, v1);
            lw(t6, v0, 0);
            t4 = sll(a2, 2);
            lbu(t8, v1, 2);
            t5 = a3 & 0xE7;
            lbu(s1, v1, 1);
            lbu(s0, v1, 0);
            v0 = sra(a3, 3);
            v0 = v0 & 0x3;
            a2 = sll(v0, 2);
            v0 = addu(a1, t4);
            a2 = addu(t0, a2);
            lw(t4, a2, 0);
            a2 = t7 | t6;
            lbu(t7, v1, 3);
            a2 = sll(a2, 2);
            a3 = addu(a1, a2);
            a2 = addiu(t1, 4);
            t6 = a2 & 0xE7;
            v1 = sra(a2, 3);
            a2 = t5 | t4;
            v1 = v1 & 0x3;
            t4 = sll(t8, 7);
            v1 = sll(v1, 2);
            t8 = t4 & 0x7C00;
            a2 = sll(a2, 2);
            t4 = sll(s1, 2);
            t5 = srl(s0, 3);
            t4 = t4 & 0x3E0;
            v1 = addu(t0, v1);
            s0 = t8 | t4;
            a2 = addu(a1, a2);
            t4 = sll(t7, 8);
            t5 = t5 | s0;
            t4 = t4 & 0x8000;
            t4 = t4 | t5;
            lw(t5, v1, 0);
            sh(t4, t3, 0);
            lbu(t8, v0, 2);
            t4 = addiu(t1, 5);
            lbu(s1, v0, 1);
            lbu(s0, v0, 0);
            lbu(t7, v0, 3);
            v1 = sra(t4, 3);
            v1 = v1 & 0x3;
            t4 = t4 & 0xE7;
            v1 = sll(v1, 2);
            t8 = sll(t8, 7);
            v0 = addu(t0, v1);
            v1 = t6 | t5;
            lw(v0, v0, 0);
            t5 = sll(s1, 2);
            t6 = t8 & 0x7C00;
            t5 = t5 & 0x3E0;
            v1 = sll(v1, 2);
            t6 = t6 | t5;
            v1 = addu(a1, v1);
            t5 = srl(s0, 3);
            t6 = t5 | t6;
            v0 = t4 | v0;
            t5 = sll(t7, 8);
            t4 = t5 & 0x8000;
            v0 = sll(v0, 2);
            t4 = t4 | t6;
            t5 = addiu(t1, 6);
            sh(t4, t3, 2);
            t6 = t5 & 0xE7;
            lbu(t8, a3, 2);
            t4 = sra(t5, 3);
            lbu(s1, a3, 1);
            t4 = t4 & 0x3;
            lbu(s0, a3, 0);
            t4 = sll(t4, 2);
            lbu(t7, a3, 3);
            v0 = addu(a1, v0);
            t8 = sll(t8, 7);
            s1 = sll(s1, 2);
            t8 = t8 & 0x7C00;
            s1 = s1 & 0x3E0;
            s0 = srl(s0, 3);
            a3 = addu(t0, t4);
            s1 = t8 | s1;
            lw(t5, a3, 0);
            t4 = addiu(t1, 7);
            t7 = sll(t7, 8);
            s0 = s0 | s1;
            t1 = addiu(t1, 8);
            t5 = t6 | t5;
            a3 = sra(t4, 3);
            t6 = t7 & 0x8000;
            a3 = a3 & 0x3;
            t6 = t6 | s0;
            a3 = sll(a3, 2);
            sh(t6, t3, 4);
            t5 = sll(t5, 2);
            t6 = addu(a1, t5);
            lbu(t8, a2, 2);
            t5 = t4 & 0xE7;
            a3 = addu(t0, a3);
            lw(t4, a3, 0);
            lbu(s1, a2, 1);
            lbu(s0, a2, 0);
            lbu(t7, a2, 3);
            t8 = sll(t8, 7);
            t8 = t8 & 0x7C00;
            a3 = slti(t1, 256);
            a2 = t5 | t4;
            t4 = sll(s1, 2);
            t5 = srl(s0, 3);
            t4 = t4 & 0x3E0;
            a2 = sll(a2, 2);
            s0 = t8 | t4;
            t4 = sll(t7, 8);
            t5 = t5 | s0;
            t4 = t4 & 0x8000;
            t4 = t4 | t5;
            sh(t4, t3, 6);
            t5 = addu(a1, a2);
            lbu(t7, v1, 2);
            lbu(t4, v1, 1);
            lbu(a2, v1, 0);
            t7 = sll(t7, 7);
            t4 = sll(t4, 2);
            t7 = t7 & 0x7C00;
            lbu(v1, v1, 3);
            t4 = t4 & 0x3E0;
            a2 = srl(a2, 3);
            t4 = t7 | t4;
            a2 = a2 | t4;
            v1 = sll(v1, 8);
            v1 = v1 & 0x8000;
            v1 = v1 | a2;
            sh(v1, t3, 8);
            lbu(t4, v0, 2);
            lbu(a2, v0, 1);
            lbu(v1, v0, 0);
            t4 = sll(t4, 7);
            a2 = sll(a2, 2);
            t4 = t4 & 0x7C00;
            lbu(v0, v0, 3);
            a2 = a2 & 0x3E0;
            v1 = srl(v1, 3);
            a2 = t4 | a2;
            v1 = v1 | a2;
            v0 = sll(v0, 8);
            v0 = v0 & 0x8000;
            v0 = v0 | v1;
            sh(v0, t3, 10);
            lbu(t4, t6, 2);
            lbu(a2, t6, 1);
            lbu(v1, t6, 0);
            lbu(v0, t6, 3);
            t4 = sll(t4, 7);
            a2 = sll(a2, 2);
            t4 = t4 & 0x7C00;
            a2 = a2 & 0x3E0;
            v1 = srl(v1, 3);
            a2 = t4 | a2;
            v0 = sll(v0, 8);
            v1 = v1 | a2;
            v0 = v0 & 0x8000;
            v0 = v0 | v1;
            sh(v0, t3, 12);
            lbu(t4, t5, 2);
            lbu(a2, t5, 1);
            lbu(v1, t5, 0);
            lbu(v0, t5, 3);
            t4 = sll(t4, 7);
            a2 = sll(a2, 2);
            t4 = t4 & 0x7C00;
            a2 = a2 & 0x3E0;
            v1 = srl(v1, 3);
            a2 = t4 | a2;
            v0 = sll(v0, 8);
            v1 = v1 | a2;
            v0 = v0 & 0x8000;
            v0 = v0 | v1;
            sh(v0, t3, 14);
            t3 = addiu(t3, 16);
            if (a3 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004eb414
        charge(ctx, 6);
        lw(a0, a0, 8);
        v0 = addiu(a0, 512);
        a1 = addiu(v0, 127);
        jal(ctx, 0x4EB41Cu, gen::fn_SyncDCache_00503a58);
        goto L_004eb7c0;
    }
    // 0x004eb42c
    charge(ctx, 6);
    lw(t7, a0, 8);
    t4 = 0x7C0000;
    t5 = 0;
    t6 = 0;
    t4 = addiu(t4, -12448);  // &0x7BCF60
    t3 = lui(0xFF00);
    for (;;) {
        // 0x004eb444
        charge(ctx, 219);
        v0 = t6 & 0x3;
        v1 = addiu(t5, 1);
        v0 = sll(v0, 2);
        t1 = v1 & 0xE7;
        a2 = addu(t4, v0);
        t2 = t5 & 0xE7;
        v0 = sra(v1, 3);
        lw(a3, a2, 0);
        v0 = v0 & 0x3;
        v1 = addiu(t5, 2);
        v0 = sll(v0, 2);
        s0 = v1 & 0xE7;
        v0 = addu(t4, v0);
        t6 = addiu(t6, 1);
        lw(t0, v0, 0);
        a2 = addiu(t5, 3);
        v0 = sra(v1, 3);
        t0 = t1 | t0;
        v0 = v0 & 0x3;
        v1 = t2 | a3;
        v0 = sll(v0, 2);
        t0 = sll(t0, 2);
        v0 = addu(t4, v0);
        v1 = sll(v1, 2);
        lw(a3, v0, 0);
        t2 = a2 & 0xE7;
        t0 = addu(a1, t0);
        v0 = addu(a1, v1);
        v1 = sra(a2, 3);
        lbu(t9, v0, 2);
        v1 = v1 & 0x3;
        a2 = addiu(t5, 4);
        v1 = sll(v1, 2);
        lbu(t8, v0, 1);
        v1 = addu(t4, v1);
        s1 = a2 & 0xE7;
        lw(t1, v1, 0);
        v1 = s0 | a3;
        v1 = sll(v1, 2);
        lbu(s0, v0, 0);
        a3 = addu(a1, v1);
        v1 = sra(a2, 3);
        a2 = t2 | t1;
        v1 = v1 & 0x3;
        t2 = sll(t9, 16);
        t1 = sll(t8, 8);
        t2 = t2 | t1;
        a2 = sll(a2, 2);
        t1 = sll(v1, 2);
        lbu(v0, v0, 3);
        v1 = s0 | t2;
        t1 = addu(t4, t1);
        lw(s0, t1, 0);
        t2 = addiu(t5, 5);
        t9 = t2 & 0xE7;
        a2 = addu(a1, a2);
        t1 = sll(v0, 8);
        t1 = addu(t1, v0);
        t8 = sll(t1, 8);
        t1 = sra(t2, 3);
        t8 = addu(t8, v0);
        t1 = t1 & 0x3;
        t8 = sll(t8, 7);
        t1 = sll(t1, 2);
        t8 = addu(t8, v0);
        v0 = addu(t4, t1);
        t1 = s1 | s0;
        s0 = t8 & t3;
        lw(t8, v0, 0);
        s0 = v1 | s0;
        sw(s0, t7, 0);
        v1 = sll(t1, 2);
        s0 = addiu(t5, 6);
        lbu(t2, t0, 2);
        t1 = sra(s0, 3);
        s1 = s0 & 0xE7;
        t1 = t1 & 0x3;
        v1 = addu(a1, v1);
        s0 = sll(t1, 2);
        lbu(v0, t0, 1);
        t8 = t9 | t8;
        lbu(t1, t0, 0);
        s0 = addu(t4, s0);
        t9 = sll(t2, 16);
        lw(s0, s0, 0);
        t2 = sll(t8, 2);
        t8 = sll(v0, 8);
        v0 = addu(a1, t2);
        lbu(t0, t0, 3);
        t2 = t9 | t8;
        s0 = s1 | s0;
        t8 = addiu(t5, 7);
        t1 = t1 | t2;
        t2 = sra(t8, 3);
        s0 = sll(s0, 2);
        t2 = t2 & 0x3;
        t9 = t8 & 0xE7;
        t2 = sll(t2, 2);
        s0 = addu(a1, s0);
        t2 = addu(t4, t2);
        t5 = addiu(t5, 8);
        lw(t8, t2, 0);
        t2 = sll(t0, 8);
        t2 = addu(t2, t0);
        s1 = sll(t2, 8);
        s1 = addu(s1, t0);
        t2 = slti(t5, 256);
        s1 = sll(s1, 7);
        s1 = addu(s1, t0);
        s1 = s1 & t3;
        t0 = t9 | t8;
        t1 = t1 | s1;
        t0 = sll(t0, 2);
        sw(t1, t7, 4);
        t0 = addu(a1, t0);
        lbu(t9, a3, 2);
        lbu(t8, a3, 1);
        lbu(s1, a3, 0);
        lbu(t1, a3, 3);
        t9 = sll(t9, 16);
        a3 = sll(t8, 8);
        a3 = t9 | a3;
        s1 = s1 | a3;
        a3 = sll(t1, 8);
        a3 = addu(a3, t1);
        a3 = sll(a3, 8);
        a3 = addu(a3, t1);
        a3 = sll(a3, 7);
        a3 = addu(a3, t1);
        a3 = a3 & t3;
        a3 = s1 | a3;
        sw(a3, t7, 8);
        lbu(t8, a2, 2);
        lbu(s1, a2, 1);
        lbu(t1, a2, 0);
        lbu(a3, a2, 3);
        t8 = sll(t8, 16);
        a2 = sll(s1, 8);
        a2 = t8 | a2;
        t1 = t1 | a2;
        a2 = sll(a3, 8);
        a2 = addu(a2, a3);
        a2 = sll(a2, 8);
        a2 = addu(a2, a3);
        a2 = sll(a2, 7);
        a2 = addu(a2, a3);
        a2 = a2 & t3;
        a2 = t1 | a2;
        sw(a2, t7, 12);
        lbu(s1, v1, 2);
        lbu(t1, v1, 1);
        lbu(a3, v1, 0);
        lbu(a2, v1, 3);
        s1 = sll(s1, 16);
        v1 = sll(t1, 8);
        v1 = s1 | v1;
        a3 = a3 | v1;
        v1 = sll(a2, 8);
        v1 = addu(v1, a2);
        v1 = sll(v1, 8);
        v1 = addu(v1, a2);
        v1 = sll(v1, 7);
        v1 = addu(v1, a2);
        v1 = v1 & t3;
        v1 = a3 | v1;
        sw(v1, t7, 16);
        lbu(t1, v0, 2);
        lbu(a3, v0, 1);
        lbu(a2, v0, 0);
        lbu(v1, v0, 3);
        t1 = sll(t1, 16);
        v0 = sll(a3, 8);
        v0 = t1 | v0;
        a2 = a2 | v0;
        v0 = sll(v1, 8);
        v0 = addu(v0, v1);
        v0 = sll(v0, 8);
        v0 = addu(v0, v1);
        v0 = sll(v0, 7);
        v0 = addu(v0, v1);
        v0 = v0 & t3;
        v0 = a2 | v0;
        sw(v0, t7, 20);
        lbu(a3, s0, 2);
        lbu(a2, s0, 1);
        lbu(v0, s0, 0);
        lbu(v1, s0, 3);
        a3 = sll(a3, 16);
        a2 = sll(a2, 8);
        a2 = a3 | a2;
        a2 = v0 | a2;
        v0 = sll(v1, 8);
        v0 = addu(v0, v1);
        v0 = sll(v0, 8);
        v0 = addu(v0, v1);
        v0 = sll(v0, 7);
        v0 = addu(v0, v1);
        v0 = v0 & t3;
        v0 = a2 | v0;
        sw(v0, t7, 24);
        lbu(a3, t0, 2);
        lbu(a2, t0, 1);
        lbu(v0, t0, 0);
        lbu(v1, t0, 3);
        a3 = sll(a3, 16);
        a2 = sll(a2, 8);
        a2 = a3 | a2;
        a2 = v0 | a2;
        v0 = sll(v1, 8);
        v0 = addu(v0, v1);
        v0 = sll(v0, 8);
        v0 = addu(v0, v1);
        v0 = sll(v0, 7);
        v0 = addu(v0, v1);
        v0 = v0 & t3;
        v0 = a2 | v0;
        sw(v0, t7, 28);
        t7 = addiu(t7, 32);
        if (t2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004eb7b0
    charge(ctx, 4);
    lw(a0, a0, 8);
    v0 = addiu(a0, 1024);
    a1 = addiu(v0, 127);
    jal(ctx, 0x4EB7B8u, gen::fn_SyncDCache_00503a58);
L_004eb7c0:
    charge(ctx, 1);
    ld(ra, sp, 0x20);
    // 0x004eb7c4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// sub_4EB8C0 [skyRasterSetImagePalettised] -- copies an image into a palettised raster: 8-bit rasters from 32-bit
//   images through the quantiser (sub_4EB7E0) or from 8 / 4-bit images with their palette and rows; 4-bit rasters from 32
//   / 8-bit images (quantised) or 4-bit images (nibbles packed by the raster's x parity); 1, or 0 for another combination
// 0x004EB8C0 sub_4EB8C0 -- 640 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4EB8C0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004eb8c0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    a2 = 32;
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lbu(v0, a0, 35);
    lw(s2, a0, 4);
    lw(s1, a1, 20);
    lw(a3, a1, 24);
    v1 = v0 & 0x60;
    s0 = 1;
    if (v1 != a2) {
        // 0x004eb908
        charge(ctx, 3);
        v0 = 64;
        if (v1 != v0) {
            // 0x004eb914
            charge(ctx, 2);
            s0 = 0;
            goto L_004ebb18;
        }
        // 0x004eb91c
        charge(ctx, 3);
        lw(v1, s3, rw9::image::kDepth);
        if (v1 != a2) {
            // 0x004eb928
            charge(ctx, 3);
            v0 = 8;
            if (v1 == v0) {
                goto L_004eba20;
            }
            // 0x004eb934
            charge(ctx, 3);
            v0 = 4;
            if (v1 != v0) {
                // 0x004eb940
                charge(ctx, 2);
                s0 = 0;
                // 0x004eba34
                charge(ctx, 2);
                goto L_004ebb18;
            }
            // 0x004eb948
            charge(ctx, 6);
            a1 = a3;
            jal(ctx, 0x4EB948u, gen::fn_sub_4EAC00_004eac00);
            lw(v0, s3, rw9::image::kHeight);
            at = slt(0, v0);
            a0 = 0;
            if (at == 0) {
                goto L_004ebb18;
            }
            for (;;) {
                // 0x004eb960
                charge(ctx, 6);
                lw(a2, s3, rw9::image::kWidth);
                v1 = s2;
                v0 = s1;
                at = slt(0, a2);
                a1 = 0;
                if (at != 0) {
                    for (;;) {
                        // 0x004eb978
                        charge(ctx, 5);
                        lh(a2, s4, rw9::raster::kOffsetX);
                        a2 = addu(a1, a2);
                        a2 = a2 & 0x1;
                        if (a2 == 0) {
                            // 0x004eb9c0
                            charge(ctx, 8);
                            lbu(a2, v1, 0);
                            a2 = a2 & 0xF0;
                            sb(a2, v1, 0);
                            lbu(a3, v0, 0);
                            lbu(a2, v1, 0);
                            a3 = a3 & 0xF;
                            a2 = a2 | a3;
                            sb(a2, v1, 0);
                        } else {
                            // 0x004eb98c
                            charge(ctx, 12);
                            lbu(a2, v1, 0);
                            a2 = a2 & 0xF;
                            sb(a2, v1, 0);
                            lbu(a3, v0, 0);
                            lbu(a2, v1, 0);
                            a3 = a3 & 0xF;
                            a3 = sll(a3, 4);
                            a3 = a3 & 0xFF;
                            a2 = a2 | a3;
                            sb(a2, v1, 0);
                            v1 = addiu(v1, 1);
                        }
                        // 0x004eb9e0
                        charge(ctx, 5);
                        lw(a2, s3, rw9::image::kWidth);
                        a1 = addiu(a1, 1);
                        a2 = slt(a1, a2);
                        v0 = addiu(v0, 1);
                        if (a2 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004eb9f4
                    charge(ctx, 1);
                }
                // 0x004eb9f8
                charge(ctx, 8);
                lw(v0, s3, rw9::image::kHeight);
                lw(a1, s3, rw9::image::kStride);
                a0 = addiu(a0, 1);
                lw(v1, s4, rw9::raster::kStride);
                v0 = slt(a0, v0);
                s1 = addu(s1, a1);
                s2 = addu(s2, v1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004eba18
            charge(ctx, 2);
            v0 = s0;
            // 0x004ebb1c (the shared epilogue, written out on this path)
            charge(ctx, 9);
            ld(ra, sp, 0x60);
            lq(s5, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x70);
            return;
        }
    L_004eba20:
        charge(ctx, 5);
        a0 = s4;
        a1 = s3;
        jal(ctx, 0x4EBA24u, gen::fn_sub_4EB7E0_004eb7e0);
        s0 = v0;
        goto L_004ebb18;
    }
    // 0x004eba3c
    charge(ctx, 3);
    lw(v1, s3, rw9::image::kDepth);
    if (v1 == a2) {
        // 0x004ebb08
        charge(ctx, 4);
        jal(ctx, 0x4EBB08u, gen::fn_sub_4EB7E0_004eb7e0);
        s0 = v0;
    } else {
        // 0x004eba48
        charge(ctx, 3);
        v0 = 8;
        if (v1 == v0) {
            // 0x004ebab8
            charge(ctx, 6);
            a1 = a3;
            jal(ctx, 0x4EBAB8u, gen::fn_sub_4EAC00_004eac00);
            lw(v0, s3, rw9::image::kHeight);
            at = slt(0, v0);
            s5 = 0;
            if (at != 0) {
                for (;;) {
                    // 0x004ebad0
                    charge(ctx, 12);
                    lw(a2, s3, rw9::image::kWidth);
                    a0 = s2;
                    a1 = s1;
                    jal(ctx, 0x4EBAD8u, gen::fn_memcpy_00521250);
                    lw(v0, s3, rw9::image::kHeight);
                    s5 = addiu(s5, 1);
                    lw(a0, s3, rw9::image::kStride);
                    lw(v1, s4, rw9::raster::kStride);
                    v0 = slt(s5, v0);
                    s1 = addu(s1, a0);
                    s2 = addu(s2, v1);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004ebb00
                charge(ctx, 2);
            }
        } else {
            // 0x004eba54
            charge(ctx, 3);
            v0 = 4;
            if (v1 == v0) {
                // 0x004eba68
                charge(ctx, 6);
                a1 = a3;
                jal(ctx, 0x4EBA68u, gen::fn_sub_4EAC00_004eac00);
                lw(v0, s3, rw9::image::kHeight);
                at = slt(0, v0);
                s5 = 0;
                if (at != 0) {
                    for (;;) {
                        // 0x004eba80
                        charge(ctx, 12);
                        lw(a2, s3, rw9::image::kWidth);
                        a0 = s2;
                        a1 = s1;
                        jal(ctx, 0x4EBA88u, gen::fn_memcpy_00521250);
                        lw(v0, s3, rw9::image::kHeight);
                        s5 = addiu(s5, 1);
                        lw(a0, s3, rw9::image::kStride);
                        lw(v1, s4, rw9::raster::kStride);
                        v0 = slt(s5, v0);
                        s1 = addu(s1, a0);
                        s2 = addu(s2, v1);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004ebab0
                    charge(ctx, 2);
                }
            } else {
                // 0x004eba60
                charge(ctx, 2);
                s0 = 0;
            }
        }
    }
L_004ebb18:
    charge(ctx, 1);
    v0 = s0;
    // 0x004ebb1c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// sub_4EEC10 [skyNoOp] -- an empty sky driver hook
// 0x004EEC10 sub_4EEC10 -- 8 bytes; leaf frame (no stack)
void sub_4EEC10(EEContext& ctx) {
    using namespace hg;
    // 0x004eec10
    enter(ctx, 2);  // entry check point + this block's cycles
}

// sub_4EF1D0 [skyRasterPrepareUploads] -- pre-builds a texture raster's GS upload packets: for each mip level whose
//   pixels are 16-byte aligned and contiguous an upload packet (RwMalloc'd,
//   skyFillInPktForUpLoadAlignedContiguousRectangle) when the raster extension asks for them (+52), and the palette's
//   packet (the CLUT size from the 0x7BCF8C / 0x7BCFAC tables by depth); cleared when not wanted
// 0x004EF1D0 sub_4EF1D0 -- 872 bytes; frame 0xD0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4EF1D0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004ef1d0
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = a0;
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a2, gp, -16968);  // 0x7CEAA8
    lw(v1, a0, 20);
    lw(a1, a0, 12);
    lw(s3, a0, 4);
    s4 = addu(s6, a2);
    sq(v1, sp, 0xC0);
    mult(a1, a1, v1);
    lw(v1, a0, 24);
    a1 = sra(a1, 3);
    lbu(a0, s4, 22);
    v1 = v1 ^ a1;
    v1 = sltiu(v1, 1);
    sq(v1, sp, 0xB0);
    v1 = sra(a0, 2);
    at = slt(v1, 0);
    s5 = 0;
    if (at == 0) {
        // 0x004ef244
        charge(ctx, 4);
        v1 = 0x960000;
        s1 = s4;
        v1 = addiu(v1, 376);  // &0x960178
        sq(v1, sp, 0xA0);
        for (;;) {
            // 0x004ef254
            charge(ctx, 10);
            lw(a2, s6, 12);
            v1 = s3 & 0xF;
            lw(a1, s6, 16);
            v1 = sltu(0, v1);
            lw(a0, s6, 24);
            v1 = v1 ^ 0x1;
            a2 = srav(a2, s5);
            s7 = srav(a1, s5);
            fp = srav(a0, s5);
            if (v1 != 0) {
                // 0x004ef27c
                charge(ctx, 3);
                lq(v1, sp, 0xB0);
                if (v1 != 0) {
                    // 0x004ef288
                    charge(ctx, 3);
                    lw(v1, s1, 60);
                    if (v1 == 0) {
                        // 0x004ef294
                        charge(ctx, 3);
                        lbu(s0, s4, 52);
                        if (s0 != 0) {
                            // 0x004ef2a0
                            charge(ctx, 7);
                            mult(v1, a2, s7);
                            lq(v0, sp, 0xC0);
                            mult(v0, v0, v1);
                            v0 = srl(v0, 3);
                            s2 = dsll32(v0, 0);
                            s2 = dsrl32(s2, 0);
                            if (s0 == 0) {
                                // 0x004ef308
                                charge(ctx, 16);
                                a0 = 10;
                                jal(ctx, 0x4EF308u, gen::fn__rwDMAOpenGIFPkt_004d54e0);
                                v0 = daddiu(s2, 15);
                                a1 = 32750;
                                a0 = dsrl(v0, 4);
                                jal(ctx, 0x4EF318u, gen::fn___udivdi3_0052fe98);
                                v1 = daddiu(v0, 1);
                                a1 = 0;
                                v0 = dsll(v1, 1);
                                v0 = v0 + v1;
                                v0 = dsll(v0, 4);
                                v0 = daddiu(v0, 176);
                                a0 = dsll32(v0, 0);
                                a0 = dsra32(a0, 0);
                                jal(ctx, 0x4EF33Cu, gen::fn_sub_4D5FE0_004d5fe0);
                            } else {
                                // 0x004ef2bc
                                charge(ctx, 18);
                                v0 = daddiu(s2, 15);
                                a1 = 32750;
                                a0 = dsrl(v0, 4);
                                jal(ctx, 0x4EF2C4u, gen::fn___udivdi3_0052fe98);
                                v1 = daddiu(v0, 1);
                                v0 = 0x30000;
                                a1 = v0 | 0x411;
                                v0 = dsll(v1, 1);
                                v1 = v0 + v1;
                                lq(v0, sp, 0xA0);
                                v1 = dsll(v1, 4);
                                v1 = daddiu(v1, 176);
                                a0 = dsll32(v1, 0);
                                lw(v0, v0, 0);
                                a0 = dsra32(a0, 0);
                                jalr(ctx, 0x4EF2F4u, v0.u());
                            }
                            // 0x004ef348
                            charge(ctx, 6);
                            a2 = s2;
                            a3 = s0;
                            a0 = v0;
                            a1 = s3;
                            jal(ctx, 0x4EF354u, gen::fn_skyFillInPktForUpLoadAlignedContiguousRectangle_004ef020);
                            sw(v0, s1, 60);
                        }
                    }
                    // 0x004ef360
                    charge(ctx, 3);
                    lbu(v1, s4, 52);
                    if (v1 == 0) {
                        // 0x004ef36c
                        charge(ctx, 1);
                        sw(zero, s1, 60);
                    }
                }
            }
            // 0x004ef370
            charge(ctx, 5);
            mult(v1, fp, s7);
            s3 = addu(s3, v1);
            v1 = s3 & 0xF;
            if (v1 != 0) {
                // 0x004ef384
                charge(ctx, 3);
                a0 = addiu(s3, 15);
                v1 = si(-16);
                s3 = a0 & v1;
            }
            // 0x004ef390
            charge(ctx, 6);
            lbu(v1, s4, 22);
            s5 = addiu(s5, 1);
            v1 = sra(v1, 2);
            at = slt(v1, s5);
            s1 = addiu(s1, 4);
            if (at != 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004ef3a8
    charge(ctx, 3);
    lw(v1, s4, 44);
    if (v1 != 0) {
        // 0x004ef3b4
        charge(ctx, 4);
        lw(v1, s6, 20);
        at = slti(v1, 9);
        if (at != 0) {
            // 0x004ef3c4
            charge(ctx, 15);
            a1 = sll(v1, 2);
            v1 = 0x7C0000;
            v1 = addiu(v1, -12404);  // &0x7BCF8C
            a0 = addu(v1, a1);
            lw(a2, a0, 0);
            v1 = 0x7C0000;
            v1 = addiu(v1, -12372);  // &0x7BCFAC
            v1 = addu(v1, a1);
            lw(a1, v1, 0);
            lw(a0, s4, 12);
            v1 = 10;
            a0 = srl(a0, 19);
            a0 = a0 & 0xF;
            if (a0 != v1) {
                // 0x004ef400
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    goto L_004ef424;
                }
                // 0x004ef40c
                charge(ctx, 2);
                if (a0 == 0) {
                    // 0x004ef41c
                    charge(ctx, 2);
                    a0 = 32;
                } else {
                    // 0x004ef414
                    charge(ctx, 2);
                    a0 = 16;
                }
                goto L_004ef428;
            }
        L_004ef424:
            charge(ctx, 1);
            a0 = 16;
        L_004ef428:
            charge(ctx, 3);
            lw(v1, s4, 56);
            if (v1 == 0) {
                // 0x004ef434
                charge(ctx, 3);
                lbu(s0, s4, 52);
                if (s0 != 0) {
                    // 0x004ef440
                    charge(ctx, 7);
                    lw(s2, s6, 8);
                    mult(v0, a2, a1);
                    mult(v0, a0, v0);
                    v0 = srl(v0, 3);
                    s1 = dsll32(v0, 0);
                    s1 = dsrl32(s1, 0);
                    if (s0 == 0) {
                        // 0x004ef4a4
                        charge(ctx, 16);
                        a0 = 10;
                        jal(ctx, 0x4EF4A4u, gen::fn__rwDMAOpenGIFPkt_004d54e0);
                        v0 = daddiu(s1, 15);
                        a1 = 32750;
                        a0 = dsrl(v0, 4);
                        jal(ctx, 0x4EF4B4u, gen::fn___udivdi3_0052fe98);
                        v1 = daddiu(v0, 1);
                        a1 = 0;
                        v0 = dsll(v1, 1);
                        v0 = v0 + v1;
                        v0 = dsll(v0, 4);
                        v0 = daddiu(v0, 176);
                        a0 = dsll32(v0, 0);
                        a0 = dsra32(a0, 0);
                        jal(ctx, 0x4EF4D8u, gen::fn_sub_4D5FE0_004d5fe0);
                        a1 = s2;
                    } else {
                        // 0x004ef45c
                        charge(ctx, 18);
                        v0 = daddiu(s1, 15);
                        a1 = 32750;
                        a0 = dsrl(v0, 4);
                        jal(ctx, 0x4EF464u, gen::fn___udivdi3_0052fe98);
                        v1 = daddiu(v0, 1);
                        v0 = 0x30000;
                        a1 = v0 | 0x411;
                        v0 = dsll(v1, 1);
                        v1 = v0 + v1;
                        v0 = 0x960000;
                        v1 = dsll(v1, 4);
                        lw(v0, v0, 376);  // 0x960178
                        v1 = daddiu(v1, 176);
                        a0 = dsll32(v1, 0);
                        a0 = dsra32(a0, 0);
                        jalr(ctx, 0x4EF494u, v0.u());
                        a1 = s2;
                    }
                    // 0x004ef4e4
                    charge(ctx, 5);
                    a2 = s1;
                    a3 = s0;
                    a0 = v0;
                    jal(ctx, 0x4EF4ECu, gen::fn_skyFillInPktForUpLoadAlignedContiguousRectangle_004ef020);
                    sw(v0, s4, 56);
                }
            }
            // 0x004ef4f8
            charge(ctx, 3);
            lbu(v1, s4, 52);
            if (v1 == 0) {
                // 0x004ef504
                charge(ctx, 1);
                sw(zero, s4, 56);
            }
        }
    }
    // 0x004ef508 (the shared epilogue, written out on this path)
    charge(ctx, 12);
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
    sp = addiu(sp, 0xD0);
}

// sub_4EF9F0 [skyNoOp2] -- an empty sky driver hook
// 0x004EF9F0 sub_4EF9F0 -- 8 bytes; leaf frame (no stack)
void sub_4EF9F0(EEContext& ctx) {
    using namespace hg;
    // 0x004ef9f0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// sub_4F02E0 [skyTexCacheAllocRaster] -- places a texture raster in the GS texture cache ring (0x77F200..): a raster
//   already resident is referenced again (with interrupts off its counters up, the PURef added for the first use); else
//   space after the last entry (or the cache start) is found, the entries it overlaps evicted (their rasters' cache links
//   cleared) unless locked, the raster's TEX0 base set (sub_4EFA00), and the ring entry {raster, address, 2 KiB-rounded
//   size} appended
// 0x004F02E0 sub_4F02E0 -- 1700 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
void sub_4F02E0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f02e0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(v1, gp, -16968);  // 0x7CEAA8
    s1 = addu(s2, v1);
    lbu(v1, s1, 54);
    v1 = v1 & 0x1;
    a2 = a1;
    if (v1 == 0) {
        // 0x004f0368
        charge(ctx, 2);
        if (a2 == 0) {
            backedge(ctx);
            goto L_004f0310;
        }
        // 0x004f0370
        charge(ctx, 2);
    L_004f096c:
        charge(ctx, 1);
        ld(ra, sp, 0x30);
        // 0x004f0970 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_004f0310:
    charge(ctx, 3);
    lw(t0, s1, 88);
    if (t0 != 0) {
        // 0x004f031c
        charge(ctx, 15);
        a0 = 0x780000;
        v1 = 0x780000;
        lw(a3, a0, -3580);  // 0x77F204
        lw(a1, v1, -3564);  // 0x77F214
        a0 = 0x2AAA0000;
        v1 = a0 | 0xAAAB;
        a0 = subu(t0, a1);
        mult(zero, v1, a0);
        a0 = srl(a0, 31);
        mfhi(v1);
        v1 = sra(v1, 1);
        v1 = addu(v1, a0);
        if (a3 != v1) {
            goto L_004f03c8;
        }
        // 0x004f0358
        charge(ctx, 2);
        if (a2 == 0) {
            // 0x004f0378
            charge(ctx, 13);
            jal(ctx, 0x4F0378u, gen::fn_DIntr_0050d3a0);
            lw(v0, s1, 0);
            v0 = addiu(v0, 1);
            link(ctx, 0x4F0388u);  // $ra first: the delay slot below depends on it
            sw(v0, s1, 0);
            call(ctx, gen::fn_EIntr_0050d3f0);
            lw(a0, s1, 4);
            v1 = 1;
            a0 = addiu(a0, 1);
            sw(a0, s1, 4);
            lw(a0, s1, 4);
            if (a0 == v1) {
                // 0x004f03b8
                charge(ctx, 4);
                a0 = s1;
                jal(ctx, 0x4F03B8u, gen::fn__rwDMAAddPURef_004d51c0);
                backedge(ctx);
            }
            // 0x004f03ac
            charge(ctx, 3);
            v1 = 0x780000;
            sw(s2, v1, -3548);  // 0x77F224
            goto L_004f096c;
        }
        // 0x004f0360
        charge(ctx, 2);
        ld(ra, sp, 0x30);
        // 0x004f0970 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_004f03c8:
    charge(ctx, 3);
    lbu(v1, s1, 23);
    if (v1 == 0) {
        // 0x004f03d4
        charge(ctx, 6);
        a0 = 0x780000;
        v1 = 0x780000;
        lw(a1, a0, -3568);  // 0x77F210
        lw(v1, v1, -3572);  // 0x77F20C
        if (a1 == v1) {
            // 0x004f040c
            charge(ctx, 5);
            a0 = 0x780000;
            v1 = 0x780000;
            lw(a0, a0, -3560);  // 0x77F218
            lw(v1, v1, -3556);  // 0x77F21C
            t0 = addu(a0, v1);
        } else {
            // 0x004f03ec
            charge(ctx, 8);
            a0 = sll(a1, 1);
            v1 = 0x780000;
            a0 = addu(a0, a1);
            lw(a1, v1, -3564);  // 0x77F214
            v1 = sll(a0, 2);
            v1 = addu(v1, a1);
            lw(t0, v1, 4);
        }
        // 0x004f0420
        charge(ctx, 5);
        v1 = 0x780000;
        a0 = si(-1);
        lw(v1, v1, -3580);  // 0x77F204
        if (v1 != a0) {
            // 0x004f0434
            charge(ctx, 14);
            a1 = sll(v1, 1);
            a0 = 0x780000;
            a3 = addu(a1, v1);
            lw(a1, a0, -3564);  // 0x77F214
            a3 = sll(a3, 2);
            a1 = addu(a3, a1);
            lw(a0, s1, 48);
            lw(a3, a1, 4);
            lw(a1, a1, 8);
            s0 = addu(a3, a1);
            a1 = subu(t0, s0);
            a0 = sltu(a1, a0);
            if (a0 != 0) {
                goto L_004f07e8;
            }
        L_004f046c:
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x004f0474
                charge(ctx, 3);
                a3 = si(-1);
                if (v1 == a3) {
                    goto L_004f05f0;
                }
                // 0x004f0480
                charge(ctx, 5);
                v1 = 0x780000;
                a0 = 0x780000;
                lw(a1, v1, -3540);  // 0x77F22C
                lw(t2, a0, -3576);  // 0x77F208
                if (a1 != a3) {
                    // 0x004f0494
                    charge(ctx, 9);
                    v1 = 0x780000;
                    a0 = sll(a1, 1);
                    lw(v1, v1, -3564);  // 0x77F214
                    a0 = addu(a0, a1);
                    a0 = sll(a0, 2);
                    v1 = addu(v1, a0);
                    lw(v1, v1, 0);
                    if (v1 == 0) {
                        // 0x004f04b8
                        charge(ctx, 2);
                        v1 = 0x780000;
                        sw(a3, v1, -3540);  // 0x77F22C
                    }
                }
                // 0x004f04c0
                charge(ctx, 5);
                v1 = 0x780000;
                a1 = si(-1);
                lw(a3, v1, -3536);  // 0x77F230
                if (a3 != a1) {
                    // 0x004f04d4
                    charge(ctx, 9);
                    v1 = 0x780000;
                    a0 = sll(a3, 1);
                    lw(v1, v1, -3564);  // 0x77F214
                    a0 = addu(a0, a3);
                    a0 = sll(a0, 2);
                    v1 = addu(v1, a0);
                    lw(v1, v1, 0);
                    if (v1 == 0) {
                        // 0x004f04f8
                        charge(ctx, 2);
                        v1 = 0x780000;
                        sw(a1, v1, -3536);  // 0x77F230
                    }
                }
                // 0x004f0500
                charge(ctx, 5);
                v1 = 0x780000;
                a0 = si(-1);
                lw(a1, v1, -3580);  // 0x77F204
                if (a1 == a0) {
                    goto L_004f05f0;
                }
                // 0x004f0514
                charge(ctx, 5);
                v1 = 0x780000;
                t1 = addiu(a1, 1);
                lw(t0, v1, -3568);  // 0x77F210
                if (t1 == t0) {
                    // 0x004f0528
                    charge(ctx, 1);
                    t1 = 0;
                }
                // 0x004f052c
                charge(ctx, 2);
                if (t1 == t2) {
                    // 0x004f080c
                    charge(ctx, 4);
                    v1 = 0x780000;
                    lw(v1, v1, -3540);  // 0x77F22C
                    if (t2 != v1) {
                        // 0x004f081c
                        charge(ctx, 4);
                        v1 = 0x780000;
                        lw(v1, v1, -3536);  // 0x77F230
                        if (t2 != v1) {
                            // 0x004f082c
                            charge(ctx, 3);
                            t2 = addiu(t2, 1);
                            if (t2 != t0) {
                                backedge(ctx);
                            } else {
                                // 0x004f0838
                                charge(ctx, 2);
                                t2 = 0;
                                backedge(ctx);
                            }
                            goto L_004f0534;
                        }
                    }
                    goto L_004f096c;
                }
            L_004f0534:
                charge(ctx, 22);
                v1 = 0x780000;
                a0 = sll(a1, 1);
                lw(a3, v1, -3564);  // 0x77F214
                a0 = addu(a0, a1);
                t3 = sll(a0, 2);
                lw(t5, s1, 48);
                t4 = si(-2048);
                v1 = sll(t2, 1);
                t3 = addu(t3, a3);
                a0 = addu(v1, t2);
                t5 = addiu(t5, 2047);
                a1 = sll(a0, 2);
                v1 = 0x780000;
                t8 = addu(a3, a1);
                lw(a0, v1, -3540);  // 0x77F22C
                lw(a1, t3, 4);
                t4 = t5 & t4;
                t7 = addu(s0, t4);
                v1 = 0x780000;
                lw(t3, t3, 8);
                lw(v1, v1, -3536);  // 0x77F230
                t6 = addu(a1, t3);
                for (;;) {
                    // 0x004f058c
                    charge(ctx, 2);
                    if (t1 == t2) {
                        goto L_004f05f0;
                    }
                    // 0x004f0594
                    charge(ctx, 3);
                    lw(t5, t8, 0);
                    if (t5 != 0) {
                        // 0x004f05a0
                        charge(ctx, 4);
                        lw(t4, t8, 4);
                        t3 = sltu(a1, t4);
                        if (t3 == 0) {
                            // 0x004f05b0
                            charge(ctx, 3);
                            at = sltu(t4, t7);
                            if (at == 0) {
                                goto L_004f05c8;
                            }
                            // 0x004f05bc
                            charge(ctx, 3);
                            at = sltu(t4, s0);
                            if (at == 0) {
                                goto L_004f0840;
                            }
                            goto L_004f05c8;
                        }
                    L_004f05c8:
                        charge(ctx, 3);
                        at = sltu(a1, t4);
                        if (at == 0) {
                            goto L_004f05f0;
                        }
                        // 0x004f05d4
                        charge(ctx, 3);
                        at = sltu(s0, t6);
                        if (at == 0) {
                            // 0x004f0888
                            charge(ctx, 3);
                            at = sltu(t4, t7);
                            if (at != 0) {
                                backedge(ctx);
                                goto L_004f0840;
                            }
                            // 0x004f0894
                            charge(ctx, 2);
                            backedge(ctx);
                            goto L_004f05e0;
                        }
                    L_004f05e0:
                        charge(ctx, 3);
                        at = sltu(a1, s0);
                        if (at == 0) {
                            goto L_004f0840;
                        }
                        break;
                    }
                L_004f0840:
                    charge(ctx, 2);
                    if (t5 != 0) {
                        // 0x004f0848
                        charge(ctx, 2);
                        if (t2 == a0) {
                            goto L_004f0858;
                        }
                        // 0x004f0850
                        charge(ctx, 2);
                        if (t2 != v1) {
                            goto L_004f0860;
                        }
                        goto L_004f0858;
                    }
                L_004f0860:
                    charge(ctx, 3);
                    t2 = addiu(t2, 1);
                    if (t2 == t0) {
                        // 0x004f086c
                        charge(ctx, 1);
                        t2 = 0;
                    }
                    // 0x004f0870
                    charge(ctx, 5);
                    t3 = sll(t2, 1);
                    t3 = addu(t3, t2);
                    t3 = sll(t3, 2);
                    t8 = addu(a3, t3);
                    backedge(ctx);
                }
                // 0x004f05ec
                charge(ctx, 1);
                goto L_004f05f0;
            }
        L_004f05f0:
            charge(ctx, 3);
            lw(v0, s1, 88);
            if (v0 != 0) {
                // 0x004f05fc
                charge(ctx, 2);
                sw(zero, v0, 0);
                sw(zero, s1, 88);
            }
            // 0x004f0604
            charge(ctx, 8);
            a0 = s2;
            a1 = s0;
            jal(ctx, 0x4F0608u, gen::fn_sub_4EFA00_004efa00);
            v1 = 0x780000;
            a0 = si(-1);
            lw(v1, v1, -3580);  // 0x77F204
            if (v1 == a0) {
                // 0x004f0918
                charge(ctx, 21);
                v1 = 0x780000;
                sw(zero, v1, -3580);  // 0x77F204
                a1 = 0x780000;
                v1 = 0x780000;
                a0 = 0x780000;
                sw(zero, v1, -3576);  // 0x77F208
                a2 = si(-2048);
                v1 = 0x780000;
                lw(a3, v1, -3564);  // 0x77F214
                sw(s2, a3, 0);
                v1 = 0x780000;
                lw(a1, a1, -3564);  // 0x77F214
                sw(a1, s1, 88);
                lw(a0, a0, -3564);  // 0x77F214
                sw(s0, a0, 4);
                lw(a0, s1, 48);
                lw(v1, v1, -3564);  // 0x77F214
                a0 = addiu(a0, 2047);
                a0 = a0 & a2;
                sw(a0, v1, 8);
                backedge(ctx);
            } else {
                // 0x004f0624
                charge(ctx, 5);
                a3 = addiu(v1, 1);
                v1 = 0x780000;
                lw(v1, v1, -3568);  // 0x77F210
                if (a3 == v1) {
                    // 0x004f0638
                    charge(ctx, 1);
                    a3 = 0;
                }
                // 0x004f063c
                charge(ctx, 4);
                v1 = 0x780000;
                lw(v1, v1, -3576);  // 0x77F208
                if (a3 == v1) {
                    // 0x004f064c
                    charge(ctx, 9);
                    v1 = 0x780000;
                    a0 = sll(a3, 1);
                    lw(v1, v1, -3564);  // 0x77F214
                    a0 = addu(a0, a3);
                    a0 = sll(a0, 2);
                    v1 = addu(v1, a0);
                    lw(a0, v1, 0);
                    if (a0 != 0) {
                        // 0x004f0670
                        charge(ctx, 5);
                        lw(v1, gp, -16968);  // 0x7CEAA8
                        a0 = addu(a0, v1);
                        lw(v1, a0, 88);
                        sw(zero, v1, 0);
                        sw(zero, a0, 88);
                    }
                    // 0x004f0684
                    charge(ctx, 8);
                    v1 = 0x780000;
                    a0 = 0x780000;
                    lw(a1, v1, -3576);  // 0x77F208
                    v1 = 0x780000;
                    a1 = addiu(a1, 1);
                    lw(v1, v1, -3568);  // 0x77F210
                    sw(a1, a0, -3576);  // 0x77F208
                    if (a1 == v1) {
                        // 0x004f06a4
                        charge(ctx, 2);
                        v1 = 0x780000;
                        sw(zero, v1, -3576);  // 0x77F208
                    }
                }
                // 0x004f06ac
                charge(ctx, 47);
                v1 = 0x780000;
                a0 = sll(a3, 1);
                lw(t4, v1, -3564);  // 0x77F214
                a0 = addu(a0, a3);
                t2 = 0x780000;
                t1 = 0x780000;
                t3 = si(-2048);
                a2 = 0x780000;
                t0 = 0x780000;
                a1 = 0x780000;
                t5 = 0x780000;
                v1 = sll(a0, 2);
                t4 = addu(t4, v1);
                a0 = 0x780000;
                sw(s2, t4, 0);
                lw(t2, t2, -3564);  // 0x77F214
                t4 = 0x780000;
                t2 = addu(t2, v1);
                sw(t2, s1, 88);
                lw(t1, t1, -3564);  // 0x77F214
                t2 = 0x780000;
                t1 = addu(v1, t1);
                sw(s0, t1, 4);
                lw(t1, s1, 48);
                lw(a0, a0, -3564);  // 0x77F214
                t1 = addiu(t1, 2047);
                t1 = t1 & t3;
                v1 = addu(v1, a0);
                sw(t1, v1, 8);
                a0 = addu(s0, t1);
                lw(t1, a2, -3564);  // 0x77F214
                t3 = 0x780000;
                lw(t0, t0, -3580);  // 0x77F204
                lw(a2, a1, -3576);  // 0x77F208
                v1 = sll(t0, 1);
                v1 = addu(v1, t0);
                a1 = sll(v1, 2);
                v1 = sll(a2, 1);
                t0 = addu(a1, t1);
                v1 = addu(v1, a2);
                lw(a1, t0, 4);
                v1 = sll(v1, 2);
                s1 = addu(t1, v1);
                lw(v1, t0, 8);
                t1 = 0x780000;
                v1 = addu(a1, v1);
                t0 = 0x780000;
                for (;;) {
                    // 0x004f0768
                    charge(ctx, 5);
                    lw(t7, s1, 0);
                    t6 = sltu(0, t7);
                    t6 = t6 ^ 0x1;
                    if (t6 == 0) {
                        goto L_004f077c_50;
                    }
                L_004f08a0:
                    charge(ctx, 2);
                    if (t7 != 0) {
                        // 0x004f08a8
                        charge(ctx, 6);
                        lw(a2, gp, -16968);  // 0x7CEAA8
                        t6 = addu(t7, a2);
                        lw(a2, t6, 88);
                        sw(zero, a2, 0);
                        sw(zero, t6, 88);
                    }
                    // 0x004f08c0
                    charge(ctx, 5);
                    lw(t6, t5, -3576);
                    lw(a2, t3, -3568);
                    t6 = addiu(t6, 1);
                    sw(t6, t4, -3576);
                    if (t6 == a2) {
                        // 0x004f08f8
                        charge(ctx, 2);
                        sw(zero, t0, -3576);
                        backedge(ctx);
                    } else {
                        // 0x004f08d4
                        charge(ctx, 1);
                    }
                    // 0x004f08d8
                    charge(ctx, 7);
                    lw(a2, t2, -3576);
                    lw(t6, t1, -3564);
                    t7 = sll(a2, 1);
                    t7 = addu(t7, a2);
                    t7 = sll(t7, 2);
                    s1 = addu(t6, t7);
                    backedge(ctx);
                }
            L_004f07d4_58:
                charge(ctx, 1);
            L_004f07d8:
                charge(ctx, 2);
                v1 = 0x780000;
                sw(a3, v1, -3580);  // 0x77F204
            }
            // 0x004f07e0
            charge(ctx, 2);
            goto L_004f096c;
        }
    L_004f07e8:
        charge(ctx, 7);
        a0 = 0x780000;
        lw(a1, s1, 48);
        lw(s0, a0, -3560);  // 0x77F218
        a0 = subu(t0, s0);
        a0 = sltu(a0, a1);
        if (a0 == 0) {
            // 0x004f0804
            charge(ctx, 2);
            backedge(ctx);
            goto L_004f046c;
        }
    }
    goto L_004f096c;
L_004f077c_50:
    charge(ctx, 2);
    if (a3 == a2) {
        goto L_004f07d8;
    }
    // 0x004f0784
    charge(ctx, 4);
    lw(t6, s1, 4);
    a2 = sltu(a1, t6);
    if (a2 == 0) {
        // 0x004f0794
        charge(ctx, 3);
        at = sltu(t6, a0);
        if (at == 0) {
            goto L_004f07b0;
        }
        // 0x004f07a0
        charge(ctx, 3);
        at = sltu(t6, s0);
        if (at == 0) {
            goto L_004f08a0;
        }
        // 0x004f07ac
        charge(ctx, 1);
        goto L_004f07b0;
    }
L_004f07b0:
    charge(ctx, 3);
    at = sltu(a1, t6);
    if (at == 0) {
        goto L_004f07d8;
    }
    // 0x004f07bc
    charge(ctx, 3);
    at = sltu(s0, v1);
    if (at == 0) {
        // 0x004f0900
        charge(ctx, 3);
        at = sltu(t6, a0);
        if (at != 0) {
            backedge(ctx);
            goto L_004f08a0;
        }
        // 0x004f090c
        charge(ctx, 2);
        backedge(ctx);
        goto L_004f07c8;
    }
L_004f07c8:
    charge(ctx, 3);
    at = sltu(a1, s0);
    if (at == 0) {
        goto L_004f08a0;
    }
    goto L_004f07d4_58;
L_004f0858:
    charge(ctx, 2);
    goto L_004f096c;
}

// sub_4F0AD0 [skyTexCacheReset] -- resets the sky driver's texture cache: on a reopen every resident raster's cache
//   link cleared and the ring freed; then the cache state (0x77F200..0x77F238) back to empty; 1
// 0x004F0AD0 sub_4F0AD0 -- 388 bytes; frame 0x10: ra sp+0x0
void sub_4F0AD0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f0ad0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x780000;
    sd(ra, sp, 0x0);
    lw(v0, v0, -3584);  // 0x77F200
    if (v0 != 0) {
        // 0x004f0ae8
        charge(ctx, 6);
        v1 = 0x780000;
        v0 = 0x780000;
        lw(a3, v1, -3576);  // 0x77F208
        lw(v0, v0, -3580);  // 0x77F204
        if (a3 != v0) {
            // 0x004f0b00
            charge(ctx, 3);
            v1 = 0x780000;
            v0 = 0x780000;
            a0 = 0x780000;
            for (;;) {
                // 0x004f0b0c
                charge(ctx, 8);
                lw(a1, a0, -3564);
                a2 = sll(a3, 1);
                a2 = addu(a2, a3);
                a2 = sll(a2, 2);
                a1 = addu(a1, a2);
                lw(a2, a1, 0);
                if (a2 != 0) {
                    // 0x004f0b2c
                    charge(ctx, 3);
                    lw(a1, gp, -16968);  // 0x7CEAA8
                    a1 = addu(a2, a1);
                    sw(zero, a1, 88);
                }
                // 0x004f0b38
                charge(ctx, 7);
                lw(a1, v1, -3568);
                a2 = addiu(a3, 1);
                divu(a2, a1);
                mfhi(a3);
                lw(a1, v0, -3580);
                if (a3 == a1) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004f0b54
            charge(ctx, 1);
        }
        // 0x004f0b58
        charge(ctx, 7);
        v0 = 0x780000;
        lw(a2, v0, -3568);  // 0x77F210
        v0 = 0x780000;
        lw(v0, v0, -3572);  // 0x77F20C
        at = sltu(a2, v0);
        if (at != 0) {
            // 0x004f0b74
            charge(ctx, 5);
            v0 = sll(a2, 1);
            v1 = 0x780000;
            v0 = addu(v0, a2);
            a3 = sll(v0, 2);
            v0 = 0x780000;
            for (;;) {
                // 0x004f0b88
                charge(ctx, 5);
                lw(a0, v1, -3564);
                a0 = addu(a0, a3);
                lw(a1, a0, 0);
                if (a1 != 0) {
                    // 0x004f0b9c
                    charge(ctx, 5);
                    lw(a0, gp, -16968);  // 0x7CEAA8
                    a0 = addu(a1, a0);
                    sb(zero, a0, 23);
                    sw(zero, a0, 88);
                }
                // 0x004f0bb0
                charge(ctx, 5);
                lw(a0, v0, -3572);
                a2 = addiu(a2, 1);
                a0 = sltu(a2, a0);
                a3 = addiu(a3, 12);
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004f0bc4
            charge(ctx, 1);
        }
        // 0x004f0bc8
        charge(ctx, 6);
        v0 = 0x780000;
        lw(a0, v0, -3564);  // 0x77F214
        v0 = 0x960000;
        lw(v0, v0, 380);  // 0x96017C
        jalr(ctx, 0x4F0BD8u, v0.u());
    }
    // 0x004f0be0
    charge(ctx, 29);
    v0 = 1;
    v1 = 0x780000;
    sw(v0, v1, -3584);  // 0x77F200
    a1 = si(-1);
    v1 = 0x780000;
    a0 = 0x780000;
    sw(zero, v1, -3580);  // 0x77F204
    v1 = 0x780000;
    sw(a1, a0, -3560);  // 0x77F218
    sw(zero, v1, -3576);  // 0x77F208
    a0 = 0x780000;
    v1 = 0x780000;
    sw(a1, a0, -3556);  // 0x77F21C
    sw(zero, v1, -3572);  // 0x77F20C
    a0 = 0x780000;
    v1 = 0x780000;
    sw(zero, a0, -3548);  // 0x77F224
    sw(zero, v1, -3568);  // 0x77F210
    v1 = 0x780000;
    sw(zero, v1, -3564);  // 0x77F214
    v1 = 0x780000;
    sw(a1, v1, -3532);  // 0x77F234
    v1 = 0x780000;
    sw(zero, v1, -3552);  // 0x77F220
    v1 = 0x780000;
    sw(zero, v1, -3528);  // 0x77F238
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// sub_4F1E10 [skyTexCacheGetBase] -- returns the texture cache's start word (0x77F21C)
// 0x004F1E10 sub_4F1E10 -- 12 bytes; leaf frame (no stack)
void sub_4F1E10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x004f1e10
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x780000;
    lw(v0, v0, -3556);  // 0x77F21C
}

}  // namespace p3fes::game
