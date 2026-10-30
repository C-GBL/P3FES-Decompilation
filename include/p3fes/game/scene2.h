// Slice scene2: the still-recompiled functions of 0x3B0000-0x3CFFFF after the scene slice (scene.h) -- the
// SceneManager task (the per-resource update that runs every move / rotation / scale / fade / tween request of
// mt_sceneFunc.c, the scene camera and its shake, the sorted effect draw), the nmList sort, the message-window helpers
// of fclMisc.c's "MsgAssist" task, the persona-status screen of fclMisc.c ("psStatus": loader, layouts, fades), the
// persona-model preview ("psModel_dummy") and fclBankManager.c's bust-up panels. (frFontEx's draw string sub_3B2CB0 in
// the band stays recompiled: test_calendar / test_ui6 stand it in and test_field_hi checks runs stop at it.)
// Sources: game/src/scene/scene2_{func,msg,fcl}.cpp. Every function keeps the name symbols/functions.json gives it; a
// proposed name is given in [brackets] (and in symbols/deltas/scene2.sym). Register ABI throughout: arguments in $a0..
// ($f12.. for floats), the result in $v0 ($f0 for floats). Each body is p3fes_handgen's (register for register, block
// for block as the recompiled one); the named constants below replace only the literal they equal.
//
// --- Records this slice extends or adds (for the editor's Scene view / Inspector; scene.h has the rest) ---------------
// The scene resource record (scene.h scn::res, the common 256 bytes): fields the SceneManager update reads, added here
// in scene2::res (obs: sub_3B9610, sub_3B88C0; the request setters of scene.h write the same fields):
//   +40 flags, more bits: 0x20 the pending-steps word +244 drives this frame (taken once, then cleared), 0x40 the bezier
//       path loops, 0x400 the type-7 float tween runs, 0x2000 a queued motion waits for its slot, 0x4000 the alpha fade,
//       0x8000 the scale tween; bit 3 (scene.h: "shown") also stops the per-frame step: steps = 1 only while it is clear
//   +80 u8 move kind: 0 at a speed (+88 per step, straight at the target), 1 timed (+96 frames, +92 time, eased by +81),
//       2 along the bezier path in the owned block +84 (+88 speed, +92 distance, +96 the path length, f32)
//   +81 u8 move easing: 0 linear, 1..5 a curve row (sub_3B55B0) evaluated by sub_3BBED0
//   +92 move time (s32 frames for kind 1; f32 distance for kind 2)   +96 move frames (s32) / path length (f32)
//   +125 u8 rotation easing (scene.h kRotMode)    +136 vec3 scale from   +148 vec3 scale to   +160 s32 frames
//   +164 s32 time   +168 u8 footstep mode (1 while moving, 2 while turning: a step every +174 frames after the +176
//       delay, one last step when the move / turn ends, then 0)   +169 u8 the step index 0..3   +170 u8 the step sound
//       bank   +172 u16 step timer   +174 u16 interval (0: one step)   +176 u16 delay   +196 f32 tween from   +200 f32 to
//   +204 s32 frames   +208 s32 time
//   +244 s32 pending steps (with flag 0x20)
//   A footstep plays sub_10A4E0(0, +170, 1, +169 + 4 * the field-hit value under the resource) -- the floor kind picks
//   the sound.
// Type 7 (272 B) is the scene camera: +256 f32 the field of view (35.0 at creation; the 0x400 tween writes it), +260 f32
//   the eye distance, +264 s32 1 = the active camera (the SceneManager drives the first such one), +268 u16 the resource
//   id the camera looks at (0: its own position).
// Type 6 (effects, 264 B): +256 u8 the draw pass (0: depth-sorted by the SceneManager Draw, 1: drawn after, unsorted),
//   +260 the EPL handle.
// A bezier path block (+84 of a kind-2 move, 304 B, RwMalloc'd by sub_3B88C0): u8 count, then up to 25 points (8
//   segments), as scene.h's path format.
// The camera shake (sub_3BC940, every frame): 0x7CE658 u16 on, 0x7CE65C s16 frames left, 0x7CE660 / 0x7CE664 u16 the x /
//   z amplitudes (x 0x7CADA0), 0x7CD560 / 0x7CD564 f32 the band each axis may wander in before it drifts back; the
//   offset 0x95AFF0 / 0x95AFF4 (f32 x, z; 0x95AFF8 / 0x95AFFC cleared with them) is what sub_3BC900 returns while the
//   shake is on (scene.h called it "the reference point") and sub_3BB7A0 adds to the camera position.
//
// The message-window slot (14 bytes; fclMisc.c and the battle / shuffle result screens, sub_3C7990 / sub_3C9xxx):
//   +0 s32 the itfMesMng handle (-1: none)  +4 s8 state (0 idle, 1 shown until the manager is not busy, 2 waiting for a
//   choice, 3 closing)  +5 u8 hold (stay in state 2)  +8 s32 a selection to set (-1: none)  +12 u8  +13 s8 the choice
//   read back (-1: none).
// The MsgAssist work (*0x7CE67C; fclMisc_UpdateMsgAssistTask): +0 the request nmList (its node +20 -> a request: +4
//   flags 1 open pending / 2 shown / 4 finished, +16 its message-window slot, +32 the message id, +40 the window kind,
//   +44 the icon index), +4 flags (1 free: no request holds the window, 2 the icon sprites are loading), +20 u32 the
//   icons kept loaded (bit per icon), +24 the sprite-request nmList, +28 eleven 12-byte icon slots {+0 flags: 2 loaded, 4 release;
//   +8 the sprite file}.
// The psStatus work (kwlnTask "psStatus", fclMisc.c 1816..1863): +0 s32 the screen kind (0..4: which sheet layout),
//   +4 s32 state (1 start, 2 request the file, 3 wait for it, 4 run), +8 flags (1 drawn, 2 the alternate panel draw,
//   4 reset the text colour, 8 fade in, 0x10 fade out, 0x20 loaded, 0x40 slide), +12 / +14 s16 fade-in / fade-out
//   frames, +16 s16 fade timer, +18 s16 alpha 0..255, +20 s16 slide frames, +22 s16 slide timer, +24 rgba, +28 / +32
//   the panel position, +34 u16 the persona id, +108 s32 a value printed beside it, +196 the text group, +200 the
//   H_Cdvd request, +204 the file name, +208 / +212 / +216 the sprite banks (sheet, kind 0/1/3, kind 2/4), +220 the
//   layout callback (one of sub_3CB1F0 / sub_3CBA50 / sub_3CCC40 / sub_3CD0B0 / sub_3CD5A0 / sub_3CB960), +232 s8 the
//   cursor row / slide side, +233 s8 the row count, +234 s16 the page.
// The psModel work (sub_3CE2A0 / sub_3CEA50): +0 u16 the view kind, +4 flags (1 shown, 0x10000 animate), +8 s32 state
//   (1..4 as psStatus), +12 u16 the persona id, +14 u16 a second id (another model path, sub_3CDBA0), +24 the model,
//   +28..+32 s16 position offset, +36 f32 scale offset, +64.. a matrix, +128 rgba, +132 / +148 two vec4 colour
//   targets fed to sub_16BC80 / sub_16BDB0, +164..+175 the rgba fade (to, from, s16 time, s16 frames), +176..+211 the
//   first vec4 tween (to, from, time, frames), +212..+247 the second.
// The fclBank work (*0x7CE680 +36): the facility screens' bust-up portraits -- three 20-byte panels from +4, one per
//   bust-up display record of h_chrdsp.c (font2.h: H_ChrDsp_*): {+0 u16 flags (1 used, 2 loading, 4 open, 8 shown, 0x20
//   shares its bust-up with another shown panel, 0x100 the side, 0x200 open request, 0x400 close, 0x800 end, 0x1000
//   kill), +2 u16 the slide state (sub_3CFB50), +4 u32 the bust-up (character << 16 | pose << 8 | expression), +8 s16
//   the display record}. obs: sub_106860 is H_ChrDsp_Request; a request on the dorm machine prints "!!! READ DISP2 1"
//   and asks for bustup/*.bin.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace scene2 {
namespace res {  // the scene resource record (scene.h scn::res has the rest)
inline constexpr s32 kMoveKind = 80;
inline constexpr s32 kMoveEase = 81;
inline constexpr s32 kPathBlock = 84;
inline constexpr s32 kMoveSpeed = 88;
inline constexpr s32 kMoveTime = 92;
inline constexpr s32 kMoveFrames = 96;  // s32 frames (kind 1) / f32 the path length (kind 2)
inline constexpr s32 kRotEase = 125;
inline constexpr s32 kScaleFrom = 136;
inline constexpr s32 kScaleFromY = 140;
inline constexpr s32 kScaleFromZ = 144;
inline constexpr s32 kScaleTo = 148;
inline constexpr s32 kScaleToY = 152;
inline constexpr s32 kScaleToZ = 156;
inline constexpr s32 kScaleFrames = 160;
inline constexpr s32 kScaleTime = 164;
inline constexpr s32 kStepMode = 168;
inline constexpr s32 kStepIndex = 169;
inline constexpr s32 kStepBank = 170;
inline constexpr s32 kStepTimer = 172;
inline constexpr s32 kStepInterval = 174;
inline constexpr s32 kStepDelay = 176;
inline constexpr s32 kFadeHold = 192;
inline constexpr s32 kTweenFrom = 196;
inline constexpr s32 kTweenTo = 200;
inline constexpr s32 kTweenFrames = 204;
inline constexpr s32 kTweenTime = 208;
inline constexpr s32 kPendingSteps = 244;
inline constexpr s32 kTypeWord = 256;  // the first word of the per-type part (type 7: the fov; type 1/3: icon 0)
inline constexpr s32 kModel13 = 296;   // types 1 / 3: the model (scene.h chr::kModel)
inline constexpr s32 kModel2 = 280;    // type 2: the model (scene.h mdl::kModel)
inline constexpr s32 kMotionQ13 = 272; // types 1 / 3: the queued motion request (scene.h chr::kMotionReq)
inline constexpr s32 kMotionQ2 = 256;  // type 2: the queued motion request
}  // namespace res
namespace cam {  // type 7: the scene camera
inline constexpr s32 kFov = 256;
inline constexpr s32 kDist = 260;
inline constexpr s32 kActive = 264;
inline constexpr s32 kTarget = 268;
}  // namespace cam
namespace eff {  // type 6: effects
inline constexpr s32 kPass = 256;
inline constexpr s32 kEpl = 260;
}  // namespace eff
namespace g {  // globals: gp offsets ($gp = 0x7D2CF0) and lo parts of 0x960000 / 0x6A0000
inline constexpr s32 kGpShakeRateX = -22416;  // 0x7CD560: f32: the x band (x amplitude) the offset may wander in
inline constexpr s32 kGpShakeRateZ = -22412;  // 0x7CD564: f32: the z band
inline constexpr s32 kGpShakeOn = -18072;     // 0x7CE658: u16: the camera shake is on
inline constexpr s32 kGpShakeFrames = -18068; // 0x7CE65C: s16: frames left (the amplitudes decay by 1 / (frames + 5))
inline constexpr s32 kGpShakeAmpX = -18064;   // 0x7CE660: u16: the x amplitude (x 0x7CADA0)
inline constexpr s32 kGpShakeAmpZ = -18060;   // 0x7CE664: u16: the z amplitude
inline constexpr s32 kGpShakeScale = -32592;  // 0x7CADA0: f32: the amplitude unit
inline constexpr s32 kLoShakeX = -20496;      // 0x95AFF0: f32: the shake offset x (scene.h g::kLoRefPointX)
inline constexpr s32 kLoShakeZ = -20492;      // 0x95AFF4: f32: the shake offset z
inline constexpr s32 kLoShakeW2 = -20488;     // 0x95AFF8: cleared with the offset
inline constexpr s32 kLoShakeW3 = -20484;     // 0x95AFFC: cleared with the offset
inline constexpr s32 kGpAssist = -18036;      // 0x7CE67C: -> the MsgAssist work
inline constexpr s32 kGpBankTask = -18032;    // 0x7CE680: -> the fclBank task (scene.h g::kGpBankTask)
inline constexpr s32 kGpPersonaTable = -18640; // 0x7CE420: PERSONA.TBL section 0 (14-byte records, +2 arcana)
inline constexpr s32 kLoRwMalloc = 376;       // 0x960178: the RwMalloc slot
inline constexpr s32 kLoRwFree = 380;         // 0x96017C: the RwFree slot
inline constexpr s32 kLoMsgSlots = 15952;     // 0x6A3E50: s32[]: the message handles sub_3C7DD0 destroys
}  // namespace g
namespace msgw {  // the 14-byte message-window slot
inline constexpr s32 kHandle = 0;
inline constexpr s32 kState = 4;
inline constexpr s32 kHold = 5;
inline constexpr s32 kSelect = 8;
inline constexpr s32 kFlag12 = 12;
inline constexpr s32 kChoice = 13;
}  // namespace msgw
namespace assist {  // the MsgAssist work
inline constexpr s32 kList = 0;
inline constexpr s32 kFlags = 4;
inline constexpr s32 kKeepMask = 20;
inline constexpr s32 kSprList = 24;
inline constexpr s32 kSlots = 28;         // eleven 12-byte icon slots (sprslot)
inline constexpr s32 kSlotFile = 36;      // kSlots + 8: slot 0's sprite file
}  // namespace assist
namespace req {  // a MsgAssist request (an nmList node's payload)
inline constexpr s32 kFlags = 4;
inline constexpr s32 kWin = 16;   // its message-window slot (msgw)
inline constexpr s32 kMsg = 32;
inline constexpr s32 kKind = 40;
inline constexpr s32 kIcon = 44;
}  // namespace req
namespace sprslot {  // the 12-byte sprite request / icon slot of the MsgAssist work
inline constexpr s32 kFlags = 0;
inline constexpr s32 kKind = 4;
inline constexpr s32 kFile = 8;
}  // namespace sprslot
namespace nml {  // an nmList (nmlist.c; scene.h sub_3C4650 makes its nodes)
inline constexpr s32 kFirst = 4;
inline constexpr s32 kCursor = 12;
inline constexpr s32 kCount = 16;  // u16
}  // namespace nml
namespace nmnode {  // an nmList node
inline constexpr s32 kNext = 16;
inline constexpr s32 kPayload = 20;
}  // namespace nmnode
namespace sprh {  // a sprite draw handle (ui4.h spr: the SprHandle, 0x34 bytes)
inline constexpr s32 kX = 16;         // f32
inline constexpr s32 kY = 20;         // f32
inline constexpr s32 kInvAlpha = 25;  // u8: 255 - alpha
inline constexpr s32 kU = 32;         // f32 (sub_3CA780's $f13)
inline constexpr s32 kW = 36;         // s16
inline constexpr s32 kH = 38;         // s16
inline constexpr s32 kFix0 = 40;      // u16: 4096 x a float argument
inline constexpr s32 kFix1 = 42;      // u16: 4096 x a float argument
inline constexpr s32 kZ = 44;         // f32
inline constexpr s32 kR = 48;         // u8 (g +49, b +50)
inline constexpr s32 kG = 49;
inline constexpr s32 kB = 50;
}  // namespace sprh
namespace ps {  // the psStatus work
inline constexpr s32 kKind = 0;
inline constexpr s32 kState = 4;
inline constexpr s32 kFlags = 8;
inline constexpr s32 kFadeIn = 12;
inline constexpr s32 kFadeOut = 14;
inline constexpr s32 kTimer = 16;
inline constexpr s32 kAlpha = 18;
inline constexpr s32 kSlideFrames = 20;
inline constexpr s32 kSlideTime = 22;
inline constexpr s32 kRgba = 24;
inline constexpr s32 kPosX = 28;
inline constexpr s32 kPosY = 32;
inline constexpr s32 kPersona = 34;
inline constexpr s32 kValue = 108;
inline constexpr s32 kText = 196;
inline constexpr s32 kCdReq = 200;
inline constexpr s32 kFile = 204;
inline constexpr s32 kSprSheet = 208;
inline constexpr s32 kSprA = 212;
inline constexpr s32 kSprB = 216;
inline constexpr s32 kLayout = 220;
inline constexpr s32 kRow = 232;
inline constexpr s32 kRows = 233;
inline constexpr s32 kPage = 234;
}  // namespace ps
namespace psm {  // the psModel work
inline constexpr s32 kView = 0;
inline constexpr s32 kFlags = 4;
inline constexpr s32 kState = 8;
inline constexpr s32 kPersona = 12;
inline constexpr s32 kAltId = 14;
inline constexpr s32 kModel = 24;
inline constexpr s32 kOffX = 28;   // s16
inline constexpr s32 kOffY = 30;   // s16
inline constexpr s32 kOffZ = 32;   // s16
inline constexpr s32 kScale = 36;  // f32
inline constexpr s32 kRgba = 128;
inline constexpr s32 kRgbaG = 129;
inline constexpr s32 kRgbaB = 130;
inline constexpr s32 kRgbaA = 131;
inline constexpr s32 kColAY = 136;
inline constexpr s32 kColAZ = 140;
inline constexpr s32 kColAW = 144;
inline constexpr s32 kColBY = 152;
inline constexpr s32 kColBZ = 156;
inline constexpr s32 kColBW = 160;
inline constexpr s32 kColA = 132;
inline constexpr s32 kColB = 148;
inline constexpr s32 kFadeTo = 164;
inline constexpr s32 kFadeFrom = 168;
inline constexpr s32 kFadeTime = 172;
inline constexpr s32 kFadeFrames = 174;
inline constexpr s32 kTweenATo = 176;
inline constexpr s32 kTweenAFrom = 192;
inline constexpr s32 kTweenATime = 208;
inline constexpr s32 kTweenAFrames = 210;
inline constexpr s32 kTweenBTo = 212;
inline constexpr s32 kTweenBFrom = 228;
inline constexpr s32 kTweenBTime = 244;
inline constexpr s32 kTweenBFrames = 246;
}  // namespace psm
namespace psfade {  // psModel +164: the rgba fade {u8 to[4], u8 from[4], s16 time, s16 frames}
inline constexpr s32 kTo = 0;
inline constexpr s32 kToG = 1;
inline constexpr s32 kToB = 2;
inline constexpr s32 kToA = 3;
inline constexpr s32 kFrom = 4;
inline constexpr s32 kFromG = 5;
inline constexpr s32 kFromB = 6;
inline constexpr s32 kFromA = 7;
inline constexpr s32 kTime = 8;
inline constexpr s32 kFrames = 10;
}  // namespace psfade
namespace tween4 {  // psModel +212: a vec4 tween {f32 to[4], f32 from[4], s16 time, s16 frames}
inline constexpr s32 kTo = 0;
inline constexpr s32 kToY = 4;
inline constexpr s32 kToZ = 8;
inline constexpr s32 kToW = 12;
inline constexpr s32 kFrom = 16;
inline constexpr s32 kFromY = 20;
inline constexpr s32 kFromZ = 24;
inline constexpr s32 kFromW = 28;
inline constexpr s32 kTime = 32;
inline constexpr s32 kFrames = 34;
}  // namespace tween4
namespace mdlx {  // the model record (field / battle model, sub_316E00): what psModel touches
inline constexpr s32 kFlags = 216;  // u16: 0x100 cleared at set-up, 0x200 for kind-2 personas
}  // namespace mdlx
namespace bank {  // the fclBank object (*0x7CE680: an nmList of requests, +36 the work) and its panels
inline constexpr s32 kWork = 36;
inline constexpr s32 kPanels = 4;       // the first panel, from the work
inline constexpr s32 kPanelStride = 20;
inline constexpr s32 kPFlags = 0;       // from a panel
inline constexpr s32 kPState = 2;
inline constexpr s32 kPBank = 4;
inline constexpr s32 kPSlot = 8;
}  // namespace bank
namespace bankw {  // a panel's fields from the work + 20 i
inline constexpr s32 kFlags = 4;
inline constexpr s32 kState = 6;
inline constexpr s32 kBank = 8;
inline constexpr s32 kSlot = 12;
}  // namespace bankw
namespace bankreq {  // a bank request (an nmList node's payload)
inline constexpr s32 kFlags = 0;  // u16
inline constexpr s32 kBank = 4;
}  // namespace bankreq
}  // namespace scene2

