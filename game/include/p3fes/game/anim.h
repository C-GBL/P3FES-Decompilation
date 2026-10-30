// Animation and skinning (slice anim, game/src/model/anim.cpp): RenderWare's RtAnim, RpHAnim, RpSkin and RpUVAnim
// toolkits, the compressed keyframe scheme 0x4F7300-0x4F8E10, the game's keyframe scheme 0x35A290-0x35ABA0 and two
// model-manager leftovers (sub_311730 the look-at hierarchy update, sub_317730 the per-model frame update; the slot
// update / start, the material animation and four destroy functions stay recompiled: test_field3_units stands them in).
// Register-ABI bodies (arguments in $a0.., the result in $v0); the record layouts below are the offsets the bodies use
// (named in the bodies as anim:: / mdl:: constants), read from the instructions and checked on the replay snapshots
// (b_5800, dorm_replay_4900, climb_ref_17000: tests/game/test_anim.cpp).
//
// What animates a character, frame by frame (mdlModelUpdate sub_317730 -> mdlAnimSlotUpdate sub_313490 per slot):
//
//   MdlModel (models.h)            +236 MdlAnimSlot[4] (156 bytes each; slot 0 the body, 1..3 further hierarchies)
//     MdlAnimSlot                  +4 s16 animation index into the slot's MdlAnimSet (+44), +8 f32 speed,
//                                  +12 f32 time (seconds; follows the interpolator after every update),
//                                  +16 / +20 the animation being blended out and its time, +24 u16 blend length in
//                                  frames, +28 f32 blend progress (0..1; >= 1 = no blend), +36 / +40 the outgoing /
//                                  incoming blend interpolators, +2 u8 stopped, +0 bit 0 loop, +32 the hierarchy
//     RpHAnimHierarchy             +32 the interpolator, +8 the node matrices (RwMatrix[nodes], 64 bytes each),
//                                  +16 the node table (id, index, push / pop flags, frame), +20 the parent frame
//     RtAnimInterpolator           +0 the current RtAnimAnimation, +4 f32 time, +76 per node the interpolated frame
//                                  {key1*, key2*, quaternion f32[4], translation f32[3]} (36 bytes for the compressed
//                                  scheme every character animation uses: info 0x95FBE0 = id 2)
//     RtAnimAnimation              +0 the scheme, +4 keyframe count, +12 f32 duration, +16 the keyframes, +20 the
//                                  compressed scheme's 24-byte custom data (translation offset[3], scale[3])
//     RpSkin (per skinned geometry) +12 the inverse bind matrices; the bone palette is node matrix x inverse bind,
//                                  built per atomic by _rpSkinMatrixUpdating (render code) from the hierarchy's +8.
//
// The state a networked character needs, smallest first: per slot {animation index (+4), time (+12), speed (+8),
// loop flag (+0 bit 0), and while blending the previous index / time (+16 / +20), blend length (+24) and progress
// (+28)}. Everything else is derived: the interpolated frames come from the animation at that time
// (RtAnimInterpolatorSetCurrentTime replays keyframes from the start when the time goes back), the node matrices from
// RpHAnimHierarchyUpdateMatrices, the skin palette from the node matrices -- so a remote character can be posed by
// setting index / time / blend on its slot and running the normal update, without sending matrices. Sending the node
// matrices instead (+8 of the hierarchy, 64 bytes x 90-102 nodes for the party in b_5800) is the fallback when the
// remote side cannot run the update. The look-at (slot +76.., applied by sub_311730) and the material (UV) animation
// (MdlModel +868, sub_314D30) are separate small states of the same kind (target / angles; index + time).
//
// Measured on b_5800 (battle): the three party models (kind 1, ids 1 / 2 / 5) have 94 / 91 / 102-node hierarchies,
// interpolators on the compressed scheme with 394..509 keyframes, slot 0 blending (+28 > 1 after the blend, the two
// blend interpolators kept); the enemy (kind 2, id 225) 40 nodes; weapons (kind 7 / 10) 1..7 nodes.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace anim {

