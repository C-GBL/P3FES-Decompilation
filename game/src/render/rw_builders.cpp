// RenderWare sky-driver builders that reach the DMA packet layer (game/include/p3fes/game/rw_builders.h has the groups;
// docs/ANALYSIS/22_rendering.md sections 2.4, 3.2, 5 and 7). Phase 5 slice render_rw2: these replace the recompiled bodies
// listed in game/replaced.txt under "render_rw2"; tests/game/test_render_rw2.cpp runs each against its __recomp body on
// the hardware-observing harness (bus log, scratchpad, DMA window, the register file at every check point).
//
// Virtual time (ADR-0013): every guest::charge is one `ctx.cycles += N` block of the recompiled body; a block that
// contains a `jal` is charged in full before the call (the recompiler keeps a call inside its block), and
// guest::backedge stands where the recompiled body has a back-edge check point -- including the forward-looking ones
// its block layout produces (a branch to an out-of-line block that jumps back).
//
// Registers (rw_builders.h): at each check point, each call and the return every register holds what the original
// holds there. The packet words are built with named fields; the scratch registers the original leaves behind are set
// in the original's order next to the computation, so the trace can be read against the instructions.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 24 of the 35 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: callee frames 8, the hand version terminated the
// host on a random world 7, faults only 5, frame/spills 4); the others are the hand-written versions this
// header describes.
//
// Readability pass (read_render, 2026-10-22): the 24 generated bodies keep every statement, charge, check point and
// call of p3fes_handgen's output in the same order on every path (proved per function by a bisimulation of the two
// statement graphs, and by the faithfulness audit); on top of it they name what they touch -- render_view.h for the
// records and addresses more than one render file reads (`hi()` / `lo()` / `la()` for a lui pair, `gp_off()`, the
// matrix, frame, camera, raster, image, texture, atomic, geometry, sector, Rt2d and PS2All records, the walk tables,
// the driver globals; the PTank, lock and resEntry records in this file's own rwb_view) --, say what each block does,
// and replace the generator's gotos by if / else / break (local lambdas for the shared tails such as the epilogue);
// none is left. Each function's comment gives its role and, for a `sub_` name, a proposed
// name in brackets.
#include "p3fes/game/rw_builders.h"

#include <array>
#include <utility>
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/render_view.h"

namespace p3fes::recomp_gen {
void fn__rwDMAOpenVIFPkt_004d59d0(p3fes::EEContext&);    // (type, qwords) -> 0 when no packet could be opened
void fn__rwDMAAddPkt_004d5000(p3fes::EEContext&);        // (addr, type | qwc << 12): a queue entry
void fn__rwDMAForceBufferSwap_004d4df0(p3fes::EEContext&);
void fn__rwDMAHandler_004d4350(p3fes::EEContext&);       // (-1): the DMAC handler run inline
void fn__rwDMAReqFlip_004d5270(p3fes::EEContext&);
void fn_sub_4D5FE0_004d5fe0(p3fes::EEContext&);          // DMA-memory block allocator (size, 0)
void fn_sub_4F0C60_004f0c60(p3fes::EEContext&);          // (render_rw) the texture-cache frame tick
void fn_sub_4E2F10_004e2f10(p3fes::EEContext&);          // the deferred raster operations of the frame
void fn_sub_4E3640_004e3640(p3fes::EEContext&);          // camera-texture copy of a raster
void fn_sub_4E4800_004e4800(p3fes::EEContext&);          // raster clear (flags, rect)
void fn_sub_46B8E0_0046b8e0(p3fes::EEContext&);          // RpSkin: matrix-palette upload (pipe)
void fn_RpMeshPS2AllBridgeCallBack_004a0e00(p3fes::EEContext&);
void fn_matfxBridgeBumpMap_0046c5b0(p3fes::EEContext&);
void fn_matfxBridgeEnvMap_0046cd90(p3fes::EEContext&);
void fn_matfxBridgeBumpEnvMap_0046d6f0(p3fes::EEContext&);
void fn_matfxBridgeDual_0046e170(p3fes::EEContext&);
void fn_matfxBridgeUvTransform_00472270(p3fes::EEContext&);
void fn_matfxBridgeDualUvTransform_00472970(p3fes::EEContext&);
void fn_sub_46F400_0046f400(p3fes::EEContext&);
void fn_sub_470200_00470200(p3fes::EEContext&);
void fn_sub_470E10_00470e10(p3fes::EEContext&);
void fn_sub_4861B0_004861b0(p3fes::EEContext&);          // RpPTank: run the instance callbacks
void fn_sub_476980_00476980(p3fes::EEContext&);          // RpPTank: scratchpad streamer of 8-byte pairs
void fn_RpSkyTexCacheAccessRaster_004f1020(p3fes::EEContext&);          // RpSkyTexCacheAccessRaster(raster, 1)
void fn_sub_4F1E40_004f1e40(p3fes::EEContext&);          // TEX0/TEX1 words of a raster (raster, out, filter)
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);          // RwFrameGetLTM(frame)
void fn_sub_474A80_00474a80(p3fes::EEContext&);          // RpPTank: reset the tank's instance data
void fn_sub_4D5E90_004d5e90(p3fes::EEContext&);          // wait for the scratchpad DMA of the PTank streamers
void fn_sub_476490_00476490(p3fes::EEContext&);          // RpPTank streamers: 8-byte, 4-byte and 16-byte elements
void fn_sub_476140_00476140(p3fes::EEContext&);
void fn_sub_476720_00476720(p3fes::EEContext&);
void fn__rwDMAOpenGIFPkt_004d54e0(p3fes::EEContext&);    // (qwords): a GIF (PATH3) packet
// This file's own entry points, called the way the originals call them (jal).
void fn_sub_4E4180_004e4180(p3fes::EEContext&);
void fn_sub_4E4420_004e4420(p3fes::EEContext&);
void fn_sub_4E46C0_004e46c0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace rwb;
using namespace rview;  // render_view.h: la / hi / lo / gp_off / flt and the shared RW records
using guest::backedge;
using guest::charge;
using guest::enter;
namespace gen = recomp_gen;
namespace core = ee::core;

namespace {

u64 sx(u32 v) { return core::sext32(v); }

// `_rwDMAOpenVIFPkt(type, qwords)` with the arguments in $a0/$a1 (set by the caller in the original order), jal at pc.
u64 open_vif(EEContext& ctx, u32 pc) {
    jal(ctx, pc, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    return core::gpr64(ctx, GPR_V0);
}

// The scratchpad packet write pointer.
u32 spr_ptr(const EEContext& ctx) { return lw(ctx, gpv(ctx, kGpSprWritePtr)); }
void set_spr_ptr(EEContext& ctx, u32 p) { sw(ctx, gpv(ctx, kGpSprWritePtr), p); }

}  // namespace

// --- named views of the register-level bodies below (read_render, 2026-10-22; render_view.h has the shared ones) ---
// Offsets from the instructions of the functions that use them, cross-checked against ptank.h's data flow.
namespace rwb_view {
// The PTank block (the atomic's plugin data: *(atomic->+8 + the gp-17792 offset); ptank.h's "data flow of one tank"):
// the constant attributes the fills copy, the pipeline record, the instance callback slot.
namespace ptank_block {
inline constexpr s32 kInstanceCb = 36;    // u32: the instance callback sub_4861B0 runs (the render callbacks swap it)
inline constexpr s32 kRunArgs = 80;       // the record handed to sub_4861B0 as its second argument
inline constexpr s32 kConstWidth = 112;   // f32: the constant size (w, h)
inline constexpr s32 kConstHeight = 116;  // f32
inline constexpr s32 kConstColour = 124;  // u8[4]: the constant colour (RGBA)
inline constexpr s32 kConstUv0 = 144;     // f32[2]: the constant UV rectangle's (u0, v0); the UV quad's four pairs
inline constexpr s32 kConstUv1 = 152;     // f32[2]: ... and (u1, v1)                          run to +172
inline constexpr s32 kPipeRecord = 156;   // u32: the pipeline record (ptank_pipe::)
}  // namespace ptank_block
// The instance data the lock and texture callbacks get ($a0 / $a2): its +76 is the same pipeline record.
namespace ptank_inst {
inline constexpr s32 kPipeRecord = 76;    // u32: the pipeline record (ptank_pipe::)
}  // namespace ptank_inst
// The PTank pipeline record (block +156): the GS words of the tank and a ring of 36-byte buffer records, the current
// one's index at +228; a component's buffer pointer is at record + 36 * index + its offset.
namespace ptank_pipe {
inline constexpr s32 kGsTest = 200;        // u64: the tank's TEST word (bit 0 ATE)
inline constexpr s32 kGsTex0 = 208;        // u64: TEX0 (TEX1 at +216; sub_4F1E40 writes both)
inline constexpr s32 kBufIndex = 228;      // u32: the current buffer record
inline constexpr s32 kBufRecordSize = 36;
inline constexpr s32 kBuf16A = 320;        // u32: the 16-byte component A (always locked)
inline constexpr s32 kBuf8 = 332;          // u32: the 8-byte component
inline constexpr s32 kBuf4 = 336;          // u32: the 4-byte component
inline constexpr s32 kBuf3D = 340;         // u32: the 3D format's second component (sub_479840)
inline constexpr s32 kBuf16B = 348;        // u32: the 16-byte component B
inline constexpr s32 kBuf3DB = 352;        // u32: the 3D format's third component (sub_479840)
}  // namespace ptank_pipe
// The atomic as the render callbacks see it: +8 the plugin base the PTank offset is added to, +44 the geometry-like
// record whose +4 is the vertex count.
namespace ptank_atomic {
inline constexpr s32 kPluginBase = 8;
inline constexpr s32 kCounts = 44;
}  // namespace ptank_atomic
// The parameter block of the render callbacks: four words copied into the current buffer record.
namespace ptank_params {
inline constexpr s32 kP0 = 0, kP1 = 4, kP2 = 8, kP3 = 12;
}  // namespace ptank_params
// A raster as these bodies read it (core3.cpp names more of it).
namespace raster_rd {
inline constexpr s32 kDepth = 20;          // s32: bits per pixel (< 9: palettized)
inline constexpr s32 kTypeByte = 32;       // u8: bits 0..2 the raster type (5: a camera texture)
inline constexpr s32 kFormatByte = 35;     // u8: its low nibble the pixel format (6: no alpha test), 0x90 private flags
}  // namespace raster_rd
// The header of a PS2All resEntry's DMA block (HandleUnexpected__... fills it).
namespace res_hdr {
inline constexpr s32 kWord0 = 0, kWord4 = 4;  // cleared
inline constexpr s32 kSize = 8;               // u32: the size asked for
inline constexpr s32 kOwnerData = 12;         // u32: the owner's +8 word
inline constexpr s32 kWord16 = 16;            // cleared
inline constexpr s32 kTag = 20;               // u32: the caller's tag
}  // namespace res_hdr
// A camera: +96 its frame raster.
namespace camera_rd {
inline constexpr s32 kRaster = 96;
}  // namespace camera_rd
// A texture: +0 its raster, +80 the filter byte.
namespace texture_rd {
inline constexpr s32 kRaster = 0;
inline constexpr s32 kFilter = 80;
}  // namespace texture_rd
// The guest functions the render callbacks install (instance / render callbacks of the PTank formats).
inline constexpr u32 kPtank2DLock = 0x477470u;      // sub_477470
inline constexpr u32 kPtank2DRender = 0x477150u;    // sub_477150
inline constexpr u32 kPtank3DInstance = 0x479590u;  // sub_479590
inline constexpr u32 kPtank3DRender = 0x479170u;    // sub_479170
// The PTank 2D lock record sub_477470 fills: which components are locked, then their {pointer, stride} pairs.
namespace ptank_lock {
inline constexpr s32 kWant16A = 0, kWant16B = 4, kWant4 = 8, kWant8 = 12;  // u32: 1 = locked
inline constexpr s32 kPair16A = 16, kPair16B = 24, kPair4 = 32, kPair8 = 40;  // {u32 pointer, u32 stride}
}  // namespace ptank_lock
// A {pointer, stride} stream (the fills' first argument).
namespace pt_stream {
inline constexpr s32 kPtr = 0;
inline constexpr s32 kStride = 4;
}  // namespace pt_stream
}  // namespace rwb_view
using namespace rwb_view;

// ==================================================================================================================
// PS2All / PDS bridges
// ==================================================================================================================

// 0x0046FB70 sub_46FB70 -- 12 bytes; leaf frame (no stack)
// sub_46FB70 [PDS 2D bridge entry](_, pair): sub_46F400(pair[0], pair[1]) as a tail call. One block of 3.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: frame/spills (own frame)).
void sub_46FB70(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::enter, hg::lw;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x0046fb70
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a0, a1, 0);  // a0 = pair[0]
    lw(a1, a1, 4);  // a1 = pair[1]
    gen::fn_sub_46F400_0046f400(ctx);  // tail call
}

// 0x00470780 sub_470780 -- 12 bytes; leaf frame (no stack)
// sub_470780 [PDS 2D bridge entry](_, pair): sub_470200(pair[0], pair[1]) as a tail call. One block of 3.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: frame/spills (own frame)).
void sub_470780(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::enter, hg::lw;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00470780
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a0, a1, 0);  // a0 = pair[0]
    lw(a1, a1, 4);  // a1 = pair[1]
    gen::fn_sub_470200_00470200(ctx);  // tail call
}

// 0x00471210 sub_471210 -- 12 bytes; leaf frame (no stack)
// sub_471210 [PDS 2D bridge entry](_, pair): sub_470E10(pair[0], pair[1]) as a tail call. One block of 3.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: frame/spills (own frame)).
void sub_471210(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::enter, hg::lw;
    Gpr a0{ctx, 4}, a1{ctx, 5};
    // 0x00471210
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a0, a1, 0);  // a0 = pair[0]
    lw(a1, a1, 4);  // a1 = pair[1]
    gen::fn_sub_470E10_00470e10(ctx);  // tail call
}

// 0x00472130 sub_472130 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_472130 [PDS skin bridge: RpMeshPS2AllBridgeCallBack](pipe): when a skin matrix palette is pending (0x95DE38),
// its upload
// sub_46B8E0(pipe) first; then RpMeshPS2AllBridgeCallBack(pipe), whose $v0 is the result.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: the hand version terminated the host on a random world).
void sub_472130(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00472130
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = hi(kSkinPalettePending);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, v0, lo(kSkinPalettePending));  // the pending skin matrix palette
    s0 = a0;  // s0 = pipe
    if (v0 != 0) {
        // 0x0047214c: sub_46B8E0(pipe): upload it
        charge(ctx, 2);
        jal(ctx, 0x47214Cu, gen::fn_sub_46B8E0_0046b8e0);
    }
    // 0x00472154: the material bridge
    charge(ctx, 6);
    a0 = s0;
    jal(ctx, 0x472154u, gen::fn_RpMeshPS2AllBridgeCallBack_004a0e00);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00472170 sub_472170 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_472170 [PDS skin bridge: matfxBridgeBumpMap](pipe): when a skin matrix palette is pending (0x95DE38), its upload
// sub_46B8E0(pipe) first; then matfxBridgeBumpMap(pipe), whose $v0 is the result.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: the hand version terminated the host on a random world).
void sub_472170(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00472170
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = hi(kSkinPalettePending);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, v0, lo(kSkinPalettePending));  // the pending skin matrix palette
    s0 = a0;  // s0 = pipe
    if (v0 != 0) {
        // 0x0047218c: sub_46B8E0(pipe): upload it
        charge(ctx, 2);
        jal(ctx, 0x47218Cu, gen::fn_sub_46B8E0_0046b8e0);
    }
    // 0x00472194: the material bridge
    charge(ctx, 6);
    a0 = s0;
    jal(ctx, 0x472194u, gen::fn_matfxBridgeBumpMap_0046c5b0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004721B0 sub_4721B0 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4721B0 [PDS skin bridge: matfxBridgeEnvMap](pipe): when a skin matrix palette is pending (0x95DE38), its upload
// sub_46B8E0(pipe) first; then matfxBridgeEnvMap(pipe), whose $v0 is the result.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: the hand version terminated the host on a random world).
void sub_4721B0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004721b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = hi(kSkinPalettePending);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, v0, lo(kSkinPalettePending));  // the pending skin matrix palette
    s0 = a0;  // s0 = pipe
    if (v0 != 0) {
        // 0x004721cc: sub_46B8E0(pipe): upload it
        charge(ctx, 2);
        jal(ctx, 0x4721CCu, gen::fn_sub_46B8E0_0046b8e0);
    }
    // 0x004721d4: the material bridge
    charge(ctx, 6);
    a0 = s0;
    jal(ctx, 0x4721D4u, gen::fn_matfxBridgeEnvMap_0046cd90);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004721F0 sub_4721F0 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4721F0 [PDS skin bridge: matfxBridgeBumpEnvMap](pipe): when a skin matrix palette is pending (0x95DE38), its
// upload
// sub_46B8E0(pipe) first; then matfxBridgeBumpEnvMap(pipe), whose $v0 is the result.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: the hand version terminated the host on a random world).
void sub_4721F0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004721f0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = hi(kSkinPalettePending);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, v0, lo(kSkinPalettePending));  // the pending skin matrix palette
    s0 = a0;  // s0 = pipe
    if (v0 != 0) {
        // 0x0047220c: sub_46B8E0(pipe): upload it
        charge(ctx, 2);
        jal(ctx, 0x47220Cu, gen::fn_sub_46B8E0_0046b8e0);
    }
    // 0x00472214: the material bridge
    charge(ctx, 6);
    a0 = s0;
    jal(ctx, 0x472214u, gen::fn_matfxBridgeBumpEnvMap_0046d6f0);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00472230 sub_472230 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_472230 [PDS skin bridge: matfxBridgeDual](pipe): when a skin matrix palette is pending (0x95DE38), its upload
