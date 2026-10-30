// Phase 5 slice field7, part 3 (game/src/field/field7_draw.cpp): the rest of the 0x1A0000 band's leaves -- the field
// object frame helpers (position, translate, rotate in place, snap to the ground), the "circle draw" fan of the Kyoto
// NPC think task, the matrix angle helpers, a model alpha fade, the clump draw-node lists and the translucent queue of
// k_clump.c (append, depth comparator, culled atomic draw), small task destroys and accessors. Register-ABI bodies
// (arguments in $a0.., result in $v0); names are functions.json's, proposed names in brackets (ADR-0009).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace f7::draw {
inline constexpr int kTaskWork = 60;        // kwln task +60: the work block
inline constexpr int kFramePos = 48;        // RwFrame / RwMatrix +48..+56: the position
// the circle record (work +8 of "circle draw", 28 bytes)
inline constexpr int kCircleRecord = 8;
inline constexpr int kCircleAngle = 0;      // degrees, 0..360
inline constexpr int kCircleRadius = 4;
inline constexpr int kCircleCentre = 8;     // vec3
inline constexpr int kCircleAtomic = 20;    // +24 its geometry (34 vertices: centre, 32 rim points, the closing one)
inline constexpr int kCircleVertices = 34;
// the clump draw-node lists (sub_1A71A0's first argument)
inline constexpr int kListsNodes = 0;       // every node added
inline constexpr int kListsFlagged = 4;     // nodes added with flagged == 1
inline constexpr int kDrawNodeSize = 44;    // value +0, flagged +4, arg +8, four 1.0f +12, list +28, next +40
inline constexpr int kDrawNodeNext = 40;
// the translucent queue (sub_1A8920)
inline constexpr int kQueueCount = 0;
inline constexpr int kQueueNodes = 4;       // 44-byte nodes (11 words), at most 128
inline constexpr int kQueueMax = 128;
// the model alpha fade work (sub_1A5F30)
inline constexpr int kFadeModel = 4;
inline constexpr int kFadeTarget = 8;       // float alpha
inline constexpr int kFadeAlpha = 12;       // float alpha now
inline constexpr int kFadeFrames = 16;      // frames left
}  // namespace f7::draw

void sub_1A13B0(EEContext& ctx);  // [K_TexFilterCollect](texture, list) -> texture
void sub_1A1540(EEContext& ctx);  // [K_ReturnZero]() -> 0
void sub_1A4DF0(EEContext& ctx);  // [K_FldObj_GetPos](out, task)
void sub_1A4E50(EEContext& ctx);  // [K_Task_GetWork](task) -> task +60
void sub_1A4ED0(EEContext& ctx);  // [K_FldObj_TranslateScaled](task, vec, $f12 scale)
void sub_1A4F40(EEContext& ctx);  // [K_FldObj_RotateInPlace](task, axis, $f12 degrees)
void sub_1A5000(EEContext& ctx);  // [K_FldObj_SnapToGround](task) -> 1 on a hit
void sub_1A56B0(EEContext& ctx);  // [K_CircleDraw_SetWord0](task, value)
void sub_1A56C0(EEContext& ctx);  // [K_CircleDraw_SetWord4](task, value)
void sub_1A56D0(EEContext& ctx);  // [K_CircleDraw_SetCentre](task, pos)
void sub_1A5700(EEContext& ctx);  // [K_CircleDraw_SetColour](task, rgba)
void sub_1A57A0(EEContext& ctx);  // [K_CircleDraw_SetArc](task, $f12 angle, $f13 radius)
void sub_1A5AA0(EEContext& ctx);  // [K_Mtx_GetYawDeg](matrix) -> $f0
void sub_1A5B30(EEContext& ctx);  // [K_Mtx_GetPitchDeg](matrix) -> $f0
void sub_1A5BC0(EEContext& ctx);  // [K_Mtx_GetRollDeg](matrix) -> $f0
void sub_1A5E70(EEContext& ctx);  // destroy: frees the work
void sub_1A5F30(EEContext& ctx);  // [K_MdlFade_Update](task) -> 0, or -1 when done
void sub_1A60A0(EEContext& ctx);  // destroy: frees the work
void sub_1A6260(EEContext& ctx);  // [K_Task_KillTarget](task) -> -1
void sub_1A6290(EEContext& ctx);  // destroy: frees the work
void sub_1A7030(EEContext& ctx);  // [K_CpuDraw_Kill](task) -> -1
void sub_1A70A0(EEContext& ctx);  // [K_Clump_AtomicCallback](atomic, data) -> atomic
void sub_1A71A0(EEContext& ctx);  // [K_Clump_AddDrawNode](lists, kind, value, flagged, arg) -> node
void sub_1A74B0(EEContext& ctx);  // [K_MatFindOpaque](material, out) -> material
void sub_1A7660(EEContext& ctx);  // [K_Clump_HasDrawNodes](lists) -> 0 / 1
void sub_1A76E0(EEContext& ctx);  // [K_Clump_HasList8](lists) -> 0 / 1
void sub_1A8820(EEContext& ctx);  // [K_Clump_DrawAtomicCulled](atomic) -> atomic
void sub_1A8910(EEContext& ctx);  // [K_ShadowCam_Clear](out)
void sub_1A8920(EEContext& ctx);  // [K_Clump_QueueTranslucent](queue, node)
void sub_1A89C0(EEContext& ctx);  // [K_Clump_CompareDepth](a, b) -> int

}  // namespace p3fes::game
