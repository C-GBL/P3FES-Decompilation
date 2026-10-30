// The game root, the logo and the title screen (game/include/p3fes/game/title.h), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/27_unmapped_bands.md section 4). Phase 5 slice `title`: these replace the recompiled bodies listed in
// game/replaced.txt; tests/game/test_title.cpp runs each against its __recomp body.
//
// Virtual time per ADR-0013: every guest::enter / charge mirrors a `ctx.cycles += N` block of the recompiled body on
// the executed path, charged where the block starts (before its calls), and guest::backedge sits where the recompiled
// loop checks before jumping back (all loops here test first: the check comes after a true test, before the body).
//
// Register discipline (docs/PHASE5_AGENT_BRIEF.md, the wave-6 / wave-7 lessons). These functions are entered through
// `jalr` from the kwln task kernel or called by recompiled code, and a check point may preempt the thread and save
// the whole register file into guest memory. So each one
//   * writes the original prologue spills (Frame: `sd ra`, `sq s0..`, `swc1 $f20`) and reloads them at the return;
//   * keeps in every register the original writes the value the original has there at each call, each check point
//     and the return (S(...) where the original assigns it; a register the original leaves alone keeps what the
//     caller or the last callee left);
//   * calls through the callee's generated entry point with $ra = the original link (jal), and the visitor calls of
//     sub_269A10 with $v0 = the target and $ra = the `jalr` link (jalr_to);
//   * runs the integer divisions (HI/LO) and the floating-point steps through the runtime's EE operations on the
//     guest registers, in the compiled order (EE single precision, FCR31 flags);
//   * returns its result in $v0 through the shim; the void functions leave $v0 as their last step left it.
// gp-relative globals are read the way the original reads them, through the guest $gp.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 6 of the 60 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: faults only 5, frame/spills 1); each keeps the
// notes of its earlier hand version above it. The others are the hand-written versions this header describes.
#include "p3fes/game/title.h"

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"

#include <utility>
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
// Callees (still recompiled, or replaced by this or other slices: always through their generated entry points).
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);         // K_Assert(file, line): `jr ra` in retail
void fn_kwlnTaskExists_00195460(p3fes::EEContext&);     // (task) (kwln_task)
void fn_kwlnTaskGetState_00195290(p3fes::EEContext&);   // (task) -> 0..3 (kwln_task)
void fn_datGetFlag_0016f190(p3fes::EEContext&);         // (id) (menu_ui)
void fn_sub_16F380_0016f380(p3fes::EEContext&);         // counter get (id)
void fn_sub_16F3E0_0016f3e0(p3fes::EEContext&);         // counter set (id, value)
void fn_sub_17D800_0017d800(p3fes::EEContext&);         // scenario: 1 = The Answer (ui2)
void fn_sub_17D820_0017d820(p3fes::EEContext&);
void fn_sub_182750_00182750(p3fes::EEContext&);         // The Answer: start (0)
void fn_nullsub_6_00188670(p3fes::EEContext&);
void fn_nullsub_7_00188680(p3fes::EEContext&);
void fn_sub_17FAD0_0017fad0(p3fes::EEContext&);         // new game: start the field
void fn_sub_17FB90_0017fb90(p3fes::EEContext&);         // continue: start the field
void fn_sub_188660_00188660(p3fes::EEContext&);         // (ui3)
void fn_sub_195DE0_00195de0(p3fes::EEContext&);
void fn_sub_265C20_00265c20(p3fes::EEContext&);         // creates the "op" / "op draw" pair (heap: not replaced)
void fn_sub_15C460_0015c460(p3fes::EEContext&);
void fn_Y_McProc_CreateMcProcDrawTask_00420340(p3fes::EEContext&);         // memory-card process task (parent, 0)
void fn_sub_108E50_00108e50(p3fes::EEContext&);         // current BGM
void fn_sub_1099D0_001099d0(p3fes::EEContext&);         // play BGM (id, 1)
void fn_sub_108F70_00108f70(p3fes::EEContext&);
void fn_sub_108710_00108710(p3fes::EEContext&);
void fn_sub_108570_00108570(p3fes::EEContext&);
void fn_sub_1085C0_001085c0(p3fes::EEContext&);
void fn_sub_108670_00108670(p3fes::EEContext&);
void fn_sub_1086A0_001086a0(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);         // system sound (0, 0, 0, kind)
void fn_sub_10BC20_0010bc20(p3fes::EEContext&);         // (parent, kind)
void fn_sub_1938E0_001938e0(p3fes::EEContext&);         // the opening movie task (0)
void fn_sub_1928D0_001928d0(p3fes::EEContext&);
void fn_sub_192AA0_00192aa0(p3fes::EEContext&);
void fn_sub_266660_00266660(p3fes::EEContext&);         // this file
void fn_sub_266710_00266710(p3fes::EEContext&);         // op_res update (file I/O: not replaced)
void fn_sub_266A20_00266a20(p3fes::EEContext&);         // op_res: load the title (file I/O: not replaced)
void fn_sub_266CB0_00266cb0(p3fes::EEContext&);         // op_res: load the logo (file I/O: not replaced)
void fn_sub_267430_00267430(p3fes::EEContext&);         // op_title draw (not replaced)
void fn_sub_26A2C0_0026a2c0(p3fes::EEContext&);         // opMenuUpdate (not replaced)
void fn_sub_26EED0_0026eed0(p3fes::EEContext&);         // op_wait draw (not replaced)
void fn_sub_269F50_00269f50(p3fes::EEContext&);         // (render_im2d)
void fn_sub_26C710_0026c710(p3fes::EEContext&);
void fn_sub_26E000_0026e000(p3fes::EEContext&);
void fn_sub_26CC90_0026cc90(p3fes::EEContext&);
void fn_sub_268E20_00268e20(p3fes::EEContext&);
void fn_sub_2720C0_002720c0(p3fes::EEContext&);
void fn_sub_271C10_00271c10(p3fes::EEContext&);
void fn_sub_271DB0_00271db0(p3fes::EEContext&);         // fade out
void fn_sub_271E10_00271e10(p3fes::EEContext&);         // fade in
void fn_sub_271E70_00271e70(p3fes::EEContext&);         // fade busy
void fn_sub_271EC0_00271ec0(p3fes::EEContext&);
void fn_sub_272220_00272220(p3fes::EEContext&);         // fade colour (rgba*)
void fn_sub_272290_00272290(p3fes::EEContext&);
void fn_sub_2722E0_002722e0(p3fes::EEContext&);
void fn_sub_2721D0_002721d0(p3fes::EEContext&);         // fade speed (frames)
void fn_sub_269690_00269690(p3fes::EEContext&);         // (1, 12, 9): heap: not replaced
void fn_sub_2699A0_002699a0(p3fes::EEContext&);         // its destroy: heap: not replaced
void fn_sub_4CDE90_004cde90(p3fes::EEContext&);         // RW: texture destroy
void fn_sub_21CC20_0021cc20(p3fes::EEContext&);
void fn_sub_21CCA0_0021cca0(p3fes::EEContext&);         // (image, index) -> sprite source
void fn_sub_21D3B0_0021d3b0(p3fes::EEContext&);         // (sprite, source)
void fn_sub_21D8E0_0021d8e0(p3fes::EEContext&);         // (sprite, rect*)
void fn_sub_21D950_0021d950(p3fes::EEContext&);         // (sprite, rgba*)
void fn_sub_21EAC0_0021eac0(p3fes::EEContext&);         // (sprite; $f12)
void fn_sub_21EAE0_0021eae0(p3fes::EEContext&);         // (sprite, rect*)
void fn_sub_21EB80_0021eb80(p3fes::EEContext&);         // (sprite, rect*)
void fn_sub_198590_00198590(p3fes::EEContext&);         // the current camera
void fn_sub_488F30_00488f30(p3fes::EEContext&);         // RpRandom
void fn_sinf_0052e878(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_sub_265030_00265030(p3fes::EEContext&);         // this file
void fn_sub_265B30_00265b30(p3fes::EEContext&);
void fn_sub_265BB0_00265bb0(p3fes::EEContext&);
void fn_sub_265F80_00265f80(p3fes::EEContext&);
void fn_sub_266060_00266060(p3fes::EEContext&);
void fn_sub_2660D0_002660d0(p3fes::EEContext&);
void fn_sub_266140_00266140(p3fes::EEContext&);
void fn_sub_2663C0_002663c0(p3fes::EEContext&);
void fn_sub_266430_00266430(p3fes::EEContext&);
void fn_sub_266AE0_00266ae0(p3fes::EEContext&);
void fn_sub_266B30_00266b30(p3fes::EEContext&);
void fn_sub_266BF0_00266bf0(p3fes::EEContext&);
void fn_sub_266C50_00266c50(p3fes::EEContext&);
void fn_sub_266D70_00266d70(p3fes::EEContext&);
void fn_sub_266DC0_00266dc0(p3fes::EEContext&);
void fn_sub_266E50_00266e50(p3fes::EEContext&);
void fn_sub_2692D0_002692d0(p3fes::EEContext&);
void fn_sub_2694B0_002694b0(p3fes::EEContext&);
void fn_sub_269500_00269500(p3fes::EEContext&);
void fn_sub_269550_00269550(p3fes::EEContext&);
void fn_sub_2695B0_002695b0(p3fes::EEContext&);
void fn_sub_269640_00269640(p3fes::EEContext&);
void fn_sub_269D50_00269d50(p3fes::EEContext&);
void fn_sub_26A0F0_0026a0f0(p3fes::EEContext&);
void fn_sub_26A1E0_0026a1e0(p3fes::EEContext&);
void fn_sub_26D430_0026d430(p3fes::EEContext&);
void fn_sub_26DA10_0026da10(p3fes::EEContext&);
void fn_sub_26DA90_0026da90(p3fes::EEContext&);
void fn_sub_26DB30_0026db30(p3fes::EEContext&);
void fn_sub_26DBD0_0026dbd0(p3fes::EEContext&);
void fn_sub_26DC20_0026dc20(p3fes::EEContext&);
void fn_sub_26DC70_0026dc70(p3fes::EEContext&);
void fn_sub_26DCC0_0026dcc0(p3fes::EEContext&);
void fn_sub_26DDC0_0026ddc0(p3fes::EEContext&);
void fn_sub_26E780_0026e780(p3fes::EEContext&);
void fn_sub_26EBF0_0026ebf0(p3fes::EEContext&);
void fn_sub_26EC50_0026ec50(p3fes::EEContext&);
void fn_sub_26ECA0_0026eca0(p3fes::EEContext&);
void fn_sub_26ED40_0026ed40(p3fes::EEContext&);
void fn_sub_26EDB0_0026edb0(p3fes::EEContext&);
void fn_sub_26EDD0_0026edd0(p3fes::EEContext&);
void fn_sub_26EE30_0026ee30(p3fes::EEContext&);
void fn_sub_26EE80_0026ee80(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

using namespace title;
namespace rg = p3fes::recomp_gen;

// --- registers ---------------------------------------------------------------------------------------------------
constexpr unsigned kAT = 1, kV0 = 2, kV1 = 3, kA0 = 4, kA1 = 5, kA2 = 6, kA3 = 7, kS0 = 16, kS1 = 17, kS2 = 18,
                   kS3 = 19, kS4 = 20, kGP = 28, kSP = 29;
constexpr unsigned kF0 = 0, kF1 = 1, kF2 = 2, kF3 = 3, kF12 = 12, kF20 = 20;

u64 R(const EEContext& ctx, unsigned r) { return ee::core::gpr64(ctx, r); }
void S(EEContext& ctx, unsigned r, u64 v) { ee::core::set_gpr64(ctx, r, v); }
u64 sx(u32 v) { return ee::core::sext32(v); }
u32 a32(u64 v) { return static_cast<u32>(v); }
s64 sgn(u64 v) { return static_cast<s64>(v); }

// The recompiled loads / stores stop the program (rt's memory fault) at an unaligned or unmapped address, where
// guest::load reads 0 and guest::store drops the write: an access that does not resolve to RAM (and is no hardware
// window) goes through the same rt operation first, with $zero as its register, so the stop is the same.
template <typename T> void same_fault(EEContext& ctx, u32 va, bool write) {
    if (ctx.memory && ctx.memory->resolve(va, static_cast<u32>(sizeof(T)))) return;
    if ((va & (sizeof(T) - 1u)) == 0 && EEMemory::is_hw(va)) return;
    const s32 imm = static_cast<s32>(va);
    if constexpr (sizeof(T) == 1) write ? rt::sb(ctx, 0, 0, imm) : rt::lbu(ctx, 0, 0, imm);
    else if constexpr (sizeof(T) == 2) write ? rt::sh(ctx, 0, 0, imm) : rt::lhu(ctx, 0, 0, imm);
    else write ? rt::sw(ctx, 0, 0, imm) : rt::lw(ctx, 0, 0, imm);
}
template <typename T> T ld(EEContext& ctx, u64 va) {
    same_fault<T>(ctx, a32(va), false);
    return guest::load<T>(ctx, a32(va));
}
template <typename T> void st(EEContext& ctx, u64 va, T v) {
    same_fault<T>(ctx, a32(va), true);
    guest::store<T>(ctx, a32(va), v);
}
// `lw rX, off(base)`: the word sign-extended, as the register holds it.
u64 lw(EEContext& ctx, u64 base, s32 off) { return sx(ld<u32>(ctx, a32(base) + static_cast<u32>(off))); }
// `lhu rX, off(base)`.
u64 lhu(EEContext& ctx, u64 base, s32 off) { return ld<u16>(ctx, a32(base) + static_cast<u32>(off)); }
void sw(EEContext& ctx, u64 value, u64 base, s32 off) { st<u32>(ctx, a32(base) + static_cast<u32>(off), a32(value)); }
void sb(EEContext& ctx, u64 value, u64 base, s32 off) {
    st<u8>(ctx, a32(base) + static_cast<u32>(off), static_cast<u8>(value));
}
// `addiu` / `addu` / `subu`: the 32-bit result sign-extended.
u64 add32(u64 a, u64 b) { return sx(a32(a) + a32(b)); }
u64 sub32(u64 a, u64 b) { return sx(a32(a) - a32(b)); }
u64 addr(u64 base, s32 off) { return sx(a32(base) + static_cast<u32>(off)); }
// `sll rd, rt, sa`: the low word shifted, sign-extended.
u64 sll(u64 v, unsigned sa) { return sx(a32(v) << sa); }
// `slti` / `slt`: whole-register signed compares.
u64 slt(u64 a, s64 b) { return sgn(a) < b ? 1u : 0u; }

// The gp-relative word at `off` (`lw rX, off(gp)` / `sw rX, off(gp)`).
u64 gpw(EEContext& ctx, s32 off) { return lw(ctx, R(ctx, kGP), off); }
void set_gpw(EEContext& ctx, s32 off, u64 v) { sw(ctx, v, R(ctx, kGP), off); }

// `jal fn` with $ra = the original link (the value the generated body hands rt::jal); returns $v0.
u64 jal(EEContext& ctx, u32 link, guest::Fn fn) {
    rt::jal(ctx, link);
    fn(ctx);
    return R(ctx, kV0);
}

// The prologue `addiu sp, sp, -size; sd ra, ra_off(sp); sq s<n-1>..s0` (s_i at ra_off - 16 * (n - i)) and, with
// `f20`, `swc1 $f20, 0(sp)`; on destruction its epilogue (the reloads from the guest stack, `addiu sp, sp, size`).
class Frame {
public:
    Frame(EEContext& ctx, u32 size, u32 ra_off, unsigned nsaved, bool f20 = false) noexcept
        : ctx_(ctx), size_(size), ra_off_(ra_off), n_(nsaved), f20_(f20) {
        rt::addiu(ctx_, GPR_SP, GPR_SP, -static_cast<s32>(size_));
        rt::sd(ctx_, GPR_RA, GPR_SP, static_cast<s32>(ra_off_));
        for (unsigned i = n_; i-- > 0;) rt::sq(ctx_, kS0 + i, GPR_SP, slot(i));
        if (f20_) rt::swc1(ctx_, kF20, GPR_SP, 0);
    }
    ~Frame() {
        if (abandoned_) return;
        rt::ld(ctx_, GPR_RA, GPR_SP, static_cast<s32>(ra_off_));
        for (unsigned i = n_; i-- > 0;) rt::lq(ctx_, kS0 + i, GPR_SP, slot(i));
        if (f20_) rt::lwc1(ctx_, kF20, GPR_SP, 0);
        rt::addiu(ctx_, GPR_SP, GPR_SP, static_cast<s32>(size_));
    }
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;
    u64 at(u32 off) const noexcept { return addr(R(ctx_, GPR_SP), static_cast<s32>(off)); }  // `addiu rX, sp, off`
    // The generated body's unreachable `jr` default leaves through the target without its epilogue.
    void abandon() noexcept { abandoned_ = true; }

private:
    s32 slot(unsigned i) const noexcept { return static_cast<s32>(ra_off_ - 16u * (n_ - i)); }
    EEContext& ctx_;
    u32 size_, ra_off_;
    unsigned n_;
    bool f20_;
    bool abandoned_ = false;
};

// `lui a0, 0x69; addiu a0, a0, file; addiu a1, zero, line; jal K_Assert` (a 5-cycle block; `jr ra` in retail, so the
// caller continues).
void k_assert(EEContext& ctx, u32 file, u32 line, u32 link) {
    guest::charge(ctx, 5);
    S(ctx, kA0, file);
    S(ctx, kA1, line);
    jal(ctx, link, &rg::fn_sub_19D3F0_0019d3f0);
}
// The "work must exist" check every accessor starts with: `lw rN, off(gp); bnez rN, ok; <k_assert>`.
void need_work(EEContext& ctx, unsigned reg, s32 gp_off, u32 file, u32 line, u32 link) {
    S(ctx, reg, gpw(ctx, gp_off));
    if (R(ctx, reg) == 0) k_assert(ctx, file, line, link);
}

// clear work (sub_2673F0 / sub_269D10 / sub_26A280): `<need_work v1>; gp word = 0`.
void clear_work(EEContext& ctx, s32 gp_off, u32 file, u32 line, u32 link) {
    guest::enter(ctx, 5);
    Frame f(ctx, 16, 0, 0);
    need_work(ctx, kV1, gp_off, file, line, link);
    guest::charge(ctx, 5);
    set_gpw(ctx, gp_off, 0);
}
// flags test (sub_266AE0, sub_266D70, sub_269640, sub_26A1E0, sub_26DCC0, sub_26EE30, sub_26EE80):
// `<need_work v0>; v0 = work->flags & mask`.
u64 work_flag(EEContext& ctx, s32 gp_off, u32 file, u32 line, u32 link, u32 mask) {
    guest::enter(ctx, 5);
    Frame f(ctx, 16, 0, 0);
    need_work(ctx, kV0, gp_off, file, line, link);
    guest::charge(ctx, 7);
    S(ctx, kV0, gpw(ctx, gp_off));
    S(ctx, kV0, lw(ctx, R(ctx, kV0), 0));
    S(ctx, kV0, R(ctx, kV0) & mask);
    return R(ctx, kV0);
}
// `lw r, 0(work); ori r, r, bits; sw r, 0(work)`.
void or_flags(EEContext& ctx, unsigned r, u64 work, u32 bits) {
    S(ctx, r, lw(ctx, work, 0) | bits);
    sw(ctx, R(ctx, r), work, 0);
}
// `lw tmp, off(work); addiu res, zero, mask; and res, tmp, res; sw res, off(work)` (the whole registers).
void and_flags(EEContext& ctx, unsigned tmp, unsigned res, u64 work, s32 off, s32 mask) {
    S(ctx, tmp, lw(ctx, work, off));
    S(ctx, res, sx(static_cast<u32>(mask)));
    S(ctx, res, R(ctx, tmp) & R(ctx, res));
    sw(ctx, R(ctx, res), work, off);
}
// The indexed getters of op_res (sub_266BF0 +12, sub_266C50 +68, sub_266E50 +76): `s0 = index; <need_work v0>;
// v1 = work; v0 = work[index]`.
u64 res_entry(EEContext& ctx, u64 index, s32 off, u32 link) {
    guest::enter(ctx, 7);
    Frame f(ctx, 32, 16, 1);
    S(ctx, kS0, index);
    need_work(ctx, kV0, kGpOpRes, kFileOpRes, 68, link);
    guest::charge(ctx, 9);
    S(ctx, kV1, gpw(ctx, kGpOpRes));
    S(ctx, kV0, sll(R(ctx, kS0), 2));
    S(ctx, kV0, add32(R(ctx, kV0), R(ctx, kV1)));
    S(ctx, kV0, lw(ctx, R(ctx, kV0), off));
    return R(ctx, kV0);
}
// The "alive -> 0, over -> -1" tail of the two task updates (opRoot_UpdateOpTask / gmRoot_UpdateGameRootTask): `<need_work v0>;
// v0 = flags & 1; v0 ? 0 : -1`.
u64 alive_result(EEContext& ctx, s32 gp_off, u32 file, u32 line, u32 link) {
    need_work(ctx, kV0, gp_off, file, line, link);
    guest::charge(ctx, 5);
    S(ctx, kV0, gpw(ctx, gp_off));
    S(ctx, kV0, lw(ctx, R(ctx, kV0), 0) & 1u);
    if (R(ctx, kV0) != 0) {
        guest::charge(ctx, 3);
        S(ctx, kV0, 0);
    } else {
        guest::charge(ctx, 1);
        S(ctx, kV0, sx(0xFFFFFFFFu));
    }
    guest::charge(ctx, 4);
    return R(ctx, kV0);
}
// `lui v0, hi; sw v0, off(sp)`-style float constants: the bits of `hi << 16`.
u64 fbits(u32 hi16) { return sx(hi16 << 16); }

}  // namespace

// =====================================================================================================================
// op_res.c: the title / logo resources (work gp-18780: +0 flags (bit 0 title request pending, 1 logo request pending), +4
// what is built (bit 0 title textures, 1 logo textures), +8 the title request, +12 14 title textures, +68 the title
// image, +76 2 logo textures)
// =====================================================================================================================

// 0x00266670 sub_266670 -- 20 bytes; leaf frame (no stack)
// 0x266670 [opRes_SetWork](work): work->+0 = work->+4 = 0; gp-18780 = work (no check).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_266670(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sw;
    Gpr zero{ctx, 0}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00266670
    enter(ctx, 5);  // entry check point + this block's cycles
    sw(zero, a0, 0);
    sw(zero, a0, 4);
    sw(a0, gp, -18780);  // 0x7CE394
}

