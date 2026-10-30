// Pair tests of slice sweep5b (game/src/field/sweep5b.cpp): every body against its recompiled body on
//   * random worlds: the p3fes_handgen sweep;
//   * the packet's replay snapshots (b_5800, dorm_replay_4900, climb_ref_17000, fusion_ref_6300, shop_ref_4100): the
//     snapshot's own globals (scene and camera records, gEncountTbl, the shop tables, the library states) with
//     arguments of each function's kind (field object ids, event / floor / social-link / shop ids, gFldUnitsPc,
//     blocks with pointers to further blocks, file names);
//   * documented rules on the host: the CRI channel table (116-byte rows from +4880), sub_3580F0's scrambler, the
//     one-load accessors, sub_589F38's carry, the field object lookups (+300 / +284 ...) and the camera word with
//     the lookup stood in, K_Encount_PickEncounter's floors without encounters.
// Compared by tests/game/handgen_pairs.h (hgp::pair) and stand_ins.h (run_pair_si): the whole register file and cycle
// count at every check point and at the return / stop, all 32 MiB of RAM (the dead stack included), the scratchpad,
// the BIOS window and the bus log.
#include "handgen_pairs.h"
#include "sweep2_util.h"

#include "p3fes/game/sweep5b.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <memory>
#include <random>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::s2t;

