// Pair tests of slice sce1 (game/src/sce/sce_*.cpp): the pure parts of the Sony runtime libraries. Every pair runs the
// hand body and its recompiled body from the same guest machine through tests/game/handgen_pairs.h -- the whole register
// file and the cycle count at every check point and at the return / stop, all 32 MiB of RAM (write-tracked), the
// scratchpad, the BIOS window, the bus log -- on two identical stand-in worlds (tests/game/stand_ins.h) whose call logs
// must match: the callees no test build emits (sceOpen / sceRead / sceClose, _sce_GetGsDxDyOffset, scePrintf, Exit,
// kputs, kputchar, fptodp, strncmp) are served by recorders or by custom stand-ins; __fixunssfdi runs (slice unblock
// replaced it) and sub_50EFA8's result is checked instead of a call count.
//
// Inputs and documented-rule checks (public PS2 hardware documentation; no SDK material):
//   * the draw environments (both contexts) against the GS register formats FRAME / ZBUF / XYOFFSET / SCISSOR /
//     PRMODECONT / COLCLAMP / DTHE / TEST, over pixel formats, sizes, Z modes and field / frame modes, and the Z-buffer
//     page against the 64 x 32 / 64 x 64 page geometry; the store-image packet against the VIF codes (MSKPATH3, FLUSHA,
//     DIRECT), the GIF tag and BITBLTBUF / TRXPOS / TRXREG / FINISH / TRXDIR;
//   * the dorm snapshot's four live draw environments (SkyStart's calls, docs/RUNTIME_CONTRACT.md B-50) rebuilt and
//     compared doubleword for doubleword, minus SkyStart's later patches;
//   * the display environment for NTSC / PAL (field, frame, progressive), 480p (with and without the newer-ROM offsets)
//     and an unknown mode against PMODE / SMODE2 / DISPFB / DISPLAY / BGCOLOR; checkModelVersion on ROMVER texts;
//   * libdma's address mapping and memclr, the newlib stubs and errno; the tty ring against a host ring, sceTtyRead,
//     the DECI2 line buffer and the serial CR LF;
//     sceVsnprintf / sceSnprintf against the host snprintf;
//   * the SIF tables, the alarm pool (allocation ids, the sorted pending list, unlink, free with bad ids), the bus-clock
//     conversions against host u64 maths and host floats (within one ulp), the module version checks;
//   * libmc2's helpers against host string models and a host glob matcher.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/sce.h"

#include <algorithm>
#include <array>
#include <bit>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
namespace sce = p3fes::game::sce;

