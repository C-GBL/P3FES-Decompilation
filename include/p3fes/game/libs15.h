// Slice libs15 (Phase 5): 100 CRI middleware functions, hand-decompiled from the p3fes_handgen bodies
// (game/src/cri/libs15.cpp): ADXT loop-play entry points and the ADXM server threads, the PS2RNA IOP command
// wrappers, the ROFS / PFS front ends (rofs_if.c, rofs_pfs.c), the MPEG-2 video header parsers of CRI Sofdec
// (sequence, GOP, picture, extension, user data), MWPLY play-list entries, the WTLS hooks and the ADX stream input steps.
// Register-ABI bodies: arguments in $a0.., the result in $v0. Names are symbols/ names; proposals are in comments and
// symbols/deltas/libs15.sym.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

// Field offsets the bodies use, from the instructions (the callers' loads / stores and the error strings).
namespace l15 {
namespace adxt {                         // the ADXT handle
constexpr s32 kStat = 1;                 // s8: the handle's status byte (0 = stopped)
constexpr s32 kStm = 148;                // the handle's stream / loop-list object (sub_55D668, sub_55D7C0, ...)
}  // namespace adxt
namespace rofs_if {                      // slots of the ROFS volume interface table *0x7B26F8 (rofs_if.c)
constexpr s32 kDelVolume = 28;
constexpr s32 kGetFileSiz = 52;
constexpr s32 kLoadDir = 60;
constexpr s32 kIsExistFile = 72;
constexpr s32 kGetNumFiles = 76;
constexpr s32 kGetDirInf = 80;
constexpr s32 kGetFileSiz64 = 88;
}  // namespace rofs_if
namespace pfs {                          // slots of the PFS device table g_rofs_pfs_tbl (rofs_pfs.c)
constexpr s32 kTell = 28;
constexpr s32 kStopTr = 40;
}  // namespace pfs
namespace m2v {                          // the MPEG-2 video parser's work (sub_570030's callees)
constexpr s32 kDecMode = 56;             // s32: 1 / 2 / 3, chosen by sub_5702F8
constexpr s32 kMode1 = 72;               // s32: 1 makes sub_5702F8 choose mode 1
constexpr s32 kIntraDcPrec = 276;        // s32: intra_dc_precision 0..3 (8..11 bits)
constexpr s32 kPicStruct = 280;          // s32: picture_structure (1 top, 2 bottom, 3 frame)
constexpr s32 kDcReset = 800;            // s32: the DC predictor reset value 128 << precision
constexpr s32 kDcMult = 816;             // s32: the DC multiplier 8 >> precision
constexpr s32 kHdrKind = 1508;           // s32: the last header parsed (1 sequence, 2 GOP, 3 picture): user-data routing
}  // namespace m2v
namespace mwply {                        // the MWPLY (Sofdec player) handle
constexpr s32 kList = 72;                // the play-list object (sub_55D428, sub_55D7C0, ...)
constexpr s32 kSeekReq = 380;            // s32: nonzero = a seek is pending (sub_583848)
constexpr s32 kAfs = 420;                // the AFS partition table sub_53DD10 resolves entries in
}  // namespace mwply
namespace adxs {                         // the ADX stream input object
constexpr s32 kWork = 8196;              // pointer to the stream work; its word 0 is the decoder handle
constexpr s32 kCbRec = 8468;             // pointer to the callback record (+20: the data callback)
constexpr s32 kBlocks = 56;              // s32 in the work: the decoded block count (32 per block row)
constexpr s32 kStep = 60;                // in the work: the next input step (sub_586B58 / sub_586F20)
}  // namespace adxs
}  // namespace l15

