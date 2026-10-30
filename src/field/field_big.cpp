// The field layer's larger functions (game/include/p3fes/game/field_big.h), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/26_field.md). Phase 5 slice `field_big`: these replace the recompiled bodies listed in
// game/replaced.txt; tests/game/test_field_big.cpp runs each against its __recomp body.
//
// Virtual time per ADR-0013: every enter / charge below mirrors one `ctx.cycles += N` block of the recompiled body
// (recomp/generated/fn_0006_* .. fn_0008_*) on the executed path; a block that contains a `jal` is charged whole before
// the call, as the generated code does. backedge() stands where the recompiled loop checks before jumping back (for
// the loops whose test block comes first: after the test, before each iteration's body).
//
// Registers. These run under the field root, the dungeon task, the draw tasks and the enemy-think tasks, and a check
// point may preempt the thread: the kernel then writes the whole register file to the guest stack. So each body runs
// on a register view of the guest context (Cpu below: one proxy per GPR, the FPU through the runtime's own instruction
// semantics) and keeps every value in the register the original keeps it in; scratch registers, HI/LO, the FPRs and
// FCR31 hold the original's values at every check point and at the return. Within one block (no check point inside)
// the statements are free to read in the order that explains the code best; across blocks the order is the
// original's. Prologue spills and the original's stack temporaries are written to the guest stack, and every callee is
// entered through its generated entry point with $ra = the original link.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 24 of the 33 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: faults only 20, callee frames 2, the hand version
// terminated the host on a random world 1, frame/spills 1); each keeps the notes of its earlier hand version above
// it. The others are the hand-written versions this header describes.
#include "p3fes/game/field_big.h"

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"
#include "p3fes_recomp_rt.h"

#include <initializer_list>
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
void fn_sub_318B00_00318b00(p3fes::EEContext&);  // mdlGetColor(model) -> u8 rgba[4]
void fn_sub_318AD0_00318ad0(p3fes::EEContext&);  // mdlSetColor(model, rgba)
void fn_K_Scene_IsRandomFloor_001a0250(p3fes::EEContext&);   // (game/src/field/field.cpp)
void fn_sub_1A02C0_001a02c0(p3fes::EEContext&);              // [K_Scene_IsFixedTartarusFloor] (field_lo.cpp)
void fn_sub_3B5D50_003b5d50(p3fes::EEContext&);              // MT_Scene_GetResListHead(type)
void fn_sub_3B5D10_003b5d10(p3fes::EEContext&);              // MT_Scene_GetRes(id)
void fn_K_FldFrame_CtlGetXGrid_001ad910(p3fes::EEContext&);  // (field_lo.cpp)
void fn_K_FldFrame_CtlGetZGrid_001ad920(p3fes::EEContext&);  // (field_lo.cpp)
void fn_sub_198590_00198590(p3fes::EEContext&);              // kwlnGetMainCamera: gp-0x4C30
void fn_sub_1A5AA0_001a5aa0(p3fes::EEContext&);              // (matrix) -> $f0 = its yaw in degrees (atan2f)
void fn_K_Field_Get_001b9120(p3fes::EEContext&);             // &sField (field.cpp)
void fn_sub_1A0150_001a0150(p3fes::EEContext&);              // [K_Scene_SetResFlag](id, on) (field_lo.cpp)
void fn_sub_1C7160_001c7160(p3fes::EEContext&);              // (unit, unit, $f12 distance) -> 0 / 1 (inf: within)
void fn_clndGetCurrentMonth_0017d920(p3fes::EEContext&);
void fn_clndGetCurrentDay_0017da40(p3fes::EEContext&);
void fn_clndIsDateInRange_0017e480(p3fes::EEContext&);       // (m1, d1, m2, d2) -> 1 when today is in the range
void fn_datGetTime_0016ef30(p3fes::EEContext&);              // the time of day 0..8
void fn_datGetFlag_0016f190(p3fes::EEContext&);
void fn_sub_1A01C0_001a01c0(p3fes::EEContext&);              // [K_Scene_IsTartarus] (field_lo.cpp)
void fn_K_FldDungeon_GetCurrentFloor_001bff20(p3fes::EEContext&);  // (field.cpp)
void fn_sub_16F380_0016f380(p3fes::EEContext&);              // (i) -> the g_data counter i
void fn_sub_17D800_0017d800(p3fes::EEContext&);              // gp-0x4D4C (inf: the scenario)
void fn_sub_1099D0_001099d0(p3fes::EEContext&);              // (bgm, 1) (inf: play a BGM; the sound driver)
void fn_sub_108FD0_00108fd0(p3fes::EEContext&);              // (frames) (inf: fade the BGM out)
void fn_sub_10A410_0010a410(p3fes::EEContext&);              // (channel, file) (inf: start a looping file)
void fn_sub_109F60_00109f60(p3fes::EEContext&);              // (channel, 0) (inf: stop the channel)
void fn_sub_318B60_00318b60(p3fes::EEContext&);              // mdlGetMatrix(model)
void fn_sub_318A30_00318a30(p3fes::EEContext&);              // (model, &vec, 2) (inf: mdlTranslate)
void fn_sub_318A50_00318a50(p3fes::EEContext&);              // (model, axis, $f12, 2) (inf: rotate)
void fn_sub_1AB390_001ab390(p3fes::EEContext&);              // collision against an RW collision world
void fn_sub_1ABD20_001abd20(p3fes::EEContext&);              // collision against a mesh
void fn_sub_1D38A0_001d38a0(p3fes::EEContext&);              // (task) -> the frames left before the Reaper (field_hi.cpp)
void fn_sub_1AD940_001ad940(p3fes::EEContext&);              // (out, controller task): its position (this file)
void fn_sub_1ADFF0_001adff0(p3fes::EEContext&);              // (controller task, axis, $f12): turn (this file)
void fn_sub_1AD9E0_001ad9e0(p3fes::EEContext&);              // (controller task, work) (inf: update the model matrix)
void fn_sub_1CD650_001cd650(p3fes::EEContext&);              // (event task, value) (field_hi.cpp)
void fn_sub_1D75F0_001d75f0(p3fes::EEContext&);              // (major, minor, floor) -> initial shadows (k_encount)
void fn_sub_1D76E0_001d76e0(p3fes::EEContext&);              // (major, minor, floor) -> shadows kept (k_encount)
void fn_K_FldDungeon_GetFloorKind_001c0040(p3fes::EEContext&);  // (field.cpp)
void fn_sub_1D0720_001d0720(p3fes::EEContext&);              // (n): places n shadows (26_field.md 6.4)
void fn_sub_1CFDD0_001cfdd0(p3fes::EEContext&);              // (i) -> placement i done
void fn_sub_1D2A10_001d2a10(p3fes::EEContext&);              // the shadows placed
void fn_sub_452010_00452010(p3fes::EEContext&);              // (&pos): the Reaper's spawn position (enemy-think band)
void fn_K_FldUnit_CreateReaper_001cfc50(p3fes::EEContext&);   // (1, &pos)
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_sub_1D38D0_001d38d0(p3fes::EEContext&);              // (task, per_cell) (this file)
void fn_K_FldFrame_IsPointInTriangle_001aaad0(p3fes::EEContext&);  // (point, tri[3], normal) (field.cpp)
void fn_sub_1D0880_001d0880(p3fes::EEContext&);              // (i, n) -> the next spawn slot or 0
void fn_sub_1D7300_001d7300(p3fes::EEContext&);              // (major, minor, floor) -> an encounter (k_encount)
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);              // K_Assert(file, line): `jr $ra` in retail
void fn_sub_1CF940_001cf940(p3fes::EEContext&);              // (encounter, slot): create a shadow
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

namespace core = ee::core;
namespace gen = ::p3fes::recomp_gen;
using namespace fldbig;

// --- R5900 integer results (32-bit operations sign-extend into the 64-bit register) ------------------------------------
constexpr u64 si(s32 v) { return static_cast<u64>(static_cast<s64>(v)); }  // `li rd, imm` / `addiu rd, $zero, imm`
constexpr u64 addu(u64 a, u64 b) { return core::add32(a, b); }
constexpr u64 addiu(u64 a, s32 i) { return core::add32i(a, i); }
constexpr u64 subu(u64 a, u64 b) { return core::sub32(a, b); }
constexpr u64 lui(u32 i) { return core::lui(i); }
constexpr u64 sll(u64 a, unsigned n) { return core::sll(a, n); }
constexpr u64 sra(u64 a, unsigned n) { return core::sra(a, n); }
constexpr u64 dsll32(u64 a, unsigned n) { return core::dsll32(a, n); }
constexpr u64 dsra32(u64 a, unsigned n) { return core::dsra32(a, n); }
constexpr u64 slt(u64 a, u64 b) { return core::slt(a, b); }
constexpr u64 slti(u64 a, s32 i) { return core::slti(a, i); }
constexpr u64 sltiu(u64 a, s32 i) { return core::sltiu(a, i); }
constexpr bool lez(u64 a) { return static_cast<s64>(a) <= 0; }
constexpr u32 w(u64 v) { return static_cast<u32>(v); }

// One GPR of the guest context (64-bit writes keep bits 64..127, as the EE does).
struct Gpr {
    EEContext* c;
    unsigned r;
    operator u64() const noexcept { return c->gpr[r].u64[0]; }
    Gpr& operator=(u64 v) noexcept {
        core::set_gpr64(*c, r, v);
        return *this;
    }
    Gpr& operator=(const Gpr& o) noexcept { return *this = static_cast<u64>(o); }
};

// The guest machine as the bodies see it. IDA's register names: r8..r11 = $a4..$a7, r12..r15 = $t4..$t7.
class Cpu {
public:
    explicit Cpu(EEContext& ctx) noexcept : c(ctx) {}

    EEContext& c;
    Gpr zero{&c, 0}, at{&c, 1}, v0{&c, 2}, v1{&c, 3}, a0{&c, 4}, a1{&c, 5}, a2{&c, 6}, a3{&c, 7};
    Gpr a4{&c, 8}, a5{&c, 9}, a6{&c, 10}, a7{&c, 11}, t4{&c, 12}, t5{&c, 13}, t6{&c, 14}, t7{&c, 15};
    Gpr s0{&c, 16}, s1{&c, 17}, s2{&c, 18}, s3{&c, 19}, s4{&c, 20}, s5{&c, 21}, s6{&c, 22}, s7{&c, 23};
    Gpr t8{&c, 24}, t9{&c, 25}, gp{&c, 28}, sp{&c, 29}, fp{&c, 30}, ra{&c, 31};

    // virtual time
    void enter(u64 n) { guest::enter(c, n); }  // not noexcept: a check point may raise a fatal event
    void charge(u64 n) noexcept { guest::charge(c, n); }
    void backedge() { guest::backedge(c); }

    // loads / stores at base + off (the address is the low word of the sum)
    static u32 ea(u64 base, s32 off) noexcept { return w(base) + static_cast<u32>(off); }
    u64 lw(u64 b, s32 o) const noexcept { return core::sext32(guest::load<u32>(c, ea(b, o))); }
    u64 lh(u64 b, s32 o) const noexcept { return core::sext16(guest::load<u16>(c, ea(b, o))); }
    u64 lhu(u64 b, s32 o) const noexcept { return guest::load<u16>(c, ea(b, o)); }
    u64 lb(u64 b, s32 o) const noexcept { return core::sext8(guest::load<u8>(c, ea(b, o))); }
    u64 lbu(u64 b, s32 o) const noexcept { return guest::load<u8>(c, ea(b, o)); }
    u64 ld(u64 b, s32 o) const noexcept { return guest::load<u64>(c, ea(b, o)); }
    void sw(u64 b, s32 o, u64 v) noexcept { guest::store<u32>(c, ea(b, o), w(v)); }
    void sh(u64 b, s32 o, u64 v) noexcept { guest::store<u16>(c, ea(b, o), static_cast<u16>(v)); }
    void sb(u64 b, s32 o, u64 v) noexcept { guest::store<u8>(c, ea(b, o), static_cast<u8>(v)); }
    void sd(u64 b, s32 o, u64 v) noexcept { guest::store<u64>(c, ea(b, o), v); }
    void sq(const Gpr& r, u64 b, s32 o) noexcept { guest::store<u128>(c, ea(b, o) & ~15u, c.gpr[r.r]); }
    void lq(Gpr& r, u64 b, s32 o) noexcept { core::set_gpr128(c, r.r, guest::load<u128>(c, ea(b, o) & ~15u)); }

    // FPU (the runtime's instruction semantics: EE singles, FCR31 flags)
    void lwc1(unsigned f, u64 b, s32 o) noexcept { c.fpr[f] = guest::load<u32>(c, ea(b, o)); }
    void swc1(unsigned f, u64 b, s32 o) noexcept { guest::store<u32>(c, ea(b, o), c.fpr[f]); }
    void mtc1(const Gpr& g, unsigned f) noexcept { rt::mtc1(c, g.r, f); }
    void mfc1(Gpr& g, unsigned f) noexcept { rt::mfc1(c, g.r, f); }
    void cvt_s_w(unsigned d, unsigned s) noexcept { rt::cvt_s_w(c, d, s); }
    void cvt_w_s(unsigned d, unsigned s) noexcept { rt::cvt_w_s(c, d, s); }
    void add_s(unsigned d, unsigned s, unsigned t) noexcept { rt::add_s(c, d, s, t); }
    void sub_s(unsigned d, unsigned s, unsigned t) noexcept { rt::sub_s(c, d, s, t); }
    void mul_s(unsigned d, unsigned s, unsigned t) noexcept { rt::mul_s(c, d, s, t); }
    void div_s(unsigned d, unsigned s, unsigned t) noexcept { rt::div_s(c, d, s, t); }
    void c_le_s(unsigned s, unsigned t) noexcept { rt::c_le_s(c, s, t); }
    void c_lt_s(unsigned s, unsigned t) noexcept { rt::c_lt_s(c, s, t); }
    void c_eq_s(unsigned s, unsigned t) noexcept { rt::c_eq_s(c, s, t); }
    void mov_s(unsigned d, unsigned s) noexcept { rt::mov_s(c, d, s); }
    bool cond() const noexcept { return rt::cop1_cond(c); }

    void mula_s(unsigned s, unsigned t) noexcept { rt::mula_s(c, s, t); }
    void madda_s(unsigned s, unsigned t) noexcept { rt::madda_s(c, s, t); }
    void madd_s(unsigned d, unsigned s, unsigned t) noexcept { rt::madd_s(c, d, s, t); }
    void sqrt_s(unsigned d, unsigned t) noexcept { rt::sqrt_s(c, d, t); }
    void abs_s(unsigned d, unsigned s) noexcept { rt::abs_s(c, d, s); }

    // HI/LO (the EE three-operand form: rd = LO)
    void mult(Gpr d, const Gpr& s, const Gpr& t) noexcept { rt::mult(c, d.r, s.r, t.r); }
    void divu(const Gpr& s, const Gpr& t) noexcept { rt::divu(c, s.r, t.r); }
    void div(const Gpr& s, const Gpr& t) noexcept { rt::div(c, s.r, t.r); }
    void mflo(Gpr d) noexcept { rt::mflo(c, d.r); }

    // `jal fn` at pc ($ra = pc + 8) through the callee's generated entry point
    void jal(u32 pc, rt::Fn fn) {
        rt::jal(c, pc);
        fn(c);
    }

    // The prologue `addiu sp, sp, -size; sd ra, ra_off(sp); sq r, ra_off - 16 (sp) ...` (registers in the order given)
    // and the epilogue's reloads with `addiu sp, sp, size`. ra_off < 0: a leaf frame without $ra.
    void prologue(u32 size, s32 ra_off, std::initializer_list<Gpr> regs) noexcept {
        sp = addiu(sp, -static_cast<s32>(size));
        if (ra_off >= 0) sd(sp, ra_off, ra);
        s32 slot = ra_off;
        for (const Gpr& r : regs) sq(r, sp, slot -= 16);
    }
    void epilogue(u32 size, s32 ra_off, std::initializer_list<Gpr> regs) noexcept {
        if (ra_off >= 0) ra = ld(sp, ra_off);
        s32 slot = ra_off;
        for (Gpr r : regs) lq(r, sp, slot -= 16);
        sp = addiu(sp, static_cast<s32>(size));
    }

    // `lw rd, 60(task)`: a kwln task's work pointer
    u64 work(u64 task) const noexcept { return lw(task, kTaskWork); }
};

// =====================================================================================================================
// Leaves without a route caller
// =====================================================================================================================

// =====================================================================================================================
// The transparent-wall fades (callbacks of the dungeon's wall control task, entered through its jalr table)
// =====================================================================================================================

// =====================================================================================================================
// The Tartarus floor generator: rotating a block descriptor
// =====================================================================================================================

// Cell (row, col) of the descriptor's 3 x 3 cell array (8 bytes each, four halfwords).

// =====================================================================================================================
// The per-frame Tartarus block culling (called by the opaque field draw task K_SceneDraw_UpdateDrwOpcFldTask)
// =====================================================================================================================

// A grid cell relative to the player's: the u16 block resource id of cell (x + dx, z + dz) lies at
// sField + 76 + 256 (z + dz) + 16 (x + dx); the code adds 256 z + 16 x to &sField and loads at this offset.
struct CellOffset {
    s8 dx, dz;
};
constexpr s32 cell_res_offset(CellOffset c) {
    return static_cast<s32>(kGridBase + kGridCellRes) + static_cast<s32>(kGridRow) * c.dz + static_cast<s32>(kGridCell) * c.dx;
}

// The cells drawn for each camera heading (the yaw of the main camera's frame in degrees, sub_1A5AA0): a wedge of 20
// or 21 cells opening away from the camera, in the original's order. `pc` is the first `jal K_Field_Get` of the run.
struct ViewWedge {
    u32 pc;
    unsigned n;
    CellOffset cells[21];
};
constexpr ViewWedge kViewWedges[8] = {
    // yaw in [-22.5, 22.5]: looking along +z
    {0x1BDAB4u, 21, {{-1, -1}, {0, -1}, {1, -1}, {-2, 0}, {-1, 0}, {0, 0}, {1, 0}, {2, 0}, {-2, 1}, {-1, 1}, {0, 1},
                     {1, 1}, {2, 1}, {-2, 2}, {-1, 2}, {0, 2}, {1, 2}, {2, 2}, {-1, 3}, {0, 3}, {1, 3}}},
    // (22.5, 67.5]: +x +z
    {0x1BDD94u, 20, {{0, 3}, {1, 3}, {-1, 2}, {0, 2}, {1, 2}, {2, 2}, {-1, 1}, {0, 1}, {1, 1}, {2, 1}, {3, 1},
                     {-1, 0}, {0, 0}, {1, 0}, {2, 0}, {3, 0}, {-1, -1}, {0, -1}, {1, -1}, {2, -1}}},
    // (67.5, 112.5]: +x
    {0x1BE054u, 21, {{-1, -1}, {-1, 0}, {-1, 1}, {0, -2}, {0, -1}, {0, 0}, {0, 1}, {0, 2}, {1, -2}, {1, -1}, {1, 0},
                     {1, 1}, {1, 2}, {2, -2}, {2, -1}, {2, 0}, {2, 1}, {2, 2}, {3, -1}, {3, 0}, {3, 1}}},
    // (112.5, 157.5]: +x -z
    {0x1BE32Cu, 20, {{-1, 1}, {0, 1}, {1, 1}, {2, 1}, {-1, 0}, {0, 0}, {1, 0}, {2, 0}, {3, 0}, {-1, -1}, {0, -1},
                     {1, -1}, {2, -1}, {3, -1}, {-1, -2}, {0, -2}, {1, -2}, {2, -2}, {0, -3}, {1, -3}}},
    // [-67.5, -22.5): -x +z
    {0x1BE5ECu, 20, {{0, 3}, {1, 3}, {1, 2}, {0, 2}, {-1, 2}, {-2, 2}, {1, 1}, {0, 1}, {-1, 1}, {-2, 1}, {-3, 1},
                     {1, 0}, {0, 0}, {-1, 0}, {-2, 0}, {-3, 0}, {-2, -1}, {-1, -1}, {0, -1}, {1, -1}}},
    // [-112.5, -67.5): -x
    {0x1BE8ACu, 21, {{1, -1}, {1, 0}, {1, 1}, {0, -2}, {0, -1}, {0, 0}, {0, 1}, {0, 2}, {-1, -2}, {-1, -1}, {-1, 0},
                     {-1, 1}, {-1, 2}, {-2, -2}, {-2, -1}, {-2, 0}, {-2, 1}, {-2, 2}, {-3, -1}, {-3, 0}, {-3, 1}}},
    // [-157.5, -112.5): -x -z
    {0x1BEB84u, 20, {{1, 1}, {0, 1}, {-1, 1}, {-2, 1}, {1, 0}, {0, 0}, {-1, 0}, {-2, 0}, {-3, 0}, {1, -1}, {0, -1},
                     {-1, -1}, {-2, -1}, {-3, -1}, {1, -2}, {0, -2}, {-1, -2}, {-2, -2}, {0, -3}, {1, -3}}},
    // the rest (|yaw| > 157.5, or NaN): looking along -z
    {0x1BEE14u, 21, {{-1, 1}, {0, 1}, {1, 1}, {-2, 0}, {-1, 0}, {0, 0}, {1, 0}, {2, 0}, {-2, -1}, {-1, -1}, {0, -1},
                     {1, -1}, {2, -1}, {-2, -2}, {-1, -2}, {0, -2}, {1, -2}, {2, -2}, {-1, -3}, {0, -3}, {1, -3}}},
};

