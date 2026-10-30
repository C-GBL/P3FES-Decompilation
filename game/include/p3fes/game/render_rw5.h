// Slice render_rw5: RenderWare, fifth pass -- the device-independent scene logic a D3D11 renderer keeps when it
// replaces the PS2 pipelines (docs/ANALYSIS/22_rendering.md): 159 functions of the RW band 0x45EC00-0x4FB100,
// started from p3fes_handgen and made readable (game/src/render/render_rw5.cpp).
//
// Groups (sub_* keep their symbols/functions.json names; proposed names in brackets, symbols/deltas/render_rw5.sym):
//   * RwCamera (0x4C89A0-0x4CA090, 0x4C7A50, 0x4D18C0, 0x4F28E0): create, the module open / close,
//     the setters (view window, view offset, far clip, projection) and the z scale / shift they refresh, the
//     camera sync callback that rebuilds the view matrix (perspective / parallel), the frustum planes and corners and
//     the frustum's bounding box; CameraBeginUpdate / CameraEndUpdate (the object callbacks behind
//     RwCameraBeginUpdate / RwCameraEndUpdate); the object-off-its-frame release every framed object uses.
//   * RpLight (0x494490-0x494930): create / destroy, the colour setter (with its 'grey' flag), the module open /
//     close.
//   * RpMaterial (0x4949C0-0x494E10): create, the module open / close, the material-pipeline stream extension, the
//     material registry's plugin helpers.
//   * RpWorld's object ties (0x49AAF0-0x49C790): the world module open / close (the two free lists of 24-byte sector
//     ties), the camera / atomic / clump / light world extensions (constructor / copy / destructor), the camera's
//     begin / end / sync wrappers that make the world current and build the camera's visible-sector list (the frustum
//     walk of the BSP), the atomic and light syncs that tie an object to the sectors its bounds touch, add / remove a
//     camera, an atomic, a clump, a light to / from a world, the default pipelines of the three object kinds.
//   * World sectors (0x4991F0-0x49A950): the sector registry helpers, the BSP walks that compute the sectors' bounding
//     boxes (their BSP cells), free the sectors' meshes and build them (the distinct textures / rasters / pipelines of
//     a sector's triangles), the world module's pending-pair list, the world's for-all-materials.
//   * RpClump / RpAtomic (0x490690-0x492060): the clump / atomic module open / close, the clump's camera and light
//     lists (the tie extensions, for-all, add / remove), clump create, add atomic, the atomic-pipeline stream extension.
//   * RpGeometry and the mesh build (0x492C30-0x495C80): the atomic / clump / geometry plugin registration helpers, the
//     morph targets (add, bounding sphere), triangles (vertex indices, material), the material list (init, find,
//     append), geometry references, the mesh module open / close and the build-mesh records.
//   * RpCollision (0x45EC40-0x45F7D0, 0x464280): the collision data of world sectors and geometries -- create / size /
//     stream read / write of the collision tree, the plugin's constructor / destructor / copy / stream callbacks and
//     its registration (plugin id 0x11D), the triangle-map array.
//   * RwV3d / RwV2d (0x4C69F0-0x4C6CE0): normalize, length (3-D and 2-D), the transform-points / -vectors entry points
//     through the vector module; the bounding box of n points (sub_4C7A50, the camera's frustum box).
//   * RwImage (0x4CBC70-0x4CD750): create / destroy, free pixels, the module close, the image stream reader.
//   * Im3D (0x4F23C0, 0x4F2430): the Im3D pipeline setters (the transform pipeline; the render pipeline per primitive type).
//
// RW globals: the engine instance 0x960070 (+0 the current camera, +4 the current world, +8 / +10 the u16 render / light frame stamps,
// +16.. the device functions); each module's data lives at 0x960070 + its offset (a gp word written by the module's
// open); each plugin extension lives at object + its offset (a gp word written by the plugin registration).
// render_rw4.h has the frame / matrix / free-list / plugin-registry / texture / raster layouts (rw4::).
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/render_rw4.h"  // rw4:: the frame / object / plugin-registry / free-list / texture layouts

