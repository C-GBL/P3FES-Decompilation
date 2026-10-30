// Pair tests for slice libs27 (game/src/lib/libs27.cpp): every body against its recompiled body, compared by
// tests/game/handgen_pairs.h (the whole register file and cycle count at every check point and at the return / stop, all
// 32 MiB of RAM with the dead stack, the scratchpad, the BIOS window and the bus log). Worlds: random worlds; the
// library globals the bodies test (the heap-client bind word, the timer-1 registers and overflow count, the pad and DBC
// tables) set to the values their branches compare; the ROFS work area, volumes and directory tables of the replay
// snapshots with real "VOL:NAME" paths; and documented rules. sprintf and the semaphore wrappers (_sceWaitSema /
// _sceSignalSema) are stood in; any other callee this build does not emit stops both runs at the same call (no test
// asserts such a stop).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/libs27.h"

#include <algorithm>
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
void fn_sceSifQueryTotalFreeMemSize_0050b978(EEContext&);  // generated body
void fn_sceSifQueryTotalFreeMemSize_0050b978__recomp(EEContext&);  // recompiled
void fn_sceSifQueryBlockTopAddress_0050b9e8(EEContext&);  // generated body
void fn_sceSifQueryBlockTopAddress_0050b9e8__recomp(EEContext&);  // recompiled
void fn_sceSifQueryBlockSize_0050ba68(EEContext&);  // generated body
void fn_sceSifQueryBlockSize_0050ba68__recomp(EEContext&);  // recompiled
void fn_sceSifStopModule_0050beb8(EEContext&);  // generated body
void fn_sceSifStopModule_0050beb8__recomp(EEContext&);  // recompiled
void fn_sceSifUnloadModule_0050c0c0(EEContext&);  // generated body
void fn_sceSifUnloadModule_0050c0c0__recomp(EEContext&);  // recompiled
void fn_sceSifSearchModuleByName_0050c150(EEContext&);  // generated body
void fn_sceSifSearchModuleByName_0050c150__recomp(EEContext&);  // recompiled
void fn_sceSifSearchModuleByAddress_0050c1f0(EEContext&);  // generated body
void fn_sceSifSearchModuleByAddress_0050c1f0__recomp(EEContext&);  // recompiled
void fn_sceSifLoadModuleBuffer_0050c280(EEContext&);  // generated body
void fn_sceSifLoadModuleBuffer_0050c280__recomp(EEContext&);  // recompiled
void fn_sceSifLoadStartModuleBuffer_0050c2a0(EEContext&);  // generated body
void fn_sceSifLoadStartModuleBuffer_0050c2a0__recomp(EEContext&);  // recompiled
void fn_sceSifLoadStartModule_0050c508(EEContext&);  // generated body
void fn_sceSifLoadStartModule_0050c508__recomp(EEContext&);  // recompiled
void fn_sceSifLoadElfPart_0050c630(EEContext&);  // generated body
void fn_sceSifLoadElfPart_0050c630__recomp(EEContext&);  // recompiled
void fn_sceSifLoadElf_0050c650(EEContext&);  // generated body
void fn_sceSifLoadElf_0050c650__recomp(EEContext&);  // recompiled
void fn_sceSifGetIopAddr_0050c678(EEContext&);  // generated body
void fn_sceSifGetIopAddr_0050c678__recomp(EEContext&);  // recompiled
void fn_sceSifSetIopAddr_0050c768(EEContext&);  // generated body
void fn_sceSifSetIopAddr_0050c768__recomp(EEContext&);  // recompiled
void fn_sceSifIsAliveIop_0050c9a0(EEContext&);  // generated body
void fn_sceSifIsAliveIop_0050c9a0__recomp(EEContext&);  // recompiled
void fn_PutTLBEntry_0050cd40(EEContext&);  // generated body
void fn_PutTLBEntry_0050cd40__recomp(EEContext&);  // recompiled
void fn_iPutTLBEntry_0050cd50(EEContext&);  // generated body
void fn_iPutTLBEntry_0050cd50__recomp(EEContext&);  // recompiled
void fn_iSetTLBEntry_0050cda0(EEContext&);  // generated body
void fn_iSetTLBEntry_0050cda0__recomp(EEContext&);  // recompiled
void fn_GetTLBEntry_0050cdb0(EEContext&);  // generated body
void fn_GetTLBEntry_0050cdb0__recomp(EEContext&);  // recompiled
void fn_iGetTLBEntry_0050cdc0(EEContext&);  // generated body
void fn_iGetTLBEntry_0050cdc0__recomp(EEContext&);  // recompiled
void fn_ProbeTLBEntry_0050cdd0(EEContext&);  // generated body
void fn_ProbeTLBEntry_0050cdd0__recomp(EEContext&);  // recompiled
void fn_iProbeTLBEntry_0050cde0(EEContext&);  // generated body
void fn_iProbeTLBEntry_0050cde0__recomp(EEContext&);  // recompiled
void fn_ExpandScratchPad_0050cdf0(EEContext&);  // generated body
void fn_ExpandScratchPad_0050cdf0__recomp(EEContext&);  // recompiled
void fn_LoadExecPS2_0050da10(EEContext&);  // generated body
void fn_LoadExecPS2_0050da10__recomp(EEContext&);  // recompiled
void fn_ExecOSD_0050da80(EEContext&);  // generated body
void fn_ExecOSD_0050da80__recomp(EEContext&);  // recompiled
void fn_sub_50DEC0_0050dec0(EEContext&);  // generated body
void fn_sub_50DEC0_0050dec0__recomp(EEContext&);  // recompiled
void fn_sub_50DF80_0050df80(EEContext&);  // generated body
void fn_sub_50DF80_0050df80__recomp(EEContext&);  // recompiled
void fn_sub_50E558_0050e558(EEContext&);  // generated body
void fn_sub_50E558_0050e558__recomp(EEContext&);  // recompiled
void fn_sceCdCallback_0050f630(EEContext&);  // generated body
void fn_sceCdCallback_0050f630__recomp(EEContext&);  // recompiled
void fn_sceCdSearchFile_0050ff38(EEContext&);  // generated body
void fn_sceCdSearchFile_0050ff38__recomp(EEContext&);  // recompiled
void fn_sceCdGetDiskType_00510ec8(EEContext&);  // generated body
void fn_sceCdGetDiskType_00510ec8__recomp(EEContext&);  // recompiled
void fn_scePadEnd_005113c8(EEContext&);  // generated body
void fn_scePadEnd_005113c8__recomp(EEContext&);  // recompiled
void fn_scePadPortClose_00511778(EEContext&);  // generated body
void fn_scePadPortClose_00511778__recomp(EEContext&);  // recompiled
void fn_scePadSetVrefParam_005124a0(EEContext&);  // generated body
void fn_scePadSetVrefParam_005124a0__recomp(EEContext&);  // recompiled
void fn_scePadGetPortMax_00512570(EEContext&);  // generated body
void fn_scePadGetPortMax_00512570__recomp(EEContext&);  // recompiled
void fn_scePadGetSlotMax_005125d8(EEContext&);  // generated body
void fn_scePadGetSlotMax_005125d8__recomp(EEContext&);  // recompiled
void fn_scePadSetWarningLevel_005126a8(EEContext&);  // generated body
void fn_scePadSetWarningLevel_005126a8__recomp(EEContext&);  // recompiled
void fn_sceSdTransToIOP_00512918(EEContext&);  // generated body
void fn_sceSdTransToIOP_00512918__recomp(EEContext&);  // recompiled
void fn_sceDbcGetIopDmabuff_0051c6a0(EEContext&);  // generated body
void fn_sceDbcGetIopDmabuff_0051c6a0__recomp(EEContext&);  // recompiled
void fn_sceDbcGetDepNumber_0051c960(EEContext&);  // generated body
void fn_sceDbcGetDepNumber_0051c960__recomp(EEContext&);  // recompiled
void fn_sceDbcInitSocket_0051cbc8(EEContext&);  // generated body
void fn_sceDbcInitSocket_0051cbc8__recomp(EEContext&);  // recompiled
void fn_sceDbcResetSocket_0051cc78(EEContext&);  // generated body
void fn_sceDbcResetSocket_0051cc78__recomp(EEContext&);  // recompiled
void fn_sceDbcGetDeviceStatus_0051cd28(EEContext&);  // generated body
void fn_sceDbcGetDeviceStatus_0051cd28__recomp(EEContext&);  // recompiled
void fn_sceDbcSRData_0051ce98(EEContext&);  // generated body
void fn_sceDbcSRData_0051ce98__recomp(EEContext&);  // recompiled
void fn_sceDbcSendData_0051d028(EEContext&);  // generated body
void fn_sceDbcSendData_0051d028__recomp(EEContext&);  // recompiled
void fn_sceDbcSendData2_0051d158(EEContext&);  // generated body
void fn_sceDbcSendData2_0051d158__recomp(EEContext&);  // recompiled
void fn_sceDbcReceiveData_0051d460(EEContext&);  // generated body
void fn_sceDbcReceiveData_0051d460__recomp(EEContext&);  // recompiled
void fn_sceSkSsQuit_0051dae0(EEContext&);  // generated body
void fn_sceSkSsQuit_0051dae0__recomp(EEContext&);  // recompiled
void fn_sub_53D198_0053d198(EEContext&);  // generated body
void fn_sub_53D198_0053d198__recomp(EEContext&);  // recompiled
void fn_sub_53DF50_0053df50(EEContext&);  // generated body
void fn_sub_53DF50_0053df50__recomp(EEContext&);  // recompiled
void fn_sub_547998_00547998(EEContext&);  // generated body
void fn_sub_547998_00547998__recomp(EEContext&);  // recompiled
void fn_dtx_svr_proc_00559508(EEContext&);  // generated body
void fn_dtx_svr_proc_00559508__recomp(EEContext&);  // recompiled
void fn_RFMAI_UnMountG_005680d8(EEContext&);  // generated body
void fn_RFMAI_UnMountG_005680d8__recomp(EEContext&);  // recompiled
void fn_RFMAI_OpenRangeG_005685b8(EEContext&);  // generated body
void fn_RFMAI_OpenRangeG_005685b8__recomp(EEContext&);  // recompiled
void fn_RFMAI_LoadDirG_00568e38(EEContext&);  // generated body
void fn_RFMAI_LoadDirG_00568e38__recomp(EEContext&);  // recompiled
void fn_RFMAI_SetIsoDirG_00569230(EEContext&);  // generated body
void fn_RFMAI_SetIsoDirG_00569230__recomp(EEContext&);  // recompiled
void fn_RFMAI_IsExistFile_005692e0(EEContext&);  // generated body
void fn_RFMAI_IsExistFile_005692e0__recomp(EEContext&);  // recompiled
void fn_sub_569390_00569390(EEContext&);  // generated body
void fn_sub_569390_00569390__recomp(EEContext&);  // recompiled
void fn_sub_569420_00569420(EEContext&);  // generated body
void fn_sub_569420_00569420__recomp(EEContext&);  // recompiled
void fn_sub_5698B0_005698b0(EEContext&);  // generated body
void fn_sub_5698B0_005698b0__recomp(EEContext&);  // recompiled
void fn_RFMAI_GetScrambleInfG_00569c28(EEContext&);  // generated body
void fn_RFMAI_GetScrambleInfG_00569c28__recomp(EEContext&);  // recompiled
void fn_ROFS_CheckDirrecFile_00569ec0(EEContext&);  // generated body
void fn_ROFS_CheckDirrecFile_00569ec0__recomp(EEContext&);  // recompiled
void fn_sub_56C9A0_0056c9a0(EEContext&);  // generated body
void fn_sub_56C9A0_0056c9a0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