namespace p3fes::recomp_gen {
void fn_checkModelVersion_004f90b8(EEContext&);  // generated body
void fn_checkModelVersion_004f90b8__recomp(EEContext&);  // recompiled
void fn_sceGsSetDefDispEnv_004f9168(EEContext&);  // generated body
void fn_sceGsSetDefDispEnv_004f9168__recomp(EEContext&);  // recompiled
void fn_sceGszbufaddr_004f95a0(EEContext&);  // generated body
void fn_sceGszbufaddr_004f95a0__recomp(EEContext&);  // recompiled
void fn_sceGsSetDefDrawEnv_004f9668(EEContext&);  // generated body
void fn_sceGsSetDefDrawEnv_004f9668__recomp(EEContext&);  // recompiled
void fn_sceGsSetDefStoreImage_004f9ce8(EEContext&);  // generated body
void fn_sceGsSetDefStoreImage_004f9ce8__recomp(EEContext&);  // recompiled
void fn_sceGsSetDefDrawEnv2_004fa558(EEContext&);  // generated body
void fn_sceGsSetDefDrawEnv2_004fa558__recomp(EEContext&);  // recompiled
void fn_CheckAddress_004fa890(EEContext&);  // generated body
void fn_CheckAddress_004fa890__recomp(EEContext&);  // recompiled
void fn_memclr_004fa8b8(EEContext&);  // generated body
void fn_memclr_004fa8b8__recomp(EEContext&);  // recompiled
void fn_sceDmaGetEnv_004fabd0(EEContext&);  // generated body
void fn_sceDmaGetEnv_004fabd0__recomp(EEContext&);  // recompiled
void fn_open_00503820(EEContext&);  // generated body
void fn_open_00503820__recomp(EEContext&);  // recompiled
void fn_close_00503848(EEContext&);  // generated body
void fn_close_00503848__recomp(EEContext&);  // recompiled
void fn_ioctl_00503850(EEContext&);  // generated body
void fn_ioctl_00503850__recomp(EEContext&);  // recompiled
void fn_lseek_00503858(EEContext&);  // generated body
void fn_lseek_00503858__recomp(EEContext&);  // recompiled
void fn_isatty_00503910(EEContext&);  // generated body
void fn_isatty_00503910__recomp(EEContext&);  // recompiled
void fn_fstat_00503918(EEContext&);  // generated body
void fn_fstat_00503918__recomp(EEContext&);  // recompiled
void fn_getpid_00503930(EEContext&);  // generated body
void fn_getpid_00503930__recomp(EEContext&);  // recompiled
void fn_kill_00503938(EEContext&);  // generated body
void fn_kill_00503938__recomp(EEContext&);  // recompiled
void fn_stat_00503960(EEContext&);  // generated body
void fn_stat_00503960__recomp(EEContext&);  // recompiled
void fn_unlink_00503988(EEContext&);  // generated body
void fn_unlink_00503988__recomp(EEContext&);  // recompiled
void fn_sceResetttyinit_005035e0(EEContext&);  // generated body
void fn_sceResetttyinit_005035e0__recomp(EEContext&);  // recompiled
void fn_QueueInit_00504678(EEContext&);  // generated body
void fn_QueueInit_00504678__recomp(EEContext&);  // recompiled
void fn_QueuePeekWriteDone_005046a0(EEContext&);  // generated body
void fn_QueuePeekWriteDone_005046a0__recomp(EEContext&);  // recompiled
void fn_QueuePeekReadDone_005046e0(EEContext&);  // generated body
void fn_QueuePeekReadDone_005046e0__recomp(EEContext&);  // recompiled
void fn_sceTtyRead_00504a30(EEContext&);  // generated body
void fn_sceTtyRead_00504a30__recomp(EEContext&);  // recompiled
void fn_deci2Putchar_00504bf8(EEContext&);  // generated body
void fn_deci2Putchar_00504bf8__recomp(EEContext&);  // recompiled
void fn_serialPutchar_00504ca8(EEContext&);  // generated body
void fn_serialPutchar_00504ca8__recomp(EEContext&);  // recompiled
void fn_ftoi_00504ce0(EEContext&);  // generated body
void fn_ftoi_00504ce0__recomp(EEContext&);  // recompiled
void fn_printfloat_00504d70(EEContext&);  // generated body
void fn_printfloat_00504d70__recomp(EEContext&);  // recompiled
void fn__sceSnprintf_00504f48(EEContext&);  // generated body
void fn__sceSnprintf_00504f48__recomp(EEContext&);  // recompiled
void fn_snprintf_char_00505c60(EEContext&);  // generated body
void fn_snprintf_char_00505c60__recomp(EEContext&);  // recompiled
void fn_printf_char_00505cb8(EEContext&);  // generated body
void fn_printf_char_00505cb8__recomp(EEContext&);  // recompiled
void fn_kprintf_char_00505ce0(EEContext&);  // generated body
void fn_kprintf_char_00505ce0__recomp(EEContext&);  // recompiled
void fn__sceSnprintf_pf_00505d08(EEContext&);  // generated body
void fn__sceSnprintf_pf_00505d08__recomp(EEContext&);  // recompiled
void fn_sceVsnprintf_00505d58(EEContext&);  // generated body
void fn_sceVsnprintf_00505d58__recomp(EEContext&);  // recompiled
void fn_sceSnprintf_00505d90(EEContext&);  // generated body
void fn_sceSnprintf_00505d90__recomp(EEContext&);  // recompiled
void fn__set_sreg_00505f48(EEContext&);  // generated body
void fn__set_sreg_00505f48__recomp(EEContext&);  // recompiled
void fn__change_addr_00505f68(EEContext&);  // generated body
void fn__change_addr_00505f68__recomp(EEContext&);  // recompiled
void fn_sceSifGetSreg_00505f78(EEContext&);  // generated body
void fn_sceSifGetSreg_00505f78__recomp(EEContext&);  // recompiled
void fn_sceSifSetSreg_00505f90(EEContext&);  // generated body
void fn_sceSifSetSreg_00505f90__recomp(EEContext&);  // recompiled
void fn_sceSifGetDataTable_00505fb0(EEContext&);  // generated body
void fn_sceSifGetDataTable_00505fb0__recomp(EEContext&);  // recompiled
void fn_sub_506400_00506400(EEContext&);  // generated body
void fn_sub_506400_00506400__recomp(EEContext&);  // recompiled
void fn_sub_506418_00506418(EEContext&);  // generated body
void fn_sub_506418_00506418__recomp(EEContext&);  // recompiled
void fn_sub_506430_00506430(EEContext&);  // generated body
void fn_sub_506430_00506430__recomp(EEContext&);  // recompiled
void fn___sceKernlGetEhSemaId_0050d468(EEContext&);  // generated body
void fn___sceKernlGetEhSemaId_0050d468__recomp(EEContext&);  // recompiled
void fn_sub_50D840_0050d840(EEContext&);  // generated body
void fn_sub_50D840_0050d840__recomp(EEContext&);  // recompiled
void fn_nullsub_131_0050dc78(EEContext&);  // generated body
void fn_nullsub_131_0050dc78__recomp(EEContext&);  // recompiled
void fn_sub_50E190_0050e190(EEContext&);  // generated body
void fn_sub_50E190_0050e190__recomp(EEContext&);  // recompiled
void fn_sub_50E218_0050e218(EEContext&);  // generated body
void fn_sub_50E218_0050e218__recomp(EEContext&);  // recompiled
void fn_sub_50E5D8_0050e5d8(EEContext&);  // generated body
void fn_sub_50E5D8_0050e5d8__recomp(EEContext&);  // recompiled
void fn_sub_50E690_0050e690(EEContext&);  // generated body
void fn_sub_50E690_0050e690__recomp(EEContext&);  // recompiled
void fn_sub_50E7A0_0050e7a0(EEContext&);  // generated body
void fn_sub_50E7A0_0050e7a0__recomp(EEContext&);  // recompiled
void fn_sub_50EB50_0050eb50(EEContext&);  // generated body
void fn_sub_50EB50_0050eb50__recomp(EEContext&);  // recompiled
void fn_sub_50EE38_0050ee38(EEContext&);  // generated body
void fn_sub_50EE38_0050ee38__recomp(EEContext&);  // recompiled
void fn_sub_50EEE0_0050eee0(EEContext&);  // generated body
void fn_sub_50EEE0_0050eee0__recomp(EEContext&);  // recompiled
void fn_sub_50EF50_0050ef50(EEContext&);  // generated body
void fn_sub_50EF50_0050ef50__recomp(EEContext&);  // recompiled
void fn_sub_50EFA8_0050efa8(EEContext&);  // generated body
void fn_sub_50EFA8_0050efa8__recomp(EEContext&);  // recompiled
void fn__InitAlarm_0050efe0(EEContext&);  // generated body
void fn__InitAlarm_0050efe0__recomp(EEContext&);  // recompiled
void fn_AlarmHandler_0050f030(EEContext&);  // generated body
void fn_AlarmHandler_0050f030__recomp(EEContext&);  // recompiled
void fn__fs_version_00508378(EEContext&);  // generated body
void fn__fs_version_00508378__recomp(EEContext&);  // recompiled
void fn__lf_version_0050bbe8(EEContext&);  // generated body
void fn__lf_version_0050bbe8__recomp(EEContext&);  // recompiled
void fn_instr_00514d50(EEContext&);  // generated body
void fn_instr_00514d50__recomp(EEContext&);  // recompiled
void fn_isCorrNameSize_00514db0(EEContext&);  // generated body
void fn_isCorrNameSize_00514db0__recomp(EEContext&);  // recompiled
void fn_isCorrFname_00514e20(EEContext&);  // generated body
void fn_isCorrFname_00514e20__recomp(EEContext&);  // recompiled
void fn_isPathCurParent_00514e78(EEContext&);  // generated body
void fn_isPathCurParent_00514e78__recomp(EEContext&);  // recompiled
void fn_isWildFit_00514f30(EEContext&);  // generated body
void fn_isWildFit_00514f30__recomp(EEContext&);  // recompiled
void fn__strtok_005150b0(EEContext&);  // generated body
void fn__strtok_005150b0__recomp(EEContext&);  // recompiled
void fn__get_dir_nest_005151d0(EEContext&);  // generated body
void fn__get_dir_nest_005151d0__recomp(EEContext&);  // recompiled
void fn__make_path_00515218(EEContext&);  // generated body
void fn__make_path_00515218__recomp(EEContext&);  // recompiled
void fn__get_free_slot_0051c0f8(EEContext&);  // generated body
void fn__get_free_slot_0051c0f8__recomp(EEContext&);  // recompiled
void fn_DPRINT_0051d588(EEContext&);  // generated body
void fn_DPRINT_0051d588__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"checkModelVersion", 0x4F90B8, &recomp_gen::fn_checkModelVersion_004f90b8, &recomp_gen::fn_checkModelVersion_004f90b8__recomp},
    {"sceGsSetDefDispEnv", 0x4F9168, &recomp_gen::fn_sceGsSetDefDispEnv_004f9168, &recomp_gen::fn_sceGsSetDefDispEnv_004f9168__recomp},
    {"sceGszbufaddr", 0x4F95A0, &recomp_gen::fn_sceGszbufaddr_004f95a0, &recomp_gen::fn_sceGszbufaddr_004f95a0__recomp},
    {"sceGsSetDefDrawEnv", 0x4F9668, &recomp_gen::fn_sceGsSetDefDrawEnv_004f9668, &recomp_gen::fn_sceGsSetDefDrawEnv_004f9668__recomp},
    {"sceGsSetDefStoreImage", 0x4F9CE8, &recomp_gen::fn_sceGsSetDefStoreImage_004f9ce8, &recomp_gen::fn_sceGsSetDefStoreImage_004f9ce8__recomp},
    {"sceGsSetDefDrawEnv2", 0x4FA558, &recomp_gen::fn_sceGsSetDefDrawEnv2_004fa558, &recomp_gen::fn_sceGsSetDefDrawEnv2_004fa558__recomp},
    {"CheckAddress", 0x4FA890, &recomp_gen::fn_CheckAddress_004fa890, &recomp_gen::fn_CheckAddress_004fa890__recomp},
    {"memclr", 0x4FA8B8, &recomp_gen::fn_memclr_004fa8b8, &recomp_gen::fn_memclr_004fa8b8__recomp},
    {"sceDmaGetEnv", 0x4FABD0, &recomp_gen::fn_sceDmaGetEnv_004fabd0, &recomp_gen::fn_sceDmaGetEnv_004fabd0__recomp},
    {"open", 0x503820, &recomp_gen::fn_open_00503820, &recomp_gen::fn_open_00503820__recomp},
    {"close", 0x503848, &recomp_gen::fn_close_00503848, &recomp_gen::fn_close_00503848__recomp},
    {"ioctl", 0x503850, &recomp_gen::fn_ioctl_00503850, &recomp_gen::fn_ioctl_00503850__recomp},
    {"lseek", 0x503858, &recomp_gen::fn_lseek_00503858, &recomp_gen::fn_lseek_00503858__recomp},
    {"isatty", 0x503910, &recomp_gen::fn_isatty_00503910, &recomp_gen::fn_isatty_00503910__recomp},
    {"fstat", 0x503918, &recomp_gen::fn_fstat_00503918, &recomp_gen::fn_fstat_00503918__recomp},
    {"getpid", 0x503930, &recomp_gen::fn_getpid_00503930, &recomp_gen::fn_getpid_00503930__recomp},
    {"kill", 0x503938, &recomp_gen::fn_kill_00503938, &recomp_gen::fn_kill_00503938__recomp},
    {"stat", 0x503960, &recomp_gen::fn_stat_00503960, &recomp_gen::fn_stat_00503960__recomp},
    {"unlink", 0x503988, &recomp_gen::fn_unlink_00503988, &recomp_gen::fn_unlink_00503988__recomp},
    {"sceResetttyinit", 0x5035E0, &recomp_gen::fn_sceResetttyinit_005035e0, &recomp_gen::fn_sceResetttyinit_005035e0__recomp},
    {"QueueInit", 0x504678, &recomp_gen::fn_QueueInit_00504678, &recomp_gen::fn_QueueInit_00504678__recomp},
    {"QueuePeekWriteDone", 0x5046A0, &recomp_gen::fn_QueuePeekWriteDone_005046a0, &recomp_gen::fn_QueuePeekWriteDone_005046a0__recomp},
    {"QueuePeekReadDone", 0x5046E0, &recomp_gen::fn_QueuePeekReadDone_005046e0, &recomp_gen::fn_QueuePeekReadDone_005046e0__recomp},
    {"sceTtyRead", 0x504A30, &recomp_gen::fn_sceTtyRead_00504a30, &recomp_gen::fn_sceTtyRead_00504a30__recomp},
    {"deci2Putchar", 0x504BF8, &recomp_gen::fn_deci2Putchar_00504bf8, &recomp_gen::fn_deci2Putchar_00504bf8__recomp},
    {"serialPutchar", 0x504CA8, &recomp_gen::fn_serialPutchar_00504ca8, &recomp_gen::fn_serialPutchar_00504ca8__recomp},
    {"ftoi", 0x504CE0, &recomp_gen::fn_ftoi_00504ce0, &recomp_gen::fn_ftoi_00504ce0__recomp},
    {"printfloat", 0x504D70, &recomp_gen::fn_printfloat_00504d70, &recomp_gen::fn_printfloat_00504d70__recomp},
    {"_sceSnprintf", 0x504F48, &recomp_gen::fn__sceSnprintf_00504f48, &recomp_gen::fn__sceSnprintf_00504f48__recomp},
    {"snprintf_char", 0x505C60, &recomp_gen::fn_snprintf_char_00505c60, &recomp_gen::fn_snprintf_char_00505c60__recomp},
    {"printf_char", 0x505CB8, &recomp_gen::fn_printf_char_00505cb8, &recomp_gen::fn_printf_char_00505cb8__recomp},
    {"kprintf_char", 0x505CE0, &recomp_gen::fn_kprintf_char_00505ce0, &recomp_gen::fn_kprintf_char_00505ce0__recomp},
    {"_sceSnprintf_pf", 0x505D08, &recomp_gen::fn__sceSnprintf_pf_00505d08, &recomp_gen::fn__sceSnprintf_pf_00505d08__recomp},
    {"sceVsnprintf", 0x505D58, &recomp_gen::fn_sceVsnprintf_00505d58, &recomp_gen::fn_sceVsnprintf_00505d58__recomp},
    {"sceSnprintf", 0x505D90, &recomp_gen::fn_sceSnprintf_00505d90, &recomp_gen::fn_sceSnprintf_00505d90__recomp},
    {"_set_sreg", 0x505F48, &recomp_gen::fn__set_sreg_00505f48, &recomp_gen::fn__set_sreg_00505f48__recomp},
    {"_change_addr", 0x505F68, &recomp_gen::fn__change_addr_00505f68, &recomp_gen::fn__change_addr_00505f68__recomp},
    {"sceSifGetSreg", 0x505F78, &recomp_gen::fn_sceSifGetSreg_00505f78, &recomp_gen::fn_sceSifGetSreg_00505f78__recomp},
    {"sceSifSetSreg", 0x505F90, &recomp_gen::fn_sceSifSetSreg_00505f90, &recomp_gen::fn_sceSifSetSreg_00505f90__recomp},
    {"sceSifGetDataTable", 0x505FB0, &recomp_gen::fn_sceSifGetDataTable_00505fb0, &recomp_gen::fn_sceSifGetDataTable_00505fb0__recomp},
    {"sub_506400", 0x506400, &recomp_gen::fn_sub_506400_00506400, &recomp_gen::fn_sub_506400_00506400__recomp},
    {"sub_506418", 0x506418, &recomp_gen::fn_sub_506418_00506418, &recomp_gen::fn_sub_506418_00506418__recomp},
    {"sub_506430", 0x506430, &recomp_gen::fn_sub_506430_00506430, &recomp_gen::fn_sub_506430_00506430__recomp},
    {"__sceKernlGetEhSemaId", 0x50D468, &recomp_gen::fn___sceKernlGetEhSemaId_0050d468, &recomp_gen::fn___sceKernlGetEhSemaId_0050d468__recomp},
    {"sub_50D840", 0x50D840, &recomp_gen::fn_sub_50D840_0050d840, &recomp_gen::fn_sub_50D840_0050d840__recomp},
    {"nullsub_131", 0x50DC78, &recomp_gen::fn_nullsub_131_0050dc78, &recomp_gen::fn_nullsub_131_0050dc78__recomp},
    {"sub_50E190", 0x50E190, &recomp_gen::fn_sub_50E190_0050e190, &recomp_gen::fn_sub_50E190_0050e190__recomp},
    {"sub_50E218", 0x50E218, &recomp_gen::fn_sub_50E218_0050e218, &recomp_gen::fn_sub_50E218_0050e218__recomp},
    {"sub_50E5D8", 0x50E5D8, &recomp_gen::fn_sub_50E5D8_0050e5d8, &recomp_gen::fn_sub_50E5D8_0050e5d8__recomp},
    {"sub_50E690", 0x50E690, &recomp_gen::fn_sub_50E690_0050e690, &recomp_gen::fn_sub_50E690_0050e690__recomp},
    {"sub_50E7A0", 0x50E7A0, &recomp_gen::fn_sub_50E7A0_0050e7a0, &recomp_gen::fn_sub_50E7A0_0050e7a0__recomp},
    {"sub_50EB50", 0x50EB50, &recomp_gen::fn_sub_50EB50_0050eb50, &recomp_gen::fn_sub_50EB50_0050eb50__recomp},
    {"sub_50EE38", 0x50EE38, &recomp_gen::fn_sub_50EE38_0050ee38, &recomp_gen::fn_sub_50EE38_0050ee38__recomp},
    {"sub_50EEE0", 0x50EEE0, &recomp_gen::fn_sub_50EEE0_0050eee0, &recomp_gen::fn_sub_50EEE0_0050eee0__recomp},
    {"sub_50EF50", 0x50EF50, &recomp_gen::fn_sub_50EF50_0050ef50, &recomp_gen::fn_sub_50EF50_0050ef50__recomp},
    {"sub_50EFA8", 0x50EFA8, &recomp_gen::fn_sub_50EFA8_0050efa8, &recomp_gen::fn_sub_50EFA8_0050efa8__recomp},
    {"_InitAlarm", 0x50EFE0, &recomp_gen::fn__InitAlarm_0050efe0, &recomp_gen::fn__InitAlarm_0050efe0__recomp},
    {"AlarmHandler", 0x50F030, &recomp_gen::fn_AlarmHandler_0050f030, &recomp_gen::fn_AlarmHandler_0050f030__recomp},
    {"_fs_version", 0x508378, &recomp_gen::fn__fs_version_00508378, &recomp_gen::fn__fs_version_00508378__recomp},
    {"_lf_version", 0x50BBE8, &recomp_gen::fn__lf_version_0050bbe8, &recomp_gen::fn__lf_version_0050bbe8__recomp},
    {"instr", 0x514D50, &recomp_gen::fn_instr_00514d50, &recomp_gen::fn_instr_00514d50__recomp},
    {"isCorrNameSize", 0x514DB0, &recomp_gen::fn_isCorrNameSize_00514db0, &recomp_gen::fn_isCorrNameSize_00514db0__recomp},
    {"isCorrFname", 0x514E20, &recomp_gen::fn_isCorrFname_00514e20, &recomp_gen::fn_isCorrFname_00514e20__recomp},
    {"isPathCurParent", 0x514E78, &recomp_gen::fn_isPathCurParent_00514e78, &recomp_gen::fn_isPathCurParent_00514e78__recomp},
    {"isWildFit", 0x514F30, &recomp_gen::fn_isWildFit_00514f30, &recomp_gen::fn_isWildFit_00514f30__recomp},
    {"_strtok", 0x5150B0, &recomp_gen::fn__strtok_005150b0, &recomp_gen::fn__strtok_005150b0__recomp},
    {"_get_dir_nest", 0x5151D0, &recomp_gen::fn__get_dir_nest_005151d0, &recomp_gen::fn__get_dir_nest_005151d0__recomp},
    {"_make_path", 0x515218, &recomp_gen::fn__make_path_00515218, &recomp_gen::fn__make_path_00515218__recomp},
    {"_get_free_slot", 0x51C0F8, &recomp_gen::fn__get_free_slot_0051c0f8, &recomp_gen::fn__get_free_slot_0051c0f8__recomp},
    {"DPRINT", 0x51D588, &recomp_gen::fn_DPRINT_0051d588, &recomp_gen::fn_DPRINT_0051d588__recomp},
};

