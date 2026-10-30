// Slice render_rw6: RenderWare, sixth pass -- the collision intersection tests (what the server will need for
// collision), the Rt2d toolkit's state / path / brush / object helpers, the RtFS file-system manager, the sList helpers,
// the PS2AllMat pipeline-node set-up and the engine's device requests: 163 functions of the RW band 0x45F930-0x4F3F70,
// started from p3fes_handgen and made readable (game/src/render/render_rw6.cpp).
//
// Groups (sub_* keep their symbols/functions.json names; proposed names in brackets, symbols/deltas/render_rw6.sym):
//   * Collision (0x45F930-0x463F20, 0x4BAE00, 0x4BB5D0): the world tests behind RpCollisionWorldForAllIntersections --
//     a line (sub_45F930), a sphere (sub_460EC0), a box (sub_4606B0) walked down the world's BSP and each sector's
//     collision tree, every candidate triangle tested and handed to the callback --, the geometry tests behind
//     RpAtomicForAllIntersections -- the atomic's sphere into the atomic's space (sub_463F20), a line or a sphere
//     against a one-morph-target geometry through its collision tree (sub_461EA0 / sub_462BB0, or every triangle:
//     sub_461900 / sub_461D00) or against the interpolated vertices of two morph targets (sub_463490 / sub_463B20) --,
//     and the two triangle tests: sphere / triangle (sub_4BAE00, with the contact normal and distance) and box /
//     triangle (sub_4BB5D0, separating axes).
//   * Rt2d (0x4A5400-0x4B6500, 0x4A53B0, 0x4A5540): the toolkit's open / close pieces (free lists, the current
//     transformation stack, the 2-D pipelines from RpPDSGetPipe), the CTM translate / scale, path building (move / line
//     / curve segments with their normals and lengths), the point-in-path test, path flattening helpers (orientation of
//     a corner, the triangle classification), brush / font / object-string helpers, the scene's object lists and the
//     animation / maestro data's lists (props, frames, messages, buttons): create, destroy, walk.
//   * RtFS (0x4BF6E0-0x4C0FD0): the file-system manager -- the registered file systems' list (find by name, register,
//     the name prefix), a file system's init (its files, its name), the generic file-system creation with its 112-byte
//     file records and default callbacks, the stream read / write adaptors that go through a file's callbacks.
//   * sList (0x4C1BC0-0x4C21E0): the sList growth by n entries, destroy, to-array, the end pointer, the count
//     shrink, and the small module open / close / error-slot helpers beside them.
//   * PS2AllMat (0x4A38F0-0x4A5330, 0x4F3EC0, 0x4F3F70): the node's initialisation data (RxPipelineNodeCreateInitData /
//     RxPipelineNodeGetInitData) and the cluster set-ups of the tri-list, tri-strip and point / line batches, the
//     node's private callbacks, VU1 code array and VIF offset; the PS2 pipeline-id plugin of atomics, world sectors and
//     geometries (constructor, stream-always callbacks that look the pipeline up by id, registration); the default
//     material / sector / atomic pipelines from RpPDSGetPipe.
//   * Engine (0x4CA380-0x4CA600): the device's system requests (_rwDeviceSystemRequest and its standard answers),
//     the video-mode and sub-system queries / setters, the engine plugin registration and its offset lookup, the
//     resource-arena memory callbacks.
//
// RW globals as in render_rw5.h (the engine instance 0x960070, + a module offset = that module's data). The engine's
// string functions (the public RwStringFunctions order) sit at 0x960134..: strcpy 0x96013C, strcmp 0x960158, the
// case-insensitive compare 0x960160, strlen 0x960164; the memory functions at 0x960178.. (RwMalloc, RwFree, RwRealloc,
// RwCalloc, the free-list alloc / free).
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/render_rw5.h"  // rw5:: (and rw4::) the scene layouts: sectors, worlds, geometries, atomics, BSP nodes