namespace p3fes::recomp_gen {
void fn_start_00100008(EEContext&);  // generated body
void fn_start_00100008__recomp(EEContext&);  // recompiled
void fn_H_Memcard_UpdateChkAreaSeq_00191260(EEContext&);  // generated body
void fn_H_Memcard_UpdateChkAreaSeq_00191260__recomp(EEContext&);  // recompiled
void fn_kwlnVsyncFieldGate_0019d320(EEContext&);  // generated body
void fn_kwlnVsyncFieldGate_0019d320__recomp(EEContext&);  // recompiled
void fn_sub_1A0430_001a0430(EEContext&);  // generated body
void fn_sub_1A0430_001a0430__recomp(EEContext&);  // recompiled
void fn_sub_1A0700_001a0700(EEContext&);  // generated body
void fn_sub_1A0700_001a0700__recomp(EEContext&);  // recompiled
void fn_sub_1A07F0_001a07f0(EEContext&);  // generated body
void fn_sub_1A07F0_001a07f0__recomp(EEContext&);  // recompiled
void fn_sub_1A08E0_001a08e0(EEContext&);  // generated body
void fn_sub_1A08E0_001a08e0__recomp(EEContext&);  // recompiled
void fn_sub_1A1150_001a1150(EEContext&);  // generated body
void fn_sub_1A1150_001a1150__recomp(EEContext&);  // recompiled
void fn_sub_1A1190_001a1190(EEContext&);  // generated body
void fn_sub_1A1190_001a1190__recomp(EEContext&);  // recompiled
void fn_sub_1A1210_001a1210(EEContext&);  // generated body
void fn_sub_1A1210_001a1210__recomp(EEContext&);  // recompiled
void fn_sub_1A14C0_001a14c0(EEContext&);  // generated body
void fn_sub_1A14C0_001a14c0__recomp(EEContext&);  // recompiled
void fn_sub_1A4600_001a4600(EEContext&);  // generated body
void fn_sub_1A4600_001a4600__recomp(EEContext&);  // recompiled
void fn_sub_1A4860_001a4860(EEContext&);  // generated body
void fn_sub_1A4860_001a4860__recomp(EEContext&);  // recompiled
void fn_sub_1A5EA0_001a5ea0(EEContext&);  // generated body
void fn_sub_1A5EA0_001a5ea0__recomp(EEContext&);  // recompiled
void fn_sub_1A6400_001a6400(EEContext&);  // generated body
void fn_sub_1A6400_001a6400__recomp(EEContext&);  // recompiled
void fn_sub_1A6860_001a6860(EEContext&);  // generated body
void fn_sub_1A6860_001a6860__recomp(EEContext&);  // recompiled
void fn_sub_1A6C00_001a6c00(EEContext&);  // generated body
void fn_sub_1A6C00_001a6c00__recomp(EEContext&);  // recompiled
void fn_sub_1A7170_001a7170(EEContext&);  // generated body
void fn_sub_1A7170_001a7170__recomp(EEContext&);  // recompiled
void fn_sub_1A7570_001a7570(EEContext&);  // generated body
void fn_sub_1A7570_001a7570__recomp(EEContext&);  // recompiled
void fn_sub_1A7710_001a7710(EEContext&);  // generated body
void fn_sub_1A7710_001a7710__recomp(EEContext&);  // recompiled
void fn_sub_1AD9E0_001ad9e0(EEContext&);  // generated body
void fn_sub_1AD9E0_001ad9e0__recomp(EEContext&);  // recompiled
void fn_sub_1CD9A0_001cd9a0(EEContext&);  // generated body
void fn_sub_1CD9A0_001cd9a0__recomp(EEContext&);  // recompiled
void fn_K_Encount_PickEncounter_001d78c0(EEContext&);  // generated body
void fn_K_Encount_PickEncounter_001d78c0__recomp(EEContext&);  // recompiled
void fn_sub_1DA020_001da020(EEContext&);  // generated body
void fn_sub_1DA020_001da020__recomp(EEContext&);  // recompiled
void fn_sub_1F9E90_001f9e90(EEContext&);  // generated body
void fn_sub_1F9E90_001f9e90__recomp(EEContext&);  // recompiled
void fn_sub_25BE60_0025be60(EEContext&);  // generated body
void fn_sub_25BE60_0025be60__recomp(EEContext&);  // recompiled
void fn_sub_351C20_00351c20(EEContext&);  // generated body
void fn_sub_351C20_00351c20__recomp(EEContext&);  // recompiled
void fn_sub_3580F0_003580f0(EEContext&);  // generated body
void fn_sub_3580F0_003580f0__recomp(EEContext&);  // recompiled
void fn_sub_3F33D0_003f33d0(EEContext&);  // generated body
void fn_sub_3F33D0_003f33d0__recomp(EEContext&);  // recompiled
void fn_sub_3F39A0_003f39a0(EEContext&);  // generated body
void fn_sub_3F39A0_003f39a0__recomp(EEContext&);  // recompiled
void fn_sub_3FFE60_003ffe60(EEContext&);  // generated body
void fn_sub_3FFE60_003ffe60__recomp(EEContext&);  // recompiled
void fn_sub_418C10_00418c10(EEContext&);  // generated body
void fn_sub_418C10_00418c10__recomp(EEContext&);  // recompiled
void fn_sub_419B80_00419b80(EEContext&);  // generated body
void fn_sub_419B80_00419b80__recomp(EEContext&);  // recompiled
void fn_sub_41A310_0041a310(EEContext&);  // generated body
void fn_sub_41A310_0041a310__recomp(EEContext&);  // recompiled
void fn__sceMpegPictureData0_004fc168(EEContext&);  // generated body
void fn__sceMpegPictureData0_004fc168__recomp(EEContext&);  // recompiled
void fn__sceMpegPeepBit_004fd740(EEContext&);  // generated body
void fn__sceMpegPeepBit_004fd740__recomp(EEContext&);  // recompiled
void fn_j__sceMpegFlushBuf_0_004ff9d0(EEContext&);  // generated body
void fn_j__sceMpegFlushBuf_0_004ff9d0__recomp(EEContext&);  // recompiled
void fn__sceMpegNextHeader_004ff9d8(EEContext&);  // generated body
void fn__sceMpegNextHeader_004ff9d8__recomp(EEContext&);  // recompiled
void fn_flushByteBoundary_004ffb38(EEContext&);  // generated body
void fn_flushByteBoundary_004ffb38__recomp(EEContext&);  // recompiled
void fn__clearOnce_004ffda8(EEContext&);  // generated body
void fn__clearOnce_004ffda8__recomp(EEContext&);  // recompiled
void fn_sceMpegCreate_004ffe78(EEContext&);  // generated body
void fn_sceMpegCreate_004ffe78__recomp(EEContext&);  // recompiled
void fn_sceMpegInit_00500a20(EEContext&);  // generated body
void fn_sceMpegInit_00500a20__recomp(EEContext&);  // recompiled
void fn_sceMpegReset_00500bb8(EEContext&);  // generated body
void fn_sceMpegReset_00500bb8__recomp(EEContext&);  // recompiled
void fn__sceMpegAlalcFree_00501090(EEContext&);  // generated body
void fn__sceMpegAlalcFree_00501090__recomp(EEContext&);  // recompiled
void fn__sceMpegAlalcAlloc_005010a0(EEContext&);  // generated body
void fn__sceMpegAlalcAlloc_005010a0__recomp(EEContext&);  // recompiled
void fn__sceMpegOutputFrame_00501ba8(EEContext&);  // generated body
void fn__sceMpegOutputFrame_00501ba8__recomp(EEContext&);  // recompiled
void fn__sceMpegCscStoreRefImage_00501df8(EEContext&);  // generated body
void fn__sceMpegCscStoreRefImage_00501df8__recomp(EEContext&);  // recompiled
void fn__sceAddIntcHandler_00502e40(EEContext&);  // generated body
void fn__sceAddIntcHandler_00502e40__recomp(EEContext&);  // recompiled
void fn__sceRemoveDmacHandler_00502e90(EEContext&);  // generated body
void fn__sceRemoveDmacHandler_00502e90__recomp(EEContext&);  // recompiled
void fn__sceSleepThread_00503080(EEContext&);  // generated body
void fn__sceSleepThread_00503080__recomp(EEContext&);  // recompiled
void fn_EnableIntc_00503ca8(EEContext&);  // generated body
void fn_EnableIntc_00503ca8__recomp(EEContext&);  // recompiled
void fn_DisableDmac_00503d10(EEContext&);  // generated body
void fn_DisableDmac_00503d10__recomp(EEContext&);  // recompiled
void fn_iWakeupThread_00504028(EEContext&);  // generated body
void fn_iWakeupThread_00504028__recomp(EEContext&);  // recompiled
void fn_sub_5064F8_005064f8(EEContext&);  // generated body
void fn_sub_5064F8_005064f8__recomp(EEContext&);  // recompiled
void fn_sub_50E000_0050e000(EEContext&);  // generated body
void fn_sub_50E000_0050e000__recomp(EEContext&);  // recompiled
void fn__send_to_iop_00511478(EEContext&);  // generated body
void fn__send_to_iop_00511478__recomp(EEContext&);  // recompiled
void fn_sceSdRemoteInit_00512868(EEContext&);  // generated body
void fn_sceSdRemoteInit_00512868__recomp(EEContext&);  // recompiled
void fn_sceMc2Init_005130e8(EEContext&);  // generated body
void fn_sceMc2Init_005130e8__recomp(EEContext&);  // recompiled
void fn_sceMc2SearchFileAsync_005137b8(EEContext&);  // generated body
void fn_sceMc2SearchFileAsync_005137b8__recomp(EEContext&);  // recompiled
void fn_sceMc2ReadFileAsync_00513968(EEContext&);  // generated body
void fn_sceMc2ReadFileAsync_00513968__recomp(EEContext&);  // recompiled
void fn_sceMc2CheckAsync_00514900(EEContext&);  // generated body
void fn_sceMc2CheckAsync_00514900__recomp(EEContext&);  // recompiled
void fn__sceMcCoreGetCardSpec_0051afd8(EEContext&);  // generated body
void fn__sceMcCoreGetCardSpec_0051afd8__recomp(EEContext&);  // recompiled
void fn__sceMcCoreCheckNewCard_0051b1b0(EEContext&);  // generated body
void fn__sceMcCoreCheckNewCard_0051b1b0__recomp(EEContext&);  // recompiled
void fn__sceMcCoreClearNewCardFlag_0051b2c0(EEContext&);  // generated body
void fn__sceMcCoreClearNewCardFlag_0051b2c0__recomp(EEContext&);  // recompiled
void fn__sceMcCoreAuthentication_0051b3b0(EEContext&);  // generated body
void fn__sceMcCoreAuthentication_0051b3b0__recomp(EEContext&);  // recompiled
void fn__sceMcCoreWriteBack_0051b4a0(EEContext&);  // generated body
void fn__sceMcCoreWriteBack_0051b4a0__recomp(EEContext&);  // recompiled
void fn__sceMcCoreReadPage2_0051b708(EEContext&);  // generated body
void fn__sceMcCoreReadPage2_0051b708__recomp(EEContext&);  // recompiled
void fn__sceMcCoreGetConnection_0051c0c0(EEContext&);  // generated body
void fn__sceMcCoreGetConnection_0051c0c0__recomp(EEContext&);  // recompiled
void fn__sceMcCoreCreateSocket_0051c130(EEContext&);  // generated body
void fn__sceMcCoreCreateSocket_0051c130__recomp(EEContext&);  // recompiled
void fn_sceDbcInit_0051c3b8(EEContext&);  // generated body
void fn_sceDbcInit_0051c3b8__recomp(EEContext&);  // recompiled
void fn_sceSpu2MemAllocate_0051d6f8(EEContext&);  // generated body
void fn_sceSpu2MemAllocate_0051d6f8__recomp(EEContext&);  // recompiled
void fn_sceSkInit_0051da48(EEContext&);  // generated body
void fn_sceSkInit_0051da48__recomp(EEContext&);  // recompiled
void fn_sceSkSsInit_0051da50(EEContext&);  // generated body
void fn_sceSkSsInit_0051da50__recomp(EEContext&);  // recompiled
void fn_sceSkSsSOUND_Control_0051db00(EEContext&);  // generated body
void fn_sceSkSsSOUND_Control_0051db00__recomp(EEContext&);  // recompiled
void fn_sceSkSsSESQ_Control_0051df58(EEContext&);  // generated body
void fn_sceSkSsSESQ_Control_0051df58__recomp(EEContext&);  // recompiled
void fn_sceSkSsSESQ_Status_0051e028(EEContext&);  // generated body
void fn_sceSkSsSESQ_Status_0051e028__recomp(EEContext&);  // recompiled
void fn_malloc_00520728(EEContext&);  // generated body
void fn_malloc_00520728__recomp(EEContext&);  // recompiled
void fn_cfree_00520748(EEContext&);  // generated body
void fn_cfree_00520748__recomp(EEContext&);  // recompiled
void fn_pow_0052e9d0(EEContext&);  // generated body
void fn_pow_0052e9d0__recomp(EEContext&);  // recompiled
void fn_sub_5379B0_005379b0(EEContext&);  // generated body
void fn_sub_5379B0_005379b0__recomp(EEContext&);  // recompiled
void fn_sub_537F30_00537f30(EEContext&);  // generated body
void fn_sub_537F30_00537f30__recomp(EEContext&);  // recompiled
void fn_sub_537F40_00537f40(EEContext&);  // generated body
void fn_sub_537F40_00537f40__recomp(EEContext&);  // recompiled
void fn_width__CQ24_STL8ios_base_00537fe8(EEContext&);  // generated body
void fn_width__CQ24_STL8ios_base_00537fe8__recomp(EEContext&);  // recompiled
void fn_sub_538038_00538038(EEContext&);  // generated body
void fn_sub_538038_00538038__recomp(EEContext&);  // recompiled
void fn_sub_5383E8_005383e8(EEContext&);  // generated body
void fn_sub_5383E8_005383e8__recomp(EEContext&);  // recompiled
void fn_sub_5383F0_005383f0(EEContext&);  // generated body
void fn_sub_5383F0_005383f0__recomp(EEContext&);  // recompiled
void fn_sub_5389B0_005389b0(EEContext&);  // generated body
void fn_sub_5389B0_005389b0__recomp(EEContext&);  // recompiled
void fn_sub_53DD10_0053dd10(EEContext&);  // generated body
void fn_sub_53DD10_0053dd10__recomp(EEContext&);  // recompiled
void fn_sub_53EA90_0053ea90(EEContext&);  // generated body
void fn_sub_53EA90_0053ea90__recomp(EEContext&);  // recompiled
void fn_sub_53F8B8_0053f8b8(EEContext&);  // generated body
void fn_sub_53F8B8_0053f8b8__recomp(EEContext&);  // recompiled
void fn_sub_53F940_0053f940(EEContext&);  // generated body
void fn_sub_53F940_0053f940__recomp(EEContext&);  // recompiled
void fn_ADXM_ExecMain_00540ec0(EEContext&);  // generated body
void fn_ADXM_ExecMain_00540ec0__recomp(EEContext&);  // recompiled
void fn_sub_541008_00541008(EEContext&);  // generated body
void fn_sub_541008_00541008__recomp(EEContext&);  // recompiled
void fn_cosl_1_00541a78(EEContext&);  // generated body
void fn_cosl_1_00541a78__recomp(EEContext&);  // recompiled
void fn_coshl_1_00541a90(EEContext&);  // generated body
void fn_coshl_1_00541a90__recomp(EEContext&);  // recompiled
void fn_hypotf_1_00541ac0(EEContext&);  // generated body
void fn_hypotf_1_00541ac0__recomp(EEContext&);  // recompiled
void fn_sub_545FC8_00545fc8(EEContext&);  // generated body
void fn_sub_545FC8_00545fc8__recomp(EEContext&);  // recompiled
void fn_sub_546058_00546058(EEContext&);  // generated body
void fn_sub_546058_00546058__recomp(EEContext&);  // recompiled
void fn_sub_5460E0_005460e0(EEContext&);  // generated body
void fn_sub_5460E0_005460e0__recomp(EEContext&);  // recompiled
void fn_sub_5465A0_005465a0(EEContext&);  // generated body
void fn_sub_5465A0_005465a0__recomp(EEContext&);  // recompiled
void fn_sub_5466B8_005466b8(EEContext&);  // generated body
void fn_sub_5466B8_005466b8__recomp(EEContext&);  // recompiled
void fn_sceInsockBind_2_00548b38(EEContext&);  // generated body
void fn_sceInsockBind_2_00548b38__recomp(EEContext&);  // recompiled
void fn_sceInsockListen_2_00549160(EEContext&);  // generated body
void fn_sceInsockListen_2_00549160__recomp(EEContext&);  // recompiled
void fn_expl_4_0054d148(EEContext&);  // generated body
void fn_expl_4_0054d148__recomp(EEContext&);  // recompiled
void fn_sub_552658_00552658(EEContext&);  // generated body
void fn_sub_552658_00552658__recomp(EEContext&);  // recompiled
void fn_sub_552680_00552680(EEContext&);  // generated body
void fn_sub_552680_00552680__recomp(EEContext&);  // recompiled
void fn_dvCiGetStat_0055a720(EEContext&);  // generated body
void fn_dvCiGetStat_0055a720__recomp(EEContext&);  // recompiled
void fn_dvci_conv_fname_0055a9b0(EEContext&);  // generated body
void fn_dvci_conv_fname_0055a9b0__recomp(EEContext&);  // recompiled
void fn_sub_55D2A0_0055d2a0(EEContext&);  // generated body
void fn_sub_55D2A0_0055d2a0__recomp(EEContext&);  // recompiled
void fn_sub_55D3A8_0055d3a8(EEContext&);  // generated body
void fn_sub_55D3A8_0055d3a8__recomp(EEContext&);  // recompiled
void fn_sub_55D3F8_0055d3f8(EEContext&);  // generated body
void fn_sub_55D3F8_0055d3f8__recomp(EEContext&);  // recompiled
void fn_sub_55D790_0055d790(EEContext&);  // generated body
void fn_sub_55D790_0055d790__recomp(EEContext&);  // recompiled
void fn_sub_55D7C0_0055d7c0(EEContext&);  // generated body
void fn_sub_55D7C0_0055d7c0__recomp(EEContext&);  // recompiled
void fn_sub_560DB8_00560db8(EEContext&);  // generated body
void fn_sub_560DB8_00560db8__recomp(EEContext&);  // recompiled
void fn_sub_564FE8_00564fe8(EEContext&);  // generated body
void fn_sub_564FE8_00564fe8__recomp(EEContext&);  // recompiled
void fn_sub_57AC68_0057ac68(EEContext&);  // generated body
void fn_sub_57AC68_0057ac68__recomp(EEContext&);  // recompiled
void fn_sub_57AE90_0057ae90(EEContext&);  // generated body
void fn_sub_57AE90_0057ae90__recomp(EEContext&);  // recompiled
void fn_sub_57C730_0057c730(EEContext&);  // generated body
void fn_sub_57C730_0057c730__recomp(EEContext&);  // recompiled
void fn_sub_57DB58_0057db58(EEContext&);  // generated body
void fn_sub_57DB58_0057db58__recomp(EEContext&);  // recompiled
void fn_my_malloc_0_00581070(EEContext&);  // generated body
void fn_my_malloc_0_00581070__recomp(EEContext&);  // recompiled
void fn_sub_588F48_00588f48(EEContext&);  // generated body
void fn_sub_588F48_00588f48__recomp(EEContext&);  // recompiled
void fn_sub_5895F0_005895f0(EEContext&);  // generated body
void fn_sub_5895F0_005895f0__recomp(EEContext&);  // recompiled
void fn_sub_589CB0_00589cb0(EEContext&);  // generated body
void fn_sub_589CB0_00589cb0__recomp(EEContext&);  // recompiled
void fn_sub_589CD0_00589cd0(EEContext&);  // generated body
void fn_sub_589CD0_00589cd0__recomp(EEContext&);  // recompiled
void fn_sub_589D80_00589d80(EEContext&);  // generated body
void fn_sub_589D80_00589d80__recomp(EEContext&);  // recompiled
void fn_sub_589F38_00589f38(EEContext&);  // generated body
void fn_sub_589F38_00589f38__recomp(EEContext&);  // recompiled
void fn_sub_5944A8_005944a8(EEContext&);  // generated body
void fn_sub_5944A8_005944a8__recomp(EEContext&);  // recompiled
void fn_sub_5946A8_005946a8(EEContext&);  // generated body
void fn_sub_5946A8_005946a8__recomp(EEContext&);  // recompiled
void fn_sub_5947A8_005947a8(EEContext&);  // generated body
void fn_sub_5947A8_005947a8__recomp(EEContext&);  // recompiled
void fn_sub_595BC0_00595bc0(EEContext&);  // generated body
void fn_sub_595BC0_00595bc0__recomp(EEContext&);  // recompiled
void fn_sub_597368_00597368(EEContext&);  // generated body
void fn_sub_597368_00597368__recomp(EEContext&);  // recompiled
void fn_sceInsockGetErrnoMode_1_00597438(EEContext&);  // generated body
void fn_sceInsockGetErrnoMode_1_00597438__recomp(EEContext&);  // recompiled
void fn_sub_5990C0_005990c0(EEContext&);  // generated body
void fn_sub_5990C0_005990c0__recomp(EEContext&);  // recompiled
void fn_sub_5A1A30_005a1a30(EEContext&);  // generated body
void fn_sub_5A1A30_005a1a30__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"start", 0x100008, &recomp_gen::fn_start_00100008, &recomp_gen::fn_start_00100008__recomp},
    {"H_Memcard_UpdateChkAreaSeq", 0x191260, &recomp_gen::fn_H_Memcard_UpdateChkAreaSeq_00191260, &recomp_gen::fn_H_Memcard_UpdateChkAreaSeq_00191260__recomp},
    {"kwlnVsyncFieldGate", 0x19D320, &recomp_gen::fn_kwlnVsyncFieldGate_0019d320, &recomp_gen::fn_kwlnVsyncFieldGate_0019d320__recomp},
    {"sub_1A0430", 0x1A0430, &recomp_gen::fn_sub_1A0430_001a0430, &recomp_gen::fn_sub_1A0430_001a0430__recomp},
    {"sub_1A0700", 0x1A0700, &recomp_gen::fn_sub_1A0700_001a0700, &recomp_gen::fn_sub_1A0700_001a0700__recomp},
    {"sub_1A07F0", 0x1A07F0, &recomp_gen::fn_sub_1A07F0_001a07f0, &recomp_gen::fn_sub_1A07F0_001a07f0__recomp},
    {"sub_1A08E0", 0x1A08E0, &recomp_gen::fn_sub_1A08E0_001a08e0, &recomp_gen::fn_sub_1A08E0_001a08e0__recomp},
    {"sub_1A1150", 0x1A1150, &recomp_gen::fn_sub_1A1150_001a1150, &recomp_gen::fn_sub_1A1150_001a1150__recomp},
    {"sub_1A1190", 0x1A1190, &recomp_gen::fn_sub_1A1190_001a1190, &recomp_gen::fn_sub_1A1190_001a1190__recomp},
    {"sub_1A1210", 0x1A1210, &recomp_gen::fn_sub_1A1210_001a1210, &recomp_gen::fn_sub_1A1210_001a1210__recomp},
    {"sub_1A14C0", 0x1A14C0, &recomp_gen::fn_sub_1A14C0_001a14c0, &recomp_gen::fn_sub_1A14C0_001a14c0__recomp},
    {"sub_1A4600", 0x1A4600, &recomp_gen::fn_sub_1A4600_001a4600, &recomp_gen::fn_sub_1A4600_001a4600__recomp},
    {"sub_1A4860", 0x1A4860, &recomp_gen::fn_sub_1A4860_001a4860, &recomp_gen::fn_sub_1A4860_001a4860__recomp},
    {"sub_1A5EA0", 0x1A5EA0, &recomp_gen::fn_sub_1A5EA0_001a5ea0, &recomp_gen::fn_sub_1A5EA0_001a5ea0__recomp},
    {"sub_1A6400", 0x1A6400, &recomp_gen::fn_sub_1A6400_001a6400, &recomp_gen::fn_sub_1A6400_001a6400__recomp},
    {"sub_1A6860", 0x1A6860, &recomp_gen::fn_sub_1A6860_001a6860, &recomp_gen::fn_sub_1A6860_001a6860__recomp},
    {"sub_1A6C00", 0x1A6C00, &recomp_gen::fn_sub_1A6C00_001a6c00, &recomp_gen::fn_sub_1A6C00_001a6c00__recomp},
    {"sub_1A7170", 0x1A7170, &recomp_gen::fn_sub_1A7170_001a7170, &recomp_gen::fn_sub_1A7170_001a7170__recomp},
    {"sub_1A7570", 0x1A7570, &recomp_gen::fn_sub_1A7570_001a7570, &recomp_gen::fn_sub_1A7570_001a7570__recomp},
    {"sub_1A7710", 0x1A7710, &recomp_gen::fn_sub_1A7710_001a7710, &recomp_gen::fn_sub_1A7710_001a7710__recomp},
    {"sub_1AD9E0", 0x1AD9E0, &recomp_gen::fn_sub_1AD9E0_001ad9e0, &recomp_gen::fn_sub_1AD9E0_001ad9e0__recomp},
    {"sub_1CD9A0", 0x1CD9A0, &recomp_gen::fn_sub_1CD9A0_001cd9a0, &recomp_gen::fn_sub_1CD9A0_001cd9a0__recomp},
    {"K_Encount_PickEncounter", 0x1D78C0, &recomp_gen::fn_K_Encount_PickEncounter_001d78c0, &recomp_gen::fn_K_Encount_PickEncounter_001d78c0__recomp},
    {"sub_1DA020", 0x1DA020, &recomp_gen::fn_sub_1DA020_001da020, &recomp_gen::fn_sub_1DA020_001da020__recomp},
    {"sub_1F9E90", 0x1F9E90, &recomp_gen::fn_sub_1F9E90_001f9e90, &recomp_gen::fn_sub_1F9E90_001f9e90__recomp},
    {"sub_25BE60", 0x25BE60, &recomp_gen::fn_sub_25BE60_0025be60, &recomp_gen::fn_sub_25BE60_0025be60__recomp},
    {"sub_351C20", 0x351C20, &recomp_gen::fn_sub_351C20_00351c20, &recomp_gen::fn_sub_351C20_00351c20__recomp},
    {"sub_3580F0", 0x3580F0, &recomp_gen::fn_sub_3580F0_003580f0, &recomp_gen::fn_sub_3580F0_003580f0__recomp},
    {"sub_3F33D0", 0x3F33D0, &recomp_gen::fn_sub_3F33D0_003f33d0, &recomp_gen::fn_sub_3F33D0_003f33d0__recomp},
    {"sub_3F39A0", 0x3F39A0, &recomp_gen::fn_sub_3F39A0_003f39a0, &recomp_gen::fn_sub_3F39A0_003f39a0__recomp},
    {"sub_3FFE60", 0x3FFE60, &recomp_gen::fn_sub_3FFE60_003ffe60, &recomp_gen::fn_sub_3FFE60_003ffe60__recomp},
    {"sub_418C10", 0x418C10, &recomp_gen::fn_sub_418C10_00418c10, &recomp_gen::fn_sub_418C10_00418c10__recomp},
    {"sub_419B80", 0x419B80, &recomp_gen::fn_sub_419B80_00419b80, &recomp_gen::fn_sub_419B80_00419b80__recomp},
    {"sub_41A310", 0x41A310, &recomp_gen::fn_sub_41A310_0041a310, &recomp_gen::fn_sub_41A310_0041a310__recomp},
    {"_sceMpegPictureData0", 0x4FC168, &recomp_gen::fn__sceMpegPictureData0_004fc168, &recomp_gen::fn__sceMpegPictureData0_004fc168__recomp},
    {"_sceMpegPeepBit", 0x4FD740, &recomp_gen::fn__sceMpegPeepBit_004fd740, &recomp_gen::fn__sceMpegPeepBit_004fd740__recomp},
    {"j__sceMpegFlushBuf_0", 0x4FF9D0, &recomp_gen::fn_j__sceMpegFlushBuf_0_004ff9d0, &recomp_gen::fn_j__sceMpegFlushBuf_0_004ff9d0__recomp},
    {"_sceMpegNextHeader", 0x4FF9D8, &recomp_gen::fn__sceMpegNextHeader_004ff9d8, &recomp_gen::fn__sceMpegNextHeader_004ff9d8__recomp},
    {"flushByteBoundary", 0x4FFB38, &recomp_gen::fn_flushByteBoundary_004ffb38, &recomp_gen::fn_flushByteBoundary_004ffb38__recomp},
    {"_clearOnce", 0x4FFDA8, &recomp_gen::fn__clearOnce_004ffda8, &recomp_gen::fn__clearOnce_004ffda8__recomp},
    {"sceMpegCreate", 0x4FFE78, &recomp_gen::fn_sceMpegCreate_004ffe78, &recomp_gen::fn_sceMpegCreate_004ffe78__recomp},
    {"sceMpegInit", 0x500A20, &recomp_gen::fn_sceMpegInit_00500a20, &recomp_gen::fn_sceMpegInit_00500a20__recomp},
    {"sceMpegReset", 0x500BB8, &recomp_gen::fn_sceMpegReset_00500bb8, &recomp_gen::fn_sceMpegReset_00500bb8__recomp},
    {"_sceMpegAlalcFree", 0x501090, &recomp_gen::fn__sceMpegAlalcFree_00501090, &recomp_gen::fn__sceMpegAlalcFree_00501090__recomp},
    {"_sceMpegAlalcAlloc", 0x5010A0, &recomp_gen::fn__sceMpegAlalcAlloc_005010a0, &recomp_gen::fn__sceMpegAlalcAlloc_005010a0__recomp},
    {"_sceMpegOutputFrame", 0x501BA8, &recomp_gen::fn__sceMpegOutputFrame_00501ba8, &recomp_gen::fn__sceMpegOutputFrame_00501ba8__recomp},
    {"_sceMpegCscStoreRefImage", 0x501DF8, &recomp_gen::fn__sceMpegCscStoreRefImage_00501df8, &recomp_gen::fn__sceMpegCscStoreRefImage_00501df8__recomp},
    {"_sceAddIntcHandler", 0x502E40, &recomp_gen::fn__sceAddIntcHandler_00502e40, &recomp_gen::fn__sceAddIntcHandler_00502e40__recomp},
    {"_sceRemoveDmacHandler", 0x502E90, &recomp_gen::fn__sceRemoveDmacHandler_00502e90, &recomp_gen::fn__sceRemoveDmacHandler_00502e90__recomp},
    {"_sceSleepThread", 0x503080, &recomp_gen::fn__sceSleepThread_00503080, &recomp_gen::fn__sceSleepThread_00503080__recomp},
    {"EnableIntc", 0x503CA8, &recomp_gen::fn_EnableIntc_00503ca8, &recomp_gen::fn_EnableIntc_00503ca8__recomp},
    {"DisableDmac", 0x503D10, &recomp_gen::fn_DisableDmac_00503d10, &recomp_gen::fn_DisableDmac_00503d10__recomp},
    {"iWakeupThread", 0x504028, &recomp_gen::fn_iWakeupThread_00504028, &recomp_gen::fn_iWakeupThread_00504028__recomp},
    {"sub_5064F8", 0x5064F8, &recomp_gen::fn_sub_5064F8_005064f8, &recomp_gen::fn_sub_5064F8_005064f8__recomp},
    {"sub_50E000", 0x50E000, &recomp_gen::fn_sub_50E000_0050e000, &recomp_gen::fn_sub_50E000_0050e000__recomp},
    {"_send_to_iop", 0x511478, &recomp_gen::fn__send_to_iop_00511478, &recomp_gen::fn__send_to_iop_00511478__recomp},
    {"sceSdRemoteInit", 0x512868, &recomp_gen::fn_sceSdRemoteInit_00512868, &recomp_gen::fn_sceSdRemoteInit_00512868__recomp},
    {"sceMc2Init", 0x5130E8, &recomp_gen::fn_sceMc2Init_005130e8, &recomp_gen::fn_sceMc2Init_005130e8__recomp},
    {"sceMc2SearchFileAsync", 0x5137B8, &recomp_gen::fn_sceMc2SearchFileAsync_005137b8, &recomp_gen::fn_sceMc2SearchFileAsync_005137b8__recomp},
    {"sceMc2ReadFileAsync", 0x513968, &recomp_gen::fn_sceMc2ReadFileAsync_00513968, &recomp_gen::fn_sceMc2ReadFileAsync_00513968__recomp},
    {"sceMc2CheckAsync", 0x514900, &recomp_gen::fn_sceMc2CheckAsync_00514900, &recomp_gen::fn_sceMc2CheckAsync_00514900__recomp},
    {"_sceMcCoreGetCardSpec", 0x51AFD8, &recomp_gen::fn__sceMcCoreGetCardSpec_0051afd8, &recomp_gen::fn__sceMcCoreGetCardSpec_0051afd8__recomp},
    {"_sceMcCoreCheckNewCard", 0x51B1B0, &recomp_gen::fn__sceMcCoreCheckNewCard_0051b1b0, &recomp_gen::fn__sceMcCoreCheckNewCard_0051b1b0__recomp},
    {"_sceMcCoreClearNewCardFlag", 0x51B2C0, &recomp_gen::fn__sceMcCoreClearNewCardFlag_0051b2c0, &recomp_gen::fn__sceMcCoreClearNewCardFlag_0051b2c0__recomp},
    {"_sceMcCoreAuthentication", 0x51B3B0, &recomp_gen::fn__sceMcCoreAuthentication_0051b3b0, &recomp_gen::fn__sceMcCoreAuthentication_0051b3b0__recomp},
    {"_sceMcCoreWriteBack", 0x51B4A0, &recomp_gen::fn__sceMcCoreWriteBack_0051b4a0, &recomp_gen::fn__sceMcCoreWriteBack_0051b4a0__recomp},
    {"_sceMcCoreReadPage2", 0x51B708, &recomp_gen::fn__sceMcCoreReadPage2_0051b708, &recomp_gen::fn__sceMcCoreReadPage2_0051b708__recomp},
    {"_sceMcCoreGetConnection", 0x51C0C0, &recomp_gen::fn__sceMcCoreGetConnection_0051c0c0, &recomp_gen::fn__sceMcCoreGetConnection_0051c0c0__recomp},
    {"_sceMcCoreCreateSocket", 0x51C130, &recomp_gen::fn__sceMcCoreCreateSocket_0051c130, &recomp_gen::fn__sceMcCoreCreateSocket_0051c130__recomp},
    {"sceDbcInit", 0x51C3B8, &recomp_gen::fn_sceDbcInit_0051c3b8, &recomp_gen::fn_sceDbcInit_0051c3b8__recomp},
    {"sceSpu2MemAllocate", 0x51D6F8, &recomp_gen::fn_sceSpu2MemAllocate_0051d6f8, &recomp_gen::fn_sceSpu2MemAllocate_0051d6f8__recomp},
    {"sceSkInit", 0x51DA48, &recomp_gen::fn_sceSkInit_0051da48, &recomp_gen::fn_sceSkInit_0051da48__recomp},
    {"sceSkSsInit", 0x51DA50, &recomp_gen::fn_sceSkSsInit_0051da50, &recomp_gen::fn_sceSkSsInit_0051da50__recomp},
    {"sceSkSsSOUND_Control", 0x51DB00, &recomp_gen::fn_sceSkSsSOUND_Control_0051db00, &recomp_gen::fn_sceSkSsSOUND_Control_0051db00__recomp},
    {"sceSkSsSESQ_Control", 0x51DF58, &recomp_gen::fn_sceSkSsSESQ_Control_0051df58, &recomp_gen::fn_sceSkSsSESQ_Control_0051df58__recomp},
    {"sceSkSsSESQ_Status", 0x51E028, &recomp_gen::fn_sceSkSsSESQ_Status_0051e028, &recomp_gen::fn_sceSkSsSESQ_Status_0051e028__recomp},
    {"malloc", 0x520728, &recomp_gen::fn_malloc_00520728, &recomp_gen::fn_malloc_00520728__recomp},
    {"cfree", 0x520748, &recomp_gen::fn_cfree_00520748, &recomp_gen::fn_cfree_00520748__recomp},
    {"pow", 0x52E9D0, &recomp_gen::fn_pow_0052e9d0, &recomp_gen::fn_pow_0052e9d0__recomp},
    {"sub_5379B0", 0x5379B0, &recomp_gen::fn_sub_5379B0_005379b0, &recomp_gen::fn_sub_5379B0_005379b0__recomp},
    {"sub_537F30", 0x537F30, &recomp_gen::fn_sub_537F30_00537f30, &recomp_gen::fn_sub_537F30_00537f30__recomp},
    {"sub_537F40", 0x537F40, &recomp_gen::fn_sub_537F40_00537f40, &recomp_gen::fn_sub_537F40_00537f40__recomp},
    {"width__CQ24_STL8ios_base", 0x537FE8, &recomp_gen::fn_width__CQ24_STL8ios_base_00537fe8, &recomp_gen::fn_width__CQ24_STL8ios_base_00537fe8__recomp},
    {"sub_538038", 0x538038, &recomp_gen::fn_sub_538038_00538038, &recomp_gen::fn_sub_538038_00538038__recomp},
    {"sub_5383E8", 0x5383E8, &recomp_gen::fn_sub_5383E8_005383e8, &recomp_gen::fn_sub_5383E8_005383e8__recomp},
    {"sub_5383F0", 0x5383F0, &recomp_gen::fn_sub_5383F0_005383f0, &recomp_gen::fn_sub_5383F0_005383f0__recomp},
    {"sub_5389B0", 0x5389B0, &recomp_gen::fn_sub_5389B0_005389b0, &recomp_gen::fn_sub_5389B0_005389b0__recomp},
    {"sub_53DD10", 0x53DD10, &recomp_gen::fn_sub_53DD10_0053dd10, &recomp_gen::fn_sub_53DD10_0053dd10__recomp},
    {"sub_53EA90", 0x53EA90, &recomp_gen::fn_sub_53EA90_0053ea90, &recomp_gen::fn_sub_53EA90_0053ea90__recomp},
    {"sub_53F8B8", 0x53F8B8, &recomp_gen::fn_sub_53F8B8_0053f8b8, &recomp_gen::fn_sub_53F8B8_0053f8b8__recomp},
    {"sub_53F940", 0x53F940, &recomp_gen::fn_sub_53F940_0053f940, &recomp_gen::fn_sub_53F940_0053f940__recomp},
    {"ADXM_ExecMain", 0x540EC0, &recomp_gen::fn_ADXM_ExecMain_00540ec0, &recomp_gen::fn_ADXM_ExecMain_00540ec0__recomp},
    {"sub_541008", 0x541008, &recomp_gen::fn_sub_541008_00541008, &recomp_gen::fn_sub_541008_00541008__recomp},
    {"cosl_1", 0x541A78, &recomp_gen::fn_cosl_1_00541a78, &recomp_gen::fn_cosl_1_00541a78__recomp},
    {"coshl_1", 0x541A90, &recomp_gen::fn_coshl_1_00541a90, &recomp_gen::fn_coshl_1_00541a90__recomp},
    {"hypotf_1", 0x541AC0, &recomp_gen::fn_hypotf_1_00541ac0, &recomp_gen::fn_hypotf_1_00541ac0__recomp},
    {"sub_545FC8", 0x545FC8, &recomp_gen::fn_sub_545FC8_00545fc8, &recomp_gen::fn_sub_545FC8_00545fc8__recomp},
    {"sub_546058", 0x546058, &recomp_gen::fn_sub_546058_00546058, &recomp_gen::fn_sub_546058_00546058__recomp},
    {"sub_5460E0", 0x5460E0, &recomp_gen::fn_sub_5460E0_005460e0, &recomp_gen::fn_sub_5460E0_005460e0__recomp},
    {"sub_5465A0", 0x5465A0, &recomp_gen::fn_sub_5465A0_005465a0, &recomp_gen::fn_sub_5465A0_005465a0__recomp},
    {"sub_5466B8", 0x5466B8, &recomp_gen::fn_sub_5466B8_005466b8, &recomp_gen::fn_sub_5466B8_005466b8__recomp},
    {"sceInsockBind_2", 0x548B38, &recomp_gen::fn_sceInsockBind_2_00548b38, &recomp_gen::fn_sceInsockBind_2_00548b38__recomp},
    {"sceInsockListen_2", 0x549160, &recomp_gen::fn_sceInsockListen_2_00549160, &recomp_gen::fn_sceInsockListen_2_00549160__recomp},
    {"expl_4", 0x54D148, &recomp_gen::fn_expl_4_0054d148, &recomp_gen::fn_expl_4_0054d148__recomp},
    {"sub_552658", 0x552658, &recomp_gen::fn_sub_552658_00552658, &recomp_gen::fn_sub_552658_00552658__recomp},
    {"sub_552680", 0x552680, &recomp_gen::fn_sub_552680_00552680, &recomp_gen::fn_sub_552680_00552680__recomp},
    {"dvCiGetStat", 0x55A720, &recomp_gen::fn_dvCiGetStat_0055a720, &recomp_gen::fn_dvCiGetStat_0055a720__recomp},
    {"dvci_conv_fname", 0x55A9B0, &recomp_gen::fn_dvci_conv_fname_0055a9b0, &recomp_gen::fn_dvci_conv_fname_0055a9b0__recomp},
    {"sub_55D2A0", 0x55D2A0, &recomp_gen::fn_sub_55D2A0_0055d2a0, &recomp_gen::fn_sub_55D2A0_0055d2a0__recomp},
    {"sub_55D3A8", 0x55D3A8, &recomp_gen::fn_sub_55D3A8_0055d3a8, &recomp_gen::fn_sub_55D3A8_0055d3a8__recomp},
    {"sub_55D3F8", 0x55D3F8, &recomp_gen::fn_sub_55D3F8_0055d3f8, &recomp_gen::fn_sub_55D3F8_0055d3f8__recomp},
    {"sub_55D790", 0x55D790, &recomp_gen::fn_sub_55D790_0055d790, &recomp_gen::fn_sub_55D790_0055d790__recomp},
    {"sub_55D7C0", 0x55D7C0, &recomp_gen::fn_sub_55D7C0_0055d7c0, &recomp_gen::fn_sub_55D7C0_0055d7c0__recomp},
    {"sub_560DB8", 0x560DB8, &recomp_gen::fn_sub_560DB8_00560db8, &recomp_gen::fn_sub_560DB8_00560db8__recomp},
    {"sub_564FE8", 0x564FE8, &recomp_gen::fn_sub_564FE8_00564fe8, &recomp_gen::fn_sub_564FE8_00564fe8__recomp},
    {"sub_57AC68", 0x57AC68, &recomp_gen::fn_sub_57AC68_0057ac68, &recomp_gen::fn_sub_57AC68_0057ac68__recomp},
    {"sub_57AE90", 0x57AE90, &recomp_gen::fn_sub_57AE90_0057ae90, &recomp_gen::fn_sub_57AE90_0057ae90__recomp},
    {"sub_57C730", 0x57C730, &recomp_gen::fn_sub_57C730_0057c730, &recomp_gen::fn_sub_57C730_0057c730__recomp},
    {"sub_57DB58", 0x57DB58, &recomp_gen::fn_sub_57DB58_0057db58, &recomp_gen::fn_sub_57DB58_0057db58__recomp},
    {"my_malloc_0", 0x581070, &recomp_gen::fn_my_malloc_0_00581070, &recomp_gen::fn_my_malloc_0_00581070__recomp},
    {"sub_588F48", 0x588F48, &recomp_gen::fn_sub_588F48_00588f48, &recomp_gen::fn_sub_588F48_00588f48__recomp},
    {"sub_5895F0", 0x5895F0, &recomp_gen::fn_sub_5895F0_005895f0, &recomp_gen::fn_sub_5895F0_005895f0__recomp},
    {"sub_589CB0", 0x589CB0, &recomp_gen::fn_sub_589CB0_00589cb0, &recomp_gen::fn_sub_589CB0_00589cb0__recomp},
    {"sub_589CD0", 0x589CD0, &recomp_gen::fn_sub_589CD0_00589cd0, &recomp_gen::fn_sub_589CD0_00589cd0__recomp},
    {"sub_589D80", 0x589D80, &recomp_gen::fn_sub_589D80_00589d80, &recomp_gen::fn_sub_589D80_00589d80__recomp},
    {"sub_589F38", 0x589F38, &recomp_gen::fn_sub_589F38_00589f38, &recomp_gen::fn_sub_589F38_00589f38__recomp},
    {"sub_5944A8", 0x5944A8, &recomp_gen::fn_sub_5944A8_005944a8, &recomp_gen::fn_sub_5944A8_005944a8__recomp},
    {"sub_5946A8", 0x5946A8, &recomp_gen::fn_sub_5946A8_005946a8, &recomp_gen::fn_sub_5946A8_005946a8__recomp},
    {"sub_5947A8", 0x5947A8, &recomp_gen::fn_sub_5947A8_005947a8, &recomp_gen::fn_sub_5947A8_005947a8__recomp},
    {"sub_595BC0", 0x595BC0, &recomp_gen::fn_sub_595BC0_00595bc0, &recomp_gen::fn_sub_595BC0_00595bc0__recomp},
    {"sub_597368", 0x597368, &recomp_gen::fn_sub_597368_00597368, &recomp_gen::fn_sub_597368_00597368__recomp},
    {"sceInsockGetErrnoMode_1", 0x597438, &recomp_gen::fn_sceInsockGetErrnoMode_1_00597438, &recomp_gen::fn_sceInsockGetErrnoMode_1_00597438__recomp},
    {"sub_5990C0", 0x5990C0, &recomp_gen::fn_sub_5990C0_005990c0, &recomp_gen::fn_sub_5990C0_005990c0__recomp},
    {"sub_5A1A30", 0x5A1A30, &recomp_gen::fn_sub_5A1A30_005a1a30, &recomp_gen::fn_sub_5A1A30_005a1a30__recomp},
};

