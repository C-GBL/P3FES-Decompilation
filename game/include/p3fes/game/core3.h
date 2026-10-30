// Phase 5 slice render_core3: the third pass over RenderWare's core and the PS2 sky driver below the draw path
// (docs/ANALYSIS/22_rendering.md sections 2-5; queue_rendering.txt rows tagged [rt2d] [rwcore] [renderstate] [raster]
// [upload] [im3d] [rxheap]).
//
// What is here, by group:
//   [rwcore]  the matrix combine ops (scale / translate / transform, ortho-normalise), the frame hierarchy (LTM sync,
//             RwFrameGetLTM, transform + dirty-list link), the resource heap (first-fit allocate, split, free + merge),
//             the camera / raster entry points over the device's standard functions (0x9600B8 + 4 * index: begin /
//             end update, clear, show raster, lock / unlock, sub-raster, image <-> raster), the image box resampler,
//             the texture name and validation calls.
//   [rt2d]    the Rt2d toolkit of the Maestro UI: the CTM stack (0x95EDF0 / depth 0x95EE70), the device matrix and
//             flattening tolerance, path flattening (Bezier split / recursive flatten / close / bbox), the path-node
//             chain destroy, brush colour mixing, and the object renderers (string, pick region, shape -- path nodes
//             or an atomic --, scene with its depth sort, the Maestro scene call).
//   [renderstate] the driver's RwRenderStateGet (0x960094), answering from the GS register shadows.
//   [raster]  the CPU swizzles of a locked raster (PSMT8 / PSMT4, both directions), the driver's raster unlock and
//             palette lock / unlock, the frame-buffer raster binding, the scissor clips of the blits.
//   [upload]  the per-camera VU1 constant block, the PATH2 contiguous upload chain and the PATH3 row upload chain.
//   [im3d]    RwIm3DTransform / RenderPrimitive / RenderIndexedPrimitive over the Im3D pipelines.
//   [rxheap]  RxPipelineExecute, the pipeline lock (scratch blocks per node) and its bump allocator.
// Kept recompiled (core3.cpp calls them through their generated entry points): the functions of these groups that
// call RwMalloc / RwFree / RwRealloc / the freelists through the engine's memory function pointers (0x960178 ..
// 0x96018C: sub_4AB0E0, sub_4C1E70, sub_4C47E0, sub_4C4930, sub_4CBF20, sub_4CC1D0, sub_4E4E90, sub_4F61C0, and
// sub_4EFA00, which also brackets the texture-cache allocator with DIntr / EIntr), and the four raster blits / lock
// (sub_4DE0A0, sub_4E53E0, sub_4E6D60, sub_4E8610: 3.1 - 6.5 KB each, the GS store-image / texture-cache / DMA
// callees) -- see docs/INTEGRATION_LOG.md.
//
// Register contract (docs/PHASE5_AGENT_BRIEF.md, waves 6 and 7): every check point can preempt the thread and the
// kernel then saves the whole register file in guest memory, callees spill what they receive and game code reads
// registers a callee left behind. So these bodies are register-faithful: at every check point, every call and every
// return each GPR (128 bits), HI/LO (both pipes), FPR, ACC and FCR31 holds what the original holds there, and the
// prologues write the original spills (the compiler's 128-bit frame slots included). The bodies work on the guest
// registers directly (the Cpu view in core3.cpp, one named variable per register, as mesh.cpp / ptank.cpp), with the
// data flow named in comments; the per-block virtual time follows the recompiled bodies (ADR-0013).
//
// Names: every function keeps its symbols/functions.json name; a bracketed role is a proposal (RenderWare 3.x API names
// where the behaviour matches the toolkit's contract; not imported).
// The recompiled program's entry points (`fn_<name>_<addr8>`) are defined in src/render/core3.cpp; each function below
// takes its guest arguments as 64-bit register values ($a0.., then $t0..) and returns $v0 (for the void ones, $v0 is
// whatever the original left).
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"

