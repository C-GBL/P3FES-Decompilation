// Pure leaves of the RenderWare sky driver (game/include/p3fes/game/rw_leaves.h), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/22_rendering.md; queue docs/ANALYSIS/queue_rendering.txt, "Full queue"). Phase 5: these replace
// the recompiled bodies listed under "render_rw" in game/replaced.txt; tests/game/test_render_rw.cpp runs each one
// against its __recomp body and compares every register and the touched memory.
//
// Conventions of this file:
//  * Guest values that live in GPRs are kept as u64 register images (`lws` = `lw`, sign-extended; the 32-bit ALU
//    results go through ee::core's add32/sub32/sll, which sign-extend like ADDU/SUBU/SLL). Branches compare whole
//    64-bit registers where the original's `beq`/`bne`/`sltu` do (an argument a caller passes with stray upper bits
//    behaves as before).
//  * Float values are EE single bit patterns (`F`) combined through ee::fpu (round toward zero, no Inf/NaN, the
//    recompiler-oracle addition), in the compiled operand order; MULA/MADDA/MADD/MSUB go through an explicit `acc`.
//    The registers the original leaves (FPRs, ACC, FCR31 C / D / I) are written back at the end.
//  * Block costs: recomp/generated (fn_0041_00458b00_0046bfb0.cpp ... fn_0042_..._004fb100.cpp); `guest::backedge`
//    marks every back-edge check of the generated body.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 27 of the 38 functions here are p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: faults only 17, $v0 4, scratch GPRs 4,
// frame/spills 2); the others are the hand-written versions the conventions above describe. The 27 were made
// readable on 2026-10-22 (slice read_misc): a role comment each (the bracketed role names of rw_leaves.h), record
// offsets by name (the anonymous namespace below: matrices, planes, images, atomics, Im3D / PS2All records), the
// texture-cache words and RW globals as mview::hi / lo of the rwl:: addresses, the render-state shadows as $gp
// offsets, named registers, block roles, and no goto left. Every guest statement, frame, link, cycle charge and
// check point is the generated body's, in its order on every path.
#include "p3fes/game/rw_leaves.h"

#include "p3fes/ee/core.h"
#include "p3fes/ee/fpu.h"
#include "p3fes/ee/hilo.h"
#include "p3fes/ee/vu0.h"
#include "p3fes/game/guest.h"
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/misc_view.h"
#include "p3fes/game/task.h"  // kwln::Frame / kwln::jal / kwln::jalr: the original's frame, spills and link values

namespace p3fes::recomp_gen {
void fn_memset_00521408(p3fes::EEContext&);      // memset(dst, value, n)
void fn_sub_4C2860_004c2860(p3fes::EEContext&);  // (this file)
void fn_sub_46AD20_0046ad20(p3fes::EEContext&);  // (this file)
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

using namespace rwl;
namespace core = ee::core;
namespace fpu = ee::fpu;
namespace vu0 = ee::vu0;

// --- register images and guest memory ----------------------------------------------------------------------------
u64 reg(const EEContext& c, unsigned r) { return core::gpr64(c, r); }
void setr(EEContext& c, unsigned r, u64 v) { core::set_gpr64(c, r, v); }
u64 sx(u32 v) { return core::sext32(v); }
u32 lo(u64 v) { return static_cast<u32>(v); }
u32 gpw(const EEContext& c, s32 off) { return core::gpr32(c, GPR_GP) + static_cast<u32>(off); }

u32 lw(const EEContext& c, u32 va) { return guest::load<u32>(c, va); }
u64 lws(const EEContext& c, u32 va) { return sx(lw(c, va)); }
void sw(EEContext& c, u32 va, u64 v) { guest::store<u32>(c, va, lo(v)); }

// --- named immediates of the register-level (p3fes_handgen) bodies ----------------------------------------------
// Record offsets as the load / store immediates, from the instructions of the functions that use them (and the
// notes of the earlier hand versions). `hi` / `lo` / `la` / `flt` of an address are mview:: (misc_view.h); this
// file's own `lo(u64)` above is the low word of a register image.
// The sky driver's render-state shadows (sub_4D81B0), $gp-relative.
inline constexpr s32 kGpRsState5 = -20256;          // 0x7CDDD0: state 5
inline constexpr s32 kGpRsState4Override = -16860;  // 0x7CEB14: set -> state 4 reads 0
inline constexpr s32 kGpRsState4 = -16864;          // 0x7CEB10: f32, state 4
inline constexpr s32 kGpRsState3 = -17072;          // 0x7CEA40: state 3
inline constexpr s32 kGpRsState2Shadow = -17032;    // 0x7CEA68: u64 GS register shadow, state 2 = byte 0 | byte 4 << 24
inline constexpr s32 kGpCurrentRaster = -17120;     // 0x7CEA10: the current raster
inline constexpr s32 kGpRsState1Enable = -16936;    // 0x7CEAC8: state 1 is known only while set
inline constexpr s32 kGpRsState1 = -16960;          // 0x7CEAB0: state 1
// {base, count, capacity, stride}: the singly linked array.
namespace slist {
inline constexpr s32 kBase = 0, kCount = 4, kStride = 12;  // (+8: the capacity)
}  // namespace slist
// RwMatrix {right, flags; up, pad; at, pad; pos, pad}: the rows (quadwords) and their words.
namespace mtx {
inline constexpr s32 kRight = 0, kUp = 16, kAt = 32, kPos = 48;
inline constexpr s32 kRightX = 0, kRightY = 4, kRightZ = 8, kFlags = 12;
inline constexpr s32 kUpX = 16, kUpY = 20, kUpZ = 24;
inline constexpr s32 kAtX = 32, kAtY = 36, kAtZ = 40;
inline constexpr s32 kPosX = 48, kPosY = 52, kPosZ = 56;
}  // namespace mtx
inline constexpr s32 kMatrixModuleFlags = 4;  // the matrix module's flags word (at its plugin offset); 0x20000 identity
namespace v3 {
inline constexpr s32 kX = 0, kY = 4, kZ = 8;
}  // namespace v3
namespace sphere {
inline constexpr s32 kX = 0, kY = 4, kZ = 8, kRadius = 12;
}  // namespace sphere
// A frustum plane, 20 bytes: {normal, distance, the box-corner selectors x y z}.
namespace plane {
inline constexpr s32 kNx = 0, kNy = 4, kNz = 8, kDist = 12, kSelX = 16, kSelY = 17, kSelZ = 18;
}  // namespace plane
inline constexpr s32 kCameraPlanes = 148;  // sub_4C9DF0: the camera's six planes
inline constexpr s32 kFrustumPlanes = 96;  // sub_4A3F70: the planes at the camera plugin data + 96
inline constexpr s32 kSectorBBox = 96;     // sub_4A3F70: the sector's box {inf xyz, sup xyz} (12-byte corners)
inline constexpr s32 kFrameRoot = 160;     // RwFrame: the root frame
inline constexpr s32 kFrameFlags = 3;      // its dirty-flags byte
// RwImage.
namespace image {
inline constexpr s32 kWidth = 4, kHeight = 8, kDepth = 12, kStride = 16, kPixels = 20, kPalette = 24;  // (+0: flags)
}  // namespace image
inline constexpr s32 kRasterDepth = 8;     // RwRaster: depth
inline constexpr s32 kExtCacheSlot = 88;   // the sky raster extension: the texture-cache slot pointer
inline constexpr s32 kIm3DPool = 64;       // the Im3D module state: the 60-byte pool
inline constexpr s32 kIm3DOpen = 68;       // its "open" word (inside the pool)
inline constexpr s32 kIm3DPoolSize = 60;
inline constexpr s32 kSkinMatrices = 12;   // RpSkin: the skin-to-bone matrices
// RpAtomic, its geometry and the 28-byte morph targets (sub_491100).
namespace atomic {
inline constexpr s32 kObjFlags = 3, kGeometry = 24;
inline constexpr s32 kSphereX = 28, kSphereY = 32, kSphereZ = 36, kSphereR = 40;  // the interpolated sphere
inline constexpr s32 kFlags = 76;                                                 // bit 1: the sphere is stale
inline constexpr s32 kTarget = 80, kNextTarget = 82;                              // s16
inline constexpr s32 kBlendA = 88, kBlendB = 92;                                  // t = A * B
}  // namespace atomic
namespace geom {
inline constexpr s32 kTargetCount = 24, kTargets = 92;
}  // namespace geom
namespace morph {
inline constexpr s32 kSphereX = 4, kSphereY = 8, kSphereZ = 12, kSphereR = 16;
}  // namespace morph
inline constexpr s32 kMatListMaterials = 0;  // RpMaterialList: the material pointer array
// The find-sector query {sector, found} and the camera's frustum sector list {sectors, ?, count}.
namespace query {
inline constexpr s32 kSector = 0, kFound = 4;
}  // namespace query
namespace seclist {
inline constexpr s32 kSectors = 0, kCount = 8;
}  // namespace seclist
inline constexpr s32 kNodePrivate = 20, kPrivGroupMeshes = 24;  // the PS2All node and its private data
// The PS2All mesh-instance record (sub_4A0C20) and what it points at.
namespace inst {
inline constexpr s32 kObject = 12, kMesh = 44, kResEntry = 48, kFlags = 52, kObjFlags = 56;
}  // namespace inst
inline constexpr s32 kMeshVertexCount = 4;   // the mesh: vertex count
inline constexpr s32 kResInstHeader = 24;    // the resEntry: its instance header
inline constexpr s32 kInstHeaderCount = 12;  // the header: index count
inline constexpr s32 kResGeomFlags = 44;     // the flags word the object flags are compared with
// The Im3D mesh-cache record, the mesh header it is pointed at, and the Im3D source (sub_4A24A0).
namespace mcache {
inline constexpr s32 kHeader = 12, kRecord = 16;
}  // namespace mcache
namespace mhdr {
inline constexpr s32 kFlags = 0, kVertexCount = 8, kOffset = 12, kIndices = 16, kIndexCount = 20, kList = 24;
}  // namespace mhdr
namespace im3dsrc {
inline constexpr s32 kPrimType = 36, kIndices = 40, kVertexCount = 44;
}  // namespace im3dsrc
inline constexpr s32 kIm3DPrimFlags = 39;    // the prim-type flags table at the Im3D prim offset + 39
inline constexpr s32 kCacheRecordWord4 = 4;  // cleared in the gp mesh-cache record
// The PDS pipeline registry {entries, count}, 20-byte entries with the id at +8.
namespace pds {
inline constexpr s32 kEntries = 0, kCount = 4;
}  // namespace pds
inline constexpr s32 kPdsEntryId = 8;
inline constexpr s32 kTexName = 16;  // RwTexture: the name
inline constexpr s32 kNameMax = 30;  // sub_468720: at most 30 characters

}  // namespace

// =================================================================================================================
// rwcore
// =================================================================================================================