// The random worlds of the first case: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;
constexpr u32 kOut = 0x01F40000u;  // free in the ELF image and every snapshot (stand_ins.h)

// The callees of this slice that no test build emits, served by stand-ins in every pair: IOP file requests, kernel
// calls, the DECI2 / SIO output, soft-float helpers kept recompiled by the libc slice.
constexpr u32 kSceOpen = 0x508670u, kSceRead = 0x508CB8u, kSceClose = 0x508900u, kGetDxDy = 0x4F9158u;
constexpr u32 kScePrintf = 0x505E48u, kExit = 0x50DA58u, kKputs = 0x504650u, kKputchar = 0x504BC0u;
// (__fixunssfdi 0x52EDA0, fptodp 0x530DA0 and strncmp 0x524670 are replaced and run: not stood in)

// --- the pair runner of this file ---------------------------------------------------------------------------------
// hgp::pair (handgen_pairs.h) through two trampolines that set chosen FPRs after the random register file and give
// each body a fresh, identical stand-in world (the recorders above plus any custom stand-in of the case) whose call
// logs must match.
struct Tramp {
    Fn fn[2] = {};
    std::unique_ptr<StandInWorld> world[2];
    std::map<unsigned, u32> fpr;
    std::vector<std::tuple<u32, std::string, StandInFn>> customs;
};
Tramp g_t;
int g_pairs = 0;
int g_stops = 0;

void install_recorders(StandInWorld& w) {
    w.si.install_recorder(kSceOpen, "sceOpen", 3);
    w.si.install_recorder(kSceRead, "sceRead", 1);
    w.si.install_recorder(kSceClose, "sceClose", 0);
    w.si.install_recorder(kGetDxDy, "_sce_GetGsDxDyOffset", 0);
    w.si.install_recorder(kScePrintf, "scePrintf", 0);
    w.si.install_recorder(kExit, "Exit", 0);
    w.si.install_recorder(kKputs, "kputs", 0);
    w.si.install_recorder(kKputchar, "kputchar", 0);
    // __fixunssfdi (0x52EDA0) is not stood in: it runs (hand-written since slice unblock), and its result is checked.
    // fptodp and strncmp are replaced too and run: their stand-ins here were never served, and since the hooked
    // forwarders (2026-10-29) they would be, so they are gone (the pairs run as they always did).
}

template <int K>
void tramp(EEContext& c) {
    for (const auto& [i, v] : g_t.fpr) c.fpr[i] = v;
    g_t.world[K] = std::make_unique<StandInWorld>();
    install_recorders(*g_t.world[K]);
    for (const auto& [va, name, fn] : g_t.customs) g_t.world[K]->si.install(va, name, fn);
    StandInsScope scope(g_t.world[K]->si);
    g_t.fn[K](c);
}

const Case& by_name(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

struct Opt {
    std::map<unsigned, u64> gpr_in;  // $t0.. (arguments 5..8)
    std::map<unsigned, u32> fpr;     // $f12..
    std::vector<std::tuple<u32, std::string, StandInFn>> customs;
};

hgp::Run sce_pair(Machine& m, const char* name, const Args& a, u32 seed, const std::string& what, const Opt& o = {}) {
    const Case& c = by_name(name);
    g_t.fn[0] = c.hand;
    g_t.fn[1] = c.recomp;
    g_t.fpr = o.fpr;
    g_t.customs = o.customs;
    HwCheck hw;
    hw.gpr_in = o.gpr_in;
    hgp::Run r = hgp::pair(m, &tramp<0>, &tramp<1>, a, seed, what.c_str(), hw);
    if (g_t.world[0] && g_t.world[1]) expect_same_log(g_t.world[0]->si, g_t.world[1]->si, what.c_str());
    ++g_pairs;
    if (r.stopped) {
        ++g_stops;
        MESSAGE(what << ": both bodies stopped at " << hex64(r.stop_pc) << " (" << r.what << ")");
    }
    return r;
}
u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
s32 v0s(const hgp::Run& r) { return static_cast<s32>(r.end.gpr[GPR_V0].u64[0]); }
const StandIns& log_of() { return g_t.world[1]->si; }

// --- guest memory helpers -------------------------------------------------------------------------------------------
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + (va & 0x1FFFFFFu), 4);
    return v;
}
u64 r64(const Machine& m, u32 va) {
    u64 v;
    std::memcpy(&v, m.mem.main_ram() + (va & 0x1FFFFFFu), 8);
    return v;
}
u8 r8(const Machine& m, u32 va) { return m.mem.main_ram()[va & 0x1FFFFFFu]; }
void w64(Machine& m, u32 va, u64 v) { std::memcpy(m.at(va), &v, 8); }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void wstr(Machine& m, u32 va, const std::string& s) {
    std::memcpy(m.at(va), s.data(), s.size());
    *m.at(va + static_cast<u32>(s.size())) = 0;
}
void wzero(Machine& m, u32 va, u32 n) { std::memset(m.at(va), 0, n); }
std::string gstr(const Machine& m, u32 va, u32 max = 512) { return m.str(va, max); }
u32 fbits(float f) { return std::bit_cast<u32>(f); }
float ffrom(u32 b) { return std::bit_cast<float>(b); }

void set_gparam(Machine& m, u16 interlace, u16 omode, u16 ffmode) {
    w16(m, sce::gparam::kAddr + sce::gparam::kInterlace, interlace);
    w16(m, sce::gparam::kAddr + sce::gparam::kOmode, omode);
    w16(m, sce::gparam::kAddr + sce::gparam::kFfmode, ffmode);
}

// --- host models of the GS register images (public GS documentation) -------------------------------------------------
s64 zbp_model(s32 psm, s32 w, s32 h, bool field) {
    const s32 px = (w + 63) / 64;
    const s32 py = (psm & 2) ? (h + 63) / 64 : (h + 31) / 32;
    const s32 n = px * py;
    return static_cast<s16>(field ? n : n << 1);
}
struct DrawEnvModel {
    u64 data[8];
    u64 addr[8];
};
DrawEnvModel draw_model(bool ctx2, s32 psm, s32 w, s32 h, s32 ztest, s32 zpsm, bool field, const u64 old[8]) {
    DrawEnvModel e{};
    const u64 fbw = ctx2 ? static_cast<u64>((w >> 6) & 0x3F) : static_cast<u64>(((w + 63) >> 6) & 0x3F);
    e.data[0] = fbw << 16 | static_cast<u64>(psm & 0xF) << 24;                        // FRAME: FBP 0, FBW, PSM
    e.data[1] = static_cast<u64>(zbp_model(psm, w, h, field)) | static_cast<u64>(zpsm & 0xF) << 24 |
                (ztest == 0 ? 1ull << 32 : 0);                                        // ZBUF: ZBP, PSM, ZMSK
    e.data[2] = static_cast<u64>(static_cast<s64>(2048 - static_cast<s16>(w >> 1)) * 16) |
                static_cast<u64>(static_cast<s64>(2048 - static_cast<s16>(h >> 1))) << 36;  // XYOFFSET (12.4)
    e.data[3] = static_cast<u64>(static_cast<s64>(w - 1)) << 16 | static_cast<u64>(static_cast<s64>(h - 1)) << 48;  // SCISSOR
    e.data[4] = old[4] | 1;                                                           // PRMODECONT.AC
    e.data[5] = old[5] | 1;                                                           // COLCLAMP.CLAMP
    e.data[6] = (psm & 2) ? old[6] | 1 : old[6] & ~1ull;                              // DTHE for 16-bit formats
    e.data[7] = ztest ? (static_cast<u64>(ztest & 3) << 17 | 0x10000) : 0x30000;      // TEST: ZTE, ZTST
    const u64 a1[8] = {0x4C, 0x4E, 0x18, 0x40, 0x1A, 0x46, 0x45, 0x47};
    const u64 a2[8] = {0x4D, 0x4F, 0x19, 0x41, 0x1A, 0x46, 0x45, 0x48};
    for (int i = 0; i < 8; ++i) e.addr[i] = ctx2 ? a2[i] : a1[i];
    return e;
}