// The argument kinds of the snapshot sweep (a0..a3; default "Bnnn"): B a block of kScratch (+4 / +60 pointers to
// cleared blocks, +56 a count 1..4, +140 a count 0..5, floats at +256), Z a block or 0, S a guest file name, O a field
// object id (kind 0..3 in bits 10..15), U gFldUnitsPc, T a live KwlnTask, e an event id 0..63, E an encounter id 0..399, f a floor
// 0..89, L a social link 0..12, s a shop 0..9, k a menu kind 0..11, m a size 1..4096, w a random word, h -1..7,
// n 0..7, z 0 / 1, 0 zero, - none.
const std::map<std::string, const char*> kKinds = {
    {"start", "-"},
    {"H_Memcard_UpdateChkAreaSeq", "-"},
    {"kwlnVsyncFieldGate", "-"},
    {"sub_1A0430", "Oz"},
    {"sub_1A0700", "O"},
    {"sub_1A07F0", "O"},
    {"sub_1A08E0", "O"},
    {"sub_1A1150", "-"},
    {"sub_1A1190", "-"},
    {"sub_1A1210", "BBBZ"},
    {"sub_1A4600", "-"},
    {"sub_1A4860", "T"},
    {"sub_1A6400", "BS"},
    {"sub_1A6860", "BB"},
    {"sub_1CD9A0", "e"},
    {"K_Encount_PickEncounter", "fnn"},
    {"sub_1DA020", "Unn"},
    {"sub_1F9E90", "Lh"},
    {"sub_25BE60", "nnn"},
    {"sub_3580F0", "Zw"},
    {"sub_3F33D0", "sn"},
    {"sub_3F39A0", "szn"},
    {"sub_3FFE60", "k"},
    {"sub_418C10", "-"},
    {"sub_41A310", "nB"},
    {"sceMc2SearchFileAsync", "nSn"},
    {"sceMc2ReadFileAsync", "nSnn"},
    {"sceSpu2MemAllocate", "m"},
    {"malloc", "m"},
    {"cfree", "0"},
    {"sub_589F38", "ww"},
    {"sub_589CB0", "Bnw"},
    {"sub_589CD0", "Bn"},
    {"sub_5895F0", "BnB"},
    {"sub_588F48", "BnnB"},
    {"dvci_conv_fname", "SB"},
    {"dvCiGetStat", "Z"},
    {"sub_55D790", "Z"},
    {"sub_55D7C0", "Z"},
};

