// Pair tests for slice libs4 (game/src/cri/libs4_*.cpp: CRI SVM's server table, ROFS's pure parts, the RSU CVM
// descrambler, the glue next to Sofdec). Every body against its recompiled body, compared by tests/game/handgen_pairs.h:
// the whole register file and cycle count at every check point and at the return / stop, all 32 MiB of RAM (the dead
// stack too), the scratchpad, the BIOS window, the bus log. Callees this test binary does not emit (the Sofdec reader's
// handle check and stream reads, the PFS lock word, the SVM / ROFS / RSU / Sofdec callbacks the snapshots hold, SVM's
// slot setter that test_libs2 stands in) are recorders without scratch clobbering (stand_ins.h); a stand-in's entry
// check point holds the call's arguments, so the pair compares the calls too. On top of the generic sweep:
//   * every function on four replay snapshots (dorm, battle x2, fusion), with the live SVM server table and callbacks,
//     the live ROFS work area and its seven file handles, and built inputs for the rest;
//   * SVM: a server table's life on a fresh machine (register, 'too many', set / overwrite, delete, the range errors and
//     their texts, execute one / a type with the results OR-ed, the 'executing' flag around each call, the counters),
//     init / finish counting, the callback setters, the test-and-set and its hook;
//   * ROFS: seek / tell / status / transfer counts on the live handles and the range rules, the error text
//     "(code)function[detail]#file:line" through an error callback, the last error, the work flags, the handle fill;
//   * the disc's CVM headers (BGM / BTL / DATA.CVM: CVMH + ZONE) parsed and checked against the bytes, a CVMF header,
//     bad magics; the ISO's primary volume descriptor and root directory record copied field by field;
//   * RSU: the three prime hashes against a host model, the fixed keys, deciphering twice restores the data, an all-zero
//     key leaves it, the argument checks;
//   * the Sofdec glue: the callback thunks, the reader record methods on built records, the CFT converter against a
//     host model, the ratio compare.
// Random draws are separate statements (MSVC and clang evaluate arguments in different orders).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/libs4.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <tuple>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_sub_564878_00564878(EEContext&);  // generated body
void fn_sub_564878_00564878__recomp(EEContext&);  // recompiled
void fn_sub_564A08_00564a08(EEContext&);  // generated body
void fn_sub_564A08_00564a08__recomp(EEContext&);  // recompiled
void fn_sub_564A80_00564a80(EEContext&);  // generated body
void fn_sub_564A80_00564a80__recomp(EEContext&);  // recompiled
void fn_sub_564A98_00564a98(EEContext&);  // generated body
void fn_sub_564A98_00564a98__recomp(EEContext&);  // recompiled
void fn_sub_564BA0_00564ba0(EEContext&);  // generated body
void fn_sub_564BA0_00564ba0__recomp(EEContext&);  // recompiled
void fn_sub_564C10_00564c10(EEContext&);  // generated body
void fn_sub_564C10_00564c10__recomp(EEContext&);  // recompiled
void fn_sub_564D20_00564d20(EEContext&);  // generated body
void fn_sub_564D20_00564d20__recomp(EEContext&);  // recompiled
void fn_sub_564DB8_00564db8(EEContext&);  // generated body
void fn_sub_564DB8_00564db8__recomp(EEContext&);  // recompiled
void fn_sub_564DD0_00564dd0(EEContext&);  // generated body
void fn_sub_564DD0_00564dd0__recomp(EEContext&);  // recompiled
void fn_sub_564E38_00564e38(EEContext&);  // generated body
void fn_sub_564E38_00564e38__recomp(EEContext&);  // recompiled
void fn_sub_564F38_00564f38(EEContext&);  // generated body
void fn_sub_564F38_00564f38__recomp(EEContext&);  // recompiled
void fn_sub_564FD0_00564fd0(EEContext&);  // generated body
void fn_sub_564FD0_00564fd0__recomp(EEContext&);  // recompiled
void fn_sub_565058_00565058(EEContext&);  // generated body
void fn_sub_565058_00565058__recomp(EEContext&);  // recompiled
void fn_sub_565158_00565158(EEContext&);  // generated body
void fn_sub_565158_00565158__recomp(EEContext&);  // recompiled
void fn_sub_5651B0_005651b0(EEContext&);  // generated body
void fn_sub_5651B0_005651b0__recomp(EEContext&);  // recompiled
void fn_sub_5651F0_005651f0(EEContext&);  // generated body
void fn_sub_5651F0_005651f0__recomp(EEContext&);  // recompiled
void fn_sub_565230_00565230(EEContext&);  // generated body
void fn_sub_565230_00565230__recomp(EEContext&);  // recompiled
void fn_sub_565248_00565248(EEContext&);  // generated body
void fn_sub_565248_00565248__recomp(EEContext&);  // recompiled
void fn_sub_565328_00565328(EEContext&);  // generated body
void fn_sub_565328_00565328__recomp(EEContext&);  // recompiled
void fn_sub_5653C0_005653c0(EEContext&);  // generated body
void fn_sub_5653C0_005653c0__recomp(EEContext&);  // recompiled
void fn_sub_5653D8_005653d8(EEContext&);  // generated body
void fn_sub_5653D8_005653d8__recomp(EEContext&);  // recompiled
void fn_sub_5653F0_005653f0(EEContext&);  // generated body
void fn_sub_5653F0_005653f0__recomp(EEContext&);  // recompiled
void fn_sub_565408_00565408(EEContext&);  // generated body
void fn_sub_565408_00565408__recomp(EEContext&);  // recompiled
void fn_SVM_ExecSvrFs_00565420(EEContext&);  // generated body
void fn_SVM_ExecSvrFs_00565420__recomp(EEContext&);  // recompiled
void fn_sub_565438_00565438(EEContext&);  // generated body
void fn_sub_565438_00565438__recomp(EEContext&);  // recompiled
void fn_sub_565450_00565450(EEContext&);  // generated body
void fn_sub_565450_00565450__recomp(EEContext&);  // recompiled
void fn_sub_565468_00565468(EEContext&);  // generated body
void fn_sub_565468_00565468__recomp(EEContext&);  // recompiled
void fn_sub_565480_00565480(EEContext&);  // generated body
void fn_sub_565480_00565480__recomp(EEContext&);  // recompiled
void fn_sub_5654A8_005654a8(EEContext&);  // generated body
void fn_sub_5654A8_005654a8__recomp(EEContext&);  // recompiled
void fn_sub_565550_00565550(EEContext&);  // generated body
void fn_sub_565550_00565550__recomp(EEContext&);  // recompiled
void fn_sub_565590_00565590(EEContext&);  // generated body
void fn_sub_565590_00565590__recomp(EEContext&);  // recompiled
void fn_sub_5655E8_005655e8(EEContext&);  // generated body
void fn_sub_5655E8_005655e8__recomp(EEContext&);  // recompiled
void fn_sub_565678_00565678(EEContext&);  // generated body
void fn_sub_565678_00565678__recomp(EEContext&);  // recompiled
void fn_sub_565690_00565690(EEContext&);  // generated body
void fn_sub_565690_00565690__recomp(EEContext&);  // recompiled
void fn_sub_5656C0_005656c0(EEContext&);  // generated body
void fn_sub_5656C0_005656c0__recomp(EEContext&);  // recompiled
void fn_sub_5656F0_005656f0(EEContext&);  // generated body
void fn_sub_5656F0_005656f0__recomp(EEContext&);  // recompiled
void fn_PFSCVFS_GetPfsTbl_005658a8(EEContext&);  // generated body
void fn_PFSCVFS_GetPfsTbl_005658a8__recomp(EEContext&);  // recompiled
void fn_rfhn_setHandle_00565970(EEContext&);  // generated body
void fn_rfhn_setHandle_00565970__recomp(EEContext&);  // recompiled
void fn_RFHN_CreateHnG_00565a20(EEContext&);  // generated body
void fn_RFHN_CreateHnG_00565a20__recomp(EEContext&);  // recompiled
void fn_RFHN_ReopenHn_00565a78(EEContext&);  // generated body
void fn_RFHN_ReopenHn_00565a78__recomp(EEContext&);  // recompiled
void fn_RFHN_CreateDirhn_00565ac0(EEContext&);  // generated body
void fn_RFHN_CreateDirhn_00565ac0__recomp(EEContext&);  // recompiled
void fn_RFHN_IsUseImgHn_00565b18(EEContext&);  // generated body
void fn_RFHN_IsUseImgHn_00565b18__recomp(EEContext&);  // recompiled
void fn_ROFS_Seek_00565c10(EEContext&);  // generated body
void fn_ROFS_Seek_00565c10__recomp(EEContext&);  // recompiled
void fn_ROFS_Tell_00565d78(EEContext&);  // generated body
void fn_ROFS_Tell_00565d78__recomp(EEContext&);  // recompiled
void fn_RFHN_GetStatG_00565fe8(EEContext&);  // generated body
void fn_RFHN_GetStatG_00565fe8__recomp(EEContext&);  // recompiled
void fn_ROFS_GetNumTr_00566050(EEContext&);  // generated body
void fn_ROFS_GetNumTr_00566050__recomp(EEContext&);  // recompiled
void fn_sub_5660F0_005660f0(EEContext&);  // generated body
void fn_sub_5660F0_005660f0__recomp(EEContext&);  // recompiled
void fn_sub_5662C8_005662c8(EEContext&);  // generated body
void fn_sub_5662C8_005662c8__recomp(EEContext&);  // recompiled
void fn_sub_5669B8_005669b8(EEContext&);  // generated body
void fn_sub_5669B8_005669b8__recomp(EEContext&);  // recompiled
void fn_rfmai_delVolume_00567430(EEContext&);  // generated body
void fn_rfmai_delVolume_00567430__recomp(EEContext&);  // recompiled
void fn_rfmai_setCvmfInfo_005675c8(EEContext&);  // generated body
void fn_rfmai_setCvmfInfo_005675c8__recomp(EEContext&);  // recompiled
void fn_sub_568A78_00568a78(EEContext&);  // generated body
void fn_sub_568A78_00568a78__recomp(EEContext&);  // recompiled
void fn_sub_569518_00569518(EEContext&);  // generated body
void fn_sub_569518_00569518__recomp(EEContext&);  // recompiled
void fn_sub_569700_00569700(EEContext&);  // generated body
void fn_sub_569700_00569700__recomp(EEContext&);  // recompiled
void fn_sub_569718_00569718(EEContext&);  // generated body
void fn_sub_569718_00569718__recomp(EEContext&);  // recompiled
void fn_sub_569730_00569730(EEContext&);  // generated body
void fn_sub_569730_00569730__recomp(EEContext&);  // recompiled
void fn_sub_569810_00569810(EEContext&);  // generated body
void fn_sub_569810_00569810__recomp(EEContext&);  // recompiled
void fn___errno_10_00569820(EEContext&);  // generated body
void fn___errno_10_00569820__recomp(EEContext&);  // recompiled
void fn_sub_569830_00569830(EEContext&);  // generated body
void fn_sub_569830_00569830__recomp(EEContext&);  // recompiled
void fn_sub_569950_00569950(EEContext&);  // generated body
void fn_sub_569950_00569950__recomp(EEContext&);  // recompiled
void fn_sub_569960_00569960(EEContext&);  // generated body
void fn_sub_569960_00569960__recomp(EEContext&);  // recompiled
void fn_sub_569AF0_00569af0(EEContext&);  // generated body
void fn_sub_569AF0_00569af0__recomp(EEContext&);  // recompiled
void fn_sub_569B60_00569b60(EEContext&);  // generated body
void fn_sub_569B60_00569b60__recomp(EEContext&);  // recompiled
void fn_rfmai_decipherSectors_00569c00(EEContext&);  // generated body
void fn_rfmai_decipherSectors_00569c00__recomp(EEContext&);  // recompiled
void fn_sub_569F40_00569f40(EEContext&);  // generated body
void fn_sub_569F40_00569f40__recomp(EEContext&);  // recompiled
void fn_sub_569F60_00569f60(EEContext&);  // generated body
void fn_sub_569F60_00569f60__recomp(EEContext&);  // recompiled
void fn_sub_56A040_0056a040(EEContext&);  // generated body
void fn_sub_56A040_0056a040__recomp(EEContext&);  // recompiled
void fn_rfmai_copyStructCdVd_0056a0a8(EEContext&);  // generated body
void fn_rfmai_copyStructCdVd_0056a0a8__recomp(EEContext&);  // recompiled
void fn_RFMAI_CopyStructCdDr_0056a348(EEContext&);  // generated body
void fn_RFMAI_CopyStructCdDr_0056a348__recomp(EEContext&);  // recompiled
void fn_RFMAI_CopyStructCdPt_0056a468(EEContext&);  // generated body
void fn_RFMAI_CopyStructCdPt_0056a468__recomp(EEContext&);  // recompiled
void fn_sub_56A4F8_0056a4f8(EEContext&);  // generated body
void fn_sub_56A4F8_0056a4f8__recomp(EEContext&);  // recompiled
void fn_RFPFS_PfsWait_0056ab78(EEContext&);  // generated body
void fn_RFPFS_PfsWait_0056ab78__recomp(EEContext&);  // recompiled
void fn_RFPFS_PfsLock_0056ab90(EEContext&);  // generated body
void fn_RFPFS_PfsLock_0056ab90__recomp(EEContext&);  // recompiled
void fn_sub_56ABE0_0056abe0(EEContext&);  // generated body
void fn_sub_56ABE0_0056abe0__recomp(EEContext&);  // recompiled
void fn_sub_56ABF8_0056abf8(EEContext&);  // generated body
void fn_sub_56ABF8_0056abf8__recomp(EEContext&);  // recompiled
void fn_sub_56AC10_0056ac10(EEContext&);  // generated body
void fn_sub_56AC10_0056ac10__recomp(EEContext&);  // recompiled
void fn_RFPFS_SetPfsTbl_0056ad28(EEContext&);  // generated body
void fn_RFPFS_SetPfsTbl_0056ad28__recomp(EEContext&);  // recompiled
void fn_cvmh_GetSize_0056ad48(EEContext&);  // generated body
void fn_cvmh_GetSize_0056ad48__recomp(EEContext&);  // recompiled
void fn_sub_56ADB8_0056adb8(EEContext&);  // generated body
void fn_sub_56ADB8_0056adb8__recomp(EEContext&);  // recompiled
void fn_sub_56ADE0_0056ade0(EEContext&);  // generated body
void fn_sub_56ADE0_0056ade0__recomp(EEContext&);  // recompiled
void fn_cvmh_AnalyMainHdrCvm_0056ae20(EEContext&);  // generated body
void fn_cvmh_AnalyMainHdrCvm_0056ae20__recomp(EEContext&);  // recompiled
void fn_cvmh_AnalyCvmHdr_0056b028(EEContext&);  // generated body
void fn_cvmh_AnalyCvmHdr_0056b028__recomp(EEContext&);  // recompiled
void fn_cvmh_GetZoneDataLoc_0056b0d0(EEContext&);  // generated body
void fn_cvmh_GetZoneDataLoc_0056b0d0__recomp(EEContext&);  // recompiled
void fn_cvmh_AnalyZoneHdr_0056b128(EEContext&);  // generated body
void fn_cvmh_AnalyZoneHdr_0056b128__recomp(EEContext&);  // recompiled
void fn_CVMH_AnalyCvmHdr_0056b240(EEContext&);  // generated body
void fn_CVMH_AnalyCvmHdr_0056b240__recomp(EEContext&);  // recompiled
void fn_CVMH_AnalyZoneHdr_0056b300(EEContext&);  // generated body
void fn_CVMH_AnalyZoneHdr_0056b300__recomp(EEContext&);  // recompiled
void fn_sub_56B3C0_0056b3c0(EEContext&);  // generated body
void fn_sub_56B3C0_0056b3c0__recomp(EEContext&);  // recompiled
void fn_sub_56B528_0056b528(EEContext&);  // generated body
void fn_sub_56B528_0056b528__recomp(EEContext&);  // recompiled
void fn_sub_56B690_0056b690(EEContext&);  // generated body
void fn_sub_56B690_0056b690__recomp(EEContext&);  // recompiled
void fn_sub_56B6E0_0056b6e0(EEContext&);  // generated body
void fn_sub_56B6E0_0056b6e0__recomp(EEContext&);  // recompiled
void fn_sub_56B918_0056b918(EEContext&);  // generated body
void fn_sub_56B918_0056b918__recomp(EEContext&);  // recompiled
void fn_sub_56C878_0056c878(EEContext&);  // generated body
void fn_sub_56C878_0056c878__recomp(EEContext&);  // recompiled
void fn_ROCI_GetInterface_0056c888(EEContext&);  // generated body
void fn_ROCI_GetInterface_0056c888__recomp(EEContext&);  // recompiled
void fn_sub_56C8E0_0056c8e0(EEContext&);  // generated body
void fn_sub_56C8E0_0056c8e0__recomp(EEContext&);  // recompiled
void fn_sub_56CA08_0056ca08(EEContext&);  // generated body
void fn_sub_56CA08_0056ca08__recomp(EEContext&);  // recompiled
void fn_sub_56CA78_0056ca78(EEContext&);  // generated body
void fn_sub_56CA78_0056ca78__recomp(EEContext&);  // recompiled
void fn_sub_56CDF0_0056cdf0(EEContext&);  // generated body
void fn_sub_56CDF0_0056cdf0__recomp(EEContext&);  // recompiled
void fn_sub_56CE10_0056ce10(EEContext&);  // generated body
void fn_sub_56CE10_0056ce10__recomp(EEContext&);  // recompiled
void fn_sub_56CE48_0056ce48(EEContext&);  // generated body
void fn_sub_56CE48_0056ce48__recomp(EEContext&);  // recompiled
void fn_sub_56CE88_0056ce88(EEContext&);  // generated body
void fn_sub_56CE88_0056ce88__recomp(EEContext&);  // recompiled
void fn_sub_56D040_0056d040(EEContext&);  // generated body
void fn_sub_56D040_0056d040__recomp(EEContext&);  // recompiled
void fn_sub_56D0D0_0056d0d0(EEContext&);  // generated body
void fn_sub_56D0D0_0056d0d0__recomp(EEContext&);  // recompiled
void fn_sub_56D108_0056d108(EEContext&);  // generated body
void fn_sub_56D108_0056d108__recomp(EEContext&);  // recompiled
void fn_sub_56D140_0056d140(EEContext&);  // generated body
void fn_sub_56D140_0056d140__recomp(EEContext&);  // recompiled
void fn_sub_56D180_0056d180(EEContext&);  // generated body
void fn_sub_56D180_0056d180__recomp(EEContext&);  // recompiled
void fn_sub_56D1E8_0056d1e8(EEContext&);  // generated body
void fn_sub_56D1E8_0056d1e8__recomp(EEContext&);  // recompiled
void fn_sub_56D248_0056d248(EEContext&);  // generated body
void fn_sub_56D248_0056d248__recomp(EEContext&);  // recompiled
void fn_sub_56D2D0_0056d2d0(EEContext&);  // generated body
void fn_sub_56D2D0_0056d2d0__recomp(EEContext&);  // recompiled
void fn_rsu_GenerateFixedKeyByCvmhdr_0056d358(EEContext&);  // generated body
void fn_rsu_GenerateFixedKeyByCvmhdr_0056d358__recomp(EEContext&);  // recompiled
void fn_sub_56D3B0_0056d3b0(EEContext&);  // generated body
void fn_sub_56D3B0_0056d3b0__recomp(EEContext&);  // recompiled
void fn_r_lock_def_free_1_0056d4a0(EEContext&);  // generated body
void fn_r_lock_def_free_1_0056d4a0__recomp(EEContext&);  // recompiled
void fn_r_lock_def_get_free_item_1_0056d4c0(EEContext&);  // generated body
void fn_r_lock_def_get_free_item_1_0056d4c0__recomp(EEContext&);  // recompiled
void fn_sub_56D508_0056d508(EEContext&);  // generated body
void fn_sub_56D508_0056d508__recomp(EEContext&);  // recompiled
void fn_rsu_Decipher_0056d6c0(EEContext&);  // generated body
void fn_rsu_Decipher_0056d6c0__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_14_0056d6d8(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_14_0056d6d8__recomp(EEContext&);  // recompiled
void fn_RSU_Init_0056d6e8(EEContext&);  // generated body
void fn_RSU_Init_0056d6e8__recomp(EEContext&);  // recompiled
void fn_sub_56D740_0056d740(EEContext&);  // generated body
void fn_sub_56D740_0056d740__recomp(EEContext&);  // recompiled
void fn_RSU_GenerateFixedKey_0056d780(EEContext&);  // generated body
void fn_RSU_GenerateFixedKey_0056d780__recomp(EEContext&);  // recompiled
void fn_sub_56D828_0056d828(EEContext&);  // generated body
void fn_sub_56D828_0056d828__recomp(EEContext&);  // recompiled
void fn_sub_56D850_0056d850(EEContext&);  // generated body
void fn_sub_56D850_0056d850__recomp(EEContext&);  // recompiled
void fn_sub_56D898_0056d898(EEContext&);  // generated body
void fn_sub_56D898_0056d898__recomp(EEContext&);  // recompiled
void fn_RSU_Decipher_0056d900(EEContext&);  // generated body
void fn_RSU_Decipher_0056d900__recomp(EEContext&);  // recompiled
void fn_sub_56D968_0056d968(EEContext&);  // generated body
void fn_sub_56D968_0056d968__recomp(EEContext&);  // recompiled
void fn_sub_56D9A8_0056d9a8(EEContext&);  // generated body
void fn_sub_56D9A8_0056d9a8__recomp(EEContext&);  // recompiled
void fn_sub_56DA10_0056da10(EEContext&);  // generated body
void fn_sub_56DA10_0056da10__recomp(EEContext&);  // recompiled
void fn_sub_56DA78_0056da78(EEContext&);  // generated body
void fn_sub_56DA78_0056da78__recomp(EEContext&);  // recompiled
void fn_sub_56DAE0_0056dae0(EEContext&);  // generated body
void fn_sub_56DAE0_0056dae0__recomp(EEContext&);  // recompiled
void fn_sub_56DB48_0056db48(EEContext&);  // generated body
void fn_sub_56DB48_0056db48__recomp(EEContext&);  // recompiled
void fn_sub_56DBB0_0056dbb0(EEContext&);  // generated body
void fn_sub_56DBB0_0056dbb0__recomp(EEContext&);  // recompiled
void fn_sub_56DC18_0056dc18(EEContext&);  // generated body
void fn_sub_56DC18_0056dc18__recomp(EEContext&);  // recompiled
void fn_sub_56DC80_0056dc80(EEContext&);  // generated body
void fn_sub_56DC80_0056dc80__recomp(EEContext&);  // recompiled
void fn_sub_56DCE8_0056dce8(EEContext&);  // generated body
void fn_sub_56DCE8_0056dce8__recomp(EEContext&);  // recompiled
void fn_atan2l_9_0056dd50(EEContext&);  // generated body
void fn_atan2l_9_0056dd50__recomp(EEContext&);  // recompiled
void fn_cosl_9_0056dd68(EEContext&);  // generated body
void fn_cosl_9_0056dd68__recomp(EEContext&);  // recompiled
void fn_coshl_9_0056dd80(EEContext&);  // generated body
void fn_coshl_9_0056dd80__recomp(EEContext&);  // recompiled
void fn_sub_56DDC8_0056ddc8(EEContext&);  // generated body
void fn_sub_56DDC8_0056ddc8__recomp(EEContext&);  // recompiled
void fn_sub_56DDF8_0056ddf8(EEContext&);  // generated body
void fn_sub_56DDF8_0056ddf8__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_15_0056dec0(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_15_0056dec0__recomp(EEContext&);  // recompiled
void fn_sub_56DED0_0056ded0(EEContext&);  // generated body
void fn_sub_56DED0_0056ded0__recomp(EEContext&);  // recompiled
void fn_logl_9_0056def8(EEContext&);  // generated body
void fn_logl_9_0056def8__recomp(EEContext&);  // recompiled
void fn___env_lock_9_0056df18(EEContext&);  // generated body
void fn___env_lock_9_0056df18__recomp(EEContext&);  // recompiled
void fn___env_unlock_8_0056df20(EEContext&);  // generated body
void fn___env_unlock_8_0056df20__recomp(EEContext&);  // recompiled
void fn_powl_9_0056df28(EEContext&);  // generated body
void fn_powl_9_0056df28__recomp(EEContext&);  // recompiled
void fn___env_lock_10_0056df30(EEContext&);  // generated body
void fn___env_lock_10_0056df30__recomp(EEContext&);  // recompiled
void fn___env_unlock_9_0056df38(EEContext&);  // generated body
void fn___env_unlock_9_0056df38__recomp(EEContext&);  // recompiled
void fn_sinl_9_0056df40(EEContext&);  // generated body
void fn_sinl_9_0056df40__recomp(EEContext&);  // recompiled
void fn_sub_56F4B8_0056f4b8(EEContext&);  // generated body
void fn_sub_56F4B8_0056f4b8__recomp(EEContext&);  // recompiled
void fn___errno_11_0056f500(EEContext&);  // generated body
void fn___errno_11_0056f500__recomp(EEContext&);  // recompiled
void fn_sub_56F510_0056f510(EEContext&);  // generated body
void fn_sub_56F510_0056f510__recomp(EEContext&);  // recompiled
void fn_sub_56F540_0056f540(EEContext&);  // generated body
void fn_sub_56F540_0056f540__recomp(EEContext&);  // recompiled
void fn_sub_56F570_0056f570(EEContext&);  // generated body
void fn_sub_56F570_0056f570__recomp(EEContext&);  // recompiled
void fn_sub_56F598_0056f598(EEContext&);  // generated body
void fn_sub_56F598_0056f598__recomp(EEContext&);  // recompiled
void fn_sub_56F5C0_0056f5c0(EEContext&);  // generated body
void fn_sub_56F5C0_0056f5c0__recomp(EEContext&);  // recompiled
void fn_sub_56F5F0_0056f5f0(EEContext&);  // generated body
void fn_sub_56F5F0_0056f5f0__recomp(EEContext&);  // recompiled
void fn_sub_56F618_0056f618(EEContext&);  // generated body
void fn_sub_56F618_0056f618__recomp(EEContext&);  // recompiled
void fn_sub_56F640_0056f640(EEContext&);  // generated body
void fn_sub_56F640_0056f640__recomp(EEContext&);  // recompiled
void fn_sub_56F668_0056f668(EEContext&);  // generated body
void fn_sub_56F668_0056f668__recomp(EEContext&);  // recompiled
void fn_sub_56F690_0056f690(EEContext&);  // generated body
void fn_sub_56F690_0056f690__recomp(EEContext&);  // recompiled
void fn_sub_56F6B8_0056f6b8(EEContext&);  // generated body
void fn_sub_56F6B8_0056f6b8__recomp(EEContext&);  // recompiled
void fn_sub_56F6E0_0056f6e0(EEContext&);  // generated body
void fn_sub_56F6E0_0056f6e0__recomp(EEContext&);  // recompiled
void fn_sub_56F708_0056f708(EEContext&);  // generated body
void fn_sub_56F708_0056f708__recomp(EEContext&);  // recompiled
void fn_sub_56F730_0056f730(EEContext&);  // generated body
void fn_sub_56F730_0056f730__recomp(EEContext&);  // recompiled
void fn_sub_56F758_0056f758(EEContext&);  // generated body
void fn_sub_56F758_0056f758__recomp(EEContext&);  // recompiled
void fn_sub_56F780_0056f780(EEContext&);  // generated body
void fn_sub_56F780_0056f780__recomp(EEContext&);  // recompiled
void fn_sub_56F7B0_0056f7b0(EEContext&);  // generated body
void fn_sub_56F7B0_0056f7b0__recomp(EEContext&);  // recompiled
void fn_sub_56F7D8_0056f7d8(EEContext&);  // generated body
void fn_sub_56F7D8_0056f7d8__recomp(EEContext&);  // recompiled
void fn_sub_56F800_0056f800(EEContext&);  // generated body
void fn_sub_56F800_0056f800__recomp(EEContext&);  // recompiled
void fn_sub_56F828_0056f828(EEContext&);  // generated body
void fn_sub_56F828_0056f828__recomp(EEContext&);  // recompiled
void fn_sub_56F850_0056f850(EEContext&);  // generated body
void fn_sub_56F850_0056f850__recomp(EEContext&);  // recompiled
void fn_sub_56F888_0056f888(EEContext&);  // generated body
void fn_sub_56F888_0056f888__recomp(EEContext&);  // recompiled
void fn_sub_56F9C8_0056f9c8(EEContext&);  // generated body
void fn_sub_56F9C8_0056f9c8__recomp(EEContext&);  // recompiled
void fn_sub_56FA00_0056fa00(EEContext&);  // generated body
void fn_sub_56FA00_0056fa00__recomp(EEContext&);  // recompiled
void fn_sub_56FAB8_0056fab8(EEContext&);  // generated body
void fn_sub_56FAB8_0056fab8__recomp(EEContext&);  // recompiled
void fn_sub_56FAC0_0056fac0(EEContext&);  // generated body
void fn_sub_56FAC0_0056fac0__recomp(EEContext&);  // recompiled
void fn_sub_56FBC0_0056fbc0(EEContext&);  // generated body
void fn_sub_56FBC0_0056fbc0__recomp(EEContext&);  // recompiled
void fn_sub_56FC20_0056fc20(EEContext&);  // generated body
void fn_sub_56FC20_0056fc20__recomp(EEContext&);  // recompiled
void fn_sub_56FCB0_0056fcb0(EEContext&);  // generated body
void fn_sub_56FCB0_0056fcb0__recomp(EEContext&);  // recompiled
void fn_sub_56FD28_0056fd28(EEContext&);  // generated body
void fn_sub_56FD28_0056fd28__recomp(EEContext&);  // recompiled
void fn_sub_56FD58_0056fd58(EEContext&);  // generated body
void fn_sub_56FD58_0056fd58__recomp(EEContext&);  // recompiled
void fn_sub_56FDE0_0056fde0(EEContext&);  // generated body
void fn_sub_56FDE0_0056fde0__recomp(EEContext&);  // recompiled
void fn_sub_56FE08_0056fe08(EEContext&);  // generated body
void fn_sub_56FE08_0056fe08__recomp(EEContext&);  // recompiled
void fn_sub_56FE18_0056fe18(EEContext&);  // generated body
void fn_sub_56FE18_0056fe18__recomp(EEContext&);  // recompiled
void fn_sub_56FE40_0056fe40(EEContext&);  // generated body
void fn_sub_56FE40_0056fe40__recomp(EEContext&);  // recompiled
void fn_sub_56FEC0_0056fec0(EEContext&);  // generated body
void fn_sub_56FEC0_0056fec0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_564878", 0x564878, &recomp_gen::fn_sub_564878_00564878, &recomp_gen::fn_sub_564878_00564878__recomp},
    {"sub_564A08", 0x564A08, &recomp_gen::fn_sub_564A08_00564a08, &recomp_gen::fn_sub_564A08_00564a08__recomp},
    {"sub_564A80", 0x564A80, &recomp_gen::fn_sub_564A80_00564a80, &recomp_gen::fn_sub_564A80_00564a80__recomp},
    {"sub_564A98", 0x564A98, &recomp_gen::fn_sub_564A98_00564a98, &recomp_gen::fn_sub_564A98_00564a98__recomp},
    {"sub_564BA0", 0x564BA0, &recomp_gen::fn_sub_564BA0_00564ba0, &recomp_gen::fn_sub_564BA0_00564ba0__recomp},
    {"sub_564C10", 0x564C10, &recomp_gen::fn_sub_564C10_00564c10, &recomp_gen::fn_sub_564C10_00564c10__recomp},
    {"sub_564D20", 0x564D20, &recomp_gen::fn_sub_564D20_00564d20, &recomp_gen::fn_sub_564D20_00564d20__recomp},
    {"sub_564DB8", 0x564DB8, &recomp_gen::fn_sub_564DB8_00564db8, &recomp_gen::fn_sub_564DB8_00564db8__recomp},
    {"sub_564DD0", 0x564DD0, &recomp_gen::fn_sub_564DD0_00564dd0, &recomp_gen::fn_sub_564DD0_00564dd0__recomp},
    {"sub_564E38", 0x564E38, &recomp_gen::fn_sub_564E38_00564e38, &recomp_gen::fn_sub_564E38_00564e38__recomp},
    {"sub_564F38", 0x564F38, &recomp_gen::fn_sub_564F38_00564f38, &recomp_gen::fn_sub_564F38_00564f38__recomp},
    {"sub_564FD0", 0x564FD0, &recomp_gen::fn_sub_564FD0_00564fd0, &recomp_gen::fn_sub_564FD0_00564fd0__recomp},
    {"sub_565058", 0x565058, &recomp_gen::fn_sub_565058_00565058, &recomp_gen::fn_sub_565058_00565058__recomp},
    {"sub_565158", 0x565158, &recomp_gen::fn_sub_565158_00565158, &recomp_gen::fn_sub_565158_00565158__recomp},
    {"sub_5651B0", 0x5651B0, &recomp_gen::fn_sub_5651B0_005651b0, &recomp_gen::fn_sub_5651B0_005651b0__recomp},
    {"sub_5651F0", 0x5651F0, &recomp_gen::fn_sub_5651F0_005651f0, &recomp_gen::fn_sub_5651F0_005651f0__recomp},
    {"sub_565230", 0x565230, &recomp_gen::fn_sub_565230_00565230, &recomp_gen::fn_sub_565230_00565230__recomp},
    {"sub_565248", 0x565248, &recomp_gen::fn_sub_565248_00565248, &recomp_gen::fn_sub_565248_00565248__recomp},
    {"sub_565328", 0x565328, &recomp_gen::fn_sub_565328_00565328, &recomp_gen::fn_sub_565328_00565328__recomp},
    {"sub_5653C0", 0x5653C0, &recomp_gen::fn_sub_5653C0_005653c0, &recomp_gen::fn_sub_5653C0_005653c0__recomp},
    {"sub_5653D8", 0x5653D8, &recomp_gen::fn_sub_5653D8_005653d8, &recomp_gen::fn_sub_5653D8_005653d8__recomp},
    {"sub_5653F0", 0x5653F0, &recomp_gen::fn_sub_5653F0_005653f0, &recomp_gen::fn_sub_5653F0_005653f0__recomp},
    {"sub_565408", 0x565408, &recomp_gen::fn_sub_565408_00565408, &recomp_gen::fn_sub_565408_00565408__recomp},
    {"SVM_ExecSvrFs", 0x565420, &recomp_gen::fn_SVM_ExecSvrFs_00565420, &recomp_gen::fn_SVM_ExecSvrFs_00565420__recomp},
    {"sub_565438", 0x565438, &recomp_gen::fn_sub_565438_00565438, &recomp_gen::fn_sub_565438_00565438__recomp},
    {"sub_565450", 0x565450, &recomp_gen::fn_sub_565450_00565450, &recomp_gen::fn_sub_565450_00565450__recomp},
    {"sub_565468", 0x565468, &recomp_gen::fn_sub_565468_00565468, &recomp_gen::fn_sub_565468_00565468__recomp},
    {"sub_565480", 0x565480, &recomp_gen::fn_sub_565480_00565480, &recomp_gen::fn_sub_565480_00565480__recomp},
    {"sub_5654A8", 0x5654A8, &recomp_gen::fn_sub_5654A8_005654a8, &recomp_gen::fn_sub_5654A8_005654a8__recomp},
    {"sub_565550", 0x565550, &recomp_gen::fn_sub_565550_00565550, &recomp_gen::fn_sub_565550_00565550__recomp},
    {"sub_565590", 0x565590, &recomp_gen::fn_sub_565590_00565590, &recomp_gen::fn_sub_565590_00565590__recomp},
    {"sub_5655E8", 0x5655E8, &recomp_gen::fn_sub_5655E8_005655e8, &recomp_gen::fn_sub_5655E8_005655e8__recomp},
    {"sub_565678", 0x565678, &recomp_gen::fn_sub_565678_00565678, &recomp_gen::fn_sub_565678_00565678__recomp},
    {"sub_565690", 0x565690, &recomp_gen::fn_sub_565690_00565690, &recomp_gen::fn_sub_565690_00565690__recomp},
    {"sub_5656C0", 0x5656C0, &recomp_gen::fn_sub_5656C0_005656c0, &recomp_gen::fn_sub_5656C0_005656c0__recomp},
    {"sub_5656F0", 0x5656F0, &recomp_gen::fn_sub_5656F0_005656f0, &recomp_gen::fn_sub_5656F0_005656f0__recomp},
    {"PFSCVFS_GetPfsTbl", 0x5658A8, &recomp_gen::fn_PFSCVFS_GetPfsTbl_005658a8, &recomp_gen::fn_PFSCVFS_GetPfsTbl_005658a8__recomp},
    {"rfhn_setHandle", 0x565970, &recomp_gen::fn_rfhn_setHandle_00565970, &recomp_gen::fn_rfhn_setHandle_00565970__recomp},
    {"RFHN_CreateHnG", 0x565A20, &recomp_gen::fn_RFHN_CreateHnG_00565a20, &recomp_gen::fn_RFHN_CreateHnG_00565a20__recomp},
    {"RFHN_ReopenHn", 0x565A78, &recomp_gen::fn_RFHN_ReopenHn_00565a78, &recomp_gen::fn_RFHN_ReopenHn_00565a78__recomp},
    {"RFHN_CreateDirhn", 0x565AC0, &recomp_gen::fn_RFHN_CreateDirhn_00565ac0, &recomp_gen::fn_RFHN_CreateDirhn_00565ac0__recomp},
    {"RFHN_IsUseImgHn", 0x565B18, &recomp_gen::fn_RFHN_IsUseImgHn_00565b18, &recomp_gen::fn_RFHN_IsUseImgHn_00565b18__recomp},
    {"ROFS_Seek", 0x565C10, &recomp_gen::fn_ROFS_Seek_00565c10, &recomp_gen::fn_ROFS_Seek_00565c10__recomp},
    {"ROFS_Tell", 0x565D78, &recomp_gen::fn_ROFS_Tell_00565d78, &recomp_gen::fn_ROFS_Tell_00565d78__recomp},
    {"RFHN_GetStatG", 0x565FE8, &recomp_gen::fn_RFHN_GetStatG_00565fe8, &recomp_gen::fn_RFHN_GetStatG_00565fe8__recomp},
    {"ROFS_GetNumTr", 0x566050, &recomp_gen::fn_ROFS_GetNumTr_00566050, &recomp_gen::fn_ROFS_GetNumTr_00566050__recomp},
    {"sub_5660F0", 0x5660F0, &recomp_gen::fn_sub_5660F0_005660f0, &recomp_gen::fn_sub_5660F0_005660f0__recomp},
    {"sub_5662C8", 0x5662C8, &recomp_gen::fn_sub_5662C8_005662c8, &recomp_gen::fn_sub_5662C8_005662c8__recomp},
    {"sub_5669B8", 0x5669B8, &recomp_gen::fn_sub_5669B8_005669b8, &recomp_gen::fn_sub_5669B8_005669b8__recomp},
    {"rfmai_delVolume", 0x567430, &recomp_gen::fn_rfmai_delVolume_00567430, &recomp_gen::fn_rfmai_delVolume_00567430__recomp},
    {"rfmai_setCvmfInfo", 0x5675C8, &recomp_gen::fn_rfmai_setCvmfInfo_005675c8, &recomp_gen::fn_rfmai_setCvmfInfo_005675c8__recomp},
    {"sub_568A78", 0x568A78, &recomp_gen::fn_sub_568A78_00568a78, &recomp_gen::fn_sub_568A78_00568a78__recomp},
    {"sub_569518", 0x569518, &recomp_gen::fn_sub_569518_00569518, &recomp_gen::fn_sub_569518_00569518__recomp},
    {"sub_569700", 0x569700, &recomp_gen::fn_sub_569700_00569700, &recomp_gen::fn_sub_569700_00569700__recomp},
    {"sub_569718", 0x569718, &recomp_gen::fn_sub_569718_00569718, &recomp_gen::fn_sub_569718_00569718__recomp},
    {"sub_569730", 0x569730, &recomp_gen::fn_sub_569730_00569730, &recomp_gen::fn_sub_569730_00569730__recomp},
    {"sub_569810", 0x569810, &recomp_gen::fn_sub_569810_00569810, &recomp_gen::fn_sub_569810_00569810__recomp},
    {"__errno_10", 0x569820, &recomp_gen::fn___errno_10_00569820, &recomp_gen::fn___errno_10_00569820__recomp},
    {"sub_569830", 0x569830, &recomp_gen::fn_sub_569830_00569830, &recomp_gen::fn_sub_569830_00569830__recomp},
    {"sub_569950", 0x569950, &recomp_gen::fn_sub_569950_00569950, &recomp_gen::fn_sub_569950_00569950__recomp},
    {"sub_569960", 0x569960, &recomp_gen::fn_sub_569960_00569960, &recomp_gen::fn_sub_569960_00569960__recomp},
    {"sub_569AF0", 0x569AF0, &recomp_gen::fn_sub_569AF0_00569af0, &recomp_gen::fn_sub_569AF0_00569af0__recomp},
    {"sub_569B60", 0x569B60, &recomp_gen::fn_sub_569B60_00569b60, &recomp_gen::fn_sub_569B60_00569b60__recomp},
    {"rfmai_decipherSectors", 0x569C00, &recomp_gen::fn_rfmai_decipherSectors_00569c00, &recomp_gen::fn_rfmai_decipherSectors_00569c00__recomp},
    {"sub_569F40", 0x569F40, &recomp_gen::fn_sub_569F40_00569f40, &recomp_gen::fn_sub_569F40_00569f40__recomp},
    {"sub_569F60", 0x569F60, &recomp_gen::fn_sub_569F60_00569f60, &recomp_gen::fn_sub_569F60_00569f60__recomp},
    {"sub_56A040", 0x56A040, &recomp_gen::fn_sub_56A040_0056a040, &recomp_gen::fn_sub_56A040_0056a040__recomp},
    {"rfmai_copyStructCdVd", 0x56A0A8, &recomp_gen::fn_rfmai_copyStructCdVd_0056a0a8, &recomp_gen::fn_rfmai_copyStructCdVd_0056a0a8__recomp},
    {"RFMAI_CopyStructCdDr", 0x56A348, &recomp_gen::fn_RFMAI_CopyStructCdDr_0056a348, &recomp_gen::fn_RFMAI_CopyStructCdDr_0056a348__recomp},
    {"RFMAI_CopyStructCdPt", 0x56A468, &recomp_gen::fn_RFMAI_CopyStructCdPt_0056a468, &recomp_gen::fn_RFMAI_CopyStructCdPt_0056a468__recomp},
    {"sub_56A4F8", 0x56A4F8, &recomp_gen::fn_sub_56A4F8_0056a4f8, &recomp_gen::fn_sub_56A4F8_0056a4f8__recomp},
    {"RFPFS_PfsWait", 0x56AB78, &recomp_gen::fn_RFPFS_PfsWait_0056ab78, &recomp_gen::fn_RFPFS_PfsWait_0056ab78__recomp},
    {"RFPFS_PfsLock", 0x56AB90, &recomp_gen::fn_RFPFS_PfsLock_0056ab90, &recomp_gen::fn_RFPFS_PfsLock_0056ab90__recomp},
    {"sub_56ABE0", 0x56ABE0, &recomp_gen::fn_sub_56ABE0_0056abe0, &recomp_gen::fn_sub_56ABE0_0056abe0__recomp},
    {"sub_56ABF8", 0x56ABF8, &recomp_gen::fn_sub_56ABF8_0056abf8, &recomp_gen::fn_sub_56ABF8_0056abf8__recomp},
    {"sub_56AC10", 0x56AC10, &recomp_gen::fn_sub_56AC10_0056ac10, &recomp_gen::fn_sub_56AC10_0056ac10__recomp},
    {"RFPFS_SetPfsTbl", 0x56AD28, &recomp_gen::fn_RFPFS_SetPfsTbl_0056ad28, &recomp_gen::fn_RFPFS_SetPfsTbl_0056ad28__recomp},
    {"cvmh_GetSize", 0x56AD48, &recomp_gen::fn_cvmh_GetSize_0056ad48, &recomp_gen::fn_cvmh_GetSize_0056ad48__recomp},
    {"sub_56ADB8", 0x56ADB8, &recomp_gen::fn_sub_56ADB8_0056adb8, &recomp_gen::fn_sub_56ADB8_0056adb8__recomp},
    {"sub_56ADE0", 0x56ADE0, &recomp_gen::fn_sub_56ADE0_0056ade0, &recomp_gen::fn_sub_56ADE0_0056ade0__recomp},
    {"cvmh_AnalyMainHdrCvm", 0x56AE20, &recomp_gen::fn_cvmh_AnalyMainHdrCvm_0056ae20, &recomp_gen::fn_cvmh_AnalyMainHdrCvm_0056ae20__recomp},
    {"cvmh_AnalyCvmHdr", 0x56B028, &recomp_gen::fn_cvmh_AnalyCvmHdr_0056b028, &recomp_gen::fn_cvmh_AnalyCvmHdr_0056b028__recomp},
    {"cvmh_GetZoneDataLoc", 0x56B0D0, &recomp_gen::fn_cvmh_GetZoneDataLoc_0056b0d0, &recomp_gen::fn_cvmh_GetZoneDataLoc_0056b0d0__recomp},
    {"cvmh_AnalyZoneHdr", 0x56B128, &recomp_gen::fn_cvmh_AnalyZoneHdr_0056b128, &recomp_gen::fn_cvmh_AnalyZoneHdr_0056b128__recomp},
    {"CVMH_AnalyCvmHdr", 0x56B240, &recomp_gen::fn_CVMH_AnalyCvmHdr_0056b240, &recomp_gen::fn_CVMH_AnalyCvmHdr_0056b240__recomp},
    {"CVMH_AnalyZoneHdr", 0x56B300, &recomp_gen::fn_CVMH_AnalyZoneHdr_0056b300, &recomp_gen::fn_CVMH_AnalyZoneHdr_0056b300__recomp},
    {"sub_56B3C0", 0x56B3C0, &recomp_gen::fn_sub_56B3C0_0056b3c0, &recomp_gen::fn_sub_56B3C0_0056b3c0__recomp},
    {"sub_56B528", 0x56B528, &recomp_gen::fn_sub_56B528_0056b528, &recomp_gen::fn_sub_56B528_0056b528__recomp},
    {"sub_56B690", 0x56B690, &recomp_gen::fn_sub_56B690_0056b690, &recomp_gen::fn_sub_56B690_0056b690__recomp},
    {"sub_56B6E0", 0x56B6E0, &recomp_gen::fn_sub_56B6E0_0056b6e0, &recomp_gen::fn_sub_56B6E0_0056b6e0__recomp},
    {"sub_56B918", 0x56B918, &recomp_gen::fn_sub_56B918_0056b918, &recomp_gen::fn_sub_56B918_0056b918__recomp},
    {"sub_56C878", 0x56C878, &recomp_gen::fn_sub_56C878_0056c878, &recomp_gen::fn_sub_56C878_0056c878__recomp},
    {"ROCI_GetInterface", 0x56C888, &recomp_gen::fn_ROCI_GetInterface_0056c888, &recomp_gen::fn_ROCI_GetInterface_0056c888__recomp},
    {"sub_56C8E0", 0x56C8E0, &recomp_gen::fn_sub_56C8E0_0056c8e0, &recomp_gen::fn_sub_56C8E0_0056c8e0__recomp},
    {"sub_56CA08", 0x56CA08, &recomp_gen::fn_sub_56CA08_0056ca08, &recomp_gen::fn_sub_56CA08_0056ca08__recomp},
    {"sub_56CA78", 0x56CA78, &recomp_gen::fn_sub_56CA78_0056ca78, &recomp_gen::fn_sub_56CA78_0056ca78__recomp},
    {"sub_56CDF0", 0x56CDF0, &recomp_gen::fn_sub_56CDF0_0056cdf0, &recomp_gen::fn_sub_56CDF0_0056cdf0__recomp},
    {"sub_56CE10", 0x56CE10, &recomp_gen::fn_sub_56CE10_0056ce10, &recomp_gen::fn_sub_56CE10_0056ce10__recomp},
    {"sub_56CE48", 0x56CE48, &recomp_gen::fn_sub_56CE48_0056ce48, &recomp_gen::fn_sub_56CE48_0056ce48__recomp},
    {"sub_56CE88", 0x56CE88, &recomp_gen::fn_sub_56CE88_0056ce88, &recomp_gen::fn_sub_56CE88_0056ce88__recomp},
    {"sub_56D040", 0x56D040, &recomp_gen::fn_sub_56D040_0056d040, &recomp_gen::fn_sub_56D040_0056d040__recomp},
    {"sub_56D0D0", 0x56D0D0, &recomp_gen::fn_sub_56D0D0_0056d0d0, &recomp_gen::fn_sub_56D0D0_0056d0d0__recomp},
    {"sub_56D108", 0x56D108, &recomp_gen::fn_sub_56D108_0056d108, &recomp_gen::fn_sub_56D108_0056d108__recomp},
    {"sub_56D140", 0x56D140, &recomp_gen::fn_sub_56D140_0056d140, &recomp_gen::fn_sub_56D140_0056d140__recomp},
    {"sub_56D180", 0x56D180, &recomp_gen::fn_sub_56D180_0056d180, &recomp_gen::fn_sub_56D180_0056d180__recomp},
    {"sub_56D1E8", 0x56D1E8, &recomp_gen::fn_sub_56D1E8_0056d1e8, &recomp_gen::fn_sub_56D1E8_0056d1e8__recomp},
    {"sub_56D248", 0x56D248, &recomp_gen::fn_sub_56D248_0056d248, &recomp_gen::fn_sub_56D248_0056d248__recomp},
    {"sub_56D2D0", 0x56D2D0, &recomp_gen::fn_sub_56D2D0_0056d2d0, &recomp_gen::fn_sub_56D2D0_0056d2d0__recomp},
    {"rsu_GenerateFixedKeyByCvmhdr", 0x56D358, &recomp_gen::fn_rsu_GenerateFixedKeyByCvmhdr_0056d358, &recomp_gen::fn_rsu_GenerateFixedKeyByCvmhdr_0056d358__recomp},
    {"sub_56D3B0", 0x56D3B0, &recomp_gen::fn_sub_56D3B0_0056d3b0, &recomp_gen::fn_sub_56D3B0_0056d3b0__recomp},
    {"r_lock_def_free_1", 0x56D4A0, &recomp_gen::fn_r_lock_def_free_1_0056d4a0, &recomp_gen::fn_r_lock_def_free_1_0056d4a0__recomp},
    {"r_lock_def_get_free_item_1", 0x56D4C0, &recomp_gen::fn_r_lock_def_get_free_item_1_0056d4c0, &recomp_gen::fn_r_lock_def_get_free_item_1_0056d4c0__recomp},
    {"sub_56D508", 0x56D508, &recomp_gen::fn_sub_56D508_0056d508, &recomp_gen::fn_sub_56D508_0056d508__recomp},
    {"rsu_Decipher", 0x56D6C0, &recomp_gen::fn_rsu_Decipher_0056d6c0, &recomp_gen::fn_rsu_Decipher_0056d6c0__recomp},
    {"sceLibgcc32GetErxEntries_14", 0x56D6D8, &recomp_gen::fn_sceLibgcc32GetErxEntries_14_0056d6d8, &recomp_gen::fn_sceLibgcc32GetErxEntries_14_0056d6d8__recomp},
    {"RSU_Init", 0x56D6E8, &recomp_gen::fn_RSU_Init_0056d6e8, &recomp_gen::fn_RSU_Init_0056d6e8__recomp},
    {"sub_56D740", 0x56D740, &recomp_gen::fn_sub_56D740_0056d740, &recomp_gen::fn_sub_56D740_0056d740__recomp},
    {"RSU_GenerateFixedKey", 0x56D780, &recomp_gen::fn_RSU_GenerateFixedKey_0056d780, &recomp_gen::fn_RSU_GenerateFixedKey_0056d780__recomp},
    {"sub_56D828", 0x56D828, &recomp_gen::fn_sub_56D828_0056d828, &recomp_gen::fn_sub_56D828_0056d828__recomp},
    {"sub_56D850", 0x56D850, &recomp_gen::fn_sub_56D850_0056d850, &recomp_gen::fn_sub_56D850_0056d850__recomp},
    {"sub_56D898", 0x56D898, &recomp_gen::fn_sub_56D898_0056d898, &recomp_gen::fn_sub_56D898_0056d898__recomp},
    {"RSU_Decipher", 0x56D900, &recomp_gen::fn_RSU_Decipher_0056d900, &recomp_gen::fn_RSU_Decipher_0056d900__recomp},
    {"sub_56D968", 0x56D968, &recomp_gen::fn_sub_56D968_0056d968, &recomp_gen::fn_sub_56D968_0056d968__recomp},
    {"sub_56D9A8", 0x56D9A8, &recomp_gen::fn_sub_56D9A8_0056d9a8, &recomp_gen::fn_sub_56D9A8_0056d9a8__recomp},
    {"sub_56DA10", 0x56DA10, &recomp_gen::fn_sub_56DA10_0056da10, &recomp_gen::fn_sub_56DA10_0056da10__recomp},
    {"sub_56DA78", 0x56DA78, &recomp_gen::fn_sub_56DA78_0056da78, &recomp_gen::fn_sub_56DA78_0056da78__recomp},
    {"sub_56DAE0", 0x56DAE0, &recomp_gen::fn_sub_56DAE0_0056dae0, &recomp_gen::fn_sub_56DAE0_0056dae0__recomp},
    {"sub_56DB48", 0x56DB48, &recomp_gen::fn_sub_56DB48_0056db48, &recomp_gen::fn_sub_56DB48_0056db48__recomp},
    {"sub_56DBB0", 0x56DBB0, &recomp_gen::fn_sub_56DBB0_0056dbb0, &recomp_gen::fn_sub_56DBB0_0056dbb0__recomp},
    {"sub_56DC18", 0x56DC18, &recomp_gen::fn_sub_56DC18_0056dc18, &recomp_gen::fn_sub_56DC18_0056dc18__recomp},
    {"sub_56DC80", 0x56DC80, &recomp_gen::fn_sub_56DC80_0056dc80, &recomp_gen::fn_sub_56DC80_0056dc80__recomp},
    {"sub_56DCE8", 0x56DCE8, &recomp_gen::fn_sub_56DCE8_0056dce8, &recomp_gen::fn_sub_56DCE8_0056dce8__recomp},
    {"atan2l_9", 0x56DD50, &recomp_gen::fn_atan2l_9_0056dd50, &recomp_gen::fn_atan2l_9_0056dd50__recomp},
    {"cosl_9", 0x56DD68, &recomp_gen::fn_cosl_9_0056dd68, &recomp_gen::fn_cosl_9_0056dd68__recomp},
    {"coshl_9", 0x56DD80, &recomp_gen::fn_coshl_9_0056dd80, &recomp_gen::fn_coshl_9_0056dd80__recomp},
    {"sub_56DDC8", 0x56DDC8, &recomp_gen::fn_sub_56DDC8_0056ddc8, &recomp_gen::fn_sub_56DDC8_0056ddc8__recomp},
    {"sub_56DDF8", 0x56DDF8, &recomp_gen::fn_sub_56DDF8_0056ddf8, &recomp_gen::fn_sub_56DDF8_0056ddf8__recomp},
    {"sceLibgcc32GetErxEntries_15", 0x56DEC0, &recomp_gen::fn_sceLibgcc32GetErxEntries_15_0056dec0, &recomp_gen::fn_sceLibgcc32GetErxEntries_15_0056dec0__recomp},
    {"sub_56DED0", 0x56DED0, &recomp_gen::fn_sub_56DED0_0056ded0, &recomp_gen::fn_sub_56DED0_0056ded0__recomp},
    {"logl_9", 0x56DEF8, &recomp_gen::fn_logl_9_0056def8, &recomp_gen::fn_logl_9_0056def8__recomp},
    {"__env_lock_9", 0x56DF18, &recomp_gen::fn___env_lock_9_0056df18, &recomp_gen::fn___env_lock_9_0056df18__recomp},
    {"__env_unlock_8", 0x56DF20, &recomp_gen::fn___env_unlock_8_0056df20, &recomp_gen::fn___env_unlock_8_0056df20__recomp},
    {"powl_9", 0x56DF28, &recomp_gen::fn_powl_9_0056df28, &recomp_gen::fn_powl_9_0056df28__recomp},
    {"__env_lock_10", 0x56DF30, &recomp_gen::fn___env_lock_10_0056df30, &recomp_gen::fn___env_lock_10_0056df30__recomp},
    {"__env_unlock_9", 0x56DF38, &recomp_gen::fn___env_unlock_9_0056df38, &recomp_gen::fn___env_unlock_9_0056df38__recomp},
    {"sinl_9", 0x56DF40, &recomp_gen::fn_sinl_9_0056df40, &recomp_gen::fn_sinl_9_0056df40__recomp},
    {"sub_56F4B8", 0x56F4B8, &recomp_gen::fn_sub_56F4B8_0056f4b8, &recomp_gen::fn_sub_56F4B8_0056f4b8__recomp},
    {"__errno_11", 0x56F500, &recomp_gen::fn___errno_11_0056f500, &recomp_gen::fn___errno_11_0056f500__recomp},
    {"sub_56F510", 0x56F510, &recomp_gen::fn_sub_56F510_0056f510, &recomp_gen::fn_sub_56F510_0056f510__recomp},
    {"sub_56F540", 0x56F540, &recomp_gen::fn_sub_56F540_0056f540, &recomp_gen::fn_sub_56F540_0056f540__recomp},
    {"sub_56F570", 0x56F570, &recomp_gen::fn_sub_56F570_0056f570, &recomp_gen::fn_sub_56F570_0056f570__recomp},
    {"sub_56F598", 0x56F598, &recomp_gen::fn_sub_56F598_0056f598, &recomp_gen::fn_sub_56F598_0056f598__recomp},
    {"sub_56F5C0", 0x56F5C0, &recomp_gen::fn_sub_56F5C0_0056f5c0, &recomp_gen::fn_sub_56F5C0_0056f5c0__recomp},
    {"sub_56F5F0", 0x56F5F0, &recomp_gen::fn_sub_56F5F0_0056f5f0, &recomp_gen::fn_sub_56F5F0_0056f5f0__recomp},
    {"sub_56F618", 0x56F618, &recomp_gen::fn_sub_56F618_0056f618, &recomp_gen::fn_sub_56F618_0056f618__recomp},
    {"sub_56F640", 0x56F640, &recomp_gen::fn_sub_56F640_0056f640, &recomp_gen::fn_sub_56F640_0056f640__recomp},
    {"sub_56F668", 0x56F668, &recomp_gen::fn_sub_56F668_0056f668, &recomp_gen::fn_sub_56F668_0056f668__recomp},
    {"sub_56F690", 0x56F690, &recomp_gen::fn_sub_56F690_0056f690, &recomp_gen::fn_sub_56F690_0056f690__recomp},
    {"sub_56F6B8", 0x56F6B8, &recomp_gen::fn_sub_56F6B8_0056f6b8, &recomp_gen::fn_sub_56F6B8_0056f6b8__recomp},
    {"sub_56F6E0", 0x56F6E0, &recomp_gen::fn_sub_56F6E0_0056f6e0, &recomp_gen::fn_sub_56F6E0_0056f6e0__recomp},
    {"sub_56F708", 0x56F708, &recomp_gen::fn_sub_56F708_0056f708, &recomp_gen::fn_sub_56F708_0056f708__recomp},
    {"sub_56F730", 0x56F730, &recomp_gen::fn_sub_56F730_0056f730, &recomp_gen::fn_sub_56F730_0056f730__recomp},
    {"sub_56F758", 0x56F758, &recomp_gen::fn_sub_56F758_0056f758, &recomp_gen::fn_sub_56F758_0056f758__recomp},
    {"sub_56F780", 0x56F780, &recomp_gen::fn_sub_56F780_0056f780, &recomp_gen::fn_sub_56F780_0056f780__recomp},
    {"sub_56F7B0", 0x56F7B0, &recomp_gen::fn_sub_56F7B0_0056f7b0, &recomp_gen::fn_sub_56F7B0_0056f7b0__recomp},
    {"sub_56F7D8", 0x56F7D8, &recomp_gen::fn_sub_56F7D8_0056f7d8, &recomp_gen::fn_sub_56F7D8_0056f7d8__recomp},
    {"sub_56F800", 0x56F800, &recomp_gen::fn_sub_56F800_0056f800, &recomp_gen::fn_sub_56F800_0056f800__recomp},
    {"sub_56F828", 0x56F828, &recomp_gen::fn_sub_56F828_0056f828, &recomp_gen::fn_sub_56F828_0056f828__recomp},
    {"sub_56F850", 0x56F850, &recomp_gen::fn_sub_56F850_0056f850, &recomp_gen::fn_sub_56F850_0056f850__recomp},
    {"sub_56F888", 0x56F888, &recomp_gen::fn_sub_56F888_0056f888, &recomp_gen::fn_sub_56F888_0056f888__recomp},
    {"sub_56F9C8", 0x56F9C8, &recomp_gen::fn_sub_56F9C8_0056f9c8, &recomp_gen::fn_sub_56F9C8_0056f9c8__recomp},
    {"sub_56FA00", 0x56FA00, &recomp_gen::fn_sub_56FA00_0056fa00, &recomp_gen::fn_sub_56FA00_0056fa00__recomp},
    {"sub_56FAB8", 0x56FAB8, &recomp_gen::fn_sub_56FAB8_0056fab8, &recomp_gen::fn_sub_56FAB8_0056fab8__recomp},
    {"sub_56FAC0", 0x56FAC0, &recomp_gen::fn_sub_56FAC0_0056fac0, &recomp_gen::fn_sub_56FAC0_0056fac0__recomp},
    {"sub_56FBC0", 0x56FBC0, &recomp_gen::fn_sub_56FBC0_0056fbc0, &recomp_gen::fn_sub_56FBC0_0056fbc0__recomp},
    {"sub_56FC20", 0x56FC20, &recomp_gen::fn_sub_56FC20_0056fc20, &recomp_gen::fn_sub_56FC20_0056fc20__recomp},
    {"sub_56FCB0", 0x56FCB0, &recomp_gen::fn_sub_56FCB0_0056fcb0, &recomp_gen::fn_sub_56FCB0_0056fcb0__recomp},
    {"sub_56FD28", 0x56FD28, &recomp_gen::fn_sub_56FD28_0056fd28, &recomp_gen::fn_sub_56FD28_0056fd28__recomp},
    {"sub_56FD58", 0x56FD58, &recomp_gen::fn_sub_56FD58_0056fd58, &recomp_gen::fn_sub_56FD58_0056fd58__recomp},
    {"sub_56FDE0", 0x56FDE0, &recomp_gen::fn_sub_56FDE0_0056fde0, &recomp_gen::fn_sub_56FDE0_0056fde0__recomp},
    {"sub_56FE08", 0x56FE08, &recomp_gen::fn_sub_56FE08_0056fe08, &recomp_gen::fn_sub_56FE08_0056fe08__recomp},
    {"sub_56FE18", 0x56FE18, &recomp_gen::fn_sub_56FE18_0056fe18, &recomp_gen::fn_sub_56FE18_0056fe18__recomp},
    {"sub_56FE40", 0x56FE40, &recomp_gen::fn_sub_56FE40_0056fe40, &recomp_gen::fn_sub_56FE40_0056fe40__recomp},
    {"sub_56FEC0", 0x56FEC0, &recomp_gen::fn_sub_56FEC0_0056fec0, &recomp_gen::fn_sub_56FEC0_0056fec0__recomp},
};

using namespace p3fes::game::libs4;

const Case& by_addr(u32 addr) {
    for (const Case& c : kCases)
        if (c.addr == addr) return c;
    static const Case none{"?", 0, nullptr, nullptr};
    FAIL("no case for " << hex64(addr));
    return none;
}

// --- guest memory helpers ------------------------------------------------------------------------------------------
u8 r8(Machine& m, u32 va) { return *m.at(va); }
u16 r16(Machine& m, u32 va) { u16 v; std::memcpy(&v, m.at(va), 2); return v; }
s16 r16s(Machine& m, u32 va) { return static_cast<s16>(r16(m, va)); }
u32 r32(Machine& m, u32 va) { u32 v; std::memcpy(&v, m.at(va), 4); return v; }
s32 r32s(Machine& m, u32 va) { return static_cast<s32>(r32(m, va)); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void wstr(Machine& m, u32 va, const std::string& s) { std::memcpy(m.at(va), s.c_str(), s.size() + 1); }
std::string rstr(Machine& m, u32 va, std::size_t max = 255) {
    std::string s;
    for (u32 a = va; s.size() < max && *m.at(a); ++a) s += static_cast<char>(*m.at(a));
    return s;
}
u32 be32(const u8* p) { return (u32{p[0]} << 24) | (u32{p[1]} << 16) | (u32{p[2]} << 8) | p[3]; }
s32 sv(u64 v) { return static_cast<s32>(static_cast<u32>(v)); }
u32 uv(u64 v) { return static_cast<u32>(v); }
u64 sx64(s32 v) { return static_cast<u64>(static_cast<s64>(v)); }

// --- the stand-ins ---------------------------------------------------------------------------------------------------
// Callees no test emits, as recorders (no scratch clobbering: one set serves both bodies of a pair alike).
constexpr u32 kLockWord = 0x5584F0u;      // __errno_4: the PFS lock word rofs_PfsLock spins on (0: free)
constexpr u32 kSfdCheck = 0x5753E8u;      // the Sofdec reader's handle check (0: valid)
constexpr u32 kSfdTail = 0x56F978u;       // the reader methods' shared error tail (inside sub_56F8F8)
constexpr u32 kSvmSetIdPub = 0x564FE8u;   // SVM_SetCbSvrId (locked), test_libs2's stand-in
const u32 kDrivers[] = {kLockWord, kSfdCheck, kSfdTail, kSvmSetIdPub, 0x57AC68u, 0x57AE90u, 0x570030u};
// Callback functions the tests register (functions no test emits, so the recorders serve them).
constexpr u32 kCbA = 0x55E978u, kCbB = 0x55EA00u, kCbC = 0x55F4F0u;

std::map<u32, u64> g_cb_v0;                   // per-callback results (default 0)
std::vector<std::pair<u32, u32>> g_cb_seen;   // (callback, its first argument) as the recomp body met them
std::vector<std::string> g_err_text;          // texts the error-callback stand-in received
std::vector<u32> g_flag_seen;                 // SVM 'executing' flags read during a server call

// Every function pointer the machine's SVM / ROFS / RSU / Sofdec globals hold, plus the test's own.
std::vector<u32> callback_targets(Machine& m) {
    std::vector<u32> v = {kCbA, kCbB, kCbC};
    auto add = [&](u32 f) {
        if (f >= 0x100000u && f < 0x800000u && (f & 3) == 0) v.push_back(f);
    };
    for (u32 t = 0; t < 8; ++t)
        for (u32 s = 0; s < 6; ++s) add(r32(m, kSvmSvrTbl + t * kSvmTypeStride + s * kSvmSlotStride));
    for (u32 i = 0; i < 16; ++i) add(r32(m, kSvmThrdCb + 8 * i));
    for (u32 a : {0x99A0A0u, 0x99A0A8u, 0x99A0B0u, kSvmTasHook, kSvmCbC0, kSvmCbC8, kRsuErrCb}) add(r32(m, a));
    for (u32 a = kSfdCbTbl; a <= 0x7B2978u; a += 4) add(r32(m, a));
    const u32 work = r32(m, kRofsWorkPtr);
    if (work && work < 0x2000000u) add(r32(m, work + 64));
    std::sort(v.begin(), v.end());
    v.erase(std::unique(v.begin(), v.end()), v.end());
    return v;
}
void install_drivers(StandIns& s, Machine& m) {
    s.clobber_scratch = false;
    for (u32 va : kDrivers) s.install_recorder(va, "driver", 0, 3);
    for (u32 va : callback_targets(m)) {
        s.install(va, "callback", [va](EEContext& ctx, StandIns&, StandInCall& c) {
            c.v0 = g_cb_v0.count(va) ? g_cb_v0[va] : 0;
            g_cb_seen.emplace_back(va, uv(c.args[0]));
            g_flag_seen.push_back(ctx.memory->read<u32>(kSvmExecFlag + 4 * 4));  // type 4's flag (the rule check)
            // an error callback gets (object, text[, code]): keep printable texts
            const u32 t = uv(c.args[1]);
            if (t >= 0x100000u && t < 0x2000000u) {
                std::string s;
                for (u32 a = t; s.size() < 120; ++a) {
                    const char ch = static_cast<char>(ctx.memory->read<u8>(a));
                    if (ch == 0) break;
                    s += ch;
                }
                if (!s.empty() && std::all_of(s.begin(), s.end(), [](char ch) { return ch >= 32 && ch < 127; })) g_err_text.push_back(s);
            }
        }, 3);
    }
}

std::map<std::string, int> g_pairs;  // pairs per function in the meaningful sections
u32 g_seed = 1;

// One pair from the machine's current state, with the stand-ins; $t0..$t3 from `t`.
hgp::Run pr(Machine& m, u32 addr, Args a, std::map<unsigned, u64> t = {}) {
    const Case& c = by_addr(addr);
    StandIns si;
    install_drivers(si, m);
    StandInsScope scope{si};
    HwCheck hw;
    hw.gpr_in = std::move(t);
    ++g_pairs[c.name];
    return hgp::pair(m, c.hand, c.recomp, a, g_seed++, c.name, hw);
}
u64 v0of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
u64 prv(Machine& m, u32 addr, Args a, std::map<unsigned, u64> t = {}) {
    const hgp::Run r = pr(m, addr, a, std::move(t));
    INFO(by_addr(addr).name);
    CHECK_FALSE(r.stopped);
    return v0of(r);
}
std::map<unsigned, u64> tregs(u64 t0, u64 t1 = 0) { return {{GPR_T0, t0}, {GPR_T0 + 1, t1}}; }

std::unique_ptr<Machine> machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    return m;
}
std::vector<u8> snapshot(const char* dir) {
    std::vector<u8> snap = read_snapshot(dir);
    if (snap.size() != EEMemory::kMainRamSize) {
        MESSAGE("SKIP: snapshot " << dir << " not found");
        snap.clear();
    }
    return snap;
}
void restore(Machine& m, const std::vector<u8>& snap) { std::memcpy(m.mem.main_ram(), snap.data(), snap.size()); }
std::string summary() {
    int total = 0;
    for (const auto& [name, n] : g_pairs) total += n;
    return std::to_string(total) + " pairs over " + std::to_string(g_pairs.size()) + " functions";
}

// A file of the extracted tree (the disc's CVMs, the ISO), `len` bytes from `off`; empty when absent.
std::vector<u8> read_file(const std::string& path, u64 off, std::size_t len) {
    std::ifstream f(path, std::ios::binary);
    if (!f) return {};
    f.seekg(static_cast<std::streamoff>(off));
    std::vector<u8> b(len);
    f.read(reinterpret_cast<char*>(b.data()), static_cast<std::streamsize>(len));
    if (static_cast<std::size_t>(f.gcount()) != len) return {};
    return b;
}
std::string disc_file(const char* name) { return extracted_root() + "/disc/" + name; }
std::string iso_path() {
    const std::string root = extracted_root();  // .../extracted
    const std::size_t k = root.find_last_of("/\\");
    return (k == std::string::npos ? std::string(".") : root.substr(0, k)) + "/input/persona3fes.iso";
}

// --- the built world -------------------------------------------------------------------------------------------------
constexpr u32 kWork = 0x01810000u;      // free RAM for built records (the generated world's region)
constexpr u32 kText1 = kWork + 0x0000u, kText2 = kWork + 0x0100u, kBuf = kWork + 0x0200u;   // texts, a 256-byte buffer
constexpr u32 kHn = kWork + 0x0400u;    // a built ROFS handle (60 bytes) and its volume record
constexpr u32 kVolRec = kWork + 0x0480u, kLoc = kWork + 0x04C0u;
constexpr u32 kRofsW = kWork + 0xB000u;  // a built ROFS work (0x1100 bytes: the handle count +4, the table +4236)
constexpr u32 kOut = kWork + 0x0600u;   // outputs (2 KiB)
constexpr u32 kHdr = kWork + 0x1000u;   // a CVM header sector (2 KiB) and its zone sector
constexpr u32 kZoneHdr = kWork + 0x1800u;
constexpr u32 kInfo = kWork + 0x2000u;  // 1904-byte CVM info / 44-byte zone info
constexpr u32 kZoneInfo = kWork + 0x2800u;
constexpr u32 kSect = kWork + 0x3000u;  // 8 KiB of sector data for the descrambler
constexpr u32 kKey = kWork + 0x5000u, kMask = kWork + 0x5010u, kKeyOut = kWork + 0x5020u, kRound = kWork + 0x5030u;
constexpr u32 kRec = kWork + 0x6000u;   // a Sofdec reader record (2 KiB)
constexpr u32 kLut = kWork + 0x7000u;   // a 256-word lookup table
constexpr u32 kPix = kWork + 0x8000u;   // 16 x 16 x 4 source bytes, then the destination
constexpr u32 kDst = kWork + 0x9000u, kDesc = kWork + 0xA000u, kSrcPtr = kWork + 0xA040u;

// The built inputs every section can use (on top of whatever the machine holds).
void build_world(Machine& m, u32 seed) {
    std::mt19937 rng{seed};
    wstr(m, kText1, "../../rofs_hn.c");
    wstr(m, kText2, "ROFS_Seek");
    for (u32 i = 0; i < 256; ++i) w8(m, kBuf + i, static_cast<u8>(rng()));
    // a handle: open, 5 sectors, at sector 2, through a device record whose PFS handle is 0x1234
    std::memset(m.at(kHn), 0, 60);
    w32(m, kHn + rofs_hn::kSizeLo, 5 * 2048 - 100);
    w32(m, kHn + rofs_hn::kRofs, kRofsW);
    w32(m, kHn + rofs_hn::kPosSct, 2);
    w32(m, kHn + rofs_hn::kSizeSct, 5);
    w32(m, kHn + rofs_hn::kVol, kVolRec);
    w32(m, kHn + rofs_hn::kRdSct, 3);
    w32(m, kHn + rofs_hn::kRdRemBytes, 77);
    w16(m, kHn + rofs_hn::kActive, 1);
    w16(m, kHn + rofs_hn::kStat, 1);
    std::memset(m.at(kVolRec), 0, 64);
    w32(m, kVolRec, 0x1234u);
    w16(m, kVolRec + 20, 2);
    w32(m, kLoc, 0x00000000u);  // a 64-bit {sector-ish lo, hi} location for sub_569BE8
    w32(m, kLoc + 4, 0x00000000u);
    std::memset(m.at(kRofsW), 0, 0x1100);
    w32(m, kRofsW + 4, 2);                  // two handles in its table (+4236)
    std::memcpy(m.at(kRofsW + 4236), m.at(kHn), 60);
    w16(m, kRofsW + 4236 + rofs_hn::kReqState, 1);
    w32(m, kRofsW + 4236 + 60 + rofs_hn::kVol, kVolRec);
    w16(m, kRofsW + 4236 + 60 + rofs_hn::kReqState, 1);
    for (u32 i = 0; i < 0x800; ++i) w8(m, kOut + i, 0xCD);
    for (u32 i = 0; i < 8192; ++i) w8(m, kSect + i, static_cast<u8>(rng()));
    for (u32 i = 0; i < 8; ++i) w8(m, kKey + i, static_cast<u8>(rng() | 1));
    for (u32 i = 0; i < 0x800; ++i) w8(m, kRec + i, static_cast<u8>(rng()));
    for (u32 i = 0; i < 256; ++i) w32(m, kLut + 4 * i, 0xFF000000u | (i * 0x010101u));
    for (u32 i = 0; i < 2048; ++i) w8(m, kPix + i, static_cast<u8>(rng()));
    w32(m, kSrcPtr, kPix);
    std::memset(m.at(kDesc), 0, 32);
    w32(m, kDesc + 4, kDst);
    w32(m, kDesc + 8, 16);
    w32(m, kDesc + 16, 16);
    w32(m, kDesc + 20, 16);
    // a CVM header + zone: the disc's BGM.CVM when present, else a built one of the same form
    const std::vector<u8> cvm = read_file(disc_file("BGM.CVM"), 0, 0x1000);
    if (!cvm.empty()) {
        std::memcpy(m.at(kHdr), cvm.data(), 0x1000);
    } else {
        std::memset(m.at(kHdr), 0, 0x1000);
        std::memcpy(m.at(kHdr), "CVMH", 4);
        std::memcpy(m.at(kZoneHdr), "ZONE", 4);
    }
}

// The argument recipes per function: the values each one's branches test, the live records of the machine (the ROFS
// work area and its handles, the SVM tables) and the built world. Each entry: the four argument registers and $t0/$t1.
struct Call {
    Args a;
    u64 t0 = 0, t1 = 0;
};
std::vector<Call> recipes(Machine& m, u32 addr) {
    std::vector<Call> v;
    const u32 work = r32(m, kRofsWorkPtr);
    std::vector<u32> hns = {kHn};
    if (work && work < 0x2000000u) {
        const u32 n = std::min<u32>(r32(m, work + 4), 8);
        for (u32 i = 0; i < n; ++i) hns.push_back(work + 4236 + 60 * i);
    }
    auto add = [&](u64 a0, u64 a1 = 0, u64 a2 = 0, u64 a3 = 0, u64 t0 = 0, u64 t1 = 0) { v.push_back({Args{a0, a1, a2, a3}, t0, t1}); };
    switch (addr) {
    // SVM
    case 0x564878: add(kBuf); add(kRec); break;
    case 0x564BA0: add(kText1, kText2); add(kText2, kText1); break;
    case 0x564C10: add(12345, kOut, 16); add(0, kOut, 1); add(sx64(-7), kOut, 40); add(99, kOut, 0); break;
    case 0x564D20: add(1, 58, kOut, 16); add(10, 2, kOut, 8); break;
    case 0x564DB8: case 0x564DD0: case 0x564E38:
        for (u32 t : {0u, 2u, 4u, 7u, 8u}) add(t, kCbA, 0x77, addr == 0x564DB8u ? 0 : kText2);
        break;
    case 0x564F38: case 0x565328:
        for (u32 t : {0u, 2u, 4u, 5u, 8u})
            for (u32 id : {0u, 1u, 5u, 6u}) add(t, id);
        break;
    case 0x564FD0: case 0x565058:
        for (u32 t : {0u, 4u, 8u})
            for (u32 id : {0u, 2u, 6u}) add(t, id, kCbB, 0x55, 0, 0), v.back().t0 = (id == 2 ? kText2 : 0);
        break;
    case 0x565158: case 0x5651B0: for (u32 n : {0u, 1u, 3u}) add(n, kCbC, 0x66); break;
    case 0x5651F0: case 0x565230: case 0x565248: case 0x565690: add(kCbA, 0x11); add(0, 0); break;
    case 0x565480: for (u32 n : {0u, 4u, 6u, 7u, 100u}) add(n); break;
    case 0x5655E8: w32(m, kOut, 1); add(kOut); add(kOut + 4); break;
    // ROFS
    case 0x565970: case 0x565A20:
        for (u32 h : hns) add(h, 3, 0x99, kLoc, kVolRec);
        add(0, 3, 0, kLoc, kVolRec);
        add(kHn, 3, 0, kLoc, 0);
        break;
    case 0x565A78: case 0x565D78: case 0x565FE8: case 0x566050: case 0x5660F0: case 0x569700: case 0x569718:
        for (u32 h : hns) add(h);
        if (addr != 0x569700u && addr != 0x569718u) add(0);
        break;
    case 0x565AC0: add(kOut, 5); add(kOut, sx64(-1)); add(0, 5); break;
    case 0x565B18: for (u32 h : hns) add(h, 0), add(h, 0x1234), add(h, 0x9999); add(0, 0); break;
    case 0x565C10:
        for (u32 h : hns)
            for (u32 org : {0u, 1u, 2u, 3u})
                for (s32 off : {-1, 0, 1, 4, 5, 6}) add(h, sx64(off), org);
        add(0, 0, 0);
        break;
    case 0x567430: add(kRofsW); add(0); if (work) add(r32(m, work + 44)); break;
    case 0x5675C8: add(kInfo, kZoneInfo); add(0, kZoneInfo); add(kInfo, 0); break;
    case 0x569518: add(kCbA, 0x42); add(0, 0); break;
    case 0x569730:
        add(kText1, 302, kText2, 0, sx64(-101));
        add(kText1, 7, kText2, kText1, sx64(-205));
        break;
    case 0x569960: case 0x56B3C0:
        w32(m, kOut, 0x10); w32(m, kOut + 4, 0x2); w32(m, kOut + 8, 0x3); w32(m, kOut + 12, 0);
        for (u32 op = 0; op < 7; ++op)
            for (u32 width : {0u, 1u, 2u, 3u}) add(op, width, kOut + 8, kOut);
        break;
    case 0x569AF0: add(kBuf, kOut); break;
    case 0x569B60: add(kOut); break;
    case 0x569C00: add(kKey - 36, kSect, 2, 100); add(kKey - 36, kSect, 0, 7); break;
    case 0x569F40: add(5); add(0); break;
    case 0x569F60: case 0x56A040:
        for (u32 kind : {0u, 1u, 2u, 3u})
            for (u32 val : {0u, 1u, 2u}) add(0, kind, addr == 0x56A040u ? kOut : val);
        break;
    case 0x56A0A8: add(kOut, kHdr); break;
    case 0x56A348: case 0x56A468: add(kHdr); add(kBuf); break;
    case 0x56A4F8: w32(m, kRofsCopySrc, kHdr); for (u32 n : {0u, 3u, 13u}) add(kOut, 0x7B27B0u, n); break;
    case 0x56AD28: add(0x7C6F50u); break;
    case 0x56AD48: case 0x56ADB8: case 0x56ADE0: case 0x56B0D0: add(kHdr + 0x1C, kOut); add(kBuf, kOut); break;
    case 0x56AE20: add(kHdr + 12, kInfo); break;
    case 0x56B028: case 0x56B240: case 0x56B528: case 0x56B690: add(kHdr, kInfo); add(kBuf, kInfo); break;
    case 0x56B128: case 0x56B300: case 0x56B6E0: add(kZoneHdr, kZoneInfo); add(kHdr, kZoneInfo); add(kBuf, kZoneInfo); break;
    case 0x56B918: for (u32 n : {0u, 1u, 3u, 1000u}) add(n); break;
    // RSU
    case 0x56CE10: add(kText2); break;
    case 0x56CE88:
        add(kText2, 9, kOut, kOut + 2, kOut + 4);
        add(kText1, 1, kOut, kOut + 2, kOut + 4);
        add(0, 0, kOut, kOut + 2, kOut + 4);
        add(kBuf, sx64(-3), kOut, kOut + 2, kOut + 4);
        break;
    case 0x56D040: add(kOut, kOut + 2, kOut + 4); break;
    case 0x56D0D0: case 0x56D108: add(0x12345678u, kOut); add(0xFFFF, kOut); break;
    case 0x56D140: add(kHdr + 48, kOut); add(kBuf, kOut); break;
    case 0x56D180: add(kHdr, kOut); w32(m, kBuf + 48, 0x10000000u); add(kBuf, kOut); break;
    case 0x56D1E8:
        w32(m, kOut, kText1); w32(m, kOut + 4, kText2); add(kOut, kKeyOut);
        w32(m, kOut + 8, 0); w32(m, kOut + 12, kText2); add(kOut + 8, kKeyOut);
        break;
    case 0x56D248: add(kKey); break;
    case 0x56D2D0: case 0x56D4A0: case 0x56D828: for (u32 s : {0u, 1u, 100u, 0x12345u}) add(s, kMask, kRound); add(1, 0, kRound); break;
    case 0x56D358: add(kHdr, kKeyOut); add(kBuf, kKeyOut); break;
    case 0x56D3B0: add(kText2, kKeyOut); add(kText1, kKeyOut); break;
    case 0x56D4C0: case 0x56D850:
        for (u32 r : {0u, 4u, 8u, 9u}) add(kKey, kMask, r, kKeyOut);
        add(0, kMask, 1, kKeyOut);
        add(kKey, kMask, 1, 0);
        break;
    case 0x56D508: case 0x56D6C0: case 0x56D898: case 0x56D900:
        add(kSect, 4096, 2048, 50, kKey, 8);
        add(kSect, 4096, 2000, 50, kKey, 8);
        add(kSect, 2048, 2048, 0, kKey, 3);
        add(kSect, 2048, 2048, 0, kOut, 8);   // kOut: 0xCD bytes, not zero
        add(0, 2048, 2048, 0, kKey, 8);
        add(kSect, sx64(-1), 2048, 0, kKey, 8);
        break;
    case 0x56D780: add(kHdr, 0, kKeyOut); add(kHdr, kText2, kKeyOut); add(0, 0, kKeyOut); add(kHdr, 0, 0); break;
    case 0x56D968: add(kKey, 8); add(kOut + 0x700, 0); w32(m, kOut + 0x7F0, 0); w32(m, kOut + 0x7F4, 0); add(kOut + 0x7F0, 8); break;
    case 0x56D9A8: case 0x56DA10: case 0x56DA78: case 0x56DAE0: case 0x56DB48: case 0x56DBB0: case 0x56DC18:
    case 0x56DC80: case 0x56DCE8:
        add(kKey, kMask, kKeyOut);
        break;
    // CFT / Sofdec
    case 0x56DED0: add(0x5A5A); break;
    case 0x56DF40: add(kSrcPtr, kDesc, kLut); break;
    case 0x56F4B8:
        add(3, 4, 5, 6); add(sx64(-3), 4, 5, 6); add(0x7FFFFFFF, 0x7FFFFFFF, 1, 1); add(2, 1, 4, 2);
        break;
    case 0x56F888: case 0x56FA00: case 0x56FAC0: case 0x56FBC0: case 0x56FCB0: case 0x56FE08: case 0x56FE18:
    case 0x56FE40:
        add(kRec, kOut, kOut + 8, kOut + 16);
        add(kRec, 0, 0, 0);
        break;
    case 0x56FC20: add(kRec, kOut, kOut + 4, kOut + 8); break;
    case 0x56F9C8: w32(m, kRec, kCbA); add(kRec, 1); add(kRec, 0); w32(m, kRec + 0x100, 0); add(kRec + 0x100, 1); break;
    case 0x56FD58: case 0x56FEC0: add(kRec); break;
    case 0x56FDE0: add(kRec, 0, 1, 2, 3); add(kRec, 3, 4, 5, 6); break;
    default: add(0); break;  // no arguments (getters, executors, init / finish, stubs)
    }
    return v;
}

}  // namespace