namespace L = p3fes::game::libs27;

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sceSifQueryTotalFreeMemSize", 0x50B978, &recomp_gen::fn_sceSifQueryTotalFreeMemSize_0050b978, &recomp_gen::fn_sceSifQueryTotalFreeMemSize_0050b978__recomp},
    {"sceSifQueryBlockTopAddress", 0x50B9E8, &recomp_gen::fn_sceSifQueryBlockTopAddress_0050b9e8, &recomp_gen::fn_sceSifQueryBlockTopAddress_0050b9e8__recomp},
    {"sceSifQueryBlockSize", 0x50BA68, &recomp_gen::fn_sceSifQueryBlockSize_0050ba68, &recomp_gen::fn_sceSifQueryBlockSize_0050ba68__recomp},
    {"sceSifStopModule", 0x50BEB8, &recomp_gen::fn_sceSifStopModule_0050beb8, &recomp_gen::fn_sceSifStopModule_0050beb8__recomp},
    {"sceSifUnloadModule", 0x50C0C0, &recomp_gen::fn_sceSifUnloadModule_0050c0c0, &recomp_gen::fn_sceSifUnloadModule_0050c0c0__recomp},
    {"sceSifSearchModuleByName", 0x50C150, &recomp_gen::fn_sceSifSearchModuleByName_0050c150, &recomp_gen::fn_sceSifSearchModuleByName_0050c150__recomp},
    {"sceSifSearchModuleByAddress", 0x50C1F0, &recomp_gen::fn_sceSifSearchModuleByAddress_0050c1f0, &recomp_gen::fn_sceSifSearchModuleByAddress_0050c1f0__recomp},
    {"sceSifLoadModuleBuffer", 0x50C280, &recomp_gen::fn_sceSifLoadModuleBuffer_0050c280, &recomp_gen::fn_sceSifLoadModuleBuffer_0050c280__recomp},
    {"sceSifLoadStartModuleBuffer", 0x50C2A0, &recomp_gen::fn_sceSifLoadStartModuleBuffer_0050c2a0, &recomp_gen::fn_sceSifLoadStartModuleBuffer_0050c2a0__recomp},
    {"sceSifLoadStartModule", 0x50C508, &recomp_gen::fn_sceSifLoadStartModule_0050c508, &recomp_gen::fn_sceSifLoadStartModule_0050c508__recomp},
    {"sceSifLoadElfPart", 0x50C630, &recomp_gen::fn_sceSifLoadElfPart_0050c630, &recomp_gen::fn_sceSifLoadElfPart_0050c630__recomp},
    {"sceSifLoadElf", 0x50C650, &recomp_gen::fn_sceSifLoadElf_0050c650, &recomp_gen::fn_sceSifLoadElf_0050c650__recomp},
    {"sceSifGetIopAddr", 0x50C678, &recomp_gen::fn_sceSifGetIopAddr_0050c678, &recomp_gen::fn_sceSifGetIopAddr_0050c678__recomp},
    {"sceSifSetIopAddr", 0x50C768, &recomp_gen::fn_sceSifSetIopAddr_0050c768, &recomp_gen::fn_sceSifSetIopAddr_0050c768__recomp},
    {"sceSifIsAliveIop", 0x50C9A0, &recomp_gen::fn_sceSifIsAliveIop_0050c9a0, &recomp_gen::fn_sceSifIsAliveIop_0050c9a0__recomp},
    {"PutTLBEntry", 0x50CD40, &recomp_gen::fn_PutTLBEntry_0050cd40, &recomp_gen::fn_PutTLBEntry_0050cd40__recomp},
    {"iPutTLBEntry", 0x50CD50, &recomp_gen::fn_iPutTLBEntry_0050cd50, &recomp_gen::fn_iPutTLBEntry_0050cd50__recomp},
    {"iSetTLBEntry", 0x50CDA0, &recomp_gen::fn_iSetTLBEntry_0050cda0, &recomp_gen::fn_iSetTLBEntry_0050cda0__recomp},
    {"GetTLBEntry", 0x50CDB0, &recomp_gen::fn_GetTLBEntry_0050cdb0, &recomp_gen::fn_GetTLBEntry_0050cdb0__recomp},
    {"iGetTLBEntry", 0x50CDC0, &recomp_gen::fn_iGetTLBEntry_0050cdc0, &recomp_gen::fn_iGetTLBEntry_0050cdc0__recomp},
    {"ProbeTLBEntry", 0x50CDD0, &recomp_gen::fn_ProbeTLBEntry_0050cdd0, &recomp_gen::fn_ProbeTLBEntry_0050cdd0__recomp},
    {"iProbeTLBEntry", 0x50CDE0, &recomp_gen::fn_iProbeTLBEntry_0050cde0, &recomp_gen::fn_iProbeTLBEntry_0050cde0__recomp},
    {"ExpandScratchPad", 0x50CDF0, &recomp_gen::fn_ExpandScratchPad_0050cdf0, &recomp_gen::fn_ExpandScratchPad_0050cdf0__recomp},
    {"LoadExecPS2", 0x50DA10, &recomp_gen::fn_LoadExecPS2_0050da10, &recomp_gen::fn_LoadExecPS2_0050da10__recomp},
    {"ExecOSD", 0x50DA80, &recomp_gen::fn_ExecOSD_0050da80, &recomp_gen::fn_ExecOSD_0050da80__recomp},
    {"sub_50DEC0", 0x50DEC0, &recomp_gen::fn_sub_50DEC0_0050dec0, &recomp_gen::fn_sub_50DEC0_0050dec0__recomp},
    {"sub_50DF80", 0x50DF80, &recomp_gen::fn_sub_50DF80_0050df80, &recomp_gen::fn_sub_50DF80_0050df80__recomp},
    {"sub_50E558", 0x50E558, &recomp_gen::fn_sub_50E558_0050e558, &recomp_gen::fn_sub_50E558_0050e558__recomp},
    {"sceCdCallback", 0x50F630, &recomp_gen::fn_sceCdCallback_0050f630, &recomp_gen::fn_sceCdCallback_0050f630__recomp},
    {"sceCdSearchFile", 0x50FF38, &recomp_gen::fn_sceCdSearchFile_0050ff38, &recomp_gen::fn_sceCdSearchFile_0050ff38__recomp},
    {"sceCdGetDiskType", 0x510EC8, &recomp_gen::fn_sceCdGetDiskType_00510ec8, &recomp_gen::fn_sceCdGetDiskType_00510ec8__recomp},
    {"scePadEnd", 0x5113C8, &recomp_gen::fn_scePadEnd_005113c8, &recomp_gen::fn_scePadEnd_005113c8__recomp},
    {"scePadPortClose", 0x511778, &recomp_gen::fn_scePadPortClose_00511778, &recomp_gen::fn_scePadPortClose_00511778__recomp},
    {"scePadSetVrefParam", 0x5124A0, &recomp_gen::fn_scePadSetVrefParam_005124a0, &recomp_gen::fn_scePadSetVrefParam_005124a0__recomp},
    {"scePadGetPortMax", 0x512570, &recomp_gen::fn_scePadGetPortMax_00512570, &recomp_gen::fn_scePadGetPortMax_00512570__recomp},
    {"scePadGetSlotMax", 0x5125D8, &recomp_gen::fn_scePadGetSlotMax_005125d8, &recomp_gen::fn_scePadGetSlotMax_005125d8__recomp},
    {"scePadSetWarningLevel", 0x5126A8, &recomp_gen::fn_scePadSetWarningLevel_005126a8, &recomp_gen::fn_scePadSetWarningLevel_005126a8__recomp},
    {"sceSdTransToIOP", 0x512918, &recomp_gen::fn_sceSdTransToIOP_00512918, &recomp_gen::fn_sceSdTransToIOP_00512918__recomp},
    {"sceDbcGetIopDmabuff", 0x51C6A0, &recomp_gen::fn_sceDbcGetIopDmabuff_0051c6a0, &recomp_gen::fn_sceDbcGetIopDmabuff_0051c6a0__recomp},
    {"sceDbcGetDepNumber", 0x51C960, &recomp_gen::fn_sceDbcGetDepNumber_0051c960, &recomp_gen::fn_sceDbcGetDepNumber_0051c960__recomp},
    {"sceDbcInitSocket", 0x51CBC8, &recomp_gen::fn_sceDbcInitSocket_0051cbc8, &recomp_gen::fn_sceDbcInitSocket_0051cbc8__recomp},
    {"sceDbcResetSocket", 0x51CC78, &recomp_gen::fn_sceDbcResetSocket_0051cc78, &recomp_gen::fn_sceDbcResetSocket_0051cc78__recomp},
    {"sceDbcGetDeviceStatus", 0x51CD28, &recomp_gen::fn_sceDbcGetDeviceStatus_0051cd28, &recomp_gen::fn_sceDbcGetDeviceStatus_0051cd28__recomp},
    {"sceDbcSRData", 0x51CE98, &recomp_gen::fn_sceDbcSRData_0051ce98, &recomp_gen::fn_sceDbcSRData_0051ce98__recomp},
    {"sceDbcSendData", 0x51D028, &recomp_gen::fn_sceDbcSendData_0051d028, &recomp_gen::fn_sceDbcSendData_0051d028__recomp},
    {"sceDbcSendData2", 0x51D158, &recomp_gen::fn_sceDbcSendData2_0051d158, &recomp_gen::fn_sceDbcSendData2_0051d158__recomp},
    {"sceDbcReceiveData", 0x51D460, &recomp_gen::fn_sceDbcReceiveData_0051d460, &recomp_gen::fn_sceDbcReceiveData_0051d460__recomp},
    {"sceSkSsQuit", 0x51DAE0, &recomp_gen::fn_sceSkSsQuit_0051dae0, &recomp_gen::fn_sceSkSsQuit_0051dae0__recomp},
    {"sub_53D198", 0x53D198, &recomp_gen::fn_sub_53D198_0053d198, &recomp_gen::fn_sub_53D198_0053d198__recomp},
    {"sub_53DF50", 0x53DF50, &recomp_gen::fn_sub_53DF50_0053df50, &recomp_gen::fn_sub_53DF50_0053df50__recomp},
    {"sub_547998", 0x547998, &recomp_gen::fn_sub_547998_00547998, &recomp_gen::fn_sub_547998_00547998__recomp},
    {"dtx_svr_proc", 0x559508, &recomp_gen::fn_dtx_svr_proc_00559508, &recomp_gen::fn_dtx_svr_proc_00559508__recomp},
    {"RFMAI_UnMountG", 0x5680D8, &recomp_gen::fn_RFMAI_UnMountG_005680d8, &recomp_gen::fn_RFMAI_UnMountG_005680d8__recomp},
    {"RFMAI_OpenRangeG", 0x5685B8, &recomp_gen::fn_RFMAI_OpenRangeG_005685b8, &recomp_gen::fn_RFMAI_OpenRangeG_005685b8__recomp},
    {"RFMAI_LoadDirG", 0x568E38, &recomp_gen::fn_RFMAI_LoadDirG_00568e38, &recomp_gen::fn_RFMAI_LoadDirG_00568e38__recomp},
    {"RFMAI_SetIsoDirG", 0x569230, &recomp_gen::fn_RFMAI_SetIsoDirG_00569230, &recomp_gen::fn_RFMAI_SetIsoDirG_00569230__recomp},
    {"RFMAI_IsExistFile", 0x5692E0, &recomp_gen::fn_RFMAI_IsExistFile_005692e0, &recomp_gen::fn_RFMAI_IsExistFile_005692e0__recomp},
    {"sub_569390", 0x569390, &recomp_gen::fn_sub_569390_00569390, &recomp_gen::fn_sub_569390_00569390__recomp},
    {"sub_569420", 0x569420, &recomp_gen::fn_sub_569420_00569420, &recomp_gen::fn_sub_569420_00569420__recomp},
    {"sub_5698B0", 0x5698B0, &recomp_gen::fn_sub_5698B0_005698b0, &recomp_gen::fn_sub_5698B0_005698b0__recomp},
    {"RFMAI_GetScrambleInfG", 0x569C28, &recomp_gen::fn_RFMAI_GetScrambleInfG_00569c28, &recomp_gen::fn_RFMAI_GetScrambleInfG_00569c28__recomp},
    {"ROFS_CheckDirrecFile", 0x569EC0, &recomp_gen::fn_ROFS_CheckDirrecFile_00569ec0, &recomp_gen::fn_ROFS_CheckDirrecFile_00569ec0__recomp},
    {"sub_56C9A0", 0x56C9A0, &recomp_gen::fn_sub_56C9A0_0056c9a0, &recomp_gen::fn_sub_56C9A0_0056c9a0__recomp},
};