constexpr u32 kFldUnitsPc = 0x8717A0u;  // gFldUnitsPc
constexpr u32 kTaskSlot = 0x7CDED8u;    // a global holding a KwlnTask (the parent of the task creators)
constexpr u32 kNames = kScratch + 0x20000u;
const char* const kFileNames[] = {"/BASLUS-21621SaveG0/BASLUS-21621SaveG0", "data/field/f001.bin", "ADX\\BGM_01.ADX;1",
                                  "a", "/SYSTEM.CNF"};

const char* kinds_of(const std::string& name) {
    const auto it = kKinds.find(name);
    return it == kKinds.end() ? "Bnnn" : it->second;
}

// One argument of kind `k` (writes the world it needs); B blocks come from kScratch upwards.
u64 arg_of(Machine& m, char k, std::mt19937& rng, u32& blk) {
    auto block = [&]() {
        const u32 b = kScratch + 0x4000u * blk++;
        std::memset(m.at(b), 0, 0x3000);
        w32(m, b + 4, b + 0x400);
        w32(m, b + 56, 1 + rng() % 4);
        w32(m, b + 60, b + 0x800);
        w32(m, b + 140, rng() % 6);
        w32(m, b + 0x800 + 56, 1 + rng() % 3);
        for (u32 i = 0; i < 16; ++i) wf32(m, b + 256 + 4 * i, static_cast<f32>(static_cast<int>(rng() % 1601) - 800));
        return b;
    };
    switch (k) {
    case 'B': return block();
    case 'Z': return (rng() % 4 == 0) ? 0u : block();
    case 'S': {
        const u32 s = kNames + 0x100u * (blk % 8);
        wstr(m, s, kFileNames[rng() % (sizeof(kFileNames) / sizeof(kFileNames[0]))]);
        return s;
    }
    case 'O': return (static_cast<u64>(rng() % 4) << 10) | (rng() % 32);
    case 'U': return kFldUnitsPc;
    case 'T': return r32(m, kTaskSlot);  // a live KwlnTask (types_query: *(0x7CDED8) is one in every snapshot)
    case 'e': return rng() % 64;
    case 'E': return rng() % 400;
    case 'f': return rng() % 90;
    case 'L': return rng() % 13;
    case 's': return rng() % 10;
    case 'k': return rng() % 12;
    case 'm': return 1 + rng() % 4096;
    case 'w': return rng();
    case 'h': return static_cast<u64>(static_cast<s64>(static_cast<int>(rng() % 9) - 1));
    case 'z': return rng() % 2;
    case '0': return 0;
    default: return rng() % 8;
    }
}

