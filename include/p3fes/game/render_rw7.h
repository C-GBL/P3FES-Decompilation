// Slice render_rw7: RenderWare, seventh pass -- the plugins render_rw6 left: RpMatFX's plugin (the material / atomic /
// world-sector extensions, their streams and the effect getters / setters), RpMorph, the PDS registry, RpRandom,
// RpSpline, RpUserData, the PS2 pipeline-id streams of atomics and sectors, the bin-mesh and native-data streams, the
// tri-strip builder's edge records, the PTank plugin's data layout and its PS2All object set-ups, the light / material
// stream readers, RxPipelineDestroy, and Rt2d's brush and font layer: 170 functions of the RW band 0x4643B0-0x4F3010,
// started from p3fes_handgen and made readable (game/src/render/render_rw7.cpp).
//
// Groups (sub_* keep their symbols/functions.json names; proposed names in brackets, symbols/deltas/render_rw7.sym):
//   * The plugin-0x122 loader (0x4643B0, 0x464540): the chunk reader the resource manager's thread calls (a 4-word
//     header, per entry its 20-byte records of four reals and a word).
//   * RpMatFX (0x467590-0x469CF0, plugin 0x120): the engine open / close (a 144-byte free list), the 132-byte material
//     extension (two 64-byte effect slots, the effect flags at +128: 1 bump map, 2 environment map, 3 bump + environment,
//     4 dual pass, 5 UV transform, 6 dual + UV transform), its reset / destructor, stream write / size, the atomic and
//     world-sector "effects enabled" words and their streams, the plugin registration, the slot getters / setters of each effect
//     (bump: frame, texture, coefficient; environment: frame, texture, coefficient, frame-buffer alpha; dual: texture,
//     blend modes; UV: the two matrices) and the slots' GS words (ALPHA from the dual blend modes, the bump / environment
//     passes).
//   * RpMorph (0x469DD0-0x46A530, plugin 0x105): the atomic's 12-byte interpolation state and the geometry's
//     interpolation keys (20 bytes each: type, start / end morph target, duration, next key), their copy and streams,
//     RpMorphGeometryCreateInterpolators, the default key-end callback (go to the next key), the registration.
//   * PDS (0x46A660-0x46A9E0, plugin 0x131): the pipe registry's set-up (20-byte entries, 9 by default) and destroy
//     (RxPipelineDestroy 0x4F3010 on each pipe, the node destroy 0x4F2AD0), the engine close, and the registration with
//     the material / atomic / world-sector rights callbacks that set an object's pipeline from the PDS id read with it
//     (RpPDSGetPipe).
//   * PTank (0x4734B0-0x47ABF0, plugin 0x12F): the atomic extension (the tank data), the plugin registration, the data
//     allocation by format flags (structure of arrays sub_473600 / array of structures sub_473B10 / the size
//     sub_4753D0), the pipeline record's creation (sub_475540), the buffer-ring step, the instance-buffer release, and
//     the three PS2All object set-up callbacks of the tank pipelines (sub_478CC0, sub_47A050, sub_47ABF0: transform,
//     frustum clip flag, and for the lit pipe the instance flags and the lights).
//   * RpRandom (0x488C70-0x488FE0, plugin 0x10C): the generator every game system draws from (below).
//   * RpSpline (0x48AD20-0x48DCF0, plugin 0x102): the basis tables (12 x 257 floats) and the open splines' end
//     matrices (4..10 points), the control-point solve (the interpolating cubic: the user's points through the
//     tridiagonal system to the B-spline points at +56), RpSplineSetControlPoint, RpSplineFindPosition (paths 10 smooth /
//     11 nice ends), the open, close and registration.
//   * RpUserData (0x48DD30-0x48EFE0, plugin 0x11F): user data arrays (16 bytes: name, format 1 int / 2 real / 3 string,
//     count, data), the per-object list of arrays (count, array of arrays) with its constructor / destructor / copy /
//     stream read / write / size, adding an array, the array getters / setters, the format size.
//   * RpLightStreamRead / RpMaterialStreamRead (0x494580, 0x494E30).
//   * PS2 pipeline-id streams (0x48F340-0x48F550, plugin 0x1F): the atomic's (pipeline at +108) and the world sector's
//     (pipeline at +124) stream read (the id pair held for the rights callback), write and size.
//   * The world's streams and helpers (0x495FB0-0x49F500): the bin-mesh header stream write / read / size for
//     geometries (+84) and world sectors (+120, through the world's flags), the mesh-header serial number, the tri-strip
//     builder's edge / triangle records, the BSP teardown walks, the world-plugin registrations (0x501..0x50E), the
//     native-data sizes and the DMA-chain relocation of native data (addresses <-> qword offsets), a PS2All node's
//     private-data init, the PS2All node's callback setter and its node definition (sceLibgcc32GetErxEntries).
//   * Rt2d brushes and fonts (0x4A5470-0x4A9BE0): Rt2dBrushCreate, the brush colours (Rt2dBrushSetRGBA), texture and UV
//     set-ups, the brush stream read, the font's code-to-glyph map for codes >= 128, the font module's open / close
//     (free lists, the path buffer, the quad index table), Rt2dFontSetPath, the string width, the font destroy, the
//     unicode flag, the font read-callback slot.
//
// RpRandom -- the state a Tartarus floor (field4: the generator's only random source) and every other game system
// depends on. It is the classic BSD additive generator ("TYPE_3": x[n] = x[n-31] + x[n-3] mod 2^32, output x >> 1):
//   * The state is a 124-byte table of 31 words (RwMalloc'd by the plugin open sub_488D40, hint 0x4010C) and four
//     pointers in the plugin's engine block, at RwEngineInstance 0x960070 + the plugin offset (gp 0x7CE778):
//       +0 table, +4 front ("fptr", starts at table + 3), +8 rear ("rptr", starts at table + 0), +12 end (table + 124).
//   * RpRandom (sub_488F30, 63 callers): *front += *rear; the result is the new *front >> 1 (31 bits, 0 .. 2^31 - 1,
//     zero-extended in $v0); front and rear step one word, front wrapping to the table start at the end (rear then
//     steps without a check), else rear wrapping at the end. front - rear stays 3 words (mod 31).
//   * RpRandomSeed (0x488DD0): table[0] = seed, table[i] = table[i-1] x 1103515245 + 12345 (i = 1..30, mod 2^32),
//     front = table + 3, rear = table, then 310 (10 x 31) draws thrown away. The open seeds 0x9A319039; kwlnMain
//     (0x1984C0) reseeds with the T0 counter at boot -- once per boot, so a run's whole sequence follows from that
//     seed and the number of draws since.
//   * RpRandomSeedMT (0x488C70) is a separate generator (a 624-word table at 0x95D414, seed | 1 at 0x95D410, multiplier
//     69069, index 0x7CDBC4 cleared), also seeded by kwlnMain; RpRandom never reads it.
//   (The host model of both is in tests/game/test_render_rw7.cpp; the snapshots' live states check its invariants.)
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/render_rw6.h"  // rw6:: (and rw5:: / rw4::) the scene layouts and the PS2 pipeline records

