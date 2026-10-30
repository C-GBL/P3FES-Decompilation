// Phase 5 slice sweep2: the still-recompiled functions of 0x330000-0x3AFFFF and 0x3D0000-0x44FFFF that no pair test in
// tests/game stands in with a recorder -- effect class 10 kind 9 (with the shipped effect editor), effect class 23,
// class 30 kind 1, the update slots of class 31's kinds 1 / 5 / 7 / 8 / 9 / 11 / 12, and the compendium screen's element
// animator of fclShop.c. Register-ABI bodies (arguments in $a0.., $f12.., the result in $v0) made readable on top of
// p3fes_handgen's output; the named offsets below each equal the literal they replace (a check script compares every
// file with the generator's output statement for statement). Bracketed names are proposals (symbols/deltas/sweep2.sym).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace sw2 {

// --- effect class 10 kind 9 (group fx) ---------------------------------------------------------------------------------
// The class-10 instance (fx2.h): +48 u32 the instance colour, +52 the frame, +60 the kind object {+0 the 40-byte
// records, +4 the strip mesh, +8 the block itself}, +64 the parameters (0x108 bytes for kind 9). The parameter words
// below are the ones the effect editor (docs/ANALYSIS/30_debug_tools.md) edits; the u labels are the developer's own
// ("top u   = %3.2f", "bottom u= %3.2f", "BgMode = %d").
inline constexpr s32 kK10Frame = 52;       // instance: the frame (compared with params +52, the end; 0 = endless)
inline constexpr s32 kK10Obj = 60;         // instance: the kind object
inline constexpr s32 kK10Params = 64;      // instance: the kind's parameters
inline constexpr s32 kBand9TopU = 164;     // params f32 (the editor's up / down; 0.01 steps, at most 0.99)
inline constexpr s32 kBand9BottomU = 168;  // params f32 (the editor's left / right; kept ordered with the top)
inline constexpr s32 kBand9BgMode = 196;   // params s8: the background mode (square / triangle)
inline constexpr s32 kBand9Record = 40;    // bytes per kind-9 record (word 0: -1 free, -2 dead, else the age)

// --- effect class 23 (group fx) ----------------------------------------------------------------------------------------
// The instance (176 bytes, script4_fx.h FxC23Inst): +0 word (-1 new), +4 the frame count, +8 the frame, +12 the 152-byte
// copy of the effect record's body, +164 the quad mesh, +168 the image sequence, +172 the sprite player.
inline constexpr s32 kC23Size = 176;
inline constexpr s32 kC23Mesh = 164;
inline constexpr s32 kC23ImageSeq = 168;
inline constexpr s32 kC23Sprite = 172;

// --- effect class 31 kinds (group fade) --------------------------------------------------------------------------------
// The class-31 instance (script4_fx.h FxC31Inst): +0 position, +16 rotation, +32 f32 scale, +36 colour, +40 the frame,
// +48 the kind's state (a model holder {+0 the model, +4 u16 the helper index} for kinds 1 / 8 / 9, the saved colour for
// kind 5), +56 the parameters. The battle units the kinds walk: four lists at gBtl +336 + 8 * list, linked by +2612.
inline constexpr s32 kGpBtl = -18692;       // 0x7CE3EC gBtl* (battle_core2 / battle3)
inline constexpr s32 kGpInv255 = -32420;    // 0x7CAE4C f32 1/255: colour bytes to floats
inline constexpr s32 kC31Frame = 40;        // instance: the frame
inline constexpr s32 kC31State = 48;        // instance: the kind's state
inline constexpr s32 kC31Params = 56;       // instance: the kind's parameters
inline constexpr s32 kBtlUnitLists = 336;   // gBtl: the four unit list heads (8 bytes apart)
inline constexpr s32 kUnitFlags = 2508;     // btlUnit u16 flags (kind 7 sets bit 3)
inline constexpr s32 kUnitModelLight = 2548;  // btlUnit: the model's light block (kind 1 at frame 0)
inline constexpr s32 kUnitStatus = 2604;    // btlUnit: the status record (datCalcIsDead's argument; 0 for enemies)
inline constexpr s32 kUnitNext = 2612;      // btlUnit: the next unit of its list

// --- the compendium element animator (group fcl) -----------------------------------------------------------------------
// The list (fclShopBook_BuildList's 40-byte list) +36 -> the shop work, whose +68 holds the screen record: +4 the list
// kind (-8 compendium, -9 registration), +28 / +32 the two element sets. The template 0x6AF620 is 28 records of 28
// bytes (word +0 the element id, half +24 cleared by the animator); one of them is passed as the element's descriptor.
inline constexpr s32 kBookListWork = 36;   // list: the shop work
inline constexpr s32 kBookScreen = 68;     // shop work: the compendium screen record
inline constexpr s32 kBookSetA = 28;       // screen record: element set A
inline constexpr s32 kBookSetB = 32;       // screen record: element set B
inline constexpr s32 kBookTemplateWords = 98;  // the template copied as 98 pairs of words (784 bytes)

}  // namespace sw2