// Functions whose snapshot pairs may spin on a recorder (a loop whose exit needs a real callee's result).
const std::set<std::string> kSpins = {"sub_57DB58"};

// Functions install_standard's heap stands in at their own address: in a stand-in pair the hand side's entry met the
// heap stand-in (0 cycles) while the recompiled body ran, so they pair on the random worlds only.
const std::set<std::string> kWorldStoodIn = {"malloc", "cfree"};

u32 v0_of(const SiPair& p) { return static_cast<u32>(p.hw.recomp.gpr[GPR_V0].u64[0]); }
u64 v0_64(const SiPair& p) { return p.hw.recomp.gpr[GPR_V0].u64[0]; }

}  // namespace

TEST_CASE("game(sweep5b): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, 0x01810000u, 0x10000u, 64);
}

// Every body on the packet's snapshots: arguments of each function's kind (above), the snapshot restored between pairs.
// The pairs run on the stand-ins (every callee this build does not emit recorded); a pair whose original faults is run
// again as a plain pair, which compares the two stops.
TEST_CASE("game(sweep5b): every body on the replay snapshots with real structures") {
    struct Snap {
        const char* dir;
        u32 reps;
    };
    const Snap snaps[] = {{"b_5800", 2}, {"dorm_replay_4900", 2}, {"climb_ref_17000", 2}, {"fusion_ref_6300", 1}, {"shop_ref_4100", 1}};
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    HwCheck hw;
    hw.gpr_mask = kAllGprs;
    int pairs = 0, stood = 0, stops = 0, used = 0;
    std::map<std::string, int> stop_of, spun;
    for (const Snap& sn : snaps) {
        std::vector<u8> base;
        auto mp = real_machine(sn.dir, base);
        if (!mp) {
            MESSAGE("SKIP: no ELF or snapshot " << std::string(sn.dir));
            continue;
        }
        Machine& m = *mp;
        write_rw_slots(m);
        base.assign(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        ++used;
        const u32 reps = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : sn.reps;
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            if (kWorldStoodIn.count(c.name) != 0) continue;
            const char* kinds = kinds_of(c.name);
            for (u32 rep = 0; rep < reps; ++rep) {
                if (trace) std::fprintf(stderr, "%s %s rep %u\n", sn.dir, c.name, rep);
                const std::mt19937 rng0{rep * 104729u + c.addr + static_cast<u32>(used) * 7u};
                u64 a[4] = {};
                // the arguments and the world they need (the same draws after every reset)
                auto draw = [&](Machine& mm) {
                    std::mt19937 rng = rng0;
                    u32 blk = 0;
                    for (u64& x : a) x = rng() % 8;
                    for (std::size_t i = 0; i < 4 && kinds[i] && kinds[i] != '-'; ++i) a[i] = arg_of(mm, kinds[i], rng, blk);
                    return rng();
                };
                const u32 seed = draw(m);
                ++pairs;
                try {
                    run_case(m, base, kCases, c.name, Args{a[0], a[1], a[2], a[3]}, seed, [&](Machine& mm) { draw(mm); });
                    ++stood;
                } catch (const rt_test::FatalEvent&) {
                    // a guest fault in the original: the plain pair compares the two stops
                    reset(m, base);
                    draw(m);
                    const hgp::Run r = hgp::pair(m, c.hand, c.recomp, Args{a[0], a[1], a[2], a[3]}, seed, c.name, hw);
                    if (r.stopped) {
                        ++stops;
                        ++stop_of[std::string(c.name) + " (" + r.what.substr(0, 40) + " at " + hex64(r.stop_pc) + ")"];
                    }
                } catch (const std::runtime_error& e) {
                    // a loop that only ends on a real callee's result, spinning on a recorder: allowed for the
                    // functions of kSpins alone (the random sweep and their own worlds still pair them)
                    const std::string w = e.what();
                    if (w.find("stand-in log over") == std::string::npos) throw;
                    ++spun[c.name];
                }
                reset(m, base);
            }
        }
    }
    std::string why;
    for (const auto& [k, n] : stop_of) why += " " + k + " x" + std::to_string(n) + ";";
    MESSAGE("snapshots: " << pairs << " pairs on " << used << " snapshot(s), " << stood << " on the stand-ins, " << stops
                          << " ended at a compared fault stop:" << why.substr(0, 1500));
    for (const auto& [name, n] : spun) {
        INFO(name << " spun on a recorder " << n << " time(s)");
        CHECK(kSpins.count(name) == 1u);
    }
}

