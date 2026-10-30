// Phase 5 slice fx2: the effect system, second pass -- 154 functions of the effect-type band 0x330000-0x34FFFF that
// fx_types and fx_epl left (docs/ANALYSIS/27_unmapped_bands.md section 6). The bodies are p3fes_handgen's
// (game/include/p3fes/game/hg_cpu.h): register for register and block for block as the recompiled bodies; the
// readability pass (comments, block roles, the named offsets below) changes no statement.
// What is here, by file: fx2_psys.cpp the particle-system types 8..11 (update / scale, rows 0x69C590..) and the
// ribbon effect classes 2 / 15 with their ribbon meshes; fx2_kinds12.cpp effect class 13 and the ring kinds of class
// 12; fx2_kinds10.cpp the spark kinds 1, 2, 4, 5, 6, 8 of class 10 and the class-10 instance allocator;
// fx2_kinds16.cpp the streamer kinds 1 / 2 of class 16 and its allocator; fx2_classes.cpp the sprite class 7, the
// lens flare class 9, the shake object class 21, the screen filters (classes 4 / 5: instance slots, kinds 1..7, the
// quad / cell helpers), the effect-model helpers and the constructors / destructors / clones of fx_epl's four EPL
// kinds.
// Chosen by measuring (a temporary per-function entry counter in the recompiled bodies, never committed): 115
// functions run on the battle / fusion / dorm routes (112 are here: sub_343B60 [k16Streamer2Create], sub_338D60
// [kobj12Ring3Create] and sub_342890 [k16Streamer1Create] are left out, see docs/INTEGRATION_LOG.md); 42 more
// complete the classes they belong to. Names: every function keeps its symbols/functions.json name; a bracketed role
// is a proposal (ADR-0009). Each function takes the register ABI (arguments in $a0.., the result in $v0).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace fx2 {

// [FxPsys] the particle system sub_332070 allocates (one RwMalloc block: header, particles, per-particle state, two
// copies of the type parameters). Type rows 0x69C510 + 16 * type: {update, scale, per-particle state size, parameter
// size}. fx_types / fx_epl call it the "track" / "particle system" (sub_332200 .. sub_332330).
constexpr s32 kPsysType = 0;  // u16 type (row of 0x69C510)
constexpr s32 kPsysCount = 4;  // particles
constexpr s32 kPsysSlots = 8;  // particle slots = count * (cells + 1)
constexpr s32 kPsysFlags = 0xC;  // bit 0: parameters +188 set (particles in world space)
constexpr s32 kPsysFrame = 0x10;  // frames run (sub_332210)
constexpr s32 kPsysEmitAcc = 0x14;  // f32 fractional emission carried to the next frame
constexpr s32 kPsysParticles = 0x18;  // 32-byte particles (FxParticle)
constexpr s32 kPsysState = 0x1C;  // per-particle state of the type (size row +8)
constexpr s32 kPsysParams = 0x20;  // the live parameters (FxPsysParams)
constexpr s32 kPsysBaseParams = 0x24;  // the parameters as created (the scale functions multiply from these)
constexpr s32 kPsysSelf = 0x28;  // the block itself

// [FxPsysParams] the particle-system parameters (the effect file block copied by sub_332070); the common head of the
// types 8..11 (type-specific fields from +200).
constexpr s32 kPpPos = 0;  // vec4 emitter position
constexpr s32 kPpRot = 0x10;  // vec4 emitter rotation (Euler, VU0 matrix sub_357E30)
constexpr s32 kPpLifetime = 0x20;  // emitter lifetime in frames (0 = forever)
constexpr s32 kPpRate = 0x24;  // particles emitted per frame
constexpr s32 kPpRateRand = 0x28;  // f32 rate randomness (rate * (1 - r * rand))
constexpr s32 kPpLayer = 0x54;  // u16 draw layer of the meshes
constexpr s32 kPpScaleRand = 0x6C;  // f32 scale randomness
constexpr s32 kPpSpinRand = 0x98;  // f32 spin randomness
constexpr s32 kPpSpinMode = 0x9C;  // u8: 0 random spin speed, 1 also a random start angle and sign, 2 no spin
constexpr s32 kPpLife = 0xB8;  // particle life in frames
constexpr s32 kPpWorld = 0xBC;  // u8: particles keep the world origin 0x957A80 (Psys flag bit 0)
constexpr s32 kPpBurst = 0xBD;  // u8: emit every particle on frame 0
constexpr s32 kPpCellsX = 0xC0;  // trail cells across
constexpr s32 kPpCellsY = 0xC4;  // trail cells down (cells = X * Y; a slot per cell follows each particle)

// [FxParticle] one 32-byte particle of FxPsys +24.
constexpr s32 kPtPos = 0;  // vec4 position
constexpr s32 kPtAge = 0x10;  // age in frames; -1 free, -2 finished (no re-emission)
constexpr s32 kPtColour = 0x14;  // RGBA
constexpr s32 kPtScale = 0x18;  // f32 size
constexpr s32 kPtSpin = 0x1C;  // f32 rotation

