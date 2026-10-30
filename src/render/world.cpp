// RenderWare's world on the PS2 driver: atomics, world sectors, clump render, geometry locks, the tri-strip and mesh
// sort helpers, the PS2All instancing (vertex data -> VIF UNPACK clusters) and the MatFX / skin / PDS set-up (world.h
// has the data flow; docs/ANALYSIS/22_rendering.md sections 2.2, 2.3, 3.1 and 7.3 c7 / c8).
//
// Cycle model (ADR-0013): every charge() below is one `ctx.cycles += N` block of the recompiled body in
// recomp/generated; backedge() sits wherever that body has a check point on a backward jump -- loops, and the
// backward `goto`s of the compiler's block layout (the shared tails the branches return to), which the hand versions
// keep as explicit check points. A block that ends in a `jal` is charged in full before the call (the recompiler keeps
// the call inside its block). A `jr` switch is a C++ switch with the per-case block costs; the register that held the
// table entry keeps it.
//
// Registers: register-faithful (world.h). Each body runs on a Cpu view of the guest context: one variable per GPR
// (64-bit writes keep bits 64..127, as the EE does; lq / MMI results write all 128), the FPU / HI-LO operations
// through the runtime's own instruction semantics, prologue spills and epilogue reloads on the guest stack. A branch
// is decided before its delay slot's instruction executes (as the EE does); where the delay slot writes a register
// the condition reads, the condition is taken first into a local. Guest structure offsets are named in world.h and
// in the comments.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 38 of the 45 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: faults only 15, the hand version terminated the
// host on a random world 9, callee frames 9, frame/spills 5); the others are the hand-written versions this
// header describes.
//
// Readability pass (read_render, 2026-10-22): the 38 generated bodies keep every statement, charge, check point and
// call of p3fes_handgen's output in the same order on every path (proved per function by a bisimulation of the two
// statement graphs, and by the faithfulness audit); on top of it they name what they touch -- render_view.h for the
// records and addresses more than one render file reads (`hi()` / `lo()` / `la()` for a lui pair, `gp_off()`, the
// matrix, frame, camera, raster, image, texture, atomic, geometry, sector, Rt2d and PS2All records, the walk tables,
// the driver globals) --, say what each block does, and replace the generator's gotos by if / else / break
// (a `do { ... } while (false)` block where several paths leave a ladder early, local lambdas for the shared tails
// such as the epilogue); none is left. Each function's comment gives its role and, for a `sub_` name, a proposed
// name in brackets.
#include "p3fes/game/world.h"

#include "p3fes_recomp_rt.h"

#include <initializer_list>
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/render_view.h"
#include "p3fes/game/rw_builders.h"  // rwb:: driver $gp words
#include "p3fes/game/rw_leaves.h"    // rwl:: RW globals and module offsets
#include "p3fes/game/sky.h"          // sky:: GS shadows and driver globals

namespace p3fes::recomp_gen {
void fn_RpPDSGetPipe_0046a890(p3fes::EEContext&);   // PDS pipeline by id
void fn_RxPipelineExecute_004f2e70(p3fes::EEContext&);
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);     // RwFrameGetLTM
void fn_sub_4CAE30_004cae30(p3fes::EEContext&);     // RwFrame dirty test
void fn_sub_4C6BE0_004c6be0(p3fes::EEContext&);     // sphere by a matrix
void fn_sub_4C9DF0_004c9df0(p3fes::EEContext&);     // camera frustum: sphere test
void fn_sub_4C2F30_004c2f30(p3fes::EEContext&);     // matrix product
void fn_sub_4C2FB0_004c2fb0(p3fes::EEContext&);
void fn_sub_4C32A0_004c32a0(p3fes::EEContext&);     // matrix inverse
void fn_sub_4C2090_004c2090(p3fes::EEContext&);
void fn_sub_4C2120_004c2120(p3fes::EEContext&);
void fn_sub_495C80_00495c80(p3fes::EEContext&);     // mesh header destroy
void fn_sub_495C20_00495c20(p3fes::EEContext&);
void fn_sub_498720_00498720(p3fes::EEContext&);     // mesh header build (RwMalloc through the RW globals)
void fn_sub_49C330_0049c330(p3fes::EEContext&);     // frustum sector walk
void fn_sub_49FF10_0049ff10(p3fes::EEContext&);     // one light into the light block (render_mesh)
void fn_sub_4A24A0_004a24a0(p3fes::EEContext&);
void fn_worldForAllLights_00499c20(p3fes::EEContext&);
void fn_worldSectorForAllLights_00499ca0(p3fes::EEContext&);
void fn_sub_49E5A0_0049e5a0(p3fes::EEContext&);     // resEntry array (RwMalloc / RwFree)
void fn_sub_4A3F70_004a3f70(p3fes::EEContext&);     // world sector frustum test
void fn_sub_4AAE60_004aae60(p3fes::EEContext&);
void fn_sub_4AB8C0_004ab8c0(p3fes::EEContext&);     // Rt2d: flatten a path
void fn_sub_4ABD50_004abd50(p3fes::EEContext&);
void fn_sub_4AC020_004ac020(p3fes::EEContext&);     // Rt2d: path bounds
void fn_sub_4F2710_004f2710(p3fes::EEContext&);     // packet record
void fn_sub_46BAB0_0046bab0(p3fes::EEContext&);
void fn_sub_46BD00_0046bd00(p3fes::EEContext&);
void fn_sub_4CBE00_004cbe00(p3fes::EEContext&);     // RwImage: create (w, h, depth)
void fn_sub_4CBF20_004cbf20(p3fes::EEContext&);     // RwImage: allocate the pixels
void fn_sub_4CBEB0_004cbeb0(p3fes::EEContext&);     // RwImage: destroy
void fn_sub_4CDC70_004cdc70(p3fes::EEContext&);     // RwImage from a raster
void fn_sub_4CEC10_004cec10(p3fes::EEContext&);     // RwImage resample
void fn_sub_4CC0A0_004cc0a0(p3fes::EEContext&);
void fn_sub_4CC1D0_004cc1d0(p3fes::EEContext&);
void fn_sub_4CDD50_004cdd50(p3fes::EEContext&);     // raster format for an image
void fn_sub_4CE0F0_004ce0f0(p3fes::EEContext&);     // RwRaster create
void fn_sub_4CDCE0_004cdce0(p3fes::EEContext&);     // raster from an image
void fn_sub_4D0E40_004d0e40(p3fes::EEContext&);     // RwTexture create
void fn_sub_4D0FD0_004d0fd0(p3fes::EEContext&);     // RwTexture set name
void fn_sub_4F3F70_004f3f70(p3fes::EEContext&);     // the object's pipeline slot array
void fn_sub_4F3EC0_004f3ec0(p3fes::EEContext&);     // ... created
void fn_sub_491100_00491100(p3fes::EEContext&);
void fn_atomicGetWorldBoundingSphere_004912b0(p3fes::EEContext&);
void fn_worldSectorRenderDispatch_00499230(p3fes::EEContext&);
void fn_worldForAllSectors_0049a870(p3fes::EEContext&);
void fn_worldSectorGetWorld_0049a170(p3fes::EEContext&);
void fn_sub_4687E0_004687e0(p3fes::EEContext&);
void fn_sub_468720_00468720(p3fes::EEContext&);
void fn_ps2AllAtomicInstance_004a1430(p3fes::EEContext&);
void fn_ps2AllSectorInstance_004a42f0(p3fes::EEContext&);
void fn_skinInstanceWeights_0046b1b0(p3fes::EEContext&);
void fn_ps2AllIm3DInstance_004a2bb0(p3fes::EEContext&);
void fn_triStripTriangleEdge_00496e80(p3fes::EEContext&);
void fn_triStripTakeTriangle_00496f60(p3fes::EEContext&);
void fn_ps2AllInstanceSizes_0049d4d0(p3fes::EEContext&);
void fn_ps2AllInstanceDmaChain_0049dc70(p3fes::EEContext&);
void fn_SyncDCache_00503a58(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace rview;  // render_view.h: la / hi / lo / gp_off / flt and the shared RW records

namespace {

namespace core = ee::core;
namespace gen = ::p3fes::recomp_gen;
using namespace world;

// --- R5900 integer results (32-bit operations sign-extend into the 64-bit register) ----------------------
constexpr u64 sx(u32 v) { return core::sext32(v); }
constexpr u64 addiu(u64 a, s32 i) { return core::add32i(a, i); }
constexpr u64 lui(u32 i) { return core::lui(i); }
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

// FPR numbers.
enum : unsigned {
    F0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15,
    F16, F17, F18, F19, F20, F21, F22, F23, F24, F25, F26, F27, F28, F29, F30, F31
};

// The guest machine as the bodies see it.
class Cpu {
public:
    explicit Cpu(EEContext& ctx) noexcept : c(ctx) {}

    EEContext& c;
    Gpr zero{c, 0}, at{c, 1}, v0{c, 2}, v1{c, 3}, a0{c, 4}, a1{c, 5}, a2{c, 6}, a3{c, 7};
    Gpr t0{c, 8}, t1{c, 9}, t2{c, 10}, t3{c, 11}, t4{c, 12}, t5{c, 13}, t6{c, 14}, t7{c, 15};
    Gpr s0{c, 16}, s1{c, 17}, s2{c, 18}, s3{c, 19}, s4{c, 20}, s5{c, 21}, s6{c, 22}, s7{c, 23};
    Gpr t8{c, 24}, t9{c, 25}, gp{c, 28}, sp{c, 29}, s8{c, 30}, ra{c, 31};

    // virtual time
    void enter(u64 n) { guest::enter(c, n); }  // not noexcept: a check point may raise a fatal event
    void charge(u64 n) noexcept { guest::charge(c, n); }
    void backedge() { guest::backedge(c); }

    // loads / stores (addresses are 32-bit; LQ / SQ force a quadword boundary)
    u64 lw(u64 a) const noexcept { return sx(guest::load<u32>(c, w(a))); }
    u64 lwu(u64 a) const noexcept { return guest::load<u32>(c, w(a)); }
    u64 lh(u64 a) const noexcept { return core::sext16(guest::load<u16>(c, w(a))); }
    u64 lhu(u64 a) const noexcept { return guest::load<u16>(c, w(a)); }
    u64 lb(u64 a) const noexcept { return core::sext8(guest::load<u8>(c, w(a))); }
    u64 lbu(u64 a) const noexcept { return guest::load<u8>(c, w(a)); }
    u64 ld(u64 a) const noexcept { return guest::load<u64>(c, w(a)); }
    void lq(Gpr& d, u64 a) noexcept { core::set_gpr128(c, d.r, guest::load<u128>(c, w(a) & ~15u)); }
    void sw(u64 a, u64 v) noexcept { guest::store<u32>(c, w(a), w(v)); }
    void sh(u64 a, u64 v) noexcept { guest::store<u16>(c, w(a), static_cast<u16>(v)); }
    void sb(u64 a, u64 v) noexcept { guest::store<u8>(c, w(a), static_cast<u8>(v)); }
    void sd(u64 a, u64 v) noexcept { guest::store<u64>(c, w(a), v); }
    void sq(u64 a, const Gpr& v) noexcept { guest::store<u128>(c, w(a) & ~15u, c.gpr[v.r]); }
    u32 gpw(s32 off) const noexcept { return gp.u() + static_cast<u32>(off); }

    // FPU (the runtime's instruction semantics: EE singles, ACC, FCR31 flags)
    void lwc1(unsigned f, u64 a) noexcept { c.fpr[f] = guest::load<u32>(c, w(a)); }
    void swc1(unsigned f, u64 a) noexcept { guest::store<u32>(c, w(a), c.fpr[f]); }
    void mtc1(const Gpr& g, unsigned f) noexcept { rt::mtc1(c, g.r, f); }
    void mfc1(Gpr& g, unsigned f) noexcept { rt::mfc1(c, g.r, f); }
    void mov_s(unsigned d, unsigned s) noexcept { rt::mov_s(c, d, s); }
    void cvt_w_s(unsigned d, unsigned s) noexcept { rt::cvt_w_s(c, d, s); }
    void sub_s(unsigned d, unsigned s, unsigned t) noexcept { rt::sub_s(c, d, s, t); }
    void mul_s(unsigned d, unsigned s, unsigned t) noexcept { rt::mul_s(c, d, s, t); }
    void div_s(unsigned d, unsigned s, unsigned t) noexcept { rt::div_s(c, d, s, t); }
    void sqrt_s(unsigned d, unsigned t) noexcept { rt::sqrt_s(c, d, t); }
    void mula_s(unsigned s, unsigned t) noexcept { rt::mula_s(c, s, t); }
    void madda_s(unsigned s, unsigned t) noexcept { rt::madda_s(c, s, t); }
    void madd_s(unsigned d, unsigned s, unsigned t) noexcept { rt::madd_s(c, d, s, t); }
    void c_lt_s(unsigned s, unsigned t) noexcept { rt::c_lt_s(c, s, t); }
    bool cop1_cond() const noexcept { return rt::cop1_cond(c); }

    // HI/LO, MMI, conditional moves
    void mult(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::mult(c, d.r, s.r, t.r); }
    void mult1(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::mult1(c, d.r, s.r, t.r); }
    void div(const Gpr& s, const Gpr& t) noexcept { rt::div(c, s.r, t.r); }
    void divu(const Gpr& s, const Gpr& t) noexcept { rt::divu(c, s.r, t.r); }
    void mflo(Gpr& d) noexcept { rt::mflo(c, d.r); }
    void mfhi(Gpr& d) noexcept { rt::mfhi(c, d.r); }
    void pcpyld(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::pcpyld(c, d.r, s.r, t.r); }
    void movn(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::movn(c, d.r, s.r, t.r); }
    void movz(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::movz(c, d.r, s.r, t.r); }

    // calls: `jal fn` at pc ($ra = pc + 8; the delay slot's instruction is written before the call), `jalr target`
    // at pc (through the dispatch table; the target register is read before the delay slot), and the tail jumps
    void jal(u32 pc, rt::Fn fn) {
        rt::jal(c, pc);
        fn(c);
    }
    void jalr(u32 pc, u32 target) {
        rt::jalr(c, GPR_RA, pc);
        rt::lookup_func(target)(c);
    }
    void jr(u32 target) { rt::lookup_func(target)(c); }

    // --- the bodies (world.h documents each) ---
    // world sectors
    void sector_render();          // worldSectorRenderDispatch
    void world_render();           // RpWorldRender
    void world_for_lights();       // worldForAllLights
    void sector_render_atomics();  // WorldSectorRender
    void geometry_mesh_build();    // sub_498E30
    void matfx_tail();             // sub_469DC0
    void im3d_instance_tail();     // sub_4A2780
};

// =========================================================================================================
// World sectors (RpWorld)
// =========================================================================================================

// worldSectorRenderDispatch: the current world's sector render callback (world +104) for the sector in $a0, as a tail jump.
void Cpu::sector_render() {
    enter(5);
    v0 = lui(0x96);
    v0 = lw(v0 + 116);  // RW globals +4: the current world
    v0 = lw(v0 + 104);  // its sector render callback
    jr(v0.u());
}

// RpWorldRender: sub_49C330(the current camera, WorldSectorRender, world) -- the frustum walk of the world's sectors.
// Returns the world.
void Cpu::world_render() {
    enter(15);
    sp = addiu(sp, -32);
    a1 = lui(0x4a);
    sd(sp + 16, ra);
    v0 = lui(0x96);
    sq(sp, s0);
    a1 = addiu(a1, -27872);  // WorldSectorRender 0x499320
    s0 = a0;
    a0 = lw(v0 + 112);       // RW globals +0: the current camera
    a2 = s0;
    jal(0x49a270, gen::fn_sub_49C330_0049c330);
    v0 = s0;
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 32);
}

// worldForAllLights: for every light of the current world (list at world +60, link at light +52): callback $a0 (light,
// data $a1) until it returns 0. Returns 1.
void Cpu::world_for_lights() {
    enter(13);
    sp = addiu(sp, -80);
    v0 = lui(0x96);
    sd(sp + 64, ra);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    s3 = a0;
    sq(sp + 16, s1);
    sq(sp, s0);
    v0 = lw(v0 + 116);
    s1 = lw(v0 + 60);
    s0 = addiu(v0, 60);
    const bool none = s1 == s0;
    s2 = a1;
    bool stopped = false;
    if (!none) {
        for (;;) {
            charge(3);
            a0 = addiu(s1, -52);  // the light
            const bool null = a0 == 0;
            s1 = lw(s1);
            if (!null) {
                charge(4);
                a1 = s2;
                jalr(0x499c60, s3.u());
                if (v0 == 0) {
                    charge(2);
                    v0 = 1;
                    stopped = true;
                    break;
                }
            }
            charge(2);
            if (s1 == s0) break;
            backedge();
        }
    }
    if (!stopped) {
        charge(1);
        v0 = 1;
    }
    charge(7);
    ra = ld(sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 80);
}

// WorldSectorRender: the sector's own render (worldSectorRenderDispatch); then every atomic tied to the sector (+56 list of {next,
// prev, atomic}) with its render flag (bit 2 at +2) not yet drawn this frame (u16 stamp at +96 vs the frame counter
// 0x960078): world bounding sphere (atomicGetWorldBoundingSphere), frustum test against the current camera (sub_4C9DF0), the render
// callback (+72) when visible, then the stamp. Returns the sector.
void Cpu::sector_render_atomics() {
    enter(11);
    sp = addiu(sp, -96);
    sd(sp + 80, ra);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    s4 = a0;
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    jal(0x49933c, gen::fn_worldSectorRenderDispatch_00499230);
    bool walk = v0 != 0;
    if (walk) {
        charge(4);
        s3 = lw(s4 + 56);
        s2 = addiu(s4, 56);
        walk = s3 != s2;
    }
    if (walk) {
        charge(2);
        s1 = lui(0x96);
        s1 = addiu(s1, 120);  // the render frame counter
        for (;;) {
            charge(5);
            s0 = lw(s3 + 8);  // the atomic
            v0 = lbu(s0 + 2);
            v0 = v0 & 0x4;
            if (v0 != 0) {
                charge(4);
                v1 = lhu(s0 + 96);
                v0 = lhu(s1);
                if (v1 != v0) {
                    charge(8);
                    a0 = s0;
                    jal(0x499388, gen::fn_atomicGetWorldBoundingSphere_004912b0);
                    v1 = lui(0x96);
                    a0 = lw(v1 + 112);
                    a1 = v0;
                    jal(0x499398, gen::fn_sub_4C9DF0_004c9df0);
                    if (v0 != 0) {
                        charge(5);
                        v0 = lw(s0 + 72);
                        a0 = s0;
                        jalr(0x4993cc, v0.u());
                        backedge();
                    }
                    charge(2);
                    v0 = lhu(s1);
                    sh(s0 + 96, v0);
                }
            }
            charge(3);
            s3 = lw(s3);
            if (s3 == s2) break;
            backedge();
        }
        charge(1);
    }
    charge(2);
    v0 = s4;
    charge(8);
    ra = ld(sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 96);
}

// =========================================================================================================
// Atomics, clumps, geometry
// =========================================================================================================

// sub_498E30: sub_498720(geometry $a0, 0, 1) as a tail call (the mesh header build).
void Cpu::geometry_mesh_build() {
    enter(3);
    a1 = 0;
    a2 = 1;
    gen::fn_sub_498720_00498720(c);
}

// =========================================================================================================
// MatFX / skin / PDS
// =========================================================================================================

// sub_469DC0: sub_4687E0 as a tail call (same arguments).
void Cpu::matfx_tail() {
    enter(2);
    gen::fn_sub_4687E0_004687e0(c);
}

// =========================================================================================================
// PS2All
// =========================================================================================================

// sub_4A2780: ps2AllIm3DInstance as a tail call.
void Cpu::im3d_instance_tail() {
    enter(2);
    gen::fn_ps2AllIm3DInstance_004a2bb0(c);
}

// The argument registers of a host call (sign-extended 32-bit values, as `move` / `addiu` leave them).
void args(EEContext& ctx, std::initializer_list<u32> values) {
    unsigned r = GPR_A0;
    for (const u32 v : values) core::set_gpr64(ctx, r++, sx(v));
}
u32 v0_of(const EEContext& ctx) { return core::gpr32(ctx, GPR_V0); }

using Body = void (Cpu::*)();
u32 host(EEContext& ctx, Body body, std::initializer_list<u32> values) {
    args(ctx, values);
    (Cpu(ctx).*body)();
    return v0_of(ctx);
}

}  // namespace

// --- host entry points (world.h) ----------------------------------------------------------------------------
u32 worldSectorRenderDispatch(EEContext& ctx, u32 sector) { return host(ctx, &Cpu::sector_render, {sector}); }
// 0x0049A3D0 worldSetSectorRenderCallBack -- 40 bytes; leaf frame (no stack)
// worldSetSectorRenderCallBack [RpWorldSetSectorRenderCallBack](world, callback): world +104 = the callback, or the
// default _rpSectorDefaultRenderCallBack when 0. Returns the world.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void worldSetSectorRenderCallBack(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::sw;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0049a3d0
    enter(ctx, 2);  // entry check point + this block's cycles
    if (a1 == 0) {
        // 0x0049a3e4: the default
        charge(ctx, 3);
        a1 = hi(kDefaultSectorRenderCb);
        a1 = addiu(a1, lo(kDefaultSectorRenderCb));  // &_rpSectorDefaultRenderCallBack
        backedge(ctx);
    }
    // 0x0049a3d8
    charge(ctx, 3);
    sw(a1, a0, rw_world::kRenderCb);
    v0 = a0;
    // 0x0049a3f0
    charge(ctx, 2);
}
u32 RpWorldRender(EEContext& ctx, u32 world) { return host(ctx, &Cpu::world_render, {world}); }
// 0x00499B90 _rpSectorDefaultRenderCallBack -- 136 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// _rpSectorDefaultRenderCallBack(sector): a sector with polygons (+132 > 0) runs its pipeline (+124), else the world's
// default sector pipeline (+108), else the PS2All module's global default (RW globals + gp-16840, +64), through
// RxPipelineExecute(pipe, sector, 1). Returns the sector, or 0 when the pipeline failed.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void _rpSectorDefaultRenderCallBack(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::jal, hg::ld, hg::lhu,
          hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00499b90
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lhu(v0, a0, rw_sector::kPolygons);
    s0 = a0;  // s0 = the sector
    if (i64(v0) <= 0) {
        // 0x00499bcc: no polygons: the sector
        charge(ctx, 2);
        v0 = s0;
    } else {
        // 0x00499ba8: the pipeline
        charge(ctx, 3);
        lw(a0, s0, rw_sector::kPipeline);
        if (a0 == 0) {
            // 0x00499bd4: the current world's default sector pipeline
            charge(ctx, 5);
            v0 = hi(rwl::kRwGlobals + rw_globals::kCurrentWorld);
            lw(v0, v0, lo(rwl::kRwGlobals + rw_globals::kCurrentWorld));
            lw(a0, v0, rw_world::kSectorPipe);
            if (a0 == 0) {
                // 0x00499bf0: the PS2All module's global default
                charge(ctx, 6);
                lw(v1, gp, world::kGpPs2AllModule);
                v0 = hi(rwl::kRwGlobals);
                v0 = addiu(v0, lo(rwl::kRwGlobals));
                v0 = addu(v0, v1);
                lw(a0, v0, ps2all_module::kDefaultPipe);
                backedge(ctx);
                // 0x00499bb4 (written out on this path)
                charge(ctx, 1);
                a1 = s0;
            } else {
                // 0x00499be8
                charge(ctx, 2);
                a1 = s0;
                backedge(ctx);
            }
        } else {
            // 0x00499bb4
            charge(ctx, 1);
            a1 = s0;
        }
        // 0x00499bb8: RxPipelineExecute(pipe, sector, 1): the sector, or 0
        charge(ctx, 5);
        a2 = 1;
        jal(ctx, 0x499BB8u, gen::fn_RxPipelineExecute_004f2e70);
        if (v0 == 0) s0 = 0;
        v0 = s0;
    }
    // 0x00499c08 (the shared epilogue)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}
u32 worldForAllLights(EEContext& ctx, u32 callback, u32 data) { return host(ctx, &Cpu::world_for_lights, {callback, data}); }
// 0x00499CA0 worldSectorForAllLights -- 132 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// worldSectorForAllLights [RpWorldSectorForAllLights](sector, callback, data): for every light tied to the sector (the
// list at sector +64 of {next, prev, light}): callback(light, data) until it returns 0. Returns the sector.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: the hand version terminated the host on a random world).
void worldSectorForAllLights(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jalr, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00499ca0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;  // s4 = the sector
    sq(s2, sp, 0x20);
    s3 = a1;  // s3 = the callback
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, rw_sector::kLights + light_link::kNext);  // v0 = the first link
    s0 = addiu(s4, rw_sector::kLights);                    // s0 = the list head
    s2 = a2;  // s2 = data
    if (v0 != s0) {
        for (;;) {
            // 0x00499cd4: the link's light; s1 = the next link
            charge(ctx, 3);
            lw(a0, v0, light_link::kLight);
            lw(s1, v0, light_link::kNext);
            if (a0 != 0) {
                // 0x00499ce0: callback(light, data)
                charge(ctx, 4);
                a1 = s2;
                jalr(ctx, 0x499CE0u, s3.u());
                if (v0 == 0) {
                    // 0x00499cf0: it said stop: return the sector
                    charge(ctx, 2);
                    v0 = s4;
                    // 0x00499d04 (the shared epilogue, written out on this path)
                    charge(ctx, 8);
                    ld(ra, sp, 0x50);
                    lq(s4, sp, 0x40);
                    lq(s3, sp, 0x30);
                    lq(s2, sp, 0x20);
                    lq(s1, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x60);
                    return;
                }
            }
            // 0x00499cf8: the next link, until the head again
            charge(ctx, 2);
            v0 = s1;
            if (s1 == s0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00499d00: return the sector
    charge(ctx, 1);
    v0 = s4;
    // 0x00499d04 (the shared epilogue)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0049A870 worldForAllSectors -- 168 bytes; frame 0x150: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// worldForAllSectors [RpWorldForAllWorldSectors](world, callback, data): every sector of the world in BSP order: from
// the root (+28), a plane node (type word >= 0) pushes its right child (+12) on the frame's stack (sp + 80, one word
// each) and goes left (+8); a sector (type < 0) runs callback(sector, data) -- 0 stops -- and pops the next node.
// Returns the world.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: the hand version terminated the host on a random world).
void worldForAllSectors(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::jalr, hg::ld, hg::lq,
          hg::lw, hg::sd, hg::sll, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049a870
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x150);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;  // s3 = the world
    sq(s1, sp, 0x10);
    s2 = a1;  // s2 = the callback
    sq(s0, sp, 0x0);
    s1 = a2;  // s1 = data
    lw(a0, a0, rw_world::kRoot);  // a0 = the node
    s0 = 0;  // s0 = the stack depth (the stack at sp + 80 + 4 * depth)
    for (;;) {
        // 0x0049a89c
        charge(ctx, 3);
        lw(v0, a0, bsp_node::kType);
        if (i64(v0) >= 0) {
            // 0x0049a8a8: a plane: push the right child, go left
            charge(ctx, 6);
            lw(v1, a0, bsp_node::kRight);
            s0 = addiu(s0, 1);
            v0 = sll(s0, 2);
            v0 = addu(v0, sp);
            lw(a0, a0, bsp_node::kLeft);
            sw(v1, v0, 80);
        } else {
            // 0x0049a8d0: a sector: callback(sector, data); 0 stops
            charge(ctx, 4);
            a1 = s1;
            jalr(ctx, 0x49A8D0u, s2.u());
            if (v0 == 0) {
                break;
            }
            // 0x0049a8e0: pop
            charge(ctx, 5);
            v0 = sll(s0, 2);
            v0 = addu(v0, sp);
            lw(a0, v0, 80);
            s0 = addiu(s0, -1);
            backedge(ctx);
        }
        // 0x0049a8c0: until the stack is empty
        charge(ctx, 2);
        if (i64(s0) < 0) {
            // 0x0049a8c8: return the world
            charge(ctx, 2);
            v0 = s3;
            // 0x0049a8fc (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x40);
            lq(s3, sp, 0x30);
            lq(s2, sp, 0x20);
            lq(s1, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x150);
            return;
        }
        backedge(ctx);
    }
    // 0x0049a8f8: stopped: return the world
    charge(ctx, 1);
    v0 = s3;
    // 0x0049a8fc (the shared epilogue)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x150);
}

// 0x0049A170 worldSectorGetWorld -- 220 bytes; frame 0x70: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// worldSectorGetWorld [RpWorldSectorGetWorld](sector): the world a sector belongs to: over the world plugin's list of
// worlds (RW globals + gp-17552, +4; link at world chunk +8), a world whose flag bit 0 (+3) is set holds its sectors in
// its own block [world, world + block size (+4)): an address test; any other world is searched with worldForAllSectors
// and the match callback 0x4992F0 on the frame record {sector, result} at sp + 104. Returns the world, or 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: the hand version terminated the host on a random world).
void worldSectorGetWorld(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq,
          hg::lw, hg::sd, hg::sltu, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // The epilogue 0x0049a230, written out on each path that returns.
    auto epilogue = [&] {
        charge(ctx, 7);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x70);
    };
    // 0x0049a170
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v0 = hi(rwl::kRwGlobals);
    sd(ra, sp, 0x50);
    v0 = addiu(v0, lo(rwl::kRwGlobals));
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, gp, world::kGpWorldModule);
    v0 = addu(v0, v1);   // the world module's data
    lw(s3, v0, 4);       // s3 = the first link of its world list
    s2 = addiu(v0, 4);   // s2 = the list head
    s4 = a0;             // s4 = the sector
    if (s3 != s2) {
        // 0x0049a1ac
        charge(ctx, 1);
        s1 = addiu(sp, 0x6C);  // the search record's result word
        for (;;) {
            // 0x0049a1b0: s0 = the world chunk (link - 8), v0 = its world
            charge(ctx, 5);
            lw(v0, s3, -8);
            lbu(v1, v0, 3);
            v1 = v1 & 0x1;
            s0 = addiu(s3, -8);
            if (v1 != 0) {
                // 0x0049a1c4: sectors in the world's own block: an address test
                charge(ctx, 3);
                v1 = sltu(s4, v0);
                if (v1 == 0) {
                    // 0x0049a1d0
                    charge(ctx, 5);
                    lw(v1, s0, 4);
                    v1 = addu(v0, v1);
                    at = sltu(s4, v1);
                    if (at != 0) {
                        // 0x0049a1e4: inside: return the world
                        charge(ctx, 2);
                        ld(ra, sp, 0x50);
                        epilogue();
                        return;
                    }
                }
            } else {
                // 0x0049a200: search it: worldForAllSectors(world, sub_4992F0, {sector, result})
                charge(ctx, 10);
                sw(s4, sp, 0x68);
                a1 = hi(kSectorMatchCb);
                sw(zero, s1, 0);
                a1 = addiu(a1, lo(kSectorMatchCb));  // &sub_4992F0
                lw(a0, s0, 0);
                a2 = addiu(sp, 0x68);
                jal(ctx, 0x49A214u, gen::fn_worldForAllSectors_0049a870);
                lw(v0, s1, 0);
                if (v0 != 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0049a1ec: the next world
            charge(ctx, 3);
            lw(s3, s3, 0);
            if (s3 == s2) {
                // 0x0049a1f8: none: 0
                charge(ctx, 2);
                v0 = 0;
                // 0x0049a22c
                charge(ctx, 1);
                ld(ra, sp, 0x50);
                epilogue();
                return;
            }
            backedge(ctx);
        }
        // 0x0049a228: found by the search: its world
        charge(ctx, 1);
        lw(v0, s0, 0);
        // 0x0049a22c
        charge(ctx, 1);
        ld(ra, sp, 0x50);
        epilogue();
    } else {
        // 0x0049a1f8: no worlds: 0
        charge(ctx, 2);
        v0 = 0;
        // 0x0049a22c
        charge(ctx, 1);
        ld(ra, sp, 0x50);
        epilogue();
    }
}
u32 WorldSectorRender(EEContext& ctx, u32 sector) { return host(ctx, &Cpu::sector_render_atomics, {sector}); }
// 0x00499140 sub_499140 -- 164 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_499140 [geometry unlock: run the mesh build callback](geometry $a0, flags $a1) -> the geometry, or 0. A
// geometry with a mesh header (+4) runs the build callback -- the one installed at 0x77DDA0 with its data 0x77DDA4
// when bit 0 of $a1 is set, else sub_498E70 (data 0) -- and on success sub_495C20; without one only sub_495C20,
// returning 0x77DD90.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void sub_499140(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::jalr, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00499140
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    if (s0 != 0) {
        // 0x0049915c
        charge(ctx, 3);
        lw(v0, s0, 4);
        if (v0 == 0) {
            // 0x004991b8: no mesh header: sub_495C20 only; return 0x77DD90
            charge(ctx, 5);
            jal(ctx, 0x4991B8u, gen::fn_sub_495C20_00495c20);
            v0 = hi(kMeshBuildNone);
            v0 = addiu(v0, lo(kMeshBuildNone));  // &0x77DD90
        } else {
            // 0x00499168: the build callback: the installed one (flag bit 0) or sub_498E70
            charge(ctx, 3);
            v0 = a1 & 0x1;
            if (v0 == 0) {
                // 0x00499188: sub_498E70(geometry, 0)
                charge(ctx, 3);
                v1 = hi(kMeshBuildDefault);
                a1 = 0;
                v1 = addiu(v1, lo(kMeshBuildDefault));  // &sub_498E70
            } else {
                // 0x00499174: the installed callback and its data
                charge(ctx, 5);
                v1 = hi(kMeshBuildCb);
                v0 = hi(kMeshBuildData);
                lw(a1, v0, lo(kMeshBuildData));
                lw(v1, v1, lo(kMeshBuildCb));
            }
            // 0x00499194
            charge(ctx, 5);
            a0 = s0;
            jalr(ctx, 0x499194u, v1.u());
            s1 = v0;
            if (s1 == 0) {
                // 0x004991cc (written out on this path): it failed: 0
                charge(ctx, 1);
                v0 = 0;
                // 0x004991d0 (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(ra, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x30);
                return;
            }
            // 0x004991a8: then sub_495C20; return its result
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x4991A8u, gen::fn_sub_495C20_00495c20);
            v0 = s1;
        }
        // 0x004991d0 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x30);
        return;
    }
    // 0x004991cc: no geometry: 0
    charge(ctx, 1);
    v0 = 0;
    // 0x004991d0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x004912B0 atomicGetWorldBoundingSphere -- 352 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// atomicGetWorldBoundingSphere: the atomic's world bounding sphere (+44: centre, +56: radius) from its object sphere (+28, radius +40):
// the interpolation update sub_491100 first when flag 2 (+76) is set; recomputed when the frame (+4) is dirty
// (sub_4CAE30) or the atomic's own dirty bit 0 (+3) is set: centre by the LTM (sub_4C6BE0), radius x the largest axis
// length of the LTM unless its type bits (+12 & 3) say 3 (orthonormal: radius copied); the dirty bit is cleared.
// Returns &atomic->worldSphere (+44).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void atomicGetWorldBoundingSphere(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::backedge, hg::c_lt_s, hg::charge, hg::cond, hg::enter, hg::jal, hg::lbu,
          hg::ld, hg::lq, hg::lw, hg::lwc1, hg::madd_s, hg::madda_s, hg::mov_s, hg::mul_s, hg::mula_s, hg::sb,
          hg::sd, hg::si, hg::sq, hg::sqrt_s, hg::swc1;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5};
    // 0x004912b0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, rw_atomic::kInterp);
    lw(s1, a0, rw_atomic::kFrame);  // s1 = the frame
    v0 = v0 & 0x2;
    s0 = a0;  // s0 = the atomic
    if (v0 != 0) {
        // 0x004912d4: the interpolation update
        charge(ctx, 2);
        jal(ctx, 0x4912D4u, gen::fn_sub_491100_00491100);
    }
    // 0x004912dc: the frame dirty (sub_4CAE30)?
    charge(ctx, 4);
    a0 = s1;
    jal(ctx, 0x4912DCu, gen::fn_sub_4CAE30_004cae30);
    do {
        if (v0 == 0) {
            // 0x004912ec: ... or the atomic's own dirty bit
            charge(ctx, 4);
            lbu(v0, s0, rw_atomic::kDirty);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                break;  // the cached sphere
            }
        }
        // 0x00491304: recompute: the centre by the frame's LTM (sub_4C6BE0)
        charge(ctx, 12);
        a0 = s1;
        jal(ctx, 0x491304u, gen::fn_sub_4CB2F0_004cb2f0);
        s1 = v0;  // s1 = the LTM
        a0 = addiu(s0, rw_atomic::kWorldSphere);
        a1 = addiu(s0, rw_atomic::kSphere);
        a2 = s1;
        jal(ctx, 0x491318u, gen::fn_sub_4C6BE0_004c6be0);
        lw(v1, s1, rw_matrix::kFlags);
        v0 = 3;
        v1 = v1 & 0x3;
        if (v1 == v0) {
            // 0x004913f0: orthonormal: the radius copied
            charge(ctx, 3);
            lwc1(f0, s0, rw_atomic::kSphereRadius);
            swc1(f0, s0, rw_atomic::kWorldRadius);
            backedge(ctx);
        } else {
            // 0x00491334: the radius times the longest axis: f4 / f3 / f1 = |right|^2, |up|^2, |at|^2
            charge(ctx, 21);
            lwc1(f5, s1, rw_matrix::kRightY);
            lwc1(f4, s1, rw_matrix::kRightX);
            lwc1(f3, s1, rw_matrix::kRightZ);
            lwc1(f2, s1, rw_matrix::kUpY);
            lwc1(f1, s1, rw_matrix::kUpX);
            lwc1(f0, s1, rw_matrix::kUpZ);
            mula_s(f5, f5);
            madda_s(f4, f4);
            madd_s(f4, f3, f3);
            mula_s(f2, f2);
            madda_s(f1, f1);
            madd_s(f3, f0, f0);
            lwc1(f2, s1, rw_matrix::kAtY);
            lwc1(f1, s1, rw_matrix::kAtX);
            lwc1(f0, s1, rw_matrix::kAtZ);
            mula_s(f2, f2);
            madda_s(f1, f1);
            madd_s(f1, f0, f0);
            c_lt_s(f3, f1);
            if (cond(ctx)) {
                // 0x00491390
                charge(ctx, 1);
                mov_s(f0, f1);
            } else {
                // 0x00491388
                charge(ctx, 2);
                mov_s(f0, f3);
            }
            // 0x00491394
            charge(ctx, 3);
            c_lt_s(f4, f0);
            if (cond(ctx)) {
                // 0x004913a8
                charge(ctx, 3);
                c_lt_s(f3, f1);
                if (cond(ctx)) {
                    // 0x004913bc
                    charge(ctx, 2);
                    mov_s(f3, f1);
                    mov_s(f4, f3);
                } else {
                    // 0x004913b4
                    charge(ctx, 2);
                    mov_s(f4, f3);
                }
                // 0x004913c4
                charge(ctx, 1);
            } else {
                // 0x004913a0
                charge(ctx, 2);
            }
            // 0x004913c8
            charge(ctx, 5);
            sqrt_s(f1, f4);
            lwc1(f0, s0, rw_atomic::kSphereRadius);
            mul_s(f0, f0, f1);
            swc1(f0, s0, rw_atomic::kWorldRadius);
        }
        // 0x004913dc
        charge(ctx, 5);
        lbu(v1, s0, rw_atomic::kDirty);
        v0 = si(-2);
        v0 = v1 & v0;
        sb(v0, s0, rw_atomic::kDirty);
        backedge(ctx);
    } while (false);
    // 0x004912fc: return &atomic->worldSphere
    charge(ctx, 2);
    v0 = addiu(s0, 44);
    // 0x004913fc
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00491630 RpClumpRender -- 148 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// RpClumpRender: every atomic of the clump (list at +8, link at atomic +64) with its render flag (bit 2 at +2): the
// frame's LTM (sub_4CB2F0 of atomic +4) and the render callback (+72). Returns the clump, or 0 when a callback
// returned 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: the hand version terminated the host on a random world).
void RpClumpRender(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::call, hg::charge, hg::enter, hg::jalr, hg::lbu, hg::ld, hg::link,
          hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00491630
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = addiu(a0, rw_clump::kAtomics);
    sq(s0, sp, 0x0);
    lw(s0, a0, rw_clump::kAtomics);
    s1 = a0;
    if (s0 != s2) {
        for (;;) {
            // 0x00491658
            charge(ctx, 4);
            lbu(v0, s0, rw_atomic::kFlags - rw_atomic::kClumpLink);
            v0 = v0 & 0x4;
            s3 = addiu(s0, -64);
            if (v0 != 0) {
                // 0x00491680
                charge(ctx, 7);
                link(ctx, 0x491680u);  // $ra first: the delay slot below depends on it
                lw(a0, s3, rw_atomic::kFrame);
                call(ctx, gen::fn_sub_4CB2F0_004cb2f0);
                lw(v0, s3, rw_atomic::kRenderCb);
                a0 = s3;
                jalr(ctx, 0x49168Cu, v0.u());
                if (v0 != 0) {
                    backedge(ctx);
                } else {
                    // 0x0049169c
                    charge(ctx, 2);
                    s1 = 0;
                    backedge(ctx);
                }
            }
            // 0x00491668
            charge(ctx, 3);
            lw(s0, s0, 0);
            if (s0 == s2) {
                break;
            }
            backedge(ctx);
        }
        // 0x00491674
        charge(ctx, 1);
    }
    // 0x00491678
    charge(ctx, 2);
    v0 = s1;
    // 0x004916a8
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00493370 geometryLock -- 84 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// geometryLock [RpGeometryLock]: geometry +12 (u16 lock flags) |= the low 16 bits of $a1; locking the polygons (bit 0)
// destroys the mesh header (+84, sub_495C80) and clears it. Returns the geometry.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void geometryLock(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq, hg::lw, hg::sd, hg::sh,
          hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00493370
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = a1 & 0xFFFF;
    sd(ra, sp, 0x10);
    v0 = a1 & 0x1;
    sq(s0, sp, 0x0);
    lhu(v1, a0, rw_geometry::kLockFlags);
    s0 = a0;
    v1 = v1 | a2;
    sh(v1, a0, rw_geometry::kLockFlags);
    if (v0 != 0) {
        // 0x00493398
        charge(ctx, 3);
        lw(a0, s0, rw_geometry::kMeshHeader);
        if (a0 != 0) {
            // 0x004933a4
            charge(ctx, 3);
            jal(ctx, 0x4933A4u, gen::fn_sub_495C80_00495c80);
            sw(zero, s0, rw_geometry::kMeshHeader);
        }
    }
    // 0x004933b0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}
u32 sub_498E30(EEContext& ctx, u32 geometry) { return host(ctx, &Cpu::geometry_mesh_build, {geometry}); }
// 0x00495F10 meshHeaderForAllMeshes -- 160 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// meshHeaderForAllMeshes: for every 12-byte mesh after the mesh header $a0 (count u16 at +4, first offset at +12, meshes from
// header + offset + 16): callback $a1 (mesh, header, data $a2) until it returns 0. Returns the header.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void meshHeaderForAllMeshes(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jalr, hg::ld, hg::lhu, hg::lq,
          hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00495f10
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a1;
    sq(s1, sp, 0x10);
    s2 = a2;
    sq(s0, sp, 0x0);
    lw(v0, a0, mesh_hdr::kFirstOffset);
    lhu(v1, a0, mesh_hdr::kMeshCount);
    v0 = addu(v0, s4);
    s1 = addiu(v1, -1);
    s0 = addiu(v0, 16);
    if (v1 != 0) {
        for (;;) {
            // 0x00495f58
            charge(ctx, 6);
            a0 = s0;
            a1 = s4;
            a2 = s2;
            jalr(ctx, 0x495F60u, s3.u());
            if (v0 == 0) {
                // 0x00495f70: it said stop: return the header
                charge(ctx, 2);
                v0 = s4;
                // 0x00495f90 (the shared epilogue, written out on this path)
                charge(ctx, 8);
                ld(ra, sp, 0x50);
                lq(s4, sp, 0x40);
                lq(s3, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x60);
                return;
            }
            // 0x00495f78: the next mesh (12 bytes)
            charge(ctx, 4);
            v0 = s1;
            s0 = addiu(s0, 12);
            s1 = addiu(s1, -1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x00495f88
        charge(ctx, 2);
        backedge(ctx);
    }
    // 0x00495f50: return the header
    charge(ctx, 2);
    v0 = s4;
    // 0x00495f90 (the shared epilogue)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x00496E80 triStripTriangleEdge -- 216 bytes; leaf frame (no stack)
// triStripTriangleEdge [tri-strip: the triangle's edge (a, b)](triangle, a, b): the triangle has three edge records at
// +4 / +8 / +12, each {u16 vertex, u16 vertex, ...}; returns the edge joining the vertices a and b (either
// orientation), or 0. Each edge is tried as (a, b), then as (b, a).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void triStripTriangleEdge(EEContext& ctx) {
    using hg::Gpr, hg::backedge, hg::charge, hg::enter, hg::lhu, hg::lw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x00496e80
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, tristrip_tri::kEdge0);  // v0 = edge 0
    t0 = a1 & 0xFFFF;                   // t0 = a
    lhu(a3, v0, tristrip_edge::kV0);
    do {
        if (a3 != t0) {
            // 0x00496e94
            charge(ctx, 1);
            a2 = a2 & 0xFFFF;  // a2 = b
        } else {
            // 0x00496f0c: edge 0 as (a, b)?
            charge(ctx, 4);
            lhu(a1, v0, tristrip_edge::kV1);
            v1 = a2 & 0xFFFF;
            if (a1 == v1) {
                break;  // edge 0
            }
            // 0x00496f1c
            charge(ctx, 2);
            a2 = a2 & 0xFFFF;  // a2 = b
            backedge(ctx);
        }
        // 0x00496e98: edge 0 as (b, a)?
        charge(ctx, 2);
        if (a3 == a2) {
            // 0x00496ea0
            charge(ctx, 3);
            lhu(v1, v0, tristrip_edge::kV1);
            if (v1 == t0) {
                // 0x00496eac: edge 0
                charge(ctx, 2);
                break;
            }
        }
        // 0x00496eb4: edge 1 as (a, b)?
        charge(ctx, 4);
        lw(v0, a0, tristrip_tri::kEdge1);
        lhu(a1, v0, tristrip_edge::kV0);
        if (a1 == t0) {
            // 0x00496f24
            charge(ctx, 3);
            lhu(v1, v0, tristrip_edge::kV1);
            if (v1 == a2) {
                break;  // edge 1
            }
            // 0x00496f30
            charge(ctx, 2);
            backedge(ctx);
        }
        // 0x00496ec4: edge 1 as (b, a)?
        charge(ctx, 2);
        if (a1 == a2) {
            // 0x00496ecc
            charge(ctx, 3);
            lhu(v1, v0, tristrip_edge::kV1);
            if (v1 == t0) {
                // 0x00496ed8: edge 1
                charge(ctx, 2);
                break;
            }
        }
        // 0x00496ee0: edge 2 as (a, b)?
        charge(ctx, 4);
        lw(v0, a0, tristrip_tri::kEdge2);
        lhu(a0, v0, tristrip_edge::kV0);
        if (a0 == t0) {
            // 0x00496f38
            charge(ctx, 3);
            lhu(v1, v0, tristrip_edge::kV1);
            if (v1 == a2) {
                break;  // edge 2
            }
            // 0x00496f44
            charge(ctx, 2);
            backedge(ctx);
        }
        // 0x00496ef0: edge 2 as (b, a)?
        charge(ctx, 2);
        if (a0 == a2) {
            // 0x00496ef8
            charge(ctx, 3);
            lhu(v1, v0, tristrip_edge::kV1);
            if (v1 == t0) {
                // 0x00496f04: edge 2
                charge(ctx, 2);
                break;
            }
        }
        // 0x00496f4c: none: 0
        charge(ctx, 1);
        v0 = 0;
    } while (false);
    // 0x00496f50 (the shared epilogue)
    charge(ctx, 2);
}

// 0x004965A0 meshSortCompare -- 504 bytes; leaf frame (no stack)
// meshSortCompare [mesh sort compare]: the qsort comparator of the mesh build ($a0 / $a1 point at two records whose +8 is
// the material). Equal materials compare 0; else each side's key bits: 0x10 when its texture's raster (texture +0)
// has an alpha format (format nibble of raster +35: 1, 3 or 5) or its colour alpha (material +7) is not 255, then 8 /
// 4 / 2 / 1 from the u16 fields +16, +18, +14, +12 (the greater side gets the bit); returns left bits - right bits.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void meshSortCompare(EEContext& ctx) {
    using hg::Gpr, hg::backedge, hg::charge, hg::enter, hg::lbu, hg::lhu, hg::lw, hg::sll, hg::slt, hg::subu;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x004965a0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(v0, a0, 0);
    lw(v1, a1, 0);
    lw(t1, v0, mesh_rd::kMaterial);
    a0 = 0;
    lw(t0, v1, mesh_rd::kMaterial);
    a1 = 0;
    if (t1 == t0) {
        // 0x0049660c
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004965bc
        charge(ctx, 2);
        if (t1 != 0) {
            // 0x004965c4
            charge(ctx, 3);
            lw(a2, t1, rw_material::kTexture);
            if (a2 != 0) {
                // 0x004965d0
                charge(ctx, 7);
                lw(a3, a2, rw_texture::kRaster);
                lbu(a3, a3, rw_raster::kFormatHi);
                a2 = 256;
                a3 = sll(a3, 8);
                a3 = a3 & 0xF00;
                if (a3 != a2) {
                    // 0x004965ec
                    charge(ctx, 3);
                    a2 = 768;
                    if (a3 == a2) {
                        // 0x00496614 (written out on this path): format 3
                        charge(ctx, 1);
                        a1 = a1 | 0x10;
                    } else {
                        // 0x004965f8
                        charge(ctx, 3);
                        a2 = 1280;
                        if (a3 == a2) {
                            // 0x00496604: format 5
                            charge(ctx, 2);
                            a1 = a1 | 0x10;
                        }
                    }
                } else {
                    // 0x00496614: format 1
                    charge(ctx, 1);
                    a1 = a1 | 0x10;
                }
            }
            // 0x00496618: ... or the colour's alpha is not 255
            charge(ctx, 4);
            lbu(a3, t1, rw_material::kAlpha);
            a2 = 255;
            if (a3 != a2) {
                // 0x00496628
                charge(ctx, 1);
                a1 = a1 | 0x10;
            }
        }
        // 0x0049662c
        charge(ctx, 2);
        if (t0 != 0) {
            // 0x00496634
            charge(ctx, 3);
            lw(a2, t0, rw_material::kTexture);
            if (a2 != 0) {
                // 0x00496640
                charge(ctx, 7);
                lw(a3, a2, rw_texture::kRaster);
                lbu(a3, a3, rw_raster::kFormatHi);
                a2 = 256;
                a3 = sll(a3, 8);
                a3 = a3 & 0xF00;
                if (a3 != a2) {
                    // 0x0049665c
                    charge(ctx, 3);
                    a2 = 768;
                    if (a3 == a2) {
                        // 0x00496674 (written out on this path): format 3
                        charge(ctx, 1);
                        a0 = a0 | 0x10;
                    } else {
                        // 0x00496668
                        charge(ctx, 3);
                        a2 = 1280;
                        if (a3 == a2) {
                            // 0x00496674 (written out on this path): format 5
                            charge(ctx, 1);
                            a0 = a0 | 0x10;
                        }
                    }
                } else {
                    // 0x00496674: format 1
                    charge(ctx, 1);
                    a0 = a0 | 0x10;
                }
            }
            // 0x00496678: ... or the colour's alpha is not 255
            charge(ctx, 4);
            lbu(a3, t0, rw_material::kAlpha);
            a2 = 255;
            if (a3 != a2) {
                // 0x00496688
                charge(ctx, 2);
                a0 = a0 | 0x10;
            }
        }
        // 0x00496774
        charge(ctx, 5);
        lhu(a3, v1, 16);
        lhu(a2, v0, 16);
        at = slt(a3, a2);
        if (at == 0) {
            backedge(ctx);
            // 0x00496698
            charge(ctx, 1);
            t0 = 0;
        } else {
            // 0x00496788
            charge(ctx, 2);
            backedge(ctx);
            // 0x00496690
            charge(ctx, 2);
            t0 = 8;
        }
        // 0x0049669c
        charge(ctx, 3);
        at = slt(a2, a3);
        t0 = a1 | t0;
        if (at == 0) {
            // 0x004966b0
            charge(ctx, 1);
            a1 = 0;
        } else {
            // 0x004966a8
            charge(ctx, 2);
            a1 = 8;
        }
        // 0x004966b4
        charge(ctx, 6);
        a3 = a0 | a1;
        lhu(a1, v1, 18);
        lhu(a0, v0, 18);
        at = slt(a1, a0);
        if (at == 0) {
            // 0x004966d4
            charge(ctx, 1);
            a2 = 0;
        } else {
            // 0x004966cc
            charge(ctx, 2);
            a2 = 4;
        }
        // 0x004966d8
        charge(ctx, 3);
        at = slt(a0, a1);
        a2 = t0 | a2;
        if (at == 0) {
            // 0x004966ec
            charge(ctx, 1);
            a0 = 0;
        } else {
            // 0x004966e4
            charge(ctx, 2);
            a0 = 4;
        }
        // 0x004966f0
        charge(ctx, 6);
        a3 = a3 | a0;
        lhu(a1, v1, 14);
        lhu(a0, v0, 14);
        at = slt(a1, a0);
        if (at == 0) {
            // 0x00496710
            charge(ctx, 1);
            t0 = 0;
        } else {
            // 0x00496708
            charge(ctx, 2);
            t0 = 2;
        }
        // 0x00496714
        charge(ctx, 3);
        at = slt(a0, a1);
        a2 = a2 | t0;
        if (at == 0) {
            // 0x00496728
            charge(ctx, 1);
            a0 = 0;
        } else {
            // 0x00496720
            charge(ctx, 2);
            a0 = 2;
        }
        // 0x0049672c
        charge(ctx, 6);
        a1 = a3 | a0;
        lhu(v0, v0, 12);
        lhu(a0, v1, 12);
        at = slt(a0, v0);
        if (at == 0) {
            // 0x0049674c
            charge(ctx, 1);
            v1 = 0;
        } else {
            // 0x00496744
            charge(ctx, 2);
            v1 = 1;
        }
        // 0x00496750
        charge(ctx, 3);
        at = slt(v0, a0);
        v1 = a2 | v1;
        if (at == 0) {
            // 0x00496764
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0049675c
            charge(ctx, 2);
            v0 = 1;
        }
        // 0x00496768
        charge(ctx, 3);
        v0 = a1 | v0;
        v0 = subu(v1, v0);
    }
    // 0x00496790 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00496F60 triStripTakeTriangle -- 464 bytes; leaf frame (no stack)
// triStripTakeTriangle [tri-strip: take a triangle]: with $a2 < 4 only marks the triangle $a0 (+28 = 1). Else marks it used
// (+24 = 1), unlinks it from its bucket (bucket lists $a1, index = the byte +32 = its free neighbour count; links +16
// next / +20 prev), and for each of its three edges (+4 / +8 / +12, the edge's two triangles at +4 / +8) moves the
// unused neighbour one bucket down (count - 1, relinked at the head).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void triStripTakeTriangle(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lbu, hg::lw, hg::sb, hg::sll,
          hg::slti, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x00496f60
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = slti(a2, 4);
    if (v1 != 0) {
        // 0x004970a8
        charge(ctx, 3);
        v1 = 1;
        sw(v1, a0, tristrip_tri::kTakenLo);
        backedge(ctx);
    } else {
        // 0x00496f6c
        charge(ctx, 8);
        v1 = 1;
        sw(v1, a0, tristrip_tri::kTakenHi);
        lbu(v1, a0, tristrip_tri::kBucket);
        v1 = sll(v1, 2);
        a2 = addu(a1, v1);
        lw(v1, a2, 0);
        if (v1 == a0) {
            // 0x004970b4
            charge(ctx, 8);
            lw(v1, v1, tristrip_tri::kNext);
            sw(v1, a2, 0);
            lbu(v1, a0, tristrip_tri::kBucket);
            v1 = sll(v1, 2);
            v1 = addu(a1, v1);
            lw(v1, v1, 0);
            if (v1 == 0) {
                backedge(ctx);
            } else {
                // 0x004970d4
                charge(ctx, 2);
                sw(zero, v1, tristrip_tri::kPrev);
                backedge(ctx);
            }
        } else {
            // 0x00496f8c
            charge(ctx, 3);
            lw(a2, a0, tristrip_tri::kNext);
            if (a2 != 0) {
                // 0x00496f98
                charge(ctx, 2);
                lw(v1, a0, tristrip_tri::kPrev);
                sw(v1, a2, tristrip_tri::kPrev);
            }
            // 0x00496fa0
            charge(ctx, 3);
            lw(a2, a0, tristrip_tri::kPrev);
            if (a2 != 0) {
                // 0x00496fac
                charge(ctx, 2);
                lw(v1, a0, tristrip_tri::kNext);
                sw(v1, a2, tristrip_tri::kNext);
            }
        }
        // 0x00496fb4
        charge(ctx, 1);
        a2 = 0;
        for (;;) {
            // 0x00496fb8
            charge(ctx, 7);
            a3 = a2 & 0xFF;
            a3 = sll(a3, 2);
            a3 = addu(a0, a3);
            lw(t1, a3, tristrip_tri::kEdge0);  // t1 = edge k (k = a2)
            lw(t0, t1, tristrip_edge::kTri0);
            v1 = 0;  // v1 = the unused neighbour across it, if any
            do {
                if (t0 != 0) {
                    // 0x00496fd4: the edge's first side, unless it is this triangle or used
                    charge(ctx, 2);
                    if (t0 != a0) {
                        // 0x00496fdc
                        charge(ctx, 3);
                        lw(a3, t0, tristrip_tri::kTakenHi);
                        if (a3 == 0) {
                            // 0x00496fe8
                            charge(ctx, 2);
                            v1 = t0;
                            break;
                        }
                    }
                }
                // 0x004970dc: its second side
                charge(ctx, 3);
                lw(t0, t1, tristrip_edge::kTri1);
                if (t0 == 0) {
                    backedge(ctx);
                } else {
                    // 0x004970e8
                    charge(ctx, 3);
                    lw(a3, t0, tristrip_tri::kTakenHi);
                    if (a3 != 0) {
                        backedge(ctx);
                    } else {
                        // 0x004970f4
                        charge(ctx, 2);
                        v1 = t0;
                        backedge(ctx);
                    }
                }
            } while (false);
            // 0x00496ff0: move the neighbour one bucket down
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x00496ff8
                charge(ctx, 6);
                lbu(a3, v1, tristrip_tri::kBucket);
                a3 = sll(a3, 2);
                t0 = addu(a1, a3);
                lw(a3, t0, 0);
                if (a3 == v1) {
                    // 0x00497100
                    charge(ctx, 8);
                    lw(a3, a3, tristrip_tri::kNext);
                    sw(a3, t0, 0);
                    lbu(a3, v1, tristrip_tri::kBucket);
                    a3 = sll(a3, 2);
                    a3 = addu(a1, a3);
                    lw(a3, a3, 0);
                    if (a3 == 0) {
                        backedge(ctx);
                    } else {
                        // 0x00497120
                        charge(ctx, 2);
                        sw(zero, a3, tristrip_tri::kPrev);
                        backedge(ctx);
                    }
                } else {
                    // 0x00497010
                    charge(ctx, 3);
                    lw(t0, v1, tristrip_tri::kNext);
                    if (t0 != 0) {
                        // 0x0049701c
                        charge(ctx, 3);
                        lw(a3, v1, tristrip_tri::kPrev);
                        sw(a3, t0, tristrip_tri::kPrev);
                    }
                    // 0x00497028
                    charge(ctx, 3);
                    lw(t0, v1, tristrip_tri::kPrev);
                    if (t0 != 0) {
                        // 0x00497034
                        charge(ctx, 3);
                        lw(a3, v1, tristrip_tri::kNext);
                        sw(a3, t0, tristrip_tri::kNext);
                    }
                }
                // 0x00497040
                charge(ctx, 11);
                lbu(a3, v1, tristrip_tri::kBucket);
                a3 = addiu(a3, -1);
                sb(a3, v1, tristrip_tri::kBucket);
                lbu(a3, v1, tristrip_tri::kBucket);
                a3 = sll(a3, 2);
                a3 = addu(a1, a3);
                lw(a3, a3, 0);
                sw(a3, v1, tristrip_tri::kNext);
                lw(a3, v1, tristrip_tri::kNext);
                if (a3 != 0) {
                    // 0x0049706c
                    charge(ctx, 1);
                    sw(v1, a3, tristrip_tri::kPrev);
                }
                // 0x00497070
                charge(ctx, 6);
                lbu(a3, v1, tristrip_tri::kBucket);
                a3 = sll(a3, 2);
                a3 = addu(a1, a3);
                sw(v1, a3, 0);
                sw(zero, v1, tristrip_tri::kPrev);
            }
            // 0x00497088
            charge(ctx, 5);
            v1 = addiu(a2, 1);
            a2 = v1 & 0xFF;
            v1 = slti(a2, 3);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0049709c
        charge(ctx, 1);
    }
    // 0x004970a0
    charge(ctx, 2);
    // 0x00497128
    charge(ctx, 2);
}

// 0x00469D00 matfxSetSectorPipeline -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// matfxSetSectorPipeline [MatFX world sector pipe]: sector +124 = RpPDSGetPipe(0x11010 when the sector's world (worldSectorGetWorld) has
// flag 0x80 at +8, else 0x1100F). Returns the sector.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: the hand version terminated the host on a random world).
void matfxSetSectorPipeline(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00469d00
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;  // s0 = the sector
    jal(ctx, 0x469D0Cu, gen::fn_worldSectorGetWorld_0049a170);
    lw(v0, v0, rw_world::kFlags);  // its world's flags
    v0 = v0 & 0x80;  // two UV sets?
    if (v0 == 0) {
        // 0x00469d38: PDS 0x1100F
        charge(ctx, 4);
        v0 = 0x10000;
        a0 = v0 | 0x100F;
        jal(ctx, 0x469D3Cu, gen::fn_RpPDSGetPipe_0046a890);
        sw(v0, s0, rw_sector::kPipeline);
    } else {
        // 0x00469d24: PDS 0x11010
        charge(ctx, 5);
        v0 = 0x10000;
        a0 = v0 | 0x1010;
        jal(ctx, 0x469D28u, gen::fn_RpPDSGetPipe_0046a890);
        sw(v0, s0, rw_sector::kPipeline);
    }
    // 0x00469d48 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00469D60 matfxSetAtomicPipeline -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// matfxSetAtomicPipeline [MatFX atomic pipe]: atomic +108 = RpPDSGetPipe(0x1100E when its geometry (+24) has flag 0x80 at +8,
// else 0x1100D). Returns the atomic.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void matfxSetAtomicPipeline(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00469d60
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, rw_atomic::kGeometry);
    lw(v0, v0, rw_geometry::kFlags);
    v0 = v0 & 0x80;  // two UV sets?
    s0 = a0;  // s0 = the atomic
    if (v0 == 0) {
        // 0x00469d94: PDS 0x1100D
        charge(ctx, 4);
        v0 = 0x10000;
        a0 = v0 | 0x100D;
        jal(ctx, 0x469D98u, gen::fn_RpPDSGetPipe_0046a890);
        sw(v0, s0, rw_atomic::kPipeline);
    } else {
        // 0x00469d80: PDS 0x1100E
        charge(ctx, 5);
        v0 = 0x10000;
        a0 = v0 | 0x100E;
        jal(ctx, 0x469D84u, gen::fn_RpPDSGetPipe_0046a890);
        sw(v0, s0, rw_atomic::kPipeline);
    }
    // 0x00469da4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0046EB10 RpPDS_G3d_Skin_PS2AllInstanceCallBack -- 128 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// RpPDS_G3d_Skin_PS2AllInstanceCallBack: (pipe data $a0, instance data $a1): a geometry without the native flag
// 0x01000000 (+8) is instanced as an atomic (ps2AllAtomicInstance, $a1 = the geometry) and then gets its skin weights
// (skinInstanceWeights(mesh pd +44, the geometry's skin extension (skin globals +4 offset), *$a1)). Returns 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void RpPDS_G3d_Skin_PS2AllInstanceCallBack(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::enter, hg::jal, hg::ld, hg::link,
          hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046eb10
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 0x1000000;  // the native flag 0x01000000
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, ps2all_pd::kObject);  // the atomic
    s0 = a1;  // s0 = the instance data
    lw(a1, v1, rw_atomic::kGeometry);  // a1 = its geometry
    lw(v1, a1, rw_geometry::kFlags);
    v0 = v1 & v0;
    s1 = a0;  // s1 = pd
    if (v0 == 0) {
        // 0x0046eb4c: instance it as an atomic; s2 = the geometry's skin extension
        charge(ctx, 11);
        v0 = hi(kSkinGeometryOffset);
        lw(v0, v0, lo(kSkinGeometryOffset));
        v0 = addu(a1, v0);
        link(ctx, 0x46EB58u);  // $ra first: the delay slot below depends on it
        lw(s2, v0, 0);
        call(ctx, gen::fn_ps2AllAtomicInstance_004a1430);
        lw(a0, s1, ps2all_pd::kMesh);  // skinInstanceWeights(mesh, skin, *instance data)
        lw(a2, s0, 0);
        a1 = s2;
        jal(ctx, 0x46EB68u, gen::fn_skinInstanceWeights_0046b1b0);
        backedge(ctx);
    }
    // 0x0046eb44
    charge(ctx, 2);
    v0 = 1;
    // 0x0046eb78
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x004A0DC0 RpMeshPS2AllInstanceCallBack -- 64 bytes; frame 0x10: ra sp+0x0
// RpMeshPS2AllInstanceCallBack: the object type byte (*(pd +8)) 0xFF (a world sector) -> ps2AllSectorInstance, else ps2AllAtomicInstance.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void RpMeshPS2AllInstanceCallBack(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a0dc0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 255;  // a world sector's type byte
    sd(ra, sp, 0x0);
    lw(v1, a0, ps2all_pd::kObject);
    lbu(v1, v1, 0);  // its type byte
    if (v1 != v0) {
        // 0x004a0dec: an atomic
        charge(ctx, 3);
        jal(ctx, 0x4A0DECu, gen::fn_ps2AllAtomicInstance_004a1430);
        ld(ra, sp, 0x0);
    } else {
        // 0x004a0ddc: a world sector
        charge(ctx, 4);
        jal(ctx, 0x4A0DDCu, gen::fn_ps2AllSectorInstance_004a42f0);
        ld(ra, sp, 0x0);
    }
    // 0x004a0df8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x004A3F20 ps2AllSectorLightCB -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// ps2AllSectorLightCB [sector light callback]: a light with the world flag (bit 1 at +2) goes into the light block
// (sub_49FF10(light, 0) with scale and inverse scale 1.0). Returns the light.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void ps2AllSectorLightCB(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq,
          hg::mov_s, hg::mtc1, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12}, f13{ctx, 13};
    // 0x004a3f20
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lbu(v0, a0, rw_light::kFlags);  // the world flag (bit 1)
    v0 = v0 & 0x2;
    s0 = a0;  // s0 = the light
    if (v0 != 0) {
        // 0x004a3f44: sub_49FF10(light, 0) with scale and inverse scale 1.0
        charge(ctx, 7);
        v0 = flt(1.0f);
        a1 = 0;
        mtc1(v0, f12);
        mov_s(f13, f12);
        jal(ctx, 0x4A3F50u, gen::fn_sub_49FF10_0049ff10);
        backedge(ctx);
    }
    // 0x004a3f3c
    charge(ctx, 2);
    v0 = s0;
    // 0x004a3f60
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0049C7A0 sub_49C7A0 -- 104 bytes; frame 0x10: ra sp+0x0
// sub_49C7A0 [Im3D render test]: (_, record ref $a1): a record (*$a1) with no vertices (u16 +0 <= 0) returns 0; else
// +24 = +4, render state 1 (RW device +144, (1, 0)) unless bit 0 of +12 is set; returns 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: frame/spills (own frame)).
void sub_49C7A0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::jalr, hg::ld, hg::lhu, hg::lw,
          hg::sd, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0049c7a0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    lw(v1, a1, 0);  // v1 = the record
    sd(ra, sp, 0x0);
    lhu(v0, v1, 0);  // its vertex count
    if (i64(v0) <= 0) {
        // 0x0049c7d8: none: 0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0049c7b8: +24 = +4; render state 1 = 0 unless bit 0 of +12
        charge(ctx, 6);
        lw(v0, v1, 4);
        sw(v0, v1, 24);
        lw(v0, v1, 12);
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x0049c7e0
            charge(ctx, 7);
            v0 = hi(kRenderStateSet);
            a0 = 1;
            lw(v0, v0, lo(kRenderStateSet));
            a1 = 0;
            jalr(ctx, 0x49C7ECu, v0.u());
            backedge(ctx);
        }
        // 0x0049c7d0
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x0049c7fc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004A2560 ps2AllIm3DObjectSetup -- 368 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// ps2AllIm3DObjectSetup [Im3D object set-up]: (pipe data $a0, matrix ref $a1): sub_4A24A0(Im3D record = pd +8, pd); pd +20 =
// 0x7FFF8; the object matrix and frustum result (im3d_matrix); prim / transType from the primitive flags (*(pd +12))
// (prim_trans); pd +42 = 1. Returns 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void ps2AllIm3DObjectSetup(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::call, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal,
          hg::lbu, hg::ld, hg::link, hg::lq, hg::lw, hg::sb, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a2560
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s1 = a1;
    lw(s0, a0, ps2all_pd::kObject);
    a1 = s2;
    a0 = s0;
    jal(ctx, 0x4A2584u, gen::fn_sub_4A24A0_004a24a0);
    v1 = 0x70000;
    v0 = hi(rwl::kRwGlobals);
    v1 = v1 | 0xFFF8;
    sw(v1, s2, ps2all_pd::kObjFlags);
    lw(v0, v0, lo(rwl::kRwGlobals));
    lw(a1, s0, im3d_rec::kMatrix);
    a2 = addiu(v0, 32);
    if (a1 == 0) {
        // 0x004a2658
        charge(ctx, 2);
        sw(a2, s1, 0);
        backedge(ctx);
    } else {
        // 0x004a25ac
        charge(ctx, 2);
        link(ctx, 0x4A25ACu);  // $ra first: the delay slot below depends on it
        lw(a0, s1, 0);
        call(ctx, gen::fn_sub_4C2F30_004c2f30);
    }
    // 0x004a25b4
    charge(ctx, 4);
    lw(v1, s0, im3d_rec::kFlags);
    v1 = v1 & 0x4;
    v0 = 1;
    if (v1 != 0) {
        // 0x004a2660
        charge(ctx, 2);
        v0 = 2;
        backedge(ctx);
    }
    // 0x004a25c4
    charge(ctx, 7);
    lw(v1, s2, ps2all_pd::kMeshHeader);
    v0 = dsll32(v0, 0);
    a2 = 1;
    lw(a3, v1, 0);
    v1 = a3 & 0x1;
    v0 = dsra32(v0, 0);
    if (v1 == a2) {
        // 0x004a2668
        charge(ctx, 5);
        v1 = 4;
        sb(v1, s2, ps2all_pd::kPrim);
        lbu(v1, gp, world::kGpCamFlags);
        sb(v1, s2, ps2all_pd::kTransType);
        backedge(ctx);
    } else {
        // 0x004a25e0
        charge(ctx, 3);
        v1 = a3 & 0xFF;
        if (v1 != 0) {
            // 0x004a25ec
            charge(ctx, 4);
            v1 = a3 & 0x2;
            a1 = 2;
            if (v1 != a1) {
                // 0x004a25fc
                charge(ctx, 4);
                a0 = a3 & 0x10;
                v1 = 16;
                if (a0 == v1) {
                    // 0x004a2694
                    charge(ctx, 5);
                    v1 = 4;
                    sb(v1, s2, ps2all_pd::kPrim);
                    lbu(v1, gp, world::kGpCamFlags);
                    sb(v1, s2, ps2all_pd::kTransType);
                    backedge(ctx);
                } else {
                    // 0x004a260c
                    charge(ctx, 4);
                    a0 = a3 & 0x8;
                    v1 = 8;
                    if (a0 != v1) {
                        // 0x004a2630
                        charge(ctx, 4);
                        sb(a2, s2, ps2all_pd::kPrim);
                        lbu(v1, gp, world::kGpCamFlags);
                        v1 = v1 | 0x14;
                        sb(v1, s2, ps2all_pd::kTransType);
                    } else {
                        // 0x004a261c
                        charge(ctx, 5);
                        sb(a1, s2, ps2all_pd::kPrim);
                        lbu(v1, gp, world::kGpCamFlags);
                        v1 = v1 | 0x10;
                        sb(v1, s2, ps2all_pd::kTransType);
                    }
                }
            } else {
                // 0x004a267c (written out on this path): a fan: prim 3, transType | 4
                charge(ctx, 6);
                v1 = 3;
                sb(v1, s2, ps2all_pd::kPrim);
                lbu(v1, gp, world::kGpCamFlags);
                v1 = v1 | 0x4;
                sb(v1, s2, ps2all_pd::kTransType);
                backedge(ctx);
            }
        } else {
            // 0x004a267c: no type bits: prim 3, transType | 4
            charge(ctx, 6);
            v1 = 3;
            sb(v1, s2, ps2all_pd::kPrim);
            lbu(v1, gp, world::kGpCamFlags);
            v1 = v1 | 0x4;
            sb(v1, s2, ps2all_pd::kTransType);
            backedge(ctx);
        }
    }
    // 0x004a2640: transType | 2 unless the frustum test said inside (2)
    charge(ctx, 3);
    v1 = 2;
    if (v0 != v1) {
        // 0x004a26a8
        charge(ctx, 4);
        lbu(v0, s2, ps2all_pd::kTransType);
        v0 = v0 | 0x2;
        sb(v0, s2, ps2all_pd::kTransType);
        backedge(ctx);
    }
    // 0x004a264c
    charge(ctx, 3);
    v0 = 1;
    sb(v0, s2, ps2all_pd::kVertexAlpha);
    // 0x004a26b8
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x0046FB80 pds2DObjectSetupA -- 584 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// pds2DObjectSetupA / pds2DObjectSetupB / pds2DObjectSetupC [PDS 2D object set-up] (pipe data $a0, matrix ref $a1), one compiled body at
// three addresses (`base` = the function's start; they differ in the template 0x6B0000 + `tpl` and the record's
// mode `mode`): the 2-D record (pd +8): +44 and +8 = the u16 at 0x95EFC4, +4 = sub_4AAE60(), +0 = the word at
// 0x95EF54, +32 = 0, +36 = mode, +40 = 0; pd +16 = gp-20704 (the material colour), pd +12 = the mesh header 0x77DEC0
// {+8 = record +44, +12 = 0, +0 = flags: the low byte from the PS2All module's prim table (RW globals + gp-17568 +
// mode + 39), 0x100 set when record +40 is 0}; the mesh: +4 = 0, +24 = the template, +16 / +20 = record +40 / +44;
// pd +20 = 0x7FFF8; the object matrix and frustum result (im3d_matrix); prim / transType (prim_trans). Returns 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void pds2DObjectSetupA(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::dsll32, hg::dsra32, hg::enter,
          hg::lbu, hg::ld, hg::lhu, hg::link, hg::lq, hg::lw, hg::sb, hg::sd, hg::si, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046fb80
    enter(ctx, 51);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v1 = hi(kRt2dCount);
    sd(ra, sp, 0x30);
    v0 = hi(kRt2dCount);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;  // s2 = pd
    sq(s0, sp, 0x0);
    s1 = a1;  // s1 = the matrix reference
    lw(s0, a0, ps2all_pd::kObject);  // s0 = the 2-D record
    lhu(v1, v1, lo(kRt2dCount));  // the vertex count (u16) into the record
    sw(v1, s0, pds2d_rec::kCount2);
    lhu(v0, v0, lo(kRt2dCount));
    link(ctx, 0x46FBB4u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, pds2d_rec::kCount);
    call(ctx, gen::fn_sub_4AAE60_004aae60);
    sw(v0, s0, pds2d_rec::kMatrix);  // the Rt2d device matrix (sub_4AAE60)
    v1 = hi(rwl::kIm3DMeshHeader);
    v0 = hi(kRt2dPds2DWord);
    a1 = hi(rwl::kRwGlobals);
    lw(a3, v0, lo(kRt2dPds2DWord));
    a2 = 6;
    a0 = addiu(gp, rwl::kGpIm3DMeshCache);  // the material colour record
    v1 = addiu(v1, lo(rwl::kIm3DMeshHeader));
    a1 = addiu(a1, lo(rwl::kRwGlobals));
    sw(a3, s0, pds2d_rec::kWord0);
    v0 = si(-256);
    sw(zero, s0, pds2d_rec::kWord32);
    sw(a2, s0, pds2d_rec::kMode);
    sw(zero, s0, pds2d_rec::kIndices);
    sw(a0, s2, ps2all_pd::kObjRecord);  // pd +16 = the material colour record
    sw(v1, s2, ps2all_pd::kMeshHeader);  // pd +12 = the Im3D mesh header {+8 the count, +12 = 0, +0 flags}
    lw(a0, s0, pds2d_rec::kCount2);
    lw(v1, s2, ps2all_pd::kMeshHeader);
    sw(a0, v1, 8);
    lw(v1, s2, ps2all_pd::kMeshHeader);
    sw(zero, v1, 12);
    lw(v1, s2, ps2all_pd::kMeshHeader);
    sw(zero, v1, 0);
    // the flags' low byte from the mesh module's prim table (RW globals + offset + mode + 39)
    lw(a2, gp, world::kGpMeshModule);
    lw(a3, s2, ps2all_pd::kMeshHeader);
    lbu(a0, s0, pds2d_rec::kMode);
    a1 = addu(a1, a2);
    lw(v1, a3, 0);
    a0 = addu(a0, a1);
    lbu(a0, a0, 39);
    v0 = v1 & v0;
    v0 = v0 | a0;
    sw(v0, a3, 0);
    lw(v0, s0, pds2d_rec::kIndices);
    if (v0 == 0) {
        // 0x0046fd3c: no indices: header flag 0x100
        charge(ctx, 5);
        lw(v1, s2, ps2all_pd::kMeshHeader);
        lw(v0, v1, 0);
        v0 = v0 | 0x100;
        sw(v0, v1, 0);
        backedge(ctx);
    }
    // 0x0046fc4c: the mesh: +4 = 0, +24 = the template, +16 / +20 = the record's +40 / +44; pd +20 = 0x7FFF8
    charge(ctx, 18);
    lw(a1, s2, ps2all_pd::kObjRecord);
    a0 = hi(kPds2DTemplateA);
    v1 = 0x70000;
    a0 = addiu(a0, lo(kPds2DTemplateA));
    v1 = v1 | 0xFFF8;
    v0 = hi(rwl::kRwGlobals);
    sw(zero, a1, 4);
    lw(a1, s2, ps2all_pd::kMeshHeader);
    sw(a0, a1, 24);
    lw(a0, s0, pds2d_rec::kIndices);
    sw(a0, a1, 16);
    lw(a0, s0, pds2d_rec::kCount2);
    sw(a0, a1, 20);
    sw(v1, s2, ps2all_pd::kObjFlags);
    lw(v0, v0, lo(rwl::kRwGlobals));
    lw(a1, s0, pds2d_rec::kMatrix);  // the matrix: the camera's view matrix (camera +32), or the device matrix times it
    a2 = addiu(v0, 32);
    if (a1 == 0) {
        // 0x0046fd50
        charge(ctx, 2);
        sw(a2, s1, 0);
        backedge(ctx);
    } else {
        // 0x0046fc94
        charge(ctx, 2);
        link(ctx, 0x46FC94u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, 0);
        call(ctx, gen::fn_sub_4C2F30_004c2f30);
    }
    // 0x0046fc9c
    charge(ctx, 4);
    lw(v1, s0, pds2d_rec::kWord0);
    v1 = v1 & 0x4;
    v0 = 1;
    if (v1 != 0) {
        // 0x0046fd58
        charge(ctx, 2);
        v0 = 2;
        backedge(ctx);
    }
    // 0x0046fcac
    charge(ctx, 7);
    lw(v1, s2, ps2all_pd::kMeshHeader);
    v0 = dsll32(v0, 0);
    a2 = 1;
    lw(a3, v1, 0);
    v1 = a3 & 0x1;
    v0 = dsra32(v0, 0);
    if (v1 == a2) {
        // 0x0046fd60
        charge(ctx, 5);
        v1 = 4;
        sb(v1, s2, ps2all_pd::kPrim);
        lbu(v1, gp, world::kGpCamFlags);
        sb(v1, s2, ps2all_pd::kTransType);
        backedge(ctx);
    } else {
        // 0x0046fcc8
        charge(ctx, 3);
        v1 = a3 & 0xFF;
        if (v1 != 0) {
            // 0x0046fcd4
            charge(ctx, 4);
            v1 = a3 & 0x2;
            a1 = 2;
            if (v1 != a1) {
                // 0x0046fce4
                charge(ctx, 4);
                a0 = a3 & 0x10;
                v1 = 16;
                if (a0 == v1) {
                    // 0x0046fd8c
                    charge(ctx, 5);
                    v1 = 4;
                    sb(v1, s2, ps2all_pd::kPrim);
                    lbu(v1, gp, world::kGpCamFlags);
                    sb(v1, s2, ps2all_pd::kTransType);
                    backedge(ctx);
                } else {
                    // 0x0046fcf4
                    charge(ctx, 4);
                    a0 = a3 & 0x8;
                    v1 = 8;
                    if (a0 != v1) {
                        // 0x0046fd18
                        charge(ctx, 4);
                        sb(a2, s2, ps2all_pd::kPrim);
                        lbu(v1, gp, world::kGpCamFlags);
                        v1 = v1 | 0x14;
                        sb(v1, s2, ps2all_pd::kTransType);
                    } else {
                        // 0x0046fd04
                        charge(ctx, 5);
                        sb(a1, s2, ps2all_pd::kPrim);
                        lbu(v1, gp, world::kGpCamFlags);
                        v1 = v1 | 0x10;
                        sb(v1, s2, ps2all_pd::kTransType);
                    }
                }
            } else {
                // 0x0046fd74 (written out on this path): a fan: prim 3, transType | 4
                charge(ctx, 6);
                v1 = 3;
                sb(v1, s2, ps2all_pd::kPrim);
                lbu(v1, gp, world::kGpCamFlags);
                v1 = v1 | 0x4;
                sb(v1, s2, ps2all_pd::kTransType);
                backedge(ctx);
            }
        } else {
            // 0x0046fd74: no type bits: prim 3, transType | 4
            charge(ctx, 6);
            v1 = 3;
            sb(v1, s2, ps2all_pd::kPrim);
            lbu(v1, gp, world::kGpCamFlags);
            v1 = v1 | 0x4;
            sb(v1, s2, ps2all_pd::kTransType);
            backedge(ctx);
        }
    }
    // 0x0046fd28: transType | 2 unless the frustum test said inside (2)
    charge(ctx, 3);
    v1 = 2;
    if (v0 != v1) {
        // 0x0046fda0
        charge(ctx, 4);
        lbu(v0, s2, ps2all_pd::kTransType);
        v0 = v0 | 0x2;
        sb(v0, s2, ps2all_pd::kTransType);
        backedge(ctx);
    }
    // 0x0046fd34
    charge(ctx, 2);
    v0 = 1;
    // 0x0046fdb0
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00470790 pds2DObjectSetupB -- 584 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// pds2DObjectSetupA / pds2DObjectSetupB / pds2DObjectSetupC [PDS 2D object set-up] (pipe data $a0, matrix ref $a1), one compiled body at
// three addresses (`base` = the function's start; they differ in the template 0x6B0000 + `tpl` and the record's
// mode `mode`): the 2-D record (pd +8): +44 and +8 = the u16 at 0x95EFC4, +4 = sub_4AAE60(), +0 = the word at
// 0x95EF54, +32 = 0, +36 = mode, +40 = 0; pd +16 = gp-20704 (the material colour), pd +12 = the mesh header 0x77DEC0
// {+8 = record +44, +12 = 0, +0 = flags: the low byte from the PS2All module's prim table (RW globals + gp-17568 +
// mode + 39), 0x100 set when record +40 is 0}; the mesh: +4 = 0, +24 = the template, +16 / +20 = record +40 / +44;
// pd +20 = 0x7FFF8; the object matrix and frustum result (im3d_matrix); prim / transType (prim_trans). Returns 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void pds2DObjectSetupB(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::dsll32, hg::dsra32, hg::enter,
          hg::lbu, hg::ld, hg::lhu, hg::link, hg::lq, hg::lw, hg::sb, hg::sd, hg::si, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00470790
    enter(ctx, 51);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v1 = hi(kRt2dCount);
    sd(ra, sp, 0x30);
    v0 = hi(kRt2dCount);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;  // s2 = pd
    sq(s0, sp, 0x0);
    s1 = a1;  // s1 = the matrix reference
    lw(s0, a0, ps2all_pd::kObject);  // s0 = the 2-D record
    lhu(v1, v1, lo(kRt2dCount));  // the vertex count (u16) into the record
    sw(v1, s0, pds2d_rec::kCount2);
    lhu(v0, v0, lo(kRt2dCount));
    link(ctx, 0x4707C4u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, pds2d_rec::kCount);
    call(ctx, gen::fn_sub_4AAE60_004aae60);
    sw(v0, s0, pds2d_rec::kMatrix);  // the Rt2d device matrix (sub_4AAE60)
    v1 = hi(rwl::kIm3DMeshHeader);
    v0 = hi(kRt2dPds2DWord);
    a1 = hi(rwl::kRwGlobals);
    lw(a3, v0, lo(kRt2dPds2DWord));
    a2 = 6;
    a0 = addiu(gp, rwl::kGpIm3DMeshCache);  // the material colour record
    v1 = addiu(v1, lo(rwl::kIm3DMeshHeader));
    a1 = addiu(a1, lo(rwl::kRwGlobals));
    sw(a3, s0, pds2d_rec::kWord0);
    v0 = si(-256);
    sw(zero, s0, pds2d_rec::kWord32);
    sw(a2, s0, pds2d_rec::kMode);
    sw(zero, s0, pds2d_rec::kIndices);
    sw(a0, s2, ps2all_pd::kObjRecord);  // pd +16 = the material colour record
    sw(v1, s2, ps2all_pd::kMeshHeader);  // pd +12 = the Im3D mesh header {+8 the count, +12 = 0, +0 flags}
    lw(a0, s0, pds2d_rec::kCount2);
    lw(v1, s2, ps2all_pd::kMeshHeader);
    sw(a0, v1, 8);
    lw(v1, s2, ps2all_pd::kMeshHeader);
    sw(zero, v1, 12);
    lw(v1, s2, ps2all_pd::kMeshHeader);
    sw(zero, v1, 0);
    // the flags' low byte from the mesh module's prim table (RW globals + offset + mode + 39)
    lw(a2, gp, world::kGpMeshModule);
    lw(a3, s2, ps2all_pd::kMeshHeader);
    lbu(a0, s0, pds2d_rec::kMode);
    a1 = addu(a1, a2);
    lw(v1, a3, 0);
    a0 = addu(a0, a1);
    lbu(a0, a0, 39);
    v0 = v1 & v0;
    v0 = v0 | a0;
    sw(v0, a3, 0);
    lw(v0, s0, pds2d_rec::kIndices);
    if (v0 == 0) {
        // 0x0047094c: no indices: header flag 0x100
        charge(ctx, 5);
        lw(v1, s2, ps2all_pd::kMeshHeader);
        lw(v0, v1, 0);
        v0 = v0 | 0x100;
        sw(v0, v1, 0);
        backedge(ctx);
    }
    // 0x0047085c: the mesh: +4 = 0, +24 = the template, +16 / +20 = the record's +40 / +44; pd +20 = 0x7FFF8
    charge(ctx, 18);
    lw(a1, s2, ps2all_pd::kObjRecord);
    a0 = hi(kPds2DTemplateB);
    v1 = 0x70000;
    a0 = addiu(a0, lo(kPds2DTemplateB));
    v1 = v1 | 0xFFF8;
    v0 = hi(rwl::kRwGlobals);
    sw(zero, a1, 4);
    lw(a1, s2, ps2all_pd::kMeshHeader);
    sw(a0, a1, 24);
    lw(a0, s0, pds2d_rec::kIndices);
    sw(a0, a1, 16);
    lw(a0, s0, pds2d_rec::kCount2);
    sw(a0, a1, 20);
    sw(v1, s2, ps2all_pd::kObjFlags);
    lw(v0, v0, lo(rwl::kRwGlobals));
    lw(a1, s0, pds2d_rec::kMatrix);  // the matrix: the camera's view matrix (camera +32), or the device matrix times it
    a2 = addiu(v0, 32);
    if (a1 == 0) {
        // 0x00470960
        charge(ctx, 2);
        sw(a2, s1, 0);
        backedge(ctx);
    } else {
        // 0x004708a4
        charge(ctx, 2);
        link(ctx, 0x4708A4u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, 0);
        call(ctx, gen::fn_sub_4C2F30_004c2f30);
    }
    // 0x004708ac
    charge(ctx, 4);
    lw(v1, s0, pds2d_rec::kWord0);
    v1 = v1 & 0x4;
    v0 = 1;
    if (v1 != 0) {
        // 0x00470968
        charge(ctx, 2);
        v0 = 2;
        backedge(ctx);
    }
    // 0x004708bc
    charge(ctx, 7);
    lw(v1, s2, ps2all_pd::kMeshHeader);
    v0 = dsll32(v0, 0);
    a2 = 1;
    lw(a3, v1, 0);
    v1 = a3 & 0x1;
    v0 = dsra32(v0, 0);
    if (v1 == a2) {
        // 0x00470970
        charge(ctx, 5);
        v1 = 4;
        sb(v1, s2, ps2all_pd::kPrim);
        lbu(v1, gp, world::kGpCamFlags);
        sb(v1, s2, ps2all_pd::kTransType);
        backedge(ctx);
    } else {
        // 0x004708d8
        charge(ctx, 3);
        v1 = a3 & 0xFF;
        if (v1 != 0) {
            // 0x004708e4
            charge(ctx, 4);
            v1 = a3 & 0x2;
            a1 = 2;
            if (v1 != a1) {
                // 0x004708f4
                charge(ctx, 4);
                a0 = a3 & 0x10;
                v1 = 16;
                if (a0 == v1) {
                    // 0x0047099c
                    charge(ctx, 5);
                    v1 = 4;
                    sb(v1, s2, ps2all_pd::kPrim);
                    lbu(v1, gp, world::kGpCamFlags);
                    sb(v1, s2, ps2all_pd::kTransType);
                    backedge(ctx);
                } else {
                    // 0x00470904
                    charge(ctx, 4);
                    a0 = a3 & 0x8;
                    v1 = 8;
                    if (a0 != v1) {
                        // 0x00470928
                        charge(ctx, 4);
                        sb(a2, s2, ps2all_pd::kPrim);
                        lbu(v1, gp, world::kGpCamFlags);
                        v1 = v1 | 0x14;
                        sb(v1, s2, ps2all_pd::kTransType);
                    } else {
                        // 0x00470914
                        charge(ctx, 5);
                        sb(a1, s2, ps2all_pd::kPrim);
                        lbu(v1, gp, world::kGpCamFlags);
                        v1 = v1 | 0x10;
                        sb(v1, s2, ps2all_pd::kTransType);
                    }
                }
            } else {
                // 0x00470984 (written out on this path): a fan: prim 3, transType | 4
                charge(ctx, 6);
                v1 = 3;
                sb(v1, s2, ps2all_pd::kPrim);
                lbu(v1, gp, world::kGpCamFlags);
                v1 = v1 | 0x4;
                sb(v1, s2, ps2all_pd::kTransType);
                backedge(ctx);
            }
        } else {
            // 0x00470984: no type bits: prim 3, transType | 4
            charge(ctx, 6);
            v1 = 3;
            sb(v1, s2, ps2all_pd::kPrim);
            lbu(v1, gp, world::kGpCamFlags);
            v1 = v1 | 0x4;
            sb(v1, s2, ps2all_pd::kTransType);
            backedge(ctx);
        }
    }
    // 0x00470938: transType | 2 unless the frustum test said inside (2)
    charge(ctx, 3);
    v1 = 2;
    if (v0 != v1) {
        // 0x004709b0
        charge(ctx, 4);
        lbu(v0, s2, ps2all_pd::kTransType);
        v0 = v0 | 0x2;
        sb(v0, s2, ps2all_pd::kTransType);
        backedge(ctx);
    }
    // 0x00470944
    charge(ctx, 2);
    v0 = 1;
    // 0x004709c0
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x00471220 pds2DObjectSetupC -- 584 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// pds2DObjectSetupA / pds2DObjectSetupB / pds2DObjectSetupC [PDS 2D object set-up] (pipe data $a0, matrix ref $a1), one compiled body at
// three addresses (`base` = the function's start; they differ in the template 0x6B0000 + `tpl` and the record's
// mode `mode`): the 2-D record (pd +8): +44 and +8 = the u16 at 0x95EFC4, +4 = sub_4AAE60(), +0 = the word at
// 0x95EF54, +32 = 0, +36 = mode, +40 = 0; pd +16 = gp-20704 (the material colour), pd +12 = the mesh header 0x77DEC0
// {+8 = record +44, +12 = 0, +0 = flags: the low byte from the PS2All module's prim table (RW globals + gp-17568 +
// mode + 39), 0x100 set when record +40 is 0}; the mesh: +4 = 0, +24 = the template, +16 / +20 = record +40 / +44;
// pd +20 = 0x7FFF8; the object matrix and frustum result (im3d_matrix); prim / transType (prim_trans). Returns 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void pds2DObjectSetupC(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::dsll32, hg::dsra32, hg::enter,
          hg::lbu, hg::ld, hg::lhu, hg::link, hg::lq, hg::lw, hg::sb, hg::sd, hg::si, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00471220
    enter(ctx, 51);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v1 = hi(kRt2dCount);
    sd(ra, sp, 0x30);
    v0 = hi(kRt2dCount);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;  // s2 = pd
    sq(s0, sp, 0x0);
    s1 = a1;  // s1 = the matrix reference
    lw(s0, a0, ps2all_pd::kObject);  // s0 = the 2-D record
    lhu(v1, v1, lo(kRt2dCount));  // the vertex count (u16) into the record
    sw(v1, s0, pds2d_rec::kCount2);
    lhu(v0, v0, lo(kRt2dCount));
    link(ctx, 0x471254u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, pds2d_rec::kCount);
    call(ctx, gen::fn_sub_4AAE60_004aae60);
    sw(v0, s0, pds2d_rec::kMatrix);  // the Rt2d device matrix (sub_4AAE60)
    v1 = hi(rwl::kIm3DMeshHeader);
    v0 = hi(kRt2dPds2DWord);
    a1 = hi(rwl::kRwGlobals);
    lw(a3, v0, lo(kRt2dPds2DWord));
    a2 = 4;
    a0 = addiu(gp, rwl::kGpIm3DMeshCache);  // the material colour record
    v1 = addiu(v1, lo(rwl::kIm3DMeshHeader));
    a1 = addiu(a1, lo(rwl::kRwGlobals));
    sw(a3, s0, pds2d_rec::kWord0);
    v0 = si(-256);
    sw(zero, s0, pds2d_rec::kWord32);
    sw(a2, s0, pds2d_rec::kMode);
    sw(zero, s0, pds2d_rec::kIndices);
    sw(a0, s2, ps2all_pd::kObjRecord);  // pd +16 = the material colour record
    sw(v1, s2, ps2all_pd::kMeshHeader);  // pd +12 = the Im3D mesh header {+8 the count, +12 = 0, +0 flags}
    lw(a0, s0, pds2d_rec::kCount2);
    lw(v1, s2, ps2all_pd::kMeshHeader);
    sw(a0, v1, 8);
    lw(v1, s2, ps2all_pd::kMeshHeader);
    sw(zero, v1, 12);
    lw(v1, s2, ps2all_pd::kMeshHeader);
    sw(zero, v1, 0);
    // the flags' low byte from the mesh module's prim table (RW globals + offset + mode + 39)
    lw(a2, gp, world::kGpMeshModule);
    lw(a3, s2, ps2all_pd::kMeshHeader);
    lbu(a0, s0, pds2d_rec::kMode);
    a1 = addu(a1, a2);
    lw(v1, a3, 0);
    a0 = addu(a0, a1);
    lbu(a0, a0, 39);
    v0 = v1 & v0;
    v0 = v0 | a0;
    sw(v0, a3, 0);
    lw(v0, s0, pds2d_rec::kIndices);
    if (v0 == 0) {
        // 0x004713dc: no indices: header flag 0x100
        charge(ctx, 5);
        lw(v1, s2, ps2all_pd::kMeshHeader);
        lw(v0, v1, 0);
        v0 = v0 | 0x100;
        sw(v0, v1, 0);
        backedge(ctx);
    }
    // 0x004712ec: the mesh: +4 = 0, +24 = the template, +16 / +20 = the record's +40 / +44; pd +20 = 0x7FFF8
    charge(ctx, 18);
    lw(a1, s2, ps2all_pd::kObjRecord);
    a0 = hi(kPds2DTemplateC);
    v1 = 0x70000;
    a0 = addiu(a0, lo(kPds2DTemplateC));
    v1 = v1 | 0xFFF8;
    v0 = hi(rwl::kRwGlobals);
    sw(zero, a1, 4);
    lw(a1, s2, ps2all_pd::kMeshHeader);
    sw(a0, a1, 24);
    lw(a0, s0, pds2d_rec::kIndices);
    sw(a0, a1, 16);
    lw(a0, s0, pds2d_rec::kCount2);
    sw(a0, a1, 20);
    sw(v1, s2, ps2all_pd::kObjFlags);
    lw(v0, v0, lo(rwl::kRwGlobals));
    lw(a1, s0, pds2d_rec::kMatrix);  // the matrix: the camera's view matrix (camera +32), or the device matrix times it
    a2 = addiu(v0, 32);
    if (a1 == 0) {
        // 0x004713f0
        charge(ctx, 2);
        sw(a2, s1, 0);
        backedge(ctx);
    } else {
        // 0x00471334
        charge(ctx, 2);
        link(ctx, 0x471334u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, 0);
        call(ctx, gen::fn_sub_4C2F30_004c2f30);
    }
    // 0x0047133c
    charge(ctx, 4);
    lw(v1, s0, pds2d_rec::kWord0);
    v1 = v1 & 0x4;
    v0 = 1;
    if (v1 != 0) {
        // 0x004713f8
        charge(ctx, 2);
        v0 = 2;
        backedge(ctx);
    }
    // 0x0047134c
    charge(ctx, 7);
    lw(v1, s2, ps2all_pd::kMeshHeader);
    v0 = dsll32(v0, 0);
    a2 = 1;
    lw(a3, v1, 0);
    v1 = a3 & 0x1;
    v0 = dsra32(v0, 0);
    if (v1 == a2) {
        // 0x00471400
        charge(ctx, 5);
        v1 = 4;
        sb(v1, s2, ps2all_pd::kPrim);
        lbu(v1, gp, world::kGpCamFlags);
        sb(v1, s2, ps2all_pd::kTransType);
        backedge(ctx);
    } else {
        // 0x00471368
        charge(ctx, 3);
        v1 = a3 & 0xFF;
        if (v1 != 0) {
            // 0x00471374
            charge(ctx, 4);
            v1 = a3 & 0x2;
            a1 = 2;
            if (v1 != a1) {
                // 0x00471384
                charge(ctx, 4);
                a0 = a3 & 0x10;
                v1 = 16;
                if (a0 == v1) {
                    // 0x0047142c
                    charge(ctx, 5);
                    v1 = 4;
                    sb(v1, s2, ps2all_pd::kPrim);
                    lbu(v1, gp, world::kGpCamFlags);
                    sb(v1, s2, ps2all_pd::kTransType);
                    backedge(ctx);
                } else {
                    // 0x00471394
                    charge(ctx, 4);
                    a0 = a3 & 0x8;
                    v1 = 8;
                    if (a0 != v1) {
                        // 0x004713b8
                        charge(ctx, 4);
                        sb(a2, s2, ps2all_pd::kPrim);
                        lbu(v1, gp, world::kGpCamFlags);
                        v1 = v1 | 0x14;
                        sb(v1, s2, ps2all_pd::kTransType);
                    } else {
                        // 0x004713a4
                        charge(ctx, 5);
                        sb(a1, s2, ps2all_pd::kPrim);
                        lbu(v1, gp, world::kGpCamFlags);
                        v1 = v1 | 0x10;
                        sb(v1, s2, ps2all_pd::kTransType);
                    }
                }
            } else {
                // 0x00471414 (written out on this path): a fan: prim 3, transType | 4
                charge(ctx, 6);
                v1 = 3;
                sb(v1, s2, ps2all_pd::kPrim);
                lbu(v1, gp, world::kGpCamFlags);
                v1 = v1 | 0x4;
                sb(v1, s2, ps2all_pd::kTransType);
                backedge(ctx);
            }
        } else {
            // 0x00471414: no type bits: prim 3, transType | 4
            charge(ctx, 6);
            v1 = 3;
            sb(v1, s2, ps2all_pd::kPrim);
            lbu(v1, gp, world::kGpCamFlags);
            v1 = v1 | 0x4;
            sb(v1, s2, ps2all_pd::kTransType);
            backedge(ctx);
        }
    }
    // 0x004713c8: transType | 2 unless the frustum test said inside (2)
    charge(ctx, 3);
    v1 = 2;
    if (v0 != v1) {
        // 0x00471440
        charge(ctx, 4);
        lbu(v0, s2, ps2all_pd::kTransType);
        v0 = v0 | 0x2;
        sb(v0, s2, ps2all_pd::kTransType);
        backedge(ctx);
    }
    // 0x004713d4
    charge(ctx, 2);
    v0 = 1;
    // 0x00471450
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x004A4060 ps2AllSectorObjectSetup -- 652 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// ps2AllSectorObjectSetup [world sector object set-up] (pipe data $a0, matrix ref $a1): the mesh header (pd +12 = sector +120);
// the sector's resEntry array (plugin offset gp-17512) when its count matches the mesh count, else sub_49E5A0
// (re)allocates it -> pd +16; unless the current world has the native flag 0x01000000 (+8): the object identifier
// (pd +24 = header serial (+6) | (world flags & 0x9D) << 16), instance flags bit 0 cleared, then 4 (only the serial
// differs) or 8 (the flags differ) against the first resEntry's identifier (+40); *$a1 = the camera's view matrix;
// the frustum result (sub_4A3F70 into sp + 92); prim / transType (prim_trans); pd +42 = world flag 0x40; for a lit
// world (flag 0x20) the world lights and the sector's lights through the light callback ps2AllSectorLightCB. Returns 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void ps2AllSectorObjectSetup(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld,
          hg::lhu, hg::link, hg::lq, hg::lw, hg::sb, hg::sd, hg::si, hg::sll, hg::sltu, hg::sq, hg::srl, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004a4060
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;
    sq(s1, sp, 0x10);
    s2 = a1;
    sq(s0, sp, 0x0);
    lw(s1, a0, ps2all_pd::kObject);
    lw(v0, s1, rw_sector::kMeshHeader);
    sw(v0, a0, ps2all_pd::kMeshHeader);
    lw(v0, gp, world::kGpSectorResEntries);
    a0 = addu(s1, v0);
    lw(v0, a0, 0);
    a1 = 0;
    if (v0 != 0) {
        // 0x004a40a0
        charge(ctx, 5);
        lw(v1, s3, ps2all_pd::kMeshHeader);
        lw(v0, v0, 0);
        lhu(v1, v1, mesh_hdr::kMeshCount);
        if (v1 == v0) {
            // 0x004a40b4
            charge(ctx, 1);
            a1 = 1;
        }
    }
    // 0x004a40b8
    charge(ctx, 2);
    if (a1 == 0) {
        // 0x004a40c8
        charge(ctx, 5);
        lw(v0, s3, ps2all_pd::kMeshHeader);
        link(ctx, 0x4A40CCu);  // $ra first: the delay slot below depends on it
        lhu(a1, v0, mesh_hdr::kMeshCount);
        call(ctx, gen::fn_sub_49E5A0_0049e5a0);
        a0 = v0;
        lw(v1, a0, 0);
    } else {
        // 0x004a40c0
        charge(ctx, 2);
        lw(v1, a0, 0);
    }
    // 0x004a40dc
    charge(ctx, 9);
    s0 = hi(rwl::kRwGlobals + rw_globals::kCurrentWorld);
    s0 = addiu(s0, lo(rwl::kRwGlobals + rw_globals::kCurrentWorld));
    v0 = 0x1000000;
    sw(v1, s3, ps2all_pd::kObjRecord);
    lw(v1, s0, 0);  // 0x960074
    lw(v1, v1, rw_world::kFlags);
    v0 = v1 & v0;
    if (v0 == 0) {
        // 0x004a41d0
        charge(ctx, 15);
        lw(a0, s3, ps2all_pd::kMeshHeader);
        v0 = v1 & 0x9D;
        v1 = v0 & 0xFF;
        v1 = sll(v1, 16);
        v0 = si(-2);
        lhu(a0, a0, mesh_hdr::kSerial);
        v1 = a0 | v1;
        sw(v1, s3, ps2all_pd::kObjectId);
        lw(v1, s3, ps2all_pd::kObjFlags);
        v0 = v1 & v0;
        sw(v0, s3, ps2all_pd::kObjFlags);
        lw(v0, s3, ps2all_pd::kObjRecord);
        lw(v0, v0, 4);
        if (v0 == 0) {
            backedge(ctx);
        } else {
            // 0x004a420c
            charge(ctx, 4);
            lw(a0, v0, res_entry::kObjectId);
            lw(v0, s3, ps2all_pd::kObjectId);
            if (v0 == a0) {
                backedge(ctx);
            } else {
                // 0x004a421c
                charge(ctx, 6);
                v1 = srl(v0, 16);
                v0 = srl(a0, 16);
                v1 = v1 & 0xFF;
                v0 = v0 & 0xFF;
                if (v1 == v0) {
                    // 0x004a4244
                    charge(ctx, 4);
                    lw(v0, s3, ps2all_pd::kObjFlags);
                    v0 = v0 | 0x4;
                    sw(v0, s3, ps2all_pd::kObjFlags);
                    backedge(ctx);
                } else {
                    // 0x004a4234
                    charge(ctx, 4);
                    lw(v0, s3, ps2all_pd::kObjFlags);
                    v0 = v0 | 0x8;
                    sw(v0, s3, ps2all_pd::kObjFlags);
                    backedge(ctx);
                }
            }
        }
    }
    // 0x004a4100
    charge(ctx, 13);
    v0 = hi(rwl::kRwGlobals);
    a0 = s1;
    lw(v0, v0, lo(rwl::kRwGlobals));
    a1 = addiu(sp, 0x5C);
    v0 = addiu(v0, 32);
    link(ctx, 0x4A4114u);  // $ra first: the delay slot below depends on it
    sw(v0, s2, 0);
    call(ctx, gen::fn_sub_4A3F70_004a3f70);
    lw(v1, s3, ps2all_pd::kMeshHeader);
    a2 = 1;
    lw(a3, v1, 0);
    v1 = a3 & 0x1;
    lw(v0, sp, 0x5C);
    if (v1 == a2) {
        // 0x004a4254
        charge(ctx, 5);
        v1 = 4;
        sb(v1, s3, ps2all_pd::kPrim);
        lbu(v1, gp, world::kGpCamFlags);
        sb(v1, s3, ps2all_pd::kTransType);
        backedge(ctx);
    } else {
        // 0x004a4134
        charge(ctx, 3);
        v1 = a3 & 0xFF;
        if (v1 != 0) {
            // 0x004a4140
            charge(ctx, 4);
            v1 = a3 & 0x2;
            a1 = 2;
            if (v1 != a1) {
                // 0x004a4150
                charge(ctx, 4);
                a0 = a3 & 0x10;
                v1 = 16;
                if (a0 == v1) {
                    // 0x004a4280: header flag 0x10: prim 4, transType = the camera's
                    charge(ctx, 5);
                    v1 = 4;
                    sb(v1, s3, ps2all_pd::kPrim);
                    lbu(v1, gp, world::kGpCamFlags);
                    sb(v1, s3, ps2all_pd::kTransType);
                    backedge(ctx);
                } else {
                    // 0x004a4160
                    charge(ctx, 4);
                    a0 = a3 & 0x8;
                    v1 = 8;
                    if (a0 != v1) {
                        // 0x004a4184: a list: prim 1, transType | 0x14
                        charge(ctx, 4);
                        sb(a2, s3, ps2all_pd::kPrim);
                        lbu(v1, gp, world::kGpCamFlags);
                        v1 = v1 | 0x14;
                        sb(v1, s3, ps2all_pd::kTransType);
                    } else {
                        // 0x004a4170: a polyline: prim 2, transType | 0x10
                        charge(ctx, 5);
                        sb(a1, s3, ps2all_pd::kPrim);
                        lbu(v1, gp, world::kGpCamFlags);
                        v1 = v1 | 0x10;
                        sb(v1, s3, ps2all_pd::kTransType);
                    }
                }
            } else {
                // 0x004a4268 (written out on this path): a fan: prim 3, transType | 4
                charge(ctx, 6);
                v1 = 3;
                sb(v1, s3, ps2all_pd::kPrim);
                lbu(v1, gp, world::kGpCamFlags);
                v1 = v1 | 0x4;
                sb(v1, s3, ps2all_pd::kTransType);
                backedge(ctx);
            }
        } else {
            // 0x004a4268: no type bits: prim 3, transType | 4
            charge(ctx, 6);
            v1 = 3;
            sb(v1, s3, ps2all_pd::kPrim);
            lbu(v1, gp, world::kGpCamFlags);
            v1 = v1 | 0x4;
            sb(v1, s3, ps2all_pd::kTransType);
            backedge(ctx);
        }
    }
    // 0x004a4194: transType | 2 unless the frustum test said inside (2)
    charge(ctx, 3);
    v1 = 2;
    if (v0 != v1) {
        // 0x004a4294
        charge(ctx, 4);
        lbu(v0, s3, ps2all_pd::kTransType);
        v0 = v0 | 0x2;
        sb(v0, s3, ps2all_pd::kTransType);
        backedge(ctx);
    }
    // 0x004a41a0
    charge(ctx, 10);
    lw(v0, s0, 0);
    lw(v0, v0, rw_world::kFlags);
    v0 = v0 & 0x40;
    v0 = sltu(0, v0);
    sb(v0, s3, ps2all_pd::kVertexAlpha);
    lw(v0, s0, 0);
    lw(v0, v0, rw_world::kFlags);
    v0 = v0 & 0x20;
    lw(s1, s3, ps2all_pd::kObject);
    if (v0 != 0) {
        // 0x004a42a4
        charge(ctx, 11);
        a0 = 0x4A0000;
        a1 = 0;
        a0 = addiu(a0, 16160);  // &ps2AllSectorLightCB
        jal(ctx, 0x4A42ACu, gen::fn_worldForAllLights_00499c20);
        a1 = 0x4A0000;
        a0 = s1;
        a1 = addiu(a1, 16160);  // &ps2AllSectorLightCB
        a2 = 0;
        jal(ctx, 0x4A42C0u, gen::fn_worldSectorForAllLights_00499ca0);
        backedge(ctx);
    }
    // 0x004a41c8
    charge(ctx, 2);
    v0 = 1;
    // 0x004a42d0
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// 0x0046B060 matfxEffectMatrix -- 336 bytes; frame 0x90: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// matfxEffectMatrix [MatFX effect matrix] (frame $a0 (0: the current camera's frame), out $a1, object $a2): the 4x4 matrix
// cached at 0x95C460 for (the object's +8 record, the frame, the render frame stamp 0x960078) -- remembered at gp-17804
// / gp-17808 / gp-17800 -- else recomputed: the inverse of the frame's LTM (sub_4C32A0), times the record's own frame
// LTM (+4) unless the record is a world (type 0xFF), and re-orthonormalised (sub_4C2FB0) unless the result's type bits
// (+12 & 3) say 3; the 16 words are copied to $a1. Returns the frame.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: frame/spills (own frame)).
void matfxEffectMatrix(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::call, hg::charge, hg::enter, hg::i64, hg::jal, hg::lbu, hg::ld,
          hg::lhu, hg::link, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0046b060
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;  // s3 = the frame
    sq(s1, sp, 0x10);
    s2 = a1;  // s2 = out
    sq(s0, sp, 0x0);
    if (s3 == 0) {
        // 0x0046b134: no frame: the current camera's (camera +4)
        charge(ctx, 4);
        v0 = hi(rwl::kRwGlobals);
        lw(v0, v0, lo(rwl::kRwGlobals));
        lw(s3, v0, 4);
        backedge(ctx);
    }
    // 0x0046b084
    charge(ctx, 6);
    v0 = hi(world::kRenderFrame);
    lw(s1, a2, 8);  // s1 = the object's +8 record
    lhu(s0, v0, lo(world::kRenderFrame));  // s0 = the render frame stamp
    lw(v0, gp, world::kGpFxCacheRecord);
    do {
        // the cache: the same record, frame and render frame stamp keep the matrix at 0x95C460
        if (s1 == v0) {
            // 0x0046b144
            charge(ctx, 3);
            lw(v0, gp, world::kGpFxCacheFrame);
            if (s3 == v0) {
                // 0x0046b150
                charge(ctx, 3);
                ld(v0, gp, world::kGpFxCacheStamp);
                if (s0 == v0) {
                    backedge(ctx);
                    break;  // cached
                }
                // 0x0046b15c
                charge(ctx, 2);
                backedge(ctx);
            } else {
                backedge(ctx);
            }
        }
        // 0x0046b09c: recompute: the inverse of the frame's LTM ...
        charge(ctx, 6);
        a0 = s3;
        jal(ctx, 0x46B09Cu, gen::fn_sub_4CB2F0_004cb2f0);
        lbu(a0, s1, 0);
        v1 = 255;  // a world record (type 0xFF)
        if (a0 == v1) {
            // 0x0046b164: ... alone for a world
            charge(ctx, 6);
            a0 = hi(world::kFxMatrix);
            a1 = v0;
            a0 = addiu(a0, lo(world::kFxMatrix));
            jal(ctx, 0x46B16Cu, gen::fn_sub_4C32A0_004c32a0);
            backedge(ctx);
        } else {
            // 0x0046b0b4: ... times the record's own frame LTM (+4)
            charge(ctx, 10);
            a1 = v0;
            a0 = addiu(sp, 0x50);
            jal(ctx, 0x46B0B8u, gen::fn_sub_4C32A0_004c32a0);
            link(ctx, 0x46B0C0u);  // $ra first: the delay slot below depends on it
            lw(a0, s1, 4);
            call(ctx, gen::fn_sub_4CB2F0_004cb2f0);
            a0 = hi(world::kFxMatrix);
            a1 = v0;
            a0 = addiu(a0, lo(world::kFxMatrix));
            a2 = addiu(sp, 0x50);
            jal(ctx, 0x46B0D4u, gen::fn_sub_4C2F30_004c2f30);
        }
        // 0x0046b0dc: re-orthonormalised unless its type bits say 3; the cache key remembered
        charge(ctx, 6);
        v0 = hi(world::kFxMatrix + rw_matrix::kFlags);
        v1 = 3;
        lw(v0, v0, lo(world::kFxMatrix + rw_matrix::kFlags));
        v0 = v0 & 0x3;
        if (v0 != v1) {
            // 0x0046b17c
            charge(ctx, 6);
            a0 = hi(world::kFxMatrix);
            a0 = addiu(a0, lo(world::kFxMatrix));
            a1 = a0;
            jal(ctx, 0x46B184u, gen::fn_sub_4C2FB0_004c2fb0);
            sw(s1, gp, world::kGpFxCacheRecord);
            backedge(ctx);
        } else {
            // 0x0046b0f4
            charge(ctx, 1);
            sw(s1, gp, world::kGpFxCacheRecord);
        }
        // 0x0046b0f8
        charge(ctx, 2);
        sd(s0, gp, world::kGpFxCacheStamp);
        sw(s3, gp, world::kGpFxCacheFrame);
    } while (false);
    // 0x0046b100: the 16 words to $a1
    charge(ctx, 3);
    a1 = hi(world::kFxMatrix);
    a0 = 8;
    a1 = addiu(a1, lo(world::kFxMatrix));
    for (;;) {
        // 0x0046b10c
        charge(ctx, 8);
        lw(v1, a1, 0);
        a0 = addiu(a0, -1);
        lw(v0, a1, 4);
        sw(v1, s2, 0);
        a1 = addiu(a1, 8);
        sw(v0, s2, 4);
        s2 = addiu(s2, 8);
        if (i64(a0) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0046b12c
    charge(ctx, 2);
    v0 = s3;
    // 0x0046b194
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x0046BAB0 sub_46BAB0 -- 580 bytes; frame 0x80: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_46BAB0 [Rt2d path draw, outline] (path $a0, brush $a1): for the path and every path after it (+20, a recursion):
// the flattened segment list (+12, made by sub_4AB8C0 / sub_4ABD50 when absent) -> its vertex array ($s3: sub_4C2090
// when the cached count (+4) is -1, else +0) and count ($s2: sub_4C2120 likewise); the brush texture's render states
// through the device setter (RW globals +144): 1 = the raster, 9 = the filter (low byte of texture +80), 2 = the
// addressing (0 when the U / V nibbles differ), or 1 = 0 untextured; the draw globals 0x95EF60.. (the path's inset
// +16, the last vertex's width, the brush, the vertices); sub_4F2710 opens the 20-byte packet record; the batch count
// at 0x95EFC8 = (count - 40) / 39 rounded up (0 for up to 40 vertices), 0x95EFC4 = count + batches; then
// RxPipelineExecute(0x95F040 pipeline, record + 12, 0). Returns the path, or 0 when the pipeline failed.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: the hand version terminated the host on a random world).
void sub_46BAB0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::div, hg::enter, hg::i64,
          hg::jal, hg::jalr, hg::ld, hg::link, hg::lq, hg::lui, hg::lw, hg::lwc1, hg::mfhi, hg::mult, hg::sd, hg::sh,
          hg::si, hg::sll, hg::sq, hg::sra, hg::srl, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x0046bab0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (s5 != 0) {
        // 0x0046bae0
        charge(ctx, 3);
        lw(v0, s5, rt2d_path::kFlat);
        s0 = s5;
        if (v0 == 0) {
            // 0x0046baec: no flattened list yet: sub_4AB8C0 makes one, sub_4ABD50 flattens the path into it
            charge(ctx, 6);
            jal(ctx, 0x46BAECu, gen::fn_sub_4AB8C0_004ab8c0);
            s0 = v0;
            a1 = s5;
            a0 = s0;
            jal(ctx, 0x46BAFCu, gen::fn_sub_4ABD50_004abd50);
        }
        // 0x0046bb04: s3 = the vertices (the array's base when the count is not cached)
        charge(ctx, 4);
        lw(v1, s0, rt2d_flat::kCount);
        v0 = si(-1);
        if (v1 != v0) {
            // 0x0046bb24
            charge(ctx, 1);
            lw(s3, s0, rt2d_flat::kArray);
        } else {
            // 0x0046bb14
            charge(ctx, 4);
            link(ctx, 0x46BB14u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, rt2d_flat::kArray);
            call(ctx, gen::fn_sub_4C2090_004c2090);
            s3 = v0;
        }
        // 0x0046bb28: s2 = their count
        charge(ctx, 4);
        lw(s2, s0, rt2d_flat::kCount);
        v0 = si(-1);
        if (s2 == v0) {
            // 0x0046bb38
            charge(ctx, 3);
            link(ctx, 0x46BB38u);  // $ra first: the delay slot below depends on it
            lw(a0, s0, rt2d_flat::kArray);
            call(ctx, gen::fn_sub_4C2120_004c2120);
            s2 = v0;
        }
        // 0x0046bb44: the brush's render states (through pfn_RwRenderStateSet): textured: 1 the raster, 9 the filter,
        // 2 the
        // addressing (0 when U and V differ); untextured: 1 = 0
        charge(ctx, 3);
        lw(a0, s4, rt2d_brush::kTexture);
        if (a0 == 0) {
            // 0x0046bca0
            charge(ctx, 7);
            v0 = hi(kRenderStateSet);
            a0 = 1;
            lw(v0, v0, lo(kRenderStateSet));
            a1 = 0;
            jalr(ctx, 0x46BCACu, v0.u());
            v0 = sll(s2, 1);
            backedge(ctx);
        } else {
            // 0x0046bb50
            charge(ctx, 7);
            lw(v1, a0, rw_texture::kFilterAddr);
            v0 = v1 & 0xF000;
            s1 = srl(v0, 12);
            v0 = v1 & 0xF00;
            v0 = srl(v0, 8);
            s6 = v1 & 0xFF;
            if (v0 != s1) {
                // 0x0046bb74
                charge(ctx, 1);
                s1 = 0;
            } else {
                // 0x0046bb6c
                charge(ctx, 2);
            }
            // 0x0046bb78
            charge(ctx, 15);
            s0 = hi(kRenderStateSet);
            lw(a1, a0, rw_texture::kRaster);
            s0 = addiu(s0, lo(kRenderStateSet));
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            a0 = 1;
            jalr(ctx, 0x46BB88u, v0.u());
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            a1 = s6;
            a0 = 9;
            jalr(ctx, 0x46BB98u, v0.u());
            lw(v0, s0, 0);  // pfn_RwRenderStateSet
            a1 = s1;
            a0 = 2;
            jalr(ctx, 0x46BBA8u, v0.u());
            v0 = sll(s2, 1);
        }
        // 0x0046bbb4: the draw globals (inset, the last vertex's width, the brush, the vertices); sub_4F2710 opens the
        // packet record
        charge(ctx, 16);
        a0 = hi(kRt2dInset);
        v0 = addu(v0, s2);
        v1 = hi(kRt2dBrush);
        a1 = sll(v0, 3);
        a1 = addu(a1, s3);
        v0 = hi(kRt2dWidth);
        lwc1(f1, a1, -4);
        lwc1(f0, s5, rt2d_path::kInset);
        swc1(f0, a0, lo(kRt2dInset));
        sw(s4, v1, lo(kRt2dBrush));
        link(ctx, 0x46BBDCu);  // $ra first: the delay slot below depends on it
        swc1(f1, v0, lo(kRt2dWidth));  // the last vertex's width
        call(ctx, gen::fn_sub_4F2710_004f2710);
        v1 = hi(kRt2dVertices);
        a3 = addiu(s2, -40);
        sw(s3, v1, lo(kRt2dVertices));
        if (i64(a3) <= 0) {
            // 0x0046bcbc
            charge(ctx, 3);
            v1 = hi(kRt2dBatches);
            sw(zero, v1, lo(kRt2dBatches));
            backedge(ctx);
        } else {
            // 0x0046bbf4: (count - 40) / 39 rounded up (the magic-number division by 39)
            charge(ctx, 17);
            v1 = lui(0xD20D);
            a2 = 39;
            v1 = v1 | 0x20D3;
            mult(zero, v1, a3);
            a1 = srl(a3, 31);
            mfhi(a0);
            v1 = hi(kRt2dBatches);
            a0 = addu(a0, a3);
            a0 = sra(a0, 5);
            a0 = addu(a0, a1);
            a0 = addiu(a0, 1);
            sw(a0, v1, lo(kRt2dBatches));
            div(a3, a2);
            mfhi(v1);
            if (v1 == 0) {
                // 0x0046bc38
                charge(ctx, 3);
                a0 = addiu(a0, -1);
                v1 = hi(kRt2dBatches);
                sw(a0, v1, lo(kRt2dBatches));
            }
        }
        // 0x0046bc44: the record {count + batches, the packet word, 20}; RxPipelineExecute(the stroke pipeline, record
        // + 12, 0)
        charge(ctx, 18);
        v1 = hi(kRt2dBatches);
        a3 = hi(kRt2dCount);
        lw(t1, v1, lo(kRt2dBatches));
        a0 = hi(kRt2dPacketWord);
        t0 = 20;
        a1 = addiu(v0, 12);
        t1 = addu(s2, t1);
        v1 = hi(kRt2dStrokePipe);
        sw(t1, a3, lo(kRt2dCount));
        sh(t1, v0, 0);
        lw(a0, a0, lo(kRt2dPacketWord));
        sw(a0, v0, 4);
        sw(t0, v0, 8);
        lw(a0, v1, lo(kRt2dStrokePipe));
        a2 = 0;
        jal(ctx, 0x46BC7Cu, gen::fn_RxPipelineExecute_004f2e70);
        if (v0 != 0) {
            // 0x0046bc8c: the next path (+20), recursively
            charge(ctx, 3);
            lw(a0, s5, rt2d_path::kNext);
            a1 = s4;
            jal(ctx, 0x46BC90u, gen::fn_sub_46BAB0_0046bab0);
            // 0x0046bc98 (written out on this path): return the path
            charge(ctx, 2);
            v0 = s5;
        } else {
            // 0x0046bcc8: the pipeline failed: 0
            charge(ctx, 1);
            v0 = 0;
        }
    } else {
        // 0x0046bc98: no path: return it (0)
        charge(ctx, 2);
        v0 = s5;
    }
    // 0x0046bccc (the shared epilogue)
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// 0x0046BD00 sub_46BD00 -- 676 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_46BD00 [Rt2d path draw, filled] (path $a0, brush $a1): for the path and every path after it (+20, a recursion);
// a path without its +8 data is skipped. The flattened list as sub_46BAB0 ($s1 vertices, count - 1 clamped to >= 3 in
// $s2, $s8 = the last vertex); the brush render states; the path's bounds (sub_4AC020 into the frame at sp + 160..172)
// give the UV origin and scale (1 / width, 1 / height) at 0x95EF70..; the draw globals; sub_4F2710's packet record
// with the vertex count rounded up to even; RxPipelineExecute(0x95F050 pipeline, record + 12, 0). Returns the path,
// or 0 when the pipeline failed.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void sub_46BD00(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::div_s, hg::enter, hg::jal,
          hg::jalr, hg::ld, hg::link, hg::lq, hg::lw, hg::lwc1, hg::mtc1, hg::sd, hg::sh, hg::si, hg::sll, hg::slti,
          hg::sq, hg::srl, hg::sub_s, hg::sw, hg::swc1;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4};
    // 0x0046bd00
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    s5 = a0;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    if (s5 != 0) {
        // 0x0046bd38: a path without nodes is skipped
        charge(ctx, 3);
        lw(v0, s5, rt2d_path::kData);
        if (v0 != 0) {
            // 0x0046bd44
            charge(ctx, 3);
            lw(v0, s5, rt2d_path::kFlat);
            s3 = s5;
            if (v0 == 0) {
                // 0x0046bd50: no flattened list yet: sub_4AB8C0 makes one, sub_4ABD50 flattens the path into it
                charge(ctx, 6);
                jal(ctx, 0x46BD50u, gen::fn_sub_4AB8C0_004ab8c0);
                s3 = v0;
                a1 = s5;
                a0 = s3;
                jal(ctx, 0x46BD60u, gen::fn_sub_4ABD50_004abd50);
            }
            // 0x0046bd68: s1 = the vertices (the array's base when the count is not cached)
            charge(ctx, 4);
            lw(v1, s3, rt2d_flat::kCount);
            v0 = si(-1);
            if (v1 != v0) {
                // 0x0046bd88
                charge(ctx, 1);
                lw(s1, s3, rt2d_flat::kArray);
            } else {
                // 0x0046bd78
                charge(ctx, 4);
                link(ctx, 0x46BD78u);  // $ra first: the delay slot below depends on it
                lw(a0, s3, rt2d_flat::kArray);
                call(ctx, gen::fn_sub_4C2090_004c2090);
                s1 = v0;
            }
            // 0x0046bd8c: the count
            charge(ctx, 4);
            lw(v0, s3, rt2d_flat::kCount);
            v1 = si(-1);
            if (v0 == v1) {
                // 0x0046bd9c
                charge(ctx, 2);
                link(ctx, 0x46BD9Cu);  // $ra first: the delay slot below depends on it
                lw(a0, s3, rt2d_flat::kArray);
                call(ctx, gen::fn_sub_4C2120_004c2120);
            }
            // 0x0046bda4: s2 = count - 1, at least 3; fp = the last vertex
            charge(ctx, 4);
            s2 = addiu(v0, -1);
            at = slti(s2, 3);
            if (at != 0) {
                // 0x0046bdb4
                charge(ctx, 1);
                s2 = 3;
            }
            // 0x0046bdb8
            charge(ctx, 7);
            lw(a0, s4, rt2d_brush::kTexture);
            v1 = addiu(s2, -1);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v0 = sll(v0, 3);
            fp = addu(s1, v0);
            if (a0 == 0) {
                // 0x0046bf58: untextured: 1 = 0
                charge(ctx, 7);
                v0 = hi(kRenderStateSet);
                a0 = 1;
                lw(v0, v0, lo(kRenderStateSet));
                a1 = 0;
                jalr(ctx, 0x46BF64u, v0.u());
                lwc1(f0, s1, 4);
                backedge(ctx);
            } else {
                // 0x0046bdd4: textured: 1 the raster, 9 the filter, 2 the addressing (0 when U and V differ)
                charge(ctx, 7);
                lw(v1, a0, rw_texture::kFilterAddr);
                v0 = v1 & 0xF000;
                s6 = srl(v0, 12);
                v0 = v1 & 0xF00;
                v0 = srl(v0, 8);
                s7 = v1 & 0xFF;
                if (v0 != s6) {
                    // 0x0046bdf8
                    charge(ctx, 1);
                    s6 = 0;
                } else {
                    // 0x0046bdf0
                    charge(ctx, 2);
                }
                // 0x0046bdfc
                charge(ctx, 15);
                s0 = hi(kRenderStateSet);
                lw(a1, a0, rw_texture::kRaster);
                s0 = addiu(s0, lo(kRenderStateSet));
                lw(v0, s0, 0);  // pfn_RwRenderStateSet
                a0 = 1;
                jalr(ctx, 0x46BE0Cu, v0.u());
                lw(v0, s0, 0);  // pfn_RwRenderStateSet
                a1 = s7;
                a0 = 9;
                jalr(ctx, 0x46BE1Cu, v0.u());
                lw(v0, s0, 0);  // pfn_RwRenderStateSet
                a1 = s6;
                a0 = 2;
                jalr(ctx, 0x46BE2Cu, v0.u());
                lwc1(f0, s1, 4);
            }
            // 0x0046be38: the bounds (sub_4AC020 into sp + 0xA0..0xAC, from the first vertex) give the UV origin and
            // scale;
            // the draw globals; sub_4F2710 opens the packet record
            charge(ctx, 45);
            s0 = addiu(sp, 0xA8);
            a0 = s3;
            s6 = addiu(sp, 0xA4);
            s3 = addiu(sp, 0xAC);
            a1 = addiu(sp, 0xA0);
            swc1(f0, s0, 0);
            swc1(f0, sp, 0xA0);
            lwc1(f0, s1, 8);
            swc1(f0, s3, 0);
            link(ctx, 0x46BE5Cu);  // $ra first: the delay slot below depends on it
            swc1(f0, s6, 0);
            call(ctx, gen::fn_sub_4AC020_004ac020);
            lwc1(f3, s0, 0);
            t2 = 0x3F800000;
            lwc1(f4, sp, 0xA0);
            v0 = hi(kRt2dUvOriginX);
            lwc1(f1, s6, 0);
            a3 = hi(kRt2dUvOriginY);
            lwc1(f0, s3, 0);
            t1 = hi(kRt2dUvScaleX);
            mtc1(t2, f2);
            t0 = hi(kRt2dUvScaleY);
            a2 = hi(kRt2dInset);
            a1 = hi(kRt2dBrush);
            a0 = hi(kRt2dInset);
            v1 = hi(kRt2dBrush);
            sub_s(f3, f3, f4);
            sub_s(f0, f0, f1);
            swc1(f1, a3, lo(kRt2dUvOriginY));
            div_s(f1, f2, f3);
            div_s(f0, f2, f0);
            swc1(f4, v0, lo(kRt2dUvOriginX));
            swc1(f1, t1, lo(kRt2dUvScaleX));
            v0 = hi(kRt2dWidth);
            swc1(f0, t0, lo(kRt2dUvScaleY));
            lwc1(f0, s5, rt2d_path::kInset);
            swc1(f0, a2, lo(kRt2dInset));
            sw(s4, a1, lo(kRt2dBrush));
            lwc1(f0, s5, rt2d_path::kInset);
            swc1(f0, a0, lo(kRt2dInset));
            sw(t2, v0, lo(kRt2dWidth));
            link(ctx, 0x46BED8u);  // $ra first: the delay slot below depends on it
            sw(s4, v1, lo(kRt2dBrush));
            call(ctx, gen::fn_sub_4F2710_004f2710);
            v1 = s2 & 0x1;
            if (v1 != 0) {
                // 0x0046beec
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            // 0x0046bef0: the record {count rounded up to even, the packet word, 20}; RxPipelineExecute(the fill
            // pipeline, record + 12, 0)
            charge(ctx, 19);
            v1 = hi(kRt2dVertices);
            a1 = hi(kRt2dCount);
            sw(s1, v1, lo(kRt2dVertices));
            a0 = hi(kRt2dPacketWord);
            v1 = hi(kRt2dLastVertex);
            sw(s2, a1, lo(kRt2dCount));
            sw(fp, v1, lo(kRt2dLastVertex));
            a3 = 20;
            sh(s2, v0, 0);
            v1 = hi(kRt2dFillPipe);
            lw(a0, a0, lo(kRt2dPacketWord));
            a1 = addiu(v0, 12);
            sw(a0, v0, 4);
            sw(a3, v0, 8);
            lw(a0, v1, lo(kRt2dFillPipe));
            a2 = 0;
            jal(ctx, 0x46BF2Cu, gen::fn_RxPipelineExecute_004f2e70);
            if (v0 == 0) {
                // 0x0046bf3c: the pipeline failed: 0
                charge(ctx, 2);
                v0 = 0;
                // 0x0046bf74 (the shared epilogue, written out on this path)
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
                sp = addiu(sp, 0xB0);
                return;
            }
        }
        // 0x0046bf44: the next path (+20), recursively
        charge(ctx, 3);
        lw(a0, s5, rt2d_path::kNext);
        a1 = s4;
        jal(ctx, 0x46BF48u, gen::fn_sub_46BD00_0046bd00);
    }
    // 0x0046bf50
    charge(ctx, 2);
    v0 = s5;
    // 0x0046bf74 (the shared epilogue, written out on this path)
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
    sp = addiu(sp, 0xB0);
}

// 0x0046B1B0 skinInstanceWeights -- 864 bytes; leaf frame (no stack)
// skinInstanceWeights [skin weights at instance] (mesh $a0, skin $a1, destination $a2): for each of the mesh's indices (u16
// array +0, count +4) the 16-byte weight record of that vertex (skin +24 array) to the destination, 8 per iteration
// while at least 9 remain (and the count is a positive 32-bit value), then one at a time.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: the hand version terminated the host on a random world).
void skinInstanceWeights(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lhu, hg::lw, hg::lwc1,
          hg::sll, hg::slt, hg::slti, hg::swc1;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    Fpr f0{ctx, 0};
    // 0x0046b1b0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(t0, a0, mesh_rd::kIndices);  // t0 = the mesh's u16 indices
    lw(a1, a1, skin_rd::kWeights);  // a1 = the skin's 16-byte weight records
    lw(a0, a0, mesh_rd::kIndexCount);  // a0 = the index count
    at = slt(0, a0);
    a3 = 0;  // a3 = the indices done
    if (at != 0) {
        // 0x0046b1c8: count > 8?
        charge(ctx, 3);
        at = slti(a0, 9);
        v1 = addiu(a0, -8);  // v1 = count - 8
        if (at == 0) {
            // 0x0046b1d4: the unrolled loop's guard: 0 <= count < 0x7FFFFFFF
            charge(ctx, 3);
            at = slt(a0, 0);
            t1 = 0;
            if (at == 0) {
                // 0x0046b1e0
                charge(ctx, 5);
                at = 0x7FFF0000;
                at = at | 0xFFFF;
                at = slt(a0, at);
                if (at != 0) {
                    // 0x0046b1f4
                    charge(ctx, 1);
                    t1 = 1;
                }
            }
            // 0x0046b1f8
            charge(ctx, 2);
            if (t1 != 0) {
                for (;;) {
                    // 0x0046b200: eight vertices: their weight records (16 bytes each) to the destination
                    charge(ctx, 165);
                    lhu(t2, t0, 0);
                    a3 = addiu(a3, 8);
                    t1 = slt(a3, v1);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 0);
                    swc1(f0, a2, 0);
                    lhu(t2, t0, 0);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 4);
                    swc1(f0, a2, 4);
                    lhu(t2, t0, 0);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 8);
                    swc1(f0, a2, 8);
                    lhu(t2, t0, 0);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 12);
                    swc1(f0, a2, 12);
                    lhu(t2, t0, 2);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 0);
                    swc1(f0, a2, 16);
                    lhu(t2, t0, 2);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 4);
                    swc1(f0, a2, 20);
                    lhu(t2, t0, 2);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 8);
                    swc1(f0, a2, 24);
                    lhu(t2, t0, 2);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 12);
                    swc1(f0, a2, 28);
                    lhu(t2, t0, 4);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 0);
                    swc1(f0, a2, 32);
                    lhu(t2, t0, 4);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 4);
                    swc1(f0, a2, 36);
                    lhu(t2, t0, 4);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 8);
                    swc1(f0, a2, 40);
                    lhu(t2, t0, 4);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 12);
                    swc1(f0, a2, 44);
                    lhu(t2, t0, 6);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 0);
                    swc1(f0, a2, 48);
                    lhu(t2, t0, 6);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 4);
                    swc1(f0, a2, 52);
                    lhu(t2, t0, 6);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 8);
                    swc1(f0, a2, 56);
                    lhu(t2, t0, 6);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 12);
                    swc1(f0, a2, 60);
                    lhu(t2, t0, 8);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 0);
                    swc1(f0, a2, 64);
                    lhu(t2, t0, 8);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 4);
                    swc1(f0, a2, 68);
                    lhu(t2, t0, 8);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 8);
                    swc1(f0, a2, 72);
                    lhu(t2, t0, 8);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 12);
                    swc1(f0, a2, 76);
                    lhu(t2, t0, 10);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 0);
                    swc1(f0, a2, 80);
                    lhu(t2, t0, 10);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 4);
                    swc1(f0, a2, 84);
                    lhu(t2, t0, 10);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 8);
                    swc1(f0, a2, 88);
                    lhu(t2, t0, 10);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 12);
                    swc1(f0, a2, 92);
                    lhu(t2, t0, 12);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 0);
                    swc1(f0, a2, 96);
                    lhu(t2, t0, 12);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 4);
                    swc1(f0, a2, 100);
                    lhu(t2, t0, 12);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 8);
                    swc1(f0, a2, 104);
                    lhu(t2, t0, 12);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 12);
                    swc1(f0, a2, 108);
                    lhu(t2, t0, 14);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 0);
                    swc1(f0, a2, 112);
                    lhu(t2, t0, 14);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 4);
                    swc1(f0, a2, 116);
                    lhu(t2, t0, 14);
                    t2 = sll(t2, 4);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 8);
                    swc1(f0, a2, 120);
                    lhu(t2, t0, 14);
                    t2 = sll(t2, 4);
                    t0 = addiu(t0, 16);
                    t2 = addu(a1, t2);
                    lwc1(f0, t2, 12);
                    swc1(f0, a2, 124);
                    a2 = addiu(a2, 128);
                    if (t1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0046b494
                charge(ctx, 1);
            }
        }
        // 0x0046b498
        charge(ctx, 3);
        at = slt(a3, a0);
        if (at != 0) {
            for (;;) {
                // 0x0046b4a4
                charge(ctx, 25);
                lhu(t1, t0, 0);
                a3 = addiu(a3, 1);
                v1 = slt(a3, a0);
                t1 = sll(t1, 4);
                t1 = addu(a1, t1);
                lwc1(f0, t1, 0);
                swc1(f0, a2, 0);
                lhu(t1, t0, 0);
                t1 = sll(t1, 4);
                t1 = addu(a1, t1);
                lwc1(f0, t1, 4);
                swc1(f0, a2, 4);
                lhu(t1, t0, 0);
                t1 = sll(t1, 4);
                t1 = addu(a1, t1);
                lwc1(f0, t1, 8);
                swc1(f0, a2, 8);
                lhu(t1, t0, 0);
                t1 = sll(t1, 4);
                t0 = addiu(t0, 2);
                t1 = addu(a1, t1);
                lwc1(f0, t1, 12);
                swc1(f0, a2, 12);
                a2 = addiu(a2, 16);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x0046b508 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x004687E0 sub_4687E0 -- 1128 bytes; frame 0xE0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4687E0 [MatFX dual / environment raster combine] (second texture $a0 or 0, base texture $a1): the base raster
// (*$a1 -> raster s0) is read into a 32-bit image (sub_4CBE00 create, sub_4CBF20 pixels, sub_4CDC70 from raster);
// the second texture's raster likewise -- or, without one, an image of the base size filled with 0xFFFFFFFF (8 words
// per iteration while at least 9 remain in the row, then one at a time; image +16 stride, +20 pixels); a size mismatch
// resamples the base image to the second's size (sub_4CEC10, the old image freed by sub_4CBEB0); the two are combined
// (sub_4CC0A0, sub_4CC1D0), the raster format chosen (sub_4CDD50 into the frame words sp + 208..220; 0x9000 added when
// the source raster format has bit 15 of (+35 << 8)), a raster created and filled (sub_4CE0F0, sub_4CDCE0) and wrapped in
// a texture (sub_4D0E40) whose filter / addressing word (+80) takes the source texture's filter byte and its U / V
// nibbles (0 when they differ); both images freed; the 32-byte name buffer at sp + 176 zeroed, named by sub_468720 and set
// (sub_4D0FD0). Returns the new texture.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: frame/spills (own frame)).
void sub_4687E0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld,
          hg::link, hg::lq, hg::lui, hg::lw, hg::mult, hg::mult1, hg::sb, hg::sd, hg::si, hg::sll, hg::slt, hg::slti,
          hg::sq, hg::srl, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004687e0
    enter(ctx, 29);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    a2 = 32;
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    s6 = 0;
    sq(s4, sp, 0x40);
    s5 = a0;  // s5 = the second texture (or 0)
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a1, rw_texture::kRaster);  // s0 = the base raster
    sw(a1, sp, 0xAC);  // the base texture, kept at sp+0xAC
    lw(s7, s0, rw_raster::kWidth);  // s7 x fp = its size
    lw(fp, s0, rw_raster::kHeight);
    a0 = s7;
    a1 = fp;
    jal(ctx, 0x46882Cu, gen::fn_sub_4CBE00_004cbe00);  // the base image s2 = a 32-bit image of the base raster
    s2 = v0;
    a0 = s2;
    jal(ctx, 0x468838u, gen::fn_sub_4CBF20_004cbf20);
    a0 = s2;
    a1 = s0;
    jal(ctx, 0x468844u, gen::fn_sub_4CDC70_004cdc70);
    if (s5 == 0) {
        // 0x004689f0: no second texture: s1 = an image of the base size, every pixel 0xFFFFFFFF
        charge(ctx, 12);
        lw(s4, s0, rw_raster::kWidth);
        a2 = 32;
        lw(s3, s0, rw_raster::kHeight);
        a0 = s4;
        a1 = s3;
        jal(ctx, 0x468A00u, gen::fn_sub_4CBE00_004cbe00);
        s1 = v0;
        a0 = s1;
        jal(ctx, 0x468A0Cu, gen::fn_sub_4CBF20_004cbf20);
        at = slt(0, s3);
        a2 = 0;
        if (at == 0) {
            backedge(ctx);
        } else {
            // 0x00468a20
            charge(ctx, 3);
            v0 = si(-1);
            v1 = 1;
            a0 = addiu(s4, -8);
            for (;;) {
                // 0x00468a2c: per row (a2): 8 words per iteration while at least 9 remain, then one at a time
                charge(ctx, 3);
                at = slt(0, s4);
                a3 = 0;
                if (at != 0) {
                    // 0x00468a38
                    charge(ctx, 3);
                    at = slti(s4, 9);
                    if (at == 0) {
                        // 0x00468a44
                        charge(ctx, 3);
                        at = slt(s4, 0);
                        a1 = 0;
                        if (at == 0) {
                            // 0x00468a50
                            charge(ctx, 5);
                            at = 0x7FFF0000;
                            at = at | 0xFFFF;
                            at = slt(s4, at);
                            if (at != 0) {
                                // 0x00468a64
                                charge(ctx, 1);
                                a1 = v1;
                            }
                        }
                        // 0x00468a68
                        charge(ctx, 2);
                        if (a1 != 0) {
                            // 0x00468a70
                            charge(ctx, 2);
                            a1 = 0;
                            for (;;) {
                                // 0x00468a78
                                charge(ctx, 52);
                                lw(t0, s1, rw_image::kStride);
                                mult(t1, t0, a2);
                                lw(t0, s1, rw_image::kPixels);
                                t0 = addu(t0, t1);
                                t0 = addu(t0, a1);
                                sw(v0, t0, 0);
                                lw(t0, s1, rw_image::kStride);
                                mult1(t1, t0, a2);
                                lw(t0, s1, rw_image::kPixels);
                                t0 = addu(t0, t1);
                                t0 = addu(t0, a1);
                                sw(v0, t0, 4);
                                lw(t0, s1, rw_image::kStride);
                                mult(t1, t0, a2);
                                lw(t0, s1, rw_image::kPixels);
                                t0 = addu(t0, t1);
                                t0 = addu(t0, a1);
                                sw(v0, t0, 8);
                                lw(t0, s1, rw_image::kStride);
                                mult1(t1, t0, a2);
                                lw(t0, s1, rw_image::kPixels);
                                t0 = addu(t0, t1);
                                t0 = addu(t0, a1);
                                sw(v0, t0, 12);
                                lw(t0, s1, rw_image::kStride);
                                mult(t1, t0, a2);
                                lw(t0, s1, rw_image::kPixels);
                                t0 = addu(t0, t1);
                                t0 = addu(t0, a1);
                                sw(v0, t0, 16);
                                lw(t0, s1, rw_image::kStride);
                                mult1(t1, t0, a2);
                                lw(t0, s1, rw_image::kPixels);
                                t0 = addu(t0, t1);
                                t0 = addu(t0, a1);
                                sw(v0, t0, 20);
                                lw(t0, s1, rw_image::kStride);
                                mult(t1, t0, a2);
                                lw(t0, s1, rw_image::kPixels);
                                t0 = addu(t0, t1);
                                t0 = addu(t0, a1);
                                sw(v0, t0, 24);
                                lw(t0, s1, rw_image::kStride);
                                mult1(t2, t0, a2);
                                lw(t1, s1, rw_image::kPixels);
                                a3 = addiu(a3, 8);
                                t0 = slt(a3, a0);
                                t1 = addu(t1, t2);
                                t1 = addu(t1, a1);
                                sw(v0, t1, 28);
                                a1 = addiu(a1, 32);
                                if (t0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                        }
                    }
                    // 0x00468b48
                    charge(ctx, 3);
                    at = slt(a3, s4);
                    if (at != 0) {
                        // 0x00468b54
                        charge(ctx, 1);
                        t2 = sll(a3, 2);
                        for (;;) {
                            // 0x00468b58
                            charge(ctx, 10);
                            lw(a1, s1, rw_image::kStride);
                            mult(t1, a1, a2);
                            lw(t0, s1, rw_image::kPixels);
                            a3 = addiu(a3, 1);
                            a1 = slt(a3, s4);
                            t0 = addu(t0, t1);
                            t0 = addu(t0, t2);
                            sw(v0, t0, 0);
                            t2 = addiu(t2, 4);
                            if (a1 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                }
                // 0x00468b80
                charge(ctx, 4);
                a2 = addiu(a2, 1);
                a1 = slt(a2, s3);
                if (a1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x00468b90
            charge(ctx, 2);
            backedge(ctx);
        }
    } else {
        // 0x00468854: s1 = the second texture's raster as a 32-bit image
        charge(ctx, 13);
        lw(s6, s5, rw_texture::kRaster);  // s6 = its raster; s4 x s3 its size
        a2 = 32;
        lw(s4, s6, rw_raster::kWidth);
        lw(s3, s6, rw_raster::kHeight);
        a0 = s4;
        a1 = s3;
        jal(ctx, 0x468868u, gen::fn_sub_4CBE00_004cbe00);
        s1 = v0;
        a0 = s1;
        jal(ctx, 0x468874u, gen::fn_sub_4CBF20_004cbf20);
        a0 = s1;
        a1 = s6;
        jal(ctx, 0x468880u, gen::fn_sub_4CDC70_004cdc70);
    }
    // 0x00468888: the second image's size (s4 x s3) against the base's (s7 x fp)
    charge(ctx, 2);
    do {
        if (s4 == s7) {
            // 0x00468890
            charge(ctx, 2);
            if (s3 == fp) {
                break;  // the same size
            }
        }
        // 0x00468b98: resample the base image to the second's size (a new 32-bit image), the old one freed
        charge(ctx, 14);
        a0 = s4;
        a1 = s3;
        a2 = 32;
        jal(ctx, 0x468BA0u, gen::fn_sub_4CBE00_004cbe00);
        s3 = v0;
        a0 = s3;
        jal(ctx, 0x468BACu, gen::fn_sub_4CBF20_004cbf20);
        a0 = s3;
        a1 = s2;
        jal(ctx, 0x468BB8u, gen::fn_sub_4CEC10_004cec10);
        a0 = s2;
        jal(ctx, 0x468BC0u, gen::fn_sub_4CBEB0_004cbeb0);
        s2 = s3;
        backedge(ctx);
    } while (false);
    // 0x00468898: combine the two (sub_4CC0A0, sub_4CC1D0)
    charge(ctx, 14);
    a0 = s2;
    jal(ctx, 0x468898u, gen::fn_sub_4CC0A0_004cc0a0);
    a0 = s1;
    a1 = s2;
    jal(ctx, 0x4688A4u, gen::fn_sub_4CC1D0_004cc1d0);
    a0 = s1;  // the raster format for the combined image (sp+0xDC..0xD0)
    a1 = 4;
    a2 = addiu(sp, 0xDC);
    a3 = addiu(sp, 0xD8);
    t0 = addiu(sp, 0xD4);
    t1 = addiu(sp, 0xD0);
    jal(ctx, 0x4688C0u, gen::fn_sub_4CDD50_004cdd50);
    if (s5 == 0) {
        // 0x004688dc: the format flag (raster +35 bit 7): 0x9000 more in the format word
        charge(ctx, 2);
        lbu(v0, s0, rw_raster::kFormatHi);
        v0 = sll(v0, 8);
    } else {
        // 0x004688d0
        charge(ctx, 3);
        lbu(v0, s6, rw_raster::kFormatHi);
        v0 = sll(v0, 8);
    }
    // 0x004688e4
    charge(ctx, 3);
    v0 = v0 & 0x8000;
    if (v0 != 0) {
        // 0x00468bd0
        charge(ctx, 4);
        lw(v0, sp, 0xD0);
        v0 = v0 | 0x9000;
        sw(v0, sp, 0xD0);
        backedge(ctx);
    }
    // 0x004688f0: the raster (sub_4CE0F0) from the image (sub_4CDCE0), wrapped in a texture (sub_4D0E40): s0
    charge(ctx, 13);
    lw(a1, sp, 0xD8);
    lw(a2, sp, 0xD4);
    lw(a3, sp, 0xD0);
    link(ctx, 0x4688FCu);  // $ra first: the delay slot below depends on it
    lw(a0, sp, 0xDC);
    call(ctx, gen::fn_sub_4CE0F0_004ce0f0);
    s0 = v0;
    a1 = s1;
    a0 = s0;
    jal(ctx, 0x46890Cu, gen::fn_sub_4CDCE0_004cdce0);
    a0 = s0;
    jal(ctx, 0x468914u, gen::fn_sub_4D0E40_004d0e40);
    s0 = v0;
    if (s5 == 0) {
        // 0x00468be0: the source texture's filter and its U / V addressing (0 when they differ) for the new texture
        charge(ctx, 9);
        lw(v0, sp, 0xAC);
        a2 = 0xF000;
        lw(v1, v0, rw_texture::kFilterAddr);
        v0 = v1 & 0xF000;
        a3 = srl(v0, 12);
        v0 = v1 & 0xF00;
        v0 = srl(v0, 8);
        a0 = v1 & 0xFF;
        if (v0 != a3) {
            // 0x00468c0c
            charge(ctx, 1);
            a3 = 0;
        } else {
            // 0x00468c04
            charge(ctx, 2);
        }
        // 0x00468c10
        charge(ctx, 2);
        v1 = sll(a3, 12);
        backedge(ctx);
    } else {
        // 0x00468924
        charge(ctx, 8);
        lw(v1, s5, rw_texture::kFilterAddr);
        a2 = 0xF000;
        v0 = v1 & 0xF000;
        a3 = srl(v0, 12);
        v0 = v1 & 0xF00;
        v0 = srl(v0, 8);
        a0 = v1 & 0xFF;
        if (v0 != a3) {
            // 0x0046894c
            charge(ctx, 1);
            a3 = 0;
        } else {
            // 0x00468944
            charge(ctx, 2);
        }
        // 0x00468950
        charge(ctx, 1);
        v1 = sll(a3, 12);
    }
    // 0x00468954: the new texture's +80; both images freed
    charge(ctx, 23);
    a1 = sll(a3, 8);
    v1 = v1 & a2;
    a1 = a1 & 0xF00;
    lw(a2, s0, rw_texture::kFilterAddr);
    a3 = a1 | v1;
    a1 = lui(0xFFFF);
    v0 = a0 & 0xFF;
    a1 = a1 | 0xFF;
    v1 = si(-256);
    a0 = s1;
    a1 = a2 & a1;
    a1 = a1 | a3;
    sw(a1, s0, rw_texture::kFilterAddr);
    lw(a1, s0, rw_texture::kFilterAddr);
    v1 = a1 & v1;
    v0 = v1 | v0;
    link(ctx, 0x468994u);  // $ra first: the delay slot below depends on it
    sw(v0, s0, rw_texture::kFilterAddr);
    call(ctx, gen::fn_sub_4CBEB0_004cbeb0);
    a0 = s2;
    jal(ctx, 0x46899Cu, gen::fn_sub_4CBEB0_004cbeb0);
    v1 = addiu(sp, 0xB0);  // the 32-byte name buffer at sp+0xB0 zeroed
    v0 = 32;
    if (v1 != 0) {
        for (;;) {
            // 0x004689b0
            charge(ctx, 7);
            sb(zero, v1, 0);
            v0 = addiu(v0, -1);
            v1 = addiu(v1, 1);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004689cc: named by sub_468720, set (sub_4D0FD0); return the texture
    charge(ctx, 9);
    lw(a2, sp, 0xAC);
    a1 = s5;
    a0 = addiu(sp, 0xB0);
    jal(ctx, 0x4689D4u, gen::fn_sub_468720_00468720);
    a0 = s0;
    a1 = addiu(sp, 0xB0);
    jal(ctx, 0x4689E0u, gen::fn_sub_4D0FD0_004d0fd0);
    v0 = s0;
    // 0x00468c18
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
    sp = addiu(sp, 0xE0);
}

// 0x00497130 triStripExtend -- 1232 bytes; frame 0x10: ra sp+0x0
// triStripExtend [tri-strip: extend a strip] (strip $a0 = {u16 indices, count}, edge $a1, buckets $a2, mode $t0): from
// the strip's last edge, repeatedly: the free triangle across the edge (its +4 or +8 side; free = flag +28 clear in
// modes < 4, else +24 clear); none ends the walk. The triangle is taken (triStripTakeTriangle); of its three edges the one we
// came through ($t2: 0..2) gives the next one ((t2 + 1) % 3) and its far vertex ($t1); triStripTriangleEdge finds the edge from
// the strip's last vertex to it. When that edge leads to a free triangle the vertex is appended and the walk goes on
// through it; else the triangle's third edge ($t4) decides: with a free triangle beyond it the strip turns (an even
// count first repeats the second-to-last vertex as a swap) and continues there, otherwise the vertex closes the strip.
// Returns the number of triangles taken.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void triStripExtend(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::div, hg::enter, hg::jal, hg::ld, hg::lhu,
          hg::lw, hg::mfhi, hg::sd, hg::sh, hg::si, hg::sll, hg::slti, hg::sltu, hg::sw;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00497130
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a1;
    sd(ra, sp, 0x0);
    t8 = a0;
    t7 = a2;
    t6 = t0;
    t5 = 0;
    t4 = 0;
    if (v0 != 0) {
        for (;;) {
            // 0x00497154
            charge(ctx, 4);
            at = slti(t6, 4);
            t3 = 0;  // t3 = the free triangle across the edge, if any
            t2 = si(-1);
            do {
                if (at == 0) {
                    // 0x00497184: modes 4 and up: free = +24 clear; the edge's first side ...
                    charge(ctx, 3);
                    lw(a0, v0, tristrip_edge::kTri0);
                    if (a0 != 0) {
                        // 0x00497190
                        charge(ctx, 3);
                        lw(v1, a0, tristrip_tri::kTakenHi);
                        if (v1 == 0) {
                            // 0x0049719c
                            charge(ctx, 1);
                            t3 = a0;
                            break;
                        }
                    }
                    // 0x004974f8: ... then its second side
                    charge(ctx, 3);
                    lw(a0, v0, tristrip_edge::kTri1);
                    if (a0 == 0) {
                        backedge(ctx);
                    } else {
                        // 0x00497504
                        charge(ctx, 3);
                        lw(v1, a0, tristrip_tri::kTakenHi);
                        if (v1 != 0) {
                            backedge(ctx);
                        } else {
                            // 0x00497510
                            charge(ctx, 2);
                            t3 = a0;
                            backedge(ctx);
                        }
                    }
                } else {
                    // 0x00497164: modes below 4: free = +28 clear; the edge's first side ...
                    charge(ctx, 3);
                    lw(a0, v0, tristrip_edge::kTri0);
                    if (a0 != 0) {
                        // 0x00497170
                        charge(ctx, 3);
                        lw(v1, a0, tristrip_tri::kTakenLo);
                        if (v1 == 0) {
                            // 0x0049717c
                            charge(ctx, 2);
                            t3 = a0;
                            break;
                        }
                    }
                    // 0x004974d8: ... then its second side
                    charge(ctx, 3);
                    lw(a0, v0, tristrip_edge::kTri1);
                    if (a0 == 0) {
                        backedge(ctx);
                    } else {
                        // 0x004974e4
                        charge(ctx, 3);
                        lw(v1, a0, tristrip_tri::kTakenLo);
                        if (v1 != 0) {
                            backedge(ctx);
                        } else {
                            // 0x004974f0
                            charge(ctx, 2);
                            t3 = a0;
                            backedge(ctx);
                        }
                    }
                }
            } while (false);
            // 0x004971a0: none: the walk ends (0x00497518 is the loop's exit)
            charge(ctx, 2);
            if (t3 == 0) {
                break;
            }
            // 0x004971a8
            charge(ctx, 8);
            a0 = t3;
            a1 = t7;
            a2 = t6;
            t5 = addiu(t5, 1);
            jal(ctx, 0x4971B4u, gen::fn_triStripTakeTriangle_00496f60);
            lw(v1, t3, tristrip_tri::kEdge0);
            if (v0 == v1) {
                // 0x00497520
                charge(ctx, 2);
                t2 = 0;
                backedge(ctx);
            } else {
                // 0x004971c8
                charge(ctx, 3);
                lw(v1, t3, tristrip_tri::kEdge1);
                if (v0 == v1) {
                    // 0x00497528
                    charge(ctx, 2);
                    t2 = 1;
                    backedge(ctx);
                } else {
                    // 0x004971d4
                    charge(ctx, 3);
                    lw(v1, t3, tristrip_tri::kEdge2);
                    if (v0 == v1) {
                        // 0x004971e0
                        charge(ctx, 1);
                        t2 = 2;
                    }
                }
            }
            // 0x004971e4
            charge(ctx, 10);
            a0 = addiu(t2, 1);
            v1 = 3;
            div(a0, v1);
            mfhi(v1);
            v1 = sll(v1, 2);
            v1 = addu(t3, v1);
            lw(a0, v1, tristrip_tri::kEdge0);
            lw(v1, a0, tristrip_edge::kTri0);
            if (v1 != t3) {
                // 0x00497214
                charge(ctx, 1);
                lhu(v1, a0, tristrip_edge::kV0);
            } else {
                // 0x0049720c
                charge(ctx, 2);
                lhu(v1, a0, tristrip_edge::kV1);
            }
            // 0x00497218
            charge(ctx, 13);
            t1 = v1 & 0xFFFF;
            t2 = v0;
            lw(v1, t8, tristrip_strip::kCount);
            a0 = t3;
            lw(v0, t8, tristrip_strip::kIndices);
            v1 = sll(v1, 1);
            v0 = addu(v0, v1);
            lhu(a1, v0, -2);
            a2 = t1;
            jal(ctx, 0x497238u, gen::fn_triStripTriangleEdge_00496e80);
            at = slti(t6, 4);
            if (at == 0) {
                // 0x004972c8
                charge(ctx, 5);
                a0 = sltu(0, v0);
                v1 = 1;
                a0 = a0 ^ 0x1;
                a3 = v1;
                if (a0 == 0) {
                    // 0x004972dc
                    charge(ctx, 3);
                    lw(a0, v0, tristrip_edge::kTri1);
                    a2 = 0;
                    if (a0 != 0) {
                        // 0x004972e8
                        charge(ctx, 5);
                        lw(a0, a0, tristrip_tri::kTakenHi);
                        a0 = sltu(0, a0);
                        a0 = a0 ^ 0x1;
                        if (a0 != 0) {
                            // 0x004972fc
                            charge(ctx, 1);
                            a2 = v1;
                        }
                    }
                    // 0x00497300
                    charge(ctx, 3);
                    lw(a0, v0, tristrip_edge::kTri0);
                    a1 = 0;
                    if (a0 != 0) {
                        // 0x0049730c
                        charge(ctx, 5);
                        lw(a0, a0, tristrip_tri::kTakenHi);
                        a0 = sltu(0, a0);
                        a0 = a0 ^ 0x1;
                        if (a0 != 0) {
                            // 0x00497320
                            charge(ctx, 1);
                            a1 = 1;
                        }
                    }
                    // 0x00497324
                    charge(ctx, 3);
                    a0 = addu(a1, a2);
                    if (a0 != 0) {
                        // 0x00497330
                        charge(ctx, 2);
                        a3 = 0;
                    }
                }
                // 0x00497540
                charge(ctx, 2);
                if (a3 != 0) {
                    backedge(ctx);
                } else {
                    // 0x00497548
                    charge(ctx, 2);
                    v1 = 0;
                    backedge(ctx);
                }
            } else {
                // 0x0049724c
                charge(ctx, 5);
                a0 = sltu(0, v0);
                v1 = 1;
                a0 = a0 ^ 0x1;
                a3 = v1;
                if (a0 == 0) {
                    // 0x00497260
                    charge(ctx, 3);
                    lw(a0, v0, tristrip_edge::kTri1);
                    a2 = 0;
                    if (a0 != 0) {
                        // 0x0049726c
                        charge(ctx, 5);
                        lw(a0, a0, tristrip_tri::kTakenLo);
                        a0 = sltu(0, a0);
                        a0 = a0 ^ 0x1;
                        if (a0 != 0) {
                            // 0x00497280
                            charge(ctx, 1);
                            a2 = v1;
                        }
                    }
                    // 0x00497284
                    charge(ctx, 3);
                    lw(a0, v0, tristrip_edge::kTri0);
                    a1 = 0;
                    if (a0 != 0) {
                        // 0x00497290
                        charge(ctx, 5);
                        lw(a0, a0, tristrip_tri::kTakenLo);
                        a0 = sltu(0, a0);
                        a0 = a0 ^ 0x1;
                        if (a0 != 0) {
                            // 0x004972a4
                            charge(ctx, 1);
                            a1 = 1;
                        }
                    }
                    // 0x004972a8
                    charge(ctx, 3);
                    a0 = addu(a1, a2);
                    if (a0 != 0) {
                        // 0x004972b4
                        charge(ctx, 2);
                        a3 = 0;
                    }
                }
                // 0x00497530
                charge(ctx, 2);
                if (a3 != 0) {
                    backedge(ctx);
                } else {
                    // 0x00497538
                    charge(ctx, 2);
                    v1 = 0;
                    backedge(ctx);
                    // 0x004972c0
                    charge(ctx, 2);
                }
            }
            // 0x0049733c
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x004975d0
                charge(ctx, 9);
                lw(a0, t8, tristrip_strip::kCount);
                lw(v1, t8, tristrip_strip::kIndices);
                a0 = sll(a0, 1);
                v1 = addu(v1, a0);
                sh(t1, v1, 0);
                lw(v1, t8, tristrip_strip::kCount);
                v1 = addiu(v1, 1);
                sw(v1, t8, tristrip_strip::kCount);
                backedge(ctx);
            } else {
                // 0x00497344
                // t4 = the triangle's third edge: neither the one we came through (t2) nor the one found (v0)
                do {
                    charge(ctx, 3);
                    lw(v1, t3, tristrip_tri::kEdge0);
                    if (v1 != t2) {
                        // 0x00497350
                        charge(ctx, 2);
                        if (v1 != v0) {
                            // 0x00497358
                            charge(ctx, 1);
                            t4 = v1;
                            break;
                        }
                    }
                    // 0x00497550
                    charge(ctx, 3);
                    lw(v1, t3, tristrip_tri::kEdge1);
                    if (v1 != t2) {
                        // 0x0049755c
                        charge(ctx, 2);
                        if (v1 != v0) {
                            // 0x00497564
                            charge(ctx, 2);
                            t4 = v1;
                            backedge(ctx);
                            break;
                        }
                    }
                    // 0x0049756c
                    charge(ctx, 3);
                    lw(v1, t3, tristrip_tri::kEdge2);
                    if (v1 == t2) {
                        backedge(ctx);
                    } else {
                        // 0x00497578
                        charge(ctx, 2);
                        if (v1 == v0) {
                            backedge(ctx);
                        } else {
                            // 0x00497580
                            charge(ctx, 2);
                            t4 = v1;
                            backedge(ctx);
                        }
                    }
                } while (false);
                // 0x0049735c: a free triangle beyond the third edge?
                charge(ctx, 3);
                at = slti(t6, 4);
                if (at == 0) {
                    // 0x004973dc
                    charge(ctx, 3);
                    v0 = 0;
                    a2 = 0;
                    if (t4 != 0) {
                        // 0x004973e8
                        charge(ctx, 3);
                        lw(v1, t4, tristrip_edge::kTri1);
                        a1 = 0;
                        if (v1 != 0) {
                            // 0x004973f4
                            charge(ctx, 5);
                            lw(v1, v1, tristrip_tri::kTakenHi);
                            v1 = sltu(0, v1);
                            v1 = v1 ^ 0x1;
                            if (v1 != 0) {
                                // 0x00497408
                                charge(ctx, 1);
                                a1 = 1;
                            }
                        }
                        // 0x0049740c
                        charge(ctx, 3);
                        lw(v1, t4, tristrip_edge::kTri0);
                        a0 = 0;
                        if (v1 != 0) {
                            // 0x00497418
                            charge(ctx, 5);
                            lw(v1, v1, tristrip_tri::kTakenHi);
                            v1 = sltu(0, v1);
                            v1 = v1 ^ 0x1;
                            if (v1 != 0) {
                                // 0x0049742c
                                charge(ctx, 1);
                                a0 = 1;
                            }
                        }
                        // 0x00497430
                        charge(ctx, 3);
                        v1 = addu(a0, a1);
                        if (v1 != 0) {
                            // 0x0049743c
                            charge(ctx, 2);
                            a2 = 1;
                        }
                    }
                    // 0x00497598
                    charge(ctx, 2);
                    if (a2 == 0) {
                        backedge(ctx);
                    } else {
                        // 0x004975a0
                        charge(ctx, 2);
                        v0 = 1;
                        backedge(ctx);
                    }
                } else {
                    // 0x00497368
                    charge(ctx, 3);
                    v0 = 0;
                    a2 = 0;
                    if (t4 != 0) {
                        // 0x00497374
                        charge(ctx, 3);
                        lw(v1, t4, tristrip_edge::kTri1);
                        a1 = 0;
                        if (v1 != 0) {
                            // 0x00497380
                            charge(ctx, 5);
                            lw(v1, v1, tristrip_tri::kTakenLo);
                            v1 = sltu(0, v1);
                            v1 = v1 ^ 0x1;
                            if (v1 != 0) {
                                // 0x00497394
                                charge(ctx, 1);
                                a1 = 1;
                            }
                        }
                        // 0x00497398
                        charge(ctx, 3);
                        lw(v1, t4, tristrip_edge::kTri0);
                        a0 = 0;
                        if (v1 != 0) {
                            // 0x004973a4
                            charge(ctx, 5);
                            lw(v1, v1, tristrip_tri::kTakenLo);
                            v1 = sltu(0, v1);
                            v1 = v1 ^ 0x1;
                            if (v1 != 0) {
                                // 0x004973b8
                                charge(ctx, 1);
                                a0 = 1;
                            }
                        }
                        // 0x004973bc
                        charge(ctx, 3);
                        v1 = addu(a0, a1);
                        if (v1 != 0) {
                            // 0x004973c8
                            charge(ctx, 2);
                            a2 = 1;
                        }
                    }
                    // 0x00497588
                    charge(ctx, 2);
                    if (a2 == 0) {
                        backedge(ctx);
                    } else {
                        // 0x00497590
                        charge(ctx, 2);
                        v0 = 1;
                        backedge(ctx);
                        // 0x004973d4
                        charge(ctx, 2);
                    }
                }
                // 0x00497448
                charge(ctx, 2);
                if (v0 == 0) {
                    // 0x004975a8
                    charge(ctx, 10);
                    lw(a0, t8, tristrip_strip::kCount);
                    v0 = 0;
                    lw(v1, t8, tristrip_strip::kIndices);
                    a0 = sll(a0, 1);
                    v1 = addu(v1, a0);
                    sh(t1, v1, 0);
                    lw(v1, t8, tristrip_strip::kCount);
                    v1 = addiu(v1, 1);
                    sw(v1, t8, tristrip_strip::kCount);
                    backedge(ctx);
                } else {
                    // 0x00497450
                    charge(ctx, 4);
                    lw(v1, t8, tristrip_strip::kCount);
                    v0 = v1 & 0x1;
                    if (v0 == 0) {
                        // 0x00497484
                        charge(ctx, 17);
                        a0 = sll(v1, 1);
                        v0 = t4;
                        lw(v1, t8, tristrip_strip::kIndices);
                        a0 = addu(v1, a0);
                        lhu(v1, a0, -4);
                        sh(v1, a0, 0);
                        lw(v1, t8, tristrip_strip::kCount);
                        v1 = addiu(v1, 1);
                        sw(v1, t8, tristrip_strip::kCount);
                        lw(a0, t8, tristrip_strip::kCount);
                        lw(v1, t8, tristrip_strip::kIndices);
                        a0 = sll(a0, 1);
                        v1 = addu(v1, a0);
                        sh(t1, v1, 0);
                        lw(v1, t8, tristrip_strip::kCount);
                        v1 = addiu(v1, 1);
                        sw(v1, t8, tristrip_strip::kCount);
                    } else {
                        // 0x00497460
                        charge(ctx, 9);
                        a0 = sll(v1, 1);
                        v0 = 0;
                        lw(v1, t8, tristrip_strip::kIndices);
                        v1 = addu(v1, a0);
                        sh(t1, v1, 0);
                        lw(v1, t8, tristrip_strip::kCount);
                        v1 = addiu(v1, 1);
                        sw(v1, t8, tristrip_strip::kCount);
                    }
                }
            }
            // 0x004974c8
            charge(ctx, 2);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004974d0 / 0x00497518: return the triangles taken
    charge(ctx, 2);
    v0 = t5;
    // 0x004975f4 (the shared epilogue)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0049FAA0 PS2AllNodeInstance -- 924 bytes; frame 0x1B0: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// PS2AllNodeInstance (pipe data $a0): (re)instances one mesh. When the mesh instance flags (pd +52) ask for it (4 / 8):
// pd +52 |= 0x7FFF0; the vertex count to instance (mesh +4 index count; a tri-fan (header flag 2) becomes 3 (n - 2));
// ps2AllInstanceSizes sizes the clusters into the frame (sp + 128: 24-byte records per stream; sp + 420..428 the totals); the old
// resEntry (*slot, pd +48) is unlinked; the material pipeline's resEntry allocator (matPvt +4; with the release
// callback 0x49CC30) gets the new size -> *slot (0: returns 0); the resEntry header {+24 / +28 = 0, +40 object
// identifier (pd +24), +44 geometry flags (header +0, also pd +56), +36 count} and the per-stream records copied to
// +144..; the data address (resEntry + 24 + 432, 64-byte aligned, 128 when the pipeline asks (matPvt +180)) and the
// per-stream UNPACK targets (+48 / +52 of each instanced stream: matPvt +32 flags bit 0 set and 0x2000 clear) set up;
// ps2AllInstanceDmaChain writes the DMA tags. Then (always): the stream addresses (resEntry +48 + 8 k, matPvt +181 streams) gathered
// at sp + 80 (8 per iteration while at least 9), the instance callback (matPvt +8: (pd, sp + 80)) and the data written
// back to memory (SyncDCache over [resEntry data, resEntry + size + 219)). Returns the callback's result.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: the hand version terminated the host on a random world).
void PS2AllNodeInstance(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter,
          hg::jal, hg::jalr, hg::lbu, hg::ld, hg::lq, hg::lw, hg::lwc1, hg::sd, hg::si, hg::sll, hg::sltiu, hg::sltu,
          hg::sq, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0049fae8 .. 0x0049fbc8: the stream addresses (instance header +48 + 8 k, matPvt +181 streams) gathered at
    // sp + 0x50 (8 per iteration while at least 9), the instance callback (matPvt +8: (pd, sp + 0x50)), the data
    // written back (SyncDCache over [the resEntry data, resEntry + size + 219)); $v0 = the callback's result.
    // Shared by the path that instanced and the one that did not.
    auto run_callback = [&] {
        charge(ctx, 3);
        at = sltu(0, a2);
        a1 = 0;
        if (at != 0) {
            // 0x0049faf4
            charge(ctx, 3);
            at = sltiu(a2, 9);
            a0 = addiu(a2, -8);
            if (at == 0) {
                // 0x0049fb00
                charge(ctx, 2);
                t0 = s0;
                a3 = addiu(sp, 0x50);
                for (;;) {
                    // 0x0049fb08
                    charge(ctx, 21);
                    lw(v1, t0, 48);
                    a1 = addiu(a1, 8);
                    v0 = sltu(a1, a0);
                    sw(v1, a3, 0);
                    lw(v1, t0, 56);
                    sw(v1, a3, 4);
                    lw(v1, t0, 64);
                    sw(v1, a3, 8);
                    lw(v1, t0, 72);
                    sw(v1, a3, 12);
                    lw(v1, t0, 80);
                    sw(v1, a3, 16);
                    lw(v1, t0, 88);
                    sw(v1, a3, 20);
                    lw(v1, t0, 96);
                    sw(v1, a3, 24);
                    lw(v1, t0, 104);
                    sw(v1, a3, 28);
                    t0 = addiu(t0, 64);
                    a3 = addiu(a3, 32);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0049fb5c
                charge(ctx, 1);
            }
            // 0x0049fb60
            charge(ctx, 3);
            at = sltu(a1, a2);
            if (at != 0) {
                // 0x0049fb6c
                charge(ctx, 5);
                v0 = sll(a1, 2);
                v1 = sll(a1, 3);
                v0 = addu(v0, sp);
                a3 = addu(s0, v1);
                a0 = addiu(v0, 80);
                for (;;) {
                    // 0x0049fb80
                    charge(ctx, 7);
                    lw(v1, a3, 48);
                    a1 = addiu(a1, 1);
                    v0 = sltu(a1, a2);
                    sw(v1, a0, 0);
                    a3 = addiu(a3, 8);
                    a0 = addiu(a0, 4);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0049fb9c
                charge(ctx, 1);
            }
        }
        // 0x0049fba0
        charge(ctx, 14);
        lw(v0, s2, ps2all_matpvt::kInstanceCb);
        a0 = s3;
        a1 = addiu(sp, 0x50);
        jalr(ctx, 0x49FBA8u, v0.u());
        s1 = v0;
        lw(a0, s0, 8);
        lw(v0, s3, ps2all_pd::kResEntrySlot);
        lw(v1, v0, 0);
        lw(v0, v1, 8);
        v0 = addu(v1, v0);
        a1 = addiu(v0, 219);
        jal(ctx, 0x49FBC8u, gen::fn_SyncDCache_00503a58);
        v0 = s1;
    };
    // 0x0049faa0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1B0);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;  // s3 = pd
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    sw(zero, sp, 0x1AC);  // the three outs of ps2AllInstanceSizes (sp+0x1AC / 0x1A8 / 0x1A4)
    sw(zero, sp, 0x1A8);
    sw(zero, sp, 0x1A4);
    lw(v1, a0, ps2all_pd::kInstFlags);
    lw(s2, a0, ps2all_pd::kMatPvt);  // s2 = the material pipeline's private data
    lw(s1, a0, ps2all_pd::kResEntrySlot);  // s1 = the resEntry slot
    v0 = v1 & 0xC;  // re-instance asked (4 / 8)?
    lw(a0, s1, 0);  // the resEntry
    s0 = addiu(a0, res_entry::kHeader);  // s0 = its instance header
    if (v0 == 0) {
        // 0x0049fae4: no re-instance asked: the stream count, then the callback
        charge(ctx, 1);
        lbu(a2, s2, ps2all_matpvt::kStreamCount);
        run_callback();
    } else {
        // 0x0049fbd8: re-instance: pd +52 |= 0x7FFF0; the vertex count (a tri-fan's n indices become 3 (n - 2))
        charge(ctx, 10);
        v0 = 0x70000;
        v0 = v0 | 0xFFF0;
        v0 = v1 | v0;
        sw(v0, s3, ps2all_pd::kInstFlags);
        lw(v0, s3, ps2all_pd::kMeshHeader);  // the mesh header
        lw(v1, s3, ps2all_pd::kMesh);
        lw(v0, v0, mesh_hdr::kFlags);
        v0 = v0 & 0x2;  // a fan?
        lw(s0, v1, 4);  // s0 = the mesh's index count
        if (v0 != 0) {
            // 0x0049fd04
            charge(ctx, 6);
            v0 = dsll32(s0, 0);
            v0 = dsra32(v0, 0);
            v1 = addiu(v0, -2);
            v0 = sll(v1, 1);
            s0 = addu(v0, v1);
            backedge(ctx);
        }
        // 0x0049fc00: ps2AllInstanceSizes(pd, n, sp+0x80 (24-byte records per stream), the three outs): $v0 = the
        // resEntry size
        charge(ctx, 11);
        a1 = dsll32(s0, 0);
        a0 = s3;
        a1 = dsra32(a1, 0);
        a2 = addiu(sp, 0x80);
        a3 = addiu(sp, 0x1AC);
        t0 = addiu(sp, 0x1A8);
        t1 = addiu(sp, 0x1A4);
        jal(ctx, 0x49FC18u, gen::fn_ps2AllInstanceSizes_0049d4d0);
        lw(v1, s1, 0);
        if (v1 != 0) {  // the old resEntry unlinked
            // 0x0049fc2c
            charge(ctx, 2);
            sw(zero, v1, 16);
            sw(zero, s1, 0);
        }
        // 0x0049fc34: the material pipeline's resEntry allocator(pd, slot, size, release callback sub_49CC30) -> *slot
        charge(ctx, 11);
        a2 = v0;
        a3 = hi(kResEntryRelease);
        lw(v0, s2, ps2all_matpvt::kResEntryAlloc);
        a0 = s3;
        a1 = s1;
        a3 = addiu(a3, lo(kResEntryRelease));  // &sub_49CC30
        jalr(ctx, 0x49FC48u, v0.u());
        sw(v0, s1, 0);
        lw(a0, s1, 0);
        if (a0 == 0) {
            // 0x0049fd1c: none: return 0
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x0049fc60: the resEntry header; the stream records copied to +144..
            charge(ctx, 18);
            sw(zero, a0, res_entry::kHeader);
            v0 = dsll32(s0, 0);
            sw(zero, a0, res_entry::kHeader + 4);
            v0 = dsra32(v0, 0);
            lw(v1, s3, ps2all_pd::kObjectId);
            s0 = addiu(a0, 24);
            sw(v1, a0, res_entry::kObjectId);
            lw(v1, s3, ps2all_pd::kMeshHeader);
            lw(v1, v1, mesh_hdr::kFlags);
            sw(v1, s3, ps2all_pd::kGeomFlags);
            lw(v1, s3, ps2all_pd::kGeomFlags);
            sw(v1, a0, res_entry::kGeomFlags);
            sw(v0, a0, res_entry::kVertexCount);
            lw(v0, s3, ps2all_pd::kMorphStreams);
            v0 = addiu(v0, 10);
            at = sltu(0, v0);
            a1 = 0;
            if (at == 0) {
                // 0x0049fd24
                charge(ctx, 1);
                lw(a1, sp, 0x1AC);
            } else {
                // 0x0049fca8
                charge(ctx, 2);
                a0 = addiu(sp, 0x80);
                v1 = s0;
                for (;;) {
                    // 0x0049fcb0
                    charge(ctx, 19);
                    lwc1(f3, a0, 0);
                    a1 = addiu(a1, 1);
                    lwc1(f2, a0, 4);
                    lwc1(f1, a0, 8);
                    lwc1(f0, a0, 12);
                    swc1(f3, v1, 144);
                    swc1(f2, v1, 148);
                    swc1(f1, v1, 152);
                    swc1(f0, v1, 156);
                    lwc1(f1, a0, 16);
                    lwc1(f0, a0, 20);
                    swc1(f1, v1, 160);
                    a0 = addiu(a0, 24);
                    swc1(f0, v1, 164);
                    lw(v0, s3, ps2all_pd::kMorphStreams);
                    v0 = addiu(v0, 10);
                    v0 = sltu(a1, v0);
                    v1 = addiu(v1, 24);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0049fcfc
                charge(ctx, 2);
                lw(a1, sp, 0x1AC);
            }
            // 0x0049fd28
            charge(ctx, 16);
            v1 = addiu(s0, 432);
            v0 = si(-64);
            v1 = addiu(v1, 63);
            v1 = v1 & v0;
            a0 = 1;
            sw(a1, s0, 24);
            lw(v0, sp, 0x1A4);
            sw(v0, s0, 28);
            lw(v0, sp, 0x1A8);
            sw(v0, s0, 32);
            sw(zero, s0, 36);
            sw(zero, s0, 40);
            sw(a0, s0, 44);
            lbu(v0, s2, ps2all_matpvt::kDoubleBuffer);
            if (v0 != 0) {
                // 0x0049fd68
                charge(ctx, 3);
                v1 = addiu(v1, 127);
                v0 = si(-128);
                v1 = v1 & v0;
            }
            // 0x0049fd74
            charge(ctx, 7);
            sw(v1, s0, 8);
            t2 = 0;
            lw(a2, s3, ps2all_pd::kMorphStreams);
            v0 = addiu(a2, 10);
            at = sltu(0, v0);
            a1 = 0;
            if (at != 0) {
                // 0x0049fd90
                charge(ctx, 3);
                t1 = s2;
                t0 = s0;
                a3 = s0;
                for (;;) {
                    // 0x0049fd9c
                    charge(ctx, 4);
                    lw(v1, t1, 32);
                    v0 = v1 & 0x1;
                    a0 = addiu(t1, 32);
                    if (v0 != 0) {
                        // 0x0049fdac
                        charge(ctx, 3);
                        v0 = v1 & 0x2000;
                        if (v0 == 0) {
                            // 0x0049fdb8
                            charge(ctx, 2);
                            lw(v0, t0, 152);
                            if (a2 != 0) {
                                // 0x0049fdc0
                                charge(ctx, 2);
                                lw(v0, t0, 156);
                            }
                            // 0x0049fdc8
                            charge(ctx, 10);
                            v1 = sll(v0, 4);
                            lw(v0, s0, 8);
                            t2 = addiu(t2, 1);
                            v0 = addu(v0, v1);
                            sw(v0, a3, 48);
                            lw(v0, a0, 4);
                            v0 = sll(v0, 2);
                            sw(v0, a3, 52);
                            a3 = addiu(a3, 8);
                        }
                    }
                    // 0x0049fdf0
                    charge(ctx, 7);
                    lw(a2, s3, ps2all_pd::kMorphStreams);
                    a1 = addiu(a1, 1);
                    t1 = addiu(t1, 8);
                    v0 = addiu(a2, 10);
                    v0 = sltu(a1, v0);
                    t0 = addiu(t0, 24);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x0049fe0c
                charge(ctx, 1);
            }
            // 0x0049fe10
            charge(ctx, 4);
            a0 = s3;
            jal(ctx, 0x49FE10u, gen::fn_ps2AllInstanceDmaChain_0049dc70);
            lbu(a2, s2, ps2all_matpvt::kStreamCount);
            backedge(ctx);
            run_callback();
        }
    }
    // 0x0049fe20 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x1B0);
}

// 0x004A35C0 sub_4A35C0 -- 808 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4A35C0 [Im3D / PS2All: attach a pipeline to an object slot] (object $a0, pipeline $a1, slot $a2 < 10): slots 0..5
// first require pipeline flags (+8) for the slot (jump table 0x7BCB30: 0x68000000, 0x6C000000, 0x64000000, 0x6C000000,
// 0x6E000000 with 0x4000, 0x6E000000) and a pipeline name (+12) equal to "PS2" (0x7CDC60; the engine's string compare
// 0x960158; a different name returns 0, a missing flag 0); then (all slots) a name equal to "PS2" stores the pipeline
// into the object's slot array (sub_4F3F70; created by sub_4F3EC0(object, 64) and cleared -- 10 words of 0, +56 = 4,
// +48 / +52 = 4 * 69 -- when absent); a different name leaves it. Returns the object, or 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4A35C0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::jalr, hg::ld, hg::lq,
          hg::lw, hg::sd, hg::sll, hg::sltiu, hg::sq, hg::sw, hg::tail;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // The shared tails of the original's block layout, written out on each path that reaches them.
    auto epilogue = [&] {  // 0x004a38d4
        charge(ctx, 5);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x40);
    };
    auto finish = [&] {  // 0x004a38d0: $ra back, the epilogue
        charge(ctx, 1);
        ld(ra, sp, 0x30);
        epilogue();
    };
    auto finish2 = [&] {  // 0x004a37d8: the slot 4 case's copy
        charge(ctx, 2);
        ld(ra, sp, 0x30);
        epilogue();
    };
    // 0x004a36f4: the attach: a pipeline named "PS2" goes into the object's slot array (created when absent);
    // returns the object, or 0 when the array cannot be created. Every path ends the function.
    auto attach = [&] {
        charge(ctx, 8);
        v0 = hi(kRwStrCmp);
        a1 = hi(kStrPs2);
        lw(a0, s1, pipe_rd::kName);
        lw(v0, v0, lo(kRwStrCmp));
        a1 = addiu(a1, lo(kStrPs2));  // "PS2"
        jalr(ctx, 0x4A3704u, v0.u());
        if (v0 == 0) {
            // 0x004a3808: the name matches: the object's slot array
            charge(ctx, 4);
            a0 = s2;
            jal(ctx, 0x4A3808u, gen::fn_sub_4F3F70_004f3f70);
            if (v0 != 0) {
                // 0x004a3818
                charge(ctx, 1);
                v1 = sll(s0, 2);
                // 0x004a381c (written out on this path): array[slot] = pipeline
                charge(ctx, 3);
                v0 = addu(v0, v1);
                sw(s1, v0, 0);
                backedge(ctx);
                // 0x004a3714: return the object
                charge(ctx, 2);
                v0 = s2;
                finish();
            } else {
                // 0x004a3828: none yet: sub_4F3EC0(object, 64) creates it
                charge(ctx, 5);
                a0 = s2;
                a1 = 64;
                jal(ctx, 0x4A382Cu, gen::fn_sub_4F3EC0_004f3ec0);
                if (v0 == 0) {
                    // 0x004a38b8: failed
                    charge(ctx, 2);
                    a1 = 0;
                    backedge(ctx);
                } else {
                    // 0x004a383c: cleared: ten words of 0, then +60 = 0, +56 = 4, +52 = +48 = 69 * 4
                    charge(ctx, 2);
                    a1 = 0;
                    a0 = v0;
                    for (;;) {
                        // 0x004a3844
                        charge(ctx, 9);
                        sw(zero, a0, 0);
                        a1 = addiu(a1, 5);
                        sw(zero, a0, 4);
                        v1 = sltiu(a1, 10);
                        sw(zero, a0, 8);
                        sw(zero, a0, 12);
                        sw(zero, a0, 16);
                        a0 = addiu(a0, 20);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004a3868
                    charge(ctx, 16);
                    sw(zero, v0, 60);
                    v1 = 4;
                    sw(v1, v0, 56);
                    a1 = 1;
                    lw(a0, v0, 56);
                    v1 = sll(a0, 4);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 2);
                    v1 = addu(v1, a0);
                    sw(v1, v0, 52);
                    lw(a0, v0, 56);
                    v1 = sll(a0, 4);
                    v1 = addu(v1, a0);
                    v1 = sll(v1, 2);
                    v1 = addu(v1, a0);
                    sw(v1, v0, 48);
                }
                // 0x004a38a8
                charge(ctx, 2);
                if (a1 != 0) {
                    // 0x004a38c0: the new array
                    charge(ctx, 4);
                    a0 = s2;
                    jal(ctx, 0x4A38C0u, gen::fn_sub_4F3F70_004f3f70);
                    v1 = sll(s0, 2);
                    backedge(ctx);
                    // 0x004a381c (written out on this path): array[slot] = pipeline
                    charge(ctx, 3);
                    v0 = addu(v0, v1);
                    sw(s1, v0, 0);
                    backedge(ctx);
                    // 0x004a3714: return the object
                    charge(ctx, 2);
                    v0 = s2;
                    finish();
                } else {
                    // 0x004a38b0: return 0
                    charge(ctx, 2);
                    v0 = 0;
                    finish();
                }
            }
        } else {
            // 0x004a3714: another name: return the object
            charge(ctx, 2);
            v0 = s2;
            finish();
        }
    };
    // The name check of slots 0..5 (0x004a3734 and its copies): $v0 = the compare's result.
    auto name_check = [&] {
        charge(ctx, 8);
        v0 = hi(kRwStrCmp);
        a1 = hi(kStrPs2);
        lw(a0, s1, pipe_rd::kName);
        lw(v0, v0, lo(kRwStrCmp));
        a1 = addiu(a1, lo(kStrPs2));  // "PS2"
    };
    // 0x004a35c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;  // s2 = the object
    sq(s0, sp, 0x0);
    s1 = a1;  // s1 = the pipeline
    s0 = a2;  // s0 = the slot
    if (s2 == 0) {
        // 0x004a371c: no object: 0
        charge(ctx, 2);
        v0 = 0;
        finish();
        return;
    }
    // 0x004a35e4
    charge(ctx, 2);
    if (s1 == 0) {
        // 0x004a3724: no pipeline: 0
        charge(ctx, 2);
        v0 = 0;
        finish();
        return;
    }
    // 0x004a35ec
    charge(ctx, 3);
    at = sltiu(s0, 10);
    if (at == 0) {
        // 0x004a372c: slot 10 or more: 0
        charge(ctx, 2);
        v0 = 0;
        finish();
        return;
    }
    // 0x004a35f8
    charge(ctx, 3);
    at = sltiu(s0, 6);
    if (at == 0) {
        attach();  // slots 6..9: no flag or name check first
        return;
    }
    // 0x004a3604: slots 0..5: the slot's pipeline flag (jump table 0x7BCB30)
    charge(ctx, 7);
    v1 = hi(kJtAttachSlot);
    v0 = sll(s0, 2);
    v1 = addiu(v1, lo(kJtAttachSlot));
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    switch (v0.u()) {
    case 0x4A3620u:  // table[0]
        // 0x004a3620: slot 0: flag 0x68000000
        charge(ctx, 5);
        lw(v1, s1, pipe_rd::kFlags);
        v0 = 0x68000000;
        v0 = v1 & v0;
        if (v0 != 0) {
            // 0x004a3734
            name_check();
            jalr(ctx, 0x4A3744u, v0.u());
            if (v0 != 0) {
                // 0x004a3754: another name
                charge(ctx, 2);
                backedge(ctx);
                // 0x004a3634: 0
                charge(ctx, 2);
                v0 = 0;
                finish();
                return;
            }
            backedge(ctx);
            attach();
            return;
        }
        // 0x004a3634: no flag: 0
        charge(ctx, 2);
        v0 = 0;
        finish();
        return;
    case 0x4A363Cu:  // table[1]
        // 0x004a363c: slot 1: flag 0x6C000000
        charge(ctx, 5);
        lw(v1, s1, pipe_rd::kFlags);
        v0 = 0x6C000000;
        v0 = v1 & v0;
        if (v0 != 0) {
            // 0x004a375c
            name_check();
            jalr(ctx, 0x4A376Cu, v0.u());
            if (v0 == 0) {
                backedge(ctx);
                attach();
                return;
            }
            // 0x004a377c: another name
            charge(ctx, 2);
            backedge(ctx);
        }
        // 0x004a3650: 0
        charge(ctx, 2);
        v0 = 0;
        finish();
        return;
    case 0x4A3658u:  // table[2]
        // 0x004a3658: slot 2: flag 0x64000000
        charge(ctx, 5);
        lw(v1, s1, pipe_rd::kFlags);
        v0 = 0x64000000;
        v0 = v1 & v0;
        if (v0 != 0) {
            // 0x004a3784
            name_check();
            jalr(ctx, 0x4A3794u, v0.u());
            if (v0 == 0) {
                backedge(ctx);
                attach();
                return;
            }
            // 0x004a37a4: another name
            charge(ctx, 2);
            backedge(ctx);
        }
        // 0x004a366c: 0
        charge(ctx, 2);
        v0 = 0;
        finish();
        return;
    case 0x4A3674u:  // table[3]
        // 0x004a3674: slot 3: flag 0x6C000000
        charge(ctx, 5);
        lw(v1, s1, pipe_rd::kFlags);
        v0 = 0x6C000000;
        v0 = v1 & v0;
        if (v0 != 0) {
            // 0x004a37ac
            name_check();
            jalr(ctx, 0x4A37BCu, v0.u());
            if (v0 == 0) {
                backedge(ctx);
                attach();
                return;
            }
            // 0x004a37cc: another name
            charge(ctx, 2);
            backedge(ctx);
        }
        // 0x004a3688: 0
        charge(ctx, 2);
        v0 = 0;
        finish();
        return;
    case 0x4A3690u:  // table[4]
        // 0x004a3690: slot 4: flags 0x6E000000 and 0x4000
        charge(ctx, 5);
        lw(v1, s1, pipe_rd::kFlags);
        v0 = 0x6E000000;
        v0 = v1 & v0;
        if (v0 != 0) {
            // 0x004a36a4
            charge(ctx, 3);
            v0 = v1 & 0x4000;
            if (v0 != 0) {
                // 0x004a36b0
                name_check();
                jalr(ctx, 0x4A36C0u, v0.u());
                if (v0 == 0) {
                    attach();
                    return;
                }
                // 0x004a36d0: another name: 0
                charge(ctx, 2);
                v0 = 0;
                finish2();
                return;
            }
        }
        // 0x004a37d4: a flag missing: 0
        charge(ctx, 1);
        v0 = 0;
        finish2();
        return;
    case 0x4A36D8u:  // table[5]
        // 0x004a36d8: slot 5: flag 0x6E000000
        charge(ctx, 5);
        lw(v1, s1, pipe_rd::kFlags);
        v0 = 0x6E000000;
        v0 = v1 & v0;
        if (v0 != 0) {
            // 0x004a37e0
            name_check();
            jalr(ctx, 0x4A37F0u, v0.u());
            if (v0 == 0) {
                backedge(ctx);
                attach();
                return;
            }
            // 0x004a3800: another name
            charge(ctx, 2);
            backedge(ctx);
        }
        // 0x004a36ec: 0
        charge(ctx, 2);
        v0 = 0;
        finish();
        return;
    default:  // not one of the table's targets: the dispatch table, as the recompiled body
        tail(ctx, v0.u());
        return;
    }
}

// 0x004A2BB0 ps2AllIm3DInstance -- 1300 bytes; frame 0x90: s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// ps2AllIm3DInstance [Im3D instance] (pipe data $a0): the Im3D vertices (record pd +8: +12 the 36-byte vertices) into the
// resEntry's clusters (resEntry +24 header; +8 the data, +24 vertices per cluster, +36 the vertex count; per stream at
// +144 / +192 / +240: the first cluster's count, the offset (+152 / +200 / +248, quadwords), the cluster stride
// (+160 / +208 / +256) and the last cluster's back-step (+164 / +212 / +260)). The vertex order comes from the walk
// tables at 0x7BCAxx (strip / list vs fan (header flag 2): per step the index byte of the three slots, the next slot
// (2 bits of $t9), the slot advance), over the mesh's indices (header flag 0x100 clear) or the identity table
// 0x7BCAD0; each cluster after the first re-sends the last `overlap` vertices ($t5: 2 for a strip (flag 1), 1 for a
// polyline (8), else 0). Streams (pd +52 instance flags x record +0 flags): positions (0x10 x 8; x, y, z), UVs (0x80
// x 1; u, v at +28), colours (0x40 x 0x10; RGBA bytes at +12 repacked through the frame bytes sp + 140..143). Returns 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void ps2AllIm3DInstance(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::lbu, hg::lh,
          hg::lhu, hg::lq, hg::lw, hg::lwc1, hg::sb, hg::sll, hg::sllv, hg::slt, hg::sq, hg::srlv, hg::subu, hg::sw,
          hg::swc1;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x004a2bb0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, ps2all_pd::kResEntrySlot);  // the resEntry slot
    lw(v0, a0, ps2all_pd::kMeshHeader);  // the mesh header
    lw(a2, a0, ps2all_pd::kObject);  // a2 = the Im3D record
    lw(v1, v1, 0);  // v1 = the resEntry
    lw(a3, v0, mesh_hdr::kFlags);  // a3 = the mesh header flags
    lw(s2, v1, res_entry::kVertexCount);  // s2 = the vertices to instance
    v0 = a3 & 0x2;  // a fan?
    a1 = addiu(v1, res_entry::kHeader);  // a1 = the instance header
    if (v0 == 0) {
        // 0x004a2c24: strips / lists: the walk's slot pattern (t9), start slot (t7) and index columns (t4, t3, t2);
        // fans their own
        charge(ctx, 10);
        v1 = hi(kWalkIm3D + walk::kListPattern);
        v0 = hi(kWalkIm3D + walk::kListStart);
        lbu(t9, v1, lo(kWalkIm3D + walk::kListPattern));
        t4 = hi(kWalkIm3D + walk::kListCol0);
        lbu(t7, v0, lo(kWalkIm3D + walk::kListStart));
        t3 = hi(kWalkIm3D + walk::kListCol1);
        t2 = hi(kWalkIm3D + walk::kListCol2);
        t4 = addiu(t4, lo(kWalkIm3D + walk::kListCol0));
        t3 = addiu(t3, lo(kWalkIm3D + walk::kListCol1));
        t2 = addiu(t2, lo(kWalkIm3D + walk::kListCol2));
    } else {
        // 0x004a2bf8
        charge(ctx, 11);
        v1 = hi(kWalkIm3D + walk::kFanPattern);
        v0 = hi(kWalkIm3D + walk::kFanStart);
        lbu(t9, v1, lo(kWalkIm3D + walk::kFanPattern));
        t4 = hi(kWalkIm3D + walk::kFanCol0);
        lbu(t7, v0, lo(kWalkIm3D + walk::kFanStart));
        t3 = hi(kWalkIm3D + walk::kFanCol1);
        t2 = hi(kWalkIm3D + walk::kFanCol2);
        t4 = addiu(t4, lo(kWalkIm3D + walk::kFanCol0));
        t3 = addiu(t3, lo(kWalkIm3D + walk::kFanCol1));
        t2 = addiu(t2, lo(kWalkIm3D + walk::kFanCol2));
    }
    // 0x004a2c4c: the overlap t5 each cluster after the first re-sends: 2 for a strip, 1 for a polyline, else 0
    charge(ctx, 3);
    v0 = a3 & 0x1;
    if (v0 != 0) {
        // 0x004a3038
        charge(ctx, 2);
        t5 = 2;
        backedge(ctx);
    } else {
        // 0x004a2c58
        charge(ctx, 3);
        v0 = a3 & 0x8;
        if (v0 == 0) {
            // 0x004a2c6c
            charge(ctx, 1);
            t5 = 0;
        } else {
            // 0x004a2c64
            charge(ctx, 2);
            t5 = 1;
        }
    }
    // 0x004a2c70: the index table t1: the identity table (no indices) or the mesh's indices (columns t4 / t3 swapped)
    charge(ctx, 3);
    v0 = a3 & 0x100;
    if (v0 != 0) {
        // 0x004a2c94
        charge(ctx, 2);
        t1 = hi(kWalkIm3D + walk::kIdentity);
        t1 = addiu(t1, lo(kWalkIm3D + walk::kIdentity));
    } else {
        // 0x004a2c7c
        charge(ctx, 6);
        lw(v0, a0, ps2all_pd::kMesh);
        v1 = t4;
        t4 = t3;
        lw(t1, v0, 0);
        t3 = v1;
    }
    // 0x004a2c9c: positions (instance flags 0x10 and record flags 8): x, y, z
    charge(ctx, 4);
    lw(v0, a0, ps2all_pd::kInstFlags);
    v0 = v0 & 0x10;
    if (v0 != 0) {
        // 0x004a2cac
        charge(ctx, 4);
        lw(v0, a2, im3d_rec::kFlags);
        v0 = v0 & 0x8;
        if (v0 != 0) {
            // 0x004a2cbc
            charge(ctx, 10);
            lw(a3, a1, strm(0, ps2all_stream::kOffset));
            t6 = 0;
            lw(v0, a1, ps2all_hdr::kData);
            t8 = t7;
            lw(v1, a2, im3d_rec::kVertices);
            s1 = s2;
            a3 = sll(a3, 4);
            t0 = addu(v0, a3);
            a3 = t0;
            if (i64(s2) > 0) {
                // 0x004a2ce4
                charge(ctx, 2);
                v0 = addiu(sp, 0x84);
                s7 = addiu(sp, 0x88);
                for (;;) {
                    // 0x004a2cec
                    charge(ctx, 4);
                    lw(s0, a1, ps2all_hdr::kClusterVerts);
                    at = slt(s0, s1);
                    if (at != 0) {
                        // 0x004a2d18
                        charge(ctx, 4);
                        lw(s0, a1, strm(0, ps2all_stream::kCount));
                        s3 = subu(s0, t5);
                        s1 = subu(s1, s3);
                    } else {
                        // 0x004a2cfc
                        charge(ctx, 7);
                        lh(a3, a1, strm(0, ps2all_stream::kLastBack));
                        s0 = s1;
                        s1 = 0;
                        a3 = sll(a3, 4);
                        t0 = subu(t0, a3);
                        a3 = t0;
                    }
                    // 0x004a2d28
                    charge(ctx, 3);
                    s3 = s0;
                    s0 = addiu(s0, -1);
                    if (s3 == 0) {
                        // 0x004a3040
                        charge(ctx, 1);
                        lh(a3, a1, strm(0, ps2all_stream::kStride));
                    } else {
                        // 0x004a2d34
                        charge(ctx, 1);
                        for (;;) {
                            // 0x004a2d38
                            charge(ctx, 36);
                            s3 = addu(t4, t6);
                            lbu(s6, s3, 0);
                            s3 = addu(t3, t6);
                            s6 = sllv(t8, s6);
                            lbu(s5, s3, 0);
                            s6 = sll(s6, 1);
                            s6 = addu(t1, s6);
                            s3 = addu(t2, t6);
                            s5 = sllv(t8, s5);
                            lbu(s4, s3, 0);
                            t6 = sll(t6, 1);
                            t6 = srlv(t9, t6);
                            t6 = t6 & 0x3;
                            t8 = addu(t8, s4);
                            s3 = s0;
                            lhu(s4, s6, 0);
                            s0 = addiu(s0, -1);
                            s4 = addu(s5, s4);
                            s5 = s4 & 0xFFFF;
                            s4 = sll(s5, 3);
                            s4 = addu(s4, s5);
                            s4 = sll(s4, 2);
                            s4 = addu(v1, s4);
                            lwc1(f1, s4, 4);
                            lwc1(f0, s4, 8);
                            lwc1(f2, s4, 0);
                            swc1(f1, sp, 0x84);
                            swc1(f0, sp, 0x88);
                            lwc1(f1, v0, 0);
                            lwc1(f0, s7, 0);
                            swc1(f2, a3, 0);
                            swc1(f2, sp, 0x80);
                            swc1(f1, a3, 4);
                            swc1(f0, a3, 8);
                            a3 = addiu(a3, 12);
                            if (s3 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004a2dc8
                        charge(ctx, 2);
                        lh(a3, a1, strm(0, ps2all_stream::kStride));
                    }
                    // 0x004a3044
                    charge(ctx, 5);
                    t8 = subu(t8, t5);
                    a3 = sll(a3, 4);
                    t0 = addu(t0, a3);
                    a3 = t0;
                    if (i64(s1) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004a3058
                charge(ctx, 2);
                backedge(ctx);
            }
        }
    }
    // 0x004a2dd0: UVs (instance flags 0x80 and record flags 1): u, v at vertex +28
    charge(ctx, 4);
    lw(v0, a0, ps2all_pd::kInstFlags);
    v0 = v0 & 0x80;
    if (v0 != 0) {
        // 0x004a2de0
        charge(ctx, 4);
        lw(v0, a2, im3d_rec::kFlags);
        v0 = v0 & 0x1;
        if (v0 != 0) {
            // 0x004a2df0
            charge(ctx, 10);
            lw(v1, a1, strm(2, ps2all_stream::kOffset));
            s1 = 0;
            lw(v0, a1, ps2all_hdr::kData);
            s3 = t7;
            lw(t0, a2, im3d_rec::kVertices);
            s0 = s2;
            v1 = sll(v1, 4);
            s5 = addu(v0, v1);
            s4 = s5;
            if (i64(s2) > 0) {
                for (;;) {
                    // 0x004a2e18
                    charge(ctx, 4);
                    lw(v0, a1, ps2all_hdr::kClusterVerts);
                    at = slt(v0, s0);
                    if (at != 0) {
                        // 0x004a2e48
                        charge(ctx, 4);
                        lw(t6, a1, strm(2, ps2all_stream::kCount));
                        v0 = subu(t6, t5);
                        s0 = subu(s0, v0);
                    } else {
                        // 0x004a2e28
                        charge(ctx, 7);
                        lh(v0, a1, strm(2, ps2all_stream::kLastBack));
                        t6 = s0;
                        s0 = 0;
                        v0 = sll(v0, 4);
                        s5 = subu(s5, v0);
                        s4 = s5;
                    }
                    // 0x004a2e58
                    charge(ctx, 3);
                    v0 = t6;
                    t6 = addiu(t6, -1);
                    if (v0 == 0) {
                        // 0x004a3060
                        charge(ctx, 1);
                        lh(v0, a1, strm(2, ps2all_stream::kStride));
                    } else {
                        // 0x004a2e64
                        charge(ctx, 1);
                        for (;;) {
                            // 0x004a2e68
                            charge(ctx, 29);
                            v0 = addu(t4, s1);
                            lbu(a3, v0, 0);
                            s6 = t6;
                            t6 = addiu(t6, -1);
                            v0 = addu(t3, s1);
                            a3 = sllv(s3, a3);
                            lbu(v1, v0, 0);
                            a3 = sll(a3, 1);
                            a3 = addu(t1, a3);
                            v0 = addu(t2, s1);
                            v1 = sllv(s3, v1);
                            lbu(v0, v0, 0);
                            s1 = sll(s1, 1);
                            s1 = srlv(t9, s1);
                            s1 = s1 & 0x3;
                            s3 = addu(s3, v0);
                            lhu(v0, a3, 0);
                            v0 = addu(v1, v0);
                            v1 = v0 & 0xFFFF;
                            v0 = sll(v1, 3);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addu(t0, v0);
                            lwc1(f0, v0, im3d_vertex::kU);
                            swc1(f0, s4, 0);
                            lwc1(f0, v0, im3d_vertex::kV);
                            swc1(f0, s4, 4);
                            s4 = addiu(s4, 8);
                            if (s6 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004a2edc
                        charge(ctx, 2);
                        lh(v0, a1, strm(2, ps2all_stream::kStride));
                    }
                    // 0x004a3064
                    charge(ctx, 5);
                    s3 = subu(s3, t5);
                    v0 = sll(v0, 4);
                    s5 = addu(s5, v0);
                    s4 = s5;
                    if (i64(s0) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004a3078
                charge(ctx, 2);
                backedge(ctx);
            }
        }
    }
    // 0x004a2ee8: colours (instance flags 0x40 and record flags 0x10): the RGBA bytes at vertex +12, through the frame
    // bytes
    // sp + 140..143
    charge(ctx, 4);
    lw(v0, a0, ps2all_pd::kInstFlags);
    v0 = v0 & 0x40;
    if (v0 != 0) {
        // 0x004a2ef8
        charge(ctx, 4);
        lw(v0, a2, im3d_rec::kFlags);
        v0 = v0 & 0x10;
        if (v0 != 0) {
            // 0x004a2f08
            charge(ctx, 8);
            lw(v1, a1, strm(4, ps2all_stream::kOffset));
            s0 = 0;
            lw(v0, a1, ps2all_hdr::kData);
            lw(t0, a2, im3d_rec::kVertices);
            v1 = sll(v1, 4);
            s3 = addu(v0, v1);
            s1 = s3;
            if (i64(s2) > 0) {
                // 0x004a2f28
                charge(ctx, 3);
                a3 = addiu(sp, 0x8D);
                a2 = addiu(sp, 0x8E);
                a0 = addiu(sp, 0x8F);
                for (;;) {
                    // 0x004a2f34
                    charge(ctx, 4);
                    lw(v0, a1, ps2all_hdr::kClusterVerts);
                    at = slt(v0, s2);
                    if (at != 0) {
                        // 0x004a2f60
                        charge(ctx, 4);
                        lw(t6, a1, strm(4, ps2all_stream::kCount));
                        v0 = subu(t6, t5);
                        s2 = subu(s2, v0);
                    } else {
                        // 0x004a2f44
                        charge(ctx, 7);
                        lh(v0, a1, strm(4, ps2all_stream::kLastBack));
                        t6 = s2;
                        s2 = 0;
                        v0 = sll(v0, 4);
                        s3 = subu(s3, v0);
                        s1 = s3;
                    }
                    // 0x004a2f70
                    charge(ctx, 3);
                    v0 = t6;
                    t6 = addiu(t6, -1);
                    if (v0 == 0) {
                        // 0x004a3080
                        charge(ctx, 1);
                        lh(v0, a1, strm(4, ps2all_stream::kStride));
                    } else {
                        // 0x004a2f7c
                        charge(ctx, 1);
                        for (;;) {
                            // 0x004a2f80
                            charge(ctx, 44);
                            v0 = addu(t4, s0);
                            lbu(v1, v0, 0);
                            s4 = addu(t2, s0);
                            lbu(s5, s4, 0);
                            v1 = sllv(t7, v1);
                            v0 = addu(t3, s0);
                            v1 = sll(v1, 1);
                            lbu(v0, v0, 0);
                            v1 = addu(t1, v1);
                            s0 = sll(s0, 1);
                            lhu(v1, v1, 0);
                            s0 = srlv(t9, s0);
                            s4 = t6;
                            s0 = s0 & 0x3;
                            t6 = addiu(t6, -1);
                            v0 = sllv(t7, v0);
                            t7 = addu(t7, s5);
                            v0 = addu(v0, v1);
                            v1 = v0 & 0xFFFF;
                            v0 = sll(v1, 3);
                            v0 = addu(v0, v1);
                            v0 = sll(v0, 2);
                            v0 = addu(t0, v0);
                            lbu(s6, v0, im3d_vertex::kColour);
                            lbu(s5, v0, im3d_vertex::kColour + 1);
                            lbu(v1, v0, im3d_vertex::kColour + 2);
                            sb(s6, sp, 0x8C);
                            sb(s5, sp, 0x8D);
                            lbu(v0, v0, im3d_vertex::kColour + 3);
                            sb(v1, sp, 0x8E);
                            lbu(s6, a3, 0);
                            lbu(v1, a2, 0);
                            lbu(s5, sp, 0x8C);
                            sb(v0, sp, 0x8F);
                            lbu(v0, a0, 0);
                            s6 = sll(s6, 8);
                            v1 = sll(v1, 16);
                            s5 = s5 | s6;
                            v1 = v1 | s5;
                            v0 = sll(v0, 24);
                            v0 = v0 | v1;
                            sw(v0, s1, 0);
                            s1 = addiu(s1, 4);
                            if (s4 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004a3030
                        charge(ctx, 2);
                        lh(v0, a1, strm(4, ps2all_stream::kStride));
                    }
                    // 0x004a3084
                    charge(ctx, 5);
                    t7 = subu(t7, t5);
                    v0 = sll(v0, 4);
                    s3 = addu(s3, v0);
                    s1 = s3;
                    if (i64(s2) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
    }
    // 0x004a3098 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    v0 = 1;
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x0049CC70 ps2AllMatClusterLayout -- 2140 bytes; frame 0x90: fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// ps2AllMatClusterLayout [PS2All material pipeline: the cluster layout] (material pipeline private data $a0): the instance modes
// (+496 lists, +184 strips / polylines: {vertices per primitive, overlap}; 12/0 and 4/2 when the pipeline flags (+176)
// have bit 0 or
// no type bits, else 4/0 with strips / polylines overlapping 1 when bits 2..3 are set); the two pseudo-streams (+112 =
// 0x68002001,
// +120 = 0x6E002001); $v1 = 1 unless an instanced stream (+32 + 8 k, bit 0) is not 0x2000 ("in the cluster"); the
// instanced / 0x10 stream count must equal +182 (else 0). Then for the strip record and the list record: the batch
// sizes (+8 vertices per cluster from the VU1 buffer size +4 over the stream count, rounded to whole primitives;
// +12 / +20 how many fit in 0xFFFF qwords; +16 the double-buffered size) -- 0 when a batch is smaller than one
// primitive -- the per-cluster quadword total (8 for the GIF tag (2 for list clusters), + each stream's size by its
// type, jump table 0x7BCA10, + 1 per stream header) and the per-stream records (24 bytes at the record + 24 k: +46 the
// stream index, +24 / +28 the vertices, +32 / +36 the offset, +40 / +42 the cluster size, +44 = 0; jump tables 0x7BC9C0
// / 0x7BC990 for the sizes), 10 streams for the first pass and 12 (with the pseudo-streams) for the second.
// Returns 1, or 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void ps2AllMatClusterLayout(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::div, hg::divu, hg::enter, hg::lbu, hg::lq,
          hg::lw, hg::mflo, hg::mult, hg::mult1, hg::sb, hg::sh, hg::sll, hg::slt, hg::sltiu, hg::sq, hg::sra,
          hg::subu, hg::sw, hg::tail;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30};
    // The epilogue 0x0049d4a0, written out on each path that returns.
    auto epilogue = [&] {
        charge(ctx, 11);
        lq(fp, sp, 0x80);
        lq(s7, sp, 0x70);
        lq(s6, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x90);
    };
    // 0x0049cc70
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, ps2all_matpvt::kPipeFlags);
    v0 = v1 & 0x1;
    // the cluster records' {vertices per primitive, overlap}: lists (+496) / strips and polylines (+184)
    if (v0 == 0) {
        // 0x0049cca8
        charge(ctx, 3);
        v0 = v1 & 0xFF;
        if (v0 == 0) {
            // 0x0049d274 (written out on this path): no type bits: lists {12, 0}, strips {4, 2}
            charge(ctx, 8);
            v0 = 12;
            v1 = 4;
            sb(v0, a0, ps2all_matpvt::kListRecord);
            sb(zero, a0, ps2all_matpvt::kListOverlap);
            v0 = 2;
            sb(v1, a0, ps2all_matpvt::kStripRecord);
            sb(v0, a0, ps2all_matpvt::kStripOverlap);
            backedge(ctx);
        } else {
            // 0x0049ccb4: type bits: lists {4, 0}, strips {4, 0} -- strips overlapping 1 with bits 2..3
            charge(ctx, 3);
            v0 = v1 & 0xC;
            if (v0 == 0) {
                // 0x0049ccdc
                charge(ctx, 5);
                v0 = 4;
                sb(v0, a0, ps2all_matpvt::kListRecord);
                sb(zero, a0, ps2all_matpvt::kListOverlap);
                sb(v0, a0, ps2all_matpvt::kStripRecord);
                sb(zero, a0, ps2all_matpvt::kStripOverlap);
            } else {
                // 0x0049ccc0
                charge(ctx, 7);
                v1 = 4;
                v0 = 1;
                sb(v1, a0, ps2all_matpvt::kListRecord);
                sb(zero, a0, ps2all_matpvt::kListOverlap);
                sb(v1, a0, ps2all_matpvt::kStripRecord);
                sb(v0, a0, ps2all_matpvt::kStripOverlap);
            }
        }
    } else {
        // 0x0049d274: pipeline flag bit 0: lists {12, 0}, strips {4, 2}
        charge(ctx, 8);
        v0 = 12;
        v1 = 4;
        sb(v0, a0, ps2all_matpvt::kListRecord);
        sb(zero, a0, ps2all_matpvt::kListOverlap);
        v0 = 2;
        sb(v1, a0, ps2all_matpvt::kStripRecord);
        sb(v0, a0, ps2all_matpvt::kStripOverlap);
        backedge(ctx);
    }
    // 0x0049ccf0: the two pseudo-streams; then the stream flags: t1 = the instanced streams, v1 = 1 unless an
    // instanced stream is outside the cluster
    charge(ctx, 10);
    v1 = 0x68000000;
    v0 = 0x6E000000;
    v1 = v1 | 0x2001;
    v0 = v0 | 0x2001;
    sw(v1, a0, sflags(10));
    t1 = 0;
    v1 = 1;
    sw(v0, a0, sflags(11));
    t0 = 0;
    a3 = a0;
    for (;;) {
        // 0x0049cd18
        charge(ctx, 4);
        lw(a2, a3, ps2all_matpvt::kStreamFlags);
        a1 = a2 & 0x1;
        if (a1 == 0) {
            // 0x0049d294: not instanced: counted when it has 0x10
            charge(ctx, 3);
            v0 = a2 & 0x10;
            if (v0 != 0) {
                // 0x0049d2a0
                charge(ctx, 2);
                backedge(ctx);
                // 0x0049cd28 (written out on this path)
                charge(ctx, 2);
                if (a1 != 0) {
                    // 0x0049cd30
                    charge(ctx, 3);
                    v0 = a2 & 0x2000;
                    if (v0 == 0) {
                        // 0x0049cd3c
                        charge(ctx, 1);
                        v1 = 0;
                    }
                }
                // 0x0049cd40
                charge(ctx, 2);
                v0 = addiu(t1, 1);
                t1 = v0 & 0xFF;
            } else {
                backedge(ctx);
            }
        } else {
            // 0x0049cd28: instanced: outside the cluster (no 0x2000) clears v1
            charge(ctx, 2);
            if (a1 != 0) {
                // 0x0049cd30
                charge(ctx, 3);
                v0 = a2 & 0x2000;
                if (v0 == 0) {
                    // 0x0049cd3c
                    charge(ctx, 1);
                    v1 = 0;
                }
            }
            // 0x0049cd40: counted
            charge(ctx, 2);
            v0 = addiu(t1, 1);
            t1 = v0 & 0xFF;
        }
        // 0x0049cd48: the next of the ten streams
        charge(ctx, 4);
        t0 = addiu(t0, 1);
        v0 = sltiu(t0, 10);
        a3 = addiu(a3, 8);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0049cd58: the instanced count must equal +182: else return 0
    charge(ctx, 5);
    sb(v1, a0, ps2all_matpvt::kDoubleBuffer);
    t8 = t1 & 0xFF;
    lbu(v0, a0, ps2all_matpvt::kInstStreams);
    if (t8 != v0) {
        // 0x0049d2a8
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x0049cd6c: two passes (v0 = 1, 2): the list record (a1 = +496), then the strip record (+184)
        charge(ctx, 17);
        v0 = 1;
        t4 = hi(kJtLayoutClusterQw);
        t0 = hi(kJtLayoutStreamSizeA);
        t2 = hi(kJtLayoutStreamSizeB);
        a2 = hi(kJtLayoutStreamSize);
        a1 = addiu(a0, ps2all_matpvt::kListRecord);
        t7 = addiu(t8, 2);
        t4 = addiu(t4, lo(kJtLayoutClusterQw));
        t0 = addiu(t0, lo(kJtLayoutStreamSizeA));
        t2 = addiu(t2, lo(kJtLayoutStreamSizeB));
        a2 = addiu(a2, lo(kJtLayoutStreamSize));
        t6 = v0;
        s7 = 0xFFFF;
        t5 = v0;
        fp = 0x2;
        t3 = v0;
        t1 = addiu(a0, ps2all_matpvt::kStripRecord);
        for (;;) {
            // 0x0049cdb0: the batch sizes from the VU1 buffer: one cluster record per pass
            charge(ctx, 2);
            if (v1 != 0) {
                // 0x0049cdb8
                charge(ctx, 13);
                lw(a3, a1, cluster_rec::kBufferSize);
                lbu(s0, a1, cluster_rec::kPrimVerts);
                divu(a3, t8);
                mflo(a3);
                divu(a3, s0);
                mflo(a3);
                mult(a3, s0, a3);
                sw(a3, a1, cluster_rec::kClusterVerts);
                lw(a3, a1, cluster_rec::kClusterVerts);
                lbu(s0, a1, cluster_rec::kPrimVerts);
                s0 = slt(a3, s0);
                if (s0 != 0) {
                    // 0x0049d2b0 (written out on this path): a batch smaller than one primitive: return 0
                    charge(ctx, 2);
                    v0 = 0;
                    epilogue();
                    return;
                }
                // 0x0049cdec
                charge(ctx, 47);
                s1 = sll(a3, 2);
                s0 = addiu(a3, 3);
                s2 = addiu(s1, 3);
                s1 = sra(s0, 2);
                s2 = sra(s2, 2);
                s0 = sll(a3, 1);
                a3 = addu(s0, a3);
                s0 = sll(s2, 1);
                a3 = addiu(a3, 15);
                s0 = addiu(s0, 5);
                a3 = sra(a3, 4);
                s0 = addu(s0, s1);
                a3 = addu(s0, a3);
                div(s7, a3);
                mflo(a3);
                sw(a3, a1, cluster_rec::kBatch);
                lw(a3, a1, cluster_rec::kBufferSize);
                lbu(s0, a1, cluster_rec::kPrimVerts);
                divu(a3, t7);
                mflo(a3);
                divu(a3, s0);
                mflo(a3);
                mult1(a3, s0, a3);
                sw(a3, a1, cluster_rec::kClusterVerts2);
                lw(a3, a1, cluster_rec::kClusterVerts2);
                s1 = sll(a3, 2);
                s0 = sll(a3, 1);
                s1 = addiu(s1, 3);
                s0 = addu(s0, a3);
                s2 = sra(s1, 2);
                s0 = addiu(s0, 15);
                s1 = sra(s0, 4);
                s2 = addu(s2, s1);
                s0 = addiu(a3, 3);
                s1 = sra(s0, 2);
                s2 = sll(s2, 1);
                s0 = addiu(a3, 1);
                s2 = addiu(s2, 7);
                a3 = sll(s0, 1);
                s1 = addu(s2, s1);
                a3 = addu(a3, s0);
                a3 = sra(a3, 2);
                a3 = addu(s1, a3);
                div(s7, a3);
                mflo(a3);
                sw(a3, a1, cluster_rec::kBatch2);
            } else {
                // 0x0049cea8
                charge(ctx, 22);
                lw(a3, a1, cluster_rec::kBufferSize);
                divu(a3, t8);
                lbu(a3, a1, cluster_rec::kOverlap);
                mflo(s0);
                a3 = subu(s0, a3);
                sw(a3, a1, cluster_rec::kClusterVerts);
                lbu(s0, a1, cluster_rec::kPrimVerts);
                lw(a3, a1, cluster_rec::kClusterVerts);
                div(a3, s0);
                mflo(a3);
                mult(s0, s0, a3);
                lbu(a3, a1, cluster_rec::kOverlap);
                a3 = addu(a3, s0);
                sw(a3, a1, cluster_rec::kClusterVerts);
                lbu(s0, a1, cluster_rec::kPrimVerts);
                lbu(a3, a1, cluster_rec::kOverlap);
                lw(s1, a1, cluster_rec::kClusterVerts);
                a3 = addu(s0, a3);
                a3 = slt(s1, a3);
                if (a3 != 0) {
                    // 0x0049d2b8 (written out on this path): a batch smaller than one primitive plus the overlap:
                    // return 0
                    charge(ctx, 2);
                    v0 = 0;
                    epilogue();
                    return;
                }
                // 0x0049cf00
                charge(ctx, 18);
                sw(t6, a1, cluster_rec::kBatch);
                lw(a3, a1, cluster_rec::kBufferSize);
                divu(a3, t7);
                lbu(a3, a1, cluster_rec::kOverlap);
                mflo(s0);
                a3 = subu(s0, a3);
                sw(a3, a1, cluster_rec::kClusterVerts2);
                lbu(s0, a1, cluster_rec::kPrimVerts);
                lw(a3, a1, cluster_rec::kClusterVerts2);
                div(a3, s0);
                mflo(a3);
                mult(s0, s0, a3);
                lbu(a3, a1, cluster_rec::kOverlap);
                a3 = addu(a3, s0);
                sw(a3, a1, cluster_rec::kClusterVerts2);
                sw(t6, a1, cluster_rec::kBatch2);
            }
            // 0x0049cf48: the per-cluster quadwords and the stream records
            charge(ctx, 2);
            s5 = fp;
            if (v1 != 0) {
                // 0x0049cf50
                charge(ctx, 2);
                s5 = t5;
            }
            // 0x0049cf58
            charge(ctx, 2);
            a3 = 0;
            s0 = a0;
            for (;;) {
                // 0x0049cf60
                charge(ctx, 4);
                lw(s2, s0, ps2all_matpvt::kStreamFlags);
                s1 = s2 & 0x1;
                if (s1 != 0) {
                    // 0x0049cf70
                    charge(ctx, 3);
                    s1 = s2 & 0x2000;
                    if (s1 == 0) {
                        // 0x0049d030
                        charge(ctx, 2);
                        s5 = addiu(s5, 2);
                    } else {
                        // 0x0049cf7c
                        charge(ctx, 3);
                        at = sltiu(a3, 6);
                        if (at != 0) {
                            // 0x0049cf88
                            charge(ctx, 5);
                            s1 = sll(a3, 2);
                            s1 = addu(s1, t4);
                            lw(s1, s1, 0);
                            switch (s1.u()) {
                            case 0x49CFA0u:  // table[0]
                                // 0x0049cfa0
                                charge(ctx, 7);
                                lw(s1, a1, cluster_rec::kClusterVerts);
                                s2 = addiu(s1, 1);
                                s1 = sll(s2, 1);
                                s1 = addu(s1, s2);
                                s1 = sra(s1, 2);
                                s5 = addu(s5, s1);
                                break;
                            case 0x49CFC0u:  // table[1]
                                // 0x0049cfc0
                                charge(ctx, 3);
                                lw(s1, a1, cluster_rec::kClusterVerts);
                                s5 = addu(s5, s1);
                                break;
                            case 0x49CFD0u:  // table[2]
                                // 0x0049cfd0
                                charge(ctx, 6);
                                lw(s1, a1, cluster_rec::kClusterVerts);
                                s1 = sll(s1, 1);
                                s1 = addiu(s1, 3);
                                s1 = sra(s1, 2);
                                s5 = addu(s5, s1);
                                break;
                            case 0x49CFE8u:  // table[3]
                                // 0x0049cfe8
                                charge(ctx, 3);
                                lw(s1, a1, cluster_rec::kClusterVerts);
                                s5 = addu(s5, s1);
                                break;
                            case 0x49CFF8u:  // table[4]
                                // 0x0049cff8
                                charge(ctx, 5);
                                lw(s1, a1, cluster_rec::kClusterVerts);
                                s1 = addiu(s1, 3);
                                s1 = sra(s1, 2);
                                s5 = addu(s5, s1);
                                break;
                            case 0x49D010u:  // table[5]
                                // 0x0049d010
                                charge(ctx, 6);
                                lw(s2, a1, cluster_rec::kClusterVerts);
                                s1 = sll(s2, 1);
                                s1 = addu(s1, s2);
                                s1 = addiu(s1, 15);
                                s1 = sra(s1, 4);
                                s5 = addu(s5, s1);
                                break;
                            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                tail(ctx, s1.u());
                                return;
                            }
                        }
                        // 0x0049d028
                        charge(ctx, 2);
                        s5 = addiu(s5, 1);
                    }
                }
                // 0x0049d038
                charge(ctx, 4);
                a3 = addiu(a3, 1);
                s1 = sltiu(a3, 10);
                s0 = addiu(s0, 8);
                if (s1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0049d048: the per-stream records: ten streams (twelve with the pseudo-streams on the second pass)
            charge(ctx, 8);
            lbu(a3, a0, ps2all_matpvt::kStreamCount);
            s3 = 0;
            t9 = 0;
            s0 = 0;
            s2 = a0;
            s1 = a1;
            a3 = sll(a3, 1);
            s4 = addiu(a3, 1);
            for (;;) {
                // 0x0049d068
                charge(ctx, 4);
                lw(s6, s2, ps2all_matpvt::kStreamFlags);
                a3 = s6 & 0x1;
                if (a3 != 0) {
                    // 0x0049d2c0
                    charge(ctx, 5);
                    sb(t9, s1, cluster_rec::kStreams + ps2all_stream::kUnpack);
                    lw(a3, s2, ps2all_matpvt::kStreamFlags);
                    a3 = a3 & 0x2000;
                    if (a3 == 0) {
                        // 0x0049d378
                        charge(ctx, 7);
                        sw(zero, s1, cluster_rec::kStreams + ps2all_stream::kCount);
                        sw(zero, s1, cluster_rec::kStreams + ps2all_stream::kOffset);
                        a3 = addiu(t9, 1);
                        sh(zero, s1, cluster_rec::kStreams + ps2all_stream::kStride);
                        t9 = a3 & 0xFF;
                        sh(zero, s1, cluster_rec::kStreams + ps2all_stream::kLastBack);
                        backedge(ctx);
                    } else {
                        // 0x0049d2d4
                        charge(ctx, 11);
                        lw(a3, a1, cluster_rec::kClusterVerts);
                        s6 = addiu(s3, 1);
                        s4 = addu(s4, s6);
                        at = sltiu(s0, 6);
                        s6 = addiu(t9, 1);
                        t9 = s6 & 0xFF;
                        sw(a3, s1, cluster_rec::kStreams + ps2all_stream::kCount);
                        sw(s4, s1, cluster_rec::kStreams + ps2all_stream::kOffset);
                        sh(s5, s1, cluster_rec::kStreams + ps2all_stream::kStride);
                        sh(zero, s1, cluster_rec::kStreams + ps2all_stream::kLastBack);
                        if (at == 0) {
                            backedge(ctx);
                        } else {
                            // 0x0049d300
                            charge(ctx, 5);
                            s6 = sll(s0, 2);
                            s6 = addu(s6, t0);
                            lw(s6, s6, 0);
                            switch (s6.u()) {
                            case 0x49D318u:  // table[0]
                                // 0x0049d318
                                charge(ctx, 5);
                                s3 = addiu(a3, 1);
                                a3 = sll(s3, 1);
                                a3 = addu(a3, s3);
                                s3 = sra(a3, 2);
                                backedge(ctx);
                                break;
                            case 0x49D330u:  // table[1]
                                // 0x0049d330
                                charge(ctx, 2);
                                s3 = a3;
                                backedge(ctx);
                                break;
                            case 0x49D338u:  // table[2]
                                // 0x0049d338
                                charge(ctx, 4);
                                a3 = sll(a3, 1);
                                a3 = addiu(a3, 3);
                                s3 = sra(a3, 2);
                                backedge(ctx);
                                break;
                            case 0x49D348u:  // table[3]
                                // 0x0049d348
                                charge(ctx, 2);
                                s3 = a3;
                                backedge(ctx);
                                break;
                            case 0x49D350u:  // table[4]
                                // 0x0049d350
                                charge(ctx, 3);
                                a3 = addiu(a3, 3);
                                s3 = sra(a3, 2);
                                backedge(ctx);
                                break;
                            case 0x49D360u:  // table[5]
                                // 0x0049d360
                                charge(ctx, 5);
                                s3 = sll(a3, 1);
                                a3 = addu(s3, a3);
                                a3 = addiu(a3, 15);
                                s3 = sra(a3, 4);
                                backedge(ctx);
                                break;
                            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                tail(ctx, s6.u());
                                return;
                            }
                        }
                    }
                } else {
                    // 0x0049d078
                    charge(ctx, 3);
                    a3 = s6 & 0x10;
                    if (a3 != 0) {
                        // 0x0049d084
                        charge(ctx, 7);
                        sb(t9, s1, cluster_rec::kStreams + ps2all_stream::kUnpack);
                        a3 = addiu(t9, 1);
                        sw(zero, s1, cluster_rec::kStreams + ps2all_stream::kCount);
                        t9 = a3 & 0xFF;
                        sw(zero, s1, cluster_rec::kStreams + ps2all_stream::kOffset);
                        sh(zero, s1, cluster_rec::kStreams + ps2all_stream::kStride);
                        sh(zero, s1, cluster_rec::kStreams + ps2all_stream::kLastBack);
                    }
                }
                // 0x0049d0a0
                charge(ctx, 5);
                s0 = addiu(s0, 1);
                a3 = sltiu(s0, 10);
                s2 = addiu(s2, 8);
                s1 = addiu(s1, 24);
                if (a3 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0049d0b4
            charge(ctx, 2);
            s2 = fp;
            if (v1 != 0) {
                // 0x0049d0bc
                charge(ctx, 1);
                s2 = t3;
            }
            // 0x0049d0c0
            charge(ctx, 2);
            a3 = 0;
            s0 = a0;
            for (;;) {
                // 0x0049d0c8
                charge(ctx, 4);
                lw(s3, s0, ps2all_matpvt::kStreamFlags);
                s1 = s3 & 0x1;
                if (s1 != 0) {
                    // 0x0049d0d8
                    charge(ctx, 3);
                    s1 = s3 & 0x2000;
                    if (s1 == 0) {
                        // 0x0049d1d8
                        charge(ctx, 2);
                        s2 = addiu(s2, 2);
                    } else {
                        // 0x0049d0e4
                        charge(ctx, 3);
                        at = sltiu(a3, 12);
                        if (at != 0) {
                            // 0x0049d0f0
                            charge(ctx, 5);
                            s1 = sll(a3, 2);
                            s1 = addu(s1, t2);
                            lw(s1, s1, 0);
                            switch (s1.u()) {
                            case 0x49D108u:  // table[0]
                                // 0x0049d108
                                charge(ctx, 7);
                                lw(s1, a1, cluster_rec::kClusterVerts2);
                                s3 = addiu(s1, 1);
                                s1 = sll(s3, 1);
                                s1 = addu(s1, s3);
                                s1 = sra(s1, 2);
                                s2 = addu(s2, s1);
                                break;
                            case 0x49D128u:  // table[1]
                                // 0x0049d128
                                charge(ctx, 3);
                                lw(s1, a1, cluster_rec::kClusterVerts2);
                                s2 = addu(s2, s1);
                                break;
                            case 0x49D138u:  // table[2]
                                // 0x0049d138
                                charge(ctx, 6);
                                lw(s1, a1, cluster_rec::kClusterVerts2);
                                s1 = sll(s1, 1);
                                s1 = addiu(s1, 3);
                                s1 = sra(s1, 2);
                                s2 = addu(s2, s1);
                                break;
                            case 0x49D150u:  // table[3]
                                // 0x0049d150
                                charge(ctx, 3);
                                lw(s1, a1, cluster_rec::kClusterVerts2);
                                s2 = addu(s2, s1);
                                break;
                            case 0x49D160u:  // table[4]
                                // 0x0049d160
                                charge(ctx, 5);
                                lw(s1, a1, cluster_rec::kClusterVerts2);
                                s1 = addiu(s1, 3);
                                s1 = sra(s1, 2);
                                s2 = addu(s2, s1);
                                break;
                            case 0x49D178u:  // table[5]
                                // 0x0049d178
                                charge(ctx, 7);
                                lw(s3, a1, cluster_rec::kClusterVerts2);
                                s1 = sll(s3, 1);
                                s1 = addu(s1, s3);
                                s1 = addiu(s1, 15);
                                s1 = sra(s1, 4);
                                s2 = addu(s2, s1);
                                break;
                            case 0x49D198u:  // table[10]
                                // 0x0049d198
                                charge(ctx, 7);
                                lw(s1, a1, cluster_rec::kClusterVerts2);
                                s3 = addiu(s1, 1);
                                s1 = sll(s3, 1);
                                s1 = addu(s1, s3);
                                s1 = sra(s1, 2);
                                s2 = addu(s2, s1);
                                break;
                            case 0x49D1B8u:  // table[11]
                                // 0x0049d1b8
                                charge(ctx, 6);
                                lw(s3, a1, cluster_rec::kClusterVerts2);
                                s1 = sll(s3, 1);
                                s1 = addu(s1, s3);
                                s1 = addiu(s1, 15);
                                s1 = sra(s1, 4);
                                s2 = addu(s2, s1);
                                break;
                            case 0x49D1D0u:  // table[6, 7, 8, 9]
                                break;
                            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                tail(ctx, s1.u());
                                return;
                            }
                        }
                        // 0x0049d1d0
                        charge(ctx, 2);
                        s2 = addiu(s2, 1);
                    }
                }
                // 0x0049d1e0
                charge(ctx, 4);
                a3 = addiu(a3, 1);
                s1 = sltiu(a3, 12);
                s0 = addiu(s0, 8);
                if (s1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0049d1f0
            charge(ctx, 8);
            lbu(a3, a0, ps2all_matpvt::kStreamCount);
            s0 = 0;
            t9 = 0;
            s3 = 0;
            s5 = a0;
            s4 = a1;
            a3 = sll(a3, 1);
            s1 = addiu(a3, 1);
            for (;;) {
                // 0x0049d210
                charge(ctx, 4);
                lw(s6, s5, ps2all_matpvt::kStreamFlags);
                a3 = s6 & 0x1;
                if (a3 != 0) {
                    // 0x0049d398
                    charge(ctx, 5);
                    sb(t9, s4, cluster_rec::kStreams + ps2all_stream::kUnpack);
                    lw(a3, s5, ps2all_matpvt::kStreamFlags);
                    a3 = a3 & 0x2000;
                    if (a3 == 0) {
                        // 0x0049d480
                        charge(ctx, 7);
                        sw(zero, s4, cluster_rec::kStreams + ps2all_stream::kCount2);
                        sw(zero, s4, cluster_rec::kStreams + ps2all_stream::kOffset2);
                        a3 = addiu(t9, 1);
                        sh(zero, s4, cluster_rec::kStreams + ps2all_stream::kStride2);
                        t9 = a3 & 0xFF;
                        sh(zero, s4, cluster_rec::kStreams + ps2all_stream::kLastBack);
                        backedge(ctx);
                    } else {
                        // 0x0049d3ac
                        charge(ctx, 11);
                        lw(a3, a1, cluster_rec::kClusterVerts2);
                        s6 = addiu(s0, 1);
                        s1 = addu(s1, s6);
                        at = sltiu(s3, 12);
                        s6 = addiu(t9, 1);
                        t9 = s6 & 0xFF;
                        sw(a3, s4, cluster_rec::kStreams + ps2all_stream::kCount2);
                        sw(s1, s4, cluster_rec::kStreams + ps2all_stream::kOffset2);
                        sh(s2, s4, cluster_rec::kStreams + ps2all_stream::kStride2);
                        sh(zero, s4, cluster_rec::kStreams + ps2all_stream::kLastBack);
                        if (at == 0) {
                            backedge(ctx);
                        } else {
                            // 0x0049d3d8
                            charge(ctx, 5);
                            s6 = sll(s3, 2);
                            s6 = addu(s6, a2);
                            lw(s6, s6, 0);
                            switch (s6.u()) {
                            case 0x49D248u:  // table[6, 7, 8, 9]
                                backedge(ctx);
                                break;
                            case 0x49D3F0u:  // table[0]
                                // 0x0049d3f0
                                charge(ctx, 5);
                                s0 = addiu(a3, 1);
                                a3 = sll(s0, 1);
                                a3 = addu(a3, s0);
                                s0 = sra(a3, 2);
                                backedge(ctx);
                                break;
                            case 0x49D408u:  // table[1]
                                // 0x0049d408
                                charge(ctx, 2);
                                s0 = a3;
                                backedge(ctx);
                                break;
                            case 0x49D410u:  // table[2]
                                // 0x0049d410
                                charge(ctx, 4);
                                a3 = sll(a3, 1);
                                a3 = addiu(a3, 3);
                                s0 = sra(a3, 2);
                                backedge(ctx);
                                break;
                            case 0x49D420u:  // table[3]
                                // 0x0049d420
                                charge(ctx, 2);
                                s0 = a3;
                                backedge(ctx);
                                break;
                            case 0x49D428u:  // table[4]
                                // 0x0049d428
                                charge(ctx, 3);
                                a3 = addiu(a3, 3);
                                s0 = sra(a3, 2);
                                backedge(ctx);
                                break;
                            case 0x49D438u:  // table[5]
                                // 0x0049d438
                                charge(ctx, 5);
                                s0 = sll(a3, 1);
                                a3 = addu(s0, a3);
                                a3 = addiu(a3, 15);
                                s0 = sra(a3, 4);
                                backedge(ctx);
                                break;
                            case 0x49D450u:  // table[10]
                                // 0x0049d450
                                charge(ctx, 5);
                                s0 = addiu(a3, 1);
                                a3 = sll(s0, 1);
                                a3 = addu(a3, s0);
                                s0 = sra(a3, 2);
                                backedge(ctx);
                                break;
                            case 0x49D468u:  // table[11]
                                // 0x0049d468
                                charge(ctx, 5);
                                s0 = sll(a3, 1);
                                a3 = addu(s0, a3);
                                a3 = addiu(a3, 15);
                                s0 = sra(a3, 4);
                                backedge(ctx);
                                break;
                            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                tail(ctx, s6.u());
                                return;
                            }
                        }
                    }
                } else {
                    // 0x0049d220
                    charge(ctx, 3);
                    a3 = s6 & 0x10;
                    if (a3 != 0) {
                        // 0x0049d22c
                        charge(ctx, 7);
                        sb(t9, s4, cluster_rec::kStreams + ps2all_stream::kUnpack);
                        a3 = addiu(t9, 1);
                        sw(zero, s4, cluster_rec::kStreams + ps2all_stream::kCount2);
                        t9 = a3 & 0xFF;
                        sw(zero, s4, cluster_rec::kStreams + ps2all_stream::kOffset2);
                        sh(zero, s4, cluster_rec::kStreams + ps2all_stream::kStride2);
                        sh(zero, s4, cluster_rec::kStreams + ps2all_stream::kLastBack);
                    }
                }
                // 0x0049d248
                charge(ctx, 5);
                s3 = addiu(s3, 1);
                a3 = sltiu(s3, 12);
                s5 = addiu(s5, 8);
                s4 = addiu(s4, 24);
                if (a3 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0049d25c: the next pass
            charge(ctx, 4);
            v0 = addiu(v0, 1);
            at = sltiu(v0, 3);
            a1 = t1;
            if (at == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0049d26c: return 1
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x0049d4a0 (the shared epilogue)
    epilogue();
}

// 0x0049D4D0 ps2AllInstanceSizes -- 1944 bytes; frame 0xE0: fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// ps2AllInstanceSizes [PS2All instance sizes] (pipe data $a0, vertex count $a1, stream records out $a2, out $a3 / $t0 / $t1):
// the cluster layout of one mesh from the material pipeline's record (matPvt +184 for strips (header flag 1) and
// polylines (8), else +496): vertices per cluster (+8, or +16 for a morph target), the batch (+12 / +20 -> sp + 208),
// the cluster count ($t5 = (n + overlap * ... ) / step, the overlap = record +1) and the last cluster's vertices ($t3);
// the 24-byte stream records copied to $a2 (10 + morph streams). Without double buffering (matPvt +180 = 0): per
// instanced stream (jump table 0x7BCA30 by type) its offset (+20 / +44 / +68 / +92 / +116 / +140, u16) and its total
// size, streams outside the cluster (0x2000 clear) sized whole (+0 / +4 = $a1, +20 = 0); a morph's second set (+260 /
// +284); the per-stream data addresses (+8 / +12). With it: the offsets by type sizes in sequence. Out: *$a3 = vertices
// per cluster, *$t0 = the batch, *$t1 = the cluster count. Returns the resEntry size in bytes (qwords * 16 + 559).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: the hand version terminated the host on a random world).
void ps2AllInstanceSizes(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::divu, hg::dsll32, hg::dsra32,
          hg::enter, hg::lbu, hg::lh, hg::lq, hg::lw, hg::lwc1, hg::mflo, hg::mult, hg::mult1, hg::sh, hg::si,
          hg::sll, hg::sltiu, hg::sltu, hg::sq, hg::sra, hg::srl, hg::subu, hg::sw, hg::swc1, hg::tail;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x0049d4d0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0xE0);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, ps2all_pd::kMeshHeader);
    lw(v1, v0, mesh_hdr::kFlags);
    v0 = v1 & 0x1;  // a strip?
    lw(s3, a0, ps2all_pd::kMatPvt);  // s3 = the material pipeline's private data
    // v0 = the cluster record: the strip / polyline record (+184) or the list record (+496)
    if (v0 == 0) {
        // 0x0049d50c
        charge(ctx, 3);
        v0 = v1 & 0x8;  // a polyline?
        if (v0 != 0) {
            // 0x0049d5d8 (written out on this path)
            charge(ctx, 2);
            v0 = addiu(s3, ps2all_matpvt::kStripRecord);
            backedge(ctx);
        } else {
            // 0x0049d518
            charge(ctx, 1);
            v0 = addiu(s3, ps2all_matpvt::kListRecord);
        }
    } else {
        // 0x0049d5d8
        charge(ctx, 2);
        v0 = addiu(s3, ps2all_matpvt::kStripRecord);
        backedge(ctx);
    }
    // 0x0049d51c: s2 = vertices per cluster, sp+0xD0 = the batch (a morph target's when pd +36 is not 0)
    charge(ctx, 5);
    lw(v1, v0, cluster_rec::kBatch);
    lw(t4, a0, ps2all_pd::kMorphStreams);
    lw(s2, v0, cluster_rec::kClusterVerts);
    sw(v1, sp, 0xD0);
    if (t4 != 0) {
        // 0x0049d530
        charge(ctx, 3);
        lw(v1, v0, cluster_rec::kBatch2);
        lw(s2, v0, cluster_rec::kClusterVerts2);
        sw(v1, sp, 0xD0);
    }
    // 0x0049d53c: the clusters t5 = (n + overlap * ... ) / step and the last cluster's vertices t3; then the stream
    // records copied to $a2 (10 + the morph streams)
    charge(ctx, 16);
    lbu(t3, v0, cluster_rec::kOverlap);
    v1 = si(-2);
    mult(t2, t3, v1);
    t2 = addiu(t2, -1);
    v1 = subu(s2, t3);
    t2 = addu(t2, s2);
    t2 = addu(t2, a1);
    divu(t2, v1);
    mflo(t5);
    v1 = addiu(t5, -1);
    mult(t2, t3, v1);
    v1 = addiu(t4, 10);
    t3 = addu(a1, t2);
    at = sltu(0, v1);
    t4 = 0;
    if (at == 0) {
        // 0x0049d5e0
        charge(ctx, 1);
        lbu(v0, s3, ps2all_matpvt::kDoubleBuffer);
    } else {
        // 0x0049d57c
        charge(ctx, 1);
        t2 = a2;
        for (;;) {
            // 0x0049d580
            charge(ctx, 20);
            lwc1(f3, v0, cluster_rec::kStreams);
            v1 = addiu(v0, 24);
            lwc1(f2, v0, cluster_rec::kStreams + 4);
            t4 = addiu(t4, 1);
            lwc1(f1, v0, cluster_rec::kStreams + 8);
            lwc1(f0, v0, cluster_rec::kStreams + 12);
            swc1(f3, t2, 0);
            swc1(f2, t2, 4);
            swc1(f1, t2, 8);
            swc1(f0, t2, 12);
            lwc1(f1, v0, cluster_rec::kStreams + 16);
            lwc1(f0, v0, cluster_rec::kStreams + 20);
            swc1(f1, t2, 16);
            v0 = v1;
            swc1(f0, t2, 20);
            lw(v1, a0, ps2all_pd::kMorphStreams);
            v1 = addiu(v1, 10);
            v1 = sltu(t4, v1);
            t2 = addiu(t2, 24);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0049d5d0
        charge(ctx, 2);
        lbu(v0, s3, ps2all_matpvt::kDoubleBuffer);
    }
    // 0x0049d5e4
    charge(ctx, 2);
    if (v0 != 0) {
        // 0x0049d868: double buffered: each stream's offset in the cluster in sequence by the type sizes (records 0..5
        // at +16 / +40
        // / +64 / +88 / +112 / +136, their +20 the running offset), then a morph target's second set (+260 / +284)
        charge(ctx, 7);
        t2 = 1;
        t4 = 0;
        mult(v1, s2, t5);
        lh(v0, a2, srec(0, ps2all_stream::kStride));
        s1 = 0;
        a1 = subu(v1, t3);
        if (v0 == 0) {
            // 0x0049d89c
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0049d884
            charge(ctx, 6);
            v1 = addiu(t3, 1);
            t2 = addiu(t2, 1);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v0 = srl(v0, 2);
        }
        // 0x0049d8a0
        charge(ctx, 5);
        v1 = addu(s1, v0);
        sh(zero, a2, srec(0, ps2all_stream::kLastBack));
        lh(v0, a2, srec(0, ps2all_stream::kStride));
        if (v0 == 0) {
            // 0x0049d8c4
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0049d8b4
            charge(ctx, 4);
            v0 = sll(a1, 1);
            v0 = addu(v0, a1);
            v0 = sra(v0, 2);
        }
        // 0x0049d8c8
        charge(ctx, 4);
        t4 = addu(t4, v0);
        lh(v0, a2, srec(1, ps2all_stream::kStride));
        if (v0 == 0) {
            // 0x0049d8e4
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0049d8d8
            charge(ctx, 3);
            t2 = addiu(t2, 1);
            v0 = t3;
        }
        // 0x0049d8e8
        charge(ctx, 5);
        v1 = addu(v1, v0);
        sh(t4, a2, srec(1, ps2all_stream::kLastBack));
        lh(v0, a2, srec(1, ps2all_stream::kStride));
        if (v0 == 0) {
            // 0x0049d904
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0049d8fc
            charge(ctx, 2);
            v0 = a1;
        }
        // 0x0049d908
        charge(ctx, 4);
        t4 = addu(t4, v0);
        lh(v0, a2, srec(2, ps2all_stream::kStride));
        if (v0 == 0) {
            // 0x0049d92c
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0049d918
            charge(ctx, 5);
            v0 = sll(t3, 1);
            t2 = addiu(t2, 1);
            v0 = addiu(v0, 3);
            v0 = srl(v0, 2);
        }
        // 0x0049d930
        charge(ctx, 5);
        v1 = addu(v1, v0);
        sh(t4, a2, srec(2, ps2all_stream::kLastBack));
        lh(v0, a2, srec(2, ps2all_stream::kStride));
        if (v0 == 0) {
            // 0x0049d94c
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0049d944
            charge(ctx, 2);
            v0 = sra(a1, 1);
        }
        // 0x0049d950
        charge(ctx, 4);
        t4 = addu(t4, v0);
        lh(v0, a2, srec(3, ps2all_stream::kStride));
        if (v0 == 0) {
            // 0x0049d96c
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0049d960
            charge(ctx, 3);
            t2 = addiu(t2, 1);
            v0 = t3;
        }
        // 0x0049d970
        charge(ctx, 5);
        v1 = addu(v1, v0);
        sh(t4, a2, srec(3, ps2all_stream::kLastBack));
        lh(v0, a2, srec(3, ps2all_stream::kStride));
        if (v0 == 0) {
            // 0x0049d98c
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0049d984
            charge(ctx, 2);
            v0 = a1;
        }
        // 0x0049d990
        charge(ctx, 4);
        t4 = addu(t4, v0);
        lh(v0, a2, srec(4, ps2all_stream::kStride));
        if (v0 == 0) {
            // 0x0049d9b0
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0049d9a0
            charge(ctx, 4);
            v0 = addiu(t3, 3);
            t2 = addiu(t2, 1);
            v0 = srl(v0, 2);
        }
        // 0x0049d9b4
        charge(ctx, 5);
        v1 = addu(v1, v0);
        sh(t4, a2, srec(4, ps2all_stream::kLastBack));
        lh(v0, a2, srec(4, ps2all_stream::kStride));
        if (v0 == 0) {
            // 0x0049d9d0
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0049d9c8
            charge(ctx, 2);
            v0 = sra(a1, 2);
        }
        // 0x0049d9d4
        charge(ctx, 4);
        v0 = addu(t4, v0);
        lh(t4, a2, srec(5, ps2all_stream::kStride));
        if (t4 == 0) {
            // 0x0049da20
            charge(ctx, 1);
            t4 = 0;
        } else {
            // 0x0049d9e4
            charge(ctx, 15);
            t4 = sll(s2, 1);
            t2 = addiu(t2, 1);
            t6 = addu(t4, s2);
            t6 = addiu(t6, 15);
            t4 = addiu(t5, -1);
            t6 = srl(t6, 4);
            mult(t7, t4, t6);
            mult1(t4, s2, t4);
            t6 = subu(t3, t4);
            t4 = sll(t6, 1);
            t4 = addu(t4, t6);
            t4 = addiu(t4, 15);
            t4 = srl(t4, 4);
            t4 = addu(t7, t4);
        }
        // 0x0049da24: the morph streams
        charge(ctx, 5);
        s1 = addu(v1, t4);
        sh(v0, a2, srec(5, ps2all_stream::kLastBack));
        lw(v1, a0, ps2all_pd::kMorphStreams);
        if (v1 != 0) {
            // 0x0049da38
            charge(ctx, 3);
            lh(v1, a2, srec(5, ps2all_stream::kStride));
            if (v1 == 0) {
                // 0x0049da78
                charge(ctx, 1);
                v1 = 0;
            } else {
                // 0x0049da44
                charge(ctx, 13);
                v1 = addiu(t5, -1);
                mult(a0, s2, v1);
                t4 = subu(t3, a0);
                v1 = sll(s2, 1);
                a0 = sll(t4, 1);
                v1 = addu(v1, s2);
                a0 = addu(a0, t4);
                v1 = addiu(v1, 15);
                a0 = addiu(a0, 15);
                v1 = srl(v1, 4);
                a0 = srl(a0, 4);
                v1 = subu(v1, a0);
            }
            // 0x0049da7c
            charge(ctx, 27);
            t4 = addu(v0, v1);
            t2 = addiu(t2, 2);
            v1 = addiu(t3, 1);
            sh(t4, a2, srec(10, ps2all_stream::kLastBack));
            v0 = sll(v1, 1);
            a0 = addu(v0, v1);
            v0 = sll(a1, 1);
            v1 = addu(v0, a1);
            v0 = srl(a0, 2);
            v1 = sra(v1, 2);
            a0 = sll(s2, 1);
            t4 = addu(t4, v1);
            a0 = addu(a0, s2);
            v1 = addiu(t5, -1);
            a0 = addiu(a0, 15);
            v0 = addu(s1, v0);
            a0 = srl(a0, 4);
            mult(a1, v1, a0);
            mult1(v1, s2, v1);
            sh(t4, a2, srec(11, ps2all_stream::kLastBack));
            a0 = subu(t3, v1);
            v1 = sll(a0, 1);
            v1 = addu(v1, a0);
            v1 = addiu(v1, 15);
            v1 = srl(v1, 4);
            v1 = addu(a1, v1);
            s1 = addu(v0, v1);
        }
        // 0x0049dae8: the resEntry quadwords: per cluster plus the DMA tags of the batches
        charge(ctx, 11);
        mult(a0, t2, t5);
        lw(v0, sp, 0xD0);
        a0 = addu(s1, a0);
        v0 = addu(t5, v0);
        v1 = addiu(v0, -1);
        lw(v0, sp, 0xD0);
        divu(v1, v0);
        mflo(v0);
        v1 = addu(a0, v0);
        v0 = sll(v0, 3);
        s1 = addu(v1, v0);
        // 0x0049db14
        charge(ctx, 1);
        lw(v0, sp, 0xD0);
    } else {
        // 0x0049d5ec: not double buffered: per instanced stream (jump table 0x7BCA30 by type) its offset and total
        // size;
        // the streams outside the cluster sized whole
        charge(ctx, 45);
        t4 = addiu(t5, -1);
        s0 = 0;
        mult(v0, s2, t4);
        lbu(v1, s3, ps2all_matpvt::kStreamCount);
        v0 = subu(t3, v0);
        v1 = addiu(v1, 1);
        v1 = sll(v1, 1);
        mult1(t6, t5, v1);
        t2 = addiu(s2, 1);
        v1 = sll(t2, 1);
        s4 = addiu(v0, 1);
        v1 = addu(v1, t2);
        s7 = sra(s4, 1);
        t3 = srl(v1, 2);
        s1 = 0;
        v1 = sll(s4, 1);
        t7 = 0;
        v1 = addu(v1, s4);
        t9 = s3;
        v1 = sra(v1, 2);
        s4 = sll(v0, 1);
        sq(v1, sp, 0xC0);
        s4 = addu(s4, v0);
        v1 = addiu(s2, 3);
        s4 = addiu(s4, 15);
        s6 = srl(v1, 2);
        s4 = sra(s4, 4);
        v1 = addiu(v0, 3);
        t8 = a2;
        s5 = sra(v1, 2);
        t2 = srl(t2, 1);
        v1 = sll(s2, 1);
        sq(s4, sp, 0xB0);
        v1 = addu(v1, s2);
        v1 = addiu(v1, 15);
        v1 = srl(v1, 4);
        s4 = subu(s6, s5);
        fp = subu(t2, s7);
        sq(s4, sp, 0xA0);
        v0 = subu(s2, v0);
        lq(s4, sp, 0xB0);
        s4 = subu(v1, s4);
        sq(s4, sp, 0x90);
        lq(s4, sp, 0xC0);
        s7 = subu(t3, s4);
        for (;;) {
            // 0x0049d6a0
            charge(ctx, 4);
            lw(s5, t9, ps2all_matpvt::kStreamFlags);
            s4 = s5 & 0x1;
            if (s4 != 0) {
                // 0x0049d6b0
                charge(ctx, 3);
                s4 = s5 & 0x2000;
                if (s4 == 0) {
                    // 0x0049db30
                    charge(ctx, 8);
                    lw(s4, t9, ps2all_matpvt::kStreamSize);
                    mult(s4, a1, s4);
                    sw(a1, t8, ps2all_stream::kCount);
                    sw(a1, t8, ps2all_stream::kCount2);
                    sh(zero, t8, ps2all_stream::kLastBack);
                    s4 = addiu(s4, 3);
                    s4 = srl(s4, 2);
                    s1 = addu(s1, s4);
                } else {
                    // 0x0049d6bc
                    charge(ctx, 3);
                    at = sltiu(t7, 6);
                    if (at != 0) {
                        // 0x0049d6c8
                        charge(ctx, 7);
                        s4 = hi(kJtInstanceSizes);
                        s5 = sll(t7, 2);
                        s4 = addiu(s4, lo(kJtInstanceSizes));
                        s4 = addu(s5, s4);
                        lw(s4, s4, 0);
                        switch (s4.u()) {
                        case 0x49D6E8u:  // table[0]
                            // 0x0049d6e8
                            charge(ctx, 4);
                            lw(t6, a0, ps2all_pd::kMorphStreams);
                            lw(s4, a2, srec(0, ps2all_stream::kOffset));
                            lh(s5, a2, srec(0, ps2all_stream::kStride));
                            if (t6 != 0) {
                                // 0x0049d6f8
                                charge(ctx, 2);
                                lh(s5, a2, srec(0, ps2all_stream::kStride2));
                                lw(s4, a2, srec(0, ps2all_stream::kOffset2));
                            }
                            // 0x0049d700
                            charge(ctx, 9);
                            t6 = dsll32(s5, 16);
                            t6 = dsra32(t6, 16);
                            mult(t6, t6, t4);
                            sh(s0, a2, srec(0, ps2all_stream::kLastBack));
                            s0 = addu(s0, s7);
                            t6 = addu(s4, t6);
                            t6 = addu(t3, t6);
                            t6 = addiu(t6, 1);
                            break;
                        case 0x49D728u:  // table[1]
                            // 0x0049d728
                            charge(ctx, 4);
                            lw(t6, a0, ps2all_pd::kMorphStreams);
                            lw(s4, a2, srec(1, ps2all_stream::kOffset));
                            lh(s5, a2, srec(1, ps2all_stream::kStride));
                            if (t6 != 0) {
                                // 0x0049d738
                                charge(ctx, 2);
                                lh(s5, a2, srec(1, ps2all_stream::kStride2));
                                lw(s4, a2, srec(1, ps2all_stream::kOffset2));
                            }
                            // 0x0049d740
                            charge(ctx, 9);
                            t6 = dsll32(s5, 16);
                            t6 = dsra32(t6, 16);
                            mult(t6, t6, t4);
                            sh(s0, a2, srec(1, ps2all_stream::kLastBack));
                            s0 = addu(s0, v0);
                            t6 = addu(s4, t6);
                            t6 = addu(s2, t6);
                            t6 = addiu(t6, 1);
                            break;
                        case 0x49D768u:  // table[2]
                            // 0x0049d768
                            charge(ctx, 4);
                            lw(t6, a0, ps2all_pd::kMorphStreams);
                            lw(s4, a2, srec(2, ps2all_stream::kOffset));
                            lh(s5, a2, srec(2, ps2all_stream::kStride));
                            if (t6 != 0) {
                                // 0x0049d778
                                charge(ctx, 2);
                                lh(s5, a2, srec(2, ps2all_stream::kStride2));
                                lw(s4, a2, srec(2, ps2all_stream::kOffset2));
                            }
                            // 0x0049d780
                            charge(ctx, 9);
                            t6 = dsll32(s5, 16);
                            t6 = dsra32(t6, 16);
                            mult(t6, t6, t4);
                            sh(s0, a2, srec(2, ps2all_stream::kLastBack));
                            s0 = addu(s0, fp);
                            t6 = addu(s4, t6);
                            t6 = addu(t2, t6);
                            t6 = addiu(t6, 1);
                            break;
                        case 0x49D7A8u:  // table[3]
                            // 0x0049d7a8
                            charge(ctx, 4);
                            lw(t6, a0, ps2all_pd::kMorphStreams);
                            lw(s4, a2, srec(3, ps2all_stream::kOffset));
                            lh(s5, a2, srec(3, ps2all_stream::kStride));
                            if (t6 != 0) {
                                // 0x0049d7b8
                                charge(ctx, 2);
                                lh(s5, a2, srec(3, ps2all_stream::kStride2));
                                lw(s4, a2, srec(3, ps2all_stream::kOffset2));
                            }
                            // 0x0049d7c0
                            charge(ctx, 9);
                            t6 = dsll32(s5, 16);
                            t6 = dsra32(t6, 16);
                            mult(t6, t6, t4);
                            sh(s0, a2, srec(3, ps2all_stream::kLastBack));
                            s0 = addu(s0, v0);
                            t6 = addu(s4, t6);
                            t6 = addu(s2, t6);
                            t6 = addiu(t6, 1);
                            break;
                        case 0x49D7E8u:  // table[4]
                            // 0x0049d7e8
                            charge(ctx, 4);
                            lw(s4, a0, ps2all_pd::kMorphStreams);
                            lw(t6, a2, srec(4, ps2all_stream::kOffset));
                            lh(s5, a2, srec(4, ps2all_stream::kStride));
                            if (s4 != 0) {
                                // 0x0049d7f8
                                charge(ctx, 2);
                                lh(s5, a2, srec(4, ps2all_stream::kStride2));
                                lw(t6, a2, srec(4, ps2all_stream::kOffset2));
                            }
                            // 0x0049d800
                            charge(ctx, 10);
                            s4 = dsll32(s5, 16);
                            s4 = dsra32(s4, 16);
                            mult(s5, s4, t4);
                            sh(s0, a2, srec(4, ps2all_stream::kLastBack));
                            lq(s4, sp, 0xA0);
                            t6 = addu(t6, s5);
                            t6 = addu(s6, t6);
                            t6 = addiu(t6, 1);
                            s0 = addu(s0, s4);
                            break;
                        case 0x49D828u:  // table[5]
                            // 0x0049d828
                            charge(ctx, 4);
                            lw(s4, a0, ps2all_pd::kMorphStreams);
                            lw(t6, a2, srec(5, ps2all_stream::kOffset));
                            lh(s5, a2, srec(5, ps2all_stream::kStride));
                            if (s4 != 0) {
                                // 0x0049d838
                                charge(ctx, 2);
                                lh(s5, a2, srec(5, ps2all_stream::kStride2));
                                lw(t6, a2, srec(5, ps2all_stream::kOffset2));
                            }
                            // 0x0049d840
                            charge(ctx, 10);
                            s4 = dsll32(s5, 16);
                            s4 = dsra32(s4, 16);
                            mult(s5, s4, t4);
                            sh(s0, a2, srec(5, ps2all_stream::kLastBack));
                            lq(s4, sp, 0x90);
                            t6 = addu(t6, s5);
                            t6 = addu(v1, t6);
                            t6 = addiu(t6, 1);
                            s0 = addu(s0, s4);
                            break;
                        default:  // not one of the table's targets: the dispatch table, as the recompiled body
                            tail(ctx, s4.u());
                            return;
                        }
                    }
                }
            }
            // 0x0049db50
            charge(ctx, 5);
            t7 = addiu(t7, 1);
            s4 = sltiu(t7, 10);
            t9 = addiu(t9, 8);
            t8 = addiu(t8, 24);
            if (s4 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0049db64
        charge(ctx, 3);
        lw(v0, a0, ps2all_pd::kMorphStreams);
        if (v0 != 0) {
            // 0x0049dbfc
            charge(ctx, 16);
            lq(v0, sp, 0xC0);
            sh(s0, a2, srec(10, ps2all_stream::kLastBack));
            lh(t2, a2, srec(11, ps2all_stream::kStride2));
            v0 = subu(t3, v0);
            t4 = addu(s0, v0);
            lw(t3, a2, srec(11, ps2all_stream::kOffset2));
            v0 = addiu(t5, -1);
            mult(t2, t2, v0);
            lq(v0, sp, 0xB0);
            sh(t4, a2, srec(11, ps2all_stream::kLastBack));
            v0 = subu(v1, v0);
            s0 = addu(t4, v0);
            v0 = addu(t3, t2);
            v0 = addu(v1, v0);
            t6 = addiu(v0, 1);
            backedge(ctx);
        }
        // 0x0049db70
        charge(ctx, 7);
        lw(t3, a0, ps2all_pd::kMorphStreams);
        t6 = subu(t6, s0);
        t2 = 0;
        v0 = addiu(t3, 10);
        at = sltu(0, v0);
        s1 = addu(s1, t6);
        if (at == 0) {
            backedge(ctx);
            // 0x0049db14 (written out on this path): no streams
            charge(ctx, 1);
            lw(v0, sp, 0xD0);
        } else {
            for (;;) {
                // 0x0049db8c
                charge(ctx, 4);
                lw(v1, s3, ps2all_matpvt::kStreamFlags);
                v0 = v1 & 0x1;
                if (v0 != 0) {
                    // 0x0049db9c
                    charge(ctx, 3);
                    v0 = v1 & 0x2000;
                    if (v0 == 0) {
                        // 0x0049dba8
                        charge(ctx, 2);
                        if (t3 == 0) {
                            // 0x0049dbb8
                            charge(ctx, 2);
                            sw(t6, a2, ps2all_stream::kOffset);
                        } else {
                            // 0x0049dbb0
                            charge(ctx, 2);
                            sw(t6, a2, ps2all_stream::kOffset2);
                        }
                        // 0x0049dbc0
                        charge(ctx, 6);
                        lw(v0, s3, ps2all_matpvt::kStreamSize);
                        mult(v0, a1, v0);
                        v0 = addiu(v0, 3);
                        v0 = srl(v0, 2);
                        t6 = addu(t6, v0);
                    }
                }
                // 0x0049dbd8
                charge(ctx, 7);
                lw(t3, a0, ps2all_pd::kMorphStreams);
                t2 = addiu(t2, 1);
                s3 = addiu(s3, 8);
                v0 = addiu(t3, 10);
                v0 = sltu(t2, v0);
                a2 = addiu(a2, 24);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0049dbf4
            charge(ctx, 2);
            lw(v0, sp, 0xD0);
            backedge(ctx);
        }
    }
    // 0x0049db18: return the resEntry size in bytes (qwords * 16 + 559); out: *$a3 vertices per cluster, *$t0 the
    // batch, *$t1
    // the clusters
    charge(ctx, 6);
    v1 = sll(s1, 4);
    sw(s2, a3, 0);
    sw(v0, t0, 0);
    v0 = addiu(v1, 559);
    sw(t5, t1, 0);
    // 0x0049dc3c
    charge(ctx, 11);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xE0);
}

// 0x0049DC70 ps2AllInstanceDmaChain -- 2172 bytes; frame 0x210: fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// ps2AllInstanceDmaChain [PS2All instance: the DMA chain and UNPACK headers of a resEntry] (pipe data $a0): over the resEntry's
// clusters (resEntry +52 count, +56 clusters per DMA block, +36 vertices; header +24 per-cluster vertices (the last
// cluster gets the rest), +28 cluster count, +8 data, per stream +152 / +156 offsets and +166 the unpack address): every
// N-th cluster opens a DMA `cnt` / `ref` block (0x10000000 | qwords - 1; or, without double buffering, a 0x11000000
// FLUSH-headed tag); each stream outside the cluster (flag bit 0, 0x2000 clear) gets a `ref` tag (0x30000000 | qwords)
// to its data with STCYCL 1,1 + the UNPACK (the stream's format bits, the vertex count << 16, the element size by
// the format: 6C 4, 68 3, 6D / 64 2, 65 / 6E / 60 1, else 4, the offset +166) and a `cnt` 0x10000000 qword; each
// stream in the cluster (0x2000 set) an UNPACK header by its type (jump table 0x7BCA50: the eight UNPACK templates of
// the frame, sp + 176..352) followed by its data area; the cluster's ITOP / MSCAL(NT) quadword (0x04000000 | vertices,
// 0x15000000 for the first cluster, 0x17000000 after); finally the block's closing FLUSH (0x11000000 pair) and the
// `cnt` tag of the last block (0x60000000 = `ret` | qwords - 1), the ref's high word zeroed when not double buffered.
// Returns 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: frame/spills (own frame)).
void ps2AllInstanceDmaChain(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::div, hg::divu, hg::dsll, hg::dsll32,
          hg::dsra32, hg::dsrl32, hg::enter, hg::i64, hg::lbu, hg::ld, hg::lq, hg::lui, hg::lw, hg::lwu, hg::mfhi,
          hg::mflo, hg::mult, hg::mult1, hg::pcpyld, hg::sd, hg::si, hg::sll, hg::slt, hg::sltiu, hg::sq, hg::sra,
          hg::subu, hg::sw, hg::tail;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30};
    // 0x0049dc70
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x210);
    a2 = 0;
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, ps2all_pd::kMatPvt);  // the material pipeline's private data, kept at sp+0x200
    lw(a1, a0, ps2all_pd::kResEntrySlot);  // the resEntry slot
    lw(v1, a0, ps2all_pd::kMeshHeader);  // the mesh header
    sw(v0, sp, 0x200);
    v0 = 0;
    lw(a3, a1, 0);  // a3 = the resEntry
    pcpyld(t9, a2, v0);
    lw(v0, sp, 0x200);
    lw(a2, v1, mesh_hdr::kFlags);  // a2 = the mesh header flags
    lw(s4, a3, res_entry::kHeader + ps2all_hdr::kData);  // s4 = the data: the tags are written from here
    s5 = addiu(a3, res_entry::kHeader);  // s5 = the instance header
    lbu(v0, v0, ps2all_matpvt::kInstStreams);  // the instanced streams (sp+0x1B0)
    lw(v1, a3, res_entry::kHeader + ps2all_hdr::kClusterCount);  // v1 = the clusters
    a1 = a2 & 0x1;
    sq(v0, sp, 0x1B0);
    lw(v0, a3, res_entry::kVertexCount);
    sw(v0, sp, 0x1F0);  // the vertex total (sp+0x1F0)
    lw(v0, a3, res_entry::kHeader + ps2all_hdr::kBlockClusters);
    sq(v0, sp, 0x1C0);  // clusters per DMA block (sp+0x1C0)
    if (a1 == 0) {
        // 0x0049dcec: not a strip
        charge(ctx, 3);
        v0 = a2 & 0x8;
        if (v0 != 0) {
            // 0x0049e484 (written out on this path): a polyline: the strip / polyline record's overlap (+185);
            // the vertex total grows by overlap * (clusters - 1)
            charge(ctx, 9);
            lw(v0, sp, 0x200);
            a1 = addiu(v1, -1);
            lbu(v0, v0, ps2all_matpvt::kStripOverlap);
            sw(v0, sp, 0x90);
            mult(a1, v0, a1);
            lw(v0, sp, 0x1F0);
            v0 = addu(v0, a1);
            sw(v0, sp, 0x1F0);
            backedge(ctx);
        } else {
            // 0x0049dcf8: a list: the list record's overlap (+497)
            charge(ctx, 3);
            lw(v0, sp, 0x200);
            lbu(v0, v0, ps2all_matpvt::kListOverlap);
            sw(v0, sp, 0x90);
        }
    } else {
        // 0x0049e484: a strip: the strip / polyline record's overlap (+185); the vertex total grows by
        // overlap * (clusters - 1)
        charge(ctx, 9);
        lw(v0, sp, 0x200);
        a1 = addiu(v1, -1);
        lbu(v0, v0, ps2all_matpvt::kStripOverlap);
        sw(v0, sp, 0x90);
        mult(a1, v0, a1);
        lw(v0, sp, 0x1F0);
        v0 = addu(v0, a1);
        sw(v0, sp, 0x1F0);
        backedge(ctx);
    }
    // 0x0049dd04: the UNPACK templates of the frame (sp + 0xB0 .. 0x1A0), then cluster by cluster
    charge(ctx, 5);
    at = slt(0, v1);
    s3 = s4;
    s2 = 0;
    s1 = 0;
    if (at != 0) {
        // 0x0049dd18
        charge(ctx, 3);
        at = slt(0, v1);
        sd(zero, sp, 0x1D8);
        if (at != 0) {
            // 0x0049dd24
            charge(ctx, 46);
            lq(v0, sp, 0x1B0);
            a2 = 0x1000000;
            lq(a1, sp, 0x1B0);
            a3 = 0x11000000;
            t6 = 0;
            v0 = dsll32(v0, 0);
            v0 = dsrl32(v0, 0);
            sq(v0, sp, 0x1A0);
            v0 = a2 | 0x100;  // &0x1000100
            sq(v0, sp, 0x190);
            v0 = a1 | v0;
            t3 = dsll32(v0, 0);
            a1 = 0;
            v0 = a2 | 0x404;  // &0x1000404
            t3 = dsrl32(t3, 0);
            sq(v0, sp, 0xB0);
            a2 = dsll32(a3, 0);
            v0 = 0xFF00;
            v0 = dsll(v0, 16);
            v0 = v0 | 0x4000;
            sq(v0, sp, 0x170);
            v0 = 0x10000000;
            pcpyld(v0, a1, v0);
            a1 = 0x68000000;
            sq(v0, sp, 0x1E0);
            a1 = a1 | 0x8000;
            v0 = 0x5000000;
            sq(a1, sp, 0x160);
            v0 = dsll32(v0, 0);
            a1 = a3 | a2;
            sq(a1, sp, 0x180);
            a1 = 0x6C000000;
            a1 = a1 | 0x8000;
            sq(a1, sp, 0x150);
            a1 = 0x64000000;
            a1 = a1 | 0x8000;
            sq(a1, sp, 0x130);
            a1 = 0x6E000000;
            a1 = a1 | 0xC000;
            sq(a1, sp, 0xF0);
            a1 = 0x6A000000;
            a1 = a1 | 0x8000;
            sq(a1, sp, 0xC0);
            lq(a1, sp, 0x1B0);
            a1 = addiu(a1, 1);
            sq(a1, sp, 0xA0);
            for (;;) {
                // 0x0049dddc
                charge(ctx, 4);
                a1 = addiu(v1, -1);
                at = slt(s1, a1);
                if (at == 0) {
                    // 0x0049ddf4
                    charge(ctx, 4);
                    lw(v1, s5, ps2all_hdr::kClusterVerts);
                    mult(a1, a1, v1);
                    lw(v1, sp, 0x1F0);
                    t8 = subu(v1, a1);
                } else {
                    // 0x0049ddec
                    charge(ctx, 2);
                    lw(t8, s5, ps2all_hdr::kClusterVerts);
                }
                // 0x0049de04
                charge(ctx, 5);
                lq(v1, sp, 0x1C0);
                divu(s1, v1);
                mfhi(v1);
                if (v1 == 0) {
                    // 0x0049de18
                    charge(ctx, 3);
                    a1 = subu(s4, s3);
                    v1 = sra(a1, 4);
                    if (i64(a1) < 0) {
                        // 0x0049de24
                        charge(ctx, 2);
                        v1 = addiu(a1, 15);
                        v1 = sra(v1, 4);
                    }
                    // 0x0049de2c
                    charge(ctx, 11);
                    a2 = addiu(v1, -1);
                    lq(a1, sp, 0x180);
                    v1 = 0x10000000;
                    v1 = a2 | v1;
                    a2 = dsll32(v1, 0);
                    lw(v1, sp, 0x200);
                    a2 = dsra32(a2, 0);
                    if (s1 != 0) a1 = 0;
                    lbu(v1, v1, 180);
                    pcpyld(a1, a1, a2);
                    if (v1 != 0) {
                        // 0x0049de58: double buffered
                        charge(ctx, 2);
                        if (s1 == 0) {
                            // 0x0049e4a8 (written out on this path): the first block: the whole tag quadword
                            charge(ctx, 4);
                            sq(a1, s3, 0);
                            s3 = s4;
                            s4 = addiu(s4, 16);
                            backedge(ctx);
                        } else {
                            // 0x0049de60: the previous block's tag word; the block is open
                            charge(ctx, 3);
                            sd(a2, s3, 0);
                            s2 = 1;
                            s3 = s4;
                        }
                    } else {
                        // 0x0049e4a8: the tag quadword (FLUSH-headed for the first block), the next tag after it
                        charge(ctx, 4);
                        sq(a1, s3, 0);
                        s3 = s4;
                        s4 = addiu(s4, 16);
                        backedge(ctx);
                    }
                }
                // 0x0049de6c: the streams of this cluster
                charge(ctx, 5);
                lw(a1, a0, ps2all_pd::kMorphStreams);
                a2 = addiu(a1, 10);
                at = slt(0, a2);
                s0 = 0;
                if (at != 0) {
                    // 0x0049de80
                    charge(ctx, 2);
                    lw(t5, sp, 0x200);
                    t4 = s5;
                    for (;;) {
                        // 0x0049de88
                        charge(ctx, 4);
                        lw(a2, t5, ps2all_matpvt::kStreamFlags);
                        v1 = a2 & 0x1;
                        if (v1 != 0) {
                            // 0x0049de98
                            charge(ctx, 3);
                            v1 = a2 & 0x2000;
                            if (v1 == 0) {
                                // 0x0049dea4
                                charge(ctx, 5);
                                v1 = lui(0xFF00);
                                v1 = a2 & v1;  // the stream's UNPACK format (bits 24..31)
                                a2 = 0x6C000000;
                                // t7 = the element size in words by the format: V4-32 4, V3-32 3, V2-32 / V4-16 2,
                                // V3-16 / V4-8 / S-32 1, anything else 4 (0x0049df08 / df10 / df18 / df20)
                                do {
                                    if (v1 == a2) {
                                        // 0x0049df20: V4-32
                                        charge(ctx, 2);
                                        t7 = 4;
                                        break;
                                    }
                                    // 0x0049deb8
                                    charge(ctx, 3);
                                    a2 = 0x68000000;
                                    if (v1 == a2) {
                                        // 0x0049df18: V3-32
                                        charge(ctx, 2);
                                        t7 = 3;
                                        break;
                                    }
                                    // 0x0049dec4
                                    charge(ctx, 3);
                                    a2 = 0x6D000000;
                                    if (v1 == a2) {
                                        // 0x0049df10: V4-16
                                        charge(ctx, 2);
                                        t7 = 2;
                                        break;
                                    }
                                    // 0x0049ded0
                                    charge(ctx, 3);
                                    a2 = 0x64000000;
                                    if (v1 == a2) {
                                        // 0x0049df10: V2-32
                                        charge(ctx, 2);
                                        t7 = 2;
                                        break;
                                    }
                                    // 0x0049dedc
                                    charge(ctx, 3);
                                    a2 = 0x65000000;
                                    if (v1 == a2) {
                                        // 0x0049df08: V2-16
                                        charge(ctx, 2);
                                        t7 = 1;
                                        break;
                                    }
                                    // 0x0049dee8
                                    charge(ctx, 3);
                                    a2 = 0x6E000000;
                                    if (v1 == a2) {
                                        // 0x0049df08: V4-8
                                        charge(ctx, 2);
                                        t7 = 1;
                                        break;
                                    }
                                    // 0x0049def4
                                    charge(ctx, 3);
                                    a2 = 0x60000000;
                                    if (v1 == a2) {
                                        // 0x0049df08: S-32
                                        charge(ctx, 2);
                                        t7 = 1;
                                        break;
                                    }
                                    // 0x0049df00: any other format
                                    charge(ctx, 2);
                                    // 0x0049df20
                                    charge(ctx, 2);
                                    t7 = 4;
                                } while (false);
                                // 0x0049df28: the stream's offset (the morph target's second one when a1 != 0)
                                charge(ctx, 2);
                                lw(t0, t4, ps2all_hdr::kStreams + ps2all_stream::kOffset);
                                if (a1 != 0) {
                                    // 0x0049df30
                                    charge(ctx, 2);
                                    lw(t0, t4, ps2all_hdr::kStreams + ps2all_stream::kOffset2);
                                }
                                // 0x0049df38: a stream outside the cluster: a `ref` tag (0x30000000 | qwords) to its
                                // data, STCYCL 1,1 and the
                                // UNPACK (format, vertices << 16, the unpack address), then a `cnt` quadword
                                charge(ctx, 52);
                                mult(a3, t8, t7);
                                lw(a2, s5, ps2all_hdr::kClusterVerts);
                                lw(a1, sp, 0x90);
                                v1 = addiu(a3, 3);
                                a2 = subu(a2, a1);
                                mult1(a1, t7, t6);
                                mult(a2, a2, a1);
                                t1 = sll(t0, 4);
                                lw(t0, s5, ps2all_hdr::kData);
                                t2 = sra(v1, 2);
                                s6 = addiu(t7, -1);
                                a1 = 0x30000000;
                                a1 = t2 | a1;
                                t2 = si(-4);
                                v1 = v1 & t2;
                                t0 = addu(t0, t1);
                                v1 = subu(v1, a3);
                                t2 = dsll32(a2, 0);
                                v1 = addu(v1, s6);
                                a3 = dsll32(a1, 0);
                                div(v1, t7);
                                t0 = dsll32(t0, 0);
                                lbu(a1, t4, ps2all_hdr::kStreams + ps2all_stream::kUnpack);
                                t2 = dsrl32(t2, 0);
                                t0 = dsra32(t0, 0);
                                lwu(a2, t5, ps2all_matpvt::kStreamFlags);
                                t0 = t0 + t2;
                                a3 = dsra32(a3, 0);
                                t1 = dsll32(t0, 0);
                                lq(t0, sp, 0x170);
                                a1 = dsll32(a1, 0);
                                a1 = dsra32(a1, 0);
                                t0 = a2 & t0;
                                a2 = a3 | t1;
                                a3 = t0 | 0x8000;
                                a1 = a3 | a1;
                                mflo(v1);
                                v1 = addu(t8, v1);
                                v1 = sll(v1, 16);
                                v1 = a1 | v1;
                                a1 = dsll32(v1, 0);
                                lq(v1, sp, 0x190);
                                a1 = a1 | v1;
                                lq(v1, sp, 0x1A0);
                                v1 = a1 | v1;
                                pcpyld(v1, v1, a2);
                                sq(v1, s3, 0);
                                lq(v1, sp, 0x1E0);
                                s3 = addiu(s4, 16);
                                sq(v1, s4, 0);
                                s4 = addiu(s4, 32);
                            }
                        }
                        // 0x0049e008: the next stream (ten, plus a morph target's)
                        charge(ctx, 7);
                        lw(a1, a0, ps2all_pd::kMorphStreams);
                        s0 = addiu(s0, 1);
                        t5 = addiu(t5, 8);
                        a2 = addiu(a1, 10);
                        v1 = slt(s0, a2);
                        t4 = addiu(t4, 24);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0049e024
                    charge(ctx, 1);
                }
                // 0x0049e028: the streams in the cluster: an UNPACK header by type (the frame's templates) before each
                // data area
                charge(ctx, 3);
                at = slt(0, a2);
                t0 = 0;
                if (at != 0) {
                    // 0x0049e034
                    charge(ctx, 56);
                    lq(v1, sp, 0x160);
                    t4 = sll(t8, 16);
                    t5 = sll(t8, 2);
                    a1 = addiu(t8, 1);
                    t5 = addiu(t5, 3);
                    lw(t2, sp, 0x200);
                    t1 = s5;
                    a3 = t4 | v1;
                    v1 = sll(a1, 1);
                    a2 = addu(v1, a1);
                    lq(v1, sp, 0x150);
                    a2 = sra(a2, 2);
                    a2 = sll(a2, 4);
                    a1 = t4 | v1;
                    v1 = sll(t8, 4);
                    sq(v1, sp, 0x140);
                    lq(v1, sp, 0x130);
                    v1 = t4 | v1;
                    sq(v1, sp, 0x120);
                    v1 = sll(t8, 1);
                    t7 = addiu(v1, 3);
                    s0 = sra(t7, 2);
                    v1 = addu(v1, t8);
                    t7 = sra(t5, 2);
                    t5 = sll(s0, 4);
                    sq(t5, sp, 0x110);
                    t5 = sll(t7, 4);
                    sq(t5, sp, 0x100);
                    lq(t5, sp, 0xF0);
                    t5 = t4 | t5;
                    sq(t5, sp, 0xE0);
                    lq(t5, sp, 0xC0);
                    s6 = t4 | t5;
                    t4 = addiu(v1, 15);
                    v1 = si(-16);
                    v1 = t4 & v1;
                    t4 = addiu(t8, 3);
                    t4 = sra(t4, 2);
                    t4 = sll(t4, 4);
                    sq(t4, sp, 0xD0);
                    lq(t4, sp, 0x1B0);
                    mult(t4, t8, t4);
                    t4 = dsll32(t4, 0);
                    t4 = dsrl32(t4, 0);
                    t4 = a3 | t4;
                    t5 = dsll32(t4, 0);
                    lq(t4, sp, 0xB0);
                    s7 = t5 | t4;
                    lq(t4, sp, 0xA0);
                    mult1(t4, t8, t4);
                    t4 = dsll32(t4, 0);
                    t4 = dsrl32(t4, 0);
                    t4 = s6 | t4;
                    t5 = dsll32(t4, 0);
                    lq(t4, sp, 0xB0);
                    fp = t5 | t4;
                    for (;;) {
                        // 0x0049e114
                        charge(ctx, 4);
                        lw(t5, t2, ps2all_matpvt::kStreamFlags);
                        t4 = t5 & 0x1;
                        if (t4 != 0) {
                            // 0x0049e124
                            charge(ctx, 3);
                            t4 = t5 & 0x2000;
                            if (t4 != 0) {
                                // 0x0049e130
                                charge(ctx, 3);
                                at = sltiu(t0, 12);
                                if (at != 0) {
                                    // 0x0049e13c: the stream's type picks its UNPACK template (jump table 0x7BCA50)
                                    charge(ctx, 7);
                                    t4 = hi(kJtDmaUnpack);
                                    t5 = sll(t0, 2);
                                    t4 = addiu(t4, lo(kJtDmaUnpack));
                                    t4 = addu(t5, t4);
                                    lw(t4, t4, 0);
                                    switch (t4.u()) {
                                    case 0x49E158u:  // table[0]
                                        // 0x0049e158
                                        charge(ctx, 2);
                                        if (s2 == 0) {
                                            // 0x0049e170
                                            charge(ctx, 2);
                                            t4 = v0;
                                        } else {
                                            // 0x0049e160
                                            charge(ctx, 3);
                                            ld(t4, s4, 0);
                                            s2 = 0;
                                        }
                                        // 0x0049e178
                                        charge(ctx, 12);
                                        lbu(t7, t1, ps2all_hdr::kStreams + ps2all_stream::kUnpack);
                                        t5 = addu(s4, a2);
                                        t7 = dsll32(t7, 0);
                                        t7 = dsra32(t7, 0);
                                        t7 = a3 | t7;
                                        t7 = dsll32(t7, 0);
                                        t7 = t3 | t7;
                                        pcpyld(t4, t7, t4);
                                        sq(t4, s4, 0);
                                        sq(t9, t5, 0);
                                        s4 = addiu(t5, 16);
                                        break;
                                    case 0x49E1A8u:  // table[1]
                                        // 0x0049e1a8
                                        charge(ctx, 2);
                                        if (s2 == 0) {
                                            // 0x0049e1c0
                                            charge(ctx, 2);
                                            t5 = v0;
                                        } else {
                                            // 0x0049e1b0
                                            charge(ctx, 3);
                                            ld(t5, s4, 0);
                                            s2 = 0;
                                        }
                                        // 0x0049e1c8
                                        charge(ctx, 13);
                                        lbu(t4, t1, ps2all_hdr::kStreams + ps2all_stream::kUnpack);
                                        lq(t7, sp, 0x140);
                                        t4 = dsll32(t4, 0);
                                        t4 = dsra32(t4, 0);
                                        t7 = addu(s4, t7);
                                        t4 = a1 | t4;
                                        t4 = dsll32(t4, 0);
                                        t4 = t3 | t4;
                                        pcpyld(t4, t4, t5);
                                        sq(t4, s4, 0);
                                        sq(t9, t7, 0);
                                        s4 = addiu(t7, 16);
                                        break;
                                    case 0x49E200u:  // table[2]
                                        // 0x0049e200
                                        charge(ctx, 2);
                                        if (s2 == 0) {
                                            // 0x0049e218
                                            charge(ctx, 2);
                                            s0 = v0;
                                        } else {
                                            // 0x0049e208
                                            charge(ctx, 3);
                                            ld(s0, s4, 0);
                                            s2 = 0;
                                        }
                                        // 0x0049e220
                                        charge(ctx, 14);
                                        lbu(t4, t1, ps2all_hdr::kStreams + ps2all_stream::kUnpack);
                                        lq(t5, sp, 0x110);
                                        t7 = dsll32(t4, 0);
                                        lq(t4, sp, 0x120);
                                        t7 = dsra32(t7, 0);
                                        t5 = addu(s4, t5);
                                        t4 = t4 | t7;
                                        t4 = dsll32(t4, 0);
                                        t4 = t3 | t4;
                                        pcpyld(t4, t4, s0);
                                        sq(t4, s4, 0);
                                        sq(t9, t5, 0);
                                        s4 = addiu(t5, 16);
                                        break;
                                    case 0x49E258u:  // table[3]
                                        // 0x0049e258
                                        charge(ctx, 2);
                                        if (s2 == 0) {
                                            // 0x0049e270
                                            charge(ctx, 2);
                                            t5 = v0;
                                        } else {
                                            // 0x0049e260
                                            charge(ctx, 3);
                                            ld(t5, s4, 0);
                                            s2 = 0;
                                        }
                                        // 0x0049e278
                                        charge(ctx, 13);
                                        lbu(t4, t1, ps2all_hdr::kStreams + ps2all_stream::kUnpack);
                                        lq(t7, sp, 0x100);
                                        t4 = dsll32(t4, 0);
                                        t4 = dsra32(t4, 0);
                                        t7 = addu(s4, t7);
                                        t4 = a1 | t4;
                                        t4 = dsll32(t4, 0);
                                        t4 = t3 | t4;
                                        pcpyld(t4, t4, t5);
                                        sq(t4, s4, 0);
                                        sq(t9, t7, 0);
                                        s4 = addiu(t7, 16);
                                        break;
                                    case 0x49E2B0u:  // table[4]
                                        // 0x0049e2b0
                                        charge(ctx, 2);
                                        if (s2 == 0) {
                                            // 0x0049e2c8
                                            charge(ctx, 2);
                                            s0 = v0;
                                        } else {
                                            // 0x0049e2b8
                                            charge(ctx, 3);
                                            ld(s0, s4, 0);
                                            s2 = 0;
                                        }
                                        // 0x0049e2d0
                                        charge(ctx, 14);
                                        lbu(t4, t1, ps2all_hdr::kStreams + ps2all_stream::kUnpack);
                                        lq(t5, sp, 0xD0);
                                        t7 = dsll32(t4, 0);
                                        lq(t4, sp, 0xE0);
                                        t7 = dsra32(t7, 0);
                                        t5 = addu(s4, t5);
                                        t4 = t4 | t7;
                                        t4 = dsll32(t4, 0);
                                        t4 = t3 | t4;
                                        pcpyld(t4, t4, s0);
                                        sq(t4, s4, 0);
                                        sq(t9, t5, 0);
                                        s4 = addiu(t5, 16);
                                        break;
                                    case 0x49E308u:  // table[5]
                                        // 0x0049e308
                                        charge(ctx, 2);
                                        if (s2 == 0) {
                                            // 0x0049e320
                                            charge(ctx, 2);
                                            t4 = v0;
                                        } else {
                                            // 0x0049e310
                                            charge(ctx, 3);
                                            ld(t4, s4, 0);
                                            s2 = 0;
                                        }
                                        // 0x0049e328
                                        charge(ctx, 12);
                                        lbu(t7, t1, ps2all_hdr::kStreams + ps2all_stream::kUnpack);
                                        t5 = addu(s4, v1);
                                        t7 = dsll32(t7, 0);
                                        t7 = dsra32(t7, 0);
                                        t7 = s6 | t7;
                                        t7 = dsll32(t7, 0);
                                        t7 = t3 | t7;
                                        pcpyld(t4, t7, t4);
                                        sq(t4, s4, 0);
                                        sq(t9, t5, 0);
                                        s4 = addiu(t5, 16);
                                        break;
                                    case 0x49E358u:  // table[10]
                                        // 0x0049e358
                                        charge(ctx, 2);
                                        if (s2 == 0) {
                                            // 0x0049e370
                                            charge(ctx, 2);
                                            t5 = v0;
                                        } else {
                                            // 0x0049e360
                                            charge(ctx, 3);
                                            ld(t5, s4, 0);
                                            s2 = 0;
                                        }
                                        // 0x0049e378
                                        charge(ctx, 6);
                                        t4 = addu(s4, a2);
                                        pcpyld(t5, s7, t5);
                                        sq(t5, s4, 0);
                                        sq(t9, t4, 0);
                                        s4 = addiu(t4, 16);
                                        break;
                                    case 0x49E390u:  // table[11]
                                        // 0x0049e390
                                        charge(ctx, 2);
                                        if (s2 == 0) {
                                            // 0x0049e3a8
                                            charge(ctx, 2);
                                            t5 = v0;
                                        } else {
                                            // 0x0049e398
                                            charge(ctx, 3);
                                            ld(t5, s4, 0);
                                            s2 = 0;
                                        }
                                        // 0x0049e3b0
                                        charge(ctx, 6);
                                        t4 = addu(s4, v1);
                                        pcpyld(t5, fp, t5);
                                        sq(t5, s4, 0);
                                        sq(t9, t4, 0);
                                        s4 = addiu(t4, 16);
                                        break;
                                    case 0x49E3C8u:  // table[6, 7, 8, 9]
                                        break;
                                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                                        tail(ctx, t4.u());
                                        return;
                                    }
                                }
                            }
                        }
                        // 0x0049e3c8: the next stream
                        charge(ctx, 7);
                        lw(t4, a0, ps2all_pd::kMorphStreams);
                        t0 = addiu(t0, 1);
                        t2 = addiu(t2, 8);
                        t4 = addiu(t4, 10);
                        t4 = slt(t0, t4);
                        t1 = addiu(t1, 24);
                        if (t4 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x0049e3e4
                    charge(ctx, 1);
                }
                // 0x0049e3e8: the cluster's ITOP / MSCAL quadword (0x04000000 | vertices; 0x15000000 for the first
                // cluster, 0x17000000 after)
                charge(ctx, 18);
                v1 = 0x4000000;
                v1 = t8 | v1;
                a2 = 0x15000000;
                a1 = dsll32(v1, 0);
                t6 = addiu(t6, 4);
                v1 = 0x17000000;
                a1 = dsra32(a1, 0);
                if (s1 != 0) a2 = v1;
                v1 = dsll32(a2, 0);
                s1 = addiu(s1, 1);
                a1 = v1 | a1;
                ld(v1, sp, 0x1D8);
                pcpyld(v1, v1, a1);
                sq(v1, s4, 0);
                lw(v1, s5, ps2all_hdr::kClusterCount);
                a1 = slt(s1, v1);
                s4 = addiu(s4, 16);
                if (a1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x0049e430: close the last block: the FLUSH pair, its `ret` tag (0x60000000 | qwords - 1)
    charge(ctx, 7);
    a1 = 0x11000000;
    v1 = subu(s4, s3);
    a0 = dsll32(a1, 0);
    v0 = sra(v1, 4);
    a0 = a1 | a0;
    sd(a0, s4, -8);
    if (i64(v1) < 0) {
        // 0x0049e44c
        charge(ctx, 2);
        v0 = addiu(v1, 15);
        v0 = sra(v0, 4);
    }
    // 0x0049e454
    charge(ctx, 10);
    v1 = addiu(v0, -1);
    v0 = 0x60000000;
    v0 = v1 | v0;
    v0 = dsll32(v0, 0);
    v0 = dsra32(v0, 0);
    sd(v0, s3, 0);
    lw(v0, sp, 0x200);
    lbu(v0, v0, ps2all_matpvt::kDoubleBuffer);
    if (v0 == 0) {  // the ref's high word zeroed when not double buffered
        // 0x0049e4b8
        charge(ctx, 2);
        sd(zero, s3, 8);
        backedge(ctx);
    }
    // 0x0049e47c: return 1
    charge(ctx, 2);
    v0 = 1;
    // 0x0049e4c0
    charge(ctx, 11);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x210);
}

// 0x004A42F0 ps2AllSectorInstance -- 2644 bytes; frame 0x90: fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// ps2AllSectorInstance [world sector instance] (pipe data $a0): the sector's vertex streams (sector = pd +8) into the resEntry's
// clusters, as ps2AllIm3DInstance does for Im3D (the same walk tables at 0x7BCB4x, the identity table 0x7BCB50, the overlap
// $t8 2 / 1 / 0), each stream when its material pipeline stream flags (matPvt +32 + 8 k) have bit 0 and not bit 3:
// positions 12 bytes (+8, stream +152.., pd +52 bit 4), positions 16 bytes with w = 0 (+8, stream +176.., bit 4),
// UVs 8 bytes (+16, +200.., pd +52 bits 7..8 and world flags 0x84), two UV sets 16 bytes (+16 and +20 when the world has
// flag 0x80, +224..), colours (+48, +248.., bit 6: the prelit RGBA when the world has flag 8, else 0xFF000000) and
// normals (+12, +272.., bit 5: 3 or 4 signed bytes by the stream's 0x2000 flag, zero when the world has no normals
// (flag 0x10)). The current world is RW globals +4. Returns 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void ps2AllSectorInstance(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::lb, hg::lbu,
          hg::lh, hg::lhu, hg::lq, hg::lui, hg::lw, hg::lwc1, hg::sb, hg::sll, hg::sllv, hg::slt, hg::sq, hg::srlv,
          hg::subu, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30};
    Fpr f0{ctx, 0};
    // 0x004a42f0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    v0 = hi(rwl::kRwGlobals + rw_globals::kCurrentWorld);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s2, v0, lo(rwl::kRwGlobals + rw_globals::kCurrentWorld));  // s2 = the current world
    lw(v1, a0, ps2all_pd::kResEntrySlot);  // the resEntry slot
    lw(s7, a0, ps2all_pd::kObject);  // s7 = the sector
    lw(v0, a0, ps2all_pd::kMeshHeader);  // the mesh header
    lw(v1, v1, 0);  // v1 = the resEntry
    lw(a2, v0, mesh_hdr::kFlags);  // a2 = the mesh header flags
    lw(s1, v1, res_entry::kVertexCount);  // s1 = the vertices to instance
    v0 = a2 & 0x2;  // a fan?
    a1 = addiu(v1, res_entry::kHeader);  // a1 = the instance header
    if (v0 == 0) {
        // strips / lists: the walk's slot pattern (s0), start slot (t9) and index columns (t7, t6, t5); fans their own
        // 0x004a4370
        charge(ctx, 10);
        v1 = hi(kWalkSector + walk::kListPattern);
        v0 = hi(kWalkSector + walk::kListStart);
        lbu(s0, v1, lo(kWalkSector + walk::kListPattern));
        t7 = hi(kWalkSector + walk::kListCol0);
        lbu(t9, v0, lo(kWalkSector + walk::kListStart));
        t6 = hi(kWalkSector + walk::kListCol1);
        t5 = hi(kWalkSector + walk::kListCol2);
        t7 = addiu(t7, lo(kWalkSector + walk::kListCol0));
        t6 = addiu(t6, lo(kWalkSector + walk::kListCol1));
        t5 = addiu(t5, lo(kWalkSector + walk::kListCol2));
    } else {
        // 0x004a4344
        charge(ctx, 11);
        v1 = hi(kWalkSector + walk::kFanPattern);
        v0 = hi(kWalkSector + walk::kFanStart);
        lbu(s0, v1, lo(kWalkSector + walk::kFanPattern));
        t7 = hi(kWalkSector + walk::kFanCol0);
        lbu(t9, v0, lo(kWalkSector + walk::kFanStart));
        t6 = hi(kWalkSector + walk::kFanCol1);
        t5 = hi(kWalkSector + walk::kFanCol2);
        t7 = addiu(t7, lo(kWalkSector + walk::kFanCol0));
        t6 = addiu(t6, lo(kWalkSector + walk::kFanCol1));
        t5 = addiu(t5, lo(kWalkSector + walk::kFanCol2));
    }
    // 0x004a4398: the overlap t8 each cluster after the first re-sends: 2 for a strip, 1 for a polyline, else 0
    charge(ctx, 3);
    v0 = a2 & 0x1;
    if (v0 != 0) {
        // 0x004a4518
        charge(ctx, 2);
        t8 = 2;
        backedge(ctx);
    } else {
        // 0x004a43a4
        charge(ctx, 3);
        v0 = a2 & 0x8;
        if (v0 == 0) {
            // 0x004a43b8
            charge(ctx, 1);
            t8 = 0;
        } else {
            // 0x004a43b0
            charge(ctx, 2);
            t8 = 1;
        }
    }
    // 0x004a43bc: the index table t4: the identity table (no indices) or the mesh's indices (columns t7 / t6 swapped)
    charge(ctx, 3);
    v0 = a2 & 0x100;
    if (v0 != 0) {
        // 0x004a43e0
        charge(ctx, 2);
        t4 = hi(kWalkSector + walk::kIdentity);
        t4 = addiu(t4, lo(kWalkSector + walk::kIdentity));
    } else {
        // 0x004a43c8
        charge(ctx, 6);
        lw(v0, a0, ps2all_pd::kMesh);
        v1 = t7;
        t7 = t6;
        lw(t4, v0, 0);
        t6 = v1;
    }
    // 0x004a43e8: stream 0: positions, 12 bytes per vertex, when the instance flags have bit 4 and the stream flags
    // bit 0 and
    // not bit 3
    charge(ctx, 4);
    lw(v0, a0, ps2all_pd::kInstFlags);
    v0 = v0 & 0x10;
    if (v0 != 0) {
        // 0x004a43f8
        charge(ctx, 5);
        lw(v0, a0, ps2all_pd::kMatPvt);
        lw(v1, v0, sflags(0));
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x004a440c
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 == 0) {
                // 0x004a4418
                charge(ctx, 10);
                lw(a2, a1, strm(0, ps2all_stream::kOffset));
                a3 = 0;
                lw(v1, a1, ps2all_hdr::kData);
                t0 = t9;
                lw(v0, s7, rw_sector::kVertices);
                t2 = s1;
                a2 = sll(a2, 4);
                a2 = addu(v1, a2);
                v1 = a2;
                if (i64(s1) > 0) {
                    for (;;) {
                        // 0x004a4440
                        charge(ctx, 4);
                        lw(t1, a1, ps2all_hdr::kClusterVerts);
                        at = slt(t1, t2);
                        if (at != 0) {
                            // 0x004a4470
                            charge(ctx, 4);
                            lw(t1, a1, strm(0, ps2all_stream::kCount));
                            t3 = subu(t1, t8);
                            t2 = subu(t2, t3);
                        } else {
                            // 0x004a4450
                            charge(ctx, 7);
                            lh(v1, a1, strm(0, ps2all_stream::kLastBack));
                            t1 = t2;
                            t2 = 0;
                            v1 = sll(v1, 4);
                            a2 = subu(a2, v1);
                            v1 = a2;
                        }
                        // 0x004a4480
                        charge(ctx, 3);
                        t3 = t1;
                        t1 = addiu(t1, -1);
                        if (t3 == 0) {
                            // 0x004a4520
                            charge(ctx, 1);
                            lh(v1, a1, strm(0, ps2all_stream::kStride));
                        } else {
                            // 0x004a448c
                            charge(ctx, 1);
                            for (;;) {
                                // 0x004a4490
                                charge(ctx, 31);
                                t3 = addu(t7, a3);
                                lbu(s5, t3, 0);
                                t3 = addu(t6, a3);
                                s5 = sllv(t0, s5);
                                lbu(s4, t3, 0);
                                s5 = sll(s5, 1);
                                s5 = addu(t4, s5);
                                t3 = addu(t5, a3);
                                s4 = sllv(t0, s4);
                                lbu(s3, t3, 0);
                                a3 = sll(a3, 1);
                                a3 = srlv(s0, a3);
                                a3 = a3 & 0x3;
                                t0 = addu(t0, s3);
                                t3 = t1;
                                lhu(s3, s5, 0);
                                t1 = addiu(t1, -1);
                                s3 = addu(s4, s3);
                                s4 = s3 & 0xFFFF;
                                s3 = sll(s4, 1);
                                s3 = addu(s3, s4);
                                s3 = sll(s3, 2);
                                s3 = addu(v0, s3);
                                lwc1(f0, s3, 0);
                                swc1(f0, v1, 0);
                                lwc1(f0, s3, 4);
                                swc1(f0, v1, 4);
                                lwc1(f0, s3, 8);
                                swc1(f0, v1, 8);
                                v1 = addiu(v1, 12);
                                if (t3 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004a450c
                            charge(ctx, 2);
                            lh(v1, a1, strm(0, ps2all_stream::kStride));
                        }
                        // 0x004a4524
                        charge(ctx, 5);
                        t0 = subu(t0, t8);
                        v1 = sll(v1, 4);
                        a2 = addu(a2, v1);
                        v1 = a2;
                        if (i64(t2) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
        }
    }
    // 0x004a4538: stream 1: positions, 16 bytes per vertex (w = 0)
    charge(ctx, 4);
    lw(v0, a0, ps2all_pd::kInstFlags);
    v0 = v0 & 0x10;
    if (v0 != 0) {
        // 0x004a4548
        charge(ctx, 5);
        lw(v0, a0, ps2all_pd::kMatPvt);
        lw(v1, v0, sflags(1));
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x004a455c
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 == 0) {
                // 0x004a4568
                charge(ctx, 10);
                lw(t1, a1, strm(1, ps2all_stream::kOffset));
                a3 = 0;
                lw(v1, a1, ps2all_hdr::kData);
                t0 = t9;
                lw(v0, s7, rw_sector::kVertices);
                a2 = s1;
                t1 = sll(t1, 4);
                t2 = addu(v1, t1);
                t1 = t2;
                if (i64(s1) > 0) {
                    for (;;) {
                        // 0x004a4590
                        charge(ctx, 4);
                        lw(v1, a1, ps2all_hdr::kClusterVerts);
                        at = slt(v1, a2);
                        if (at != 0) {
                            // 0x004a45c0
                            charge(ctx, 4);
                            lw(v1, a1, strm(1, ps2all_stream::kCount));
                            t3 = subu(v1, t8);
                            a2 = subu(a2, t3);
                        } else {
                            // 0x004a45a0
                            charge(ctx, 7);
                            lh(t1, a1, strm(1, ps2all_stream::kLastBack));
                            v1 = a2;
                            a2 = 0;
                            t1 = sll(t1, 4);
                            t2 = subu(t2, t1);
                            t1 = t2;
                        }
                        // 0x004a45d0
                        charge(ctx, 3);
                        t3 = v1;
                        v1 = addiu(v1, -1);
                        if (t3 != 0) {
                            // 0x004a45dc
                            charge(ctx, 1);
                            for (;;) {
                                // 0x004a45e0
                                charge(ctx, 32);
                                t3 = addu(t7, a3);
                                lbu(s5, t3, 0);
                                t3 = addu(t6, a3);
                                s5 = sllv(t0, s5);
                                lbu(s4, t3, 0);
                                s5 = sll(s5, 1);
                                s5 = addu(t4, s5);
                                t3 = addu(t5, a3);
                                s4 = sllv(t0, s4);
                                lbu(s3, t3, 0);
                                a3 = sll(a3, 1);
                                a3 = srlv(s0, a3);
                                a3 = a3 & 0x3;
                                t0 = addu(t0, s3);
                                t3 = v1;
                                lhu(s3, s5, 0);
                                v1 = addiu(v1, -1);
                                s3 = addu(s4, s3);
                                s4 = s3 & 0xFFFF;
                                s3 = sll(s4, 1);
                                s3 = addu(s3, s4);
                                s3 = sll(s3, 2);
                                s3 = addu(v0, s3);
                                lwc1(f0, s3, 0);
                                swc1(f0, t1, 0);
                                lwc1(f0, s3, 4);
                                swc1(f0, t1, 4);
                                lwc1(f0, s3, 8);
                                swc1(f0, t1, 8);
                                sw(zero, t1, 12);
                                t1 = addiu(t1, 16);
                                if (t3 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                        }
                        // 0x004a4660
                        charge(ctx, 6);
                        lh(v1, a1, strm(1, ps2all_stream::kStride));
                        t0 = subu(t0, t8);
                        v1 = sll(v1, 4);
                        t2 = addu(t2, v1);
                        t1 = t2;
                        if (i64(a2) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
        }
    }
    // 0x004a4678: stream 2: UVs, 8 bytes per vertex (instance flags bits 7..8, world flags 0x84)
    charge(ctx, 4);
    lw(v0, a0, ps2all_pd::kInstFlags);
    v0 = v0 & 0x180;
    if (v0 != 0) {
        // 0x004a4688
        charge(ctx, 5);
        lw(v0, a0, ps2all_pd::kMatPvt);
        lw(v1, v0, sflags(2));
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x004a469c
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 == 0) {
                // 0x004a46a8
                charge(ctx, 4);
                lw(v0, s2, rw_world::kFlags);
                v0 = v0 & 0x84;
                if (v0 != 0) {
                    // 0x004a46b8
                    charge(ctx, 10);
                    lw(t1, a1, strm(2, ps2all_stream::kOffset));
                    a3 = 0;
                    lw(v1, a1, ps2all_hdr::kData);
                    t0 = t9;
                    lw(v0, s7, rw_sector::kUv0);
                    a2 = s1;
                    t1 = sll(t1, 4);
                    t2 = addu(v1, t1);
                    t1 = t2;
                    if (i64(s1) > 0) {
                        for (;;) {
                            // 0x004a46e0
                            charge(ctx, 4);
                            lw(v1, a1, ps2all_hdr::kClusterVerts);
                            at = slt(v1, a2);
                            if (at != 0) {
                                // 0x004a4710
                                charge(ctx, 4);
                                lw(v1, a1, strm(2, ps2all_stream::kCount));
                                t3 = subu(v1, t8);
                                a2 = subu(a2, t3);
                            } else {
                                // 0x004a46f0
                                charge(ctx, 7);
                                lh(t1, a1, strm(2, ps2all_stream::kLastBack));
                                v1 = a2;
                                a2 = 0;
                                t1 = sll(t1, 4);
                                t2 = subu(t2, t1);
                                t1 = t2;
                            }
                            // 0x004a4720
                            charge(ctx, 3);
                            t3 = v1;
                            v1 = addiu(v1, -1);
                            if (t3 != 0) {
                                // 0x004a472c
                                charge(ctx, 1);
                                for (;;) {
                                    // 0x004a4730
                                    charge(ctx, 27);
                                    t3 = addu(t7, a3);
                                    lbu(s5, t3, 0);
                                    t3 = addu(t6, a3);
                                    s5 = sllv(t0, s5);
                                    lbu(s4, t3, 0);
                                    s5 = sll(s5, 1);
                                    s5 = addu(t4, s5);
                                    t3 = addu(t5, a3);
                                    s4 = sllv(t0, s4);
                                    lbu(s3, t3, 0);
                                    a3 = sll(a3, 1);
                                    a3 = srlv(s0, a3);
                                    a3 = a3 & 0x3;
                                    t0 = addu(t0, s3);
                                    t3 = v1;
                                    lhu(s3, s5, 0);
                                    v1 = addiu(v1, -1);
                                    s3 = addu(s4, s3);
                                    s3 = s3 & 0xFFFF;
                                    s3 = sll(s3, 3);
                                    s3 = addu(v0, s3);
                                    lwc1(f0, s3, 0);
                                    swc1(f0, t1, 0);
                                    lwc1(f0, s3, 4);
                                    swc1(f0, t1, 4);
                                    t1 = addiu(t1, 8);
                                    if (t3 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004a479c
                                charge(ctx, 1);
                            }
                            // 0x004a47a0
                            charge(ctx, 6);
                            lh(v1, a1, strm(2, ps2all_stream::kStride));
                            t0 = subu(t0, t8);
                            v1 = sll(v1, 4);
                            t2 = addu(t2, v1);
                            t1 = t2;
                            if (i64(a2) <= 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                }
            }
        }
    }
    // 0x004a47b8: stream 3: two UV sets, 16 bytes per vertex (the second set when the world has flag 0x80)
    charge(ctx, 4);
    lw(v0, a0, ps2all_pd::kInstFlags);
    v0 = v0 & 0x180;
    if (v0 != 0) {
        // 0x004a47c8
        charge(ctx, 5);
        lw(v0, a0, ps2all_pd::kMatPvt);
        lw(v1, v0, sflags(3));
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x004a47dc
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 == 0) {
                // 0x004a47e8
                charge(ctx, 4);
                lw(v1, s2, rw_world::kFlags);
                v0 = v1 & 0x84;
                if (v0 != 0) {
                    // 0x004a47f8
                    charge(ctx, 8);
                    lw(a3, a1, strm(3, ps2all_stream::kOffset));
                    v0 = v1 & 0x80;
                    lw(a2, a1, ps2all_hdr::kData);
                    lw(v1, s7, rw_sector::kUv0);
                    a3 = sll(a3, 4);
                    t3 = addu(a2, a3);
                    t2 = t3;
                    if (v0 == 0) {
                        // 0x004a4820
                        charge(ctx, 1);
                        v0 = v1;
                    } else {
                        // 0x004a4818
                        charge(ctx, 2);
                        lw(v0, s7, rw_sector::kUv1);
                    }
                    // 0x004a4824
                    charge(ctx, 4);
                    t0 = 0;
                    t1 = t9;
                    a3 = s1;
                    if (i64(s1) > 0) {
                        for (;;) {
                            // 0x004a4834
                            charge(ctx, 4);
                            lw(a2, a1, ps2all_hdr::kClusterVerts);
                            at = slt(a2, a3);
                            if (at != 0) {
                                // 0x004a4860
                                charge(ctx, 4);
                                lw(a2, a1, strm(3, ps2all_stream::kCount));
                                s3 = subu(a2, t8);
                                a3 = subu(a3, s3);
                            } else {
                                // 0x004a4844
                                charge(ctx, 7);
                                lh(t2, a1, strm(3, ps2all_stream::kLastBack));
                                a2 = a3;
                                a3 = 0;
                                t2 = sll(t2, 4);
                                t3 = subu(t3, t2);
                                t2 = t3;
                            }
                            // 0x004a4870
                            charge(ctx, 3);
                            s3 = a2;
                            a2 = addiu(a2, -1);
                            if (s3 == 0) {
                                // 0x004a4cf8
                                charge(ctx, 1);
                                lh(a2, a1, strm(3, ps2all_stream::kStride));
                            } else {
                                // 0x004a487c
                                charge(ctx, 1);
                                for (;;) {
                                    // 0x004a4880
                                    charge(ctx, 32);
                                    s3 = addu(t7, t0);
                                    lbu(s6, s3, 0);
                                    s3 = addu(t6, t0);
                                    s6 = sllv(t1, s6);
                                    lbu(s5, s3, 0);
                                    s6 = sll(s6, 1);
                                    s6 = addu(t4, s6);
                                    s3 = addu(t5, t0);
                                    s5 = sllv(t1, s5);
                                    lbu(s4, s3, 0);
                                    t0 = sll(t0, 1);
                                    t0 = srlv(s0, t0);
                                    t0 = t0 & 0x3;
                                    t1 = addu(t1, s4);
                                    s3 = a2;
                                    lhu(s4, s6, 0);
                                    a2 = addiu(a2, -1);
                                    s4 = addu(s5, s4);
                                    s4 = s4 & 0xFFFF;
                                    s4 = sll(s4, 3);
                                    s5 = addu(v1, s4);
                                    lwc1(f0, s5, 0);
                                    s4 = addu(v0, s4);
                                    swc1(f0, t2, 0);
                                    lwc1(f0, s5, 4);
                                    swc1(f0, t2, 4);
                                    lwc1(f0, s4, 0);
                                    swc1(f0, t2, 8);
                                    lwc1(f0, s4, 4);
                                    swc1(f0, t2, 12);
                                    t2 = addiu(t2, 16);
                                    if (s3 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004a4900
                                charge(ctx, 2);
                                lh(a2, a1, strm(3, ps2all_stream::kStride));
                            }
                            // 0x004a4cfc
                            charge(ctx, 5);
                            t1 = subu(t1, t8);
                            a2 = sll(a2, 4);
                            t3 = addu(t3, a2);
                            t2 = t3;
                            if (i64(a3) <= 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004a4d10
                        charge(ctx, 2);
                        backedge(ctx);
                    }
                }
            }
        }
    }
    // 0x004a4908: stream 4: colours (bit 6: the prelit RGBA when the world has flag 8, else 0xFF000000)
    charge(ctx, 4);
    lw(v0, a0, ps2all_pd::kInstFlags);
    v0 = v0 & 0x40;
    if (v0 != 0) {
        // 0x004a4918
        charge(ctx, 5);
        lw(v0, a0, ps2all_pd::kMatPvt);
        lw(v1, v0, sflags(4));
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x004a492c
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 == 0) {
                // 0x004a4938
                charge(ctx, 10);
                lw(t1, a1, strm(4, ps2all_stream::kOffset));
                a3 = 0;
                lw(v1, a1, ps2all_hdr::kData);
                t0 = t9;
                lw(v0, s7, rw_sector::kPrelit);
                a2 = s1;
                t1 = sll(t1, 4);
                t2 = addu(v1, t1);
                t1 = t2;
                if (i64(s1) > 0) {
                    // 0x004a4960
                    charge(ctx, 1);
                    fp = lui(0xFF00);
                    for (;;) {
                        // 0x004a4964
                        charge(ctx, 4);
                        lw(v1, a1, ps2all_hdr::kClusterVerts);
                        at = slt(v1, a2);
                        if (at != 0) {
                            // 0x004a4990
                            charge(ctx, 4);
                            lw(v1, a1, strm(4, ps2all_stream::kCount));
                            t3 = subu(v1, t8);
                            a2 = subu(a2, t3);
                        } else {
                            // 0x004a4974
                            charge(ctx, 7);
                            lh(t1, a1, strm(4, ps2all_stream::kLastBack));
                            v1 = a2;
                            a2 = 0;
                            t1 = sll(t1, 4);
                            t2 = subu(t2, t1);
                            t1 = t2;
                        }
                        // 0x004a49a0
                        charge(ctx, 4);
                        lw(t3, s2, rw_world::kFlags);
                        t3 = t3 & 0x8;
                        if (t3 == 0) {
                            // 0x004a4a50
                            charge(ctx, 3);
                            t3 = v1;
                            v1 = addiu(v1, -1);
                            if (t3 != 0) {
                                // 0x004a4a5c
                                charge(ctx, 1);
                                for (;;) {
                                    // 0x004a4a60
                                    charge(ctx, 7);
                                    sw(fp, t1, 0);
                                    t3 = v1;
                                    t1 = addiu(t1, 4);
                                    v1 = addiu(v1, -1);
                                    if (t3 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004a4a7c
                                charge(ctx, 1);
                            }
                        } else {
                            // 0x004a49b0
                            charge(ctx, 3);
                            t3 = v1;
                            v1 = addiu(v1, -1);
                            if (t3 != 0) {
                                // 0x004a49bc
                                charge(ctx, 1);
                                for (;;) {
                                    // 0x004a49c0
                                    charge(ctx, 34);
                                    t3 = addu(t7, a3);
                                    lbu(s5, t3, 0);
                                    t3 = addu(t6, a3);
                                    s5 = sllv(t0, s5);
                                    lbu(s4, t3, 0);
                                    s5 = sll(s5, 1);
                                    s5 = addu(t4, s5);
                                    t3 = addu(t5, a3);
                                    s4 = sllv(t0, s4);
                                    lbu(s3, t3, 0);
                                    a3 = sll(a3, 1);
                                    a3 = srlv(s0, a3);
                                    a3 = a3 & 0x3;
                                    t0 = addu(t0, s3);
                                    t3 = v1;
                                    lhu(s3, s5, 0);
                                    v1 = addiu(v1, -1);
                                    s3 = addu(s4, s3);
                                    s3 = s3 & 0xFFFF;
                                    s3 = sll(s3, 2);
                                    s3 = addu(v0, s3);
                                    lbu(s6, s3, 1);
                                    lbu(s4, s3, 2);
                                    lbu(s5, s3, 0);
                                    s6 = sll(s6, 8);
                                    s4 = sll(s4, 16);
                                    lbu(s3, s3, 3);
                                    s5 = s5 | s6;
                                    s4 = s4 | s5;
                                    s3 = sll(s3, 24);
                                    s3 = s3 | s4;
                                    sw(s3, t1, 0);
                                    t1 = addiu(t1, 4);
                                    if (t3 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004a4a48
                                charge(ctx, 2);
                            }
                        }
                        // 0x004a4a80
                        charge(ctx, 6);
                        lh(v1, a1, strm(4, ps2all_stream::kStride));
                        t0 = subu(t0, t8);
                        v1 = sll(v1, 4);
                        t2 = addu(t2, v1);
                        t1 = t2;
                        if (i64(a2) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
        }
    }
    // 0x004a4a98: stream 5: normals (bit 5: 3 or 4 signed bytes by the stream's 0x2000 flag; zero without normals,
    // flag 0x10)
    charge(ctx, 4);
    lw(v0, a0, ps2all_pd::kInstFlags);
    v0 = v0 & 0x20;
    if (v0 != 0) {
        // 0x004a4aa8
        charge(ctx, 5);
        lw(v0, a0, ps2all_pd::kMatPvt);
        lw(v1, v0, sflags(5));
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x004a4abc
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 == 0) {
                // 0x004a4ac8
                charge(ctx, 8);
                lw(a2, a1, strm(5, ps2all_stream::kOffset));
                a3 = 0;
                lw(v0, a1, ps2all_hdr::kData);
                lw(v1, s7, rw_sector::kNormals);
                a2 = sll(a2, 4);
                t1 = addu(v0, a2);
                t0 = t1;
                if (i64(s1) > 0) {
                    for (;;) {
                        // 0x004a4ae8
                        charge(ctx, 4);
                        lw(v0, a1, ps2all_hdr::kClusterVerts);
                        at = slt(v0, s1);
                        if (at != 0) {
                            // 0x004a4b18
                            charge(ctx, 4);
                            lw(a2, a1, strm(5, ps2all_stream::kCount));
                            v0 = subu(a2, t8);
                            s1 = subu(s1, v0);
                        } else {
                            // 0x004a4af8
                            charge(ctx, 7);
                            lh(v0, a1, strm(5, ps2all_stream::kLastBack));
                            a2 = s1;
                            s1 = 0;
                            v0 = sll(v0, 4);
                            t1 = subu(t1, v0);
                            t0 = t1;
                        }
                        // 0x004a4b28
                        charge(ctx, 4);
                        lw(v0, s2, rw_world::kFlags);
                        v0 = v0 & 0x10;
                        if (v0 == 0) {
                            // 0x004a4c60
                            charge(ctx, 5);
                            lw(v0, a0, ps2all_pd::kMatPvt);
                            lw(v0, v0, sflags(5));
                            v0 = v0 & 0x2000;
                            if (v0 == 0) {
                                // 0x004a4ca8
                                charge(ctx, 3);
                                v0 = a2;
                                a2 = addiu(a2, -1);
                                if (v0 != 0) {
                                    // 0x004a4cb4
                                    charge(ctx, 1);
                                    for (;;) {
                                        // 0x004a4cb8
                                        charge(ctx, 8);
                                        sb(zero, t0, 0);
                                        sb(zero, t0, 1);
                                        v0 = a2;
                                        sb(zero, t0, 2);
                                        a2 = addiu(a2, -1);
                                        sb(zero, t0, 3);
                                        t0 = addiu(t0, 4);
                                        if (v0 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                }
                            } else {
                                // 0x004a4c74
                                charge(ctx, 3);
                                v0 = a2;
                                a2 = addiu(a2, -1);
                                if (v0 != 0) {
                                    for (;;) {
                                        // 0x004a4c80
                                        charge(ctx, 7);
                                        sb(zero, t0, 0);
                                        sb(zero, t0, 1);
                                        v0 = a2;
                                        sb(zero, t0, 2);
                                        a2 = addiu(a2, -1);
                                        t0 = addiu(t0, 3);
                                        if (v0 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004a4c9c
                                    charge(ctx, 2);
                                }
                            }
                        } else {
                            // 0x004a4b38
                            charge(ctx, 5);
                            lw(v0, a0, ps2all_pd::kMatPvt);
                            lw(v0, v0, sflags(5));
                            v0 = v0 & 0x2000;
                            if (v0 == 0) {
                                // 0x004a4bd0
                                charge(ctx, 3);
                                v0 = a2;
                                a2 = addiu(a2, -1);
                                if (v0 != 0) {
                                    // 0x004a4bdc
                                    charge(ctx, 1);
                                    for (;;) {
                                        // 0x004a4be0
                                        charge(ctx, 29);
                                        t2 = addu(t6, a3);
                                        lbu(s3, t2, 0);
                                        v0 = addu(t7, a3);
                                        lbu(v0, v0, 0);
                                        t2 = addu(t5, a3);
                                        lbu(t3, t2, 0);
                                        v0 = sllv(t9, v0);
                                        s4 = sll(v0, 1);
                                        a3 = sll(a3, 1);
                                        v0 = sllv(t9, s3);
                                        a3 = srlv(s0, a3);
                                        s3 = addu(t4, s4);
                                        a3 = a3 & 0x3;
                                        t9 = addu(t9, t3);
                                        t2 = a2;
                                        lhu(t3, s3, 0);
                                        a2 = addiu(a2, -1);
                                        v0 = addu(v0, t3);
                                        v0 = sll(v0, 2);
                                        t3 = addu(v1, v0);
                                        lb(v0, t3, 0);
                                        sb(v0, t0, 0);
                                        lb(v0, t3, 1);
                                        sb(v0, t0, 1);
                                        lb(v0, t3, 2);
                                        sb(v0, t0, 2);
                                        sb(zero, t0, 3);
                                        t0 = addiu(t0, 4);
                                        if (t2 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004a4c54
                                    charge(ctx, 2);
                                }
                            } else {
                                // 0x004a4b4c
                                charge(ctx, 3);
                                v0 = a2;
                                a2 = addiu(a2, -1);
                                if (v0 != 0) {
                                    for (;;) {
                                        // 0x004a4b58
                                        charge(ctx, 28);
                                        t2 = addu(t6, a3);
                                        lbu(s3, t2, 0);
                                        v0 = addu(t7, a3);
                                        lbu(v0, v0, 0);
                                        t2 = addu(t5, a3);
                                        lbu(t3, t2, 0);
                                        v0 = sllv(t9, v0);
                                        s4 = sll(v0, 1);
                                        a3 = sll(a3, 1);
                                        v0 = sllv(t9, s3);
                                        a3 = srlv(s0, a3);
                                        s3 = addu(t4, s4);
                                        a3 = a3 & 0x3;
                                        t9 = addu(t9, t3);
                                        t2 = a2;
                                        lhu(t3, s3, 0);
                                        a2 = addiu(a2, -1);
                                        v0 = addu(v0, t3);
                                        v0 = sll(v0, 2);
                                        t3 = addu(v1, v0);
                                        lb(v0, t3, 0);
                                        sb(v0, t0, 0);
                                        lb(v0, t3, 1);
                                        sb(v0, t0, 1);
                                        lb(v0, t3, 2);
                                        sb(v0, t0, 2);
                                        t0 = addiu(t0, 3);
                                        if (t2 == 0) {
                                            break;
                                        }
                                        backedge(ctx);
                                    }
                                    // 0x004a4bc8
                                    charge(ctx, 2);
                                }
                            }
                        }
                        // 0x004a4cd8
                        charge(ctx, 6);
                        lh(v0, a1, strm(5, ps2all_stream::kStride));
                        t9 = subu(t9, t8);
                        v0 = sll(v0, 4);
                        t1 = addu(t1, v0);
                        t0 = t1;
                        if (i64(s1) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
        }
    }
    // 0x004a4cf0: return 1
    charge(ctx, 2);
    v0 = 1;
    // 0x004a4d18
    charge(ctx, 11);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x004A1430 ps2AllAtomicInstance -- 4196 bytes; frame 0xB0: fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// ps2AllAtomicInstance [atomic instance] (pipe data $a0): the atomic's geometry streams (atomic = pd +8, geometry = atomic +24)
// into the resEntry's clusters (walk tables 0x7BCAxx, the identity table 0x7BCAC0, the overlap $t2 2 / 1 / 0, as
// ps2AllSectorInstance). The morph targets (geometry +92, 28 bytes each: +20 vertices, +24 normals) of the interpolation record
// (atomic +76: +4 start, +6 end); a geometry with two or more targets (+24) takes each stream's second count / offset /
// stride (+4 / +2 beside the first). Streams (their material pipeline flags at matPvt +32 + 8 k: bit 0 and not bit 3):
// positions 12 bytes (pd +52 bit 4), positions 16 bytes with w = 0, normals x 127 as 3 or 4 signed bytes (bit 5; zero
// when the geometry has no normals (flag 0x10); 3 bytes when the stream has 0x2000); the resEntry +36 / +40 / +44 =
// start, end, target count; with two targets the end target's positions (+396..) and normals (+420.., stream flags +120);
// then UVs 8 bytes (+52, pd +52 bits 7..8 and geometry flags 0x84), two UV sets 16 bytes (+52 and +56 with flag 0x80) and
// colours (+48 prelit with flag 8, else 0xFF000000). Returns 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: frame/spills (own frame)).
void ps2AllAtomicInstance(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::cvt_w_s, hg::enter, hg::i64, hg::lbu,
          hg::lh, hg::lhu, hg::lq, hg::lui, hg::lw, hg::lwc1, hg::mfc1, hg::mtc1, hg::mul_s, hg::sb, hg::sll,
          hg::sllv, hg::slt, hg::slti, hg::sq, hg::srlv, hg::subu, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, fp{ctx, 30};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x004a1430
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(a2, a0, ps2all_pd::kObject);  // a2 = the atomic
    lw(a1, a0, ps2all_pd::kResEntrySlot);  // the resEntry slot
    lw(v1, a0, ps2all_pd::kMeshHeader);  // the mesh header
    lw(s2, a2, rw_atomic::kGeometry);  // s2 = the geometry
    v0 = addiu(a2, rw_atomic::kInterp);  // v0 = the interpolation record
    lw(a1, a1, 0);  // a1 = the resEntry
    lw(a2, v1, mesh_hdr::kFlags);  // a2 = the mesh header flags
    lw(s0, a1, res_entry::kVertexCount);  // s0 = the vertices to instance
    v1 = a2 & 0x2;  // a fan?
    s1 = addiu(a1, res_entry::kHeader);  // s1 = the instance header
    if (v1 == 0) {
        // 0x004a14b0: strips / lists: the walk's slot pattern (t6), start slot (t4) and index columns (t1, t0, a3)
        charge(ctx, 10);
        a1 = hi(kWalkAtomic + walk::kListPattern);
        v1 = hi(kWalkAtomic + walk::kListStart);
        lbu(t6, a1, lo(kWalkAtomic + walk::kListPattern));
        t1 = hi(kWalkAtomic + walk::kListCol0);
        lbu(t4, v1, lo(kWalkAtomic + walk::kListStart));
        t0 = hi(kWalkAtomic + walk::kListCol1);
        a3 = hi(kWalkAtomic + walk::kListCol2);
        t1 = addiu(t1, lo(kWalkAtomic + walk::kListCol0));
        t0 = addiu(t0, lo(kWalkAtomic + walk::kListCol1));
        a3 = addiu(a3, lo(kWalkAtomic + walk::kListCol2));
    } else {
        // 0x004a1484: a fan: its pattern, start slot and columns
        charge(ctx, 11);
        a1 = hi(kWalkAtomic + walk::kFanPattern);
        v1 = hi(kWalkAtomic + walk::kFanStart);
        lbu(t6, a1, lo(kWalkAtomic + walk::kFanPattern));
        t1 = hi(kWalkAtomic + walk::kFanCol0);
        lbu(t4, v1, lo(kWalkAtomic + walk::kFanStart));
        t0 = hi(kWalkAtomic + walk::kFanCol1);
        a3 = hi(kWalkAtomic + walk::kFanCol2);
        t1 = addiu(t1, lo(kWalkAtomic + walk::kFanCol0));
        t0 = addiu(t0, lo(kWalkAtomic + walk::kFanCol1));
        a3 = addiu(a3, lo(kWalkAtomic + walk::kFanCol2));
    }
    // 0x004a14d8: the overlap t2 each cluster after the first re-sends: 2 for a strip, 1 for a polyline, else 0
    charge(ctx, 3);
    v1 = a2 & 0x1;
    if (v1 != 0) {
        // 0x004a2058
        charge(ctx, 2);
        t2 = 2;
        backedge(ctx);
    } else {
        // 0x004a14e4
        charge(ctx, 3);
        v1 = a2 & 0x8;
        if (v1 == 0) {
            // 0x004a14f8
            charge(ctx, 1);
            t2 = 0;
        } else {
            // 0x004a14f0
            charge(ctx, 2);
            t2 = 1;
        }
    }
    // 0x004a14fc: the index table a2: the identity table (no indices) or the mesh's indices (columns t1 / t0 swapped)
    charge(ctx, 3);
    v1 = a2 & 0x100;
    if (v1 != 0) {
        // 0x004a1520
        charge(ctx, 2);
        a2 = hi(kWalkAtomic + walk::kIdentity);
        a2 = addiu(a2, lo(kWalkAtomic + walk::kIdentity));
    } else {
        // 0x004a1508
        charge(ctx, 6);
        lw(v1, a0, ps2all_pd::kMesh);
        a1 = t1;
        t1 = t0;
        lw(a2, v1, 0);  // the mesh's indices
        t0 = a1;
    }
    // 0x004a1528: the streams to write: sp+0xA0 = positions (stream 0), t7 = positions with w (1), fp = normals (5);
    // each
    // when the instance flags ask (bit 4 / bit 5) and its stream flags have bit 0 and not bit 3
    charge(ctx, 4);
    lw(v1, a0, ps2all_pd::kInstFlags);
    t5 = v1 & 0x10;
    sw(zero, sp, 0xA0);
    if (t5 != 0) {
        // 0x004a1538
        charge(ctx, 5);
        lw(a1, a0, ps2all_pd::kMatPvt);
        lw(t3, a1, sflags(0));
        a1 = t3 & 0x1;
        if (a1 != 0) {
            // 0x004a154c
            charge(ctx, 3);
            a1 = t3 & 0x8;
            if (a1 == 0) {
                // 0x004a1558
                charge(ctx, 2);
                a1 = 1;
                sw(a1, sp, 0xA0);
            }
        }
    }
    // 0x004a1560
    charge(ctx, 2);
    t7 = 0;
    if (t5 != 0) {
        // 0x004a1568
        charge(ctx, 5);
        lw(a1, a0, ps2all_pd::kMatPvt);
        lw(t3, a1, sflags(1));
        a1 = t3 & 0x1;
        if (a1 != 0) {
            // 0x004a157c
            charge(ctx, 3);
            a1 = t3 & 0x8;
            if (a1 == 0) {
                // 0x004a1588
                charge(ctx, 1);
                t7 = 1;
            }
        }
    }
    // 0x004a158c
    charge(ctx, 3);
    v1 = v1 & 0x20;
    fp = 0;
    if (v1 != 0) {
        // 0x004a1598
        charge(ctx, 5);
        lw(v1, a0, ps2all_pd::kMatPvt);
        lw(a1, v1, sflags(5));
        v1 = a1 & 0x1;
        if (v1 != 0) {
            // 0x004a15ac
            charge(ctx, 3);
            v1 = a1 & 0x8;
            if (v1 == 0) {
                // 0x004a15b8
                charge(ctx, 1);
                fp = 0x1;
            }
        }
    }
    // 0x004a15bc: sp+0x90 = the start morph target (geometry->morph targets + 28 * start)
    charge(ctx, 10);
    lh(t3, v0, rw_atomic::kInterpStart);
    lw(v1, s2, rw_geometry::kMorphTargets);
    a1 = sll(t3, 3);
    a1 = subu(a1, t3);
    a1 = sll(a1, 2);
    v1 = addu(v1, a1);
    sw(v1, sp, 0x90);
    lw(v1, sp, 0xA0);
    if (v1 != 0) {
        // 0x004a15e4: stream 0: positions, 12 bytes per vertex; a1 = v1 = the destination (the data + the stream's
        // offset)
        charge(ctx, 9);
        lw(v1, sp, 0x90);
        lw(s3, s2, rw_geometry::kMorphCount);
        lw(t3, s1, ps2all_hdr::kData);
        lw(s7, v1, rw_morph::kVertices);  // s7 = the target's positions
        at = slti(s3, 2);
        lw(v1, s1, strm(0, ps2all_stream::kOffset));
        v1 = sll(v1, 4);
        a1 = addu(t3, v1);
        if (at == 0) {
            // 0x004a1608
            charge(ctx, 3);
            lw(v1, s1, strm(0, ps2all_stream::kOffset2));
            v1 = sll(v1, 4);
            a1 = addu(t3, v1);
        }
        // 0x004a1614
        charge(ctx, 5);
        v1 = a1;
        t3 = 0;
        t5 = t4;
        t9 = s0;
        if (i64(s0) > 0) {
            for (;;) {
                // 0x004a1628: per cluster: a full one takes the stream's count (the overlap re-sent), the last one the
                // rest
                // with the destination moved back by the back-step
                charge(ctx, 4);
                lw(s4, s1, ps2all_hdr::kClusterVerts);
                at = slt(s4, t9);
                if (at != 0) {
                    // 0x004a1658
                    charge(ctx, 3);
                    at = slti(s3, 2);
                    lw(t8, s1, strm(0, ps2all_stream::kCount));
                    if (at == 0) {
                        // 0x004a1664
                        charge(ctx, 1);
                        lw(t8, s1, strm(0, ps2all_stream::kCount2));
                    }
                    // 0x004a1668
                    charge(ctx, 2);
                    s3 = subu(t8, t2);
                    t9 = subu(t9, s3);
                } else {
                    // 0x004a1638
                    charge(ctx, 7);
                    lh(v1, s1, strm(0, ps2all_stream::kLastBack));
                    t8 = t9;
                    t9 = 0;
                    v1 = sll(v1, 4);
                    a1 = subu(a1, v1);
                    v1 = a1;
                }
                // 0x004a1670
                charge(ctx, 3);
                s3 = t8;
                t8 = addiu(t8, -1);
                if (s3 == 0) {
                    // 0x004a2060
                    charge(ctx, 1);
                    lw(s3, s2, rw_geometry::kMorphCount);
                } else {
                    // 0x004a167c
                    charge(ctx, 1);
                    for (;;) {
                        // 0x004a1680: per vertex: the walk gives the vertex index (s4); copy its position
                        charge(ctx, 31);
                        s3 = addu(t1, t3);
                        lbu(s6, s3, 0);
                        s3 = addu(t0, t3);
                        s6 = sllv(t5, s6);
                        lbu(s5, s3, 0);
                        s6 = sll(s6, 1);
                        s6 = addu(a2, s6);
                        s3 = addu(a3, t3);
                        s5 = sllv(t5, s5);
                        lbu(s4, s3, 0);
                        t3 = sll(t3, 1);
                        t3 = srlv(t6, t3);
                        t3 = t3 & 0x3;
                        t5 = addu(t5, s4);
                        s3 = t8;
                        lhu(s4, s6, 0);
                        t8 = addiu(t8, -1);
                        s4 = addu(s5, s4);
                        s5 = s4 & 0xFFFF;
                        s4 = sll(s5, 1);
                        s4 = addu(s4, s5);
                        s4 = sll(s4, 2);
                        s4 = addu(s7, s4);
                        lwc1(f0, s4, 0);
                        swc1(f0, v1, 0);
                        lwc1(f0, s4, 4);
                        swc1(f0, v1, 4);
                        lwc1(f0, s4, 8);
                        swc1(f0, v1, 8);
                        v1 = addiu(v1, 12);
                        if (s3 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004a16fc
                    charge(ctx, 2);
                    lw(s3, s2, rw_geometry::kMorphCount);
                }
                // 0x004a2064: the next cluster: back by the overlap in the walk, on by the stream's cluster stride
                charge(ctx, 4);
                lh(v1, s1, strm(0, ps2all_stream::kStride));
                at = slti(s3, 2);
                t5 = subu(t5, t2);
                if (at == 0) {
                    // 0x004a2074
                    charge(ctx, 1);
                    lh(v1, s1, strm(0, ps2all_stream::kStride2));
                }
                // 0x004a2078
                charge(ctx, 4);
                v1 = sll(v1, 4);
                a1 = addu(a1, v1);
                v1 = a1;
                if (i64(t9) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004a2088
            charge(ctx, 2);
            backedge(ctx);
        }
    }
    // 0x004a1708
    charge(ctx, 2);
    if (t7 != 0) {
        // 0x004a1710: stream 1: positions, 16 bytes per vertex (w = 0)
        charge(ctx, 9);
        lw(v1, sp, 0x90);
        lw(a1, s1, strm(1, ps2all_stream::kOffset));
        lw(s5, s2, rw_geometry::kMorphCount);
        lw(t3, s1, ps2all_hdr::kData);
        lw(v1, v1, 20);
        a1 = sll(a1, 4);
        at = slti(s5, 2);
        s4 = addu(t3, a1);
        if (at == 0) {
            // 0x004a1734
            charge(ctx, 3);
            lw(a1, s1, strm(1, ps2all_stream::kOffset2));
            a1 = sll(a1, 4);
            s4 = addu(t3, a1);
        }
        // 0x004a1740
        charge(ctx, 5);
        s3 = s4;
        t5 = 0;
        t7 = t4;
        t3 = s0;
        if (i64(s0) > 0) {
            for (;;) {
                // 0x004a1754
                charge(ctx, 4);
                lw(a1, s1, ps2all_hdr::kClusterVerts);
                at = slt(a1, t3);
                if (at != 0) {
                    // 0x004a1780
                    charge(ctx, 3);
                    at = slti(s5, 2);
                    lw(a1, s1, strm(1, ps2all_stream::kCount));
                    if (at == 0) {
                        // 0x004a178c
                        charge(ctx, 1);
                        lw(a1, s1, strm(1, ps2all_stream::kCount2));
                    }
                    // 0x004a1790
                    charge(ctx, 2);
                    s5 = subu(a1, t2);
                    t3 = subu(t3, s5);
                } else {
                    // 0x004a1764
                    charge(ctx, 7);
                    lh(s3, s1, strm(1, ps2all_stream::kLastBack));
                    a1 = t3;
                    t3 = 0;
                    s3 = sll(s3, 4);
                    s4 = subu(s4, s3);
                    s3 = s4;
                }
                // 0x004a1798
                charge(ctx, 3);
                s5 = a1;
                a1 = addiu(a1, -1);
                if (s5 == 0) {
                    // 0x004a2090
                    charge(ctx, 1);
                    lw(s5, s2, rw_geometry::kMorphCount);
                } else {
                    // 0x004a17a4
                    charge(ctx, 1);
                    for (;;) {
                        // 0x004a17a8: per vertex: the position and w = 0
                        charge(ctx, 32);
                        s5 = addu(t1, t5);
                        lbu(t8, s5, 0);
                        s5 = addu(t0, t5);
                        t8 = sllv(t7, t8);
                        lbu(s7, s5, 0);
                        t8 = sll(t8, 1);
                        t8 = addu(a2, t8);
                        s5 = addu(a3, t5);
                        s7 = sllv(t7, s7);
                        lbu(s6, s5, 0);
                        t5 = sll(t5, 1);
                        t5 = srlv(t6, t5);
                        t5 = t5 & 0x3;
                        t7 = addu(t7, s6);
                        s5 = a1;
                        lhu(s6, t8, 0);
                        a1 = addiu(a1, -1);
                        s6 = addu(s7, s6);
                        s7 = s6 & 0xFFFF;
                        s6 = sll(s7, 1);
                        s6 = addu(s6, s7);
                        s6 = sll(s6, 2);
                        s6 = addu(v1, s6);
                        lwc1(f0, s6, 0);
                        swc1(f0, s3, 0);
                        lwc1(f0, s6, 4);
                        swc1(f0, s3, 4);
                        lwc1(f0, s6, 8);
                        swc1(f0, s3, 8);
                        sw(zero, s3, 12);
                        s3 = addiu(s3, 16);
                        if (s5 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                    // 0x004a1828
                    charge(ctx, 2);
                    lw(s5, s2, rw_geometry::kMorphCount);
                }
                // 0x004a2094
                charge(ctx, 4);
                lh(a1, s1, strm(1, ps2all_stream::kStride));
                at = slti(s5, 2);
                t7 = subu(t7, t2);
                if (at == 0) {
                    // 0x004a20a4
                    charge(ctx, 1);
                    lh(a1, s1, strm(1, ps2all_stream::kStride2));
                }
                // 0x004a20a8
                charge(ctx, 4);
                a1 = sll(a1, 4);
                s4 = addu(s4, a1);
                s3 = s4;
                if (i64(t3) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004a20b8
            charge(ctx, 2);
            backedge(ctx);
        }
    }
    // 0x004a1830
    charge(ctx, 2);
    if (fp != 0) {
        // 0x004a1838: stream 5: the normals x 127 as signed bytes (zero without normals; 3 bytes per vertex when the
        // stream has
        // 0x2000, else 4)
        charge(ctx, 9);
        lw(v1, sp, 0x90);
        lw(a1, s1, strm(5, ps2all_stream::kOffset));
        lw(s5, s2, rw_geometry::kMorphCount);
        lw(t3, s1, ps2all_hdr::kData);
        lw(v1, v1, 24);
        a1 = sll(a1, 4);
        at = slti(s5, 2);
        s4 = addu(t3, a1);
        if (at == 0) {
            // 0x004a185c
            charge(ctx, 3);
            lw(a1, s1, strm(5, ps2all_stream::kOffset2));
            a1 = sll(a1, 4);
            s4 = addu(t3, a1);
        }
        // 0x004a1868
        charge(ctx, 5);
        s3 = s4;
        t5 = 0;
        t7 = t4;
        t3 = s0;
        if (i64(s0) > 0) {
            // 0x004a187c
            charge(ctx, 2);
            a1 = flt(127.0f);
            mtc1(a1, f1);
            for (;;) {
                // 0x004a1884
                charge(ctx, 4);
                lw(a1, s1, ps2all_hdr::kClusterVerts);
                at = slt(a1, t3);
                if (at != 0) {
                    // 0x004a18b0
                    charge(ctx, 3);
                    at = slti(s5, 2);
                    lw(a1, s1, strm(5, ps2all_stream::kCount));
                    if (at == 0) {
                        // 0x004a18bc
                        charge(ctx, 1);
                        lw(a1, s1, strm(5, ps2all_stream::kCount2));
                    }
                    // 0x004a18c0
                    charge(ctx, 2);
                    s5 = subu(a1, t2);
                    t3 = subu(t3, s5);
                } else {
                    // 0x004a1894
                    charge(ctx, 7);
                    lh(s3, s1, strm(5, ps2all_stream::kLastBack));
                    a1 = t3;
                    t3 = 0;
                    s3 = sll(s3, 4);
                    s4 = subu(s4, s3);
                    s3 = s4;
                }
                // 0x004a18c8
                charge(ctx, 4);
                lw(s5, s2, rw_geometry::kFlags);
                s5 = s5 & 0x10;
                if (s5 == 0) {
                    // 0x004a1a70
                    charge(ctx, 5);
                    lw(s5, a0, ps2all_pd::kMatPvt);
                    lw(s5, s5, sflags(5));
                    s5 = s5 & 0x2000;
                    if (s5 == 0) {
                        // 0x004a1ab8
                        charge(ctx, 3);
                        s5 = a1;
                        a1 = addiu(a1, -1);
                        if (s5 != 0) {
                            // 0x004a1ac4
                            charge(ctx, 1);
                            for (;;) {
                                // 0x004a1ac8
                                charge(ctx, 8);
                                sb(zero, s3, 0);
                                sb(zero, s3, 1);
                                s5 = a1;
                                sb(zero, s3, 2);
                                a1 = addiu(a1, -1);
                                sb(zero, s3, 3);
                                s3 = addiu(s3, 4);
                                if (s5 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                        }
                    } else {
                        // 0x004a1a84
                        charge(ctx, 3);
                        s5 = a1;
                        a1 = addiu(a1, -1);
                        if (s5 != 0) {
                            for (;;) {
                                // 0x004a1a90
                                charge(ctx, 7);
                                sb(zero, s3, 0);
                                sb(zero, s3, 1);
                                s5 = a1;
                                sb(zero, s3, 2);
                                a1 = addiu(a1, -1);
                                s3 = addiu(s3, 3);
                                if (s5 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004a1aac
                            charge(ctx, 2);
                        }
                    }
                } else {
                    // 0x004a18d8
                    charge(ctx, 5);
                    lw(s5, a0, ps2all_pd::kMatPvt);
                    lw(s5, s5, sflags(5));
                    s5 = s5 & 0x2000;
                    if (s5 == 0) {
                        // 0x004a19a8
                        charge(ctx, 3);
                        s5 = a1;
                        a1 = addiu(a1, -1);
                        if (s5 != 0) {
                            // 0x004a19b4
                            charge(ctx, 1);
                            for (;;) {
                                // 0x004a19b8
                                charge(ctx, 43);
                                s5 = addu(t1, t5);
                                lbu(t8, s5, 0);
                                s5 = addu(t0, t5);
                                t8 = sllv(t7, t8);
                                lbu(s7, s5, 0);
                                t8 = sll(t8, 1);
                                t8 = addu(a2, t8);
                                s5 = addu(a3, t5);
                                s7 = sllv(t7, s7);
                                lbu(s6, s5, 0);
                                t5 = sll(t5, 1);
                                t5 = srlv(t6, t5);
                                t5 = t5 & 0x3;
                                t7 = addu(t7, s6);
                                s5 = a1;
                                lhu(s6, t8, 0);
                                a1 = addiu(a1, -1);
                                s7 = addu(s7, s6);
                                s6 = sll(s7, 1);
                                s6 = addu(s6, s7);
                                s6 = sll(s6, 2);
                                s6 = addu(v1, s6);
                                lwc1(f0, s6, 0);
                                mul_s(f0, f1, f0);
                                cvt_w_s(f0, f0);
                                mfc1(s7, f0);
                                sb(s7, s3, 0);
                                lwc1(f0, s6, 4);
                                mul_s(f0, f1, f0);
                                cvt_w_s(f0, f0);
                                mfc1(s7, f0);
                                sb(s7, s3, 1);
                                lwc1(f0, s6, 8);
                                mul_s(f0, f1, f0);
                                cvt_w_s(f0, f0);
                                mfc1(s6, f0);
                                sb(s6, s3, 2);
                                sb(zero, s3, 3);
                                s3 = addiu(s3, 4);
                                if (s5 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004a1a64
                            charge(ctx, 2);
                        }
                    } else {
                        // 0x004a18ec
                        charge(ctx, 3);
                        s5 = a1;
                        a1 = addiu(a1, -1);
                        if (s5 != 0) {
                            for (;;) {
                                // 0x004a18f8
                                charge(ctx, 42);
                                s5 = addu(t1, t5);
                                lbu(t8, s5, 0);
                                s5 = addu(t0, t5);
                                t8 = sllv(t7, t8);
                                lbu(s7, s5, 0);
                                t8 = sll(t8, 1);
                                t8 = addu(a2, t8);
                                s5 = addu(a3, t5);
                                s7 = sllv(t7, s7);
                                lbu(s6, s5, 0);
                                t5 = sll(t5, 1);
                                t5 = srlv(t6, t5);
                                t5 = t5 & 0x3;
                                t7 = addu(t7, s6);
                                s5 = a1;
                                lhu(s6, t8, 0);
                                a1 = addiu(a1, -1);
                                s7 = addu(s7, s6);
                                s6 = sll(s7, 1);
                                s6 = addu(s6, s7);
                                s6 = sll(s6, 2);
                                s6 = addu(v1, s6);
                                lwc1(f0, s6, 0);
                                mul_s(f0, f1, f0);
                                cvt_w_s(f0, f0);
                                mfc1(s7, f0);
                                sb(s7, s3, 0);
                                lwc1(f0, s6, 4);
                                mul_s(f0, f1, f0);
                                cvt_w_s(f0, f0);
                                mfc1(s7, f0);
                                sb(s7, s3, 1);
                                lwc1(f0, s6, 8);
                                mul_s(f0, f1, f0);
                                cvt_w_s(f0, f0);
                                mfc1(s6, f0);
                                sb(s6, s3, 2);
                                s3 = addiu(s3, 3);
                                if (s5 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004a19a0
                            charge(ctx, 2);
                        }
                    }
                }
                // 0x004a1ae8
                charge(ctx, 5);
                lw(s5, s2, rw_geometry::kMorphCount);
                lh(a1, s1, strm(5, ps2all_stream::kStride));
                at = slti(s5, 2);
                t7 = subu(t7, t2);
                if (at == 0) {
                    // 0x004a1afc
                    charge(ctx, 1);
                    lh(a1, s1, strm(5, ps2all_stream::kStride2));
                }
                // 0x004a1b00
                charge(ctx, 4);
                a1 = sll(a1, 4);
                s4 = addu(s4, a1);
                s3 = s4;
                if (i64(t3) <= 0) {
                    break;
                }
                backedge(ctx);
            }
        }
    }
    // 0x004a1b10: with two or more morph targets: the end target's positions (stream 10) and normals (stream 11)
    charge(ctx, 10);
    lh(v1, v0, rw_atomic::kInterpStart);
    sw(v1, s1, 36);
    lh(v1, v0, rw_atomic::kInterpEnd);
    sw(v1, s1, 40);
    lw(v1, s2, rw_geometry::kMorphCount);
    sw(v1, s1, 44);
    lw(v1, s2, rw_geometry::kMorphCount);
    at = slti(v1, 2);
    if (at == 0) {
        // 0x004a1b38
        charge(ctx, 9);
        lh(a1, v0, rw_atomic::kInterpEnd);
        lw(v0, s2, rw_geometry::kMorphTargets);
        v1 = sll(a1, 3);
        v1 = subu(v1, a1);
        v1 = sll(v1, 2);
        t8 = addu(v0, v1);
        lw(v0, sp, 0xA0);
        if (v0 != 0) {
            // 0x004a1b5c
            charge(ctx, 10);
            lw(t7, s1, strm(10, ps2all_stream::kOffset2));
            t3 = 0;
            lw(v1, s1, ps2all_hdr::kData);
            t5 = t4;
            lw(v0, t8, 20);
            a1 = s0;
            t7 = sll(t7, 4);
            s3 = addu(v1, t7);
            t7 = s3;
            if (i64(s0) > 0) {
                for (;;) {
                    // 0x004a1b84
                    charge(ctx, 4);
                    lw(v1, s1, ps2all_hdr::kClusterVerts);
                    at = slt(v1, a1);
                    if (at != 0) {
                        // 0x004a1bb0
                        charge(ctx, 4);
                        lw(v1, s1, strm(10, ps2all_stream::kCount2));
                        s4 = subu(v1, t2);
                        a1 = subu(a1, s4);
                    } else {
                        // 0x004a1b94
                        charge(ctx, 7);
                        lh(t7, s1, strm(10, ps2all_stream::kLastBack));
                        v1 = a1;
                        a1 = 0;
                        t7 = sll(t7, 4);
                        s3 = subu(s3, t7);
                        t7 = s3;
                    }
                    // 0x004a1bc0
                    charge(ctx, 3);
                    s4 = v1;
                    v1 = addiu(v1, -1);
                    if (s4 == 0) {
                        // 0x004a20c0
                        charge(ctx, 1);
                        lh(v1, s1, strm(10, ps2all_stream::kStride2));
                    } else {
                        // 0x004a1bcc
                        charge(ctx, 1);
                        for (;;) {
                            // 0x004a1bd0
                            charge(ctx, 31);
                            s4 = addu(t1, t3);
                            lbu(s7, s4, 0);
                            s4 = addu(t0, t3);
                            s7 = sllv(t5, s7);
                            lbu(s6, s4, 0);
                            s7 = sll(s7, 1);
                            s7 = addu(a2, s7);
                            s4 = addu(a3, t3);
                            s6 = sllv(t5, s6);
                            lbu(s5, s4, 0);
                            t3 = sll(t3, 1);
                            t3 = srlv(t6, t3);
                            t3 = t3 & 0x3;
                            t5 = addu(t5, s5);
                            s4 = v1;
                            lhu(s5, s7, 0);
                            v1 = addiu(v1, -1);
                            s5 = addu(s6, s5);
                            s6 = s5 & 0xFFFF;
                            s5 = sll(s6, 1);
                            s5 = addu(s5, s6);
                            s5 = sll(s5, 2);
                            s5 = addu(v0, s5);
                            lwc1(f0, s5, 0);
                            swc1(f0, t7, 0);
                            lwc1(f0, s5, 4);
                            swc1(f0, t7, 4);
                            lwc1(f0, s5, 8);
                            swc1(f0, t7, 8);
                            t7 = addiu(t7, 12);
                            if (s4 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004a1c4c
                        charge(ctx, 2);
                        lh(v1, s1, strm(10, ps2all_stream::kStride2));
                    }
                    // 0x004a20c4
                    charge(ctx, 5);
                    t5 = subu(t5, t2);
                    v1 = sll(v1, 4);
                    s3 = addu(s3, v1);
                    t7 = s3;
                    if (i64(a1) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004a20d8
                charge(ctx, 2);
                backedge(ctx);
            }
        }
        // 0x004a1c58
        charge(ctx, 2);
        if (fp != 0) {
            // 0x004a1c60
            charge(ctx, 10);
            lw(t7, s1, strm(11, ps2all_stream::kOffset2));
            t3 = 0;
            lw(v1, s1, ps2all_hdr::kData);
            t5 = t4;
            lw(v0, t8, 24);
            a1 = s0;
            t7 = sll(t7, 4);
            s3 = addu(v1, t7);
            t7 = s3;
            if (i64(s0) > 0) {
                // 0x004a1c88
                charge(ctx, 2);
                v1 = flt(127.0f);
                mtc1(v1, f1);
                for (;;) {
                    // 0x004a1c90
                    charge(ctx, 4);
                    lw(v1, s1, ps2all_hdr::kClusterVerts);
                    at = slt(v1, a1);
                    if (at != 0) {
                        // 0x004a1cc0
                        charge(ctx, 4);
                        lw(v1, s1, strm(11, ps2all_stream::kCount2));
                        s4 = subu(v1, t2);
                        a1 = subu(a1, s4);
                    } else {
                        // 0x004a1ca0
                        charge(ctx, 7);
                        lh(t7, s1, strm(11, ps2all_stream::kLastBack));
                        v1 = a1;
                        a1 = 0;
                        t7 = sll(t7, 4);
                        s3 = subu(s3, t7);
                        t7 = s3;
                    }
                    // 0x004a1cd0
                    charge(ctx, 4);
                    lw(s4, s2, rw_geometry::kFlags);
                    s4 = s4 & 0x10;
                    if (s4 == 0) {
                        // 0x004a1e78
                        charge(ctx, 5);
                        lw(s4, a0, ps2all_pd::kMatPvt);
                        lw(s4, s4, sflags(11));
                        s4 = s4 & 0x2000;
                        if (s4 == 0) {
                            // 0x004a1ec0
                            charge(ctx, 3);
                            s4 = v1;
                            v1 = addiu(v1, -1);
                            if (s4 != 0) {
                                // 0x004a1ecc
                                charge(ctx, 1);
                                for (;;) {
                                    // 0x004a1ed0
                                    charge(ctx, 8);
                                    sb(zero, t7, 0);
                                    sb(zero, t7, 1);
                                    s4 = v1;
                                    sb(zero, t7, 2);
                                    v1 = addiu(v1, -1);
                                    sb(zero, t7, 3);
                                    t7 = addiu(t7, 4);
                                    if (s4 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                            }
                        } else {
                            // 0x004a1e8c
                            charge(ctx, 3);
                            s4 = v1;
                            v1 = addiu(v1, -1);
                            if (s4 != 0) {
                                for (;;) {
                                    // 0x004a1e98
                                    charge(ctx, 7);
                                    sb(zero, t7, 0);
                                    sb(zero, t7, 1);
                                    s4 = v1;
                                    sb(zero, t7, 2);
                                    v1 = addiu(v1, -1);
                                    t7 = addiu(t7, 3);
                                    if (s4 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004a1eb4
                                charge(ctx, 2);
                            }
                        }
                    } else {
                        // 0x004a1ce0
                        charge(ctx, 5);
                        lw(s4, a0, ps2all_pd::kMatPvt);
                        lw(s4, s4, sflags(11));
                        s4 = s4 & 0x2000;
                        if (s4 == 0) {
                            // 0x004a1db0
                            charge(ctx, 3);
                            s4 = v1;
                            v1 = addiu(v1, -1);
                            if (s4 != 0) {
                                // 0x004a1dbc
                                charge(ctx, 1);
                                for (;;) {
                                    // 0x004a1dc0
                                    charge(ctx, 43);
                                    s4 = addu(t1, t3);
                                    lbu(s6, s4, 0);
                                    s7 = v1;
                                    v1 = addiu(v1, -1);
                                    s4 = addu(t0, t3);
                                    s6 = sllv(t5, s6);
                                    lbu(s5, s4, 0);
                                    s6 = sll(s6, 1);
                                    s6 = addu(a2, s6);
                                    s4 = addu(a3, t3);
                                    s5 = sllv(t5, s5);
                                    lbu(s4, s4, 0);
                                    t3 = sll(t3, 1);
                                    t3 = srlv(t6, t3);
                                    t3 = t3 & 0x3;
                                    t5 = addu(t5, s4);
                                    lhu(s4, s6, 0);
                                    s5 = addu(s5, s4);
                                    s4 = sll(s5, 1);
                                    s4 = addu(s4, s5);
                                    s4 = sll(s4, 2);
                                    s5 = addu(v0, s4);
                                    lwc1(f0, s5, 0);
                                    mul_s(f0, f1, f0);
                                    cvt_w_s(f0, f0);
                                    mfc1(s4, f0);
                                    sb(s4, t7, 0);
                                    lwc1(f0, s5, 4);
                                    mul_s(f0, f1, f0);
                                    cvt_w_s(f0, f0);
                                    mfc1(s4, f0);
                                    sb(s4, t7, 1);
                                    lwc1(f0, s5, 8);
                                    mul_s(f0, f1, f0);
                                    cvt_w_s(f0, f0);
                                    mfc1(s4, f0);
                                    sb(s4, t7, 2);
                                    sb(zero, t7, 3);
                                    t7 = addiu(t7, 4);
                                    if (s7 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004a1e6c
                                charge(ctx, 2);
                            }
                        } else {
                            // 0x004a1cf4
                            charge(ctx, 3);
                            s4 = v1;
                            v1 = addiu(v1, -1);
                            if (s4 != 0) {
                                for (;;) {
                                    // 0x004a1d00
                                    charge(ctx, 42);
                                    s4 = addu(t1, t3);
                                    lbu(s6, s4, 0);
                                    s7 = v1;
                                    v1 = addiu(v1, -1);
                                    s4 = addu(t0, t3);
                                    s6 = sllv(t5, s6);
                                    lbu(s5, s4, 0);
                                    s6 = sll(s6, 1);
                                    s6 = addu(a2, s6);
                                    s4 = addu(a3, t3);
                                    s5 = sllv(t5, s5);
                                    lbu(s4, s4, 0);
                                    t3 = sll(t3, 1);
                                    t3 = srlv(t6, t3);
                                    t3 = t3 & 0x3;
                                    t5 = addu(t5, s4);
                                    lhu(s4, s6, 0);
                                    s5 = addu(s5, s4);
                                    s4 = sll(s5, 1);
                                    s4 = addu(s4, s5);
                                    s4 = sll(s4, 2);
                                    s5 = addu(v0, s4);
                                    lwc1(f0, s5, 0);
                                    mul_s(f0, f1, f0);
                                    cvt_w_s(f0, f0);
                                    mfc1(s4, f0);
                                    sb(s4, t7, 0);
                                    lwc1(f0, s5, 4);
                                    mul_s(f0, f1, f0);
                                    cvt_w_s(f0, f0);
                                    mfc1(s4, f0);
                                    sb(s4, t7, 1);
                                    lwc1(f0, s5, 8);
                                    mul_s(f0, f1, f0);
                                    cvt_w_s(f0, f0);
                                    mfc1(s4, f0);
                                    sb(s4, t7, 2);
                                    t7 = addiu(t7, 3);
                                    if (s7 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004a1da8
                                charge(ctx, 2);
                            }
                        }
                    }
                    // 0x004a1ef0
                    charge(ctx, 6);
                    lh(v1, s1, strm(11, ps2all_stream::kStride2));
                    t5 = subu(t5, t2);
                    v1 = sll(v1, 4);
                    s3 = addu(s3, v1);
                    t7 = s3;
                    if (i64(a1) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
        }
    }
    // 0x004a1f08: stream 2: UVs, 8 bytes per vertex (the geometry's first UV set when its flags have 0x84)
    charge(ctx, 4);
    lw(v0, a0, ps2all_pd::kInstFlags);
    v0 = v0 & 0x180;
    if (v0 != 0) {
        // 0x004a1f18
        charge(ctx, 5);
        lw(v0, a0, ps2all_pd::kMatPvt);
        lw(v1, v0, sflags(2));
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x004a1f2c
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 == 0) {
                // 0x004a1f38
                charge(ctx, 4);
                lw(v0, s2, rw_geometry::kFlags);
                v0 = v0 & 0x84;
                if (v0 != 0) {
                    // 0x004a1f48
                    charge(ctx, 8);
                    lw(v1, s1, strm(2, ps2all_stream::kOffset));
                    lw(v0, s2, rw_geometry::kMorphCount);
                    lw(a1, s1, ps2all_hdr::kData);
                    lw(t3, s2, rw_geometry::kUv0);
                    v1 = sll(v1, 4);
                    at = slti(v0, 2);
                    s6 = addu(a1, v1);
                    if (at == 0) {
                        // 0x004a1f68
                        charge(ctx, 3);
                        lw(v1, s1, strm(2, ps2all_stream::kOffset2));
                        v1 = sll(v1, 4);
                        s6 = addu(a1, v1);
                    }
                    // 0x004a1f74
                    charge(ctx, 5);
                    s5 = s6;
                    s3 = 0;
                    s4 = t4;
                    t7 = s0;
                    if (i64(s0) > 0) {
                        for (;;) {
                            // 0x004a1f88
                            charge(ctx, 4);
                            lw(v1, s1, ps2all_hdr::kClusterVerts);
                            at = slt(v1, t7);
                            if (at != 0) {
                                // 0x004a1fb8
                                charge(ctx, 3);
                                at = slti(v0, 2);
                                lw(t5, s1, strm(2, ps2all_stream::kCount));
                                if (at == 0) {
                                    // 0x004a1fc4
                                    charge(ctx, 1);
                                    lw(t5, s1, strm(2, ps2all_stream::kCount2));
                                }
                                // 0x004a1fc8
                                charge(ctx, 2);
                                v0 = subu(t5, t2);
                                t7 = subu(t7, v0);
                            } else {
                                // 0x004a1f98
                                charge(ctx, 7);
                                lh(v0, s1, strm(2, ps2all_stream::kLastBack));
                                t5 = t7;
                                t7 = 0;
                                v0 = sll(v0, 4);
                                s6 = subu(s6, v0);
                                s5 = s6;
                            }
                            // 0x004a1fd0
                            charge(ctx, 3);
                            v0 = t5;
                            t5 = addiu(t5, -1);
                            if (v0 == 0) {
                                // 0x004a20e0
                                charge(ctx, 1);
                                lw(v0, s2, rw_geometry::kMorphCount);
                            } else {
                                // 0x004a1fdc
                                charge(ctx, 1);
                                for (;;) {
                                    // 0x004a1fe0
                                    charge(ctx, 27);
                                    v0 = addu(t1, s3);
                                    lbu(a1, v0, 0);
                                    s7 = t5;
                                    t5 = addiu(t5, -1);
                                    v0 = addu(t0, s3);
                                    a1 = sllv(s4, a1);
                                    lbu(v1, v0, 0);
                                    a1 = sll(a1, 1);
                                    a1 = addu(a2, a1);
                                    v0 = addu(a3, s3);
                                    v1 = sllv(s4, v1);
                                    lbu(v0, v0, 0);
                                    s3 = sll(s3, 1);
                                    s3 = srlv(t6, s3);
                                    s3 = s3 & 0x3;
                                    s4 = addu(s4, v0);
                                    lhu(v0, a1, 0);
                                    v0 = addu(v1, v0);
                                    v0 = v0 & 0xFFFF;
                                    v0 = sll(v0, 3);
                                    v0 = addu(t3, v0);
                                    lwc1(f0, v0, 0);
                                    swc1(f0, s5, 0);
                                    lwc1(f0, v0, 4);
                                    swc1(f0, s5, 4);
                                    s5 = addiu(s5, 8);
                                    if (s7 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004a204c
                                charge(ctx, 2);
                                lw(v0, s2, rw_geometry::kMorphCount);
                            }
                            // 0x004a20e4
                            charge(ctx, 4);
                            lh(v1, s1, strm(2, ps2all_stream::kStride));
                            at = slti(v0, 2);
                            s4 = subu(s4, t2);
                            if (at == 0) {
                                // 0x004a20f4
                                charge(ctx, 1);
                                lh(v1, s1, strm(2, ps2all_stream::kStride2));
                            }
                            // 0x004a20f8
                            charge(ctx, 4);
                            v1 = sll(v1, 4);
                            s6 = addu(s6, v1);
                            s5 = s6;
                            if (i64(t7) <= 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                }
            }  // stream 3: two UV sets, 16 bytes per vertex (the second set when the geometry has 0x80)
        }
    }
    // 0x004a2108
    charge(ctx, 4);
    lw(v0, a0, ps2all_pd::kInstFlags);
    v0 = v0 & 0x180;
    if (v0 != 0) {
        // 0x004a2118
        charge(ctx, 5);
        lw(v0, a0, ps2all_pd::kMatPvt);
        lw(v1, v0, sflags(3));
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x004a212c
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 == 0) {
                // 0x004a2138
                charge(ctx, 4);
                lw(v1, s2, rw_geometry::kFlags);
                v0 = v1 & 0x84;
                if (v0 != 0) {
                    // 0x004a2148
                    charge(ctx, 3);
                    v0 = v1 & 0x80;
                    lw(v1, s2, rw_geometry::kUv0);
                    if (v0 == 0) {
                        // 0x004a215c
                        charge(ctx, 1);
                        v0 = v1;
                    } else {
                        // 0x004a2154
                        charge(ctx, 2);
                        lw(v0, s2, rw_geometry::kUv1);
                    }
                    // 0x004a2160
                    charge(ctx, 7);
                    lw(a1, s1, strm(3, ps2all_stream::kOffset));
                    lw(s5, s2, rw_geometry::kMorphCount);
                    lw(t3, s1, ps2all_hdr::kData);
                    a1 = sll(a1, 4);
                    at = slti(s5, 2);
                    s4 = addu(t3, a1);
                    if (at == 0) {
                        // 0x004a217c
                        charge(ctx, 3);
                        lw(a1, s1, strm(3, ps2all_stream::kOffset2));
                        a1 = sll(a1, 4);
                        s4 = addu(t3, a1);
                    }
                    // 0x004a2188
                    charge(ctx, 5);
                    s3 = s4;
                    t5 = 0;
                    t7 = t4;
                    t3 = s0;
                    if (i64(s0) > 0) {
                        for (;;) {
                            // 0x004a219c
                            charge(ctx, 4);
                            lw(a1, s1, ps2all_hdr::kClusterVerts);
                            at = slt(a1, t3);
                            if (at != 0) {
                                // 0x004a21c8
                                charge(ctx, 3);
                                at = slti(s5, 2);
                                lw(a1, s1, strm(3, ps2all_stream::kCount));
                                if (at == 0) {
                                    // 0x004a21d4
                                    charge(ctx, 1);
                                    lw(a1, s1, strm(3, ps2all_stream::kCount2));
                                }
                                // 0x004a21d8
                                charge(ctx, 2);
                                s5 = subu(a1, t2);
                                t3 = subu(t3, s5);
                            } else {
                                // 0x004a21ac
                                charge(ctx, 7);
                                lh(s3, s1, strm(3, ps2all_stream::kLastBack));
                                a1 = t3;
                                t3 = 0;
                                s3 = sll(s3, 4);
                                s4 = subu(s4, s3);
                                s3 = s4;
                            }
                            // 0x004a21e0
                            charge(ctx, 3);
                            s5 = a1;
                            a1 = addiu(a1, -1);
                            if (s5 == 0) {
                                // 0x004a2438
                                charge(ctx, 1);
                                lw(s5, s2, rw_geometry::kMorphCount);
                            } else {
                                // 0x004a21ec
                                charge(ctx, 1);
                                for (;;) {
                                    // 0x004a21f0
                                    charge(ctx, 32);
                                    s5 = addu(t1, t5);
                                    lbu(t8, s5, 0);
                                    s5 = addu(t0, t5);
                                    t8 = sllv(t7, t8);
                                    lbu(s7, s5, 0);
                                    t8 = sll(t8, 1);
                                    t8 = addu(a2, t8);
                                    s5 = addu(a3, t5);
                                    s7 = sllv(t7, s7);
                                    lbu(s6, s5, 0);
                                    t5 = sll(t5, 1);
                                    t5 = srlv(t6, t5);
                                    t5 = t5 & 0x3;
                                    t7 = addu(t7, s6);
                                    s5 = a1;
                                    lhu(s6, t8, 0);
                                    a1 = addiu(a1, -1);
                                    s6 = addu(s7, s6);
                                    s6 = s6 & 0xFFFF;
                                    s6 = sll(s6, 3);
                                    s7 = addu(v1, s6);
                                    lwc1(f0, s7, 0);
                                    s6 = addu(v0, s6);
                                    swc1(f0, s3, 0);
                                    lwc1(f0, s7, 4);
                                    swc1(f0, s3, 4);
                                    lwc1(f0, s6, 0);
                                    swc1(f0, s3, 8);
                                    lwc1(f0, s6, 4);
                                    swc1(f0, s3, 12);
                                    s3 = addiu(s3, 16);
                                    if (s5 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004a2270
                                charge(ctx, 2);
                                lw(s5, s2, rw_geometry::kMorphCount);
                            }
                            // 0x004a243c
                            charge(ctx, 4);
                            lh(a1, s1, strm(3, ps2all_stream::kStride));
                            at = slti(s5, 2);
                            t7 = subu(t7, t2);
                            if (at == 0) {
                                // 0x004a244c
                                charge(ctx, 1);
                                lh(a1, s1, strm(3, ps2all_stream::kStride2));
                            }
                            // 0x004a2450
                            charge(ctx, 4);
                            a1 = sll(a1, 4);
                            s4 = addu(s4, a1);
                            s3 = s4;
                            if (i64(t3) <= 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004a2460
                        charge(ctx, 2);
                        backedge(ctx);
                    }
                }
            }
        }
    }  // stream 4: colours (the prelit RGBA with geometry flag 8, else 0xFF000000)
    // 0x004a2278
    charge(ctx, 4);
    lw(v0, a0, ps2all_pd::kInstFlags);
    v0 = v0 & 0x40;
    if (v0 != 0) {
        // 0x004a2288
        charge(ctx, 5);
        lw(v0, a0, ps2all_pd::kMatPvt);
        lw(v1, v0, sflags(4));
        v0 = v1 & 0x1;
        if (v0 != 0) {
            // 0x004a229c
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 == 0) {
                // 0x004a22a8
                charge(ctx, 8);
                lw(a0, s1, strm(4, ps2all_stream::kOffset));
                lw(v0, s2, rw_geometry::kMorphCount);
                lw(a1, s1, ps2all_hdr::kData);
                lw(v1, s2, rw_geometry::kPrelit);
                a0 = sll(a0, 4);
                at = slti(v0, 2);
                t5 = addu(a1, a0);
                if (at == 0) {
                    // 0x004a22c8
                    charge(ctx, 3);
                    lw(a0, s1, strm(4, ps2all_stream::kOffset2));
                    a0 = sll(a0, 4);
                    t5 = addu(a1, a0);
                }
                // 0x004a22d4
                charge(ctx, 3);
                t3 = t5;
                a1 = 0;
                if (i64(s0) > 0) {
                    // 0x004a22e0
                    charge(ctx, 1);
                    t7 = lui(0xFF00);
                    for (;;) {
                        // 0x004a22e4
                        charge(ctx, 4);
                        lw(a0, s1, ps2all_hdr::kClusterVerts);
                        at = slt(a0, s0);
                        if (at != 0) {
                            // 0x004a2310
                            charge(ctx, 3);
                            at = slti(v0, 2);
                            lw(a0, s1, strm(4, ps2all_stream::kCount));
                            if (at == 0) {
                                // 0x004a231c
                                charge(ctx, 1);
                                lw(a0, s1, strm(4, ps2all_stream::kCount2));
                            }
                            // 0x004a2320
                            charge(ctx, 2);
                            v0 = subu(a0, t2);
                            s0 = subu(s0, v0);
                        } else {
                            // 0x004a22f4
                            charge(ctx, 7);
                            lh(v0, s1, strm(4, ps2all_stream::kLastBack));
                            a0 = s0;
                            s0 = 0;
                            v0 = sll(v0, 4);
                            t5 = subu(t5, v0);
                            t3 = t5;
                        }
                        // 0x004a2328
                        charge(ctx, 4);
                        lw(v0, s2, rw_geometry::kFlags);
                        v0 = v0 & 0x8;
                        if (v0 == 0) {
                            // 0x004a23d8
                            charge(ctx, 3);
                            v0 = a0;
                            a0 = addiu(a0, -1);
                            if (v0 != 0) {
                                // 0x004a23e4
                                charge(ctx, 1);
                                for (;;) {
                                    // 0x004a23e8
                                    charge(ctx, 7);
                                    sw(t7, t3, 0);
                                    v0 = a0;
                                    t3 = addiu(t3, 4);
                                    a0 = addiu(a0, -1);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004a2404
                                charge(ctx, 1);
                            }
                        } else {
                            // 0x004a2338
                            charge(ctx, 3);
                            v0 = a0;
                            a0 = addiu(a0, -1);
                            if (v0 != 0) {
                                // 0x004a2344
                                charge(ctx, 1);
                                for (;;) {
                                    // 0x004a2348
                                    charge(ctx, 34);
                                    s3 = addu(t0, a1);
                                    lbu(s5, s3, 0);
                                    v0 = addu(t1, a1);
                                    lbu(v0, v0, 0);
                                    s3 = addu(a3, a1);
                                    lbu(s4, s3, 0);
                                    v0 = sllv(t4, v0);
                                    s6 = sll(v0, 1);
                                    a1 = sll(a1, 1);
                                    v0 = sllv(t4, s5);
                                    a1 = srlv(t6, a1);
                                    s5 = addu(a2, s6);
                                    a1 = a1 & 0x3;
                                    t4 = addu(t4, s4);
                                    s3 = a0;
                                    lhu(s4, s5, 0);
                                    a0 = addiu(a0, -1);
                                    v0 = addu(v0, s4);
                                    v0 = v0 & 0xFFFF;
                                    v0 = sll(v0, 2);
                                    v0 = addu(v1, v0);
                                    lbu(s6, v0, 1);
                                    lbu(s4, v0, 2);
                                    lbu(s5, v0, 0);
                                    s6 = sll(s6, 8);
                                    s4 = sll(s4, 16);
                                    lbu(v0, v0, 3);
                                    s5 = s5 | s6;
                                    s4 = s4 | s5;
                                    v0 = sll(v0, 24);
                                    v0 = v0 | s4;
                                    sw(v0, t3, 0);
                                    t3 = addiu(t3, 4);
                                    if (s3 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                                // 0x004a23d0
                                charge(ctx, 2);
                            }
                        }
                        // 0x004a2408
                        charge(ctx, 5);
                        lw(v0, s2, rw_geometry::kMorphCount);
                        lh(a0, s1, strm(4, ps2all_stream::kStride));
                        at = slti(v0, 2);
                        t4 = subu(t4, t2);
                        if (at == 0) {
                            // 0x004a241c
                            charge(ctx, 1);
                            lh(a0, s1, strm(4, ps2all_stream::kStride2));
                        }
                        // 0x004a2420
                        charge(ctx, 4);
                        a0 = sll(a0, 4);
                        t5 = addu(t5, a0);
                        t3 = t5;
                        if (i64(s0) <= 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
            }
        }
    }
    // 0x004a2430
    charge(ctx, 2);
    v0 = 1;
    // 0x004a2468
    charge(ctx, 11);
    lq(fp, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (the bodies read their arguments from the registers) -----------
namespace p3fes::recomp_gen {
namespace g = ::p3fes::game;

void fn_worldSectorRenderDispatch_00499230(p3fes::EEContext& ctx) { g::Cpu(ctx).sector_render(); }
void fn_RpWorldRender_0049a250(p3fes::EEContext& ctx) { g::Cpu(ctx).world_render(); }
void fn_worldForAllLights_00499c20(p3fes::EEContext& ctx) { g::Cpu(ctx).world_for_lights(); }
void fn_WorldSectorRender_00499320(p3fes::EEContext& ctx) { g::Cpu(ctx).sector_render_atomics(); }
void fn_sub_498E30_00498e30(p3fes::EEContext& ctx) { g::Cpu(ctx).geometry_mesh_build(); }
void fn_sub_469DC0_00469dc0(p3fes::EEContext& ctx) { g::Cpu(ctx).matfx_tail(); }
void fn_sub_4A2780_004a2780(p3fes::EEContext& ctx) { g::Cpu(ctx).im3d_instance_tail(); }

}  // namespace p3fes::recomp_gen
