// Slice finalA (game/src/field/finalA.cpp): the last functions other tests held recompiled -- 19 p3fes_handgen bodies
// (register ABI: arguments in $a0.., the result in $v0) made readable with a role comment each and the layouts below.
// Proposed names are in brackets (symbols/deltas/finalA.sym); the code keeps symbols/functions.json's names.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

// --- the layouts the bodies read (offsets in bytes; from the instructions, the pseudocode reference as a hint) ------
namespace finalA {

// The BGM / stream channel table 0x7E4430: 6 records of 308 bytes (sweep5a::kBgmChannels); sub_10A410 fills one.
inline constexpr u32 kBgmChannels = 0x7E4430u;
inline constexpr s32 kBgmChannelSize = 308;
inline constexpr u32 kBgmActive = 0;    // s32: 1 once started
inline constexpr u32 kBgmWord8 = 8;     // u16: cleared at the start
inline constexpr u32 kBgmWord12 = 12;   // u16: cleared at the start
inline constexpr u32 kBgmState = 20;    // u16: 6 at the start
inline constexpr u32 kBgmName = 22;     // char[]: "BGM:<file>"

// $gp words (crt0's $gp = 0x7D2CF0).
inline constexpr s32 kGpKeepFlags = -19832;      // 0x7CDF78: set -> datInitNewGame keeps the flags 387..393
inline constexpr s32 kGpWord7CDFFC = -19700;     // 0x7CDFFC: cleared by datInitNewGame
inline constexpr s32 kGpGmRootWork = -18788;     // 0x7CE38C: the game-root work (gm_root.c)
inline constexpr s32 kGpEncountTbl = -18504;     // 0x7CE4A8: gEncountTbl, 28-byte records
inline constexpr s32 kGpSceneIds = -22448;       // 0x7CD540: -> {s32 major, s32 minor}
inline constexpr s32 kGpLiveEcCount = -19044;    // 0x7CE28C: the number of live shadows
inline constexpr s32 kGpTextureModule = -17312;  // 0x7CE950: the RwTexture module's offset in the engine instance
inline constexpr s32 kGpFadeColour = -27408;     // 0x7CC1E0: f32, the fade's initial colour word (sub_1A60D0)
inline constexpr s32 kGpFarPlane = -32244;       // 0x7CAEFC: f32, the "no contact" distance of the collision scans
inline constexpr s32 kGpFontAlpha = -32604;      // 0x7CAD94: f32, the kind-10 alpha scale of sub_3B2CB0
inline constexpr s32 kGpFontMiddle = -32628;     // 0x7CAD7C: f32, the vertical-centre factor of sub_3B2CB0
inline constexpr s32 kGpFontPhase = -22512;      // 0x7CD500: s16, bits 0..1 = 1 while building, 2 while drawing

// The game-root work (44 bytes, RW-allocated by gmRoot_CreateGameRootTask).
inline constexpr u32 kGmRootFlags = 0;    // bit 0 set at the creation
inline constexpr u32 kGmRootState = 4;    // 0 at the creation
inline constexpr u32 kGmRootTask = 8;     // the kwln task "game root"
inline constexpr u32 kGmRootWord40 = 40;  // sub_188860(task)

// The model-fade work (20 bytes, RW-callocated by sub_1A60D0; task "rmd fade(kosaka)").
inline constexpr u32 kFadeModel = 4;    // the model handle
inline constexpr u32 kFadeFrames = 8;   // f32: the frame count (an s32 argument converted)
inline constexpr u32 kFadeTarget = 12;  // f32: 255.0 for a fade-in (0 frames), else 0
inline constexpr u32 kFadeColour = 16;  // the colour argument

// The floor-effect work of the field camera task (sub_1A9400's $a0->+60).
inline constexpr u32 kFxWord16 = 16;   // cleared by an index below 0
inline constexpr u32 kFxCount = 32;    // live effect count
inline constexpr u32 kFxSlots = 36;    // u32[4]: effect nodes (sub_34FCF0 destroys one)

// Field units (448 bytes; gFldUnitsEc 0x86EDA0 [24], gFldUnitsPc 0x8717A0 [4]; field_hi.h fldhi::).
inline constexpr u32 kEcUnits = 0x86EDA0u;
inline constexpr u32 kPcUnits = 0x8717A0u;
inline constexpr u32 kUnitSize = 448;
inline constexpr u32 kUnitInstance = 72;    // encounter instance (datUnitCreateEc) / DatUnit holder; 0 = free
inline constexpr u32 kUnitEncounter = 76;   // -> the gEncountTbl record
inline constexpr u32 kUnitModel = 80;       // the model (sub_316E00(8, kind, 0))
inline constexpr u32 kUnitResource = 84;    // the scene resource (u16 id at +0); with +72 the unit is live
inline constexpr u32 kUnitSpawn = 88;       // 272 bytes: the spawn record copied (68 words)
inline constexpr u32 kUnitSpawnPtr = 360;   // -> +88
inline constexpr u32 kUnitTask364 = 364;    // kwln tasks sub_1D1640 destroys (364, 368, 376, 384, 372)
inline constexpr u32 kUnitLevel = 388;      // the average level of the encounter's genera (1000 for the size class 3)
inline constexpr u32 kUnitModelKind = 396;  // 1..5 from the encounter kind (the id's high half)
inline constexpr u32 kUnitSizeClass = 400;  // 1 / 2 / 3 by the encounter's genus count (1, 2..3, 4..)
inline constexpr u32 kUnitCellX = 404;      // s16: (spawn +256 + 400) / 800
inline constexpr u32 kUnitCellZ = 406;      // s16: (spawn +264 + 400) / 800
inline constexpr u32 kUnitWord424 = 424;    // u16: cleared at the creation

// The collision scans (sub_1AB390 world, sub_1ABD20 clumps): up to 64 contacts on the frame, {point[3]} at +0,
// {normal[3]} at +768, the distance at +1536 (gp-32244 = none) and, for the clump scan, a flag word at +2560.
inline constexpr u32 kHitMax = 64;
inline constexpr u32 kHitNormals = 768;
inline constexpr u32 kHitDistances = 1536;
inline constexpr u32 kHitFlags = 2560;

// The thread context StartThread prepares at stack + size - 672 (libkernel): 42 quad words.
inline constexpr u32 kThreadContextSize = 672;
inline constexpr u32 kContextArg = 64;     // $a0 of the new thread (64-bit)
inline constexpr u32 kContextSaved = 448;  // four 64-bit words widened from their low halves (+448 .. +504)

// libpad (0x96DCC0 ..): the RPC clients, the per-port / per-slot records and the request buffer.
inline constexpr u32 kPadInitDone = 0x782748u;    // scePadInit ran
inline constexpr u32 kPadVerbose = 0x78274Cu;     // messages through scePrintf
inline constexpr u32 kPadRpcCd0 = 0x96DCC0u;      // sceSifBindRpc 0x80000100 (+36 = the server once bound)
inline constexpr u32 kPadRpcCd1 = 0x96DCE8u;      // sceSifBindRpc 0x80000101
inline constexpr u32 kPadRecords = 0x96DD10u;     // 112 per port, 28 per slot: +0 buffer, +4 -> state word, +8 IOP
                                                  // address, +12 0, +16 open
inline constexpr u32 kPadStates = 0x96DE00u;      // 128 per port, 32 per slot: the state word
inline constexpr u32 kPadRpcBuf = 0x96DF00u;      // +0 func (1 = open), +4 port, +8 slot, +12 result, +16 buffer,
                                                  // +20 the IOP address
inline constexpr u32 kPadPortStride = 112, kPadSlotStride = 28;

// libmc2: the library flag and sceMc2CreateSocket's error codes.
inline constexpr u32 kMc2Ready = 0x7827D8u;
inline constexpr u32 kMc2ErrNotReady = 0x81018001u;
inline constexpr u32 kMc2ErrParam = 0x81010016u;   // type (+4) not 2 / 3, or +8 set
inline constexpr u32 kMc2ErrSocket = 0x81010017u;  // _sceMcCoreCreateSocket failed

// frFont line chains (frFontBuildGlyphList): a line {+3 s8 spacing, +4 x (1/16 px), +8 y (1/8 px), +20 f32 scale,
// +28 first glyph, +36 next line}; a glyph {+12 advance, +16 colour, +40 next}.
inline constexpr u32 kLineSpacing = 3, kLineX = 4, kLineY = 8, kLineScale = 20, kLineGlyphs = 28, kLineNext = 36;
inline constexpr u32 kGlyphAdvance = 12, kGlyphColour = 16, kGlyphNext = 40;
inline constexpr u32 kAlignRight = 2, kAlignBottom = 4, kAlignCentre = 8, kAlignMiddle = 0x10, kAlignMeasure = 0xB;

// The RwTexture module in the engine instance (0x960070 + *0x7CE950): +16 the current dictionary, +20 the read
// callback (name, mask) and +24 the "find in the current dictionary" callback; a texture: +4 its dictionary, +8 / +12
// the dictionary list links, +84 the reference count. Error 22 with the names when nothing is found.
inline constexpr u32 kRwEngine = 0x960070u;
inline constexpr u32 kTexModDictionary = 16, kTexModRead = 20, kTexModFind = 24;
inline constexpr u32 kTexDictionary = 4, kTexLinkNext = 8, kTexLinkPrev = 12, kTexRefCount = 84;

}  // namespace finalA

