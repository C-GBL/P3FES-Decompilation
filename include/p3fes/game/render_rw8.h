// Slice render_rw8: RenderWare, eighth pass -- the RxPipeline core render_rw7 left for size and the pipe constructors
// that need it, then RW leftovers of the band 0x45EC20-0x4F72F0 that touch no hardware: 150 functions, started from
// p3fes_handgen and made readable (game/src/render/render_rw8.cpp).
//
// Groups (sub_* keep their symbols/functions.json names; proposed names in brackets, symbols/deltas/render_rw8.sym; RW
// 3.x public API names only where the body does what that API does):
//   * The RxPipeline core (0x4F2730-0x4F72F0): the pipeline module's open / close (the 52-byte pipeline free list, the
//     node limit 64, the default render-state vector, the global RxHeap), RxPipelineCreate (sub_4F2F70),
//     RxPipelineLock (sub_4F4640), RxLockedPipeAddFragment (sub_4F4950: a NULL-terminated list of node definitions in
//     $a2.., chained output 0 -> next), RxLockedPipeAddPath (sub_4F4C30), RxPipelineFindNodeByName (sub_4F4830),
//     RxLockedPipeUnlock (sub_4F3F80) with its passes: the node record set-up from a definition (sub_4F3680), the super
//     block sizing / relocation (sub_4F3260) and copy (sub_4F3410), the distinct-cluster count (sub_4F31C0), the
//     topological sort (sub_4F3880 in-degrees, sub_4F3970 the depth-first placement that swaps nodes into order,
//     sub_4F3D60), the cluster passes behind sub_4F6140 (requirement lists sub_4F50A0 / sub_4F4CF0 / sub_4F4DB0,
//     propagation sub_4F5520, slot allocation sub_4F57F0 / sub_4F4FE0 / sub_4F5A90, the slot sort sub_4F5D90 /
//     sub_4F5C50 / sub_4F7080 with its radix pass sub_4F6CE0 and insertion pass sub_4F6F20), a top-down scratch
//     allocator in the super block (sub_4F30E0); the RxHeap (create sub_4F6A10, destroy sub_4F6970, alloc sub_4F67B0
//     with its split sub_4F64F0 and grow sub_4F63D0, free sub_4F65B0), a packet's cluster release (sub_4F28F0),
//     RwIm3DRenderLine (sub_4F22B0) and four empty / constant module hooks.
//   * The pipe constructors: the PDS registry's (0x46A600-0x46AFA0: the engine open that builds every registered pipe,
//     RpPDSRegisterPipe / PDSRegistryAddPipe, RpPDSSkyMatPipeCreate for material definitions, sub_46AFA0 for object
//     definitions, sub_46A8D0 the object pipe's link to its material pipe), PTank's (0x474BB0-0x47B1A0: the engine open /
//     close and the six pipes: the 2D / 3D sprite PS2AllMat pipes and their PS2All object pipes, the tank pipe, the
//     instancing pipe), Im3D's (0x499A80-0x49C9B0: the module open / close, the FastIm3DTransform pipe, the render
//     pipes taken from the PDS registry), the PS2AllMat node's initialisation (0x4A30D0, 0x4A3540: the cluster layout).
//   * The world's leftovers: the user-data plugin registrations (sub_48F030, plugin 0x11F on nine object types), plugin
//     0x11D's registration and stream write (sub_45F7D0, sub_45F580), the world-sector / plane-sector stream readers
//     (sub_48F580, sub_48FBD0), a float compare wrapper (sub_45EC20).
//   * Rt2d's object layer (0x4A9A80-0x4AE150): the font lookup by name, the object string / text / brush set-ups, the
//     scene's object tree walks; the path fill's triangulation (0x4B0B10, 0x4B0FA0); Rt2dAnim's keyframe lists and the
//     maestro (0x4B1420-0x4B5B50).
//   * Image files: the BMP reader / writer (0x4B9840-0x4BAD50), the Sun raster writer's open (0x4BE930).
//   * The mipmap K / L pass over a world's sectors (0x4BC830-0x4BCBF0, 0x4D8320).
//   * RtQuat (0x4BDB30-0x4BE310): RtQuatConvertFromMatrix (sub_4BDCB0 with its three major-axis cases), RtQuatRotate
//     (sub_4BDDE0), RtQuatTransformVectors (sub_4BE1E0), RtQuatSetupSlerpCache (sub_4BE310).
//   * The palette quantiser (0x4D1900-0x4D41E0): an octree over (alpha, luminance-weighted colour) that the sky
//     driver's raster conversions use to reduce an image to a 16 / 256-colour palette.
//
// The pipeline rules the pair tests check (tests/game/test_render_rw8.cpp):
//   * a lock / unlock round trip of every live pipeline (the PDS registry's 33, PTank's six, the Im3D transform) keeps
//     every node, output, initialisation data, input-slot map, the cluster-slot count and the entry point; the unlock
//     re-runs each node's initialisation, so the private data goes back to the definition's defaults (PS2AllMat: no
//     callbacks, VIF offset 0x114, the default VU1 code array 0x77F130 x 32; PS2All: no callback, no material
//     pipeline) -- every constructor sets its callbacks after the unlock;
//   * the constructors rebuild the live pipelines node for node, private data included;
//   * the unlock sorts the nodes topologically (each output leads to a later node), makes node 0 the entry point and
//     gives each distinct cluster one slot.
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/render_rw7.h"  // rw7:: (and rw6:: .. rw4::) the records of the earlier passes