TEST_CASE("game(libs4): every body equals its recompiled body on random worlds") {
    auto m = machine();
    if (!m) return;
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : 24u;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    constexpr u32 kWorldSize = 0x10000u;
    int total = 0, stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWork, kWorldSize, rng);
            const u64 a0 = hgp::random_arg(rng, kWork, kWorldSize);
            const u64 a1 = hgp::random_arg(rng, kWork, kWorldSize);
            const u64 a2 = hgp::random_arg(rng, kWork, kWorldSize);
            const u64 a3 = hgp::random_arg(rng, kWork, kWorldSize);
            stops += hgp::pair(*m, c.hand, c.recomp, Args{a0, a1, a2, a3}, seed, c.name).stopped ? 1 : 0;
            ++total;
        }
    }
    MESSAGE(total << " pairs, " << stops << " stopped early (identically)");
}

// Every function on four replay snapshots: the live SVM server table, its callbacks and counters, the live ROFS work
// area (0x7B2700) and its file handles, RSU's and Sofdec's globals, plus the built world for the inputs no snapshot
// holds (CVM headers from the disc, texts, keys, sector data, a reader record). Each pair starts from the snapshot.
TEST_CASE("game(libs4): every body on the snapshots' live SVM table, ROFS work area and handles") {
    auto m = machine();
    if (!m) return;
    const char* only = std::getenv("P3FES_HG_ONLY");
    int ran = 0, stopped = 0;
    for (const char* dir : {"dorm_replay_4900", "b_5800", "battle_ref_6150", "fusion_ref_6300"}) {
        const std::vector<u8> snap = snapshot(dir);
        if (snap.empty()) continue;
        restore(*m, snap);
        CHECK(r32(*m, kRofsWorkPtr) != 0u);  // ROFS is mounted on every route
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            restore(*m, snap);
            build_world(*m, c.addr);
            const std::vector<Call> calls = recipes(*m, c.addr);
            for (const Call& call : calls) {
                restore(*m, snap);
                build_world(*m, c.addr);
                (void)recipes(*m, c.addr);  // the recipes' own memory set-up
                const hgp::Run r = pr(*m, c.addr, call.a, tregs(call.t0, call.t1));
                ++ran;
                stopped += r.stopped ? 1 : 0;
            }
        }
    }
    MESSAGE(ran << " pairs on snapshot state, " << stopped << " stopped (identically)");
    MESSAGE(summary());
}