// The f32 bounds of the heading tests (bit patterns: `lui v0, hi; mtc1 v0, $f1`), and the two gp constants of +-157.5
// (`lwc1 $f1, off($gp)`).
constexpr u32 kDeg22_5 = 0x41B4u, kDeg67_5 = 0x4287u, kDeg112_5 = 0x42E1u;
constexpr u32 kNeg22_5 = 0xC1B4u, kNeg67_5 = 0xC287u, kNeg112_5 = 0xC2E1u;
constexpr s32 kGpDeg157_5 = -31644, kGpNeg157_5 = -31640;

struct Culling : Cpu {
    using Cpu::Cpu;

    // `$f1 = bound; c.le.s / c.lt.s $f0, $f1`: the yaw (in $f0) against a bound; returns the condition bit.
    bool yaw_le(u32 hi) {
        v0 = lui(hi);
        mtc1(v0, 1);
        c_le_s(0, 1);
        return cond();
    }
    bool yaw_lt(u32 hi) {
        v0 = lui(hi);
        mtc1(v0, 1);
        c_lt_s(0, 1);
        return cond();
    }
    bool yaw_le_gp(s32 off) {
        lwc1(1, gp, off);
        c_le_s(0, 1);
        return cond();
    }
    bool yaw_lt_gp(s32 off) {
        lwc1(1, gp, off);
        c_lt_s(0, 1);
        return cond();
    }

    // The heading test chain (each wedge: a 6-cycle test of its first bound, then 6 -- or 4 for the gp bounds -- for
    // the second; the first test of wedge 0 belongs to the caller's block).
    unsigned pick_wedge() {
        if (yaw_le(kDeg22_5)) {
            charge(6);
            if (!yaw_lt(kNeg22_5)) return 0;
        }
        charge(6);
        if (!yaw_le(kDeg22_5)) {
            charge(6);
            if (yaw_le(kDeg67_5)) return 1;
        }
        charge(6);
        if (!yaw_le(kDeg67_5)) {
            charge(6);
            if (yaw_le(kDeg112_5)) return 2;
        }
        charge(6);
        if (!yaw_le(kDeg112_5)) {
            charge(4);
            if (yaw_le_gp(kGpDeg157_5)) return 3;
        }
        charge(6);
        if (yaw_lt(kNeg22_5)) {
            charge(6);
            if (!yaw_lt(kNeg67_5)) return 4;
        }
        charge(6);
        if (yaw_lt(kNeg67_5)) {
            charge(6);
            if (!yaw_lt(kNeg112_5)) return 5;
        }
        charge(6);
        if (yaw_lt(kNeg112_5)) {
            charge(4);
            if (!yaw_lt_gp(kGpNeg157_5)) return 6;
        }
        return 7;
    }

    // One wedge: one block (8 cycles per cell + 4) of `sub_1A0150(sField[cell].res, 1)` with &sField re-fetched through
    // K_Field_Get for every cell; $s3 / $s0 become 256 z / 16 x.
    void draw_wedge(const ViewWedge& wedge) {
        charge(8 * wedge.n + 4);
        s3 = sll(s3, 8);
        s0 = sll(s0, 4);
        u32 pc = wedge.pc;
        for (unsigned i = 0; i < wedge.n; ++i, pc += 0x20) {
            jal(pc, &gen::fn_K_Field_Get_001b9120);
            v0 = addu(v0, s3);
            v0 = addu(v0, s0);
            a0 = lhu(v0, cell_res_offset(wedge.cells[i]));
            a1 = si(1);
            jal(pc + 0x18, &gen::fn_sub_1A0150_001a0150);  // the draw flag of resource a0 on
        }
    }

    // 0x1BD950: on Tartarus floors (random, or the fixed majors 51..58 / 71..78) only the blocks around the player in
    // the camera's view are drawn. With the player's character resource (id 1024) present, every block (type 12)
    // loses the draw flag (+40 bit 1), the player's grid cell is stored (gp-0x4AA0 / gp-0x4A9C) and the view wedge of
    // the camera's heading gets the flag back; without it every block keeps the flag (the wedge of the last stored cell
    // is still set). The block parts (types 10 and 11) then copy their block's flag, and every live enemy unit's scene
    // resource gets it when sub_1C7160(unit, hero, 2000.0) says 1 (inf: within 2000 units of the hero).
    void sub_1BD950() {
        enter(11);
        prologue(80, 64, {s3, s2, s1, s0});
        jal(0x1BD968u, &gen::fn_K_Scene_IsRandomFloor_001a0250);
        v1 = si(1);
        if (v0 != v1) {
            charge(5);
            jal(0x1BD97Cu, &gen::fn_sub_1A02C0_001a02c0);  // [K_Scene_IsFixedTartarusFloor]
            v1 = si(1);
            if (v0 != v1) {
                charge(8);
                epilogue(80, 64, {s3, s2, s1, s0});
                return;
            }
        }
        charge(18);
        a0 = si(12);
        jal(0x1BD994u, &gen::fn_sub_3B5D50_003b5d50);  // MT_Scene_GetResListHead(12): the blocks
        s0 = v0;
        a0 = si(1024);
        jal(0x1BD9A4u, &gen::fn_sub_3B5D10_003b5d10);  // MT_Scene_GetRes(1024): the player's character
        s3 = v0;
        a0 = si(10);
        jal(0x1BD9B4u, &gen::fn_sub_3B5D50_003b5d50);
        s2 = v0;
        a0 = si(11);
        jal(0x1BD9C4u, &gen::fn_sub_3B5D50_003b5d50);
        s1 = v0;
        if (s3 != 0) {
            charge(11);
            a0 = lw(s3, kResController);
            jal(0x1BD9DCu, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
            sw(gp, kGpPlayerCellX, v0);
            a0 = lw(s3, kResController);
            jal(0x1BD9ECu, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
            sw(gp, kGpPlayerCellZ, v0);
            v1 = si(-3);
            for (;;) {  // every block: draw flag off
                charge(3);
                if (s0 == 0) break;
                backedge();
                charge(4);
                v0 = lw(s0, kResFlags);
                v0 = v0 & v1;
                sw(s0, kResFlags, v0);
                s0 = lw(s0, kResNext);
            }
            charge(5);
            a0 = si(12);
            jal(0x1BDA24u, &gen::fn_sub_3B5D50_003b5d50);  // (the result is not used)
        } else {
            for (;;) {  // every block: draw flag on
                charge(3);
                if (s0 == 0) break;
                backedge();
                charge(4);
                v0 = lw(s0, kResFlags);
                v0 = v0 | kResDrawFlag;
                sw(s0, kResFlags, v0);
                s0 = lw(s0, kResNext);
            }
            charge(3);
            a0 = si(12);
            jal(0x1BDA54u, &gen::fn_sub_3B5D50_003b5d50);
        }
        charge(14);
        s0 = lw(gp, kGpPlayerCellX);
        s3 = lw(gp, kGpPlayerCellZ);
        jal(0x1BDA64u, &gen::fn_sub_198590_00198590);  // kwlnGetMainCamera
        v0 = lw(v0, 4);
        a0 = addiu(v0, 16);                            // the camera frame's matrix
        jal(0x1BDA74u, &gen::fn_sub_1A5AA0_001a5aa0);  // its yaw in degrees -> $f0
        draw_wedge(kViewWedges[pick_wedge()]);

        // The block parts of type 10 follow their block (+256; none: unchanged).
        for (;;) {
            charge(2);
            if (s2 == 0) break;
            backedge();
            charge(3);
            v1 = lw(s2, kResParent);
            if (v1 != 0) {
                charge(4);
                v1 = lw(v1, kResFlags);
                v1 = v1 & kResDrawFlag;
                if (v1 != 0) {
                    charge(5);
                    v1 = lw(s2, kResFlags);
                    v1 = v1 | kResDrawFlag;
                    sw(s2, kResFlags, v1);
                } else {
                    charge(4);
                    a0 = lw(s2, kResFlags);
                    v1 = si(-3);
                    v1 = a0 & v1;
                    sw(s2, kResFlags, v1);
                }
            }
            charge(1);
            s2 = lw(s2, kResNext);
        }
        // Type 11 always has a block.
        charge(3);
        a0 = si(-3);
        for (;;) {
            charge(2);
            if (s1 == 0) break;
            backedge();
            charge(5);
            v1 = lw(s1, kResParent);
            v1 = lw(v1, kResFlags);
            v1 = v1 & kResDrawFlag;
            if (v1 != 0) {
                charge(5);
                v1 = lw(s1, kResFlags);
                v1 = v1 | kResDrawFlag;
                sw(s1, kResFlags, v1);
            } else {
                charge(3);
                v1 = lw(s1, kResFlags);
                v1 = v1 & a0;
                sw(s1, kResFlags, v1);
            }
            charge(1);
            s1 = lw(s1, kResNext);
        }
        // The enemies (gFldUnitsEc[24] with an encounter and a scene resource).
        charge(3);
        s0 = 0;
        for (;;) {
            charge(3);
            v1 = slti(s0, static_cast<s32>(kFldUnitsEcCount));
            if (v1 == 0) break;
            backedge();
            charge(9);
            v1 = sll(s0, 3);
            v1 = subu(v1, s0);
            a0 = sll(v1, 6);  // 448 i
            v1 = lui(0x87u);
            v1 = addiu(v1, -4704);  // gFldUnitsEc
            a0 = addu(v1, a0);
            v1 = lw(a0, kUnitEncounter);
            if (v1 != 0) {
                charge(4);
                s1 = addiu(a0, kUnitSceneRes);
                v1 = lw(a0, kUnitSceneRes);
                if (v1 != 0) {
                    charge(9);
                    v0 = lui(0x44FAu);  // 2000.0
                    mtc1(v0, 12);
                    a1 = lui(0x87u);
                    a1 = addiu(a1, 6048);  // gFldUnitsPc: the hero
                    jal(0x1BF1A4u, &gen::fn_sub_1C7160_001c7160);
                    v1 = si(1);
                    if (v0 == v1) {
                        charge(6);
                        a0 = lw(s1, 0);
                        v1 = lw(a0, kResFlags);
                        v1 = v1 | kResDrawFlag;
                        sw(a0, kResFlags, v1);
                    } else {
                        charge(5);
                        a1 = lw(s1, 0);
                        a0 = lw(a1, kResFlags);
                        v1 = si(-3);
                        v1 = a0 & v1;
                        sw(a1, kResFlags, v1);
                    }
                }
            }
            charge(1);
            s0 = addiu(s0, 1);
        }
        charge(8);
        epilogue(80, 64, {s3, s2, s1, s0});
    }
};

// =====================================================================================================================
// The field's scene variant by time of day and season (field root state 4: the sub-id of MT_Scene_Load)
// =====================================================================================================================

// A `major == M && minor == N` test of the field's compare chains, as compiled ($s0 = major, $s2 = minor, the constant
// in $v0): 3 cycles for the major, 3 for the minor (2 when N == M: $v0 already holds it); kAnyMinor: the major alone.
constexpr s32 kAnyMinor = -1;
struct SceneId {
    s32 major, minor;
};

// The jump table 0x7B6B00 of sub_1B6EB0, by datGetTime() (0..8): the code address of each case.
constexpr u32 kTimeCaseMidnight = 0x1B7484u;  // 0
constexpr u32 kTimeCaseDay = 0x1B7034u;       // 1..4: by season
constexpr u32 kTimeCaseAfterSchool = 0x1B73BCu;  // 5
constexpr u32 kTimeCaseEvening = 0x1B7468u;   // 6, 7
constexpr u32 kTimeCaseLateNight = 0x1B7490u; // 8

struct FieldChains : Cpu {
    using Cpu::Cpu;

    bool scene_is(SceneId id) {
        charge(3);
        v0 = si(id.major);
        if (id.minor == kAnyMinor) return s0 == v0;
        if (s0 != v0) return false;
        if (id.minor == id.major) {
            charge(2);
        } else {
            charge(3);
            v0 = si(id.minor);
        }
        return s2 == v0;
    }
    bool scene_in(std::initializer_list<SceneId> ids) {
        for (const SceneId& id : ids)
            if (scene_is(id)) return true;
        return false;
    }

    // clndIsDateInRange(m1, d1, m2, d2) == 1 in a block of `cycles` (8 or 9: the compiler reuses a register that
    // already holds the value); the 1 it compares with goes to `one` ($v1 or $a0).
    bool date_in(u64 cycles, u32 pc, s32 m1, s32 d1, s32 m2, s32 d2, Gpr one) {
        charge(cycles);
        a0 = si(m1);
        a1 = si(d1);
        a2 = si(m2);
        a3 = si(d2);
        jal(pc, &gen::fn_clndIsDateInRange_0017e480);
        one = si(1);
        return v0 == one;
    }
};

struct SceneVariant : FieldChains {
    using FieldChains::FieldChains;

    // The daytime variants (time 1..4) by season: +500 from 4/27 to 9/22 (6/13 -> 113), +600 to 12/3, +700 to the end
    // of February; nothing for 3/1..3/5 and 4/5..4/26.
    void daytime_by_season() {
        if (date_in(8, 0x1B7040u, 3, 1, 3, 5, v1) || date_in(9, 0x1B7064u, 4, 5, 4, 26, v1)) {
        } else if (date_in(9, 0x1B7088u, 4, 27, 9, 22, v1)) {
            charge(4);
            s3 = addiu(s3, 500);
            v0 = si(6);
            if (s0 == v0) {
                charge(3);
                v0 = si(13);
                if (s2 == v0) {
                    charge(3);
                    s3 = addiu(s2, 100);
                }
            }
        } else if (date_in(9, 0x1B70D4u, 9, 23, 12, 3, v1)) {
            charge(3);
            s3 = addiu(s3, 600);
        } else if (date_in(9, 0x1B7104u, 12, 4, 12, 31, a0) || date_in(8, 0x1B7124u, 1, 1, 2, 28, v1)) {
            charge(1);
            s3 = addiu(s3, 700);
        }
        // The fields that keep their daytime look from late April on.
        if (scene_in({{6, 4}, {6, 5}, {6, 7}, {6, 8}, {6, 21}, {6, 22}, {7, 1}, {7, 3}, {7, 4}, {7, 5}, {7, 6}, {7, 7},
                      {7, 14}, {7, 15}, {8, kAnyMinor}, {9, 3}, {9, 4}, {9, 5}, {9, 6}, {10, 2}, {14, 2}, {15, 1},
                      {16, 4}, {16, 5}})) {
            if (date_in(9, 0x1B737Cu, 4, 27, 12, 31, a0) || date_in(8, 0x1B739Cu, 1, 1, 2, 28, v1)) {
                charge(3);
                s3 = s2;
            }
        }
    }

    // 0x1B6EB0(major, minor) -> the scene sub-id of field major/minor at the current time (datGetTime; the month and
    // day are fetched first and not used): 6 for 15/6, 201 for field 1 and 33/1 at time 6, the minor itself for field 1
    // (otherwise), Tartarus (sub_1A01C0), majors >= 200 and the fixed Tartarus floors 20..28 / 40..48 with minor >= 50;
    // for the town fields minor + 400 (time 0), + the season's 500 / 600 / 700 (1..4), + 100 (5), + 200 (6, 7),
    // + 300 (8), with per-field exceptions keeping the minor, and field 4: minor + 200, + 300 with flag 728.
    void sub_1B6EB0() {
        enter(20);
        prologue(80, 64, {s3, s2, s1, s0});
        s0 = a0;
        s2 = a1 & 0xFFFFu;  // minor
        s3 = s2;            // the result being built
        jal(0x1B6ED4u, &gen::fn_clndGetCurrentMonth_0017d920);
        jal(0x1B6EDCu, &gen::fn_clndGetCurrentDay_0017da40);
        jal(0x1B6EE4u, &gen::fn_datGetTime_0016ef30);
        s1 = v0 & 0xFFu;    // time of day
        s0 = s0 & 0xFFFFu;  // major
        v0 = si(15);
        if (s0 == v0) {
            charge(3);
            v0 = si(6);
            if (s2 == v0) {
                charge(3);
                v0 = s2;  // 15/6 -> 6
                return finish();
            }
        }
        charge(3);
        v0 = si(1);
        if (s0 == v0) {
            charge(4);
            v1 = s1 & 0xFFu;
            v0 = si(6);
            if (v1 == v0) {
                charge(3);
                v0 = si(201);  // field 1 at time 6
                return finish();
            }
        }
        charge(3);
        v0 = si(1);
        if (s0 == v0) {
            charge(2);  // field 1: $v0 = 1 (the major) is returned
            return finish();
        }
        // The fixed Tartarus floors (majors 20..28 / 40..48 with minor >= 50) keep the minor.
        charge(3);
        v0 = slti(s0, 20);
        bool fixed_floor_major = false;
        if (v0 == 0) {
            charge(3);
            at = slti(s0, 29);
            fixed_floor_major = at != 0;
        }
        if (!fixed_floor_major) {
            charge(3);
            v0 = slti(s0, 40);
            if (v0 == 0) {
                charge(3);
                at = slti(s0, 49);
                fixed_floor_major = at != 0;
            }
        }
        if (fixed_floor_major) {
            charge(3);
            v0 = slti(s2, 50);
            if (v0 == 0) {
                charge(3);
                v0 = s2;
                return finish();
            }
        }
        charge(3);
        v0 = si(33);
        if (s0 == v0) {
            charge(3);
            v0 = si(1);
            if (s2 == v0) {
                charge(4);
                v1 = s1 & 0xFFu;
                v0 = si(6);
                if (v1 == v0) {
                    charge(3);
                    v0 = si(201);  // 33/1 at time 6
                    return finish();
                }
            }
        }
        charge(5);
        jal(0x1B6FD0u, &gen::fn_sub_1A01C0_001a01c0);  // [K_Scene_IsTartarus]
        a1 = si(1);
        if (v0 == a1) {
            charge(3);
            v0 = s2;
            return finish();
        }
        charge(3);
        v0 = slti(s0, 200);
        if (v0 == 0) {
            charge(3);
            v0 = s2;
            return finish();
        }
        // The town fields by time of day (jump table 0x7B6B00).
        charge(4);
        v0 = s1 & 0xFFu;
        at = sltiu(v0, 9);
        if (at != 0) {
            charge(7);
            v1 = lui(0x7Bu);
            v1 = addiu(v1, 27392);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            v0 = lw(v0, 0);
            switch (w(v0)) {
            case kTimeCaseDay:
                daytime_by_season();
                break;
            case kTimeCaseAfterSchool:
                charge(4);
                s3 = addiu(s3, 100);
                v0 = si(7);  // the major test of 7/14 shares the case's first block
                if ((s0 == v0 && (charge(3), v0 = si(14), s2 == v0)) ||
                    scene_in({{7, 15}, {8, kAnyMinor}, {9, 3}, {9, 4}, {9, 5}, {9, 6}})) {
                    charge(3);
                    s3 = s2;
                }
                break;
            case kTimeCaseEvening:
                charge(4);
                s3 = addiu(s3, 200);
                v0 = si(8);
                if (s0 == v0) {
                    charge(3);
                    s3 = s2;
                }
                break;
            case kTimeCaseMidnight:
                charge(3);
                s3 = addiu(s3, 400);
                break;
            case kTimeCaseLateNight:
                charge(1);
                s3 = addiu(s3, 300);
                break;
            default:  // (an indirect jump through a changed table entry)
                rt::lookup_func(w(v0))(c);
                return;
            }
        }
        // Fields that never change.
        if (scene_in({{6, 22}, {7, 10}, {7, 11}, {7, 12}, {7, 13}, {8, 3}, {9, 5}, {16, 4}, {16, 5}})) {
            charge(1);
            s3 = s2;
        }
        charge(3);
        v0 = si(4);
        if (s0 == v0) {
            charge(6);
            s3 = addiu(s2, 200);
            a0 = si(728);
            jal(0x1B7584u, &gen::fn_datGetFlag_0016f190);
            if (v0 != 0) {
                charge(1);
                s3 = addiu(s2, 300);
            }
        }
        charge(3);
        v0 = si(5);
        if (s0 == v0) {
            charge(1);
            s3 = s2;
        }
        charge(3);
        v0 = si(39);
        if (s0 == v0) {
            charge(1);
            s3 = s2;
        }
        charge(1);
        v0 = s3;
        finish();
    }
    void finish() {
        charge(8);
        epilogue(80, 64, {s3, s2, s1, s0});
    }
};

// =====================================================================================================================
// The field's BGM (field root states 10 / 15 / 16, the event task after a battle)
// =====================================================================================================================

// A floor threshold of the Tartarus BGM chains: floors >= `from` play `bgm`.
struct FloorBgm {
    s32 from, bgm;
    u32 pc;  // the `jal sub_1099D0` of the case
};
constexpr FloorBgm kFloorBgm[] = {
    {401, 70, 0x1A98ECu}, {400, 1, 0x1A9910u}, {290, 1, 0x1A9934u}, {255, 75, 0x1A9958u}, {215, 74, 0x1A997Cu},
    {165, 73, 0x1A99A0u}, {115, 72, 0x1A99C4u}, {65, 81, 0x1A99E8u}, {17, 70, 0x1A9A0Cu},  {2, 1, 0x1A9A30u},
};
constexpr FloorBgm kFloorBgmOther[] = {  // sub_17D800() != 0 (inf: the other scenario)
    {161, 100, 0x1A9A74u}, {131, 99, 0x1A9A98u}, {101, 98, 0x1A9ABCu}, {71, 97, 0x1A9AE0u},
    {41, 96, 0x1A9B04u},   {21, 95, 0x1A9B28u},  {2, 94, 0x1A9B4Cu},
};

struct Bgm : FieldChains {
    using FieldChains::FieldChains;

    // `sub_1099D0(bgm, 1)` (inf: play BGM `bgm`), in a block of `cycles`; `set_a1`: the block loads the 1 itself
    // (otherwise $a1 already holds it from the compare before).
    void play(u64 cycles, u32 pc, s32 bgm, bool set_a1) {
        charge(cycles);
        a0 = si(bgm);
        if (set_a1) a1 = si(1);
        jal(pc, &gen::fn_sub_1099D0_001099d0);
    }
    // `sub_108FD0(20)` (inf: fade the BGM out over 20 frames), a 5-cycle block.
    void fade_out(u32 pc) {
        charge(5);
        a0 = si(20);
        jal(pc, &gen::fn_sub_108FD0_00108fd0);
    }
    // `datGetFlag(id) == 1` in a 6-cycle block ($a1 = 1).
    bool flag_on(u32 pc, s32 id) {
        charge(6);
        a0 = si(id);
        jal(pc, &gen::fn_datGetFlag_0016f190);
        a1 = si(1);
        return v0 == a1;
    }
    // A minor test against the scene record in `rec`: `lw tmp, 4(rec); li v1, n` in a 4-cycle block.
    bool minor_is(Gpr rec, Gpr tmp, s32 n) {
        charge(4);
        tmp = lw(rec, 4);
        v1 = si(n);
        return tmp == v1;
    }
    // A major test `li v1, n; bne a2, v1` (3 cycles; $a2 = the major).
    bool major_is(s32 n) {
        charge(3);
        v1 = si(n);
        return a2 == v1;
    }

    // A threshold chain over the floor in $s0 (3 cycles per test; 6 for the play block).
    bool floor_chain(const FloorBgm* t, std::size_t n) {
        for (std::size_t i = 0; i < n; ++i) {
            charge(3);
            v1 = slti(s0, t[i].from);
            if (v1 == 0) {
                play(6, t[i].pc, t[i].bgm, true);
                return true;
            }
        }
        return false;
    }

    // In Tartarus (floor > 0): the counter sub_16F380(1) overrides from floor 2 on; else by floor (two tables).
    void tartarus_bgm() {
        charge(3);
        at = slti(s0, 2);
        if (at == 0) {
            charge(5);
            a0 = si(1);
            jal(0x1A9890u, &gen::fn_sub_16F380_0016f380);
            if (!lez(v0)) {
                charge(10);
                a0 = si(1);
                jal(0x1A98A4u, &gen::fn_sub_16F380_0016f380);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);  // (s16) counter
                a1 = si(1);
                jal(0x1A98B8u, &gen::fn_sub_1099D0_001099d0);
                return;
            }
        }
        charge(4);
        jal(0x1A98C8u, &gen::fn_sub_17D800_0017d800);
        if (v0 == 0) {
            if (floor_chain(kFloorBgm, std::size(kFloorBgm))) return;
            charge(2);
            if (!lez(s0)) play(6, 0x1A9A50u, 71, true);  // floor 1 (the entrance)
        } else {
            if (floor_chain(kFloorBgmOther, std::size(kFloorBgmOther))) return;
            charge(3);
            a1 = si(1);
            if (s0 == a1) play(5, 0x1A9B6Cu, 101, false);
        }
    }

    // Outside Tartarus: by scene (the record behind gp-0x57B0: +0 major, +4 minor), calendar and flags.
    void scene_bgm() {
        charge(5);
        a1 = lw(gp, kGpSceneIds);
        a0 = lw(a1, 0);
        // 7/6, 8/1, 9/1 at time 8: BGM 71
        bool night_field = false;
        v0 = si(7);
        if (a0 == v0) {
            charge(4);
            v1 = lw(a1, 4);
            v0 = si(6);
            night_field = v1 == v0;
        }
        if (!night_field) {
            charge(3);
            v0 = si(8);
            if (a0 == v0) {
                charge(4);
                v1 = lw(a1, 4);
                v0 = si(1);
                night_field = v1 == v0;
            }
        }
        if (!night_field) {
            charge(3);
            v0 = si(9);
            if (a0 == v0) {
                charge(4);
                v1 = lw(a1, 4);
                v0 = si(1);
                night_field = v1 == v0;
            }
        }
        if (night_field) {
            charge(6);
            jal(0x1A9BD8u, &gen::fn_datGetTime_0016ef30);
            v1 = v0 & 0xFFu;
            v0 = si(8);
            if (v1 == v0) return play(6, 0x1A9BF8u, 71, true);
        }
        if (flag_on(0x1A9C0Cu, 3584)) return play(5, 0x1A9C24u, 19, false);
        if (flag_on(0x1A9C38u, 3680)) return fade_out(0x1A9C50u);
        charge(5);
        v0 = lw(gp, kGpSceneIds);
        v1 = lw(v0, 0);
        v0 = si(31);
        if (v1 == v0) return play(5, 0x1A9C78u, 20, false);
        if (flag_on(0x1A9C8Cu, 3823)) return play(5, 0x1A9CA4u, 20, false);
        // by major ($a3 = the record, $a2 = the major)
        charge(5);
        a3 = lw(gp, kGpSceneIds);
        a2 = lw(a3, 0);
        v1 = si(33);
        if (a2 == v1) return fade_out(0x1A9CCCu);
        if (major_is(34)) return play(5, 0x1A9CECu, 22, false);
        if (major_is(35)) return play(5, 0x1A9D0Cu, 21, false);
        if (major_is(37)) return play(5, 0x1A9D2Cu, 71, false);
        if (major_is(14) && minor_is(a3, a0, 5)) return fade_out(0x1A9D5Cu);
        if ((major_is(8) && minor_is(a3, a0, 3)) || (major_is(5) && minor_is(a3, a0, 3)))
            return play(6, 0x1A9DACu, 54, true);
        if (major_is(8) && minor_is(a3, a0, 9)) return fade_out(0x1A9DDCu);
        if (major_is(7) && minor_is(a3, a0, 1)) {
            // 7/1 before time 2 or from time 7 on: fade out
            charge(6);
            jal(0x1A9E08u, &gen::fn_datGetTime_0016ef30);
            v0 = v0 & 0xFFu;
            at = slti(v0, 2);
            bool fade = at != 0;
            if (!fade) {
                charge(6);
                jal(0x1A9E20u, &gen::fn_datGetTime_0016ef30);
                v1 = v0 & 0xFFu;
                v1 = slti(v1, 7);
                fade = v1 == 0;
            }
            if (fade) return fade_out(0x1A9E3Cu);
        }
        charge(5);
        a3 = lw(gp, kGpSceneIds);
        a2 = lw(a3, 0);
        v1 = si(8);
        if ((a2 == v1 && minor_is(a3, a0, 2)) || (major_is(5) && minor_is(a3, a0, 2)))
            return play(6, 0x1A9E94u, 87, true);
        // the dorm-type majors 8, 9, 10, 12 and 7/9: by season
        bool seasonal = major_is(8);
        if (!seasonal) {
            charge(3);
            a0 = si(9);
            seasonal = a2 == a0;
        }
        if (!seasonal) seasonal = major_is(10) || major_is(12);
        if (!seasonal && major_is(7)) {
            charge(3);
            v1 = lw(a3, 4);
            seasonal = v1 == a0;  // minor 9
        }
        if (seasonal) {
            if (date_in(9, 0x1A9EFCu, 4, 5, 12, 31, a1) || date_in(8, 0x1A9F1Cu, 3, 1, 3, 5, a0))
                return play(6, 0x1A9F38u, 25, true);
            if (date_in(8, 0x1A9F54u, 1, 1, 2, 28, a1)) play(5, 0x1A9F6Cu, 80, false);
            return;
        }
        if (major_is(5)) {
            charge(4);
            v1 = lw(a3, 4);
            a1 = si(1);
            if (v1 == a1) return play(5, 0x1A9F9Cu, 25, false);
        }
        if (major_is(14)) return play(6, 0x1A9FC0u, 32, true);
        if (major_is(6)) {
            if (date_in(9, 0x1A9FECu, 4, 5, 8, 31, a1) || date_in(8, 0x1AA00Cu, 3, 1, 3, 5, a1))
                return play(6, 0x1AA028u, 50, true);
            if (date_in(8, 0x1AA044u, 9, 1, 12, 31, a1)) return play(5, 0x1AA05Cu, 51, false);
            if (date_in(8, 0x1AA078u, 1, 1, 2, 28, a1)) play(5, 0x1AA090u, 52, false);
            return;
        }
        if (major_is(7)) {
            if (date_in(9, 0x1AA0BCu, 4, 5, 12, 31, a1)) return play(5, 0x1AA0D4u, 53, false);
            if (date_in(8, 0x1AA0F0u, 1, 1, 2, 28, a1)) return play(5, 0x1AA108u, 77, false);
            if (date_in(8, 0x1AA124u, 3, 1, 3, 5, a1)) play(5, 0x1AA13Cu, 92, false);
            return;
        }
        if (major_is(4)) return play(6, 0x1AA160u, 77, true);
        if (major_is(39)) {
            charge(4);
            v1 = lw(a3, 4);
            a1 = si(1);
            if (v1 == a1) play(3, 0x1AA190u, 101, false);
        }
    }

    // 0x1A9850: the field's BGM on entering it. Nothing while gp-0x4AEC == 1. In Tartarus by floor (the entrance 71,
    // 2..16 BGM 1, 17..64 70, 65..114 81, 115.. 72 / 73 / 74 / 75 by block, 290..400 BGM 1, above 70; a counter
    // overrides), elsewhere by scene, season, time of day and story flags (3584 -> 19, 3680 -> fade out, 3823 -> 20).
    void sub_1A9850() {
        enter(7);
        prologue(32, 16, {s0});
        a0 = lw(gp, kGpFieldBgmSuppressed);
        v1 = si(1);
        if (a0 != v1) {
            charge(5);
            jal(0x1A986Cu, &gen::fn_K_FldDungeon_GetCurrentFloor_001bff20);
            s0 = v0;
            if (!lez(s0)) {
                tartarus_bgm();
            } else {
                scene_bgm();
            }
        }
        charge(5);
        epilogue(32, 16, {s0});
    }
};

// =====================================================================================================================
// The field's ambience loop on sound channel 4 (field root states 10 / 15 / 16)
// =====================================================================================================================

// The ENV_*.ADX file names (addresses 0x680000 + lo, `lui a1, 0x68; addiu a1, a1, lo`).
constexpr s32 kEnv001 = -3968, kEnv003 = -3840, kEnv004 = -3776, kEnv005 = -3712, kEnv007 = -3584, kEnv008 = -3520;
constexpr s32 kEnv010 = -3392, kEnv011 = -3328, kEnv050 = -3264, kEnv054 = -3200;

struct Ambience : FieldChains {
    using FieldChains::FieldChains;