// [FxRibbon] the instance of the effect classes 2 and 15 (56 bytes, sub_332370 / sub_3325D0): a particle system whose
// particles drag ribbons (two strip meshes) and an optional class-1 child object.
constexpr s32 kC2Count = 0;  // ribbons = (lifetime or particle life) * rate, at most 100
constexpr s32 kC2Colour = 4;  // RGBA (class slot 12)
constexpr s32 kC2Scale = 8;  // f32 (class slot 10)
constexpr s32 kC2Head = 0xC;  // 28-byte copy of the effect block head (+0 u16 points per ribbon, +8 colours)
constexpr s32 kC2ChildStart = 0x10;  // frame from which the child object runs (head +4)
constexpr s32 kC2ChildScale = 0x24;  // f32 child draw scale x 10 (head +24)
constexpr s32 kC2Strips = 0x28;  // the ribbon meshes (FxStrips, sub_3330E0)
constexpr s32 kC2Child = 0x2C;  // class-1 child object (sub_326490), or 0
constexpr s32 kC2Psys = 0x30;  // the particle system (sub_332070)
constexpr s32 kC2Alive = 0x34;  // u16, 1 after creation

// [FxStrips] the two ribbon meshes of a class 2 / 15 instance (sub_3330E0: 28 bytes + a u16 per ribbon).
constexpr s32 kStMeshA = 0x10;  // band mesh (sub_323FB0, vertex layout 0x69BCD0)
constexpr s32 kStMeshB = 0x14;  // grid mesh (sub_323E10, 0x69BDE0)
constexpr s32 kStLengths = 0x18;  // u16 points pushed per ribbon (inline at +28)

// [FxMesh] an effect mesh of the layer manager (sub_3233A0 / sub_323240 / sub_323FB0 / sub_323E10, fx_layers).
constexpr s32 kMeshFlags = 0;  // u16: bit 0 additive, bit 2 re-instance after unlock
constexpr s32 kMeshVerts = 8;  // s16 vertex count
constexpr s32 kMeshAtomic = 0x10;  // RpAtomic (+24 its geometry)
constexpr s32 kMeshFrame = 0x14;  // RwFrame
constexpr s32 kMeshColours = 0x28;  // per-vertex-group material colour pointers

// [RpGeometry] RenderWare 3.7 geometry fields the bodies touch (rwGEOMETRYLOCK* flags: 2 vertices, 8 prelight, 0xFF0
// texture coordinates).
constexpr s32 kGeoLockedSinceInst = 0xC;  // u16 lockedSinceLastInst (bit 0 forces re-instancing)
constexpr s32 kGeoPreLit = 0x30;  // RwRGBA *preLitLum
constexpr s32 kGeoTexCoords = 0x34;  // RwTexCoords *texCoords[0]
constexpr s32 kGeoMorph = 0x5C;  // RpMorphTarget * (+20 its vertices)

// [FxEffectDef] the effect record a class create slot receives (fx_types: the block getters sub_3245B0 / sub_3245F0).
constexpr s32 kEfKind = 0xC;  // u16 kind of the class (row of the class kind table)
constexpr s32 kEfBlockBType = 0x1C;  // u16 type of block B (1 frame list, 2 sprite set, 4 texture name, 7 image sequence)
constexpr s32 kEfModelArg = 0x24;  // model create argument (class 26)

// [FxKobj13] the class-13 instance (sub_337A60: 64 bytes + the kind parameters). Kind rows 0x69C5D0 + 24 * kind:
// {init, create, destroy, update, draw, parameter size}; kinds 1, 3, 4 (lightning-like strand meshes, sub_334310 ..
// sub_3377F0, never reached on the replay routes).
constexpr s32 kC13Pos = 0;  // vec4 position (class slot 8)
constexpr s32 kC13Rot = 0x10;  // vec4 rotation (class slot 9)
constexpr s32 kC13Scale = 0x20;  // f32 (class slot 10)
constexpr s32 kC13Colour = 0x24;  // RGBA (class slot 12)
constexpr s32 kC13Frame = 0x28;  // frames updated
constexpr s32 kC13Kind = 0x2C;  // kind (row of 0x69C5D0)
constexpr s32 kC13Obj = 0x30;  // the kind object (row +4 create)
constexpr s32 kC13Params = 0x34;  // the kind parameters (inline at +64)

// [FxKobj12] the class-12 instance (sub_3393D0: 80 bytes + the kind parameters; fx_types' kobj12). Kind rows 0x69C650
// + 24 * kind: {init, create, destroy, update, draw, parameter size}: kind 1 a flat ring (sub_337E10 .. sub_338360),
// kind 2 a ring of class-12 kind-1 sub-instances (sub_338530 .. sub_338AC0), kind 3 a cone / fan (sub_338CE0 ..
// sub_339200).
constexpr s32 kC12Pos = 0;  // vec4 position
constexpr s32 kC12Rot = 0x10;  // vec4 rotation
constexpr s32 kC12Scale = 0x20;  // vec4 scale (1, 1, 1, 1 from 0x69C4A0)
constexpr s32 kC12Colour = 0x30;  // RGBA
constexpr s32 kC12Frame = 0x34;  // frames updated
constexpr s32 kC12Kind = 0x38;  // kind (row of 0x69C650)
constexpr s32 kC12Obj = 0x3C;  // the kind object
constexpr s32 kC12Params = 0x40;  // the kind parameters (inline at +80)

// [FxRingParams] the parameters of the class-12 ring kinds 1 / 3 (kind 1 has its speed block 4 bytes later than kind
// 3).
constexpr s32 kRpColourCurve = 0x24;  // the colour track sampled by sub_32A120
constexpr s32 kRpLayer = 0x28;  // u16 draw layer
constexpr s32 kRpLifetime = 0x34;  // frames (0 = forever)
constexpr s32 kRpSegments = 0x38;  // ring segments (at least 3)
constexpr s32 kRpAdditive = 0x3C;  // u8 additive blending (mesh flag bit 0)
constexpr s32 kRpRadius = 0x40;  // f32 start radius
constexpr s32 kRpColourA = 0x44;  // RGBA of the inner vertices
constexpr s32 kRpColourB = 0x48;  // RGBA of the middle vertices
constexpr s32 kRpColourC = 0x4C;  // RGBA of the outer vertices
constexpr s32 kRpWidth0 = 0x50;  // f32 band widths: inner
constexpr s32 kRpWidth1 = 0x54;  // f32 middle
constexpr s32 kRpWidth2 = 0x58;  // f32 outer