// The CRI channel table: 116-byte rows from +4880 (+4884 open, +4888 a word, +4896 four 16-byte vectors, +4900 the
// value sub_5895F0 hands out).
TEST_CASE("game(sweep5b): the CRI channel table accessors") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    const u32 t = kScratch;
    auto clear = [t](Machine& mm) { std::memset(mm.at(t), 0, 0x2000); };
    run_case_w(m, base, kCases, "sub_589CB0", {t, 3, 0x12345678u, 0}, 901, clear);
    CHECK(r32(m, t + 116 * 3 + 4888) == 0x12345678u);
    run_case_w(m, base, kCases, "sub_589CD0", {t, 2, 0, 0}, 902, [t, clear](Machine& mm) {
        clear(mm);
        w32(mm, t + 116 * 2 + 4888, 0xCAFEF00Du);
    });
    // (the result: the recompiled run's $v0, compared with the hand run's by the pair)
    const u32 src = t + 0x1800;
    run_case_w(m, base, kCases, "sub_588F48", {t, 1, 2, src}, 903, [t, src, clear](Machine& mm) {
        clear(mm);
        for (u32 i = 0; i < 16; ++i) w8(mm, src + i, static_cast<u8>(0xA0 + i));
    });
    for (u32 i = 0; i < 16; ++i) CHECK(r8(m, t + 116 * 1 + 4896 + 16 * 2 + i) == 0xA0 + i);
    const u32 out = t + 0x1900;
    const SiPair open = run_case_w(m, base, kCases, "sub_5895F0", {t, 4, out, 0}, 904, [t, out, clear](Machine& mm) {
        clear(mm);
        w32(mm, t + 116 * 4 + 4884, 1);
        w32(mm, t + 116 * 4 + 4900, 0x0BADBEEFu);
        w32(mm, out, 0xFFFFFFFFu);
    });
    CHECK(v0_of(open) == 0u);
    CHECK(r32(m, out) == 0x0BADBEEFu);
}