namespace p3fes::game {

namespace rw7 {

namespace mfx {                               // the RpMatFX material extension (132 bytes; material + gp 0x7CE738)
constexpr s32 kEffect0 = 0;                   // two 64-byte effect slots
constexpr s32 kEffect1 = 64;
constexpr s32 kSlotSize = 64;
constexpr s32 kEnv0FbAlpha = 12;              // slot 0 / slot 1 read as environment slots (the frame-buffer alpha switch)
constexpr s32 kEnv1FbAlpha = 76;
constexpr s32 kGs0Alpha = 40;                 // u64 x 3 the GS words of slot 0 (ALPHA first) ...
constexpr s32 kGs0B = 48;
constexpr s32 kGs0C = 56;
constexpr s32 kGs1Alpha = 104;                // ... and of slot 1
constexpr s32 kGs1B = 112;
constexpr s32 kGs1C = 120;
constexpr s32 kFlags = 128;                   // 1 bump, 2 env, 3 bump + env, 4 dual, 5 UV, 6 dual + UV
}  // namespace mfx

namespace mfxslot {                           // the common tail of an effect slot
constexpr s32 kType = 32;                     // the slot's effect: 0 none, 1 bump, 2 env, 4 dual, 5 UV
constexpr s32 kGsAlpha = 40;                  // u64 the pass's ALPHA word (bit 39 set: 0x80_0000_0000 | the blend), then 48 / 56
constexpr s32 kGs48 = 48;
constexpr s32 kGs56 = 56;
}  // namespace mfxslot

namespace mfxbump {                           // a bump-map slot
constexpr s32 kFrame = 0;
constexpr s32 kBumpTexture = 4;               // the derived (bumped) texture
constexpr s32 kTexture = 8;
constexpr s32 kNegCoef = 12;                  // f32: the coefficient, stored negated
constexpr s32 kInvWidth = 16;                 // f32: 1 / the texture's raster width
}  // namespace mfxbump

namespace mfxenv {                            // an environment-map slot
constexpr s32 kFrame = 0;
constexpr s32 kTexture = 4;
constexpr s32 kCoef = 8;                      // f32
constexpr s32 kFbAlpha = 12;                  // the frame-buffer alpha switch
}  // namespace mfxenv

namespace mfxdual {                           // a dual-pass slot
constexpr s32 kTexture = 0;
constexpr s32 kSrcBlend = 4;                  // RwBlendFunction values (1, 2, 5, 6, 7 map to the ALPHA table rows)
constexpr s32 kDstBlend = 8;
}  // namespace mfxdual

namespace mfxuv {                             // a UV-transform slot
constexpr s32 kBaseMatrix = 0;
constexpr s32 kDualMatrix = 4;
}  // namespace mfxuv

namespace morphgeo {                          // the RpMorph geometry extension (12 bytes; geometry + gp 0x7CE748)
constexpr s32 kNumKeys = 0;
constexpr s32 kKeyEnd = 4;                    // the key-end callback (default sub_46A400: the next key)
constexpr s32 kKeys = 8;                      // the 20-byte keys (rw7::morphkey)
}  // namespace morphgeo

namespace morphkey {                          // an RpMorph interpolation key (20 bytes)
constexpr s32 kType = 0;
constexpr s32 kStartMorph = 4;                // s16
constexpr s32 kEndMorph = 6;                  // s16
constexpr s32 kTime = 8;                      // f32 the duration
constexpr s32 kNext = 16;                     // the next key (streamed as its index)
constexpr s32 kSize = 20;
}  // namespace morphkey

namespace morphatom {                         // the RpMorph atomic extension (12 bytes; atomic + gp 0x7CE744)
constexpr s32 kKey = 0;                       // the current key
constexpr s32 kPosition = 4;                  // f32 the position in it
constexpr s32 kGeometry = 8;                  // the geometry the state belongs to (copied only for the same geometry)
}  // namespace morphatom

namespace pdsreg {                            // the PDS pipe registry (0x95C44C)
constexpr s32 kEntries = 0;                   // 20-byte entries
constexpr s32 kCount = 4;
constexpr s32 kCapacity = 8;                  // 9 when the attach is given 0
constexpr s32 kWord12 = 12;
}  // namespace pdsreg

namespace rrand {                             // RpRandom's engine block (RwEngineInstance 0x960070 + gp 0x7CE778)
constexpr s32 kTable = 0;                     // 31 words (124 bytes)
constexpr s32 kFront = 4;
constexpr s32 kRear = 8;
constexpr s32 kEnd = 12;
constexpr s32 kTableBytes = 124;
}  // namespace rrand

namespace spline {                            // an RpSpline
constexpr s32 kNumPoints = 8;                 // the internal point count: the user's + 2 (open) / + 3 (closed)
constexpr s32 kType = 12;                     // 1 open, 2 closed
constexpr s32 kCtrlPoints = 20;               // the user's control points (V3d)
constexpr s32 kBPoints = 56;                  // the solved B-spline points (V3d), from here on
}  // namespace spline

namespace uda {                               // an RpUserDataArray (16 bytes)
constexpr s32 kName = 0;
constexpr s32 kFormat = 4;                    // 1 int, 2 real, 3 string
constexpr s32 kCount = 8;
constexpr s32 kData = 12;                     // the elements (strings: an array of string pointers)
constexpr s32 kSize = 16;
}  // namespace uda

namespace udlist {                            // an object's user data list (the extension, 8 bytes)
constexpr s32 kCount = 0;
constexpr s32 kArrays = 4;                    // count x 16-byte arrays
}  // namespace udlist

namespace meshhdr {                           // an RpMeshHeader (16 bytes), its meshes after it (rw7::mesh), then the indices
constexpr s32 kFlags = 0;                     // bit 0: tri-strips
constexpr s32 kNumMeshes = 4;                 // u16
constexpr s32 kSerial = 6;                    // u16 the serial number (sub_496580)
constexpr s32 kTotalIndices = 8;
constexpr s32 kFirstMeshOffset = 12;
constexpr s32 kMeshes = 16;
}  // namespace meshhdr

namespace mesh {                              // an RpMesh (12 bytes)
constexpr s32 kIndices = 0;                   // u16 indices (streamed as 32-bit words, 256 at a time)
constexpr s32 kNumIndices = 4;
constexpr s32 kMaterial = 8;                  // streamed as its index in the material list
constexpr s32 kSize = 12;
}  // namespace mesh

namespace geoext {                            // the geometry's plugin words of this slice
constexpr s32 kMeshHeader = 84;               // the bin-mesh header
}  // namespace geoext

namespace ptankdata {                         // the PTank data of a tank atomic (atomic + gp 0x7CE770; ptank.h)
constexpr s32 kNumParticles = 0;
constexpr s32 kBlock = 12;                    // the RwMalloc'd block the component arrays live in
constexpr s32 kWord60 = 60;
constexpr s32 kFlagsPipe = 68;                // bit 4: the instance buffers are not the tank's
constexpr s32 kPosition = 84;                 // {pointer, stride} of each component: position (flag 0x1, 12 bytes)
constexpr s32 kPositionStride = 88;
constexpr s32 kMatrix = 92;                   // matrix (0x8, 64)
constexpr s32 kMatrixStride = 96;
constexpr s32 kNormal = 100;                  // normal (0x10, 12)
constexpr s32 kNormalStride = 104;
constexpr s32 kPartSize = 108;                // size (0x4, 8)
constexpr s32 kPartSizeStride = 112;
constexpr s32 kColor = 116;                   // colour (0x2, 4)
constexpr s32 kColorStride = 120;
constexpr s32 kVtxColor = 124;                // vertex colours (0x40, 16)
constexpr s32 kVtxColorStride = 128;
constexpr s32 kRotate = 132;                  // 2-D rotation (0x20, 4)
constexpr s32 kRotateStride = 136;
constexpr s32 kVtx2Tex = 140;                 // two texture coordinates (0x80, 16)
constexpr s32 kVtx2TexStride = 144;
constexpr s32 kVtx4Tex = 148;                 // four texture coordinates (0x100, 32)
constexpr s32 kVtx4TexStride = 152;
constexpr s32 kPipeRecord = 156;              // the pipeline record (its buffer ring)
constexpr s32 kNumComponents = 160;
constexpr s32 kWord164 = 164;
constexpr s32 kFormat = 168;                  // the format flags (the low 9 bits rewritten by the allocation)
}  // namespace ptankdata

namespace tsedge {                            // a tri-strip builder edge (16 bytes)
constexpr s32 kV1 = 0;                        // u16
constexpr s32 kV0 = 2;                        // u16
constexpr s32 kTri = 4;                       // the first triangle
constexpr s32 kOther = 8;                     // the second triangle (0: the edge is open)
constexpr s32 kNext = 12;                     // the next edge of the bucket
}  // namespace tsedge

namespace tstri {                             // a tri-strip builder triangle (36 bytes)
constexpr s32 kIndex = 0;
constexpr s32 kEdge0 = 4;
constexpr s32 kEdge1 = 8;
constexpr s32 kEdge2 = 12;
constexpr s32 kWord16 = 16;
constexpr s32 kWord20 = 20;
constexpr s32 kWord24 = 24;
constexpr s32 kNeighbours = 32;               // u8 the count of shared edges
}  // namespace tstri

namespace objsetup {                          // the PS2All object set-up record the tank callbacks fill
constexpr s32 kAtomic = 8;
constexpr s32 kMeshHeader = 12;               // the geometry's mesh header (+84)
constexpr s32 kResEntry = 16;                 // the geometry's native resource entry (the pipeline-id cache, sub_49E5A0)
constexpr s32 kFlags = 20;                    // bit 0 cleared: reinstance flags (2, 4, 8 in the lit set-up)
constexpr s32 kInstanceKey = 24;              // the lit set-up: geometry flags / morph count / serial
constexpr s32 kClip = 40;                     // u8: the camera's clip word | 2 when the sphere crosses a plane
constexpr s32 kLightMode = 41;                // u8: 4 (unlit), 1 / 2 / 4 by the lights
constexpr s32 kDone = 42;                     // u8: 1
}  // namespace objsetup

namespace font2d {                            // an Rt2d font (324 bytes, free list 0x95ED68)
constexpr s32 kHeight = 12;                   // f32 the inter-character gap added to each advance
constexpr s32 kFlags = 16;                    // bit 1: unicode (two-byte codes)
constexpr s32 kTextures = 20;                 // four texture slots
constexpr s32 kMap = 36;                      // s16 x 128: the glyph index of codes 0..127
constexpr s32 kFirstHigh = 292;               // the codes >= 128: the first, the count, the s16 map
constexpr s32 kNumHigh = 296;
constexpr s32 kHighMap = 300;
constexpr s32 kNumGlyphs = 304;
constexpr s32 kGlyphs = 308;                  // the sList of 32-byte glyphs (+0 the advance, +24 a path)
}  // namespace font2d

namespace brush2d {                           // an Rt2d brush (120 bytes): four 24-byte groups {f32 RGBA, f32 UV}
constexpr s32 kRgba0 = 0;                     // the first colour (floats 0..255) and UV, then the deltas to the
constexpr s32 kUv0 = 16;                      // second colour / UV of the same edge, then the other edge's pair
constexpr s32 kRgbaDelta0 = 24;
constexpr s32 kUvDelta0 = 40;
constexpr s32 kRgba1 = 48;
constexpr s32 kUv1 = 64;
constexpr s32 kRgbaDelta1 = 72;
constexpr s32 kUvDelta1 = 88;
constexpr s32 kPackedRgba = 96;               // u8 x 4: the first colour as bytes
constexpr s32 kFlags = 100;                   // bit 1: textured / UV varying
constexpr s32 kTexture = 104;
constexpr s32 kHalfWidth = 112;               // f32 (0.5 at create)
constexpr s32 kRefCount = 116;
}  // namespace brush2d

namespace rxpipe {                            // an RxPipeline (the fields the destroy reads)
constexpr s32 kLocked = 0;                    // non-zero while locked: a node destroy then removes the node in place
constexpr s32 kNumNodes = 4;
constexpr s32 kNodes = 8;                     // 40-byte nodes (rw6::pnode)
constexpr s32 kScratch = 32;                  // a block freed with the pipeline, and its size
constexpr s32 kScratchSize = 36;
}  // namespace rxpipe

namespace rxnodedef {                         // an RxNodeDefinition (the fields a node destroy reads)
constexpr s32 kNodeTerm = 12;                 // called when the last node of the definition goes
constexpr s32 kPipelineNodeTerm = 20;         // called for each node destroyed
constexpr s32 kHeapAllocated = 56;            // non-zero: the definition is freed with its last node
constexpr s32 kRefCount = 60;
}  // namespace rxnodedef

}  // namespace rw7

// --- the bodies (register ABI: arguments in $a0.., $f12.., the result in $v0 / $f0) ---------------------------------
void sub_4643B0(EEContext& ctx);  // 0x4643B0 [prt122CreateEntry] -- allocates entry $a1's 20-byte records of a plugin-0x122 object: n records zeroed with their last word -1, the count
void sub_464540(EEContext& ctx);  // 0x464540 [prt122StreamRead] -- reads a plugin-0x122 chunk (the resource manager's loader): a 4-word header, the object (sub_464280), each entry's 20-byte records
void sub_467590(EEContext& ctx);  // 0x467590 [matfxClose] -- RpMatFX's engine close: the open count down (at 0 the platform close sub_469CF0), the 144-byte free list destroyed
void sub_467600(EEContext& ctx);  // 0x467600 [matfxOpen] -- RpMatFX's engine open: on the first open the 144-byte effect free list (sub_4C3B60, static block 0x95C410) and the platform open
void sub_4676A0(EEContext& ctx);  // 0x4676A0 [matfxMaterialConstructor] -- the RpMatFX material extension constructor: no effects (the pointer at material + offset = 0); the material
void sub_4676C0(EEContext& ctx);  // 0x4676C0 [matfxEffectsReset] -- resets a material's RpMatFX effects record: each slot's textures destroyed by its type, then all 144 bytes cleared
void sub_4677F0(EEContext& ctx);  // 0x4677F0 [matfxMaterialDestructor] -- the RpMatFX material extension destructor: the effects record reset (sub_4676C0) and returned to the 144-byte free list; the material
void sub_467B40(EEContext& ctx);  // 0x467B40 [matfxReadTexture] -- reads an effect texture: a 'present' word, then (when 1) the texture chunk (RwTextureStreamRead, sub_4C83C0)
void sub_467C20(EEContext& ctx);  // 0x467C20 [matfxMaterialStreamWrite] -- the RpMatFX material extension stream write: the effects flags, then each of the two slots by its type
void sub_468350(EEContext& ctx);  // 0x468350 [matfxMaterialStreamSize] -- the RpMatFX material extension stream size: 4 (the flags) + per slot 4 (its type) + its fields and textures
void sub_4684C0(EEContext& ctx);  // 0x4684C0 [matfxAtomicConstructor] -- the RpMatFX atomic extension constructor: the 'effects enabled' word = 0; the atomic
void sub_4684E0(EEContext& ctx);  // 0x4684E0 [matfxAtomicDestructor] -- the RpMatFX atomic extension destructor: the 'effects enabled' word = 0; the atomic
void sub_468500(EEContext& ctx);  // 0x468500 [matfxAtomicCopy] -- the RpMatFX atomic extension copy: sets the destination's word to 1 when the source's is set; the destination
void sub_468530(EEContext& ctx);  // 0x468530 [matfxAtomicStreamWrite] -- the RpMatFX atomic extension stream write: the 'effects enabled' word (RwStreamWriteInt32)
void sub_4685D0(EEContext& ctx);  // 0x4685D0 [matfxAtomicStreamSize] -- the RpMatFX atomic extension stream size: 4 when effects are enabled, else 0
void sub_4685F0(EEContext& ctx);  // 0x4685F0 [matfxSectorConstructor] -- the RpMatFX world-sector extension constructor: the 'effects enabled' word = 0; the sector
void sub_468610(EEContext& ctx);  // 0x468610 [matfxSectorDestructor] -- the RpMatFX world-sector extension destructor: the 'effects enabled' word = 0; the sector
void sub_468630(EEContext& ctx);  // 0x468630 [matfxSectorCopy] -- the RpMatFX world-sector extension copy: sets the destination's word to 1 when the source's is set
void sub_468660(EEContext& ctx);  // 0x468660 [matfxSectorStreamWrite] -- the RpMatFX world-sector extension stream write: the 'effects enabled' word
void sub_468690(EEContext& ctx);  // 0x468690 [matfxSectorStreamRead] -- the RpMatFX world-sector extension stream read: a word; when set, RpMatFXWorldSectorEnableEffects (sub_468E30)
void sub_468700(EEContext& ctx);  // 0x468700 [matfxSectorStreamSize] -- the RpMatFX world-sector extension stream size: 4 when effects are enabled, else 0
void sub_468C50(EEContext& ctx);  // 0x468C50 [RpMatFXPluginAttach] -- registers RpMatFX (plugin 0x120): the engine open / close, the 4-byte material, atomic and world-sector extensions with their streams
void sub_468E30(EEContext& ctx);  // 0x468E30 [RpMatFXWorldSectorEnableEffects] -- enables effects on a world sector: once, its pipeline set (matfxSetSectorPipeline) and the word set to 1
void sub_469030(EEContext& ctx);  // 0x469030 [RpMatFXMaterialGetEffects] -- a material's effects flags (extension +128), or 0 without an extension
void sub_469060(EEContext& ctx);  // 0x469060 [RpMatFXMaterialSetBumpMapTexture] -- sets the bump-map slot's texture and derives the bumped texture
void sub_469280(EEContext& ctx);  // 0x469280 [RpMatFXMaterialSetBumpMapFrame] -- the bump-map slot's frame (+0) = $a1; the material
void sub_4692E0(EEContext& ctx);  // 0x4692E0 [RpMatFXMaterialSetBumpMapCoefficient] -- the bump-map slot's coefficient = $f12, stored negated (+12); the material
void sub_469340(EEContext& ctx);  // 0x469340 [RpMatFXMaterialGetBumpMapFrame] -- the bump-map slot's frame (+0)
void sub_4693A0(EEContext& ctx);  // 0x4693A0 [RpMatFXMaterialGetBumpMapCoefficient] -- the bump-map slot's coefficient in $f0 (the stored value negated back)
void sub_469400(EEContext& ctx);  // 0x469400 [RpMatFXMaterialSetEnvMapTexture] -- sets the environment slot's texture: its reference count up, the old one destroyed; the material
void sub_4694B0(EEContext& ctx);  // 0x4694B0 [RpMatFXMaterialSetEnvMapFrame] -- the environment slot's frame (+0) = $a1; the material
void sub_469590(EEContext& ctx);  // 0x469590 [RpMatFXMaterialSetEnvMapCoefficient] -- the environment slot's coefficient (+8) = $f12; the material
void sub_4695F0(EEContext& ctx);  // 0x4695F0 [RpMatFXMaterialGetEnvMapTexture] -- the environment slot's texture (+4)
void sub_469650(EEContext& ctx);  // 0x469650 [RpMatFXMaterialGetEnvMapFrame] -- the environment slot's frame (+0)
void sub_4696B0(EEContext& ctx);  // 0x4696B0 [RpMatFXMaterialGetEnvMapFrameBufferAlpha] -- the environment slot's frame-buffer alpha switch (+12)
void sub_469710(EEContext& ctx);  // 0x469710 [RpMatFXMaterialGetEnvMapCoefficient] -- the environment slot's coefficient (+8) in $f0
void sub_4698E0(EEContext& ctx);  // 0x4698E0 [RpMatFXMaterialGetDualTexture] -- the dual slot's texture (+0)
void sub_469940(EEContext& ctx);  // 0x469940 [RpMatFXMaterialGetDualBlendModes] -- the dual slot's source / destination blend modes (+4 / +8) into *$a1 / *$a2; the material
void sub_4699B0(EEContext& ctx);  // 0x4699B0 [RpMatFXMaterialSetUVTransformMatrices] -- the UV slot's base / dual matrices (+0 / +4) = $a1 / $a2; the material
void sub_469A10(EEContext& ctx);  // 0x469A10 [RpMatFXMaterialGetUVTransformMatrices] -- the UV slot's base / dual matrices into *$a1 / *$a2 (each when non-null); the material
void sub_469AA0(EEContext& ctx);  // 0x469AA0 [matfxSetupGsWords] -- the default GS words of a material's effect passes by its effects flags (a jump table on +128)
void sub_469B50(EEContext& ctx);  // 0x469B50 [matfxSetEnvAlphaWord] -- an environment pass's ALPHA word from its frame-buffer alpha switch: 88 when set, else 0x80_0000_0068
void sub_469BC0(EEContext& ctx);  // 0x469BC0 [matfxSetDualAlphaWord] -- the dual pass's ALPHA word from its blend modes: the 6 x 6 table 0x6B4EB0 | 0x80_0000_0000
void sub_469CE0(EEContext& ctx);  // 0x469CE0 [matfxPlatformOpen] -- the platform part of RpMatFX's open: 1
void sub_469CF0(EEContext& ctx);  // 0x469CF0 [matfxPlatformClose] -- the platform part of RpMatFX's close: 1
void sub_469DD0(EEContext& ctx);  // 0x469DD0 [morphOpen] -- RpMorph's engine open: the open count up; $a0
void sub_469DF0(EEContext& ctx);  // 0x469DF0 [morphClose] -- RpMorph's engine close: the open count down; $a0
void sub_469E10(EEContext& ctx);  // 0x469E10 [morphAtomicConstructor] -- the RpMorph atomic extension constructor: key, position and geometry cleared; the atomic
void sub_469E30(EEContext& ctx);  // 0x469E30 [morphAtomicCopy] -- the RpMorph atomic extension copy: the state when it belongs to the source's geometry, applied to the interpolator
void sub_469FE0(EEContext& ctx);  // 0x469FE0 [morphGeometryDestructor] -- the RpMorph geometry extension destructor: the key array freed (RwFree), count and keys cleared; the geometry
void sub_46A040(EEContext& ctx);  // 0x46A040 [morphGeometryCopy] -- the RpMorph geometry extension copy: the keys copied into a new 20 x n block (RwMalloc, memcpy) with the count
void sub_46A0F0(EEContext& ctx);  // 0x46A0F0 [morphGeometryStreamWrite] -- the RpMorph geometry extension stream write: the key count, then each key as 5 words (type, start, end, duration, next index)
void sub_46A230(EEContext& ctx);  // 0x46A230 [morphGeometryStreamRead] -- the RpMorph geometry extension stream read: the key count, the keys (RpMorphGeometryCreateInterpolators), each read as 5 words
void sub_46A3C0(EEContext& ctx);  // 0x46A3C0 [morphGeometryStreamSize] -- the RpMorph geometry extension stream size: 20 x keys + 4, or 0 without keys
void sub_46A400(EEContext& ctx);  // 0x46A400 [morphDefaultKeyEnd] -- RpMorph's default key-end callback: the atomic's current key becomes that key's next (+16); returns it
void sub_46A440(EEContext& ctx);  // 0x46A440 [morphGeometryConstructor] -- the RpMorph geometry extension constructor: no keys, the key-end callback sub_46A400; the geometry
void sub_46A470(EEContext& ctx);  // 0x46A470 [RpMorphGeometryCreateInterpolators] -- gives a geometry $a1 zeroed interpolation keys: the old array freed, RwMalloc(20 x n), the count; the geometry, or 0
void sub_46A530(EEContext& ctx);  // 0x46A530 [RpMorphPluginAttach] -- registers RpMorph (plugin 0x105): the engine open / close, the 12-byte atomic and geometry extensions and the geometry's streams
void sub_46A660(EEContext& ctx);  // 0x46A660 [pdsClose] -- the PDS plugin's engine close: the open count down; at 0 the pipe registry destroyed (sub_46A9E0); $a0
void sub_46A6C0(EEContext& ctx);  // 0x46A6C0 [pdsMaterialRights] -- the PDS rights callback of materials: the material's pipeline (+8) from its PDS id
void sub_46A6F0(EEContext& ctx);  // 0x46A6F0 [pdsAtomicRights] -- the PDS rights callback of atomics: the atomic's pipeline (+108) from its PDS id
void sub_46A720(EEContext& ctx);  // 0x46A720 [pdsSectorRights] -- the PDS rights callback of world sectors: the sector's pipeline (+124) from its PDS id
void sub_46A750(EEContext& ctx);  // 0x46A750 [RpPDSPluginAttach] -- registers the PDS plugin (0x131): the pipe registry for $a0 pipes, the engine open / close, the material / atomic / sector rights callbacks
void sub_46A970(EEContext& ctx);  // 0x46A970 [pdsRegistryInit] -- sets up a PDS pipe registry: RwMalloc(20 x n) (n = $a1, 9 when 0), count 0, capacity n; the registry
void sub_46A9E0(EEContext& ctx);  // 0x46A9E0 [pdsRegistryDestroy] -- destroys a PDS pipe registry: each entry's pipeline (RxPipelineDestroy), the entry array (RwFree), the four words cleared
void sub_4734B0(EEContext& ctx);  // 0x4734B0 [ptankAtomicConstructor] -- the PTank atomic extension constructor: no tank data; the atomic
void sub_473590(EEContext& ctx);  // 0x473590 [ptankPluginAttach] -- registers the PTank plugin (0x12F): the engine open / close (sub_474BB0 / sub_474C60) and the 4-byte atomic extension (destructor sub_4734D0)
void sub_473600(EEContext& ctx);  // 0x473600 [ptankAllocSeparate] -- allocates a tank's component arrays one after the other (a structure of arrays) for the format $a1
void sub_473B10(EEContext& ctx);  // 0x473B10 [ptankAllocInterleaved] -- allocates a tank's components interleaved (an array of structures) for the format $a1
void sub_4753D0(EEContext& ctx);  // 0x4753D0 [ptankDataSize] -- the bytes of a tank's components for $a0 particles in the format $a1, each array rounded to 16 (+79 for colour and size)
void sub_475540(EEContext& ctx);  // 0x475540 [ptankCreatePipeData] -- creates a tank's pipeline record (400 bytes + its buffers) for $a1 particles and the format at +88, by the flags $a3
void sub_475C20(EEContext& ctx);  // 0x475C20 [ptankReleaseInstanceBuffers] -- releases a tank atomic's instance buffers: each buffer record's resource entry (sub_4C47E0) cleared
void sub_477050(EEContext& ctx);  // 0x477050 [ptankNextBuffer] -- steps a tank's buffer ring and loads the current buffer's three {pointer, stride} pairs into the tank data
void sub_478CC0(EEContext& ctx);  // 0x478CC0 [ptank2dObjectSetup] -- the 2-D tank pipeline's PS2All object set-up callback: mesh header, resource entry, transform, frustum clip flag
void sub_47A050(EEContext& ctx);  // 0x47A050 [ptank3dObjectSetup] -- the 3-D tank pipeline's PS2All object set-up callback (the same body as sub_478CC0)
void sub_47ABF0(EEContext& ctx);  // 0x47ABF0 [ptankLitObjectSetup] -- the lit tank pipeline's PS2All object set-up callback: as sub_478CC0 plus the reinstance flags and the lights
void RpRandomSeedMT(EEContext& ctx);  // 0x488C70 -- seeds the separate MT-style generator: 0x95D410 = seed | 1, the 623 words at 0x95D414 the successive x 69069 products, the index cleared
void sub_488CD0(EEContext& ctx);  // 0x488CD0 [randomClose] -- RpRandom's engine close: the 124-byte state table freed (RwFree) and its pointer cleared; $a0
void sub_488D40(EEContext& ctx);  // 0x488D40 [randomOpen] -- RpRandom's engine open: the 124-byte state table (RwMalloc, hint 0x4010C), the pointers, the default seed 0x9A319039
void RpRandomSeed(EEContext& ctx);  // 0x488DD0 -- seeds RpRandom: table[0] = seed, table[i] = table[i-1] x 1103515245 + 12345, front = table + 3, rear = table, 310 draws discarded
void sub_488F30(EEContext& ctx);  // 0x488F30 [RpRandom] -- RpRandom: *front += *rear, the result the new value >> 1 (0 .. 2^31 - 1); front and rear step, wrapping at the table end
void sub_488FE0(EEContext& ctx);  // 0x488FE0 [RpRandomPluginAttach] -- registers RpRandom (plugin 0x10C): 16 bytes of engine data, the open / close (sub_488D40 / sub_488CD0); 1 when registered
void sub_48AD20(EEContext& ctx);  // 0x48AD20 [splineOpenBasis] -- RpSpline's open: the twelve 257-entry basis tables (one RwMalloc of 12,336 bytes) -- the cubic B-spline weights and their derivatives at t = i / 256
void sub_48AF80(EEContext& ctx);  // 0x48AF80 [splineEndMatrix] -- builds the n x n float matrix of an open spline's end conditions (the inverse of the 1 4 1 system with its ends)
void sub_48B910(EEContext& ctx);  // 0x48B910 [splineSolve] -- RpSpline's control-point solve: the user's points (+20) to the B-spline points (+56) so that the curve passes through them
void sub_48CF00(EEContext& ctx);  // 0x48CF00 [splineClose] -- RpSpline's close: at the last close the basis tables freed (RwFree x 8 of the scratch, then the block); $a0
void sub_48CFA0(EEContext& ctx);  // 0x48CFA0 [splineOpen] -- RpSpline's engine open: on the first open the basis tables (sub_48AD20) and the end matrices for 4..10 points (0x95DE50..)
void sub_48D200(EEContext& ctx);  // 0x48D200 [splineGetNumSegments] -- the number of user control points of a spline: points - 3 (closed) / - 2 (open); error 1 and 0 for another type
void sub_48D370(EEContext& ctx);  // 0x48D370 [RpSplineSetControlPoint] -- sets user control point $a1 of a spline to *$a2 and re-solves the spline (sub_48B910)
void sub_48D480(EEContext& ctx);  // 0x48D480 [RpSplineFindPosition] -- RpSpline's position (and tangent) at a parameter: path 10 (smooth) or 11 (nice ends), the basis tables
void sub_48DCF0(EEContext& ctx);  // 0x48DCF0 [RpSplinePluginAttach] -- registers RpSpline (plugin 0x102): the engine open / close (sub_48CFA0 / sub_48CF00); 1 when registered
void sub_48DD30(EEContext& ctx);  // 0x48DD30 [userDataOpen] -- RpUserData's engine open: the open count up; $a0
void sub_48DD50(EEContext& ctx);  // 0x48DD50 [userDataClose] -- RpUserData's engine close: the open count down; $a0
void sub_48DD70(EEContext& ctx);  // 0x48DD70 [userDataArrayDestroy] -- frees a user data array: its name, for strings every string, and the element array (RwFree)
void sub_48DE50(EEContext& ctx);  // 0x48DE50 [userDataArrayCopy] -- copies a user data array into $a0: format, count, the name and (strings) each string duplicated, else the elements copied
void sub_48E020(EEContext& ctx);  // 0x48E020 [userDataArrayStreamRead] -- reads a user data array: the name (length, chars), the format, the count, then the elements by format
void sub_48E2D0(EEContext& ctx);  // 0x48E2D0 [userDataArrayStreamWrite] -- writes a user data array: the name (strlen + 1, then the chars), the format, the count, the elements by format
void sub_48E4F0(EEContext& ctx);  // 0x48E4F0 [userDataArrayStreamSize] -- the stream size of a user data array: 4 + the name (strlen + 1) + 8 + the elements (strings: 4 + length + 1 each)
void sub_48E610(EEContext& ctx);  // 0x48E610 [userDataListDestroy] -- frees every array of a user data list (as sub_48DD70) and the array of arrays; count and pointer cleared
void sub_48E750(EEContext& ctx);  // 0x48E750 [userDataListStreamWrite] -- writes a user data list: the count of arrays with a format, then each such array (sub_48E2D0)
void sub_48E890(EEContext& ctx);  // 0x48E890 [userDataListAddArray] -- adds an array to a user data list: the first array without data, else the list grown by one (RwMalloc, copy, RwFree)
void sub_48EA90(EEContext& ctx);  // 0x48EA90 [userDataConstructor] -- the user data extension constructor ($a1 = the extension offset): count and arrays cleared; the object
void sub_48EAB0(EEContext& ctx);  // 0x48EAB0 [userDataDestructor] -- the user data extension destructor: each array destroyed (sub_48DD70), the array of arrays freed; the object
void sub_48EB50(EEContext& ctx);  // 0x48EB50 [userDataCopy] -- the user data extension copy: the destination's list destroyed (sub_48E610), then every array copied (sub_48DE50); the destination
void sub_48EC20(EEContext& ctx);  // 0x48EC20 [userDataStreamRead] -- the user data extension stream read: the array count, the arrays (RwMalloc of 16 x count), each read by sub_48E020
void sub_48ECF0(EEContext& ctx);  // 0x48ECF0 [userDataStreamWrite] -- the user data extension stream write: the list written (sub_48E750); the stream
void sub_48ED20(EEContext& ctx);  // 0x48ED20 [userDataStreamSize] -- the user data extension stream size: the arrays with a format (sub_48E4F0) + 4, or 0
void sub_48EDE0(EEContext& ctx);  // 0x48EDE0 [userDataCountFilled] -- the number of an object's user data arrays that have elements (data != 0)
void sub_48EE30(EEContext& ctx);  // 0x48EE30 [userDataGetArray] -- an object's user data array $a1 (its 16-byte record), or 0 past the count
void sub_48EE70(EEContext& ctx);  // 0x48EE70 [userDataAddArrayTo] -- adds a user data array to the object of extension gp 0x7CE7E0 (sub_48E890 on its list); the index
void name__C9type_info_0(EEContext& ctx);  // 0x48EF10 -- returns the word at $a0 + 0: here an RpUserDataArray's name (RpUserDataArrayGetName)
void sub_48EF20(EEContext& ctx);  // 0x48EF20 [RpUserDataArrayGetFormat] -- a user data array's format (+4)
void sub_48EF30(EEContext& ctx);  // 0x48EF30 [RpUserDataArrayGetNumElements] -- a user data array's element count (+8)
void sub_48EF40(EEContext& ctx);  // 0x48EF40 [RpUserDataArrayGetInt] -- element $a1 of a user data array as an int
void sub_48EF60(EEContext& ctx);  // 0x48EF60 [RpUserDataArrayGetReal] -- element $a1 of a user data array as a real ($f0)
void sub_48EFA0(EEContext& ctx);  // 0x48EFA0 [RpUserDataArraySetInt] -- element $a1 of a user data array = $a2
void sub_48EFC0(EEContext& ctx);  // 0x48EFC0 [RpUserDataArraySetReal] -- element $a1 of a user data array = $f12
void sub_48EFE0(EEContext& ctx);  // 0x48EFE0 [RpUserDataGetFormatSize] -- the element size of a user data format: 4 for 1 (int), 2 (real), 3 (string pointer), else 0
void sub_48F340(EEContext& ctx);  // 0x48F340 [atomicPipeStreamRead] -- the atomic's pipeline-id stream read: the plugin id (held at gp 0x7CE804) and, for an 8-byte chunk, the data (0x7CE800)
void sub_48F3C0(EEContext& ctx);  // 0x48F3C0 [atomicPipeStreamWrite] -- the atomic's pipeline-id stream write: its pipeline's plugin id and data (+44 / +48)
void sub_48F430(EEContext& ctx);  // 0x48F430 [atomicPipeStreamSize] -- the atomic's pipeline-id stream size: 8 when its pipeline (+108) has a plugin id, else 0
void sub_48F460(EEContext& ctx);  // 0x48F460 [sectorPipeStreamRead] -- the world sector's pipeline-id stream read: the plugin id (gp 0x7CE7FC) and, for an 8-byte chunk, the data (0x7CE7F8)
void sub_48F4E0(EEContext& ctx);  // 0x48F4E0 [sectorPipeStreamWrite] -- the world sector's pipeline-id stream write: its pipeline's plugin id and data (+44 / +48)
void sub_48F550(EEContext& ctx);  // 0x48F550 [sectorPipeStreamSize] -- the world sector's pipeline-id stream size: 8 when its pipeline (+124) has a plugin id, else 0
void sub_494580(EEContext& ctx);  // 0x494580 [RpLightStreamRead] -- reads a light: the struct chunk (library 0x35000..0x37002), the light created by type (sub_4947C0), radius, colour, cone, flags, its plugins
void sub_494E30(EEContext& ctx);  // 0x494E30 [RpMaterialStreamRead] -- reads a material: the struct chunk (library 0x35000..0x37002), a material from the free list, colour, surface properties, the texture, its plugins
void sub_495FB0(EEContext& ctx);  // 0x495FB0 [binMeshStreamWrite] -- writes a bin-mesh header: {flags, mesh count, total indices}, per mesh {index count, material index} and its indices
void sub_496230(EEContext& ctx);  // 0x496230 [binMeshStreamRead] -- reads a bin-mesh header: one RwMalloc for the header, the meshes and the indices; the serial number from the engine counter
void sub_4964F0(EEContext& ctx);  // 0x4964F0 [binMeshStreamSize] -- the stream size of a bin-mesh header: 12 + 8 x meshes (+ 4 x the header's total indices unless native data)
void sub_496580(EEContext& ctx);  // 0x496580 [meshHeaderNextSerial] -- the next mesh-header serial number: the engine's u16 counter, post-incremented (sign-extended)
void sub_496AD0(EEContext& ctx);  // 0x496AD0 [triStripFindEdge] -- the tri-strip builder's edge lookup: the open edge (v0, v1) of a bucket gets triangle $t0 as its second, else a new edge
void sub_496BE0(EEContext& ctx);  // 0x496BE0 [triStripFreeEdges] -- frees the tri-strip builder's records: the edge list to its free list, the free lists destroyed, the triangle table freed; 0
void sub_496CD0(EEContext& ctx);  // 0x496CD0 [triStripBuildTriangles] -- builds the tri-strip builder's triangles: a 36-byte record per triangle and its three edges (sub_496AD0)
void sub_498E40(EEContext& ctx);  // 0x498E40 [getWordPair] -- stores the pointer word 0x77DDA0 into *$a0 and the word 0x77DDA4 into *$a1 (each when non-null); 1
void sub_499720(EEContext& ctx);  // 0x499720 [bspTeardown] -- walks a BSP tree and unhooks each world sector: its resource entry (sub_4C47E0), atomic and light ties, its plugin data
void sub_499850(EEContext& ctx);  // 0x499850 [bspDestroy] -- destroys a BSP tree: as sub_499720 and every sector array / plane freed (RwFree)
void sub_49A980(EEContext& ctx);  // 0x49A980 [worldPluginAttach] -- registers the world module's plugins (0x501..0x50B): the engine data, the sector / world / geometry plugins, then sub_49BE50, sub_4915C0, sub_4A5100
void sub_49BC50(EEContext& ctx);  // 0x49BC50 [geometryBinMeshWrite] -- the geometry's bin-mesh stream write: its mesh header (+84) through sub_495FB0 (the material list at +32)
void sub_49BC70(EEContext& ctx);  // 0x49BC70 [geometryBinMeshRead] -- the geometry's bin-mesh stream read: the mesh header (sub_496230) into +84; the stream, or 0
void sub_49BCC0(EEContext& ctx);  // 0x49BCC0 [geometryBinMeshSize] -- the geometry's bin-mesh stream size (sub_4964F0 on +84)
void sub_49BD10(EEContext& ctx);  // 0x49BD10 [geometryNativeSizeThunk] -- the geometry's native-data stream size: a tail call to sub_49ECD0
void sub_49BD60(EEContext& ctx);  // 0x49BD60 [sectorNativeSizeThunk] -- the world sector's native-data stream size: a tail call to sub_49F340
void sub_49BD70(EEContext& ctx);  // 0x49BD70 [sectorBinMeshWrite] -- the world sector's bin-mesh stream write: its mesh header (+120) with its world (worldSectorGetWorld) and the world's materials
void sub_49BDC0(EEContext& ctx);  // 0x49BDC0 [sectorBinMeshRead] -- the world sector's bin-mesh stream read: the mesh header into +120; the stream, or 0
void sub_49BE20(EEContext& ctx);  // 0x49BE20 [sectorBinMeshSize] -- the world sector's bin-mesh stream size (sub_4964F0 on +120 with its world)
void sub_49BE50(EEContext& ctx);  // 0x49BE50 [worldRegisterPlugins] -- the world module's plugin set: the 0x509 extensions of worlds / sectors / atomics / clumps / lights, the bin-mesh (0x50E) and native-data (0x510) streams, the pipeline-id streams (0x1F)
void sub_49E6C0(EEContext& ctx);  // 0x49E6C0 [nativeDataToOffsets] -- rewrites the DMA chain of native data for streaming: each ref tag's (3) address becomes a qword offset from the chain start
void sub_49E780(EEContext& ctx);  // 0x49E780 [nativeDataToAddresses] -- the inverse of sub_49E6C0 after reading: each ref tag's qword offset becomes an address again; 1 when none was met, else 0
void sub_49ECD0(EEContext& ctx);  // 0x49ECD0 [geometryNativeSize] -- the geometry's native-data stream size: 16 + per DMA packet its size - the header's offset + 8; 0 without native data
void sub_49F340(EEContext& ctx);  // 0x49F340 [sectorNativeSize] -- the world sector's native-data stream size, as sub_49ECD0 for the sector's resource (gp 0x7CE888) when its world is native
void sub_49F500(EEContext& ctx);  // 0x49F500 [ps2AllNodeInitData] -- a PS2All node's private-data init: the 976-byte packet area with its 16-aligned GIF tag, the stride / field bytes
void sub_49FE40(EEContext& ctx);  // 0x49FE40 [ps2AllNodeSetCallBack] -- sets a PS2All node's callback: type 1 (non-null) at private data +16, type 2 at +20; the node, or 0
void sceLibgcc32GetErxEntries(EEContext& ctx);  // 0x49FF00 -- returns 0x77DE80: the PS2All node definition the PDS pipe builders add (the symbol name is not its role)
void sub_4A5470(EEContext& ctx);  // 0x4A5470 [Rt2dBrushCreate] -- creates a brush: a cleared 120-byte record from the brush free list, white (four 255 colours), zero UVs, no texture, 0.5 at +112, one reference
void sub_4A5DD0(EEContext& ctx);  // 0x4A5DD0 [Rt2dBrushSetRGBA] -- sets a brush's four colours: the byte RGBA of $t0 / $a3 / $a1 / $a2 as floats, the second of each edge as a delta, the first packed at +96
void sub_4A6200(EEContext& ctx);  // 0x4A6200 [rt2dBrushSetUV] -- sets a brush's two UV origins and deltas from four points; flag bit 1 set when any delta is non-zero, else cleared
void sub_4A62E0(EEContext& ctx);  // 0x4A62E0 [rt2dBrushSetTexture] -- sets a brush's texture: its reference count up, flag bit 1 by its presence, the old texture destroyed; the brush
void sub_4A6360(EEContext& ctx);  // 0x4A6360 [rt2dBrushStreamReadBody] -- fills a brush from its streamed 112-byte record: the four colour / UV groups, the packed colour, flags, +112; the texture when streamed
void sub_4A6530(EEContext& ctx);  // 0x4A6530 [Rt2dBrushStreamRead] -- reads a brush: 112 bytes from the stream, the packed colour, then the body (sub_4A6360) when the record's version word is 1; else 0
void sub_4A7620(EEContext& ctx);  // 0x4A7620 [rt2dFontBuildHighMap] -- builds a font's map of codes >= 128: the code table's minimum / maximum positive codes, a u16 table of glyph indices (-1 for none)
void sub_4A91F0(EEContext& ctx);  // 0x4A91F0 [rt2dFontClose] -- the font module's close: every dictionary font destroyed (its name freed, sub_4A96B0), the texture dictionary, free lists and buffers released
void sub_4A9330(EEContext& ctx);  // 0x4A9330 [rt2dFontOpen] -- the font module's open: the 324-byte font and 12-byte entry free lists, the 81-byte path buffer ('fonts\\'), the quad index table, the texture dictionary
void sub_4A9490(EEContext& ctx);  // 0x4A9490 [Rt2dFontSetPath] -- sets the font path: the buffer grown to strlen + 1 (RwRealloc) when needed, the string copied; the path, or 0
void sub_4A9550(EEContext& ctx);  // 0x4A9550 [rt2dFontSetReadCallBack] -- stores the font read callback (0x95F478); 1
void sub_4A9560(EEContext& ctx);  // 0x4A9560 [Rt2dFontGetStringWidth] -- a string's width in $f0: the sum of each character's glyph advance + the font's gap, times the height $f12
void sub_4A96B0(EEContext& ctx);  // 0x4A96B0 [rt2dFontDestroy] -- destroys a font: each glyph's path (sub_4AC390), the glyph sList, the high map, the four textures, the record; 1, or 0 for none
void sub_4A9BD0(EEContext& ctx);  // 0x4A9BD0 [Rt2dFontIsUnicode] -- 1 when a font is unicode (flag bit 1)
void sub_4A9BE0(EEContext& ctx);  // 0x4A9BE0 [rt2dCallToolkitHook] -- calls the toolkit hook at 0x95EFD0 (a tail call)
void sub_4F2AD0(EEContext& ctx);  // 0x4F2AD0 [rxPipelineNodeDestroy] -- destroys one node of a pipeline: unlocked, the definition's terms and reference count; locked, the node removed from the arrays in place
void sub_4F3010(EEContext& ctx);  // 0x4F3010 [RxPipelineDestroy] -- destroys a pipeline: each of its nodes (sub_4F2AD0), its scratch block (RwFree), the record back to the pipeline free list

}  // namespace p3fes::game