// 0x266690 [opRes_ClearWork]: release what is built (title textures, logo textures), then gp-18780 = 0.
void sub_266690(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    need_work(ctx, kV1, kGpOpRes, kFileOpRes, 68, 0x2666b4u);
    guest::charge(ctx, 5);
    S(ctx, kS0, gpw(ctx, kGpOpRes));
    S(ctx, kV1, lw(ctx, R(ctx, kS0), 4) & 1u);
    if (R(ctx, kV1) != 0) {
        guest::charge(ctx, 2);
        jal(ctx, 0x2666d0u, &rg::fn_sub_266B30_00266b30);
    }
    guest::charge(ctx, 4);
    S(ctx, kV1, lw(ctx, R(ctx, kS0), 4) & 2u);
    if (R(ctx, kV1) != 0) {
        guest::charge(ctx, 2);
        jal(ctx, 0x2666e8u, &rg::fn_sub_266DC0_00266dc0);
    }
    guest::charge(ctx, 6);
    set_gpw(ctx, kGpOpRes, 0);
}

// 0x266AE0 [opRes_IsTitleLoading]: flags & 1.
u64 sub_266AE0(EEContext& ctx) { return work_flag(ctx, kGpOpRes, kFileOpRes, 68, 0x266b00u, 1); }

// 0x266B30 [opRes_ReleaseTitle]: destroy the 14 title textures (+12..) and the title image (+68), built &= ~1.
void sub_266B30(EEContext& ctx) {
    guest::enter(ctx, 7);
    Frame f(ctx, 48, 32, 2);
    need_work(ctx, kV1, kGpOpRes, kFileOpRes, 68, 0x266b58u);
    guest::charge(ctx, 4);
    S(ctx, kS0, gpw(ctx, kGpOpRes));
    S(ctx, kS1, 0);
    for (;;) {
        guest::charge(ctx, 3);
        S(ctx, kV1, slt(R(ctx, kS1), 14));
        if (R(ctx, kV1) == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 6);
        S(ctx, kV0, add32(R(ctx, kS0), sll(R(ctx, kS1), 2)));
        S(ctx, kA0, lw(ctx, R(ctx, kV0), 12));
        jal(ctx, 0x266b7cu, &rg::fn_sub_4CDE90_004cde90);
        S(ctx, kS1, add32(R(ctx, kS1), 1));
    }
    guest::charge(ctx, 3);
    S(ctx, kS1, 0);
    for (;;) {  // one image (`blez s1`)
        guest::charge(ctx, 2);
        if (sgn(R(ctx, kS1)) > 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 6);
        S(ctx, kV0, add32(R(ctx, kS0), sll(R(ctx, kS1), 2)));
        S(ctx, kA0, lw(ctx, R(ctx, kV0), 68));
        jal(ctx, 0x266bacu, &rg::fn_sub_21CC20_0021cc20);
        S(ctx, kS1, add32(R(ctx, kS1), 1));
    }
    guest::charge(ctx, 10);
    and_flags(ctx, kA0, kV1, R(ctx, kS0), 4, -2);
}

// 0x266BF0 [opRes_GetTitleTexture](index): +12[index].
u64 sub_266BF0(EEContext& ctx, u64 index) { return res_entry(ctx, index, 12, 0x266c18u); }
// 0x266C50 [opRes_GetTitleImage](index): +68[index].
u64 sub_266C50(EEContext& ctx, u64 index) { return res_entry(ctx, index, 68, 0x266c78u); }
// 0x266D70 [opRes_IsLogoLoading]: flags & 2.
u64 sub_266D70(EEContext& ctx) { return work_flag(ctx, kGpOpRes, kFileOpRes, 68, 0x266d90u, 2); }

// 0x266DC0 [opRes_ReleaseLogo]: destroy the 2 logo textures (+76..), built &= ~2.
void sub_266DC0(EEContext& ctx) {
    guest::enter(ctx, 7);
    Frame f(ctx, 48, 32, 2);
    need_work(ctx, kV1, kGpOpRes, kFileOpRes, 68, 0x266de8u);
    guest::charge(ctx, 4);
    S(ctx, kS0, gpw(ctx, kGpOpRes));
    S(ctx, kS1, 0);
    for (;;) {
        guest::charge(ctx, 3);
        S(ctx, kV1, slt(R(ctx, kS1), 2));
        if (R(ctx, kV1) == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 6);
        S(ctx, kV0, add32(R(ctx, kS0), sll(R(ctx, kS1), 2)));
        S(ctx, kA0, lw(ctx, R(ctx, kV0), 76));
        jal(ctx, 0x266e0cu, &rg::fn_sub_4CDE90_004cde90);
        S(ctx, kS1, add32(R(ctx, kS1), 1));
    }
    guest::charge(ctx, 10);
    and_flags(ctx, kA0, kV1, R(ctx, kS0), 4, -3);
}

// 0x266E50 [opRes_GetLogoTexture](index): +76[index].
u64 sub_266E50(EEContext& ctx, u64 index) { return res_entry(ctx, index, 76, 0x266e78u); }

// =====================================================================================================================
// op_title.c (work gp-18756: +0 flags (bit 0 alive, 2 showing), +4 fade timer, +8 0 = logo / 1 = menu, +16.. the
// sprites, +1552 9 particles of 288 bytes, +4148 3 random seeds)
// =====================================================================================================================

// 0x002673A0 sub_2673A0 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x2673A0 [opTitle_SetWork](work).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_2673A0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002673a0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, -18756);  // 0x7CE3AC
    if (v1 != 0) {
        // 0x002673bc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4864);  // "op_title.c"
        a1 = 149;
        jal(ctx, 0x2673C8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x002673d0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sw(zero, s0, 0);
    sw(s0, gp, -18756);  // 0x7CE3AC
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}
// 0x2673F0 [opTitle_ClearWork].
void sub_2673F0(EEContext& ctx) { clear_work(ctx, kGpOpTitle, kFileOpTitle, 142, 0x267410u); }

// 0x2692D0 [opTitle_Init]: the title sprites from the title image (+16 index 14, +272 13, +784 37, +1040 36,
// +1296 37, +528 17), the 9 particles (+1552 + 288 i: +0 = +272 = 0, sprite index 15), 3 random seeds (+4152 + 8 i
// = 0, +4148 + 8 i = RpRandom() & 7), then sub_269500 (show the logo) and flags |= 1.
void sub_2692D0(EEContext& ctx) {
    guest::enter(ctx, 9);
    Frame f(ctx, 80, 64, 4);
    need_work(ctx, kV0, kGpOpTitle, kFileOpTitle, 142, 0x269300u);
    guest::charge(ctx, 56);
    S(ctx, kS0, gpw(ctx, kGpOpTitle));
    S(ctx, kA0, 0);
    S(ctx, kS2, jal(ctx, 0x269310u, &rg::fn_sub_266C50_00266c50));
    struct Sprite {  // (sprite offset, image index, jal links)
        s32 off;
        u32 index, link_src, link_set;
    };
    static constexpr Sprite kSprites[] = {{16, 14, 0x269324u, 0x269334u},   {272, 13, 0x269344u, 0x269354u},
                                          {784, 37, 0x269364u, 0x269374u},  {1040, 36, 0x269384u, 0x269394u},
                                          {1296, 37, 0x2693a4u, 0x2693b4u}, {528, 17, 0x2693c4u, 0x2693d4u}};
    for (const Sprite& s : kSprites) {
        S(ctx, kA0, R(ctx, kS2));
        S(ctx, kA1, s.index);
        const u64 src = jal(ctx, s.link_src, &rg::fn_sub_21CCA0_0021cca0);
        S(ctx, kA0, addr(R(ctx, kS0), s.off));
        S(ctx, kA1, src);
        jal(ctx, s.link_set, &rg::fn_sub_21D3B0_0021d3b0);
    }
    S(ctx, kS1, 0);
    for (;;) {
        guest::charge(ctx, 3);
        S(ctx, kV0, slt(R(ctx, kS1), 9));
        if (R(ctx, kV0) == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 16);
        S(ctx, kV0, sll(R(ctx, kS1), 3));
        S(ctx, kV0, add32(R(ctx, kV0), R(ctx, kS1)));
        S(ctx, kV0, sll(R(ctx, kV0), 5));  // 288 * i
        S(ctx, kV0, add32(R(ctx, kS0), R(ctx, kV0)));
        S(ctx, kS3, addr(R(ctx, kV0), 1552));
        sw(ctx, 0, R(ctx, kV0), 1552);
        sw(ctx, 0, R(ctx, kV0), 1824);
        S(ctx, kA0, R(ctx, kS2));
        S(ctx, kA1, 15);
        const u64 src = jal(ctx, 0x26940cu, &rg::fn_sub_21CCA0_0021cca0);
        S(ctx, kA0, addr(R(ctx, kS3), 16));
        S(ctx, kA1, src);
        jal(ctx, 0x26941cu, &rg::fn_sub_21D3B0_0021d3b0);
        S(ctx, kS1, add32(R(ctx, kS1), 1));
    }
    guest::charge(ctx, 3);
    S(ctx, kS1, 0);
    for (;;) {
        guest::charge(ctx, 3);
        S(ctx, kV0, slt(R(ctx, kS1), 3));
        if (R(ctx, kV0) == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 9);
        S(ctx, kV0, add32(R(ctx, kS0), sll(R(ctx, kS1), 3)));
        S(ctx, kS2, addr(R(ctx, kV0), 4148));
        sw(ctx, 0, R(ctx, kV0), 4152);
        const u64 r = jal(ctx, 0x269450u, &rg::fn_sub_488F30_00488f30);
        S(ctx, kV0, r & 7u);
        sw(ctx, R(ctx, kV0), R(ctx, kS2), 0);
        S(ctx, kS1, add32(R(ctx, kS1), 1));
    }
    guest::charge(ctx, 13);
    jal(ctx, 0x269470u, &rg::fn_sub_269500_00269500);
    or_flags(ctx, kV1, R(ctx, kS0), 1);
}

// 0x2694B0 [opTitle_Stop]: flags &= ~1.
void sub_2694B0(EEContext& ctx) {
    guest::enter(ctx, 5);
    Frame f(ctx, 16, 0, 0);
    need_work(ctx, kV1, kGpOpTitle, kFileOpTitle, 142, 0x2694d0u);
    guest::charge(ctx, 9);
    S(ctx, kA1, gpw(ctx, kGpOpTitle));
    and_flags(ctx, kA0, kV1, R(ctx, kA1), 0, -2);
}

// 0x269500 [opTitle_ShowLogo]: +4 = +8 = 0, flags |= 4.
void sub_269500(EEContext& ctx) {
    guest::enter(ctx, 5);
    Frame f(ctx, 16, 0, 0);
    need_work(ctx, kV1, kGpOpTitle, kFileOpTitle, 142, 0x269520u);
    guest::charge(ctx, 10);
    S(ctx, kA0, gpw(ctx, kGpOpTitle));
    sw(ctx, 0, R(ctx, kA0), 4);
    sw(ctx, 0, R(ctx, kA0), 8);
    or_flags(ctx, kV1, R(ctx, kA0), 4);
}

// 0x269550 [opTitle_ShowMenu]: +4 = 0, +8 = 1, flags |= 4.
void sub_269550(EEContext& ctx) {
    guest::enter(ctx, 5);
    Frame f(ctx, 16, 0, 0);
    need_work(ctx, kV1, kGpOpTitle, kFileOpTitle, 142, 0x269570u);
    guest::charge(ctx, 11);
    S(ctx, kA0, gpw(ctx, kGpOpTitle));
    sw(ctx, 0, R(ctx, kA0), 4);
    S(ctx, kV1, 1);
    sw(ctx, 1, R(ctx, kA0), 8);
    or_flags(ctx, kV1, R(ctx, kA0), 4);
}

// 0x2695B0 [opTitle_SkipFade]: asserts showing (line 1212) and the logo page (+8 == 0, line 1213); +4 = 200.
void sub_2695B0(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    need_work(ctx, kV1, kGpOpTitle, kFileOpTitle, 142, 0x2695d4u);
    guest::charge(ctx, 5);
    S(ctx, kS0, gpw(ctx, kGpOpTitle));
    S(ctx, kV1, lw(ctx, R(ctx, kS0), 0) & 4u);
    if (R(ctx, kV1) == 0) k_assert(ctx, kFileOpTitle, 1212, 0x2695fcu);
    guest::charge(ctx, 3);
    S(ctx, kV1, lw(ctx, R(ctx, kS0), 8));
    if (R(ctx, kV1) != 0) k_assert(ctx, kFileOpTitle, 1213, 0x26961cu);
    guest::charge(ctx, 7);
    S(ctx, kV1, 200);
    sw(ctx, 200, R(ctx, kS0), 4);
}

// 0x269640 [opTitle_IsShowing]: flags & 4.
u64 sub_269640(EEContext& ctx) { return work_flag(ctx, kGpOpTitle, kFileOpTitle, 142, 0x269660u, 4); }

// 0x00269A10 sub_269A10 -- 620 bytes; frame 0xA0: ra sp+0x70, s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq), s5 sp+0x80
// 0x269A10 [opTitle_ForEachGridPoint](grid, visitor): calls visitor->+0 (`jalr`) once per point of a
// (grid->+8 + 1) x (grid->+12 + 1) grid with a record on its frame: +128 grid, +132 x in [0, 1], +136 y in [0, 1],
// +140 visitor->+4, +144 the point index. grid->+24 picks the layout: 0 a plain grid (index = row * (cols + 1) + col),
// 1 a staggered one whose even rows get one point more (x = 0, 1 at the ends, the inner points shifted by half a
// cell); other values visit nothing.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_269A10(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::cvt_s_w, hg::div_s,
          hg::enter, hg::jalr, hg::ld, hg::lq, hg::lw, hg::lwc1, hg::madd_s, hg::mtc1, hg::mult, hg::nor, hg::sd,
          hg::slt, hg::sq, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3};
    // 0x00269a10
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(ra, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    s4 = a1;
    sw(s5, sp, 0x80);
    lw(v1, a1, 4);
    sw(v1, sp, 0x8C);
    lw(a0, a0, 24);
    v1 = 1;
    if (a0 == v1) {
        // 0x00269b0c
        charge(ctx, 4);
        s1 = 0;
        s3 = 0;
        for (;;) {
            // 0x00269c3c
            charge(ctx, 5);
            lw(v1, s5, 12);
            v1 = addiu(v1, 1);
            v1 = slt(s3, v1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x00269b1c
            charge(ctx, 4);
            v1 = nor(s3, 0);
            s6 = v1 & 0x1;
            if (s6 == 0) {
                // 0x00269b3c
                charge(ctx, 2);
                lw(v1, s5, 8);
                s0 = addiu(v1, 1);
            } else {
                // 0x00269b2c
                charge(ctx, 4);
                lw(v1, s5, 8);
                s0 = addiu(v1, 2);
            }
            // 0x00269b44
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x00269c2c
                charge(ctx, 3);
                v1 = slt(s2, s0);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00269b50
                charge(ctx, 2);
                if (s6 == 0) {
                    // 0x00269bd8
                    charge(ctx, 6);
                    lwc1(f0, s5, 8);
                    cvt_s_w(f1, f0);
                    mtc1(s2, f0);
                    cvt_s_w(f0, f0);
                    div_s(f0, f0, f1);
                } else {
                    // 0x00269b58
                    charge(ctx, 2);
                    if (s2 != 0) {
                        // 0x00269b6c
                        charge(ctx, 3);
                        v0 = addiu(s0, -1);
                        if (s2 != v0) {
                            // 0x00269b88
                            charge(ctx, 20);
                            lwc1(f0, s5, 8);
                            v0 = 0x3F800000;
                            mtc1(v0, f1);
                            cvt_s_w(f0, f0);
                            div_s(f3, f1, f0);
                            v0 = addiu(s2, -1);
                            mtc1(v0, f0);
                            cvt_s_w(f2, f0);
                            v0 = 0x40000000;
                            mtc1(v0, f0);
                            div_s(f1, f3, f0);
                            mtc1(zero, f0);
                            adda_s(f0, f1);
                            madd_s(f0, f3, f2);
                        } else {
                            // 0x00269b78
                            charge(ctx, 4);
                            v0 = 0x3F800000;
                            mtc1(v0, f0);
                        }
                    } else {
                        // 0x00269b60
                        charge(ctx, 3);
                        mtc1(zero, f0);
                    }
                }
                // 0x00269bf0
                charge(ctx, 15);
                swc1(f0, sp, 0x84);
                lwc1(f0, s5, 12);
                cvt_s_w(f1, f0);
                mtc1(s3, f0);
                cvt_s_w(f0, f0);
                div_s(f0, f0, f1);
                swc1(f0, sp, 0x88);
                sw(s1, sp, 0x90);
                a0 = addiu(sp, 0x80);
                lw(v0, s4, 0);
                jalr(ctx, 0x269C1Cu, v0.u());
                s2 = addiu(s2, 1);
                s1 = addiu(s1, 1);
            }
            // 0x00269c38
            charge(ctx, 1);
            s3 = addiu(s3, 1);
        }
    } else {
        // 0x00269a58
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x00269a68
            charge(ctx, 3);
            s0 = 0;
            for (;;) {
                // 0x00269af0
                charge(ctx, 5);
                lw(v1, s5, 12);
                v1 = addiu(v1, 1);
                v1 = slt(s0, v1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x00269a74
                charge(ctx, 3);
                s1 = 0;
                for (;;) {
                    // 0x00269ad8
                    charge(ctx, 5);
                    lw(v1, s5, 8);
                    a0 = addiu(v1, 1);
                    v1 = slt(s1, a0);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x00269a80
                    charge(ctx, 22);
                    lwc1(f0, s5, 8);
                    mult(v0, a0, s0);
                    v0 = addu(s1, v0);
                    mtc1(s1, f1);
                    cvt_s_w(f1, f1);
                    cvt_s_w(f0, f0);
                    div_s(f0, f1, f0);
                    swc1(f0, sp, 0x84);
                    lwc1(f0, s5, 12);
                    cvt_s_w(f1, f0);
                    mtc1(s0, f0);
                    cvt_s_w(f0, f0);
                    div_s(f0, f0, f1);
                    swc1(f0, sp, 0x88);
                    sw(v0, sp, 0x90);
                    a0 = addiu(sp, 0x80);
                    lw(v0, s4, 0);
                    jalr(ctx, 0x269ACCu, v0.u());
                    s1 = addiu(s1, 1);
                }
                // 0x00269aec
                charge(ctx, 1);
                s0 = addiu(s0, 1);
            }
            // 0x00269b04
            charge(ctx, 2);
        } else {
            // 0x00269a60
            charge(ctx, 2);
        }
    }
    // 0x00269c50 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(ra, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0xA0);
}

