// Pair tests for slice sweep5a (H_Cdvd / H_Pad / H_malloc / BGM / sprite / message-manager / battle / facility
// bodies, the libkernel syscall wrappers and the libc / CRI thunks): every hand body against its recompiled body,
// compared by tests/game/handgen_pairs.h -- the whole register file and cycle count at every check point and at the
// return / stop, all 32 MiB of RAM, the scratchpad, the BIOS window and the bus log. Worlds: random ones, the five
// replay snapshots' RAM (the real globals), and fixed records for the accessor / sound-slot / sprintf rules checked on
// the host.
#include "handgen_pairs.h"

#include "stand_ins.h"

#include "p3fes/game/sweep5a.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <random>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_H_Cdvd_FileExists_001008b0(EEContext&);  // generated body
void fn_H_Cdvd_FileExists_001008b0__recomp(EEContext&);  // recompiled
void fn_H_Cdvd_Update_00100980(EEContext&);  // generated body
void fn_H_Cdvd_Update_00100980__recomp(EEContext&);  // recompiled
void fn_H_Cdvd_Request_00100d80(EEContext&);  // generated body
void fn_H_Cdvd_Request_00100d80__recomp(EEContext&);  // recompiled
void fn_H_Cdvd_Destroy_00100ec0(EEContext&);  // generated body
void fn_H_Cdvd_Destroy_00100ec0__recomp(EEContext&);  // recompiled
void fn_H_Cdvd_ReadSync_001023a0(EEContext&);  // generated body
void fn_H_Cdvd_ReadSync_001023a0__recomp(EEContext&);  // recompiled
void fn_H_Pad_UpdateWorkPad_00103110(EEContext&);  // generated body
void fn_H_Pad_UpdateWorkPad_00103110__recomp(EEContext&);  // recompiled
void fn_sub_103F50_00103f50(EEContext&);  // generated body
void fn_sub_103F50_00103f50__recomp(EEContext&);  // recompiled
void fn_sub_104040_00104040(EEContext&);  // generated body
void fn_sub_104040_00104040__recomp(EEContext&);  // recompiled
void fn_sub_104140_00104140(EEContext&);  // generated body
void fn_sub_104140_00104140__recomp(EEContext&);  // recompiled
void fn_sub_104280_00104280(EEContext&);  // generated body
void fn_sub_104280_00104280__recomp(EEContext&);  // recompiled
void fn_sub_108F70_00108f70(EEContext&);  // generated body
void fn_sub_108F70_00108f70__recomp(EEContext&);  // recompiled
void fn_sub_108FD0_00108fd0(EEContext&);  // generated body
void fn_sub_108FD0_00108fd0__recomp(EEContext&);  // recompiled
void fn_sub_109180_00109180(EEContext&);  // generated body
void fn_sub_109180_00109180__recomp(EEContext&);  // recompiled
void fn_sub_1099D0_001099d0(EEContext&);  // generated body
void fn_sub_1099D0_001099d0__recomp(EEContext&);  // recompiled
void fn_sub_109AE0_00109ae0(EEContext&);  // generated body
void fn_sub_109AE0_00109ae0__recomp(EEContext&);  // recompiled
void fn_sub_109DF0_00109df0(EEContext&);  // generated body
void fn_sub_109DF0_00109df0__recomp(EEContext&);  // recompiled
void fn_sub_109F60_00109f60(EEContext&);  // generated body
void fn_sub_109F60_00109f60__recomp(EEContext&);  // recompiled
void fn_sub_10A0E0_0010a0e0(EEContext&);  // generated body
void fn_sub_10A0E0_0010a0e0__recomp(EEContext&);  // recompiled
void fn_sub_10A100_0010a100(EEContext&);  // generated body
void fn_sub_10A100_0010a100__recomp(EEContext&);  // recompiled
void fn_sub_10A240_0010a240(EEContext&);  // generated body
void fn_sub_10A240_0010a240__recomp(EEContext&);  // recompiled
void fn_sub_10A370_0010a370(EEContext&);  // generated body
void fn_sub_10A370_0010a370__recomp(EEContext&);  // recompiled
void fn_sub_10A720_0010a720(EEContext&);  // generated body
void fn_sub_10A720_0010a720__recomp(EEContext&);  // recompiled
void fn_sub_10A860_0010a860(EEContext&);  // generated body
void fn_sub_10A860_0010a860__recomp(EEContext&);  // recompiled
void fn_sub_10C1A0_0010c1a0(EEContext&);  // generated body
void fn_sub_10C1A0_0010c1a0__recomp(EEContext&);  // recompiled
void fn_sub_10C3A0_0010c3a0(EEContext&);  // generated body
void fn_sub_10C3A0_0010c3a0__recomp(EEContext&);  // recompiled
void fn_H_Sndcom_UnbindSfx_0010d950(EEContext&);  // generated body
void fn_H_Sndcom_UnbindSfx_0010d950__recomp(EEContext&);  // recompiled
void fn_uttmxCreateRaster_0010e880(EEContext&);  // generated body
void fn_uttmxCreateRaster_0010e880__recomp(EEContext&);  // recompiled
void fn_sub_111C50_00111c50(EEContext&);  // generated body
void fn_sub_111C50_00111c50__recomp(EEContext&);  // recompiled
void fn_sub_111CB0_00111cb0(EEContext&);  // generated body
void fn_sub_111CB0_00111cb0__recomp(EEContext&);  // recompiled
void fn_sub_111D50_00111d50(EEContext&);  // generated body
void fn_sub_111D50_00111d50__recomp(EEContext&);  // recompiled
void fn_sub_111DD0_00111dd0(EEContext&);  // generated body
void fn_sub_111DD0_00111dd0__recomp(EEContext&);  // recompiled
void fn_sub_111EC0_00111ec0(EEContext&);  // generated body
void fn_sub_111EC0_00111ec0__recomp(EEContext&);  // recompiled
void fn_sub_111EE0_00111ee0(EEContext&);  // generated body
void fn_sub_111EE0_00111ee0__recomp(EEContext&);  // recompiled
void fn_sub_111F20_00111f20(EEContext&);  // generated body
void fn_sub_111F20_00111f20__recomp(EEContext&);  // recompiled
void fn_sprFileHandleUpdate_00112110(EEContext&);  // generated body
void fn_sprFileHandleUpdate_00112110__recomp(EEContext&);  // recompiled
void fn_sprCreateHandleFromData_00112420(EEContext&);  // generated body
void fn_sprCreateHandleFromData_00112420__recomp(EEContext&);  // recompiled
void fn_sub_1124B0_001124b0(EEContext&);  // generated body
void fn_sub_1124B0_001124b0__recomp(EEContext&);  // recompiled
void fn_sprDrawSpriteBasic_001159f0(EEContext&);  // generated body
void fn_sprDrawSpriteBasic_001159f0__recomp(EEContext&);  // recompiled
void fn_sub_115AD0_00115ad0(EEContext&);  // generated body
void fn_sub_115AD0_00115ad0__recomp(EEContext&);  // recompiled
void fn_sub_115BC0_00115bc0(EEContext&);  // generated body
void fn_sub_115BC0_00115bc0__recomp(EEContext&);  // recompiled
void fn_sub_1712D0_001712d0(EEContext&);  // generated body
void fn_sub_1712D0_001712d0__recomp(EEContext&);  // recompiled
void fn_sub_191A10_00191a10(EEContext&);  // generated body
void fn_sub_191A10_00191a10__recomp(EEContext&);  // recompiled
void fn_sub_191AF0_00191af0(EEContext&);  // generated body
void fn_sub_191AF0_00191af0__recomp(EEContext&);  // recompiled
void fn_sub_1A4580_001a4580(EEContext&);  // generated body
void fn_sub_1A4580_001a4580__recomp(EEContext&);  // recompiled
void fn_sub_1A91B0_001a91b0(EEContext&);  // generated body
void fn_sub_1A91B0_001a91b0__recomp(EEContext&);  // recompiled
void fn_sub_20F570_0020f570(EEContext&);  // generated body
void fn_sub_20F570_0020f570__recomp(EEContext&);  // recompiled
void fn_sub_233E70_00233e70(EEContext&);  // generated body
void fn_sub_233E70_00233e70__recomp(EEContext&);  // recompiled
void fn_sub_242600_00242600(EEContext&);  // generated body
void fn_sub_242600_00242600__recomp(EEContext&);  // recompiled
void fn_sub_245EA0_00245ea0(EEContext&);  // generated body
void fn_sub_245EA0_00245ea0__recomp(EEContext&);  // recompiled
void fn_sub_24F090_0024f090(EEContext&);  // generated body
void fn_sub_24F090_0024f090__recomp(EEContext&);  // recompiled
void fn_sub_257130_00257130(EEContext&);  // generated body
void fn_sub_257130_00257130__recomp(EEContext&);  // recompiled
void fn_sub_258630_00258630(EEContext&);  // generated body
void fn_sub_258630_00258630__recomp(EEContext&);  // recompiled
void fn_sub_25AAD0_0025aad0(EEContext&);  // generated body
void fn_sub_25AAD0_0025aad0__recomp(EEContext&);  // recompiled
void fn_sub_2813F0_002813f0(EEContext&);  // generated body
void fn_sub_2813F0_002813f0__recomp(EEContext&);  // recompiled
void fn_sub_281F20_00281f20(EEContext&);  // generated body
void fn_sub_281F20_00281f20__recomp(EEContext&);  // recompiled
void fn_sub_282D40_00282d40(EEContext&);  // generated body
void fn_sub_282D40_00282d40__recomp(EEContext&);  // recompiled
void fn_sub_2849A0_002849a0(EEContext&);  // generated body
void fn_sub_2849A0_002849a0__recomp(EEContext&);  // recompiled
void fn_sub_2879F0_002879f0(EEContext&);  // generated body
void fn_sub_2879F0_002879f0__recomp(EEContext&);  // recompiled
void fn_sub_287EA0_00287ea0(EEContext&);  // generated body
void fn_sub_287EA0_00287ea0__recomp(EEContext&);  // recompiled
void fn_sub_288110_00288110(EEContext&);  // generated body
void fn_sub_288110_00288110__recomp(EEContext&);  // recompiled
void fn_sub_28AA20_0028aa20(EEContext&);  // generated body
void fn_sub_28AA20_0028aa20__recomp(EEContext&);  // recompiled
void fn_sub_28DF00_0028df00(EEContext&);  // generated body
void fn_sub_28DF00_0028df00__recomp(EEContext&);  // recompiled
void fn_sub_338D60_00338d60(EEContext&);  // generated body
void fn_sub_338D60_00338d60__recomp(EEContext&);  // recompiled
void fn_sub_342890_00342890(EEContext&);  // generated body
void fn_sub_342890_00342890__recomp(EEContext&);  // recompiled
void fn_sub_34A650_0034a650(EEContext&);  // generated body
void fn_sub_34A650_0034a650__recomp(EEContext&);  // recompiled
void fn_sub_34AE30_0034ae30(EEContext&);  // generated body
void fn_sub_34AE30_0034ae30__recomp(EEContext&);  // recompiled
void fn_sub_358030_00358030(EEContext&);  // generated body
void fn_sub_358030_00358030__recomp(EEContext&);  // recompiled
void fn_sub_3A2A30_003a2a30(EEContext&);  // generated body
void fn_sub_3A2A30_003a2a30__recomp(EEContext&);  // recompiled
void fn_itfMesMngInitialize_003a2d80(EEContext&);  // generated body
void fn_itfMesMngInitialize_003a2d80__recomp(EEContext&);  // recompiled
void fn_itfMesMngDestroyHandle_003a3060(EEContext&);  // generated body
void fn_itfMesMngDestroyHandle_003a3060__recomp(EEContext&);  // recompiled
void fn_itfMesMngRequestMessage_003a30c0(EEContext&);  // generated body
void fn_itfMesMngRequestMessage_003a30c0__recomp(EEContext&);  // recompiled
void fn_sub_3A3420_003a3420(EEContext&);  // generated body
void fn_sub_3A3420_003a3420__recomp(EEContext&);  // recompiled
void fn_sub_3A37C0_003a37c0(EEContext&);  // generated body
void fn_sub_3A37C0_003a37c0__recomp(EEContext&);  // recompiled
void fn_sub_3A4010_003a4010(EEContext&);  // generated body
void fn_sub_3A4010_003a4010__recomp(EEContext&);  // recompiled
void fn_sub_3A4360_003a4360(EEContext&);  // generated body
void fn_sub_3A4360_003a4360__recomp(EEContext&);  // recompiled
void fn_itfMesMngChangeWindowType_003a4990(EEContext&);  // generated body
void fn_itfMesMngChangeWindowType_003a4990__recomp(EEContext&);  // recompiled
void fn_sub_3D06D0_003d06d0(EEContext&);  // generated body
void fn_sub_3D06D0_003d06d0__recomp(EEContext&);  // recompiled
void fn_sub_3D1DF0_003d1df0(EEContext&);  // generated body
void fn_sub_3D1DF0_003d1df0__recomp(EEContext&);  // recompiled
void fn_sub_3D2200_003d2200(EEContext&);  // generated body
void fn_sub_3D2200_003d2200__recomp(EEContext&);  // recompiled
void fn_sub_3D32E0_003d32e0(EEContext&);  // generated body
void fn_sub_3D32E0_003d32e0__recomp(EEContext&);  // recompiled
void fn_sub_3D3620_003d3620(EEContext&);  // generated body
void fn_sub_3D3620_003d3620__recomp(EEContext&);  // recompiled
void fn_sub_3D38B0_003d38b0(EEContext&);  // generated body
void fn_sub_3D38B0_003d38b0__recomp(EEContext&);  // recompiled
void fn_sub_3D8850_003d8850(EEContext&);  // generated body
void fn_sub_3D8850_003d8850__recomp(EEContext&);  // recompiled
void fn_sub_3DB650_003db650(EEContext&);  // generated body
void fn_sub_3DB650_003db650__recomp(EEContext&);  // recompiled
void fn_sub_3DD260_003dd260(EEContext&);  // generated body
void fn_sub_3DD260_003dd260__recomp(EEContext&);  // recompiled
void fn_sub_3E9AF0_003e9af0(EEContext&);  // generated body
void fn_sub_3E9AF0_003e9af0__recomp(EEContext&);  // recompiled
void fn_sub_3EA820_003ea820(EEContext&);  // generated body
void fn_sub_3EA820_003ea820__recomp(EEContext&);  // recompiled
void fn_sub_3EE920_003ee920(EEContext&);  // generated body
void fn_sub_3EE920_003ee920__recomp(EEContext&);  // recompiled
void fn_sub_3EEE80_003eee80(EEContext&);  // generated body
void fn_sub_3EEE80_003eee80__recomp(EEContext&);  // recompiled
void fn_sub_3EF2B0_003ef2b0(EEContext&);  // generated body
void fn_sub_3EF2B0_003ef2b0__recomp(EEContext&);  // recompiled
void fn_sub_3F1DC0_003f1dc0(EEContext&);  // generated body
void fn_sub_3F1DC0_003f1dc0__recomp(EEContext&);  // recompiled
void fn_sub_3F45E0_003f45e0(EEContext&);  // generated body
void fn_sub_3F45E0_003f45e0__recomp(EEContext&);  // recompiled
void fn_sub_3F55B0_003f55b0(EEContext&);  // generated body
void fn_sub_3F55B0_003f55b0__recomp(EEContext&);  // recompiled
void fn_sub_3F8E10_003f8e10(EEContext&);  // generated body
void fn_sub_3F8E10_003f8e10__recomp(EEContext&);  // recompiled
void fn_sub_3FBC00_003fbc00(EEContext&);  // generated body
void fn_sub_3FBC00_003fbc00__recomp(EEContext&);  // recompiled
void fn_sub_3FF630_003ff630(EEContext&);  // generated body
void fn_sub_3FF630_003ff630__recomp(EEContext&);  // recompiled
void fn_sub_3FFBB0_003ffbb0(EEContext&);  // generated body
void fn_sub_3FFBB0_003ffbb0__recomp(EEContext&);  // recompiled
void fn_sub_40D640_0040d640(EEContext&);  // generated body
void fn_sub_40D640_0040d640__recomp(EEContext&);  // recompiled
void fn_sub_40E360_0040e360(EEContext&);  // generated body
void fn_sub_40E360_0040e360__recomp(EEContext&);  // recompiled
void fn_sub_4178C0_004178c0(EEContext&);  // generated body
void fn_sub_4178C0_004178c0__recomp(EEContext&);  // recompiled
void fn_sub_418230_00418230(EEContext&);  // generated body
void fn_sub_418230_00418230__recomp(EEContext&);  // recompiled
void fn_sub_418390_00418390(EEContext&);  // generated body
void fn_sub_418390_00418390__recomp(EEContext&);  // recompiled
void fn_sub_418510_00418510(EEContext&);  // generated body
void fn_sub_418510_00418510__recomp(EEContext&);  // recompiled
void fn_sub_418880_00418880(EEContext&);  // generated body
void fn_sub_418880_00418880__recomp(EEContext&);  // recompiled
void fn_sub_418C70_00418c70(EEContext&);  // generated body
void fn_sub_418C70_00418c70__recomp(EEContext&);  // recompiled
void fn_sub_419050_00419050(EEContext&);  // generated body
void fn_sub_419050_00419050__recomp(EEContext&);  // recompiled
void fn_sub_4195F0_004195f0(EEContext&);  // generated body
void fn_sub_4195F0_004195f0__recomp(EEContext&);  // recompiled
void fn_sub_419A30_00419a30(EEContext&);  // generated body
void fn_sub_419A30_00419a30__recomp(EEContext&);  // recompiled
void fn_sub_419A70_00419a70(EEContext&);  // generated body
void fn_sub_419A70_00419a70__recomp(EEContext&);  // recompiled
void fn_sub_41AE20_0041ae20(EEContext&);  // generated body
void fn_sub_41AE20_0041ae20__recomp(EEContext&);  // recompiled
void fn_sub_41B810_0041b810(EEContext&);  // generated body
void fn_sub_41B810_0041b810__recomp(EEContext&);  // recompiled
void fn_sub_41B950_0041b950(EEContext&);  // generated body
void fn_sub_41B950_0041b950__recomp(EEContext&);  // recompiled
void fn__sceMpegNextBit_004fd658(EEContext&);  // generated body
void fn__sceMpegNextBit_004fd658__recomp(EEContext&);  // recompiled
void fn__sceCreateThread_00502f60(EEContext&);  // generated body
void fn__sceCreateThread_00502f60__recomp(EEContext&);  // recompiled
void fn__sceChangeThreadPriority_00502ff0(EEContext&);  // generated body
void fn__sceChangeThreadPriority_00502ff0__recomp(EEContext&);  // recompiled
void fn__sceGetThreadId_00503050(EEContext&);  // generated body
void fn__sceGetThreadId_00503050__recomp(EEContext&);  // recompiled
void fn__sceReferThreadStatus_00503060(EEContext&);  // generated body
void fn__sceReferThreadStatus_00503060__recomp(EEContext&);  // recompiled
void fn__sceCreateSema_00503160(EEContext&);  // generated body
void fn__sceCreateSema_00503160__recomp(EEContext&);  // recompiled
void fn__sceDeleteSema_00503170(EEContext&);  // generated body
void fn__sceDeleteSema_00503170__recomp(EEContext&);  // recompiled
void fn__sceSignalSema_00503180(EEContext&);  // generated body
void fn__sceSignalSema_00503180__recomp(EEContext&);  // recompiled
void fn__sceiSignalSema_00503190(EEContext&);  // generated body
void fn__sceiSignalSema_00503190__recomp(EEContext&);  // recompiled
void fn__sceWaitSema_005031a0(EEContext&);  // generated body
void fn__sceWaitSema_005031a0__recomp(EEContext&);  // recompiled
void fn__sceDeci2Call_00503590(EEContext&);  // generated body
void fn__sceDeci2Call_00503590__recomp(EEContext&);  // recompiled
void fn_scePrintf_00505e48(EEContext&);  // generated body
void fn_scePrintf_00505e48__recomp(EEContext&);  // recompiled
void fn_scePadGetDmaStr_00511830(EEContext&);  // generated body
void fn_scePadGetDmaStr_00511830__recomp(EEContext&);  // recompiled
void fn_sceSdRemote_005129c0(EEContext&);  // generated body
void fn_sceSdRemote_005129c0__recomp(EEContext&);  // recompiled
void fn_sceMc2GetInfoAsync_005136f8(EEContext&);  // generated body
void fn_sceMc2GetInfoAsync_005136f8__recomp(EEContext&);  // recompiled
void fn_sceMc2Sync2_00514858(EEContext&);  // generated body
void fn_sceMc2Sync2_00514858__recomp(EEContext&);  // recompiled
void fn_sprintf_00523ac8(EEContext&);  // generated body
void fn_sprintf_00523ac8__recomp(EEContext&);  // recompiled
void fn_vsprintf_005288c8(EEContext&);  // generated body
void fn_vsprintf_005288c8__recomp(EEContext&);  // recompiled
void fn_sub_546270_00546270(EEContext&);  // generated body
void fn_sub_546270_00546270__recomp(EEContext&);  // recompiled
void fn_sub_546368_00546368(EEContext&);  // generated body
void fn_sub_546368_00546368__recomp(EEContext&);  // recompiled
void fn_sub_5463A8_005463a8(EEContext&);  // generated body
void fn_sub_5463A8_005463a8__recomp(EEContext&);  // recompiled
void fn_sub_546498_00546498(EEContext&);  // generated body
void fn_sub_546498_00546498__recomp(EEContext&);  // recompiled
void fn_sub_546718_00546718(EEContext&);  // generated body
void fn_sub_546718_00546718__recomp(EEContext&);  // recompiled
void fn_sub_546FA0_00546fa0(EEContext&);  // generated body
void fn_sub_546FA0_00546fa0__recomp(EEContext&);  // recompiled
void fn_sceInsockSetsockopt_2_0054a928(EEContext&);  // generated body
void fn_sceInsockSetsockopt_2_0054a928__recomp(EEContext&);  // recompiled
void fn_DTX_CallUrpc_00559c10(EEContext&);  // generated body
void fn_DTX_CallUrpc_00559c10__recomp(EEContext&);  // recompiled
void fn_sub_55D668_0055d668(EEContext&);  // generated body
void fn_sub_55D668_0055d668__recomp(EEContext&);  // recompiled
void fn_sub_5753E8_005753e8(EEContext&);  // generated body
void fn_sub_5753E8_005753e8__recomp(EEContext&);  // recompiled
void fn_sub_575410_00575410(EEContext&);  // generated body
void fn_sub_575410_00575410__recomp(EEContext&);  // recompiled
void fn_sub_575880_00575880(EEContext&);  // generated body
void fn_sub_575880_00575880__recomp(EEContext&);  // recompiled
void fn_sub_589D10_00589d10(EEContext&);  // generated body
void fn_sub_589D10_00589d10__recomp(EEContext&);  // recompiled
void fn_sub_58C100_0058c100(EEContext&);  // generated body
void fn_sub_58C100_0058c100__recomp(EEContext&);  // recompiled
void fn_sub_58C118_0058c118(EEContext&);  // generated body
void fn_sub_58C118_0058c118__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"H_Cdvd_FileExists", 0x1008B0, &recomp_gen::fn_H_Cdvd_FileExists_001008b0, &recomp_gen::fn_H_Cdvd_FileExists_001008b0__recomp},
    {"H_Cdvd_Update", 0x100980, &recomp_gen::fn_H_Cdvd_Update_00100980, &recomp_gen::fn_H_Cdvd_Update_00100980__recomp},
    {"H_Cdvd_Request", 0x100D80, &recomp_gen::fn_H_Cdvd_Request_00100d80, &recomp_gen::fn_H_Cdvd_Request_00100d80__recomp},
    {"H_Cdvd_Destroy", 0x100EC0, &recomp_gen::fn_H_Cdvd_Destroy_00100ec0, &recomp_gen::fn_H_Cdvd_Destroy_00100ec0__recomp},
    {"H_Cdvd_ReadSync", 0x1023A0, &recomp_gen::fn_H_Cdvd_ReadSync_001023a0, &recomp_gen::fn_H_Cdvd_ReadSync_001023a0__recomp},
    {"H_Pad_UpdateWorkPad", 0x103110, &recomp_gen::fn_H_Pad_UpdateWorkPad_00103110, &recomp_gen::fn_H_Pad_UpdateWorkPad_00103110__recomp},
    {"sub_103F50", 0x103F50, &recomp_gen::fn_sub_103F50_00103f50, &recomp_gen::fn_sub_103F50_00103f50__recomp},
    {"sub_104040", 0x104040, &recomp_gen::fn_sub_104040_00104040, &recomp_gen::fn_sub_104040_00104040__recomp},
    {"sub_104140", 0x104140, &recomp_gen::fn_sub_104140_00104140, &recomp_gen::fn_sub_104140_00104140__recomp},
    {"sub_104280", 0x104280, &recomp_gen::fn_sub_104280_00104280, &recomp_gen::fn_sub_104280_00104280__recomp},
    {"sub_108F70", 0x108F70, &recomp_gen::fn_sub_108F70_00108f70, &recomp_gen::fn_sub_108F70_00108f70__recomp},
    {"sub_108FD0", 0x108FD0, &recomp_gen::fn_sub_108FD0_00108fd0, &recomp_gen::fn_sub_108FD0_00108fd0__recomp},
    {"sub_109180", 0x109180, &recomp_gen::fn_sub_109180_00109180, &recomp_gen::fn_sub_109180_00109180__recomp},
    {"sub_1099D0", 0x1099D0, &recomp_gen::fn_sub_1099D0_001099d0, &recomp_gen::fn_sub_1099D0_001099d0__recomp},
    {"sub_109AE0", 0x109AE0, &recomp_gen::fn_sub_109AE0_00109ae0, &recomp_gen::fn_sub_109AE0_00109ae0__recomp},
    {"sub_109DF0", 0x109DF0, &recomp_gen::fn_sub_109DF0_00109df0, &recomp_gen::fn_sub_109DF0_00109df0__recomp},
    {"sub_109F60", 0x109F60, &recomp_gen::fn_sub_109F60_00109f60, &recomp_gen::fn_sub_109F60_00109f60__recomp},
    {"sub_10A0E0", 0x10A0E0, &recomp_gen::fn_sub_10A0E0_0010a0e0, &recomp_gen::fn_sub_10A0E0_0010a0e0__recomp},
    {"sub_10A100", 0x10A100, &recomp_gen::fn_sub_10A100_0010a100, &recomp_gen::fn_sub_10A100_0010a100__recomp},
    {"sub_10A240", 0x10A240, &recomp_gen::fn_sub_10A240_0010a240, &recomp_gen::fn_sub_10A240_0010a240__recomp},
    {"sub_10A370", 0x10A370, &recomp_gen::fn_sub_10A370_0010a370, &recomp_gen::fn_sub_10A370_0010a370__recomp},
    {"sub_10A720", 0x10A720, &recomp_gen::fn_sub_10A720_0010a720, &recomp_gen::fn_sub_10A720_0010a720__recomp},
    {"sub_10A860", 0x10A860, &recomp_gen::fn_sub_10A860_0010a860, &recomp_gen::fn_sub_10A860_0010a860__recomp},
    {"sub_10C1A0", 0x10C1A0, &recomp_gen::fn_sub_10C1A0_0010c1a0, &recomp_gen::fn_sub_10C1A0_0010c1a0__recomp},
    {"sub_10C3A0", 0x10C3A0, &recomp_gen::fn_sub_10C3A0_0010c3a0, &recomp_gen::fn_sub_10C3A0_0010c3a0__recomp},
    {"H_Sndcom_UnbindSfx", 0x10D950, &recomp_gen::fn_H_Sndcom_UnbindSfx_0010d950, &recomp_gen::fn_H_Sndcom_UnbindSfx_0010d950__recomp},
    {"uttmxCreateRaster", 0x10E880, &recomp_gen::fn_uttmxCreateRaster_0010e880, &recomp_gen::fn_uttmxCreateRaster_0010e880__recomp},
    {"sub_111C50", 0x111C50, &recomp_gen::fn_sub_111C50_00111c50, &recomp_gen::fn_sub_111C50_00111c50__recomp},
    {"sub_111CB0", 0x111CB0, &recomp_gen::fn_sub_111CB0_00111cb0, &recomp_gen::fn_sub_111CB0_00111cb0__recomp},
    {"sub_111D50", 0x111D50, &recomp_gen::fn_sub_111D50_00111d50, &recomp_gen::fn_sub_111D50_00111d50__recomp},
    {"sub_111DD0", 0x111DD0, &recomp_gen::fn_sub_111DD0_00111dd0, &recomp_gen::fn_sub_111DD0_00111dd0__recomp},
    {"sub_111EC0", 0x111EC0, &recomp_gen::fn_sub_111EC0_00111ec0, &recomp_gen::fn_sub_111EC0_00111ec0__recomp},
    {"sub_111EE0", 0x111EE0, &recomp_gen::fn_sub_111EE0_00111ee0, &recomp_gen::fn_sub_111EE0_00111ee0__recomp},
    {"sub_111F20", 0x111F20, &recomp_gen::fn_sub_111F20_00111f20, &recomp_gen::fn_sub_111F20_00111f20__recomp},
    {"sprFileHandleUpdate", 0x112110, &recomp_gen::fn_sprFileHandleUpdate_00112110, &recomp_gen::fn_sprFileHandleUpdate_00112110__recomp},
    {"sprCreateHandleFromData", 0x112420, &recomp_gen::fn_sprCreateHandleFromData_00112420, &recomp_gen::fn_sprCreateHandleFromData_00112420__recomp},
    {"sub_1124B0", 0x1124B0, &recomp_gen::fn_sub_1124B0_001124b0, &recomp_gen::fn_sub_1124B0_001124b0__recomp},
    {"sprDrawSpriteBasic", 0x1159F0, &recomp_gen::fn_sprDrawSpriteBasic_001159f0, &recomp_gen::fn_sprDrawSpriteBasic_001159f0__recomp},
    {"sub_115AD0", 0x115AD0, &recomp_gen::fn_sub_115AD0_00115ad0, &recomp_gen::fn_sub_115AD0_00115ad0__recomp},
    {"sub_115BC0", 0x115BC0, &recomp_gen::fn_sub_115BC0_00115bc0, &recomp_gen::fn_sub_115BC0_00115bc0__recomp},
    {"sub_1712D0", 0x1712D0, &recomp_gen::fn_sub_1712D0_001712d0, &recomp_gen::fn_sub_1712D0_001712d0__recomp},
    {"sub_191A10", 0x191A10, &recomp_gen::fn_sub_191A10_00191a10, &recomp_gen::fn_sub_191A10_00191a10__recomp},
    {"sub_191AF0", 0x191AF0, &recomp_gen::fn_sub_191AF0_00191af0, &recomp_gen::fn_sub_191AF0_00191af0__recomp},
    {"sub_1A4580", 0x1A4580, &recomp_gen::fn_sub_1A4580_001a4580, &recomp_gen::fn_sub_1A4580_001a4580__recomp},
    {"sub_1A91B0", 0x1A91B0, &recomp_gen::fn_sub_1A91B0_001a91b0, &recomp_gen::fn_sub_1A91B0_001a91b0__recomp},
    {"sub_20F570", 0x20F570, &recomp_gen::fn_sub_20F570_0020f570, &recomp_gen::fn_sub_20F570_0020f570__recomp},
    {"sub_233E70", 0x233E70, &recomp_gen::fn_sub_233E70_00233e70, &recomp_gen::fn_sub_233E70_00233e70__recomp},
    {"sub_242600", 0x242600, &recomp_gen::fn_sub_242600_00242600, &recomp_gen::fn_sub_242600_00242600__recomp},
    {"sub_245EA0", 0x245EA0, &recomp_gen::fn_sub_245EA0_00245ea0, &recomp_gen::fn_sub_245EA0_00245ea0__recomp},
    {"sub_24F090", 0x24F090, &recomp_gen::fn_sub_24F090_0024f090, &recomp_gen::fn_sub_24F090_0024f090__recomp},
    {"sub_257130", 0x257130, &recomp_gen::fn_sub_257130_00257130, &recomp_gen::fn_sub_257130_00257130__recomp},
    {"sub_258630", 0x258630, &recomp_gen::fn_sub_258630_00258630, &recomp_gen::fn_sub_258630_00258630__recomp},
    {"sub_25AAD0", 0x25AAD0, &recomp_gen::fn_sub_25AAD0_0025aad0, &recomp_gen::fn_sub_25AAD0_0025aad0__recomp},
    {"sub_2813F0", 0x2813F0, &recomp_gen::fn_sub_2813F0_002813f0, &recomp_gen::fn_sub_2813F0_002813f0__recomp},
    {"sub_281F20", 0x281F20, &recomp_gen::fn_sub_281F20_00281f20, &recomp_gen::fn_sub_281F20_00281f20__recomp},
    {"sub_282D40", 0x282D40, &recomp_gen::fn_sub_282D40_00282d40, &recomp_gen::fn_sub_282D40_00282d40__recomp},
    {"sub_2849A0", 0x2849A0, &recomp_gen::fn_sub_2849A0_002849a0, &recomp_gen::fn_sub_2849A0_002849a0__recomp},
    {"sub_2879F0", 0x2879F0, &recomp_gen::fn_sub_2879F0_002879f0, &recomp_gen::fn_sub_2879F0_002879f0__recomp},
    {"sub_287EA0", 0x287EA0, &recomp_gen::fn_sub_287EA0_00287ea0, &recomp_gen::fn_sub_287EA0_00287ea0__recomp},
    {"sub_288110", 0x288110, &recomp_gen::fn_sub_288110_00288110, &recomp_gen::fn_sub_288110_00288110__recomp},
    {"sub_28AA20", 0x28AA20, &recomp_gen::fn_sub_28AA20_0028aa20, &recomp_gen::fn_sub_28AA20_0028aa20__recomp},
    {"sub_28DF00", 0x28DF00, &recomp_gen::fn_sub_28DF00_0028df00, &recomp_gen::fn_sub_28DF00_0028df00__recomp},
    {"sub_338D60", 0x338D60, &recomp_gen::fn_sub_338D60_00338d60, &recomp_gen::fn_sub_338D60_00338d60__recomp},
    {"sub_342890", 0x342890, &recomp_gen::fn_sub_342890_00342890, &recomp_gen::fn_sub_342890_00342890__recomp},
    {"sub_34A650", 0x34A650, &recomp_gen::fn_sub_34A650_0034a650, &recomp_gen::fn_sub_34A650_0034a650__recomp},
    {"sub_34AE30", 0x34AE30, &recomp_gen::fn_sub_34AE30_0034ae30, &recomp_gen::fn_sub_34AE30_0034ae30__recomp},
    {"sub_358030", 0x358030, &recomp_gen::fn_sub_358030_00358030, &recomp_gen::fn_sub_358030_00358030__recomp},
    {"sub_3A2A30", 0x3A2A30, &recomp_gen::fn_sub_3A2A30_003a2a30, &recomp_gen::fn_sub_3A2A30_003a2a30__recomp},
    {"itfMesMngInitialize", 0x3A2D80, &recomp_gen::fn_itfMesMngInitialize_003a2d80, &recomp_gen::fn_itfMesMngInitialize_003a2d80__recomp},
    {"itfMesMngDestroyHandle", 0x3A3060, &recomp_gen::fn_itfMesMngDestroyHandle_003a3060, &recomp_gen::fn_itfMesMngDestroyHandle_003a3060__recomp},
    {"itfMesMngRequestMessage", 0x3A30C0, &recomp_gen::fn_itfMesMngRequestMessage_003a30c0, &recomp_gen::fn_itfMesMngRequestMessage_003a30c0__recomp},
    {"sub_3A3420", 0x3A3420, &recomp_gen::fn_sub_3A3420_003a3420, &recomp_gen::fn_sub_3A3420_003a3420__recomp},
    {"sub_3A37C0", 0x3A37C0, &recomp_gen::fn_sub_3A37C0_003a37c0, &recomp_gen::fn_sub_3A37C0_003a37c0__recomp},
    {"sub_3A4010", 0x3A4010, &recomp_gen::fn_sub_3A4010_003a4010, &recomp_gen::fn_sub_3A4010_003a4010__recomp},
    {"sub_3A4360", 0x3A4360, &recomp_gen::fn_sub_3A4360_003a4360, &recomp_gen::fn_sub_3A4360_003a4360__recomp},
    {"itfMesMngChangeWindowType", 0x3A4990, &recomp_gen::fn_itfMesMngChangeWindowType_003a4990, &recomp_gen::fn_itfMesMngChangeWindowType_003a4990__recomp},
    {"sub_3D06D0", 0x3D06D0, &recomp_gen::fn_sub_3D06D0_003d06d0, &recomp_gen::fn_sub_3D06D0_003d06d0__recomp},
    {"sub_3D1DF0", 0x3D1DF0, &recomp_gen::fn_sub_3D1DF0_003d1df0, &recomp_gen::fn_sub_3D1DF0_003d1df0__recomp},
    {"sub_3D2200", 0x3D2200, &recomp_gen::fn_sub_3D2200_003d2200, &recomp_gen::fn_sub_3D2200_003d2200__recomp},
    {"sub_3D32E0", 0x3D32E0, &recomp_gen::fn_sub_3D32E0_003d32e0, &recomp_gen::fn_sub_3D32E0_003d32e0__recomp},
    {"sub_3D3620", 0x3D3620, &recomp_gen::fn_sub_3D3620_003d3620, &recomp_gen::fn_sub_3D3620_003d3620__recomp},
    {"sub_3D38B0", 0x3D38B0, &recomp_gen::fn_sub_3D38B0_003d38b0, &recomp_gen::fn_sub_3D38B0_003d38b0__recomp},
    {"sub_3D8850", 0x3D8850, &recomp_gen::fn_sub_3D8850_003d8850, &recomp_gen::fn_sub_3D8850_003d8850__recomp},
    {"sub_3DB650", 0x3DB650, &recomp_gen::fn_sub_3DB650_003db650, &recomp_gen::fn_sub_3DB650_003db650__recomp},
    {"sub_3DD260", 0x3DD260, &recomp_gen::fn_sub_3DD260_003dd260, &recomp_gen::fn_sub_3DD260_003dd260__recomp},
    {"sub_3E9AF0", 0x3E9AF0, &recomp_gen::fn_sub_3E9AF0_003e9af0, &recomp_gen::fn_sub_3E9AF0_003e9af0__recomp},
    {"sub_3EA820", 0x3EA820, &recomp_gen::fn_sub_3EA820_003ea820, &recomp_gen::fn_sub_3EA820_003ea820__recomp},
    {"sub_3EE920", 0x3EE920, &recomp_gen::fn_sub_3EE920_003ee920, &recomp_gen::fn_sub_3EE920_003ee920__recomp},
    {"sub_3EEE80", 0x3EEE80, &recomp_gen::fn_sub_3EEE80_003eee80, &recomp_gen::fn_sub_3EEE80_003eee80__recomp},
    {"sub_3EF2B0", 0x3EF2B0, &recomp_gen::fn_sub_3EF2B0_003ef2b0, &recomp_gen::fn_sub_3EF2B0_003ef2b0__recomp},
    {"sub_3F1DC0", 0x3F1DC0, &recomp_gen::fn_sub_3F1DC0_003f1dc0, &recomp_gen::fn_sub_3F1DC0_003f1dc0__recomp},
    {"sub_3F45E0", 0x3F45E0, &recomp_gen::fn_sub_3F45E0_003f45e0, &recomp_gen::fn_sub_3F45E0_003f45e0__recomp},
    {"sub_3F55B0", 0x3F55B0, &recomp_gen::fn_sub_3F55B0_003f55b0, &recomp_gen::fn_sub_3F55B0_003f55b0__recomp},
    {"sub_3F8E10", 0x3F8E10, &recomp_gen::fn_sub_3F8E10_003f8e10, &recomp_gen::fn_sub_3F8E10_003f8e10__recomp},
    {"sub_3FBC00", 0x3FBC00, &recomp_gen::fn_sub_3FBC00_003fbc00, &recomp_gen::fn_sub_3FBC00_003fbc00__recomp},
    {"sub_3FF630", 0x3FF630, &recomp_gen::fn_sub_3FF630_003ff630, &recomp_gen::fn_sub_3FF630_003ff630__recomp},
    {"sub_3FFBB0", 0x3FFBB0, &recomp_gen::fn_sub_3FFBB0_003ffbb0, &recomp_gen::fn_sub_3FFBB0_003ffbb0__recomp},
    {"sub_40D640", 0x40D640, &recomp_gen::fn_sub_40D640_0040d640, &recomp_gen::fn_sub_40D640_0040d640__recomp},
    {"sub_40E360", 0x40E360, &recomp_gen::fn_sub_40E360_0040e360, &recomp_gen::fn_sub_40E360_0040e360__recomp},
    {"sub_4178C0", 0x4178C0, &recomp_gen::fn_sub_4178C0_004178c0, &recomp_gen::fn_sub_4178C0_004178c0__recomp},
    {"sub_418230", 0x418230, &recomp_gen::fn_sub_418230_00418230, &recomp_gen::fn_sub_418230_00418230__recomp},
    {"sub_418390", 0x418390, &recomp_gen::fn_sub_418390_00418390, &recomp_gen::fn_sub_418390_00418390__recomp},
    {"sub_418510", 0x418510, &recomp_gen::fn_sub_418510_00418510, &recomp_gen::fn_sub_418510_00418510__recomp},
    {"sub_418880", 0x418880, &recomp_gen::fn_sub_418880_00418880, &recomp_gen::fn_sub_418880_00418880__recomp},
    {"sub_418C70", 0x418C70, &recomp_gen::fn_sub_418C70_00418c70, &recomp_gen::fn_sub_418C70_00418c70__recomp},
    {"sub_419050", 0x419050, &recomp_gen::fn_sub_419050_00419050, &recomp_gen::fn_sub_419050_00419050__recomp},
    {"sub_4195F0", 0x4195F0, &recomp_gen::fn_sub_4195F0_004195f0, &recomp_gen::fn_sub_4195F0_004195f0__recomp},
    {"sub_419A30", 0x419A30, &recomp_gen::fn_sub_419A30_00419a30, &recomp_gen::fn_sub_419A30_00419a30__recomp},
    {"sub_419A70", 0x419A70, &recomp_gen::fn_sub_419A70_00419a70, &recomp_gen::fn_sub_419A70_00419a70__recomp},
    {"sub_41AE20", 0x41AE20, &recomp_gen::fn_sub_41AE20_0041ae20, &recomp_gen::fn_sub_41AE20_0041ae20__recomp},
    {"sub_41B810", 0x41B810, &recomp_gen::fn_sub_41B810_0041b810, &recomp_gen::fn_sub_41B810_0041b810__recomp},
    {"sub_41B950", 0x41B950, &recomp_gen::fn_sub_41B950_0041b950, &recomp_gen::fn_sub_41B950_0041b950__recomp},
    {"_sceMpegNextBit", 0x4FD658, &recomp_gen::fn__sceMpegNextBit_004fd658, &recomp_gen::fn__sceMpegNextBit_004fd658__recomp},
    {"_sceCreateThread", 0x502F60, &recomp_gen::fn__sceCreateThread_00502f60, &recomp_gen::fn__sceCreateThread_00502f60__recomp},
    {"_sceChangeThreadPriority", 0x502FF0, &recomp_gen::fn__sceChangeThreadPriority_00502ff0, &recomp_gen::fn__sceChangeThreadPriority_00502ff0__recomp},
    {"_sceGetThreadId", 0x503050, &recomp_gen::fn__sceGetThreadId_00503050, &recomp_gen::fn__sceGetThreadId_00503050__recomp},
    {"_sceReferThreadStatus", 0x503060, &recomp_gen::fn__sceReferThreadStatus_00503060, &recomp_gen::fn__sceReferThreadStatus_00503060__recomp},
    {"_sceCreateSema", 0x503160, &recomp_gen::fn__sceCreateSema_00503160, &recomp_gen::fn__sceCreateSema_00503160__recomp},
    {"_sceDeleteSema", 0x503170, &recomp_gen::fn__sceDeleteSema_00503170, &recomp_gen::fn__sceDeleteSema_00503170__recomp},
    {"_sceSignalSema", 0x503180, &recomp_gen::fn__sceSignalSema_00503180, &recomp_gen::fn__sceSignalSema_00503180__recomp},
    {"_sceiSignalSema", 0x503190, &recomp_gen::fn__sceiSignalSema_00503190, &recomp_gen::fn__sceiSignalSema_00503190__recomp},
    {"_sceWaitSema", 0x5031A0, &recomp_gen::fn__sceWaitSema_005031a0, &recomp_gen::fn__sceWaitSema_005031a0__recomp},
    {"_sceDeci2Call", 0x503590, &recomp_gen::fn__sceDeci2Call_00503590, &recomp_gen::fn__sceDeci2Call_00503590__recomp},
    {"scePrintf", 0x505E48, &recomp_gen::fn_scePrintf_00505e48, &recomp_gen::fn_scePrintf_00505e48__recomp},
    {"scePadGetDmaStr", 0x511830, &recomp_gen::fn_scePadGetDmaStr_00511830, &recomp_gen::fn_scePadGetDmaStr_00511830__recomp},
    {"sceSdRemote", 0x5129C0, &recomp_gen::fn_sceSdRemote_005129c0, &recomp_gen::fn_sceSdRemote_005129c0__recomp},
    {"sceMc2GetInfoAsync", 0x5136F8, &recomp_gen::fn_sceMc2GetInfoAsync_005136f8, &recomp_gen::fn_sceMc2GetInfoAsync_005136f8__recomp},
    {"sceMc2Sync2", 0x514858, &recomp_gen::fn_sceMc2Sync2_00514858, &recomp_gen::fn_sceMc2Sync2_00514858__recomp},
    {"sprintf", 0x523AC8, &recomp_gen::fn_sprintf_00523ac8, &recomp_gen::fn_sprintf_00523ac8__recomp},
    {"vsprintf", 0x5288C8, &recomp_gen::fn_vsprintf_005288c8, &recomp_gen::fn_vsprintf_005288c8__recomp},
    {"sub_546270", 0x546270, &recomp_gen::fn_sub_546270_00546270, &recomp_gen::fn_sub_546270_00546270__recomp},
    {"sub_546368", 0x546368, &recomp_gen::fn_sub_546368_00546368, &recomp_gen::fn_sub_546368_00546368__recomp},
    {"sub_5463A8", 0x5463A8, &recomp_gen::fn_sub_5463A8_005463a8, &recomp_gen::fn_sub_5463A8_005463a8__recomp},
    {"sub_546498", 0x546498, &recomp_gen::fn_sub_546498_00546498, &recomp_gen::fn_sub_546498_00546498__recomp},
    {"sub_546718", 0x546718, &recomp_gen::fn_sub_546718_00546718, &recomp_gen::fn_sub_546718_00546718__recomp},
    {"sub_546FA0", 0x546FA0, &recomp_gen::fn_sub_546FA0_00546fa0, &recomp_gen::fn_sub_546FA0_00546fa0__recomp},
    {"sceInsockSetsockopt_2", 0x54A928, &recomp_gen::fn_sceInsockSetsockopt_2_0054a928, &recomp_gen::fn_sceInsockSetsockopt_2_0054a928__recomp},
    {"DTX_CallUrpc", 0x559C10, &recomp_gen::fn_DTX_CallUrpc_00559c10, &recomp_gen::fn_DTX_CallUrpc_00559c10__recomp},
    {"sub_55D668", 0x55D668, &recomp_gen::fn_sub_55D668_0055d668, &recomp_gen::fn_sub_55D668_0055d668__recomp},
    {"sub_5753E8", 0x5753E8, &recomp_gen::fn_sub_5753E8_005753e8, &recomp_gen::fn_sub_5753E8_005753e8__recomp},
    {"sub_575410", 0x575410, &recomp_gen::fn_sub_575410_00575410, &recomp_gen::fn_sub_575410_00575410__recomp},
    {"sub_575880", 0x575880, &recomp_gen::fn_sub_575880_00575880, &recomp_gen::fn_sub_575880_00575880__recomp},
    {"sub_589D10", 0x589D10, &recomp_gen::fn_sub_589D10_00589d10, &recomp_gen::fn_sub_589D10_00589d10__recomp},
    {"sub_58C100", 0x58C100, &recomp_gen::fn_sub_58C100_0058c100, &recomp_gen::fn_sub_58C100_0058c100__recomp},
    {"sub_58C118", 0x58C118, &recomp_gen::fn_sub_58C118_0058c118, &recomp_gen::fn_sub_58C118_0058c118__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena; the fixed records below sit inside it.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;
constexpr u32 kTask = kWorld;               // a KwlnTask (+0x3C work)
constexpr u32 kWork = kWorld + 0x400u;      // its work record (the H_DrawMaestro work is 308 bytes)
constexpr u32 kRec = kWorld + 0x1000u;      // a plain record ($a0)
constexpr u32 kFmt = kWorld + 0x3000u;      // a format string
constexpr u32 kStr = kWorld + 0x3100u;      // a string argument
constexpr u32 kBuf = kWorld + 0x3200u;      // an output buffer
constexpr u32 kSoundSlots = 0x7E5770u;      // 40-byte sound slots, +0 the state halfword
constexpr u32 kSel5753 = 0x99B2A8u;         // the word sub_5753E8 stores $a0 to

u32 r32(Machine& m, u32 va) {
    u32 v = 0;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void wstr(Machine& m, u32 va, const char* s) { std::memcpy(m.at(va), s, std::strlen(s) + 1); }
u64 v0_of(const hgp::Run& r) { return r.end.gpr[2].u64[0]; }

const Case& by_addr(u32 addr) {
    for (const Case& c : kCases)
        if (c.addr == addr) return c;
    FAIL("no case " << std::hex << addr);
    return kCases[0];
}

// $f12 for the float-argument bodies (sub_111D50): the thunks set it after the harness randomises the registers.
Fn g_fn[2];
bool g_set_f12 = false;
u32 g_f12 = 0;
void thunk0(EEContext& ctx) {
    if (g_set_f12) ctx.fpr[12] = g_f12;
    g_fn[0](ctx);
}
void thunk1(EEContext& ctx) {
    if (g_set_f12) ctx.fpr[12] = g_f12;
    g_fn[1](ctx);
}
hgp::Run fpair(Machine& m, const Case& c, const Args& args, u32 seed, float f12) {
    g_fn[0] = c.hand;
    g_fn[1] = c.recomp;
    std::memcpy(&g_f12, &f12, 4);
    g_set_f12 = true;
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, c.name);
    g_set_f12 = false;
    return r;
}
hgp::Run spair(Machine& m, const Case& c, const Args& args, u32 seed) {
    return hgp::pair(m, c.hand, c.recomp, args, seed, c.name);
}

void run_random(Machine& m, u32 seeds, const char* label) {
    const char* only = std::getenv("P3FES_HG_ONLY");  // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s %s seed %u\n", label, c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += spair(m, c, args, seed).stopped ? 1 : 0;
        }
        const std::string summary = std::string(label) + " " + c.name + ": " + std::to_string(seeds) + " pairs, " +
                                    std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

}  // namespace

