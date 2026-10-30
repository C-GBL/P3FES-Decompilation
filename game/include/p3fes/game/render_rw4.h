// Slice render_rw4: RenderWare, fourth pass (docs/ANALYSIS/22_rendering.md, queue_rendering.txt) -- 150 functions of
// the RW band 0x45EC00-0x4FB100, started from p3fes_handgen and made readable (game/src/render/render_rw4.cpp).
//
// Groups (sub_* keep their symbols/functions.json names; proposed names in brackets, symbols/deltas/render_rw4.sym):
//   * RwFrame (0x4CA9B0-0x4CB9F0, 0x4CEFB0-0x4CF340, 0x4C7CF0-0x4C7D80): the module open / close, create / destroy
//     (one frame, a hierarchy), clone, add / remove child, the dirty list, the hierarchy sync, the frame-list stream.
//   * RwMatrix (0x4C2200-0x4C38C0, 0x4C19F0): multiply, the tolerance checks and the flag optimiser, rotate
//     (axis + angle, by sine / cosine), create / destroy, the module open / close, the matrix stream reader.
//   * Free lists (0x4C3960-0x4C43B0): create (with preallocated blocks), destroy, purge, for-all-used.
//   * The resource arena (0x4C45F0-0x4C4D70, 0x4C47E0, 0x4C4930, 0x4C6DF0): instanced-data entries (resEntries)
//     with their owner back-pointer and destructor, the used / free lists, allocate / free / empty / usage.
//   * Streams (0x4C12D0-0x4C1970, 0x4C4EB0-0x4C58A0): open (file, file name, memory, custom), read / write / skip /
//     close, the 12-byte chunk headers (type, size, library id -> version / build), find chunk, the int32 / real
//     readers and writers.
//   * The plugin registry (0x4C5A50-0x4C65D0): register a plugin (offset, size, id, constructor / destructor / copy),
//     init / de-init / copy an object's plugin data, the extension chunks (read / write / size / skip / rights).
//   * Textures and texture dictionaries (0x4D0C30-0x4D15E0, 0x4C81A0-0x4C8680): create / destroy, reference
//     counts, names, the current dictionary, the module, the texture / dictionary stream readers and writer.
//   * Rasters (0x4CDE40-0x4CE2C0): create / destroy through the device's standard functions, palette lock /
//     unlock, mip levels, the module.
//   * The heap users earlier render slices skipped (now paired on the stand-ins): the geometry unlock and the mesh
//     build (tri-list / tri-strip generation, the strip joiner, the polygon sort), the resEntry allocators of the
//     PS2All pipelines, the PTank clone-pipeline callbacks, the singly linked list growth, the image pixel
//     allocation and mask, the RxHeap free-block list.
//   * The raster lock / blits and the upload set-up the core3 slice left for size: the sky driver's raster lock
//     (the GS store-image read-back path), the three raster render paths (plain, scaled, fast) and their texture
//     upload set-up, the texture-cache memory raster upload.
//
// RW globals: the engine instance 0x960070 (+0 the current camera, +4 the world, +8 the frame stamp, +16 the device
// functions, the 29 standard functions from 0x9600B8, the dirty-frame list 0x96012C, the string functions 0x960134..,
// the memory functions 0x960178..0x96018C); each module's data lives at 0x960070 + its offset (a gp word written
// by the module's open). Free lists, frames, matrices, textures and rasters are records in the free lists; a stand-in
// heap serves 0x960178.. in the pair tests (tests/game/test_render_rw4.cpp).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace rw4 {

namespace rwobj {
constexpr s32 kType = 0;                      // u8 RwObject type
constexpr s32 kSubType = 1;                   // u8
constexpr s32 kFlags = 2;                     // u8
constexpr s32 kPrivateFlags = 3;              // u8 (a frame: bits 0..1 = a root with LTMs / objects to sync (in the dirty list), bits 2..3 = this frame's LTM / objects to sync)
constexpr s32 kParent = 4;                    // the parent (RwObject.parent: a frame for an object, a frame's parent frame)
}  // namespace rwobj

namespace rwframe {
constexpr s32 kDirtyNext = 8;                 // the root's link in the dirty-frame list 0x96012C (next, prev)
constexpr s32 kDirtyPrev = 12;
constexpr s32 kModelling = 16;                // RwMatrix: the modelling matrix (64 bytes)
constexpr s32 kModellingFlags = 28;           //   its flags word
constexpr s32 kLtm = 80;                      // RwMatrix: the local-to-world matrix
constexpr s32 kLtmFlags = 92;                 //   its flags word
constexpr s32 kObjects = 144;                 // the list of the objects that hang on the frame (next, prev)
constexpr s32 kObjectsPrev = 148;
constexpr s32 kChild = 152;                   // the first child
constexpr s32 kNext = 156;                    // the next sibling
constexpr s32 kRoot = 160;                    // the hierarchy's root
constexpr s32 kSize = 164;                    // (the plugins follow; the free-list entry is 192 bytes)
}  // namespace rwframe