// Random worlds: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

constexpr u32 kWaitSema = 0x5031A0u;    // _sceWaitSema (a kernel wrapper; stood in)
constexpr u32 kSignalSema = 0x503180u;  // _sceSignalSema

u32 r32(Machine& m, u32 va) {
    u32 v = 0;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w64(Machine& m, u32 va, u64 v) { std::memcpy(m.at(va), &v, 8); }
u8 r8(Machine& m, u32 va) { return *m.at(va); }
void wstr(Machine& m, u32 va, const std::string& s) { std::memcpy(m.at(va), s.c_str(), s.size() + 1); }

// Pairs with the stand-ins: both bodies get a fresh set and the two call logs must be equal.
StandInWorld* g_si[2];
Fn g_fn[2];
void thunk0(EEContext& ctx) {
    StandInsScope s(g_si[0]->si);
    g_fn[0](ctx);
}
void thunk1(EEContext& ctx) {
    StandInsScope s(g_si[1]->si);
    g_fn[1](ctx);
}
int g_pairs = 0;
int g_stops = 0;
hgp::Run spair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, const HwCheck& hw = {}) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    for (StandInWorld* w : {wh.get(), wr.get()}) {
        install_sprintf(w->si);
        w->si.install_recorder(kWaitSema, "_sceWaitSema", 0);
        w->si.install_recorder(kSignalSema, "_sceSignalSema", 0);
    }
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, what, hw);
    expect_same_log(wh->si, wr->si, what);
    ++g_pairs;
    g_stops += r.stopped ? 1 : 0;
    return r;
}