// SVM's server table on a fresh machine: register into the first free slot, 'too many', the name default, set /
// overwrite / delete by id with their range errors (texts through the error callback), execute one slot and a whole
// type (results OR-ed, the type's 'executing' flag set around each call, the count), init / finish, the setters.
TEST_CASE("game(libs4): SVM -- the server table, execution, counters, callbacks, test-and-set") {
    auto m = machine();
    if (!m) return;
    build_world(*m, 1);
    w32(*m, 0x99A0B0u, kCbC);  // the error callback: a recorder that keeps the texts
    w32(*m, 0x99A0B4u, 0xE0);
    g_err_text.clear();
    // register: type 4, three functions, then fill the type
    CHECK(sv(prv(*m, 0x564DD0u, Args{4, kCbA, 0x10, kText2})) == 0);
    CHECK(r32(*m, kSvmSvrTbl + 4 * kSvmTypeStride) == kCbA);
    CHECK(r32(*m, kSvmSvrTbl + 4 * kSvmTypeStride + 4) == 0x10u);
    CHECK(rstr(*m, r32(*m, kSvmSvrTbl + 4 * kSvmTypeStride + 8)) == "ROFS_Seek");
    CHECK(sv(prv(*m, 0x564DB8u, Args{4, kCbB, 0x20, 0})) == 1);
    CHECK(rstr(*m, r32(*m, kSvmSvrTbl + 4 * kSvmTypeStride + kSvmSlotStride + 8)) == "Unknown");
    for (s32 slot = 2; slot < 6; ++slot) CHECK(sv(prv(*m, 0x564E38u, Args{4, kCbA, 0x30, 0})) == slot);
    CHECK(sv(prv(*m, 0x564E38u, Args{4, kCbA, 0x30, 0})) == -1);
    CHECK(sv(prv(*m, 0x564E38u, Args{8, kCbA, 0x30, 0})) == -1);
    // delete slot 3, register again: it is found
    prv(*m, 0x564F38u, Args{4, 3, 0, 0});
    CHECK(r32(*m, kSvmSvrTbl + 4 * kSvmTypeStride + 3 * kSvmSlotStride) == 0u);
    CHECK(sv(prv(*m, 0x564E38u, Args{4, kCbB, 0x40, 0})) == 3);
    prv(*m, 0x564F38u, Args{4, 6, 0, 0});
    prv(*m, 0x564F38u, Args{9, 0, 0, 0});
    // set by id: empty slot of type 1, then the overwrite (reported, still stored), the range errors (nothing stored)
    prv(*m, 0x565058u, Args{1, 2, kCbA, 0x50}, tregs(0));
    CHECK(r32(*m, kSvmSvrTbl + 1 * kSvmTypeStride + 2 * kSvmSlotStride) == kCbA);
    CHECK(rstr(*m, r32(*m, kSvmSvrTbl + 1 * kSvmTypeStride + 2 * kSvmSlotStride + 8)) == "Unknown");
    prv(*m, 0x565058u, Args{1, 2, kCbB, 0x51}, tregs(kText1));
    CHECK(r32(*m, kSvmSvrTbl + 1 * kSvmTypeStride + 2 * kSvmSlotStride) == kCbB);
    CHECK(r32(*m, kSvmSvrTbl + 1 * kSvmTypeStride + 2 * kSvmSlotStride + 4) == 0x51u);
    prv(*m, 0x565058u, Args{1, 6, kCbA, 0x52}, tregs(0));
    prv(*m, 0x565058u, Args{8, 0, kCbA, 0x52}, tregs(0));
    const std::vector<std::string> expect_err = {
        "1051001:SVM_SetCbSvr:too many server function", "1071205:SVM_SetCbSvrId:illegal svtype",
        "1051002:SVM_DelCbSvr:illegal id", "1071206:SVM_SetCbSvrId:illegal svtype",
        "2100801:SVM_SetCbSvrId:over write callback function.", "1071201:SVM_SetCbSvrId:illegal id",
        "1071202:SVM_SetCbSvrId:illegal svtype"};
    // each text twice (the hand and the recompiled run of the pair)
    std::vector<std::string> seen;
    for (std::size_t i = 0; i < g_err_text.size(); i += 2) seen.push_back(g_err_text[i]);
    CHECK(seen == expect_err);
    // execute one slot: the function's result with its object; empty / out of range 0
    g_cb_v0[kCbB] = 0x8;
    g_cb_seen.clear();
    CHECK(prv(*m, 0x565328u, Args{1, 2, 0, 0}) == 0x8u);
    REQUIRE(g_cb_seen.size() == 2u);
    CHECK(g_cb_seen[1] == std::make_pair(kCbB, 0x51u));
    CHECK(prv(*m, 0x565328u, Args{1, 3, 0, 0}) == 0u);
    CHECK(prv(*m, 0x565328u, Args{1, 6, 0, 0}) == 0u);
    // execute type 4: slots 0..5 in order, the OR of the results, the flag set during each call, the counter
    g_cb_v0[kCbA] = 0x1;
    g_cb_v0[kCbB] = 0x10;
    g_cb_seen.clear();
    g_flag_seen.clear();
    const u32 count0 = r32(*m, kSvmExecCount + 16);
    CHECK(prv(*m, 0x565420u, Args{0, 0, 0, 0}) == 0x11u);
    CHECK(r32(*m, kSvmExecCount + 16) == count0 + 1);  // the recompiled run's memory stays: one count
    CHECK(r32(*m, kSvmExecFlag + 16) == 0u);
    REQUIRE(g_cb_seen.size() == 12u);
    const u32 objs[6] = {0x10, 0x20, 0x30, 0x40, 0x30, 0x30};
    for (u32 i = 0; i < 6; ++i) CHECK(g_cb_seen[6 + i].second == objs[i]);
    for (u32 f : g_flag_seen) CHECK(f == 1u);
    CHECK(prv(*m, 0x565480u, Args{4, 0, 0, 0}) == r32(*m, kSvmExecCount + 16));
    CHECK(prv(*m, 0x565480u, Args{7, 0, 0, 0}) == 0u);
    // the other types run their own slots only (type 1: slot 2)
    g_cb_seen.clear();
    CHECK(prv(*m, 0x5653D8u, Args{0, 0, 0, 0}) == 0x10u);
    CHECK(g_cb_seen.size() == 2u);
    for (u32 a : {0x5653C0u, 0x5653F0u, 0x565408u, 0x565438u, 0x565450u, 0x565468u}) CHECK(prv(*m, a, Args{0, 0, 0, 0}) == 0u);
    // init / finish counting: the first init and the last finish reset (the table stays)
    w32(*m, kSvmInitCount, 0);
    w32(*m, kSvmExecFlag, 1);
    w32(*m, kSvmExecCount + 4 * 5, 9);
    w32(*m, kSvmExecCount + 4 * 6, 5);
    CHECK(prv(*m, 0x565550u, Args{0, 0, 0, 0}) == 1u);
    CHECK(r32(*m, kSvmExecFlag) == 0u);
    CHECK(r32(*m, kSvmExecCount + 4 * 5) == 0u);  // the reset clears six counters (types 0..5) ...
    CHECK(r32(*m, kSvmExecCount + 4 * 6) == 5u);  // ... type 6's survives
    CHECK(prv(*m, 0x565480u, Args{6, 0, 0, 0}) == 5u);
    CHECK(prv(*m, 0x565550u, Args{0, 0, 0, 0}) == 2u);
    w32(*m, kSvmExecFlag, 1);
    prv(*m, 0x565590u, Args{0, 0, 0, 0});
    CHECK(r32(*m, kSvmExecFlag) == 1u);
    CHECK(r32(*m, 0x99A0B0u) == kCbC);
    prv(*m, 0x565590u, Args{0, 0, 0, 0});
    CHECK(r32(*m, kSvmInitCount) == 0u);
    CHECK(r32(*m, kSvmExecFlag) == 0u);
    CHECK(r32(*m, 0x99A0B0u) == 0u);  // the last finish clears the error callback
    CHECK(r32(*m, kSvmSvrTbl + 4 * kSvmTypeStride) == kCbA);
    // setters / callers
    prv(*m, 0x565158u, Args{3, kCbA, 0x77, 0});
    CHECK(r32(*m, kSvmThrdCb + 24) == kCbA);
    CHECK(r32(*m, kSvmThrdCb + 28) == 0x77u);
    g_cb_seen.clear();
    g_cb_v0[kCbA] = 5;
    CHECK(prv(*m, 0x5651B0u, Args{3, 0, 0, 0}) == 5u);
    CHECK(g_cb_seen.back() == std::make_pair(kCbA, 0x77u));
    prv(*m, 0x5651F0u, Args{kCbB, 0x12, 0, 0});
    CHECK(r32(*m, 0x99A0B0u) == kCbB);
    CHECK(r32(*m, 0x99A0B4u) == 0x12u);
    prv(*m, 0x565690u, Args{kCbC, 0x13, 0, 0});
    CHECK(r32(*m, kSvmCbC0) == kCbC);
    g_cb_v0[kCbC] = 9;
    CHECK(prv(*m, 0x5656C0u, Args{0, 0, 0, 0}) == 9u);
    w32(*m, kSvmCbC8, 0);
    CHECK(prv(*m, 0x5656F0u, Args{0, 0, 0, 0}) == kSvmCbC8);  // none: the slot's address is left in $v0
    // test-and-set: locked, *flag = 1, "was not 1"; a hook takes over; the hook clearer only clears an unset hook
    w32(*m, kSvmTasHook, 0);
    w32(*m, kOut, 0);
    CHECK(prv(*m, 0x5655E8u, Args{kOut, 0, 0, 0}) == 1u);
    CHECK(r32(*m, kOut) == 1u);
    CHECK(prv(*m, 0x5655E8u, Args{kOut, 0, 0, 0}) == 0u);
    CHECK(prv(*m, 0x565678u, Args{0, 0, 0, 0}) == 1u);
    w32(*m, kSvmTasHook, kCbA);
    g_cb_v0[kCbA] = 0x33;
    CHECK(prv(*m, 0x5655E8u, Args{kOut, 0, 0, 0}) == 0x33u);
    CHECK(prv(*m, 0x565678u, Args{0, 0, 0, 0}) == 0u);
    CHECK(r32(*m, kSvmTasHook) == kCbA);
    // the lock type getter and the type-1000 lock / unlock pair leave the depth as it was
    const u32 depth = r32(*m, 0x7B2630u);
    prv(*m, 0x564A08u, Args{0, 0, 0, 0});
    CHECK(prv(*m, 0x564A98u, Args{0, 0, 0, 0}) == r32(*m, 0x7B2634u));
    prv(*m, 0x564A80u, Args{0, 0, 0, 0});
    CHECK(r32(*m, 0x7B2630u) == depth);
    // number to text, as compiled: digits into buf, then the reversed static buffer over them
    wstr(*m, kSvmItoaBuf, "4321");
    prv(*m, 0x564C10u, Args{987, kOut, 16, 0});
    CHECK(rstr(*m, kOut) == "1234");
    wstr(*m, kSvmItoaBuf, "");
    prv(*m, 0x564C10u, Args{987, kOut, 16, 0});
    CHECK(r8(*m, kOut) == 0);
    w8(*m, kOut + 1, 0xEE);
    w8(*m, kOut + 2, 0xEE);
    MESSAGE(summary());
}

