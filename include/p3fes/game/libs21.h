// Phase 5 slice libs21: CRI middleware -- the ROFS interface front ends (rofs_if.c: each clears the last error and
// calls a slot of the installed interface 0x7B26F8, or reports -203), MPV's start-code copy, MWSFD's finish and the
// MWPLY accessors / setters of the 0x580000 band (handle check, SFD parameter / SFX / ADXT / loop-play forwards), the
// insock / WTLS globals. Register-ABI bodies started from p3fes_handgen (every statement, charge and check point is
// the generator's: game/include/p3fes/game/hg_cpu.h): arguments in $a0.., the result in $v0. Each body carries its
// role and, in brackets, a proposed name -- from the binary's own error texts ("mwPlyGetTime", "mwPlyFxSetOutZscale",
// "ROFS_GetDefVolume" ...) where it prints one, our own otherwise (ADR-0009: proposals only, in
// symbols/deltas/libs21.sym). No CRI material was opened. The player offsets come from libs5::ply; the records below
// name the rest (each equals the literal it replaces).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace libs21 {
// The ROFS interface (the function table whose address is at 0x7B26F8): the slots the front ends call.
namespace rofsif {
constexpr s32 kFinish = 16;
constexpr s32 kSetPfsFuncTbl = 20;
constexpr s32 kGetDefVolume = 36;
constexpr s32 kOpenRange = 44;
constexpr s32 kSetIsoDir = 68;
constexpr s32 kEntryErrFunc = 84;
constexpr s32 kGetScrambleInf = 92;
constexpr s32 kCancelScramble = 96;
}  // namespace rofsif
// The MWPLY handle's AddInf user buffer (beyond libs5::ply's names).
namespace ply21 {
constexpr s32 kAddInfUsrBuf = 392;   // mwPlyAttachAddInfBuf: the buffer
constexpr s32 kAddInfUsrSize = 396;  // and its size (128 KiB at least, else W2121001)
}  // namespace ply21
// The player's SFX handle (+168): the fields the mwPlyFx* setters / getters touch.
namespace sfx {
constexpr s32 kUnk16 = 16;       // cleared by mwPlyFxSetOutBufSize
constexpr s32 kOutZscale = 40;   // mwPlyFxSetOutZscale / Get
constexpr s32 kOutZoffset = 44;  // mwPlyFxSetOutZoffset / Get
}  // namespace sfx
}  // namespace libs21