const Case& find_case(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
s64 sv(const hgp::Run& r) { return static_cast<s64>(v0_of(r)); }

// Timer 1 as the bodies see it: a random mode (clock source, overflow flag bit 7, pending bit 11) and count.
HwCheck timer_hw(std::mt19937& rng) {
    HwCheck hw;
    const u32 bits = (rng() % 4) | (rng() % 2 ? 0x80u : 0u) | (rng() % 2 ? 0x800u : 0u) | (rng() % 2 ? 0x400u : 0u);
    hw.regs[L::kT1Mode] = bits;
    hw.regs[L::kT1Count] = rng() & 0xFFFFu;
    return hw;
}

// The library globals the bodies branch on, drawn from the values they compare.
void guard_world(Machine& m, std::mt19937& rng) {
    static const u32 kSmall[] = {0u, 1u, 2u, 0xFFFFFFFFu};
    const auto pick = [&] { return kSmall[rng() % 4]; };
    w32(m, L::kHeapBound, pick());
    w32(m, L::kTimerAlloc, pick());
    w64(m, L::kTimerOverflows, rng() % 3 == 0 ? (static_cast<u64>(rng()) << 32 | rng()) : rng() % 100);
    w32(m, L::kCdCallback, rng() % 2 ? 0u : kWorld + 0x100u);
    w32(m, L::kPadOpen, rng() % 2);
    for (u32 port = 0; port < 2; ++port)
        for (u32 slot = 0; slot < 4; ++slot) w32(m, L::kPadPorts + 112 * port + 28 * slot, rng() % 2);
    w32(m, L::kDbcSema, rng() % 8);
    for (u32 i = 0; i < 16; ++i) {
        w32(m, L::kDbcStateLive + 4 * i, rng() % 3);
        w32(m, L::kDbcState + 4 * i, rng() % 3);
    }
}

u64 guard_arg(std::mt19937& rng) {
    const u32 k = rng() % 8;
    if (k < 4) return rng() % 4;
    if (k < 5) return sx(0xFFFFFFFFu);
    if (k < 7) return sx(kWorld + ((rng() % kWorldSize) & ~15u));
    return sx(rng());
}

// --- the ROFS world of a snapshot ---------------------------------------------------------------------------------
// The live work area (*0x7B2700): +8 volume slots, +40 the RofsVolume array (52 bytes: +0 image handle, +16 the
// directory table, +22 the name, +44 the dirrec bytes), a table = 24-byte header (+0 count) then 48-byte entries
// (+0 size, +8 lba, +12 flags, +14 name).
constexpr u32 kRofsWorkPtr = 0x7B2700u;
struct Vol {
    u32 va = 0;
    std::string name;
    u32 dir = 0;
    u32 count = 0;
};
std::vector<Vol> live_volumes(Machine& m) {
    std::vector<Vol> v;
    const u32 work = r32(m, kRofsWorkPtr);
    if (work == 0 || work >= 0x02000000u) return v;
    const u32 n = std::min<u32>(r32(m, work + 8), 8);
    const u32 vols = r32(m, work + 40);
    if (vols == 0 || vols >= 0x02000000u) return v;
    for (u32 i = 0; i < n; ++i) {
        Vol x;
        x.va = vols + 52 * i;
        x.name = m.str(x.va + 22, 9);
        if (x.name.empty() || r32(m, x.va) == 0) continue;
        x.dir = r32(m, x.va + 16);
        if (x.dir == 0 || x.dir >= 0x02000000u) continue;
        x.count = r32(m, x.dir);
        if (x.count < 3 || x.count > 4096) continue;
        v.push_back(x);
    }
    return v;
}
u32 entry(const Vol& v, u32 i) { return v.dir + 24 + 48 * i; }
std::string entry_name(Machine& m, const Vol& v, u32 i) { return m.str(entry(v, i) + 14, 34); }

// Strings in the world for the ROFS calls: volume names, "VOL:NAME" paths (real files, a missing one, an absolute path,
// the device name), each at kWorld + 0x40 * k; the buffers the bodies fill follow at kOut.
constexpr u32 kText = kWorld;
constexpr u32 kOut = kWorld + 0x2000u;
std::vector<u32> rofs_texts(Machine& m, const std::vector<Vol>& vols, std::mt19937& rng) {
    std::vector<std::string> s = {"ROFS", "NOVOL", "", "ROFS:NOFILE.BIN", "BAD"};
    for (const Vol& v : vols) {
        s.push_back(v.name);
        s.push_back(v.name + ":NOSUCH.BIN");
        s.push_back(v.name + ":/");
        for (int k = 0; k < 3; ++k) {
            const std::string e = entry_name(m, v, 2 + rng() % (v.count - 2));
            if (!e.empty() && e.size() < 24) s.push_back(v.name + ":" + e);
        }
        const std::string e = entry_name(m, v, 2);
        if (!e.empty() && e.size() < 24) s.push_back(v.name + ":/" + e);
    }
    std::vector<u32> at;
    for (std::size_t k = 0; k < s.size() && k < 0x80; ++k) {
        const u32 va = kText + 0x40u * static_cast<u32>(k);
        wstr(m, va, s[k]);
        at.push_back(va);
    }
    std::memset(m.at(kOut), 0, 0x1000);
    return at;
}
u64 rofs_arg(std::mt19937& rng, const std::vector<u32>& texts) {
    const u32 k = rng() % 10;
    if (k < 5) return sx(texts[rng() % texts.size()]);
    if (k < 6) return sx(kOut + 0x100u * (rng() % 8));
    if (k < 8) return rng() % 6;
    if (k < 9) return 0;
    return sx(0xFFFFFFFFu);
}

const char* const kSnaps[] = {"dorm_replay_4900", "b_5800", "climb_ref_17000"};

}  // namespace