    // `rec = *(gp-0x57B0); major = rec->major` (the 5-cycle head of each test group; it also holds the group's first
    // major compare).
    void load_scene(Gpr rec, Gpr major) {
        charge(5);
        rec = lw(gp, kGpSceneIds);
        major = lw(rec, 0);
    }
    // Any of the scenes (the constants in $v0, the minor loaded into $v1): 3 cycles per major test after the first,
    // 4 per minor test.
    bool scene_any(Gpr rec, Gpr major, std::initializer_list<SceneId> ids, bool first_in_head = true) {
        bool first = first_in_head;
        for (const SceneId& id : ids) {
            if (!first) charge(3);
            first = false;
            v0 = si(id.major);
            if (major != v0) continue;
            charge(4);
            v1 = lw(rec, 4);
            v0 = si(id.minor);
            if (v1 == v0) return true;
        }
        return false;
    }
    // `(u8) datGetTime() == t` in a 6-cycle block.
    bool time_is(u32 pc, s32 t) {
        charge(6);
        jal(pc, &gen::fn_datGetTime_0016ef30);
        v1 = v0 & 0xFFu;
        v0 = si(t);
        return v1 == v0;
    }
    // `sub_10A410(4, "ENV_xxx.ADX")` (inf: start the file on sound channel 4), a 7-cycle block.
    void start(u32 pc, s32 file) {
        charge(7);
        a0 = si(4);
        a1 = lui(0x68u);
        a1 = addiu(a1, file);
        jal(pc, &gen::fn_sub_10A410_0010a410);
    }

    // The rules in order; the first that matches starts its file.
    void choose() {
        // School-route fields 6/1, 3, 4, 7, 11, 20 at times 1, 3, 5: ENV_001.
        if (scene_any(a1, a0, {{6, 1}, {6, 3}, {6, 4}, {6, 7}, {6, 11}, {6, 20}}) &&
            (time_is(0x1AA268u, 1) || time_is(0x1AA280u, 3) || time_is(0x1AA298u, 5)))
            return start(0x1AA2BCu, kEnv001);
        // 6/2, 5, 16 at times 5, 3 from 7/18 to 9/20 (summer): ENV_003.
        load_scene(a1, a0);
        if (scene_any(a1, a0, {{6, 2}, {6, 5}, {6, 16}}) && (time_is(0x1AA328u, 5) || time_is(0x1AA340u, 3)) &&
            date_in(9, 0x1AA368u, 7, 18, 9, 20, v1))
            return start(0x1AA388u, kEnv003);
        // 7/1 (the record in $a0, the major in $v1): times 4..7 on 9/18 -> ENV_007; time 4 in summer -> ENV_003;
        // time 7 -> ENV_008; time 1 -> ENV_005.
        load_scene(a0, v1);
        if (scene_any(a0, v1, {{7, 1}}) &&
            (time_is(0x1AA3BCu, 4) || time_is(0x1AA3D4u, 5) || time_is(0x1AA3ECu, 6) || time_is(0x1AA404u, 7)) &&
            date_in(9, 0x1AA42Cu, 9, 18, 9, 18, v1))
            return start(0x1AA44Cu, kEnv007);
        load_scene(a0, v1);
        if (scene_any(a0, v1, {{7, 1}}) && time_is(0x1AA480u, 4) && date_in(9, 0x1AA4A8u, 7, 18, 9, 20, v1))
            return start(0x1AA4C8u, kEnv003);
        load_scene(a0, v1);
        if (scene_any(a0, v1, {{7, 1}}) && time_is(0x1AA4FCu, 7)) return start(0x1AA520u, kEnv008);
        load_scene(a0, v1);
        if (scene_any(a0, v1, {{7, 1}}) && time_is(0x1AA554u, 1)) return start(0x1AA578u, kEnv005);
        // 7/9, 9/1, 9/2, 9/7, 12/1 at times 5, 4 in summer: ENV_003.
        load_scene(a1, a0);
        if (scene_any(a1, a0, {{7, 9}, {9, 1}, {9, 2}, {9, 7}, {12, 1}}) &&
            (time_is(0x1AA61Cu, 5) || time_is(0x1AA634u, 4)) && date_in(9, 0x1AA65Cu, 7, 18, 9, 20, v1))
            return start(0x1AA67Cu, kEnv003);
        // 6/2, 6/16, 7/9, 12/1 at times 4..7 from 10/16 to 11/25: ENV_004.
        load_scene(a1, a0);
        if (scene_any(a1, a0, {{6, 2}, {6, 16}, {7, 9}, {12, 1}}) &&
            (time_is(0x1AA704u, 5) || time_is(0x1AA71Cu, 4) || time_is(0x1AA734u, 6) || time_is(0x1AA74Cu, 7)) &&
            date_in(9, 0x1AA774u, 10, 16, 11, 25, v1))
            return start(0x1AA794u, kEnv004);
        // Major 6 with flag 3680: ENV_008.
        load_scene(v0, v1);
        v0 = si(6);
        if (v1 == v0) {
            charge(6);
            a0 = si(3680);
            jal(0x1AA7BCu, &gen::fn_datGetFlag_0016f190);
            v1 = si(1);
            if (v0 == v1) return start(0x1AA7DCu, kEnv008);
        }
        // 14/1 ENV_050, 14/5 ENV_011, 33/1 ENV_010, other 33 ENV_054.
        load_scene(a1, a0);
        if (scene_any(a1, a0, {{14, 1}})) return start(0x1AA81Cu, kEnv050);
        if (scene_any(a1, a0, {{14, 5}}, false)) return start(0x1AA854u, kEnv011);
        if (scene_any(a1, a0, {{33, 1}}, false)) return start(0x1AA88Cu, kEnv010);
        charge(3);
        v0 = si(33);
        if (a0 == v0) return start(0x1AA8B4u, kEnv054);
        // Nothing: `sub_109F60(4, 0)` (inf: stop channel 4).
        charge(4);
        a0 = si(4);
        a1 = 0;
        jal(0x1AA8CCu, &gen::fn_sub_109F60_00109f60);
    }

    // 0x1AA1B0: the field's ambience on entering it (sound channel 4): the school / dorm / town fields by time of day
    // and season (ENV_001..ENV_008, the summer insects ENV_003 from 7/18 to 9/20), 14/1, 14/5, 33/1, 33/*; else
    // channel 4 stops.
    void sub_1AA1B0() {
        enter(7);
        prologue(16, 0, {});
        a1 = lw(gp, kGpSceneIds);
        a0 = lw(a1, 0);
        choose();
        charge(4);
        epilogue(16, 0, {});
    }
};

// =====================================================================================================================
// The Tartarus floor generator: fitting a block on the grid (sub_1BCAC0)
// =====================================================================================================================

// The door bits of a cell's door byte (descriptor cell +0 / grid cell +11): open towards -z, -x, +z, +x.

// =====================================================================================================================
// The collision controller (52-byte work, 26_field.md 4.2): position, grid cell, turning, the collision mesh
// =====================================================================================================================

// Collision controller work: +16 the model, +44 / +48 the grid cell (x, z).
constexpr s32 kCtlModel = 16, kCtlGridX = 44, kCtlGridZ = 48;
// sField +4460: the field's collision record (+0 bit 0: an RW collision world at +12; else the mesh at +8).
constexpr s32 kFieldCollision = 4460;
// gp-0x4A64: the live shadow count (26_field.md 6.4).

struct Controller : Cpu {
    using Cpu::Cpu;

    // `mdlGetMatrix(model)` -> $v0; the position row (+48 / +52 / +56) into $f2 / $f1 / $f0.
    void model_position(u32 pc) {
        jal(pc, &gen::fn_sub_318B60_00318b60);
        lwc1(2, v0, 48);
        lwc1(1, v0, 52);
        lwc1(0, v0, 56);
    }