// 0x269C80 / 0x269CA0: sinf / cosf of $f12 in a 16-byte frame (result in $f0).
void sub_269C80(EEContext& ctx) {
    guest::enter(ctx, 8);
    Frame f(ctx, 16, 0, 0);
    jal(ctx, 0x269c88u, &rg::fn_sinf_0052e878);
}
void sub_269CA0(EEContext& ctx) {
    guest::enter(ctx, 8);
    Frame f(ctx, 16, 0, 0);
    jal(ctx, 0x269ca8u, &rg::fn_cosf_0052e6d8);
}

// =====================================================================================================================
// op_logo.c (work gp-18752: +0 flags (bit 0 alive), +4 0 = first logo / 1 = second, +16 the logo sprite, +272 frame
// counter, +276 fade state 0 in / 1 hold / 2 out)
// =====================================================================================================================

// 0x00269CC0 sub_269CC0 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x269CC0 [opLogo_SetWork](work).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_269CC0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00269cc0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, -18752);  // 0x7CE3B0
    if (v1 != 0) {
        // 0x00269cdc
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4848);  // "op_logo.c"
        a1 = 51;
        jal(ctx, 0x269CE8u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x00269cf0 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sw(zero, s0, 0);
    sw(s0, gp, -18752);  // 0x7CE3B0
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}
// 0x269D10 [opLogo_ClearWork].
void sub_269D10(EEContext& ctx) { clear_work(ctx, kGpOpLogo, kFileOpLogo, 44, 0x269d30u); }

// 0x269D50 [opLogo_Update]: per logo (+4 = 0, 1) the fade cycle +276: 0 wait for the fade-in to end (sub_271E70 == 0)
// -> hold (frames +272 = 0); 1 count frames, after 75 frames or any button (pad 0x7E094E) start the fade-out
// (sub_271DB0) -> 2; 2 when the fade ends: the first logo fades in again (sub_271E10) and becomes the second, the
// second clears flags bit 0 (done).
void sub_269D50(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    need_work(ctx, kV1, kGpOpLogo, kFileOpLogo, 44, 0x269d74u);
    guest::charge(ctx, 6);
    S(ctx, kS0, gpw(ctx, kGpOpLogo));
    S(ctx, kV1, ~lw(ctx, R(ctx, kS0), 0) & 1u);
    if (R(ctx, kV1) != 0) {
        guest::charge(ctx, 5);
        return;
    }
    guest::charge(ctx, 4);
    S(ctx, kV1, lw(ctx, R(ctx, kS0), 4));
    S(ctx, kA1, 1);
    // One logo's fade cycle; `second` selects the end of state 2 and the call links.
    const auto cycle = [&](bool second) {
        guest::charge(ctx, 4);
        S(ctx, kA0, lw(ctx, R(ctx, kS0), 276));
        S(ctx, kV1, 2);
        const u64 st = R(ctx, kA0);
        if (st == R(ctx, kV1)) {  // fading out
            guest::charge(ctx, 4);
            if (jal(ctx, second ? 0x269f10u : 0x269e4cu, &rg::fn_sub_271E70_00271e70) != 0) return;
            if (second) {
                guest::charge(ctx, 4);
                and_flags(ctx, kA0, kV1, R(ctx, kS0), 0, -2);
            } else {
                guest::charge(ctx, 7);
                jal(ctx, 0x269e5cu, &rg::fn_sub_271E10_00271e10);
                sw(ctx, 0, R(ctx, kS0), 276);
                S(ctx, kV1, 1);
                sw(ctx, 1, R(ctx, kS0), 4);
            }
            return;
        }
        guest::charge(ctx, 2);
        if (st == R(ctx, kA1)) {  // hold: 75 frames or a button
            guest::charge(ctx, 9);
            S(ctx, kV1, add32(lw(ctx, R(ctx, kS0), 272), 1));
            sw(ctx, R(ctx, kV1), R(ctx, kS0), 272);
            S(ctx, kV1, lhu(ctx, 0, a32(kPadHeld)));
            S(ctx, kV1, (R(ctx, kV1) != 0 ? 1u : 0u) ^ 1u);
            if (R(ctx, kV1) != 0) {
                guest::charge(ctx, 4);
                S(ctx, kV1, slt(lw(ctx, R(ctx, kS0), 272), 75));
                if (R(ctx, kV1) != 0) return;
            }
            guest::charge(ctx, 6);
            jal(ctx, second ? 0x269ef8u : 0x269e34u, &rg::fn_sub_271DB0_00271db0);
            S(ctx, kV1, 2);
            sw(ctx, 2, R(ctx, kS0), 276);
            return;
        }
        guest::charge(ctx, 2);
        if (st == 0) {  // fading in
            guest::charge(ctx, 4);
            if (jal(ctx, second ? 0x269ea0u : 0x269ddcu, &rg::fn_sub_271E70_00271e70) != 0) return;
            guest::charge(ctx, 5);
            sw(ctx, 0, R(ctx, kS0), 272);
            S(ctx, kV1, 1);
            sw(ctx, 1, R(ctx, kS0), 276);
            return;
        }
        guest::charge(ctx, 2);
    };
    const u64 logo = R(ctx, kV1);
    if (logo == R(ctx, kA1)) {
        cycle(true);
    } else {
        guest::charge(ctx, 2);
        if (logo == 0) cycle(false);
        else guest::charge(ctx, 2);
    }
    guest::charge(ctx, 5);
}

// 0x26A0F0 [opLogo_Init]: the logo sprite (+16: rect {0, 0, 0.625, 0.875} in texture space, {0, 0, 640, 448} on
// screen, white), fade speed 20, fade in, +276 = +4 = 0, flags |= 1. (It also fetches logo texture 0 and drops it.)
void sub_26A0F0(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 64, 16, 1);
    need_work(ctx, kV0, kGpOpLogo, kFileOpLogo, 44, 0x26a114u);
    guest::charge(ctx, 48);
    S(ctx, kS0, gpw(ctx, kGpOpLogo));
    S(ctx, kA0, 0);
    jal(ctx, 0x26a124u, &rg::fn_sub_266E50_00266e50);
    const auto rect = [&](u32 w_hi, u32 h_hi) {  // {0, 0, w, h} at sp+32
        sw(ctx, 0, R(ctx, kSP), 32);
        sw(ctx, 0, R(ctx, kSP), 36);
        S(ctx, kV0, fbits(w_hi));
        sw(ctx, R(ctx, kV0), R(ctx, kSP), 40);
        S(ctx, kV0, fbits(h_hi));
        sw(ctx, R(ctx, kV0), R(ctx, kSP), 44);
        S(ctx, kA0, addr(R(ctx, kS0), 16));
        S(ctx, kA1, f.at(32));
    };
    rect(0x3F20u, 0x3F60u);  // 0.625, 0.875
    jal(ctx, 0x26a14cu, &rg::fn_sub_21EAE0_0021eae0);
    rect(0x4420u, 0x43E0u);  // 640, 448
    jal(ctx, 0x26a174u, &rg::fn_sub_21D8E0_0021d8e0);
    S(ctx, kV0, 255);
    for (s32 i = 60; i < 64; ++i) sb(ctx, 255, R(ctx, kSP), i);
    S(ctx, kA0, addr(R(ctx, kS0), 16));
    S(ctx, kA1, f.at(60));
    jal(ctx, 0x26a198u, &rg::fn_sub_21D950_0021d950);
    S(ctx, kA0, 20);
    jal(ctx, 0x26a1a4u, &rg::fn_sub_2721D0_002721d0);
    jal(ctx, 0x26a1acu, &rg::fn_sub_271E10_00271e10);
    sw(ctx, 0, R(ctx, kS0), 276);
    sw(ctx, 0, R(ctx, kS0), 4);
    or_flags(ctx, kV1, R(ctx, kS0), 1);
}

// 0x26A1E0 [opLogo_IsRunning]: flags & 1.
u64 sub_26A1E0(EEContext& ctx) { return work_flag(ctx, kGpOpLogo, kFileOpLogo, 44, 0x26a200u, 1); }

// =====================================================================================================================
// op_menu.c (work gp-18748: +0 flags (bit 0 alive, 2 shown, 3 fading, 5 continue list), +2808 title list cursor,
// +2816 4 title items of 784 bytes (+0 state, +4 timer), +6736 continue list cursor, +6752 2 items of 784 bytes)
// =====================================================================================================================