// RtAnimInterpolatorInfo: one interpolation scheme (the table at 0x95FBE0, 16 entries, count 0x7CE8A0); 48 bytes
inline constexpr s32 kInfoTypeId = 0;         // s32 scheme id (1 RpHAnim standard, 2 compressed, 0x1C0 / 0x1C1 UV, 0x44A07195 the game's)
inline constexpr s32 kInfoInterpFrameSize = 4;// s32 bytes per interpolated frame
inline constexpr s32 kInfoAnimFrameSize = 8;  // s32 bytes per keyframe
inline constexpr s32 kInfoApplyCB = 12;       // fn(matrix, frame): an interpolated frame as a matrix
inline constexpr s32 kInfoBlendCB = 16;       // fn(out, a, b; f12 weight)
inline constexpr s32 kInfoInterpolateCB = 20; // fn(out, key1, key2; f12 time, custom data)
inline constexpr s32 kInfoAddCB = 24;         // fn(out, a, b)
inline constexpr s32 kInfoMulRecipCB = 28;    // fn(frame, start)
inline constexpr s32 kInfoStreamReadCB = 32;  // fn(stream, anim)
inline constexpr s32 kInfoStreamWriteCB = 36; // fn(anim, stream)
inline constexpr s32 kInfoStreamSizeCB = 40;  // fn(anim) -> bytes
inline constexpr s32 kInfoCustomDataSize = 44;// s32 bytes of per-animation custom data
inline constexpr s32 kInfoSize = 48;

// RtAnimAnimation: an animation (RwMalloc'd with its keyframes and custom data); 24 bytes
inline constexpr s32 kAnmInfo = 0;            // RtAnimInterpolatorInfo*: the scheme
inline constexpr s32 kAnmNumFrames = 4;       // s32 keyframe count
inline constexpr s32 kAnmFlags = 8;           // u32
inline constexpr s32 kAnmDuration = 12;       // f32 seconds
inline constexpr s32 kAnmFrames = 16;         // the keyframes (= anim + 24); node i's first two are i and i + nodes
inline constexpr s32 kAnmCustomData = 20;     // after the keyframes (0 without); UV animations: UvCustom*
inline constexpr s32 kAnmSize = 24;

// RtAnimInterpolator: plays one animation over a hierarchy's nodes; interpolated frames from +76; 76 bytes
inline constexpr s32 kItpAnim = 0;            // RtAnimAnimation*: the current animation
inline constexpr s32 kItpTime = 4;            // f32 current time (seconds)
inline constexpr s32 kItpNextFrame = 8;       // the next keyframe to feed (0 = restart the search)
inline constexpr s32 kItpCallBack = 12;       // fn(itp, data) -> keep: the animation callback
inline constexpr s32 kItpCallBackData = 16;
inline constexpr s32 kItpCallBackTime = 20;   // f32 when the callback fires (-1.0 none)
inline constexpr s32 kItpLoopCallBack = 24;   // fn(itp, data) -> keep: called when the time wraps (models: mdlAnimEndCB)
inline constexpr s32 kItpLoopCallBackData = 28;
inline constexpr s32 kItpMaxFrameSize = 32;   // s32 room per interpolated frame
inline constexpr s32 kItpFrameSize = 36;      // s32 the scheme's interpolated frame size (the stride from +76)
inline constexpr s32 kItpAnimFrameSize = 40;  // s32 the scheme's keyframe size (-1 before an animation)
inline constexpr s32 kItpNumNodes = 44;       // s32
inline constexpr s32 kItpIsSub = 48;          // s32 1 = a sub-interpolator
inline constexpr s32 kItpOffsetInParent = 52; // s32 first node in the parent
inline constexpr s32 kItpParent = 56;         // the parent interpolator (itself when not a sub-interpolator)
inline constexpr s32 kItpApplyCB = 60;        // the scheme's callbacks, copied at SetCurrentAnim
inline constexpr s32 kItpBlendCB = 64;
inline constexpr s32 kItpInterpolateCB = 68;
inline constexpr s32 kItpAddCB = 72;
inline constexpr s32 kItpFrames = 76;         // the interpolated frames: per node {key1*, key2*, the scheme's values}
inline constexpr s32 kItpSize = 76;