namespace p3fes::game {

namespace rw8 {

namespace rxpipeline {                        // an RxPipeline (52 bytes, the pipeline module's free list)
constexpr s32 kLocked = 0;
constexpr s32 kNumNodes = 4;
constexpr s32 kNodes = 8;                     // 40-byte node records (rxpnode), in the super block
constexpr s32 kClusterSlots = 12;             // the distinct clusters of the nodes (one slot each)
constexpr s32 kPacketState = 16;
constexpr s32 kPacket = 20;                   // relocated with the super block
constexpr s32 kNumInputReqs = 24;
constexpr s32 kInputReqs = 28;                // relocated with the super block
constexpr s32 kSuperBlock = 32;               // one RwMalloc'd block: nodes, outputs, slot records, private data
constexpr s32 kSuperBlockSize = 36;
constexpr s32 kEntryPoint = 40;               // the index of the first node
constexpr s32 kPluginId = 44;
constexpr s32 kPluginData = 48;
constexpr s32 kSize = 52;
}  // namespace rxpipeline

namespace rxpnode {                           // an RxPipelineNode (40 bytes)
constexpr s32 kNodeDef = 0;
constexpr s32 kNumOutputs = 4;
constexpr s32 kOutputs = 8;                   // the node index of each output, -1 unconnected
constexpr s32 kSlotClusterRefs = 12;
constexpr s32 kSlotsContinue = 16;
constexpr s32 kPrivateData = 20;
constexpr s32 kInputToSlot = 24;              // a slot index per cluster of interest
constexpr s32 kTopSortData = 28;              // the unlock's work record (in-degree, placed count, cluster list)
constexpr s32 kInitData = 32;
constexpr s32 kInitDataSize = 36;
constexpr s32 kSize = 40;
}  // namespace rxpnode

namespace rxdef {                             // an RxNodeDefinition
constexpr s32 kName = 0;
constexpr s32 kBody = 4;
constexpr s32 kNodeInit = 8;                  // called when the first pipeline node of the definition is made
constexpr s32 kNodeTerm = 12;                 // called when the last one goes
constexpr s32 kPipelineNodeInit = 16;         // per node, at the unlock
constexpr s32 kPipelineNodeTerm = 20;         // per node, at the lock
constexpr s32 kPipelineNodeConfig = 24;       // per node, after the unlock's sort
constexpr s32 kConfigMsgHandler = 28;
constexpr s32 kNumClusters = 32;              // at most 32
constexpr s32 kClusters = 36;                 // 12-byte cluster refs (rxclref)
constexpr s32 kInputReqs = 40;                // a requirement per cluster: 0 not wanted, 1 required, 2 optional
constexpr s32 kNumOutputs = 44;               // at most 32
constexpr s32 kOutputs = 48;                  // 12-byte output specs (rxoutspec)
constexpr s32 kPrivateDataSize = 52;
constexpr s32 kEditable = 56;
constexpr s32 kUseCount = 60;                 // pipeline nodes made from it
}  // namespace rxdef

namespace rxclref {                           // a cluster of interest (12 bytes)
constexpr s32 kCluster = 0;                   // the cluster definition: name, default stride, attributes
constexpr s32 kForcePresent = 4;
constexpr s32 kSize = 12;
}  // namespace rxclref

namespace rxoutspec {                         // an output of a node definition (12 bytes)
constexpr s32 kName = 0;
constexpr s32 kClusterStatus = 4;             // per cluster of interest: 0 no change, 1 valid, 2 invalid
constexpr s32 kAllOther = 8;                  // the status of every other cluster
constexpr s32 kSize = 12;
}  // namespace rxoutspec

namespace pipemodule {                        // the pipeline module (engine 0x960070 + gp 0x7CEB28)
constexpr s32 kFreeList = 0;                  // the 52-byte pipeline free list
constexpr s32 kRenderState = 4;               // the default render-state vector (44 bytes)
constexpr s32 kMaxNodes = 56;                 // the node limit of a pipeline (64)
}  // namespace pipemodule

namespace rxheap {                            // an RxHeap (28 bytes)
constexpr s32 kBlockSize = 0;                 // the size a new super block gets
constexpr s32 kSuperBlocks = 4;               // the chain of super blocks (+0 aligned start, +4 size, +8 next)
constexpr s32 kFreeEntries = 12;              // 8-byte free entries {size, block header}
constexpr s32 kEntriesCapacity = 16;
constexpr s32 kNumFree = 20;
constexpr s32 kDirty = 24;                    // set by every allocation
}  // namespace rxheap

namespace heapblock {                         // an RxHeap block header (32 bytes before the user's bytes)
constexpr s32 kPrev = 0;
constexpr s32 kNext = 4;
constexpr s32 kSize = 8;
constexpr s32 kFreeEntry = 12;                // the free entry while free, 0 while allocated
}  // namespace heapblock

namespace pdsentry {                          // a PDS registry entry (20 bytes; rw7::pdsreg holds the array)
constexpr s32 kDef = 0;                       // the pipe definition (pdsmatdef / pdsobjdef)
constexpr s32 kAuxId = 4;                     // an object pipe's material pipe id (0: none)
constexpr s32 kId = 8;
constexpr s32 kType = 12;                     // 1 material pipe, 2 object pipe
constexpr s32 kPipe = 16;
constexpr s32 kSize = 20;
}  // namespace pdsentry

namespace pdsmatdef {                         // a PDS material pipe definition (132 bytes)
constexpr s32 kPluginId = 0;
constexpr s32 kPluginData = 4;
constexpr s32 kClusters = 8;                  // up to 10 {cluster, type} pairs, 0-terminated
constexpr s32 kPrimType = 88;                 // 1 / 2 lines, 3..5 triangles, 6 points
constexpr s32 kBatch0 = 92;                   // the VU batch set-up of that primitive type
constexpr s32 kBatch1 = 96;
constexpr s32 kBatch2 = 100;
constexpr s32 kVifOffset = 104;
constexpr s32 kVU1Code = 108;                 // -> {code array, count}
constexpr s32 kCallBack1 = 112;               // the five PS2AllMat callbacks
constexpr s32 kCallBack2 = 116;
constexpr s32 kCallBack3 = 120;
constexpr s32 kCallBack4 = 124;
constexpr s32 kCallBack5 = 128;
}  // namespace pdsmatdef

namespace pdsobjdef {                         // a PDS object pipe definition (20 bytes)
constexpr s32 kPluginId = 0;
constexpr s32 kPluginData = 4;
constexpr s32 kCallBack1 = 8;                 // the PS2All node's two callbacks
constexpr s32 kCallBack2 = 12;
constexpr s32 kMatPipe = 16;                  // its material pipeline (set from the aux id at registration)
}  // namespace pdsobjdef

namespace ptankpipes {                        // PTank's six pipelines (24 bytes; engine + gp 0x7CE774)
constexpr s32 kTank = 0;                      // PS2PTank.csl
constexpr s32 kSpr2dMat = 4;                  // the 2D sprite PS2AllMat pipe
constexpr s32 kSpr2dObj = 8;                  // its PS2All object pipe
constexpr s32 kSpr3dMat = 12;
constexpr s32 kSpr3dObj = 16;
constexpr s32 kInstance = 20;                 // a PS2All object pipe
}  // namespace ptankpipes

}  // namespace rw8

// --- the bodies (register ABI: arguments in $a0.., $f12.., the result in $v0 / $f0) ---------------------------------
void sub_45EC20(EEContext& ctx);  // 0x45EC20 -- a float compare: 1 when the libgcc compare (dpcmp) of its operands is positive, else 0
void sub_45F580(EEContext& ctx);  // 0x45F580 [plg11DStreamWrite] -- plugin 0x11D's stream write: when the object's extension word is set, a 4-byte header (sub_4CA510) and the extension's body (sub_45EE00)
void sub_45F7D0(EEContext& ctx);  // 0x45F7D0 [plg11DPluginAttach] -- registers plugin 0x11D: the engine extension, the clump extension, the world-sector and atomic extensions with their stream callbacks
void sub_46A600(EEContext& ctx);  // 0x46A600 [pdsEngineOpen] -- the PDS plugin's engine open: on the first open every registered pipe is built (sub_46AC30 on the registry 0x95C44C); the open count up; $a0
void RpPDSRegisterPipe(EEContext& ctx);  // 0x46A830 -- registers a PDS pipe definition: the registry set up with its requested size when it has none (sub_46A970), then PDSRegistryAddPipe; $a0
void sub_46A8D0(EEContext& ctx);  // 0x46A8D0 [pdsObjPipeCreate] -- builds a type-2 (object) registry entry's pipe: its definition's material pipe set from the entry naming the aux id (0 for none), then sub_46AFA0; the pipe's plugin data = the entry's id
void PDSRegistryAddPipe(EEContext& ctx);  // 0x46AA80 -- adds a definition to the PDS registry: refused (error 0x131 / 2) when its id is there; the entries doubled (RwRealloc) when full; in a built registry the pipe is made at once
void sub_46AC30(EEContext& ctx);  // 0x46AC30 [pdsRegistryBuildPipes] -- builds every registry entry's pipe: first the type-1 (material) pipes through RpPDSSkyMatPipeCreate (plugin data = the id), then every entry through sub_46A8D0; marks the registry built (+12 = 1)
void RpPDSSkyMatPipeCreate(EEContext& ctx);  // 0x46AD80 -- builds a PS2AllMat material pipeline from a 132-byte PDS definition: create, lock, the PS2AllMat node, its clusters, the batch set-up of the primitive type, unlock, then the VIF offset, VU1 code array and five callbacks
void sub_46AFA0(EEContext& ctx);  // 0x46AFA0 [pdsObjPipeCreateFromDef] -- builds a PS2All object pipeline from a 20-byte PDS definition: create, lock, the PS2All node, unlock, then its two callbacks and its material pipeline
void sub_474BB0(EEContext& ctx);  // 0x474BB0 [ptankEngineOpen] -- PTank's engine open: a 24-byte record of six pipelines (RwMalloc) at engine + gp 0x7CE774, filled by the 3D and 2D sprite pipe builders, the tank pipe (+0) and the instancing pipe (+20); $a0, or 0
void sub_474C60(EEContext& ctx);  // 0x474C60 [ptankEngineClose] -- PTank's engine close: each of the six pipelines destroyed (RxPipelineDestroy) and the record freed; $a0
void rpSpr2dGenCreatePS2AllMatPipe(EEContext& ctx);  // 0x478A70 -- builds the 2D sprite PS2AllMat pipeline: the PS2AllMat node with four sprite clusters (their definitions refreshed from the static templates), point batches, the sprite VU1 code and callbacks
void sub_479030(EEContext& ctx);  // 0x479030 [ptankSpr2dPipesCreate] -- builds PTank's 2D sprite pipes: the PS2AllMat pipe (+4) and its PS2All object pipe (+8: callback 1 sub_478CC0, the material pipe); 1 when the object pipe was made
void rpSpr3dGenCreatePS2AllMatPipe(EEContext& ctx);  // 0x479E50 -- builds the 3D sprite PS2AllMat pipeline: as the 2D one with the 3D sprite clusters (0x95D3E0..0x95D400) and VU1 code
void sub_47A3D0(EEContext& ctx);  // 0x47A3D0 [ptankSpr3dPipesCreate] -- builds PTank's 3D sprite pipes: the PS2AllMat pipe (+12) and its PS2All object pipe (+16: callback 1 sub_47A050, the material pipe); 1 when the object pipe was made
void sub_47AB70(EEContext& ctx);  // 0x47AB70 [ptankTankPipeCreate] -- builds the tank pipeline: create, lock, the PS2PTank node fragment, unlock; the pipeline (stored at +0)
void sub_47B1A0(EEContext& ctx);  // 0x47B1A0 [ptankInstancePipeCreate] -- builds PTank's instancing pipeline: a PS2All object pipe with callback 1 sub_47ABF0; the pipeline (stored at +20), or 0
void sub_48F030(EEContext& ctx);  // 0x48F030 [rpUserDataPluginAttach] -- registers RpUserData (plugin 0x11F): the engine open / close and the 8-byte user-data list with its stream callbacks on nine object types
void sub_48F580(EEContext& ctx);  // 0x48F580 [worldSectorStreamRead] -- reads an atomic world sector (chunk 9, versions 0x35000..0x37002): the 44-byte header, the sector's bounding box and counts, its vertices / normals / UVs / triangles, the collision and plugin data
void sub_48FBD0(EEContext& ctx);  // 0x48FBD0 [worldPlaneStreamRead] -- reads a plane sector (chunk 10) and its two children, recursively: plane sectors through itself, atomic sectors through sub_48F580
void sub_499A80(EEContext& ctx);  // 0x499A80 [worldEngineClose] -- the world module's engine close: its 16-byte free list destroyed, the default pipelines released (sub_49C680), the open count down; $a0
void sub_499AF0(EEContext& ctx);  // 0x499AF0 [worldEngineOpen] -- the world module's engine open: the default pipelines (sub_49C6C0), then a 16-byte free list (8 per block) whose record links to itself; $a0, or 0
void sub_49C680(EEContext& ctx);  // 0x49C680 [worldDefaultPipesDestroy] -- releases the default pipelines: the Im3D ones (sub_49C9B0) and the default material / world-sector / atomic pipes (sub_4A5290, sub_4A5320, sub_4A5200)
void sub_49C6C0(EEContext& ctx);  // 0x49C6C0 [worldDefaultPipesCreate] -- creates the default pipelines: the pipeline module's defaults cleared (+60..+92), then the atomic, world-sector, material and Im3D pipes; on a failure all released; 1 / 0
void sub_49C810(EEContext& ctx);  // 0x49C810 [im3dTransformPipeCreate] -- builds the Im3D transform pipeline ('FastIm3DTransform'): create (plugin id 1), lock, the node fragment 0x77DE10, unlock; on a failure destroyed and error 0x80000006
void sub_49C8C0(EEContext& ctx);  // 0x49C8C0 [im3dPipesCreate] -- sets the Im3D module's pipelines: the transform pipe (sub_49C810) and the render pipes the PDS registry holds for ids 4..7, each made the current pipe of its primitive types; 1
void sub_49C9B0(EEContext& ctx);  // 0x49C9B0 [im3dPipesDestroy] -- clears the Im3D module's pipelines: the current pipes of every primitive type reset, the module's pointers cleared, the transform pipe destroyed
void sub_4A30D0(EEContext& ctx);  // 0x4A30D0 [ps2AllMatNodeClusterLayout] -- lays out a PS2AllMat node's clusters from its initialisation data: per cluster its attributes and VIF unpack width; refuses illegal attribute combinations with a message
void PS2AllMatPipelineNodeInit(EEContext& ctx);  // 0x4A3540 -- the PS2AllMat node's pipeline-node init: no callbacks, VIF offset 0x114 (276), the default VU1 code array (0x77F130, 32 entries), then the cluster layout (sub_4A30D0)
void sub_4A9A80(EEContext& ctx);  // 0x4A9A80 [rt2dFontFindOrRead] -- finds a font in the font dictionary by name (strcmp slot), else reads it through the font read callback and adds it (a 12-byte dictionary entry); the font, or 0
void sub_4AC240(EEContext& ctx);  // 0x4AC240 [rt2dObjectListCompact] -- walks an object list (the next pointer at +20), recursing every fourth level, and replaces each single-entry sList (count 1) by its entry (sub_4AB0E0); the list
void sub_4AC410(EEContext& ctx);  // 0x4AC410 [rt2dObjectListClear] -- clears an object list's string slots: an sList-backed slot (+4 == -1) destroyed, an allocated one freed, both zeroed; recursing down the list (+20)
void sub_4AC710(EEContext& ctx);  // 0x4AC710 [rt2dObjectListFlatten] -- turns an object list's sList-backed slots (+4 == -1) into plain arrays (sub_4C2130) with their counts, down the list (+20, recursing every fourth record) while the slots are sList-backed
void sub_4AD480(EEContext& ctx);  // 0x4AD480 [rt2dTextSetString] -- copies a text object's string: two-byte codes up to a 0 pair for a unicode font, else strlen + 1 bytes, into a new block (RwMalloc); its byte length at +8; 1 / 0
void sub_4AD5B0(EEContext& ctx);  // 0x4AD5B0 [rt2dTextObjectInit] -- initialises a text object: height 1.0, a fresh brush (Rt2dBrushCreate), the font by name (sub_4AD700; a missing font sets error 400 and flag 0x1000000), the string
void sub_4AD700(EEContext& ctx);  // 0x4AD700 [rt2dTextSetFont] -- sets a text object's font (+192) to the font of that name (sub_4A9A80); the object, or 0 when none
void sub_4AD940(EEContext& ctx);  // 0x4AD940 [rt2dTextObjectStreamRead] -- reads a text object: the font name and string lengths and bytes, the height, then the object set up (sub_4AD5B0) and its brush read (Rt2dBrushStreamRead)
void sub_4ADC90(EEContext& ctx);  // 0x4ADC90 [rt2dObjectCopyHeader] -- copies a 272-byte Rt2d object (memcpy, a tail call)
void sub_4ADCC0(EEContext& ctx);  // 0x4ADCC0 [rt2dObjectInit] -- initialises an Rt2d object record: the type, the id 666, two identity matrices, flags |= 0x20003, cleared colour and depth
void sub_4AE150(EEContext& ctx);  // 0x4AE150 [rt2dObjectSetColorMult] -- sets an object's colour multiplier: the four floats x 255 at +160, flag bit 3 (changed); the object
void sub_4B0B10(EEContext& ctx);  // 0x4B0B10 [rt2dTriangulateRun] -- triangulates a closed outline by ear clipping: a three-vertex outline is one triangle; else each ear found (sub_4B0430) is cut off, its three indices appended, recursing on the rest
void sub_4B0FA0(EEContext& ctx);  // 0x4B0FA0 [rt2dPathTriangulate] -- triangulates a path's outline (sub_4B0DF0 builds it) into the index buffer $a2: the triangle count to *$a1; the outline freed; $a0
void sub_4B1420(EEContext& ctx);  // 0x4B1420 [rt2dKeyFrameListReset] -- rewinds a keyframe list: time 0, the first and last entries of its sList, the first entry's changes applied to the props ($a1); $a0
void sub_4B14C0(EEContext& ctx);  // 0x4B14C0 [rt2dAnimAddDeltaTime] -- advances an animation by $f12 x its speed (+4, + its offset +8): the new time through sub_4B1700; $a0
void sub_4B1500(EEContext& ctx);  // 0x4B1500 [rt2dKeyFrameListStep] -- steps a keyframe list $a2 entries forwards (positive) or backwards (negative), applying each entry's changes to the props; the list's current / next entry pointers updated; $a0
void sub_4B1700(EEContext& ctx);  // 0x4B1700 [rt2dAnimSetTime] -- moves an animation to time $f12: steps through the keyframes in the direction of the change, wrapping at the ends when looping (the 1.0 / 0.0 bounds), each crossed keyframe applied; $a0
void sub_4B1870(EEContext& ctx);  // 0x4B1870 [rt2dKeyFrameListGotoIndex] -- moves a keyframe list to entry $a2: rewinds when the target lies before the current one, then steps forwards to it; $a0
void sub_4B1D00(EEContext& ctx);  // 0x4B1D00 [rt2dAnimStreamReadBody] -- reads an animation's keyframes: the header (count, duration), per keyframe its time and changed props (matrix, colour, colour offset, the object, a string), into 160-byte records; 1 / 0
void sub_4B22B0(EEContext& ctx);  // 0x4B22B0 [rt2dAnimStreamRead] -- reads an animation: a record from the animation free list (0x95FB4C), filled by sub_4B1D00
void sub_4B2300(EEContext& ctx);  // 0x4B2300 [rt2dKeyFrameApply] -- applies one keyframe's changes to the props: for each change record (until flag 0x20) the object's matrix (64 bytes, flag 1), colour (flag 2), colour offset (flag 4), visibility / string (flags 8 / 16), each marked changed
void sub_4B2BF0(EEContext& ctx);  // 0x4B2BF0 [rt2dSListAddCopy] -- appends an entry to an sList (sub_4C1F70) and copies $a2 bytes into it when $a1 is given; the entry's index, or -1
void sub_4B2C80(EEContext& ctx);  // 0x4B2C80 [rt2dAnimPropsStreamRead] -- reads an animation's props: a 16-byte props record (from the free list when $a1 is 0), the label count and each label string into the scene's string sList; the props, or 0
void sub_4B4450(EEContext& ctx);  // 0x4B4450 [rt2dMaestroAnimReset] -- resets a maestro animation: its scene object (when the animation names one), each of its keyframe lists rewound and stepped once
void sub_4B5270(EEContext& ctx);  // 0x4B5270 [rt2dMaestroGetSceneObject] -- the maestro's scene object of animation $a1: the parent chain followed recursively through the animations' parent (+52) and child index (+56); the root's +36 for none
void sub_4B5380(EEContext& ctx);  // 0x4B5380 [rt2dMaestroUpdate] -- updates every animation of a maestro: per animation its scene object, its time stepped and each crossed keyframe applied; button transitions queued
void sub_4B56D0(EEContext& ctx);  // 0x4B56D0 [rt2dMaestroUpdateButtons] -- updates a maestro's buttons against the pointer message $a1: each button's state from its hot region and the message, transitions queued
void sub_4B5B50(EEContext& ctx);  // 0x4B5B50 [rt2dMaestroMessageHandler] -- the maestro's default message handler: play / stop (flag bit 0), goto frame / label (keyframe list moved), buttons, by the message type (a jump table)
void sub_4B9840(EEContext& ctx);  // 0x4B9840 [bmpPaletteSize] -- the palette size of a BMP of $a0 bits per pixel: 4 x 2^bpp below 9, else 0
void sub_4B9870(EEContext& ctx);  // 0x4B9870 [bmpWriteFileHeader] -- writes a BMP file header: 'BM', the file size (54 + palette + rows padded to 32 bits), two reserved words, the bits' offset
void sub_4B99A0(EEContext& ctx);  // 0x4B99A0 [bmpWriteInfoHeader] -- writes a BMP info header (40 bytes: width, height, 1 plane, the bit count, no compression) and the image's palette
void sub_4B9BA0(EEContext& ctx);  // 0x4B9BA0 [bmpWriteRow] -- writes one image row bottom-up into a BMP row: 4-bit pixels packed in pairs, 8-bit copied, 32-bit as BGR, padded to 32 bits; the bytes written
void sub_4B9D40(EEContext& ctx);  // 0x4B9D40 [bmpWritePixels] -- writes an image's rows to a BMP from the last to the first (sub_4B9BA0) through a row buffer; the total bytes
void sub_4B9E00(EEContext& ctx);  // 0x4B9E00 [bmpReadRow] -- converts one BMP row into an image row by (image depth, BMP bit count): 32-bit RGBA from 24 / 32-bit BGR(A), palette indices from 1 / 4 / 8-bit; unknown pairs error
void sub_4BA2A0(EEContext& ctx);  // 0x4BA2A0 [bmpImageRead] -- reads a BMP file into a new image: the file stream opened, the 'BM' header and info header checked, the palette, the rows (sub_4B9E00) bottom-up; the image, or 0
void sub_4BAD50(EEContext& ctx);  // 0x4BAD50 [bmpImageWrite] -- writes an image as a BMP file: the file stream opened (sub_4C58A0), the headers and pixels, closed; the image, or 0
void sub_4BC830(EEContext& ctx);  // 0x4BC830 [mipKLTriangleArea] -- accumulates a triangle's texel density: its screen area (cross product) against its texture's texel count, summed into the pass record
void sub_4BCA00(EEContext& ctx);  // 0x4BCA00 [mipKLSectorTriangles] -- visits a world sector's triangles: those whose material passes the pass's filter add their density (sub_4BC830); the sector
void sub_4BCAE0(EEContext& ctx);  // 0x4BCAE0 [mipKLSectorCallBack] -- the sector callback of the K / L pass: the material filter set (sub_4BCB20), the sector's triangles visited
void sub_4BCB20(EEContext& ctx);  // 0x4BCB20 [mipKLMatchTexture] -- 1 when the material's texture is the one the pass looks at
void sub_4BCB30(EEContext& ctx);  // 0x4BCB30 [mipKLTextureCallBack] -- the texture callback of the K / L pass: every world sector visited for the texture; with any density the texture's K value set from its logarithm (sub_4D8320)
void sub_4BCBF0(EEContext& ctx);  // 0x4BCBF0 [RpMipmapKLWorldCalculate] -- computes the mipmap K / L values of a world's textures: for mipmapped rasters (flags 0x84) every texture of the current dictionary visited (sub_4BCB30)
void sub_4BDB30(EEContext& ctx);  // 0x4BDB30 [quatFromMatrixX] -- the matrix-to-quaternion case of a dominant x diagonal: x = sqrt(1 + xx - yy - zz) / 2, the other components from the off-diagonals
void sub_4BDBB0(EEContext& ctx);  // 0x4BDBB0 [quatFromMatrixY] -- the matrix-to-quaternion case of a dominant y diagonal
void sub_4BDC30(EEContext& ctx);  // 0x4BDC30 [quatFromMatrixZ] -- the matrix-to-quaternion case of a dominant z diagonal
void sub_4BDCB0(EEContext& ctx);  // 0x4BDCB0 [RtQuatConvertFromMatrix] -- converts a rotation matrix to a quaternion: a positive trace directly (w = sqrt(trace + 1) / 2), else the case of the largest diagonal element (sub_4BDB30 / sub_4BDBB0 / sub_4BDC30)
void sub_4BDDE0(EEContext& ctx);  // 0x4BDDE0 [RtQuatRotate] -- rotates a quaternion by $f12 degrees about an axis: the axis quaternion (sin / cos of the half angle, the axis normalised) replaces, pre- or post-multiplies it by the combine type
void sub_4BE1E0(EEContext& ctx);  // 0x4BE1E0 [RtQuatTransformVectors] -- rotates $a2 vectors by a unit quaternion: v' = v (w^2 - |q|^2) + 2 (q.v) q + 2 w (q x v), from $a1 into $a0
void sub_4BE310(EEContext& ctx);  // 0x4BE310 [RtQuatSetupSlerpCache] -- sets up a slerp cache: the start quaternion (+0), the end one (+16, negated when the dot product is negative), the angle (+32, acos of |dot| by polynomial), the 'nearly equal' flag (+36)
void sub_4BE930(EEContext& ctx);  // 0x4BE930 [rasImageWriteOpen] -- opens a Sun raster image file for writing: the 32-byte big-endian header (magic 0x59A66A95, width, height, 24 bits), the record's sizes and a cleared band buffer
void sub_4D1900(EEContext& ctx);  // 0x4D1900 [imageAlphaClass] -- classifies a palettised image's alpha through its palette: 1 opaque (every alpha >= 0xF0), 2 only transparent / opaque alphas, 3 translucent (an alpha in 0x10..0xEF); 2 for other depths
void sub_4D1A50(EEContext& ctx);  // 0x4D1A50 [quantAddPixel] -- adds one RGBA pixel (its low bits dropped by the quantiser's depth) to a node's statistics: the count, the weighted channel sums (luminance weights 0.509 / 0.194 ..) and the squared sum
void sub_4D1C30(EEContext& ctx);  // 0x4D1C30 [quantNodeFinish] -- finishes a leaf's statistics: its variance term from the sums
void sub_4D1DF0(EEContext& ctx);  // 0x4D1DF0 [quantNodeAdd] -- adds two nodes' statistics into $a0: counts, channel sums and the variance terms combined
void sub_4D1F10(EEContext& ctx);  // 0x4D1F10 [quantNodeSubtract] -- subtracts one node's sums from another's (the remainder's mean recomputed)
void sub_4D2030(EEContext& ctx);  // 0x4D2030 [quantNodeToColor] -- converts a node's mean back to an RGBA palette colour (each channel x 255.99, the luminance weights undone)
void sub_4D2130(EEContext& ctx);  // 0x4D2130 [quantTreeInsert] -- inserts a pixel into the 16-way colour tree (one bit of each of the four channels per level): the child by the pixel's bits, allocated from the 92-byte node free list, recursively
void sub_4D22F0(EEContext& ctx);  // 0x4D22F0 [quantAddImage] -- adds an image's pixels to the colour tree (sub_4D2130 with the pixel statistics sub_4D1A50), 32-bit pixels directly, palettised ones through their palette
void sub_4D2730(EEContext& ctx);  // 0x4D2730 [quantBoxAssign] -- gives the tree's nodes inside a colour box the box's palette index, recursively
void sub_4D2900(EEContext& ctx);  // 0x4D2900 [quantBoxSum] -- sums the statistics of the tree's nodes inside a colour box, recursively (sub_4D1DF0)
void sub_4D2B50(EEContext& ctx);  // 0x4D2B50 [quantSplitError] -- the error of splitting a box at a plane: both halves' sums (sub_4D2900 / sub_4D1F10) and their weighted variance
void sub_4D2D60(EEContext& ctx);  // 0x4D2D60 [quantBestSplit] -- finds a box's best split over the four axes (sub_4D2B50), the axis and position stored
void sub_4D2ED0(EEContext& ctx);  // 0x4D2ED0 [quantTreeSum] -- rebuilds a node's statistics from its 16 children to a depth, recursively (leaves finished by sub_4D1C30)
void sub_4D3040(EEContext& ctx);  // 0x4D3040 [quantTreeCount] -- counts the nodes present at a depth below a node, recursively
void sub_4D3120(EEContext& ctx);  // 0x4D3120 [quantTreeColors] -- writes palette colours for the tree's nodes at a depth (sub_4D2030), each node's index stored, recursively
void sub_4D3220(EEContext& ctx);  // 0x4D3220 [quantTreeLookup] -- the palette index of a pixel: down the tree by the pixel's bits ($a1, four per level) to the depth; the node's index
void sub_4D3300(EEContext& ctx);  // 0x4D3300 [quantMakePalette] -- builds the palette: the tree's statistics summed (sub_4D2ED0); with few enough nodes each gets an entry (sub_4D3120), else colour boxes are split at their best plane (sub_4D2D60) until the palette is full and assigned (sub_4D2730)
void sub_4D3800(EEContext& ctx);  // 0x4D3800 [quantMatchImage] -- converts an image to palette indices: each pixel's index looked up (sub_4D3220), packed for 4 or 8-bit rasters
void sub_4D3FC0(EEContext& ctx);  // 0x4D3FC0 [quantInit] -- initialises the quantiser: the bit-spreading table (2^depth 64-bit masks at 0x964190), the 92-byte node free list, the root with 16 empty children
void sub_4D40E0(EEContext& ctx);  // 0x4D40E0 [quantTreeFree] -- returns a node's children to the node free list, recursively
void sub_4D41E0(EEContext& ctx);  // 0x4D41E0 [quantTerm] -- releases the quantiser: the tree's nodes freed (sub_4D40E0), the node free list destroyed
void sub_4D8320(EEContext& ctx);  // 0x4D8320 [RpSkyTextureSetMipmapK] -- sets a texture's mipmap K: $f12 x 16 clamped to -2048..2047, stored in its raster's extension; the texture, or 0
void sub_4F22B0(EEContext& ctx);  // 0x4F22B0 [RwIm3DRenderLine] -- renders one line of the transformed Im3D vertices: two u16 indices from the global RxHeap, the Im3D line pipe executed; 1, or 0 (error 35 when nothing is transformed)
void sub_4F2730(EEContext& ctx);  // 0x4F2730 [im3dEngineClose] -- the Im3D module's engine close: two empty hooks, the open count down; $a0
void sub_4F2790(EEContext& ctx);  // 0x4F2790 [im3dEngineOpen] -- the Im3D module's engine open: the module offset / address stored, the module cleared, two hooks that always succeed; $a0
void sub_4F2870(EEContext& ctx);  // 0x4F2870 [rxPipelineModuleOpen] -- the pipeline module's engine open: its offset (gp 0x7CEB28) stored, the module set up (sub_4F2A00); $a0, or 0
void sub_4F28A0(EEContext& ctx);  // 0x4F28A0 [rxPipelineModuleClose] -- the pipeline module's engine close: the module torn down (sub_4F2990); $a0
void sub_4F28D0(EEContext& ctx);  // 0x4F28D0 -- a hook that always succeeds (1)
void sub_4F28F0(EEContext& ctx);  // 0x4F28F0 [rxPacketReleaseClusters] -- releases a packet's clusters: each slot (28 bytes) with data and no 'external' flag frees it from the global RxHeap; the slots cleared, the packet's count 0
void sub_4F2990(EEContext& ctx);  // 0x4F2990 [rxPipelineModuleTerm] -- tears the pipeline module down when it is open: the 52-byte pipeline free list destroyed, the global RxHeap destroyed, the flag cleared; 1
void sub_4F2A00(EEContext& ctx);  // 0x4F2A00 [rxPipelineModuleInit] -- sets the pipeline module up: the global RxHeap (its initial size 0x7CDDF0), the 52-byte pipeline free list, the node limit (64), the default render-state vector (sub_4F6B50)
void sub_4F2F70(EEContext& ctx);  // 0x4F2F70 [RxPipelineCreate] -- creates a pipeline: a cleared 52-byte record from the pipeline free list; the pipeline, or error 0x80000013 (out of memory) and 0
void sub_4F30E0(EEContext& ctx);  // 0x4F30E0 [rxUnlockScratchAlloc] -- takes $a0 bytes (rounded to 4) from the top of the unlock's scratch area, which grows downwards; the block, or error 0x80000013 (out of memory) and 0 when it would pass the bottom
void sub_4F31C0(EEContext& ctx);  // 0x4F31C0 [rxPipelineCountClusters] -- counts the distinct cluster definitions among a pipeline's nodes' clusters of interest (repeatedly the next larger address); the count
void sub_4F3260(EEContext& ctx);  // 0x4F3260 [rxPipelineResizeSuperBlock] -- resizes a pipeline's super block (RwRealloc) to $a1 bytes and relocates every pointer into it: the nodes, the packet, the input requirements and each node's five pointer fields
void sub_4F3410(EEContext& ctx);  // 0x4F3410 [rxPipelineCopyNodes] -- copies pipeline $a1's nodes into pipeline $a0's super-block layout (nodes from the top, each node's outputs in its 128-byte slot), initialisation data duplicated; for $a0 == $a1 only the outputs are re-laid out
void sub_4F3680(EEContext& ctx);  // 0x4F3680 [rxPipelineNodeSetup] -- sets up a locked pipeline's next node record from a definition: refuses more than 32 outputs (41) or clusters (40) or a full pipeline (42); outputs all unconnected, a cleared sort record; the count up
void sub_4F3880(EEContext& ctx);  // 0x4F3880 [rxTopSortCountInputs] -- the topological sort's start: each node's sort record cleared, then each connected output adds one to its target's in-degree
void sub_4F3970(EEContext& ctx);  // 0x4F3970 [rxTopSortPlace] -- places a node at the next sorted position: swaps it there (node record, outputs, sort record, every output index renumbered), then each target whose inputs are now all placed follows, recursively
void sub_4F3D60(EEContext& ctx);  // 0x4F3D60 [rxPipelineTopSort] -- sorts a pipeline's nodes topologically from its entry point: in-degrees (sub_4F3880), the entry must have none (error 36), then the placement (sub_4F3970); the pipeline, or 0 when a node is unreachable (a cycle)
void sub_4F3F80(EEContext& ctx);  // 0x4F3F80 [RxLockedPipeUnlock] -- unlocks a locked pipeline: sizes the super block, sorts the nodes (sub_4F3D60), lays out outputs and sort records, runs the cluster passes (sub_4F6140), shrinks the block, then each node's init / pipeline-node init / config
void sub_4F4640(EEContext& ctx);  // 0x4F4640 [RxPipelineLock] -- locks a pipeline for editing: a super block of 180 x the node limit (RwMalloc, or grown), the nodes copied into its layout, each node's pipeline-node term and (at its last use) node term run
void sub_4F4830(EEContext& ctx);  // 0x4F4830 [RxPipelineFindNodeByName] -- finds a pipeline's node by its definition's name (strcmp slot), from the node after $a2 (the first when 0); its index to *$a3
void sub_4F4950(EEContext& ctx);  // 0x4F4950 [RxLockedPipeAddFragment] -- adds a chain of nodes to a locked pipeline: the definitions from $a2 on (a NULL-terminated list), each node set up (sub_4F3680) and connected from the previous node's output 0 (sub_4F4C30)
void sub_4F4C30(EEContext& ctx);  // 0x4F4C30 [RxLockedPipeAddPath] -- connects an output slot (*$a1, which must be -1) of a locked pipeline to node $a2: the node's index stored; the pipeline, or 0 when unlocked, connected or not a node of it
void sub_4F4CF0(EEContext& ctx);  // 0x4F4CF0 [rxReqListAdd] -- adds a cluster to a node's requirement list (36-byte entries): an existing entry made required when $a2 is 1; else appended with its flags, creator and slot -1; the entry
void sub_4F4DB0(EEContext& ctx);  // 0x4F4DB0 [rxReqListRemove] -- drops a cluster from a node's requirement list (its reference count down; at 0 the last entry moved into its place) and, for each output that does not keep the cluster, from the target node, recursively
void sub_4F4FE0(EEContext& ctx);  // 0x4F4FE0 [rxSlotMerge] -- merges two cluster-slot chains: both followed to their roots; when different, the second is appended to the first and taken out of the free chain $a0
void sub_4F50A0(EEContext& ctx);  // 0x4F50A0 [rxPipelineBuildRequirements] -- the requirement pass, last node first: per node a requirement list (cluster count from sub_4F31C0, scratch-allocated), filled from its outputs' targets and its own clusters of interest
void sub_4F5520(EEContext& ctx);  // 0x4F5520 [rxPipelinePropagateRequirements] -- the propagation pass, first node first: each node's clusters and each output's surviving clusters marked in the targets' lists (bit per output); 0, or 32
void sub_4F57F0(EEContext& ctx);  // 0x4F57F0 [rxPipelineAllocSlots] -- the slot pass: each requirement entry gets a slot record (16 bytes, scratch-allocated) unless it already has one; entries carried along an output share their source's slot (merged when both have one)
void sub_4F5A90(EEContext& ctx);  // 0x4F5A90 [rxPipelineCountSlots] -- numbers the slot chains: the bits used along each chain, the first free bit index as its slot; the highest + 1 is the pipeline's slot count
void sub_4F5B80(EEContext& ctx);  // 0x4F5B80 [rxSlotSortKeys] -- fills the slot sort records: per slot its key (the first node using it) and the chain
void sub_4F5C50(EEContext& ctx);  // 0x4F5C50 [rxSlotSort] -- sorts the slot records by key (sub_4F7080) and renumbers them in that order
void sub_4F5D90(EEContext& ctx);  // 0x4F5D90 [rxPipelineAssignSlots] -- the assignment pass: slots sorted (sub_4F5B80, sub_4F5C50), then each node's input-to-slot map and slot cluster refs written into the super block
void sub_4F6140(EEContext& ctx);  // 0x4F6140 [rxPipelineClusterPasses] -- runs the unlock's cluster passes in order: requirements, propagation, slot allocation, slot count, assignment; the first error, or 0
void sub_4F63D0(EEContext& ctx);  // 0x4F63D0 [rxHeapGrow] -- grows an RxHeap by a super block of max(size + 96, the heap's block size) (RwMalloc, 128-aligned start), its first free block made; 'Heap resized from %d to %d bytes'; the block's free header, or 0
void sub_4F64F0(EEContext& ctx);  // 0x4F64F0 [rxHeapSplit] -- allocates $a2 bytes from a free block: split when 256 or more bytes remain (the rest stays free in the same entry), else the whole block taken and its free entry removed; the user pointer (header + 32)
void sub_4F65B0(EEContext& ctx);  // 0x4F65B0 [RxHeapFree] -- frees an RxHeap block: merged with a free previous and / or next block (their entries removed or reused), else given a new free entry
void sub_4F67B0(EEContext& ctx);  // 0x4F67B0 [RxHeapAlloc] -- allocates from an RxHeap: the size rounded to 32, the free entries searched from the last, the heap grown when none fits (sub_4F63D0); the heap marked dirty; the block, or error 0x80000013 (out of memory) and 0
void sub_4F6970(EEContext& ctx);  // 0x4F6970 [RxHeapDestroy] -- destroys an RxHeap: the free-entry array, every super block, the record (RwFree)
void sub_4F6A10(EEContext& ctx);  // 0x4F6A10 [RxHeapCreate] -- creates an RxHeap of at least 1,024 bytes: the 28-byte record and its first super block (size rounded to 32, a 128-aligned start), the free entries set up (sub_4F6890); the heap, or 0
void sub_4F6B50(EEContext& ctx);  // 0x4F6B50 [RxRenderStateVectorSetDefaultRenderStateVector] -- fills a render-state vector with the defaults: flags 7, gouraud shading, blend src 5 / dest 6, no raster, wrap addressing, linear filter, the border / fog colours
void sub_4F6CE0(EEContext& ctx);  // 0x4F6CE0 [rxRadixSortPass] -- the radix pass of the slot sort: an explicit-stack partition of the records by the key's bits, highest bit first, down to runs of five
void sub_4F6F20(EEContext& ctx);  // 0x4F6F20 [rxInsertionSortPass] -- the insertion pass of the slot sort: records of stride $a2 ordered by the int key at $a3
void sub_4F7080(EEContext& ctx);  // 0x4F7080 [rxSortRecords] -- sorts $a1 records of stride $a2 by the int key at offset $a3 (keys in [$t0, $t1)): the radix pass for six or more, the smallest of the first five moved first, then the insertion pass
void sub_4F72C0(EEContext& ctx);  // 0x4F72C0 -- an empty hook
void sub_4F72D0(EEContext& ctx);  // 0x4F72D0 -- a hook that always succeeds (1)
void sub_4F72E0(EEContext& ctx);  // 0x4F72E0 -- an empty hook
void sub_4F72F0(EEContext& ctx);  // 0x4F72F0 -- a hook that always succeeds (1)

}  // namespace p3fes::game