// sub_46B8E0(pipe) first; then matfxBridgeDual(pipe), whose $v0 is the result.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: the hand version terminated the host on a random world).
void sub_472230(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00472230
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = hi(kSkinPalettePending);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, v0, lo(kSkinPalettePending));  // the pending skin matrix palette
    s0 = a0;  // s0 = pipe
    if (v0 != 0) {
        // 0x0047224c: sub_46B8E0(pipe): upload it
        charge(ctx, 2);
        jal(ctx, 0x47224Cu, gen::fn_sub_46B8E0_0046b8e0);
    }
    // 0x00472254: the material bridge
    charge(ctx, 6);
    a0 = s0;
    jal(ctx, 0x472254u, gen::fn_matfxBridgeDual_0046e170);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00473340 sub_473340 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_473340 [PDS skin bridge: matfxBridgeUvTransform](pipe): when a skin matrix palette is pending (0x95DE38), its
// upload
// sub_46B8E0(pipe) first; then matfxBridgeUvTransform(pipe), whose $v0 is the result.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: the hand version terminated the host on a random world).
void sub_473340(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00473340
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = hi(kSkinPalettePending);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, v0, lo(kSkinPalettePending));  // the pending skin matrix palette
    s0 = a0;  // s0 = pipe
    if (v0 != 0) {
        // 0x0047335c: sub_46B8E0(pipe): upload it
        charge(ctx, 2);
        jal(ctx, 0x47335Cu, gen::fn_sub_46B8E0_0046b8e0);
    }
    // 0x00473364: the material bridge
    charge(ctx, 6);
    a0 = s0;
    jal(ctx, 0x473364u, gen::fn_matfxBridgeUvTransform_00472270);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00473380 sub_473380 -- 60 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_473380 [PDS skin bridge: matfxBridgeDualUvTransform](pipe): when a skin matrix palette is pending (0x95DE38),
// its upload
// sub_46B8E0(pipe) first; then matfxBridgeDualUvTransform(pipe), whose $v0 is the result.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: the hand version terminated the host on a random world).
void sub_473380(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00473380
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = hi(kSkinPalettePending);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, v0, lo(kSkinPalettePending));  // the pending skin matrix palette
    s0 = a0;  // s0 = pipe
    if (v0 != 0) {
        // 0x0047339c: sub_46B8E0(pipe): upload it
        charge(ctx, 2);
        jal(ctx, 0x47339Cu, gen::fn_sub_46B8E0_0046b8e0);
    }
    // 0x004733a4: the material bridge
    charge(ctx, 6);
    a0 = s0;
    jal(ctx, 0x4733A4u, gen::fn_matfxBridgeDualUvTransform_00472970);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004A26D0 HandleUnexpected__FP12ThrowContextP13ExceptionInfoP16ex_specificationPc -- 164 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// HandleUnexpected__... [PS2All resEntry header](owner, out, size, tag) (a stray C++ runtime symbol on a RenderWare
// function, kept as the IDA name): opens a 128-qw VIF packet, allocates the entry's DMA block (sub_4D5FE0(size + 24,
// 0)) into *out and fills its header {0, 0, size, owner->+8, 0, tag}; returns the entry (0 when the allocation
// failed).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void HandleUnexpected__FP12ThrowContextP13ExceptionInfoP16ex_specificationPc(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a26d0
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;  // s3 = owner
    sq(s1, sp, 0x10);
    s2 = a1;  // s2 = out
    sq(s0, sp, 0x0);
    s1 = a2;  // s1 = size
    s0 = a3;  // s0 = tag
    a0 = 0;
    a1 = 128;
    jal(ctx, 0x4A26FCu, gen::fn__rwDMAOpenVIFPkt_004d59d0);  // _rwDMAOpenVIFPkt(0, 128)
    a0 = addiu(s1, 24);  // sub_4D5FE0(size + 24, 0): the entry's block
    a1 = 0;
    jal(ctx, 0x4A2708u, gen::fn_sub_4D5FE0_004d5fe0);
    sw(v0, s2, 0);  // *out = the entry
    lw(v0, s2, 0);
    sw(zero, v0, res_hdr::kWord4);
    lw(v0, s2, 0);
    sw(zero, v0, res_hdr::kWord0);
    lw(v1, s3, 8);  // owner->+8
    lw(v0, s2, 0);
    sw(v1, v0, res_hdr::kOwnerData);
    lw(v0, s2, 0);
    sw(s1, v0, res_hdr::kSize);
    lw(v0, s2, 0);
    sw(zero, v0, res_hdr::kWord16);
    lw(v0, s2, 0);
    sw(s0, v0, res_hdr::kTag);
    lw(v0, s2, 0);  // return the entry
    if (v0 == 0) {
        // 0x004a2754: none: 0
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x004a2758 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u32 HandleUnexpected__FP12ThrowContextP13ExceptionInfoP16ex_specificationPc(EEContext& ctx, u64 owner, u64 out, u64 size,
                                                                           u64 tag) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(owner));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(out));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(size));
    ee::core::set_gpr64(ctx, GPR_A3, static_cast<u64>(tag));
    HandleUnexpected__FP12ThrowContextP13ExceptionInfoP16ex_specificationPc(ctx);
    return static_cast<u32>(ee::core::gpr64(ctx, GPR_V0));
}

// ==================================================================================================================
// DMA queue
// ==================================================================================================================

// [_rwDMAFlushPURefs] Every resource entry referenced since the last flush (the ring _rwDMAAddPURef fills: u16 read and
// write indices, kGpPuRefSlots slots) becomes queue fences of type 0x42 with its quadword count, at most 0xFFFF per entry
// (a count above that is split); the entry's count is cleared and both indices reset to 0.
void sub_4D4280(EEContext& ctx) {
    Regs r{ctx};
    enter(ctx, 10);
    Frame f(ctx, 80);
    f.sd(GPR_RA, 64);
    f.sq(GPR_S3, 48);
    f.sq(GPR_S2, 32);
    f.sq(GPR_S1, 16);
    f.sq(GPR_S0, 0);
    u32 index = guest::load<u16>(ctx, gpv(ctx, kGpPuRefRead));
    const u32 end = guest::load<u16>(ctx, gpv(ctx, kGpPuRefWrite));
    r.d(GPR_S3, index);
    r.d(GPR_S1, end);
    if (index != end) {
        charge(ctx, 2);
        guest::store<u16>(ctx, gpv(ctx, kGpPuRefRead), 0);
        guest::store<u16>(ctx, gpv(ctx, kGpPuRefWrite), 0);
        for (;;) {
            charge(ctx, 8);
            const u32 slot = (index & 0xFFFFu) << 2;
            r.w(GPR_V1, lw(ctx, gpv(ctx, kGpPuRefRing)));
            r.d(GPR_A0, index & 0xFFFFu);
            r.w(GPR_S0, slot);
            r.w(GPR_V1, r.get32(GPR_V1) + slot);
            const u32 res = lw(ctx, r.get32(GPR_V1));
            r.w(GPR_V1, res);
            s64 count = static_cast<s32>(lw(ctx, res + 4));
            r.d(GPR_S2, static_cast<u64>(count));
            sw(ctx, res + 4, 0);
            while (count > 0) {
                charge(ctx, 5);
                r.w(GPR_V0, lw(ctx, gpv(ctx, kGpPuRefRing)));
                r.d(GPR_AT, count < 0x10000 ? 1 : 0);
                r.w(GPR_V1, slot + r.get32(GPR_V0));
                if (count < 0x10000) {
                    charge(ctx, 1);
                    r.d(GPR_V0, static_cast<u64>(count));
                } else {
                    charge(ctx, 2);
                    r.d(GPR_V0, 0xFFFFu);
                }
                charge(ctx, 8);
                r.w(GPR_A0, lw(ctx, r.get32(GPR_V1)));  // the ring slot again: the queue fence of this entry
                r.w(GPR_V0, r.get32(GPR_V0) << 12);
                r.d(GPR_A1, r.get(GPR_V0) | 0x42u);
                jal(ctx, 0x4D42F8u, gen::fn__rwDMAAddPkt_004d5000);
                r.w(GPR_V1, static_cast<u32>(count) - 32768u);
                count = static_cast<s32>(r.get32(GPR_V1) - 32767u);
                r.d(GPR_S2, static_cast<u64>(count));
                if (count > 0) backedge(ctx);
            }
            charge(ctx, 5);
            const u32 slots = guest::load<u16>(ctx, gpv(ctx, kGpPuRefSlots));
            r.d(GPR_V1, slots);
            r.w(GPR_A0, index + 1);
            index = (index + 1) & 0xFFFFu;
            r.d(GPR_S3, index);
            if (index == slots) {
                charge(ctx, 1);
                index = 0;
                r.d(GPR_S3, 0);
            }
            charge(ctx, 3);
            r.d(GPR_V1, index);
            if (index == end) break;
            backedge(ctx);
        }
    }
    charge(ctx, 7);
}

// Swap the build half once the DMA side is idle: when a swap is pending (kGpQueuePending) it is cleared, the handler
// is run inline if the queue still holds entries and no transfer is in flight, then the halves are swapped if the
// current half holds a queue.
void _rwDMAWaitQueue(EEContext& ctx) {
    Regs r{ctx};
    enter(ctx, 5);
    Frame f(ctx, 16);
    f.sd(GPR_RA, 0);
    auto lbu3 = [&](s32 off) {
        const u32 v = guest::load<u8>(ctx, gpv(ctx, off));
        r.d(GPR_V1, v);
        return v;
    };
    // The current half's queue start against the write pointer: a non-empty queue swaps.
    auto half_has_queue = [&] {
        charge(ctx, 8);
        const u32 half = guest::load<u8>(ctx, gpv(ctx, kGpHalfIndex));
        r.d(GPR_A1, half);
        r.w(GPR_A0, gpv(ctx, kGpHalfStart));
        r.w(GPR_V1, lw(ctx, gpv(ctx, kGpQueueWrite)));
        r.w(GPR_A1, half << 2);
        r.w(GPR_A0, r.get32(GPR_A0) + (half << 2));
        r.w(GPR_A0, lw(ctx, r.get32(GPR_A0)));
        return r.get(GPR_A0) != r.get(GPR_V1);
    };
    auto queue_empty = [&] {
        charge(ctx, 4);
        r.w(GPR_A0, lw(ctx, gpv(ctx, kGpQueueHead)));
        r.w(GPR_V1, lw(ctx, gpv(ctx, kGpQueueTail)));
        return r.get(GPR_A0) == r.get(GPR_V1);
    };
    if (lbu3(kGpQueuePending) == 0) {
        charge(ctx, 1);
        charge(ctx, 2);
        return;
    }
    charge(ctx, 3);
    const bool busy_b = lbu3(kGpDmaBusyB) != 0;
    guest::store<u8>(ctx, gpv(ctx, kGpQueuePending), 0);
    bool kick_path = busy_b;
    if (!kick_path) {
        charge(ctx, 3);
        kick_path = lbu3(kGpDmaBusyA) != 0;
    }
    if (!kick_path) {
        charge(ctx, 3);
        kick_path = lbu3(kGpDmaBusyB) != 0;
    }
    if (!kick_path) {
        kick_path = !queue_empty();
    }
    if (!kick_path) {
        // Nothing in flight and nothing queued: swap straight away when the half holds a queue.
        if (half_has_queue()) {
            charge(ctx, 4);
            jal(ctx, 0x4D5458u, gen::fn__rwDMAForceBufferSwap_004d4df0);
            charge(ctx, 2);
            return;
        }
        charge(ctx, 1);
        charge(ctx, 2);
        return;
    }
    // Entries left or a transfer in flight: run the handler when the queue holds entries and nothing is in flight.
    if (!queue_empty()) {
        charge(ctx, 3);
        if (lbu3(kGpDmaBusyB) == 0) {
            charge(ctx, 3);
            if (lbu3(kGpDmaBusyA) == 0) {
                charge(ctx, 3);
                if (lbu3(kGpDmaBusyB) == 0) {
                    charge(ctx, 2);
                    r.d(GPR_A0, ~0ull);
                    jal(ctx, 0x4D549Cu, gen::fn__rwDMAHandler_004d4350);
                }
            }
        }
    }
    if (half_has_queue()) {
        charge(ctx, 2);
        jal(ctx, 0x4D54C4u, gen::fn__rwDMAForceBufferSwap_004d4df0);
    }
    charge(ctx, 1);
    charge(ctx, 2);
}

// The flip request: a 24-qw VIF packet (a DMA `ret`-style tag pair, an A+D head writing reg 0x7F, a 0x13000000 code
// and 20 zero quadwords), the fence 64 (odd flag 65) of `flip_data` through _rwDMAAddPkt, then with interrupts masked
// the flip count and, when no transfer is in flight, the handler run inline. When a swap was already pending the
// halves are swapped first.
void _rwDMAReqFlip(EEContext& ctx, u64 flip_data, u64 flags) {
    Regs r{ctx};
    enter(ctx, 36);
    Frame f(ctx, 48);
    f.sd(GPR_RA, 32);
    f.sq(GPR_S1, 16);
    f.sq(GPR_S0, 0);
    r.d(GPR_S1, flip_data);
    r.d(GPR_S0, flags);
    r.d(GPR_A0, 0);
    r.d(GPR_A1, 24);
    open_vif(ctx, 0x4D528Cu);
    // Head: DMA tag {cnt 23, VIF codes 0x50000002 (DIRECT 2) / 0x11000000 (FLUSH)}, the A+D tag, reg 0x7F data 0,
    // a 0x13000000 code word (FLUSHA), then 20 zero quadwords.
    r.w(GPR_V0, 0x50000000u);
    r.w(GPR_V1, 0x11000000u);
    r.w(GPR_V0, 0x50000002u);
    const u32 p = spr_ptr(ctx);
    r.w(GPR_A1, p);
    r.d(GPR_A0, 0x5000000200000000ull);
    r.w(GPR_V0, 0x10000000u);
    r.d(GPR_A0, 0x5000000211000000ull);
    r.d(GPR_V1, 0x10000017u);
    r.q(GPR_A2, 0x10000017u, 0x5000000211000000ull);
    r.d(GPR_V1, 0x1000000000000000ull);
    r.d(GPR_A0, kGifAd);
    r.d(GPR_V0, 0x8001u);
    sq(ctx, p, r.get_q(GPR_A2));
    r.d(GPR_V0, kGifAdTag1);
    r.q(GPR_V0, kGifAdTag1, kGifAd);
    sq(ctx, p + 16, r.get_q(GPR_V0));
    r.d(GPR_V1, 0);
    r.d(GPR_V0, 127);
    r.q(GPR_V0, 0, 127);
    sq(ctx, p + 32, r.get_q(GPR_V0));
    r.w(GPR_V0, 0x13000000u);
    r.q(GPR_V0, 0, 0x13000000u);
    sq(ctx, p + 48, r.get_q(GPR_V0));
    r.w(GPR_A0, p + 64);
    r.d(GPR_V0, 0);
    r.q(GPR_V1, 0, 0);
    r.d(GPR_A1, 0);
    u32 q = p + 64;
    for (u32 n = 0;;) {  // 20 zero quadwords, 5 per iteration
        charge(ctx, 9);
        for (u32 k = 0; k < 5; ++k) sq(ctx, q + 16 * k, 0, 0);
        n += 5;
        r.d(GPR_A1, n);
        r.d(GPR_V0, n < 20 ? 1 : 0);
        q += 80;
        r.w(GPR_A0, q);
        if (n >= 20) break;
        backedge(ctx);
    }
    charge(ctx, 3);
    const u32 pending = guest::load<u8>(ctx, gpv(ctx, kGpQueuePending));
    r.d(GPR_V0, pending);
    set_spr_ptr(ctx, q);
    if (pending != 0) {
        charge(ctx, 4);
        jal(ctx, 0x4D53C4u, gen::fn__rwDMAForceBufferSwap_004d4df0);
        r.d(GPR_V0, r.get(GPR_S0) & 0xFFu);
        backedge(ctx);
    } else {
        charge(ctx, 1);
        r.d(GPR_V0, r.get(GPR_S0) & 0xFFu);
    }
    charge(ctx, 4);
    r.d(GPR_V1, 1);
    const bool odd = (r.get(GPR_V0) & 1u) != 0;
    r.d(GPR_V0, r.get(GPR_V0) & 1u);
    guest::store<u8>(ctx, gpv(ctx, kGpQueuePending), 1);
    r.d(GPR_A0, r.get(GPR_S1));
    if (odd) {
        charge(ctx, 5);
        r.d(GPR_A1, 65);
        jal(ctx, 0x4D5348u, gen::fn__rwDMAAddPkt_004d5000);
    } else {
        charge(ctx, 4);
        r.d(GPR_A1, 64);
        jal(ctx, 0x4D535Cu, gen::fn__rwDMAAddPkt_004d5000);
    }
    r.d(GPR_V1, 0x10000u);
    for (;;) {  // di until Status.EIE reads clear
        charge(ctx, 7);
        rt::di(ctx);
        rt::sync(ctx, 16);
        rt::mfc0(ctx, GPR_A0, 12);
        r.d(GPR_A0, r.get(GPR_A0) & r.get(GPR_V1));
        if (r.get(GPR_A0) == 0) break;
        backedge(ctx);
    }
    charge(ctx, 6);
    const u32 flips = guest::load<u8>(ctx, gpv(ctx, kGpFlipCount)) + 1u;
    r.d(GPR_V1, flips);
    guest::store<u8>(ctx, gpv(ctx, kGpFlipCount), static_cast<u8>(flips));
    auto lbu3 = [&](s32 off) {
        const u32 v = guest::load<u8>(ctx, gpv(ctx, off));
        r.d(GPR_V1, v);
        return v;
    };
    if (lbu3(kGpDmaBusyB) == 0) {
        charge(ctx, 3);
        if (lbu3(kGpDmaBusyA) == 0) {
            charge(ctx, 3);
            if (lbu3(kGpDmaBusyB) == 0) {
                charge(ctx, 2);
                r.d(GPR_A0, ~0ull);
                jal(ctx, 0x4D53B4u, gen::fn__rwDMAHandler_004d4350);
            }
        }
    }
    charge(ctx, 2);
    rt::ei(ctx);
    charge(ctx, 5);
}