// Interpolated frame header (every scheme): the two keyframes it lies between; 8 bytes
inline constexpr s32 kIfKey1 = 0;             // the earlier keyframe
inline constexpr s32 kIfKey2 = 4;             // the later keyframe
inline constexpr s32 kIfQuat = 8;             // f32[4] quaternion x, y, z, w (standard / compressed / game schemes)
inline constexpr s32 kIfTrans = 24;           // f32[3] translation
inline constexpr s32 kIfScale = 36;           // f32[3] the game scheme's scale
inline constexpr s32 kIfSize = 8;

// Keyframe header (every scheme); 8 bytes
inline constexpr s32 kKfPrev = 0;             // the previous keyframe of the same node
inline constexpr s32 kKfTime = 4;             // f32 seconds
inline constexpr s32 kKfQuat = 8;             // standard: f32[4] quaternion; compressed: s16[4]; game: f32[4]
inline constexpr s32 kKfTrans = 24;           // standard / game: f32[3] translation
inline constexpr s32 kKfScale = 36;           // game: f32[3] scale; +48 f32 a scalar the blend multiplies
inline constexpr s32 kKfSize = 8;

// RpHAnimHierarchy (free list 0x7CE734); 36 bytes
inline constexpr s32 kHierFlags = 0;          // u32: 1 sub-hierarchy, 2 no matrix array, 0x1000 / 0x2000 update the node frames, 0x4000 local-space matrices
inline constexpr s32 kHierNumNodes = 4;       // s32
inline constexpr s32 kHierMatrices = 8;       // RwMatrix[nodes], 64 bytes each, 16-aligned: the bone matrices
inline constexpr s32 kHierMatricesRaw = 12;   // the unaligned allocation
inline constexpr s32 kHierNodeInfo = 16;      // RpHAnimNodeInfo[nodes]
inline constexpr s32 kHierParentFrame = 20;   // RwFrame* the hierarchy hangs off
inline constexpr s32 kHierParentHier = 24;    // the root hierarchy (itself unless a sub-hierarchy)
inline constexpr s32 kHierRootParentOffset = 28;// s32 a sub-hierarchy's parent node (-1 none)
inline constexpr s32 kHierInterp = 32;        // RtAnimInterpolator*: the current animation state
inline constexpr s32 kHierSize = 36;

// RpHAnimNodeInfo; 16 bytes
inline constexpr s32 kNodeId = 0;             // s32 node id (matches the frame's HAnim id)
inline constexpr s32 kNodeIndex = 4;          // s32 node index
inline constexpr s32 kNodeFlags = 8;          // s32: 1 pop the parent matrix after this node, 2 push it
inline constexpr s32 kNodeFrame = 12;         // RwFrame* (0 until attached)
inline constexpr s32 kNodeSize = 16;

// RpSkin (free list 0x95DE28; the geometry extension at 0x95DE18 points at it); 72 bytes
inline constexpr s32 kSkinNumBones = 0;       // s32
inline constexpr s32 kSkinNumUsedBones = 4;   // s32
inline constexpr s32 kSkinUsedBones = 8;      // u8[used] bone numbers
inline constexpr s32 kSkinBoneMatrices = 12;  // RwMatrix[bones]: skin-to-bone (inverse bind) matrices, 16-aligned
inline constexpr s32 kSkinMaxWeights = 16;    // s32 weights per vertex (1..4)
inline constexpr s32 kSkinVertexIndices = 20; // u32 per vertex: four bone index bytes
inline constexpr s32 kSkinVertexWeights = 24; // f32[4] per vertex (bone index + 1) x 4 packed in the low mantissa bits
inline constexpr s32 kSkinWeightCounts = 28;  // s32[4] vertices with 1..4 weights
inline constexpr s32 kSkinSplitBoneLimit = 44;// s32 split data (partitioned skins): bone limit
inline constexpr s32 kSkinSplitNumMeshes = 48;// s32 (non-zero = partitioned)
inline constexpr s32 kSkinSplitNumRLE = 52;   // s32
inline constexpr s32 kSkinSplitRemap = 56;    // u8* bone remap indices (one block with the next two)
inline constexpr s32 kSkinSplitRLECount = 60; // u8[2 x meshes]
inline constexpr s32 kSkinSplitRLE = 64;      // u8[2 x RLE count]
inline constexpr s32 kSkinDataBlock = 68;     // the data block allocation (used bones, matrices, indices, weights)
inline constexpr s32 kSkinSize = 72;

