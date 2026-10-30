// Slice sweep5b (game/src/field/sweep5b.cpp): 134 bodies made readable from p3fes_handgen's faithful start -- the
// crt0 entry, field / camera / encounter / shop helpers, the memory-card boot check, and library code the game links
// (libmpeg, libkernel / libsif wrappers, libpad, libmc2 / libdbc, libsdr / libsk / libspu2, newlib, CRI ADX / MWSFD).
// Register ABI throughout: arguments in $a0.., the result in $v0.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

// Local layouts the bodies name (offsets confirmed from the instructions; docs/INTEGRATION_LOG.md, sweep5b).
namespace sweep5b_layout {
// Field object ids (sub_1A0430 / sub_1A0700 / sub_1A07F0 / sub_1A08E0): kind in bits 10..15 (1, 2, 3); the object
// comes from sub_3B54C0 on the current scene's object table *(*(0x7CD540) + 8).
inline constexpr u32 kObjKindShift = 10;
inline constexpr s32 kObjFlags = 40;          // bit 31 set / cleared by sub_1A0430
inline constexpr s32 kObjVecA = 300, kObjVecAKind2 = 284;  // sub_1A0700
inline constexpr s32 kObjVecB = 400, kObjVecBKind2 = 384;  // sub_1A07F0
inline constexpr s32 kObjVecC = 416, kObjVecCKind2 = 400;  // sub_1A08E0
// The field camera record (sub_3B5D50(20)).
inline constexpr s32 kCamWord264 = 264, kCamFloat260 = 260;
// CRI handle fields read by the one-load accessors.
inline constexpr s32 kCriState = 14, kCriWord24 = 24, kCriWord144 = 144, kCriWord148 = 148, kCriStatus = 152,
                     kCriWord204 = 204, kCriFlag232 = 232;
// CRI channel table: 116-byte rows from +4880 (computed as ((n * 8 - n) * 4 + n) * 4 = 116 * n).
inline constexpr s32 kChanStride = 116, kChanBase = 4880, kChanOpen = 4884, kChanWord = 4888, kChanVec = 4896,
                     kChanValue = 4900;
// sub_3580F0's 16-byte scrambler: w0 = seed ^ kScr0, w1 = rotr8(w0), w2 = rotr8(w1 ^ kScr1), w3 = rotr8(w2 ^ kScr2).
inline constexpr u32 kScr0 = 0x0AED1A0Cu, kScr1 = 0xAA5A02FEu, kScr2 = 0x11BE81C7u;
}  // namespace sweep5b_layout

