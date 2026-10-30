// Phase 5 slice script4, the 0x350000 band (game/src/script/script4_fx.cpp): what the earlier script and effect passes
// left of 0x350070-0x358458, plus the quaternion-to-matrix helper sub_3296A0 of the effect band. Not script-command code
// (the only COMM row here is 146, sub_350200): the band is the tail of the effect system (docs/ANALYSIS/27 section 6).
// Every body is p3fes_handgen's register-ABI body (arguments in $a0.., $f12.., the result in $v0) with roles, named
// offsets and comments added (docs/PHASE5_AGENT_BRIEF.md "Using p3fes_handgen"). Names are symbols/functions.json's; a
// bracketed name is a proposal (symbols/deltas/script4.sym).
//
// The dispatch, read from the ELF (tables) and the instructions:
//
//   [effect class rows] 0x69BE20 + 52 * class (fx_types.h), 13 slots. Reading the three rows of this band together
//     with class 21's: slot 0 create the instance from the effect record, 1 step (update, frame + 1, draw), 2 update
//     (frame + 1), 3 draw, 4 destroy, 5 clone, 6 copy the resources of another instance (class 23 only), 7 restart
//     (frame = 0), 8 set the position (one quadword at +0), 9 set the rotation (quadword +16), 10 set the scale (f32),
//     12 set a parameter word.
//       class 23 (0x69C2CC) a textured quad with an image sequence or a sprite player (like class 7):
//                 sub_350230 / sub_351250 / sub_3505B0 / sub_3505D0 / sub_3503E0 / sub_350450 / sub_350500 / sub_3505A0 /
//                 - / - / - / - / sub_351280
//       class 30 (0x69C438) kind-dispatched, kinds in 0x69CCC0:
//                 sub_352800 / sub_352B80 / sub_352AD0 / sub_352B30 / sub_352910 / sub_352980 / - / sub_352A80 /
//                 sub_352C10 / - / - / - / sub_352C20
//       class 31 (0x69C46C) kind-dispatched, kinds in 0x69CCF0 (the "fade" kinds, below):
//                 sub_357830 / sub_357CE0 / sub_357C10 / sub_357C80 / sub_357930 / sub_3579B0 / - / sub_357BA0 /
//                 sub_357D90 / sub_357DA0 / sub_357DC0 / - / sub_357DB0
//   [class 30 kinds] 0x69CCC0 + 24 * kind: {init(inst), create(block A) -> state, destroy(state), update(inst),
//     draw(inst), parameter size}. Kind 1 = {sub_351CA0, sub_351D20, sub_351E20, sub_351E70, sub_3520A0, 0x94}: a
//     colour-strip mesh of block A +56 rows.
//   [class 31 kinds] 0x69CCF0 + 28 * kind: {init(inst), create(block A, effect type, block B, effect +36) -> state,
//     destroy(state), clone(source inst) -> state, update(inst), draw(inst), parameter size}. The class slots call the
//     kind slots only while a battle is up (gBtl, gp-18692, non-null; a clone with a clone slot excepted), and the
//     update slot counts the frame only then. Kinds 1..11:
//       1 a model (sub_352E10 / sub_352F20 / sub_352EB0, update sub_352F70)       params 0x30
//       2 the battle scene-light fade (state 32 B: sub_353960 / sub_353990, update sub_3539C0)  params 0x10
//       3 the battle units' colour fade (destroy nullsub_112, update sub_3542A0)    params 0x10
//       4 the scene light-block fade (sub_354B20 / sub_354B50, update sub_354B80) params 0x10
//       5 (sub_355670 / sub_3556A0, update sub_3556D0)                            params 0x10
//       6 a model lit by a light fade (sub_355DD0 / sub_355EE0 / sub_355E70, update sub_355F30)  params 0x28
//       7 (update sub_3569E0)                                                     params 0x20
//       8 a model (sub_356B00 / sub_356C20 / sub_356BA0, update sub_356C70)       params 0x30
//       9 a model started on a random frame (sub_356FD0 / sub_357170 / sub_3570B0, update sub_3571C0)  params 0x58
//      10 the battle camera's field-of-view fade (destroy sub_357450, update sub_357470)  params 0x6C
//      11 (destroy nullsub_113)
//   [fade envelope] the fade kinds 2..6 share one parameter head {u32 duration, u16 fade-in frames, u16 fade-out
//     frames, u32 RGBA colour A, u32 RGBA colour B} and one envelope (t in unsigned frame arithmetic): frames
//     [0, fade-in] blend from the value saved at frame 0 towards the target with t = frame / fade-in (1 when fade-in is
//     0; phase 1); later frames from duration - fade-out on blend from the value saved at that first fade-out frame
//     back to the scene's own with t = (duration - frame) / fade-out (0 when fade-out is 0; phase 2), so the last frame
//     leaves exactly the scene's value; frames in between write nothing; past a non-zero duration nothing runs;
//     duration 0 = phase 0: the target is set once, at frame 0. Colours are scaled by 1/255 (0x7CAE4C).
//   [screen shake request] sub_3500A0 / sub_350110 / sub_3500E0 / sub_350200 drive fx_types' shake (sub_348110 /
//     sub_347F80) from the request at 0x957BC0 and the gp words -18300 (frames run) / -18296 (active).
//   [unit filter] sub_352C70(unit, selector) with the actors 0x957BD0 / 0x957BD4 (sub_352C30) and the list 0x957BD8
//     .. 0x957BE0 (sub_352C50).
//   [VU0 helpers] quaternion product / normalise / to-matrix, Euler angles to quaternion, the axis rotations, the
//     axis-angle matrix and a 4x4 product, on vf10 / vf11 and the matrix registers vf24..vf27 / vf28..vf31.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace s4fx {

