// The PS2All mesh seam (mesh.h has the data flow; docs/ANALYSIS/22_rendering.md sections 3 and 8.2).
//
// Cycle model (ADR-0013): every charge() below is one `ctx.cycles += N` block of the recompiled body in
// recomp/generated (fn_0042_* / fn_0044_* / fn_0048_*); backedge() sits wherever that body has a check point
// on a backward jump -- loops, and also the backward `goto`s of the compiler's block layout (the shared tails
// the branches return to), which the hand versions keep as explicit check points.
//
// Registers: register-faithful (mesh.h). Each body runs on a Cpu view of the guest context: one variable per
// GPR (64-bit writes keep bits 64..127, as the EE does; lq / MMI results write all 128), the FPU / VU0 / HI-LO
// operations through the runtime's own instruction semantics, prologue spills and epilogue reloads on the
// guest stack. Guest structure offsets are named in mesh.h and in the comments; the observer records
// (ObjectSetup, SkinPalette, MeshDraw) are filled from the guest state after it is complete.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 20 of the 21 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: faults only 8, callee frames 7, the hand version
// terminated the host on a random world 3, frame/spills 2); each keeps the notes of its earlier hand version above
// it. The others are the hand-written versions this header describes.
#include "p3fes/game/mesh.h"

#include "p3fes/ee/vu0.h"
#include "p3fes_recomp_rt.h"

#include <initializer_list>
#include <iterator>
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
void fn__rwDMAOpenVIFPkt_004d59d0(p3fes::EEContext&);  // the DMA packet layer (DMAC registers)
void fn__rwDMAAddPURef_004d51c0(p3fes::EEContext&);        // _rwDMAAddPURef
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);        // RwFrameGetLTM
void fn_sub_4C32A0_004c32a0(p3fes::EEContext&);        // matrix inverse (render_rw)
void fn_sub_4C2F30_004c2f30(p3fes::EEContext&);        // matrix product (render_rw)
void fn_sub_48A3E0_0048a3e0(p3fes::EEContext&);        // skin -> skin-to-bone matrices (render_rw)
void fn_atomicGetWorldBoundingSphere_004912b0(p3fes::EEContext&);        // atomic world bounding sphere
void fn_worldForAllLights_00499c20(p3fes::EEContext&);        // world: for all lights (callback, data)
void fn_sub_49E5A0_0049e5a0(p3fes::EEContext&);        // resEntry array (re)allocation (RwMalloc/RwFree)
void fn_PS2AllNodeInstance_0049faa0(p3fes::EEContext&);        // PS2AllNodeInstance
void fn_RxPipelineExecute_004f2e70(p3fes::EEContext&);        // RxPipelineExecute
void fn_sub_49CA50_0049ca50(p3fes::EEContext&);
void fn_sub_49CAB0_0049cab0(p3fes::EEContext&);
void fn_sub_49CBD0_0049cbd0(p3fes::EEContext&);
void fn_RpAtomicPS2AllPrimTypeTransTypeSetupFunc_004a05d0(p3fes::EEContext&);
void fn_sub_4A0480_004a0480(p3fes::EEContext&);
void fn_sub_49FF10_0049ff10(p3fes::EEContext&);
void fn_sub_4A0430_004a0430(p3fes::EEContext&);
void fn_sub_4A06C0_004a06c0(p3fes::EEContext&);
void fn__rpSkinMatrixUpdating_0046b510(p3fes::EEContext&);
void fn_openVU1SetupPktNew_004ec2b0(p3fes::EEContext&);
void fn_sub_4F0F30_004f0f30(p3fes::EEContext&);
void fn_RpSkyTexCacheAccessRaster_004f1020(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

namespace core = ee::core;
namespace gen = ::p3fes::recomp_gen;
using namespace mesh;

const DrawObserver* g_observer = nullptr;

// --- the draw records (host-only reads: no guest effect) -----------------------------------------------------------
// The register-faithful bodies (p3fes_handgen's, since the 2026-10-21 audit) capture the packet positions and the
// program / resEntry where the original has them in registers and report as the earlier hand versions did.
struct BridgePass {
    u32 colour_at = 0, surface_at = 0;  // where sub_49CAB0 / sub_49CBD0 wrote their quadwords
    u32 program = 0;
    bool uploaded = false;
    u32 res_entry = 0, vif_offset = 0;
};
u32 rd32(const EEContext& c, u32 va) { return guest::load<u32>(c, va); }
u64 rd64(const EEContext& c, u32 va) { return guest::load<u64>(c, va); }
u32 rd8(const EEContext& c, u32 va) { return guest::load<u8>(c, va); }
u32 gp_word(const EEContext& c, s32 off) { return static_cast<u32>(c.gpr[GPR_GP].u64[0]) + static_cast<u32>(off); }
u32 write_ptr(const EEContext& c) { return rd32(c, gp_word(c, kGpSprWrite)); }

// RpMeshPS2AllBridgeCallBack's record (mesh.h MeshDraw), read once the guest state is complete.
void report_bridge(EEContext& c, u32 pipe, const BridgePass& p) {
    if (!g_observer || !g_observer->mesh) return;
    MeshDraw draw;
    draw.atomic = rd32(c, pipe + pd::kObject);
    draw.mesh = rd32(c, pipe + pd::kMesh);
    draw.material = draw.mesh ? rd32(c, draw.mesh + 8) : 0;
    draw.texture = rd32(c, pipe + pd::kTexture);
    draw.raster = draw.texture ? rd32(c, draw.texture) : 0;
    if (draw.raster) {
        const u32 ext = draw.raster + rd32(c, gp_word(c, kGpRasterExt));
        draw.tex0 = rd32(c, ext + 8) | (static_cast<u64>(rd32(c, ext + 12)) << 32);
    }
    draw.tex1 = rd64(c, gp_word(c, kGpTex1));
    draw.clamp = rd64(c, gp_word(c, kGpClamp));
    draw.test = rd64(c, gp_word(c, kGpTest));
    draw.gif_tag_lo = rd64(c, kTplGifTag);
    draw.gif_tag_hi = rd64(c, kTplGifTag + 8);
    draw.trans_type = static_cast<u8>(rd8(c, pipe + pd::kTransType));
    draw.prim_type = static_cast<u8>(rd8(c, pipe + pd::kPrimType));
    draw.vu1_code_index = static_cast<u8>(rd8(c, pipe + pd::kVu1CodeIndex));
    draw.vu1_program = p.program;
    draw.program_uploaded = p.uploaded;
    for (u32 i = 0; i < 4; ++i) {
        draw.colour[i] = rd32(c, p.colour_at + 4 * i);
        draw.surface[i] = rd32(c, p.surface_at + 4 * i);
    }
    draw.res_entry = p.res_entry;
    draw.res_data = p.res_entry ? rd32(c, p.res_entry + 32) : 0;
    draw.vif_offset = p.vif_offset;
    g_observer->mesh(c, draw);
}

// --- R5900 integer results (32-bit operations sign-extend into the 64-bit register) ----------------------
constexpr u64 sx(u32 v) { return core::sext32(v); }
constexpr u64 si(s32 v) { return static_cast<u64>(static_cast<s64>(v)); }  // a negative immediate
constexpr u64 addiu(u64 a, s32 i) { return core::add32i(a, i); }
constexpr u32 w(u64 v) { return static_cast<u32>(v); }

// One GPR of the guest context.
struct Gpr {
    EEContext& c;
    const unsigned r;
    operator u64() const noexcept { return c.gpr[r].u64[0]; }
    u32 u() const noexcept { return c.gpr[r].u32[0]; }
    Gpr& operator=(u64 v) noexcept {
        core::set_gpr64(c, r, v);
        return *this;
    }
    Gpr& operator=(const Gpr& o) noexcept { return *this = static_cast<u64>(o); }
};

// FPR / VU0 register numbers and VU0 broadcast fields.
enum : unsigned { F0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13 };
enum : unsigned { VF0, VF1, VF2, VF3, VF4, VF5, VF6, VF7, VF8, VF9, VF10, VF11, VF12, VF13, VF14, VF15, VF16 };
constexpr unsigned XYZW = 15, BX = 0, BY = 1, BZ = 2, BW = 3;

// The guest machine as the bodies see it.
class Cpu {
public:
    explicit Cpu(EEContext& ctx) noexcept : c(ctx) {}

    EEContext& c;
    Gpr zero{c, 0}, at{c, 1}, v0{c, 2}, v1{c, 3}, a0{c, 4}, a1{c, 5}, a2{c, 6}, a3{c, 7};
    Gpr t0{c, 8}, t1{c, 9}, t2{c, 10}, t3{c, 11}, t4{c, 12}, t5{c, 13}, t6{c, 14}, t7{c, 15};
    Gpr s0{c, 16}, s1{c, 17}, s2{c, 18}, s3{c, 19}, s4{c, 20}, s5{c, 21}, s6{c, 22}, s7{c, 23};
    Gpr gp{c, 28}, sp{c, 29}, s8{c, 30}, ra{c, 31};

    // virtual time
    void enter(u64 n) { guest::enter(c, n); }  // not noexcept: a check point may raise a fatal event
    void charge(u64 n) noexcept { guest::charge(c, n); }
    void backedge() { guest::backedge(c); }

    // loads / stores (addresses are 32-bit; LQ / SQ force a quadword boundary)
    u64 lw(u64 a) const noexcept { return sx(guest::load<u32>(c, w(a))); }
    u64 lwu(u64 a) const noexcept { return guest::load<u32>(c, w(a)); }
    u64 lh(u64 a) const noexcept { return core::sext16(guest::load<u16>(c, w(a))); }
    u64 lhu(u64 a) const noexcept { return guest::load<u16>(c, w(a)); }
    u64 lbu(u64 a) const noexcept { return guest::load<u8>(c, w(a)); }
    u64 ld(u64 a) const noexcept { return guest::load<u64>(c, w(a)); }
    void lq(Gpr& d, u64 a) noexcept { core::set_gpr128(c, d.r, guest::load<u128>(c, w(a) & ~15u)); }
    void sw(u64 a, u64 v) noexcept { guest::store<u32>(c, w(a), w(v)); }
    void sh(u64 a, u64 v) noexcept { guest::store<u16>(c, w(a), static_cast<u16>(v)); }
    void sb(u64 a, u64 v) noexcept { guest::store<u8>(c, w(a), static_cast<u8>(v)); }
    void sd(u64 a, u64 v) noexcept { guest::store<u64>(c, w(a), v); }
    void sq(u64 a, const Gpr& v) noexcept { guest::store<u128>(c, w(a) & ~15u, c.gpr[v.r]); }

    // FPU (the runtime's instruction semantics: EE singles, ACC, FCR31 flags)
    void lwc1(unsigned f, u64 a) noexcept { c.fpr[f] = guest::load<u32>(c, w(a)); }
    void swc1(unsigned f, u64 a) noexcept { guest::store<u32>(c, w(a), c.fpr[f]); }
    void mtc1(const Gpr& g, unsigned f) noexcept { rt::mtc1(c, g.r, f); }
    void mfc1(Gpr& g, unsigned f) noexcept { rt::mfc1(c, g.r, f); }
    void cvt_s_w(unsigned d, unsigned s) noexcept { rt::cvt_s_w(c, d, s); }
    void add_s(unsigned d, unsigned s, unsigned t) noexcept { rt::add_s(c, d, s, t); }
    void sub_s(unsigned d, unsigned s, unsigned t) noexcept { rt::sub_s(c, d, s, t); }
    void mul_s(unsigned d, unsigned s, unsigned t) noexcept { rt::mul_s(c, d, s, t); }
    void div_s(unsigned d, unsigned s, unsigned t) noexcept { rt::div_s(c, d, s, t); }
    void madd_s(unsigned d, unsigned s, unsigned t) noexcept { rt::madd_s(c, d, s, t); }
    void mula_s(unsigned s, unsigned t) noexcept { rt::mula_s(c, s, t); }
    void madda_s(unsigned s, unsigned t) noexcept { rt::madda_s(c, s, t); }
    void neg_s(unsigned d, unsigned s) noexcept { rt::neg_s(c, d, s); }
    void sqrt_s(unsigned d, unsigned t) noexcept { rt::sqrt_s(c, d, t); }
    void c_le_s(unsigned s, unsigned t) noexcept { rt::c_le_s(c, s, t); }
    void c_lt_s(unsigned s, unsigned t) noexcept { rt::c_lt_s(c, s, t); }
    bool cop1_cond() const noexcept { return rt::cop1_cond(c); }

    // VU0 macro mode
    void lqc2(unsigned vf, u64 a) noexcept { ee::vu0::qmtc2(c.vu0, vf, guest::load<u128>(c, w(a) & ~15u)); }
    void sqc2(unsigned vf, u64 a) noexcept { guest::store<u128>(c, w(a) & ~15u, ee::vu0::qmfc2(c.vu0, vf)); }
    void vmula_bc(unsigned dest, unsigned fs, unsigned ft, unsigned bc) noexcept { rt::vmula_bc(c, dest, fs, ft, bc); }
    void vmadda_bc(unsigned dest, unsigned fs, unsigned ft, unsigned bc) noexcept { rt::vmadda_bc(c, dest, fs, ft, bc); }
    void vmadd_bc(unsigned dest, unsigned fd, unsigned fs, unsigned ft, unsigned bc) noexcept {
        rt::vmadd_bc(c, dest, fd, fs, ft, bc);
    }

    // MMI, HI/LO, COP0
    void pcpyld(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::pcpyld(c, d.r, s.r, t.r); }
    void ppacw(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::ppacw(c, d.r, s.r, t.r); }
    void pexew(Gpr& d, const Gpr& t) noexcept { rt::pexew(c, d.r, t.r); }
    void mult(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::mult(c, d.r, s.r, t.r); }
    void mfhi(Gpr& d) noexcept { rt::mfhi(c, d.r); }
    void di() noexcept { rt::di(c); }
    void ei() noexcept { rt::ei(c); }
    void sync_p() noexcept { rt::sync(c, 0x10); }
    void mfc0_status(Gpr& d) noexcept { rt::mfc0(c, d.r, 12); }

    // calls: `jal fn` at pc ($ra = pc + 8), `jalr target` at pc (through the dispatch table)
    void jal(u32 pc, rt::Fn fn) {
        rt::jal(c, pc);
        fn(c);
    }
    void jalr(u32 pc, u32 target) {
        rt::jalr(c, GPR_RA, pc);
        rt::lookup_func(target)(c);
    }

    // the light block / packet write pointers are re-read and re-written around every store, as compiled
    u32 gpw(s32 off) const noexcept { return gp.u() + static_cast<u32>(off); }

    // A 4x4 matrix in four VU0 registers, and the product as the compiled code issues it: rows of A in
    // vf[a..a+3], B in vf[b..b+3]; out[i] = A[i].x B0 + A[i].y B1 + A[i].z B2 (+ B3 * vf00.w = B3 for the
    // position row), through ACC.
    void lqc2_rows(unsigned vf, u64 addr) noexcept {
        for (unsigned i = 0; i < 4; ++i) lqc2(vf + i, addr + 16 * i);
    }
    void sqc2_rows(unsigned vf, u64 addr) noexcept {
        for (unsigned i = 0; i < 4; ++i) sqc2(vf + i, addr + 16 * i);
    }
    void vu0_matmul(unsigned out, unsigned a, unsigned b) noexcept {
        for (unsigned i = 0; i < 4; ++i) {
            vmula_bc(XYZW, b, a + i, BX);
            vmadda_bc(XYZW, b + 1, a + i, BY);
            if (i < 3) {
                vmadd_bc(XYZW, out + i, b + 2, a + i, BZ);
            } else {
                vmadda_bc(XYZW, b + 2, a + i, BZ);
                vmadd_bc(XYZW, out + 3, b + 3, VF0, BW);
            }
        }
    }

    // --- the bodies (mesh.h documents each) ---
    void filter_shadow();         // sub_49CA50

    // Light block helpers (gp-17516 is reloaded and rewritten around every store, as compiled).
    // `old = *lp; new = old + 4; *lp = new; store at old + 4` -- the block's "advance, then store" step.
    void light_push_f(Gpr& old, Gpr& nw, unsigned f) {
        old = lw(gpw(kGpLightPtr));
        nw = addiu(old, 4);
        sw(gpw(kGpLightPtr), nw);
        swc1(f, old + 4);
    }
    void light_push_w(Gpr& old, Gpr& nw, u64 value) {
        old = lw(gpw(kGpLightPtr));
        nw = addiu(old, 4);
        sw(gpw(kGpLightPtr), nw);
        sw(old + 4, value);
    }
    // `r = *lp; store at r; r = *lp + 4; *lp = r` -- "store, then advance".
    void light_put_f(Gpr& r, unsigned f) {
        r = lw(gpw(kGpLightPtr));
        swc1(f, r);
        r = lw(gpw(kGpLightPtr));
        r = addiu(r, 4);
        sw(gpw(kGpLightPtr), r);
    }
    // `r = *lp + n; *lp = r`
    void light_skip(Gpr& r, s32 n) {
        r = lw(gpw(kGpLightPtr));
        r = addiu(r, n);
        sw(gpw(kGpLightPtr), r);
    }
    // The end of a light: `p = *lp + step; n = *count + k; *lp = p; *count = n` (k quadwords written).
    void light_close(Gpr& p, Gpr& n, s32 step, s32 k) {
        p = lw(gpw(kGpLightPtr));
        n = lw(gpw(kGpLightCount));
        p = addiu(p, step);
        n = addiu(n, k);
        sw(gpw(kGpLightPtr), p);
        sw(gpw(kGpLightCount), n);
    }
};

// =========================================================================================================
// Leaves
// =========================================================================================================

// sub_49CA50: TEX1_1 MMAG/MMIN (bits 5..8) for the RwTextureFilterMode in $a0. Modes 1 (nearest) and others
// keep 0; 2 linear 0x60, 3 mip nearest 0x80, 4 mip linear 0x120, 5 linear-mip nearest 0xC0, 6 linear-mip
// linear 0x160.
void Cpu::filter_shadow() {
    enter(6);
    a1 = ld(gpw(kGpTex1));
    v1 = si(-481);  // ~0x1E0
    v1 = a1 & v1;
    static constexpr struct {
        u32 mode, bits;
    } kModes[] = {{6, 0x160}, {5, 0xC0}, {4, 0x120}, {3, 0x80}, {2, 0x60}};
    bool found = false;
    for (std::size_t i = 0; i < std::size(kModes); ++i) {
        if (i != 0) charge(3);
        at = kModes[i].mode;
        if (at == a0) {
            a1 = v1 | kModes[i].bits;
            found = true;
            break;
        }
    }
    if (!found) {
        charge(1);
        a1 = v1;
    }
    charge(3);
    sd(gpw(kGpTex1), a1);
}

// =========================================================================================================
// Lights
// =========================================================================================================
// The light block (buffer 0x95DFC0, write pointer gp-17516, quadword count gp-17520) is what the VU1 programs
// light with: on the first light of an object a 4-quadword header (the inverse LTM rows with the scale in the
// w lanes, or an identity with the scale), then per light its colour quadword {r, g, b, type} and, by type,
// the direction (directional), the position + radius (point) or the position + radius and direction + cone
// (spot / soft spot). At most 124 quadwords.

// =========================================================================================================
// Object set-up (stock atomic)
// =========================================================================================================

// =========================================================================================================
// Skin: the bone-matrix palette
// =========================================================================================================
// The skin plugin's globals at 0x95DE14: +0 the atomic extension offset (-> the hierarchy), +4 the geometry
// extension offset (-> the skin), +8 the palette (64 bytes per bone, uploaded to VU1 0x2BC), +0x20 a lighting
// hook (replaces the inlined light walk when set), +0x24 the partition record of sub_46B8E0. A hierarchy is
// {flags, node count, node frames, ..., node records (+16: 16 bytes each, +12 the frame)}; a skin {bone count,
// ..., skin-to-bone matrices at +12 (sub_48A3E0)}.

// =========================================================================================================
// The per-object VIF packet
// =========================================================================================================

// =========================================================================================================
// The texture cache entry
// =========================================================================================================
// A raster's sky extension (raster + gp-16968): +8 / +12 TEX0 (TBP0 in bits 0..13, CBP in bits 37..50 of the
// 64-bit word), +16 the palette offset in blocks, +20 K/L, +22 MXL, +23 "keep its MIPTBP", +24..+39 MIPTBP1/2,
// +88 the cache slot ({raster, tbp << 6, ...}, 12 bytes). Cache globals at 0x77F200 (active), 0x77F214 (slots),
// 0x77F220 (upload callback), 0x77F224 / 0x77F228 (last raster / mode), 0x77F22C / 0x77F230 (remembered slots).

// =========================================================================================================
// The material bridge
// =========================================================================================================

// =========================================================================================================
// The object node and the atomic render callback
// =========================================================================================================

// The argument registers of a host call (sign-extended 32-bit values, as `move` / `addiu` leave them); only
// the registers the function takes are written.
void args(EEContext& ctx, std::initializer_list<u32> values) {
    unsigned r = GPR_A0;
    for (const u32 v : values) core::set_gpr64(ctx, r++, sx(v));
}

}  // namespace

void sub_49CA50(EEContext& ctx, u32 filter_mode) {
    args(ctx, {filter_mode});
    Cpu(ctx).filter_shadow();
}