namespace rwmatrix {
constexpr s32 kRight = 0;                     // f32 x 3
constexpr s32 kFlags = 12;                    // bit 0 normal, bit 1 orthogonal, bit 17 identity (0x20003 = all three)
constexpr s32 kUp = 16;                       // f32 x 3
constexpr s32 kPad1 = 28;
constexpr s32 kAt = 32;                       // f32 x 3
constexpr s32 kPad2 = 44;
constexpr s32 kPos = 48;                      // f32 x 3
constexpr s32 kPad3 = 60;
}  // namespace rwmatrix

namespace freelist {
constexpr s32 kEntrySize = 0;                 // bytes per entry
constexpr s32 kEntriesPerBlock = 4;
constexpr s32 kHeapSize = 8;                  // bytes of the used bitmap per block ((entries + 7) / 8)
constexpr s32 kAlignment = 12;
constexpr s32 kBlocks = 16;                   // the block list (next, prev); a block: +0 next, +4 prev, +8 the bitmap, then the entries
constexpr s32 kBlocksPrev = 20;
constexpr s32 kFlags = 24;                    // bit 0 = static (not freed), bit 1 = allocated by the free list
constexpr s32 kLink = 28;                     // the link in the list of all free lists 0x7CE8E8 (next, prev)
constexpr s32 kLinkPrev = 32;
}  // namespace freelist

namespace resarena {
constexpr s32 kSize = 0;                      // the arena size (RwResourcesSetArenaSize)
constexpr s32 kUsed = 4;                      // bytes in the arena's entries
constexpr s32 kEvicted = 8;                   // bytes evicted from this frame's list (still counted by sub_4C4D20)
constexpr s32 kHeap = 12;                     // the resource heap block (sub_4C6DF0 / sub_4C6E60 / sub_4C6F30)
constexpr s32 kListA = 16;                    // one of the two list heads (next, prev)
constexpr s32 kListAPrev = 20;
constexpr s32 kListB = 24;                    // the other list head (next, prev)
constexpr s32 kListBPrev = 28;
constexpr s32 kOlder = 32;                    // -> the head of the entries not used this frame (eviction takes their tail first)
constexpr s32 kCurrent = 36;                  // -> the head of this frame's entries (new ones are linked at its head)
}  // namespace resarena

namespace resentry {
constexpr s32 kNext = 0;                      // the link in a resource list (0 = allocated outside the arena)
constexpr s32 kPrev = 4;
constexpr s32 kSize = 8;                      // bytes of data
constexpr s32 kOwner = 12;                    // the owning object
constexpr s32 kOwnerRef = 16;                 // where the owner keeps its pointer to this entry (cleared on free)
constexpr s32 kDestroy = 20;                  // the destroy notification (called before the free)
constexpr s32 kData = 24;                     // the data
}  // namespace resentry

namespace stream {
constexpr s32 kType = 0;                      // 1 file, 2 file name, 3 memory, 4 custom
constexpr s32 kAccess = 4;                    // 1 read, 2 write, 3 append
constexpr s32 kPosition = 8;                  // (unused here)
constexpr s32 kFile = 12;                     // file / file name: the file handle; memory: the position; custom: close
constexpr s32 kMemSize = 16;                  // memory: the size; custom: read
constexpr s32 kMemStart = 20;                 // memory: the start; custom: write
constexpr s32 kCustomSkip = 24;               // custom: skip
constexpr s32 kCustomData = 28;               // custom: its data
constexpr s32 kRwOwned = 32;                  // 1 = the stream record came from the stream free list (close frees it)
}  // namespace stream

namespace plugreg {
constexpr s32 kSizeOfStruct = 0;              // the object size with every plugin so far
constexpr s32 kOrigSize = 4;
constexpr s32 kMaxSize = 8;                   // 0 = no limit
constexpr s32 kStaticAlloc = 12;
constexpr s32 kFirst = 16;                    // the first entry
constexpr s32 kLast = 20;                     // the last entry
}  // namespace plugreg

namespace plugentry {
constexpr s32 kOffset = 0;                    // where the plugin's data sits in the object
constexpr s32 kSize = 4;
constexpr s32 kPluginId = 8;
constexpr s32 kReadCb = 12;                   // stream read (stream, length, object, offset, size)
constexpr s32 kWriteCb = 16;                  // stream write
constexpr s32 kGetSizeCb = 20;                // stream size
constexpr s32 kAlwaysCb = 24;                 // called after every read of the object
constexpr s32 kRightsCb = 28;                 // the rights callback
constexpr s32 kConstructCb = 32;              // constructor (object, offset, size)
constexpr s32 kDestructCb = 36;               // destructor
constexpr s32 kCopyCb = 40;                   // copy (dst, src, offset, size)
constexpr s32 kErrStrCb = 44;
constexpr s32 kNext = 48;
constexpr s32 kPrev = 52;
constexpr s32 kParent = 56;                   // the registry
}  // namespace plugentry