// ROFS: the live handles' seek / tell / status / counts and the range rules, the error text through a callback.
TEST_CASE("game(libs4): ROFS -- handles, seek rules, the error text, the work flags, the handle fill") {
    auto m = machine();
    if (!m) return;
    const std::vector<u8> snap = snapshot("dorm_replay_4900");
    if (snap.empty()) return;
    restore(*m, snap);
    build_world(*m, 2);
    const u32 work = r32(*m, kRofsWorkPtr);
    REQUIRE(work != 0u);
    // the live handles: tell = +20, status = +56 (open ones), counts = (+36 << 11) + +40
    const u32 n = r32(*m, work + 4);
    CHECK(n >= 1u);
    for (u32 i = 0; i < n && i < 8; ++i) {
        const u32 h = work + 4236 + 60 * i;
        if (r16(*m, h + rofs_hn::kActive) == 0) continue;
        CHECK(sv(prv(*m, 0x565D78u, Args{h, 0, 0, 0})) == r32s(*m, h + rofs_hn::kPosSct));
        CHECK(sv(prv(*m, 0x565FE8u, Args{h, 0, 0, 0})) == r16s(*m, h + rofs_hn::kStat));
        CHECK(uv(prv(*m, 0x566050u, Args{h, 0, 0, 0})) == (r32(*m, h + rofs_hn::kRdSct) << 11) + r32(*m, h + rofs_hn::kRdRemBytes));
        CHECK(uv(prv(*m, 0x5660F0u, Args{h, 0, 0, 0})) == (r32(*m, h + rofs_hn::kRdSct) << 11) + r32(*m, h + rofs_hn::kRdRemBytes));
    }
    // seek on the built handle (5 sectors at position 2): the three origins, the range and origin errors
    CHECK(sv(prv(*m, 0x565C10u, Args{kHn, 1, 0, 0})) == 1);
    CHECK(sv(prv(*m, 0x565C10u, Args{kHn, 2, 1, 0})) == 3);
    CHECK(sv(prv(*m, 0x565C10u, Args{kHn, sx64(-5), 2, 0})) == 0);
    CHECK(sv(prv(*m, 0x565C10u, Args{kHn, 5, 0, 0})) == 5);  // the end itself is allowed
    CHECK(sv(prv(*m, 0x565C10u, Args{kHn, 6, 0, 0})) == -205);
    CHECK(sv(prv(*m, 0x565C10u, Args{kHn, sx64(-1), 0, 0})) == -205);
    CHECK(sv(prv(*m, 0x565C10u, Args{kHn, 0, 3, 0})) == -205);
    CHECK(sv(prv(*m, 0x569820u, Args{0, 0, 0, 0})) == -205);  // the last error
    CHECK(r32s(*m, kHn + rofs_hn::kPosSct) == 5);  // the failed seeks left the position
    CHECK(sv(prv(*m, 0x565D78u, Args{kHn, 0, 0, 0})) == 5);
    CHECK(sv(prv(*m, 0x569830u, Args{0, 0, 0, 0})) == 0);   // tell cleared it
    CHECK(sv(prv(*m, 0x565C10u, Args{0, 0, 0, 0})) == -101);
    w16(*m, kHn + rofs_hn::kActive, 0);
    CHECK(sv(prv(*m, 0x565D78u, Args{kHn, 0, 0, 0})) == -101);
    CHECK(sv(prv(*m, 0x565FE8u, Args{kHn, 0, 0, 0})) == 3);
    CHECK(sv(prv(*m, 0x565FE8u, Args{0, 0, 0, 0})) == 3);
    // the error text through an error callback (work +64 / +68)
    prv(*m, 0x569518u, Args{kCbA, 0x4242, 0, 0});
    CHECK(r32(*m, work + 64) == kCbA);
    CHECK(r32(*m, work + 68) == 0x4242u);
    g_err_text.clear();
    CHECK(sv(prv(*m, 0x569730u, Args{kText1, 302, kText2, 0}, tregs(sx64(-101)))) == -101);
    CHECK(sv(prv(*m, 0x569730u, Args{kText1, 9, kText2, kText1}, tregs(sx64(-7)))) == -7);
    REQUIRE(g_err_text.size() == 4u);
    CHECK(g_err_text[0] == "(-101)ROFS_Seek#../../rofs_hn.c:302");
    CHECK(g_err_text[2] == "(-7)ROFS_Seek[../../rofs_hn.c]#../../rofs_hn.c:9");
    CHECK(rstr(*m, kRofsErrText) == "(-7)ROFS_Seek[../../rofs_hn.c]#../../rofs_hn.c:9");
    w16(*m, kHn + rofs_hn::kActive, 1);
    g_err_text.clear();
    CHECK(sv(prv(*m, 0x565C10u, Args{kHn, 9, 0, 0})) == -205);
    REQUIRE(g_err_text.size() == 2u);
    CHECK(g_err_text[0] == "(-205)ROFS_Seek#../../rofs_hn.c:329");
    // no work area: -203
    w32(*m, kRofsWorkPtr, 0);
    CHECK(sv(prv(*m, 0x569730u, Args{kText1, 1, kText2, 0}, tregs(sx64(-1)))) == -203);
    CHECK(sv(prv(*m, 0x569820u, Args{0, 0, 0, 0})) == -203);
    w32(*m, kRofsWorkPtr, work);
    // the work flags: kinds 1 / 2 / 0 -> bits 0 / 1 / 10, read back
    const u32 flags0 = r32(*m, work + 24);
    prv(*m, 0x569F60u, Args{0, 1, 1, 0});
    prv(*m, 0x569F60u, Args{0, 2, 1, 0});
    CHECK((r32(*m, work + 24) & 3u) == 3u);
    w32(*m, kOut, 7);
    CHECK(prv(*m, 0x56A040u, Args{0, 2, kOut, 0}) == 0u);
    CHECK(r32(*m, kOut) == 1u);
    prv(*m, 0x569F60u, Args{0, 2, 0, 0});
    CHECK((r32(*m, work + 24) & 2u) == 0u);
    CHECK(sv(prv(*m, 0x569F60u, Args{0, 3, 1, 0})) == -100);
    CHECK(sv(prv(*m, 0x56A040u, Args{0, 3, kOut, 0})) == -100);
    w32(*m, work + 24, flags0);
    prv(*m, 0x569F40u, Args{7, 0, 0, 0});
    CHECK(r32(*m, work + 28) == 70000u);
    CHECK(prv(*m, 0x569950u, Args{0, 0, 0, 0}) == r32(*m, work + 20));
    CHECK(prv(*m, 0x5669B8u, Args{0, 0, 0, 0}) == 2048u);
    // the handle fill: open, the 64-bit size split, the size in sectors rounded up, counts cleared
    w32(*m, kLoc, 0x1000u);     // sub_569BE8 splits the 64-bit location {lo, hi}
    w32(*m, kLoc + 4, 0);
    std::memset(m->at(kOut), 0xEE, 60);
    w16(*m, kOut + rofs_hn::kActive, 0);
    CHECK(uv(prv(*m, 0x565A20u, Args{kOut, 3, 0x99, kLoc}, tregs(kVolRec))) == kOut);
    CHECK(r16(*m, kOut + rofs_hn::kActive) == 1u);
    CHECK(r32(*m, kOut + rofs_hn::kDirIdx) == 3u);
    CHECK(r32(*m, kOut + rofs_hn::kStartLba) == 0x99u);
    CHECK(r32(*m, kOut + rofs_hn::kVol) == kVolRec);
    CHECK(r32(*m, kOut + rofs_hn::kSizeSct) == (r32(*m, kOut + rofs_hn::kSizeLo) + 2047) >> 11);
    CHECK(r32(*m, kOut + rofs_hn::kPosSct) == 0u);
    CHECK(r32(*m, kOut + rofs_hn::kRofs) == 0xEEEEEEEEu);  // not the fill's
    // a second create on the now open handle fails; reopen refills unless it is transferring
    CHECK(prv(*m, 0x565A20u, Args{kOut, 3, 0x99, kLoc}, tregs(kVolRec)) == 0u);
    w16(*m, kOut + rofs_hn::kReqState, 1);
    CHECK(prv(*m, 0x565A78u, Args{kOut, 3, 0x98, kLoc}, tregs(kVolRec)) == 0u);
    w16(*m, kOut + rofs_hn::kReqState, 2);
    CHECK(uv(prv(*m, 0x565A78u, Args{kOut, 3, 0x98, kLoc}, tregs(kVolRec))) == kOut);
    CHECK(r32(*m, kOut + rofs_hn::kStartLba) == 0x98u);
    // the image-handle search: the built work's first handle transfers through a volume whose image handle is 0x1234
    CHECK(prv(*m, 0x565B18u, Args{kRofsW + 4236, 0x1234, 0, 0}) == 1u);
    CHECK(prv(*m, 0x565B18u, Args{kRofsW + 4236, 0x9999, 0, 0}) == 0u);
    CHECK(prv(*m, 0x565B18u, Args{kRofsW + 4236, 0, 0, 0}) == 1u);  // the default: its own device handle
    // the use count of a handle's volume record
    CHECK(prv(*m, 0x569700u, Args{kHn, 0, 0, 0}) == 3u);
    CHECK(prv(*m, 0x569718u, Args{kHn, 0, 0, 0}) == 2u);
    // directory handle: 72 bytes cleared, the size kept; a negative size is refused
    std::memset(m->at(kOut), 0xEE, 80);
    CHECK(uv(prv(*m, 0x565AC0u, Args{kOut, 12, 0, 0})) == kOut);
    CHECK(r32(*m, kOut + rofs_dirhn::kDirSize) == 12u);
    CHECK(r32(*m, kOut + 68) == 0u);
    CHECK(r32(*m, kOut + 72) == 0xEEEEEEEEu);
    CHECK(prv(*m, 0x565AC0u, Args{kOut, sx64(-1), 0, 0}) == 0u);
    // delete a volume record: 52 bytes cleared, no longer the default
    w32(*m, work + 44, kRofsW);
    prv(*m, 0x567430u, Args{kRofsW, 0, 0, 0});
    CHECK(r32(*m, work + 44) == 0u);
    CHECK(r32(*m, kRofsW + 4) == 0u);
    MESSAGE(summary());
}