// ==================================================================================================================
// Camera / raster
// ==================================================================================================================

u32 SkyRasterShowRaster(EEContext& ctx) {
    Regs r{ctx};
    enter(ctx, 5);
    Frame f(ctx, 16);
    f.sd(GPR_RA, 0);
    const u64 pending = ld(ctx, gpv(ctx, kGpShowRasterPending));
    r.d(GPR_V0, pending);
    if (pending != 0) {
        charge(ctx, 3);
        sd(ctx, gpv(ctx, kGpShowRasterPending), 0);
        sw(ctx, gpv(ctx, kGpTexFlushPending), 0);
        backedge(ctx);
    }
    charge(ctx, 15);
    jal(ctx, 0x4D9474u, gen::fn_sub_4F0C60_004f0c60);
    // The flip: _rwDMAReqFlip(&flip data, frame count & 0xFF) with the frame count incremented.
    const u32 frame = lw(ctx, gpv(ctx, kGpFrameCount));
    r.w(GPR_V1, frame);
    r.w(GPR_A0, 0x960000u);
    r.w(GPR_A0, kFlipPacketData);
    r.w(GPR_V0, frame + 1);
    r.d(GPR_A1, frame & 0xFFu);
    sw(ctx, gpv(ctx, kGpFrameCount), frame + 1);
    jal(ctx, 0x4D9490u, gen::fn__rwDMAReqFlip_004d5270);
    jal(ctx, 0x4D9498u, gen::fn_sub_4E2F10_004e2f10);
    // Any of the four deferred-operation words set -> the next frame waits for vsync.
    bool deferred = false;
    for (u32 k = 0; k < 4; ++k) {
        if (k != 0) charge(ctx, 4);
        r.w(GPR_V0, 0x960000u);
        const u32 w = lw(ctx, kDeferredOps + 4 * k);
        r.w(GPR_V0, w);
        if (w != 0) {
            deferred = true;
            break;
        }
    }
    if (deferred) {
        charge(ctx, 3);
        r.d(GPR_V0, 1);
        sw(ctx, gpv(ctx, kGpNeedVsync), 1);
        backedge(ctx);
    }
    charge(ctx, 2);
    r.d(GPR_V0, 1);
    charge(ctx, 3);
    return 1;
}

// 0x004D8E80 sub_4D8E80 -- 192 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4D8E80 [SkyCameraEndUpdate](_, camera): a camera whose frame raster (camera +96) is a camera texture (type 5 in
// the raster's type byte +32) gets a TEXFLUSH A+D packet, and when that raster also has both private flags 0x90 (byte
// +35) it is copied (sub_4E3640); an owed TEXFLUSH flag is cleared. Returns 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4D8E80(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::dsll32, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq,
          hg::lui, hg::lw, hg::pcpyld, hg::sd, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004d8e80
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 5;  // a camera texture
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a1, camera_rd::kRaster);
    lbu(v1, v1, raster_rd::kTypeByte);
    v1 = v1 & 0x7;
    s0 = addiu(a1, camera_rd::kRaster);  // s0 = &camera->raster
    if (v1 == v0) {
        // 0x004d8eb8: a 2-qw A+D packet {GIF tag (NLOOP 1, EOP, NREG 1, A+D), TEXFLUSH = 0}
        charge(ctx, 24);
        a0 = lui(0x8000);
        a1 = 2;
        jal(ctx, 0x4D8EBCu, gen::fn__rwDMAOpenVIFPkt_004d59d0);
        v0 = 0x10000000;
        a0 = kGifAd;
        v1 = dsll32(v0, 0);
        v0 = 0x8001;
        v0 = v0 | v1;  // kGifAdTag1
        lw(v1, gp, kGpSprWritePtr);
        pcpyld(a1, a0, v0);
        v0 = kGsTexflush;
        a0 = 0;
        pcpyld(a0, v0, a0);
        v0 = 144;  // both private flags 0x90
        sq(a1, v1, 0);
        sq(a0, v1, 16);
        lw(v1, gp, kGpSprWritePtr);
        v1 = addiu(v1, 32);
        sw(v1, gp, kGpSprWritePtr);  // the write pointer past the packet
        lw(a0, s0, 0);
        lbu(v1, a0, raster_rd::kFormatByte);
        v1 = v1 & 0x90;
        if (v1 != v0) {
            backedge(ctx);
            // 0x004d8ea4 (the shared tail, written out on this path): the owed TEXFLUSH flag
            charge(ctx, 1);
            lw(v0, gp, kGpTexFlushPending);
        } else {
            // 0x004d8f18: sub_4E3640(raster): copy the camera texture
            charge(ctx, 4);
            jal(ctx, 0x4D8F18u, gen::fn_sub_4E3640_004e3640);
            lw(v0, gp, kGpTexFlushPending);
            backedge(ctx);
        }
    } else {
        // 0x004d8ea4: the owed TEXFLUSH flag
        charge(ctx, 1);
        lw(v0, gp, kGpTexFlushPending);
    }
    // 0x004d8ea8
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x004d8f28: cleared
        charge(ctx, 2);
        sw(zero, gp, kGpTexFlushPending);
        backedge(ctx);
    }
    // 0x004d8eb0: return 1
    charge(ctx, 2);
    v0 = 1;
    // 0x004d8f30
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// [clear the whole frame raster] sub_4E4800(0, rect) with the rectangle {0, 0, width, height} of the camera's frame
// raster in the frame at +16 (nothing when there is no raster).
void sub_4E4E40(EEContext& ctx) {
    Regs r{ctx};
    enter(ctx, 5);
    Frame f(ctx, 32);
    f.sd(GPR_RA, 0);
    const u32 raster = lw(ctx, gpv(ctx, kGpFrameRaster));
    r.w(GPR_V1, raster);
    r.d(GPR_V0, 0);
    if (raster != 0) {
        charge(ctx, 9);
        sw(ctx, f.at(20), 0);
        r.d(GPR_A0, 0);
        sw(ctx, f.at(16), 0);
        r.w(GPR_A1, f.at(16));
        const u32 width = lw(ctx, raster + 12);
        r.w(GPR_V0, width);
        sw(ctx, f.at(24), width);
        const u32 height = lw(ctx, raster + 16);
        r.w(GPR_V0, height);
        sw(ctx, f.at(28), height);
        jal(ctx, 0x4E4E70u, gen::fn_sub_4E4800_004e4800);
    }
    charge(ctx, 3);
}

namespace {

// The interlace field wait shared by the raster packets: with kGpInterlace set, `di` until Status.EIE reads clear,
// then parity = (field parity ^ (flip count & 1)) ^ DMA busy flag A, `ei`; 0 otherwise. `tmp` is the register the
// body uses for the Status read and the parity terms ($a0 / $a1), `tmp2` the second term register.
u64 field_parity_wait(EEContext& ctx, unsigned tmp, unsigned tmp2) {
    Regs r{ctx};
    charge(ctx, 1);
    r.d(GPR_V1, 0x10000u);
    for (;;) {
        charge(ctx, 7);
        rt::di(ctx);
        rt::sync(ctx, 16);
        rt::mfc0(ctx, tmp, 12);
        r.d(tmp, r.get(tmp) & r.get(GPR_V1));
        if (r.get(tmp) == 0) break;
        backedge(ctx);
    }
    charge(ctx, 9);
    const u32 parity = guest::load<u8>(ctx, gpv(ctx, kGpFieldParity));
    r.d(tmp2, parity);
    const u32 flips = guest::load<u8>(ctx, gpv(ctx, kGpFlipCount));
    r.d(tmp, flips);
    const u32 busy = guest::load<u8>(ctx, gpv(ctx, kGpDmaBusyA));
    r.d(GPR_V1, busy);
    r.d(tmp, flips & 1u);
    r.d(tmp, parity ^ (flips & 1u));
    const u64 v = busy ^ (parity ^ (flips & 1u));
    r.d(GPR_V1, sx(static_cast<u32>(v)));
    rt::ei(ctx);
    return r.get(GPR_V1);
}

}  // namespace

// [raster draw-environment packet] FRAME_1 (the frame shadow of this field's draw environment), ZBUF_1, TEST_1 (Z test
// always, alpha/destination tests off) and DTHE; mode 2 masks Z writes and dithers below 24 bpp, every other mode
// masks the colour (a Z-only pass). Then ALPHA_1 = 0x44, the prim shadow's bits 5..8 = 3 (old value saved) and
// XYOFFSET_1 from the frame raster's offsets with the field's half-line.
void sub_4E4180(EEContext& ctx, u64 mode) {
    Regs r{ctx};
    enter(ctx, 7);
    Frame f(ctx, 32);
    f.sd(GPR_RA, 16);
    f.sq(GPR_S0, 0);
    const u32 odd = lw(ctx, gpv(ctx, kGpFrameCount)) & 1u;
    r.d(GPR_V0, odd);
    r.d(GPR_S0, mode);
    if (odd != 0) {
        charge(ctx, 4);
        r.w(GPR_V0, 0x960000u);
        r.d(GPR_V0, ld(ctx, 0x9649F0u));
    } else {
        charge(ctx, 3);
        r.w(GPR_V0, 0x960000u);
        r.d(GPR_V0, ld(ctx, 0x964B60u));
    }
    sd(ctx, gpv(ctx, kGpFrame1), r.get(GPR_V0));
    charge(ctx, 13);
    r.w(GPR_A0, 0x80000000u);
    r.d(GPR_A1, 32);
    open_vif(ctx, 0x4E41BCu);
    // The A+D tag: six registers follow.
    r.w(GPR_V1, 0x10000000u);
    r.d(GPR_A1, kGifAd);
    r.d(GPR_A0, 0x1000000000000000ull);
    r.d(GPR_V1, 0x8006u);
    r.d(GPR_V1, 0x1000000000008006ull);
    const u32 p = spr_ptr(ctx);
    r.w(GPR_A0, p);
    r.q(GPR_A1, 0x1000000000008006ull, kGifAd);
    r.d(GPR_V1, 2);
    sq(ctx, p, r.get_q(GPR_A1));
    if (mode == 2) {
        charge(ctx, 42);
        const u64 frame = ld(ctx, gpv(ctx, kGpFrame1));
        r.d(GPR_T4, frame);
        r.d(GPR_V1, 0xFFFFu);
        r.d(GPR_V1, 0xFFFF0000u);
        r.w(GPR_A1, 0xFFFA0000u);
        const u32 q = spr_ptr(ctx);
        r.w(GPR_T3, q);
        r.d(GPR_A2, 0xFFFFFFFFu);
        r.d(GPR_V1, 1);
        r.d(GPR_A1, 0xFFFFFFFFFFFABFFEull);
        r.d(GPR_T2, kGsFrame1);
        r.d(GPR_T0, 0x100000000ull);
        r.d(GPR_T1, kGsZbuf1);
        r.w(GPR_A0, 0x30000u);
        r.d(GPR_A2, frame & 0xFFFFFFFFu);  // FRAME_1: FBMSK 0
        r.d(GPR_A3, kGsTest1);
        r.q(GPR_A2, frame & 0xFFFFFFFFu, kGsFrame1);
        sq(ctx, q + 16, r.get_q(GPR_A2));
        r.q(GPR_A1, 0xFFFFFFFFFFFABFFEull, 0);
        const u64 zbuf = ld(ctx, gpv(ctx, kGpZbuf1));
        r.d(GPR_T2, zbuf);
        r.d(GPR_A2, kGsDthe);
        r.d(GPR_T0, zbuf | 0x100000000ull);  // ZBUF_1: ZMSK
        r.q(GPR_T0, zbuf | 0x100000000ull, kGsZbuf1);
        sq(ctx, q + 32, r.get_q(GPR_T0));
        const u64 test = ld(ctx, gpv(ctx, kGpTest1));
        r.d(GPR_T0, test);
        r.d(GPR_A1, test & 0xFFFFFFFFFFFABFFEull);
        r.d(GPR_A0, (test & 0xFFFFFFFFFFFABFFEull) | 0x30000u);  // TEST_1: ZTE, ZTST always
        r.q(GPR_A0, r.get(GPR_A0), kGsTest1);
        sq(ctx, q + 48, r.get_q(GPR_A0));
        const u32 q2 = spr_ptr(ctx) + 64;
        r.w(GPR_A0, q2);
        const u32 raster = lw(ctx, gpv(ctx, kGpFrameRaster));
        r.w(GPR_A1, raster);
        set_spr_ptr(ctx, q2);
        const u32 depth = lw(ctx, raster + 20);
        r.w(GPR_A1, depth);
        r.d(GPR_AT, depth < 24 ? 1 : 0);
        if (depth >= 24) r.d(GPR_V1, 0);  // DTHE: dither below 24 bpp
        r.q(GPR_A1, r.get(GPR_V1), kGsDthe);
        r.d(GPR_V1, sx(q2));
        sq(ctx, q2, r.get_q(GPR_A1));
        r.w(GPR_V1, spr_ptr(ctx));
        r.w(GPR_A0, r.get32(GPR_V1) + 16);
        set_spr_ptr(ctx, r.get32(GPR_A0));
    } else {
        charge(ctx, 38);
        const u64 zbuf = ld(ctx, gpv(ctx, kGpZbuf1));
        r.d(GPR_A2, zbuf);
        r.d(GPR_V1, 0xFFFFu);
        r.d(GPR_A0, ~1ull);
        r.d(GPR_V1, 0xFFFF0000u);
        const u32 q = spr_ptr(ctx);
        r.w(GPR_T2, q);
        r.d(GPR_A0, 0xFFFFFFFE00000000ull);
        r.d(GPR_V1, 0xFFFFFFFFu);
        r.d(GPR_A1, kGsZbuf1);
        r.d(GPR_V1, 0xFFFFFFFEFFFFFFFFull);
        r.d(GPR_T3, 0);
        r.q(GPR_V1, 0xFFFFFFFEFFFFFFFFull, 0);
        r.d(GPR_A0, zbuf & 0xFFFFFFFEFFFFFFFFull);  // ZBUF_1: Z written
        r.d(GPR_T0, kGsFrame1);
        r.d(GPR_V1, ~0ull);
        r.d(GPR_A2, kGsTest1);
        r.q(GPR_A0, zbuf & 0xFFFFFFFEFFFFFFFFull, kGsZbuf1);
        sq(ctx, q + 16, r.get_q(GPR_A0));
        r.d(GPR_V1, 0xFFFFFFFF00000000ull);
        r.q(GPR_A3, 0xFFFFFFFF00000000ull, 0);
        const u64 frame = ld(ctx, gpv(ctx, kGpFrame1));
        r.d(GPR_T1, frame);
        r.w(GPR_V1, 0xFFFB0000u);
        r.w(GPR_A0, 0x30000u);
        r.d(GPR_V1, 0xFFFFFFFFFFFBBFFEull);
        r.q(GPR_A1, 0xFFFFFFFFFFFBBFFEull, 0);
        r.d(GPR_V1, kGsDthe);
        r.q(GPR_T3, 0, kGsDthe);
        r.d(GPR_V1, frame | 0xFFFFFFFF00000000ull);  // FRAME_1: every colour bit masked
        r.q(GPR_V1, frame | 0xFFFFFFFF00000000ull, kGsFrame1);
        sq(ctx, q + 32, r.get_q(GPR_V1));
        const u64 test = ld(ctx, gpv(ctx, kGpTest1));
        r.d(GPR_V1, test);
        r.d(GPR_V1, test & 0xFFFFFFFFFFFBBFFEull);
        r.d(GPR_V1, (test & 0xFFFFFFFFFFFBBFFEull) | 0x30000u);
        r.q(GPR_V1, r.get(GPR_V1), kGsTest1);
        sq(ctx, q + 48, r.get_q(GPR_V1));
        sq(ctx, q + 64, r.get_q(GPR_T3));  // DTHE 0
        r.w(GPR_V1, spr_ptr(ctx));
        r.w(GPR_A0, r.get32(GPR_V1) + 80);
        set_spr_ptr(ctx, r.get32(GPR_A0));
    }
    charge(ctx, 17);
    r.d(GPR_A1, kGsAlpha1);
    r.d(GPR_V1, 0x44);
    r.q(GPR_A2, 0x44, kGsAlpha1);
    r.d(GPR_V1, sx(r.get32(GPR_A0)));
    r.w(GPR_A1, static_cast<u32>(-481));
    sq(ctx, r.get32(GPR_V1), r.get_q(GPR_A2));  // ALPHA_1 = (Cs - Cd) * As + Cd
    const u64 prim = ld(ctx, gpv(ctx, kGpPrimShadow));
    r.d(GPR_A2, prim);
    r.w(GPR_A0, spr_ptr(ctx));
    const u32 interlace = guest::load<u8>(ctx, gpv(ctx, kGpInterlace));
    r.d(GPR_V1, interlace);
    r.d(GPR_A1, prim & ~0x1E0ull);
    sd(ctx, gpv(ctx, kGpPrimShadowSaved), prim);
    r.w(GPR_A0, r.get32(GPR_A0) + 16);
    r.d(GPR_A1, (prim & ~0x1E0ull) | 0x60u);
    set_spr_ptr(ctx, r.get32(GPR_A0));
    sd(ctx, gpv(ctx, kGpPrimShadow), r.get(GPR_A1));
    u64 parity;
    if (interlace != 0) {
        parity = field_parity_wait(ctx, GPR_A1, GPR_A2);
    } else {
        charge(ctx, 2);
        r.d(GPR_V1, 0);
        parity = 0;
        backedge(ctx);
    }
    // XYOFFSET_1 = the frame raster's (s16 & 0xFFF) offsets in 1/16 pixel, plus half a line on the odd field.
    charge(ctx, 19);
    const u32 raster = lw(ctx, gpv(ctx, kGpFrameRaster));
    r.w(GPR_T0, raster);
    r.d(GPR_A2, parity << 35);
    const u32 dst = r.get32(GPR_A0);
    r.d(GPR_A1, kGsXyoffset1);
    r.d(GPR_V1, sx(dst));
    const u64 ox = static_cast<u64>(core::sext16(guest::load<u16>(ctx, raster + 28))) & 0xFFFu;
    const u64 oy = static_cast<u64>(core::sext16(guest::load<u16>(ctx, raster + 30))) & 0xFFFu;
    r.d(GPR_A3, ox << 4);
    r.d(GPR_A0, oy << 36);
    r.d(GPR_A0, (ox << 4) | (oy << 36) | (parity << 35));
    r.q(GPR_A0, r.get(GPR_A0), kGsXyoffset1);
    sq(ctx, dst, r.get_q(GPR_A0));
    r.w(GPR_V1, spr_ptr(ctx));
    r.w(GPR_A0, r.get32(GPR_V1) + 16);
    set_spr_ptr(ctx, r.get32(GPR_A0));
    charge(ctx, 4);
}