TEST_CASE("game(libs27): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    g_pairs = g_stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            spair(*m, c.hand, c.recomp, args, seed, c.name, timer_hw(rng));
        }
    }
    MESSAGE(g_pairs << " pairs on random worlds, " << g_stops << " stopped early (identically)");
}

TEST_CASE("game(libs27): every body equals its recompiled body with the library globals at their branch values") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : 32u;
    const char* only = std::getenv("P3FES_HG_ONLY");
    g_pairs = g_stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            std::mt19937 rng{seed * 104729u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            guard_world(*m, rng);
            const Args args{guard_arg(rng), guard_arg(rng), guard_arg(rng), guard_arg(rng)};
            spair(*m, c.hand, c.recomp, args, seed, c.name, timer_hw(rng));
        }
    }
    MESSAGE(g_pairs << " pairs on guard worlds, " << g_stops << " stopped early (identically)");
}

// Every body over the RAM of the replay snapshots: the live loadfile / heap / pad / DBC client state and the mounted
// ROFS volumes with their directory tables, the ROFS calls on real "VOL:NAME" paths.
TEST_CASE("game(libs27): every body equals its recompiled body on the replay snapshots' live state") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? std::max<u32>(1, static_cast<u32>(std::strtoul(env, nullptr, 10)) / 8) : 6u;
    const char* only = std::getenv("P3FES_HG_ONLY");
    g_pairs = g_stops = 0;
    for (const char* dir : kSnaps) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.size() != EEMemory::kMainRamSize) {
            MESSAGE("SKIP: snapshot " << dir << " not found");
            continue;
        }
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        const std::vector<Vol> vols = live_volumes(*m);
        CHECK(!vols.empty());  // ROFS is mounted on every route
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            for (u32 seed = 1; seed <= seeds; ++seed) {
                std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
                std::mt19937 rng{seed * 131u + c.addr};
                const std::vector<u32> texts = rofs_texts(*m, vols, rng);
                const Args args{rofs_arg(rng, texts), rofs_arg(rng, texts), rofs_arg(rng, texts), rofs_arg(rng, texts)};
                spair(*m, c.hand, c.recomp, args, seed, c.name, timer_hw(rng));
            }
        }
        MESSAGE(std::string(dir) << ": " << vols.size() << " mounted volumes");
    }
    MESSAGE(g_pairs << " pairs on snapshot state, " << g_stops << " stopped early (identically)");
}

