// Phase 5 slice libs14 (game/src/cri/libs14.cpp): CRI PS2RNA, SJX / DTX glue, PFS-on-CVFS, ROFS and Sofdec / SFX
// helpers. The register-ABI bodies (arguments in $a0.., the result in $v0) and the RofsHandle offsets they use.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace libs14::rofs_hn {
// RofsHandle (symbols/types/file_io.h, 60 bytes; tools/ours/types/deltas/libs14.json). +44 is the sector count the
// image read accepted (RFHN_ReqRdG stores the read's result there; rfmai_updateHnStat compares the transferred bytes
// with it * 2048).
constexpr s32 kRofs = 8;         // the ROFS work area (g_rofs_work)
constexpr s32 kStartLba = 16;    // file start sector
constexpr s32 kPosSct = 20;      // current position (sectors)
constexpr s32 kSizeSct = 24;     // file size (sectors)
constexpr s32 kVol = 28;         // RofsVolume*
constexpr s32 kReqSct = 32;      // sectors requested
constexpr s32 kRdSct = 36;       // sectors transferred
constexpr s32 kRdRemBytes = 40;  // bytes of a partial sector
constexpr s32 kRdAccepted = 44;  // sectors the image read accepted
constexpr s32 kBuf = 48;         // destination buffer
constexpr s32 kActive = 52;      // s16: 1 = in use
constexpr s32 kReqState = 54;    // s16: 1 = request pending, 2 = stopped
constexpr s32 kStat = 56;        // s16: 0 idle, 1 complete, 2 busy, 3 error
constexpr s32 kErr = 58;         // s16: ROFS error code
}  // namespace libs14::rofs_hn