// The disc's CVM headers: CVMH + ZONE parsed and checked against the bytes; a CVMF header; bad magics.
TEST_CASE("game(libs4): the disc's CVM headers -- CVMH / ZONE / CVMF parsed, bad magics refused") {
    auto m = machine();
    if (!m) return;
    int files = 0;
    for (const char* name : {"BGM.CVM", "BTL.CVM", "DATA.CVM"}) {
        const std::vector<u8> h = read_file(disc_file(name), 0, 0x1000);
        if (h.empty()) {
            MESSAGE("SKIP: " << name << " not found");
            continue;
        }
        ++files;
        INFO(name);
        std::memcpy(m->at(kHdr), h.data(), 0x1000);
        std::memset(m->at(kInfo), 0xEE, 1904 + 16);
        CHECK(prv(*m, 0x56B240u, Args{kHdr, kInfo, 0, 0}) == 0u);
        const u8* mp = h.data() + 12;  // the main part
        CHECK(r32(*m, kInfo + cvm_info::kTotalSize) == be32(mp + 20));
        CHECK(r32(*m, kInfo + cvm_info::kTotalSize + 4) == be32(mp + 16));
        const u64 size = (u64{r32(*m, kInfo + 4)} << 32) | r32(*m, kInfo);
        std::ifstream f(disc_file(name), std::ios::binary | std::ios::ate);
        CHECK(size == static_cast<u64>(f.tellg()));  // the header's size is the file's
        CHECK(std::memcmp(m->at(kInfo + cvm_info::kDate), mp + 24, 7) == 0);
        CHECK(std::memcmp(m->at(kInfo + cvm_info::kVersion), mp + 32, 4) == 0);
        CHECK(r32(*m, kInfo + cvm_info::kFlags) == be32(mp + 36));
        CHECK(std::memcmp(m->at(kInfo + cvm_info::kId), mp + 44, 63) == 0);
        CHECK(r8(*m, kInfo + cvm_info::kIdEnd) == 0);
        CHECK(r32(*m, kInfo + cvm_info::kNumZones) == be32(mp + 116));
        CHECK(r32(*m, kInfo + cvm_info::kZoneSel) == be32(mp + 120));
        CHECK(r32(*m, kInfo + cvm_info::kDataSct) == be32(mp + 124));
        const u32 nz = r32(*m, kInfo + cvm_info::kNumZones);
        CHECK(nz >= 1u);
        for (u32 z = 0; z < nz && z < 8; ++z) CHECK(r32(*m, kInfo + cvm_info::kZoneTbl + 4 * z) == be32(h.data() + 256 + 4 * z));
        CHECK(r32(*m, kInfo + 1904) == 0xEEEEEEEEu);  // the 1904-byte clear stops there
        CHECK(rstr(*m, kInfo + cvm_info::kId).rfind("ROFSBLD", 0) == 0);  // the ID names the builder
        // the zone header (the next sector)
        std::memset(m->at(kZoneInfo), 0xEE, 64);
        CHECK(prv(*m, 0x56B300u, Args{kHdr + 0x800, kZoneInfo, 0, 0}) == 0u);
        const u8* zp = h.data() + 0x800;
        CHECK(r32(*m, kZoneInfo + zone_info::kWord0) == be32(zp + 12));
        CHECK(std::memcmp(m->at(kZoneInfo + zone_info::kFlag0), zp + 16, 5) == 0);
        CHECK(r32(*m, kZoneInfo + zone_info::kWord12) == be32(zp + 24));
        CHECK(r32(*m, kZoneInfo + zone_info::kWord16) == be32(zp + 28));
        CHECK(r32(*m, kZoneInfo + zone_info::kLoc0) == be32(zp + 32));
        CHECK(r32(*m, kZoneInfo + zone_info::kLoc0 + 4) == be32(zp + 40));
        CHECK(r32(*m, kZoneInfo + zone_info::kLoc0 + 8) == be32(zp + 36));
        CHECK(r32(*m, kZoneInfo + zone_info::kLoc1) == be32(zp + 44));
        CHECK(r32(*m, kZoneInfo + zone_info::kLoc1 + 4) == be32(zp + 52));
        CHECK(r32(*m, kZoneInfo + 44) == 0xEEEEEEEEu);
        // on the disc: 2048-byte sectors, location 1 = the data from sector 3 to the end of the file
        CHECK(r32(*m, kZoneInfo + zone_info::kWord12) == 2048u);
        CHECK(r32(*m, kZoneInfo + zone_info::kLoc1) == r32(*m, kInfo + cvm_info::kDataSct));
        CHECK(u64{r32(*m, kZoneInfo + zone_info::kLoc1 + 4)} + 2048u * r32(*m, kZoneInfo + zone_info::kLoc1) == size);
        // the scramble flag is clear: no key strings, the fixed key stays zero
        CHECK((be32(h.data() + 48) & 0x10u) == 0u);
        std::memset(m->at(kKeyOut), 0xEE, 8);
        CHECK(prv(*m, 0x56D780u, Args{kHdr, 0, kKeyOut, 0}) == 0u);
        for (u32 i = 0; i < 8; ++i) CHECK(r8(*m, kKeyOut + i) == 0);
    }
    if (files == 0) return;
    // bad magics
    std::memcpy(m->at(kBuf), "XVMH", 4);
    CHECK(sv(prv(*m, 0x56B240u, Args{kBuf, kInfo, 0, 0})) == -2);
    CHECK(sv(prv(*m, 0x56B300u, Args{kBuf, kZoneInfo, 0, 0})) == -2);
    // a 'CIMF' (CD CRAFT) image header: size +4 (+8), the ID, one zone, the data offset (+32 + 352,816) / 2048
    std::memset(m->at(kBuf), 0, 64);
    std::memcpy(m->at(kBuf), "CIMF", 4);
    const u8 sz[4] = {0x00, 0x10, 0x00, 0x00}, off[4] = {0x00, 0x00, 0x10, 0x00};
    std::memcpy(m->at(kBuf + 4), sz, 4);
    std::memcpy(m->at(kBuf + 32), off, 4);
    CHECK(prv(*m, 0x56B240u, Args{kBuf, kInfo, 0, 0}) == 0u);
    CHECK(r32(*m, kInfo) == 0x00100008u);
    CHECK(rstr(*m, kInfo + 24) == "SFORCRI CD CRAFT");
    CHECK(r32(*m, kInfo + cvm_info::kNumZones) == 1u);
    CHECK(r32(*m, kInfo + cvm_info::kDataSct) == (0x1000u + 352816u) / 2048u);
    CHECK(r32(*m, kInfo + cvm_info::kZoneTbl) == 0u);
    // its zone form: mode 1 / 2 / 4 -> 0 / 1 / 2 (results 0, -3, -3), others -4; raw 2352 / 2450 sectors
    struct ZoneMode { u8 mode, sel; s32 res; };
    for (const ZoneMode& zm : {ZoneMode{1, 0, 0}, ZoneMode{2, 1, -3}, ZoneMode{4, 2, -3}}) {
        const u8 mode = zm.mode, sel = zm.sel;
        const s32 res = zm.res;
        const u8 mb[4] = {0, 0, 0, mode};
        std::memcpy(m->at(kBuf + 16), mb, 4);
        CHECK(sv(prv(*m, 0x56B300u, Args{kBuf, kZoneInfo, 0, 0})) == res);
        CHECK(r8(*m, kZoneInfo + 5) == sel);
        CHECK(r32(*m, kZoneInfo + 12) == 2352u);
        CHECK(r32(*m, kZoneInfo + 16) == 2450u);
    }
    const u8 bad[4] = {0, 0, 0, 3};
    std::memcpy(m->at(kBuf + 16), bad, 4);
    CHECK(sv(prv(*m, 0x56B300u, Args{kBuf, kZoneInfo, 0, 0})) == -4);
    // sector -> byte offset in a CVMF image: 2048-byte sectors before the second location, 2352 after
    w32(*m, kCvmfLoc + 8, 10);   // second location: sector 10, remainder 16
    w32(*m, kCvmfLoc + 12, 16);
    CHECK(prv(*m, 0x56B918u, Args{12, 0, 0, 0}) == 10u * 2048u + 16u + 2u * 2352u);
    // whole-disc defaults
    CHECK(prv(*m, 0x5675C8u, Args{kInfo, kZoneInfo, 0, 0}) == 0u);
    CHECK(r32(*m, kInfo + cvm_info::kNumZones) == 1u);
    CHECK(r32(*m, kInfo + cvm_info::kDataSct) == 0u);
    CHECK(r32(*m, kZoneInfo + 12) == 2048u);
    CHECK(r32(*m, kZoneInfo + 16) == 2048u);
    CHECK(sv(prv(*m, 0x5675C8u, Args{0, kZoneInfo, 0, 0})) == -100);
    MESSAGE(summary());
}