// Documented rules, from the instructions (both bodies run and are compared, then the result is checked). Only results
// that hold whatever the callees are (replaced or recompiled) are checked.
TEST_CASE("game(libs27): timer, SIF / pad / DBC guards, syscall wrappers") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const auto run = [&](const char* name, const Args& a, const HwCheck& hw = {}) {
        const Case& c = find_case(name);
        return spair(*m, c.hand, c.recomp, a, 1, c.name, hw);
    };
    g_pairs = g_stops = 0;
    HwCheck hw;
    // sub_50DEC0: the clock source when the timer is allocated, else 0x80008001 (sign-extended by lui)
    w32(*m, L::kTimerAlloc, 0xFFFFFFFFu);
    hw.regs[L::kT1Mode] = 0x82;
    CHECK(v0_of(run("sub_50DEC0", Args{0, 0, 0, 0}, hw)) == L::kTimerErrNotAlloc);
    w32(*m, L::kTimerAlloc, 0);
    CHECK(v0_of(run("sub_50DEC0", Args{0, 0, 0, 0}, hw)) == 2u);
    // sub_50E558: ((overflows (+1 when bit 11 is pending)) << 16 | count) << (source ? 2 << source : 0)
    w64(*m, L::kTimerOverflows, 5);
    for (const u32 mode : {0x000u, 0x001u, 0x002u, 0x003u, 0x801u, 0x800u}) {
        hw.regs[L::kT1Mode] = mode;
        hw.regs[L::kT1Count] = 0x1234;
        const u64 ov = 5u + ((mode & 0x800u) ? 1u : 0u);
        const u32 src = mode & 3u;
        const u64 expect = ((ov << 16) | 0x1234u) << (src ? (2u << src) : 0u);
        CHECK(v0_of(run("sub_50E558", Args{0, 0, 0, 0}, hw)) == expect);
    }
    // sub_50DF80: no overflow flag (bit 7) -> 0 (the set path writes the mode back through sub_50DC90)
    hw.regs[L::kT1Mode] = 0x0C01;
    CHECK(v0_of(run("sub_50DF80", Args{0, 0, 0, 0}, hw)) == 0u);
    // the heap RPC clients: not bound -> 0 before any call
    w32(*m, L::kHeapBound, 0xFFFFFFFFu);
    for (const char* n : {"sceSifQueryTotalFreeMemSize", "sceSifQueryBlockTopAddress", "sceSifQueryBlockSize"}) {
        const hgp::Run r = run(n, Args{0x1000, 0, 0, 0});
        CHECK(!r.stopped);
        CHECK(v0_of(r) == 0u);
    }
    // sceSdTransToIOP: a3 == 0 -> -1 without a DMA
    {
        const hgp::Run r = run("sceSdTransToIOP", Args{kWorld, 0x1000, 0x40, 0});
        CHECK(!r.stopped);
        CHECK(sv(r) == -1);
    }
    // scePadEnd: not open -> 1; scePadPortClose: a closed port / slot -> 0
    w32(*m, L::kPadOpen, 0);
    CHECK(v0_of(run("scePadEnd", Args{0, 0, 0, 0})) == 1u);
    w32(*m, L::kPadPorts + 112 * 1 + 28 * 2, 0);
    CHECK(v0_of(run("scePadPortClose", Args{1, 2, 0, 0})) == 0u);
    // sceDbcGetDepNumber: the live table is copied (64 bytes), a socket not in state 1 -> -12 before the semaphore
    for (u32 i = 0; i < 16; ++i) {
        w32(*m, L::kDbcStateLive + 4 * i, i == 3 ? 2u : 1u);
        w32(*m, L::kDbcState + 4 * i, 0);
    }
    {
        const hgp::Run r = run("sceDbcGetDepNumber", Args{3, 0, 0, 0});
        CHECK(sv(r) == L::kDbcErrNotConnected);
        CHECK(std::memcmp(m->at(L::kDbcStateLive), m->at(L::kDbcState), 64) == 0);
    }
    // the syscall wrappers: one syscall each, its result in $v0
    for (const char* n : {"PutTLBEntry", "iPutTLBEntry", "iSetTLBEntry", "GetTLBEntry", "iGetTLBEntry", "ProbeTLBEntry",
                          "iProbeTLBEntry", "ExpandScratchPad"}) {
        const hgp::Run r = run(n, Args{1, 2, 3, 4});
        CHECK(r.syscalls == 1);
        CHECK(v0_of(r) == 0x600DF00Du);
    }
    MESSAGE(g_pairs << " pairs for the rules");
}

