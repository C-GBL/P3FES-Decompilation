// The model manager band 0x311310-0x320000 (slice `models`, game/src/model/models.cpp): the register-ABI bodies
// (arguments in $a0.., the result in $v0) and the record layouts the bodies name (named offsets, from the bodies'
// own instructions; tools/ours/types/deltas/models.json feeds them back to type recovery).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace mdl {

// The RW memory functions (device slots, as every slice reads them)
// 0x960000 + 376 = 0x960178: RwMalloc(size, hint) -- hint 0x40000 everywhere here
inline constexpr s32 kRwMallocSlot = 376;
inline constexpr s32 kRwFreeSlot = 380;       // 0x960000 + 380 = 0x96017C: RwFree(ptr)
// MdlModel: the model instance record, 1,072 bytes (sub_316690 allocates and initialises it)
inline constexpr s32 kMdlSize = 1072;         // RwMalloc(1072, 0x40000), zeroed
// gMdlLists 0x9571F0: one list head per model kind (sub_31B470 clears 48 bytes)
inline constexpr s32 kMdlListCount = 12;
// RwMatrix: the placement (identity at creation); sub_318B60 hands out its address
inline constexpr s32 kMdlPlace = 0;
// RwMatrix: the animation set entry's root matrix (sub_3182D0 copies it; identity otherwise)
inline constexpr s32 kMdlRootOffset = 64;
inline constexpr s32 kMdlScale = 128;         // f32[3] scale (1, 1, 1); sub_318A90
// RwMatrix: the parent's placement when attached (sub_3197C0 copies it into each child)
inline constexpr s32 kMdlParentMatrix = 144;
inline constexpr s32 kMdlColour = 208;        // u8[4] rgba (255 x 4); sub_318AD0 / sub_318B00
// u16: the model kind, the list index -- in the replay snapshots 1 the party (ids 1, 2, 5), 2 enemies, 3 / 4 battle /
// map objects, 5 NPCs, 7 / 10 the party's weapons (children); 1 and 2 are stored packed (sub_31D4F0)
inline constexpr s32 kMdlType = 212;
inline constexpr s32 kMdlId = 214;            // u16: the model number within the kind
// u16 flags (0x118 at creation): 0x1 / 0x20 game-side toggles (sub_319010..70), 0x4 attached, 0x1000 ready, 0x2000
// waiting to clone a loaded twin, 0x4000 synchronous load, 0x8000 is a child
inline constexpr s32 kMdlFlags = 216;
inline constexpr s32 kMdlClump = 220;         // RpClump* (0 until loaded)
inline constexpr s32 kMdlAtomicList = 224;    // sub_1A7570(clump) after set-up, released with sub_1A7710
inline constexpr s32 kMdl228 = 228;           // s32 = 68 at creation
inline constexpr s32 kMdl232 = 232;           // s32 = 464891 (0x717FB) at creation
// MdlAnimSlot[4], 156 bytes each: slot 0 the body, 1..3 further hierarchies
inline constexpr s32 kMdlSlots = 236;
inline constexpr s32 kMdlSlotCount = 4;
inline constexpr s32 kSlotSize = 156;
// {set, current} of the slot-0 animations of the 0x320xxx animation code (sub_313CA0)
inline constexpr s32 kMdlAltAnim = 860;
// the material (UV) animation record: slot-like (+2 done, +4 index, +8 speed, +12/+16 time, +24 its set = model +892);
// sub_3143C0 / sub_314730
inline constexpr s32 kMdlMatAnim = 868;
inline constexpr s32 kMatAnimSet = 24;        // the material-animation set inside kMdlMatAnim
// MdlAttach[5], 12 bytes each: +0 u8 flags (bit 0 used), +4 child model, +8 helper id
inline constexpr s32 kMdlAttach = 948;
inline constexpr s32 kMdlAttachCount = 5;
inline constexpr s32 kAttachSize = 12;
inline constexpr s32 kAttFlags = 0;
inline constexpr s32 kAttChild = 4;
inline constexpr s32 kAttHelper = 8;          // s32, -1 = none (sub_3196D0)
// the helper table: {u16 count, u16 refs, entries*}, 80-byte entries (matrix, +64 id, +68 frame id)
inline constexpr s32 kMdlHelpers = 1008;
inline constexpr s32 kMdlFxList = 1012;       // the effect list (sub_31D6B0): effect nodes bound to helpers
// the model's sound record (32 bytes; sub_31EEB0 / sub_31EBE0 / sub_31F5C0)
inline constexpr s32 kMdlSound = 1016;
inline constexpr s32 kMdlLayer = 1048;        // u16 = 2 at creation; sub_319230 sets it for the model and its children
inline constexpr s32 kMdlColour2 = 1050;      // u8[4]: a copy of the creation colour
inline constexpr s32 kMdlPrev = 1056;         // MdlModel*: the list links, list head gMdlLists[type] (0x9571F0)
inline constexpr s32 kMdlNext = 1060;
// MdlLoad*: the pending load (80 bytes; sub_319840), freed when ready (sub_319910)
inline constexpr s32 kMdlLoad = 1064;
// MdlAnimSlot (156 bytes, at kMdlSlots + 156 * i; sub_313230 initialises it)
// u16: 0x1 loop, 0x2 owns a hierarchy copy, 0x4 time set, 0x10 bone scale on
inline constexpr s32 kSlotFlags = 0;
inline constexpr s32 kSlotDone = 2;           // u8: 1 = stopped at the end (1 at creation)
inline constexpr s32 kSlotAnim = 4;           // s16: the current animation index (-1 none)
inline constexpr s32 kSlotSpeed = 8;          // f32 speed (1.0)
inline constexpr s32 kSlotTime = 12;          // f32: the time in seconds (frames x 1/30)
inline constexpr s32 kSlotPrevAnim = 16;      // s16: the animation being blended out (-1)
inline constexpr s32 kSlotPrevTime = 20;      // f32: its time
inline constexpr s32 kSlotBlend = 28;         // f32: blend weight (1.0 = no blend)
inline constexpr s32 kSlotHier = 32;          // the slot's hierarchy (its interpolator at +32)
inline constexpr s32 kSlotInterpA = 36;       // blend interpolators (destroyed with the slot)
inline constexpr s32 kSlotInterpB = 40;
inline constexpr s32 kSlotSet = 44;           // MdlAnimSet*: the animations (refcounted)
// the effect binding (sub_311480): {count, +8 setter argument, +20 effect lists* (one per animation), +24 / +28 the
// list running / wanted, +32 after-effect handles*, +36 / +40 running / wanted, +44 changed, +48 u16 delay}
inline constexpr s32 kSlotFx = 48;
inline constexpr s32 kSlotBone = 52;          // s32: the bone the scale applies to
inline constexpr s32 kSlotBoneScale = 56;     // f32[3] that bone's scale
// f32: two more bone parameters (copied to 0x9571C0 / 0x9571C4 for sub_311730)
inline constexpr s32 kSlotBoneArg0 = 68;
inline constexpr s32 kSlotBoneArg1 = 72;
// u16 look-at flags: 0x20 / 0x40 point modes, 0x80 angle mode, 0x100 / 0x200, 0x4000 applied
inline constexpr s32 kSlotLook = 76;
inline constexpr s32 kSlotLookSpeed = 80;     // f32 (0.2 = gp-32588)
inline constexpr s32 kSlotLookYaw = 84;       // f32 limit, degrees (70)
inline constexpr s32 kSlotLookPitch = 88;     // f32 limit, degrees (80)
inline constexpr s32 kSlotLookQuat = 92;      // f32[4] (0, 0, 0, 1)
inline constexpr s32 kSlotLookScale = 124;    // f32[3] (1, 1, 1)
inline constexpr s32 kSlotLookTarget = 136;   // f32[3]: the point / the two angles
inline constexpr s32 kSlotEndFn = 148;        // void (*)(arg): called when an animation ends (sub_313090)
inline constexpr s32 kSlotEndArg = 152;
// MdlAnimSet (sub_311310): {entries*, u16 count, u16 refs}, then count 80-byte entries
inline constexpr s32 kSetEntries = 0;
inline constexpr s32 kSetCount = 4;           // u16
inline constexpr s32 kSetRefs = 6;            // u16
// RwMatrix root (identity), +64 the animation, +68 flags (bit 0: not owned)
inline constexpr s32 kSetEntrySize = 80;
inline constexpr s32 kEntAnim = 64;           // the animation (0 none; &gMdlDummyAnim 0x9571D0 = a placeholder)
inline constexpr s32 kEntFlags = 68;
// MdlLoad (80 bytes, kMdlLoad)
inline constexpr s32 kLdStream = 0;           // the memory stream over the file (sub_4C58A0), 0 until opened
inline constexpr s32 kLdBuffer = 12;          // a buffer freed with the request
inline constexpr s32 kLdData = 56;            // {data, size} of the model file
inline constexpr s32 kLdSize = 60;
inline constexpr s32 kLdTexDict = 64;         // released with sub_1A14C0 when set
inline constexpr s32 kLdNode = 68;            // the H_Cdvd request node (0 = data given in memory)
// u8: 0 waiting for the file, 1 / 2 / 3 reading (sub_31AAD0 / sub_319970), 4 closing, 5 done
inline constexpr s32 kLdState = 72;
inline constexpr s32 kLdPacked = 76;          // s32: 1 = an archive {model, sound bank}
// MdlFxNode (20 bytes) of an effect list, and its shared definition
inline constexpr s32 kFxDef = 0;              // MdlFxDef*: {data*, instance, refs, flags}
inline constexpr s32 kFxHelper = 4;           // u16 helper id
inline constexpr s32 kFxNode = 8;             // the effect node instance (sub_34FCD0 / sub_34FD50), 0 when stopped
inline constexpr s32 kFxPrev = 12;
inline constexpr s32 kFxNext = 16;
inline constexpr s32 kFxDefData = 0;
inline constexpr s32 kFxDefInst = 4;          // the first instance (later ones are clones of it)
inline constexpr s32 kFxDefRefs = 8;
inline constexpr s32 kFxDefFlags = 12;        // bit 0: restart with the animation (sub_31DCE0)

}  // namespace mdl