// The ISO's primary volume descriptor (sector 16) and its root directory record, copied field by field.
TEST_CASE("game(libs4): ISO 9660 -- the disc's volume descriptor and root record copied by the field tables") {
    auto m = machine();
    if (!m) return;
    const std::vector<u8> pvd = read_file(iso_path(), 16 * 2048, 2048);
    if (pvd.empty()) {
        MESSAGE("SKIP: the ISO is not found");
        return;
    }
    REQUIRE(std::memcmp(pvd.data() + 1, "CD001", 5) == 0);
    std::memcpy(m->at(kHdr), pvd.data(), 2048);
    std::memset(m->at(kSect), 0xEE, 2048 + 16);
    prv(*m, 0x56A0A8u, Args{kSect, kHdr, 0, 0});
    CHECK(std::memcmp(m->at(kSect), pvd.data(), 2048) == 0);  // the 39 fields tile the whole sector
    CHECK(r32(*m, kSect + 2048) == 0xEEEEEEEEu);
    // the root directory record (+156): length, extent, size, flags, name
    const u8* dr = pvd.data() + 156;
    CHECK(uv(prv(*m, 0x56A348u, Args{kHdr + 156, 0, 0, 0})) == kRofsCdRec);
    CHECK(r8(*m, kRofsCdRec) == dr[0]);
    u32 ext, siz;
    std::memcpy(&ext, dr + 2, 4);
    std::memcpy(&siz, dr + 10, 4);
    CHECK(r32(*m, kRofsCdRec + 4) == ext);
    CHECK(std::memcmp(m->at(kRofsCdRec + 8), dr + 6, 4) == 0);  // the big-endian copy stays raw
    CHECK(r32(*m, kRofsCdRec + 12) == siz);
    CHECK(std::memcmp(m->at(kRofsCdRec + 16), dr + 14, 4) == 0);
    CHECK(std::memcmp(m->at(kRofsCdRec + 20), dr + 18, 7) == 0);
    CHECK(r8(*m, kRofsCdRec + 27) == dr[25]);
    CHECK((r8(*m, kRofsCdRec + 27) & 2u) != 0u);  // the root is a directory
    CHECK(r8(*m, kRofsCdRec + 34) == dr[32]);
    CHECK(r8(*m, kRofsCdRec + 35) == dr[33]);
    // the path table record copier on the first path table record
    u32 pt_lba;
    std::memcpy(&pt_lba, pvd.data() + 140, 4);
    const std::vector<u8> pt = read_file(iso_path(), u64{pt_lba} * 2048, 64);
    REQUIRE_FALSE(pt.empty());
    std::memcpy(m->at(kBuf), pt.data(), 64);
    CHECK(uv(prv(*m, 0x56A468u, Args{kBuf, 0, 0, 0})) == kRofsCdRec);
    CHECK(r8(*m, kRofsCdRec) == pt[0]);   // name length 1 (the root)
    u32 pext;
    std::memcpy(&pext, pt.data() + 2, 4);
    CHECK(r32(*m, kRofsCdRec + 4) == pext);
    CHECK(pext == ext);                   // the root's extent, as the volume descriptor says
    MESSAGE(summary());
}