// A UV animation's custom data (free list 0x7CE8B0); 68 bytes
inline constexpr s32 kUvcName = 0;            // char[32]
inline constexpr s32 kUvcChannels = 32;       // s32[8] node -> UV channel (0 / 1)
inline constexpr s32 kUvcRefCount = 64;       // s32
inline constexpr s32 kUvcSize = 68;

// RpUVAnim's material extension (offset 0x7CE8B4); 48 bytes
inline constexpr s32 kUvxMatrix0 = 0;         // RwMatrix* UV channel 0 (0 = unused)
inline constexpr s32 kUvxMatrix1 = 4;         // RwMatrix* UV channel 1
inline constexpr s32 kUvxSlots = 8;           // RtAnimInterpolator*[8]
inline constexpr s32 kUvxSize = 48;

// RtDict (an animation dictionary); 8 bytes
inline constexpr s32 kDictSchema = 0;         // RtDictSchema*
inline constexpr s32 kDictEntries = 4;        // rwSList of entry pointers
inline constexpr s32 kDictSize = 8;

// RtDictSchema (the UV-animation schema at 0x77E4E0); 48 bytes
inline constexpr s32 kDscAllocHint = 4;       // u32 memory hint (| 0x30000)
inline constexpr s32 kDscEntryChunkId = 8;    // u32
inline constexpr s32 kDscVersion = 12;        // u32 oldest native chunk version
inline constexpr s32 kDscDicts = 16;          // rwSList of dictionaries
inline constexpr s32 kDscCurrent = 20;        // RtDict*: the current dictionary
inline constexpr s32 kDscAddRefCB = 24;       // fn(entry)
inline constexpr s32 kDscDestroyCB = 28;      // fn(entry)
inline constexpr s32 kDscGetNameCB = 32;      // fn(entry) -> name
inline constexpr s32 kDscStreamReadCB = 40;   // fn(stream) -> entry
inline constexpr s32 kDscCompatReadCB = 44;   // fn(stream) -> dictionary (old versions)
inline constexpr s32 kDscSize = 48;

// RpGeometry (the fields the skin code reads)
inline constexpr s32 kGeoFlags = 8;           // u32: 0x80 MatFX, 0x1000000 native
inline constexpr s32 kGeoNumVertices = 20;    // s32

// RpAtomic (the fields the skin code reads)
inline constexpr s32 kAtmGeometry = 24;       // RpGeometry*
inline constexpr s32 kAtmPipeline = 108;      // RxPipeline* (+44 plugin id, +48 plugin data)

// The model manager's records beyond models.h (mdl::): the animation slot's blend length and the
// material-animation record (MdlModel + 868) with its set
inline constexpr s32 kSlotBlendFrames = 24;   // u16: the blend length in frames (0 = no blend); +28 is the blend's progress 0..1 (>= 1 done)
inline constexpr s32 kMatFlags = 0;           // u16 bit 0 loop
inline constexpr s32 kMatDone = 2;            // u8 1 = stopped
inline constexpr s32 kMatAnim = 4;            // s16 the current material animation (-1 none)
inline constexpr s32 kMatSpeed = 8;           // f32 speed
inline constexpr s32 kMatTime = 12;           // f32 the time since the start
inline constexpr s32 kMatAnimTime = 16;       // f32 the animation time
inline constexpr s32 kMatBlendCount = 20;     // u16 frames left before the animation time runs
inline constexpr s32 kMatSetEntries = 0;      // the per-animation entries {dictionary*, ...} (8 bytes each)
inline constexpr s32 kMatSetMaterials = 8;    // rwSList of the UV-animated materials
inline constexpr s32 kMatSetCount = 12;       // u16 animation count

}  // namespace anim

