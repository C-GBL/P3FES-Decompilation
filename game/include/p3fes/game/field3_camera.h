// Slice field3, part camera: the field camera controller (k_fldCamera.c) and its neighbours in the band
// 0x1D5220-0x1D75E8 -- the follow / dead-zone / rail camera task, its create / destroy / mode switch, the rotation
// tasks, the camera save / restore around battles, the per-field camera set-up (.CMR file, field pack, scene camera
// resource), the opmap table loader and the shadow encounter picker. game/src/field/field3_camera.cpp (p3fes_handgen
// bodies made readable; the file comment describes the camera work), pair tests tests/game/test_field3_camera.cpp.
//
// Every function uses the register ABI: arguments in $a0.. ($t0.. for the 5th..), $f12 for a float, the result in $v0.
// Names: symbols/functions.json's; a proposed name (ours, from the instructions and the callers) is in brackets.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

// The replaced functions of field3_camera.cpp: X(name, address as 8 hex digits).
#define P3FES_FIELD3_CAMERA_BODIES(X)                  \
    X(K_FldCamera_UpdateFieldCameraControlerTask, 001d5220) \
    X(sub_1D59E0, 001d59e0)                            \
    X(K_FldCamera_CreateFieldCameraControlerTask, 001d5a90) \
    X(sub_1D5C10, 001d5c10)                            \
    X(sub_1D5E30, 001d5e30)                            \
    X(sub_1D5F90, 001d5f90)                            \
    X(sub_1D6240, 001d6240)                            \
    X(sub_1D6270, 001d6270)                            \
    X(sub_1D6630, 001d6630)                            \
    X(sub_1D68E0, 001d68e0)                            \
    X(sub_1D69E0, 001d69e0)                            \
    X(sub_1D6B10, 001d6b10)                            \
    X(sub_1D6BC0, 001d6bc0)                            \
    X(sub_1D70A0, 001d70a0)                            \
    X(sub_1D7260, 001d7260)                            \
    X(sub_1D7300, 001d7300)

// --- the camera controller task ("field camera controler", sField+4) --------------------------------------------------
void K_FldCamera_UpdateFieldCameraControlerTask(EEContext& ctx);  // 0x1D5220 (task) -> 0: follow / dead zone / rail
void sub_1D59E0(EEContext& ctx);  // 0x1D59E0 [K_FldCamera_DestroyFieldCameraControlerTask] (task): unlink, free
void K_FldCamera_CreateFieldCameraControlerTask(EEContext& ctx);  // 0x1D5A90 (parent) -> task or 0: work, pivot frame
void sub_1D5C10(EEContext& ctx);  // 0x1D5C10 [K_FldCamera_SetMode] (task, mode): rail samples / debug points
void sub_1D5E30(EEContext& ctx);  // 0x1D5E30 [K_FldCamera_RotateMainCamera] (task, $f12 deg): mode 0, about world y

// --- the rotation tasks ("field camera rotation", 24-byte work) ------------------------------------------------------
void sub_1D5F90(EEContext& ctx);  // 0x1D5F90 [K_FldCamera_UpdateRotationTask] (task) -> 0 / -1: sine-eased turn
void sub_1D6240(EEContext& ctx);  // 0x1D6240 [K_FldCamera_DestroyRotationTask] (task): RwFree(work)
void sub_1D6270(EEContext& ctx);  // 0x1D6270 [K_FldCamera_CreateTurnToHero] (parent, frames, deg or -1) -> task / 0
void sub_1D6630(EEContext& ctx);  // 0x1D6630 [K_FldCamera_CreateTurnToAngle] (parent, frames, deg) -> task / 0

// --- save / restore, the per-field set-up ---------------------------------------------------------------------------
void sub_1D68E0(EEContext& ctx);  // 0x1D68E0 [K_FldCamera_SaveState] (out[96], task): matrix, fov, mode, zone
void sub_1D69E0(EEContext& ctx);  // 0x1D69E0 [K_FldCamera_RestoreState] (task, saved): apply + re-aim
void sub_1D6B10(EEContext& ctx);  // 0x1D6B10 [K_FldCamera_RequestCmrFile] () -> request / 1 (pack) / 0
void sub_1D6BC0(EEContext& ctx);  // 0x1D6BC0 [K_FldCamera_ApplyCmrFile] (req, outs.. or 0) -> 1 done / 0 loading
void sub_1D70A0(EEContext& ctx);  // 0x1D70A0 [K_FldCamera_ApplySceneCamera] (): the type-20 scene resource

// --- neighbours ---------------------------------------------------------------------------------------------------
void sub_1D7260(EEContext& ctx);  // 0x1D7260 [K_Field_LoadOpmapTable] (): field/table/opmap.bin -> gp-19008
void sub_1D7300(EEContext& ctx);  // 0x1D7300 [K_Encount_PickShadowEncounter] (major, minor, floor) -> tier<<16|id / -1

}  // namespace p3fes::game