void sub_53ED00(EEContext& ctx);  // 0x53ED00 (register ABI: arguments in $a0.., the result in $v0)
void sub_53F268(EEContext& ctx);  // 0x53F268 (register ABI: arguments in $a0.., the result in $v0)
void sub_53F298(EEContext& ctx);  // 0x53F298 (register ABI: arguments in $a0.., the result in $v0)
void PS2RNA_InitIopSnd(EEContext& ctx);  // 0x560298 (register ABI: arguments in $a0.., the result in $v0)
void PS2RNA_Create(EEContext& ctx);  // 0x560758 (register ABI: arguments in $a0.., the result in $v0)
void sub_560AF8(EEContext& ctx);  // 0x560AF8 (register ABI: arguments in $a0.., the result in $v0)
void sub_560C88(EEContext& ctx);  // 0x560C88 (register ABI: arguments in $a0.., the result in $v0)
void sub_560D20(EEContext& ctx);  // 0x560D20 (register ABI: arguments in $a0.., the result in $v0)
void sub_560EB0(EEContext& ctx);  // 0x560EB0 (register ABI: arguments in $a0.., the result in $v0)
void sub_560F18(EEContext& ctx);  // 0x560F18 (register ABI: arguments in $a0.., the result in $v0)
void sub_560F78(EEContext& ctx);  // 0x560F78 (register ABI: arguments in $a0.., the result in $v0)
void PS2RNA_ExecServer(EEContext& ctx);  // 0x561138 (register ABI: arguments in $a0.., the result in $v0)
void sub_561258(EEContext& ctx);  // 0x561258 (register ABI: arguments in $a0.., the result in $v0)
void sub_561390(EEContext& ctx);  // 0x561390 (register ABI: arguments in $a0.., the result in $v0)
void sub_561728(EEContext& ctx);  // 0x561728 (register ABI: arguments in $a0.., the result in $v0)
void sub_561740(EEContext& ctx);  // 0x561740 (register ABI: arguments in $a0.., the result in $v0)
void sub_563D20(EEContext& ctx);  // 0x563D20 (register ABI: arguments in $a0.., the result in $v0)
void sub_563E68(EEContext& ctx);  // 0x563E68 (register ABI: arguments in $a0.., the result in $v0)
void sub_563FE0(EEContext& ctx);  // 0x563FE0 (register ABI: arguments in $a0.., the result in $v0)
void sub_564218(EEContext& ctx);  // 0x564218 (register ABI: arguments in $a0.., the result in $v0)
void sub_5642D0(EEContext& ctx);  // 0x5642D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_564360(EEContext& ctx);  // 0x564360 (register ABI: arguments in $a0.., the result in $v0)
void sub_564400(EEContext& ctx);  // 0x564400 (register ABI: arguments in $a0.., the result in $v0)
void sub_564510(EEContext& ctx);  // 0x564510 (register ABI: arguments in $a0.., the result in $v0)
void sub_564738(EEContext& ctx);  // 0x564738 (register ABI: arguments in $a0.., the result in $v0)
void pfsCvfsSeek(EEContext& ctx);  // 0x565730 (register ABI: arguments in $a0.., the result in $v0)
void pfsCvfsReqRd(EEContext& ctx);  // 0x5657A0 (register ABI: arguments in $a0.., the result in $v0)
void pfsCvfsGetStat(EEContext& ctx);  // 0x5657D0 (register ABI: arguments in $a0.., the result in $v0)
void pfsCvfsGetSctLen(EEContext& ctx);  // 0x565820 (register ABI: arguments in $a0.., the result in $v0)
void pfsCvfsGetNumTr(EEContext& ctx);  // 0x565838 (register ABI: arguments in $a0.., the result in $v0)
void coshl_8(EEContext& ctx);  // 0x565850 (register ABI: arguments in $a0.., the result in $v0)
void pfsCvfsExecServer(EEContext& ctx);  // 0x565888 (register ABI: arguments in $a0.., the result in $v0)
void sub_565BC0(EEContext& ctx);  // 0x565BC0 (register ABI: arguments in $a0.., the result in $v0)
void RFHN_ReqRdG(EEContext& ctx);  // 0x565E10 (register ABI: arguments in $a0.., the result in $v0)
void RFHN_StopTrG(EEContext& ctx);  // 0x566180 (register ABI: arguments in $a0.., the result in $v0)
void RFIF_InitOvl(EEContext& ctx);  // 0x5662F0 (register ABI: arguments in $a0.., the result in $v0)
void ROFS_AddVolume(EEContext& ctx);  // 0x5663D8 (register ABI: arguments in $a0.., the result in $v0)
void sub_5664F8(EEContext& ctx);  // 0x5664F8 (register ABI: arguments in $a0.., the result in $v0)
void ROFS_Open(EEContext& ctx);  // 0x5665D0 (register ABI: arguments in $a0.., the result in $v0)
void ROFS_Close(EEContext& ctx);  // 0x5666E0 (register ABI: arguments in $a0.., the result in $v0)
void ROFS_ReqRd(EEContext& ctx);  // 0x566708 (register ABI: arguments in $a0.., the result in $v0)
void ROFS_ExecServer(EEContext& ctx);  // 0x566778 (register ABI: arguments in $a0.., the result in $v0)
void ROFS_GetStat(EEContext& ctx);  // 0x5667A8 (register ABI: arguments in $a0.., the result in $v0)
void ROFS_GetFileSiz(EEContext& ctx);  // 0x5667D0 (register ABI: arguments in $a0.., the result in $v0)
void ROFS_GetVolumeInf(EEContext& ctx);  // 0x5669D8 (register ABI: arguments in $a0.., the result in $v0)
void ROFS_SetDir(EEContext& ctx);  // 0x566B08 (register ABI: arguments in $a0.., the result in $v0)
void rfmai_isDvdRomAccess(EEContext& ctx);  // 0x567478 (register ABI: arguments in $a0.., the result in $v0)
void sceLibgcc32GetErxEntries_11(EEContext& ctx);  // 0x567810 (register ABI: arguments in $a0.., the result in $v0)
void ROFS_Init(EEContext& ctx);  // 0x567820 (register ABI: arguments in $a0.., the result in $v0)
void RFMAI_InitG(EEContext& ctx);  // 0x567858 (register ABI: arguments in $a0.., the result in $v0)
void sub_567BE0(EEContext& ctx);  // 0x567BE0 (register ABI: arguments in $a0.., the result in $v0)
void rfmai_updateHnStat(EEContext& ctx);  // 0x568710 (register ABI: arguments in $a0.., the result in $v0)
void sub_568AC0(EEContext& ctx);  // 0x568AC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_568B80(EEContext& ctx);  // 0x568B80 (register ABI: arguments in $a0.., the result in $v0)
void RFMAI_ReadWG(EEContext& ctx);  // 0x569538 (register ABI: arguments in $a0.., the result in $v0)
void dcfInit(EEContext& ctx);  // 0x56A530 (register ABI: arguments in $a0.., the result in $v0)
void dcfSeek(EEContext& ctx);  // 0x56A540 (register ABI: arguments in $a0.., the result in $v0)
void dcfReqRd(EEContext& ctx);  // 0x56A600 (register ABI: arguments in $a0.., the result in $v0)
void dcfExecServer(EEContext& ctx);  // 0x56A698 (register ABI: arguments in $a0.., the result in $v0)
void dcfGetStat(EEContext& ctx);  // 0x56A6D0 (register ABI: arguments in $a0.., the result in $v0)
void dcfGetSctLen(EEContext& ctx);  // 0x56A730 (register ABI: arguments in $a0.., the result in $v0)
void dcfGetNumTr(EEContext& ctx);  // 0x56A790 (register ABI: arguments in $a0.., the result in $v0)
void sub_56A7F0(EEContext& ctx);  // 0x56A7F0 (register ABI: arguments in $a0.., the result in $v0)
void dcfReqRdBlk(EEContext& ctx);  // 0x56A860 (register ABI: arguments in $a0.., the result in $v0)
void dcfReqRdCda(EEContext& ctx);  // 0x56AA98 (register ABI: arguments in $a0.., the result in $v0)
void rfpfs_waitRdComplete(EEContext& ctx);  // 0x56AC28 (register ABI: arguments in $a0.., the result in $v0)
void rfpfs_parentSeek(EEContext& ctx);  // 0x56ACB8 (register ABI: arguments in $a0.., the result in $v0)
void sceLibgcc32GetErxEntries_12(EEContext& ctx);  // 0x56AD38 (register ABI: arguments in $a0.., the result in $v0)
void sceLibgcc32GetErxEntries_13(EEContext& ctx);  // 0x56C8B8 (register ABI: arguments in $a0.., the result in $v0)
void sub_56DDE0(EEContext& ctx);  // 0x56DDE0 (register ABI: arguments in $a0.., the result in $v0)
void sub_570248(EEContext& ctx);  // 0x570248 (register ABI: arguments in $a0.., the result in $v0)
void sub_5703B8(EEContext& ctx);  // 0x5703B8 (register ABI: arguments in $a0.., the result in $v0)
void sub_593140(EEContext& ctx);  // 0x593140 (register ABI: arguments in $a0.., the result in $v0)
void sub_593408(EEContext& ctx);  // 0x593408 (register ABI: arguments in $a0.., the result in $v0)
void sub_595868(EEContext& ctx);  // 0x595868 (register ABI: arguments in $a0.., the result in $v0)
void sub_5959E0(EEContext& ctx);  // 0x5959E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_596760(EEContext& ctx);  // 0x596760 (register ABI: arguments in $a0.., the result in $v0)
void sub_596B68(EEContext& ctx);  // 0x596B68 (register ABI: arguments in $a0.., the result in $v0)
void sub_597878(EEContext& ctx);  // 0x597878 (register ABI: arguments in $a0.., the result in $v0)
void sub_5978E8(EEContext& ctx);  // 0x5978E8 (register ABI: arguments in $a0.., the result in $v0)
void sub_597A18(EEContext& ctx);  // 0x597A18 (register ABI: arguments in $a0.., the result in $v0)
void sub_5985F8(EEContext& ctx);  // 0x5985F8 (register ABI: arguments in $a0.., the result in $v0)
void sub_598980(EEContext& ctx);  // 0x598980 (register ABI: arguments in $a0.., the result in $v0)
void sub_599020(EEContext& ctx);  // 0x599020 (register ABI: arguments in $a0.., the result in $v0)
void sub_59A298(EEContext& ctx);  // 0x59A298 (register ABI: arguments in $a0.., the result in $v0)
void sub_59A600(EEContext& ctx);  // 0x59A600 (register ABI: arguments in $a0.., the result in $v0)
void sub_59AD40(EEContext& ctx);  // 0x59AD40 (register ABI: arguments in $a0.., the result in $v0)
void sub_59EC08(EEContext& ctx);  // 0x59EC08 (register ABI: arguments in $a0.., the result in $v0)
void sub_59EE18(EEContext& ctx);  // 0x59EE18 (register ABI: arguments in $a0.., the result in $v0)
void sub_59F320(EEContext& ctx);  // 0x59F320 (register ABI: arguments in $a0.., the result in $v0)
void sub_59F3D8(EEContext& ctx);  // 0x59F3D8 (register ABI: arguments in $a0.., the result in $v0)
void sub_59F8F8(EEContext& ctx);  // 0x59F8F8 (register ABI: arguments in $a0.., the result in $v0)
void sub_59F968(EEContext& ctx);  // 0x59F968 (register ABI: arguments in $a0.., the result in $v0)
void WTLS_get_table_2(EEContext& ctx);  // 0x59FD60 (register ABI: arguments in $a0.., the result in $v0)
void sub_59FE50(EEContext& ctx);  // 0x59FE50 (register ABI: arguments in $a0.., the result in $v0)
void sub_59FFC8(EEContext& ctx);  // 0x59FFC8 (register ABI: arguments in $a0.., the result in $v0)
void sub_5A0048(EEContext& ctx);  // 0x5A0048 (register ABI: arguments in $a0.., the result in $v0)
void sub_5A04F0(EEContext& ctx);  // 0x5A04F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_5A0BB0(EEContext& ctx);  // 0x5A0BB0 (register ABI: arguments in $a0.., the result in $v0)
void sub_5A10E8(EEContext& ctx);  // 0x5A10E8 (register ABI: arguments in $a0.., the result in $v0)

}  // namespace p3fes::game