// 0x0049CAB0 sub_49CAB0 -- 288 bytes; leaf frame (no stack)
// sub_49CAB0: the material colour quadword. The bytes are converted as unsigned (the compiled code's
// `bltz` halving path of the unsigned conversion is dead for a zero-extended byte); r/g/b are scaled by
// $f12 (1/255 untextured, 1/507.6 textured: the bridge's choice) and alpha by 0x3B011B50.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_49CAB0(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::charge, hg::cvt_s_w, hg::enter, hg::i64, hg::lbu, hg::lw,
          hg::mfc1, hg::mtc1, hg::mul_s, hg::pexew, hg::ppacw, hg::sq, hg::srl, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f12{ctx, 12};
    // 0x0049cab0
    enter(ctx, 3);  // entry check point + this block's cycles
    lbu(v1, a0, 0);
    if (i64(v1) < 0) {
        // 0x0049cac8
        charge(ctx, 7);
        a1 = srl(v1, 1);
        v1 = v1 & 0x1;
        a1 = a1 | v1;
        mtc1(a1, f0);
        cvt_s_w(f4, f0);
        add_s(f4, f4, f4);
    } else {
        // 0x0049cabc
        charge(ctx, 3);
        mtc1(v1, f0);
        cvt_s_w(f4, f0);
    }
    // 0x0049cae4
    charge(ctx, 3);
    lbu(v1, a0, 1);
    if (i64(v1) < 0) {
        // 0x0049cafc
        charge(ctx, 7);
        a1 = srl(v1, 1);
        v1 = v1 & 0x1;
        a1 = a1 | v1;
        mtc1(a1, f0);
        cvt_s_w(f3, f0);
        add_s(f3, f3, f3);
    } else {
        // 0x0049caf0
        charge(ctx, 3);
        mtc1(v1, f0);
        cvt_s_w(f3, f0);
    }
    // 0x0049cb18
    charge(ctx, 3);
    lbu(v1, a0, 2);
    if (i64(v1) < 0) {
        // 0x0049cb30
        charge(ctx, 7);
        a1 = srl(v1, 1);
        v1 = v1 & 0x1;
        a1 = a1 | v1;
        mtc1(a1, f0);
        cvt_s_w(f2, f0);
        add_s(f2, f2, f2);
    } else {
        // 0x0049cb24
        charge(ctx, 3);
        mtc1(v1, f0);
        cvt_s_w(f2, f0);
    }
    // 0x0049cb4c
    charge(ctx, 3);
    lbu(v1, a0, 3);
    if (i64(v1) < 0) {
        // 0x0049cb64
        charge(ctx, 7);
        a0 = srl(v1, 1);
        v1 = v1 & 0x1;
        a0 = a0 | v1;
        mtc1(a0, f0);
        cvt_s_w(f1, f0);
        add_s(f1, f1, f1);
    } else {
        // 0x0049cb58
        charge(ctx, 3);
        mtc1(v1, f0);
        cvt_s_w(f1, f0);
    }
    // 0x0049cb80 (the shared epilogue, written out on this path)
    charge(ctx, 20);
    v1 = 0x3B010000;
    v1 = v1 | 0x1B50;
    mtc1(v1, f0);
    mul_s(f1, f1, f0);
    mul_s(f0, f3, f12);
    mfc1(a0, f1);
    mfc1(v1, f0);
    pexew(a0, a0);
    pexew(v1, v1);
    mul_s(f1, f2, f12);
    mul_s(f0, f4, f12);
    mfc1(a0, f1);
    mfc1(v1, f0);
    ppacw(a0, a0, v1);
    lw(v1, gp, -17148);  // 0x7CE9F4
    sq(a0, v1, 0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    v1 = addiu(v1, 16);
    sw(v1, gp, -17148);  // 0x7CE9F4
}

// 0x0049CBD0 sub_49CBD0 -- 88 bytes; leaf frame (no stack)
// sub_49CBD0: {ambient, specular, diffuse} x 255.00002 (0x437F0001) and spExtra ($f12) as one quadword.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_49CBD0(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addiu, hg::enter, hg::lw, hg::lwc1, hg::mfc1, hg::mtc1, hg::mul_s, hg::pexew,
          hg::ppacw, hg::sq, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x0049cbd0
    enter(ctx, 22);  // entry check point + this block's cycles
    lwc1(f3, a0, 0);
    v1 = 0x437F0000;
    lwc1(f2, a0, 4);
    v1 = v1 | 0x1;
    lwc1(f1, a0, 8);
    mtc1(v1, f0);
    mul_s(f2, f2, f0);
    mfc1(a0, f12);
    mfc1(v1, f2);
    pexew(a0, a0);
    pexew(v1, v1);
    mul_s(f1, f1, f0);
    mul_s(f2, f3, f0);
    mfc1(a0, f1);
    mfc1(v1, f2);
    ppacw(a0, a0, v1);
    lw(v1, gp, -17148);  // 0x7CE9F4
    sq(a0, v1, 0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    v1 = addiu(v1, 16);
    sw(v1, gp, -17148);  // 0x7CE9F4
}

// 0x004F1E20 sub_4F1E20 -- 32 bytes; leaf frame (no stack)
// sub_4F1E20: the two TEX0 words of the raster's sky extension (+8 -> *$a2, +12 -> *$a1). Returns the raster.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_4F1E20(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::enter, hg::lw, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, gp{ctx, 28};
    // 0x004f1e20
    enter(ctx, 8);  // entry check point + this block's cycles
    lw(v1, gp, -16968);  // 0x7CEAA8
    v0 = a0;
    a0 = addu(a0, v1);
    lw(v1, a0, 8);
    sw(v1, a2, 0);
    lw(v1, a0, 12);
    sw(v1, a1, 0);
}

// 0x004F1E40 sub_4F1E40 -- 140 bytes; leaf frame (no stack)
// sub_4F1E40: TEX1 = K (ext +20 bits 0..11 -> bits 32..43) | L (ext +20 bits 12..13 -> 19..20) | MXL (ext +22)
// | MMAG/MMIN of the filter mode in $a2 (the same table as sub_49CA50). Returns the raster.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_4F1E40(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll, hg::dsll32, hg::dsra32, hg::enter, hg::i64, hg::lbu,
          hg::lhu, hg::lw, hg::sd, hg::sra;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x004f1e40
    enter(ctx, 20);  // entry check point + this block's cycles
    lw(v0, gp, -16968);  // 0x7CEAA8
    v1 = addu(a0, v0);
    lbu(a3, v1, 22);
    lhu(v0, v1, 20);
    a3 = dsll32(a3, 0);
    v1 = v0 & 0xFFF;
    a3 = dsra32(a3, 0);
    v0 = sra(v0, 12);
    v1 = dsll32(v1, 0);
    v0 = v0 & 0x3;
    v1 = dsra32(v1, 0);
    v0 = dsll32(v0, 0);
    v1 = dsll32(v1, 0);
    v0 = dsra32(v0, 0);
    v1 = a3 | v1;
    v0 = dsll(v0, 19);
    v0 = v0 | v1;
    at = addiu(a2, -2);
    if (at == 0) {
        v1 = v0 | 0x60;
    } else {
        // 0x004f1e90
        charge(ctx, 2);
        if (i64(at) < 0) {
            v1 = v0 | 0x0;
        } else {
            // 0x004f1e98
            charge(ctx, 3);
            at = addiu(at, -2);
            if (at == 0) {
                v1 = v0 | 0x120;
            } else {
                // 0x004f1ea4
                charge(ctx, 2);
                if (i64(at) < 0) {
                    v1 = v0 | 0x80;
                } else {
                    // 0x004f1eac
                    charge(ctx, 3);
                    at = addiu(at, -2);
                    if (at == 0) {
                        v1 = v0 | 0x160;
                    } else {
                        // 0x004f1eb8
                        charge(ctx, 1);
                        v1 = v0 | 0xC0;
                    }
                }
            }
        }
    }
    // 0x004f1ebc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    sd(v1, a1, 0);
    v0 = a0;
}

// 0x004A05D0 RpAtomicPS2AllPrimTypeTransTypeSetupFunc -- 228 bytes; leaf frame (no stack)
// RpAtomicPS2AllPrimTypeTransTypeSetupFunc [RpAtomicPS2AllPrimTypeTransTypeSetupFunc]: from the mesh header flags (pd +12 -> +0):
//   strip (1) -> prim 4, tt = cam;   list (flags & 0xFF == 0) or fan (2) -> prim 3, tt = cam | 4;
//   points (0x10) -> prim 4, tt = cam; polyline (8) -> prim 2, tt = cam | 0x10; line list -> prim 1, cam | 0x14
// then tt |= 2 unless the frustum result ($a1) is 2 (inside).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void RpAtomicPS2AllPrimTypeTransTypeSetupFunc(EEContext& ctx) {
    using hg::Gpr, hg::backedge, hg::charge, hg::enter, hg::lbu, hg::lw, hg::sb;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, gp{ctx, 28};
    // 0x004a05d0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, a0, 12);
    t0 = 1;
    lw(t1, v1, 0);
    v1 = t1 & 0x1;
    if (v1 == t0) {
        // 0x004a065c
        charge(ctx, 5);
        v1 = 4;
        sb(v1, a0, 41);
        lbu(v1, gp, -16892);  // 0x7CEAF4
        sb(v1, a0, 40);
        backedge(ctx);
    } else {
        // 0x004a05e8
        charge(ctx, 3);
        v1 = t1 & 0xFF;
        if (v1 != 0) {
            // 0x004a05f4
            charge(ctx, 4);
            v1 = t1 & 0x2;
            a3 = 2;
            if (v1 == a3) {
                goto L_004a0670;
            }
            // 0x004a0604
            charge(ctx, 4);
            a2 = t1 & 0x10;
            v1 = 16;
            if (a2 == v1) {
                // 0x004a0688
                charge(ctx, 5);
                v1 = 4;
                sb(v1, a0, 41);
                lbu(v1, gp, -16892);  // 0x7CEAF4
                sb(v1, a0, 40);
                backedge(ctx);
            } else {
                // 0x004a0614
                charge(ctx, 4);
                a2 = t1 & 0x8;
                v1 = 8;
                if (a2 != v1) {
                    // 0x004a0638
                    charge(ctx, 4);
                    sb(t0, a0, 41);
                    lbu(v1, gp, -16892);  // 0x7CEAF4
                    v1 = v1 | 0x14;
                    sb(v1, a0, 40);
                } else {
                    // 0x004a0624
                    charge(ctx, 5);
                    sb(a3, a0, 41);
                    lbu(v1, gp, -16892);  // 0x7CEAF4
                    v1 = v1 | 0x10;
                    sb(v1, a0, 40);
                }
            }
            goto L_004a0648;
        }
    L_004a0670:
        charge(ctx, 6);
        v1 = 3;
        sb(v1, a0, 41);
        lbu(v1, gp, -16892);  // 0x7CEAF4
        v1 = v1 | 0x4;
        sb(v1, a0, 40);
        backedge(ctx);
    }
L_004a0648:
    charge(ctx, 3);
    v1 = 2;
    if (a1 != v1) {
        // 0x004a069c
        charge(ctx, 4);
        lbu(v1, a0, 40);
        v1 = v1 | 0x2;
        sb(v1, a0, 40);
        backedge(ctx);
    }
    // 0x004a0654
    charge(ctx, 2);
    // 0x004a06ac
    charge(ctx, 2);
}

// 0x004A0480 sub_4A0480 -- 332 bytes; leaf frame (no stack)
// sub_4A0480: the instance test of a stock atomic ($a0) for its PipeData ($a1). Geometry flag 0x01000000
// (native data) skips it. objIdentifier = vertex count (meshHeader... +6 u16 of the geometry's mesh data) |
// (flags & 0x9F) << 16 | morph count << 24; objInstance &= ~1; with a resEntry: a different identifier sets 4
// (only the vertex count differs) or 8; the geometry's lock bits (+12) set 8 (all) or 2 | bits << 3; an
// interpolating atomic (+76 flag 1) whose start/end morph targets differ from the resEntry's sets 4.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_4A0480(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::lbu, hg::lh, hg::lhu, hg::lw, hg::si, hg::sll, hg::srl,
          hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    // 0x004a0480
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, a0, 24);
    a2 = 0x1000000;
    lw(a3, v1, 8);
    a2 = a3 & a2;
    if (a2 == 0) {
        // 0x004a0498
        charge(ctx, 18);
        lw(t1, a1, 12);
        a2 = a3 & 0x9F;
        lbu(a3, v1, 24);
        a2 = a2 & 0xFF;
        t0 = sll(a2, 16);
        a2 = si(-2);
        lhu(t1, t1, 6);
        a3 = sll(a3, 24);
        t0 = t1 | t0;
        a3 = a3 | t0;
        sw(a3, a1, 24);
        lw(a3, a1, 20);
        a2 = a3 & a2;
        sw(a2, a1, 20);
        lw(a2, a1, 16);
        lw(a3, a2, 4);
        if (a3 != 0) {
            // 0x004a04e0
            charge(ctx, 5);
            lw(t2, a3, 40);
            a0 = addiu(a0, 76);
            lw(t1, a1, 24);
            a2 = addiu(a3, 24);
            if (t1 != t2) {
                // 0x004a04f4
                charge(ctx, 6);
                t0 = srl(t1, 16);
                a3 = srl(t2, 16);
                t0 = t0 & 0xFF;
                a3 = a3 & 0xFF;
                if (t0 == a3) {
                    // 0x004a050c
                    charge(ctx, 6);
                    t0 = srl(t1, 24);
                    a3 = srl(t2, 24);
                    t0 = t0 & 0xFF;
                    a3 = a3 & 0xFF;
                    if (t0 != a3) {
                        goto L_004a0534;
                    }
                    // 0x004a0524
                    charge(ctx, 4);
                    lw(a3, a1, 20);
                    a3 = a3 | 0x4;
                    sw(a3, a1, 20);
                    goto L_004a0540;
                }
            L_004a0534:
                charge(ctx, 3);
                lw(a3, a1, 20);
                a3 = a3 | 0x8;
                sw(a3, a1, 20);
            }
        L_004a0540:
            charge(ctx, 3);
            lhu(a3, v1, 12);
            if (a3 != 0) {
                // 0x004a054c
                charge(ctx, 3);
                a3 = a3 & 0x1;
                if (a3 == 0) {
                    // 0x004a0568
                    charge(ctx, 8);
                    lw(a3, a1, 20);
                    a3 = a3 | 0x2;
                    sw(a3, a1, 20);
                    lhu(a3, v1, 12);
                    lw(v1, a1, 20);
                    a3 = sll(a3, 3);
                    v1 = v1 | a3;
                    sw(v1, a1, 20);
                } else {
                    // 0x004a0558
                    charge(ctx, 4);
                    lw(v1, a1, 20);
                    v1 = v1 | 0x8;
                    sw(v1, a1, 20);
                }
            }
            // 0x004a0588
            charge(ctx, 4);
            lw(v1, a0, 0);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                // 0x004a0598
                charge(ctx, 4);
                lw(a3, a2, 40);
                lh(v1, a0, 6);
                if (a3 == v1) {
                    // 0x004a05a8
                    charge(ctx, 4);
                    lw(a2, a2, 36);
                    lh(v1, a0, 4);
                    if (a2 != v1) {
                        goto L_004a05b8;
                    }
                    // 0x004a05c4 (the shared epilogue, written out on this path)
                    charge(ctx, 2);
                    return;
                }
            L_004a05b8:
                charge(ctx, 3);
                lw(v1, a1, 20);
                v1 = v1 | 0x4;
                sw(v1, a1, 20);
            }
        }
    }
    // 0x004a05c4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0049FF10 sub_49FF10 -- 1308 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_49FF10: one light ($a0) into the block; $a1 = the inverse LTM of the object (0 -> identity), $f12 / $f13