u64 sub_4C1C50(EEContext& ctx, u64 error) {
    // The error slot is {pluginID, errorCode} at the error module's plugin offset in the RW globals; "empty" is
    // {0, 0x80000000}. The first error after a clear wins; later ones are dropped.
    guest::enter(ctx, 7);
    const u32 e = lo(error);
    u64 v1 = lws(ctx, gpw(ctx, kGpErrorOffset));
    u64 a1 = core::add32(kRwGlobals, v1);  // the slot
    if (lws(ctx, lo(a1)) == 0) {
        guest::charge(ctx, 4);
        v1 = core::lui(0x8000);
        if (lws(ctx, lo(a1) + 4) == v1) {
            guest::charge(ctx, 4);
            if ((lws(ctx, e + 4) & v1) == 0) {  // an error code without bit 31 keeps the plugin ID
                guest::charge(ctx, 2);
                sw(ctx, lo(a1), lw(ctx, e));
            } else {
                guest::charge(ctx, 2);
                sw(ctx, lo(a1), 0);
                guest::backedge(ctx);  // `b` back into the shared store of the code
            }
            guest::charge(ctx, 6);
            v1 = lws(ctx, gpw(ctx, kGpErrorOffset));
            a1 = lws(ctx, e + 4);
            sw(ctx, lo(core::add32(kRwGlobals, v1)) + 4, a1);
        }
    }
    guest::charge(ctx, 2 + 2);
    setr(ctx, GPR_V1, v1);
    setr(ctx, GPR_A1, a1);
    setr(ctx, GPR_V0, error);
    return error;
}

u64 sub_4C1D10(EEContext& ctx, u32 code) {
    // Variadic: the prologue homes $a1..$t3 (the EABI argument registers after the code) into the va_list area of
    // its 80-byte frame; nothing reads them in retail (the message formatting is compiled out).
    guest::enter(ctx, 14);
    const u32 frame = core::gpr32(ctx, GPR_SP) - 80;
    for (unsigned i = 0; i < 7; ++i) guest::store<u64>(ctx, frame + 24 + 8 * i, reg(ctx, GPR_A1 + i));
    setr(ctx, GPR_AT, 1);  // `slti at, v0, 8` of the va_start bookkeeping, v0 = 1
    const u64 v0 = sx(code);
    setr(ctx, GPR_V0, v0);
    return v0;
}

// 0x004C1E60 sub_4C1E60 -- 8 bytes; leaf frame (no stack)
// sub_4C1E60 [singly linked array: empty]: list->count = 0. One block of 2.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4C1E60(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sw;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    Gpr& list = a0;
    // 0x004c1e60
    enter(ctx, 2);  // entry check point + this block's cycles
    sw(zero, list, slist::kCount);
}

// 0x004C2090 sub_4C2090 -- 32 bytes; leaf frame (no stack)
// sub_4C2090 [array base, 0 when empty]: list->count != 0 ? list->base : 0.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4C2090(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    Gpr& list = a0;
    // 0x004c2090
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, list, slist::kCount);
    if (v0 == 0) {
        // 0x004c20a4: empty: 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004c209c: list->base
        charge(ctx, 2);
        lw(v0, list, slist::kBase);
    }
    // 0x004c20a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004C2120 sub_4C2120 -- 8 bytes; leaf frame (no stack)
// sub_4C2120 [array count]: list->count. One block of 2.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4C2120(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    Gpr& list = a0;
    // 0x004c2120
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, list, slist::kCount);
}

// 0x004C21B0 sub_4C21B0 -- 20 bytes; leaf frame (no stack)
// sub_4C21B0 [array entry]: list->base + list->stride * index (MULT: HI/LO hold the product).
// {base, count, capacity, stride}. One block of 5.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4C21B0(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::enter, hg::lw, hg::mult;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Gpr& list = a0;
    Gpr& index = a1;
    // 0x004c21b0
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, list, slist::kStride);
    mult(v1, v0, index);
    lw(v0, list, slist::kBase);
    v0 = addu(v0, v1);
}

// 0x004C2F30 sub_4C2F30 -- 124 bytes; leaf frame (no stack)
// sub_4C2F30 [matrix product on VU0]: dst = a * b, dst flags = a.flags & b.flags; returns dst.
// RwMatrix = {right, flags; up, pad; at, pad; pos, pad}. The product runs on VU0 in macro mode: a's rows in
// vf1..vf4, b's in vf5..vf8, each result row ACC = b0 * a.x + b1 * a.y, row = ACC + b2 * a.z (+ b3 * vf00.w = b3
// for the position row), only the xyz lanes written -- the w lanes of vf9..vf12 keep what VU0 held and are
// stored with the rows (the flags word then overwrites row 0's). One block of 31.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4C2F30(EEContext& ctx) {
    using hg::Gpr, hg::Vf, hg::enter, hg::lqc2, hg::lwu, hg::sqc2, hg::sw, hg::vmadd_bc, hg::vmadda_bc, hg::vmula_bc;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Gpr& dst = a0;
    Gpr& a = a1;
    Gpr& b = a2;
    Vf vf0{ctx, 0}, vf1{ctx, 1}, vf2{ctx, 2}, vf3{ctx, 3}, vf4{ctx, 4}, vf5{ctx, 5}, vf6{ctx, 6}, vf7{ctx, 7}, vf8{ctx, 8}, vf9{ctx, 9}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12};
    // 0x004c2f30
    enter(ctx, 31);  // entry check point + this block's cycles
    lqc2(vf1, a, mtx::kRight);  // a's rows
    lqc2(vf2, a, mtx::kUp);
    lqc2(vf3, a, mtx::kAt);
    lqc2(vf4, a, mtx::kPos);
    lwu(v1, a, 12);
    lqc2(vf5, b, mtx::kRight);  // b's rows
    lqc2(vf6, b, mtx::kUp);
    lqc2(vf7, b, mtx::kAt);
    lqc2(vf8, b, mtx::kPos);
    lwu(v0, b, 12);
    // dst.right = b.right * a.right.x + b.up * a.right.y + b.at * a.right.z
    vmula_bc(0xE, vf5, vf1, 0);  // vmulax.xyz
    vmadda_bc(0xE, vf6, vf1, 1);  // vmadday.xyz
    vmadd_bc(0xE, vf9, vf7, vf1, 2);  // vmaddz.xyz
    vmula_bc(0xE, vf5, vf2, 0);  // vmulax.xyz
    vmadda_bc(0xE, vf6, vf2, 1);  // vmadday.xyz
    vmadd_bc(0xE, vf10, vf7, vf2, 2);  // vmaddz.xyz
    vmula_bc(0xE, vf5, vf3, 0);  // vmulax.xyz
    vmadda_bc(0xE, vf6, vf3, 1);  // vmadday.xyz
    vmadd_bc(0xE, vf11, vf7, vf3, 2);  // vmaddz.xyz
    // dst.pos = b.right * a.pos.x + b.up * a.pos.y + b.at * a.pos.z + b.pos
    vmula_bc(0xE, vf5, vf4, 0);  // vmulax.xyz
    vmadda_bc(0xE, vf6, vf4, 1);  // vmadday.xyz
    vmadda_bc(0xE, vf7, vf4, 2);  // vmaddaz.xyz
    vmadd_bc(0xE, vf12, vf8, vf0, 3);  // vmaddw.xyz
    v0 = v0 & v1;  // dst flags = a.flags & b.flags
    sqc2(vf9, dst, mtx::kRight);
    sqc2(vf10, dst, mtx::kUp);
    sqc2(vf11, dst, mtx::kAt);
    sqc2(vf12, dst, mtx::kPos);
    sw(v0, dst, mtx::kFlags);
    v0 = dst;
}

// 0x004C6970 sub_4C6970 -- 116 bytes; leaf frame (no stack)
// sub_4C6970 [normalise a 3-vector]: dst = src * scale, scale = 1 / |src|; a zero length (|src| <= 0) keeps the
// scale |src| itself, so dst = 0. $v0 holds the bits of 1.0f when it divided.
// Blocks 13, the division 7, the scaling 9.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4C6970(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::c_le_s, hg::charge, hg::cond, hg::div_s, hg::enter, hg::lwc1, hg::madd_s,
          hg::madda_s, hg::mtc1, hg::mul_s, hg::mula_s, hg::sqrt_s, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    Gpr& dst = a0;
    Gpr& src = a1;
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x004c6970
    enter(ctx, 13);  // entry check point + this block's cycles
    lwc1(f2, src, v3::kY);
    lwc1(f3, src, v3::kX);
    lwc1(f0, src, v3::kZ);
    mtc1(zero, f1);
    mula_s(f2, f2);
    madda_s(f3, f3);
    madd_s(f0, f0, f0);
    sqrt_s(f0, f0);
    c_le_s(f0, f1);  // |src| <= 0?
    if (!cond(ctx)) {
        // 0x004c69a4: scale = 1 / |src|
        charge(ctx, 7);
        v0 = mview::flt(1.0f);
        mtc1(v0, f1);
        div_s(f0, f1, f0);
    }
    // 0x004c69c0 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    mul_s(f1, f3, f0);
    swc1(f1, dst, v3::kX);
    lwc1(f2, src, v3::kY);
    lwc1(f1, src, v3::kZ);
    mul_s(f2, f2, f0);
    mul_s(f1, f1, f0);
    swc1(f2, dst, v3::kY);
    swc1(f1, dst, v3::kZ);
}