// sceGsSetDefDispEnv's DISPLAY / SMODE2 for a mode (the offsets are the four stack words)
struct DispModel {
    u64 pmode, smode2, dispfb, display, bgcolor;
    bool display_set;
};
DispModel disp_model(u16 interlace, u16 omode, u16 ffmode, s32 psm, s32 w, s32 h, s32 dx, s32 dy, const s32 off[4]) {
    DispModel d{};
    d.pmode = 0x66;
    d.smode2 = interlace == 0 ? 2 : (ffmode != 0 ? 3 : 1);
    d.dispfb = static_cast<u64>(((w + 63) >> 6) & 0x3F) << 9 | static_cast<u64>(psm & 0xF) << 15;
    d.bgcolor = 0;
    d.display_set = true;
    if (omode == 2 || omode == 3) {
        const bool ntsc = omode == 2;
        const s32 magh1 = (w + 2559) / w;
        const s32 dxv = (dx * magh1 + off[0] + (ntsc ? 636 : 656)) & 0xFFF;
        s32 dyv, dh;
        if (static_cast<s16>(interlace) == 1) {
            dyv = (dy + off[1] + (ntsc ? 50 : 72)) & 0xFFF;
            dh = ffmode ? 2 * h - 1 : h - 1;
        } else {
            dyv = (dy + off[1] + (ntsc ? 25 : 36)) & 0xFFF;
            dh = h - 1;
        }
        d.display = static_cast<u64>(static_cast<s64>(magh1 - 1)) << 23 | static_cast<u64>(static_cast<s64>(magh1 * w - 1)) << 32 |
                    static_cast<u64>(dxv) | static_cast<u64>(static_cast<s64>(dh)) << 44 | static_cast<u64>(dyv) << 12;
    } else if (omode == 0x50) {
        const s32 dxv = (2 * ((720 - w) / 2) + off[0] + 2 * dx + 232) & 0xFFF;
        const s32 dyv = (dy + off[1] + 35) & 0xFFF;
        d.display = static_cast<u64>(static_cast<s64>(h - 1)) << 44 | static_cast<u64>(static_cast<s64>(2 * w - 1)) << 32 |
                    static_cast<u64>(dxv) | 0x800000ull | static_cast<u64>(dyv) << 12;
    } else {
        d.display_set = false;
    }
    return d;
}

// A ROMVER file served through sceOpen / sceRead / sceClose (checkModelVersion's IOP requests)
std::vector<std::tuple<u32, std::string, StandInFn>> romver_standins(const std::string& text, bool open_ok) {
    auto pos = std::make_shared<std::size_t>(0);
    std::vector<std::tuple<u32, std::string, StandInFn>> v;
    v.emplace_back(kSceOpen, "sceOpen", [open_ok, pos](EEContext&, StandIns&, StandInCall& c) {
        *pos = 0;
        c.v0 = open_ok ? 3 : sx(0xFFFFFFFEu);
    });
    v.emplace_back(kSceRead, "sceRead", [text, pos](EEContext& ctx, StandIns&, StandInCall& c) {
        const u8 b = *pos < text.size() ? static_cast<u8>(text[*pos]) : 0;
        ++*pos;
        ctx.memory->main_ram()[static_cast<u32>(c.args[1]) & 0x1FFFFFFu] = b;
        c.v0 = 1;
    });
    return v;
}

// the _sce_GetGsDxDyOffset kernel call: writes the four offsets through $a1..$t0
StandInFn dxdy_standin(const s32 off[4]) {
    const std::array<s32, 4> o{off[0], off[1], off[2], off[3]};
    return [o](EEContext& ctx, StandIns&, StandInCall& c) {
        const u32 ptrs[4] = {static_cast<u32>(c.args[1]), static_cast<u32>(c.args[2]), static_cast<u32>(c.args[3]), static_cast<u32>(c.args[4])};
        for (int i = 0; i < 4; ++i) std::memcpy(ctx.memory->main_ram() + (ptrs[i] & 0x1FFFFFFu), &o[i], 4);
        c.v0 = 0;
    };
}

bool glob_model(const char* name, const char* pat) {  // '?' one character, '*' any run
    if (*pat == 0) return *name == 0;
    if (*pat == '*') return glob_model(name, pat + 1) || (*name && glob_model(name + 1, pat));
    if (*name == 0) return false;
    return (*pat == '?' || *pat == *name) && glob_model(name + 1, pat + 1);
}

}  // namespace

// =====================================================================================================================
// Every body on random worlds (the p3fes_handgen sweep; the cases below carry the real inputs)
// =====================================================================================================================
TEST_CASE("game(sce1): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");  // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    int stops = 0, pairs = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        // sceTtyRead spins on an empty ring: its random worlds run into the runaway stop (both bodies alike) -- fewer
        const u32 n = std::string(c.name) == "sceTtyRead" ? 4 : seeds;
        for (u32 seed = 1; seed <= n; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            Args args{};
            for (u64& a : args) a = hgp::random_arg(rng, kWorld, kWorldSize);  // one draw per statement
            g_t.fn[0] = c.hand;
            g_t.fn[1] = c.recomp;
            g_t.fpr.clear();
            g_t.customs.clear();
            const hgp::Run r = hgp::pair(*m, &tramp<0>, &tramp<1>, args, seed, c.name);
            expect_same_log(g_t.world[0]->si, g_t.world[1]->si, c.name);
            stops += r.stopped ? 1 : 0;
            ++pairs;
        }
    }
    MESSAGE("random worlds: " << pairs << " pairs, " << stops << " stopped early");
}

// =====================================================================================================================
// libgraph: the draw environments, the Z-buffer page, the store-image packet against the GS register formats
// =====================================================================================================================
TEST_CASE("game(sce1): draw environments and the Z-buffer page against the GS register formats") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    std::mt19937 rng{0x5CE1u};
    u32 seed = 100;
    const s32 psms[] = {0x00, 0x01, 0x02, 0x0A, 0x30, 0x31, 0x32, 0x3A};
    const s32 sizes[][2] = {{640, 448}, {640, 480}, {512, 448}, {640, 224}, {320, 240}, {720, 480}, {64, 32}, {1, 1}, {100, 77}};
    int checked = 0;
    for (int field = 0; field < 2; ++field) {
        set_gparam(m, field ? 1 : 0, 2, 0);
        for (const auto& wh : sizes) {
            for (int k = 0; k < 3; ++k) {
                const s32 psm = psms[rng() % 8];
                const s32 ztest = static_cast<s32>(rng() % 4);
                const s32 zpsm = psms[rng() % 8];
                // sceGszbufaddr(psm, w, h)
                const hgp::Run z = sce_pair(m, "sceGszbufaddr", {static_cast<u64>(psm), static_cast<u64>(wh[0]), static_cast<u64>(wh[1]), 0},
                                            seed++, "sceGszbufaddr");
                CHECK(static_cast<s64>(v0_of(z)) == zbp_model(psm, wh[0], wh[1], field != 0));
                for (int ctx2 = 0; ctx2 < 2; ++ctx2) {
                    u64 old[8] = {};
                    for (int i = 0; i < 16; ++i) w64(m, kOut + 8 * i, 0);
                    old[4] = rng() & 6u;  // the bits the OR / AND keep
                    old[5] = rng() & 6u;
                    old[6] = rng() & 7u;
                    w64(m, kOut + sce::draw::kPrmodecont, old[4]);
                    w64(m, kOut + sce::draw::kColclamp, old[5]);
                    w64(m, kOut + sce::draw::kDthe, old[6]);
                    Opt o;
                    o.gpr_in[GPR_T0] = static_cast<u64>(ztest);
                    o.gpr_in[GPR_T1] = static_cast<u64>(zpsm);
                    const char* fn = ctx2 ? "sceGsSetDefDrawEnv2" : "sceGsSetDefDrawEnv";
                    const hgp::Run r = sce_pair(m, fn, {sx(kOut), static_cast<u64>(psm), static_cast<u64>(wh[0]), static_cast<u64>(wh[1])},
                                                seed++, fn, o);
                    REQUIRE(!r.stopped);
                    CHECK(v0_of(r) == sce::draw::kPairs);
                    const DrawEnvModel e = draw_model(ctx2 != 0, psm, wh[0], wh[1], ztest, zpsm, field != 0, old);
                    for (int i = 0; i < 8; ++i) {
                        INFO(fn << " pair " << i << " psm " << psm << " " << wh[0] << "x" << wh[1] << " ztest " << ztest);
                        CHECK(r64(m, kOut + 16 * i) == e.data[i]);
                        CHECK(r64(m, kOut + 16 * i + sce::draw::kAddrOff) == e.addr[i]);
                    }
                    ++checked;
                }
            }
        }
    }
    MESSAGE("draw environments checked against the GS formats: " << checked);

    // sceGsSetDefStoreImage: VIF codes, GIF tag, BITBLTBUF / TRXPOS / TRXREG / FINISH / TRXDIR
    for (int k = 0; k < 24; ++k) {
        const s32 sbp = static_cast<s32>(rng() % 0x4000);  // one random draw per statement
        const s32 sbw = static_cast<s32>(rng() % 64);
        const s32 spsm = psms[rng() % 8];
        const s32 x = static_cast<s32>(rng() % 2048);
        const s32 y = static_cast<s32>(rng() % 2048);
        const s32 w = static_cast<s32>(1 + rng() % 2048);
        const s32 h = static_cast<s32>(1 + rng() % 2048);
        for (int i = 0; i < 14; ++i) w64(m, kOut + 8 * i, ~0ull);
        Opt o;
        o.gpr_in[GPR_T0] = static_cast<u64>(x);
        o.gpr_in[GPR_T1] = static_cast<u64>(y);
        o.gpr_in[GPR_T2] = static_cast<u64>(w);
        o.gpr_in[GPR_T3] = static_cast<u64>(h);
        const hgp::Run r = sce_pair(m, "sceGsSetDefStoreImage", {sx(kOut), static_cast<u64>(sbp), static_cast<u64>(sbw), static_cast<u64>(spsm)},
                                    seed++, "sceGsSetDefStoreImage", o);
        REQUIRE(!r.stopped);
        CHECK(v0_of(r) == sce::store::kQwords);
        CHECK(r32(m, kOut + sce::store::kVifNop) == 0);
        CHECK(r32(m, kOut + sce::store::kVifMskpath3) == 0x06008000u);  // MSKPATH3 (cmd 6), mask on
        CHECK(r32(m, kOut + sce::store::kVifFlusha) == 0x13000000u);    // FLUSHA (cmd 0x13)
        CHECK(r32(m, kOut + sce::store::kVifDirect) == 0x50000006u);    // DIRECT (cmd 0x50), 6 qwords
        const u64 tag = r64(m, kOut + sce::store::kGifTag);
        CHECK((tag & 0x7FFF) == 5);        // NLOOP
        CHECK(((tag >> 15) & 1) == 1);     // EOP
        CHECK(((tag >> 58) & 3) == 0);     // FLG PACKED
        CHECK((tag >> 60) == 1);           // NREG
        CHECK(r64(m, kOut + sce::store::kGifTag + 8) == 0xE);  // REGS: A+D
        CHECK(r64(m, kOut + sce::store::kBitbltbuf) == (static_cast<u64>(sbp) | static_cast<u64>(sbw) << 16 | static_cast<u64>(spsm) << 24));
        CHECK(r64(m, kOut + sce::store::kBitbltbuf + 8) == 0x50);
        CHECK(r64(m, kOut + sce::store::kTrxpos) == (static_cast<u64>(x) | static_cast<u64>(y) << 16));
        CHECK(r64(m, kOut + sce::store::kTrxpos + 8) == 0x51);
        CHECK(r64(m, kOut + sce::store::kTrxreg) == (static_cast<u64>(w) | static_cast<u64>(h) << 32));
        CHECK(r64(m, kOut + sce::store::kTrxreg + 8) == 0x52);
        CHECK(r64(m, kOut + sce::store::kFinish) == 0);
        CHECK(r64(m, kOut + sce::store::kFinish + 8) == 0x61);
        CHECK(r64(m, kOut + sce::store::kTrxdir) == 1);  // XDIR: local -> host
        CHECK(r64(m, kOut + sce::store::kTrxdir + 8) == 0x53);
    }
}