// RSU: the hashes against a host model, keys, deciphering twice restores the data, a zero key leaves it.
TEST_CASE("game(libs4): RSU -- the prime hashes, the fixed keys, decipher twice = identity") {
    auto m = machine();
    if (!m) return;
    build_world(*m, 3);
    auto prime = [&](u32 i) { return static_cast<s32>(r16s(*m, kRsuPrimes + 2 * i)); };
    CHECK(prime(0) == 16411);
    auto host_hash = [&](const std::string& s, u32 seed_index) {
        s32 h = prime(seed_index);
        for (char ch : s) {
            const s32 v = h * prime(128 + static_cast<s32>(static_cast<signed char>(ch)));
            h = prime(static_cast<u32>(v % 1024));
        }
        return static_cast<u16>(h);
    };
    for (const std::string s : {"CRI-MW", "ROFS_Seek", "a", "\xC0\xFFxyz"}) {
        wstr(*m, kText1, s);
        prv(*m, 0x56CE88u, Args{kText1, s.size(), kOut, kOut + 2}, tregs(kOut + 4));
        INFO(s);
        CHECK(r16(*m, kOut) == host_hash(s, 256));
        CHECK(r16(*m, kOut + 2) == host_hash(s, 512));
        CHECK(r16(*m, kOut + 4) == host_hash(s, 768));
    }
    prv(*m, 0x56D040u, Args{kOut + 8, kOut + 10, kOut + 12, 0});
    CHECK(r16(*m, kOut + 8) == host_hash("CRI-MW", 256));
    // no string, n <= 0: zeros
    w32(*m, kOut, 0xFFFFFFFFu);
    CHECK(prv(*m, 0x56CE88u, Args{0, 0, kOut, kOut + 2}, tregs(kOut + 4)) == 0u);
    CHECK(r32(*m, kOut) == 0u);
    // big-endian stores
    prv(*m, 0x56D108u, Args{0x12345678u, kOut, 0, 0});
    CHECK(be32(m->at(kOut)) == 0x12345678u);
    prv(*m, 0x56D0D0u, Args{0xABCDu, kOut, 0, 0});
    CHECK(r8(*m, kOut) == 0xAB);
    CHECK(r8(*m, kOut + 1) == 0xCD);
    // a password key is deterministic and non-zero; a header key without the scramble flag is zero
    prv(*m, 0x56D780u, Args{0, kText2, kKeyOut, 0});
    std::vector<u8> k1(m->at(kKeyOut), m->at(kKeyOut) + 8);
    prv(*m, 0x56D780u, Args{0, kText2, kKeyOut, 0});
    CHECK(std::vector<u8>(m->at(kKeyOut), m->at(kKeyOut) + 8) == k1);
    CHECK(std::any_of(k1.begin(), k1.end(), [](u8 b) { return b != 0; }));
    CHECK(sv(prv(*m, 0x56D780u, Args{0, 0, kKeyOut, 0})) == -100);
    CHECK(sv(prv(*m, 0x56D780u, Args{kHdr, 0, 0, 0})) == -100);
    // a scrambled header: flag 0x10 at +48, key strings at +37 / +32 -> a non-zero key
    std::memset(m->at(kBuf), 0, 64);
    w8(*m, kBuf + 51, 0x10);
    std::memcpy(m->at(kBuf + 32), "ABCD", 4);
    std::memcpy(m->at(kBuf + 37), "WXYZ", 4);
    prv(*m, 0x56D780u, Args{kBuf, 0, kKeyOut, 0});
    std::vector<u8> k2(m->at(kKeyOut), m->at(kKeyOut) + 8);
    CHECK(std::any_of(k2.begin(), k2.end(), [](u8 b) { return b != 0; }));
    // decipher twice restores the data (the key stream depends on key and sector only); a zero key leaves it
    std::memcpy(m->at(kKey), k1.data(), 8);
    const std::vector<u8> plain(m->at(kSect), m->at(kSect) + 4096);
    CHECK(prv(*m, 0x56D900u, Args{kSect, 4096, 2048, 77}, tregs(kKey, 8)) == 0u);
    const std::vector<u8> once(m->at(kSect), m->at(kSect) + 4096);
    CHECK(once != plain);
    CHECK(prv(*m, 0x56D900u, Args{kSect, 4096, 2048, 77}, tregs(kKey, 8)) == 0u);
    CHECK(std::vector<u8>(m->at(kSect), m->at(kSect) + 4096) == plain);
    // the sector number matters: another sector gives another stream
    prv(*m, 0x56D900u, Args{kSect, 2048, 2048, 78}, tregs(kKey, 8));
    CHECK(std::memcmp(m->at(kSect), once.data(), 2048) != 0);
    prv(*m, 0x56D900u, Args{kSect, 2048, 2048, 78}, tregs(kKey, 8));
    CHECK(std::vector<u8>(m->at(kSect), m->at(kSect) + 4096) == plain);
    // rfmai_decipherSectors = RSU_Decipher(buf, n << 11, 2048, sector, volume + 36, 8): the same stream as above
    CHECK(prv(*m, 0x569C00u, Args{kKey - 36, kSect, 2, 77}) == 0u);
    CHECK(std::vector<u8>(m->at(kSect), m->at(kSect) + 4096) == once);
    prv(*m, 0x569C00u, Args{kKey - 36, kSect, 2, 77});
    CHECK(std::vector<u8>(m->at(kSect), m->at(kSect) + 4096) == plain);
    std::memset(m->at(kKeyOut), 0, 8);
    CHECK(prv(*m, 0x56D900u, Args{kSect, 4096, 2048, 77}, tregs(kKeyOut, 8)) == 0u);
    CHECK(std::vector<u8>(m->at(kSect), m->at(kSect) + 4096) == plain);
    CHECK(prv(*m, 0x56D968u, Args{kKeyOut, 8, 0, 0}) == 1u);
    CHECK(prv(*m, 0x56D968u, Args{kKey, 8, 0, 0}) == 0u);
    // argument checks: -100
    CHECK(sv(prv(*m, 0x56D900u, Args{0, 4096, 2048, 77}, tregs(kKey, 8))) == -100);
    CHECK(sv(prv(*m, 0x56D900u, Args{kSect, sx64(-1), 2048, 77}, tregs(kKey, 8))) == -100);
    CHECK(sv(prv(*m, 0x56D900u, Args{kSect, 4096, 2048, sx64(-1)}, tregs(kKey, 8))) == -100);
    CHECK(sv(prv(*m, 0x56D900u, Args{kSect, 4096, 2048, 77}, tregs(0, 8))) == -100);
    CHECK(sv(prv(*m, 0x56D900u, Args{kSect, 4096, 2000, 77}, tregs(kKey, 8))) == -100);  // size % sector size
    CHECK(sv(prv(*m, 0x56D900u, Args{kSect, 4096, 2048, 77}, tregs(kKey, 3))) == -100);  // sector size % key size
    CHECK(std::vector<u8>(m->at(kSect), m->at(kSect) + 4096) == plain);
    // the rounds: round n < 9 through the table, else -1000
    CHECK(sv(prv(*m, 0x56D4C0u, Args{kKey, kMask, 9, kKeyOut})) == -1000);
    CHECK(prv(*m, 0x56D4C0u, Args{kKey, kMask, 0, kKeyOut}) == 0u);
    // round 0: out = {k3^m0, k0, k7^m3, k4, k1, k6^m2, k2, k5^m1}
    const u8* k = m->at(kKey);
    const u8* mk = m->at(kMask);
    const u8 r0[8] = {static_cast<u8>(k[3] ^ mk[0]), k[0], static_cast<u8>(k[7] ^ mk[3]), k[4], k[1],
                      static_cast<u8>(k[6] ^ mk[2]), k[2], static_cast<u8>(k[5] ^ mk[1])};
    CHECK(std::memcmp(m->at(kKeyOut), r0, 8) == 0);
    // the version text and init / finish counting
    CHECK(rstr(*m, uv(prv(*m, 0x56D6D8u, Args{0, 0, 0, 0}))).find("RSU Ver.1.10") != std::string::npos);
    w32(*m, kRsuInitCount, 0);
    w32(*m, kRsuUsers, 0);
    prv(*m, 0x56D6E8u, Args{0, 0, 0, 0});
    CHECK(r32(*m, kRsuInitCount) == 1u);
    CHECK(r32(*m, kRsuUsers) == 1u);
    prv(*m, 0x56D6E8u, Args{0, 0, 0, 0});
    CHECK(r32(*m, kRsuUsers) == 1u);
    prv(*m, 0x56D740u, Args{0, 0, 0, 0});
    prv(*m, 0x56D740u, Args{0, 0, 0, 0});
    CHECK(r32(*m, kRsuInitCount) == 0u);
    CHECK(r32(*m, kRsuUsers) == 0u);
    MESSAGE(summary());
}