// 0x004C9DF0 sub_4C9DF0 -- 152 bytes; leaf frame (no stack)
// sub_4C9DF0 [camera frustum test of a sphere] (c7): 0 outside, 1 intersecting, 2 inside.
// Six planes {normal x, y, z, distance, ...} 20 bytes apart at camera + 148. Per plane d = n . centre - dist:
// d > r -> outside (0, stop); d > -r -> touching (result 1); else this plane leaves the result.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4C9DF0(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addiu, hg::backedge, hg::c_le_s, hg::charge, hg::cond, hg::enter, hg::lwc1,
          hg::madd_s, hg::madda_s, hg::mula_s, hg::neg_s, hg::sub_s;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Gpr& sph = a1;
    Gpr& planes = a3;  // camera + 148, the plane cursor
    Gpr& left = a2;  // planes left - 1
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8};
    // 0x004c9df0
    enter(ctx, 5);  // entry check point + this block's cycles
    v1 = 6;
    planes = addiu(a0, kCameraPlanes);  // $a0: the camera (then the constant 1)
    v0 = 2;
    left = addiu(v1, -1);
    if (v1 != 0) {
        // 0x004c9e04: the sphere; a0 = 1
        charge(ctx, 6);
        lwc1(f5, sph, sphere::kRadius);
        a0 = 1;
        lwc1(f8, sph, sphere::kY);
        lwc1(f7, sph, sphere::kX);
        lwc1(f6, sph, sphere::kZ);
        neg_s(f0, f5);
        for (;;) {
            // 0x004c9e1c: d = n . centre - dist; d <= r?
            charge(ctx, 11);
            lwc1(f2, planes, plane::kNy);
            lwc1(f3, planes, plane::kNx);
            lwc1(f4, planes, plane::kNz);
            lwc1(f1, planes, plane::kDist);
            mula_s(f8, f2);
            madda_s(f7, f3);
            madd_s(f2, f6, f4);
            sub_s(f1, f2, f1);
            c_le_s(f1, f5);
            v1 = a0;  // v1 = !(d <= r)
            if (cond(ctx)) {
                // 0x004c9e48: d <= r: v1 = 0
                charge(ctx, 1);
                v1 = 0;
            }
            // 0x004c9e4c
            charge(ctx, 3);
            v1 = v1 ^ 0x1;
            if (v1 == 0) {
                // 0x004c9e58: outside this plane: 0
                charge(ctx, 2);
                v0 = 0;
                break;
            }
            // 0x004c9e60: d > -r?
            charge(ctx, 3);
            c_le_s(f1, f0);
            if (!cond(ctx)) {
                // 0x004c9e6c: d > -r: touching (1)
                charge(ctx, 1);
                v0 = a0;  // touching: 1
            }
            // 0x004c9e70: next plane
            charge(ctx, 4);
            v1 = left;
            planes = addiu(planes, 20);
            left = addiu(left, -1);
            if (v1 != 0) {
                backedge(ctx);
                continue;
            }
            break;
        }
    }
    // 0x004c9e80
    charge(ctx, 2);
}

// 0x004CAE30 sub_4CAE30 -- 16 bytes; leaf frame (no stack)
// sub_4CAE30 [frame dirty bits]: frame->root->flags & 3 (the root at +160, its flags byte at +3).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4CAE30(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lbu, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004cae30
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, kFrameRoot);
    lbu(v0, v0, kFrameFlags);
    v0 = v0 & 0x3;
}

// 0x004C2860 sub_4C2860 -- 464 bytes; frame 0x10
// sub_4C2860 [general 3x4 matrix inverse]: adjugate / determinant (determinant 0 -> scale 1), then
// pos' = -(pos * inverse); flags 0. Returns dst. A zero determinant is exactly +0.0, tested as a word through
// the frame. m[i] = src word i: right m0..m2, up m4..m6, at m8..m10, pos m12..m14. Loads and stores keep the
// compiled order (the reloads of the output words read what was just stored; it matters when dst == src).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4C2860(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addiu, hg::charge, hg::div_s, hg::enter, hg::lw, hg::lwc1, hg::madd_s, hg::madda_s,
          hg::msub_s, hg::mtc1, hg::mul_s, hg::mula_s, hg::neg_s, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29};
    Gpr& dst = a0;
    Gpr& src = a1;
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11}, f12{ctx, 12};
    // 0x004c2860
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    lwc1(f7, src, mtx::kUpY);
    lwc1(f6, src, mtx::kAtZ);
    lwc1(f9, src, mtx::kUpZ);
    lwc1(f8, src, mtx::kAtY);
    lwc1(f3, src, mtx::kRightY);
    lwc1(f5, src, mtx::kRightZ);
    lwc1(f0, src, mtx::kUpX);
    mula_s(f7, f6);
    lwc1(f2, src, mtx::kRightX);
    msub_s(f1, f9, f8);
    swc1(f1, dst, mtx::kRightX);
    mula_s(f3, f6);
    msub_s(f1, f5, f8);
    mula_s(f3, f9);
    neg_s(f1, f1);
    msub_s(f5, f5, f7);
    swc1(f1, dst, mtx::kRightY);
    swc1(f5, dst, mtx::kRightZ);
    lwc1(f1, dst, mtx::kRightY);
    lwc1(f3, dst, mtx::kRightX);
    lwc1(f4, src, mtx::kAtX);
    mula_s(f1, f0);
    madda_s(f3, f2);
    madd_s(f0, f5, f4);
    swc1(f0, sp, 0xC);
    lw(v0, sp, 0xC);
    if (v0 == 0) {
        // 0x004c28f8: a zero determinant: scale 1
        charge(ctx, 2);
        v0 = mview::flt(1.0f);
        mtc1(v0, f12);
    } else {
        // 0x004c28d4: scale = 1 / determinant
        charge(ctx, 9);
        lwc1(f0, sp, 0xC);
        v0 = mview::flt(1.0f);
        mtc1(v0, f1);
        div_s(f12, f1, f0);
    }
    // 0x004c2900: the cofactors times the scale, then pos' = -(pos * inverse); flags 0
    charge(ctx, 76);
    lwc1(f0, dst, mtx::kRightX);
    v0 = dst;
    lwc1(f8, src, mtx::kUpX);
    lwc1(f7, src, mtx::kAtZ);
    lwc1(f10, src, mtx::kUpZ);
    lwc1(f9, src, mtx::kAtX);
    lwc1(f4, src, mtx::kRightX);
    mul_s(f0, f0, f12);
    swc1(f0, dst, mtx::kRightX);
    mula_s(f8, f7);
    msub_s(f0, f10, f9);
    neg_s(f0, f0);
    lwc1(f2, dst, mtx::kRightY);
    mul_s(f1, f12, f0);
    mul_s(f0, f2, f12);
    swc1(f0, dst, mtx::kRightY);
    lwc1(f11, dst, mtx::kRightZ);
    lwc1(f6, src, mtx::kRightZ);
    mula_s(f4, f7);
    lwc1(f2, src, mtx::kAtY);
    lwc1(f3, src, mtx::kUpY);
    lwc1(f0, src, mtx::kRightY);
    mul_s(f11, f11, f12);
    swc1(f11, dst, mtx::kRightZ);
    swc1(f1, dst, mtx::kUpX);
    msub_s(f1, f6, f9);
    mul_s(f1, f12, f1);
    mula_s(f4, f10);
    swc1(f1, dst, mtx::kUpY);
    msub_s(f1, f6, f8);
    neg_s(f1, f1);
    mul_s(f1, f12, f1);
    swc1(f1, dst, mtx::kUpZ);
    mula_s(f8, f2);
    msub_s(f1, f3, f9);
    mul_s(f1, f12, f1);
    mula_s(f4, f2);
    swc1(f1, dst, mtx::kAtX);
    msub_s(f1, f0, f9);
    mula_s(f4, f3);
    neg_s(f1, f1);
    msub_s(f0, f0, f8);
    mul_s(f1, f12, f1);
    mul_s(f0, f12, f0);
    swc1(f1, dst, mtx::kAtY);
    swc1(f0, dst, mtx::kAtZ);
    lwc1(f3, src, mtx::kPosY);
    lwc1(f0, dst, mtx::kUpX);
    lwc1(f4, src, mtx::kPosX);
    lwc1(f1, dst, mtx::kRightX);
    lwc1(f5, src, mtx::kPosZ);
    lwc1(f2, dst, mtx::kAtX);
    mula_s(f3, f0);
    madda_s(f4, f1);
    madd_s(f0, f5, f2);
    neg_s(f0, f0);
    swc1(f0, dst, mtx::kPosX);
    lwc1(f0, dst, mtx::kUpY);
    lwc1(f1, dst, mtx::kRightY);
    lwc1(f2, dst, mtx::kAtY);
    mula_s(f3, f0);
    madda_s(f4, f1);
    madd_s(f0, f5, f2);
    neg_s(f0, f0);
    swc1(f0, dst, mtx::kPosY);
    lwc1(f0, dst, mtx::kUpZ);
    lwc1(f1, dst, mtx::kRightZ);
    lwc1(f2, dst, mtx::kAtZ);
    mula_s(f3, f0);
    madda_s(f4, f1);
    madd_s(f0, f5, f2);
    neg_s(f0, f0);
    swc1(f0, dst, mtx::kPosZ);
    sw(zero, dst, mtx::kFlags);
    sp = addiu(sp, 0x10);
}