// 0x0026A230 opMenuSetWork -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x26A230 opMenuSetWork(work).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void opMenuSetWork(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0026a230
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, -18748);  // 0x7CE3B4
    if (v1 != 0) {
        // 0x0026a24c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4832);  // "op_menu.c"
        a1 = 142;
        jal(ctx, 0x26A258u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0026a260 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sw(zero, s0, 0);
    sw(s0, gp, -18748);  // 0x7CE3B4
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}
// 0x26A280 [opMenu_ClearWork].
void sub_26A280(EEContext& ctx) { clear_work(ctx, kGpOpMenu, kFileOpMenu, 135, 0x26a2a0u); }

namespace {
// `sw zero, 112(sp); sw zero, 116(sp); sw r, 120(sp); sw r, 124(sp)` with r = 1.0 (`lui r, 0x3F80` unless the
// caller already holds it): the unit rect {0, 0, 1, 1} of the sprite set-ups.
void unit_rect(EEContext& ctx, s32 at, unsigned r, bool load) {
    sw(ctx, 0, R(ctx, kSP), at);
    sw(ctx, 0, R(ctx, kSP), at + 4);
    if (load) S(ctx, r, fbits(0x3F80u));
    sw(ctx, R(ctx, r), R(ctx, kSP), at + 8);
    sw(ctx, R(ctx, r), R(ctx, kSP), at + 12);
}
// `addiu a0, base, off; addiu a1, sp, at; jal sub_21EAE0; mtc1 zero, $f12; addiu a0, base, off; jal sub_21EAC0`:
// a sprite's source rect and its z = 0.
void sprite_rect_z0(EEContext& ctx, unsigned base, s32 off, s32 at, u32 link_rect, u32 link_z, guest::Fn rect_fn) {
    S(ctx, kA0, addr(R(ctx, base), off));
    S(ctx, kA1, addr(R(ctx, kSP), at));
    jal(ctx, link_rect, rect_fn);
    rt::mtc1(ctx, 0, kF12);
    S(ctx, kA0, addr(R(ctx, base), off));
    jal(ctx, link_z, &rg::fn_sub_21EAC0_0021eac0);
}
// `move a0, image; li/move a1, index; jal sub_21CCA0; addiu a0, base, off; move a1, v0; jal sub_21D3B0`: a sprite
// from image entry `index`.
void sprite_from_image(EEContext& ctx, unsigned image, u64 index, unsigned base, s32 off, u32 link_src, u32 link_set) {
    S(ctx, kA0, R(ctx, image));
    S(ctx, kA1, index);
    const u64 src = jal(ctx, link_src, &rg::fn_sub_21CCA0_0021cca0);
    S(ctx, kA0, addr(R(ctx, base), off));
    S(ctx, kA1, src);
    jal(ctx, link_set, &rg::fn_sub_21D3B0_0021d3b0);
}
// The menu items' `i * 784` (`sll v0, i, 3; subu v1, v0, i; sll v0, v1, 3; subu v0, v0, v1; sll v0, v0, 4`), leaving
// v0 = 784 i and v1 = 7 i as the original does.
u64 item_offset(EEContext& ctx, u64 i) {
    S(ctx, kV0, sll(i, 3));
    S(ctx, kV1, sub32(R(ctx, kV0), i));
    S(ctx, kV0, sll(R(ctx, kV1), 3));
    S(ctx, kV0, sub32(R(ctx, kV0), R(ctx, kV1)));
    S(ctx, kV0, sll(R(ctx, kV0), 4));
    return R(ctx, kV0);
}
// The `if (i == 3) ... else if (i == 2) ... else if (i == 1) ... else if (i == 0)` chains of sub_26D430 choosing the
// sprite index in $s4 (other values leave it): r3 / r2 / r1 are the registers the original loads 3 / 2 / 1 into (the
// load of 3 belongs to the block before), vals the index for i = 0..3.
void pick4(EEContext& ctx, u64 i, unsigned r3, unsigned r2, unsigned r1, const u32 (&vals)[4]) {
    S(ctx, r3, 3);
    if (i == 3) {
        guest::charge(ctx, 1);
        S(ctx, kS4, vals[3]);
        return;
    }
    guest::charge(ctx, 3);
    S(ctx, r2, 2);
    if (i == 2) {
        guest::charge(ctx, 3);
        S(ctx, kS4, vals[2]);
        return;
    }
    guest::charge(ctx, 3);
    S(ctx, r1, 1);
    if (i == 1) {
        guest::charge(ctx, 3);
        S(ctx, kS4, vals[1]);
        return;
    }
    guest::charge(ctx, 2);
    if (i == 0) {
        guest::charge(ctx, 3);
        S(ctx, kS4, vals[0]);
        return;
    }
    guest::charge(ctx, 2);
}
// The two-way form (`li v0, 1; beq i, v0; ...; beqz i`).
void pick2(EEContext& ctx, u64 i, const u32 (&vals)[2]) {
    S(ctx, kV0, 1);
    if (i == 1) {
        guest::charge(ctx, 1);
        S(ctx, kS4, vals[1]);
        return;
    }
    guest::charge(ctx, 2);
    if (i == 0) {
        guest::charge(ctx, 3);
        S(ctx, kS4, vals[0]);
        return;
    }
    guest::charge(ctx, 2);
}
// The selected / idle start of a menu item: `addiu v1, item, list; lw v0, cursor(s2); bne i, v0; sw zero / 8, 0(v1);
// sw zero, 4(v1)` (state 0 = selected, 8 = idle; timer 0).
void item_start(EEContext& ctx, u64 i, s32 list, s32 cursor) {
    S(ctx, kV1, addr(R(ctx, kS1), list));
    S(ctx, kV0, lw(ctx, R(ctx, kS2), cursor));
    if (i == R(ctx, kV0)) {
        guest::charge(ctx, 3);
        sw(ctx, 0, R(ctx, kV1), 0);
    } else {
        guest::charge(ctx, 2);
        S(ctx, kV0, 8);
        sw(ctx, 8, R(ctx, kV1), 0);
    }
    guest::charge(ctx, 4);
    sw(ctx, 0, R(ctx, kV1), 4);
}
}  // namespace

// 0x26D430 [opMenu_Init]: the menu sprites (+16 .. +2064: unit source rects, z 0; +2336 image entry 21), the title
// list (4 items at +2816: three sprites each from entries {0, 2, 4, 25} / {1, 3, 5, 26} / {6, 7, 8, 27}, item +2808
// selected), the continue list (+5968 entry 34, +6224 entry 35; 2 items at +6752 from {28, 30} / {29, 31}, item +6736
// selected), the three fades (+2600 / +2664 / +2728 with scale 1 / camera->+128), the counters cleared, then
// flags |= 8 (fading), sub_26DC70 (show) and flags |= 1.
void sub_26D430(EEContext& ctx) {
    guest::enter(ctx, 11);
    Frame f(ctx, 144, 96, 5, true);
    need_work(ctx, kV0, kGpOpMenu, kFileOpMenu, 135, 0x26d468u);
    guest::charge(ctx, 124);
    S(ctx, kS2, gpw(ctx, kGpOpMenu));
    S(ctx, kA0, 0);
    S(ctx, kS0, jal(ctx, 0x26d478u, &rg::fn_sub_266C50_00266c50));
    const u64 camera = jal(ctx, 0x26d484u, &rg::fn_sub_198590_00198590);
    S(ctx, kV1, fbits(0x3F80u));
    rt::mtc1(ctx, kV1, kF1);
    rt::lwc1(ctx, kF0, kV0, 128);
    rt::div_s(ctx, kF20, kF1, kF0);  // 1 / camera->+128
    (void)camera;
    unit_rect(ctx, 112, kV1, false);
    sprite_rect_z0(ctx, kS2, 16, 112, 0x26d4b4u, 0x26d4c4u, &rg::fn_sub_21EAE0_0021eae0);
    struct Spr {
        s32 off;
        bool rect;
        u32 link_rect, link_z;
    };
    static constexpr Spr kSprs[] = {{272, true, 0x26d4e8u, 0x26d4f8u},   {528, false, 0x26d508u, 0x26d518u},
                                    {784, true, 0x26d53cu, 0x26d54cu},   {1040, false, 0x26d55cu, 0x26d56cu},
                                    {1296, true, 0x26d590u, 0x26d5a0u},  {1552, false, 0x26d5b0u, 0x26d5c0u},
                                    {1808, true, 0x26d5e4u, 0x26d5f4u},  {2064, true, 0x26d618u, 0x26d628u}};
    for (const Spr& s : kSprs) {
        if (s.rect) unit_rect(ctx, 112, kV0, true);
        sprite_rect_z0(ctx, kS2, s.off, 112, s.link_rect, s.link_z, &rg::fn_sub_21EAE0_0021eae0);
    }
    sprite_from_image(ctx, kS0, 21, kS2, 2336, 0x26d638u, 0x26d648u);
    sw(ctx, 0, R(ctx, kS2), 2808);
    S(ctx, kS3, 0);
    for (;;) {  // the title list
        guest::charge(ctx, 3);
        S(ctx, kV0, slt(R(ctx, kS3), 4));
        if (R(ctx, kV0) == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 10);
        const u64 i = R(ctx, kS3);
        S(ctx, kS1, add32(R(ctx, kS2), item_offset(ctx, i)));
        item_start(ctx, i, 2816, 2808);
        pick4(ctx, i, kV0, kV1, kV0, {0, 2, 4, 25});
        guest::charge(ctx, 11);
        sprite_from_image(ctx, kS0, R(ctx, kS4), kS1, 2832, 0x26d704u, 0x26d714u);
        pick4(ctx, i, kV1, kV0, kV0, {1, 3, 5, 26});
        guest::charge(ctx, 11);
        sprite_from_image(ctx, kS0, R(ctx, kS4), kS1, 3088, 0x26d780u, 0x26d790u);
        pick4(ctx, i, kV0, kV0, kV0, {6, 7, 8, 27});
        guest::charge(ctx, 9);
        sprite_from_image(ctx, kS0, R(ctx, kS4), kS1, 3344, 0x26d7fcu, 0x26d80cu);
        S(ctx, kS3, add32(R(ctx, kS3), 1));
    }
    guest::charge(ctx, 23);
    sw(ctx, 0, R(ctx, kS2), 5952);
    sw(ctx, 0, R(ctx, kS2), 5956);
    sprite_from_image(ctx, kS0, 34, kS2, 5968, 0x26d834u, 0x26d844u);
    S(ctx, kS4, 35);
    sprite_from_image(ctx, kS0, R(ctx, kS4), kS2, 6224, 0x26d858u, 0x26d868u);
    sw(ctx, 0, R(ctx, kS2), 6736);
    S(ctx, kS3, 0);
    for (;;) {  // the continue list
        guest::charge(ctx, 3);
        S(ctx, kV0, slt(R(ctx, kS3), 2));
        if (R(ctx, kV0) == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 10);
        const u64 i = R(ctx, kS3);
        S(ctx, kS1, add32(R(ctx, kS2), item_offset(ctx, i)));
        item_start(ctx, i, 6752, 6736);
        pick2(ctx, i, {28, 30});
        guest::charge(ctx, 11);
        sprite_from_image(ctx, kS0, R(ctx, kS4), kS1, 6768, 0x26d8f4u, 0x26d904u);
        pick2(ctx, i, {29, 31});
        guest::charge(ctx, 9);
        sprite_from_image(ctx, kS0, R(ctx, kS4), kS1, 7024, 0x26d940u, 0x26d950u);
        S(ctx, kS3, add32(R(ctx, kS3), 1));
    }
    guest::charge(ctx, 39);
    for (s32 base : {2600, 2664, 2728}) {  // three fades: +8 = +12 = 0, +16 = 1 / camera->+128, +0 = 0
        sw(ctx, 0, R(ctx, kS2), base + 8);
        sw(ctx, 0, R(ctx, kS2), base + 12);
        rt::swc1(ctx, kF20, kS2, base + 16);
        sw(ctx, 0, R(ctx, kS2), base);
    }
    for (s32 off : {2320, 2324, 2328, 2784, 2788, 2792, 2796, 2800, 2804}) sw(ctx, 0, R(ctx, kS2), off);
    or_flags(ctx, kV0, R(ctx, kS2), 8);
    jal(ctx, 0x26d9c8u, &rg::fn_sub_26DC70_0026dc70);
    or_flags(ctx, kV1, R(ctx, kS2), 1);
}

// 0x26DA10 [opMenu_Stop]: select item 0 of both lists, hide the continue list, flags &= ~1.
void sub_26DA10(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    need_work(ctx, kV0, kGpOpMenu, kFileOpMenu, 135, 0x26da34u);
    guest::charge(ctx, 18);
    S(ctx, kS0, gpw(ctx, kGpOpMenu));
    S(ctx, kA0, 0);
    jal(ctx, 0x26da44u, &rg::fn_sub_26DA90_0026da90);
    S(ctx, kA0, 0);
    jal(ctx, 0x26da50u, &rg::fn_sub_26DB30_0026db30);
    jal(ctx, 0x26da58u, &rg::fn_sub_26DC20_0026dc20);
    and_flags(ctx, kA0, kV1, R(ctx, kS0), 0, -2);
}

namespace {
// sub_26DA90 / sub_26DB30: the new item's state = 8 (then 0), the old item's timer = 0, cursor = item, the new item's
// state / timer = 0 -- in the original's order and registers.
void select_item(EEContext& ctx, u64 item, s32 cursor, s32 list, u32 link) {
    guest::enter(ctx, 7);
    Frame f(ctx, 32, 16, 1);
    S(ctx, kS0, item);
    need_work(ctx, kV1, kGpOpMenu, kFileOpMenu, 135, link);
    guest::charge(ctx, 25);
    S(ctx, kA2, gpw(ctx, kGpOpMenu));
    const auto times784 = [&](u64 i) {  // `sll v1, i, 3; subu a0, v1, i; sll v1, a0, 3; subu v1, v1, a0; sll ..., 4`
        S(ctx, kV1, sll(i, 3));
        S(ctx, kA0, sub32(R(ctx, kV1), i));
        S(ctx, kV1, sll(R(ctx, kA0), 3));
        S(ctx, kV1, sub32(R(ctx, kV1), R(ctx, kA0)));
    };
    times784(R(ctx, kS0));
    S(ctx, kA0, sll(R(ctx, kV1), 4));
    S(ctx, kV1, 8);
    S(ctx, kA1, add32(R(ctx, kA0), R(ctx, kA2)));
    sw(ctx, 8, R(ctx, kA1), list);
    S(ctx, kA0, lw(ctx, R(ctx, kA2), cursor));
    S(ctx, kV1, sll(R(ctx, kA0), 3));
    S(ctx, kA0, sub32(R(ctx, kV1), R(ctx, kA0)));
    S(ctx, kV1, sll(R(ctx, kA0), 3));
    S(ctx, kV1, sub32(R(ctx, kV1), R(ctx, kA0)));
    S(ctx, kV1, sll(R(ctx, kV1), 4));
    S(ctx, kV1, add32(R(ctx, kV1), R(ctx, kA2)));
    sw(ctx, 0, R(ctx, kV1), list + 4);
    sw(ctx, R(ctx, kS0), R(ctx, kA2), cursor);
    sw(ctx, 0, R(ctx, kA1), list);
    sw(ctx, 0, R(ctx, kA1), list + 4);
}
}  // namespace

// 0x26DA90 [opMenu_SelectTitleItem](item).
void sub_26DA90(EEContext& ctx, u64 item) { select_item(ctx, item, 2808, 2816, 0x26dab8u); }
// 0x26DB30 [opMenu_SelectContinueItem](item).
void sub_26DB30(EEContext& ctx, u64 item) { select_item(ctx, item, 6736, 6752, 0x26db58u); }

// 0x26DBD0 [opMenu_ShowContinue]: flags |= 0x20.
void sub_26DBD0(EEContext& ctx) {
    guest::enter(ctx, 5);
    Frame f(ctx, 16, 0, 0);
    need_work(ctx, kV1, kGpOpMenu, kFileOpMenu, 135, 0x26dbf0u);
    guest::charge(ctx, 8);
    S(ctx, kA0, gpw(ctx, kGpOpMenu));
    or_flags(ctx, kV1, R(ctx, kA0), 0x20);
}

// 0x26DC20 [opMenu_HideContinue]: flags &= ~0x20.
void sub_26DC20(EEContext& ctx) {
    guest::enter(ctx, 5);
    Frame f(ctx, 16, 0, 0);
    need_work(ctx, kV1, kGpOpMenu, kFileOpMenu, 135, 0x26dc40u);
    guest::charge(ctx, 9);
    S(ctx, kA1, gpw(ctx, kGpOpMenu));
    and_flags(ctx, kA0, kV1, R(ctx, kA1), 0, -33);
}

// 0x26DC70 [opMenu_Show]: +2332 = 0, flags |= 4.
void sub_26DC70(EEContext& ctx) {
    guest::enter(ctx, 5);
    Frame f(ctx, 16, 0, 0);
    need_work(ctx, kV1, kGpOpMenu, kFileOpMenu, 135, 0x26dc90u);
    guest::charge(ctx, 9);
    S(ctx, kA0, gpw(ctx, kGpOpMenu));
    sw(ctx, 0, R(ctx, kA0), 2332);
    or_flags(ctx, kV1, R(ctx, kA0), 4);
}

// 0x26DCC0 [opMenu_IsFading]: flags & 8.
u64 sub_26DCC0(EEContext& ctx) { return work_flag(ctx, kGpOpMenu, kFileOpMenu, 135, 0x26dce0u, 8); }

// =====================================================================================================================
// op_wait.c, the "press start" screen (work gp-18744: +0 flags (bit 0 alive, 1 fades created, 2 showing, 3 fading
// in), +4 page, +8 page timer, +12..+48 animation counters, +40 fade-in timer, +64.. the sprites, +3648 3 symbols of
// 272 bytes, +4464 / +4468 the two fade objects)
// =====================================================================================================================

// 0x0026DD10 sub_26DD10 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x26DD10 [opWait_SetWork](work).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_26DD10(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0026dd10
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v1, gp, -18744);  // 0x7CE3B8
    if (v1 != 0) {
        // 0x0026dd2c
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, -4816);  // "op_wait.c"
        a1 = 226;
        jal(ctx, 0x26DD38u, gen::fn_sub_19D3F0_0019d3f0);
    }
    // 0x0026dd40 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    sw(zero, s0, 0);
    sw(s0, gp, -18744);  // 0x7CE3B8
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x26DD60 [opWait_ClearWork]: destroy the fades if created, gp-18744 = 0.
void sub_26DD60(EEContext& ctx) {
    guest::enter(ctx, 5);
    Frame f(ctx, 16, 0, 0);
    need_work(ctx, kV1, kGpOpWait, kFileOpWait, 219, 0x26dd80u);
    guest::charge(ctx, 5);
    S(ctx, kV1, gpw(ctx, kGpOpWait));
    S(ctx, kV1, lw(ctx, R(ctx, kV1), 0) & 2u);
    if (R(ctx, kV1) != 0) {
        guest::charge(ctx, 2);
        jal(ctx, 0x26dd9cu, &rg::fn_sub_26ED40_0026ed40);
    }
    guest::charge(ctx, 5);
    set_gpw(ctx, kGpOpWait, 0);
}

namespace {
// `lw v0, off(v1); addiu a0, v0, 1; sw a0, off(v1); li v0, m; div a0, v0; mfhi v0; sw v0, off(v1)`: a counter
// wrapping at m (the divide leaves HI / LO as the original does).
void wrap_counter(EEContext& ctx, s32 off, u32 m) {
    const u64 w = R(ctx, kV1);
    S(ctx, kV0, lw(ctx, w, off));
    S(ctx, kA0, add32(R(ctx, kV0), 1));
    sw(ctx, R(ctx, kA0), w, off);
    S(ctx, kV0, m);
    rt::div(ctx, kA0, kV0);
    rt::mfhi(ctx, kV0);
    sw(ctx, R(ctx, kV0), w, off);
}
// The same through $v0 with the divisor already in $a1 (`lw v0; addiu v0, v0, 1; sw v0; div v0, a1; mfhi v0; sw v0`).
void wrap_counter_a1(EEContext& ctx, s32 off) {
    const u64 w = R(ctx, kV1);
    S(ctx, kV0, add32(lw(ctx, w, off), 1));
    sw(ctx, R(ctx, kV0), w, off);
    rt::div(ctx, kV0, kA1);
    rt::mfhi(ctx, kV0);
    sw(ctx, R(ctx, kV0), w, off);
}
// `lw v0, off(v1); addiu a0, v0, 1; sw a0, off(v1); andi v0, a0, 0x3FF; bgez a0, ..; beqz v0, ..; addiu v0, -1024`:
// the compiled `% 1024` (block costs 2 / 1 on the negative path); the store is the caller's.
void mod1024(EEContext& ctx, s32 off) {
    const u64 w = R(ctx, kV1);
    S(ctx, kV0, lw(ctx, w, off));
    S(ctx, kA0, add32(R(ctx, kV0), 1));
    sw(ctx, R(ctx, kA0), w, off);
    S(ctx, kV0, R(ctx, kA0) & 0x3FFu);
    if (sgn(R(ctx, kA0)) >= 0) return;
    guest::charge(ctx, 2);
    if (R(ctx, kV0) == 0) return;
    guest::charge(ctx, 1);
    S(ctx, kV0, addr(R(ctx, kV0), -1024));
}
}  // namespace

