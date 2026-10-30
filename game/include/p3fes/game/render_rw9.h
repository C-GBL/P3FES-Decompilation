// Slice render_rw9: RenderWare, ninth pass -- what render_rw4..8 left of the band 0x467FD0-0x4F1E10 that touches no
// hardware register in its own body, ordered by reach on the six replay routes: 165 functions, started from
// p3fes_handgen and made readable (game/src/render/render_rw9.cpp).
//
// Groups (sub_* keep their symbols/functions.json names; proposed names in brackets, symbols/deltas/render_rw9.sym; RW
// 3.x public API names only where the body does what that API does):
//   * The clump / atomic / geometry core (0x4908D0-0x4954C0): RpAtomicCreate (sub_491880), RpAtomicSetGeometry
//     (sub_4919B0), RpAtomicClone (sub_491B40), RpClumpClone (sub_491CC0) with its per-atomic callback, the atomic
//     destroy callback, RpGeometryCreate (sub_493710), RpGeometryDestroy (sub_493B60) and the free behind it, the
//     stream readers of a clump (sub_4920A0: its frame list, geometry list, atomics, lights, cameras), of an atomic, a
//     geometry list and a geometry (sub_493CB0), the material list's free and stream read (sub_495260, sub_4954C0).
//   * The world (0x490050, 0x49A290-0x4A4D60): RpWorldStreamRead, RpWorldCreate / RpWorldDestroy, the clump-copy
//     callback; the PS2 native-data plugin's instance list free and destructor.
//   * RpMatFX's material effects (0x467FD0-0x469840): the material stream read, the atomic flag read,
//     RpMatFXMaterialSetEffects and the dual-texture setters.
//   * PTank's geometry set-up (0x4734D0-0x47A210): the atomic create / destroy and extension destructor, the GS packet
//     field writer, the instance layout and packet flush, the per-atomic set-up choosing the sprite, instancing or
//     generic geometry, the 2D / 3D sprite geometries.
//   * Rt2d (0x4A6630-0x4B6040): Rt2dOpen / Rt2dClose; the path layer (create, sList form, moveto, the module open, the
//     stream readers); the shapes (the fill geometry builder, the shared representations: stream read, build,
//     geometry, release; the shape's stream read and destroy); the scene (stream read, unlock, destroy, the object
//     dispatch by type); the maestro (create / init / destroy, its animation / button / label / message lists and their
//     stream readers, the keyframe interpolation into the props and their commit, the per-animation update and rewind).
//   * Dictionaries and the RtFS manager's helpers (0x4B7630-0x4C06C0): the dictionary schema's init / destruct,
//     RwFsInit, the file-record open, the file system of a path, the exists test.
//   * Engine helpers (0x4C4420-0x4CAAC0): the memory module open / close with the newlib defaults, the default vector
//     transforms and their set-up, the module 1042 open / close, the string helpers (upper / lower case, strchr /
//     strrchr, the string chunk size and read), the absolute-path test, the camera plugin stream registration, the
//     engine's core module registration, the frame root set-up.
//   * The image module and the texture readers (0x4CBA20-0x4D11D0): the module open, the search path and its walk, the
//     file format registry, RwImageRead and RwImageReadMaskedImage, the gamma tables and correction, the pixel copy,
//     the resample to 32 bits, the palettisers; the default texture readers, the raster mip-level fill, the named
//     texture search, the current dictionary.
//   * The sky driver (0x4D82A0-0x4F1E10): RpSkySelectDeepZBuffer and two option setters, the texture plugin's K / L
//     stream read, the raster format rules, the texture mip-chain layout, the sub-raster set-up, the mip-level count,
//     the raster and texture native stream readers, SkySystem (the device-control entry) with its frame / scratch
//     raster helpers and standard-function table, the plugin attach, the raster format from an image, the palette
//     upload (the GS CLUT layout), the palettised image copy, the upload-packet preparation, the texture cache's
//     placement and reset.
//
// The rules the pair tests check (tests/game/test_render_rw9.cpp):
//   * RpGeometryCreate lays out the record as rw9::geometry says: type 8, one reference, the counts, the texture-
//     coordinate sets from the flags (bits 16..23, else 2 for 0x80, 1 for 0x04), the arrays after the plugin-extended
//     record (pre-lit colours, the UV sets, the triangles with material index -1), one morph target, nothing for a
//     native geometry; 65536 vertices or more are refused; a create / destroy round trip frees every block;
//   * RpAtomicClone / RpClumpClone of the live objects share each geometry (one more reference per clone) and give the
//     clump a cloned frame hierarchy with the same atomics;
//   * the image gamma tables follow 255 * (i / 255)^g; the gamma correction maps RGB through the table and keeps alpha;
//     an 8-bit image copied into a 32-bit one expands through its palette;
//   * the sky driver stores a 256-entry CLUT swizzled (the middle 8-entry groups of each 32 swapped) and a 16-entry one
//     in order, 32-bit entries with the alpha halved, 16-bit ones as 1555; a texture raster without format bits gets
//     them from its depth (16 -> 0x01, 24 -> 0x06, 32 -> 0x05, 8 -> 0x21, 4 -> 0x41).
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/render_rw8.h"  // rw8:: (and rw7:: .. rw4::) the records of the earlier passes

