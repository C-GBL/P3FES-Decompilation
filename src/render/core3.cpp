// RenderWare core, third rendering pass (core3.h has the groups and the data each function works on;
// docs/ANALYSIS/22_rendering.md sections 2-5, queue_rendering.txt rows tagged [rt2d] [rwcore] [renderstate] [raster]
// [upload] [im3d] [rxheap]).
//
// Cycle model (ADR-0013): every charge() below is one `ctx.cycles += N` block of the recompiled body in
// recomp/generated; backedge() sits wherever that body has a check point on a backward jump -- loops, and also the
// backward `goto`s of the compiler's block layout (a shared tail placed before the block that jumps to it), which
// the hand versions keep as explicit check points. A block that ends in a `jal` is charged in full before the call
// (the recompiler keeps the call inside its block), so a call's return continues in the same block.
//
// Registers: register-faithful (core3.h). Each body runs on a Cpu view of the guest context: one variable per GPR
// (64-bit writes keep bits 64..127, as the EE does; lq / MMI results write all 128), the FPU and HI/LO operations
// through the runtime's own instruction semantics, prologue spills and epilogue reloads on the guest stack. A
// branch's delay-slot instruction is written once before the `if` when it does not change the branch condition
// (it executes on both paths); the loop shapes are the compiled ones.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 52 of the 77 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: faults only 35, callee frames 8, frame/spills 8,
// the hand version terminated the host on a random world 1); the others are the hand-written versions this
// header describes.
//
// Readability pass (read_render, 2026-10-22): the 52 generated bodies keep every statement, charge, check point and
// call of p3fes_handgen's output in the same order on every path (proved per function by a bisimulation of the two
// statement graphs, and by the faithfulness audit); on top of it they name what they touch -- render_view.h for the
// records and addresses more than one render file reads (`hi()` / `lo()` / `la()` for a lui pair, `gp_off()`, the
// matrix, frame, camera, raster, image, texture, atomic, geometry, sector, Rt2d and PS2All records, the walk tables,
// the driver globals) --, say what each block does, and replace the generator's gotos by if / else / break
// (a `do { ... } while (false)` block where several paths leave a ladder early, local lambdas for the shared tails
// such as the epilogue); none is left. Each function's comment gives its role and, for a `sub_` name, a proposed
// name in brackets.
#include "p3fes/game/core3.h"

#include "p3fes_recomp_rt.h"

#include <initializer_list>
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/render_view.h"
#include "p3fes/game/rw_builders.h"  // rwb:: driver $gp words
#include "p3fes/game/rw_leaves.h"    // rwl:: RW globals and module offsets
#include "p3fes/game/sky.h"          // sky:: GS shadows and driver globals

namespace p3fes::recomp_gen {
void fn_RwRasterShowRaster_004cdfe0(p3fes::EEContext&);  // this slice
void fn_RxPipelineExecute_004f2e70(p3fes::EEContext&);  // this slice
void fn_SyncDCache_00503a58(p3fes::EEContext&);  // libkernel: write the data cache back
void fn___floatdisf_0052eb60(p3fes::EEContext&);  // libgcc: s64 -> float
void fn___udivdi3_0052fe98(p3fes::EEContext&);  // libgcc: u64 / u64
void fn__rwDMAOpenGIFPkt_004d54e0(p3fes::EEContext&);  // the DMA packet layer: open a GIF packet
void fn_memcpy_00521250(p3fes::EEContext&);  // libc memcpy
void fn_sub_46BAB0_0046bab0(p3fes::EEContext&);  // the Rt2d path fill (flatten + the Rt2d fill pipeline)
void fn_sub_46BD00_0046bd00(p3fes::EEContext&);  // the Rt2d path stroke
void fn_sub_4A55B0_004a55b0(p3fes::EEContext&);  // this slice
void fn_sub_4A6600_004a6600(p3fes::EEContext&);  // this slice
void fn_sub_4A9A70_004a9a70(p3fes::EEContext&);  // this slice
void fn_sub_4AA2C0_004aa2c0(p3fes::EEContext&);  // this slice
void fn_sub_4AAB40_004aab40(p3fes::EEContext&);  // this slice
void fn_sub_4AAC70_004aac70(p3fes::EEContext&);  // this slice
void fn_sub_4AAD50_004aad50(p3fes::EEContext&);  // this slice
void fn_sub_4AAE60_004aae60(p3fes::EEContext&);  // this slice
void fn_sub_4AB0C0_004ab0c0(p3fes::EEContext&);  // this slice
void fn_sub_4AB0E0_004ab0e0(p3fes::EEContext&);  // an Rt2d object free (RwFree / the freelist; kept recompiled)
void fn_sub_4AB6A0_004ab6a0(p3fes::EEContext&);  // this slice
void fn_sub_4AB910_004ab910(p3fes::EEContext&);  // this slice
void fn_sub_4ABA20_004aba20(p3fes::EEContext&);  // this slice
void fn_sub_4AC390_004ac390(p3fes::EEContext&);  // this slice
void fn_sub_4ACE70_004ace70(p3fes::EEContext&);  // this slice
void fn_sub_4AD750_004ad750(p3fes::EEContext&);  // this slice
void fn_sub_4ADF30_004adf30(p3fes::EEContext&);  // this slice
void fn_sub_4AE2F0_004ae2f0(p3fes::EEContext&);  // this slice
void fn_sub_4AE690_004ae690(p3fes::EEContext&);  // this slice
void fn_sub_4AE940_004ae940(p3fes::EEContext&);  // this slice
void fn_sub_4AE960_004ae960(p3fes::EEContext&);  // this slice
void fn_sub_4AF9D0_004af9d0(p3fes::EEContext&);  // this slice
void fn_sub_4C1C50_004c1c50(p3fes::EEContext&);  // RwErrorSet (render_rw)
void fn_sub_4C1D10_004c1d10(p3fes::EEContext&);  // _rwerror: the error code word (render_rw)
void fn_sub_4C1E60_004c1e60(p3fes::EEContext&);  // array: empty (render_rw)
void fn_sub_4C1E70_004c1e70(p3fes::EEContext&);  // the growable array append (RwRealloc; kept recompiled)
void fn_sub_4C2090_004c2090(p3fes::EEContext&);  // array: base, 0 when empty (render_rw)
void fn_sub_4C2120_004c2120(p3fes::EEContext&);  // array: count (render_rw)
void fn_sub_4C21B0_004c21b0(p3fes::EEContext&);  // array: entry (render_rw)
void fn_sub_4C2330_004c2330(p3fes::EEContext&);  // this slice
void fn_sub_4C2F30_004c2f30(p3fes::EEContext&);  // RwMatrixMultiply on VU0 (render_rw)
void fn_sub_4C32A0_004c32a0(p3fes::EEContext&);  // the matrix inverse (render_rw)
void fn_sub_4C33D0_004c33d0(p3fes::EEContext&);  // this slice
void fn_sub_4C35D0_004c35d0(p3fes::EEContext&);  // this slice
void fn_sub_4C3760_004c3760(p3fes::EEContext&);  // this slice
void fn_sub_4C38C0_004c38c0(p3fes::EEContext&);  // RwMatrixCreate (the matrix freelist)
void fn_sub_4C4890_004c4890(p3fes::EEContext&);  // the resource arena purge
void fn_sub_4C6C60_004c6c60(p3fes::EEContext&);  // this slice
void fn_sub_4C6D60_004c6d60(p3fes::EEContext&);  // this slice
void fn_sub_4CB2F0_004cb2f0(p3fes::EEContext&);  // this slice
void fn_sub_4CB7F0_004cb7f0(p3fes::EEContext&);  // this slice
void fn_sub_4CE3A0_004ce3a0(p3fes::EEContext&);  // this slice
void fn_sub_4CE9A0_004ce9a0(p3fes::EEContext&);  // this slice
void fn_sub_4CF3B0_004cf3b0(p3fes::EEContext&);  // this slice
void fn_sub_4CF4C0_004cf4c0(p3fes::EEContext&);  // this slice
void fn_sub_4D13E0_004d13e0(p3fes::EEContext&);  // this slice
void fn_sub_4D5FE0_004d5fe0(p3fes::EEContext&);  // the DMA packet layer: flush the scratchpad half
void fn_sub_4DDAA0_004ddaa0(p3fes::EEContext&);  // this slice
void fn_sub_4DDD30_004ddd30(p3fes::EEContext&);  // this slice
void fn_sub_4F0C70_004f0c70(p3fes::EEContext&);  // texture cache: re-upload a raster's palette
void fn_sub_4F1540_004f1540(p3fes::EEContext&);  // texture cache: release a raster (render_rw)
void fn_sub_4F28F0_004f28f0(p3fes::EEContext&);  // the pipeline: release a node list
void fn_sub_4F2E60_004f2e60(p3fes::EEContext&);  // the global RxHeap (render_rw)
void fn_sub_4F3150_004f3150(p3fes::EEContext&);  // this slice
void fn_sub_4F61C0_004f61c0(p3fes::EEContext&);  // the RxHeap block growth (RwRealloc; kept recompiled)
void fn_sub_4F62D0_004f62d0(p3fes::EEContext&);  // this slice
void fn_sub_4F6890_004f6890(p3fes::EEContext&);  // this slice
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

using namespace rview;  // render_view.h: la / hi / lo / gp_off / flt and the shared RW records

namespace c3 {
namespace detail {

namespace core = ee::core;
namespace gen = ::p3fes::recomp_gen;

// --- R5900 integer results (32-bit operations sign-extend into the 64-bit register) ----------------------
constexpr u64 sx(u32 v) { return core::sext32(v); }
constexpr u64 si(s32 v) { return static_cast<u64>(static_cast<s64>(v)); }  // a negative immediate
constexpr s64 sgn(u64 v) { return static_cast<s64>(v); }                  // a register as a signed 64-bit value
constexpr u64 addu(u64 a, u64 b) { return core::add32(a, b); }
constexpr u64 addiu(u64 a, s32 i) { return core::add32i(a, i); }
constexpr u64 daddiu(u64 a, s32 i) { return core::add64i(a, i); }
constexpr u64 subu(u64 a, u64 b) { return core::sub32(a, b); }
constexpr u64 lui(u32 i) { return core::lui(i); }
constexpr u64 sll(u64 a, unsigned n) { return core::sll(a, n); }
constexpr u64 srl(u64 a, unsigned n) { return core::srl(a, n); }
constexpr u64 sra(u64 a, unsigned n) { return core::sra(a, n); }
constexpr u64 sllv(u64 a, u64 n) { return core::sllv(a, n); }
constexpr u64 srlv(u64 a, u64 n) { return core::srlv(a, n); }
constexpr u64 srav(u64 a, u64 n) { return core::srav(a, n); }
constexpr u64 dsllv(u64 a, u64 n) { return core::dsllv(a, n); }
constexpr u64 dsll(u64 a, unsigned n) { return core::dsll(a, n); }
constexpr u64 dsrl(u64 a, unsigned n) { return core::dsrl(a, n); }
constexpr u64 dsra(u64 a, unsigned n) { return core::dsra(a, n); }
constexpr u64 dsll32(u64 a, unsigned n) { return core::dsll32(a, n); }
constexpr u64 dsrl32(u64 a, unsigned n) { return core::dsrl32(a, n); }
constexpr u64 dsra32(u64 a, unsigned n) { return core::dsra32(a, n); }
constexpr u64 slt(u64 a, u64 b) { return core::slt(a, b); }
constexpr u64 sltu(u64 a, u64 b) { return core::sltu(a, b); }
constexpr u64 slti(u64 a, s32 i) { return core::slti(a, i); }
constexpr u64 sltiu(u64 a, s32 i) { return core::sltiu(a, i); }
constexpr u32 w(u64 v) { return static_cast<u32>(v); }

// One GPR of the guest context. Reads go through volatile lvalues, and so does virtual time below: MSVC 14.44 /O2
// (in-TU interprocedural mod-ref) was seen keeping ctx.cycles in a host register across a call to a small leaf
// helper that charges (sub_4C33D0's combine-op dispatch: the helper's charges were lost). A volatile access is a
// compiler barrier under /volatile:ms (and keeps every access real under clang-cl), so no guest state is cached
// across a helper.
struct Gpr {
    EEContext& c;
    const unsigned r;
    operator u64() const noexcept { return static_cast<const volatile u64&>(c.gpr[r].u64[0]); }
    u32 u() const noexcept { return static_cast<const volatile u32&>(c.gpr[r].u32[0]); }
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
    Gpr t8{c, 24}, t9{c, 25}, gp{c, 28}, sp{c, 29}, fp{c, 30}, ra{c, 31};

    // virtual time
    // enter / backedge are not noexcept (as guest.h): a check point's fatal event must unwind through the bodies
    void enter(u64 n) {
        rt::check_events(c);
        charge(n);
    }
    void charge(u64 n) noexcept {
        volatile u64& t = c.cycles;
        t = t + n;
    }
    void backedge() { rt::check_events(c); }

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

    // FPU (the runtime's instruction semantics: EE singles, ACC, FCR31 flags)
    void lwc1(unsigned f, u64 a) noexcept { c.fpr[f] = guest::load<u32>(c, w(a)); }
    void swc1(unsigned f, u64 a) noexcept { guest::store<u32>(c, w(a), c.fpr[f]); }
    void mtc1(const Gpr& g, unsigned f) noexcept { rt::mtc1(c, g.r, f); }
    void mfc1(Gpr& g, unsigned f) noexcept { rt::mfc1(c, g.r, f); }
    void mov_s(unsigned d, unsigned s) noexcept { rt::mov_s(c, d, s); }
    void neg_s(unsigned d, unsigned s) noexcept { rt::neg_s(c, d, s); }
    void cvt_s_w(unsigned d, unsigned s) noexcept { rt::cvt_s_w(c, d, s); }
    void cvt_w_s(unsigned d, unsigned s) noexcept { rt::cvt_w_s(c, d, s); }
    void add_s(unsigned d, unsigned s, unsigned t) noexcept { rt::add_s(c, d, s, t); }
    void sub_s(unsigned d, unsigned s, unsigned t) noexcept { rt::sub_s(c, d, s, t); }
    void mul_s(unsigned d, unsigned s, unsigned t) noexcept { rt::mul_s(c, d, s, t); }
    void div_s(unsigned d, unsigned s, unsigned t) noexcept { rt::div_s(c, d, s, t); }
    void sqrt_s(unsigned d, unsigned t) noexcept { rt::sqrt_s(c, d, t); }
    void adda_s(unsigned s, unsigned t) noexcept { rt::adda_s(c, s, t); }
    void mula_s(unsigned s, unsigned t) noexcept { rt::mula_s(c, s, t); }
    void madda_s(unsigned s, unsigned t) noexcept { rt::madda_s(c, s, t); }
    void madd_s(unsigned d, unsigned s, unsigned t) noexcept { rt::madd_s(c, d, s, t); }
    void msub_s(unsigned d, unsigned s, unsigned t) noexcept { rt::msub_s(c, d, s, t); }
    void c_eq_s(unsigned s, unsigned t) noexcept { rt::c_eq_s(c, s, t); }
    void c_lt_s(unsigned s, unsigned t) noexcept { rt::c_lt_s(c, s, t); }
    void c_le_s(unsigned s, unsigned t) noexcept { rt::c_le_s(c, s, t); }
    bool cop1_cond() const noexcept { return rt::cop1_cond(c); }

    // HI/LO (both pipes) and MMI
    void mult(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::mult(c, d.r, s.r, t.r); }
    void multu(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::multu(c, d.r, s.r, t.r); }
    void mult1(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::mult1(c, d.r, s.r, t.r); }
    void maddu(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::maddu(c, d.r, s.r, t.r); }
    void div(const Gpr& s, const Gpr& t) noexcept { rt::div(c, s.r, t.r); }
    void divu(const Gpr& s, const Gpr& t) noexcept { rt::divu(c, s.r, t.r); }
    void mflo(Gpr& d) noexcept { rt::mflo(c, d.r); }
    void mfhi(Gpr& d) noexcept { rt::mfhi(c, d.r); }
    void pcpyld(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::pcpyld(c, d.r, s.r, t.r); }
    void pextlw(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::pextlw(c, d.r, s.r, t.r); }

    // calls: `jal fn` at pc ($ra = pc + 8; the delay slot's instruction is written before the call), `jalr target`
    // at pc (through the dispatch table), a `jr` tail call (no link) and a static tail call (`j fn`)
    void jal(u32 pc, rt::Fn fn) {
        rt::jal(c, pc);
        fn(c);
    }
    void jalr(u32 pc, u32 target) {
        rt::jalr(c, GPR_RA, pc);
        rt::lookup_func(target)(c);
    }
    void tail(u32 target) { rt::lookup_func(target)(c); }
    void tailcall(rt::Fn fn) { fn(c); }

    // --- the bodies (core3.h documents each; named as the functions they are) ---
    void sub_4C2FB0();
    void rwerror(u32 pc, s32 slot);
    unsigned combine_op(s32 slot);
    void matrix_flags_exit(u32 mask_lo);
    void sub_4C33D0();
    void sub_4C35D0();
    void copy_matrix(Gpr& n, Gpr& src, Gpr& dst, Gpr& lo, Gpr& hi, bool src_step_between);
    void sub_4C3760();
    void plugin_call_keep_a0(s32 slot, s32 off, u32 pc);
    void sub_4C6BE0();
    void sub_4C6C60();
    void sub_4C6D60();
    void sub_4C6E60();
    void sub_4C6F30();
    void RwCameraEndUpdate();
    void RwCameraBeginUpdate();
    void RwCameraClear();
    void RwCameraShowRaster();
    void sub_4CB2F0();
    void sub_4CB7F0();
    bool std_call2(s32 off, u32 pc);
    void std_call2_exit();
    void sub_4CDC70();
    void sub_4CDCE0();
    void sub_4CDD50();
    void sub_4CDE00();
    void RwRasterShowRaster();
    void sub_4CE050();
    void sub_4CE200();
    void frame_ltm(const Gpr& f, Gpr& flags_reg, Gpr& t, Gpr& u, u32 pc);
    void sub_4CF3B0();
    void sub_4CF4C0();
    void sub_4D0FD0();
    void sub_4D13E0();
    void recip_unless_le0(unsigned v, unsigned one);
    void sub_4C2330();
    void u2f(Gpr& val, Gpr& tmp, unsigned fd, unsigned fs);
    void channel_store(Gpr& k, const Gpr& out, s32 off);
    void scale4(const Gpr& p, unsigned f, unsigned tmp);
    void sub_4CE3A0();
    void sub_4CE9A0();
    void sub_4CEC10();
    void RxPipelineExecute();
    void sub_4F3150();
    void sub_4F5D30();
    void sub_4F62D0();
    void sub_4F6890();
    void pipeline_lock_exit();
    void sub_4F1ED0();
    void im3d_exit(s32 frame, s32 ra_slot);
    void sub_4F1FD0();
    void sub_4F2150();
    void sub_4D78B0();
    void half(Gpr& dst, const Gpr& src);
    void sub_4EEC20();
    void skyFillInPktForUpLoadAlignedContiguousRectangle();
    void sub_4EF770();
    void sub_4DD480();
    void sub_4DD700();
    void sub_4DDAA0();
    void sub_4DDD30();
    void raster_bytes(u64 tail_cost);
    void sub_4DECE0();
    void unlock_exit();
    void sub_4DEF10();
    void sub_4DEFD0();
    void palette_exit();
    void fb_raster(s32 slot, Gpr& rec, bool first);
    void sub_4E2F10();
    void sub_4E4A90();
    void sub_4E4C20();
    void sub_4A55B0();
    void sub_4A9A70();
    bool ctm_push_slot(u32 create_pc);
    void sub_4AAB40();
    void sub_4AAC70();
    void sub_4AAD50();
    void sub_4AB0C0();
    void sub_4AB910();
    bool segment_normal(unsigned fa, unsigned fb, const Gpr& count, u64 copy_cost);
    void append_curve_end(u32 count_pc);
    void sub_4ABA20();
    void sub_4AC020();
    void sub_4AC390();
    void sub_4AE690();
    void sub_4AB8C0();
    void sub_4AB6A0();
    void sub_4ABD50();
    void sub_4AAE60();
    void sub_4AA2C0();
    void sub_4AD750();
    void sub_4AE2F0();
    void sub_4A6600();
    void sub_4ACE70();
    void sub_4ADF30();
    void sub_4AE960();
    void sub_4AE940();
    void sub_4B5330();
    void object_push_dirty(const Gpr& obj, u32 push_pc);
    void sub_4AF9D0();
};

// =========================================================================================================
// The bodies
// =========================================================================================================

// =========================================================================================================
// [rwcore] RenderWare core: matrices, frames, the resource heap, cameras, rasters and images.
// =========================================================================================================

// sub_4C2FB0 [RwMatrixOptimize-like wrapper]: a static tail call into sub_4C2330 (same arguments).
void Cpu::sub_4C2FB0() {
    enter(2);
    tailcall(gen::fn_sub_4C2330_004c2330);
}

// The RWERROR sequence of the core: v0 = _rwerror(a0 = code, ...) (sub_4C1D10, jal at `pc`), the pair {.., v0} at
// sp + slot (+4 the code word; +0 written by the caller), RwErrorSet(sp + slot) (sub_4C1C50, jal at pc + 12).
void Cpu::rwerror(u32 pc, s32 slot) {
    jal(pc, gen::fn_sub_4C1D10_004c1d10);
    sw(sp + slot + 4, v0);
    a0 = addiu(sp, slot);
    jal(pc + 12, gen::fn_sub_4C1C50_004c1c50);
}

// The matrix "combine op" dispatch shared by sub_4C33D0 / sub_4C35D0 / sub_4C3760: $a2 = 2 (post-concat), 1
// (pre-concat), 0 (replace); returns the op (0..2), or 3 for a bad op after storing 1 at sp + `slot` (the error
// pair's first word; v0 holds 1 there).
unsigned Cpu::combine_op(s32 slot) {
    v0 = 2;
    if (a2 == v0) return 2;
    charge(3);
    v0 = 1;
    if (a2 == v0) return 1;
    charge(2);
    if (a2 == 0) return 0;
    charge(2);
    sw(sp + slot, v0);
    return 3;
}

// The RwMatrix flags word (+12) after a scale / translate: flags & mask, returning the matrix in $v0.
void Cpu::matrix_flags_exit(u32 mask_lo) {
    charge(9);
    a1 = lw(a0 + 12);
    v0 = lui(0xFFFD);
    v1 = v0 | mask_lo;
    v0 = a0;
    v1 = a1 & v1;
    sw(a0 + 12, v1);
    ra = ld(sp);
    sp = addiu(sp, 32);
}

// sub_4C33D0 [RwMatrixScale(matrix, scale, combine)]: $a0 the matrix (right +0, up +16, at +32, pos +48, flags +12),
// $a1 the scale vector. Replace: identity scaled; pre-concat: each row scaled by one component; post-concat: each
// column scaled. The flags lose 0x20003 (identity / orthonormal / normalised). A bad op: RWERROR, then the flags of
// the matrix at address 0 are updated (the retail error path continues with a0 = 0).
void Cpu::sub_4C33D0() {
    enter(4);
    sp = addiu(sp, -32);
    sd(sp, ra);  // (the first branch's delay slot)
    const unsigned op = combine_op(24);
    switch (op) {
    case 0:  // replace
        charge(25);
        v1 = lui(0x3F80);  // 1.0
        v0 = lui(0x2);
        sw(a0 + 40, v1);
        lwc1(F2, a1);
        sw(a0 + 20, v1);
        lwc1(F1, a1 + 4);
        sw(a0, v1);
        lwc1(F0, a1 + 8);
        sw(a0 + 16, zero);
        v0 = v0 | 3;
        sw(a0 + 8, zero);
        sw(a0 + 4, zero);
        sw(a0 + 36, zero);
        sw(a0 + 32, zero);
        sw(a0 + 24, zero);
        sw(a0 + 56, zero);
        sw(a0 + 52, zero);
        sw(a0 + 48, zero);
        v1 = lw(a0 + 12);
        v0 = v1 | v0;
        sw(a0 + 12, v0);
        swc1(F2, a0);
        swc1(F1, a0 + 20);
        swc1(F0, a0 + 40);
        break;
    case 1:  // pre-concat: right *= x, up *= y, at *= z
        charge(31);
        lwc1(F0, a0);
        lwc1(F3, a1);
        lwc1(F2, a1 + 4);
        lwc1(F1, a1 + 8);
        for (unsigned row = 0; row < 3; ++row) {
            const unsigned f = row == 0 ? F3 : row == 1 ? F2 : F1;
            for (unsigned k = 0; k < 3; ++k) {
                if (row != 0 || k != 0) lwc1(F0, a0 + 16 * row + 4 * k);
                mul_s(F0, F0, f);
                swc1(F0, a0 + 16 * row + 4 * k);
            }
        }
        break;
    case 2:  // post-concat: the x / y / z column of every row (pos included) scaled
        charge(40);
        lwc1(F0, a0);
        lwc1(F3, a1);
        lwc1(F2, a1 + 4);
        lwc1(F1, a1 + 8);
        for (unsigned row = 0; row < 4; ++row) {
            for (unsigned k = 0; k < 3; ++k) {
                if (row != 0 || k != 0) lwc1(F0, a0 + 16 * row + 4 * k);
                mul_s(F0, F0, k == 0 ? F3 : k == 1 ? F2 : F1);
                swc1(F0, a0 + 16 * row + 4 * k);
            }
        }
        break;
    default:  // bad combine op
        charge(9);
        a1 = lui(0x78);
        v0 = lui(0x8000);
        a1 = addiu(a1, -6720);
        a0 = v0 | 3;
        rwerror(0x4C3588u, 24);
        a0 = zero;
        break;
    }
    matrix_flags_exit(0xFFFC);
}

// sub_4C35D0 [RwMatrixTranslate(matrix, translation, combine)]: replace: identity with pos = t; pre-concat:
// pos += right * t.x + up * t.y + at * t.z (through ACC); post-concat: pos += t. The flags lose 0x20000.
void Cpu::sub_4C35D0() {
    enter(4);
    sp = addiu(sp, -32);
    sd(sp, ra);  // (the first branch's delay slot)
    const unsigned op = combine_op(24);
    switch (op) {
    case 0:
        charge(25);
        v1 = lui(0x3F80);
        v0 = lui(0x2);
        sw(a0 + 40, v1);
        lwc1(F2, a1);
        sw(a0 + 20, v1);
        lwc1(F1, a1 + 4);
        sw(a0, v1);
        lwc1(F0, a1 + 8);
        sw(a0 + 16, zero);
        v0 = v0 | 3;
        sw(a0 + 8, zero);
        sw(a0 + 4, zero);
        sw(a0 + 36, zero);
        sw(a0 + 32, zero);
        sw(a0 + 24, zero);
        sw(a0 + 56, zero);
        sw(a0 + 52, zero);
        sw(a0 + 48, zero);
        v1 = lw(a0 + 12);
        v0 = v1 | v0;
        sw(a0 + 12, v0);
        swc1(F2, a0 + 48);
        swc1(F1, a0 + 52);
        swc1(F0, a0 + 56);
        break;
    case 1:
        charge(31);
        lwc1(F4, a1 + 4);
        lwc1(F1, a0 + 16);
        lwc1(F5, a1);
        lwc1(F2, a0);
        lwc1(F6, a1 + 8);
        lwc1(F3, a0 + 32);
        for (unsigned k = 0; k < 3; ++k) {
            if (k != 0) {
                lwc1(F1, a0 + 16 + 4 * k);
                lwc1(F2, a0 + 4 * k);
                lwc1(F3, a0 + 32 + 4 * k);
            }
            lwc1(F0, a0 + 48 + 4 * k);
            mula_s(F4, F1);
            madda_s(F5, F2);
            madd_s(F1, F6, F3);
            add_s(F0, F0, F1);
            swc1(F0, a0 + 48 + 4 * k);
        }
        break;
    case 2:
        charge(13);
        lwc1(F3, a0 + 48);
        lwc1(F0, a1);
        lwc1(F2, a1 + 4);
        lwc1(F1, a1 + 8);
        add_s(F0, F3, F0);
        swc1(F0, a0 + 48);
        lwc1(F0, a0 + 52);
        add_s(F0, F0, F2);
        swc1(F0, a0 + 52);
        lwc1(F0, a0 + 56);
        add_s(F0, F0, F1);
        swc1(F0, a0 + 56);
        break;
    default:
        charge(9);
        a1 = lui(0x78);
        v0 = lui(0x8000);
        a1 = addiu(a1, -6720);
        a0 = v0 | 3;
        rwerror(0x4C371Cu, 24);
        a0 = zero;
        break;
    }
    matrix_flags_exit(0xFFFF);
}

// 64 bytes from `src` to `dst` as eight word pairs through `lo` / `hi` (the compiled copy loop: counter `n` from 8,
// the destination advanced in the branch delay slot); `src_step_between` puts the source step between the two stores
// (the other compiled order steps it after them).
void Cpu::copy_matrix(Gpr& n, Gpr& src, Gpr& dst, Gpr& lo, Gpr& hi, bool src_step_between) {
    n = 8;
    for (;;) {
        charge(8);
        lo = lw(src);
        n = addiu(n, -1);
        hi = lw(src + 4);
        sw(dst, lo);
        if (src_step_between) {
            src = addiu(src, 8);
            sw(dst + 4, hi);
        } else {
            sw(dst + 4, hi);
            src = addiu(src, 8);
        }
        const bool more = sgn(n) > 0;
        dst = addiu(dst, 8);
        if (!more) break;
        backedge();
    }
}

// sub_4C3760 [RwMatrixTransform(matrix, transform, combine)]: replace: copy; pre-concat: matrix = transform x
// matrix; post-concat: matrix = matrix x transform (sub_4C2F30 into a 64-byte frame buffer, then copied back).
// Returns the matrix (0 after RWERROR for a bad op).
void Cpu::sub_4C3760() {
    enter(6);
    sp = addiu(sp, -176);
    sd(sp + 16, ra);
    sq(sp, s0);
    s0 = a0;  // (the branch delay slot)
    const unsigned op = combine_op(168);
    switch (op) {
    case 0:
        charge(2);
        a2 = s0;
        copy_matrix(a0, a1, a2, v1, v0, false);
        charge(2);
        v0 = s0;
        break;
    case 1:
        charge(6);
        a0 = addiu(sp, 96);
        a2 = s0;
        jal(0x4C37C8u, gen::fn_sub_4C2F30_004c2f30);
        a2 = addiu(sp, 96);
        a1 = s0;
        copy_matrix(a0, a2, a1, v1, v0, true);
        charge(2);
        charge(1);
        v0 = s0;
        break;
    case 2:
        charge(7);
        a2 = a1;
        a0 = addiu(sp, 32);
        a1 = s0;
        jal(0x4C380Cu, gen::fn_sub_4C2F30_004c2f30);
        a2 = addiu(sp, 32);
        a1 = s0;
        copy_matrix(a0, a2, a1, v1, v0, true);
        charge(2);
        charge(1);
        v0 = s0;
        break;
    default:
        charge(9);
        a1 = lui(0x78);
        v0 = lui(0x8000);
        a1 = addiu(a1, -6720);
        a0 = v0 | 3;
        rwerror(0x4C3854u, 168);
        s0 = zero;
        charge(1);
        v0 = s0;
        break;
    }
    charge(4);
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 176);
}

// A call through a function pointer of the engine-plugin block: *(0x960070 + *(gp + `slot`) + `off`)($a0, ...),
// keeping $a0 in $s0 and returning it (sub_4C6BE0 / sub_4C6C60: 32-byte frame, $ra at +16).
void Cpu::plugin_call_keep_a0(s32 slot, s32 off, u32 pc) {
    enter(15);
    sp = addiu(sp, -32);
    v0 = lui(0x96);
    sd(sp + 16, ra);
    v0 = addiu(v0, 112);
    sq(sp, s0);
    v1 = lw(gp + slot);
    v0 = addu(v0, v1);
    v0 = lw(v0 + off);
    s0 = a0;
    jalr(pc, v0.u());
    v0 = s0;
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 32);
}

// sub_4C6BE0 [RwV3dTransformPoints]: the vector module's points transform (its function table +8), returns $a0.
void Cpu::sub_4C6BE0() { plugin_call_keep_a0(-17376, 8, 0x4C6C00u); }

// sub_4C6C60 [RwV3dTransformVectors]: the vector module's vectors transform (+16), returns $a0.
void Cpu::sub_4C6C60() { plugin_call_keep_a0(-17376, 16, 0x4C6C80u); }

// The resource heap (RwResourcesHeap-like): blocks with a 32-byte header {+0 heap, +4 next, +8 prev, +12 size,
// +16 used}; the heap {+0 .., +4 the first-free hint, +12 ..}.

// sub_4C6D60 [split a free block]: $a0 the block header, $a1 the size to keep. A new free header is made at
// a0 + a1 + 32 and linked after it; the remainder size goes to the new header, the block keeps a1.
void Cpu::sub_4C6D60() {
    enter(4);
    a2 = lw(a0 + 4);  // next
    v1 = addu(a0, a1);
    a3 = addiu(v1, 32);  // the new header (the branch delay slot)
    bool merge_next = false;
    if (a2 != 0) {
        charge(5);
        v1 = lw(a2 + 16);
        v1 = ~v1;
        v1 = v1 & 1;
        merge_next = v1 != 0;  // the next block is free: the new header absorbs it
    }
    if (merge_next) {
        charge(8);
        v1 = lw(a2 + 4);
        sw(a3 + 4, v1);
        v1 = lw(a0 + 4);
        a2 = lw(a0 + 12);
        v1 = lw(v1 + 12);
        a2 = subu(a2, a1);
        v1 = addu(v1, a2);
        sw(a3 + 12, v1);
    } else {
        charge(6);
        sw(a3 + 4, a2);
        v1 = lw(a0 + 12);
        v1 = subu(v1, a1);
        v1 = addiu(v1, -32);
        sw(a3 + 12, v1);
        backedge();
    }
    charge(6);
    sw(a0 + 4, a3);
    sw(a3 + 16, zero);
    sw(a3 + 8, a0);
    v1 = lw(a3 + 4);
    if (v1 != 0) {
        charge(1);
        sw(v1 + 8, a3);
    }
    charge(4);
    sw(a0 + 12, a1);
    v1 = lw(a0);
    sw(a3, v1);
    charge(2);
}

// sub_4C6E60 [free a block]: $a0 the block's data (header at a0 - 32). Marks it free, moves the heap's first-free
// hint back to it when it is earlier (or the hint is 0), and merges it with a free previous and a free next block.
void Cpu::sub_4C6E60() {
    enter(9);
    sw(a0 - 16, zero);     // used = 0
    v1 = addiu(a0, -32);   // the header
    a3 = lw(a0 - 24);      // prev
    a2 = lw(a0 - 28);      // next
    a0 = lw(a0 - 32);      // the heap
    a1 = addiu(a0, 4);     // &heap->hint
    a0 = lw(a0 + 4);
    bool move_hint = a0 == 0;
    if (!move_hint) {
        charge(3);
        a0 = sltu(v1, a0);
        move_hint = a0 != 0;
    }
    if (move_hint) {
        charge(2);
        sw(a1, v1);
        backedge();
    }
    charge(2);
    if (a3 != 0) {
        charge(5);
        a0 = lw(a3 + 16);
        a0 = ~a0;
        a0 = a0 & 1;
        if (a0 != 0) {  // merge into the free previous block
            charge(2);
            sw(a3 + 4, a2);
            if (a2 != 0) {
                charge(1);
                sw(a2 + 8, a3);
            }
            charge(6);
            v1 = lw(v1 + 12);
            a0 = lw(a3 + 12);
            a1 = addiu(v1, 32);
            a0 = addu(a0, a1);
            v1 = a3;
            sw(a3 + 12, a0);
        }
    }
    charge(2);
    if (a2 != 0) {
        charge(5);
        a0 = lw(a2 + 16);
        a0 = ~a0;
        a0 = a0 & 1;
        if (a0 != 0) {  // absorb the free next block
            charge(5);
            a0 = lw(a2 + 4);
            sw(v1 + 4, a0);
            a0 = lw(a2 + 4);
            if (a0 != 0) {
                charge(1);
                sw(a0 + 8, v1);
            }
            charge(7);
            a1 = lw(a2 + 12);
            a0 = lw(v1 + 12);
            a1 = addiu(a1, 32);
            a0 = addu(a0, a1);
            sw(v1 + 12, a0);
        }
    }
    charge(2);
}

// sub_4C6F30 [allocate from the resource heap]: $a0 the heap, $a1 the size (rounded up to 32). First fit from the
// hint (+4); a block more than 64 bytes larger is split (sub_4C6D60); when the block was the hint, the hint moves to
// the next free block. Marks the block used and returns its data (header + 32), or 0.
void Cpu::sub_4C6F30() {
    enter(8);
    sp = addiu(sp, -16);
    t0 = a0;
    sd(sp, ra);
    v1 = addiu(a1, 31);
    a2 = lw(a0 + 4);
    v0 = si(-32);
    a1 = v1 & v0;
    a0 = zero;
    for (;;) {
        charge(4);
        v0 = sltu(zero, a2);
        v0 = v0 ^ 1;
        if (v0 != 0) break;
        charge(2);
        if (a0 != 0) break;
        charge(5);
        v0 = lw(a2 + 16);
        v0 = ~v0;
        v0 = v0 & 1;
        if (v0 != 0) {
            charge(4);
            v0 = lw(a2 + 12);
            v0 = sltu(v0, a1);
            if (v0 == 0) {
                charge(1);
                a0 = a2;
            }
        }
        charge(2);
        a2 = lw(a2 + 4);
        backedge();
    }
    charge(2);
    if (a0 == 0) {
        charge(2);
        v0 = zero;
    } else {
        charge(5);
        v1 = lw(a0 + 12);
        v0 = addiu(a1, 64);
        at = sltu(v0, v1);
        if (at != 0) {
            charge(4);
            jal(0x4C6FD8u, gen::fn_sub_4C6D60_004c6d60);
            v1 = lw(t0 + 4);
            backedge();
        } else {
            charge(1);
            v1 = lw(t0 + 4);
        }
        charge(2);
        if (a0 == v1) {  // the hint: on to the next free block
            for (;;) {
                charge(5);
                v0 = lw(v1 + 4);
                sw(t0 + 4, v0);
                v1 = lw(t0 + 4);
                if (v1 == 0) {
                    backedge();
                    charge(1);
                    v1 = 1;
                    break;
                }
                charge(4);
                v0 = lw(v1 + 16);
                v0 = v0 & 1;
                if (v0 == 0) {
                    charge(2);
                    v1 = 1;
                    backedge();
                    break;
                }
                backedge();
            }
        } else {
            charge(1);
            v1 = 1;
        }
        charge(3);
        v0 = addiu(a0, 32);
        sw(a0 + 16, v1);
    }
    charge(3);
    ra = ld(sp);
    sp = addiu(sp, 16);
}

// RwCameraEndUpdate(camera): a `jr` tail call through camera +28 (CameraEndUpdate).
void Cpu::RwCameraEndUpdate() {
    enter(3);
    v0 = lw(a0 + 28);
    tail(v0.u());
}

// RwCameraBeginUpdate(camera): a `jr` tail call through camera +24 (CameraBeginUpdate).
void Cpu::RwCameraBeginUpdate() {
    enter(3);
    v0 = lw(a0 + 24);
    tail(v0.u());
}

// RwCameraClear(camera, colour, mode): the device's camera-clear standard function (0x96010C); returns the camera,
// or 0 when the device call failed.
void Cpu::RwCameraClear() {
    enter(13);
    sp = addiu(sp, -32);
    v0 = lui(0x96);
    sd(sp + 16, ra);
    sq(sp, s0);
    v0 = lw(v0 + 268);
    s0 = a0;
    jalr(0x4C9EA4u, v0.u());
    if (v0 == 0) s0 = zero;  // movz
    v0 = s0;
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 32);
}

// RwCameraShowRaster(camera, dev, flags): RwRasterShowRaster(camera +96 = the frame buffer, dev, flags); returns the
// camera or 0.
void Cpu::RwCameraShowRaster() {
    enter(12);
    sp = addiu(sp, -32);
    sd(sp + 16, ra);
    sq(sp, s0);
    s0 = a0;
    a0 = lw(a0 + 96);
    jal(0x4C9EE0u, gen::fn_RwRasterShowRaster_004cdfe0);
    if (v0 == 0) s0 = zero;  // movz
    v0 = s0;
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 32);
}

// sub_4CB2F0 [RwFrameGetLTM(frame)]: when the hierarchy root (frame +160) has its "dirty" bit (root +3 bit 0),
// sub_4CF4C0(root) brings the LTMs up to date; returns frame + 80 (the LTM).
void Cpu::sub_4CB2F0() {
    enter(9);
    sp = addiu(sp, -32);
    sd(sp + 16, ra);
    sq(sp, s0);
    s0 = a0;
    a0 = lw(a0 + 160);
    v0 = lbu(a0 + 3);
    v0 = v0 & 1;
    if (v0 != 0) {
        charge(4);
        jal(0x4CB31Cu, gen::fn_sub_4CF4C0_004cf4c0);
        backedge();
    }
    charge(2);
    v0 = addiu(s0, 80);
    charge(4);
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 32);
}

// sub_4CB7F0 [RwFrameTransform-like: matrix + mark dirty]: sub_4C3760(frame +16 the modelling matrix, $a1, $a2);
// a root not yet dirty (root +3 & 3 == 0) is linked at the head of the dirty-frame list (0x96012C, through root +8);
// then root +3 |= 3 and frame +3 |= 0xC. Returns the frame.
void Cpu::sub_4CB7F0() {
    enter(11);
    sp = addiu(sp, -32);
    sd(sp + 16, ra);
    sq(sp, s0);
    s0 = a0;
    a0 = addiu(s0, 16);
    jal(0x4CB800u, gen::fn_sub_4C3760_004c3760);
    v1 = lw(s0 + 160);
    a1 = lbu(v1 + 3);
    v0 = a1 & 3;
    if (v0 == 0) {
        charge(14);
        a0 = lui(0x96);
        a0 = addiu(a0, 300);  // the dirty-frame list head
        v0 = lw(a0);
        sw(v1 + 8, v0);
        v0 = lw(s0 + 160);
        sw(v0 + 12, a0);
        v1 = lw(s0 + 160);
        v0 = lw(a0);
        v1 = addiu(v1, 8);
        sw(v0 + 4, v1);
        v0 = lw(s0 + 160);
        v0 = addiu(v0, 8);
        sw(a0, v0);
        backedge();
    }
    charge(8);
    v1 = lw(s0 + 160);
    a0 = a1 | 3;
    v0 = s0;
    sb(v1 + 3, a0);
    v1 = lbu(s0 + 3);
    v1 = v1 | 0xC;
    sb(s0 + 3, v1);
    charge(4);
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 32);
}

// A device standard function called as fn(a0, a1, 0) with the two arguments kept in $s0 / $s1 (48-byte frame); the
// caller's follow-up runs on success, 0 is returned on failure. Shared prologue of sub_4CDC70 / sub_4CDCE0.
bool Cpu::std_call2(s32 off, u32 pc) {
    enter(12);
    sp = addiu(sp, -48);
    v0 = lui(0x96);
    sd(sp + 32, ra);
    a2 = zero;
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = a1;
    v0 = lw(v0 + off);
    s0 = a0;
    jalr(pc, v0.u());
    return v0 != 0;
}
void Cpu::std_call2_exit() {
    charge(5);
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}

// sub_4CDC70 [RwRasterSetFromImage-like (raster, image)]: the device's standard function 6 (0x9600D0); on success,
// image +34 bit 0 sets raster +0 bit 1. Returns the raster or 0.
void Cpu::sub_4CDC70() {
    if (!std_call2(208, 0x4CDC90u)) {
        charge(1);
        v0 = zero;
    } else {
        charge(4);
        v0 = lbu(s1 + 34);
        v0 = v0 & 1;
        if (v0 != 0) {
            charge(4);
            v0 = lw(s0);
            v0 = v0 | 2;
            sw(s0, v0);
            backedge();
        }
        charge(2);
        v0 = s0;
    }
    std_call2_exit();
}

// sub_4CDCE0 [RwImageSetFromRaster-like (image, raster)]: standard function 7 (0x9600D4); on success, raster +0
// bit 1 sets image +34 bit 0. Returns the image or 0.
void Cpu::sub_4CDCE0() {
    if (!std_call2(212, 0x4CDD00u)) {
        charge(1);
        v0 = zero;
    } else {
        charge(4);
        v0 = lw(s1);
        v0 = v0 & 2;
        if (v0 != 0) {
            charge(4);
            v0 = lbu(s0 + 34);
            v0 = v0 | 1;
            sb(s0 + 34, v0);
            backedge();
        }
        charge(2);
        v0 = s0;
    }
    std_call2_exit();
}

// sub_4CDD50 [RwImageFindRasterFormat-like (image, type, &width, &height, &depth, &format)]: standard function 9
// (0x9600DC) fills a raster template in the 160-byte frame (sp + 96); on success width / height / depth (+12 / +16
// / +20) and the format (+32 | +35 << 8) are stored through the four pointers ($a2, $a3, $t0, $t1). Returns the
// image or 0.
void Cpu::sub_4CDD50() {
    enter(20);
    sp = addiu(sp, -160);
    v0 = lui(0x96);
    sd(sp + 80, ra);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    s4 = a0;
    sq(sp + 32, s2);
    s3 = a2;
    sq(sp + 16, s1);
    a2 = a1;
    sq(sp, s0);
    s2 = a3;
    v0 = lw(v0 + 220);
    s1 = t0;
    s0 = t1;
    a0 = addiu(sp, 96);
    a1 = s4;
    jalr(0x4CDD90u, v0.u());
    if (v0 == 0) {
        charge(2);
        v0 = zero;
    } else {
        charge(12);
        a0 = lbu(sp + 131);
        v0 = s4;
        v1 = lbu(sp + 128);
        a0 = sll(a0, 8);
        v1 = a0 | v1;
        sw(s0, v1);
        v1 = lw(sp + 108);
        sw(s3, v1);
        v1 = lw(sp + 112);
        sw(s2, v1);
        v1 = lw(sp + 116);
        sw(s1, v1);
    }
    charge(8);
    ra = ld(sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 160);
}

// sub_4CDE00 [RwRasterUnlock(raster)]: the device's raster-unlock standard function (0x9600F8) as fn(0, raster, 0);
// returns the raster.
void Cpu::sub_4CDE00() {
    enter(15);
    sp = addiu(sp, -32);
    v0 = lui(0x96);
    sd(sp + 16, ra);
    a2 = zero;
    sq(sp, s0);
    v0 = lw(v0 + 248);
    s0 = a0;
    a0 = zero;
    a1 = s0;
    jalr(0x4CDE20u, v0.u());
    v0 = s0;
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 32);
}

// RwRasterShowRaster(raster, dev, flags): the resource purge sub_4C4890, then the device's show-raster standard
// function (0x960108, read before the purge) with the three arguments; returns the raster or 0.
void Cpu::RwRasterShowRaster() {
    enter(25);
    sp = addiu(sp, -80);
    v0 = lui(0x96);
    sd(sp + 64, ra);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    s3 = a0;
    sq(sp + 16, s1);
    s2 = a1;
    sq(sp, s0);
    s0 = lw(v0 + 264);
    s1 = a2;
    jal(0x4CE008u, gen::fn_sub_4C4890_004c4890);
    a1 = s2;
    a2 = s1;
    a0 = s3;
    jalr(0x4CE018u, s0.u());
    if (v0 == 0) s3 = zero;  // movz
    v0 = s3;
    ra = ld(sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 80);
}

// sub_4CE050 [RwRasterSubRaster(raster, parent, rect)]: only for a raster without its own pixels (+33 bit 7):
// width / height from rect +8 / +12, the offsets (+28 / +30, s16) = the parent's + rect x / y, then the device's
// sub-raster standard function (0x9600E8) as fn(raster, parent, 0); on success raster +0 = parent +0. Returns the
// raster or 0.
void Cpu::sub_4CE050() {
    enter(9);
    sp = addiu(sp, -48);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = a0;
    v0 = lbu(a0 + 33);
    v0 = v0 & 0x80;
    s0 = a1;
    if (v0 == 0) {
        charge(2);
        v0 = zero;
    } else {
        charge(18);
        v1 = lw(a2 + 8);
        v0 = lui(0x96);
        sw(s1 + 12, v1);
        v1 = lw(a2 + 12);
        sw(s1 + 16, v1);
        a3 = lh(s0 + 28);
        v1 = lh(a2);
        v1 = addu(a3, v1);
        sh(s1 + 28, v1);
        v1 = lh(a2 + 4);
        a3 = lh(s0 + 30);
        v1 = addu(a3, v1);
        sh(s1 + 30, v1);
        v0 = lw(v0 + 232);
        a2 = zero;
        jalr(0x4CE0B4u, v0.u());
        if (v0 == 0) {
            charge(2);
            v0 = zero;
        } else {
            charge(3);
            v1 = lw(s0);
            v0 = s1;
            sw(s1, v1);
        }
    }
    charge(5);
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}

// sub_4CE200 [RwRasterLock(raster, level, flags)]: the device's raster-lock standard function (0x9600F4) as
// fn(&pixels at sp + 28, raster, flags + (level & 0xFF) << 8); returns the pixel pointer or 0.
void Cpu::sub_4CE200() {
    enter(13);
    sp = addiu(sp, -32);
    v0 = a1 & 0xFF;
    v0 = sll(v0, 8);
    v1 = a0;
    a2 = addu(a2, v0);
    sd(sp, ra);
    v0 = lui(0x96);
    a0 = addiu(sp, 28);
    v0 = lw(v0 + 244);
    a1 = v1;
    jalr(0x4CE224u, v0.u());
    if (v0 == 0) {
        charge(1);
        v0 = zero;
    } else {
        charge(2);
        v0 = lw(sp + 28);
    }
    charge(3);
    ra = ld(sp);
    sp = addiu(sp, 32);
}

// The LTM of one frame from its parent's: ltm = sub_4C2F30(frame +80 out, frame +16 modelling, parent(+4) +80), then
// the frame's +3 bit 2 cleared (re-read through `flags_reg` = frame + 3). Charged by the caller's block.
void Cpu::frame_ltm(const Gpr& f, Gpr& flags_reg, Gpr& t, Gpr& u, u32 pc) {
    charge(10);
    v0 = lw(f + 4);
    a0 = addiu(f, 80);
    a1 = addiu(f, 16);
    a2 = addiu(v0, 80);
    jal(pc, gen::fn_sub_4C2F30_004c2f30);
    t = lbu(flags_reg);
    u = si(-5);
    u = t & u;
    sb(f + 3, u);
}

// sub_4CF3B0 [_rwFrameSyncHierarchyLTM: siblings and children]: $a0 a frame, $a1 the inherited dirty flags. For the
// frame and each sibling (+156): flags |= +3; with bit 2 the LTM is rebuilt from the parent; then every child (+152)
// gets the same treatment one level down (the grandchildren through a recursive call).
void Cpu::sub_4CF3B0() {
    enter(11);
    sp = addiu(sp, -112);
    sd(sp + 96, ra);
    sq(sp + 80, s5);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = a0;
    s0 = a1;
    if (s1 != 0) {
        for (;;) {
            charge(5);
            v1 = lbu(s1 + 3);
            s3 = s0 | v1;
            v1 = s3 & 4;
            s2 = addiu(s1, 3);
            if (v1 != 0) {
                frame_ltm(s1, s2, a0, v1, 0x4CF454u);
                backedge();
            }
            charge(3);
            s5 = lw(s1 + 152);  // the first child
            if (s5 != 0) {
                charge(1);
                for (;;) {
                    charge(5);
                    v0 = lbu(s5 + 3);
                    s4 = s3 | v0;
                    v0 = s4 & 4;
                    s2 = addiu(s5, 3);
                    if (v0 != 0) {
                        frame_ltm(s5, s2, v1, v0, 0x4CF47Cu);
                        backedge();
                    } else {
                        charge(1);
                    }
                    charge(6);
                    a0 = lw(s5 + 152);
                    a1 = s4;
                    jal(0x4CF41Cu, gen::fn_sub_4CF3B0_004cf3b0);
                    s5 = lw(s5 + 156);
                    if (s5 == 0) break;
                    backedge();
                }
            }
            charge(3);
            s1 = lw(s1 + 156);  // the next sibling
            if (s1 == 0) break;
            backedge();
        }
        charge(1);
    }
    charge(2);
    charge(9);
    ra = ld(sp + 96);
    lq(s5, sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 112);
}

// sub_4CF4C0 [_rwFrameSyncHierarchyLTM(root)]: a dirty root (+3 bit 2) copies its modelling matrix into its LTM;
// each child gets its LTM rebuilt when dirty, then its own children through sub_4CF3B0; finally root +3 &= ~5.
void Cpu::sub_4CF4C0() {
    enter(11);
    sp = addiu(sp, -96);
    sd(sp + 80, ra);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = lbu(a0 + 3);
    v1 = s1 & 4;
    s4 = a0;
    if (v1 != 0) {
        charge(3);
        a3 = addiu(s4, 16);
        a2 = addiu(s4, 80);
        copy_matrix(a1, a3, a2, a0, v1, true);
        charge(2);
        s3 = lw(s4 + 152);
        backedge();
    } else {
        charge(1);
        s3 = lw(s4 + 152);
    }
    charge(2);
    if (s3 != 0) {
        for (;;) {
            charge(5);
            v0 = lbu(s3 + 3);
            s2 = s1 | v0;
            v0 = s2 & 4;
            s0 = addiu(s3, 3);
            if (v0 != 0) {
                frame_ltm(s3, s0, v1, v0, 0x4CF578u);
                backedge();
            } else {
                charge(1);
            }
            charge(6);
            a0 = lw(s3 + 152);
            a1 = s2;
            jal(0x4CF514u, gen::fn_sub_4CF3B0_004cf3b0);
            s3 = lw(s3 + 156);
            if (s3 == 0) break;
            backedge();
        }
    }
    charge(4);
    v1 = si(-6);
    v1 = s1 & v1;
    sb(s4 + 3, v1);
    charge(8);
    ra = ld(sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 96);
}

// sub_4D0FD0 [RwTextureSetName(texture, name)]: strncpy(texture +16, name, 32) (the string table at 0x960140); a
// name of 32 characters or more (strlen, 0x960164) is an RWERROR (0x8000001E, name, 32, 31) and the last byte (+47)
// is cleared. Returns the texture.
void Cpu::sub_4D0FD0() {
    enter(18);
    sp = addiu(sp, -64);
    v0 = lui(0x96);
    sd(sp + 32, ra);
    a2 = 0x20;
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = a0;
    v0 = lw(v0 + 320);
    s0 = a1;
    a0 = addiu(s1, 16);
    jalr(0x4D0FF4u, v0.u());
    v0 = lui(0x96);
    v0 = lw(v0 + 356);
    a0 = s0;
    jalr(0x4D1004u, v0.u());
    at = sltiu(v0, 32);
    if (at == 0) {
        charge(14);
        t0 = lb(s0 + 31);
        v0 = 1;
        sw(sp + 56, v0);
        a1 = s0;
        v0 = lui(0x8000);
        a2 = 0x20;
        a0 = v0 | 0x1E;
        a3 = 0x1F;
        rwerror(0x4D103Cu, 56);
        sb(s1 + 47, zero);
        backedge();
    }
    charge(2);
    v0 = s1;
    charge(5);
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 64);
}

// sub_4D13E0 [RwTextureRasterValid-like]: a call through the texture module's function table (+44 of the plugin
// block at gp-17312) with the caller's arguments; returns its result as 0 / 1.
void Cpu::sub_4D13E0() {
    enter(13);
    sp = addiu(sp, -16);
    v0 = lui(0x96);
    sd(sp, ra);
    v0 = addiu(v0, 112);
    v1 = lw(gp - 17312);
    v0 = addu(v0, v1);
    v0 = lw(v0 + 44);
    jalr(0x4D13FCu, v0.u());
    ra = ld(sp);
    v0 = sltu(zero, v0);
    sp = addiu(sp, 16);
}

// The register pattern of the compiled reciprocal guard: when not ($f`v` <= 0) ($f`v` = 1 / $f`v` through $f`one`).
void Cpu::recip_unless_le0(unsigned v, unsigned one) {
    if (!cop1_cond()) {
        charge(7);
        v0 = lui(0x3F80);
        mtc1(v0, one);
        div_s(v, one, v);
    }
}

// sub_4C2330 [RwMatrixOrthoNormalize(dst, src)]: the right / up / at rows of `src` normalised (a zero length keeps
// the row), then the row most orthogonal to the other two (the smallest absolute dot product, with zero-length rows
// rebuilt first) is replaced by the cross product of the other two (normalised), and the third by the cross of that
// and the first; pos copied. The rows live in the 64-byte frame: right sp+48, up sp+32, at sp+16, pos sp+0. dst flags
// (+12) get bits 0..1 and lose 0x20000.
void Cpu::sub_4C2330() {
    enter(39);
    sp = addiu(sp, -64);
    lwc1(F0, a1 + 4);
    t1 = addiu(sp, 52);
    lwc1(F2, a1 + 32);
    t0 = addiu(sp, 56);
    lwc1(F1, a1 + 8);
    lwc1(F6, a1);
    lwc1(F5, a1 + 16);
    lwc1(F4, a1 + 20);
    swc1(F0, sp + 52);
    lwc1(F0, a1 + 36);
    swc1(F2, sp + 16);
    lwc1(F2, t1);
    swc1(F1, sp + 56);
    lwc1(F3, a1 + 24);
    lwc1(F1, a1 + 40);
    swc1(F0, sp + 20);
    lwc1(F0, t0);
    mula_s(F2, F2);
    madda_s(F6, F6);
    swc1(F5, sp + 32);
    swc1(F4, sp + 36);
    swc1(F3, sp + 40);
    madd_s(F0, F0, F0);
    sqrt_s(F0, F0);  // |right|
    lwc1(F5, a1 + 48);
    lwc1(F4, a1 + 52);
    lwc1(F3, a1 + 56);
    swc1(F1, sp + 24);
    mtc1(zero, F1);
    swc1(F6, sp + 48);
    swc1(F5, sp);
    swc1(F4, sp + 4);
    swc1(F3, sp + 8);
    c_le_s(F0, F1);
    recip_unless_le0(F0, F1);
    // right *= 1 / |right|; |up|
    charge(24);
    a3 = addiu(sp, 36);
    a2 = addiu(sp, 40);
    lwc1(F4, a3);
    lwc1(F1, sp + 32);
    lwc1(F3, a2);
    lwc1(F7, sp + 48);
    lwc1(F6, t1);
    lwc1(F5, t0);
    mula_s(F4, F4);
    madda_s(F1, F1);
    madd_s(F1, F3, F3);
    sqrt_s(F10, F1);
    mul_s(F3, F6, F0);
    swc1(F3, t1);
    mul_s(F7, F7, F0);
    mul_s(F3, F5, F0);
    mtc1(zero, F2);
    swc1(F7, sp + 48);
    swc1(F3, t0);
    c_le_s(F10, F2);
    recip_unless_le0(F10, F1);
    // up *= 1 / |up|; |at|
    charge(24);
    a1 = addiu(sp, 20);
    v1 = addiu(sp, 24);
    lwc1(F4, a1);
    lwc1(F1, sp + 16);
    lwc1(F3, v1);
    lwc1(F6, a3);
    lwc1(F7, sp + 32);
    lwc1(F5, a2);
    mula_s(F4, F4);
    madda_s(F1, F1);
    madd_s(F1, F3, F3);
    mul_s(F3, F6, F10);
    swc1(F3, a3);
    mul_s(F3, F5, F10);
    sqrt_s(F5, F1);
    mul_s(F7, F7, F10);
    mtc1(zero, F2);
    swc1(F7, sp + 32);
    swc1(F3, a2);
    c_le_s(F5, F2);
    recip_unless_le0(F5, F1);
    // at *= 1 / |at|
    charge(13);
    lwc1(F4, sp + 16);
    lwc1(F3, a1);
    lwc1(F2, v1);
    mtc1(zero, F1);
    c_le_s(F0, F1);
    mul_s(F4, F4, F5);
    mul_s(F9, F3, F5);
    mul_s(F8, F2, F5);
    swc1(F4, sp + 16);
    swc1(F9, a1);
    swc1(F8, v1);
    // which row is rebuilt: v1 = the row replaced by a2 x a1
    auto rows = [&](u64 cost, s32 r2, s32 r1, s32 rv) {
        charge(cost);
        a2 = addiu(sp, r2);
        a1 = addiu(sp, r1);
        v1 = addiu(sp, rv);
    };
    if (cop1_cond()) {  // |right| was 0: right = up x at
        rows(3, 32, 16, 48);
    } else {
        charge(3);
        c_le_s(F10, F1);
        if (cop1_cond()) {  // |up| was 0: up = at x right
            rows(4, 16, 48, 32);
        } else {
            charge(3);
            c_le_s(F5, F1);
            if (cop1_cond()) {  // |at| was 0: at = right x up
                rows(4, 48, 32, 16);
            } else {
                // |right . at| in $f10, |right . up| in $f4, |up . at| in $f0
                charge(11);
                lwc1(F7, a3);
                lwc1(F2, sp + 32);
                lwc1(F5, a2);
                mul_s(F0, F7, F9);
                adda_s(F1, F0);
                madd_s(F0, F2, F4);
                adda_s(F1, F0);
                madd_s(F10, F5, F8);
                c_lt_s(F10, F1);
                charge(2);
                if (cop1_cond()) neg_s(F10, F10);
                lwc1(F6, t1);
                charge(9);
                lwc1(F1, sp + 48);
                lwc1(F3, t0);
                mtc1(zero, F0);
                mula_s(F9, F6);
                madda_s(F4, F1);
                madd_s(F4, F8, F3);
                c_lt_s(F4, F0);
                charge(2);
                if (cop1_cond()) neg_s(F4, F4);
                mula_s(F6, F7);
                charge(6);
                madda_s(F1, F2);
                mtc1(zero, F1);
                madd_s(F0, F3, F5);
                c_lt_s(F0, F1);
                if (cop1_cond()) {
                    charge(1);
                    neg_s(F0, F0);
                } else {
                    charge(2);
                }
                charge(3);
                c_lt_s(F10, F4);
                if (cop1_cond()) {
                    charge(3);
                    c_lt_s(F10, F0);
                    if (cop1_cond())
                        rows(4, 32, 16, 48);
                    else
                        rows(4, 48, 32, 16);
                } else {
                    charge(3);
                    c_lt_s(F4, F0);
                    if (cop1_cond())
                        rows(4, 16, 48, 32);
                    else
                        rows(4, 48, 32, 16);
                }
            }
        }
    }
    // v1 = a2 x a1, normalised
    charge(34);
    lwc1(F1, a2 + 4);
    lwc1(F0, a1 + 8);
    lwc1(F3, a2 + 8);
    lwc1(F2, a1 + 4);
    mtc1(zero, F4);
    mula_s(F1, F0);
    msub_s(F0, F3, F2);
    swc1(F0, v1);
    lwc1(F1, a2 + 8);
    lwc1(F0, a1);
    lwc1(F3, a2);
    lwc1(F2, a1 + 8);
    mula_s(F1, F0);
    msub_s(F0, F3, F2);
    swc1(F0, v1 + 4);
    lwc1(F1, a2);
    lwc1(F0, a1 + 4);
    lwc1(F3, a2 + 4);
    lwc1(F2, a1);
    mula_s(F1, F0);
    msub_s(F0, F3, F2);
    swc1(F0, v1 + 8);
    lwc1(F2, v1 + 4);
    lwc1(F1, v1);
    lwc1(F0, v1 + 8);
    mula_s(F2, F2);
    madda_s(F1, F1);
    madd_s(F0, F0, F0);
    sqrt_s(F1, F0);
    c_le_s(F1, F4);
    recip_unless_le0(F1, F0);
    // a1 = v1 x a2, normalised
    charge(42);
    lwc1(F0, v1);
    mtc1(zero, F4);
    mul_s(F0, F0, F1);
    swc1(F0, v1);
    lwc1(F0, v1 + 4);
    mul_s(F0, F0, F1);
    swc1(F0, v1 + 4);
    lwc1(F0, v1 + 8);
    mul_s(F3, F0, F1);
    swc1(F3, v1 + 8);
    lwc1(F1, v1 + 4);
    lwc1(F0, a2 + 8);
    lwc1(F2, a2 + 4);
    mula_s(F1, F0);
    msub_s(F0, F3, F2);
    swc1(F0, a1);
    lwc1(F1, v1 + 8);
    lwc1(F0, a2);
    lwc1(F3, v1);
    lwc1(F2, a2 + 8);
    mula_s(F1, F0);
    msub_s(F0, F3, F2);
    swc1(F0, a1 + 4);
    lwc1(F1, v1);
    lwc1(F0, a2 + 4);
    lwc1(F3, v1 + 4);
    lwc1(F2, a2);
    mula_s(F1, F0);
    msub_s(F0, F3, F2);
    swc1(F0, a1 + 8);
    lwc1(F2, a1 + 4);
    lwc1(F1, a1);
    lwc1(F0, a1 + 8);
    mula_s(F2, F2);
    madda_s(F1, F1);
    madd_s(F0, F0, F0);
    sqrt_s(F5, F0);
    c_le_s(F5, F4);
    recip_unless_le0(F5, F0);
    // the rows and pos into dst
    charge(42);
    lwc1(F3, a1);
    v0 = lui(0xFFFD);
    v1 = v0 | 0xFFFF;
    lwc1(F2, sp);
    v0 = a0;
    lwc1(F1, sp + 4);
    lwc1(F0, sp + 8);
    mul_s(F3, F3, F5);
    swc1(F3, a1);
    lwc1(F3, a1 + 4);
    mul_s(F3, F3, F5);
    swc1(F3, a1 + 4);
    lwc1(F3, a1 + 8);
    mul_s(F3, F3, F5);
    swc1(F3, a1 + 8);
    for (unsigned row = 0; row < 3; ++row) {  // right (sp+48), up (sp+32), at (sp+16) -> dst +0 / +16 / +32
        const s32 from = 48 - 16 * static_cast<s32>(row);
        lwc1(F5, sp + from);
        lwc1(F4, sp + from + 4);
        lwc1(F3, sp + from + 8);
        swc1(F5, a0 + 16 * row);
        swc1(F4, a0 + 16 * row + 4);
        swc1(F3, a0 + 16 * row + 8);
    }
    swc1(F2, a0 + 48);
    swc1(F1, a0 + 52);
    swc1(F0, a0 + 56);
    a1 = lw(a0 + 12);
    a1 = a1 | 3;
    v1 = a1 & v1;
    sw(a0 + 12, v1);
    sp = addiu(sp, 64);
}

// The unsigned-to-float idiom of the compiled byte loads: $f`fd` = (float)`val` through $f`fs` (a "negative" value
// -- never for a byte -- is halved with its low bit kept in `tmp`, converted and doubled). Charges its own block.
void Cpu::u2f(Gpr& val, Gpr& tmp, unsigned fd, unsigned fs) {
    if (sgn(val) < 0) {
        charge(7);
        tmp = srl(val, 1);
        val = val & 1;
        tmp = tmp | val;
        mtc1(tmp, fs);
        cvt_s_w(fd, fs);
        add_s(fd, fd, fd);
    } else {
        charge(3);
        mtc1(val, fs);
        cvt_s_w(fd, fs);
    }
}

// One byte channel of a pixel scaled by 1/255 (0x3B808081) into out + off: the block after a u2f into $f2.
void Cpu::channel_store(Gpr& k, const Gpr& out, s32 off) {
    charge(9);
    k = lui(0x3B80);
    k = k | 0x8081;  // 0x3B808081: 1 / 255
    mtc1(k, F0);
    mul_s(F0, F0, F2);
    swc1(F0, out + off);
}

// The four floats at t0 (+0..+12) multiplied by $f`f`, through $f`tmp`.
void Cpu::scale4(const Gpr& p, unsigned f, unsigned tmp) {
    for (unsigned k = 0; k < 4; ++k) {
        lwc1(tmp, p + 4 * k);
        mul_s(tmp, tmp, f);
        swc1(tmp, p + 4 * k);
    }
}

// sub_4CE3A0 [image resample: one row's box sample]: $a0 the image (+16 stride, +20 pixels, RGBA8), $a1 / $a2 the
// span [x0, x1) in 16.16, $a3 the row (16.16, integer part used), $t0 the RGBA float accumulator out. The first
// partial pixel is weighted by its covered fraction, whole pixels by 1, the last partial pixel by its fraction; the
// sum is divided by the span width (x1 - x0) / 65536. Channels are bytes / 255.
void Cpu::sub_4CE3A0() {
    enter(16);
    t1 = subu(a2, a1);
    v1 = lui(0x3780);  // 1 / 65536
    mtc1(t1, F1);
    a3 = sra(a3, 16);
    mtc1(v1, F0);
    t2 = sra(a1, 16);
    cvt_s_w(F1, F1);
    v1 = lw(a0 + 16);
    mul_s(F1, F0, F1);  // the span width in pixels
    mult(t1, a3, v1);
    a3 = lw(a0 + 20);
    v1 = sll(t2, 2);
    a3 = addu(a3, t1);
    a0 = sra(a2, 16);
    v1 = addu(a3, v1);  // the first pixel
    if (t2 == a0) {
        // the whole span inside one pixel: its colour, times the width, divided by it below
        charge(3);
        a0 = lbu(v1);
        u2f(a0, a1, F2, F0);
        channel_store(a0, t0, 0);
        a0 = lbu(v1 + 1);
        u2f(a0, a1, F2, F0);
        channel_store(a0, t0, 4);
        a0 = lbu(v1 + 2);
        u2f(a0, a1, F2, F0);
        channel_store(a0, t0, 8);
        v1 = lbu(v1 + 3);
        u2f(v1, a0, F2, F0);
        charge(18);
        v1 = lui(0x3B80);
        v1 = v1 | 0x8081;  // 0x3B808081: 1 / 255
        mtc1(v1, F0);
        mul_s(F0, F0, F2);
        swc1(F0, t0 + 12);
        scale4(t0, F1, F0);
    } else {
        // the first partial pixel, weighted by (next pixel - x0)
        charge(4);
        t1 = lbu(v1);
        a3 = addiu(t2, 1);
        a3 = sll(a3, 16);
        u2f(t1, t2, F2, F0);
        channel_store(t1, t0, 0);
        t1 = lbu(v1 + 1);
        u2f(t1, t2, F2, F0);
        channel_store(t1, t0, 4);
        t1 = lbu(v1 + 2);
        u2f(t1, t2, F2, F0);
        channel_store(t1, t0, 8);
        t1 = lbu(v1 + 3);
        u2f(t1, t2, F3, F0);
        charge(27);
        a1 = subu(a3, a1);
        t3 = sra(a3, 16);
        mtc1(a1, F2);
        v1 = addiu(v1, 4);
        cvt_s_w(F4, F2);
        a1 = lui(0x3B80);
        t1 = a1 | 0x8081;  // 0x3B808081: 1 / 255
        a1 = lui(0x3780);
        mtc1(t1, F0);
        mul_s(F2, F0, F3);
        swc1(F2, t0 + 12);
        mtc1(a1, F3);
        lwc1(F2, t0);
        mul_s(F3, F3, F4);
        for (unsigned k = 0; k < 4; ++k) {
            if (k) lwc1(F2, t0 + 4 * k);
            mul_s(F2, F2, F3);
            swc1(F2, t0 + 4 * k);
        }
        if (t3 == a0) {
            charge(1);
            a0 = lbu(v1);
        } else {
            // the whole pixels: the channels added with weight 1 (red through ACC: 0 + 1/255 * r)
            charge(2);
            mtc1(zero, F3);
            a1 = lui(0x1);
            for (;;) {
                charge(3);
                t1 = lbu(v1 + 1);
                u2f(t1, t2, F2, F2);
                charge(3);
                t1 = lbu(v1 + 2);
                mul_s(F5, F0, F2);
                u2f(t1, t2, F2, F2);
                charge(3);
                t1 = lbu(v1 + 3);
                mul_s(F6, F0, F2);
                u2f(t1, t2, F2, F2);
                charge(3);
                t1 = lbu(v1);
                mul_s(F7, F0, F2);
                u2f(t1, t2, F4, F2);
                charge(17);
                lwc1(F2, t0);
                t3 = addiu(t3, 1);
                v1 = addiu(v1, 4);
                a3 = addu(a3, a1);
                adda_s(F3, F2);
                madd_s(F2, F0, F4);
                swc1(F2, t0);
                lwc1(F2, t0 + 4);
                add_s(F2, F2, F5);
                swc1(F2, t0 + 4);
                lwc1(F2, t0 + 8);
                add_s(F2, F2, F6);
                swc1(F2, t0 + 8);
                lwc1(F2, t0 + 12);
                add_s(F2, F2, F7);
                swc1(F2, t0 + 12);
                if (t3 == a0) break;
                backedge();
            }
            charge(2);
            a0 = lbu(v1);
        }
        // the last partial pixel, weighted by (x1 - its start)
        charge(2);
        u2f(a0, a1, F2, F0);
        charge(6);
        a1 = lui(0x3B80);
        a0 = lbu(v1 + 1);
        a1 = a1 | 0x8081;  // 0x3B808081: 1 / 255
        mtc1(a1, F0);
        mul_s(F4, F0, F2);
        u2f(a0, a1, F2, F0);
        charge(6);
        a1 = lui(0x3B80);
        a0 = lbu(v1 + 2);
        a1 = a1 | 0x8081;  // 0x3B808081: 1 / 255
        mtc1(a1, F0);
        mul_s(F7, F0, F2);
        u2f(a0, a1, F2, F0);
        charge(6);
        a0 = lui(0x3B80);
        v1 = lbu(v1 + 3);
        a0 = a0 | 0x8081;  // 0x3B808081: 1 / 255
        mtc1(a0, F0);
        mul_s(F8, F0, F2);
        u2f(v1, a0, F3, F0);
        charge(27);
        v1 = lui(0x3B80);
        a0 = subu(a2, a3);
        a1 = v1 | 0x8081;  // 0x3B808081: 1 / 255
        mtc1(a1, F2);
        v1 = lui(0x3780);
        mtc1(a0, F0);
        mul_s(F6, F2, F3);
        cvt_s_w(F3, F0);
        mtc1(v1, F2);
        lwc1(F0, t0);
        mul_s(F5, F2, F3);
        mul_s(F2, F4, F5);
        add_s(F0, F0, F2);
        swc1(F0, t0);
        lwc1(F0, t0 + 4);
        mul_s(F4, F7, F5);
        add_s(F0, F0, F4);
        swc1(F0, t0 + 4);
        lwc1(F0, t0 + 8);
        mul_s(F3, F8, F5);
        add_s(F0, F0, F3);
        swc1(F0, t0 + 8);
        lwc1(F0, t0 + 12);
        mul_s(F2, F6, F5);
        add_s(F0, F0, F2);
        swc1(F0, t0 + 12);
        backedge();
    }
    // divided by the span width
    charge(16);
    v1 = lui(0x3F80);
    mtc1(v1, F2);
    lwc1(F0, t0);
    div_s(F1, F2, F1);
    scale4(t0, F1, F0);
    charge(2);
}

// sub_4CE9A0 [image resample: one output pixel's box sample]: $a0 the image, $a1 / $a2 the x span (16.16), $a3 / $t0
// the y span [y0, y1) (16.16), $t1 the RGBA float result. Rows are sampled through sub_4CE3A0: the first partial row
// weighted by its covered fraction, whole rows by 1 (into the 16-byte frame buffer at sp + 80, then added), the last
// partial row by its fraction; the sum divided by the y extent.
void Cpu::sub_4CE9A0() {
    enter(21);
    sp = addiu(sp, -96);
    t6 = t0;
    sd(sp + 64, ra);
    v1 = lui(0x3780);
    sq(sp + 48, s3);
    mtc1(v1, F0);
    sq(sp + 32, s2);
    t4 = sra(t6, 16);
    sq(sp + 16, s1);
    t5 = t1;
    sq(sp, s0);
    t8 = a0;
    s0 = a3;
    t7 = a1;
    t0 = subu(t6, s0);
    v1 = sra(s0, 16);
    mtc1(t0, F1);
    cvt_s_w(F1, F1);
    mul_s(F9, F0, F1);  // the y extent in rows
    if (v1 == t4) {
        // one row: its sample times the extent
        charge(14);
        t0 = t5;
        jal(0x4CEAD0u, gen::fn_sub_4CE3A0_004ce3a0);
        scale4(t5, F9, F0);
    } else {
        // the first partial row
        charge(25);
        v1 = addiu(v1, 1);
        t0 = t5;
        s3 = sll(v1, 16);
        jal(0x4CE9FCu, gen::fn_sub_4CE3A0_004ce3a0);
        a0 = subu(s3, s0);
        v1 = lui(0x3780);
        mtc1(a0, F1);
        s2 = sra(s3, 16);
        mtc1(v1, F0);
        cvt_s_w(F1, F1);
        mul_s(F1, F0, F1);
        scale4(t5, F1, F0);
        if (s2 == t4) {
            charge(1);
            a0 = t8;
        } else {
            charge(3);
            s1 = addiu(sp, 84);
            s0 = addiu(sp, 88);
            t9 = addiu(sp, 92);
            for (;;) {  // the whole rows
                charge(25);
                a0 = t8;
                a1 = t7;
                a3 = s3;
                t0 = addiu(sp, 80);
                jal(0x4CEA70u, gen::fn_sub_4CE3A0_004ce3a0);
                lwc1(F1, t5);
                v1 = lui(0x1);
                lwc1(F0, sp + 80);
                s2 = addiu(s2, 1);
                s3 = addu(s3, v1);
                add_s(F0, F1, F0);
                swc1(F0, t5);
                lwc1(F1, t5 + 4);
                lwc1(F0, s1);
                add_s(F0, F1, F0);
                swc1(F0, t5 + 4);
                lwc1(F1, t5 + 8);
                lwc1(F0, s0);
                add_s(F0, F1, F0);
                swc1(F0, t5 + 8);
                lwc1(F1, t5 + 12);
                lwc1(F0, t9);
                add_s(F0, F1, F0);
                swc1(F0, t5 + 12);
                if (s2 == t4) break;
                backedge();
            }
            charge(2);
            a0 = t8;
        }
        // the last partial row
        charge(41);
        a1 = t7;
        a3 = s3;
        t0 = addiu(sp, 80);
        jal(0x4CEB54u, gen::fn_sub_4CE3A0_004ce3a0);
        a0 = subu(t6, s3);
        v1 = lui(0x3780);
        mtc1(a0, F2);
        a1 = addiu(sp, 84);
        mtc1(v1, F1);
        cvt_s_w(F2, F2);
        a0 = addiu(sp, 88);
        v1 = addiu(sp, 92);
        mul_s(F4, F1, F2);
        lwc1(F0, sp + 80);
        lwc1(F2, a1);
        lwc1(F1, a0);
        mul_s(F3, F0, F4);
        lwc1(F0, v1);
        mul_s(F2, F2, F4);
        mul_s(F1, F1, F4);
        mul_s(F0, F0, F4);
        swc1(F3, sp + 80);
        swc1(F2, a1);
        swc1(F1, a0);
        swc1(F0, v1);
        lwc1(F0, t5);
        add_s(F0, F0, F3);
        swc1(F0, t5);
        lwc1(F0, a1);
        lwc1(F1, t5 + 4);
        add_s(F0, F1, F0);
        swc1(F0, t5 + 4);
        lwc1(F0, a0);
        lwc1(F1, t5 + 8);
        add_s(F0, F1, F0);
        swc1(F0, t5 + 8);
        lwc1(F0, v1);
        lwc1(F1, t5 + 12);
        add_s(F0, F1, F0);
        swc1(F0, t5 + 12);
        backedge();
    }
    // divided by the y extent
    charge(16);
    v1 = lui(0x3F80);
    mtc1(v1, F1);
    lwc1(F0, t5);
    div_s(F1, F1, F9);
    scale4(t5, F1, F0);
    charge(7);
    ra = ld(sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 96);
}

// sub_4CEC10 [RwImageResample-like (dst, src)]: $a0 the destination image (+0 flags, +4 width, +8 height, +16 stride,
// +20 pixels), $a1 the source (+0 flags: bit 1 copied, +4 width, +8 height). The 16.16 steps src / dst * 65536 per
// axis; each destination pixel is the box sample sub_4CE9A0 over its source footprint, converted back to bytes as
// (int)(0.5 + 255 * c) per channel. The compiler keeps the height and the y step in 128-bit frame slots (sp + 176 /
// + 160) and the running y and row end at sp + 208 / + 192.
void Cpu::sub_4CEC10() {
    enter(49);
    sp = addiu(sp, -256);
    a2 = lw(a1);
    sd(sp + 144, ra);
    lwc1(F3, a1 + 4);
    sq(sp + 128, fp);
    lwc1(F0, a1 + 8);
    sq(sp + 112, s7);
    v0 = a0;
    sq(sp + 96, s6);
    fp = zero;
    sq(sp + 80, s5);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    cvt_s_w(F3, F3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s2 = lw(a0 + 4);   // dst width
    v1 = lw(a0 + 8);   // dst height
    sw(sp + 236, a1);
    a1 = lw(a0);
    mtc1(s2, F1);
    sq(sp + 176, v1);
    cvt_s_w(F1, F1);
    v1 = lui(0x4780);  // 65536.0
    div_s(F1, F3, F1);
    mtc1(v1, F2);
    mul_s(F1, F2, F1);
    v1 = a2 & 2;
    v1 = a1 | v1;
    sw(a0, v1);
    lq(v1, sp + 176);
    cvt_w_s(F1, F1);
    mfc1(s1, F1);      // the x step
    cvt_s_w(F1, F0);
    mtc1(v1, F0);
    cvt_s_w(F0, F0);
    div_s(F0, F1, F0);
    mul_s(F0, F2, F0);
    cvt_w_s(F0, F0);
    mfc1(v1, F0);      // the y step
    sq(sp + 160, v1);
    lq(v1, sp + 176);
    at = slt(zero, v1);
    sw(sp + 208, zero);
    if (at != 0) {
        charge(3);
        s0 = addiu(sp, 244);
        s6 = addiu(sp, 248);
        s7 = addiu(sp, 252);
        for (;;) {  // the destination rows (fp)
            charge(8);
            v1 = lw(v0 + 16);
            mult(a1, v1, fp);
            a0 = lw(v0 + 20);
            s4 = zero;
            s5 = zero;
            v1 = slt(zero, s2);
            s3 = addu(a0, a1);
            if (v1 != 0) {
                charge(6);
                a0 = lw(sp + 208);
                lq(v1, sp + 160);
                v1 = addu(a0, v1);
                v1 = addiu(v1, -1);
                sw(sp + 192, v1);
                for (;;) {  // the pixels of the row (s5)
                    charge(43);
                    a0 = lw(sp + 236);
                    a3 = lw(sp + 208);
                    v1 = addu(s4, s1);
                    t0 = lw(sp + 192);
                    a2 = addiu(v1, -1);
                    a1 = s4;
                    t1 = addiu(sp, 240);
                    jal(0x4CED58u, gen::fn_sub_4CE9A0_004ce9a0);
                    v1 = lui(0x437F);  // 255.0
                    s5 = addiu(s5, 1);
                    mtc1(v1, F3);
                    s4 = addu(s4, s1);
                    lwc1(F0, sp + 240);
                    v1 = lui(0x3F00);  // 0.5
                    mtc1(v1, F2);
                    mtc1(zero, F1);
                    v1 = slt(s5, s2);
                    const Gpr* ch[4] = {nullptr, &s0, &s6, &s7};
                    for (unsigned k = 0; k < 4; ++k) {
                        adda_s(F1, F2);
                        if (k) lwc1(F0, *ch[k]);
                        madd_s(F0, F3, F0);
                        cvt_w_s(F0, F0);
                        mfc1(a0, F0);
                        sb(s3 + k, a0);
                    }
                    s3 = addiu(s3, 4);
                    if (v1 == 0) break;
                    backedge();
                }
                charge(2);
                backedge();
            }
            charge(8);
            a0 = lw(sp + 208);
            lq(v1, sp + 160);
            fp = addiu(fp, 1);
            a0 = addu(a0, v1);
            lq(v1, sp + 176);
            v1 = slt(fp, v1);
            sw(sp + 208, a0);
            if (v1 == 0) break;
            backedge();
        }
    }
    charge(2);
    charge(12);
    ra = ld(sp + 144);
    lq(fp, sp + 128);
    lq(s7, sp + 112);
    lq(s6, sp + 96);
    lq(s5, sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 256);
}

// =========================================================================================================
// [rxheap] the pipeline executor and its scratch memory; [im3d] the Im3D entry points.
// =========================================================================================================

// RxPipelineExecute(pipeline, data, lock): with `lock` and an unlocked pipeline (the current pipeline gp-16832 +24),
// sub_4F6890 locks it first. Sets the execution globals (0x965A88 = 1 "continue", 0x965A80 the pipeline, 0x965A90
// the data, 0x965A94 the current pipeline), clears the pipeline's +16 state and calls the first node's body
// (node +0 = its definition, +4 the body) as body(node, &0x965A90). A body returning 0 clears the "continue" word.
// A pipeline state >= 2 afterwards is set to 2 and its +20 list is released (sub_4F28F0). The globals are cleared;
// returns the pipeline when "continue" survived, else 0.
void Cpu::RxPipelineExecute() {
    enter(7);
    sp = addiu(sp, -48);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = a0;
    s0 = a1;
    if (a2 != 0) {
        charge(4);
        a0 = lw(gp - 16832);
        v0 = lw(a0 + 24);
        if (v0 != 0) {
            charge(2);
            jal(0x4F2E9Cu, gen::fn_sub_4F6890_004f6890);
        }
    }
    charge(19);
    v1 = 1;
    v0 = lui(0x96);
    sw(v0 + 23176, v1);  // 0x965A88 = 1
    a1 = lui(0x96);
    v1 = lw(gp - 16832);
    v0 = lui(0x96);
    sw(v0 + 23168, s1);  // 0x965A80 = pipeline
    v0 = lui(0x96);
    sw(v0 + 23184, s0);  // 0x965A90 = data
    v0 = lui(0x96);
    sw(v0 + 23188, v1);  // 0x965A94 = the current pipeline
    sw(s1 + 16, zero);
    a0 = lw(s1 + 8);     // the first node
    v0 = lw(a0);
    v0 = lw(v0 + 4);     // its body
    a1 = addiu(a1, 23184);
    jalr(0x4F2EE0u, v0.u());
    if (v0 == 0) {
        charge(3);
        v1 = lui(0x96);
        sw(v1 + 23176, v0);
        backedge();
    }
    charge(4);
    v0 = lw(s1 + 16);
    at = slti(v0, 2);
    if (at == 0) {
        charge(6);
        v0 = 2;
        sw(s1 + 16, v0);
        a0 = lw(s1 + 20);
        jal(0x4F2F48u, gen::fn_sub_4F28F0_004f28f0);
        backedge();
    }
    charge(9);
    v0 = lui(0x96);
    v1 = lui(0x96);
    sw(v0 + 23184, zero);
    v0 = lui(0x96);
    sw(v1 + 23168, zero);
    v0 = lw(v0 + 23176);
    v1 = lui(0x96);
    sw(v1 + 23188, zero);
    charge(2);
    if (v0 == 0)
        v0 = zero;
    else
        v0 = s1;
    charge(5);
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}

// sub_4F3150 [the pipeline scratch allocator]: $a0 bytes (rounded up to 4) from the bump pointer gp-16820, bounded by
// gp-16824; returns the block, or 0 after RWERROR 0x80000013 (the pointer is restored).
void Cpu::sub_4F3150() {
    enter(11);
    sp = addiu(sp, -32);
    a0 = addiu(a0, 3);
    sd(sp, ra);
    v0 = si(-4);
    a1 = a0 & v0;
    v1 = lw(gp - 16820);
    v0 = lw(gp - 16824);
    v1 = addu(v1, a1);
    at = sltu(v0, v1);
    sw(gp - 16820, v1);
    if (at == 0) {
        charge(2);
        v0 = subu(v1, a1);
    } else {
        charge(11);
        v0 = subu(v1, a1);
        sw(gp - 16820, v0);
        v1 = 1;
        v0 = lui(0x8000);
        sw(sp + 24, v1);
        a0 = v0 | 0x13;
        rwerror(0x4F3198u, 24);
        v0 = zero;
    }
    charge(3);
    ra = ld(sp);
    sp = addiu(sp, 32);
}

// sub_4F5D30 [a node's output link]: an 8-byte record from sub_4F3150 = {$a0, $a0 +8}; stored at *$a2 when that is
// still 0. Returns the record.
void Cpu::sub_4F5D30() {
    enter(11);
    sp = addiu(sp, -48);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = a0;
    s0 = a2;
    a0 = 8;
    jal(0x4F5D48u, gen::fn_sub_4F3150_004f3150);
    v1 = lw(s0);
    if (v1 == 0) {
        charge(2);
        sw(s0, v0);
        backedge();
    }
    charge(4);
    sw(v0, s1);
    v1 = lw(s1 + 8);
    sw(v0 + 4, v1);
    charge(5);
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}

// sub_4F62D0 [lock one node's scratch block]: sub_4F61C0($a2) grows the pipeline's block (kept recompiled: RwRealloc);
// on success a 32-byte header is set up at the node's block (+0 its start: zeroed, its last 32 bytes a copy of the
// header) and linked to the previous node ($a1, its block's end - 32). Returns 1, or 0.
void Cpu::sub_4F62D0() {
    enter(10);
    sp = addiu(sp, -48);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = a0;
    s0 = a1;
    a0 = a2;
    jal(0x4F62E8u, gen::fn_sub_4F61C0_004f61c0);
    if (v0 == 0) {
        charge(1);
        v0 = zero;
    } else {
        charge(37);
        a3 = lw(s1);
        v1 = lw(s1 + 4);
        a2 = addiu(a3, 32);
        sw(a3, zero);
        a1 = addu(a3, v1);
        sw(a3 + 4, zero);
        a0 = addiu(a1, -32);
        sw(a3 + 8, zero);
        v1 = addiu(a2, 32);
        sw(a3 + 12, zero);
        v1 = subu(a0, v1);
        for (unsigned half = 0; half < 2; ++half) {  // the header's 32 bytes copied to the block end
            lwc1(F3, a3 + 16 * half);
            lwc1(F2, a3 + 16 * half + 4);
            lwc1(F1, a3 + 16 * half + 8);
            lwc1(F0, a3 + 16 * half + 12);
            swc1(F3, a1 - 32 + 16 * half);
            swc1(F2, a1 - 28 + 16 * half);
            swc1(F1, a1 - 24 + 16 * half);
            swc1(F0, a1 - 20 + 16 * half);
        }
        sw(a3 + 4, a2);
        sw(a3 + 32, a3);
        sw(a3 + 36, a0);
        sw(a1 - 32, a2);
        sw(a3 + 40, v1);
        sw(a3 + 44, v0);
        sw(v0 + 4, a2);
        v1 = lw(a3 + 40);
        sw(v0, v1);
        if (s0 != 0) {
            charge(6);
            v1 = lw(s0);
            v0 = lw(s0 + 4);
            v0 = addu(v1, v0);
            sw(v0 - 28, a3);
            v0 = addiu(v0, -32);
            sw(a3, v0);
        }
        charge(2);
        v0 = 1;
    }
    charge(5);
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}

// sub_4F6890 [RxPipelineLock-like]: clears the pipeline's +20, locks every node of the list at pipeline +4 -> +8
// (sub_4F62D0 with the previous node), the first one's +0 going to pipeline +8, then the list head itself; clears
// +24 (the "needs lock" flag) and returns 1, or 0 when a node failed.
void Cpu::sub_4F6890() {
    enter(11);
    sp = addiu(sp, -64);
    sd(sp + 48, ra);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    s2 = zero;
    sq(sp, s0);
    sw(a0 + 20, zero);
    v0 = lw(a0 + 4);
    s1 = lw(v0 + 8);
    s0 = a0;
    if (s1 != 0) {
        for (;;) {
            charge(6);
            a0 = s1;
            a1 = s2;
            a2 = s0;
            jal(0x4F68C4u, gen::fn_sub_4F62D0_004f62d0);
            if (v0 == 0) {
                charge(2);
                v0 = zero;
                pipeline_lock_exit();
                return;
            }
            charge(2);
            if (s2 == 0) {
                charge(3);
                v0 = lw(s1);
                sw(s0 + 8, v0);
                backedge();
            } else {
                charge(1);
            }
            charge(4);
            s2 = s1;
            s1 = lw(s1 + 8);
            if (s1 == 0) break;
            backedge();
        }
    }
    charge(7);
    s1 = lw(s0 + 4);
    a1 = s2;
    a2 = s0;
    a0 = s1;
    jal(0x4F6904u, gen::fn_sub_4F62D0_004f62d0);
    if (v0 == 0) {
        charge(2);
        v0 = zero;
    } else {
        charge(2);
        if (s2 == 0) {
            charge(3);
            v0 = lw(s1);
            sw(s0 + 8, v0);
            backedge();
        }
        charge(3);
        sw(s0 + 24, zero);
        v0 = 1;
    }
    pipeline_lock_exit();
}
void Cpu::pipeline_lock_exit() {
    charge(6);
    ra = ld(sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 64);
}

// The Im3D globals: 0x960070 + *(gp-16848): +0 the transform pipeline, +4 .. +20 the render pipelines by primitive
// type (3 tri-list, 5 tri-fan, 4 tri-strip, 1 line-list, 2 poly-line), +64 the vertex count (u16), +68 the vertices,
// +72 the stride, +76 the transform flags, +80 the matrix; the render record from +76 (+32 its pipeline, +44 the
// primitive count for lists), +108 .. +120 {0, type, indices, count}.

// sub_4F1ED0 [RwIm3DTransform(vertices, count, matrix, flags)]: count < 65537 (as an unsigned 32-bit value) fills
// the Im3D transform record and runs its pipeline (RxPipelineExecute(pipe, record, 1)); returns the vertices, or 0
// (RWERROR 0x32 for a count out of range).
void Cpu::sub_4F1ED0() {
    enter(10);
    sp = addiu(sp, -48);
    v0 = dsll32(a1, 0);
    at = lui(0x1);
    sd(sp + 16, ra);
    sq(sp, s0);
    v0 = dsrl32(v0, 0);
    at = at | 1;
    at = slt(v0, at);
    s0 = a0;
    if (at != 0) {
        charge(17);
        v0 = a3 | 0x18;
        a0 = lui(0x96);
        a3 = lw(gp - 16848);
        a0 = addiu(a0, 112);
        v1 = 0x24;
        a0 = addu(a0, a3);
        sh(a0 + 64, a1);
        sw(a0 + 68, s0);
        a1 = addiu(a0, 64);
        sw(a0 + 72, v1);
        sw(a0 + 80, a2);
        sw(a0 + 76, v0);
        a0 = lw(a0);
        a2 = 1;
        jal(0x4F1F2Cu, gen::fn_RxPipelineExecute_004f2e70);
        if (v0 != 0) {
            charge(2);
            v0 = s0;
            im3d_exit(48, 16);
            return;
        }
    } else {
        charge(9);
        v0 = 1;
        a0 = 0x32;
        sw(sp + 40, v0);
        rwerror(0x4F1F54u, 40);
        backedge();
    }
    charge(2);
    v0 = zero;
    im3d_exit(48, 16);
}
void Cpu::im3d_exit(s32 frame, s32 ra_slot) {
    charge(frame == 48 ? 4 : 5);
    ra = ld(sp + ra_slot);
    if (frame == 64) lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, frame);
}

// sub_4F1FD0 [RwIm3DRenderIndexedPrimitive(type, indices, count)]: only after a transform (Im3D +68 != 0). Fills
// {+108 0, +112 type, +116 indices, +120 count}, picks the type's pipeline; for tri-lists the primitive count is
// count - count % 3, for line-lists count rounded down to even (+44). Runs RxPipelineExecute(pipe, record, 0);
// returns 1 or 0 (RWERROR 0x23 without a transform, 0x25 for a bad type).
void Cpu::sub_4F1FD0() {
    enter(10);
    sp = addiu(sp, -48);
    a3 = lui(0x96);
    sd(sp + 16, ra);
    a3 = addiu(a3, 112);
    sq(sp, s0);
    v0 = lw(gp - 16848);
    v1 = addu(a3, v0);
    v0 = lw(v1 + 68);
    if (v0 == 0) {
        charge(9);
        v0 = 1;
        a0 = 0x23;
        sw(sp + 32, v0);
        rwerror(0x4F2124u, 32);
        backedge();
        charge(2);
        v0 = zero;
        im3d_exit(48, 16);
        return;
    }
    charge(7);
    sw(v1 + 108, zero);
    v0 = 2;
    sw(v1 + 112, a0);
    s0 = addiu(v1, 76);
    sw(v1 + 116, a1);
    sw(v1 + 120, a2);
    // the pipeline at Im3D globals + off (re-read through gp-16848)
    auto pipe = [&](u64 cost, s32 off) {
        charge(cost);
        v0 = lw(gp - 16848);
        v0 = addu(a3, v0);
        v0 = lw(v0 + off);
        sw(s0 + 32, v0);
    };
    bool ok = true;
    if (a0 == v0) {
        pipe(5, 20);  // 2 poly-line
    } else {
        charge(3);
        a1 = 1;
        if (a0 == a1) {  // 1 line-list: count rounded down to even
            charge(6);
            v1 = lw(gp - 16848);
            v0 = a2 & 1;
            v1 = addu(a3, v1);
            v1 = lw(v1 + 16);
            sw(s0 + 32, v1);
            if (sgn(a2) < 0) {
                charge(2);
                if (v0 != 0) {
                    charge(1);
                    v0 = addiu(v0, -2);
                }
            }
            charge(3);
            v0 = subu(a2, v0);
            sw(s0 + 44, v0);
        } else {
            charge(3);
            v0 = 4;
            if (a0 == v0) {
                pipe(5, 12);  // 4 tri-strip
            } else {
                charge(3);
                v0 = 5;
                if (a0 == v0) {
                    pipe(5, 8);  // 5 tri-fan
                } else {
                    charge(3);
                    v1 = 3;
                    if (a0 == v1) {  // 3 tri-list: count - count % 3
                        charge(9);
                        v0 = lw(gp - 16848);
                        v0 = addu(a3, v0);
                        v0 = lw(v0 + 4);
                        sw(s0 + 32, v0);
                        div(a2, v1);
                        mfhi(v0);
                        v0 = subu(a2, v0);
                        sw(s0 + 44, v0);
                    } else {
                        ok = false;
                    }
                }
            }
        }
    }
    if (!ok) {  // a bad type: RWERROR 0x25 (type), then the pipeline of the record as it stands
        charge(2);
        sw(sp + 40, a1);
        charge(6);
        a1 = a0;
        a0 = 0x25;
        rwerror(0x4F20E0u, 40);
    }
    charge(6);
    a0 = lw(s0 + 32);
    a1 = s0;
    a2 = zero;
    jal(0x4F20FCu, gen::fn_RxPipelineExecute_004f2e70);
    charge(2);
    if (v0 != 0)
        v0 = 1;
    else
        v0 = zero;
    im3d_exit(48, 16);
}

// sub_4F2150 [RwIm3DRenderPrimitive(type)]: sub_4F2E60 first (the transform's closing call); only after a transform.
// The record {+108 0, +112 type, +116 0, +120 the vertex count}, the type's pipeline, RxPipelineExecute(pipe,
// record, 0); returns 1 or 0 (RWERROR 0x23 / 0x25).
void Cpu::sub_4F2150() {
    enter(14);
    sp = addiu(sp, -64);
    v0 = lui(0x96);
    sd(sp + 32, ra);
    v0 = addiu(v0, 112);
    sq(sp + 16, s1);
    sq(sp, s0);
    s1 = a0;
    v1 = lw(gp - 16848);
    v0 = addu(v0, v1);
    v0 = lw(v0 + 68);
    s0 = sltu(zero, v0);
    jal(0x4F2178u, gen::fn_sub_4F2E60_004f2e60);
    if (s0 == 0) {
        charge(9);
        v0 = 1;
        a0 = 0x23;
        sw(sp + 48, v0);
        rwerror(0x4F2274u, 48);
        backedge();
        charge(2);
        v0 = zero;
        im3d_exit(64, 32);
        return;
    }
    charge(12);
    a0 = lw(gp - 16848);
    v1 = lui(0x96);
    v1 = addiu(v1, 112);
    v0 = 2;
    a0 = addu(v1, a0);
    sw(a0 + 108, zero);
    s0 = addiu(a0, 76);
    sw(a0 + 112, s1);
    sw(a0 + 116, zero);
    v1 = lhu(a0 + 64);
    sw(a0 + 120, v1);
    auto pipe = [&](s32 off) {
        charge(3);
        v0 = lw(a0 + off);
        sw(s0 + 32, v0);
    };
    if (s1 == v0) {
        pipe(20);
    } else {
        charge(3);
        v1 = 1;
        if (s1 == v1) {
            pipe(16);
        } else {
            charge(3);
            v0 = 4;
            if (s1 == v0) {
                pipe(12);
            } else {
                charge(3);
                v0 = 5;
                if (s1 == v0) {
                    pipe(8);
                } else {
                    charge(3);
                    v0 = 3;
                    if (s1 == v0) {
                        pipe(4);
                    } else {
                        charge(2);
                        sw(sp + 56, v1);
                        charge(6);
                        a1 = s1;
                        a0 = 0x25;
                        rwerror(0x4F2230u, 56);
                    }
                }
            }
        }
    }
    charge(6);
    a0 = lw(s0 + 32);
    a1 = s0;
    a2 = zero;
    jal(0x4F224Cu, gen::fn_RxPipelineExecute_004f2e70);
    charge(2);
    if (v0 != 0)
        v0 = 1;
    else
        v0 = zero;
    im3d_exit(64, 32);
}

// =========================================================================================================
// [renderstate] the render-state getter
// =========================================================================================================

// sub_4D78B0 [RwRenderStateGet, the driver's: the engine's pointer at 0x960094]: $a0 the state, $a1 where its value
// goes. The answers come from the GS register shadows of the sky driver: TEST gp-17048 / gp-17072 (alpha test, z test,
// the alpha reference), ALPHA gp-17032 (looked up in the 6 x 6 blend table 0x77EF80 by the shadows of the source /
// destination blend gp-20264 / gp-20260, with FIX = 0x80 for 1 / 1), the prim / shading word gp-20272, CLAMP
// gp-17040, FOGCOL gp-17056, the texture raster / filter gp-16964 / gp-16956, the current raster gp-16924 and its
// address-mode words, the texture's +... (state 1: gp-16948, -1 read as 0). Returns 1, or 0 for an unknown state or an
// unrepresentable shadow. The compiled form is a compare chain over the state (13, 30, 29, 20, 16, 15, 14, 12, 11, 10,
// 9 .. 1) with a shared "store and return 1" tail.
void Cpu::sub_4D78B0() {
    enter(7);
    sp = addiu(sp, -32);
    sd(sp + 16, ra);
    sq(sp, s0);
    s0 = a1;
    a1 = 0xD;
    // the exits
    auto tail = [&] {  // L_7F4C
        charge(1);
        ra = ld(sp + 16);
        charge(3);
        lq(s0, sp);
        sp = addiu(sp, 32);
    };
    auto ok = [&] {  // L_7F08: return 1
        charge(1);
        v0 = 1;
        charge(2);
        tail();
    };
    auto fail = [&](u64 cost) {  // v0 = 0, then the tail (through L_7F00 when `cost` is the chain's own)
        charge(cost);
        v0 = zero;
        tail();
    };
    auto put = [&](u64 cost, u64 value) {
        charge(cost);
        v0 = value;
        sw(s0, v0);
        ok();
    };
    auto put_back = [&](u64 cost, u64 value) {  // a block placed after the tail: a backward jump into it
        charge(cost);
        v0 = value;
        sw(s0, v0);
        backedge();
        ok();
    };
    auto is = [&](Gpr& r, u32 k) {  // the next compare of the chain
        charge(3);
        r = k;
        return a0 == r;
    };

    if (a0 == a1) {  // 13: no value
        charge(1);
        v0 = zero;
        fail(2);
        return;
    }
    if (is(v0, 0x1E)) {  // 30: the alpha reference (TEST AREF) * 1.99999 as an integer
        charge(13);
        v0 = ld(gp - 17072);
        v0 = v0 & 0xFF0;
        a0 = dsra(v0, 4);
        jal(0x4D7ED0u, gen::fn___floatdisf_0052eb60);
        v0 = lui(0x3FFF);
        v0 = v0 | 7;
        mtc1(v0, F1);
        mul_s(F0, F1, F0);
        cvt_w_s(F0, F0);
        mfc1(v0, F0);
        sw(s0, v0);
        ok();
        return;
    }
    if (is(v0, 0x1D)) {  // 29: the alpha test function (TEST ATE / ATST)
        charge(4);
        v1 = ld(gp - 17072);
        v0 = v1 & 1;
        if (v0 == 0) {
            put_back(3, 8);
            return;
        }
        charge(3);
        a0 = v1 & 0x300E;
        if (a0 == a1) {
            put(3, 6);
        } else if (is(v0, 0xC)) {
            put(3, 5);
        } else if (is(v0, 0xA)) {
            put(3, 7);
        } else if (is(v1, 8)) {
            put(3, 3);
        } else if (is(v0, 6)) {
            put(3, 4);
        } else if (is(v0, 4)) {
            put(3, 2);
        } else if (is(v0, 2)) {
            charge(2);
            sw(s0, v1);  // v1 = 8 here
            ok();
        } else {
            charge(2);
            if (a0 == 0) {
                put(3, 1);
            } else {
                charge(2);
                sw(s0, zero);
                charge(2);
                ok();
            }
        }
        return;
    }
    if (is(v0, 0x14)) {  // 20
        charge(3);
        v0 = lw(gp - 16964);
        sw(s0, v0);
        ok();
        return;
    }
    if (is(v0, 0x10)) {  // 16: which of the three driver rasters is current (0x965610 / 0x965530 / 0x965450)
        charge(5);
        v1 = lw(gp - 16924);
        v0 = lui(0x96);
        v0 = addiu(v0, 22032);
        if (v1 == v0) {
            put_back(3, 1);
            return;
        }
        charge(4);
        v0 = lui(0x96);
        v0 = addiu(v0, 21808);
        if (v1 == v0) {
            put_back(3, 2);
            return;
        }
        charge(4);
        v0 = lui(0x96);
        v0 = addiu(v0, 21584);
        if (v1 == v0) {
            put_back(3, 3);
            return;
        }
        charge(2);
        sw(s0, zero);
        ok();
        return;
    }
    if (is(v0, 0xF)) {  // 15: the fog colour (FOGCOL bytes swapped into RGBA, alpha 0xFF)
        charge(16);
        a2 = ld(gp - 17056);
        v1 = lui(0xFF);
        v0 = 0xFF00;
        v0 = dsll(v0, 16);
        a0 = a2 & 0xFF;
        v1 = a2 & v1;
        a1 = dsll(a0, 16);
        v1 = dsra(v1, 16);
        a0 = a2 & 0xFF00;
        a0 = a1 | a0;
        v1 = v1 | a0;
        v0 = v1 | v0;
        v0 = dsll32(v0, 0);
        v0 = dsra32(v0, 0);
        sw(s0, v0);
        ok();
        return;
    }
    if (is(v0, 0xE)) {  // 14: fog enable (prim word bit 5)
        charge(5);
        v0 = ld(gp - 20272);
        v0 = v0 & 0x20;
        v0 = sltu(zero, v0);
        sw(s0, v0);
        ok();
        return;
    }
    if (is(v0, 0xC)) {  // 12
        charge(3);
        v0 = lw(gp - 16956);
        sw(s0, v0);
        ok();
        return;
    }
    // 11 / 10: the destination / source blend, valid only when ALPHA still equals the table's word for the shadows
    auto blend = [&](Gpr& alpha, Gpr& idx_reg, Gpr& flag, bool dst) {
        charge(3);
        alpha = ld(gp - 17032);
        if (sgn(alpha) < 0) {
            fail(2);
            return;
        }
        charge(4);
        Gpr& src = dst ? a0 : a3;  // the source blend shadow's register
        src = lw(gp - 20264);
        v1 = 1;
        flag = zero;
        if (src == v1) {
            charge(3);
            v0 = lw(gp - 20260);
            if (v0 == v1) {
                charge(1);
                flag = v1;
            }
        }
        charge(16);
        if (dst) {
            a1 = lw(gp - 20260);
            v0 = sll(a0, 2);
            v1 = 0x80;
            a2 = dsll32(v1, 0);
            v1 = lui(0x78);
            if (t0 == 0) a2 = zero;  // movz
            v1 = addiu(v1, -4224);
            a0 = sll(a1, 1);
            a0 = addu(a0, a1);
            a0 = sll(a0, 3);
            v1 = addu(v1, a0);
            v0 = addu(v0, v1);
            v0 = lw(v0);
            v0 = v0 | a2;
        } else {
            a2 = lw(gp - 20260);
            v0 = 0x80;
            v0 = dsll32(v0, 0);
            v1 = lui(0x78);
            if (a1 == 0) v0 = zero;  // movz
            v1 = addiu(v1, -4224);
            a0 = sll(a3, 2);
            a1 = sll(a2, 1);
            a1 = addu(a1, a2);
            a1 = sll(a1, 3);
            v1 = addu(v1, a1);
            v1 = addu(a0, v1);
            v1 = lw(v1);
            v0 = v1 | v0;
        }
        if (alpha != v0) {
            fail(2);
            return;
        }
        charge(3);
        at = sltiu(idx_reg, 6);
        if (at == 0) {
            fail(2);
            return;
        }
        u32 t;
        if (dst) {
            charge(7);
            v1 = lui(0x7C);
            v0 = sll(a1, 2);
            v1 = addiu(v1, -13088);
            v0 = addu(v0, v1);
            v0 = lw(v0);  // the jump table 0x7BCCE0
            t = v0.u();
        } else {
            charge(6);
            v0 = lui(0x7C);
            v0 = addiu(v0, -13056);
            v0 = addu(a0, v0);
            v0 = lw(v0);  // the jump table 0x7BCD00
            t = v0.u();
        }
        static constexpr u32 kSrcCases[6] = {0x4D7C0Cu, 0x4D7C18u, 0x4D7C24u, 0x4D7C30u, 0x4D7C3Cu, 0x4D7C48u};
        static constexpr u32 kDstCases[6] = {0x4D7CF8u, 0x4D7D04u, 0x4D7D10u, 0x4D7D1Cu, 0x4D7D28u, 0x4D7D34u};
        static constexpr u32 kValues[6] = {1, 2, 5, 6, 7, 8};
        const u32* cases = dst ? kDstCases : kSrcCases;
        for (unsigned k = 0; k < 6; ++k) {
            if (t == cases[k]) {
                put(3, kValues[k]);
                return;
            }
        }
        rt::lookup_func(t)(c);  // a target outside the function (never in retail data): the jr itself
    };
    if (is(v0, 0xB)) {
        blend(a3, a1, t0, true);
        return;
    }
    if (is(v0, 0xA)) {
        blend(t0, a3, a1, false);
        return;
    }
    if (is(v0, 9)) {  // 9: the texture address mode (CLAMP bits 5..8)
        charge(5);
        v1 = ld(gp - 17040);
        v0 = 0x160;
        v1 = v1 & 0x1E0;
        if (v1 == v0) {
            put(3, 6);
        } else if ((charge(3), v0 = 0xC0, v1 == v0)) {
            put(3, 5);
        } else if ((charge(3), v0 = 0x120, v1 == v0)) {
            put(3, 4);
        } else if ((charge(3), v0 = 0x80, v1 == v0)) {
            put(3, 3);
        } else if ((charge(3), v0 = 0x60, v1 == v0)) {
            put(3, 2);
        } else {
            charge(2);
            if (v1 == 0) {
                put(3, 1);
            } else {
                charge(2);
                v0 = zero;
                charge(2);
                ra = ld(sp + 16);
                charge(3);
                lq(s0, sp);
                sp = addiu(sp, 32);
            }
        }
        return;
    }
    if (is(v0, 8)) {  // 8
        charge(8);
        v1 = ld(gp - 17088);
        v0 = 1;
        v0 = dsll32(v0, 0);
        v0 = v1 & v0;
        v0 = sltu(zero, v0);
        v0 = v0 ^ 1;
        sw(s0, v0);
        ok();
        return;
    }
    if (is(v0, 7)) {  // 7: shading (prim word bit 3: 2 Gouraud, 1 flat)
        charge(7);
        a0 = ld(gp - 20272);
        v1 = 2;
        v0 = 1;
        a0 = a0 & 8;
        if (a0 == 0) v1 = v0;  // movz
        sw(s0, v1);
        ok();
        return;
    }
    if (is(v0, 6)) {  // 6: z test (TEST bits 17..18 == 2)
        charge(8);
        a0 = ld(gp - 17072);
        v1 = lui(0x6);
        v0 = lui(0x4);
        v1 = a0 & v1;
        v0 = v1 ^ v0;
        v0 = sltiu(v0, 1);
        sw(s0, v0);
        ok();
        return;
    }
    if (is(v0, 5)) {  // 5: prim word bit 8 -> 0, else 1
        charge(4);
        v0 = ld(gp - 20272);
        v0 = v0 & 0x100;
        if (v0 == 0) {
            put(3, 1);
        } else {
            charge(2);
            sw(s0, zero);
            ok();
        }
        return;
    }
    if (is(v0, 4)) {  // 4: CLAMP bits 2..3 (v): 3 when set, else 1
        charge(4);
        v0 = ld(gp - 17048);
        v0 = v0 & 0xC;
        if (v0 == 0)
            put(3, 1);
        else
            put(3, 3);
        return;
    }
    if (is(a1, 3)) {  // 3: CLAMP bits 0..1 (u): 3 when set, else 1
        charge(4);
        v0 = ld(gp - 17048);
        v0 = v0 & 3;
        if (v0 == 0) {
            put(3, 1);
        } else {
            charge(2);
            sw(s0, a1);
            ok();
        }
        return;
    }
    if (is(v0, 2)) {  // 2: both modes: 0 when they differ
        charge(5);
        v0 = ld(gp - 17048);
        v1 = v0 & 3;
        v0 = v0 & 0xC;
        if (v1 != v0) {
            charge(2);
            sw(s0, zero);
            backedge();
            ok();
            return;
        }
        charge(2);
        if (v1 == 0) {
            put(3, 1);
        } else {
            charge(2);
            sw(s0, a1);
            ok();
        }
        return;
    }
    if (is(v0, 1)) {  // 1: gp-16948, -1 reads as 0
        charge(4);
        v1 = lw(gp - 16948);
        v0 = si(-1);
        charge(2);
        if (v1 == v0) v1 = zero;
        sw(s0, v1);
        charge(2);
        v0 = 1;
        charge(2);
        tail();
        return;
    }
    charge(2);  // an unknown state
    v0 = zero;
    fail(2);
}

// =========================================================================================================
// [upload] the per-camera VU constants and the texture upload packets
// =========================================================================================================

// `dst` = `src` / 2 rounded toward zero (the compiled signed halving: sra, and for a negative value (src + 1) >> 1 in
// a 2-cycle block); the sra is the branch delay slot, executed on both paths.
void Cpu::half(Gpr& dst, const Gpr& src) {
    const bool neg = sgn(src) < 0;
    dst = sra(src, 1);
    if (neg) {
        charge(2);
        dst = addiu(src, 1);
        dst = sra(dst, 1);
    }
}

// sub_4EEC20 [the per-camera VU1 constants]: $a0 the camera (+20 projection: 1 perspective, +96 the frame buffer
// raster, +128 / +132 the near / far clip planes, +136 the z shift, +140 / +144 the view offset). Writes the constant
// block at 0x965950..0x9659F0: near / far splats (0x965950 / 0x965960), the raster size and view offset (0x965980 /
// 0x965990), the screen centres (2048 + raster offset +- size / 2: 0x9659A0 / 0x965A20), the z scale (0x965970,
// -255 / (far - zshift), with the fog far gp-16864 unless gp-16860), the guard-band ranges (0x965910 / 0x965920:
// min(x, 4095 - x) and its reciprocal) and the clip half-sizes + 5 (0x965930 / 0x965940); the projection terms of the
// matrix diagonal; gp-16892 bit 3 set for a parallel camera, cleared for perspective.
void Cpu::sub_4EEC20() {
    enter(53);
    t3 = lw(a0 + 96);   // the frame buffer raster
    lwc1(F0, a0 + 128);  // near
    t6 = lui(0x96);
    t7 = lui(0x96);
    t6 = addiu(t6, 22864);
    t5 = lui(0x96);
    t4 = lui(0x96);
    t2 = lui(0x96);
    t1 = lui(0x96);
    t0 = lui(0x96);
    a3 = lui(0x96);
    a2 = lui(0x96);
    swc1(F0, t6 + 12);
    a1 = lui(0x96);
    swc1(F0, t6 + 8);
    v1 = lui(0x96);
    swc1(F0, t6 + 4);
    t7 = addiu(t7, 22880);
    swc1(F0, t6);
    t5 = addiu(t5, 22912);
    lwc1(F0, a0 + 132);  // far
    t4 = addiu(t4, 22928);
    t2 = addiu(t2, 22800);
    t1 = addiu(t1, 22816);
    t0 = addiu(t0, 22832);
    a3 = addiu(a3, 22848);
    a2 = addiu(a2, 23072);
    a1 = addiu(a1, 22944);
    v1 = addiu(v1, 22896);
    swc1(F0, t7 + 12);
    swc1(F0, t7 + 8);
    swc1(F0, t7 + 4);
    swc1(F0, t7);
    lwc1(F0, t3 + 12);
    cvt_s_w(F0, F0);
    swc1(F0, t5);
    lwc1(F0, t3 + 16);
    cvt_s_w(F0, F0);
    swc1(F0, t5 + 4);
    lwc1(F0, a0 + 140);
    swc1(F0, t5 + 8);
    sw(t5 + 12, zero);
    sw(t4, zero);
    sw(t4 + 4, zero);
    lwc1(F0, a0 + 144);
    swc1(F0, t4 + 8);
    sw(t4 + 12, zero);
    // the screen centre: 2048 + raster x - parent width / 2 + width / 2, then the same for y
    t5 = lh(t3 + 28);
    t4 = lw(t3);
    t6 = addiu(t5, 2048);
    t5 = lw(t4 + 12);
    half(t4, t5);
    charge(4);
    t5 = lw(t3 + 12);
    t6 = subu(t6, t4);
    half(t4, t5);
    charge(11);
    t4 = addu(t4, t6);
    mtc1(t4, F0);
    cvt_s_w(F0, F0);
    swc1(F0, a1);
    t5 = lh(t3 + 30);
    t4 = lw(t3);
    t6 = addiu(t5, 2048);
    t5 = lw(t4 + 16);
    half(t4, t5);
    charge(4);
    t5 = lw(t3 + 16);
    t6 = subu(t6, t4);
    half(t4, t5);
    charge(12);
    t4 = addu(t4, t6);
    sw(a1 + 8, zero);
    mtc1(t4, F0);
    sw(a1 + 12, zero);
    cvt_s_w(F0, F0);
    swc1(F0, a1 + 4);
    // the parent's centre: 2048 + raster x - parent width / 2 (and y)
    t5 = lh(t3 + 28);
    t4 = lw(t3);
    t6 = addiu(t5, 2048);
    t5 = lw(t4 + 12);
    half(t4, t5);
    charge(11);
    t4 = subu(t6, t4);
    mtc1(t4, F0);
    cvt_s_w(F0, F0);
    swc1(F0, a2);
    t5 = lh(t3 + 30);
    t4 = lw(t3);
    t6 = addiu(t5, 2048);
    t5 = lw(t4 + 16);
    half(t4, t5);
    charge(8);
    t4 = subu(t6, t4);
    sw(a2 + 8, zero);
    mtc1(t4, F0);
    sw(a2 + 12, zero);
    cvt_s_w(F0, F0);
    t4 = lw(gp - 16860);
    swc1(F0, a2 + 4);
    // the z scale: -255 / (far (or the fog far gp-16864) - zshift)
    if (t4 != 0) {
        charge(13);
        lwc1(F1, a0 + 132);
        a2 = lui(0xC37F);
        mtc1(a2, F0);
        swc1(F1, v1 + 12);
        lwc1(F2, a0 + 132);
        lwc1(F1, a0 + 136);
        sub_s(F1, F2, F1);
        div_s(F0, F0, F1);
        swc1(F0, v1 + 8);
    } else {
        charge(8);
        lwc1(F2, gp - 16864);
        a2 = lui(0xC37F);
        mtc1(a2, F0);
        swc1(F2, v1 + 12);
        lwc1(F1, a0 + 136);
        sub_s(F1, F2, F1);
        div_s(F0, F0, F1);
        swc1(F0, v1 + 8);
    }
    // the guard band: x range min(cx, 4095 - cx) and its reciprocal
    charge(15);
    lwc1(F4, a0 + 132);
    v1 = lui(0x3F80);
    lwc1(F3, a0 + 128);
    mtc1(v1, F0);
    lwc1(F2, a1);
    v1 = lui(0x457F);
    v1 = v1 | 0xFF00;  // 4095.0
    mtc1(v1, F1);
    sub_s(F3, F4, F3);
    div_s(F0, F0, F3);  // 1 / (far - near)
    sub_s(F1, F1, F2);
    c_le_s(F2, F1);
    charge(2);
    if (!cop1_cond()) mov_s(F2, F1);
    v1 = lui(0x3F80);
    charge(13);
    mtc1(v1, F1);
    lwc1(F3, a1 + 4);
    div_s(F1, F1, F2);
    v1 = lui(0x457F);
    v1 = v1 | 0xFF00;
    swc1(F1, t2 + 4);
    mtc1(v1, F1);
    swc1(F2, t2);
    lwc1(F2, a0 + 132);
    sub_s(F1, F1, F3);
    c_le_s(F3, F1);
    swc1(F2, t2 + 12);
    charge(2);
    if (!cop1_cond()) mov_s(F3, F1);
    v1 = lui(0x3F80);
    charge(45);
    mtc1(v1, F2);
    swc1(F3, t1);
    div_s(F1, F2, F3);
    v1 = 1;
    swc1(F1, t1 + 4);
    lwc1(F1, a0 + 128);
    swc1(F1, t1 + 12);
    // the clip half-sizes: width / 2 + 5, height / 2 + 5, and their reciprocals
    for (unsigned axis = 0; axis < 2; ++axis) {
        const Gpr& out = axis == 0 ? t0 : a3;
        a1 = lw(t3 + 12 + 4 * axis);
        a1 = sra(a1, 1);
        a1 = addiu(a1, 5);
        mtc1(a1, F1);
        cvt_s_w(F1, F1);
        swc1(F1, out);
        a1 = lw(t3 + 12 + 4 * axis);
        a1 = sra(a1, 1);
        a1 = addiu(a1, 5);
        mtc1(a1, F1);
        cvt_s_w(F1, F1);
        div_s(F1, F2, F1);
        swc1(F1, out + 4);
        lwc1(F1, a0 + 132 - 4 * axis);  // the far plane for x, the near plane for y
        swc1(F1, out + 12);
    }
    a1 = lw(a0 + 20);
    if (a1 == v1) {  // perspective: -2 far near / (far - near), (far + near) / (far - near); bit 3 cleared
        charge(19);
        lwc1(F2, a0 + 132);
        a1 = lui(0xC000);
        mtc1(a1, F3);
        v1 = lbu(gp - 16892);
        lwc1(F1, a0 + 128);
        mul_s(F2, F3, F2);
        v1 = v1 & 0xF7;
        mul_s(F1, F2, F1);
        mul_s(F1, F0, F1);
        swc1(F1, t0 + 8);
        swc1(F1, t2 + 8);
        lwc1(F2, a0 + 132);
        lwc1(F1, a0 + 128);
        add_s(F1, F2, F1);
        sb(gp - 16892, v1);
        mul_s(F0, F0, F1);
        swc1(F0, a3 + 8);
        swc1(F0, t1 + 8);
    } else {  // parallel: -(far + near) / (far - near), 2 / (far - near); bit 3 set
        charge(16);
        a1 = lui(0x4000);
        v1 = lbu(gp - 16892);
        mtc1(a1, F1);
        neg_s(F2, F0);
        lwc1(F4, a0 + 132);
        lwc1(F3, a0 + 128);
        mul_s(F0, F1, F0);
        v1 = v1 | 8;
        add_s(F1, F4, F3);
        sb(gp - 16892, v1);
        mul_s(F1, F2, F1);
        swc1(F1, t0 + 8);
        swc1(F1, t2 + 8);
        swc1(F0, a3 + 8);
        swc1(F0, t1 + 8);
    }
    charge(2);
}

// skyFillInPktForUpLoadAlignedContiguousRectangle(packet, address, bytes): builds, at the packet rounded up to 64
// bytes, the PATH2 upload chain of `bytes` (rounded to qwords) from guest `address`: per chunk of at most 0x7FEE
// qwords a `cnt` tag + NOP/DIRECT pair {DIRECT 0x50000000 | qwc, FLUSH...} and a `ref` tag to the data (0x30000000 |
// qwc, address advanced by 0x7FEE0 per chunk); then the closing `cnt` + the IMAGE-end GIF tag (A+D TEXFLUSH, the
// template quadword at 0x965A40). Writes the data cache back (SyncDCache(start, end + 127)); returns the packet.
void Cpu::skyFillInPktForUpLoadAlignedContiguousRectangle() {
    enter(33);
    sp = addiu(sp, -48);
    v0 = daddiu(a2, 15);
    v0 = dsrl(v0, 4);   // qwords
    sd(sp + 32, ra);
    t4 = dsll32(v0, 0);
    a2 = lui(0x5000);
    sq(sp + 16, s1);
    v1 = a2 | 1;
    v0 = lui(0x1000);
    sq(sp, s0);
    v1 = dsll32(v1, 0);
    v0 = v0 | 1;
    pcpyld(t2, v1, v0);  // {cnt 1, DIRECT 1}
    s0 = a0;
    v0 = si(-64);
    v1 = addiu(s0, 63);
    t4 = dsra32(t4, 0);
    a0 = v1 & v0;
    a3 = addiu(t4, 32749);
    v0 = lui(0x8012);
    t5 = zero;
    v0 = v0 | 0x289;
    t3 = a0;
    mult(zero, v0, a3);  // (qwc + 0x7FED) / 0x7FEE through the magic reciprocal
    v1 = srl(a3, 31);
    mfhi(v0);
    v0 = addu(v0, a3);
    v0 = sra(v0, 14);
    v1 = addu(v0, v1);   // chunks
    at = slt(zero, v1);
    if (at != 0) {
        charge(3);
        at = slt(zero, v1);
        a3 = zero;
        if (at != 0) {
            charge(6);
            v0 = lui(0x800);
            t1 = lui(0x7);
            t0 = 3;
            t6 = 0x7FEE;
            v0 = dsll32(v0, 0);
            t7 = t1 | 0xFEE0;
            for (;;) {
                charge(3);
                at = slti(t4, 32751);
                sq(t3, t2);
                if (at == 0) {  // a full chunk of 0x7FEE qwords
                    charge(3);
                    t1 = t6;
                    s1 = zero;
                    backedge();
                } else {
                    charge(3);
                    t1 = t4;
                    s1 = zero;
                }
                charge(27);
                s1 = sll(s1, 15);
                t8 = t1 | s1;
                t5 = addiu(t5, 1);
                t8 = dsll32(t8, 0);
                s1 = dsll32(t1, 0);
                t8 = dsrl32(t8, 0);
                s1 = dsrl32(s1, 0);
                t8 = t8 | v0;
                s1 = s1 | a2;
                pcpyld(t8, a3, t8);
                sq(t3 + 16, t8);
                s1 = dsll32(s1, 0);
                t8 = dsll32(a1, 0);
                t4 = addiu(t4, -32750);
                t8 = dsrl32(t8, 0);
                a1 = addu(a1, t7);
                t9 = dsll32(t8, 0);
                t8 = sll(t0, 28);
                t1 = t1 | t8;
                t1 = dsll32(t1, 0);
                t1 = dsrl32(t1, 0);
                t1 = t9 | t1;
                pcpyld(t1, s1, t1);
                sq(t3 + 32, t1);
                t1 = slt(t5, v1);
                t3 = addiu(t3, 48);
                if (t1 == 0) break;
                backedge();
            }
            charge(1);
        }
    }
    charge(22);
    v0 = lui(0x5000);
    v1 = v0 | 2;
    a2 = 0xE;
    v0 = lui(0x6000);
    v1 = dsll32(v1, 0);
    v0 = v0 | 2;
    pcpyld(v0, v1, v0);
    sq(t3, v0);
    v1 = 0x8001;
    v0 = lui(0x1000);
    a1 = dsll32(v0, 0);
    a1 = v1 | a1;
    v0 = lui(0x96);
    pcpyld(a1, a2, a1);
    sq(t3 + 16, a1);
    v1 = addiu(t3, 48);
    lq(v0, v0 + 23104);
    a1 = addiu(v1, 127);
    sq(t3 + 32, v0);
    jal(0x4EF198u, gen::fn_SyncDCache_00503a58);
    v0 = s0;
    charge(5);
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}

// sub_4EF770 [the texture upload through PATH3, by rows]: $a0 width, $a1 rows, $a2 the first row's address, $a3 the
// destination TBP, $t0 TBW, $t1 the bits per pixel, $t2 PSM, $t3 the row stride. Opens a GIF packet of 10 qwords
// (_rwDMAOpenGIFPkt), reserves (rows + 1) * 48 bytes of DMA space (sub_4D5FE0) for the reference chain, reopens; the
// header: a `cnt` with BITBLTBUF / TRXPOS / TRXREG / TRXDIR (templates at 0x965A50 / 0x965A40 / 0x965A60 / 0x965A70,
// TRXREG = (qwc * 128 / bpp) x rows through __udivdi3); then per row {cnt + DIRECT, IMAGE tag, ref to the row}, the
// closing IMAGE-end, SyncDCache over the chain.
void Cpu::sub_4EF770() {
    enter(102);
    sp = addiu(sp, -176);
    v1 = lui(0x5000);
    sd(sp + 144, ra);
    v0 = lui(0x1000);
    sq(sp + 128, fp);
    v1 = v1 | 1;
    sq(sp + 112, s7);
    v0 = v0 | 1;
    sq(sp + 96, s6);
    v1 = dsll32(v1, 0);
    sq(sp + 80, s5);
    s7 = a3;
    sq(sp + 64, s4);
    s5 = t1;
    sq(sp + 48, s3);
    s4 = a1;
    sq(sp + 32, s2);
    s3 = a2;
    sq(sp + 16, s1);
    fp = t0;
    sq(sp, s0);
    s2 = t3;
    pcpyld(s0, v1, v0);
    sw(sp + 172, t2);
    mult(v0, a0, s5);   // width * bpp
    v0 = srl(v0, 3);
    a0 = 0xA;
    v0 = addiu(v0, 15);
    v0 = srl(v0, 4);
    s6 = dsll32(v0, 0);
    s6 = dsrl32(s6, 0);  // qwords per row
    jal(0x4EF7E8u, gen::fn__rwDMAOpenGIFPkt_004d54e0);
    v1 = addiu(s4, 1);
    a1 = zero;
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    a0 = sll(v0, 4);
    jal(0x4EF800u, gen::fn_sub_4D5FE0_004d5fe0);
    s1 = v0;
    a0 = 0xA;
    jal(0x4EF80Cu, gen::fn__rwDMAOpenGIFPkt_004d54e0);
    v0 = lwu(sp + 172);
    a1 = dsll32(s5, 0);
    a0 = dsll32(s1, 0);
    s5 = lw(gp - 17148);  // the scratchpad write pointer
    a0 = dsrl32(a0, 0);
    a2 = lui(0x96);
    a0 = dsll32(a0, 0);
    a1 = dsrl32(a1, 0);
    v1 = v0;
    v0 = s7 & 0x3FFF;
    t0 = dsll32(v1, 24);
    t1 = dsll32(v0, 0);
    v1 = dsll(v1, 24);
    v0 = dsll32(fp, 0);
    v0 = dsrl32(v0, 0);
    a3 = dsll32(v0, 16);
    v0 = lui(0x5000);
    a3 = t0 | a3;
    v0 = v0 | 6;
    t1 = t1 | a3;
    v0 = a0 | v0;
    t1 = v1 | t1;
    a0 = zero;
    t0 = lui(0xA);
    pcpyld(v0, a0, v0);
    a0 = lui(0x96);
    sq(s5, v0);
    lq(v0, a0 + 23152);
    a3 = 0x50;
    t0 = t1 | t0;
    v1 = lui(0x96);
    pcpyld(a3, a3, t0);  // BITBLTBUF
    sq(s5 + 16, v0);
    a0 = dsll(s6, 7);
    lq(v0, a2 + 23104);
    sq(s5 + 32, v0);
    sq(s5 + 48, a3);
    lq(v0, v1 + 23120);
    sq(s5 + 64, v0);
    jal(0x4EF8ACu, gen::fn___udivdi3_0052fe98);
    v1 = dsll32(v0, 0);
    at = sltu(zero, s4);
    v1 = dsra32(v1, 0);
    v0 = dsll32(s4, 0);
    v0 = dsrl32(v0, 0);
    v1 = dsll32(v1, 0);
    v1 = dsrl32(v1, 0);
    v0 = dsll32(v0, 0);
    v1 = v0 | v1;
    v0 = 0x52;
    pcpyld(v0, v0, v1);  // TRXREG
    sq(s5 + 80, v0);
    v1 = zero;
    v0 = lui(0x96);
    lq(a0, v0 + 23136);
    sq(s5 + 96, a0);
    v0 = s1;
    a0 = lw(gp - 17148);
    a0 = addiu(a0, 112);
    sw(gp - 17148, a0);
    if (at != 0) {
        charge(6);
        a0 = lui(0x5000);
        at = sltu(zero, s4);
        a0 = s6 | a0;
        t0 = zero;
        a3 = dsll32(a0, 0);
        if (at != 0) {
            charge(6);
            a1 = lui(0x800);
            a0 = lui(0x3000);
            a2 = dsll32(a1, 0);
            a1 = s6 | a0;
            a0 = s6 | a2;
            pcpyld(a2, t0, a0);
            for (;;) {  // the rows
                charge(13);
                a0 = dsll32(s3, 0);
                sq(v0, s0);
                a0 = dsrl32(a0, 0);
                sq(v0 + 16, a2);
                a0 = dsll32(a0, 0);
                v1 = addiu(v1, 1);
                a0 = a0 | a1;
                s3 = addu(s3, s2);
                pcpyld(a0, a3, a0);
                sq(v0 + 32, a0);
                a0 = sltu(v1, s4);
                v0 = addiu(v0, 48);
                if (a0 == 0) break;
                backedge();
            }
            charge(1);
        }
    }
    charge(32);
    a1 = lui(0x5000);
    a2 = a1 | 2;
    v1 = lui(0x1000);
    a3 = dsll32(a2, 0);
    a1 = v1 | 2;
    a2 = dsll32(v1, 0);
    a0 = s1;
    pcpyld(v1, a3, a1);
    a1 = 0x8001;
    sq(v0, v1);
    a2 = a1 | a2;
    a3 = 0xE;
    pcpyld(a2, a3, a2);
    v1 = lui(0x96);
    sq(v0 + 16, a2);
    lq(v1, v1 + 23104);
    a1 = addiu(v0, 48);
    a1 = addiu(a1, 127);
    sq(v0 + 32, v1);
    jal(0x4EF9B8u, gen::fn_SyncDCache_00503a58);
    ra = ld(sp + 144);
    lq(fp, sp + 128);
    lq(s7, sp + 112);
    lq(s6, sp + 96);
    lq(s5, sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 176);
}

// =========================================================================================================
// [raster] the CPU swizzles of a locked raster (GS PSMT8 / PSMT4 block order <-> linear), in 4-row bands
// =========================================================================================================
//
// The raster's lock record: +4 the pixels, +12 the row length in bytes, +16 the rows, +24 the stride. Each band of 4
// rows is copied through the 4 KiB (PSMT8) / 2 KiB (PSMT4) frame buffer: the GS column order of a byte / nibble
// within its 16 x 4 (32 x 4) column is the bit shuffle written out in each loop (bit 1 -> 3, 2 -> 0, 3 -> 1, 4 -> 2,
// 5 -> 4 (or 6 -> 5 for PSMT4), bit 0 -> 5 / 6 and 2, with bit 2 of the band index flipping the column parity).

// sub_4DD480 [swizzle a PSMT8 raster in place]: per band the four rows are read as quadwords (rows r and r + 2 through
// the HI/LO pipes 0 and 1: two mult / mult1 per pair), each of their 64 bytes stored at its shuffled place in the
// frame buffer at sp + 176 (16-byte columns, 1 KiB per row), then the four 1 KiB rows written back over the band.
void Cpu::sub_4DD480() {
    enter(12);
    sp = addiu(sp, -4272);
    sq(sp + 96, s6);
    sq(sp + 80, s5);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    v1 = lw(a0 + 16);
    at = slt(zero, v1);
    t7 = zero;  // the band's first row
    bool run = at != 0;
    if (run) {
        charge(3);
        at = slt(zero, v1);
        t4 = addiu(sp, 112);
        run = at != 0;
    }
    if (run) {
        charge(4);
        t3 = addiu(sp, 128);
        t2 = addiu(sp, 144);
        t1 = addiu(sp, 160);
        s1 = addiu(sp, 176);
        for (;;) {  // the bands
            charge(4);
            t5 = lw(a0 + 12);
            at = slt(zero, t5);
            t8 = zero;
            if (at != 0) {
                charge(5);
                a3 = lw(a0 + 24);
                t6 = zero;
                a2 = lw(a0 + 4);
                t0 = t7 & 4;
                a1 = addiu(t7, 2);
                for (;;) {  // 16-byte columns of the band (t8 the byte offset, t6 = 2 * t8)
                    charge(24);
                    mult(v1, t7, a3);
                    v1 = addu(a2, v1);
                    v1 = addu(v1, t6);
                    lq(v1, v1);
                    sq(sp + 112, v1);
                    mult1(v1, t7, a3);
                    v1 = addu(a2, v1);
                    v1 = addu(v1, t6);
                    lq(v1, v1 + 16);
                    sq(t3, v1);
                    mult(v1, a1, a3);
                    v1 = addu(a2, v1);
                    v1 = addu(v1, t6);
                    lq(v1, v1);
                    sq(t2, v1);
                    mult1(v1, a1, a3);
                    s0 = zero;
                    v1 = addu(a2, v1);
                    t5 = addu(v1, t6);
                    lq(t5, t5 + 16);
                    v1 = addu(t8, sp);
                    v1 = addiu(v1, 176);
                    sq(t1, t5);
                    for (;;) {  // the four 16-byte rows of the column (s0)
                        charge(2);
                        t9 = zero;
                        t5 = addu(t4, s0);
                        for (;;) {  // the 16 bytes (t9)
                            charge(2);
                            if (t0 != 0) {
                                charge(23);
                                s4 = addu(s0, t9);
                                s3 = s4 & 2;
                                s2 = s4 & 4;
                                s3 = sll(s3, 2);
                                s2 = sra(s2, 2);
                                s5 = s3 | s2;
                                s2 = s4 & 8;
                                s3 = sra(s2, 2);
                                s2 = s4 & 0x10;
                                s3 = s3 | s5;
                                s2 = sra(s2, 2);
                                s5 = s2 | s3;
                                s2 = s4 & 0x20;
                                s3 = sra(s2, 1);
                                s2 = s4 & 1;
                                s3 = s3 | s5;
                                s4 = ~s4;
                                s2 = sll(s2, 5);
                                s4 = s4 & 1;
                                s4 = sll(s4, 2);
                                s2 = s2 | s4;
                                s4 = s3 ^ s2;
                            } else {
                                charge(20);
                                s4 = addu(s0, t9);
                                s2 = s4 & 2;
                                s5 = s4 & 4;
                                s6 = sra(s5, 2);
                                s2 = sll(s2, 2);
                                s5 = s4 & 8;
                                s6 = s2 | s6;
                                s2 = sra(s5, 2);
                                s3 = s4 & 1;
                                s5 = s4 & 0x10;
                                s2 = s2 | s6;
                                s5 = sra(s5, 2);
                                s4 = s4 & 0x20;
                                s5 = s5 | s2;
                                s2 = sra(s4, 1);
                                s5 = s2 | s5;
                                s4 = sll(s3, 5);
                                s2 = sll(s3, 2);
                                s2 = s4 | s2;
                                s4 = s5 ^ s2;
                            }
                            charge(11);
                            s2 = lbu(t5);
                            s3 = sra(s4, 4);
                            t9 = addiu(t9, 1);
                            s3 = sll(s3, 10);
                            s4 = s4 & 0xF;
                            s5 = addu(v1, s3);
                            s4 = addu(s5, s4);
                            s3 = slti(t9, 16);
                            sb(s4, s2);
                            t5 = addiu(t5, 1);
                            if (s3 == 0) break;
                            backedge();
                        }
                        charge(4);
                        s0 = addiu(s0, 16);
                        t5 = slti(s0, 64);
                        if (t5 == 0) break;
                        backedge();
                    }
                    charge(5);
                    t5 = lw(a0 + 12);
                    t8 = addiu(t8, 16);
                    v1 = slt(t8, t5);
                    t6 = addiu(t6, 32);
                    if (v1 == 0) break;
                    backedge();
                }
            }
            // the four 1 KiB rows of the frame buffer back over the band
            charge(2);
            s0 = zero;
            t6 = s1;
            for (;;) {
                charge(3);
                at = slt(zero, t5);
                t0 = zero;
                if (at != 0) {
                    charge(1);
                    a3 = addu(t7, s0);
                    for (;;) {
                        charge(13);
                        v1 = addu(t6, t0);
                        lq(a2, v1);
                        v1 = lw(a0 + 24);
                        mult(a1, v1, a3);
                        v1 = lw(a0 + 4);
                        v1 = addu(v1, a1);
                        v1 = addu(v1, t0);
                        sq(v1, a2);
                        t0 = addiu(t0, 16);
                        t5 = lw(a0 + 12);
                        v1 = slt(t0, t5);
                        if (v1 == 0) break;
                        backedge();
                    }
                    charge(1);
                }
                charge(4);
                s0 = addiu(s0, 1);
                v1 = slti(s0, 4);
                t6 = addiu(t6, 1024);
                if (v1 == 0) break;
                backedge();
            }
            charge(5);
            v1 = lw(a0 + 16);
            t7 = addiu(t7, 4);
            v1 = slt(t7, v1);
            if (v1 == 0) break;
            backedge();
        }
        charge(1);
    }
    charge(9);
    lq(s6, sp + 96);
    lq(s5, sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 4272);
}

// sub_4DD700 [swizzle a PSMT4 raster in place]: as sub_4DD480 with nibbles: per 32-byte column the 128 nibbles of the
// band's four rows are ORed into the cleared 2 KiB frame buffer at sp + 144 (512-byte rows) at their shuffled places
// (high / low nibble by the parities of the source and the destination), then written back.
void Cpu::sub_4DD700() {
    enter(10);
    sp = addiu(sp, -2192);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    v1 = lw(a0 + 16);
    at = slt(zero, v1);
    t8 = zero;
    bool run = at != 0;
    if (run) {
        charge(3);
        at = slt(zero, v1);
        t5 = addiu(sp, 80);
        run = at != 0;
    }
    if (run) {
        charge(4);
        t4 = addiu(sp, 96);
        t3 = addiu(sp, 112);
        t2 = addiu(sp, 128);
        v1 = addiu(sp, 144);
        for (;;) {  // the bands (t8)
            charge(4);
            a1 = lw(a0 + 12);
            at = slt(zero, a1);
            t9 = zero;
            if (at != 0) {
                charge(5);
                t0 = lw(a0 + 24);
                t7 = zero;
                a3 = lw(a0 + 4);
                t1 = t8 & 4;
                a2 = addiu(t8, 2);
                for (;;) {  // 32-byte columns (t9; t7 = t9 / 2 into the frame buffer)
                    charge(44);
                    mult(a1, t8, t0);
                    a1 = addu(a3, a1);
                    a1 = addu(a1, t9);
                    lq(a1, a1);
                    sq(sp + 80, a1);
                    mult1(a1, t8, t0);
                    a1 = addu(a3, a1);
                    a1 = addu(a1, t9);
                    lq(a1, a1 + 16);
                    sq(t4, a1);
                    mult(a1, a2, t0);
                    a1 = addu(a3, a1);
                    a1 = addu(a1, t9);
                    lq(a1, a1);
                    sq(t3, a1);
                    mult1(a1, a2, t0);
                    s2 = zero;
                    t6 = addu(a3, a1);
                    a1 = addu(t7, sp);
                    sd(a1 + 144, zero);
                    a1 = addu(t6, t9);
                    lq(s0, a1 + 16);
                    a1 = addiu(t7, 8);
                    sq(t2, s0);
                    t6 = addu(a1, sp);
                    a1 = addiu(t7, 512);
                    sd(t6 + 144, zero);
                    a1 = addu(a1, sp);
                    sd(a1 + 144, zero);
                    a1 = addiu(t7, 520);
                    t6 = addu(a1, sp);
                    a1 = addiu(t7, 1024);
                    sd(t6 + 144, zero);
                    t6 = addu(a1, sp);
                    a1 = addiu(t7, 1032);
                    sd(t6 + 144, zero);
                    a1 = addu(a1, sp);
                    sd(a1 + 144, zero);
                    a1 = addiu(t7, 1536);
                    t6 = addu(a1, sp);
                    a1 = addiu(t7, 1544);
                    sd(t6 + 144, zero);
                    a1 = addu(a1, sp);
                    sd(a1 + 144, zero);
                    for (;;) {  // the four 32-nibble rows (s2 by 32)
                        charge(1);
                        s1 = zero;
                        for (;;) {  // the 32 nibbles (s1)
                            charge(2);
                            if (t1 != 0) {
                                charge(26);
                                t6 = addu(s2, s1);
                                s0 = t6 & 2;
                                a1 = t6 & 0x20;
                                s0 = sll(s0, 2);
                                a1 = sra(a1, 1);
                                s3 = s0 | a1;
                                a1 = t6 & 4;
                                s0 = sra(a1, 2);
                                a1 = t6 & 8;
                                s0 = s0 | s3;
                                a1 = sra(a1, 2);
                                s3 = a1 | s0;
                                a1 = t6 & 0x10;
                                s0 = sra(a1, 2);
                                a1 = t6 & 0x40;
                                s0 = s0 | s3;
                                a1 = sra(a1, 1);
                                a1 = a1 | s0;
                                s0 = t6 & 1;
                                s3 = sll(s0, 6);
                                s0 = ~t6;
                                s0 = s0 & 1;
                                s0 = sll(s0, 2);
                                s0 = s3 | s0;
                                s0 = a1 ^ s0;
                            } else {
                                charge(23);
                                t6 = addu(s2, s1);
                                s0 = t6 & 2;
                                a1 = t6 & 1;
                                s4 = sll(s0, 2);
                                s0 = t6 & 0x20;
                                s3 = sra(s0, 1);
                                s0 = t6 & 4;
                                s3 = s4 | s3;
                                s0 = sra(s0, 2);
                                s4 = s0 | s3;
                                s0 = t6 & 8;
                                s3 = sra(s0, 2);
                                s0 = t6 & 0x10;
                                s3 = s3 | s4;
                                s0 = sra(s0, 2);
                                s4 = s0 | s3;
                                s0 = t6 & 0x40;
                                s3 = sra(s0, 1);
                                s0 = sll(a1, 6);
                                s3 = s3 | s4;
                                a1 = sll(a1, 2);
                                a1 = s0 | a1;
                                s0 = s3 ^ a1;
                            }
                            charge(3);
                            a1 = s0 & 1;
                            if (a1 != 0) {  // into the destination's high nibble
                                charge(3);
                                a1 = s1 & 1;
                                charge(5);
                                a1 = sra(t6, 1);
                                a1 = addu(t5, a1);
                                a1 = lbu(a1);
                                if ((s1.u() & 1) != 0) {
                                    a1 = a1 & 0xF0;
                                } else {
                                    a1 = a1 & 0xF;
                                    a1 = sll(a1, 4);
                                }
                                charge(12);
                                t6 = sra(s0, 5);
                                a1 = a1 & 0xFF;
                                s3 = sll(t6, 10);
                                t6 = s0 & 0x1F;
                                t6 = addu(t9, t6);
                                t6 = addu(s3, t6);
                                t6 = sra(t6, 1);
                                s0 = addu(t6, sp);
                                t6 = lbu(s0 + 144);
                                a1 = t6 | a1;
                                sb(s0 + 144, a1);
                            } else {  // into the low nibble
                                charge(3);
                                a1 = s1 & 1;
                                if (a1 != 0) {
                                    charge(6);
                                    a1 = sra(t6, 1);
                                    a1 = addu(t5, a1);
                                    a1 = lbu(a1);
                                    a1 = a1 & 0xF0;
                                    a1 = sra(a1, 4);
                                } else {
                                    charge(4);
                                    a1 = sra(t6, 1);
                                    a1 = addu(t5, a1);
                                    a1 = lbu(a1);
                                    a1 = a1 & 0xF;
                                }
                                charge(11);
                                t6 = sra(s0, 5);
                                a1 = a1 & 0xFF;
                                s3 = sll(t6, 10);
                                t6 = s0 & 0x1F;
                                t6 = addu(t9, t6);
                                t6 = addu(s3, t6);
                                t6 = sra(t6, 1);
                                s0 = addu(t6, sp);
                                t6 = lbu(s0 + 144);
                                a1 = t6 | a1;
                                sb(s0 + 144, a1);
                            }
                            charge(4);
                            s1 = addiu(s1, 1);
                            a1 = slti(s1, 32);
                            if (a1 == 0) break;
                            backedge();
                        }
                        charge(4);
                        s2 = addiu(s2, 32);
                        a1 = slti(s2, 128);
                        if (a1 == 0) break;
                        backedge();
                    }
                    charge(5);
                    a1 = lw(a0 + 12);
                    t9 = addiu(t9, 32);
                    t6 = slt(t9, a1);
                    t7 = addiu(t7, 16);
                    if (t6 == 0) break;
                    backedge();
                }
            }
            // the four 512-byte rows back over the band
            charge(2);
            a3 = zero;
            a2 = v1;
            for (;;) {
                charge(4);
                t0 = sra(a1, 1);
                at = slt(zero, t0);
                t7 = zero;
                if (at != 0) {
                    charge(1);
                    t6 = addu(t8, a3);
                    for (;;) {
                        charge(14);
                        a1 = addu(a2, t7);
                        lq(t1, a1);
                        a1 = lw(a0 + 24);
                        mult(t0, a1, t6);
                        a1 = lw(a0 + 4);
                        a1 = addu(a1, t0);
                        a1 = addu(a1, t7);
                        sq(a1, t1);
                        t7 = addiu(t7, 16);
                        a1 = lw(a0 + 12);
                        t0 = sra(a1, 1);
                        t0 = slt(t7, t0);
                        if (t0 == 0) break;
                        backedge();
                    }
                    charge(2);
                    a3 = addiu(a3, 1);
                } else {
                    charge(1);
                    a3 = addiu(a3, 1);
                }
                charge(3);
                t0 = slti(a3, 4);
                a2 = addiu(a2, 512);
                if (t0 == 0) break;
                backedge();
            }
            charge(5);
            a1 = lw(a0 + 16);
            t8 = addiu(t8, 4);
            a1 = slt(t8, a1);
            if (a1 == 0) break;
            backedge();
        }
        charge(2);
        backedge();
    }
    charge(2);
    lq(s4, sp + 64);
    charge(6);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 2192);
}

// sub_4DDAA0 [unswizzle a PSMT8 raster in place]: per band the four rows go to the 4 KiB frame buffer at sp + 144
// (1 KiB per row), then each 16-byte column of the band is gathered from its shuffled places into sp + 80 .. + 143
// and written back as the four rows' quadwords (rows r / r + 2 through the HI/LO pipes 0 and 1).
void Cpu::sub_4DDAA0() {
    enter(10);
    sp = addiu(sp, -4240);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    v1 = lw(a0 + 16);
    at = slt(zero, v1);
    t9 = zero;
    bool run = at != 0;
    if (run) {
        charge(3);
        at = slt(zero, v1);
        t5 = addiu(sp, 80);
        run = at != 0;
    }
    if (run) {
        charge(4);
        t4 = addiu(sp, 96);
        t3 = addiu(sp, 112);
        t2 = addiu(sp, 128);
        t1 = addiu(sp, 144);
        for (;;) {  // the bands (t9)
            charge(3);
            t7 = lw(a0 + 12);
            s3 = zero;
            s1 = t1;
            for (;;) {  // the four rows into the frame buffer (s3)
                charge(4);
                at = slt(zero, t7);
                s2 = zero;
                s0 = t7;
                if (at != 0) {
                    charge(4);
                    t0 = lw(a0 + 24);
                    t6 = addu(t9, s3);
                    a3 = lw(a0 + 4);
                    s0 = lw(a0 + 12);
                    for (;;) {
                        charge(9);
                        mult(v1, t0, t6);
                        a1 = addu(s1, s2);
                        v1 = addu(a3, v1);
                        v1 = addu(v1, s2);
                        lq(a2, v1);
                        s2 = addiu(s2, 16);
                        v1 = slt(s2, s0);
                        sq(a1, a2);
                        if (v1 == 0) break;
                        backedge();
                    }
                    charge(1);
                }
                charge(4);
                s3 = addiu(s3, 1);
                v1 = slti(s3, 4);
                s1 = addiu(s1, 1024);
                if (v1 == 0) break;
                backedge();
            }
            charge(3);
            at = slt(zero, s0);
            t6 = zero;
            if (at != 0) {
                charge(3);
                t8 = zero;
                t0 = t9 & 4;
                v1 = addiu(t9, 2);
                for (;;) {  // 16-byte columns (t6; t8 = 2 * t6 in the rows)
                    charge(4);
                    a1 = addu(t6, sp);
                    s1 = zero;
                    a3 = addiu(a1, 144);
                    for (;;) {  // the four 16-byte rows of the column (s1)
                        charge(2);
                        s0 = zero;
                        t7 = addu(t5, s1);
                        for (;;) {  // the 16 bytes (s0)
                            charge(2);
                            if (t0 != 0) {
                                charge(23);
                                a2 = addu(s1, s0);
                                s2 = a2 & 2;
                                a1 = a2 & 4;
                                s2 = sll(s2, 2);
                                a1 = sra(a1, 2);
                                s3 = s2 | a1;
                                a1 = a2 & 8;
                                s2 = sra(a1, 2);
                                a1 = a2 & 0x10;
                                s2 = s2 | s3;
                                a1 = sra(a1, 2);
                                s3 = a1 | s2;
                                a1 = a2 & 0x20;
                                s2 = a2 & 1;
                                a2 = ~a2;
                                a1 = sra(a1, 1);
                                a2 = a2 & 1;
                                s2 = sll(s2, 5);
                                a2 = sll(a2, 2);
                                a1 = a1 | s3;
                                a2 = s2 | a2;
                                s2 = a1 ^ a2;
                            } else {
                                charge(20);
                                a2 = addu(s1, s0);
                                s2 = a2 & 2;
                                a1 = a2 & 1;
                                s4 = sll(s2, 2);
                                s2 = a2 & 4;
                                s3 = sra(s2, 2);
                                s2 = a2 & 8;
                                s3 = s4 | s3;
                                s2 = sra(s2, 2);
                                s3 = s2 | s3;
                                s2 = a2 & 0x10;
                                s2 = sra(s2, 2);
                                a2 = a2 & 0x20;
                                s2 = s2 | s3;
                                a2 = sra(a2, 1);
                                s2 = a2 | s2;
                                a2 = sll(a1, 5);
                                a1 = sll(a1, 2);
                                a1 = a2 | a1;
                                s2 = s2 ^ a1;
                            }
                            charge(11);
                            a1 = sra(s2, 4);
                            a2 = sll(a1, 10);
                            s0 = addiu(s0, 1);
                            a1 = s2 & 0xF;
                            a2 = addu(a3, a2);
                            a2 = addu(a2, a1);
                            a2 = lbu(a2);
                            a1 = slti(s0, 16);
                            sb(t7, a2);
                            t7 = addiu(t7, 1);
                            if (a1 == 0) break;
                            backedge();
                        }
                        charge(4);
                        s1 = addiu(s1, 16);
                        a1 = slti(s1, 64);
                        if (a1 == 0) break;
                        backedge();
                    }
                    // the column's four quadwords back into rows r, r + 1 (pipe 1), r + 2, r + 3 (pipe 1)
                    charge(33);
                    a1 = lw(a0 + 24);
                    lq(t7, sp + 80);
                    mult(a2, t9, a1);
                    lq(a3, t4);
                    a1 = lw(a0 + 4);
                    a1 = addu(a1, a2);
                    a1 = addu(a1, t8);
                    sq(a1, t7);
                    a1 = lw(a0 + 24);
                    mult1(a2, t9, a1);
                    lq(t7, t3);
                    a1 = lw(a0 + 4);
                    a1 = addu(a1, a2);
                    a1 = addu(a1, t8);
                    sq(a1 + 16, a3);
                    a1 = lw(a0 + 24);
                    mult(a2, v1, a1);
                    lq(a3, t2);
                    a1 = lw(a0 + 4);
                    a1 = addu(a1, a2);
                    a1 = addu(a1, t8);
                    sq(a1, t7);
                    a1 = lw(a0 + 24);
                    mult1(a2, v1, a1);
                    t6 = addiu(t6, 16);
                    a1 = lw(a0 + 4);
                    a1 = addu(a1, a2);
                    a1 = addu(a1, t8);
                    sq(a1 + 16, a3);
                    a1 = lw(a0 + 12);
                    a1 = slt(t6, a1);
                    t8 = addiu(t8, 32);
                    if (a1 == 0) break;
                    backedge();
                }
            }
            charge(5);
            v1 = lw(a0 + 16);
            t9 = addiu(t9, 4);
            v1 = slt(t9, v1);
            if (v1 == 0) break;
            backedge();
        }
        charge(1);
    }
    charge(7);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 4240);
}

// sub_4DDD30 [unswizzle a PSMT4 raster in place]: the PSMT4 counterpart of sub_4DDAA0 (512-byte frame-buffer rows,
// nibbles gathered into sp + 80 by the parities of the destination and the source).
void Cpu::sub_4DDD30() {
    enter(10);
    sp = addiu(sp, -2192);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    v1 = lw(a0 + 16);
    at = slt(zero, v1);
    t7 = zero;
    bool run = at != 0;
    if (run) {
        charge(3);
        at = slt(zero, v1);
        t4 = addiu(sp, 80);
        run = at != 0;
    }
    if (run) {
        charge(4);
        t3 = addiu(sp, 96);
        t2 = addiu(sp, 112);
        t1 = addiu(sp, 128);
        t0 = addiu(sp, 144);
        for (;;) {  // the bands (t7)
            charge(4);
            a3 = lw(a0 + 12);
            t9 = zero;
            t6 = t0;
            a2 = sra(a3, 1);
            for (;;) {  // the four rows into the frame buffer (t9)
                charge(4);
                at = slt(zero, a2);
                t8 = zero;
                t5 = a3;
                if (at != 0) {
                    charge(5);
                    t5 = lw(a0 + 12);
                    a1 = addu(t7, t9);
                    v1 = lw(a0 + 24);
                    s4 = lw(a0 + 4);
                    s1 = sra(t5, 1);
                    for (;;) {
                        charge(9);
                        mult(s0, v1, a1);
                        s2 = addu(t6, t8);
                        s0 = addu(s4, s0);
                        s0 = addu(s0, t8);
                        lq(s3, s0);
                        t8 = addiu(t8, 16);
                        s0 = slt(t8, s1);
                        sq(s2, s3);
                        if (s0 == 0) break;
                        backedge();
                    }
                    charge(2);
                    t9 = addiu(t9, 1);
                } else {
                    charge(1);
                    t9 = addiu(t9, 1);
                }
                charge(3);
                v1 = slti(t9, 4);
                t6 = addiu(t6, 512);
                if (v1 == 0) break;
                backedge();
            }
            charge(3);
            at = slt(zero, t5);
            a3 = zero;
            if (at != 0) {
                charge(2);
                a2 = t7 & 4;
                v1 = addiu(t7, 2);
                for (;;) {  // 32-byte columns (a3)
                    charge(1);
                    t8 = zero;
                    for (;;) {  // the four 32-nibble rows (t8 by 32)
                        charge(1);
                        t6 = zero;
                        for (;;) {  // the 32 nibbles (t6)
                            charge(2);
                            if (a2 != 0) {
                                charge(26);
                                t5 = addu(t8, t6);
                                s0 = t5 & 2;
                                a1 = t5 & 0x20;
                                s0 = sll(s0, 2);
                                a1 = sra(a1, 1);
                                s1 = s0 | a1;
                                a1 = t5 & 4;
                                s0 = sra(a1, 2);
                                a1 = t5 & 8;
                                s0 = s0 | s1;
                                a1 = sra(a1, 2);
                                s1 = a1 | s0;
                                a1 = t5 & 0x10;
                                s0 = sra(a1, 2);
                                a1 = t5 & 0x40;
                                s0 = s0 | s1;
                                a1 = sra(a1, 1);
                                s1 = a1 | s0;
                                a1 = t5 & 1;
                                s0 = sll(a1, 6);
                                a1 = ~t5;
                                a1 = a1 & 1;
                                a1 = sll(a1, 2);
                                a1 = s0 | a1;
                                s0 = s1 ^ a1;
                            } else {
                                charge(23);
                                t5 = addu(t8, t6);
                                s0 = t5 & 2;
                                a1 = t5 & 1;
                                t9 = sll(s0, 2);
                                s0 = t5 & 0x20;
                                s1 = sra(s0, 1);
                                s0 = t5 & 4;
                                s1 = t9 | s1;
                                s0 = sra(s0, 2);
                                t9 = s0 | s1;
                                s0 = t5 & 8;
                                s1 = sra(s0, 2);
                                s0 = t5 & 0x10;
                                s1 = s1 | t9;
                                s0 = sra(s0, 2);
                                t9 = sll(a1, 6);
                                s1 = s0 | s1;
                                a1 = sll(a1, 2);
                                s0 = t5 & 0x40;
                                a1 = t9 | a1;
                                s0 = sra(s0, 1);
                                s0 = s0 | s1;
                                s0 = s0 ^ a1;
                            }
                            // the nibble at frame-buffer position s0 (row a3 + its column): t9 = it
                            auto fetch = [&](u64 cost) {
                                charge(cost);
                                t9 = sra(s0, 5);
                                a1 = s0 & 0x1F;
                                t9 = sll(t9, 10);
                                a1 = addu(a3, a1);
                                a1 = addu(t9, a1);
                                a1 = sra(a1, 1);
                                a1 = addu(a1, sp);
                                a1 = lbu(a1 + 144);
                            };
                            charge(3);
                            a1 = t6 & 1;
                            if (a1 != 0) {  // into the destination's high nibble (ORed)
                                charge(3);
                                a1 = s0 & 1;
                                if (a1 != 0) {
                                    fetch(10);
                                    a1 = a1 & 0xF0;
                                } else {
                                    fetch(10);
                                    a1 = a1 & 0xF;
                                    a1 = sll(a1, 4);
                                }
                                charge(7);
                                t9 = a1 & 0xFF;
                                a1 = sra(t5, 1);
                                t5 = addu(t4, a1);
                                a1 = lbu(t5);
                                a1 = a1 | t9;
                                sb(t5, a1);
                            } else {  // the low nibble (stored)
                                charge(3);
                                a1 = s0 & 1;
                                if (a1 != 0) {
                                    fetch(11);
                                    a1 = sra(a1, 4);
                                    t9 = a1 & 0xF;
                                } else {
                                    fetch(9);
                                    t9 = a1 & 0xF;
                                }
                                charge(3);
                                a1 = sra(t5, 1);
                                a1 = addu(t4, a1);
                                sb(a1, t9);
                            }
                            charge(4);
                            t6 = addiu(t6, 1);
                            a1 = slti(t6, 32);
                            if (a1 == 0) break;
                            backedge();
                        }
                        charge(4);
                        t8 = addiu(t8, 32);
                        a1 = slti(t8, 128);
                        if (a1 == 0) break;
                        backedge();
                    }
                    charge(33);
                    a1 = lw(a0 + 24);
                    lq(t8, sp + 80);
                    mult(t5, t7, a1);
                    lq(t6, t3);
                    a1 = lw(a0 + 4);
                    a1 = addu(a1, t5);
                    a1 = addu(a1, a3);
                    sq(a1, t8);
                    a1 = lw(a0 + 24);
                    mult1(t5, t7, a1);
                    lq(t8, t2);
                    a1 = lw(a0 + 4);
                    a1 = addu(a1, t5);
                    a1 = addu(a1, a3);
                    sq(a1 + 16, t6);
                    a1 = lw(a0 + 24);
                    mult(t5, v1, a1);
                    lq(t6, t1);
                    a1 = lw(a0 + 4);
                    a1 = addu(a1, t5);
                    a1 = addu(a1, a3);
                    sq(a1, t8);
                    a1 = lw(a0 + 24);
                    mult1(t5, v1, a1);
                    a1 = lw(a0 + 4);
                    a1 = addu(a1, t5);
                    a1 = addu(a1, a3);
                    sq(a1 + 16, t6);
                    a3 = addiu(a3, 32);
                    a1 = lw(a0 + 12);
                    a1 = slt(a3, a1);
                    if (a1 == 0) break;
                    backedge();
                }
            }
            charge(5);
            v1 = lw(a0 + 16);
            t7 = addiu(t7, 4);
            v1 = slt(t7, v1);
            if (v1 == 0) break;
            backedge();
        }
        charge(2);
        backedge();
    }
    charge(2);
    lq(s4, sp + 64);
    charge(6);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 2192);
}

// =========================================================================================================
// [raster] the driver's raster lock / unlock / palette lock, the frame-buffer rasters, the scissor clips
// =========================================================================================================

// The bytes of a w x h x depth raster, rounded up from bits: v0 = (w * h * depth) / 8 (toward zero; the product in v1
// through two mult's), written into a SyncDCache(pixels, pixels + bytes + 127). `a0` holds the pixels. The caller
// charges the block that starts with the loads; `tail_cost` is the block with the jal.
void Cpu::raster_bytes(u64 tail_cost) {
    mult(v1, v1, v0);
    v0 = lw(s1 + 20);
    mult(v1, v0, v1);
    v0 = sra(v1, 3);
    if (sgn(v1) < 0) {
        charge(2);
        v0 = addiu(v1, 7);
        v0 = sra(v0, 3);
    }
    charge(tail_cost);
    v0 = addu(a0, v0);
    a1 = addiu(v0, 127);
}

// sub_4DECE0 [the driver's raster unlock (standard function 16)]: $a1 the raster (+4 pixels, +12 / +16 / +20 width,
// height, depth, +24 stride, +32 type, +34 lock flags, +35 format flags). For a locked raster (+34 & 6): a CPU raster
// (types 1 / 5 / 2) writes its pixels back (SyncDCache); a GS raster with a lock buffer unswizzles PSMT8 (TEX0 PSM
// 0x13, stride >= 16, not +34 bit 5; sub_4DDAA0) or PSMT4 (0x14; sub_4DDD30) per its cache flags (+54 bits 1 / 2),
// writes back, and restores the raster's own fields from the saved copy (+36 .. +48; +4 one level down the cache slot
// when +54 bit 0). A palettised, mipmapped raster still flagged dirty re-validates through sub_4D13E0(raster, 0).
// Clears the lock flags (& ~0x26); returns 1, or 0 when it was not locked.
void Cpu::sub_4DECE0() {
    enter(8);
    sp = addiu(sp, -48);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    v0 = lbu(a1 + 34);
    v1 = v0 & 6;
    s1 = a1;
    if (v1 == 0) {
        charge(2);
        v0 = zero;
        unlock_exit();
        return;
    }
    charge(5);
    a0 = lbu(s1 + 32);
    v1 = 1;
    a0 = a0 & 7;
    bool cpu_raster = a0 == v1;
    if (!cpu_raster) {
        charge(3);
        v1 = 5;
        cpu_raster = a0 == v1;
    }
    if (!cpu_raster) {
        charge(3);
        v1 = 2;
        cpu_raster = a0 == v1;
    }
    bool have_flags = false;  // v1 already holds +35 (the CPU raster's write-back path)
    if (cpu_raster) {
        charge(3);
        a0 = lw(s1 + 4);
        if (a0 != 0) {
            charge(7);
            v1 = lw(s1 + 12);
            v0 = lw(s1 + 16);
            raster_bytes(5);
            jal(0x4DED68u, gen::fn_SyncDCache_00503a58);
            v1 = lbu(s1 + 35);
            have_flags = true;
        }
    } else {
        charge(2);
        a0 = lw(gp - 16968);  // the cache-slot plugin offset
        charge(3);
        v1 = lw(s1 + 4);
        s0 = addu(s1, a0);
        if (v1 != 0) {
            charge(4);
            a1 = lbu(s0 + 54);
            v1 = a1 & 2;
            bool unswizzled8 = false;
            if (v1 != 0) {  // PSMT8 unswizzle?
                charge(6);
                a0 = lw(s0 + 8);
                v1 = 0x13;
                a0 = srl(a0, 20);
                a0 = a0 & 0x3F;
                if (a0 == v1) {
                    charge(4);
                    v1 = lw(s1 + 24);
                    v1 = slti(v1, 16);
                    if (v1 == 0) {
                        charge(3);
                        v1 = v0 & 0x20;
                        if (v1 == 0) {
                            charge(4);
                            a0 = s1;
                            jal(0x4DEED8u, gen::fn_sub_4DDAA0_004ddaa0);
                            v1 = lw(s1 + 12);
                            unswizzled8 = true;
                        }
                    }
                }
                backedge();
            }
            if (!unswizzled8) {
                charge(3);
                v1 = a1 & 4;
                if (v1 != 0) {  // PSMT4 unswizzle?
                    charge(6);
                    a0 = lw(s0 + 8);
                    v1 = 0x14;
                    a0 = srl(a0, 20);
                    a0 = a0 & 0x3F;
                    if (a0 == v1) {
                        charge(4);
                        v1 = lw(s1 + 24);
                        v1 = slti(v1, 16);
                        if (v1 == 0) {
                            charge(3);
                            v0 = v0 & 0x20;
                            if (v0 == 0) {
                                charge(2);
                                a0 = s1;
                                jal(0x4DEDD4u, gen::fn_sub_4DDD30_004ddd30);
                            }
                        }
                    }
                }
                charge(1);
                v1 = lw(s1 + 12);
            }
            charge(7);
            v0 = lw(s1 + 16);
            a0 = lw(s1 + 4);
            raster_bytes(3);
            jal(0x4DEE08u, gen::fn_SyncDCache_00503a58);
        }
        // the raster's own fields back from the saved copy
        charge(12);
        v0 = lw(s1 + 40);
        sw(s1 + 12, v0);
        v0 = lw(s1 + 44);
        sw(s1 + 16, v0);
        v0 = lw(s1 + 48);
        sw(s1 + 24, v0);
        v0 = lw(s1 + 36);
        sw(s1 + 4, v0);
        v0 = lbu(s0 + 54);
        v0 = v0 & 1;
        if (v0 != 0) {
            charge(4);
            v0 = lw(s1 + 4);
            v0 = lw(v0 + 4);
            v0 = addiu(v0, 80);
            sw(s1 + 4, v0);
        }
    }
    if (!have_flags) {
        charge(1);
        v1 = lbu(s1 + 35);
    }
    charge(3);
    v0 = v1 & 0x80;
    bool revalidate = false;
    if (v0 != 0) {
        charge(3);
        v0 = v1 & 0x10;
        if (v0 != 0) {
            charge(4);
            v1 = lbu(s1 + 34);
            v0 = v1 & 4;
            revalidate = v0 != 0;
        }
    }
    if (revalidate) {
        charge(6);
        v0 = si(-39);
        a0 = s1;
        v0 = v1 & v0;
        a1 = zero;
        sb(s1 + 34, v0);
        jal(0x4DEE8Cu, gen::fn_sub_4D13E0_004d13e0);
    } else {
        charge(5);
        v1 = lbu(s1 + 34);
        v0 = si(-39);
        v0 = v1 & v0;
        sb(s1 + 34, v0);
        backedge();
    }
    charge(2);
    v0 = 1;
    unlock_exit();
}
void Cpu::unlock_exit() {
    charge(5);
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}

// sub_4DEF10 [the driver's palette lock (standard function 23)]: $a0 where the palette pointer goes, $a1 the raster,
// $a2 the lock mode (bit 0 read, bit 1 write). Only for a palettised raster (+35 & 0x60) that owns its pixels
// (+33 bit 7 clear): reading a palette not yet in RAM (+33 bit 6 clear) fetches it first (sub_4F1540); *$a0 = the
// palette (+8); +34 gets 0x10 (read) / 8 (write). Returns 1, or 0.
void Cpu::sub_4DEF10() {
    enter(12);
    sp = addiu(sp, -80);
    sd(sp + 64, ra);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    s2 = a0;
    sq(sp, s0);
    s1 = a2;
    v0 = lbu(a1 + 35);
    v0 = v0 & 0x60;
    s0 = a1;
    bool ok = v0 != 0;
    if (ok) {
        charge(4);
        v1 = lbu(s0 + 33);
        v0 = v1 & 0x80;
        ok = v0 == 0;
    }
    if (ok) {
        charge(3);
        s3 = s1 & 1;
        if (s3 != 0) {
            charge(3);
            v0 = v1 & 0x40;
            if (v0 == 0) {
                charge(2);
                a0 = s0;
                jal(0x4DEF68u, gen::fn_sub_4F1540_004f1540);
            }
        }
        charge(3);
        v0 = lw(s0 + 8);
        sw(s2, v0);
        if (s3 != 0) {
            charge(4);
            v0 = lbu(s0 + 34);
            v0 = v0 | 0x10;
            sb(s0 + 34, v0);
            backedge();
        }
        charge(3);
        v0 = s1 & 2;
        if (v0 != 0) {
            charge(4);
            v0 = lbu(s0 + 34);
            v0 = v0 | 8;
            sb(s0 + 34, v0);
            backedge();
        }
        charge(2);
        v0 = 1;
    } else {
        charge(1);
        v0 = zero;
    }
    charge(7);
    ra = ld(sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 80);
}

// sub_4DEFD0 [the driver's palette unlock (standard function 24)]: for a palettised raster with a palette (+8): the
// palette size 16 / 256 entries (+35 bit 6) times 4 (32-bit, format 0x500) or 2 (16-bit, 0x100) bytes, else RWERROR
// 0x8000000D and 0. A palette already in GS memory (+33 bit 6) with a cache slot (+88) and +34 bit 0 is re-uploaded
// (sub_4F0C70); otherwise the palette is written back (SyncDCache). +34 &= ~0x18; returns 1.
void Cpu::sub_4DEFD0() {
    enter(8);
    sp = addiu(sp, -48);
    sd(sp + 16, ra);
    sq(sp, s0);
    v0 = lbu(a1 + 35);
    v1 = sll(v0, 8);
    v0 = v1 & 0x6000;
    s0 = a1;
    if (v0 == 0) {
        charge(1);
        v0 = zero;
        palette_exit();
        return;
    }
    charge(3);
    a0 = lw(s0 + 8);
    if (a0 == 0) {
        charge(2);
        v0 = 1;
        palette_exit();
        return;
    }
    charge(8);
    v0 = v1 & 0x4000;
    a2 = 0x10;
    a1 = 0x100;
    v1 = v1 & 0xF00;
    if (v0 == 0) a2 = a1;  // movz: 256 entries
    v0 = 0x500;
    if (v1 == v0) {
        charge(1);
        v1 = sll(a2, 2);
    } else {
        charge(2);
        if (v1 == a1) {
            charge(2);
            v1 = sll(a2, 1);
        } else {
            charge(2);
            v1 = 1;
            charge(9);
            v0 = lui(0x8000);
            sw(sp + 40, v1);
            a0 = v0 | 0xD;
            rwerror(0x4DF084u, 40);
            v0 = zero;
            palette_exit();
            return;
        }
    }
    charge(4);
    v0 = lbu(s0 + 33);
    v0 = v0 & 0x40;
    bool reloaded = false;  // v1 = +34 already (after the re-upload)
    if (v0 == 0) {
        charge(5);
        v0 = addu(a0, v1);
        a1 = addiu(v0, 127);
        jal(0x4DF0BCu, gen::fn_SyncDCache_00503a58);
        backedge();
    } else {
        charge(4);
        v0 = lbu(s0 + 34);
        v0 = v0 & 1;
        if (v0 != 0) {
            charge(5);
            v0 = lw(gp - 16968);
            v0 = addu(s0, v0);
            v0 = lw(v0 + 88);
            if (v0 != 0) {
                charge(4);
                a0 = s0;
                jal(0x4DF06Cu, gen::fn_sub_4F0C70_004f0c70);
                v1 = lbu(s0 + 34);
                reloaded = true;
            }
        }
    }
    if (!reloaded) {
        charge(1);
        v1 = lbu(s0 + 34);
    }
    charge(3);
    v0 = si(-25);
    v0 = v1 & v0;
    sb(s0 + 34, v0);
    charge(2);
    v0 = 1;
    palette_exit();
}
void Cpu::palette_exit() {
    charge(4);
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}

// One frame-buffer raster's GS addressing (sub_4E2F10): the raster `r` (gp slot), its cache slot (+ gp-16968): the
// previous binding (+88) released, the camera's frame record `rec` bound ({+0 the raster, +4 its GS address}); TEX0
// TBP0 (+8, 14 bits) = address >> 6 and CBP (+12 bits 5..18) = TBP0 + the slot's +16.
// The two halves use different scratch registers (t0 / a3 for the first, a0 / a3 for the second): `first`.
void Cpu::fb_raster(s32 slot, Gpr& rec, bool first) {
    charge(3);
    a1 = lw(gp + slot);
    if (a1 == 0) return;
    charge(5);
    v1 = lw(gp - 16968);
    v1 = addu(a1, v1);
    a1 = lw(v1 + 88);
    if (a1 != 0) {
        charge(2);
        sw(a1, zero);
        sw(v1 + 88, zero);
    }
    charge(29);
    a3 = lw(gp + slot);
    a1 = lui(0xFFF8);
    a2 = si(-16384);
    a1 = a1 | 0x1F;
    sw(rec, a3);
    sw(v1 + 88, rec);
    if (first) {
        t0 = lw(v1 + 88);
        a3 = lw(v1 + 8);
        t0 = lw(t0 + 4);
        a2 = a3 & a2;
        sw(v1 + 8, a2);
        t0 = srl(t0, 6);
        a2 = lw(v1 + 8);
        a3 = t0 & 0x3FFF;
        a2 = a2 | a3;
        sw(v1 + 8, a2);
        a3 = lw(v1 + 16);
        a2 = lw(v1 + 12);
        a3 = addu(t0, a3);
        a2 = a2 & a1;
        a1 = a3 & 0x3FFF;
        sw(v1 + 12, a2);
        a1 = a1 & 0x3FFF;
        a2 = dsll(a1, 5);
        a1 = lw(v1 + 12);
        a2 = dsll32(a2, 0);
        a2 = dsra32(a2, 0);
        a1 = a1 | a2;
        sw(v1 + 12, a1);
    } else {
        a3 = lw(v1 + 88);
        a0 = lw(v1 + 8);
        a3 = lw(a3 + 4);
        a0 = a0 & a2;
        sw(v1 + 8, a0);
        a3 = srl(a3, 6);
        a0 = lw(v1 + 8);
        a2 = a3 & 0x3FFF;
        a0 = a0 | a2;
        sw(v1 + 8, a0);
        a2 = lw(v1 + 16);
        a0 = lw(v1 + 12);
        a2 = addu(a3, a2);
        a1 = a0 & a1;
        a0 = a2 & 0x3FFF;
        sw(v1 + 12, a1);
        a0 = a0 & 0x3FFF;
        a1 = dsll(a0, 5);
        a0 = lw(v1 + 12);
        a1 = dsll32(a1, 0);
        a1 = dsra32(a1, 0);
        a0 = a0 | a1;
        sw(v1 + 12, a0);
    }
}

// sub_4E2F10 [bind the frame-buffer rasters to the current draw buffer]: the draw buffer (gp-17016 bit 0) picks the
// frame records 0x9656F0 / 0x965710 or 0x965700 / 0x965720; the two driver rasters gp-17024 / gp-17020 are bound to
// them (fb_raster).
void Cpu::sub_4E2F10() {
    enter(4);
    v1 = lw(gp - 17016);
    v1 = v1 & 1;
    if (v1 != 0) {
        charge(5);
        t0 = lui(0x96);
        a0 = lui(0x96);
        t0 = addiu(t0, 22272);
        a0 = addiu(a0, 22304);
    } else {
        charge(4);
        t0 = lui(0x96);
        a0 = lui(0x96);
        t0 = addiu(t0, 22256);
        a0 = addiu(a0, 22288);
    }
    fb_raster(-17024, t0, true);
    fb_raster(-17020, a0, false);
    charge(2);
}

// The scissor rectangle at 0x965840: x +0, y +4, w +8, h +12 (s32).

// sub_4E4A90 [clip a blit 1:1 against the scissor]: $a0 the source rectangle {x, y, w, h}, $a1 the destination.
// Rejected (0) when the destination misses the scissor; otherwise its left / right / top / bottom overhangs are cut
// (the source origin moved by the same amounts) and the clipped w / h (both > 0, else 0) are copied to the source.
// Returns 1.
void Cpu::sub_4E4A90() {
    enter(8);
    v0 = lui(0x96);
    t1 = lw(a1);
    a3 = lw(a1 + 8);
    t0 = lw(v0 + 22592);
    v0 = addu(t1, a3);
    at = slt(t0, v0);
    auto reject = [&] {
        charge(1);
        v0 = zero;
        charge(2);
    };
    if (at == 0) return reject();
    charge(8);
    v0 = lui(0x96);
    a2 = lw(a1 + 4);
    v1 = lw(v0 + 22596);
    v0 = lw(a1 + 12);
    v0 = addu(a2, v0);
    at = slt(v1, v0);
    if (at == 0) return reject();
    charge(6);
    v0 = lui(0x96);
    v0 = lw(v0 + 22600);
    v0 = addu(t0, v0);
    at = slt(t1, v0);
    if (at == 0) return reject();
    charge(6);
    v0 = lui(0x96);
    v0 = lw(v0 + 22604);
    v0 = addu(v1, v0);
    at = slt(a2, v0);
    if (at == 0) return reject();
    charge(3);
    v0 = slt(t1, t0);
    if (v0 != 0) {  // the left overhang
        charge(10);
        a2 = subu(t0, t1);
        v0 = lui(0x96);
        v1 = subu(a3, a2);
        sw(a1 + 8, v1);
        v1 = lw(a0);
        v1 = addu(v1, a2);
        sw(a0, v1);
        v0 = lw(v0 + 22592);
        sw(a1, v0);
        backedge();
    }
    charge(11);
    v1 = lui(0x96);
    v0 = lui(0x96);
    a3 = lw(v1 + 22592);
    a2 = lw(v0 + 22600);
    v1 = lw(a1);
    v0 = lw(a1 + 8);
    a2 = addu(a3, a2);
    v0 = addu(v1, v0);
    at = slt(a2, v0);
    if (at != 0) {  // the right overhang
        charge(3);
        v0 = subu(a2, v1);
        sw(a1 + 8, v0);
        backedge();
    }
    charge(6);
    v0 = lui(0x96);
    v1 = lw(a1 + 4);
    a2 = lw(v0 + 22596);
    v0 = slt(v1, a2);
    if (v0 != 0) {  // the top overhang
        charge(11);
        a2 = subu(a2, v1);
        v0 = lui(0x96);
        v1 = lw(a1 + 12);
        v1 = subu(v1, a2);
        sw(a1 + 12, v1);
        v1 = lw(a0 + 4);
        v1 = addu(v1, a2);
        sw(a0 + 4, v1);
        v0 = lw(v0 + 22596);
        sw(a1 + 4, v0);
        backedge();
    }
    charge(11);
    v1 = lui(0x96);
    v0 = lui(0x96);
    a3 = lw(v1 + 22596);
    a2 = lw(v0 + 22604);
    v1 = lw(a1 + 4);
    v0 = lw(a1 + 12);
    a2 = addu(a3, a2);
    v0 = addu(v1, v0);
    at = slt(a2, v0);
    if (at != 0) {  // the bottom overhang
        charge(3);
        v0 = subu(a2, v1);
        sw(a1 + 12, v0);
        backedge();
    }
    charge(3);
    v1 = lw(a1 + 8);
    if (sgn(v1) <= 0) return reject();
    charge(3);
    v0 = lw(a1 + 12);
    if (sgn(v0) <= 0) return reject();
    charge(5);
    sw(a0 + 8, v1);
    v0 = 1;
    v1 = lw(a1 + 12);
    sw(a0 + 12, v1);
    charge(2);
}

// sub_4E4C20 [clip a scaled blit against the scissor]: as sub_4E4A90, but each cut of the destination cuts the source
// proportionally (source w / h * cut / destination w / h through mult / div); returns 1 when all four extents stay
// positive, else 0.
void Cpu::sub_4E4C20() {
    enter(8);
    v0 = lui(0x96);
    t1 = lw(a1 + 8);
    t0 = lw(a1);
    a3 = lw(v0 + 22592);
    v0 = addu(t0, t1);
    at = slt(a3, v0);
    auto reject = [&] {
        charge(1);
        v0 = zero;
        charge(2);
    };
    if (at == 0) return reject();
    charge(8);
    v0 = lui(0x96);
    a2 = lw(a1 + 4);
    v1 = lw(v0 + 22596);
    v0 = lw(a1 + 12);
    v0 = addu(a2, v0);
    at = slt(v1, v0);
    if (at == 0) return reject();
    charge(6);
    v0 = lui(0x96);
    v0 = lw(v0 + 22600);
    v0 = addu(a3, v0);
    at = slt(t0, v0);
    if (at == 0) return reject();
    charge(6);
    v0 = lui(0x96);
    v0 = lw(v0 + 22604);
    v0 = addu(v1, v0);
    at = slt(a2, v0);
    if (at == 0) return reject();
    charge(3);
    v0 = slt(t0, a3);
    if (v0 != 0) {  // the left overhang: the source loses w * cut / dst w
        charge(17);
        v0 = lw(a0 + 8);
        v1 = subu(a3, t0);
        mult(v0, v1, v0);
        div(v0, t1);
        v0 = subu(t1, v1);
        sw(a1 + 8, v0);
        mflo(a2);
        v1 = lw(a0 + 8);
        v0 = lui(0x96);
        v1 = subu(v1, a2);
        sw(a0 + 8, v1);
        v0 = lw(v0 + 22592);
        sw(a1, v0);
        v0 = lw(a0);
        v0 = addu(v0, a2);
        sw(a0, v0);
        backedge();
    }
    charge(11);
    v1 = lui(0x96);
    v0 = lui(0x96);
    a2 = lw(v1 + 22592);
    a3 = lw(a1 + 8);
    v1 = lw(v0 + 22600);
    v0 = lw(a1);
    v1 = addu(a2, v1);
    v0 = addu(v0, a3);
    at = slt(v1, v0);
    if (at != 0) {  // the right overhang
        charge(11);
        a2 = subu(v0, v1);
        v0 = lw(a0 + 8);
        mult(v0, a2, v0);
        div(v0, a3);
        v0 = subu(a3, a2);
        sw(a1 + 8, v0);
        mflo(v1);
        v0 = lw(a0 + 8);
        v0 = subu(v0, v1);
        sw(a0 + 8, v0);
        backedge();
    }
    charge(6);
    v0 = lui(0x96);
    v1 = lw(a1 + 4);
    a2 = lw(v0 + 22596);
    v0 = slt(v1, a2);
    if (v0 != 0) {  // the top overhang
        charge(18);
        v0 = lw(a0 + 12);
        a3 = subu(a2, v1);
        mult(v1, a3, v0);
        v0 = lw(a1 + 12);
        div(v1, v0);
        v0 = subu(v0, a3);
        sw(a1 + 12, v0);
        mflo(a2);
        v1 = lw(a0 + 12);
        v0 = lui(0x96);
        v1 = subu(v1, a2);
        sw(a0 + 12, v1);
        v0 = lw(v0 + 22596);
        sw(a1 + 4, v0);
        v0 = lw(a0 + 4);
        v0 = addu(v0, a2);
        sw(a0 + 4, v0);
        backedge();
    }
    charge(11);
    v1 = lui(0x96);
    v0 = lui(0x96);
    a2 = lw(v1 + 22596);
    a3 = lw(a1 + 12);
    v1 = lw(v0 + 22604);
    v0 = lw(a1 + 4);
    v1 = addu(a2, v1);
    v0 = addu(v0, a3);
    at = slt(v1, v0);
    if (at != 0) {  // the bottom overhang
        charge(11);
        a2 = subu(v0, v1);
        v0 = lw(a0 + 12);
        mult(v0, a2, v0);
        div(v0, a3);
        v0 = subu(a3, a2);
        sw(a1 + 12, v0);
        mflo(v1);
        v0 = lw(a0 + 12);
        v0 = subu(v0, v1);
        sw(a0 + 12, v0);
        backedge();
    }
    for (s32 off : {8, 12}) {  // the destination's extents
        charge(3);
        v0 = lw(a1 + off);
        if (sgn(v0) <= 0) return reject();
    }
    for (s32 off : {8, 12}) {  // the source's
        charge(3);
        v0 = lw(a0 + off);
        if (sgn(v0) <= 0) return reject();
    }
    charge(2);
    v0 = 1;
    charge(2);
}

// =========================================================================================================
// [rt2d] the Rt2d toolkit (the Maestro UI's vector graphics): the CTM stack, paths, brushes, scenes and shapes
// =========================================================================================================
//
// Globals (RW's Rt2d state): the CTM stack 0x95EDF0 (31 matrix pointers, +4 * depth) with its depth 0x95EE70; the
// "CTM changed" flags 0x95EF50 / 0x95EF64; the device-space matrix cache 0x95EE90.. (built by sub_4AAE60 against the
// camera 0x95EF84); the flattening tolerance 0x95EF60; the scratch path 0x95ED88.

// sub_4A55B0 [Rt2dBrush colour set-up]: $a0 the brush; four source colours ($t0, $a3, $a1, $a2: RGBA floats) each
// mixed as clamp(t2 + c * t1, 0, 255) per channel ($t2 the colour offset, $t1 the colour multiplier) into brush +0 /
// +24 / +48 / +72; the first one also packed as RGBA bytes at +96. Returns the brush.
void Cpu::sub_4A55B0() {
    // One channel: out = clamp(t2[k] + src[k] * t1[k], 0, 255) through ACC (the compiled min / max ladder).
    auto channel = [&](bool first, const Gpr& src, s32 k, s32 out) {
        if (first)
            enter(12);
        else
            charge(12);
        v0 = lui(0x437F);  // 255.0
        lwc1(F2, t2 + 4 * k);
        lwc1(F4, src + 4 * k);
        lwc1(F3, t1 + 4 * k);
        mtc1(zero, F0);
        mtc1(v0, F1);
        adda_s(F0, F2);
        madd_s(F2, F4, F3);
        c_le_s(F2, F1);
        if (cop1_cond()) {
            charge(1);
            mov_s(F1, F2);  // min(x, 255)
        }
        charge(5);
        mtc1(zero, F0);
        c_lt_s(F0, F1);
        if (!cop1_cond()) {
            charge(2);
            swc1(F0, a0 + out);  // <= 0: 0
            return;
        }
        charge(6);
        v0 = lui(0x437F);
        mtc1(v0, F0);
        c_le_s(F2, F0);
        charge(2);
        if (cop1_cond()) {
            mov_s(F0, F2);
        } else {
            mov_s(F2, F0);
            mov_s(F0, F2);
        }
        charge(1);
        swc1(F0, a0 + out);
    };
    const Gpr* srcs[4] = {&t0, &a3, &a1, &a2};
    for (unsigned col = 0; col < 4; ++col)
        for (unsigned k = 0; k < 4; ++k)
            channel(col == 0 && k == 0, *srcs[col], static_cast<s32>(k), static_cast<s32>(24 * col + 4 * k));
    charge(21);
    v0 = a0;
    for (unsigned k = 0; k < 4; ++k) {  // the first colour as bytes
        lwc1(F0, a0 + 4 * k);
        cvt_w_s(F0, F0);
        mfc1(v1, F0);
        sb(a0 + 96 + k, v1);
    }
}

// sub_4A9A70 [a jr tail call through +312 of $a0 (an Rt2d font's render callback)].
void Cpu::sub_4A9A70() {
    enter(3);
    v0 = lw(a0 + 312);
    tail(v0.u());
}

// The "new CTM slot" step of sub_4AAB40 / sub_4AAC70: the depth (0x95EE70) is below 31 -> depth + 1, and an empty slot
// gets a fresh matrix (sub_4C38C0, RwMatrixCreate). Returns false when the stack is full (s0 = 0 then).
bool Cpu::ctm_push_slot(u32 create_pc) {
    enter(9);
    sp = addiu(sp, -48);
    v0 = lui(0x96);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    v0 = lw(v0 - 4496);
    s0 = slti(v0, 31);
    s1 = a0;
    if (s0 == 0) return false;
    charge(10);
    v1 = addiu(v0, 1);
    v0 = lui(0x96);
    sw(v0 - 4496, v1);
    v0 = lui(0x96);
    v1 = sll(v1, 2);
    v0 = addiu(v0, -4624);
    v0 = addu(v0, v1);
    v0 = lw(v0);
    if (v0 == 0) {
        charge(10);
        jal(create_pc, gen::fn_sub_4C38C0_004c38c0);
        v1 = lui(0x96);
        a0 = lui(0x96);
        v1 = lw(v1 - 4496);
        a0 = addiu(a0, -4624);
        v1 = sll(v1, 2);
        v1 = addu(a0, v1);
        sw(v1, v0);
        backedge();
    }
    return true;
}

// sub_4AAB40 [Rt2dCTMPush(matrix)]: a new CTM = matrix x the previous CTM (sub_4C2F30), or a copy of the previous one
// for a null matrix; the "changed" flags cleared. Returns 1, or 0 when the stack is full.
void Cpu::sub_4AAB40() {
    if (ctm_push_slot(0x4AABD0u)) {
        charge(2);
        if (s1 != 0) {
            charge(15);
            v0 = lui(0x96);
            v1 = lui(0x96);
            a0 = lw(v0 - 4496);
            v1 = addiu(v1, -4624);
            v0 = lui(0x96);
            a0 = sll(a0, 2);
            v0 = addiu(v0, -4628);
            v1 = addu(v1, a0);
            v0 = addu(v0, a0);
            a0 = lw(v1);
            a2 = lw(v0);
            a1 = s1;
            jal(0x4AABC0u, gen::fn_sub_4C2F30_004c2f30);
        } else {
            charge(12);
            v0 = lui(0x96);
            v1 = lui(0x96);
            a1 = lw(v0 - 4496);
            v1 = addiu(v1, -4628);
            v0 = lui(0x96);
            a1 = sll(a1, 2);
            v0 = addiu(v0, -4624);
            v1 = addu(v1, a1);
            v0 = addu(v0, a1);
            a2 = lw(v1);
            a1 = lw(v0);
            copy_matrix(a0, a2, a1, v1, v0, true);
        }
    }
    charge(10);
    v1 = lui(0x96);
    v0 = s0;
    sw(v1 - 4272, zero);
    v1 = lui(0x96);
    sw(v1 - 4252, zero);
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}

// sub_4AAC70 [Rt2dCTMSet-push(matrix)]: a new CTM = a copy of `matrix`. Returns 1, or 0 when the stack is full.
void Cpu::sub_4AAC70() {
    if (ctm_push_slot(0x4AAD14u)) {
        charge(8);
        v0 = lui(0x96);
        v1 = lui(0x96);
        v0 = lw(v0 - 4496);
        v1 = addiu(v1, -4624);
        a0 = 8;
        v0 = sll(v0, 2);
        v0 = addu(v1, v0);
        a1 = lw(v0);
        copy_matrix(a0, s1, a1, v1, v0, true);
    }
    charge(6);
    v1 = lui(0x96);
    v0 = s0;
    sw(v1 - 4272, zero);
    v1 = lui(0x96);
    sw(v1 - 4252, zero);
    charge(5);
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}

// sub_4AAD50 [Rt2dCTMPop]: depth - 1 when above 0, the "changed" flags cleared.
void Cpu::sub_4AAD50() {
    enter(5);
    v0 = lui(0x96);
    v1 = lw(v0 - 4496);
    v0 = slt(zero, v1);
    if (v0 != 0) {
        charge(8);
        a0 = addiu(v1, -1);
        v1 = lui(0x96);
        sw(v1 - 4496, a0);
        v1 = lui(0x96);
        sw(v1 - 4272, zero);
        v1 = lui(0x96);
        sw(v1 - 4252, zero);
        backedge();
    }
    charge(2);
    charge(2);
}

// sub_4AB0C0 [Rt2dCTMRead]: the CTM at the current depth.
void Cpu::sub_4AB0C0() {
    enter(8);
    v0 = lui(0x96);
    v1 = lw(v0 - 4496);
    v0 = lui(0x96);
    v1 = sll(v1, 2);
    v0 = addiu(v0, -4624);
    v0 = addu(v0, v1);
    v0 = lw(v0);
}

// sub_4AB910 [split a cubic Bezier at t = 1/2 (de Casteljau)]: $a0 the four control points (x, y pairs), $a1 / $a2
// the two halves.
void Cpu::sub_4AB910() {
    enter(65);
    lwc1(F7, a0 + 8);
    v1 = lui(0x3F00);
    lwc1(F9, a0 + 16);
    lwc1(F2, a0);
    mtc1(v1, F0);
    lwc1(F4, a0 + 12);
    lwc1(F3, a0 + 4);
    lwc1(F5, a0 + 20);
    add_s(F6, F7, F9);
    mul_s(F8, F6, F0);   // (p1 + p2) / 2
    add_s(F2, F2, F7);
    lwc1(F6, a0 + 24);
    lwc1(F1, a0 + 28);
    add_s(F3, F3, F4);
    mul_s(F2, F0, F2);
    add_s(F6, F6, F9);
    add_s(F4, F4, F5);
    add_s(F1, F1, F5);
    swc1(F2, a1 + 8);
    mul_s(F2, F0, F3);
    mul_s(F5, F0, F1);
    swc1(F2, a1 + 12);
    mul_s(F6, F0, F6);
    swc1(F6, a2 + 16);
    swc1(F5, a2 + 20);
    lwc1(F5, a1 + 8);
    mul_s(F7, F4, F0);
    lwc1(F6, a1 + 12);
    add_s(F5, F5, F8);
    mul_s(F5, F0, F5);
    add_s(F6, F6, F7);
    swc1(F5, a1 + 16);
    mul_s(F5, F0, F6);
    swc1(F5, a1 + 20);
    lwc1(F5, a2 + 16);
    lwc1(F6, a2 + 20);
    lwc1(F4, a0);
    lwc1(F3, a0 + 4);
    lwc1(F2, a0 + 24);
    lwc1(F1, a0 + 28);
    add_s(F5, F5, F8);
    mul_s(F5, F0, F5);
    add_s(F6, F6, F7);
    swc1(F5, a2 + 8);
    mul_s(F5, F0, F6);
    swc1(F5, a2 + 12);
    lwc1(F6, a1 + 16);
    lwc1(F5, a2 + 8);
    lwc1(F8, a1 + 20);
    lwc1(F7, a2 + 12);
    add_s(F5, F6, F5);
    mul_s(F5, F0, F5);
    add_s(F7, F8, F7);
    mul_s(F0, F0, F7);
    swc1(F5, a1 + 24);   // the midpoint, shared
    swc1(F0, a1 + 28);
    swc1(F4, a1);
    swc1(F3, a1 + 4);
    lwc1(F3, a1 + 24);
    lwc1(F0, a1 + 28);
    swc1(F3, a2);
    swc1(F0, a2 + 4);
    swc1(F2, a2 + 24);
    swc1(F1, a2 + 28);
}

// The path segment record (24 bytes): {+0 type (1 line, 2 curve), +4 x, +8 y, +12 / +16 the normal, +20 the length so
// far}. After a point is appended at v0 (its x / y stored and the delta to the previous point in $f`fa` / $f`fb`
// squared-summed into $f1, $f0 = 0): the length, the unit normal (1 / length, or the length itself when 0) and the
// running length; with at least two points before it (`count` >= 2) the previous point's normal becomes the
// normalised average of both, else a copy. `copy_cost` is the copy block's charge; returns whether it averaged.
bool Cpu::segment_normal(unsigned fa, unsigned fb, const Gpr& count, u64 copy_cost) {
    sqrt_s(F4, F1);
    c_le_s(F4, F0);
    if (cop1_cond()) {
        charge(1);
        mov_s(F0, F4);
    } else {
        charge(8);
        v1 = lui(0x3F80);
        mtc1(v1, F0);
        div_s(F0, F0, F4);
    }
    charge(9);
    mul_s(F1, fa, F0);
    at = slti(count, 2);
    mul_s(F0, fb, F0);
    swc1(F1, v0 + 12);
    swc1(F0, v0 + 16);
    lwc1(F0, v0 - 4);
    add_s(F0, F0, F4);
    swc1(F0, v0 + 20);
    if (at == 0) {
        charge(16);
        lwc1(F5, v0 - 12);
        v1 = lui(0x3F80);
        lwc1(F2, v0 + 12);
        lwc1(F3, v0 - 8);
        lwc1(F1, v0 + 16);
        mtc1(v1, F0);
        add_s(F4, F5, F2);
        add_s(F2, F3, F1);
        mula_s(F3, F2);
        madd_s(F1, F5, F4);
        div_s(F0, F0, F1);
        mul_s(F1, F4, F0);
        mul_s(F0, F2, F0);
        swc1(F1, v0 - 12);
        swc1(F0, v0 - 8);
        return true;
    }
    charge(copy_cost);
    lwc1(F1, v0 + 12);
    lwc1(F0, v0 + 16);
    swc1(F1, v0 - 12);
    swc1(F0, v0 - 8);
    return false;
}

// Appends the point (x, y) at `pt` (+24 / +28 of a curve record, or the record itself) to the path array $s2's list
// (sub_4C2120 count, sub_4C1E70 append with hint 0x30190) and computes its normal (segment_normal with count in s1).
void Cpu::append_curve_end(u32 count_pc) {
    charge(26);
    a0 = lw(s2);
    jal(count_pc, gen::fn_sub_4C2120_004c2120);
    a0 = lw(s2);
    s1 = v0;
    v0 = lui(0x3);
    a1 = v0 | 0x190;
    jal(count_pc + 20, gen::fn_sub_4C1E70_004c1e70);
    lwc1(F4, s0 + 24);
    v1 = 1;
    lwc1(F3, s0 + 28);
    sw(v0, v1);
    mtc1(zero, F0);
    swc1(F4, v0 + 4);
    swc1(F3, v0 + 8);
    lwc1(F2, v0 - 16);
    lwc1(F1, v0 - 20);
    sub_s(F2, F3, F2);
    sub_s(F3, F1, F4);
    mula_s(F3, F3);
    madd_s(F1, F2, F2);
}

// sub_4ABA20 [flatten a cubic Bezier into line points]: $a0 the flattened path, $a1 the four control points, $a2 the
// recursion budget. When the budget is spent or both inner control points lie within the tolerance (0x95EF60) of the
// chord, the end point is appended; otherwise the curve is split (sub_4AB910 into two 32-byte frame buffers) and both
// halves flattened with budget - 1.
void Cpu::sub_4ABA20() {
    enter(11);
    sp = addiu(sp, -128);
    sd(sp + 48, ra);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    s2 = a0;
    s1 = a2;
    sq(sp, s0);
    s1 = addiu(s1, -1);
    v0 = slt(s1, zero);
    s0 = a1;
    if (v0 != 0) {  // the budget is spent: the end point
        append_curve_end(0x4ABC04u);
        segment_normal(F2, F3, s1, 5);
        backedge();
    } else {
        // flat enough? (the distance of p1 and p2 from the chord p0 -> p3, squared, against the tolerance)
        charge(24);
        lwc1(F5, s0 + 4);
        v0 = lui(0x96);
        lwc1(F2, s0 + 28);
        lwc1(F4, v0 - 4256);
        lwc1(F6, s0);
        lwc1(F1, s0 + 8);
        lwc1(F3, s0 + 24);
        lwc1(F0, s0 + 12);
        sub_s(F7, F2, F5);
        sub_s(F2, F1, F6);
        sub_s(F3, F3, F6);
        mula_s(F7, F7);
        sub_s(F1, F0, F5);
        madd_s(F8, F3, F3);
        mula_s(F1, F7);
        madd_s(F0, F2, F3);
        mula_s(F1, F1);
        madd_s(F1, F2, F2);
        sub_s(F1, F1, F4);
        mul_s(F0, F0, F0);
        mul_s(F1, F8, F1);
        c_lt_s(F1, F0);
        v0 = 1;
        if (!cop1_cond()) {
            charge(1);
            v0 = zero;
        }
        charge(2);
        if (v0 != 0) {
            charge(14);
            lwc1(F0, s0 + 20);
            lwc1(F1, s0 + 16);
            sub_s(F0, F0, F5);
            sub_s(F1, F1, F6);
            mula_s(F0, F7);
            madd_s(F2, F1, F3);
            mula_s(F0, F0);
            madd_s(F0, F1, F1);
            sub_s(F0, F0, F4);
            mul_s(F1, F8, F0);
            mul_s(F0, F2, F2);
            c_lt_s(F1, F0);
            v0 = 1;
            if (!cop1_cond()) {
                charge(1);
                v0 = zero;
            }
        }
        charge(2);
        if (v0 != 0) {
            append_curve_end(0x4ABAFCu);
            segment_normal(F2, F3, s1, 4);
        } else {
            charge(13);
            a0 = s0;
            a1 = addiu(sp, 96);
            a2 = addiu(sp, 64);
            jal(0x4ABD10u, gen::fn_sub_4AB910_004ab910);
            a0 = s2;
            a2 = s1;
            jal(0x4ABD1Cu, gen::fn_sub_4ABA20_004aba20);
            a0 = s2;
            a2 = s1;
            a1 = addiu(sp, 64);
            jal(0x4ABD2Cu, gen::fn_sub_4ABA20_004aba20);
            backedge();
        }
    }
    charge(2);
    ra = ld(sp + 48);
    charge(5);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 128);
}

// sub_4AC020 [Rt2dPathGetBBox-like]: $a0 the path ({+0 the point array, +4 its count or -1 to ask the array}), $a1 the
// box {min x, min y, max x, max y} grown over every point (24-byte records, x +4, y +8). Returns the box.
void Cpu::sub_4AC020() {
    enter(10);
    sp = addiu(sp, -64);
    v1 = lw(a0 + 4);
    sd(sp + 48, ra);
    v0 = si(-1);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    s2 = a0;
    sq(sp, s0);
    s0 = a1;
    if (v1 == v0) {
        charge(4);
        a0 = lw(s2);
        jal(0x4AC048u, gen::fn_sub_4C2090_004c2090);
        s1 = v0;
    } else {
        charge(2);
        v0 = lw(s2);
        s1 = v0;
    }
    charge(4);
    v1 = si(-1);
    v0 = lw(s2 + 4);
    if (v0 == v1) {
        charge(2);
        a0 = lw(s2);
        jal(0x4AC070u, gen::fn_sub_4C2120_004c2120);
    }
    charge(3);
    at = slt(zero, v0);
    a0 = zero;
    if (at != 0) {
        for (;;) {
            charge(5);
            lwc1(F1, s1 + 4);
            lwc1(F0, s0);
            c_lt_s(F1, F0);
            if (cop1_cond()) {  // x < min x
                charge(2);
                swc1(F1, s0);
                backedge();
            } else {
                charge(4);
                lwc1(F0, s0 + 8);
                c_le_s(F1, F0);
                if (!cop1_cond()) {  // x > max x
                    charge(2);
                    swc1(F1, s0 + 8);
                }
            }
            charge(5);
            lwc1(F1, s1 + 8);
            lwc1(F0, s0 + 4);
            c_lt_s(F1, F0);
            if (cop1_cond()) {
                charge(2);
                swc1(F1, s0 + 4);
                backedge();
            } else {
                charge(4);
                lwc1(F0, s0 + 12);
                c_le_s(F1, F0);
                if (!cop1_cond()) {
                    charge(1);
                    swc1(F1, s0 + 12);
                }
            }
            charge(4);
            a0 = addiu(a0, 1);
            v1 = slt(a0, v0);
            s1 = addiu(s1, 24);
            if (v1 == 0) break;
            backedge();
        }
    }
    charge(2);
    v0 = s0;
    charge(6);
    ra = ld(sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 64);
}

// sub_4AC390 [Rt2dPathDestroy-like, recursive]: $a0 a path node; four links freed in a chain (sub_4AB0E0 returns the
// next one; kept recompiled: RwFree / the freelist), the fourth's result destroyed recursively. Returns 1 for a
// non-null node, else 0.
void Cpu::sub_4AC390() {
    enter(6);
    sp = addiu(sp, -32);
    sd(sp + 16, ra);
    sq(sp, s0);
    s0 = sltu(zero, a0);
    if (s0 != 0) {
        charge(4);
        jal(0x4AC3B0u, gen::fn_sub_4AB0E0_004ab0e0);
        if (v0 != 0) {
            charge(4);
            a0 = v0;
            jal(0x4AC3C0u, gen::fn_sub_4AB0E0_004ab0e0);
            if (v0 != 0) {
                charge(4);
                a0 = v0;
                jal(0x4AC3D0u, gen::fn_sub_4AB0E0_004ab0e0);
                if (v0 != 0) {
                    charge(6);
                    a0 = v0;
                    jal(0x4AC3E0u, gen::fn_sub_4AB0E0_004ab0e0);
                    a0 = v0;
                    jal(0x4AC3E8u, gen::fn_sub_4AC390_004ac390);
                }
            }
        }
        backedge();
    }
    charge(2);
    v0 = s0;
    charge(4);
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 32);
}

// sub_4AE690 [Rt2dSceneUpdateLTM-like: sort the scene's children by depth]: $a0 the scene (+180 the child count,
// +184 the child array {object, depth} pairs, 8 bytes): each pair's depth refreshed from its object (+4), then a
// selection sort by depth (swapping through the frame at sp + 40). Returns the scene.
void Cpu::sub_4AE690() {
    enter(11);
    sp = addiu(sp, -48);
    sd(sp + 16, ra);
    sq(sp, s0);
    s0 = a0;
    a0 = lw(a0 + 184);
    jal(0x4AE6A0u, gen::fn_sub_4C2090_004c2090);
    v1 = lw(s0 + 180);
    v1 = sll(v1, 3);
    a2 = addu(v0, v1);  // the end
    if (v0 != a2) {
        charge(2);
        a0 = v0;
        if (v0 == a2) {
            charge(1);
        } else {
            for (;;) {  // the depths
                charge(7);
                v1 = lw(a0);
                v1 = lw(v1 + 4);
                sw(a0 + 4, v1);
                a0 = addiu(a0, 8);
                if (a0 == a2) break;
                backedge();
            }
            charge(2);
        }
        a1 = addiu(a2, -8);
        charge(3);
        at = sltu(v0, a1);
        if (at != 0) {
            for (;;) {  // selection sort: v0 the position, a3 the candidates after it
                charge(4);
                a3 = addiu(v0, 8);
                at = sltu(a3, a2);
                if (at != 0) {
                    for (;;) {
                        charge(5);
                        a0 = lw(v0 + 4);
                        v1 = lw(a3 + 4);
                        at = slt(v1, a0);
                        if (at != 0) {  // swap the pairs
                            charge(11);
                            lwc1(F3, v0);
                            lwc1(F2, v0 + 4);
                            lwc1(F1, a3);
                            lwc1(F0, a3 + 4);
                            swc1(F3, sp + 40);
                            swc1(F2, sp + 44);
                            swc1(F1, v0);
                            swc1(F0, v0 + 4);
                            swc1(F3, a3);
                            swc1(F2, a3 + 4);
                            backedge();
                        } else {
                            charge(1);
                        }
                        charge(4);
                        a3 = addiu(a3, 8);
                        v1 = sltu(a3, a2);
                        if (v1 == 0) break;
                        backedge();
                    }
                }
                charge(4);
                v0 = addiu(v0, 8);
                v1 = sltu(v0, a1);
                if (v1 == 0) break;
                backedge();
            }
        }
    }
    charge(2);
    v0 = s0;
    charge(4);
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 48);
}

// sub_4AB8C0 [reset the scratch path 0x95ED88]: its node chain destroyed (sub_4AC390(+20)), its point array emptied
// (sub_4C1E60(+0)), +8 = 0, +12 = 1 (flat), +24 = itself. Returns it.
void Cpu::sub_4AB8C0() {
    enter(20);
    sp = addiu(sp, -32);
    v0 = lui(0x96);
    sd(sp + 16, ra);
    sq(sp, s0);
    s0 = lw(v0 - 4728);
    a0 = lw(s0 + 20);
    jal(0x4AB8D4u, gen::fn_sub_4AC390_004ac390);
    sw(s0 + 20, zero);
    a0 = lw(s0);
    jal(0x4AB8E0u, gen::fn_sub_4C1E60_004c1e60);
    sw(s0 + 8, zero);
    v0 = 1;
    sw(s0 + 12, v0);
    sw(s0 + 24, s0);
    v0 = lui(0x96);
    ra = ld(sp + 16);
    lq(s0, sp);
    v0 = lw(v0 - 4728);
    sp = addiu(sp, 32);
}

// sub_4AB6A0 [Rt2dPathClose on a flattened path]: $a0 the path, +24 its flattened copy ({+0 the point array}). When
// the last point differs from the first, the first is appended again (its normal computed); the closing point's and
// the first point's normals become their normalised average; +8 (closed) = 1. Returns the path. ($f20 is spilled to
// the frame and restored.)
void Cpu::sub_4AB6A0() {
    enter(31);
    sp = addiu(sp, -112);
    sd(sp + 80, ra);
    sq(sp + 64, s3);
    sq(sp + 48, s2);
    s3 = a0;
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F20, sp);
    s1 = lw(a0 + 24);
    a0 = lw(s1);
    jal(0x4AB6C4u, gen::fn_sub_4C2120_004c2120);
    a0 = lw(s1);
    s2 = v0;  // the count
    jal(0x4AB6D0u, gen::fn_sub_4C2090_004c2090);
    a0 = lw(s1);
    s0 = v0;  // the first point
    a1 = addiu(s2, -1);
    jal(0x4AB6E0u, gen::fn_sub_4C21B0_004c21b0);
    lwc1(F3, s0 + 8);
    v1 = addiu(sp, 108);
    lwc1(F4, s0 + 4);
    lwc1(F2, v0 + 4);
    lwc1(F1, v0 + 8);
    mtc1(zero, F0);
    swc1(F3, sp + 108);
    lwc1(F20, v1);
    sub_s(F2, F2, F4);
    sub_s(F1, F20, F1);
    c_eq_s(F0, F1);
    swc1(F4, sp + 104);
    bool same = false;
    if (cop1_cond()) {
        charge(3);
        c_eq_s(F0, F2);
        same = cop1_cond();
    }
    if (!same) {  // append the first point again
        charge(27);
        v0 = lw(s3 + 24);
        a0 = lw(v0);
        jal(0x4AB72Cu, gen::fn_sub_4C2120_004c2120);
        v1 = lw(s3 + 24);
        s0 = v0;
        v0 = lui(0x3);
        a0 = lw(v1);
        a1 = v0 | 0x190;
        jal(0x4AB744u, gen::fn_sub_4C1E70_004c1e70);
        lwc1(F3, sp + 104);
        v1 = 1;
        sw(v0, v1);
        mtc1(zero, F0);
        swc1(F3, v0 + 4);
        swc1(F20, v0 + 8);
        lwc1(F1, v0 - 20);
        lwc1(F2, v0 - 16);
        sub_s(F3, F1, F3);
        sub_s(F2, F20, F2);
        mula_s(F3, F3);
        madd_s(F1, F2, F2);
        segment_normal(F2, F3, s0, 4);
        charge(6);
        a0 = lw(s1);
        jal(0x4AB82Cu, gen::fn_sub_4C2090_004c2090);
        a0 = lw(s1);
        a1 = s2;
        s0 = v0;
        jal(0x4AB83Cu, gen::fn_sub_4C21B0_004c21b0);
    }
    // the closing point and the first point share their averaged normal
    charge(30);
    lwc1(F5, s0 + 12);
    v1 = lui(0x3F80);
    lwc1(F2, v0 + 12);
    mtc1(v1, F0);
    lwc1(F3, s0 + 16);
    lwc1(F1, v0 + 16);
    v1 = 1;
    add_s(F4, F5, F2);
    add_s(F2, F3, F1);
    mula_s(F3, F2);
    madd_s(F1, F5, F4);
    div_s(F0, F0, F1);
    mul_s(F1, F4, F0);
    mul_s(F0, F2, F0);
    swc1(F1, v0 + 12);
    swc1(F0, v0 + 16);
    lwc1(F1, v0 + 12);
    lwc1(F0, v0 + 16);
    swc1(F1, s0 + 12);
    v0 = s3;
    swc1(F0, s0 + 16);
    sw(s1 + 8, v1);
    ra = ld(sp + 80);
    lwc1(F20, sp);
    lq(s3, sp + 64);
    lq(s2, sp + 48);
    lq(s1, sp + 32);
    lq(s0, sp + 16);
    sp = addiu(sp, 112);
}

// sub_4ABD50 [Rt2dPathFlatten(dst, src)]: the tolerance (sub_4AA2C0) to 0x95EF60; every record of `src` (24 bytes;
// +4 count or -1) appended to `dst`: lines (type 1) with their normals, curves (type 2: the curve record and the next
// two) flattened by sub_4ABA20 with the budget 0x95EF68, other records copied; a closed source (+8) closes `dst`
// (sub_4AB6A0). Returns dst.
void Cpu::sub_4ABD50() {
    enter(20);
    sp = addiu(sp, -192);
    sd(sp + 144, ra);
    sq(sp + 128, fp);
    sq(sp + 112, s7);
    sq(sp + 96, s6);
    sq(sp + 80, s5);
    sq(sp + 64, s4);
    s5 = a0;
    sq(sp + 48, s3);
    s4 = a1;
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    jal(0x4ABD80u, gen::fn_sub_4AA2C0_004aa2c0);
    v1 = lw(s4 + 4);
    v0 = lui(0x96);
    swc1(F0, v0 - 4256);
    v0 = si(-1);
    if (v1 == v0) {
        charge(4);
        a0 = lw(s4);
        jal(0x4ABDA0u, gen::fn_sub_4C2090_004c2090);
        s1 = lw(s4 + 4);
    } else {
        charge(2);
        v0 = lw(s4);
        s1 = lw(s4 + 4);
    }
    charge(4);
    s3 = v0;
    v0 = si(-1);
    if (s1 == v0) {
        charge(3);
        a0 = lw(s4);
        jal(0x4ABDC8u, gen::fn_sub_4C2120_004c2120);
        s1 = v0;
    }
    charge(3);
    at = slt(zero, s1);
    s2 = zero;
    if (at != 0) {
        charge(3);
        s6 = addiu(sp, 168);
        s7 = addiu(sp, 176);
        fp = addiu(sp, 184);
        for (;;) {
            charge(4);
            v1 = lw(s3);
            v0 = 2;
            if (v1 == v0) {  // a curve: the four control points into the frame (sp + 160 ..), flattened
                charge(24);
                lwc1(F1, s3 - 20);
                v0 = lui(0x96);
                lwc1(F0, s3 - 16);
                a2 = lw(v0 - 4248);
                a1 = addiu(sp, 160);
                a0 = s5;
                swc1(F1, sp + 160);
                swc1(F0, sp + 164);
                lwc1(F1, s3 + 4);
                lwc1(F0, s3 + 8);
                swc1(F1, s6);
                swc1(F0, s6 + 4);
                lwc1(F1, s3 + 28);
                lwc1(F0, s3 + 32);
                swc1(F1, s7);
                swc1(F0, s7 + 4);
                lwc1(F1, s3 + 52);
                lwc1(F0, s3 + 56);
                swc1(F1, fp);
                swc1(F0, fp + 4);
                jal(0x4ABFC4u, gen::fn_sub_4ABA20_004aba20);
                s2 = addiu(s2, 2);
                s3 = addiu(s3, 48);
                backedge();
            } else {
                charge(3);
                v0 = 1;
                if (v1 == v0) {  // a line: append with its normal
                    charge(28);
                    a0 = lw(s5);
                    jal(0x4ABE08u, gen::fn_sub_4C2120_004c2120);
                    a0 = lw(s5);
                    s0 = v0;
                    v0 = lui(0x3);
                    a1 = v0 | 0x190;
                    jal(0x4ABE1Cu, gen::fn_sub_4C1E70_004c1e70);
                    v1 = 1;
                    sw(v0, v1);
                    mtc1(zero, F0);
                    lwc1(F1, s3 + 4);
                    swc1(F1, v0 + 4);
                    lwc1(F1, s3 + 8);
                    swc1(F1, v0 + 8);
                    lwc1(F2, v0 - 20);
                    lwc1(F1, s3 + 4);
                    lwc1(F4, s3 + 8);
                    lwc1(F3, v0 - 16);
                    sub_s(F2, F2, F1);
                    sub_s(F3, F4, F3);
                    mula_s(F2, F2);
                    madd_s(F1, F3, F3);
                    segment_normal(F3, F2, s0, 5);
                } else {  // anything else: copied
                    charge(16);
                    a0 = lw(s5);
                    v0 = lui(0x3);
                    a1 = v0 | 0x1A1;
                    jal(0x4ABF1Cu, gen::fn_sub_4C1E70_004c1e70);
                    lwc1(F3, s3);
                    lwc1(F2, s3 + 4);
                    lwc1(F1, s3 + 8);
                    lwc1(F0, s3 + 12);
                    swc1(F3, v0);
                    swc1(F2, v0 + 4);
                    swc1(F1, v0 + 8);
                    swc1(F0, v0 + 12);
                    lwc1(F1, s3 + 16);
                    lwc1(F0, s3 + 20);
                    swc1(F1, v0 + 16);
                    swc1(F0, v0 + 20);
                }
            }
            charge(4);
            s2 = addiu(s2, 1);
            v0 = slt(s2, s1);
            s3 = addiu(s3, 24);
            if (v0 == 0) break;
            backedge();
        }
    }
    charge(3);
    v0 = lw(s4 + 8);
    if (v0 != 0) {
        charge(4);
        a0 = s5;
        jal(0x4ABFD8u, gen::fn_sub_4AB6A0_004ab6a0);
        backedge();
    }
    charge(2);
    v0 = s5;
    charge(12);
    ra = ld(sp + 144);
    lq(fp, sp + 128);
    lq(s7, sp + 112);
    lq(s6, sp + 96);
    lq(s5, sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 192);
}

// sub_4AAE60 [Rt2d device matrix]: once per change (0x95EF50 clear): the device scale (1.0 for a camera of projection
// 2, else 0x95EF58), CTM x the base matrix 0x95EEB0 (sub_4C2F30), scaled by (s, s, 1) and (-aspect, 1, 1) (sub_4C33D0
// post-concat), translated by (w / 2 * s, -h / 2 * s) (sub_4C35D0): the matrix copied to 0x95EE90 and its inverse to
// 0x95EED0 (sub_4C32A0), the flag set. Every call: 0x95EF10 = 0x95EE90 x the camera frame's LTM (sub_4CB2F0 of camera
// +4), returned. $f20..$f22 are spilled to the frame.
void Cpu::sub_4AAE60() {
    enter(11);
    sp = addiu(sp, -160);
    v0 = lui(0x96);
    sd(sp + 48, ra);
    sq(sp + 32, s1);
    sq(sp + 16, s0);
    swc1(F22, sp + 8);
    swc1(F21, sp + 4);
    swc1(F20, sp);
    v0 = lw(v0 - 4272);
    if (v0 == 0) {
        charge(6);
        v0 = lui(0x96);
        v1 = 2;
        v0 = lw(v0 - 4220);   // the camera
        v0 = lw(v0 + 20);
        if (v0 == v1) {
            charge(4);
            v0 = lui(0x3F80);
            mtc1(v0, F22);
        } else {
            charge(2);
            v0 = lui(0x96);
            lwc1(F22, v0 - 4264);
        }
        charge(28);
        v0 = lui(0x96);
        v1 = lui(0x96);
        v0 = lw(v0 - 4496);
        a2 = lui(0x96);
        v1 = addiu(v1, -4624);
        a0 = addiu(sp, 64);
        v0 = sll(v0, 2);
        v0 = addu(v1, v0);
        a1 = lw(v0);
        a2 = addiu(a2, -4688);
        jal(0x4AAEE0u, gen::fn_sub_4C2F30_004c2f30);
        v0 = lui(0x96);
        s1 = addiu(sp, 148);
        lwc1(F20, v0 - 4492);
        s0 = addiu(sp, 152);
        a0 = addiu(sp, 64);
        a1 = addiu(sp, 144);
        a2 = 2;
        swc1(F22, sp + 144);
        swc1(F22, s1);
        v0 = lui(0x96);
        lwc1(F21, v0 - 4488);
        v0 = lui(0x3F80);
        sw(s0, v0);
        jal(0x4AAF18u, gen::fn_sub_4C33D0_004c33d0);
        c_lt_s(F20, F21);
        if (cop1_cond()) {
            charge(2);
            mov_s(F0, F20);
        } else {
            charge(1);
            mov_s(F0, F21);
        }
        charge(78);
        swc1(F0, s1);
        v0 = lui(0x3F80);
        neg_s(F0, F0);
        sw(s0, v0);
        swc1(F0, sp + 144);
        a0 = addiu(sp, 64);
        a1 = addiu(sp, 144);
        a2 = 2;
        jal(0x4AAF54u, gen::fn_sub_4C33D0_004c33d0);
        v0 = lui(0x3F00);
        a0 = addiu(sp, 64);
        mtc1(v0, F0);
        a1 = addiu(sp, 128);
        a2 = 2;
        sw(sp + 136, zero);
        mul_s(F1, F0, F20);
        mul_s(F0, F0, F21);
        mul_s(F0, F0, F22);
        mul_s(F1, F1, F22);
        neg_s(F0, F0);
        swc1(F1, sp + 128);
        swc1(F0, sp + 132);
        jal(0x4AAF8Cu, gen::fn_sub_4C35D0_004c35d0);
        // the matrix (sp + 64) to 0x95EE90, word by word in the compiled order
        lwc1(F0, sp + 64);
        a3 = lui(0x96);
        lwc1(F4, sp + 68);
        v1 = lui(0x96);
        lwc1(F1, sp + 80);
        a1 = lui(0x96);
        lwc1(F3, sp + 72);
        a2 = lui(0x96);
        lwc1(F2, sp + 84);
        a0 = lui(0x96);
        t0 = lw(sp + 76);
        v0 = lui(0x96);
        swc1(F0, a3 - 4464);
        lwc1(F0, sp + 88);
        a3 = lw(sp + 108);
        swc1(F1, a1 - 4448);
        swc1(F3, a2 - 4456);
        a1 = lui(0x96);
        swc1(F2, a0 - 4444);
        a2 = lw(sp + 92);
        swc1(F4, v1 - 4460);
        sw(v0 - 4452, t0);
        v1 = lui(0x96);
        v0 = lui(0x96);
        swc1(F0, v1 - 4440);
        a0 = lui(0x96);
        lwc1(F1, sp + 96);
        v1 = lui(0x96);
        lwc1(F0, sp + 104);
        sw(v0 - 4436, a2);
        lwc1(F3, sp + 100);
        v0 = lui(0x96);
        a2 = lw(sp + 124);
        sw(v0 - 4420, a3);
        lwc1(F2, sp + 112);
        v0 = lui(0x96);
        swc1(F1, a0 - 4432);
        swc1(F0, v1 - 4424);
        a0 = lui(0x96);
        lwc1(F1, sp + 116);
        v1 = lui(0x96);
        lwc1(F0, sp + 120);
        sw(v0 - 4404, a2);
        swc1(F3, a1 - 4428);
        a1 = lui(0x96);
        swc1(F2, a0 - 4416);
        a0 = lui(0x96);
        swc1(F1, a1 - 4412);
        a0 = addiu(a0, -4400);
        a1 = addiu(sp, 64);
        swc1(F0, v1 - 4408);
        jal(0x4AB05Cu, gen::fn_sub_4C32A0_004c32a0);
        v1 = 1;
        v0 = lui(0x96);
        sw(v0 - 4272, v1);
    }
    charge(20);
    v0 = lui(0x96);
    v0 = lw(v0 - 4220);
    a0 = lw(v0 + 4);
    jal(0x4AB078u, gen::fn_sub_4CB2F0_004cb2f0);
    a0 = lui(0x96);
    a1 = lui(0x96);
    a2 = v0;
    a0 = addiu(a0, -4336);
    a1 = addiu(a1, -4464);
    jal(0x4AB090u, gen::fn_sub_4C2F30_004c2f30);
    ra = ld(sp + 48);
    lwc1(F22, sp + 8);
    lq(s1, sp + 32);
    lwc1(F21, sp + 4);
    lq(s0, sp + 16);
    lwc1(F20, sp);
    v0 = lui(0x96);
    v0 = addiu(v0, -4336);
    sp = addiu(sp, 160);
}

// sub_4AA2C0 [the flattening tolerance]: cached in 0x95EF60 while 0x95EF64 is set; else the device matrix
// (sub_4AAE60) transforms the vector (0x95EF58 * 0x95EF5C * height / width, 0, 0) (sub_4C6C60 into the frame at
// sp + 48) and its squared length is the tolerance. Returned in $f0.
void Cpu::sub_4AA2C0() {
    enter(8);
    sp = addiu(sp, -64);
    v0 = lui(0x96);
    sd(sp + 32, ra);
    sq(sp + 16, s1);
    sq(sp, s0);
    v0 = lw(v0 - 4252);
    if (v0 == 0) {
        charge(35);
        jal(0x4AA2ECu, gen::fn_sub_4AAE60_004aae60);
        v1 = lui(0x96);
        v0 = lui(0x96);
        lwc1(F3, v1 - 4492);
        a0 = addiu(sp, 48);
        lwc1(F2, v0 - 4484);
        a2 = lui(0x96);
        s1 = addiu(sp, 52);
        s0 = addiu(sp, 56);
        a1 = a0;
        a2 = addiu(a2, -4400);
        sw(s1, zero);
        sw(s0, zero);
        v1 = lui(0x96);
        div_s(F2, F3, F2);
        v0 = lui(0x96);
        lwc1(F1, v1 - 4264);
        lwc1(F0, v0 - 4260);
        mul_s(F1, F1, F2);
        mul_s(F0, F0, F1);
        swc1(F0, sp + 48);
        jal(0x4AA340u, gen::fn_sub_4C6C60_004c6c60);
        lwc1(F2, s1);
        v1 = lui(0x96);
        lwc1(F0, sp + 48);
        a0 = 1;
        lwc1(F1, s0);
        v0 = lui(0x96);
        sw(v0 - 4252, a0);
        mula_s(F2, F2);
        madda_s(F0, F0);
        madd_s(F0, F1, F1);
        swc1(F0, v1 - 4256);
        backedge();
    }
    charge(3);
    v0 = lui(0x96);
    lwc1(F0, v0 - 4256);
    charge(5);
    ra = ld(sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 64);
}

// sub_4AD750 [Rt2dObjectString render]: a visible string (+8 & 0x1000004 == 4): its 8-byte frame buffer cleared, the
// object's CTM pushed, the font's colour block (+180 font, its +0 .. +87) saved, mixed with the object's colour
// (+144 / +160) by sub_4A55B0, the string drawn through the font's callback (sub_4A9A70: +192 font object +4, text
// +176, size $f12 = +188), the CTM popped and the colour block restored. Returns the object.
void Cpu::sub_4AD750() {
    enter(15);
    sp = addiu(sp, -208);
    v0 = lui(0x100);
    sd(sp + 80, ra);
    v1 = v0 | 4;
    sq(sp + 64, s4);
    v0 = 4;
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    s0 = a0;
    a0 = lw(a0 + 8);
    v1 = a0 & v1;
    if (v1 == v0) {
        charge(3);
        v1 = addiu(sp, 200);
        v0 = 8;
        if (v1 != 0) {
            for (;;) {  // the 8-byte buffer at sp + 200 cleared
                charge(7);
                sb(v1, zero);
                v0 = addiu(v0, -1);
                v1 = addiu(v1, 1);
                if (v0 == 0) break;
                backedge();
            }
        }
        charge(5);
        v1 = lw(s0 + 8);
        v0 = 2;
        v1 = v1 & 2;
        if (v1 == v0) {
            charge(6);
            a0 = addiu(s0, 16);
            jal(0x4AD8D4u, gen::fn_sub_4AAB40_004aab40);
            jal(0x4AD8DCu, gen::fn_sub_4AB0C0_004ab0c0);
            a2 = addiu(s0, 80);
            copy_matrix(a1, v0, a2, a0, v1, true);
            charge(5);
            v1 = lw(s0 + 8);
            v0 = si(-3);
            v0 = v1 & v0;
            sw(s0 + 8, v0);
            backedge();
        } else {
            charge(2);
            a0 = addiu(s0, 80);
            jal(0x4AD7D0u, gen::fn_sub_4AAC70_004aac70);
        }
        charge(63);
        a0 = addiu(sp, 176);
        a1 = addiu(s0, 144);
        a2 = 0x10;
        jal(0x4AD7E0u, gen::fn_memcpy_00521250);
        a0 = addiu(sp, 160);
        a1 = addiu(s0, 160);
        a2 = 0x10;
        jal(0x4AD7F0u, gen::fn_memcpy_00521250);
        s1 = lw(s0 + 180);
        a0 = addiu(sp, 96);
        a2 = 0x10;
        a1 = addiu(s1, 48);
        jal(0x4AD804u, gen::fn_memcpy_00521250);
        s2 = addiu(sp, 112);
        a1 = addiu(s1, 72);
        a0 = s2;
        a2 = 0x10;
        jal(0x4AD818u, gen::fn_memcpy_00521250);
        s3 = addiu(sp, 128);
        a1 = addiu(s1, 24);
        a0 = s3;
        a2 = 0x10;
        jal(0x4AD82Cu, gen::fn_memcpy_00521250);
        s4 = addiu(sp, 144);
        a1 = s1;
        a0 = s4;
        a2 = 0x10;
        jal(0x4AD840u, gen::fn_memcpy_00521250);
        a0 = s1;
        a1 = addiu(sp, 96);
        a2 = s2;
        a3 = s3;
        t0 = s4;
        t1 = addiu(sp, 176);
        t2 = addiu(sp, 160);
        jal(0x4AD860u, gen::fn_sub_4A55B0_004a55b0);
        v0 = lw(s0 + 192);
        lwc1(F12, s0 + 188);
        a1 = lw(s0 + 176);
        a2 = addiu(sp, 200);
        a0 = lw(v0 + 4);
        a3 = s1;
        jal(0x4AD87Cu, gen::fn_sub_4A9A70_004a9a70);
        jal(0x4AD884u, gen::fn_sub_4AAD50_004aad50);
        a0 = addiu(s1, 48);
        a1 = addiu(sp, 96);
        a2 = 0x10;
        jal(0x4AD894u, gen::fn_memcpy_00521250);
        a1 = s2;
        a0 = addiu(s1, 72);
        a2 = 0x10;
        jal(0x4AD8A4u, gen::fn_memcpy_00521250);
        a1 = s3;
        a0 = addiu(s1, 24);
        a2 = 0x10;
        jal(0x4AD8B4u, gen::fn_memcpy_00521250);
        a0 = s1;
        a1 = s4;
        a2 = 0x10;
        jal(0x4AD8C4u, gen::fn_memcpy_00521250);
        backedge();
    }
    charge(2);
    v0 = s0;
    charge(8);
    ra = ld(sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 208);
}

// sub_4AE2F0 [Rt2dPickRegion update]: a visible region (+8 bit 2): a dirty local matrix is pushed and read back into
// +80 with its inverse at +208 (sub_4C32A0), otherwise +80 is pushed; then popped. Returns the region.
void Cpu::sub_4AE2F0() {
    enter(9);
    sp = addiu(sp, -32);
    v0 = 4;
    sd(sp + 16, ra);
    sq(sp, s0);
    s0 = a0;
    a0 = lw(a0 + 8);
    v1 = a0 & 4;
    if (v1 == v0) {
        charge(4);
        v1 = a0 & 2;
        v0 = 2;
        if (v1 == v0) {
            charge(6);
            a0 = addiu(s0, 16);
            jal(0x4AE33Cu, gen::fn_sub_4AAB40_004aab40);
            jal(0x4AE344u, gen::fn_sub_4AB0C0_004ab0c0);
            a2 = addiu(s0, 80);
            copy_matrix(a1, v0, a2, a0, v1, true);
            charge(8);
            a0 = addiu(s0, 208);
            a1 = addiu(s0, 80);
            jal(0x4AE378u, gen::fn_sub_4C32A0_004c32a0);
            v1 = lw(s0 + 8);
            v0 = si(-3);
            v0 = v1 & v0;
            sw(s0 + 8, v0);
            backedge();
        } else {
            charge(2);
            a0 = addiu(s0, 80);
            jal(0x4AE324u, gen::fn_sub_4AAC70_004aac70);
        }
        charge(2);
        jal(0x4AE32Cu, gen::fn_sub_4AAD50_004aad50);
    }
    charge(2);
    v0 = s0;
    charge(4);
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 32);
}

// sub_4A6600 [stroke a path]: sub_46BD00($a0, $a1), returning $a0.
void Cpu::sub_4A6600() {
    enter(10);
    sp = addiu(sp, -32);
    sd(sp + 16, ra);
    sq(sp, s0);
    s0 = a0;
    jal(0x4A660Cu, gen::fn_sub_46BD00_0046bd00);
    v0 = s0;
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 32);
}

// sub_4ACE70 [fill a path]: a static tail call into sub_46BAB0.
void Cpu::sub_4ACE70() {
    enter(2);
    tailcall(gen::fn_sub_46BAB0_0046bab0);
}

// sub_4ADF30 [Rt2dObject render]: by the object's type (+0): 4 string (sub_4AD750), 3 pick region (sub_4AE2F0),
// 2 shape (sub_4AF9D0), 1 scene (sub_4AE960 with the colour multiplier / offset $a1 / $a2), 0 nothing; another type
// returns 0, else the object.
void Cpu::sub_4ADF30() {
    enter(7);
    sp = addiu(sp, -32);
    v0 = 4;
    sd(sp + 16, ra);
    sq(sp, s0);
    v1 = lw(a0);
    s0 = a0;
    bool scene = false;
    if (v1 == v0) {
        charge(2);
        jal(0x4ADFB0u, gen::fn_sub_4AD750_004ad750);
    } else if ((charge(3), v0 = 3, v1 == v0)) {
        charge(4);
        jal(0x4ADFA0u, gen::fn_sub_4AE2F0_004ae2f0);
    } else if ((charge(3), v0 = 2, v1 == v0)) {
        charge(4);
        jal(0x4ADF90u, gen::fn_sub_4AF9D0_004af9d0);
    } else if ((charge(3), v0 = 1, v1 == v0)) {
        charge(4);
        jal(0x4ADF80u, gen::fn_sub_4AE960_004ae960);
        v0 = s0;
        scene = true;
    } else {
        charge(2);
        if (v1 != 0) {
            charge(2);
            s0 = zero;
        }
    }
    if (!scene) {
        charge(1);
        v0 = s0;
    }
    charge(4);
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 32);
}

// sub_4AE960 [Rt2dSceneRender(scene, multiply, offset)]: a visible scene (+8 bit 2): the CTM pushed (dirty: matrix x
// CTM read back, every child marked dirty), the colour multiplier (scene +144.. * $a1) and offset (scene +160.. / 255 *
// multiplier + $a2) into the frame (sp + 96 / sp + 80); children re-sorted when +188 (sub_4AE690); each child
// rendered (sub_4ADF30) with the combined colours; the CTM popped. Returns the scene.
void Cpu::sub_4AE960() {
    enter(14);
    sp = addiu(sp, -112);
    v0 = 4;
    sd(sp + 64, ra);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    s3 = a0;
    sq(sp + 16, s1);
    s2 = zero;  // children need a dirty mark
    sq(sp, s0);
    s1 = a1;
    a0 = lw(a0 + 8);
    v1 = a0 & 4;
    s0 = a2;
    if (v1 == v0) {
        charge(4);
        v1 = a0 & 2;
        v0 = 2;
        if (v1 == v0) {
            charge(6);
            a0 = addiu(s3, 16);
            jal(0x4AEAC0u, gen::fn_sub_4AAB40_004aab40);
            jal(0x4AEAC8u, gen::fn_sub_4AB0C0_004ab0c0);
            a2 = addiu(s3, 80);
            copy_matrix(a1, v0, a2, a0, v1, true);
            charge(6);
            v1 = lw(s3 + 8);
            v0 = si(-3);
            s2 = 1;
            v0 = v1 & v0;
            sw(s3 + 8, v0);
            backedge();
        } else {
            charge(2);
            a0 = addiu(s3, 80);
            jal(0x4AE9A8u, gen::fn_sub_4AAC70_004aac70);
        }
        // the combined colours
        charge(51);
        lwc1(F1, s3 + 144);
        v0 = lui(0x437F);
        lwc1(F9, s1);
        lwc1(F8, s1 + 4);
        lwc1(F7, s1 + 8);
        lwc1(F6, s1 + 12);
        mtc1(v0, F5);
        lwc1(F0, s0);
        mul_s(F1, F1, F9);
        swc1(F1, sp + 96);
        lwc1(F4, s3 + 148);
        mtc1(zero, F3);
        lwc1(F2, s0 + 4);
        adda_s(F3, F0);
        lwc1(F1, s0 + 8);
        lwc1(F0, s0 + 12);
        mul_s(F4, F4, F8);
        swc1(F4, sp + 100);
        lwc1(F4, s3 + 152);
        mul_s(F4, F4, F7);
        swc1(F4, sp + 104);
        lwc1(F4, s3 + 156);
        mul_s(F4, F4, F6);
        swc1(F4, sp + 108);
        lwc1(F4, s3 + 160);
        div_s(F4, F4, F5);
        madd_s(F4, F4, F9);
        swc1(F4, sp + 80);
        adda_s(F3, F2);
        lwc1(F2, s3 + 164);
        div_s(F2, F2, F5);
        madd_s(F2, F2, F8);
        swc1(F2, sp + 84);
        adda_s(F3, F1);
        lwc1(F1, s3 + 168);
        div_s(F1, F1, F5);
        madd_s(F1, F1, F7);
        adda_s(F3, F0);
        swc1(F1, sp + 88);
        lwc1(F0, s3 + 172);
        div_s(F0, F0, F5);
        madd_s(F0, F0, F6);
        swc1(F0, sp + 92);
        a0 = lw(s3 + 184);
        jal(0x4AEA5Cu, gen::fn_sub_4C2090_004c2090);
        s1 = v0;
        v1 = lw(s3 + 180);
        v0 = lw(s3 + 188);
        v1 = sll(v1, 3);
        s0 = addu(s1, v1);
        if (v0 != 0) {  // re-sort first
            charge(4);
            a0 = s3;
            jal(0x4AEB10u, gen::fn_sub_4AE690_004ae690);
            sw(s3 + 188, zero);
            backedge();
        }
        charge(2);
        if (s1 != s0) {
            for (;;) {
                charge(2);
                if (s2 != 0) {
                    charge(5);
                    v1 = lw(s1);
                    v0 = lw(v1 + 8);
                    v0 = v0 | 2;
                    sw(v1 + 8, v0);
                    backedge();
                } else {
                    charge(1);
                }
                charge(7);
                a0 = lw(s1);
                a1 = addiu(sp, 96);
                a2 = addiu(sp, 80);
                jal(0x4AEA98u, gen::fn_sub_4ADF30_004adf30);
                s1 = addiu(s1, 8);
                if (s1 == s0) break;
                backedge();
            }
            charge(1);
        }
        charge(2);
        jal(0x4AEAB0u, gen::fn_sub_4AAD50_004aad50);
    }
    charge(2);
    v0 = s3;
    charge(7);
    ra = ld(sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 112);
}

// sub_4AE940 [Rt2dSceneRender with the default colours]: a static tail call into sub_4AE960 with the multiplier /
// offset 0x7BCB70 / 0x7BCB80.
void Cpu::sub_4AE940() {
    enter(5);
    a1 = lui(0x7C);
    a2 = lui(0x7C);
    a1 = addiu(a1, -13456);
    a2 = addiu(a2, -13440);
    tailcall(gen::fn_sub_4AE960_004ae960);
}

// sub_4B5330 [a Maestro's scene render]: the scene at +36 rendered (sub_4AE940) when present; returns the object, or 0
// when the render failed.
void Cpu::sub_4B5330() {
    enter(7);
    sp = addiu(sp, -32);
    sd(sp + 16, ra);
    sq(sp, s0);
    s0 = a0;
    a0 = lw(a0 + 36);
    if (a0 != 0) {
        charge(4);
        jal(0x4B534Cu, gen::fn_sub_4AE940_004ae940);
        if (v0 == 0) {
            charge(2);
            v0 = zero;
            charge(4);
            ra = ld(sp + 16);
            lq(s0, sp);
            sp = addiu(sp, 32);
            return;
        }
    }
    charge(1);
    v0 = s0;
    charge(4);
    ra = ld(sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 32);
}

// The dirty-matrix push of an Rt2d object at `obj` (sub_4AF9D0's two copies): matrix x CTM (sub_4AAB40(+16), pc
// `push_pc`; sub_4AB0C0 at push_pc + 8) read back into +80, the dirty bit (+8 bit 1) cleared. Ends with a backedge
// (the block sits after its join point).
void Cpu::object_push_dirty(const Gpr& obj, u32 push_pc) {
    charge(6);
    a0 = addiu(obj, 16);
    jal(push_pc, gen::fn_sub_4AAB40_004aab40);
    jal(push_pc + 8, gen::fn_sub_4AB0C0_004ab0c0);
    a2 = addiu(obj, 80);
    copy_matrix(a1, v0, a2, a0, v1, true);
    charge(5);
    v1 = lw(obj + 8);
    v0 = si(-3);
    v0 = v1 & v0;
    sw(obj + 8, v0);
    backedge();
}

// sub_4AF9D0 [Rt2dShape render(shape, multiply, offset)]: a visible shape (+8 bit 2). The combined colour multiplier
// (shape +144.. * $a1, frame sp + 208) and offset (shape +160.. * $a1 + 255 * $a2, sp + 192).
//   * A shape built on an atomic (+184): each of its material colours (the atomic's geometry +8 -> +36 count, +32 the
//     materials) = clamp(offset + multiplier * the shape's colour bytes (+180, 4 per material), 0, 255) as RGBA bytes
//     (assembled at sp + 236 .. 239, then stored into material +4 .. +7); +8 bit 3 cleared; the CTM pushed; the
//     atomic's frame transform set from the Rt2d device matrix (sub_4AAE60 -> sub_4CB7F0(frame, matrix, 0)) and the
//     atomic rendered through its callback (+72).
//   * Otherwise each node of the shape's path list (+176: 12-byte {flags, path, brush} records): the brush's colour
//     block saved, mixed (sub_4A55B0), the path stroked (flags bit 0: sub_4A6600) or filled (sub_4ACE70), the colour
//     block restored.
// The CTM popped; returns the shape.
void Cpu::sub_4AF9D0() {
    enter(13);
    sp = addiu(sp, -240);
    sd(sp + 112, ra);
    sq(sp + 96, s6);
    sq(sp + 80, s5);
    sq(sp + 64, s4);
    sq(sp + 48, s3);
    sq(sp + 32, s2);
    sq(sp + 16, s1);
    sq(sp, s0);
    v0 = lw(a0 + 8);
    v0 = v0 & 4;
    s5 = a0;
    if (v0 != 0) {
        charge(47);
        lwc1(F0, s5 + 144);
        v0 = lui(0x437F);
        lwc1(F9, a1);
        t6 = addiu(sp, 212);
        lwc1(F8, a1 + 4);
        t5 = addiu(sp, 216);
        lwc1(F7, a1 + 8);
        t4 = addiu(sp, 220);
        lwc1(F6, a1 + 12);
        t3 = addiu(sp, 196);
        lwc1(F4, a2);
        t2 = addiu(sp, 200);
        mtc1(v0, F5);
        t1 = addiu(sp, 204);
        mul_s(F0, F0, F9);
        swc1(F0, sp + 208);
        lwc1(F0, s5 + 148);
        lwc1(F3, a2 + 4);
        lwc1(F2, a2 + 8);
        lwc1(F1, a2 + 12);
        mul_s(F0, F0, F8);
        swc1(F0, t6);
        lwc1(F0, s5 + 152);
        mul_s(F0, F0, F7);
        swc1(F0, t5);
        lwc1(F0, s5 + 156);
        mul_s(F0, F0, F6);
        swc1(F0, t4);
        lwc1(F0, s5 + 160);
        mula_s(F0, F9);
        madd_s(F0, F5, F4);
        swc1(F0, sp + 192);
        lwc1(F0, s5 + 164);
        mula_s(F0, F8);
        madd_s(F0, F5, F3);
        swc1(F0, t3);
        lwc1(F0, s5 + 168);
        mula_s(F0, F7);
        madd_s(F0, F5, F2);
        swc1(F0, t2);
        lwc1(F0, s5 + 172);
        mula_s(F0, F6);
        madd_s(F0, F5, F1);
        swc1(F0, t1);
        v0 = lw(s5 + 184);
        if (v0 != 0) {
            // the atomic's material colours
            charge(6);
            v0 = lw(s5 + 176);
            t0 = lw(v0 + 8);
            a3 = lw(t0 + 36);
            at = sltu(zero, a3);
            s2 = zero;
            if (at != 0) {
                charge(6);
                mtc1(zero, F3);
                t7 = zero;
                a2 = addiu(sp, 237);
                a1 = addiu(sp, 238);
                a0 = addiu(sp, 239);
                v0 = 0xFF;
                // a channel's candidate min(x, 255) into `cand` (the < 256 test already in $at)
                auto pick_cand = [&](Gpr& cand, const Gpr& x) {
                    if (at != 0) {
                        charge(1);
                        cand = x;
                    } else {
                        charge(2);
                        cand = v0;
                    }
                };
                // x clamped to [0, 255] by the candidate's sign, then the block's tail (the next value's < 256 test)
                auto clamp = [&](const Gpr& cand, Gpr& x, auto&& tail) {
                    charge(3);
                    at = slt(zero, cand);
                    if (at != 0) {
                        charge(3);
                        at = slti(x, 256);
                        if (at == 0) {
                            charge(1);
                            x = v0;
                        }
                        charge(2);
                    } else {
                        charge(2);
                        x = zero;
                    }
                    tail();
                };
                for (;;) {
                    charge(5);
                    v1 = lw(s5 + 180);
                    v1 = addu(v1, t7);
                    s0 = lbu(v1);
                    lwc1(F2, sp + 208);
                    u2f(s0, s1, F1, F0);
                    charge(8);
                    lwc1(F0, sp + 192);
                    s0 = lbu(v1 + 1);
                    adda_s(F3, F0);
                    madd_s(F0, F2, F1);
                    cvt_w_s(F0, F0);
                    mfc1(s1, F0);  // red
                    u2f(s0, s3, F2, F0);
                    charge(9);
                    lwc1(F0, t3);
                    s3 = lbu(v1 + 2);
                    lwc1(F1, t6);
                    adda_s(F3, F0);
                    madd_s(F0, F1, F2);
                    cvt_w_s(F0, F0);
                    mfc1(s0, F0);  // green
                    u2f(s3, s4, F2, F0);
                    charge(9);
                    lwc1(F0, t2);
                    s3 = lbu(v1 + 3);
                    lwc1(F1, t5);
                    adda_s(F3, F0);
                    madd_s(F0, F1, F2);
                    cvt_w_s(F0, F0);
                    mfc1(v1, F0);  // blue
                    u2f(s3, s4, F2, F0);
                    charge(9);
                    lwc1(F0, t1);
                    at = slti(s1, 256);
                    lwc1(F1, t4);
                    adda_s(F3, F0);
                    madd_s(F0, F1, F2);
                    cvt_w_s(F0, F0);
                    mfc1(s4, F0);  // alpha
                    pick_cand(s3, s1);
                    clamp(s3, s1, [&] { at = slti(s0, 256); });
                    charge(2);
                    sb(sp + 236, s1);
                    pick_cand(s1, s0);
                    clamp(s1, s0, [&] { at = slti(v1, 256); });
                    charge(2);
                    sb(a2, s0);
                    pick_cand(s0, v1);
                    clamp(s0, v1, [&] { at = slti(s4, 256); });
                    charge(2);
                    sb(a1, v1);
                    pick_cand(v1, s4);
                    clamp(v1, s4, [&] { s6 = lw(t0 + 32); });
                    // into the material's colour
                    charge(15);
                    s2 = addiu(s2, 1);
                    sb(a0, s4);
                    v1 = sltu(s2, a3);
                    s4 = lbu(sp + 236);
                    s3 = lbu(sp + 237);
                    s1 = lbu(sp + 238);
                    s0 = lbu(sp + 239);
                    s6 = addu(s6, t7);
                    s6 = lw(s6);
                    t7 = addiu(t7, 4);
                    sb(s6 + 4, s4);
                    sb(s6 + 5, s3);
                    sb(s6 + 6, s1);
                    sb(s6 + 7, s0);
                    if (v1 == 0) break;
                    backedge();
                }
            }
            charge(9);
            a0 = lw(s5 + 8);
            v1 = si(-9);
            v0 = 2;
            v1 = a0 & v1;
            sw(s5 + 8, v1);
            v1 = lw(s5 + 8);
            v1 = v1 & 2;
            if (v1 == v0) {
                object_push_dirty(s5, 0x4AFF60u);
            } else {
                charge(2);
                a0 = addiu(s5, 80);
                jal(0x4AFD88u, gen::fn_sub_4AAC70_004aac70);
            }
            charge(11);
            jal(0x4AFD90u, gen::fn_sub_4AAE60_004aae60);
            a1 = v0;
            v0 = lw(s5 + 184);
            a0 = lw(v0 + 4);
            a2 = zero;
            jal(0x4AFDA4u, gen::fn_sub_4CB7F0_004cb7f0);
            a0 = lw(s5 + 184);
            v0 = lw(a0 + 72);
            jalr(0x4AFDB4u, v0.u());
        } else {
            // the path nodes
            charge(5);
            v1 = lw(s5 + 8);
            v0 = 2;
            v1 = v1 & 2;
            if (v1 == v0) {
                object_push_dirty(s5, 0x4AFF14u);
            } else {
                charge(2);
                a0 = addiu(s5, 80);
                jal(0x4AFDE0u, gen::fn_sub_4AAC70_004aac70);
            }
            charge(13);
            v0 = lw(s5 + 176);
            a0 = lw(v0);
            jal(0x4AFDECu, gen::fn_sub_4C2090_004c2090);
            s4 = v0;
            v0 = lw(s5 + 176);
            a0 = lw(v0);
            jal(0x4AFDFCu, gen::fn_sub_4C2120_004c2120);
            v1 = sll(v0, 1);
            v0 = addu(v1, v0);
            v0 = sll(v0, 2);
            s6 = addu(s4, v0);  // the end of the 12-byte records
            if (s4 != s6) {
                charge(3);
                s2 = addiu(sp, 144);
                s1 = addiu(sp, 160);
                s0 = addiu(sp, 176);
                for (;;) {
                    charge(29);
                    s3 = lw(s4 + 8);  // the brush
                    a0 = addiu(sp, 128);
                    a2 = 0x10;
                    a1 = addiu(s3, 48);
                    jal(0x4AFE34u, gen::fn_memcpy_00521250);
                    a0 = s2;
                    a1 = addiu(s3, 72);
                    a2 = 0x10;
                    jal(0x4AFE44u, gen::fn_memcpy_00521250);
                    a0 = s1;
                    a1 = addiu(s3, 24);
                    a2 = 0x10;
                    jal(0x4AFE54u, gen::fn_memcpy_00521250);
                    a0 = s0;
                    a1 = s3;
                    a2 = 0x10;
                    jal(0x4AFE64u, gen::fn_memcpy_00521250);
                    a0 = s3;
                    a1 = addiu(sp, 128);
                    a2 = s2;
                    a3 = s1;
                    t0 = s0;
                    t1 = addiu(sp, 208);
                    t2 = addiu(sp, 192);
                    jal(0x4AFE84u, gen::fn_sub_4A55B0_004a55b0);
                    v0 = lw(s4);
                    v0 = v0 & 1;
                    if (v0 != 0) {
                        charge(5);
                        a0 = lw(s4 + 4);
                        a1 = s3;
                        jal(0x4AFEA0u, gen::fn_sub_4A6600_004a6600);
                    } else {
                        charge(4);
                        a0 = lw(s4 + 4);
                        a1 = s3;
                        jal(0x4AFEB4u, gen::fn_sub_4ACE70_004ace70);
                    }
                    charge(19);
                    a0 = addiu(s3, 48);
                    a1 = addiu(sp, 128);
                    a2 = 0x10;
                    jal(0x4AFEC8u, gen::fn_memcpy_00521250);
                    a0 = addiu(s3, 72);
                    a1 = s2;
                    a2 = 0x10;
                    jal(0x4AFED8u, gen::fn_memcpy_00521250);
                    a0 = addiu(s3, 24);
                    a1 = s1;
                    a2 = 0x10;
                    jal(0x4AFEE8u, gen::fn_memcpy_00521250);
                    a0 = s3;
                    a1 = s0;
                    a2 = 0x10;
                    jal(0x4AFEF8u, gen::fn_memcpy_00521250);
                    s4 = addiu(s4, 12);
                    if (s4 == s6) break;
                    backedge();
                }
                charge(2);
            }
            backedge();
        }
        charge(2);
        jal(0x4AFDBCu, gen::fn_sub_4AAD50_004aad50);
    }
    charge(2);
    v0 = s5;
    charge(10);
    ra = ld(sp + 112);
    lq(s6, sp + 96);
    lq(s5, sp + 80);
    lq(s4, sp + 64);
    lq(s3, sp + 48);
    lq(s2, sp + 32);
    lq(s1, sp + 16);
    lq(s0, sp);
    sp = addiu(sp, 240);
}

}  // namespace detail
}  // namespace c3

// --- the host-callable entry points: the arguments go to the registers the bodies read (64-bit values as given) --
u64 sub_4C2FB0(EEContext& ctx, u64 matrix) {
    ee::core::set_gpr64(ctx, GPR_A0, matrix);
    c3::detail::Cpu(ctx).sub_4C2FB0();
    return ee::core::gpr64(ctx, GPR_V0);
}

// 0x004C33D0 sub_4C33D0 -- 500 bytes; frame 0x20: ra sp+0x0
// sub_4C33D0 [RwMatrixScale(matrix, scale, combine)]: $a0 the matrix (right +0, up +16, at +32, pos +48, flags +12),
// $a1 the scale vector. Replace: identity scaled; pre-concat: each row scaled by one component; post-concat: each
// column scaled. The flags lose 0x20003 (identity / orthonormal / normalised). A bad op: RWERROR, then the flags of
// the matrix at address 0 are updated (the retail error path continues with a0 = 0).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4C33D0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lui, hg::lw, hg::lwc1, hg::mul_s,
          hg::sd, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x004c33d0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 2;
    sd(ra, sp, 0x0);
    if (a2 == v0) {
        // 0x004c34dc: post-concat: each column scaled
        charge(ctx, 40);
        lwc1(f0, a0, rw_matrix::kRightX);
        lwc1(f3, a1, 0);
        lwc1(f2, a1, 4);
        lwc1(f1, a1, 8);
        mul_s(f0, f0, f3);
        swc1(f0, a0, rw_matrix::kRightX);
        lwc1(f0, a0, rw_matrix::kRightY);
        mul_s(f0, f0, f2);
        swc1(f0, a0, rw_matrix::kRightY);
        lwc1(f0, a0, rw_matrix::kRightZ);
        mul_s(f0, f0, f1);
        swc1(f0, a0, rw_matrix::kRightZ);
        lwc1(f0, a0, rw_matrix::kUpX);
        mul_s(f0, f0, f3);
        swc1(f0, a0, rw_matrix::kUpX);
        lwc1(f0, a0, rw_matrix::kUpY);
        mul_s(f0, f0, f2);
        swc1(f0, a0, rw_matrix::kUpY);
        lwc1(f0, a0, rw_matrix::kUpZ);
        mul_s(f0, f0, f1);
        swc1(f0, a0, rw_matrix::kUpZ);
        lwc1(f0, a0, rw_matrix::kAtX);
        mul_s(f0, f0, f3);
        swc1(f0, a0, rw_matrix::kAtX);
        lwc1(f0, a0, rw_matrix::kAtY);
        mul_s(f0, f0, f2);
        swc1(f0, a0, rw_matrix::kAtY);
        lwc1(f0, a0, rw_matrix::kAtZ);
        mul_s(f0, f0, f1);
        swc1(f0, a0, rw_matrix::kAtZ);
        lwc1(f0, a0, rw_matrix::kPosX);
        mul_s(f0, f0, f3);
        swc1(f0, a0, rw_matrix::kPosX);
        lwc1(f0, a0, rw_matrix::kPosY);
        mul_s(f0, f0, f2);
        swc1(f0, a0, rw_matrix::kPosY);
        lwc1(f0, a0, rw_matrix::kPosZ);
        mul_s(f0, f0, f1);
        swc1(f0, a0, rw_matrix::kPosZ);
    } else {
        // 0x004c33e0
        charge(ctx, 3);
        v0 = 1;
        if (a2 == v0) {
            // 0x004c3460: pre-concat: each row scaled by one component
            charge(ctx, 31);
            lwc1(f0, a0, rw_matrix::kRightX);
            lwc1(f3, a1, 0);
            lwc1(f2, a1, 4);
            lwc1(f1, a1, 8);
            mul_s(f0, f0, f3);
            swc1(f0, a0, rw_matrix::kRightX);
            lwc1(f0, a0, rw_matrix::kRightY);
            mul_s(f0, f0, f3);
            swc1(f0, a0, rw_matrix::kRightY);
            lwc1(f0, a0, rw_matrix::kRightZ);
            mul_s(f0, f0, f3);
            swc1(f0, a0, rw_matrix::kRightZ);
            lwc1(f0, a0, rw_matrix::kUpX);
            mul_s(f0, f0, f2);
            swc1(f0, a0, rw_matrix::kUpX);
            lwc1(f0, a0, rw_matrix::kUpY);
            mul_s(f0, f0, f2);
            swc1(f0, a0, rw_matrix::kUpY);
            lwc1(f0, a0, rw_matrix::kUpZ);
            mul_s(f0, f0, f2);
            swc1(f0, a0, rw_matrix::kUpZ);
            lwc1(f0, a0, rw_matrix::kAtX);
            mul_s(f0, f0, f1);
            swc1(f0, a0, rw_matrix::kAtX);
            lwc1(f0, a0, rw_matrix::kAtY);
            mul_s(f0, f0, f1);
            swc1(f0, a0, rw_matrix::kAtY);
            lwc1(f0, a0, rw_matrix::kAtZ);
            mul_s(f0, f0, f1);
            swc1(f0, a0, rw_matrix::kAtZ);
        } else {
            // 0x004c33ec
            charge(ctx, 2);
            if (a2 == 0) {
                // 0x004c33fc: replace: identity (flags | 0x20003) scaled
                charge(ctx, 25);
                v1 = 0x3F800000;
                v0 = 0x20000;
                sw(v1, a0, rw_matrix::kAtZ);
                lwc1(f2, a1, 0);
                sw(v1, a0, rw_matrix::kUpY);
                lwc1(f1, a1, 4);
                sw(v1, a0, rw_matrix::kRightX);
                lwc1(f0, a1, 8);
                sw(zero, a0, rw_matrix::kUpX);
                v0 = v0 | 0x3;
                sw(zero, a0, rw_matrix::kRightZ);
                sw(zero, a0, rw_matrix::kRightY);
                sw(zero, a0, rw_matrix::kAtY);
                sw(zero, a0, rw_matrix::kAtX);
                sw(zero, a0, rw_matrix::kUpZ);
                sw(zero, a0, rw_matrix::kPosZ);
                sw(zero, a0, rw_matrix::kPosY);
                sw(zero, a0, rw_matrix::kPosX);
                lw(v1, a0, rw_matrix::kFlags);
                v0 = v1 | v0;
                sw(v0, a0, rw_matrix::kFlags);
                swc1(f2, a0, rw_matrix::kRightX);
                swc1(f1, a0, rw_matrix::kUpY);
                swc1(f0, a0, rw_matrix::kAtZ);
            } else {
                // 0x004c33f4: a bad op: RWERROR(E 3, "Invalid combination type"); the flags of the matrix at 0 then
                charge(ctx, 2);
                sw(v0, sp, 0x18);
                // 0x004c357c
                charge(ctx, 9);
                a1 = hi(kStrInvalidCombination);
                v0 = lui(0x8000);
                a1 = addiu(a1, lo(kStrInvalidCombination));  // "Invalid combination type"
                a0 = v0 | 0x3;
                jal(ctx, 0x4C3588u, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x1C);
                a0 = addiu(sp, 0x18);
                jal(ctx, 0x4C3594u, gen::fn_sub_4C1C50_004c1c50);
                a0 = 0;
            }
        }
    }
    // 0x004c35a0 (the shared epilogue, written out on this path): the flags lose 0x20003; return the matrix
    charge(ctx, 9);
    lw(a1, a0, rw_matrix::kFlags);
    v0 = lui(0xFFFD);
    v1 = v0 | 0xFFFC;
    v0 = a0;
    v1 = a1 & v1;
    sw(v1, a0, rw_matrix::kFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4C33D0(EEContext& ctx, u64 matrix, u64 scale, u64 combine) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(matrix));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(scale));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(combine));
    sub_4C33D0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004C35D0 sub_4C35D0 -- 392 bytes; frame 0x20: ra sp+0x0
// sub_4C35D0 [RwMatrixTranslate(matrix, translation, combine)]: replace: identity with pos = t; pre-concat:
// pos += right * t.x + up * t.y + at * t.z (through ACC); post-concat: pos += t. The flags lose 0x20000.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4C35D0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lui, hg::lw, hg::lwc1,
          hg::madd_s, hg::madda_s, hg::mula_s, hg::sd, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6};
    // 0x004c35d0
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 2;
    sd(ra, sp, 0x0);
    if (a2 == v0) {
        // 0x004c36dc: post-concat: pos += t
        charge(ctx, 13);
        lwc1(f3, a0, rw_matrix::kPosX);
        lwc1(f0, a1, 0);
        lwc1(f2, a1, 4);
        lwc1(f1, a1, 8);
        add_s(f0, f3, f0);
        swc1(f0, a0, rw_matrix::kPosX);
        lwc1(f0, a0, rw_matrix::kPosY);
        add_s(f0, f0, f2);
        swc1(f0, a0, rw_matrix::kPosY);
        lwc1(f0, a0, rw_matrix::kPosZ);
        add_s(f0, f0, f1);
        swc1(f0, a0, rw_matrix::kPosZ);
    } else {
        // 0x004c35e0
        charge(ctx, 3);
        v0 = 1;
        if (a2 == v0) {
            // 0x004c3660: pre-concat: pos += right * t.x + up * t.y + at * t.z (through ACC)
            charge(ctx, 31);
            lwc1(f4, a1, 4);
            lwc1(f1, a0, rw_matrix::kUpX);
            lwc1(f5, a1, 0);
            lwc1(f2, a0, rw_matrix::kRightX);
            lwc1(f6, a1, 8);
            lwc1(f3, a0, rw_matrix::kAtX);
            lwc1(f0, a0, rw_matrix::kPosX);
            mula_s(f4, f1);
            madda_s(f5, f2);
            madd_s(f1, f6, f3);
            add_s(f0, f0, f1);
            swc1(f0, a0, rw_matrix::kPosX);
            lwc1(f1, a0, rw_matrix::kUpY);
            lwc1(f2, a0, rw_matrix::kRightY);
            lwc1(f3, a0, rw_matrix::kAtY);
            lwc1(f0, a0, rw_matrix::kPosY);
            mula_s(f4, f1);
            madda_s(f5, f2);
            madd_s(f1, f6, f3);
            add_s(f0, f0, f1);
            swc1(f0, a0, rw_matrix::kPosY);
            lwc1(f1, a0, rw_matrix::kUpZ);
            lwc1(f2, a0, rw_matrix::kRightZ);
            lwc1(f3, a0, rw_matrix::kAtZ);
            lwc1(f0, a0, rw_matrix::kPosZ);
            mula_s(f4, f1);
            madda_s(f5, f2);
            madd_s(f1, f6, f3);
            add_s(f0, f0, f1);
            swc1(f0, a0, rw_matrix::kPosZ);
        } else {
            // 0x004c35ec
            charge(ctx, 2);
            if (a2 == 0) {
                // 0x004c35fc: replace: identity with pos = t
                charge(ctx, 25);
                v1 = 0x3F800000;
                v0 = 0x20000;
                sw(v1, a0, rw_matrix::kAtZ);
                lwc1(f2, a1, 0);
                sw(v1, a0, rw_matrix::kUpY);
                lwc1(f1, a1, 4);
                sw(v1, a0, rw_matrix::kRightX);
                lwc1(f0, a1, 8);
                sw(zero, a0, rw_matrix::kUpX);
                v0 = v0 | 0x3;
                sw(zero, a0, rw_matrix::kRightZ);
                sw(zero, a0, rw_matrix::kRightY);
                sw(zero, a0, rw_matrix::kAtY);
                sw(zero, a0, rw_matrix::kAtX);
                sw(zero, a0, rw_matrix::kUpZ);
                sw(zero, a0, rw_matrix::kPosZ);
                sw(zero, a0, rw_matrix::kPosY);
                sw(zero, a0, rw_matrix::kPosX);
                lw(v1, a0, rw_matrix::kFlags);
                v0 = v1 | v0;
                sw(v0, a0, rw_matrix::kFlags);
                swc1(f2, a0, rw_matrix::kPosX);
                swc1(f1, a0, rw_matrix::kPosY);
                swc1(f0, a0, rw_matrix::kPosZ);
            } else {
                // 0x004c35f4: a bad op: RWERROR(E 3, "Invalid combination type"); the flags of the matrix at 0 then
                charge(ctx, 2);
                sw(v0, sp, 0x18);
                // 0x004c3710
                charge(ctx, 9);
                a1 = hi(kStrInvalidCombination);
                v0 = lui(0x8000);
                a1 = addiu(a1, lo(kStrInvalidCombination));  // "Invalid combination type"
                a0 = v0 | 0x3;
                jal(ctx, 0x4C371Cu, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0x1C);
                a0 = addiu(sp, 0x18);
                jal(ctx, 0x4C3728u, gen::fn_sub_4C1C50_004c1c50);
                a0 = 0;
            }
        }
    }
    // 0x004c3734 (the shared epilogue, written out on this path): the flags lose 0x20000; return the matrix
    charge(ctx, 9);
    lw(a1, a0, rw_matrix::kFlags);
    v0 = lui(0xFFFD);
    v1 = v0 | 0xFFFF;
    v0 = a0;
    v1 = a1 & v1;
    sw(v1, a0, rw_matrix::kFlags);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4C35D0(EEContext& ctx, u64 matrix, u64 translation, u64 combine) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(matrix));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(translation));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(combine));
    sub_4C35D0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004C3760 sub_4C3760 -- 288 bytes; frame 0xB0: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4C3760 [RwMatrixTransform(matrix, transform, combine)]: replace: copy; pre-concat: matrix = transform x
// matrix; post-concat: matrix = matrix x transform (sub_4C2F30 into a 64-byte frame buffer, then copied back).
// Returns the matrix (0 after RWERROR for a bad op).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4C3760(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::jal, hg::ld, hg::lq, hg::lui, hg::lw,
          hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c3760
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    v0 = 2;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;  // s0 = the matrix
    if (a2 == v0) {
        // 0x004c3804: post-concat: sp+0x20 = matrix x transform, copied back (8 x 2 words)
        charge(ctx, 7);
        a2 = a1;
        a0 = addiu(sp, 0x20);
        a1 = s0;
        jal(ctx, 0x4C380Cu, gen::fn_sub_4C2F30_004c2f30);
        a2 = addiu(sp, 0x20);
        a0 = 8;
        a1 = s0;
        for (;;) {
            // 0x004c3820
            charge(ctx, 8);
            lw(v1, a2, 0);
            a0 = addiu(a0, -1);
            lw(v0, a2, 4);
            sw(v1, a1, 0);
            a2 = addiu(a2, 8);
            sw(v0, a1, 4);
            a1 = addiu(a1, 8);
            if (i64(a0) <= 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004c3840
        charge(ctx, 2);
        // 0x004c386c: return the matrix
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x004c3778
        charge(ctx, 3);
        v0 = 1;
        if (a2 == v0) {
            // 0x004c37c4: pre-concat: sp+0x60 = transform x matrix, copied back
            charge(ctx, 6);
            a0 = addiu(sp, 0x60);
            a2 = s0;
            jal(ctx, 0x4C37C8u, gen::fn_sub_4C2F30_004c2f30);
            a2 = addiu(sp, 0x60);
            a0 = 8;
            a1 = s0;
            for (;;) {
                // 0x004c37dc
                charge(ctx, 8);
                lw(v1, a2, 0);
                a0 = addiu(a0, -1);
                lw(v0, a2, 4);
                sw(v1, a1, 0);
                a2 = addiu(a2, 8);
                sw(v0, a1, 4);
                a1 = addiu(a1, 8);
                if (i64(a0) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004c37fc
            charge(ctx, 2);
            // 0x004c386c (written out on this path): return the matrix
            charge(ctx, 1);
            v0 = s0;
        } else {
            // 0x004c3784
            charge(ctx, 2);
            if (a2 != 0) {
                // 0x004c378c: a bad op: RWERROR(E 3, "Invalid combination type"); return 0
                charge(ctx, 2);
                sw(v0, sp, 0xA8);
                // 0x004c3848
                charge(ctx, 9);
                a1 = hi(kStrInvalidCombination);
                v0 = lui(0x8000);
                a1 = addiu(a1, lo(kStrInvalidCombination));  // "Invalid combination type"
                a0 = v0 | 0x3;
                jal(ctx, 0x4C3854u, gen::fn_sub_4C1D10_004c1d10);
                sw(v0, sp, 0xAC);
                a0 = addiu(sp, 0xA8);
                jal(ctx, 0x4C3860u, gen::fn_sub_4C1C50_004c1c50);
                s0 = 0;
                // 0x004c386c (written out on this path)
                charge(ctx, 1);
                v0 = s0;
            } else {
                // 0x004c3794: replace: copy the transform (8 x 2 words)
                charge(ctx, 2);
                a0 = 8;
                a2 = s0;
                for (;;) {
                    // 0x004c379c
                    charge(ctx, 8);
                    lw(v1, a1, 0);
                    a0 = addiu(a0, -1);
                    lw(v0, a1, 4);
                    sw(v1, a2, 0);
                    sw(v0, a2, 4);
                    a1 = addiu(a1, 8);
                    a2 = addiu(a2, 8);
                    if (i64(a0) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004c37bc
                charge(ctx, 2);
                v0 = s0;
            }
        }
    }
    // 0x004c3870 (the shared epilogue)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xB0);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4C3760(EEContext& ctx, u64 matrix, u64 transform, u64 combine) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(matrix));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(transform));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(combine));
    sub_4C3760(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_4C6BE0(EEContext& ctx, u64 out, u64 points, u64 count, u64 matrix) {
    ee::core::set_gpr64(ctx, GPR_A0, out);
    ee::core::set_gpr64(ctx, GPR_A1, points);
    ee::core::set_gpr64(ctx, GPR_A2, count);
    ee::core::set_gpr64(ctx, GPR_A3, matrix);
    c3::detail::Cpu(ctx).sub_4C6BE0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_4C6C60(EEContext& ctx, u64 out, u64 vectors, u64 count, u64 matrix) {
    ee::core::set_gpr64(ctx, GPR_A0, out);
    ee::core::set_gpr64(ctx, GPR_A1, vectors);
    ee::core::set_gpr64(ctx, GPR_A2, count);
    ee::core::set_gpr64(ctx, GPR_A3, matrix);
    c3::detail::Cpu(ctx).sub_4C6C60();
    return ee::core::gpr64(ctx, GPR_V0);
}

// 0x004C6D60 sub_4C6D60 -- 144 bytes; leaf frame (no stack)
// sub_4C6D60 [split a free block]: $a0 the block header, $a1 the size to keep. A new free header is made at
// a0 + a1 + 32 and linked after it; the remainder size goes to the new header, the block keeps a1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4C6D60(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::nor, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x004c6d60
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(a2, a0, heap_block::kNext);  // a2 = the next block
    v1 = addu(a0, a1);
    a3 = addiu(v1, heap_block::kHeaderSize);  // a3 = the new free header after the kept bytes
    do {
        if (a2 != 0) {
            // 0x004c6d70: a free next block?
            charge(ctx, 5);
            lw(v1, a2, heap_block::kUsed);
            v1 = nor(v1, 0);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                // 0x004c6d84: the new block absorbs it: its next, the remainder plus the next block's size
                charge(ctx, 8);
                lw(v1, a2, heap_block::kNext);
                sw(v1, a3, heap_block::kNext);
                lw(v1, a0, heap_block::kNext);
                lw(a2, a0, heap_block::kSize);
                lw(v1, v1, heap_block::kSize);
                a2 = subu(a2, a1);
                v1 = addu(v1, a2);
                sw(v1, a3, heap_block::kSize);
                break;
            }
        }
        // 0x004c6dd0: the next block stays: the remainder less its header
        charge(ctx, 6);
        sw(a2, a3, heap_block::kNext);
        lw(v1, a0, heap_block::kSize);
        v1 = subu(v1, a1);
        v1 = addiu(v1, -heap_block::kHeaderSize);
        sw(v1, a3, heap_block::kSize);
        backedge(ctx);
    } while (false);
    // 0x004c6da4: link the new block after this one, free
    charge(ctx, 6);
    sw(a3, a0, heap_block::kNext);
    sw(zero, a3, heap_block::kUsed);
    sw(a0, a3, heap_block::kPrev);
    lw(v1, a3, heap_block::kNext);
    if (v1 != 0) {
        // 0x004c6dbc
        charge(ctx, 1);
        sw(a3, v1, heap_block::kPrev);
    }
    // 0x004c6dc0: this block keeps the size; the new one the same heap
    charge(ctx, 4);
    sw(a1, a0, heap_block::kSize);
    lw(v1, a0, heap_block::kHeap);
    sw(v1, a3, heap_block::kHeap);
    // 0x004c6de8
    charge(ctx, 2);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_4C6D60(EEContext& ctx, u64 block, u64 size) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(block));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(size));
    sub_4C6D60(ctx);
}

// 0x004C6E60 sub_4C6E60 -- 208 bytes; leaf frame (no stack)
// sub_4C6E60 [free a block]: $a0 the block's data (header at a0 - 32). Marks it free, moves the heap's first-free
// hint back to it when it is earlier (or the hint is 0), and merges it with a free previous and a free next block.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4C6E60(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lw, hg::nor, hg::sltu, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x004c6e60
    enter(ctx, 9);  // entry check point + this block's cycles
    sw(zero, a0, heap_block::kUsed - heap_block::kHeaderSize);  // free
    v1 = addiu(a0, -heap_block::kHeaderSize);                    // v1 = the header
    lw(a3, a0, heap_block::kPrev - heap_block::kHeaderSize);     // a3 = the previous block
    lw(a2, a0, heap_block::kNext - heap_block::kHeaderSize);     // a2 = the next block
    lw(a0, a0, heap_block::kHeap - heap_block::kHeaderSize);     // the heap
    a1 = addiu(a0, res_heap::kHint);                             // a1 = &heap->hint
    lw(a0, a0, res_heap::kHint);
    do {
        if (a0 != 0) {
            // 0x004c6e84: a hint after this block?
            charge(ctx, 3);
            a0 = sltu(v1, a0);
            if (a0 == 0) {
                break;
            }
        }
        // 0x004c6f20: the hint moves back to this block
        charge(ctx, 2);
        sw(v1, a1, 0);
        backedge(ctx);
    } while (false);
    // 0x004c6e90: merge into a free previous block
    charge(ctx, 2);
    if (a3 != 0) {
        // 0x004c6e98
        charge(ctx, 5);
        lw(a0, a3, heap_block::kUsed);
        a0 = nor(a0, 0);
        a0 = a0 & 0x1;
        if (a0 != 0) {
            // 0x004c6eac
            charge(ctx, 2);
            sw(a2, a3, heap_block::kNext);
            if (a2 != 0) {
                // 0x004c6eb4
                charge(ctx, 1);
                sw(a3, a2, heap_block::kPrev);
            }
            // 0x004c6eb8
            charge(ctx, 6);
            lw(v1, v1, heap_block::kSize);
            lw(a0, a3, heap_block::kSize);
            a1 = addiu(v1, 32);
            a0 = addu(a0, a1);
            v1 = a3;
            sw(a0, a3, heap_block::kSize);
        }
    }
    // 0x004c6ed0
    charge(ctx, 2);
    if (a2 != 0) {
        // 0x004c6ed8
        charge(ctx, 5);
        lw(a0, a2, heap_block::kUsed);
        a0 = nor(a0, 0);
        a0 = a0 & 0x1;
        if (a0 != 0) {
            // 0x004c6eec
            charge(ctx, 5);
            lw(a0, a2, heap_block::kNext);
            sw(a0, v1, heap_block::kNext);
            lw(a0, a2, heap_block::kNext);
            if (a0 != 0) {
                // 0x004c6f00
                charge(ctx, 1);
                sw(v1, a0, heap_block::kPrev);
            }
            // 0x004c6f04
            charge(ctx, 7);
            lw(a1, a2, heap_block::kSize);
            lw(a0, v1, heap_block::kSize);
            a1 = addiu(a1, 32);
            a0 = addu(a0, a1);
            sw(a0, v1, heap_block::kSize);
        }
    }
    // 0x004c6f28 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_4C6E60(EEContext& ctx, u64 data) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(data));
    sub_4C6E60(ctx);
}

// 0x004C6F30 sub_4C6F30 -- 240 bytes; frame 0x10: ra sp+0x0
// sub_4C6F30 [allocate from the resource heap]: $a0 the heap, $a1 the size (rounded up to 32). First fit from the
// hint (+4); a block more than 64 bytes larger is split (sub_4C6D60); when the block was the hint, the hint moves to
// the next free block. Marks the block used and returns its data (header + 32), or 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4C6F30(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lw, hg::nor, hg::sd, hg::si,
          hg::sltu, hg::sw;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c6f30
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = a0;
    sd(ra, sp, 0x0);
    v1 = addiu(a1, 31);
    lw(a2, a0, res_heap::kHint);
    v0 = si(-32);
    a1 = v1 & v0;
    a0 = 0;
    for (;;) {
        // 0x004c6f50
        charge(ctx, 4);
        v0 = sltu(0, a2);
        v0 = v0 ^ 0x1;
        if (v0 == 0) {
            // 0x004c6f60
            charge(ctx, 2);
            if (a0 == 0) {
                // 0x004c6f68
                charge(ctx, 5);
                lw(v0, a2, heap_block::kUsed);
                v0 = nor(v0, 0);
                v0 = v0 & 0x1;
                if (v0 != 0) {
                    // 0x004c6f7c
                    charge(ctx, 4);
                    lw(v0, a2, heap_block::kSize);
                    v0 = sltu(v0, a1);
                    if (v0 == 0) {
                        // 0x004c6f8c
                        charge(ctx, 1);
                        a0 = a2;
                    }
                }
                // 0x004c6f90
                charge(ctx, 2);
                lw(a2, a2, heap_block::kNext);
                backedge(ctx);
                continue;
            }
        }
        break;
    }
    // 0x004c6f98
    charge(ctx, 2);
    if (a0 == 0) {
        // 0x004c6fd0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004c6fa0
        charge(ctx, 5);
        lw(v1, a0, heap_block::kSize);
        v0 = addiu(a1, 64);
        at = sltu(v0, v1);
        if (at != 0) {
            // 0x004c6fd8
            charge(ctx, 4);
            jal(ctx, 0x4C6FD8u, gen::fn_sub_4C6D60_004c6d60);
            lw(v1, t0, res_heap::kHint);
            backedge(ctx);
        } else {
            // 0x004c6fb4
            charge(ctx, 1);
            lw(v1, t0, res_heap::kHint);
        }
        // 0x004c6fb8
        charge(ctx, 2);
        if (a0 == v1) {
            // the block was the hint: the hint moves on to the next free block
            for (;;) {
                // 0x004c6fe8
                charge(ctx, 5);
                lw(v0, v1, heap_block::kNext);
                sw(v0, t0, res_heap::kHint);
                lw(v1, t0, res_heap::kHint);
                if (v1 == 0) {
                    backedge(ctx);
                    // 0x004c6fc0 (written out on this path): none left
                    charge(ctx, 1);
                    v1 = 1;
                    break;
                }
                // 0x004c6ffc
                charge(ctx, 4);
                lw(v0, v1, heap_block::kUsed);
                v0 = v0 & 0x1;
                if (v0 == 0) {
                    // 0x004c700c: a free one
                    charge(ctx, 2);
                    v1 = 1;
                    backedge(ctx);
                    break;
                }
                backedge(ctx);
            }
        } else {
            // 0x004c6fc0
            charge(ctx, 1);
            v1 = 1;
        }
        // 0x004c6fc4: mark it used; return its data
        charge(ctx, 3);
        v0 = addiu(a0, 32);
        sw(v1, a0, heap_block::kUsed);
    }
    // 0x004c7014 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4C6F30(EEContext& ctx, u64 heap, u64 size) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(heap));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(size));
    sub_4C6F30(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004C9D00 RwCameraEndUpdate -- 12 bytes; leaf frame (no stack)
// RwCameraEndUpdate(camera): a `jr` tail call through camera +28 (CameraEndUpdate).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void RwCameraEndUpdate(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::tail;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004c9d00
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, rw_camera::kEndUpdate);
    tail(ctx, v0.u());  // jr: the target's entry point
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 RwCameraEndUpdate(EEContext& ctx, u64 camera) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(camera));
    RwCameraEndUpdate(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004C9D10 RwCameraBeginUpdate -- 12 bytes; leaf frame (no stack)
// RwCameraBeginUpdate(camera): a `jr` tail call through camera +24 (CameraBeginUpdate).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void RwCameraBeginUpdate(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::tail;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004c9d10
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, rw_camera::kBeginUpdate);
    tail(ctx, v0.u());  // jr: the target's entry point
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 RwCameraBeginUpdate(EEContext& ctx, u64 camera) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(camera));
    RwCameraBeginUpdate(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 RwCameraClear(EEContext& ctx, u64 camera, u64 colour, u64 mode) {
    ee::core::set_gpr64(ctx, GPR_A0, camera);
    ee::core::set_gpr64(ctx, GPR_A1, colour);
    ee::core::set_gpr64(ctx, GPR_A2, mode);
    c3::detail::Cpu(ctx).RwCameraClear();
    return ee::core::gpr64(ctx, GPR_V0);
}

// 0x004C9ED0 RwCameraShowRaster -- 48 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// RwCameraShowRaster(camera, dev, flags): RwRasterShowRaster(camera +96 = the frame buffer, dev, flags); returns the
// camera or 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void RwCameraShowRaster(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::call, hg::enter, hg::ld, hg::link, hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004c9ed0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    link(ctx, 0x4C9EE0u);  // $ra first: the delay slot below depends on it
    lw(a0, a0, rw_camera::kRaster);
    call(ctx, gen::fn_RwRasterShowRaster_004cdfe0);
    if (v0 == 0) s0 = 0;
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 RwCameraShowRaster(EEContext& ctx, u64 camera, u64 dev, u64 flags) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(camera));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(dev));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(flags));
    RwCameraShowRaster(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004CB2F0 sub_4CB2F0 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4CB2F0 [RwFrameGetLTM(frame)]: when the hierarchy root (frame +160) has its "dirty" bit (root +3 bit 0),
// sub_4CF4C0(root) brings the LTMs up to date; returns frame + 80 (the LTM).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4CB2F0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cb2f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, rw_frame::kRoot);
    lbu(v0, a0, rw_frame::kDirty);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        // 0x004cb31c
        charge(ctx, 4);
        jal(ctx, 0x4CB31Cu, gen::fn_sub_4CF4C0_004cf4c0);
        backedge(ctx);
    }
    // 0x004cb314
    charge(ctx, 2);
    v0 = addiu(s0, rw_frame::kLtm);
    // 0x004cb32c
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4CB2F0(EEContext& ctx, u64 frame) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(frame));
    sub_4CB2F0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004CB7F0 sub_4CB7F0 -- 148 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4CB7F0 [RwFrameTransform-like: matrix + mark dirty]: sub_4C3760(frame +16 the modelling matrix, $a1, $a2);
// a root not yet dirty (root +3 & 3 == 0) is linked at the head of the dirty-frame list (0x96012C, through root +8);
// then root +3 |= 3 and frame +3 |= 0xC. Returns the frame.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4CB7F0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq, hg::lw, hg::sb,
          hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cb7f0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = addiu(s0, rw_frame::kMatrix);
    jal(ctx, 0x4CB800u, gen::fn_sub_4C3760_004c3760);
    lw(v1, s0, rw_frame::kRoot);
    lbu(a1, v1, rw_frame::kDirty);
    v0 = a1 & 0x3;
    if (v0 == 0) {
        // 0x004cb83c
        charge(ctx, 14);
        a0 = hi(kDirtyFrames);
        a0 = addiu(a0, lo(kDirtyFrames));
        lw(v0, a0, 0);  // 0x96012C
        sw(v0, v1, rw_frame::kDirtyLink);
        lw(v0, s0, rw_frame::kRoot);
        sw(a0, v0, rw_frame::kDirtyLink + 4);
        lw(v1, s0, rw_frame::kRoot);
        lw(v0, a0, 0);  // 0x96012C
        v1 = addiu(v1, 8);
        sw(v1, v0, 4);
        lw(v0, s0, rw_frame::kRoot);
        v0 = addiu(v0, 8);
        sw(v0, a0, 0);  // 0x96012C
        backedge(ctx);
    }
    // 0x004cb81c
    charge(ctx, 8);
    lw(v1, s0, rw_frame::kRoot);
    a0 = a1 | 0x3;
    v0 = s0;
    sb(a0, v1, rw_frame::kDirty);
    lbu(v1, s0, rw_frame::kDirty);
    v1 = v1 | 0xC;
    sb(v1, s0, rw_frame::kDirty);
    // 0x004cb874
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4CB7F0(EEContext& ctx, u64 frame, u64 transform, u64 combine) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(frame));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(transform));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(combine));
    sub_4CB7F0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_4CDC70(EEContext& ctx, u64 raster, u64 image) {
    ee::core::set_gpr64(ctx, GPR_A0, raster);
    ee::core::set_gpr64(ctx, GPR_A1, image);
    c3::detail::Cpu(ctx).sub_4CDC70();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_4CDCE0(EEContext& ctx, u64 image, u64 raster) {
    ee::core::set_gpr64(ctx, GPR_A0, image);
    ee::core::set_gpr64(ctx, GPR_A1, raster);
    c3::detail::Cpu(ctx).sub_4CDCE0();
    return ee::core::gpr64(ctx, GPR_V0);
}

// 0x004CDD50 sub_4CDD50 -- 168 bytes; frame 0xA0: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4CDD50 [RwImageFindRasterFormat-like (image, type, &width, &height, &depth, &format)]: standard function 9
// (0x9600DC) fills a raster template in the 160-byte frame (sp + 96); on success width / height / depth (+12 / +16
// / +20) and the format (+32 | +35 << 8) are stored through the four pointers ($a2, $a3, $t0, $t1). Returns the
// image or 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4CDD50(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jalr, hg::lbu, hg::ld, hg::lq, hg::lw, hg::sd, hg::sll,
          hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cdd50
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    v0 = hi(kDeviceStd + 4 * 9);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    s4 = a0;
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    a2 = a1;
    sq(s0, sp, 0x0);
    s2 = a3;
    lw(v0, v0, lo(kDeviceStd + 4 * 9));
    s1 = t0;
    s0 = t1;
    a0 = addiu(sp, 0x60);
    a1 = s4;
    jalr(ctx, 0x4CDD90u, v0.u());
    if (v0 != 0) {
        // 0x004cdda8
        charge(ctx, 12);
        lbu(a0, sp, 0x83);
        v0 = s4;
        lbu(v1, sp, 0x80);
        a0 = sll(a0, 8);
        v1 = a0 | v1;
        sw(v1, s0, 0);
        lw(v1, sp, 0x6C);
        sw(v1, s3, 0);
        lw(v1, sp, 0x70);
        sw(v1, s2, 0);
        lw(v1, sp, 0x74);
        sw(v1, s1, 0);
    } else {
        // 0x004cdda0
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004cddd8 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4CDD50(EEContext& ctx, u64 image, u64 type, u64 width, u64 height, u64 depth, u64 format) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(image));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(type));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(width));
    ee::core::set_gpr64(ctx, GPR_A3, static_cast<u64>(height));
    ee::core::set_gpr64(ctx, GPR_T0, static_cast<u64>(depth));
    ee::core::set_gpr64(ctx, GPR_T1, static_cast<u64>(format));
    sub_4CDD50(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_4CDE00(EEContext& ctx, u64 raster) {
    ee::core::set_gpr64(ctx, GPR_A0, raster);
    c3::detail::Cpu(ctx).sub_4CDE00();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 RwRasterShowRaster(EEContext& ctx, u64 raster, u64 dev, u64 flags) {
    ee::core::set_gpr64(ctx, GPR_A0, raster);
    ee::core::set_gpr64(ctx, GPR_A1, dev);
    ee::core::set_gpr64(ctx, GPR_A2, flags);
    c3::detail::Cpu(ctx).RwRasterShowRaster();
    return ee::core::gpr64(ctx, GPR_V0);
}

// 0x004CE050 sub_4CE050 -- 156 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4CE050 [RwRasterSubRaster(raster, parent, rect)]: only for a raster without its own pixels (+33 bit 7):
// width / height from rect +8 / +12, the offsets (+28 / +30, s16) = the parent's + rect x / y, then the device's
// sub-raster standard function (0x9600E8) as fn(raster, parent, 0); on success raster +0 = parent +0. Returns the
// raster or 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4CE050(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jalr, hg::lbu, hg::ld, hg::lh, hg::lq, hg::lw,
          hg::sd, hg::sh, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ce050
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    lbu(v0, a0, rw_raster::kCacheByte);
    v0 = v0 & 0x80;
    s0 = a1;
    if (v0 != 0) {
        // 0x004ce07c
        charge(ctx, 18);
        lw(v1, a2, rect::kW);
        v0 = hi(kDeviceStd + 4 * 12);
        sw(v1, s1, rw_raster::kWidth);
        lw(v1, a2, rect::kH);
        sw(v1, s1, rw_raster::kHeight);
        lh(a3, s0, rw_raster::kOffsetX);
        lh(v1, a2, rect::kX);
        v1 = addu(a3, v1);
        sh(v1, s1, rw_raster::kOffsetX);
        lh(v1, a2, rect::kY);
        lh(a3, s0, rw_raster::kOffsetY);
        v1 = addu(a3, v1);
        sh(v1, s1, rw_raster::kOffsetY);
        lw(v0, v0, lo(kDeviceStd + 4 * 12));
        a2 = 0;
        jalr(ctx, 0x4CE0B4u, v0.u());
        if (v0 != 0) {
            // 0x004ce0cc
            charge(ctx, 3);
            lw(v1, s0, rw_raster::kParent);
            v0 = s1;
            sw(v1, s1, rw_raster::kParent);
        } else {
            // 0x004ce0c4
            charge(ctx, 2);
            v0 = 0;
        }
    } else {
        // 0x004ce074
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x004ce0d8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4CE050(EEContext& ctx, u64 raster, u64 parent, u64 rect) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(raster));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(parent));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(rect));
    sub_4CE050(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_4CE200(EEContext& ctx, u64 raster, u64 level, u64 flags) {
    ee::core::set_gpr64(ctx, GPR_A0, raster);
    ee::core::set_gpr64(ctx, GPR_A1, level);
    ee::core::set_gpr64(ctx, GPR_A2, flags);
    c3::detail::Cpu(ctx).sub_4CE200();
    return ee::core::gpr64(ctx, GPR_V0);
}

// 0x004CF3B0 sub_4CF3B0 -- 268 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4CF3B0 [_rwFrameSyncHierarchyLTM: siblings and children]: $a0 a frame, $a1 the inherited dirty flags. For the
// frame and each sibling (+156): flags |= +3; with bit 2 the LTM is rebuilt from the parent; then every child (+152)
// gets the same treatment one level down (the grandchildren through a recursive call).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void sub_4CF3B0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq, hg::lw, hg::sb,
          hg::sd, hg::si, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cf3b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    if (s1 != 0) {
        for (;;) {
            // 0x004cf3dc: each frame of the sibling chain: flags |= its own
            charge(ctx, 5);
            lbu(v1, s1, rw_frame::kDirty);
            s3 = s0 | v1;
            v1 = s3 & 0x4;
            s2 = addiu(s1, 3);
            if (v1 != 0) {
                // 0x004cf448: dirty: LTM = modelling matrix x the parent's LTM (sub_4C2F30)
                charge(ctx, 10);
                lw(v0, s1, rw_frame::kParent);
                a0 = addiu(s1, 80);
                a1 = addiu(s1, 16);
                a2 = addiu(v0, 80);
                jal(ctx, 0x4CF454u, gen::fn_sub_4C2F30_004c2f30);
                lbu(a0, s2, 0);
                v1 = si(-5);
                v1 = a0 & v1;
                sb(v1, s1, rw_frame::kDirty);
                backedge(ctx);
            }
            // 0x004cf3f0: its children, one level down
            charge(ctx, 3);
            lw(s5, s1, rw_frame::kChild);
            if (s5 != 0) {
                // 0x004cf3fc
                charge(ctx, 1);
                for (;;) {
                    // 0x004cf400: a child: flags |= its own
                    charge(ctx, 5);
                    lbu(v0, s5, rw_frame::kDirty);
                    s4 = s3 | v0;
                    v0 = s4 & 0x4;
                    s2 = addiu(s5, 3);
                    if (v0 != 0) {
                        // 0x004cf470: dirty: its LTM from its parent's
                        charge(ctx, 10);
                        lw(v0, s5, rw_frame::kParent);
                        a0 = addiu(s5, 80);
                        a1 = addiu(s5, 16);
                        a2 = addiu(v0, 80);
                        jal(ctx, 0x4CF47Cu, gen::fn_sub_4C2F30_004c2f30);
                        lbu(v1, s2, 0);
                        v0 = si(-5);
                        v0 = v1 & v0;
                        sb(v0, s5, rw_frame::kDirty);
                        backedge(ctx);
                    } else {
                        // 0x004cf414
                        charge(ctx, 1);
                    }
                    // 0x004cf418: its children through a recursive call
                    charge(ctx, 6);
                    lw(a0, s5, rw_frame::kChild);
                    a1 = s4;
                    jal(ctx, 0x4CF41Cu, gen::fn_sub_4CF3B0_004cf3b0);
                    lw(s5, s5, rw_frame::kSibling);
                    if (s5 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004cf430: the next sibling
            charge(ctx, 3);
            lw(s1, s1, rw_frame::kSibling);
            if (s1 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004cf43c
        charge(ctx, 1);
    }
    // 0x004cf440
    charge(ctx, 2);
    // 0x004cf498
    charge(ctx, 9);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_4CF3B0(EEContext& ctx, u64 frame, u64 flags) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(frame));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(flags));
    sub_4CF3B0(ctx);
}

// 0x004CF4C0 sub_4CF4C0 -- 248 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4CF4C0 [_rwFrameSyncHierarchyLTM(root)]: a dirty root (+3 bit 2) copies its modelling matrix into its LTM;
// each child gets its LTM rebuilt when dirty, then its own children through sub_4CF3B0; finally root +3 &= ~5.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void sub_4CF4C0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::jal, hg::lbu, hg::ld, hg::lq, hg::lw,
          hg::sb, hg::sd, hg::si, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004cf4c0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lbu(s1, a0, rw_frame::kDirty);
    v1 = s1 & 0x4;
    s4 = a0;
    if (v1 != 0) {
        // 0x004cf538: a dirty root: LTM = its modelling matrix (8 x 2 words)
        charge(ctx, 3);
        a3 = addiu(s4, 16);
        a2 = addiu(s4, 80);
        a1 = 8;
        for (;;) {
            // 0x004cf544
            charge(ctx, 8);
            lw(a0, a3, 0);
            a1 = addiu(a1, -1);
            lw(v1, a3, 4);
            sw(a0, a2, 0);
            a3 = addiu(a3, 8);
            sw(v1, a2, 4);
            a2 = addiu(a2, 8);
            if (i64(a1) <= 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x004cf564
        charge(ctx, 2);
        lw(s3, s4, rw_frame::kChild);
        backedge(ctx);
    } else {
        // 0x004cf4ec
        charge(ctx, 1);
        lw(s3, s4, rw_frame::kChild);
    }
    // 0x004cf4f0: each child
    charge(ctx, 2);
    if (s3 != 0) {
        for (;;) {
            // 0x004cf4f8: flags |= its own
            charge(ctx, 5);
            lbu(v0, s3, rw_frame::kDirty);
            s2 = s1 | v0;
            v0 = s2 & 0x4;
            s0 = addiu(s3, 3);
            if (v0 != 0) {
                // 0x004cf56c: dirty: its LTM from the root's
                charge(ctx, 10);
                lw(v0, s3, rw_frame::kParent);
                a0 = addiu(s3, 80);
                a1 = addiu(s3, 16);
                a2 = addiu(v0, 80);
                jal(ctx, 0x4CF578u, gen::fn_sub_4C2F30_004c2f30);
                lbu(v1, s0, 0);
                v0 = si(-5);
                v0 = v1 & v0;
                sb(v0, s3, rw_frame::kDirty);
                backedge(ctx);
            } else {
                // 0x004cf50c
                charge(ctx, 1);
            }
            // 0x004cf510: its children through sub_4CF3B0
            charge(ctx, 6);
            lw(a0, s3, rw_frame::kChild);
            a1 = s2;
            jal(ctx, 0x4CF514u, gen::fn_sub_4CF3B0_004cf3b0);
            lw(s3, s3, rw_frame::kSibling);
            if (s3 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004cf528: root +3 &= ~5
    charge(ctx, 4);
    v1 = si(-6);
    v1 = s1 & v1;
    sb(v1, s4, rw_frame::kDirty);
    // 0x004cf598
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_4CF4C0(EEContext& ctx, u64 root) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(root));
    sub_4CF4C0(ctx);
}
u64 sub_4D0FD0(EEContext& ctx, u64 texture, u64 name) {
    ee::core::set_gpr64(ctx, GPR_A0, texture);
    ee::core::set_gpr64(ctx, GPR_A1, name);
    c3::detail::Cpu(ctx).sub_4D0FD0();
    return ee::core::gpr64(ctx, GPR_V0);
}
u64 sub_4D13E0(EEContext& ctx, u64 a, u64 b, u64 c) {
    ee::core::set_gpr64(ctx, GPR_A0, a);
    ee::core::set_gpr64(ctx, GPR_A1, b);
    ee::core::set_gpr64(ctx, GPR_A2, c);
    c3::detail::Cpu(ctx).sub_4D13E0();
    return ee::core::gpr64(ctx, GPR_V0);
}

// 0x004C2330 sub_4C2330 -- 1328 bytes; frame 0x40
// sub_4C2330 [RwMatrixOrthoNormalize(dst, src)]: the right / up / at rows of `src` normalised (a zero length keeps
// the row), then the row most orthogonal to the other two (the smallest absolute dot product, with zero-length rows
// rebuilt first) is replaced by the cross product of the other two (normalised), and the third by the cross of that
// and the first; pos copied. The rows live in the 64-byte frame: right sp+48, up sp+32, at sp+16, pos sp+0. dst flags
// (+12) get bits 0..1 and lose 0x20000.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: frame/spills (own frame)).
void sub_4C2330(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::addiu, hg::c_le_s, hg::c_lt_s, hg::charge, hg::cond, hg::div_s,
          hg::enter, hg::lui, hg::lw, hg::lwc1, hg::madd_s, hg::madda_s, hg::msub_s, hg::mtc1, hg::mul_s, hg::mula_s,
          hg::neg_s, hg::sqrt_s, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, sp{ctx, 29};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9}, f10{ctx, 10};
    // 0x004c2330: the right row (src +0) normalised into the frame (sp+48), a zero length keeping it
    enter(ctx, 39);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    lwc1(f0, a1, 4);
    t1 = addiu(sp, 0x34);
    lwc1(f2, a1, 32);
    t0 = addiu(sp, 0x38);
    lwc1(f1, a1, 8);
    lwc1(f6, a1, 0);
    lwc1(f5, a1, 16);
    lwc1(f4, a1, 20);
    swc1(f0, sp, 0x34);
    lwc1(f0, a1, 36);
    swc1(f2, sp, 0x10);
    lwc1(f2, t1, 0);
    swc1(f1, sp, 0x38);
    lwc1(f3, a1, 24);
    lwc1(f1, a1, 40);
    swc1(f0, sp, 0x14);
    lwc1(f0, t0, 0);
    mula_s(f2, f2);
    madda_s(f6, f6);
    swc1(f5, sp, 0x20);
    swc1(f4, sp, 0x24);
    swc1(f3, sp, 0x28);
    madd_s(f0, f0, f0);
    sqrt_s(f0, f0);
    lwc1(f5, a1, 48);
    lwc1(f4, a1, 52);
    lwc1(f3, a1, 56);
    swc1(f1, sp, 0x18);
    mtc1(zero, f1);
    swc1(f6, sp, 0x30);
    swc1(f5, sp, 0x0);
    swc1(f4, sp, 0x4);
    swc1(f3, sp, 0x8);
    c_le_s(f0, f1);
    if (!cond(ctx)) {
        // 0x004c23cc
        charge(ctx, 7);
        v0 = flt(1.0f);
        mtc1(v0, f1);
        div_s(f0, f1, f0);
    }
    // 0x004c23e8: the up row (src +16) into sp+32
    charge(ctx, 24);
    a3 = addiu(sp, 0x24);
    a2 = addiu(sp, 0x28);
    lwc1(f4, a3, 0);
    lwc1(f1, sp, 0x20);
    lwc1(f3, a2, 0);
    lwc1(f7, sp, 0x30);
    lwc1(f6, t1, 0);
    lwc1(f5, t0, 0);
    mula_s(f4, f4);
    madda_s(f1, f1);
    madd_s(f1, f3, f3);
    sqrt_s(f10, f1);
    mul_s(f3, f6, f0);
    swc1(f3, t1, 0);
    mul_s(f7, f7, f0);
    mul_s(f3, f5, f0);
    mtc1(zero, f2);
    swc1(f7, sp, 0x30);
    swc1(f3, t0, 0);
    c_le_s(f10, f2);
    if (!cond(ctx)) {
        // 0x004c2448
        charge(ctx, 7);
        v0 = flt(1.0f);
        mtc1(v0, f1);
        div_s(f10, f1, f10);
    }
    // 0x004c2464: the at row (src +32) into sp+16
    charge(ctx, 24);
    a1 = addiu(sp, 0x14);
    v1 = addiu(sp, 0x18);
    lwc1(f4, a1, 0);
    lwc1(f1, sp, 0x10);
    lwc1(f3, v1, 0);
    lwc1(f6, a3, 0);
    lwc1(f7, sp, 0x20);
    lwc1(f5, a2, 0);
    mula_s(f4, f4);
    madda_s(f1, f1);
    madd_s(f1, f3, f3);
    mul_s(f3, f6, f10);
    swc1(f3, a3, 0);
    mul_s(f3, f5, f10);
    sqrt_s(f5, f1);
    mul_s(f7, f7, f10);
    mtc1(zero, f2);
    swc1(f7, sp, 0x20);
    swc1(f3, a2, 0);
    c_le_s(f5, f2);
    if (!cond(ctx)) {
        // 0x004c24c4
        charge(ctx, 7);
        v0 = flt(1.0f);
        mtc1(v0, f1);
        div_s(f5, f1, f5);
    }
    // 0x004c24e0: the row most orthogonal to the other two (the smallest absolute dot product) is rebuilt
    charge(ctx, 13);
    lwc1(f4, sp, 0x10);
    lwc1(f3, a1, 0);
    lwc1(f2, v1, 0);
    mtc1(zero, f1);
    c_le_s(f0, f1);
    mul_s(f4, f4, f5);
    mul_s(f9, f3, f5);
    mul_s(f8, f2, f5);
    swc1(f4, sp, 0x10);
    swc1(f9, a1, 0);
    swc1(f8, v1, 0);
    if (cond(ctx)) {
        // 0x004c2644
        charge(ctx, 3);
        a2 = addiu(sp, 0x20);
        a1 = addiu(sp, 0x10);
        v1 = addiu(sp, 0x30);
    } else {
        // 0x004c2514
        charge(ctx, 3);
        c_le_s(f10, f1);
        if (cond(ctx)) {
            // 0x004c2634
            charge(ctx, 4);
            a2 = addiu(sp, 0x10);
            a1 = addiu(sp, 0x30);
            v1 = addiu(sp, 0x20);
        } else {
            // 0x004c2520
            charge(ctx, 3);
            c_le_s(f5, f1);
            if (cond(ctx)) {
                // 0x004c2624
                charge(ctx, 4);
                a2 = addiu(sp, 0x30);
                a1 = addiu(sp, 0x20);
                v1 = addiu(sp, 0x10);
            } else {
                // 0x004c252c
                charge(ctx, 11);
                lwc1(f7, a3, 0);
                lwc1(f2, sp, 0x20);
                lwc1(f5, a2, 0);
                mul_s(f0, f7, f9);
                adda_s(f1, f0);
                madd_s(f0, f2, f4);
                adda_s(f1, f0);
                madd_s(f10, f5, f8);
                c_lt_s(f10, f1);
                if (cond(ctx)) {
                    // 0x004c2560
                    charge(ctx, 2);
                    neg_s(f10, f10);
                    lwc1(f6, t1, 0);
                } else {
                    // 0x004c2558
                    charge(ctx, 2);
                    lwc1(f6, t1, 0);
                }
                // 0x004c2568
                charge(ctx, 9);
                lwc1(f1, sp, 0x30);
                lwc1(f3, t0, 0);
                mtc1(zero, f0);
                mula_s(f9, f6);
                madda_s(f4, f1);
                madd_s(f4, f8, f3);
                c_lt_s(f4, f0);
                if (cond(ctx)) {
                    // 0x004c2594
                    charge(ctx, 2);
                    neg_s(f4, f4);
                    mula_s(f6, f7);
                } else {
                    // 0x004c258c
                    charge(ctx, 2);
                    mula_s(f6, f7);
                }
                // 0x004c259c
                charge(ctx, 6);
                madda_s(f1, f2);
                mtc1(zero, f1);
                madd_s(f0, f3, f5);
                c_lt_s(f0, f1);
                if (cond(ctx)) {
                    // 0x004c25bc
                    charge(ctx, 1);
                    neg_s(f0, f0);
                } else {
                    // 0x004c25b4
                    charge(ctx, 2);
                }
                // 0x004c25c0
                charge(ctx, 3);
                c_lt_s(f10, f4);
                if (!cond(ctx)) {
                    // 0x004c25f8
                    charge(ctx, 3);
                    c_lt_s(f4, f0);
                    if (!cond(ctx)) {
                        // 0x004c2614
                        charge(ctx, 4);
                        a2 = addiu(sp, 0x30);
                        a1 = addiu(sp, 0x20);
                        v1 = addiu(sp, 0x10);
                    } else {
                        // 0x004c2604
                        charge(ctx, 4);
                        a2 = addiu(sp, 0x10);
                        a1 = addiu(sp, 0x30);
                        v1 = addiu(sp, 0x20);
                    }
                } else {
                    // 0x004c25cc
                    charge(ctx, 3);
                    c_lt_s(f10, f0);
                    if (!cond(ctx)) {
                        // 0x004c25e8
                        charge(ctx, 4);
                        a2 = addiu(sp, 0x30);
                        a1 = addiu(sp, 0x20);
                        v1 = addiu(sp, 0x10);
                    } else {
                        // 0x004c25d8
                        charge(ctx, 4);
                        a2 = addiu(sp, 0x20);
                        a1 = addiu(sp, 0x10);
                        v1 = addiu(sp, 0x30);
                    }
                }
            }
        }
    }
    // 0x004c2650: the cross product of the other two (normalised) replaces it
    charge(ctx, 34);
    lwc1(f1, a2, 4);
    lwc1(f0, a1, 8);
    lwc1(f3, a2, 8);
    lwc1(f2, a1, 4);
    mtc1(zero, f4);
    mula_s(f1, f0);
    msub_s(f0, f3, f2);
    swc1(f0, v1, 0);
    lwc1(f1, a2, 8);
    lwc1(f0, a1, 0);
    lwc1(f3, a2, 0);
    lwc1(f2, a1, 8);
    mula_s(f1, f0);
    msub_s(f0, f3, f2);
    swc1(f0, v1, 4);
    lwc1(f1, a2, 0);
    lwc1(f0, a1, 4);
    lwc1(f3, a2, 4);
    lwc1(f2, a1, 0);
    mula_s(f1, f0);
    msub_s(f0, f3, f2);
    swc1(f0, v1, 8);
    lwc1(f2, v1, 4);
    lwc1(f1, v1, 0);
    lwc1(f0, v1, 8);
    mula_s(f2, f2);
    madda_s(f1, f1);
    madd_s(f0, f0, f0);
    sqrt_s(f1, f0);
    c_le_s(f1, f4);
    if (!cond(ctx)) {
        // 0x004c26d8
        charge(ctx, 7);
        v0 = flt(1.0f);
        mtc1(v0, f0);
        div_s(f1, f0, f1);
    }
    // 0x004c26f4: the third row: the cross of that and the first (normalised)
    charge(ctx, 42);
    lwc1(f0, v1, 0);
    mtc1(zero, f4);
    mul_s(f0, f0, f1);
    swc1(f0, v1, 0);
    lwc1(f0, v1, 4);
    mul_s(f0, f0, f1);
    swc1(f0, v1, 4);
    lwc1(f0, v1, 8);
    mul_s(f3, f0, f1);
    swc1(f3, v1, 8);
    lwc1(f1, v1, 4);
    lwc1(f0, a2, 8);
    lwc1(f2, a2, 4);
    mula_s(f1, f0);
    msub_s(f0, f3, f2);
    swc1(f0, a1, 0);
    lwc1(f1, v1, 8);
    lwc1(f0, a2, 0);
    lwc1(f3, v1, 0);
    lwc1(f2, a2, 8);
    mula_s(f1, f0);
    msub_s(f0, f3, f2);
    swc1(f0, a1, 4);
    lwc1(f1, v1, 0);
    lwc1(f0, a2, 4);
    lwc1(f3, v1, 4);
    lwc1(f2, a2, 0);
    mula_s(f1, f0);
    msub_s(f0, f3, f2);
    swc1(f0, a1, 8);
    lwc1(f2, a1, 4);
    lwc1(f1, a1, 0);
    lwc1(f0, a1, 8);
    mula_s(f2, f2);
    madda_s(f1, f1);
    madd_s(f0, f0, f0);
    sqrt_s(f5, f0);
    c_le_s(f5, f4);
    if (!cond(ctx)) {
        // 0x004c279c
        charge(ctx, 7);
        v0 = flt(1.0f);
        mtc1(v0, f0);
        div_s(f5, f0, f5);
    }
    // 0x004c27b8: dst flags: bits 0..1 set, 0x20000 cleared; pos copied
    charge(ctx, 42);
    lwc1(f3, a1, 0);
    v0 = lui(0xFFFD);
    v1 = v0 | 0xFFFF;
    lwc1(f2, sp, 0x0);
    v0 = a0;
    lwc1(f1, sp, 0x4);
    lwc1(f0, sp, 0x8);
    mul_s(f3, f3, f5);
    swc1(f3, a1, 0);
    lwc1(f3, a1, 4);
    mul_s(f3, f3, f5);
    swc1(f3, a1, 4);
    lwc1(f3, a1, 8);
    mul_s(f3, f3, f5);
    swc1(f3, a1, 8);
    lwc1(f5, sp, 0x30);
    lwc1(f4, sp, 0x34);
    lwc1(f3, sp, 0x38);
    swc1(f5, a0, 0);
    swc1(f4, a0, 4);
    swc1(f3, a0, 8);
    lwc1(f5, sp, 0x20);
    lwc1(f4, sp, 0x24);
    lwc1(f3, sp, 0x28);
    swc1(f5, a0, 16);
    swc1(f4, a0, 20);
    swc1(f3, a0, 24);
    lwc1(f5, sp, 0x10);
    lwc1(f4, sp, 0x14);
    lwc1(f3, sp, 0x18);
    swc1(f5, a0, 32);
    swc1(f4, a0, 36);
    swc1(f3, a0, 40);
    swc1(f2, a0, 48);
    swc1(f1, a0, 52);
    swc1(f0, a0, 56);
    lw(a1, a0, 12);
    a1 = a1 | 0x3;
    v1 = a1 & v1;
    sw(v1, a0, 12);
    sp = addiu(sp, 0x40);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4C2330(EEContext& ctx, u64 dst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(dst));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(src));
    sub_4C2330(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004CE3A0 sub_4CE3A0 -- 1524 bytes; leaf frame (no stack)
// sub_4CE3A0 [image resample: one row's box sample]: $a0 the image (+16 stride, +20 pixels, RGBA8), $a1 / $a2 the
// span [x0, x1) in 16.16, $a3 the row (16.16, integer part used), $t0 the RGBA float accumulator out. The first
// partial pixel is weighted by its covered fraction, whole pixels by 1, the last partial pixel by its fraction; the
// sum is divided by the span width (x1 - x0) / 65536. Channels are bytes / 255.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4CE3A0(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::add_s, hg::adda_s, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::cvt_s_w,
          hg::div_s, hg::enter, hg::i64, hg::lbu, hg::lw, hg::lwc1, hg::madd_s, hg::mtc1, hg::mul_s, hg::mult,
          hg::sll, hg::sra, hg::srl, hg::subu, hg::swc1;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8};
    // 0x004ce3a0
    enter(ctx, 16);  // entry check point + this block's cycles
    t1 = subu(a2, a1);
    v1 = 0x37800000;  // 1 / 65536 (16.16 to float)
    mtc1(t1, f1);
    a3 = sra(a3, 16);
    mtc1(v1, f0);
    t2 = sra(a1, 16);
    cvt_s_w(f1, f1);
    lw(v1, a0, rw_image::kStride);
    mul_s(f1, f0, f1);
    mult(t1, a3, v1);
    lw(a3, a0, rw_image::kPixels);
    v1 = sll(t2, 2);
    a3 = addu(a3, t1);
    a0 = sra(a2, 16);
    v1 = addu(a3, v1);
    if (t2 == a0) {
        // 0x004ce68c: the span inside one pixel: its channels (bytes / 255) times the span's width
        charge(ctx, 3);
        lbu(a0, v1, 0);
        if (i64(a0) < 0) {
            // 0x004ce6a4
            charge(ctx, 7);
            a1 = srl(a0, 1);
            a0 = a0 & 0x1;
            a1 = a1 | a0;
            mtc1(a1, f0);
            cvt_s_w(f2, f0);
            add_s(f2, f2, f2);
        } else {
            // 0x004ce698
            charge(ctx, 3);
            mtc1(a0, f0);
            cvt_s_w(f2, f0);
        }
        // 0x004ce6c0
        charge(ctx, 9);
        a0 = flt(0.00390625f);
        a0 = a0 | 0x8081;  // 0x3B808081: 1 / 255
        mtc1(a0, f0);
        mul_s(f0, f0, f2);
        swc1(f0, t0, rgba_f::kR);
        lbu(a0, v1, 1);
        if (i64(a0) < 0) {
            // 0x004ce6f0
            charge(ctx, 7);
            a1 = srl(a0, 1);
            a0 = a0 & 0x1;
            a1 = a1 | a0;
            mtc1(a1, f0);
            cvt_s_w(f2, f0);
            add_s(f2, f2, f2);
        } else {
            // 0x004ce6e4
            charge(ctx, 3);
            mtc1(a0, f0);
            cvt_s_w(f2, f0);
        }
        // 0x004ce70c
        charge(ctx, 9);
        a0 = flt(0.00390625f);
        a0 = a0 | 0x8081;  // 0x3B808081: 1 / 255
        mtc1(a0, f0);
        mul_s(f0, f0, f2);
        swc1(f0, t0, rgba_f::kG);
        lbu(a0, v1, 2);
        if (i64(a0) < 0) {
            // 0x004ce73c
            charge(ctx, 7);
            a1 = srl(a0, 1);
            a0 = a0 & 0x1;
            a1 = a1 | a0;
            mtc1(a1, f0);
            cvt_s_w(f2, f0);
            add_s(f2, f2, f2);
        } else {
            // 0x004ce730
            charge(ctx, 3);
            mtc1(a0, f0);
            cvt_s_w(f2, f0);
        }
        // 0x004ce758
        charge(ctx, 9);
        a0 = flt(0.00390625f);
        a0 = a0 | 0x8081;  // 0x3B808081: 1 / 255
        mtc1(a0, f0);
        mul_s(f0, f0, f2);
        swc1(f0, t0, rgba_f::kB);
        lbu(v1, v1, 3);
        if (i64(v1) < 0) {
            // 0x004ce788
            charge(ctx, 7);
            a0 = srl(v1, 1);
            v1 = v1 & 0x1;
            a0 = a0 | v1;
            mtc1(a0, f0);
            cvt_s_w(f2, f0);
            add_s(f2, f2, f2);
        } else {
            // 0x004ce77c
            charge(ctx, 3);
            mtc1(v1, f0);
            cvt_s_w(f2, f0);
        }
        // 0x004ce7a4
        charge(ctx, 18);
        v1 = flt(0.00390625f);
        v1 = v1 | 0x8081;  // 0x3B808081: 1 / 255
        mtc1(v1, f0);
        mul_s(f0, f0, f2);
        swc1(f0, t0, rgba_f::kA);
        lwc1(f0, t0, rgba_f::kR);
        mul_s(f0, f0, f1);
        swc1(f0, t0, rgba_f::kR);
        lwc1(f0, t0, rgba_f::kG);
        mul_s(f0, f0, f1);
        swc1(f0, t0, rgba_f::kG);
        lwc1(f0, t0, rgba_f::kB);
        mul_s(f0, f0, f1);
        swc1(f0, t0, rgba_f::kB);
        lwc1(f0, t0, rgba_f::kA);
        mul_s(f0, f0, f1);
        swc1(f0, t0, rgba_f::kA);
    } else {
        // 0x004ce3e0: the first, partial pixel, weighted by its covered fraction
        charge(ctx, 4);
        lbu(t1, v1, 0);
        a3 = addiu(t2, 1);
        a3 = sll(a3, 16);
        if (i64(t1) < 0) {
            // 0x004ce3fc
            charge(ctx, 7);
            t2 = srl(t1, 1);
            t1 = t1 & 0x1;
            t2 = t2 | t1;
            mtc1(t2, f0);
            cvt_s_w(f2, f0);
            add_s(f2, f2, f2);
        } else {
            // 0x004ce3f0
            charge(ctx, 3);
            mtc1(t1, f0);
            cvt_s_w(f2, f0);
        }
        // 0x004ce418
        charge(ctx, 9);
        t1 = flt(0.00390625f);
        t1 = t1 | 0x8081;  // 0x3B808081: 1 / 255
        mtc1(t1, f0);
        mul_s(f0, f0, f2);
        swc1(f0, t0, rgba_f::kR);
        lbu(t1, v1, 1);
        if (i64(t1) < 0) {
            // 0x004ce448
            charge(ctx, 7);
            t2 = srl(t1, 1);
            t1 = t1 & 0x1;
            t2 = t2 | t1;
            mtc1(t2, f0);
            cvt_s_w(f2, f0);
            add_s(f2, f2, f2);
        } else {
            // 0x004ce43c
            charge(ctx, 3);
            mtc1(t1, f0);
            cvt_s_w(f2, f0);
        }
        // 0x004ce464
        charge(ctx, 9);
        t1 = flt(0.00390625f);
        t1 = t1 | 0x8081;  // 0x3B808081: 1 / 255
        mtc1(t1, f0);
        mul_s(f0, f0, f2);
        swc1(f0, t0, rgba_f::kG);
        lbu(t1, v1, 2);
        if (i64(t1) < 0) {
            // 0x004ce494
            charge(ctx, 7);
            t2 = srl(t1, 1);
            t1 = t1 & 0x1;
            t2 = t2 | t1;
            mtc1(t2, f0);
            cvt_s_w(f2, f0);
            add_s(f2, f2, f2);
        } else {
            // 0x004ce488
            charge(ctx, 3);
            mtc1(t1, f0);
            cvt_s_w(f2, f0);
        }
        // 0x004ce4b0
        charge(ctx, 9);
        t1 = flt(0.00390625f);
        t1 = t1 | 0x8081;  // 0x3B808081: 1 / 255
        mtc1(t1, f0);
        mul_s(f0, f0, f2);
        swc1(f0, t0, rgba_f::kB);
        lbu(t1, v1, 3);
        if (i64(t1) < 0) {
            // 0x004ce4e0
            charge(ctx, 7);
            t2 = srl(t1, 1);
            t1 = t1 & 0x1;
            t2 = t2 | t1;
            mtc1(t2, f0);
            cvt_s_w(f3, f0);
            add_s(f3, f3, f3);
        } else {
            // 0x004ce4d4
            charge(ctx, 3);
            mtc1(t1, f0);
            cvt_s_w(f3, f0);
        }
        // 0x004ce4fc: the whole pixels, weight 1, summed into $t0
        charge(ctx, 27);
        a1 = subu(a3, a1);
        t3 = sra(a3, 16);
        mtc1(a1, f2);
        v1 = addiu(v1, 4);
        cvt_s_w(f4, f2);
        a1 = flt(0.00390625f);
        t1 = a1 | 0x8081;  // 0x3B808081: 1 / 255
        a1 = 0x37800000;  // 1 / 65536 (16.16 to float)
        mtc1(t1, f0);
        mul_s(f2, f0, f3);
        swc1(f2, t0, rgba_f::kA);
        mtc1(a1, f3);
        lwc1(f2, t0, rgba_f::kR);
        mul_s(f3, f3, f4);
        mul_s(f2, f2, f3);
        swc1(f2, t0, rgba_f::kR);
        lwc1(f2, t0, rgba_f::kG);
        mul_s(f2, f2, f3);
        swc1(f2, t0, rgba_f::kG);
        lwc1(f2, t0, rgba_f::kB);
        mul_s(f2, f2, f3);
        swc1(f2, t0, rgba_f::kB);
        lwc1(f2, t0, rgba_f::kA);
        mul_s(f2, f2, f3);
        swc1(f2, t0, rgba_f::kA);
        if (t3 == a0) {
            // 0x004ce82c
            charge(ctx, 1);
            lbu(a0, v1, 0);
        } else {
            // 0x004ce568
            charge(ctx, 2);
            mtc1(zero, f3);
            a1 = 0x10000;
            for (;;) {
                // 0x004ce570: one pixel: G, B, A, R (unsigned bytes / 255)
                charge(ctx, 3);
                lbu(t1, v1, 1);
                if (i64(t1) < 0) {
                    // 0x004ce588
                    charge(ctx, 7);
                    t2 = srl(t1, 1);
                    t1 = t1 & 0x1;
                    t2 = t2 | t1;
                    mtc1(t2, f2);
                    cvt_s_w(f2, f2);
                    add_s(f2, f2, f2);
                } else {
                    // 0x004ce57c
                    charge(ctx, 3);
                    mtc1(t1, f2);
                    cvt_s_w(f2, f2);
                }
                // 0x004ce5a4
                charge(ctx, 3);
                lbu(t1, v1, 2);
                mul_s(f5, f0, f2);
                if (i64(t1) < 0) {
                    // 0x004ce5bc
                    charge(ctx, 7);
                    t2 = srl(t1, 1);
                    t1 = t1 & 0x1;
                    t2 = t2 | t1;
                    mtc1(t2, f2);
                    cvt_s_w(f2, f2);
                    add_s(f2, f2, f2);
                } else {
                    // 0x004ce5b0
                    charge(ctx, 3);
                    mtc1(t1, f2);
                    cvt_s_w(f2, f2);
                }
                // 0x004ce5d8
                charge(ctx, 3);
                lbu(t1, v1, 3);
                mul_s(f6, f0, f2);
                if (i64(t1) < 0) {
                    // 0x004ce5f0
                    charge(ctx, 7);
                    t2 = srl(t1, 1);
                    t1 = t1 & 0x1;
                    t2 = t2 | t1;
                    mtc1(t2, f2);
                    cvt_s_w(f2, f2);
                    add_s(f2, f2, f2);
                } else {
                    // 0x004ce5e4
                    charge(ctx, 3);
                    mtc1(t1, f2);
                    cvt_s_w(f2, f2);
                }
                // 0x004ce60c
                charge(ctx, 3);
                lbu(t1, v1, 0);
                mul_s(f7, f0, f2);
                if (i64(t1) < 0) {
                    // 0x004ce624
                    charge(ctx, 7);
                    t2 = srl(t1, 1);
                    t1 = t1 & 0x1;
                    t2 = t2 | t1;
                    mtc1(t2, f2);
                    cvt_s_w(f4, f2);
                    add_s(f4, f4, f4);
                } else {
                    // 0x004ce618
                    charge(ctx, 3);
                    mtc1(t1, f2);
                    cvt_s_w(f4, f2);
                }
                // 0x004ce640
                charge(ctx, 17);
                lwc1(f2, t0, rgba_f::kR);
                t3 = addiu(t3, 1);
                v1 = addiu(v1, 4);
                a3 = addu(a3, a1);
                adda_s(f3, f2);
                madd_s(f2, f0, f4);
                swc1(f2, t0, rgba_f::kR);
                lwc1(f2, t0, rgba_f::kG);
                add_s(f2, f2, f5);
                swc1(f2, t0, rgba_f::kG);
                lwc1(f2, t0, rgba_f::kB);
                add_s(f2, f2, f6);
                swc1(f2, t0, rgba_f::kB);
                lwc1(f2, t0, rgba_f::kA);
                add_s(f2, f2, f7);
                swc1(f2, t0, rgba_f::kA);
                if (t3 == a0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004ce684
            charge(ctx, 2);
            lbu(a0, v1, 0);
        }
        // 0x004ce830: the last, partial pixel, weighted by its fraction
        charge(ctx, 2);
        if (i64(a0) < 0) {
            // 0x004ce844
            charge(ctx, 7);
            a1 = srl(a0, 1);
            a0 = a0 & 0x1;
            a1 = a1 | a0;
            mtc1(a1, f0);
            cvt_s_w(f2, f0);
            add_s(f2, f2, f2);
        } else {
            // 0x004ce838
            charge(ctx, 3);
            mtc1(a0, f0);
            cvt_s_w(f2, f0);
        }
        // 0x004ce860
        charge(ctx, 6);
        a1 = flt(0.00390625f);
        lbu(a0, v1, 1);
        a1 = a1 | 0x8081;  // 0x3B808081: 1 / 255
        mtc1(a1, f0);
        mul_s(f4, f0, f2);
        if (i64(a0) < 0) {
            // 0x004ce884
            charge(ctx, 7);
            a1 = srl(a0, 1);
            a0 = a0 & 0x1;
            a1 = a1 | a0;
            mtc1(a1, f0);
            cvt_s_w(f2, f0);
            add_s(f2, f2, f2);
        } else {
            // 0x004ce878
            charge(ctx, 3);
            mtc1(a0, f0);
            cvt_s_w(f2, f0);
        }
        // 0x004ce8a0
        charge(ctx, 6);
        a1 = flt(0.00390625f);
        lbu(a0, v1, 2);
        a1 = a1 | 0x8081;  // 0x3B808081: 1 / 255
        mtc1(a1, f0);
        mul_s(f7, f0, f2);
        if (i64(a0) < 0) {
            // 0x004ce8c4
            charge(ctx, 7);
            a1 = srl(a0, 1);
            a0 = a0 & 0x1;
            a1 = a1 | a0;
            mtc1(a1, f0);
            cvt_s_w(f2, f0);
            add_s(f2, f2, f2);
        } else {
            // 0x004ce8b8
            charge(ctx, 3);
            mtc1(a0, f0);
            cvt_s_w(f2, f0);
        }
        // 0x004ce8e0
        charge(ctx, 6);
        a0 = flt(0.00390625f);
        lbu(v1, v1, 3);
        a0 = a0 | 0x8081;  // 0x3B808081: 1 / 255
        mtc1(a0, f0);
        mul_s(f8, f0, f2);
        if (i64(v1) < 0) {
            // 0x004ce904
            charge(ctx, 7);
            a0 = srl(v1, 1);
            v1 = v1 & 0x1;
            a0 = a0 | v1;
            mtc1(a0, f0);
            cvt_s_w(f3, f0);
            add_s(f3, f3, f3);
        } else {
            // 0x004ce8f8
            charge(ctx, 3);
            mtc1(v1, f0);
            cvt_s_w(f3, f0);
        }
        // 0x004ce920
        charge(ctx, 27);
        v1 = 0x3B800000;
        a0 = subu(a2, a3);
        a1 = v1 | 0x8081;  // 0x3B808081: 1 / 255
        mtc1(a1, f2);
        v1 = 0x37800000;  // 1 / 65536 (16.16 to float)
        mtc1(a0, f0);
        mul_s(f6, f2, f3);
        cvt_s_w(f3, f0);
        mtc1(v1, f2);
        lwc1(f0, t0, rgba_f::kR);
        mul_s(f5, f2, f3);
        mul_s(f2, f4, f5);
        add_s(f0, f0, f2);
        swc1(f0, t0, rgba_f::kR);
        lwc1(f0, t0, rgba_f::kG);
        mul_s(f4, f7, f5);
        add_s(f0, f0, f4);
        swc1(f0, t0, rgba_f::kG);
        lwc1(f0, t0, rgba_f::kB);
        mul_s(f3, f8, f5);
        add_s(f0, f0, f3);
        swc1(f0, t0, rgba_f::kB);
        lwc1(f0, t0, rgba_f::kA);
        mul_s(f2, f6, f5);
        add_s(f0, f0, f2);
        swc1(f0, t0, rgba_f::kA);
        backedge(ctx);
    }
    // 0x004ce7ec: the sum divided by the span width (x1 - x0) / 65536
    charge(ctx, 16);
    v1 = flt(1.0f);
    mtc1(v1, f2);
    lwc1(f0, t0, rgba_f::kR);
    div_s(f1, f2, f1);
    mul_s(f0, f0, f1);
    swc1(f0, t0, rgba_f::kR);
    lwc1(f0, t0, rgba_f::kG);
    mul_s(f0, f0, f1);
    swc1(f0, t0, rgba_f::kG);
    lwc1(f0, t0, rgba_f::kB);
    mul_s(f0, f0, f1);
    swc1(f0, t0, rgba_f::kB);
    lwc1(f0, t0, rgba_f::kA);
    mul_s(f0, f0, f1);
    swc1(f0, t0, rgba_f::kA);
    // 0x004ce98c
    charge(ctx, 2);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_4CE3A0(EEContext& ctx, u64 image, u64 x0, u64 x1, u64 row) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(image));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(x0));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(x1));
    ee::core::set_gpr64(ctx, GPR_A3, static_cast<u64>(row));
    sub_4CE3A0(ctx);
}

// 0x004CE9A0 sub_4CE9A0 -- 620 bytes; frame 0x60: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4CE9A0 [image resample: one output pixel's box sample]: $a0 the image, $a1 / $a2 the x span (16.16), $a3 / $t0
// the y span [y0, y1) (16.16), $t1 the RGBA float result. Rows are sampled through sub_4CE3A0: the first partial row
// weighted by its covered fraction, whole rows by 1 (into the 16-byte frame buffer at sp + 80, then added), the last
// partial row by its fraction; the sum divided by the y extent.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: frame/spills (own frame)).
void sub_4CE9A0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::cvt_s_w, hg::div_s,
          hg::enter, hg::jal, hg::ld, hg::lq, hg::lwc1, hg::mtc1, hg::mul_s, hg::sd, hg::sll, hg::sq, hg::sra,
          hg::subu, hg::swc1;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f9{ctx, 9};
    // 0x004ce9a0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    t6 = t0;
    sd(ra, sp, 0x40);
    v1 = 0x37800000;  // 1 / 65536 (16.16 to float)
    sq(s3, sp, 0x30);
    mtc1(v1, f0);
    sq(s2, sp, 0x20);
    t4 = sra(t6, 16);
    sq(s1, sp, 0x10);
    t5 = t1;
    sq(s0, sp, 0x0);
    t8 = a0;
    s0 = a3;
    t7 = a1;
    t0 = subu(t6, s0);
    v1 = sra(s0, 16);
    mtc1(t0, f1);
    cvt_s_w(f1, f1);
    mul_s(f9, f0, f1);
    if (v1 == t4) {
        // 0x004cead0: the y span inside one row: one row sample (sub_4CE3A0), times the span
        charge(ctx, 14);
        t0 = t5;
        jal(ctx, 0x4CEAD0u, gen::fn_sub_4CE3A0_004ce3a0);
        lwc1(f0, t5, rgba_f::kR);
        mul_s(f0, f0, f9);
        swc1(f0, t5, rgba_f::kR);
        lwc1(f0, t5, rgba_f::kG);
        mul_s(f0, f0, f9);
        swc1(f0, t5, rgba_f::kG);
        lwc1(f0, t5, rgba_f::kB);
        mul_s(f0, f0, f9);
        swc1(f0, t5, rgba_f::kB);
        lwc1(f0, t5, rgba_f::kA);
        mul_s(f0, f0, f9);
        swc1(f0, t5, rgba_f::kA);
    } else {
        // 0x004ce9f4: the first, partial row, weighted by its covered fraction
        charge(ctx, 25);
        v1 = addiu(v1, 1);
        t0 = t5;
        s3 = sll(v1, 16);
        jal(ctx, 0x4CE9FCu, gen::fn_sub_4CE3A0_004ce3a0);
        a0 = subu(s3, s0);
        v1 = 0x37800000;  // 1 / 65536 (16.16 to float)
        mtc1(a0, f1);
        s2 = sra(s3, 16);
        mtc1(v1, f0);
        cvt_s_w(f1, f1);
        mul_s(f1, f0, f1);
        lwc1(f0, t5, rgba_f::kR);
        mul_s(f0, f0, f1);
        swc1(f0, t5, rgba_f::kR);
        lwc1(f0, t5, rgba_f::kG);
        mul_s(f0, f0, f1);
        swc1(f0, t5, rgba_f::kG);
        lwc1(f0, t5, rgba_f::kB);
        mul_s(f0, f0, f1);
        swc1(f0, t5, rgba_f::kB);
        lwc1(f0, t5, rgba_f::kA);
        mul_s(f0, f0, f1);
        swc1(f0, t5, rgba_f::kA);
        if (s2 == t4) {
            // 0x004ceb48
            charge(ctx, 1);
            a0 = t8;
        } else {
            // 0x004cea58: the whole rows, weight 1 (each into sp+0x50, then added)
            charge(ctx, 3);
            s1 = addiu(sp, 0x54);
            s0 = addiu(sp, 0x58);
            t9 = addiu(sp, 0x5C);
            for (;;) {
                // 0x004cea64
                charge(ctx, 25);
                a0 = t8;
                a1 = t7;
                a3 = s3;
                t0 = addiu(sp, 0x50);
                jal(ctx, 0x4CEA70u, gen::fn_sub_4CE3A0_004ce3a0);
                lwc1(f1, t5, rgba_f::kR);
                v1 = 0x10000;
                lwc1(f0, sp, 0x50);
                s2 = addiu(s2, 1);
                s3 = addu(s3, v1);
                add_s(f0, f1, f0);
                swc1(f0, t5, rgba_f::kR);
                lwc1(f1, t5, rgba_f::kG);
                lwc1(f0, s1, 0);
                add_s(f0, f1, f0);
                swc1(f0, t5, rgba_f::kG);
                lwc1(f1, t5, rgba_f::kB);
                lwc1(f0, s0, 0);
                add_s(f0, f1, f0);
                swc1(f0, t5, rgba_f::kB);
                lwc1(f1, t5, rgba_f::kA);
                lwc1(f0, t9, 0);
                add_s(f0, f1, f0);
                swc1(f0, t5, rgba_f::kA);
                if (s2 == t4) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004ceac8
            charge(ctx, 2);
            a0 = t8;
        }
        // 0x004ceb4c: the last, partial row, weighted by its fraction
        charge(ctx, 41);
        a1 = t7;
        a3 = s3;
        t0 = addiu(sp, 0x50);
        jal(ctx, 0x4CEB54u, gen::fn_sub_4CE3A0_004ce3a0);
        a0 = subu(t6, s3);
        v1 = 0x37800000;  // 1 / 65536 (16.16 to float)
        mtc1(a0, f2);
        a1 = addiu(sp, 0x54);
        mtc1(v1, f1);
        cvt_s_w(f2, f2);
        a0 = addiu(sp, 0x58);
        v1 = addiu(sp, 0x5C);
        mul_s(f4, f1, f2);
        lwc1(f0, sp, 0x50);
        lwc1(f2, a1, 0);
        lwc1(f1, a0, 0);
        mul_s(f3, f0, f4);
        lwc1(f0, v1, 0);
        mul_s(f2, f2, f4);
        mul_s(f1, f1, f4);
        mul_s(f0, f0, f4);
        swc1(f3, sp, 0x50);
        swc1(f2, a1, 0);
        swc1(f1, a0, 0);
        swc1(f0, v1, 0);
        lwc1(f0, t5, rgba_f::kR);
        add_s(f0, f0, f3);
        swc1(f0, t5, rgba_f::kR);
        lwc1(f0, a1, 0);
        lwc1(f1, t5, rgba_f::kG);
        add_s(f0, f1, f0);
        swc1(f0, t5, rgba_f::kG);
        lwc1(f0, a0, 0);
        lwc1(f1, t5, rgba_f::kB);
        add_s(f0, f1, f0);
        swc1(f0, t5, rgba_f::kB);
        lwc1(f0, v1, 0);
        lwc1(f1, t5, rgba_f::kA);
        add_s(f0, f1, f0);
        swc1(f0, t5, rgba_f::kA);
        backedge(ctx);
    }
    // 0x004ceb08: the sum divided by the y extent
    charge(ctx, 16);
    v1 = flt(1.0f);
    mtc1(v1, f1);
    lwc1(f0, t5, rgba_f::kR);
    div_s(f1, f1, f9);
    mul_s(f0, f0, f1);
    swc1(f0, t5, rgba_f::kR);
    lwc1(f0, t5, rgba_f::kG);
    mul_s(f0, f0, f1);
    swc1(f0, t5, rgba_f::kG);
    lwc1(f0, t5, rgba_f::kB);
    mul_s(f0, f0, f1);
    swc1(f0, t5, rgba_f::kB);
    lwc1(f0, t5, rgba_f::kA);
    mul_s(f0, f0, f1);
    swc1(f0, t5, rgba_f::kA);
    // 0x004cebf0
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_4CE9A0(EEContext& ctx, u64 image, u64 x0, u64 x1, u64 y0) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(image));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(x0));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(x1));
    ee::core::set_gpr64(ctx, GPR_A3, static_cast<u64>(y0));
    sub_4CE9A0(ctx);
}

// 0x004CEC10 sub_4CEC10 -- 536 bytes; frame 0x100: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4CEC10 [RwImageResample-like (dst, src)]: $a0 the destination image (+0 flags, +4 width, +8 height, +16 stride,
// +20 pixels), $a1 the source (+0 flags: bit 1 copied, +4 width, +8 height). The 16.16 steps src / dst * 65536 per
// axis; each destination pixel is the box sample sub_4CE9A0 over its source footprint, converted back to bytes as
// (int)(0.5 + 255 * c) per channel. The compiler keeps the height and the y step in 128-bit frame slots (sp + 176 /
// + 160) and the running y and row end at sp + 208 / + 192.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: frame/spills (own frame)).
void sub_4CEC10(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::cvt_s_w, hg::cvt_w_s,
          hg::div_s, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::lwc1, hg::madd_s, hg::mfc1, hg::mtc1, hg::mul_s,
          hg::mult, hg::sb, hg::sd, hg::slt, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x004cec10
    enter(ctx, 49);  // entry check point + this block's cycles
    sp = addiu(sp, -0x100);
    lw(a2, a1, rw_image::kFlags);  // the source's flags
    sd(ra, sp, 0x90);
    lwc1(f3, a1, rw_image::kWidth);
    sq(fp, sp, 0x80);
    lwc1(f0, a1, rw_image::kHeight);
    sq(s7, sp, 0x70);
    v0 = a0;
    sq(s6, sp, 0x60);
    fp = 0;
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    cvt_s_w(f3, f3);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s2, a0, rw_image::kWidth);  // s2 = the destination width
    lw(v1, a0, rw_image::kHeight);
    sw(a1, sp, 0xEC);
    lw(a1, a0, rw_image::kFlags);
    mtc1(s2, f1);
    sq(v1, sp, 0xB0);
    cvt_s_w(f1, f1);
    v1 = flt(65536.0f);
    div_s(f1, f3, f1);
    mtc1(v1, f2);
    mul_s(f1, f2, f1);
    v1 = a2 & 0x2;
    v1 = a1 | v1;
    sw(v1, a0, 0);
    lq(v1, sp, 0xB0);
    cvt_w_s(f1, f1);
    mfc1(s1, f1);
    cvt_s_w(f1, f0);
    mtc1(v1, f0);
    cvt_s_w(f0, f0);
    div_s(f0, f1, f0);
    mul_s(f0, f2, f0);
    cvt_w_s(f0, f0);
    mfc1(v1, f0);
    sq(v1, sp, 0xA0);
    lq(v1, sp, 0xB0);
    at = slt(0, v1);
    sw(zero, sp, 0xD0);
    if (at != 0) {
        // 0x004cecd4: per destination row
        charge(ctx, 3);
        s0 = addiu(sp, 0xF4);
        s6 = addiu(sp, 0xF8);
        s7 = addiu(sp, 0xFC);
        for (;;) {
            // 0x004cece0: the row's pixels
            charge(ctx, 8);
            lw(v1, v0, rw_image::kStride);
            mult(a1, v1, fp);
            lw(a0, v0, rw_image::kPixels);
            s4 = 0;
            s5 = 0;
            v1 = slt(0, s2);
            s3 = addu(a0, a1);
            if (v1 != 0) {
                // 0x004ced28
                charge(ctx, 6);
                lw(a0, sp, 0xD0);
                lq(v1, sp, 0xA0);
                v1 = addu(a0, v1);
                v1 = addiu(v1, -1);
                sw(v1, sp, 0xC0);
                for (;;) {
                    // 0x004ced40: one pixel: the box sample over its source footprint (sub_4CE9A0), back to bytes as
                    // (int)(0.5 + 255 c)
                    charge(ctx, 43);
                    lw(a0, sp, 0xEC);
                    lw(a3, sp, 0xD0);
                    v1 = addu(s4, s1);
                    lw(t0, sp, 0xC0);
                    a2 = addiu(v1, -1);
                    a1 = s4;
                    t1 = addiu(sp, 0xF0);
                    jal(ctx, 0x4CED58u, gen::fn_sub_4CE9A0_004ce9a0);
                    v1 = flt(255.0f);
                    s5 = addiu(s5, 1);
                    mtc1(v1, f3);
                    s4 = addu(s4, s1);
                    lwc1(f0, sp, 0xF0);
                    v1 = flt(0.5f);
                    mtc1(v1, f2);
                    mtc1(zero, f1);
                    v1 = slt(s5, s2);
                    adda_s(f1, f2);
                    madd_s(f0, f3, f0);
                    cvt_w_s(f0, f0);
                    mfc1(a0, f0);
                    adda_s(f1, f2);
                    sb(a0, s3, 0);
                    lwc1(f0, s0, 0);
                    madd_s(f0, f3, f0);
                    cvt_w_s(f0, f0);
                    mfc1(a0, f0);
                    adda_s(f1, f2);
                    sb(a0, s3, 1);
                    lwc1(f0, s6, 0);
                    madd_s(f0, f3, f0);
                    cvt_w_s(f0, f0);
                    mfc1(a0, f0);
                    adda_s(f1, f2);
                    sb(a0, s3, 2);
                    lwc1(f0, s7, 0);
                    madd_s(f0, f3, f0);
                    cvt_w_s(f0, f0);
                    mfc1(a0, f0);
                    sb(a0, s3, 3);
                    s3 = addiu(s3, 4);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004cedec
                charge(ctx, 2);
                backedge(ctx);
            }
            // 0x004ced00
            charge(ctx, 8);
            lw(a0, sp, 0xD0);
            lq(v1, sp, 0xA0);
            fp = addiu(fp, 0x1);
            a0 = addu(a0, v1);
            lq(v1, sp, 0xB0);
            v1 = slt(fp, v1);
            sw(a0, sp, 0xD0);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004ced20
    charge(ctx, 2);
    // 0x004cedf8
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
    sp = addiu(sp, 0x100);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4CEC10(EEContext& ctx, u64 dst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(dst));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(src));
    sub_4CEC10(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004F2E70 RxPipelineExecute -- 252 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// RxPipelineExecute(pipeline, data, lock): with `lock` and an unlocked pipeline (the current pipeline gp-16832 +24),
// sub_4F6890 locks it first. Sets the execution globals (0x965A88 = 1 "continue", 0x965A80 the pipeline, 0x965A90
// the data, 0x965A94 the current pipeline), clears the pipeline's +16 state and calls the first node's body
// (node +0 = its definition, +4 the body) as body(node, &0x965A90). A body returning 0 clears the "continue" word.
// A pipeline state >= 2 afterwards is set to 2 and its +20 list is released (sub_4F28F0). The globals are cleared;
// returns the pipeline when "continue" survived, else 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void RxPipelineExecute(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::call, hg::charge, hg::enter, hg::jal, hg::jalr, hg::ld, hg::link,
          hg::lq, hg::lw, hg::sd, hg::slti, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f2e70
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    if (a2 != 0) {
        // 0x004f2e8c: lock first when asked and the pipeline needs it (sub_4F6890)
        charge(ctx, 4);
        lw(a0, gp, rwl::kGpRxHeap);
        lw(v0, a0, rx_pipeline::kNeedsLock);
        if (v0 != 0) {
            // 0x004f2e9c
            charge(ctx, 2);
            jal(ctx, 0x4F2E9Cu, gen::fn_sub_4F6890_004f6890);
        }
    }
    // 0x004f2ea4: the execution globals; the first node's body(node, &data)
    charge(ctx, 19);
    v1 = 1;
    v0 = hi(kRxExecContinue);
    sw(v1, v0, lo(kRxExecContinue));
    a1 = hi(kRxExecData);
    lw(v1, gp, rwl::kGpRxHeap);
    v0 = hi(kRxExecPipeline);
    sw(s1, v0, lo(kRxExecPipeline));
    v0 = hi(kRxExecData);
    sw(s0, v0, lo(kRxExecData));
    v0 = hi(kRxExecHeap);
    sw(v1, v0, lo(kRxExecHeap));
    sw(zero, s1, rx_pipeline::kState);
    lw(a0, s1, rx_pipeline::kFirstNode);
    lw(v0, a0, 0);
    lw(v0, v0, 4);
    a1 = addiu(a1, lo(kRxExecData));
    jalr(ctx, 0x4F2EE0u, v0.u());
    if (v0 == 0) {
        // 0x004f2f34: it returned 0: stop
        charge(ctx, 3);
        v1 = hi(kRxExecContinue);
        sw(v0, v1, lo(kRxExecContinue));
        backedge(ctx);
    }
    // 0x004f2ef0: a state >= 2 afterwards: 2, its list released (sub_4F28F0)
    charge(ctx, 4);
    lw(v0, s1, rx_pipeline::kState);
    at = slti(v0, 2);
    if (at == 0) {
        // 0x004f2f40
        charge(ctx, 6);
        v0 = 2;
        sw(v0, s1, rx_pipeline::kState);
        link(ctx, 0x4F2F48u);  // $ra first: the delay slot below depends on it
        lw(a0, s1, rx_pipeline::kList);
        call(ctx, gen::fn_sub_4F28F0_004f28f0);
        backedge(ctx);
    }
    // 0x004f2f00: the globals cleared; return the pipeline when "continue" survived
    charge(ctx, 9);
    v0 = hi(kRxExecData);
    v1 = hi(kRxExecPipeline);
    sw(zero, v0, lo(kRxExecData));
    v0 = hi(kRxExecContinue);
    sw(zero, v1, lo(kRxExecPipeline));
    lw(v0, v0, lo(kRxExecContinue));
    v1 = hi(kRxExecHeap);
    sw(zero, v1, lo(kRxExecHeap));
    if (v0 == 0) {
        // 0x004f2f2c
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004f2f24
        charge(ctx, 2);
        v0 = s1;
    }
    // 0x004f2f58 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 RxPipelineExecute(EEContext& ctx, u64 pipeline, u64 data, u64 lock) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(pipeline));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(data));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(lock));
    RxPipelineExecute(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_4F3150(EEContext& ctx, u64 size) {
    ee::core::set_gpr64(ctx, GPR_A0, size);
    c3::detail::Cpu(ctx).sub_4F3150();
    return ee::core::gpr64(ctx, GPR_V0);
}

// 0x004F5D30 sub_4F5D30 -- 88 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4F5D30 [a node's output link]: an 8-byte record from sub_4F3150 = {$a0, $a0 +8}; stored at *$a2 when that is
// still 0. Returns the record.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4F5D30(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq,
          hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f5d30
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a2;
    a0 = 8;
    jal(ctx, 0x4F5D48u, gen::fn_sub_4F3150_004f3150);
    lw(v1, s0, 0);
    if (v1 == 0) {
        // 0x004f5d6c
        charge(ctx, 2);
        sw(v0, s0, 0);
        backedge(ctx);
    }
    // 0x004f5d5c
    charge(ctx, 4);
    sw(s1, v0, 0);
    lw(v1, s1, 8);
    sw(v1, v0, 4);
    // 0x004f5d74
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4F5D30(EEContext& ctx, u64 node, u64 unused, u64 out) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(node));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(unused));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(out));
    sub_4F5D30(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004F62D0 sub_4F62D0 -- 244 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4F62D0 [lock one node's scratch block]: sub_4F61C0($a2) grows the pipeline's block (kept recompiled: RwRealloc);
// on success a 32-byte header is set up at the node's block (+0 its start: zeroed, its last 32 bytes a copy of the
// header) and linked to the previous node ($a1, its block's end - 32). Returns 1, or 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4F62D0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::lwc1,
          hg::sd, hg::sq, hg::subu, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x004f62d0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = a0;
    s0 = a1;
    a0 = a2;
    jal(ctx, 0x4F62E8u, gen::fn_sub_4F61C0_004f61c0);
    if (v0 == 0) {
        // 0x004f63ac: the block could not grow: 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004f62f8: the node's block: zeroed header, its last 32 bytes a copy of the header; the links
        charge(ctx, 37);
        lw(a3, s1, 0);
        lw(v1, s1, 4);
        a2 = addiu(a3, 32);
        sw(zero, a3, 0);
        a1 = addu(a3, v1);
        sw(zero, a3, 4);
        a0 = addiu(a1, -32);
        sw(zero, a3, 8);
        v1 = addiu(a2, 32);
        sw(zero, a3, 12);
        v1 = subu(a0, v1);
        lwc1(f3, a3, 0);
        lwc1(f2, a3, 4);
        lwc1(f1, a3, 8);
        lwc1(f0, a3, 12);
        swc1(f3, a1, -32);
        swc1(f2, a1, -28);
        swc1(f1, a1, -24);
        swc1(f0, a1, -20);
        lwc1(f3, a3, 16);
        lwc1(f2, a3, 20);
        lwc1(f1, a3, 24);
        lwc1(f0, a3, 28);
        swc1(f3, a1, -16);
        swc1(f2, a1, -12);
        swc1(f1, a1, -8);
        swc1(f0, a1, -4);
        sw(a2, a3, 4);
        sw(a3, a3, 32);
        sw(a0, a3, 36);
        sw(a2, a1, -32);
        sw(v1, a3, 40);
        sw(v0, a3, 44);
        sw(a2, v0, 4);
        lw(v1, a3, 40);
        sw(v1, v0, 0);
        if (s0 != 0) {
            // 0x004f638c: linked to the previous node's block end
            charge(ctx, 6);
            lw(v1, s0, 0);
            lw(v0, s0, 4);
            v0 = addu(v1, v0);
            sw(a3, v0, -28);
            v0 = addiu(v0, -32);
            sw(v0, a3, 0);
        }
        // 0x004f63a4: 1
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x004f63b0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4F62D0(EEContext& ctx, u64 node, u64 prev, u64 pipeline) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(node));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(prev));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(pipeline));
    sub_4F62D0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004F6890 sub_4F6890 -- 212 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4F6890 [RxPipelineLock-like]: clears the pipeline's +20, locks every node of the list at pipeline +4 -> +8
// (sub_4F62D0 with the previous node), the first one's +0 going to pipeline +8, then the list head itself; clears
// +24 (the "needs lock" flag) and returns 1, or 0 when a node failed.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void sub_4F6890(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq,
          hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f6890
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = 0;
    sq(s0, sp, 0x0);
    sw(zero, a0, rx_pipeline::kList);
    lw(v0, a0, rx_pipeline::kNodes);
    lw(s1, v0, 8);
    s0 = a0;
    if (s1 != 0) {
        for (;;) {
            // 0x004f68bc
            charge(ctx, 6);
            a0 = s1;
            a1 = s2;
            a2 = s0;
            jal(ctx, 0x4F68C4u, gen::fn_sub_4F62D0_004f62d0);
            if (v0 == 0) {
                // 0x004f68d4: a node failed: 0
                charge(ctx, 2);
                v0 = 0;
                // 0x004f694c (the shared epilogue, written out on this path)
                charge(ctx, 6);
                ld(ra, sp, 0x30);
                lq(s2, sp, 0x20);
                lq(s1, sp, 0x10);
                lq(s0, sp, 0x0);
                sp = addiu(sp, 0x40);
                return;
            }
            // 0x004f68dc: the first node's block start goes to the pipeline (+8)
            charge(ctx, 2);
            if (s2 == 0) {
                // 0x004f6928
                charge(ctx, 3);
                lw(v0, s1, 0);
                sw(v0, s0, rx_pipeline::kFirstNode);
                backedge(ctx);
            } else {
                // 0x004f68e4
                charge(ctx, 1);
            }
            // 0x004f68e8: the next node (+8)
            charge(ctx, 4);
            s2 = s1;
            lw(s1, s1, 8);
            if (s1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004f68f8: then the list head itself
    charge(ctx, 7);
    lw(s1, s0, rx_pipeline::kNodes);
    a1 = s2;
    a2 = s0;
    a0 = s1;
    jal(ctx, 0x4F6904u, gen::fn_sub_4F62D0_004f62d0);
    if (v0 == 0) {
        // 0x004f6938
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004f6914
        charge(ctx, 2);
        if (s2 == 0) {
            // 0x004f6940
            charge(ctx, 3);
            lw(v0, s1, 0);
            sw(v0, s0, rx_pipeline::kFirstNode);
            backedge(ctx);
        }
        // 0x004f691c
        charge(ctx, 3);
        sw(zero, s0, rx_pipeline::kNeedsLock);
        v0 = 1;
    }
    // 0x004f694c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4F6890(EEContext& ctx, u64 pipeline) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(pipeline));
    sub_4F6890(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_4F1ED0(EEContext& ctx, u64 vertices, u64 count, u64 matrix, u64 flags) {
    ee::core::set_gpr64(ctx, GPR_A0, vertices);
    ee::core::set_gpr64(ctx, GPR_A1, count);
    ee::core::set_gpr64(ctx, GPR_A2, matrix);
    ee::core::set_gpr64(ctx, GPR_A3, flags);
    c3::detail::Cpu(ctx).sub_4F1ED0();
    return ee::core::gpr64(ctx, GPR_V0);
}

// 0x004F1FD0 sub_4F1FD0 -- 384 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4F1FD0 [RwIm3DRenderIndexedPrimitive(type, indices, count)]: only after a transform (Im3D +68 != 0). Fills
// {+108 0, +112 type, +116 indices, +120 count}, picks the type's pipeline; for tri-lists the primitive count is
// count - count % 3, for line-lists count rounded down to even (+44). Runs RxPipelineExecute(pipe, record, 0);
// returns 1 or 0 (RWERROR 0x23 without a transform, 0x25 for a bad type).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: the hand version terminated the host on a random world).
void sub_4F1FD0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::div, hg::enter, hg::i64, hg::jal,
          hg::ld, hg::link, hg::lq, hg::lw, hg::mfhi, hg::sd, hg::sq, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004f1fd0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    a3 = hi(rwl::kRwGlobals);
    sd(ra, sp, 0x10);
    a3 = addiu(a3, lo(rwl::kRwGlobals));
    sq(s0, sp, 0x0);
    lw(v0, gp, rwl::kGpIm3DOffset);
    v1 = addu(a3, v0);
    lw(v0, v1, im3d_state::kTransformed);
    if (v0 == 0) {
        // 0x004f211c: no transform: RWERROR(0x23); 0
        charge(ctx, 9);
        v0 = 1;
        a0 = 35;
        link(ctx, 0x4F2124u);  // $ra first: the delay slot below depends on it
        sw(v0, sp, 0x20);
        call(ctx, gen::fn_sub_4C1D10_004c1d10);
        sw(v0, sp, 0x24);
        a0 = addiu(sp, 0x20);
        jal(ctx, 0x4F2130u, gen::fn_sub_4C1C50_004c1c50);
        backedge(ctx);
        // 0x004f2114: 0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004f1ff8: the render record {+108 0, type, indices, count}; the type's pipeline
        charge(ctx, 7);
        sw(zero, v1, im3d_state::kRecordWord108);
        v0 = 2;
        sw(a0, v1, im3d_state::kType);
        s0 = addiu(v1, im3d_state::kRecord);
        sw(a1, v1, im3d_state::kIndices);
        sw(a2, v1, im3d_state::kCount);
        if (a0 == v0) {
            // 0x004f20c8: type 2
            charge(ctx, 5);
            lw(v0, gp, rwl::kGpIm3DOffset);
            v0 = addu(a3, v0);
            lw(v0, v0, 20);
            sw(v0, s0, 32);
        } else {
            // 0x004f2014
            charge(ctx, 3);
            a1 = 1;
            if (a0 == a1) {
                // 0x004f2098: type 1: the count rounded down to even
                charge(ctx, 6);
                lw(v1, gp, rwl::kGpIm3DOffset);
                v0 = a2 & 0x1;
                v1 = addu(a3, v1);
                lw(v1, v1, 16);
                sw(v1, s0, 32);
                if (i64(a2) < 0) {
                    // 0x004f20b0
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x004f20b8
                        charge(ctx, 1);
                        v0 = addiu(v0, -2);
                    }
                }
                // 0x004f20bc
                charge(ctx, 3);
                v0 = subu(a2, v0);
                sw(v0, s0, 44);
            } else {
                // 0x004f2020
                charge(ctx, 3);
                v0 = 4;
                if (a0 == v0) {
                    // 0x004f2084: type 4
                    charge(ctx, 5);
                    lw(v0, gp, rwl::kGpIm3DOffset);
                    v0 = addu(a3, v0);
                    lw(v0, v0, 12);
                    sw(v0, s0, 32);
                } else {
                    // 0x004f202c
                    charge(ctx, 3);
                    v0 = 5;
                    if (a0 == v0) {
                        // 0x004f2070: type 5
                        charge(ctx, 5);
                        lw(v0, gp, rwl::kGpIm3DOffset);
                        v0 = addu(a3, v0);
                        lw(v0, v0, 8);
                        sw(v0, s0, 32);
                    } else {
                        // 0x004f2038
                        charge(ctx, 3);
                        v1 = 3;
                        if (a0 == v1) {
                            // 0x004f204c: type 3: count - count % 3
                            charge(ctx, 9);
                            lw(v0, gp, rwl::kGpIm3DOffset);
                            v0 = addu(a3, v0);
                            lw(v0, v0, 4);
                            sw(v0, s0, 32);
                            div(a2, v1);
                            mfhi(v0);
                            v0 = subu(a2, v0);
                            sw(v0, s0, 44);
                        } else {
                            // 0x004f2044: another type: RWERROR(0x25, type)
                            charge(ctx, 2);
                            sw(a1, sp, 0x28);
                            // 0x004f20dc
                            charge(ctx, 6);
                            a1 = a0;
                            a0 = 37;
                            jal(ctx, 0x4F20E0u, gen::fn_sub_4C1D10_004c1d10);
                            sw(v0, sp, 0x2C);
                            a0 = addiu(sp, 0x28);
                            jal(ctx, 0x4F20ECu, gen::fn_sub_4C1C50_004c1c50);
                        }
                    }
                }
            }
        }
        // 0x004f20f4: RxPipelineExecute(pipe, record, 0)
        charge(ctx, 6);
        lw(a0, s0, 32);
        a1 = s0;
        a2 = 0;
        jal(ctx, 0x4F20FCu, gen::fn_RxPipelineExecute_004f2e70);
        if (v0 == 0) {
            // 0x004f2114 (written out on this path): the pipeline failed: 0
            charge(ctx, 2);
            v0 = 0;
        } else {
            // 0x004f210c: 1
            charge(ctx, 2);
            v0 = 1;
        }
    }
    // 0x004f2140 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4F1FD0(EEContext& ctx, u64 type, u64 indices, u64 count) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(type));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(indices));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(count));
    sub_4F1FD0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_4F2150(EEContext& ctx, u64 type) {
    ee::core::set_gpr64(ctx, GPR_A0, type);
    c3::detail::Cpu(ctx).sub_4F2150();
    return ee::core::gpr64(ctx, GPR_V0);
}

// 0x004D78B0 sub_4D78B0 -- 1708 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4D78B0 [RwRenderStateGet, the driver's: the engine's pointer at 0x960094]: $a0 the state, $a1 where its value
// goes. The answers come from the GS register shadows of the sky driver: TEST gp-17048 / gp-17072 (alpha test, z test,
// the alpha reference), ALPHA gp-17032 (looked up in the 6 x 6 blend table 0x77EF80 by the shadows of the source /
// destination blend gp-20264 / gp-20260, with FIX = 0x80 for 1 / 1), the prim / shading word gp-20272, CLAMP
// gp-17040, FOGCOL gp-17056, the texture raster / filter gp-16964 / gp-16956, the current raster gp-16924 and its
// address-mode words, the texture's +... (state 1: gp-16948, -1 read as 0). Returns 1, or 0 for an unknown state or an
// unrepresentable shadow. The compiled form is a compare chain over the state (13, 30, 29, 20, 16, 15, 14, 12, 11, 10,
// 9 .. 1) with a shared "store and return 1" tail.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4D78B0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::cvt_w_s, hg::dsll, hg::dsll32,
          hg::dsra, hg::dsra32, hg::enter, hg::i64, hg::jal, hg::ld, hg::lq, hg::lw, hg::mfc1, hg::mtc1, hg::mul_s,
          hg::sd, hg::si, hg::sll, hg::sltiu, hg::sltu, hg::sq, hg::sw, hg::tail;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // The shared tails of the compare chain, written out on each path that reaches them.
    auto epilogue = [&] {  // 0x004d7f50
        charge(ctx, 3);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
    };
    auto finish = [&] {  // 0x004d7f4c: $ra back, then the epilogue
        charge(ctx, 1);
        ld(ra, sp, 0x10);
        epilogue();
    };
    auto finish2 = [&] {  // 0x004d7f00 / 0x004d7f0c: one block more, then finish
        charge(ctx, 2);
        finish();
    };
    auto return_1 = [&] {  // 0x004d7f08: the value is stored: return 1
        charge(ctx, 1);
        v0 = 1;
        finish2();
    };
    // 0x004d78b0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a1;
    a1 = 13;
    if (a0 == a1) {
        // 0x004d7efc: state 13: not supported: 0
        charge(ctx, 1);
        v0 = 0;
        finish2();
        return;
    } else {
        // 0x004d78cc
        charge(ctx, 3);
        v0 = 30;
        if (a0 == v0) {
            // 0x004d7ec8: state 30: the alpha reference (TEST bits 4..11) through a float scale
            charge(ctx, 13);
            ld(v0, gp, sky::kGpTest1);
            v0 = v0 & 0xFF0;
            a0 = dsra(v0, 4);
            jal(ctx, 0x4D7ED0u, gen::fn___floatdisf_0052eb60);
            v0 = flt(1.9921875f);
            v0 = v0 | 0x7;
            mtc1(v0, f1);
            mul_s(f0, f1, f0);
            cvt_w_s(f0, f0);
            mfc1(v0, f0);
            sw(v0, s0, 0);
            return_1();
            return;
        }
        // 0x004d78d8
        charge(ctx, 3);
        v0 = 29;
        if (a0 == v0) {
            // 0x004d7df0: state 29: the alpha test from TEST (ATE clear: 8; else the ATST / AREF combination)
            charge(ctx, 4);
            ld(v1, gp, sky::kGpTest1);
            v0 = v1 & 0x1;
            if (v0 == 0) {
                // 0x004d7f40
                charge(ctx, 3);
                v0 = 8;
                sw(v0, s0, 0);
                backedge(ctx);
            } else {
                // 0x004d7e00
                charge(ctx, 3);
                a0 = v1 & 0x300E;
                if (a0 == a1) {
                    // 0x004d7eb4
                    charge(ctx, 3);
                    v0 = 6;
                    sw(v0, s0, 0);
                } else {
                    // 0x004d7e0c
                    charge(ctx, 3);
                    v0 = 12;
                    if (a0 == v0) {
                        // 0x004d7ea8
                        charge(ctx, 3);
                        v0 = 5;
                        sw(v0, s0, 0);
                    } else {
                        // 0x004d7e18
                        charge(ctx, 3);
                        v0 = 10;
                        if (a0 == v0) {
                            // 0x004d7e9c
                            charge(ctx, 3);
                            v0 = 7;
                            sw(v0, s0, 0);
                        } else {
                            // 0x004d7e24
                            charge(ctx, 3);
                            v1 = 8;
                            if (a0 == v1) {
                                // 0x004d7e90
                                charge(ctx, 3);
                                v0 = 3;
                                sw(v0, s0, 0);
                            } else {
                                // 0x004d7e30
                                charge(ctx, 3);
                                v0 = 6;
                                if (a0 == v0) {
                                    // 0x004d7e84
                                    charge(ctx, 3);
                                    v0 = 4;
                                    sw(v0, s0, 0);
                                } else {
                                    // 0x004d7e3c
                                    charge(ctx, 3);
                                    v0 = 4;
                                    if (a0 == v0) {
                                        // 0x004d7e78
                                        charge(ctx, 3);
                                        v0 = 2;
                                        sw(v0, s0, 0);
                                    } else {
                                        // 0x004d7e48
                                        charge(ctx, 3);
                                        v0 = 2;
                                        if (a0 == v0) {
                                            // 0x004d7e70
                                            charge(ctx, 2);
                                            sw(v1, s0, 0);
                                        } else {
                                            // 0x004d7e54
                                            charge(ctx, 2);
                                            if (a0 == 0) {
                                                // 0x004d7e64
                                                charge(ctx, 3);
                                                v0 = 1;
                                                sw(v0, s0, 0);
                                            } else {
                                                // 0x004d7e5c
                                                charge(ctx, 2);
                                                sw(zero, s0, 0);
                                                // 0x004d7ec0
                                                charge(ctx, 2);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            return_1();
            return;
        }
        // 0x004d78e4
        charge(ctx, 3);
        v0 = 20;
        if (a0 == v0) {
            // 0x004d7de4: state 20: the cull mode word
            charge(ctx, 3);
            lw(v0, gp, sky::kGpCamProjection);
            sw(v0, s0, 0);
            return_1();
            return;
        }
        // 0x004d78f0
        charge(ctx, 3);
        v0 = 16;
        if (a0 == v0) {
            // 0x004d7da8: state 16: the fog type from the fog table pointer (1 / 2 / 3, else 0)
            charge(ctx, 5);
            lw(v1, gp, sky::kGpFogTable);
            v0 = hi(sky::kFogTable);
            v0 = addiu(v0, lo(sky::kFogTable));
            if (v1 == v0) {
                // 0x004d7f1c
                charge(ctx, 3);
                v0 = 1;
                sw(v0, s0, 0);
                backedge(ctx);
            } else {
                // 0x004d7dbc
                charge(ctx, 4);
                v0 = hi(kFogTable2);
                v0 = addiu(v0, lo(kFogTable2));
                if (v1 == v0) {
                    // 0x004d7f28
                    charge(ctx, 3);
                    v0 = 2;
                    sw(v0, s0, 0);
                    backedge(ctx);
                } else {
                    // 0x004d7dcc
                    charge(ctx, 4);
                    v0 = hi(kFogTable3);
                    v0 = addiu(v0, lo(kFogTable3));
                    if (v1 == v0) {
                        // 0x004d7f34
                        charge(ctx, 3);
                        v0 = 3;
                        sw(v0, s0, 0);
                        backedge(ctx);
                    } else {
                        // 0x004d7ddc
                        charge(ctx, 2);
                        sw(zero, s0, 0);
                    }
                }
            }
            return_1();
            return;
        }
        // 0x004d78fc
        charge(ctx, 3);
        v0 = 15;
        if (a0 == v0) {
            // 0x004d7d68: state 15: FOGCOL as 0xFFBBGGRR
            charge(ctx, 16);
            ld(a2, gp, sky::kGpFogCol);
            v1 = 0xFF0000;
            v0 = 0xFF00;
            v0 = dsll(v0, 16);
            a0 = a2 & 0xFF;
            v1 = a2 & v1;
            a1 = dsll(a0, 16);
            v1 = dsra(v1, 16);
            a0 = a2 & 0xFF00;
            a0 = a1 | a0;
            v1 = v1 | a0;
            v0 = v1 | v0;
            v0 = dsll32(v0, 0);
            v0 = dsra32(v0, 0);
            sw(v0, s0, 0);
            return_1();
            return;
        }
        // 0x004d7908
        charge(ctx, 3);
        v0 = 14;
        if (a0 == v0) {
            // 0x004d7d54: state 14: render flags bit 5
            charge(ctx, 5);
            ld(v0, gp, sky::kGpRenderFlags);
            v0 = v0 & 0x20;
            v0 = sltu(0, v0);
            sw(v0, s0, 0);
            return_1();
            return;
        }
        // 0x004d7914
        charge(ctx, 3);
        v0 = 12;
        if (a0 == v0) {
            // 0x004d7d48: state 12: the vertex alpha word
            charge(ctx, 3);
            lw(v0, gp, sky::kGpVertexAlpha);
            sw(v0, s0, 0);
            return_1();
            return;
        }
        // 0x004d7920
        charge(ctx, 3);
        v0 = 11;
        if (a0 == v0) {
            // 0x004d7c5c: state 11: the destination blend (the ALPHA shadow must be the table's entry)
            charge(ctx, 3);
            ld(a3, gp, sky::kGpAlpha1);
            if (i64(a3) >= 0) {
                // 0x004d7c68
                charge(ctx, 4);
                lw(a0, gp, sky::kGpSrcBlend);
                v1 = 1;
                t0 = 0;
                if (a0 == v1) {
                    // 0x004d7c78
                    charge(ctx, 3);
                    lw(v0, gp, sky::kGpDestBlend);
                    if (v0 == v1) {
                        // 0x004d7c84
                        charge(ctx, 1);
                        t0 = v1;
                    }
                }
                // 0x004d7c88
                charge(ctx, 16);
                lw(a1, gp, sky::kGpDestBlend);
                v0 = sll(a0, 2);
                v1 = 128;
                a2 = dsll32(v1, 0);
                v1 = hi(sky::kAlphaTable);
                if (t0 == 0) a2 = 0;
                v1 = addiu(v1, lo(sky::kAlphaTable));
                a0 = sll(a1, 1);
                a0 = addu(a0, a1);
                a0 = sll(a0, 3);
                v1 = addu(v1, a0);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                v0 = v0 | a2;
                if (a3 != v0) {
                    // 0x004d7cc8 (written out on this path): not representable: 0
                    charge(ctx, 2);
                    v0 = 0;
                    finish();
                    return;
                }
                // 0x004d7cd0
                charge(ctx, 3);
                at = sltiu(a1, 6);
                if (at != 0) {
                    // 0x004d7cdc
                    charge(ctx, 7);
                    v1 = hi(kJtBlendDest);
                    v0 = sll(a1, 2);
                    v1 = addiu(v1, lo(kJtBlendDest));
                    v0 = addu(v0, v1);
                    lw(v0, v0, 0);
                    switch (v0.u()) {
                    case 0x4D7CF8u:  // table[0]
                        // 0x004d7cf8
                        charge(ctx, 3);
                        v0 = 1;
                        sw(v0, s0, 0);
                        break;
                    case 0x4D7D04u:  // table[1]
                        // 0x004d7d04
                        charge(ctx, 3);
                        v0 = 2;
                        sw(v0, s0, 0);
                        break;
                    case 0x4D7D10u:  // table[2]
                        // 0x004d7d10
                        charge(ctx, 3);
                        v0 = 5;
                        sw(v0, s0, 0);
                        break;
                    case 0x4D7D1Cu:  // table[3]
                        // 0x004d7d1c
                        charge(ctx, 3);
                        v0 = 6;
                        sw(v0, s0, 0);
                        break;
                    case 0x4D7D28u:  // table[4]
                        // 0x004d7d28
                        charge(ctx, 3);
                        v0 = 7;
                        sw(v0, s0, 0);
                        break;
                    case 0x4D7D34u:  // table[5]
                        // 0x004d7d34
                        charge(ctx, 3);
                        v0 = 8;
                        sw(v0, s0, 0);
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v0.u());
                        return;
                    }
                    return_1();
                    return;
                }
                // 0x004d7d40
                charge(ctx, 2);
                v0 = 0;
                finish();
                return;
            }
            // 0x004d7cc8: a negative ALPHA shadow: 0
            charge(ctx, 2);
            v0 = 0;
            finish();
            return;
        }
        // 0x004d792c
        charge(ctx, 3);
        v0 = 10;
        if (a0 == v0) {
            // 0x004d7b74: state 10: the source blend (likewise)
            charge(ctx, 3);
            ld(t0, gp, sky::kGpAlpha1);
            if (i64(t0) >= 0) {
                // 0x004d7b80
                charge(ctx, 4);
                lw(a3, gp, sky::kGpSrcBlend);
                v1 = 1;
                a1 = 0;
                if (a3 == v1) {
                    // 0x004d7b90
                    charge(ctx, 3);
                    lw(v0, gp, sky::kGpDestBlend);
                    if (v0 == v1) {
                        // 0x004d7b9c
                        charge(ctx, 1);
                        a1 = v1;
                    }
                }
                // 0x004d7ba0
                charge(ctx, 16);
                lw(a2, gp, sky::kGpDestBlend);
                v0 = 128;
                v0 = dsll32(v0, 0);
                v1 = hi(sky::kAlphaTable);
                if (a1 == 0) v0 = 0;
                v1 = addiu(v1, lo(sky::kAlphaTable));
                a0 = sll(a3, 2);
                a1 = sll(a2, 1);
                a1 = addu(a1, a2);
                a1 = sll(a1, 3);
                v1 = addu(v1, a1);
                v1 = addu(a0, v1);
                lw(v1, v1, 0);
                v0 = v1 | v0;
                if (t0 != v0) {
                    // 0x004d7be0 (written out on this path): not representable: 0
                    charge(ctx, 2);
                    v0 = 0;
                    finish();
                    return;
                }
                // 0x004d7be8
                charge(ctx, 3);
                at = sltiu(a3, 6);
                if (at != 0) {
                    // 0x004d7bf4
                    charge(ctx, 6);
                    v0 = hi(kJtBlendSrc);
                    v0 = addiu(v0, lo(kJtBlendSrc));
                    v0 = addu(a0, v0);
                    lw(v0, v0, 0);
                    switch (v0.u()) {
                    case 0x4D7C0Cu:  // table[0]
                        // 0x004d7c0c
                        charge(ctx, 3);
                        v0 = 1;
                        sw(v0, s0, 0);
                        break;
                    case 0x4D7C18u:  // table[1]
                        // 0x004d7c18
                        charge(ctx, 3);
                        v0 = 2;
                        sw(v0, s0, 0);
                        break;
                    case 0x4D7C24u:  // table[2]
                        // 0x004d7c24
                        charge(ctx, 3);
                        v0 = 5;
                        sw(v0, s0, 0);
                        break;
                    case 0x4D7C30u:  // table[3]
                        // 0x004d7c30
                        charge(ctx, 3);
                        v0 = 6;
                        sw(v0, s0, 0);
                        break;
                    case 0x4D7C3Cu:  // table[4]
                        // 0x004d7c3c
                        charge(ctx, 3);
                        v0 = 7;
                        sw(v0, s0, 0);
                        break;
                    case 0x4D7C48u:  // table[5]
                        // 0x004d7c48
                        charge(ctx, 3);
                        v0 = 8;
                        sw(v0, s0, 0);
                        break;
                    default:  // not one of the table's targets: the dispatch table, as the recompiled body
                        tail(ctx, v0.u());
                        return;
                    }
                    return_1();
                    return;
                }
                // 0x004d7c54
                charge(ctx, 2);
                v0 = 0;
                finish();
                return;
            }
            // 0x004d7be0: a negative ALPHA shadow: 0
            charge(ctx, 2);
            v0 = 0;
            finish();
            return;
        }
        // 0x004d7938
        charge(ctx, 3);
        v0 = 9;
        if (a0 != v0) {
            // 0x004d7944
            charge(ctx, 3);
            v0 = 8;
            if (a0 == v0) {
                // 0x004d7ab0: state 8: ZBUF's ZMSK clear
                charge(ctx, 8);
                ld(v1, gp, sky::kGpZbuf1);
                v0 = 1;
                v0 = dsll32(v0, 0);
                v0 = v1 & v0;
                v0 = sltu(0, v0);
                v0 = v0 ^ 0x1;
                sw(v0, s0, 0);
                return_1();
                return;
            }
            // 0x004d7950
            charge(ctx, 3);
            v0 = 7;
            if (a0 == v0) {
                // 0x004d7a94: state 7: render flags bit 3 (2) or not (1)
                charge(ctx, 7);
                ld(a0, gp, sky::kGpRenderFlags);
                v1 = 2;
                v0 = 1;
                a0 = a0 & 0x8;
                if (a0 == 0) v1 = v0;
                sw(v1, s0, 0);
                return_1();
                return;
            }
            // 0x004d795c
            charge(ctx, 3);
            v0 = 6;
            if (a0 == v0) {
                // 0x004d7a74: state 6: TEST's ZTE / ZTST bits 17..18 = 2
                charge(ctx, 8);
                ld(a0, gp, sky::kGpTest1);
                v1 = 0x60000;
                v0 = 0x40000;
                v1 = a0 & v1;
                v0 = v1 ^ v0;
                v0 = sltiu(v0, 1);
                sw(v0, s0, 0);
                return_1();
                return;
            }
            // 0x004d7968
            charge(ctx, 3);
            v0 = 5;
            if (a0 == v0) {
                // 0x004d7a50: state 5: render flags bit 8 clear (1) or set (0)
                charge(ctx, 4);
                ld(v0, gp, sky::kGpRenderFlags);
                v0 = v0 & 0x100;
                if (v0 == 0) {
                    // 0x004d7a68
                    charge(ctx, 3);
                    v0 = 1;
                    sw(v0, s0, 0);
                } else {
                    // 0x004d7a60
                    charge(ctx, 2);
                    sw(zero, s0, 0);
                }
                return_1();
                return;
            }
            // 0x004d7974
            charge(ctx, 3);
            v0 = 4;
            if (a0 == v0) {
                // 0x004d7a28: state 4: CLAMP bits 2..3 (1 when 0, else 3)
                charge(ctx, 4);
                ld(v0, gp, sky::kGpClamp1);
                v0 = v0 & 0xC;
                if (v0 == 0) {
                    // 0x004d7a44
                    charge(ctx, 3);
                    v0 = 1;
                    sw(v0, s0, 0);
                } else {
                    // 0x004d7a38
                    charge(ctx, 3);
                    v0 = 3;
                    sw(v0, s0, 0);
                }
                return_1();
                return;
            }
            // 0x004d7980
            charge(ctx, 3);
            a1 = 3;
            if (a0 == a1) {
                // 0x004d7a04: state 3: CLAMP bits 0..1 (1 when 0, else 3)
                charge(ctx, 4);
                ld(v0, gp, sky::kGpClamp1);
                v0 = v0 & 0x3;
                if (v0 == 0) {
                    // 0x004d7a1c
                    charge(ctx, 3);
                    v0 = 1;
                    sw(v0, s0, 0);
                } else {
                    // 0x004d7a14
                    charge(ctx, 2);
                    sw(a1, s0, 0);
                }
                return_1();
                return;
            }
            // 0x004d798c
            charge(ctx, 3);
            v0 = 2;
            if (a0 == v0) {
                // 0x004d79d4: state 2: CLAMP's two halves when they agree (1 / 3), else 0
                charge(ctx, 5);
                ld(v0, gp, sky::kGpClamp1);
                v1 = v0 & 0x3;
                v0 = v0 & 0xC;
                if (v1 != v0) {
                    // 0x004d7f14
                    charge(ctx, 2);
                    sw(zero, s0, 0);
                    backedge(ctx);
                } else {
                    // 0x004d79e8
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x004d79f8
                        charge(ctx, 3);
                        v0 = 1;
                        sw(v0, s0, 0);
                    } else {
                        // 0x004d79f0
                        charge(ctx, 2);
                        sw(a1, s0, 0);
                    }
                }
                return_1();
                return;
            }
            // 0x004d7998
            charge(ctx, 3);
            v0 = 1;
            if (a0 != v0) {
                // 0x004d79a4: another state: 0
                charge(ctx, 2);
                v0 = 0;
                finish2();
                return;
            }
            // 0x004d79ac: state 1: the current raster (-1 read as 0)
            charge(ctx, 4);
            lw(v1, gp, sky::kGpRaster);
            v0 = si(-1);
            if (v1 == v0) {
                // 0x004d79c4
                charge(ctx, 2);
                v1 = 0;
                sw(v1, s0, 0);
            } else {
                // 0x004d79bc
                charge(ctx, 2);
                sw(v1, s0, 0);
            }
            // 0x004d79cc
            charge(ctx, 2);
            v0 = 1;
            finish2();
            return;
        }
        // 0x004d7ad0: state 9: the filter from the TEX1 shadow (MMAG / MMIN bits 5..8)
        charge(ctx, 5);
        ld(v1, gp, sky::kGpTex1);
        v0 = 352;
        v1 = v1 & 0x1E0;
        if (v1 == v0) {
            // 0x004d7b60
            charge(ctx, 3);
            v0 = 6;
            sw(v0, s0, 0);
            return_1();
            return;
        }
        // 0x004d7ae4
        charge(ctx, 3);
        v0 = 192;
        if (v1 == v0) {
            // 0x004d7b54
            charge(ctx, 3);
            v0 = 5;
            sw(v0, s0, 0);
            return_1();
            return;
        }
        // 0x004d7af0
        charge(ctx, 3);
        v0 = 288;
        if (v1 == v0) {
            // 0x004d7b48
            charge(ctx, 3);
            v0 = 4;
            sw(v0, s0, 0);
            return_1();
            return;
        }
        // 0x004d7afc
        charge(ctx, 3);
        v0 = 128;
        if (v1 == v0) {
            // 0x004d7b3c
            charge(ctx, 3);
            v0 = 3;
            sw(v0, s0, 0);
            return_1();
            return;
        }
        // 0x004d7b08
        charge(ctx, 3);
        v0 = 96;
        if (v1 == v0) {
            // 0x004d7b30
            charge(ctx, 3);
            v0 = 2;
            sw(v0, s0, 0);
            return_1();
            return;
        }
        // 0x004d7b14
        charge(ctx, 2);
        if (v1 == 0) {
            // 0x004d7b24
            charge(ctx, 3);
            v0 = 1;
            sw(v0, s0, 0);
            return_1();
            return;
        }
        // 0x004d7b1c
        charge(ctx, 2);
        v0 = 0;
        // 0x004d7b6c
        charge(ctx, 2);
        ld(ra, sp, 0x10);
    }
    // 0x004d7f50 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4D78B0(EEContext& ctx, u64 state, u64 out) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(state));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(out));
    sub_4D78B0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004EEC20 sub_4EEC20 -- 1016 bytes; leaf frame (no stack)
// sub_4EEC20 [the per-camera VU1 constants]: $a0 the camera (+20 projection: 1 perspective, +96 the frame buffer
// raster, +128 / +132 the near / far clip planes, +136 the z shift, +140 / +144 the view offset). Writes the constant
// block at 0x965950..0x9659F0: near / far splats (0x965950 / 0x965960), the raster size and view offset (0x965980 /
// 0x965990), the screen centres (2048 + raster offset +- size / 2: 0x9659A0 / 0x965A20), the z scale (0x965970,
// -255 / (far - zshift), with the fog far gp-16864 unless gp-16860), the guard-band ranges (0x965910 / 0x965920:
// min(x, 4095 - x) and its reciprocal) and the clip half-sizes + 5 (0x965930 / 0x965940); the projection terms of the
// matrix diagonal; gp-16892 bit 3 set for a parallel camera, cleared for perspective.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4EEC20(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::c_le_s, hg::charge, hg::cond, hg::cvt_s_w, hg::div_s,
          hg::enter, hg::i64, hg::lbu, hg::lh, hg::lui, hg::lw, hg::lwc1, hg::mov_s, hg::mtc1, hg::mul_s, hg::neg_s,
          hg::sb, hg::sra, hg::sub_s, hg::subu, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, gp{ctx, 28};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4};
    // 0x004eec20: $a0 the camera: t3 = its raster
    enter(ctx, 53);  // entry check point + this block's cycles
    lw(t3, a0, rw_camera::kRaster);
    lwc1(f0, a0, rw_camera::kNear);
    t6 = hi(kCamVuBlock + 0x40);
    t7 = hi(kCamVuBlock + 0x50);
    t6 = addiu(t6, lo(kCamVuBlock + 0x40));
    t5 = hi(kCamVuBlock + 0x70);
    t4 = hi(kCamVuBlock + 0x80);
    t2 = hi(sky::kTplClipFog);
    t1 = hi(kCamVuBlock + 0x10);
    t0 = hi(sky::kTplClipCull);
    a3 = hi(kCamVuBlock + 0x30);
    a2 = hi(kCamVuBlock + 0x110);
    swc1(f0, t6, 12);  // 0x96595C
    a1 = hi(kCamVuBlock + 0x90);
    swc1(f0, t6, 8);  // 0x965958
    v1 = hi(kCamVuBlock + 0x60);
    swc1(f0, t6, 4);  // 0x965954
    t7 = addiu(t7, lo(kCamVuBlock + 0x50));
    swc1(f0, t6, 0);  // 0x965950
    t5 = addiu(t5, lo(kCamVuBlock + 0x70));
    lwc1(f0, a0, rw_camera::kFar);
    t4 = addiu(t4, lo(kCamVuBlock + 0x80));
    t2 = addiu(t2, lo(sky::kTplClipFog));
    t1 = addiu(t1, lo(kCamVuBlock + 0x10));
    t0 = addiu(t0, lo(sky::kTplClipCull));
    a3 = addiu(a3, lo(kCamVuBlock + 0x30));
    a2 = addiu(a2, lo(kCamVuBlock + 0x110));
    a1 = addiu(a1, lo(kCamVuBlock + 0x90));
    v1 = addiu(v1, lo(kCamVuBlock + 0x60));
    swc1(f0, t7, 12);  // 0x96596C
    swc1(f0, t7, 8);  // 0x965968
    swc1(f0, t7, 4);  // 0x965964
    swc1(f0, t7, 0);  // 0x965960
    lwc1(f0, t3, rw_raster::kWidth);
    cvt_s_w(f0, f0);
    swc1(f0, t5, 0);  // 0x965980
    lwc1(f0, t3, rw_raster::kHeight);
    cvt_s_w(f0, f0);
    swc1(f0, t5, 4);  // 0x965984
    lwc1(f0, a0, rw_camera::kViewOffsetX);
    swc1(f0, t5, 8);  // 0x965988
    sw(zero, t5, 12);  // 0x96598C
    sw(zero, t4, 0);  // 0x965990
    sw(zero, t4, 4);  // 0x965994
    lwc1(f0, a0, rw_camera::kViewOffsetY);
    swc1(f0, t4, 8);  // 0x965998
    sw(zero, t4, 12);  // 0x96599C
    lh(t5, t3, rw_raster::kOffsetX);
    lw(t4, t3, 0);
    t6 = addiu(t5, 2048);
    lw(t5, t4, 12);
    t4 = sra(t5, 1);
    if (i64(t5) < 0) {
        // 0x004eecf4
        charge(ctx, 2);
        t4 = addiu(t5, 1);
        t4 = sra(t4, 1);
    }
    // 0x004eecfc
    charge(ctx, 4);
    lw(t5, t3, rw_raster::kWidth);
    t6 = subu(t6, t4);
    t4 = sra(t5, 1);
    if (i64(t5) < 0) {
        // 0x004eed0c
        charge(ctx, 2);
        t4 = addiu(t5, 1);
        t4 = sra(t4, 1);
    }
    // 0x004eed14
    charge(ctx, 11);
    t4 = addu(t4, t6);
    mtc1(t4, f0);
    cvt_s_w(f0, f0);
    swc1(f0, a1, 0);
    lh(t5, t3, rw_raster::kOffsetY);
    lw(t4, t3, 0);
    t6 = addiu(t5, 2048);
    lw(t5, t4, 16);
    t4 = sra(t5, 1);
    if (i64(t5) < 0) {
        // 0x004eed40
        charge(ctx, 2);
        t4 = addiu(t5, 1);
        t4 = sra(t4, 1);
    }
    // 0x004eed48
    charge(ctx, 4);
    lw(t5, t3, rw_raster::kHeight);
    t6 = subu(t6, t4);
    t4 = sra(t5, 1);
    if (i64(t5) < 0) {
        // 0x004eed58
        charge(ctx, 2);
        t4 = addiu(t5, 1);
        t4 = sra(t4, 1);
    }
    // 0x004eed60
    charge(ctx, 12);
    t4 = addu(t4, t6);
    sw(zero, a1, 8);
    mtc1(t4, f0);
    sw(zero, a1, 12);
    cvt_s_w(f0, f0);
    swc1(f0, a1, 4);
    lh(t5, t3, rw_raster::kOffsetX);
    lw(t4, t3, 0);
    t6 = addiu(t5, 2048);
    lw(t5, t4, 12);
    t4 = sra(t5, 1);
    if (i64(t5) < 0) {
        // 0x004eed90
        charge(ctx, 2);
        t4 = addiu(t5, 1);
        t4 = sra(t4, 1);
    }
    // 0x004eed98
    charge(ctx, 11);
    t4 = subu(t6, t4);
    mtc1(t4, f0);
    cvt_s_w(f0, f0);
    swc1(f0, a2, 0);
    lh(t5, t3, rw_raster::kOffsetY);
    lw(t4, t3, 0);
    t6 = addiu(t5, 2048);
    lw(t5, t4, 16);
    t4 = sra(t5, 1);
    if (i64(t5) < 0) {
        // 0x004eedc4
        charge(ctx, 2);
        t4 = addiu(t5, 1);
        t4 = sra(t4, 1);
    }
    // 0x004eedcc
    charge(ctx, 8);
    t4 = subu(t6, t4);
    sw(zero, a2, 8);
    mtc1(t4, f0);
    sw(zero, a2, 12);
    cvt_s_w(f0, f0);
    lw(t4, gp, rwb::kGpRenderStateFSet);
    swc1(f0, a2, 4);
    if (t4 == 0) {
        // 0x004eee20
        charge(ctx, 8);
        lwc1(f2, gp, rwb::kGpRenderStateF);
        a2 = flt(-255.0f);
        mtc1(a2, f0);
        swc1(f2, v1, 12);
        lwc1(f1, a0, rw_camera::kZShift);
        sub_s(f1, f2, f1);
        div_s(f0, f0, f1);
        swc1(f0, v1, 8);
    } else {
        // 0x004eedec
        charge(ctx, 13);
        lwc1(f1, a0, rw_camera::kFar);
        a2 = flt(-255.0f);
        mtc1(a2, f0);
        swc1(f1, v1, 12);
        lwc1(f2, a0, rw_camera::kFar);
        lwc1(f1, a0, rw_camera::kZShift);
        sub_s(f1, f2, f1);
        div_s(f0, f0, f1);
        swc1(f0, v1, 8);
    }
    // 0x004eee40: the projection terms (near / far)
    charge(ctx, 15);
    lwc1(f4, a0, rw_camera::kFar);
    v1 = flt(1.0f);
    lwc1(f3, a0, rw_camera::kNear);
    mtc1(v1, f0);
    lwc1(f2, a1, 0);
    v1 = 0x457F0000;
    v1 = v1 | 0xFF00;
    mtc1(v1, f1);
    sub_s(f3, f4, f3);
    div_s(f0, f0, f3);
    sub_s(f1, f1, f2);
    c_le_s(f2, f1);
    if (!cond(ctx)) {
        // 0x004eee84
        charge(ctx, 2);
        mov_s(f2, f1);
        v1 = 0x3F800000;
    } else {
        // 0x004eee7c
        charge(ctx, 2);
        v1 = flt(1.0f);
    }
    // 0x004eee8c
    charge(ctx, 13);
    mtc1(v1, f1);
    lwc1(f3, a1, 4);
    div_s(f1, f1, f2);
    v1 = 0x457F0000;
    v1 = v1 | 0xFF00;
    swc1(f1, t2, 4);
    mtc1(v1, f1);
    swc1(f2, t2, 0);
    lwc1(f2, a0, rw_camera::kFar);
    sub_s(f1, f1, f3);
    c_le_s(f3, f1);
    swc1(f2, t2, 12);
    if (!cond(ctx)) {
        // 0x004eeec8
        charge(ctx, 2);
        mov_s(f3, f1);
        v1 = 0x3F800000;
    } else {
        // 0x004eeec0
        charge(ctx, 2);
        v1 = flt(1.0f);
    }
    // 0x004eeed0
    charge(ctx, 45);
    mtc1(v1, f2);
    swc1(f3, t1, 0);
    div_s(f1, f2, f3);
    v1 = 1;
    swc1(f1, t1, 4);
    lwc1(f1, a0, rw_camera::kNear);
    swc1(f1, t1, 12);
    lw(a1, t3, rw_raster::kWidth);
    a1 = sra(a1, 1);
    a1 = addiu(a1, 5);
    mtc1(a1, f1);
    cvt_s_w(f1, f1);
    swc1(f1, t0, 0);
    lw(a1, t3, rw_raster::kWidth);
    a1 = sra(a1, 1);
    a1 = addiu(a1, 5);
    mtc1(a1, f1);
    cvt_s_w(f1, f1);
    div_s(f1, f2, f1);
    swc1(f1, t0, 4);
    lwc1(f1, a0, rw_camera::kFar);
    swc1(f1, t0, 12);
    lw(a1, t3, rw_raster::kHeight);
    a1 = sra(a1, 1);
    a1 = addiu(a1, 5);
    mtc1(a1, f1);
    cvt_s_w(f1, f1);
    swc1(f1, a3, 0);
    lw(a1, t3, rw_raster::kHeight);
    a1 = sra(a1, 1);
    a1 = addiu(a1, 5);
    mtc1(a1, f1);
    cvt_s_w(f1, f1);
    div_s(f1, f2, f1);
    swc1(f1, a3, 4);
    lwc1(f1, a0, rw_camera::kNear);
    swc1(f1, a3, 12);
    lw(a1, a0, rw_camera::kProjection);
    if (a1 != v1) {
        // 0x004eefd0: parallel: gp-16892 bit 3 set
        charge(ctx, 16);
        a1 = flt(2.0f);
        lbu(v1, gp, sky::kGpCamFlags);
        mtc1(a1, f1);
        neg_s(f2, f0);
        lwc1(f4, a0, rw_camera::kFar);
        lwc1(f3, a0, rw_camera::kNear);
        mul_s(f0, f1, f0);
        v1 = v1 | 0x8;
        add_s(f1, f4, f3);
        sb(v1, gp, sky::kGpCamFlags);
        mul_s(f1, f2, f1);
        swc1(f1, t0, 8);
        swc1(f1, t2, 8);
        swc1(f0, a3, 8);
        swc1(f0, t1, 8);
    } else {
        // 0x004eef84: perspective: bit 3 cleared
        charge(ctx, 19);
        lwc1(f2, a0, rw_camera::kFar);
        a1 = flt(-2.0f);
        mtc1(a1, f3);
        lbu(v1, gp, sky::kGpCamFlags);
        lwc1(f1, a0, rw_camera::kNear);
        mul_s(f2, f3, f2);
        v1 = v1 & 0xF7;
        mul_s(f1, f2, f1);
        mul_s(f1, f0, f1);
        swc1(f1, t0, 8);
        swc1(f1, t2, 8);
        lwc1(f2, a0, rw_camera::kFar);
        lwc1(f1, a0, rw_camera::kNear);
        add_s(f1, f2, f1);
        sb(v1, gp, sky::kGpCamFlags);
        mul_s(f0, f0, f1);
        swc1(f0, a3, 8);
        swc1(f0, t1, 8);
    }
    // 0x004ef010 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_4EEC20(EEContext& ctx, u64 camera) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(camera));
    sub_4EEC20(ctx);
}

// 0x004EF020 skyFillInPktForUpLoadAlignedContiguousRectangle -- 428 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// skyFillInPktForUpLoadAlignedContiguousRectangle(packet, address, bytes): builds, at the packet rounded up to 64
// bytes, the PATH2 upload chain of `bytes` (rounded to qwords) from guest `address`: per chunk of at most 0x7FEE
// qwords a `cnt` tag + NOP/DIRECT pair {DIRECT 0x50000000 | qwc, FLUSH...} and a `ref` tag to the data (0x30000000 |
// qwc, address advanced by 0x7FEE0 per chunk); then the closing `cnt` + the IMAGE-end GIF tag (A+D TEXFLUSH, the
// template quadword at 0x965A40). Writes the data cache back (SyncDCache(start, end + 127)); returns the packet.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void skyFillInPktForUpLoadAlignedContiguousRectangle(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::daddiu, hg::dsll32, hg::dsra32,
          hg::dsrl, hg::dsrl32, hg::enter, hg::ld, hg::link, hg::lq, hg::lui, hg::mfhi, hg::mult, hg::pcpyld, hg::sd,
          hg::si, hg::sll, hg::slt, hg::slti, hg::sq, hg::sra, hg::srl;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ef020
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = daddiu(a2, 15);
    v0 = dsrl(v0, 4);
    sd(ra, sp, 0x20);
    t4 = dsll32(v0, 0);
    a2 = 0x50000000;
    sq(s1, sp, 0x10);
    v1 = a2 | 0x1;
    v0 = 0x10000000;
    sq(s0, sp, 0x0);
    v1 = dsll32(v1, 0);
    v0 = v0 | 0x1;
    pcpyld(t2, v1, v0);
    s0 = a0;
    v0 = si(-64);
    v1 = addiu(s0, 63);
    t4 = dsra32(t4, 0);
    a0 = v1 & v0;
    a3 = addiu(t4, 32749);
    v0 = lui(0x8012);
    t5 = 0;
    v0 = v0 | 0x289;
    t3 = a0;
    mult(zero, v0, a3);
    v1 = srl(a3, 31);
    mfhi(v0);
    v0 = addu(v0, a3);
    v0 = sra(v0, 14);
    v1 = addu(v0, v1);
    at = slt(0, v1);
    if (at != 0) {
        // 0x004ef0a4: the chunks of at most 0x7FEE qwords
        charge(ctx, 3);
        at = slt(0, v1);
        a3 = 0;
        if (at != 0) {
            // 0x004ef0b0
            charge(ctx, 6);
            v0 = 0x8000000;
            t1 = 0x70000;
            t0 = 3;
            t6 = 32750;
            v0 = dsll32(v0, 0);
            t7 = t1 | 0xFEE0;
            for (;;) {
                // 0x004ef0c8: one chunk: a cnt tag + NOP / DIRECT, a ref tag to the data
                charge(ctx, 3);
                at = slti(t4, 32751);
                sq(t2, t3, 0);
                if (at == 0) {
                    // 0x004ef1a8
                    charge(ctx, 3);
                    t1 = t6;
                    s1 = 0;
                    backedge(ctx);
                } else {
                    // 0x004ef0d4
                    charge(ctx, 3);
                    t1 = t4;
                    s1 = 0;
                }
                // 0x004ef0e0
                charge(ctx, 27);
                s1 = sll(s1, 15);
                t8 = t1 | s1;
                t5 = addiu(t5, 1);
                t8 = dsll32(t8, 0);
                s1 = dsll32(t1, 0);
                t8 = dsrl32(t8, 0);
                s1 = dsrl32(s1, 0);
                t8 = t8 | v0;
                s1 = s1 | a2;
                pcpyld(t8, a3, t8);
                sq(t8, t3, 16);
                s1 = dsll32(s1, 0);
                t8 = dsll32(a1, 0);
                t4 = addiu(t4, -32750);
                t8 = dsrl32(t8, 0);
                a1 = addu(a1, t7);
                t9 = dsll32(t8, 0);
                t8 = sll(t0, 28);
                t1 = t1 | t8;
                t1 = dsll32(t1, 0);
                t1 = dsrl32(t1, 0);
                t1 = t9 | t1;
                pcpyld(t1, s1, t1);
                sq(t1, t3, 32);
                t1 = slt(t5, v1);
                t3 = addiu(t3, 48);
                if (t1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004ef14c
            charge(ctx, 1);
        }
    }
    // 0x004ef150: the closing cnt and the IMAGE-end GIF tag; the data cache written back
    charge(ctx, 22);
    v0 = 0x50000000;
    v1 = v0 | 0x2;
    a2 = 14;
    v0 = 0x60000000;
    v1 = dsll32(v1, 0);
    v0 = v0 | 0x2;
    pcpyld(v0, v1, v0);
    sq(v0, t3, 0);
    v1 = 0x8001;
    v0 = 0x10000000;
    a1 = dsll32(v0, 0);
    a1 = v1 | a1;
    v0 = hi(kUploadTpl + 0x0);
    pcpyld(a1, a2, a1);
    sq(a1, t3, 16);
    v1 = addiu(t3, 48);
    lq(v0, v0, lo(kUploadTpl + 0x0));
    a1 = addiu(v1, 127);
    link(ctx, 0x4EF198u);  // $ra first: the delay slot below depends on it
    sq(v0, t3, 32);
    call(ctx, gen::fn_SyncDCache_00503a58);
    v0 = s0;
    // 0x004ef1b8
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 skyFillInPktForUpLoadAlignedContiguousRectangle(EEContext& ctx, u64 packet, u64 address, u64 bytes) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(packet));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(address));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(bytes));
    skyFillInPktForUpLoadAlignedContiguousRectangle(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004EF770 sub_4EF770 -- 640 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4EF770 [the texture upload through PATH3, by rows]: $a0 width, $a1 rows, $a2 the first row's address, $a3 the
// destination TBP, $t0 TBW, $t1 the bits per pixel, $t2 PSM, $t3 the row stride. Opens a GIF packet of 10 qwords
// (_rwDMAOpenGIFPkt), reserves (rows + 1) * 48 bytes of DMA space (sub_4D5FE0) for the reference chain, reopens; the
// header: a `cnt` with BITBLTBUF / TRXPOS / TRXREG / TRXDIR (templates at 0x965A50 / 0x965A40 / 0x965A60 / 0x965A70,
// TRXREG = (qwc * 128 / bpp) x rows through __udivdi3); then per row {cnt + DIRECT, IMAGE tag, ref to the row}, the
// closing IMAGE-end, SyncDCache over the chain.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void sub_4EF770(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::dsll, hg::dsll32, hg::dsra32,
          hg::dsrl32, hg::enter, hg::jal, hg::ld, hg::link, hg::lq, hg::lw, hg::lwu, hg::mult, hg::pcpyld, hg::sd,
          hg::sll, hg::sltu, hg::sq, hg::srl, hg::sw;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x004ef770
    enter(ctx, 102);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    v1 = 0x50000000;
    sd(ra, sp, 0x90);
    v0 = 0x10000000;
    sq(fp, sp, 0x80);
    v1 = v1 | 0x1;
    sq(s7, sp, 0x70);
    v0 = v0 | 0x1;
    sq(s6, sp, 0x60);
    v1 = dsll32(v1, 0);
    sq(s5, sp, 0x50);
    s7 = a3;
    sq(s4, sp, 0x40);
    s5 = t1;
    sq(s3, sp, 0x30);
    s4 = a1;
    sq(s2, sp, 0x20);
    s3 = a2;
    sq(s1, sp, 0x10);
    fp = t0;
    sq(s0, sp, 0x0);
    s2 = t3;
    pcpyld(s0, v1, v0);
    sw(t2, sp, 0xAC);
    mult(v0, a0, s5);
    v0 = srl(v0, 3);
    a0 = 10;
    v0 = addiu(v0, 15);
    v0 = srl(v0, 4);
    s6 = dsll32(v0, 0);
    s6 = dsrl32(s6, 0);
    jal(ctx, 0x4EF7E8u, gen::fn__rwDMAOpenGIFPkt_004d54e0);
    v1 = addiu(s4, 1);
    a1 = 0;
    v0 = sll(v1, 1);
    v0 = addu(v0, v1);
    a0 = sll(v0, 4);
    jal(ctx, 0x4EF800u, gen::fn_sub_4D5FE0_004d5fe0);
    s1 = v0;
    a0 = 10;
    jal(ctx, 0x4EF80Cu, gen::fn__rwDMAOpenGIFPkt_004d54e0);
    lwu(v0, sp, 0xAC);
    a1 = dsll32(s5, 0);
    a0 = dsll32(s1, 0);
    lw(s5, gp, rwb::kGpSprWritePtr);
    a0 = dsrl32(a0, 0);
    a2 = hi(kUploadTpl + 0x0);
    a0 = dsll32(a0, 0);
    a1 = dsrl32(a1, 0);
    v1 = v0;
    v0 = s7 & 0x3FFF;
    t0 = dsll32(v1, 24);
    t1 = dsll32(v0, 0);
    v1 = dsll(v1, 24);
    v0 = dsll32(fp, 0);
    v0 = dsrl32(v0, 0);
    a3 = dsll32(v0, 16);
    v0 = 0x50000000;
    a3 = t0 | a3;
    v0 = v0 | 0x6;
    t1 = t1 | a3;
    v0 = a0 | v0;
    t1 = v1 | t1;
    a0 = 0;
    t0 = 0xA0000;
    pcpyld(v0, a0, v0);
    a0 = hi(kUploadTpl + 0x30);
    sq(v0, s5, 0);
    lq(v0, a0, lo(kUploadTpl + 0x30));
    a3 = 80;
    t0 = t1 | t0;
    v1 = hi(kUploadTpl + 0x10);
    pcpyld(a3, a3, t0);
    sq(v0, s5, 16);
    a0 = dsll(s6, 7);
    lq(v0, a2, lo(kUploadTpl + 0x0));
    sq(v0, s5, 32);
    sq(a3, s5, 48);
    lq(v0, v1, lo(kUploadTpl + 0x10));
    link(ctx, 0x4EF8ACu);  // $ra first: the delay slot below depends on it
    sq(v0, s5, 64);
    call(ctx, gen::fn___udivdi3_0052fe98);
    v1 = dsll32(v0, 0);
    at = sltu(0, s4);
    v1 = dsra32(v1, 0);
    v0 = dsll32(s4, 0);
    v0 = dsrl32(v0, 0);
    v1 = dsll32(v1, 0);
    v1 = dsrl32(v1, 0);
    v0 = dsll32(v0, 0);
    v1 = v0 | v1;
    v0 = 82;
    pcpyld(v0, v0, v1);
    sq(v0, s5, 80);
    v1 = 0;
    v0 = hi(kUploadTpl + 0x20);
    lq(a0, v0, lo(kUploadTpl + 0x20));
    sq(a0, s5, 96);
    v0 = s1;
    lw(a0, gp, rwb::kGpSprWritePtr);
    a0 = addiu(a0, 112);
    sw(a0, gp, rwb::kGpSprWritePtr);
    if (at != 0) {
        // 0x004ef908: per row: cnt + DIRECT, the IMAGE tag, a ref to the row
        charge(ctx, 6);
        a0 = 0x50000000;
        at = sltu(0, s4);
        a0 = s6 | a0;
        t0 = 0;
        a3 = dsll32(a0, 0);
        if (at != 0) {
            // 0x004ef920
            charge(ctx, 6);
            a1 = 0x8000000;
            a0 = 0x30000000;
            a2 = dsll32(a1, 0);
            a1 = s6 | a0;
            a0 = s6 | a2;
            pcpyld(a2, t0, a0);
            for (;;) {
                // 0x004ef938
                charge(ctx, 13);
                a0 = dsll32(s3, 0);
                sq(s0, v0, 0);
                a0 = dsrl32(a0, 0);
                sq(a2, v0, 16);
                a0 = dsll32(a0, 0);
                v1 = addiu(v1, 1);
                a0 = a0 | a1;
                s3 = addu(s3, s2);
                pcpyld(a0, a3, a0);
                sq(a0, v0, 32);
                a0 = sltu(v1, s4);
                v0 = addiu(v0, 48);
                if (a0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004ef96c
            charge(ctx, 1);
        }
    }
    // 0x004ef970: the closing IMAGE-end; the chain written back (SyncDCache)
    charge(ctx, 32);
    a1 = 0x50000000;
    a2 = a1 | 0x2;
    v1 = 0x10000000;
    a3 = dsll32(a2, 0);
    a1 = v1 | 0x2;
    a2 = dsll32(v1, 0);
    a0 = s1;
    pcpyld(v1, a3, a1);
    a1 = 0x8001;
    sq(v1, v0, 0);
    a2 = a1 | a2;
    a3 = 14;
    pcpyld(a2, a3, a2);
    v1 = hi(kUploadTpl + 0x0);
    sq(a2, v0, 16);
    lq(v1, v1, lo(kUploadTpl + 0x0));
    a1 = addiu(v0, 48);
    a1 = addiu(a1, 127);
    link(ctx, 0x4EF9B8u);  // $ra first: the delay slot below depends on it
    sq(v1, v0, 32);
    call(ctx, gen::fn_SyncDCache_00503a58);
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

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_4EF770(EEContext& ctx, u64 width, u64 rows, u64 address, u64 tbp) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(width));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(rows));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(address));
    ee::core::set_gpr64(ctx, GPR_A3, static_cast<u64>(tbp));
    sub_4EF770(ctx);
}

// 0x004DD480 sub_4DD480 -- 636 bytes; frame 0x10B0: s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4DD480 [swizzle a PSMT8 raster in place]: per band the four rows are read as quadwords (rows r and r + 2 through
// the HI/LO pipes 0 and 1: two mult / mult1 per pair), each of their 64 bytes stored at its shuffled place in the
// frame buffer at sp + 176 (16-byte columns, 1 KiB per row), then the four 1 KiB rows written back over the band.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: frame/spills (own frame)).
void sub_4DD480(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lbu, hg::lq, hg::lw, hg::mult,
          hg::mult1, hg::nor, hg::sb, hg::sll, hg::slt, hg::slti, hg::sq, hg::sra;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x004dd480
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10B0);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, rw_raster::kHeight);
    at = slt(0, v1);
    t7 = 0;
    if (at != 0) {
        // 0x004dd4b0: per band of four rows
        charge(ctx, 3);
        at = slt(0, v1);
        t4 = addiu(sp, 0x70);
        if (at != 0) {
            // 0x004dd4bc
            charge(ctx, 4);
            t3 = addiu(sp, 0x80);
            t2 = addiu(sp, 0x90);
            t1 = addiu(sp, 0xA0);
            s1 = addiu(sp, 0xB0);
            for (;;) {
                // 0x004dd4cc: per 16-byte column of the band
                charge(ctx, 4);
                lw(t5, a0, rw_raster::kWidth);
                at = slt(0, t5);
                t8 = 0;
                if (at != 0) {
                    // 0x004dd4dc
                    charge(ctx, 5);
                    lw(a3, a0, rw_raster::kStride);
                    t6 = 0;
                    lw(a2, a0, rw_raster::kPixels);
                    t0 = t7 & 0x4;
                    a1 = addiu(t7, 2);
                    for (;;) {
                        // 0x004dd4f0: the four rows' quadwords (rows r / r + 2 through the HI/LO pipes 0 / 1)
                        charge(ctx, 24);
                        mult(v1, t7, a3);
                        v1 = addu(a2, v1);
                        v1 = addu(v1, t6);
                        lq(v1, v1, 0);
                        sq(v1, sp, 0x70);
                        mult1(v1, t7, a3);
                        v1 = addu(a2, v1);
                        v1 = addu(v1, t6);
                        lq(v1, v1, 16);
                        sq(v1, t3, 0);
                        mult(v1, a1, a3);
                        v1 = addu(a2, v1);
                        v1 = addu(v1, t6);
                        lq(v1, v1, 0);
                        sq(v1, t2, 0);
                        mult1(v1, a1, a3);
                        s0 = 0;
                        v1 = addu(a2, v1);
                        t5 = addu(v1, t6);
                        lq(t5, t5, 16);
                        v1 = addu(t8, sp);
                        v1 = addiu(v1, 176);
                        sq(t5, t1, 0);
                        for (;;) {
                            // 0x004dd550
                            charge(ctx, 2);
                            t9 = 0;
                            t5 = addu(t4, s0);
                            for (;;) {
                                // 0x004dd558: each of the 64 bytes to its shuffled place in the frame buffer (sp +
                                // 0xB0)
                                charge(ctx, 2);
                                if (t0 == 0) {
                                    // 0x004dd5c0
                                    charge(ctx, 20);
                                    s4 = addu(s0, t9);
                                    s2 = s4 & 0x2;
                                    s5 = s4 & 0x4;
                                    s6 = sra(s5, 2);
                                    s2 = sll(s2, 2);
                                    s5 = s4 & 0x8;
                                    s6 = s2 | s6;
                                    s2 = sra(s5, 2);
                                    s3 = s4 & 0x1;
                                    s5 = s4 & 0x10;
                                    s2 = s2 | s6;
                                    s5 = sra(s5, 2);
                                    s4 = s4 & 0x20;
                                    s5 = s5 | s2;
                                    s2 = sra(s4, 1);
                                    s5 = s2 | s5;
                                    s4 = sll(s3, 5);
                                    s2 = sll(s3, 2);
                                    s2 = s4 | s2;
                                    s4 = s5 ^ s2;
                                } else {
                                    // 0x004dd560
                                    charge(ctx, 23);
                                    s4 = addu(s0, t9);
                                    s3 = s4 & 0x2;
                                    s2 = s4 & 0x4;
                                    s3 = sll(s3, 2);
                                    s2 = sra(s2, 2);
                                    s5 = s3 | s2;
                                    s2 = s4 & 0x8;
                                    s3 = sra(s2, 2);
                                    s2 = s4 & 0x10;
                                    s3 = s3 | s5;
                                    s2 = sra(s2, 2);
                                    s5 = s2 | s3;
                                    s2 = s4 & 0x20;
                                    s3 = sra(s2, 1);
                                    s2 = s4 & 0x1;
                                    s3 = s3 | s5;
                                    s4 = nor(s4, 0);
                                    s2 = sll(s2, 5);
                                    s4 = s4 & 0x1;
                                    s4 = sll(s4, 2);
                                    s2 = s2 | s4;
                                    s4 = s3 ^ s2;
                                }
                                // 0x004dd610
                                charge(ctx, 11);
                                lbu(s2, t5, 0);
                                s3 = sra(s4, 4);
                                t9 = addiu(t9, 1);
                                s3 = sll(s3, 10);
                                s4 = s4 & 0xF;
                                s5 = addu(v1, s3);
                                s4 = addu(s5, s4);
                                s3 = slti(t9, 16);
                                sb(s2, s4, 0);
                                t5 = addiu(t5, 1);
                                if (s3 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004dd63c
                            charge(ctx, 4);
                            s0 = addiu(s0, 16);
                            t5 = slti(s0, 64);
                            if (t5 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004dd64c
                        charge(ctx, 5);
                        lw(t5, a0, rw_raster::kWidth);
                        t8 = addiu(t8, 16);
                        v1 = slt(t8, t5);
                        t6 = addiu(t6, 32);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x004dd660: the four 1 KiB rows written back over the band
                charge(ctx, 2);
                s0 = 0;
                t6 = s1;
                for (;;) {
                    // 0x004dd668
                    charge(ctx, 3);
                    at = slt(0, t5);
                    t0 = 0;
                    if (at != 0) {
                        // 0x004dd674
                        charge(ctx, 1);
                        a3 = addu(t7, s0);
                        for (;;) {
                            // 0x004dd678
                            charge(ctx, 13);
                            v1 = addu(t6, t0);
                            lq(a2, v1, 0);
                            lw(v1, a0, rw_raster::kStride);
                            mult(a1, v1, a3);
                            lw(v1, a0, rw_raster::kPixels);
                            v1 = addu(v1, a1);
                            v1 = addu(v1, t0);
                            sq(a2, v1, 0);
                            t0 = addiu(t0, 16);
                            lw(t5, a0, rw_raster::kWidth);
                            v1 = slt(t0, t5);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004dd6ac
                        charge(ctx, 1);
                    }
                    // 0x004dd6b0
                    charge(ctx, 4);
                    s0 = addiu(s0, 1);
                    v1 = slti(s0, 4);
                    t6 = addiu(t6, 1024);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004dd6c0
                charge(ctx, 5);
                lw(v1, a0, rw_raster::kHeight);
                t7 = addiu(t7, 4);
                v1 = slt(t7, v1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004dd6d4
            charge(ctx, 1);
        }
    }
    // 0x004dd6d8 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x10B0);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_4DD480(EEContext& ctx, u64 lock) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(lock));
    sub_4DD480(ctx);
}

// 0x004DD700 sub_4DD700 -- 916 bytes; frame 0x890: s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4DD700 [swizzle a PSMT4 raster in place]: as sub_4DD480 with nibbles: per 32-byte column the 128 nibbles of the
// band's four rows are ORed into the cleared 2 KiB frame buffer at sp + 144 (512-byte rows) at their shuffled places
// (high / low nibble by the parities of the source and the destination), then written back.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4DD700(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lbu, hg::lq, hg::lw, hg::mult,
          hg::mult1, hg::nor, hg::sb, hg::sd, hg::sll, hg::slt, hg::slti, hg::sq, hg::sra;
    Gpr zero{ctx, 0}, at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x004dd700
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x890);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, rw_raster::kHeight);
    at = slt(0, v1);
    t8 = 0;
    if (at != 0) {
        // 0x004dd728: per band of four rows
        charge(ctx, 3);
        at = slt(0, v1);
        t5 = addiu(sp, 0x50);
        if (at != 0) {
            // 0x004dd734
            charge(ctx, 4);
            t4 = addiu(sp, 0x60);
            t3 = addiu(sp, 0x70);
            t2 = addiu(sp, 0x80);
            v1 = addiu(sp, 0x90);
            for (;;) {
                // 0x004dd744: per 32-byte column of the band
                charge(ctx, 4);
                lw(a1, a0, rw_raster::kWidth);
                at = slt(0, a1);
                t9 = 0;
                if (at != 0) {
                    // 0x004dd754
                    charge(ctx, 5);
                    lw(t0, a0, rw_raster::kStride);
                    t7 = 0;
                    lw(a3, a0, rw_raster::kPixels);
                    t1 = t8 & 0x4;
                    a2 = addiu(t8, 2);
                    for (;;) {
                        // 0x004dd768
                        charge(ctx, 44);
                        mult(a1, t8, t0);
                        a1 = addu(a3, a1);
                        a1 = addu(a1, t9);
                        lq(a1, a1, 0);
                        sq(a1, sp, 0x50);
                        mult1(a1, t8, t0);
                        a1 = addu(a3, a1);
                        a1 = addu(a1, t9);
                        lq(a1, a1, 16);
                        sq(a1, t4, 0);
                        mult(a1, a2, t0);
                        a1 = addu(a3, a1);
                        a1 = addu(a1, t9);
                        lq(a1, a1, 0);
                        sq(a1, t3, 0);
                        mult1(a1, a2, t0);
                        s2 = 0;
                        t6 = addu(a3, a1);
                        a1 = addu(t7, sp);
                        sd(zero, a1, 144);
                        a1 = addu(t6, t9);
                        lq(s0, a1, 16);
                        a1 = addiu(t7, 8);
                        sq(s0, t2, 0);
                        t6 = addu(a1, sp);
                        a1 = addiu(t7, 512);
                        sd(zero, t6, 144);
                        a1 = addu(a1, sp);
                        sd(zero, a1, 144);
                        a1 = addiu(t7, 520);
                        t6 = addu(a1, sp);
                        a1 = addiu(t7, 1024);
                        sd(zero, t6, 144);
                        t6 = addu(a1, sp);
                        a1 = addiu(t7, 1032);
                        sd(zero, t6, 144);
                        a1 = addu(a1, sp);
                        sd(zero, a1, 144);
                        a1 = addiu(t7, 1536);
                        t6 = addu(a1, sp);
                        a1 = addiu(t7, 1544);
                        sd(zero, t6, 144);
                        a1 = addu(a1, sp);
                        sd(zero, a1, 144);
                        for (;;) {
                            // 0x004dd818
                            charge(ctx, 1);
                            s1 = 0;
                            for (;;) {
                                // 0x004dd81c: each of the 128 nibbles ORed into its shuffled place (sp + 0x90)
                                charge(ctx, 2);
                                if (t1 == 0) {
                                    // 0x004dd88c
                                    charge(ctx, 23);
                                    t6 = addu(s2, s1);
                                    s0 = t6 & 0x2;
                                    a1 = t6 & 0x1;
                                    s4 = sll(s0, 2);
                                    s0 = t6 & 0x20;
                                    s3 = sra(s0, 1);
                                    s0 = t6 & 0x4;
                                    s3 = s4 | s3;
                                    s0 = sra(s0, 2);
                                    s4 = s0 | s3;
                                    s0 = t6 & 0x8;
                                    s3 = sra(s0, 2);
                                    s0 = t6 & 0x10;
                                    s3 = s3 | s4;
                                    s0 = sra(s0, 2);
                                    s4 = s0 | s3;
                                    s0 = t6 & 0x40;
                                    s3 = sra(s0, 1);
                                    s0 = sll(a1, 6);
                                    s3 = s3 | s4;
                                    a1 = sll(a1, 2);
                                    a1 = s0 | a1;
                                    s0 = s3 ^ a1;
                                } else {
                                    // 0x004dd824
                                    charge(ctx, 26);
                                    t6 = addu(s2, s1);
                                    s0 = t6 & 0x2;
                                    a1 = t6 & 0x20;
                                    s0 = sll(s0, 2);
                                    a1 = sra(a1, 1);
                                    s3 = s0 | a1;
                                    a1 = t6 & 0x4;
                                    s0 = sra(a1, 2);
                                    a1 = t6 & 0x8;
                                    s0 = s0 | s3;
                                    a1 = sra(a1, 2);
                                    s3 = a1 | s0;
                                    a1 = t6 & 0x10;
                                    s0 = sra(a1, 2);
                                    a1 = t6 & 0x40;
                                    s0 = s0 | s3;
                                    a1 = sra(a1, 1);
                                    a1 = a1 | s0;
                                    s0 = t6 & 0x1;
                                    s3 = sll(s0, 6);
                                    s0 = nor(t6, 0);
                                    s0 = s0 & 0x1;
                                    s0 = sll(s0, 2);
                                    s0 = s3 | s0;
                                    s0 = a1 ^ s0;
                                }
                                // 0x004dd8e8
                                charge(ctx, 3);
                                a1 = s0 & 0x1;
                                if (a1 == 0) {
                                    // 0x004dd958
                                    charge(ctx, 3);
                                    a1 = s1 & 0x1;
                                    if (a1 == 0) {
                                        // 0x004dd97c
                                        charge(ctx, 4);
                                        a1 = sra(t6, 1);
                                        a1 = addu(t5, a1);
                                        lbu(a1, a1, 0);
                                        a1 = a1 & 0xF;
                                    } else {
                                        // 0x004dd964
                                        charge(ctx, 6);
                                        a1 = sra(t6, 1);
                                        a1 = addu(t5, a1);
                                        lbu(a1, a1, 0);
                                        a1 = a1 & 0xF0;
                                        a1 = sra(a1, 4);
                                    }
                                    // 0x004dd98c
                                    charge(ctx, 11);
                                    t6 = sra(s0, 5);
                                    a1 = a1 & 0xFF;
                                    s3 = sll(t6, 10);
                                    t6 = s0 & 0x1F;
                                    t6 = addu(t9, t6);
                                    t6 = addu(s3, t6);
                                    t6 = sra(t6, 1);
                                    s0 = addu(t6, sp);
                                    lbu(t6, s0, 144);
                                    a1 = t6 | a1;
                                    sb(a1, s0, 144);
                                } else {
                                    // 0x004dd8f4
                                    charge(ctx, 3);
                                    a1 = s1 & 0x1;
                                    if (a1 == 0) {
                                        // 0x004dd914
                                        charge(ctx, 5);
                                        a1 = sra(t6, 1);
                                        a1 = addu(t5, a1);
                                        lbu(a1, a1, 0);
                                        a1 = a1 & 0xF;
                                        a1 = sll(a1, 4);
                                    } else {
                                        // 0x004dd900
                                        charge(ctx, 5);
                                        a1 = sra(t6, 1);
                                        a1 = addu(t5, a1);
                                        lbu(a1, a1, 0);
                                        a1 = a1 & 0xF0;
                                    }
                                    // 0x004dd928
                                    charge(ctx, 12);
                                    t6 = sra(s0, 5);
                                    a1 = a1 & 0xFF;
                                    s3 = sll(t6, 10);
                                    t6 = s0 & 0x1F;
                                    t6 = addu(t9, t6);
                                    t6 = addu(s3, t6);
                                    t6 = sra(t6, 1);
                                    s0 = addu(t6, sp);
                                    lbu(t6, s0, 144);
                                    a1 = t6 | a1;
                                    sb(a1, s0, 144);
                                }
                                // 0x004dd9b8
                                charge(ctx, 4);
                                s1 = addiu(s1, 1);
                                a1 = slti(s1, 32);
                                if (a1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004dd9c8
                            charge(ctx, 4);
                            s2 = addiu(s2, 32);
                            a1 = slti(s2, 128);
                            if (a1 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004dd9d8
                        charge(ctx, 5);
                        lw(a1, a0, rw_raster::kWidth);
                        t9 = addiu(t9, 32);
                        t6 = slt(t9, a1);
                        t7 = addiu(t7, 16);
                        if (t6 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x004dd9ec: the four 512-byte rows written back over the band
                charge(ctx, 2);
                a3 = 0;
                a2 = v1;
                for (;;) {
                    // 0x004dd9f4
                    charge(ctx, 4);
                    t0 = sra(a1, 1);
                    at = slt(0, t0);
                    t7 = 0;
                    if (at == 0) {
                        // 0x004dda50
                        charge(ctx, 1);
                        a3 = addiu(a3, 1);
                    } else {
                        // 0x004dda04
                        charge(ctx, 1);
                        t6 = addu(t8, a3);
                        for (;;) {
                            // 0x004dda08
                            charge(ctx, 14);
                            a1 = addu(a2, t7);
                            lq(t1, a1, 0);
                            lw(a1, a0, rw_raster::kStride);
                            mult(t0, a1, t6);
                            lw(a1, a0, rw_raster::kPixels);
                            a1 = addu(a1, t0);
                            a1 = addu(a1, t7);
                            sq(t1, a1, 0);
                            t7 = addiu(t7, 16);
                            lw(a1, a0, rw_raster::kWidth);
                            t0 = sra(a1, 1);
                            t0 = slt(t7, t0);
                            if (t0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004dda40
                        charge(ctx, 2);
                        a3 = addiu(a3, 1);
                    }
                    // 0x004dda54
                    charge(ctx, 3);
                    t0 = slti(a3, 4);
                    a2 = addiu(a2, 512);
                    if (t0 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004dda60
                charge(ctx, 5);
                lw(a1, a0, rw_raster::kHeight);
                t8 = addiu(t8, 4);
                a1 = slt(t8, a1);
                if (a1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004dda74
            charge(ctx, 2);
            backedge(ctx);
        }
    }
    // 0x004dda48
    charge(ctx, 2);
    lq(s4, sp, 0x40);
    // 0x004dda7c
    charge(ctx, 6);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x890);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_4DD700(EEContext& ctx, u64 lock) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(lock));
    sub_4DD700(ctx);
}

// 0x004DDAA0 sub_4DDAA0 -- 644 bytes; frame 0x1090: s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4DDAA0 [unswizzle a PSMT8 raster in place]: per band the four rows go to the 4 KiB frame buffer at sp + 144
// (1 KiB per row), then each 16-byte column of the band is gathered from its shuffled places into sp + 80 .. + 143
// and written back as the four rows' quadwords (rows r / r + 2 through the HI/LO pipes 0 and 1).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: frame/spills (own frame)).
void sub_4DDAA0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lbu, hg::lq, hg::lw, hg::mult,
          hg::mult1, hg::nor, hg::sb, hg::sll, hg::slt, hg::slti, hg::sq, hg::sra;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x004ddaa0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x1090);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, rw_raster::kHeight);
    at = slt(0, v1);
    t9 = 0;
    if (at != 0) {
        // 0x004ddac8: per band of four rows
        charge(ctx, 3);
        at = slt(0, v1);
        t5 = addiu(sp, 0x50);
        if (at != 0) {
            // 0x004ddad4
            charge(ctx, 4);
            t4 = addiu(sp, 0x60);
            t3 = addiu(sp, 0x70);
            t2 = addiu(sp, 0x80);
            t1 = addiu(sp, 0x90);
            for (;;) {
                // 0x004ddae4: the four rows to the 4 KiB frame buffer (sp + 0x90, 1 KiB per row)
                charge(ctx, 3);
                lw(t7, a0, rw_raster::kWidth);
                s3 = 0;
                s1 = t1;
                for (;;) {
                    // 0x004ddaf0
                    charge(ctx, 4);
                    at = slt(0, t7);
                    s2 = 0;
                    s0 = t7;
                    if (at != 0) {
                        // 0x004ddb00
                        charge(ctx, 4);
                        lw(t0, a0, rw_raster::kStride);
                        t6 = addu(t9, s3);
                        lw(a3, a0, rw_raster::kPixels);
                        lw(s0, a0, rw_raster::kWidth);
                        for (;;) {
                            // 0x004ddb10
                            charge(ctx, 9);
                            mult(v1, t0, t6);
                            a1 = addu(s1, s2);
                            v1 = addu(a3, v1);
                            v1 = addu(v1, s2);
                            lq(a2, v1, 0);
                            s2 = addiu(s2, 16);
                            v1 = slt(s2, s0);
                            sq(a2, a1, 0);
                            if (v1 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004ddb34
                        charge(ctx, 1);
                    }
                    // 0x004ddb38
                    charge(ctx, 4);
                    s3 = addiu(s3, 1);
                    v1 = slti(s3, 4);
                    s1 = addiu(s1, 1024);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004ddb48: each 16-byte column gathered from its shuffled places (sp + 0x50)
                charge(ctx, 3);
                at = slt(0, s0);
                t6 = 0;
                if (at != 0) {
                    // 0x004ddb54
                    charge(ctx, 3);
                    t8 = 0;
                    t0 = t9 & 0x4;
                    v1 = addiu(t9, 2);
                    for (;;) {
                        // 0x004ddb60
                        charge(ctx, 4);
                        a1 = addu(t6, sp);
                        s1 = 0;
                        a3 = addiu(a1, 144);
                        for (;;) {
                            // 0x004ddb70
                            charge(ctx, 2);
                            s0 = 0;
                            t7 = addu(t5, s1);
                            for (;;) {
                                // 0x004ddb78
                                charge(ctx, 2);
                                if (t0 == 0) {
                                    // 0x004ddbe0
                                    charge(ctx, 20);
                                    a2 = addu(s1, s0);
                                    s2 = a2 & 0x2;
                                    a1 = a2 & 0x1;
                                    s4 = sll(s2, 2);
                                    s2 = a2 & 0x4;
                                    s3 = sra(s2, 2);
                                    s2 = a2 & 0x8;
                                    s3 = s4 | s3;
                                    s2 = sra(s2, 2);
                                    s3 = s2 | s3;
                                    s2 = a2 & 0x10;
                                    s2 = sra(s2, 2);
                                    a2 = a2 & 0x20;
                                    s2 = s2 | s3;
                                    a2 = sra(a2, 1);
                                    s2 = a2 | s2;
                                    a2 = sll(a1, 5);
                                    a1 = sll(a1, 2);
                                    a1 = a2 | a1;
                                    s2 = s2 ^ a1;
                                } else {
                                    // 0x004ddb80
                                    charge(ctx, 23);
                                    a2 = addu(s1, s0);
                                    s2 = a2 & 0x2;
                                    a1 = a2 & 0x4;
                                    s2 = sll(s2, 2);
                                    a1 = sra(a1, 2);
                                    s3 = s2 | a1;
                                    a1 = a2 & 0x8;
                                    s2 = sra(a1, 2);
                                    a1 = a2 & 0x10;
                                    s2 = s2 | s3;
                                    a1 = sra(a1, 2);
                                    s3 = a1 | s2;
                                    a1 = a2 & 0x20;
                                    s2 = a2 & 0x1;
                                    a2 = nor(a2, 0);
                                    a1 = sra(a1, 1);
                                    a2 = a2 & 0x1;
                                    s2 = sll(s2, 5);
                                    a2 = sll(a2, 2);
                                    a1 = a1 | s3;
                                    a2 = s2 | a2;
                                    s2 = a1 ^ a2;
                                }
                                // 0x004ddc30
                                charge(ctx, 11);
                                a1 = sra(s2, 4);
                                a2 = sll(a1, 10);
                                s0 = addiu(s0, 1);
                                a1 = s2 & 0xF;
                                a2 = addu(a3, a2);
                                a2 = addu(a2, a1);
                                lbu(a2, a2, 0);
                                a1 = slti(s0, 16);
                                sb(a2, t7, 0);
                                t7 = addiu(t7, 1);
                                if (a1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004ddc5c
                            charge(ctx, 4);
                            s1 = addiu(s1, 16);
                            a1 = slti(s1, 64);
                            if (a1 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004ddc6c: written back as the four rows' quadwords
                        charge(ctx, 33);
                        lw(a1, a0, rw_raster::kStride);
                        lq(t7, sp, 0x50);
                        mult(a2, t9, a1);
                        lq(a3, t4, 0);
                        lw(a1, a0, rw_raster::kPixels);
                        a1 = addu(a1, a2);
                        a1 = addu(a1, t8);
                        sq(t7, a1, 0);
                        lw(a1, a0, rw_raster::kStride);
                        mult1(a2, t9, a1);
                        lq(t7, t3, 0);
                        lw(a1, a0, rw_raster::kPixels);
                        a1 = addu(a1, a2);
                        a1 = addu(a1, t8);
                        sq(a3, a1, 16);
                        lw(a1, a0, rw_raster::kStride);
                        mult(a2, v1, a1);
                        lq(a3, t2, 0);
                        lw(a1, a0, rw_raster::kPixels);
                        a1 = addu(a1, a2);
                        a1 = addu(a1, t8);
                        sq(t7, a1, 0);
                        lw(a1, a0, rw_raster::kStride);
                        mult1(a2, v1, a1);
                        t6 = addiu(t6, 16);
                        lw(a1, a0, rw_raster::kPixels);
                        a1 = addu(a1, a2);
                        a1 = addu(a1, t8);
                        sq(a3, a1, 16);
                        lw(a1, a0, rw_raster::kWidth);
                        a1 = slt(t6, a1);
                        t8 = addiu(t8, 32);
                        if (a1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x004ddcf0
                charge(ctx, 5);
                lw(v1, a0, rw_raster::kHeight);
                t9 = addiu(t9, 4);
                v1 = slt(t9, v1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004ddd04
            charge(ctx, 1);
        }
    }
    // 0x004ddd08 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x1090);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_4DDAA0(EEContext& ctx, u64 lock) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(lock));
    sub_4DDAA0(ctx);
}

// 0x004DDD30 sub_4DDD30 -- 876 bytes; frame 0x890: s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4DDD30 [unswizzle a PSMT4 raster in place]: the PSMT4 counterpart of sub_4DDAA0 (512-byte frame-buffer rows,
// nibbles gathered into sp + 80 by the parities of the destination and the source).
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4DDD30(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lbu, hg::lq, hg::lw, hg::mult,
          hg::mult1, hg::nor, hg::sb, hg::sll, hg::slt, hg::slti, hg::sq, hg::sra;
    Gpr at{ctx, 1}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, t8{ctx, 24}, t9{ctx, 25}, sp{ctx, 29};
    // 0x004ddd30
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x890);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, rw_raster::kHeight);
    at = slt(0, v1);
    t7 = 0;
    if (at != 0) {
        // 0x004ddd58: per band of four rows
        charge(ctx, 3);
        at = slt(0, v1);
        t4 = addiu(sp, 0x50);
        if (at != 0) {
            // 0x004ddd64
            charge(ctx, 4);
            t3 = addiu(sp, 0x60);
            t2 = addiu(sp, 0x70);
            t1 = addiu(sp, 0x80);
            t0 = addiu(sp, 0x90);
            for (;;) {
                // 0x004ddd74: the four rows to the frame buffer (512-byte rows)
                charge(ctx, 4);
                lw(a3, a0, rw_raster::kWidth);
                t9 = 0;
                t6 = t0;
                a2 = sra(a3, 1);
                for (;;) {
                    // 0x004ddd84
                    charge(ctx, 4);
                    at = slt(0, a2);
                    t8 = 0;
                    t5 = a3;
                    if (at == 0) {
                        // 0x004ddde0
                        charge(ctx, 1);
                        t9 = addiu(t9, 1);
                    } else {
                        // 0x004ddd94
                        charge(ctx, 5);
                        lw(t5, a0, rw_raster::kWidth);
                        a1 = addu(t7, t9);
                        lw(v1, a0, rw_raster::kStride);
                        lw(s4, a0, rw_raster::kPixels);
                        s1 = sra(t5, 1);
                        for (;;) {
                            // 0x004ddda8
                            charge(ctx, 9);
                            mult(s0, v1, a1);
                            s2 = addu(t6, t8);
                            s0 = addu(s4, s0);
                            s0 = addu(s0, t8);
                            lq(s3, s0, 0);
                            t8 = addiu(t8, 16);
                            s0 = slt(t8, s1);
                            sq(s3, s2, 0);
                            if (s0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004dddcc
                        charge(ctx, 2);
                        t9 = addiu(t9, 1);
                    }
                    // 0x004ddde4
                    charge(ctx, 3);
                    v1 = slti(t9, 4);
                    t6 = addiu(t6, 512);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004dddf0: the nibbles gathered by the parities of the destination and the source
                charge(ctx, 3);
                at = slt(0, t5);
                a3 = 0;
                if (at != 0) {
                    // 0x004dddfc
                    charge(ctx, 2);
                    a2 = t7 & 0x4;
                    v1 = addiu(t7, 2);
                    for (;;) {
                        // 0x004dde04
                        charge(ctx, 1);
                        t8 = 0;
                        for (;;) {
                            // 0x004dde08
                            charge(ctx, 1);
                            t6 = 0;
                            for (;;) {
                                // 0x004dde0c
                                charge(ctx, 2);
                                if (a2 == 0) {
                                    // 0x004dde7c
                                    charge(ctx, 23);
                                    t5 = addu(t8, t6);
                                    s0 = t5 & 0x2;
                                    a1 = t5 & 0x1;
                                    t9 = sll(s0, 2);
                                    s0 = t5 & 0x20;
                                    s1 = sra(s0, 1);
                                    s0 = t5 & 0x4;
                                    s1 = t9 | s1;
                                    s0 = sra(s0, 2);
                                    t9 = s0 | s1;
                                    s0 = t5 & 0x8;
                                    s1 = sra(s0, 2);
                                    s0 = t5 & 0x10;
                                    s1 = s1 | t9;
                                    s0 = sra(s0, 2);
                                    t9 = sll(a1, 6);
                                    s1 = s0 | s1;
                                    a1 = sll(a1, 2);
                                    s0 = t5 & 0x40;
                                    a1 = t9 | a1;
                                    s0 = sra(s0, 1);
                                    s0 = s0 | s1;
                                    s0 = s0 ^ a1;
                                } else {
                                    // 0x004dde14
                                    charge(ctx, 26);
                                    t5 = addu(t8, t6);
                                    s0 = t5 & 0x2;
                                    a1 = t5 & 0x20;
                                    s0 = sll(s0, 2);
                                    a1 = sra(a1, 1);
                                    s1 = s0 | a1;
                                    a1 = t5 & 0x4;
                                    s0 = sra(a1, 2);
                                    a1 = t5 & 0x8;
                                    s0 = s0 | s1;
                                    a1 = sra(a1, 2);
                                    s1 = a1 | s0;
                                    a1 = t5 & 0x10;
                                    s0 = sra(a1, 2);
                                    a1 = t5 & 0x40;
                                    s0 = s0 | s1;
                                    a1 = sra(a1, 1);
                                    s1 = a1 | s0;
                                    a1 = t5 & 0x1;
                                    s0 = sll(a1, 6);
                                    a1 = nor(t5, 0);
                                    a1 = a1 & 0x1;
                                    a1 = sll(a1, 2);
                                    a1 = s0 | a1;
                                    s0 = s1 ^ a1;
                                }
                                // 0x004dded8
                                charge(ctx, 3);
                                a1 = t6 & 0x1;
                                if (a1 == 0) {
                                    // 0x004ddf5c
                                    charge(ctx, 3);
                                    a1 = s0 & 0x1;
                                    if (a1 == 0) {
                                        // 0x004ddf94
                                        charge(ctx, 9);
                                        t9 = sra(s0, 5);
                                        a1 = s0 & 0x1F;
                                        t9 = sll(t9, 10);
                                        a1 = addu(a3, a1);
                                        a1 = addu(t9, a1);
                                        a1 = sra(a1, 1);
                                        a1 = addu(a1, sp);
                                        lbu(a1, a1, 144);
                                        t9 = a1 & 0xF;
                                    } else {
                                        // 0x004ddf68
                                        charge(ctx, 11);
                                        t9 = sra(s0, 5);
                                        a1 = s0 & 0x1F;
                                        t9 = sll(t9, 10);
                                        a1 = addu(a3, a1);
                                        a1 = addu(t9, a1);
                                        a1 = sra(a1, 1);
                                        a1 = addu(a1, sp);
                                        lbu(a1, a1, 144);
                                        a1 = sra(a1, 4);
                                        t9 = a1 & 0xF;
                                    }
                                    // 0x004ddfb8
                                    charge(ctx, 3);
                                    a1 = sra(t5, 1);
                                    a1 = addu(t4, a1);
                                    sb(t9, a1, 0);
                                } else {
                                    // 0x004ddee4
                                    charge(ctx, 3);
                                    a1 = s0 & 0x1;
                                    if (a1 == 0) {
                                        // 0x004ddf18
                                        charge(ctx, 10);
                                        t9 = sra(s0, 5);
                                        a1 = s0 & 0x1F;
                                        t9 = sll(t9, 10);
                                        a1 = addu(a3, a1);
                                        a1 = addu(t9, a1);
                                        a1 = sra(a1, 1);
                                        a1 = addu(a1, sp);
                                        lbu(a1, a1, 144);
                                        a1 = a1 & 0xF;
                                        a1 = sll(a1, 4);
                                    } else {
                                        // 0x004ddef0
                                        charge(ctx, 10);
                                        t9 = sra(s0, 5);
                                        a1 = s0 & 0x1F;
                                        t9 = sll(t9, 10);
                                        a1 = addu(a3, a1);
                                        a1 = addu(t9, a1);
                                        a1 = sra(a1, 1);
                                        a1 = addu(a1, sp);
                                        lbu(a1, a1, 144);
                                        a1 = a1 & 0xF0;
                                    }
                                    // 0x004ddf40
                                    charge(ctx, 7);
                                    t9 = a1 & 0xFF;
                                    a1 = sra(t5, 1);
                                    t5 = addu(t4, a1);
                                    lbu(a1, t5, 0);
                                    a1 = a1 | t9;
                                    sb(a1, t5, 0);
                                }
                                // 0x004ddfc4
                                charge(ctx, 4);
                                t6 = addiu(t6, 1);
                                a1 = slti(t6, 32);
                                if (a1 == 0) {
                                    break;
                                }
                                backedge(ctx);
                            }
                            // 0x004ddfd4
                            charge(ctx, 4);
                            t8 = addiu(t8, 32);
                            a1 = slti(t8, 128);
                            if (a1 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                        // 0x004ddfe4: written back as the four rows' quadwords
                        charge(ctx, 33);
                        lw(a1, a0, rw_raster::kStride);
                        lq(t8, sp, 0x50);
                        mult(t5, t7, a1);
                        lq(t6, t3, 0);
                        lw(a1, a0, rw_raster::kPixels);
                        a1 = addu(a1, t5);
                        a1 = addu(a1, a3);
                        sq(t8, a1, 0);
                        lw(a1, a0, rw_raster::kStride);
                        mult1(t5, t7, a1);
                        lq(t8, t2, 0);
                        lw(a1, a0, rw_raster::kPixels);
                        a1 = addu(a1, t5);
                        a1 = addu(a1, a3);
                        sq(t6, a1, 16);
                        lw(a1, a0, rw_raster::kStride);
                        mult(t5, v1, a1);
                        lq(t6, t1, 0);
                        lw(a1, a0, rw_raster::kPixels);
                        a1 = addu(a1, t5);
                        a1 = addu(a1, a3);
                        sq(t8, a1, 0);
                        lw(a1, a0, rw_raster::kStride);
                        mult1(t5, v1, a1);
                        lw(a1, a0, rw_raster::kPixels);
                        a1 = addu(a1, t5);
                        a1 = addu(a1, a3);
                        sq(t6, a1, 16);
                        a3 = addiu(a3, 32);
                        lw(a1, a0, rw_raster::kWidth);
                        a1 = slt(a3, a1);
                        if (a1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x004de068
                charge(ctx, 5);
                lw(v1, a0, rw_raster::kHeight);
                t7 = addiu(t7, 4);
                v1 = slt(t7, v1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004de07c
            charge(ctx, 2);
            backedge(ctx);
        }
    }
    // 0x004dddd8
    charge(ctx, 2);
    lq(s4, sp, 0x40);
    // 0x004de084
    charge(ctx, 6);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x890);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_4DDD30(EEContext& ctx, u64 lock) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(lock));
    sub_4DDD30(ctx);
}

// 0x004DECE0 sub_4DECE0 -- 560 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4DECE0 [the driver's raster unlock (standard function 16)](_, raster): the raster (+4 pixels, +12 / +16 / +20
// width, height, depth, +24 stride, +32 type, +34 lock flags, +35 format flags). For a locked raster (+34 & 6): a CPU
// raster (types 1 / 5 / 2) writes its pixels back (SyncDCache); a GS raster with a lock buffer unswizzles PSMT8 (TEX0
// PSM 0x13, stride >= 16, not +34 bit 5; sub_4DDAA0) or PSMT4 (0x14; sub_4DDD30) per its cache flags (+54 bits 1 /
// 2), writes back, and restores the raster's own fields from the saved copy (+36 .. +48; +4 one level down the cache
// slot when +54 bit 0). A palettised, mipmapped raster still flagged dirty re-validates through sub_4D13E0(raster, 0).
// Clears the lock flags (& ~0x26); returns 1, or 0 when it was not locked.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void sub_4DECE0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::enter, hg::i64, hg::jal, hg::lbu,
          hg::ld, hg::link, hg::lq, hg::lw, hg::mult, hg::sb, hg::sd, hg::si, hg::slti, hg::sq, hg::sra, hg::srl,
          hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ded34: a CPU raster: its pixels written back (SyncDCache over width * height * depth / 8 + 127); $v1 = the
    // format byte
    auto cpu_writeback = [&] {
        charge(ctx, 3);
        lw(a0, s1, rw_raster::kPixels);
        if (a0 == 0) {
            // 0x004dee50
            charge(ctx, 1);
            lbu(v1, s1, rw_raster::kFormatHi);
        } else {
            // 0x004ded40
            charge(ctx, 7);
            lw(v1, s1, rw_raster::kWidth);
            lw(v0, s1, rw_raster::kHeight);
            mult(v1, v1, v0);
            lw(v0, s1, rw_raster::kDepth);
            mult(v1, v0, v1);
            v0 = sra(v1, 3);
            if (i64(v1) < 0) {
                // 0x004ded5c
                charge(ctx, 2);
                v0 = addiu(v1, 7);
                v0 = sra(v0, 3);
            }
            // 0x004ded64
            charge(ctx, 5);
            v0 = addu(a0, v0);
            a1 = addiu(v0, 127);
            jal(ctx, 0x4DED68u, gen::fn_SyncDCache_00503a58);
            lbu(v1, s1, rw_raster::kFormatHi);
        }
    };
    // 0x004dee54: a palettised (0x80), mipmapped (0x10) raster still flagged (+34 bit 2) re-validates; the lock flags
    // cleared (& ~0x26); return 1
    auto finish = [&] {
        charge(ctx, 3);
        v0 = v1 & 0x80;
        do {
            if (v0 != 0) {
                // 0x004dee60
                charge(ctx, 3);
                v0 = v1 & 0x10;
                if (v0 != 0) {
                    // 0x004dee6c
                    charge(ctx, 4);
                    lbu(v1, s1, rw_raster::kLockFlags);
                    v0 = v1 & 0x4;
                    if (v0 != 0) {
                        // 0x004dee7c: sub_4D13E0(raster, 0)
                        charge(ctx, 6);
                        v0 = si(-39);
                        a0 = s1;
                        v0 = v1 & v0;
                        a1 = 0;
                        link(ctx, 0x4DEE8Cu);  // $ra first: the delay slot below depends on it
                        sb(v0, s1, rw_raster::kLockFlags);
                        call(ctx, gen::fn_sub_4D13E0_004d13e0);
                        break;
                    }
                }
            }
            // 0x004deee8
            charge(ctx, 5);
            lbu(v1, s1, rw_raster::kLockFlags);
            v0 = si(-39);
            v0 = v1 & v0;
            sb(v0, s1, rw_raster::kLockFlags);
            backedge(ctx);
        } while (false);
        // 0x004dee94
        charge(ctx, 2);
        v0 = 1;
    };
    // 0x004dece0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lbu(v0, a1, rw_raster::kLockFlags);
    v1 = v0 & 0x6;
    s1 = a1;  // s1 = the raster
    if (v1 == 0) {
        // 0x004dee9c: not locked: 0
        charge(ctx, 2);
        v0 = 0;
    } else {
        // 0x004ded00: by the raster type
        charge(ctx, 5);
        lbu(a0, s1, rw_raster::kTypeByte);
        v1 = 1;
        a0 = a0 & 0x7;
        if (a0 != v1) {
            // 0x004ded14
            charge(ctx, 3);
            v1 = 5;
            if (a0 == v1) {
                cpu_writeback();
            } else {
                // 0x004ded20
                charge(ctx, 3);
                v1 = 2;
                if (a0 == v1) {
                    cpu_writeback();
                } else {
                    // 0x004ded2c: a GS raster: s0 = its sky extension
                    charge(ctx, 2);
                    lw(a0, gp, sky::kGpRasterExt);
                    // 0x004ded78
                    charge(ctx, 3);
                    lw(v1, s1, rw_raster::kPixels);
                    s0 = addu(s1, a0);
                    if (v1 != 0) {
                        // 0x004ded84: a lock buffer: unswizzle it per the cache flags
                        charge(ctx, 4);
                        lbu(a1, s0, sky_raster::kCacheFlags);
                        v1 = a1 & 0x2;
                        do {
                            if (v1 != 0) {
                                // 0x004deea4: PSMT8 (PSM 0x13), stride >= 16, writable?
                                charge(ctx, 6);
                                lw(a0, s0, sky_raster::kTex0);
                                v1 = 19;
                                a0 = srl(a0, 20);
                                a0 = a0 & 0x3F;
                                if (a0 == v1) {
                                    // 0x004deebc
                                    charge(ctx, 4);
                                    lw(v1, s1, rw_raster::kStride);
                                    v1 = slti(v1, 16);
                                    if (v1 == 0) {
                                        // 0x004deecc
                                        charge(ctx, 3);
                                        v1 = v0 & 0x20;
                                        if (v1 == 0) {
                                            // 0x004deed8: sub_4DDAA0(raster)
                                            charge(ctx, 4);
                                            a0 = s1;
                                            jal(ctx, 0x4DEED8u, gen::fn_sub_4DDAA0_004ddaa0);
                                            lw(v1, s1, rw_raster::kWidth);
                                            backedge(ctx);
                                            break;
                                        }
                                    }
                                }
                                backedge(ctx);
                            }
                            // 0x004ded94: PSMT4 (PSM 0x14), stride >= 16, writable: sub_4DDD30(raster)
                            charge(ctx, 3);
                            v1 = a1 & 0x4;
                            if (v1 != 0) {
                                // 0x004deda0
                                charge(ctx, 6);
                                lw(a0, s0, sky_raster::kTex0);
                                v1 = 20;
                                a0 = srl(a0, 20);
                                a0 = a0 & 0x3F;
                                if (a0 == v1) {
                                    // 0x004dedb8
                                    charge(ctx, 4);
                                    lw(v1, s1, rw_raster::kStride);
                                    v1 = slti(v1, 16);
                                    if (v1 == 0) {
                                        // 0x004dedc8
                                        charge(ctx, 3);
                                        v0 = v0 & 0x20;
                                        if (v0 == 0) {
                                            // 0x004dedd4
                                            charge(ctx, 2);
                                            a0 = s1;
                                            jal(ctx, 0x4DEDD4u, gen::fn_sub_4DDD30_004ddd30);
                                        }
                                    }
                                }
                            }
                            // 0x004deddc
                            charge(ctx, 1);
                            lw(v1, s1, rw_raster::kWidth);
                        } while (false);
                        // 0x004dede0: write the buffer back (width * height * depth / 8 + 127)
                        charge(ctx, 7);
                        lw(v0, s1, rw_raster::kHeight);
                        lw(a0, s1, rw_raster::kPixels);
                        mult(v1, v1, v0);
                        lw(v0, s1, rw_raster::kDepth);
                        mult(v1, v0, v1);
                        v0 = sra(v1, 3);
                        if (i64(v1) < 0) {
                            // 0x004dedfc
                            charge(ctx, 2);
                            v0 = addiu(v1, 7);
                            v0 = sra(v0, 3);
                        }
                        // 0x004dee04
                        charge(ctx, 3);
                        v0 = addu(a0, v0);
                        a1 = addiu(v0, 127);
                        jal(ctx, 0x4DEE08u, gen::fn_SyncDCache_00503a58);
                    }
                    // 0x004dee10: the raster's own fields back from the saved copy
                    charge(ctx, 12);
                    lw(v0, s1, rw_raster::kSavedWidth);
                    sw(v0, s1, rw_raster::kWidth);
                    lw(v0, s1, rw_raster::kSavedHeight);
                    sw(v0, s1, rw_raster::kHeight);
                    lw(v0, s1, rw_raster::kSavedStride);
                    sw(v0, s1, rw_raster::kStride);
                    lw(v0, s1, rw_raster::kSavedPixels);
                    sw(v0, s1, rw_raster::kPixels);
                    lbu(v0, s0, sky_raster::kCacheFlags);
                    v0 = v0 & 0x1;
                    if (v0 != 0) {
                        // 0x004dee40: mipmapped: the pixels one level down the cache slot (+4, + 80)
                        charge(ctx, 4);
                        lw(v0, s1, rw_raster::kPixels);
                        lw(v0, v0, 4);
                        v0 = addiu(v0, 80);
                        sw(v0, s1, rw_raster::kPixels);
                    }
                    // 0x004dee50
                    charge(ctx, 1);
                    lbu(v1, s1, rw_raster::kFormatHi);
                }
            }
        } else {
            cpu_writeback();
        }
        finish();
    }
    // 0x004deefc (the shared epilogue)
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4DECE0(EEContext& ctx, u64 unused, u64 raster, u64 flags) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(unused));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(raster));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(flags));
    sub_4DECE0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004DEF10 sub_4DEF10 -- 192 bytes; frame 0x50: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4DEF10 [the driver's palette lock (standard function 23)](out, raster, mode): $a0 where the palette pointer
// goes, $a2 the lock mode (bit 0 read, bit 1 write). Only for a palettised raster (+35 & 0x60) that owns its pixels
// (+33 bit 7 clear): reading a palette not yet in RAM (+33 bit 6 clear) fetches it first (sub_4F1540); *$a0 = the
// palette (+8); +34 gets 0x10 (read) / 8 (write). Returns 1, or 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4DEF10(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq, hg::lw, hg::sb,
          hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // The epilogue 0x004defb4, written out on each path that returns.
    auto epilogue = [&] {
        charge(ctx, 7);
        ld(ra, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x50);
    };
    // 0x004def10
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;  // s2 = out
    sq(s0, sp, 0x0);
    s1 = a2;  // s1 = the mode
    lbu(v0, a1, rw_raster::kFormatHi);
    v0 = v0 & 0x60;  // palettised?
    s0 = a1;  // s0 = the raster
    if (v0 != 0) {
        // 0x004def40: owns its pixels?
        charge(ctx, 4);
        lbu(v1, s0, rw_raster::kCacheByte);
        v0 = v1 & 0x80;
        if (v0 != 0) {
            // 0x004defb0 (written out on this path): no: 0
            charge(ctx, 1);
            v0 = 0;
            epilogue();
            return;
        }
        // 0x004def50: reading a palette not in RAM fetches it (sub_4F1540)
        charge(ctx, 3);
        s3 = s1 & 0x1;
        if (s3 != 0) {
            // 0x004def5c
            charge(ctx, 3);
            v0 = v1 & 0x40;
            if (v0 == 0) {
                // 0x004def68
                charge(ctx, 2);
                a0 = s0;
                jal(ctx, 0x4DEF68u, gen::fn_sub_4F1540_004f1540);
            }
        }
        // 0x004def70: *out = the palette; the lock flags
        charge(ctx, 3);
        lw(v0, s0, rw_raster::kPalette);
        sw(v0, s2, 0);
        if (s3 != 0) {
            // 0x004def90: read
            charge(ctx, 4);
            lbu(v0, s0, rw_raster::kLockFlags);
            v0 = v0 | 0x10;
            sb(v0, s0, rw_raster::kLockFlags);
            backedge(ctx);
        }
        // 0x004def7c
        charge(ctx, 3);
        v0 = s1 & 0x2;
        if (v0 != 0) {
            // 0x004defa0: write
            charge(ctx, 4);
            lbu(v0, s0, rw_raster::kLockFlags);
            v0 = v0 | 0x8;
            sb(v0, s0, rw_raster::kLockFlags);
            backedge(ctx);
        }
        // 0x004def88: 1
        charge(ctx, 2);
        v0 = 1;
        epilogue();
        return;
    }
    // 0x004defb0: not palettised: 0
    charge(ctx, 1);
    v0 = 0;
    epilogue();
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4DEF10(EEContext& ctx, u64 out, u64 raster, u64 mode) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(out));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(raster));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(mode));
    sub_4DEF10(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004DEFD0 sub_4DEFD0 -- 272 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4DEFD0 [the driver's palette unlock (standard function 24)](_, raster): for a palettised raster with a palette
// (+8): the palette size 16 / 256 entries (+35 bit 6) times 4 (32-bit, format 0x500) or 2 (16-bit, 0x100) bytes, else
// RWERROR 0x8000000D and 0. A palette already in GS memory (+33 bit 6) with a cache slot (+88) and +34 bit 0 is
// re-uploaded (sub_4F0C70); otherwise the palette is written back (SyncDCache). +34 &= ~0x18; returns 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4DEFD0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq,
          hg::lui, hg::lw, hg::sb, hg::sd, hg::si, hg::sll, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004df038: the palette ($a0, $v1 bytes) re-uploaded or written back; the lock flags cleared (& ~0x18)
    auto palette_done = [&] {
        charge(ctx, 4);
        lbu(v0, s0, rw_raster::kCacheByte);
        v0 = v0 & 0x40;
        if (v0 == 0) {
            // 0x004df0b8: not in GS memory: SyncDCache(palette, palette + bytes + 127)
            charge(ctx, 5);
            v0 = addu(a0, v1);
            a1 = addiu(v0, 127);
            jal(ctx, 0x4DF0BCu, gen::fn_SyncDCache_00503a58);
            backedge(ctx);
            // 0x004df0a0
            charge(ctx, 1);
            lbu(v1, s0, rw_raster::kLockFlags);
        } else {
            // 0x004df048: in GS memory: re-upload when flagged (+34 bit 0) and cached (+88)
            charge(ctx, 4);
            lbu(v0, s0, rw_raster::kLockFlags);
            v0 = v0 & 0x1;
            if (v0 == 0) {
                // 0x004df0a0 (written out on this path)
                charge(ctx, 1);
                lbu(v1, s0, rw_raster::kLockFlags);
            } else {
                // 0x004df058
                charge(ctx, 5);
                lw(v0, gp, sky::kGpRasterExt);
                v0 = addu(s0, v0);
                lw(v0, v0, sky_raster::kCacheSlot);
                if (v0 == 0) {
                    // 0x004df0a0 (written out on this path)
                    charge(ctx, 1);
                    lbu(v1, s0, rw_raster::kLockFlags);
                } else {
                    // 0x004df06c: sub_4F0C70(raster)
                    charge(ctx, 4);
                    a0 = s0;
                    jal(ctx, 0x4DF06Cu, gen::fn_sub_4F0C70_004f0c70);
                    lbu(v1, s0, rw_raster::kLockFlags);
                }
            }
        }
        // 0x004df0a4
        charge(ctx, 3);
        v0 = si(-25);
        v0 = v1 & v0;
        sb(v0, s0, rw_raster::kLockFlags);
    };
    // 0x004defd0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lbu(v0, a1, rw_raster::kFormatHi);
    v1 = sll(v0, 8);  // v1 = the format word's high half
    v0 = v1 & 0x6000;
    s0 = a1;  // s0 = the raster
    if (v0 == 0) {
        // 0x004df0cc: not palettised: 0
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x004deff0
        charge(ctx, 3);
        lw(a0, s0, rw_raster::kPalette);
        if (a0 != 0) {
            // 0x004deffc: a2 = the entries (16 / 256)
            charge(ctx, 8);
            v0 = v1 & 0x4000;
            a2 = 16;
            a1 = 256;
            v1 = v1 & 0xF00;
            if (v0 == 0) a2 = a1;
            v0 = 1280;
            if (v1 == v0) {
                // 0x004df034: 32-bit entries
                charge(ctx, 1);
                v1 = sll(a2, 2);
                palette_done();
            } else {
                // 0x004df01c
                charge(ctx, 2);
                if (v1 == a1) {
                    // 0x004df02c: 16-bit entries
                    charge(ctx, 2);
                    v1 = sll(a2, 1);
                    palette_done();
                } else {
                    // 0x004df024: another format: RWERROR(0x8000000D); 0
                    charge(ctx, 2);
                    v1 = 1;
                    // 0x004df07c
                    charge(ctx, 9);
                    v0 = lui(0x8000);
                    sw(v1, sp, 0x28);
                    a0 = v0 | 0xD;
                    jal(ctx, 0x4DF084u, gen::fn_sub_4C1D10_004c1d10);
                    sw(v0, sp, 0x2C);
                    a0 = addiu(sp, 0x28);
                    jal(ctx, 0x4DF090u, gen::fn_sub_4C1C50_004c1c50);
                    v0 = 0;
                    // 0x004df0d0 (the shared epilogue, written out on this path)
                    charge(ctx, 4);
                    ld(ra, sp, 0x10);
                    lq(s0, sp, 0x0);
                    sp = addiu(sp, 0x30);
                    return;
                }
            }
        }
        // 0x004df0b0: 1
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x004df0d0 (the shared epilogue)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4DEFD0(EEContext& ctx, u64 unused, u64 raster) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(unused));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(raster));
    sub_4DEFD0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
void sub_4E2F10(EEContext& ctx, u64 unused) {
    ee::core::set_gpr64(ctx, GPR_A0, unused);
    c3::detail::Cpu(ctx).sub_4E2F10();
}

// 0x004E4A90 sub_4E4A90 -- 400 bytes; leaf frame (no stack)
// sub_4E4A90 [clip a blit 1:1 against the scissor]: $a0 the source rectangle {x, y, w, h}, $a1 the destination.
// Rejected (0) when the destination misses the scissor; otherwise its left / right / top / bottom overhangs are cut
// (the source origin moved by the same amounts) and the clipped w / h (both > 0, else 0) are copied to the source.
// Returns 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4E4A90(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::lw, hg::slt, hg::subu, hg::sw;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x004e4c14 + the epilogue 0x004e4c18: rejected: 0
    auto reject = [&] {
        charge(ctx, 1);
        v0 = 0;
        // 0x004e4c18 (the shared epilogue, written out on this path)
        charge(ctx, 2);
    };
    // 0x004e4a90
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = hi(kScissor + rect::kX);
    lw(t1, a1, rect::kX);
    lw(a3, a1, rect::kW);
    lw(t0, v0, lo(kScissor + rect::kX));
    v0 = addu(t1, a3);
    at = slt(t0, v0);
    if (at != 0) {
        // 0x004e4ab0: the destination's right edge is inside; its bottom?
        charge(ctx, 8);
        v0 = hi(kScissor + rect::kY);
        lw(a2, a1, rect::kY);
        lw(v1, v0, lo(kScissor + rect::kY));
        lw(v0, a1, rect::kH);
        v0 = addu(a2, v0);
        at = slt(v1, v0);
        if (at == 0) {
            reject();
            return;
        }
        // 0x004e4ad0: its left edge before the scissor's right?
        charge(ctx, 6);
        v0 = hi(kScissor + rect::kW);
        lw(v0, v0, lo(kScissor + rect::kW));
        v0 = addu(t0, v0);
        at = slt(t1, v0);
        if (at == 0) {
            reject();
            return;
        }
        // 0x004e4ae8: its top before the scissor's bottom?
        charge(ctx, 6);
        v0 = hi(kScissor + rect::kH);
        lw(v0, v0, lo(kScissor + rect::kH));
        v0 = addu(v1, v0);
        at = slt(a2, v0);
        if (at == 0) {
            reject();
            return;
        }
        // 0x004e4b00
        charge(ctx, 3);
        v0 = slt(t1, t0);
        if (v0 != 0) {
            // 0x004e4ba8: the left overhang cut (the source x moved by it)
            charge(ctx, 10);
            a2 = subu(t0, t1);
            v0 = hi(kScissor + rect::kX);
            v1 = subu(a3, a2);
            sw(v1, a1, rect::kW);
            lw(v1, a0, rect::kX);
            v1 = addu(v1, a2);
            sw(v1, a0, rect::kX);
            lw(v0, v0, lo(kScissor + rect::kX));
            sw(v0, a1, rect::kX);
            backedge(ctx);
        }
        // 0x004e4b0c
        charge(ctx, 11);
        v1 = hi(kScissor + rect::kX);
        v0 = hi(kScissor + rect::kW);
        lw(a3, v1, lo(kScissor + rect::kX));
        lw(a2, v0, lo(kScissor + rect::kW));
        lw(v1, a1, rect::kX);
        lw(v0, a1, rect::kW);
        a2 = addu(a3, a2);
        v0 = addu(v1, v0);
        at = slt(a2, v0);
        if (at != 0) {
            // 0x004e4bd0: the right overhang cut
            charge(ctx, 3);
            v0 = subu(a2, v1);
            sw(v0, a1, rect::kW);
            backedge(ctx);
        }
        // 0x004e4b38
        charge(ctx, 6);
        v0 = hi(kScissor + rect::kY);
        lw(v1, a1, rect::kY);
        lw(a2, v0, lo(kScissor + rect::kY));
        v0 = slt(v1, a2);
        if (v0 != 0) {
            // 0x004e4bdc: the top overhang cut (the source y moved by it)
            charge(ctx, 11);
            a2 = subu(a2, v1);
            v0 = hi(kScissor + rect::kY);
            lw(v1, a1, rect::kH);
            v1 = subu(v1, a2);
            sw(v1, a1, rect::kH);
            lw(v1, a0, rect::kY);
            v1 = addu(v1, a2);
            sw(v1, a0, rect::kY);
            lw(v0, v0, lo(kScissor + rect::kY));
            sw(v0, a1, rect::kY);
            backedge(ctx);
        }
        // 0x004e4b50
        charge(ctx, 11);
        v1 = hi(kScissor + rect::kY);
        v0 = hi(kScissor + rect::kH);
        lw(a3, v1, lo(kScissor + rect::kY));
        lw(a2, v0, lo(kScissor + rect::kH));
        lw(v1, a1, rect::kY);
        lw(v0, a1, rect::kH);
        a2 = addu(a3, a2);
        v0 = addu(v1, v0);
        at = slt(a2, v0);
        if (at != 0) {
            // 0x004e4c08: the bottom overhang cut
            charge(ctx, 3);
            v0 = subu(a2, v1);
            sw(v0, a1, rect::kH);
            backedge(ctx);
        }
        // 0x004e4b7c: both extents still positive: copied to the source; 1
        charge(ctx, 3);
        lw(v1, a1, rect::kW);
        if (i64(v1) <= 0) {
            reject();
            return;
        }
        // 0x004e4b88
        charge(ctx, 3);
        lw(v0, a1, rect::kH);
        if (i64(v0) <= 0) {
            reject();
            return;
        }
        // 0x004e4b94
        charge(ctx, 5);
        sw(v1, a0, rect::kW);
        v0 = 1;
        lw(v1, a1, rect::kH);
        sw(v1, a0, rect::kH);
        // 0x004e4c18 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x004e4c14 (the shared block)
    reject();
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4E4A90(EEContext& ctx, u64 src, u64 dst) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(src));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(dst));
    sub_4E4A90(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004E4C20 sub_4E4C20 -- 532 bytes; leaf frame (no stack)
// sub_4E4C20 [clip a scaled blit against the scissor]: as sub_4E4A90, but each cut of the destination cuts the source
// proportionally (source w / h * cut / destination w / h through mult / div); returns 1 when all four extents stay
// positive, else 0.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4E4C20(EEContext& ctx) {
    using hg::Gpr, hg::addu, hg::backedge, hg::charge, hg::div, hg::enter, hg::i64, hg::lw, hg::mflo, hg::mult,
          hg::slt, hg::subu, hg::sw;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x004e4e28 + the epilogue 0x004e4e2c: rejected: 0
    auto reject = [&] {
        charge(ctx, 1);
        v0 = 0;
        // 0x004e4e2c (the shared epilogue, written out on this path)
        charge(ctx, 2);
    };
    // 0x004e4c20
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = hi(kScissor + rect::kX);
    lw(t1, a1, rect::kW);
    lw(t0, a1, rect::kX);
    lw(a3, v0, lo(kScissor + rect::kX));
    v0 = addu(t0, t1);
    at = slt(a3, v0);
    if (at != 0) {
        // 0x004e4c40: the destination's right edge is inside; its bottom?
        charge(ctx, 8);
        v0 = hi(kScissor + rect::kY);
        lw(a2, a1, rect::kY);
        lw(v1, v0, lo(kScissor + rect::kY));
        lw(v0, a1, rect::kH);
        v0 = addu(a2, v0);
        at = slt(v1, v0);
        if (at == 0) {
            reject();
            return;
        }
        // 0x004e4c60: its left edge before the scissor's right?
        charge(ctx, 6);
        v0 = hi(kScissor + rect::kW);
        lw(v0, v0, lo(kScissor + rect::kW));
        v0 = addu(a3, v0);
        at = slt(t0, v0);
        if (at == 0) {
            reject();
            return;
        }
        // 0x004e4c78: its top before the scissor's bottom?
        charge(ctx, 6);
        v0 = hi(kScissor + rect::kH);
        lw(v0, v0, lo(kScissor + rect::kH));
        v0 = addu(v1, v0);
        at = slt(a2, v0);
        if (at == 0) {
            reject();
            return;
        }
        // 0x004e4c90
        charge(ctx, 3);
        v0 = slt(t0, a3);
        if (v0 != 0) {
            // 0x004e4d44: the left overhang cut, the source cut by w * cut / dst w
            charge(ctx, 17);
            lw(v0, a0, rect::kW);
            v1 = subu(a3, t0);
            mult(v0, v1, v0);
            div(v0, t1);
            v0 = subu(t1, v1);
            sw(v0, a1, rect::kW);
            mflo(a2);
            lw(v1, a0, rect::kW);
            v0 = hi(kScissor + rect::kX);
            v1 = subu(v1, a2);
            sw(v1, a0, rect::kW);
            lw(v0, v0, lo(kScissor + rect::kX));
            sw(v0, a1, rect::kX);
            lw(v0, a0, rect::kX);
            v0 = addu(v0, a2);
            sw(v0, a0, rect::kX);
            backedge(ctx);
        }
        // 0x004e4c9c
        charge(ctx, 11);
        v1 = hi(kScissor + rect::kX);
        v0 = hi(kScissor + rect::kW);
        lw(a2, v1, lo(kScissor + rect::kX));
        lw(a3, a1, rect::kW);
        lw(v1, v0, lo(kScissor + rect::kW));
        lw(v0, a1, rect::kX);
        v1 = addu(a2, v1);
        v0 = addu(v0, a3);
        at = slt(v1, v0);
        if (at != 0) {
            // 0x004e4d88: the right overhang cut, likewise
            charge(ctx, 11);
            a2 = subu(v0, v1);
            lw(v0, a0, rect::kW);
            mult(v0, a2, v0);
            div(v0, a3);
            v0 = subu(a3, a2);
            sw(v0, a1, rect::kW);
            mflo(v1);
            lw(v0, a0, rect::kW);
            v0 = subu(v0, v1);
            sw(v0, a0, rect::kW);
            backedge(ctx);
        }
        // 0x004e4cc8
        charge(ctx, 6);
        v0 = hi(kScissor + rect::kY);
        lw(v1, a1, rect::kY);
        lw(a2, v0, lo(kScissor + rect::kY));
        v0 = slt(v1, a2);
        if (v0 != 0) {
            // 0x004e4db4: the top overhang cut, the source by h * cut / dst h
            charge(ctx, 18);
            lw(v0, a0, rect::kH);
            a3 = subu(a2, v1);
            mult(v1, a3, v0);
            lw(v0, a1, rect::kH);
            div(v1, v0);
            v0 = subu(v0, a3);
            sw(v0, a1, rect::kH);
            mflo(a2);
            lw(v1, a0, rect::kH);
            v0 = hi(kScissor + rect::kY);
            v1 = subu(v1, a2);
            sw(v1, a0, rect::kH);
            lw(v0, v0, lo(kScissor + rect::kY));
            sw(v0, a1, rect::kY);
            lw(v0, a0, rect::kY);
            v0 = addu(v0, a2);
            sw(v0, a0, rect::kY);
            backedge(ctx);
        }
        // 0x004e4ce0
        charge(ctx, 11);
        v1 = hi(kScissor + rect::kY);
        v0 = hi(kScissor + rect::kH);
        lw(a2, v1, lo(kScissor + rect::kY));
        lw(a3, a1, rect::kH);
        lw(v1, v0, lo(kScissor + rect::kH));
        lw(v0, a1, rect::kY);
        v1 = addu(a2, v1);
        v0 = addu(v0, a3);
        at = slt(v1, v0);
        if (at != 0) {
            // 0x004e4dfc: the bottom overhang cut, likewise
            charge(ctx, 11);
            a2 = subu(v0, v1);
            lw(v0, a0, rect::kH);
            mult(v0, a2, v0);
            div(v0, a3);
            v0 = subu(a3, a2);
            sw(v0, a1, rect::kH);
            mflo(v1);
            lw(v0, a0, rect::kH);
            v0 = subu(v0, v1);
            sw(v0, a0, rect::kH);
            backedge(ctx);
        }
        // 0x004e4d0c: all four extents still positive: 1
        charge(ctx, 3);
        lw(v0, a1, rect::kW);
        if (i64(v0) <= 0) {
            reject();
            return;
        }
        // 0x004e4d18
        charge(ctx, 3);
        lw(v0, a1, rect::kH);
        if (i64(v0) <= 0) {
            reject();
            return;
        }
        // 0x004e4d24
        charge(ctx, 3);
        lw(v0, a0, rect::kW);
        if (i64(v0) <= 0) {
            reject();
            return;
        }
        // 0x004e4d30
        charge(ctx, 3);
        lw(v0, a0, rect::kH);
        if (i64(v0) <= 0) {
            reject();
            return;
        }
        // 0x004e4d3c
        charge(ctx, 2);
        v0 = 1;
        // 0x004e4e2c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
    // 0x004e4e28 (the shared block)
    reject();
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4E4C20(EEContext& ctx, u64 src, u64 dst) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(src));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(dst));
    sub_4E4C20(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004A55B0 sub_4A55B0 -- 2068 bytes; leaf frame (no stack)
// sub_4A55B0 [Rt2dBrush colour set-up]: $a0 the brush; four source colours ($t0, $a3, $a1, $a2: RGBA floats) each
// mixed as clamp(t2 + c * t1, 0, 255) per channel ($t2 the colour offset, $t1 the colour multiplier) into brush +0 /
// +24 / +48 / +72; the first one also packed as RGBA bytes at +96. Returns the brush.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4A55B0(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::c_le_s, hg::c_lt_s, hg::charge, hg::cond, hg::cvt_w_s, hg::enter,
          hg::lwc1, hg::madd_s, hg::mfc1, hg::mov_s, hg::mtc1, hg::sb, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4};
    // 0x004a55b0
    enter(ctx, 12);  // entry check point + this block's cycles
    lwc1(f2, t2, rgba_f::kR);
    v0 = flt(255.0f);
    lwc1(f4, t0, rgba_f::kR);
    lwc1(f3, t1, rgba_f::kR);
    mtc1(zero, f0);
    mtc1(v0, f1);
    adda_s(f0, f2);
    madd_s(f2, f4, f3);
    c_le_s(f2, f1);
    if (cond(ctx)) {
        // 0x004a55e0
        charge(ctx, 1);
        mov_s(f1, f2);
    }
    // 0x004a55e4
    charge(ctx, 5);
    mtc1(zero, f0);
    c_lt_s(f0, f1);
    if (cond(ctx)) {
        // 0x004a5600
        charge(ctx, 6);
        v0 = flt(255.0f);
        mtc1(v0, f0);
        c_le_s(f2, f0);
        if (!cond(ctx)) {
            // 0x004a5620
            charge(ctx, 2);
            mov_s(f2, f0);
            mov_s(f0, f2);
        } else {
            // 0x004a5618
            charge(ctx, 2);
            mov_s(f0, f2);
        }
        // 0x004a5628
        charge(ctx, 1);
        swc1(f0, a0, rt2d_brushcol::kColour0 + rgba_f::kR);
    } else {
        // 0x004a55f8
        charge(ctx, 2);
        swc1(f0, a0, rt2d_brushcol::kColour0 + rgba_f::kR);
    }
    // 0x004a562c
    charge(ctx, 12);
    v0 = flt(255.0f);
    lwc1(f2, t2, rgba_f::kG);
    lwc1(f4, t0, rgba_f::kG);
    lwc1(f3, t1, rgba_f::kG);
    mtc1(zero, f0);
    mtc1(v0, f1);
    adda_s(f0, f2);
    madd_s(f2, f4, f3);
    c_le_s(f2, f1);
    if (cond(ctx)) {
        // 0x004a565c
        charge(ctx, 1);
        mov_s(f1, f2);
    }
    // 0x004a5660
    charge(ctx, 5);
    mtc1(zero, f0);
    c_lt_s(f0, f1);
    if (cond(ctx)) {
        // 0x004a567c
        charge(ctx, 6);
        v0 = flt(255.0f);
        mtc1(v0, f0);
        c_le_s(f2, f0);
        if (!cond(ctx)) {
            // 0x004a569c
            charge(ctx, 2);
            mov_s(f2, f0);
            mov_s(f0, f2);
        } else {
            // 0x004a5694
            charge(ctx, 2);
            mov_s(f0, f2);
        }
        // 0x004a56a4
        charge(ctx, 1);
        swc1(f0, a0, rt2d_brushcol::kColour0 + rgba_f::kG);
    } else {
        // 0x004a5674
        charge(ctx, 2);
        swc1(f0, a0, rt2d_brushcol::kColour0 + rgba_f::kG);
    }
    // 0x004a56a8
    charge(ctx, 12);
    v0 = flt(255.0f);
    lwc1(f2, t2, rgba_f::kB);
    lwc1(f4, t0, rgba_f::kB);
    lwc1(f3, t1, rgba_f::kB);
    mtc1(zero, f0);
    mtc1(v0, f1);
    adda_s(f0, f2);
    madd_s(f2, f4, f3);
    c_le_s(f2, f1);
    if (cond(ctx)) {
        // 0x004a56d8
        charge(ctx, 1);
        mov_s(f1, f2);
    }
    // 0x004a56dc
    charge(ctx, 5);
    mtc1(zero, f0);
    c_lt_s(f0, f1);
    if (cond(ctx)) {
        // 0x004a56f8
        charge(ctx, 6);
        v0 = flt(255.0f);
        mtc1(v0, f0);
        c_le_s(f2, f0);
        if (!cond(ctx)) {
            // 0x004a5718
            charge(ctx, 2);
            mov_s(f2, f0);
            mov_s(f0, f2);
        } else {
            // 0x004a5710
            charge(ctx, 2);
            mov_s(f0, f2);
        }
        // 0x004a5720
        charge(ctx, 1);
        swc1(f0, a0, rt2d_brushcol::kColour0 + rgba_f::kB);
    } else {
        // 0x004a56f0
        charge(ctx, 2);
        swc1(f0, a0, rt2d_brushcol::kColour0 + rgba_f::kB);
    }
    // 0x004a5724
    charge(ctx, 12);
    v0 = flt(255.0f);
    lwc1(f2, t2, rgba_f::kA);
    lwc1(f4, t0, rgba_f::kA);
    lwc1(f3, t1, rgba_f::kA);
    mtc1(zero, f0);
    mtc1(v0, f1);
    adda_s(f0, f2);
    madd_s(f2, f4, f3);
    c_le_s(f2, f1);
    if (cond(ctx)) {
        // 0x004a5754
        charge(ctx, 1);
        mov_s(f1, f2);
    }
    // 0x004a5758
    charge(ctx, 5);
    mtc1(zero, f0);
    c_lt_s(f0, f1);
    if (cond(ctx)) {
        // 0x004a5774
        charge(ctx, 6);
        v0 = flt(255.0f);
        mtc1(v0, f0);
        c_le_s(f2, f0);
        if (!cond(ctx)) {
            // 0x004a5794
            charge(ctx, 2);
            mov_s(f2, f0);
            mov_s(f0, f2);
        } else {
            // 0x004a578c
            charge(ctx, 2);
            mov_s(f0, f2);
        }
        // 0x004a579c
        charge(ctx, 1);
        swc1(f0, a0, rt2d_brushcol::kColour0 + rgba_f::kA);
    } else {
        // 0x004a576c
        charge(ctx, 2);
        swc1(f0, a0, rt2d_brushcol::kColour0 + rgba_f::kA);
    }
    // 0x004a57a0
    charge(ctx, 12);
    v0 = flt(255.0f);
    lwc1(f2, t2, rgba_f::kR);
    lwc1(f4, a3, rgba_f::kR);
    lwc1(f3, t1, rgba_f::kR);
    mtc1(zero, f0);
    mtc1(v0, f1);
    adda_s(f0, f2);
    madd_s(f2, f4, f3);
    c_le_s(f2, f1);
    if (cond(ctx)) {
        // 0x004a57d0
        charge(ctx, 1);
        mov_s(f1, f2);
    }
    // 0x004a57d4
    charge(ctx, 5);
    mtc1(zero, f0);
    c_lt_s(f0, f1);
    if (cond(ctx)) {
        // 0x004a57f0
        charge(ctx, 6);
        v0 = flt(255.0f);
        mtc1(v0, f0);
        c_le_s(f2, f0);
        if (!cond(ctx)) {
            // 0x004a5810
            charge(ctx, 2);
            mov_s(f2, f0);
            mov_s(f0, f2);
        } else {
            // 0x004a5808
            charge(ctx, 2);
            mov_s(f0, f2);
        }
        // 0x004a5818
        charge(ctx, 1);
        swc1(f0, a0, rt2d_brushcol::kColour1 + rgba_f::kR);
    } else {
        // 0x004a57e8
        charge(ctx, 2);
        swc1(f0, a0, rt2d_brushcol::kColour1 + rgba_f::kR);
    }
    // 0x004a581c
    charge(ctx, 12);
    v0 = flt(255.0f);
    lwc1(f2, t2, rgba_f::kG);
    lwc1(f4, a3, rgba_f::kG);
    lwc1(f3, t1, rgba_f::kG);
    mtc1(zero, f0);
    mtc1(v0, f1);
    adda_s(f0, f2);
    madd_s(f2, f4, f3);
    c_le_s(f2, f1);
    if (cond(ctx)) {
        // 0x004a584c
        charge(ctx, 1);
        mov_s(f1, f2);
    }
    // 0x004a5850
    charge(ctx, 5);
    mtc1(zero, f0);
    c_lt_s(f0, f1);
    if (cond(ctx)) {
        // 0x004a586c
        charge(ctx, 6);
        v0 = flt(255.0f);
        mtc1(v0, f0);
        c_le_s(f2, f0);
        if (!cond(ctx)) {
            // 0x004a588c
            charge(ctx, 2);
            mov_s(f2, f0);
            mov_s(f0, f2);
        } else {
            // 0x004a5884
            charge(ctx, 2);
            mov_s(f0, f2);
        }
        // 0x004a5894
        charge(ctx, 1);
        swc1(f0, a0, rt2d_brushcol::kColour1 + rgba_f::kG);
    } else {
        // 0x004a5864
        charge(ctx, 2);
        swc1(f0, a0, rt2d_brushcol::kColour1 + rgba_f::kG);
    }
    // 0x004a5898
    charge(ctx, 12);
    v0 = flt(255.0f);
    lwc1(f2, t2, rgba_f::kB);
    lwc1(f4, a3, rgba_f::kB);
    lwc1(f3, t1, rgba_f::kB);
    mtc1(zero, f0);
    mtc1(v0, f1);
    adda_s(f0, f2);
    madd_s(f2, f4, f3);
    c_le_s(f2, f1);
    if (cond(ctx)) {
        // 0x004a58c8
        charge(ctx, 1);
        mov_s(f1, f2);
    }
    // 0x004a58cc
    charge(ctx, 5);
    mtc1(zero, f0);
    c_lt_s(f0, f1);
    if (cond(ctx)) {
        // 0x004a58e8
        charge(ctx, 6);
        v0 = flt(255.0f);
        mtc1(v0, f0);
        c_le_s(f2, f0);
        if (!cond(ctx)) {
            // 0x004a5908
            charge(ctx, 2);
            mov_s(f2, f0);
            mov_s(f0, f2);
        } else {
            // 0x004a5900
            charge(ctx, 2);
            mov_s(f0, f2);
        }
        // 0x004a5910
        charge(ctx, 1);
        swc1(f0, a0, rt2d_brushcol::kColour1 + rgba_f::kB);
    } else {
        // 0x004a58e0
        charge(ctx, 2);
        swc1(f0, a0, rt2d_brushcol::kColour1 + rgba_f::kB);
    }
    // 0x004a5914
    charge(ctx, 12);
    v0 = flt(255.0f);
    lwc1(f2, t2, rgba_f::kA);
    lwc1(f4, a3, rgba_f::kA);
    lwc1(f3, t1, rgba_f::kA);
    mtc1(zero, f0);
    mtc1(v0, f1);
    adda_s(f0, f2);
    madd_s(f2, f4, f3);
    c_le_s(f2, f1);
    if (cond(ctx)) {
        // 0x004a5944
        charge(ctx, 1);
        mov_s(f1, f2);
    }
    // 0x004a5948
    charge(ctx, 5);
    mtc1(zero, f0);
    c_lt_s(f0, f1);
    if (cond(ctx)) {
        // 0x004a5964
        charge(ctx, 6);
        v0 = flt(255.0f);
        mtc1(v0, f0);
        c_le_s(f2, f0);
        if (!cond(ctx)) {
            // 0x004a5984
            charge(ctx, 2);
            mov_s(f2, f0);
            mov_s(f0, f2);
        } else {
            // 0x004a597c
            charge(ctx, 2);
            mov_s(f0, f2);
        }
        // 0x004a598c
        charge(ctx, 1);
        swc1(f0, a0, rt2d_brushcol::kColour1 + rgba_f::kA);
    } else {
        // 0x004a595c
        charge(ctx, 2);
        swc1(f0, a0, rt2d_brushcol::kColour1 + rgba_f::kA);
    }
    // 0x004a5990
    charge(ctx, 12);
    v0 = flt(255.0f);
    lwc1(f2, t2, rgba_f::kR);
    lwc1(f4, a1, rgba_f::kR);
    lwc1(f3, t1, rgba_f::kR);
    mtc1(zero, f0);
    mtc1(v0, f1);
    adda_s(f0, f2);
    madd_s(f2, f4, f3);
    c_le_s(f2, f1);
    if (cond(ctx)) {
        // 0x004a59c0
        charge(ctx, 1);
        mov_s(f1, f2);
    }
    // 0x004a59c4
    charge(ctx, 5);
    mtc1(zero, f0);
    c_lt_s(f0, f1);
    if (cond(ctx)) {
        // 0x004a59e0
        charge(ctx, 6);
        v0 = flt(255.0f);
        mtc1(v0, f0);
        c_le_s(f2, f0);
        if (!cond(ctx)) {
            // 0x004a5a00
            charge(ctx, 2);
            mov_s(f2, f0);
            mov_s(f0, f2);
        } else {
            // 0x004a59f8
            charge(ctx, 2);
            mov_s(f0, f2);
        }
        // 0x004a5a08
        charge(ctx, 1);
        swc1(f0, a0, rt2d_brushcol::kColour2 + rgba_f::kR);
    } else {
        // 0x004a59d8
        charge(ctx, 2);
        swc1(f0, a0, rt2d_brushcol::kColour2 + rgba_f::kR);
    }
    // 0x004a5a0c
    charge(ctx, 12);
    v0 = flt(255.0f);
    lwc1(f2, t2, rgba_f::kG);
    lwc1(f4, a1, rgba_f::kG);
    lwc1(f3, t1, rgba_f::kG);
    mtc1(zero, f0);
    mtc1(v0, f1);
    adda_s(f0, f2);
    madd_s(f2, f4, f3);
    c_le_s(f2, f1);
    if (cond(ctx)) {
        // 0x004a5a3c
        charge(ctx, 1);
        mov_s(f1, f2);
    }
    // 0x004a5a40
    charge(ctx, 5);
    mtc1(zero, f0);
    c_lt_s(f0, f1);
    if (cond(ctx)) {
        // 0x004a5a5c
        charge(ctx, 6);
        v0 = flt(255.0f);
        mtc1(v0, f0);
        c_le_s(f2, f0);
        if (!cond(ctx)) {
            // 0x004a5a7c
            charge(ctx, 2);
            mov_s(f2, f0);
            mov_s(f0, f2);
        } else {
            // 0x004a5a74
            charge(ctx, 2);
            mov_s(f0, f2);
        }
        // 0x004a5a84
        charge(ctx, 1);
        swc1(f0, a0, rt2d_brushcol::kColour2 + rgba_f::kG);
    } else {
        // 0x004a5a54
        charge(ctx, 2);
        swc1(f0, a0, rt2d_brushcol::kColour2 + rgba_f::kG);
    }
    // 0x004a5a88
    charge(ctx, 12);
    v0 = flt(255.0f);
    lwc1(f2, t2, rgba_f::kB);
    lwc1(f4, a1, rgba_f::kB);
    lwc1(f3, t1, rgba_f::kB);
    mtc1(zero, f0);
    mtc1(v0, f1);
    adda_s(f0, f2);
    madd_s(f2, f4, f3);
    c_le_s(f2, f1);
    if (cond(ctx)) {
        // 0x004a5ab8
        charge(ctx, 1);
        mov_s(f1, f2);
    }
    // 0x004a5abc
    charge(ctx, 5);
    mtc1(zero, f0);
    c_lt_s(f0, f1);
    if (cond(ctx)) {
        // 0x004a5ad8
        charge(ctx, 6);
        v0 = flt(255.0f);
        mtc1(v0, f0);
        c_le_s(f2, f0);
        if (!cond(ctx)) {
            // 0x004a5af8
            charge(ctx, 2);
            mov_s(f2, f0);
            mov_s(f0, f2);
        } else {
            // 0x004a5af0
            charge(ctx, 2);
            mov_s(f0, f2);
        }
        // 0x004a5b00
        charge(ctx, 1);
        swc1(f0, a0, rt2d_brushcol::kColour2 + rgba_f::kB);
    } else {
        // 0x004a5ad0
        charge(ctx, 2);
        swc1(f0, a0, rt2d_brushcol::kColour2 + rgba_f::kB);
    }
    // 0x004a5b04
    charge(ctx, 12);
    v0 = flt(255.0f);
    lwc1(f2, t2, rgba_f::kA);
    lwc1(f4, a1, rgba_f::kA);
    lwc1(f3, t1, rgba_f::kA);
    mtc1(zero, f0);
    mtc1(v0, f1);
    adda_s(f0, f2);
    madd_s(f2, f4, f3);
    c_le_s(f2, f1);
    if (cond(ctx)) {
        // 0x004a5b34
        charge(ctx, 1);
        mov_s(f1, f2);
    }
    // 0x004a5b38
    charge(ctx, 5);
    mtc1(zero, f0);
    c_lt_s(f0, f1);
    if (cond(ctx)) {
        // 0x004a5b54
        charge(ctx, 6);
        v0 = flt(255.0f);
        mtc1(v0, f0);
        c_le_s(f2, f0);
        if (!cond(ctx)) {
            // 0x004a5b74
            charge(ctx, 2);
            mov_s(f2, f0);
            mov_s(f0, f2);
        } else {
            // 0x004a5b6c
            charge(ctx, 2);
            mov_s(f0, f2);
        }
        // 0x004a5b7c
        charge(ctx, 1);
        swc1(f0, a0, rt2d_brushcol::kColour2 + rgba_f::kA);
    } else {
        // 0x004a5b4c
        charge(ctx, 2);
        swc1(f0, a0, rt2d_brushcol::kColour2 + rgba_f::kA);
    }
    // 0x004a5b80
    charge(ctx, 12);
    v0 = flt(255.0f);
    lwc1(f2, t2, rgba_f::kR);
    lwc1(f4, a2, rgba_f::kR);
    lwc1(f3, t1, rgba_f::kR);
    mtc1(zero, f0);
    mtc1(v0, f1);
    adda_s(f0, f2);
    madd_s(f2, f4, f3);
    c_le_s(f2, f1);
    if (cond(ctx)) {
        // 0x004a5bb0
        charge(ctx, 1);
        mov_s(f1, f2);
    }
    // 0x004a5bb4
    charge(ctx, 5);
    mtc1(zero, f0);
    c_lt_s(f0, f1);
    if (cond(ctx)) {
        // 0x004a5bd0
        charge(ctx, 6);
        v0 = flt(255.0f);
        mtc1(v0, f0);
        c_le_s(f2, f0);
        if (!cond(ctx)) {
            // 0x004a5bf0
            charge(ctx, 2);
            mov_s(f2, f0);
            mov_s(f0, f2);
        } else {
            // 0x004a5be8
            charge(ctx, 2);
            mov_s(f0, f2);
        }
        // 0x004a5bf8
        charge(ctx, 1);
        swc1(f0, a0, rt2d_brushcol::kColour3 + rgba_f::kR);
    } else {
        // 0x004a5bc8
        charge(ctx, 2);
        swc1(f0, a0, rt2d_brushcol::kColour3 + rgba_f::kR);
    }
    // 0x004a5bfc
    charge(ctx, 12);
    v0 = flt(255.0f);
    lwc1(f2, t2, rgba_f::kG);
    lwc1(f4, a2, rgba_f::kG);
    lwc1(f3, t1, rgba_f::kG);
    mtc1(zero, f0);
    mtc1(v0, f1);
    adda_s(f0, f2);
    madd_s(f2, f4, f3);
    c_le_s(f2, f1);
    if (cond(ctx)) {
        // 0x004a5c2c
        charge(ctx, 1);
        mov_s(f1, f2);
    }
    // 0x004a5c30
    charge(ctx, 5);
    mtc1(zero, f0);
    c_lt_s(f0, f1);
    if (cond(ctx)) {
        // 0x004a5c4c
        charge(ctx, 6);
        v0 = flt(255.0f);
        mtc1(v0, f0);
        c_le_s(f2, f0);
        if (!cond(ctx)) {
            // 0x004a5c6c
            charge(ctx, 2);
            mov_s(f2, f0);
            mov_s(f0, f2);
        } else {
            // 0x004a5c64
            charge(ctx, 2);
            mov_s(f0, f2);
        }
        // 0x004a5c74
        charge(ctx, 1);
        swc1(f0, a0, rt2d_brushcol::kColour3 + rgba_f::kG);
    } else {
        // 0x004a5c44
        charge(ctx, 2);
        swc1(f0, a0, rt2d_brushcol::kColour3 + rgba_f::kG);
    }
    // 0x004a5c78
    charge(ctx, 12);
    v0 = flt(255.0f);
    lwc1(f2, t2, rgba_f::kB);
    lwc1(f4, a2, rgba_f::kB);
    lwc1(f3, t1, rgba_f::kB);
    mtc1(zero, f0);
    mtc1(v0, f1);
    adda_s(f0, f2);
    madd_s(f2, f4, f3);
    c_le_s(f2, f1);
    if (cond(ctx)) {
        // 0x004a5ca8
        charge(ctx, 1);
        mov_s(f1, f2);
    }
    // 0x004a5cac
    charge(ctx, 5);
    mtc1(zero, f0);
    c_lt_s(f0, f1);
    if (cond(ctx)) {
        // 0x004a5cc8
        charge(ctx, 6);
        v0 = flt(255.0f);
        mtc1(v0, f0);
        c_le_s(f2, f0);
        if (!cond(ctx)) {
            // 0x004a5ce8
            charge(ctx, 2);
            mov_s(f2, f0);
            mov_s(f0, f2);
        } else {
            // 0x004a5ce0
            charge(ctx, 2);
            mov_s(f0, f2);
        }
        // 0x004a5cf0
        charge(ctx, 1);
        swc1(f0, a0, rt2d_brushcol::kColour3 + rgba_f::kB);
    } else {
        // 0x004a5cc0
        charge(ctx, 2);
        swc1(f0, a0, rt2d_brushcol::kColour3 + rgba_f::kB);
    }
    // 0x004a5cf4
    charge(ctx, 12);
    v0 = flt(255.0f);
    lwc1(f2, t2, rgba_f::kA);
    lwc1(f4, a2, rgba_f::kA);
    lwc1(f3, t1, rgba_f::kA);
    mtc1(zero, f0);
    mtc1(v0, f1);
    adda_s(f0, f2);
    madd_s(f2, f4, f3);
    c_le_s(f2, f1);
    if (cond(ctx)) {
        // 0x004a5d24
        charge(ctx, 1);
        mov_s(f1, f2);
    }
    // 0x004a5d28
    charge(ctx, 5);
    mtc1(zero, f0);
    c_lt_s(f0, f1);
    if (cond(ctx)) {
        // 0x004a5d44
        charge(ctx, 6);
        v0 = flt(255.0f);
        mtc1(v0, f0);
        c_le_s(f2, f0);
        if (!cond(ctx)) {
            // 0x004a5d64
            charge(ctx, 2);
            mov_s(f2, f0);
            mov_s(f0, f2);
        } else {
            // 0x004a5d5c
            charge(ctx, 2);
            mov_s(f0, f2);
        }
        // 0x004a5d6c
        charge(ctx, 1);
        swc1(f0, a0, rt2d_brushcol::kColour3 + rgba_f::kA);
    } else {
        // 0x004a5d3c
        charge(ctx, 2);
        swc1(f0, a0, rt2d_brushcol::kColour3 + rgba_f::kA);
    }
    // 0x004a5d70 (the shared epilogue, written out on this path)
    charge(ctx, 21);
    v0 = a0;
    lwc1(f0, a0, rt2d_brushcol::kColour0 + rgba_f::kR);
    cvt_w_s(f0, f0);
    mfc1(v1, f0);
    sb(v1, a0, rt2d_brushcol::kPacked + 0);
    lwc1(f0, a0, rt2d_brushcol::kColour0 + rgba_f::kG);
    cvt_w_s(f0, f0);
    mfc1(v1, f0);
    sb(v1, a0, rt2d_brushcol::kPacked + 1);
    lwc1(f0, a0, rt2d_brushcol::kColour0 + rgba_f::kB);
    cvt_w_s(f0, f0);
    mfc1(v1, f0);
    sb(v1, a0, rt2d_brushcol::kPacked + 2);
    lwc1(f0, a0, rt2d_brushcol::kColour0 + rgba_f::kA);
    cvt_w_s(f0, f0);
    mfc1(v1, f0);
    sb(v1, a0, rt2d_brushcol::kPacked + 3);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4A55B0(EEContext& ctx, u64 brush, u64 c2, u64 c3, u64 c1) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(brush));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(c2));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(c3));
    ee::core::set_gpr64(ctx, GPR_A3, static_cast<u64>(c1));
    sub_4A55B0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004A9A70 sub_4A9A70 -- 12 bytes; leaf frame (no stack)
// sub_4A9A70 [a jr tail call through +312 of $a0 (an Rt2d font's render callback)].
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4A9A70(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::tail;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x004a9a70
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, rt2d_font::kDrawCb);
    tail(ctx, v0.u());  // jr: the target's entry point
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_4A9A70(EEContext& ctx, u64 font) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(font));
    sub_4A9A70(ctx);
}
u64 sub_4AAB40(EEContext& ctx, u64 matrix) {
    ee::core::set_gpr64(ctx, GPR_A0, matrix);
    c3::detail::Cpu(ctx).sub_4AAB40();
    return ee::core::gpr64(ctx, GPR_V0);
}

// 0x004AAC70 sub_4AAC70 -- 224 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4AAC70 [Rt2dCTMSet-push(matrix)]: a new CTM = a copy of `matrix`. Returns 1, or 0 when the stack is full.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4AAC70(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::jal, hg::ld, hg::lq,
          hg::lw, hg::sd, hg::sll, hg::slti, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004aac70
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = hi(kRt2dCtmDepth);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, v0, lo(kRt2dCtmDepth));
    s0 = slti(v0, 31);
    s1 = a0;
    if (s0 != 0) {
        // 0x004aac94
        charge(ctx, 10);
        v1 = addiu(v0, 1);
        v0 = hi(kRt2dCtmDepth);
        sw(v1, v0, lo(kRt2dCtmDepth));
        v0 = hi(kRt2dCtmStack);
        v1 = sll(v1, 2);
        v0 = addiu(v0, lo(kRt2dCtmStack));
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        if (v0 == 0) {
            // 0x004aad14
            charge(ctx, 10);
            jal(ctx, 0x4AAD14u, gen::fn_sub_4C38C0_004c38c0);
            v1 = hi(kRt2dCtmDepth);
            a0 = hi(kRt2dCtmStack);
            lw(v1, v1, lo(kRt2dCtmDepth));
            a0 = addiu(a0, lo(kRt2dCtmStack));
            v1 = sll(v1, 2);
            v1 = addu(a0, v1);
            sw(v0, v1, 0);
            backedge(ctx);
        }
        // 0x004aacbc
        charge(ctx, 8);
        v0 = hi(kRt2dCtmDepth);
        v1 = hi(kRt2dCtmStack);
        lw(v0, v0, lo(kRt2dCtmDepth));
        v1 = addiu(v1, lo(kRt2dCtmStack));
        a0 = 8;
        v0 = sll(v0, 2);
        v0 = addu(v1, v0);
        lw(a1, v0, 0);
        for (;;) {
            // 0x004aacdc
            charge(ctx, 8);
            lw(v1, s1, 0);
            a0 = addiu(a0, -1);
            lw(v0, s1, 4);
            sw(v1, a1, 0);
            s1 = addiu(s1, 8);
            sw(v0, a1, 4);
            a1 = addiu(a1, 8);
            if (i64(a0) <= 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004aacfc
    charge(ctx, 6);
    v1 = hi(kRt2dDeviceValid);
    v0 = s0;
    sw(zero, v1, lo(kRt2dDeviceValid));
    v1 = hi(kRt2dCtmWord64);
    sw(zero, v1, lo(kRt2dCtmWord64));
    // 0x004aad3c
    charge(ctx, 5);
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4AAC70(EEContext& ctx, u64 matrix) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(matrix));
    sub_4AAC70(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
void sub_4AAD50(EEContext& ctx) {
    c3::detail::Cpu(ctx).sub_4AAD50();
}
u64 sub_4AB0C0(EEContext& ctx) {
    c3::detail::Cpu(ctx).sub_4AB0C0();
    return ee::core::gpr64(ctx, GPR_V0);
}

// 0x004AB910 sub_4AB910 -- 260 bytes; leaf frame (no stack)
// sub_4AB910 [split a cubic Bezier at t = 1/2 (de Casteljau)]: $a0 the four control points (x, y pairs), $a1 / $a2
// the two halves.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4AB910(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::add_s, hg::enter, hg::lwc1, hg::mtc1, hg::mul_s, hg::swc1;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9};
    // 0x004ab910
    enter(ctx, 65);  // entry check point + this block's cycles
    lwc1(f7, a0, 8);
    v1 = flt(0.5f);
    lwc1(f9, a0, 16);
    lwc1(f2, a0, 0);
    mtc1(v1, f0);
    lwc1(f4, a0, 12);
    lwc1(f3, a0, 4);
    lwc1(f5, a0, 20);
    add_s(f6, f7, f9);
    mul_s(f8, f6, f0);
    add_s(f2, f2, f7);
    lwc1(f6, a0, 24);
    lwc1(f1, a0, 28);
    add_s(f3, f3, f4);
    mul_s(f2, f0, f2);
    add_s(f6, f6, f9);
    add_s(f4, f4, f5);
    add_s(f1, f1, f5);
    swc1(f2, a1, 8);
    mul_s(f2, f0, f3);
    mul_s(f5, f0, f1);
    swc1(f2, a1, 12);
    mul_s(f6, f0, f6);
    swc1(f6, a2, 16);
    swc1(f5, a2, 20);
    lwc1(f5, a1, 8);
    mul_s(f7, f4, f0);
    lwc1(f6, a1, 12);
    add_s(f5, f5, f8);
    mul_s(f5, f0, f5);
    add_s(f6, f6, f7);
    swc1(f5, a1, 16);
    mul_s(f5, f0, f6);
    swc1(f5, a1, 20);
    lwc1(f5, a2, 16);
    lwc1(f6, a2, 20);
    lwc1(f4, a0, 0);
    lwc1(f3, a0, 4);
    lwc1(f2, a0, 24);
    lwc1(f1, a0, 28);
    add_s(f5, f5, f8);
    mul_s(f5, f0, f5);
    add_s(f6, f6, f7);
    swc1(f5, a2, 8);
    mul_s(f5, f0, f6);
    swc1(f5, a2, 12);
    lwc1(f6, a1, 16);
    lwc1(f5, a2, 8);
    lwc1(f8, a1, 20);
    lwc1(f7, a2, 12);
    add_s(f5, f6, f5);
    mul_s(f5, f0, f5);
    add_s(f7, f8, f7);
    mul_s(f0, f0, f7);
    swc1(f5, a1, 24);
    swc1(f0, a1, 28);
    swc1(f4, a1, 0);
    swc1(f3, a1, 4);
    lwc1(f3, a1, 24);
    lwc1(f0, a1, 28);
    swc1(f3, a2, 0);
    swc1(f0, a2, 4);
    swc1(f2, a2, 24);
    swc1(f1, a2, 28);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_4AB910(EEContext& ctx, u64 points, u64 left, u64 right) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(points));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(left));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(right));
    sub_4AB910(ctx);
}

// 0x004ABA20 sub_4ABA20 -- 816 bytes; frame 0x80: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4ABA20 [flatten a cubic Bezier into line points]: $a0 the flattened path, $a1 the four control points, $a2 the
// recursion budget. When the budget is spent or both inner control points lie within the tolerance (0x95EF60) of the
// chord, the end point is appended; otherwise the curve is split (sub_4AB910 into two 32-byte frame buffers) and both
// halves flattened with budget - 1.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: frame/spills (own frame)).
void sub_4ABA20(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::backedge, hg::c_le_s, hg::c_lt_s, hg::call, hg::charge,
          hg::cond, hg::div_s, hg::enter, hg::jal, hg::ld, hg::link, hg::lq, hg::lw, hg::lwc1, hg::madd_s, hg::mov_s,
          hg::mtc1, hg::mul_s, hg::mula_s, hg::sd, hg::slt, hg::slti, hg::sq, hg::sqrt_s, hg::sub_s, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8};
    // 0x004aba20
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    s1 = a2;
    sq(s0, sp, 0x0);
    s1 = addiu(s1, -1);
    v0 = slt(s1, 0);
    s0 = a1;
    if (v0 != 0) {
        // 0x004abc04
        charge(ctx, 26);
        link(ctx, 0x4ABC04u);  // $ra first: the delay slot below depends on it
        lw(a0, s2, rt2d_flat::kArray);
        call(ctx, gen::fn_sub_4C2120_004c2120);
        lw(a0, s2, rt2d_flat::kArray);
        s1 = v0;
        v0 = 0x30000;
        a1 = v0 | 0x190;
        jal(ctx, 0x4ABC18u, gen::fn_sub_4C1E70_004c1e70);
        lwc1(f4, s0, 24);
        v1 = 1;
        lwc1(f3, s0, 28);
        sw(v1, v0, 0);
        mtc1(zero, f0);
        swc1(f4, v0, 4);
        swc1(f3, v0, 8);
        lwc1(f2, v0, -16);
        lwc1(f1, v0, -20);
        sub_s(f2, f3, f2);
        sub_s(f3, f1, f4);
        mula_s(f3, f3);
        madd_s(f1, f2, f2);
        sqrt_s(f4, f1);
        c_le_s(f4, f0);
        if (cond(ctx)) {
            // 0x004abc8c
            charge(ctx, 1);
            mov_s(f0, f4);
        } else {
            // 0x004abc6c
            charge(ctx, 8);
            v1 = flt(1.0f);
            mtc1(v1, f0);
            div_s(f0, f0, f4);
        }
        // 0x004abc90
        charge(ctx, 9);
        mul_s(f1, f2, f0);
        at = slti(s1, 2);
        mul_s(f0, f3, f0);
        swc1(f1, v0, 12);
        swc1(f0, v0, 16);
        lwc1(f0, v0, -4);
        add_s(f0, f0, f4);
        swc1(f0, v0, 20);
        if (at != 0) {
            // 0x004abcf4
            charge(ctx, 5);
            lwc1(f1, v0, 12);
            lwc1(f0, v0, 16);
            swc1(f1, v0, -12);
            swc1(f0, v0, -8);
            backedge(ctx);
        } else {
            // 0x004abcb4
            charge(ctx, 16);
            lwc1(f5, v0, -12);
            v1 = flt(1.0f);
            lwc1(f2, v0, 12);
            lwc1(f3, v0, -8);
            lwc1(f1, v0, 16);
            mtc1(v1, f0);
            add_s(f4, f5, f2);
            add_s(f2, f3, f1);
            mula_s(f3, f2);
            madd_s(f1, f5, f4);
            div_s(f0, f0, f1);
            mul_s(f1, f4, f0);
            mul_s(f0, f2, f0);
            swc1(f1, v0, -12);
            swc1(f0, v0, -8);
            backedge(ctx);
        }
    } else {
        // 0x004aba4c
        charge(ctx, 24);
        lwc1(f5, s0, 4);
        v0 = hi(kRt2dTolerance);
        lwc1(f2, s0, 28);
        lwc1(f4, v0, lo(kRt2dTolerance));
        lwc1(f6, s0, 0);
        lwc1(f1, s0, 8);
        lwc1(f3, s0, 24);
        lwc1(f0, s0, 12);
        sub_s(f7, f2, f5);
        sub_s(f2, f1, f6);
        sub_s(f3, f3, f6);
        mula_s(f7, f7);
        sub_s(f1, f0, f5);
        madd_s(f8, f3, f3);
        mula_s(f1, f7);
        madd_s(f0, f2, f3);
        mula_s(f1, f1);
        madd_s(f1, f2, f2);
        sub_s(f1, f1, f4);
        mul_s(f0, f0, f0);
        mul_s(f1, f8, f1);
        c_lt_s(f1, f0);
        v0 = 1;
        if (!cond(ctx)) {
            // 0x004abaac
            charge(ctx, 1);
            v0 = 0;
        }
        // 0x004abab0
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x004abab8
            charge(ctx, 14);
            lwc1(f0, s0, 20);
            lwc1(f1, s0, 16);
            sub_s(f0, f0, f5);
            sub_s(f1, f1, f6);
            mula_s(f0, f7);
            madd_s(f2, f1, f3);
            mula_s(f0, f0);
            madd_s(f0, f1, f1);
            sub_s(f0, f0, f4);
            mul_s(f1, f8, f0);
            mul_s(f0, f2, f2);
            c_lt_s(f1, f0);
            v0 = 1;
            if (!cond(ctx)) {
                // 0x004abaf0
                charge(ctx, 1);
                v0 = 0;
            }
        }
        // 0x004abaf4
        charge(ctx, 2);
        if (v0 == 0) {
            // 0x004abd08
            charge(ctx, 13);
            a0 = s0;
            a1 = addiu(sp, 0x60);
            a2 = addiu(sp, 0x40);
            jal(ctx, 0x4ABD10u, gen::fn_sub_4AB910_004ab910);
            a0 = s2;
            a2 = s1;
            jal(ctx, 0x4ABD1Cu, gen::fn_sub_4ABA20_004aba20);
            a0 = s2;
            a2 = s1;
            a1 = addiu(sp, 0x40);
            jal(ctx, 0x4ABD2Cu, gen::fn_sub_4ABA20_004aba20);
            backedge(ctx);
        } else {
            // 0x004abafc
            charge(ctx, 26);
            link(ctx, 0x4ABAFCu);  // $ra first: the delay slot below depends on it
            lw(a0, s2, rt2d_flat::kArray);
            call(ctx, gen::fn_sub_4C2120_004c2120);
            lw(a0, s2, rt2d_flat::kArray);
            s1 = v0;
            v0 = 0x30000;
            a1 = v0 | 0x190;
            jal(ctx, 0x4ABB10u, gen::fn_sub_4C1E70_004c1e70);
            lwc1(f4, s0, 24);
            v1 = 1;
            lwc1(f3, s0, 28);
            sw(v1, v0, 0);
            mtc1(zero, f0);
            swc1(f4, v0, 4);
            swc1(f3, v0, 8);
            lwc1(f2, v0, -16);
            lwc1(f1, v0, -20);
            sub_s(f2, f3, f2);
            sub_s(f3, f1, f4);
            mula_s(f3, f3);
            madd_s(f1, f2, f2);
            sqrt_s(f4, f1);
            c_le_s(f4, f0);
            if (cond(ctx)) {
                // 0x004abb84
                charge(ctx, 1);
                mov_s(f0, f4);
            } else {
                // 0x004abb64
                charge(ctx, 8);
                v1 = flt(1.0f);
                mtc1(v1, f0);
                div_s(f0, f0, f4);
            }
            // 0x004abb88
            charge(ctx, 9);
            mul_s(f1, f2, f0);
            at = slti(s1, 2);
            mul_s(f0, f3, f0);
            swc1(f1, v0, 12);
            swc1(f0, v0, 16);
            lwc1(f0, v0, -4);
            add_s(f0, f0, f4);
            swc1(f0, v0, 20);
            if (at != 0) {
                // 0x004abbec
                charge(ctx, 4);
                lwc1(f1, v0, 12);
                lwc1(f0, v0, 16);
                swc1(f1, v0, -12);
                swc1(f0, v0, -8);
            } else {
                // 0x004abbac
                charge(ctx, 16);
                lwc1(f5, v0, -12);
                v1 = flt(1.0f);
                lwc1(f2, v0, 12);
                lwc1(f3, v0, -8);
                lwc1(f1, v0, 16);
                mtc1(v1, f0);
                add_s(f4, f5, f2);
                add_s(f2, f3, f1);
                mula_s(f3, f2);
                madd_s(f1, f5, f4);
                div_s(f0, f0, f1);
                mul_s(f1, f4, f0);
                mul_s(f0, f2, f0);
                swc1(f1, v0, -12);
                swc1(f0, v0, -8);
            }
        }
    }
    // 0x004abbfc
    charge(ctx, 2);
    ld(ra, sp, 0x30);
    // 0x004abd3c
    charge(ctx, 5);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x80);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_4ABA20(EEContext& ctx, u64 dst, u64 points, u64 budget) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(dst));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(points));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(budget));
    sub_4ABA20(ctx);
}

// 0x004AC020 sub_4AC020 -- 248 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4AC020 [Rt2dPathGetBBox-like]: $a0 the path ({+0 the point array, +4 its count or -1 to ask the array}), $a1 the
// box {min x, min y, max x, max y} grown over every point (24-byte records, x +4, y +8). Returns the box.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: frame/spills (own frame)).
void sub_4AC020(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::backedge, hg::c_le_s, hg::c_lt_s, hg::call, hg::charge, hg::cond,
          hg::enter, hg::ld, hg::link, hg::lq, hg::lw, hg::lwc1, hg::sd, hg::si, hg::slt, hg::sq, hg::swc1;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x004ac020
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    lw(v1, a0, rt2d_flat::kCount);
    sd(ra, sp, 0x30);
    v0 = si(-1);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    s2 = a0;
    sq(s0, sp, 0x0);
    s0 = a1;
    if (v1 != v0) {
        // 0x004ac058
        charge(ctx, 2);
        lw(v0, s2, rt2d_flat::kArray);
        s1 = v0;
    } else {
        // 0x004ac048
        charge(ctx, 4);
        link(ctx, 0x4AC048u);  // $ra first: the delay slot below depends on it
        lw(a0, s2, rt2d_flat::kArray);
        call(ctx, gen::fn_sub_4C2090_004c2090);
        s1 = v0;
    }
    // 0x004ac060
    charge(ctx, 4);
    v1 = si(-1);
    lw(v0, s2, rt2d_flat::kCount);
    if (v0 == v1) {
        // 0x004ac070
        charge(ctx, 2);
        link(ctx, 0x4AC070u);  // $ra first: the delay slot below depends on it
        lw(a0, s2, rt2d_flat::kArray);
        call(ctx, gen::fn_sub_4C2120_004c2120);
    }
    // 0x004ac078
    charge(ctx, 3);
    at = slt(0, v0);
    a0 = 0;
    if (at != 0) {
        for (;;) {
            // 0x004ac084
            charge(ctx, 5);
            lwc1(f1, s1, rt2d_point::kX);
            lwc1(f0, s0, rect::kX);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x004ac0f0
                charge(ctx, 2);
                swc1(f1, s0, rect::kX);
                backedge(ctx);
            } else {
                // 0x004ac098
                charge(ctx, 4);
                lwc1(f0, s0, rect::kW);
                c_le_s(f1, f0);
                if (!cond(ctx)) {
                    // 0x004ac0a8
                    charge(ctx, 2);
                    swc1(f1, s0, rect::kW);
                }
            }
            // 0x004ac0b0
            charge(ctx, 5);
            lwc1(f1, s1, rt2d_point::kY);
            lwc1(f0, s0, rect::kY);
            c_lt_s(f1, f0);
            if (cond(ctx)) {
                // 0x004ac0f8
                charge(ctx, 2);
                swc1(f1, s0, rect::kY);
                backedge(ctx);
            } else {
                // 0x004ac0c4
                charge(ctx, 4);
                lwc1(f0, s0, rect::kH);
                c_le_s(f1, f0);
                if (!cond(ctx)) {
                    // 0x004ac0d4
                    charge(ctx, 1);
                    swc1(f1, s0, rect::kH);
                }
            }
            // 0x004ac0d8
            charge(ctx, 4);
            a0 = addiu(a0, 1);
            v1 = slt(a0, v0);
            s1 = addiu(s1, 24);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004ac0e8
    charge(ctx, 2);
    v0 = s0;
    // 0x004ac100
    charge(ctx, 6);
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4AC020(EEContext& ctx, u64 path, u64 box) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(path));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(box));
    sub_4AC020(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_4AC390(EEContext& ctx, u64 node) {
    ee::core::set_gpr64(ctx, GPR_A0, node);
    c3::detail::Cpu(ctx).sub_4AC390();
    return ee::core::gpr64(ctx, GPR_V0);
}

// 0x004AE690 sub_4AE690 -- 256 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4AE690 [Rt2dSceneUpdateLTM-like: sort the scene's children by depth]: $a0 the scene (+180 the child count,
// +184 the child array {object, depth} pairs, 8 bytes): each pair's depth refreshed from its object (+4), then a
// selection sort by depth (swapping through the frame at sp + 40). Returns the scene.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4AE690(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::enter, hg::ld, hg::link,
          hg::lq, hg::lw, hg::lwc1, hg::sd, hg::sll, hg::slt, hg::sltu, hg::sq, hg::sw, hg::swc1;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x004ae690
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    link(ctx, 0x4AE6A0u);  // $ra first: the delay slot below depends on it
    lw(a0, a0, rt2d_scene::kChildren);
    call(ctx, gen::fn_sub_4C2090_004c2090);
    lw(v1, s0, rt2d_scene::kChildCount);
    v1 = sll(v1, 3);
    a2 = addu(v0, v1);
    if (v0 == a2) {
        // 0x004ae6e8
        charge(ctx, 2);
        v0 = s0;
    } else {
        // 0x004ae6bc
        charge(ctx, 2);
        a0 = v0;
        if (v0 == a2) {
            // 0x004ae6f0
            charge(ctx, 1);
            a1 = addiu(a2, -8);
        } else {
            for (;;) {
                // 0x004ae6c4
                charge(ctx, 7);
                lw(v1, a0, 0);
                lw(v1, v1, 4);
                sw(v1, a0, 4);
                a0 = addiu(a0, 8);
                if (a0 == a2) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004ae6e0
            charge(ctx, 2);
            a1 = addiu(a2, -8);
        }
        // 0x004ae6f4
        charge(ctx, 3);
        at = sltu(v0, a1);
        if (at != 0) {
            for (;;) {
                // 0x004ae700
                charge(ctx, 4);
                a3 = addiu(v0, 8);
                at = sltu(a3, a2);
                if (at != 0) {
                    for (;;) {
                        // 0x004ae710
                        charge(ctx, 5);
                        lw(a0, v0, 4);
                        lw(v1, a3, 4);
                        at = slt(v1, a0);
                        if (at != 0) {
                            // 0x004ae750
                            charge(ctx, 11);
                            lwc1(f3, v0, 0);
                            lwc1(f2, v0, 4);
                            lwc1(f1, a3, 0);
                            lwc1(f0, a3, 4);
                            swc1(f3, sp, 0x28);
                            swc1(f2, sp, 0x2C);
                            swc1(f1, v0, 0);
                            swc1(f0, v0, 4);
                            swc1(f3, a3, 0);
                            swc1(f2, a3, 4);
                            backedge(ctx);
                        } else {
                            // 0x004ae724
                            charge(ctx, 1);
                        }
                        // 0x004ae728
                        charge(ctx, 4);
                        a3 = addiu(a3, 8);
                        v1 = sltu(a3, a2);
                        if (v1 == 0) {
                            break;
                        }
                        backedge(ctx);
                    }
                }
                // 0x004ae738
                charge(ctx, 4);
                v0 = addiu(v0, 8);
                v1 = sltu(v0, a1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x004ae748
        charge(ctx, 2);
        v0 = s0;
    }
    // 0x004ae780 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4AE690(EEContext& ctx, u64 scene) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(scene));
    sub_4AE690(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_4AB8C0(EEContext& ctx) {
    c3::detail::Cpu(ctx).sub_4AB8C0();
    return ee::core::gpr64(ctx, GPR_V0);
}

// 0x004AB6A0 sub_4AB6A0 -- 540 bytes; frame 0x70: ra sp+0x50, s3 sp+0x40 (sq), s2 sp+0x30 (sq), s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// sub_4AB6A0 [Rt2dPathClose on a flattened path]: $a0 the path, +24 its flattened copy ({+0 the point array}). When
// the last point differs from the first, the first is appended again (its normal computed); the closing point's and
// the first point's normals become their normalised average; +8 (closed) = 1. Returns the path. ($f20 is spilled to
// the frame and restored.)
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4AB6A0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::c_eq_s, hg::c_le_s, hg::call, hg::charge, hg::cond, hg::div_s,
          hg::enter, hg::jal, hg::ld, hg::link, hg::lq, hg::lw, hg::lwc1, hg::madd_s, hg::mov_s, hg::mtc1, hg::mul_s,
          hg::mula_s, hg::sd, hg::slti, hg::sq, hg::sqrt_s, hg::sub_s, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f20{ctx, 20};
    // 0x004ab6a0
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x50);
    sq(s3, sp, 0x40);
    sq(s2, sp, 0x30);
    s3 = a0;
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    lw(s1, a0, rt2d_path::kPoints);
    link(ctx, 0x4AB6C4u);  // $ra first: the delay slot below depends on it
    lw(a0, s1, rt2d_flat::kArray);
    call(ctx, gen::fn_sub_4C2120_004c2120);
    lw(a0, s1, rt2d_flat::kArray);
    s2 = v0;
    jal(ctx, 0x4AB6D0u, gen::fn_sub_4C2090_004c2090);
    lw(a0, s1, rt2d_flat::kArray);
    s0 = v0;
    a1 = addiu(s2, -1);
    jal(ctx, 0x4AB6E0u, gen::fn_sub_4C21B0_004c21b0);
    lwc1(f3, s0, rt2d_point::kY);
    v1 = addiu(sp, 0x6C);
    lwc1(f4, s0, rt2d_point::kX);
    lwc1(f2, v0, rt2d_point::kX);
    lwc1(f1, v0, rt2d_point::kY);
    mtc1(zero, f0);
    swc1(f3, sp, 0x6C);
    lwc1(f20, v1, 0);
    sub_s(f2, f2, f4);
    sub_s(f1, f20, f1);
    c_eq_s(f0, f1);
    swc1(f4, sp, 0x68);
    do {
        if (cond(ctx)) {
            // 0x004ab71c: the same y; the same x too?
            charge(ctx, 3);
            c_eq_s(f0, f2);
            if (cond(ctx)) {
                break;  // the last point is the first: no point appended
            }
        }
        // 0x004ab728: append the first point again (sub_4C1E70), its normal and length from the previous point
        charge(ctx, 27);
        lw(v0, s3, rt2d_path::kPoints);
        link(ctx, 0x4AB72Cu);  // $ra first: the delay slot below depends on it
        lw(a0, v0, rt2d_flat::kArray);
        call(ctx, gen::fn_sub_4C2120_004c2120);
        lw(v1, s3, rt2d_path::kPoints);
        s0 = v0;
        v0 = 0x30000;
        lw(a0, v1, rt2d_flat::kArray);
        a1 = v0 | 0x190;
        jal(ctx, 0x4AB744u, gen::fn_sub_4C1E70_004c1e70);
        lwc1(f3, sp, 0x68);
        v1 = 1;
        sw(v1, v0, rt2d_point::kKind);
        mtc1(zero, f0);
        swc1(f3, v0, rt2d_point::kX);
        swc1(f20, v0, rt2d_point::kY);
        lwc1(f1, v0, rt2d_point::kX - rt2d_point::kSize);
        lwc1(f2, v0, rt2d_point::kY - rt2d_point::kSize);
        sub_s(f3, f1, f3);
        sub_s(f2, f20, f2);
        mula_s(f3, f3);
        madd_s(f1, f2, f2);
        sqrt_s(f4, f1);
        c_le_s(f4, f0);
        if (cond(ctx)) {
            // 0x004ab7b4
            charge(ctx, 1);
            mov_s(f0, f4);
        } else {
            // 0x004ab794
            charge(ctx, 8);
            v1 = flt(1.0f);
            mtc1(v1, f0);
            div_s(f0, f0, f4);
        }
        // 0x004ab7b8
        charge(ctx, 9);
        mul_s(f1, f2, f0);
        at = slti(s0, 2);
        mul_s(f0, f3, f0);
        swc1(f1, v0, rt2d_point::kNx);
        swc1(f0, v0, rt2d_point::kNy);
        lwc1(f0, v0, rt2d_point::kLength - rt2d_point::kSize);
        add_s(f0, f0, f4);
        swc1(f0, v0, rt2d_point::kLength);
        if (at != 0) {
            // 0x004ab81c
            charge(ctx, 4);
            lwc1(f1, v0, rt2d_point::kNx);
            lwc1(f0, v0, rt2d_point::kNy);
            swc1(f1, v0, rt2d_point::kNx - rt2d_point::kSize);
            swc1(f0, v0, rt2d_point::kNy - rt2d_point::kSize);
        } else {
            // 0x004ab7dc
            charge(ctx, 16);
            lwc1(f5, v0, rt2d_point::kNx - rt2d_point::kSize);
            v1 = flt(1.0f);
            lwc1(f2, v0, rt2d_point::kNx);
            lwc1(f3, v0, rt2d_point::kNy - rt2d_point::kSize);
            lwc1(f1, v0, rt2d_point::kNy);
            mtc1(v1, f0);
            add_s(f4, f5, f2);
            add_s(f2, f3, f1);
            mula_s(f3, f2);
            madd_s(f1, f5, f4);
            div_s(f0, f0, f1);
            mul_s(f1, f4, f0);
            mul_s(f0, f2, f0);
            swc1(f1, v0, rt2d_point::kNx - rt2d_point::kSize);
            swc1(f0, v0, rt2d_point::kNy - rt2d_point::kSize);
        }
        // 0x004ab82c
        charge(ctx, 6);
        link(ctx, 0x4AB82Cu);  // $ra first: the delay slot below depends on it
        lw(a0, s1, rt2d_flat::kArray);
        call(ctx, gen::fn_sub_4C2090_004c2090);
        lw(a0, s1, rt2d_flat::kArray);
        a1 = s2;
        s0 = v0;
        jal(ctx, 0x4AB83Cu, gen::fn_sub_4C21B0_004c21b0);
} while (false);
// 0x004ab844: the closing point's and the first point's normals become their normalised average; closed (+8) = 1
    charge(ctx, 30);
    lwc1(f5, s0, rt2d_point::kNx);
    v1 = flt(1.0f);
    lwc1(f2, v0, rt2d_point::kNx);
    mtc1(v1, f0);
    lwc1(f3, s0, rt2d_point::kNy);
    lwc1(f1, v0, rt2d_point::kNy);
    v1 = 1;
    add_s(f4, f5, f2);
    add_s(f2, f3, f1);
    mula_s(f3, f2);
    madd_s(f1, f5, f4);
    div_s(f0, f0, f1);
    mul_s(f1, f4, f0);
    mul_s(f0, f2, f0);
    swc1(f1, v0, rt2d_point::kNx);
    swc1(f0, v0, rt2d_point::kNy);
    lwc1(f1, v0, rt2d_point::kNx);
    lwc1(f0, v0, rt2d_point::kNy);
    swc1(f1, s0, rt2d_point::kNx);
    v0 = s3;
    swc1(f0, s0, rt2d_point::kNy);
    sw(v1, s1, rt2d_flat::kClosed);
    ld(ra, sp, 0x50);
    lwc1(f20, sp, 0x0);
    lq(s3, sp, 0x40);
    lq(s2, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    sp = addiu(sp, 0x70);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4AB6A0(EEContext& ctx, u64 path) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(path));
    sub_4AB6A0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004ABD50 sub_4ABD50 -- 712 bytes; frame 0xC0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4ABD50 [Rt2dPathFlatten(dst, src)]: the tolerance (sub_4AA2C0) to 0x95EF60; every record of `src` (24 bytes;
// +4 count or -1) appended to `dst`: lines (type 1) with their normals, curves (type 2: the curve record and the next
// two) flattened by sub_4ABA20 with the budget 0x95EF68, other records copied; a closed source (+8) closes `dst`
// (sub_4AB6A0). Returns dst.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: callee frames ($sp off / deeper stack)).
void sub_4ABD50(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::backedge, hg::c_le_s, hg::call, hg::charge, hg::cond,
          hg::div_s, hg::enter, hg::jal, hg::ld, hg::link, hg::lq, hg::lw, hg::lwc1, hg::madd_s, hg::mov_s, hg::mtc1,
          hg::mul_s, hg::mula_s, hg::sd, hg::si, hg::slt, hg::slti, hg::sq, hg::sqrt_s, hg::sub_s, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5};
    // 0x004abd50
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
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
    link(ctx, 0x4ABD80u);  // $ra first: the delay slot below depends on it
    sq(s0, sp, 0x0);
    call(ctx, gen::fn_sub_4AA2C0_004aa2c0);
    lw(v1, s4, rt2d_flat::kCount);
    v0 = hi(kRt2dTolerance);
    swc1(f0, v0, lo(kRt2dTolerance));
    v0 = si(-1);
    if (v1 != v0) {
        // 0x004abdb0
        charge(ctx, 2);
        lw(v0, s4, rt2d_flat::kArray);
        lw(s1, s4, rt2d_flat::kCount);
    } else {
        // 0x004abda0
        charge(ctx, 4);
        link(ctx, 0x4ABDA0u);  // $ra first: the delay slot below depends on it
        lw(a0, s4, rt2d_flat::kArray);
        call(ctx, gen::fn_sub_4C2090_004c2090);
        lw(s1, s4, rt2d_flat::kCount);
    }
    // 0x004abdb8
    charge(ctx, 4);
    s3 = v0;
    v0 = si(-1);
    if (s1 == v0) {
        // 0x004abdc8
        charge(ctx, 3);
        link(ctx, 0x4ABDC8u);  // $ra first: the delay slot below depends on it
        lw(a0, s4, rt2d_flat::kArray);
        call(ctx, gen::fn_sub_4C2120_004c2120);
        s1 = v0;
    }
    // 0x004abdd4
    charge(ctx, 3);
    at = slt(0, s1);
    s2 = 0;
    if (at != 0) {
        // 0x004abde0
        charge(ctx, 3);
        s6 = addiu(sp, 0xA8);
        s7 = addiu(sp, 0xB0);
        fp = addiu(sp, 0xB8);
        for (;;) {
            // 0x004abdec
            charge(ctx, 4);
            lw(v1, s3, rt2d_point::kKind);
            v0 = 2;
            if (v1 == v0) {
                // 0x004abf78
                charge(ctx, 24);
                lwc1(f1, s3, -20);
                v0 = hi(kRt2dFlatWord);
                lwc1(f0, s3, -16);
                lw(a2, v0, lo(kRt2dFlatWord));
                a1 = addiu(sp, 0xA0);
                a0 = s5;
                swc1(f1, sp, 0xA0);
                swc1(f0, sp, 0xA4);
                lwc1(f1, s3, rt2d_point::kX);
                lwc1(f0, s3, rt2d_point::kY);
                swc1(f1, s6, 0);
                swc1(f0, s6, 4);
                lwc1(f1, s3, 28);
                lwc1(f0, s3, 32);
                swc1(f1, s7, 0);
                swc1(f0, s7, 4);
                lwc1(f1, s3, 52);
                lwc1(f0, s3, 56);
                swc1(f1, fp, 0x0);
                link(ctx, 0x4ABFC4u);  // $ra first: the delay slot below depends on it
                swc1(f0, fp, 0x4);
                call(ctx, gen::fn_sub_4ABA20_004aba20);
                s2 = addiu(s2, 2);
                s3 = addiu(s3, 48);
                backedge(ctx);
            } else {
                // 0x004abdfc
                charge(ctx, 3);
                v0 = 1;
                if (v1 != v0) {
                    // 0x004abf14
                    charge(ctx, 16);
                    lw(a0, s5, rt2d_flat::kArray);
                    v0 = 0x30000;
                    a1 = v0 | 0x1A1;
                    jal(ctx, 0x4ABF1Cu, gen::fn_sub_4C1E70_004c1e70);
                    lwc1(f3, s3, rt2d_point::kKind);
                    lwc1(f2, s3, rt2d_point::kX);
                    lwc1(f1, s3, rt2d_point::kY);
                    lwc1(f0, s3, 12);
                    swc1(f3, v0, 0);
                    swc1(f2, v0, 4);
                    swc1(f1, v0, 8);
                    swc1(f0, v0, 12);
                    lwc1(f1, s3, 16);
                    lwc1(f0, s3, 20);
                    swc1(f1, v0, 16);
                    swc1(f0, v0, 20);
                } else {
                    // 0x004abe08
                    charge(ctx, 28);
                    link(ctx, 0x4ABE08u);  // $ra first: the delay slot below depends on it
                    lw(a0, s5, rt2d_flat::kArray);
                    call(ctx, gen::fn_sub_4C2120_004c2120);
                    lw(a0, s5, rt2d_flat::kArray);
                    s0 = v0;
                    v0 = 0x30000;
                    a1 = v0 | 0x190;
                    jal(ctx, 0x4ABE1Cu, gen::fn_sub_4C1E70_004c1e70);
                    v1 = 1;
                    sw(v1, v0, 0);
                    mtc1(zero, f0);
                    lwc1(f1, s3, rt2d_point::kX);
                    swc1(f1, v0, 4);
                    lwc1(f1, s3, rt2d_point::kY);
                    swc1(f1, v0, 8);
                    lwc1(f2, v0, -20);
                    lwc1(f1, s3, rt2d_point::kX);
                    lwc1(f4, s3, rt2d_point::kY);
                    lwc1(f3, v0, -16);
                    sub_s(f2, f2, f1);
                    sub_s(f3, f4, f3);
                    mula_s(f2, f2);
                    madd_s(f1, f3, f3);
                    sqrt_s(f4, f1);
                    c_le_s(f4, f0);
                    if (cond(ctx)) {
                        // 0x004abe98
                        charge(ctx, 1);
                        mov_s(f0, f4);
                    } else {
                        // 0x004abe78
                        charge(ctx, 8);
                        v1 = flt(1.0f);
                        mtc1(v1, f0);
                        div_s(f0, f0, f4);
                    }
                    // 0x004abe9c
                    charge(ctx, 9);
                    mul_s(f1, f3, f0);
                    at = slti(s0, 2);
                    mul_s(f0, f2, f0);
                    swc1(f1, v0, 12);
                    swc1(f0, v0, 16);
                    lwc1(f0, v0, -4);
                    add_s(f0, f0, f4);
                    swc1(f0, v0, 20);
                    if (at != 0) {
                        // 0x004abf00
                        charge(ctx, 5);
                        lwc1(f1, v0, 12);
                        lwc1(f0, v0, 16);
                        swc1(f1, v0, -12);
                        swc1(f0, v0, -8);
                    } else {
                        // 0x004abec0
                        charge(ctx, 16);
                        lwc1(f5, v0, -12);
                        v1 = flt(1.0f);
                        lwc1(f2, v0, 12);
                        lwc1(f3, v0, -8);
                        lwc1(f1, v0, 16);
                        mtc1(v1, f0);
                        add_s(f4, f5, f2);
                        add_s(f2, f3, f1);
                        mula_s(f3, f2);
                        madd_s(f1, f5, f4);
                        div_s(f0, f0, f1);
                        mul_s(f1, f4, f0);
                        mul_s(f0, f2, f0);
                        swc1(f1, v0, -12);
                        swc1(f0, v0, -8);
                    }
                }
            }
            // 0x004abf54
            charge(ctx, 4);
            s2 = addiu(s2, 1);
            v0 = slt(s2, s1);
            s3 = addiu(s3, 24);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x004abf64
    charge(ctx, 3);
    lw(v0, s4, rt2d_flat::kClosed);
    if (v0 != 0) {
        // 0x004abfd8
        charge(ctx, 4);
        a0 = s5;
        jal(ctx, 0x4ABFD8u, gen::fn_sub_4AB6A0_004ab6a0);
        backedge(ctx);
    }
    // 0x004abf70
    charge(ctx, 2);
    v0 = s5;
    // 0x004abfe8
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
    sp = addiu(sp, 0xC0);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4ABD50(EEContext& ctx, u64 dst, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(dst));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(src));
    sub_4ABD50(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_4AAE60(EEContext& ctx) {
    c3::detail::Cpu(ctx).sub_4AAE60();
    return ee::core::gpr64(ctx, GPR_V0);
}
void sub_4AA2C0(EEContext& ctx) {
    c3::detail::Cpu(ctx).sub_4AA2C0();
}

// 0x004AD750 sub_4AD750 -- 496 bytes; frame 0xD0: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4AD750 [Rt2dObjectString render]: a visible string (+8 & 0x1000004 == 4): its 8-byte frame buffer cleared, the
// object's CTM pushed, the font's colour block (+180 font, its +0 .. +87) saved, mixed with the object's colour
// (+144 / +160) by sub_4A55B0, the string drawn through the font's callback (sub_4A9A70: +192 font object +4, text
// +176, size $f12 = +188), the CTM popped and the colour block restored. Returns the object.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4AD750(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::jal, hg::ld, hg::lq, hg::lw,
          hg::lwc1, hg::sb, hg::sd, hg::si, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x004ad750
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    v0 = 0x1000000;
    sd(ra, sp, 0x50);
    v1 = v0 | 0x4;  // &0x1000004
    sq(s4, sp, 0x40);
    v0 = 4;
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, rt2d_obj::kFlags);
    v1 = a0 & v1;
    if (v1 == v0) {
        // 0x004ad794
        charge(ctx, 3);
        v1 = addiu(sp, 0xC8);
        v0 = 8;
        if (v1 != 0) {
            for (;;) {
                // 0x004ad7a0
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
        // 0x004ad7bc
        charge(ctx, 5);
        lw(v1, s0, rt2d_obj::kFlags);
        v0 = 2;
        v1 = v1 & 0x2;
        if (v1 == v0) {
            // 0x004ad8d4
            charge(ctx, 6);
            a0 = addiu(s0, 16);
            jal(ctx, 0x4AD8D4u, gen::fn_sub_4AAB40_004aab40);
            jal(ctx, 0x4AD8DCu, gen::fn_sub_4AB0C0_004ab0c0);
            a2 = addiu(s0, rt2d_obj::kCtm);
            a1 = 8;
            for (;;) {
                // 0x004ad8ec
                charge(ctx, 8);
                lw(a0, v0, 0);
                a1 = addiu(a1, -1);
                lw(v1, v0, 4);
                sw(a0, a2, 0);
                v0 = addiu(v0, 8);
                sw(v1, a2, 4);
                a2 = addiu(a2, 8);
                if (i64(a1) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004ad90c
            charge(ctx, 5);
            lw(v1, s0, rt2d_obj::kFlags);
            v0 = si(-3);
            v0 = v1 & v0;
            sw(v0, s0, rt2d_obj::kFlags);
            backedge(ctx);
        } else {
            // 0x004ad7d0
            charge(ctx, 2);
            a0 = addiu(s0, rt2d_obj::kCtm);
            jal(ctx, 0x4AD7D0u, gen::fn_sub_4AAC70_004aac70);
        }
        // 0x004ad7d8
        charge(ctx, 63);
        a0 = addiu(sp, 0xB0);
        a1 = addiu(s0, rt2d_obj::kColourMul);
        a2 = 16;
        jal(ctx, 0x4AD7E0u, gen::fn_memcpy_00521250);
        a0 = addiu(sp, 0xA0);
        a1 = addiu(s0, rt2d_obj::kColourOffset);
        a2 = 16;
        jal(ctx, 0x4AD7F0u, gen::fn_memcpy_00521250);
        lw(s1, s0, rt2d_string::kFont);
        a0 = addiu(sp, 0x60);
        a2 = 16;
        a1 = addiu(s1, 48);
        jal(ctx, 0x4AD804u, gen::fn_memcpy_00521250);
        s2 = addiu(sp, 0x70);
        a1 = addiu(s1, 72);
        a0 = s2;
        a2 = 16;
        jal(ctx, 0x4AD818u, gen::fn_memcpy_00521250);
        s3 = addiu(sp, 0x80);
        a1 = addiu(s1, 24);
        a0 = s3;
        a2 = 16;
        jal(ctx, 0x4AD82Cu, gen::fn_memcpy_00521250);
        s4 = addiu(sp, 0x90);
        a1 = s1;
        a0 = s4;
        a2 = 16;
        jal(ctx, 0x4AD840u, gen::fn_memcpy_00521250);
        a0 = s1;
        a1 = addiu(sp, 0x60);
        a2 = s2;
        a3 = s3;
        t0 = s4;
        t1 = addiu(sp, 0xB0);
        t2 = addiu(sp, 0xA0);
        jal(ctx, 0x4AD860u, gen::fn_sub_4A55B0_004a55b0);
        lw(v0, s0, rt2d_string::kFontObject);
        lwc1(f12, s0, rt2d_string::kSize);
        lw(a1, s0, rt2d_string::kText);
        a2 = addiu(sp, 0xC8);
        lw(a0, v0, 4);
        a3 = s1;
        jal(ctx, 0x4AD87Cu, gen::fn_sub_4A9A70_004a9a70);
        jal(ctx, 0x4AD884u, gen::fn_sub_4AAD50_004aad50);
        a0 = addiu(s1, 48);
        a1 = addiu(sp, 0x60);
        a2 = 16;
        jal(ctx, 0x4AD894u, gen::fn_memcpy_00521250);
        a1 = s2;
        a0 = addiu(s1, 72);
        a2 = 16;
        jal(ctx, 0x4AD8A4u, gen::fn_memcpy_00521250);
        a1 = s3;
        a0 = addiu(s1, 24);
        a2 = 16;
        jal(ctx, 0x4AD8B4u, gen::fn_memcpy_00521250);
        a0 = s1;
        a1 = s4;
        a2 = 16;
        jal(ctx, 0x4AD8C4u, gen::fn_memcpy_00521250);
        backedge(ctx);
    }
    // 0x004ad78c
    charge(ctx, 2);
    v0 = s0;
    // 0x004ad920
    charge(ctx, 8);
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xD0);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4AD750(EEContext& ctx, u64 string) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(string));
    sub_4AD750(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004AE2F0 sub_4AE2F0 -- 180 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4AE2F0 [Rt2dPickRegion update]: a visible region (+8 bit 2): a dirty local matrix is pushed and read back into
// +80 with its inverse at +208 (sub_4C32A0), otherwise +80 is pushed; then popped. Returns the region.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4AE2F0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::si, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004ae2f0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 4;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, rt2d_obj::kFlags);
    v1 = a0 & 0x4;
    if (v1 == v0) {
        // 0x004ae314
        charge(ctx, 4);
        v1 = a0 & 0x2;
        v0 = 2;
        if (v1 == v0) {
            // 0x004ae33c
            charge(ctx, 6);
            a0 = addiu(s0, rt2d_obj::kMatrix);
            jal(ctx, 0x4AE33Cu, gen::fn_sub_4AAB40_004aab40);
            jal(ctx, 0x4AE344u, gen::fn_sub_4AB0C0_004ab0c0);
            a2 = addiu(s0, rt2d_obj::kCtm);
            a1 = 8;
            for (;;) {
                // 0x004ae354
                charge(ctx, 8);
                lw(a0, v0, 0);
                a1 = addiu(a1, -1);
                lw(v1, v0, 4);
                sw(a0, a2, 0);
                v0 = addiu(v0, 8);
                sw(v1, a2, 4);
                a2 = addiu(a2, 8);
                if (i64(a1) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004ae374
            charge(ctx, 8);
            a0 = addiu(s0, rt2d_region::kInverse);
            a1 = addiu(s0, rt2d_obj::kCtm);
            jal(ctx, 0x4AE378u, gen::fn_sub_4C32A0_004c32a0);
            lw(v1, s0, rt2d_obj::kFlags);
            v0 = si(-3);
            v0 = v1 & v0;
            sw(v0, s0, rt2d_obj::kFlags);
            backedge(ctx);
        } else {
            // 0x004ae324
            charge(ctx, 2);
            a0 = addiu(s0, rt2d_obj::kCtm);
            jal(ctx, 0x4AE324u, gen::fn_sub_4AAC70_004aac70);
        }
        // 0x004ae32c
        charge(ctx, 2);
        jal(ctx, 0x4AE32Cu, gen::fn_sub_4AAD50_004aad50);
    }
    // 0x004ae334
    charge(ctx, 2);
    v0 = s0;
    // 0x004ae394
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4AE2F0(EEContext& ctx, u64 region) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(region));
    sub_4AE2F0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_4A6600(EEContext& ctx, u64 path, u64 brush) {
    ee::core::set_gpr64(ctx, GPR_A0, path);
    ee::core::set_gpr64(ctx, GPR_A1, brush);
    c3::detail::Cpu(ctx).sub_4A6600();
    return ee::core::gpr64(ctx, GPR_V0);
}
void sub_4ACE70(EEContext& ctx, u64 path, u64 brush) {
    ee::core::set_gpr64(ctx, GPR_A0, path);
    ee::core::set_gpr64(ctx, GPR_A1, brush);
    c3::detail::Cpu(ctx).sub_4ACE70();
}

// 0x004AF9D0 sub_4AF9D0 -- 1540 bytes; frame 0xF0: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4AF9D0 [Rt2dShape render(shape, multiply, offset)]: a visible shape (+8 bit 2). The combined colour multiplier
// (shape +144.. * $a1, frame sp + 208) and offset (shape +160.. * $a1 + 255 * $a2, sp + 192).
//   * A shape built on an atomic (+184): each of its material colours (the atomic's geometry +8 -> +36 count, +32 the
//     materials) = clamp(offset + multiplier * the shape's colour bytes (+180, 4 per material), 0, 255) as RGBA bytes
//     (assembled at sp + 236 .. 239, then stored into material +4 .. +7); +8 bit 3 cleared; the CTM pushed; the
//     atomic's frame transform set from the Rt2d device matrix (sub_4AAE60 -> sub_4CB7F0(frame, matrix, 0)) and the
//     atomic rendered through its callback (+72).
//   * Otherwise each node of the shape's path list (+176: 12-byte {flags, path, brush} records): the brush's colour
//     block saved, mixed (sub_4A55B0), the path stroked (flags bit 0: sub_4A6600) or filled (sub_4ACE70), the colour
//     block restored.
// The CTM popped; returns the shape.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: frame/spills (own frame)).
void sub_4AF9D0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::adda_s, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge,
          hg::cvt_s_w, hg::cvt_w_s, hg::enter, hg::i64, hg::jal, hg::jalr, hg::lbu, hg::ld, hg::link, hg::lq, hg::lw,
          hg::lwc1, hg::madd_s, hg::mfc1, hg::mtc1, hg::mul_s, hg::mula_s, hg::sb, hg::sd, hg::si, hg::sll, hg::slt,
          hg::slti, hg::sltu, hg::sq, hg::srl, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9};
    // 0x004af9d0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0xF0);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v0, a0, rt2d_obj::kFlags);
    v0 = v0 & 0x4;
    s5 = a0;
    if (v0 != 0) {
        // 0x004afa04: visible: the combined colour multiplier (sp+0xD0) and offset (sp+0xC0)
        charge(ctx, 47);
        lwc1(f0, s5, rt2d_obj::kColourMul);
        v0 = 0x437F0000;
        lwc1(f9, a1, 0);
        t6 = addiu(sp, 0xD4);
        lwc1(f8, a1, 4);
        t5 = addiu(sp, 0xD8);
        lwc1(f7, a1, 8);
        t4 = addiu(sp, 0xDC);
        lwc1(f6, a1, 12);
        t3 = addiu(sp, 0xC4);
        lwc1(f4, a2, 0);
        t2 = addiu(sp, 0xC8);
        mtc1(v0, f5);
        t1 = addiu(sp, 0xCC);
        mul_s(f0, f0, f9);
        swc1(f0, sp, 0xD0);
        lwc1(f0, s5, rt2d_obj::kColourMul + 4);
        lwc1(f3, a2, 4);
        lwc1(f2, a2, 8);
        lwc1(f1, a2, 12);
        mul_s(f0, f0, f8);
        swc1(f0, t6, 0);
        lwc1(f0, s5, rt2d_obj::kColourMul + 8);
        mul_s(f0, f0, f7);
        swc1(f0, t5, 0);
        lwc1(f0, s5, rt2d_obj::kColourMul + 12);
        mul_s(f0, f0, f6);
        swc1(f0, t4, 0);
        lwc1(f0, s5, rt2d_obj::kColourOffset);
        mula_s(f0, f9);
        madd_s(f0, f5, f4);
        swc1(f0, sp, 0xC0);
        lwc1(f0, s5, rt2d_obj::kColourOffset + 4);
        mula_s(f0, f8);
        madd_s(f0, f5, f3);
        swc1(f0, t3, 0);
        lwc1(f0, s5, rt2d_obj::kColourOffset + 8);
        mula_s(f0, f7);
        madd_s(f0, f5, f2);
        swc1(f0, t2, 0);
        lwc1(f0, s5, rt2d_obj::kColourOffset + 12);
        mula_s(f0, f6);
        madd_s(f0, f5, f1);
        swc1(f0, t1, 0);
        lw(v0, s5, rt2d_shape::kAtomic);
        if (v0 == 0) {
            // 0x004afdcc: paths: push the CTM (dirty: matrix x CTM, read back)
            charge(ctx, 5);
            lw(v1, s5, rt2d_obj::kFlags);
            v0 = 2;
            v1 = v1 & 0x2;
            if (v1 == v0) {
                // 0x004aff14
                charge(ctx, 6);
                a0 = addiu(s5, rt2d_obj::kMatrix);
                jal(ctx, 0x4AFF14u, gen::fn_sub_4AAB40_004aab40);
                jal(ctx, 0x4AFF1Cu, gen::fn_sub_4AB0C0_004ab0c0);
                a2 = addiu(s5, rt2d_obj::kCtm);
                a1 = 8;
                for (;;) {
                    // 0x004aff2c
                    charge(ctx, 8);
                    lw(a0, v0, 0);
                    a1 = addiu(a1, -1);
                    lw(v1, v0, 4);
                    sw(a0, a2, 0);
                    v0 = addiu(v0, 8);
                    sw(v1, a2, 4);
                    a2 = addiu(a2, 8);
                    if (i64(a1) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004aff4c
                charge(ctx, 5);
                lw(v1, s5, rt2d_obj::kFlags);
                v0 = si(-3);
                v0 = v1 & v0;
                sw(v0, s5, rt2d_obj::kFlags);
                backedge(ctx);
            } else {
                // 0x004afde0
                charge(ctx, 2);
                a0 = addiu(s5, rt2d_obj::kCtm);
                jal(ctx, 0x4AFDE0u, gen::fn_sub_4AAC70_004aac70);
            }
            // 0x004afde8: s4 .. s6 = the path nodes (12 bytes each)
            charge(ctx, 13);
            lw(v0, s5, rt2d_shape::kPaths);
            link(ctx, 0x4AFDECu);  // $ra first: the delay slot below depends on it
            lw(a0, v0, 0);
            call(ctx, gen::fn_sub_4C2090_004c2090);
            s4 = v0;
            lw(v0, s5, rt2d_shape::kPaths);
            link(ctx, 0x4AFDFCu);  // $ra first: the delay slot below depends on it
            lw(a0, v0, 0);
            call(ctx, gen::fn_sub_4C2120_004c2120);
            v1 = sll(v0, 1);
            v0 = addu(v1, v0);
            v0 = sll(v0, 2);
            s6 = addu(s4, v0);
            if (s4 == s6) {
                backedge(ctx);
            } else {
                // 0x004afe1c: each node: the brush's colour block saved, mixed (sub_4A55B0), the path stroked (bit 0,
                // sub_4A6600)
                // or filled (sub_4ACE70), the colour block restored
                charge(ctx, 3);
                s2 = addiu(sp, 0x90);
                s1 = addiu(sp, 0xA0);
                s0 = addiu(sp, 0xB0);
                for (;;) {
                    // 0x004afe28
                    charge(ctx, 29);
                    lw(s3, s4, rt2d_pathnode::kBrush);
                    a0 = addiu(sp, 0x80);
                    a2 = 16;
                    a1 = addiu(s3, 48);
                    jal(ctx, 0x4AFE34u, gen::fn_memcpy_00521250);
                    a0 = s2;
                    a1 = addiu(s3, 72);
                    a2 = 16;
                    jal(ctx, 0x4AFE44u, gen::fn_memcpy_00521250);
                    a0 = s1;
                    a1 = addiu(s3, 24);
                    a2 = 16;
                    jal(ctx, 0x4AFE54u, gen::fn_memcpy_00521250);
                    a0 = s0;
                    a1 = s3;
                    a2 = 16;
                    jal(ctx, 0x4AFE64u, gen::fn_memcpy_00521250);
                    a0 = s3;
                    a1 = addiu(sp, 0x80);
                    a2 = s2;
                    a3 = s1;
                    t0 = s0;
                    t1 = addiu(sp, 0xD0);
                    t2 = addiu(sp, 0xC0);
                    jal(ctx, 0x4AFE84u, gen::fn_sub_4A55B0_004a55b0);
                    lw(v0, s4, rt2d_pathnode::kFlags);
                    v0 = v0 & 0x1;
                    if (v0 == 0) {
                        // 0x004afeb0
                        charge(ctx, 4);
                        lw(a0, s4, rt2d_pathnode::kPath);
                        a1 = s3;
                        jal(ctx, 0x4AFEB4u, gen::fn_sub_4ACE70_004ace70);
                    } else {
                        // 0x004afe9c
                        charge(ctx, 5);
                        lw(a0, s4, rt2d_pathnode::kPath);
                        a1 = s3;
                        jal(ctx, 0x4AFEA0u, gen::fn_sub_4A6600_004a6600);
                    }
                    // 0x004afec0
                    charge(ctx, 19);
                    a0 = addiu(s3, 48);
                    a1 = addiu(sp, 0x80);
                    a2 = 16;
                    jal(ctx, 0x4AFEC8u, gen::fn_memcpy_00521250);
                    a0 = addiu(s3, 72);
                    a1 = s2;
                    a2 = 16;
                    jal(ctx, 0x4AFED8u, gen::fn_memcpy_00521250);
                    a0 = addiu(s3, 24);
                    a1 = s1;
                    a2 = 16;
                    jal(ctx, 0x4AFEE8u, gen::fn_memcpy_00521250);
                    a0 = s3;
                    a1 = s0;
                    a2 = 16;
                    jal(ctx, 0x4AFEF8u, gen::fn_memcpy_00521250);
                    s4 = addiu(s4, 12);
                    if (s4 == s6) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004aff0c
                charge(ctx, 2);
                backedge(ctx);
            }
        } else {
            // 0x004afac0: built on an atomic: each material's colour = clamp(offset + multiplier * the shape's colour
            // bytes, 0, 255); the word at +176 is read as the material holder here: +8 -> {+32 materials, +36 count}
            charge(ctx, 6);
            lw(v0, s5, 176);
            lw(t0, v0, 8);
            lw(a3, t0, 36);
            at = sltu(0, a3);
            s2 = 0;
            if (at != 0) {
                // 0x004afad8
                charge(ctx, 6);
                mtc1(zero, f3);
                t7 = 0;
                a2 = addiu(sp, 0xED);
                a1 = addiu(sp, 0xEE);
                a0 = addiu(sp, 0xEF);
                v0 = 255;
                for (;;) {
                    // 0x004afaf0
                    charge(ctx, 5);
                    lw(v1, s5, rt2d_shape::kColourBytes);
                    v1 = addu(v1, t7);
                    lbu(s0, v1, 0);
                    lwc1(f2, sp, 0xD0);
                    if (i64(s0) < 0) {
                        // 0x004afb10
                        charge(ctx, 7);
                        s1 = srl(s0, 1);
                        s0 = s0 & 0x1;
                        s1 = s1 | s0;
                        mtc1(s1, f0);
                        cvt_s_w(f1, f0);
                        add_s(f1, f1, f1);
                    } else {
                        // 0x004afb04
                        charge(ctx, 3);
                        mtc1(s0, f0);
                        cvt_s_w(f1, f0);
                    }
                    // 0x004afb2c
                    charge(ctx, 8);
                    lwc1(f0, sp, 0xC0);
                    lbu(s0, v1, 1);
                    adda_s(f3, f0);
                    madd_s(f0, f2, f1);
                    cvt_w_s(f0, f0);
                    mfc1(s1, f0);
                    if (i64(s0) < 0) {
                        // 0x004afb58
                        charge(ctx, 7);
                        s3 = srl(s0, 1);
                        s0 = s0 & 0x1;
                        s3 = s3 | s0;
                        mtc1(s3, f0);
                        cvt_s_w(f2, f0);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x004afb4c
                        charge(ctx, 3);
                        mtc1(s0, f0);
                        cvt_s_w(f2, f0);
                    }
                    // 0x004afb74
                    charge(ctx, 9);
                    lwc1(f0, t3, 0);
                    lbu(s3, v1, 2);
                    lwc1(f1, t6, 0);
                    adda_s(f3, f0);
                    madd_s(f0, f1, f2);
                    cvt_w_s(f0, f0);
                    mfc1(s0, f0);
                    if (i64(s3) < 0) {
                        // 0x004afba4
                        charge(ctx, 7);
                        s4 = srl(s3, 1);
                        s3 = s3 & 0x1;
                        s4 = s4 | s3;
                        mtc1(s4, f0);
                        cvt_s_w(f2, f0);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x004afb98
                        charge(ctx, 3);
                        mtc1(s3, f0);
                        cvt_s_w(f2, f0);
                    }
                    // 0x004afbc0
                    charge(ctx, 9);
                    lwc1(f0, t2, 0);
                    lbu(s3, v1, 3);
                    lwc1(f1, t5, 0);
                    adda_s(f3, f0);
                    madd_s(f0, f1, f2);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    if (i64(s3) < 0) {
                        // 0x004afbf0
                        charge(ctx, 7);
                        s4 = srl(s3, 1);
                        s3 = s3 & 0x1;
                        s4 = s4 | s3;
                        mtc1(s4, f0);
                        cvt_s_w(f2, f0);
                        add_s(f2, f2, f2);
                    } else {
                        // 0x004afbe4
                        charge(ctx, 3);
                        mtc1(s3, f0);
                        cvt_s_w(f2, f0);
                    }
                    // 0x004afc0c
                    charge(ctx, 9);
                    lwc1(f0, t1, 0);
                    at = slti(s1, 256);
                    lwc1(f1, t4, 0);
                    adda_s(f3, f0);
                    madd_s(f0, f1, f2);
                    cvt_w_s(f0, f0);
                    mfc1(s4, f0);
                    if (at != 0) {
                        // 0x004afc38
                        charge(ctx, 1);
                        s3 = s1;
                    } else {
                        // 0x004afc30
                        charge(ctx, 2);
                        s3 = v0;
                    }
                    // 0x004afc3c
                    charge(ctx, 3);
                    at = slt(0, s3);
                    if (at == 0) {
                        // 0x004afc60
                        charge(ctx, 2);
                        s1 = 0;
                        at = slti(s0, 256);
                    } else {
                        // 0x004afc48
                        charge(ctx, 3);
                        at = slti(s1, 256);
                        if (at == 0) {
                            // 0x004afc54
                            charge(ctx, 1);
                            s1 = v0;
                        }
                        // 0x004afc58
                        charge(ctx, 2);
                        at = slti(s0, 256);
                    }
                    // 0x004afc68
                    charge(ctx, 2);
                    sb(s1, sp, 0xEC);
                    if (at != 0) {
                        // 0x004afc78
                        charge(ctx, 1);
                        s1 = s0;
                    } else {
                        // 0x004afc70
                        charge(ctx, 2);
                        s1 = v0;
                    }
                    // 0x004afc7c
                    charge(ctx, 3);
                    at = slt(0, s1);
                    if (at == 0) {
                        // 0x004afca0
                        charge(ctx, 2);
                        s0 = 0;
                        at = slti(v1, 256);
                    } else {
                        // 0x004afc88
                        charge(ctx, 3);
                        at = slti(s0, 256);
                        if (at == 0) {
                            // 0x004afc94
                            charge(ctx, 1);
                            s0 = v0;
                        }
                        // 0x004afc98
                        charge(ctx, 2);
                        at = slti(v1, 256);
                    }
                    // 0x004afca8
                    charge(ctx, 2);
                    sb(s0, a2, 0);
                    if (at != 0) {
                        // 0x004afcb8
                        charge(ctx, 1);
                        s0 = v1;
                    } else {
                        // 0x004afcb0
                        charge(ctx, 2);
                        s0 = v0;
                    }
                    // 0x004afcbc
                    charge(ctx, 3);
                    at = slt(0, s0);
                    if (at == 0) {
                        // 0x004afce0
                        charge(ctx, 2);
                        v1 = 0;
                        at = slti(s4, 256);
                    } else {
                        // 0x004afcc8
                        charge(ctx, 3);
                        at = slti(v1, 256);
                        if (at == 0) {
                            // 0x004afcd4
                            charge(ctx, 1);
                            v1 = v0;
                        }
                        // 0x004afcd8
                        charge(ctx, 2);
                        at = slti(s4, 256);
                    }
                    // 0x004afce8
                    charge(ctx, 2);
                    sb(v1, a1, 0);
                    if (at != 0) {
                        // 0x004afcf8
                        charge(ctx, 1);
                        v1 = s4;
                    } else {
                        // 0x004afcf0
                        charge(ctx, 2);
                        v1 = v0;
                    }
                    // 0x004afcfc
                    charge(ctx, 3);
                    at = slt(0, v1);
                    if (at == 0) {
                        // 0x004afd20
                        charge(ctx, 2);
                        s4 = 0;
                        lw(s6, t0, 32);
                    } else {
                        // 0x004afd08
                        charge(ctx, 3);
                        at = slti(s4, 256);
                        if (at == 0) {
                            // 0x004afd14
                            charge(ctx, 1);
                            s4 = v0;
                        }
                        // 0x004afd18
                        charge(ctx, 2);
                        lw(s6, t0, 32);
                    }
                    // 0x004afd28
                    charge(ctx, 15);
                    s2 = addiu(s2, 1);
                    sb(s4, a0, 0);
                    v1 = sltu(s2, a3);
                    lbu(s4, sp, 0xEC);
                    lbu(s3, sp, 0xED);
                    lbu(s1, sp, 0xEE);
                    lbu(s0, sp, 0xEF);
                    s6 = addu(s6, t7);
                    lw(s6, s6, 0);
                    t7 = addiu(t7, 4);
                    sb(s4, s6, 4);
                    sb(s3, s6, 5);
                    sb(s1, s6, 6);
                    sb(s0, s6, 7);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x004afd64: +8 bit 3 cleared; push the CTM (dirty: matrix x CTM, read back)
            charge(ctx, 9);
            lw(a0, s5, rt2d_obj::kFlags);
            v1 = si(-9);
            v0 = 2;
            v1 = a0 & v1;
            sw(v1, s5, rt2d_obj::kFlags);
            lw(v1, s5, rt2d_obj::kFlags);
            v1 = v1 & 0x2;
            if (v1 == v0) {
                // 0x004aff60
                charge(ctx, 6);
                a0 = addiu(s5, rt2d_obj::kMatrix);
                jal(ctx, 0x4AFF60u, gen::fn_sub_4AAB40_004aab40);
                jal(ctx, 0x4AFF68u, gen::fn_sub_4AB0C0_004ab0c0);
                a2 = addiu(s5, rt2d_obj::kCtm);
                a1 = 8;
                for (;;) {
                    // 0x004aff78
                    charge(ctx, 8);
                    lw(a0, v0, 0);
                    a1 = addiu(a1, -1);
                    lw(v1, v0, 4);
                    sw(a0, a2, 0);
                    v0 = addiu(v0, 8);
                    sw(v1, a2, 4);
                    a2 = addiu(a2, 8);
                    if (i64(a1) <= 0) {
                        break;
                    }
                    backedge(ctx);
                }
                // 0x004aff98
                charge(ctx, 5);
                lw(v1, s5, rt2d_obj::kFlags);
                v0 = si(-3);
                v0 = v1 & v0;
                sw(v0, s5, rt2d_obj::kFlags);
                backedge(ctx);
            } else {
                // 0x004afd88
                charge(ctx, 2);
                a0 = addiu(s5, rt2d_obj::kCtm);
                jal(ctx, 0x4AFD88u, gen::fn_sub_4AAC70_004aac70);
            }
            // 0x004afd90: the atomic's frame from the Rt2d device matrix (sub_4CB7F0(frame, matrix, 0)); its render
            // callback
            charge(ctx, 11);
            jal(ctx, 0x4AFD90u, gen::fn_sub_4AAE60_004aae60);
            a1 = v0;
            lw(v0, s5, rt2d_shape::kAtomic);
            lw(a0, v0, rw_atomic::kFrame);
            a2 = 0;
            jal(ctx, 0x4AFDA4u, gen::fn_sub_4CB7F0_004cb7f0);
            lw(a0, s5, rt2d_shape::kAtomic);
            lw(v0, a0, rw_atomic::kRenderCb);
            jalr(ctx, 0x4AFDB4u, v0.u());
        }
        // 0x004afdbc: pop the CTM
        charge(ctx, 2);
        jal(ctx, 0x4AFDBCu, gen::fn_sub_4AAD50_004aad50);
    }
    // 0x004afdc4: return the shape
    charge(ctx, 2);
    v0 = s5;
    // 0x004affac
    charge(ctx, 10);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xF0);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4AF9D0(EEContext& ctx, u64 shape, u64 multiply, u64 offset) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(shape));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(multiply));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(offset));
    sub_4AF9D0(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004ADF30 sub_4ADF30 -- 156 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4ADF30 [Rt2dObject render]: by the object's type (+0): 4 string (sub_4AD750), 3 pick region (sub_4AE2F0),
// 2 shape (sub_4AF9D0), 1 scene (sub_4AE960 with the colour multiplier / offset $a1 / $a2), 0 nothing; another type
// returns 0, else the object.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4ADF30(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004adf30
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = 4;
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(v1, a0, rt2d_obj::kType);
    s0 = a0;  // s0 = the object
    if (v1 == v0) {
        // 0x004adfb0: 4 a string
        charge(ctx, 2);
        jal(ctx, 0x4ADFB0u, gen::fn_sub_4AD750_004ad750);
        // 0x004adfb8: return the object
        charge(ctx, 1);
        v0 = s0;
    } else {
        // 0x004adf4c
        charge(ctx, 3);
        v0 = 3;
        if (v1 == v0) {
            // 0x004adfa0: 3 a pick region
            charge(ctx, 4);
            jal(ctx, 0x4ADFA0u, gen::fn_sub_4AE2F0_004ae2f0);
            // 0x004adfb8 (written out on this path)
            charge(ctx, 1);
            v0 = s0;
        } else {
            // 0x004adf58
            charge(ctx, 3);
            v0 = 2;
            if (v1 == v0) {
                // 0x004adf90: 2 a shape
                charge(ctx, 4);
                jal(ctx, 0x4ADF90u, gen::fn_sub_4AF9D0_004af9d0);
                // 0x004adfb8 (written out on this path)
                charge(ctx, 1);
                v0 = s0;
            } else {
                // 0x004adf64
                charge(ctx, 3);
                v0 = 1;
                if (v1 != v0) {
                    // 0x004adf70: 0 nothing; another type: 0
                    charge(ctx, 2);
                    if (v1 != 0) {
                        // 0x004adf78
                        charge(ctx, 2);
                        s0 = 0;
                    }
                    // 0x004adfb8 (written out on this path)
                    charge(ctx, 1);
                    v0 = s0;
                } else {
                    // 0x004adf80: 1 a scene, with the colours
                    charge(ctx, 4);
                    jal(ctx, 0x4ADF80u, gen::fn_sub_4AE960_004ae960);
                    v0 = s0;
                }
            }
        }
    }
    // 0x004adfbc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4ADF30(EEContext& ctx, u64 object, u64 multiply, u64 offset) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(object));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(multiply));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(offset));
    sub_4ADF30(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x004AE960 sub_4AE960 -- 500 bytes; frame 0x70: ra sp+0x40, s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// sub_4AE960 [Rt2dSceneRender(scene, multiply, offset)]: a visible scene (+8 bit 2): the CTM pushed (dirty: matrix x
// CTM read back, every child marked dirty), the colour multiplier (scene +144.. * $a1) and offset (scene +160.. / 255 *
// multiplier + $a2) into the frame (sp + 96 / sp + 80); children re-sorted when +188 (sub_4AE690); each child
// rendered (sub_4ADF30) with the combined colours; the CTM popped. Returns the scene.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4AE960(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::addiu, hg::addu, hg::backedge, hg::call, hg::charge, hg::div_s,
          hg::enter, hg::i64, hg::jal, hg::ld, hg::link, hg::lq, hg::lw, hg::lwc1, hg::madd_s, hg::mtc1, hg::mul_s,
          hg::sd, hg::si, hg::sll, hg::sq, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6}, f7{ctx, 7}, f8{ctx, 8}, f9{ctx, 9};
    // 0x004ae960
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    v0 = 4;
    sd(ra, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    s3 = a0;  // s3 = the scene
    sq(s1, sp, 0x10);
    s2 = 0;  // s2 = the children are to be marked dirty
    sq(s0, sp, 0x0);
    s1 = a1;  // s1 = the colour multiplier
    lw(a0, a0, rt2d_obj::kFlags);
    v1 = a0 & 0x4;  // visible?
    s0 = a2;  // s0 = the colour offset
    if (v1 == v0) {
        // 0x004ae998: the matrix changed?
        charge(ctx, 4);
        v1 = a0 & 0x2;
        v0 = 2;
        if (v1 == v0) {
            // 0x004aeac0: push matrix x CTM (sub_4AAB40), read the CTM back into the scene's +80 copy; clear the flag
            charge(ctx, 6);
            a0 = addiu(s3, rt2d_obj::kMatrix);
            jal(ctx, 0x4AEAC0u, gen::fn_sub_4AAB40_004aab40);
            jal(ctx, 0x4AEAC8u, gen::fn_sub_4AB0C0_004ab0c0);
            a2 = addiu(s3, rt2d_obj::kCtm);
            a1 = 8;
            for (;;) {
                // 0x004aead8
                charge(ctx, 8);
                lw(a0, v0, 0);
                a1 = addiu(a1, -1);
                lw(v1, v0, 4);
                sw(a0, a2, 0);
                v0 = addiu(v0, 8);
                sw(v1, a2, 4);
                a2 = addiu(a2, 8);
                if (i64(a1) <= 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004aeaf8
            charge(ctx, 6);
            lw(v1, s3, rt2d_obj::kFlags);
            v0 = si(-3);
            s2 = 1;
            v0 = v1 & v0;
            sw(v0, s3, rt2d_obj::kFlags);
            backedge(ctx);
        } else {
            // 0x004ae9a8: unchanged: push the scene's CTM copy (sub_4AAC70)
            charge(ctx, 2);
            a0 = addiu(s3, rt2d_obj::kCtm);
            jal(ctx, 0x4AE9A8u, gen::fn_sub_4AAC70_004aac70);
        }
        // 0x004ae9b0: the combined colours into the frame: multiplier (sp+0x60) = scene's * $a1, offset (sp+0x50) =
        // scene's / 255 * $a1 + $a2; then the children
        charge(ctx, 51);
        lwc1(f1, s3, rt2d_obj::kColourMul);
        v0 = flt(255.0f);
        lwc1(f9, s1, 0);
        lwc1(f8, s1, 4);
        lwc1(f7, s1, 8);
        lwc1(f6, s1, 12);
        mtc1(v0, f5);
        lwc1(f0, s0, 0);
        mul_s(f1, f1, f9);
        swc1(f1, sp, 0x60);
        lwc1(f4, s3, rt2d_obj::kColourMul + 4);
        mtc1(zero, f3);
        lwc1(f2, s0, 4);
        adda_s(f3, f0);
        lwc1(f1, s0, 8);
        lwc1(f0, s0, 12);
        mul_s(f4, f4, f8);
        swc1(f4, sp, 0x64);
        lwc1(f4, s3, rt2d_obj::kColourMul + 8);
        mul_s(f4, f4, f7);
        swc1(f4, sp, 0x68);
        lwc1(f4, s3, rt2d_obj::kColourMul + 12);
        mul_s(f4, f4, f6);
        swc1(f4, sp, 0x6C);
        lwc1(f4, s3, rt2d_obj::kColourOffset);
        div_s(f4, f4, f5);
        madd_s(f4, f4, f9);
        swc1(f4, sp, 0x50);
        adda_s(f3, f2);
        lwc1(f2, s3, rt2d_obj::kColourOffset + 4);
        div_s(f2, f2, f5);
        madd_s(f2, f2, f8);
        swc1(f2, sp, 0x54);
        adda_s(f3, f1);
        lwc1(f1, s3, rt2d_obj::kColourOffset + 8);
        div_s(f1, f1, f5);
        madd_s(f1, f1, f7);
        adda_s(f3, f0);
        swc1(f1, sp, 0x58);
        lwc1(f0, s3, rt2d_obj::kColourOffset + 12);
        div_s(f0, f0, f5);
        madd_s(f0, f0, f6);
        swc1(f0, sp, 0x5C);
        link(ctx, 0x4AEA5Cu);  // $ra first: the delay slot below depends on it
        lw(a0, s3, rt2d_scene::kChildren);
        call(ctx, gen::fn_sub_4C2090_004c2090);
        s1 = v0;
        lw(v1, s3, rt2d_scene::kChildCount);
        lw(v0, s3, rt2d_scene::kResort);
        v1 = sll(v1, 3);
        s0 = addu(s1, v1);
        if (v0 != 0) {
            // 0x004aeb10
            charge(ctx, 4);
            a0 = s3;
            jal(ctx, 0x4AEB10u, gen::fn_sub_4AE690_004ae690);
            sw(zero, s3, rt2d_scene::kResort);
            backedge(ctx);
        }
        // 0x004aea7c
        charge(ctx, 2);
        if (s1 != s0) {
            for (;;) {
                // 0x004aea84
                charge(ctx, 2);
                if (s2 != 0) {
                    // 0x004aeb20
                    charge(ctx, 5);
                    lw(v1, s1, 0);
                    lw(v0, v1, 8);
                    v0 = v0 | 0x2;
                    sw(v0, v1, 8);
                    backedge(ctx);
                } else {
                    // 0x004aea8c
                    charge(ctx, 1);
                }
                // 0x004aea90
                charge(ctx, 7);
                lw(a0, s1, 0);
                a1 = addiu(sp, 0x60);
                a2 = addiu(sp, 0x50);
                jal(ctx, 0x4AEA98u, gen::fn_sub_4ADF30_004adf30);
                s1 = addiu(s1, 8);
                if (s1 == s0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x004aeaac
            charge(ctx, 1);
        }
        // 0x004aeab0
        charge(ctx, 2);
        jal(ctx, 0x4AEAB0u, gen::fn_sub_4AAD50_004aad50);
    }
    // 0x004aeab8
    charge(ctx, 2);
    v0 = s3;
    // 0x004aeb38
    charge(ctx, 7);
    ld(ra, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x70);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4AE960(EEContext& ctx, u64 scene, u64 multiply, u64 offset) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(scene));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(multiply));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(offset));
    sub_4AE960(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}
u64 sub_4AE940(EEContext& ctx, u64 scene) {
    ee::core::set_gpr64(ctx, GPR_A0, scene);
    c3::detail::Cpu(ctx).sub_4AE940();
    return ee::core::gpr64(ctx, GPR_V0);
}

// 0x004B5330 sub_4B5330 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// sub_4B5330 [a Maestro's scene render]: the scene at +36 rendered (sub_4AE940) when present; returns the object, or 0
// when the render failed.
// Register-faithful (p3fes_handgen body; audit 2026-10-21: faults only (differs only on runs that stop)).
void sub_4B5330(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004b5330
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;  // s0 = the Maestro
    lw(a0, a0, rt2d_maestro::kScene);
    if (a0 != 0) {
        // 0x004b534c: sub_4AE940(scene)
        charge(ctx, 4);
        jal(ctx, 0x4B534Cu, gen::fn_sub_4AE940_004ae940);
        if (v0 == 0) {
            // 0x004b535c: the render failed: 0
            charge(ctx, 2);
            v0 = 0;
            // 0x004b5368 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(ra, sp, 0x10);
            lq(s0, sp, 0x0);
            sp = addiu(sp, 0x20);
            return;
        }
    }
    // 0x004b5364: return the Maestro
    charge(ctx, 1);
    v0 = s0;
    // 0x004b5368 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u64 sub_4B5330(EEContext& ctx, u64 maestro) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(maestro));
    sub_4B5330(ctx);
    return static_cast<u64>(ee::core::gpr64(ctx, GPR_V0));
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (the bodies read their arguments from the registers) -----------
namespace p3fes::recomp_gen {
namespace pg = ::p3fes::game;

void fn_sub_4C2FB0_004c2fb0(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4C2FB0(); }
void fn_sub_4C6BE0_004c6be0(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4C6BE0(); }
void fn_sub_4C6C60_004c6c60(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4C6C60(); }
void fn_RwCameraClear_004c9e90(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).RwCameraClear(); }
void fn_sub_4CDC70_004cdc70(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4CDC70(); }
void fn_sub_4CDCE0_004cdce0(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4CDCE0(); }
void fn_sub_4CDE00_004cde00(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4CDE00(); }
void fn_RwRasterShowRaster_004cdfe0(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).RwRasterShowRaster(); }
void fn_sub_4CE200_004ce200(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4CE200(); }
void fn_sub_4D0FD0_004d0fd0(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4D0FD0(); }
void fn_sub_4D13E0_004d13e0(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4D13E0(); }
void fn_sub_4F3150_004f3150(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4F3150(); }
void fn_sub_4F1ED0_004f1ed0(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4F1ED0(); }
void fn_sub_4F2150_004f2150(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4F2150(); }
void fn_sub_4E2F10_004e2f10(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4E2F10(); }
void fn_sub_4AAB40_004aab40(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4AAB40(); }
void fn_sub_4AAD50_004aad50(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4AAD50(); }
void fn_sub_4AB0C0_004ab0c0(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4AB0C0(); }
void fn_sub_4AC390_004ac390(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4AC390(); }
void fn_sub_4AB8C0_004ab8c0(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4AB8C0(); }
void fn_sub_4AAE60_004aae60(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4AAE60(); }
void fn_sub_4AA2C0_004aa2c0(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4AA2C0(); }
void fn_sub_4A6600_004a6600(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4A6600(); }
void fn_sub_4ACE70_004ace70(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4ACE70(); }
void fn_sub_4AE940_004ae940(p3fes::EEContext& ctx) { pg::c3::detail::Cpu(ctx).sub_4AE940(); }

}  // namespace p3fes::recomp_gen