TEST_CASE("game(sce1): the dorm snapshot's live draw environments") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const std::vector<u8> snap = read_snapshot("dorm_replay_4900");
    if (snap.size() != EEMemory::kMainRamSize) {
        MESSAGE("SKIP: no dorm_replay_4900 snapshot");
        return;
    }
    std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
    // SkyStart's four environments (docs/RUNTIME_CONTRACT.md B-50): sceGsSetDefDrawEnv(&env, 0, 640, 448, 2, 0x3A) and
    // its context-2 twin, into a fresh record; the snapshot's records then differ only where SkyStart patched them after
    // the call: FRAME.FBP (140 / 0), ZBUF.ZBP (280), and TEST_1 with the clear packets' 0x140B bits
    struct Env {
        u32 va;
        bool ctx2;
    };
    const Env envs[] = {{0x9649F0u, false}, {0x964A70u, true}, {0x964B60u, false}, {0x964BE0u, true}};
    u32 seed = 200;
    for (const Env& e : envs) {
        wzero(m, kOut, sce::draw::kSize);
        Opt o;
        o.gpr_in[GPR_T0] = 2;
        o.gpr_in[GPR_T1] = 0x3A;
        const char* fn = e.ctx2 ? "sceGsSetDefDrawEnv2" : "sceGsSetDefDrawEnv";
        const hgp::Run r = sce_pair(m, fn, {sx(kOut), 0, 640, 448}, seed++, std::string(fn) + " (dorm)", o);
        REQUIRE(!r.stopped);
        for (u32 i = 0; i < 16; ++i) {
            u64 mine = r64(m, kOut + 8 * i), live = r64(m, e.va + 8 * i);
            if (i == 0) {
                mine &= ~0x1FFull;
                live &= ~0x1FFull;
            }
            if (i == 2) {
                mine &= ~0x1FFull;
                live &= ~0x1FFull;
            }
            if (i == 14) live &= ~0x140Bull;
            INFO(fn << " at " << hex64(e.va) << " doubleword " << i);
            CHECK(mine == live);
        }
        CHECK((r64(m, e.va + sce::draw::kZbuf) & 0x1FF) == 280);  // ZBP after SkyStart's patch = 2 x 140 pages
    }
}

TEST_CASE("game(sce1): display environments per video mode, checkModelVersion and the DX / DY offsets") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    u32 seed = 300;
    // checkModelVersion on ROMVER texts (the date field: the 8 characters before the final byte)
    struct Rom {
        const char* text;
        bool open_ok;
        s32 expect;
    };
    const Rom roms[] = {{"0230AC20080220\n", true, 1}, {"0160EC20010704\n", true, 1}, {"0120JC20010608\n", true, 0},
                        {"0100JC20000117\n", true, 0}, {"0230AC20080220", true, 0} /* no newline: atoi("C2008..") = 0 */,
                        {"", true, 0}, {"0230AC20080220\n", false, -1}};
    for (const Rom& rom : roms) {
        Opt o;
        o.customs = romver_standins(rom.text, rom.open_ok);
        const hgp::Run r = sce_pair(m, "checkModelVersion", {0, 0, 0, 0}, seed++, std::string("checkModelVersion ") + rom.text, o);
        REQUIRE(!r.stopped);
        CHECK(v0s(r) == rom.expect);
        CHECK(gstr(m, static_cast<u32>(log_of().log.at(0).args[0])) == "rom0:ROMVER");
        CHECK(log_of().calls_to(kSceClose) == (rom.open_ok ? 1u : 0u));
    }
    {   // a 300-byte file without a NUL: the loop stops after 256 reads
        Opt o;
        o.customs = romver_standins(std::string(300, '7'), true);
        const hgp::Run r = sce_pair(m, "checkModelVersion", {0, 0, 0, 0}, seed++, "checkModelVersion 300 bytes", o);
        REQUIRE(!r.stopped);
        CHECK(log_of().calls_to(kSceRead) == 256u);
    }

    // sceGsSetDefDispEnv: NTSC / PAL interlaced field and frame, progressive, 480p with and without the newer-ROM
    // offsets, an unsupported mode
    struct Mode {
        u16 interlace, omode, ffmode;
    };
    const Mode modes[] = {{1, 2, 0}, {1, 2, 1}, {0, 2, 0}, {1, 3, 0}, {1, 3, 1}, {0, 3, 0}, {0, 0x50, 0}, {1, 0x50, 1}, {0, 0x1A, 0}};
    const s32 sizes[][2] = {{640, 448}, {640, 224}, {512, 448}, {720, 480}, {320, 240}, {256, 224}};
    std::mt19937 rng{0xD15Fu};
    int checked = 0;
    for (const Mode& md : modes) {
        for (const auto& wh : sizes) {
            for (int rom = 0; rom < 3; ++rom) {  // 480p: ROM newer (offsets), older (none), unreadable (-1: offsets too)
                if (rom > 0 && (md.omode == 2 || md.omode == 3)) break;
                set_gparam(m, md.interlace, md.omode, md.ffmode);
                const s32 psm = static_cast<s32>(rng() % 3);
                const s32 dx = static_cast<s32>(rng() % 64) - 16;
                const s32 dy = static_cast<s32>(rng() % 64) - 16;
                const s32 offx = static_cast<s32>(rng() % 32);
                const s32 offy = static_cast<s32>(rng() % 32);
                const s32 dxdy[4] = {offx, offy, 7, 9};
                for (int i = 0; i < 5; ++i) w64(m, kOut + 8 * i, 0xA5A5A5A5A5A5A5A5ull);
                w32(m, sce::kDeci2LineFill, 0);
                Opt o;
                o.gpr_in[GPR_T0] = sx(static_cast<u32>(dx));
                o.gpr_in[GPR_T1] = sx(static_cast<u32>(dy));
                o.customs = romver_standins(rom == 1 ? "0100JC20000117\n" : "0230AC20080220\n", rom != 2);
                o.customs.emplace_back(kGetDxDy, "_sce_GetGsDxDyOffset", dxdy_standin(dxdy));
                const hgp::Run r = sce_pair(m, "sceGsSetDefDispEnv", {sx(kOut), static_cast<u64>(psm), static_cast<u64>(wh[0]), static_cast<u64>(wh[1])},
                                            seed++, "sceGsSetDefDispEnv", o);
                REQUIRE(!r.stopped);
                const bool offsets = md.omode != 2 && md.omode != 3 && rom != 1;  // asked for every mode but NTSC / PAL
                const s32 zero[4] = {0, 0, 0, 0};
                const DispModel d = disp_model(md.interlace, md.omode, md.ffmode, psm, wh[0], wh[1], dx, dy, offsets ? dxdy : zero);
                INFO("mode " << md.omode << " interlace " << md.interlace << " ffmode " << md.ffmode << " " << wh[0] << "x" << wh[1]
                             << " dx " << dx << " dy " << dy << " rom " << rom);
                CHECK(r64(m, kOut + sce::disp::kPmode) == d.pmode);
                CHECK(r64(m, kOut + sce::disp::kSmode2) == d.smode2);
                CHECK(r64(m, kOut + sce::disp::kDispfb) == d.dispfb);
                CHECK(r64(m, kOut + sce::disp::kDisplay) == (d.display_set ? d.display : 0xA5A5A5A5A5A5A5A5ull));
                CHECK(r64(m, kOut + sce::disp::kBgcolor) == 0);
                CHECK(log_of().calls_to(kGetDxDy) == (offsets ? 1u : 0u));
                // the unknown mode's message: scePrintf runs recompiled in this build (printf_char -> deci2Putchar -> kputs)
                CHECK(log_of().calls_to(kScePrintf) + log_of().calls_to(kKputs) == (d.display_set ? 0u : 1u));
                if (!d.display_set && log_of().calls_to(kKputs) == 1)
                    CHECK(gstr(m, sce::kDeci2Line) == "sceGsDefDispEnv:Not support displaymode for 0x1a!!\n");
                ++checked;
            }
        }
    }
    MESSAGE("display environments checked: " << checked);
}

// =====================================================================================================================
// libdma and libkernel's newlib glue
// =====================================================================================================================
TEST_CASE("game(sce1): libdma helpers and the newlib glue") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    u32 seed = 400;
    // CheckAddress: the scratchpad (0x7xxxxxxx) gets the SPR flag (bit 31) on its offset
    const u64 addrs[] = {0x70000000u, 0x70003FF0u, 0x7FFFFFFFu, 0x00100000u, 0x01FFFFF0u, 0x80000000u, 0x6FFFFFFFu, sx(0x70001000u), 0x1234567870000010ull};
    for (u64 a : addrs) {
        const hgp::Run r = sce_pair(m, "CheckAddress", {a, 0, 0, 0}, seed++, "CheckAddress");
        const u32 lo = static_cast<u32>(a);
        const u64 expect = (lo >> 28) == 7 ? sx(0x80000000u | (lo & 0x0FFFFFFFu)) : a;
        CHECK(v0_of(r) == expect);
    }
    // memclr over lengths 0..40 at every alignment, with guard bytes
    for (u32 n = 0; n <= 40; n += 3) {
        for (u32 al = 0; al < 4; ++al) {
            std::memset(m.at(kOut), 0x5A, 64);
            sce_pair(m, "memclr", {sx(kOut + 8 + al), n, 0, 0}, seed++, "memclr");
            for (u32 i = 0; i < 64; ++i) CHECK(r8(m, kOut + i) == ((i >= 8 + al && i < 8 + al + n) ? 0 : 0x5A));
        }
    }
    // sceDmaGetEnv copies the 20-byte shadow and returns its argument
    for (u32 i = 0; i < 20; ++i) w8(m, sce::kDmaEnvShadow + i, static_cast<u8>(0x30 + i));
    std::memset(m.at(kOut), 0xEE, 32);
    {
        const hgp::Run r = sce_pair(m, "sceDmaGetEnv", {sx(kOut), 0, 0, 0}, seed++, "sceDmaGetEnv");
        CHECK(v0_of(r) == sx(kOut));
        for (u32 i = 0; i < 20; ++i) CHECK(r8(m, kOut + i) == 0x30 + i);
        CHECK(r8(m, kOut + 20) == 0xEE);
    }
    // the newlib stubs: -1 / 1 / 0 and errno = EIO (5) through __errno (the _reent's first word)
    const u32 reent = r32(m, 0x782F30u);  // _impure_ptr
    for (const char* fn : {"open", "stat", "unlink"}) {
        w32(m, reent, 0);
        const hgp::Run r = sce_pair(m, fn, {sx(kOut), 0, 0, 0}, seed++, fn);
        CHECK(v0s(r) == -1);
        CHECK(r32(m, reent) == 5u);
    }
    for (const char* fn : {"close", "ioctl", "lseek"}) CHECK(v0s(sce_pair(m, fn, {3, 0, 0, 0}, seed++, fn)) == -1);
    CHECK(v0s(sce_pair(m, "isatty", {1, 0, 0, 0}, seed++, "isatty")) == 1);
    CHECK(v0s(sce_pair(m, "getpid", {0, 0, 0, 0}, seed++, "getpid")) == 1);
    {
        std::memset(m.at(kOut), 0xCC, 96);
        const hgp::Run r = sce_pair(m, "fstat", {1, sx(kOut), 0, 0}, seed++, "fstat");
        CHECK(v0s(r) == 0);
        CHECK(r32(m, kOut + 4) == 0x2000u);  // st_mode = S_IFCHR
        CHECK(r64(m, kOut + 72) == 0);
        CHECK(r32(m, kOut + 0) == 0xCCCCCCCCu);
    }
    {   // kill(1, sig) exits through the kernel; another pid is ignored
        const hgp::Run r1 = sce_pair(m, "kill", {1, 9, 0, 0}, seed++, "kill self");
        CHECK(log_of().calls_to(kExit) == 1u);
        CHECK(log_of().log.at(0).args[0] == 9);
        const hgp::Run r2 = sce_pair(m, "kill", {2, 9, 0, 0}, seed++, "kill other");
        CHECK(log_of().calls_to(kExit) == 0u);
        CHECK(v0s(r2) == 0);
        (void)r1;
    }
    w32(m, sce::kTtyInitFlag, 1);
    sce_pair(m, "sceResetttyinit", {0, 0, 0, 0}, seed++, "sceResetttyinit");
    CHECK(r32(m, sce::kTtyInitFlag) == 0);
}

