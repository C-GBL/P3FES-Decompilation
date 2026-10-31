// The imports the generated SK code calls (sk_imports.cpp): one per library function the six modules import, named
// imp_<library>_<function> (ps2sdk's import names) -- the libsd ordinals go to the IOP model's libsd, the kernel ones to
// NativeSk (sk_host.h).
#pragma once

#include "sk_cpu.h"

namespace p3fes::native::sound::sk {

void imp_intrman_CpuSuspendIntr(Cpu& c);  // intrman 17
void imp_intrman_CpuResumeIntr(Cpu& c);  // intrman 18
void imp_libsd_sceSdInit(Cpu& c);  // libsd 4
void imp_libsd_sceSdSetParam(Cpu& c);  // libsd 5
void imp_libsd_sceSdGetParam(Cpu& c);  // libsd 6
void imp_libsd_sceSdSetSwitch(Cpu& c);  // libsd 7
void imp_libsd_sceSdGetSwitch(Cpu& c);  // libsd 8
void imp_libsd_sceSdSetAddr(Cpu& c);  // libsd 9
void imp_libsd_sceSdGetAddr(Cpu& c);  // libsd 10
void imp_libsd_sceSdSetCoreAttr(Cpu& c);  // libsd 11
void imp_libsd_sceSdGetCoreAttr(Cpu& c);  // libsd 12
void imp_libsd_sceSdNote2Pitch(Cpu& c);  // libsd 13
void imp_libsd_sceSdPitch2Note(Cpu& c);  // libsd 14
void imp_libsd_sceSdProcBatch(Cpu& c);  // libsd 15
void imp_libsd_sceSdProcBatchEx(Cpu& c);  // libsd 16
void imp_libsd_sceSdVoiceTrans(Cpu& c);  // libsd 17
void imp_libsd_sceSdBlockTrans(Cpu& c);  // libsd 18
void imp_libsd_sceSdVoiceTransStatus(Cpu& c);  // libsd 19
void imp_libsd_sceSdBlockTransStatus(Cpu& c);  // libsd 20
void imp_libsd_sceSdSetEffectAttr(Cpu& c);  // libsd 23
void imp_libsd_sceSdGetEffectAttr(Cpu& c);  // libsd 24
void imp_libsd_sceSdClearEffectWorkArea(Cpu& c);  // libsd 25
void imp_libsd_sceSdSetTransIntrHandler(Cpu& c);  // libsd 26
void imp_libsd_sceSdSetSpu2IntrHandler(Cpu& c);  // libsd 27
void imp_libsd_sceSdStopTrans(Cpu& c);  // libsd 30
void imp_libsd_sceSdCleanEffectWorkArea(Cpu& c);  // libsd 31
void imp_libsd_sceSdSetEffectMode(Cpu& c);  // libsd 32
void imp_libsd_sceSdSetEffectModeParams(Cpu& c);  // libsd 33
void imp_loadcore_RegisterLibraryEntries(Cpu& c);  // loadcore 6
void imp_loadcore_ReleaseLibraryEntries(Cpu& c);  // loadcore 7
void imp_sifcmd_sceSifInitRpc(Cpu& c);  // sifcmd 14
void imp_sifcmd_sceSifBindRpc(Cpu& c);  // sifcmd 15
void imp_sifcmd_sceSifCallRpc(Cpu& c);  // sifcmd 16
void imp_sifcmd_sceSifRegisterRpc(Cpu& c);  // sifcmd 17
void imp_sifcmd_sceSifSetRpcQueue(Cpu& c);  // sifcmd 19
void imp_sifcmd_sceSifRpcLoop(Cpu& c);  // sifcmd 22
void imp_sifcmd_sceSifRemoveRpc(Cpu& c);  // sifcmd 24
void imp_sifcmd_sceSifRemoveRpcQueue(Cpu& c);  // sifcmd 25
void imp_stdio_printf(Cpu& c);  // stdio 4
void imp_sysclib_look_ctype_table(Cpu& c);  // sysclib 8
void imp_sysclib_memset(Cpu& c);  // sysclib 14
void imp_sysclib_bzero(Cpu& c);  // sysclib 17
void imp_sysclib_strlen(Cpu& c);  // sysclib 27
void imp_sysclib_strncmp(Cpu& c);  // sysclib 29
void imp_sysclib_strtol(Cpu& c);  // sysclib 36
void imp_sysmem_AllocSysMemory(Cpu& c);  // sysmem 4
void imp_sysmem_FreeSysMemory(Cpu& c);  // sysmem 5
void imp_sysmem_Kprintf(Cpu& c);  // sysmem 14
void imp_thbase_CreateThread(Cpu& c);  // thbase 4
void imp_thbase_DeleteThread(Cpu& c);  // thbase 5
void imp_thbase_StartThread(Cpu& c);  // thbase 6
void imp_thbase_TerminateThread(Cpu& c);  // thbase 10
void imp_thbase_ChangeThreadPriority(Cpu& c);  // thbase 14
void imp_thbase_GetThreadId(Cpu& c);  // thbase 20
void imp_thbase_ReferThreadStatus(Cpu& c);  // thbase 22
void imp_thbase_SleepThread(Cpu& c);  // thbase 24
void imp_thbase_iWakeupThread(Cpu& c);  // thbase 26
void imp_thbase_iCancelWakeupThread(Cpu& c);  // thbase 28
void imp_thbase_GetSystemTime(Cpu& c);  // thbase 34
void imp_thbase_USec2SysClock(Cpu& c);  // thbase 39
void imp_thbase_SysClock2USec(Cpu& c);  // thbase 40
void imp_thsemap_CreateSema(Cpu& c);  // thsemap 4
void imp_thsemap_DeleteSema(Cpu& c);  // thsemap 5
void imp_thsemap_SignalSema(Cpu& c);  // thsemap 6
void imp_thsemap_WaitSema(Cpu& c);  // thsemap 8
void imp_timrman_AllocHardTimer(Cpu& c);  // timrman 4
void imp_timrman_FreeHardTimer(Cpu& c);  // timrman 6
void imp_timrman_SetTimerHandler(Cpu& c);  // timrman 20
void imp_timrman_SetupHardTimer(Cpu& c);  // timrman 22
void imp_timrman_StartHardTimer(Cpu& c);  // timrman 23
void imp_timrman_StopHardTimer(Cpu& c);  // timrman 24

}  // namespace p3fes::native::sound::sk