    // 0x1AD940(out, task): out = the controller's model position, or (0, 0, 0) without a model (the 12-byte vector
    // at sp+32 is cleared byte by byte first: the inlined memset).
    void sub_1AD940() {
        enter(9);
        prologue(48, 16, {s0});
        s0 = a0;
        a1 = work(a1);
        a0 = addiu(sp, 32);
        v1 = si(12);
        if (a0 != 0) {
            do {
                charge(7);
                sb(a0, 0, zero);
                a0 = addiu(a0, 1);
                v1 = addiu(v1, -1);
                if (v1 == 0) break;
                backedge();
            } while (true);
        }
        charge(3);
        a0 = lw(a1, kCtlModel);
        if (a0 != 0) {
            charge(8);
            model_position(0x1AD98Cu);
            swc1(2, sp, 32);
            swc1(1, sp, 36);
            swc1(0, sp, 40);
        }
        charge(11);
        lwc1(2, sp, 32);
        lwc1(1, sp, 36);
        lwc1(0, sp, 40);
        swc1(2, s0, 0);
        swc1(1, s0, 4);
        swc1(0, s0, 8);
        epilogue(48, 16, {s0});
    }

    // (int)((coordinate + 400) / 800) of the model's position row (+off) into `cell` through `tmp`.
    void grid_coordinate(u32 pc, s32 off, Gpr tmp, s32 cell) {
        a0 = lw(s0, kCtlModel);
        jal(pc, &gen::fn_sub_318B60_00318b60);
        lwc1(1, v0, off);
        tmp = lui(0x43C8u);  // 400.0
        mtc1(tmp, 0);
        add_s(1, 0, 1);
        tmp = lui(0x4448u);  // 800.0
        mtc1(tmp, 0);
        div_s(0, 1, 0);
        cvt_w_s(0, 0);
        mfc1(tmp, 0);
        sw(s0, cell, tmp);
    }
    // 0x1ADD40(task): the controller's grid cell from its model's position (800-unit cells, origin at the world origin).
    void sub_1ADD40() {
        enter(41);
        prologue(32, 16, {s0});
        s0 = work(a0);
        grid_coordinate(0x1ADD54u, 48, v0, kCtlGridX);
        grid_coordinate(0x1ADD94u, 56, v1, kCtlGridZ);
        epilogue(32, 16, {s0});
    }

    // 0x1ADFF0(task, axis, $f12 angle): turns the controller's model in place: translate by -position,
    // sub_318A50(model, axis, angle, 2) (inf: rotate), translate back (sub_318A30(model, &vec, 2): mdlTranslate).
    // The position and its negation sit at sp+80 / sp+64; $f20 keeps the angle across the calls.
    void sub_1ADFF0() {
        enter(11);
        sp = addiu(sp, -96);
        sd(sp, 48, ra);
        sq(s1, sp, 32);
        sq(s0, sp, 16);
        swc1(20, sp, 0);
        s1 = a1;
        mov_s(20, 12);
        s0 = work(a0);
        a0 = lw(s0, kCtlModel);
        if (a0 != 0) {
            charge(35);
            model_position(0x1AE01Cu);
            swc1(2, sp, 80);
            swc1(1, sp, 84);
            swc1(0, sp, 88);
            v0 = lui(0xBF80u);  // -1.0
            mtc1(v0, 1);
            for (s32 i = 0; i < 3; ++i) {
                lwc1(0, sp, 80 + 4 * i);
                mul_s(0, 1, 0);
                swc1(0, sp, 64 + 4 * i);
            }
            a0 = lw(s0, kCtlModel);
            a1 = addiu(sp, 64);
            a2 = si(2);
            jal(0x1AE074u, &gen::fn_sub_318A30_00318a30);
            a0 = lw(s0, kCtlModel);
            a1 = s1;
            mov_s(12, 20);
            a2 = si(2);
            jal(0x1AE08Cu, &gen::fn_sub_318A50_00318a50);
            a0 = lw(s0, kCtlModel);
            a1 = addiu(sp, 80);
            a2 = si(2);
            jal(0x1AE0A0u, &gen::fn_sub_318A30_00318a30);
        }
        charge(7);
        ra = ld(sp, 48);
        lq(s1, sp, 32);
        lq(s0, sp, 16);
        lwc1(20, sp, 0);
        sp = addiu(sp, 96);
    }

    // 0x1AC750(pos, step, resource id; $f12): the collision mesh for a move, then the collision itself (still
    // recompiled): with an RW collision world (field record bit 0) sub_1AB390(world, pos, step, $f12); otherwise
    // sub_1ABD20(mesh, pos, step, id, $f12) with the mesh of the block under the mover on Tartarus floors (random, or
    // majors 51..78: the grid cell of the resource's controller -- +480 for characters (type 1), +488 otherwise -- names
    // the block, the first type-12 resource with that id gives +352 -> +8), else the field's own mesh. $f20 keeps $f12.
    void K_FldFrame_HandleCollis() {
        enter(21);
        prologue(144, 128, {s6, s5, s4, s3, s2, s1, s0});
        swc1(20, sp, 0);
        s2 = a0;
        s1 = a1;
        mov_s(20, 12);
        s0 = a2;
        jal(0x1AC788u, &gen::fn_K_Field_Get_001b9120);
        v0 = lw(v0, kFieldCollision);
        v0 = lw(v0, 0);
        v0 = v0 & 1u;
        if (v0 != 0) {
            charge(11);
            jal(0x1AC7A4u, &gen::fn_K_Field_Get_001b9120);
            v0 = lw(v0, kFieldCollision);
            a0 = lw(v0, 12);
            a1 = s2;
            a2 = s1;
            mov_s(12, 20);
            jal(0x1AC7C0u, &gen::fn_sub_1AB390_001ab390);
        } else {
            charge(6);
            s5 = 0;  // the mesh
            jal(0x1AC7D4u, &gen::fn_K_Scene_IsRandomFloor_001a0250);
            v1 = si(1);
            bool tartarus = v0 == v1;
            if (!tartarus) {
                charge(5);
                v0 = lw(gp, kGpSceneIds);
                v1 = lw(v0, 0);
                v0 = slti(v1, 51);
                if (v0 == 0) {
                    charge(3);
                    at = slti(v1, 79);
                    tartarus = at != 0;
                }
            }
            if (tartarus) {
                charge(15);
                a0 = si(12);
                jal(0x1AC80Cu, &gen::fn_sub_3B5D50_003b5d50);  // the blocks
                s4 = v0;
                a0 = s0;
                jal(0x1AC81Cu, &gen::fn_sub_3B5D10_003b5d10);  // the mover's resource
                a0 = s0 & 0xFFFFu;
                v1 = lui(0xFu);
                v1 = v1 | 0xFC00u;
                v1 = a0 & v1;
                a0 = sra(v1, 10);  // the resource type
                v1 = si(1);
                const bool character = a0 == v1;
                const s32 ctl = character ? 480 : 488;
                charge(character ? 11 : 9);
                s6 = addiu(v0, ctl);
                a0 = lw(v0, ctl);
                jal(character ? 0x1AC84Cu : 0x1AC878u, &gen::fn_K_FldFrame_CtlGetXGrid_001ad910);
                s3 = v0;
                a0 = lw(s6, 0);
                jal(character ? 0x1AC85Cu : 0x1AC888u, &gen::fn_K_FldFrame_CtlGetZGrid_001ad920);
                s6 = v0;
                charge(9);
                jal(0x1AC894u, &gen::fn_K_Field_Get_001b9120);
                v1 = sll(s6, 8);
                v1 = addu(v0, v1);
                v0 = sll(s3, 4);
                v0 = addu(v1, v0);
                v1 = lhu(v0, static_cast<s32>(kGridBase + kGridCellRes));  // the cell's block id
                for (;;) {
                    charge(2);
                    if (s4 == 0) {
                        charge(2);
                        break;
                    }
                    backedge();
                    charge(3);
                    v0 = lhu(s4, 0);
                    if (v0 == v1) {
                        charge(4);
                        v0 = lw(s4, 352);
                        s5 = lw(v0, 8);
                        break;
                    }
                    charge(1);
                    s4 = lw(s4, kResNext);
                }
            } else {
                charge(4);
                jal(0x1AC8E8u, &gen::fn_K_Field_Get_001b9120);
                v0 = lw(v0, kFieldCollision);
                s5 = lw(v0, 8);
            }
            charge(7);
            a0 = s5;
            a1 = s2;
            a2 = s1;
            mov_s(12, 20);
            a3 = s0;
            jal(0x1AC90Cu, &gen::fn_sub_1ABD20_001abd20);
        }
        charge(12);
        lwc1(20, sp, 0);
        epilogue(144, 128, {s6, s5, s4, s3, s2, s1, s0});
    }
};

// =====================================================================================================================
// Small field helpers on the event / camera / virtual-pad side
// =====================================================================================================================

struct FieldMisc : Cpu {
    using Cpu::Cpu;

    // 0x1C7130(unit; $f12 distance): sub_1C7160(unit, the hero gFldUnitsPc[0], $f12) (inf: within the distance).
    void sub_1C7130() {
        enter(10);
        prologue(16, 0, {});
        a1 = lui(0x87u);
        a1 = addiu(a1, 6048);  // gFldUnitsPc
        jal(0x1C7140u, &gen::fn_sub_1C7160_001c7160);
        epilogue(16, 0, {});
    }

    // 0x1D5140(camera controller task) -> the index (0..8) of the camera point nearest the player (work +96 + 12 i,
    // nine f32 triples; the player's position from its controller, resource work +204 -> +480), starting from the
    // distance gp-0x7DF4; when none is nearer, the caller's $s1 is returned as it was. sqrtf((dy dy + dx dx) + dz dz)
    // through ACC, as compiled.
    void sub_1D5140() {
        enter(23);
        prologue(80, 32, {s1, s0});
        s0 = work(a0);
        v0 = lw(s0, 204);
        a0 = addiu(sp, 48);
        a1 = lw(v0, kResController);
        jal(0x1D5160u, &gen::fn_sub_1AD940_001ad940);  // the player's position
        lwc1(2, sp, 48);
        lwc1(1, sp, 52);
        lwc1(0, sp, 56);
        swc1(2, sp, 64);
        swc1(1, sp, 68);
        swc1(0, sp, 72);
        lwc1(6, gp, -32244);  // the best distance so far
        v1 = 0;
        lwc1(5, sp, 68);  // y
        lwc1(4, sp, 72);  // z
        lwc1(3, sp, 64);  // x
        for (;;) {
            charge(3);
            v0 = slti(v1, 9);
            if (v0 == 0) break;
            backedge();
            charge(19);
            v0 = sll(v1, 1);
            v0 = addu(v0, v1);
            v0 = sll(v0, 2);
            v0 = addu(s0, v0);
            lwc1(0, v0, 96);
            sub_s(2, 0, 3);
            lwc1(0, v0, 100);
            sub_s(1, 0, 5);
            lwc1(0, v0, 104);
            sub_s(0, 0, 4);
            mula_s(1, 1);
            madda_s(2, 2);
            madd_s(0, 0, 0);
            sqrt_s(0, 0);
            c_le_s(6, 0);
            if (!cond()) {
                charge(2);
                mov_s(6, 0);
                s1 = v1;
            }
            charge(1);
            v1 = addiu(v1, 1);
        }
        charge(7);
        v0 = s1;
        epilogue(80, 32, {s1, s0});
    }

    // 0x1E13F0: the virtual pad's "rotate" task body (work +64 active, +68 the controller task, +84 f32 the step angle,
    // +88 frames done, +92 frames): while active, turns the controller by the step about the axis 0x683DA0 (copied to
    // sp+32) each frame (sub_1ADFF0); when done, sub_1AD9E0(controller, work), sub_1CD650(sField.event, 0) and inactive.
    // Returns 0.
    void sub_1E13F0() {
        enter(15);
        prologue(48, 16, {s0});
        s0 = work(a0);
        a1 = addiu(sp, 32);
        v0 = lui(0x68u);
        v1 = ld(v0, 15776);
        v0 = lui(0x68u);
        lwc1(0, v0, 15784);
        sd(sp, 32, v1);
        swc1(0, sp, 40);
        v1 = lw(s0, 64);
        v0 = si(1);
        if (v1 != v0) {
            charge(2);
            if (v1 != 0) charge(2);  // (state 0 and any other state end alike, through one more block)
        } else {
            charge(12);
            v0 = lw(s0, 88);
            v0 = addiu(v0, 1);
            sw(s0, 88, v0);
            a0 = lw(s0, 68);
            lwc1(12, s0, 84);
            jal(0x1E1450u, &gen::fn_sub_1ADFF0_001adff0);
            v1 = lw(s0, 88);
            v0 = lw(s0, 92);
            v0 = slt(v1, v0);
            if (v0 == 0) {
                charge(11);
                a0 = lw(s0, 68);
                a1 = s0;
                jal(0x1E1474u, &gen::fn_sub_1AD9E0_001ad9e0);
                jal(0x1E147Cu, &gen::fn_K_Field_Get_001b9120);
                a0 = lw(v0, 8);  // the field event task
                a1 = 0;
                jal(0x1E148Cu, &gen::fn_sub_1CD650_001cd650);
                sw(s0, 64, zero);
            }
        }
        charge(6);
        v0 = 0;
        epilogue(48, 16, {s0});
    }
};

// =====================================================================================================================
// The enemy pop scheduler's helpers (K_Unit_UpdateEnemyPopSchedulerTask, 26_field.md 6.4)
// =====================================================================================================================

// =====================================================================================================================
// Field hits (scene resources of type 13: a quad at +284 / +296 / +308 / +320, 26_field.md 5.2)
// =====================================================================================================================

struct FieldHits : Cpu {
    using Cpu::Cpu;

    // `point.y` (f32 at base + off) within (corner0.y - 100, corner0.y + 100): the first corner through the triangle
    // pointers at sp+tris. A 10-cycle block, then 4.
    bool height_within(s32 tris, Gpr base, s32 off) {
        charge(10);
        v0 = lw(sp, tris);
        lwc1(3, v0, 4);
        lwc1(2, base, off);
        v0 = lui(0x42C8u);  // 100.0
        mtc1(v0, 1);
        add_s(0, 1, 3);
        c_lt_s(2, 0);
        if (!cond()) return false;
        charge(4);
        sub_s(0, 3, 1);
        c_le_s(2, 0);
        return !cond();
    }
    // The triangle (c0, c1, c2) of the quad in $s0 as three pointers at sp+tris, then
    // K_FldFrame_IsPointInTriangle(a0, &tris, a2 = &normal) == 1 ($v1 = 1).
    bool triangle_hit(u32 pc, s32 tris, s32 c0, s32 c1, s32 c2) {
        v0 = addiu(s0, c0);
        sw(sp, tris, v0);
        v0 = addiu(s0, c1);
        sw(sp, tris + 4, v0);
        v0 = addiu(s0, c2);
        sw(sp, tris + 8, v0);
        a1 = addiu(sp, tris);
        jal(pc, &gen::fn_K_FldFrame_IsPointInTriangle_001aaad0);
        v1 = si(1);
        return v0 == v1;
    }
    // The normal (0x680000 + lo, 12 bytes) copied to sp+normal, a2 = &it.
    void copy_normal(s32 normal, s32 lo) {
        a2 = addiu(sp, normal);
        v0 = lui(0x68u);
        v1 = ld(v0, lo);
        v0 = lui(0x68u);
        lwc1(0, v0, lo + 8);
        sd(sp, normal, v1);
        swc1(0, sp, normal + 8);
    }

    // 0x1C5EE0 K_FldEvent_FindFldHitAt(point, &res) -> the u16 id of the first field hit whose quad (two triangles,
    // normal (0, 1, 0) at 0x6836C0) lies under the point within +-100 in height, the resource in *res; 0xFFFF for none
    // and on random floors.
    void K_FldEvent_FindFldHitAt() {
        enter(19);
        prologue(112, 64, {s3, s2, s1, s0});
        s3 = a0;
        s2 = a1;
        v0 = zero | 0xFFFFu;
        s1 = v0 & 0xFFFFu;  // the result: none
        a0 = si(13);
        jal(0x1C5F0Cu, &gen::fn_sub_3B5D50_003b5d50);  // the field hits
        s0 = v0;
        jal(0x1C5F18u, &gen::fn_K_Scene_IsRandomFloor_001a0250);
        v1 = si(1);
        if (v0 == v1) {
            charge(3);
            v0 = zero | 0xFFFFu;
            return finish_hit();
        }
        for (;;) {
            charge(2);
            if (s0 == 0) break;
            backedge();
            charge(20);
            copy_normal(80, 14016);
            a0 = s3;
            bool hit = triangle_hit(0x1C5F74u, 96, 284, 296, 308) && height_within(96, s3, 4);
            if (!hit) {
                charge(14);
                a0 = s3;
                a2 = addiu(sp, 80);
                hit = triangle_hit(0x1C5FF4u, 96, 296, 308, 320) && height_within(96, s3, 4);
            }
            if (hit) {
                charge(4);
                s1 = lhu(s0, 0);
                sw(s2, 0, s0);
                break;
            }
            charge(1);
            s0 = lw(s0, kResNext);
        }
        charge(1);
        v0 = s1;
        finish_hit();
    }
    void finish_hit() {
        charge(8);
        epilogue(112, 64, {s3, s2, s1, s0});
    }

    // 0x1C7B30 K_FldEvent_IsUnitNearFldHit(unit) -> 1 when the unit's model position (+80) lies over a field hit quad
    // within +-100 in height (normal 0x6836E0); only on random floors (0 elsewhere).
    void K_FldEvent_IsUnitNearFldHit() {
        enter(15);
        prologue(112, 48, {s2, s1, s0});
        s2 = a0;
        s1 = 0;
        a0 = si(13);
        jal(0x1C7B50u, &gen::fn_sub_3B5D50_003b5d50);
        s0 = v0;
        jal(0x1C7B5Cu, &gen::fn_K_Scene_IsRandomFloor_001a0250);
        if (v0 == 0) {
            charge(3);
            v0 = 0;
            return finish_near();
        }
        charge(11);
        a0 = lw(s2, 80);
        jal(0x1C7B7Cu, &gen::fn_sub_318B60_00318b60);  // mdlGetMatrix: the position row to sp+96
        lwc1(2, v0, 48);
        lwc1(1, v0, 52);
        lwc1(0, v0, 56);
        swc1(2, sp, 96);
        swc1(1, sp, 100);
        swc1(0, sp, 104);
        for (;;) {
            charge(2);
            if (s0 == 0) break;
            backedge();
            charge(20);
            copy_normal(64, 14048);
            a0 = addiu(sp, 96);
            bool hit = triangle_hit(0x1C7BE0u, 80, 284, 296, 308) && height_within(80, sp, 100);
            if (!hit) {
                charge(14);
                a0 = addiu(sp, 96);
                a2 = addiu(sp, 64);
                hit = triangle_hit(0x1C7C5Cu, 80, 296, 308, 320) && height_within(80, sp, 100);
            }
            if (hit) {
                charge(3);
                s1 = v1;  // 1
                break;
            }
            charge(1);
            s0 = lw(s0, kResNext);
        }
        charge(1);
        v0 = s1;
        finish_near();
    }
    void finish_near() {
        charge(7);
        epilogue(112, 48, {s2, s1, s0});
    }
};

// =====================================================================================================================
// Shadow spawning (k_unit.c)
// =====================================================================================================================

struct Spawner : Cpu {
    using Cpu::Cpu;