// ROFS on a snapshot's mounted volumes: counts, entry records, existence, the scramble record, the dirrec compare, the
// image-handle store and the parameter / volume errors (the error callback cleared, so sub_569730 returns the code).
TEST_CASE("game(libs27): ROFS -- file counts, entry records, existence, scramble info, dirrec, errors") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    std::vector<u8> snap;
    for (const char* dir : kSnaps) {
        snap = read_snapshot(dir);
        if (snap.size() == EEMemory::kMainRamSize) break;
    }
    if (snap.size() != EEMemory::kMainRamSize) {
        MESSAGE("SKIP: no snapshot");
        return;
    }
    std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
    const std::vector<Vol> vols = live_volumes(*m);
    REQUIRE(!vols.empty());
    const Vol& v = vols[0];
    const u32 work = r32(*m, kRofsWorkPtr);
    w32(*m, work + L::kRofsWorkErrCb, 0);
    const auto run = [&](const char* name, const Args& a) {
        const Case& c = find_case(name);
        return spair(*m, c.hand, c.recomp, a, 1, c.name);
    };
    g_pairs = g_stops = 0;
    const u32 tVol = kWorld, tFile = kWorld + 0x40, tMissing = kWorld + 0x80, tNoVol = kWorld + 0xC0, tDev = kWorld + 0x100;
    // a plain file (not a directory) with a short name, from entry 2 on
    u32 fi = 0;
    for (u32 i = 2; i < v.count && fi == 0; ++i) {
        const std::string e = entry_name(*m, v, i);
        if (!e.empty() && e.size() < 24 && (r8(*m, entry(v, i) + 12) & 2u) == 0) fi = i;
    }
    REQUIRE(fi != 0);
    wstr(*m, tVol, v.name);
    wstr(*m, tFile, v.name + ":" + entry_name(*m, v, fi));
    wstr(*m, tMissing, v.name + ":NOSUCH.ZZZ");
    wstr(*m, tNoVol, "ZZZZ:A.BIN");
    wstr(*m, tDev, "ROFS");
    // the file count: entries - 2 ("." and ".."); unknown volume -105
    CHECK(sv(run("sub_569390", Args{tVol, 0, 0, 0})) == static_cast<s64>(v.count) - 2);
    CHECK(sv(run("sub_569390", Args{tNoVol + 5, 0, 0, 0})) == L::kRofsErrVolume);  // "A.BIN" as a volume name
    // the entry records: min(n, count) records of 16 bytes (size, size high, the name's address, the flags)
    std::memset(m->at(kOut), 0xEE, 0x100);
    CHECK(sv(run("sub_569420", Args{tVol, kOut, 3, 0})) == 3);
    for (u32 i = 0; i < 3; ++i) {
        CHECK(r32(*m, kOut + 16 * i) == r32(*m, entry(v, i)));
        CHECK(r32(*m, kOut + 16 * i + 4) == r32(*m, entry(v, i) + 4));
        CHECK(r32(*m, kOut + 16 * i + 8) == entry(v, i) + 14);
        CHECK(r8(*m, kOut + 16 * i + 12) == r8(*m, entry(v, i) + 12));
    }
    CHECK(r8(*m, kOut + 48) == 0xEE);
    if (v.count <= 200) CHECK(sv(run("sub_569420", Args{tVol, kOut, 0x7FFF, 0})) == static_cast<s64>(v.count));  // n capped at the count
    CHECK(sv(run("sub_569420", Args{tVol, kOut, sx(0xFFFFFFFFu), 0})) == L::kRofsErrParam);
    CHECK(sv(run("sub_569420", Args{tVol, 0, 3, 0})) == L::kRofsErrParam);
    // existence
    CHECK(v0_of(run("RFMAI_IsExistFile", Args{tFile, 0, 0, 0})) == 1u);
    CHECK(v0_of(run("RFMAI_IsExistFile", Args{tMissing, 0, 0, 0})) == 0u);
    CHECK(v0_of(run("RFMAI_IsExistFile", Args{tNoVol, 0, 0, 0})) == 0u);
    // the scramble record: the volume and the entry's lba word; a missing entry -107 (the record cleared)
    std::memset(m->at(kOut), 0xEE, 0x40);
    CHECK(sv(run("RFMAI_GetScrambleInfG", Args{tFile, kOut, 0, 0})) == 0);
    CHECK(r32(*m, kOut) == v.va);
    CHECK(r32(*m, kOut + 4) == r32(*m, entry(v, fi) + 8));
    for (u32 k = 8; k < 32; k += 4) CHECK(r32(*m, kOut + k) == 0u);
    CHECK(sv(run("RFMAI_GetScrambleInfG", Args{tMissing, kOut, 0, 0})) == L::kRofsErrNoEntry);
    CHECK(sv(run("RFMAI_GetScrambleInfG", Args{tFile, 0, 0, 0})) == L::kRofsErrParam);
    CHECK(sv(run("RFMAI_GetScrambleInfG", Args{tNoVol, kOut, 0, 0})) == L::kRofsErrVolume);
    // the dirrec compare: equal 8 bytes -> 0, else -111
    std::memcpy(m->at(kOut), m->at(v.va + L::kRofsVolDirrec), 8);
    CHECK(sv(run("ROFS_CheckDirrecFile", Args{tVol, kOut, 0, 0})) == 0);
    *m->at(kOut + 7) ^= 0x5A;
    CHECK(sv(run("ROFS_CheckDirrecFile", Args{tVol, kOut, 0, 0})) == L::kRofsErrDirrec);
    CHECK(sv(run("ROFS_CheckDirrecFile", Args{tNoVol + 5, kOut, 0, 0})) == L::kRofsErrVolume);
    // parameter and device-name errors
    CHECK(sv(run("RFMAI_UnMountG", Args{0, 0, 0, 0})) == L::kRofsErrParam);
    CHECK(sv(run("RFMAI_UnMountG", Args{tDev, 0, 0, 0})) == L::kRofsErrDevName);
    CHECK(sv(run("RFMAI_SetIsoDirG", Args{tVol, 0, 0, 0})) == L::kRofsErrParam);
    CHECK(v0_of(run("RFMAI_OpenRangeG", Args{tVol, sx(0xFFFFFFFFu), 4, 0})) == 0u);
    CHECK(v0_of(run("RFMAI_OpenRangeG", Args{tVol, 16, sx(0xFFFFFFFFu), 0})) == 0u);
    // the image-handle store: the value lands in the volume's first word; no value -100
    const u32 hn = r32(*m, v.va);
    CHECK(sv(run("sub_5698B0", Args{tVol, 0x1234, 0, 0})) == 0);
    CHECK(r32(*m, v.va) == 0x1234u);
    CHECK(sv(run("sub_5698B0", Args{tVol, 0, 0, 0})) == L::kRofsErrParam);
    CHECK(sv(run("sub_5698B0", Args{0, 0x1234, 0, 0})) == L::kRofsErrParam);
    w32(*m, v.va, hn);
    MESSAGE(g_pairs << " pairs for the ROFS rules on volume " << v.name << " (" << v.count << " entries)");
}

#else

TEST_CASE("game(libs27): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