// -------------------------------------------------------------------------------------------------------------------
// group fx (game/src/sweep/sweep2_fx.cpp): class 10 kind 9, effect class 23, class 30 kind 1.
// -------------------------------------------------------------------------------------------------------------------
// sub_3402C0 0x3402C0 [k10Band9Init]:
//   (inst) Class-10 kind 9 slot 0 (row 0x69C94C +0): locks the mesh of the kind object (inst +60 -> +4, its
//   atomic's geometry; geometryLock 2), clears its 12-byte vertices (memset, the mesh's vertex count +8),
//   unlocks (sub_4933D0), sets the geometry's polygons-locked bit (RpGeometry lock flags +12 bit 0) when the
//   mesh flags bit 2 is set, and frees every 40-byte record of the parameters' count (+56): word 0 = -1.
void sub_3402C0(EEContext& ctx);
// sub_3403B0 0x3403B0 [k10Band9BuildUv]:
//   (obj, params) The texture coordinates of the class-10 kind 9 mesh (called by create, clone and the debug
//   keys of update): with a count (+56), locks the mesh (geometryLock 4080) and writes 64 bytes per record into
//   the texture-coordinate array (+52): eight coordinate pairs per record from the two u values +168 (bottom) /
//   +164 (top) (the developer's labels) and the constants 0 / 1; with the background mode byte +196 set every
//   record spans the whole texture, clear the odd records take 0.5 .
void sub_3403B0(EEContext& ctx);
// sub_340600 0x340600 [k10Band9Create]:
//   (params, texture) -> kind object. Class-10 kind 9 slot 1: one RwMalloc block (0x960178, hint 0x40000) of 16
//   + 40 * count bytes (records right after the 16-byte head: +0 -> the records, +8 the block itself), a strip
//   mesh (sub_3233A0(count, 6, 8, layout 0x69C730, stride 76)) at +4, the given texture (sub_323B90) or the
//   effect texture 18 (sub_3210A0, sub_494D50 on the mesh's material), then the texture coordinates
//   (sub_3403B0).
void sub_340600(EEContext& ctx);
// sub_3406F0 0x3406F0 [k10Band9Clone]:
//   (inst) -> kind object. Class-10 kind 9 slot 3: a new 16 + 40 * count block (RwMalloc), a copy of the
//   instance's mesh (sub_323640) at +4, the texture coordinates rebuilt (sub_3403B0).
void sub_3406F0(EEContext& ctx);
// sub_340790 0x340790 [k10Band9Destroy]:
//   (obj) Class-10 kind 9 slot 2: destroys the mesh (sub_3237C0 on +4) and frees the block (+8) through the
//   RwFree slot 0x96017C (jalr).
void sub_340790(EEContext& ctx);
// sub_3407E0 0x3407E0 [k10Band9Update]:
//   (inst) Class-10 kind 9 slot 4, while the effect runs (frame < the parameters' end +52, or no end): the four
//   track colours +172 / +184 / +176 / +180 copied to +88 / +92 / +188 / +192 and scaled to floats on VU0
//   (1/255, 0x7CAE4C); the emission budget (+80, or the whole count on a burst +85 at frame 0); every 40-byte
//   record either respawned from the random ranges (effRandF sub_358030, effMiscRand sub_357FD0 for a burst's
//   start frame) or aged along its band (cosf / sinf, the camera matrix sub_198590 / sub_4CB2F0, VU0), the
//   band's vertices and colours written under geometryLock 10 (MMI packs).
void sub_3407E0(EEContext& ctx);
// sub_341BA0 0x341BA0 [k10Band9Draw]:
//   (inst) Class-10 kind 9 slot 5, while the effect runs: the mesh colour from the instance colour x the colour
//   track on VU0 (sub_32A120, 1/255, ppacb; an alpha of 255 stored as 254), placed at the effect's frame
//   (sub_3238D0), the mesh flag bit 0 from the parameters' byte +86, queued with the blend +40 (sub_323860);
//   while the word 0x7CCA3C is 0 the developer text screen (dbgPrintAt sub_104D10, from the packed position
//   0x7CCA40, two rows apart) gets the top / bottom u (+164 / +168), the four track colours +172..+187 and the
//   background mode +196.
void sub_341BA0(EEContext& ctx);
// sub_350230 0x350230 [fx23Create]:
//   (source record or 0) -> instance. Effect class 23 slot 0: one 176-byte RwMalloc block, zeroed, +0 = -1; with
//   a record: the frame count +4 from record +12, the record's 152-byte body copied to +12 (sub_3245B0), a 1 x 2
//   quad mesh (sub_3233A0(1, 2, 4, layout 0x69BDC8, stride 76), its flag bit 2 cleared, the four vertex colours
//   -1) at +164, then by the record's resource type +28: 7 an image sequence (sub_322DC0 -> +168), 4 an effect
//   texture (sub_3210A0 on the mesh's material), 2 a sprite player (sub_322530 -> +172), 1 a texture
//   (sub_323B90).
void sub_350230(EEContext& ctx);
// sub_350450 0x350450 [fx23Clone]:
//   (inst) -> instance. Effect class 23 slot 5: a bare instance (sub_350230(0)), the frame count +4 and the
//   152-byte body copied, a copy of the mesh (sub_323640, the four vertex colours -1) when the source has one,
//   then the resources copied (sub_350500, slot 6).
void sub_350450(EEContext& ctx);
// sub_3505D0 0x3505D0 [fx23Draw]:
//   (inst) Effect class 23 slot 3, for frames 1 .. count - 1: the vertex colour from the instance colour x the
//   colour track on VU0 (sub_32A120, 1/255; alpha 255 stored as 254), the scale track (sub_32A540 / 100) and the
//   second track; the texture rectangle from the sprite player (+172: sub_322D40 / sub_322D10, the frame's cell
//   in 16ths), the image sequence (+168: sub_322FD0) or the texture (sub_323BF0); the four corners rotated (cosf
//   / sinf of the angle) and projected onto the camera's near plane (sub_198590 +104 / +128 / +132, the screen
//   640 x 448, the position +156 / +160), the texture coordinates, then the quad placed at the camera frame
//   (sub_4CB7F0) and drawn with render mode 5 (sub_321130 / sub_321120, sub_323860 with the blend +52).
void sub_3505D0(EEContext& ctx);
// sub_351250 0x351250 [fx23Step]:
//   (inst) Effect class 23 slot 1: frame +8 += 1, then the draw (sub_3505D0, a tail call).
void sub_351250(EEContext& ctx);
// sub_351E70 0x351E70 [k30Strip1Update]:
//   (inst) Class-30 kind 1 slot 3, while the effect runs: every +76 frames (frame % +76 == 0) each of the
//   parameters' +56 rows of the strip (8 bytes: u16 phase, u8 alpha, f32 width) gets new random values (effRandF
//   sub_358030: phase 0..0xFFFF, alpha 255 x (1 - +100 + +100 x r), the width from +132 % and the accumulator
//   blends); the frame +20 += 1.
void sub_351E70(EEContext& ctx);
// sub_3520A0 0x3520A0 [k30Strip1Draw]:
//   (inst) Class-30 kind 1 slot 4, while the effect runs: the strip colour from the instance colour x the colour
//   track on VU0 (sub_32A120), the camera matrix (sub_198590, sub_4C6BE0), the strip's rows written into the
//   mesh under geometryLock (positions on VU0 from the row phase / width, colours by MMI packs), unlocked,
//   placed at the camera frame (sub_4CB2F0 / sub_4CB7F0) and queued with render mode 5 (sub_321130 / sub_321120
//   / sub_323860).
void sub_3520A0(EEContext& ctx);