// 0x004C32A0 sub_4C32A0 -- 300 bytes; frame 0x10: ra sp+0x0
// sub_4C32A0 [matrix inverse]: dst = inverse(src); returns dst. An identity (the matrix module's flags
// word and the matrix flags both have 0x20000) is copied; an orthonormal one (flags & 3 == 3) is transposed with
// pos' = -(pos * transpose) and flags 3; anything else goes through sub_4C2860.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4C32A0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::jal, hg::ld,
          hg::lw, hg::lwc1, hg::madd_s, hg::madda_s, hg::mula_s, hg::neg_s, hg::sd, hg::sw, hg::swc1;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& dst = a0;
    Gpr& src = a1;  // (the copy cursor in the identity loop)
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f11{ctx, 11};
    // 0x004c32a0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = mview::hi(kRwGlobals);
    sd(ra, sp, 0x0);
    v1 = addiu(v1, mview::lo(kRwGlobals));
    lw(a2, gp, kGpMatrixOffset);
    v0 = 0x20000;  // kMatrixIdentity
    lw(a3, src, mtx::kFlags);
    v1 = addu(v1, a2);
    lw(v1, v1, kMatrixModuleFlags);
    v0 = v1 & v0;
    v0 = a3 & v0;
    if (v0 != 0) {
        // 0x004c3380: an identity: copy the 64 bytes, two words per pass
        charge(ctx, 2);
        a2 = 8;
        a3 = dst;
        for (;;) {
            // 0x004c3388
            charge(ctx, 8);
            lw(v1, src, 0);
            a2 = addiu(a2, -1);
            lw(v0, src, 4);
            sw(v1, a3, 0);
            sw(v0, a3, 4);
            src = addiu(src, 8);
            a3 = addiu(a3, 8);
            if (i64(a2) <= 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004c33a8: copied
        charge(ctx, 2);
        backedge(ctx);
    } else {
        // 0x004c32d4: not an identity: orthonormal (flags & 3 == 3)?
        charge(ctx, 4);
        v1 = a3 & 0x3;
        v0 = 3;
        if (v1 != v0) {
            // 0x004c33b0: general: sub_4C2860(dst, src)
            charge(ctx, 4);
            jal(ctx, 0x4C33B0u, gen::fn_sub_4C2860_004c2860);
            backedge(ctx);
        } else {
            // 0x004c32e4: orthonormal: transpose the rotation, pos' = -(pos * transpose), flags = 3
            charge(ctx, 37);
            lwc1(f11, src, mtx::kRightX);
            lwc1(f10, src, mtx::kUpX);
            lwc1(f9, src, mtx::kAtX);
            lwc1(f8, src, mtx::kRightY);
            lwc1(f7, src, mtx::kUpY);
            lwc1(f2, src, mtx::kPosY);
            swc1(f11, dst, mtx::kRightX);
            swc1(f10, dst, mtx::kRightY);
            swc1(f9, dst, mtx::kRightZ);
            swc1(f8, dst, mtx::kUpX);
            lwc1(f6, src, mtx::kAtY);
            swc1(f7, dst, mtx::kUpY);
            lwc1(f0, src, mtx::kRightZ);
            lwc1(f3, src, mtx::kPosX);
            mula_s(f2, f8);
            lwc1(f4, src, mtx::kPosZ);
            swc1(f6, dst, mtx::kUpZ);
            lwc1(f1, src, mtx::kUpZ);
            swc1(f0, dst, mtx::kAtX);
            madda_s(f3, f11);
            lwc1(f5, src, mtx::kAtZ);
            madd_s(f0, f4, f0);
            mula_s(f2, f7);
            swc1(f1, dst, mtx::kAtY);
            madda_s(f3, f10);
            madd_s(f1, f4, f1);
            mula_s(f2, f6);
            swc1(f5, dst, mtx::kAtZ);
            neg_s(f0, f0);
            swc1(f0, dst, mtx::kPosX);
            madda_s(f3, f9);
            madd_s(f0, f4, f5);
            neg_s(f1, f1);
            swc1(f1, dst, mtx::kPosY);
            neg_s(f0, f0);
            swc1(f0, dst, mtx::kPosZ);
            sw(v0, dst, mtx::kFlags);
        }
    }
    // 0x004c3378: return dst
    charge(ctx, 2);
    v0 = dst;
    // 0x004c33c0
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004CC0A0 sub_4CC0A0 -- 296 bytes; leaf frame (no stack)
// sub_4CC0A0 [image: alpha from max(r, g, b)]: per 32-bit pixel, or per palette entry (1 << depth entries)
// of a 4- or 8-bit image; other depths are left alone. RwImage {flags, width, height, depth, stride, pixels,
// palette}. Returns the image.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4CC0A0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lbu, hg::lw, hg::sb, hg::sllv,
          hg::slt;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    Gpr& img = a0;
    // 0x004cc0a0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, img, image::kDepth);
    v0 = 32;
    if (v1 == v0) {
        // 0x004cc134: 32-bit pixels: rows of width pixels, stride bytes apart
        charge(ctx, 5);
        lw(v0, img, image::kHeight);
        lw(t0, img, image::kPixels);
        at = slt(0, v0);
        a1 = 0;
        if (at != 0) {
            for (;;) {
                // 0x004cc148: a row
                charge(ctx, 4);
                lw(v0, img, image::kWidth);
                at = slt(0, v0);
                a3 = 0;
                if (at != 0) {
                    // 0x004cc158: its pixels
                    charge(ctx, 2);
                    v1 = t0;
                    for (;;) {
                        // 0x004cc160: a = max(r, g)
                        charge(ctx, 5);
                        lbu(a2, v1, 0);
                        lbu(v0, v1, 1);
                        at = slt(a2, v0);
                        if (at != 0) {
                            // 0x004cc174
                            charge(ctx, 1);
                            a2 = v0;
                        }
                        // 0x004cc178: a = max(a, b)
                        charge(ctx, 4);
                        lbu(v0, v1, 2);
                        at = slt(a2, v0);
                        if (at != 0) {
                            // 0x004cc188
                            charge(ctx, 2);
                            a2 = v0;
                        }
                        // 0x004cc190: pixel.a = a; next pixel
                        charge(ctx, 6);
                        sb(a2, v1, 3);
                        lw(v0, img, image::kWidth);
                        a3 = addiu(a3, 1);
                        v0 = slt(a3, v0);
                        v1 = addiu(v1, 4);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x004cc1a8: next row
                charge(ctx, 6);
                lw(v0, img, image::kHeight);
                lw(v1, img, image::kStride);
                a1 = addiu(a1, 1);
                v0 = slt(a1, v0);
                t0 = addu(t0, v1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    } else {
        // 0x004cc0b0: 8 bits?
        charge(ctx, 3);
        v0 = 8;
        if (v1 != v0) {
            // 0x004cc0bc: 4 bits?
            charge(ctx, 3);
            v0 = 4;
            if (v1 != v0) {
                // 0x004cc0c8: another depth: nothing to do
                charge(ctx, 2);
                // 0x004cc1c0 (the shared epilogue, written out on this path)
                charge(ctx, 2);
                v0 = img;
                return;
            }
        }
        // 0x004cc0d0: 4 or 8 bits: the 1 << depth palette entries
        charge(ctx, 6);
        lw(a1, img, image::kPalette);
        v0 = 1;
        v1 = sllv(v0, v1);
        at = slt(0, v1);
        a3 = 0;
        if (at != 0) {
            for (;;) {
                // 0x004cc0e8: a palette entry: a = max(r, g)
                charge(ctx, 5);
                lbu(a2, a1, 0);
                lbu(v0, a1, 1);
                at = slt(a2, v0);
                if (at != 0) {
                    // 0x004cc0fc
                    charge(ctx, 1);
                    a2 = v0;
                }
                // 0x004cc100: a = max(a, b)
                charge(ctx, 4);
                lbu(v0, a1, 2);
                at = slt(a2, v0);
                if (at != 0) {
                    // 0x004cc110
                    charge(ctx, 2);
                    a2 = v0;
                }
                // 0x004cc118: entry.a = a; next entry
                charge(ctx, 5);
                a3 = addiu(a3, 1);
                sb(a2, a1, 3);
                v0 = slt(a3, v1);
                a1 = addiu(a1, 4);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004cc12c
            charge(ctx, 2);
        }
    }
    // 0x004cc1c0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = img;
}

// =================================================================================================================
// render state / raster / texture cache
// =================================================================================================================

// 0x004D6B60 sub_4D6B60 -- 48 bytes; leaf frame (no stack)
// sub_4D6B60 [index of the most significant bit, -1 for 0]: v0 = -1, then one per shift until the value
// is 0.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4D6B60(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::si, hg::srl;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    Gpr& value = a0;
    // 0x004d6b60
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = si(-1);
    if (value != 0) {
        for (;;) {
            // 0x004d6b68: value >>= 1; v0++ until 0
            charge(ctx, 7);
            value = srl(value, 1);
            v0 = addiu(v0, 1);
            if (value == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004d6b84
        charge(ctx, 1);
    }
    // 0x004d6b88 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004D81B0 sub_4D81B0 -- 236 bytes; leaf frame (no stack)
// sub_4D81B0 [sky render-state get] (c6): *out = state 5 / 4 / 3 / 2 / 1 from the driver's GS register
// shadows; returns 1 for a known state, 0 otherwise. 4 is 0 while the override word is set, else the float;
// 2 is byte 0 | byte 4 << 24 of the 64-bit shadow; 1 only when the current raster's depth is not 32 and the
// enable word is set.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4D81B0(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::charge, hg::dsll, hg::dsll32, hg::dsra, hg::dsra32, hg::enter, hg::ld, hg::lw,
          hg::lwc1, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    Gpr& state = a0;  // (later a temporary)
    Gpr& out = a1;
    Fpr f0{ctx, 0};
    // 0x004d81b0: the compiled switch tests 5, 4, 3, 2, 1 in turn
    enter(ctx, 3);  // entry check point + this block's cycles
    bool known = false;  // a value was stored: return 1
    v0 = 5;
    if (state == v0) {
        // 0x004d8278: state 5
        charge(ctx, 2);
        lw(v0, gp, kGpRsState5);
        sw(v0, out, 0);
        known = true;
    } else {
        // 0x004d81bc
        charge(ctx, 3);
        v0 = 4;
        if (state == v0) {
            // 0x004d8258: state 4: 0 while overridden, else the float
            charge(ctx, 3);
            lw(v0, gp, kGpRsState4Override);
            if (v0 == 0) {
                // 0x004d826c
                charge(ctx, 3);
                lwc1(f0, gp, kGpRsState4);
                swc1(f0, out, 0);
            } else {
                // 0x004d8264
                charge(ctx, 2);
                sw(zero, out, 0);
            }
            known = true;
        } else {
            // 0x004d81c8
            charge(ctx, 3);
            v0 = 3;
            if (state == v0) {
                // 0x004d824c: state 3
                charge(ctx, 3);
                lw(v0, gp, kGpRsState3);
                sw(v0, out, 0);
                known = true;
            } else {
                // 0x004d81d4
                charge(ctx, 3);
                v0 = 2;
                if (state == v0) {
                    // 0x004d8220: state 2 = (s32)(byte 0 | (shadow >> 8) & 0xFF000000) of the 64-bit shadow
                    charge(ctx, 11);
                    ld(v1, gp, kGpRsState2Shadow);
                    v0 = 0xFF00;
                    v0 = dsll(v0, 16);
                    a0 = v1 & 0xFF;
                    v1 = dsra(v1, 8);
                    v0 = v1 & v0;
                    v0 = a0 | v0;
                    v0 = dsll32(v0, 0);
                    v0 = dsra32(v0, 0);
                    sw(v0, out, 0);
                    known = true;
                } else {
                    // 0x004d81e0
                    charge(ctx, 3);
                    v0 = 1;
                    if (state == v0) {
                        // 0x004d81f4: state 1: known only for a raster depth other than 32 and while enabled
                        charge(ctx, 5);
                        lw(v1, gp, kGpCurrentRaster);
                        v0 = 32;
                        lw(v1, v1, kRasterDepth);
                        if (v1 != v0) {
                            // 0x004d8208
                            charge(ctx, 3);
                            lw(v0, gp, kGpRsState1Enable);
                            if (v0 != 0) {
                                // 0x004d8214
                                charge(ctx, 3);
                                lw(v0, gp, kGpRsState1);
                                sw(v0, out, 0);
                                known = true;
                            }
                        }
                        if (!known) {
                            // 0x004d8290: not available: 0
                            charge(ctx, 1);
                            v0 = 0;
                        }
                    } else {
                        // 0x004d81ec: an unknown state: 0
                        charge(ctx, 2);
                        v0 = 0;
                        // 0x004d8288
                        charge(ctx, 2);
                    }
                }
            }
        }
    }
    if (known) {
        // 0x004d8280
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x004d8294 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004DB200 sub_4DB200 -- 324 bytes; leaf frame (no stack)
// sub_4DB200 [minimum transfer size of a raster format]: *outWidth / *outHeight. The minimum width of
// an upload by raster format (4- / 8-bit indexed and the 16/32-bit layouts), height 1; the swizzled variants
// (flag 2 with format 19, flag 4 with format 20) need 16x4 / 32x4. The compiled test chain compares the whole
// register in this order (its block costs follow the order).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4DB200(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    Gpr& format = a0;
    Gpr& flags = a1;
    Gpr& out_w = a2;
    Gpr& out_h = a3;
    Gpr& width = t2;
    Gpr& height = t1;
    // 0x004db200
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 44;
    width = 0;
    height = 1;
    if (format == v1) {
        // 0x004db2f0
        charge(ctx, 1);
        width = 8;
    } else {
        // 0x004db210
        charge(ctx, 3);
        v1 = 36;
        if (format == v1) {
            // 0x004db2e8
            charge(ctx, 2);
            width = 8;
        } else {
            // 0x004db21c
            charge(ctx, 3);
            v1 = 20;
            if (format == v1) {
                // 0x004db2e0
                charge(ctx, 2);
                width = 8;
            } else {
                // 0x004db228
                charge(ctx, 3);
                v1 = 27;
                if (format == v1) {
                    // 0x004db2d8
                    charge(ctx, 2);
                    width = 8;
                } else {
                    // 0x004db234
                    charge(ctx, 3);
                    v1 = 19;
                    if (format == v1) {
                        // 0x004db2d0
                        charge(ctx, 2);
                        width = 8;
                    } else {
                        // 0x004db240
                        charge(ctx, 3);
                        v1 = 58;
                        if (format == v1) {
                            // 0x004db2c8
                            charge(ctx, 2);
                            width = 4;
                        } else {
                            // 0x004db24c
                            charge(ctx, 3);
                            v1 = 50;
                            if (format == v1) {
                                // 0x004db2c0
                                charge(ctx, 2);
                                width = 4;
                            } else {
                                // 0x004db258
                                charge(ctx, 3);
                                v1 = 10;
                                if (format == v1) {
                                    // 0x004db2b8
                                    charge(ctx, 2);
                                    width = 4;
                                } else {
                                    // 0x004db264
                                    charge(ctx, 3);
                                    t0 = 2;
                                    if (format == t0) {
                                        // 0x004db2b0
                                        charge(ctx, 2);
                                        width = 4;
                                    } else {
                                        // 0x004db270
                                        charge(ctx, 3);
                                        v1 = 49;
                                        if (format == v1) {
                                            // 0x004db2a8
                                            charge(ctx, 2);
                                            width = 8;
                                        } else {
                                            // 0x004db27c
                                            charge(ctx, 2);
                                            if (format == height) {
                                                // 0x004db2a0
                                                charge(ctx, 2);
                                                width = 8;
                                            } else {
                                                // 0x004db284
                                                charge(ctx, 3);
                                                v1 = 48;
                                                if (format == v1) {
                                                    // 0x004db298
                                                    charge(ctx, 2);
                                                    width = t0;
                                                } else {
                                                    // 0x004db290
                                                    charge(ctx, 2);
                                                    if (format == 0) width = t0;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    // 0x004db2f4: swizzled formats: flag 2 with format 19 -> 16 x 4
    charge(ctx, 4);
    flags = flags & 0xFF;
    v1 = flags & 0x2;
    if (v1 != 0) {
        // 0x004db304
        charge(ctx, 3);
        v1 = 19;
        if (format == v1) {
            // 0x004db310
            charge(ctx, 2);
            width = 16;
            height = 4;
        }
    }
    // 0x004db318: flag 4 with format 20 -> 32 x 4
    charge(ctx, 3);
    v1 = flags & 0x4;
    if (v1 != 0) {
        // 0x004db324
        charge(ctx, 3);
        v1 = 20;
        if (format == v1) {
            // 0x004db330
            charge(ctx, 2);
            width = 32;
            height = 4;
        }
    }
    // 0x004db338 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    sw(width, out_w, 0);
    sw(height, out_h, 0);
}

void sub_4F0C60(EEContext& ctx) { guest::enter(ctx, 2); }

// 0x004F1540 sub_4F1540 -- 572 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4F1540 [texture cache: release a raster] (c5). The raster's cache slot pointer is at its sky
// extension + 88. Cache on: the slot's raster word is cleared, the two remembered indices forget it, and
// when it sits at one end of the ring that end moves over freed slots (an emptied ring becomes -1/-1).
// Cache off: the release callback (if any) for a raster that has a slot pointer. Either way the pointer is
// cleared and the "last accessed" raster forgets this one. The slot index is (slot - slots) / 12 by the
// compiler's multiply (0x2AAAAAAB, HI >> 1, + the sign bit).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4F1540(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jalr, hg::ld, hg::lq, hg::lw,
          hg::mfhi, hg::mult, hg::sd, hg::si, hg::sll, hg::sq, hg::sra, hg::srl, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& raster = s1;  // $a0
    Gpr& ext = s0;  // raster + the sky extension offset
    // 0x004f1540
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = mview::hi(kTexCache);
    sd(ra, sp, 0x20);
    sq(raster, sp, 0x10);
    sq(ext, sp, 0x0);
    raster = a0;
    lw(a0, gp, kGpRasterExt);
    lw(v1, v1, mview::lo(kTexCache));
    ext = addu(raster, a0);
    bool released = false;  // the cache-on path ran
    if (v1 != 0) {
        // 0x004f15b0
        charge(ctx, 3);
        lw(a2, ext, kExtCacheSlot);
        if (a2 == 0) {
            // no slot: nothing to release in the cache
            backedge(ctx);
        } else {
            // 0x004f15bc: clear the slot's raster word; its index = (slot - slots) / 12
            charge(ctx, 16);
            v1 = mview::hi(kTexCache);
            a0 = 0x2AAA0000;  // / 12: the multiplier 0x2AAAAAAB
            lw(a1, v1, mview::lo(kTexCacheSlots));
            v1 = a0 | 0xAAAB;
            a0 = subu(a2, a1);
            mult(zero, v1, a0);
            a1 = srl(a0, 31);
            mfhi(a0);
            sw(zero, a2, 0);
            v1 = mview::hi(kTexCache);
            lw(v1, v1, mview::lo(kTexCacheHit0));
            a0 = sra(a0, 1);
            a1 = addu(a0, a1);
            if (a1 == v1) {
                // 0x004f16c4: the first remembered index forgets it
                charge(ctx, 4);
                a0 = si(-1);
                v1 = mview::hi(kTexCache);
                sw(a0, v1, mview::lo(kTexCacheHit0));
                backedge(ctx);
            }
            // 0x004f15fc: the second remembered index
            charge(ctx, 4);
            v1 = mview::hi(kTexCache);
            lw(v1, v1, mview::lo(kTexCacheHit1));
            if (a1 == v1) {
                // 0x004f16d4: it forgets it
                charge(ctx, 4);
                a0 = si(-1);
                v1 = mview::hi(kTexCache);
                sw(a0, v1, mview::lo(kTexCacheHit1));
                backedge(ctx);
            }
            // 0x004f160c: the slot at the back end?
            charge(ctx, 4);
            v1 = mview::hi(kTexCache);
            lw(v1, v1, mview::lo(kTexCacheBack));
            if (a1 != v1) {
                // 0x004f16f0: at the front end?
                charge(ctx, 4);
                a0 = mview::hi(kTexCache);
                lw(a0, a0, mview::lo(kTexCacheFront));
                if (a1 != a0) {
                    backedge(ctx);
                } else {
                    // 0x004f1700: the front end moves up over freed slots (wrapping at count to 0)
                    charge(ctx, 9);
                    v1 = mview::hi(kTexCache);
                    a1 = mview::hi(kTexCache);
                    lw(t1, v1, mview::lo(kTexCacheSlots));
                    a0 = mview::hi(kTexCache);
                    a2 = mview::hi(kTexCache);
                    v1 = mview::hi(kTexCache);
                    lw(a3, v1, mview::lo(kTexCacheCount));
                    v1 = mview::hi(kTexCache);
                    lw(v1, v1, mview::lo(kTexCacheBack));
                    for (;;) {
                        // 0x004f1724: front == back: stop
                        charge(ctx, 3);
                        lw(t2, a2, mview::lo(kTexCacheFront));
                        if (v1 == t2) {
                            backedge(ctx);
                        } else {
                            // 0x004f1730: slots[front].raster == 0?
                            charge(ctx, 7);
                            t0 = sll(t2, 1);
                            t0 = addu(t0, t2);
                            t0 = sll(t0, 2);
                            t0 = addu(t1, t0);
                            lw(t0, t0, 0);
                            if (t0 == 0) {
                                // 0x004f174c: front++ (wrapping)
                                charge(ctx, 3);
                                t0 = addiu(t2, 1);
                                sw(t0, a1, mview::lo(kTexCacheFront));
                                if (t0 != a3) {
                                    backedge(ctx);
                                } else {
                                    // 0x004f1758: front = 0
                                    charge(ctx, 2);
                                    sw(zero, a0, mview::lo(kTexCacheFront));
                                    backedge(ctx);
                                }
                                continue;
                            }
                            backedge(ctx);
                        }
                        break;
                    }
                }
            } else {
                // 0x004f161c: the back end moves down over freed slots (wrapping at 0 to count - 1)
                charge(ctx, 10);
                v1 = mview::hi(kTexCache);
                a0 = mview::hi(kTexCache);
                lw(t0, v1, mview::lo(kTexCacheCount));
                a2 = mview::hi(kTexCache);
                lw(t2, a0, mview::lo(kTexCacheSlots));
                a1 = mview::hi(kTexCache);
                a3 = mview::hi(kTexCache);
                v1 = mview::hi(kTexCache);
                lw(t3, v1, mview::lo(kTexCacheFront));
                a0 = mview::hi(kTexCache);
                for (;;) {
                    // 0x004f1644: back == front: stop
                    charge(ctx, 3);
                    lw(v1, a3, mview::lo(kTexCacheBack));
                    if (v1 != t3) {
                        // 0x004f1650: slots[back].raster == 0?
                        charge(ctx, 7);
                        t1 = sll(v1, 1);
                        t1 = addu(t1, v1);
                        t1 = sll(t1, 2);
                        t1 = addu(t2, t1);
                        lw(t1, t1, 0);
                        if (t1 == 0) {
                            // 0x004f166c: back == 0: wrap to count
                            charge(ctx, 2);
                            if (v1 == 0) {
                                // 0x004f16e4: back = count
                                charge(ctx, 2);
                                sw(t0, a0, mview::lo(kTexCacheBack));
                                backedge(ctx);
                            } else {
                                // 0x004f1674
                                charge(ctx, 1);
                            }
                            // 0x004f1678: back--
                            charge(ctx, 4);
                            lw(v1, a2, mview::lo(kTexCacheBack));
                            v1 = addiu(v1, -1);
                            sw(v1, a1, mview::lo(kTexCacheBack));
                            backedge(ctx);
                            continue;
                        }
                    }
                    break;
                }
            }
            // 0x004f1688: the end slot is free too: the ring is empty (-1 / -1)
            charge(ctx, 9);
            a0 = sll(v1, 1);
            a0 = addu(a0, v1);
            v1 = mview::hi(kTexCache);
            a0 = sll(a0, 2);
            lw(v1, v1, mview::lo(kTexCacheSlots));
            v1 = addu(v1, a0);
            lw(v1, v1, 0);
            if (v1 != 0) {
                backedge(ctx);
            } else {
                // 0x004f16ac: back = front = -1
                charge(ctx, 6);
                a0 = si(-1);
                v1 = mview::hi(kTexCache);
                sw(a0, v1, mview::lo(kTexCacheBack));
                v1 = mview::hi(kTexCache);
                sw(a0, v1, mview::lo(kTexCacheFront));
                backedge(ctx);
            }
            released = true;
        }
    }
    if (!released) {
        // 0x004f1568: cache off: the release callback for a raster that has a slot
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x004f1570
            charge(ctx, 4);
            v1 = mview::hi(kTexCache);
            lw(a1, v1, mview::lo(kTexCacheRelease));
            if (a1 != 0) {
                // 0x004f1580
                charge(ctx, 3);
                lw(v1, ext, kExtCacheSlot);
                if (v1 != 0) {
                    // 0x004f158c
                    charge(ctx, 2);
                    a0 = raster;
                    jalr(ctx, 0x4F158Cu, a1.u());
                }
            }
        }
    }
    // 0x004f1594: the slot pointer = 0; the last accessed raster forgets this one
    charge(ctx, 5);
    sw(zero, ext, kExtCacheSlot);
    v1 = mview::hi(kTexCache);
    lw(v1, v1, mview::lo(kTexCacheLast));
    if (raster == v1) {
        // 0x004f1760: last = 0
        charge(ctx, 3);
        v1 = mview::hi(kTexCache);
        sw(zero, v1, mview::lo(kTexCacheLast));
        backedge(ctx);
    }
    // 0x004f15a8: epilogue
    charge(ctx, 2);
    ld(ra, sp, 0x20);
    // 0x004f176c
    charge(ctx, 4);
    lq(raster, sp, 0x10);
    lq(ext, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// =================================================================================================================
// Im3D / RxHeap / libgraph / libdma
// =================================================================================================================

// 0x004F1F80 sub_4F1F80 -- 76 bytes; frame 0x10: ra sp+0x0
// sub_4F1F80 [Im3D end]: clears the 60-byte Im3D pool when it is open (memset); 1 if it was, else 0.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4F1F80_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f1f80
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = mview::hi(kRwGlobals);
    sd(ra, sp, 0x0);
    v0 = addiu(v0, mview::lo(kRwGlobals));
    lw(v1, gp, kGpIm3DOffset);
    v1 = addu(v0, v1);
    lw(v0, v1, kIm3DOpen);
    if (v0 == 0) {
        // 0x004f1fbc: not open: 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004f1fa4: memset(pool, 0, 60); 1
        charge(ctx, 6);
        a0 = addiu(v1, kIm3DPool);
        a1 = 0;
        a2 = kIm3DPoolSize;
        jal(ctx, 0x4F1FACu, gen::fn_memset_00521408);
        v0 = 1;
    }
    // 0x004f1fc0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

u32 sub_4F2710(EEContext& ctx) {
    guest::enter(ctx, 6);
    const u64 v1 = lws(ctx, gpw(ctx, kGpIm3DOffset));
    const u64 v0 = core::add32i(core::add32(kRwGlobals, v1), 64);
    setr(ctx, GPR_V1, v1);
    setr(ctx, GPR_V0, v0);
    return lo(v0);
}

u32 sub_4F2E60(EEContext& ctx) {
    guest::enter(ctx, 2);
    const u64 v0 = lws(ctx, gpw(ctx, kGpRxHeap));
    setr(ctx, GPR_V0, v0);
    return lo(v0);
}

u32 sceGsGetGParam(EEContext& ctx) {
    guest::enter(ctx, 3);
    setr(ctx, GPR_V0, kGsGParam);
    return kGsGParam;
}

u32 sceDmaGetChan(EEContext& ctx, u64 chan) {
    guest::enter(ctx, 3);
    u64 v0 = 0;
    if (chan < 10) {  // sltiu on the whole register
        guest::charge(ctx, 5);
        const u64 v1 = core::add32(core::sll(chan, 2), kDmaChanTable);
        v0 = lws(ctx, lo(v1));
        setr(ctx, GPR_V1, v1);
    } else {
        guest::charge(ctx, 2);
    }
    setr(ctx, GPR_V0, v0);
    return lo(v0);
}

// =================================================================================================================
// rpworld / skin / PS2All / MatFX
// =================================================================================================================

// 0x0048A3E0 sub_48A3E0 -- 8 bytes; leaf frame (no stack)
// sub_48A3E0 [skin: skin-to-bone matrices] = skin + 12. One block of 2.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_48A3E0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0048a3e0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, kSkinMatrices);
}

u64 sub_490D80(EEContext& ctx, u64 clump) {
    guest::enter(ctx, 2);
    setr(ctx, GPR_V0, clump);
    return clump;
}

// 0x00491100 sub_491100 -- 432 bytes; leaf frame (no stack)
// sub_491100 [atomic: resync the interpolated bounding sphere] (c7): lerp between the two morph
// targets' spheres. atomic +24 geometry (+24 morph-target count, +92 targets: 28-byte {.., sphere x y z r
// at +4..+16}), +28..+40 the interpolated sphere, +76 flags (bit 1 = sphere stale), +80/+82 current/next
// target, +88 * +92 the blend factor.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_491100(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::add_s, hg::adda_s, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lbu,
          hg::lh, hg::lw, hg::lwc1, hg::madd_s, hg::mtc1, hg::mul_s, hg::sb, hg::si, hg::sll, hg::slt, hg::sub_s,
          hg::subu, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    Gpr& atom = a0;
    Gpr& cur = t0;  // the current target index
    Gpr& next = t1;  // the next one
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4};
    // 0x00491100
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(a2, atom, atomic::kGeometry);
    if (a2 != 0) {
        // 0x0049110c: the targets; v1 = &atomic->flags
        charge(ctx, 4);
        lh(next, atom, atomic::kNextTarget);
        lh(cur, atom, atomic::kTarget);
        v1 = addiu(atom, atomic::kFlags);  // &atomic->flags (+12 / +16: the blend factor)
        bool done = false;
        if (cur != next) {
            // 0x0049111c: both targets exist?
            charge(ctx, 4);
            lw(a1, a2, geom::kTargetCount);
            at = slt(cur, a1);
            if (at != 0) {
                // 0x0049112c
                charge(ctx, 3);
                at = slt(next, a1);
                if (at != 0) {
                    // 0x00491138: sphere = A + (B - A) * t, t = blendA * blendB; A = targets[cur] ($a2),
                    // B = targets[next] ($a1), 28-byte targets
                    charge(ctx, 53);
                    lw(a3, a2, geom::kTargets);
                    a1 = sll(cur, 3);
                    lwc1(f4, v1, atomic::kBlendA - atomic::kFlags);
                    lwc1(f3, v1, atomic::kBlendB - atomic::kFlags);
                    mtc1(zero, f0);
                    a2 = subu(a1, cur);
                    a1 = sll(next, 3);
                    a2 = sll(a2, 2);
                    a1 = subu(a1, next);
                    a2 = addu(a3, a2);
                    a1 = sll(a1, 2);
                    a1 = addu(a3, a1);
                    lwc1(f2, a2, morph::kSphereR);
                    lwc1(f1, a1, morph::kSphereR);
                    mul_s(f3, f4, f3);
                    adda_s(f0, f2);
                    sub_s(f0, f1, f2);
                    madd_s(f0, f3, f0);
                    swc1(f0, atom, atomic::kSphereR);
                    lwc1(f1, a1, morph::kSphereX);
                    lwc1(f0, a2, morph::kSphereX);
                    sub_s(f0, f1, f0);
                    swc1(f0, atom, atomic::kSphereX);
                    lwc1(f1, a1, morph::kSphereY);
                    lwc1(f0, a2, morph::kSphereY);
                    sub_s(f0, f1, f0);
                    swc1(f0, atom, atomic::kSphereY);
                    lwc1(f1, a1, morph::kSphereZ);
                    lwc1(f0, a2, morph::kSphereZ);
                    sub_s(f0, f1, f0);
                    swc1(f0, atom, atomic::kSphereZ);
                    lwc1(f0, atom, atomic::kSphereX);
                    mul_s(f0, f0, f3);
                    swc1(f0, atom, atomic::kSphereX);
                    lwc1(f0, atom, atomic::kSphereY);
                    mul_s(f0, f0, f3);
                    swc1(f0, atom, atomic::kSphereY);
                    lwc1(f0, atom, atomic::kSphereZ);
                    mul_s(f0, f0, f3);
                    swc1(f0, atom, atomic::kSphereZ);
                    lwc1(f1, a2, morph::kSphereX);
                    lwc1(f0, atom, atomic::kSphereX);
                    add_s(f0, f0, f1);
                    swc1(f0, atom, atomic::kSphereX);
                    lwc1(f1, a2, morph::kSphereY);
                    lwc1(f0, atom, atomic::kSphereY);
                    add_s(f0, f0, f1);
                    swc1(f0, atom, atomic::kSphereY);
                    lwc1(f1, a2, morph::kSphereZ);
                    lwc1(f0, atom, atomic::kSphereZ);
                    add_s(f0, f0, f1);
                    swc1(f0, atom, atomic::kSphereZ);
                    done = true;
                }
            }
        }
        if (!done) {
            // 0x0049120c: no blend: the current target's sphere when both exist
            charge(ctx, 4);
            lw(a1, a2, geom::kTargetCount);
            at = slt(cur, a1);
            if (at != 0) {
                // 0x0049121c
                charge(ctx, 3);
                at = slt(next, a1);
                if (at != 0) {
                    // 0x00491228
                    charge(ctx, 13);
                    lw(a2, a2, geom::kTargets);
                    a1 = sll(cur, 3);
                    a1 = subu(a1, cur);
                    a1 = sll(a1, 2);
                    a1 = addu(a1, a2);
                    lwc1(f3, a1, morph::kSphereX);
                    lwc1(f2, a1, morph::kSphereY);
                    lwc1(f1, a1, morph::kSphereZ);
                    lwc1(f0, a1, morph::kSphereR);
                    swc1(f3, atom, atomic::kSphereX);
                    swc1(f2, atom, atomic::kSphereY);
                    swc1(f1, atom, atomic::kSphereZ);
                    swc1(f0, atom, atomic::kSphereR);
                    done = true;
                }
            }
            if (!done) {
                // 0x00491280: else target 0's
                charge(ctx, 10);
                lw(a1, a2, geom::kTargets);
                lwc1(f3, a1, morph::kSphereX);
                lwc1(f2, a1, morph::kSphereY);
                lwc1(f1, a1, morph::kSphereZ);
                lwc1(f0, a1, morph::kSphereR);
                swc1(f3, atom, atomic::kSphereX);
                swc1(f2, atom, atomic::kSphereY);
                swc1(f1, atom, atomic::kSphereZ);
                swc1(f0, atom, atomic::kSphereR);
                backedge(ctx);
            }
        }
        // 0x0049125c: flags &= ~2 (current); object flags |= 1
        charge(ctx, 9);
        lw(a2, v1, 0);
        a1 = si(-3);  // ~2: the sphere is current
        a1 = a2 & a1;
        sw(a1, v1, 0);
        lbu(v1, atom, atomic::kObjFlags);
        v1 = v1 | 0x1;
        sb(v1, atom, atomic::kObjFlags);
    }
    // 0x004912a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00495320 sub_495320 -- 20 bytes; leaf frame (no stack)
// sub_495320 [material list: material i] = list->materials[i]. One block of 5.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_495320(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::enter, hg::lw, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Gpr& index = a1;
    // 0x00495320
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, kMatListMaterials);
    v1 = sll(index, 2);
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
}

// 0x004992F0 sub_4992F0 -- 40 bytes; leaf frame (no stack)
// sub_4992F0 [find-sector callback]: query {sector, found}: when the sector matches, found = 1 and 0
// (stop the walk); else the sector (go on).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4992F0(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lw, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Gpr& sector = a0;
    Gpr& qry = a1;
    // 0x004992f0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, qry, query::kSector);
    if (v0 == sector) {
        // 0x00499304: found: query->found = 1; 0 stops the walk
        charge(ctx, 3);
        v1 = 1;
        v0 = 0;
        sw(v1, qry, query::kFound);
    } else {
        // 0x004992fc: go on: the sector
        charge(ctx, 2);
        v0 = sector;
    }
    // 0x00499310 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0049C330 sub_49C330 -- 148 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_49C330 [for all sectors in the camera frustum] (c7): callback(sector, data) for each sector of
// the camera's frustum sector list {sectors, ?, count} until it returns 0; returns the camera. The callback
// runs inside the original 96-byte frame with the original s-registers.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_49C330(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jalr, hg::ld, hg::lq, hg::lw,
          hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Gpr& camera = s2;  // $a0
    Gpr& callback = s1;  // $a1
    Gpr& data = s0;  // $a2
    Gpr& left = s3;  // sectors left
    Gpr& cursor = s4;  // the sector pointer cursor
    // 0x0049c330
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(cursor, sp, 0x40);
    sq(left, sp, 0x30);
    sq(camera, sp, 0x20);
    sq(callback, sp, 0x10);
    camera = a0;
    sq(data, sp, 0x0);
    callback = a1;
    lw(v0, gp, kGpCameraSectors);
    v0 = addu(camera, v0);
    lw(left, v0, seclist::kCount);
    lw(cursor, v0, seclist::kSectors);
    data = a2;
    if (left != 0) {
        for (;;) {
            // 0x0049c374: v0 = callback(*cursor, data)
            charge(ctx, 5);
            lw(a0, cursor, 0);
            a1 = data;
            jalr(ctx, 0x49C378u, callback.u());
            if (v0 == 0) {
                // 0x0049c388: the callback said stop: return the camera
                charge(ctx, 2);
                v0 = camera;
                // 0x0049c3a4 (the shared epilogue, written out on this path)
                charge(ctx, 8);
                ld(ra, sp, 0x50);
                lq(cursor, sp, 0x40);
                lq(left, sp, 0x30);
                lq(camera, sp, 0x20);
                lq(callback, sp, 0x10);
                lq(data, sp, 0x0);
                sp = addiu(sp, 0x60);
                return;
            }
            // 0x0049c390: next sector
            charge(ctx, 3);
            left = addiu(left, -1);
            cursor = addiu(cursor, 4);
            if (left == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0049c39c: every sector visited
        charge(ctx, 2);
        backedge(ctx);
    }
    // 0x0049c36c: return the camera
    charge(ctx, 2);
    v0 = camera;
    // 0x0049c3a4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(cursor, sp, 0x40);
    lq(left, sp, 0x30);
    lq(camera, sp, 0x20);
    lq(callback, sp, 0x10);
    lq(data, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0049FEC0 sub_49FEC0 -- 52 bytes; leaf frame (no stack)
// sub_49FEC0 [PS2All node: group meshes]: node->private->groupMeshes = value; returns node, or 0 when
// node or its private data is null.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_49FEC0(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lw, hg::sw;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    Gpr& node = a0;
    Gpr& value = a1;
    // 0x0049fec0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (node == 0) {
        // 0x0049fee0: no node: 0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0049fec8: its private data
        charge(ctx, 3);
        lw(v0, node, kNodePrivate);
        if (v0 == 0) {
            // 0x0049fee8: none: 0
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0049fed4: private->groupMeshes = value; return node
            charge(ctx, 3);
            sw(value, v0, kPrivGroupMeshes);
            v0 = node;
        }
    }
    // 0x0049feec (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004A0C20 sub_4A0C20 -- 188 bytes; leaf frame (no stack)
// sub_4A0C20 [PS2All mesh instance test]: flag 8 (re-instance) when the index count or the geometry
// flags differ from the resEntry's; returns 1. The record: +12 the object (its flags word: bit 1 =
// tri-strip -> 3 (n - 2) indices), +44 the mesh (+4 vertex count), +48 the resEntry pointer (+24 the
// instance header: +12 count; +44 the flags), +52 the instance flags, +56 the object flags copy.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4A0C20(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lw, hg::sll,
          hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Gpr& inst = a0;
    // 0x004a0c20
    enter(ctx, 9);  // entry check point + this block's cycles
    lw(v1, inst, inst::kObject);
    lw(a1, inst, inst::kResEntry);
    lw(v0, inst, inst::kMesh);
    lw(v1, v1, 0);
    lw(a1, a1, 0);
    lw(v0, v0, kMeshVertexCount);
    v1 = v1 & 0x2;
    a1 = addiu(a1, kResInstHeader);
    if (v1 != 0) {
        // 0x004a0c94: a tri-strip: 3 * (n - 2) indices
        charge(ctx, 6);
        v0 = dsll32(v0, 0);
        v0 = dsra32(v0, 0);
        v1 = addiu(v0, -2);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        backedge(ctx);
    }
    // 0x004a0c44: the index count differs from the instance header's: re-instance
    charge(ctx, 5);
    v1 = dsll32(v0, 0);
    lw(v0, a1, kInstHeaderCount);
    v1 = dsra32(v1, 0);
    if (v1 != v0) {
        // 0x004a0cac: flags |= 8
        charge(ctx, 4);
        lw(v0, inst, inst::kFlags);
        v0 = v0 | 0x8;
        sw(v0, inst, inst::kFlags);
        backedge(ctx);
    }
    // 0x004a0c58: already flagged: 1
    charge(ctx, 4);
    lw(v0, inst, inst::kFlags);
    v0 = v0 & 0x8;
    if (v0 != 0) {
        // 0x004a0cbc: 1
        charge(ctx, 2);
        v0 = 1;
    } else {
        // 0x004a0c68: copy the object flags and compare them with the resEntry's
        charge(ctx, 9);
        lw(v1, inst, inst::kResEntry);
        lw(v0, inst, inst::kObject);
        lw(v1, v1, 0);
        lw(v0, v0, 0);
        sw(v0, inst, inst::kObjFlags);
        lw(v0, v1, kResGeomFlags);
        lw(v1, inst, inst::kObjFlags);
        if (v1 != v0) {
            // 0x004a0cc4: flags |= 8
            charge(ctx, 4);
            lw(v0, inst, inst::kFlags);
            v0 = v0 | 0x8;
            sw(v0, inst, inst::kFlags);
            backedge(ctx);
        }
        // 0x004a0c8c: 1
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x004a0cd4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004A24A0 sub_4A24A0 -- 184 bytes; leaf frame (no stack)
// sub_4A24A0 [Im3D PS2All mesh-cache callback]: points the record (dst) at the Im3D mesh header
// (0x77DEC0) and the gp mesh-cache record, and fills the header from the Im3D source: vertex count (+44), no
// offset, the prim-type flags from the table at the Im3D prim offset + 39 indexed by +36 (bit 8 = not
// indexed when +40 is 0), the mesh list 0x77DEE0 with indices +40 / count +44.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4A24A0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lbu, hg::lw, hg::si, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, gp{ctx, 28};
    Gpr& src = a0;
    // 0x004a24a0
    enter(ctx, 28);  // entry check point + this block's cycles
    v1 = addiu(gp, kGpIm3DMeshCache);
    t0 = mview::hi(kRwGlobals);
    sw(v1, a1, mcache::kRecord);  // $a1: the mesh-cache record
    t0 = addiu(t0, mview::lo(kRwGlobals));
    mview::la(v1, kIm3DMeshHeader);
    sw(v1, a1, mcache::kHeader);
    lw(a3, src, im3dsrc::kVertexCount);
    v1 = si(-256);  // keep all but the prim byte
    lw(a2, a1, mcache::kHeader);
    sw(a3, a2, mhdr::kVertexCount);
    lw(a2, a1, mcache::kHeader);
    sw(zero, a2, mhdr::kOffset);
    lw(a2, a1, mcache::kHeader);
    sw(zero, a2, mhdr::kFlags);
    lw(t1, gp, kGpIm3DPrimTable);
    lw(t2, a1, mcache::kHeader);
    lbu(a3, src, im3dsrc::kPrimType);
    t0 = addu(t0, t1);
    lw(a2, t2, mhdr::kFlags);
    a3 = addu(a3, t0);
    lbu(a3, a3, kIm3DPrimFlags);
    v1 = a2 & v1;
    v1 = v1 | a3;
    sw(v1, t2, mhdr::kFlags);
    lw(v1, src, im3dsrc::kIndices);
    if (v1 == 0) {
        // 0x004a253c: not indexed: header flags |= 0x100
        charge(ctx, 5);
        lw(a2, a1, mcache::kHeader);
        lw(v1, a2, mhdr::kFlags);
        v1 = v1 | 0x100;
        sw(v1, a2, mhdr::kFlags);
        backedge(ctx);
    }
    // 0x004a2510: the mesh list and its indices / count
    charge(ctx, 11);
    lw(a2, a1, mcache::kRecord);
    mview::la(v1, kIm3DMeshList);
    sw(zero, a2, kCacheRecordWord4);
    lw(a1, a1, mcache::kHeader);  // $a1 = the header from here
    sw(v1, a1, mhdr::kList);
    lw(v1, src, im3dsrc::kIndices);
    sw(v1, a1, mhdr::kIndices);
    lw(v1, src, im3dsrc::kVertexCount);
    sw(v1, a1, mhdr::kIndexCount);
    // 0x004a2550
    charge(ctx, 2);
}

u32 sub_4A2BA0(EEContext& ctx) {
    guest::enter(ctx, 2);
    setr(ctx, GPR_V0, 1);
    return 1;
}

u32 sub_4A35B0(EEContext& ctx) {
    guest::enter(ctx, 2);
    setr(ctx, GPR_V0, 0);
    return 0;
}

// 0x004A3F70 sub_4A3F70 -- 232 bytes; leaf frame (no stack)
// sub_4A3F70 [sector bounding box vs. the camera frustum] (c7): *out = 2 inside, 1 when a plane cuts
// the box. The current camera's frustum planes at *0x960070 + the camera plugin offset + 96: 20-byte
// {normal, distance, corner selectors sx sy sz (bytes +16..+18)}. Per plane the box corner (sector +96 inf /
// +108 sup, picked per axis by 1 - selector) is tested: on the positive side -> *out = 1 and stop.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4A3F70(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::c_le_s, hg::charge, hg::cond, hg::enter, hg::lbu,
          hg::lw, hg::lwc1, hg::madd_s, hg::madda_s, hg::mtc1, hg::mula_s, hg::sll, hg::sub_s, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, gp{ctx, 28};
    Gpr& sector = a0;
    Gpr& out = a1;
    Gpr& planes = a3;  // the plane cursor
    Gpr& left = a2;  // planes left - 1
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7};
    // 0x004a3f70
    enter(ctx, 10);  // entry check point + this block's cycles
    v1 = 2;
    sw(v1, out, 0);
    v1 = mview::hi(kRwGlobals);
    lw(planes, gp, kGpCameraFrustum);
    lw(t0, v1, mview::lo(kRwGlobals));  // the current camera
    v1 = 6;
    planes = addu(t0, planes);
    left = addiu(v1, -1);
    planes = addiu(planes, kFrustumPlanes);
    if (v1 != 0) {
        // 0x004a3f98: per plane
        charge(ctx, 2);
        mtc1(zero, f2);
        v1 = 1;
        for (;;) {
            // 0x004a3fa0: corner = per axis (1 - selector) * 12 into {inf, sup}; d = n . corner - dist; d <= 0?
            charge(ctx, 32);
            lbu(t3, planes, plane::kSelZ);
            lwc1(f1, planes, plane::kNy);
            lbu(t2, planes, plane::kSelX);
            lwc1(f4, planes, plane::kNx);
            lbu(t1, planes, plane::kSelY);
            lwc1(f6, planes, plane::kNz);
            lwc1(f0, planes, plane::kDist);
            t4 = subu(v1, t3);
            t3 = subu(v1, t2);
            t2 = sll(t4, 1);
            t4 = addu(t2, t4);
            t2 = subu(v1, t1);
            t4 = sll(t4, 2);
            t1 = sll(t3, 1);
            t1 = addu(t1, t3);
            t3 = addu(t4, sector);
            t1 = sll(t1, 2);
            lwc1(f7, t3, kSectorBBox + 8);  // corner.z
            t3 = addu(t1, sector);
            t1 = sll(t2, 1);
            t1 = addu(t1, t2);
            t1 = sll(t1, 2);
            t1 = addu(t1, sector);
            lwc1(f3, t1, kSectorBBox + 4);  // corner.y
            lwc1(f5, t3, kSectorBBox);  // corner.x
            mula_s(f3, f1);
            madda_s(f5, f4);
            madd_s(f1, f7, f6);
            sub_s(f0, f1, f0);
            c_le_s(f0, f2);
            t0 = v1;
            if (cond(ctx)) {
                // 0x004a4020: d <= 0: inside this plane
                charge(ctx, 1);
                t0 = 0;
            }
            // 0x004a4024
            charge(ctx, 3);
            t0 = t0 ^ 0x1;
            if (t0 == 0) {
                // 0x004a4030: the corner is on the positive side: *out = 1, stop
                charge(ctx, 3);
                v1 = 1;
                sw(v1, out, 0);
                // 0x004a4050 (the shared epilogue, written out on this path)
                charge(ctx, 2);
                return;
            }
            // 0x004a403c: next plane
            charge(ctx, 4);
            t0 = left;
            planes = addiu(planes, 20);
            left = addiu(left, -1);
            if (t0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004a404c: every plane passed: *out stays 2
        charge(ctx, 1);
    }
    // 0x004a4050
    charge(ctx, 2);
}

// 0x0046AD20 sub_46AD20 -- 84 bytes; leaf frame (no stack)
// sub_46AD20 [PDS registry lookup]: the 20-byte entry whose id (+8) matches, or 0.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_46AD20(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::sll, hg::sltu;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    Gpr& id = a1;
    Gpr& count = a2;
    Gpr& i = a3;
    // 0x0046ad20
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(count, a0, pds::kCount);
    at = sltu(0, count);
    i = 0;
    if (at != 0) {
        // 0x0046ad30: the entries
        charge(ctx, 2);
        lw(v1, a0, pds::kEntries);
        a0 = v1;
        for (;;) {
            // 0x0046ad38
            charge(ctx, 3);
            lw(v0, a0, kPdsEntryId);
            if (id == v0) {
                // 0x0046ad44: found: entries + 20 * i
                charge(ctx, 5);
                v0 = sll(i, 2);
                v0 = addu(v0, i);
                v0 = sll(v0, 2);
                v0 = addu(v1, v0);
                // 0x0046ad6c (the shared epilogue, written out on this path)
                charge(ctx, 2);
                return;
            }
            // 0x0046ad58: next entry
            charge(ctx, 4);
            i = addiu(i, 1);
            v0 = sltu(i, count);
            a0 = addiu(a0, 20);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0046ad68: not found: 0
    charge(ctx, 1);
    v0 = 0;
    // 0x0046ad6c
    charge(ctx, 2);
}

u32 RpPDSGetPipe(EEContext& ctx, u32 id) {
    (void)id;
    guest::enter(ctx, 8);
    kwln::Frame frame(ctx, 16);
    setr(ctx, GPR_A1, reg(ctx, GPR_A0));
    setr(ctx, GPR_A0, sx(kPdsRegistry));
    frame.sd(GPR_RA, 0);
    kwln::jal(ctx, 0x46A8A0u, &recomp_gen::fn_sub_46AD20_0046ad20);
    u64 v0 = reg(ctx, GPR_V0);
    if (v0 == 0) {
        guest::charge(ctx, 1);
    } else {
        guest::charge(ctx, 2);
        v0 = lws(ctx, lo(v0) + 16);
    }
    guest::charge(ctx, 3);
    setr(ctx, GPR_V0, v0);
    return lo(v0);
}

// 0x00468720 sub_468720 -- 180 bytes; frame 0x10
// sub_468720 [MatFX bump map: build the combined texture name]: the two names (tex + 16) interleaved
// character by character until 30 characters or both end; texA 0 -> texB twice. The two name cursors live in
// the frame (+8 = texA's name, +12 = texB's); the inner loop walks them by address.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_468720(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::lb, hg::lw, hg::sb, hg::slti, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, sp{ctx, 29};
    Gpr& out = a0;
    Gpr& count = t2;  // characters written
    // 0x00468720
    enter(ctx, 3);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    count = 0;
    if (a1 == 0) {
        // 0x00468790: no texA: texB's name twice
        charge(ctx, 4);
        v1 = addiu(a2, kTexName);
        sw(v1, sp, 0xC);
        sw(v1, sp, 0x8);
        backedge(ctx);
    } else {
        // 0x0046872c: texA's and texB's names
        charge(ctx, 4);
        a1 = addiu(a1, kTexName);
        v1 = addiu(a2, kTexName);
        sw(a1, sp, 0x8);
        sw(v1, sp, 0xC);
    }
    // 0x0046873c: the cursors' addresses; count < 30?
    charge(ctx, 3);
    a3 = addiu(sp, 0xC);
    a2 = addiu(sp, 0x8);
    at = slti(count, kNameMax);
    for (;;) {
        // 0x00468748: while (count < 30)
        charge(ctx, 2);
        if (at == 0) {
            break;
        }
        // 0x00468750: texA's name ended?
        charge(ctx, 4);
        lw(v1, sp, 0x8);
        lb(v1, v1, 0);
        if (v1 == 0) {
            // 0x004687b8: and texB's: stop
            charge(ctx, 4);
            lw(v1, a3, 0);
            lb(v1, v1, 0);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00468760: one character from each name (a name that has ended adds none)
        charge(ctx, 2);
        t1 = 0;
        t0 = a2;
        for (;;) {
            // 0x00468768: a name that has not ended gives one character
            charge(ctx, 4);
            lw(a1, t0, 0);
            lb(v1, a1, 0);
            if (v1 != 0) {
                // 0x004687a0: *out++ = *name++; count++
                charge(ctx, 6);
                sb(v1, out, 0);
                count = addiu(count, 1);
                v1 = addiu(a1, 1);
                out = addiu(out, 1);
                sw(v1, t0, 0);
                backedge(ctx);
            }
            // 0x00468778: the next name
            charge(ctx, 4);
            t1 = addiu(t1, 1);
            v1 = slti(t1, 2);
            t0 = addiu(t0, 4);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00468788: count < 30?
        charge(ctx, 2);
        at = slti(count, kNameMax);
        backedge(ctx);
    }
    // 0x004687c8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    sb(zero, out, 0);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game

// =================================================================================================================
// Entry points of the recompiled program (recomp/generated/functions.h): the hand versions take their arguments
// from $a0..$a3 and leave every register effect themselves.
// =================================================================================================================
namespace p3fes::recomp_gen {

namespace g = ::p3fes::game;
using ::p3fes::game::guest::arg32;

void fn_sub_4C1C50_004c1c50(p3fes::EEContext& ctx) { g::sub_4C1C50(ctx, ee::core::gpr64(ctx, GPR_A0)); }
void fn_sub_4C1D10_004c1d10(p3fes::EEContext& ctx) { g::sub_4C1D10(ctx, arg32(ctx, 0)); }
void fn_sub_4F0C60_004f0c60(p3fes::EEContext& ctx) { g::sub_4F0C60(ctx); }
void fn_sub_4F2710_004f2710(p3fes::EEContext& ctx) { g::sub_4F2710(ctx); }
void fn_sub_4F2E60_004f2e60(p3fes::EEContext& ctx) { g::sub_4F2E60(ctx); }
void fn_sceGsGetGParam_004f9040(p3fes::EEContext& ctx) { g::sceGsGetGParam(ctx); }
void fn_sceDmaGetChan_004fa8f0(p3fes::EEContext& ctx) { g::sceDmaGetChan(ctx, ee::core::gpr64(ctx, GPR_A0)); }
void fn_sub_490D80_00490d80(p3fes::EEContext& ctx) { g::sub_490D80(ctx, ee::core::gpr64(ctx, GPR_A0)); }
void fn_sub_4A2BA0_004a2ba0(p3fes::EEContext& ctx) { g::sub_4A2BA0(ctx); }
void fn_sub_4A35B0_004a35b0(p3fes::EEContext& ctx) { g::sub_4A35B0(ctx); }
void fn_RpPDSGetPipe_0046a890(p3fes::EEContext& ctx) { g::RpPDSGetPipe(ctx, arg32(ctx, 0)); }

}  // namespace p3fes::recomp_gen
