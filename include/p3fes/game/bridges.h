// Phase 5 slice render_bridges: the PDS material bridges of the RenderWare MatFX plugin on the PS2 driver ("sky")
// and the skinned atomic's partition-aware set-up callback (docs/ANALYSIS/22_rendering.md section 3; queue
// docs/ANALYSIS/queue_rendering.txt rows tagged [pds-bridge]; deferred by render_rw2 for size). Seven functions, 15.9 KB
// of MIPS, all class a0 except the set-up callback.
//
// Where they sit: PS2AllNodeBody calls the material pipeline's bridge callback once per mesh. For a MatFX material
// that callback is the dispatcher sub_46EA80 (mesh.cpp), which reads the material's MatFX effect (material +
// gp-17848 -> +128) and calls the bridge table 0x6B4EE4 with the material pipeline's VU1 code array advanced by 16
// entries per effect; skinned atomics reach the same bridges through the 60-byte wrappers sub_472130 .. sub_473380
// (rw_builders.cpp: the partitioned palette upload sub_46B8E0 first when 0x95DE38 is set). The table, by effect
// (RenderWare's RpMatFXMaterialFlags order, confirmed by what each body reads):
//
//   0 none              RpMeshPS2AllBridgeCallBack 0x4A0E00 (mesh.cpp, the stock bridge)
//   1 bump map          matfxBridgeBumpMap  the bump texture (or the material's) replaces the mesh texture; the bump light's
//                                   3x4 matrix (matfxEffectMatrix), coefficient x inverse width and the camera depth scale,
//                                   two ALPHA_1 / TEST_1 A+D blocks for the bump passes; ALPHA_1 / TEST_1 restored
//   2 environment map   matfxBridgeEnvMap  base texture + the environment texture in GS context 2 (TEX0_2, TEX1_2,
//                                   CLAMP_2, ALPHA_2, TEST_2, ZBUF_2, FOGCOL), the env matrix (matfxEffectMatrix)
//   3 bump + env map    matfxBridgeBumpEnvMap  both of the above: two matfxEffectMatrix matrices, bump scale, context 2 env pass
//   4 dual texture      matfxBridgeDual  base texture + a second texture in context 2 (the same register block)
//   5 UV transform      matfxBridgeUvTransform  the stock packet plus one UNPACK of rows 0, 1, 3 of the UV matrix (identity
//                                   built on the frame when the effect has none) to VU1 0x3BC
//   6 dual + UV xform   matfxBridgeDualUvTransform  dual texture with both UV matrices (identity for a missing one)
//
// Each bridge has the stock bridge's skeleton (mesh.h data flow): texture placement (sub_4F0F30 /
// RpSkyTexCacheAccessRaster), the GS shadows (TEX1 / CLAMP / TEST), _rwDMAOpenVIFPkt, the GIF tag of the VU1 kick
// (template 0x9658A0, PRIM = render flags | prim type) -> VU1 0x3FA, material colour sub_49CAB0 -> 0x3FB, surface
// properties sub_49CBD0 -> 0x3FC, clip vectors + flags -> 0x3FD..0x3FF, the A+D TEST/TEX1/CLAMP (textured) or TEST
// block, the VU1 program `call` when not resident, the resEntry `call` under DI/EI and _rwDMAAddPURef on a first
// use -- with the effect's block (a DMA cnt with UNPACKs to VU1 0x3BC.., and DIRECT GS registers for the context-2
// effects) inserted before the GIF tag, and for every effect but the UV transform a closing packet after the
// resEntry call that restores the driver's GS registers (ALPHA_1 / TEST_1 / FOGCOL).
//
// skinSplitObjectSetupCB is the skinned atomic's object set-up callback when the skin is split into partitions (the "SkSpt"
// pipeline): sub_46EB90's body (the stock set-up with the instance test, prim/transType and lights inlined, then
// _rpSkinMatrixUpdating) except that a partitioned skin (skin +48 != 0) leaves the upload to the per-mesh wrappers by
// setting 0x95DE38 = skin + 44; otherwise it uploads the whole palette (cnt + STCYCL 1,1 / UNPACK V4-32 to VU1 0x2BC)
// and clears 0x95DE38.
//
// Draw data: each bridge reports its mesh draw through the render_mesh observer (mesh::set_draw_observer,
// mesh::MeshDraw, the same fields the stock bridge reports) and, when installed, the MatFX extra through
// bridges::set_effect_observer (which effect, the second texture / raster, where the effect's extra quadwords went);
// skinSplitObjectSetupCB reports its palette through the observer's SkinPalette when it uploads it. Observers never change guest
// state.
//
// Register contract (docs/PHASE5_AGENT_BRIEF.md, waves 6 and 7; as mesh.h): register-faithful at every check point,
// every call and the return (GPRs in 128 bits, HI/LO, FPRs, ACC, FCR31), the original prologue spills and frame
// records written. The bodies work on the guest registers directly (a Cpu view in bridges.cpp, one variable per
// register, the runtime's instruction semantics for MMI / FPU / COP0); the data flow is named in comments.
//
// Names: functions.json names (all sub_*); bracketed roles are proposals (symbols/deltas/render_bridges.sym).
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"