// The glue next to Sofdec: the callback thunks, the reader record methods, the CFT converter, the ratio compare, the
// PFS lock / wait helpers.
TEST_CASE("game(libs4): the Sofdec glue -- thunks, reader records, the CFT converter, the ratio compare") {
    auto m = machine();
    if (!m) return;
    build_world(*m, 4);
    // the thunks: each calls its slot when set; an empty slot gives 0
    const std::pair<u32, u32> thunks[] = {
        {0x56F510u, 0x7B292Cu}, {0x56F540u, 0x7B2930u}, {0x56F570u, 0x7B2934u}, {0x56F598u, 0x7B2938u},
        {0x56F5C0u, 0x7B293Cu}, {0x56F5F0u, 0x7B2940u}, {0x56F618u, 0x7B2948u}, {0x56F640u, 0x7B2944u},
        {0x56F668u, 0x7B294Cu}, {0x56F690u, 0x7B2950u}, {0x56F6B8u, 0x7B2954u}, {0x56F6E0u, 0x7B2958u},
        {0x56F708u, 0x7B295Cu}, {0x56F730u, 0x7B2960u}, {0x56F758u, 0x7B2964u}, {0x56F780u, 0x7B2968u},
        {0x56F7B0u, 0x7B296Cu}, {0x56F7D8u, 0x7B2970u}, {0x56F800u, 0x7B2974u}, {0x56F828u, 0x7B2978u}};
    g_cb_v0[kCbB] = 0x1234;
    for (const auto& [fn, slot] : thunks) {
        INFO(by_addr(fn).name);
        w32(*m, slot, 0);
        CHECK(prv(*m, fn, Args{0, 0, 0, 0}) == 0u);
        w32(*m, slot, kCbB);
        CHECK(prv(*m, fn, Args{0, 0, 0, 0}) == 0x1234u);
        w32(*m, slot, 0);
    }
    // five globals cleared
    for (u32 a = 0x7B2980u; a <= 0x7B2990u; a += 4) w32(*m, a, 0xAAu);
    prv(*m, 0x56F850u, Args{0, 0, 0, 0});
    for (u32 a = 0x7B2980u; a <= 0x7B2990u; a += 4) CHECK(r32(*m, a) == 0u);
    // the reader record: reset, entries, pairs, the info builder
    prv(*m, 0x56FD58u, Args{kRec, 0, 0, 0});
    CHECK(r32(*m, kRec + 352 + 4 * 53) == 1u);
    CHECK(r32(*m, kRec + 352 + 4 * 31) == 255u);
    CHECK(r32(*m, kRec + 352 + 4 * 19) == 1u);
    CHECK(r32(*m, kRec + 352 + 4 * 100) == 0u);
    prv(*m, 0x56FDE0u, Args{kRec, 2, 7, 8}, tregs(9));
    CHECK(r32(*m, kRec + 280 + 24) == 7u);
    CHECK(r32(*m, kRec + 280 + 28) == 8u);
    CHECK(r32(*m, kRec + 280 + 32) == 9u);
    prv(*m, 0x56FE08u, Args{kRec, 0x31, 0x32, 0});
    w32(*m, kRec + 336, 0x33);
    w32(*m, kOut, 0);
    w32(*m, kOut + 4, 0);
    prv(*m, 0x56FE18u, Args{kRec, kOut, kOut + 4, 0});
    CHECK(r32(*m, kOut) == 0x31u);
    CHECK(r32(*m, kOut + 4) == 0x33u);  // +336, not the pair's second word (+332)
    CHECK(r32(*m, kRec + 332) == 0x32u);
    prv(*m, 0x56FEC0u, Args{kRec, 0, 0, 0});
    CHECK(r32(*m, kRec + 88 + 68) == 1u);
    CHECK(r32(*m, kRec + 88 + 64) == 0u);
    // the methods with a valid handle (the check stand-in returns 0)
    w32(*m, kRec + 352 + 724, 0x4444);
    w32(*m, kOut, 0);
    prv(*m, 0x56FBC0u, Args{kRec, kOut, 0, 0});
    CHECK(r32(*m, kOut) == 0x4444u);
    w32(*m, kRec + 352 + 728, 3);
    CHECK(sv(prv(*m, 0x56FC20u, Args{kRec, kOut, kOut + 4, kOut + 8})) == -1);
    CHECK(r32(*m, kOut) == 3u * 2048u);
    CHECK(r32s(*m, kOut + 8) == -1);
    prv(*m, 0x56F888u, Args{kRec, 0x51, 0x52, 0});
    CHECK(r32(*m, kRec + 4) == 0x51u);
    CHECK(r32(*m, kRec + 8) == 0x52u);
    prv(*m, 0x56FAC0u, Args{kRec, kOut + 0x100, 0, 0});
    CHECK(std::memcmp(m->at(kOut + 0x100), m->at(kRec + 88), 128) == 0);
    prv(*m, 0x56FAC0u, Args{kRec, kOut + 0x204, 0, 0});  // unaligned destination: the other loop, the same bytes
    CHECK(std::memcmp(m->at(kOut + 0x204), m->at(kRec + 88), 128) == 0);
    // the flag-and-call helper
    w32(*m, kRec, kCbA);
    w32(*m, kRec + 4, 0x61);
    g_cb_seen.clear();
    prv(*m, 0x56F9C8u, Args{kRec, 1, 0, 0});
    CHECK(r32(*m, kRec + 8) == 1u);
    CHECK(g_cb_seen.size() == 2u);
    g_cb_seen.clear();
    prv(*m, 0x56F9C8u, Args{kRec, 0, 0, 0});
    CHECK(g_cb_seen.empty());
    // the CFT converter: one 16 x 16 block, every fourth source byte through the table; the source pointer is
    // advanced by a column of blocks ((height / 16) x 1024 bytes) before the first read
    std::memset(m->at(kDst), 0, 1024 + 64);
    prv(*m, 0x56DF40u, Args{kSrcPtr, kDesc, kLut, 0});
    for (u32 y = 0; y < 16; ++y)
        for (u32 x = 0; x < 16; ++x) {
            const u8 idx = r8(*m, kPix + 1024 + 64 * y + 4 * x);
            INFO("pixel " << x << "," << y);
            CHECK(r32(*m, kDst + 4 * (16 * y + x)) == r32(*m, kLut + 4u * idx));
        }
    CHECK(r32(*m, kDst + 1024) == 0u);
    // the ratio compare: a2 x a1 >= a0 x a3 in 64 bits
    CHECK(prv(*m, 0x56F4B8u, Args{1, 2, 1, 2}) == 1u);
    CHECK(prv(*m, 0x56F4B8u, Args{3, 4, 5, 6}) == 1u);   // 20 >= 18
    CHECK(prv(*m, 0x56F4B8u, Args{5, 4, 3, 6}) == 0u);   // 12 < 30
    CHECK(prv(*m, 0x56F4B8u, Args{0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFF, 0x7FFFFFFE}) == 1u);  // no 32-bit overflow
    // CFT's global word: its address, set, get
    prv(*m, 0x56DED0u, Args{0x5A5A, 0, 0, 0});
    CHECK(r32(*m, kCftWork) == 0x5A5Au);
    CHECK(prv(*m, 0x56DEF8u, Args{0, 0, 0, 0}) == 0x5A5Au);
    CHECK(prv(*m, 0x56DEC0u, Args{0, 0, 0, 0}) == kCftWork);
    // the PFS lock: a free lock word -> locked, 0; the wait helpers return 0 after 7,551 iterations
    CHECK(prv(*m, 0x56DD80u, Args{0, 0, 0, 0}) == 1u);
    CHECK(prv(*m, 0x56AB90u, Args{0, 0, 0, 0}) == 0u);
    prv(*m, 0x56ABE0u, Args{0, 0, 0, 0});
    CHECK(prv(*m, 0x56DDF8u, Args{0, 0, 0, 0}) == 0u);
    CHECK(prv(*m, 0x56AB78u, Args{0, 0, 0, 0}) == 0u);
    // ROCI: the version text noted, the method table
    CHECK(prv(*m, 0x56C888u, Args{0, 0, 0, 0}) == kRociVtbl);
    CHECK(rstr(*m, r32(*m, 0x99B240u)).find("ROCI Ver.1.15") != std::string::npos);
    CHECK(prv(*m, 0x56CA08u, Args{0, 0, 0, 0}) == 2048u);
    CHECK(prv(*m, 0x5658A8u, Args{0, 0, 0, 0}) == kPfsCvfsTbl);
    MESSAGE(summary());
}

#else

TEST_CASE("game(libs4): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