void sub_311310(EEContext& ctx);  // 0x311310 [mdlAnimSetCreate]
void sub_311480(EEContext& ctx);  // 0x311480 [mdlAnimFxUpdate]
void sub_3115A0(EEContext& ctx);  // 0x3115A0 [mdlFindHierarchyFrameCB]
void sub_311610(EEContext& ctx);  // 0x311610 [mdlAtomicSetHierarchyCB]
void sub_311640(EEContext& ctx);  // 0x311640 [mdlInterpBlendNodesCB]
void sub_312C70(EEContext& ctx);  // 0x312C70 [mdlBoneScaleKeyCB]
void sub_312D40(EEContext& ctx);  // 0x312D40 [mdlSlotUpdateHierarchy]
void mdlManagerSetMaterialMatFxPipeline(EEContext& ctx);  // 0x312E80 (register ABI: arguments in $a0.., the result in $v0)
void mdlManagerSetClumpPipelines(EEContext& ctx);  // 0x312F90 (register ABI: arguments in $a0.., the result in $v0)
void sub_313090(EEContext& ctx);  // 0x313090 [mdlAnimEndCB]
void sub_313230(EEContext& ctx);  // 0x313230 [mdlAnimSlotInit]
void sub_3132C0(EEContext& ctx);  // 0x3132C0 [mdlAnimSlotRelease]
void sub_313BE0(EEContext& ctx);  // 0x313BE0 [mdlAltAnimSetRelease]
void sub_313CA0(EEContext& ctx);  // 0x313CA0 [mdlAltAnimSlotUpdate]
void sub_313E60(EEContext& ctx);  // 0x313E60 [mdlMatAnimSetRelease]
void sub_313F40(EEContext& ctx);  // 0x313F40 [mdlMaterialListAddUniqueCB]
void sub_313FE0(EEContext& ctx);  // 0x313FE0 [mdlAtomicForAllMaterialsCB]
void sub_314020(EEContext& ctx);  // 0x314020 [mdlStepKeyApply]
void sub_314060(EEContext& ctx);  // 0x314060 [mdlStepKeyBlend]
void sub_3140C0(EEContext& ctx);  // 0x3140C0 [mdlMatAnimFreezeCB]
void sub_314170(EEContext& ctx);  // 0x314170 [mdlMatAnimEndCB]
void sub_3142B0(EEContext& ctx);  // 0x3142B0 [mdlMaterialNameString]
void sub_3143C0(EEContext& ctx);  // 0x3143C0 [mdlMatAnimSetup]
void sub_314510(EEContext& ctx);  // 0x314510 [mdlAtomicSetSkinTypeCB]
void sub_314650(EEContext& ctx);  // 0x314650 [mdlAtomicSetBigSkinMatPipesCB]
void sub_314730(EEContext& ctx);  // 0x314730 [mdlMatAnimSetTime]
void sub_315010(EEContext& ctx);  // 0x315010 [mdlFindFrameByIdCB]
void sub_315090(EEContext& ctx);  // 0x315090 [mdlHelperMatrixFromTable]
void sub_315ED0(EEContext& ctx);  // 0x315ED0 [mdlAtomicMaterialsSetupCB]
void sub_315F50(EEContext& ctx);  // 0x315F50 [mdlAtomicApplyColourCB]
void sub_316320(EEContext& ctx);  // 0x316320 [mdlClumpApplyColour]
void sub_316360(EEContext& ctx);  // 0x316360 [mdlAtomicFindTranslucentMatCB]
void sub_316410(EEContext& ctx);  // 0x316410 [mdlAtomicMatFxFlagCB]
void sub_3164C0(EEContext& ctx);  // 0x3164C0 [mdlClumpMatFxFlag]
void sub_3164F0(EEContext& ctx);  // 0x3164F0 [mdlSlotsBoneScaleFromHeader]
void sub_3165E0(EEContext& ctx);  // 0x3165E0 [mdlAtomicDoubleBoundsCB]
void sub_316690(EEContext& ctx);  // 0x316690 [mdlModelCreate]
void sub_316910(EEContext& ctx);  // 0x316910 [mdlModelFind]
void sub_316970(EEContext& ctx);  // 0x316970 [mdlModelSetupClump]
void sub_316B40(EEContext& ctx);  // 0x316B40 [mdlModelCreateFromFile]
void sub_316BD0(EEContext& ctx);  // 0x316BD0 [mdlModelCreateFromMemory]
void sub_316C70(EEContext& ctx);  // 0x316C70 [mdlModelCreateFromArchive]
void sub_317450(EEContext& ctx);  // 0x317450 [mdlModelClone]
void sub_3174E0(EEContext& ctx);  // 0x3174E0 [mdlModelDestroy]
void sub_3176C0(EEContext& ctx);  // 0x3176C0 [mdlModelApplyPlacement]
void sub_3182D0(EEContext& ctx);  // 0x3182D0 [mdlModelSetAnim]
void sub_318540(EEContext& ctx);  // 0x318540 [mdlModelGetAnim]
void sub_3185B0(EEContext& ctx);  // 0x3185B0 [mdlModelHasAnimSet]
void sub_318620(EEContext& ctx);  // 0x318620 [mdlModelHasAnim]
void sub_3186E0(EEContext& ctx);  // 0x3186E0 [mdlModelIsDummyAnim]
void sub_318770(EEContext& ctx);  // 0x318770 [mdlModelSetAnimFrame]
void sub_318870(EEContext& ctx);  // 0x318870 [mdlModelGetCurAnimLength]
void sub_318910(EEContext& ctx);  // 0x318910 [mdlModelGetAnimLength]
void sub_318990(EEContext& ctx);  // 0x318990 [mdlModelGetSlotFrame]
void sub_3189F0(EEContext& ctx);  // 0x3189F0 [mdlModelSetAnimSpeed]
void sub_318A30(EEContext& ctx);  // 0x318A30 [mdlMatrixTranslate]
void sub_318A50(EEContext& ctx);  // 0x318A50 [mdlMatrixRotate]
void sub_318A70(EEContext& ctx);  // 0x318A70 [mdlMatrixTransform]
void sub_318A90(EEContext& ctx);  // 0x318A90 [mdlModelSetScale]
void sub_318AD0(EEContext& ctx);  // 0x318AD0 [mdlModelSetColour]
void sub_318B00(EEContext& ctx);  // 0x318B00 [mdlModelGetColour]
void sub_318B10(EEContext& ctx);  // 0x318B10 [mdlMatrixSetIdentity]
void sub_318B60(EEContext& ctx);  // 0x318B60 [mdlModelGetPlacement]
void sub_318B70(EEContext& ctx);  // 0x318B70 [mdlModelGetFrame]
void sub_318B80(EEContext& ctx);  // 0x318B80 [mdlModelGetClump]
void sub_318B90(EEContext& ctx);  // 0x318B90 [mdlModelUpdateHierarchy]
void sub_318D10(EEContext& ctx);  // 0x318D10 [mdlModelGetHelperMatrix]
void sub_318ED0(EEContext& ctx);  // 0x318ED0 [mdlModelGetHelperPos]
void sub_318FC0(EEContext& ctx);  // 0x318FC0 [mdlModelGetHelperCount]
void sub_319010(EEContext& ctx);  // 0x319010 [mdlModelSetFlag1]
void sub_319030(EEContext& ctx);  // 0x319030 [mdlModelClearFlag1]
void sub_319050(EEContext& ctx);  // 0x319050 [mdlModelSetFlag20]
void sub_319070(EEContext& ctx);  // 0x319070 [mdlModelClearFlag20]
void sub_319090(EEContext& ctx);  // 0x319090 [mdlModelSetLookSpeed]
void sub_3190A0(EEContext& ctx);  // 0x3190A0 [mdlModelSetLookLimits]
void sub_3190B0(EEContext& ctx);  // 0x3190B0 [mdlModelLookAtPoint]
void sub_319100(EEContext& ctx);  // 0x319100 [mdlModelLookAtPoint2]
void sub_319150(EEContext& ctx);  // 0x319150 [mdlModelLookAngles]
void sub_319190(EEContext& ctx);  // 0x319190 [mdlModelLookRelease]
void sub_3191B0(EEContext& ctx);  // 0x3191B0 [mdlModelLookFlag200]
void sub_3191D0(EEContext& ctx);  // 0x3191D0 [mdlModelIsLooking]
void sub_3191F0(EEContext& ctx);  // 0x3191F0 [mdlModelSetLookFlags]
void sub_319200(EEContext& ctx);  // 0x319200 [mdlModelGetLookFlags]
void sub_319210(EEContext& ctx);  // 0x319210 [mdlModelSetLookScale]
void sub_319230(EEContext& ctx);  // 0x319230 [mdlModelSetLayer]
void sub_3192A0(EEContext& ctx);  // 0x3192A0 [mdlModelAttachFromFile]
void sub_319390(EEContext& ctx);  // 0x319390 [mdlModelAttachFromMemory]
void sub_319490(EEContext& ctx);  // 0x319490 [mdlModelAttachById]
void sub_3195F0(EEContext& ctx);  // 0x3195F0 [mdlModelAttachClone]
void sub_3196D0(EEContext& ctx);  // 0x3196D0 [mdlModelSetAttachHelper]
void sub_3196F0(EEContext& ctx);  // 0x3196F0 [mdlModelDetach]
void sub_319770(EEContext& ctx);  // 0x319770 [mdlModelAttachReady]
void sub_3197C0(EEContext& ctx);  // 0x3197C0 [mdlModelSetChildrenParentMatrix]
void sub_319840(EEContext& ctx);  // 0x319840 [mdlLoadCreate]
void sub_3198A0(EEContext& ctx);  // 0x3198A0 [mdlLoadSetMemory]
void sub_3198C0(EEContext& ctx);  // 0x3198C0 [mdlLoadRequestFile]
void sub_319900(EEContext& ctx);  // 0x319900 [mdlLoadSetPacked]
void sub_319910(EEContext& ctx);  // 0x319910 [mdlLoadDestroy]
void sub_31B220(EEContext& ctx);  // 0x31B220 [mdlModelLoadStep]
void sub_31B470(EEContext& ctx);  // 0x31B470 [mdlManagerInit]
void sub_31B4A0(EEContext& ctx);  // 0x31B4A0 [mdlNpcModelPath]
void sub_31B680(EEContext& ctx);  // 0x31B680 [mdlPartyNpcId]
void sub_31BE80(EEContext& ctx);  // 0x31BE80 [mdlModelAttachNpcWeapon]
void sub_31C000(EEContext& ctx);  // 0x31C000 [mdlNpcModelPathResolve]
void sub_31C7E0(EEContext& ctx);  // 0x31C7E0 [mdlModelLoadSoundBank]
void sub_31D4F0(EEContext& ctx);  // 0x31D4F0 [mdlIsPackedKind]
void sub_31D530(EEContext& ctx);  // 0x31D530 [mdlModelPath]
void sub_31D6B0(EEContext& ctx);  // 0x31D6B0 [mdlFxListCreate]
void sub_31D700(EEContext& ctx);  // 0x31D700 [mdlFxListClone]
void sub_31D790(EEContext& ctx);  // 0x31D790 [mdlFxListDestroy]
void sub_31D7D0(EEContext& ctx);  // 0x31D7D0 [mdlFxListInit]
void sub_31D7E0(EEContext& ctx);  // 0x31D7E0 [mdlFxListAddDef]
void sub_31D900(EEContext& ctx);  // 0x31D900 [mdlFxListAddShared]
void sub_31D9C0(EEContext& ctx);  // 0x31D9C0 [mdlFxListPlace]
void sub_31DC80(EEContext& ctx);  // 0x31DC80 [mdlFxListDraw]
void sub_31DCE0(EEContext& ctx);  // 0x31DCE0 [mdlFxListRestart]
void sub_31DD40(EEContext& ctx);  // 0x31DD40 [mdlFxListSetColour]
void sub_31DDA0(EEContext& ctx);  // 0x31DDA0 [mdlFxListSet]
void sub_31DE30(EEContext& ctx);  // 0x31DE30 [mdlFxListClear]
void sub_31DED0(EEContext& ctx);  // 0x31DED0 [mdlFxListInstantiate]
void sub_31DF80(EEContext& ctx);  // 0x31DF80 [mdlFxListStop]
void sub_31DFF0(EEContext& ctx);  // 0x31DFF0 [mdlAfxCreate]
void sub_31E0B0(EEContext& ctx);  // 0x31E0B0 [mdlAfxClone]
void sub_31E130(EEContext& ctx);  // 0x31E130 [mdlAfxDestroy]
void sub_31E1B0(EEContext& ctx);  // 0x31E1B0 [mdlAfxUpdate]
void sub_31E1E0(EEContext& ctx);  // 0x31E1E0 [mdlAfxDraw]
void sub_31E210(EEContext& ctx);  // 0x31E210 [mdlAfxRestart]
void sub_31E240(EEContext& ctx);  // 0x31E240 [mdlAfxDraw2]
void sub_31E270(EEContext& ctx);  // 0x31E270 [mdlAfxStart]
void sub_31E2C0(EEContext& ctx);  // 0x31E2C0 [mdlAfxStop]
void sub_31E300(EEContext& ctx);  // 0x31E300 [mdlAfxData]
void sub_31E310(EEContext& ctx);  // 0x31E310 [mdlSoundBankSlot]
void sub_31E420(EEContext& ctx);  // 0x31E420 [mdlPlayerOutfitFlag]
void sub_31EBE0(EEContext& ctx);  // 0x31EBE0 [mdlSoundUpdateLoad]
void sub_31EE80(EEContext& ctx);  // 0x31EE80 [mdlSoundShare]
void sub_31EEB0(EEContext& ctx);  // 0x31EEB0 [mdlSoundInit]
void sub_31EEE0(EEContext& ctx);  // 0x31EEE0 [mdlSoundRelease]
void sub_31F5C0(EEContext& ctx);  // 0x31F5C0 [mdlSoundUpdate]
void sub_31F6D0(EEContext& ctx);  // 0x31F6D0 [mdlSoundPlay]
void sub_31F740(EEContext& ctx);  // 0x31F740 [mdlCurveFindKey]
void sub_31F7A0(EEContext& ctx);  // 0x31F7A0 [mdlCurveEvalScalar]
void sub_31F870(EEContext& ctx);  // 0x31F870 [mdlCurveEvalScalarBlend]
void sub_31F9D0(EEContext& ctx);  // 0x31F9D0 [mdlCurveEvalScalarFade]
void sub_31FAF0(EEContext& ctx);  // 0x31FAF0 [mdlMaterialSetAlphaCB]
void sub_31FBD0(EEContext& ctx);  // 0x31FBD0 [mdlCurveEvalVec3]
void sub_31FD00(EEContext& ctx);  // 0x31FD00 [mdlCurveEvalVec3Blend]
void sub_31FDE0(EEContext& ctx);  // 0x31FDE0 [mdlCurveEvalVec3Fade]
void sub_31FF40(EEContext& ctx);  // 0x31FF40 [mdlColourFromVec3]

}  // namespace p3fes::game
