// Phase 5 slice boot, part 3: the scene-draw and shadow tasks of 0x199C60-0x19FF10 (k_sceneDraw.c, k_shadow.c) that
// kwlnRootUpdateTask creates every boot (K_SceneDraw_CreateTasks): the field's opaque / translucent passes, the
// character-model pass with its distance sort, the real-time shadow maps ("shadow map camera") and the per-character
// shadows ("renderTex for shadow": a rendered texture or a flat disc), the scene colour scale and the field-light
// frame reset. Bodies in game/src/boot/boot_scene.cpp (p3fes_handgen's, made readable; boot.h explains the
// conventions, the boot sequence and the frame's task order).
//
// Records: the field resources come from sub_3B5D50(list) (12 the field sources, 1 the characters, 3 the NPCs, 2 / 4
// / 5 the light records, 19 the lights), linked by +248; a resource's flag word +40 (bit 1 visible, bit 29 a second
// model at +488 / +492, bit 30 / 31 its own lights), its model at +296, its shadow record at +484 (characters) / +496
// (NPCs), up to three effect markers at +256..+264, the field source draw handle at +352. The field work is *0x7CD540
// (its first word = the field major: the translucent passes run only below 200).
// * renderTex-for-shadow work (140 bytes): see sub_19B2B0 / sub_19BEB0.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace boot_scene {
inline constexpr u32 kFieldWork = 0x7CD540u;      // the field work pointer
inline constexpr u32 kFieldMajorLimit = 200;      // translucent passes only below this field major
inline constexpr u32 kShadowWorkSize = 140;
inline constexpr u32 kShadowTexSize = 128;        // the shadow texture and camera: 128 x 128
inline constexpr u32 kCharDrawMax = 64;           // characters the model pass can sort (K_Assert past it)
}  // namespace boot_scene

void sub_199C60(EEContext& ctx);  // 0x199C60 (camera) [K_Shadow_DestroyCamera]
void sub_199CF0(EEContext& ctx);  // 0x199CF0 (atomic, acc) -> atomic [K_Shadow_AccumulateBounds]
void sub_19AB30(EEContext& ctx);  // 0x19AB30 (atomic, data) -> atomic [K_Shadow_AtomicCallback]
void sub_19B2B0(EEContext& ctx);  // 0x19B2B0 (task) -> 0 / -1 [K_Shadow_UpdateRenderTexTask]
void sub_19BEB0(EEContext& ctx);  // 0x19BEB0 (parent, owner_id, kind) -> task / 0 [K_Shadow_CreateRenderTexTask]
void sub_19C320(EEContext& ctx);  // 0x19C320 (task, radius $f12) [K_Shadow_SetDiscRadius]
void sub_19C4B0(EEContext& ctx);  // 0x19C4B0 (task) -> 0 / -1 [K_Shadow_UpdateMapCameraTask]
void sub_19D270(EEContext& ctx);  // 0x19D270 (task) [K_Shadow_DestroyMapCameraTask]
void sub_19D2A0(EEContext& ctx);  // 0x19D2A0 (parent) -> task / 0 [K_Shadow_CreateMapCameraTask]
void K_SceneDraw_UpdateDrwOpcFldTask(EEContext& ctx);  // 0x19D410 (task) -> 0
void sub_19D4A0(EEContext& ctx);  // 0x19D4A0 (task) -> 0 [K_SceneDraw_UpdateDrwTrnFldTask]
void sub_19DE40(EEContext& ctx);  // 0x19DE40 (task) -> 0 [K_SceneDraw_UpdateDrwTrnFldObjTask]
void sub_19E1B0(EEContext& ctx);  // 0x19E1B0 (task) -> 0 [K_SceneDraw_UpdateDrwTrnFldObjPreCharTask]
void sub_19E1F0(EEContext& ctx);  // 0x19E1F0 (a**, b**) -> int [K_SceneDraw_CompareCameraDistance]
void sub_19E330(EEContext& ctx);  // 0x19E330 (task) -> 0 [K_SceneDraw_UpdateDrwCharModelTask]
void sub_19EE40(EEContext& ctx);  // 0x19EE40 (a**, b**) -> int [K_SceneDraw_CompareCameraDistance2]
void K_SceneDraw_CreateTasks(EEContext& ctx);  // 0x19F730 (parent) -> task
void sub_19F8F0(EEContext& ctx);  // 0x19F8F0 (rgba_scale*) [K_SceneDraw_SetColorScale]
void sub_19FDD0(EEContext& ctx);  // 0x19FDD0 (arg) [K_SceneDraw_FieldCall1]
void sub_19FE20(EEContext& ctx);  // 0x19FE20 (arg) [K_SceneDraw_FieldCall2]
void sub_19FE70(EEContext& ctx);  // 0x19FE70 (arg) [K_SceneDraw_FieldCall3]
void sub_19FEC0(EEContext& ctx);  // 0x19FEC0 (arg) [K_SceneDraw_FieldCall4]
void sub_19FF10(EEContext& ctx);  // 0x19FF10 () [K_SceneDraw_ResetFieldLightFrame]

}  // namespace p3fes::game
