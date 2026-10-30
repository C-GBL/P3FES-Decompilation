// High-level emulation of the Sony PS2 SDK (libsce*) surface.
//
// The static recompiler will emit calls to the game's own copies of these
// library routines unless they are intercepted. This namespace is where the
// intercepts live. Nothing is implemented yet; the families that must be
// covered (names per the official SDK, which IDA labelling prefers) are:
//
//   sceGs*   GS setup/display environment: sceGsResetGraph, sceGsSetDefDispEnv,
//            sceGsPutDispEnv, sceGsSetDefDrawEnv, sceGsSyncV, sceGsSyncPath, ...
//   sceDma*  DMAC channel control: sceDmaGetChan, sceDmaSend, sceDmaSync, ...
//   sceVif*  VIF0/VIF1 packet helpers and VIF register access.
//   sceVu*   VU0/VU1 microprogram upload and control (sceVu1PutMicro, ...).
//   sceCd*   CD/DVD access over SIF: sceCdInit, sceCdRead, sceCdSync, sceCdSearchFile, ...
//   sceSif*  SIF RPC/CMD plumbing to the IOP: sceSifInitRpc, sceSifBindRpc, sceSifCallRpc, ...
//   scePad*  DualShock 2 input: scePadInit, scePadPortOpen, scePadRead, ...
//   sceMc*   memory card: sceMcInit, sceMcOpen, sceMcRead, sceMcWrite, ...
//
// Each HLE'd function must keep the EE-visible side effects the game depends
// on (return values in $v0, buffers written in guest memory, semaphores
// signalled) and nothing else.
#pragma once

namespace p3fes::hle {

// Intentionally empty for now.

} // namespace p3fes::hle