void start(EEContext& ctx);  // 0x100008 (register ABI: arguments in $a0.., the result in $v0)
void H_Memcard_UpdateChkAreaSeq(EEContext& ctx);  // 0x191260 (register ABI: arguments in $a0.., the result in $v0)
void kwlnVsyncFieldGate(EEContext& ctx);  // 0x19D320 (register ABI: arguments in $a0.., the result in $v0)
void sub_1A0430(EEContext& ctx);  // 0x1A0430 (register ABI: arguments in $a0.., the result in $v0)
void sub_1A0700(EEContext& ctx);  // 0x1A0700 (register ABI: arguments in $a0.., the result in $v0)
void sub_1A07F0(EEContext& ctx);  // 0x1A07F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_1A08E0(EEContext& ctx);  // 0x1A08E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_1A1150(EEContext& ctx);  // 0x1A1150 (register ABI: arguments in $a0.., the result in $v0)
void sub_1A1190(EEContext& ctx);  // 0x1A1190 (register ABI: arguments in $a0.., the result in $v0)
void sub_1A1210(EEContext& ctx);  // 0x1A1210 (register ABI: arguments in $a0.., the result in $v0)
void sub_1A14C0(EEContext& ctx);  // 0x1A14C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_1A4600(EEContext& ctx);  // 0x1A4600 (register ABI: arguments in $a0.., the result in $v0)
void sub_1A4860(EEContext& ctx);  // 0x1A4860 (register ABI: arguments in $a0.., the result in $v0)
void sub_1A5EA0(EEContext& ctx);  // 0x1A5EA0 (register ABI: arguments in $a0.., the result in $v0)
void sub_1A6400(EEContext& ctx);  // 0x1A6400 (register ABI: arguments in $a0.., the result in $v0)
void sub_1A6860(EEContext& ctx);  // 0x1A6860 (register ABI: arguments in $a0.., the result in $v0)
void sub_1A6C00(EEContext& ctx);  // 0x1A6C00 (register ABI: arguments in $a0.., the result in $v0)
void sub_1A7170(EEContext& ctx);  // 0x1A7170 (register ABI: arguments in $a0.., the result in $v0)
void sub_1A7570(EEContext& ctx);  // 0x1A7570 (register ABI: arguments in $a0.., the result in $v0)
void sub_1A7710(EEContext& ctx);  // 0x1A7710 (register ABI: arguments in $a0.., the result in $v0)
void sub_1AD9E0(EEContext& ctx);  // 0x1AD9E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_1CD9A0(EEContext& ctx);  // 0x1CD9A0 (register ABI: arguments in $a0.., the result in $v0)
void K_Encount_PickEncounter(EEContext& ctx);  // 0x1D78C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_1DA020(EEContext& ctx);  // 0x1DA020 (register ABI: arguments in $a0.., the result in $v0)
void sub_1F9E90(EEContext& ctx);  // 0x1F9E90 (register ABI: arguments in $a0.., the result in $v0)
void sub_25BE60(EEContext& ctx);  // 0x25BE60 (register ABI: arguments in $a0.., the result in $v0)
void sub_351C20(EEContext& ctx);  // 0x351C20 (register ABI: arguments in $a0.., the result in $v0)
void sub_3580F0(EEContext& ctx);  // 0x3580F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3F33D0(EEContext& ctx);  // 0x3F33D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3F39A0(EEContext& ctx);  // 0x3F39A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_3FFE60(EEContext& ctx);  // 0x3FFE60 (register ABI: arguments in $a0.., the result in $v0)
void sub_418C10(EEContext& ctx);  // 0x418C10 (register ABI: arguments in $a0.., the result in $v0)
void sub_419B80(EEContext& ctx);  // 0x419B80 (register ABI: arguments in $a0.., the result in $v0)
void sub_41A310(EEContext& ctx);  // 0x41A310 (register ABI: arguments in $a0.., the result in $v0)
void _sceMpegPictureData0(EEContext& ctx);  // 0x4FC168 (register ABI: arguments in $a0.., the result in $v0)
void _sceMpegPeepBit(EEContext& ctx);  // 0x4FD740 (register ABI: arguments in $a0.., the result in $v0)
void j__sceMpegFlushBuf_0(EEContext& ctx);  // 0x4FF9D0 (register ABI: arguments in $a0.., the result in $v0)
void _sceMpegNextHeader(EEContext& ctx);  // 0x4FF9D8 (register ABI: arguments in $a0.., the result in $v0)
void flushByteBoundary(EEContext& ctx);  // 0x4FFB38 (register ABI: arguments in $a0.., the result in $v0)
void _clearOnce(EEContext& ctx);  // 0x4FFDA8 (register ABI: arguments in $a0.., the result in $v0)
void sceMpegCreate(EEContext& ctx);  // 0x4FFE78 (register ABI: arguments in $a0.., the result in $v0)
void sceMpegInit(EEContext& ctx);  // 0x500A20 (register ABI: arguments in $a0.., the result in $v0)
void sceMpegReset(EEContext& ctx);  // 0x500BB8 (register ABI: arguments in $a0.., the result in $v0)
void _sceMpegAlalcFree(EEContext& ctx);  // 0x501090 (register ABI: arguments in $a0.., the result in $v0)
void _sceMpegAlalcAlloc(EEContext& ctx);  // 0x5010A0 (register ABI: arguments in $a0.., the result in $v0)
void _sceMpegOutputFrame(EEContext& ctx);  // 0x501BA8 (register ABI: arguments in $a0.., the result in $v0)
void _sceMpegCscStoreRefImage(EEContext& ctx);  // 0x501DF8 (register ABI: arguments in $a0.., the result in $v0)
void _sceAddIntcHandler(EEContext& ctx);  // 0x502E40 (register ABI: arguments in $a0.., the result in $v0)
void _sceRemoveDmacHandler(EEContext& ctx);  // 0x502E90 (register ABI: arguments in $a0.., the result in $v0)
void _sceSleepThread(EEContext& ctx);  // 0x503080 (register ABI: arguments in $a0.., the result in $v0)
void EnableIntc(EEContext& ctx);  // 0x503CA8 (register ABI: arguments in $a0.., the result in $v0)
void DisableDmac(EEContext& ctx);  // 0x503D10 (register ABI: arguments in $a0.., the result in $v0)
void iWakeupThread(EEContext& ctx);  // 0x504028 (register ABI: arguments in $a0.., the result in $v0)
void sub_5064F8(EEContext& ctx);  // 0x5064F8 (register ABI: arguments in $a0.., the result in $v0)
void sub_50E000(EEContext& ctx);  // 0x50E000 (register ABI: arguments in $a0.., the result in $v0)
void _send_to_iop(EEContext& ctx);  // 0x511478 (register ABI: arguments in $a0.., the result in $v0)
void sceSdRemoteInit(EEContext& ctx);  // 0x512868 (register ABI: arguments in $a0.., the result in $v0)
void sceMc2Init(EEContext& ctx);  // 0x5130E8 (register ABI: arguments in $a0.., the result in $v0)
void sceMc2SearchFileAsync(EEContext& ctx);  // 0x5137B8 (register ABI: arguments in $a0.., the result in $v0)
void sceMc2ReadFileAsync(EEContext& ctx);  // 0x513968 (register ABI: arguments in $a0.., the result in $v0)
void sceMc2CheckAsync(EEContext& ctx);  // 0x514900 (register ABI: arguments in $a0.., the result in $v0)
void _sceMcCoreGetCardSpec(EEContext& ctx);  // 0x51AFD8 (register ABI: arguments in $a0.., the result in $v0)
void _sceMcCoreCheckNewCard(EEContext& ctx);  // 0x51B1B0 (register ABI: arguments in $a0.., the result in $v0)
void _sceMcCoreClearNewCardFlag(EEContext& ctx);  // 0x51B2C0 (register ABI: arguments in $a0.., the result in $v0)
void _sceMcCoreAuthentication(EEContext& ctx);  // 0x51B3B0 (register ABI: arguments in $a0.., the result in $v0)
void _sceMcCoreWriteBack(EEContext& ctx);  // 0x51B4A0 (register ABI: arguments in $a0.., the result in $v0)
void _sceMcCoreReadPage2(EEContext& ctx);  // 0x51B708 (register ABI: arguments in $a0.., the result in $v0)
void _sceMcCoreGetConnection(EEContext& ctx);  // 0x51C0C0 (register ABI: arguments in $a0.., the result in $v0)
void _sceMcCoreCreateSocket(EEContext& ctx);  // 0x51C130 (register ABI: arguments in $a0.., the result in $v0)
void sceDbcInit(EEContext& ctx);  // 0x51C3B8 (register ABI: arguments in $a0.., the result in $v0)
void sceSpu2MemAllocate(EEContext& ctx);  // 0x51D6F8 (register ABI: arguments in $a0.., the result in $v0)
void sceSkInit(EEContext& ctx);  // 0x51DA48 (register ABI: arguments in $a0.., the result in $v0)
void sceSkSsInit(EEContext& ctx);  // 0x51DA50 (register ABI: arguments in $a0.., the result in $v0)
void sceSkSsSOUND_Control(EEContext& ctx);  // 0x51DB00 (register ABI: arguments in $a0.., the result in $v0)
void sceSkSsSESQ_Control(EEContext& ctx);  // 0x51DF58 (register ABI: arguments in $a0.., the result in $v0)
void sceSkSsSESQ_Status(EEContext& ctx);  // 0x51E028 (register ABI: arguments in $a0.., the result in $v0)
void malloc(EEContext& ctx);  // 0x520728 (register ABI: arguments in $a0.., the result in $v0)
void cfree(EEContext& ctx);  // 0x520748 (register ABI: arguments in $a0.., the result in $v0)
void pow(EEContext& ctx);  // 0x52E9D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_5379B0(EEContext& ctx);  // 0x5379B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_537F30(EEContext& ctx);  // 0x537F30 (register ABI: arguments in $a0.., the result in $v0)
void sub_537F40(EEContext& ctx);  // 0x537F40 (register ABI: arguments in $a0.., the result in $v0)
void width__CQ24_STL8ios_base(EEContext& ctx);  // 0x537FE8 (register ABI: arguments in $a0.., the result in $v0)
void sub_538038(EEContext& ctx);  // 0x538038 (register ABI: arguments in $a0.., the result in $v0)
void sub_5383E8(EEContext& ctx);  // 0x5383E8 (register ABI: arguments in $a0.., the result in $v0)
void sub_5383F0(EEContext& ctx);  // 0x5383F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_5389B0(EEContext& ctx);  // 0x5389B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_53DD10(EEContext& ctx);  // 0x53DD10 (register ABI: arguments in $a0.., the result in $v0)
void sub_53EA90(EEContext& ctx);  // 0x53EA90 (register ABI: arguments in $a0.., the result in $v0)
void sub_53F8B8(EEContext& ctx);  // 0x53F8B8 (register ABI: arguments in $a0.., the result in $v0)
void sub_53F940(EEContext& ctx);  // 0x53F940 (register ABI: arguments in $a0.., the result in $v0)
void ADXM_ExecMain(EEContext& ctx);  // 0x540EC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_541008(EEContext& ctx);  // 0x541008 (register ABI: arguments in $a0.., the result in $v0)
void cosl_1(EEContext& ctx);  // 0x541A78 (register ABI: arguments in $a0.., the result in $v0)
void coshl_1(EEContext& ctx);  // 0x541A90 (register ABI: arguments in $a0.., the result in $v0)
void hypotf_1(EEContext& ctx);  // 0x541AC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_545FC8(EEContext& ctx);  // 0x545FC8 (register ABI: arguments in $a0.., the result in $v0)
void sub_546058(EEContext& ctx);  // 0x546058 (register ABI: arguments in $a0.., the result in $v0)
void sub_5460E0(EEContext& ctx);  // 0x5460E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_5465A0(EEContext& ctx);  // 0x5465A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_5466B8(EEContext& ctx);  // 0x5466B8 (register ABI: arguments in $a0.., the result in $v0)
void sceInsockBind_2(EEContext& ctx);  // 0x548B38 (register ABI: arguments in $a0.., the result in $v0)
void sceInsockListen_2(EEContext& ctx);  // 0x549160 (register ABI: arguments in $a0.., the result in $v0)
void expl_4(EEContext& ctx);  // 0x54D148 (register ABI: arguments in $a0.., the result in $v0)
void sub_552658(EEContext& ctx);  // 0x552658 (register ABI: arguments in $a0.., the result in $v0)
void sub_552680(EEContext& ctx);  // 0x552680 (register ABI: arguments in $a0.., the result in $v0)
void dvCiGetStat(EEContext& ctx);  // 0x55A720 (register ABI: arguments in $a0.., the result in $v0)
void dvci_conv_fname(EEContext& ctx);  // 0x55A9B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_55D2A0(EEContext& ctx);  // 0x55D2A0 (register ABI: arguments in $a0.., the result in $v0)
void sub_55D3A8(EEContext& ctx);  // 0x55D3A8 (register ABI: arguments in $a0.., the result in $v0)
void sub_55D3F8(EEContext& ctx);  // 0x55D3F8 (register ABI: arguments in $a0.., the result in $v0)
void sub_55D790(EEContext& ctx);  // 0x55D790 (register ABI: arguments in $a0.., the result in $v0)
void sub_55D7C0(EEContext& ctx);  // 0x55D7C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_560DB8(EEContext& ctx);  // 0x560DB8 (register ABI: arguments in $a0.., the result in $v0)
void sub_564FE8(EEContext& ctx);  // 0x564FE8 (register ABI: arguments in $a0.., the result in $v0)
void sub_57AC68(EEContext& ctx);  // 0x57AC68 (register ABI: arguments in $a0.., the result in $v0)
void sub_57AE90(EEContext& ctx);  // 0x57AE90 (register ABI: arguments in $a0.., the result in $v0)
void sub_57C730(EEContext& ctx);  // 0x57C730 (register ABI: arguments in $a0.., the result in $v0)
void sub_57DB58(EEContext& ctx);  // 0x57DB58 (register ABI: arguments in $a0.., the result in $v0)
void my_malloc_0(EEContext& ctx);  // 0x581070 (register ABI: arguments in $a0.., the result in $v0)
void sub_588F48(EEContext& ctx);  // 0x588F48 (register ABI: arguments in $a0.., the result in $v0)
void sub_5895F0(EEContext& ctx);  // 0x5895F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_589CB0(EEContext& ctx);  // 0x589CB0 (register ABI: arguments in $a0.., the result in $v0)
void sub_589CD0(EEContext& ctx);  // 0x589CD0 (register ABI: arguments in $a0.., the result in $v0)
void sub_589D80(EEContext& ctx);  // 0x589D80 (register ABI: arguments in $a0.., the result in $v0)
void sub_589F38(EEContext& ctx);  // 0x589F38 (register ABI: arguments in $a0.., the result in $v0)
void sub_5944A8(EEContext& ctx);  // 0x5944A8 (register ABI: arguments in $a0.., the result in $v0)
void sub_5946A8(EEContext& ctx);  // 0x5946A8 (register ABI: arguments in $a0.., the result in $v0)
void sub_5947A8(EEContext& ctx);  // 0x5947A8 (register ABI: arguments in $a0.., the result in $v0)
void sub_595BC0(EEContext& ctx);  // 0x595BC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_597368(EEContext& ctx);  // 0x597368 (register ABI: arguments in $a0.., the result in $v0)
void sceInsockGetErrnoMode_1(EEContext& ctx);  // 0x597438 (register ABI: arguments in $a0.., the result in $v0)
void sub_5990C0(EEContext& ctx);  // 0x5990C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_5A1A30(EEContext& ctx);  // 0x5A1A30 (register ABI: arguments in $a0.., the result in $v0)

}  // namespace p3fes::game