// --- mt_sceneFunc.c: the SceneManager task (scene2_func.cpp) ---------------------------------------------------------
// [MT_SceneFunc_DirAngle] (from, to, out_dir, out_angle) The direction from -> to (not normalised) into out_dir and its
// heading in degrees (acos of the dot of the normalised direction, y then zeroed, with the axis 0x6A2DC8, x 57.29578
// (0x7CAF18), negative when x < 0) into *out_angle: 1; a zero-length direction returns 0 and writes nothing.
void sub_3B8540(EEContext& ctx);  // 0x3B8540
// [MT_SceneFunc_RequestPathMove] (res, path, loop, $f12 speed) Starts a bezier path move: flag bit 0 on, 0x40 off (on
// again when loop == 1), speed +88, kind 2, distance 0; the 304-byte path block +84 is allocated once (RwMalloc, hint
// 0x40000; asserts mt_sceneFunc.c 571) and the path copied into it; +96 = its length (sub_3BC0E0), printed ("path bezier
// max kyori = %f"). 1, or 0 for NULL.
void sub_3B88C0(EEContext& ctx);  // 0x3B88C0
// [MT_SceneFunc_UpdateRes] (res) The SceneManager's per-frame update of one resource: the steps this frame (flag 0x20:
// +244, taken once; else 1 while flag bit 3 is clear, 0 when set); the move (flag bit 0, kind +80: 0 at +88 per step
// until within one step -- "move idou end"; 1 timed over +96 frames, linear or eased (+81) -- "move length0 end" for 0
// frames; 2 along the path +84 (sub_3BC220), the heading taken from the path unless bit 3, looping with 0x40), the
// rotation (flag bit 2: +128 frames, eased by +125, through the shorter turn sub_3BBAA0), the angles wrapped
// (sub_3BB9B0), the scale (0x8000, +136 -> +148 over +160), the alpha fade (0x4000: effects through their EPL colour,
// objects through the model colour with the "tokushu trans" switch unless the target is 255 or +192 is 0), the type-7
// fov tween (0x400; its time base is +92, the move time -- a quirk of the original), the icon EPLs (types 1 / 3: +256 ..
// +264; type 6: +260; sub_34FD30), a queued motion (0x2000: once the model's motion slot is ready, sub_3B8FF0) and the
// footsteps (+168..+176: sub_10A4E0 with the floor's hit value). Every changed transform is applied (sub_3B7460).
void sub_3B9610(EEContext& ctx);  // 0x3B9610
// [MT_SceneFunc_SetNpcIcon] (n, icon) The icon EPL over NPC resource 0xC00 | (n & 0x3FF) (sub_3BAC40); 0 when the
// resource is missing.
void sub_3BB060(EEContext& ctx);  // 0x3BB060
// [MT_SceneFunc_CameraEye] (out, camera, $f12 dist) The type-7 camera's eye: from its position -- or, with a target id
// (+268) that is found, from the target's position shifted by -15 x the normalised first row of the matrix of (that
// position, the camera's angles) in x and z (sub_3B79A0, sub_4C69F0), with dist replaced by +260 -- moved back by dist
// along the view direction of the camera's angles (sub_3BB450; +z for unturned angles: out = pos - dist x (0, 0, 1)).
void sub_3BB620(EEContext& ctx);  // 0x3BB620
// [MT_SceneFunc_ApplyCamera] (camera) Places the main RW camera (sub_198590, its frame +4) at a type-7 resource: the eye
// (sub_3BB620) back into the record, a fresh matrix (identity, flags 0x20003) turned by the three axes 0x6A2F18 /
// 0x6A2F28 / 0x6A2F38 (sub_4C31B0, pre-concatenated) and translated to the eye, plus the shake offset (sub_3BC900) when
// the shake is on; the frame transform set (sub_4CB930 / sub_4CB7F0), the matrix freed and the camera updated
// (sub_1A4580). Nothing without a camera or frame.
void sub_3BB7A0(EEContext& ctx);  // 0x3BB7A0
// [MT_SceneFunc_DirToAngles] (dir, out) The heading of a direction as angles {0, a, 0} in degrees (acos of the
// normalised direction, y then zeroed, against 0x6A2F48, negative for x < 0); {0, 0, 0} for a zero-length direction.
void sub_3BBB90(EEContext& ctx);  // 0x3BBB90
// [MT_SceneFunc_Ease] (curve, $f12 t) The eased parameter of curve row `curve` (< 6; asserts mt_sceneFunc.c 2432): a
// one-segment path through (0, c0), (c1, c2), (c3, 1) .. built on the stack from the four values of sub_3B55B0(curve),
// evaluated at t (sub_3BBD40); the result's y in $f0.
void sub_3BBED0(EEContext& ctx);  // 0x3BBED0
// [MT_SceneFunc_PathAt] (path, out_pos, out_angles, $f12 dist, $f13 length) The point at distance `dist` along a bezier
// path (20 chords per segment, the chord interpolated) and its heading (sub_3BBB90 of the local direction) into
// out_angles; dist >= length gives the last point with the last chord's heading (and returns 1.0).
void sub_3BC220(EEContext& ctx);  // 0x3BC220
// [MT_SceneFunc_UpdateShake] The camera shake, once a frame: off -> the offset words 0x95AFF0..0x95AFFC cleared; on with
// no frames left -> switched off; else each axis with an amplitude a wanders randomly (sub_358030) inside +-a * band
// (0x7CD560 / 0x7CD564) or drifts back towards 0 by 0.5 a (1 + r), clamped to +-a; then both amplitudes lose 1 /
// (frames + 5) and the frames count down.
void sub_3BC940(EEContext& ctx);  // 0x3BC940
// Update of "SceneManager Task": the shake (sub_3BC940), every resource of types 1..21 through sub_3B9610, then the
// first type-7 camera that is active (+264 == 1) applied (sub_3BB7A0); returns 0 (run again).
void sub_3BCCB0(EEContext& ctx);  // 0x3BCCB0
// Destroy of "SceneManager Task": a tail call of sub_3BCC80.
void sub_3BCD80(EEContext& ctx);  // 0x3BCD80
// [MT_SceneFunc_CompareEffDepth] (a, b) qsort comparator of two type-6 resources (pointers to pointers): the distance of
// b's EPL position from the camera (sub_34FFC0, the RW camera frame's position) minus a's, as an int -- far ones first.
void sub_3BCDA0(EEContext& ctx);  // 0x3BCDA0
// [MT_SceneFunc_DrawSortedEffects] (first) Collects the visible (flag bit 1) effects with an EPL and draw pass 0 from a
// type-6 list into an RwMalloc'd array, sorts them back to front (qsort, sub_3BCDA0) and draws each (sub_34FD70(epl,
// 3)); frees the array.
void sub_3BCEB0(EEContext& ctx);  // 0x3BCEB0
// Update of "SceneManager Draw": the sorted effects (sub_3BCEB0), then the visible pass-1 effects in list order
// (sub_34FD70); returns 0.
void sub_3BD010(EEContext& ctx);  // 0x3BD010
// A script command (COMM handler): parameter 0 read and dropped, then sub_3BB010(0x400, parameter 1 & 0xFF); returns 1.
void sub_3BD230(EEContext& ctx);  // 0x3BD230