// -------------------------------------------------------------------------------------------------------------------
// group fade (game/src/sweep/sweep2_fade.cpp): the class-31 kind updates 1 / 5 / 7 / 8 / 9 / 11 and kind 12's
// destroy / update.
// -------------------------------------------------------------------------------------------------------------------
// sub_352F70 0x352F70 [k31Model1Update]:
//   (inst) Class-31 kind 1 slot 4 (row 0x69CD0C): within the duration (params +12; 0 = endless) the fade
//   envelope of script4_fx.h on the parameters' head at +12 (phase 1 for frames up to fade-in +16, phase 2 from
//   duration - fade-out +18 on); the kind's model (inst +48 -> +0) placed from the instance's rotation
//   (sub_3296A0 on +16), scale (+32 x params +28) and position (+0) (mdlMatrixTransform / SetScale / Translate /
//   SetAnimSpeed / Update) and its helper 0 position read (sub_318ED0).
void sub_352F70(EEContext& ctx);
// sub_3556D0 0x3556D0 [k31ColorScale5Update]:
//   (inst) Class-31 kind 5 slot 4 (row 0x69CD7C): the fade envelope on the parameters' head (+0 duration, +4 /
//   +6 fade-in / fade-out, +8 colour) applied to the scene colour scale: the current value (sub_29EA50) is saved
//   into the state (inst +48) at frame 0 (phase 1) or at the first fade-out frame (phase 2), blended towards the
//   parameters' colour (phase 1) or back to the scene's own 0x7CCA38..0x7CCA3B (phase 2) with t from the
//   envelope (x 1/255, the FPU accumulator), alpha 1, written back and passed to K_SceneDraw_SetColorScale
//   (sub_19F8F0); phase 0 sets the parameters' colour once at frame 0.
void sub_3556D0(EEContext& ctx);
// sub_3569E0 0x3569E0 [k31UnitMotion7Update]:
//   (inst) Class-31 kind 7 slot 4 (row 0x69CDB4): every battle unit of the four lists that the selector (params)
//   picks and whose status record (+2604; enemies have none) is not dead (datCalcIsDead) gets flag +2508 bit 3;
//   at frame 0 (+40) it also gets the motion: the model state 4 (sub_287CF0) unless params +14, the motion
//   params +4 with mode +12, flags +6 and the f32 speed +8 (sub_282D40), then sub_287B20(unit, 4).
void sub_3569E0(EEContext& ctx);
// sub_356C70 0x356C70 [k31ModelScale8Update]:
//   (inst) Class-31 kind 8 slot 4 (row 0x69CDD0), within the duration (params +4): on the last frame with the
//   reset flag (params +16) every live player unit's position / rotation / motion is restored (sub_27F7C0 /
//   sub_27F650 / sub_27F680, sub_2831C0, its idle motion +2528 / +2536 through sub_282D40); otherwise, with a
//   model (inst +48 -> +0), the model is placed from the instance (rotation sub_3296A0, scale +32 x params +12,
//   position) and updated, its helper 0 matrix read (sub_318D10) and, when that succeeds, every selected unit
//   gets that matrix scaled by 1 / scale (sub_4C33D0 / sub_4C2F30, sub_27F650, sub_27F6D0); the debug flag gBtl
//   +20 bit 1 draws the helper (sub_358A30 / sub_359380).
void sub_356C70(EEContext& ctx);
// sub_3571C0 0x3571C0 [k31CameraModel9Update]:
//   (inst) Class-31 kind 9 slot 4 (row 0x69CDEC), within the duration (params +44): at frame 0 the battle camera
//   mode 1 (sub_2A38F0; with params +56 clear also the free mode and sub_2A3E80(0, 0, 0, 64)); while the camera
//   is in that mode (sub_2A3A80 == 1) and the kind has a model (inst +48 -> +0): the model placed from the
//   instance (rotation, scale +32 x params +52, position), updated, its two helpers (+4, +4 + 1) read
//   (sub_318D10), drawn by the debug flag gBtl +20 bit 1 unless +12 bit 2, and the camera set from the two
//   points (sub_2A4690, sub_2A2170 on gBtl +32).
void sub_3571C0(EEContext& ctx);
// sub_357550 0x357550 [k31NaviShot11Update]:
//   (inst) Class-31 kind 11 slot 4 (row 0x69CE24), at frame 0 only: the battle camera mode 1 and sub_2A3E80(0,
//   0, 0, 64), then a camera shot by params +0: 2 = shot 39 on the action of the unit 0x957BD4
//   (btlActionFindByUnit sub_29A1D0), 1 = shot 38, 0 = shot 37 (sub_2A38F0); with params +4 every live player
//   unit's position / rotation / motion is restored as kind 8's reset does.
void sub_357550(EEContext& ctx);
// sub_357710 0x357710 [k31Fade12Destroy]:
//   (state) Class-31 kind 12 slot 2 (row 0x69CE40 +8): the screen fade reset (sub_103CB0, a tail call).
void sub_357710(EEContext& ctx);
// sub_357730 0x357730 [k31Fade12Update]:
//   (inst) Class-31 kind 12 slot 4: at frame 0 (+40) the screen fade request (sub_103C30) with the parameters'
//   four halves +0 / +4 / +8 / +12 (sign-extended); later frames do nothing.
void sub_357730(EEContext& ctx);

// -------------------------------------------------------------------------------------------------------------------
// group fcl (game/src/sweep/sweep2_fcl.cpp): the compendium screen's element animator.
// -------------------------------------------------------------------------------------------------------------------
// sub_4072D0 0x4072D0 [fclShopBook_AnimElements]:
//   (list, group, dir) The compendium screen's element animator: the shop work (list +36 -> +68) gives the two
//   element sets (+28 / +32); by the group ($a1: 2 the list rows, 11 / 12 / 13 / 14 / 15 / 16 the panels and
//   frames) and the direction ($a2: 0 in, 1 out) the template 0x6AF620 (98 pairs of words) is copied to a stack
//   buffer, the key words of each element filled in, 28 bytes of it copied as the element's descriptor and the
//   element of that id (sub_3DFFC0(set, id, ..)) started with it (fclElemSetParams sub_3DF100).
void sub_4072D0(EEContext& ctx);

}  // namespace p3fes::game