// 0x26DDC0 [opWait_Update]: the animation counters (+12 % 90, +16 % 50, +20 % 30, +24 % 690, +28 % 70, +32 % 690,
// +36 % 1024, +44 % 360, +48 % 1024), the fade-in timer (+40 up to 190, then flags &= ~8), the page timer (+8 up to
// 220 on pages 0 / 1, then flags &= ~4), then the draw sub_26EED0.
void sub_26DDC0(EEContext& ctx) {
    guest::enter(ctx, 5);
    Frame f(ctx, 16, 0, 0);
    need_work(ctx, kV1, kGpOpWait, kFileOpWait, 219, 0x26dde0u);
    guest::charge(ctx, 6);
    S(ctx, kV1, gpw(ctx, kGpOpWait));
    const u64 w = R(ctx, kV1);
    S(ctx, kA0, ~lw(ctx, w, 0) & 1u);
    if (R(ctx, kA0) != 0) {
        guest::charge(ctx, 4);
        return;
    }
    guest::charge(ctx, 47);
    wrap_counter(ctx, 12, 90);
    wrap_counter(ctx, 16, 50);
    wrap_counter(ctx, 20, 30);
    S(ctx, kV0, add32(lw(ctx, w, 24), 1));
    sw(ctx, R(ctx, kV0), w, 24);
    S(ctx, kA1, 690);
    rt::div(ctx, kV0, kA1);
    rt::mfhi(ctx, kV0);
    sw(ctx, R(ctx, kV0), w, 24);
    wrap_counter(ctx, 28, 70);
    wrap_counter_a1(ctx, 32);
    mod1024(ctx, 36);
    guest::charge(ctx, 14);
    sw(ctx, R(ctx, kV0), w, 36);
    wrap_counter(ctx, 44, 360);
    mod1024(ctx, 48);
    guest::charge(ctx, 5);
    sw(ctx, R(ctx, kV0), w, 48);
    S(ctx, kA0, lw(ctx, w, 0));
    S(ctx, kV0, R(ctx, kA0) & 8u);
    if (R(ctx, kV0) != 0) {  // fading in
        guest::charge(ctx, 4);
        S(ctx, kV0, lw(ctx, w, 40));
        S(ctx, kAT, slt(R(ctx, kV0), 190));
        if (R(ctx, kAT) != 0) {
            guest::charge(ctx, 4);
            S(ctx, kV0, add32(R(ctx, kV0), 1));
            sw(ctx, R(ctx, kV0), w, 40);
        } else {
            guest::charge(ctx, 3);
            S(ctx, kV0, sx(0xFFFFFFF7u));
            S(ctx, kV0, R(ctx, kA0) & R(ctx, kV0));
            sw(ctx, R(ctx, kV0), w, 0);
        }
    }
    guest::charge(ctx, 4);
    S(ctx, kA1, lw(ctx, w, 0));
    S(ctx, kV0, R(ctx, kA1) & 4u);
    if (R(ctx, kV0) != 0) {  // showing: the page timer
        guest::charge(ctx, 4);
        S(ctx, kA0, lw(ctx, w, 4));
        S(ctx, kV0, 1);
        bool page = true;
        if (R(ctx, kA0) != R(ctx, kV0)) {
            guest::charge(ctx, 2);
            if (R(ctx, kA0) != 0) {
                guest::charge(ctx, 2);
                page = false;
            }
        }
        if (page) {
            guest::charge(ctx, 4);
            S(ctx, kV0, lw(ctx, w, 8));
            S(ctx, kAT, slt(R(ctx, kV0), 220));
            if (R(ctx, kAT) != 0) {
                guest::charge(ctx, 4);
                S(ctx, kV0, add32(R(ctx, kV0), 1));
                sw(ctx, R(ctx, kV0), w, 8);
            } else {
                guest::charge(ctx, R(ctx, kA0) == 1 ? 3 : 5);  // page 0's block also holds the `b` to the draw
                S(ctx, kV0, sx(0xFFFFFFFBu));
                S(ctx, kV0, R(ctx, kA1) & R(ctx, kV0));
                sw(ctx, R(ctx, kV0), w, 0);
            }
        }
    }
    guest::charge(ctx, 2);
    jal(ctx, 0x26dfdcu, &rg::fn_sub_26EED0_0026eed0);
    guest::charge(ctx, 4);
}

// 0x26E780 [opWait_Init]: the screen sprites (+64 / +320 / +576 unit rects), 3 symbols at +3648 in a random order
// (a 16-swap shuffle of {0, 1, 2} with RpRandom; symbol i's +0 = 100 * perm[i] + 60, unit rect), the two text strips
// (+832 / +1088: rects from the size of title texture 12), +2112, five sprites from the title image (+2368 entry 19,
// +2624 38, +2880 10, +3136 11, +3392 16), sub_26EC50 (show page 0), counters +12..+40 = 0, flags |= 8, the fades
// (sub_26ECA0), the first draw, +44 = +48 = 0, flags |= 1.
void sub_26E780(EEContext& ctx) {
    guest::enter(ctx, 10);
    Frame f(ctx, 144, 80, 4, true);
    need_work(ctx, kV0, kGpOpWait, kFileOpWait, 219, 0x26e7b4u);
    guest::charge(ctx, 54);
    S(ctx, kS3, gpw(ctx, kGpOpWait));
    S(ctx, kA0, 0);
    S(ctx, kS0, jal(ctx, 0x26e7c4u, &rg::fn_sub_266C50_00266c50));
    jal(ctx, 0x26e7d0u, &rg::fn_sub_198590_00198590);
    unit_rect(ctx, 96, kV0, true);
    sprite_rect_z0(ctx, kS3, 64, 96, 0x26e7f4u, 0x26e804u, &rg::fn_sub_21EAE0_0021eae0);
    unit_rect(ctx, 96, kV0, true);
    sprite_rect_z0(ctx, kS3, 320, 96, 0x26e828u, 0x26e838u, &rg::fn_sub_21EAE0_0021eae0);
    unit_rect(ctx, 96, kV0, true);
    sprite_rect_z0(ctx, kS3, 576, 96, 0x26e85cu, 0x26e86cu, &rg::fn_sub_21EAE0_0021eae0);
    unit_rect(ctx, 96, kV0, true);
    S(ctx, kV1, 0);
    for (;;) {  // perm = {0, 1, 2} at sp+128
        guest::charge(ctx, 3);
        S(ctx, kV0, slt(R(ctx, kV1), 3));
        if (R(ctx, kV0) == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 4);
        S(ctx, kV0, add32(sll(R(ctx, kV1), 2), R(ctx, kSP)));
        sw(ctx, R(ctx, kV1), R(ctx, kV0), 128);
        S(ctx, kV1, add32(R(ctx, kV1), 1));
    }
    guest::charge(ctx, 3);
    S(ctx, kS1, 0);
    for (;;) {  // 16 swaps: perm[RpRandom() % 3] <-> perm[(RpRandom() & 1) + (that >= the first)]
        guest::charge(ctx, 3);
        S(ctx, kV0, slt(R(ctx, kS1), 16));
        if (R(ctx, kV0) == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 11);
        jal(ctx, 0x26e8bcu, &rg::fn_sub_488F30_00488f30);
        S(ctx, kV1, 3);
        rt::divu(ctx, kV0, kV1);
        rt::mfhi(ctx, kS2);
        const u64 r = jal(ctx, 0x26e8d0u, &rg::fn_sub_488F30_00488f30);
        S(ctx, kV1, r & 1u);
        S(ctx, kV0, sgn(R(ctx, kV1)) < sgn(R(ctx, kS2)) ? 1u : 0u);
        if (R(ctx, kV0) == 0) {
            guest::charge(ctx, 1);
            S(ctx, kV1, add32(R(ctx, kV1), 1));
        }
        guest::charge(ctx, 11);
        S(ctx, kV0, add32(sll(R(ctx, kS2), 2), R(ctx, kSP)));
        S(ctx, kA1, addr(R(ctx, kV0), 128));
        S(ctx, kA0, lw(ctx, R(ctx, kA1), 0));
        S(ctx, kV0, add32(sll(R(ctx, kV1), 2), R(ctx, kSP)));
        S(ctx, kV1, addr(R(ctx, kV0), 128));
        S(ctx, kV0, lw(ctx, R(ctx, kV1), 0));
        sw(ctx, R(ctx, kV0), R(ctx, kA1), 0);
        sw(ctx, R(ctx, kA0), R(ctx, kV1), 0);
        S(ctx, kS1, add32(R(ctx, kS1), 1));
    }
    guest::charge(ctx, 3);
    S(ctx, kS2, 0);
    for (;;) {  // the 3 symbols
        guest::charge(ctx, 3);
        S(ctx, kV0, slt(R(ctx, kS2), 3));
        if (R(ctx, kV0) == 0) break;
        guest::backedge(ctx);
        guest::charge(ctx, 24);
        S(ctx, kV0, sll(R(ctx, kS2), 4));
        S(ctx, kV0, add32(R(ctx, kV0), R(ctx, kS2)));
        S(ctx, kV0, sll(R(ctx, kV0), 4));  // 272 * i
        S(ctx, kA0, add32(R(ctx, kS3), R(ctx, kV0)));
        S(ctx, kS1, addr(R(ctx, kA0), 3648));
        S(ctx, kV0, add32(sll(R(ctx, kS2), 2), R(ctx, kSP)));
        S(ctx, kV1, lw(ctx, R(ctx, kV0), 128));
        S(ctx, kV0, sll(R(ctx, kV1), 2));
        S(ctx, kV1, add32(R(ctx, kV0), R(ctx, kV1)));
        S(ctx, kV0, sll(R(ctx, kV1), 2));
        S(ctx, kV0, add32(R(ctx, kV1), R(ctx, kV0)));
        S(ctx, kV0, sll(R(ctx, kV0), 2));
        S(ctx, kV0, addr(R(ctx, kV0), 60));  // 100 * perm + 60
        sw(ctx, R(ctx, kV0), R(ctx, kA0), 3648);
        sprite_rect_z0(ctx, kS1, 16, 96, 0x26e974u, 0x26e984u, &rg::fn_sub_21EAE0_0021eae0);
        S(ctx, kS2, add32(R(ctx, kS2), 1));
    }
    guest::charge(ctx, 149);
    S(ctx, kA0, 12);
    const u64 tex = jal(ctx, 0x26e9a0u, &rg::fn_sub_266BF0_00266bf0);
    S(ctx, kS2, lw(ctx, tex, 12));  // texture width
    S(ctx, kS1, lw(ctx, tex, 16));  // height
    S(ctx, kV0, fbits(0x4000u));
    rt::mtc1(ctx, kV0, kF3);
    rt::mtc1(ctx, kS2, kF0);
    rt::cvt_s_w(ctx, kF2, kF0);
    rt::div_s(ctx, kF0, kF3, kF2);
    rt::swc1(ctx, kF0, kSP, 96);
    rt::mtc1(ctx, kS1, kF0);
    rt::cvt_s_w(ctx, kF1, kF0);
    rt::div_s(ctx, kF20, kF3, kF1);
    rt::swc1(ctx, kF20, kSP, 100);
    S(ctx, kV0, fbits(0x4420u));
    rt::mtc1(ctx, kV0, kF0);
    rt::div_s(ctx, kF0, kF0, kF2);
    rt::swc1(ctx, kF0, kSP, 104);
    S(ctx, kV0, fbits(0x43E0u));
    rt::mtc1(ctx, kV0, kF0);
    rt::div_s(ctx, kF0, kF0, kF1);
    rt::swc1(ctx, kF0, kSP, 108);
    sprite_rect_z0(ctx, kS3, 832, 96, 0x26ea10u, 0x26ea20u, &rg::fn_sub_21EB80_0021eb80);
    S(ctx, kV0, 651);
    rt::mtc1(ctx, kV0, kF0);
    rt::cvt_s_w(ctx, kF2, kF0);
    rt::mtc1(ctx, kS2, kF0);
    rt::cvt_s_w(ctx, kF1, kF0);
    rt::div_s(ctx, kF0, kF2, kF1);
    rt::swc1(ctx, kF0, kSP, 96);
    rt::swc1(ctx, kF20, kSP, 100);
    S(ctx, kV0, fbits(0x4368u));
    rt::mtc1(ctx, kV0, kF0);
    rt::div_s(ctx, kF0, kF0, kF1);
    rt::swc1(ctx, kF0, kSP, 104);
    S(ctx, kV0, fbits(0x43D0u));
    rt::mtc1(ctx, kV0, kF1);
    rt::mtc1(ctx, kS1, kF0);
    rt::cvt_s_w(ctx, kF0, kF0);
    rt::div_s(ctx, kF0, kF1, kF0);
    rt::swc1(ctx, kF0, kSP, 108);
    sprite_rect_z0(ctx, kS3, 1088, 96, 0x26ea88u, 0x26ea98u, &rg::fn_sub_21EB80_0021eb80);
    unit_rect(ctx, 96, kV0, true);
    sprite_rect_z0(ctx, kS3, 2112, 96, 0x26eabcu, 0x26eaccu, &rg::fn_sub_21EB80_0021eb80);
    sprite_from_image(ctx, kS0, 19, kS3, 2368, 0x26eadcu, 0x26eaecu);
    sprite_from_image(ctx, kS0, 38, kS3, 2624, 0x26eafcu, 0x26eb0cu);
    sprite_from_image(ctx, kS0, 10, kS3, 2880, 0x26eb1cu, 0x26eb2cu);
    sprite_from_image(ctx, kS0, 11, kS3, 3136, 0x26eb3cu, 0x26eb4cu);
    sprite_from_image(ctx, kS0, 16, kS3, 3392, 0x26eb5cu, 0x26eb6cu);
    jal(ctx, 0x26eb74u, &rg::fn_sub_26EC50_0026ec50);
    for (s32 off = 12; off <= 40; off += 4) sw(ctx, 0, R(ctx, kS3), off);
    or_flags(ctx, kV0, R(ctx, kS3), 8);
    jal(ctx, 0x26eba8u, &rg::fn_sub_26ECA0_0026eca0);
    jal(ctx, 0x26ebb0u, &rg::fn_sub_26EED0_0026eed0);
    sw(ctx, 0, R(ctx, kS3), 44);
    sw(ctx, 0, R(ctx, kS3), 48);
    or_flags(ctx, kV1, R(ctx, kS3), 1);
}

// 0x26EBF0 [opWait_Stop]: flags &= ~1; destroy the fades if created.
void sub_26EBF0(EEContext& ctx) {
    guest::enter(ctx, 5);
    Frame f(ctx, 16, 0, 0);
    need_work(ctx, kV1, kGpOpWait, kFileOpWait, 219, 0x26ec10u);
    guest::charge(ctx, 8);
    S(ctx, kA1, gpw(ctx, kGpOpWait));
    and_flags(ctx, kA0, kV1, R(ctx, kA1), 0, -2);
    S(ctx, kV1, R(ctx, kV1) & 2u);
    if (R(ctx, kV1) != 0) {
        guest::charge(ctx, 2);
        jal(ctx, 0x26ec38u, &rg::fn_sub_26ED40_0026ed40);
    }
    guest::charge(ctx, 4);
}

// 0x26EC50 [opWait_ShowStart]: +8 = +4 = 0, flags |= 4.
void sub_26EC50(EEContext& ctx) {
    guest::enter(ctx, 5);
    Frame f(ctx, 16, 0, 0);
    need_work(ctx, kV1, kGpOpWait, kFileOpWait, 219, 0x26ec70u);
    guest::charge(ctx, 10);
    S(ctx, kA0, gpw(ctx, kGpOpWait));
    sw(ctx, 0, R(ctx, kA0), 8);
    sw(ctx, 0, R(ctx, kA0), 4);
    or_flags(ctx, kV1, R(ctx, kA0), 4);
}

// 0x26ECA0 [opWait_CreateFades]: destroy old ones if created, two sub_269690(1, 12, 9) objects -> +4464 / +4468,
// flags |= 2.
void sub_26ECA0(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    need_work(ctx, kV0, kGpOpWait, kFileOpWait, 219, 0x26ecc4u);
    guest::charge(ctx, 5);
    S(ctx, kS0, gpw(ctx, kGpOpWait));
    S(ctx, kV0, lw(ctx, R(ctx, kS0), 0) & 2u);
    if (R(ctx, kV0) != 0) {
        guest::charge(ctx, 2);
        jal(ctx, 0x26ece0u, &rg::fn_sub_26ED40_0026ed40);
    }
    guest::charge(ctx, 20);
    for (const auto& [link, off] : {std::pair<u32, s32>{0x26ecf4u, 4464}, {0x26ed0cu, 4468}}) {
        S(ctx, kA0, 1);
        S(ctx, kA1, 12);
        S(ctx, kA2, 9);
        sw(ctx, jal(ctx, link, &rg::fn_sub_269690_00269690), R(ctx, kS0), off);
    }
    or_flags(ctx, kV1, R(ctx, kS0), 2);
}

// 0x26ED40 [opWait_DestroyFades]: sub_2699A0 on both, flags &= ~2.
void sub_26ED40(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    need_work(ctx, kV0, kGpOpWait, kFileOpWait, 219, 0x26ed64u);
    guest::charge(ctx, 16);
    S(ctx, kS0, gpw(ctx, kGpOpWait));
    S(ctx, kA0, lw(ctx, R(ctx, kS0), 4464));
    jal(ctx, 0x26ed74u, &rg::fn_sub_2699A0_002699a0);
    S(ctx, kA0, lw(ctx, R(ctx, kS0), 4468));
    jal(ctx, 0x26ed80u, &rg::fn_sub_2699A0_002699a0);
    and_flags(ctx, kA0, kV1, R(ctx, kS0), 0, -3);
}

// 0x26EDB0 [opWait_ShowPressStart]: sub_26EDD0 in a 16-byte frame.
void sub_26EDB0(EEContext& ctx) {
    guest::enter(ctx, 8);
    Frame f(ctx, 16, 0, 0);
    jal(ctx, 0x26edb8u, &rg::fn_sub_26EDD0_0026edd0);
}

// 0x26EDD0: +8 = 0, +4 = 1 (page 1), flags |= 4.
void sub_26EDD0(EEContext& ctx) {
    guest::enter(ctx, 5);
    Frame f(ctx, 16, 0, 0);
    need_work(ctx, kV1, kGpOpWait, kFileOpWait, 219, 0x26edf0u);
    guest::charge(ctx, 11);
    S(ctx, kA0, gpw(ctx, kGpOpWait));
    sw(ctx, 0, R(ctx, kA0), 8);
    S(ctx, kV1, 1);
    sw(ctx, 1, R(ctx, kA0), 4);
    or_flags(ctx, kV1, R(ctx, kA0), 4);
}