// --- nmlist.c / the message-window helpers / fclMisc.c "MsgAssist" (scene2_msg.cpp) ----------------------------------
// [nmListSort] (list, compare) Sorts an nmList: its nodes (+4 first, +16 next; +16 u16 count) into an RwMalloc'd array,
// qsort with `compare`, relinked in that order (nmListRebuild), the cursor +12 reset to the first; nothing for an
// empty list.
void sub_3C4FC0(EEContext& ctx);  // 0x3C4FC0
// [MsgWinStep] (clear) One step of the current message-window slot (sub_3C7D50; nothing when absent or without a
// handle): state 1 -> 2 once the manager is not busy; 2 sets a pending selection (+8) and, unless held (+5), reads the
// choice (+13; itfMesMngGetSelectWord84 / itfMesMngGetSelection) or goes to 3; 3 closes the window (busy off, the
// optional clear sub_3A2A30, sub_3A3420(handle, 0), sub_3C7C90(1)) and returns to 0.
void sub_3C7990(EEContext& ctx);  // 0x3C7990
// [MsgHandleRelease] (i) Destroys message handle i of the table 0x6A3E50 (itfMesMngDestroyHandle) and marks it -1.
void sub_3C7DD0(EEContext& ctx);  // 0x3C7DD0
// [fclMiscAssistUpdateSprites] (work) The MsgAssist sprite loads: the head sprite request (+24 list) is loaded once
// (sprAddFile of "facility/i_jmes01.spr", "facility/i_jmes_bNN.spr" or, for kind 9 on the AGS build (sub_17D800),
// "facility/AGS_i_jmes_b09.spr" -- sprintf) and finished when ready (flag 2, sub_3C49E0 unlinks it); then every icon
// slot marked for release drops its sprite file once it is ready (sub_1124B0). Asserts fclMisc.c 941 on NULL.
void sub_3C8550(EEContext& ctx);  // 0x3C8550
// Update of the "MsgAssist" task. While it is free (+4 bit 0): with the icon sprites loading (bit 1) it waits for them
// (sub_3C8810 / sub_3C8D80), then advances the request list (sub_3C8DC0, sub_3C4A90) and refreshes the eleven icon slots
// (sub_3C8770); otherwise the head request takes the window (bit 0 off; sub_3C91B0 on its slot with its kind,
// sub_3C8400 for icon 0 and its icon, request flags 3). Then a shown head request whose window finished (sub_3C8B50)
// frees the task again (bit 0) and is unlinked (sub_3C49E0); the sprites are updated (sub_3C8550); returns 0.
void fclMisc_UpdateMsgAssistTask(EEContext& ctx);  // 0x3C89A0
// [fclMiscAssistStepRequest] (work, request) One request: finished (+4 bit 2) -> once the manager state has none of
// 0x3300 the window is released (sub_3C9240) and the icon slots it used marked for release unless kept (+20; asserts
// fclMisc.c 1003 / 1004), 1; pending (bit 0) -> waits for the slot sprites, then shows the message (sub_3C9290); then the
// window steps (sub_3C9390) and, once it closed (sub_3C9340 == 0), is cleared (sub_3C9460) and marked finished. 0
// otherwise. Asserts fclMisc.c 995 on a NULL work.
void sub_3C8B50(EEContext& ctx);  // 0x3C8B50
// [fclMiscAssistClose] Closes the head request's window when it is shown (sub_3C9460) and marks it finished.
void sub_3C8FA0(EEContext& ctx);  // 0x3C8FA0
// [fclMiscAssistDrawIcon] (x, y, alpha, slot, sprite, $f12 z, $f13, $f14) Draws icon slot `slot` when its sprite file
// is loaded: a sprite handle (sprCreateHandle(0, file, sprite)) at (x, y, z), alpha 255 - a, $f13 / $f14 as the two
// 4096-scaled fixed values +40 / +42 (the float -> u16 conversion with its 2^31 bias), drawn (sub_1127D0(h, 1)) and
// freed (sub_115980).
void sub_3C9000(EEContext& ctx);  // 0x3C9000
// [MsgWinOpen] (slot, kind) Resets a message-window slot (handle -1, state 0, hold 0, selection -1, +12 / +13 1) and,
// when it has no handle, creates one (itfMesMngInitialize(kind), sub_3A4360(h, 5)): 1; else 0. Since the reset writes
// handle -1 first, the "already has one" branch is dead: a non-NULL slot always gets a new handle (1) -- an old one
// is dropped without itfMesMngDestroyHandle. A NULL slot skips the reset and reads address 0.
void sub_3C91B0(EEContext& ctx);  // 0x3C91B0
// [MsgWinRelease] (slot) Clears the window (sub_3C9460) and destroys its handle: handle -1, state 0, hold 0.
void sub_3C9240(EEContext& ctx);  // 0x3C9240
// [MsgWinShow] (slot, icon, msg) Shows message `msg` in the slot's window: state flags, the request
// (itfMesMngRequestMessage(h, msg, 0)), the layout sub_3A5210(h, 1, 5, 32, 0), the icon (sub_3A8600(h, icon)); state 1.
void sub_3C9290(EEContext& ctx);  // 0x3C9290
// [MsgWinUpdate] (slot) One step of a window slot: 1 -> 2 once not busy; 2 drops a pending selection and goes to 3
// unless held; 3 clears the window (sub_3C9460).
void sub_3C9390(EEContext& ctx);  // 0x3C9390
// [MsgWinClear] (slot) For a slot with a handle: busy off, sub_3A2A30, sub_3A3420(h, 0), state 0: 1; else 0.
void sub_3C9460(EEContext& ctx);  // 0x3C9460