void sceLibgcc32GetErxEntries_9(EEContext& ctx);  // 0x565720
void sub_565788(EEContext& ctx);  // 0x565788
void ROFS_Finish(EEContext& ctx);  // 0x566320
void ROFS_SetPfsFuncTbl(EEContext& ctx);  // 0x566368
void sub_566568(EEContext& ctx);  // 0x566568
void ROFS_OpenRange(EEContext& ctx);  // 0x566650
void sub_566B88(EEContext& ctx);  // 0x566B88
void sub_566D98(EEContext& ctx);  // 0x566D98
void sub_566E18(EEContext& ctx);  // 0x566E18
void sub_566E98(EEContext& ctx);  // 0x566E98
void sub_578268(EEContext& ctx);  // 0x578268
void sub_57FB20(EEContext& ctx);  // 0x57FB20
void __errno_12(EEContext& ctx);  // 0x580010
void sub_580020(EEContext& ctx);  // 0x580020
void sub_580048(EEContext& ctx);  // 0x580048
void sub_580068(EEContext& ctx);  // 0x580068
void sub_5800B8(EEContext& ctx);  // 0x5800B8
void sub_580170(EEContext& ctx);  // 0x580170
void sub_5801D0(EEContext& ctx);  // 0x5801D0
void sub_580200(EEContext& ctx);  // 0x580200
void sub_580258(EEContext& ctx);  // 0x580258
void sub_580498(EEContext& ctx);  // 0x580498
void sub_5806D0(EEContext& ctx);  // 0x5806D0
void sub_580878(EEContext& ctx);  // 0x580878
void sub_580B10(EEContext& ctx);  // 0x580B10
void sub_580B60(EEContext& ctx);  // 0x580B60
void WTLS_set_table_0(EEContext& ctx);  // 0x580E00
void sceInsockSetErrnoMode_0(EEContext& ctx);  // 0x581050
void sceInsockGetErrnoMode_0(EEContext& ctx);  // 0x581060
void sub_5810B8(EEContext& ctx);  // 0x5810B8
void sub_581150(EEContext& ctx);  // 0x581150
void sub_5811B0(EEContext& ctx);  // 0x5811B0
void sub_581220(EEContext& ctx);  // 0x581220
void sub_581350(EEContext& ctx);  // 0x581350
void sub_5813F8(EEContext& ctx);  // 0x5813F8
void sub_581480(EEContext& ctx);  // 0x581480
void sub_5814B8(EEContext& ctx);  // 0x5814B8
void sub_581510(EEContext& ctx);  // 0x581510
void sub_581598(EEContext& ctx);  // 0x581598
void sub_5815D0(EEContext& ctx);  // 0x5815D0
void sub_5816B8(EEContext& ctx);  // 0x5816B8
void sub_5816E8(EEContext& ctx);  // 0x5816E8
void sub_581730(EEContext& ctx);  // 0x581730
void sub_581748(EEContext& ctx);  // 0x581748
void __sceInsockHErrnoLoc_0(EEContext& ctx);  // 0x581760
void sub_581778(EEContext& ctx);  // 0x581778
void sub_5817B0(EEContext& ctx);  // 0x5817B0
void sub_5817C0(EEContext& ctx);  // 0x5817C0
void sub_5817C8(EEContext& ctx);  // 0x5817C8
void sub_5818D8(EEContext& ctx);  // 0x5818D8
void sub_581930(EEContext& ctx);  // 0x581930
void sub_581A90(EEContext& ctx);  // 0x581A90
void sub_581B38(EEContext& ctx);  // 0x581B38
void sub_581BB0(EEContext& ctx);  // 0x581BB0
void sub_581C08(EEContext& ctx);  // 0x581C08
void sceInsockSetSendTimeout_0(EEContext& ctx);  // 0x581C38
void sub_581D08(EEContext& ctx);  // 0x581D08
void sceInsockAbort_0(EEContext& ctx);  // 0x581D38
void sub_581D68(EEContext& ctx);  // 0x581D68
void sub_581DD8(EEContext& ctx);  // 0x581DD8
void sub_581E58(EEContext& ctx);  // 0x581E58
void sub_581EC8(EEContext& ctx);  // 0x581EC8
void sub_581F48(EEContext& ctx);  // 0x581F48
void sub_581F90(EEContext& ctx);  // 0x581F90
void sub_581FD0(EEContext& ctx);  // 0x581FD0
void sub_582008(EEContext& ctx);  // 0x582008
void sub_582098(EEContext& ctx);  // 0x582098
void sub_582168(EEContext& ctx);  // 0x582168
void sub_582258(EEContext& ctx);  // 0x582258
void sceInsockConnect_0(EEContext& ctx);  // 0x582350
void sub_5823A8(EEContext& ctx);  // 0x5823A8
void sub_5823D8(EEContext& ctx);  // 0x5823D8
void sub_582440(EEContext& ctx);  // 0x582440
void sub_5824B0(EEContext& ctx);  // 0x5824B0
void sub_582558(EEContext& ctx);  // 0x582558
void sub_582578(EEContext& ctx);  // 0x582578
void add_listen_0(EEContext& ctx);  // 0x582598
void sub_5825B8(EEContext& ctx);  // 0x5825B8
void sub_5825D8(EEContext& ctx);  // 0x5825D8
void sub_5825F8(EEContext& ctx);  // 0x5825F8
void sub_582640(EEContext& ctx);  // 0x582640
void sub_582688(EEContext& ctx);  // 0x582688
void sub_5826D0(EEContext& ctx);  // 0x5826D0
void sub_582718(EEContext& ctx);  // 0x582718
void sub_582730(EEContext& ctx);  // 0x582730
void sub_582770(EEContext& ctx);  // 0x582770
void sub_582830(EEContext& ctx);  // 0x582830
void sub_582D98(EEContext& ctx);  // 0x582D98
void sub_582DB0(EEContext& ctx);  // 0x582DB0
void sub_582DC8(EEContext& ctx);  // 0x582DC8
void sub_582E78(EEContext& ctx);  // 0x582E78
void sub_582F28(EEContext& ctx);  // 0x582F28
void sub_5830D0(EEContext& ctx);  // 0x5830D0
void sub_583238(EEContext& ctx);  // 0x583238
void sub_5832A8(EEContext& ctx);  // 0x5832A8
void sub_583308(EEContext& ctx);  // 0x583308
void sub_583378(EEContext& ctx);  // 0x583378
void sub_583550(EEContext& ctx);  // 0x583550
void sub_583740(EEContext& ctx);  // 0x583740
void sub_5838A8(EEContext& ctx);  // 0x5838A8

}  // namespace p3fes::game