// 0x26EE30 [opWait_IsShowing]: flags & 4.
u64 sub_26EE30(EEContext& ctx) { return work_flag(ctx, kGpOpWait, kFileOpWait, 219, 0x26ee50u, 4); }
// 0x26EE80 [opWait_IsFading]: flags & 8.
u64 sub_26EE80(EEContext& ctx) { return work_flag(ctx, kGpOpWait, kFileOpWait, 219, 0x26eea0u, 8); }

// =====================================================================================================================
// gm_root.c: the "game root" task
// =====================================================================================================================

// 0x266140 [gmRoot_Update]: drop the finished children (op root +12: remember gp-18784 in +20; game +16), then
// state 0: once the wait task +40 is gone, create the op root (sub_2663C0); state 1: once the op root is gone, start
// the game by mode +20 (0 new game: The Answer sub_17D820(0) + sub_182750(0), else nullsub_6(0) + sub_17FAD0();
// 1 continue: The Answer sub_182750(0), else sub_17FB90(); other: K_Assert line 188) -> +16, flags |= 4, state 2;
// state 2: count counter 47 up (saturating at 0x7FFFFFFF) unless flag 0x1418, and once the game task is gone either
// restart it (flag 0x1413: sub_266430) or go back to the title (sub_2663C0).
void sub_266140(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    need_work(ctx, kV1, kGpGmRoot, kFileGmRoot, 90, 0x266164u);
    guest::charge(ctx, 6);
    S(ctx, kS0, gpw(ctx, kGpGmRoot));
    const u64 w = R(ctx, kS0);
    S(ctx, kA0, lw(ctx, w, kGmFlags));
    S(ctx, kV1, ~R(ctx, kA0) & 1u);
    if (R(ctx, kV1) != 0) {
        guest::charge(ctx, 5);
        return;
    }
    guest::charge(ctx, 3);
    S(ctx, kV1, R(ctx, kA0) & 2u);
    if (R(ctx, kV1) != 0) {
        guest::charge(ctx, 5);
        S(ctx, kA0, lw(ctx, w, kGmOpTask));
        if (jal(ctx, 0x266194u, &rg::fn_kwlnTaskExists_00195460) == 0) {
            guest::charge(ctx, 6);
            S(ctx, kV1, gpw(ctx, kGpTitleMode));
            sw(ctx, R(ctx, kV1), w, kGmMode);
            and_flags(ctx, kA0, kV1, w, kGmFlags, -3);
        }
    }
    guest::charge(ctx, 4);
    S(ctx, kV1, lw(ctx, w, kGmFlags) & 4u);
    if (R(ctx, kV1) != 0) {
        guest::charge(ctx, 5);
        S(ctx, kA0, lw(ctx, w, kGmGameTask));
        if (jal(ctx, 0x2661d0u, &rg::fn_kwlnTaskExists_00195460) == 0) {
            guest::charge(ctx, 4);
            and_flags(ctx, kA0, kV1, w, kGmFlags, -5);
        }
    }
    guest::charge(ctx, 4);
    S(ctx, kA1, lw(ctx, w, kGmState));
    S(ctx, kV1, 2);
    const u64 state = R(ctx, kA1);
    if (state == 2) {
        guest::charge(ctx, 5);
        S(ctx, kA0, kGmFlagNoCount);
        if (jal(ctx, 0x266330u, &rg::fn_datGetFlag_0016f190) == 0) {
            guest::charge(ctx, 7);
            S(ctx, kA0, kGmSessionCounter);
            jal(ctx, 0x266344u, &rg::fn_sub_16F380_0016f380);
            S(ctx, kV1, 0x7FFFFFFFu);
            if (R(ctx, kV0) != R(ctx, kV1)) {
                guest::charge(ctx, 1);
                S(ctx, kV0, add32(R(ctx, kV0), 1));
            }
            guest::charge(ctx, 4);
            S(ctx, kA0, kGmSessionCounter);
            S(ctx, kA1, R(ctx, kV0));
            jal(ctx, 0x266368u, &rg::fn_sub_16F3E0_0016f3e0);
        }
        guest::charge(ctx, 4);
        S(ctx, kV1, lw(ctx, w, kGmFlags) & 4u);
        if (R(ctx, kV1) == 0) {
            guest::charge(ctx, 5);
            S(ctx, kA0, kGmFlagReturnToTitle);
            if (jal(ctx, 0x266384u, &rg::fn_datGetFlag_0016f190) != 0) {
                guest::charge(ctx, 4);
                jal(ctx, 0x266394u, &rg::fn_sub_266430_00266430);
            } else {
                guest::charge(ctx, 2);
                jal(ctx, 0x2663a4u, &rg::fn_sub_2663C0_002663c0);
            }
        }
    } else {
        guest::charge(ctx, 3);
        S(ctx, kA0, 1);
        if (state == 1) {
            guest::charge(ctx, 4);
            S(ctx, kV1, lw(ctx, w, kGmFlags) & 2u);
            if (R(ctx, kV1) == 0) {
                guest::charge(ctx, 3);
                S(ctx, kV0, lw(ctx, w, kGmMode));
                const u64 mode = R(ctx, kV0);
                bool started = true;
                if (mode == R(ctx, kA0)) {  // continue
                    guest::charge(ctx, 4);
                    if (jal(ctx, 0x2662c0u, &rg::fn_sub_17D800_0017d800) != 0) {
                        guest::charge(ctx, 6);
                        S(ctx, kA0, 0);
                        sw(ctx, jal(ctx, 0x2662d4u, &rg::fn_sub_182750_00182750), w, kGmGameTask);
                    } else {
                        guest::charge(ctx, 5);
                        sw(ctx, jal(ctx, 0x2662e8u, &rg::fn_sub_17FB90_0017fb90), w, kGmGameTask);
                    }
                } else {
                    guest::charge(ctx, 2);
                    if (mode == 0) {  // new game
                        guest::charge(ctx, 4);
                        if (jal(ctx, 0x26626cu, &rg::fn_sub_17D800_0017d800) != 0) {
                            guest::charge(ctx, 9);
                            S(ctx, kA0, 0);
                            jal(ctx, 0x266280u, &rg::fn_sub_17D820_0017d820);
                            S(ctx, kA0, 0);
                            sw(ctx, jal(ctx, 0x26628cu, &rg::fn_sub_182750_00182750), w, kGmGameTask);
                        } else {
                            guest::charge(ctx, 8);
                            S(ctx, kA0, 0);
                            jal(ctx, 0x2662a4u, &rg::fn_nullsub_6_00188670);
                            sw(ctx, jal(ctx, 0x2662acu, &rg::fn_sub_17FAD0_0017fad0), w, kGmGameTask);
                        }
                    } else {
                        guest::charge(ctx, 2);
                        started = false;
                    }
                }
                if (!started) k_assert(ctx, kFileGmRoot, 188, 0x266308u);
                guest::charge(ctx, 7);
                or_flags(ctx, kV1, w, 4);
                S(ctx, kV1, 2);
                sw(ctx, 2, w, kGmState);
            }
        } else {
            guest::charge(ctx, 2);
            if (state == 0) {
                guest::charge(ctx, 5);
                S(ctx, kA0, lw(ctx, w, kGmWaitTask));
                if (jal(ctx, 0x266220u, &rg::fn_kwlnTaskExists_00195460) == 0) {
                    guest::charge(ctx, 4);
                    jal(ctx, 0x266230u, &rg::fn_sub_2663C0_002663c0);
                }
            } else {
                guest::charge(ctx, 2);
            }
        }
    }
    guest::charge(ctx, 5);
}

// 0x2663C0 [gmRoot_CreateOpRoot]: sub_195DE0(), +12 = sub_265C20(+8) (the op task pair), flags |= 2, state 1.
void sub_2663C0(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    need_work(ctx, kV0, kGpGmRoot, kFileGmRoot, 90, 0x2663e4u);
    guest::charge(ctx, 17);
    S(ctx, kS0, gpw(ctx, kGpGmRoot));
    jal(ctx, 0x2663f0u, &rg::fn_sub_195DE0_00195de0);
    S(ctx, kA0, lw(ctx, R(ctx, kS0), kGmParent));
    sw(ctx, jal(ctx, 0x2663fcu, &rg::fn_sub_265C20_00265c20), R(ctx, kS0), kGmOpTask);
    or_flags(ctx, kV1, R(ctx, kS0), 2);
    S(ctx, kV1, 1);
    sw(ctx, 1, R(ctx, kS0), kGmState);
}

// 0x266430 [gmRoot_RestartGame]: K_Assert(line 253) unless sub_188660(); nullsub_7(); +16 = sub_17FB90() (continue),
// flags |= 4, state 2.
void sub_266430(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    need_work(ctx, kV0, kGpGmRoot, kFileGmRoot, 90, 0x266454u);
    guest::charge(ctx, 5);
    S(ctx, kS0, gpw(ctx, kGpGmRoot));
    if (jal(ctx, 0x266460u, &rg::fn_sub_188660_00188660) == 0) k_assert(ctx, kFileGmRoot, 253, 0x26647cu);
    guest::charge(ctx, 15);
    jal(ctx, 0x266484u, &rg::fn_nullsub_7_00188680);
    sw(ctx, jal(ctx, 0x26648cu, &rg::fn_sub_17FB90_0017fb90), R(ctx, kS0), kGmGameTask);
    or_flags(ctx, kV1, R(ctx, kS0), 4);
    S(ctx, kV1, 2);
    sw(ctx, 2, R(ctx, kS0), kGmState);
}

// 0x266590 gmRoot_UpdateGameRootTask(task): sub_266140, then 0 while the game root is alive, -1 once it is over.
u64 gmRoot_UpdateGameRootTask(EEContext& ctx) {
    guest::enter(ctx, 7);
    Frame f(ctx, 16, 0, 0);
    jal(ctx, 0x266598u, &rg::fn_sub_266140_00266140);
    return alive_result(ctx, kGpGmRoot, kFileGmRoot, 90, 0x2665b8u);
}

// 0x266660 [gmRoot_SetMode](mode): gp-18784 = mode.
void sub_266660(EEContext& ctx, u64 mode) {
    guest::enter(ctx, 3);
    set_gpw(ctx, kGpTitleMode, mode);
}

// =====================================================================================================================
// op_root.c: the op root (the logo / movie / title / menu sequence)
// =====================================================================================================================

namespace {
// The idle check of states 8 / 9 / 17: count +17700 up to 450, then fade to black (sub_272220 with {0, 0, 0, 255},
// sub_271DB0), remember the state in +17704 and go to state 10. Returns false after the fade.
bool idle_tick(EEContext& ctx, u64 w, u32 link_colour, u32 link_fade) {
    guest::charge(ctx, 4);
    S(ctx, kV0, lw(ctx, w, kOpIdle));
    S(ctx, kAT, slt(R(ctx, kV0), kOpIdleLimit));
    if (R(ctx, kAT) != 0) {
        guest::charge(ctx, 4);
        S(ctx, kV0, add32(R(ctx, kV0), 1));
        sw(ctx, R(ctx, kV0), w, kOpIdle);
        return true;
    }
    guest::charge(ctx, 16);
    sb(ctx, 0, R(ctx, kSP), 60);
    sb(ctx, 0, R(ctx, kSP), 61);
    sb(ctx, 0, R(ctx, kSP), 62);
    S(ctx, kV0, 255);
    sb(ctx, 255, R(ctx, kSP), 63);
    S(ctx, kA0, addr(R(ctx, kSP), 60));
    jal(ctx, link_colour, &rg::fn_sub_272220_00272220);
    jal(ctx, link_fade, &rg::fn_sub_271DB0_00271db0);
    S(ctx, kV0, lw(ctx, w, kOpState));
    sw(ctx, R(ctx, kV0), w, kOpReturnState);
    S(ctx, kV0, 10);
    sw(ctx, 10, w, kOpState);
    return false;
}
// Any button (pads 0x7E094C / 0x7E0956 outside 0x600) resets the idle counter.
void idle_reset(EEContext& ctx, u64 w, unsigned r) {
    guest::charge(ctx, 5);
    S(ctx, r, lhu(ctx, 0, a32(kPadButtons)) & 0xF9FFu);
    if (R(ctx, r) == 0) {
        guest::charge(ctx, 5);
        S(ctx, r, lhu(ctx, 0, a32(kPadPressed2)) & 0xF9FFu);
        if (R(ctx, r) == 0) return;
    }
    guest::charge(ctx, 1);
    sw(ctx, 0, w, kOpIdle);
}
// While flags bit 3 is set the menu waits until up / down (0x1000 / 0x4000) are released on both pads: returns true
// while one is held. `r` is the test register, `ra` / `rb` take the two pad words.
bool held_lock(EEContext& ctx, u64 w, unsigned r, unsigned ra, unsigned rb) {
    guest::charge(ctx, 4);
    S(ctx, r, lw(ctx, w, kOpFlags) & 8u);
    if (R(ctx, r) == 0) return false;
    guest::charge(ctx, 5);
    S(ctx, ra, lhu(ctx, 0, a32(kPadButtons)));
    S(ctx, r, R(ctx, ra) & 0x1000u);
    if (R(ctx, r) != 0) return true;
    guest::charge(ctx, 5);
    S(ctx, rb, lhu(ctx, 0, a32(kPadPressed2)));
    S(ctx, r, R(ctx, rb) & 0x1000u);
    if (R(ctx, r) != 0) return true;
    guest::charge(ctx, 3);
    S(ctx, r, R(ctx, ra) & 0x4000u);
    if (R(ctx, r) != 0) return true;
    guest::charge(ctx, 3);
    S(ctx, r, R(ctx, rb) & 0x4000u);
    return R(ctx, r) != 0;
}
// `move a0..a3, 0, 0, 0, kind; jal sub_10A4E0`: a system sound.
void sound(EEContext& ctx, u32 kind, u32 link) {
    S(ctx, kA0, 0);
    S(ctx, kA1, 0);
    S(ctx, kA2, 0);
    S(ctx, kA3, kind);
    jal(ctx, link, &rg::fn_sub_10A4E0_0010a4e0);
}
// The up / down presses (0x7E0952 / 0x7E095A): leaves a0 = the first word and, when it was tested, v1 = the second.
// Returns 1 for up, 2 for down, 0 for neither.
int menu_press(EEContext& ctx) {
    guest::charge(ctx, 5);
    S(ctx, kA0, lhu(ctx, 0, a32(kPadPressed)));
    S(ctx, kV0, R(ctx, kA0) & 0x1000u);
    if (R(ctx, kV0) != 0) return 1;
    guest::charge(ctx, 5);
    S(ctx, kV1, lhu(ctx, 0, a32(kPadRepeat)));
    S(ctx, kV0, R(ctx, kV1) & 0x1000u);
    if (R(ctx, kV0) != 0) return 1;
    guest::charge(ctx, 3);
    S(ctx, kV0, R(ctx, kA0) & 0x4000u);
    if (R(ctx, kV0) != 0) return 2;
    guest::charge(ctx, 3);
    S(ctx, kV0, R(ctx, kV1) & 0x4000u);
    return R(ctx, kV0) != 0 ? 2 : 0;
}
// After a cursor move: the cursor sound, then the menu's select function on the new cursor.
void moved(EEContext& ctx, u64 w, u32 link_sound, u32 link_select, guest::Fn select) {
    guest::charge(ctx, 11);
    sound(ctx, 0, link_sound);
    S(ctx, kA0, lw(ctx, w, kOpCursor));
    jal(ctx, link_select, select);
}
}  // namespace