// [FxSparkParams] the parameters of the class-10 kinds (the common head; kind-specific random ranges from +96). Every
// kind is a set of mesh particles ("sparks": streaks, quads or textured sprites) re-emitted over the effect's life.
constexpr s32 kSpColourCurve = 0x24;  // the colour track sampled by sub_32A120
constexpr s32 kSpLayer = 0x28;  // u16 draw layer
constexpr s32 kSpLifetime = 0x34;  // frames (0 = forever)
constexpr s32 kSpCount = 0x38;  // particles (records of the kind object)
constexpr s32 kSpFadeIn = 0x44;  // f32 fraction of a particle's life fading in
constexpr s32 kSpFadeOut = 0x48;  // f32 fraction fading out
constexpr s32 kSpLife = 0x4C;  // particle life in frames
constexpr s32 kSpRespawn = 0x50;  // frames between re-emissions
constexpr s32 kSpMode = 0x54;  // u8 emission mode
constexpr s32 kSpOnce = 0x55;  // u8: emit on frame 0 only
constexpr s32 kSpAdditive = 0x56;  // u8 additive blending (mesh flag bit 0)
constexpr s32 kSpColourA = 0x58;  // RGB (24 bits) at birth
constexpr s32 kSpColourB = 0x5C;  // RGB at death

// [FxSparkSet] the kind object of the class-10 / class-16 kinds (one RwMalloc block: 16 bytes + the records).
constexpr s32 kKoRecords = 0;  // the per-particle records (inline at +16)
constexpr s32 kKoMesh = 4;  // the particles' mesh (FxMesh)
constexpr s32 kKoBlock = 8;  // the block itself (freed by the destroy slot)

// [FxStreamerParams] the parameters of the class-16 kinds 1 / 2 (textured streamers: strands of points that trail
// behind moving heads).
constexpr s32 kStmColourCurve = 0x24;  // the colour track sampled by sub_32A120 for the whole effect
constexpr s32 kStmLayer = 0x28;  // u16 draw layer
constexpr s32 kStmLifetime = 0x34;  // frames (0 = forever)
constexpr s32 kStmCount = 0x38;  // strands (records of 48 bytes)
constexpr s32 kStmStrandCurve = 0x3C;  // the per-strand colour track (sampled at +96)
constexpr s32 kStmFadeIn = 0x78;  // f32 fraction of the points fading in along a strand
constexpr s32 kStmFadeOut = 0x7C;  // f32 fraction fading out
constexpr s32 kStmLife = 0x80;  // strand life in frames
constexpr s32 kStmRespawn = 0x84;  // frames between re-emissions
constexpr s32 kStmKeep = 0x88;  // u8: keep the vertices of a dead strand
constexpr s32 kStmPoints = 0x8C;  // segments per strand (at least 3; points = segments + 1)
constexpr s32 kStmTexLength = 0x90;  // f32 texture v length of a strand
constexpr s32 kStmOnce = 0xB8;  // u8: emit on frame 0 only
constexpr s32 kStmAdditive = 0xB9;  // u8 additive blending

// [FxSprite] the class-7 instance (sub_3461A0: 212 bytes): one camera-facing textured quad with colour / size /
// rotation curves, animated by a sprite player or an image sequence.
constexpr s32 kC7Pos = 0;  // vec4 position
constexpr s32 kC7Rot = 0x10;  // vec4 rotation
constexpr s32 kC7Scale = 0x20;  // f32 scale
constexpr s32 kC7Colour = 0x24;  // RGBA
constexpr s32 kC7Kind = 0x28;  // the effect kind (+12)
constexpr s32 kC7Frame = 0x2C;  // frames run (slot 1 counts it)
constexpr s32 kC7Def = 0x30;  // 152-byte copy of block A: +48 colour track, +100 size curve, +144 rotation curve
constexpr s32 kC7Loop = 0x74;  // u8: restart after the duration
constexpr s32 kC7Duration = 0xBC;  // frames of the curves
constexpr s32 kC7Size = 0xC0;  // f32 base size
constexpr s32 kC7Mesh = 0xC8;  // the quad mesh (sub_3233A0: 1 quad, layout 0x69BDC8)
constexpr s32 kC7ImageSeq = 0xCC;  // image sequence (block B type 7, sub_322DC0)
constexpr s32 kC7Player = 0xD0;  // sprite player (block B type 2, sub_322530)

// [FxFlare] the class-9 instance (sub_347170: 92 bytes): a lens flare of 13 screen-space elements.
constexpr s32 kC9Pos = 0;  // vec4 the light position
constexpr s32 kC9Frame = 0x10;  // frames run
constexpr s32 kC9Colour = 0x14;  // RGBA
constexpr s32 kC9Def = 0x18;  // 64-byte copy of block A: +24 colour track, +60 colour curve, +76 intensity, +80 duration, +84 u8 style
constexpr s32 kC9Mesh = 0x58;  // the 13-quad mesh (sub_323E10, layout 0x69BDC8)

