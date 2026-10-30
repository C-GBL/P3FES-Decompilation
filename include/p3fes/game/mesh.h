// Phase 5 slice render_mesh: the second rendering slice -- RenderWare's PS2All mesh seam on the PS2 driver
// ("sky"), stock and skin path (docs/ANALYSIS/22_rendering.md sections 3.1-3.3 and 8.2; queue
// docs/ANALYSIS/queue_rendering.txt "Second slice"). 21 functions between RxPipelineExecute and the DMA packet
// layer: the per-atomic object node, the object set-up callbacks (stock and skin), lights, the instance test,
// the skin bone-matrix palette, the per-object VIF packet, the material bridge with the texture-cache entry
// and the per-mesh GS register shadows.
//
// Data flow of one atomic (every character, prop and world object drawn by a PS2All pipeline):
//
//   AtomicDefaultRenderCallBack AtomicDefaultRenderCallBack (atomic+0x6C pipeline, else the global default)
//     -> RxPipelineExecute 0x4F2E70 (recompiled) -> node body
//   PS2AllNodeBody PS2AllNodeBody
//     |  builds the 72-byte PipeData record on its own guest stack frame (sp+272, layout below; every
//     |  callback gets its address in $a0) and the object matrix at sp+208
//     |  object set-up callback (node private +16):
//     |      stock atomic  sub_4A09D0: mesh header, resEntry array, morph lerp, the object matrix (LTM x the
//     |                    camera's view), frustum test of the bounding sphere, PrimTypeTransTypeSetup RpAtomicPS2AllPrimTypeTransTypeSetupFunc
//     |                    (prim + transType), instance test sub_4A0480, lights sub_4A06C0 -> worldForAllLights (world
//     |                    lights, recompiled) -> sub_4A0430 -> sub_49FF10 (one light into the light block),
//     |                    and the lights tied to the world sectors the atomic touches
//     |      skinned atomic sub_46EB90: the same inlined, then the bone palette _rpSkinMatrixUpdating
//     |                    _rpSkinMatrixUpdating (VU0 4x4 products) uploaded whole (cnt + UNPACK V4-32 to VU1 0x2BC);
//     |                    sub_46B8E0 uploads one mesh's part of a partitioned palette
//     |  the light block header quadword (UNPACK of the light count to node private +28)
//     |  openVU1SetupPktNew openVU1SetupPktNew: the object matrix (4 qw) + 2 zero qw, 5 template qw, the light block
//     |  per mesh (12-byte records after the mesh header):
//     |      material pipeline: node +24, else material +8, else the global default
//     |      PipeData: mesh, resEntry slot, surface properties, texture, material colour
//     |      material instance test callback [0], PS2AllNodeInstance PS2AllNodeInstance (recompiled) when stale,
//     |      the resEntry relinked at the head of the resource list
//     |      bridge callback [3]: RpMeshPS2AllBridgeCallBack sub_4A0E00 (stock; MatFX skin bridges go through
//     |                          the dispatcher sub_46EA80)
//     |          texture: sub_4F0F30 (speculative cache placement), RpSkyTexCacheAccessRaster RpSkyTexCacheAccessRaster
//     |                   (TEX0 TBP/CBP, A+D TEX0/MIPTBP1/MIPTBP2 or TEX1), filter shadow sub_49CA50
//     |          VIF packet (18 qw reserved): cnt 15, the GIF tag -> VU1 0x3FA (template 0x9658A0, PRIM =
//     |          render flags | mesh prim), material colour sub_49CAB0 -> 0x3FB, surface properties
//     |          sub_49CBD0 -> 0x3FC, clip vectors + flags -> 0x3FD..0x3FF, A+D TEST/TEX1/CLAMP (textured)
//     |          or TEST (DIRECT), the VU1 code
//     |          array entry ((tt & 0x20) >> 5 | (tt & 0x18) >> 2) and a DMA `call` of its program when it is
//     |          not the resident one, then the DMA `call` of the resEntry's instanced clusters (reference
//     |          counted under DI/EI; first use -> _rwDMAAddPURef)
//     |      post-mesh callback [4]
//     |  the object's post callback (node private +20)
//
// What a future VU1-bypass renderer consumes is exactly the data this code serialises; the hand versions
// report it as host records (ObjectSetup, SkinPalette, MeshDraw below) to an optional observer, after the
// guest state is complete. The observer never changes guest state.
//
// Register contract (docs/PHASE5_AGENT_BRIEF.md, waves 6 and 7): every check point can preempt the thread and
// the kernel then saves the whole register file in guest memory, every callee's prologue spills registers, and
// game code reads registers a callee left behind. So these bodies are register-faithful: at every check point,
// every call and every return each GPR (128 bits), HI/LO, FPR, ACC, FCR31 and VU0 register holds what the
// original holds there, and the prologues write the original spills. The bodies therefore work on the guest
// registers directly (the Cpu view in mesh.cpp, one named variable per register), with the data flow named
// in comments and constants; the per-block virtual time follows the recompiled bodies (ADR-0013).
//
// Names: every function keeps its symbols/functions.json name (sub_* except RpMeshPS2AllBridgeCallBack); a
// bracketed name is a role (verified in 22_rendering.md and symbols/deltas/rendering.sym, not imported).
// The recompiled program's entry points (`fn_<name>_<addr8>`) are defined in src/render/mesh.cpp.
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"