// 0x265030 [opRoot_Update] (opRootUpdate in topic 20): drop the finished children (+16 the memory-card process,
// +24), run the state (jump table 0x7B79D0):
//    0 when sub_108710() and the logo file is ready: opLogo_Init -> 1
//    1 when the logos are done: sub_2722E0(), -> 4 if the movie ran already (gp-19672), else 2
//    2 start the opening movie (sub_1938E0) -> 3;   3 when it finished: gp-19672 = 1 -> 4
//    4 release the logo, create the sub_10BC20 task (kind 35 / 1 alternately, gp-18796) -> 5
//    5 when it is gone: sub_272290(), load the title (sub_266A20) -> 6
//    6 when the title file is ready: sub_2722E0(), opTitle_Init, opWait_Init, BGM 115, idle = 0 -> 8
//    7 when sub_108710(): flags &= ~1 (the op root ends: continue)
//    8 "press start": once the wait screen and the title are up, any button skips the fade-in; idle -> demo fade;
//      Start / Cross (0x9FF) -> opMenu_Init, the menu page, cursor 0, sound 1, sub_2660D0 (state 17)
//    9 the title menu (cursor +17696 0..3): Cross -> sound 1 and New Game (12) / Load (7, gp-18784 = 0) / 2 -> 15 /
//      3 -> the continue list (17); up / down with wrap-around and the release lock (flags bit 3)
//   10 when the fade ended: sub_265F80 (back to the logo)
//   11 when the memory-card process ended: card result (gp-19700) -> gp-18784 = 1, end; else the new-game set-up -> 13
//   12 when sub_108710(): the memory-card check (sub_265B30) -> 11
//   13 when sub_108710(): sub_266060 (-> 9);  14 when +24 is gone -> 16;  15 sub_265BB0 (-> 14);  16 sub_266060
//   17 the continue list (cursor 0..1): Cross -> sound 1, the load task (sub_1928D0 / sub_192AA0) -> 18
//   18 when that task finished: sub_195DE0(), cursor 0, opMenu_ShowContinue, select item 0 -> 9
// then the per-frame modules: sub_266710 (op_res), opLogo_Update, the title draw sub_267430, opWait_Update,
// opMenuUpdate sub_26A2C0, sub_271EC0.
void sub_265030(EEContext& ctx) {
    guest::enter(ctx, 7);
    Frame f(ctx, 64, 32, 2);
    need_work(ctx, kV1, kGpOpRoot, kFileOpRoot, 154, 0x265058u);
    guest::charge(ctx, 6);
    S(ctx, kS0, gpw(ctx, kGpOpRoot));
    const u64 w = R(ctx, kS0);
    S(ctx, kA0, lw(ctx, w, kOpFlags));
    S(ctx, kV1, ~R(ctx, kA0) & 1u);
    if (R(ctx, kV1) != 0) {
        guest::charge(ctx, 6);
        return;
    }
    guest::charge(ctx, 3);
    S(ctx, kV0, R(ctx, kA0) & 2u);
    if (R(ctx, kV0) != 0) {
        guest::charge(ctx, 5);
        S(ctx, kA0, lw(ctx, w, kOpChild16));
        if (jal(ctx, 0x265088u, &rg::fn_kwlnTaskExists_00195460) == 0) {
            guest::charge(ctx, 4);
            and_flags(ctx, kV1, kV0, w, kOpFlags, -3);
        }
    }
    guest::charge(ctx, 4);
    S(ctx, kV0, lw(ctx, w, kOpFlags) & 4u);
    if (R(ctx, kV0) != 0) {
        guest::charge(ctx, 5);
        S(ctx, kA0, lw(ctx, w, kOpChild24));
        if (jal(ctx, 0x2650bcu, &rg::fn_kwlnTaskExists_00195460) == 0) {
            guest::charge(ctx, 4);
            and_flags(ctx, kV1, kV0, w, kOpFlags, -5);
        }
    }
    guest::charge(ctx, 4);
    S(ctx, kV0, lw(ctx, w, kOpState));
    S(ctx, kAT, R(ctx, kV0) < kOpStates ? 1u : 0u);  // sltiu: the whole register, unsigned
    const auto set_state = [&](u32 s) {
        S(ctx, kV0, s);
        sw(ctx, s, w, kOpState);
    };
    // `jal fn; beqz/bnez v0, tail`: the state's guard call.
    const auto call = [&](u32 link, guest::Fn fn) { return jal(ctx, link, fn); };
    if (R(ctx, kAT) != 0) {
        guest::charge(ctx, 7);
        S(ctx, kV1, kOpJumpTable);
        S(ctx, kV0, add32(sll(R(ctx, kV0), 2), R(ctx, kV1)));
        S(ctx, kV0, lw(ctx, R(ctx, kV0), 0));
        const u32 target = a32(R(ctx, kV0));
        switch (target) {
        case 0x265108u:  // 0: start the logos
            guest::charge(ctx, 4);
            if (call(0x265108u, &rg::fn_sub_108710_00108710) == 0) break;
            guest::charge(ctx, 4);
            if (call(0x265118u, &rg::fn_sub_266D70_00266d70) != 0) break;
            guest::charge(ctx, 6);
            jal(ctx, 0x265128u, &rg::fn_sub_26A0F0_0026a0f0);
            set_state(1);
            break;
        case 0x265140u:  // 1: the logos are done
            guest::charge(ctx, 4);
            if (call(0x265140u, &rg::fn_sub_26A1E0_0026a1e0) != 0) break;
            guest::charge(ctx, 5);
            jal(ctx, 0x265150u, &rg::fn_sub_2722E0_002722e0);
            S(ctx, kV0, gpw(ctx, kGpMovieSeen));
            guest::charge(ctx, 4);
            set_state(R(ctx, kV0) != 0 ? 4 : 2);
            break;
        case 0x265184u:  // 2: the opening movie
            guest::charge(ctx, 8);
            S(ctx, kA0, 0);
            sw(ctx, jal(ctx, 0x265188u, &rg::fn_sub_1938E0_001938e0), w, kOpMovieTask);
            set_state(3);
            break;
        case 0x2651a4u:  // 3: wait for the movie
            guest::charge(ctx, 6);
            S(ctx, kA0, lw(ctx, w, kOpMovieTask));
            jal(ctx, 0x2651a8u, &rg::fn_kwlnTaskGetState_00195290);
            S(ctx, kV1, 3);
            if (R(ctx, kV0) != R(ctx, kV1)) break;
            guest::charge(ctx, 7);
            sw(ctx, 0, w, kOpMovieTask);
            S(ctx, kV0, 1);
            set_gpw(ctx, kGpMovieSeen, 1);
            set_state(4);
            break;
        case 0x2651d8u:  // 4: release the logo, the sub_10BC20 task
            guest::charge(ctx, 5);
            jal(ctx, 0x2651d8u, &rg::fn_sub_266DC0_00266dc0);
            S(ctx, kV0, ld<u8>(ctx, a32(R(ctx, kGP)) + static_cast<u32>(kGpOpToggle)));
            if (R(ctx, kV0) == 0) {
                guest::charge(ctx, 9);
                S(ctx, kA0, lw(ctx, w, kOpParent));
                S(ctx, kA1, 35);
                sw(ctx, jal(ctx, 0x2651f4u, &rg::fn_sub_10BC20_0010bc20), w, kOpChild20);
                S(ctx, kV0, 1);
                sb(ctx, 1, R(ctx, kGP), kGpOpToggle);
            } else {
                guest::charge(ctx, 6);
                S(ctx, kA0, lw(ctx, w, kOpParent));
                S(ctx, kA1, 1);
                sw(ctx, jal(ctx, 0x265218u, &rg::fn_sub_10BC20_0010bc20), w, kOpChild20);
                sb(ctx, 0, R(ctx, kGP), kGpOpToggle);
            }
            guest::charge(ctx, 4);
            set_state(5);
            break;
        case 0x265238u:  // 5: load the title
            guest::charge(ctx, 5);
            S(ctx, kA0, lw(ctx, w, kOpChild20));
            if (call(0x26523cu, &rg::fn_kwlnTaskExists_00195460) != 0) break;
            guest::charge(ctx, 8);
            jal(ctx, 0x26524cu, &rg::fn_sub_272290_00272290);
            jal(ctx, 0x265254u, &rg::fn_sub_266A20_00266a20);
            set_state(6);
            break;
        case 0x26526cu:  // 6: build the title
            guest::charge(ctx, 4);
            if (call(0x26526cu, &rg::fn_sub_266AE0_00266ae0) != 0) break;
            guest::charge(ctx, 15);
            jal(ctx, 0x26527cu, &rg::fn_sub_2722E0_002722e0);
            jal(ctx, 0x265284u, &rg::fn_sub_2692D0_002692d0);
            jal(ctx, 0x26528cu, &rg::fn_sub_26E780_0026e780);
            S(ctx, kA0, 115);
            S(ctx, kA1, 1);
            jal(ctx, 0x26529cu, &rg::fn_sub_1099D0_001099d0);
            sw(ctx, 0, w, kOpIdle);
            set_state(8);
            break;
        case 0x26570cu:  // 7: end
            guest::charge(ctx, 4);
            if (call(0x26570cu, &rg::fn_sub_108710_00108710) == 0) break;
            guest::charge(ctx, 6);
            and_flags(ctx, kV1, kV0, w, kOpFlags, -2);
            break;
        case 0x2652b8u: {  // 8: press start
            guest::charge(ctx, 4);
            bool up = call(0x2652b8u, &rg::fn_sub_26EE80_0026ee80) != 0;
            if (up) {
                guest::charge(ctx, 4);
                up = call(0x2652c8u, &rg::fn_sub_269640_00269640) != 0;
            }
            if (up) {
                guest::charge(ctx, 4);
                up = call(0x2652d8u, &rg::fn_sub_26EE30_0026ee30) != 0;
            }
            if (up) {  // still fading in: a button skips it
                guest::charge(ctx, 5);
                S(ctx, kV0, lhu(ctx, 0, a32(kPadHeld)) & 0x9FFu);
                if (R(ctx, kV0) == 0) break;
                guest::charge(ctx, 6);
                jal(ctx, 0x2652fcu, &rg::fn_sub_271C10_00271c10);
                jal(ctx, 0x265304u, &rg::fn_sub_2695B0_002695b0);
                break;
            }
            if (!idle_tick(ctx, w, 0x26534cu, 0x265354u)) break;
            guest::charge(ctx, 5);
            S(ctx, kV0, lhu(ctx, 0, a32(kPadHeld)) & 0x9FFu);
            if (R(ctx, kV0) == 0) break;
            guest::charge(ctx, 17);
            jal(ctx, 0x265388u, &rg::fn_sub_26D430_0026d430);
            jal(ctx, 0x265390u, &rg::fn_sub_26EDB0_0026edb0);
            jal(ctx, 0x265398u, &rg::fn_sub_269550_00269550);
            sw(ctx, 0, w, kOpCursor);
            sound(ctx, 1, 0x2653b4u);
            jal(ctx, 0x2653bcu, &rg::fn_sub_2660D0_002660d0);
            break;
        }
        case 0x2653ccu: {  // 9: the title menu
            guest::charge(ctx, 4);
            if (call(0x2653ccu, &rg::fn_sub_26DCC0_0026dcc0) != 0) break;
            if (!idle_tick(ctx, w, 0x265414u, 0x26541cu)) break;
            guest::charge(ctx, 6);
            S(ctx, kV0, 0);
            S(ctx, kV1, lhu(ctx, 0, a32(kPadHeld)) & 0x40u);
            if (R(ctx, kV1) != 0) {  // Cross
                guest::charge(ctx, 10);
                sound(ctx, 1, 0x265464u);
                S(ctx, kV1, lw(ctx, w, kOpCursor));
                S(ctx, kV0, 3);
                const u64 cur = R(ctx, kV1);
                if (cur == 3) {  // the continue list
                    guest::charge(ctx, 8);
                    sw(ctx, 0, w, kOpCursor);
                    jal(ctx, 0x26552cu, &rg::fn_sub_26DC20_0026dc20);
                    S(ctx, kA0, 0);
                    jal(ctx, 0x265538u, &rg::fn_sub_26DB30_0026db30);
                    set_state(17);
                } else {
                    guest::charge(ctx, 3);
                    S(ctx, kV0, 2);
                    if (cur == 2) {
                        guest::charge(ctx, 4);
                        set_state(15);
                    } else {
                        guest::charge(ctx, 2);
                        if (cur == 0) {  // New Game
                            guest::charge(ctx, 14);
                            jal(ctx, 0x2654e0u, &rg::fn_sub_108570_00108570);
                            S(ctx, kA0, 5);
                            jal(ctx, 0x2654ecu, &rg::fn_sub_108670_00108670);
                            S(ctx, kA0, 20);
                            jal(ctx, 0x2654f8u, &rg::fn_sub_1086A0_001086a0);
                            jal(ctx, 0x265500u, &rg::fn_sub_108F70_00108f70);
                            set_state(12);
                        } else {
                            guest::charge(ctx, 3);
                            S(ctx, kV0, 1);
                            if (cur == 1) {  // Load
                                guest::charge(ctx, 15);
                                S(ctx, kA0, 0);
                                jal(ctx, 0x2654a8u, &rg::fn_sub_266660_00266660);
                                jal(ctx, 0x2654b0u, &rg::fn_sub_108570_00108570);
                                S(ctx, kA0, 5);
                                jal(ctx, 0x2654bcu, &rg::fn_sub_108670_00108670);
                                S(ctx, kA0, 20);
                                jal(ctx, 0x2654c8u, &rg::fn_sub_1086A0_001086a0);
                                set_state(7);
                            } else {
                                guest::charge(ctx, 2);
                            }
                        }
                    }
                }
                guest::charge(ctx, 1);
                S(ctx, kV0, 1);
            }
            idle_reset(ctx, w, kV1);
            if (held_lock(ctx, w, kV1, kA1, kA0)) break;
            guest::charge(ctx, 6);
            and_flags(ctx, kA0, kV1, w, kOpFlags, -9);
            if (R(ctx, kV0) != 0) break;  // confirmed this frame
            const int press = menu_press(ctx);
            if (press == 1) {  // up: 0 -> 3 wraps; reaching 0 sets the lock
                guest::charge(ctx, 3);
                S(ctx, kV0, lw(ctx, w, kOpCursor));
                if (sgn(R(ctx, kV0)) <= 0) {
                    guest::charge(ctx, 2);
                    S(ctx, kV0, 3);
                    sw(ctx, 3, w, kOpCursor);
                } else {
                    guest::charge(ctx, 4);
                    S(ctx, kV0, addr(R(ctx, kV0), -1));
                    sw(ctx, R(ctx, kV0), w, kOpCursor);
                    if (R(ctx, kV0) == 0) {
                        guest::charge(ctx, 5);
                        or_flags(ctx, kV0, w, 8);
                    }
                }
                moved(ctx, w, 0x265650u, 0x26565cu, &rg::fn_sub_26DA90_0026da90);
            } else if (press == 2) {  // down: 3 -> 0 wraps; reaching 3 sets the lock
                guest::charge(ctx, 4);
                S(ctx, kV0, lw(ctx, w, kOpCursor));
                S(ctx, kAT, slt(R(ctx, kV0), 3));
                if (R(ctx, kAT) != 0) {
                    guest::charge(ctx, 5);
                    S(ctx, kV1, addr(R(ctx, kV0), 1));
                    sw(ctx, R(ctx, kV1), w, kOpCursor);
                    S(ctx, kV0, 3);
                    if (R(ctx, kV1) == R(ctx, kV0)) {
                        guest::charge(ctx, 5);
                        or_flags(ctx, kV0, w, 8);
                    }
                } else {
                    guest::charge(ctx, 1);
                    sw(ctx, 0, w, kOpCursor);
                }
                moved(ctx, w, 0x2656d0u, 0x2656dcu, &rg::fn_sub_26DA90_0026da90);
            }
            break;
        }
        case 0x2656ecu:  // 10: after the demo fade
            guest::charge(ctx, 4);
            if (call(0x2656ecu, &rg::fn_sub_271E70_00271e70) != 0) break;
            guest::charge(ctx, 4);
            jal(ctx, 0x2656fcu, &rg::fn_sub_265F80_00265f80);
            break;
        case 0x265754u:  // 11: the memory-card process
            guest::charge(ctx, 4);
            S(ctx, kV0, lw(ctx, w, kOpFlags) & 2u);
            if (R(ctx, kV0) != 0) break;
            guest::charge(ctx, 3);
            S(ctx, kV0, gpw(ctx, kGpMcResultA));
            if (R(ctx, kV0) != 0) {
                guest::charge(ctx, 9);
                S(ctx, kA0, 1);
                jal(ctx, 0x265774u, &rg::fn_sub_266660_00266660);
                and_flags(ctx, kV1, kV0, w, kOpFlags, -2);
            } else {
                guest::charge(ctx, 12);
                jal(ctx, 0x265794u, &rg::fn_sub_1085C0_001085c0);
                S(ctx, kA0, 5);
                jal(ctx, 0x2657a0u, &rg::fn_sub_108670_00108670);
                S(ctx, kA0, 20);
                jal(ctx, 0x2657acu, &rg::fn_sub_1086A0_001086a0);
                set_state(13);
            }
            break;
        case 0x265734u:  // 12
            guest::charge(ctx, 4);
            if (call(0x265734u, &rg::fn_sub_108710_00108710) == 0) break;
            guest::charge(ctx, 4);
            jal(ctx, 0x265744u, &rg::fn_sub_265B30_00265b30);
            break;
        case 0x2657c4u:  // 13
            guest::charge(ctx, 4);
            if (call(0x2657c4u, &rg::fn_sub_108710_00108710) == 0) break;
            guest::charge(ctx, 4);
            jal(ctx, 0x2657d4u, &rg::fn_sub_266060_00266060);
            break;
        case 0x2657f4u:  // 14
            guest::charge(ctx, 4);
            S(ctx, kV0, lw(ctx, w, kOpFlags) & 4u);
            if (R(ctx, kV0) != 0) break;
            guest::charge(ctx, 4);
            set_state(16);
            break;
        case 0x2657e4u:  // 15
            guest::charge(ctx, 4);
            jal(ctx, 0x2657e4u, &rg::fn_sub_265BB0_00265bb0);
            break;
        case 0x265814u:  // 16
            guest::charge(ctx, 4);
            jal(ctx, 0x265814u, &rg::fn_sub_266060_00266060);
            break;
        case 0x265824u: {  // 17: the continue list
            guest::charge(ctx, 4);
            if (call(0x265824u, &rg::fn_sub_26DCC0_0026dcc0) != 0) break;
            if (!idle_tick(ctx, w, 0x26586cu, 0x265874u)) break;
            guest::charge(ctx, 6);
            S(ctx, kS1, 0);
            S(ctx, kV0, lhu(ctx, 0, a32(kPadHeld)) & 0x40u);
            if (R(ctx, kV0) != 0) {  // Cross: the load task
                guest::charge(ctx, 10);
                sound(ctx, 1, 0x2658bcu);
                S(ctx, kS1, 1);
                S(ctx, kV0, lw(ctx, w, kOpCursor));
                if (R(ctx, kV0) == 0) {
                    guest::charge(ctx, 5);
                    sw(ctx, jal(ctx, 0x2658dcu, &rg::fn_sub_1928D0_001928d0), w, kOpChild28);
                } else {
                    guest::charge(ctx, 2);
                    guest::charge(ctx, 3);
                    sw(ctx, jal(ctx, 0x2658f0u, &rg::fn_sub_192AA0_00192aa0), w, kOpChild28);
                }
                guest::charge(ctx, 2);
                set_state(18);
            }
            idle_reset(ctx, w, kV0);
            if (held_lock(ctx, w, kV0, kA0, kV1)) break;
            guest::charge(ctx, 6);
            and_flags(ctx, kV1, kV0, w, kOpFlags, -9);
            if (R(ctx, kS1) != 0) break;
            const int press = menu_press(ctx);
            if (press == 1) {  // up: 0 -> 1 wraps; reaching 0 sets the lock
                guest::charge(ctx, 3);
                S(ctx, kV0, lw(ctx, w, kOpCursor));
                if (sgn(R(ctx, kV0)) <= 0) {
                    guest::charge(ctx, 2);
                    S(ctx, kV0, 1);
                    sw(ctx, 1, w, kOpCursor);
                } else {
                    guest::charge(ctx, 4);
                    S(ctx, kV0, addr(R(ctx, kV0), -1));
                    sw(ctx, R(ctx, kV0), w, kOpCursor);
                    if (R(ctx, kV0) == 0) {
                        guest::charge(ctx, 5);
                        or_flags(ctx, kV0, w, 8);
                    }
                }
                moved(ctx, w, 0x265a08u, 0x265a14u, &rg::fn_sub_26DB30_0026db30);
            } else if (press == 2) {  // down: 1 -> 0 wraps; reaching 1 sets the lock
                guest::charge(ctx, 3);
                S(ctx, kV0, lw(ctx, w, kOpCursor));
                if (sgn(R(ctx, kV0)) > 0) {
                    guest::charge(ctx, 1);
                    sw(ctx, 0, w, kOpCursor);
                } else {
                    guest::charge(ctx, 5);
                    S(ctx, kV1, addr(R(ctx, kV0), 1));
                    sw(ctx, R(ctx, kV1), w, kOpCursor);
                    S(ctx, kV0, 1);
                    if (R(ctx, kV1) == R(ctx, kV0)) {
                        guest::charge(ctx, 5);
                        or_flags(ctx, kV0, w, 8);
                    }
                }
                moved(ctx, w, 0x265a84u, 0x265a90u, &rg::fn_sub_26DB30_0026db30);
            }
            break;
        }
        case 0x265aa0u:  // 18: wait for the load task
            guest::charge(ctx, 6);
            S(ctx, kA0, lw(ctx, w, kOpChild28));
            jal(ctx, 0x265aa4u, &rg::fn_kwlnTaskGetState_00195290);
            S(ctx, kV1, 3);
            if (R(ctx, kV0) != R(ctx, kV1)) break;
            guest::charge(ctx, 11);
            jal(ctx, 0x265ab8u, &rg::fn_sub_195DE0_00195de0);
            sw(ctx, 0, w, kOpCursor);
            sw(ctx, 0, w, kOpChild28);
            jal(ctx, 0x265ac8u, &rg::fn_sub_26DBD0_0026dbd0);
            S(ctx, kA0, 0);
            jal(ctx, 0x265ad4u, &rg::fn_sub_26DA90_0026da90);
            set_state(9);
            break;
        default:  // a rewritten table entry: the generated `jr` leaves through the target without the epilogue
            f.abandon();
            rt::lookup_func(target)(ctx);
            return;
        }
    }
    guest::charge(ctx, 12);
    jal(ctx, 0x265ae4u, &rg::fn_sub_266710_00266710);
    jal(ctx, 0x265aecu, &rg::fn_sub_269D50_00269d50);
    jal(ctx, 0x265af4u, &rg::fn_sub_267430_00267430);
    jal(ctx, 0x265afcu, &rg::fn_sub_26DDC0_0026ddc0);
    jal(ctx, 0x265b04u, &rg::fn_sub_26A2C0_0026a2c0);
    jal(ctx, 0x265b0cu, &rg::fn_sub_271EC0_00271ec0);
    guest::charge(ctx, 6);
}