    // 0x1D0720(n) -> the shadows placed: none with flag 5141 or on the fixed Tartarus floors 20..28 / 40..48 with a
    // minor; otherwise while sub_1D0880(i, n) yields a spawn slot, the encounter sub_1D7300(major, minor, floor) (on
    // Thebel, field 51/1: encounter 466 + i with bit 16) -- 0xFFFF asserts (k_unit.c 1404) and becomes 1 -- goes to
    // sub_1CF940(encounter, slot).
    void sub_1D0720() {
        enter(14);
        prologue(80, 64, {s3, s2, s1, s0});
        s2 = a0;
        s0 = 0;  // placed
        a0 = si(5141);
        jal(0x1D0744u, &gen::fn_datGetFlag_0016f190);
        v1 = si(1);
        if (v0 == v1) {
            charge(3);
            v0 = 0;
            return finish();
        }
        charge(5);
        a0 = lw(gp, kGpSceneIds);
        v1 = lw(a0, 0);
        v0 = slti(v1, 20);
        bool fixed_major = false;
        if (v0 == 0) {
            charge(3);
            at = slti(v1, 29);
            fixed_major = at != 0;
        }
        if (!fixed_major) {
            charge(3);
            v0 = slti(v1, 40);
            if (v0 == 0) {
                charge(3);
                at = slti(v1, 49);
                fixed_major = at != 0;
            }
        }
        if (fixed_major) {
            charge(3);
            v0 = lw(a0, 4);
            if (v0 != 0) {
                charge(3);
                v0 = 0;
                return finish();
            }
        }
        for (;;) {
            charge(7);
            a0 = s0;
            a1 = s2;
            jal(0x1D0848u, &gen::fn_sub_1D0880_001d0880);  // the next spawn slot, or 0
            s1 = v0;
            if (v0 == 0) break;
            backedge();
            charge(13);
            s3 = lw(gp, kGpSceneIds);
            jal(0x1D07B8u, &gen::fn_K_FldDungeon_GetCurrentFloor_001bff20);
            a2 = v0 & 0xFFFFu;
            a0 = lhu(s3, 0);
            a1 = lhu(s3, 4);
            jal(0x1D07CCu, &gen::fn_sub_1D7300_001d7300);  // the floor's encounter
            a1 = lw(gp, kGpSceneIds);
            a0 = lw(a1, 0);
            v1 = si(51);
            if (a0 == v1) {
                charge(4);
                a0 = lw(a1, 4);
                v1 = si(1);
                if (a0 == v1) {
                    charge(3);
                    v1 = addiu(s0, 466);
                    v0 = lui(0x1u);
                    v0 = v1 | v0;
                }
            }
            charge(4);
            a0 = v0 & 0xFFFFu;
            v1 = zero | 0xFFFFu;
            if (a0 == v1) {
                charge(6);
                a0 = lui(0x68u);
                a0 = addiu(a0, 14656);  // "k_unit.c"
                a1 = si(1404);
                jal(0x1D0820u, &gen::fn_sub_19D3F0_0019d3f0);  // K_Assert: `jr $ra` in retail
                v0 = si(1);
            }
            charge(5);
            a0 = v0;
            a1 = s1;
            jal(0x1D0834u, &gen::fn_sub_1CF940_001cf940);  // create the shadow
            s0 = addiu(s0, 1);
        }
        charge(1);
        v0 = s0;
        finish();
    }
    void finish() {
        charge(8);
        epilogue(80, 64, {s3, s2, s1, s0});
    }
};

// =====================================================================================================================
// The virtual pad's turn in place: starting the rotate task (K_VPad_UpdateTask)
// =====================================================================================================================

}  // namespace

// =====================================================================================================================
// Typed entry points (arguments as the whole caller registers; results as the original leaves them)
// =====================================================================================================================

namespace {
void set_args(EEContext& ctx, std::initializer_list<u64> args) {
    unsigned r = GPR_A0;
    for (u64 a : args) core::set_gpr64(ctx, r++, a);
}
u32 v0_of(const EEContext& ctx) { return core::gpr32(ctx, GPR_V0); }
}  // namespace

// 0x0019C2F0 sub_19C2F0 -- 16 bytes; leaf frame (no stack)
// 0x19C2F0: work +4 = $a1 ($v1 = the work).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_19C2F0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0019c2f0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    sw(a1, v1, 4);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_19C2F0(EEContext& ctx, u64 task, u64 value) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(value));
    sub_19C2F0(ctx);
}

// 0x0019C300 sub_19C300 -- 16 bytes; leaf frame (no stack)
// 0x19C300: $v0 = u16 work +10.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_19C300(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lhu, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0019c300
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    lhu(v0, v0, 10);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u32 sub_19C300(EEContext& ctx, u64 task) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    sub_19C300(ctx);
    return static_cast<u32>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x0019C310 sub_19C310 -- 16 bytes; leaf frame (no stack)
// 0x19C310: u16 work +10 = $a1.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_19C310(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sh;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0019c310
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    sh(a1, v1, 10);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_19C310(EEContext& ctx, u64 task, u64 value) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(value));
    sub_19C310(ctx);
}

// 0x0019C490 sub_19C490 -- 32 bytes; leaf frame (no stack)
// 0x19C490: $f0 = *(f32 *)(work +76), or 0.0 when that pointer is NULL ($v0 ends as the pointer).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_19C490(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::charge, hg::enter, hg::lw, hg::lwc1, hg::mtc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4};
    Fpr f0{ctx, 0};
    // 0x0019c490
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(v0, a0, 60);
    mtc1(zero, f0);
    lw(v0, v0, 76);
    if (v0 != 0) {
        // 0x0019c4a4
        charge(ctx, 1);
        lwc1(f0, v0, 0);
    }
    // 0x0019c4a8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u32 sub_19C490(EEContext& ctx, u64 task) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    sub_19C490(ctx);
    return static_cast<u32>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x001A4770 sub_1A4770 -- 16 bytes; leaf frame (no stack)
// 0x1A4770: the camera debug point's enable word, work +0 (sub_1D5C10 switches the three points).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1A4770(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001a4770
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    sw(a1, v1, 0);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_1A4770(EEContext& ctx, u64 task, u64 on) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(on));
    sub_1A4770(ctx);
}

// 0x001A4780 sub_1A4780 -- 36 bytes; leaf frame (no stack)
// 0x1A4780: the point's position, work +4..+12 = pos[0..2] (through $f2 / $f1 / $f0).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1A4780(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::enter, hg::lw, hg::lwc1, hg::swc1;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x001a4780
    enter(ctx, 9);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    lwc1(f2, a1, 0);
    lwc1(f1, a1, 4);
    lwc1(f0, a1, 8);
    swc1(f2, v1, 4);
    swc1(f1, v1, 8);
    swc1(f0, v1, 12);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_1A4780(EEContext& ctx, u64 task, u64 pos) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(pos));
    sub_1A4780(ctx);
}

// 0x001A47B0 sub_1A47B0 -- 44 bytes; leaf frame (no stack)
// 0x1A47B0: the point's colour, work +16..+19 = rgba[0..3] (through $a3 / $a2 / $a0 / $v1; $a4 = the work).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1A47B0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lbu, hg::lw, hg::sb;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x001a47b0
    enter(ctx, 11);  // entry check point + this block's cycles
    lw(t0, a0, 60);
    lbu(a3, a1, 0);
    lbu(a2, a1, 1);
    lbu(a0, a1, 2);
    lbu(v1, a1, 3);
    sb(a3, t0, 16);
    sb(a2, t0, 17);
    sb(a0, t0, 18);
    sb(v1, t0, 19);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_1A47B0(EEContext& ctx, u64 task, u64 rgba) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(rgba));
    sub_1A47B0(ctx);
}

// 0x001B01B0 sub_1B01B0 -- 32 bytes; leaf frame (no stack)
// 0x1B01B0: $v0 = &work->queue[i] = work + 32 + 24 i (the enemy-think action entries, field_lo.h).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1B01B0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::lw, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001b01b0
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = sll(a1, 1);
    v0 = addu(v0, a1);
    v1 = sll(v0, 3);
    lw(v0, a0, 60);
    v0 = addu(v0, v1);
    v0 = addiu(v0, 32);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u32 sub_1B01B0(EEContext& ctx, u64 task, u64 i) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(i));
    sub_1B01B0(ctx);
    return static_cast<u32>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x001B01D0 sub_1B01D0 -- 72 bytes; leaf frame (no stack)
// 0x1B01D0: work->queue[i] = 24 bytes of src, copied as three pairs of words (a do-while on $a1 = 3).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1B01D0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::i64, hg::lw, hg::sll, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x001b01d0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(a0, a0, 60);
    v1 = sll(a1, 1);
    v1 = addu(v1, a1);
    v1 = sll(v1, 3);
    v1 = addu(v1, a0);
    a3 = addiu(v1, 32);
    a1 = 3;
    for (;;) {
        // 0x001b01ec
        charge(ctx, 9);
        lw(a0, a2, 0);
        lw(v1, a2, 4);
        a2 = addiu(a2, 8);
        a1 = addiu(a1, -1);
        sw(a0, a3, 0);
        sw(v1, a3, 4);
        a3 = addiu(a3, 8);
        if (i64(a1) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x001b0210
    charge(ctx, 2);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_1B01D0(EEContext& ctx, u64 task, u64 i, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(i));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(src));
    sub_1B01D0(ctx);
}

// 0x001B0230 sub_1B0230 -- 16 bytes; leaf frame (no stack)
// 0x1B0230: the action count, work +28.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1B0230(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001b0230
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    sw(a1, v1, 28);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_1B0230(EEContext& ctx, u64 task, u64 value) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(value));
    sub_1B0230(ctx);
}

// 0x001B0250 sub_1B0250 -- 16 bytes; leaf frame (no stack)
// 0x1B0250: work +1204 (written by the Y_* enemy / NPC think states 0x44AF60.. ; inf).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1B0250(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x001b0250
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 60);
    sw(a1, v1, 1204);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_1B0250(EEContext& ctx, u64 task, u64 value) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(value));
    sub_1B0250(ctx);
}

// 0x001C0880 sub_1C0880 -- 152 bytes; leaf frame (no stack)
// 0x1C0880: state 1 -> -1 (done; the task ends). State 0: while frames remain, value += (end - value) / frames
// (written as value - (value - end) / frames) and frames--; on the last call value = end and state 1. The value is
// the f32 at target +24. Any other state: 0, nothing done.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1C0880(EEContext& ctx) {
    using hg::Fpr, hg::Gpr, hg::addiu, hg::charge, hg::cvt_s_w, hg::div_s, hg::enter, hg::i64, hg::lw, hg::lwc1,
          hg::mtc1, hg::si, hg::sub_s, hg::sw, hg::swc1;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x001c0880
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(a1, a0, 60);
    lw(a0, a1, 0);
    v0 = 1;
    if (a0 == v0) {
        // 0x001c0900
        charge(ctx, 3);
        v0 = si(-1);
    } else {
        // 0x001c0894
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x001c08a4
            charge(ctx, 3);
            lw(v1, a1, 8);
            if (i64(v1) <= 0) {
                // 0x001c08e4
                charge(ctx, 3);
                lwc1(f0, a1, 12);
                v0 = addiu(a0, 1);
                sw(v0, a1, 0);
            } else {
                // 0x001c08b0
                charge(ctx, 13);
                lw(v0, a1, 4);
                lwc1(f2, v0, 24);
                lwc1(f0, a1, 12);
                sub_s(f1, f2, f0);
                mtc1(v1, f0);
                cvt_s_w(f0, f0);
                div_s(f0, f1, f0);
                sub_s(f0, f2, f0);
                v0 = addiu(v1, -1);
                sw(v0, a1, 8);
            }
            // 0x001c08f0
            charge(ctx, 4);
            lw(v0, a1, 4);
            swc1(f0, v0, 24);
        } else {
            // 0x001c089c
            charge(ctx, 2);
        }
        // 0x001c090c
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x001c0910 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
s32 sub_1C0880(EEContext& ctx, u64 task) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    sub_1C0880(ctx);
    return static_cast<s32>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x001C0960 sub_1C0960 -- 964 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// 0x1C0960: the same fade on a wall model's alpha byte (mdlGetColor/mdlSetColor of target +260, rgba copied to the
// frame at sp+44): state 0 steps alpha (u8, through f32), then writes alpha / 255 to the f32 +24 of every material
// in the model's nine material lists (+224 -> +8, +20, +24, +32, +12, +16, +28, +36, +40) and sets the colour back.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1C0960(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::backedge, hg::c_le_s, hg::charge, hg::cond, hg::cvt_s_w,
          hg::cvt_w_s, hg::div_s, hg::enter, hg::i64, hg::jal, hg::lbu, hg::ld, hg::lq, hg::lui, hg::lw, hg::lwc1,
          hg::mfc1, hg::mtc1, hg::sb, hg::sd, hg::si, hg::sq, hg::srl, hg::sub_s, hg::sw, hg::swc1;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x001c0960
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(v0, s0, 4);
    lw(a0, v0, 260);
    jal(ctx, 0x1C0978u, gen::fn_sub_318B00_00318b00);
    lbu(a2, v0, 0);
    lbu(a1, v0, 1);
    lbu(a0, v0, 2);
    lbu(v1, v0, 3);
    sb(a2, sp, 0x2C);
    sb(a1, sp, 0x2D);
    sb(a0, sp, 0x2E);
    sb(v1, sp, 0x2F);
    lw(a0, s0, 0);
    v1 = 1;
    if (a0 == v1) {
        // 0x001c0d00
        charge(ctx, 3);
        v0 = si(-1);
    } else {
        // 0x001c09b0
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x001c09c0
            charge(ctx, 3);
            lw(a1, s0, 8);
            if (i64(a1) <= 0) {
                // 0x001c0ac8
                charge(ctx, 7);
                lwc1(f1, s0, 12);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x001c0afc
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x001c0ae4
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x001c0b14
                charge(ctx, 4);
                sb(v1, sp, 0x2F);
                lw(v0, s0, 0);
                v0 = addiu(v0, 1);
                sw(v0, s0, 0);
            } else {
                // 0x001c09cc
                charge(ctx, 3);
                lbu(a0, v0, 3);
                if (i64(a0) < 0) {
                    // 0x001c09ec
                    charge(ctx, 7);
                    v1 = srl(a0, 1);
                    v0 = a0 & 0x1;
                    v1 = v1 | v0;
                    mtc1(v1, f0);
                    cvt_s_w(f1, f0);
                    add_s(f1, f1, f1);
                } else {
                    // 0x001c09d8
                    charge(ctx, 5);
                    mtc1(a0, f0);
                    cvt_s_w(f1, f0);
                }
                // 0x001c0a08
                charge(ctx, 11);
                lwc1(f0, s0, 12);
                sub_s(f1, f1, f0);
                mtc1(a1, f0);
                cvt_s_w(f0, f0);
                div_s(f1, f1, f0);
                if (i64(a0) < 0) {
                    // 0x001c0a48
                    charge(ctx, 7);
                    v1 = srl(a0, 1);
                    v0 = a0 & 0x1;
                    v1 = v1 | v0;
                    mtc1(v1, f0);
                    cvt_s_w(f0, f0);
                    add_s(f0, f0, f0);
                } else {
                    // 0x001c0a34
                    charge(ctx, 5);
                    mtc1(a0, f0);
                    cvt_s_w(f0, f0);
                }
                // 0x001c0a64
                charge(ctx, 7);
                sub_s(f1, f0, f1);
                v0 = 0x4F000000;
                mtc1(v0, f0);
                c_le_s(f0, f1);
                if (cond(ctx)) {
                    // 0x001c0a98
                    charge(ctx, 6);
                    sub_s(f0, f1, f0);
                    cvt_w_s(f0, f0);
                    mfc1(v1, f0);
                    v0 = lui(0x8000);
                    v1 = v1 | v0;
                    v1 = v1 & 0xFF;
                } else {
                    // 0x001c0a80
                    charge(ctx, 6);
                    cvt_w_s(f0, f1);
                    mfc1(v1, f0);
                    v1 = v1 & 0xFF;
                }
                // 0x001c0ab0
                charge(ctx, 6);
                sb(v1, sp, 0x2F);
                lw(v0, s0, 8);
                v0 = addiu(v0, -1);
                sw(v0, s0, 8);
            }
            // 0x001c0b24
            charge(ctx, 3);
            lbu(v0, sp, 0x2F);
            if (i64(v0) < 0) {
                // 0x001c0b44
                charge(ctx, 7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, f0);
                cvt_s_w(f1, f0);
                add_s(f1, f1, f1);
            } else {
                // 0x001c0b30
                charge(ctx, 5);
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
            }
            // 0x001c0b60
            charge(ctx, 10);
            v0 = 0x437F0000;
            mtc1(v0, f0);
            div_s(f0, f1, f0);
            lw(v0, s0, 4);
            lw(v0, v0, 260);
            lw(v0, v0, 224);
            lw(v1, v0, 8);
            for (;;) {
                // 0x001c0b90
                charge(ctx, 5);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001c0b88
                charge(ctx, 2);
                swc1(f0, v1, 24);
                lw(v1, v1, 40);
            }
            // 0x001c0ba4
            charge(ctx, 3);
            lw(v1, v0, 20);
            for (;;) {
                // 0x001c0bb8
                charge(ctx, 5);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001c0bb0
                charge(ctx, 2);
                swc1(f0, v1, 24);
                lw(v1, v1, 40);
            }
            // 0x001c0bcc
            charge(ctx, 3);
            lw(v1, v0, 24);
            for (;;) {
                // 0x001c0be0
                charge(ctx, 5);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001c0bd8
                charge(ctx, 2);
                swc1(f0, v1, 24);
                lw(v1, v1, 40);
            }
            // 0x001c0bf4
            charge(ctx, 3);
            lw(v1, v0, 32);
            for (;;) {
                // 0x001c0c08
                charge(ctx, 5);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001c0c00
                charge(ctx, 2);
                swc1(f0, v1, 24);
                lw(v1, v1, 40);
            }
            // 0x001c0c1c
            charge(ctx, 3);
            lw(v1, v0, 12);
            for (;;) {
                // 0x001c0c30
                charge(ctx, 5);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001c0c28
                charge(ctx, 2);
                swc1(f0, v1, 24);
                lw(v1, v1, 40);
            }
            // 0x001c0c44
            charge(ctx, 3);
            lw(v1, v0, 16);
            for (;;) {
                // 0x001c0c58
                charge(ctx, 5);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001c0c50
                charge(ctx, 2);
                swc1(f0, v1, 24);
                lw(v1, v1, 40);
            }
            // 0x001c0c6c
            charge(ctx, 3);
            lw(v1, v0, 28);
            for (;;) {
                // 0x001c0c80
                charge(ctx, 5);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001c0c78
                charge(ctx, 2);
                swc1(f0, v1, 24);
                lw(v1, v1, 40);
            }
            // 0x001c0c94
            charge(ctx, 3);
            lw(v1, v0, 36);
            for (;;) {
                // 0x001c0ca8
                charge(ctx, 5);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001c0ca0
                charge(ctx, 2);
                swc1(f0, v1, 24);
                lw(v1, v1, 40);
            }
            // 0x001c0cbc
            charge(ctx, 3);
            lw(v0, v0, 40);
            for (;;) {
                // 0x001c0cd0
                charge(ctx, 5);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001c0cc8
                charge(ctx, 2);
                swc1(f0, v0, 24);
                lw(v0, v0, 40);
            }
            // 0x001c0ce4
            charge(ctx, 7);
            lw(v0, s0, 4);
            lw(a0, v0, 260);
            a1 = addiu(sp, 0x2C);
            jal(ctx, 0x1C0CF0u, gen::fn_sub_318AD0_00318ad0);
        } else {
            // 0x001c09b8
            charge(ctx, 2);
        }
        // 0x001c0d0c
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x001c0d10 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
s32 sub_1C0960(EEContext& ctx, u64 task) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    sub_1C0960(ctx);
    return static_cast<s32>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x001BAB60 sub_1BAB60 -- 1328 bytes; frame 0x20