void sub_53F2D8(EEContext& ctx);  // 0x53F2D8 (register ABI: arguments in $a0.., the result in $v0)
void sub_53F458(EEContext& ctx);  // 0x53F458 (register ABI: arguments in $a0.., the result in $v0)
void sub_53F548(EEContext& ctx);  // 0x53F548 (register ABI: arguments in $a0.., the result in $v0)
void sub_53F5B0(EEContext& ctx);  // 0x53F5B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_53F768(EEContext& ctx);  // 0x53F768 (register ABI: arguments in $a0.., the result in $v0)
void sub_53FAC0(EEContext& ctx);  // 0x53FAC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_53FAE8(EEContext& ctx);  // 0x53FAE8 (register ABI: arguments in $a0.., the result in $v0)
void adxm_safe_proc(EEContext& ctx);  // 0x53FB00 (register ABI: arguments in $a0.., the result in $v0)
void sub_53FB58(EEContext& ctx);  // 0x53FB58 (register ABI: arguments in $a0.., the result in $v0)
void sub_53FF20(EEContext& ctx);  // 0x53FF20 (register ABI: arguments in $a0.., the result in $v0)
void sub_560240(EEContext& ctx);  // 0x560240 (register ABI: arguments in $a0.., the result in $v0)
void sub_560378(EEContext& ctx);  // 0x560378 (register ABI: arguments in $a0.., the result in $v0)
void sub_5603D8(EEContext& ctx);  // 0x5603D8 (register ABI: arguments in $a0.., the result in $v0)
void sub_560448(EEContext& ctx);  // 0x560448 (register ABI: arguments in $a0.., the result in $v0)
void PS2RNA_StartPcmTrans(EEContext& ctx);  // 0x560558 (register ABI: arguments in $a0.., the result in $v0)
void PS2RNA_StopPcmTrans(EEContext& ctx);  // 0x5605E8 (register ABI: arguments in $a0.., the result in $v0)
void sub_560BE0(EEContext& ctx);  // 0x560BE0 (register ABI: arguments in $a0.., the result in $v0)
void sub_560C28(EEContext& ctx);  // 0x560C28 (register ABI: arguments in $a0.., the result in $v0)
void sub_5611E0(EEContext& ctx);  // 0x5611E0 (register ABI: arguments in $a0.., the result in $v0)
void sub_5615B0(EEContext& ctx);  // 0x5615B0 (register ABI: arguments in $a0.., the result in $v0)
void sub_561640(EEContext& ctx);  // 0x561640 (register ABI: arguments in $a0.., the result in $v0)
void sub_561688(EEContext& ctx);  // 0x561688 (register ABI: arguments in $a0.., the result in $v0)
void sub_5616C8(EEContext& ctx);  // 0x5616C8 (register ABI: arguments in $a0.., the result in $v0)
void sub_563E30(EEContext& ctx);  // 0x563E30 (register ABI: arguments in $a0.., the result in $v0)
void sub_564038(EEContext& ctx);  // 0x564038 (register ABI: arguments in $a0.., the result in $v0)
void sub_564320(EEContext& ctx);  // 0x564320 (register ABI: arguments in $a0.., the result in $v0)
void sub_564830(EEContext& ctx);  // 0x564830 (register ABI: arguments in $a0.., the result in $v0)
void pfsCvfsStopTr(EEContext& ctx);  // 0x5657B8 (register ABI: arguments in $a0.., the result in $v0)
void ROFS_DelVolume(EEContext& ctx);  // 0x566488 (register ABI: arguments in $a0.., the result in $v0)
void ROFS_StopTr(EEContext& ctx);  // 0x566750 (register ABI: arguments in $a0.., the result in $v0)
void sub_566848(EEContext& ctx);  // 0x566848 (register ABI: arguments in $a0.., the result in $v0)
void sub_5668B8(EEContext& ctx);  // 0x5668B8 (register ABI: arguments in $a0.., the result in $v0)
void sub_566938(EEContext& ctx);  // 0x566938 (register ABI: arguments in $a0.., the result in $v0)
void ROFS_LoadDir(EEContext& ctx);  // 0x566A58 (register ABI: arguments in $a0.., the result in $v0)
void sub_566C20(EEContext& ctx);  // 0x566C20 (register ABI: arguments in $a0.., the result in $v0)
void sub_566CB8(EEContext& ctx);  // 0x566CB8 (register ABI: arguments in $a0.., the result in $v0)
void sub_566D28(EEContext& ctx);  // 0x566D28 (register ABI: arguments in $a0.., the result in $v0)
void sub_56A538(EEContext& ctx);  // 0x56A538 (register ABI: arguments in $a0.., the result in $v0)
void dcfTell(EEContext& ctx);  // 0x56A5A0 (register ABI: arguments in $a0.., the result in $v0)
void dcfStopTr(EEContext& ctx);  // 0x56A660 (register ABI: arguments in $a0.., the result in $v0)
void dcfReadBlk(EEContext& ctx);  // 0x56A9E0 (register ABI: arguments in $a0.., the result in $v0)
void dcfReadCda(EEContext& ctx);  // 0x56AAC0 (register ABI: arguments in $a0.., the result in $v0)
void sub_56CA60(EEContext& ctx);  // 0x56CA60 (register ABI: arguments in $a0.., the result in $v0)
void sub_56CA80(EEContext& ctx);  // 0x56CA80 (register ABI: arguments in $a0.., the result in $v0)
void sub_56CA98(EEContext& ctx);  // 0x56CA98 (register ABI: arguments in $a0.., the result in $v0)
void sub_570240(EEContext& ctx);  // 0x570240 (register ABI: arguments in $a0.., the result in $v0)
void sub_5702F8(EEContext& ctx);  // 0x5702F8 (register ABI: arguments in $a0.., the result in $v0)
void sub_570348(EEContext& ctx);  // 0x570348 (register ABI: arguments in $a0.., the result in $v0)
void sub_5703C0(EEContext& ctx);  // 0x5703C0 (register ABI: arguments in $a0.., the result in $v0)
void sub_570B98(EEContext& ctx);  // 0x570B98 (register ABI: arguments in $a0.., the result in $v0)
void sub_570CB8(EEContext& ctx);  // 0x570CB8 (register ABI: arguments in $a0.., the result in $v0)
void sub_570ED0(EEContext& ctx);  // 0x570ED0 (register ABI: arguments in $a0.., the result in $v0)
void sub_571048(EEContext& ctx);  // 0x571048 (register ABI: arguments in $a0.., the result in $v0)
void sub_571088(EEContext& ctx);  // 0x571088 (register ABI: arguments in $a0.., the result in $v0)
void sub_574068(EEContext& ctx);  // 0x574068 (register ABI: arguments in $a0.., the result in $v0)
void sub_5745D0(EEContext& ctx);  // 0x5745D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_578378(EEContext& ctx);  // 0x578378 (register ABI: arguments in $a0.., the result in $v0)
void sub_578820(EEContext& ctx);  // 0x578820 (register ABI: arguments in $a0.., the result in $v0)
void sub_582BF0(EEContext& ctx);  // 0x582BF0 (register ABI: arguments in $a0.., the result in $v0)
void sub_582C68(EEContext& ctx);  // 0x582C68 (register ABI: arguments in $a0.., the result in $v0)
void sub_582CD8(EEContext& ctx);  // 0x582CD8 (register ABI: arguments in $a0.., the result in $v0)
void sub_582D48(EEContext& ctx);  // 0x582D48 (register ABI: arguments in $a0.., the result in $v0)
void sub_583848(EEContext& ctx);  // 0x583848 (register ABI: arguments in $a0.., the result in $v0)
void _get_peer_or_sock_name_0(EEContext& ctx);  // 0x5843E8 (register ABI: arguments in $a0.., the result in $v0)
void sub_584400(EEContext& ctx);  // 0x584400 (register ABI: arguments in $a0.., the result in $v0)
void sub_584558(EEContext& ctx);  // 0x584558 (register ABI: arguments in $a0.., the result in $v0)
void sub_584748(EEContext& ctx);  // 0x584748 (register ABI: arguments in $a0.., the result in $v0)
void sub_584760(EEContext& ctx);  // 0x584760 (register ABI: arguments in $a0.., the result in $v0)
void sub_5849D0(EEContext& ctx);  // 0x5849D0 (register ABI: arguments in $a0.., the result in $v0)
void sub_584AB0(EEContext& ctx);  // 0x584AB0 (register ABI: arguments in $a0.., the result in $v0)
void sub_584B78(EEContext& ctx);  // 0x584B78 (register ABI: arguments in $a0.., the result in $v0)
void sub_584BE0(EEContext& ctx);  // 0x584BE0 (register ABI: arguments in $a0.., the result in $v0)
void sub_584E68(EEContext& ctx);  // 0x584E68 (register ABI: arguments in $a0.., the result in $v0)
void sub_584EC8(EEContext& ctx);  // 0x584EC8 (register ABI: arguments in $a0.., the result in $v0)
void sub_585250(EEContext& ctx);  // 0x585250 (register ABI: arguments in $a0.., the result in $v0)
void sub_585340(EEContext& ctx);  // 0x585340 (register ABI: arguments in $a0.., the result in $v0)
void sub_585398(EEContext& ctx);  // 0x585398 (register ABI: arguments in $a0.., the result in $v0)
void sub_5853F0(EEContext& ctx);  // 0x5853F0 (register ABI: arguments in $a0.., the result in $v0)
void sub_585440(EEContext& ctx);  // 0x585440 (register ABI: arguments in $a0.., the result in $v0)
void sinl_11(EEContext& ctx);  // 0x585658 (register ABI: arguments in $a0.., the result in $v0)
void sub_586110(EEContext& ctx);  // 0x586110 (register ABI: arguments in $a0.., the result in $v0)
void sub_586300(EEContext& ctx);  // 0x586300 (register ABI: arguments in $a0.., the result in $v0)
void sub_586308(EEContext& ctx);  // 0x586308 (register ABI: arguments in $a0.., the result in $v0)
void sub_586450(EEContext& ctx);  // 0x586450 (register ABI: arguments in $a0.., the result in $v0)
void sub_586468(EEContext& ctx);  // 0x586468 (register ABI: arguments in $a0.., the result in $v0)
void sub_586628(EEContext& ctx);  // 0x586628 (register ABI: arguments in $a0.., the result in $v0)
void sub_5866C8(EEContext& ctx);  // 0x5866C8 (register ABI: arguments in $a0.., the result in $v0)
void sub_5866E8(EEContext& ctx);  // 0x5866E8 (register ABI: arguments in $a0.., the result in $v0)
void sub_586708(EEContext& ctx);  // 0x586708 (register ABI: arguments in $a0.., the result in $v0)
void sub_586728(EEContext& ctx);  // 0x586728 (register ABI: arguments in $a0.., the result in $v0)
void R_LOCK_DEF_w_lock_4(EEContext& ctx);  // 0x586748 (register ABI: arguments in $a0.., the result in $v0)
void sub_586C10(EEContext& ctx);  // 0x586C10 (register ABI: arguments in $a0.., the result in $v0)
void sub_586E78(EEContext& ctx);  // 0x586E78 (register ABI: arguments in $a0.., the result in $v0)
void sub_586F00(EEContext& ctx);  // 0x586F00 (register ABI: arguments in $a0.., the result in $v0)
void sub_587100(EEContext& ctx);  // 0x587100 (register ABI: arguments in $a0.., the result in $v0)
void sub_587FD8(EEContext& ctx);  // 0x587FD8 (register ABI: arguments in $a0.., the result in $v0)
void sub_588360(EEContext& ctx);  // 0x588360 (register ABI: arguments in $a0.., the result in $v0)
void sub_588568(EEContext& ctx);  // 0x588568 (register ABI: arguments in $a0.., the result in $v0)
void sub_588640(EEContext& ctx);  // 0x588640 (register ABI: arguments in $a0.., the result in $v0)
void sub_588698(EEContext& ctx);  // 0x588698 (register ABI: arguments in $a0.., the result in $v0)

}  // namespace p3fes::game