// [FxFilter] the instance of the screen-filter classes 4 / 5 (sub_34B1A0 / sub_34B6B0: 48 bytes + the kind
// parameters). Kind rows 0x69CB90 / 0x69CC50 + 24 * kind: {create, destroy, update, draw, u8 uses a texture, size}.
constexpr s32 kFltColour = 0x10;  // RGBA
constexpr s32 kFltScale = 0x14;  // f32
constexpr s32 kFltKind = 0x18;  // kind
constexpr s32 kFltFrame = 0x1C;  // frames run
constexpr s32 kFltObj = 0x20;  // the kind object (row +0 create), or 0
constexpr s32 kFltParams = 0x24;  // the kind parameters (inline at +48; FxFilterParams)
constexpr s32 kFltTexRef = 0x28;  // texture reference {type, count, texture} (sub_34BBC0), or 0

// [FxFilterParams] the parameters of a screen-filter kind (the kinds' live output from +192).
constexpr s32 kFpColourCurve = 0x24;  // the colour track sampled by sub_32A120
constexpr s32 kFpLayer = 0x28;  // u16 layer / blend word
constexpr s32 kFpCurveA = 0x34;  // first float curve (sub_32A540)
constexpr s32 kFpCurveB = 0x60;  // second float curve
constexpr s32 kFpSizeCurve = 0x8C;  // size curve (kinds 2, 3, 4)
constexpr s32 kFpDuration = 0xB8;  // frames (0 = hold frame 0)
constexpr s32 kFpCentred = 0xBC;  // u8: centred on the screen, else at the projected effect position (sub_329BA0)
constexpr s32 kFpOut = 0xC0;  // the kind's output for the draw (colour, rectangle, scale, angle; cells for kinds 3, 4, 7)

// [EplModelObj] fx_epl's kind 1 object (class 26 / EPL row 0x69C368: 160 bytes).
constexpr s32 kE1Scale = 0x20;  // f32 scale
constexpr s32 kE1Colour = 0x28;  // RGBA
constexpr s32 kE1Def = 0x2C;  // 104-byte copy of block A
constexpr s32 kE1Model = 0x94;  // the model (sub_316BD0)
constexpr s32 kE1Age = 0x98;  // age

// [EplNodeModelObj] fx_epl's kind 2 object (EPL row 0x69C39C: 164 bytes).
constexpr s32 kE2Scale = 0x20;  // f32 scale
constexpr s32 kE2Colour = 0x24;  // RGBA
constexpr s32 kE2Frames = 0x28;  // frames of the model (sub_318FC0)
constexpr s32 kE2Def = 0x30;  // 104-byte copy of block A (when the effect kind is 0)
constexpr s32 kE2Lifetime = 0x90;  // frames (0 = forever: the animation loops)
constexpr s32 kE2Nodes = 0x98;  // one effect node per model frame
constexpr s32 kE2NodeBlock = 0x9C;  // the node pointer block (freed by the destroy)
constexpr s32 kE2Model = 0xA0;  // the model

// [EplClumpParticleObj] fx_epl's kind 3 object (EPL row 0x69C3D0: 104 bytes).
constexpr s32 kE3Count = 0;  // particles = (lifetime or life) * rate, at most 100
constexpr s32 kE3Colour = 4;  // RGBA
constexpr s32 kE3Scale = 8;  // f32
constexpr s32 kE3BlockBType = 0xC;  // u16 type of block B (3 = a clump stream)
constexpr s32 kE3Def = 0x10;  // 68-byte copy of block A
constexpr s32 kE3Clump = 0x54;  // RpClump, or 0
constexpr s32 kE3Psys = 0x58;  // the particle system
constexpr s32 kE3Records = 0x5C;  // 24-byte particle records
constexpr s32 kE3RecordBlock = 0x60;  // their block

// [EplTexParticleObj] fx_epl's kind 4 object (EPL row 0x69C404: 112 bytes).
constexpr s32 kE4Count = 0;  // particles, at most 100
constexpr s32 kE4Colour = 4;  // RGBA
constexpr s32 kE4Scale = 8;  // f32
constexpr s32 kE4Def = 0xC;  // 72-byte copy of block A
constexpr s32 kE4ScrollU = 0x54;  // f32 scroll position
constexpr s32 kE4ScrollV = 0x58;  // f32 scroll position
constexpr s32 kE4Psys = 0x5C;  // the particle system
constexpr s32 kE4Texture = 0x60;  // RwTexture, or 0
constexpr s32 kE4Records = 0x64;  // 28-byte particle records
constexpr s32 kE4RecordBlock = 0x68;  // their block

}  // namespace fx2