namespace rwtex {
constexpr s32 kRaster = 0;                    // the raster
constexpr s32 kDict = 4;                      // the dictionary it is in (0: none)
constexpr s32 kDictNext = 8;                  // the link in the dictionary's texture list (next, prev)
constexpr s32 kDictPrev = 12;
constexpr s32 kName = 16;                     // char[32]
constexpr s32 kMask = 48;                     // char[32] the mask name
constexpr s32 kMaskLast = 79;                 //   its last byte
constexpr s32 kFilterAddressing = 80;         // filter mode in bits 0..7, the u / v addressing in 8..11 / 12..15
constexpr s32 kRefCount = 84;
}  // namespace rwtex

namespace rwtexdict {
constexpr s32 kTextures = 8;                  // the texture list head (next, prev); a texture's link is texture + 8
constexpr s32 kTexturesPrev = 12;
constexpr s32 kLink = 16;                     // the link in the module's dictionary list (next, prev)
constexpr s32 kLinkPrev = 20;
}  // namespace rwtexdict

namespace rwraster {
constexpr s32 kParent = 0;                    // the raster this one is a sub-raster of (itself for a top raster)
constexpr s32 kPixels = 4;
constexpr s32 kPalette = 8;
constexpr s32 kWidth = 12;
constexpr s32 kHeight = 16;
constexpr s32 kDepth = 20;
constexpr s32 kStride = 24;
constexpr s32 kOffsetX = 28;                  // s16
constexpr s32 kOffsetY = 30;                  // s16
constexpr s32 kType = 32;                     // u8 raster type
constexpr s32 kPrivateFlags = 33;             // u8
constexpr s32 kLockFlags = 34;                // u8: bits 3..4 = palette locked for read / write
constexpr s32 kFormat = 35;                   // u8: the raster format's high byte (0x80 = has mip levels)
}  // namespace rwraster

namespace rastmod {
constexpr s32 kContextStack = 0;              // -> the context stack below (+44)
constexpr s32 kFreeList = 96;                 // the raster free list
}  // namespace rastmod

namespace rwimage {
constexpr s32 kFlags = 0;                     // bit 0 = the pixels belong to the image (freed with it)
constexpr s32 kWidth = 4;
constexpr s32 kHeight = 8;
constexpr s32 kDepth = 12;                    // 4, 8 (palettised) or 32
constexpr s32 kStride = 16;                   // bytes per row
constexpr s32 kPixels = 20;
constexpr s32 kPalette = 24;                  // 4 << depth bytes after the pixels (depth 4 / 8)
}  // namespace rwimage

namespace slist {
constexpr s32 kData = 0;                      // the entries
constexpr s32 kCount = 4;                     // entries in use
constexpr s32 kCapacity = 8;
constexpr s32 kEntrySize = 12;
}  // namespace slist

namespace matmod {
constexpr s32 kFreeList = 0;                  // the matrix free list
constexpr s32 kFlags = 4;                     // 0x20000 after the open
constexpr s32 kMultiply = 8;                  // the multiply function (sub_4C2200 by default)
constexpr s32 kTolNormal = 12;                // f32 the three tolerances (sub_4C2CC0 / sub_4C2CF0 copy them)
constexpr s32 kTolOrthogonal = 16;
constexpr s32 kTolIdentity = 20;
}  // namespace matmod

namespace chunkhdr {
constexpr s32 kType = 0;                      // the 12-byte chunk header as read: type
constexpr s32 kLength = 4;                    // the payload length
constexpr s32 kLibraryId = 8;                 // the library id (version and build packed)
}  // namespace chunkhdr

namespace texmod {
constexpr s32 kDicts = 0;                     // the dictionary list head (next, prev)
constexpr s32 kDictsPrev = 4;
constexpr s32 kTexFreeList = 8;               // the texture free list
constexpr s32 kDictFreeList = 12;             // the texture-dictionary free list
constexpr s32 kCurrentDict = 16;              // the current dictionary
constexpr s32 kTexReadCb = 20;                // default sub_4D05F0 (reads a texture by name)
constexpr s32 kFindCb = 24;                   // default sub_4D0AC0
constexpr s32 kCb28 = 28;                     // 0 after the open
constexpr s32 kCb32 = 32;                     // 0 after the open
constexpr s32 kScratch = 36;                  // a scratch block (RwFree on close)
constexpr s32 kScratchSize = 40;              // u16
constexpr s32 kCb44 = 44;                     // default sub_4D0640
constexpr s32 kCb48 = 48;                     // default sub_4CF5C0 (called through sub_4D1210)
}  // namespace texmod

}  // namespace rw4