// =====================================================================================================================
// The tty ring, the character sinks and the small printf
// =====================================================================================================================
TEST_CASE("game(sce1): the tty ring, the DECI2 / serial sinks and sceSnprintf") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    u32 seed = 500;
    const u32 q = sce::ttyq::kInstance;
    // QueueInit, then writes and reads against a host ring of the same capacity
    const u32 cap = 13;
    {
        const hgp::Run r = sce_pair(m, "QueueInit", {cap, 0, 0, 0}, seed++, "QueueInit");
        CHECK(v0_of(r) == sx(q));
        CHECK(r32(m, q + sce::ttyq::kCapacity) == cap);
        CHECK(r32(m, q + sce::ttyq::kCount) == 0);
        CHECK(r32(m, q + sce::ttyq::kReadPtr) == q + sce::ttyq::kData);
        CHECK(r32(m, q + sce::ttyq::kWritePtr) == q + sce::ttyq::kData);
    }
    std::mt19937 rng{0x7171u};
    u32 hw = 0, hr = 0, hc = 0;
    for (int k = 0; k < 60; ++k) {
        const bool write = hc == 0 || (hc < cap && rng() % 2 == 0);
        const hgp::Run r = sce_pair(m, write ? "QueuePeekWriteDone" : "QueuePeekReadDone", {sx(q), 0, 0, 0}, seed++, "QueuePeek");
        u32& p = write ? hw : hr;
        hc = write ? hc + 1 : hc - 1;
        p = (p + 1) % cap;
        CHECK(r32(m, q + sce::ttyq::kCount) == hc);
        CHECK(r32(m, q + sce::ttyq::kWritePtr) == q + sce::ttyq::kData + hw);
        CHECK(r32(m, q + sce::ttyq::kReadPtr) == q + sce::ttyq::kData + hr);
        CHECK(v0_of(r) == sx(p == 0 ? q + sce::ttyq::kData : hc));
    }
    // sceTtyRead: a line out of the ring (stops after '\n' or '\r', or after n bytes)
    struct ReadCase {
        std::string text;
        u32 n;
        std::string expect;
    };
    const ReadCase reads[] = {{"hello\nworld", 32, "hello\n"}, {"ab\rcd", 32, "ab\r"}, {"abcdefgh", 5, "abcde"}, {"x", 0, ""}, {"\n", 4, "\n"}};
    for (const ReadCase& rc : reads) {
        const u32 ring = kOut + 0x100;
        w32(m, ring + sce::ttyq::kCapacity, 64);
        w32(m, ring + sce::ttyq::kCount, static_cast<u32>(rc.text.size()));
        w32(m, ring + sce::ttyq::kReadPtr, ring + sce::ttyq::kData);
        w32(m, ring + sce::ttyq::kWritePtr, ring + sce::ttyq::kData + static_cast<u32>(rc.text.size()));
        std::memcpy(m.at(ring + sce::ttyq::kData), rc.text.data(), rc.text.size());
        w32(m, sce::ttyq::kPointer, ring);
        std::memset(m.at(kOut), 0, 64);
        const hgp::Run r = sce_pair(m, "sceTtyRead", {sx(kOut), rc.n, 0, 0}, seed++, "sceTtyRead");
        REQUIRE(!r.stopped);
        CHECK(v0s(r) == static_cast<s32>(rc.expect.size()));
        CHECK(std::string(reinterpret_cast<const char*>(m.at(kOut)), rc.expect.size()) == rc.expect);
        CHECK(r32(m, ring + sce::ttyq::kCount) == rc.text.size() - rc.expect.size());
    }
    // deci2Putchar: the line buffer and its flushes through kputs
    {
        w32(m, sce::kDeci2LineFill, 0);
        for (char ch : std::string("abc")) sce_pair(m, "deci2Putchar", {static_cast<u64>(ch), 0, 0, 0}, seed++, "deci2Putchar");
        CHECK(r32(m, sce::kDeci2LineFill) == 3u);
        sce_pair(m, "deci2Putchar", {'\n', 0, 0, 0}, seed++, "deci2Putchar newline");
        CHECK(log_of().calls_to(kKputs) == 1u);
        CHECK(log_of().log.at(0).args[0] == sx(sce::kDeci2Line));
        CHECK(gstr(m, sce::kDeci2Line) == "abc\n");
        CHECK(r32(m, sce::kDeci2LineFill) == 0u);
        w32(m, sce::kDeci2LineFill, 126);  // a full buffer: NUL at +127, flush, then the character
        sce_pair(m, "deci2Putchar", {'Z', 0, 0, 0}, seed++, "deci2Putchar full");
        CHECK(log_of().calls_to(kKputs) == 1u);
        CHECK(r8(m, sce::kDeci2Line + 127) == 0);
        CHECK(r8(m, sce::kDeci2Line) == 'Z');
        CHECK(r32(m, sce::kDeci2LineFill) == 1u);
    }
    // serialPutchar: "\n" -> "\r\n"
    {
        sce_pair(m, "serialPutchar", {'\n', 0, 0, 0}, seed++, "serialPutchar newline");
        REQUIRE(log_of().log.size() == 2u);
        CHECK(log_of().log[0].args[0] == '\r');
        CHECK(log_of().log[1].args[0] == '\n');
        sce_pair(m, "serialPutchar", {'q', 0, 0, 0}, seed++, "serialPutchar");
        REQUIRE(log_of().log.size() == 1u);
        CHECK(log_of().log[0].args[0] == 'q');
        sce_pair(m, "kprintf_char", {0, 0, 'k', 0}, seed++, "kprintf_char");  // the sinks take the character in $a2
        CHECK(log_of().calls_to(kKputchar) == 1u);
        sce_pair(m, "kprintf_char", {0, 0, 0, 0}, seed++, "kprintf_char NUL");  // a NUL is not sent
        CHECK(log_of().calls_to(kKputchar) == 0u);
        w32(m, sce::kDeci2LineFill, 0);
        const hgp::Run r = sce_pair(m, "printf_char", {0, 0, 'p', 0}, seed++, "printf_char");
        CHECK(r8(m, sce::kDeci2Line) == 'p');
        (void)r;
    }
    // ftoi against the rule on doubles: 0 below 0.5, 9999 from 2^65, the nearest integer (within one) in between
    for (double d : {0.0, 0.25, 0.4999, 0.5, 0.75, 1.0, 1.5, 2.75, 123.0, 8191.9, 8192.0, 1e9, 2147483000.0, 1e-20, 4095.5, 0x1p65, 1e30}) {
        const hgp::Run r = sce_pair(m, "ftoi", {std::bit_cast<u64>(d), 0, 0, 0}, seed++, "ftoi");
        const s32 v = v0s(r);
        INFO("ftoi(" << d << ") = " << v);
        if (d < 0.5) CHECK(v == 0);
        else if (d >= 0x1p65) CHECK(v == 9999);
        else if (d < 2147483647.0) CHECK(std::abs(static_cast<double>(v) - d) <= 1.0);
    }
    // sceVsnprintf(buf, size, fmt, ap) against the host's snprintf on the conversions both define alike
    struct Fmt {
        const char* fmt;
        u64 arg;
        bool str;  // the argument is a string (written to the guest)
    };
    const u32 sarg = kOut + 0x800;
    const Fmt fmts[] = {{"%d", static_cast<u64>(-42), false}, {"%5d|", 42, false}, {"%-5d|", 42, false}, {"%05d", 42, false},
                        {"%x", 0xBEEF, false}, {"%X", 0xBEEF, false}, {"%#x", 0xBEEF, false}, {"%o", 8, false}, {"%#o", 8, false},
                        {"%u", 4000000000u, false}, {"%c", 'A', false}, {"%s", 0, true}, {"%10s|", 0, true}, {"%-10s|", 0, true},
                        {"%.3s", 0, true}, {"100%%", 0, false}, {"%i", 7, false}, {"%ld", static_cast<u64>(-1234567890123ll), false},
                        {"%lx", 0x123456789ABCDEFull, false}, {"%hd", 0x12345, false}, {"%+d", 5, false}, {"% d", 5, false},
                        {"%.4d", 7, false}, {"%8.3d|", 7, false}, {"[%3c]", 'z', false}, {"%p", 0x1234, false}, {"%lu", 0xFFFFFFFFFFFFFFFFull, false}};
    wstr(m, sarg, "guest");
    int host_equal = 0, host_differ = 0;
    std::string differ;
    for (const Fmt& f : fmts) {
        for (u32 size : {64u, 4u, 1u}) {
            const u32 fmt = kOut + 0x400, ap = kOut + 0x600, buf = kOut;
            wstr(m, fmt, f.fmt);
            w64(m, ap, f.str ? sx(sarg) : f.arg);
            std::memset(m.at(buf), 0x7E, 128);
            const hgp::Run r = sce_pair(m, "sceVsnprintf", {sx(buf), size, sx(fmt), sx(ap)}, seed++, std::string("sceVsnprintf ") + f.fmt);
            REQUIRE(!r.stopped);
            if (size != 64) continue;
            char host[128];
            if (f.str) std::snprintf(host, sizeof host, f.fmt, "guest");
            else if (const std::size_t l = std::string(f.fmt).find('l'); l != std::string::npos) {
                std::string hf = f.fmt;  // 'l' is 64-bit on the EE; the host's long long
                hf.insert(l, "l");
                std::snprintf(host, sizeof host, hf.c_str(), static_cast<long long>(f.arg));
            } else if (std::string(f.fmt).find('p') != std::string::npos) std::snprintf(host, sizeof host, "0x%x", static_cast<unsigned>(f.arg));
            else std::snprintf(host, sizeof host, f.fmt, static_cast<int>(f.arg));
            const std::string guest = gstr(m, buf, 127);
            if (guest == host) ++host_equal;
            else {
                ++host_differ;
                differ += std::string(" [") + f.fmt + "] guest \"" + guest + "\" host \"" + host + "\";";
            }
        }
    }
    MESSAGE("sceVsnprintf vs host snprintf: " << host_equal << " equal, " << host_differ << " differ:" << differ);
    CHECK(host_differ == 0);
    // sceSnprintf(buf, size, fmt, ...) with register / stack varargs
    {
        const u32 fmt = kOut + 0x400;
        wstr(m, fmt, "%d-%x-%s-%c");
        Opt o;
        o.gpr_in[GPR_T0] = 0xAB;
        o.gpr_in[GPR_T1] = sx(sarg);
        o.gpr_in[GPR_T2] = '!';
        const hgp::Run r = sce_pair(m, "sceSnprintf", {sx(kOut), 64, sx(fmt), 12}, seed++, "sceSnprintf", o);
        REQUIRE(!r.stopped);
        CHECK(gstr(m, kOut) == "12-ab-guest-!");
        CHECK(v0s(r) == 13);
    }
    // %e / %f: printfloat through the soft-float helpers (fptodp stood in) -- pairs only
    for (double d : {0.0, 1.5, -2.25, 12345.678, 0.001}) {
        const u32 fmt = kOut + 0x400, ap = kOut + 0x600;
        wstr(m, fmt, "v=%f;");
        w64(m, ap, std::bit_cast<u64>(d));
        sce_pair(m, "sceVsnprintf", {sx(kOut), 64, sx(fmt), sx(ap)}, seed++, "sceVsnprintf %f");
    }
}

