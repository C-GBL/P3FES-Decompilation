// Named views for the register-level RenderWare bodies (p3fes_handgen, game/include/p3fes/game/hg_cpu.h) of
// core3.cpp, world.cpp and rw_builders.cpp: the addressing helpers and the records more than one of the three files
// reads, so a body says `lwc1(f0, a0, rw_matrix::kPosX)` instead of `lwc1(f0, a0, 48)`. Written by the read_render
// readability pass (2026-10-22); header only. Nothing here changes what a body runs: the constants are the values the
// instructions hold, and the helpers run exactly the statements, in order, that they stand for. The records only one
// file reads are named in that file (a namespace near its first body).
//
// Every offset comes from the instructions of the functions that use it, cross-checked against the layouts the
// slices documented (core3.h, world.h, rw_builders.h, rw_leaves.h, sky.h) and the proposed layouts of the type
// recovery (tools/ours/types/types_query.py; docs/ANALYSIS/28_types.md). Names are ours or the project's
// (symbols/p3fes.sym); no unverified community names (ADR-0009). text_view.h and battle_view.h have the same
// addressing helpers in their own namespaces; they are repeated here so the render bodies do not pull those in.
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/ee_context.h"
#include "p3fes/game/hg_cpu.h"

#include <bit>

namespace p3fes::game::rview {

// --- addressing: spell the address a `lui`/`addiu` pair or a `$gp` offset forms ------------------------------------
inline constexpr u32 kGpBase = 0x7D2CF0u;  // $gp of the whole program (crt0; world::kGp)
// `lw rt, gp_off(va)(gp)`: the signed 16-bit offset of `va` from $gp.
constexpr s32 gp_off(u32 va) noexcept { return static_cast<s32>(va - kGpBase); }
// `lui rt, hi(va)` + `addiu/lw rt, lo(va)(rt)`: the carry-adjusted upper half (as lui writes it: sign-extended) and the
// signed lower half. hi(0x77E5C0) = 0x780000, lo(0x77E5C0) = -6720.
constexpr u64 hi(u32 va) noexcept { return ee::core::lui((va + 0x8000u) >> 16); }
constexpr s32 lo(u32 va) noexcept { return static_cast<s16>(static_cast<u16>(va & 0xFFFFu)); }
static_assert(hi(0x77E5C0u) == 0x780000u && lo(0x77E5C0u) == -6720);
// `lui rt, hi16` of an EE single literal (lui + mtc1 builds every such float): the register value lui writes for `f`.
constexpr u64 flt(float f) noexcept { return ee::core::sext32(std::bit_cast<u32>(f)); }
static_assert(flt(1.0f) == 0x3F800000u);

// `la r, va`: the adjacent `lui r, hi(va); addiu r, r, lo(va)` pair that loads an address (same block, same order).
inline void la(hg::Gpr r, u32 va) {
    r = hi(va);
    r = hg::addiu(r, lo(va));
}

// --- the RW engine globals (0x960070; rw_leaves.h rwl::kRwGlobals) --------------------------------------------------
// Module data lives at rwl::kRwGlobals + a plugin offset the module keeps in a $gp word (rwl::kGp*, world::kGp*);
// world::kRenderFrame (0x960078) is the u16 render frame stamp.
inline constexpr u32 kDeviceStd = 0x9600B8u;     // the device's standard functions, 4 * index (core3.h)
inline constexpr u32 kRenderStateGet = 0x960094u;  // the driver's RwRenderStateGet slot (core3.h [renderstate])
inline constexpr u32 kMemFuncs = 0x960178u;      // the engine's memory function pointers (0x960178..0x96018C)

namespace rw_globals {
inline constexpr s32 kCurrentCamera = 0;  // u32: the camera between BeginUpdate and EndUpdate
inline constexpr s32 kCurrentWorld = 4;   // u32: the world being rendered
}  // namespace rw_globals

// --- the error report (RWERROR): sub_4C1D10 builds the code, sub_4C1C50 stores {plugin, code} in the error slot ----
// `lui v0, 0x8000; ori a0, v0, n`: an engine error code (bit 31: no plugin). The message string is $a1.
inline constexpr u32 kErrCodeBase = 0x80000000u;
inline constexpr u32 kStrInvalidCombination = 0x77E5C0u;  // "Invalid combination type" (the matrix ops' bad combine)

// --- RxPipelineExecute's execution globals and the pipeline records (core3.cpp [rxheap]) -----------------------------
inline constexpr u32 kRxExecPipeline = 0x965A80u;  // the pipeline being executed
inline constexpr u32 kRxExecContinue = 0x965A88u;  // 1 until a node body returns 0
inline constexpr u32 kRxExecData = 0x965A90u;      // the data the nodes get (&kRxExecData is their second argument)
inline constexpr u32 kRxExecHeap = 0x965A94u;      // the global RxHeap (gp-16832) during the run
namespace rx_pipeline {
inline constexpr s32 kNodes = 4;       // u32: the node list (+8 the first node)
inline constexpr s32 kFirstNode = 8;   // u32: the first node (+0 its definition: +4 the body)
inline constexpr s32 kState = 16;      // s32: >= 2 after a run: the +20 list is released
inline constexpr s32 kList = 20;       // u32
inline constexpr s32 kNeedsLock = 24;  // u32
}  // namespace rx_pipeline

// --- the Im3D module state (RW globals + gp-16848; core3.cpp sub_4F1FD0) ---------------------------------------------
namespace im3d_state {
// the pipeline of each primitive type (1 a line list, 3 a triangle list: the counts sub_4F1FD0 rounds)
inline constexpr s32 kPipeType3 = 4, kPipeType5 = 8, kPipeType4 = 12, kPipeType1 = 16, kPipeType2 = 20;
inline constexpr s32 kTransformed = 68;    // u32: RwIm3DTransform ran
inline constexpr s32 kRecord = 76;         // the render record: +32 the pipeline, +44 the primitive count
inline constexpr s32 kRecordWord108 = 108, kType = 112, kIndices = 116, kCount = 120;
}  // namespace im3d_state

// --- a rectangle {x, y, w, h} (s32) and the blits' scissor (core3.cpp sub_4E4A90 / sub_4E4C20) ----------------------
namespace rect {
inline constexpr s32 kX = 0, kY = 4, kW = 8, kH = 12;
}  // namespace rect
inline constexpr u32 kScissor = 0x965840u;

// --- the resource heap (core3.cpp sub_4C6D60 / sub_4C6E60 / sub_4C6F30): a heap and its 32-byte block headers ------
namespace res_heap {
inline constexpr s32 kHint = 4;          // u32: the first-fit hint (a free block, or 0)
}  // namespace res_heap
namespace heap_block {
inline constexpr s32 kHeap = 0;          // u32: the heap
inline constexpr s32 kNext = 4;          // u32: the next block
inline constexpr s32 kPrev = 8;          // u32: the previous block
inline constexpr s32 kSize = 12;         // u32: the data bytes
inline constexpr s32 kUsed = 16;         // u32: bit 0 used
inline constexpr s32 kHeaderSize = 32;   // the data follows the header
}  // namespace heap_block

// --- a 4x4 matrix (64 bytes; core3.h [rwcore], sub_4C33D0 / sub_4C35D0 / sub_4C3760) -------------------------------
namespace rw_matrix {
inline constexpr s32 kRightX = 0, kRightY = 4, kRightZ = 8;
inline constexpr s32 kFlags = 12;              // u32: bit 0 / 1 orthonormal parts, bit 17 (0x20000) identity
inline constexpr s32 kUpX = 16, kUpY = 20, kUpZ = 24;
inline constexpr s32 kAtX = 32, kAtY = 36, kAtZ = 40;
inline constexpr s32 kPosX = 48, kPosY = 52, kPosZ = 56;
inline constexpr s32 kSize = 64;
inline constexpr u32 kFlagIdentity = 0x20000u;
inline constexpr u32 kFlagsOrthonormal = 0x3u;
}  // namespace rw_matrix

inline constexpr u32 kRenderStateSet = 0x960090u;  // pfn_RwRenderStateSet (state, value)
// The driver's render-state get (core3.cpp sub_4D78B0): the fog tables of fog types 2 / 3 (type 1: sky::kFogTable)
// and the jump tables of the blend lookups.
inline constexpr u32 kFogTable2 = 0x965530u;
inline constexpr u32 kFogTable3 = 0x965450u;
inline constexpr u32 kJtBlendDest = 0x7BCCE0u;
inline constexpr u32 kJtBlendSrc = 0x7BCD00u;

// --- the Rt2d path draws (world.cpp sub_46BAB0 / sub_46BD00) and their globals ---------------------------------------
namespace rt2d_path {
inline constexpr s32 kData = 8;       // u32: the path's nodes (a path without them is skipped by the fill)
inline constexpr s32 kFlat = 12;      // u32: the flattened segment list (rt2d_flat::), made on first use
inline constexpr s32 kInset = 16;     // f32
inline constexpr s32 kNext = 20;      // u32: the next path of the chain
inline constexpr s32 kPoints = 24;    // u32: its point list (rt2d_flat:: {+0 the array, +8 closed})
}  // namespace rt2d_path
// A point of a flattened path (24 bytes): the flatten / close functions write them.
namespace rt2d_point {
inline constexpr s32 kKind = 0;               // u32: 1 a line point
inline constexpr s32 kX = 4, kY = 8;          // f32
inline constexpr s32 kNx = 12, kNy = 16;      // f32: the normal
inline constexpr s32 kLength = 20;            // f32: the path length up to here
inline constexpr s32 kSize = 24;
}  // namespace rt2d_point
namespace rt2d_flat {
inline constexpr s32 kArray = 0;      // u32: the growable vertex array (24-byte vertices)
inline constexpr s32 kCount = 4;      // s32: its cached count, -1 = ask the array
inline constexpr s32 kClosed = 8;     // u32: closed (sub_4AB6A0)
}  // namespace rt2d_flat
// An Rt2d object (core3.cpp [rt2d]): the common header; a scene's children follow.
namespace rt2d_obj {
inline constexpr s32 kType = 0;          // s32: 1 scene, 2 shape, 3 pick region, 4 string
inline constexpr s32 kDepth = 4;         // f32: the depth a scene sorts its children by
inline constexpr s32 kFlags = 8;         // u32: bit 2 visible, bit 1 the matrix changed
inline constexpr s32 kMatrix = 16;       // the object's own matrix (64 bytes)
inline constexpr s32 kCtm = 80;          // the CTM it was last drawn with (64 bytes)
inline constexpr s32 kColourMul = 144;   // f32[4]: the colour multiplier
inline constexpr s32 kColourOffset = 160;  // f32[4]: the colour offset (0..255)
}  // namespace rt2d_obj
namespace rt2d_shape {
inline constexpr s32 kPaths = 176;       // u32: the growable array of path nodes (rt2d_pathnode::, 12 bytes)
inline constexpr s32 kColourBytes = 180; // u32: the colour bytes (RGBA, one set per material of the atomic)
inline constexpr s32 kAtomic = 184;      // u32: the atomic the shape is built on (0: paths)
}  // namespace rt2d_shape
namespace rt2d_pathnode {
inline constexpr s32 kFlags = 0;         // u32: bit 0 stroke (else fill)
inline constexpr s32 kPath = 4;          // u32
inline constexpr s32 kBrush = 8;         // u32
}  // namespace rt2d_pathnode
namespace rt2d_scene {
inline constexpr s32 kChildCount = 180;  // s32
inline constexpr s32 kChildren = 184;    // u32: the growable array of {object, ...} (8 bytes each)
inline constexpr s32 kResort = 188;      // u32: the children need sorting
}  // namespace rt2d_scene
namespace rt2d_string {
inline constexpr s32 kText = 176;        // u32
inline constexpr s32 kFont = 180;        // u32: the font (its colour block +0 .. +87)
inline constexpr s32 kSize = 188;        // f32: the text size ($f12 of the draw)
inline constexpr s32 kFontObject = 192;  // u32: the font object the draw callback gets (+4)
}  // namespace rt2d_string
namespace rt2d_region {
inline constexpr s32 kInverse = 208;     // the inverse of the CTM copy (a pick region)
}  // namespace rt2d_region
namespace rt2d_font {
inline constexpr s32 kDrawCb = 312;      // u32: the font's draw callback
}  // namespace rt2d_font
// The brush's colour slots (sub_4A55B0): four RGBA float colours 24 bytes apart, the first also packed at +96.
namespace rt2d_brushcol {
inline constexpr s32 kColour0 = 0, kColour1 = 24, kColour2 = 48, kColour3 = 72;
inline constexpr s32 kPacked = 96;       // u8[4]
}  // namespace rt2d_brushcol
namespace rt2d_maestro {
inline constexpr s32 kScene = 36;        // u32
}  // namespace rt2d_maestro
namespace rt2d_brush {
inline constexpr s32 kTexture = 104;  // u32: 0 untextured
}  // namespace rt2d_brush
inline constexpr u32 kRt2dPacketWord = 0x95ED64u;   // the word the packet record's +4 takes
inline constexpr u32 kRt2dCtmStack = 0x95EDF0u;     // u32[32]: the CTM stack (matrices made by RwMatrixCreate)
inline constexpr u32 kRt2dCtmDepth = 0x95EE70u;     // s32: its top
inline constexpr u32 kRt2dDeviceValid = 0x95EF50u;  // cleared when the CTM changes (the device matrix 0x95EF10 is
inline constexpr u32 kRt2dCtmWord64 = 0x95EF64u;    //  rebuilt), with this second word
inline constexpr u32 kRt2dTolerance = 0x95EF60u;    // f32: the flattening tolerance (sub_4AA2C0)
inline constexpr u32 kRt2dFlatWord = 0x95EF68u;     // the word the Bezier flattener gets as its third argument
inline constexpr u32 kRt2dBrush = 0x95EF88u;        // the draw's brush
inline constexpr u32 kRt2dVertices = 0x95EF98u;     // its vertices
inline constexpr u32 kRt2dLastVertex = 0x95EF9Cu;   // the fill's last vertex
inline constexpr u32 kRt2dInset = 0x95EFA0u;        // f32: the path's inset
inline constexpr u32 kRt2dWidth = 0x95EFA4u;        // f32: the stroke width (the fill: 1.0)
inline constexpr u32 kRt2dUvOriginX = 0x95EFACu;    // f32: the fill's UV origin (the bounds' minimum) ...
inline constexpr u32 kRt2dUvOriginY = 0x95EFB0u;
inline constexpr u32 kRt2dUvScaleX = 0x95EFBCu;     // f32: ... and scale (1 / width, 1 / height)
inline constexpr u32 kRt2dUvScaleY = 0x95EFC0u;
inline constexpr u32 kRt2dCount = 0x95EFC4u;        // the vertices sent (with the batch repeats)
inline constexpr u32 kRt2dBatches = 0x95EFC8u;      // the stroke's extra batches ((count - 40) / 39 rounded up)
inline constexpr u32 kRt2dStrokePipe = 0x95F040u;   // the pipelines the two draws execute
inline constexpr u32 kRt2dFillPipe = 0x95F050u;

// --- the PDS 2D object set-ups (world.cpp pds2DObjectSetupA / B / C): the 2-D record (pd +8) -------------------------
namespace pds2d_rec {
inline constexpr s32 kWord0 = 0;     // u32: kRt2dPds2DWord's value
inline constexpr s32 kMatrix = 4;    // u32: the Rt2d device matrix (sub_4AAE60), 0 = the camera's view matrix
inline constexpr s32 kCount = 8;     // u32: the vertex count (kRt2dCount)
inline constexpr s32 kWord32 = 32;   // cleared
inline constexpr s32 kMode = 36;     // u32: the primitive mode (6 / 4), the PS2All prim table's index
inline constexpr s32 kIndices = 40;  // u32: cleared (no indices: the mesh header gets 0x100)
inline constexpr s32 kCount2 = 44;   // u32: the vertex count again
}  // namespace pds2d_rec
inline constexpr u32 kRt2dPds2DWord = 0x95EF54u;   // the word the 2-D records take at +0
inline constexpr u32 kPds2DTemplateA = 0x6B5790u;  // the PDS 2D mesh templates (A / B / C)
inline constexpr u32 kPds2DTemplateB = 0x6B58E0u;
inline constexpr u32 kPds2DTemplateC = 0x6B5A30u;

// --- a camera and a frame (core3.h [rwcore]) -------------------------------------------------------------------------
namespace rw_camera {
inline constexpr s32 kFrame = 4;         // u32
inline constexpr s32 kBeginUpdate = 24;  // u32: the camera's BeginUpdate
inline constexpr s32 kEndUpdate = 28;    // u32: its EndUpdate
inline constexpr s32 kProjection = 20;   // u32: 1 perspective, 2 parallel
inline constexpr s32 kRaster = 96;       // u32: the frame-buffer raster
inline constexpr s32 kNear = 128, kFar = 132;  // f32: the clip planes
inline constexpr s32 kZShift = 136;      // f32
inline constexpr s32 kViewOffsetX = 140, kViewOffsetY = 144;  // f32
}  // namespace rw_camera
// The per-camera VU1 constant block sub_4EEC20 writes (0x965910 .. 0x965A2F; sky::kTplClipFog / kTplClipCull are its
// first quadwords): guard-band ranges +0x00 and their reciprocals +0x10, clip half-sizes +0x20 / +0x30, the near and
// far splats +0x40 / +0x50, the z scale +0x60, the raster size +0x70, the view offset +0x80, the screen centres
// +0x90 and +0x110.
inline constexpr u32 kCamVuBlock = 0x965910u;
// The upload chains' GIF template quadwords (0x965A40 .. 0x965A7F; core3.cpp skyFillInPkt... / sub_4EF770,
// rw_builders.cpp sub_4EF540).
inline constexpr u32 kUploadTpl = 0x965A40u;
namespace rw_frame {
inline constexpr s32 kDirty = 3;         // u8: a root's bits 0..1 (in the dirty list), the frame's own 2..3
inline constexpr s32 kParent = 4;        // u32: the parent frame
inline constexpr s32 kDirtyLink = 8;     // {next, prev}: a root's link in the dirty-frame list
inline constexpr s32 kMatrix = 16;       // the modelling matrix (64 bytes)
inline constexpr s32 kLtm = 80;          // the local-to-world matrix
inline constexpr s32 kChild = 152;       // u32: the first child
inline constexpr s32 kSibling = 156;     // u32: the next sibling
inline constexpr s32 kRoot = 160;        // u32: the hierarchy's root
}  // namespace rw_frame
inline constexpr u32 kDirtyFrames = 0x96012Cu;  // the dirty-frame list head (RW globals + 0xBC)

// --- rasters, images, textures (as the bodies read them; core3.h [rwcore] / [raster]) --------------------------------
namespace rw_raster {
inline constexpr s32 kParent = 0;       // u32: the parent raster (a sub-raster's)
inline constexpr s32 kPixels = 4;       // u32: the pixels (a locked raster's lock buffer)
inline constexpr s32 kPalette = 8;      // u32: the palette
inline constexpr s32 kWidth = 12;       // s32
inline constexpr s32 kHeight = 16;      // s32
inline constexpr s32 kDepth = 20;       // s32: bits per pixel (< 9: palettized)
inline constexpr s32 kStride = 24;      // s32: bytes per row
inline constexpr s32 kOffsetX = 28, kOffsetY = 30;  // s16: a sub-raster's offset in its parent
inline constexpr s32 kTypeByte = 32;    // u8: bits 0..2 the raster type (1 / 2 / 5: CPU-side, 5 also a camera texture)
inline constexpr s32 kCacheByte = 33;   // u8: bit 6 the palette is in GS memory, bit 7 the pixels are not its own
inline constexpr s32 kLockFlags = 34;   // u8: bits 1..2 locked (pixels / palette), bit 5 read-only
inline constexpr s32 kFormatHi = 35;    // u8: the format word's high byte (bit 7: the 0x8000 format flag; low nibble
                                        // the pixel format; 0x90 private flags)
inline constexpr s32 kSavedPixels = 36; // the raster's own pixels / width / height / stride, saved while locked
inline constexpr s32 kSavedWidth = 40, kSavedHeight = 44, kSavedStride = 48;
}  // namespace rw_raster
// The sky driver's raster extension (raster + the gp-16968 plugin offset).
namespace sky_raster {
inline constexpr s32 kTex0 = 8;         // u32: the TEX0 low word (bits 20..25 the PSM: 0x13 PSMT8, 0x14 PSMT4)
inline constexpr s32 kCacheFlags = 54;  // u8: bit 0 mipmapped (the pixels one level down), 1 / 2 swizzled PSMT8 / 4
inline constexpr s32 kCacheSlot = 88;   // u32: the texture-cache slot (rw_leaves.h rwl::kGpRasterExt)
}  // namespace sky_raster
namespace rw_image {
inline constexpr s32 kFlags = 0;        // u32: bit 1 copied by the resampler
inline constexpr s32 kWidth = 4, kHeight = 8, kDepth = 12;  // s32
inline constexpr s32 kStride = 16;      // s32: bytes per row
inline constexpr s32 kPixels = 20;      // u32
}  // namespace rw_image
// An RGBA colour as four floats (the image resampler's accumulators, Rt2d colours).
namespace rgba_f {
inline constexpr s32 kR = 0, kG = 4, kB = 8, kA = 12;
}  // namespace rgba_f
namespace rw_texture {
inline constexpr s32 kRaster = 0;       // u32
inline constexpr s32 kName = 16;        // char[32]
inline constexpr s32 kFilterAddr = 80;  // u32: bits 0..7 the filter mode, 8..11 U addressing, 12..15 V addressing
}  // namespace rw_texture

// --- an atomic, its geometry and morph targets (world.h; the instance callbacks and the clump / sector walks) --------
namespace rw_atomic {
inline constexpr s32 kFlags = 2;      // u8: bit 2 render
inline constexpr s32 kDirty = 3;      // u8: bit 0 the world sphere is stale
inline constexpr s32 kFrame = 4;      // u32
inline constexpr s32 kSphere = 28;    // f32[3]: the object bounding sphere's centre ...
inline constexpr s32 kSphereRadius = 40;  // f32 ... and radius
inline constexpr s32 kWorldSphere = 44;   // f32[3]: the world bounding sphere's centre ...
inline constexpr s32 kWorldRadius = 56;   // f32 ... and radius
inline constexpr s32 kClumpLink = 64;     // the clump's atomic list link
inline constexpr s32 kRenderCb = 72;      // u32: the render callback
inline constexpr s32 kPipeline = 108;     // u32: its pipeline (the MatFX set-up picks a PDS one)
inline constexpr s32 kGeometry = 24;  // u32
inline constexpr s32 kInterp = 76;    // the interpolation record: +4 the start morph target, +6 the end one (s16)
inline constexpr s32 kInterpStart = 4, kInterpEnd = 6;
}  // namespace rw_atomic
namespace rw_clump {
inline constexpr s32 kAtomics = 8;    // the atomic list head (links at atomic +64)
}  // namespace rw_clump
namespace rw_geometry {
inline constexpr s32 kFlags = 8;          // u32: 0x8 prelit, 0x10 normals, 0x04 / 0x80 one / two UV sets
inline constexpr s32 kLockFlags = 12;     // u16: RpGeometryLock's flags (bit 0 polygons)
inline constexpr s32 kMorphCount = 24;    // s32: morph targets
inline constexpr s32 kPrelit = 48;        // u32: the prelit colours (RGBA)
inline constexpr s32 kUv0 = 52;           // u32: the first UV set
inline constexpr s32 kUv1 = 56;           // u32: the second UV set
inline constexpr s32 kMeshHeader = 84;    // u32: the mesh header (0 after a polygon lock)
inline constexpr s32 kMorphTargets = 92;  // u32: the morph targets (rw_morph::, 28 bytes each)
inline constexpr u32 kFlagPrelit = 0x8, kFlagNormals = 0x10, kFlagUvs = 0x84, kFlagUv2 = 0x80;
}  // namespace rw_geometry
namespace rw_morph {
inline constexpr s32 kVertices = 20;  // u32: the positions (12 bytes each)
inline constexpr s32 kNormals = 24;   // u32: the normals (12 bytes each)
inline constexpr s32 kSize = 28;
}  // namespace rw_morph

// --- a world sector and the world (ps2AllSectorInstance; the world is the RW globals' current world) ----------------
namespace rw_sector {
inline constexpr s32 kVertices = 8;   // u32: positions (12 bytes each)
inline constexpr s32 kNormals = 12;   // u32: normals (3 signed bytes + pad)
inline constexpr s32 kUv0 = 16;       // u32: the first UV set
inline constexpr s32 kUv1 = 20;       // u32: the second UV set
inline constexpr s32 kPrelit = 48;    // u32: the prelit colours (RGBA)
inline constexpr s32 kLights = 64;      // the list head of the lights tied to the sector ({next, prev, light} links)
inline constexpr s32 kMeshHeader = 120;  // u32: the sector's mesh header
inline constexpr s32 kPipeline = 124;    // u32: its own pipeline (0: the world's)
inline constexpr s32 kPolygons = 132;    // u16: its polygon count
}  // namespace rw_sector
namespace rw_world {
inline constexpr s32 kFlags = 8;      // u32: as the geometry flags (0x8 prelit, 0x10 normals, 0x84 / 0x80 UV sets,
                                      // 0x20 lit, 0x40 vertex alpha, 0x01000000 native)
inline constexpr s32 kRoot = 28;      // u32: the BSP root (bsp_node::)
inline constexpr s32 kRenderCb = 104; // u32: the sector render callback
inline constexpr s32 kSectorPipe = 108;  // u32: the default sector pipeline
}  // namespace rw_world
namespace bsp_node {
inline constexpr s32 kType = 0;       // s32: >= 0 a plane node, < 0 a sector
inline constexpr s32 kLeft = 8, kRight = 12;  // u32: a plane node's children
}  // namespace bsp_node
namespace light_link {
inline constexpr s32 kNext = 0, kPrev = 4, kLight = 8;  // a sector's light list entry
}  // namespace light_link
namespace ps2all_module {
inline constexpr s32 kDefaultPipe = 64;  // u32: the global default pipeline (RW globals + gp-16840)
}  // namespace ps2all_module
inline constexpr u32 kDefaultSectorRenderCb = 0x499B90u;  // _rpSectorDefaultRenderCallBack
inline constexpr u32 kMeshBuildNone = 0x77DD90u;     // sub_499140's result without a mesh header
inline constexpr u32 kMeshBuildCb = 0x77DDA0u;       // the installed mesh build callback ...
inline constexpr u32 kMeshBuildData = 0x77DDA4u;     // ... and its data
inline constexpr u32 kMeshBuildDefault = 0x498E70u;  // sub_498E70: the default build callback
inline constexpr u32 kSectorMatchCb = 0x4992F0u;          // sub_4992F0: the find-sector callback

// --- the tri-strip builder's records (world.cpp: triStripTriangleEdge / triStripTakeTriangle / triStripExtend) -------
namespace tristrip_strip {
inline constexpr s32 kIndices = 0;  // u32: the u16 vertex indices
inline constexpr s32 kCount = 4;    // u32: their count
}  // namespace tristrip_strip
namespace tristrip_edge {
inline constexpr s32 kV0 = 0, kV1 = 2;      // u16: its two vertices
inline constexpr s32 kTri0 = 4, kTri1 = 8;  // u32: the triangles on its two sides (0 none)
}  // namespace tristrip_edge
namespace tristrip_tri {
inline constexpr s32 kEdge0 = 4, kEdge1 = 8, kEdge2 = 12;  // u32: its three edges
inline constexpr s32 kNext = 16, kPrev = 20;  // u32: its bucket list links
inline constexpr s32 kBucket = 32;            // u8: its bucket (the free neighbour count)
inline constexpr s32 kTakenHi = 24;  // u32: taken (the walk's modes 4 and up)
inline constexpr s32 kTakenLo = 28;  // u32: taken (modes below 4)
}  // namespace tristrip_tri

// =====================================================================================================================
// PS2All instancing (world.cpp: PS2AllNodeInstance, ps2AllMatClusterLayout, ps2AllInstanceSizes,
// ps2AllInstanceDmaChain and the atomic / sector / Im3D instance callbacks; world.h has the data flow)
// =====================================================================================================================

// --- the pipe data the instance functions get in $a0 ---------------------------------------------------------------
namespace ps2all_pd {
inline constexpr s32 kMatPvt = 4;      // u32: the material pipeline's private data (ps2all_matpvt::)
inline constexpr s32 kObject = 8;      // u32: the atomic / world sector / Im3D record being instanced
inline constexpr s32 kMeshHeader = 12; // u32: the mesh header (+0 its flags: mesh_hdr::)
// the set-up's record (a sector: its resEntry array; PDS 2D: the material colour)
inline constexpr s32 kObjRecord = 16;  // u32
inline constexpr s32 kObjFlags = 20;   // u32: the object's instance flags (bit 0, 4 re-instance, 8 rebuild)
inline constexpr s32 kTransType = 40;  // u8: the transType bits (the camera's | 0x2 clip, 0x4 fan, 0x10 / 0x14)
inline constexpr s32 kPrim = 41;       // u8: the primitive (1 list, 2 polyline, 3 fan / none, 4 strip)
inline constexpr s32 kVertexAlpha = 42; // u8: the world's flag 0x40
inline constexpr s32 kObjectId = 24;   // u32: the object identifier the resEntry records
inline constexpr s32 kMesh = 44;       // u32: the mesh (+0 its indices, +4 its index count)
inline constexpr s32 kResEntrySlot = 48;  // u32: the resEntry slot (*slot = the resEntry)
inline constexpr s32 kInstFlags = 52;  // u32: the instance flags (bit 4 positions, 5 normals, 6 colours, 7..8 UVs)
inline constexpr s32 kGeomFlags = 56;  // u32: the geometry flags
inline constexpr s32 kMorphStreams = 36;  // u32: the stream records beyond the ten (a morph target's)
}  // namespace ps2all_pd

// --- a mesh (pd +44): its indices ----------------------------------------------------------------------------------
namespace mesh_rd {
inline constexpr s32 kIndices = 0;     // u32: the u16 vertex indices
inline constexpr s32 kIndexCount = 4;  // u32
inline constexpr s32 kMaterial = 8;    // u32
}  // namespace mesh_rd
// --- a material (the mesh sort): +0 its texture, +4 the colour (RGBA bytes) ------------------------------------------
namespace rw_material {
inline constexpr s32 kTexture = 0;    // u32
inline constexpr s32 kAlpha = 7;      // u8: the colour's alpha
}  // namespace rw_material
// --- a light (ps2AllSectorLightCB): +2 its flags (bit 1 world) -------------------------------------------------------
namespace rw_light {
inline constexpr s32 kFlags = 2;      // u8
}  // namespace rw_light
inline constexpr u32 kSkinGeometryOffset = 0x95DE18u;  // the skin's geometry extension offset (skin globals +4)
// --- the skin plugin data (skinInstanceWeights) --------------------------------------------------------------------
namespace skin_rd {
inline constexpr s32 kWeights = 24;    // u32: a 16-byte weight record per vertex
}  // namespace skin_rd

// --- the mesh header flags (pd +12 -> +0) ---------------------------------------------------------------------------
namespace mesh_hdr {
inline constexpr s32 kFlags = 0;
inline constexpr s32 kMeshCount = 4;  // u16: the meshes
inline constexpr s32 kSerial = 6;     // u16: the header's serial (the object identifier's low half)
inline constexpr s32 kFirstOffset = 12;  // u32: the meshes start at header + 16 + this
inline constexpr s32 kMeshSize = 12;     // each mesh record
inline constexpr u32 kStrip = 0x1, kFan = 0x2, kPolyline = 0x8, kNoIndices = 0x100;
}  // namespace mesh_hdr

// --- the resEntry: +24 the instance header, +36 the vertex count ---------------------------------------------------
namespace res_entry {
inline constexpr s32 kHeader = 24;
inline constexpr s32 kVertexCount = 36;
inline constexpr s32 kObjectId = 40;    // u32: pd +24 (PS2AllNodeInstance)
inline constexpr s32 kGeomFlags = 44;   // u32: the mesh header's flags, also pd +56
}  // namespace res_entry

inline constexpr u32 kResEntryRelease = 0x49CC30u;  // sub_49CC30: the release callback PS2AllNodeInstance hands over

// --- the instance header (resEntry + 24): the cluster layout and its per-stream records ----------------------------
namespace ps2all_hdr {
inline constexpr s32 kData = 8;           // u32: the cluster data
inline constexpr s32 kClusterVerts = 24;  // u32: vertices per cluster
inline constexpr s32 kClusterCount = 28;  // u32: clusters
inline constexpr s32 kBlockClusters = 32; // u32: clusters per DMA block (ps2AllInstanceDmaChain)
inline constexpr s32 kStreams = 144;      // the per-stream records (ps2all_stream::), stream k at +144 + 24 k
}  // namespace ps2all_hdr
// One stream's record (24 bytes). The second count / offset / stride are a morph target's (two or more targets).
namespace ps2all_stream {
inline constexpr s32 kCount = 0, kCount2 = 4;     // u32: the first cluster's vertices
inline constexpr s32 kOffset = 8, kOffset2 = 12;  // u32: the stream's offset in the cluster data (quadwords)
inline constexpr s32 kStride = 16, kStride2 = 18; // s16: the cluster stride (quadwords)
inline constexpr s32 kLastBack = 20;              // s16: the last cluster's back-step (quadwords)
inline constexpr s32 kUnpack = 22;                // u16: the UNPACK address (ps2AllInstanceDmaChain)
inline constexpr s32 kSize = 24;
}  // namespace ps2all_stream
// stream k's field f in the instance header: `lw(v1, s1, strm(0, ps2all_stream::kOffset))`.
constexpr s32 strm(int k, s32 f) noexcept { return ps2all_hdr::kStreams + ps2all_stream::kSize * k + f; }
static_assert(strm(0, ps2all_stream::kOffset) == 152 && strm(10, ps2all_stream::kOffset2) == 396);

// --- the material pipeline's private data (pd +4) ------------------------------------------------------------------
namespace ps2all_matpvt {
inline constexpr s32 kResEntryAlloc = 4;   // u32: the resEntry allocator (pd, slot, size, release callback)
inline constexpr s32 kInstanceCb = 8;      // u32: the instance callback (pd, the stream addresses)
inline constexpr s32 kStreamFlags = 32;    // u32[12] at a stride of 8: stream k's flags (sflags(k))
inline constexpr s32 kStreamSize = 36;     // u32 beside each: the stream's size per vertex ((n * size + 3) / 4 qwords)
inline constexpr s32 kPipeFlags = 176;     // u32: the pipeline flags (bit 0, the type bits 2..3)
inline constexpr s32 kDoubleBuffer = 180;  // u8: double buffered
inline constexpr s32 kStreamCount = 181;   // u8: the streams the stream addresses are gathered for
inline constexpr s32 kInstStreams = 182;   // u8: the instanced streams
inline constexpr s32 kStripRecord = 184;   // the strip / polyline cluster record: +0 vertices per primitive, +1 overlap
inline constexpr s32 kStripOverlap = 185;  // u8
inline constexpr s32 kListRecord = 496;    // the list cluster record
inline constexpr s32 kListOverlap = 497;   // u8
inline constexpr u32 kInstanced = 0x1;    // a stream flag: instanced
inline constexpr u32 kSkip = 0x8;         // ... not written by the instance callbacks
inline constexpr u32 kInCluster = 0x2000; // ... in the cluster (else a separate `ref` stream)
}  // namespace ps2all_matpvt
// A cluster record of the material pipeline (+184 strips / polylines, +496 lists; ps2AllMatClusterLayout fills it):
// the batch sizes, then the per-stream records (ps2all_stream:: at +24 + 24 k) copied into the instance header.
namespace cluster_rec {
inline constexpr s32 kPrimVerts = 0;       // u8: vertices per primitive
inline constexpr s32 kOverlap = 1;         // u8: vertices each cluster after the first re-sends
inline constexpr s32 kBufferSize = 4;      // u32: the VU1 input buffer (quadwords) the clusters are sized from
inline constexpr s32 kClusterVerts = 8;    // u32: vertices per cluster
inline constexpr s32 kBatch = 12;          // u32: clusters that fit in 0xFFFF qwords
inline constexpr s32 kClusterVerts2 = 16;  // u32: ... with a morph target
inline constexpr s32 kBatch2 = 20;         // u32
inline constexpr s32 kStreams = 24;        // the per-stream records
}  // namespace cluster_rec
// stream k's field f in a bare array of stream records (ps2AllInstanceSizes' $a2).
constexpr s32 srec(int k, s32 f) noexcept { return ps2all_stream::kSize * k + f; }
// stream k's flags word: `lw(t3, a1, sflags(0))`.
constexpr s32 sflags(int k) noexcept { return 32 + 8 * k; }

// --- the vertex-order walk tables of the instance callbacks (16 bytes each) ----------------------------------------
// Per step: the slot pattern (2 bits per step of the next slot), the start slot, and three index-byte columns; one
// set for strips / lists, one for fans.
namespace walk {
inline constexpr s32 kIdentity = 0;  // u16[]: the identity index table (meshes without indices)
inline constexpr s32 kListPattern = 2, kListStart = 3, kListCol0 = 4, kListCol1 = 5, kListCol2 = 6;
inline constexpr s32 kFanPattern = 7, kFanStart = 8, kFanCol0 = 9, kFanCol1 = 12, kFanCol2 = 15;
}  // namespace walk
inline constexpr u32 kWalkAtomic = 0x7BCAC0u;  // ps2AllAtomicInstance
inline constexpr u32 kWalkIm3D = 0x7BCAE0u;    // ps2AllIm3DInstance
inline constexpr u32 kWalkSector = 0x7BCB50u;  // ps2AllSectorInstance

// --- the Im3D record ps2AllIm3DInstance instances (pd +8) and its 36-byte vertices ---------------------------------
namespace im3d_rec {
inline constexpr s32 kFlags = 0;      // u32: 0x8 positions, 0x1 UVs, 0x10 colours (with the instance flags); 0x4
                                      // the frustum test's "inside"
inline constexpr s32 kMatrix = 4;     // u32: the object matrix (0: the camera's view matrix alone)
inline constexpr s32 kVertices = 12;  // u32: the vertices (im3d_vertex::)
}  // namespace im3d_rec
namespace im3d_vertex {
inline constexpr s32 kX = 0, kY = 4, kZ = 8;  // f32
inline constexpr s32 kColour = 12;            // u8[4]: RGBA
inline constexpr s32 kU = 28, kV = 32;        // f32
inline constexpr s32 kSize = 36;
}  // namespace im3d_vertex

// --- sub_4A35C0 (attach a pipeline to an object slot) ----------------------------------------------------------------
namespace pipe_rd {
inline constexpr s32 kFlags = 8;   // u32: the pipeline's flags (the UNPACK format bits a slot requires)
inline constexpr s32 kName = 12;   // u32: its name string
}  // namespace pipe_rd
inline constexpr u32 kRwStrCmp = 0x960158u;     // the engine's string compare (RW globals + 0xE8)
inline constexpr u32 kStrPs2 = 0x7CDC60u;       // "PS2"
inline constexpr u32 kJtAttachSlot = 0x7BCB30u; // the per-slot flag checks (slots 0..5)

// --- the jump tables of the layout functions (the generated switches name their targets) ---------------------------
inline constexpr u32 kJtLayoutStreamSize = 0x7BC990u;  // ps2AllMatClusterLayout: a stream's size by type (pass 2)
inline constexpr u32 kJtLayoutStreamSizeA = 0x7BC9C0u; // ... (pass 1)
inline constexpr u32 kJtLayoutStreamSizeB = 0x7BC9E0u; // ... the third table
inline constexpr u32 kJtLayoutClusterQw = 0x7BCA10u;   // ps2AllMatClusterLayout: the per-cluster quadwords by type
inline constexpr u32 kJtInstanceSizes = 0x7BCA30u;     // ps2AllInstanceSizes: a stream's offset by type
inline constexpr u32 kJtDmaUnpack = 0x7BCA50u;         // ps2AllInstanceDmaChain: the UNPACK template by type

}  // namespace p3fes::game::rview