void sub_330100(EEContext& ctx);  // 0x330100 [fxPsysScale8] type 8: live parameters = base x $f12
void sub_330190(EEContext& ctx);  // 0x330190 [fxPsysUpdate9] type 9: emit and move the particles (spray along random directions)
void sub_330BB0(EEContext& ctx);  // 0x330BB0 [fxPsysScale9] type 9: live parameters = base x $f12
void sub_330C40(EEContext& ctx);  // 0x330C40 [fxPsysUpdate10] type 10: emit and move the particles (rings / spirals around the emitter)
void sub_3315D0(EEContext& ctx);  // 0x3315D0 [fxPsysScale10] type 10: live parameters = base x $f12
void sub_331FD0(EEContext& ctx);  // 0x331FD0 [fxPsysScale11] type 11: live parameters = base x $f12
void sub_332070(EEContext& ctx);  // 0x332070 [fxPsysCreate] particle system of a type: header, particles, state, two parameter copies
void sub_332370(EEContext& ctx);  // 0x332370 [fxRibbonCreate] class 2 slot 0: the instance of a ribbon effect
void sub_332470(EEContext& ctx);  // 0x332470 [fxRibbonSetChild] the class-1 child of a ribbon from block B, by its type
void sub_3325D0(EEContext& ctx);  // 0x3325D0 [fxRibbonCreate15] class 15 slot 0: a ribbon effect with a child object
void sub_332700(EEContext& ctx);  // 0x332700 [fxRibbonDestroy] class 2 / 15 slot 4: child, meshes, particle system, instance
void sub_332780(EEContext& ctx);  // 0x332780 [fxRibbonClone] class 2 slot 5: a copy of a ribbon instance
void sub_332880(EEContext& ctx);  // 0x332880 [fxRibbonClone15] class 15 slot 5: a copy of a ribbon instance and its child
void sub_332990(EEContext& ctx);  // 0x332990 [fxRibbonCopyChild] copy a ribbon's child object (class 15 clone)
void sub_332A30(EEContext& ctx);  // 0x332A30 [fxRibbonSetHead] head copy and ribbon meshes of a ribbon instance
void sub_332AC0(EEContext& ctx);  // 0x332AC0 [fxRibbonSetPsys] the particle system of a ribbon instance
void sub_332B60(EEContext& ctx);  // 0x332B60 [fxRibbonStep] class 2 / 15 slot 2: one frame of the particle system and the ribbons
void sub_332E10(EEContext& ctx);  // 0x332E10 [fxRibbonDraw] class 2 / 15 slot 3: place and queue the ribbon meshes
void sub_332F10(EEContext& ctx);  // 0x332F10 [fxRibbonUpdate] class 2 / 15 slot 1: step (sub_332B60), then draw
void sub_3330E0(EEContext& ctx);  // 0x3330E0 [fxStripsCreate] the two ribbon meshes for n ribbons
void sub_333300(EEContext& ctx);  // 0x333300 [fxStripsSetColour] material colour of ribbon i in both meshes
void sub_333420(EEContext& ctx);  // 0x333420 [fxStripsSetGradient] prelight colours of the ribbon meshes from two key colours
void sub_333970(EEContext& ctx);  // 0x333970 [fxStripsPush] push a point into ribbon i and rebuild its band (VU0)
void sub_3341C0(EEContext& ctx);  // 0x3341C0 [fxStripsLock] camera position, lock both ribbon geometries
void sub_334220(EEContext& ctx);  // 0x334220 [fxStripsUnlock] unlock both ribbon geometries, re-instance when flagged
void sub_337A60(EEContext& ctx);  // 0x337A60 [kobj13Create] a class-13 instance of a kind from its parameters
void sub_337B70(EEContext& ctx);  // 0x337B70 [kobj13New] class 13 slot 0: kobj13Create(kind +12, block A)
void sub_337BB0(EEContext& ctx);  // 0x337BB0 [kobj13Destroy] class 13 slot 4: kind destroy on the object, free
void sub_337C10(EEContext& ctx);  // 0x337C10 [kobj13Clone] class 13 slot 5: a new instance of the same kind and parameters
void sub_337C40(EEContext& ctx);  // 0x337C40 [kobj13Restart] class 13 slot 7: kind init again, frame = 0
void sub_337C90(EEContext& ctx);  // 0x337C90 [kobj13Step] class 13 slot 2: kind update, ++frame
void sub_337CF0(EEContext& ctx);  // 0x337CF0 [kobj13Draw] class 13 slot 3: kind draw once a frame has run
void sub_337D40(EEContext& ctx);  // 0x337D40 [kobj13Update] class 13 slot 1: kind update, ++frame, kind draw
void sub_337DD0(EEContext& ctx);  // 0x337DD0 [kobj13SetPos] class 13 slot 8: position = *$a1 (128 bits)
void sub_337DE0(EEContext& ctx);  // 0x337DE0 [kobj13SetRot] class 13 slot 9: rotation = *$a1 (128 bits)
void sub_337DF0(EEContext& ctx);  // 0x337DF0 [kobj13SetColour] class 13 slot 12: colour +36 = $a1
void sub_337E00(EEContext& ctx);  // 0x337E00 [kobj13SetScale] class 13 slot 10: scale +32 = $f12
void sub_337E90(EEContext& ctx);  // 0x337E90 [kobj12Ring1Create] class 12 kind 1 slot 1: the ring mesh
void sub_337FD0(EEContext& ctx);  // 0x337FD0 [kobj12Ring1Update] class 12 kind 1 slot 3: the ring's vertices for this frame
void sub_338360(EEContext& ctx);  // 0x338360 [kobj12Ring1Draw] class 12 kind 1 slot 4: colour, place and queue the ring
void sub_338EA0(EEContext& ctx);  // 0x338EA0 [kobj12Ring3Update] class 12 kind 3 slot 3: the cone's vertices for this frame
void sub_339200(EEContext& ctx);  // 0x339200 [kobj12Ring3Draw] class 12 kind 3 slot 4: colour, place and queue (= sub_338360)
void sub_3393D0(EEContext& ctx);  // 0x3393D0 [kobj12Create] a class-12 instance of a kind from its parameters
void sub_3397D0(EEContext& ctx);  // 0x3397D0 [k10Streak1Init] kind 1 slot 0: clear the vertices, free every record
void sub_3398C0(EEContext& ctx);  // 0x3398C0 [k10Streak1Create] kind 1 slot 1: records (24 bytes) and a 3 x 5 grid mesh
void sub_3399A0(EEContext& ctx);  // 0x3399A0 [k10Streak1Update] kind 1 slot 4: emit / age the streaks, rebuild the vertices
void sub_33A220(EEContext& ctx);  // 0x33A220 [k10Streak1Draw] kind 1 slot 5: colour, place and queue the mesh
void sub_33A3E0(EEContext& ctx);  // 0x33A3E0 [k10Streak2Init] kind 2 slot 0: clear the vertices, free every record
void sub_33A4D0(EEContext& ctx);  // 0x33A4D0 [k10Streak2Create] kind 2 slot 1: records (28 bytes) and a 12 x 13 grid mesh
void sub_33A560(EEContext& ctx);  // 0x33A560 [k10Streak2Destroy] kind 2 slot 2: destroy the mesh, free the block
void sub_33A5B0(EEContext& ctx);  // 0x33A5B0 [k10Streak2Update] kind 2 slot 4: emit / age the streaks, rebuild the vertices
void sub_33AF10(EEContext& ctx);  // 0x33AF10 [k10Streak2Draw] kind 2 slot 5: colour, place and queue the mesh
void sub_33BDA0(EEContext& ctx);  // 0x33BDA0 [k10Sprite4Init] kind 4 slot 0: clear the vertices, free every record
void sub_33BE90(EEContext& ctx);  // 0x33BE90 [k10Sprite4TexCoords] kind 4: the two-frame texture coordinates of every quad
void sub_33BFA0(EEContext& ctx);  // 0x33BFA0 [k10Sprite4Create] kind 4 slot 1: records and a textured quad mesh
void sub_33C0A0(EEContext& ctx);  // 0x33C0A0 [k10Sprite4Clone] kind 4 slot 3: a copy of the kind object
void sub_33C150(EEContext& ctx);  // 0x33C150 [k10Sprite4Destroy] kind 4 slot 2: destroy the mesh, free the block
void sub_33C1A0(EEContext& ctx);  // 0x33C1A0 [k10Sprite4Update] kind 4 slot 4: emit / age the sprites, rebuild the quads
void sub_33C960(EEContext& ctx);  // 0x33C960 [k10Sprite4Draw] kind 4 slot 5: colour, place and queue the mesh
void sub_33CB20(EEContext& ctx);  // 0x33CB20 [k10Sprite5Init] kind 5 slot 0: clear the vertices, free every record
void sub_33CC10(EEContext& ctx);  // 0x33CC10 [k10Sprite5TexCoords] kind 5: the two-frame texture coordinates of every quad
void sub_33CD20(EEContext& ctx);  // 0x33CD20 [k10Sprite5Create] kind 5 slot 1: records and a textured quad mesh
void sub_33CE10(EEContext& ctx);  // 0x33CE10 [k10Sprite5Clone] kind 5 slot 3: a copy of the kind object
void sub_33CEB0(EEContext& ctx);  // 0x33CEB0 [k10Sprite5Destroy] kind 5 slot 2: destroy the mesh, free the block
void sub_33CF00(EEContext& ctx);  // 0x33CF00 [k10Sprite5Update] kind 5 slot 4: emit / age the sprites, rebuild the quads
void sub_33D6D0(EEContext& ctx);  // 0x33D6D0 [k10Sprite5Draw] kind 5 slot 5: colour, place and queue the mesh
void sub_33D890(EEContext& ctx);  // 0x33D890 [k10Sprite6Init] kind 6 slot 0: clear the vertices, free every record
void sub_33D980(EEContext& ctx);  // 0x33D980 [k10Sprite6TexCoords] kind 6: the two-frame texture coordinates of every quad
void sub_33DA90(EEContext& ctx);  // 0x33DA90 [k10Sprite6Create] kind 6 slot 1: records and a textured quad mesh
void sub_33DB80(EEContext& ctx);  // 0x33DB80 [k10Sprite6Clone] kind 6 slot 3: a copy of the kind object
void sub_33DC20(EEContext& ctx);  // 0x33DC20 [k10Sprite6Destroy] kind 6 slot 2: destroy the mesh, free the block
void sub_33DC70(EEContext& ctx);  // 0x33DC70 [k10Sprite6Update] kind 6 slot 4: emit / age the sprites (size and speed ramps), rebuild the quads
void sub_33E540(EEContext& ctx);  // 0x33E540 [k10Sprite6Draw] kind 6 slot 5: colour, place and queue the mesh
void sub_33F4A0(EEContext& ctx);  // 0x33F4A0 [k10Sprite8Init] kind 8 slot 0: clear the vertices, free every record
void sub_33F590(EEContext& ctx);  // 0x33F590 [k10Sprite8TexCoords] kind 8: the two-frame texture coordinates of every quad
void sub_33F6A0(EEContext& ctx);  // 0x33F6A0 [k10Sprite8Create] kind 8 slot 1: records and a textured quad mesh
void sub_33F780(EEContext& ctx);  // 0x33F780 [k10Sprite8Clone] kind 8 slot 3: a copy of the kind object
void sub_33F810(EEContext& ctx);  // 0x33F810 [k10Sprite8Destroy] kind 8 slot 2: destroy the mesh, free the block
void sub_33F860(EEContext& ctx);  // 0x33F860 [k10Sprite8Update] kind 8 slot 4: emit / age the sprites, rebuild the quads
void sub_340100(EEContext& ctx);  // 0x340100 [k10Sprite8Draw] kind 8 slot 5: colour, place and queue the mesh
void sub_341F10(EEContext& ctx);  // 0x341F10 [kobj10Alloc] a class-10 instance with a copy of its kind parameters
void sub_342480(EEContext& ctx);  // 0x342480 [k16Streamer1Init] kind 1 slot 0: tint every strand, free every record
void sub_342550(EEContext& ctx);  // 0x342550 [k16Streamer1Geometry] kind 1: strand colours (alpha ramp) and texture coordinates
void sub_342990(EEContext& ctx);  // 0x342990 [k16Streamer1Clone] kind 1 slot 3: a copy of the kind object
void sub_342A90(EEContext& ctx);  // 0x342A90 [k16Streamer1Update] kind 1 slot 4: emit / age the strands, trail their points
void sub_343410(EEContext& ctx);  // 0x343410 [k16Streamer1Draw] kind 1 slot 5: strand colours, matrix, queue
void sub_343790(EEContext& ctx);  // 0x343790 [k16Streamer2Init] kind 2 slot 0: tint every strand, free every record
void sub_343860(EEContext& ctx);  // 0x343860 [k16Streamer2Geometry] kind 2: strand colours (alpha ramp) and texture coordinates
void sub_343C60(EEContext& ctx);  // 0x343C60 [k16Streamer2Clone] kind 2 slot 3: a copy of the kind object
void sub_343D10(EEContext& ctx);  // 0x343D10 [k16Streamer2Destroy] kind 2 slot 2: destroy the mesh, free the block
void sub_343D60(EEContext& ctx);  // 0x343D60 [k16Streamer2Update] kind 2 slot 4: emit / age the strands, trail their points
void sub_344720(EEContext& ctx);  // 0x344720 [k16Streamer2Draw] kind 2 slot 5: strand colours, matrix, queue
void sub_345CF0(EEContext& ctx);  // 0x345CF0 [kobj16Alloc] a class-16 instance with a copy of its kind parameters
void sub_3461A0(EEContext& ctx);  // 0x3461A0 [fxSpriteCreate] class 7 slot 0: the sprite quad, its curves and its animation
void sub_346350(EEContext& ctx);  // 0x346350 [fxSpriteDestroy] class 7 slot 4: image sequence, sprite player, mesh, instance
void sub_3463C0(EEContext& ctx);  // 0x3463C0 [fxSpriteClone] class 7 slot 5: a copy of a sprite instance
void sub_346460(EEContext& ctx);  // 0x346460 [fxSpriteCopyAnim] class 7 slot 6: copy the sprite player / image sequence of another instance
void sub_346530(EEContext& ctx);  // 0x346530 [fxSpriteDraw] class 7 slot 3: curves, animation frame, quad vertices, queue
void sub_347100(EEContext& ctx);  // 0x347100 [fxSpriteUpdate] class 7 slot 1: ++frame, then draw (sub_346530)
void sub_347170(EEContext& ctx);  // 0x347170 [fxFlareCreate] a lens-flare instance from its definition
void sub_3472D0(EEContext& ctx);  // 0x3472D0 [fxFlareNew] class 9 slot 0: sub_347170(block A)
void sub_347350(EEContext& ctx);  // 0x347350 [fxFlareClone] class 9 slot 5: sub_347170(the source's definition +24)
void sub_3473B0(EEContext& ctx);  // 0x3473B0 [fxFlareDraw] class 9 slot 3: project the light, place the 13 flare elements, queue
void sub_347CB0(EEContext& ctx);  // 0x347CB0 [fxFlareUpdate] class 9 slot 1: ++frame, then draw (sub_3473B0)
void sub_347FC0(EEContext& ctx);  // 0x347FC0 [fxShakeObjCreate] class 21 slot 0: frame 0 and a copy of the 16-byte shake record
void sub_348030(EEContext& ctx);  // 0x348030 [fxShakeObjDestroy] class 21 slot 4: camera frame back, shake off, free
void sub_348090(EEContext& ctx);  // 0x348090 [fxShakeObjClone] class 21 slot 5: frame 0 and a copy of the source's shake record
void sub_348340(EEContext& ctx);  // 0x348340 [fltQuadUvRotated] Im2D quad of a filter rectangle, texture coordinates from the screen, rotated
void sub_348760(EEContext& ctx);  // 0x348760 [fltQuadUvFull] Im2D quad of a filter rectangle with the whole texture
void sub_348BD0(EEContext& ctx);  // 0x348BD0 [fltQuadPlain] Im2D quad of a filter rectangle, no texture coordinates
void sub_348F30(EEContext& ctx);  // 0x348F30 [fltCellRespawn3] filter kind 3: a sparkle cell at a random place around the centre
void sub_349260(EEContext& ctx);  // 0x349260 [fltCellRespawn7] filter kind 7: a cell at a random screen place
void sub_349450(EEContext& ctx);  // 0x349450 [fltCellsUpdate7] filter kind 7: count down, respawn, pulse every cell
void sub_349870(EEContext& ctx);  // 0x349870 [flt4Kind1Update] class 4 kind 1: full-screen tint colour and its two curves
void sub_349AF0(EEContext& ctx);  // 0x349AF0 [flt4Kind2Update] class 4 kind 2: a tinted disc at the effect position or the screen centre
void sub_349ED0(EEContext& ctx);  // 0x349ED0 [flt4Kind3Create] class 4 kind 3: the sparkle cells (52 bytes each)
void sub_349FA0(EEContext& ctx);  // 0x349FA0 [flt4Kind3Destroy] class 4 kind 3: free the cells
void sub_34A1D0(EEContext& ctx);  // 0x34A1D0 [flt4Kind3Draw] class 4 kind 3: the visible sparkle cells as quads
void sub_34A280(EEContext& ctx);  // 0x34A280 [flt4Kind4Create] class 4 kind 4: the cells, staggered phases
void sub_34A340(EEContext& ctx);  // 0x34A340 [flt4Kind4Destroy] class 4 kind 4: free the cells
void sub_34A590(EEContext& ctx);  // 0x34A590 [flt4Kind4Draw] class 4 kind 4: the started cells as quads
void sub_34A8C0(EEContext& ctx);  // 0x34A8C0 [flt4Kind7Create] class 4 kind 7: the cells (52 bytes each)
void sub_34A990(EEContext& ctx);  // 0x34A990 [flt4Kind7Destroy] class 4 kind 7: free the cells
void sub_34A9C0(EEContext& ctx);  // 0x34A9C0 [flt4Kind7Update] class 4 kind 7: colour, scale, angle, then the cells
void sub_34ABC0(EEContext& ctx);  // 0x34ABC0 [flt4Kind7Draw] class 4 kind 7: the active cells as quads
void sub_34AC70(EEContext& ctx);  // 0x34AC70 [flt5Kind1Update] class 5 kind 1: full-screen colour
void sub_34B1A0(EEContext& ctx);  // 0x34B1A0 [fltCreate4] class 4 slot 0: a screen-filter instance of the effect's kind
void sub_34B320(EEContext& ctx);  // 0x34B320 [fltDestroy4] class 4 slot 4: kind destroy, texture reference, instance
void sub_34B3A0(EEContext& ctx);  // 0x34B3A0 [fltClone4] class 4 slot 5: a copy of a filter instance
void sub_34B600(EEContext& ctx);  // 0x34B600 [fltUpdate4] class 4 slot 1: kind update, ++frame, queue on the filter layer
void sub_34B6B0(EEContext& ctx);  // 0x34B6B0 [fltCreate5] class 5 slot 0: a screen-filter instance (class 5 kinds)
void sub_34B830(EEContext& ctx);  // 0x34B830 [fltDestroy5] class 5 slot 4: kind destroy, texture reference, instance
void sub_34B8B0(EEContext& ctx);  // 0x34B8B0 [fltClone5] class 5 slot 5: a copy of a filter instance
void sub_34BB10(EEContext& ctx);  // 0x34BB10 [fltUpdate5] class 5 slot 1: kind update, ++frame, queue (sub_3211D0)
void sub_34BBC0(EEContext& ctx);  // 0x34BBC0 [fltTexRefCreate] a texture reference {type, count 1, texture} from block B
void sub_34BC80(EEContext& ctx);  // 0x34BC80 [fltTexRefRelease] release a texture reference (destroy the texture unless managed)
void sub_34BD60(EEContext& ctx);  // 0x34BD60 [eplModelReset] animation 0 of a model at time 0, flag 2 cleared
void sub_34BDF0(EEContext& ctx);  // 0x34BDF0 [eplModelCreate] a model with a fresh id of group 6, reset
void sub_34BEF0(EEContext& ctx);  // 0x34BEF0 [eplModelDestroy] sub_3174E0(model)
void sub_34BF10(EEContext& ctx);  // 0x34BF10 [eplModelCopy] a model of the same file (+212 / +214), reset
void sub_34BFC0(EEContext& ctx);  // 0x34BFC0 [eplModelObjCreate] class 26 / EPL kind 1 slot 0: the model object
void sub_34C160(EEContext& ctx);  // 0x34C160 [eplModelObjDestroy] class 26 / EPL kind 1 slot 4: model, object
void sub_34C1B0(EEContext& ctx);  // 0x34C1B0 [eplModelObjClone] class 26 / EPL kind 1 slot 5: a copy with its own model
void sub_34C670(EEContext& ctx);  // 0x34C670 [eplNodeModelCreate] EPL kind 2 slot 0: a model whose frames carry effect nodes
void sub_34C890(EEContext& ctx);  // 0x34C890 [eplNodeModelDestroy] EPL kind 2 slot 4: model, nodes, object
void sub_34C9B0(EEContext& ctx);  // 0x34C9B0 [eplNodeModelCopy] EPL kind 2 slot 6: model and nodes like another object's
void sub_34D510(EEContext& ctx);  // 0x34D510 [eplClumpPsysCreate] EPL kind 3 slot 0: particle system, records and clump
void sub_34D670(EEContext& ctx);  // 0x34D670 [eplClumpPsysDestroy] EPL kind 3 slot 4: particle system, records, clump, object
void sub_34D6F0(EEContext& ctx);  // 0x34D6F0 [eplClumpPsysClone] EPL kind 3 slot 5: a copy of the object
void sub_34D8A0(EEContext& ctx);  // 0x34D8A0 [eplClumpPsysSetSystem] EPL kind 3: a new particle system and its 24-byte records
void sub_34E4C0(EEContext& ctx);  // 0x34E4C0 [eplTexPsysCreate] EPL kind 4 slot 0: particle system, records and texture
void sub_34E610(EEContext& ctx);  // 0x34E610 [eplTexPsysDestroy] EPL kind 4 slot 4: texture, particle system, records, object
void sub_34E690(EEContext& ctx);  // 0x34E690 [eplTexPsysClone] EPL kind 4 slot 5: a copy of the object
void sub_34E820(EEContext& ctx);  // 0x34E820 [eplTexPsysSetSystem] EPL kind 4: a new particle system and its 28-byte records

}  // namespace p3fes::game