void sub_10A410(EEContext& ctx);  // 0x10A410 (slot, file) -> 1 [bgmChannelStart]: slot < 6 starts the channel record
void sub_195DE0(EEContext& ctx);  // 0x195DE0 () [datInitNewGame]: the whole save data for a new game (The Journey / The Answer)
void sub_1A60D0(EEContext& ctx);  // 0x1A60D0 (parent, model, frames, colour) -> task [K_MdlFade_Create] "rmd fade(kosaka)"
void sub_1A9400(EEContext& ctx);  // 0x1A9400 (task, index) [K_FldCamera_StopFloorEffect]: one effect slot released
void sub_1AB390(EEContext& ctx);  // 0x1AB390 (world, pos, delta; $f12 radius) -> 1 when pushed [K_FldFrame_CollideWorld]
void sub_1ABD20(EEContext& ctx);  // 0x1ABD20 (world, pos, delta, kind; $f12 radius) -> 1 when pushed [K_FldFrame_CollideClump]
void sub_1CF940(EEContext& ctx);  // 0x1CF940 (encounter id | kind << 16, spawn) -> unit [K_FldUnit_CreateShadow] k_unit.c:1072
void sub_1D1640(EEContext& ctx);  // 0x1D1640 (unit, destroy model) [K_FldUnit_ReleaseModel]
void gmRoot_CreateGameRootTask(EEContext& ctx);  // 0x2664C0 (parent) -> task: the "game root" task and its work (gm_root.c:90)
void sub_4D1260(EEContext& ctx);  // 0x4D1260 (name, mask) -> texture [RwTextureRead]: the dictionary first, then the reader
void _sceWakeupThread(EEContext& ctx);   // 0x503090 (thread): syscall 51
void _sceSuspendThread(EEContext& ctx);  // 0x5030D0 (thread): syscall 55
void _sceResumeThread(EEContext& ctx);   // 0x5030F0 (thread): syscall 57
void StartThread(EEContext& ctx);  // 0x5042A0 (thread, argument) -> id / -1: the dormant thread's context prepared, _sceStartThread
void kputs(EEContext& ctx);  // 0x504650 (text): _sceDeci2Call(16, &text)
void scePadInit(EEContext& ctx);  // 0x511138 (mode) -> scePadInit2's result / 0: binds the pad RPC servers, checks padman 4.x
void scePadPortOpen(EEContext& ctx);  // 0x511590 (port, slot, buffer) -> result / 0: the open request to the pad server
void sceMc2CreateSocket(EEContext& ctx);  // 0x513368 (parameters) -> socket / error (finalA::kMc2Err*)
void sub_3B2CB0(EEContext& ctx);  // 0x3B2CB0 (x, y, rgba, kind, font, text, align; $f12 scale) -> width [frFontExDrawString]

}  // namespace p3fes::game