namespace p3fes::game {

namespace rw5 {

// --- module / plugin offset words (gp-relative globals written at registration; the value is an offset) --------------
namespace gpoff {
constexpr u32 kCollModule = 0x7CE720;         // the collision plugin's engine-module offset (0x7CE71C: its open count)
constexpr u32 kCollAtomic = 0x7CE724;         // its atomic extension offset
constexpr u32 kCollGeometry = 0x7CE728;       // its geometry extension offset
constexpr u32 kCollSector = 0x7CE72C;         // its world-sector extension offset
constexpr u32 kCamClumpTie = 0x7CE810;        // camera extension: the tie into a clump's camera list (12 bytes)
constexpr u32 kLightClumpTie = 0x7CE814;      // light extension: the tie into a clump's light list (12 bytes)
constexpr u32 kAtomicModule = 0x7CE820;       // the clump / atomic module (+0 atomic free list, +4 clump free list)
constexpr u32 kLightModule = 0x7CE830;        // the light module (+0 light free list)
constexpr u32 kMaterialModule = 0x7CE840;     // the material module (+0 material free list)
constexpr u32 kMeshFreeList = 0x7CE848;       // the build-mesh free list (12-byte records)
constexpr u32 kCamWorldExt = 0x7CE868;        // camera extension: its world and visible-sector list
constexpr u32 kAtomicWorldExt = 0x7CE86C;     // atomic extension: its world and saved sync callback
constexpr u32 kClumpWorldExt = 0x7CE870;      // clump extension: its world
constexpr u32 kLightWorldExt = 0x7CE874;      // light extension: its world and saved sync callback
constexpr u32 kWorldModule = 0x7CE878;        // the world module (+0 atomic-sector tie free list, +4 light-sector ties)
constexpr u32 kV3dModule = 0x7CE910;          // the vector module (+12 transform points, +20 transform vectors)
constexpr u32 kCameraModule = 0x7CE920;       // the camera module (+0 camera free list)
constexpr u32 kImageModule = 0x7CE938;        // the image module (+0 image free list, +4 / +528 scratch buffers)
constexpr u32 kIm3dModule = 0x7CEB20;         // the Im3D module (pipelines per primitive kind)
constexpr u32 kPipeModule = 0x7CEB28;         // the default object pipelines
}  // namespace gpoff

// --- registries (rw4::plugreg layout) ---------------------------------------------------------------------------------
namespace reg {
constexpr u32 kAtomic = 0x77DCE0;
constexpr u32 kClump = 0x77DD00;
constexpr u32 kGeometry = 0x77DD20;
constexpr u32 kLight = 0x77DD40;
constexpr u32 kMaterial = 0x77DD60;
constexpr u32 kWorldSector = 0x77DDB0;
constexpr u32 kWorld = 0x77DDD0;
constexpr u32 kCamera = 0x77E5E0;
constexpr u32 kImage = 0x77E690;
}  // namespace reg

namespace camera {                            // RwCamera (the camera free list's records)
constexpr s32 kFrame = 4;                     // the object's frame (RwObjectHasFrame)
constexpr s32 kFrameLinkNext = 8;             //   the link in the frame's object list (next, prev)
constexpr s32 kFrameLinkPrev = 12;
constexpr s32 kSync = 16;                     // the object sync callback (sub_4C9AD0)
constexpr s32 kProjection = 20;               // 1 perspective, 2 parallel
constexpr s32 kBeginUpdate = 24;              // CameraBeginUpdate (or the world wrapper sub_49AC90)
constexpr s32 kEndUpdate = 28;                // CameraEndUpdate (or sub_49ACD0)
constexpr s32 kViewMatrix = 32;               // RwMatrix: the view matrix (rebuilt by the sync); element [row][col]:
constexpr s32 kView00 = 32;                   //   row 0: column 0 = the scaled right axis's x, ...
constexpr s32 kView01 = 36;
constexpr s32 kView02 = 40;
constexpr s32 kViewMatrixFlags = 44;          //   its flags word
constexpr s32 kView10 = 48;
constexpr s32 kView11 = 52;
constexpr s32 kView12 = 56;
constexpr s32 kView20 = 64;
constexpr s32 kView21 = 68;
constexpr s32 kView22 = 72;
constexpr s32 kView30 = 80;                   //   row 3: the translation
constexpr s32 kView31 = 84;
constexpr s32 kView32 = 88;
constexpr s32 kFrameBuffer = 96;              // the frame-buffer raster
constexpr s32 kZBuffer = 100;                 // the z-buffer raster
constexpr s32 kViewWindowX = 104;             // f32 the view window (half extents at distance 1)
constexpr s32 kViewWindowY = 108;
constexpr s32 kRecipViewWindowX = 112;        // f32 1 / the view window
constexpr s32 kRecipViewWindowY = 116;
constexpr s32 kViewOffsetX = 120;             // f32 the view offset
constexpr s32 kViewOffsetY = 124;
constexpr s32 kNearPlane = 128;               // f32 near clip (0.05 at create)
constexpr s32 kFarPlane = 132;                // f32 far clip (10 at create)
constexpr s32 kFogPlane = 136;                // f32 (5 at create)
constexpr s32 kZScale = 140;                  // f32 the device z scale (sub_4C89A0)
constexpr s32 kZShift = 144;                  // f32 the device z shift
constexpr s32 kFrustumPlanes = 148;           // 6 planes x 20 bytes (frustplane below): far, near, left, top, right, bottom
constexpr s32 kFrustumBoxSup = 268;           // the frustum corners' bounding box: maximum x, y, z
constexpr s32 kFrustumBoxInf = 280;           //   minimum x, y, z
constexpr s32 kFrustumCorners = 292;          // 8 corners x 12 bytes (near 4, then far 4)
}  // namespace camera

namespace frameltm {                          // a frame's local-to-world matrix, as offsets from the frame (rw4::rwframe::kLtm)
constexpr s32 kRightX = 80;
constexpr s32 kRightY = 84;
constexpr s32 kRightZ = 88;
constexpr s32 kUpX = 96;
constexpr s32 kUpY = 100;
constexpr s32 kUpZ = 104;
constexpr s32 kAtX = 112;
constexpr s32 kAtY = 116;
constexpr s32 kAtZ = 120;
constexpr s32 kPosX = 128;
constexpr s32 kPosY = 132;
constexpr s32 kPosZ = 136;
}  // namespace frameltm

namespace mtx {                               // an RwMatrix's position (rw4::rwmatrix::kPos)
constexpr s32 kPosX = 48;
constexpr s32 kPosY = 52;
constexpr s32 kPosZ = 56;
}  // namespace mtx

namespace objframe {                          // RwObjectHasFrame: an object hung on a frame (camera, light, atomic)
constexpr s32 kFrame = 4;
constexpr s32 kLinkNext = 8;                  // the link in the frame's object list (rw4::rwframe::kObjects)
constexpr s32 kLinkPrev = 12;
}  // namespace objframe

namespace bbox {                              // RwBBox
constexpr s32 kSupX = 0;                      // the maximum
constexpr s32 kSupY = 4;
constexpr s32 kSupZ = 8;
constexpr s32 kInfX = 12;                     // the minimum
constexpr s32 kInfY = 16;
constexpr s32 kInfZ = 20;
}  // namespace bbox

namespace frustplane {                        // one frustum plane (20 bytes)
constexpr s32 kNormal = 0;                    // f32 x 3
constexpr s32 kDistance = 12;                 // f32 normal . a point on the plane
constexpr s32 kClosestX = 16;                 // u8: 1 + (normal.x < 0) -- which box corner is closest (0 / 1 / 2 coded)
constexpr s32 kClosestY = 17;
constexpr s32 kClosestZ = 18;
constexpr s32 kSize = 20;
}  // namespace frustplane

namespace light {                             // RpLight
constexpr s32 kType = 1;                      // u8 RwObject subtype = the light type (bit 7: a local light, tied to sectors)
constexpr s32 kFlags = 2;                     // u8 (3 = light atomics | light world at create)
constexpr s32 kPrivateFlags = 3;              // u8: 1 when the colour is grey (r == g == b)
constexpr s32 kFrame = 4;
constexpr s32 kSync = 16;                     // the object sync callback (sub_4944A0: none)
constexpr s32 kRadius = 20;                   // f32
constexpr s32 kColor = 24;                    // f32 r, g, b, a
constexpr s32 kColorG = 28;
constexpr s32 kColorB = 32;
constexpr s32 kColorA = 36;
constexpr s32 kMinusCosAngle = 40;            // f32 (the cone)
constexpr s32 kSectorTies = 44;               // the list of its sector ties (next, prev; a tie's object link is tie + 12)
constexpr s32 kSectorTiesPrev = 48;
constexpr s32 kWorldLink = 52;                // the link in the world's light list (next, prev)
constexpr s32 kWorldLinkPrev = 56;
constexpr s32 kLightFrame = 60;               // u16 the frame stamp
}  // namespace light

namespace material {                          // RpMaterial
constexpr s32 kTexture = 0;
constexpr s32 kColor = 4;                     // u8 r, g, b, a (255 x 4 at create)
constexpr s32 kColorG = 5;
constexpr s32 kColorB = 6;
constexpr s32 kColorA = 7;
constexpr s32 kPipeline = 8;
constexpr s32 kAmbient = 12;                  // f32 the surface properties (from 0x77DD78)
constexpr s32 kSpecular = 16;
constexpr s32 kDiffuse = 20;
constexpr s32 kRefCount = 24;                 // u16
}  // namespace material

namespace clump {                             // RpClump
constexpr s32 kAtomics = 8;                   // the atomic list (next, prev; an atomic's link is atomic + 64)
constexpr s32 kAtomicsPrev = 12;
constexpr s32 kLights = 16;                   // the light list (ties at light + the light tie offset + 4)
constexpr s32 kLightsPrev = 20;
constexpr s32 kCameras = 24;                  // the camera list (ties at camera + the camera tie offset + 4)
constexpr s32 kCamerasPrev = 28;
constexpr s32 kStreamPad32 = 32;              // 0 at create
constexpr s32 kStreamPad36 = 36;
constexpr s32 kCallback = 40;                 // the clump callback (sub_490D80 at create)
}  // namespace clump

namespace atomic {                            // RpAtomic (types/model.h)
constexpr s32 kFrame = 4;
constexpr s32 kSync = 16;
constexpr s32 kGeometry = 24;
constexpr s32 kClump = 60;                    // the clump it is in
constexpr s32 kClumpLink = 64;                // the link in the clump's atomic list (next, prev)
constexpr s32 kClumpLinkPrev = 68;
constexpr s32 kRenderFrame = 96;              // u16 the frame stamp of its last render
constexpr s32 kSectorTies = 100;              // the list of its sector ties (next, prev; tie + 12)
constexpr s32 kSectorTiesPrev = 104;
constexpr s32 kPipeline = 108;                // (the user-data plugin's block pointer in sub_4906F0's family)
}  // namespace atomic

namespace tie {                               // an object-to-sector tie (24 bytes, the world module's two free lists)
constexpr s32 kSectorNext = 0;                // the link in the sector's list (next, prev)
constexpr s32 kSectorPrev = 4;
constexpr s32 kObject = 8;                    // the atomic / light
constexpr s32 kObjectNext = 12;               // the link in the object's list (next, prev)
constexpr s32 kObjectPrev = 16;
constexpr s32 kSector = 20;
}  // namespace tie

namespace bsp {                               // a BSP plane node / a world sector (type < 0)
constexpr s32 kType = 0;                      // < 0: a sector; else the axis offset 0 / 4 / 8 of the plane
constexpr s32 kPlane = 4;                     // f32 the plane value (camera walk)
constexpr s32 kLeft = 8;                      // the child below the plane
constexpr s32 kRight = 12;                    // the child above
constexpr s32 kLeftValue = 16;                // f32 the left child's upper bound on the axis
constexpr s32 kRightValue = 20;               // f32 the right child's lower bound
}  // namespace bsp

namespace sector {                            // RpWorldSector
constexpr s32 kTriangles = 4;                 // the triangles (8 bytes: three u16 vertex indices, the u16 material index)
constexpr s32 kAtomicTies = 56;               // the atomics tied to it (next, prev)
constexpr s32 kAtomicTiesPrev = 60;
constexpr s32 kLightTies = 64;                // the lights tied to it (next, prev)
constexpr s32 kLightTiesPrev = 68;
constexpr s32 kBoxSup = 72;                   // f32 x 3 the bounding box maximum (the BSP split of the world's box)
constexpr s32 kBoxInf = 84;                   // f32 x 3 its minimum
constexpr s32 kTightBoxSup = 96;              // f32 x 3 the box of its vertices (the collision reader's box)
constexpr s32 kTightBoxInf = 108;
constexpr s32 kMesh = 120;                    // the mesh header
constexpr s32 kMatListBase = 128;             // u16 the first material of the sector in the world's list
constexpr s32 kNumTriangles = 132;            // u16
}  // namespace sector

namespace world {                             // RpWorld
constexpr s32 kFlags = 8;                     // bit 0: tri-strips
constexpr s32 kMaterials = 16;                // the world's material array
constexpr s32 kNumMaterials = 20;
constexpr s32 kRootNode = 28;                 // the root BSP node
constexpr s32 kLocalLights = 52;              // the local lights (bit 7 type) (next, prev)
constexpr s32 kGlobalLights = 60;             // the directional / ambient lights (next, prev)
constexpr s32 kBoxSup = 80;                   // f32 x 3 the world's bounding box maximum
constexpr s32 kBoxInf = 92;                   // f32 x 3 its minimum
}  // namespace world

namespace camworld {                          // the camera's world extension (gpoff::kCamWorldExt)
constexpr s32 kSectors = 0;                   // the visible-sector array (grown by 50)
constexpr s32 kCapacity = 4;
constexpr s32 kCount = 8;
constexpr s32 kWorld = 12;
constexpr s32 kSavedBegin = 16;               // the camera's own begin / end / sync callbacks
constexpr s32 kSavedEnd = 20;
constexpr s32 kSavedSync = 24;
}  // namespace camworld

namespace objworld {                          // the atomic / light / clump world extensions
constexpr s32 kWorld = 0;
constexpr s32 kSavedSync = 4;                 // the object's own sync callback (atomic, light)
}  // namespace objworld

namespace geometry {                          // RpGeometry (types/model.h)
constexpr s32 kFlags = 8;                     // bit 4 normals, bit 24 native
constexpr s32 kLockFlags = 12;                // u16
constexpr s32 kRefCount = 14;                 // u16
constexpr s32 kNumTriangles = 16;
constexpr s32 kNumVertices = 20;
constexpr s32 kNumMorphTargets = 24;
constexpr s32 kMatList = 32;                  // the material list: +0 array, +4 count, +8 capacity
constexpr s32 kMatListCount = 36;
constexpr s32 kMorphTargets = 92;             // the morph-target array (28-byte records)
}  // namespace geometry

namespace morph {                             // a morph target (28 bytes)
constexpr s32 kParent = 0;                    // the geometry
constexpr s32 kSphere = 4;                    // f32 centre x, y, z, radius
constexpr s32 kVerts = 20;
constexpr s32 kNormals = 24;
constexpr s32 kSize = 28;
}  // namespace morph

namespace matlist {                           // a material list
constexpr s32 kArray = 0;
constexpr s32 kCount = 4;
constexpr s32 kCapacity = 8;                  // grown by 20
}  // namespace matlist

namespace image {                             // RwImage (rw4::rwimage)
constexpr s32 kFlags = 0;
constexpr s32 kWidth = 4;
constexpr s32 kHeight = 8;
constexpr s32 kDepth = 12;
constexpr s32 kStride = 16;
constexpr s32 kPixels = 20;
constexpr s32 kPalette = 24;
}  // namespace image

namespace coll {                              // the collision data of a sector / geometry (RpCollTree-like block)
constexpr s32 kFlags = 0;                     // bit 0: a triangle map follows
constexpr s32 kBoxSup = 4;                    // f32 x 3 the box maximum (the stream holds the minimum first)
constexpr s32 kBoxInf = 16;                   // f32 x 3 the box minimum
constexpr s32 kNumTriangles = 28;             // u16
constexpr s32 kNumSplits = 30;                // u16
constexpr s32 kSplits = 32;                   // the split array (16-byte records)
constexpr s32 kTriMap = 36;                   // the triangle map (u16 per triangle)
}  // namespace coll

namespace im3dmod {                           // the Im3D module (engine + gpoff::kIm3dModule): the pipelines in use, the defaults
constexpr s32 kTransform = 0;                 // the transform pipeline (sub_4F23C0)
constexpr s32 kRender3 = 4;                   // the render pipeline of primitive type 3 (tri-list)
constexpr s32 kRender5 = 8;                   //   type 5
constexpr s32 kRender4 = 12;                  //   type 4 (tri-strip)
constexpr s32 kRender1 = 16;                  //   type 1 (line list)
constexpr s32 kRender2 = 20;                  //   type 2 (polyline)
constexpr s32 kRender6 = 24;                  //   type 6
constexpr s32 kDefTransform = 28;             // the defaults the setters fall back to on 0
constexpr s32 kDefRender3 = 32;
constexpr s32 kDefRender5 = 36;
constexpr s32 kDefRender4 = 40;
constexpr s32 kDefRender1 = 44;
constexpr s32 kDefRender2 = 48;
constexpr s32 kDefRender6 = 52;
}  // namespace im3dmod

namespace pipemod {                           // the default object pipelines (engine + gpoff::kPipeModule)
constexpr s32 kAtomic = 60;                   // the atomics' default pipeline (sub_49C5C0)
constexpr s32 kSector = 64;                   // the world sectors' (sub_49C560)
constexpr s32 kMaterial = 68;                 // the materials' (sub_49C620)
constexpr s32 kDefAtomic = 84;                // what a 0 argument restores
constexpr s32 kDefSector = 88;
constexpr s32 kDefMaterial = 92;
}  // namespace pipemod

namespace pipeline {                          // RxPipeline (the fields the stream callbacks write)
constexpr s32 kPluginId = 44;                 // the plugin that owns it
constexpr s32 kPluginData = 48;
}  // namespace pipeline

namespace buildmesh {                         // a build mesh (12 bytes, the build-mesh free list)
constexpr s32 kCapacity = 0;
constexpr s32 kCount = 4;
constexpr s32 kTriangles = 8;                 // 20-byte triangle records
}  // namespace buildmesh

namespace engine {                            // the RW engine instance 0x960070, as offsets from it
constexpr s32 kCurrentCamera = 0;
constexpr s32 kCurrentWorld = 4;
constexpr s32 kRenderFrame = 8;               // u16
constexpr s32 kLightFrame = 10;               // u16
}  // namespace engine

}  // namespace rw5

void sub_45EC40(EEContext& ctx);  // 0x45EC40 [collTreeCreate] -- allocates a collision block for a sector / geometry
void sub_45EDC0(EEContext& ctx);  // 0x45EDC0 [collTreeDestroy] -- frees a collision block (RwFree, a tail call through 0x96017C)
void sub_45EDD0(EEContext& ctx);  // 0x45EDD0 [collTreeStreamGetSize] -- the payload of a collision chunk: 48 + 16 per split (+ 2 per triangle with a map)
void sub_45EE00(EEContext& ctx);  // 0x45EE00 [collTreeStreamWrite] -- writes a collision block as a chunk
void sub_45EFE0(EEContext& ctx);  // 0x45EFE0 [collTreeStreamRead] -- reads a collision chunk's struct: the header record, the block, the splits, the map
void sub_45F140(EEContext& ctx);  // 0x45F140 [collTreeStreamReadOld] -- reads the collision data of the older layout (library ids before 0x36001)
void sub_45F490(EEContext& ctx);  // 0x45F490 [collModuleOpen] -- the collision plugin's engine-module open: clears its module word and counts the open
void sub_45F4C0(EEContext& ctx);  // 0x45F4C0 [collModuleClose] -- the collision plugin's engine-module close: counts down
void sub_45F4E0(EEContext& ctx);  // 0x45F4E0 [collDataDestructor] -- the sector / geometry extension destructor: frees the collision block and clears the word
void sub_45F530(EEContext& ctx);  // 0x45F530 [collDataConstructor] -- the sector / geometry extension constructor: no collision block
void sub_45F540(EEContext& ctx);  // 0x45F540 [collDataStreamGetSize] -- the extension chunk size: 0 without a block, else its chunk size + 16
void sub_45F600(EEContext& ctx);  // 0x45F600 [collDataStreamRead] -- reads the collision extension of a sector / geometry
void sub_45F7B0(EEContext& ctx);  // 0x45F7B0 [collAtomicConstructor] -- the atomic extension constructor: clears the word at atomic + gp 0x7CE724
void sub_464280(EEContext& ctx);  // 0x464280 [pairArrayCreate] -- allocates a counted array of n zeroed 8-byte pairs: {count, -> the pairs}
void sub_490690(EEContext& ctx);  // 0x490690 [pipeStreamModuleClose] -- the atomic-pipeline stream module's close: counts down (gp 0x7CE80C)
void sub_4906B0(EEContext& ctx);  // 0x4906B0 [pipeStreamModuleOpen] -- the atomic-pipeline stream module's open: counts the open
void sub_4906F0(EEContext& ctx);  // 0x4906F0 [atomicPipelineStreamRead] -- reads an atomic's pipeline extension: the plugin id (and data for 8 bytes) into globals
void sub_490770(EEContext& ctx);  // 0x490770 [atomicPipelineStreamWrite] -- writes an atomic's pipeline extension: its pipeline's plugin id and data
void sub_4907E0(EEContext& ctx);  // 0x4907E0 [atomicPipelineStreamGetSize] -- 8 when the atomic has a pipeline with a plugin id, else 0
void sub_490CA0(EEContext& ctx);  // 0x490CA0 [cameraClumpTieConstructor] -- the camera's clump-tie extension constructor: clears its 12 bytes
void sub_490CC0(EEContext& ctx);  // 0x490CC0 [cameraClumpTieCopy] -- the camera's clump-tie copy: nothing to copy, returns the camera
void sub_490CD0(EEContext& ctx);  // 0x490CD0 [lightClumpTieConstructor] -- the light's clump-tie extension constructor: clears its 12 bytes
void sub_490CF0(EEContext& ctx);  // 0x490CF0 [lightClumpTieCopy] -- the light's clump-tie copy: nothing to copy, returns the light
void sub_490D00(EEContext& ctx);  // 0x490D00 [clumpDestroyLightCB] -- the clump destroy's light callback: out of the clump (sub_492020), then destroyed
void sub_491410(EEContext& ctx);  // 0x491410 [clumpModuleClose] -- the clump / atomic module's close: every clump, then every atomic destroyed; both free lists
void sub_4914D0(EEContext& ctx);  // 0x4914D0 [clumpModuleOpen] -- the clump / atomic module's open: the atomic and clump free lists (16-aligned, static records)
void sub_4915C0(EEContext& ctx);  // 0x4915C0 [clumpTiesAttach] -- registers the 12-byte clump-tie extensions of cameras and lights; 1 when both offsets are valid
void sub_491760(EEContext& ctx);  // 0x491760 [clumpForAllCameras] -- calls a callback on each camera of a clump until it returns 0; returns the clump
void sub_4917F0(EEContext& ctx);  // 0x4917F0 [clumpForAllLights] -- calls a callback on each light of a clump until it returns 0; returns the clump
void sub_491DE0(EEContext& ctx);  // 0x491DE0 [clumpCreate] -- a clump from the clump free list: type 2, empty atomic / light / camera lists, the default callback
void sub_491FF0(EEContext& ctx);  // 0x491FF0 [clumpAddAtomic] -- links an atomic at the head of the clump's atomic list and sets its clump; returns the clump
void sub_492020(EEContext& ctx);  // 0x492020 [clumpRemoveLight] -- unlinks a light's clump tie and clears it; returns the clump
void sub_492060(EEContext& ctx);  // 0x492060 [clumpRemoveCamera] -- unlinks a camera's clump tie and clears it; returns the clump
void sub_492C30(EEContext& ctx);  // 0x492C30 [atomicRegisterPlugin] -- registers an atomic plugin (sub_4C61B0 on the atomic registry 0x77DCE0)
void sub_492C60(EEContext& ctx);  // 0x492C60 [clumpRegisterPlugin] -- registers a clump plugin (sub_4C61B0 on the clump registry 0x77DD00)
void sub_492C90(EEContext& ctx);  // 0x492C90 [atomicRegisterPluginStream] -- sets an atomic plugin's stream read / write / size callbacks; its offset or -1
void sub_492CC0(EEContext& ctx);  // 0x492CC0 [atomicSetStreamAlwaysCallBack] -- sets an atomic plugin's 'always' stream callback; its offset or -1
void sub_492CE0(EEContext& ctx);  // 0x492CE0 [atomicSetStreamRightsCallBack] -- sets an atomic plugin's rights callback; its offset or -1
void sub_492D00(EEContext& ctx);  // 0x492D00 [atomicGetPluginOffset] -- the offset of an atomic plugin's data, -1 when it is not registered
void sub_492DE0(EEContext& ctx);  // 0x492DE0 [geometryModuleOpen] -- the geometry module's open: keeps its offset (gp 0x7CE828), counts the open
void sub_492E00(EEContext& ctx);  // 0x492E00 [geometryModuleClose] -- the geometry module's close: counts down
void sub_492E20(EEContext& ctx);  // 0x492E20 [morphTargetCalcBoundingSphere] -- a morph target's bounding sphere: the centre of its vertices' box, the radius
void sub_492F80(EEContext& ctx);  // 0x492F80 [geometryAddMorphTargets] -- grows a geometry's morph-target array by n; the first new index or -1
void sub_493210(EEContext& ctx);  // 0x493210 [triangleSetVertexIndices] -- ($a1 = the triangle) its three u16 vertex indices; returns the geometry
void sub_493230(EEContext& ctx);  // 0x493230 [triangleSetMaterial] -- ($a1 = the triangle, $a2 = the material) its index in the geometry's material list
void sub_493B40(EEContext& ctx);  // 0x493B40 [geometryAddRef] -- adds a reference to a geometry (+14); returns it
void sub_493C50(EEContext& ctx);  // 0x493C50 [geometryRegisterPlugin] -- registers a geometry plugin (sub_4C61B0 on the geometry registry 0x77DD20)
void sub_493C80(EEContext& ctx);  // 0x493C80 [geometryRegisterPluginStream] -- sets a geometry plugin's stream callbacks; its offset or -1
void sub_494490(EEContext& ctx);  // 0x494490 [lightDestroyCB] -- the light module close's walk callback: destroys the light (sub_494760, a tail call)
void sub_4944A0(EEContext& ctx);  // 0x4944A0 [lightSyncNone] -- the light's default object sync: nothing to do, returns the light
void sub_4944B0(EEContext& ctx);  // 0x4944B0 [lightSetColor] -- copies a light's colour (r, g, b, a) and sets its private flag byte to (r == g == b)
void sub_494520(EEContext& ctx);  // 0x494520 [lightRegisterPlugin] -- registers a light plugin (sub_4C61B0 on the light registry 0x77DD40)
void sub_494550(EEContext& ctx);  // 0x494550 [lightRegisterPluginStream] -- sets a light plugin's stream callbacks; its offset or -1
void sub_494760(EEContext& ctx);  // 0x494760 [lightDestroy] -- destroys a light: the plugin destructors, off its frame (sub_4D18C0), back to its free list; 1
void sub_4947C0(EEContext& ctx);  // 0x4947C0 [lightCreate] -- ($a0 = the light type) a light from the light free list, then the light plugins' constructors
void sub_4948B0(EEContext& ctx);  // 0x4948B0 [lightModuleClose] -- the light module's close: every live light destroyed, the free list destroyed, count down
void sub_494930(EEContext& ctx);  // 0x494930 [lightModuleOpen] -- the light module's open: the light free list (16-aligned, the static record 0x95DED0)
void sub_4949C0(EEContext& ctx);  // 0x4949C0 [materialPipelineStreamRead] -- reads a material's pipeline extension: the plugin id (and data) into globals
void sub_494A40(EEContext& ctx);  // 0x494A40 [materialPipelineStreamWrite] -- writes a material's pipeline extension: its pipeline's plugin id and data
void sub_494AB0(EEContext& ctx);  // 0x494AB0 [materialPipelineStreamGetSize] -- 8 when the material has a pipeline with a plugin id, else 0
void sub_494AE0(EEContext& ctx);  // 0x494AE0 [materialModuleOpen] -- the material module's open: the material free list (4-aligned, static record 0x95DF00)
void sub_494B70(EEContext& ctx);  // 0x494B70 [materialModuleClose] -- the material module's close: destroys the material free list; count down
void sub_494BE0(EEContext& ctx);  // 0x494BE0 [materialCreate] -- a material from its free list: one reference, white, no texture or pipeline, the default
void sub_494DB0(EEContext& ctx);  // 0x494DB0 [materialRegisterPlugin] -- registers a material plugin (sub_4C61B0 on the material registry 0x77DD60)
void sub_494DE0(EEContext& ctx);  // 0x494DE0 [materialRegisterPluginStream] -- sets a material plugin's stream callbacks; its offset or -1
void sub_494E10(EEContext& ctx);  // 0x494E10 [materialSetStreamRightsCallBack] -- sets a material plugin's rights callback; its offset or -1
void sub_495300(EEContext& ctx);  // 0x495300 [matListInit] -- empties a material list (array, count, capacity 0); returns it
void sub_495340(EEContext& ctx);  // 0x495340 [matListAppendMaterial] -- appends a material to a list (grown by 20); its index or -1
void sub_495480(EEContext& ctx);  // 0x495480 [matListFindMaterial] -- the index of a material in a list, searched from the end; -1 when it is missing
void sub_4959C0(EEContext& ctx);  // 0x4959C0 [meshMalloc] -- RwMalloc(size, 0x30502) for mesh data (a tail call)
void sub_4959E0(EEContext& ctx);  // 0x4959E0 [meshModuleClose] -- the mesh module's close: counts down; the last close destroys the build-mesh free list
void sub_495A30(EEContext& ctx);  // 0x495A30 [meshModuleOpen] -- the mesh module's open: the build-mesh free list (once), the module's primitive code tables
void sub_495B10(EEContext& ctx);  // 0x495B10 [buildMeshCreate] -- ($a0 = triangles) a build mesh from its free list with room for n 20-byte triangles
void sub_495C20(EEContext& ctx);  // 0x495C20 [buildMeshDestroy] -- frees a build mesh's triangle records and returns it to its free list; 1
void sub_495C80(EEContext& ctx);  // 0x495C80 [meshHeaderDestroy] -- frees a mesh header (RwFree) when any of its first fields is set; 1
void sub_4991F0(EEContext& ctx);  // 0x4991F0 [sectorModuleOpen] -- the world-sector module's open: counts the open
void sub_499210(EEContext& ctx);  // 0x499210 [sectorModuleClose] -- the world-sector module's close: counts down
void sub_499250(EEContext& ctx);  // 0x499250 [sectorRegisterPlugin] -- registers a world-sector plugin (sub_4C61B0 on the sector registry 0x77DDB0)
void sub_499280(EEContext& ctx);  // 0x499280 [sectorRegisterPluginStream] -- sets a world-sector plugin's stream callbacks; its offset or -1
void sub_4992B0(EEContext& ctx);  // 0x4992B0 [sectorSetStreamAlwaysCallBack] -- sets a world-sector plugin's 'always' stream callback; its offset or -1
void sub_4992D0(EEContext& ctx);  // 0x4992D0 [sectorSetStreamRightsCallBack] -- sets a world-sector plugin's rights callback; its offset or -1
void sub_499400(EEContext& ctx);  // 0x499400 [sectorBuildMesh] -- builds a sector's mesh from its triangles
void sub_499D30(EEContext& ctx);  // 0x499D30 [worldCalcSectorBoxes] -- gives every sector of a world the box of its BSP cell
void sub_499E90(EEContext& ctx);  // 0x499E90 [pendingPairAdd] -- links a new {first, second} record at the head of the world module's pending list
void sub_499F40(EEContext& ctx);  // 0x499F40 [pendingPairRemove] -- unlinks and frees the pending record whose first word is $a0 (if any)
void sub_499FD0(EEContext& ctx);  // 0x499FD0 [worldDestroySectorMeshes] -- frees every sector's mesh header (sub_495C80) and clears it; the world (0: no tree)
void sub_49A080(EEContext& ctx);  // 0x49A080 [worldBuildSectorMeshes] -- builds the mesh of every sector that has none; the world, or 0 on a failure
void sub_49A7C0(EEContext& ctx);  // 0x49A7C0 [worldForAllMaterials] -- calls a callback on each material of a world until it returns 0; returns the world
void sub_49A920(EEContext& ctx);  // 0x49A920 [worldRegisterPlugin] -- registers a world plugin (sub_4C61B0 on the world registry 0x77DDD0)
void sub_49A950(EEContext& ctx);  // 0x49A950 [worldRegisterPluginStream] -- sets a world plugin's stream callbacks; its offset or -1
void sub_49AAF0(EEContext& ctx);  // 0x49AAF0 [worldTiesModuleOpen] -- the world-ties module's open: the atomic-tie and light-tie free lists (24-byte records)
void sub_49ABF0(EEContext& ctx);  // 0x49ABF0 [worldTiesModuleClose] -- the world-ties module's close: destroys both tie free lists; count down
void sub_49AC90(EEContext& ctx);  // 0x49AC90 [cameraWorldBeginUpdate] -- the camera's begin-update in a world: its world current, a new frame stamp, its own begin-update
void sub_49ACD0(EEContext& ctx);  // 0x49ACD0 [cameraWorldEndUpdate] -- the camera's end in a world: no current world, then its own end-update (tail call)
void sub_49ACF0(EEContext& ctx);  // 0x49ACF0 [cameraWorldSync] -- the camera's sync in a world: its own sync, then its visible-sector list (sub_49B850)
void sub_49AD80(EEContext& ctx);  // 0x49AD80 [cameraWorldExtConstructor] -- the camera's world extension constructor: no list, no world; saves the camera's
void sub_49ADE0(EEContext& ctx);  // 0x49ADE0 [cameraWorldExtCopy] -- the camera's world extension copy: an empty list; the copy joins the source's world
void sub_49AE30(EEContext& ctx);  // 0x49AE30 [cameraWorldExtDestructor] -- the camera's world extension destructor: frees the sector list, restores the camera's callbacks
void sub_49AEB0(EEContext& ctx);  // 0x49AEB0 [lightTieFree] -- unlinks a light-sector tie from both lists and returns it to the light-tie free list; 1
void sub_49AF20(EEContext& ctx);  // 0x49AF20 [atomicTieFree] -- unlinks an atomic-sector tie (when it is in use) and returns it to the atomic-tie free list; 1
void sub_49AFA0(EEContext& ctx);  // 0x49AFA0 [atomicTieToSectors] -- ties an atomic to every sector its world bounding sphere's box reaches
void sub_49B180(EEContext& ctx);  // 0x49B180 [atomicWorldSync] -- the atomic's sync in a world: its own sync, then its old ties freed and new ones made
void sub_49B290(EEContext& ctx);  // 0x49B290 [atomicWorldExtConstructor] -- the atomic's world extension constructor: no world, an old render stamp, the world sync installed
void sub_49B2D0(EEContext& ctx);  // 0x49B2D0 [atomicWorldExtCopy] -- the atomic's world extension copy: returns the atomic
void sub_49B2E0(EEContext& ctx);  // 0x49B2E0 [atomicWorldExtDestructor] -- the atomic's world extension destructor: its ties freed, its own sync restored
void sub_49B3C0(EEContext& ctx);  // 0x49B3C0 [clumpWorldExtConstructor] -- the clump's world extension constructor: no world; +4 from the world module's +8
void sub_49B430(EEContext& ctx);  // 0x49B430 [clumpWorldExtDestructor] -- the clump's world extension destructor: nothing to do, returns the clump
void sub_49B440(EEContext& ctx);  // 0x49B440 [lightWorldSync] -- the light's sync in a world: its own sync, then a local light is tied to the sectors it reaches
void sub_49B730(EEContext& ctx);  // 0x49B730 [lightWorldExtConstructor] -- the light's world extension constructor: no world, saves its sync, installs sub_49B440
void sub_49B760(EEContext& ctx);  // 0x49B760 [lightWorldExtCopy] -- the light's world extension copy: the copy joins the source's world (sub_49C3D0)
void sub_49B7A0(EEContext& ctx);  // 0x49B7A0 [lightWorldExtDestructor] -- the light's world extension destructor: frees its sector ties
void sub_49B850(EEContext& ctx);  // 0x49B850 [cameraBuildSectorList] -- builds a camera's visible-sector list: the BSP walked against the frustum
void sub_49BBC0(EEContext& ctx);  // 0x49BBC0 [worldAddAtomicCB] -- a for-all callback: adds the atomic to the world (sub_49C1E0); returns the atomic
void sub_49BBF0(EEContext& ctx);  // 0x49BBF0 [worldAddLightCB] -- a for-all callback: adds the light to the world (sub_49C3D0); returns the light
void sub_49BC20(EEContext& ctx);  // 0x49BC20 [worldAddCameraCB] -- a for-all callback: adds the camera to the world (sub_49C160); returns the camera
void sub_49C160(EEContext& ctx);  // 0x49C160 [worldAddCamera] -- ($a0 = the world, $a1 = the camera) the camera's world; its frame marked dirty; the world
void sub_49C1B0(EEContext& ctx);  // 0x49C1B0 [worldRemoveCamera] -- the camera leaves its world (no world, no sectors); 0 when it had none
void sub_49C1E0(EEContext& ctx);  // 0x49C1E0 [worldAddAtomic] -- ($a0 = the world, $a1 = the atomic) the atomic's world; its frame marked dirty (re-tie)
void sub_49C230(EEContext& ctx);  // 0x49C230 [atomicGetWorld] -- the world an atomic is in
void sub_49C3D0(EEContext& ctx);  // 0x49C3D0 [worldAddLight] -- ($a0 = the world, $a1 = the light) the light joins the world's global list (type < 0x80)
void sub_49C480(EEContext& ctx);  // 0x49C480 [worldRemoveLight] -- the light leaves its world: its sector ties freed, out of the world's light list
void sub_49C560(EEContext& ctx);  // 0x49C560 [setDefaultSectorPipeline] -- sets the world sectors' default pipeline (0: the original default); returns it
void sub_49C5C0(EEContext& ctx);  // 0x49C5C0 [setDefaultAtomicPipeline] -- sets the atomics' default pipeline (0: the original default); returns it
void sub_49C620(EEContext& ctx);  // 0x49C620 [setDefaultMaterialPipeline] -- sets the materials' default pipeline (0: the original default); returns it
void sub_49C790(EEContext& ctx);  // 0x49C790 [worldPluginsDone] -- returns 1 (the end of the world plugins' attach sequence)
void sub_4C69F0(EEContext& ctx);  // 0x4C69F0 [v3dNormalize] -- dst = src / |src|; $f0 = the length; error 25 for a zero vector (dst = src x 0)
void sub_4C6AC0(EEContext& ctx);  // 0x4C6AC0 [v3dLength] -- $f0 = |v| (3-D)
void sub_4C6AF0(EEContext& ctx);  // 0x4C6AF0 [v2dLength] -- $f0 = |v| (2-D)
void sub_4C6B20(EEContext& ctx);  // 0x4C6B20 [v2dNormalize] -- dst = src / |src| (2-D); $f0 = the length; error 25 for a zero vector
void sub_4C6C20(EEContext& ctx);  // 0x4C6C20 [v3dTransformPoints] -- transforms points by a matrix through the vector module's function (+12); the dst
void sub_4C6CA0(EEContext& ctx);  // 0x4C6CA0 [v3dTransformVectors] -- transforms vectors by a matrix through the vector module's function (+20); the dst
void sub_4C6CE0(EEContext& ctx);  // 0x4C6CE0 [v3dModuleClose] -- the vector module's close: counts down
void sub_4C7A50(EEContext& ctx);  // 0x4C7A50 [bboxCalculate] -- the box of n points: the maximum at +0, the minimum at +12; returns the box
void sub_4C89A0(EEContext& ctx);  // 0x4C89A0 [cameraUpdateZShiftScale] -- the camera's device z scale and shift from its clip planes
void sub_4C8A60(EEContext& ctx);  // 0x4C8A60 [cameraBuildPerspFrustum] -- the perspective camera's frustum: its 8 corners and 6 planes in world space
void sub_4C9270(EEContext& ctx);  // 0x4C9270 [cameraBuildPerspViewMatrix] -- the perspective camera's view matrix from its frame and view window / offset
void sub_4C9400(EEContext& ctx);  // 0x4C9400 [cameraBuildParallelFrustum] -- the parallel camera's frustum: its 8 corners (transformed by the frame, sub_4C6C20) and 6 planes
void sub_4C9940(EEContext& ctx);  // 0x4C9940 [cameraBuildParallelViewMatrix] -- the parallel camera's view matrix from its frame and view window / offset
void sub_4C9AD0(EEContext& ctx);  // 0x4C9AD0 [cameraSync] -- the camera's object sync: the view matrix and frustum for its projection, then the frustum's box
void CameraEndUpdate(EEContext& ctx);  // 0x4C9B40 -- the camera's end-update: the device's end-update; the current camera cleared; the camera or 0
void CameraBeginUpdate(EEContext& ctx);  // 0x4C9BA0 -- the camera's begin-update: current camera, dirty frames synced, the device's begin-update
void sub_4C9C00(EEContext& ctx);  // 0x4C9C00 [cameraModuleClose] -- the camera module's close: destroys the camera free list; count down
void sub_4C9C70(EEContext& ctx);  // 0x4C9C70 [cameraModuleOpen] -- the camera module's open: the camera free list (16-aligned, static record 0x960040)
void sub_4C9D20(EEContext& ctx);  // 0x4C9D20 [cameraSetViewOffset] -- sets the camera's view offset (x, y); its frame marked dirty; returns the camera
void sub_4C9DB0(EEContext& ctx);  // 0x4C9DB0 [cameraSetFarClipPlane] -- sets the far clip ($f12), refreshes the z scale / shift, marks the frame dirty
void sub_4C9F00(EEContext& ctx);  // 0x4C9F00 [cameraSetProjection] -- sets the projection (1 perspective, 2 parallel; else 'Invalid projection type
void sub_4C9F90(EEContext& ctx);  // 0x4C9F90 [cameraSetViewWindow] -- sets the view window (x, y) and its reciprocals; marks the frame dirty
void sub_4CA000(EEContext& ctx);  // 0x4CA000 [cameraRegisterPlugin] -- registers a camera plugin (sub_4C61B0 on the camera registry 0x77E5E0)
void sub_4CA090(EEContext& ctx);  // 0x4CA090 [cameraCreate] -- a camera from the camera free list, then the camera plugins' constructors
void sub_4CBC70(EEContext& ctx);  // 0x4CBC70 [imageModuleClose] -- the image module's close: its scratch buffers and list records freed, its free lists destroyed
void sub_4CBE00(EEContext& ctx);  // 0x4CBE00 [imageCreate] -- ($a0 = width, $a1 = height, $a2 = depth) an image from its free list, without pixels or palette
void sub_4CBEB0(EEContext& ctx);  // 0x4CBEB0 [imageDestroy] -- destroys an image: owned pixels freed (sub_4CC050), the plugin destructors, back to its free
void sub_4CC050(EEContext& ctx);  // 0x4CC050 [imageFreePixels] -- frees an image's pixels (RwFree), clears pixels / palette and the owned flag; the image
void sub_4CC6B0(EEContext& ctx);  // 0x4CC6B0 [imageGetScratch] -- the image module's scratch buffer (+4)
void sub_4CD750(EEContext& ctx);  // 0x4CD750 [imageStreamRead] -- reads an image chunk: the 16-byte header, the image, its pixels and palette
void sub_4D18C0(EEContext& ctx);  // 0x4D18C0 [objectHasFrameReleaseFrame] -- takes an object off its frame's object list (when it has a frame)
void sub_4F23C0(EEContext& ctx);  // 0x4F23C0 [im3dSetTransformPipeline] -- sets the Im3D transform pipeline (0: the default); returns the one in use
void sub_4F2430(EEContext& ctx);  // 0x4F2430 [im3dSetRenderPipeline] -- sets the Im3D render pipeline of a primitive type ($a1 = 1..6; $a0 = 0: the default); the one in use
void sub_4F28E0(EEContext& ctx);  // 0x4F28E0 [cameraBeginUpdateHook] -- an empty hook called at the end of CameraBeginUpdate

}  // namespace p3fes::game
