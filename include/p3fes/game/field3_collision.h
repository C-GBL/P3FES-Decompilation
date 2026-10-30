// The field layer, third pass, part "collision" (Phase 5 slice `field3`; docs/ANALYSIS/26_field.md section 4): the
// k_fldFrame.c band 0x1AA8F0-0x1AFD40 -- the collision controller task, the sphere-contact gatherers and their RW
// triangle callbacks, the ground ray, the transparent-wall pickers, the move / turn / warp helpers on a controller and
// the "collis mover" / "collis sphere" / "death se" tasks. game/src/field/field3_collision.cpp (p3fes_handgen bodies
// made readable; the records are described there), pair tests tests/game/test_field3_collision.cpp.
//
// Names: symbols/functions.json calls most functions here `sub_<addr>` and the names stay; a proposed name (ours, from
// the instructions and the callers) is given in brackets. Every function uses the register ABI (arguments in
// $a0.. / $f12, the result in $v0) and leaves every register, the frame, the spills and the cycle count exactly as the
// original does.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

// The replaced functions of field3_collision.cpp: X(name, address as 8 hex digits).
#define P3FES_FIELD3_COLLISION_BODIES(X) \
    X(sub_1AA8F0, 001aa8f0) \
    X(sub_1AA9F0, 001aa9f0) \
    X(sub_1AAA20, 001aaa20) \
    X(sub_1AAAC0, 001aaac0) \
    X(sub_1AAF30, 001aaf30) \
    X(sub_1AB640, 001ab640) \
    X(sub_1ABCD0, 001abcd0) \
    X(sub_1AC950, 001ac950) \
    X(sub_1ACA40, 001aca40) \
    X(sub_1ACB20, 001acb20) \
    X(sub_1ACB70, 001acb70) \
    X(sub_1ACC30, 001acc30) \
    X(sub_1ACE90, 001ace90) \
    X(sub_1ACFC0, 001acfc0) \
    X(sub_1AD050, 001ad050) \
    X(sub_1AD120, 001ad120) \
    X(sub_1AD220, 001ad220) \
    X(K_FldFrame_UpdateCtlTask, 001ad2f0) \
    X(sub_1AD630, 001ad630) \
    X(K_FldFrame_CreateCtlTask, 001ad660) \
    X(sub_1ADC20, 001adc20) \
    X(sub_1ADEC0, 001adec0) \
    X(sub_1AE0D0, 001ae0d0) \
    X(sub_1AE3C0, 001ae3c0) \
    X(sub_1AE3F0, 001ae3f0) \
    X(sub_1AE480, 001ae480) \
    X(sub_1AF8E0, 001af8e0) \
    X(sub_1AF930, 001af930) \
    X(sub_1AFA20, 001afa20) \
    X(sub_1AFD40, 001afd40)

// --- the "death se" task (the Reaper's looping sound) --------------------------------------------------------------
void sub_1AA8F0(EEContext& ctx);  // [K_DeathSe_Update] sound 32 / 33 / 34 every 181 / 151 frames by mode and distance
void sub_1AA9F0(EEContext& ctx);  // [K_DeathSe_Destroy] RwFree(work)
void sub_1AAA20(EEContext& ctx);  // [K_DeathSe_CreateTask](parent, unit) -> task: 12-byte work, "death se"
void sub_1AAAC0(EEContext& ctx);  // [K_DeathSe_SetMode](task, mode): work +4

// --- sphere vs world: contact gathering and the push-out ------------------------------------------------------------
void sub_1AAF30(EEContext& ctx);  // [K_FldFrame_WorldTriangleCB] world triangle -> nearest contact per plane
void sub_1AB640(EEContext& ctx);  // [K_FldFrame_ClumpTriangleCB] clump triangle (LTM-transformed) -> contact per plane
void sub_1ABCD0(EEContext& ctx);  // [K_FldFrame_AtomicCB] per atomic: RpAtomicForAllIntersections with sub_1AB640

// --- the ground ray -------------------------------------------------------------------------------------------------
void sub_1AC950(EEContext& ctx);  // [K_FldFrame_RayWorldTriangleCB] the line's crossing of a world triangle's plane
void sub_1ACA40(EEContext& ctx);  // [K_FldFrame_RayAtomicTriangleCB] keeps the nearest crossing (best t)
void sub_1ACB20(EEContext& ctx);  // [K_FldFrame_RayAtomicCB] per atomic: sub_464120 with sub_1ACA40
void sub_1ACB70(EEContext& ctx);  // [K_FldFrame_RaycastClump](clump, line, out) -> 1 on a hit
void sub_1ACC30(EEContext& ctx);  // [K_FldFrame_Raycast](line, out) -> 1 on a hit: world, cell block or field clump

// --- the transparent walls ("per3TrnsWall" materials) ---------------------------------------------------------------
void sub_1ACE90(EEContext& ctx);  // [K_FldTWall_TriangleCB] adds the geometry's materials to the result list
void sub_1ACFC0(EEContext& ctx);  // [K_FldTWall_AtomicCB] atomics in the camera frustum only
void sub_1AD050(EEContext& ctx);  // [K_FldTWall_PickMaterials](clump, vec4, line, list)
void sub_1AD120(EEContext& ctx);  // [K_FldTWall_AtomicTriangleCB] adds the atomic to the result list
void sub_1AD220(EEContext& ctx);  // [K_FldTWall_PickAtomic](&atomic, line, list)

// --- the collision controller ---------------------------------------------------------------------------------------
void K_FldFrame_UpdateCtlTask(EEContext& ctx);  // the pending move in three collision-checked thirds, ground snap, grid
void sub_1AD630(EEContext& ctx);  // [K_FldFrame_DestroyCtlTask] RwFree(work)
void K_FldFrame_CreateCtlTask(EEContext& ctx);  // (parent, id; $f12 radius) -> task: 52-byte work, unit lookup
void sub_1ADC20(EEContext& ctx);  // [K_FldFrame_CtlWarp](task, position): place the model, grid cell
void sub_1ADEC0(EEContext& ctx);  // [K_FldFrame_CtlMoveForward](task; $f12 speed): when idle, along the model's +32 axis
void sub_1AE0D0(EEContext& ctx);  // [K_FldFrame_CtlSnapToGround](task): 3.0 above the ray's hit
void sub_1AE3C0(EEContext& ctx);  // [K_FldFrame_DestroyCollisSphereTask] RwFree(work)
void sub_1AE3F0(EEContext& ctx);  // [K_FldFrame_CreateCollisSphereTask](parent): "collis sphere", priority 4174

// --- the "collis mover" ---------------------------------------------------------------------------------------------
void sub_1AE480(EEContext& ctx);  // [K_FldMover_PopWaypoint](task) -> 1 when the front entry was removed
void sub_1AF8E0(EEContext& ctx);  // [K_FldMover_Destroy] the RW object +1228, RwFree(work)
void sub_1AF930(EEContext& ctx);  // [K_FldMover_CreateTask](parent, resource) -> task: 1,440-byte work
void sub_1AFA20(EEContext& ctx);  // [K_FldMover_PushWaypoint](task, pos; $f12 speed) -> 1 when queued (on the ground)
void sub_1AFD40(EEContext& ctx);  // [K_FldMover_PushNudge](task, pos; $f12 speed) -> 1 when queued (kind 3)

}  // namespace p3fes::game