// 0x1BAB60(block, turn): turn = 1 << k for k in 0..3 quarter turns (any other value: k = 0).
//  1. every cell (row, col) is filled from the kind table: cells[row][col] = table[kinds[row][col]];
//  2. the cells are rotated: 2 x 2 blocks k times around the ring (0,0) <- (0,1) <- (1,1) <- (1,0); 1 x 2 blocks
//     (width 1, depth 2) become 2 x 1 for k = 1 / 3 and swap ends for k = 2; 3 x 3 blocks rotate their outer ring
//     2 k positions (the centre stays); 1 x 1 and other shapes keep their cells;
//  3. each cell's door byte rotates both nibbles left by k within 4 bits (the open sides turn with the block).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1BAB60(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::lbu, hg::lh, hg::sb, hg::sh,
          hg::sll, hg::sllv, hg::slt, hg::slti, hg::sra, hg::srl;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13}, t6{ctx, 14}, t7{ctx, 15}, t8{ctx, 24}, sp{ctx, 29};
    // 0x001bab60
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a3 = 0;
    v1 = 0;
    t5 = 0x680000;
    t5 = addiu(t5, -2560);  // &0x67F600
    for (;;) {
        // 0x001babe8
        charge(ctx, 3);
        a2 = slti(v1, 3);
        if (a2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001bab7c
        charge(ctx, 8);
        t8 = 0;
        a2 = sll(v1, 1);
        a2 = addu(a2, v1);
        t7 = addu(a0, a2);
        a2 = sll(a2, 3);
        t6 = addu(a0, a2);
        for (;;) {
            // 0x001babd8
            charge(ctx, 3);
            a2 = slti(t8, 3);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001bab9c
            charge(ctx, 15);
            a2 = addu(t7, t8);
            lbu(a2, a2, 4);
            a2 = sll(a2, 3);
            t4 = addu(t5, a2);
            a2 = sll(t8, 3);
            t3 = addu(t6, a2);
            lh(t2, t4, 0);
            lh(t1, t4, 2);
            lh(t0, t4, 4);
            lh(a2, t4, 6);
            sh(t2, t3, 14);
            sh(t1, t3, 16);
            sh(t0, t3, 18);
            sh(a2, t3, 20);
            t8 = addiu(t8, 1);
        }
        // 0x001babe4
        charge(ctx, 1);
        v1 = addiu(v1, 1);
    }
    // 0x001babf4
    charge(ctx, 4);
    t0 = 0;
    a2 = 1;
    for (;;) {
        // 0x001bac20
        charge(ctx, 3);
        v1 = slti(t0, 4);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001bac04
        charge(ctx, 3);
        v1 = sllv(a2, t0);
        if (v1 == a1) {
            goto L_001bac10_8;
        }
        // 0x001bac1c
        charge(ctx, 1);
        t0 = addiu(t0, 1);
    }
L_001bac2c:
    charge(ctx, 4);
    lbu(t0, a0, 1);
    a1 = 1;
    if (t0 == a1) {
        // 0x001bac3c
        charge(ctx, 3);
        lbu(v1, a0, 2);
        if (v1 != a1) {
            goto L_001bac48;
        }
        goto L_001baff0;
    }
L_001bac48:
    charge(ctx, 3);
    a1 = 2;
    if (t0 == a1) {
        // 0x001bac54
        charge(ctx, 3);
        lbu(v1, a0, 2);
        if (v1 != a1) {
            goto L_001bad20;
        }
        // 0x001bac60
        charge(ctx, 3);
        v1 = 0;
        for (;;) {
            // 0x001bad0c
            charge(ctx, 3);
            a1 = slt(v1, a3);
            if (a1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001bac6c
            charge(ctx, 40);
            lh(t0, a0, 14);
            lh(a2, a0, 16);
            lh(a1, a0, 18);
            lh(t2, a0, 20);
            sh(t0, sp, 0x18);
            sh(a2, sp, 0x1A);
            sh(a1, sp, 0x1C);
            sh(t2, sp, 0x1E);
            lh(t1, a0, 22);
            lh(t0, a0, 24);
            lh(a2, a0, 26);
            lh(a1, a0, 28);
            sh(t1, a0, 14);
            sh(t0, a0, 16);
            sh(a2, a0, 18);
            sh(a1, a0, 20);
            lh(t1, a0, 46);
            lh(t0, a0, 48);
            lh(a2, a0, 50);
            lh(a1, a0, 52);
            sh(t1, a0, 22);
            sh(t0, a0, 24);
            sh(a2, a0, 26);
            sh(a1, a0, 28);
            lh(t1, a0, 38);
            lh(t0, a0, 40);
            lh(a2, a0, 42);
            lh(a1, a0, 44);
            sh(t1, a0, 46);
            sh(t0, a0, 48);
            sh(a2, a0, 50);
            sh(a1, a0, 52);
            lh(t0, sp, 0x18);
            lh(a2, sp, 0x1A);
            lh(a1, sp, 0x1C);
            sh(t0, a0, 38);
            sh(a2, a0, 40);
            sh(a1, a0, 42);
            sh(t2, a0, 44);
            v1 = addiu(v1, 1);
        }
        // 0x001bad18
        charge(ctx, 2);
        goto L_001baff0;
    }
L_001bad20:
    charge(ctx, 3);
    a1 = 1;
    if (t0 == a1) {
        // 0x001bad2c
        charge(ctx, 4);
        lbu(a2, a0, 2);
        v1 = 2;
        if (a2 != v1) {
            goto L_001bae9c;
        }
        // 0x001bad3c
        charge(ctx, 2);
        if (a3 != a1) {
            // 0x001bada4
            charge(ctx, 2);
            if (a3 != v1) {
                // 0x001bae10
                charge(ctx, 3);
                a2 = 3;
                if (a3 == a2) {
                    // 0x001bae1c
                    charge(ctx, 32);
                    lh(t2, a0, 14);
                    lh(t1, a0, 16);
                    lh(t0, a0, 18);
                    lh(a2, a0, 20);
                    sh(t2, a0, 22);
                    sh(t1, a0, 24);
                    sh(t0, a0, 26);
                    sh(a2, a0, 28);
                    lh(t2, a0, 38);
                    lh(t1, a0, 40);
                    lh(t0, a0, 42);
                    lh(a2, a0, 44);
                    sh(t2, a0, 14);
                    sh(t1, a0, 16);
                    sh(t0, a0, 18);
                    sh(a2, a0, 20);
                    a2 = 0x680000;
                    lh(t2, a2, -2560);  // 0x67F600
                    a2 = 0x680000;
                    lh(t1, a2, -2558);  // 0x67F602
                    a2 = 0x680000;
                    lh(t0, a2, -2556);  // 0x67F604
                    a2 = 0x680000;
                    lh(a2, a2, -2554);  // 0x67F606
                    sh(t2, a0, 38);
                    sh(t1, a0, 40);
                    sh(t0, a0, 42);
                    sh(a2, a0, 44);
                    sb(v1, a0, 1);
                    sb(a1, a0, 2);
                }
            } else {
                // 0x001badac
                charge(ctx, 25);
                lh(a2, a0, 14);
                lh(a1, a0, 16);
                lh(v1, a0, 18);
                lh(t1, a0, 20);
                sh(a2, sp, 0x10);
                sh(a1, sp, 0x12);
                sh(v1, sp, 0x14);
                sh(t1, sp, 0x16);
                lh(t0, a0, 38);
                lh(a2, a0, 40);
                lh(a1, a0, 42);
                lh(v1, a0, 44);
                sh(t0, a0, 14);
                sh(a2, a0, 16);
                sh(a1, a0, 18);
                sh(v1, a0, 20);
                lh(a2, sp, 0x10);
                lh(a1, sp, 0x12);
                lh(v1, sp, 0x14);
                sh(a2, a0, 38);
                sh(a1, a0, 40);
                sh(v1, a0, 42);
                sh(t1, a0, 44);
            }
        } else {
            // 0x001bad44
            charge(ctx, 24);
            lh(t2, a0, 38);
            lh(t1, a0, 40);
            lh(t0, a0, 42);
            lh(a2, a0, 44);
            sh(t2, a0, 22);
            sh(t1, a0, 24);
            sh(t0, a0, 26);
            sh(a2, a0, 28);
            a2 = 0x680000;
            lh(t2, a2, -2560);  // 0x67F600
            a2 = 0x680000;
            lh(t1, a2, -2558);  // 0x67F602
            a2 = 0x680000;
            lh(t0, a2, -2556);  // 0x67F604
            a2 = 0x680000;
            lh(a2, a2, -2554);  // 0x67F606
            sh(t2, a0, 38);
            sh(t1, a0, 40);
            sh(t0, a0, 42);
            sh(a2, a0, 44);
            sb(v1, a0, 1);
            sb(a1, a0, 2);
        }
        goto L_001baff0;
    }
L_001bae9c:
    charge(ctx, 3);
    a1 = 3;
    if (t0 == a1) {
        // 0x001baea8
        charge(ctx, 3);
        lbu(v1, a0, 2);
        if (v1 == a1) {
            // 0x001baeb4
            charge(ctx, 4);
            a2 = 0;
            a1 = sll(a3, 1);
            for (;;) {
                // 0x001bafe4
                charge(ctx, 3);
                v1 = slt(a2, a1);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001baec4
                charge(ctx, 72);
                lh(t2, a0, 14);
                lh(t1, a0, 16);
                lh(t0, a0, 18);
                lh(v1, a0, 20);
                sh(t2, sp, 0x8);
                sh(t1, sp, 0xA);
                sh(t0, sp, 0xC);
                sh(v1, sp, 0xE);
                lh(t3, a0, 22);
                lh(t2, a0, 24);
                lh(t1, a0, 26);
                lh(t0, a0, 28);
                sh(t3, a0, 14);
                sh(t2, a0, 16);
                sh(t1, a0, 18);
                sh(t0, a0, 20);
                lh(t3, a0, 30);
                lh(t2, a0, 32);
                lh(t1, a0, 34);
                lh(t0, a0, 36);
                sh(t3, a0, 22);
                sh(t2, a0, 24);
                sh(t1, a0, 26);
                sh(t0, a0, 28);
                lh(t3, a0, 54);
                lh(t2, a0, 56);
                lh(t1, a0, 58);
                lh(t0, a0, 60);
                sh(t3, a0, 30);
                sh(t2, a0, 32);
                sh(t1, a0, 34);
                sh(t0, a0, 36);
                lh(t3, a0, 78);
                lh(t2, a0, 80);
                lh(t1, a0, 82);
                lh(t0, a0, 84);
                sh(t3, a0, 54);
                sh(t2, a0, 56);
                sh(t1, a0, 58);
                sh(t0, a0, 60);
                lh(t3, a0, 70);
                lh(t2, a0, 72);
                lh(t1, a0, 74);
                lh(t0, a0, 76);
                sh(t3, a0, 78);
                sh(t2, a0, 80);
                sh(t1, a0, 82);
                sh(t0, a0, 84);
                lh(t3, a0, 62);
                lh(t2, a0, 64);
                lh(t1, a0, 66);
                lh(t0, a0, 68);
                sh(t3, a0, 70);
                sh(t2, a0, 72);
                sh(t1, a0, 74);
                sh(t0, a0, 76);
                lh(t3, a0, 38);
                lh(t2, a0, 40);
                lh(t1, a0, 42);
                lh(t0, a0, 44);
                sh(t3, a0, 62);
                sh(t2, a0, 64);
                sh(t1, a0, 66);
                sh(t0, a0, 68);
                lh(t2, sp, 0x8);
                lh(t1, sp, 0xA);
                lh(t0, sp, 0xC);
                sh(t2, a0, 38);
                sh(t1, a0, 40);
                sh(t0, a0, 42);
                sh(v1, a0, 44);
                a2 = addiu(a2, 1);
            }
        }
    }
L_001baff0:
    charge(ctx, 3);
    a2 = 0;
    for (;;) {
        // 0x001bb078
        charge(ctx, 3);
        v1 = slti(a2, 3);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001baffc
        charge(ctx, 7);
        a1 = 0;
        v1 = sll(a2, 1);
        v1 = addu(v1, a2);
        v1 = sll(v1, 3);
        v1 = addu(a0, v1);
        for (;;) {
            // 0x001bb068
            charge(ctx, 3);
            t0 = slti(a1, 3);
            if (t0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001bb018
            charge(ctx, 20);
            t0 = sll(a1, 3);
            t4 = addu(v1, t0);
            lbu(t3, t4, 14);
            t0 = t3 & 0xF;
            t0 = t0 & 0xF;
            t0 = sllv(t0, a3);
            t1 = t0 & 0xF;
            t0 = srl(t0, 4);
            t2 = t1 | t0;
            t0 = t3 & 0xF0;
            t0 = sra(t0, 4);
            t0 = t0 & 0xF;
            t0 = sllv(t0, a3);
            t1 = t0 & 0xF;
            t0 = srl(t0, 4);
            t0 = t1 | t0;
            t0 = sll(t0, 4);
            t0 = t2 | t0;
            sb(t0, t4, 14);
            a1 = addiu(a1, 1);
        }
        // 0x001bb074
        charge(ctx, 1);
        a2 = addiu(a2, 1);
    }
    // 0x001bb084
    charge(ctx, 3);
    sp = addiu(sp, 0x20);
    return;
L_001bac10_8:
    charge(ctx, 3);
    a3 = t0;
    goto L_001bac2c;
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_1BAB60(EEContext& ctx, u64 block, u64 turn) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(block));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(turn));
    sub_1BAB60(ctx);
}
void sub_1BD950(EEContext& ctx) { Culling{ctx}.sub_1BD950(); }
u32 sub_1B6EB0(EEContext& ctx, u64 major, u64 minor) { set_args(ctx, {major, minor}); SceneVariant{ctx}.sub_1B6EB0(); return v0_of(ctx); }
void sub_1A9850(EEContext& ctx) { Bgm{ctx}.sub_1A9850(); }
void sub_1AA1B0(EEContext& ctx) { Ambience{ctx}.sub_1AA1B0(); }
// 0x001BC630 sub_1BC630 -- 1168 bytes; frame 0xB0: ra sp+0x90, fp sp+0x80 (sq), s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: the hand version terminated the host on a random world.
// p3fes_handgen's body, statement for statement the original's.
void sub_1BC630(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq,
          hg::lw, hg::sd, hg::sll, hg::slt, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x001bc630
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0xB0);
    sd(ra, sp, 0x90);
    sq(fp, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a0;
    sw(a1, sp, 0xAC);
    sw(a2, sp, 0xA8);
    s0 = 0;
    lw(s4, a2, 0);
    for (;;) {
        // 0x001bc720
        charge(ctx, 4);
        lbu(v0, s5, 2);
        v0 = slt(s0, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001bc678
        charge(ctx, 5);
        s3 = 0;
        lw(v0, sp, 0xAC);
        lw(s6, v0, 0);
        for (;;) {
        L_001bc708:
            charge(ctx, 4);
            lbu(v0, s5, 1);
            v0 = slt(s3, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001bc68c
            charge(ctx, 3);
            s2 = 0;
            for (;;) {
                // 0x001bc6e8
                charge(ctx, 4);
                lbu(v0, s5, 2);
                v0 = slt(s2, v0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001bc698
                charge(ctx, 5);
                s1 = 0;
                v0 = addu(s4, s2);
                s7 = sll(v0, 8);
                for (;;) {
                    // 0x001bc6d4
                    charge(ctx, 4);
                    lbu(v0, s5, 1);
                    v0 = slt(s1, v0);
                    if (v0 == 0) {
                        break;
                    }
                    backedge(ctx);
                    // 0x001bc6ac
                    charge(ctx, 9);
                    jal(ctx, 0x1BC6ACu, gen::fn_K_Field_Get_001b9120);
                    v1 = addu(s7, v0);
                    v0 = addu(s6, s1);
                    v0 = sll(v0, 4);
                    v0 = addu(v1, v0);
                    lbu(v0, v0, 72);
                    if (v0 != 0) {
                        goto L_001bc700;
                    }
                    // 0x001bc6d0
                    charge(ctx, 1);
                    s1 = addiu(s1, 1);
                }
                // 0x001bc6e4
                charge(ctx, 1);
                s2 = addiu(s2, 1);
            }
            goto L_001bc6f8_9;
        }
        // 0x001bc718
        charge(ctx, 2);
        s0 = addiu(s0, 1);
        s4 = addiu(s4, -1);
    }
    // 0x001bc730
    charge(ctx, 3);
    v0 = 0;
    // 0x001bca8c (the shared epilogue, written out on this path)
    charge(ctx, 13);
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
L_001bc6f8_9:
    charge(ctx, 2);
    // 0x001bc73c
    charge(ctx, 4);
    sw(s4, sp, 0xA4);
    fp = 0;
    for (;;) {
        // 0x001bca64
        charge(ctx, 4);
        lbu(v0, s5, 2);
        v0 = slt(fp, v0);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001bc74c
        charge(ctx, 9);
        s3 = 0;
        s7 = s6;
        v0 = sll(fp, 1);
        v0 = addu(v0, fp);
        v0 = sll(v0, 3);
        s2 = addu(s5, v0);
        s1 = sll(s4, 8);
        for (;;) {
            // 0x001bca4c
            charge(ctx, 4);
            lbu(v0, s5, 1);
            v0 = slt(s3, v0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001bc770
            charge(ctx, 3);
            v0 = 14;
            if (s4 == v0) {
                // 0x001bc77c
                charge(ctx, 6);
                v0 = sll(s3, 3);
                v0 = addu(s2, v0);
                lbu(v0, v0, 14);
                v0 = v0 & 0x40;
                if (v0 == 0) {
                    goto L_001bc7a0;
                }
                goto L_001bc794_19;
            }
        L_001bc7a0:
            charge(ctx, 3);
            v0 = 1;
            if (s4 == v0) {
                // 0x001bc7ac
                charge(ctx, 6);
                v0 = sll(s3, 3);
                v0 = addu(s2, v0);
                lbu(v0, v0, 14);
                v0 = v0 & 0x10;
                if (v0 == 0) {
                    goto L_001bc7d0;
                }
                goto L_001bc7c4_22;
            }
        L_001bc7d0:
            charge(ctx, 3);
            v0 = 14;
            if (s7 == v0) {
                // 0x001bc7dc
                charge(ctx, 6);
                v0 = sll(s3, 3);
                v0 = addu(s2, v0);
                lbu(v0, v0, 14);
                v0 = v0 & 0x80;
                if (v0 == 0) {
                    goto L_001bc800;
                }
                goto L_001bc7f4_25;
            }
        L_001bc800:
            charge(ctx, 3);
            v0 = 1;
            if (s7 == v0) {
                // 0x001bc80c
                charge(ctx, 6);
                v0 = sll(s3, 3);
                v0 = addu(s2, v0);
                lbu(v0, v0, 14);
                v0 = v0 & 0x20;
                if (v0 == 0) {
                    goto L_001bc830;
                }
                goto L_001bc824_28;
            }
        L_001bc830:
            charge(ctx, 8);
            s0 = sll(s7, 4);
            jal(ctx, 0x1BC834u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(s1, v0);
            v0 = addu(v0, s0);
            lbu(v0, v0, -184);
            if (v0 != 0) {
                // 0x001bc850
                charge(ctx, 8);
                jal(ctx, 0x1BC850u, gen::fn_K_Field_Get_001b9120);
                v0 = addu(s1, v0);
                v0 = addu(v0, s0);
                lbu(v0, v0, -173);
                v0 = v0 & 0x40;
                if (v0 == 0) {
                    // 0x001bc894
                    charge(ctx, 6);
                    v0 = sll(s3, 3);
                    v0 = addu(s2, v0);
                    lbu(v0, v0, 14);
                    v0 = v0 & 0x10;
                    if (v0 == 0) {
                        goto L_001bc8b8;
                    }
                    goto L_001bc8ac_34;
                }
                // 0x001bc870
                charge(ctx, 6);
                v0 = sll(s3, 3);
                v0 = addu(s2, v0);
                lbu(v0, v0, 14);
                v0 = v0 & 0x10;
                if (v0 != 0) {
                    goto L_001bc8b8;
                }
                goto L_001bc888_32;
            }
        L_001bc8b8:
            charge(ctx, 7);
            jal(ctx, 0x1BC8B8u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(s1, v0);
            v0 = addu(v0, s0);
            lbu(v0, v0, 56);
            if (v0 != 0) {
                // 0x001bc8d4
                charge(ctx, 8);
                jal(ctx, 0x1BC8D4u, gen::fn_K_Field_Get_001b9120);
                v0 = addu(s1, v0);
                v0 = addu(v0, s0);
                lbu(v0, v0, 67);
                v0 = v0 & 0x80;
                if (v0 == 0) {
                    // 0x001bc918
                    charge(ctx, 6);
                    v0 = sll(s3, 3);
                    v0 = addu(s2, v0);
                    lbu(v0, v0, 14);
                    v0 = v0 & 0x20;
                    if (v0 == 0) {
                        goto L_001bc93c;
                    }
                    goto L_001bc930_40;
                }
                // 0x001bc8f4
                charge(ctx, 6);
                v0 = sll(s3, 3);
                v0 = addu(s2, v0);
                lbu(v0, v0, 14);
                v0 = v0 & 0x20;
                if (v0 != 0) {
                    goto L_001bc93c;
                }
                goto L_001bc90c_38;
            }
        L_001bc93c:
            charge(ctx, 7);
            jal(ctx, 0x1BC93Cu, gen::fn_K_Field_Get_001b9120);
            v0 = addu(s1, v0);
            v0 = addu(v0, s0);
            lbu(v0, v0, 328);
            if (v0 != 0) {
                // 0x001bc958
                charge(ctx, 8);
                jal(ctx, 0x1BC958u, gen::fn_K_Field_Get_001b9120);
                v0 = addu(s1, v0);
                v0 = addu(v0, s0);
                lbu(v0, v0, 339);
                v0 = v0 & 0x10;
                if (v0 == 0) {
                    // 0x001bc99c
                    charge(ctx, 6);
                    v0 = sll(s3, 3);
                    v0 = addu(s2, v0);
                    lbu(v0, v0, 14);
                    v0 = v0 & 0x40;
                    if (v0 == 0) {
                        goto L_001bc9c0;
                    }
                    goto L_001bc9b4_46;
                }
                // 0x001bc978
                charge(ctx, 6);
                v0 = sll(s3, 3);
                v0 = addu(s2, v0);
                lbu(v0, v0, 14);
                v0 = v0 & 0x40;
                if (v0 != 0) {
                    goto L_001bc9c0;
                }
                goto L_001bc990_44;
            }
        L_001bc9c0:
            charge(ctx, 7);
            jal(ctx, 0x1BC9C0u, gen::fn_K_Field_Get_001b9120);
            v0 = addu(s1, v0);
            v0 = addu(v0, s0);
            lbu(v0, v0, 88);
            if (v0 != 0) {
                // 0x001bc9dc
                charge(ctx, 8);
                jal(ctx, 0x1BC9DCu, gen::fn_K_Field_Get_001b9120);
                v0 = addu(s1, v0);
                v0 = addu(v0, s0);
                lbu(v0, v0, 99);
                v0 = v0 & 0x20;
                if (v0 == 0) {
                    // 0x001bca20
                    charge(ctx, 6);
                    v0 = sll(s3, 3);
                    v0 = addu(s2, v0);
                    lbu(v0, v0, 14);
                    v0 = v0 & 0x80;
                    if (v0 == 0) {
                        goto L_001bca44;
                    }
                    goto L_001bca38_52;
                }
                // 0x001bc9fc
                charge(ctx, 6);
                v0 = sll(s3, 3);
                v0 = addu(s2, v0);
                lbu(v0, v0, 14);
                v0 = v0 & 0x80;
                if (v0 != 0) {
                    goto L_001bca44;
                }
                goto L_001bca14_50;
            }
        L_001bca44:
            charge(ctx, 2);
            s3 = addiu(s3, 1);
            s7 = addiu(s7, 1);
        }
        // 0x001bca5c
        charge(ctx, 2);
        fp = addiu(fp, 0x1);
        s4 = addiu(s4, 1);
    }
    // 0x001bca74
    charge(ctx, 6);
    lw(v0, sp, 0xAC);
    sw(s6, v0, 0);
    lw(v1, sp, 0xA4);
    lw(v0, sp, 0xA8);
    sw(v1, v0, 0);
    v0 = 1;
    // 0x001bca8c (the shared epilogue, written out on this path)
    charge(ctx, 13);
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
L_001bc700:
    charge(ctx, 2);
    s3 = addiu(s3, 1);
    s6 = addiu(s6, -1);
    goto L_001bc708;
L_001bc794_19:
    charge(ctx, 3);
    v0 = 0;
    // 0x001bca8c (the shared epilogue, written out on this path)
    charge(ctx, 13);
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
L_001bc7c4_22:
    charge(ctx, 3);
    v0 = 0;
    // 0x001bca8c (the shared epilogue, written out on this path)
    charge(ctx, 13);
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
L_001bc7f4_25:
    charge(ctx, 3);
    v0 = 0;
    // 0x001bca8c (the shared epilogue, written out on this path)
    charge(ctx, 13);
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
L_001bc824_28:
    charge(ctx, 3);
    v0 = 0;
    // 0x001bca8c (the shared epilogue, written out on this path)
    charge(ctx, 13);
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
L_001bc888_32:
    charge(ctx, 3);
    v0 = 0;
    // 0x001bca8c (the shared epilogue, written out on this path)
    charge(ctx, 13);
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
L_001bc8ac_34:
    charge(ctx, 3);
    v0 = 0;
    // 0x001bca8c (the shared epilogue, written out on this path)
    charge(ctx, 13);
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
L_001bc90c_38:
    charge(ctx, 3);
    v0 = 0;
    // 0x001bca8c (the shared epilogue, written out on this path)
    charge(ctx, 13);
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
L_001bc930_40:
    charge(ctx, 3);
    v0 = 0;
    // 0x001bca8c (the shared epilogue, written out on this path)
    charge(ctx, 13);
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
L_001bc990_44:
    charge(ctx, 3);
    v0 = 0;
    // 0x001bca8c (the shared epilogue, written out on this path)
    charge(ctx, 13);
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
L_001bc9b4_46:
    charge(ctx, 3);
    v0 = 0;
    // 0x001bca8c (the shared epilogue, written out on this path)
    charge(ctx, 13);
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
L_001bca14_50:
    charge(ctx, 3);
    v0 = 0;
    // 0x001bca8c (the shared epilogue, written out on this path)
    charge(ctx, 13);
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
L_001bca38_52:
    charge(ctx, 3);
    v0 = 0;
    // 0x001bca8c (the shared epilogue, written out on this path)
    charge(ctx, 13);
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
u32 sub_1BC630(EEContext& ctx, u64 block, u64 px, u64 pz) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(block));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(px));
    ee::core::set_gpr64(ctx, GPR_A2, static_cast<u64>(pz));
    sub_1BC630(ctx);
    return static_cast<u32>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x001AD940 sub_1AD940 -- 152 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// 0x1AD940(out, task): out = the controller's model position, or (0, 0, 0) without a model (the 12-byte vector
// at sp+32 is cleared byte by byte first: the inlined memset).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1AD940(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw,
          hg::lwc1, hg::sb, hg::sd, hg::sq, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x001ad940
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a1, a1, 60);
    a0 = addiu(sp, 0x20);
    v1 = 12;
    if (a0 != 0) {
        for (;;) {
            // 0x001ad964
            charge(ctx, 7);
            sb(zero, a0, 0);
            a0 = addiu(a0, 1);
            v1 = addiu(v1, -1);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x001ad980
    charge(ctx, 3);
    lw(a0, a1, 16);
    if (a0 != 0) {
        // 0x001ad98c
        charge(ctx, 8);
        jal(ctx, 0x1AD98Cu, gen::fn_sub_318B60_00318b60);
        lwc1(f2, v0, 48);
        lwc1(f1, v0, 52);
        lwc1(f0, v0, 56);
        swc1(f2, sp, 0x20);
        swc1(f1, sp, 0x24);
        swc1(f0, sp, 0x28);
    }
    // 0x001ad9ac (the shared epilogue, written out on this path)
    charge(ctx, 11);
    lwc1(f2, sp, 0x20);
    lwc1(f1, sp, 0x24);
    lwc1(f0, sp, 0x28);
    swc1(f2, s0, 0);
    swc1(f1, s0, 4);
    swc1(f0, s0, 8);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_1AD940(EEContext& ctx, u64 out, u64 task) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(out));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(task));
    sub_1AD940(ctx);
}

// 0x001ADD40 sub_1ADD40 -- 164 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x1ADD40(task): the controller's grid cell from its model's position (800-unit cells, origin at the world origin).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1ADD40(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::cvt_w_s, hg::div_s, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw,
          hg::lwc1, hg::mfc1, hg::mtc1, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1};
    // 0x001add40
    enter(ctx, 41);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(a0, s0, 16);
    jal(ctx, 0x1ADD54u, gen::fn_sub_318B60_00318b60);
    lwc1(f1, v0, 48);
    v0 = 0x43C80000;
    mtc1(v0, f0);
    add_s(f1, f0, f1);
    v0 = 0x44480000;
    mtc1(v0, f0);
    div_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(v0, f0);
    sw(v0, s0, 44);
    lw(a0, s0, 16);
    jal(ctx, 0x1ADD94u, gen::fn_sub_318B60_00318b60);
    lwc1(f1, v0, 56);
    v1 = 0x43C80000;
    mtc1(v1, f0);
    add_s(f1, f0, f1);
    v1 = 0x44480000;
    mtc1(v1, f0);
    div_s(f0, f1, f0);
    cvt_w_s(f0, f0);
    mfc1(v1, f0);
    sw(v1, s0, 48);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_1ADD40(EEContext& ctx, u64 task) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    sub_1ADD40(ctx);
}

// 0x001ADFF0 sub_1ADFF0 -- 212 bytes; frame 0x60: ra sp+0x30, s1 sp+0x20 (sq), s0 sp+0x10 (sq), f20 sp+0x0
// 0x1ADFF0(task, axis, $f12 angle): turns the controller's model in place: translate by -position,
// sub_318A50(model, axis, angle, 2) (inf: rotate), translate back (sub_318A30(model, &vec, 2): mdlTranslate).
// The position and its negation sit at sp+80 / sp+64; $f20 keeps the angle across the calls.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1ADFF0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lui, hg::lw, hg::lwc1,
          hg::mov_s, hg::mtc1, hg::mul_s, hg::sd, hg::sq, hg::swc1;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f12{ctx, 12}, f20{ctx, 20};
    // 0x001adff0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x30);
    sq(s1, sp, 0x20);
    sq(s0, sp, 0x10);
    swc1(f20, sp, 0x0);
    s1 = a1;
    mov_s(f20, f12);
    lw(s0, a0, 60);
    lw(a0, s0, 16);
    if (a0 != 0) {
        // 0x001ae01c
        charge(ctx, 35);
        jal(ctx, 0x1AE01Cu, gen::fn_sub_318B60_00318b60);
        lwc1(f2, v0, 48);
        lwc1(f1, v0, 52);
        lwc1(f0, v0, 56);
        swc1(f2, sp, 0x50);
        swc1(f1, sp, 0x54);
        swc1(f0, sp, 0x58);
        v0 = lui(0xBF80);
        mtc1(v0, f1);
        lwc1(f0, sp, 0x50);
        mul_s(f0, f1, f0);
        swc1(f0, sp, 0x40);
        lwc1(f0, sp, 0x54);
        mul_s(f0, f1, f0);
        swc1(f0, sp, 0x44);
        lwc1(f0, sp, 0x58);
        mul_s(f0, f1, f0);
        swc1(f0, sp, 0x48);
        lw(a0, s0, 16);
        a1 = addiu(sp, 0x40);
        a2 = 2;
        jal(ctx, 0x1AE074u, gen::fn_sub_318A30_00318a30);
        lw(a0, s0, 16);
        a1 = s1;
        mov_s(f12, f20);
        a2 = 2;
        jal(ctx, 0x1AE08Cu, gen::fn_sub_318A50_00318a50);
        lw(a0, s0, 16);
        a1 = addiu(sp, 0x50);
        a2 = 2;
        jal(ctx, 0x1AE0A0u, gen::fn_sub_318A30_00318a30);
    }
    // 0x001ae0a8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(s1, sp, 0x20);
    lq(s0, sp, 0x10);
    lwc1(f20, sp, 0x0);
    sp = addiu(sp, 0x60);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
void sub_1ADFF0(EEContext& ctx, u64 task, u64 axis) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(axis));
    sub_1ADFF0(ctx);
}
u32 K_FldFrame_HandleCollis(EEContext& ctx, u64 pos, u64 step, u64 id) { set_args(ctx, {pos, step, id}); Controller{ctx}.K_FldFrame_HandleCollis(); return v0_of(ctx); }
// 0x001D38D0 sub_1D38D0 -- 228 bytes; frame 0x70: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x1D38D0(task, per_cell): on random floors the Reaper limit (work +12) is lowered to per_cell x the number of
// floor cells (grid byte +0 == 1), compared unsigned; HI/LO keep the product.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1D38D0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq,
          hg::lw, hg::mult, hg::sd, hg::sll, hg::slti, hg::sltu, hg::sq, hg::sw;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001d38d0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s5 = a1;
    lw(s1, a0, 60);
    jal(ctx, 0x1D38F8u, gen::fn_K_Scene_IsRandomFloor_001a0250);
    v1 = 1;
    if (v0 == v1) {
        // 0x001d390c
        charge(ctx, 4);
        s4 = 0;
        s2 = 0;
        for (;;) {
            // 0x001d3968
            charge(ctx, 3);
            v1 = slti(s4, 16);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001d391c
            charge(ctx, 4);
            s3 = 0;
            s0 = sll(s4, 8);
            for (;;) {
                // 0x001d3958
                charge(ctx, 3);
                v1 = slti(s3, 16);
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
                // 0x001d392c
                charge(ctx, 9);
                jal(ctx, 0x1D392Cu, gen::fn_K_Field_Get_001b9120);
                a0 = addu(s0, v0);
                v1 = sll(s3, 4);
                v1 = addu(a0, v1);
                lbu(a0, v1, 72);
                v1 = 1;
                if (a0 == v1) {
                    // 0x001d3950
                    charge(ctx, 1);
                    s2 = addiu(s2, 1);
                }
                // 0x001d3954
                charge(ctx, 1);
                s3 = addiu(s3, 1);
            }
            // 0x001d3964
            charge(ctx, 1);
            s4 = addiu(s4, 1);
        }
        // 0x001d3974
        charge(ctx, 5);
        mult(a0, s2, s5);
        lw(v1, s1, 12);
        at = sltu(a0, v1);
        if (at != 0) {
            // 0x001d3988
            charge(ctx, 1);
            sw(a0, s1, 12);
        }
    }
    // 0x001d398c (the shared epilogue, written out on this path)
    charge(ctx, 10);
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
void sub_1D38D0(EEContext& ctx, u64 task, u64 per_cell) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(per_cell));
    sub_1D38D0(ctx);
}

