// Phase 5 slice render_world: RenderWare's world on the PS2 driver -- world sectors and their render walk, atomics,
// clump render, geometry locks and the mesh-build helpers, the PS2All instancing that turns vertex data into VIF
// UNPACK clusters, and the MatFX / skin / PDS set-up (docs/ANALYSIS/22_rendering.md sections 2.2, 2.3, 3.1, 3.3 and
// 7.3 c7 / c8; queue docs/ANALYSIS/queue_rendering.txt, groups [matfx] [skin] [pds-bridge] [pds-2d] [rpworld-atomic]
// [rpworld-sector] [ps2all]).
//
// Data flow:
//
//   field world (K_FldSrc_DrawFieldOpaque):
//     RpWorldRender(world) -> sub_49C330(camera, WorldSectorRender, world): the frustum walk (recompiled)
//       WorldSectorRender(sector)
//         worldSectorRenderDispatch: the world's sector callback (world +104, set by worldSetSectorRenderCallBack; default
//                     _rpSectorDefaultRenderCallBack: RxPipelineExecute(sector +124 / world +108 / the PS2All
//                     global default, sector, 1))
//         per atomic tied to the sector (+56) with the render flag and not stamped this frame (atomic +96 vs
//         0x960078): atomicGetWorldBoundingSphere (world bounding sphere), sub_4C9DF0 (frustum), the atomic's render callback (+72)
//   models: RpClumpRender walks a clump's atomics the same way (render flag, frame LTM, callback)
//   lights: worldForAllLights (every light of the current world), worldSectorForAllLights (the lights tied to a sector), the sector
//           light callback ps2AllSectorLightCB (sub_49FF10 for a world-flagged light)
//   PS2All (inside PS2AllNodeBody, render_mesh): a mesh without a current resEntry goes to PS2AllNodeInstance:
//       ps2AllInstanceSizes / ps2AllMatClusterLayout: the cluster layout and sizes of the mesh (strip / list splitting per VU1 batch)
//       ps2AllInstanceDmaChain: the resEntry's DMA tags and UNPACK headers
//       the instance callback (material pipe +12): RpMeshPS2AllInstanceCallBack -> ps2AllSectorInstance (world sector) /
//       ps2AllAtomicInstance (atomic); skinned: RpPDS_G3d_Skin_PS2AllInstanceCallBack = ps2AllAtomicInstance + the weights skinInstanceWeights
//       the data cache written back (SyncDCache)
//   Im3D: ps2AllIm3DObjectSetup (object set-up), ps2AllIm3DInstance (instance), sub_49C7A0 (render test); sub_4A35C0 attaches a
//         pipeline to an object's slot array
//   world sectors: ps2AllSectorObjectSetup (sector object set-up: lights, resEntry array, instance test)
//   MatFX: matfxSetSectorPipeline / matfxSetAtomicPipeline pick the MatFX PDS pipelines, matfxEffectMatrix the cached effect matrix, sub_4687E0
//          (via sub_469DC0) combines two rasters into a new texture
//   PDS 2D: pds2DObjectSetupA / pds2DObjectSetupB / pds2DObjectSetupC, the object set-ups of the three 2-D PDS pipelines (one compiled body)
//   Rt2d: sub_46BAB0 / sub_46BD00 (tagged [skin] in the queue) draw a chain of Rt2d paths through the pipelines at
//         0x95F040 / 0x95F050
//   mesh build: the tri-strip helpers triStripTriangleEdge / triStripTakeTriangle / triStripExtend and the material sort meshSortCompare (load time)
//
// Not taken from the slice's groups (they allocate through the RW heap pointers 0x960178.. in their own bodies, or
// print): sub_4933D0, sub_495CF0, sub_4967A0, sub_4982B0, sub_497600, sub_498720, sub_498E70, sub_49E5A0, sub_4A08F0,
// sub_4A0CE0 (heap); sub_46F400, sub_470200, sub_470E10 (printf).
//
// Register contract (docs/PHASE5_AGENT_BRIEF.md, waves 6 and 7): every check point can preempt the thread and the
// kernel then saves the whole register file in guest memory, callees spill what they receive, and game code reads
// registers a callee left behind. So these bodies are register-faithful: at every check point, every call and every
// return each GPR (128 bits), HI/LO, FPR, ACC and FCR31 holds what the original holds there, and the prologues write
// the original spills. The bodies work on the guest registers directly (the Cpu view in world.cpp, one named variable
// per register, as mesh.cpp / ptank.cpp), with the data flow named in comments; the per-block virtual time follows
// the recompiled bodies (ADR-0013).
//
// Names: every function keeps its symbols/functions.json name (sub_* except the RW names); a bracketed name is a
// role (proposed in symbols/deltas/render_world.sym, not imported). The recompiled program's entry points
// (`fn_<name>_<addr8>`) are defined in src/render/world.cpp.
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"

