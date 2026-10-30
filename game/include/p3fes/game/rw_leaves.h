// Pure leaves of the RenderWare sky driver (band 0x460000-0x4FB100), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/22_rendering.md, queue docs/ANALYSIS/queue_rendering.txt "Full queue"). Slice `render_rw`:
// class a / a0 entries without `callsB`, depth 0-2, outside the first two slices -- the matrix product and
// inverses, the vector normalise, the camera frustum tests (c7), the render-state getter (c6), the texture
// cache release (c5), the singly linked list / registry / material list accessors, the Im3D and PS2All
// helper callbacks, the error slot and the texture-name builder.
//
// Names: every function keeps its symbols/functions.json name (mostly `sub_XXXXXX`); a bracketed name in a
// comment is a role description, not an imported name (community hints stay out of the repo, ADR-0009).
//
// Register contract. These are RenderWare library functions compiled with GCC; their callers may keep values
// in caller-saved registers across a call the compiler could see into, and compiled code reads registers a
// callee left behind when a local is uninitialised (docs/PHASE5_AGENT_BRIEF.md, wave 6). So each hand
// version leaves EVERY register the original writes with the original's final value: $v0 (also when the
// original leaves it untouched on a path), the scratch GPRs ($at, $v1, $a0..$a3, $t0..$t4), HI/LO of a
// MULT, the FPU registers, ACC and FCR31 (condition bit, D/I flags of DIV.S/SQRT.S) of the float leaves and
// the VU0 registers / ACC / MAC / STATUS of the VU0 matrix product. tests/game/test_render_rw.cpp compares
// all of them against the recompiled bodies. The functions return their C result for host callers too.
//
// Virtual time per ADR-0013: `guest::enter` / `guest::charge` with the block costs of the generated bodies
// (recomp/generated fn_0041.. / fn_0042..), `guest::backedge` wherever the recompiled body has a back-edge
// check (also on the backward `goto`s of non-loop shapes, e.g. the shared tail of sub_4C1C50).
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/ee/fpu.h"
#include "p3fes/ee_context.h"

#include <cstdint>