// --- RenderWare memory slots (0x960000 + lo) and the hint every effect allocation passes ----------------------------
constexpr s32 kRwMalloc = 376;     // 0x960178: RwMalloc(size, hint)
constexpr s32 kRwFree = 380;       // 0x96017C: RwFree(block)
constexpr s32 kHintFx = 0x40000;   // the memory hint of the effect allocations

// --- globals (lo halves under 0x950000, gp-relative under $gp = 0x7D2CF0) ------------------------------------------
constexpr s32 kLoShakeDuration = 31680;  // 0x957BC0 u32: shake request duration in frames (0 = until stopped)
constexpr s32 kLoShakeKind = 31684;      // 0x957BC4 s16: shake request kind (the block sub_348110 receives)
constexpr s32 kLoShakeWord8 = 31688;     // 0x957BC8 u32 (cleared by the request)
constexpr s32 kLoShakeWordC = 31692;     // 0x957BCC u32 (cleared by the request)
constexpr s32 kGpShakeFrame = -18300;    // 0x7CE574: frames the requested shake has run
constexpr s32 kGpShakeActive = -18296;   // 0x7CE578: a shake request is running
constexpr s32 kLoActorA = 31696;         // 0x957BD0 btlUnit*: unit filter actor A (selector byte 0)
constexpr s32 kLoActorB = 31700;         // 0x957BD4 btlUnit*: unit filter actor B (selector byte 1)
constexpr s32 kLoListed = 31704;         // 0x957BD8 btlUnit*[3]: the listed units (selector byte 2 bit i)
constexpr s32 kLoRandState = 31728;      // 0x957BF0: effMiscRand's default state (4 words)
constexpr s32 kGpBtl = -18692;           // 0x7CE3EC gBtl* (battle_core2 / battle3)
constexpr s32 kGpStripRgba = -18348;     // 0x7CE544 u8[4]: class 30 kind 1's strip colour (alpha 255 stored as 254)
constexpr s32 kGpStripAlpha = -18345;    // 0x7CE547
constexpr s32 kGpUnitFadeRgba = -25272;  // 0x7CCA38 u8[4]: the colour kind 3 fades the units back to
constexpr s32 kGpInv255 = -32420;        // 0x7CAE4C f32 1/255
constexpr s32 kGpDegToRad = -32444;      // 0x7CAE34 f32 pi/180
constexpr s32 kGpFovDefault = -32440;    // 0x7CAE38 f32 0.6981317 (40 degrees)