namespace p3fes::game {

namespace bridges {

// --- the MatFX material extension (material + gp-17848), the fields these bodies read --------------------------
// Two 64-byte effect slots (+0, +64) and the effect kind at +128 (RpMatFXMaterialFlags). The PS2 slots carry GS
// register values for the second pass: +40 ALPHA_2 data, +48 FOGCOL data (0x01000000 = "use the driver's", gp-17056),
// +56 TEST_2 bits ORed into TEST_1's ATE/ATST/AREF (TEST_1 & 0x70000).
inline constexpr s32 kGpMatFxExt = -17848;     // plugin offset of the material extension
inline constexpr u32 kExtEffect = 128;          // the effect kind (0..6, the table above)
inline constexpr s32 kGpFogColour = -17056;     // u64 shadow of GS FOGCOL (the default second-pass FOGCOL data)
inline constexpr s32 kGpZbuf = -17088;          // u64 shadow of GS ZBUF_1 (copied to ZBUF_2 for the second pass)
inline constexpr s32 kGpAlpha = -17032;         // u64 shadow of GS ALPHA_1 (the bump pass's closing packet)
inline constexpr s32 kGpCamFar = -20924;        // float: the camera far plane the bump scale was computed for
inline constexpr s32 kGpCamDepthScale = -20928; // float: 1 / (far - near) of that camera
inline constexpr u32 kBridgeTable = 0x006B4EE4u;  // the bridge per effect (7 words)
inline constexpr u32 kSkinPartition = 0x0095DE38u;  // the partition record of the current skinned atomic (0 = none)

// The MatFX extra of one bridge, after the guest state is complete (host-only).
enum class Effect : u8 { BumpMap = 1, EnvMap = 2, BumpEnvMap = 3, Dual = 4, UvTransform = 5, DualUvTransform = 6 };
struct EffectDraw {
    Effect effect = Effect::BumpMap;
    u32 pipe_data = 0;      // the RxPS2AllPipeData of the mesh
    u32 texture2 = 0;       // the effect's texture (bump / environment / dual), 0 = none
    u32 raster2 = 0;
    u32 extra_at = 0;       // the effect block's DMA cnt tag in the packet (scratchpad or RAM)
    u32 extra_qw = 0;       // quadwords of that block up to the stock packet's first UNPACK (tag included)
    u32 closing_at = 0;     // the closing packet of the two-pass effects (0 = none) and its quadwords
    u32 closing_qw = 0;
};
struct EffectObserver {
    void (*effect)(EEContext&, const EffectDraw&) = nullptr;
};
// Installs the effect observer (nullptr / empty: none, the default). Host-only, no guest effect.
void set_effect_observer(const EffectObserver* observer) noexcept;

}  // namespace bridges

// --- the seven functions ----------------------------------------------------------------------------------------
// The bridges take the RxPS2AllPipeData in $a0 (mesh.h pd::) and return 1 in $v0.

// [matfxBridgeBumpMap] the MatFX bump-map bridge, effect 1.
void matfxBridgeBumpMap(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [matfxBridgeEnvMap] the MatFX environment-map bridge, effect 2.
void matfxBridgeEnvMap(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [matfxBridgeBumpEnvMap] the MatFX bump + environment-map bridge, effect 3.
void matfxBridgeBumpEnvMap(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [matfxBridgeDual] the MatFX dual-texture bridge, effect 4.
void matfxBridgeDual(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [matfxBridgeUvTransform] the MatFX UV-transform bridge, effect 5.
void matfxBridgeUvTransform(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [matfxBridgeDualUvTransform] the MatFX dual-texture + UV-transform bridge, effect 6.
void matfxBridgeDualUvTransform(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// [skinSplitObjectSetupCB] the skin object set-up callback for partitioned skins ($a0 = PipeData, $a1 = the matrix
// reference). Returns 1, 0 for a geometry without meshes.
void skinSplitObjectSetupCB(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

}  // namespace p3fes::game