// --- fclMisc.c "psStatus" / "psModel_dummy", fclBankManager.c (scene2_fcl.cpp) --------------------------------------
// [psStatusLoadSprites] (work) Builds the sprites from the loaded archive (+200): the shared banks 6 / 8 / 10 (members
// 0..2 -> sprCreateHandleFromData -> sub_119A80), the sheet (member 3 -> +208) and the kind's extra bank (member 4 ->
// +216 for kinds 2 / 4, +212 for 0 / 1 / 3); prints its three progress lines (printf + sub_1052B0).
void sub_3C9FE0(EEContext& ctx);  // 0x3C9FE0
// Update of "psStatus": states 1 (print), 2 (request the file +204, H_Cdvd_Request(name, 1) -> +200), 3 (once loaded:
// the sprites, sub_3C9FE0; state 4, flag 0x20); state 4 runs the fade in (8) / out (0x10) over +12 / +14 frames into the
// alpha +18 (255 t / n), the slide (0x40: +22 up to +20 or down to 0 by the side +232), the layout callback +220 and
// the text group's colour (sub_133B70 / sub_133B80; flag 4 resets it, sub_133B40 sets the alpha while drawn); 0.
void fclMisc_UpdatePsStatusTask(EEContext& ctx);  // 0x3CA230
// Destroy of "psStatus": frees the sprite banks 6 / 8 / 10 (sub_119A60 -> sub_1124B0), the sheet and the two kind banks,
// the file request (H_Cdvd_Destroy) and the work (RwFree).
void sub_3CA6B0(EEContext& ctx);  // 0x3CA6B0
// [psStatusDrawSprite] (x, y, rgba, sprite, w, h, file, $f12 z, $f13, $f14, $f15) One sprite of a sheet: a handle
// (sprCreateHandle(0, file, sprite)) at (x, y, z), alpha 255 - (rgba & 0xFF), r / g / b from rgba's upper bytes, w / h
// (+36 / +38; mostly 0, the bottom bar's end piece -260), $f13 at +32, $f14 / $f15 as the two 4096-fixed values +40 /
// +42 (the layouts pass 0, 0, 1.0, 1.0), drawn and freed; 0. The layouts pass rgba = 0xFFFFFF00 | the work's alpha
// (+18).
void sub_3CA780(EEContext& ctx);  // 0x3CA780
// [psStatusDrawTabs] (work) The row tabs: for each of +233 rows the tab frames 23 / 24 (the cursor row +232) and the
// labels 25 + 2 i / 26 + 2 i at the per-count positions of the tables 0x6A41E8 / 0x6A41F8, the last row 37 / 38.
void sub_3CACC0(EEContext& ctx);  // 0x3CACC0
// [psStatusLayoutSheet] (work) Layout callback: the sheet frame (frames 3..6), the text group (sub_133A80 then
// sub_1332F0 / sub_133180 by flag 2), and by page +234: 2 the kind's header frames (21 / 22 or 2 / 3), the tabs
// (sub_3CACC0) and, with a persona and a value, the arcana icon (sub_16DEB0 / sub_16DBA0) and two numbers
// (sprintf "%d" -> sub_40EC50 with the colour callback sub_3CB050); 1 the header and frame 20; 0 frame 20 and the numbers.
void sub_3CB1F0(EEContext& ctx);  // 0x3CB1F0
// [psStatusLayoutBar] (work) Layout callback: the three frames of the bottom bar (2 at the origin, 0 at (-357, 189),
// 1 at (-97, 189) 260 wide).
void sub_3CB960(EEContext& ctx);  // 0x3CB960
// [psStatusLayoutPages] (work) Layout callback for the paged screens (page +234 4, 3, 2, ...): the sheet frames, the
// text group, the panel slide (sub_3CA960), the kind's header and, per row, the row frames (69 / 70, 52 / 53, 71 + 2 i
// / 72 + 2 i and the like) at the x positions of the table 0x7CD708.
void sub_3CBA50(EEContext& ctx);  // 0x3CBA50
// [psStatusLayoutSheetBar] (work) Layout callback: the bottom bar and the sheet frames, the text group and its panel
// draw (sub_1332F0 or sub_133460), then the page's frames.
void sub_3CCC40(EEContext& ctx);  // 0x3CCC40
// [psStatusLayoutB] (work) Layout callback: as sub_3CCC40 with the other page set (sub_1332F0 / sub_133180).
void sub_3CD0B0(EEContext& ctx);  // 0x3CD0B0
// [psStatusLayoutC] (work) Layout callback: a third page set of the same frames.
void sub_3CD5A0(EEContext& ctx);  // 0x3CD5A0
// Update of "psModel_dummy": once the model's load finished (sub_316F70) it is released (sub_3174E0): -1; else 0.
void fclMisc_UpdatePsModelDummyTask(EEContext& ctx);  // 0x3CDA00
// [psModelUpdate] (task) The persona-model preview, once a frame: states 1 / 2 release an old model and request the
// persona's (sub_316E00(11, id, 0); none for id 0 -> state 4); 3 once loaded: motion 8 (sub_319230), the second id's
// set-up (sub_3CDBA0) or the model's colour flags by the persona's kind (sub_17C0E0: 4 -> sub_319070, 2 -> flag 0x200)
// and the two colour vectors (sub_16BC80 / sub_16BDB0); state 4 (shown, animating) runs the rgba fade and the two vec4
// tweens (the float -> u8 conversions with the 2^31 bias) and draws (sub_3CEA50); 0.
void sub_3CE2A0(EEContext& ctx);  // 0x3CE2A0
// [psModelDraw] (work) Draws the persona model into the main camera: saves the camera's view window / matrix and the
// two light colours, sets the persona's light colours (+132 / +148, sub_4944B0), turns the light frame by the
// persona's quaternion (sub_16BEE0, the matrix built from it, sub_4C2F30), places the model (sub_16BF80's offset +28..,
// scale +36, the matrix +64.., colour +128 with its alpha scaled; sub_318A70 / sub_318A90 / sub_318AD0), sets the
// view window to the persona's size / (640, 448), renders it between RwCameraBeginUpdate / RwCameraEndUpdate with the
// render states 6, 8, 14 and RpSky states 2 / 3 (sub_317A20; asserts fclMisc.c 2861 when the camera will not begin),
// then restores the camera, lights and view window; 0.
void sub_3CEA50(EEContext& ctx);  // 0x3CEA50
// Destroy of the psModel work: a loaded model (+24) is released at once (sub_3174E0); one still loading is handed to a
// "psModel_dummy" task (priority 5244, fclMisc_UpdatePsModelDummyTask) that releases it when it arrives; the work is freed (RwFree).
void fclMisc_CreatePsModelDummyTask(EEContext& ctx);  // 0x3CF080
// [fclBankTakePanel] (request) Takes a bust-up panel for a request node (+20 -> {u16 flags, .., u32 bust-up}): the first
// free panel, else the first used one neither loading nor shown; prints "BankNo:%d"; none -> -1. The panel gets the
// bust-up, the flags and its record number; the bust-up is requested (H_ChrDsp_Request sub_106860(slot, character,
// pose, expression)), its fade set (sub_106EC0(slot, 1)) and flip cleared (sub_106F30(slot, 0)), the panel marked used +
// loading and the request unlinked (sub_3C49E0); returns the panel.
void sub_3CF6C0(EEContext& ctx);  // 0x3CF6C0
// Update of the "fclBank" task, the facility bust-ups (asserts fclBankManager.c 624 without one): serves the request
// list (sub_3CF6C0; "No Bank!!!" when no panel is free), then per used panel: loading -> open once the bust-up is in
// (H_ChrDsp_IsReady sub_106FF0); open with a request: 0x200 "OPEN" (sub_3CFAC0; the same character on another shown
// panel of the same side -> 0x20), 0x400 "CLOSE" (shown: slide state 4), 0x800 "END" (shown: becomes a close; else
// H_ChrDsp_Release sub_106730), 0x1000 "KILL" (H_ChrDsp_Release); then the panel slides (sub_3CFB50); 0.
void fclBank_UpdateTask(EEContext& ctx);  // 0x3CFE50

}  // namespace p3fes::game