namespace p3fes::game {

namespace world {

// --- guest addresses (obs: instructions) ---------------------------------------------------------------------
inline constexpr u32 kGp = 0x007D2CF0u;
inline constexpr u32 kRwGlobals = 0x00960070u;     // +0 the current camera, +4 the current world, +8 the frame counter
inline constexpr u32 kRenderFrame = 0x00960078u;   // u16 render frame stamp (atomic +96 is compared with it)
inline constexpr s32 kGpWorldModule = -17552;      // plugin offset of the world module in the RW globals (+4: worlds)
inline constexpr s32 kGpPs2AllModule = -16840;     // plugin offset of the PS2All module (+64: the default pipeline)
inline constexpr s32 kGpCamFlags = -16892;         // byte: the camera's transType bits (render_mesh)
inline constexpr s32 kGpMeshModule = -17568;       // plugin offset of the mesh module (+39 + mode: the header flag table)
inline constexpr s32 kGpSectorResEntries = -17512; // plugin offset of a world sector's resEntry array
inline constexpr s32 kGpFxCacheRecord = -17804;    // matfxEffectMatrix's cache key: the object's +8 record
inline constexpr s32 kGpFxCacheFrame = -17808;     // ... the frame
inline constexpr s32 kGpFxCacheStamp = -17800;     // ... the render frame stamp (64-bit)
inline constexpr u32 kFxMatrix = 0x0095C460u;      // matfxEffectMatrix's cached matrix (+12: its type bits)

}  // namespace world

// --- the functions (host entry points: the typed arguments are written to $a0.. sign-extended first, the result
// is $v0) ---------------------------------------------------------------------------------------------------------

// world sectors
u32 worldSectorRenderDispatch(EEContext& ctx, u32 sector);  // [RpWorldSectorRender] the current world's sector callback (+104), tail jump
void worldSetSectorRenderCallBack(EEContext& ctx);  // [register ABI] [RpWorldSetSectorRenderCallBack] (0 = the default) -> world
u32 RpWorldRender(EEContext& ctx, u32 world);  // sub_49C330(camera, WorldSectorRender, world) -> world
void _rpSectorDefaultRenderCallBack(EEContext& ctx);  // [register ABI] RxPipelineExecute(sector / world / global pipe) -> sector or 0
u32 worldForAllLights(EEContext& ctx, u32 callback, u32 data);  // [RpWorldForAllLights] current world, until 0 -> 1
void worldSectorForAllLights(EEContext& ctx);  // [register ABI] [RpWorldSectorForAllLights] -> sector
void worldForAllSectors(EEContext& ctx);  // [register ABI] [RpWorldForAllWorldSectors] BSP order -> world
void worldSectorGetWorld(EEContext& ctx);  // [register ABI] [RpWorldSectorGetWorld] -> world or 0
u32 WorldSectorRender(EEContext& ctx, u32 sector);  // the sector, then its visible atomics not drawn this frame -> sector
void sub_499140(EEContext& ctx);  // [register ABI] [geometry unlock: mesh build callback] -> geometry or 0

// atomics, clumps, geometry
void atomicGetWorldBoundingSphere(EEContext& ctx);  // [register ABI] [RpAtomicGetWorldBoundingSphere] -> &atomic->worldSphere (+44)
void RpClumpRender(EEContext& ctx);  // [register ABI] every atomic with the render flag -> clump, or 0 when a callback failed
void geometryLock(EEContext& ctx);  // [register ABI] [RpGeometryLock] -> geometry
u32 sub_498E30(EEContext& ctx, u32 geometry);  // sub_498720(geometry, 0, 1), tail call
void meshHeaderForAllMeshes(EEContext& ctx);  // [register ABI] [RpMeshHeaderForAllMeshes] -> header
void triStripTriangleEdge(EEContext& ctx);  // [register ABI] [tri-strip] the triangle's edge (va, vb) or 0
void meshSortCompare(EEContext& ctx);  // [register ABI] [mesh sort compare] qsort comparator
void triStripTakeTriangle(EEContext& ctx);  // [register ABI] [tri-strip] take a triangle out of the buckets
void triStripExtend(EEContext& ctx);  // [register ABI] [tri-strip] extend a strip -> triangles taken

// MatFX / skin / PDS
void matfxSetSectorPipeline(EEContext& ctx);  // [register ABI] [MatFX world sector pipe] sector +124 = PDS 0x1100F / 0x11010
void matfxSetAtomicPipeline(EEContext& ctx);  // [register ABI] [MatFX atomic pipe] atomic +108 = PDS 0x1100D / 0x1100E
void RpPDS_G3d_Skin_PS2AllInstanceCallBack(EEContext& ctx);  // [register ABI] atomic instance + weights -> 1

// PS2All
void RpMeshPS2AllInstanceCallBack(EEContext& ctx);  // [register ABI] sector ps2AllSectorInstance / atomic ps2AllAtomicInstance
void ps2AllSectorLightCB(EEContext& ctx);  // [register ABI] [sector light callback] world-flagged lights into the light block -> light
void sub_49C7A0(EEContext& ctx);  // [register ABI] [Im3D render test] -> 0 (no vertices) / 1
void ps2AllIm3DObjectSetup(EEContext& ctx);  // [register ABI] [Im3D object set-up] matrix, prim, transType
void PS2AllNodeInstance(EEContext& ctx);  // [register ABI] (re)instance one mesh -> the instance callback's result
void sub_4A35C0(EEContext& ctx);  // [register ABI] [attach a pipeline to a slot] -> object or 0
void ps2AllIm3DInstance(EEContext& ctx);  // [register ABI] [Im3D instance] the vertices into the clusters -> 1
void ps2AllMatClusterLayout(EEContext& ctx);  // [register ABI] [PS2All cluster layout of a material pipeline] -> 1 / 0
// [PS2All instance sizes] the cluster layout of one mesh -> the resEntry size; out: vertices / batch / clusters
void ps2AllInstanceSizes(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
void ps2AllInstanceDmaChain(EEContext& ctx);  // [register ABI] [PS2All instance: DMA chain and UNPACK headers] -> 1
void ps2AllSectorInstance(EEContext& ctx);  // [register ABI] [world sector instance] the sector's streams into the clusters -> 1
void ps2AllAtomicInstance(EEContext& ctx);  // [register ABI] [atomic instance] the geometry's streams into the clusters -> 1
void pds2DObjectSetupA(EEContext& ctx);  // [register ABI] [PDS 2D object set-up] (template 0x6B5790, mode 6)
void pds2DObjectSetupB(EEContext& ctx);  // [register ABI] [PDS 2D object set-up] (template 0x6B58E0, mode 6)
void pds2DObjectSetupC(EEContext& ctx);  // [register ABI] [PDS 2D object set-up] (template 0x6B5A30, mode 4)
void ps2AllSectorObjectSetup(EEContext& ctx);  // [register ABI] [world sector object set-up] -> 1
void matfxEffectMatrix(EEContext& ctx);  // [register ABI] [MatFX effect matrix] cached 4x4 -> frame
void sub_46BAB0(EEContext& ctx);  // [register ABI] [Rt2d path draw, outline] the path chain -> path or 0
void sub_46BD00(EEContext& ctx);  // [register ABI] [Rt2d path draw, filled] the path chain -> path or 0
void skinInstanceWeights(EEContext& ctx);  // [register ABI] [skin weights at instance] per index, 16 bytes each
void sub_4687E0(EEContext& ctx);  // [register ABI] [MatFX raster combine] -> the new texture

}  // namespace p3fes::game