TEST_CASE("game(sweep5a): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    run_random(*m, env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds, "random");
}

// The same over the RAM of the replay snapshots: the real globals (the H_Cdvd request list, the heap function pointers
// at 0x960178.., the BGM channel table, the sound slots, the message-manager slots, the battle / facility work
// pointers), with random worlds for the pointer arguments.
TEST_CASE("game(sweep5a): every body equals its recompiled body on the replay snapshots") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    for (const char* dir : {"dorm_replay_4900", "b_5800", "climb_ref_17000", "fusion_ref_6300", "shop_ref_4100"}) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.size() != EEMemory::kMainRamSize) {
            MESSAGE("SKIP: snapshot " << dir << " not found");
            continue;
        }
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        run_random(*m, 3u, dir);
    }
}

// Documented rules on the host, each through a pair (both bodies compared as above): the H_DrawMaestro work accessors,
// the sound-slot state test, the H_malloc free of NULL, the task-state callback, sub_5753E8 / sub_589D10 and sprintf
// through vfprintf.
TEST_CASE("game(sweep5a): accessors, the sound-slot state and sprintf") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    std::mt19937 rng{0x5a};
    u32 seed = 1;
    auto fresh = [&] {
        hgp::random_world(*m, kWorld, kWorldSize, rng);
        w32(*m, kTask + 0x3C, kWork);
    };

    // H_DrawMaestro work: sub_111EC0 = state >= 3; sub_111EE0 sets state 4; sub_111F20 sets +288; sub_111D50 +296.
    for (u32 state : {0u, 2u, 3u, 4u, 0x80000000u}) {
        fresh();
        w32(*m, kWork, state);
        const u64 v0 = v0_of(spair(*m, by_addr(0x111EC0u), Args{sx(kTask), 0, 0, 0}, seed++));
        CHECK(v0 == (static_cast<s32>(state) >= 3 ? 1u : 0u));
    }
    fresh();
    spair(*m, by_addr(0x111EE0u), Args{sx(kTask), 0, 0, 0}, seed++);
    CHECK(r32(*m, kWork) == 4u);
    fresh();
    spair(*m, by_addr(0x111F20u), Args{sx(kTask), 0x1234567u, 0, 0}, seed++);
    CHECK(r32(*m, kWork + 288) == 0x1234567u);
    for (float f : {1.0f, 0.5f, -2.25f}) {
        fresh();
        fpair(*m, by_addr(0x111D50u), Args{sx(kTask), 0, 0, 0}, seed++, f);
        u32 bits = 0;
        std::memcpy(&bits, &f, 4);
        CHECK(r32(*m, kWork + 296) == bits);
    }

    // sub_109DF0: slot a0's state halfword == 1 (a0 taken as s16).
    for (u16 state : {u16{0}, u16{1}, u16{2}, u16{3}}) {
        for (u32 slot : {0u, 5u}) {
            fresh();
            w16(*m, kSoundSlots + 40u * slot, state);
            CHECK(v0_of(spair(*m, by_addr(0x109DF0u), Args{slot, 0, 0, 0}, seed++)) == (state == 1 ? 1u : 0u));
        }
    }

    // sub_104280 (H_malloc free): NULL returns without a call.
    fresh();
    CHECK_FALSE(spair(*m, by_addr(0x104280u), Args{0, 0, 0, 0}, seed++).stopped);

    // sub_10A720: a work state other than 2 returns 0 and keeps the task.
    for (u32 state : {0u, 1u, 3u}) {
        fresh();
        w32(*m, kWork, state);
        CHECK(v0_of(spair(*m, by_addr(0x10A720u), Args{sx(kTask), 0, 0, 0}, seed++)) == 0u);
    }

    // sub_5753E8: stores a0; returns -1 for NULL, 0 when *a0 == 2, else -1.
    for (u32 first : {2u, 0u, 3u}) {
        fresh();
        w32(*m, kRec, first);
        CHECK(v0_of(spair(*m, by_addr(0x5753E8u), Args{sx(kRec), 0, 0, 0}, seed++)) == (first == 2 ? 0u : ~0ull));
        CHECK(r32(*m, kSel5753) == kRec);
    }
    fresh();
    CHECK(v0_of(spair(*m, by_addr(0x5753E8u), Args{0, 0, 0, 0}, seed++)) == ~0ull);
    CHECK(r32(*m, kSel5753) == 0u);

    // sub_589D10: the word at a0 + 4892 + 116 * a1.
    for (u32 i : {0u, 1u, 7u}) {
        fresh();
        w32(*m, kRec + 4892u + 116u * i, 0xABC00000u + i);
        CHECK(v0_of(spair(*m, by_addr(0x589D10u), Args{sx(kRec), i, 0, 0}, seed++)) == sx(0xABC00000u + i));
    }

    // sprintf: vfprintf into the buffer, the length in $v0.
    fresh();
    wstr(*m, kFmt, "%d-%s-%x");
    wstr(*m, kStr, "abc");
    const hgp::Run r = spair(*m, by_addr(0x523AC8u), Args{sx(kBuf), sx(kFmt), 77, sx(kStr)}, seed++);
    if (!r.stopped) {
        CHECK(std::string(reinterpret_cast<const char*>(m->at(kBuf))).rfind("77-abc-", 0) == 0);
    }
}

#else

TEST_CASE("game(sweep5a): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