// sub_3580F0: w0 = seed ^ 0x0AED1A0C, w1 = rotr8(w0), w2 = rotr8(w1 ^ 0xAA5A02FE), w3 = rotr8(w2 ^ 0x11BE81C7).
TEST_CASE("game(sweep5b): sub_3580F0 seeds the scrambler state") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    auto rotr8 = [](u32 x) { return (x >> 8) | (x << 24); };
    u32 seed_no = 910;
    for (const u32 seed : {0u, 1u, 0xDEADBEEFu, 0x0AED1A0Cu}) {
        run_case_w(m, base, kCases, "sub_3580F0", {kScratch, seed, 0, 0}, ++seed_no, {});
        const u32 w0 = seed ^ 0x0AED1A0Cu;
        const u32 w1 = rotr8(w0);
        const u32 w2 = rotr8(w1 ^ 0xAA5A02FEu);
        const u32 w3 = rotr8(w2 ^ 0x11BE81C7u);
        INFO("seed " << hex64(seed));
        CHECK(r32(m, kScratch) == w0);
        CHECK(r32(m, kScratch + 4) == w1);
        CHECK(r32(m, kScratch + 8) == w2);
        CHECK(r32(m, kScratch + 12) == w3);
    }
    // a0 == 0: the default state at 0x957BF0
    run_case_w(m, base, kCases, "sub_3580F0", {0, 5, 0, 0}, 920, {});
    CHECK(r32(m, 0x957BF0u) == (5u ^ 0x0AED1A0Cu));
}