// --- gBtl / btlUnit fields these bodies touch -------------------------------------------------------------------
constexpr s32 kBtlFov = 216;          // gBtl f32: the battle camera's field of view (radians)
constexpr s32 kBtlSideLists = 336;    // gBtl: four unit lists, 8 bytes apart (head word first)
constexpr s32 kUnitColourSave = 56;   // btlUnit u8[4]: the colour saved at a fade's phase start
constexpr s32 kUnitColour = 60;       // btlUnit u8[4]: the unit's colour (RGBA)
constexpr s32 kUnitFlags = 152;       // btlUnit u32: bit 2 = colour overridden this frame
constexpr s32 kUnitSide = 162;        // btlUnit u8: side
constexpr s32 kUnitNext = 2612;       // btlUnit: next unit in its side list

// --- class 23 instance (176 bytes, sub_350230) -------------------------------------------------------------------
constexpr s32 kC23Word0 = 0;        // u32 (-1 on creation; slot 12 sets it)
constexpr s32 kC23Id = 4;           // u32: effect record +12
constexpr s32 kC23Frame = 8;        // u32 frame counter
constexpr s32 kC23Params = 12;      // 152 bytes copied from the record's block A
constexpr s32 kC23Mesh = 164;       // FxMesh*: one quad, vertex layout 0x69BDC8
constexpr s32 kC23ImageSeq = 168;   // image sequence (block B type 7: sub_322DC0 / sub_322F20 / sub_322FB0)
constexpr s32 kC23Player = 172;     // sprite player (block B type 2: sub_322530 / sub_322660 / sub_3225D0)

// --- class 30 instance (48-byte head + the kind's parameters) and its kind rows ------------------------------------
constexpr s32 kC30Pos = 0;          // quadword (vf0 on creation)
constexpr s32 kC30Word = 16;        // u32 (-1 on creation; slot 12 sets it)
constexpr s32 kC30Frame = 20;       // s32 frame counter (draw only after frame 0)
constexpr s32 kC30Kind = 24;        // u32 kind (effect record +12)
constexpr s32 kC30State = 28;       // the kind's state (its create's result)
constexpr s32 kC30Params = 32;      // -> the parameter copy at +48
constexpr s32 kC30Head = 48;
constexpr s32 kK30Init = -13120;    // 0x6A0000 - 13120 = 0x69CCC0: kind row +0 init(inst)
constexpr s32 kK30Create = -13116;  // 0x69CCC4: +4 create(block A) -> state
constexpr s32 kK30Destroy = -13112; // 0x69CCC8: +8 destroy(state)
constexpr s32 kK30Update = -13108;  // 0x69CCCC: +12 update(inst)
constexpr s32 kK30Draw = -13104;    // 0x69CCD0: +16 draw(inst)
constexpr s32 kK30Size = -13100;    // 0x69CCD4: +20 parameter size
constexpr s32 kK30RowBytes = 24;
constexpr s32 kStripRows = 56;      // class 30 kind 1 block A: row count
constexpr s32 kStripColourA = 84;   // class 30 kind 1 block A: RGBA of the rows' first and third vertices
constexpr s32 kStripColourB = 88;   // class 30 kind 1 block A: RGBA of the rows' second half
constexpr s32 kStripVerts = 0, kStripMesh = 4, kStripSelf = 8, kStripHead = 16;  // class 30 kind 1 state