namespace p3fes::game {

namespace rw9 {

namespace atomic {                            // an RpAtomic (the atomic free list at engine + gp 0x7CE820)
constexpr s32 kType = 0;                      // 1
constexpr s32 kSubType = 1;
constexpr s32 kFlags = 2;                     // 5: collision test | render
constexpr s32 kPrivateFlags = 3;
constexpr s32 kFrame = 4;                     // the parent frame
constexpr s32 kSync = 16;                     // the frame sync callback
constexpr s32 kRepEntry = 20;                 // the instance data
constexpr s32 kGeometry = 24;
constexpr s32 kSphereX = 28;                  // the bounding sphere (from the geometry's first morph target)
constexpr s32 kSphereY = 32;
constexpr s32 kSphereZ = 36;
constexpr s32 kSphereRadius = 40;
constexpr s32 kWorldSphereX = 44;             // the world-space bounding sphere
constexpr s32 kWorldSphereY = 48;
constexpr s32 kWorldSphereZ = 52;
constexpr s32 kWorldSphereRadius = 56;
constexpr s32 kClump = 60;
constexpr s32 kClumpNext = 64;                // the link in the clump's atomic list
constexpr s32 kClumpPrev = 68;
constexpr s32 kRenderCallback = 72;
constexpr s32 kInterpFlags = 76;              // the morph interpolator
constexpr s32 kInterpStartMorph = 80;         // s16
constexpr s32 kInterpEndMorph = 82;           // s16
constexpr s32 kInterpTime = 84;
constexpr s32 kInterpRecipTime = 88;
constexpr s32 kInterpPosition = 92;
constexpr s32 kRenderFrame = 96;              // u16
constexpr s32 kSectorsNext = 100;             // the world sectors the atomic is in (a list head)
constexpr s32 kSectorsPrev = 104;
constexpr s32 kPipeline = 108;
}  // namespace atomic

namespace geometry {                          // an RpGeometry (96 bytes, then the plugin extensions, then the arrays)
constexpr s32 kType = 0;                      // 8
constexpr s32 kSubType = 1;
constexpr s32 kObjFlags = 2;
constexpr s32 kPrivateFlags = 3;
constexpr s32 kParent = 4;
constexpr s32 kFlags = 8;                     // format: 0x08 pre-lit, 0x04 / 0x80 UV sets, 0x01000000 native
constexpr s32 kLockedSinceInst = 12;          // u16
constexpr s32 kRefCount = 14;                 // s16
constexpr s32 kNumTriangles = 16;
constexpr s32 kNumVertices = 20;
constexpr s32 kNumMorphTargets = 24;
constexpr s32 kNumTexCoordSets = 28;
constexpr s32 kMatList = 32;                  // the material list (rw9::matlist), inline
constexpr s32 kMatListCount = 36;
constexpr s32 kMatListSpace = 40;
constexpr s32 kTriangles = 44;                // 8 bytes each: three vertex indices and the material index
constexpr s32 kPreLit = 48;                   // RGBA per vertex
constexpr s32 kTexCoords = 52;                // up to eight UV sets, 8 bytes per vertex each
constexpr s32 kMesh = 84;                     // the mesh header
constexpr s32 kRepEntry = 88;                 // the instance data
constexpr s32 kMorphTargets = 92;             // 28 bytes each: bounding sphere (+4), points (+20), normals (+24)
}  // namespace geometry

namespace matlist {                           // an RpMaterialList (inline in a geometry or a world)
constexpr s32 kMaterials = 0;                 // the material pointer array
constexpr s32 kCount = 4;
constexpr s32 kSpace = 8;                     // the array's capacity
}  // namespace matlist

namespace image {                             // an RwImage
constexpr s32 kFlags = 0;                     // 1 pixels owned, 2 gamma corrected
constexpr s32 kWidth = 4;
constexpr s32 kHeight = 8;
constexpr s32 kDepth = 12;                    // 4, 8 or 32
constexpr s32 kStride = 16;
constexpr s32 kPixels = 20;
constexpr s32 kPalette = 24;                  // RGBA entries for 4 / 8-bit images
}  // namespace image

namespace raster {                            // an RwRaster (the sky driver's extension at + gp 0x7CEAA8)
constexpr s32 kParent = 0;
constexpr s32 kPixels = 4;
constexpr s32 kPalette = 8;
constexpr s32 kWidth = 12;
constexpr s32 kHeight = 16;
constexpr s32 kDepth = 20;
constexpr s32 kStride = 24;
constexpr s32 kOffsetX = 28;                  // s16, a sub-raster's position in its parent
constexpr s32 kOffsetY = 30;
constexpr s32 kType = 32;                     // 0 normal, 1 Z buffer, 2 camera, 4 texture, 5 camera texture
constexpr s32 kFlags = 33;
constexpr s32 kPrivateFlags = 34;
constexpr s32 kFormat = 35;                   // 0x01 1555, 0x05 8888, 0x06 888, 0x20 / 0x40 palette 8 / 4
constexpr s32 kOrigPixels = 36;
constexpr s32 kOrigWidth = 40;
constexpr s32 kOrigHeight = 44;
constexpr s32 kOrigStride = 48;
}  // namespace raster

}  // namespace rw9

// --- the bodies (register ABI: arguments in $a0.., $f12.., the result in $v0 / $f0) ---------------------------------
void sub_467FD0(EEContext& ctx);  // 0x467FD0 [matFXMaterialStreamRead] -- RpMatFX's material stream read: the effect type (sub_468EA0), then two slots, each a type word and its data -- dual texture 4 (the two blend modes, a texture), environment map 2 (coefficient, frame-buffer alpha, a texture), bump map 1 (coefficient, two textures; 1 / texture width kept at +16); the stream, or 0
void sub_468560(EEContext& ctx);  // 0x468560 [matFXAtomicStreamRead] -- RpMatFX's atomic / world-sector stream read: a 4-byte flag; when set the object's effects are enabled (sub_468DC0); the stream, or 0
void sub_468EA0(EEContext& ctx);  // 0x468EA0 [RpMatFXMaterialSetEffects] -- sets a material's effect type: the extension allocated (144 bytes, cleared) on first use; a changed type releases the old effects (sub_4676C0); the slot types for the type (1 bump, 2 env, 3 bump + env, 4 dual -- blend modes 5 / 6 --, 5 UV transform, 6 UV transform + dual), then sub_469AA0; the material, or 0
void sub_469770(EEContext& ctx);  // 0x469770 [RpMatFXMaterialSetDualTexture] -- sets the dual-texture slot's texture: the slot of type 4 (or 0), the texture's reference count up (+84), the old one destroyed (sub_4D0F00), then the slot's two dirty bits (sub_469A90 2 / 1); the material
void sub_469840(EEContext& ctx);  // 0x469840 [RpMatFXMaterialSetDualBlendModes] -- sets the dual-texture slot's source / destination blend modes (+4 / +8), the slot's dirty bits 10 / 11 (sub_469A90), sub_469BC0; the material
void sub_4734D0(EEContext& ctx);  // 0x4734D0 [ptankAtomicDestructor] -- PTank's atomic extension destructor (atomic + gp 0x7CE770): the first material's texture cleared (sub_494D50), the instance data's packets flushed (sub_475CB0 / sub_475C20) and freed, the extension freed (RwFree) and cleared; $a0
void sub_474260(EEContext& ctx);  // 0x474260 [RpPTankAtomicCreate] -- creates a PTank atomic: an atomic (sub_491880) with a 320-byte extension (RwMalloc), the render callback chained (sub_474160), the data / platform flags, the instance callback or the default layout (sub_473B10 / sub_473600), the create callback (+24), the default constant colour / matrix / UV, the three current render states; the atomic, or 0 (the atomic destroyed)
void sub_474630(EEContext& ctx);  // 0x474630 [RpPTankAtomicDestroy] -- destroys a PTank atomic (a tail call into the atomic destroy sub_491A80)
void sub_474820(EEContext& ctx);  // 0x474820 [ptankSetGsPacketField] -- writes one field of a PTank atomic's GS packet: kind 2 the low 16 bits of the 64-bit word +200, kind 1 the word +184 (the low byte and the top byte) and clears flag 0x10000000; 1, or 0 for another kind
void sub_474F20(EEContext& ctx);  // 0x474F20 [ptankInstanceLayout] -- lays out a PTank atomic's instance buffer from $a1: with a material pipe the per-packet DMA headers and the cluster offsets of each batch (sub_474D30), else the per-property offsets (+84.. +148) for the flags in +168 (the property strides 0x7BC904..)
void sub_475CB0(EEContext& ctx);  // 0x475CB0 [ptankFlushPackets] -- flushes a PTank atomic's DMA packets: for each used batch two forced buffer swaps (_rwDMAForceBufferSwap), unless flag 0x10 of +68
void sub_475D60(EEContext& ctx);  // 0x475D60 [ptankAtomicSetup] -- PTank's per-atomic set-up: picks the geometry and pipeline by the data / platform flags -- the instancing pipe (an empty geometry, render callback sub_47A510), the 2D sprite (sub_478E80) or 3D sprite (sub_47A210) geometry with their callbacks, the generic quads (sub_486340, pipe +20), a custom path through the callback 0x77B254 -- then the instance layout (sub_474F20); 1 / 0
void sub_478E80(EEContext& ctx);  // 0x478E80 [ptankSpr2dGeometryCreate] -- builds a PTank atomic's 2D-sprite geometry: an empty geometry, a material (colour 0.3 / 1 / 1), a one-entry mesh header (sub_4959C0) of $a1 primitives with the material, the material pipe PTank +4, the atomic's pipe PTank +8; 1 / 0
void sub_47A210(EEContext& ctx);  // 0x47A210 [ptankSpr3dGeometryCreate] -- builds a PTank atomic's 3D-sprite geometry: as the 2D one with 4 x $a1 indices, the material pipe PTank +12 and the atomic's pipe PTank +16; 1 / 0
void sub_490050(EEContext& ctx);  // 0x490050 [RpWorldStreamRead] -- reads a world chunk: the struct (version 0x35000..0x37002; a world with an extra count refused, error 0x80000004), one block (RwMalloc, cleared) sized for the world record, its sectors, vertices, pre-lit colours, normals, UV sets and triangles by the format flags, the record (type 7, flags, root type 2, the negated origin, the texture-coordinate set count, empty lists), the material list (chunk 8, sub_4954C0), the root sector -- an atomic sector (chunk 9, sub_48F580) or a plane sector (chunk 10, sub_48FBD0) --, the bounding box, the sectors' set-up (sub_499D30) and render callback, every sector's plugin constructors, the world's extensions (sub_4C5A50 / sub_4C5C30 on 0x77DDD0) and sub_49A080; on a failure the world is destroyed (RpWorldDestroy); the world, or 0
void sub_4908D0(EEContext& ctx);  // 0x4908D0 [clumpCloneAtomicCB] -- RpClumpClone's per-atomic callback: the atomic cloned (sub_491B40), its frame set to the clone of its frame (the frame's +160 link), added to the new clump (sub_491FF0); on a missing frame the clone is destroyed and error 5 set; a failed clone clears the context's ok flag (+8); the atomic, or 0
void sub_490980(EEContext& ctx);  // 0x490980 [clumpGeometryListStreamRead] -- reads a clump's geometry list (chunk 26 body): the struct chunk (version 0x35000..0x37002), the count, a pointer array (RwMalloc), each geometry chunk (15) read (sub_493CB0); on any failure the geometries read so far are released (sub_493B60) and the array freed; the list, or 0
void sub_490D90(EEContext& ctx);  // 0x490D90 [atomicDestroyCB] -- a per-atomic callback that destroys the atomic (sub_491A80) and returns it
void sub_490DC0(EEContext& ctx);  // 0x490DC0 [clumpAtomicStreamRead] -- reads one atomic chunk of a clump: the struct (frame index, geometry index, flags, 16 bytes), a new atomic (sub_491880) with the flags, its frame from the frame list and its geometry from the geometry list -- or a geometry chunk (15) of its own --, then its extensions (sub_4C5A50 on the atomic plugin registry 0x77DCE0) and the right-to-render callback (sub_4C5C30) when one was read; the atomic, or 0 (errors 0x80000004 / 0x8000001A)
void sub_491880(EEContext& ctx);  // 0x491880 [RpAtomicCreate] -- creates an atomic from the atomic free list (engine + gp 0x7CE820): type 1, flags 5 (collision test | render), private flags 1, no frame, the default sync / render callbacks, no geometry, interpolator 0..0 with times 1.0, the world-sector link list empty, then the plugin constructors (sub_4C64B0 on 0x77DCE0); the atomic, or 0
void sub_4919B0(EEContext& ctx);  // 0x4919B0 [RpAtomicSetGeometry] -- sets an atomic's geometry: the new one referenced (sub_493B40), the old one released (sub_493B60); unless flag 1 of $a2 the bounding sphere copied from the geometry's first morph target and, with a frame, the atomic re-synced (sub_49C230 / sub_4CB270); the atomic
void sub_491B40(EEContext& ctx);  // 0x491B40 [RpAtomicClone] -- clones an atomic: a new atomic (sub_491880) with the type, flags, the geometry (referenced) and its bounding sphere, the render callback, the interpolator, the pipeline, then the plugin copy constructors (sub_4C65D0 on 0x77DCE0); the clone, or 0
void sub_491CC0(EEContext& ctx);  // 0x491CC0 [RpClumpClone] -- clones a clump: a new clump (sub_491DE0), its frame hierarchy cloned (sub_4CACE0), every atomic cloned onto the new frames (sub_4908D0 over the atomic list), the frame clone links cleared (sub_4CAD30), the callback (+40) and the plugin copy constructors (sub_4C65D0 on 0x77DD00); the clone, or 0 (destroyed on a failure)
void sub_4920A0(EEContext& ctx);  // 0x4920A0 [RpClumpStreamRead] -- reads a clump chunk: the struct (version 0x35000..0x37002; atomic, light and camera counts), a new clump (sub_491DE0), the frame list (chunk 14, sub_4C7D80) whose first frame becomes the clump's, the geometry list (chunk 26, sub_490980), each atomic (chunk 20, sub_490DC0) linked into the clump, each light (chunk 18 after its frame index, sub_494580) and camera (chunk 5, sub_4C7B90) given its frame and linked, the geometry list released, the frame list freed (sub_4C7D30), the clump's extensions (sub_4C5A50 on 0x77DD00); on any failure the clump is torn down (plugin destructors, its atomics / lights / cameras destroyed, the frame hierarchy destroyed, freed) and error 0x8000001A set; the clump, or 0
void sub_492D50(EEContext& ctx);  // 0x492D50 [geometryFree] -- frees a geometry (reference count about to reach 0): the count held up, its instance data unlocked (geometryLock 0x493370), the plugin destructors (sub_4C6560 on 0x77DD20), the morph-target block (+92) and the mesh header (+32, sub_495260) freed, the geometry freed; 1
void sub_493710(EEContext& ctx);  // 0x493710 [RpGeometryCreate] -- creates a geometry of $a0 vertices and $a1 triangles with format flags $a2: refused above 65535 vertices (error 6) or below 0 triangles; the number of texture-coordinate sets from the flags (bits 16..23, else 2 for 0x80, 1 for 0x04), one block (RwMalloc) sized for the pre-lit colours, the UV sets and the triangles unless native (0x01000000), the mesh header (sub_495300), type 8, reference count 1, the arrays laid out after the plugin-extended record (the registry size; triangle material indices -1), one morph target (sub_492F80), the plugin constructors (sub_4C64B0 on 0x77DD20); the geometry, or 0
void sub_493B60(EEContext& ctx);  // 0x493B60 [RpGeometryDestroy] -- releases a geometry: the reference count (+14) down; at the last reference the instance data unlocked (sub_4C47E0), the mesh (+84, sub_495C80), the plugin destructors (sub_4C6560 on 0x77DD20), the morph targets and mesh header freed and the geometry freed; 1
void sub_493CB0(EEContext& ctx);  // 0x493CB0 [geometryStreamRead] -- reads a geometry chunk: the struct (version 0x35000..0x37002, format / triangle / vertex / morph-target counts), the geometry (RpGeometryCreate) with its extra morph targets, the pre-lit colours, the UV sets, the triangles (vertex indices swapped into place), each morph target's bounding sphere, points and normals, the material list (chunk 8, sub_4954C0), the mesh / extensions (sub_4C5A50 on 0x77DD20) and the unlock (sub_4933D0); the geometry, or 0 (released on a failure)
void sub_495260(EEContext& ctx);  // 0x495260 [materialListDeinit] -- frees a material list: each material released (sub_494CC0) and its slot cleared, the array freed (RwFree), the count and capacity zeroed; the list
void sub_4954C0(EEContext& ctx);  // 0x4954C0 [materialListStreamRead] -- reads a material list chunk: the struct (version 0x35000..0x37002) and count, the array grown (RwRealloc / RwMalloc), the index array; per entry a new material chunk (index < 0: chunk 7, sub_494E30) or a reference to an earlier one (its reference count +24 up), appended (sub_495340) and released once (sub_494CC0); on a failure the list is emptied; the list, or 0
void sub_49A290(EEContext& ctx);  // 0x49A290 [RpWorldDestroy] -- destroys a world: unlinked from the engine's world list (engine + gp 0x7CE860, the link freed), its sectors torn down (sub_499FD0), the material list freed, the root sector freed (an atomic sector sub_499720, a plane sector sub_499850), the plugin destructors (sub_4C6560 on 0x77DDD0), the world freed; 1
void sub_49A400(EEContext& ctx);  // 0x49A400 [RpWorldCreate] -- creates an empty world over the box $a0: the world record (type 7, the material list, root type 2) and one atomic sector covering the box (its lists empty, its bounding boxes = the box), the default sector render callback, linked into the engine's world list, the plugin constructors of world and sector (0x77DDD0 / 0x77DDB0), then sub_49A080; the world, or 0 (torn down on a failure; error 0x80000013 on an allocation)
void sub_49B3F0(EEContext& ctx);  // 0x49B3F0 [worldClumpCopyCB] -- the world extension's clump copy callback: when the source clump is in a world (its + gp 0x7CE870 word) the new clump is added to it (sub_49C240); the new clump
void sub_49E4F0(EEContext& ctx);  // 0x49E4F0 [nativeInstanceListFree] -- frees a PS2 native instance list (a count and the instance blocks): from the last entry, a block still in use by the DMA chain (+0 / +4 set) is only detached (+16 = 0), an idle one is released (sub_49CC30, sub_4C47E0); the list freed (RwFree)
void sub_4A4D60(EEContext& ctx);  // 0x4A4D60 [nativeDataDestructor] -- the native-data plugin's destructor: the object's instance list (+ the plugin offset $a1) freed (sub_49E4F0) when set; the object
void sub_4A6630(EEContext& ctx);  // 0x4A6630 [rt2dShapeFillGeometry] -- fills an Rt2d shape's geometry from its path: the brush's material (made from its texture and colour on first use, referenced after), the scratch index buffer (0x95F57C, grown as needed), then per closed sub-path its vertices (inset by the path's width), pre-lit colours from the brush's four-corner gradient (flag 1) or white, UVs from the brush's UV gradient, the outline triangulated (sub_4B0FA0) and the triangles added with the material (sub_493210 / sub_493230); the vertex / triangle counters advanced; the shape, or 0
void sub_4AA550(EEContext& ctx);  // 0x4AA550 [Rt2dOpen] -- opens Rt2d: the device-flags word cleared, then the module opens -- the PS2 pipes' globals, paths (sub_4AC870), brushes, fonts, objects, the CTM stack, the PS2 pipe (rt2dPS2PipeOpen) -- and the default camera (sub_4AA410 with $a0)
void sub_4AA5C0(EEContext& ctx);  // 0x4AA5C0 [Rt2dClose] -- closes Rt2d: the module closes in reverse order, then the camera cleared (sub_4AA410(0))
void sub_4AB200(EEContext& ctx);  // 0x4AB200 [Rt2dPathMoveto] -- starts a sub-path at ($f12, $f13): when the current sub-path already has nodes a new path is chained after it (sub_4AC570 / sub_4AC5F0) and made current, recursing; else a moveto node {0, x, y} appended to its sList; the path
void sub_4AC570(EEContext& ctx);  // 0x4AC570 [rt2dPathCreate] -- creates an empty Rt2d path from the path free list (0x95ED84): no nodes, closed 0, flat 0, one reference, no next, itself as the current path; converted to its sList form (sub_4AC5F0); the path, or 0
void sub_4AC5F0(EEContext& ctx);  // 0x4AC5F0 [rt2dPathMakeSList] -- turns a path's node array (+0 / +4 count) into a 24-byte-entry sList (sub_4C1D50), the nodes copied and the array freed, +4 = -1; down the chain of sub-paths (+20); the path, or 0
void sub_4AC870(EEContext& ctx);  // 0x4AC870 [rt2dPathOpen] -- opens the path module: the 28-byte path free list (sub_4C3B60) at 0x95ED84 and the scratch path 0x95ED88 made in sList form; 1
void sub_4AC920(EEContext& ctx);  // 0x4AC920 [rt2dPathStreamReadBody] -- reads a path's body over an existing path: the old nodes and sub-paths released, the count / closed / flat flags / inset from the header, the 24-byte nodes read into a new array, the chained sub-paths (chunk 417, sub_4ACB90) when flagged, each sub-path's current pointer set; the path, or 0
void sub_4ACB10(EEContext& ctx);  // 0x4ACB10 [rt2dPathStreamRead] -- reads a path: the 16-byte header, the body (sub_4AC920) when its version is 1; the path, or 0
void sub_4ADBD0(EEContext& ctx);  // 0x4ADBD0 [rt2dObjectDestroyByType] -- destroys an Rt2d object by its type: 4 text (sub_4AD6A0), 3 pick region (sub_4AE1E0), 2 shape (sub_4AF940), 1 scene (sub_4AE4E0); else 0
void sub_4ADE90(EEContext& ctx);  // 0x4ADE90 [rt2dObjectStreamReadByType] -- reads an Rt2d object's body by its type: 4 text (sub_4AD940), 3 pick region (sub_4AE270), 2 shape (sub_4AFFE0), 1 scene (sub_4AEBF0); the object, or 0 for another type
void sub_4AE3B0(EEContext& ctx);  // 0x4AE3B0 [rt2dShapeRepListStreamRead] -- reads a scene's shared shape representations: the count, an array (RwMalloc; error 0x80000013 on failure) and each representation (sub_4AF760); the list, or 0
void sub_4AE5A0(EEContext& ctx);  // 0x4AE5A0 [Rt2dSceneDestroy] -- destroys a scene: as sub_4AE4E0, then the object returned to the object free list (0x95ED8C); 1 when all went well
void sub_4AE790(EEContext& ctx);  // 0x4AE790 [rt2dSceneUnlock] -- unlocks a scene being built (flag 1 of +8): the child pointer array replaced by an sList of 272-byte objects (each copied, sub_4ADC90, and its old record released, sub_4ADC70), the reference sList (+184, 8-byte entries) pointing at each child, the scene's bounds updated (sub_4AE690); the scene
void sub_4AEBF0(EEContext& ctx);  // 0x4AEBF0 [rt2dSceneStreamReadBody] -- reads a scene's children: the count, the child array (zeroed), the scene locked then unlocked (sub_4AE790); each child's header (sub_4ADDB0) and body (sub_4ADE90) read, with the shared representations of $a2 or of the scene's own list (sub_4AE3B0, released after with sub_4AF130); the reference array re-pointed, the bounds (sub_4AE690); the scene, or 0
void sub_4AEEA0(EEContext& ctx);  // 0x4AEEA0 [Rt2dSceneStreamRead] -- reads a scene object: a new object (sub_4ADCA0) initialised as a scene (type 1), its header (sub_4ADDB0) and body (sub_4AEBF0); a failed body destroys it (sub_4AE4E0, the free list 0x95ED8C); the scene, or 0
void sub_4AF130(EEContext& ctx);  // 0x4AF130 [rt2dShapeRepDestroy] -- releases a shared shape representation: the reference count (+4) down; at 0 each node's path and brush released (sub_4AC390 / sub_4A5540), the node sList, the geometry (RpGeometryDestroy), the record freed; 1 when freed, else 0
void sub_4AF210(EEContext& ctx);  // 0x4AF210 [rt2dShapeRepBuildGeometry] -- builds a shape representation's geometry: a geometry (RpGeometryCreate) for the counted vertices and triangles with the format flags $a3, each node's path filled (sub_4A6630, node flag 1) or stroked (sub_4ACE80) with its brush, then the bounding sphere (sub_492E20) and the unlock (sub_4933D0); the geometry, or 0
void sub_4AF340(EEContext& ctx);  // 0x4AF340 [rt2dShapeRepBuild] -- builds a shape representation from its nodes: per node its paths copied (shared when flat, else flattened by sub_4ABD50) and chained, the vertex / triangle / index counts summed (fill: n and n - 3 per path, stroke: 2n and 2n - 2), the geometry built (sub_4AF210, flags 111), the temporary paths released; the geometry stored at +8 and returned
void sub_4AF760(EEContext& ctx);  // 0x4AF760 [rt2dShapeRepStreamRead] -- reads a shape representation: an 8-byte header, a 12-byte record (reference count 1) with a 12-byte-node sList, per node its flags and, when it has a path (flag 4), the path (chunk 417: sub_4AC570 / sub_4AC710 / sub_4ACB10) and the brush (chunk 418: sub_4A5470 / sub_4A6530); the geometry built (sub_4AF340); the representation, or 0
void sub_4AF940(EEContext& ctx);  // 0x4AF940 [rt2dShapeDestroyBody] -- destroys a shape's contents: its representation released (sub_4AF130), the atomic's frame detached and destroyed (sub_492D10 / sub_4CAF80), the atomic destroyed (sub_491A80), the node colour array freed; 1
void sub_4AFFE0(EEContext& ctx);  // 0x4AFFE0 [rt2dShapeStreamRead] -- reads a shape's body: its representation (an index into the shared list $a2, or its own, sub_4AF760), the per-node colour array taken from the geometry's materials, the representation referenced (or an empty one made), a frame (sub_4CAF10) with the current transform (sub_4CB7F0), an atomic (sub_491880) on the frame with the representation's geometry; the shape, or 0
void sub_4B1290(EEContext& ctx);  // 0x4B1290 [rt2dMaestroKeyListStreamRead] -- reads a maestro animation's keyed list: the count, an sList of 8-byte entries {time, animation (chunk 432, sub_4B22B0)}, speed 1.0, the first entry current and the latest-starting entry remembered (+24); the list, or 0
void sub_4B1620(EEContext& ctx);  // 0x4B1620 [rt2dMaestroAnimApply] -- applies a maestro animation's current keyframe to its props (sub_4B2810): the current entry (+20), or the last one (+24) when there is none; the animation, or 0
void sub_4B1BA0(EEContext& ctx);  // 0x4B1BA0 [rt2dAnimPropsCreate] -- creates the props of a scene for animation: a 160-byte-entry sList (sub_4C1D50), one entry per object of the scene (its +4 sList), each with the object pointer and its change flags cleared; the sList
void sub_4B26A0(EEContext& ctx);  // 0x4B26A0 [rt2dAnimPropsCommit] -- commits the changed props to their objects: for each prop marked changed, its matrix (sub_4AE020), colour multiplier (sub_4AE150), colour offset (sub_4AE110) and visibility / scene position (sub_4AE1D0 / sub_4AEF50 / sub_4ADFD0) when their dirty flags are set, the flags cleared
void sub_4B2810(EEContext& ctx);  // 0x4B2810 [rt2dKeyFrameInterpolate] -- interpolates a keyframe into the props by $f12 when 0 < t < 1: per change record (until flag 0x20) the matrix blended (sub_4B24C0, flag 1), the colour multiplier (flag 2) and colour offset (flag 4) lerped into the object (+160.. x 255, +144..) with its changed flag, flag 8 skipped, flag 0x10 the visibility reset; then the props committed (sub_4B26A0); the keyframe list
void sub_4B2AD0(EEContext& ctx);  // 0x4B2AD0 [rt2dAnimPropsInit] -- initialises a props record for a scene: the scene, a 4-byte sList of its objects (filled by the walk sub_4AEB60 with sub_4B2A90), the props sList (sub_4B1BA0); the record, or 0
void sub_4B2BC0(EEContext& ctx);  // 0x4B2BC0 [rt2dMaestroStringsCreate] -- creates the maestro's string buffer: a 1-byte-entry sList (a tail call into sub_4C1D50)
void sub_4B2E20(EEContext& ctx);  // 0x4B2E20 [rt2dMaestroAnimsCreate] -- creates a maestro's animation sList (16-byte entries) at +12; the maestro, or 0
void sub_4B2F10(EEContext& ctx);  // 0x4B2F10 [rt2dMaestroAnimsStreamRead] -- reads a maestro's animations: the count, the animation sList (+12, made when missing) grown by it, each 16-byte entry cleared (index -1) and read (sub_4B2C80); the maestro, or 0
void sub_4B3160(EEContext& ctx);  // 0x4B3160 [rt2dMaestroButtonsStreamRead] -- reads a maestro's buttons: three counts, the button sList (+16, made when missing; the maestro made from the free list when $a0 is 0) grown, each 144-byte button initialised (every index -1) and read (three words and its 4-byte-per-state transition table); the maestro, or 0
void sub_4B3440(EEContext& ctx);  // 0x4B3440 [rt2dMaestroButtonsCreate] -- creates a maestro's button sList (144-byte entries) at +16; the maestro, or 0
void sub_4B3730(EEContext& ctx);  // 0x4B3730 [rt2dMaestroLabelsCreate] -- creates a maestro's label sLists: the label index (4-byte entries) at +24 and the labels (16-byte entries) at +20; the maestro, or 0
void sub_4B3900(EEContext& ctx);  // 0x4B3900 [rt2dMaestroLabelIndexStreamRead] -- reads a maestro's label index: the count, the index sList (+24, the label sLists made when missing) grown, the 4-byte entries read; the maestro, or 0
void sub_4B3AC0(EEContext& ctx);  // 0x4B3AC0 [rt2dMaestroLabelsStreamRead] -- reads a maestro's labels: the count, the label sList (+20, made when missing) grown, each 16-byte label {type, index -1, ...} read and its type's reader called through the table 0x77E3F0 (three words per type); the maestro, or 0
void sub_4B4230(EEContext& ctx);  // 0x4B4230 [rt2dMaestroInit] -- initialises a maestro record: the lists emptied and created (animation list sub_4B47D0, animations, buttons, labels, the message queue sub_4B40F0, the string buffer sub_4B2BC0), the default message handler (sub_4B5B50), the bounding extent 2^32 x 2^32, the message state (sub_4B34E0 at +88); the maestro
void sub_4B42E0(EEContext& ctx);  // 0x4B42E0 [rt2dMaestroDestroyBody] -- destroys a maestro's contents: the animation list (sub_4B4810), animations (sub_4B2E70), buttons (sub_4B3490), labels (sub_4B3790), its scene (Rt2dSceneDestroy sub_4AE5A0), the message queue (sub_4B41B0), the string buffer (sub_4B2BD0); 1
void sub_4B4410(EEContext& ctx);  // 0x4B4410 [Rt2dMaestroDestroy] -- destroys a maestro: its contents (sub_4B42E0), the record returned to the free list (0x95FA98); 1
void sub_4B4790(EEContext& ctx);  // 0x4B4790 [rt2dMaestroAnimApplyCB] -- an animation-list walk callback: the entry's current keyframe applied to its props (sub_4B1620 on +4 / +32); the context, or 0 on a failure
void sub_4B47D0(EEContext& ctx);  // 0x4B47D0 [rt2dMaestroAnimListCreate] -- creates a maestro's animation list (60-byte entries) at +8; the maestro, or 0
void sub_4B4860(EEContext& ctx);  // 0x4B4860 [rt2dMaestroAnimListStreamRead] -- reads a maestro's animation list: the count, the 60-byte entries (the list made when missing), each {type 2, parent / object index -1, a message list (sub_4B6040 / sub_4B5EC0), the two indices, a 28-byte record (sub_4C1970), its props for the scene object (sub_4B5270 / sub_4B2AD0), its keyframes (sub_4B1290)}; the first entry made current (sub_4C21B0); the maestro, or 0
void sub_4B4CC0(EEContext& ctx);  // 0x4B4CC0 [rt2dMaestroSceneStreamRead] -- reads a maestro's scene: a flag word and, when set, the scene chunk (421) read (Rt2dSceneStreamRead sub_4AEEA0) into +36; the maestro, or 0
void sub_4B4D70(EEContext& ctx);  // 0x4B4D70 [rt2dMaestroAnimUpdateCB] -- updates one maestro animation: just restarted (flag 2): its keyframe's message posted (sub_4B39F0) when it has one, the messages processed (sub_4B3CC0 / sub_4B5380); when its scene object is visible (sub_4AE010) and it is not stopped (flag 1) its time advanced (sub_4B14C0) and the new keyframe's message posted on a change; the maestro, or 0
void sub_4B4EB0(EEContext& ctx);  // 0x4B4EB0 [rt2dMaestroAnimRewind] -- rewinds a maestro animation that reached its end (not looping) or when forced ($a2): its keyframe list to entry 0 (sub_4B1870), flag 2 set, and every later animation parented to it reset as well (recursively) with its scene object's visibility cleared (sub_4AE900 / sub_4ADFD0); the maestro
void sub_4B5D80(EEContext& ctx);  // 0x4B5D80 [rt2dMaestroMsgStreamRead] -- reads one maestro message record: two words, a count and that many 4-byte entries into its sList (made when missing), a final word; the record, or 0
void sub_4B5EC0(EEContext& ctx);  // 0x4B5EC0 [rt2dMaestroMsgListStreamRead] -- reads a maestro message list (a new one when $a1 is 0, sub_4B6040 / sub_4B6270): the count, the 16-byte records (indices -1, each with its own 4-byte sList) read by sub_4B5D80; the list, or 0
void sub_4B6040(EEContext& ctx);  // 0x4B6040 [rt2dMaestroMsgListCreate] -- creates a maestro message list from the free list (0x95FB94): a 16-byte-record sList and reference count 1; on an allocation failure the half-made list is torn down; the list, or 0
void sub_4B7630(EEContext& ctx);  // 0x4B7630 [rtDictSchemaInit] -- initialises a dictionary schema: its dictionary sList (4-byte entries, the schema's memory hint | 0x40000) at +16 and no current dictionary; the schema, or 0
void sub_4B7690(EEContext& ctx);  // 0x4B7690 [rtDictSchemaDestruct] -- destructs a dictionary schema: its dictionary sList destroyed (sub_4C20B0); 1
void RwFsInit(EEContext& ctx);  // 0x4BFBB0 -- initialises the RtFS manager: the maximum file systems ($a0), no file systems, no default, no error callback, the manager semaphore created (count 1, _sceCreateSema) and the initialised flag; 1
void sub_4BFEA0(EEContext& ctx);  // 0x4BFEA0 [rtfsFileOpenRecord] -- opens a file record of a file system: under the manager semaphore the first free record (state 1, through the file system's record getter +20) marked opening (5); the async / sync mode words for flag 0x10 or an always-async file system; the file system's open callback (+40) run and the record's state set (busy 2) or freed again on a failure; error 8 (no record) / 4 (no file system) through the error callback 0x95FF24; the record, or 0
void sub_4C00F0(EEContext& ctx);  // 0x4C00F0 [rtfsFindFileSystem] -- finds the file system of a path: when any is registered, the device prefix up to each ':' compared (strncpy / strcmp slots) with the registered names (list 0x95FF10); else the default file system (gp 0x7CE8BC); error 6 through the error callback when none; the file system, or 0
void sub_4C06C0(EEContext& ctx);  // 0x4C06C0 [rtfsFileExistsByPath] -- tests whether a file exists: its file system found by the device prefix (as sub_4C00F0) or the default, then that file system's exists callback (+76); its result, or 0
void j_malloc(EEContext& ctx);  // 0x4C4420 -- a tail call into newlib malloc (the default RW allocation slot)
void j_realloc(EEContext& ctx);  // 0x4C4430 -- a tail call into newlib realloc (the default RW reallocation slot)
void j_calloc(EEContext& ctx);  // 0x4C4440 -- a tail call into newlib calloc (the default RW zeroed-allocation slot)
void sub_4C4450(EEContext& ctx);  // 0x4C4450 [rwMemoryOpen] -- opens RW's memory module: the free-list registry (a 36-byte free list, sub_4C3970) with an empty list head, then the four memory function slots 0x960178..0x960184 set from the caller's table $a0 or the newlib defaults (j_malloc, cfree, j_realloc, j_calloc); 1, or 0
void sub_4C4570(EEContext& ctx);  // 0x4C4570 [rwMemoryClose] -- closes RW's memory module: every registered free list unlinked and destroyed (sub_4C3B70), then the registry's own free list; the registry cleared
void sub_4C6640(EEContext& ctx);  // 0x4C6640 [rwV3dTransformPointsDefault] -- the default point transform: $a2 points from $a1 times the matrix $a3 (rotation and translation) into $a0 (FPU multiply-accumulate); $a0
void sub_4C6700(EEContext& ctx);  // 0x4C6700 [rwV3dTransformPointDefault] -- the default single-point transform: the point $a1 times the matrix $a2 (rotation and translation) into $a0; $a0
void sub_4C67A0(EEContext& ctx);  // 0x4C67A0 [rwV3dTransformVectorsDefault] -- the default vector transform: $a2 vectors from $a1 times the matrix $a3's rotation (no translation) into $a0; $a0
void sub_4C6840(EEContext& ctx);  // 0x4C6840 [rwV3dTransformVectorDefault] -- the default single-vector transform: the vector $a1 times the matrix $a2's rotation into $a0; $a0
void sub_4C68C0(EEContext& ctx);  // 0x4C68C0 [rwV3dSetTransformFns] -- sets the vector module's four transform functions (engine + gp 0x7CE910, +8..+20), each argument or, when 0, its default (sub_4C6700 / sub_4C6640 / sub_4C6840 / sub_4C67A0); 1
void sub_4C6D00(EEContext& ctx);  // 0x4C6D00 [rwV3dModuleOpen] -- the vector module's open: its engine offset (gp 0x7CE910) stored, the four default transform functions installed, the open count up; $a0
void sub_4C7020(EEContext& ctx);  // 0x4C7020 [rwModule1042Open] -- the engine module 1042's open: its engine offset (gp 0x7CE918) stored, a free list of 33-byte entries (sub_4C3B60, in place at 0x960010, block size and preallocation from 0x7CDD58 / 0x7CDD5C) kept at engine + offset, the open count (gp 0x7CE91C) up; $a0, or 0
void sub_4C70A0(EEContext& ctx);  // 0x4C70A0 [rwModule1042Close] -- the engine module 1042's close: its free list destroyed (sub_4C3C30) when made, the open count down; $a0
void sub_4C71C0(EEContext& ctx);  // 0x4C71C0 [rwStrUpr] -- upper-cases a string in place (a..z), then returns it through the empty helper sub_4C7208
void sub_4C7208(EEContext& ctx);  // 0x4C7208 [rwStrReturn] -- returns its argument (an empty helper)
void sub_4C7210(EEContext& ctx);  // 0x4C7210 [rwStrLwr] -- lower-cases a string in place (A..Z), then returns it through the empty helper sub_4C7258
void sub_4C7258(EEContext& ctx);  // 0x4C7258 [rwStrReturn2] -- returns its argument (an empty helper)
void sub_4C7260(EEContext& ctx);  // 0x4C7260 [rwStrChr] -- finds the first $a1 character in a string: a pointer to it, or 0 at the terminator
void sub_4C72A0(EEContext& ctx);  // 0x4C72A0 [rwStrRChr] -- finds the last $a1 character in a string: a pointer to it, or 0
void sub_4C7400(EEContext& ctx);  // 0x4C7400 [rwEngineNoOp] -- an empty engine hook (returns at once)
void sub_4C7410(EEContext& ctx);  // 0x4C7410 [rwStringStreamGetSize] -- the stream size of a string chunk's body: (strlen(s) + 4) & ~3, an empty string ("" at 0x7BCBE8) for 0
void sub_4C7520(EEContext& ctx);  // 0x4C7520 [rwStringStreamReadAscii] -- reads a string chunk's body of $a2 bytes into $a0 (RwMalloc'd when 0; error 0x80000013) in 64-byte pieces; the string, or 0
void sub_4C78A0(EEContext& ctx);  // 0x4C78A0 [rwStringStreamRead] -- reads the next string from a stream: the chunk headers walked (sub_4C1450; versions 0x35000..0x37002 else error 0x80000004), other chunks skipped (sub_4C5620), a string (2, sub_4C7520) or unicode string (19, sub_4C76C0) read into $a0; the string, or 0
void sub_4C79E0(EEContext& ctx);  // 0x4C79E0 [rwPathIsAbsolute] -- whether a path is absolute: it starts with '\' or with a letter (ctype table 0x7BE9C8) and ':'; 1 / 0
void sub_4C7B60(EEContext& ctx);  // 0x4C7B60 [RwCameraRegisterPluginStream] -- registers the stream callbacks of a camera plugin: in the camera plugin registry (0x77E5E0, through the shared registry tail at 0x4C5960) the entry with id $a0 gets its read / write / get-size callbacks ($a1..$a3); its offset, or -1
void sub_4CA190(EEContext& ctx);  // 0x4CA190 [rwEngineRegisterModules] -- registers the engine's core modules (sub_4CA520: size, module id 1025..1042, open / close functions) -- the error, vector, string, matrix, frame, stream, camera, image, raster, texture, pipeline, the 0x4C7020 free list and resource modules -- and the pipeline's own (sub_4F28D0); 1 when all succeeded
void sub_4CAAC0(EEContext& ctx);  // 0x4CAAC0 [frameSetRoot] -- sets a frame's root (+160) and, recursively, every descendant's (child +152, sibling +156; two levels unrolled)
void sub_4CBA20(EEContext& ctx);  // 0x4CBA20 [imageModuleOpen] -- the image module's open (engine + gp 0x7CE938): the image free list and the 52-byte format free list (sub_4C3B60), a 256-byte search path buffer (empty), the open count up, the default formats registered (sub_4CDB50), a 256-byte scratch buffer; unwound on a failure; $a0, or 0
void sub_4CC5C0(EEContext& ctx);  // 0x4CC5C0 [RwImageSetPath] -- sets the image search path: the module's buffer grown (RwRealloc; error 0x80000013) to the string's length + 1 and the string copied; the path, or 0
void sub_4CC6D0(EEContext& ctx);  // 0x4CC6D0 [imageSearchPathForEach] -- calls $a2(path, $a3) for a file name: a relative name is tried after each ';'-separated directory of the image search path (the module's scratch buffer grown to fit, RwRealloc / RwMalloc; error 0x80000013) until the callback returns 0; an absolute name (sub_4C79E0) or an empty path is tried once as it is; $a0, or 0
void sub_4CCA60(EEContext& ctx);  // 0x4CCA60 [imageReadCB] -- the image read's search-path callback: when the file exists (sub_4C06C0) the format's reader (*$a1) is called and its image stored in $a1[1]; 0 (stop) once an image was read, else the path
void sub_4CCAC0(EEContext& ctx);  // 0x4CCAC0 [RwImageRead] -- reads an image file: the extension found after the last ':', '/', '\' and '.', the registered format with that extension (lower- or upper-case, strcmp slot), its reader run over the search path (sub_4CC6D0 with sub_4CCA60); the image, or 0
void sub_4CCC30(EEContext& ctx);  // 0x4CCC30 [imageFindFileCB] -- the image find's search-path callback: the path with each registered format's lower- and upper-case extension appended tested (sub_4C06C0); on a hit the extension's address stored in *$a1 and 0 returned (stop), else the path
void sub_4CCD20(EEContext& ctx);  // 0x4CCD20 [imageFindFile] -- finds an image file over the search path trying every registered extension (sub_4CC6D0 with sub_4CCC30); the extension found, or 0
void sub_4CCD50(EEContext& ctx);  // 0x4CCD50 [RwImageRegisterImageFormat] -- registers an image file format: the extension as ".ext" (18 characters) lower-cased; an existing entry is reused, else a 52-byte entry from the format free list with the lower- and upper-case extensions, linked at the head; the reader ($a1) and writer ($a2) set when given; 1, or 0
void sub_4CCF10(EEContext& ctx);  // 0x4CCF10 [RwImageReadMaskedImage] -- reads an image and, when a mask name is given, its mask (RwImageRead each), the mask turned into alpha (sub_4CC0A0 / sub_4CC1D0) and the mask image destroyed (pixels freed, plugin destructors on 0x77E690, the free list); on a failure both are destroyed; the image, or 0
void sub_4CD260(EEContext& ctx);  // 0x4CD260 [rwImageCopyPixels] -- copies an image's pixels into another of the same size by their depths: 8 / 4 bpp to 32 bpp through the palette, 8 to 8 row by row, same-depth 32 / 4 / 8 already equal, other pairs refused (error 0x80000009); 1, or 0
void sub_4CD940(EEContext& ctx);  // 0x4CD940 [RwImageGammaCorrect] -- gamma-corrects an image through the module's gamma table (+12): a 32-bit image's RGB per pixel (alpha kept), a 4 / 8-bit image's palette; no pixels or another depth is an error (0x80000016 / 0x80000009); the image, or 0
void sub_4CDB50(EEContext& ctx);  // 0x4CDB50 [RwImageSetGamma] -- sets the image gamma ($f12, kept at +524) and rebuilds the two 256-entry tables (+12 gamma, +268 inverse): entry i = 255 * (i / 255)^g + 0.5 (powf), entry 0 = 0; 1
void sub_4CEE30(EEContext& ctx);  // 0x4CEE30 [imageResampleTo32] -- makes a 32-bit image of $a1 x $a2 from an image: the destination allocated (sub_4CBE00 / sub_4CBF20), a non-32-bit source first copied into a 32-bit one (sub_4CD620), then resampled into it (sub_4CEC10); the temporary images destroyed; the new image, or 0
void sub_4CF690(EEContext& ctx);  // 0x4CF690 [imagePalettise] -- reduces *$a0 to a palette of 2^$a1 colours: the quantiser initialised (sub_4D3FC0), fed the image (sub_4D22F0), the palette made (sub_4D3300), a new image of that depth with the indices (sub_4D3800) and palette, the old image destroyed and *$a0 replaced, the quantiser freed (sub_4D41E0); 1, or 0
void sub_4CF790(EEContext& ctx);  // 0x4CF790 [imagesPalettiseShared] -- gives a mip chain of $a3 images one palette of 2^$t0 colours in $a0: when every level already carries the same palette it is copied; else all levels are fed to one quantiser, the palette made, and each level replaced by a palettised image pointing at $a0 (the original $a1 kept); 1, or 0
void sub_4CF9B0(EEContext& ctx);  // 0x4CF9B0 [textureReadImage] -- reads the image for a texture raster: the name and mask (256 characters, error 0x8000001E when longer) with their found extensions (sub_4CCD20), the masked image (RwImageReadMaskedImage), the raster format chosen when not given (sub_4CDD50), the image resampled to the raster size (via a 32-bit copy) and palettised for 4 / 8-bit rasters (sub_4CF690); the image, or 0
void sub_4CFD30(EEContext& ctx);  // 0x4CFD30 [textureReadDefault] -- the default texture reader without mipmaps: the names copied, the level-name hook (sub_4D1210), the image (sub_4CF9B0) for a 4-bit-capable raster, the raster created (RwRasterCreate), a palettised raster's palette made (sub_4CF790), the image gamma-corrected and copied into the raster (sub_4CDCE0), the texture (sub_4D0E40) with its names; the texture, or 0
void sub_4D05F0(EEContext& ctx);  // 0x4D05F0 [textureReadDefaultCB] -- the texture module's default read callback: the mipmapped reader (sub_4CFFD0) when the module's mipmapping flag (+28) is set, else sub_4CFD30 (a tail call)
void sub_4D0640(EEContext& ctx);  // 0x4D0640 [rasterSetImageMipmaps] -- fills a raster's mip levels from an image ($a1, or read back from the raster when 0, sub_4CDC70; converted to 32-bit when needed): level 0 from it, each further level resampled from the previous one at the locked level's size (sub_4CEE30), the levels palettised together for 4 / 8-bit rasters (sub_4CF790) or gamma-corrected, each copied into its locked level (sub_4CDCE0); the raster's automatic-mipmap flag held off meanwhile; the raster, or 0
void sub_4D0AC0(EEContext& ctx);  // 0x4D0AC0 [textureFindNamedAnyDict] -- finds a texture by name: in the current dictionary (the module's +16, sub_4D1170) when there is one, else in every dictionary of the module's list; the texture, or 0
void sub_4D11D0(EEContext& ctx);  // 0x4D11D0 [RwTexDictionarySetCurrent] -- sets the current texture dictionary (the texture module's +16); the dictionary
void RpSkySelectDeepZBuffer(EEContext& ctx);  // 0x4D82A0 -- selects the sky driver's Z buffer depth before the engine starts: 32 bits (Im2D near screen Z 16777215) for a non-zero $a0, else 16 bits (65535); refused (0) once the engine is started (0x7CEAC8); 1
void sub_4D8300(EEContext& ctx);  // 0x4D8300 [skySetFlag7CEB04] -- stores a sky driver option word (gp 0x7CEB04); 1
void sub_4D8310(EEContext& ctx);  // 0x4D8310 [skySetFlag7CDDE8] -- stores a sky driver option word (0x7CDDE8); 1
void sub_4D83C0(EEContext& ctx);  // 0x4D83C0 [skyTextureKLStreamRead] -- the sky texture plugin's stream read: for a 4-byte extension of a texture with a raster, the raster's mipmap K / L halfword (raster + gp 0x7CEAA8 + 20) read; the stream, or 0
void sub_4D9520(EEContext& ctx);  // 0x4D9520 [skyRasterValidateFormat] -- checks and completes a raster's format for the sky driver: the type (+32) and flags (+33) from $a2; a Z buffer must match the selected Z depth (format 0x700 / 0x900), a camera raster the display / custom mode's depth and format (0x500 for 32-bit, 0x100 for 16-bit), a texture / normal raster gets its format from its depth (16 / 24 / 32 / 8 palettised / 4 palettised) or has its depth checked against its format; the private format byte (+35) set; 1, or 0 (errors 0x8000000C / 0x8000000D)
void sub_4D9BC0(EEContext& ctx);  // 0x4D9BC0 [skyTextureMipLayout] -- computes the GS memory layout of a texture's mip chain for the sky driver: the page / block / column sizes of the pixel storage mode $a2 (PSMCT32 / 24 / 16 / 16S, PSMT8 / 4 and the Z modes), the level count (halving while both sides stay above 8, up to the driver's limit), then level by level each level's page-aligned position and buffer width packed beside the previous ones (the corner cases of levels smaller than a page), the per-level offsets and widths written to the caller's arrays, the last block number converted to the GS block numbering of the storage mode (*$t3) and the total size (*$t2; 64-bit products through __udivdi3 / __umoddi3)
void sub_4DCEA0(EEContext& ctx);  // 0x4DCEA0 [skyRasterSubRaster] -- the sky driver's sub-raster set-up: the sub-raster ($a0) takes its parent's ($a1) format, depth and stride; a sub-raster of a camera raster used as a texture (type 5 of type 2) gets its offset / size rounded to the GS page grid and its own TEX0 words (base pointer, buffer width, log2 width / height); the pixel pointer from the parent's position; the original rectangle kept (+36..+48); 1, or 0 when the parent is unaligned for it
void sub_4DF0E0(EEContext& ctx);  // 0x4DF0E0 [skyRasterGetMipLevels] -- the sky driver's mip-level count of a raster: (the raster extension's +22 >> 2) + 1 for a mipmapped raster (flag 0x80 of +35), else 1; 0 for a raster without pixels
void sub_4DF3F0(EEContext& ctx);  // 0x4DF3F0 [skyRasterNativeStreamRead] -- reads a raster's PS2 native data: the 64-byte struct, a raster created with that size, depth and format (the mip-level count forced meanwhile), the raster extension's GS words restored, then the pixel data (one block, or palette and pixels for a palettised texture) with the data cache written back (SyncDCache); the raster, or 0 (destroyed on a failure)
void sub_4DF9D0(EEContext& ctx);  // 0x4DF9D0 [skyTextureNativeStreamRead] -- reads a texture's PS2 native data: the struct (version 0x35000..0x37002, the 'PS2' platform tag), the name and mask strings (sub_4C78A0), the raster (sub_4DF3F0), a texture (sub_4D0E40) with its names and the filter / address modes (a missing V address copied from U); 1, or 0
void sub_4DFCA0(EEContext& ctx);  // 0x4DFCA0 [skyReturnOne] -- returns 1 (an empty sky driver hook)
void sub_4DFCC0(EEContext& ctx);  // 0x4DFCC0 [skyFillStandardTable] -- fills a device standard-function table: $a1 entries set to the default sub_4DFCB0, then each of the $a3 {index, function} pairs of $a2 stored when its index is in range
void sub_4E00E0(EEContext& ctx);  // 0x4E00E0 [skyPluginsAttach] -- attaches the sky driver's plugins: a 92-byte raster extension (gp 0x7CEAA8), a 216-byte camera extension (0x7CEAA4), a 272-byte texture extension (0x7CEAA0) with its stream callbacks (sub_4D83C0 / sub_4D8440 / sub_4D84A0); 1 when all succeeded
void SkySystem(EEContext& ctx);  // 0x4E2B70 -- the sky driver's device-control entry (the engine's system request $a0): 0 open (SkyOpen), 1 / 8 / 9 nothing, 2 start (SkyStart), 3 stop (the DMA closed, the post-flip chain cleared, the texture cache closed sub_4F0AD0, the started flags cleared), 4 the device's standard function table copied (7 pairs from sceLibgcc32GetErxEntries_2) and the device id kept, 5 the mode count (90), 6 a video mode's record (the custom mode for -1), 7 use a mode (SkyUseMode), 10 the current mode, 11 the standard functions table (sub_4DFCC0 with 28 entries at 0x77F010), 12 the texture memory size, 17 the pipelines overloaded and the frame / scratch rasters made (sub_4E40B0 / sub_4E3550) with the VU0 transforms installed (sub_4C2A30 / sub_4C68C0) or released (sub_4EEC10), the identity matrix and the frame stamp, 18 the rasters released (sub_4E4130 / sub_4E3090 / sub_4EEC10), 19 1024, 22 the halfword 6; 1 / 0
void sceLibgcc32GetErxEntries_2(EEContext& ctx);  // 0x4E2F00 -- returns the address of the sky device's standard-function block 0x77F0F0 (a FLIRT-named three-instruction getter)
void sub_4E3090(EEContext& ctx);  // 0x4E3090 [skyDestroyFrameRasters] -- releases the sky driver's frame-buffer and Z-buffer rasters (0x7CEA74 / 0x7CEA70, sub_4CDE90) when the engine is started; the started flag
void sub_4E3550(EEContext& ctx);  // 0x4E3550 [skyCreateFrameRasters] -- makes the sky driver's frame-buffer and Z-buffer rasters when the engine is started: the two display and draw buffer base words taken from the flip data's FRAME / DISPFB registers, SkyCreateFBRaster / SkyCreateDBRaster, then sub_4E2F10; 1, or 0
void sub_4E40B0(EEContext& ctx);  // 0x4E40B0 [skyCreateScratchRasters] -- makes the sky driver's two empty type-128 rasters (0x7CEAE8 / 0x7CEAEC, RwRasterCreate), the current raster cleared; 1, or 0 (the first released when the second fails)
void sub_4E4130(EEContext& ctx);  // 0x4E4130 [skyDestroyScratchRasters] -- releases the sky driver's two scratch rasters (sub_4CDE90) and clears their slots
void sub_4E98A0(EEContext& ctx);  // 0x4E98A0 [skyRasterFormatFromImage] -- the sky driver's raster set-up from an image: width / height and type / flags from $a1 / $a2; a Z buffer gets no format, a camera raster the display depth's (0x500 / 0x100), a texture the format from the image's alpha class (sub_4D1900) and the frame depth, the palette bits for 4 / 8-bit images, its size rounded up to powers of two (sub_4D6B60) up to 1024, a normal raster the format bits given (at least 1); 1, or 0 for another type
void sub_4EAC00(EEContext& ctx);  // 0x4EAC00 [skyRasterWritePalette] -- writes a palette into a raster's palette memory (+8) in the GS CLUT layout by the raster's format: 256 entries swizzled (the 0x7BCF60 table) or 16 entries, as 32-bit (alpha halved: 8421505 x a & 0xFF000000) or 16-bit 1555 colours; the data cache written back (SyncDCache)
void sub_4EB8C0(EEContext& ctx);  // 0x4EB8C0 [skyRasterSetImagePalettised] -- copies an image into a palettised raster: 8-bit rasters from 32-bit images through the quantiser (sub_4EB7E0) or from 8 / 4-bit images with their palette and rows; 4-bit rasters from 32 / 8-bit images (quantised) or 4-bit images (nibbles packed by the raster's x parity); 1, or 0 for another combination
void sub_4EEC10(EEContext& ctx);  // 0x4EEC10 [skyNoOp] -- an empty sky driver hook
void sub_4EF1D0(EEContext& ctx);  // 0x4EF1D0 [skyRasterPrepareUploads] -- pre-builds a texture raster's GS upload packets: for each mip level whose pixels are 16-byte aligned and contiguous an upload packet (RwMalloc'd, skyFillInPktForUpLoadAlignedContiguousRectangle) when the raster extension asks for them (+52), and the palette's packet (the CLUT size from the 0x7BCF8C / 0x7BCFAC tables by depth); cleared when not wanted
void sub_4EF9F0(EEContext& ctx);  // 0x4EF9F0 [skyNoOp2] -- an empty sky driver hook
void sub_4F02E0(EEContext& ctx);  // 0x4F02E0 [skyTexCacheAllocRaster] -- places a texture raster in the GS texture cache ring (0x77F200..): a raster already resident is referenced again (with interrupts off its counters up, the PURef added for the first use); else space after the last entry (or the cache start) is found, the entries it overlaps evicted (their rasters' cache links cleared) unless locked, the raster's TEX0 base set (sub_4EFA00), and the ring entry {raster, address, 2 KiB-rounded size} appended
void sub_4F0AD0(EEContext& ctx);  // 0x4F0AD0 [skyTexCacheReset] -- resets the sky driver's texture cache: on a reopen every resident raster's cache link cleared and the ring freed; then the cache state (0x77F200..0x77F238) back to empty; 1
void sub_4F1E10(EEContext& ctx);  // 0x4F1E10 [skyTexCacheGetBase] -- returns the texture cache's start word (0x77F21C)

}  // namespace p3fes::game