// ==================================================================================================================
// Render state
// ==================================================================================================================

// 0x004D7F60 RpSkyRenderStateSet -- 588 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// RpSkyRenderStateSet(state, value): the game-facing sky render states. 1 DIMX (when enabled: 0 off, 0x55555555 one
// dither matrix, anything else another; a DIMX A+D packet), 2 ALPHA_1 (the low byte A/B/C/D, the FIX byte from bits
// 24..31; packet + shadow), 3 TEST_1 (its low 16 bits replace the shadow's; packet + shadow), 4 a float value (its
// companion word cleared), 5 the alpha-test reference (kept when 1..7). Returns 1, or 0 for an unknown state, a
// value out of range or no packet.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void RpSkyRenderStateSet(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::dsll, hg::dsll32, hg::dsrl32, hg::enter,
          hg::i64, hg::jal, hg::ld, hg::lq, hg::lui, hg::lw, hg::lwc1, hg::pcpyld, hg::sd, hg::slti, hg::sq, hg::sw,
          hg::swc1;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // The shared tails of the original's block layout, written out on each path that reaches them.
    auto reload_ra = [&] {  // 0x004d819c
        charge(ctx, 1);
        ld(ra, sp, 0x10);
    };
    auto return_1 = [&] {  // 0x004d8030
        charge(ctx, 2);
        v0 = 1;
        reload_ra();
    };
    auto return_0 = [&] {  // 0x004d8198
        charge(ctx, 1);
        v0 = 0;
        reload_ra();
    };
    // 0x004d7f60
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 5;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;  // s0 = the value
    if (a0 == v0) {
        // 0x004d8008: state 5: the alpha-test reference, kept when 1..7
        charge(ctx, 3);
        lw(v0, s0, 0);
        if (i64(v0) > 0) {
            // 0x004d8014
            charge(ctx, 3);
            at = slti(v0, 8);
            if (at == 0) {
                return_0();
            } else {
                // 0x004d8020
                charge(ctx, 2);
                sw(v0, gp, kGpAlphaTestRef);
                return_1();
            }
        } else {
            return_0();
        }
    } else {
        // 0x004d7f78
        charge(ctx, 3);
        v0 = 4;
        if (a0 == v0) {
            // 0x004d7ff8: state 4: the float value, its companion word cleared
            charge(ctx, 4);
            sw(zero, gp, kGpRenderStateFSet);
            lwc1(f0, s0, 0);
            swc1(f0, gp, kGpRenderStateF);
            return_1();
        } else {
            // 0x004d7f84
            charge(ctx, 3);
            v0 = 3;
            if (a0 == v0) {
                // 0x004d7fdc: state 3: TEST_1 -- a 2-qw A+D packet
                charge(ctx, 5);
                a0 = lui(0x8000);
                a1 = 2;
                jal(ctx, 0x4D7FE0u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
                if (v0 != 0) {
                    // 0x004d8144: {GIF tag, (shadow & ~0xFFFF | value & 0xFFFF, TEST_1)}, the shadow updated
                    charge(ctx, 21);
                    lw(a2, gp, kGpSprWritePtr);
                    a0 = 0x10000000;
                    v0 = 0x8001;
                    a0 = dsll32(a0, 0);
                    v0 = v0 | a0;  // kGifAdTag1
                    a1 = kGifAd;
                    pcpyld(a1, a1, v0);
                    a0 = lui(0xFFFF);
                    v1 = s0 & 0xFFFF;
                    v0 = kGsTest1;
                    sq(a1, a2, 0);
                    ld(a1, gp, kGpTest1);
                    a0 = a1 & a0;
                    v1 = a0 | v1;
                    pcpyld(v0, v0, v1);
                    sd(v1, gp, kGpTest1);
                    sq(v0, a2, 16);
                    lw(v0, gp, kGpSprWritePtr);
                    v0 = addiu(v0, 32);
                    sw(v0, gp, kGpSprWritePtr);  // the write pointer past the packet
                    backedge(ctx);
                    return_1();
                } else {
                    // 0x004d7ff0: no packet
                    charge(ctx, 2);
                    v0 = 0;
                    reload_ra();
                }
            } else {
                // 0x004d7f90
                charge(ctx, 3);
                a1 = 2;
                if (a0 == a1) {
                    // 0x004d7fc4: state 2: ALPHA_1 -- a 2-qw A+D packet
                    charge(ctx, 4);
                    a0 = lui(0x8000);
                    jal(ctx, 0x4D7FC4u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
                    if (v0 != 0) {
                        // 0x004d80e4: {GIF tag, ((value >> 24 & 0xFF) << 32 | value & 0xFF, ALPHA_1)}, the shadow set
                        charge(ctx, 24);
                        v0 = 0x10000000;
                        a1 = dsll32(s0, 0);
                        v1 = dsll32(v0, 0);
                        a0 = kGifAd;
                        v0 = 0x8001;
                        lw(a2, gp, kGpSprWritePtr);
                        v0 = v0 | v1;  // kGifAdTag1
                        a1 = dsrl32(a1, 0);
                        pcpyld(a3, a0, v0);
                        a0 = 0xFF00;
                        v1 = s0 & 0xFF;
                        a0 = dsll(a0, 16);
                        v0 = kGsAlpha1;
                        a0 = a1 & a0;
                        a0 = dsll(a0, 8);
                        sq(a3, a2, 0);
                        v1 = v1 | a0;
                        pcpyld(v0, v0, v1);
                        sd(v1, gp, kGpAlpha1);
                        sq(v0, a2, 16);
                        lw(v0, gp, kGpSprWritePtr);
                        v0 = addiu(v0, 32);
                        sw(v0, gp, kGpSprWritePtr);  // the write pointer past the packet
                        backedge(ctx);
                        return_1();
                    } else {
                        // 0x004d7fd4: no packet
                        charge(ctx, 2);
                        v0 = 0;
                        reload_ra();
                    }
                } else {
                    // 0x004d7f9c
                    charge(ctx, 3);
                    v0 = 1;
                    if (a0 == v0) {
                        // 0x004d7fb0: state 1: DIMX, when enabled
                        charge(ctx, 3);
                        lw(v0, gp, kGpDimxEnabled);
                        if (v0 != 0) {
                            // 0x004d8038: a 2-qw A+D packet
                            charge(ctx, 4);
                            a0 = lui(0x8000);
                            jal(ctx, 0x4D8038u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
                            if (v0 != 0) {
                                // 0x004d8048: the GIF tag; v1 = the DIMX matrix for the value
                                charge(ctx, 9);
                                lw(a1, gp, kGpSprWritePtr);
                                v0 = 0x10000000;
                                v1 = dsll32(v0, 0);
                                a0 = kGifAd;
                                v0 = 0x8001;
                                v0 = v0 | v1;  // kGifAdTag1
                                pcpyld(v0, a0, v0);
                                sq(v0, a1, 0);
                                if (s0 == 0) {
                                    // 0x004d80d0: off: mode 0, matrix 0
                                    charge(ctx, 3);
                                    sw(zero, gp, kGpDimxMode);
                                    v1 = 0;
                                    backedge(ctx);
                                } else {
                                    // 0x004d806c
                                    charge(ctx, 4);
                                    v0 = 0x55550000;
                                    v0 = v0 | 0x5555;
                                    if (s0 != v0) {
                                        // 0x004d8094: mode 1, matrix 0x6071243571603524
                                        charge(ctx, 8);
                                        v1 = 0x60710000;
                                        v0 = 0x71600000;
                                        a0 = v1 | 0x2435;
                                        v1 = v0 | 0x3524;
                                        a0 = dsll32(a0, 0);
                                        v0 = 1;
                                        v1 = v1 | a0;
                                        sw(v0, gp, kGpDimxMode);
                                    } else {
                                        // 0x004d807c: 0x55555555: mode 0x55555555, matrix 0x1212303012123030
                                        charge(ctx, 6);
                                        sw(v0, gp, kGpDimxMode);
                                        v0 = 0x12120000;
                                        v1 = v0 | 0x3030;
                                        v0 = dsll32(v1, 0);
                                        v1 = v1 | v0;
                                    }
                                }
                                // 0x004d80b4: (matrix, DIMX)
                                charge(ctx, 7);
                                v0 = kGsDimx;
                                pcpyld(v0, v0, v1);
                                sq(v0, a1, 16);
                                lw(v0, gp, kGpSprWritePtr);
                                v0 = addiu(v0, 32);
                                sw(v0, gp, kGpSprWritePtr);  // the write pointer past the packet
                                backedge(ctx);
                                return_1();
                            } else {
                                // 0x004d80dc: no packet
                                charge(ctx, 2);
                                v0 = 0;
                                reload_ra();
                            }
                        } else {
                            // 0x004d7fbc: DIMX not allowed
                            charge(ctx, 2);
                            v0 = 0;
                            reload_ra();
                        }
                    } else {
                        // 0x004d7fa8: an unknown state
                        charge(ctx, 2);
                        v0 = 0;
                        // 0x004d8028
                        charge(ctx, 2);
                        ld(ra, sp, 0x10);
                    }
                }
            }
        }
    }
    // 0x004d81a0 (the shared epilogue)
    charge(ctx, 3);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// ==================================================================================================================
// PTank
// ==================================================================================================================

// 0x00478440 sub_478440 -- 212 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_478440 [PTank 2D render callback](atomic, params): copies the four parameter words into the current buffer
// record of the tank's pipeline record ({+0 -> rec+336, +4 -> +332, +8 -> +348, +12 -> +320}), installs the 2D
// lock sub_477470 as the instance callback for the run (sub_4861B0(atomic counts +4, block +80, flags mask
// 0xEFFFFFFF)) and the render callback sub_477150 after it. Returns 1. One block of 53.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void sub_478440(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::jal, hg::ld, hg::lq, hg::lui, hg::lw, hg::sd, hg::sll, hg::sq,
          hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00478440
    enter(ctx, 53);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = lui(0xEFFF);
    sd(ra, sp, 0x10);
    a2 = hi(kPtank2DLock);
    sq(s0, sp, 0x0);
    a3 = v0 | 0xFFFF;  // a3 = 0xEFFFFFFF: every flag but the reset bit 0x10000000
    lw(v1, a0, ptank_atomic::kCounts);
    a2 = addiu(a2, lo(kPtank2DLock));  // &sub_477470
    lw(t0, gp, kGpPtankDataOffset);  // the PTank plugin offset
    lw(t2, a1, ptank_params::kP3);
    lw(a0, a0, ptank_atomic::kPluginBase);
    v0 = addu(a0, t0);
    lw(s0, v0, 0);  // s0 = the tank block
    lw(v0, s0, ptank_block::kPipeRecord);  // v0 = the pipeline record
    lw(t1, v0, ptank_pipe::kBufIndex);
    t0 = sll(t1, 3);  // t0 = v0 + 36 * index: the current buffer record
    t0 = addu(t0, t1);
    t0 = sll(t0, 2);
    t0 = addu(t0, v0);
    sw(t2, t0, ptank_pipe::kBuf16A);
    lw(t1, v0, ptank_pipe::kBufIndex);
    lw(t2, a1, ptank_params::kP0);
    t0 = sll(t1, 3);
    t0 = addu(t0, t1);
    t0 = sll(t0, 2);
    t0 = addu(t0, v0);
    sw(t2, t0, ptank_pipe::kBuf4);
    lw(t1, v0, ptank_pipe::kBufIndex);
    lw(t2, a1, ptank_params::kP1);
    t0 = sll(t1, 3);
    t0 = addu(t0, t1);
    t0 = sll(t0, 2);
    t0 = addu(t0, v0);
    sw(t2, t0, ptank_pipe::kBuf8);
    lw(t1, v0, ptank_pipe::kBufIndex);
    lw(t2, a1, ptank_params::kP2);
    t0 = sll(t1, 3);
    t0 = addu(t0, t1);
    t0 = sll(t0, 2);
    v0 = addu(t0, v0);
    sw(t2, v0, ptank_pipe::kBuf16B);
    sw(a2, s0, ptank_block::kInstanceCb);  // the instance callback for the run: the 2D lock
    lw(a2, v1, 4);  // the vertex count
    a1 = addiu(s0, ptank_block::kRunArgs);
    jal(ctx, 0x4784ECu, gen::fn_sub_4861B0_004861b0);  // sub_4861B0: run the instance callbacks
    v1 = hi(kPtank2DRender);
    v0 = 1;
    v1 = addiu(v1, lo(kPtank2DRender));  // &sub_477150
    sw(v1, s0, ptank_block::kInstanceCb);  // ... then the 2D render callback
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00479840 sub_479840 -- 188 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_479840 [PTank 3D render callback](atomic, params): as sub_478440 for the 3D format: params {+4 -> rec+320,
// +0 -> +340, +8 -> +352}; instance callback sub_479590 for the run (the count word is the vertex count / 4),
// render callback sub_479170 after. Returns 1. One block of 47.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void sub_479840(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::jal, hg::ld, hg::lq, hg::lui, hg::lw, hg::sd, hg::sll, hg::sq,
          hg::srl, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00479840
    enter(ctx, 47);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = lui(0xEFFF);
    sd(ra, sp, 0x10);
    a2 = hi(kPtank3DInstance);
    sq(s0, sp, 0x0);
    a3 = v0 | 0xFFFF;  // a3 = 0xEFFFFFFF: every flag but the reset bit 0x10000000
    lw(v1, a0, ptank_atomic::kCounts);
    a2 = addiu(a2, lo(kPtank3DInstance));  // &sub_479590
    lw(t0, gp, kGpPtankDataOffset);  // the PTank plugin offset
    lw(t2, a1, ptank_params::kP1);
    lw(a0, a0, ptank_atomic::kPluginBase);
    v0 = addu(a0, t0);
    lw(s0, v0, 0);  // s0 = the tank block
    lw(v0, s0, ptank_block::kPipeRecord);  // v0 = the pipeline record
    lw(t1, v0, ptank_pipe::kBufIndex);
    t0 = sll(t1, 3);  // t0 = v0 + 36 * index: the current buffer record
    t0 = addu(t0, t1);
    t0 = sll(t0, 2);
    t0 = addu(t0, v0);
    sw(t2, t0, ptank_pipe::kBuf16A);
    lw(t1, v0, ptank_pipe::kBufIndex);
    lw(t2, a1, ptank_params::kP0);
    t0 = sll(t1, 3);
    t0 = addu(t0, t1);
    t0 = sll(t0, 2);
    t0 = addu(t0, v0);
    sw(t2, t0, ptank_pipe::kBuf3D);
    lw(t1, v0, ptank_pipe::kBufIndex);
    lw(t2, a1, ptank_params::kP2);
    t0 = sll(t1, 3);
    t0 = addu(t0, t1);
    a1 = addiu(s0, ptank_block::kRunArgs);
    t0 = sll(t0, 2);
    v0 = addu(t0, v0);
    sw(t2, v0, ptank_pipe::kBuf3DB);
    sw(a2, s0, ptank_block::kInstanceCb);  // the instance callback for the run: the 3D instance
    lw(v0, v1, 4);  // the vertex count
    a2 = srl(v0, 2);  // / 4: the particles
    jal(ctx, 0x4798D4u, gen::fn_sub_4861B0_004861b0);  // sub_4861B0: run the instance callbacks
    v1 = hi(kPtank3DRender);
    v0 = 1;
    v1 = addiu(v1, lo(kPtank3DRender));  // &sub_479170
    sw(v1, s0, ptank_block::kInstanceCb);  // ... then the 3D render callback
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00485EF0 sub_485EF0 -- 256 bytes; frame 0x30: ra sp+0x0
// sub_485EF0 [PTank constant UV, two pairs](stream, count, tank): each particle's four vertices get (u0, v1), (u1,
// v1), (u1, v0), (u0, v0) of the rectangle at tank + 144 {u0, v0, u1, v1}; a stride of 16 goes to the streamer
// sub_476980 (the four pairs on the stack, count * stride * 4 bytes), any other is written here.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void sub_485EF0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lw,
          hg::lwc1, hg::mult, hg::sd, hg::sll, hg::slt, hg::swc1;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x00485ef0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 16;
    sd(ra, sp, 0x0);
    lw(t0, a0, pt_stream::kStride);  // t0 = the stride
    if (t0 == v1) {
        // 0x00485f88: stride 16: the four pairs to the stack, sub_476980(dst, count * 16 * 4, pairs)
        charge(ctx, 24);
        lwc1(f0, a2, ptank_block::kConstUv0);
        swc1(f0, sp, 0x10);
        lwc1(f0, a2, ptank_block::kConstUv1 + 4);
        swc1(f0, sp, 0x14);
        lwc1(f0, a2, ptank_block::kConstUv1);
        swc1(f0, sp, 0x18);
        lwc1(f0, a2, ptank_block::kConstUv1 + 4);
        swc1(f0, sp, 0x1C);
        lwc1(f0, a2, ptank_block::kConstUv1);
        swc1(f0, sp, 0x20);
        lwc1(f0, a2, ptank_block::kConstUv0 + 4);
        swc1(f0, sp, 0x24);
        lwc1(f0, a2, ptank_block::kConstUv0);
        swc1(f0, sp, 0x28);
        lwc1(f0, a2, ptank_block::kConstUv0 + 4);
        swc1(f0, sp, 0x2C);
        lw(v0, a0, pt_stream::kStride);
        mult(v0, v0, a1);
        lw(a0, a0, pt_stream::kPtr);
        a2 = addiu(sp, 0x10);
        a1 = sll(v0, 2);
        jal(ctx, 0x485FD8u, gen::fn_sub_476980_00476980);
        backedge(ctx);
    } else {
        // 0x00485f08: written here: t2 = &(u0, v0), t1 = &(u1, v1)
        charge(ctx, 6);
        lw(t3, a0, pt_stream::kPtr);  // t3 = the destination
        at = slt(0, a1);
        t2 = addiu(a2, ptank_block::kConstUv0);
        t1 = addiu(a2, ptank_block::kConstUv1);
        t4 = 0;  // t4 = the particles written
        if (at != 0) {
            for (;;) {
                // 0x00485f20: one particle's four vertices t3, a3, a2, a0
                charge(ctx, 23);
                lwc1(f0, t2, 0);
                a3 = addu(t3, t0);
                a2 = addu(a3, t0);
                t4 = addiu(t4, 1);
                a0 = addu(a2, t0);
                v1 = slt(t4, a1);
                swc1(f0, t3, 0);
                lwc1(f0, t1, 4);
                swc1(f0, t3, 4);
                lwc1(f0, t1, 0);
                t3 = addu(a0, t0);
                swc1(f0, a3, 0);
                lwc1(f0, t1, 4);
                swc1(f0, a3, 4);
                lwc1(f0, t1, 0);
                swc1(f0, a2, 0);
                lwc1(f0, t2, 4);
                swc1(f0, a2, 4);
                lwc1(f0, t2, 0);
                swc1(f0, a0, 0);
                lwc1(f0, t2, 4);
                swc1(f0, a0, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00485f7c
            charge(ctx, 1);
        }
    }
    // 0x00485f80
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    // 0x00485fe8
    charge(ctx, 2);
    sp = addiu(sp, 0x30);
}

// 0x00485FF0 sub_485FF0 -- 264 bytes; frame 0x30: ra sp+0x0
// sub_485FF0 [PTank constant UV, four pairs](stream, count, tank): vertex k of each particle gets the pair at tank +
// 144 + 8k (the UV quad); a stride of 8 goes to the streamer sub_476980 (the quad on the stack), any other is written
// here.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void sub_485FF0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lw,
          hg::lwc1, hg::mult, hg::sd, hg::sll, hg::slt, hg::swc1;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x00485ff0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 8;
    sd(ra, sp, 0x0);
    lw(t1, a0, pt_stream::kStride);  // t1 = the stride
    if (t1 == v1) {
        // 0x00486090: stride 8: the quad to the stack, sub_476980(dst, count * 8 * 4, quad)
        charge(ctx, 24);
        lwc1(f0, a2, ptank_block::kConstUv0);
        swc1(f0, sp, 0x10);
        lwc1(f0, a2, ptank_block::kConstUv0 + 4);
        swc1(f0, sp, 0x14);
        lwc1(f0, a2, ptank_block::kConstUv0 + 8);
        swc1(f0, sp, 0x18);
        lwc1(f0, a2, ptank_block::kConstUv0 + 12);
        swc1(f0, sp, 0x1C);
        lwc1(f0, a2, ptank_block::kConstUv0 + 16);
        swc1(f0, sp, 0x20);
        lwc1(f0, a2, ptank_block::kConstUv0 + 20);
        swc1(f0, sp, 0x24);
        lwc1(f0, a2, ptank_block::kConstUv0 + 24);
        swc1(f0, sp, 0x28);
        lwc1(f0, a2, ptank_block::kConstUv0 + 28);
        swc1(f0, sp, 0x2C);
        lw(v0, a0, pt_stream::kStride);
        mult(v0, v0, a1);
        lw(a0, a0, pt_stream::kPtr);
        a2 = addiu(sp, 0x10);
        a1 = sll(v0, 2);
        jal(ctx, 0x4860E0u, gen::fn_sub_476980_00476980);
        backedge(ctx);
    } else {
        // 0x00486008: written here: t0, t4, t3, t2 = the four pairs
        charge(ctx, 8);
        lw(t5, a0, pt_stream::kPtr);  // t5 = the destination
        at = slt(0, a1);
        t0 = addiu(a2, ptank_block::kConstUv0);
        t4 = addiu(a2, ptank_block::kConstUv0 + 8);
        t3 = addiu(a2, ptank_block::kConstUv0 + 16);
        t2 = addiu(a2, ptank_block::kConstUv0 + 24);
        t6 = 0;  // t6 = the particles written
        if (at != 0) {
            for (;;) {
                // 0x00486028: one particle's four vertices t5, a3, a2, a0
                charge(ctx, 23);
                lwc1(f0, t0, 0);
                a3 = addu(t5, t1);
                a2 = addu(a3, t1);
                t6 = addiu(t6, 1);
                a0 = addu(a2, t1);
                v1 = slt(t6, a1);
                swc1(f0, t5, 0);
                lwc1(f0, t0, 4);
                swc1(f0, t5, 4);
                lwc1(f0, t4, 0);
                t5 = addu(a0, t1);
                swc1(f0, a3, 0);
                lwc1(f0, t4, 4);
                swc1(f0, a3, 4);
                lwc1(f0, t3, 0);
                swc1(f0, a2, 0);
                lwc1(f0, t3, 4);
                swc1(f0, a2, 4);
                lwc1(f0, t2, 0);
                swc1(f0, a0, 0);
                lwc1(f0, t2, 4);
                swc1(f0, a0, 4);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00486084
            charge(ctx, 1);
        }
    }
    // 0x00486088
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    // 0x004860f0
    charge(ctx, 2);
    sp = addiu(sp, 0x30);
}

// 0x004748C0 sub_4748C0 -- 220 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4748C0 [PTank texture](inst, texture): the texture's raster (RwTexture +0) is made resident
// (RpSkyTexCacheAccessRaster(raster, 1)); on success its TEX0/TEX1 go to the pipeline record +208 (filter byte
// texture +80) and the record's TEST word (+200, with the Z bits 16..18 of the global TEST shadow) gets ATE unless
// the raster's format nibble is 6; a palettized raster (depth < 9) invalidates the bridges' current-texture cache.
// No texture: TEX0 0, ATE cleared. Returns 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void sub_4748C0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq, hg::lw,
          hg::pcpyld, hg::sd, hg::si, hg::slti, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004748c0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x70000;  // the Z bits 16..18 of TEST
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a1;  // s3 = the texture
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, a0, ptank_inst::kPipeRecord);  // s1 = the pipeline record
    ld(v1, gp, kGpTest1);  // the global TEST shadow
    ld(a0, s1, ptank_pipe::kGsTest);
    v0 = v1 & v0;
    s2 = a0 | v0;  // s2 = the record's TEST | the shadow's Z bits
    if (s3 == 0) {
        // 0x0047496c: no texture: TEX0 = 0, ATE off (s2 &= ~1, all 128 bits)
        charge(ctx, 5);
        v0 = si(-2);
        sd(zero, s1, ptank_pipe::kGsTex0);
        pcpyld(v0, zero, v0);
        s2 = s2 & v0;
        backedge(ctx);
    } else {
        // 0x004748f8: make the raster resident
        charge(ctx, 6);
        lw(s0, s3, texture_rd::kRaster);  // s0 = the raster
        a1 = 1;
        a0 = s0;
        jal(ctx, 0x474900u, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
        if (v0 != 0) {
            // 0x00474910: sub_4F1E40(raster, &TEX0, filter)
            charge(ctx, 9);
            lbu(a2, s3, texture_rd::kFilter);
            a0 = s0;
            a1 = addiu(s1, ptank_pipe::kGsTex0);
            jal(ctx, 0x474918u, gen::fn_sub_4F1E40_004f1e40);
            lbu(v1, s0, raster_rd::kFormatByte);
            v0 = 6;
            v1 = v1 & 0xF;
            if (v1 == v0) {
                // 0x0047493c: format 6: ATE off
                charge(ctx, 3);
                v0 = si(-2);
                pcpyld(v0, zero, v0);
                s2 = s2 & v0;
            } else {
                // 0x00474934: ATE on
                charge(ctx, 2);
                s2 = s2 | 0x1;
            }
            // 0x00474948: a palettized raster: forget the bridges' current texture
            charge(ctx, 4);
            lw(v0, s0, raster_rd::kDepth);
            at = slti(v0, 9);
            if (at != 0) {
                // 0x00474958
                charge(ctx, 2);
                v0 = si(-1);
                sw(v0, gp, kGpCurrentTexture);
            }
        }
    }
    // 0x00474960: the TEST word back; return 1
    charge(ctx, 3);
    sd(s2, s1, ptank_pipe::kGsTest);
    v0 = 1;
    // 0x00474980
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004733C0 sub_4733C0 -- 240 bytes; frame 0x60: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4733C0 [PTank camera block](a, b): a 4-qw packet (_rwDMAOpenVIFPkt(0, 4)): DMA cnt 3 + STCYCL 4,4 + UNPACK
// V4-32 x3 to VU1 0x2FD, then the vectors at a + 24 and b + 24 and the "at" row of b's frame LTM
// (RwFrameGetLTM(b->frame) + 32, w the frame's stale stack word). Returns 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: frame/spills (own frame)).
void sub_4733C0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::call, hg::dsll32, hg::enter, hg::ld, hg::link, hg::lq, hg::lw, hg::lwc1,
          hg::pcpyld, hg::sd, hg::sq, hg::sw, hg::swc1;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x004733c0
    enter(ctx, 60);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;  // s2 = a
    s1 = a1;  // s1 = b
    a0 = 0;
    a1 = 4;
    link(ctx, 0x4733E0u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    v0 = 0x6C030000;  // UNPACK V4-32, 3 qwords ...
    lw(s0, gp, kGpSprWritePtr);  // s0 = the scratchpad write pointer
    v1 = v0 | 0x2FD;  // ... to VU1 0x2FD
    v0 = 0x1000000;
    v1 = dsll32(v1, 0);
    v0 = v0 | 0x404;  // STCYCL 4,4 (0x01000404)
    v1 = v0 | v1;
    v0 = 0x10000000;  // DMA cnt ...
    v0 = v0 | 0x3;  // ... 3 qwords
    pcpyld(v0, v1, v0);
    sq(v0, s0, 0);  // packet + 0: tag, STCYCL, UNPACK
    lwc1(f3, s2, 24);  // packet + 16: a's vector (+24 .. +36), through the stack
    lwc1(f2, s2, 28);
    lwc1(f1, s2, 32);
    lwc1(f0, s2, 36);
    swc1(f3, sp, 0x40);
    swc1(f2, sp, 0x44);
    swc1(f1, sp, 0x48);
    swc1(f0, sp, 0x4C);
    lq(v0, sp, 0x40);
    sq(v0, s0, 16);
    lwc1(f3, s1, 24);  // packet + 32: b's vector
    lwc1(f2, s1, 28);
    lwc1(f1, s1, 32);
    lwc1(f0, s1, 36);
    swc1(f3, sp, 0x40);
    swc1(f2, sp, 0x44);
    swc1(f1, sp, 0x48);
    swc1(f0, sp, 0x4C);
    lq(v0, sp, 0x40);
    sq(v0, s0, 32);
    link(ctx, 0x473464u);  // $ra first: the delay slot below depends on it
    lw(a0, s1, 4);  // sub_4CB2F0(b->frame): RwFrameGetLTM
    call(ctx, gen::fn_sub_4CB2F0_004cb2f0);
    lwc1(f2, v0, 32);  // packet + 48: the LTM's "at" row (+32 .. +40); w is the stack word at sp+0x5C
    v1 = addiu(s0, 64);
    lwc1(f1, v0, 36);
    lwc1(f0, v0, 40);
    swc1(f2, sp, 0x50);
    swc1(f1, sp, 0x54);
    swc1(f0, sp, 0x58);
    v0 = 1;
    lq(a0, sp, 0x50);
    sq(a0, s0, 48);
    sw(v1, gp, kGpSprWritePtr);  // the write pointer past the packet
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

namespace {

// The prologue of the two sprite packets: nine spills, the arguments $a0..$a3 / $t0..$t3 moved into $s4, $s3, $s2,
// $s1, $s0, $s5, $s6, $s7 in the original's order, then _rwDMAOpenVIFPkt(0x80000000, 32).
struct SpriteArgs {
    u32 x0, y0, x1, y1, w4, w5, w6, w7;
};

SpriteArgs sprite_prologue(EEContext& ctx, Frame& f, u32 open_pc) {
    Regs r{ctx};
    f.sd(GPR_RA, 128);
    f.sq(GPR_S7, 112);
    f.sq(GPR_S6, 96);
    r.d(GPR_S7, r.get(GPR_T3));
    f.sq(GPR_S5, 80);
    r.d(GPR_S6, r.get(GPR_T2));
    f.sq(GPR_S4, 64);
    r.d(GPR_S5, r.get(GPR_T1));
    f.sq(GPR_S3, 48);
    r.d(GPR_S4, r.get(GPR_A0));
    f.sq(GPR_S2, 32);
    r.d(GPR_S3, r.get(GPR_A1));
    f.sq(GPR_S1, 16);
    r.d(GPR_S2, r.get(GPR_A2));
    f.sq(GPR_S0, 0);
    r.d(GPR_S1, r.get(GPR_A3));
    r.d(GPR_S0, r.get(GPR_T0));
    const SpriteArgs s{r.get32(GPR_S4), r.get32(GPR_S3), r.get32(GPR_S2), r.get32(GPR_S1),
                       r.get32(GPR_S0), r.get32(GPR_S5), r.get32(GPR_S6), r.get32(GPR_S7)};
    r.w(GPR_A0, 0x80000000u);
    r.d(GPR_A1, 32);
    open_vif(ctx, open_pc);
    return s;
}

// The A+D tag for `nregs` registers at the write pointer: $v1 / $a0 / $a1 as the bodies leave them.
u32 ad_tag(EEContext& ctx, u32 nregs) {
    Regs r{ctx};
    r.w(GPR_V1, 0x10000000u);
    r.d(GPR_A1, kGifAd);
    r.d(GPR_A0, 0x1000000000000000ull);
    r.d(GPR_V1, 0x8000u | nregs);
    r.d(GPR_V1, 0x1000000000008000ull | nregs);
    r.q(GPR_A1, 0x1000000000008000ull | nregs, kGifAd);
    return spr_ptr(ctx);
}

}  // namespace

// [raster fill rectangle] A+D: PRIM sprite (0x46 with alpha blending when the 10th argument is set, else 0x06),
// XYZ2 (x0, y0, z), RGBAQ (r | g << 8 | b << 16 | a << 24), XYZ2 (x1, y1, z): coordinates are shifted into 12.4,
// z is the 9th argument. Arguments: $a0 x0, $a1 y0, $a2 x1, $a3 y1, $t0..$t3 r g b a, stack +0 z, +8 blend.
void sub_4E4420(EEContext& ctx) {
    Regs r{ctx};
    enter(ctx, 31);
    Frame f(ctx, 144);
    const SpriteArgs s = sprite_prologue(ctx, f, 0x4E446Cu);
    const u32 p = ad_tag(ctx, 4);
    r.w(GPR_A0, p);
    const u32 blend = lw(ctx, f.at(152));
    r.w(GPR_V1, blend);
    sq(ctx, p, r.get_q(GPR_A1));
    if (blend != 0) {
        charge(ctx, 4);
        r.d(GPR_A0, 0);
        r.d(GPR_V1, 0x46);
        r.q(GPR_A0, 0x46, 0);  // PRIM (address 0)
    } else {
        charge(ctx, 3);
        r.d(GPR_A0, 0);
        r.d(GPR_V1, 6);
        r.q(GPR_A0, 6, 0);
    }
    charge(ctx, 42);
    const u32 q = spr_ptr(ctx);
    r.w(GPR_T4, q);
    r.w(GPR_A2, s.w7 << 24);
    r.w(GPR_A1, s.w6 << 16);
    const u64 z = guest::load<u32>(ctx, f.at(144));  // LWU
    r.d(GPR_T3, z);
    const u32 rgba = s.w4 | (s.w5 << 8) | (s.w6 << 16) | (s.w7 << 24);
    r.w(GPR_A2, (s.w7 << 24) | (s.w6 << 16));
    r.d(GPR_T0, 1);
    r.w(GPR_A1, s.w5 << 8);
    r.w(GPR_T2, s.y0 << 20);
    r.w(GPR_A1, (s.w5 << 8) | (s.w7 << 24) | (s.w6 << 16));
    r.w(GPR_V1, s.x0 << 4);
    r.w(GPR_A3, rgba);
    r.w(GPR_A2, s.x1 << 4);
    sq(ctx, q + 16, r.get_q(GPR_A0));
    r.d(GPR_A3, rgba);  // DSLL32 / DSRL32: zero-extended
    r.d(GPR_A0, z << 32);
    r.q(GPR_T0, rgba, 1);  // RGBAQ
    r.w(GPR_A1, s.y1 << 20);
    const u64 xyz0 = (z << 32) | core::sext32(s.y0 << 20) | core::sext32(s.x0 << 4);
    const u64 xyz1 = core::sext32(s.x1 << 4) | (z << 32) | core::sext32(s.y1 << 20);
    r.d(GPR_A3, (z << 32) | core::sext32(s.y0 << 20));
    r.d(GPR_A0, (z << 32) | core::sext32(s.y1 << 20));
    r.d(GPR_T1, 5);
    r.d(GPR_A1, xyz0);
    r.d(GPR_V1, xyz1);
    r.q(GPR_A0, xyz0, 5);  // XYZ2
    sq(ctx, q + 32, r.get_q(GPR_A0));
    r.q(GPR_V1, xyz1, 5);
    sq(ctx, q + 48, r.get_q(GPR_T0));
    sq(ctx, q + 64, r.get_q(GPR_V1));
    r.w(GPR_V1, spr_ptr(ctx) + 80);
    set_spr_ptr(ctx, r.get32(GPR_V1));
}

// [raster copy sprite] A+D: PRIM textured sprite with UV coordinates (0x156 with alpha blending when the 9th argument
// is set, else 0x116), UV (u0, v0), XYZ2 (x0, y0), RGBAQ 0x80FFFFFF, UV (u1, v1), XYZ2 (x1, y1). Arguments: $a0 x0,
// $a1 y0, $a2 x1, $a3 y1, $t0 u0, $t1 v0, $t2 u1, $t3 v1 (already 12.4 / texel units as given), stack +0 blend.
void sub_4E4560(EEContext& ctx) {
    Regs r{ctx};
    enter(ctx, 31);
    Frame f(ctx, 144);
    const SpriteArgs s = sprite_prologue(ctx, f, 0x4E45ACu);
    const u32 p = ad_tag(ctx, 6);
    r.w(GPR_A0, p);
    const u32 blend = lw(ctx, f.at(144));
    r.w(GPR_V1, blend);
    sq(ctx, p, r.get_q(GPR_A1));
    if (blend != 0) {
        charge(ctx, 4);
        r.d(GPR_A0, 0);
        r.d(GPR_V1, 342);
        r.q(GPR_V1, 342, 0);
    } else {
        charge(ctx, 3);
        r.d(GPR_A0, 0);
        r.d(GPR_V1, 278);
        r.q(GPR_V1, 278, 0);
    }
    charge(ctx, 50);
    const u64 uv0 = core::sext32((s.w5 << 16) | s.w4);
    const u64 xyz0 = core::sext32((s.y0 << 20) | (s.x0 << 4));
    const u64 uv1 = core::sext32((s.w7 << 16) | s.w6);
    const u64 xyz1 = core::sext32((s.y1 << 20) | (s.x1 << 4));
    r.w(GPR_A0, s.w5 << 16);
    const u32 q = spr_ptr(ctx);
    r.w(GPR_T1, q);
    r.d(GPR_A2, r.get(GPR_A0) | r.get(GPR_S0));
    r.w(GPR_A1, s.y0 << 20);
    r.w(GPR_A0, s.x0 << 4);
    r.d(GPR_T0, uv0);
    r.d(GPR_A0, r.get(GPR_A1) | r.get(GPR_A0));
    r.d(GPR_A3, xyz0);
    r.w(GPR_A1, s.y1 << 20);
    r.w(GPR_A0, s.w7 << 16);
    r.d(GPR_A0, r.get(GPR_A0) | r.get(GPR_S6));
    sq(ctx, q + 16, r.get_q(GPR_V1));  // PRIM
    r.d(GPR_A2, uv1);
    r.d(GPR_V1, 0x80FF0000u);
    r.w(GPR_A0, s.x1 << 4);
    r.d(GPR_A0, r.get(GPR_A1) | r.get(GPR_A0));
    r.d(GPR_A1, 3);
    r.d(GPR_A0, r.get(GPR_A0) << 32);
    r.q(GPR_T2, uv0, 3);  // UV
    r.q(GPR_T0, uv1, 3);
    sq(ctx, q + 32, r.get_q(GPR_T2));
    r.d(GPR_A2, 5);
    r.d(GPR_A0, xyz1);
    r.q(GPR_A3, xyz0, 5);  // XYZ2
    r.d(GPR_A1, 1);
    r.d(GPR_V1, 0x80FFFFFFu);
    sq(ctx, q + 48, r.get_q(GPR_A3));
    r.q(GPR_V1, 0x80FFFFFFu, 1);  // RGBAQ
    sq(ctx, q + 64, r.get_q(GPR_V1));
    r.q(GPR_A0, xyz1, 5);
    sq(ctx, q + 80, r.get_q(GPR_T0));
    sq(ctx, q + 96, r.get_q(GPR_A0));
    r.w(GPR_V1, spr_ptr(ctx) + 112);
    set_spr_ptr(ctx, r.get32(GPR_V1));
}

// [restore draw environment] A+D: FRAME_1, ZBUF_1 and ALPHA_1 from their shadows, the prim shadow's bits 5..8
// restored from the copy sub_4E4180 saved, XYOFFSET_1 and XYOFFSET_2 = the XYOFFSET shadow with the field's half-line
// (bit 35); the bridges' current-texture cache is reset.
void sub_4E46C0(EEContext& ctx) {
    Regs r{ctx};
    enter(ctx, 34);
    Frame f(ctx, 16);
    r.w(GPR_A0, 0x80000000u);
    f.sd(GPR_RA, 0);
    r.d(GPR_A1, 32);
    open_vif(ctx, 0x4E46CCu);
    const u32 p = spr_ptr(ctx);
    r.w(GPR_T0, p);
    r.w(GPR_V1, 0x10000000u);
    r.d(GPR_A0, 0x1000000000000000ull);
    r.d(GPR_A1, kGifAd);
    r.d(GPR_V1, 0x8005u);
    r.d(GPR_A2, kGsFrame1);
    r.d(GPR_V1, 0x1000000000008005ull);
    r.q(GPR_A3, 0x1000000000008005ull, kGifAd);
    r.d(GPR_V1, kGsZbuf1);
    r.d(GPR_A0, kGsAlpha1);
    sq(ctx, p, r.get_q(GPR_A3));
    r.w(GPR_A1, static_cast<u32>(-481));
    const u64 frame = ld(ctx, gpv(ctx, kGpFrame1));
    r.d(GPR_A3, frame);
    r.q(GPR_A2, frame, kGsFrame1);
    sq(ctx, p + 16, r.get_q(GPR_A2));
    const u64 zbuf = ld(ctx, gpv(ctx, kGpZbuf1));
    r.d(GPR_A2, zbuf);
    r.q(GPR_V1, zbuf, kGsZbuf1);
    sq(ctx, p + 32, r.get_q(GPR_V1));
    const u64 alpha = ld(ctx, gpv(ctx, kGpAlpha1));
    r.d(GPR_V1, alpha);
    r.q(GPR_V1, alpha, kGsAlpha1);
    sq(ctx, p + 48, r.get_q(GPR_V1));
    const u64 prim = ld(ctx, gpv(ctx, kGpPrimShadow));
    r.d(GPR_A2, prim);
    const u64 saved = ld(ctx, gpv(ctx, kGpPrimShadowSaved));
    r.d(GPR_A0, saved);
    const u32 interlace = guest::load<u8>(ctx, gpv(ctx, kGpInterlace));
    r.d(GPR_V1, interlace);
    r.d(GPR_A1, prim & ~0x1E0ull);
    r.d(GPR_A0, saved & 0x1E0u);
    r.d(GPR_A0, (prim & ~0x1E0ull) | (saved & 0x1E0u));
    sd(ctx, gpv(ctx, kGpPrimShadow), r.get(GPR_A0));
    u64 parity;
    if (interlace != 0) {
        parity = field_parity_wait(ctx, GPR_A0, GPR_A1);
    } else {
        charge(ctx, 2);
        r.d(GPR_V1, 0);
        parity = 0;
        backedge(ctx);
    }
    charge(ctx, 22);
    r.d(GPR_A2, parity << 35);
    r.d(GPR_A0, ~8ull);
    r.d(GPR_V1, 0xFFFFu);
    const u64 xy = ld(ctx, gpv(ctx, kGpXyoffset));
    r.d(GPR_T0, xy);
    r.d(GPR_V1, 0xFFFF0000u);
    r.d(GPR_A0, 0xFFFFFFF700000000ull);
    r.d(GPR_V1, 0xFFFFFFFFu);
    r.d(GPR_A1, kGsXyoffset1);
    r.d(GPR_A3, 0xFFFFFFF7FFFFFFFFull);
    r.w(GPR_A0, spr_ptr(ctx));
    r.d(GPR_V1, kGsXyoffset1 + 1);
    const u64 off = (xy & 0xFFFFFFF7FFFFFFFFull) | (parity << 35);
    r.d(GPR_A3, xy & 0xFFFFFFF7FFFFFFFFull);
    r.d(GPR_A2, off);
    r.q(GPR_A1, off, kGsXyoffset1);
    r.q(GPR_V1, off, kGsXyoffset1 + 1);  // XYOFFSET_2
    const u32 dst = r.get32(GPR_A0);
    sq(ctx, dst + 64, r.get_q(GPR_A1));
    sq(ctx, dst + 80, r.get_q(GPR_V1));
    r.w(GPR_V1, spr_ptr(ctx));
    sw(ctx, gpv(ctx, kGpCurrentTexture), 0);
    r.w(GPR_V1, r.get32(GPR_V1) + 96);
    set_spr_ptr(ctx, r.get32(GPR_V1));
    charge(ctx, 3);
}

// ==================================================================================================================
// Batch 2: the raster clear, the PTank 2D lock and the constant attribute fills
// ==================================================================================================================

// [raster clear] Clears `rect` {x, y, w, h} of the camera's frame raster to `colour`. A camera / Z raster (type 1 / 2)
// is cleared on the GS: draw environment (sub_4E4180(type)), one sprite fill (sub_4E4420) with the colour split into
// components (1555 when the raster format nibble is 1, else 8888; the colour word also rides as the 9th argument),
// the environment restored (sub_4E46C0); returns 1. A normal / texture raster (type 0 / 4) with locked pixels is
// filled on the CPU, 32 or 16 bits per pixel row by row; returns 0. Anything else returns 0.
u32 sub_4E4800(EEContext& ctx, u32 rect, u64 colour) {
    Regs r{ctx};
    enter(ctx, 10);
    Frame f(ctx, 64);
    r.d(GPR_V0, 4);
    f.sd(GPR_RA, 48);
    f.sq(GPR_S1, 32);
    f.sq(GPR_S0, 16);
    r.d(GPR_S1, colour);
    const u32 raster = lw(ctx, gpv(ctx, kGpFrameRaster));
    r.w(GPR_A0, raster);
    const u32 type = guest::load<u8>(ctx, raster + 32);
    r.d(GPR_V1, type);
    r.w(GPR_S0, rect);
    auto leave = [&](u64 v0, u32 cycles) {  // ... ld ra (one block or two), lq, addiu
        r.d(GPR_V0, v0);
        charge(ctx, cycles);
        charge(ctx, 4);
        return static_cast<u32>(v0);
    };
    if (type == 1 || type == 2) {
        charge(ctx, 2);
        charge(ctx, 3);
        r.d(GPR_V0, 1);
        if (type == 2) {
            charge(ctx, 3);
            r.d(GPR_V0, 2);
        }
        charge(ctx, 9);
        r.d(GPR_A0, type & 0xFFu);
        jal(ctx, 0x4E4850u, gen::fn_sub_4E4180_004e4180);
        const u32 raster2 = lw(ctx, gpv(ctx, kGpFrameRaster));
        r.w(GPR_V1, raster2);
        r.d(GPR_V0, 256);
        const u32 format = (static_cast<u32>(guest::load<u8>(ctx, raster2 + 35)) << 8) & 0xF00u;
        r.d(GPR_V1, format);
        const u32 c = static_cast<u32>(colour);
        const u32 x = lw(ctx, rect + 0), y = lw(ctx, rect + 4);
        u32 call_pc;
        if (format == 0x100u) {  // 1555
            charge(ctx, 19);
            r.w(GPR_A1, y);
            r.w(GPR_A0, x);
            r.w(GPR_T0, (c & 0x1Fu) << 3);
            r.w(GPR_T2, (c & 0x7C00u) >> 7);
            r.w(GPR_T1, (c & 0x3E0u) >> 2);
            r.w(GPR_T3, (c & 0x8000u) >> 8);
            call_pc = 0x4E48B0u;
        } else {  // 8888
            charge(ctx, 18);
            r.w(GPR_A1, y);
            r.w(GPR_A0, x);
            r.w(GPR_T1, (c & 0xFF00u) >> 8);
            r.w(GPR_T0, c & 0xFFu);
            r.w(GPR_T2, (c & 0xFF0000u) >> 16);
            r.w(GPR_T3, c >> 24);
            call_pc = 0x4E4900u;
        }
        sd(ctx, f.at(0), colour);  // the 9th argument (z): the colour word; the 10th (blend): 0
        sd(ctx, f.at(8), 0);
        const u32 w = lw(ctx, rect + 8), h = lw(ctx, rect + 12);
        r.w(GPR_V1, w);
        r.w(GPR_V0, h);
        r.w(GPR_A2, x + w);
        r.w(GPR_A3, y + h);
        jal(ctx, call_pc, gen::fn_sub_4E4420_004e4420);
        charge(ctx, 4);
        jal(ctx, 0x4E4908u, gen::fn_sub_4E46C0_004e46c0);
        return leave(1, 1);
    }
    if (type != 4) {
        charge(ctx, 2);
        if (type != 0) {
            charge(ctx, 3);
            r.d(GPR_V0, 1);
            charge(ctx, 3);
            r.d(GPR_V0, 2);
            charge(ctx, 2);
            return leave(0, 2);
        }
    }
    // A locked raster: CPU fill.
    charge(ctx, 3);
    const u32 pixels = lw(ctx, raster + 4);
    r.w(GPR_A3, pixels);
    if (pixels == 0) {
        charge(ctx, 2);
        return leave(0, 1);
    }
    charge(ctx, 6);
    const u32 bytes = static_cast<u32>(static_cast<s32>(lw(ctx, raster + 20) + 7) >> 3);
    r.d(GPR_V0, 2);
    r.w(GPR_V1, bytes);
    if (bytes != 2) {
        charge(ctx, 3);
        r.d(GPR_V0, 4);
        if (bytes != 4) {
            charge(ctx, 2);
            charge(ctx, 2);
            return leave(0, 1);
        }
    }
    // Registers of the two fill bodies: 32 bits {row ptr $a1, rows left $a2}, 16 bits {row ptr $a2, rows left $a1}.
    const bool wide = bytes == 4;
    const unsigned r_ptr = wide ? GPR_A1 : GPR_A2, r_rows = wide ? GPR_A2 : GPR_A1;
    const u32 shift = wide ? 2 : 1;
    charge(ctx, 13);
    const u32 stride = lw(ctx, raster + 24);
    r.w(GPR_V1, stride);
    r.w(GPR_V0, lw(ctx, rect + 4));
    rt::mult(ctx, GPR_A2, GPR_V1, GPR_V0);  // stride * y (HI/LO kept)
    const u32 x = lw(ctx, rect + 0);
    r.w(GPR_A1, x);
    r.w(GPR_A0, stride >> shift);
    const u32 w = lw(ctx, rect + 8);
    r.w(GPR_V1, w);
    r.w(GPR_A2, pixels + r.get32(GPR_A2));
    const u32 h = lw(ctx, rect + 12);
    r.w(GPR_V0, h);
    r.w(GPR_A1, x << shift);
    r.w(r_ptr, r.get32(GPR_A2) + r.get32(GPR_A1));
    r.w(GPR_V1, (stride >> shift) - w);
    r.w(r_rows, h - 1);
    if (h != 0) {
        charge(ctx, 1);
        r.w(GPR_V1, r.get32(GPR_V1) << shift);  // the row skip in bytes
        for (;;) {
            charge(ctx, 3);
            const u32 width = lw(ctx, rect + 8);
            r.w(GPR_V0, width);
            r.w(GPR_A0, width - 1);
            if (width != 0) {
                charge(ctx, 1);
                for (;;) {
                    charge(ctx, 7);
                    if (wide) {
                        sw(ctx, r.get32(r_ptr), static_cast<u32>(colour));
                    } else {
                        guest::store<u16>(ctx, r.get32(r_ptr), static_cast<u16>(colour));
                    }
                    r.d(GPR_V0, r.get(GPR_A0));
                    r.w(r_ptr, r.get32(r_ptr) + (wide ? 4u : 2u));
                    r.w(GPR_A0, r.get32(GPR_A0) - 1);
                    if (r.get(GPR_V0) == 0) break;
                    backedge(ctx);
                }
                charge(ctx, 2);
            } else {
                charge(ctx, 1);
            }
            r.d(GPR_V0, r.get(r_rows));
            charge(ctx, 3);
            r.w(r_ptr, r.get32(r_ptr) + r.get32(GPR_V1));
            r.w(r_rows, r.get32(r_rows) - 1);
            if (r.get(GPR_V0) == 0) break;
            backedge(ctx);
        }
        charge(ctx, 2);
        backedge(ctx);
    }
    charge(ctx, 1);
    return leave(0, 2);
}

// 0x00477470 sub_477470 -- 412 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_477470 [PTank 2D lock](lock, _, data, _, flags): the lock callback sub_478440 installs. Fills the lock record
// at `lock` from the tank's current pipeline buffer record (data + 76 -> pipe, index at +228, 36-byte records):
// +0 = 1 (the 16-byte component at record +320 always), +8 = flags 2 or 0x2000 (the 4-byte component at +336), +4 =
// flags 0x80 or 0x80000 (the 16-byte one at +348), +12 = flags 4 or 0x4000 (the 8-byte one at +332); then the
// {pointer, stride} pairs of the components asked for at +16, +32, +24, +40 -- the record words sub_478440 copied
// from its parameters. Flag 0x10000000 first resets the tank (sub_474A80); sub_4D5E90 waits for the streamers'
// scratchpad DMA.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_477470(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::sltiu, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00477470
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v0 = 0x10000000;  // the reset flag
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = t0;  // s2 = flags
    sq(s0, sp, 0x0);
    v0 = s2 & v0;
    lw(s1, a2, ptank_inst::kPipeRecord);  // s1 = the pipeline record
    lw(s0, s1, ptank_pipe::kBufIndex);  // s0 = the current buffer record's index
    s3 = a0;  // s3 = the lock record
    if (v0 != 0) {
        // 0x004774a4: sub_474A80(data): reset the tank
        charge(ctx, 2);
        a0 = a2;
        jal(ctx, 0x4774A4u, gen::fn_sub_474A80_00474a80);
    }
    // 0x004774ac: wait for the streamers' DMA; the 4-byte component: flag 2 ...
    charge(ctx, 7);
    jal(ctx, 0x4774ACu, gen::fn_sub_4D5E90_004d5e90);
    v1 = s2 & 0x2;
    v1 = v1 ^ 0x2;
    v1 = sltiu(v1, 1);
    if (v1 == 0) {
        // 0x004774c8: ... or 0x2000
        charge(ctx, 3);
        v1 = s2 & 0x2000;
        v1 = v1 ^ 0x2000;
        v1 = sltiu(v1, 1);
    }
    // 0x004774d4: the 16-byte component B: flag 0x80 ...
    charge(ctx, 6);
    sw(v1, s3, ptank_lock::kWant4);
    v1 = s2 & 0x80;
    v1 = v1 ^ 0x80;
    v1 = sltiu(v1, 1);
    if (v1 == 0) {
        // 0x004774ec: ... or 0x80000
        charge(ctx, 4);
        a0 = 0x80000;
        v1 = s2 & a0;
        v1 = v1 ^ a0;
        v1 = sltiu(v1, 1);
    }
    // 0x004774fc: component A always; the 8-byte component: flag 4 ...
    charge(ctx, 8);
    sw(v1, s3, ptank_lock::kWant16B);
    v1 = 1;
    sw(v1, s3, ptank_lock::kWant16A);
    v1 = s2 & 0x4;
    v1 = v1 ^ 0x4;
    v1 = sltiu(v1, 1);
    if (v1 == 0) {
        // 0x0047751c: ... or 0x4000
        charge(ctx, 3);
        v1 = s2 & 0x4000;
        v1 = v1 ^ 0x4000;
        v1 = sltiu(v1, 1);
    }
    // 0x00477528: the pairs of the components asked for
    charge(ctx, 4);
    sw(v1, s3, ptank_lock::kWant8);
    lw(v1, s3, ptank_lock::kWant16A);
    if (v1 != 0) {
        // 0x00477564: {buffer[index] + 320, 16}
        charge(ctx, 9);
        a0 = sll(s0, 3);  // 36 * index = ((index * 8) + index) * 4
        v1 = 16;
        a0 = addu(a0, s0);
        a0 = sll(a0, 2);
        a0 = addu(a0, s1);
        lw(a0, a0, ptank_pipe::kBuf16A);
        sw(a0, s3, ptank_lock::kPair16A);
        sw(v1, s3, ptank_lock::kPair16A + 4);
        backedge(ctx);
    }
    // 0x00477538
    charge(ctx, 3);
    lw(v1, s3, ptank_lock::kWant4);
    if (v1 != 0) {
        // 0x00477588: {buffer[index] + 336, 4}
        charge(ctx, 9);
        a0 = sll(s0, 3);
        v1 = 4;
        a0 = addu(a0, s0);
        a0 = sll(a0, 2);
        a0 = addu(a0, s1);
        lw(a0, a0, ptank_pipe::kBuf4);
        sw(a0, s3, ptank_lock::kPair4);
        sw(v1, s3, ptank_lock::kPair4 + 4);
        backedge(ctx);
    }
    // 0x00477544
    charge(ctx, 3);
    lw(v1, s3, ptank_lock::kWant16B);
    if (v1 != 0) {
        // 0x004775ac: {buffer[index] + 348, 16}
        charge(ctx, 9);
        a0 = sll(s0, 3);
        v1 = 16;
        a0 = addu(a0, s0);
        a0 = sll(a0, 2);
        a0 = addu(a0, s1);
        lw(a0, a0, ptank_pipe::kBuf16B);
        sw(a0, s3, ptank_lock::kPair16B);
        sw(v1, s3, ptank_lock::kPair16B + 4);
        backedge(ctx);
    }
    // 0x00477550
    charge(ctx, 3);
    lw(v1, s3, ptank_lock::kWant8);
    if (v1 != 0) {
        // 0x004775d0: {buffer[index] + 332, 8}
        charge(ctx, 9);
        a0 = sll(s0, 3);
        v1 = 8;
        a0 = addu(a0, s0);
        a0 = sll(a0, 2);
        a0 = addu(a0, s1);
        lw(a0, a0, ptank_pipe::kBuf8);
        sw(a0, s3, ptank_lock::kPair8);
        sw(v1, s3, ptank_lock::kPair8 + 4);
        backedge(ctx);
    }
    // 0x0047755c: the epilogue
    charge(ctx, 2);
    ld(ra, sp, 0x40);
    // 0x004775f4
    charge(ctx, 6);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00478100 sub_478100 -- 372 bytes; frame 0x20: ra sp+0x0
// sub_478100 [PTank constant size](stream, count, tank): every element of the {pointer, stride} stream = the (w, h)
// pair at tank + 112; a stride of 8 goes to the streamer sub_476490 (the pair on the stack), any other is written
// here, eight elements per iteration while at least 9 are left.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void sub_478100(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lw,
          hg::lwc1, hg::mult, hg::sd, hg::slt, hg::slti, hg::swc1;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x00478100
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 8;
    sd(ra, sp, 0x0);
    lw(t6, a0, pt_stream::kStride);  // t6 = the stride
    lw(t7, a0, pt_stream::kPtr);  // t7 = the destination
    if (t6 == v1) {
        // 0x00478240: stride 8: the pair to the stack, sub_476490(dst, count * 8, pair)
        charge(ctx, 11);
        lwc1(f1, a2, ptank_block::kConstWidth);
        v0 = addiu(sp, 0x18);
        lwc1(f0, a2, ptank_block::kConstHeight);
        swc1(f1, sp, 0x18);
        swc1(f0, sp, 0x1C);
        mult(a1, a1, t6);
        a0 = t7;
        a2 = v0;
        jal(ctx, 0x47825Cu, gen::fn_sub_476490_00476490);
        backedge(ctx);
    } else {
        // 0x00478118: count > 0?
        charge(ctx, 3);
        at = slt(0, a1);
        t8 = 0;  // t8 = the elements written
        if (at != 0) {
            // 0x00478124: count > 8?
            charge(ctx, 3);
            at = slti(a1, 9);
            t5 = addiu(a1, -8);  // t5 = count - 8
            if (at == 0) {
                // 0x00478130: the unrolled loop's guard: 0 <= count < 0x7FFFFFFF
                charge(ctx, 3);
                at = slt(a1, 0);
                v1 = 0;
                if (at == 0) {
                    // 0x0047813c
                    charge(ctx, 5);
                    at = 0x7FFF0000;
                    at = at | 0xFFFF;
                    at = slt(a1, at);
                    if (at != 0) {
                        // 0x00478150
                        charge(ctx, 1);
                        v1 = 1;
                    }
                }
                // 0x00478154
                charge(ctx, 2);
                if (v1 != 0) {
                    for (;;) {
                        // 0x0047815c: eight elements t7, t4, t3, t2, t1, t0, a3, a0
                        charge(ctx, 43);
                        lwc1(f1, a2, ptank_block::kConstWidth);
                        t4 = addu(t7, t6);
                        lwc1(f0, a2, ptank_block::kConstHeight);
                        t3 = addu(t4, t6);
                        t2 = addu(t3, t6);
                        t8 = addiu(t8, 8);
                        t1 = addu(t2, t6);
                        v1 = slt(t8, t5);
                        t0 = addu(t1, t6);
                        a3 = addu(t0, t6);
                        a0 = addu(a3, t6);
                        swc1(f1, t7, 0);
                        swc1(f0, t7, 4);
                        lwc1(f1, a2, ptank_block::kConstWidth);
                        t7 = addu(a0, t6);
                        lwc1(f0, a2, ptank_block::kConstHeight);
                        swc1(f1, t4, 0);
                        swc1(f0, t4, 4);
                        lwc1(f1, a2, ptank_block::kConstWidth);
                        lwc1(f0, a2, ptank_block::kConstHeight);
                        swc1(f1, t3, 0);
                        swc1(f0, t3, 4);
                        lwc1(f1, a2, ptank_block::kConstWidth);
                        lwc1(f0, a2, ptank_block::kConstHeight);
                        swc1(f1, t2, 0);
                        swc1(f0, t2, 4);
                        lwc1(f1, a2, ptank_block::kConstWidth);
                        lwc1(f0, a2, ptank_block::kConstHeight);
                        swc1(f1, t1, 0);
                        swc1(f0, t1, 4);
                        lwc1(f1, a2, ptank_block::kConstWidth);
                        lwc1(f0, a2, ptank_block::kConstHeight);
                        swc1(f1, t0, 0);
                        swc1(f0, t0, 4);
                        lwc1(f1, a2, ptank_block::kConstWidth);
                        lwc1(f0, a2, ptank_block::kConstHeight);
                        swc1(f1, a3, 0);
                        swc1(f0, a3, 4);
                        lwc1(f1, a2, ptank_block::kConstWidth);
                        lwc1(f0, a2, ptank_block::kConstHeight);
                        swc1(f1, a0, 0);
                        swc1(f0, a0, 4);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
            // 0x00478208: the rest, one per iteration
            charge(ctx, 3);
            at = slt(t8, a1);
            if (at != 0) {
                for (;;) {
                    // 0x00478214: one element
                    charge(ctx, 8);
                    lwc1(f1, a2, ptank_block::kConstWidth);
                    t8 = addiu(t8, 1);
                    lwc1(f0, a2, ptank_block::kConstHeight);
                    v1 = slt(t8, a1);
                    swc1(f1, t7, 0);
                    swc1(f0, t7, 4);
                    t7 = addu(t7, t6);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00478234
                charge(ctx, 1);
            }
        }
    }
    // 0x00478238
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    // 0x0047826c
    charge(ctx, 2);
    sp = addiu(sp, 0x20);
}

// 0x00477810 sub_477810 -- 524 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_477810 [PTank constant colour](stream, count, tank): every element of the {pointer, stride} stream = the RGBA
// bytes at tank + 124; a stride of 4 goes to the streamer sub_476140 (the colour word as its argument), any other is
// written byte by byte here, eight elements per iteration while at least 9 are left.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void sub_477810(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq,
          hg::lw, hg::mult, hg::sb, hg::sd, hg::slt, hg::slti, hg::sq;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00477810
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v1 = 4;
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a3, a0, pt_stream::kPtr);  // a3 = the destination
    lw(a0, a0, pt_stream::kStride);  // a0 = the stride
    if (a0 == v1) {
        // 0x004779f0: stride 4: sub_476140(dst, count * 4, colour word)
        charge(ctx, 6);
        mult(a1, a1, a0);
        lw(a2, a2, ptank_block::kConstColour);
        a0 = a3;
        jal(ctx, 0x4779F8u, gen::fn_sub_476140_00476140);
        backedge(ctx);
    } else {
        // 0x00477838: count > 0?
        charge(ctx, 3);
        at = slt(0, a1);
        t0 = 0;  // t0 = the elements written
        if (at != 0) {
            // 0x00477844: count > 8?
            charge(ctx, 3);
            at = slti(a1, 9);
            v1 = addiu(a1, -8);  // v1 = count - 8
            if (at == 0) {
                // 0x00477850: the unrolled loop's guard: 0 <= count < 0x7FFFFFFF
                charge(ctx, 3);
                at = slt(a1, 0);
                t1 = 0;
                if (at == 0) {
                    // 0x0047785c
                    charge(ctx, 5);
                    at = 0x7FFF0000;
                    at = at | 0xFFFF;
                    at = slt(a1, at);
                    if (at != 0) {
                        // 0x00477870
                        charge(ctx, 1);
                        t1 = 1;
                    }
                }
                // 0x00477874
                charge(ctx, 2);
                if (t1 != 0) {
                    for (;;) {
                        // 0x0047787c: eight elements a3, s2, s1, s0, t9, t8, t7, t6
                        charge(ctx, 75);
                        lbu(t5, a2, ptank_block::kConstColour);
                        s2 = addu(a3, a0);
                        lbu(t4, a2, ptank_block::kConstColour + 1);
                        s1 = addu(s2, a0);
                        lbu(t3, a2, ptank_block::kConstColour + 2);
                        s0 = addu(s1, a0);
                        lbu(t2, a2, ptank_block::kConstColour + 3);
                        t9 = addu(s0, a0);
                        t8 = addu(t9, a0);
                        t0 = addiu(t0, 8);
                        t7 = addu(t8, a0);
                        t1 = slt(t0, v1);
                        t6 = addu(t7, a0);
                        sb(t5, a3, 0);
                        sb(t4, a3, 1);
                        sb(t3, a3, 2);
                        sb(t2, a3, 3);
                        lbu(t5, a2, 124);
                        a3 = addu(t6, a0);
                        lbu(t4, a2, 125);
                        lbu(t3, a2, 126);
                        lbu(t2, a2, 127);
                        sb(t5, s2, 0);
                        sb(t4, s2, 1);
                        sb(t3, s2, 2);
                        sb(t2, s2, 3);
                        lbu(t5, a2, 124);
                        lbu(t4, a2, 125);
                        lbu(t3, a2, 126);
                        lbu(t2, a2, 127);
                        sb(t5, s1, 0);
                        sb(t4, s1, 1);
                        sb(t3, s1, 2);
                        sb(t2, s1, 3);
                        lbu(t5, a2, 124);
                        lbu(t4, a2, 125);
                        lbu(t3, a2, 126);
                        lbu(t2, a2, 127);
                        sb(t5, s0, 0);
                        sb(t4, s0, 1);
                        sb(t3, s0, 2);
                        sb(t2, s0, 3);
                        lbu(t5, a2, 124);
                        lbu(t4, a2, 125);
                        lbu(t3, a2, 126);
                        lbu(t2, a2, 127);
                        sb(t5, t9, 0);
                        sb(t4, t9, 1);
                        sb(t3, t9, 2);
                        sb(t2, t9, 3);
                        lbu(t5, a2, 124);
                        lbu(t4, a2, 125);
                        lbu(t3, a2, 126);
                        lbu(t2, a2, 127);
                        sb(t5, t8, 0);
                        sb(t4, t8, 1);
                        sb(t3, t8, 2);
                        sb(t2, t8, 3);
                        lbu(t5, a2, 124);
                        lbu(t4, a2, 125);
                        lbu(t3, a2, 126);
                        lbu(t2, a2, 127);
                        sb(t5, t7, 0);
                        sb(t4, t7, 1);
                        sb(t3, t7, 2);
                        sb(t2, t7, 3);
                        lbu(t5, a2, 124);
                        lbu(t4, a2, 125);
                        lbu(t3, a2, 126);
                        lbu(t2, a2, 127);
                        sb(t5, t6, 0);
                        sb(t4, t6, 1);
                        sb(t3, t6, 2);
                        sb(t2, t6, 3);
                        if (t1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
            // 0x004779a8: the rest, one per iteration
            charge(ctx, 3);
            at = slt(t0, a1);
            if (at != 0) {
                for (;;) {
                    // 0x004779b4: one element
                    charge(ctx, 12);
                    lbu(t4, a2, ptank_block::kConstColour);
                    t0 = addiu(t0, 1);
                    lbu(t3, a2, ptank_block::kConstColour + 1);
                    v1 = slt(t0, a1);
                    lbu(t2, a2, ptank_block::kConstColour + 2);
                    lbu(t1, a2, ptank_block::kConstColour + 3);
                    sb(t4, a3, 0);
                    sb(t3, a3, 1);
                    sb(t2, a3, 2);
                    sb(t1, a3, 3);
                    a3 = addu(a3, a0);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004779e4
                charge(ctx, 1);
            }
        }
    }
    // 0x004779e8
    charge(ctx, 2);
    ld(ra, sp, 0x30);
    // 0x00477a08
    charge(ctx, 5);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x00477C90 sub_477C90 -- 536 bytes; frame 0x20: ra sp+0x0
// sub_477C90 [PTank constant UV rectangle](stream, count, tank): every element of the {pointer, stride} stream
// = the 16 bytes at tank + 144 (u0, v0 at +144, u1, v1 at +152); a stride of 16 goes to the streamer sub_476720 (the
// rectangle on the stack), any other is written here, eight elements per iteration while at least 9 are left.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void sub_477C90(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lw,
          hg::lwc1, hg::mult, hg::sd, hg::slt, hg::slti, hg::swc1;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x00477c90
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 16;
    sd(ra, sp, 0x0);
    t8 = addiu(a2, ptank_block::kConstUv0);  // t8 = &(u0, v0)
    lw(t6, a0, pt_stream::kStride);  // t6 = the stride
    lw(t7, a0, pt_stream::kPtr);  // t7 = the destination
    t5 = addiu(a2, ptank_block::kConstUv1);  // t5 = &(u1, v1)
    if (t6 == v1) {
        // 0x00477e68: stride 16: the rectangle to the stack, sub_476720(dst, count * 16, rect)
        charge(ctx, 14);
        lwc1(f0, a2, ptank_block::kConstUv0);
        swc1(f0, sp, 0x10);
        lwc1(f0, a2, ptank_block::kConstUv0 + 4);
        swc1(f0, sp, 0x14);
        lwc1(f0, a2, ptank_block::kConstUv1);
        swc1(f0, sp, 0x18);
        lwc1(f0, a2, ptank_block::kConstUv1 + 4);
        swc1(f0, sp, 0x1C);
        mult(a1, a1, t6);
        a0 = t7;
        a2 = addiu(sp, 0x10);
        jal(ctx, 0x477E90u, gen::fn_sub_476720_00476720);
        backedge(ctx);
    } else {
        // 0x00477cb0: count > 0?
        charge(ctx, 3);
        at = slt(0, a1);
        t9 = 0;  // t9 = the elements written
        if (at != 0) {
            // 0x00477cbc: count > 8?
            charge(ctx, 3);
            at = slti(a1, 9);
            t4 = addiu(a1, -8);  // t4 = count - 8
            if (at == 0) {
                // 0x00477cc8: the unrolled loop's guard: 0 <= count < 0x7FFFFFFF
                charge(ctx, 3);
                at = slt(a1, 0);
                v1 = 0;
                if (at == 0) {
                    // 0x00477cd4
                    charge(ctx, 5);
                    at = 0x7FFF0000;
                    at = at | 0xFFFF;
                    at = slt(a1, at);
                    if (at != 0) {
                        // 0x00477ce8
                        charge(ctx, 1);
                        v1 = 1;
                    }
                }
                // 0x00477cec
                charge(ctx, 2);
                if (v1 != 0) {
                    for (;;) {
                        // 0x00477cf4: eight elements t7, t3, t2, t1, t0, a3, a2, a0
                        charge(ctx, 75);
                        lwc1(f0, t8, 0);
                        t3 = addu(t7, t6);
                        t2 = addu(t3, t6);
                        t9 = addiu(t9, 8);
                        t1 = addu(t2, t6);
                        v1 = slt(t9, t4);
                        t0 = addu(t1, t6);
                        a3 = addu(t0, t6);
                        a2 = addu(a3, t6);
                        swc1(f0, t7, 0);
                        a0 = addu(a2, t6);
                        lwc1(f0, t8, 4);
                        swc1(f0, t7, 4);
                        lwc1(f0, t5, 0);
                        swc1(f0, t7, 8);
                        lwc1(f0, t5, 4);
                        swc1(f0, t7, 12);
                        lwc1(f0, t8, 0);
                        t7 = addu(a0, t6);
                        swc1(f0, t3, 0);
                        lwc1(f0, t8, 4);
                        swc1(f0, t3, 4);
                        lwc1(f0, t5, 0);
                        swc1(f0, t3, 8);
                        lwc1(f0, t5, 4);
                        swc1(f0, t3, 12);
                        lwc1(f0, t8, 0);
                        swc1(f0, t2, 0);
                        lwc1(f0, t8, 4);
                        swc1(f0, t2, 4);
                        lwc1(f0, t5, 0);
                        swc1(f0, t2, 8);
                        lwc1(f0, t5, 4);
                        swc1(f0, t2, 12);
                        lwc1(f0, t8, 0);
                        swc1(f0, t1, 0);
                        lwc1(f0, t8, 4);
                        swc1(f0, t1, 4);
                        lwc1(f0, t5, 0);
                        swc1(f0, t1, 8);
                        lwc1(f0, t5, 4);
                        swc1(f0, t1, 12);
                        lwc1(f0, t8, 0);
                        swc1(f0, t0, 0);
                        lwc1(f0, t8, 4);
                        swc1(f0, t0, 4);
                        lwc1(f0, t5, 0);
                        swc1(f0, t0, 8);
                        lwc1(f0, t5, 4);
                        swc1(f0, t0, 12);
                        lwc1(f0, t8, 0);
                        swc1(f0, a3, 0);
                        lwc1(f0, t8, 4);
                        swc1(f0, a3, 4);
                        lwc1(f0, t5, 0);
                        swc1(f0, a3, 8);
                        lwc1(f0, t5, 4);
                        swc1(f0, a3, 12);
                        lwc1(f0, t8, 0);
                        swc1(f0, a2, 0);
                        lwc1(f0, t8, 4);
                        swc1(f0, a2, 4);
                        lwc1(f0, t5, 0);
                        swc1(f0, a2, 8);
                        lwc1(f0, t5, 4);
                        swc1(f0, a2, 12);
                        lwc1(f0, t8, 0);
                        swc1(f0, a0, 0);
                        lwc1(f0, t8, 4);
                        swc1(f0, a0, 4);
                        lwc1(f0, t5, 0);
                        swc1(f0, a0, 8);
                        lwc1(f0, t5, 4);
                        swc1(f0, a0, 12);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
            // 0x00477e20: the rest, one per iteration
            charge(ctx, 3);
            at = slt(t9, a1);
            if (at != 0) {
                for (;;) {
                    // 0x00477e2c: one element
                    charge(ctx, 12);
                    lwc1(f0, t8, 0);
                    t9 = addiu(t9, 1);
                    v1 = slt(t9, a1);
                    swc1(f0, t7, 0);
                    lwc1(f0, t8, 4);
                    swc1(f0, t7, 4);
                    lwc1(f0, t5, 0);
                    swc1(f0, t7, 8);
                    lwc1(f0, t5, 4);
                    swc1(f0, t7, 12);
                    t7 = addu(t7, t6);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x00477e5c
                charge(ctx, 1);
            }
        }
    }
    // 0x00477e60
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    // 0x00477ea0
    charge(ctx, 2);
    sp = addiu(sp, 0x20);
}

// ==================================================================================================================
// Batch 3: the image-upload header and the VU1 record upload
// ==================================================================================================================

// [image upload header] A 10-qw GIF packet (_rwDMAOpenGIFPkt(10)): a DMA tag word (0x50000006 with the image's
// 64-byte-aligned size / address argument in its upper word), the template quadwords at 0x965A70 / 0x965A40 /
// 0x965A50 / 0x965A60 (GIF tag, TRXPOS, TRXDIR, ...) around BITBLTBUF = {DBP $a2 & 0x3FFF, DBW $a3, DPSM / SPSM $t0,
// SBW 10} and TRXREG = {RRW $a0, RRH $a1}. $t2 only changes the first block's cost (57 / 56 cycles). Arguments:
// $a0 width, $a1 height, $a2 block pointer, $a3 buffer width, $t0 pixel format, $t1 size, $t2 flag.
void sub_4EF540(EEContext& ctx) {
    Regs r{ctx};
    enter(ctx, 15);
    Frame f(ctx, 112);
    f.sd(GPR_RA, 96);
    f.sq(GPR_S5, 80);
    f.sq(GPR_S4, 64);
    r.d(GPR_S5, r.get(GPR_T1));
    f.sq(GPR_S3, 48);
    r.d(GPR_S4, r.get(GPR_A0));
    f.sq(GPR_S2, 32);
    r.d(GPR_S3, r.get(GPR_A1));
    f.sq(GPR_S1, 16);
    r.d(GPR_S2, r.get(GPR_A2));
    f.sq(GPR_S0, 0);
    r.d(GPR_S1, r.get(GPR_A3));
    r.d(GPR_S0, r.get(GPR_T0));
    const bool flag = r.get(GPR_T2) != 0;
    charge(ctx, flag ? 57 : 56);
    r.d(GPR_A0, 10);
    jal(ctx, flag ? 0x4EF57Cu : 0x4EF660u, gen::fn__rwDMAOpenGIFPkt_004d54e0);
    auto zext = [](u64 v) { return v & 0xFFFFFFFFull; };
    const u64 width = zext(r.get(GPR_S4)), height = zext(r.get(GPR_S3)), dbp = r.get(GPR_S2) & 0x3FFFu;
    const u64 dbw = zext(r.get(GPR_S1)), psm = zext(r.get(GPR_S0));
    const u64 size = static_cast<u32>(r.get32(GPR_S5) + 63u) & ~63u;
    const u64 tag = (size << 32) | 0x50000006u;
    const u64 bitbltbuf = (psm << 24) | (dbp << 32) | (dbw << 48) | (psm << 56) | 0xA0000u;
    const u64 trxreg = (height << 32) | width;
    // The packet, in the original's store order, and the registers it leaves (no check point or call follows).
    const u32 p = spr_ptr(ctx);
    sq(ctx, p, tag, 0);
    const u128 tpl70 = guest::load<u128>(ctx, 0x965A70u);
    sq(ctx, p + 16, tpl70);
    const u128 tpl40 = guest::load<u128>(ctx, 0x965A40u);
    sq(ctx, p + 32, tpl40);
    sq(ctx, p + 48, bitbltbuf, 80);  // BITBLTBUF
    const u128 tpl50 = guest::load<u128>(ctx, 0x965A50u);
    sq(ctx, p + 64, tpl50);
    sq(ctx, p + 80, trxreg, 82);  // TRXREG
    const u128 tpl60 = guest::load<u128>(ctx, 0x965A60u);
    sq(ctx, p + 96, tpl60);
    set_spr_ptr(ctx, spr_ptr(ctx) + 112);
    r.q(GPR_T3, tag, 0);
    r.q(GPR_T2, bitbltbuf, 80);
    r.q(GPR_A3, trxreg, 82);
    r.d(GPR_T0, trxreg);
    r.q(GPR_T1, tpl70);
    r.q(GPR_A2, tpl40);
    r.q(GPR_A1, tpl50);
    r.q(GPR_A0, tpl60);
    r.w(GPR_V1, p + 112);
    charge(ctx, 9);
}

// 0x0046C330 sub_46C330 -- 632 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_46C330 [VU1 record upload](src, n): `n` records of five quadwords (80 bytes) from `src` as one VIF packet:
// DMA cnt 5n + 1, STCYCL 4,4, UNPACK V4-32 (5n + 1 qw) to VU1 0x2FF, the count quadword {n, 0}, then the records
// copied verbatim, eight per iteration while at least 9 are left, then one by one. Returns src.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_46C330(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsrl32, hg::enter, hg::jal, hg::ld,
          hg::lq, hg::lw, hg::pcpyld, hg::sd, hg::sll, hg::sltiu, hg::sltu, hg::sq, hg::sw;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046c330
    enter(ctx, 39);  // entry check point + this block's cycles: frame, _rwDMAOpenVIFPkt(0, 5n + 2)
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;  // s1 = src
    s0 = a1;  // s0 = n
    a0 = 0;
    v0 = sll(s0, 2);
    s2 = addu(v0, s0);  // s2 = 5n
    a1 = addiu(s2, 2);  // $a1 = the packet's qwords
    jal(ctx, 0x46C358u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    v1 = addiu(s2, 1);  // v1 = 5n + 1: the UNPACK's qwords
    lw(a2, gp, kGpSprWritePtr);  // a2 = the scratchpad write pointer
    v0 = sll(v1, 16);  // the qword count into the UNPACK's NUM field
    at = sltu(0, s0);
    a0 = dsll32(v0, 0);
    v1 = dsll32(v1, 0);
    a0 = dsrl32(a0, 0);
    v0 = 0x6C000000;  // UNPACK V4-32 (cmd 0x6C)
    a0 = a0 | v0;
    v1 = dsrl32(v1, 0);
    a1 = a0 | 0x2FF;  // ... to VU1 address 0x2FF
    v0 = 0x1000000;
    // the first quadword: {DMA cnt tag (id 1, qwc 5n + 1), STCYCL 4,4 | UNPACK}
    a0 = v0 | 0x404;  // STCYCL 4,4 (0x01000404)
    a1 = dsll32(a1, 0);
    v0 = 0x10000000;  // the DMA tag id cnt
    a0 = a1 | a0;
    v0 = v1 | v0;
    a1 = 0;
    pcpyld(v0, a0, v0);
    sq(v0, a2, 0);  // packet + 0: the tag
    v1 = 0;
    v0 = dsll32(s0, 0);
    a0 = addiu(a2, 32);  // a0 = the records' destination
    v0 = dsrl32(v0, 0);
    pcpyld(v0, v1, v0);
    sq(v0, a2, 16);  // packet + 16: the count quadword {n, 0}
    // the records (a1 = the records copied), n > 0
    if (at != 0) {
        // 0x0046c3cc: eight records per iteration while at least 9 are left
        charge(ctx, 3);
        at = sltiu(s0, 9);
        v0 = addiu(s0, -8);
        if (at == 0) {
            // 0x0046c3d8: n >= 9
            charge(ctx, 1);
            v1 = s1;  // v1 = the source
            for (;;) {
                // 0x0046c3dc: eight 80-byte records (40 quadwords)
                charge(ctx, 85);
                lq(a3, v1, 0);
                a1 = addiu(a1, 8);
                a2 = sltu(a1, v0);
                sq(a3, a0, 0);
                lq(a3, v1, 16);
                sq(a3, a0, 16);
                lq(a3, v1, 32);
                sq(a3, a0, 32);
                lq(a3, v1, 48);
                sq(a3, a0, 48);
                lq(a3, v1, 64);
                sq(a3, a0, 64);
                lq(a3, v1, 80);
                sq(a3, a0, 80);
                lq(a3, v1, 96);
                sq(a3, a0, 96);
                lq(a3, v1, 112);
                sq(a3, a0, 112);
                lq(a3, v1, 128);
                sq(a3, a0, 128);
                lq(a3, v1, 144);
                sq(a3, a0, 144);
                lq(a3, v1, 160);
                sq(a3, a0, 160);
                lq(a3, v1, 176);
                sq(a3, a0, 176);
                lq(a3, v1, 192);
                sq(a3, a0, 192);
                lq(a3, v1, 208);
                sq(a3, a0, 208);
                lq(a3, v1, 224);
                sq(a3, a0, 224);
                lq(a3, v1, 240);
                sq(a3, a0, 240);
                lq(a3, v1, 256);
                sq(a3, a0, 256);
                lq(a3, v1, 272);
                sq(a3, a0, 272);
                lq(a3, v1, 288);
                sq(a3, a0, 288);
                lq(a3, v1, 304);
                sq(a3, a0, 304);
                lq(a3, v1, 320);
                sq(a3, a0, 320);
                lq(a3, v1, 336);
                sq(a3, a0, 336);
                lq(a3, v1, 352);
                sq(a3, a0, 352);
                lq(a3, v1, 368);
                sq(a3, a0, 368);
                lq(a3, v1, 384);
                sq(a3, a0, 384);
                lq(a3, v1, 400);
                sq(a3, a0, 400);
                lq(a3, v1, 416);
                sq(a3, a0, 416);
                lq(a3, v1, 432);
                sq(a3, a0, 432);
                lq(a3, v1, 448);
                sq(a3, a0, 448);
                lq(a3, v1, 464);
                sq(a3, a0, 464);
                lq(a3, v1, 480);
                sq(a3, a0, 480);
                lq(a3, v1, 496);
                sq(a3, a0, 496);
                lq(a3, v1, 512);
                sq(a3, a0, 512);
                lq(a3, v1, 528);
                sq(a3, a0, 528);
                lq(a3, v1, 544);
                sq(a3, a0, 544);
                lq(a3, v1, 560);
                sq(a3, a0, 560);
                lq(a3, v1, 576);
                sq(a3, a0, 576);
                lq(a3, v1, 592);
                sq(a3, a0, 592);
                lq(a3, v1, 608);
                sq(a3, a0, 608);
                lq(a3, v1, 624);
                sq(a3, a0, 624);
                v1 = addiu(v1, 640);
                a0 = addiu(a0, 640);
                if (a2 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0046c530: the rest, one record per iteration
        charge(ctx, 3);
        at = sltu(a1, s0);
        if (at != 0) {
            // 0x0046c53c: a2 = src + 80 * copied
            charge(ctx, 4);
            v0 = sll(a1, 2);
            v0 = addu(v0, a1);
            v0 = sll(v0, 4);
            a2 = addu(s1, v0);
            for (;;) {
                // 0x0046c54c: one record
                charge(ctx, 15);
                lq(v1, a2, 0);
                a1 = addiu(a1, 1);
                v0 = sltu(a1, s0);
                sq(v1, a0, 0);
                lq(v1, a2, 16);
                sq(v1, a0, 16);
                lq(v1, a2, 32);
                sq(v1, a0, 32);
                lq(v1, a2, 48);
                sq(v1, a0, 48);
                lq(v1, a2, 64);
                sq(v1, a0, 64);
                a2 = addiu(a2, 80);
                a0 = addiu(a0, 80);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x0046c588 (the shared epilogue, written out on this path): the write pointer past the records; return src
    charge(ctx, 8);
    sw(a0, gp, kGpSprWritePtr);
    v0 = s1;
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

}  // namespace p3fes::game

// ==================================================================================================================
// The recompiled program's entry points
// ==================================================================================================================
namespace p3fes::recomp_gen {

using p3fes::EEContext;
namespace guest = p3fes::game::guest;
namespace core = p3fes::ee::core;
namespace g = p3fes::game;

void fn_sub_4D4280_004d4280(EEContext& ctx) { g::sub_4D4280(ctx); }
void fn__rwDMAWaitQueue_004d53f0(EEContext& ctx) { g::_rwDMAWaitQueue(ctx); }
void fn__rwDMAReqFlip_004d5270(EEContext& ctx) { g::_rwDMAReqFlip(ctx, core::gpr64(ctx, GPR_A0), core::gpr64(ctx, GPR_A1)); }
void fn_SkyRasterShowRaster_004d9460(EEContext& ctx) { guest::ret32(ctx, g::SkyRasterShowRaster(ctx)); }
void fn_sub_4E4E40_004e4e40(EEContext& ctx) { g::sub_4E4E40(ctx); }
void fn_sub_4E4180_004e4180(EEContext& ctx) { g::sub_4E4180(ctx, core::gpr64(ctx, GPR_A0)); }
void fn_sub_4E4420_004e4420(EEContext& ctx) { g::sub_4E4420(ctx); }
void fn_sub_4E4560_004e4560(EEContext& ctx) { g::sub_4E4560(ctx); }
void fn_sub_4E46C0_004e46c0(EEContext& ctx) { g::sub_4E46C0(ctx); }

void fn_sub_4E4800_004e4800(EEContext& ctx) {
    guest::ret32(ctx, g::sub_4E4800(ctx, guest::arg32(ctx, 1), core::gpr64(ctx, GPR_A2)));
}

void fn_sub_4EF540_004ef540(EEContext& ctx) { g::sub_4EF540(ctx); }

}  // namespace p3fes::recomp_gen