namespace p3fes::game {

// --- [rwcore] matrices, frames, the resource heap, cameras, rasters, images, textures ---
u64 sub_4C2FB0(EEContext& ctx, u64 matrix);  // [RwMatrixOptimize-like wrapper]: tail call into sub_4C2330
u64 sub_4C33D0(EEContext& ctx, u64 matrix, u64 scale, u64 combine);  // [RwMatrixScale]: combine 0 replace, 1 pre-concat, 2 post-concat
u64 sub_4C35D0(EEContext& ctx, u64 matrix, u64 translation, u64 combine);  // [RwMatrixTranslate]
u64 sub_4C3760(EEContext& ctx, u64 matrix, u64 transform, u64 combine);  // [RwMatrixTransform]: through sub_4C2F30 into a frame buffer
u64 sub_4C6BE0(EEContext& ctx, u64 out, u64 points, u64 count, u64 matrix);  // [RwV3dTransformPoints]: the vector module's function +8; returns out
u64 sub_4C6C60(EEContext& ctx, u64 out, u64 vectors, u64 count, u64 matrix);  // [RwV3dTransformVectors]: the vector module's function +16
void sub_4C6D60(EEContext& ctx, u64 block, u64 size);  // [resource heap: split a free block after `size` bytes]
void sub_4C6E60(EEContext& ctx, u64 data);  // [resource heap: free a block (header at data - 32), merge neighbours]
u64 sub_4C6F30(EEContext& ctx, u64 heap, u64 size);  // [resource heap: first-fit allocation from the hint]
u64 RwCameraEndUpdate(EEContext& ctx, u64 camera);  // tail call through camera +28
u64 RwCameraBeginUpdate(EEContext& ctx, u64 camera);  // tail call through camera +24
u64 RwCameraClear(EEContext& ctx, u64 camera, u64 colour, u64 mode);  // the device's camera clear (0x96010C)
u64 RwCameraShowRaster(EEContext& ctx, u64 camera, u64 dev, u64 flags);  // RwRasterShowRaster(camera +96, ...)
u64 sub_4CB2F0(EEContext& ctx, u64 frame);  // [RwFrameGetLTM]: syncs a dirty hierarchy, returns frame + 80
u64 sub_4CB7F0(EEContext& ctx, u64 frame, u64 transform, u64 combine);  // [RwFrameTransform]: matrix combine + dirty-list link
u64 sub_4CDC70(EEContext& ctx, u64 raster, u64 image);  // [RwRasterSetFromImage]: device standard 6
u64 sub_4CDCE0(EEContext& ctx, u64 image, u64 raster);  // [RwImageSetFromRaster]: device standard 7
u64 sub_4CDD50(EEContext& ctx, u64 image, u64 type, u64 width, u64 height, u64 depth, u64 format);  // [RwImageFindRasterFormat]: device standard 9
u64 sub_4CDE00(EEContext& ctx, u64 raster);  // [RwRasterUnlock]: device standard 16
u64 RwRasterShowRaster(EEContext& ctx, u64 raster, u64 dev, u64 flags);  // resource purge + the device's show raster
u64 sub_4CE050(EEContext& ctx, u64 raster, u64 parent, u64 rect);  // [RwRasterSubRaster]: device standard 12
u64 sub_4CE200(EEContext& ctx, u64 raster, u64 level, u64 flags);  // [RwRasterLock]: device standard 15, returns the pixels
void sub_4CF3B0(EEContext& ctx, u64 frame, u64 flags);  // [_rwFrameSyncHierarchyLTM: a sibling chain and its children]
void sub_4CF4C0(EEContext& ctx, u64 root);  // [_rwFrameSyncHierarchyLTM(root)]
u64 sub_4D0FD0(EEContext& ctx, u64 texture, u64 name);  // [RwTextureSetName]: strncpy 32, RWERROR when too long
u64 sub_4D13E0(EEContext& ctx, u64 a, u64 b, u64 c);  // [texture module function +44 as a boolean]
u64 sub_4C2330(EEContext& ctx, u64 dst, u64 src);  // [RwMatrixOrthoNormalize]
void sub_4CE3A0(EEContext& ctx, u64 image, u64 x0, u64 x1, u64 row);  // [image resample: box sample of one row span]; out in $t0
void sub_4CE9A0(EEContext& ctx, u64 image, u64 x0, u64 x1, u64 y0);  // [image resample: box sample of one output pixel]; y1 in $t0, out in $t1
u64 sub_4CEC10(EEContext& ctx, u64 dst, u64 src);  // [RwImageResample-like]: every destination pixel a box sample of the source

// --- [rxheap] the pipeline executor and its scratch memory ---
u64 RxPipelineExecute(EEContext& ctx, u64 pipeline, u64 data, u64 lock);  // runs the first node's body with the execution globals set
u64 sub_4F3150(EEContext& ctx, u64 size);  // [the pipeline scratch bump allocator (gp-16820 / gp-16824)]
u64 sub_4F5D30(EEContext& ctx, u64 node, u64 unused, u64 out);  // [a node's output link record]
u64 sub_4F62D0(EEContext& ctx, u64 node, u64 prev, u64 pipeline);  // [lock one node's scratch block]
u64 sub_4F6890(EEContext& ctx, u64 pipeline);  // [RxPipelineLock-like: lock every node]

// --- [im3d] the Im3D entry points ---
u64 sub_4F1ED0(EEContext& ctx, u64 vertices, u64 count, u64 matrix, u64 flags);  // [RwIm3DTransform]
u64 sub_4F1FD0(EEContext& ctx, u64 type, u64 indices, u64 count);  // [RwIm3DRenderIndexedPrimitive]
u64 sub_4F2150(EEContext& ctx, u64 type);  // [RwIm3DRenderPrimitive]

// --- [renderstate] the render-state getter ---
u64 sub_4D78B0(EEContext& ctx, u64 state, u64 out);  // [RwRenderStateGet of the sky driver (0x960094)]

// --- [upload] the per-camera VU constants and the texture upload chains ---
void sub_4EEC20(EEContext& ctx, u64 camera);  // [the per-camera VU1 constants (0x965910..0x965A30), gp-16892 bit 3]
u64 skyFillInPktForUpLoadAlignedContiguousRectangle(EEContext& ctx, u64 packet, u64 address, u64 bytes);  // the PATH2 upload chain of a contiguous block
void sub_4EF770(EEContext& ctx, u64 width, u64 rows, u64 address, u64 tbp);  // [the PATH3 row-by-row upload chain]; tbw $t0, bpp $t1, psm $t2, stride $t3

// --- [raster] swizzles, lock / unlock, frame-buffer binding, scissor clips ---
void sub_4DD480(EEContext& ctx, u64 lock);  // [swizzle a PSMT8 lock buffer in 4-row bands]
void sub_4DD700(EEContext& ctx, u64 lock);  // [swizzle a PSMT4 lock buffer]
void sub_4DDAA0(EEContext& ctx, u64 lock);  // [unswizzle PSMT8]
void sub_4DDD30(EEContext& ctx, u64 lock);  // [unswizzle PSMT4]
u64 sub_4DECE0(EEContext& ctx, u64 unused, u64 raster, u64 flags);  // [the driver's raster unlock (standard function 16)]
u64 sub_4DEF10(EEContext& ctx, u64 out, u64 raster, u64 mode);  // [the driver's palette lock (standard function 23)]
u64 sub_4DEFD0(EEContext& ctx, u64 unused, u64 raster);  // [the driver's palette unlock (standard function 24)]
void sub_4E2F10(EEContext& ctx, u64 unused);  // [bind the frame-buffer rasters to the draw buffer]
u64 sub_4E4A90(EEContext& ctx, u64 src, u64 dst);  // [clip a 1:1 blit against the scissor 0x965840]
u64 sub_4E4C20(EEContext& ctx, u64 src, u64 dst);  // [clip a scaled blit against the scissor]

// --- [rt2d] the Rt2d toolkit: CTM stack, paths, brushes, scenes, shapes ---
u64 sub_4A55B0(EEContext& ctx, u64 brush, u64 c2, u64 c3, u64 c1);  // [Rt2dBrush colour set-up]: c0 $t0, multiplier $t1, offset $t2
void sub_4A9A70(EEContext& ctx, u64 font);  // [tail call through font +312]
u64 sub_4AAB40(EEContext& ctx, u64 matrix);  // [Rt2dCTMPush: matrix x CTM, or a copy]
u64 sub_4AAC70(EEContext& ctx, u64 matrix);  // [Rt2dCTMPush of a copy of `matrix`]
void sub_4AAD50(EEContext& ctx);  // [Rt2dCTMPop]
u64 sub_4AB0C0(EEContext& ctx);  // [Rt2dCTMRead]
void sub_4AB910(EEContext& ctx, u64 points, u64 left, u64 right);  // [split a cubic Bezier at t = 1/2]
void sub_4ABA20(EEContext& ctx, u64 dst, u64 points, u64 budget);  // [flatten a cubic Bezier]
u64 sub_4AC020(EEContext& ctx, u64 path, u64 box);  // [Rt2dPathGetBBox-like]
u64 sub_4AC390(EEContext& ctx, u64 node);  // [destroy a path-node chain, recursive]
u64 sub_4AE690(EEContext& ctx, u64 scene);  // [sort the scene's children by depth]
u64 sub_4AB8C0(EEContext& ctx);  // [reset the scratch path 0x95ED88]
u64 sub_4AB6A0(EEContext& ctx, u64 path);  // [Rt2dPathClose on the flattened path]
u64 sub_4ABD50(EEContext& ctx, u64 dst, u64 src);  // [Rt2dPathFlatten]
u64 sub_4AAE60(EEContext& ctx);  // [the Rt2d device matrix (0x95EF10)]
void sub_4AA2C0(EEContext& ctx);  // [the flattening tolerance in $f0]
u64 sub_4AD750(EEContext& ctx, u64 string);  // [Rt2dObjectString render]
u64 sub_4AE2F0(EEContext& ctx, u64 region);  // [Rt2dPickRegion update]
u64 sub_4A6600(EEContext& ctx, u64 path, u64 brush);  // [stroke a path: sub_46BD00]
void sub_4ACE70(EEContext& ctx, u64 path, u64 brush);  // [fill a path: tail call into sub_46BAB0]
u64 sub_4AF9D0(EEContext& ctx, u64 shape, u64 multiply, u64 offset);  // [Rt2dShape render]
u64 sub_4ADF30(EEContext& ctx, u64 object, u64 multiply, u64 offset);  // [Rt2dObject render by type]
u64 sub_4AE960(EEContext& ctx, u64 scene, u64 multiply, u64 offset);  // [Rt2dSceneRender]
u64 sub_4AE940(EEContext& ctx, u64 scene);  // [Rt2dSceneRender with the default colours]
u64 sub_4B5330(EEContext& ctx, u64 maestro);  // [a Maestro's scene render (+36)]

}  // namespace p3fes::game