// The one-load accessors and small rules: sub_537F40 (state 1 reads as 2 while +232 is set), sub_595BC0, sub_589F38's
// carry, the LSC getters, sceSkInit and sceInsockGetErrnoMode_1.
TEST_CASE("game(sweep5b): accessors and small rules") {
    std::vector<u8> base;
    auto mp = elf_machine(base);
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    const u32 h = kScratch;
    u32 seed = 930;
    auto handle = [h](s8 state, u32 f232) {
        return [h, state, f232](Machine& mm) {
            std::memset(mm.at(h), 0, 0x200);
            w8(mm, h + 14, static_cast<u8>(state));
            w32(mm, h + 232, f232);
        };
    };
    CHECK(v0_of(run_case_w(m, base, kCases, "sub_537F40", {h, 0, 0, 0}, ++seed, handle(1, 7))) == 2u);
    CHECK(v0_of(run_case_w(m, base, kCases, "sub_537F40", {h, 0, 0, 0}, ++seed, handle(1, 0))) == 1u);
    CHECK(v0_of(run_case_w(m, base, kCases, "sub_537F40", {h, 0, 0, 0}, ++seed, handle(3, 7))) == 3u);
    CHECK(v0_of(run_case_w(m, base, kCases, "sub_537F40", {h, 0, 0, 0}, ++seed, handle(-1, 7))) == 0xFFFFFFFFu);
    // sub_595BC0: 1 unless +72 is 1..4; then +68 == 0
    for (const u32 state : {0u, 1u, 4u, 5u}) {
        for (const u32 busy : {0u, 3u}) {
            const SiPair p = run_case_w(m, base, kCases, "sub_595BC0", {h, 0, 0, 0}, ++seed, [h, state, busy](Machine& mm) {
                std::memset(mm.at(h), 0, 0x100);
                w32(mm, h + 72, state);
                w32(mm, h + 68, busy);
            });
            const u32 want = (state >= 1 && state <= 4) ? (busy == 0 ? 1u : 0u) : 1u;
            INFO("state " << state << " +68 " << busy);
            CHECK(v0_of(p) == want);
        }
    }
    // sub_589F38: the low word becomes a1, the high word carries when a1 is below the old low word
    CHECK(v0_64(run_case_w(m, base, kCases, "sub_589F38", {0x0000000500000010ull, 0x8, 0, 0}, ++seed, {})) == 0x0000000600000008ull);
    CHECK(v0_64(run_case_w(m, base, kCases, "sub_589F38", {0x0000000500000010ull, 0x20, 0, 0}, ++seed, {})) == 0x0000000500000020ull);
    // the LSC getters on a live handle: +1 (s8) and +36
    const SiPair st = run_case_w(m, base, kCases, "sub_55D790", {h, 0, 0, 0}, ++seed, [h](Machine& mm) {
        std::memset(mm.at(h), 0, 0x100);
        w8(mm, h + 1, 0xFE);
    });
    CHECK(v0_of(st) == 0xFFFFFFFEu);
    const SiPair w36 = run_case_w(m, base, kCases, "sub_55D7C0", {h, 0, 0, 0}, ++seed, [h](Machine& mm) {
        std::memset(mm.at(h), 0, 0x100);
        w32(mm, h + 36, 77);
    });
    CHECK(v0_of(w36) == 77u);
    CHECK(v0_of(run_case_w(m, base, kCases, "sceSkInit", {0, 0, 0, 0}, ++seed, {})) == 0u);
    const SiPair em = run_case_w(m, base, kCases, "sceInsockGetErrnoMode_1", {0, 0, 0, 0}, ++seed, {});
    CHECK(v0_of(em) == r32(m, 0x7B476Cu));
}

// The field object lookups with sub_3B54C0 stood in (returning the object `obj`): kinds 1 and 3 give obj + 300 /
// 400 / 416, kind 2 obj + 284 / 384 / 400, kind 0 gives 0; sub_1A0430 sets or clears +40 bit 31. The field camera word:
// sub_1A1150 returns the camera record's +264 (sub_3B5D50 stood in), 0 without a camera.
TEST_CASE("game(sweep5b): field object and camera lookups") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or snapshot dorm_replay_4900");
        return;
    }
    Machine& m = *mp;
    const u32 obj = kScratch;
    auto with_obj = [obj](u64 v0) {
        return [obj, v0](StandInWorld& w) { w.si.install_recorder(0x3B54C0u, "sub_3B54C0", v0 ? obj : 0); };
    };
    auto prep = [obj](Machine& mm) {
        std::memset(mm.at(obj), 0, 0x200);
        w32(mm, obj + 40, 0x00001234u);
    };
    struct Want {
        const char* fn;
        u32 k13, k2;
    };
    u32 seed = 960;
    for (const Want& wnt : {Want{"sub_1A0700", 300, 284}, Want{"sub_1A07F0", 400, 384}, Want{"sub_1A08E0", 416, 400}}) {
        INFO(wnt.fn);
        for (const u32 kind : {1u, 2u, 3u}) {
            const SiPair p = run_case_w(m, base, kCases, wnt.fn, {(kind << 10) | 5u, 0, 0, 0}, ++seed, prep, with_obj(1));
            CHECK(v0_of(p) == obj + (kind == 2 ? wnt.k2 : wnt.k13));
        }
        CHECK(v0_of(run_case_w(m, base, kCases, wnt.fn, {(1u << 10) | 5u, 0, 0, 0}, ++seed, prep, with_obj(0))) == 0u);
        CHECK(v0_of(run_case_w(m, base, kCases, wnt.fn, {5u, 0, 0, 0}, ++seed, prep, with_obj(1))) == 0u);
    }
    run_case_w(m, base, kCases, "sub_1A0430", {(2u << 10) | 1u, 1, 0, 0}, ++seed, prep, with_obj(1));
    CHECK(r32(m, obj + 40) == 0x80001234u);
    run_case_w(m, base, kCases, "sub_1A0430", {(3u << 10) | 1u, 0, 0, 0}, ++seed, [obj](Machine& mm) {
        std::memset(mm.at(obj), 0, 0x200);
        w32(mm, obj + 40, 0x80001234u);
    }, with_obj(1));
    CHECK(r32(m, obj + 40) == 0x00001234u);
    // the camera word
    const u32 cam = kScratch + 0x400;
    auto cam_world = [cam](u64 present) {
        return [cam, present](StandInWorld& w) { w.si.install_recorder(0x3B5D50u, "sub_3B5D50", present ? cam : 0); };
    };
    auto cam_prep = [cam](Machine& mm) {
        std::memset(mm.at(cam), 0, 0x200);
        w32(mm, cam + 264, 0x4455u);
    };
    CHECK(v0_of(run_case_w(m, base, kCases, "sub_1A1150", {0, 0, 0, 0}, ++seed, cam_prep, cam_world(1))) == 0x4455u);
    CHECK(v0_of(run_case_w(m, base, kCases, "sub_1A1150", {0, 0, 0, 0}, ++seed, cam_prep, cam_world(0))) == 0u);
}

// K_Encount_PickEncounter: floors outside 20..58 / 71..78 (and 29, 30, 49, 50) have no encounter table: 0.
TEST_CASE("game(sweep5b): K_Encount_PickEncounter gives 0 on floors without encounters") {
    std::vector<u8> base;
    auto mp = real_machine("climb_ref_17000", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or snapshot climb_ref_17000");
        return;
    }
    Machine& m = *mp;
    u32 seed = 980;
    for (const u32 floor : {0u, 5u, 19u, 29u, 30u, 49u, 50u, 59u, 70u, 79u, 120u}) {
        INFO("floor " << floor);
        CHECK(v0_of(run_case_w(m, base, kCases, "K_Encount_PickEncounter", {floor, 0, 0, 0}, ++seed, {})) == 0u);
    }
}

#else

TEST_CASE("game(sweep5b): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