// = its scale / inverse scale.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_49FF10(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq, hg::lw,
          hg::lwc1, hg::sd, hg::sltiu, hg::sq, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10}, f12{ctx, 12}, f13{ctx, 13};
    // 0x0049ff10
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    lbu(s2, a0, 1);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lw(v1, gp, -17520);  // 0x7CE880
    lw(a0, a0, 4);
    at = sltiu(v1, 124);
    s0 = addiu(s1, 24);
    if (at != 0) {
        // 0x0049ff40
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x0049ff48
            charge(ctx, 2);
            if (a1 == 0) {
                // 0x004a02fc
                charge(ctx, 67);
                lw(a1, gp, -17516);  // 0x7CE884
                v1 = 0x3F800000;
                sw(v1, a1, 0);
                lw(a2, gp, -17516);  // 0x7CE884
                a1 = addiu(a2, 4);
                sw(a1, gp, -17516);  // 0x7CE884
                sw(zero, a2, 4);
                lw(a2, gp, -17516);  // 0x7CE884
                a1 = addiu(a2, 4);
                sw(a1, gp, -17516);  // 0x7CE884
                sw(zero, a2, 4);
                lw(a2, gp, -17516);  // 0x7CE884
                a1 = addiu(a2, 4);
                sw(a1, gp, -17516);  // 0x7CE884
                swc1(f12, a2, 4);
                lw(a2, gp, -17516);  // 0x7CE884
                a1 = addiu(a2, 4);
                sw(a1, gp, -17516);  // 0x7CE884
                sw(zero, a2, 4);
                lw(a2, gp, -17516);  // 0x7CE884
                a1 = addiu(a2, 4);
                sw(a1, gp, -17516);  // 0x7CE884
                sw(v1, a2, 4);
                lw(a2, gp, -17516);  // 0x7CE884
                a1 = addiu(a2, 4);
                sw(a1, gp, -17516);  // 0x7CE884
                sw(zero, a2, 4);
                lw(a2, gp, -17516);  // 0x7CE884
                a1 = addiu(a2, 4);
                sw(a1, gp, -17516);  // 0x7CE884
                swc1(f12, a2, 4);
                lw(a2, gp, -17516);  // 0x7CE884
                a1 = addiu(a2, 4);
                sw(a1, gp, -17516);  // 0x7CE884
                sw(zero, a2, 4);
                lw(a2, gp, -17516);  // 0x7CE884
                a1 = addiu(a2, 4);
                sw(a1, gp, -17516);  // 0x7CE884
                sw(zero, a2, 4);
                lw(a2, gp, -17516);  // 0x7CE884
                a1 = addiu(a2, 4);
                sw(a1, gp, -17516);  // 0x7CE884
                sw(v1, a2, 4);
                lw(a1, gp, -17516);  // 0x7CE884
                v1 = addiu(a1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                swc1(f12, a1, 4);
                lw(a1, gp, -17516);  // 0x7CE884
                v1 = addiu(a1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                sw(zero, a1, 4);
                lw(a1, gp, -17516);  // 0x7CE884
                v1 = addiu(a1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                sw(zero, a1, 4);
                lw(a1, gp, -17516);  // 0x7CE884
                v1 = addiu(a1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                sw(zero, a1, 4);
                lw(a1, gp, -17516);  // 0x7CE884
                v1 = addiu(a1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                swc1(f13, a1, 4);
                lw(v1, gp, -17516);  // 0x7CE884
                v1 = addiu(v1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                backedge(ctx);
            } else {
                // 0x0049ff50
                charge(ctx, 77);
                lwc1(f0, a1, 0);
                lw(v1, gp, -17516);  // 0x7CE884
                lwc1(f10, a1, 4);
                lwc1(f9, a1, 8);
                lwc1(f8, a1, 16);
                lwc1(f7, a1, 20);
                lwc1(f6, a1, 24);
                swc1(f0, v1, 0);
                lw(a2, gp, -17516);  // 0x7CE884
                lwc1(f5, a1, 32);
                lwc1(f4, a1, 36);
                lwc1(f3, a1, 40);
                lwc1(f2, a1, 48);
                lwc1(f1, a1, 52);
                lwc1(f0, a1, 56);
                v1 = addiu(a2, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                swc1(f10, a2, 4);
                lw(a1, gp, -17516);  // 0x7CE884
                v1 = addiu(a1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                swc1(f9, a1, 4);
                lw(a1, gp, -17516);  // 0x7CE884
                v1 = addiu(a1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                swc1(f12, a1, 4);
                lw(a1, gp, -17516);  // 0x7CE884
                v1 = addiu(a1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                swc1(f8, a1, 4);
                lw(a1, gp, -17516);  // 0x7CE884
                v1 = addiu(a1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                swc1(f7, a1, 4);
                lw(a1, gp, -17516);  // 0x7CE884
                v1 = addiu(a1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                swc1(f6, a1, 4);
                lw(a1, gp, -17516);  // 0x7CE884
                v1 = addiu(a1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                swc1(f12, a1, 4);
                lw(a1, gp, -17516);  // 0x7CE884
                v1 = addiu(a1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                swc1(f5, a1, 4);
                lw(a1, gp, -17516);  // 0x7CE884
                v1 = addiu(a1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                swc1(f4, a1, 4);
                lw(a1, gp, -17516);  // 0x7CE884
                v1 = addiu(a1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                swc1(f3, a1, 4);
                lw(a1, gp, -17516);  // 0x7CE884
                v1 = addiu(a1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                swc1(f12, a1, 4);
                lw(a1, gp, -17516);  // 0x7CE884
                v1 = addiu(a1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                swc1(f2, a1, 4);
                lw(a1, gp, -17516);  // 0x7CE884
                v1 = addiu(a1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                swc1(f1, a1, 4);
                lw(a1, gp, -17516);  // 0x7CE884
                v1 = addiu(a1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                swc1(f0, a1, 4);
                lw(a1, gp, -17516);  // 0x7CE884
                v1 = addiu(a1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                swc1(f13, a1, 4);
                lw(v1, gp, -17516);  // 0x7CE884
                v1 = addiu(v1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
            }
            // 0x004a0084
            charge(ctx, 3);
            lw(v1, gp, -17520);  // 0x7CE880
            v1 = addiu(v1, 4);
            sw(v1, gp, -17520);  // 0x7CE880
        }
        // 0x004a0090
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x004a0408
            charge(ctx, 3);
            a0 = 0;
            v1 = 0;
            backedge(ctx);
        } else {
            // 0x004a0098
            charge(ctx, 4);
            jal(ctx, 0x4A0098u, gen::fn_sub_4CB2F0_004cb2f0);
            v1 = addiu(v0, 32);
            a0 = addiu(v0, 48);
        }
        // 0x004a00a8
        charge(ctx, 12);
        lwc1(f2, s0, 0);
        lw(a1, gp, -17516);  // 0x7CE884
        lwc1(f1, s0, 4);
        lwc1(f0, s0, 8);
        swc1(f2, a1, 0);
        lw(a1, gp, -17516);  // 0x7CE884
        swc1(f1, a1, 4);
        lw(a1, gp, -17516);  // 0x7CE884
        swc1(f0, a1, 8);
        lw(a1, gp, -17516);  // 0x7CE884
        sw(s2, a1, 12);
        if (s2 == 0) {
            goto L_004a0414;
        }
        // 0x004a00d8
        charge(ctx, 3);
        a1 = 130;
        if (s2 != a1) {
            // 0x004a00e4
            charge(ctx, 3);
            a1 = 129;
            if (s2 == a1) {
                goto L_004a0224;
            }
            // 0x004a00f0
            charge(ctx, 3);
            a1 = 128;
            if (s2 == a1) {
                // 0x004a01ac
                charge(ctx, 30);
                lw(v1, gp, -17516);  // 0x7CE884
                lwc1(f0, s1, 20);
                v1 = addiu(v1, 16);
                sw(v1, gp, -17516);  // 0x7CE884
                lwc1(f1, a0, 0);
                lw(v1, gp, -17516);  // 0x7CE884
                swc1(f1, v1, 0);
                lw(v1, gp, -17516);  // 0x7CE884
                v1 = addiu(v1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                lwc1(f1, a0, 4);
                lw(v1, gp, -17516);  // 0x7CE884
                swc1(f1, v1, 0);
                lw(v1, gp, -17516);  // 0x7CE884
                v1 = addiu(v1, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                lwc1(f1, a0, 8);
                lw(v1, gp, -17516);  // 0x7CE884
                swc1(f1, v1, 0);
                lw(a0, gp, -17516);  // 0x7CE884
                v1 = addiu(a0, 4);
                sw(v1, gp, -17516);  // 0x7CE884
                swc1(f0, a0, 4);
                lw(a0, gp, -17516);  // 0x7CE884
                lw(v1, gp, -17520);  // 0x7CE880
                a0 = addiu(a0, 4);
                v1 = addiu(v1, 2);
                sw(a0, gp, -17516);  // 0x7CE884
                sw(v1, gp, -17520);  // 0x7CE880
            } else {
                // 0x004a00fc
                charge(ctx, 3);
                a0 = 2;
                if (s2 == a0) {
                    // 0x004a0190
                    charge(ctx, 7);
                    lw(a0, gp, -17516);  // 0x7CE884
                    lw(v1, gp, -17520);  // 0x7CE880
                    a0 = addiu(a0, 16);
                    v1 = addiu(v1, 1);
                    sw(a0, gp, -17516);  // 0x7CE884
                    sw(v1, gp, -17520);  // 0x7CE880
                } else {
                    // 0x004a0108
                    charge(ctx, 3);
                    a0 = 1;
                    if (s2 == a0) {
                        // 0x004a011c
                        charge(ctx, 29);
                        lw(a0, gp, -17516);  // 0x7CE884
                        a0 = addiu(a0, 16);
                        sw(a0, gp, -17516);  // 0x7CE884
                        lwc1(f0, v1, 0);
                        lw(a0, gp, -17516);  // 0x7CE884
                        swc1(f0, a0, 0);
                        lw(a0, gp, -17516);  // 0x7CE884
                        a0 = addiu(a0, 4);
                        sw(a0, gp, -17516);  // 0x7CE884
                        lwc1(f0, v1, 4);
                        lw(a0, gp, -17516);  // 0x7CE884
                        swc1(f0, a0, 0);
                        lw(a0, gp, -17516);  // 0x7CE884
                        a0 = addiu(a0, 4);
                        sw(a0, gp, -17516);  // 0x7CE884
                        lwc1(f0, v1, 8);
                        lw(v1, gp, -17516);  // 0x7CE884
                        swc1(f0, v1, 0);
                        lw(a0, gp, -17516);  // 0x7CE884
                        v1 = addiu(a0, 4);
                        sw(v1, gp, -17516);  // 0x7CE884
                        sw(zero, a0, 4);
                        lw(a0, gp, -17516);  // 0x7CE884
                        lw(v1, gp, -17520);  // 0x7CE880
                        a0 = addiu(a0, 4);
                        v1 = addiu(v1, 2);
                        sw(a0, gp, -17516);  // 0x7CE884
                        sw(v1, gp, -17520);  // 0x7CE880
                    } else {
                        // 0x004a0114
                        charge(ctx, 2);
                    }
                }
            }
            goto L_004a02f4;
        }
    L_004a0224:
        charge(ctx, 52);
        lw(a1, gp, -17516);  // 0x7CE884
        lwc1(f1, s1, 20);
        lwc1(f0, s1, 40);
        a1 = addiu(a1, 16);
        sw(a1, gp, -17516);  // 0x7CE884
        lwc1(f2, a0, 0);
        lw(a1, gp, -17516);  // 0x7CE884
        swc1(f2, a1, 0);
        lw(a1, gp, -17516);  // 0x7CE884
        a1 = addiu(a1, 4);
        sw(a1, gp, -17516);  // 0x7CE884
        lwc1(f2, a0, 4);
        lw(a1, gp, -17516);  // 0x7CE884
        swc1(f2, a1, 0);
        lw(a1, gp, -17516);  // 0x7CE884
        a1 = addiu(a1, 4);
        sw(a1, gp, -17516);  // 0x7CE884
        lwc1(f2, a0, 8);
        lw(a0, gp, -17516);  // 0x7CE884
        swc1(f2, a0, 0);
        lw(a1, gp, -17516);  // 0x7CE884
        a0 = addiu(a1, 4);
        sw(a0, gp, -17516);  // 0x7CE884
        swc1(f1, a1, 4);
        lw(a0, gp, -17516);  // 0x7CE884
        a0 = addiu(a0, 4);
        sw(a0, gp, -17516);  // 0x7CE884
        lwc1(f1, v1, 0);
        lw(a0, gp, -17516);  // 0x7CE884
        swc1(f1, a0, 0);
        lw(a0, gp, -17516);  // 0x7CE884
        a0 = addiu(a0, 4);
        sw(a0, gp, -17516);  // 0x7CE884
        lwc1(f1, v1, 4);
        lw(a0, gp, -17516);  // 0x7CE884
        swc1(f1, a0, 0);
        lw(a0, gp, -17516);  // 0x7CE884
        a0 = addiu(a0, 4);
        sw(a0, gp, -17516);  // 0x7CE884
        lwc1(f1, v1, 8);
        lw(v1, gp, -17516);  // 0x7CE884
        swc1(f1, v1, 0);
        lw(a0, gp, -17516);  // 0x7CE884
        v1 = addiu(a0, 4);
        sw(v1, gp, -17516);  // 0x7CE884
        swc1(f0, a0, 4);
        lw(a0, gp, -17516);  // 0x7CE884
        lw(v1, gp, -17520);  // 0x7CE880
        a0 = addiu(a0, 4);
        v1 = addiu(v1, 3);
        sw(a0, gp, -17516);  // 0x7CE884
        sw(v1, gp, -17520);  // 0x7CE880
    L_004a02f4:
        charge(ctx, 2);
        ld(ra, sp, 0x30);
        // 0x004a0418 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_004a0414:
    charge(ctx, 1);
    ld(ra, sp, 0x30);
    // 0x004a0418 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004A0430 sub_4A0430 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4A0430: the light iterator's callback (worldForAllLights for the world lights, and sub_46EB90's sector ties):
// lights flagged 1 (light atomics) go into the block with the frame record ($a1: +16 inverse LTM, +80 scale,
// +84 inverse scale). Returns the light.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_4A0430(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq,
          hg::lwc1, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13};
    // 0x004a0430
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = a1;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lbu(v0, a0, 2);
    v0 = v0 & 0x1;
    s0 = a0;
    if (v0 != 0) {
        // 0x004a0458
        charge(ctx, 6);
        lwc1(f12, v1, 80);
        lwc1(f13, v1, 84);
        a1 = addiu(v1, 16);
        jal(ctx, 0x4A0460u, gen::fn_sub_49FF10_0049ff10);
        backedge(ctx);
    }
    // 0x004a0450
    charge(ctx, 2);
    v0 = s0;
    // 0x004a0470
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004A06C0 sub_4A06C0 -- 560 bytes; frame 0xE0: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4A06C0: the lights of an atomic (pd +8) whose geometry is lit (flags 0x20). Frame record on the stack at
// sp+128: +0 the first mesh's surface properties (material + 12), +16 the inverse LTM, +80 the scale
// |at| (1 for an orthonormal LTM, flags & 3 == 3), +84 its inverse. The world lights go through worldForAllLights with
// sub_4A0430; then every light tied to each world sector the atomic touches (atomic +100 ties -> sector +64
// light ties), once per frame stamp (u16 0x96007A vs light +60), flagged 1, whose radius reaches the
// atomic's bounding sphere: (r_light + r_sphere)^2 > |centre - light position|^2.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_4A06C0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::c_le_s, hg::c_lt_s, hg::call,
          hg::charge, hg::cond, hg::div_s, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lhu, hg::link, hg::lq, hg::lw,
          hg::lwc1, hg::madd_s, hg::madda_s, hg::mtc1, hg::mul_s, hg::mula_s, hg::sd, hg::sh, hg::sq, hg::sqrt_s,
          hg::sub_s, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f12{ctx, 12}, f13{ctx, 13};
    // 0x004a06c0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s5, a0, 8);
    lw(s0, s5, 24);
    lw(v1, s0, 8);
    v1 = v1 & 0x20;
    if (v1 != 0) {
        // 0x004a06fc
        charge(ctx, 16);
        s2 = 0x960000;
        s2 = addiu(s2, 122);  // &0x96007A
        lhu(v0, s2, 0);  // 0x96007A
        v0 = addiu(v0, 1);
        sh(v0, s2, 0);  // 0x96007A
        link(ctx, 0x4A0710u);  // $ra first: the delay slot below depends on it
        lw(a0, s5, 4);
        call(ctx, gen::fn_sub_4CB2F0_004cb2f0);
        s1 = v0;
        a0 = addiu(sp, 0x90);
        a1 = s1;
        jal(ctx, 0x4A0720u, gen::fn_sub_4C32A0_004c32a0);
        lw(v1, s1, 12);
        v0 = 3;
        v1 = v1 & 0x3;
        if (v1 != v0) {
            // 0x004a074c
            charge(ctx, 12);
            lwc1(f3, sp, 0xB4);
            lwc1(f2, sp, 0xB0);
            lwc1(f0, sp, 0xB8);
            mtc1(zero, f1);
            mula_s(f3, f3);
            madda_s(f2, f2);
            madd_s(f0, f0, f0);
            sqrt_s(f2, f0);
            c_le_s(f2, f1);
            swc1(f2, sp, 0xD0);
            if (!cond(ctx)) {
                // 0x004a077c
                charge(ctx, 7);
                v0 = 0x3F800000;
                mtc1(v0, f0);
                div_s(f2, f0, f2);
            }
            // 0x004a0798
            charge(ctx, 1);
            swc1(f2, sp, 0xD4);
        } else {
            // 0x004a073c
            charge(ctx, 4);
            v0 = 0x3F800000;
            sw(v0, sp, 0xD0);
            sw(v0, sp, 0xD4);
        }
        // 0x004a079c
        charge(ctx, 14);
        lw(v1, s0, 84);
        a0 = 0x4A0000;
        a0 = addiu(a0, 1072);  // &sub_4A0430
        a1 = addiu(sp, 0x80);
        lw(v0, v1, 12);
        v0 = addu(v0, v1);
        lw(v0, v0, 24);
        v0 = addiu(v0, 12);
        link(ctx, 0x4A07BCu);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x80);
        call(ctx, gen::fn_worldForAllLights_00499c20);
        lw(s4, s5, 100);
        s6 = addiu(s5, 100);
        if (s4 != s6) {
            for (;;) {
                // 0x004a07d4
                charge(ctx, 5);
                lw(v1, s4, 8);
                lw(s3, v1, 64);
                s1 = addiu(v1, 64);
                if (s3 != s1) {
                    for (;;) {
                        // 0x004a07e8
                        charge(ctx, 3);
                        lw(a2, s3, 8);
                        if (a2 != 0) {
                            // 0x004a07f4
                            charge(ctx, 4);
                            lhu(a1, s2, 0);
                            lhu(v1, a2, 60);
                            a0 = addiu(a2, 60);
                            if (v1 != a1) {
                                // 0x004a0804
                                charge(ctx, 4);
                                lbu(v1, a2, 2);
                                v1 = v1 & 0x1;
                                if (v1 != 0) {
                                    // 0x004a0814
                                    charge(ctx, 27);
                                    sh(a1, a0, 0);
                                    lw(v0, s3, 8);
                                    link(ctx, 0x4A081Cu);  // $ra first: the delay slot below depends on it
                                    lw(a0, v0, 4);
                                    call(ctx, gen::fn_sub_4CB2F0_004cb2f0);
                                    s0 = addiu(v0, 48);
                                    a0 = s5;
                                    jal(ctx, 0x4A0828u, gen::fn_atomicGetWorldBoundingSphere_004912b0);
                                    lwc1(f4, v0, 4);
                                    lw(a0, s3, 8);
                                    lwc1(f3, s0, 4);
                                    lwc1(f6, v0, 0);
                                    lwc1(f5, s0, 0);
                                    lwc1(f0, s0, 8);
                                    lwc1(f1, v0, 8);
                                    lwc1(f2, v0, 12);
                                    sub_s(f3, f4, f3);
                                    sub_s(f5, f6, f5);
                                    mula_s(f3, f3);
                                    sub_s(f0, f1, f0);
                                    madda_s(f5, f5);
                                    madd_s(f1, f0, f0);
                                    lwc1(f0, a0, 20);
                                    add_s(f0, f2, f0);
                                    mul_s(f0, f0, f0);
                                    c_lt_s(f1, f0);
                                    if (cond(ctx)) {
                                        // 0x004a0880
                                        charge(ctx, 4);
                                        lbu(v1, a0, 2);
                                        v1 = v1 & 0x1;
                                        if (v1 != 0) {
                                            // 0x004a0890
                                            charge(ctx, 6);
                                            v0 = addiu(sp, 0x80);
                                            lwc1(f12, v0, 80);
                                            lwc1(f13, v0, 84);
                                            a1 = addiu(v0, 16);
                                            jal(ctx, 0x4A089Cu, gen::fn_sub_49FF10_0049ff10);
                                        }
                                    }
                                }
                            }
                        }
                        // 0x004a08a8
                        charge(ctx, 3);
                        lw(s3, s3, 0);
                        if (s3 == s1) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004a08b4
                    charge(ctx, 1);
                }
                // 0x004a08b8
                charge(ctx, 3);
                lw(s4, s4, 0);
                if (s4 == s6) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004a08c4
            charge(ctx, 1);
        }
    }
    // 0x004a08c8 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xE0);
}

// 0x004A09D0 sub_4A09D0 -- 588 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4A09D0: the stock atomic set-up callback ($a0 = PipeData, $a1 = the node's matrix reference: *$a1 receives
// the object matrix, the atomic's LTM x the current camera's view matrix (camera +32)).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_4A09D0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::c_le_s, hg::call, hg::charge, hg::cond,
          hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lhu, hg::link, hg::lq, hg::lw, hg::lwc1,
          hg::madd_s, hg::madda_s, hg::mul_s, hg::mula_s, hg::neg_s, hg::sb, hg::sd, hg::sh, hg::si, hg::slti,
          hg::sltu, hg::sq, hg::sub_s, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7};
    // 0x004a09d0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(s0, a0, 8);
    a1 = 1;
    lw(a2, s0, 24);
    lw(v0, a2, 84);
    sw(v0, a0, 12);
    lw(v0, a2, 24);
    s2 = a0;
    if (v0 != a1) {
        // 0x004a0b94
        charge(ctx, 5);
        lw(v0, gp, -17508);  // 0x7CE88C
        a0 = addu(s0, v0);
        lw(v0, a0, 0);
        a3 = 0;
        if (v0 != 0) {
            // 0x004a0ba8
            charge(ctx, 5);
            lw(v1, a2, 84);
            lw(v0, v0, 0);
            lhu(v1, v1, 4);
            if (v1 == v0) {
                // 0x004a0bbc
                charge(ctx, 1);
                a3 = a1;
            }
        }
        // 0x004a0bc0
        charge(ctx, 2);
        if (a3 == 0) {
            // 0x004a0bd0
            charge(ctx, 5);
            lw(v0, a2, 84);
            link(ctx, 0x4A0BD4u);  // $ra first: the delay slot below depends on it
            lhu(a1, v0, 4);
            call(ctx, gen::fn_sub_49E5A0_0049e5a0);
            a0 = v0;
            lw(v0, a0, 0);
        } else {
            // 0x004a0bc8
            charge(ctx, 2);
            lw(v0, a0, 0);
        }
        // 0x004a0be4
        charge(ctx, 2);
        sw(v0, s2, 16);
        backedge(ctx);
    } else {
        // 0x004a0a0c
        charge(ctx, 5);
        lw(v0, gp, -17504);  // 0x7CE890
        a0 = addu(a2, v0);
        lw(v0, a0, 0);
        a3 = 0;
        if (v0 != 0) {
            // 0x004a0a20
            charge(ctx, 5);
            lw(v1, a2, 84);
            lw(v0, v0, 0);
            lhu(v1, v1, 4);
            if (v1 == v0) {
                // 0x004a0a34
                charge(ctx, 1);
                a3 = a1;
            }
        }
        // 0x004a0a38
        charge(ctx, 2);
        if (a3 == 0) {
            // 0x004a0a48
            charge(ctx, 5);
            lw(v0, a2, 84);
            link(ctx, 0x4A0A4Cu);  // $ra first: the delay slot below depends on it
            lhu(a1, v0, 4);
            call(ctx, gen::fn_sub_49E5A0_0049e5a0);
            a0 = v0;
            lw(v0, a0, 0);
        } else {
            // 0x004a0a40
            charge(ctx, 2);
            lw(v0, a0, 0);
        }
        // 0x004a0a5c
        charge(ctx, 1);
        sw(v0, s2, 16);
    }
    // 0x004a0a60
    charge(ctx, 7);
    lw(v0, s0, 24);
    lw(v0, v0, 24);
    sw(v0, s2, 32);
    lw(v0, s2, 32);
    at = slti(v0, 2);
    if (at == 0) {
        // 0x004a0bec
        charge(ctx, 5);
        lwc1(f1, s0, 88);
        lwc1(f0, s0, 92);
        mul_s(f0, f1, f0);
        swc1(f0, s2, 28);
        backedge(ctx);
    }
    // 0x004a0a7c
    charge(ctx, 29);
    a0 = s0;
    a1 = s2;
    jal(ctx, 0x4A0A80u, gen::fn_sub_4A0480_004a0480);
    lw(a0, s0, 24);
    v1 = si(-2);
    v0 = 0x960000;
    sh(zero, a0, 12);
    lw(a0, s0, 76);
    v1 = a0 & v1;
    sw(v1, s0, 76);
    lw(v0, v0, 112);  // 0x960070
    lw(a0, s0, 4);
    s3 = addiu(v0, 32);
    jal(ctx, 0x4A0AACu, gen::fn_sub_4CB2F0_004cb2f0);
    lw(a0, s1, 0);
    a1 = v0;
    a2 = s3;
    jal(ctx, 0x4A0ABCu, gen::fn_sub_4C2F30_004c2f30);
    a0 = s0;
    s1 = 2;
    jal(ctx, 0x4A0AC8u, gen::fn_atomicGetWorldBoundingSphere_004912b0);
    v1 = 0x960000;
    lw(a0, gp, -16972);  // 0x7CEAA4
    lw(a1, v1, 112);  // 0x960070
    v1 = 6;
    a0 = addu(a1, a0);
    a2 = addiu(v1, -1);
    a0 = addiu(a0, 96);
    if (v1 != 0) {
        // 0x004a0af0
        charge(ctx, 6);
        lwc1(f0, v0, 12);
        v1 = 1;
        lwc1(f7, v0, 4);
        lwc1(f6, v0, 0);
        lwc1(f5, v0, 8);
        neg_s(f4, f0);
        for (;;) {
            // 0x004a0b08
            charge(ctx, 11);
            lwc1(f1, a0, 4);
            lwc1(f2, a0, 0);
            lwc1(f3, a0, 8);
            lwc1(f0, a0, 12);
            mula_s(f7, f1);
            madda_s(f6, f2);
            madd_s(f1, f5, f3);
            sub_s(f0, f1, f0);
            c_le_s(f0, f4);
            v0 = v1;
            if (cond(ctx)) {
                // 0x004a0b34
                charge(ctx, 1);
                v0 = 0;
            }
            // 0x004a0b38
            charge(ctx, 3);
            v0 = v0 ^ 0x1;
            if (v0 == 0) {
                goto L_004a0b44_14;
            }
            // 0x004a0b4c
            charge(ctx, 4);
            v0 = a2;
            a0 = addiu(a0, 20);
            a2 = addiu(a2, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004a0b5c
        charge(ctx, 1);
    }
L_004a0b60:
    charge(ctx, 13);
    a1 = dsll32(s1, 0);
    a1 = dsra32(a1, 0);
    a0 = s2;
    jal(ctx, 0x4A0B68u, gen::fn_RpAtomicPS2AllPrimTypeTransTypeSetupFunc_004a05d0);
    lw(v0, s0, 24);
    a0 = s2;
    lw(v0, v0, 8);
    v0 = v0 & 0x40;
    v0 = sltu(0, v0);
    link(ctx, 0x4A0B84u);  // $ra first: the delay slot below depends on it
    sb(v0, s2, 42);
    call(ctx, gen::fn_sub_4A06C0_004a06c0);
    v0 = 1;
    // 0x004a0c00
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
    return;
L_004a0b44_14:
    charge(ctx, 2);
    s1 = 1;
    goto L_004a0b60;
}

// 0x0046B510 _rpSkinMatrixUpdating -- 968 bytes; frame 0x130: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// _rpSkinMatrixUpdating [_rpSkinMatrixUpdating]: the palette of a skinned atomic ($a0, skin $a1). Returns the palette.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void _rpSkinMatrixUpdating(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::Vf, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::enter, hg::jal, hg::ld,
          hg::link, hg::lq, hg::lqc2, hg::lw, hg::mult, hg::sd, hg::sll, hg::slt, hg::sltu, hg::sq, hg::sqc2, hg::sw,
          hg::vmadd_bc, hg::vmadda_bc, hg::vmula_bc;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    Vf vf0{ctx, 0}, vf1{ctx, 1}, vf2{ctx, 2}, vf3{ctx, 3}, vf4{ctx, 4}, vf5{ctx, 5}, vf6{ctx, 6}, vf7{ctx, 7}, vf8{ctx, 8}, vf9{ctx, 9}, vf10{ctx, 10}, vf11{ctx, 11}, vf12{ctx, 12}, vf13{ctx, 13}, vf14{ctx, 14}, vf15{ctx, 15}, vf16{ctx, 16};
    // 0x0046b510
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x130);
    v1 = 0x960000;
    sd(ra, sp, 0x60);
    v0 = 0x960000;
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    lw(v1, v1, -8684);  // 0x95DE14
    lw(s1, v0, -8676);  // 0x95DE1C
    v0 = addu(s2, v1);
    lw(s5, v0, 0);
    if (s5 == 0) {
        // 0x0046b844
        charge(ctx, 4);
        lw(a2, a1, 0);
        at = sltu(0, a2);
        t0 = 0;
        if (at != 0) {
            // 0x0046b854
            charge(ctx, 4);
            v0 = 0x20000;
            a3 = s1;
            a1 = 0x3F800000;
            a0 = v0 | 0x3;
            for (;;) {
                // 0x0046b864
                charge(ctx, 19);
                sw(a1, a3, 40);
                t0 = addiu(t0, 1);
                sw(a1, a3, 20);
                v0 = sltu(t0, a2);
                sw(a1, a3, 0);
                sw(zero, a3, 16);
                sw(zero, a3, 8);
                sw(zero, a3, 4);
                sw(zero, a3, 36);
                sw(zero, a3, 32);
                sw(zero, a3, 24);
                sw(zero, a3, 56);
                sw(zero, a3, 52);
                sw(zero, a3, 48);
                lw(v1, a3, 12);
                v1 = v1 | a0;
                sw(v1, a3, 12);
                a3 = addiu(a3, 64);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    } else {
        // 0x0046b554
        charge(ctx, 9);
        lw(s4, s5, 4);
        lw(s3, s5, 8);
        a0 = a1;
        jal(ctx, 0x46B55Cu, gen::fn_sub_48A3E0_0048a3e0);
        lw(v1, s5, 0);
        s0 = v0;
        v0 = v1 & 0x2;
        if (v0 == 0) {
            // 0x0046b6a8
            charge(ctx, 3);
            v0 = v1 & 0x4000;
            if (v0 == 0) {
                // 0x0046b74c
                charge(ctx, 17);
                sw(zero, sp, 0x7C);
                link(ctx, 0x46B750u);  // $ra first: the delay slot below depends on it
                lw(a0, s2, 4);
                call(ctx, gen::fn_sub_4CB2F0_004cb2f0);
                a1 = v0;
                a0 = addiu(sp, 0x70);
                jal(ctx, 0x46B75Cu, gen::fn_sub_4C32A0_004c32a0);
                v1 = addiu(sp, 0x70);
                v0 = 64;
                mult(at, s4, v0);
                a2 = addu(s0, 0);
                a1 = addu(s3, 0);
                a0 = addu(s1, 0);
                lqc2(vf13, v1, 0);
                lqc2(vf14, v1, 16);
                lqc2(vf15, v1, 32);
                lqc2(vf16, v1, 48);
                at = addu(a0, at);
                for (;;) {
                    // 0x0046b790
                    charge(ctx, 43);
                    lqc2(vf1, a2, 0);
                    lqc2(vf2, a2, 16);
                    lqc2(vf3, a2, 32);
                    lqc2(vf4, a2, 48);
                    lqc2(vf5, a1, 0);
                    lqc2(vf6, a1, 16);
                    lqc2(vf7, a1, 32);
                    lqc2(vf8, a1, 48);
                    vmula_bc(0xF, vf5, vf1, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf6, vf1, 1);  // vmadday.xyzw
                    vmadd_bc(0xF, vf9, vf7, vf1, 2);  // vmaddz.xyzw
                    vmula_bc(0xF, vf5, vf2, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf6, vf2, 1);  // vmadday.xyzw
                    vmadd_bc(0xF, vf10, vf7, vf2, 2);  // vmaddz.xyzw
                    vmula_bc(0xF, vf5, vf3, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf6, vf3, 1);  // vmadday.xyzw
                    vmadd_bc(0xF, vf11, vf7, vf3, 2);  // vmaddz.xyzw
                    vmula_bc(0xF, vf5, vf4, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf6, vf4, 1);  // vmadday.xyzw
                    vmadda_bc(0xF, vf7, vf4, 2);  // vmaddaz.xyzw
                    vmadd_bc(0xF, vf12, vf8, vf0, 3);  // vmaddw.xyzw
                    vmula_bc(0xF, vf13, vf9, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf14, vf9, 1);  // vmadday.xyzw
                    vmadd_bc(0xF, vf1, vf15, vf9, 2);  // vmaddz.xyzw
                    vmula_bc(0xF, vf13, vf10, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf14, vf10, 1);  // vmadday.xyzw
                    vmadd_bc(0xF, vf2, vf15, vf10, 2);  // vmaddz.xyzw
                    vmula_bc(0xF, vf13, vf11, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf14, vf11, 1);  // vmadday.xyzw
                    vmadd_bc(0xF, vf3, vf15, vf11, 2);  // vmaddz.xyzw
                    vmula_bc(0xF, vf13, vf12, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf14, vf12, 1);  // vmadday.xyzw
                    vmadda_bc(0xF, vf15, vf12, 2);  // vmaddaz.xyzw
                    vmadd_bc(0xF, vf4, vf16, vf0, 3);  // vmaddw.xyzw
                    sqc2(vf1, a0, 0);
                    sqc2(vf2, a0, 16);
                    sqc2(vf3, a0, 32);
                    sqc2(vf4, a0, 48);
                    a0 = addiu(a0, 64);
                    a2 = addu(a2, v0);
                    a1 = addu(a1, v0);
                    if (at == a0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0046b83c
                charge(ctx, 2);
            } else {
                // 0x0046b6b4
                charge(ctx, 6);
                v0 = 64;
                mult(at, s4, v0);
                a1 = addu(s0, 0);
                a0 = addu(s3, 0);
                v1 = addu(s1, 0);
                at = addu(v1, at);
                for (;;) {
                    // 0x0046b6cc
                    charge(ctx, 30);
                    lqc2(vf1, a1, 0);
                    lqc2(vf2, a1, 16);
                    lqc2(vf3, a1, 32);
                    lqc2(vf4, a1, 48);
                    lqc2(vf5, a0, 0);
                    lqc2(vf6, a0, 16);
                    lqc2(vf7, a0, 32);
                    lqc2(vf8, a0, 48);
                    vmula_bc(0xF, vf5, vf1, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf6, vf1, 1);  // vmadday.xyzw
                    vmadd_bc(0xF, vf9, vf7, vf1, 2);  // vmaddz.xyzw
                    vmula_bc(0xF, vf5, vf2, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf6, vf2, 1);  // vmadday.xyzw
                    vmadd_bc(0xF, vf10, vf7, vf2, 2);  // vmaddz.xyzw
                    vmula_bc(0xF, vf5, vf3, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf6, vf3, 1);  // vmadday.xyzw
                    vmadd_bc(0xF, vf11, vf7, vf3, 2);  // vmaddz.xyzw
                    vmula_bc(0xF, vf5, vf4, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf6, vf4, 1);  // vmadday.xyzw
                    vmadda_bc(0xF, vf7, vf4, 2);  // vmaddaz.xyzw
                    vmadd_bc(0xF, vf12, vf8, vf0, 3);  // vmaddw.xyzw
                    sqc2(vf9, v1, 0);
                    sqc2(vf10, v1, 16);
                    sqc2(vf11, v1, 32);
                    sqc2(vf12, v1, 48);
                    v1 = addiu(v1, 64);
                    a1 = addu(a1, v0);
                    a0 = addu(a0, v0);
                    if (at == v1) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0046b744
                charge(ctx, 2);
            }
        } else {
            // 0x0046b578
            charge(ctx, 11);
            lw(s3, s5, 16);
            sw(zero, sp, 0xFC);
            lw(a0, s2, 4);
            link(ctx, 0x46B584u);  // $ra first: the delay slot below depends on it
            sw(zero, sp, 0xBC);
            call(ctx, gen::fn_sub_4CB2F0_004cb2f0);
            a1 = v0;
            a0 = addiu(sp, 0xF0);
            jal(ctx, 0x46B590u, gen::fn_sub_4C32A0_004c32a0);
            at = slt(0, s4);
            s2 = 0;
            if (at != 0) {
                for (;;) {
                    // 0x0046b5a4
                    charge(ctx, 63);
                    v0 = sll(s2, 4);
                    v0 = addu(s3, v0);
                    link(ctx, 0x46B5ACu);  // $ra first: the delay slot below depends on it
                    lw(a0, v0, 12);
                    call(ctx, gen::fn_sub_4CB2F0_004cb2f0);
                    a1 = sll(s2, 6);
                    a0 = addiu(sp, 0xB0);
                    v1 = addu(s0, a1);
                    lqc2(vf1, v1, 0);
                    lqc2(vf2, v1, 16);
                    lqc2(vf3, v1, 32);
                    lqc2(vf4, v1, 48);
                    lqc2(vf5, v0, 0);
                    lqc2(vf6, v0, 16);
                    lqc2(vf7, v0, 32);
                    lqc2(vf8, v0, 48);
                    vmula_bc(0xF, vf5, vf1, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf6, vf1, 1);  // vmadday.xyzw
                    vmadd_bc(0xF, vf9, vf7, vf1, 2);  // vmaddz.xyzw
                    vmula_bc(0xF, vf5, vf2, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf6, vf2, 1);  // vmadday.xyzw
                    vmadd_bc(0xF, vf10, vf7, vf2, 2);  // vmaddz.xyzw
                    vmula_bc(0xF, vf5, vf3, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf6, vf3, 1);  // vmadday.xyzw
                    vmadd_bc(0xF, vf11, vf7, vf3, 2);  // vmaddz.xyzw
                    vmula_bc(0xF, vf5, vf4, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf6, vf4, 1);  // vmadday.xyzw
                    vmadda_bc(0xF, vf7, vf4, 2);  // vmaddaz.xyzw
                    vmadd_bc(0xF, vf12, vf8, vf0, 3);  // vmaddw.xyzw
                    sqc2(vf9, a0, 0);
                    sqc2(vf10, a0, 16);
                    sqc2(vf11, a0, 32);
                    sqc2(vf12, a0, 48);
                    v0 = addu(s1, a1);
                    v1 = addiu(sp, 0xF0);
                    lqc2(vf1, a0, 0);
                    lqc2(vf2, a0, 16);
                    lqc2(vf3, a0, 32);
                    lqc2(vf4, a0, 48);
                    lqc2(vf5, v1, 0);
                    lqc2(vf6, v1, 16);
                    lqc2(vf7, v1, 32);
                    lqc2(vf8, v1, 48);
                    vmula_bc(0xF, vf5, vf1, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf6, vf1, 1);  // vmadday.xyzw
                    vmadd_bc(0xF, vf9, vf7, vf1, 2);  // vmaddz.xyzw
                    vmula_bc(0xF, vf5, vf2, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf6, vf2, 1);  // vmadday.xyzw
                    vmadd_bc(0xF, vf10, vf7, vf2, 2);  // vmaddz.xyzw
                    vmula_bc(0xF, vf5, vf3, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf6, vf3, 1);  // vmadday.xyzw
                    vmadd_bc(0xF, vf11, vf7, vf3, 2);  // vmaddz.xyzw
                    vmula_bc(0xF, vf5, vf4, 0);  // vmulax.xyzw
                    vmadda_bc(0xF, vf6, vf4, 1);  // vmadday.xyzw
                    vmadda_bc(0xF, vf7, vf4, 2);  // vmaddaz.xyzw
                    vmadd_bc(0xF, vf12, vf8, vf0, 3);  // vmaddw.xyzw
                    sqc2(vf9, v0, 0);
                    sqc2(vf10, v0, 16);
                    sqc2(vf11, v0, 32);
                    sqc2(vf12, v0, 48);
                    s2 = addiu(s2, 1);
                    v0 = slt(s2, s4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0046b6a0
                charge(ctx, 2);
            }
        }
    }
    // 0x0046b8b0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    v0 = s1;
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x130);
}

// 0x0046B8E0 sub_46B8E0 -- 456 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_46B8E0: the palette of one mesh of a partitioned skin ($a0 = PipeData). The partition record (0x95DE38):
// +0 bones per upload, +12 the bone -> palette slot map, +16 two bytes per mesh {first range, range count},
// +20 two bytes per range {first bone, bone count}. A cnt tag over 4 x bones + 1 quadwords, STCYCL 1,1 +
// UNPACK V4-32 of 4 x bones to VU1 0x2BC, then each bone's matrix at its slot. Returns 1.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_46B8E0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsrl32, hg::enter, hg::jal,
          hg::lbu, hg::ld, hg::lq, hg::lw, hg::mfhi, hg::mult, hg::pcpyld, hg::ppacw, hg::sd, hg::sll, hg::sltu,
          hg::sq, hg::sra, hg::srl, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046b8e0
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    v0 = 0x960000;
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s1, v0, -8648);  // 0x95DE38
    lw(a1, a0, 12);
    lw(v1, a0, 44);
    v0 = 0x2AAA0000;
    v0 = v0 | 0xAAAB;
    a0 = addiu(a1, 16);
    v1 = subu(v1, a0);
    mult(zero, v0, v1);
    v1 = srl(v1, 31);
    mfhi(v0);
    lw(s0, s1, 0);
    a0 = 0;
    v0 = sra(v0, 1);
    s3 = addu(v0, v1);
    s2 = sll(s0, 2);
    s4 = addiu(s2, 1);
    a1 = addiu(s4, 2);
    jal(ctx, 0x46B944u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    if (s4 != 0) {
        // 0x0046ba38
        charge(ctx, 12);
        v1 = dsll32(s4, 0);
        v1 = dsrl32(v1, 0);
        v0 = 0x10000000;
        v1 = v1 | v0;
        a0 = 0;
        lw(v0, gp, -17148);  // 0x7CE9F4
        pcpyld(v1, a0, v1);
        sq(v1, v0, 0);
        lw(v0, gp, -17148);  // 0x7CE9F4
        v0 = addiu(v0, 16);
        sw(v0, gp, -17148);  // 0x7CE9F4
        backedge(ctx);
    }
    // 0x0046b954
    charge(ctx, 24);
    v0 = s2 & 0xFF;
    lw(a1, s1, 16);
    a0 = sll(v0, 16);
    a2 = sll(s3, 1);
    v0 = 0x6C000000;
    lw(t0, gp, -17148);  // 0x7CE9F4
    v1 = v0 | 0x2BC;
    v0 = 0x1000000;
    v1 = a0 | v1;
    v0 = v0 | 0x101;  // &0x1000101
    a0 = 0;
    ppacw(a3, v1, v0);
    v1 = addu(a1, a2);
    a1 = 0;
    lbu(v0, v1, 0);
    ppacw(a0, a1, a0);
    lbu(a1, v1, 1);
    ppacw(v1, a3, a0);
    sq(v1, t0, 0);
    a0 = addiu(t0, 16);
    at = sltu(0, a1);
    a3 = sll(v0, 1);
    t0 = 0;
    if (at != 0) {
        // 0x0046b9b4
        charge(ctx, 1);
        t1 = 0x960000;
        for (;;) {
            // 0x0046b9b8
            charge(ctx, 7);
            lw(v0, s1, 20);
            v0 = addu(v0, a3);
            lbu(v1, v0, 1);
            lbu(v0, v0, 0);
            at = sltu(0, v1);
            a2 = 0;
            if (at == 0) {
                // 0x0046ba68
                charge(ctx, 1);
                t0 = addiu(t0, 1);
            } else {
                // 0x0046b9d4
                charge(ctx, 1);
                for (;;) {
                    // 0x0046b9d8
                    charge(ctx, 21);
                    lw(t3, t1, -8676);
                    t2 = addu(v0, a2);
                    t4 = sll(t2, 6);
                    lw(t2, s1, 12);
                    t3 = addu(t3, t4);
                    lq(t7, t3, 16);
                    lq(t6, t3, 32);
                    lq(t5, t3, 48);
                    t2 = addu(v0, t2);
                    t2 = addu(t2, a2);
                    lbu(t4, t2, 0);
                    a2 = addiu(a2, 1);
                    lq(t3, t3, 0);
                    t4 = sll(t4, 6);
                    t2 = sltu(a2, v1);
                    t4 = addu(a0, t4);
                    sq(t3, t4, 0);
                    sq(t7, t4, 16);
                    sq(t6, t4, 32);
                    sq(t5, t4, 48);
                    if (t2 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0046ba2c
                charge(ctx, 2);
                t0 = addiu(t0, 1);
            }
            // 0x0046ba6c
            charge(ctx, 3);
            v0 = sltu(t0, a1);
            a3 = addiu(a3, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0046ba78 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    v0 = sll(s0, 6);
    v1 = addu(a0, v0);
    sw(v1, gp, -17148);  // 0x7CE9F4
    if (g_observer && g_observer->skin) g_observer->skin(ctx, SkinPalette{a0.u(), s0.u()});
    v0 = 1;
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0046EB90 sub_46EB90 -- 2148 bytes; frame 0x120: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_46EB90: the skinned atomic's set-up callback ($a0 = PipeData, $a1 = the matrix reference): sub_4A09D0's
// steps with the instance test, the prim / transType setup and the lights inlined (the sector lights through
// sub_4A0430), the lighting hook (0x95DE34) instead when set, then the palette (_rpSkinMatrixUpdating) uploaded whole: a cnt
// tag + STCYCL 1,1 / UNPACK V4-32 of 4 x bones quadwords to VU1 0x2BC and the matrices. Returns 1, 0 for a
// geometry without meshes.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_46EB90(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::c_le_s, hg::c_lt_s, hg::call,
          hg::charge, hg::cond, hg::div_s, hg::dsll32, hg::dsra32, hg::dsrl32, hg::enter, hg::i64, hg::jal, hg::jalr,
          hg::lbu, hg::ld, hg::lh, hg::lhu, hg::link, hg::lq, hg::lw, hg::lwc1, hg::madd_s, hg::madda_s, hg::mtc1,
          hg::mul_s, hg::mula_s, hg::neg_s, hg::ppacw, hg::sb, hg::sd, hg::sh, hg::si, hg::sll, hg::slti, hg::sltiu,
          hg::sltu, hg::sq, hg::sqrt_s, hg::srl, hg::sub_s, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7};
    // 0x0046eb90
    enter(ctx, 26);  // entry check point + this block's cycles
    sp = addiu(sp, -0x120);
    v0 = 0x960000;
    sd(ra, sp, 0x90);
    a2 = 1;
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(fp, a0, 8);
    s0 = a1;
    lw(v1, v0, -8680);  // 0x95DE18
    lw(v0, fp, 0x18);
    v1 = addu(v0, v1);
    lw(a1, v0, 84);
    lw(v1, v1, 0);
    lw(s7, v1, 0);
    sw(v1, sp, 0xA0);
    sw(a1, a0, 12);
    lw(v1, v0, 24);
    s1 = a0;
    if (v1 != a2) {
        // 0x0046f004
        charge(ctx, 5);
        lw(v1, gp, -17508);  // 0x7CE88C
        a0 = addu(fp, v1);
        lw(v1, a0, 0);
        a3 = 0;
        if (v1 != 0) {
            // 0x0046f018
            charge(ctx, 5);
            lw(a1, v0, 84);
            lw(v1, v1, 0);
            lhu(a1, a1, 4);
            if (a1 == v1) {
                // 0x0046f02c
                charge(ctx, 1);
                a3 = a2;
            }
        }
        // 0x0046f030
        charge(ctx, 2);
        if (a3 == 0) {
            // 0x0046f040
            charge(ctx, 5);
            lw(v0, v0, 84);
            link(ctx, 0x46F044u);  // $ra first: the delay slot below depends on it
            lhu(a1, v0, 4);
            call(ctx, gen::fn_sub_49E5A0_0049e5a0);
            a0 = v0;
            lw(v0, a0, 0);
        } else {
            // 0x0046f038
            charge(ctx, 2);
            lw(v0, a0, 0);
        }
        // 0x0046f054
        charge(ctx, 2);
        sw(v0, s1, 16);
        backedge(ctx);
    } else {
        // 0x0046ebf8
        charge(ctx, 5);
        lw(v1, gp, -17504);  // 0x7CE890
        a0 = addu(v0, v1);
        lw(v1, a0, 0);
        a3 = 0;
        if (v1 != 0) {
            // 0x0046ec0c
            charge(ctx, 5);
            lw(a1, v0, 84);
            lw(v1, v1, 0);
            lhu(a1, a1, 4);
            if (a1 == v1) {
                // 0x0046ec20
                charge(ctx, 1);
                a3 = a2;
            }
        }
        // 0x0046ec24
        charge(ctx, 2);
        if (a3 == 0) {
            // 0x0046ec34
            charge(ctx, 5);
            lw(v0, v0, 84);
            link(ctx, 0x46EC38u);  // $ra first: the delay slot below depends on it
            lhu(a1, v0, 4);
            call(ctx, gen::fn_sub_49E5A0_0049e5a0);
            a0 = v0;
            lw(v0, a0, 0);
        } else {
            // 0x0046ec2c
            charge(ctx, 2);
            lw(v0, a0, 0);
        }
        // 0x0046ec48
        charge(ctx, 1);
        sw(v0, s1, 16);
    }
    // 0x0046ec4c
    charge(ctx, 4);
    lw(v0, s1, 12);
    lhu(v0, v0, 4);
    if (i64(v0) <= 0) {
        // 0x0046f05c
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0046ec5c
        charge(ctx, 7);
        lw(v0, fp, 0x18);
        lw(v0, v0, 24);
        sw(v0, s1, 32);
        lw(v0, s1, 32);
        at = slti(v0, 2);
        if (at == 0) {
            // 0x0046f064
            charge(ctx, 5);
            lwc1(f1, fp, 0x58);
            lwc1(f0, fp, 0x5C);
            mul_s(f0, f1, f0);
            swc1(f0, s1, 28);
            backedge(ctx);
        }
        // 0x0046ec78
        charge(ctx, 6);
        lw(v1, fp, 0x18);
        v0 = 0x1000000;
        lw(a0, v1, 8);
        v0 = a0 & v0;
        if (v0 == 0) {
            // 0x0046f078
            charge(ctx, 18);
            lw(a2, s1, 12);
            v0 = a0 & 0x9F;
            lbu(a0, v1, 24);
            v0 = v0 & 0xFF;
            a1 = sll(v0, 16);
            v0 = si(-2);
            lhu(a2, a2, 6);
            a0 = sll(a0, 24);
            a1 = a2 | a1;
            a0 = a0 | a1;
            sw(a0, s1, 24);
            lw(a0, s1, 20);
            v0 = a0 & v0;
            sw(v0, s1, 20);
            lw(v0, s1, 16);
            lw(a0, v0, 4);
            if (a0 == 0) {
                backedge(ctx);
            } else {
                // 0x0046f0c0
                charge(ctx, 5);
                lw(t0, a0, 40);
                v0 = addiu(a0, 24);
                lw(a3, s1, 24);
                a0 = addiu(fp, 0x4C);
                if (a3 != t0) {
                    // 0x0046f0d4
                    charge(ctx, 6);
                    a2 = srl(a3, 16);
                    a1 = srl(t0, 16);
                    a2 = a2 & 0xFF;
                    a1 = a1 & 0xFF;
                    if (a2 == a1) {
                        // 0x0046f0ec
                        charge(ctx, 6);
                        a2 = srl(a3, 24);
                        a1 = srl(t0, 24);
                        a2 = a2 & 0xFF;
                        a1 = a1 & 0xFF;
                        if (a2 != a1) {
                            goto L_0046f114;
                        }
                        // 0x0046f104
                        charge(ctx, 4);
                        lw(a1, s1, 20);
                        a1 = a1 | 0x4;
                        sw(a1, s1, 20);
                        goto L_0046f120;
                    }
                L_0046f114:
                    charge(ctx, 3);
                    lw(a1, s1, 20);
                    a1 = a1 | 0x8;
                    sw(a1, s1, 20);
                }
            L_0046f120:
                charge(ctx, 3);
                lhu(a1, v1, 12);
                if (a1 != 0) {
                    // 0x0046f12c
                    charge(ctx, 3);
                    a1 = a1 & 0x1;
                    if (a1 == 0) {
                        // 0x0046f148
                        charge(ctx, 8);
                        lw(a1, s1, 20);
                        a1 = a1 | 0x2;
                        sw(a1, s1, 20);
                        lhu(a1, v1, 12);
                        lw(v1, s1, 20);
                        a1 = sll(a1, 3);
                        v1 = v1 | a1;
                        sw(v1, s1, 20);
                    } else {
                        // 0x0046f138
                        charge(ctx, 4);
                        lw(v1, s1, 20);
                        v1 = v1 | 0x8;
                        sw(v1, s1, 20);
                    }
                }
                // 0x0046f168
                charge(ctx, 4);
                lw(v1, a0, 0);
                v1 = v1 & 0x1;
                if (v1 == 0) {
                    backedge(ctx);
                } else {
                    // 0x0046f178
                    charge(ctx, 4);
                    lw(a1, v0, 40);
                    lh(v1, a0, 6);
                    if (a1 == v1) {
                        // 0x0046f188
                        charge(ctx, 4);
                        lw(v1, v0, 36);
                        lh(v0, a0, 4);
                        if (v1 != v0) {
                            goto L_0046f198;
                        }
                        backedge(ctx);
                        goto L_0046ec90;
                    }
                L_0046f198:
                    charge(ctx, 4);
                    lw(v0, s1, 20);
                    v0 = v0 | 0x4;
                    sw(v0, s1, 20);
                    backedge(ctx);
                }
            }
        }
    L_0046ec90:
        charge(ctx, 26);
        lw(a0, fp, 0x18);
        v1 = si(-2);
        v0 = 0x960000;
        sh(zero, a0, 12);
        lw(a0, fp, 0x4C);
        v1 = a0 & v1;
        sw(v1, fp, 0x4C);
        lw(v0, v0, 112);  // 0x960070
        lw(a0, fp, 0x4);
        s2 = addiu(v0, 32);
        jal(ctx, 0x46ECB4u, gen::fn_sub_4CB2F0_004cb2f0);
        lw(a0, s0, 0);
        a1 = v0;
        a2 = s2;
        jal(ctx, 0x46ECC4u, gen::fn_sub_4C2F30_004c2f30);
        a0 = fp;
        s0 = 2;
        jal(ctx, 0x46ECD0u, gen::fn_atomicGetWorldBoundingSphere_004912b0);
        v1 = 0x960000;
        lw(a0, gp, -16972);  // 0x7CEAA4
        lw(a1, v1, 112);  // 0x960070
        v1 = 6;
        a0 = addu(a1, a0);
        a2 = addiu(v1, -1);
        a0 = addiu(a0, 96);
        if (v1 != 0) {
            // 0x0046ecf8
            charge(ctx, 6);
            lwc1(f0, v0, 12);
            v1 = 1;
            lwc1(f7, v0, 4);
            lwc1(f6, v0, 0);
            lwc1(f5, v0, 8);
            neg_s(f4, f0);
            for (;;) {
                // 0x0046ed10
                charge(ctx, 11);
                lwc1(f1, a0, 4);
                lwc1(f2, a0, 0);
                lwc1(f3, a0, 8);
                lwc1(f0, a0, 12);
                mula_s(f7, f1);
                madda_s(f6, f2);
                madd_s(f1, f5, f3);
                sub_s(f0, f1, f0);
                c_le_s(f0, f4);
                v0 = v1;
                if (cond(ctx)) {
                    // 0x0046ed3c
                    charge(ctx, 1);
                    v0 = 0;
                }
                // 0x0046ed40
                charge(ctx, 3);
                v0 = v0 ^ 0x1;
                if (v0 == 0) {
                    goto L_0046ed4c_16;
                }
                // 0x0046ed54
                charge(ctx, 4);
                v0 = a2;
                a0 = addiu(a0, 20);
                a2 = addiu(a2, -1);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0046ed64
            charge(ctx, 1);
        }
    L_0046ed68:
        charge(ctx, 7);
        lw(v1, s1, 12);
        v0 = dsll32(s0, 0);
        a2 = 1;
        lw(a3, v1, 0);
        v1 = a3 & 0x1;
        v0 = dsra32(v0, 0);
        if (v1 == a2) {
            // 0x0046f1a8
            charge(ctx, 5);
            v1 = 4;
            sb(v1, s1, 41);
            lbu(v1, gp, -16892);  // 0x7CEAF4
            sb(v1, s1, 40);
            backedge(ctx);
        } else {
            // 0x0046ed84
            charge(ctx, 3);
            v1 = a3 & 0xFF;
            if (v1 != 0) {
                // 0x0046ed90
                charge(ctx, 4);
                v1 = a3 & 0x2;
                a1 = 2;
                if (v1 == a1) {
                    goto L_0046f1bc;
                }
                // 0x0046eda0
                charge(ctx, 4);
                a0 = a3 & 0x10;
                v1 = 16;
                if (a0 == v1) {
                    // 0x0046f1d4
                    charge(ctx, 5);
                    v1 = 4;
                    sb(v1, s1, 41);
                    lbu(v1, gp, -16892);  // 0x7CEAF4
                    sb(v1, s1, 40);
                    backedge(ctx);
                } else {
                    // 0x0046edb0
                    charge(ctx, 4);
                    a0 = a3 & 0x8;
                    v1 = 8;
                    if (a0 != v1) {
                        // 0x0046edd4
                        charge(ctx, 4);
                        sb(a2, s1, 41);
                        lbu(v1, gp, -16892);  // 0x7CEAF4
                        v1 = v1 | 0x14;
                        sb(v1, s1, 40);
                    } else {
                        // 0x0046edc0
                        charge(ctx, 5);
                        sb(a1, s1, 41);
                        lbu(v1, gp, -16892);  // 0x7CEAF4
                        v1 = v1 | 0x10;
                        sb(v1, s1, 40);
                    }
                }
                goto L_0046ede4;
            }
        L_0046f1bc:
            charge(ctx, 6);
            v1 = 3;
            sb(v1, s1, 41);
            lbu(v1, gp, -16892);  // 0x7CEAF4
            v1 = v1 | 0x4;
            sb(v1, s1, 40);
            backedge(ctx);
        }
    L_0046ede4:
        charge(ctx, 3);
        v1 = 2;
        if (v0 != v1) {
            // 0x0046f1e8
            charge(ctx, 4);
            lbu(v0, s1, 40);
            v0 = v0 | 0x2;
            sb(v0, s1, 40);
            backedge(ctx);
        }
        // 0x0046edf0
        charge(ctx, 9);
        lw(v1, fp, 0x18);
        v0 = 0x960000;
        lw(v1, v1, 8);
        v1 = v1 & 0x40;
        v1 = sltu(0, v1);
        sb(v1, s1, 42);
        lw(v0, v0, -8652);  // 0x95DE34
        if (v0 != 0) {
            // 0x0046ee14
            charge(ctx, 3);
            lw(a1, s1, 8);
            a0 = 1;
            jalr(ctx, 0x46EE18u, v0.u());
            goto L_0046ee20;
        }
        // 0x0046f1f8
        charge(ctx, 6);
        lw(s4, s1, 8);
        lw(s1, s4, 24);
        lw(v0, s1, 8);
        v0 = v0 & 0x20;
        if (v0 == 0) {
            backedge(ctx);
        L_0046ee20:
            charge(ctx, 1);
            lw(a1, sp, 0xA0);
        } else {
            // 0x0046f210
            charge(ctx, 16);
            s5 = 0x960000;
            s5 = addiu(s5, 122);  // &0x96007A
            lhu(v0, s5, 0);  // 0x96007A
            v0 = addiu(v0, 1);
            sh(v0, s5, 0);  // 0x96007A
            link(ctx, 0x46F224u);  // $ra first: the delay slot below depends on it
            lw(a0, s4, 4);
            call(ctx, gen::fn_sub_4CB2F0_004cb2f0);
            s0 = v0;
            a0 = addiu(sp, 0xC0);
            a1 = s0;
            jal(ctx, 0x46F234u, gen::fn_sub_4C32A0_004c32a0);
            lw(v1, s0, 12);
            v0 = 3;
            v1 = v1 & 0x3;
            if (v1 != v0) {
                // 0x0046f260
                charge(ctx, 12);
                lwc1(f3, sp, 0xE4);
                lwc1(f2, sp, 0xE0);
                lwc1(f0, sp, 0xE8);
                mtc1(zero, f1);
                mula_s(f3, f3);
                madda_s(f2, f2);
                madd_s(f0, f0, f0);
                sqrt_s(f2, f0);
                c_le_s(f2, f1);
                swc1(f2, sp, 0x100);
                if (!cond(ctx)) {
                    // 0x0046f290
                    charge(ctx, 7);
                    v0 = 0x3F800000;
                    mtc1(v0, f0);
                    div_s(f2, f0, f2);
                }
                // 0x0046f2ac
                charge(ctx, 1);
                swc1(f2, sp, 0x104);
            } else {
                // 0x0046f250
                charge(ctx, 4);
                v0 = 0x3F800000;
                sw(v0, sp, 0x100);
                sw(v0, sp, 0x104);
            }
            // 0x0046f2b0
            charge(ctx, 14);
            lw(v1, s1, 84);
            a0 = 0x4A0000;
            a0 = addiu(a0, 1072);  // &sub_4A0430
            a1 = addiu(sp, 0xB0);
            lw(v0, v1, 12);
            v0 = addu(v0, v1);
            lw(v0, v0, 24);
            v0 = addiu(v0, 12);
            link(ctx, 0x46F2D0u);  // $ra first: the delay slot below depends on it
            sw(v0, sp, 0xB0);
            call(ctx, gen::fn_worldForAllLights_00499c20);
            lw(s3, s4, 100);
            s6 = addiu(s4, 100);
            if (s3 == s6) {
                backedge(ctx);
                goto L_0046ee20;
            }
            for (;;) {
                // 0x0046f2e8
                charge(ctx, 5);
                lw(v0, s3, 8);
                lw(s2, v0, 64);
                s1 = addiu(v0, 64);
                if (s2 != s1) {
                    // 0x0046f2fc
                    charge(ctx, 1);
                    for (;;) {
                        // 0x0046f300
                        charge(ctx, 3);
                        lw(a1, s2, 8);
                        if (a1 != 0) {
                            // 0x0046f30c
                            charge(ctx, 4);
                            lhu(a0, s5, 0);
                            lhu(v0, a1, 60);
                            v1 = addiu(a1, 60);
                            if (v0 != a0) {
                                // 0x0046f31c
                                charge(ctx, 4);
                                lbu(v0, a1, 2);
                                v0 = v0 & 0x1;
                                if (v0 != 0) {
                                    // 0x0046f32c
                                    charge(ctx, 27);
                                    sh(a0, v1, 0);
                                    lw(v0, s2, 8);
                                    link(ctx, 0x46F334u);  // $ra first: the delay slot below depends on it
                                    lw(a0, v0, 4);
                                    call(ctx, gen::fn_sub_4CB2F0_004cb2f0);
                                    s0 = addiu(v0, 48);
                                    a0 = s4;
                                    jal(ctx, 0x46F340u, gen::fn_atomicGetWorldBoundingSphere_004912b0);
                                    lwc1(f4, v0, 4);
                                    lw(a0, s2, 8);
                                    lwc1(f3, s0, 4);
                                    lwc1(f6, v0, 0);
                                    lwc1(f5, s0, 0);
                                    lwc1(f0, s0, 8);
                                    lwc1(f1, v0, 8);
                                    lwc1(f2, v0, 12);
                                    sub_s(f3, f4, f3);
                                    sub_s(f5, f6, f5);
                                    mula_s(f3, f3);
                                    sub_s(f0, f1, f0);
                                    madda_s(f5, f5);
                                    madd_s(f1, f0, f0);
                                    lwc1(f0, a0, 20);
                                    add_s(f0, f2, f0);
                                    mul_s(f0, f0, f0);
                                    c_lt_s(f1, f0);
                                    if (cond(ctx)) {
                                        // 0x0046f398
                                        charge(ctx, 2);
                                        a1 = addiu(sp, 0xB0);
                                        jal(ctx, 0x46F398u, gen::fn_sub_4A0430_004a0430);
                                    }
                                }
                            }
                        }
                        // 0x0046f3a0
                        charge(ctx, 3);
                        lw(s2, s2, 0);
                        if (s2 == s1) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0046f3ac
                    charge(ctx, 1);
                }
                // 0x0046f3b0
                charge(ctx, 3);
                lw(s3, s3, 0);
                if (s3 == s6) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0046f3bc
            charge(ctx, 2);
            lw(a1, sp, 0xA0);
            backedge(ctx);
        }
        // 0x0046ee24
        charge(ctx, 28);
        a0 = fp;
        jal(ctx, 0x46EE24u, gen::fn__rpSkinMatrixUpdating_0046b510);
        s1 = sll(s7, 2);
        s0 = v0;
        a1 = addiu(s1, 2);
        a0 = 0;
        jal(ctx, 0x46EE38u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
        v0 = s1 & 0xFF;
        a0 = 0x6C000000;
        a1 = sll(v0, 16);
        a0 = a0 | 0x2BC;
        v0 = 0x1000000;
        a0 = a1 | a0;
        v0 = v0 | 0x101;  // &0x1000101
        v1 = dsll32(s1, 0);
        ppacw(a3, a0, v0);
        lw(a2, gp, -17148);  // 0x7CE9F4
        v1 = dsrl32(v1, 0);
        v0 = 0x10000000;
        v0 = v1 | v0;
        a1 = 0;
        ppacw(v0, a1, v0);
        ppacw(v0, a3, v0);
        at = sltu(0, s7);
        a0 = addiu(a2, 16);
        v1 = 0;
        sq(v0, a2, 0);
        if (at != 0) {
            // 0x0046ee94
            charge(ctx, 3);
            at = sltiu(s7, 9);
            v0 = addiu(s7, -8);
            if (at == 0) {
                for (;;) {
                    // 0x0046eea0
                    charge(ctx, 69);
                    lq(t1, s0, 16);
                    v1 = addiu(v1, 8);
                    lq(t0, s0, 32);
                    a1 = sltu(v1, v0);
                    lq(a3, s0, 48);
                    lq(a2, s0, 0);
                    sq(a2, a0, 0);
                    sq(t1, a0, 16);
                    sq(t0, a0, 32);
                    sq(a3, a0, 48);
                    lq(t1, s0, 80);
                    lq(t0, s0, 96);
                    lq(a3, s0, 112);
                    lq(a2, s0, 64);
                    sq(a2, a0, 64);
                    sq(t1, a0, 80);
                    sq(t0, a0, 96);
                    sq(a3, a0, 112);
                    lq(t1, s0, 144);
                    lq(t0, s0, 160);
                    lq(a3, s0, 176);
                    lq(a2, s0, 128);
                    sq(a2, a0, 128);
                    sq(t1, a0, 144);
                    sq(t0, a0, 160);
                    sq(a3, a0, 176);
                    lq(t1, s0, 208);
                    lq(t0, s0, 224);
                    lq(a3, s0, 240);
                    lq(a2, s0, 192);
                    sq(a2, a0, 192);
                    sq(t1, a0, 208);
                    sq(t0, a0, 224);
                    sq(a3, a0, 240);
                    lq(t1, s0, 272);
                    lq(t0, s0, 288);
                    lq(a3, s0, 304);
                    lq(a2, s0, 256);
                    sq(a2, a0, 256);
                    sq(t1, a0, 272);
                    sq(t0, a0, 288);
                    sq(a3, a0, 304);
                    lq(t1, s0, 336);
                    lq(t0, s0, 352);
                    lq(a3, s0, 368);
                    lq(a2, s0, 320);
                    sq(a2, a0, 320);
                    sq(t1, a0, 336);
                    sq(t0, a0, 352);
                    sq(a3, a0, 368);
                    lq(t1, s0, 400);
                    lq(t0, s0, 416);
                    lq(a3, s0, 432);
                    lq(a2, s0, 384);
                    sq(a2, a0, 384);
                    sq(t1, a0, 400);
                    sq(t0, a0, 416);
                    sq(a3, a0, 432);
                    lq(t1, s0, 464);
                    lq(t0, s0, 480);
                    lq(a3, s0, 496);
                    lq(a2, s0, 448);
                    sq(a2, a0, 448);
                    s0 = addiu(s0, 512);
                    sq(t1, a0, 464);
                    sq(t0, a0, 480);
                    sq(a3, a0, 496);
                    a0 = addiu(a0, 512);
                    if (a1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0046efb4
                charge(ctx, 1);
            }
            // 0x0046efb8
            charge(ctx, 3);
            at = sltu(v1, s7);
            if (at != 0) {
                for (;;) {
                    // 0x0046efc4
                    charge(ctx, 13);
                    lq(t0, s0, 16);
                    v1 = addiu(v1, 1);
                    lq(a3, s0, 32);
                    v0 = sltu(v1, s7);
                    lq(a2, s0, 48);
                    lq(a1, s0, 0);
                    sq(a1, a0, 0);
                    s0 = addiu(s0, 64);
                    sq(t0, a0, 16);
                    sq(a3, a0, 32);
                    sq(a2, a0, 48);
                    a0 = addiu(a0, 64);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
        // 0x0046eff8
        charge(ctx, 3);
        sw(a0, gp, -17148);  // 0x7CE9F4
        if (g_observer && g_observer->skin) g_observer->skin(ctx, SkinPalette{rd32(ctx, 0x0095DE1Cu), s7.u()});  // the palette
        v0 = 1;
    }
    // 0x0046f3c4 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x90);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x120);
    return;
L_0046ed4c_16:
    charge(ctx, 2);
    s0 = 1;
    goto L_0046ed68;
}

// 0x004EC2B0 openVU1SetupPktNew -- 516 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// openVU1SetupPktNew [openVU1SetupPktNew]: ($a0 matrix or 0, $a1 light block, $a2 its quadwords). The packet: a DMA cnt
// tag over 3 + rows + lights quadwords; the template qw 0x9659C0; STCYCL 4,4 + UNPACK V4-32 of `rows` qw (10 with
// a matrix, 4 without) to VU1 0x3F0 (0x3F6 without a matrix); the matrix rows as {x, y, z, z} (the w lane takes
// z: the flags word of an RwMatrix row is not sent) and two zero quadwords; the five template quadwords at
// 0x965970..0x9659B0; the light block. Returns 1.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void openVU1SetupPktNew(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsrl32, hg::enter, hg::jal, hg::ld,
          hg::lq, hg::lw, hg::lwu, hg::pcpyld, hg::sd, hg::sll, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    const ObjectSetup setup{a0.u(), a1.u(), a2.u()};  // the draw record (host-only)
    // 0x004ec2b0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v0 = 6;
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = 1008;
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    if (s4 == 0) {
        // 0x004ec47c
        charge(ctx, 3);
        v0 = 0;
        s5 = 1014;
        backedge(ctx);
    }
    // 0x004ec2e8
    charge(ctx, 34);
    s1 = addiu(v0, 4);
    a0 = 0;
    v0 = addiu(s1, 3);
    s0 = addu(v0, s2);
    a1 = addiu(s0, 2);
    jal(ctx, 0x4EC2F8u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    v0 = sll(s1, 16);
    v1 = dsll32(s0, 0);
    a1 = dsll32(v0, 0);
    a0 = dsll32(s5, 0);
    v1 = dsrl32(v1, 0);
    v0 = 0x10000000;
    v0 = v1 | v0;
    lw(a2, gp, -17148);  // 0x7CE9F4
    v1 = 0;
    a1 = dsrl32(a1, 0);
    pcpyld(a3, v1, v0);
    v1 = 0x6C000000;
    a0 = dsrl32(a0, 0);
    a1 = a1 | v1;
    v0 = 0x960000;
    a0 = a1 | a0;
    v1 = 0x1000000;
    v1 = v1 | 0x404;  // &0x1000404
    a0 = dsll32(a0, 0);
    sq(a3, a2, 0);
    v1 = a0 | v1;
    lq(a0, v0, 22976);  // 0x9659C0
    a1 = 0;
    pcpyld(v1, v1, a1);
    sq(a0, a2, 16);
    v0 = addiu(a2, 48);
    sq(v1, a2, 32);
    if (s4 != 0) {
        // 0x004ec370
        charge(ctx, 39);
        lwu(a1, s4, 4);
        lwu(v1, s4, 0);
        lwu(t2, s4, 8);
        lwu(a0, s4, 20);
        lwu(a3, s4, 16);
        lwu(t0, s4, 24);
        a2 = dsll32(a1, 0);
        t3 = v1 | a2;
        lwu(a1, s4, 36);
        t1 = dsll32(t2, 0);
        lwu(v1, s4, 32);
        t2 = t2 | t1;
        lwu(a2, s4, 40);
        t1 = dsll32(a0, 0);
        t1 = a3 | t1;
        lwu(a0, s4, 52);
        a3 = dsll32(t0, 0);
        a1 = dsll32(a1, 0);
        t0 = t0 | a3;
        a3 = v1 | a1;
        pcpyld(t2, t2, t3);
        lwu(v1, s4, 48);
        sq(t2, v0, 0);
        pcpyld(a1, t0, t1);
        sq(a1, v0, 16);
        a1 = dsll32(a2, 0);
        a2 = a2 | a1;
        a1 = dsll32(a0, 0);
        lwu(a0, s4, 56);
        a1 = v1 | a1;
        pcpyld(a2, a2, a3);
        sq(a2, v0, 32);
        v1 = dsll32(a0, 0);
        v1 = a0 | v1;
        pcpyld(v1, v1, a1);
        sq(v1, v0, 48);
        sq(zero, v0, 64);
        sq(zero, v0, 80);
        v0 = addiu(v0, 96);
    }
    // 0x004ec40c
    charge(ctx, 19);
    v1 = 0x960000;
    a3 = s2;
    lq(t0, v1, 22896);  // 0x965970
    a2 = 0x960000;
    a1 = 0x960000;
    a0 = 0x960000;
    s2 = addiu(s2, -1);
    sq(t0, v0, 0);
    v1 = 0x960000;
    lq(a2, a2, 22912);  // 0x965980
    sq(a2, v0, 16);
    lq(a1, a1, 22928);  // 0x965990
    sq(a1, v0, 32);
    lq(a0, a0, 22944);  // 0x9659A0
    sq(a0, v0, 48);
    lq(v1, v1, 22960);  // 0x9659B0
    sq(v1, v0, 64);
    v0 = addiu(v0, 80);
    if (a3 == 0) {
        // 0x004ec488
        charge(ctx, 1);
        sw(v0, gp, -17148);  // 0x7CE9F4
    } else {
        for (;;) {
            // 0x004ec458
            charge(ctx, 7);
            lq(a0, s3, 0);
            v1 = s2;
            s2 = addiu(s2, -1);
            sq(a0, v0, 0);
            s3 = addiu(s3, 16);
            v0 = addiu(v0, 16);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004ec474
        charge(ctx, 2);
        sw(v0, gp, -17148);  // 0x7CE9F4
    }
    if (g_observer && g_observer->object) g_observer->object(ctx, setup);
    // 0x004ec48c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    v0 = 1;
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// 0x004F0F30 sub_4F0F30 -- 232 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4F0F30: before the bridge's real access, a raster that is not the last one, not locked (+32 bit 7), has
// pixels (+4) and no cache slot is placed by the upload callback (raster, 1); when that gave it a slot and the
// cache is active, its TEX0 TBP/CBP are patched.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_4F0F30(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::dsll, hg::dsll32, hg::dsra32, hg::enter, hg::jalr, hg::lbu,
          hg::ld, hg::lq, hg::lui, hg::lw, hg::sd, hg::si, hg::sq, hg::srl, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f0f30
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 0x780000;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a1, gp, -16968);  // 0x7CEAA8
    lw(v1, v1, -3548);  // 0x77F224
    s0 = addu(a0, a1);
    if (a0 != v1) {
        // 0x004f0f50
        charge(ctx, 4);
        lbu(v1, a0, 32);
        v1 = v1 & 0x80;
        if (v1 == 0) {
            // 0x004f0f60
            charge(ctx, 3);
            lw(v1, a0, 4);
            if (v1 != 0) {
                // 0x004f0f6c
                charge(ctx, 3);
                lw(v1, s0, 88);
                if (v1 == 0) {
                    // 0x004f0f78
                    charge(ctx, 7);
                    v0 = 0x780000;
                    lw(v0, v0, -3552);  // 0x77F220
                    a1 = 1;
                    jalr(ctx, 0x4F0F80u, v0.u());
                    lw(a0, s0, 88);
                    if (a0 != 0) {
                        // 0x004f0f94
                        charge(ctx, 4);
                        v1 = 0x780000;
                        lw(v1, v1, -3584);  // 0x77F200
                        if (v1 != 0) {
                            // 0x004f0fa4
                            charge(ctx, 25);
                            lw(a2, a0, 4);
                            v1 = lui(0xFFF8);
                            lw(a1, s0, 8);
                            v1 = v1 | 0x1F;
                            a0 = si(-16384);
                            a2 = srl(a2, 6);
                            a0 = a1 & a0;
                            sw(a0, s0, 8);
                            a1 = a2 & 0x3FFF;
                            lw(a0, s0, 8);
                            a0 = a0 | a1;
                            sw(a0, s0, 8);
                            lw(a1, s0, 16);
                            lw(a0, s0, 12);
                            a1 = addu(a2, a1);
                            a0 = a0 & v1;
                            v1 = a1 & 0x3FFF;
                            sw(a0, s0, 12);
                            v1 = v1 & 0x3FFF;
                            a0 = dsll(v1, 5);
                            lw(v1, s0, 12);
                            a0 = dsll32(a0, 0);
                            a0 = dsra32(a0, 0);
                            v1 = v1 | a0;
                            sw(v1, s0, 12);
                        }
                    }
                }
            }
        }
    }
    // 0x004f1008 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x004F1020 RpSkyTexCacheAccessRaster -- 1304 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// RpSkyTexCacheAccessRaster [RpSkyTexCacheAccessRaster]: ($a0 raster, $a1 mode: 0 = the bridge's TEX0 + TEX1 form, else the
// MIPTBP form). Makes the raster resident (upload callback (raster, 0)), patches TEX0, remembers the slot index
// per mode, and unless the raster is the last one with the same mode (and, for an 8-bit palettised raster
// (+32 & 7 == 2) without its own palette link, ...) emits the A+D packet: a GIF tag (NLOOP 4 / 5, A+D) with
// TEX0_1 (0x06; the CLUT bits CBP from 0x964B60 / 0x9649F0 for palettised rasters) or TEX0_2, then for mode 0
// the TEX1_1 (0x14) shadow update (K/L/MXL from the extension) and MIPTBP1/2 (0x34/0x36 or 0x35/0x37) with the
// TBP added when the cache is active. Returns 1 (0 when the raster has no slot afterwards).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void RpSkyTexCacheAccessRaster(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll, hg::dsll32, hg::dsra32, hg::dsrl32,
          hg::enter, hg::jal, hg::jalr, hg::lbu, hg::ld, hg::lhu, hg::lq, hg::lui, hg::lw, hg::lwu, hg::mfhi,
          hg::mult, hg::pcpyld, hg::sd, hg::si, hg::sq, hg::sra, hg::srl, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f1020
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x780000;
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(v1, gp, -16968);  // 0x7CEAA8
    lw(v0, v0, -3548);  // 0x77F224
    s0 = addu(s2, v1);
    if (s2 != v0) {
        // 0x004f1050
        charge(ctx, 4);
        lbu(v0, s2, 32);
        v0 = v0 & 0x80;
        if (v0 == 0) {
            // 0x004f1060
            charge(ctx, 3);
            lw(v0, s2, 4);
            if (v0 != 0) {
                // 0x004f106c
                charge(ctx, 3);
                lw(v0, s0, 88);
                if (v0 == 0) {
                    // 0x004f1078
                    charge(ctx, 4);
                    v0 = 0x780000;
                    lw(v0, v0, -3552);  // 0x77F220
                    a1 = 0;
                    jalr(ctx, 0x4F1080u, v0.u());
                }
            }
        }
    }
    // 0x004f1088
    charge(ctx, 3);
    lw(v1, s0, 88);
    if (v1 != 0) {
        // 0x004f1094
        charge(ctx, 4);
        v0 = 0x780000;
        lw(v0, v0, -3584);  // 0x77F200
        if (v0 != 0) {
            // 0x004f10a4
            charge(ctx, 26);
            lw(a1, v1, 4);
            v0 = lui(0xFFF8);
            lw(a0, s0, 8);
            v0 = v0 | 0x1F;
            v1 = si(-16384);
            a1 = srl(a1, 6);
            v1 = a0 & v1;
            sw(v1, s0, 8);
            a0 = a1 & 0x3FFF;
            lw(v1, s0, 8);
            v1 = v1 | a0;
            sw(v1, s0, 8);
            lw(a0, s0, 16);
            lw(v1, s0, 12);
            a0 = addu(a1, a0);
            v1 = v1 & v0;
            v0 = a0 & 0x3FFF;
            sw(v1, s0, 12);
            v0 = v0 & 0x3FFF;
            v1 = dsll(v0, 5);
            lw(v0, s0, 12);
            v1 = dsll32(v1, 0);
            v1 = dsra32(v1, 0);
            v0 = v0 | v1;
            sw(v0, s0, 12);
        }
    }
    // 0x004f1420
    charge(ctx, 5);
    lbu(v1, s2, 32);
    v0 = 2;
    a0 = v1 & 0x7;
    if (a0 == v0) {
        backedge(ctx);
    } else {
        // 0x004f1434
        charge(ctx, 2);
        lw(v0, s0, 88);
        backedge(ctx);
        // 0x004f110c
        charge(ctx, 2);
        if (v0 != 0) {
            goto L_004f111c;
        }
        // 0x004f1114
        charge(ctx, 2);
        v0 = 0;
        // 0x004f1520 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(ra, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
        return;
    }
L_004f111c:
    charge(ctx, 4);
    v0 = 0x780000;
    lw(v0, v0, -3548);  // 0x77F224
    if (v0 == s2) {
        // 0x004f143c
        charge(ctx, 4);
        lw(v1, gp, -16948);  // 0x7CEABC
        v0 = si(-1);
        if (v1 == v0) {
            backedge(ctx);
            goto L_004f112c;
        }
        // 0x004f144c
        charge(ctx, 4);
        v0 = 0x780000;
        lw(v0, v0, -3544);  // 0x77F228
        if (v0 != s1) {
            backedge(ctx);
            goto L_004f112c;
        }
        // 0x004f145c
        charge(ctx, 3);
        v0 = 2;
        if (a0 != v0) {
            backedge(ctx);
        } else {
            // 0x004f1468
            charge(ctx, 3);
            lw(v0, s2, 0);
            if (v0 != s2) {
                // 0x004f1474
                charge(ctx, 2);
                backedge(ctx);
                goto L_004f112c;
            }
            backedge(ctx);
        }
        goto L_004f1418;
    }
L_004f112c:
    charge(ctx, 7);
    v1 = 0x780000;
    v0 = 0x780000;
    sw(s2, v1, -3548);  // 0x77F224
    sw(s1, v0, -3544);  // 0x77F228
    lw(a1, s0, 88);
    if (a1 != 0) {
        // 0x004f1148
        charge(ctx, 4);
        v0 = 0x780000;
        lw(v0, v0, -3584);  // 0x77F200
        if (v0 != 0) {
            // 0x004f1158
            charge(ctx, 2);
            if (s1 != 0) {
                // 0x004f1198
                charge(ctx, 14);
                v0 = 0x780000;
                v1 = 0x2AAA0000;
                lw(a0, v0, -3564);  // 0x77F214
                v0 = v1 | 0xAAAB;
                v1 = subu(a1, a0);
                mult(zero, v0, v1);
                a0 = srl(v1, 31);
                mfhi(v1);
                v0 = 0x780000;
                v1 = sra(v1, 1);
                v1 = addu(v1, a0);
                sw(v1, v0, -3536);  // 0x77F230
            } else {
                // 0x004f1160
                charge(ctx, 14);
                v0 = 0x780000;
                v1 = 0x2AAA0000;
                lw(a0, v0, -3564);  // 0x77F214
                v0 = v1 | 0xAAAB;
                v1 = subu(a1, a0);
                mult(zero, v0, v1);
                a0 = srl(v1, 31);
                mfhi(v1);
                v0 = 0x780000;
                v1 = sra(v1, 1);
                v1 = addu(v1, a0);
                sw(v1, v0, -3540);  // 0x77F22C
            }
        }
    }
    // 0x004f147c
    charge(ctx, 3);
    lbu(v0, s0, 23);
    if (v0 != 0) {
        backedge(ctx);
    } else {
        // 0x004f1488
        charge(ctx, 2);
        lw(v0, gp, -16856);  // 0x7CEB18
        backedge(ctx);
        // 0x004f11d0
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x004f11d8
            charge(ctx, 4);
            v0 = 0x780000;
            lw(v0, v0, -3584);  // 0x77F200
            if (v0 != 0) {
                // 0x004f11e8
                charge(ctx, 1);
                sw(zero, gp, -17208);  // 0x7CE9B8
            }
        }
    }
    // 0x004f11ec
    charge(ctx, 34);
    a1 = 5;
    v0 = 6;
    if (s1 == 0) a1 = v0;
    a0 = lui(0x8000);
    jal(ctx, 0x4F11F8u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    a0 = 4;
    v0 = 5;
    if (s1 == 0) a0 = v0;
    v0 = 0x10000000;
    v1 = dsll32(v0, 0);
    v0 = 0x8000;
    v1 = v0 | v1;
    a0 = a0 | v1;
    v0 = 14;
    lw(v1, gp, -17148);  // 0x7CE9F4
    pcpyld(a1, v0, a0);
    v0 = 63;
    a0 = 0;
    pcpyld(a0, v0, a0);
    v0 = 2;
    sq(a1, v1, 0);
    sq(a0, v1, 16);
    lw(v1, gp, -17148);  // 0x7CE9F4
    v1 = addiu(v1, 32);
    sw(v1, gp, -17148);  // 0x7CE9F4
    lw(a3, s0, 8);
    lbu(a0, s2, 32);
    lwu(a2, s0, 12);
    a1 = dsll32(a3, 0);
    a0 = a0 & 0x7;
    a1 = dsrl32(a1, 0);
    a2 = dsll32(a2, 0);
    a2 = a1 | a2;
    if (a0 == v0) {
        // 0x004f1274
        charge(ctx, 4);
        lw(v0, gp, -17016);  // g_skyFrameCount
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x004f1290
            charge(ctx, 2);
            v0 = 0x960000;
            ld(v0, v0, 18928);  // rwDMAFlipData+0x60
        } else {
            // 0x004f1284
            charge(ctx, 3);
            v0 = 0x960000;
            ld(v0, v0, 19296);  // rwDMAFlipData+0x1D0
        }
        // 0x004f1298
        charge(ctx, 8);
        v0 = v0 & 0x1FF;
        a0 = a3 & 0x3FFF;
        a1 = dsll(v0, 5);
        v0 = si(-16384);
        a0 = a0 + a1;
        pcpyld(v0, zero, v0);
        v0 = a2 & v0;
        a2 = v0 | a0;
    }
    // 0x004f12b8
    charge(ctx, 13);
    a0 = 7;
    v0 = 6;
    if (s1 == 0) a0 = v0;
    v0 = dsll32(v1, 0);
    v1 = dsll32(a0, 0);
    v0 = dsra32(v0, 0);
    v1 = dsra32(v1, 0);
    pcpyld(v1, v1, a2);
    sq(v1, v0, 0);
    lw(v0, gp, -17148);  // 0x7CE9F4
    v1 = addiu(v0, 16);
    sw(v1, gp, -17148);  // 0x7CE9F4
    if (s1 == 0) {
        // 0x004f1490
        charge(ctx, 36);
        v0 = si(-4096);
        ld(a3, gp, -17040);  // 0x7CEA60
        a2 = dsll32(v0, 0);
        a0 = 20;
        v0 = 0xFFE7;
        v0 = dsll(v0, 16);
        a1 = v0 | 0xFDE3;
        v0 = dsll32(v1, 0);
        v1 = a1 | a2;
        v0 = dsra32(v0, 0);
        v1 = a3 & v1;
        sd(v1, gp, -17040);  // 0x7CEA60
        lhu(a1, s0, 20);
        lbu(a3, s0, 22);
        ld(v1, gp, -17040);  // 0x7CEA60
        a2 = a1 & 0xFFF;
        a1 = sra(a1, 12);
        a2 = dsll32(a2, 0);
        a1 = a1 & 0x3;
        a3 = dsll32(a3, 0);
        a2 = dsra32(a2, 0);
        a1 = dsll32(a1, 0);
        a1 = dsra32(a1, 0);
        a3 = dsra32(a3, 0);
        a2 = dsll32(a2, 0);
        a1 = dsll(a1, 19);
        a2 = a3 | a2;
        a1 = a1 | a2;
        v1 = v1 | a1;
        pcpyld(a0, a0, v1);
        sd(v1, gp, -17040);  // 0x7CEA60
        sq(a0, v0, 0);
        lw(v0, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v0, 16);
        sw(v1, gp, -17148);  // 0x7CE9F4
        backedge(ctx);
    }
    // 0x004f12ec
    charge(ctx, 9);
    lw(a1, s0, 8);
    v0 = 0x780000;
    lw(a0, v0, -3584);  // 0x77F200
    a2 = a1 & 0x3FFF;
    v0 = dsll(a2, 20);
    a1 = dsll32(a2, 8);
    v0 = a2 | v0;
    v0 = a1 | v0;
    if (a0 == 0) {
        // 0x004f1398
        charge(ctx, 31);
        lwu(a3, s0, 28);
        a1 = dsll32(v1, 0);
        lwu(t0, s0, 24);
        a0 = 53;
        v0 = 52;
        v1 = 55;
        if (s1 == 0) a0 = v0;
        a1 = dsra32(a1, 0);
        v0 = 54;
        a2 = dsll32(a0, 0);
        if (s1 == 0) v1 = v0;
        a2 = dsra32(a2, 0);
        v0 = dsll32(a3, 0);
        a0 = dsll32(v1, 0);
        v0 = t0 | v0;
        a0 = dsra32(a0, 0);
        pcpyld(v0, a2, v0);
        sq(v0, a1, 0);
        lw(v0, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v0, 16);
        sw(v1, gp, -17148);  // 0x7CE9F4
        lwu(v1, s0, 36);
        lwu(a1, s0, 32);
        lw(v0, gp, -17148);  // 0x7CE9F4
        v1 = dsll32(v1, 0);
        v1 = a1 | v1;
        pcpyld(v1, a0, v1);
        sq(v1, v0, 0);
        lw(v0, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v0, 16);
        sw(v1, gp, -17148);  // 0x7CE9F4
    } else {
        // 0x004f1310
        charge(ctx, 34);
        lwu(a3, s0, 28);
        a1 = dsll32(v1, 0);
        lwu(t0, s0, 24);
        a2 = 53;
        a0 = 52;
        v1 = 54;
        if (s1 == 0) a2 = a0;
        a1 = dsra32(a1, 0);
        a0 = 55;
        a2 = dsll32(a2, 0);
        if (s1 == 0) a0 = v1;
        a2 = dsra32(a2, 0);
        v1 = dsll32(a3, 0);
        a0 = dsll32(a0, 0);
        v1 = t0 | v1;
        a0 = dsra32(a0, 0);
        v1 = v1 + v0;
        pcpyld(v1, a2, v1);
        sq(v1, a1, 0);
        lw(v1, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v1, 16);
        sw(v1, gp, -17148);  // 0x7CE9F4
        lwu(a1, s0, 36);
        lwu(a2, s0, 32);
        lw(v1, gp, -17148);  // 0x7CE9F4
        a1 = dsll32(a1, 0);
        a1 = a2 | a1;
        v0 = a1 + v0;
        pcpyld(v0, a0, v0);
        sq(v0, v1, 0);
        lw(v0, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v0, 16);
        sw(v1, gp, -17148);  // 0x7CE9F4
    }
    // 0x004f1414
    charge(ctx, 1);
    sw(zero, gp, -16856);  // 0x7CEB18
L_004f1418:
    charge(ctx, 2);
    v0 = 1;
    // 0x004f1520 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004A0E00 RpMeshPS2AllBridgeCallBack -- 1572 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// RpMeshPS2AllBridgeCallBack: one mesh's material into the packet ($a0 = PipeData). The VIF packet (18 qw
// reserved): a cnt tag over 15 quadwords, then per UNPACK V4-32 of one quadword (STCYCL 4,4): the GIF tag of
// the VU1 kick -> VU1 0x3FA (template 0x9658A0 with PRIM = (render flags | prim type) & 0x7FF in bits 47..57,
// written back to the template), the material colour -> 0x3FB (sub_49CAB0), the surface properties -> 0x3FC
// (sub_49CBD0); UNPACK of three quadwords -> 0x3FD: the clip vector pair (templates 0x965930/40 when culling
// and not a list, or fog and a list; else 0x965910/20; the flags word gets bit 3 with the first pair) and
// {clip flags | (gp-16884: 32 for projection 3) , gp-16880, transType & 7 (| 8)}; then DIRECT 4 with the A+D
// registers TEST_1 (0x47), TEX1_1 (0x14), CLAMP_1 (0x08) when textured, or two zero quadwords and DIRECT 2
// with TEST_1 alone. After the packet: the VU1 code array entry ((tt & 0x20) >> 5 | (tt & 0x18) >> 2) of the
// material pipeline (+24) is `call`ed when it is not the resident program, and the resEntry's instanced data
// (resEntry +32) is `call`ed with BASE 0 / OFFSET (pipeline +20); its use counts (+24 under DI, +28) go up and
// a first use adds it to the packet layer's reference ring (_rwDMAAddPURef). Returns 1.
//
// Before the packet, the texture state: sub_4F0F30 places the texture's raster speculatively, the raster
// "has alpha" flag (format nibble +35 == 1 or 5), and when the raster differs from the last one: TME on +
// RpSkyTexCacheAccessRaster(raster, 0) or TME off; with a texture the filter (sub_49CA50) and the CLAMP shadow
// (address modes U / V == 3 -> REGION_CLAMP bits 0 / 2); the TEST shadow's ATE follows the raster alpha; ABE
// (flags 0x40) follows the material alpha (+71 != 255) or the raster alpha.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void RpMeshPS2AllBridgeCallBack(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::di, hg::dsll, hg::dsll32,
          hg::dsra32, hg::dsrl32, hg::ei, hg::enter, hg::jal, hg::lbu, hg::ld, hg::link, hg::lq, hg::lui, hg::lw,
          hg::lwc1, hg::lwu, hg::mfc0, hg::mtc1, hg::pcpyld, hg::sb, hg::sd, hg::si, hg::sll, hg::sltiu, hg::sltu,
          hg::sq, hg::sra, hg::srl, hg::sw, hg::sync;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    BridgePass pass;  // the draw record (host-only)
    Fpr f12{ctx, 12};
    // 0x004a0e00
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, 64);
    s2 = a0;
    if (v0 != 0) {
        // 0x004a0e20
        charge(ctx, 2);
        link(ctx, 0x4A0E20u);  // $ra first: the delay slot below depends on it
        lw(a0, v0, 0);
        call(ctx, gen::fn_sub_4F0F30_004f0f30);
    }
    // 0x004a0e28
    charge(ctx, 3);
    lw(s0, s2, 64);
    s1 = 0;
    if (s0 != 0) {
        // 0x004a0e34
        charge(ctx, 1);
        lw(s1, s0, 0);
    }
    // 0x004a0e38
    charge(ctx, 3);
    sw(zero, gp, -16952);  // 0x7CEAB8
    v0 = 0;
    if (s1 != 0) {
        // 0x004a0e44
        charge(ctx, 11);
        lbu(v1, s1, 35);
        v0 = dsll32(v0, 0);
        v0 = dsra32(v0, 0);
        v1 = v1 & 0xF;
        a0 = v1 ^ 0x1;
        v1 = v1 ^ 0x5;
        a0 = sltiu(a0, 1);
        v1 = sltiu(v1, 1);
        v1 = a0 | v1;
        v0 = v0 | v1;
        sw(v0, gp, -16952);  // 0x7CEAB8
    }
    // 0x004a0e70
    charge(ctx, 3);
    lw(v0, gp, -16948);  // 0x7CEABC
    if (s1 != v0) {
        // 0x004a0e7c
        charge(ctx, 2);
        if (s1 == 0) {
            // 0x004a1328
            charge(ctx, 5);
            ld(v1, gp, -20272);  // 0x7CDDC0
            v0 = si(-17);
            v0 = v1 & v0;
            sd(v0, gp, -20272);  // 0x7CDDC0
            backedge(ctx);
        } else {
            // 0x004a0e84
            charge(ctx, 6);
            ld(v0, gp, -20272);  // 0x7CDDC0
            a0 = s1;
            a1 = 0;
            v0 = v0 | 0x10;
            link(ctx, 0x4A0E94u);  // $ra first: the delay slot below depends on it
            sd(v0, gp, -20272);  // 0x7CDDC0
            call(ctx, gen::fn_RpSkyTexCacheAccessRaster_004f1020);
        }
        // 0x004a0e9c
        charge(ctx, 2);
        sw(s1, gp, -16948);  // 0x7CEABC
        if (s0 != 0) {
            // 0x004a0ea4
            charge(ctx, 9);
            link(ctx, 0x4A0EA4u);  // $ra first: the delay slot below depends on it
            lbu(a0, s0, 80);
            call(ctx, gen::fn_sub_49CA50_0049ca50);
            sd(zero, gp, -17048);  // 0x7CEA58
            v0 = 3;
            lw(v1, s0, 80);
            v1 = v1 & 0xF00;
            v1 = srl(v1, 8);
            if (v1 == v0) {
                // 0x004a133c
                charge(ctx, 4);
                ld(v0, gp, -17048);  // 0x7CEA58
                v0 = v0 | 0x1;
                sd(v0, gp, -17048);  // 0x7CEA58
                backedge(ctx);
            }
            // 0x004a0ec8
            charge(ctx, 6);
            lw(v1, s0, 80);
            v0 = 3;
            v1 = v1 & 0xF000;
            v1 = srl(v1, 12);
            if (v1 == v0) {
                // 0x004a0ee0
                charge(ctx, 4);
                ld(v0, gp, -17048);  // 0x7CEA58
                v0 = v0 | 0x4;
                sd(v0, gp, -17048);  // 0x7CEA58
            }
        }
    }
    // 0x004a134c
    charge(ctx, 3);
    lw(v0, gp, -16952);  // 0x7CEAB8
    if (v0 == 0) {
        backedge(ctx);
        // 0x004a0efc
        charge(ctx, 4);
        ld(v1, gp, -17072);  // 0x7CEA40
        v0 = si(-2);
        v0 = v1 & v0;
        sd(v0, gp, -17072);  // 0x7CEA40
    } else {
        // 0x004a1358
        charge(ctx, 2);
        ld(v0, gp, -17072);  // 0x7CEA40
        backedge(ctx);
        // 0x004a0ef0
        charge(ctx, 3);
        v0 = v0 | 0x1;
        sd(v0, gp, -17072);  // 0x7CEA40
    }
    // 0x004a0f0c
    charge(ctx, 28);
    a0 = 0;
    a1 = 18;
    jal(ctx, 0x4A0F10u, gen::fn__rwDMAOpenVIFPkt_004d59d0);
    v0 = 0x10000000;
    v1 = 0;
    v0 = v0 | 0xF;
    pcpyld(a2, v1, v0);
    lw(a0, gp, -17148);  // 0x7CE9F4
    v1 = 0x6C010000;
    v0 = 0x1000000;
    v1 = v1 | 0x3FA;
    v0 = v0 | 0x404;  // &0x1000404
    v1 = dsll32(v1, 0);
    a1 = 0;
    v0 = v0 | v1;
    sq(a2, a0, 0);
    pcpyld(v0, v0, a1);
    sq(v0, a0, 16);
    lw(v1, gp, -17148);  // 0x7CE9F4
    lw(v0, gp, -16952);  // 0x7CEAB8
    v1 = addiu(v1, 32);
    sw(v1, gp, -17148);  // 0x7CE9F4
    lbu(a0, s2, 71);
    a0 = a0 ^ 0xFF;
    a0 = sltu(0, a0);
    v0 = a0 | v0;
    sw(a0, gp, -16956);  // 0x7CEAB4
    if (v0 == 0) {
        // 0x004a0f8c
        charge(ctx, 4);
        ld(a0, gp, -20272);  // 0x7CDDC0
        v0 = si(-65);
        v0 = a0 & v0;
        sd(v0, gp, -20272);  // 0x7CDDC0
    } else {
        // 0x004a0f7c
        charge(ctx, 4);
        ld(v0, gp, -20272);  // 0x7CDDC0
        v0 = v0 | 0x40;
        sd(v0, gp, -20272);  // 0x7CDDC0
    }
    // 0x004a0f9c
    charge(ctx, 43);
    v0 = 0x960000;
    a0 = lui(0xFC00);
    ld(a3, v0, 22688);  // 0x9658A0
    ld(a1, gp, -20272);  // 0x7CDDC0
    v0 = a0 | 0x7FFF;
    lbu(a0, s2, 41);
    a2 = dsll32(v0, 0);
    v0 = 0xFFFF;
    v0 = dsll(v0, 16);
    v0 = v0 | 0xFFFF;
    a2 = v0 | a2;
    v0 = 0x960000;
    a0 = dsll32(a0, 0);
    ld(v0, v0, 22696);  // 0x9658A8
    a0 = dsra32(a0, 0);
    a0 = a1 | a0;
    a0 = dsll32(a0, 0);
    a0 = dsra32(a0, 0);
    pcpyld(a2, zero, a2);
    a0 = a0 & 0x7FF;
    a2 = a3 & a2;
    a0 = dsll32(a0, 15);
    a0 = a2 | a0;
    pcpyld(a2, v0, a0);
    v0 = 0x960000;
    a0 = dsll32(v1, 0);
    sq(a2, v0, 22688);  // 0x9658A0
    a0 = dsra32(a0, 0);
    v0 = 0x6C010000;
    sq(a2, a0, 0);
    v0 = v0 | 0x3FB;
    a2 = 0;
    v1 = dsll32(v0, 0);
    v0 = 0x1000000;
    v0 = v0 | 0x404;  // &0x1000404
    v0 = v0 | v1;
    pcpyld(v0, v0, a2);
    sq(v0, a0, 16);
    lw(v1, gp, -17148);  // 0x7CE9F4
    v0 = a1 & 0x10;
    v1 = addiu(v1, 32);
    sw(v1, gp, -17148);  // 0x7CE9F4
    if (v0 == 0) {
        // 0x004a105c
        charge(ctx, 4);
        v0 = 0x3B800000;
        v0 = v0 | 0x8081;
        mtc1(v0, f12);
        a0 = addiu(s2, 68);
    } else {
        // 0x004a1048
        charge(ctx, 5);
        v0 = 0x3B010000;
        v0 = v0 | 0x1B50;
        mtc1(v0, f12);
        a0 = addiu(s2, 68);
    }
    // 0x004a106c
    charge(ctx, 33);
    pass.colour_at = write_ptr(ctx);
    jal(ctx, 0x4A106Cu, gen::fn_sub_49CAB0_0049cab0);
    v1 = 0x6C010000;
    v0 = 0x1000000;
    v1 = v1 | 0x3FC;
    v0 = v0 | 0x404;  // &0x1000404
    v1 = dsll32(v1, 0);
    a0 = 0;
    v0 = v0 | v1;
    pcpyld(v1, v0, a0);
    lw(v0, gp, -17148);  // 0x7CE9F4
    sq(v1, v0, 0);
    lw(v0, gp, -17148);  // 0x7CE9F4
    v1 = addiu(v0, 16);
    sw(v1, gp, -17148);  // 0x7CE9F4
    lwc1(f12, s2, 28);
    pass.surface_at = write_ptr(ctx);
    link(ctx, 0x4A10ACu);  // $ra first: the delay slot below depends on it
    lw(a0, s2, 60);
    call(ctx, gen::fn_sub_49CBD0_0049cbd0);
    lbu(a0, s2, 40);
    v0 = 0x6C030000;
    v1 = v0 | 0x3FD;
    a1 = 0;
    v0 = 0x1000000;
    v1 = dsll32(v1, 0);
    v0 = v0 | 0x404;  // &0x1000404
    v1 = v0 | v1;
    v0 = a0 & 0x7;
    pcpyld(a0, v1, a1);
    lw(v1, gp, -17148);  // 0x7CE9F4
    sq(a0, v1, 0);
    lw(v1, gp, -16876);  // 0x7CEB04
    if (v1 != 0) {
        // 0x004a10f0
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 != 0) {
            goto L_004a10fc;
        }
    L_004a1114:
        charge(ctx, 11);
        a0 = 0x960000;
        lw(a1, gp, -17148);  // 0x7CE9F4
        lq(a0, a0, 22832);  // 0x965930
        v1 = 0x960000;
        v0 = v0 | 0x8;
        sq(a0, a1, 16);
        lq(v1, v1, 22848);  // 0x965940
        sq(v1, a1, 32);
        lw(v1, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v1, 48);
        sw(v1, gp, -17148);  // 0x7CE9F4
        goto L_004a1140;
    }
L_004a10fc:
    charge(ctx, 3);
    lw(v1, gp, -20232);  // 0x7CDDE8
    if (v1 != 0) {
        // 0x004a1108
        charge(ctx, 3);
        v1 = v0 & 0x4;
        if (v1 == 0) {
            goto L_004a1360;
        }
        goto L_004a1114;
    }
L_004a1360:
    charge(ctx, 11);
    v1 = 0x960000;
    lw(a1, gp, -17148);  // 0x7CE9F4
    lq(a0, v1, 22800);  // 0x965910
    v1 = 0x960000;
    sq(a0, a1, 16);
    lq(v1, v1, 22816);  // 0x965920
    sq(v1, a1, 32);
    lw(v1, gp, -17148);  // 0x7CE9F4
    v1 = addiu(v1, 48);
    sw(v1, gp, -17148);  // 0x7CE9F4
    backedge(ctx);
L_004a1140:
    charge(ctx, 5);
    lw(a2, gp, -16964);  // 0x7CEAAC
    a1 = 3;
    sw(zero, gp, -16884);  // 0x7CEAFC
    a0 = 0;
    if (a2 == a1) {
        // 0x004a138c
        charge(ctx, 3);
        a0 = 32;
        sw(a0, gp, -16884);  // 0x7CEAFC
        backedge(ctx);
    }
    // 0x004a1154
    charge(ctx, 17);
    lwu(a1, gp, -16880);  // 0x7CEB00
    a0 = dsll32(a0, 0);
    v0 = dsll32(v0, 0);
    a0 = dsrl32(a0, 0);
    v0 = dsrl32(v0, 0);
    a1 = dsll32(a1, 0);
    a0 = a1 | a0;
    pcpyld(a0, a0, v0);
    v0 = dsll32(v1, 0);
    v0 = dsra32(v0, 0);
    sq(a0, v0, 0);
    lw(v0, gp, -17148);  // 0x7CE9F4
    v1 = addiu(v0, 16);
    sw(v1, gp, -17148);  // 0x7CE9F4
    lw(v0, s2, 64);
    if (v0 == 0) {
        // 0x004a1398
        charge(ctx, 25);
        a1 = dsll32(v1, 0);
        v0 = 0x50000000;
        a1 = dsra32(a1, 0);
        v0 = v0 | 0x2;
        sq(zero, a1, 0);
        v0 = dsll32(v0, 0);
        v1 = 0;
        sq(zero, a1, 16);
        pcpyld(v0, v0, v1);
        sq(v0, a1, 32);
        a0 = 14;
        v0 = 0x10000000;
        v1 = dsll32(v0, 0);
        v0 = 0x8001;
        v1 = v0 | v1;
        pcpyld(v1, a0, v1);
        sq(v1, a1, 48);
        v0 = 71;
        ld(v1, gp, -17072);  // 0x7CEA40
        pcpyld(v0, v0, v1);
        sq(v0, a1, 64);
        lw(v0, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v0, 80);
        sw(v1, gp, -17148);  // 0x7CE9F4
        backedge(ctx);
    } else {
        // 0x004a1198
        charge(ctx, 30);
        v0 = 0x50000000;
        a0 = 0;
        v0 = v0 | 0x4;
        v0 = dsll32(v0, 0);
        pcpyld(v0, v0, a0);
        a1 = dsll32(v1, 0);
        a0 = 14;
        a1 = dsra32(a1, 0);
        sq(v0, a1, 0);
        v0 = 0x10000000;
        v1 = dsll32(v0, 0);
        v0 = 0x8003;
        v0 = v0 | v1;
        pcpyld(v0, a0, v0);
        sq(v0, a1, 16);
        ld(v1, gp, -17072);  // 0x7CEA40
        v0 = 71;
        pcpyld(v0, v0, v1);
        sq(v0, a1, 32);
        ld(v1, gp, -17040);  // 0x7CEA60
        v0 = 20;
        pcpyld(v0, v0, v1);
        sq(v0, a1, 48);
        ld(v1, gp, -17048);  // 0x7CEA58
        v0 = 8;
        pcpyld(v0, v0, v1);
        sq(v0, a1, 64);
        lw(v0, gp, -17148);  // 0x7CE9F4
        v1 = addiu(v0, 80);
        sw(v1, gp, -17148);  // 0x7CE9F4
    }
    // 0x004a1210
    charge(ctx, 16);
    lbu(v0, s2, 40);
    v1 = v0 & 0x20;
    v0 = v0 & 0x18;
    v1 = sra(v1, 5);
    v0 = sra(v0, 2);
    v0 = v1 | v0;
    sb(v0, s2, 43);
    lw(v1, s2, 4);
    lbu(a0, s2, 43);
    lw(v0, gp, -16888);  // 0x7CEAF8
    lw(v1, v1, 24);
    a0 = sll(a0, 2);
    v1 = addu(v1, a0);
    lw(a0, v1, 0);
    pass.program = a0.u();
    pass.uploaded = v0 != a0;
    if (v0 != a0) {
        // 0x004a1250
        charge(ctx, 13);
        v0 = dsll32(a0, 0);
        a1 = 0;
        v0 = dsrl32(v0, 0);
        v1 = dsll32(v0, 0);
        v0 = 0x50000000;
        v0 = v1 | v0;
        pcpyld(v1, a1, v0);
        lw(v0, gp, -17148);  // 0x7CE9F4
        sq(v1, v0, 0);
        lw(v0, gp, -17148);  // 0x7CE9F4
        sw(a0, gp, -16888);  // 0x7CEAF8
        v1 = addiu(v0, 16);
        sw(v1, gp, -17148);  // 0x7CE9F4
    }
    // 0x004a1284
    charge(ctx, 21);
    lw(a0, s2, 48);
    a2 = 0x2000000;
    lw(v1, s2, 4);
    a1 = 0x3000000;
    v0 = 0x50000000;
    lw(t0, a0, 0);
    lw(a3, v1, 20);
    a0 = addiu(t0, 24);
    lwu(v1, t0, 32);
    a2 = a3 | a2;
    a2 = dsll32(a2, 0);
    a1 = a2 | a1;
    v1 = dsll32(v1, 0);
    v0 = v1 | v0;
    pcpyld(a1, a1, v0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    v0 = 0x10000;
    sq(a1, v1, 0);
    lw(v1, gp, -17148);  // 0x7CE9F4
    v1 = addiu(v1, 16);
    sw(v1, gp, -17148);  // 0x7CE9F4
    pass.res_entry = t0.u();
    pass.vif_offset = a3.u();
    for (;;) {
        // 0x004a12d8
        charge(ctx, 7);
        di(ctx);
        sync(ctx, 16);
        mfc0(v1, 12);
        v1 = v1 & v0;
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x004a12f4
    charge(ctx, 11);
    lw(v0, a0, 0);
    v0 = addiu(v0, 1);
    sw(v0, a0, 0);
    ei(ctx);
    v0 = 1;
    lw(v1, a0, 4);
    v1 = addiu(v1, 1);
    sw(v1, a0, 4);
    lw(v1, a0, 4);
    if (v1 == v0) {
        // 0x004a13fc
        charge(ctx, 4);
        jal(ctx, 0x4A13FCu, gen::fn__rwDMAAddPURef_004d51c0);
        backedge(ctx);
    }
    // 0x004a1320
    charge(ctx, 2);
    v0 = 1;
    report_bridge(ctx, s2.u(), pass);
    // 0x004a140c
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0046EA80 sub_46EA80 -- 132 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_46EA80: the skin / MatFX material bridge dispatcher ($a0 = PipeData): the material's effect (material +
// gp-17848 -> +128, 0 without the extension) picks the bridge in the table 0x6B4EE4; for the call the material
// pipeline's code array (+24) is advanced by four entries per effect, then restored.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_46EA80(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jalr, hg::ld, hg::lq, hg::lw, hg::sd, hg::sll,
          hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046ea80
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, 44);
    lw(v0, gp, -17848);  // 0x7CE738
    lw(v1, v1, 8);
    v0 = addu(v1, v0);
    lw(v0, v0, 0);
    s0 = a0;
    if (v0 == 0) {
        // 0x0046eab4
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0046eaac
        charge(ctx, 2);
        lw(v0, v0, 128);
    }
    // 0x0046eab8
    charge(ctx, 19);
    lw(a2, s0, 4);
    a1 = sll(v0, 4);
    v1 = sll(v0, 2);
    v0 = 0x6B0000;
    v0 = addiu(v0, 20196);  // &0x6B4EE4
    v0 = addu(v0, v1);
    lw(s1, a2, 24);
    v1 = addu(s1, a1);
    sw(v1, a2, 24);
    lw(v0, v0, 0);
    a0 = s0;
    jalr(ctx, 0x46EAE0u, v0.u());
    lw(v1, s0, 4);
    sw(s1, v1, 24);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0049F5D0 PS2AllNodeBody -- 1220 bytes; frame 0x160: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq), s4 sp+0x110
// PS2AllNodeBody [PS2AllNodeBody]: ($a0 the node, $a1 the parameters: +0 the object). Frame: the PipeData at sp+272
// (mesh.h, pd), the object matrix at sp+208 with its reference at sp+192, the global default material pipeline at
// sp+176, the mesh header at sp+160. The light block restarts at 0x95DFC0 + 16 (count 0). After the set-up
// callback (node private +16; 0 -> nothing drawn, returns 1) and a morphing object's fast-morph mark (pd +36 = 2):
// the light block header -- count -1: none (count 0); 0: the node's default block (node private +36), 2 qw;
// -5: 4; else the terminator quadword (default block +16) and count + 1 -- then the header quadword at
// 0x95DFC0 (STCYCL 4,4, UNPACK V4-32 of count qw to node private +28) and openVU1SetupPktNew(matrix, block,
// count). Per mesh (12-byte records): the material pipeline (node +24, else material +8, else the global
// default) and its private data (pipeline +8 -> +20: callbacks [0] instance test, [3] bridge, [4] post-mesh),
// the PipeData mesh fields (material colour from the material when modulated, else the default bytes at
// gp-20712), the instance test and PS2AllNodeInstance when the instance flags (& 0xE) say so (failure:
// returns 0), the resEntry moved to the head of the resource list, the bridge, the post-mesh callback; then
// the object's post callback (node private +20). Returns 1.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void PS2AllNodeBody(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll, hg::dsll32, hg::dsra32, hg::dsrl32,
          hg::enter, hg::jal, hg::jalr, hg::lbu, hg::ld, hg::lhu, hg::lq, hg::lw, hg::lwu, hg::pcpyld, hg::sb,
          hg::sd, hg::si, hg::slti, hg::sltu, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0049f5d0
    enter(ctx, 55);  // entry check point + this block's cycles
    sp = addiu(sp, -0x160);
    v0 = 0x960000;
    sd(ra, sp, 0x90);
    v0 = addiu(v0, 112);  // &0x960070
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = addiu(sp, 0x130);
    sq(s1, sp, 0x10);
    s2 = addiu(sp, 0x134);
    sq(s0, sp, 0x0);
    s1 = addiu(sp, 0x11C);
    lw(a2, gp, -16840);  // 0x7CEB28
    s0 = addiu(sp, 0x120);
    lw(v1, a1, 0);
    lw(s4, a0, 20);
    a1 = addu(v0, a2);
    v0 = addiu(sp, 0x114);
    a0 = 1;
    sw(zero, v0, 0);
    lw(v0, a1, 68);
    sw(v1, sp, 0x118);
    sw(s4, sp, 0x110);
    sw(a0, s3, 0);
    sw(zero, sp, 0x128);
    sw(zero, sp, 0x12C);
    sw(v0, sp, 0xB0);
    a1 = addiu(sp, 0xC0);
    v0 = 255;
    sw(zero, s2, 0);
    sb(v0, sp, 0x139);
    v0 = 0x960000;
    sw(zero, s1, 0);
    v0 = addiu(v0, -8256);  // &0x95DFC0
    sw(zero, s0, 0);
    v1 = addiu(v0, 16);  // &0x95DFD0
    sw(zero, gp, -17520);  // 0x7CE880
    v0 = addiu(sp, 0x124);
    sw(v1, gp, -17516);  // 0x7CE884
    sw(a0, v0, 0);
    v0 = addiu(sp, 0xD0);
    sw(v0, sp, 0xC0);
    v0 = addiu(sp, 0x138);
    sb(zero, v0, 0);
    v0 = addiu(sp, 0x13A);
    sb(zero, v0, 0);
    lw(v0, s4, 16);
    a0 = addiu(sp, 0x110);
    jalr(ctx, 0x49F69Cu, v0.u());
    if (v0 == 0) {
        // 0x0049f9c4
        charge(ctx, 2);
        v0 = 1;
    } else {
        // 0x0049f6ac
        charge(ctx, 4);
        lw(v0, s3, 0);
        at = slti(v0, 2);
        if (at == 0) {
            // 0x0049f9cc
            charge(ctx, 3);
            v0 = 2;
            sw(v0, s2, 0);
            backedge(ctx);
        }
        // 0x0049f6bc
        charge(ctx, 3);
        lw(v1, gp, -17520);  // 0x7CE880
        if (v1 == 0) {
            // 0x0049f9d8
            charge(ctx, 5);
            lw(v1, s4, 36);
            v0 = 2;
            sw(v1, gp, -17516);  // 0x7CE884
            sw(v0, gp, -17520);  // 0x7CE880
            backedge(ctx);
        } else {
            // 0x0049f6c8
            charge(ctx, 3);
            v0 = si(-1);
            if (v1 == v0) {
                // 0x0049f9ec
                charge(ctx, 3);
                sw(zero, gp, -17520);  // 0x7CE880
                v0 = 0;
                backedge(ctx);
            } else {
                // 0x0049f6d4
                charge(ctx, 3);
                v0 = si(-5);
                if (v1 != v0) {
                    // 0x0049f6ec
                    charge(ctx, 7);
                    lw(v1, s4, 36);
                    lw(v0, gp, -17516);  // 0x7CE884
                    lq(v1, v1, 16);
                    sq(v1, v0, 0);
                    lw(v0, gp, -17520);  // 0x7CE880
                    v0 = addiu(v0, 1);
                    sw(v0, gp, -17520);  // 0x7CE880
                } else {
                    // 0x0049f6e0
                    charge(ctx, 3);
                    v0 = 4;
                    sw(v0, gp, -17520);  // 0x7CE880
                }
                // 0x0049f708
                charge(ctx, 21);
                v1 = 0x960000;
                v0 = dsll32(v0, 0);
                v1 = addiu(v1, -8256);  // &0x95DFC0
                v0 = dsrl32(v0, 0);
                sw(v1, gp, -17516);  // 0x7CE884
                a2 = 0;
                v1 = dsll(v0, 16);
                lwu(a0, s4, 28);
                v0 = 0x6C000000;
                a1 = v1 | v0;
                v0 = 0x1000000;
                v1 = v0 | 0x404;  // &0x1000404
                lw(v0, gp, -17516);  // 0x7CE884
                a0 = a1 | a0;
                a0 = dsll32(a0, 0);
                v1 = a0 | v1;
                pcpyld(v1, v1, a2);
                sq(v1, v0, 0);
                lw(v0, gp, -17520);  // 0x7CE880
                v0 = addiu(v0, 1);
                sw(v0, gp, -17520);  // 0x7CE880
            }
        }
        // 0x0049f75c
        charge(ctx, 17);
        lw(a0, sp, 0xC0);
        a2 = dsll32(v0, 0);
        lw(a1, gp, -17516);  // 0x7CE884
        a2 = dsra32(a2, 0);
        jal(ctx, 0x49F768u, gen::fn_openVU1SetupPktNew_004ec2b0);
        lw(v0, s1, 0);
        fp = 0;
        lw(s6, s0, 0);
        s3 = 0;
        s5 = 0;
        lhu(v1, v0, 4);
        lw(a0, v0, 12);
        sw(v0, sp, 0xA0);
        at = sltu(0, v1);
        v0 = addu(a0, v0);
        s2 = addiu(v0, 16);
        if (at != 0) {
            // 0x0049f7a0
            charge(ctx, 3);
            s1 = addiu(sp, 0x140);
            s0 = addiu(sp, 0x144);
            s7 = addiu(sp, 0x154);
            for (;;) {
                // 0x0049f7ac
                charge(ctx, 6);
                lw(a3, s4, 24);
                lbu(a0, gp, -20711);  // 0x7CDC09
                lbu(v1, gp, -20710);  // 0x7CDC0A
                lbu(v0, gp, -20709);  // 0x7CDC0B
                lbu(a1, gp, -20712);  // 0x7CDC08
                if (a3 == 0) {
                    // 0x0049f9f8
                    charge(ctx, 4);
                    lw(a2, s2, 8);
                    lw(a3, a2, 8);
                    if (a3 != 0) {
                        backedge(ctx);
                    } else {
                        // 0x0049fa08
                        charge(ctx, 2);
                        lw(a3, sp, 0xB0);
                        backedge(ctx);
                    }
                } else {
                    // 0x0049f7c4
                    charge(ctx, 1);
                }
                // 0x0049f7c8
                charge(ctx, 2);
                if (a3 != fp) {
                    // 0x0049f7d0
                    charge(ctx, 6);
                    lw(a2, a3, 8);
                    fp = a3;
                    lw(s3, a2, 20);
                    a2 = addiu(sp, 0x114);
                    sw(s3, a2, 0);
                }
                // 0x0049f7e8
                charge(ctx, 32);
                a2 = addiu(sp, 0x13C);
                sw(s2, a2, 0);
                a2 = addiu(sp, 0x148);
                sw(zero, a2, 0);
                a2 = addiu(s6, 4);
                sw(a2, s1, 0);
                a2 = addiu(sp, 0x124);
                lw(t1, a2, 0);
                a2 = addiu(sp, 0x138);
                sw(t1, s0, 0);
                lbu(t0, a2, 0);
                a2 = addiu(sp, 0x13A);
                t0 = t0 & 0x1F;
                lbu(a3, a2, 0);
                a2 = addiu(sp, 0x13B);
                sb(t0, a2, 0);
                lw(a2, s2, 8);
                t0 = addiu(a2, 12);
                a2 = addiu(sp, 0x14C);
                sw(t0, a2, 0);
                lw(a2, s2, 8);
                lw(t0, a2, 0);
                sb(a1, s7, 0);
                a2 = addiu(sp, 0x150);
                a1 = addiu(sp, 0x155);
                sw(t0, a2, 0);
                sb(a0, a1, 0);
                a0 = addiu(sp, 0x156);
                sb(v1, a0, 0);
                v1 = addiu(sp, 0x157);
                sb(v0, v1, 0);
                if (a3 != 0) {
                    // 0x0049fa10
                    charge(ctx, 10);
                    lw(v0, s2, 8);
                    lbu(a1, v0, 4);
                    lbu(a0, v0, 5);
                    lbu(v1, v0, 6);
                    lbu(v0, v0, 7);
                    sb(a1, s7, 0);
                    sb(a0, s7, 1);
                    sb(v1, s7, 2);
                    sb(v0, s7, 3);
                    backedge(ctx);
                }
                // 0x0049f868
                charge(ctx, 5);
                v0 = addiu(sp, 0x124);
                lw(v1, v0, 0);
                v0 = 1;
                if (v1 != v0) {
                    // 0x0049f87c
                    charge(ctx, 9);
                    v0 = addiu(sp, 0x114);
                    lw(v1, s1, 0);
                    lw(a0, v0, 0);
                    lw(v0, s0, 0);
                    v0 = v0 | 0x1;
                    sw(v0, s0, 0);
                    lw(v0, v1, 0);
                    if (v0 == 0) {
                        // 0x0049fa38
                        charge(ctx, 6);
                        lw(v1, s0, 0);
                        v0 = 0x70000;
                        v0 = v0 | 0xFFF8;
                        v0 = v1 | v0;
                        sw(v0, s0, 0);
                        backedge(ctx);
                    } else {
                        // 0x0049f8a0
                        charge(ctx, 3);
                        lw(v0, a0, 0);
                        if (v0 != 0) {
                            // 0x0049f8ac
                            charge(ctx, 3);
                            a0 = addiu(sp, 0x110);
                            jalr(ctx, 0x49F8ACu, v0.u());
                        }
                    }
                    // 0x0049f8b8
                    charge(ctx, 4);
                    lw(v0, s0, 0);
                    v0 = v0 & 0xE;
                    if (v0 != 0) {
                        // 0x0049fa50
                        charge(ctx, 4);
                        a0 = addiu(sp, 0x110);
                        jal(ctx, 0x49FA50u, gen::fn_PS2AllNodeInstance_0049faa0);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        goto L_0049f8c8;
                    }
                L_0049f8c8:
                    charge(ctx, 5);
                    lw(v0, s1, 0);
                    lw(v0, v0, 0);
                    lw(a0, v0, 0);
                    if (a0 != 0) {
                        // 0x0049f8dc
                        charge(ctx, 35);
                        lw(v1, v0, 4);
                        sw(a0, v1, 0);
                        v0 = 0x960000;
                        lw(v1, s1, 0);
                        v0 = addiu(v0, 112);  // &0x960070
                        lw(v1, v1, 0);
                        lw(a0, v1, 4);
                        lw(v1, v1, 0);
                        sw(a0, v1, 4);
                        lw(a0, gp, -17408);  // 0x7CE8F0
                        lw(v1, s1, 0);
                        a0 = addu(v0, a0);
                        lw(a0, a0, 36);
                        lw(v1, v1, 0);
                        lw(a0, a0, 0);
                        sw(a0, v1, 0);
                        lw(a0, gp, -17408);  // 0x7CE8F0
                        lw(v1, s1, 0);
                        a0 = addu(v0, a0);
                        lw(a0, a0, 36);
                        lw(v1, v1, 0);
                        sw(a0, v1, 4);
                        lw(v1, gp, -17408);  // 0x7CE8F0
                        lw(a0, s1, 0);
                        v1 = addu(v0, v1);
                        lw(v1, v1, 36);
                        lw(a0, a0, 0);
                        lw(v1, v1, 0);
                        sw(a0, v1, 4);
                        lw(v1, gp, -17408);  // 0x7CE8F0
                        lw(a0, s1, 0);
                        v0 = addu(v0, v1);
                        lw(a0, a0, 0);
                        lw(v0, v0, 36);
                        sw(a0, v0, 0);
                    }
                }
                // 0x0049f968
                charge(ctx, 8);
                v0 = addiu(sp, 0x114);
                lw(v0, v0, 0);
                lw(v0, v0, 12);
                a0 = addiu(sp, 0x110);
                jalr(ctx, 0x49F974u, v0.u());
                lw(v0, s3, 16);
                s2 = addiu(s2, 12);
                if (v0 != 0) {
                    // 0x0049f988
                    charge(ctx, 2);
                    a0 = addiu(sp, 0x110);
                    jalr(ctx, 0x49F988u, v0.u());
                }
                // 0x0049f990
                charge(ctx, 6);
                lw(v0, sp, 0xA0);
                s5 = addiu(s5, 1);
                lhu(v0, v0, 4);
                v0 = sltu(s5, v0);
                s6 = addiu(s6, 4);
                if (v0 == 0) {
                    goto L_0049f9a8;
                }
                backedge(ctx);
            }
            // 0x0049fa60
            charge(ctx, 1);
            v0 = 0;
            // 0x0049fa64 (the shared epilogue, written out on this path)
            charge(ctx, 12);
            ld(ra, sp, 0x90);
            lq(fp, sp, 0x80);
            lq(s7, sp, 0x70);
            lq(s6, sp, 0x60);
            lq(s5, sp, 0x50);
            lq(s4, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x160);
            return;
        }
    L_0049f9a8:
        charge(ctx, 3);
        lw(v0, s4, 20);
        if (v0 != 0) {
            // 0x0049f9b4
            charge(ctx, 2);
            a0 = addiu(sp, 0x110);
            jalr(ctx, 0x49F9B4u, v0.u());
        }
        // 0x0049f9bc
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x0049fa64 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x90);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x160);
}

// 0x00490860 AtomicDefaultRenderCallBack -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// AtomicDefaultRenderCallBack [AtomicDefaultRenderCallBack]: RxPipelineExecute(the atomic's pipeline (+108) or the PS2All
// module's default atomic pipeline (+60), atomic, 1). Returns the atomic, 0 when the pipeline failed.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void AtomicDefaultRenderCallBack(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00490860
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 108);
    if (a0 == 0) {
        // 0x00490898
        charge(ctx, 6);
        lw(v1, gp, -16840);  // 0x7CEB28
        v0 = 0x960000;
        v0 = addiu(v0, 112);  // &0x960070
        v0 = addu(v0, v1);
        lw(a0, v0, 60);
        backedge(ctx);
    }
    // 0x0049087c
    charge(ctx, 5);
    a1 = s0;
    a2 = 1;
    jal(ctx, 0x490880u, gen::fn_RxPipelineExecute_004f2e70);
    if (v0 == 0) {
        // 0x004908b0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00490890
        charge(ctx, 2);
        v0 = s0;
    }
    // 0x004908b4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

void mesh::set_draw_observer(const DrawObserver* observer) noexcept { g_observer = observer; }
const mesh::DrawObserver* mesh::draw_observer() noexcept { return g_observer; }

}  // namespace p3fes::game

// --- the recompiled program's entry points (the bodies read their arguments from the registers) -----------
namespace p3fes::recomp_gen {
namespace g = ::p3fes::game;

void fn_sub_49CA50_0049ca50(p3fes::EEContext& ctx) { g::Cpu(ctx).filter_shadow(); }

}  // namespace p3fes::recomp_gen