// 0x265B30 [opRoot_StartMemcardCheck]: clear the card results, +16 = Y_McProc_CreateMcProcDrawTask(+8, 0), flags |= 2, state 11.
void sub_265B30(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    need_work(ctx, kV0, kGpOpRoot, kFileOpRoot, 154, 0x265b54u);
    guest::charge(ctx, 18);
    S(ctx, kS0, gpw(ctx, kGpOpRoot));
    set_gpw(ctx, kGpMcResultA, 0);
    set_gpw(ctx, kGpMcResultB, 0);
    S(ctx, kA0, lw(ctx, R(ctx, kS0), kOpParent));
    S(ctx, kA1, 0);
    sw(ctx, jal(ctx, 0x265b70u, &rg::fn_Y_McProc_CreateMcProcDrawTask_00420340), R(ctx, kS0), kOpChild16);
    or_flags(ctx, kV1, R(ctx, kS0), 2);
    S(ctx, kV1, 11);
    sw(ctx, 11, R(ctx, kS0), kOpState);
}

// 0x265BB0 [opRoot_StartLoadMenu]: +24 = sub_15C460(+8), flags |= 4, state 14.
void sub_265BB0(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    need_work(ctx, kV0, kGpOpRoot, kFileOpRoot, 154, 0x265bd4u);
    guest::charge(ctx, 15);
    S(ctx, kS0, gpw(ctx, kGpOpRoot));
    S(ctx, kA0, lw(ctx, R(ctx, kS0), kOpParent));
    sw(ctx, jal(ctx, 0x265be4u, &rg::fn_sub_15C460_0015c460), R(ctx, kS0), kOpChild24);
    or_flags(ctx, kV1, R(ctx, kS0), 4);
    S(ctx, kV1, 14);
    sw(ctx, 14, R(ctx, kS0), kOpState);
}

// 0x265DC0 opRoot_UpdateOpTask(task): sub_265030, then 0 while the op root is alive, -1 once it is over.
u64 opRoot_UpdateOpTask(EEContext& ctx) {
    guest::enter(ctx, 7);
    Frame f(ctx, 16, 0, 0);
    jal(ctx, 0x265dc8u, &rg::fn_sub_265030_00265030);
    return alive_result(ctx, kGpOpRoot, kFileOpRoot, 154, 0x265de8u);
}

// 0x265E30 opRoot_UpdateOpDrawTask(task): unless state 5 or the op root is over: sub_269F50, the menu draws
// (sub_26C710 / sub_26CC90 + sub_268E20, skipped in state 11, the memory-card check), sub_26E000, sub_2720C0.
// Returns 0.
u64 opRoot_UpdateOpDrawTask(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    need_work(ctx, kV0, kGpOpRoot, kFileOpRoot, 154, 0x265e54u);
    guest::charge(ctx, 5);
    S(ctx, kS0, gpw(ctx, kGpOpRoot));
    S(ctx, kV1, lw(ctx, R(ctx, kS0), kOpState));
    S(ctx, kV0, 5);
    bool draw = R(ctx, kV1) != R(ctx, kV0);
    if (draw) {
        guest::charge(ctx, 5);
        S(ctx, kV0, ~lw(ctx, R(ctx, kS0), kOpFlags) & 1u);
        draw = R(ctx, kV0) == 0;
    }
    if (draw) {
        guest::charge(ctx, 6);
        jal(ctx, 0x265e84u, &rg::fn_sub_269F50_00269f50);
        S(ctx, kV1, lw(ctx, R(ctx, kS0), kOpState));
        S(ctx, kV0, 11);
        if (R(ctx, kV1) != R(ctx, kV0)) {
            guest::charge(ctx, 2);
            jal(ctx, 0x265e9cu, &rg::fn_sub_26C710_0026c710);
        }
        guest::charge(ctx, 6);
        jal(ctx, 0x265ea4u, &rg::fn_sub_26E000_0026e000);
        S(ctx, kV1, lw(ctx, R(ctx, kS0), kOpState));
        S(ctx, kV0, 11);
        if (R(ctx, kV1) != R(ctx, kV0)) {
            guest::charge(ctx, 4);
            jal(ctx, 0x265ebcu, &rg::fn_sub_26CC90_0026cc90);
            jal(ctx, 0x265ec4u, &rg::fn_sub_268E20_00268e20);
        }
        guest::charge(ctx, 2);
        jal(ctx, 0x265eccu, &rg::fn_sub_2720C0_002720c0);
    }
    guest::charge(ctx, 6);
    S(ctx, kV0, 0);
    return 0;
}

// 0x265F80 [opRoot_EndTitle]: sub_108F70(), release the title (sub_266B30), stop the wait screen and the title (and,
// from states 9 / 17, the menu: sub_26DA10; from 8 not; anything else K_Assert line 807), load the logo
// (sub_266CB0), state 0.
void sub_265F80(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    need_work(ctx, kV0, kGpOpRoot, kFileOpRoot, 154, 0x265fa4u);
    guest::charge(ctx, 9);
    S(ctx, kS0, gpw(ctx, kGpOpRoot));
    jal(ctx, 0x265fb0u, &rg::fn_sub_108F70_00108f70);
    jal(ctx, 0x265fb8u, &rg::fn_sub_266B30_00266b30);
    S(ctx, kV1, lw(ctx, R(ctx, kS0), kOpReturnState));
    S(ctx, kV0, 17);
    const u64 from = R(ctx, kV1);
    bool menu = from == 17;
    if (!menu) {
        guest::charge(ctx, 3);
        S(ctx, kV0, 9);
        menu = from == 9;
    }
    if (menu) {
        guest::charge(ctx, 8);
        jal(ctx, 0x266008u, &rg::fn_sub_26EBF0_0026ebf0);
        jal(ctx, 0x266010u, &rg::fn_sub_2694B0_002694b0);
        jal(ctx, 0x266018u, &rg::fn_sub_26DA10_0026da10);
    } else {
        guest::charge(ctx, 3);
        S(ctx, kV0, 8);
        if (from == 8) {
            guest::charge(ctx, 6);
            jal(ctx, 0x265ff0u, &rg::fn_sub_26EBF0_0026ebf0);
            jal(ctx, 0x265ff8u, &rg::fn_sub_2694B0_002694b0);
        } else {
            guest::charge(ctx, 2);
            k_assert(ctx, kFileOpRoot, 807, 0x266034u);
        }
    }
    guest::charge(ctx, 8);
    jal(ctx, 0x26603cu, &rg::fn_sub_266CB0_00266cb0);
    sw(ctx, 0, R(ctx, kS0), kOpState);
}

namespace {
// sub_266060 / sub_2660D0: BGM 54 unless it is already playing, idle = 0, state `next`.
void bgm_and_state(EEContext& ctx, u32 next, u32 link_assert, u32 link_cur, u32 link_play) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 16, 1);
    need_work(ctx, kV0, kGpOpRoot, kFileOpRoot, 154, link_assert);
    guest::charge(ctx, 6);
    S(ctx, kS0, gpw(ctx, kGpOpRoot));
    jal(ctx, link_cur, &rg::fn_sub_108E50_00108e50);
    S(ctx, kA0, 54);
    if (R(ctx, kV0) != R(ctx, kA0)) {
        guest::charge(ctx, 3);
        S(ctx, kA1, 1);
        jal(ctx, link_play, &rg::fn_sub_1099D0_001099d0);
    }
    guest::charge(ctx, 8);
    sw(ctx, 0, R(ctx, kS0), kOpIdle);
    S(ctx, kV1, next);
    sw(ctx, next, R(ctx, kS0), kOpState);
}
}  // namespace

// 0x266060 [opRoot_BackToMenu]: BGM 54, state 9.
void sub_266060(EEContext& ctx) { bgm_and_state(ctx, 9, 0x266084u, 0x266090u, 0x2660a8u); }
// 0x2660D0 [opRoot_ToContinueMenu]: BGM 54, state 17.
void sub_2660D0(EEContext& ctx) { bgm_and_state(ctx, 17, 0x2660f4u, 0x266100u, 0x266118u); }

}  // namespace p3fes::game

// =====================================================================================================================
// Shims: the generated entry points of the replaced functions
// =====================================================================================================================
namespace p3fes::recomp_gen {
using namespace p3fes::game;
namespace {
u64 a(const p3fes::EEContext& ctx, unsigned i) { return ee::core::gpr64(ctx, GPR_A0 + i); }
void v0(p3fes::EEContext& ctx, u64 v) { ee::core::set_gpr64(ctx, GPR_V0, v); }
}  // namespace
void fn_sub_265030_00265030(p3fes::EEContext& ctx) { sub_265030(ctx); }
void fn_sub_265B30_00265b30(p3fes::EEContext& ctx) { sub_265B30(ctx); }
void fn_sub_265BB0_00265bb0(p3fes::EEContext& ctx) { sub_265BB0(ctx); }
void fn_opRoot_UpdateOpTask_00265dc0(p3fes::EEContext& ctx) { v0(ctx, opRoot_UpdateOpTask(ctx)); }
void fn_opRoot_UpdateOpDrawTask_00265e30(p3fes::EEContext& ctx) { v0(ctx, opRoot_UpdateOpDrawTask(ctx)); }
void fn_sub_265F80_00265f80(p3fes::EEContext& ctx) { sub_265F80(ctx); }
void fn_sub_266060_00266060(p3fes::EEContext& ctx) { sub_266060(ctx); }
void fn_sub_2660D0_002660d0(p3fes::EEContext& ctx) { sub_2660D0(ctx); }
void fn_sub_266140_00266140(p3fes::EEContext& ctx) { sub_266140(ctx); }
void fn_sub_2663C0_002663c0(p3fes::EEContext& ctx) { sub_2663C0(ctx); }
void fn_sub_266430_00266430(p3fes::EEContext& ctx) { sub_266430(ctx); }
void fn_gmRoot_UpdateGameRootTask_00266590(p3fes::EEContext& ctx) { v0(ctx, gmRoot_UpdateGameRootTask(ctx)); }
void fn_sub_266660_00266660(p3fes::EEContext& ctx) { sub_266660(ctx, a(ctx, 0)); }
void fn_sub_266690_00266690(p3fes::EEContext& ctx) { sub_266690(ctx); }
void fn_sub_266AE0_00266ae0(p3fes::EEContext& ctx) { v0(ctx, sub_266AE0(ctx)); }
void fn_sub_266B30_00266b30(p3fes::EEContext& ctx) { sub_266B30(ctx); }
void fn_sub_266BF0_00266bf0(p3fes::EEContext& ctx) { v0(ctx, sub_266BF0(ctx, a(ctx, 0))); }
void fn_sub_266C50_00266c50(p3fes::EEContext& ctx) { v0(ctx, sub_266C50(ctx, a(ctx, 0))); }
void fn_sub_266D70_00266d70(p3fes::EEContext& ctx) { v0(ctx, sub_266D70(ctx)); }
void fn_sub_266DC0_00266dc0(p3fes::EEContext& ctx) { sub_266DC0(ctx); }
void fn_sub_266E50_00266e50(p3fes::EEContext& ctx) { v0(ctx, sub_266E50(ctx, a(ctx, 0))); }
void fn_sub_2673F0_002673f0(p3fes::EEContext& ctx) { sub_2673F0(ctx); }
void fn_sub_2692D0_002692d0(p3fes::EEContext& ctx) { sub_2692D0(ctx); }
void fn_sub_2694B0_002694b0(p3fes::EEContext& ctx) { sub_2694B0(ctx); }
void fn_sub_269500_00269500(p3fes::EEContext& ctx) { sub_269500(ctx); }
void fn_sub_269550_00269550(p3fes::EEContext& ctx) { sub_269550(ctx); }
void fn_sub_2695B0_002695b0(p3fes::EEContext& ctx) { sub_2695B0(ctx); }
void fn_sub_269640_00269640(p3fes::EEContext& ctx) { v0(ctx, sub_269640(ctx)); }
void fn_sub_269C80_00269c80(p3fes::EEContext& ctx) { sub_269C80(ctx); }
void fn_sub_269CA0_00269ca0(p3fes::EEContext& ctx) { sub_269CA0(ctx); }
void fn_sub_269D10_00269d10(p3fes::EEContext& ctx) { sub_269D10(ctx); }
void fn_sub_269D50_00269d50(p3fes::EEContext& ctx) { sub_269D50(ctx); }
void fn_sub_26A0F0_0026a0f0(p3fes::EEContext& ctx) { sub_26A0F0(ctx); }
void fn_sub_26A1E0_0026a1e0(p3fes::EEContext& ctx) { v0(ctx, sub_26A1E0(ctx)); }
void fn_sub_26A280_0026a280(p3fes::EEContext& ctx) { sub_26A280(ctx); }
void fn_sub_26D430_0026d430(p3fes::EEContext& ctx) { sub_26D430(ctx); }
void fn_sub_26DA10_0026da10(p3fes::EEContext& ctx) { sub_26DA10(ctx); }
void fn_sub_26DA90_0026da90(p3fes::EEContext& ctx) { sub_26DA90(ctx, a(ctx, 0)); }
void fn_sub_26DB30_0026db30(p3fes::EEContext& ctx) { sub_26DB30(ctx, a(ctx, 0)); }
void fn_sub_26DBD0_0026dbd0(p3fes::EEContext& ctx) { sub_26DBD0(ctx); }
void fn_sub_26DC20_0026dc20(p3fes::EEContext& ctx) { sub_26DC20(ctx); }
void fn_sub_26DC70_0026dc70(p3fes::EEContext& ctx) { sub_26DC70(ctx); }
void fn_sub_26DCC0_0026dcc0(p3fes::EEContext& ctx) { v0(ctx, sub_26DCC0(ctx)); }
void fn_sub_26DD60_0026dd60(p3fes::EEContext& ctx) { sub_26DD60(ctx); }
void fn_sub_26DDC0_0026ddc0(p3fes::EEContext& ctx) { sub_26DDC0(ctx); }
void fn_sub_26E780_0026e780(p3fes::EEContext& ctx) { sub_26E780(ctx); }
void fn_sub_26EBF0_0026ebf0(p3fes::EEContext& ctx) { sub_26EBF0(ctx); }
void fn_sub_26EC50_0026ec50(p3fes::EEContext& ctx) { sub_26EC50(ctx); }
void fn_sub_26ECA0_0026eca0(p3fes::EEContext& ctx) { sub_26ECA0(ctx); }
void fn_sub_26ED40_0026ed40(p3fes::EEContext& ctx) { sub_26ED40(ctx); }
void fn_sub_26EDB0_0026edb0(p3fes::EEContext& ctx) { sub_26EDB0(ctx); }
void fn_sub_26EDD0_0026edd0(p3fes::EEContext& ctx) { sub_26EDD0(ctx); }
void fn_sub_26EE30_0026ee30(p3fes::EEContext& ctx) { v0(ctx, sub_26EE30(ctx)); }
void fn_sub_26EE80_0026ee80(p3fes::EEContext& ctx) { v0(ctx, sub_26EE80(ctx)); }
}  // namespace p3fes::recomp_gen