namespace p3fes::game {

namespace rw6 {

namespace isect {                             // RpIntersection: the shape (24 bytes) and its type
constexpr s32 kLineStart = 0;                 // a line: f32 x 3 start, f32 x 3 end
constexpr s32 kLineEnd = 12;
constexpr s32 kSphereCentre = 0;              // a sphere: f32 x 3 centre, f32 radius
constexpr s32 kSphereRadius = 12;
constexpr s32 kBoxSup = 0;                    // a box: f32 x 3 maximum, f32 x 3 minimum
constexpr s32 kBoxInf = 12;
constexpr s32 kType = 24;                     // 1 line, 3 sphere, 4 box, 5 atomic (its world bounding sphere)
}  // namespace isect

namespace colltri {                           // RpCollisionTriangle (40 bytes, on the walker's stack)
constexpr s32 kNormal = 0;                    // f32 x 3 the unit face normal
constexpr s32 kPoint = 12;                    // f32 x 3 its first vertex
constexpr s32 kIndex = 24;                    // the triangle's index in the sector / geometry
constexpr s32 kVertex0 = 28;                  // -> its three vertices
constexpr s32 kVertex1 = 32;
constexpr s32 kVertex2 = 36;
constexpr s32 kSize = 40;
}  // namespace colltri

namespace tri {                               // a sector / geometry triangle (8 bytes)
constexpr s32 kV0 = 0;                        // u16 vertex indices
constexpr s32 kV1 = 2;
constexpr s32 kV2 = 4;
constexpr s32 kMaterial = 6;                  // u16
constexpr s32 kSize = 8;
}  // namespace tri

namespace wsect {                             // RpWorldSector, beside rw5::sector
constexpr s32 kTriangles = 4;                 // the triangle array (rw6::tri records)
constexpr s32 kVertices = 8;                  // f32 x 3 per vertex
}  // namespace wsect

namespace geo {                               // RpGeometry, beside rw5::geometry
constexpr s32 kNumTriangles = 16;
constexpr s32 kNumMorphTargets = 24;
constexpr s32 kTriangles = 44;                // the triangle array (rw6::tri records)
constexpr s32 kMorphTargets = 92;             // 28-byte records (rw5::morph): +20 the vertices
}  // namespace geo

namespace interp {                            // RpInterpolator (the atomic's, at atomic + 76)
constexpr s32 kAtomicOffset = 76;
constexpr s32 kFlags = 0;
constexpr s32 kStartMorph = 4;                // s16
constexpr s32 kEndMorph = 6;                  // s16
constexpr s32 kTime = 8;
constexpr s32 kRecipTime = 12;                // f32: the blend factor is recipTime x position
constexpr s32 kPosition = 16;
}  // namespace interp

namespace collsplit {                         // a collision-tree split (16 bytes): two child entries
constexpr s32 kLeftType = 0;                  // u8: bits 2..3 the split's axis offset (0 / 4 / 8)
constexpr s32 kLeftCount = 1;                 // u8: 0xFF = the child is a split, else its triangle count
constexpr s32 kLeftIndex = 2;                 // u16: the child split, or its first triangle (through the map)
constexpr s32 kLeftValue = 4;                 // f32: the left child's upper bound on the axis
constexpr s32 kRight = 8;                     // the right child entry
constexpr s32 kRightType = 8;
constexpr s32 kRightCount = 9;
constexpr s32 kRightIndex = 10;
constexpr s32 kRightValue = 12;               // f32: the right child's lower bound
constexpr s32 kSize = 16;
}  // namespace collsplit

namespace pnode {                             // RxPipelineNode (the public layout)
constexpr s32 kNodeDef = 0;
constexpr s32 kPrivateData = 20;              // the node's private data
constexpr s32 kInitData = 32;                 // the initialisation data and its size
constexpr s32 kInitDataSize = 36;
}  // namespace pnode

namespace allmatpriv {                        // the PS2AllMat node's private data
constexpr s32 kCallBack1 = 0;                 // the five callbacks by type 1..5 (types 2..4 refuse 0)
constexpr s32 kCallBack2 = 4;
constexpr s32 kCallBack3 = 8;
constexpr s32 kCallBack4 = 12;
constexpr s32 kCallBack5 = 16;
constexpr s32 kVifOffset = 20;                // (sub_4A3D70)
constexpr s32 kVU1Code = 24;                  // the VU1 code array and its length (default 0x77F130, 32)
constexpr s32 kVU1CodeCount = 28;
}  // namespace allmatpriv

namespace allmatinit {                        // the PS2AllMat node's 64-byte initialisation data (the batch set-up)
constexpr s32 kClusters = 0;                  // 40 bytes cleared at creation
constexpr s32 kBatchWords = 48;               // the batch size in words / vertices (69 x 4 by default)
constexpr s32 kBatchSize = 52;
constexpr s32 kStride = 56;                   // the input cluster's stride (4 by default)
constexpr s32 kPrimFlags = 60;                // 3 tri-list, 12 tri-strip, 16 point / line; 0 unset
}  // namespace allmatinit

namespace rtfs {                              // an RtFS file system (the manager's list record)
constexpr s32 kNext = 0;                      // the next registered file system
constexpr s32 kMaxFiles = 4;
constexpr s32 kStatus = 8;                    // 2 after a good init
constexpr s32 kDevice = 12;                   // the device name (a heap copy; the case-insensitive lookup compares it)
constexpr s32 kWord16 = 16;                   // 0 at the init, copied into every file's +48
constexpr s32 kGetFile = 20;                  // (fs, index) -> the file record
constexpr s32 kClose = 24;                    // the file system's close (frees the file array)
constexpr s32 kGetHandle = 28;
constexpr s32 kRegister = 32;                 // called with the name on registration
constexpr s32 kUnregister = 36;
constexpr s32 kFileOps = 40;                  // the file operations (open, close, read, write, seek, ... 10 slots)
constexpr s32 kFileRead = 48;                 // (file, buffer, bytes)
constexpr s32 kFileWrite = 52;
constexpr s32 kFileEof = 68;
constexpr s32 kName = 80;                     // the file system's name (its path prefix)
constexpr s32 kFiles = 88;                    // the 112-byte file records
}  // namespace rtfs

namespace rtfile {                            // an RtFS file record (112 bytes)
constexpr s32 kLength = 0;                    // u64 the file's length
constexpr s32 kPosition = 16;                 // u64 the position (-1: none)
constexpr s32 kOwnerWord = 48;                // the file system's +16 word at its init; 0 = no completion callback
constexpr s32 kStatus = 56;                   // 1 at the init and after sub_4C0F60; 3 after a seek
constexpr s32 kState = 64;                    // 1 idle; 4 after a seek (the callback then gets the position)
constexpr s32 kResult = 68;
constexpr s32 kCallBack = 72;                 // called (file, result or position, status, state) when an operation ends
constexpr s32 kCallBackData = 76;
constexpr s32 kFs = 80;                       // the owning file system (its file operations at +40..)
constexpr s32 kBuffer = 104;                  // the generic file system's per-file buffer and its size (sub_4C0FD0)
constexpr s32 kBufferSize = 108;
constexpr s32 kSize = 112;
}  // namespace rtfile

namespace path2d {                            // an Rt2d path (a chain of sub-paths)
constexpr s32 kSegments = 0;                  // the sList of 24-byte segments (rw6::seg2d)
constexpr s32 kNumSegments = 4;               // -1: the sList's count (the point-inside test and the bounds read it)
constexpr s32 kWord8 = 8;                     // cleared by the empty
constexpr s32 kFlat = 12;                     // 1 after the empty; 0 after a curve segment (the bounds flatten it first)
constexpr s32 kNext = 20;                     // the next sub-path
constexpr s32 kCurrent = 24;                  // the sub-path segments are appended to (the path itself after the empty)
}  // namespace path2d

namespace seg2d {                             // an Rt2d path segment (24 bytes)
constexpr s32 kType = 0;                      // 1 line, 2 curve control point
constexpr s32 kX = 4;
constexpr s32 kY = 8;
constexpr s32 kNormalX = 12;                  // the unit normal of the segment ending here, averaged with the next one's (mitre)
constexpr s32 kNormalY = 16;
constexpr s32 kDistance = 20;                 // the path length up to this point
constexpr s32 kSize = 24;
}  // namespace seg2d

namespace devreq {                            // the device's system-request entry (the engine at 0x960080)
constexpr s32 kSystem = 4;                    // the device's system function (request, out, in, number)
}  // namespace devreq

}  // namespace rw6

// --- the bodies (register ABI: arguments in $a0.., $f12.., the result in $v0 / $f0) ---------------------------------
void sub_45F930(EEContext& ctx);  // 0x45F930 [collWorldLineIntersections] -- the line test of RpCollisionWorldForAllIntersections: every triangle the line crosses
void sub_4606B0(EEContext& ctx);  // 0x4606B0 [collWorldBoxIntersections] -- the box test of RpCollisionWorldForAllIntersections: every triangle that overlaps the box
void sub_460EC0(EEContext& ctx);  // 0x460EC0 [collWorldSphereIntersections] -- the sphere test of RpCollisionWorldForAllIntersections: every triangle within the sphere
void sub_461900(EEContext& ctx);  // 0x461900 [collGeometryLineAllTriangles] -- a line against every triangle of a one-morph-target geometry (no collision tree)
void sub_461D00(EEContext& ctx);  // 0x461D00 [collGeometrySphereAllTriangles] -- a sphere against every triangle of a one-morph-target geometry (no collision tree)
void sub_461EA0(EEContext& ctx);  // 0x461EA0 [collGeometryLineIntersections] -- a line against a one-morph-target geometry: its collision tree, or every triangle
void sub_462BB0(EEContext& ctx);  // 0x462BB0 [collGeometrySphereIntersections] -- a sphere against a one-morph-target geometry: its collision tree, or every triangle
void sub_463490(EEContext& ctx);  // 0x463490 [collMorphLineIntersections] -- a line against a geometry blended between two morph targets (the atomic's interpolator)
void sub_463B20(EEContext& ctx);  // 0x463B20 [collMorphSphereIntersections] -- a sphere against a geometry blended between two morph targets (the atomic's interpolator)
void sub_463F20(EEContext& ctx);  // 0x463F20 [collAtomicSphereIntersections] -- an atomic's sphere test: the sphere into the atomic's space, then its geometry's test
void sub_4A38F0(EEContext& ctx);  // 0x4A38F0 [ps2AllMatSetTriListBatch] -- the PS2AllMat node's tri-list batch: kind 3
void sub_4A3A80(EEContext& ctx);  // 0x4A3A80 [ps2AllMatSetTriStripBatch] -- the PS2AllMat node's tri-strip batch: kind 12
void sub_4A3C10(EEContext& ctx);  // 0x4A3C10 [ps2AllMatSetPointBatch] -- the PS2AllMat node's point / line batch: kind 16
void sub_4A3D70(EEContext& ctx);  // 0x4A3D70 [ps2AllMatSetVifOffset] -- stores $a1 in the PS2AllMat node's private data (+20); the node, or 0 without node / data
void RxPipelineNodePS2AllMatSetVU1CodeArray(EEContext& ctx);  // 0x4A3DB0 -- the node's VU1 code array and length (0: the default 0x77F130, 32 entries)
void sub_4A3E30(EEContext& ctx);  // 0x4A3E30 [ps2AllMatSetCallBack] -- sets one of the PS2AllMat node's five callbacks ($a1 = 1..5; types 2..4 refuse 0)
void sceLibgcc32GetErxEntries_0(EEContext& ctx);  // 0x4A3F10 -- returns the address 0x77E1E0 (the PS2AllMat node definition the pipe builders lock)
void sub_4A4D50(EEContext& ctx);  // 0x4A4D50 [pipeIdConstructor] -- the PS2 pipeline-id extension constructor: clears the word at object + offset; the object
void sub_4A4DA0(EEContext& ctx);  // 0x4A4DA0 [geometryPipeIdAlways] -- the geometry's PS2 pipeline-id stream-always callback
void sub_4A4E40(EEContext& ctx);  // 0x4A4E40 [atomicPipeIdAlways] -- the atomic's PS2 pipeline-id stream-always callback (through its geometry)
void sub_4A4EF0(EEContext& ctx);  // 0x4A4EF0 [sectorPipeIdAlways] -- the world sector's PS2 pipeline-id stream-always callback (its record at +120)
void sub_4A4F90(EEContext& ctx);  // 0x4A4F90 [atomicPipeIdRights] -- the atomic's rights callback: 1 when its geometry's / its own pipeline can be found
void sub_4A5080(EEContext& ctx);  // 0x4A5080 [sectorPipeIdRights] -- the world sector's rights callback: 1 when its pipeline can be found (1 without a record)
void sub_4A5100(EEContext& ctx);  // 0x4A5100 [pipeIdPluginAttach] -- registers the 4-byte PS2 pipeline-id extension (plugin 0x50F) on geometries, atomics, world sectors
void sub_4A5200(EEContext& ctx);  // 0x4A5200 [pdsMaterialPipeReset] -- restores the default material pipeline (sub_49C620(0))
void sub_4A5210(EEContext& ctx);  // 0x4A5210 [pdsMaterialPipeOpen] -- the default material pipeline: RpPDSGetPipe(0x1001), made the default (sub_49C620)
void sub_4A5290(EEContext& ctx);  // 0x4A5290 [pdsSectorPipeReset] -- restores the default world-sector pipeline (sub_49C560(0))
void sub_4A52A0(EEContext& ctx);  // 0x4A52A0 [pdsSectorPipeOpen] -- the default world-sector pipeline: RpPDSGetPipe(0x1003), made the default (sub_49C560)
void sub_4A5320(EEContext& ctx);  // 0x4A5320 [pdsAtomicPipeReset] -- restores the default atomic pipeline (sub_49C5C0(0))
void sub_4A5330(EEContext& ctx);  // 0x4A5330 [pdsAtomicPipeOpen] -- the default atomic pipeline: RpPDSGetPipe(0x1002), made the default (sub_49C5C0)
void sub_4A53B0(EEContext& ctx);  // 0x4A53B0 [rt2dBrushClose] -- destroys the brush free list (sub_4C3C30) and frees the 9,216-byte buffer
void sub_4A5400(EEContext& ctx);  // 0x4A5400 [rt2dBrushOpen] -- allocates the 9,216-byte buffer and creates the 120-byte brush free list (static block 0x95E7D0)
void sub_4A5540(EEContext& ctx);  // 0x4A5540 [rt2dBrushRelease] -- drops a brush reference (+116); at 0 its texture (+104, sub_4D0F00) and the record are freed
void sub_4AA540(EEContext& ctx);  // 0x4AA540 [rt2dGetWord84] -- returns the toolkit word at 0x95EF84
void sub_4AA620(EEContext& ctx);  // 0x4AA620 [rt2dCTMClose] -- destroys the 32 CTM stack matrices (sub_4C3880), resets the top, frees the scratch block
void sub_4AA6C0(EEContext& ctx);  // 0x4AA6C0 [rt2dCTMOpen] -- the CTM stack at open: an identity matrix on top, the toolkit defaults, the 0..255 index table
void sub_4AADA0(EEContext& ctx);  // 0x4AADA0 [Rt2dCTMScale] -- scales the current transformation by ($f12, $f13, 1) (RwMatrixScale, post-concatenated); 1
void sub_4AAE00(EEContext& ctx);  // 0x4AAE00 [Rt2dCTMTranslate] -- translates the current transformation by ($f12, $f13, 0) (RwMatrixTranslate); 1
void sub_4AB170(EEContext& ctx);  // 0x4AB170 [rt2dPathReset] -- empties a path's segment sList and marks it flat (+12 = 1, +8 = 0)
void sub_4AB1B0(EEContext& ctx);  // 0x4AB1B0 [Rt2dPathEmpty] -- empties a path: its sub-paths destroyed (sub_4AC390), its segments emptied, itself current
void sub_4AB2C0(EEContext& ctx);  // 0x4AB2C0 [Rt2dPathLineto] -- appends a line segment to ($f12, $f13): its unit normal, the running length, the mitre
void sub_4AB410(EEContext& ctx);  // 0x4AB410 [Rt2dPathCurveto] -- appends a cubic curve: three type-2 control points ($f12..$f17), each with normal and length
void sub_4AC120(EEContext& ctx);  // 0x4AC120 [rt2dPathGetBBox] -- the bounding box of a path and its sub-paths: {x, y, width, height} in $a1
void sub_4AC7F0(EEContext& ctx);  // 0x4AC7F0 [rt2dPathClose3] -- destroys the scratch path's three-deep chain (sub_4AB0E0 / sub_4AC390) and its free list
void sub_4AC860(EEContext& ctx);  // 0x4AC860 [rt2dSetFreeListParams] -- stores the toolkit's free-list block parameters (0x7CDCC4 / 0x7CDCC8)
void sub_4ACCC0(EEContext& ctx);  // 0x4ACCC0 [rt2dPathPointInside] -- even-odd point-in-path test of a flattened path: 1 when ($a0) lies inside
void sub_4ACE60(EEContext& ctx);  // 0x4ACE60 [rt2dPathPointInsideThunk] -- the point-in-path test (a tail call to sub_4ACCC0)
void sub_4AD6A0(EEContext& ctx);  // 0x4AD6A0 [rt2dShapeNodeDestroy] -- frees a shape node's path (+176, RwFree) and releases its brush (+180); the brush's result
void sub_4ADB50(EEContext& ctx);  // 0x4ADB50 [rt2dShapeNodeClose] -- destroys the 272-byte shape-node free list
void sub_4ADB80(EEContext& ctx);  // 0x4ADB80 [rt2dShapeNodeOpen] -- creates the 272-byte shape-node free list (static block 0x95F9C0); 1
void sub_4ADC70(EEContext& ctx);  // 0x4ADC70 [rt2dShapeNodeFree] -- returns a shape node to its free list
void sub_4ADCA0(EEContext& ctx);  // 0x4ADCA0 [rt2dShapeNodeAlloc] -- takes a shape node from its free list (0x30193)
void sub_4ADDB0(EEContext& ctx);  // 0x4ADDB0 [rt2dObjectStreamReadHeader] -- reads an object's 44-byte header: id, flags, colour block, then the child chunk
void sub_4ADFD0(EEContext& ctx);  // 0x4ADFD0 [rt2dObjectSetVisible] -- sets (1) or clears bit 2 of an object's flags (+8); the object
void sub_4AE010(EEContext& ctx);  // 0x4AE010 [rt2dObjectIsVisible] -- bit 2 of an object's flags
void sub_4AE020(EEContext& ctx);  // 0x4AE020 [rt2dObjectSetColourMult] -- copies 64 bytes into object +16 and sets flag bit 1; the object
void sub_4AE1D0(EEContext& ctx);  // 0x4AE1D0 [rt2dObjectSetId] -- object +4 = $a1; the object
void sub_4AE1E0(EEContext& ctx);  // 0x4AE1E0 [rt2dShapeGetPath] -- destroys a shape's path (sub_4AC390 on +176) -- the tail of the shape destroy
void sub_4AE1F0(EEContext& ctx);  // 0x4AE1F0 [rt2dShapePickPoint] -- a visible shape's point test: the point through the shape's matrix (+208), then the path test
void sub_4AE8F0(EEContext& ctx);  // 0x4AE8F0 [rt2dSceneGetChildCount] -- a scene's child count (+180)
void sub_4AE900(EEContext& ctx);  // 0x4AE900 [rt2dSceneGetChild] -- a scene's child $a1: the sList entry (sub_4C21B0 on +176), dereferenced when flag bit 0 is set
void sub_4AEB60(EEContext& ctx);  // 0x4AEB60 [rt2dSceneForAllChildren] -- calls $a1(child, scene, $a2) on each 272-byte child of a scene; the scene
void sub_4AEF50(EEContext& ctx);  // 0x4AEF50 [rt2dSceneSetDirty] -- scene +188 = 1; the scene
void sub_4B0360(EEContext& ctx);  // 0x4B0360 [rt2dPolygonDestroy] -- frees a polygon: its vertex ring (8-byte records back to their free list), its point array, itself
void sub_4B0430(EEContext& ctx);  // 0x4B0430 [rt2dPolygonCornerSide] -- the side of a polygon corner: 1 left, 2 right, 4 collinear (the cross product's sign)
void sub_4B0560(EEContext& ctx);  // 0x4B0560 [rt2dPolygonPointInTriangle] -- classifies a vertex against a triangle of three others: 8 inside, 4 on an edge, 16 outside
void sub_4B08C0(EEContext& ctx);  // 0x4B08C0 [rt2dPolygonSplit] -- splits a polygon's vertex ring between two vertices into two polygons (the diagonal duplicated)
void sub_4B0DF0(EEContext& ctx);  // 0x4B0DF0 [rt2dPolygonCreate] -- a polygon from a flattened path: its points copied (8 bytes each) and a ring of vertex records
void sub_4B1050(EEContext& ctx);  // 0x4B1050 [rt2dPolygonClose] -- destroys the two polygon free lists
void sub_4B1090(EEContext& ctx);  // 0x4B1090 [rt2dPolygonOpen] -- creates the 8-byte vertex and 20-byte polygon free lists (static blocks); 1
void rt2dPS2PipeOpen(EEContext& ctx);  // 0x4B1100 -- the toolkit's 2-D pipelines: RpPDSGetPipe(0x1001A) font, (0x1001E) stroke, (0x1001C) fill, two slots each; 1
void sub_4B11A0(EEContext& ctx);  // 0x4B11A0 [rt2dPS2PipeClose] -- clears the eight 2-D pipeline slots
void sub_4B11F0(EEContext& ctx);  // 0x4B11F0 [rt2dListDestroyCB] -- a list-walk callback: destroys one record (sub_4B1C80) and folds the success into *$a3
void sub_4B1240(EEContext& ctx);  // 0x4B1240 [rt2dListDestroy] -- destroys every record of a list (sub_4B1990 with sub_4B11F0), then the sList; the list
void sub_4B1990(EEContext& ctx);  // 0x4B1990 [rt2dListForAll] -- calls $a1(list, $a2, record, $a3) on each record of a list's 8-byte sList entries; the list
void sub_4B1A30(EEContext& ctx);  // 0x4B1A30 [rt2dListGetCount] -- the entry count of a list's sList
void sub_4B1A40(EEContext& ctx);  // 0x4B1A40 [rt2dListGetRecord] -- the record of entry $a1 (its second word)
void sub_4B1A80(EEContext& ctx);  // 0x4B1A80 [rt2dListGetCursorIndex] -- the index of the list's cursor (+16) in its sList, or -1 without a cursor
void sub_4B1AE0(EEContext& ctx);  // 0x4B1AE0 [rt2dListGetCursorTime] -- the float at the cursor (+16), or 0
void sub_4B1B00(EEContext& ctx);  // 0x4B1B00 [rt2dListGetNextIndex] -- the index of the next pointer (+20) in the sList, or the count without one
void sub_4B1B60(EEContext& ctx);  // 0x4B1B60 [rt2dListGetNextTime] -- the float at the next pointer (+20), else at the end pointer (+24)
void sub_4B1B90(EEContext& ctx);  // 0x4B1B90 [rt2dListIsLooping] -- bit 1 of the list's flags (+12)
void sub_4B1C80(EEContext& ctx);  // 0x4B1C80 [rt2dRecordDestroy] -- destroys a 12-byte record: its data (an sList when +4, else RwFree) and the record; 1 for a record
void sub_4B2A90(EEContext& ctx);  // 0x4B2A90 [rt2dListAppendCB] -- a walk callback: appends $a0 to the sList $a2 (sub_4C1E70); returns $a0
void sub_4B2B40(EEContext& ctx);  // 0x4B2B40 [rt2dPropsEmpty] -- destroys the two sLists of a property set (+4, +12) and clears it; the set
void sub_4B2BA0(EEContext& ctx);  // 0x4B2BA0 [rt2dGetEntry0] -- the first word of sList entry $a1 of +4
void sub_4B2BD0(EEContext& ctx);  // 0x4B2BD0 [rt2dSListDestroy1] -- destroys an sList (sub_4C20B0); 1
void j__rwSListGetEntry(EEContext& ctx);  // 0x4B2C70 -- the sList entry getter (a tail call to sub_4C21B0)
void sub_4B2E70(EEContext& ctx);  // 0x4B2E70 [rt2dMessageListDestroy] -- resets every 16-byte record of the message sList (+12) and destroys it; the owner
void sub_4B3030(EEContext& ctx);  // 0x4B3030 [rt2dMessageGet] -- the 16-byte record $a1 of the message sList (+12), or 0 out of range
void sub_4B30A0(EEContext& ctx);  // 0x4B30A0 [rt2dStateInitA] -- a state record: -1, -1, 0, 0, then 32 words of -1
void sub_4B3100(EEContext& ctx);  // 0x4B3100 [rt2dStateInitB] -- a state record: -1, -1, 0, 0, then 32 words of -1 (a copy of sub_4B30A0)
void sub_4B3490(EEContext& ctx);  // 0x4B3490 [rt2dLabelsDestroy] -- destroys the label sList (+16) when there is one; the owner
void sub_4B34D0(EEContext& ctx);  // 0x4B34D0 [rt2dLabelGet] -- the label entry $a1 (sub_4C21B0 on +16)
void sub_4B34E0(EEContext& ctx);  // 0x4B34E0 [rt2dButtonTableInit] -- fills a 64-word button transition table with its constants; returns the end (+480)
void sub_4B3610(EEContext& ctx);  // 0x4B3610 [rt2dButtonSetState] -- a button's state: the sub-objects by the flags (+8 bits 0..3) made visible or hidden
void sub_4B3700(EEContext& ctx);  // 0x4B3700 [rt2dNullCallBack] -- a default callback: returns 0
void sub_4B3720(EEContext& ctx);  // 0x4B3720 [rt2dPassCallBack] -- a default callback: returns its second argument
void sub_4B3790(EEContext& ctx);  // 0x4B3790 [rt2dFrameListsDestroy] -- destroys the maestro's index sList (+24) and resets / destroys its 16-byte frame sList (+20)
void sub_4B39F0(EEContext& ctx);  // 0x4B39F0 [rt2dMaestroQueueActions] -- queues the actions of frame $a1: the run of non-zero entries from its index (sub_4B3F50)
void sub_4B3DE0(EEContext& ctx);  // 0x4B3DE0 [rt2dMaestroResolveTarget] -- an action's target frame: relative / absolute / via a nested scene's offset (sub_4B4A60)
void sub_4B3F50(EEContext& ctx);  // 0x4B3F50 [rt2dMaestroPushActions] -- copies $a3 16-byte actions into the queue ($a1), resolving jumps (type 12) and targets
void sub_4B4090(EEContext& ctx);  // 0x4B4090 [rt2dQueuePop] -- the next 16-byte entry of a queue, or 0; an exhausted queue is reset
void sub_4B40F0(EEContext& ctx);  // 0x4B40F0 [rt2dQueueCreate] -- a queue record (16-byte free list) with an entry array of the configured size; stored at +32
void sub_4B41B0(EEContext& ctx);  // 0x4B41B0 [rt2dQueueDestroy] -- frees the owner's queue (+32): its array and the record; the owner
void sub_4B4720(EEContext& ctx);  // 0x4B4720 [rt2dAnimDestroyCB] -- a maestro walk callback: destroys an animation entry's lists and resets it; returns $a0
void sub_4B4810(EEContext& ctx);  // 0x4B4810 [rt2dMaestroAnimsDestroy] -- destroys every animation of the maestro (sub_4B4BA0 with sub_4B4720) and their sList
void sub_4B4A60(EEContext& ctx);  // 0x4B4A60 [rt2dMaestroGetAnim] -- the animation entry $a1 (sub_4C21B0 on +8)
void sub_4B4A70(EEContext& ctx);  // 0x4B4A70 [rt2dMaestroForAllVisibleAnims] -- calls $a1 on each 60-byte animation whose scene is visible (marking bit 2)
void sub_4B4BA0(EEContext& ctx);  // 0x4B4BA0 [rt2dMaestroForAllAnims] -- calls $a1(maestro, anim, $a2) on each 60-byte animation; 0 when one does not return the maestro
void sub_4B59B0(EEContext& ctx);  // 0x4B59B0 [rt2dMaestroTriggerButton] -- a button message: finds the button in the animation's props and queues its transition
void sub_4B6000(EEContext& ctx);  // 0x4B6000 [rt2dPropsGet] -- the 16-byte prop record $a1 of a props set, or 0 without an sList
void sub_4B6190(EEContext& ctx);  // 0x4B6190 [rt2dPropsDestroy] -- destroys a props set: each record's sList, the array, then the record (8-byte free list); 1
void sub_4B6270(EEContext& ctx);  // 0x4B6270 [rt2dClearFlag0] -- clears bit 0 of +4; the record
void sub_4B62A0(EEContext& ctx);  // 0x4B62A0 [rt2dPropsLookup] -- prop $a3 of record $a2 in props $a1, through the label table (+16): its value to *$t0
void sub_4B6350(EEContext& ctx);  // 0x4B6350 [rt2dAnimOpen] -- creates the animation / maestro free lists (11 static free lists) and sets the open flag
void sub_4B6500(EEContext& ctx);  // 0x4B6500 [rt2dAnimClose] -- destroys the animation / maestro free lists
void sub_4BAE00(EEContext& ctx);  // 0x4BAE00 [sphereTriangleTest] -- sphere / triangle: 1 when any point of the triangle lies within the sphere; the normal and distance
void sub_4BB5D0(EEContext& ctx);  // 0x4BB5D0 [boxTriangleTest] -- box / triangle overlap: 1 when the triangle and the box intersect (separating axes)
void sub_4BF6E0(EEContext& ctx);  // 0x4BF6E0 [rtfsFileSystemInit] -- initialises a file system: its name, its files, its device name; 1 or an error code
void sub_4BF7E0(EEContext& ctx);  // 0x4BF7E0 [rtfsSkipDevicePrefix] -- a path after its 'device:' prefix (the first ':' + 1), or the path itself
void sub_4BF9E0(EEContext& ctx);  // 0x4BF9E0 [rtfsFileEof] -- a file's end-of-file test: position -1 or position >= length
void sub_4BFA10(EEContext& ctx);  // 0x4BFA10 [rtfsNotify] -- calls the file system's register (1) or unregister (2) callback with its name
void sub_4BFA70(EEContext& ctx);  // 0x4BFA70 [rtfsSetDevice] -- a file system's device name: 7 when the device is taken (sub_4C0070), else a heap copy; 1
void sub_4BFB20(EEContext& ctx);  // 0x4BFB20 [rtfsFileComplete] -- ends a file operation: idle again, and the completion callback with the result or position
void sub_4BFC20(EEContext& ctx);  // 0x4BFC20 [rtfsHasRoom] -- 1 when another file system can be registered; else the error callback (5) and 0
void sub_4BFC80(EEContext& ctx);  // 0x4BFC80 [RtFSManagerRegister] -- registers a file system: room and a free name required; its register callback; pushed on the list
void sub_4BFD50(EEContext& ctx);  // 0x4BFD50 [RtFSManagerGetFileSystemFromName] -- the registered file system with that name (strcmp), else the error callback (6) and 0
void sub_4BFDE0(EEContext& ctx);  // 0x4BFDE0 [rtfsNameTaken] -- 1 (and the error callback 7) when a file system of that name is registered
void sceLibgcc32GetErxEntries_1(EEContext& ctx);  // 0x4C0060 -- returns the address of the RtFS list (0x95FF10)
void sub_4C0070(EEContext& ctx);  // 0x4C0070 [rtfsFindDevice] -- the registered file system whose device name matches (case-insensitive), or 0
void sub_4C0230(EEContext& ctx);  // 0x4C0230 [rtfsSetCallBack] -- stores the manager's callback word (gp 0x7CE8BC)
void sub_4C03D0(EEContext& ctx);  // 0x4C03D0 [rtfsFread] -- fread through RtFS: the file system's read (fs +48) of size x count bytes, / size
void sub_4C0420(EEContext& ctx);  // 0x4C0420 [rtfsFwrite] -- fwrite through RtFS: the file system's write (fs +52) of size x count bytes, / size
void sub_4C0470(EEContext& ctx);  // 0x4C0470 [rtfsFseek] -- fseek through RtFS: whence 0 / 1 / 2 -> the seek operation (fs +56) with mode 1 / 2 / 3; 0, or -1
void sub_4C06B0(EEContext& ctx);  // 0x4C06B0 [rtfsFeof] -- feof through RtFS: the file system's end-of-file operation (fs +68)
void sub_4C0830(EEContext& ctx);  // 0x4C0830 [rtfsGenericGetFile] -- the generic file system's file $a1 (112-byte records at +88), or 0 out of range
void sub_4C0870(EEContext& ctx);  // 0x4C0870 [rtfsGenericGetDevice] -- the generic file system's device name ('host:')
void sub_4C0880(EEContext& ctx);  // 0x4C0880 [rtfsGenericClose] -- frees the generic file system's file array (+88)
void sub_4C0F60(EEContext& ctx);  // 0x4C0F60 [rtfsGenericSync] -- file status = 1; returns 1
void sub_4C0FD0(EEContext& ctx);  // 0x4C0FD0 [rtfsGenericCreate] -- creates a generic ('host:') file system: 92-byte record, its operations, $a0 files with buffers
void sub_4C1BC0(EEContext& ctx);  // 0x4C1BC0 [moduleOpenCount] -- counts a module open (gp 0x7CE8CC); returns $a0
void sub_4C1BE0(EEContext& ctx);  // 0x4C1BE0 [moduleCloseCount] -- counts the module's close; returns $a0
void sub_4C1C00(EEContext& ctx);  // 0x4C1C00 [errorModuleOpen] -- the error module's open: its offset, the error cleared {0, 0x80000000}, counted; returns $a0
void sub_4C1C30(EEContext& ctx);  // 0x4C1C30 [errorModuleClose] -- the error module's close: counts down; returns $a0
void sub_4C1CD0(EEContext& ctx);  // 0x4C1CD0 [RwErrorGet] -- copies the last error {plugin, code} to $a0 and clears it to {0, 0x80000000}; returns $a0
void sub_4C1F70(EEContext& ctx);  // 0x4C1F70 [slistGetNewEntries] -- reserves n entries at an sList's end: grows it by n + a quarter when full (RwRealloc)
void sub_4C2080(EEContext& ctx);  // 0x4C2080 [slistDropEntries] -- count -= n
void sub_4C20B0(EEContext& ctx);  // 0x4C20B0 [slistDestroy] -- frees an sList's data (when it has data and a capacity) and the sList; 1
void sub_4C2130(EEContext& ctx);  // 0x4C2130 [slistToArray] -- frees the sList record and returns its data (0, data freed too, when the count is 0)
void name__C9type_info_1(EEContext& ctx);  // 0x4C21D0 -- an sList's data (its first word)
void sub_4C21E0(EEContext& ctx);  // 0x4C21E0 [slistGetEnd] -- an sList's end: data + entry size x count
void sub_4CA380(EEContext& ctx);  // 0x4CA380 [rwMallocSizeOf] -- RwMalloc(*$a0) (a tail call): a memory callback
void sub_4CA3A0(EEContext& ctx);  // 0x4CA3A0 [rwFreeArg1] -- RwFree($a1); returns $a0: a memory callback
void _rwDeviceSystemRequest(EEContext& ctx);  // 0x4CA3E0 -- a request to the device's system function, with the standard answers when it declines
void sub_4CA510(EEContext& ctx);  // 0x4CA510 [RwEngineGetVersion] -- returns the library version 0x37002
void sub_4CA520(EEContext& ctx);  // 0x4CA520 [RwEngineRegisterPlugin] -- registers an engine plugin (sub_4C61B0 on the engine registry 0x77E630, no copy callback)
void sub_4CA550(EEContext& ctx);  // 0x4CA550 [RwEngineGetPluginOffset] -- the offset of an engine plugin's data, -1 when it is not registered
void sub_4CA560(EEContext& ctx);  // 0x4CA560 [RwEngineGetVideoModeInfo] -- the device's mode info for mode $a1 into $a0 (request 6); $a0, or 0
void sub_4CA5B0(EEContext& ctx);  // 0x4CA5B0 [RwEngineGetCurrentVideoMode] -- the device's current video mode (request 10), or -1
void RwEngineSetVideoMode(EEContext& ctx);  // 0x4CA600 -- selects video mode $a0 (request 7); 1 or 0
void sub_4F3EC0(EEContext& ctx);  // 0x4F3EC0 [RxPipelineNodeCreateInitData] -- a pipeline node's initialisation data: the old block freed, a new one of $a1 bytes
void sub_4F3F70(EEContext& ctx);  // 0x4F3F70 [RxPipelineNodeGetInitData] -- a pipeline node's initialisation data (node +32)

}  // namespace p3fes::game