void sub_4B65A0(EEContext& ctx);  // 0x4B65A0 [rtAnimOpen]
void sub_4B6600(EEContext& ctx);  // 0x4B6600 [rtAnimClose]
void sub_4B6640(EEContext& ctx);  // 0x4B6640 [RtAnimInitialize]
void sub_4B6680(EEContext& ctx);  // 0x4B6680 [RtAnimRegisterInterpolationScheme]
void sub_4B67B0(EEContext& ctx);  // 0x4B67B0 [RtAnimGetInterpolatorInfo]
void sub_4B6840(EEContext& ctx);  // 0x4B6840 [RtAnimAnimationCreate]
void sub_4B69B0(EEContext& ctx);  // 0x4B69B0 [RtAnimAnimationRead]
void sub_4B6A40(EEContext& ctx);  // 0x4B6A40 [RtAnimAnimationStreamRead]
void sub_4B6C80(EEContext& ctx);  // 0x4B6C80 [RtAnimAnimationStreamWrite]
void sub_4B6D90(EEContext& ctx);  // 0x4B6D90 [RtAnimAnimationStreamGetSize]
void sub_4B6DD0(EEContext& ctx);  // 0x4B6DD0 [RtAnimAnimationGetNumNodes]
void sub_4B6E10(EEContext& ctx);  // 0x4B6E10 [RtAnimInterpolatorCreate]
void sub_4B6EC0(EEContext& ctx);  // 0x4B6EC0 [RtAnimInterpolatorSetCurrentAnim]
void sub_4B7010(EEContext& ctx);  // 0x4B7010 [RtAnimInterpolatorSetAnimLoopCallBack]
void sub_4B7020(EEContext& ctx);  // 0x4B7020 [RtAnimInterpolatorCopy]
void sub_4B7050(EEContext& ctx);  // 0x4B7050 [RtAnimInterpolatorSubAnimTime]
void sub_4B7240(EEContext& ctx);  // 0x4B7240 [RtAnimInterpolatorAddAnimTime]
void sub_4B74C0(EEContext& ctx);  // 0x4B74C0 [RtAnimInterpolatorSetCurrentTime]
void sub_4B7510(EEContext& ctx);  // 0x4B7510 [RtAnimInterpolatorBlend]
void sub_4B75D0(EEContext& ctx);  // 0x4B75D0 [RtAnimInterpolatorCreateSubInterpolator]
void sub_4B76B0(EEContext& ctx);  // 0x4B76B0 [rtDictRemoveEntry]
void sub_4B7750(EEContext& ctx);  // 0x4B7750 [RtDictSchemaGetCurrentDict]
void sub_4B7760(EEContext& ctx);  // 0x4B7760 [RtDictSchemaSetCurrentDict]
void sub_4B7770(EEContext& ctx);  // 0x4B7770 [rtDictDestroyEntries]
void sub_4B77F0(EEContext& ctx);  // 0x4B77F0 [RtDictFindNamedEntry]
void sub_4B79D0(EEContext& ctx);  // 0x4B79D0 [RtDictSchemaStreamReadDict]
void sub_4B7C60(EEContext& ctx);  // 0x4B7C60 [uvAnimKeyFrameInit]
void sub_4B7D00(EEContext& ctx);  // 0x4B7D00 [uvAnimStreamRead]
void sub_4B7E10(EEContext& ctx);  // 0x4B7E10 [uvAnimStreamWrite]
void sub_4B7F30(EEContext& ctx);  // 0x4B7F30 [uvAnimStreamGetSize]
void sub_4B7F80(EEContext& ctx);  // 0x4B7F80 [uvAnimLinearApply]
void sub_4B7FD0(EEContext& ctx);  // 0x4B7FD0 [uvAnimLinearInterpolate]
void sub_4B8080(EEContext& ctx);  // 0x4B8080 [uvAnimLinearBlend]
void sub_4B8120(EEContext& ctx);  // 0x4B8120 [uvAnimLinearMulRecip]
void sub_4B81F0(EEContext& ctx);  // 0x4B81F0 [uvAnimLinearAdd]
void sub_4B8290(EEContext& ctx);  // 0x4B8290 [uvAnimLinearFromMatrix]
void sub_4B82D0(EEContext& ctx);  // 0x4B82D0 [uvAnimParamApply]
void sub_4B83D0(EEContext& ctx);  // 0x4B83D0 [uvAnimParamInterpolate]
void sub_4B8500(EEContext& ctx);  // 0x4B8500 [uvAnimParamBlend]
void nullsub_125(EEContext& ctx);  // 0x4B8610 [uvAnimParamMulRecip]
void nullsub_126(EEContext& ctx);  // 0x4B8620 [uvAnimParamAdd]
void sub_4B8630(EEContext& ctx);  // 0x4B8630 [uvAnimParamFromMatrix]
void sub_4B8740(EEContext& ctx);  // 0x4B8740 [uvAnimOpen]
void sub_4B87D0(EEContext& ctx);  // 0x4B87D0 [uvAnimClose]
void sub_4B8830(EEContext& ctx);  // 0x4B8830 [RpUVAnimPluginAttach]
void sub_4B88E0(EEContext& ctx);  // 0x4B88E0 [uvAnimMaterialCtor]
void sub_4B8920(EEContext& ctx);  // 0x4B8920 [uvAnimMaterialDtor]
void sub_4B89D0(EEContext& ctx);  // 0x4B89D0 [uvAnimMaterialCopy]
void sub_4B8B10(EEContext& ctx);  // 0x4B8B10 [uvAnimMaterialUpdateMatrices]
void sub_4B8C30(EEContext& ctx);  // 0x4B8C30 [uvAnimMaterialStreamWrite]
void sub_4B8D50(EEContext& ctx);  // 0x4B8D50 [uvAnimCreateIdentity]
void sub_4B8E70(EEContext& ctx);  // 0x4B8E70 [uvAnimMaterialStreamRead]
void sub_4B9030(EEContext& ctx);  // 0x4B9030 [uvAnimMaterialStreamGetSize]
void sub_4B90A0(EEContext& ctx);  // 0x4B90A0 [uvAnimCustomDataStreamRead]
void sub_4B9140(EEContext& ctx);  // 0x4B9140 [uvAnimCustomDataStreamWrite]
void sub_4B91C0(EEContext& ctx);  // 0x4B91C0 [uvAnimCreate]
void sub_4B92D0(EEContext& ctx);  // 0x4B92D0 [RpUVAnimDestroy]
void sub_4B9350(EEContext& ctx);  // 0x4B9350 [RpUVAnimAddRef]
void sub_4B9370(EEContext& ctx);  // 0x4B9370 [RpUVAnimMaterialApplyInterpolators]
void sub_4B96E0(EEContext& ctx);  // 0x4B96E0 [uvAnimGetName]
void sub_4B96F0(EEContext& ctx);  // 0x4B96F0 [RpUVAnimMaterialSetAnim]
void sub_4B97B0(EEContext& ctx);  // 0x4B97B0 [RpUVAnimMaterialGetInterpolator]
void sub_4B97D0(EEContext& ctx);  // 0x4B97D0 [uvAnimMaterialSetInterpolator]
void sub_4B97F0(EEContext& ctx);  // 0x4B97F0 [RpUVAnimMaterialHasAnims]
void sub_4F7300(EEContext& ctx);  // 0x4F7300 [cmpKeyFloatToHalf]
void sub_4F7470(EEContext& ctx);  // 0x4F7470 [cmpKeyFrameApply]
void sub_4F7560(EEContext& ctx);  // 0x4F7560 [cmpKeyFrameInterpolate]
void sub_4F7F40(EEContext& ctx);  // 0x4F7F40 [cmpKeyFrameBlend]
void sub_4F8560(EEContext& ctx);  // 0x4F8560 [cmpKeyFrameStreamRead]
void sub_4F8690(EEContext& ctx);  // 0x4F8690 [cmpKeyFrameStreamWrite]
void sub_4F8790(EEContext& ctx);  // 0x4F8790 [cmpKeyFrameStreamGetSize]
void sub_4F87B0(EEContext& ctx);  // 0x4F87B0 [cmpKeyFrameMulRecip]
void sub_4F8CB0(EEContext& ctx);  // 0x4F8CB0 [cmpKeyFrameAdd]
void sub_4F8E10(EEContext& ctx);  // 0x4F8E10 [cmpKeyRegisterScheme]
void sub_35A290(EEContext& ctx);  // 0x35A290 [gameKeyFrameApply]
void sub_35A3F0(EEContext& ctx);  // 0x35A3F0 [gameKeyFrameInterpolateQT]
void sub_35A620(EEContext& ctx);  // 0x35A620 [gameKeyFrameBlend]
void sub_35A6A0(EEContext& ctx);  // 0x35A6A0 [gameKeyFrameStreamWrite]
void sub_35A770(EEContext& ctx);  // 0x35A770 [gameKeyFrameStreamRead]
void sub_35A850(EEContext& ctx);  // 0x35A850 [gameKeyFrameStreamGetSize]
void sub_35A870(EEContext& ctx);  // 0x35A870 [gameKeyFrameMulRecip]
void sub_35AA10(EEContext& ctx);  // 0x35AA10 [gameKeyFrameAdd]
void sub_35ABA0(EEContext& ctx);  // 0x35ABA0 [gameKeyRegisterScheme]
void sub_464760(EEContext& ctx);  // 0x464760 [RpHAnimKeyFrameApply]
void sub_464850(EEContext& ctx);  // 0x464850 [RpHAnimKeyFrameInterpolate]
void sub_464E80(EEContext& ctx);  // 0x464E80 [RpHAnimKeyFrameBlend]
void sub_4654A0(EEContext& ctx);  // 0x4654A0 [RpHAnimKeyFrameStreamRead]
void sub_465590(EEContext& ctx);  // 0x465590 [RpHAnimKeyFrameStreamWrite]
void sub_465660(EEContext& ctx);  // 0x465660 [RpHAnimKeyFrameStreamGetSize]
void sub_465670(EEContext& ctx);  // 0x465670 [RpHAnimKeyFrameMulRecip]
void sub_4657D0(EEContext& ctx);  // 0x4657D0 [RpHAnimKeyFrameAdd]
void sub_465930(EEContext& ctx);  // 0x465930 [hAnimAttachFrameCB]
void sub_465A00(EEContext& ctx);  // 0x465A00 [hAnimOpen]
void sub_465AE0(EEContext& ctx);  // 0x465AE0 [hAnimClose]
void sub_465B20(EEContext& ctx);  // 0x465B20 [hAnimFrameCtor]
void sub_465B40(EEContext& ctx);  // 0x465B40 [hAnimFrameDtor]
void sub_465BF0(EEContext& ctx);  // 0x465BF0 [hAnimFrameCopy]
void sub_465CF0(EEContext& ctx);  // 0x465CF0 [hAnimFrameStreamWrite]
void sub_465EB0(EEContext& ctx);  // 0x465EB0 [hAnimFrameStreamRead]
void sub_466130(EEContext& ctx);  // 0x466130 [hAnimFrameStreamGetSize]
void sub_4661B0(EEContext& ctx);  // 0x4661B0 [RpHAnimPluginAttach]
void sub_466260(EEContext& ctx);  // 0x466260 [RpHAnimHierarchyCreate]
void sub_466480(EEContext& ctx);  // 0x466480 [RpHAnimHierarchyCreateSubHierarchy]
void sub_466640(EEContext& ctx);  // 0x466640 [RpHAnimHierarchyAttach]
void sub_466710(EEContext& ctx);  // 0x466710 [RpHAnimFrameGetHierarchy]
void sub_466720(EEContext& ctx);  // 0x466720 [RpHAnimFrameGetID]
void sub_466730(EEContext& ctx);  // 0x466730 [hAnimHierarchyUpdateFrames]
void sub_466EF0(EEContext& ctx);  // 0x466EF0 [RpHAnimHierarchyUpdateMatrices]
void sub_489020(EEContext& ctx);  // 0x489020 [skinSplitDataDestroy]
void sub_489080(EEContext& ctx);  // 0x489080 [skinSplitDataStreamWrite]
void sub_489160(EEContext& ctx);  // 0x489160 [skinSplitDataStreamRead]
void sub_489320(EEContext& ctx);  // 0x489320 [skinSplitDataStreamGetSize]
void sub_489350(EEContext& ctx);  // 0x489350 [skinAtomicSetType]
void sub_4893E0(EEContext& ctx);  // 0x4893E0 [skinFindMaxWeights]
void sub_489460(EEContext& ctx);  // 0x489460 [skinFindUsedBones]
void sub_489550(EEContext& ctx);  // 0x489550 [skinCreateData]
void sub_489730(EEContext& ctx);  // 0x489730 [skinOpen]
void sub_489840(EEContext& ctx);  // 0x489840 [skinClose]
void sub_4898C0(EEContext& ctx);  // 0x4898C0 [skinGeometryCtor]
void sub_4898E0(EEContext& ctx);  // 0x4898E0 [skinGeometryDtor]
void sub_489950(EEContext& ctx);  // 0x489950 [skinGeometryCopy]
void sub_489960(EEContext& ctx);  // 0x489960 [skinAtomicCtor]
void sub_4899A0(EEContext& ctx);  // 0x4899A0 [skinAtomicDtor]
void sub_4899BC(EEContext& ctx);  // 0x4899BC [skinAtomicDtorTail]
void sub_4899D0(EEContext& ctx);  // 0x4899D0 [skinAtomicCopy]
void sub_4899F0(EEContext& ctx);  // 0x4899F0 [skinAtomicAlwaysCB]
void sub_489A80(EEContext& ctx);  // 0x489A80 [skinAtomicRightsCB]
void sub_489AE0(EEContext& ctx);  // 0x489AE0 [skinGeometryStreamGetSize]
void sub_489B70(EEContext& ctx);  // 0x489B70 [skinGeometryStreamWrite]
void sub_489CD0(EEContext& ctx);  // 0x489CD0 [skinGeometryStreamRead]
void sub_489F20(EEContext& ctx);  // 0x489F20 [skinAtomicStreamRead]
void sub_48A180(EEContext& ctx);  // 0x48A180 [skinAtomicStreamWrite]
void sub_48A190(EEContext& ctx);  // 0x48A190 [skinAtomicStreamGetSize]
void sub_48A1A0(EEContext& ctx);  // 0x48A1A0 [RpSkinPluginAttach]
void sub_48A2A0(EEContext& ctx);  // 0x48A2A0 [RpSkinAtomicSetHAnimHierarchy]
void sub_48A2C0(EEContext& ctx);  // 0x48A2C0 [RpSkinGeometryGetSkin]
void sub_48A2E0(EEContext& ctx);  // 0x48A2E0 [skinGeometrySetSkin]
void sub_48A370(EEContext& ctx);  // 0x48A370 [skinDestroy]
void name__C9type_info(EEContext& ctx);  // 0x48A3D0 [RpSkinGetNumBones]
void sub_48A3F0(EEContext& ctx);  // 0x48A3F0 [RpSkinAtomicSetType]
void sub_48A480(EEContext& ctx);  // 0x48A480 [RpSkinAtomicGetType]
void sub_48A4B0(EEContext& ctx);  // 0x48A4B0 [skinPrepareWeights]
void sub_48A790(EEContext& ctx);  // 0x48A790 [skinDestroyNoop]
void sub_48A7A0(EEContext& ctx);  // 0x48A7A0 [skinNativeStreamGetSize]
void sub_48A800(EEContext& ctx);  // 0x48A800 [skinNativeStreamWrite]
void sub_48A9A0(EEContext& ctx);  // 0x48A9A0 [skinNativeStreamRead]
void sub_48ABF0(EEContext& ctx);  // 0x48ABF0 [skinPlatformOpen]
void sub_48AC00(EEContext& ctx);  // 0x48AC00 [skinPlatformClose]
void sub_48AC10(EEContext& ctx);  // 0x48AC10 [skinAtomicSetPipeline]
void sub_311730(EEContext& ctx);  // 0x311730 [mdlSlotUpdateHierarchyLookAt]
void sub_317730(EEContext& ctx);  // 0x317730 [mdlModelUpdate]

}  // namespace p3fes::game