void sub_4DE0A0(EEContext& ctx);  // 0x4DE0A0 [skyRasterLock] -- the sky driver's raster lock (standard function 15)
void sub_4E53E0(EEContext& ctx);  // 0x4E53E0 [skyRasterRender] -- draws a raster into the current context at a point (standard function 17)
void sub_4E6D60(EEContext& ctx);  // 0x4E6D60 [skyRasterRenderScaled] -- draws a raster scaled into a rectangle (standard function 18)
void sub_4E8610(EEContext& ctx);  // 0x4E8610 [skyRasterRenderFast] -- the fast raster draw (standard function 19)
void sub_4E4E90(EEContext& ctx);  // 0x4E4E90 [skyRasterSetupForUpload] -- builds a raster's GS upload description (TEX0 fields, GS size)
void sub_4EFA00(EEContext& ctx);  // 0x4EFA00 [skyTexCacheMemRasterToGs] -- uploads a raster's memory image into its GS texture-cache slot
void sub_4AB0E0(EEContext& ctx);  // 0x4AB0E0 [rt2dObjectNodeDestroy] -- frees one Rt2d list node and returns its successor
void sub_4C1E70(EEContext& ctx);  // 0x4C1E70 [sListGetNewEntry] -- appends an entry to a growable array (grows by a quarter)
void sub_4C47E0(EEContext& ctx);  // 0x4C47E0 [resEntryFree] -- frees one resEntry
void sub_4C4930(EEContext& ctx);  // 0x4C4930 [resEntryAllocate] -- allocates a resEntry in the arena, evicting old entries until it fits
void sub_4CBF20(EEContext& ctx);  // 0x4CBF20 [imageAllocatePixels] -- allocates an image's pixels (and palette) and marks them owned
void sub_4CC1D0(EEContext& ctx);  // 0x4CC1D0 [imageApplyMask] -- copies a mask image's alpha into an image (converting it to 32 bits)
void sub_4F61C0(EEContext& ctx);  // 0x4F61C0 [rxHeapFreeBlocksNewEntry] -- appends an entry to the RxHeap's free-block array (grows by 32)
void sub_4933D0(EEContext& ctx);  // 0x4933D0 [geometryUnlock] -- unlocks a geometry: rebuilds its mesh (tri-strips or tri-list) when it has none
void sub_495CF0(EEContext& ctx);  // 0x495CF0 [buildMeshAddTriangle] -- appends a triangle to a build mesh (20-byte records, grows by one)
void sub_4967A0(EEContext& ctx);  // 0x4967A0 [meshSortTriListPolygons] -- reorders a tri-list mesh's triangles so neighbours share no vertex
void sub_4982B0(EEContext& ctx);  // 0x4982B0 [triStripJoin] -- joins the strips of a tri-strip build into one index list (degenerate links)
void sub_497600(EEContext& ctx);  // 0x497600 [triStripStripTris] -- finds tri-strips over a mesh's triangles (the strip search)
void sub_498720(EEContext& ctx);  // 0x498720 [triStripMeshGenerate] -- builds a tri-strip mesh header from a build mesh
void sub_498E70(EEContext& ctx);  // 0x498E70 [triListMeshGenerate] -- builds a tri-list mesh header from a build mesh
void sub_49E5A0(EEContext& ctx);  // 0x49E5A0 [objectMeshCacheResize] -- re-allocates an object's mesh cache (the resEntries per mesh)
void sub_4A08F0(EEContext& ctx);  // 0x4A08F0 [ps2AllAtomicResEntryAlloc] -- allocates an atomic's instance data (PS2All resEntry callback)
void sub_4A0CE0(EEContext& ctx);  // 0x4A0CE0 [ps2AllMeshResEntryAllocCB] -- the PS2All mesh resEntry callback: world sectors here, atomics through sub_4A08F0
void sub_47BB40(EEContext& ctx);  // 0x47BB40 [ptankClonePipeAlloc] -- allocates a PTank clone pipeline's matrix array (RwMalloc, 16-aligned)
void sub_47BE10(EEContext& ctx);  // 0x47BE10 [ptankClonePipeRender] -- renders a PTank's clone pipeline (the render-state wrapped draw)
void sub_4CA9B0(EEContext& ctx);  // 0x4CA9B0 [frameModuleOpen] -- the frame module's open: the free list, the dirty-frame list
void sub_4CAA50(EEContext& ctx);  // 0x4CAA50 [frameModuleClose] -- the frame module's close: destroys the free list
void sub_4CAB70(EEContext& ctx);  // 0x4CAB70 [frameCloneRecurse] -- clones a frame and its subtree (one level of the clone)
void sub_4CACE0(EEContext& ctx);  // 0x4CACE0 [frameCloneHierarchy] -- clones a whole hierarchy and marks the clone dirty
void sub_4CAD30(EEContext& ctx);  // 0x4CAD30 [frameSetHierarchyRoot] -- re-points every frame of a subtree at its hierarchy's root
void sub_4CAE40(EEContext& ctx);  // 0x4CAE40 [frameInit] -- initialises a fresh frame and runs the frame plugins' constructors
void sub_4CAF10(EEContext& ctx);  // 0x4CAF10 [frameCreate] -- creates a frame (the free list, then sub_4CAE40)
void sub_4CAF80(EEContext& ctx);  // 0x4CAF80 [frameDestroy] -- destroys one frame: plugins, parent, dirty list, children orphaned, freed
void sub_4CB050(EEContext& ctx);  // 0x4CB050 [frameDestroySubtree] -- destroys a frame's subtree and the frame (recursive)
void sub_4CB1B0(EEContext& ctx);  // 0x4CB1B0 [frameDestroyHierarchy] -- destroys a frame and everything below it
void sub_4CB270(EEContext& ctx);  // 0x4CB270 [frameUpdateObjects] -- marks a frame dirty (the hierarchy's root joins the dirty list)
void sub_4CB340(EEContext& ctx);  // 0x4CB340 [frameGetRoot] -- returns the frame's hierarchy root
void sub_4CB350(EEContext& ctx);  // 0x4CB350 [frameAddChildNoUpdate] -- adds a child at the head of a frame's child list, without marking dirty
void sub_4CB420(EEContext& ctx);  // 0x4CB420 [frameAddChild] -- adds a child to a frame and marks it dirty
void sub_4CB590(EEContext& ctx);  // 0x4CB590 [frameRemoveChild] -- takes a frame off its parent: it becomes its own hierarchy, marked dirty
void sub_4CB6E0(EEContext& ctx);  // 0x4CB6E0 [frameForAllChildren] -- calls a callback on each child until it returns 0
void sub_4CB750(EEContext& ctx);  // 0x4CB750 [frameOrthoNormalize] -- ortho-normalises the modelling matrix and marks the frame dirty
void sub_4CB890(EEContext& ctx);  // 0x4CB890 [frameRotate] -- rotates the modelling matrix (axis, angle, combine) and marks the frame dirty
void sub_4CB930(EEContext& ctx);  // 0x4CB930 [frameSetIdentity] -- sets the modelling matrix to identity and marks the frame dirty
void sub_4CB9F0(EEContext& ctx);  // 0x4CB9F0 [frameRegisterPlugin] -- registers a frame plugin (sub_4C61B0 on the frame registry)
void sub_4CEFB0(EEContext& ctx);  // 0x4CEFB0 [frameSyncChildren] -- the hierarchy sync below a root: LTMs and object syncs (recursive)
void sub_4CF0A0(EEContext& ctx);  // 0x4CF0A0 [frameSyncObjectsOnly] -- the object-only sync below a root (no LTM work; recursive)
void sub_4CF1B0(EEContext& ctx);  // 0x4CF1B0 [frameSyncHierarchy] -- syncs one dirty hierarchy from its root
void sub_4CF340(EEContext& ctx);  // 0x4CF340 [frameSyncDirty] -- syncs every hierarchy in the dirty-frame list and empties it
void sub_4C7CF0(EEContext& ctx);  // 0x4C7CF0 [frameSetStreamUpdate] -- stores the frame-list reader's 'mark roots dirty' switch (gp 0x7CDD60)
void sub_4C7D00(EEContext& ctx);  // 0x4C7D00 [frameRegisterPluginStream] -- sets a frame plugin's stream callbacks (read, write, size)
void sub_4C7D30(EEContext& ctx);  // 0x4C7D30 [frameListDeinit] -- frees a frame list's array
void sub_4C7D80(EEContext& ctx);  // 0x4C7D80 [frameListStreamRead] -- reads a frame list chunk: the frames, their hierarchy, their plugins
void sub_4C2200(EEContext& ctx);  // 0x4C2200 [matrixMultiplyDefault] -- dst = a x b for 3x4 matrices (the module's default multiply)
void sub_4C2A30(EEContext& ctx);  // 0x4C2A30 [matrixSetMultiplyFn] -- sets the matrix module's multiply function (0: the default sub_4C2200)
void sub_4C2A70(EEContext& ctx);  // 0x4C2A70 [matrixDeterminant] -- the determinant of the 3x3 part, in $f0
void sub_4C2AC0(EEContext& ctx);  // 0x4C2AC0 [matrixOrthogonalError] -- the sum of the squared dot products of the three axes, in $f0
void sub_4C2B20(EEContext& ctx);  // 0x4C2B20 [matrixNormalError] -- the sum of the squared (length^2 - 1) of the three axes, in $f0
void sub_4C2B90(EEContext& ctx);  // 0x4C2B90 [matrixModuleClose] -- the matrix module's close: destroys its free list
void sub_4C2C00(EEContext& ctx);  // 0x4C2C00 [matrixModuleOpen] -- the matrix module's open: the free list, the multiply function, the tolerances
void sub_4C2CC0(EEContext& ctx);  // 0x4C2CC0 [matrixGetTolerances] -- copies the three matrix tolerances out ($a0 = 3 floats); returns 1
void sub_4C2CF0(EEContext& ctx);  // 0x4C2CF0 [matrixSetTolerances] -- sets the three matrix tolerances from $a0 (3 floats); returns 1
void sub_4C2D20(EEContext& ctx);  // 0x4C2D20 [matrixOptimize] -- sets a matrix's normal / orthogonal / identity flags from its values
void sub_4C2F10(EEContext& ctx);  // 0x4C2F10 [matrixUpdate] -- clears a matrix's normal / orthogonal / identity flags (after an edit); returns it
void sub_4C2FC0(EEContext& ctx);  // 0x4C2FC0 [matrixRotateOneMinusCosineSine] -- rotates a matrix about a unit axis, from (1 - cos) and sin
void sub_4C31B0(EEContext& ctx);  // 0x4C31B0 [matrixRotate] -- rotates a matrix about an axis by an angle in degrees
void sub_4C3880(EEContext& ctx);  // 0x4C3880 [matrixDestroy] -- returns a matrix to the matrix free list (slot 0x96018C); returns 1
void sub_4C38C0(EEContext& ctx);  // 0x4C38C0 [matrixCreate] -- a new identity matrix from the matrix free list
void sub_4B91B0(EEContext& ctx);  // 0x4B91B0 [matrixStreamGetSize] -- the size of a matrix chunk's payload: 64
void sub_4C19F0(EEContext& ctx);  // 0x4C19F0 [matrixStreamRead] -- reads a matrix from a stream (a struct chunk of 52 bytes)
void sub_4C3960(EEContext& ctx);  // 0x4C3960 [freeListSetPrealloc] -- sets the free lists' preallocation switch (gp 0x7CDD38)
void sub_4C3970(EEContext& ctx);  // 0x4C3970 [freeListCreate] -- creates (or initialises) a free list and preallocates blocks
void sub_4C3B50(EEContext& ctx);  // 0x4C3B50 [freeListCreateOneBlock] -- sub_4C3970 with one preallocated block and no static record
void sub_4C3B60(EEContext& ctx);  // 0x4C3B60 [freeListCreateFull] -- sub_4C3970 with all six arguments (tail call; the entry the modules use)
void sub_4C3B70(EEContext& ctx);  // 0x4C3B70 [freeListFree] -- frees a free list's blocks and (unless static) its record
void sub_4C3C30(EEContext& ctx);  // 0x4C3C30 [freeListDestroy] -- destroys a free list: out of the global list, blocks freed, record freed
void sub_4C4080(EEContext& ctx);  // 0x4C4080 [freeListPurge] -- frees a free list's empty blocks; returns the bytes released
void sub_4C4200(EEContext& ctx);  // 0x4C4200 [freeListForAllUsed] -- calls a callback on every entry in use, from a snapshot of each bitmap
void sub_4C43B0(EEContext& ctx);  // 0x4C43B0 [freeListPurgeAll] -- purges every free list (sub_4C4080); returns the total bytes released
void sub_4C45F0(EEContext& ctx);  // 0x4C45F0 [resArenaInit] -- initialises the resource arena (its heap block and its two lists)
void sub_4C46F0(EEContext& ctx);  // 0x4C46F0 [resModuleOpen] -- the resource module's open: the arena at its offset
void sub_4C4750(EEContext& ctx);  // 0x4C4750 [resModuleClose] -- the resource module's close: empties the arena, frees its heap
void sub_4C4890(EEContext& ctx);  // 0x4C4890 [resArenaNewFrame] -- the arena's frame flip: this frame's entries become the older ones
void RwResourcesSetArenaSize(EEContext& ctx);  // 0x4C4C00 -- sets the resource arena's size (before the open: just the size word)
void sub_4C4D20(EEContext& ctx);  // 0x4C4D20 [resArenaGetUsage] -- this frame's resource use: the evicted bytes + the entries in this frame's list
void sub_4C4D70(EEContext& ctx);  // 0x4C4D70 [resArenaEmpty] -- frees every entry of the arena
void sub_4C6DF0(EEContext& ctx);  // 0x4C6DF0 [resHeapInit] -- sets up the resource heap in a block: one free span
void sub_4C6E50(EEContext& ctx);  // 0x4C6E50 [resHeapClose] -- the resource heap's close (nothing to do); returns 1
void sub_4C12D0(EEContext& ctx);  // 0x4C12D0 [chunkIsComplex] -- 1 when a chunk type holds sub-chunks (types 5..11, 14..16, 18, 20, 26), else 0
void sub_4C1450(EEContext& ctx);  // 0x4C1450 [streamReadChunkHeader] -- reads a 12-byte chunk header; returns type / length / version / build
void sub_4C15A0(EEContext& ctx);  // 0x4C15A0 [streamWriteVersionedChunkHeader] -- writes a chunk header (type, length, version, build)
void sub_4C1600(EEContext& ctx);  // 0x4C1600 [streamFindChunk] -- skips chunks until one of the wanted type; returns its length / version
void sub_4C1750(EEContext& ctx);  // 0x4C1750 [streamWriteReal] -- writes floats to a stream, through a 256-byte stack buffer
void sub_4C17F0(EEContext& ctx);  // 0x4C17F0 [streamWriteInt32] -- writes 32-bit integers (sub_4C53F0); returns the stream
void sub_4C1820(EEContext& ctx);  // 0x4C1820 [streamWriteInt32b] -- writes 32-bit integers: a second copy of sub_4C17F0 (identical body); returns the stream
void sub_4C1850(EEContext& ctx);  // 0x4C1850 [streamReadInt32] -- reads 32-bit integers (sub_4C5250); 0 and error 0x8000001A when nothing is read
void sub_4C18B0(EEContext& ctx);  // 0x4C18B0 [streamReadReal] -- reads floats (sub_4C5250); 0 and error 0x8000001A when nothing is read
void sub_4C1910(EEContext& ctx);  // 0x4C1910 [streamReadInt32b] -- reads 32-bit integers: a second copy of sub_4C1850 (identical body); 0 and error 0x8000001A on failure
void sub_4C1970(EEContext& ctx);  // 0x4C1970 [streamReadChunkHeaderInfo] -- reads a chunk header into a 20-byte info record
void sub_4C4EB0(EEContext& ctx);  // 0x4C4EB0 [streamModuleOpen] -- the stream module's open: the stream free list
void sub_4C4F30(EEContext& ctx);  // 0x4C4F30 [streamModuleClose] -- the stream module's close: destroys the free list; count down
void sub_4C4F90(EEContext& ctx);  // 0x4C4F90 [streamOpenFileName] -- opens a file-name stream: the file opened in the access mode
void sub_4C5090(EEContext& ctx);  // 0x4C5090 [streamOpenMemory] -- opens a memory stream over {start, size}
void sub_4C5140(EEContext& ctx);  // 0x4C5140 [streamInitialize] -- fills a stream record by type (file, file name, memory, custom)
void sub_4C5250(EEContext& ctx);  // 0x4C5250 [streamRead] -- reads bytes from a stream; returns the count read
void sub_4C53F0(EEContext& ctx);  // 0x4C53F0 [streamWrite] -- writes bytes to a stream; returns the stream or 0
void sub_4C5620(EEContext& ctx);  // 0x4C5620 [streamSkip] -- skips bytes in a stream; returns the stream or 0
void sub_4C5780(EEContext& ctx);  // 0x4C5780 [streamClose] -- closes a stream (and frees its record when the free list owns it)
void sub_4C58A0(EEContext& ctx);  // 0x4C58A0 [streamOpen] -- opens a stream: a record from the stream free list, filled by sub_4C5140
void sub_4C5A50(EEContext& ctx);  // 0x4C5A50 [pluginRegistryReadDataChunks] -- reads an object's extension chunk: each plugin's data, then the always callbacks
void sub_4C5C30(EEContext& ctx);  // 0x4C5C30 [pluginRegistryInvokeRights] -- calls the rights callback of the plugin with a given id
void sub_4C5CB0(EEContext& ctx);  // 0x4C5CB0 [pluginRegistryGetSize] -- the bytes an object's extension chunk payload takes
void sub_4C5D30(EEContext& ctx);  // 0x4C5D30 [pluginRegistryWriteDataChunks] -- writes an object's extension chunk (the plugins with data)
void sub_4C5EA0(EEContext& ctx);  // 0x4C5EA0 [pluginRegistrySkipDataChunks] -- skips an extension chunk and all its sub-chunks
void sub_4C5F70(EEContext& ctx);  // 0x4C5F70 [pluginModuleOpen] -- the plugin module's open: the free list of 60-byte plugin entries
void sub_4C6000(EEContext& ctx);  // 0x4C6000 [pluginModuleClose] -- the plugin module's close: every registry reset, the entries freed
void sub_4C6140(EEContext& ctx);  // 0x4C6140 [pluginDefaultConstructor] -- the default plugin constructor: returns the object
void sub_4C6150(EEContext& ctx);  // 0x4C6150 [pluginDefaultDestructor] -- the default plugin destructor: returns the object
void sub_4C6160(EEContext& ctx);  // 0x4C6160 [pluginDefaultCopy] -- the default plugin copy: returns the destination
void sub_4C61B0(EEContext& ctx);  // 0x4C61B0 [pluginRegistryAddPlugin] -- registers a plugin: its data offset in the object, its callbacks
void sub_4C64B0(EEContext& ctx);  // 0x4C64B0 [pluginRegistryInitObject] -- runs every plugin constructor on an object (unwinds on failure)
void sub_4C6560(EEContext& ctx);  // 0x4C6560 [pluginRegistryDeInitObject] -- runs every plugin destructor on an object, last first; returns the registry
void sub_4C65D0(EEContext& ctx);  // 0x4C65D0 [pluginRegistryCopyObject] -- runs every plugin copy (dst, src); returns the registry
void sub_4D0C30(EEContext& ctx);  // 0x4D0C30 [texDictCreate] -- creates an empty texture dictionary (linked into the module's list)
void sub_4D0D10(EEContext& ctx);  // 0x4D0D10 [texDictDestroy] -- destroys a texture dictionary and every texture in it
void sub_4D0DC0(EEContext& ctx);  // 0x4D0DC0 [texDictForAllTextures] -- calls a callback on each texture of a dictionary until it returns 0
void sub_4D0E40(EEContext& ctx);  // 0x4D0E40 [textureCreate] -- creates a texture over a raster
void sub_4D0F00(EEContext& ctx);  // 0x4D0F00 [textureDestroy] -- drops a texture reference; the last one destroys it
void sub_4D1070(EEContext& ctx);  // 0x4D1070 [textureSetMaskName] -- copies a texture's mask name (32 bytes, NUL forced on overflow)
void sub_4D1110(EEContext& ctx);  // 0x4D1110 [texDictAddTexture] -- moves a texture into a dictionary (at the head of its list)
void sub_4D1170(EEContext& ctx);  // 0x4D1170 [texDictFindNamedTexture] -- finds a texture in a dictionary by name (sub_4D09D0 compares)
void sub_4D11F0(EEContext& ctx);  // 0x4D11F0 [texDictGetCurrent] -- returns the module's current texture dictionary
void sub_4D1210(EEContext& ctx);  // 0x4D1210 [textureGenerateMipName] -- calls the module's callback +48 if set (else 0)
void sub_4D13B0(EEContext& ctx);  // 0x4D13B0 [textureRegisterPlugin] -- registers a texture plugin (sub_4C61B0 on the texture registry)
void sub_4D1420(EEContext& ctx);  // 0x4D1420 [textureModuleClose] -- the texture module's close: scratch block, own dictionary, free lists
void sub_4D15E0(EEContext& ctx);  // 0x4D15E0 [textureModuleOpen] -- the texture module's open: free lists, its own dictionary, the callbacks
void sub_4C81A0(EEContext& ctx);  // 0x4C81A0 [textureRegisterPluginStream] -- sets a texture plugin's stream callbacks (the registries' shared chunk)
void sub_4C81D0(EEContext& ctx);  // 0x4C81D0 [textureStreamGetSize] -- the bytes a texture chunk takes
void sub_4C8240(EEContext& ctx);  // 0x4C8240 [textureStreamWrite] -- writes a texture chunk: struct, name, mask, extension
void sub_4C83C0(EEContext& ctx);  // 0x4C83C0 [textureStreamRead] -- reads a texture chunk: the texture comes from the read-by-name path
void sub_4C8650(EEContext& ctx);  // 0x4C8650 [texDictDestroyTextureCB] -- the dictionary walk's callback: sub_4D0F00(texture), returns the texture
void sub_4C8680(EEContext& ctx);  // 0x4C8680 [texDictStreamRead] -- reads a texture dictionary chunk: native textures, their extensions
void sub_4CDE40(EEContext& ctx);  // 0x4CDE40 [rasterUnlockPalette] -- unlocks a raster's palette (standard function 24), clears its lock bits 3..4
void sub_4CDE90(EEContext& ctx);  // 0x4CDE90 [rasterDestroy] -- destroys a raster: plugins, the device's destroy, back to the free list
void sub_4CDF00(EEContext& ctx);  // 0x4CDF00 [rasterRegisterPlugin] -- registers a raster plugin (sub_4C61B0 on the raster registry)
void sub_4CDF30(EEContext& ctx);  // 0x4CDF30 [rasterLockPalette] -- locks a raster's palette (standard function 23); returns the palette or 0
void sub_4CDF80(EEContext& ctx);  // 0x4CDF80 [rasterGetNumLevels] -- a raster's mip level count (1 without the mipmap format bit; -1 on failure)
void sub_4CE0F0(EEContext& ctx);  // 0x4CE0F0 [rasterCreate] -- creates a raster through the device (standard function 4)
void sub_4CE250(EEContext& ctx);  // 0x4CE250 [rasterModuleClose] -- the raster module's close: destroys the raster free list; count down
void sub_4CE2C0(EEContext& ctx);  // 0x4CE2C0 [rasterModuleOpen] -- the raster module's open: the context stack, the raster free list

}  // namespace p3fes::game