// =====================================================================================================================
// SIF tables, the alarm pool, the time conversions, the version checks
// =====================================================================================================================
TEST_CASE("game(sce1): SIF tables, the alarm pool, time conversions and the module version checks") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    u32 seed = 600;
    // software registers
    for (u32 i : {0u, 1u, 7u, 31u}) {
        sce_pair(m, "sceSifSetSreg", {i, 0x1000u + i, 0, 0}, seed++, "sceSifSetSreg");
        CHECK(r32(m, sce::kSifSregs + 4 * i) == 0x1000u + i);
        CHECK(v0_of(sce_pair(m, "sceSifGetSreg", {i, 0, 0, 0}, seed++, "sceSifGetSreg")) == 0x1000u + i);
    }
    CHECK(v0_of(sce_pair(m, "sceSifGetDataTable", {0, 0, 0, 0}, seed++, "sceSifGetDataTable")) == sce::kSifCmdData);
    // the command tables and a handler in each
    const u32 sys = kOut, usr = kOut + 0x200;
    w32(m, sce::kSifSysTable, 0x1111u);
    w32(m, sce::kSifUserTable, 0x2222u);
    CHECK(v0_of(sce_pair(m, "sub_506418", {sx(sys), 32, 0, 0}, seed++, "sub_506418")) == 0x1111u);
    CHECK(v0_of(sce_pair(m, "sub_506400", {sx(usr), 16, 0, 0}, seed++, "sub_506400")) == 0x2222u);
    CHECK(r32(m, sce::kSifSysTable) == sys);
    CHECK(r32(m, sce::kSifSysTable + 4) == 32u);
    CHECK(r32(m, sce::kSifUserTable) == usr);
    CHECK(r32(m, sce::kSifUserTable + 4) == 16u);
    sce_pair(m, "sub_506430", {sx(0x80000003u), 0x123450, 0xDA7A, 0}, seed++, "sub_506430 system");
    CHECK(r32(m, sys + 12 * 3) == 0x123450u);
    CHECK(r32(m, sys + 12 * 3 + 4) == 0xDA7Au);
    sce_pair(m, "sub_506430", {5, 0x543210, 0xBEEF, 0}, seed++, "sub_506430 user");
    CHECK(r32(m, usr + 12 * 5) == 0x543210u);
    CHECK(r32(m, usr + 12 * 5 + 4) == 0xBEEFu);
    // the two command handlers on built packets
    {
        const u32 pkt = kOut + 0x400, data = kOut + 0x500, table = kOut + 0x600;
        w32(m, pkt + 16, 6);
        w32(m, pkt + 20, 0xCAFE);
        w32(m, data + 28, table);
        sce_pair(m, "_set_sreg", {sx(pkt), sx(data), 0, 0}, seed++, "_set_sreg");
        CHECK(r32(m, table + 24) == 0xCAFEu);
        w32(m, pkt + 16, 0x00ABCDE0u);
        sce_pair(m, "_change_addr", {sx(pkt), sx(data), 0, 0}, seed++, "_change_addr");
        CHECK(r32(m, data + 8) == 0x00ABCDE0u);
    }

    // the timer-alarm pool: 8 records (64-byte aligned) on the free list, allocate, insert by key, unlink, free
    const u32 recs = kOut + 0x1000;
    w32(m, sce::alarm::kSetUp, 0);
    w32(m, sce::alarm::kInUse, 0);
    w32(m, sce::alarm::kTagSeq, 0);
    w32(m, sce::alarm::kPending, 0);
    w32(m, sce::alarm::kHandling, 0);
    w32(m, sce::alarm::kCursor, 0);
    for (u32 i = 0; i < 8; ++i) {
        wzero(m, recs + 64 * i, 64);
        w32(m, recs + 64 * i + sce::alarm::kNext, i < 7 ? recs + 64 * (i + 1) : 0);
    }
    w32(m, sce::alarm::kFreeList, recs);
    std::vector<u32> ids;
    for (u32 i = 0; i < 9; ++i) {
        const hgp::Run r = sce_pair(m, "sub_50E5D8", {0, 0, 0, 0}, seed++, "sub_50E5D8 alloc");
        const u32 id = static_cast<u32>(v0_of(r));
        if (i == 8) {
            CHECK(id == 0x80008005u);  // empty pool
            break;
        }
        const u32 rec = recs + 64 * i;
        CHECK((id >> 10 << 6) == rec);
        CHECK((id & 0x3FFu) == r32(m, rec + sce::alarm::kTag));
        CHECK((id & 1u) == 1u);
        CHECK((id & 0x3FFu) == (((2u * (i + 1)) & 0x3FEu) | 1u));
        CHECK(r32(m, sce::alarm::kInUse) == i + 1);
        ids.push_back(id);
    }
    {   // status: in use / free of 128
        const hgp::Run r = sce_pair(m, "sub_50E7A0", {sx(kOut + 0x800), sx(kOut + 0x804), 0, 0}, seed++, "sub_50E7A0");
        CHECK(v0_of(r) == 0);
        CHECK(r32(m, kOut + 0x800) == 8u);
        CHECK(r32(m, kOut + 0x804) == 120u);
        w32(m, sce::alarm::kSetUp, 0xFFFFFFFFu);
        CHECK(v0_of(sce_pair(m, "sub_50E7A0", {0, 0, 0, 0}, seed++, "sub_50E7A0 not set up")) == sx(0x80008001u));
        w32(m, sce::alarm::kSetUp, 0);
    }
    // keys [+32] + [+16] - [+24]; insert in a random order and check the pending list is sorted (stable for ties)
    std::mt19937 rng{0xA1A3u};
    std::vector<std::pair<u64, u32>> keyed;
    for (u32 i = 0; i < 8; ++i) {
        const u32 rec = recs + 64 * i;
        const u64 a = rng() % 1000;
        const u64 b = rng() % 50;
        const u64 c = 100 + rng() % 200;
        w64(m, rec + sce::alarm::kU64A, a);
        w64(m, rec + sce::alarm::kU64B, b);
        w64(m, rec + sce::alarm::kU64C, c);
        sce_pair(m, "sub_50E190", {sx(rec), 0, 0, 0}, seed++, "sub_50E190 insert");
        keyed.emplace_back(c + a - b, rec);
        std::stable_sort(keyed.begin(), keyed.end(), [](const auto& x, const auto& y) { return x.first < y.first; });
        u32 p = r32(m, sce::alarm::kPending), prev = 0;
        for (const auto& [k, want] : keyed) {
            CHECK(p == want);
            CHECK(r32(m, p + sce::alarm::kPrev) == prev);
            prev = p;
            p = r32(m, p + sce::alarm::kNext);
        }
        CHECK(p == 0);
    }
    {   // unlink the middle one, then the head
        const u32 mid = keyed[3].second;
        const hgp::Run r = sce_pair(m, "sub_50E218", {sx(mid), 0, 0, 0}, seed++, "sub_50E218 unlink");
        CHECK(v0_of(r) == sx(keyed[4].second));
        CHECK(r32(m, keyed[2].second + sce::alarm::kNext) == keyed[4].second);
        CHECK(r32(m, keyed[4].second + sce::alarm::kPrev) == keyed[2].second);
        CHECK(r32(m, mid + sce::alarm::kPrev) == 0);
        sce_pair(m, "sub_50E218", {sx(keyed[0].second), 0, 0, 0}, seed++, "sub_50E218 head");
        CHECK(r32(m, sce::alarm::kPending) == keyed[1].second);
    }
    // time left and free, with bad ids
    {
        const u32 id = ids[5], rec = recs + 64 * 5;
        w32(m, rec + sce::alarm::kFlags, 1);
        CHECK(v0_of(sce_pair(m, "sub_50EB50", {id, 0, 0, 0}, seed++, "sub_50EB50")) == r64(m, rec + 16) - r64(m, rec + 24));
        w32(m, rec + sce::alarm::kFlags, 0);
        CHECK(v0_of(sce_pair(m, "sub_50EB50", {id, 0, 0, 0}, seed++, "sub_50EB50 flag clear")) == 0);
        CHECK(v0s(sce_pair(m, "sub_50EB50", {id ^ 2u, 0, 0, 0}, seed++, "sub_50EB50 bad tag")) == -1);
        CHECK(v0s(sce_pair(m, "sub_50EB50", {sx(0x80000001u), 0, 0, 0}, seed++, "sub_50EB50 negative")) == -1);
        CHECK(v0_of(sce_pair(m, "sub_50E690", {id ^ 2u, 0, 0, 0}, seed++, "sub_50E690 bad")) == sx(0x80008002u));
        w32(m, sce::alarm::kHandling, id);
        CHECK(v0_of(sce_pair(m, "sub_50E690", {id, 0, 0, 0}, seed++, "sub_50E690 busy")) == sx(0x80000010u));
        w32(m, sce::alarm::kHandling, 0);
        const u32 inuse = r32(m, sce::alarm::kInUse);
        w32(m, rec + sce::alarm::kFlags, 2);  // pending: unlinked first
        CHECK(v0_of(sce_pair(m, "sub_50E690", {id, 0, 0, 0}, seed++, "sub_50E690")) == 0);
        CHECK(r32(m, sce::alarm::kFreeList) == rec);
        CHECK(r32(m, sce::alarm::kInUse) == inuse - 1);
        CHECK(r32(m, rec + sce::alarm::kTag) == 0);
        CHECK(r32(m, rec + sce::alarm::kFlags) == 0);
    }
    // the user-alarm free list and the trampoline
    {
        sce_pair(m, "_InitAlarm", {0, 0, 0, 0}, seed++, "_InitAlarm");
        CHECK(r32(m, sce::alarm::kUserFree) == sce::alarm::kUserFirst);
        u32 n = 0;
        for (u32 p = sce::alarm::kUserFirst; p != 0 && n < 100; p = r32(m, p)) ++n;
        CHECK(n == 64);
        CHECK(r32(m, sce::alarm::kUserLast) == 0);
        // a handler returning 0 (sub_50D840 copying 0 bytes) frees the record; one returning 1 (getpid) keeps it
        const u32 rec = sce::alarm::kUserFirst + 16 * 9;
        for (const auto& [fn, keep] : {std::pair<u32, bool>{0x50D840u, false}, std::pair<u32, bool>{0x503930u, true}}) {
            w32(m, rec + 8, fn);
            w32(m, rec + 12, 0x77);
            const u32 head = r32(m, sce::alarm::kUserFree);
            const hgp::Run r = sce_pair(m, "AlarmHandler", {0x37, 0x100, 0, sx(rec)}, seed++, "AlarmHandler");
            REQUIRE(!r.stopped);
            if (keep) {
                CHECK(v0s(r) == 1);
                CHECK(r32(m, sce::alarm::kUserFree) == head);
            } else {
                CHECK(v0s(r) == -1);
                CHECK(r32(m, sce::alarm::kUserFree) == rec);
                CHECK(r32(m, rec) == head);
            }
        }
    }
    // time conversions at the 147,456,000 Hz bus clock (u64 maths on the host; the float ones within one ulp)
    for (u64 cyc : {0ull, 1ull, 147455999ull, 147456000ull, 147456001ull, 1000000000000ull, 0x7FFFFFFFFFull}) {
        const hgp::Run r = sce_pair(m, "sub_50EE38", {cyc, sx(kOut), sx(kOut + 4), 0}, seed++, "sub_50EE38");
        const u64 sec = cyc / sce::kBusClock;
        CHECK(r32(m, kOut) == static_cast<u32>(sec));
        CHECK(r32(m, kOut + 4) == static_cast<u32>((cyc - static_cast<u64>(static_cast<u32>(sec)) * sce::kBusClock) * 1000000ull / sce::kBusClock));
        (void)r;
    }
    for (const auto& [sec, usec] : {std::pair<u32, u32>{0, 0}, {1, 0}, {0, 1}, {0, 999999}, {12, 345678}, {1000, 500000}}) {
        const hgp::Run r = sce_pair(m, "sub_50EEE0", {sec, usec, 0, 0}, seed++, "sub_50EEE0");
        CHECK(v0_of(r) == static_cast<u64>(sec) * sce::kBusClock + static_cast<u64>(usec) * sce::kBusClock / 1000000ull);
    }
    for (u64 n : {1ull, 60ull, 1000ull, 147456ull, 16777215ull}) {
        const hgp::Run r = sce_pair(m, "sub_50EF50", {n, 0, 0, 0}, seed++, "sub_50EF50");
        const float want = 147456000.0f / static_cast<float>(n);
        const float got = ffrom(r.end.fpr[0]);
        CHECK(std::abs(static_cast<s64>(fbits(got)) - static_cast<s64>(fbits(want))) <= 1);
    }
    for (float f : {1.0f, 60.0f, 59.94f, 1000.0f, 0.5f}) {
        Opt o;
        o.fpr[12] = fbits(f);
        // __fixunssfdi runs for real (hand-written since slice unblock): the period is the quotient truncated to u64 (the
        // R5900 quotient within one ulp of the host's, as for sub_50EF50 above)
        const hgp::Run r = sce_pair(m, "sub_50EFA8", {0, 0, 0, 0}, seed++, "sub_50EFA8", o);
        const float q = 147456000.0f / f;
        const u64 got = v0_of(r);
        CHECK((got == static_cast<u64>(q) || got == static_cast<u64>(std::nextafter(q, 0.0f)) ||
               got == static_cast<u64>(std::nextafter(q, 1e30f))));
    }
    // the version tags: equal to the library's or to the alternate -> 0; else 1 unless library == alternate
    {
        const u32 lib = 0x77F48Cu, alt = kOut + 0x900;
        struct V {
            const char *server, *library, *alternate;
            s32 expect;
        };
        const V vs[] = {{"1234", "1234", "9999", 0}, {"9999", "1234", "9999", 0}, {"5555", "1234", "9999", 1}, {"5555", "1234", "1234", 0}};
        for (const auto& [name, server, altptr] : {std::tuple<const char*, u32, u32>{"_fs_version", 0x969C28u, 0x77F550u},
                                                   std::tuple<const char*, u32, u32>{"_lf_version", 0x96A0E8u, 0x77F564u}}) {
            for (const V& v : vs) {
                std::memcpy(m.at(server), v.server, 4);
                std::memcpy(m.at(lib), v.library, 4);
                std::memcpy(m.at(alt), v.alternate, 4);
                w32(m, altptr, alt);
                CHECK(v0s(sce_pair(m, name, {0, 0, 0, 0}, seed++, name)) == v.expect);
            }
        }
    }
    {   // libkernel leaves
        w32(m, 0x77FBD4u, 0x2A);
        CHECK(v0_of(sce_pair(m, "__sceKernlGetEhSemaId", {0, 0, 0, 0}, seed++, "__sceKernlGetEhSemaId")) == 0x2A);
        wstr(m, kOut + 0x40, "copy me");
        wzero(m, kOut + 0x80, 16);
        CHECK(v0_of(sce_pair(m, "sub_50D840", {sx(kOut + 0x80), sx(kOut + 0x40), 7, 0}, seed++, "sub_50D840")) == 0);
        CHECK(gstr(m, kOut + 0x80) == "copy me");
        sce_pair(m, "nullsub_131", {0, 0, 0, 0}, seed++, "nullsub_131");
        sce_pair(m, "DPRINT", {sx(kOut), 1, 2, 3}, seed++, "DPRINT");
        wzero(m, 0x985508u, 72);
        CHECK(v0s(sce_pair(m, "_get_free_slot", {0, 0, 0, 0}, seed++, "_get_free_slot")) == 0);
        w32(m, 0x985508u, 1);
        CHECK(v0s(sce_pair(m, "_get_free_slot", {0, 0, 0, 0}, seed++, "_get_free_slot 1")) == 1);
        w32(m, 0x985508u + 36, 1);
        CHECK(v0s(sce_pair(m, "_get_free_slot", {0, 0, 0, 0}, seed++, "_get_free_slot none")) == -1);
    }
}