namespace p3fes::game {

namespace mesh {

// --- guest addresses and layouts (obs: instructions) -----------------------------------------------------
inline constexpr u32 kGp = 0x007D2CF0u;
inline constexpr u32 kRwGlobals = 0x00960070u;  // RW engine globals: +0 the current camera; plugin offsets added

// $gp-relative words of the sky driver (gp-17148 etc. as the instructions name them).
inline constexpr s32 kGpSprWrite = -17148;      // scratchpad packet write pointer (_rwDMAOpenVIFPkt moves it)
inline constexpr s32 kGpRenderFlags = -20272;   // 64-bit; low 11 bits = GIF PRIM bits (0x10 TME, 0x40 ABE)
inline constexpr s32 kGpFogEnabled = -20232;    // non-zero: the clip vectors take the second template pair
inline constexpr s32 kGpTest = -17072;          // GS TEST_1 shadow (bit 0 ATE set when the raster has alpha)
inline constexpr s32 kGpClamp = -17048;         // GS CLAMP_1 shadow (bits 0/2: REGION_CLAMP on U/V)
inline constexpr s32 kGpTex1 = -17040;          // GS TEX1_1 shadow (MMAG/MMIN bits 5..8 from the filter mode)
inline constexpr s32 kGpCamFlags = -16892;      // byte: bit 0 fog (Im2D descriptor), bit 3 parallel projection
inline constexpr s32 kGpResidentProgram = -16888;  // VU1 program the packet stream last `call`ed
inline constexpr s32 kGpClipHi = -16884;        // 0, or 32 when the camera projection (gp-16964) is 3
inline constexpr s32 kGpClipLo = -16880;
inline constexpr s32 kGpCullMode = -16876;      // non-zero: back-face culling (clip vectors pair 1)
inline constexpr s32 kGpCamProjection = -16964;
inline constexpr s32 kGpRasterExt = -16968;     // plugin offset of the sky raster extension
inline constexpr s32 kGpCamFrustum = -16972;    // plugin offset of the camera's frustum planes (+96)
inline constexpr s32 kGpAlphaTex = -16956;      // material colour alpha != 255
inline constexpr s32 kGpRasterAlpha = -16952;   // the current raster has alpha (format nibble 1 or 5)
inline constexpr s32 kGpLastRaster = -16948;    // the raster of the last bridge (-1 none)
inline constexpr s32 kGpLightCount = -17520;    // light block: quadwords written this object (-1, -5: none)
inline constexpr s32 kGpLightPtr = -17516;      // light block write pointer (buffer 0x95DFC0)
inline constexpr s32 kGpResList = -17408;       // plugin offset of the resource arena (+36 = the resEntry list)
inline constexpr s32 kGpGeomResEntries = -17504;  // plugin offsets of the resEntry array: geometry (1 morph
inline constexpr s32 kGpAtomResEntries = -17508;  // target) / atomic (morphing)
inline constexpr s32 kGpSkinGeomExt = -17848;   // plugin offset of the MatFX / skin bridge selector
inline constexpr s32 kGpDefaultMatColour = -20712;  // 4 bytes: the material colour when not modulated
inline constexpr s32 kGpRwGlobalsOffset = -16840;   // plugin offset of the PS2All module in the RW globals

inline constexpr u32 kLightBuffer = 0x0095DFC0u;  // the light block (gp-17516 starts at +16 after the header qw)
inline constexpr u32 kTplObjHead = 0x009659C0u;   // openVU1SetupPktNew: the per-object template qw
inline constexpr u32 kTplObjTail = 0x00965970u;   // ... and the 5 template qw after the matrix
inline constexpr u32 kTplGifTag = 0x009658A0u;    // the GIF tag template the bridge patches (PRIM in bits 47..57)
inline constexpr u32 kTplClipCull = 0x00965930u;  // clip vector pair (culling / no fog)
inline constexpr u32 kTplClipFog = 0x00965910u;   // clip vector pair (fog)
inline constexpr u32 kTexCacheActive = 0x0077F200u;
inline constexpr u32 kTexCacheSlots = 0x0077F214u;  // slot array base (12-byte slots)
inline constexpr u32 kTexCacheLast = 0x0077F224u;   // the raster of the last cache access
inline constexpr u32 kTexCacheLastMode = 0x0077F228u;
inline constexpr u32 kTexCacheHit0 = 0x0077F22Cu;   // remembered slot indices
inline constexpr u32 kTexCacheHit1 = 0x0077F230u;
inline constexpr u32 kTexCacheUpload = 0x0077F220u; // upload callback (raster, mode)
inline constexpr u32 kSkinGlobals = 0x0095DE14u;    // the skin plugin's globals: +0 atomic ext offset, +4 geometry
                                                    // ext offset, +8 the matrix palette, +0x1C the palette record,
                                                    // +0x20 the instance hook

// The PipeData record PS2AllNodeBody keeps on its frame (sp + 272) and hands to every callback ($a0).
namespace pd {
inline constexpr u32 kNodePrivate = 0;     // the node's private data (callbacks at +16 set-up, +20 post, +24 material pipe)
inline constexpr u32 kMatPrivate = 4;      // the current material pipeline's private data
inline constexpr u32 kObject = 8;          // the atomic
inline constexpr u32 kMeshHeader = 12;     // RpMeshHeader: +0 flags (1 strip, 2 fan, 4 line list, 8 polyline), +4 u16 count, +12 first offset
inline constexpr u32 kResEntries = 16;     // the resEntry array ({count, entries...})
inline constexpr u32 kObjInstance = 20;    // object instance flags (1 = nothing to instance; 2/4/8 = re-instance reasons)
inline constexpr u32 kObjIdentifier = 24;  // geometry flags << 16 | morph count << 24 | vertex count
inline constexpr u32 kMorphLerp = 28;      // float: the interpolator of a morphing atomic
inline constexpr u32 kMorphTargets = 32;
inline constexpr u32 kFastMorph = 36;      // 2 for a morphing atomic
inline constexpr u32 kTransType = 40;      // byte: camera bits | 2 clip | 4 list | 0x10 line
inline constexpr u32 kPrimType = 41;       // byte: 1 line list, 2 polyline, 3 tri-list, 4 tri-strip
inline constexpr u32 kMatModulate = 42;    // byte: geometry flag 0x40 (modulate material colour)
inline constexpr u32 kVu1CodeIndex = 43;   // byte: ((tt & 0x20) >> 5) | ((tt & 0x18) >> 2)
inline constexpr u32 kMesh = 44;           // the current 12-byte RpMesh
inline constexpr u32 kResEntrySlot = 48;   // &resEntries[1 + i]
inline constexpr u32 kMeshInstance = 52;   // the mesh's instance flags (from the object's)
inline constexpr u32 kMeshIdentifier = 56;
inline constexpr u32 kSurfaceProps = 60;   // material + 12 {ambient, specular, diffuse}
inline constexpr u32 kTexture = 64;        // material +0
inline constexpr u32 kMatColour = 68;      // RGBA bytes
inline constexpr u32 kSize = 72;
}  // namespace pd

// --- the draw data as host records -----------------------------------------------------------------------
// One object (atomic): written by openVU1SetupPktNew from the matrix the set-up callback left and the light
// block (gp-17516 / gp-17520) the light functions filled.
struct ObjectSetup {
    u32 matrix = 0;        // the object-to-camera matrix (4 rows of 4 floats in guest RAM), 0 = none
    u32 lights = 0;        // the light block (light-count quadword first)
    u32 light_qw = 0;      // its quadwords
};
// One skinned object: the bone palette uploaded to VU1 0x2BC (64 bytes per bone, 4 rows of 4 floats).
struct SkinPalette {
    u32 palette = 0;       // guest address of the first matrix
    u32 bones = 0;
};
// One mesh draw as the bridge serialises it.
struct MeshDraw {
    u32 atomic = 0;
    u32 mesh = 0;              // RpMesh {indices, count, material}
    u32 material = 0;
    u32 texture = 0;           // 0 = untextured
    u32 raster = 0;
    u64 tex0 = 0;              // the raster extension's TEX0 after the cache placement (textured only)
    u64 tex1 = 0, clamp = 0, test = 0;  // GS register shadows the A+D block carries
    u64 gif_tag_lo = 0, gif_tag_hi = 0;  // the GIF tag of the VU1 kick (PRIM = render flags | prim)
    u8 trans_type = 0, prim_type = 0, vu1_code_index = 0;
    u32 vu1_program = 0;       // the code array entry (the program's DMA packet)
    bool program_uploaded = false;  // a `call` of the program was emitted (it was not resident)
    u32 colour[4] = {};        // material colour quadword (float bits) sent to VU1 0x3FC
    u32 surface[4] = {};       // surface properties quadword (float bits) sent to VU1 0x3FD
    u32 res_entry = 0;         // the resEntry whose instanced clusters are `call`ed
    u32 res_data = 0;          // their DMA address (resEntry +32)
    u32 vif_offset = 0;        // OFFSET of the material pipeline (matPvt +20)
};
struct DrawObserver {
    void (*object)(EEContext&, const ObjectSetup&) = nullptr;
    void (*skin)(EEContext&, const SkinPalette&) = nullptr;
    void (*mesh)(EEContext&, const MeshDraw&) = nullptr;
};
// Installs the observer (nullptr / empty members: none, the default). Host-only, no guest effect.
void set_draw_observer(const DrawObserver* observer) noexcept;
// The installed observer (nullptr: none); the MatFX bridges (bridges.cpp) report their mesh draws through it.
const DrawObserver* draw_observer() noexcept;

}  // namespace mesh

// --- the 21 functions (leaf first) -------------------------------------------------------------------------
// Each takes the guest registers as the original does ($a0.. as documented; host callers pass the typed
// arguments, which are written to the argument registers sign-extended first) and returns $v0 where the
// original returns a value.

// [texture filter shadow] TEX1_1 shadow (gp-17040) bits 5..8 from the RwTextureFilterMode in $a0 (2..6).
void sub_49CA50(EEContext& ctx, u32 filter_mode);
// [material colour upload] One quadword at the packet write pointer: the RGBA bytes at $a0 as floats, r/g/b
// x $f12 (the bridge passes 1/255 untextured, 0x3B011B50 = 1/507.5 textured) and alpha x 0x3B011B50.
void sub_49CAB0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [surface properties upload] One quadword: {ambient, specular, diffuse} x 255.00002 and $f12 (spExtra).
void sub_49CBD0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [raster TEX0 halves] *tex0_hi_out = ext +8, *tex0_lo_out = ext +12 of the raster's sky extension; returns the raster.
void sub_4F1E20(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [raster TEX1] *out = the raster's TEX1 (MXL/LCM/K from the extension) with MMAG/MMIN for filter mode $a2.
void sub_4F1E40(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [RpAtomicPS2AllPrimTypeTransTypeSetupFunc] prim type (pd +41) and transType (pd +40) from the mesh header
// flags, the camera bits and the frustum result ($a1: 2 inside, else clip bit 2).
void RpAtomicPS2AllPrimTypeTransTypeSetupFunc(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [instance test] Object identifier (pd +24: mesh header serial | geometry flags << 16 | morph count << 24) and
// the object instance flags (pd +20) of an atomic ($a0) against its resEntry: 4 when only the low 16 bits
// differ, 8 otherwise / 8 everything locked / 2 + the lock bits << 3, 4 for an interpolated morph change.
void sub_4A0480(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [light one] One light ($a0) into the light block ($a1 = the inverse-LTM record of sub_4A06C0's 0x80 frame,
// $f12/$f13 = its scale and inverse scale): ambient / directional / point / spot / soft spot.
void sub_49FF10(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [light callback] worldForAllLights / sector tie callback: lights with flag 1 (light atomics) only. Returns the light.
void sub_4A0430(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [atomic lights] For a lit geometry (flag 0x20): the inverse LTM, its scale, the world lights (worldForAllLights)
// and every local light of every world sector the atomic touches whose sphere reaches it (frame counter
// 0x96007A stamps each light once).
void sub_4A06C0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [stock atomic set-up callback] mesh header, resEntry array, morph data, the object matrix (*matrix_ref = LTM x
// the camera's view matrix at camera +32), the frustum test of the bounding sphere, prim/transType, instance
// test, lights.
// Returns 1.
void sub_4A09D0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [_rpSkinMatrixUpdating] The bone palette ($v0 = the palette 0x95DE1C) of a skinned atomic ($a0, skin $a1):
// identity rows when the atomic has no hierarchy; else per bone LTM x skin-to-bone (VU0), x inverse atomic LTM
// unless the hierarchy flags say the matrices are already local (2) or no inverse is needed (0x4000).
void _rpSkinMatrixUpdating(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [skin palette upload, partitioned] The bone palette of one mesh ($a0 = the PipeData): a cnt tag and STCYCL
// 1,1 / UNPACK V4-32 to VU1 0x2BC, then each bone of the mesh's ranges at its slot (the partition record
// 0x95DE38). Returns 1.
void sub_46B8E0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [skin object set-up callback] sub_4A09D0 inlined for a skinned atomic, then the palette (_rpSkinMatrixUpdating) uploaded
// whole after a cnt tag + STCYCL/UNPACK V4-32 to VU1 0x2BC. Returns 1 (0 for a geometry without meshes).
void sub_46EB90(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [openVU1SetupPktNew] The per-object VIF packet: cnt + UNPACK of 6 + light quadwords + 5 template qw, the
// matrix ($a0, 0 -> none, BASE 1014) as 4 rows, the light block ($a1, $a2 quadwords). Returns 1.
void openVU1SetupPktNew(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [texture cache: speculative placement] For a raster not yet resident: the upload callback (raster, 1) and the
// TBP/CBP patch of its TEX0 in the extension.
void sub_4F0F30(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [RpSkyTexCacheAccessRaster] Makes a raster resident (upload callback (raster, 0)), patches TEX0 TBP/CBP and
// emits the TEX0 (+ MIPTBP1/2) A+D packet, or the TEX1 one when $a1 = 0. Returns 1 (0: no raster).
void RpSkyTexCacheAccessRaster(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [RpMeshPS2AllBridgeCallBack] The stock material bridge (see the data flow above). Returns 1.
void RpMeshPS2AllBridgeCallBack(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [MatFX/skin bridge dispatcher] The skin bridge table 0x6B4EE4 entry chosen by the material's skin effect,
// with the material pipeline's code array advanced by 16 entries per effect for the call.
void sub_46EA80(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [PS2AllNodeBody] The object node (see the data flow above). Returns 1 (0 when instancing failed).
void PS2AllNodeBody(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [AtomicDefaultRenderCallBack] RxPipelineExecute(atomic +0x6C or the global default, atomic, 1); the atomic, or 0.
void AtomicDefaultRenderCallBack(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

}  // namespace p3fes::game