// 0x001D3830 sub_1D3830 -- 108 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x1D3830(task) -> the Reaper warning level for the footstep supporter: -1 without a limit (work +12 == 0) or with
// 60 or more left, 1 below 60, 2 when the time is up (sub_1D38A0: the frames left before the Reaper).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1D3830(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::si, hg::slti,
          hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001d3830
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = si(-1);
    lw(v0, a0, 60);
    lw(v0, v0, 12);
    if (v0 != 0) {
        // 0x001d3858
        charge(ctx, 4);
        jal(ctx, 0x1D3858u, gen::fn_sub_1D38A0_001d38a0);
        if (v0 != 0) {
            // 0x001d3874
            charge(ctx, 3);
            at = slti(v0, 60);
            if (at != 0) {
                // 0x001d3880
                charge(ctx, 1);
                s0 = 1;
            }
        } else {
            // 0x001d3868
            charge(ctx, 3);
            s0 = 2;
        }
    } else {
        // 0x001d3850
        charge(ctx, 2);
    }
    // 0x001d3884 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
s32 sub_1D3830(EEContext& ctx, u64 task) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    sub_1D3830(ctx);
    return static_cast<s32>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x001D32A0 K_Unit_UpdateEnemyPopSchedulerTask -- 1052 bytes; frame 0x90: ra sp+0x60, s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x1D32A0: the "enemy pop scheduler" task body (work +0 state, +4 / +8 paused, +12 the Reaper limit, +16 frames,
// +20 Reapers): nothing in field 14/5 or while paused; states 0 (initial population), 1 (wait), 2 (respawn and the
// Reaper). Returns 0.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void K_Unit_UpdateEnemyPopSchedulerTask(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::divu, hg::enter, hg::i64, hg::jal,
          hg::lbu, hg::ld, hg::lhu, hg::lq, hg::lw, hg::lwc1, hg::mflo, hg::sd, hg::sll, hg::slti, hg::sltiu,
          hg::sltu, hg::sq, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x001d32a0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s4 = a0;
    lw(s0, a0, 60);
    lw(a0, gp, -22448);  // 0x7CD540
    lw(v1, a0, 0);
    v0 = 14;
    if (v1 == v0) {
        // 0x001d32dc
        charge(ctx, 4);
        lw(v1, a0, 4);
        v0 = 5;
        if (v1 != v0) {
            goto L_001d32f8;
        }
        // 0x001d32ec
        charge(ctx, 3);
        v0 = 0;
        // 0x001d3694 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(ra, sp, 0x60);
        lq(s5, sp, 0x50);
        lq(s4, sp, 0x40);
        lq(s3, sp, 0x30);
        lq(s2, sp, 0x20);
        lq(s1, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x90);
        return;
    }
L_001d32f8:
    charge(ctx, 4);
    lw(v0, s0, 4);
    a0 = 1;
    if (v0 != a0) {
        // 0x001d3314
        charge(ctx, 3);
        lw(v0, s0, 8);
        if (v0 != a0) {
            // 0x001d332c
            charge(ctx, 4);
            lw(v1, s0, 0);
            v0 = 2;
            if (v1 == v0) {
                // 0x001d353c
                charge(ctx, 14);
                lw(s1, gp, -22448);  // 0x7CD540
                jal(ctx, 0x1D3540u, gen::fn_K_FldDungeon_GetCurrentFloor_001bff20);
                a2 = v0 & 0xFFFF;
                lhu(a0, s1, 0);
                lhu(a1, s1, 4);
                jal(ctx, 0x1D3554u, gen::fn_sub_1D76E0_001d76e0);
                s1 = v0;
                jal(ctx, 0x1D3560u, gen::fn_K_FldDungeon_GetFloorKind_001c0040);
                v1 = 4;
                if (v0 != v1) {
                    // 0x001d3574
                    charge(ctx, 3);
                    v1 = 3;
                    if (v0 == v1) {
                        // 0x001d35c0
                        charge(ctx, 1);
                        s1 = 0;
                    } else {
                        // 0x001d3580
                        charge(ctx, 3);
                        v1 = 2;
                        if (v0 == v1) {
                            // 0x001d35b4
                            charge(ctx, 3);
                            s1 = 0;
                        } else {
                            // 0x001d358c
                            charge(ctx, 3);
                            v1 = 1;
                            if (v0 == v1) {
                                // 0x001d35a8
                                charge(ctx, 3);
                                s1 = 0;
                            } else {
                                // 0x001d3598
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x001d35a0
                                    charge(ctx, 2);
                                }
                            }
                        }
                    }
                }
                // 0x001d35c4
                charge(ctx, 4);
                lw(v0, gp, -19044);  // 0x7CE28C
                at = sltu(v0, s1);
                if (at != 0) {
                    // 0x001d35d4
                    charge(ctx, 5);
                    a0 = s1;
                    jal(ctx, 0x1D35D8u, gen::fn_sub_1D0720_001d0720);
                    if (i64(v0) > 0) {
                        // 0x001d35e8
                        charge(ctx, 2);
                        v0 = 1;
                        sw(v0, s0, 0);
                    }
                }
                // 0x001d35f0
                charge(ctx, 8);
                lw(a0, s0, 12);
                lw(v1, s0, 16);
                v0 = 30;
                divu(v1, v0);
                mflo(v0);
                at = sltu(a0, v0);
                if (at != 0) {
                    // 0x001d3610
                    charge(ctx, 2);
                    if (a0 == 0) {
                        goto L_001d3684;
                    }
                    // 0x001d3618
                    charge(ctx, 3);
                    lw(v0, s0, 20);
                    if (v0 != 0) {
                        goto L_001d3684;
                    }
                    // 0x001d3624
                    charge(ctx, 24);
                    a0 = addiu(sp, 0x70);
                    jal(ctx, 0x1D3628u, gen::fn_sub_452010_00452010);
                    a1 = addiu(sp, 0x80);
                    lwc1(f2, sp, 0x70);
                    lwc1(f1, sp, 0x74);
                    lwc1(f0, sp, 0x78);
                    swc1(f2, sp, 0x80);
                    swc1(f1, sp, 0x84);
                    swc1(f0, sp, 0x88);
                    a0 = 1;
                    jal(ctx, 0x1D3650u, gen::fn_K_FldUnit_CreateReaper_001cfc50);
                    a0 = 5155;
                    a1 = 1;
                    jal(ctx, 0x1D3660u, gen::fn_datSetFlag_0016f1f0);
                    lw(v0, s0, 20);
                    v0 = addiu(v0, 1);
                    sw(v0, s0, 20);
                    v0 = 1;
                    sw(v0, s0, 0);
                    goto L_001d3690;
                }
            L_001d3684:
                charge(ctx, 3);
                lw(v0, s0, 16);
                v0 = addiu(v0, 1);
                sw(v0, s0, 16);
            } else {
                // 0x001d333c
                charge(ctx, 2);
                if (v1 == a0) {
                    // 0x001d34d8
                    charge(ctx, 3);
                    s1 = 0;
                    for (;;) {
                        // 0x001d3508
                        charge(ctx, 3);
                        v0 = slti(s1, 24);
                        if (v0 == 0) {
                            break;
                        }
                        backedge(ctx);
                        // 0x001d34e4
                        charge(ctx, 5);
                        a0 = s1;
                        jal(ctx, 0x1D34E8u, gen::fn_sub_1CFDD0_001cfdd0);
                        if (v0 == 0) {
                            goto L_001d34f8_37;
                        }
                        // 0x001d3504
                        charge(ctx, 1);
                        s1 = addiu(s1, 1);
                    }
                    // 0x001d3514
                    charge(ctx, 1);
                    v0 = 1;
                L_001d3518:
                    charge(ctx, 2);
                    if (v0 != 0) {
                        // 0x001d3520
                        charge(ctx, 7);
                        jal(ctx, 0x1D3520u, gen::fn_sub_1D2A10_001d2a10);
                        lw(v0, s0, 0);
                        v0 = addiu(v0, 1);
                        sw(v0, s0, 0);
                    }
                } else {
                    // 0x001d3344
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x001d3354
                        charge(ctx, 5);
                        jal(ctx, 0x1D3354u, gen::fn_K_Scene_IsRandomFloor_001a0250);
                        v1 = 1;
                        if (v0 == v1) {
                            // 0x001d3368
                            charge(ctx, 4);
                            s3 = 0;
                            s1 = 0;
                            for (;;) {
                                // 0x001d33c4
                                charge(ctx, 3);
                                v0 = slti(s3, 16);
                                if (v0 == 0) {
                                    break;
                                }
                                backedge(ctx);
                                // 0x001d3378
                                charge(ctx, 4);
                                s2 = 0;
                                s5 = sll(s3, 8);
                                for (;;) {
                                    // 0x001d33b4
                                    charge(ctx, 3);
                                    v0 = slti(s2, 16);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                    // 0x001d3388
                                    charge(ctx, 9);
                                    jal(ctx, 0x1D3388u, gen::fn_K_Field_Get_001b9120);
                                    v1 = addu(s5, v0);
                                    v0 = sll(s2, 4);
                                    v0 = addu(v1, v0);
                                    lbu(v1, v0, 72);
                                    v0 = 1;
                                    if (v1 == v0) {
                                        // 0x001d33ac
                                        charge(ctx, 1);
                                        s1 = addiu(s1, 1);
                                    }
                                    // 0x001d33b0
                                    charge(ctx, 1);
                                    s2 = addiu(s2, 1);
                                }
                                // 0x001d33c0
                                charge(ctx, 1);
                                s3 = addiu(s3, 1);
                            }
                            // 0x001d33d0
                            charge(ctx, 4);
                            v0 = sll(s1, 2);
                            v0 = addu(v0, s1);
                            v0 = sll(v0, 1);
                            sw(v0, s0, 12);
                        }
                        // 0x001d33e0
                        charge(ctx, 15);
                        sw(zero, gp, -19044);  // 0x7CE28C
                        lw(s1, gp, -22448);  // 0x7CD540
                        jal(ctx, 0x1D33E8u, gen::fn_K_FldDungeon_GetCurrentFloor_001bff20);
                        a2 = v0 & 0xFFFF;
                        lhu(a0, s1, 0);
                        lhu(a1, s1, 4);
                        jal(ctx, 0x1D33FCu, gen::fn_sub_1D75F0_001d75f0);
                        s1 = v0;
                        jal(ctx, 0x1D3408u, gen::fn_K_FldDungeon_GetFloorKind_001c0040);
                        v1 = 4;
                        if (v0 != v1) {
                            // 0x001d341c
                            charge(ctx, 3);
                            v1 = 3;
                            if (v0 == v1) {
                                // 0x001d3494
                                charge(ctx, 4);
                                s1 = sll(s1, 1);
                                at = sltiu(s1, 19);
                                if (at == 0) {
                                    // 0x001d34a4
                                    charge(ctx, 1);
                                    s1 = 18;
                                }
                                // 0x001d34a8
                                charge(ctx, 4);
                                a0 = s4;
                                a1 = 2;
                                jal(ctx, 0x1D34B0u, gen::fn_sub_1D38D0_001d38d0);
                            } else {
                                // 0x001d3428
                                charge(ctx, 3);
                                a1 = 2;
                                if (v0 == a1) {
                                    // 0x001d347c
                                    charge(ctx, 6);
                                    s1 = 0;
                                    a0 = s4;
                                    jal(ctx, 0x1D3484u, gen::fn_sub_1D38D0_001d38d0);
                                } else {
                                    // 0x001d3434
                                    charge(ctx, 3);
                                    v1 = 1;
                                    if (v0 == v1) {
                                        // 0x001d3450
                                        charge(ctx, 4);
                                        s1 = sll(s1, 1);
                                        at = sltiu(s1, 19);
                                        if (at == 0) {
                                            // 0x001d3460
                                            charge(ctx, 1);
                                            s1 = 18;
                                        }
                                        // 0x001d3464
                                        charge(ctx, 6);
                                        a0 = s4;
                                        a1 = 2;
                                        jal(ctx, 0x1D346Cu, gen::fn_sub_1D38D0_001d38d0);
                                    } else {
                                        // 0x001d3440
                                        charge(ctx, 2);
                                        if (v0 != 0) {
                                            // 0x001d3448
                                            charge(ctx, 2);
                                        }
                                    }
                                }
                            }
                        }
                        // 0x001d34b8
                        charge(ctx, 8);
                        a0 = s1;
                        jal(ctx, 0x1D34BCu, gen::fn_sub_1D0720_001d0720);
                        lw(v0, s0, 0);
                        v0 = addiu(v0, 1);
                        sw(v0, s0, 0);
                    } else {
                        // 0x001d334c
                        charge(ctx, 2);
                    }
                }
            }
        L_001d3690:
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x001d3320
            charge(ctx, 3);
            v0 = 0;
        }
    } else {
        // 0x001d3308
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001d3694 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(ra, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x90);
    return;
L_001d34f8_37:
    charge(ctx, 3);
    v0 = 0;
    goto L_001d3518;
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
s32 K_Unit_UpdateEnemyPopSchedulerTask(EEContext& ctx, u64 task) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    K_Unit_UpdateEnemyPopSchedulerTask(ctx);
    return static_cast<s32>(ee::core::gpr64(ctx, GPR_V0));
}
u32 sub_1C7130(EEContext& ctx, u64 unit) { set_args(ctx, {unit}); FieldMisc{ctx}.sub_1C7130(); return v0_of(ctx); }
// 0x001D5140 sub_1D5140 -- 220 bytes; frame 0x50: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x1D5140(camera controller task) -> the index (0..8) of the camera point nearest the player (work +96 + 12 i,
// nine f32 triples; the player's position from its controller, resource work +204 -> +480), starting from the
// distance gp-0x7DF4; when none is nearer, the caller's $s1 is returned as it was. sqrtf((dy dy + dx dx) + dz dz)
// through ACC, as compiled.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1D5140(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::c_le_s, hg::charge, hg::cond, hg::enter, hg::jal,
          hg::ld, hg::lq, hg::lw, hg::lwc1, hg::madd_s, hg::madda_s, hg::mov_s, hg::mula_s, hg::sd, hg::sll,
          hg::slti, hg::sq, hg::sqrt_s, hg::sub_s, hg::swc1;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f4{ctx, 4}, f5{ctx, 5}, f6{ctx, 6};
    // 0x001d5140
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    lw(v0, s0, 204);
    a0 = addiu(sp, 0x30);
    lw(a1, v0, 480);
    jal(ctx, 0x1D5160u, gen::fn_sub_1AD940_001ad940);
    lwc1(f2, sp, 0x30);
    lwc1(f1, sp, 0x34);
    lwc1(f0, sp, 0x38);
    swc1(f2, sp, 0x40);
    swc1(f1, sp, 0x44);
    swc1(f0, sp, 0x48);
    lwc1(f6, gp, -32244);  // 0x7CAEFC
    v1 = 0;
    lwc1(f5, sp, 0x44);
    lwc1(f4, sp, 0x48);
    lwc1(f3, sp, 0x40);
    for (;;) {
        // 0x001d51f4
        charge(ctx, 3);
        v0 = slti(v1, 9);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001d519c
        charge(ctx, 19);
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 2);
        v0 = addu(s0, v0);
        lwc1(f0, v0, 96);
        sub_s(f2, f0, f3);
        lwc1(f0, v0, 100);
        sub_s(f1, f0, f5);
        lwc1(f0, v0, 104);
        sub_s(f0, f0, f4);
        mula_s(f1, f1);
        madda_s(f2, f2);
        madd_s(f0, f0, f0);
        sqrt_s(f0, f0);
        c_le_s(f6, f0);
        if (!cond(ctx)) {
            // 0x001d51e8
            charge(ctx, 2);
            mov_s(f6, f0);
            s1 = v1;
        }
        // 0x001d51f0
        charge(ctx, 1);
        v1 = addiu(v1, 1);
    }
    // 0x001d5200
    charge(ctx, 7);
    v0 = s1;
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u32 sub_1D5140(EEContext& ctx, u64 task) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    sub_1D5140(ctx);
    return static_cast<u32>(ee::core::gpr64(ctx, GPR_V0));
}