// =====================================================================================================================
// libmc2's path helpers against host models
// =====================================================================================================================
TEST_CASE("game(sce1): libmc2 path and file-name helpers") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    u32 seed = 700;
    REQUIRE(gstr(m, 0x7BE5F0u) == ".");
    REQUIRE(gstr(m, 0x7BE5F8u) == "..");
    REQUIRE(gstr(m, 0x7BE608u) == "/");
    const u32 s = kOut, t = kOut + 0x200;
    // instr
    for (const auto& [str, ch] : {std::pair<const char*, char>{"hello", 'l'}, {"hello", 'h'}, {"hello", 'z'}, {"", 'a'}, {"abc", '\0'}, {"a*b", '*'}}) {
        wstr(m, s, str);
        const hgp::Run r = sce_pair(m, "instr", {sx(s), static_cast<u64>(ch), 0, 0}, seed++, "instr");
        const char* p = std::strchr(str, ch);
        CHECK(v0s(r) == (p ? static_cast<s32>(p - str) : -1));
    }
    const char* names[] = {"BESLUS-21621", "/BESLUS-21621/DATA", "a/b/c", "", ".", "..", "/x/..", "0123456789012345678901234567890",
                           "01234567890123456789012345678901", "dir/0123456789012345678901234567890", "q?x", "q*", "tab\there", "/"};
    for (const char* n : names) {
        wstr(m, s, n);
        const std::string str = n;
        const std::string last = str.find('/') == std::string::npos ? str : str.substr(str.rfind('/') + 1);
        CHECK(v0s(sce_pair(m, "isCorrNameSize", {sx(s), 0, 0, 0}, seed++, "isCorrNameSize")) == (last.size() < 32 ? 1 : 0));
        bool ok = true;
        for (char c : str) ok = ok && c != '?' && c != '*' && static_cast<signed char>(c) >= 32;
        CHECK(v0s(sce_pair(m, "isCorrFname", {sx(s), 0, 0, 0}, seed++, "isCorrFname")) == (ok ? 1 : 0));
        const bool cur_parent = last.size() < 32 && last != "." && last != "..";
        CHECK(v0s(sce_pair(m, "isPathCurParent", {sx(s), 0, 0, 0}, seed++, "isPathCurParent")) == (cur_parent ? 1 : 0));
        s32 slashes = 0;
        for (char c : str) slashes += c == '/' ? 1 : 0;
        CHECK(v0s(sce_pair(m, "_get_dir_nest", {sx(s), 0, 0, 0}, seed++, "_get_dir_nest")) == slashes);
    }
    // isWildFit against a host glob matcher
    const std::pair<const char*, const char*> globs[] = {{"abc", "abc"}, {"abc", "a*"}, {"abc", "*c"}, {"abc", "a?c"}, {"abc", "b*"},
                                                         {"abcd", "a*d"}, {"abc", "*x*"}, {"BESLUS-21621", "BES*"}, {"BESLUS-21621", "*216??"},
                                                         {"icon.sys", "*.sys"}, {"icon.sys", "*.ico"}, {"aXbXc", "a*b*c"}, {"abc", "abcd"},
                                                         {"abc", "*"}, {"", "*"}, {"abcabc", "*bc"}, {"ab", "a?"}};
    int glob_equal = 0;
    std::string glob_differ;
    for (const auto& [name, pat] : globs) {
        wstr(m, s, name);
        wstr(m, t, pat);
        const hgp::Run r = sce_pair(m, "isWildFit", {sx(s), sx(t), 0, 0}, seed++, std::string("isWildFit ") + name + " " + pat);
        REQUIRE(!r.stopped);
        if ((v0s(r) == 1) == glob_model(name, pat)) ++glob_equal;
        else glob_differ += std::string(" ") + name + "~" + pat;
    }
    MESSAGE("isWildFit vs a host glob: " << glob_equal << " of " << std::size(globs) << " equal" << glob_differ);
    CHECK(glob_differ.empty());
    // _strtok over its private copy: tokens, quoted tokens, the saved position
    {
        wstr(m, s, "  /BESLUS//DATA \"a b\" x");
        wstr(m, t, "/ ");
        std::vector<std::string> toks;
        u64 a0 = sx(s);
        for (int k = 0; k < 8; ++k) {
            const hgp::Run r = sce_pair(m, "_strtok", {a0, sx(t), 0, 0}, seed++, "_strtok");
            REQUIRE(!r.stopped);
            a0 = 0;
            if (v0_of(r) == 0) break;
            toks.push_back(gstr(m, static_cast<u32>(v0_of(r))));
        }
        INFO("tokens: " << toks.size());
        REQUIRE(toks.size() >= 3);
        CHECK(toks[0] == "BESLUS");
        CHECK(toks[1] == "DATA");
        CHECK(toks[2] == "a b");
    }
    // _make_path against a host resolver
    struct MP {
        const char* cwd;
        const char* path;
        s32 ok;
        const char* expect;
    };
    const MP mps[] = {{"/", "BESLUS", 1, "/BESLUS"}, {"/BESLUS/", "DATA", 1, "/BESLUS/DATA"}, {"/BESLUS/", "/X/Y", 1, "/X/Y"},
                      {"/BESLUS/", "..", 1, "/"}, {"/A/B/", "../C", 1, "/A/C"}, {"/A/", "./B", 1, "/A/B"}, {"/", "..", 0, nullptr}};
    for (u32 port = 0; port < 2; ++port) {
        for (const MP& c : mps) {
            wstr(m, 0x97BF90u + 2200 * port, c.cwd);
            wstr(m, s, c.path);
            wzero(m, t, 0x100);
            const hgp::Run r = sce_pair(m, "_make_path", {port, sx(s), sx(t), 0}, seed++, std::string("_make_path ") + c.cwd + " " + c.path);
            REQUIRE(!r.stopped);
            INFO(c.cwd << " + " << c.path << " -> " << gstr(m, t));
            CHECK(v0s(r) == c.ok);
            if (c.expect) CHECK(gstr(m, t) == c.expect);
        }
    }
    {   // a path of 128 characters is refused
        wstr(m, s, std::string(128, 'a'));
        CHECK(v0s(sce_pair(m, "_make_path", {0, sx(s), sx(t), 0}, seed++, "_make_path long")) == 0);
    }
}

TEST_CASE("game(sce1): pair count") { MESSAGE("sce1 pairs run (outside the random-world case): " << g_pairs << ", " << g_stops << " stopped early in both bodies"); }

#else

TEST_CASE("game(sce1): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