// --- class 31 instance (64-byte head + the kind's parameters) and its kind rows ------------------------------------
constexpr s32 kC31Pos = 0;          // quadword position (vf0 on creation)
constexpr s32 kC31Rot = 16;         // quadword rotation (vf0 on creation)
constexpr s32 kC31Scale = 32;       // f32 scale (1.0)
constexpr s32 kC31Colour = 36;      // u32 RGBA (0x80808080)
constexpr s32 kC31Frame = 40;       // u32 frame counter
constexpr s32 kC31Kind = 44;        // u32 kind (effect record +12)
constexpr s32 kC31State = 48;       // the kind's state (its create's or clone's result)
constexpr s32 kC31Params = 56;      // -> the parameter copy at +64
constexpr s32 kC31Head = 64;
constexpr s32 kK31Init = -13072;    // 0x6A0000 - 13072 = 0x69CCF0: kind row +0 init(inst)
constexpr s32 kK31Create = -13068;  // 0x69CCF4: +4 create(block A, type, block B, effect +36) -> state
constexpr s32 kK31Destroy = -13064; // 0x69CCF8: +8 destroy(state)
constexpr s32 kK31Clone = -13060;   // 0x69CCFC: +12 clone(source inst) -> state
constexpr s32 kK31Update = -13056;  // 0x69CD00: +16 update(inst)
constexpr s32 kK31Draw = -13052;    // 0x69CD04: +20 draw(inst)
constexpr s32 kK31Size = -13048;    // 0x69CD08: +24 parameter size
constexpr s32 kRecId = 12;          // effect record u16: the class's kind / id
constexpr s32 kRecType = 28;        // effect record u16: the effect type (create builds the model only for type 3)
constexpr s32 kRecWord36 = 36;      // effect record word handed to a class 31 kind's create

// --- the fade kinds' parameters (class 31 instance +56 points at them) and states ----------------------------------
constexpr s32 kFadeDuration = 0;    // u32 frames (0: phase 1 forever)
constexpr s32 kFadeIn = 4;          // u16 fade-in frames
constexpr s32 kFadeOut = 6;         // u16 fade-out frames
constexpr s32 kFadeColA = 8;        // u32 RGBA target A
constexpr s32 kFadeColB = 12;       // u32 RGBA target B (kinds 2 / 4 / 6); kind 3: the unit selector bytes
constexpr s32 kFadeModelScale = 20; // kind 6: f32 scale factor (x the instance's scale)
constexpr s32 kFovFrom = 4, kFovTo = 8;  // kind 10: f32 degrees, lerped over the duration
constexpr s32 kModel = 0;           // model kinds' state: the EPL model (sub_34BDF0 / sub_34BF10)
constexpr s32 kModelStartFrame = 4; // kind 9's state u16: a random even start frame below the model's frame count
constexpr s32 kSelA = 0, kSelB = 1, kSelListMask = 2, kSelAll = 3;  // unit selector bytes (sub_352C70)

}  // namespace s4fx