// 0x001E13F0 sub_1E13F0 -- 192 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// 0x1E13F0: the virtual pad's "rotate" task body (work +64 active, +68 the controller task, +84 f32 the step angle,
// +88 frames done, +92 frames): while active, turns the controller by the step about the axis 0x683DA0 (copied to
// sp+32) each frame (sub_1ADFF0); when done, sub_1AD9E0(controller, work), sub_1CD650(sField.event, 0) and inactive.
// Returns 0.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1E13F0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::lwc1, hg::sd,
          hg::slt, hg::sq, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f12{ctx, 12};
    // 0x001e13f0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    lw(s0, a0, 60);
    a1 = addiu(sp, 0x20);
    v0 = 0x680000;
    ld(v1, v0, 15776);  // 0x683DA0
    v0 = 0x680000;
    lwc1(f0, v0, 15784);  // 0x683DA8
    sd(v1, sp, 0x20);
    swc1(f0, sp, 0x28);
    lw(v1, s0, 64);
    v0 = 1;
    if (v1 == v0) {
        // 0x001e143c
        charge(ctx, 12);
        lw(v0, s0, 88);
        v0 = addiu(v0, 1);
        sw(v0, s0, 88);
        lw(a0, s0, 68);
        lwc1(f12, s0, 84);
        jal(ctx, 0x1E1450u, gen::fn_sub_1ADFF0_001adff0);
        lw(v1, s0, 88);
        lw(v0, s0, 92);
        v0 = slt(v1, v0);
        if (v0 == 0) {
            // 0x001e146c
            charge(ctx, 11);
            lw(a0, s0, 68);
            a1 = s0;
            jal(ctx, 0x1E1474u, gen::fn_sub_1AD9E0_001ad9e0);
            jal(ctx, 0x1E147Cu, gen::fn_K_Field_Get_001b9120);
            lw(a0, v0, 8);
            a1 = 0;
            jal(ctx, 0x1E148Cu, gen::fn_sub_1CD650_001cd650);
            sw(zero, s0, 64);
        }
    } else {
        // 0x001e142c
        charge(ctx, 2);
        if (v1 != 0) {
            // 0x001e1434
            charge(ctx, 2);
        }
    }
    // 0x001e1498 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
s32 sub_1E13F0(EEContext& ctx, u64 task) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    sub_1E13F0(ctx);
    return static_cast<s32>(ee::core::gpr64(ctx, GPR_V0));
}
u32 K_FldEvent_FindFldHitAt(EEContext& ctx, u64 point, u64 res) { set_args(ctx, {point, res}); FieldHits{ctx}.K_FldEvent_FindFldHitAt(); return v0_of(ctx); }
u32 K_FldEvent_IsUnitNearFldHit(EEContext& ctx, u64 unit) { set_args(ctx, {unit}); FieldHits{ctx}.K_FldEvent_IsUnitNearFldHit(); return v0_of(ctx); }
u32 sub_1D0720(EEContext& ctx, u64 n) { set_args(ctx, {n}); Spawner{ctx}.sub_1D0720(); return v0_of(ctx); }
// 0x001E1590 sub_1E1590 -- 652 bytes; frame 0x10: ra sp+0x0
// 0x1E1590(task, src, $f12 from, $f13 to) -> 1 when a turn starts: unless already turning (work +64 == 1), copies
// 64 bytes of src into the work, stores both headings (reduced below 360) at +76 / +80, takes the shorter way
// around between them (the wrap bounds gp-0x7BAC / gp-0x7DCC fold headings near 0 / 360), and for more than 45
// degrees splits it into |angle| / 30 frames (at least 1) of +84 = angle / frames each, +88 = 0, +64 = 1, and tells
// the field event task (sub_1CD650(sField.event, 1)).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_1E1590(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::abs_s, hg::add_s, hg::addiu, hg::backedge, hg::c_le_s, hg::c_lt_s, hg::charge,
          hg::cond, hg::cvt_s_w, hg::cvt_w_s, hg::div, hg::div_s, hg::enter, hg::i64, hg::jal, hg::ld, hg::lui,
          hg::lw, hg::lwc1, hg::mfc1, hg::mflo, hg::mtc1, hg::mul_s, hg::sd, hg::sub_s, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12}, f13{ctx, 13};
    // 0x001e1590
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, 60);
    lw(a0, v0, 64);
    v1 = 1;
    if (a0 != v1) {
        // 0x001e15b8
        charge(ctx, 2);
        a2 = 8;
        a3 = v0;
        for (;;) {
            // 0x001e15c0
            charge(ctx, 9);
            lw(a0, a1, 0);
            lw(v1, a1, 4);
            a1 = addiu(a1, 8);
            a2 = addiu(a2, -1);
            sw(a0, a3, 0);
            sw(v1, a3, 4);
            a3 = addiu(a3, 8);
            if (i64(a2) <= 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x001e15e4
        charge(ctx, 6);
        v1 = 0x43B40000;
        mtc1(v1, f0);
        c_le_s(f12, f0);
        if (!cond(ctx)) {
            // 0x001e15fc
            charge(ctx, 1);
            sub_s(f12, f12, f0);
        }
        // 0x001e1600
        charge(ctx, 7);
        swc1(f12, v0, 76);
        v1 = 0x43B40000;
        mtc1(v1, f0);
        c_le_s(f13, f0);
        if (!cond(ctx)) {
            // 0x001e161c
            charge(ctx, 1);
            sub_s(f13, f13, f0);
        }
        // 0x001e1620
        charge(ctx, 4);
        swc1(f13, v0, 80);
        c_lt_s(f12, f13);
        if (!cond(ctx)) {
            // 0x001e16ac
            charge(ctx, 4);
            lwc1(f0, gp, -31660);  // 0x7CB144
            c_le_s(f12, f0);
            if (!cond(ctx)) {
                // 0x001e16bc
                charge(ctx, 2);
                v1 = 0x43B40000;
                mtc1(v1, f12);
            }
            // 0x001e16c4
            charge(ctx, 4);
            lwc1(f0, gp, -31660);  // 0x7CB144
            c_le_s(f13, f0);
            if (!cond(ctx)) {
                // 0x001e16d4
                charge(ctx, 1);
                mtc1(zero, f13);
            }
            // 0x001e16d8
            charge(ctx, 4);
            lwc1(f0, gp, -32204);  // 0x7CAF24
            c_lt_s(f12, f0);
            if (cond(ctx)) {
                // 0x001e16e8
                charge(ctx, 2);
                v1 = 0x43B40000;
                mtc1(v1, f12);
            }
            // 0x001e16f0
            charge(ctx, 4);
            lwc1(f0, gp, -32204);  // 0x7CAF24
            c_lt_s(f13, f0);
            if (cond(ctx)) {
                // 0x001e1700
                charge(ctx, 1);
                mtc1(zero, f13);
            }
            // 0x001e1704
            charge(ctx, 7);
            sub_s(f3, f12, f13);
            v1 = 0x43B40000;
            mtc1(v1, f0);
            sub_s(f0, f0, f12);
            add_s(f2, f13, f0);
            a0 = 1;
        } else {
            // 0x001e1630
            charge(ctx, 4);
            lwc1(f0, gp, -31660);  // 0x7CB144
            c_le_s(f12, f0);
            if (!cond(ctx)) {
                // 0x001e1640
                charge(ctx, 1);
                mtc1(zero, f12);
            }
            // 0x001e1644
            charge(ctx, 4);
            lwc1(f0, gp, -31660);  // 0x7CB144
            c_le_s(f13, f0);
            if (!cond(ctx)) {
                // 0x001e1654
                charge(ctx, 2);
                v1 = 0x43B40000;
                mtc1(v1, f13);
            }
            // 0x001e165c
            charge(ctx, 4);
            lwc1(f0, gp, -32204);  // 0x7CAF24
            c_lt_s(f12, f0);
            if (cond(ctx)) {
                // 0x001e166c
                charge(ctx, 1);
                mtc1(zero, f12);
            }
            // 0x001e1670
            charge(ctx, 4);
            lwc1(f0, gp, -32204);  // 0x7CAF24
            c_lt_s(f13, f0);
            if (cond(ctx)) {
                // 0x001e1680
                charge(ctx, 2);
                v1 = 0x43B40000;
                mtc1(v1, f13);
            }
            // 0x001e1688
            charge(ctx, 9);
            sub_s(f3, f13, f12);
            v1 = 0x43B40000;
            mtc1(v1, f0);
            sub_s(f0, f0, f13);
            add_s(f2, f12, f0);
            a0 = 0;
        }
        // 0x001e1720
        charge(ctx, 5);
        abs_s(f1, f3);
        abs_s(f0, f2);
        c_lt_s(f1, f0);
        if (!cond(ctx)) {
            // 0x001e1760
            charge(ctx, 3);
            swc1(f2, v0, 84);
            if (a0 == 0) {
                // 0x001e176c
                charge(ctx, 5);
                v1 = lui(0xBF80);
                mtc1(v1, f1);
                lwc1(f0, v0, 84);
                mul_s(f0, f0, f1);
                swc1(f0, v0, 84);
            }
        } else {
            // 0x001e1734
            charge(ctx, 4);
            swc1(f3, v0, 84);
            v1 = 1;
            if (a0 == v1) {
                // 0x001e1744
                charge(ctx, 7);
                v1 = lui(0xBF80);
                mtc1(v1, f1);
                lwc1(f0, v0, 84);
                mul_s(f0, f0, f1);
                swc1(f0, v0, 84);
            }
        }
        // 0x001e1780
        charge(ctx, 8);
        lwc1(f0, v0, 84);
        abs_s(f1, f0);
        v1 = 0x42340000;
        mtc1(v1, f0);
        c_le_s(f1, f0);
        if (cond(ctx)) {
            // 0x001e1808
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x001e17a0
            charge(ctx, 7);
            cvt_w_s(f0, f1);
            mfc1(a0, f0);
            v1 = 30;
            div(a0, v1);
            mflo(v1);
            if (i64(v1) <= 0) {
                // 0x001e17bc
                charge(ctx, 1);
                v1 = 1;
            }
            // 0x001e17c0
            charge(ctx, 18);
            sw(v1, v0, 92);
            sw(zero, v0, 88);
            lwc1(f0, v0, 92);
            cvt_s_w(f1, f0);
            lwc1(f0, v0, 84);
            div_s(f0, f0, f1);
            swc1(f0, v0, 84);
            v1 = 1;
            sw(v1, v0, 64);
            jal(ctx, 0x1E17E4u, gen::fn_K_Field_Get_001b9120);
            lw(a0, v0, 8);
            a1 = 1;
            jal(ctx, 0x1E17F4u, gen::fn_sub_1CD650_001cd650);
            v0 = 1;
        }
    } else {
        // 0x001e15ac
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x001e180c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// The typed entry for hand-written callers: the arguments where the original's caller puts them, the register
// body, the result from $v0 / $f0. A caller that has to stay faithful gives $ra first (rt::jal at its original
// call site, then its own $ra back), as rofs_search.cpp does for RFMAI_ToUpperStr.
u32 sub_1E1590(EEContext& ctx, u64 task, u64 src) {
    ee::core::set_gpr64(ctx, GPR_A0, static_cast<u64>(task));
    ee::core::set_gpr64(ctx, GPR_A1, static_cast<u64>(src));
    sub_1E1590(ctx);
    return static_cast<u32>(ee::core::gpr64(ctx, GPR_V0));
}

}  // namespace p3fes::game

// =====================================================================================================================
// The recompiled program's entry points (recomp/generated/functions.h signatures): the bodies read their arguments
// from the registers as the caller left them and leave every result register themselves.
// =====================================================================================================================
namespace p3fes::recomp_gen {
namespace g = p3fes::game;
void fn_sub_1BD950_001bd950(p3fes::EEContext& ctx) { g::Culling{ctx}.sub_1BD950(); }
void fn_sub_1B6EB0_001b6eb0(p3fes::EEContext& ctx) { g::SceneVariant{ctx}.sub_1B6EB0(); }
void fn_sub_1A9850_001a9850(p3fes::EEContext& ctx) { g::Bgm{ctx}.sub_1A9850(); }
void fn_sub_1AA1B0_001aa1b0(p3fes::EEContext& ctx) { g::Ambience{ctx}.sub_1AA1B0(); }
void fn_K_FldFrame_HandleCollis_001ac750(p3fes::EEContext& ctx) { g::Controller{ctx}.K_FldFrame_HandleCollis(); }
void fn_sub_1C7130_001c7130(p3fes::EEContext& ctx) { g::FieldMisc{ctx}.sub_1C7130(); }
void fn_K_FldEvent_FindFldHitAt_001c5ee0(p3fes::EEContext& ctx) { g::FieldHits{ctx}.K_FldEvent_FindFldHitAt(); }
void fn_K_FldEvent_IsUnitNearFldHit_001c7b30(p3fes::EEContext& ctx) { g::FieldHits{ctx}.K_FldEvent_IsUnitNearFldHit(); }
void fn_sub_1D0720_001d0720(p3fes::EEContext& ctx) { g::Spawner{ctx}.sub_1D0720(); }
}  // namespace p3fes::recomp_gen