namespace p3fes::game {

// --- guest addresses ------------------------------------------------------------------------------------------
namespace rwl {
constexpr u32 kRwGlobals = 0x00960070u;      // the RW engine globals block (plugin offsets are added to it)
constexpr u32 kTexCache = 0x0077F200u;       // texture cache: non-zero when the cache is active
constexpr u32 kTexCacheBack = 0x0077F204u;   // ring end trimmed downwards (wrapping at 0 to count - 1); -1 empty
constexpr u32 kTexCacheFront = 0x0077F208u;  // ring end trimmed upwards (wrapping at count to 0); -1 empty
constexpr u32 kTexCacheCount = 0x0077F210u;  // number of 12-byte slots
constexpr u32 kTexCacheSlots = 0x0077F214u;  // slot array: {raster, tbp, cbp}
constexpr u32 kTexCacheLast = 0x0077F224u;   // the raster of the last cache access
constexpr u32 kTexCacheHit0 = 0x0077F22Cu;   // two remembered slot indices (-1 none)
constexpr u32 kTexCacheHit1 = 0x0077F230u;
constexpr u32 kTexCacheRelease = 0x0077F238u;  // release callback when the cache is off
constexpr u32 kGsGParam = 0x0077F280u;       // libgraph's sceGsGParam
constexpr u32 kDmaChanTable = 0x0077F2D0u;   // libdma's ten channel register-block pointers
constexpr u32 kPdsRegistry = 0x0095C44Cu;    // the PDS pipeline registry {entries, count}, 20-byte entries
constexpr u32 kIm3DMeshHeader = 0x0077DEC0u; // the Im3D mesh header the PS2All mesh-cache callback fills
constexpr u32 kIm3DMeshList = 0x0077DEE0u;

// gp-relative words (`$gp` = 0x7D2CF0, read from the register as the code does).
constexpr s32 kGpErrorOffset = -17440;      // plugin offset of the error slot in the RW globals
constexpr s32 kGpMatrixOffset = -17432;     // plugin offset of the matrix module (its flags word at +4)
constexpr s32 kGpCameraSectors = -17544;    // plugin offset of the camera's sector list
constexpr s32 kGpRasterExt = -16968;        // plugin offset of the sky raster extension (+88 = cache slot)
constexpr s32 kGpIm3DOffset = -16848;       // plugin offset of the Im3D module state
constexpr s32 kGpRxHeap = -16832;           // the global RxHeap
constexpr s32 kGpCameraFrustum = -16972;    // plugin offset of the current camera's frustum planes (+96)
constexpr s32 kGpIm3DPrimTable = -17568;    // plugin offset of the Im3D prim-type table (+39)
constexpr s32 kGpIm3DMeshCache = -20704;    // the Im3D mesh-cache record
}  // namespace rwl

// --- rwcore ---------------------------------------------------------------------------------------------------
// sub_4C1C50 [set the engine error slot]: (pluginID, errorCode) stored only while the slot is empty
// (pluginID 0, code 0x80000000); a code with bit 31 set clears the plugin ID. Returns `error`.
u64 sub_4C1C50(EEContext& ctx, u64 error);
// sub_4C1D10 [error-code builder, varargs]: spills $a1..$t3 into its va_list frame and returns the code.
u64 sub_4C1D10(EEContext& ctx, u32 code);
// sub_4C1E60 [singly linked array: empty]: list->count = 0.
void sub_4C1E60(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_4C2090 [array base, 0 when empty], sub_4C2120 [count], sub_4C21B0 [entry = base + stride * index].
void sub_4C2090(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
void sub_4C2120(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
void sub_4C21B0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_4C2F30 [matrix product on VU0]: dst = a * b (4x4, rows a[i].x*b0 + a[i].y*b1 + a[i].z*b2 (+ b3 for the
// position row)), dst flags = a.flags & b.flags. Returns dst.
void sub_4C2F30(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_4C6970 [normalise a 3-vector]: dst = src / |src| (src unchanged in direction when |src| = 0).
void sub_4C6970(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_4C9DF0 [camera frustum test of a sphere] (c7): 0 outside, 1 intersecting, 2 inside the six planes at
// camera + 148 (20-byte {normal, distance, ...}).
void sub_4C9DF0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_4CAE30 [frame dirty bits]: frame->root->flags & 3.
void sub_4CAE30(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_4C2860 [general 3x4 matrix inverse]: adjugate / determinant (determinant 0 -> scale 1), translation
// -pos * inverse; flags 0. Returns dst.
void sub_4C2860(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_4C32A0 [matrix inverse]: identity (engine and matrix flag 0x20000) -> copy; orthonormal (flags & 3 == 3)
// -> transpose and -pos * transpose, flags 3; else sub_4C2860. Returns dst.
void sub_4C32A0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_4CC0A0 [image: alpha from max(r, g, b)]: 32-bit pixels, or the palette of a 4/8-bit image.
void sub_4CC0A0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- render state / raster / texture cache ---------------------------------------------------------------------
// sub_4D6B60 [index of the most significant bit, -1 for 0].
void sub_4D6B60(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_4D81B0 [sky render-state get] (c6): states 1..5 from the GS shadow words; 1 when known.
void sub_4D81B0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_4DB200 [minimum transfer size of a raster format]: *outWidth / *outHeight.
void sub_4DB200(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_4F0C60 [texture cache end-of-frame hook]: empty in retail.
void sub_4F0C60(EEContext& ctx);
// sub_4F1540 [texture cache: release a raster] (c5): frees its slot, forgets the remembered indices, trims the
// ring's head/tail over freed slots; with the cache off, the release callback.
void sub_4F1540(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

// --- Im3D / RxHeap / libgraph / libdma --------------------------------------------------------------------------
// sub_4F1F80 [Im3D end]: clears the 60-byte Im3D pool when it is open (memset); 1 if it was.
void sub_4F1F80_regs(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_4F2710 [Im3D pool address], sub_4F2E60 [the global RxHeap].
u32 sub_4F2710(EEContext& ctx);
u32 sub_4F2E60(EEContext& ctx);
u32 sceGsGetGParam(EEContext& ctx);
// sceDmaGetChan: the channel's register block (0..9), else 0.
u32 sceDmaGetChan(EEContext& ctx, u64 chan);

// --- rpworld / skin / PS2All / MatFX ------------------------------------------------------------------------------
// sub_48A3E0 [skin: skin-to-bone matrices] = skin + 12.
void sub_48A3E0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_490D80 [clump callback that does nothing]: returns its argument.
u64 sub_490D80(EEContext& ctx, u64 clump);
// sub_491100 [atomic: resync the interpolated bounding sphere] (c7): lerp between the two morph targets' spheres.
void sub_491100(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_495320 [material list: material i].
void sub_495320(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_4992F0 [find-sector callback]: query {sector, found}: found = 1 and stop (0) when sector matches.
void sub_4992F0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_49C330 [for all sectors in the camera frustum] (c7): callback(sector, data) until it returns 0.
void sub_49C330(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_49FEC0 [PS2All node: group meshes]: node->private->groupMeshes = value; node, or 0.
void sub_49FEC0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_4A0C20 [PS2All mesh instance test]: flag 8 (re-instance) when the vertex count or the geometry flags differ
// from the resEntry's. Returns 1.
void sub_4A0C20(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_4A24A0 [Im3D PS2All mesh-cache callback]: points the record at the Im3D mesh header and fills it.
void sub_4A24A0(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_4A2BA0 [PS2All post-mesh callback]: 1; sub_4A35B0: 0.
u32 sub_4A2BA0(EEContext& ctx);
u32 sub_4A35B0(EEContext& ctx);
// sub_4A3F70 [sector bounding box vs. the camera frustum] (c7): *out = 2 inside, 1 when a plane cuts the box.
void sub_4A3F70(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// sub_46AD20 [PDS registry lookup]: the 20-byte entry whose id (+8) matches, or 0.
void sub_46AD20(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
// RpPDSGetPipe: the registered pipeline (+16) of a PDS id, or 0.
u32 RpPDSGetPipe(EEContext& ctx, u32 id);
// sub_468720 [MatFX bump map: build the combined texture name]: the two names (tex + 16) interleaved character by
// character until 30 characters or both end; texA 0 -> texB twice.
void sub_468720(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0

}  // namespace p3fes::game