void sub_3296A0(EEContext& ctx);   // 0x3296A0 [fxQuatToMatrix34] out(a0) = rotation rows of the normalised quaternion *a1, translation 0
void sub_350070(EEContext& ctx);   // 0x350070 [fxGetWord132] return a0 +132
void sub_350080(EEContext& ctx);   // 0x350080 [fxClearBank] sub_321F10() (field root destroy, field event update)
void sub_3500A0(EEContext& ctx);   // 0x3500A0 [fxShakeRequest] (duration, kind): start a requested screen shake
void sub_3500E0(EEContext& ctx);   // 0x3500E0 [fxShakeCancel] stop the shake, clear the request
void sub_350110(EEContext& ctx);   // 0x350110 [fxShakeRequestUpdate] per frame: run / end the requested shake
void sub_350200(EEContext& ctx);   // 0x350200 [scrCommand_SHAKE_STOP] COMM 146 (no arguments): stop the shake, return 1
void sub_3503E0(EEContext& ctx);   // 0x3503E0 [fxC23Destroy] class 23 slot 4
void sub_350500(EEContext& ctx);   // 0x350500 [fxC23CopyFrom] class 23 slot 6: (inst, source)
void sub_3505A0(EEContext& ctx);   // 0x3505A0 [fxC23Restart] class 23 slot 7: frame = 0
void sub_3505B0(EEContext& ctx);   // 0x3505B0 [fxC23Update] class 23 slot 2: ++frame
void sub_351280(EEContext& ctx);   // 0x351280 [fxC23SetWord] class 23 slot 12: +0 = a1
void sub_351BB0(EEContext& ctx);   // 0x351BB0 [fxCrossfadeRequest] (kind): arm the "effect_crossfade" task, 1 if armed
void sub_351CA0(EEContext& ctx);   // 0x351CA0 [fxC30Kind1Init] the strip mesh colour from gp-18348
void sub_351D20(EEContext& ctx);   // 0x351D20 [fxC30Kind1Create] the colour-strip mesh of block A
void sub_351E20(EEContext& ctx);   // 0x351E20 [fxC30Kind1Destroy]
void sub_352800(EEContext& ctx);   // 0x352800 [fxC30Create] class 30 slot 0
void sub_352910(EEContext& ctx);   // 0x352910 [fxC30Destroy] class 30 slot 4
void sub_352980(EEContext& ctx);   // 0x352980 [fxC30Clone] class 30 slot 5
void sub_352A80(EEContext& ctx);   // 0x352A80 [fxC30Restart] class 30 slot 7
void sub_352AD0(EEContext& ctx);   // 0x352AD0 [fxC30Update] class 30 slot 2
void sub_352B30(EEContext& ctx);   // 0x352B30 [fxC30Draw] class 30 slot 3
void sub_352B80(EEContext& ctx);   // 0x352B80 [fxC30Step] class 30 slot 1
void sub_352C10(EEContext& ctx);   // 0x352C10 [fxC30SetPos] class 30 slot 8: quadword copy
void sub_352C20(EEContext& ctx);   // 0x352C20 [fxC30SetWord] class 30 slot 12: +16 = a1
void sub_352C30(EEContext& ctx);   // 0x352C30 [fxSetFadeActors] (actor A, actor B)
void sub_352C50(EEContext& ctx);   // 0x352C50 [fxSetFadeList] (unit 0, unit 1, unit 2)
void sub_352C70(EEContext& ctx);   // 0x352C70 [fxUnitSelected] (unit, selector) -> 1 when the selector picks the unit
void sub_352E10(EEContext& ctx);   // 0x352E10 [fxC31Kind1Create] the model kinds' create (model only for type 3)
void sub_352EB0(EEContext& ctx);   // 0x352EB0 [fxC31Kind1Clone]
void sub_352F20(EEContext& ctx);   // 0x352F20 [fxC31Kind1Destroy]
void sub_353960(EEContext& ctx);   // 0x353960 [fxC31Kind2Create] 32-byte saved-colour state
void sub_353990(EEContext& ctx);   // 0x353990 [fxC31Kind2Destroy]
void sub_3539C0(EEContext& ctx);   // 0x3539C0 [fxC31Kind2Update] the battle scene-light fade
void nullsub_112(EEContext& ctx);  // 0x354290 class 31 kind 3 destroy (empty)
void sub_3542A0(EEContext& ctx);   // 0x3542A0 [fxC31Kind3Update] the selected battle units' colour fade
void sub_354B20(EEContext& ctx);   // 0x354B20 [fxC31Kind4Create]
void sub_354B50(EEContext& ctx);   // 0x354B50 [fxC31Kind4Destroy]
void sub_354B80(EEContext& ctx);   // 0x354B80 [fxC31Kind4Update] the field scene-light fade
void sub_355670(EEContext& ctx);   // 0x355670 [fxC31Kind5Create]
void sub_3556A0(EEContext& ctx);   // 0x3556A0 [fxC31Kind5Destroy]
void sub_355DD0(EEContext& ctx);   // 0x355DD0 [fxC31Kind6Create]
void sub_355E70(EEContext& ctx);   // 0x355E70 [fxC31Kind6Clone]
void sub_355EE0(EEContext& ctx);   // 0x355EE0 [fxC31Kind6Destroy]
void sub_355F30(EEContext& ctx);   // 0x355F30 [fxC31Kind6Update] a model posed by the instance, lit by a light fade
void sub_356B00(EEContext& ctx);   // 0x356B00 [fxC31Kind8Create]
void sub_356BA0(EEContext& ctx);   // 0x356BA0 [fxC31Kind8Clone]
void sub_356C20(EEContext& ctx);   // 0x356C20 [fxC31Kind8Destroy]
void sub_356FD0(EEContext& ctx);   // 0x356FD0 [fxC31Kind9Create] model + random start frame
void sub_3570B0(EEContext& ctx);   // 0x3570B0 [fxC31Kind9Clone]
void sub_357170(EEContext& ctx);   // 0x357170 [fxC31Kind9Destroy]
void sub_357450(EEContext& ctx);   // 0x357450 [fxC31Kind10Destroy] the battle camera FOV back to 40 degrees
void sub_357470(EEContext& ctx);   // 0x357470 [fxC31Kind10Update] the battle camera FOV fade
void nullsub_113(EEContext& ctx);  // 0x357540 class 31 kind 11 destroy (empty)
void sub_357770(EEContext& ctx);   // 0x357770 [fxC31Alloc] (kind, parameters) -> a fresh class 31 instance
void sub_357830(EEContext& ctx);   // 0x357830 [fxC31Create] class 31 slot 0
void sub_357930(EEContext& ctx);   // 0x357930 [fxC31Destroy] class 31 slot 4
void sub_3579B0(EEContext& ctx);   // 0x3579B0 [fxC31Clone] class 31 slot 5
void sub_357BA0(EEContext& ctx);   // 0x357BA0 [fxC31Restart] class 31 slot 7
void sub_357C10(EEContext& ctx);   // 0x357C10 [fxC31Update] class 31 slot 2
void sub_357C80(EEContext& ctx);   // 0x357C80 [fxC31Draw] class 31 slot 3
void sub_357CE0(EEContext& ctx);   // 0x357CE0 [fxC31Step] class 31 slot 1
void sub_357D90(EEContext& ctx);   // 0x357D90 [fxC31SetPos] class 31 slot 8
void sub_357DA0(EEContext& ctx);   // 0x357DA0 [fxC31SetRot] class 31 slot 9
void sub_357DB0(EEContext& ctx);   // 0x357DB0 [fxC31SetColour] class 31 slot 12
void sub_357DC0(EEContext& ctx);   // 0x357DC0 [fxC31SetScale] class 31 slot 10 ($f12)
void sub_357DD0(EEContext& ctx);   // 0x357DD0 [vu0QuatMul] vf10 = vf10 * vf11
void sub_357E00(EEContext& ctx);   // 0x357E00 [vu0QuatNormalize] vf10 /= |vf10|
void sub_357E30(EEContext& ctx);   // 0x357E30 [vu0QuatToMatrix] vf28..vf31 = the rotation of the unit quaternion vf10
void sub_357EA0(EEContext& ctx);   // 0x357EA0 [vu0EulerToQuat] vf10 = the quaternion of the angles $f12 / $f13 / $f14
void sub_357FD0(EEContext& ctx);   // 0x357FD0 [effMiscRand] (state or 0) -> next 32-bit value of the 4-word generator
void sub_358160(EEContext& ctx);   // 0x358160 [vu0RotMatrixX] vf28..vf31 = rotation by $f12 about x
void sub_3581F0(EEContext& ctx);   // 0x3581F0 [vu0AxisAngleMatrix] out(a1) = rotation by $f12 about the axis *a0
void sub_358340(EEContext& ctx);   // 0x358340 [vu0AxisAngleMatrixLoad] the same into vf28..vf31
void sub_358380(EEContext& ctx);   // 0x358380 [vu0RotMatrixY] vf24..vf27 = rotation by $f12 about y
void sub_358410(EEContext& ctx);   // 0x358410 [vu0MatMul] vf28..vf31 = vf28..vf31 x vf24..vf27

}  // namespace p3fes::game
