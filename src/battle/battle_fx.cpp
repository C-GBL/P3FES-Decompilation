// The battle effect packets and the command effects (game/include/p3fes/game/battle_fx.h has the data flow;
// docs/ANALYSIS/27_unmapped_bands.md section 2), hand-decompiled from SLUS_216.21. Phase 5 slice `battle_fx`: these
// replace the recompiled bodies listed in game/replaced.txt; tests/game/test_battle_fx.cpp runs each against its
// __recomp body.
//
// Cycle model (ADR-0013): every charge() below is one `ctx.cycles += N` block of the recompiled body on the executed
// path, charged where the block starts (a block that ends in a `jal` is charged in full before the call, so a call's
// return continues in the same block); enter() is the entry check point plus the first block. backedge() sits wherever
// the recompiled body has a check point on a backward jump: the loops (a loop whose test block comes first checks
// before every iteration, after the test) and the backward `goto`s of the compiler's block layout, kept as explicit
// check points. A `jr` through a jump table reads the table entry from the guest image and switches on the target, as
// the original does; an entry outside the table's cases tail-jumps through rt::lookup_func like the recompiled body.
//
// Registers: register-faithful (battle_fx.h). Each body runs on a Cpu view of the guest context -- one named variable
// per GPR (64-bit writes keep bits 64..127, as the EE does; lq writes all 128), the FPU, VU0 macro and HI/LO operations
// through the runtime's own instruction semantics, the prologue spills and epilogue reloads on the guest stack, the
// calls with $ra = the original link -- so every register holds at every check point, call and return what the
// original holds there. A branch's delay-slot instruction is written once before the `if` when it executes on both
// paths. Structure offsets and the tables are named in the function comments.
#include "p3fes/game/battle_fx.h"

#include "p3fes/ee/core.h"
#include "p3fes_recomp_rt.h"

namespace p3fes::recomp_gen {
void fn_sub_108570_00108570(p3fes::EEContext&);
void fn_sub_108670_00108670(p3fes::EEContext&);
void fn_sub_108680_00108680(p3fes::EEContext&);
void fn_sub_1086A0_001086a0(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_sub_171110_00171110(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_kwlnTaskGetTaskByName_00195340(p3fes::EEContext&);
void fn_kwlnTaskGetWorkData_00195540(p3fes::EEContext&);
void fn_sub_1FDDF0_001fddf0(p3fes::EEContext&);
void fn_sub_1FDF10_001fdf10(p3fes::EEContext&);
void fn_sub_1FE5F0_001fe5f0(p3fes::EEContext&);
void fn_sub_1FE630_001fe630(p3fes::EEContext&);
void fn_sub_1FEA90_001fea90(p3fes::EEContext&);
void fn_sub_1FEAB0_001feab0(p3fes::EEContext&);
void fn_sub_1FEB30_001feb30(p3fes::EEContext&);
void fn_sub_1FEF10_001fef10(p3fes::EEContext&);
void fn_sub_1FF350_001ff350(p3fes::EEContext&);
void fn_sub_1FF370_001ff370(p3fes::EEContext&);
void fn_sub_1FF390_001ff390(p3fes::EEContext&);
void fn_sub_1FF3B0_001ff3b0(p3fes::EEContext&);
void fn_sub_21C3F0_0021c3f0(p3fes::EEContext&);
void fn_sub_21CCA0_0021cca0(p3fes::EEContext&);
void fn_sub_21CCE0_0021cce0(p3fes::EEContext&);
void fn_sub_27E310_0027e310(p3fes::EEContext&);
void fn_sub_27EC10_0027ec10(p3fes::EEContext&);
void fn_sub_27F650_0027f650(p3fes::EEContext&);
void fn_sub_27F680_0027f680(p3fes::EEContext&);
void fn_sub_27F7C0_0027f7c0(p3fes::EEContext&);
void fn_sub_27F940_0027f940(p3fes::EEContext&);
void fn_sub_27FFB0_0027ffb0(p3fes::EEContext&);
void fn_sub_280050_00280050(p3fes::EEContext&);
void fn_sub_2802D0_002802d0(p3fes::EEContext&);
void fn_sub_280390_00280390(p3fes::EEContext&);
void fn_sub_280870_00280870(p3fes::EEContext&);
void fn_sub_281270_00281270(p3fes::EEContext&);
void fn_sub_281290_00281290(p3fes::EEContext&);
void fn_sub_2812B0_002812b0(p3fes::EEContext&);
void fn_sub_284040_00284040(p3fes::EEContext&);
void fn_sub_288110_00288110(p3fes::EEContext&);
void fn_sub_288DA0_00288da0(p3fes::EEContext&);
void fn_sub_29AD20_0029ad20(p3fes::EEContext&);
void fn_sub_2B71E0_002b71e0(p3fes::EEContext&);
void fn_sub_2B9030_002b9030(p3fes::EEContext&);
void fn_sub_2B90D0_002b90d0(p3fes::EEContext&);  // this slice
void fn_sub_2B9300_002b9300(p3fes::EEContext&);  // this slice
void fn_sub_2B9350_002b9350(p3fes::EEContext&);  // this slice
void fn_sub_2B9370_002b9370(p3fes::EEContext&);  // this slice
void fn_sub_2B93C0_002b93c0(p3fes::EEContext&);  // this slice
void fn_sub_2B93E0_002b93e0(p3fes::EEContext&);
void fn_sub_2B94F0_002b94f0(p3fes::EEContext&);
void fn_sub_2B96F0_002b96f0(p3fes::EEContext&);  // this slice
void fn_sub_2BA0F0_002ba0f0(p3fes::EEContext&);  // this slice
void fn_sub_2BA3A0_002ba3a0(p3fes::EEContext&);  // this slice
void fn_sub_2BA900_002ba900(p3fes::EEContext&);  // this slice
void fn_sub_2BB610_002bb610(p3fes::EEContext&);
void fn_sub_2BB9C0_002bb9c0(p3fes::EEContext&);  // this slice
void fn_sub_2BBAC0_002bbac0(p3fes::EEContext&);  // this slice
void fn_sub_2BC2F0_002bc2f0(p3fes::EEContext&);
void fn_btlDrawTexturedQuad_002bc9c0(p3fes::EEContext&);  // btlDrawTexturedQuad (replaced by another slice)
void fn_sub_2BCE10_002bce10(p3fes::EEContext&);  // this slice
void fn_sub_2BDE10_002bde10(p3fes::EEContext&);  // this slice
void fn_sub_2BDFB0_002bdfb0(p3fes::EEContext&);  // this slice
void fn_sub_2BFCB0_002bfcb0(p3fes::EEContext&);  // this slice
void fn_btlTargetGetSideMask_002d1600(p3fes::EEContext&);
void fn_sub_2D1A10_002d1a10(p3fes::EEContext&);
void fn_sub_2D1A70_002d1a70(p3fes::EEContext&);
void fn_sub_2D1DE0_002d1de0(p3fes::EEContext&);
void fn_sub_2D1FD0_002d1fd0(p3fes::EEContext&);
void fn_sub_2D2280_002d2280(p3fes::EEContext&);
void fn_sub_2D4040_002d4040(p3fes::EEContext&);
void fn_sub_2D6290_002d6290(p3fes::EEContext&);
void fn_datCalcIsHpSkill_002d6370(p3fes::EEContext&);
void fn_sub_2D63B0_002d63b0(p3fes::EEContext&);
void fn_sub_2DB650_002db650(p3fes::EEContext&);
void fn_sub_2FC520_002fc520(p3fes::EEContext&);
void fn_sub_2FDCF0_002fdcf0(p3fes::EEContext&);
void fn_sub_2FDD40_002fdd40(p3fes::EEContext&);
void fn_sub_2FF330_002ff330(p3fes::EEContext&);
void fn_datCalcGetHp_002ffd70(p3fes::EEContext&);
void fn_datCalcGetSp_002ffd80(p3fes::EEContext&);
void fn_datCalcGetMaxHp_002ffdf0(p3fes::EEContext&);
void fn_datCalcGetMaxSp_00300100(p3fes::EEContext&);
void fn_datCalcChkBadStatus_00300580(p3fes::EEContext&);
void fn_sub_308930_00308930(p3fes::EEContext&);
void fn_datCalcGetSkillList_00308bb0(p3fes::EEContext&);
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);
void fn_sub_30BC20_0030bc20(p3fes::EEContext&);
void fn_sub_3174E0_003174e0(p3fes::EEContext&);
void fn_sub_3176C0_003176c0(p3fes::EEContext&);
void fn_sub_317730_00317730(p3fes::EEContext&);
void fn_sub_317A20_00317a20(p3fes::EEContext&);
void fn_sub_318AD0_00318ad0(p3fes::EEContext&);
void fn_sub_318B90_00318b90(p3fes::EEContext&);
void fn_sub_318D10_00318d10(p3fes::EEContext&);
void fn_sub_318ED0_00318ed0(p3fes::EEContext&);
void fn_sub_321120_00321120(p3fes::EEContext&);
void fn_sub_321130_00321130(p3fes::EEContext&);
void fn_sub_321320_00321320(p3fes::EEContext&);
void fn_sub_324BD0_00324bd0(p3fes::EEContext&);
void fn_sub_3252A0_003252a0(p3fes::EEContext&);
void fn_sub_325500_00325500(p3fes::EEContext&);
void fn_sub_3257E0_003257e0(p3fes::EEContext&);
void fn_sub_325920_00325920(p3fes::EEContext&);
void fn_sub_325C10_00325c10(p3fes::EEContext&);
void fn_sub_325D60_00325d60(p3fes::EEContext&);
void fn_sub_325E40_00325e40(p3fes::EEContext&);
void fn_sub_326030_00326030(p3fes::EEContext&);
void fn_sub_3297A0_003297a0(p3fes::EEContext&);
void fn_sub_329ED0_00329ed0(p3fes::EEContext&);
void fn_sub_351BB0_00351bb0(p3fes::EEContext&);
void fn_sub_352C30_00352c30(p3fes::EEContext&);
void fn_sub_352C50_00352c50(p3fes::EEContext&);
void fn_sub_357EA0_00357ea0(p3fes::EEContext&);
void fn_sub_3B2CB0_003b2cb0(p3fes::EEContext&);
void fn_sub_45A430_0045a430(p3fes::EEContext&);
void fn_sub_45AF40_0045af40(p3fes::EEContext&);
void fn_sub_45AF70_0045af70(p3fes::EEContext&);
void fn_sub_4BDDE0_004bdde0(p3fes::EEContext&);
void fn_sub_4BE1E0_004be1e0(p3fes::EEContext&);
void fn_sub_4C69F0_004c69f0(p3fes::EEContext&);
void fn_sub_4C6AC0_004c6ac0(p3fes::EEContext&);
void fn_sub_4C6AF0_004c6af0(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_strcpy_00524270(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_atan2f_0052ea18(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {
namespace battle_fx {
namespace {

namespace core = ee::core;
namespace gen = ::p3fes::recomp_gen;

// --- R5900 integer results (32-bit operations sign-extend into the 64-bit register) ----------------------------
constexpr u64 sx(u32 v) { return core::sext32(v); }
constexpr u64 si(s32 v) { return static_cast<u64>(static_cast<s64>(v)); }  // a negative immediate
constexpr u64 addu(u64 a, u64 b) { return core::add32(a, b); }
constexpr u64 addiu(u64 a, s32 i) { return core::add32i(a, i); }
constexpr u64 subu(u64 a, u64 b) { return core::sub32(a, b); }
constexpr u64 lui(u32 i) { return core::lui(i); }
constexpr u64 sll(u64 a, unsigned n) { return core::sll(a, n); }
constexpr u64 srl(u64 a, unsigned n) { return core::srl(a, n); }
constexpr u64 sra(u64 a, unsigned n) { return core::sra(a, n); }
constexpr u64 sllv(u64 a, u64 n) { return core::sllv(a, n); }
constexpr u64 dsll(u64 a, unsigned n) { return core::dsll(a, n); }
constexpr u64 dsll32(u64 a, unsigned n) { return core::dsll32(a, n); }
constexpr u64 dsrl32(u64 a, unsigned n) { return core::dsrl32(a, n); }
constexpr u64 dsra32(u64 a, unsigned n) { return core::dsra32(a, n); }
constexpr u64 slt(u64 a, u64 b) { return core::slt(a, b); }
constexpr u64 sltu(u64 a, u64 b) { return core::sltu(a, b); }
constexpr u64 slti(u64 a, s32 i) { return core::slti(a, i); }
constexpr u64 sltiu(u64 a, s32 i) { return core::sltiu(a, i); }
// The branch tests on whole 64-bit registers (blez / bgtz / bltz / bgez).
constexpr bool lez(u64 a) { return static_cast<s64>(a) <= 0; }
constexpr bool gtz(u64 a) { return static_cast<s64>(a) > 0; }
constexpr bool ltz(u64 a) { return static_cast<s64>(a) < 0; }
constexpr bool gez(u64 a) { return static_cast<s64>(a) >= 0; }

// One GPR of the guest context (a 64-bit write keeps bits 64..127, as the EE does; lq writes all 128). Reads go
// through volatile lvalues and so does virtual time below (docs/PHASE5_AGENT_BRIEF.md, wave 10: MSVC /O2 can keep
// ctx.cycles or a register in a host register across a call to a small helper that charges; a volatile access is a
// compiler barrier under /volatile:ms and keeps every access real under clang-cl).
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

// The guest machine as the bodies see it: one named variable per register, the memory, FPU and HI/LO operations
// with the runtime's own semantics, the calls with the original links.
class Cpu {
public:
    explicit Cpu(EEContext& ctx) noexcept : c(ctx) {}

    EEContext& c;
    Gpr zero{c, 0}, at{c, 1}, v0{c, 2}, v1{c, 3}, a0{c, 4}, a1{c, 5}, a2{c, 6}, a3{c, 7};
    Gpr t0{c, 8}, t1{c, 9}, t2{c, 10}, t3{c, 11}, t4{c, 12}, t5{c, 13}, t6{c, 14}, t7{c, 15};
    Gpr s0{c, 16}, s1{c, 17}, s2{c, 18}, s3{c, 19}, s4{c, 20}, s5{c, 21}, s6{c, 22}, s7{c, 23};
    Gpr t8{c, 24}, t9{c, 25}, gp{c, 28}, sp{c, 29}, fp{c, 30}, ra{c, 31};

    // virtual time (ADR-0013); a check point may raise a fatal event that unwinds through the body
    void enter(u64 n) {
        rt::check_events(c);
        charge(n);
    }
    void charge(u64 n) noexcept {
        volatile u64& t = c.cycles;
        t = t + n;
    }
    void backedge() { rt::check_events(c); }

    // Loads and stores in the instruction's own form, `lw(rt, base, imm)` = `lw rt, imm(base)`, with the runtime's
    // semantics: the RAM / scratchpad / BIOS windows, the hardware bus, and the address-error / unmapped faults of
    // the recompiled body (a bad pointer stops both versions at the same instruction with the same registers).
    void lw(Gpr& d, const Gpr& b, s32 i) { rt::lw(c, d.r, b.r, i); }
    void lh(Gpr& d, const Gpr& b, s32 i) { rt::lh(c, d.r, b.r, i); }
    void lhu(Gpr& d, const Gpr& b, s32 i) { rt::lhu(c, d.r, b.r, i); }
    void lb(Gpr& d, const Gpr& b, s32 i) { rt::lb(c, d.r, b.r, i); }
    void lbu(Gpr& d, const Gpr& b, s32 i) { rt::lbu(c, d.r, b.r, i); }
    void ld(Gpr& d, const Gpr& b, s32 i) { rt::ld(c, d.r, b.r, i); }
    void lq(Gpr& d, const Gpr& b, s32 i) { rt::lq(c, d.r, b.r, i); }
    void sw(const Gpr& t, const Gpr& b, s32 i) { rt::sw(c, t.r, b.r, i); }
    void sh(const Gpr& t, const Gpr& b, s32 i) { rt::sh(c, t.r, b.r, i); }
    void sb(const Gpr& t, const Gpr& b, s32 i) { rt::sb(c, t.r, b.r, i); }
    void sd(const Gpr& t, const Gpr& b, s32 i) { rt::sd(c, t.r, b.r, i); }
    void sq(const Gpr& t, const Gpr& b, s32 i) { rt::sq(c, t.r, b.r, i); }

    // FPU (the runtime's instruction semantics: EE singles, ACC, FCR31 flags)
    void lwc1(unsigned f, const Gpr& b, s32 i) { rt::lwc1(c, f, b.r, i); }
    void swc1(unsigned f, const Gpr& b, s32 i) { rt::swc1(c, f, b.r, i); }
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
    void adda_s(unsigned s, unsigned t) noexcept { rt::adda_s(c, s, t); }
    void mula_s(unsigned s, unsigned t) noexcept { rt::mula_s(c, s, t); }
    void madd_s(unsigned d, unsigned s, unsigned t) noexcept { rt::madd_s(c, d, s, t); }
    void msub_s(unsigned d, unsigned s, unsigned t) noexcept { rt::msub_s(c, d, s, t); }
    void c_eq_s(unsigned s, unsigned t) noexcept { rt::c_eq_s(c, s, t); }
    void c_lt_s(unsigned s, unsigned t) noexcept { rt::c_lt_s(c, s, t); }
    void c_le_s(unsigned s, unsigned t) noexcept { rt::c_le_s(c, s, t); }
    bool cop1_cond() const noexcept { return rt::cop1_cond(c); }

    // HI/LO
    void mult(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::mult(c, d.r, s.r, t.r); }

    // calls: `jal fn` at pc ($ra = pc + 8; the delay slot's instruction is written before the call), `jalr target`
    // at pc (through the dispatch table, $ra = pc + 8), and a jump table's out-of-table target (a `jr` tail jump)
    void jal(u32 pc, rt::Fn fn) {
        rt::jal(c, pc);
        fn(c);
    }
    void jalr(u32 pc, u32 target) {
        rt::jalr(c, GPR_RA, pc);
        rt::lookup_func(target)(c);
    }
    void tail(u32 target) { rt::lookup_func(target)(c); }

    // --- the bodies (battle_fx.h groups them; each keeps its symbols/functions.json name) ---
    void sub_2B77C0();
    void sub_2B79E0();
    void sub_2B7BD0();
    void sub_2B7C50();
    void sub_2B8900();
    void sub_2B8970();
    void sub_2B8990();
    void sub_2B8B50();
    void sub_2B8B70();
    void sub_2B8C00();
    void sub_2B8D60();
    void sub_2B8DC0();
    void sub_2B8F40();
    void sub_2B90D0();
    void sub_2B9220();
    void sub_2B9300();
    void sub_2B9350();
    void sub_2B9370();
    void sub_2B93C0();
    void sub_2B9590();
    void sub_2B9600();
    void sub_2B9640();
    void sub_2B96E0();
    void sub_2B96F0();
    void sub_2B99D0();
    void sub_2B9B00();
    void sub_2B9C00();
    void sub_2B9D40();
    void sub_2B9E80();
    void sub_2B9F30();
    void sub_2BA000();
    void sub_2BA0D0();
    void sub_2BA0F0();
    void sub_2BA3A0();
    void sub_2BA900();
    void sub_2BAC00();
    void sub_2BACB0();
    void sub_2BAD60();
    void sub_2BAEC0();
    void sub_2BAF30();
    void sub_2BAF90();
    void sub_2BB050();
    void sub_2BB0B0();
    void sub_2BB290();
    void sub_2BB2F0();
    void sub_2BB3A0();
    void sub_2BB580();
    void nullsub_14();
    void sub_2BB770();
    void sub_2BB9C0();
    void sub_2BBAC0();
    void sub_2BBBC0();
    void sub_2BBDC0();
    void sub_2BBDF0();
    void sub_2BBE00();
    void sub_2BBF80();
    void sub_2BBFA0();
    void sub_2BC0E0();
    void sub_2BC680();
    void sub_2BC7B0();
    void sub_2BC7E0();
    void sub_2BC830();
    void sub_2BC890();
    void sub_2BC910();
    void sub_2BC950();
    void sub_2BCDE0();
    void sub_2BCE10();
    void sub_2BD060();
    void sub_2BD080();
    void sub_2BD210();
    void sub_2BD230();
    void sub_2BD2C0();
    void sub_2BD2E0();
    void sub_2BD460();
    void sub_2BD480();
    void sub_2BD590();
    void sub_2BD690();
    void sub_2BD780();
    void sub_2BD850();
    void sub_2BD8B0();
    void sub_2BDBA0();
    void sub_2BDBD0();
    void sub_2BDCD0();
    void sub_2BDDD0();
    void sub_2BDE10();
    void sub_2BDFB0();
    void nullsub_100();
    void sub_2BE2F0();
    void sub_2BE390();
    void sub_2BE580();
    void sub_2BE5D0();
    void sub_2BE5F0();
    void sub_2BE610();
    void sub_2BE620();
    void sub_2BE720();
    void nullsub_101();
    void sub_2BE9E0();
    void sub_2BEA80();
    void sub_2BECC0();
    void btlCommand_UpdateBattleCommandCalcTask();
    void btlCommand_UpdateBattleCommandDrawTask();
    void sub_2BF650();
    void nullsub_15();
    void nullsub_16();
    void nullsub_17();
    void nullsub_18();
    void sub_2BF9B0();
    void sub_2BFAB0();
    void sub_2BFAE0();
    void sub_2BFB20();
    void sub_2BFB50();
    void sub_2BFB90();
    void sub_2BFC00();
    void sub_2BFC50();
    void sub_2BFC70();
    void sub_2BFC90();
    void sub_2BFCB0();
    void sub_2BFF60();
};

// =================================================================================================================
// unit movement packets (btlFormation.c's neighbours: kinds 0xB00..0xB04, payload at packet +120)
// =================================================================================================================

// sub_2B77C0 [formation slot]: places a unit (model record) in a formation slot: when its slot byte +2544 is negative
// and its side +162 is 0 (party, taken flags at gBtl +2620) or 1 (enemies, +2636), scans the 24-byte slots of the
// formation row of the battle's formation id (gBtl +2616; 224-byte rows at 0x694F10, slot byte +0 = used) for the first
// used slot whose taken flag is not 1 (the scan stops after slot 4), marks it taken, stores it in +2544, moves the unit
// to the slot's x / z (slot +4 / +8; sub_2D2280, sub_27F650) and turns it toward the battle centre (sub_280870 side 2,
// sub_27FFB0, sub_2D1DE0, sub_27F680).
void Cpu::sub_2B77C0() {
    enter(9);
    sp = addiu(sp, -112);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    lb(v1, a0, 2544);
    if (ltz(v1)) {
        charge(6);
        lw(a2, gp, -18692);
        lhu(a1, a2, 2616);
        lbu(a0, s1, 162);
        v1 = 1;
        if (a0 == v1) goto L_002b79c0;
        charge(2);
        if (a0 != 0) {
            charge(2);
            goto L_002b79c0;
        }
        charge(10);
        s0 = 0;
        t0 = a1 & 0xFFFF;
        a3 = sll(t0, 3);
        a3 = subu(a3, t0);
        t0 = sll(a3, 5);
        a3 = lui(0x69);
        a3 = addiu(a3, 20240);
        t0 = addu(a3, t0);
        goto L_002b783c;
L_002b7834:
        charge(2);
        a3 = addiu(s0, 1);
        s0 = a3 & 0xFFFF;
L_002b783c:
        charge(8);
        s2 = s0 & 0xFFFF;
        a3 = sll(s2, 1);
        a3 = addu(a3, s2);
        a3 = sll(a3, 3);
        a3 = addu(t0, a3);
        lbu(a3, a3, 0);
        if (a3 != 0) {
            charge(2);
            if (a0 != v1) {
                charge(2);
                if (a0 != 0) {
                    charge(2);
                    goto L_002b7894;
                }
                charge(5);
                v0 = sll(s2, 2);
                v0 = addu(a2, v0);
                lw(v0, v0, 2620);
            } else {
                charge(3);
                v0 = sll(s2, 2);
                v0 = addu(a2, v0);
                lw(v0, v0, 2636);
            }
L_002b7894:
            charge(2);
            if (v0 != v1) goto L_002b78ac;
        }
        charge(4);
        a3 = s0 & 0xFFFF;
        a3 = slti(a3, 4);
        if (a3 != 0) {
            backedge();
            goto L_002b7834;
        }
L_002b78ac:
        charge(33);
        v1 = s0 & 0xFFFF;
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        a0 = sll(v0, 3);
        v1 = a1 & 0xFFFF;
        v0 = sll(v1, 3);
        v0 = subu(v0, v1);
        v1 = sll(v0, 5);
        v0 = lui(0x69);
        v0 = addiu(v0, 20244);
        v0 = addu(v0, v1);
        v0 = addu(a0, v0);
        lwc1(F0, v0, 0);
        swc1(F0, sp, 96);
        v0 = lui(0x69);
        v0 = addiu(v0, 20248);
        v0 = addu(v0, v1);
        v0 = addu(a0, v0);
        lwc1(F0, v0, 0);
        swc1(F0, sp, 104);
        a0 = addiu(s1, 148);
        a1 = addiu(s1, 150);
        a2 = addiu(sp, 96);
        jal(0x2B7908, gen::fn_sub_2D2280_002d2280);
        a0 = s1;
        a1 = addiu(sp, 96);
        jal(0x2B7918, gen::fn_sub_27F650_0027f650);
        lbu(v0, s1, 162);
        a0 = 1;
        if (v0 != a0) {
            charge(2);
            if (v0 != 0) {
                charge(2);
                goto L_002b7968;
            }
            charge(6);
            lw(v1, gp, -18692);
            v0 = sll(s2, 2);
            v0 = addu(v0, v1);
            sw(a0, v0, 2620);
        } else {
            charge(4);
            lw(v1, gp, -18692);
            v0 = sll(s2, 2);
            v0 = addu(v0, v1);
            sw(a0, v0, 2636);
        }
L_002b7968:
        charge(22);
        sb(s0, s1, 2544);
        a0 = 2;
        a1 = 1;
        a2 = addiu(sp, 80);
        a3 = 0;
        t0 = 0;
        t1 = a1;
        jal(0x2B7984, gen::fn_sub_280870_00280870);
        a0 = s1;
        a1 = addiu(sp, 96);
        jal(0x2B7994, gen::fn_sub_27FFB0_0027ffb0);
        a0 = addiu(sp, 64);
        a1 = addiu(sp, 96);
        a2 = addiu(sp, 80);
        jal(0x2B79A8, gen::fn_sub_2D1DE0_002d1de0);
        a0 = s1;
        a1 = addiu(sp, 64);
        jal(0x2B79B8, gen::fn_sub_27F680_0027f680);
    }
L_002b79c0:
    charge(7);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 112);
}

// sub_2B79E0 [approach update]: update (+108) of packet kind 0xB00 (payload {unit, target, f32 distance, u16 flags}):
// the direction from the target to the unit, scaled to `distance` minus the target's reach (sub_288DA0 row 9 +4 times
// the target's scale +44); flag 1 moves the unit (and its rider +2560), flag 2 the target. Returns 1 (also when the two
// stand on the same spot).
void Cpu::sub_2B79E0() {
    enter(31);
    sp = addiu(sp, -112);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s2 = a0;
    lw(s1, a0, 0);
    lw(s0, a0, 4);
    a0 = s0;
    a1 = s1;
    a2 = addiu(sp, 64);
    jal(0x2B7A0C, gen::fn_sub_280390_00280390);
    lwc1(F1, s1, 4);
    lwc1(F0, sp, 64);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 96);
    sw(zero, sp, 100);
    lwc1(F1, s1, 12);
    lwc1(F0, sp, 72);
    sub_s(F0, F1, F0);
    swc1(F0, sp, 104);
    a0 = addiu(sp, 96);
    a1 = a0;
    jal(0x2B7A40, gen::fn_sub_4C69F0_004c69f0);
    mtc1(zero, F1);
    lwc1(F0, sp, 96);
    c_eq_s(F1, F0);
    if (cop1_cond()) {
        charge(4);
        lwc1(F0, sp, 104);
        c_eq_s(F1, F0);
        if (!cop1_cond()) goto L_002b7a78;
        charge(3);
        v0 = 1;
        goto L_002b7bb4;
    }
L_002b7a78:
    charge(27);
    a0 = s0;
    a1 = 9;
    jal(0x2B7A80, gen::fn_sub_288DA0_00288da0);
    lh(v0, v0, 4);
    mtc1(v0, F0);
    cvt_s_w(F3, F0);
    lwc1(F2, s0, 44);
    lwc1(F1, s2, 8);
    mtc1(zero, F0);
    adda_s(F0, F1);
    msub_s(F1, F3, F2);
    lwc1(F0, sp, 96);
    mul_s(F3, F0, F1);
    swc1(F3, sp, 96);
    lwc1(F0, sp, 100);
    mul_s(F2, F0, F1);
    swc1(F2, sp, 100);
    lwc1(F0, sp, 104);
    mul_s(F1, F0, F1);
    swc1(F1, sp, 104);
    lhu(v0, s2, 12);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        charge(16);
        lwc1(F0, s1, 4);
        add_s(F0, F0, F3);
        swc1(F0, sp, 80);
        lwc1(F0, s1, 8);
        add_s(F0, F0, F2);
        swc1(F0, sp, 84);
        lwc1(F0, s1, 12);
        add_s(F0, F0, F1);
        swc1(F0, sp, 88);
        a0 = s1;
        a1 = addiu(sp, 80);
        jal(0x2B7B10, gen::fn_sub_27F650_0027f650);
        lw(a0, s1, 2560);
        if (a0 == 0) goto L_002b7b60;
        charge(15);
        lwc1(F1, a0, 4);
        lwc1(F0, sp, 96);
        add_s(F0, F1, F0);
        swc1(F0, sp, 80);
        lwc1(F1, a0, 8);
        lwc1(F0, sp, 100);
        add_s(F0, F1, F0);
        swc1(F0, sp, 84);
        lwc1(F1, a0, 12);
        lwc1(F0, sp, 104);
        add_s(F0, F1, F0);
        swc1(F0, sp, 88);
        a1 = addiu(sp, 80);
        jal(0x2B7B58, gen::fn_sub_27F650_0027f650);
    }
L_002b7b60:
    charge(4);
    lhu(v0, s2, 12);
    v0 = v0 & 0x2;
    if (v0 != 0) {
        charge(16);
        lwc1(F1, s0, 4);
        lwc1(F0, sp, 96);
        add_s(F0, F1, F0);
        swc1(F0, sp, 80);
        lwc1(F1, s0, 8);
        lwc1(F0, sp, 100);
        add_s(F0, F1, F0);
        swc1(F0, sp, 84);
        lwc1(F1, s0, 12);
        lwc1(F0, sp, 104);
        add_s(F0, F1, F0);
        swc1(F0, sp, 88);
        a0 = s0;
        a1 = addiu(sp, 80);
        jal(0x2B7BA8, gen::fn_sub_27F650_0027f650);
    }
    charge(1);
    v0 = 1;
L_002b7bb4:
    charge(7);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 112);
}

// sub_2B7BD0 [create approach]: creates packet kind 0xB00 (16-byte payload: a0, a1, $f12, (u16)a2) with update
// sub_2B79E0 (sub_27EC10 allocates packets through the RW heap).
void Cpu::sub_2B7BD0() {
    enter(30);
    sp = addiu(sp, -80);
    sd(ra, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F20, sp, 0);
    s2 = a0;
    s1 = a1;
    mov_s(F20, F12);
    s0 = a2;
    a0 = 2816;
    a1 = 16;
    jal(0x2B7C00, gen::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2B);
    v1 = addiu(v1, 31200);
    sw(v1, v0, 108);
    lw(v1, v0, 120);
    sw(s2, v1, 0);
    sw(s1, v1, 4);
    swc1(F20, v1, 8);
    sh(s0, v1, 12);
    ld(ra, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 80);
}

// sub_2B7C50 [spread update]: update (+108) of packet kind 0xB01 (payload {actor, apply, mode}): keeps units 300.0
// apart -- for a party actor (side 0) its unit against the target (sub_2FDD40 / sub_2FDCF0 / sub_284040 / sub_27F940
// choose the spot), for an enemy actor (side 1) its members (+56.., count +106) against the party units (gBtl +340 /
// +348 lists, linked by +2608) -- moving and turning them (sub_27F650 / sub_27F680 / sub_2812B0 / sub_288110) and
// raising gBtl's flags +12 0x400000 and +24 0x2..0x1E when something moved. Returns 1.
void Cpu::sub_2B7C50() {
    enter(22);
    sp = addiu(sp, -336);
    sd(ra, sp, 144);
    sq(s6, sp, 128);
    sq(s5, sp, 112);
    sq(s4, sp, 96);
    sq(s3, sp, 80);
    sq(s2, sp, 64);
    sq(s1, sp, 48);
    sq(s0, sp, 32);
    swc1(F24, sp, 16);
    swc1(F23, sp, 12);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s3 = a0;
    lw(s0, a0, 0);
    lhu(s6, s0, 110);
    lw(v0, s0, 48);
    lbu(v0, v0, 162);
    v1 = 1;
    if (v0 != v1) {
        charge(2);
        if (v0 != 0) {
            charge(2);
            goto L_002b88b4;
        }
        charge(11);
        s4 = dsll32(s6, 16);
        s4 = dsra32(s4, 16);
        a0 = s4;
        jal(0x2B7CC4, gen::fn_datCalcIsHpSkill_002d6370);
        a0 = s0;
        jal(0x2B7CD0, gen::fn_sub_2D6290_002d6290);
        a1 = 1;
        if (v0 == a1) {
            charge(3);
            lw(v0, s0, 56);
            if (s0 == v0) {
                charge(3);
                v0 = a1;
                goto L_002b88b8;
            }
            charge(9);
            lw(s2, s0, 48);
            lw(s1, v0, 48);
            lw(s0, s2, 2560);
            a0 = s2;
            a1 = s1;
            jal(0x2B7D10, gen::fn_sub_2FDD40_002fdd40);
            if (v0 != 0) {
                charge(9);
                lw(a0, gp, -18692);
                lw(v1, a0, 12);
                v0 = lui(0x40);
                v0 = v1 | v0;
                sw(v0, a0, 12);
                lw(v1, gp, -18692);
                lhu(v0, v1, 24);
                v0 = v0 | 0xE;
                sh(v0, v1, 24);
            }
            charge(16);
            a0 = s2;
            a1 = addiu(sp, 320);
            jal(0x2B7D4C, gen::fn_sub_27FFB0_0027ffb0);
            a0 = s1;
            a1 = s2;
            a2 = addiu(sp, 304);
            jal(0x2B7D60, gen::fn_sub_2802D0_002802d0);
            lwc1(F0, s2, 8);
            swc1(F0, sp, 308);
            swc1(F0, sp, 324);
            lw(v1, s3, 8);
            v0 = 1;
            if (v1 == v0) {
                charge(2);
                if (s1 == s2) goto L_002b7ee4;
                charge(6);
                a0 = s2;
                a1 = s1;
                jal(0x2B7D94, gen::fn_sub_2FDCF0_002fdcf0);
                if (v0 == 0) goto L_002b7ee4;
                charge(6);
                lw(v0, gp, -18692);
                lw(v1, v0, 12);
                v0 = lui(0x20);
                v0 = v1 & v0;
                if (v0 == 0) {
                    charge(59);
                    a0 = s1;
                    a1 = addiu(sp, 224);
                    jal(0x2B7DC4, gen::fn_sub_27FFB0_0027ffb0);
                    a0 = addiu(sp, 160);
                    a1 = addiu(sp, 224);
                    a2 = addiu(sp, 320);
                    jal(0x2B7DD8, gen::fn_sub_2D1DE0_002d1de0);
                    lwc1(F0, s1, 128);
                    lwc1(F1, s1, 44);
                    mul_s(F0, F0, F1);
                    swc1(F0, sp, 256);
                    lwc1(F0, s1, 132);
                    mul_s(F0, F0, F1);
                    swc1(F0, sp, 260);
                    lwc1(F0, s1, 136);
                    mul_s(F0, F0, F1);
                    swc1(F0, sp, 264);
                    a0 = addiu(sp, 272);
                    a1 = addiu(sp, 256);
                    a2 = 1;
                    a3 = addiu(sp, 160);
                    jal(0x2B7E18, gen::fn_sub_4BE1E0_004be1e0);
                    lwc1(F1, sp, 224);
                    lwc1(F0, sp, 272);
                    sub_s(F0, F1, F0);
                    swc1(F0, sp, 256);
                    lwc1(F1, sp, 228);
                    lwc1(F0, sp, 276);
                    sub_s(F0, F1, F0);
                    swc1(F0, sp, 260);
                    lwc1(F1, sp, 232);
                    lwc1(F0, sp, 280);
                    sub_s(F0, F1, F0);
                    swc1(F0, sp, 264);
                    lwc1(F0, s1, 8);
                    swc1(F0, sp, 228);
                    swc1(F0, sp, 260);
                    a0 = s1;
                    a1 = addiu(sp, 256);
                    jal(0x2B7E64, gen::fn_sub_27F650_0027f650);
                    a0 = addiu(sp, 160);
                    a1 = addiu(sp, 256);
                    a2 = addiu(s2, 4);
                    jal(0x2B7E78, gen::fn_sub_2D1DE0_002d1de0);
                    a0 = s1;
                    a1 = addiu(sp, 160);
                    jal(0x2B7E88, gen::fn_sub_27F680_0027f680);
                    ld(v0, sp, 224);
                    lwc1(F0, sp, 232);
                    sd(v0, sp, 304);
                    swc1(F0, sp, 312);
                } else {
                    charge(9);
                    a0 = addiu(sp, 160);
                    a1 = addiu(sp, 304);
                    a2 = addiu(sp, 320);
                    jal(0x2B7EB4, gen::fn_sub_2D1DE0_002d1de0);
                    a0 = s1;
                    a1 = addiu(sp, 160);
                    jal(0x2B7EC4, gen::fn_sub_27F680_0027f680);
                }
                charge(6);
                a0 = s1;
                jal(0x2B7ED0, gen::fn_sub_2812B0_002812b0);
                a0 = s1;
                jal(0x2B7EDC, gen::fn_sub_288110_00288110);
            }
L_002b7ee4:
            charge(4);
            lw(v1, s3, 4);
            v0 = 1;
            if (v1 != v0) goto L_002b88b4;
            charge(20);
            lwc1(F1, sp, 320);
            lwc1(F0, sp, 304);
            sub_s(F0, F1, F0);
            swc1(F0, sp, 272);
            lwc1(F1, sp, 328);
            lwc1(F0, sp, 312);
            sub_s(F0, F1, F0);
            swc1(F0, sp, 280);
            sw(zero, sp, 276);
            a0 = addiu(sp, 272);
            a1 = a0;
            jal(0x2B7F20, gen::fn_sub_4C69F0_004c69f0);
            mov_s(F24, F0);
            lwc1(F1, s2, 144);
            lwc1(F0, s2, 44);
            mul_s(F23, F1, F0);
            mtc1(zero, F22);
            if (s0 != 0) {
                charge(23);
                s3 = dsll32(s6, 16);
                s3 = dsra32(s3, 16);
                a0 = s0;
                a1 = s3;
                a2 = 1;
                jal(0x2B7F58, gen::fn_sub_2D63B0_002d63b0);
                s5 = v0;
                a0 = s0;
                a1 = s2;
                a2 = s3;
                a3 = 1;
                jal(0x2B7F74, gen::fn_sub_284040_00284040);
                s3 = dsll32(v0, 16);
                s3 = dsra32(s3, 16);
                lwc1(F2, s2, 144);
                lwc1(F1, s2, 44);
                mov_s(F0, F22);
                adda_s(F0, F24);
                msub_s(F24, F2, F1);
                if (s5 == 0) {
                    charge(11);
                    a0 = s0;
                    a1 = s2;
                    a2 = s4;
                    a3 = 1;
                    jal(0x2B7FB0, gen::fn_sub_284040_00284040);
                    v1 = dsll32(v0, 16);
                    v1 = dsra32(v1, 16);
                    v0 = 3;
                    if (v1 != v0) {
                        charge(3);
                        v0 = 1;
                        if (v1 == v0) goto L_002b8020;
                        charge(3);
                        v0 = 2;
                        if (v1 != v0) {
                            charge(2);
                            if (v1 == 0) goto L_002b7ff4;
                            charge(2);
                            goto L_002b8070;
                        }
L_002b7ff4:
                        charge(11);
                        a0 = s0;
                        a1 = s2;
                        a2 = s1;
                        a3 = s3;
                        t0 = addiu(sp, 256);
                        t1 = 0;
                        t2 = 0;
                        jal(0x2B8010, gen::fn_sub_27F940_0027f940);
                        goto L_002b8070;
                    }
L_002b8020:
                    charge(11);
                    a0 = s0;
                    a1 = s2;
                    a2 = s1;
                    a3 = s3;
                    t0 = addiu(sp, 256);
                    t1 = 0;
                    t2 = 1;
                    jal(0x2B803C, gen::fn_sub_27F940_0027f940);
                } else {
                    charge(9);
                    a0 = s0;
                    a1 = s2;
                    a2 = s1;
                    a3 = s3;
                    t0 = addiu(sp, 256);
                    t1 = 0;
                    t2 = 2;
                    jal(0x2B8068, gen::fn_sub_27F940_0027f940);
                }
L_002b8070:
                charge(19);
                lwc1(F1, sp, 256);
                lwc1(F0, sp, 304);
                sub_s(F0, F1, F0);
                swc1(F0, sp, 272);
                lwc1(F1, sp, 264);
                lwc1(F0, sp, 312);
                sub_s(F0, F1, F0);
                swc1(F0, sp, 280);
                sw(zero, sp, 276);
                a0 = addiu(sp, 272);
                a1 = a0;
                jal(0x2B809C, gen::fn_sub_4C69F0_004c69f0);
                lwc1(F2, s0, 44);
                lwc1(F1, s0, 144);
                mul_s(F20, F1, F2);
                sub_s(F21, F0, F20);
                if (s5 == 0) {
                    charge(10);
                    lwc1(F1, s2, 144);
                    lwc1(F0, s2, 44);
                    mtc1(zero, F2);
                    adda_s(F2, F24);
                    madd_s(F1, F1, F0);
                    add_s(F0, F21, F20);
                    c_lt_s(F1, F0);
                    if (cop1_cond()) {
                        charge(2);
                        goto L_002b81d0;
                    }
                    charge(22);
                    mov_s(F24, F21);
                    mov_s(F23, F20);
                    lwc1(F1, sp, 320);
                    lwc1(F0, sp, 256);
                    sub_s(F0, F1, F0);
                    swc1(F0, sp, 240);
                    lwc1(F1, sp, 324);
                    lwc1(F0, sp, 260);
                    sub_s(F0, F1, F0);
                    swc1(F0, sp, 244);
                    lwc1(F1, sp, 328);
                    lwc1(F0, sp, 264);
                    sub_s(F0, F1, F0);
                    swc1(F0, sp, 248);
                    swc1(F2, sp, 244);
                    a0 = addiu(sp, 240);
                    a1 = a0;
                    jal(0x2B8130, gen::fn_sub_4C69F0_004c69f0);
                    mov_s(F22, F0);
                    goto L_002b81d0;
                }
                charge(31);
                mov_s(F23, F20);
                a0 = s0;
                a1 = s2;
                a2 = 0;
                a3 = si(-1);
                t0 = addiu(sp, 256);
                t1 = 0;
                t2 = 0;
                jal(0x2B8164, gen::fn_sub_27F940_0027f940);
                lwc1(F0, sp, 320);
                swc1(F0, sp, 256);
                lwc1(F1, sp, 324);
                swc1(F1, sp, 260);
                sub_s(F0, F0, F0);
                swc1(F0, sp, 240);
                sub_s(F0, F1, F1);
                swc1(F0, sp, 244);
                lwc1(F1, sp, 264);
                lwc1(F0, sp, 328);
                sub_s(F0, F1, F0);
                swc1(F0, sp, 248);
                a0 = addiu(sp, 240);
                jal(0x2B81A0, gen::fn_sub_4C6AC0_004c6ac0);
                mov_s(F22, F0);
                add_s(F1, F21, F20);
                add_s(F0, F0, F1);
                c_le_s(F0, F24);
                if (cop1_cond()) {
                    charge(3);
                    mtc1(zero, F22);
                    goto L_002b81d0;
                }
                charge(1);
                mov_s(F24, F21);
            }
L_002b81d0:
            charge(10);
            lwc1(F1, s1, 44);
            lwc1(F0, s1, 144);
            mul_s(F1, F0, F1);
            sub_s(F24, F24, F1);
            v0 = lui(0x4396);
            mtc1(v0, F0);
            c_lt_s(F24, F0);
            if (cop1_cond()) {
                charge(2);
                mov_s(F24, F0);
                s5 = 1;
            }
            charge(2);
            if (s5 == 0) goto L_002b88b4;
            charge(27);
            add_s(F0, F24, F23);
            add_s(F0, F0, F1);
            add_s(F1, F0, F22);
            lwc1(F0, sp, 272);
            mul_s(F3, F0, F1);
            swc1(F3, sp, 272);
            lwc1(F0, sp, 276);
            mul_s(F2, F0, F1);
            swc1(F2, sp, 276);
            lwc1(F0, sp, 280);
            mul_s(F1, F0, F1);
            swc1(F1, sp, 280);
            lwc1(F0, sp, 304);
            add_s(F0, F0, F3);
            swc1(F0, sp, 256);
            lwc1(F0, sp, 308);
            add_s(F0, F0, F2);
            swc1(F0, sp, 260);
            lwc1(F0, sp, 312);
            add_s(F0, F0, F1);
            swc1(F0, sp, 264);
            a0 = s2;
            a1 = addiu(sp, 256);
            jal(0x2B8264, gen::fn_sub_27F650_0027f650);
            goto L_002b88b4;
        }
        charge(6);
        lw(a0, gp, -18692);
        lw(v1, a0, 12);
        v0 = lui(0x20);
        v0 = v1 & v0;
        if (v0 == 0) {
            charge(4);
            lw(s2, s0, 48);
            lw(v0, s3, 8);
            if (v0 == a1) {
                charge(3);
                s3 = 0;
                for (;;) {  // L_002b8318
                    charge(5);
                    v1 = s3 & 0xFFFF;
                    lhu(v0, s0, 106);
                    v0 = slt(v1, v0);
                    if (v0 == 0) break;
                    backedge();
                    charge(8);
                    v0 = s3 & 0xFFFF;
                    v0 = sll(v0, 2);
                    v0 = addu(s0, v0);
                    lw(s1, v0, 56);
                    lhu(v0, s1, 26);
                    v0 = v0 & 0x1;
                    if (v0 != 0) {
                        charge(2);
                        if (s1 == s0) goto L_002b8310;
                        charge(16);
                        lw(v0, s1, 48);
                        a0 = addiu(sp, 160);
                        a1 = addiu(v0, 4);
                        a2 = addiu(s2, 4);
                        jal(0x2B82E0, gen::fn_sub_2D1DE0_002d1de0);
                        lw(a0, s1, 48);
                        a1 = addiu(sp, 160);
                        jal(0x2B82F0, gen::fn_sub_27F680_0027f680);
                        lw(a0, s1, 48);
                        jal(0x2B82FC, gen::fn_sub_2812B0_002812b0);
                        lw(a0, s1, 48);
                        jal(0x2B8308, gen::fn_sub_288110_00288110);
                    }
L_002b8310:
                    charge(2);
                    v0 = addiu(s3, 1);
                    s3 = v0 & 0xFFFF;
                }
            }
            charge(33);
            a0 = s2;
            a1 = addiu(sp, 320);
            jal(0x2B8334, gen::fn_sub_27FFB0_0027ffb0);
            a0 = 2;
            a1 = 0;
            a2 = addiu(sp, 304);
            a3 = 0;
            t0 = 0;
            t1 = 1;
            jal(0x2B8354, gen::fn_sub_280870_00280870);
            lwc1(F0, s2, 8);
            swc1(F0, sp, 308);
            swc1(F0, sp, 324);
            ld(v0, sp, 304);
            lwc1(F0, sp, 312);
            sd(v0, sp, 208);
            swc1(F0, sp, 216);
            mtc1(zero, F20);
            s0 = 1;
            lwc1(F0, sp, 320);
            swc1(F0, sp, 200);
            lwc1(F0, sp, 328);
            swc1(F0, sp, 204);
            lwc1(F0, sp, 304);
            swc1(F0, sp, 184);
            lwc1(F0, sp, 312);
            swc1(F0, sp, 188);
            lw(v0, gp, -18692);
            lw(s1, v0, 348);
            for (;;) {  // L_002b8464
                charge(2);
                if (s1 == 0) break;
                backedge();
                charge(4);
                lw(v0, s1, 156);
                v0 = v0 & 0x8;
                if (v0 != 0) {
                    charge(29);
                    a0 = s1;
                    a1 = s2;
                    a2 = addiu(sp, 224);
                    jal(0x2B83CC, gen::fn_sub_2802D0_002802d0);
                    lwc1(F0, sp, 224);
                    swc1(F0, sp, 192);
                    lwc1(F0, sp, 232);
                    swc1(F0, sp, 196);
                    a0 = addiu(sp, 200);
                    a1 = addiu(sp, 184);
                    a2 = addiu(sp, 192);
                    a3 = addiu(sp, 176);
                    jal(0x2B83F4, gen::fn_sub_2D1FD0_002d1fd0);
                    lwc1(F1, sp, 200);
                    lwc1(F0, sp, 176);
                    sub_s(F0, F1, F0);
                    swc1(F0, sp, 192);
                    lwc1(F1, sp, 204);
                    lwc1(F0, sp, 180);
                    sub_s(F0, F1, F0);
                    swc1(F0, sp, 196);
                    a0 = addiu(sp, 192);
                    jal(0x2B8420, gen::fn_sub_4C6AF0_004c6af0);
                    c_lt_s(F0, F20);
                    if (!cop1_cond()) {
                        charge(3);
                        v0 = 1;
                        if (s0 != v0) goto L_002b8460;
                    }
                    charge(8);
                    lwc1(F1, sp, 176);
                    swc1(F1, sp, 208);
                    lwc1(F1, sp, 324);
                    swc1(F1, sp, 212);
                    lwc1(F1, sp, 180);
                    swc1(F1, sp, 216);
                    mov_s(F20, F0);
                    s0 = 0;
                }
L_002b8460:
                charge(1);
                lw(s1, s1, 2608);
            }
            charge(12);
            lwc1(F1, s2, 144);
            lwc1(F0, s2, 44);
            mtc1(zero, F2);
            adda_s(F2, F20);
            msub_s(F0, F1, F0);
            v0 = lui(0x4396);
            mtc1(v0, F22);
            c_lt_s(F0, F22);
            if (!cop1_cond()) goto L_002b88b4;
            charge(45);
            lwc1(F1, sp, 320);
            lwc1(F0, sp, 208);
            sub_s(F0, F1, F0);
            swc1(F0, sp, 272);
            lwc1(F21, sp, 212);
            lwc1(F0, sp, 324);
            sub_s(F0, F0, F21);
            swc1(F0, sp, 276);
            lwc1(F20, sp, 216);
            lwc1(F0, sp, 328);
            sub_s(F0, F0, F20);
            swc1(F0, sp, 280);
            swc1(F2, sp, 276);
            a0 = addiu(sp, 272);
            a1 = a0;
            jal(0x2B84D8, gen::fn_sub_4C69F0_004c69f0);
            lwc1(F2, s2, 144);
            lwc1(F1, s2, 44);
            mtc1(zero, F0);
            adda_s(F0, F22);
            madd_s(F1, F2, F1);
            lwc1(F0, sp, 272);
            mul_s(F3, F0, F1);
            swc1(F3, sp, 272);
            lwc1(F0, sp, 276);
            mul_s(F2, F0, F1);
            swc1(F2, sp, 276);
            lwc1(F0, sp, 280);
            mul_s(F1, F0, F1);
            swc1(F1, sp, 280);
            lwc1(F0, sp, 208);
            add_s(F0, F0, F3);
            swc1(F0, sp, 256);
            add_s(F0, F21, F2);
            swc1(F0, sp, 260);
            add_s(F0, F20, F1);
            swc1(F0, sp, 264);
            a0 = s2;
            a1 = addiu(sp, 256);
            jal(0x2B8540, gen::fn_sub_27F650_0027f650);
            goto L_002b88b4;
        }
        charge(4);
        lw(v0, a0, 16);
        v0 = v0 & 0x80;
        if (v0 == 0) goto L_002b88b4;
        charge(3);
        lw(s0, a0, 340);
        for (;;) {  // L_002b85c0
            charge(2);
            if (s0 == 0) break;
            backedge();
            charge(4);
            lw(v0, s0, 156);
            v0 = v0 & 0x8;
            if (v0 != 0) {
                charge(16);
                a0 = s0;
                a1 = addiu(sp, 256);
                a2 = 0;
                a3 = 0;
                jal(0x2B858C, gen::fn_sub_27F7C0_0027f7c0);
                lwc1(F1, sp, 264);
                v0 = lui(0x4348);
                mtc1(v0, F0);
                add_s(F0, F1, F0);
                swc1(F0, sp, 264);
                a0 = s0;
                a1 = addiu(sp, 256);
                jal(0x2B85B4, gen::fn_sub_27F650_0027f650);
            }
            charge(1);
            lw(s0, s0, 2608);
        }
        charge(11);
        lw(a0, gp, -18692);
        lw(v1, a0, 12);
        v0 = lui(0x40);
        v0 = v1 | v0;
        sw(v0, a0, 12);
        lw(v1, gp, -18692);
        lhu(v0, v1, 24);
        v0 = v0 | 0x6;
        sh(v0, v1, 24);
    } else {
        charge(3);
        lhu(v0, s0, 106);
        if (v0 == v1) goto L_002b88b4;
        charge(6);
        lw(v0, gp, -18692);
        lw(v1, v0, 12);
        v0 = lui(0x20);
        v0 = v1 & v0;
        if (v0 != 0) goto L_002b88b4;
        charge(7);
        a0 = addiu(s0, 56);
        jal(0x2B861C, gen::fn_btlTargetGetSideMask_002d1600);
        s4 = v0 & 0xFFFF;
        v0 = 1;
        if (s4 != v0) goto L_002b88b4;
        charge(13);
        s2 = 0;
        lw(s1, s0, 48);
        a0 = s1;
        a1 = addiu(sp, 320);
        jal(0x2B8644, gen::fn_sub_27FFB0_0027ffb0);
        lwc1(F1, s1, 144);
        lwc1(F0, s1, 44);
        mul_s(F20, F1, F0);
        lw(v0, s3, 8);
        a1 = 1;
        if (v0 == a1) {
            charge(11);
            a0 = s4;
            a2 = addiu(sp, 304);
            a3 = 0;
            t0 = 0;
            t1 = a1;
            jal(0x2B867C, gen::fn_sub_280870_00280870);
            mtc1(zero, F21);
            s3 = 0;
            for (;;) {  // L_002b8728
                charge(5);
                v1 = s3 & 0xFFFF;
                lhu(v0, s0, 106);
                v0 = slt(v1, v0);
                if (v0 == 0) break;
                backedge();
                charge(8);
                v0 = s3 & 0xFFFF;
                v0 = sll(v0, 2);
                v0 = addu(s0, v0);
                lw(v1, v0, 56);
                lhu(v0, v1, 26);
                v0 = v0 & 0x1;
                if (v0 != 0) {
                    charge(22);
                    lw(a0, v1, 48);
                    a1 = addiu(sp, 224);
                    jal(0x2B86BC, gen::fn_sub_280050_00280050);
                    lwc1(F1, sp, 304);
                    lwc1(F0, sp, 224);
                    sub_s(F0, F1, F0);
                    swc1(F0, sp, 272);
                    lwc1(F1, sp, 308);
                    lwc1(F0, sp, 228);
                    sub_s(F0, F1, F0);
                    swc1(F0, sp, 276);
                    lwc1(F1, sp, 312);
                    lwc1(F0, sp, 232);
                    sub_s(F0, F1, F0);
                    swc1(F0, sp, 280);
                    a0 = addiu(sp, 272);
                    jal(0x2B86F8, gen::fn_sub_4C6AC0_004c6ac0);
                    c_le_s(F0, F21);
                    if (cop1_cond()) goto L_002b8720;
                    charge(5);
                    ld(v0, sp, 224);
                    lwc1(F1, sp, 232);
                    sd(v0, sp, 288);
                    swc1(F1, sp, 296);
                    mov_s(F21, F0);
                }
L_002b8720:
                charge(2);
                v0 = addiu(s3, 1);
                s3 = v0 & 0xFFFF;
            }
            charge(15);
            a0 = addiu(sp, 160);
            a1 = addiu(sp, 320);
            a2 = addiu(sp, 288);
            jal(0x2B8748, gen::fn_sub_2D1DE0_002d1de0);
            a0 = s1;
            a1 = addiu(sp, 160);
            jal(0x2B8758, gen::fn_sub_27F680_0027f680);
            a0 = s1;
            jal(0x2B8764, gen::fn_sub_2812B0_002812b0);
            a0 = s1;
            jal(0x2B8770, gen::fn_sub_288110_00288110);
        }
        charge(4);
        lw(v0, gp, -18692);
        lw(s0, v0, 340);
        for (;;) {  // L_002b8880
            charge(2);
            if (s0 == 0) break;
            backedge();
            charge(4);
            lw(v0, s0, 156);
            v0 = v0 & 0x8;
            if (v0 != 0) {
                charge(27);
                a0 = s0;
                a1 = s1;
                a2 = addiu(sp, 304);
                jal(0x2B87A4, gen::fn_sub_2802D0_002802d0);
                lwc1(F1, sp, 304);
                lwc1(F0, sp, 320);
                sub_s(F0, F1, F0);
                swc1(F0, sp, 272);
                lwc1(F1, sp, 312);
                lwc1(F0, sp, 328);
                sub_s(F0, F1, F0);
                swc1(F0, sp, 280);
                sw(zero, sp, 276);
                a0 = addiu(sp, 272);
                a1 = a0;
                jal(0x2B87D8, gen::fn_sub_4C69F0_004c69f0);
                lwc1(F2, gp, -32544);
                sub_s(F1, F0, F20);
                mtc1(zero, F4);
                adda_s(F4, F20);
                madd_s(F1, F2, F1);
                c_lt_s(F1, F0);
                if (!cop1_cond()) goto L_002b887c;
                charge(6);
                v0 = lui(0x4396);
                mtc1(v0, F0);
                c_le_s(F1, F0);
                if (cop1_cond()) goto L_002b887c;
                charge(24);
                lwc1(F0, sp, 272);
                mul_s(F3, F0, F1);
                swc1(F3, sp, 272);
                lwc1(F0, sp, 276);
                mul_s(F2, F0, F1);
                swc1(F2, sp, 276);
                lwc1(F0, sp, 280);
                mul_s(F1, F0, F1);
                swc1(F1, sp, 280);
                lwc1(F0, sp, 320);
                add_s(F0, F0, F3);
                swc1(F0, sp, 256);
                lwc1(F0, sp, 324);
                add_s(F0, F0, F2);
                swc1(F0, sp, 260);
                lwc1(F0, sp, 328);
                add_s(F0, F0, F1);
                swc1(F0, sp, 264);
                swc1(F4, sp, 260);
                a0 = s0;
                a1 = addiu(sp, 256);
                jal(0x2B8870, gen::fn_sub_27F650_0027f650);
                s2 = 1;
            }
L_002b887c:
            charge(1);
            lw(s0, s0, 2608);
        }
        charge(2);
        if (s2 == 0) goto L_002b88b4;
        charge(9);
        lw(a0, gp, -18692);
        lw(v1, a0, 12);
        v0 = lui(0x40);
        v0 = v1 | v0;
        sw(v0, a0, 12);
        lw(v1, gp, -18692);
        lhu(v0, v1, 24);
        v0 = v0 | 0x1E;
        sh(v0, v1, 24);
    }
L_002b88b4:
    charge(1);
    v0 = 1;
L_002b88b8:
    charge(16);
    ld(ra, sp, 144);
    lq(s6, sp, 128);
    lq(s5, sp, 112);
    lq(s4, sp, 96);
    lq(s3, sp, 80);
    lq(s2, sp, 64);
    lq(s1, sp, 48);
    lq(s0, sp, 32);
    lwc1(F24, sp, 16);
    lwc1(F23, sp, 12);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 336);
}

// sub_2B8900 [create spread]: creates packet kind 0xB01 (12-byte payload: a0, a1, a2) with update sub_2B7C50.
void Cpu::sub_2B8900() {
    enter(26);
    sp = addiu(sp, -64);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    a0 = 2817;
    a1 = 12;
    jal(0x2B8928, gen::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2B);
    v1 = addiu(v1, 31824);
    sw(v1, v0, 108);
    lw(v1, v0, 120);
    sw(s2, v1, 0);
    sw(s1, v1, 4);
    sw(s0, v1, 8);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
}

// sub_2B8970 [face start]: start (+104) of packet kind 0xB02: payload[0]'s busy count +160 += 1.
void Cpu::sub_2B8970() {
    enter(6);
    lw(a0, a0, 0);
    lhu(v1, a0, 160);
    v1 = addiu(v1, 1);
    sh(v1, a0, 160);
}

// sub_2B8990 [face update]: update (+108) of packet kind 0xB02 (payload {unit, target actor, other, s16 mode}): places
// the unit at its attack spot relative to the target (sub_284040 / sub_2D63B0 pick the case, sub_27F940 the position
// and direction) and turns it (sub_27F680 / sub_27F650). Returns 1.
void Cpu::sub_2B8990() {
    enter(31);
    sp = addiu(sp, -144);
    sd(ra, sp, 96);
    sq(s5, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s4 = a0;
    lw(s3, a0, 0);
    lw(v0, a0, 4);
    lw(s2, v0, 48);
    lh(v1, a0, 12);
    lw(v0, a0, 8);
    s0 = sltu(zero, v0);
    s5 = v1;
    a0 = s3;
    a1 = s2;
    a2 = s5;
    a3 = s0;
    jal(0x2B89E0, gen::fn_sub_284040_00284040);
    s1 = dsll32(v0, 16);
    s1 = dsra32(s1, 16);
    a0 = s3;
    a1 = s5;
    a2 = s0;
    jal(0x2B89FC, gen::fn_sub_2D63B0_002d63b0);
    if (v0 == 0) {
        charge(11);
        a0 = s3;
        a1 = s2;
        a2 = s5;
        a3 = s0;
        jal(0x2B8A1C, gen::fn_sub_284040_00284040);
        v1 = dsll32(v0, 16);
        v1 = dsra32(v1, 16);
        v0 = 3;
        if (v1 != v0) {
            charge(3);
            v0 = 1;
            if (v1 == v0) goto L_002b8a8c;
            charge(3);
            v0 = 2;
            if (v1 != v0) {
                charge(2);
                if (v1 == 0) goto L_002b8a60;
                charge(2);
                goto L_002b8ab0;
            }
L_002b8a60:
            charge(11);
            a0 = s3;
            a1 = s2;
            a2 = 0;
            a3 = s1;
            t0 = addiu(sp, 128);
            t1 = addiu(sp, 112);
            t2 = 0;
            jal(0x2B8A7C, gen::fn_sub_27F940_0027f940);
            goto L_002b8ab0;
        }
L_002b8a8c:
        charge(9);
        a0 = s3;
        a1 = s2;
        a2 = 0;
        a3 = s1;
        t0 = addiu(sp, 128);
        t1 = addiu(sp, 112);
        t2 = 1;
        jal(0x2B8AA8, gen::fn_sub_27F940_0027f940);
L_002b8ab0:
        charge(10);
        a0 = s3;
        a1 = addiu(sp, 112);
        jal(0x2B8AB8, gen::fn_sub_27F680_0027f680);
        a0 = s3;
        a1 = addiu(sp, 128);
        jal(0x2B8AC8, gen::fn_sub_27F650_0027f650);
    } else {
        charge(18);
        lw(v0, s4, 8);
        a0 = s3;
        a1 = s2;
        lw(a2, v0, 48);
        a3 = s1;
        t0 = addiu(sp, 128);
        t1 = addiu(sp, 112);
        t2 = 2;
        jal(0x2B8AF8, gen::fn_sub_27F940_0027f940);
        a0 = s3;
        a1 = addiu(sp, 112);
        jal(0x2B8B08, gen::fn_sub_27F680_0027f680);
        a0 = s3;
        a1 = addiu(sp, 128);
        jal(0x2B8B18, gen::fn_sub_27F650_0027f650);
    }
    charge(11);
    v0 = 1;
    ld(ra, sp, 96);
    lq(s5, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 144);
}

// sub_2B8B50 [face end]: end (+112) of packet kind 0xB02: payload[0]'s busy count +160 -= 1.
void Cpu::sub_2B8B50() {
    enter(6);
    lw(a0, a0, 0);
    lhu(v1, a0, 160);
    v1 = addiu(v1, -1);
    sh(v1, a0, 160);
}

// sub_2B8B70 [create face]: creates packet kind 0xB02 (16-byte payload: a0, a1, a2, (u16)a3) with start / update / end
// sub_2B8970 / sub_2B8990 / sub_2B8B50.
void Cpu::sub_2B8B70() {
    enter(36);
    sp = addiu(sp, -80);
    sd(ra, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    s0 = a3;
    a0 = 2818;
    a1 = 16;
    jal(0x2B8BA0, gen::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2C);
    v1 = addiu(v1, -30352);
    sw(v1, v0, 104);
    v1 = lui(0x2C);
    v1 = addiu(v1, -30320);
    sw(v1, v0, 108);
    v1 = lui(0x2C);
    v1 = addiu(v1, -29872);
    sw(v1, v0, 112);
    lw(v1, v0, 120);
    sw(s3, v1, 0);
    sw(s2, v1, 4);
    sw(s1, v1, 8);
    sh(s0, v1, 12);
    ld(ra, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 80);
}

// sub_2B8C00 [home update]: update (+108) of packet kind 0xB03 (payload {u16 side mask, u16 flags}): for every unit of
// every side in the mask (gBtl +336 + 8 side, linked by +2612) with 0x4 in +156 -- skipping the ones sub_281270 reports
// under flag 0x8000 -- reads its home position and direction (sub_27F7C0), puts it there (flag 1: sub_27F650 /
// sub_281290 / sub_2D4040) and turns it (flag 2: sub_27F680 / sub_2812B0 / sub_288110). Returns 1.
void Cpu::sub_2B8C00() {
    enter(16);
    sp = addiu(sp, -144);
    sd(ra, sp, 96);
    sq(s5, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    lhu(s2, a0, 0);
    lhu(v0, a0, 2);
    s3 = 0;
    s1 = v0 & 0x8000;
    s0 = v0 & 0x1;
    s5 = v0 & 0x2;
    for (;;) {  // L_002b8d20
        charge(3);
        v0 = sltiu(s3, 4);
        if (v0 == 0) break;
        backedge();
        charge(5);
        v0 = 1;
        v0 = sllv(v0, s3);
        v0 = s2 & v0;
        if (v0 != 0) {
            charge(6);
            v1 = sll(s3, 3);
            lw(v0, gp, -18692);
            v0 = addu(v0, v1);
            lw(s4, v0, 336);
            for (;;) {  // L_002b8d14
                charge(2);
                if (s4 == 0) break;
                backedge();
                charge(4);
                lw(v0, s4, 156);
                v0 = v0 & 0x4;
                if (v0 != 0) {
                    charge(2);
                    if (s1 != 0) {
                        charge(5);
                        a0 = s4;
                        jal(0x2B8C88, gen::fn_sub_281270_00281270);
                        if (v0 != 0) goto L_002b8d10;
                    }
                    charge(8);
                    a0 = s4;
                    a1 = addiu(sp, 128);
                    a2 = addiu(sp, 112);
                    a3 = 0;
                    jal(0x2B8CA8, gen::fn_sub_27F7C0_0027f7c0);
                    if (s0 != 0) {
                        charge(10);
                        a0 = s4;
                        a1 = addiu(sp, 128);
                        jal(0x2B8CC0, gen::fn_sub_27F650_0027f650);
                        a0 = s4;
                        jal(0x2B8CCC, gen::fn_sub_281290_00281290);
                        a0 = s4;
                        jal(0x2B8CD8, gen::fn_sub_2D4040_002d4040);
                    }
                    charge(2);
                    if (s5 == 0) goto L_002b8d10;
                    charge(10);
                    a0 = s4;
                    a1 = addiu(sp, 112);
                    jal(0x2B8CF0, gen::fn_sub_27F680_0027f680);
                    a0 = s4;
                    jal(0x2B8CFC, gen::fn_sub_2812B0_002812b0);
                    a0 = s4;
                    jal(0x2B8D08, gen::fn_sub_288110_00288110);
                }
L_002b8d10:
                charge(1);
                lw(s4, s4, 2612);
            }
        }
        charge(1);
        s3 = addiu(s3, 1);
    }
    charge(11);
    v0 = 1;
    ld(ra, sp, 96);
    lq(s5, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 144);
}

// sub_2B8D60 [create home]: creates packet kind 0xB03 (4-byte payload: (u16)a0, (u16)a1) with update sub_2B8C00.
void Cpu::sub_2B8D60() {
    enter(22);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    s0 = a1;
    a0 = 2819;
    a1 = 4;
    jal(0x2B8D80, gen::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2C);
    v1 = addiu(v1, -29696);
    sw(v1, v0, 108);
    lw(v1, v0, 120);
    sh(s1, v1, 0);
    sh(s0, v1, 2);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// sub_2B8DC0 [scatter update]: update (+108) of packet kind 0xB04 (payload {u16 flags}): sub_29AD20, the formation
// (sub_2B71E0), then with flag 1 pushes every party unit that is neither dead nor holding bad status 0x180271 away from
// its home position by 250.0 (the acting unit) or 350.0 (the others). Returns 1.
void Cpu::sub_2B8DC0() {
    enter(15);
    sp = addiu(sp, -112);
    sd(ra, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F20, sp, 0);
    s1 = a0;
    jal(0x2B8DD8, gen::fn_sub_29AD20_0029ad20);
    s0 = v0;
    jal(0x2B8DE4, gen::fn_sub_2B71E0_002b71e0);
    lhu(v0, s1, 0);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        charge(4);
        lw(v0, gp, -18692);
        lw(s1, v0, 336);
        for (;;) {  // L_002b8f18
            charge(2);
            if (s1 == 0) break;
            backedge();
            charge(7);
            lw(a0, s1, 2604);
            v0 = lui(0x18);
            a1 = v0 | 0x271;
            jal(0x2B8E18, gen::fn_datCalcChkBadStatus_00300580);
            if (v0 == 0) {
                charge(6);
                lw(a0, s1, 2604);
                a1 = 0;
                jal(0x2B8E30, gen::fn_datCalcIsDead_0030b5a0);
                if (v0 != 0) goto L_002b8f14;
                charge(3);
                lw(v0, s0, 48);
                if (v0 == s1) {
                    charge(4);
                    v0 = lui(0x437A);
                    mtc1(v0, F20);
                } else {
                    charge(2);
                    v0 = lui(0x43AF);
                    mtc1(v0, F20);
                }
                charge(44);
                a0 = s1;
                a1 = addiu(sp, 96);
                a2 = 0;
                a3 = addiu(sp, 80);
                jal(0x2B8E74, gen::fn_sub_27F7C0_0027f7c0);
                lwc1(F2, sp, 100);
                swc1(F2, sp, 84);
                lwc1(F1, sp, 96);
                lwc1(F0, sp, 80);
                sub_s(F0, F1, F0);
                swc1(F0, sp, 64);
                sub_s(F0, F2, F2);
                swc1(F0, sp, 68);
                lwc1(F1, sp, 104);
                lwc1(F0, sp, 88);
                sub_s(F0, F1, F0);
                swc1(F0, sp, 72);
                a0 = addiu(sp, 64);
                a1 = a0;
                jal(0x2B8EB4, gen::fn_sub_4C69F0_004c69f0);
                lwc1(F0, sp, 64);
                mul_s(F3, F0, F20);
                swc1(F3, sp, 64);
                lwc1(F0, sp, 68);
                mul_s(F2, F0, F20);
                swc1(F2, sp, 68);
                lwc1(F0, sp, 72);
                mul_s(F1, F0, F20);
                swc1(F1, sp, 72);
                lwc1(F0, sp, 96);
                add_s(F0, F0, F3);
                swc1(F0, sp, 96);
                lwc1(F0, sp, 100);
                add_s(F0, F0, F2);
                swc1(F0, sp, 100);
                lwc1(F0, sp, 104);
                add_s(F0, F0, F1);
                swc1(F0, sp, 104);
                a0 = s1;
                a1 = addiu(sp, 96);
                jal(0x2B8F0C, gen::fn_sub_27F650_0027f650);
            }
L_002b8f14:
            charge(1);
            lw(s1, s1, 2612);
        }
    }
    charge(8);
    v0 = 1;
    ld(ra, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 112);
}

// sub_2B8F40 [create scatter]: creates packet kind 0xB04 (2-byte payload: (u16)a0) with update sub_2B8DC0.
void Cpu::sub_2B8F40() {
    enter(18);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    a0 = 2820;
    a1 = 2;
    jal(0x2B8F58, gen::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2C);
    v1 = addiu(v1, -29248);
    sw(v1, v0, 108);
    lw(v1, v0, 120);
    sh(s0, v1, 0);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// =================================================================================================================
// .BED effect data and effect instances (BED header: two 788-byte groups of 24-byte entries at +28, flags +1584,
// references +1586, the file +1588)
// =================================================================================================================

// sub_2B90D0 [bind BED]: copies the 1584-byte BED header from a1 to a0 and resolves both groups' entries (count +16,
// entries at +28): type 254 = empty, 255 = a reference to entry (index & 31) of group (index >> 5), cloned through
// sub_325920 and typed as the original, any other type = an effect object built from the file's data + offset
// (sub_324BD0). Sets flag 0x2 (+1584, bound).
void Cpu::sub_2B90D0() {
    enter(17);
    sp = addiu(sp, -128);
    sd(ra, sp, 112);
    sq(s6, sp, 96);
    sq(s5, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s5 = a0;
    s4 = a1;
    a2 = 1584;
    jal(0x2B9100, gen::fn_memcpy_00521250);
    s3 = 0;
    for (;;) {  // L_002b91d4
        charge(4);
        v1 = s3 & 0xFFFF;
        v1 = slti(v1, 2);
        if (v1 == 0) break;
        backedge();
        charge(9);
        a0 = s3 & 0xFFFF;
        v1 = 788;
        mult(v1, a0, v1);
        v1 = addu(s5, v1);
        lhu(s0, v1, 16);
        s1 = addiu(v1, 28);
        s2 = 0;
        for (;;) {  // L_002b91bc
            charge(4);
            v1 = s2 & 0xFFFF;
            v1 = slt(v1, s0);
            if (v1 == 0) break;
            backedge();
            charge(4);
            lbu(a0, s1, 0);
            v1 = 254;
            if (a0 != v1) {
                charge(3);
                v0 = 255;
                if (a0 == v0) {
                    charge(18);
                    lw(a1, s1, 4);
                    v1 = srl(a1, 5);
                    v0 = 788;
                    mult(v0, v1, v0);
                    a0 = addu(s5, v0);
                    v1 = a1 & 0x1F;
                    v0 = sll(v1, 1);
                    v0 = addu(v0, v1);
                    v0 = sll(v0, 3);
                    v0 = addu(a0, v0);
                    s6 = addiu(v0, 28);
                    lw(a0, v0, 32);
                    jal(0x2B9184, gen::fn_sub_325920_00325920);
                    lbu(v1, s6, 0);
                    sb(v1, s1, 0);
                } else {
                    charge(4);
                    lw(v0, s1, 4);
                    a0 = addu(s4, v0);
                    jal(0x2B91A4, gen::fn_sub_324BD0_00324bd0);
                }
                charge(1);
                sw(v0, s1, 4);
            }
            charge(3);
            s1 = addiu(s1, 24);
            v1 = addiu(s2, 1);
            s2 = v1 & 0xFFFF;
        }
        charge(2);
        v1 = addiu(s3, 1);
        s3 = v1 & 0xFFFF;
    }
    charge(14);
    lhu(v1, s5, 1584);
    v1 = v1 | 0x2;
    sh(v1, s5, 1584);
    ld(ra, sp, 112);
    lq(s6, sp, 96);
    lq(s5, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 128);
}

// sub_2B9220 [release BED]: destroys every entry object of both groups (sub_3257E0; types 254 and 253 hold none) and
// clears flag 0x2.
void Cpu::sub_2B9220() {
    enter(11);
    sp = addiu(sp, -96);
    sd(ra, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s4 = a0;
    s3 = 0;
    for (;;) {  // L_002b92bc
        charge(4);
        v1 = s3 & 0xFFFF;
        v1 = slti(v1, 2);
        if (v1 == 0) break;
        backedge();
        charge(9);
        a0 = s3 & 0xFFFF;
        v1 = 788;
        mult(v1, a0, v1);
        v1 = addu(s4, v1);
        lhu(s0, v1, 16);
        s1 = addiu(v1, 28);
        s2 = 0;
        for (;;) {  // L_002b92a4
            charge(4);
            v1 = s2 & 0xFFFF;
            v1 = slt(v1, s0);
            if (v1 == 0) break;
            backedge();
            charge(4);
            lbu(a0, s1, 0);
            v1 = 254;
            if (a0 != v1) {
                charge(3);
                v1 = 253;
                if (a0 == v1) goto L_002b9298;
                charge(3);
                lw(a0, s1, 4);
                jal(0x2B9290, gen::fn_sub_3257E0_003257e0);
            }
L_002b9298:
            charge(3);
            s1 = addiu(s1, 24);
            v1 = addiu(s2, 1);
            s2 = v1 & 0xFFFF;
        }
        charge(2);
        v1 = addiu(s3, 1);
        s3 = v1 & 0xFFFF;
    }
    charge(12);
    lhu(v1, s4, 1584);
    v1 = v1 & 0xFFFD;
    sh(v1, s4, 1584);
    ld(ra, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 96);
}

// sub_2B9300 [BED add reference]: references +1586 += 1; a BED marked 0x8 binds its file (+1588, sub_2B90D0) when the
// count reaches 2.
void Cpu::sub_2B9300() {
    enter(9);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    lhu(v1, a0, 1586);
    v1 = addiu(v1, 1);
    sh(v1, a0, 1586);
    lhu(v1, a0, 1584);
    v1 = v1 & 0x8;
    if (v1 != 0) {
        charge(4);
        lhu(a1, a0, 1586);
        v1 = 2;
        if (a1 != v1) goto L_002b9340;
        charge(3);
        lw(a1, a0, 1588);
        jal(0x2B9338, gen::fn_sub_2B90D0_002b90d0);
    }
L_002b9340:
    charge(4);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// sub_2B9350 [BED bound?]: returns (flags +1584 & 0x2) != 0.
void Cpu::sub_2B9350() {
    enter(5);
    lhu(v0, a0, 1584);
    v0 = v0 & 0x2;
    v0 = sltu(zero, v0);
}

// sub_2B9370 [BED duration]: the duration of side a1 (0: +8, 1: +808, else 0).
void Cpu::sub_2B9370() {
    enter(4);
    v1 = a1 & 0xFFFF;
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
            goto L_002b93a8;
        }
        charge(3);
        lw(v0, a0, 8);
        goto L_002b93ac;
    }
    charge(3);
    lw(v0, a0, 808);
    goto L_002b93ac;
L_002b93a8:
    charge(1);
    v0 = 0;
L_002b93ac:
    charge(2);
}

// sub_2B93C0 [BED group word]: group a1's word +12 (groups 788 bytes apart).
void Cpu::sub_2B93C0() {
    enter(7);
    v1 = a1 & 0xFFFF;
    v0 = 788;
    mult(v0, v1, v0);
    v0 = addu(v0, a0);
    lw(v0, v0, 12);
}

// sub_2B9590 [unit size scale]: returns in $f0 the effect scale of a model: (+140 * +44 * 0.5 + +144 * +44) * 0.5 *
// 0.0125 (gp-31848), clamped to [0.8 (gp-31844), 2.5].
void Cpu::sub_2B9590() {
    enter(18);
    lwc1(F3, a0, 44);
    lwc1(F2, a0, 144);
    lwc1(F0, a0, 140);
    mul_s(F0, F0, F3);
    v0 = lui(0x3F00);
    mtc1(v0, F1);
    mula_s(F1, F0);
    madd_s(F0, F2, F3);
    mul_s(F1, F1, F0);
    lwc1(F0, gp, -31848);
    mul_s(F0, F0, F1);
    v0 = lui(0x4020);
    mtc1(v0, F1);
    c_le_s(F0, F1);
    if (!cop1_cond()) {
        charge(3);
        mov_s(F0, F1);
    } else {
        charge(4);
        lwc1(F1, gp, -31844);
        c_lt_s(F0, F1);
        if (!cop1_cond()) goto L_002b95f8;
        charge(1);
        mov_s(F0, F1);
    }
L_002b95f8:
    charge(2);
}

// sub_2B9600 [copy matrix]: copies the 64 bytes at a0 to 0x957100 (the effect matrix the model draw reads).
void Cpu::sub_2B9600() {
    enter(3);
    a3 = lui(0x95);
    a3 = addiu(a3, 28928);
    a2 = 8;
    for (;;) {  // L_002b960c
        charge(9);
        lw(a1, a0, 0);
        lw(v1, a0, 4);
        a0 = addiu(a0, 8);
        a2 = addiu(a2, -1);
        sw(a1, a3, 0);
        sw(v1, a3, 4);
        a3 = addiu(a3, 8);
        if (lez(a2)) break;
        backedge();
    }
    charge(2);
}

// sub_2B9640 [instance flags]: translates an effect record's words into draw flags: +8 -> 0x80, +12 -> 0x1, +4 bits
// 0x400 / 0x100 / 0x4 / 0x2 -> 0x2 / 0x4 / 0x10 / 0x8, +6 bits 0x2 / 0x4 -> 0x20 / 0x40.
void Cpu::sub_2B9640() {
    enter(4);
    v0 = 0;
    lw(v1, a0, 8);
    if (v1 != 0) {
        charge(1);
        v0 = v0 | 0x80;
    }
    charge(3);
    lw(v1, a0, 12);
    if (v1 != 0) {
        charge(1);
        v0 = v0 | 0x1;
    }
    charge(4);
    lhu(a1, a0, 4);
    v1 = a1 & 0x400;
    if (v1 != 0) {
        charge(1);
        v0 = v0 | 0x2;
    }
    charge(3);
    v1 = a1 & 0x100;
    if (v1 != 0) {
        charge(1);
        v0 = v0 | 0x4;
    }
    charge(3);
    v1 = a1 & 0x4;
    if (v1 != 0) {
        charge(1);
        v0 = v0 | 0x10;
    }
    charge(3);
    v1 = a1 & 0x2;
    if (v1 != 0) {
        charge(1);
        v0 = v0 | 0x8;
    }
    charge(4);
    lhu(a0, a0, 6);
    v1 = a0 & 0x2;
    if (v1 != 0) {
        charge(1);
        v0 = v0 | 0x20;
    }
    charge(3);
    v1 = a0 & 0x4;
    if (v1 != 0) {
        charge(1);
        v0 = v0 | 0x40;
    }
    charge(2);
}

// sub_2B96E0 [BED set file]: +1588 = a1.
void Cpu::sub_2B96E0() {
    enter(3);
    sw(a1, a0, 1588);
}

// sub_2B96F0 [place by entry]: the effect position solver: a0 = the base position, a1 = a direction quaternion, a2 =
// the BED entry ({u8 _, u8 height kind, u8 mode, _, u16 param}), a3 = the out vec4, $f12 / $f13 = the size and
// half-size. Height from the kind (table 0x696440; kind 4: 2.0 or the size) plus the param; mode 8 = straight above, 9
// / 10 = toward the camera (VU0, sub_3297A0's camera position) by the half-size, otherwise rotated by the angle of
// table 0x696460 (sub_4BDDE0 / sub_4BE1E0).
void Cpu::sub_2B96F0() {
    enter(17);
    sp = addiu(sp, -144);
    sd(ra, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    mov_s(F21, F12);
    mov_s(F22, F13);
    s2 = a0;
    s1 = a3;
    lbu(a0, a2, 1);
    lbu(a3, a2, 2);
    v1 = 4;
    if (a0 == v1) {
        charge(4);
        s0 = a3 & 0xFF;
        v1 = 8;
        if (s0 == v1) {
            charge(3);
            lhu(v1, a2, 4);
            if (v1 == 0) {
                charge(4);
                v1 = lui(0x4000);
                mtc1(v1, F20);
            } else {
                charge(1);
                mov_s(F20, F21);
            }
            charge(2);
            goto L_002b97c4;
        }
        charge(4);
        v1 = lui(0x4000);
        mtc1(v1, F20);
    } else {
        charge(14);
        a0 = sll(a0, 2);
        v1 = lui(0x69);
        v1 = addiu(v1, 25664);
        v1 = addu(v1, a0);
        lwc1(F2, v1, 0);
        lwc1(F1, s2, 4);
        mtc1(zero, F0);
        adda_s(F0, F1);
        madd_s(F20, F22, F2);
        s0 = a3 & 0xFF;
        v1 = 8;
        if (s0 != v1) goto L_002b97c4;
        charge(3);
        lhu(v1, a2, 4);
        if (v1 == 0) goto L_002b97c4;
        charge(1);
        add_s(F20, F20, F21);
    }
L_002b97c4:
    charge(3);
    v1 = 10;
    if (s0 != v1) {
        charge(3);
        v1 = 9;
        if (s0 == v1) goto L_002b980c;
        charge(3);
        v1 = 8;
        if (s0 != v1) {
            charge(2);
            goto L_002b98e8;
        }
        charge(7);
        lwc1(F0, s2, 0);
        swc1(F0, s1, 0);
        swc1(F20, s1, 4);
        lwc1(F0, s2, 8);
        swc1(F0, s1, 8);
        goto L_002b99a0;
    }
L_002b980c:
    charge(8);
    a0 = addiu(sp, 80);
    jal(0x2B9810, gen::fn_sub_3297A0_003297a0);
    v1 = addiu(sp, 80);
    rt::lqc2(c, 10, v1.r, 0);
    c_lt_s(F21, F22);
    if (cop1_cond()) {
        charge(2);
    } else {
        charge(1);
        mov_s(F22, F21);
    }
    charge(4);
    neg_s(F1, F22);
    v1 = 9;
    if (s0 == v1) {
        charge(8);
        lwc1(F0, s2, 0);
        swc1(F0, sp, 80);
        lwc1(F0, s2, 4);
        swc1(F0, sp, 84);
        lwc1(F0, s2, 8);
        swc1(F0, sp, 88);
    } else {
        charge(5);
        lwc1(F0, s2, 0);
        swc1(F0, sp, 80);
        swc1(F20, sp, 84);
        lwc1(F0, s2, 8);
        swc1(F0, sp, 88);
    }
    charge(6);
    v1 = addiu(sp, 80);
    rt::lqc2(c, 11, v1.r, 0);
    rt::vsub(c, 15, 11, 11, 10);
    v1 = 10;
    if (s0 == v1) {
        charge(4);
        v1 = addiu(sp, 96);
        rt::sqc2(c, 11, v1.r, 0);
        sw(zero, sp, 100);
        rt::lqc2(c, 11, v1.r, 0);
    }
    charge(17);
    rt::vmul(c, 14, 2, 11, 11);
    rt::vmula_bc(c, 1, 0, 2, 0);
    rt::vmadda_bc(c, 1, 0, 2, 1);
    rt::vmadd_bc(c, 1, 2, 0, 2, 2);
    rt::vrsqrt(c, 0, 3, 2, 3);
    rt::vwaitq(c);
    rt::vmulq(c, 14, 11, 11);
    mfc1(v1, F1);
    rt::qmtc2(c, v1.r, 2, false);
    rt::vmul_bc(c, 15, 11, 11, 2, 0);
    v1 = addiu(sp, 80);
    rt::lqc2(c, 10, v1.r, 0);
    rt::vadd(c, 15, 10, 10, 11);
    rt::sqc2(c, 10, s1.r, 0);
    goto L_002b99a0;
L_002b98e8:
    charge(46);
    a0 = addiu(sp, 112);
    lwc1(F3, a1, 0);
    lwc1(F2, a1, 4);
    lwc1(F1, a1, 8);
    lwc1(F0, a1, 12);
    swc1(F3, sp, 112);
    swc1(F2, sp, 116);
    swc1(F1, sp, 120);
    swc1(F0, sp, 124);
    v0 = a3 & 0xFF;
    v1 = sll(v0, 2);
    v0 = lui(0x69);
    v0 = addiu(v0, 25696);
    v0 = addu(v0, v1);
    a1 = lui(0x69);
    a1 = addiu(a1, 30848);
    lwc1(F12, v0, 0);
    a2 = 2;
    jal(0x2B9930, gen::fn_sub_4BDDE0_004bdde0);
    a0 = addiu(sp, 128);
    a1 = lui(0x69);
    a1 = addiu(a1, 30864);
    a2 = 1;
    a3 = addiu(sp, 112);
    jal(0x2B994C, gen::fn_sub_4BE1E0_004be1e0);
    lwc1(F0, sp, 128);
    mul_s(F1, F0, F21);
    swc1(F1, sp, 128);
    lwc1(F0, sp, 132);
    mul_s(F0, F0, F21);
    swc1(F0, sp, 132);
    lwc1(F0, sp, 136);
    mul_s(F0, F0, F21);
    swc1(F0, sp, 136);
    lwc1(F0, s2, 0);
    add_s(F0, F0, F1);
    swc1(F0, s1, 0);
    lwc1(F0, sp, 132);
    add_s(F0, F20, F0);
    swc1(F0, s1, 4);
    lwc1(F1, s2, 8);
    lwc1(F0, sp, 136);
    add_s(F0, F1, F0);
    swc1(F0, s1, 8);
L_002b99a0:
    charge(11);
    sw(zero, s1, 12);
    ld(ra, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 144);
}

// sub_2B99D0 [place at owner]: BED position callback 0 (table 0x696490): the owner's size (param or +48 * scale) at its
// transformed offset (+32..+40 * +80 through the matrix +64, + the position +52..), placed by sub_2B96F0.
void Cpu::sub_2B99D0() {
    enter(13);
    sp = addiu(sp, -128);
    sd(ra, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s2 = a0;
    s1 = a2;
    s0 = a3;
    lhu(v0, a2, 4);
    if (v0 == 0) {
        charge(5);
        lwc1(F1, s2, 48);
        lwc1(F0, a1, 44);
        mul_s(F20, F1, F0);
    } else {
        charge(3);
        mtc1(v0, F0);
        cvt_s_w(F20, F0);
    }
    charge(52);
    lwc1(F1, s2, 44);
    lwc1(F0, a1, 44);
    mul_s(F1, F1, F0);
    v0 = lui(0x3F00);
    mtc1(v0, F0);
    mul_s(F21, F0, F1);
    lwc1(F0, s2, 32);
    lwc1(F1, s2, 80);
    mul_s(F0, F0, F1);
    swc1(F0, sp, 96);
    lwc1(F0, s2, 36);
    mul_s(F0, F0, F1);
    swc1(F0, sp, 100);
    lwc1(F0, s2, 40);
    mul_s(F0, F0, F1);
    swc1(F0, sp, 104);
    a0 = addiu(sp, 80);
    a1 = addiu(sp, 96);
    a2 = 1;
    a3 = addiu(s2, 64);
    jal(0x2B9A78, gen::fn_sub_4BE1E0_004be1e0);
    lwc1(F1, s2, 52);
    lwc1(F0, sp, 80);
    add_s(F0, F0, F1);
    swc1(F0, sp, 112);
    lwc1(F1, s2, 56);
    lwc1(F0, sp, 84);
    add_s(F0, F0, F1);
    swc1(F0, sp, 116);
    lwc1(F1, s2, 60);
    lwc1(F0, sp, 88);
    add_s(F0, F0, F1);
    swc1(F0, sp, 120);
    mov_s(F12, F20);
    mov_s(F13, F21);
    a0 = addiu(sp, 112);
    a1 = addiu(s2, 64);
    a2 = s1;
    a3 = s0;
    jal(0x2B9AC8, gen::fn_sub_2B96F0_002b96f0);
    ld(ra, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 128);
}

// sub_2B9B00 [place at bone]: BED position callbacks 1 / 7: the position of bone `param` of the unit's model (+2548,
// sub_318ED0) when the unit is a model (+152 & 2), else the owner's transformed offset; written to a3.
void Cpu::sub_2B9B00() {
    enter(10);
    sp = addiu(sp, -96);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    s0 = a3;
    lw(v0, a1, 152);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        charge(6);
        a0 = a1;
        a1 = addiu(sp, 80);
        jal(0x2B9B30, gen::fn_sub_27FFB0_0027ffb0);
    } else {
        charge(8);
        lhu(v0, a2, 4);
        lw(a0, a1, 2548);
        a1 = v0;
        a2 = addiu(sp, 80);
        jal(0x2B9B50, gen::fn_sub_318ED0_00318ed0);
        if (v0 != 0) goto L_002b9bd0;
        charge(28);
        lwc1(F0, s1, 32);
        lwc1(F1, s1, 80);
        mul_s(F0, F0, F1);
        swc1(F0, sp, 64);
        lwc1(F0, s1, 36);
        mul_s(F0, F0, F1);
        swc1(F0, sp, 68);
        lwc1(F0, s1, 40);
        mul_s(F0, F0, F1);
        swc1(F0, sp, 72);
        a0 = addiu(sp, 48);
        a1 = addiu(sp, 64);
        a2 = 1;
        a3 = addiu(s1, 64);
        jal(0x2B9B98, gen::fn_sub_4BE1E0_004be1e0);
        lwc1(F1, s1, 52);
        lwc1(F0, sp, 48);
        add_s(F0, F0, F1);
        swc1(F0, sp, 80);
        lwc1(F1, s1, 56);
        lwc1(F0, sp, 52);
        add_s(F0, F0, F1);
        swc1(F0, sp, 84);
        lwc1(F1, s1, 60);
        lwc1(F0, sp, 56);
        add_s(F0, F0, F1);
        swc1(F0, sp, 88);
    }
L_002b9bd0:
    charge(12);
    lwc1(F0, sp, 80);
    swc1(F0, s0, 0);
    lwc1(F0, sp, 84);
    swc1(F0, s0, 4);
    lwc1(F0, sp, 88);
    swc1(F0, s0, 8);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 96);
}

// sub_2B9C00 [place at bone (attachment 964)]: BED position callbacks 8 / 10: like sub_2B9B00 on the model's attachment
// +964 (or the model itself).
void Cpu::sub_2B9C00() {
    enter(13);
    sp = addiu(sp, -128);
    sd(ra, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s2 = a0;
    s1 = a2;
    s0 = a3;
    lw(v0, a1, 152);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        charge(6);
        a0 = a1;
        a1 = addiu(sp, 112);
        jal(0x2B9C3C, gen::fn_sub_27FFB0_0027ffb0);
    } else {
        charge(4);
        lw(v0, a1, 2548);
        lw(s3, v0, 964);
        if (s3 == 0) {
            charge(1);
            s3 = v0;
        }
        charge(13);
        a0 = s3;
        jal(0x2B9C64, gen::fn_sub_3176C0_003176c0);
        a0 = s3;
        jal(0x2B9C70, gen::fn_sub_318B90_00318b90);
        lhu(a1, s1, 4);
        a0 = s3;
        a2 = addiu(sp, 112);
        jal(0x2B9C84, gen::fn_sub_318ED0_00318ed0);
        if (v0 != 0) goto L_002b9d04;
        charge(28);
        lwc1(F0, s2, 32);
        lwc1(F1, s2, 80);
        mul_s(F0, F0, F1);
        swc1(F0, sp, 96);
        lwc1(F0, s2, 36);
        mul_s(F0, F0, F1);
        swc1(F0, sp, 100);
        lwc1(F0, s2, 40);
        mul_s(F0, F0, F1);
        swc1(F0, sp, 104);
        a0 = addiu(sp, 80);
        a1 = addiu(sp, 96);
        a2 = 1;
        a3 = addiu(s2, 64);
        jal(0x2B9CCC, gen::fn_sub_4BE1E0_004be1e0);
        lwc1(F1, s2, 52);
        lwc1(F0, sp, 80);
        add_s(F0, F0, F1);
        swc1(F0, sp, 112);
        lwc1(F1, s2, 56);
        lwc1(F0, sp, 84);
        add_s(F0, F0, F1);
        swc1(F0, sp, 116);
        lwc1(F1, s2, 60);
        lwc1(F0, sp, 88);
        add_s(F0, F0, F1);
        swc1(F0, sp, 120);
    }
L_002b9d04:
    charge(14);
    lwc1(F0, sp, 112);
    swc1(F0, s0, 0);
    lwc1(F0, sp, 116);
    swc1(F0, s0, 4);
    lwc1(F0, sp, 120);
    swc1(F0, s0, 8);
    ld(ra, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 128);
}

// sub_2B9D40 [place at bone (attachment 952)]: BED position callbacks 9 / 11: like sub_2B9B00 on the model's attachment
// +952 (or the model itself).
void Cpu::sub_2B9D40() {
    enter(13);
    sp = addiu(sp, -128);
    sd(ra, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s2 = a0;
    s1 = a2;
    s0 = a3;
    lw(v0, a1, 152);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        charge(6);
        a0 = a1;
        a1 = addiu(sp, 112);
        jal(0x2B9D7C, gen::fn_sub_27FFB0_0027ffb0);
    } else {
        charge(4);
        lw(v0, a1, 2548);
        lw(s3, v0, 952);
        if (s3 == 0) {
            charge(1);
            s3 = v0;
        }
        charge(13);
        a0 = s3;
        jal(0x2B9DA4, gen::fn_sub_3176C0_003176c0);
        a0 = s3;
        jal(0x2B9DB0, gen::fn_sub_318B90_00318b90);
        lhu(a1, s1, 4);
        a0 = s3;
        a2 = addiu(sp, 112);
        jal(0x2B9DC4, gen::fn_sub_318ED0_00318ed0);
        if (v0 != 0) goto L_002b9e44;
        charge(28);
        lwc1(F0, s2, 32);
        lwc1(F1, s2, 80);
        mul_s(F0, F0, F1);
        swc1(F0, sp, 96);
        lwc1(F0, s2, 36);
        mul_s(F0, F0, F1);
        swc1(F0, sp, 100);
        lwc1(F0, s2, 40);
        mul_s(F0, F0, F1);
        swc1(F0, sp, 104);
        a0 = addiu(sp, 80);
        a1 = addiu(sp, 96);
        a2 = 1;
        a3 = addiu(s2, 64);
        jal(0x2B9E0C, gen::fn_sub_4BE1E0_004be1e0);
        lwc1(F1, s2, 52);
        lwc1(F0, sp, 80);
        add_s(F0, F0, F1);
        swc1(F0, sp, 112);
        lwc1(F1, s2, 56);
        lwc1(F0, sp, 84);
        add_s(F0, F0, F1);
        swc1(F0, sp, 116);
        lwc1(F1, s2, 60);
        lwc1(F0, sp, 88);
        add_s(F0, F0, F1);
        swc1(F0, sp, 120);
    }
L_002b9e44:
    charge(14);
    lwc1(F0, sp, 112);
    swc1(F0, s0, 0);
    lwc1(F0, sp, 116);
    swc1(F0, s0, 4);
    lwc1(F0, sp, 120);
    swc1(F0, s0, 8);
    ld(ra, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 128);
}

// sub_2B9E80 [place at centre]: BED position callback 4: the battle centre (sub_280870 side 3) placed by sub_2B96F0.
void Cpu::sub_2B9E80() {
    enter(17);
    sp = addiu(sp, -80);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a2;
    s0 = a3;
    a0 = 3;
    a1 = 0;
    a2 = addiu(sp, 64);
    a3 = addiu(sp, 76);
    t0 = 0;
    t1 = 0;
    jal(0x2B9EB0, gen::fn_sub_280870_00280870);
    lhu(v0, s1, 4);
    if (v0 == 0) {
        charge(2);
    } else {
        charge(3);
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
    }
    charge(22);
    v0 = lui(0x3F80);
    sw(v0, sp, 60);
    sw(zero, sp, 48);
    sw(zero, sp, 52);
    sw(zero, sp, 56);
    v0 = lui(0x3F00);
    mtc1(v0, F2);
    lwc1(F1, sp, 76);
    mul_s(F13, F2, F1);
    mov_s(F12, F0);
    a0 = addiu(sp, 64);
    a1 = addiu(sp, 48);
    a2 = s1;
    a3 = s0;
    jal(0x2B9F10, gen::fn_sub_2B96F0_002b96f0);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 80);
}

// sub_2B9F30 [place at own side]: BED position callback 2: the centre of the unit's own side (sub_280870 side 1 / 2 by
// +162) placed by sub_2B96F0.
void Cpu::sub_2B9F30() {
    enter(9);
    sp = addiu(sp, -80);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a2;
    s0 = a3;
    lbu(v0, a1, 162);
    if (v0 == 0) {
        charge(3);
        v0 = 1;
    } else {
        charge(1);
        v0 = 2;
    }
    charge(11);
    a0 = v0 & 0xFFFF;
    a1 = 0;
    a2 = addiu(sp, 64);
    a3 = addiu(sp, 76);
    t0 = 0;
    t1 = 0;
    jal(0x2B9F7C, gen::fn_sub_280870_00280870);
    lhu(v0, s1, 4);
    if (v0 == 0) {
        charge(2);
    } else {
        charge(3);
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
    }
    charge(22);
    v0 = lui(0x3F80);
    sw(v0, sp, 60);
    sw(zero, sp, 48);
    sw(zero, sp, 52);
    sw(zero, sp, 56);
    v0 = lui(0x3F00);
    mtc1(v0, F2);
    lwc1(F1, sp, 76);
    mul_s(F13, F2, F1);
    mov_s(F12, F0);
    a0 = addiu(sp, 64);
    a1 = addiu(sp, 48);
    a2 = s1;
    a3 = s0;
    jal(0x2B9FDC, gen::fn_sub_2B96F0_002b96f0);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 80);
}

// sub_2BA000 [place at other side]: BED position callback 3: the centre of the other side placed by sub_2B96F0.
void Cpu::sub_2BA000() {
    enter(9);
    sp = addiu(sp, -80);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a2;
    s0 = a3;
    lbu(v0, a1, 162);
    if (v0 == 0) {
        charge(3);
        v0 = 2;
    } else {
        charge(1);
        v0 = 1;
    }
    charge(11);
    a0 = v0 & 0xFFFF;
    a1 = 0;
    a2 = addiu(sp, 64);
    a3 = addiu(sp, 76);
    t0 = 0;
    t1 = 0;
    jal(0x2BA04C, gen::fn_sub_280870_00280870);
    lhu(v0, s1, 4);
    if (v0 == 0) {
        charge(2);
    } else {
        charge(3);
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
    }
    charge(22);
    v0 = lui(0x3F80);
    sw(v0, sp, 60);
    sw(zero, sp, 48);
    sw(zero, sp, 52);
    sw(zero, sp, 56);
    v0 = lui(0x3F00);
    mtc1(v0, F2);
    lwc1(F1, sp, 76);
    mul_s(F13, F2, F1);
    mov_s(F12, F0);
    a0 = addiu(sp, 64);
    a1 = addiu(sp, 48);
    a2 = s1;
    a3 = s0;
    jal(0x2BA0AC, gen::fn_sub_2B96F0_002b96f0);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 80);
}

// sub_2BA0D0 [place nowhere]: BED position callback 12: a zero vec4 in a3.
void Cpu::sub_2BA0D0() {
    enter(6);
    sw(zero, a3, 0);
    sw(zero, a3, 4);
    sw(zero, a3, 8);
    sw(zero, a3, 12);
}

// sub_2BA0F0 [orient by entry]: the effect orientation: the jump table 0x7B7D00 (13 kinds, the entry's byte +0) chooses
// kind 0 the camera-facing yaw (atan2f of the transformed axis, sub_357EA0 into VU0 vf10), 1 / 8 / 9 a bone's matrix
// (sub_318D10, sub_329ED0), 2..4 / 7 / 10..12 the identity (vf0), 5 / 6 nothing; the quaternion goes to a3 (sqc2).
void Cpu::sub_2BA0F0() {
    enter(9);
    sp = addiu(sp, -176);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    t0 = a0;
    s0 = a3;
    lbu(a3, a2, 0);
    at = sltiu(a3, 13);
    if (at != 0) {
        charge(7);
        a0 = lui(0x7B);
        a0 = addiu(a0, 32000);
        v1 = sll(a3, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (const u32 t = v1.u()) {  // jump table
        case 0x2BA130: goto L_002ba130;
        case 0x2BA1AC: goto L_002ba1ac;
        case 0x2BA1B8: goto L_002ba1b8;
        case 0x2BA288: goto L_002ba288;
        case 0x2BA37C: goto L_002ba37c;
        case 0x2BA380: goto L_002ba380;
        default: tail(t); return;
        }
L_002ba130:
        charge(13);
        a0 = addiu(sp, 160);
        a1 = lui(0x69);
        a1 = addiu(a1, 30864);
        a2 = 1;
        a3 = addiu(t0, 64);
        jal(0x2BA144, gen::fn_sub_4BE1E0_004be1e0);
        lwc1(F12, sp, 160);
        mtc1(zero, F1);
        c_eq_s(F1, F12);
        if (cop1_cond()) {
            charge(4);
            lwc1(F0, sp, 168);
            c_eq_s(F1, F0);
            if (cop1_cond()) goto L_002ba1a0;
        }
        charge(11);
        lwc1(F13, sp, 168);
        jal(0x2BA178, gen::fn_atan2f_0052ea18);
        mtc1(zero, F12);
        mov_s(F13, F0);
        mov_s(F14, F12);
        jal(0x2BA18C, gen::fn_sub_357EA0_00357ea0);
        rt::sqc2(c, 10, s0.r, 0);
        goto L_002ba380;
L_002ba1a0:
        charge(3);
        rt::sqc2(c, 0, s0.r, 0);
        goto L_002ba380;
L_002ba1ac:
        charge(3);
        rt::sqc2(c, 0, s0.r, 0);
        goto L_002ba380;
L_002ba1b8:
        charge(4);
        lw(v1, a1, 152);
        v1 = v1 & 0x2;
        if (v1 != 0) {
            charge(8);
            lhu(v0, a2, 4);
            lw(a0, a1, 2548);
            a1 = v0;
            a2 = addiu(sp, 32);
            jal(0x2BA1D8, gen::fn_sub_318D10_00318d10);
            if (v0 != 0) {
                charge(34);
                lwc1(F0, sp, 32);
                swc1(F0, sp, 96);
                lwc1(F0, sp, 36);
                swc1(F0, sp, 100);
                lwc1(F0, sp, 40);
                swc1(F0, sp, 104);
                sw(zero, sp, 108);
                lwc1(F0, sp, 48);
                swc1(F0, sp, 112);
                lwc1(F0, sp, 52);
                swc1(F0, sp, 116);
                lwc1(F0, sp, 56);
                swc1(F0, sp, 120);
                sw(zero, sp, 124);
                lwc1(F0, sp, 64);
                swc1(F0, sp, 128);
                lwc1(F0, sp, 68);
                swc1(F0, sp, 132);
                lwc1(F0, sp, 72);
                swc1(F0, sp, 136);
                sw(zero, sp, 140);
                lwc1(F0, sp, 80);
                swc1(F0, sp, 144);
                lwc1(F0, sp, 84);
                swc1(F0, sp, 148);
                lwc1(F0, sp, 88);
                swc1(F0, sp, 152);
                sw(zero, sp, 156);
                a0 = addiu(sp, 96);
                jal(0x2BA25C, gen::fn_sub_329ED0_00329ed0);
                rt::sqc2(c, 10, s0.r, 0);
                goto L_002ba380;
            }
            charge(3);
            rt::sqc2(c, 0, s0.r, 0);
            goto L_002ba380;
        }
        charge(3);
        rt::sqc2(c, 0, s0.r, 0);
        goto L_002ba380;
L_002ba288:
        charge(4);
        lw(v1, a1, 152);
        v1 = v1 & 0x2;
        if (v1 != 0) {
            charge(11);
            v1 = a3 ^ 0x8;
            a0 = sltiu(v1, 1);
            v1 = sll(a0, 1);
            v1 = addu(v1, a0);
            a0 = sll(v1, 2);
            lw(v1, a1, 2548);
            v1 = addiu(v1, 952);
            v1 = addu(v1, a0);
            lw(a0, v1, 0);
            if (a0 == 0) goto L_002ba380;
            charge(6);
            lhu(a1, a2, 4);
            a2 = addiu(sp, 32);
            jal(0x2BA2CC, gen::fn_sub_318D10_00318d10);
            if (v0 != 0) {
                charge(34);
                lwc1(F0, sp, 32);
                swc1(F0, sp, 96);
                lwc1(F0, sp, 36);
                swc1(F0, sp, 100);
                lwc1(F0, sp, 40);
                swc1(F0, sp, 104);
                sw(zero, sp, 108);
                lwc1(F0, sp, 48);
                swc1(F0, sp, 112);
                lwc1(F0, sp, 52);
                swc1(F0, sp, 116);
                lwc1(F0, sp, 56);
                swc1(F0, sp, 120);
                sw(zero, sp, 124);
                lwc1(F0, sp, 64);
                swc1(F0, sp, 128);
                lwc1(F0, sp, 68);
                swc1(F0, sp, 132);
                lwc1(F0, sp, 72);
                swc1(F0, sp, 136);
                sw(zero, sp, 140);
                lwc1(F0, sp, 80);
                swc1(F0, sp, 144);
                lwc1(F0, sp, 84);
                swc1(F0, sp, 148);
                lwc1(F0, sp, 88);
                swc1(F0, sp, 152);
                sw(zero, sp, 156);
                a0 = addiu(sp, 96);
                jal(0x2BA350, gen::fn_sub_329ED0_00329ed0);
                rt::sqc2(c, 10, s0.r, 0);
                goto L_002ba380;
            }
            charge(3);
            rt::sqc2(c, 0, s0.r, 0);
            goto L_002ba380;
        }
        charge(3);
        rt::sqc2(c, 0, s0.r, 0);
        goto L_002ba380;
L_002ba37c:
        charge(1);
        rt::sqc2(c, 0, s0.r, 0);
    }
L_002ba380:
    charge(5);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 176);
}

// sub_2BA3A0 [instance update]: per-frame update of an effect instance (+0 the BED, +4 the group, +8 flags, +12 frame,
// +16 colour, +24 owner, +28 target, +84 entry count, +88 entry objects): refreshes the owner's offset, scale and
// orientation, then for every entry whose start frame (+16) has passed creates its object (sub_325920), scales it to
// the unit size (sub_2B9590's formula), places it through the position callback of its kind (`jalr` through table
// 0x696490), orients it (sub_2BA0F0) and updates it (sub_325C10 / sub_325D60 / sub_326030 / sub_3252A0). Frame +12 +=
// 1.
void Cpu::sub_2BA3A0() {
    enter(18);
    sp = addiu(sp, -224);
    sd(ra, sp, 144);
    sq(fp, sp, 128);
    sq(s7, sp, 112);
    sq(s6, sp, 96);
    sq(s5, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s4 = a0;
    lw(s0, a0, 24);
    lw(s6, a0, 16);
    lw(a0, a0, 8);
    v1 = a0 & 0x800;
    if (v1 == 0) {
        charge(4);
        v1 = lui(0xFF00);
        v1 = s6 & v1;
        if (v1 == 0) goto L_002ba8cc;
        charge(3);
        lw(s3, s4, 12);
        if (s3 != 0) {
            charge(3);
            v0 = a0 & 0x1000;
            if (v0 != 0) {
                charge(4);
                lw(v0, s4, 0);
                lw(v0, v0, 800);
                if (s3 == v0) goto L_002ba42c;
            }
            charge(3);
            v0 = a0 & 0x100;
            if (v0 == 0) goto L_002ba5f8;
        }
L_002ba42c:
        charge(5);
        a0 = s0;
        jal(0x2BA430, gen::fn_sub_2FC520_002fc520);
        if (v0 != 0) {
            charge(18);
            lh(v1, v0, 0);
            mtc1(v1, F0);
            cvt_s_w(F0, F0);
            swc1(F0, s4, 32);
            lh(v1, v0, 2);
            mtc1(v1, F0);
            cvt_s_w(F0, F0);
            swc1(F0, s4, 36);
            lh(v1, v0, 4);
            mtc1(v1, F0);
            cvt_s_w(F0, F0);
            swc1(F0, s4, 40);
            lhu(v1, v0, 6);
            if (gez(v1)) {
                charge(5);
                mtc1(v1, F0);
                cvt_s_w(F0, F0);
            } else {
                charge(7);
                a0 = srl(v1, 1);
                v1 = v1 & 0x1;
                a0 = a0 | v1;
                mtc1(a0, F0);
                cvt_s_w(F0, F0);
                add_s(F0, F0, F0);
            }
            charge(4);
            swc1(F0, s4, 44);
            lhu(v0, v0, 8);
            if (gez(v0)) {
                charge(5);
                mtc1(v0, F0);
                cvt_s_w(F0, F0);
            } else {
                charge(7);
                v1 = srl(v0, 1);
                v0 = v0 & 0x1;
                v1 = v1 | v0;
                mtc1(v1, F0);
                cvt_s_w(F0, F0);
                add_s(F0, F0, F0);
            }
            charge(3);
            swc1(F0, s4, 48);
        } else {
            charge(10);
            lwc1(F2, s0, 128);
            lwc1(F1, s0, 132);
            lwc1(F0, s0, 136);
            swc1(F2, s4, 32);
            swc1(F1, s4, 36);
            swc1(F0, s4, 40);
            lwc1(F0, s0, 140);
            swc1(F0, s4, 44);
            lwc1(F0, s0, 144);
            swc1(F0, s4, 48);
        }
        charge(9);
        lwc1(F2, s0, 4);
        lwc1(F1, s0, 8);
        lwc1(F0, s0, 12);
        swc1(F2, s4, 52);
        swc1(F1, s4, 56);
        swc1(F0, s4, 60);
        lw(v0, s4, 28);
        if (s0 == v0) {
            charge(10);
            lwc1(F3, s0, 28);
            lwc1(F2, s0, 32);
            lwc1(F1, s0, 36);
            lwc1(F0, s0, 40);
            swc1(F3, s4, 64);
            swc1(F2, s4, 68);
            swc1(F1, s4, 72);
            swc1(F0, s4, 76);
        } else {
            charge(4);
            lbu(v1, s0, 162);
            lbu(v0, v0, 162);
            if (v1 == v0) {
                charge(3);
                v0 = 1;
                if (v1 != v0) goto L_002ba5bc;
                charge(10);
                lwc1(F3, s0, 28);
                lwc1(F2, s0, 32);
                lwc1(F1, s0, 36);
                lwc1(F0, s0, 40);
                swc1(F3, s4, 64);
                swc1(F2, s4, 68);
                swc1(F1, s4, 72);
                swc1(F0, s4, 76);
                goto L_002ba5f0;
            }
L_002ba5bc:
            charge(13);
            a0 = s0;
            a1 = addiu(sp, 208);
            jal(0x2BA5C4, gen::fn_sub_27FFB0_0027ffb0);
            lw(a0, s4, 28);
            a1 = addiu(sp, 192);
            jal(0x2BA5D4, gen::fn_sub_27FFB0_0027ffb0);
            a0 = addiu(s4, 64);
            a1 = addiu(sp, 208);
            a2 = addiu(sp, 192);
            jal(0x2BA5E8, gen::fn_sub_2D1DE0_002d1de0);
        }
L_002ba5f0:
        charge(2);
        lwc1(F0, s0, 44);
        swc1(F0, s4, 80);
L_002ba5f8:
        charge(11);
        lw(a0, s4, 24);
        lw(a1, s4, 28);
        jal(0x2BA600, gen::fn_sub_352C30_00352c30);
        lw(s2, s4, 88);
        lhu(fp, s4, 84);
        lw(v1, s4, 4);
        s1 = addiu(v1, 20);
        s5 = 0;
        for (;;) {  // L_002ba8b0
            charge(4);
            v1 = s5 & 0xFFFF;
            v1 = slt(v1, fp);
            if (v1 == 0) break;
            backedge();
            charge(4);
            lw(v1, s1, 16);
            at = sltu(v1, s3);
            if (at != 0) {
                charge(4);
                lbu(a1, s1, 0);
                v1 = 254;
                if (a1 == v1) goto L_002ba8a0;
                charge(3);
                lw(v1, s2, 0);
                if (v1 == 0) {
                    charge(5);
                    lw(v1, s4, 0);
                    lhu(v1, v1, 1584);
                    v1 = v1 & 0x4;
                    if (v1 != 0) {
                        charge(3);
                        a0 = 253;
                        if (a1 == a0) goto L_002ba688;
                        charge(6);
                        lw(v1, s1, 4);
                        sw(v1, s2, 0);
                        s7 = 0;
                        sb(a0, s1, 0);
                        goto L_002ba69c;
                    }
L_002ba688:
                    charge(5);
                    lw(a0, s1, 4);
                    jal(0x2BA68C, gen::fn_sub_325920_00325920);
                    sw(v0, s2, 0);
                    s7 = 1;
L_002ba69c:
                    charge(4);
                    lw(v1, s4, 4);
                    lbu(a1, v1, 16);
                    if (a1 != 0) {
                        charge(2);
                        if (s0 == 0) goto L_002ba7e8;
                        charge(4);
                        lbu(a0, s1, 8);
                        v1 = 7;
                        if (a0 != v1) {
                            charge(3);
                            v1 = 6;
                            if (a0 == v1) goto L_002ba6ec;
                            charge(3);
                            v1 = 1;
                            if (a0 == v1) goto L_002ba6ec;
                            charge(2);
                            if (a0 == 0) goto L_002ba6ec;
                            charge(2);
                            goto L_002ba7e8;
                        }
L_002ba6ec:
                        charge(3);
                        v0 = 1;
                        if (a1 != v0) {
                            charge(2);
                        } else {
                            charge(18);
                            lwc1(F3, s0, 44);
                            lwc1(F2, s0, 144);
                            lwc1(F0, s0, 140);
                            mul_s(F0, F0, F3);
                            v0 = lui(0x3F00);
                            mtc1(v0, F1);
                            mula_s(F1, F0);
                            madd_s(F0, F2, F3);
                            mul_s(F1, F1, F0);
                            lwc1(F0, gp, -31848);
                            mul_s(F12, F0, F1);
                            v0 = lui(0x4020);
                            mtc1(v0, F0);
                            c_le_s(F12, F0);
                            if (!cop1_cond()) {
                                charge(3);
                                mov_s(F12, F0);
                            } else {
                                charge(4);
                                lwc1(F0, gp, -31844);
                                c_lt_s(F12, F0);
                                if (!cop1_cond()) goto L_002ba768;
                                charge(1);
                                mov_s(F12, F0);
                            }
L_002ba768:
                            charge(2);
                            goto L_002ba7dc;
                        }
                        charge(19);
                        lw(v0, s4, 28);
                        lwc1(F3, v0, 44);
                        lwc1(F2, v0, 144);
                        lwc1(F0, v0, 140);
                        mul_s(F0, F0, F3);
                        v0 = lui(0x3F00);
                        mtc1(v0, F1);
                        mula_s(F1, F0);
                        madd_s(F0, F2, F3);
                        mul_s(F1, F1, F0);
                        lwc1(F0, gp, -31848);
                        mul_s(F12, F0, F1);
                        v0 = lui(0x4020);
                        mtc1(v0, F0);
                        c_le_s(F12, F0);
                        if (!cop1_cond()) {
                            charge(3);
                            mov_s(F12, F0);
                        } else {
                            charge(4);
                            lwc1(F0, gp, -31844);
                            c_lt_s(F12, F0);
                            if (!cop1_cond()) goto L_002ba7dc;
                            charge(1);
                            mov_s(F12, F0);
                        }
L_002ba7dc:
                        charge(3);
                        lw(a0, s2, 0);
                        jal(0x2BA7E0, gen::fn_sub_325E40_00325e40);
                    }
L_002ba7e8:
                    charge(2);
                    if (s7 != 0) goto L_002ba8a0;
                }
                charge(3);
                lhu(v1, s1, 14);
                if (v1 != 0) {
                    charge(4);
                    lw(v1, s4, 8);
                    v1 = v1 & 0x1E;
                    if (v1 != 0) goto L_002ba8a0;
                    charge(4);
                    lbu(v1, s4, 20);
                    v1 = slti(v1, 50);
                    if (v1 != 0) goto L_002ba8a0;
                }
                charge(33);
                a0 = s4;
                a1 = s0;
                a2 = addiu(s1, 8);
                a3 = addiu(sp, 176);
                lbu(v0, s1, 8);
                v1 = sll(v0, 2);
                v0 = lui(0x69);
                v0 = addiu(v0, 25744);
                v0 = addu(v0, v1);
                lw(v0, v0, 0);
                jalr(0x2BA844, v0.u());
                lw(a0, s2, 0);
                a1 = addiu(sp, 176);
                jal(0x2BA854, gen::fn_sub_325C10_00325c10);
                a0 = s4;
                a1 = s0;
                a2 = addiu(s1, 8);
                a3 = addiu(sp, 160);
                jal(0x2BA86C, gen::fn_sub_2BA0F0_002ba0f0);
                lw(a0, s2, 0);
                a1 = addiu(sp, 160);
                jal(0x2BA87C, gen::fn_sub_325D60_00325d60);
                lw(a0, s2, 0);
                a1 = s6;
                jal(0x2BA88C, gen::fn_sub_326030_00326030);
                lw(a0, s2, 0);
                jal(0x2BA898, gen::fn_sub_3252A0_003252a0);
            }
L_002ba8a0:
            charge(4);
            v1 = addiu(s5, 1);
            s5 = v1 & 0xFFFF;
            s1 = addiu(s1, 24);
            s2 = addiu(s2, 4);
        }
        charge(3);
        lw(v1, s4, 12);
        v1 = addiu(v1, 1);
        sw(v1, s4, 12);
    }
L_002ba8cc:
    charge(13);
    ld(ra, sp, 144);
    lq(fp, sp, 128);
    lq(s7, sp, 112);
    lq(s6, sp, 96);
    lq(s5, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 224);
}

// sub_2BA900 [instance draw]: draws an effect instance's entry objects (sub_325500); with flag 0x8000 under the model
// draw state (sub_321130 / sub_321320 with the matrix 0x957100 / sub_321120); nothing under flag 0x400.
void Cpu::sub_2BA900() {
    enter(10);
    sp = addiu(sp, -80);
    sd(ra, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    lw(a1, a0, 8);
    v1 = a1 & 0x400;
    if (v1 == 0) {
        charge(5);
        lw(s0, a0, 88);
        lhu(s2, a0, 84);
        v1 = a1 & 0x8000;
        if (v1 == 0) {
            charge(4);
            s3 = 0;
            s1 = s2 & 0xFFFF;
            for (;;) {  // L_002ba96c
                charge(4);
                v1 = s3 & 0xFFFF;
                v1 = slt(v1, s1);
                if (v1 == 0) break;
                backedge();
                charge(3);
                lw(a0, s0, 0);
                if (a0 != 0) {
                    charge(2);
                    jal(0x2BA958, gen::fn_sub_325500_00325500);
                }
                charge(3);
                v1 = addiu(s3, 1);
                s3 = v1 & 0xFFFF;
                s0 = addiu(s0, 4);
            }
            charge(2);
            goto L_002ba9f8;
        }
        charge(14);
        jal(0x2BA984, gen::fn_sub_321130_00321130);
        s1 = v0 & 0xFFFF;
        a0 = lui(0x95);
        a0 = addiu(a0, 28928);
        jal(0x2BA998, gen::fn_sub_321320_00321320);
        a0 = 4;
        jal(0x2BA9A4, gen::fn_sub_321120_00321120);
        s3 = 0;
        s2 = s2 & 0xFFFF;
        for (;;) {  // L_002ba9dc
            charge(4);
            v0 = s3 & 0xFFFF;
            v0 = slt(v0, s2);
            if (v0 == 0) break;
            backedge();
            charge(3);
            lw(a0, s0, 0);
            if (a0 != 0) {
                charge(2);
                jal(0x2BA9C8, gen::fn_sub_325500_00325500);
            }
            charge(3);
            v0 = addiu(s3, 1);
            s3 = v0 & 0xFFFF;
            s0 = addiu(s0, 4);
        }
        charge(3);
        a0 = s1;
        jal(0x2BA9F0, gen::fn_sub_321120_00321120);
    }
L_002ba9f8:
    charge(8);
    ld(ra, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 80);
}

// =================================================================================================================
// unit effect packets (kinds 0x400, 0x301, 0x302: an effect slot attached to one or two units)
// =================================================================================================================

// sub_2BAC00 [create named effect]: creates packet kind 0x400 (payload 16 + strlen(name) bytes: a0, the name copied to
// +16 and its pointer at +8, (u16)a2 at +12) with start sub_2BAA20 (loads the BED: file I/O, kept recompiled) and
// update sub_2BAAD0 (heap, kept); returns the packet.
void Cpu::sub_2BAC00() {
    enter(44);
    sp = addiu(sp, -80);
    sd(ra, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    a0 = s2;
    jal(0x2BAC28, gen::fn_strlen_00524388);
    a1 = addiu(v0, 16);
    a0 = 1024;
    jal(0x2BAC38, gen::fn_sub_27EC10_0027ec10);
    s0 = v0;
    lbu(v1, v0, 71);
    v1 = v1 & 0xFE;
    sb(v1, v0, 71);
    v1 = lui(0x2C);
    v1 = addiu(v1, -21984);
    sw(v1, v0, 104);
    v1 = lui(0x2C);
    v1 = addiu(v1, -21808);
    sw(v1, v0, 108);
    lw(v1, v0, 120);
    sw(s3, v1, 0);
    v0 = addiu(v1, 16);
    sw(v0, v1, 8);
    sh(s1, v1, 12);
    lw(a0, v1, 8);
    a1 = s2;
    jal(0x2BAC84, gen::fn_strcpy_00524270);
    v0 = s0;
    ld(ra, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 80);
}

// sub_2BACB0 [unit effect start]: start (+104) of packet kind 0x301: references the BED (sub_2B9300), raises both
// units' busy counts +160, picks the effect slot pool of the unit chosen by +12 (+2556) and allocates a slot
// (sub_2BB9C0) into +16.
void Cpu::sub_2BACB0() {
    enter(20);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    sw(zero, a0, 24);
    lw(a0, a0, 0);
    jal(0x2BACC8, gen::fn_sub_2B9300_002b9300);
    lw(v1, s0, 4);
    lhu(v0, v1, 160);
    v0 = addiu(v0, 1);
    sh(v0, v1, 160);
    lw(v1, s0, 8);
    lhu(v0, v1, 160);
    v0 = addiu(v0, 1);
    sh(v0, v1, 160);
    lh(v1, s0, 12);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
            goto L_002bad30;
        }
        charge(5);
        lw(v0, s0, 4);
        lw(v0, v0, 2556);
        sw(v0, s0, 20);
    } else {
        charge(3);
        lw(v0, s0, 8);
        lw(v0, v0, 2556);
        sw(v0, s0, 20);
    }
L_002bad30:
    charge(9);
    lw(a0, s0, 20);
    jal(0x2BAD34, gen::fn_sub_2BB9C0_002bb9c0);
    sw(v0, s0, 16);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// sub_2BAD60 [unit effect update]: update (+108) of packet kind 0x301: once the BED is bound and the slot visible: at
// frame 0 creates the instance on the slot (sub_2B93E0, kept: heap) for side +12 unless both bits 0xC00 of +28 are set;
// counts the frame +24 by 2 up to twice the side's duration - 13, then starts the slot's fade-out (0x100). Returns 1
// when the slot has faded out, else 0.
void Cpu::sub_2BAD60() {
    enter(12);
    sp = addiu(sp, -80);
    sd(ra, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s3 = a0;
    lw(a0, a0, 0);
    jal(0x2BAD80, gen::fn_sub_2B9350_002b9350);
    if (v0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(6);
        lw(s0, s3, 16);
        lw(v1, s0, 4);
        v0 = lui(0xFF00);
        v0 = v1 & v0;
        if (v0 == 0) {
            charge(3);
            v0 = 1;
            goto L_002bae98;
        }
        charge(8);
        lhu(a1, s3, 12);
        lw(a0, s3, 0);
        jal(0x2BADC8, gen::fn_sub_2B9370_002b9370);
        lhu(a0, s0, 0);
        v1 = a0 & 0x40;
        if (v1 == 0) {
            charge(6);
            lw(v1, s3, 24);
            v0 = sll(v0, 1);
            v0 = addiu(v0, -13);
            v0 = slt(v1, v0);
            if (v0 == 0) {
                charge(5);
                v0 = a0 | 0x100;
                sh(v0, s0, 0);
                v0 = 0;
                goto L_002bae98;
            }
            charge(2);
            if (v1 == 0) {
                charge(5);
                lw(t0, s3, 28);
                v1 = t0 & 0xC00;
                v0 = 3072;
                if (v1 == v0) goto L_002bae88;
                charge(4);
                lh(v1, s3, 12);
                v0 = 1;
                if (v1 != v0) {
                    charge(2);
                    if (v1 != 0) {
                        charge(2);
                        goto L_002bae60;
                    }
                    charge(4);
                    lw(s2, s3, 4);
                    lw(s1, s3, 8);
                } else {
                    charge(2);
                    lw(s2, s3, 8);
                    lw(s1, s3, 4);
                }
L_002bae60:
                charge(10);
                a1 = v1 & 0xFFFF;
                lw(a0, s3, 0);
                a2 = s2;
                a3 = s1;
                jal(0x2BAE70, gen::fn_sub_2B93E0_002b93e0);
                sw(v0, s0, 16);
                lhu(v0, s0, 0);
                v0 = v0 | 0x30;
                sh(v0, s0, 0);
            }
L_002bae88:
            charge(3);
            lw(v0, s3, 24);
            v0 = addiu(v0, 2);
            sw(v0, s3, 24);
        }
        charge(1);
        v0 = 0;
    }
L_002bae98:
    charge(8);
    ld(ra, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 80);
}

// sub_2BAEC0 [unit effect done?]: finished test (+116) of packet kind 0x301: 0 until the BED is bound, then frame +24
// >= 2 * the group word (sub_2B93C0, at least 2).
void Cpu::sub_2BAEC0() {
    enter(9);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    lw(a0, a0, 0);
    jal(0x2BAED4, gen::fn_sub_2B9350_002b9350);
    if (v0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(7);
        lhu(a1, s0, 12);
        lw(a0, s0, 0);
        jal(0x2BAEF8, gen::fn_sub_2B93C0_002b93c0);
        v1 = sll(v0, 1);
        if (lez(v1)) {
            charge(1);
            v1 = 2;
        }
        charge(3);
        lw(v0, s0, 24);
        v0 = slt(v0, v1);
        v0 = v0 ^ 0x1;
    }
    charge(5);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// sub_2BAF30 [unit effect end]: end (+112) of packet kind 0x301: frees the slot (sub_2BBAC0), drops the BED reference
// (sub_2B9030) and both busy counts.
void Cpu::sub_2BAF30() {
    enter(24);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    lw(a0, a0, 20);
    lw(a1, s0, 16);
    jal(0x2BAF48, gen::fn_sub_2BBAC0_002bbac0);
    lw(a0, s0, 0);
    jal(0x2BAF54, gen::fn_sub_2B9030_002b9030);
    lw(a0, s0, 4);
    lhu(v1, a0, 160);
    v1 = addiu(v1, -1);
    sh(v1, a0, 160);
    lw(a0, s0, 8);
    lhu(v1, a0, 160);
    v1 = addiu(v1, -1);
    sh(v1, a0, 160);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// sub_2BAF90 [create unit effect]: creates packet kind 0x301 (32-byte payload: a0..a2, (u16)a3, $t0 at +28) with start
// / update / finished / end sub_2BACB0 / sub_2BAD60 / sub_2BAEC0 / sub_2BAF30.
void Cpu::sub_2BAF90() {
    enter(46);
    sp = addiu(sp, -96);
    sd(ra, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    s0 = t0;
    a0 = 769;
    a1 = 32;
    jal(0x2BAFC8, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, 71);
    v1 = v1 & 0xEF;
    sb(v1, v0, 71);
    v1 = lui(0x2C);
    v1 = addiu(v1, -21328);
    sw(v1, v0, 104);
    v1 = lui(0x2C);
    v1 = addiu(v1, -21152);
    sw(v1, v0, 108);
    v1 = lui(0x2C);
    v1 = addiu(v1, -20800);
    sw(v1, v0, 116);
    v1 = lui(0x2C);
    v1 = addiu(v1, -20688);
    sw(v1, v0, 112);
    lw(v1, v0, 120);
    sw(s4, v1, 0);
    sw(s3, v1, 4);
    sw(s2, v1, 8);
    sh(s1, v1, 12);
    sw(s0, v1, 28);
    ld(ra, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 96);
}

// sub_2BB050 [unit effect 2 start]: start (+104) of packet kind 0x302: references the BED, raises the unit's busy count
// and allocates a slot from its pool into +24.
void Cpu::sub_2BB050() {
    enter(22);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    sw(zero, a0, 28);
    lw(a0, a0, 0);
    jal(0x2BB068, gen::fn_sub_2B9300_002b9300);
    lw(v1, s0, 4);
    lhu(v0, v1, 160);
    v0 = addiu(v0, 1);
    sh(v0, v1, 160);
    lw(v0, s0, 4);
    lw(a0, v0, 2556);
    jal(0x2BB088, gen::fn_sub_2BB9C0_002bb9c0);
    sw(v0, s0, 24);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// sub_2BB0B0 [unit effect 2 update]: update (+108) of packet kind 0x302: like sub_2BAD60 for one unit, the length from
// +32 (0x4000: +28 + 1, else twice the duration), an optional end test (sub_27E310 on +16), the 0x2000 fade step and
// the slot's fade-out from frame 2; returns 1 when the slot has faded out.
void Cpu::sub_2BB0B0() {
    enter(11);
    sp = addiu(sp, -64);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s2 = a0;
    lw(a0, a0, 0);
    jal(0x2BB0CC, gen::fn_sub_2B9350_002b9350);
    if (v0 == 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(6);
        lw(s0, s2, 24);
        lw(v1, s0, 4);
        v0 = lui(0xFF00);
        v0 = v1 & v0;
        if (v0 == 0) {
            charge(3);
            v0 = 1;
            goto L_002bb268;
        }
        charge(4);
        lhu(v0, s0, 0);
        v0 = v0 & 0x40;
        if (v0 == 0) {
            charge(4);
            lhu(v0, s2, 32);
            v0 = v0 & 0x4000;
            if (v0 == 0) {
                charge(7);
                lw(a0, s2, 0);
                a1 = 0;
                jal(0x2BB134, gen::fn_sub_2B9370_002b9370);
                s1 = sll(v0, 1);
            } else {
                charge(2);
                lw(v0, s2, 28);
                s1 = addiu(v0, 1);
            }
            charge(3);
            lw(v0, s2, 8);
            if (v0 != 0) {
                charge(6);
                lw(v1, s2, 28);
                v0 = sll(v0, 1);
                v0 = addiu(v0, -13);
                at = slt(v1, v0);
                if (at == 0) goto L_002bb1c4;
            }
            charge(3);
            ld(a0, s2, 16);
            if (a0 != 0) {
                charge(11);
                v0 = lui(0x3FFF);
                v0 = v0 | 0xFFFF;
                v1 = dsll32(v0, 0);
                v0 = 0xFFFF;
                v0 = dsll(v0, 16);
                v0 = v0 | 0xFFFF;
                a1 = v0 | v1;
                jal(0x2BB19C, gen::fn_sub_27E310_0027e310);
                if (v0 == 0) goto L_002bb1c4;
            }
            charge(2);
            if (s1 == 0) goto L_002bb1fc;
            charge(4);
            lw(v0, s2, 28);
            v0 = slt(v0, s1);
            if (v0 != 0) goto L_002bb1fc;
L_002bb1c4:
            charge(4);
            lhu(v0, s2, 32);
            v0 = v0 & 0x2000;
            if (v0 != 0) {
                charge(3);
                v1 = 4;
                lw(v0, s2, 24);
                sb(v1, v0, 8);
            }
            charge(7);
            lw(v1, s2, 24);
            lhu(v0, v1, 0);
            v0 = v0 | 0x100;
            sh(v0, v1, 0);
            v0 = 0;
            goto L_002bb268;
L_002bb1fc:
            charge(3);
            lw(v1, s2, 28);
            if (v1 == 0) {
                charge(10);
                lw(a2, s2, 4);
                lhu(t0, s2, 32);
                lw(a0, s2, 0);
                a1 = 0;
                a3 = a2;
                jal(0x2BB21C, gen::fn_sub_2B93E0_002b93e0);
                sw(v0, s0, 16);
            } else {
                charge(3);
                v0 = 2;
                if (v1 != v0) goto L_002bb258;
                charge(7);
                lhu(v0, s0, 0);
                v0 = v0 | 0xB0;
                sh(v0, s0, 0);
                lw(v0, s0, 4);
                v0 = dsll32(v0, 8);
                v0 = dsrl32(v0, 8);
                sw(v0, s0, 4);
            }
L_002bb258:
            charge(3);
            lw(v0, s2, 28);
            v0 = addiu(v0, 2);
            sw(v0, s2, 28);
        }
        charge(1);
        v0 = 0;
    }
L_002bb268:
    charge(7);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
}

// sub_2BB290 [unit effect 2 end]: end (+112) of packet kind 0x302: frees the slot, drops the BED reference and the busy
// count.
void Cpu::sub_2BB290() {
    enter(21);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    lw(v0, a0, 4);
    lw(a0, v0, 2556);
    lw(a1, s0, 24);
    jal(0x2BB2AC, gen::fn_sub_2BBAC0_002bbac0);
    lw(a0, s0, 0);
    jal(0x2BB2B8, gen::fn_sub_2B9030_002b9030);
    lw(a0, s0, 4);
    lhu(v1, a0, 160);
    v1 = addiu(v1, -1);
    sh(v1, a0, 160);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// sub_2BB2F0 [create unit effect 2]: creates packet kind 0x302 (40-byte payload: a0..a2, the 64-bit a3 at +16, (u16)$t0
// at +32) with start / update / end sub_2BB050 / sub_2BB0B0 / sub_2BB290.
void Cpu::sub_2BB2F0() {
    enter(43);
    sp = addiu(sp, -96);
    sd(ra, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s4 = a0;
    s3 = a1;
    s2 = a2;
    s1 = a3;
    s0 = t0;
    a0 = 770;
    a1 = 40;
    jal(0x2BB328, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, 71);
    v1 = v1 & 0xEF;
    sb(v1, v0, 71);
    v1 = lui(0x2C);
    v1 = addiu(v1, -20400);
    sw(v1, v0, 104);
    v1 = lui(0x2C);
    v1 = addiu(v1, -20304);
    sw(v1, v0, 108);
    v1 = lui(0x2C);
    v1 = addiu(v1, -19824);
    sw(v1, v0, 112);
    lw(v1, v0, 120);
    sw(s4, v1, 0);
    sw(s3, v1, 4);
    sw(s2, v1, 8);
    sd(s1, v1, 16);
    sh(s0, v1, 32);
    ld(ra, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 96);
}

// =================================================================================================================
// effect slots (gBtl's slot list +400, linked by +32; a unit's pool of 48 slots, in-use mask +192)
// =================================================================================================================

// sub_2BB3A0 [update slots]: per-frame update of every effect slot (+0 flags, +4 colour with the alpha in the top byte,
// +8 fade step, +12 frame, +16 instance, +20 effect object, +24 model): fades the alpha in (0x80) or out (0x100) by the
// step, updates the parts under 0x220 (sub_317730, sub_3252A0, sub_2BA3A0) and draws them under 0x210 when the alpha is
// not 0 (sub_318AD0 / sub_317A20, sub_326030 / sub_325500, sub_2BA900).
void Cpu::sub_2BB3A0() {
    enter(8);
    sp = addiu(sp, -64);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    lw(v1, gp, -18692);
    lw(s1, v1, 400);
    for (;;) {  // L_002bb560
        charge(2);
        if (s1 == 0) break;
        backedge();
        charge(5);
        lw(s0, s1, 4);
        lhu(a2, s1, 0);
        v1 = a2 & 0x40;
        if (v1 == 0) {
            charge(3);
            v1 = a2 & 0x100;
            if (v1 != 0) {
                charge(7);
                lbu(v1, s1, 8);
                a0 = sll(v1, 24);
                v1 = lui(0xFF00);
                v1 = s0 & v1;
                at = sltu(a0, v1);
                if (at != 0) {
                    charge(3);
                    s0 = subu(s0, a0);
                    goto L_002bb46c;
                }
                charge(6);
                s0 = dsll32(s0, 8);
                s0 = dsrl32(s0, 8);
                v1 = a2 & 0xFE7F;
                sh(v1, s1, 0);
            } else {
                charge(3);
                v1 = a2 & 0x80;
                if (v1 == 0) goto L_002bb46c;
                charge(8);
                lbu(v1, s1, 8);
                a1 = sll(v1, 24);
                a0 = lui(0xFF00);
                v1 = s0 & a0;
                v1 = subu(a0, v1);
                at = sltu(a1, v1);
                if (at != 0) {
                    charge(3);
                    s0 = addu(s0, a1);
                    goto L_002bb46c;
                }
                charge(5);
                v1 = dsll32(s0, 8);
                v1 = dsrl32(v1, 8);
                s0 = v1 | a0;
                v1 = a2 & 0xFE7F;
                sh(v1, s1, 0);
            }
L_002bb46c:
            charge(5);
            lhu(v1, s1, 0);
            a0 = v1 & 0x220;
            v1 = 544;
            if (a0 != v1) goto L_002bb4bc;
            charge(3);
            lw(a0, s1, 24);
            if (a0 != 0) {
                charge(2);
                jal(0x2BB48C, gen::fn_sub_317730_00317730);
            }
            charge(3);
            lw(a0, s1, 20);
            if (a0 != 0) {
                charge(2);
                jal(0x2BB4A0, gen::fn_sub_3252A0_003252a0);
            }
            charge(3);
            lw(a0, s1, 16);
            if (a0 == 0) goto L_002bb4bc;
            charge(2);
            jal(0x2BB4B4, gen::fn_sub_2BA3A0_002ba3a0);
        }
L_002bb4bc:
        charge(5);
        lhu(v1, s1, 0);
        a0 = v1 & 0x210;
        v1 = 528;
        if (a0 == v1) {
            charge(4);
            v1 = lui(0xFF00);
            v1 = s0 & v1;
            if (v1 == 0) goto L_002bb54c;
            charge(3);
            lw(v1, s1, 24);
            if (v1 != 0) {
                charge(8);
                sw(s0, sp, 60);
                lw(a0, s1, 24);
                a1 = addiu(sp, 60);
                jal(0x2BB4F8, gen::fn_sub_318AD0_00318ad0);
                lw(a0, s1, 24);
                jal(0x2BB504, gen::fn_sub_317A20_00317a20);
            }
            charge(3);
            lw(a0, s1, 20);
            if (a0 != 0) {
                charge(6);
                a1 = s0;
                jal(0x2BB51C, gen::fn_sub_326030_00326030);
                lw(a0, s1, 20);
                jal(0x2BB528, gen::fn_sub_325500_00325500);
            }
            charge(3);
            lw(v1, s1, 16);
            if (v1 == 0) goto L_002bb54c;
            charge(4);
            sw(s0, v1, 16);
            lw(a0, s1, 16);
            jal(0x2BB544, gen::fn_sub_2BA900_002ba900);
        }
L_002bb54c:
        charge(5);
        sw(s0, s1, 4);
        lw(v1, s1, 12);
        v1 = addiu(v1, 1);
        sw(v1, s1, 12);
        lw(s1, s1, 32);
    }
    charge(6);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
}

// sub_2BB580 [reset slot]: releases a slot's instance (sub_2B94F0), effect object (sub_3257E0) and model (sub_3174E0),
// then colour -1, step 20, frame 0, flags 0x200.
void Cpu::sub_2BB580() {
    enter(7);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    lw(a0, a0, 16);
    if (a0 != 0) {
        charge(3);
        jal(0x2BB59C, gen::fn_sub_2B94F0_002b94f0);
        sw(zero, s0, 16);
    }
    charge(3);
    lw(a0, s0, 20);
    if (a0 != 0) {
        charge(3);
        jal(0x2BB5B4, gen::fn_sub_3257E0_003257e0);
        sw(zero, s0, 20);
    }
    charge(3);
    lw(a0, s0, 24);
    if (a0 != 0) {
        charge(3);
        jal(0x2BB5CC, gen::fn_sub_3174E0_003174e0);
        sw(zero, s0, 24);
    }
    charge(12);
    v1 = si(-1);
    sw(v1, s0, 4);
    v1 = 20;
    sb(v1, s0, 8);
    sw(zero, s0, 12);
    v1 = 512;
    sh(v1, s0, 0);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// nullsub_14: nullsub_14: returns.
void Cpu::nullsub_14() {
    enter(2);
}

// sub_2BB770 [free all slots]: frees every slot of gBtl's list (sub_2BB610, kept: heap) and then the list (sub_2BC2F0,
// kept).
void Cpu::sub_2BB770() {
    enter(7);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    lw(v0, gp, -18692);
    lw(a0, v0, 400);
    for (;;) {  // L_002bb79c
        charge(4);
        if (a0 == 0) break;
        backedge();
        charge(4);
        lw(s0, a0, 32);
        jal(0x2BB790, gen::fn_sub_2BB610_002bb610);
        a0 = s0;
    }
    charge(7);
    jal(0x2BB7AC, gen::fn_sub_2BC2F0_002bc2f0);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// sub_2BB9C0 [alloc slot]: takes the first free slot of a unit's 48-slot pool (in-use mask +192), resets it
// (sub_2BB580's steps) and returns it; 0 when all are in use -- which never happens: the mask is one 32-bit word and
// the bit of slot i is (1 << i) as a 32-bit shift, 0 from slot 32 on, so slots 32..47 always look free (slot 32 is
// handed out again and again once 0..31 are taken).
void Cpu::sub_2BB9C0() {
    enter(10);
    sp = addiu(sp, -64);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s2 = a0;
    s0 = 1;
    v1 = 0;
    for (;;) {  // L_002bba88
        charge(3);
        v0 = sltiu(v1, 48);
        if (v0 == 0) break;
        backedge();
        charge(4);
        lw(v0, s2, 192);
        v0 = v0 & s0;
        if (v0 == 0) {
            charge(6);
            v0 = sll(v1, 2);
            v0 = addu(s2, v0);
            lw(s1, v0, 0);
            lw(a0, s1, 16);
            if (a0 != 0) {
                charge(3);
                jal(0x2BBA10, gen::fn_sub_2B94F0_002b94f0);
                sw(zero, s1, 16);
            }
            charge(3);
            lw(a0, s1, 20);
            if (a0 != 0) {
                charge(3);
                jal(0x2BBA28, gen::fn_sub_3257E0_003257e0);
                sw(zero, s1, 20);
            }
            charge(3);
            lw(a0, s1, 24);
            if (a0 != 0) {
                charge(3);
                jal(0x2BBA40, gen::fn_sub_3174E0_003174e0);
                sw(zero, s1, 24);
            }
            charge(13);
            v0 = si(-1);
            sw(v0, s1, 4);
            v0 = 20;
            sb(v0, s1, 8);
            sw(zero, s1, 12);
            v0 = 512;
            sh(v0, s1, 0);
            lw(v0, s2, 192);
            v0 = v0 | s0;
            sw(v0, s2, 192);
            v0 = s1;
            goto L_002bba98;
        }
        charge(2);
        s0 = sll(s0, 1);
        v1 = addiu(v1, 1);
    }
    charge(1);
    v0 = 0;
L_002bba98:
    charge(7);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
}

// sub_2BBAC0 [free slot]: returns slot a1 to pool a0: resets it and clears its in-use bit; 1, or 0 when the slot is not
// in the pool.
void Cpu::sub_2BBAC0() {
    enter(11);
    sp = addiu(sp, -64);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s2 = a0;
    s1 = a1;
    s0 = 1;
    v1 = 0;
    for (;;) {  // L_002bbb88
        charge(3);
        v0 = sltiu(v1, 48);
        if (v0 == 0) break;
        backedge();
        charge(5);
        v0 = sll(v1, 2);
        v0 = addu(s2, v0);
        lw(v0, v0, 0);
        if (v0 == s1) {
            charge(3);
            lw(a0, s1, 16);
            if (a0 != 0) {
                charge(3);
                jal(0x2BBB0C, gen::fn_sub_2B94F0_002b94f0);
                sw(zero, s1, 16);
            }
            charge(3);
            lw(a0, s1, 20);
            if (a0 != 0) {
                charge(3);
                jal(0x2BBB24, gen::fn_sub_3257E0_003257e0);
                sw(zero, s1, 20);
            }
            charge(3);
            lw(a0, s1, 24);
            if (a0 != 0) {
                charge(3);
                jal(0x2BBB3C, gen::fn_sub_3174E0_003174e0);
                sw(zero, s1, 24);
            }
            charge(14);
            v0 = si(-1);
            sw(v0, s1, 4);
            v0 = 20;
            sb(v0, s1, 8);
            sw(zero, s1, 12);
            v0 = 512;
            sh(v0, s1, 0);
            v1 = ~(s0 | zero);
            lw(v0, s2, 192);
            v0 = v0 & v1;
            sw(v0, s2, 192);
            v0 = 1;
            goto L_002bbb98;
        }
        charge(2);
        s0 = sll(s0, 1);
        v1 = addiu(v1, 1);
    }
    charge(1);
    v0 = 0;
L_002bbb98:
    charge(7);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
}

// sub_2BBBC0 [slots hidden]: clears flag 0x200 of all 48 slots of a pool.
void Cpu::sub_2BBBC0() {
    enter(3);
    a2 = 0;
    for (;;) {  // L_002bbbe8
        charge(3);
        v1 = sltiu(a2, 48);
        if (v1 == 0) break;
        backedge();
        charge(7);
        v1 = sll(a2, 2);
        v1 = addu(a0, v1);
        lw(a1, v1, 0);
        lhu(v1, a1, 0);
        v1 = v1 & 0xFDFF;
        sh(v1, a1, 0);
        a2 = addiu(a2, 1);
    }
    charge(2);
}

// sub_2BBDC0 [set slot effect]: sets the attached effect id +16 (s16) and marks the record dirty (+0 bit 0) when it
// changes.
void Cpu::sub_2BBDC0() {
    enter(5);
    lh(a2, a0, 16);
    v1 = dsll32(a1, 16);
    v1 = dsra32(v1, 16);
    if (a2 != v1) {
        charge(4);
        lbu(v1, a0, 0);
        v1 = v1 | 0x1;
        sb(v1, a0, 0);
        sh(a1, a0, 16);
    }
    charge(2);
}

// sub_2BBDF0 [slot effect]: returns the attached effect id +16.
void Cpu::sub_2BBDF0() {
    enter(3);
    lh(v0, a0, 16);
}

// sub_2BBE00 [refresh slot effect]: under gBtl's flag +12 0x40000: a dirty record (+0 bit 0) resets its slot (+8),
// drops its BED (+12, sub_2B9030) and, for an effect id other than -1, takes the BED of that id (gBtl +3108 + 4 id),
// references it and creates the instance on the slot (sub_2B93E0); then shows (0x30, colour +20) or hides the slot.
void Cpu::sub_2BBE00() {
    enter(11);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    lw(v1, gp, -18692);
    lw(a0, v1, 12);
    v1 = lui(0x4);
    v1 = a0 & v1;
    if (v1 != 0) {
        charge(4);
        lbu(v1, s0, 0);
        v1 = v1 & 0x1;
        if (v1 != 0) {
            charge(4);
            lw(s1, s0, 8);
            lw(a0, s1, 16);
            if (a0 != 0) {
                charge(3);
                jal(0x2BBE4C, gen::fn_sub_2B94F0_002b94f0);
                sw(zero, s1, 16);
            }
            charge(3);
            lw(a0, s1, 20);
            if (a0 != 0) {
                charge(3);
                jal(0x2BBE64, gen::fn_sub_3257E0_003257e0);
                sw(zero, s1, 20);
            }
            charge(3);
            lw(a0, s1, 24);
            if (a0 != 0) {
                charge(3);
                jal(0x2BBE7C, gen::fn_sub_3174E0_003174e0);
                sw(zero, s1, 24);
            }
            charge(10);
            v1 = si(-1);
            sw(v1, s1, 4);
            v1 = 20;
            sb(v1, s1, 8);
            sw(zero, s1, 12);
            v1 = 512;
            sh(v1, s1, 0);
            lw(a0, s0, 12);
            if (a0 != 0) {
                charge(3);
                jal(0x2BBEB0, gen::fn_sub_2B9030_002b9030);
                sw(zero, s0, 12);
            }
            charge(4);
            lh(a0, s0, 16);
            v1 = si(-1);
            if (a0 != v1) {
                charge(16);
                lw(v1, gp, -18692);
                v0 = sll(a0, 2);
                v0 = addu(v0, v1);
                lw(a0, v0, 3108);
                sw(a0, s0, 12);
                jal(0x2BBEE0, gen::fn_sub_2B9300_002b9300);
                lw(a2, s0, 4);
                lw(a0, s0, 12);
                a1 = 1;
                a3 = a2;
                t0 = 0;
                jal(0x2BBEFC, gen::fn_sub_2B93E0_002b93e0);
                lw(v1, s0, 8);
                sw(v0, v1, 16);
            }
            charge(3);
            lbu(v1, s0, 0);
            v1 = v1 & 0xFE;
            sb(v1, s0, 0);
        }
        charge(4);
        lh(a0, s0, 16);
        v1 = si(-1);
        if (a0 != v1) {
            charge(9);
            lw(a0, s0, 8);
            lhu(v1, a0, 0);
            v1 = v1 | 0x30;
            sh(v1, a0, 0);
            lw(a0, s0, 20);
            lw(v1, s0, 8);
            sw(a0, v1, 4);
            goto L_002bbf5c;
        }
        charge(4);
        lw(a0, s0, 8);
        lhu(v1, a0, 0);
        v1 = v1 & 0xFFCF;
        sh(v1, a0, 0);
    }
L_002bbf5c:
    charge(6);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// sub_2BBF80 [set slot alpha]: +20 = (a1 & 0xFF000000) | 0xFFFFFF.
void Cpu::sub_2BBF80() {
    enter(8);
    v1 = lui(0xFF00);
    a1 = a1 & v1;
    v1 = lui(0xFF);
    v1 = v1 | 0xFFFF;
    v1 = a1 | v1;
    sw(v1, a0, 20);
}

// sub_2BBFA0 [affinity icon]: the icon of an affinity bit: 1..0x80 -> 39, 40, 41, 42, 43, 36, 37, 38; 0x100 -> 45,
// 0x200 -> 44; 0 and anything else (0x400, 0x80000, 0x100000 too) -> -1.
void Cpu::sub_2BBFA0() {
    enter(2);
    if (a0 == 0) {
        charge(3);
        v0 = si(-1);
    } else {
        charge(3);
        v0 = lui(0x10);
        if (a0 != v0) {
            charge(3);
            v0 = lui(0x8);
            if (a0 == v0) goto L_002bc0d0;
            charge(3);
            v0 = 1024;
            if (a0 == v0) goto L_002bc0d0;
            charge(3);
            v0 = 512;
            if (a0 != v0) {
                charge(3);
                v0 = 256;
                if (a0 != v0) {
                    charge(3);
                    v0 = 128;
                    if (a0 != v0) {
                        charge(3);
                        v0 = 64;
                        if (a0 != v0) {
                            charge(3);
                            v0 = 32;
                            if (a0 != v0) {
                                charge(3);
                                v0 = 16;
                                if (a0 != v0) {
                                    charge(3);
                                    v0 = 8;
                                    if (a0 != v0) {
                                        charge(3);
                                        v0 = 4;
                                        if (a0 != v0) {
                                            charge(3);
                                            v0 = 2;
                                            if (a0 != v0) {
                                                charge(3);
                                                v0 = 1;
                                                if (a0 != v0) {
                                                    charge(2);
                                                    goto L_002bc0d0;
                                                }
                                                charge(3);
                                                v0 = 39;
                                                goto L_002bc0d4;
                                            }
                                            charge(3);
                                            v0 = 40;
                                            goto L_002bc0d4;
                                        }
                                        charge(3);
                                        v0 = 41;
                                        goto L_002bc0d4;
                                    }
                                    charge(3);
                                    v0 = 42;
                                    goto L_002bc0d4;
                                }
                                charge(3);
                                v0 = 43;
                                goto L_002bc0d4;
                            }
                            charge(3);
                            v0 = 36;
                            goto L_002bc0d4;
                        }
                        charge(3);
                        v0 = 37;
                        goto L_002bc0d4;
                    }
                    charge(3);
                    v0 = 38;
                    goto L_002bc0d4;
                }
                charge(3);
                v0 = 45;
                goto L_002bc0d4;
            }
            charge(3);
            v0 = 44;
            goto L_002bc0d4;
        }
L_002bc0d0:
        charge(1);
        v0 = si(-1);
    }
L_002bc0d4:
    charge(2);
}

// =================================================================================================================
// battle event packets (kinds 0x306..0x30A, the HP / SP gauges 0x500 / 0x501, 0x504..0x50A) and the affinity colours
// =================================================================================================================

// sub_2BC0E0 [affinity colour]: writes the RGBA colour of an affinity bit to a1 (alpha 255): 1 (255,148,188), 2
// (178,158,255), 4 (205,178,205), 8 (168,168,255), 0x10 (255,178,158), 0x20 (138,198,255), 0x40 (245,218,128), 0x80
// (255,108,228), 0x200 (255,58,68), 0x400 (255,64,18); 0x100 and anything else the default colour gp-25472..-25469.
void Cpu::sub_2BC0E0() {
    enter(5);
    a3 = 255;
    sb(a3, a1, 3);
    v1 = lui(0x8);
    if (a0 != v1) {
        charge(3);
        v1 = lui(0x10);
        if (a0 == v1) goto L_002bc2c8;
        charge(3);
        v1 = 1024;
        if (a0 != v1) {
            charge(3);
            v1 = 256;
            if (a0 != v1) {
                charge(3);
                v1 = 512;
                if (a0 != v1) {
                    charge(3);
                    a2 = 128;
                    if (a0 != a2) {
                        charge(3);
                        v1 = 64;
                        if (a0 != v1) {
                            charge(3);
                            v1 = 32;
                            if (a0 != v1) {
                                charge(3);
                                v1 = 16;
                                if (a0 != v1) {
                                    charge(3);
                                    v1 = 8;
                                    if (a0 != v1) {
                                        charge(3);
                                        v1 = 4;
                                        if (a0 != v1) {
                                            charge(3);
                                            v1 = 2;
                                            if (a0 != v1) {
                                                charge(3);
                                                v1 = 1;
                                                if (a0 != v1) {
                                                    charge(2);
                                                    goto L_002bc2c8;
                                                }
                                                charge(7);
                                                sb(a3, a1, 0);
                                                v1 = 148;
                                                sb(v1, a1, 1);
                                                v1 = 188;
                                                sb(v1, a1, 2);
                                                goto L_002bc2e8;
                                            }
                                            charge(7);
                                            v1 = 178;
                                            sb(v1, a1, 0);
                                            v1 = 158;
                                            sb(v1, a1, 1);
                                            sb(a3, a1, 2);
                                            goto L_002bc2e8;
                                        }
                                        charge(7);
                                        a0 = 205;
                                        sb(a0, a1, 0);
                                        v1 = 178;
                                        sb(v1, a1, 1);
                                        sb(a0, a1, 2);
                                        goto L_002bc2e8;
                                    }
                                    charge(6);
                                    v1 = 168;
                                    sb(v1, a1, 0);
                                    sb(v1, a1, 1);
                                    sb(a3, a1, 2);
                                    goto L_002bc2e8;
                                }
                                charge(7);
                                sb(a3, a1, 0);
                                v1 = 178;
                                sb(v1, a1, 1);
                                v1 = 158;
                                sb(v1, a1, 2);
                                goto L_002bc2e8;
                            }
                            charge(7);
                            v1 = 138;
                            sb(v1, a1, 0);
                            v1 = 198;
                            sb(v1, a1, 1);
                            sb(a3, a1, 2);
                            goto L_002bc2e8;
                        }
                        charge(7);
                        v1 = 245;
                        sb(v1, a1, 0);
                        v1 = 218;
                        sb(v1, a1, 1);
                        sb(a2, a1, 2);
                        goto L_002bc2e8;
                    }
                    charge(7);
                    sb(a3, a1, 0);
                    v1 = 108;
                    sb(v1, a1, 1);
                    v1 = 228;
                    sb(v1, a1, 2);
                    goto L_002bc2e8;
                }
                charge(7);
                sb(a3, a1, 0);
                v1 = 58;
                sb(v1, a1, 1);
                v1 = 68;
                sb(v1, a1, 2);
                goto L_002bc2e8;
            }
            charge(10);
            lbu(a3, gp, -25472);
            lbu(a2, gp, -25471);
            lbu(a0, gp, -25470);
            lbu(v1, gp, -25469);
            sb(a3, a1, 0);
            sb(a2, a1, 1);
            sb(a0, a1, 2);
            sb(v1, a1, 3);
            goto L_002bc2e8;
        }
        charge(7);
        sb(a3, a1, 0);
        v1 = 64;
        sb(v1, a1, 1);
        v1 = 18;
        sb(v1, a1, 2);
        goto L_002bc2e8;
    }
L_002bc2c8:
    charge(8);
    lbu(a3, gp, -25472);
    lbu(a2, gp, -25471);
    lbu(a0, gp, -25470);
    lbu(v1, gp, -25469);
    sb(a3, a1, 0);
    sb(a2, a1, 1);
    sb(a0, a1, 2);
    sb(v1, a1, 3);
L_002bc2e8:
    charge(2);
}

// sub_2BC680 [create 0x306]: creates packet kind 0x306 (no payload, flag 0x1 of +71 cleared) with start sub_2BC420
// (kept: file I/O) and update sub_2BC480 (kept: heap).
void Cpu::sub_2BC680() {
    enter(19);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    a0 = 774;
    a1 = 0;
    jal(0x2BC690, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, 71);
    v1 = v1 & 0xFE;
    sb(v1, v0, 71);
    v1 = lui(0x2C);
    v1 = addiu(v1, -15328);
    sw(v1, v0, 104);
    v1 = lui(0x2C);
    v1 = addiu(v1, -15232);
    sw(v1, v0, 108);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// sub_2BC7B0 [0x308 update]: update (+108) of packet kind 0x308: sub_351BB0(payload u16). Returns 1.
void Cpu::sub_2BC7B0() {
    enter(10);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    lhu(a0, a0, 0);
    jal(0x2BC7BC, gen::fn_sub_351BB0_00351bb0);
    v0 = 1;
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// sub_2BC7E0 [create 0x308]: creates packet kind 0x308 (2-byte payload: (u16)a0) with update sub_2BC7B0.
void Cpu::sub_2BC7E0() {
    enter(18);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    a0 = 776;
    a1 = 2;
    jal(0x2BC7F8, gen::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2C);
    v1 = addiu(v1, -14416);
    sw(v1, v0, 108);
    lw(v1, v0, 120);
    sh(s0, v1, 0);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// sub_2BC830 [fade update]: update (+108) of packet kind 0x30A: the screen fade (sub_108570; mode 8 by sub_108670, the
// colour bytes payload +0..+2 by sub_108680, the length payload +4 by sub_1086A0). Returns 1.
void Cpu::sub_2BC830() {
    enter(23);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    jal(0x2BC840, gen::fn_sub_108570_00108570);
    a0 = 8;
    jal(0x2BC84C, gen::fn_sub_108670_00108670);
    lbu(a0, s0, 0);
    lbu(a1, s0, 1);
    lbu(a2, s0, 2);
    jal(0x2BC860, gen::fn_sub_108680_00108680);
    lh(a0, s0, 4);
    jal(0x2BC86C, gen::fn_sub_1086A0_001086a0);
    v0 = 1;
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// sub_2BC890 [create fade]: creates packet kind 0x30A (6-byte payload: the RGBA bytes at a0, (u16)a1) with update
// sub_2BC830.
void Cpu::sub_2BC890() {
    enter(29);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    s0 = a1;
    a0 = 778;
    a1 = 6;
    jal(0x2BC8B0, gen::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2C);
    v1 = addiu(v1, -14288);
    sw(v1, v0, 108);
    lw(a3, v0, 120);
    lbu(a2, s1, 0);
    lbu(a1, s1, 1);
    lbu(a0, s1, 2);
    lbu(v1, s1, 3);
    sb(a2, a3, 0);
    sb(a1, a3, 1);
    sb(a0, a3, 2);
    sb(v1, a3, 3);
    sh(s0, a3, 4);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// sub_2BC910 [0x309 update]: update (+108) of packet kind 0x309: sub_352C50(payload +0, +4, +8). Returns 1.
void Cpu::sub_2BC910() {
    enter(13);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    v0 = a0;
    lw(a0, a0, 0);
    lw(a1, v0, 4);
    lw(a2, v0, 8);
    jal(0x2BC928, gen::fn_sub_352C50_00352c50);
    v0 = 1;
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// sub_2BC950 [create 0x309]: creates packet kind 0x309 (12-byte payload: a0, a1, a2) with update sub_2BC910.
void Cpu::sub_2BC950() {
    enter(26);
    sp = addiu(sp, -64);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    a0 = 777;
    a1 = 12;
    jal(0x2BC978, gen::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2C);
    v1 = addiu(v1, -14064);
    sw(v1, v0, 108);
    lw(v1, v0, 120);
    sw(s2, v1, 0);
    sw(s1, v1, 4);
    sw(s0, v1, 8);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
}

// sub_2BCDE0 [reset gauges]: resets the unit's two gauge animations at a1 (+0 / +20: start -1.0, value 1.0, frame +16 /
// +36 = -1).
void Cpu::sub_2BCDE0() {
    enter(11);
    a2 = lui(0xBF80);
    sw(a2, a1, 0);
    a0 = lui(0x3F80);
    sw(a0, a1, 4);
    v1 = si(-1);
    sh(v1, a1, 16);
    sw(a2, a1, 20);
    sw(a0, a1, 24);
    sh(v1, a1, 36);
}

// sub_2BCE10 [draw gauge]: animates and draws one HP / SP gauge (a2 = {f32 start, f32 value, f32 from, f32 to, s16
// frame}; a start >= 0 restarts it at frame 0): over 16 frames the value moves from `from` to `to`, and until frame 28
// the gauge is drawn at the unit's screen position (sub_1FEF10 on the model +168) + ($f12, $f13) as two textured quads
// (sprites 1 and 5 through sub_21C3F0 / sub_21CCA0 / sub_21CCE0, the second scaled by the value); a1's low byte 0 skips
// the draw.
void Cpu::sub_2BCE10() {
    enter(17);
    sp = addiu(sp, -80);
    sd(ra, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    mov_s(F22, F12);
    mov_s(F21, F13);
    s1 = a1;
    s0 = a2;
    lwc1(F1, a2, 0);
    mtc1(zero, F0);
    c_lt_s(F1, F0);
    if (!cop1_cond()) {
        charge(6);
        swc1(F1, s0, 12);
        lwc1(F0, s0, 4);
        swc1(F0, s0, 8);
        v1 = lui(0xBF80);
        sw(v1, s0, 0);
        sh(zero, s0, 16);
    }
    charge(3);
    lh(v1, s0, 16);
    if (gez(v1)) {
        charge(3);
        at = slti(v1, 28);
        if (at == 0) goto L_002bd034;
        charge(3);
        at = slti(v1, 16);
        if (at != 0) {
            charge(17);
            lwc1(F3, s0, 8);
            mtc1(v1, F0);
            cvt_s_w(F1, F0);
            v0 = lui(0x4180);
            mtc1(v0, F0);
            div_s(F2, F1, F0);
            lwc1(F0, s0, 12);
            sub_s(F1, F0, F3);
            mtc1(zero, F0);
            adda_s(F0, F3);
            madd_s(F0, F2, F1);
            swc1(F0, s0, 4);
        } else {
            charge(2);
            lwc1(F0, s0, 12);
            swc1(F0, s0, 4);
        }
        charge(6);
        lw(a0, a0, 168);
        a1 = addiu(sp, 72);
        jal(0x2BCEE4, gen::fn_sub_1FEF10_001fef10);
        if (v0 != 0) {
            charge(3);
            v1 = s1 & 0xFF;
            if (lez(v1)) goto L_002bd028;
            charge(74);
            lwc1(F20, s0, 4);
            lwc1(F0, sp, 76);
            add_s(F21, F0, F21);
            lwc1(F0, sp, 72);
            add_s(F22, F0, F22);
            a0 = 1;
            jal(0x2BCF18, gen::fn_sub_21C3F0_0021c3f0);
            a0 = v0;
            a1 = 1;
            jal(0x2BCF28, gen::fn_sub_21CCA0_0021cca0);
            s1 = v0;
            a0 = s1;
            jal(0x2BCF38, gen::fn_sub_21CCE0_0021cce0);
            lw(a0, s1, 12);
            v1 = sra(a0, 1);
            mtc1(v1, F0);
            cvt_s_w(F0, F0);
            sub_s(F22, F22, F0);
            mtc1(a0, F0);
            cvt_s_w(F14, F0);
            lwc1(F0, s1, 16);
            cvt_s_w(F15, F0);
            lwc1(F0, s1, 20);
            cvt_s_w(F16, F0);
            lwc1(F0, s1, 24);
            cvt_s_w(F17, F0);
            mov_s(F12, F22);
            mov_s(F13, F21);
            a0 = si(-1);
            a1 = v0;
            jal(0x2BCF8C, gen::fn_btlDrawTexturedQuad_002bc9c0);
            a0 = 5;
            jal(0x2BCF98, gen::fn_sub_21C3F0_0021c3f0);
            a0 = v0;
            a1 = 4;
            jal(0x2BCFA8, gen::fn_sub_21CCA0_0021cca0);
            s1 = v0;
            a0 = s1;
            jal(0x2BCFB8, gen::fn_sub_21CCE0_0021cce0);
            lwc1(F0, s1, 12);
            cvt_s_w(F0, F0);
            mul_s(F0, F0, F20);
            cvt_w_s(F0, F0);
            cvt_s_w(F14, F0);
            lwc1(F0, s1, 16);
            cvt_s_w(F15, F0);
            lwc1(F0, s1, 20);
            cvt_s_w(F0, F0);
            mul_s(F0, F0, F20);
            cvt_w_s(F0, F0);
            cvt_s_w(F16, F0);
            lwc1(F0, s1, 24);
            cvt_s_w(F17, F0);
            v1 = lui(0x4100);
            mtc1(v1, F0);
            add_s(F12, F0, F22);
            v1 = lui(0x4080);
            mtc1(v1, F0);
            add_s(F13, F0, F21);
            a0 = si(-1);
            a1 = v0;
            jal(0x2BD020, gen::fn_btlDrawTexturedQuad_002bc9c0);
        }
L_002bd028:
        charge(3);
        lh(v1, s0, 16);
        v1 = addiu(v1, 1);
        sh(v1, s0, 16);
    }
L_002bd034:
    charge(9);
    ld(ra, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 80);
}

// sub_2BD060 [gauge start]: start (+104) of packet kind 0x500: payload[0]'s busy count +160 += 1.
void Cpu::sub_2BD060() {
    enter(6);
    lw(a0, a0, 0);
    lhu(v1, a0, 160);
    v1 = addiu(v1, 1);
    sh(v1, a0, 160);
}

// sub_2BD080 [gauge update]: update (+108) of packet kind 0x500 (payload {unit, u8 which, s16 delta}): which 0 = HP, 1
// = SP: the gauge's target (+2564 / +2584) = clamp(current + delta, 0, max) / max. Returns 1.
void Cpu::sub_2BD080() {
    enter(11);
    sp = addiu(sp, -64);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    lw(s0, a0, 0);
    lbu(v1, a0, 4);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
            goto L_002bd1e4;
        }
        charge(13);
        lw(a0, s0, 2604);
        jal(0x2BD0C0, gen::fn_datCalcGetHp_002ffd70);
        s2 = dsll32(v0, 16);
        s2 = dsra32(s2, 16);
        lw(a0, s0, 2604);
        jal(0x2BD0D4, gen::fn_datCalcGetMaxHp_002ffdf0);
        v1 = dsll32(v0, 16);
        v1 = dsra32(v1, 16);
        lh(v0, s1, 6);
        if (v0 != 0) {
            charge(8);
            v0 = addu(s2, v0);
            s2 = dsll32(v0, 16);
            s2 = dsra32(s2, 16);
            v0 = dsll32(v1, 16);
            v0 = dsra32(v0, 16);
            at = slt(v0, s2);
            if (at != 0) {
                charge(3);
                s2 = v0;
                goto L_002bd128;
            }
            charge(2);
            if (gez(s2)) goto L_002bd128;
            charge(1);
            s2 = 0;
        }
L_002bd128:
        charge(12);
        mtc1(s2, F0);
        cvt_s_w(F1, F0);
        mtc1(v1, F0);
        cvt_s_w(F0, F0);
        div_s(F0, F1, F0);
        swc1(F0, s0, 2564);
    } else {
        charge(13);
        lw(a0, s0, 2604);
        jal(0x2BD15C, gen::fn_datCalcGetSp_002ffd80);
        s2 = dsll32(v0, 16);
        s2 = dsra32(s2, 16);
        lw(a0, s0, 2604);
        jal(0x2BD170, gen::fn_datCalcGetMaxSp_00300100);
        v1 = dsll32(v0, 16);
        v1 = dsra32(v1, 16);
        lh(v0, s1, 6);
        if (v0 != 0) {
            charge(8);
            v0 = addu(s2, v0);
            s2 = dsll32(v0, 16);
            s2 = dsra32(s2, 16);
            v0 = dsll32(v1, 16);
            v0 = dsra32(v0, 16);
            at = slt(v0, s2);
            if (at != 0) {
                charge(3);
                s2 = v0;
                goto L_002bd1c4;
            }
            charge(2);
            if (gez(s2)) goto L_002bd1c4;
            charge(1);
            s2 = 0;
        }
L_002bd1c4:
        charge(8);
        mtc1(s2, F0);
        cvt_s_w(F1, F0);
        mtc1(v1, F0);
        cvt_s_w(F0, F0);
        div_s(F0, F1, F0);
        swc1(F0, s0, 2584);
    }
L_002bd1e4:
    charge(8);
    v0 = 1;
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
}

// sub_2BD210 [gauge end]: end (+112) of packet kind 0x500: busy count -= 1.
void Cpu::sub_2BD210() {
    enter(6);
    lw(a0, a0, 0);
    lhu(v1, a0, 160);
    v1 = addiu(v1, -1);
    sh(v1, a0, 160);
}

// sub_2BD230 [create gauge]: creates packet kind 0x500 (8-byte payload: a0, (u8)a1, (u16)a2) with start / update / end
// sub_2BD060 / sub_2BD080 / sub_2BD210.
void Cpu::sub_2BD230() {
    enter(35);
    sp = addiu(sp, -64);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s2 = a0;
    s1 = a1;
    s0 = a2;
    a0 = 1280;
    a1 = 8;
    jal(0x2BD258, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, 71);
    v1 = v1 & 0xEF;
    sb(v1, v0, 71);
    v1 = lui(0x2C);
    v1 = addiu(v1, -12192);
    sw(v1, v0, 104);
    v1 = lui(0x2C);
    v1 = addiu(v1, -12160);
    sw(v1, v0, 108);
    v1 = lui(0x2C);
    v1 = addiu(v1, -11760);
    sw(v1, v0, 112);
    lw(v1, v0, 120);
    sw(s2, v1, 0);
    sb(s1, v1, 4);
    sh(s0, v1, 6);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
}

// sub_2BD2C0 [gauges start]: start (+104) of packet kind 0x501: busy count += 1.
void Cpu::sub_2BD2C0() {
    enter(6);
    lw(a0, a0, 0);
    lhu(v1, a0, 160);
    v1 = addiu(v1, 1);
    sh(v1, a0, 160);
}

// sub_2BD2E0 [gauges update]: update (+108) of packet kind 0x501 (payload {unit}): restarts both gauges at HP / max HP
// and SP / max SP (unsigned conversions), start -1.0, frame -1 (the HP gauge's start +2564 is written twice; the SP
// gauge's +2584 keeps its value). Returns 1.
void Cpu::sub_2BD2E0() {
    enter(10);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s0, sp, 16);
    swc1(F20, sp, 0);
    lw(s0, a0, 0);
    lw(a0, s0, 2604);
    jal(0x2BD2F8, gen::fn_datCalcGetHp_002ffd70);
    if (gez(v0)) {
        charge(5);
        mtc1(v0, F0);
        cvt_s_w(F20, F0);
    } else {
        charge(7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, F0);
        cvt_s_w(F20, F0);
        add_s(F20, F20, F20);
    }
    charge(5);
    lw(a0, s0, 2604);
    jal(0x2BD33C, gen::fn_datCalcGetMaxHp_002ffdf0);
    if (gez(v0)) {
        charge(5);
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
    } else {
        charge(7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, F0);
        cvt_s_w(F0, F0);
        add_s(F0, F0, F0);
    }
    charge(13);
    div_s(F0, F20, F0);
    swc1(F0, s0, 2568);
    v0 = lui(0xBF80);
    sw(v0, s0, 2564);
    v0 = si(-1);
    sh(v0, s0, 2580);
    lw(a0, s0, 2604);
    jal(0x2BD3A0, gen::fn_datCalcGetSp_002ffd80);
    if (gez(v0)) {
        charge(5);
        mtc1(v0, F0);
        cvt_s_w(F20, F0);
    } else {
        charge(7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, F0);
        cvt_s_w(F20, F0);
        add_s(F20, F20, F20);
    }
    charge(5);
    lw(a0, s0, 2604);
    jal(0x2BD3E4, gen::fn_datCalcGetMaxSp_00300100);
    if (gez(v0)) {
        charge(5);
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
    } else {
        charge(7);
        v1 = srl(v0, 1);
        v0 = v0 & 0x1;
        v1 = v1 | v0;
        mtc1(v1, F0);
        cvt_s_w(F0, F0);
        add_s(F0, F0, F0);
    }
    charge(15);
    div_s(F0, F20, F0);
    swc1(F0, s0, 2588);
    v0 = lui(0xBF80);
    sw(v0, s0, 2564);
    v0 = si(-1);
    sh(v0, s0, 2600);
    v0 = 1;
    ld(ra, sp, 32);
    lq(s0, sp, 16);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 48);
}

// sub_2BD460 [gauges end]: end (+112) of packet kind 0x501: busy count -= 1.
void Cpu::sub_2BD460() {
    enter(6);
    lw(a0, a0, 0);
    lhu(v1, a0, 160);
    v1 = addiu(v1, -1);
    sh(v1, a0, 160);
}

// sub_2BD480 [create gauges]: creates packet kind 0x501 (4-byte payload: a0) with start / update / end sub_2BD2C0 /
// sub_2BD2E0 / sub_2BD460.
void Cpu::sub_2BD480() {
    enter(27);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    a0 = 1281;
    a1 = 4;
    jal(0x2BD498, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, 71);
    v1 = v1 & 0xEF;
    sb(v1, v0, 71);
    v1 = lui(0x2C);
    v1 = addiu(v1, -11584);
    sw(v1, v0, 104);
    v1 = lui(0x2C);
    v1 = addiu(v1, -11552);
    sw(v1, v0, 108);
    v1 = lui(0x2C);
    v1 = addiu(v1, -11168);
    sw(v1, v0, 112);
    lw(v1, v0, 120);
    sw(s0, v1, 0);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// sub_2BD590 [create 0x504]: creates packet kind 0x504 (12-byte payload: a0, (u16)a1, 0) with update sub_2BD5F0 (not in
// the slice list).
void Cpu::sub_2BD590() {
    enter(23);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    s0 = a1;
    a0 = 1284;
    a1 = 12;
    jal(0x2BD5B0, gen::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2C);
    v1 = addiu(v1, -11024);
    sw(v1, v0, 108);
    lw(v1, v0, 120);
    sw(s1, v1, 0);
    sh(s0, v1, 4);
    sw(zero, v1, 8);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// sub_2BD690 [create 0x505]: creates packet kind 0x505 (12-byte payload: a0, (u16)a1, 0) with update sub_2BD6F0.
void Cpu::sub_2BD690() {
    enter(23);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    s0 = a1;
    a0 = 1285;
    a1 = 12;
    jal(0x2BD6B0, gen::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2C);
    v1 = addiu(v1, -10768);
    sw(v1, v0, 108);
    lw(v1, v0, 120);
    sw(s1, v1, 0);
    sh(s0, v1, 4);
    sw(zero, v1, 8);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// sub_2BD780 [create 0x507]: creates packet kind 0x507 (12-byte payload: a0, (u16)a1, 0) with update sub_2BD7F0.
void Cpu::sub_2BD780() {
    enter(23);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    s0 = a1;
    a0 = 1287;
    a1 = 12;
    jal(0x2BD7A0, gen::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2C);
    v1 = addiu(v1, -10512);
    sw(v1, v0, 108);
    lw(v1, v0, 120);
    sw(s1, v1, 0);
    sh(s0, v1, 4);
    sw(zero, v1, 8);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// sub_2BD850 [create 0x506]: creates packet kind 0x506 (12-byte payload: a0, a1, 0) with update sub_2BD8E0.
void Cpu::sub_2BD850() {
    enter(23);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    s0 = a1;
    a0 = 1286;
    a1 = 12;
    jal(0x2BD870, gen::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2C);
    v1 = addiu(v1, -10272);
    sw(v1, v0, 108);
    lw(v1, v0, 120);
    sw(s1, v1, 0);
    sw(s0, v1, 4);
    sw(zero, v1, 8);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// sub_2BD8B0 [pair start]: start of packet kind 0x50A: both units' busy counts (payload[0], payload[1]) += 1.
void Cpu::sub_2BD8B0() {
    enter(10);
    lw(a1, a0, 0);
    lhu(v1, a1, 160);
    v1 = addiu(v1, 1);
    sh(v1, a1, 160);
    lw(a0, a0, 4);
    lhu(v1, a0, 160);
    v1 = addiu(v1, 1);
    sh(v1, a0, 160);
}

// sub_2BDBA0 [pair end]: end of packet kind 0x50A: both busy counts -= 1.
void Cpu::sub_2BDBA0() {
    enter(10);
    lw(a1, a0, 0);
    lhu(v1, a1, 160);
    v1 = addiu(v1, -1);
    sh(v1, a1, 160);
    lw(a0, a0, 4);
    lhu(v1, a0, 160);
    v1 = addiu(v1, -1);
    sh(v1, a0, 160);
}

// sub_2BDBD0 [create 0x50A]: creates packet kind 0x50A (52-byte payload: a0, a1, the 28 bytes at $t3 copied to +8, a2
// at +36, (u16)a3 / $t0 / $t1 / $t2 at +40..+46, 1 at +48) with start / update / end sub_2BD8B0 / sub_2BD8E0 /
// sub_2BDBA0; returns the packet.
void Cpu::sub_2BDBD0() {
    enter(62);
    sp = addiu(sp, -176);
    sd(ra, sp, 144);
    sq(fp, sp, 128);
    sq(s7, sp, 112);
    sq(s6, sp, 96);
    sq(s5, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s5 = a0;
    s4 = a1;
    s3 = a2;
    s2 = a3;
    s1 = t0;
    s6 = t1;
    s7 = t2;
    fp = t3;
    a0 = 1290;
    a1 = 52;
    jal(0x2BDC24, gen::fn_sub_27EC10_0027ec10);
    sw(v0, sp, 172);
    v1 = lui(0x2C);
    v1 = addiu(v1, -10064);
    sw(v1, v0, 104);
    v1 = lui(0x2C);
    v1 = addiu(v1, -10016);
    sw(v1, v0, 108);
    v1 = lui(0x2C);
    v1 = addiu(v1, -9312);
    sw(v1, v0, 112);
    lw(s0, v0, 120);
    a0 = addiu(s0, 8);
    a1 = fp;
    a2 = 28;
    jal(0x2BDC64, gen::fn_memcpy_00521250);
    sw(s5, s0, 0);
    sw(s4, s0, 4);
    sw(s3, s0, 36);
    sh(s2, s0, 40);
    sh(s1, s0, 42);
    sh(s6, s0, 44);
    sh(s7, s0, 46);
    v0 = 1;
    sw(v0, s0, 48);
    lw(v0, sp, 172);
    ld(ra, sp, 144);
    lq(fp, sp, 128);
    lq(s7, sp, 112);
    lq(s6, sp, 96);
    lq(s5, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 176);
}

// =================================================================================================================
// the command lists (the debug lists "Attack" / "Skill" / "Item" / "Escape" / "Wait": records 0x696E10.., table
// 0x696F30) and the "battle_command_calc" / "battle_command_draw" tasks
// =================================================================================================================

// sub_2BDCD0 [0x50B update]: update (+108) of packet kind 0x50B (payload {u16 step}): step 0 waits for sub_1FEA90,
// clears battle flag +12 0x4000 after sub_2D1A70 / sub_2D1A10 / sub_1FF350, starts sub_1FEAB0 and goes to step 1; step
// 1 waits for sub_1FEB30 and sets the flag again (sub_1FF370). Returns 1 while waiting, 0 when done.
void Cpu::sub_2BDCD0() {
    enter(8);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    lhu(v1, a0, 0);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
            goto L_002bddb4;
        }
        charge(4);
        jal(0x2BDD00, gen::fn_sub_1FEA90_001fea90);
        if (v0 == 0) {
            charge(3);
            v0 = 1;
            goto L_002bddb8;
        }
        charge(5);
        jal(0x2BDD1C, gen::fn_sub_2D1A70_002d1a70);
        v1 = 1;
        if (v0 == v1) {
            charge(9);
            lw(a0, gp, -18692);
            lw(v1, a0, 12);
            v0 = si(-16385);
            v0 = v1 & v0;
            sw(v0, a0, 12);
            jal(0x2BDD44, gen::fn_sub_2D1A10_002d1a10);
            jal(0x2BDD4C, gen::fn_sub_1FF350_001ff350);
        }
        charge(6);
        jal(0x2BDD54, gen::fn_sub_1FEAB0_001feab0);
        v0 = 1;
        sh(v0, s0, 0);
    } else {
        charge(4);
        jal(0x2BDD6C, gen::fn_sub_1FEB30_001feb30);
        if (v0 != 0) goto L_002bddb4;
        charge(5);
        jal(0x2BDD7C, gen::fn_sub_2D1A70_002d1a70);
        v1 = 1;
        if (v0 == v1) {
            charge(6);
            lw(v1, gp, -18692);
            lw(v0, v1, 12);
            v0 = v0 | 0x4000;
            sw(v0, v1, 12);
            jal(0x2BDDA0, gen::fn_sub_1FF370_001ff370);
        }
        charge(3);
        v0 = 1;
        goto L_002bddb8;
    }
L_002bddb4:
    charge(1);
    v0 = 0;
L_002bddb8:
    charge(5);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// sub_2BDDD0 [create 0x50B]: creates packet kind 0x50B (2-byte payload: 0) with update sub_2BDCD0.
void Cpu::sub_2BDDD0() {
    enter(15);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    a0 = 1291;
    a1 = 2;
    jal(0x2BDDE0, gen::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2C);
    v1 = addiu(v1, -9008);
    sw(v1, v0, 108);
    lw(v1, v0, 120);
    sh(zero, v1, 0);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// sub_2BDE10 [list skills]: the unit's (a0 +48 +2604) skills (datCalcGetSkillList, 8 ids) whose SKILL.TBL row
// (gp-18680, 44 bytes, ids < 464) has 0x2 at +1, written to a1 (when not 0) sorted ascending and padded with zeros;
// returns the count.
void Cpu::sub_2BDE10() {
    enter(13);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a1;
    s0 = 0;
    lw(v0, a0, 48);
    lw(a0, v0, 2604);
    jal(0x2BDE30, gen::fn_datCalcGetSkillList_00308bb0);
    v1 = 0;
    for (;;) {  // L_002bdebc
        charge(4);
        a0 = v1 & 0xFFFF;
        a0 = slti(a0, 8);
        if (a0 == 0) break;
        backedge();
        charge(6);
        a0 = v1 & 0xFFFF;
        a0 = sll(a0, 1);
        a0 = addu(v0, a0);
        lhu(a2, a0, 0);
        if (a2 != 0) {
            charge(3);
            at = slti(a2, 464);
            if (at == 0) goto L_002bdeb4;
            charge(11);
            a0 = sll(a2, 2);
            a0 = addu(a0, a2);
            a0 = sll(a0, 1);
            a0 = addu(a0, a2);
            a1 = sll(a0, 2);
            lw(a0, gp, -18680);
            a0 = addu(a0, a1);
            lbu(a0, a0, 1);
            a0 = a0 & 0x2;
            if (a0 == 0) goto L_002bdeb4;
            charge(2);
            if (s1 != 0) {
                charge(4);
                a0 = s0 & 0xFFFF;
                a0 = sll(a0, 1);
                a0 = addu(s1, a0);
                sh(a2, a0, 0);
            }
            charge(2);
            a0 = addiu(s0, 1);
            s0 = a0 & 0xFFFF;
        }
L_002bdeb4:
        charge(2);
        v1 = addiu(v1, 1);
        v1 = v1 & 0xFFFF;
    }
    charge(2);
    if (s1 != 0) {
        charge(3);
        v1 = s0 & 0xFFFF;
        for (;;) {  // L_002bdef8
            charge(4);
            v0 = v1 & 0xFFFF;
            v0 = slti(v0, 8);
            if (v0 == 0) break;
            backedge();
            charge(6);
            v0 = v1 & 0xFFFF;
            v0 = sll(v0, 1);
            v0 = addu(s1, v0);
            sh(zero, v0, 0);
            v0 = addiu(v1, 1);
            v1 = v0 & 0xFFFF;
        }
        charge(4);
        v0 = s0 & 0xFFFF;
        at = slti(v0, 2);
        if (at != 0) goto L_002bdf88;
        charge(2);
        t0 = addiu(v0, -1);
        a0 = 1;
        for (;;) {  // L_002bdf20
            charge(4);
            t1 = 0;
            a3 = 0;
            for (;;) {  // L_002bdf70
                charge(4);
                v1 = a3 & 0xFFFF;
                v0 = slt(v1, t0);
                if (v0 == 0) break;
                backedge();
                charge(11);
                v0 = a3 & 0xFFFF;
                v0 = sll(v0, 1);
                a2 = addu(s1, v0);
                lhu(a1, a2, 0);
                v0 = sll(v1, 1);
                v0 = addu(s1, v0);
                v1 = addiu(v0, 2);
                lhu(v0, v0, 2);
                at = slt(v0, a1);
                if (at != 0) {
                    charge(3);
                    sh(v0, a2, 0);
                    sh(a1, v1, 0);
                    t1 = a0;
                }
                charge(2);
                v0 = addiu(a3, 1);
                a3 = v0 & 0xFFFF;
            }
            charge(2);
            if (t1 == 0) break;
            backedge();
        }
    }
L_002bdf88:
    charge(7);
    v0 = s0;
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// sub_2BDFB0 [list input]: moves a list window (s16 x +0, y +2, first +4, cursor +6, width +8, rows +10, count +12) by
// the pad words 0x7E094E / 0x7E0958 / 0x7E0952 / 0x7E095A: returns 2 decide (0x40), 1 cancel (0x20), 3 up / page up
// (0x1000 / 0x8000), 4 down / page down (0x4000 / 0x2000), 0 nothing; a cursor past the count is pulled back first.
void Cpu::sub_2BDFB0() {
    enter(5);
    lh(v1, a0, 12);
    lh(v0, a0, 6);
    v0 = slt(v0, v1);
    if (v0 == 0) {
        charge(10);
        v0 = addiu(v1, -1);
        sh(v0, a0, 6);
        lh(v1, a0, 12);
        lh(v0, a0, 10);
        v0 = subu(v1, v0);
        sh(v0, a0, 4);
        v0 = dsll32(v0, 16);
        v0 = dsra32(v0, 16);
        if (gez(v0)) goto L_002bdff0;
        charge(1);
        sh(zero, a0, 4);
    }
L_002bdff0:
    charge(5);
    v0 = lui(0x7E);
    lhu(a1, v0, 2382);
    v0 = a1 & 0x40;
    if (v0 == 0) {
        charge(5);
        v0 = lui(0x7E);
        lhu(v1, v0, 2392);
        v0 = v1 & 0x40;
        if (v0 == 0) goto L_002be024;
    }
    charge(3);
    v0 = 2;
    goto L_002be2d4;
L_002be024:
    charge(3);
    v0 = a1 & 0x20;
    if (v0 == 0) {
        charge(3);
        v0 = v1 & 0x20;
        if (v0 == 0) goto L_002be048;
    }
    charge(3);
    v0 = 1;
    goto L_002be2d4;
L_002be048:
    charge(5);
    v0 = lui(0x7E);
    lhu(a2, v0, 2386);
    v1 = a2 & 0x1000;
    if (v1 == 0) {
        charge(5);
        v0 = lui(0x7E);
        lhu(a1, v0, 2394);
        v0 = a1 & 0x1000;
        if (v0 != 0) goto L_002be088;
        charge(3);
        v0 = a2 & 0x8000;
        if (v0 != 0) goto L_002be088;
        charge(3);
        v0 = a1 & 0x8000;
        if (v0 == 0) goto L_002be190;
    }
L_002be088:
    charge(2);
    if (v1 == 0) {
        charge(5);
        v0 = lui(0x7E);
        lhu(v0, v0, 2394);
        v0 = v0 & 0x1000;
        if (v0 != 0) goto L_002be0ac;
        charge(2);
        goto L_002be0b8;
    }
L_002be0ac:
    charge(3);
    v0 = 1;
    goto L_002be0bc;
L_002be0b8:
    charge(1);
    lh(v0, a0, 10);
L_002be0bc:
    charge(6);
    a3 = dsll32(v0, 16);
    a3 = dsra32(a3, 16);
    t0 = 0;
    a1 = 1;
    for (;;) {  // L_002be170
        charge(5);
        v0 = dsll32(t0, 16);
        v0 = dsra32(v0, 16);
        v0 = slt(v0, a3);
        if (v0 == 0) break;
        backedge();
        charge(6);
        lh(a2, a0, 4);
        lh(v1, a0, 6);
        v0 = addiu(a2, 1);
        at = slt(v0, v1);
        if (at == 0) {
            charge(2);
            if (gtz(a2)) {
                charge(7);
                v0 = addiu(a2, -1);
                sh(v0, a0, 4);
                lh(v0, a0, 6);
                v0 = addiu(v0, -1);
                sh(v0, a0, 6);
                goto L_002be164;
            }
            charge(2);
            if (v1 == a1) {
                charge(3);
                sh(zero, a0, 6);
                goto L_002be164;
            }
            charge(8);
            lh(v1, a0, 12);
            lh(v0, a0, 10);
            v0 = subu(v1, v0);
            sh(v0, a0, 4);
            v0 = dsll32(v0, 16);
            v0 = dsra32(v0, 16);
            if (ltz(v0)) {
                charge(1);
                sh(zero, a0, 4);
            }
            charge(5);
            lh(v0, a0, 12);
            v0 = addiu(v0, -1);
            sh(v0, a0, 6);
        } else {
            charge(2);
            v0 = addiu(v1, -1);
            sh(v0, a0, 6);
        }
L_002be164:
        charge(3);
        v0 = addiu(t0, 1);
        t0 = dsll32(v0, 16);
        t0 = dsra32(t0, 16);
    }
    charge(3);
    v0 = 3;
    goto L_002be2d4;
L_002be190:
    charge(3);
    v1 = a2 & 0x4000;
    if (v1 == 0) {
        charge(3);
        v0 = a1 & 0x4000;
        if (v0 != 0) goto L_002be1c0;
        charge(3);
        v0 = a2 & 0x2000;
        if (v0 != 0) goto L_002be1c0;
        charge(3);
        v0 = a1 & 0x2000;
        if (v0 == 0) goto L_002be2d0;
    }
L_002be1c0:
    charge(2);
    if (v1 == 0) {
        charge(3);
        v0 = a1 & 0x4000;
        if (v0 != 0) goto L_002be1dc;
        charge(2);
        goto L_002be1e8;
    }
L_002be1dc:
    charge(3);
    v0 = 1;
    goto L_002be1ec;
L_002be1e8:
    charge(1);
    lh(v0, a0, 10);
L_002be1ec:
    charge(5);
    t0 = dsll32(v0, 16);
    t0 = dsra32(t0, 16);
    t1 = 0;
    for (;;) {  // L_002be2b0
        charge(5);
        v0 = dsll32(t1, 16);
        v0 = dsra32(v0, 16);
        v0 = slt(v0, t0);
        if (v0 == 0) break;
        backedge();
        charge(8);
        lh(a3, a0, 10);
        lh(a2, a0, 4);
        lh(a1, a0, 6);
        v0 = addu(a2, a3);
        v0 = addiu(v0, -2);
        at = slt(a1, v0);
        if (at != 0) {
            charge(5);
            lh(v0, a0, 12);
            v0 = addiu(v0, -2);
            v0 = slt(a1, v0);
            if (v0 != 0) goto L_002be29c;
        }
        charge(5);
        lh(v1, a0, 12);
        v0 = subu(v1, a3);
        at = slt(a2, v0);
        if (at != 0) {
            charge(8);
            lh(v0, a0, 4);
            v0 = addiu(v0, 1);
            sh(v0, a0, 4);
            lh(v0, a0, 6);
            v0 = addiu(v0, 1);
            sh(v0, a0, 6);
            goto L_002be2a4;
        }
        charge(4);
        v0 = addiu(v1, -1);
        at = slt(a1, v0);
        if (at != 0) {
            charge(5);
            lh(v0, a0, 6);
            v0 = addiu(v0, 1);
            sh(v0, a0, 6);
            goto L_002be2a4;
        }
        charge(4);
        sh(zero, a0, 4);
        sh(zero, a0, 6);
        goto L_002be2a4;
L_002be29c:
        charge(2);
        v0 = addiu(a1, 1);
        sh(v0, a0, 6);
L_002be2a4:
        charge(3);
        v0 = addiu(t1, 1);
        t1 = dsll32(v0, 16);
        t1 = dsra32(t1, 16);
    }
    charge(3);
    v0 = 4;
    goto L_002be2d4;
L_002be2d0:
    charge(1);
    v0 = 0;
L_002be2d4:
    charge(2);
}

// nullsub_100: nullsub_100: the root list's init.
void Cpu::nullsub_100() {
    enter(2);
}

// sub_2BE2F0 [root list input]: input of the root list (record 0x696E10): on decide opens the chosen command's list
// (table 0x696F30 by the cursor; links parent +32 / child +36, runs its init +16) and returns 2; cancel rewinds the
// cursor (returns 0).
void Cpu::sub_2BE2F0() {
    enter(8);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    jal(0x2BE2F8, gen::fn_sub_2BDFB0_002bdfb0);
    v1 = v0 & 0xFFFF;
    v0 = 2;
    if (v1 != v0) {
        charge(3);
        v0 = 1;
        if (v1 != v0) {
            charge(2);
            goto L_002be378;
        }
        charge(4);
        sh(zero, a0, 4);
        sh(zero, a0, 6);
    } else {
        charge(11);
        lh(v0, a0, 6);
        v1 = sll(v0, 2);
        v0 = lui(0x69);
        v0 = addiu(v0, 28464);
        v0 = addu(v0, v1);
        lw(v1, v0, 0);
        sw(v1, a0, 36);
        sw(a0, v1, 32);
        lw(v0, v1, 16);
        if (v0 != 0) {
            charge(3);
            a0 = v1;
            jalr(0x2BE364, v0.u());
        }
        charge(3);
        v0 = 2;
        goto L_002be37c;
    }
L_002be378:
    charge(1);
    v0 = 0;
L_002be37c:
    charge(4);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// sub_2BE390 [root list draw]: draws the root list: the frame quad (0xC0C0C0C0, btlDrawTexturedQuad) and the rows
// (table 0x696D90 "Attack" .. "Wait") through sub_3B2CB0, the cursor row highlighted.
void Cpu::sub_2BE390() {
    enter(67);
    sp = addiu(sp, -112);
    sd(ra, sp, 96);
    sq(s5, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    lh(v1, a0, 8);
    v0 = sll(v1, 3);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    v0 = addiu(v0, 4);
    mtc1(v0, F0);
    cvt_s_w(F14, F0);
    lh(v1, a0, 10);
    v0 = sll(v1, 3);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addiu(v0, 4);
    mtc1(v0, F0);
    cvt_s_w(F15, F0);
    s2 = dsll32(a2, 16);
    s2 = dsra32(s2, 16);
    s1 = dsll32(a1, 16);
    s1 = dsra32(s1, 16);
    lh(v0, a0, 0);
    v0 = addu(s1, v0);
    v0 = addiu(v0, -2);
    mtc1(v0, F0);
    cvt_s_w(F12, F0);
    lh(v0, a0, 2);
    v0 = addu(s2, v0);
    v0 = addiu(v0, -2);
    mtc1(v0, F0);
    cvt_s_w(F13, F0);
    mtc1(zero, F16);
    mov_s(F17, F16);
    v0 = lui(0xC0C0);
    a0 = v0 | 0xC0C0;
    a1 = 0;
    jal(0x2BE450, gen::fn_btlDrawTexturedQuad_002bc9c0);
    lh(v1, s0, 0);
    v1 = addu(v1, s1);
    s3 = dsll32(v1, 16);
    s3 = dsra32(s3, 16);
    lh(v1, s0, 2);
    v1 = addu(v1, s2);
    v1 = addiu(v1, -8);
    s4 = dsll32(v1, 16);
    s4 = dsra32(s4, 16);
    lh(s2, s0, 4);
    s5 = 0;
    a0 = sll(s2, 2);
    v1 = lui(0x69);
    v1 = addiu(v1, 28048);
    s1 = addu(v1, a0);
    for (;;) {  // L_002be53c
        charge(6);
        a0 = dsll32(s5, 16);
        a0 = dsra32(a0, 16);
        lh(v1, s0, 10);
        v1 = slt(a0, v1);
        if (v1 == 0) break;
        backedge();
        charge(4);
        lh(v1, s0, 6);
        v0 = addu(s2, a0);
        if (v1 == v0) {
            charge(16);
            a1 = dsll32(s4, 16);
            a1 = dsra32(a1, 16);
            mtc1(zero, F12);
            v0 = sll(a0, 2);
            v0 = addu(s1, v0);
            a0 = s3;
            a2 = si(-1);
            a3 = 1;
            t0 = 2;
            lw(t1, v0, 0);
            t2 = 0;
            t3 = 0;
            jal(0x2BE4DC, gen::fn_sub_3B2CB0_003b2cb0);
        } else {
            charge(14);
            a1 = dsll32(s4, 16);
            a1 = dsra32(a1, 16);
            mtc1(zero, F12);
            v0 = sll(a0, 2);
            v0 = addu(s1, v0);
            a0 = s3;
            a2 = si(-1);
            a3 = 0;
            t0 = 2;
            lw(t1, v0, 0);
            t2 = 0;
            t3 = 0;
            jal(0x2BE51C, gen::fn_sub_3B2CB0_003b2cb0);
        }
        charge(6);
        v1 = addiu(s4, 18);
        s4 = dsll32(v1, 16);
        s4 = dsra32(s4, 16);
        v1 = addiu(s5, 1);
        s5 = dsll32(v1, 16);
        s5 = dsra32(s5, 16);
    }
    charge(10);
    ld(ra, sp, 96);
    lq(s5, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 112);
}

// sub_2BE580 [Attack]: the Attack list's input: the unit's (a1) command +108 = 1, +110 = its attack skill (sub_308930).
// Returns 4.
void Cpu::sub_2BE580() {
    enter(17);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a1;
    v0 = 1;
    sh(v0, a1, 108);
    lw(v0, a1, 48);
    lw(a0, v0, 2604);
    jal(0x2BE5A0, gen::fn_sub_308930_00308930);
    sh(v0, s0, 110);
    v0 = 4;
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// sub_2BE5D0 [Escape]: the Escape list's input: command +108 = 6, +110 = 0.
void Cpu::sub_2BE5D0() {
    enter(5);
    v0 = 6;
    sh(v0, a1, 108);
    sh(zero, a1, 110);
}

// sub_2BE5F0 [Wait]: the Wait list's input: command +108 = 7, +110 = 0. Returns 6.
void Cpu::sub_2BE5F0() {
    enter(6);
    v0 = 7;
    sh(v0, a1, 108);
    sh(zero, a1, 110);
    v0 = 6;
}

// sub_2BE610 [skill list init]: the skill list's init: count +12 = 623 (every skill).
void Cpu::sub_2BE610() {
    enter(4);
    v1 = 623;
    sh(v1, a0, 12);
}

// sub_2BE620 [skill list input]: input of the skill list: count = 623 in the all-skills mode (gBtl +20 bit 0x2000000),
// else the unit's skills (sub_2BDE10); on decide command +108 = 2 and +110 = the chosen skill (returns 3), cancel
// returns 1.
void Cpu::sub_2BE620() {
    enter(12);
    sp = addiu(sp, -80);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    s0 = a1;
    lw(v0, gp, -18692);
    lw(v1, v0, 20);
    v0 = lui(0x200);
    v0 = v1 & v0;
    if (v0 != 0) {
        charge(4);
        v0 = 623;
        sh(v0, s1, 12);
    } else {
        charge(5);
        a0 = s0;
        a1 = addiu(sp, 48);
        jal(0x2BE668, gen::fn_sub_2BDE10_002bde10);
        sh(v0, s1, 12);
    }
    charge(7);
    a0 = s1;
    jal(0x2BE678, gen::fn_sub_2BDFB0_002bdfb0);
    v1 = v0 & 0xFFFF;
    v0 = 2;
    if (v1 != v0) {
        charge(3);
        v0 = 1;
        if (v1 != v0) {
            charge(2);
            goto L_002be6fc;
        }
        charge(2);
        goto L_002be700;
    }
    charge(7);
    sh(v0, s0, 108);
    lw(v0, gp, -18692);
    lw(v1, v0, 20);
    v0 = lui(0x200);
    v0 = v1 & v0;
    if (v0 != 0) {
        charge(5);
        lh(v0, s1, 6);
        v0 = addiu(v0, 1);
        sh(v0, s0, 110);
    } else {
        charge(5);
        lh(v0, s1, 6);
        v0 = sll(v0, 1);
        v0 = addu(v0, sp);
        lhu(v0, v0, 48);
        sh(v0, s0, 110);
    }
    charge(3);
    v0 = 3;
    goto L_002be700;
L_002be6fc:
    charge(1);
    v0 = 0;
L_002be700:
    charge(6);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 80);
}

// sub_2BE720 [skill list draw]: draws the skill list: the frame quad and the visible rows' names (gp-18436, 19-byte
// rows) through sub_3B2CB0.
void Cpu::sub_2BE720() {
    enter(58);
    sp = addiu(sp, -160);
    sd(ra, sp, 112);
    sq(s6, sp, 96);
    sq(s5, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s4 = a0;
    s1 = a3;
    lh(v1, a0, 8);
    v0 = sll(v1, 3);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    v0 = addiu(v0, 4);
    mtc1(v0, F0);
    cvt_s_w(F14, F0);
    lh(v1, a0, 10);
    v0 = sll(v1, 3);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addiu(v0, 4);
    mtc1(v0, F0);
    cvt_s_w(F15, F0);
    s2 = dsll32(a2, 16);
    s2 = dsra32(s2, 16);
    s0 = dsll32(a1, 16);
    s0 = dsra32(s0, 16);
    lh(v0, a0, 0);
    v0 = addu(s0, v0);
    v0 = addiu(v0, -2);
    mtc1(v0, F0);
    cvt_s_w(F12, F0);
    lh(v0, a0, 2);
    v0 = addu(s2, v0);
    v0 = addiu(v0, -2);
    mtc1(v0, F0);
    cvt_s_w(F13, F0);
    mtc1(zero, F16);
    mov_s(F17, F16);
    v0 = lui(0xC0C0);
    a0 = v0 | 0xC0C0;
    a1 = 0;
    jal(0x2BE7E8, gen::fn_btlDrawTexturedQuad_002bc9c0);
    lw(v1, gp, -18692);
    lw(a0, v1, 20);
    v1 = lui(0x200);
    v1 = a0 & v1;
    if (v1 != 0) {
        charge(4);
        v1 = 623;
        sh(v1, s4, 12);
    } else {
        charge(5);
        a0 = s1;
        a1 = addiu(sp, 128);
        jal(0x2BE820, gen::fn_sub_2BDE10_002bde10);
        sh(v0, s4, 12);
    }
    charge(5);
    lh(a0, s4, 12);
    lh(v1, s4, 10);
    at = slt(a0, v1);
    if (at == 0) {
        charge(2);
    } else {
        charge(1);
        v1 = a0;
    }
    charge(17);
    s5 = v1 & 0xFFFF;
    lh(v1, s4, 0);
    v1 = addu(v1, s0);
    s1 = dsll32(v1, 16);
    s1 = dsra32(s1, 16);
    lh(v1, s4, 2);
    v1 = addu(v1, s2);
    v1 = addiu(v1, -8);
    s2 = dsll32(v1, 16);
    s2 = dsra32(s2, 16);
    lh(s0, s4, 4);
    s3 = 0;
    v1 = sll(s0, 1);
    v1 = addu(v1, sp);
    s6 = addiu(v1, 128);
    for (;;) {  // L_002be98c
        charge(5);
        a0 = dsll32(s3, 16);
        a0 = dsra32(a0, 16);
        v1 = slt(a0, s5);
        if (v1 == 0) break;
        backedge();
        charge(6);
        lw(v0, gp, -18692);
        lw(v1, v0, 20);
        v0 = lui(0x200);
        v0 = v1 & v0;
        if (v0 != 0) {
            charge(5);
            v0 = addu(s0, a0);
            v0 = addiu(v0, 1);
            v0 = v0 & 0xFFFF;
        } else {
            charge(3);
            v0 = sll(a0, 1);
            v0 = addu(s6, v0);
            lhu(v0, v0, 0);
        }
        charge(5);
        a2 = v0 & 0xFFFF;
        lh(v1, s4, 6);
        v0 = addu(s0, a0);
        if (v1 == v0) {
            charge(20);
            a1 = dsll32(s2, 16);
            a1 = dsra32(a1, 16);
            mtc1(zero, F12);
            v1 = a2 & 0xFFFF;
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v1 = addu(v0, v1);
            lw(v0, gp, -18436);
            t1 = addu(v0, v1);
            a0 = s1;
            a2 = si(-1);
            a3 = 1;
            t0 = 2;
            t2 = 0;
            t3 = 0;
            jal(0x2BE91C, gen::fn_sub_3B2CB0_003b2cb0);
        } else {
            charge(18);
            a1 = dsll32(s2, 16);
            a1 = dsra32(a1, 16);
            mtc1(zero, F12);
            v1 = a2 & 0xFFFF;
            v0 = sll(v1, 3);
            v0 = addu(v0, v1);
            v0 = sll(v0, 1);
            v1 = addu(v0, v1);
            lw(v0, gp, -18436);
            t1 = addu(v0, v1);
            a0 = s1;
            a2 = si(-1);
            a3 = 0;
            t0 = 2;
            t2 = 0;
            t3 = 0;
            jal(0x2BE96C, gen::fn_sub_3B2CB0_003b2cb0);
        }
        charge(6);
        v1 = addiu(s2, 18);
        s2 = dsll32(v1, 16);
        s2 = dsra32(s2, 16);
        v1 = addiu(s3, 1);
        s3 = dsll32(v1, 16);
        s3 = dsra32(s3, 16);
    }
    charge(11);
    ld(ra, sp, 112);
    lq(s6, sp, 96);
    lq(s5, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 160);
}

// nullsub_101: nullsub_101: the item list's init.
void Cpu::nullsub_101() {
    enter(2);
}

// sub_2BE9E0 [item list input]: input of the item list (223 items, ids 4001 + n): on decide command +108 = 3, +112 =
// the item id, +110 = its skill (sub_30BC20); returns 3, cancel 1.
void Cpu::sub_2BE9E0() {
    enter(12);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a1;
    v0 = 223;
    sh(v0, a0, 12);
    jal(0x2BE9F8, gen::fn_sub_2BDFB0_002bdfb0);
    v1 = v0 & 0xFFFF;
    v0 = 2;
    if (v1 != v0) {
        charge(3);
        v0 = 1;
        if (v1 != v0) {
            charge(2);
            goto L_002bea5c;
        }
        charge(2);
        goto L_002bea60;
    }
    charge(12);
    v0 = 3;
    sh(v0, s0, 108);
    lh(v0, a0, 6);
    v0 = addiu(v0, 4001);
    sh(v0, s0, 112);
    lhu(a0, s0, 112);
    jal(0x2BEA44, gen::fn_sub_30BC20_0030bc20);
    sh(v0, s0, 110);
    v0 = 3;
    goto L_002bea60;
L_002bea5c:
    charge(1);
    v0 = 0;
L_002bea60:
    charge(5);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// sub_2BEA80 [item list draw]: draws the item list: the frame quad and the visible rows' item names (sub_171110)
// through sub_3B2CB0.
void Cpu::sub_2BEA80() {
    enter(57);
    sp = addiu(sp, -128);
    sd(ra, sp, 112);
    sq(s6, sp, 96);
    sq(s5, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s5 = a0;
    lh(v1, a0, 8);
    v0 = sll(v1, 3);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    v0 = addiu(v0, 4);
    mtc1(v0, F0);
    cvt_s_w(F14, F0);
    lh(v1, a0, 10);
    v0 = sll(v1, 3);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addiu(v0, 4);
    mtc1(v0, F0);
    cvt_s_w(F15, F0);
    s3 = dsll32(a2, 16);
    s3 = dsra32(s3, 16);
    s0 = dsll32(a1, 16);
    s0 = dsra32(s0, 16);
    lh(v0, a0, 0);
    v0 = addu(s0, v0);
    v0 = addiu(v0, -2);
    mtc1(v0, F0);
    cvt_s_w(F12, F0);
    lh(v0, a0, 2);
    v0 = addu(s3, v0);
    v0 = addiu(v0, -2);
    mtc1(v0, F0);
    cvt_s_w(F13, F0);
    mtc1(zero, F16);
    mov_s(F17, F16);
    v0 = lui(0xC0C0);
    a0 = v0 | 0xC0C0;
    a1 = 0;
    jal(0x2BEB44, gen::fn_btlDrawTexturedQuad_002bc9c0);
    a0 = 223;
    sh(a0, s5, 12);
    lh(v1, s5, 10);
    at = slt(a0, v1);
    if (at == 0) {
        charge(2);
    } else {
        charge(1);
        v1 = a0;
    }
    charge(15);
    s1 = v1 & 0xFFFF;
    lh(v1, s5, 0);
    v1 = addu(v1, s0);
    s2 = dsll32(v1, 16);
    s2 = dsra32(s2, 16);
    lh(v1, s5, 2);
    v1 = addu(v1, s3);
    v1 = addiu(v1, -8);
    s3 = dsll32(v1, 16);
    s3 = dsra32(s3, 16);
    lh(s0, s5, 4);
    s4 = 0;
    s6 = addiu(s0, 4001);
    for (;;) {  // L_002bec74
        charge(5);
        v1 = dsll32(s4, 16);
        v1 = dsra32(v1, 16);
        v1 = slt(v1, s1);
        if (v1 == 0) break;
        backedge();
        charge(8);
        a1 = dsll32(s4, 16);
        a1 = dsra32(a1, 16);
        v0 = addu(s6, a1);
        a0 = v0 & 0xFFFF;
        lh(v1, s5, 6);
        v0 = addu(s0, a1);
        if (v1 == v0) {
            charge(19);
            a0 = dsll32(a0, 16);
            a0 = dsra32(a0, 16);
            a1 = 0;
            jal(0x2BEBD8, gen::fn_sub_171110_00171110);
            a1 = dsll32(s3, 16);
            a1 = dsra32(a1, 16);
            mtc1(zero, F12);
            a0 = s2;
            a2 = si(-1);
            a3 = 1;
            t0 = 2;
            t1 = v0;
            t2 = 0;
            t3 = 0;
            jal(0x2BEC08, gen::fn_sub_3B2CB0_003b2cb0);
        } else {
            charge(17);
            a0 = dsll32(a0, 16);
            a0 = dsra32(a0, 16);
            a1 = 0;
            jal(0x2BEC24, gen::fn_sub_171110_00171110);
            a1 = dsll32(s3, 16);
            a1 = dsra32(a1, 16);
            mtc1(zero, F12);
            a0 = s2;
            a2 = si(-1);
            a3 = 0;
            t0 = 2;
            t1 = v0;
            t2 = 0;
            t3 = 0;
            jal(0x2BEC54, gen::fn_sub_3B2CB0_003b2cb0);
        }
        charge(6);
        v1 = addiu(s3, 18);
        s3 = dsll32(v1, 16);
        s3 = dsra32(s3, 16);
        v1 = addiu(s4, 1);
        s4 = dsll32(v1, 16);
        s4 = dsra32(s4, 16);
    }
    charge(11);
    ld(ra, sp, 112);
    lq(s6, sp, 96);
    lq(s5, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 128);
}

// sub_2BECC0 [command state]: the "battle_command_calc" task's work +0 (its state), or 5 when the task is gone.
void Cpu::sub_2BECC0() {
    enter(8);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    a0 = lui(0x69);
    a0 = addiu(a0, 28496);
    jal(0x2BECD0, gen::fn_kwlnTaskGetTaskByName_00195340);
    if (v0 == 0) {
        charge(3);
        v0 = 5;
    } else {
        charge(4);
        a0 = v0;
        jal(0x2BECF0, gen::fn_kwlnTaskGetWorkData_00195540);
        lhu(v0, v0, 0);
    }
    charge(4);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// btlCommand_UpdateBattleCommandCalcTask [battle_command_calc]: update of the task "battle_command_calc" (symbols/deltas/bands.sym; created at
// 0x2BF4B0): idle while sub_2FF330 or battle flag +20 0x4; states 3 / 5 / 7 / 8 wait. In the debug mode (+20 0x2000000;
// flags 5132 / 5129 raised) state 6 -> 2, else the current list's input (`jalr` +20) and the jump table 0x7B7D40 (1 the
// child, 2 the parent, 3 / 4 back to the parent and state 3, 6 state 5); otherwise (flags cleared) the real command
// menu (sub_1FDDF0 / sub_1FDF10, battle_cmd_menu): the chosen command into the unit's +108 / +110 / +112 / +116 and the
// state (3, 5, 7 with sub_2DB650, 8). Returns 0.
void Cpu::btlCommand_UpdateBattleCommandCalcTask() {
    enter(9);
    sp = addiu(sp, -80);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    jal(0x2BEF34, gen::fn_sub_2FF330_002ff330);
    if (v0 != 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(5);
        lw(v0, gp, -18692);
        lw(v0, v0, 20);
        v0 = v0 & 0x4;
        if (v0 != 0) {
            charge(3);
            v0 = 0;
            goto L_002bf28c;
        }
        charge(8);
        a0 = s0;
        jal(0x2BEF74, gen::fn_kwlnTaskGetWorkData_00195540);
        s1 = v0;
        lhu(v1, v0, 0);
        v0 = 8;
        if (v1 != v0) {
            charge(3);
            v0 = 7;
            if (v1 == v0) goto L_002befbc;
            charge(3);
            v0 = 5;
            if (v1 == v0) goto L_002befbc;
            charge(3);
            v0 = 3;
            if (v1 == v0) goto L_002befbc;
            charge(2);
            goto L_002befc8;
        }
L_002befbc:
        charge(3);
        v0 = 0;
        goto L_002bf28c;
L_002befc8:
        charge(6);
        lw(v0, gp, -18692);
        lw(v1, v0, 20);
        v0 = lui(0x200);
        v0 = v1 & v0;
        if (v0 != 0) {
            charge(12);
            a0 = 5132;
            a1 = 1;
            jal(0x2BEFE8, gen::fn_datSetFlag_0016f1f0);
            a0 = 5129;
            a1 = 1;
            jal(0x2BEFF8, gen::fn_datSetFlag_0016f1f0);
            lhu(v1, s1, 0);
            v0 = 6;
            if (v1 == v0) {
                charge(5);
                v0 = 2;
                sh(v0, s1, 0);
                v0 = 0;
                goto L_002bf28c;
            }
            charge(3);
            lw(s0, s1, 12);
            if (s0 == 0) goto L_002bf288;
            charge(3);
            lw(v0, s0, 20);
            if (v0 == 0) goto L_002bf288;
            charge(8);
            a0 = s0;
            lw(a1, s1, 4);
            jalr(0x2BF044, v0.u());
            v0 = v0 & 0xFFFF;
            at = sltiu(v0, 7);
            if (at == 0) goto L_002bf288;
            charge(7);
            v1 = lui(0x7B);
            v1 = addiu(v1, 32064);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (const u32 t = v0.u()) {  // jump table
            case 0x2BF078: goto L_002bf078;
            case 0x2BF094: goto L_002bf094;
            case 0x2BF0AC: goto L_002bf0ac;
            case 0x2BF0C0: goto L_002bf0c0;
            case 0x2BF0D0: goto L_002bf0d0;
            case 0x2BF288: goto L_002bf288;
            default: tail(t); return;
            }
L_002bf078:
            charge(3);
            lw(v0, s0, 32);
            if (v0 == 0) goto L_002bf288;
            charge(4);
            sw(v0, s1, 12);
            sw(zero, v0, 36);
            goto L_002bf288;
L_002bf094:
            charge(3);
            lw(v0, s0, 36);
            if (v0 == 0) goto L_002bf288;
            charge(3);
            sw(v0, s1, 12);
            goto L_002bf288;
L_002bf0ac:
            charge(3);
            lw(v0, s0, 32);
            if (v0 != 0) {
                charge(2);
                sw(v0, s1, 12);
                sw(zero, v0, 36);
            }
L_002bf0c0:
            charge(4);
            v0 = 3;
            sh(v0, s1, 0);
            goto L_002bf288;
L_002bf0d0:
            charge(4);
            v0 = 5;
            sh(v0, s1, 0);
        } else {
            charge(13);
            a0 = 5132;
            a1 = 0;
            jal(0x2BF0E8, gen::fn_datSetFlag_0016f1f0);
            a0 = 5129;
            a1 = 0;
            jal(0x2BF0F8, gen::fn_datSetFlag_0016f1f0);
            lw(s0, s1, 4);
            jal(0x2BF104, gen::fn_sub_1FDDF0_001fddf0);
            if (v0 == 0) goto L_002bf288;
            charge(9);
            a0 = addiu(sp, 48);
            jal(0x2BF118, gen::fn_sub_1FDF10_001fdf10);
            lw(v0, sp, 52);
            sh(v0, s0, 108);
            lw(a1, sp, 52);
            v0 = 13;
            if (a1 != v0) {
                charge(3);
                v0 = 7;
                if (a1 != v0) {
                    charge(3);
                    v0 = 6;
                    if (a1 == v0) goto L_002bf270;
                    charge(3);
                    v0 = 10;
                    if (a1 != v0) {
                        charge(3);
                        a0 = 5;
                        if (a1 != a0) {
                            charge(3);
                            v0 = 4;
                            if (a1 != v0) {
                                charge(3);
                                v1 = 3;
                                if (a1 != v1) {
                                    charge(3);
                                    v0 = 2;
                                    if (a1 != v0) {
                                        charge(3);
                                        v0 = 1;
                                        if (a1 != v0) {
                                            charge(2);
                                            goto L_002bf288;
                                        }
                                        charge(9);
                                        lw(v0, s0, 48);
                                        lw(a0, v0, 2604);
                                        jal(0x2BF1A8, gen::fn_sub_308930_00308930);
                                        sh(v0, s0, 110);
                                        v0 = 3;
                                        sh(v0, s1, 0);
                                        goto L_002bf288;
                                    }
                                    charge(5);
                                    lhu(v0, sp, 58);
                                    sh(v0, s0, 110);
                                    sh(v1, s1, 0);
                                    goto L_002bf288;
                                }
                                charge(10);
                                lhu(v0, sp, 56);
                                sh(v0, s0, 112);
                                lhu(a0, sp, 56);
                                jal(0x2BF1E4, gen::fn_sub_30BC20_0030bc20);
                                sh(v0, s0, 110);
                                v0 = 3;
                                sh(v0, s1, 0);
                                goto L_002bf288;
                            }
                            charge(4);
                            lw(v1, sp, 48);
                            v0 = v1 & 0x1;
                            if (v0 == 0) {
                                charge(3);
                                v0 = v1 & 0x2;
                                if (v0 == 0) goto L_002bf234;
                            }
                            charge(6);
                            lhu(v0, sp, 58);
                            sh(v0, s0, 110);
                            v0 = 3;
                            sh(v0, s1, 0);
                            goto L_002bf288;
L_002bf234:
                            charge(3);
                            sh(a0, s1, 0);
                            goto L_002bf288;
                        }
                        charge(5);
                        lhu(v0, sp, 60);
                        sh(v0, s0, 116);
                        sh(a0, s1, 0);
                        goto L_002bf288;
                    }
                    charge(7);
                    lw(a0, sp, 64);
                    jal(0x2BF258, gen::fn_sub_2DB650_002db650);
                    v0 = 7;
                    sh(v0, s1, 0);
                    goto L_002bf288;
                }
L_002bf270:
                charge(4);
                v0 = 5;
                sh(v0, s1, 0);
                goto L_002bf288;
            }
            charge(2);
            v0 = 8;
            sh(v0, s1, 0);
        }
L_002bf288:
        charge(1);
        v0 = 0;
    }
L_002bf28c:
    charge(6);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 80);
}

// btlCommand_UpdateBattleCommandDrawTask [battle_command_draw]: update of the task "battle_command_draw" (created at 0x2BF4DC): in the debug mode
// draws the list chain from the work's +8 (each list's draw +24 through `jalr`, at (16, 300), linked by +36). Returns
// 0.
void Cpu::btlCommand_UpdateBattleCommandDrawTask() {
    enter(9);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    jal(0x2BF2C4, gen::fn_sub_2FF330_002ff330);
    if (v0 != 0) {
        charge(3);
        v0 = 0;
    } else {
        charge(5);
        lw(v0, gp, -18692);
        lw(v1, v0, 20);
        v0 = v1 & 0x4;
        if (v0 != 0) {
            charge(3);
            v0 = 0;
            goto L_002bf358;
        }
        charge(4);
        v0 = lui(0x200);
        v0 = v1 & v0;
        if (v0 != 0) {
            charge(5);
            a0 = s0;
            jal(0x2BF314, gen::fn_kwlnTaskGetWorkData_00195540);
            s0 = v0;
            lw(s1, v0, 8);
            for (;;) {  // L_002bf324
                charge(3);
                lw(v0, s1, 24);
                if (v0 != 0) {
                    charge(6);
                    a0 = s1;
                    a1 = 16;
                    a2 = 300;
                    lw(a3, s0, 4);
                    jalr(0x2BF340, v0.u());
                }
                charge(3);
                lw(s1, s1, 36);
                if (s1 == 0) break;
                backedge();
            }
        }
        charge(1);
        v0 = 0;
    }
L_002bf358:
    charge(6);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// sub_2BF650 [end command tasks]: destroys the "battle_command_calc" task (with its children) when it exists.
void Cpu::sub_2BF650() {
    enter(9);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    a0 = lui(0x69);
    a0 = addiu(a0, 28496);
    jal(0x2BF660, gen::fn_kwlnTaskGetTaskByName_00195340);
    a0 = v0;
    if (v0 != 0) {
        charge(2);
        jal(0x2BF674, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
    }
    charge(4);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// =================================================================================================================
// the remaining packet callbacks, the gauges' draw and the target lists
// =================================================================================================================

// nullsub_15: nullsub_15: returns.
void Cpu::nullsub_15() {
    enter(2);
}

// nullsub_16: nullsub_16: returns.
void Cpu::nullsub_16() {
    enter(2);
}

// nullsub_17: nullsub_17: returns.
void Cpu::nullsub_17() {
    enter(2);
}

// nullsub_18: nullsub_18: returns.
void Cpu::nullsub_18() {
    enter(2);
}

// sub_2BF9B0 [draw gauges]: draws every unit's HP / SP gauge (sub_2BCE10 on +2564, colour 0xB4736400 | (+55 ? 255 : 0))
// unless the battle is in phase 18 (+692) or paused (sub_2FF330, +20 0x4), when the gauges are on (+12 0x800).
void Cpu::sub_2BF9B0() {
    enter(9);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    lw(v1, gp, -18692);
    lw(a0, v1, 692);
    v1 = 18;
    if (a0 != v1) {
        charge(4);
        jal(0x2BF9D4, gen::fn_sub_2FF330_002ff330);
        if (v0 != 0) goto L_002bfa94;
        charge(5);
        lw(a0, gp, -18692);
        lw(v1, a0, 20);
        v1 = v1 & 0x4;
        if (v1 != 0) goto L_002bfa94;
        charge(4);
        lw(v1, a0, 12);
        v1 = v1 & 0x800;
        if (v1 == 0) goto L_002bfa94;
        charge(3);
        s0 = 0;
        for (;;) {  // L_002bfa88
            charge(3);
            v1 = sltiu(s0, 4);
            if (v1 == 0) break;
            backedge();
            charge(6);
            a0 = sll(s0, 3);
            lw(v1, gp, -18692);
            v1 = addu(v1, a0);
            lw(s1, v1, 336);
            for (;;) {  // L_002bfa7c
                charge(2);
                if (s1 == 0) break;
                backedge();
                charge(3);
                lw(v1, s1, 2604);
                if (v1 != 0) {
                    charge(4);
                    mtc1(zero, F13);
                    lbu(v0, s1, 55);
                    if (v0 != 0) {
                        charge(3);
                        v1 = 255;
                    } else {
                        charge(1);
                        v1 = 0;
                    }
                    charge(8);
                    v0 = lui(0xB473);
                    v0 = v0 | 0x6400;
                    a1 = v1 | v0;
                    a0 = s1;
                    mov_s(F12, F13);
                    a2 = addiu(s1, 2564);
                    jal(0x2BFA70, gen::fn_sub_2BCE10_002bce10);
                }
                charge(1);
                lw(s1, s1, 2612);
            }
            charge(1);
            s0 = addiu(s0, 1);
        }
    }
L_002bfa94:
    charge(6);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
}

// sub_2BFAB0 [0x50C update]: update (+108) of packet kind 0x50C: sub_1FF3B0. Returns 1.
void Cpu::sub_2BFAB0() {
    enter(9);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    jal(0x2BFAB8, gen::fn_sub_1FF3B0_001ff3b0);
    v0 = 1;
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// sub_2BFAE0 [create 0x50C]: creates packet kind 0x50C (no payload) with update sub_2BFAB0.
void Cpu::sub_2BFAE0() {
    enter(13);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    a0 = 1292;
    a1 = 0;
    jal(0x2BFAF0, gen::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2C);
    v1 = addiu(v1, -1360);
    sw(v1, v0, 108);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// sub_2BFB20 [0x50D update]: update (+108) of packet kind 0x50D: sub_1FF390. Returns 1.
void Cpu::sub_2BFB20() {
    enter(9);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    jal(0x2BFB28, gen::fn_sub_1FF390_001ff390);
    v0 = 1;
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// sub_2BFB50 [create 0x50D]: creates packet kind 0x50D (no payload) with update sub_2BFB20.
void Cpu::sub_2BFB50() {
    enter(13);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    a0 = 1293;
    a1 = 0;
    jal(0x2BFB60, gen::fn_sub_27EC10_0027ec10);
    v1 = lui(0x2C);
    v1 = addiu(v1, -1248);
    sw(v1, v0, 108);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// sub_2BFB90 [0x508 update]: update (+108) of packet kind 0x508 (payload {started}): the first call starts sub_1FE5F0,
// later calls wait for sub_1FE630; returns 1 while waiting, 0 when done.
void Cpu::sub_2BFB90() {
    enter(7);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    lw(v0, a0, 0);
    if (v0 == 0) {
        charge(6);
        jal(0x2BFBAC, gen::fn_sub_1FE5F0_001fe5f0);
        v0 = 1;
        sw(v0, s0, 0);
    } else {
        charge(4);
        jal(0x2BFBC4, gen::fn_sub_1FE630_001fe630);
        if (v0 != 0) goto L_002bfbe0;
        charge(3);
        v0 = 1;
        goto L_002bfbe4;
    }
L_002bfbe0:
    charge(1);
    v0 = 0;
L_002bfbe4:
    charge(5);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

// sub_2BFC00 [create 0x508]: creates packet kind 0x508 (4-byte payload: 0, flag 0x1 of +71 cleared) with update
// sub_2BFB90.
void Cpu::sub_2BFC00() {
    enter(18);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    a0 = 1288;
    a1 = 4;
    jal(0x2BFC10, gen::fn_sub_27EC10_0027ec10);
    lbu(v1, v0, 71);
    v1 = v1 & 0xFE;
    sb(v1, v0, 71);
    v1 = lui(0x2C);
    v1 = addiu(v1, -1136);
    sw(v1, v0, 108);
    lw(v1, v0, 120);
    sw(zero, v1, 0);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// sub_2BFC50: calls sub_45A430.
void Cpu::sub_2BFC50() {
    enter(8);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    jal(0x2BFC58, gen::fn_sub_45A430_0045a430);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// sub_2BFC70: calls sub_45AF70.
void Cpu::sub_2BFC70() {
    enter(8);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    jal(0x2BFC78, gen::fn_sub_45AF70_0045af70);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// sub_2BFC90: calls sub_45AF40.
void Cpu::sub_2BFC90() {
    enter(8);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    jal(0x2BFC98, gen::fn_sub_45AF40_0045af40);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
}

// sub_2BFCB0 [target list]: fills a target list (a1: 48 bytes cleared; +0.. the units, u16 count +56): a0 = the acting
// unit, a2 = the sides (bit 1 the actor's side, bit 2 the other, bit 4 side 2), a3 = the scope (1 the actor only, 2 not
// the actor, 4 the dead too, 8 only units with bad status 0x100000), $t0 = bad statuses that exclude; walks the
// battle's unit list (gBtl (gp-18692) +332, linked by +1192).
void Cpu::sub_2BFCB0() {
    enter(29);
    sp = addiu(sp, -176);
    sd(ra, sp, 144);
    sq(fp, sp, 128);
    sq(s7, sp, 112);
    sq(s6, sp, 96);
    sq(s5, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s4 = a0;
    s3 = a1;
    s5 = a2;
    s6 = a3;
    s2 = t0;
    a0 = s3;
    a1 = 0;
    a2 = 48;
    jal(0x2BFCFC, gen::fn_memset_00521408);
    sh(zero, s3, 56);
    sh(zero, s3, 58);
    sb(zero, s3, 60);
    lbu(v1, s3, 60);
    v1 = v1 | 0x1;
    sb(v1, s3, 60);
    if (s4 != 0) {
        charge(5);
        lw(v1, s4, 48);
        lbu(a0, v1, 162);
        v1 = 1;
        if (a0 != v1) {
            charge(2);
            if (a0 != 0) {
                charge(2);
                goto L_002bfd70;
            }
            charge(4);
            s1 = v1 & 0xFFFF;
            s0 = 2;
            goto L_002bfd70;
        }
        charge(4);
        s1 = 2;
        s0 = v1 & 0xFFFF;
    } else {
        charge(2);
        s1 = 1;
        s0 = 2;
    }
L_002bfd70:
    charge(5);
    a1 = 0;
    a0 = s5 & 0xFF;
    v1 = a0 & 0x1;
    if (v1 != 0) {
        charge(2);
        v1 = a1 | s1;
        a1 = v1 & 0xFFFF;
    }
    charge(3);
    v1 = a0 & 0x2;
    if (v1 != 0) {
        charge(2);
        v1 = a1 | s0;
        a1 = v1 & 0xFFFF;
    }
    charge(3);
    v1 = a0 & 0x4;
    if (v1 != 0) {
        charge(2);
        v1 = a1 | 0x4;
        a1 = v1 & 0xFFFF;
    }
    charge(4);
    a0 = s6 & 0xFF;
    v1 = a0 & 0x1;
    if (v1 != 0) {
        charge(5);
        sw(s4, s3, 0);
        v1 = 1;
        sh(v1, s3, 56);
    } else {
        charge(10);
        lw(v1, gp, -18692);
        lw(s5, v1, 332);
        s1 = a1 & 0xFFFF;
        s6 = s1 & 0x4;
        s7 = a0 & 0x2;
        fp = a0 & 0x4;
        v1 = a0 & 0x8;
        sq(v1, sp, 160);
        for (;;) {  // L_002bff1c
            charge(2);
            if (s5 == 0) break;
            backedge();
            charge(2);
            if (s4 != 0) {
                charge(4);
                lhu(v1, s5, 26);
                v1 = v1 & 0x8;
                if (v1 == 0) goto L_002bff18;
            }
            charge(4);
            lhu(v1, s5, 26);
            v1 = v1 & 0x1;
            if (v1 != 0) {
                charge(5);
                lw(s0, s5, 48);
                lbu(a0, s0, 162);
                v1 = 2;
                if (a0 != v1) {
                    charge(4);
                    lw(v1, s0, 156);
                    v1 = v1 & 0x8;
                    if (v1 == 0) goto L_002bff18;
                }
                charge(5);
                v1 = 1;
                v1 = sllv(v1, a0);
                v1 = s1 & v1;
                if (v1 == 0) goto L_002bff18;
                charge(2);
                if (s6 == 0) {
                    charge(2);
                    if (s7 != 0) {
                        charge(2);
                        if (s4 == s5) goto L_002bff18;
                    }
                    charge(2);
                    if (fp == 0) {
                        charge(6);
                        lw(a0, s0, 2604);
                        a1 = 0;
                        jal(0x2BFE88, gen::fn_datCalcIsDead_0030b5a0);
                        if (v0 != 0) goto L_002bff18;
                    }
                    charge(3);
                    lq(v1, sp, 160);
                    if (v1 != 0) {
                        charge(6);
                        lw(a0, s0, 2604);
                        a1 = lui(0x10);
                        jal(0x2BFEAC, gen::fn_datCalcChkBadStatus_00300580);
                        if (v0 != 0) goto L_002bfefc;
                        charge(2);
                        goto L_002bff18;
                    }
                    charge(2);
                    if (s2 == 0) goto L_002bfefc;
                    charge(7);
                    lw(a0, s0, 2604);
                    lw(a1, a0, 12);
                    v1 = lui(0xFFEF);
                    v1 = v1 | 0xFFFF;
                    v1 = a1 & v1;
                    if (v1 == 0) goto L_002bff18;
                    charge(5);
                    a1 = s2;
                    jal(0x2BFEEC, gen::fn_datCalcChkBadStatus_00300580);
                    if (v0 != 0) goto L_002bff18;
                }
L_002bfefc:
                charge(7);
                lhu(v1, s3, 56);
                v1 = sll(v1, 2);
                v1 = addu(s3, v1);
                sw(s5, v1, 0);
                lhu(v1, s3, 56);
                v1 = addiu(v1, 1);
                sh(v1, s3, 56);
            }
L_002bff18:
            charge(1);
            lw(s5, s5, 1192);
        }
    }
    charge(13);
    ld(ra, sp, 144);
    lq(fp, sp, 128);
    lq(s7, sp, 112);
    lq(s6, sp, 96);
    lq(s5, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 176);
}

// sub_2BFF60 [skill targets]: for skill a2 (its SKILL.TBL row, gp-18680): with a1 not 0 builds a0's target list
// (sub_2BFCB0) from the row's sides +9 / scope +10 / bad-status mask +12 (a3 not 0 swaps the side bits 1 / 2 and the
// scope bit 1); returns the row's byte +8.
void Cpu::sub_2BFF60() {
    enter(6);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a2;
    if (a1 != 0) {
        charge(12);
        v1 = s0 & 0xFFFF;
        v0 = sll(v1, 2);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        v0 = addu(v0, v1);
        t1 = sll(v0, 2);
        lw(t0, gp, -18680);
        v0 = addu(t1, t0);
        lbu(a2, v0, 9);
        lbu(t2, v0, 10);
        if (a3 != 0) {
            charge(4);
            a3 = a2 & 0xFF;
            v1 = a3 & 0x1;
            if (v1 != 0) {
                charge(3);
                v0 = a3 & 0x2;
                if (v0 != 0) goto L_002bffdc;
                charge(6);
                v0 = a2 & 0xFE;
                v0 = v0 & 0xFF;
                v0 = v0 | 0x2;
                a2 = v0 & 0xFF;
                goto L_002c0000;
            }
L_002bffdc:
            charge(3);
            v0 = a3 & 0x2;
            if (v0 != 0) {
                charge(2);
                if (v1 != 0) goto L_002c0000;
                charge(4);
                v0 = a2 & 0xFD;
                v0 = v0 & 0xFF;
                v0 = v0 | 0x1;
                a2 = v0 & 0xFF;
            }
L_002c0000:
            charge(4);
            v0 = t2 & 0xFF;
            v0 = v0 & 0x1;
            if (v0 == 0) goto L_002c0020;
            charge(4);
            v0 = t2 & 0xFE;
            v0 = v0 & 0xFF;
            v0 = v0 | 0x2;
            t2 = v0 & 0xFF;
        }
L_002c0020:
        charge(5);
        v0 = addu(t1, t0);
        lhu(t0, v0, 12);
        a3 = t2;
        jal(0x2C002C, gen::fn_sub_2BFCB0_002bfcb0);
    }
    charge(14);
    lw(a0, gp, -18680);
    v1 = s0 & 0xFFFF;
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    v0 = addu(v0, v1);
    v0 = sll(v0, 2);
    v0 = addu(v0, a0);
    lbu(v0, v0, 8);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
}

}  // namespace
}  // namespace battle_fx

// --- the typed entry points (battle_fx.h) ----------------------------------------------------------------------------
u32 sub_2B77C0(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2B77C0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B79E0(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2B79E0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B7BD0(EEContext& ctx, u32 a0, u32 a1, u32 a2) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    battle_fx::Cpu(ctx).sub_2B7BD0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B7C50(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2B7C50();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B8900(EEContext& ctx, u32 a0, u32 a1, u32 a2) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    battle_fx::Cpu(ctx).sub_2B8900();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B8970(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2B8970();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B8990(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2B8990();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B8B50(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2B8B50();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B8B70(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    ee::core::set_gpr64(ctx, GPR_A3, battle_fx::sx(a3));
    battle_fx::Cpu(ctx).sub_2B8B70();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B8C00(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2B8C00();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B8D60(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2B8D60();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B8DC0(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2B8DC0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B8F40(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2B8F40();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B90D0(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2B90D0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B9220(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2B9220();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B9300(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2B9300();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B9350(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2B9350();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B9370(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2B9370();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B93C0(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2B93C0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B9590(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2B9590();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B9600(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2B9600();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B9640(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2B9640();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B96E0(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2B96E0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B96F0(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    ee::core::set_gpr64(ctx, GPR_A3, battle_fx::sx(a3));
    battle_fx::Cpu(ctx).sub_2B96F0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B99D0(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    ee::core::set_gpr64(ctx, GPR_A3, battle_fx::sx(a3));
    battle_fx::Cpu(ctx).sub_2B99D0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B9B00(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    ee::core::set_gpr64(ctx, GPR_A3, battle_fx::sx(a3));
    battle_fx::Cpu(ctx).sub_2B9B00();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B9C00(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    ee::core::set_gpr64(ctx, GPR_A3, battle_fx::sx(a3));
    battle_fx::Cpu(ctx).sub_2B9C00();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B9D40(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    ee::core::set_gpr64(ctx, GPR_A3, battle_fx::sx(a3));
    battle_fx::Cpu(ctx).sub_2B9D40();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B9E80(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    ee::core::set_gpr64(ctx, GPR_A3, battle_fx::sx(a3));
    battle_fx::Cpu(ctx).sub_2B9E80();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2B9F30(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    ee::core::set_gpr64(ctx, GPR_A3, battle_fx::sx(a3));
    battle_fx::Cpu(ctx).sub_2B9F30();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BA000(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    ee::core::set_gpr64(ctx, GPR_A3, battle_fx::sx(a3));
    battle_fx::Cpu(ctx).sub_2BA000();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BA0D0(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    ee::core::set_gpr64(ctx, GPR_A3, battle_fx::sx(a3));
    battle_fx::Cpu(ctx).sub_2BA0D0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BA0F0(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    ee::core::set_gpr64(ctx, GPR_A3, battle_fx::sx(a3));
    battle_fx::Cpu(ctx).sub_2BA0F0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BA3A0(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BA3A0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BA900(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BA900();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BAC00(EEContext& ctx, u32 a0, u32 a1, u32 a2) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    battle_fx::Cpu(ctx).sub_2BAC00();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BACB0(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BACB0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BAD60(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BAD60();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BAEC0(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BAEC0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BAF30(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BAF30();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BAF90(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3, u32 t0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    ee::core::set_gpr64(ctx, GPR_A3, battle_fx::sx(a3));
    ee::core::set_gpr64(ctx, GPR_T0, battle_fx::sx(t0));
    battle_fx::Cpu(ctx).sub_2BAF90();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BB050(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BB050();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BB0B0(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BB0B0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BB290(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BB290();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BB2F0(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3, u32 t0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    ee::core::set_gpr64(ctx, GPR_A3, battle_fx::sx(a3));
    ee::core::set_gpr64(ctx, GPR_T0, battle_fx::sx(t0));
    battle_fx::Cpu(ctx).sub_2BB2F0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BB3A0(EEContext& ctx) {
    battle_fx::Cpu(ctx).sub_2BB3A0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BB580(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BB580();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 nullsub_14(EEContext& ctx) {
    battle_fx::Cpu(ctx).nullsub_14();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BB770(EEContext& ctx) {
    battle_fx::Cpu(ctx).sub_2BB770();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BB9C0(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BB9C0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BBAC0(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2BBAC0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BBBC0(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BBBC0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BBDC0(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2BBDC0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BBDF0(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BBDF0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BBE00(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BBE00();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BBF80(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2BBF80();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BBFA0(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BBFA0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BC0E0(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2BC0E0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BC680(EEContext& ctx) {
    battle_fx::Cpu(ctx).sub_2BC680();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BC7B0(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BC7B0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BC7E0(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BC7E0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BC830(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BC830();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BC890(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2BC890();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BC910(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BC910();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BC950(EEContext& ctx, u32 a0, u32 a1, u32 a2) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    battle_fx::Cpu(ctx).sub_2BC950();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BCDE0(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2BCDE0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BCE10(EEContext& ctx, u32 a0, u32 a1, u32 a2) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    battle_fx::Cpu(ctx).sub_2BCE10();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BD060(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BD060();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BD080(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BD080();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BD210(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BD210();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BD230(EEContext& ctx, u32 a0, u32 a1, u32 a2) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    battle_fx::Cpu(ctx).sub_2BD230();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BD2C0(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BD2C0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BD2E0(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BD2E0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BD460(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BD460();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BD480(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BD480();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BD590(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2BD590();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BD690(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2BD690();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BD780(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2BD780();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BD850(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2BD850();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BD8B0(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BD8B0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BDBA0(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BDBA0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BDBD0(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3, u32 t0, u32 t1, u32 t2, u32 t3) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    ee::core::set_gpr64(ctx, GPR_A3, battle_fx::sx(a3));
    ee::core::set_gpr64(ctx, GPR_T0, battle_fx::sx(t0));
    ee::core::set_gpr64(ctx, GPR_T1, battle_fx::sx(t1));
    ee::core::set_gpr64(ctx, GPR_T2, battle_fx::sx(t2));
    ee::core::set_gpr64(ctx, GPR_T3, battle_fx::sx(t3));
    battle_fx::Cpu(ctx).sub_2BDBD0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BDCD0(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BDCD0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BDDD0(EEContext& ctx) {
    battle_fx::Cpu(ctx).sub_2BDDD0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BDE10(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2BDE10();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BDFB0(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BDFB0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 nullsub_100(EEContext& ctx) {
    battle_fx::Cpu(ctx).nullsub_100();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BE2F0(EEContext& ctx) {
    battle_fx::Cpu(ctx).sub_2BE2F0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BE390(EEContext& ctx, u32 a0, u32 a1, u32 a2) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    battle_fx::Cpu(ctx).sub_2BE390();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BE580(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2BE580();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BE5D0(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2BE5D0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BE5F0(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2BE5F0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BE610(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BE610();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BE620(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2BE620();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BE720(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    ee::core::set_gpr64(ctx, GPR_A3, battle_fx::sx(a3));
    battle_fx::Cpu(ctx).sub_2BE720();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 nullsub_101(EEContext& ctx) {
    battle_fx::Cpu(ctx).nullsub_101();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BE9E0(EEContext& ctx, u32 a0, u32 a1) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    battle_fx::Cpu(ctx).sub_2BE9E0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BEA80(EEContext& ctx, u32 a0, u32 a1, u32 a2) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    battle_fx::Cpu(ctx).sub_2BEA80();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BECC0(EEContext& ctx) {
    battle_fx::Cpu(ctx).sub_2BECC0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 btlCommand_UpdateBattleCommandCalcTask(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).btlCommand_UpdateBattleCommandCalcTask();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 btlCommand_UpdateBattleCommandDrawTask(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).btlCommand_UpdateBattleCommandDrawTask();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BF650(EEContext& ctx) {
    battle_fx::Cpu(ctx).sub_2BF650();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 nullsub_15(EEContext& ctx) {
    battle_fx::Cpu(ctx).nullsub_15();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 nullsub_16(EEContext& ctx) {
    battle_fx::Cpu(ctx).nullsub_16();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 nullsub_17(EEContext& ctx) {
    battle_fx::Cpu(ctx).nullsub_17();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 nullsub_18(EEContext& ctx) {
    battle_fx::Cpu(ctx).nullsub_18();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BF9B0(EEContext& ctx) {
    battle_fx::Cpu(ctx).sub_2BF9B0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BFAB0(EEContext& ctx) {
    battle_fx::Cpu(ctx).sub_2BFAB0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BFAE0(EEContext& ctx) {
    battle_fx::Cpu(ctx).sub_2BFAE0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BFB20(EEContext& ctx) {
    battle_fx::Cpu(ctx).sub_2BFB20();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BFB50(EEContext& ctx) {
    battle_fx::Cpu(ctx).sub_2BFB50();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BFB90(EEContext& ctx, u32 a0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    battle_fx::Cpu(ctx).sub_2BFB90();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BFC00(EEContext& ctx) {
    battle_fx::Cpu(ctx).sub_2BFC00();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BFC50(EEContext& ctx) {
    battle_fx::Cpu(ctx).sub_2BFC50();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BFC70(EEContext& ctx) {
    battle_fx::Cpu(ctx).sub_2BFC70();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BFC90(EEContext& ctx) {
    battle_fx::Cpu(ctx).sub_2BFC90();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BFCB0(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3, u32 t0) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    ee::core::set_gpr64(ctx, GPR_A3, battle_fx::sx(a3));
    ee::core::set_gpr64(ctx, GPR_T0, battle_fx::sx(t0));
    battle_fx::Cpu(ctx).sub_2BFCB0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2BFF60(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_fx::sx(a0));
    ee::core::set_gpr64(ctx, GPR_A1, battle_fx::sx(a1));
    ee::core::set_gpr64(ctx, GPR_A2, battle_fx::sx(a2));
    ee::core::set_gpr64(ctx, GPR_A3, battle_fx::sx(a3));
    battle_fx::Cpu(ctx).sub_2BFF60();
    return ee::core::gpr32(ctx, GPR_V0);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (recomp/generated/functions.h signatures) ---------------------------------
namespace p3fes::recomp_gen {
namespace bfx = ::p3fes::game::battle_fx;

void fn_sub_2B77C0_002b77c0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B77C0(); }
void fn_sub_2B79E0_002b79e0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B79E0(); }
void fn_sub_2B7BD0_002b7bd0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B7BD0(); }
void fn_sub_2B7C50_002b7c50(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B7C50(); }
void fn_sub_2B8900_002b8900(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B8900(); }
void fn_sub_2B8970_002b8970(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B8970(); }
void fn_sub_2B8990_002b8990(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B8990(); }
void fn_sub_2B8B50_002b8b50(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B8B50(); }
void fn_sub_2B8B70_002b8b70(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B8B70(); }
void fn_sub_2B8C00_002b8c00(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B8C00(); }
void fn_sub_2B8D60_002b8d60(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B8D60(); }
void fn_sub_2B8DC0_002b8dc0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B8DC0(); }
void fn_sub_2B8F40_002b8f40(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B8F40(); }
void fn_sub_2B90D0_002b90d0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B90D0(); }
void fn_sub_2B9220_002b9220(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B9220(); }
void fn_sub_2B9300_002b9300(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B9300(); }
void fn_sub_2B9350_002b9350(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B9350(); }
void fn_sub_2B9370_002b9370(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B9370(); }
void fn_sub_2B93C0_002b93c0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B93C0(); }
void fn_sub_2B9590_002b9590(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B9590(); }
void fn_sub_2B9600_002b9600(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B9600(); }
void fn_sub_2B9640_002b9640(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B9640(); }
void fn_sub_2B96E0_002b96e0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B96E0(); }
void fn_sub_2B96F0_002b96f0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B96F0(); }
void fn_sub_2B99D0_002b99d0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B99D0(); }
void fn_sub_2B9B00_002b9b00(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B9B00(); }
void fn_sub_2B9C00_002b9c00(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B9C00(); }
void fn_sub_2B9D40_002b9d40(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B9D40(); }
void fn_sub_2B9E80_002b9e80(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B9E80(); }
void fn_sub_2B9F30_002b9f30(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2B9F30(); }
void fn_sub_2BA000_002ba000(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BA000(); }
void fn_sub_2BA0D0_002ba0d0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BA0D0(); }
void fn_sub_2BA0F0_002ba0f0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BA0F0(); }
void fn_sub_2BA3A0_002ba3a0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BA3A0(); }
void fn_sub_2BA900_002ba900(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BA900(); }
void fn_sub_2BAC00_002bac00(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BAC00(); }
void fn_sub_2BACB0_002bacb0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BACB0(); }
void fn_sub_2BAD60_002bad60(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BAD60(); }
void fn_sub_2BAEC0_002baec0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BAEC0(); }
void fn_sub_2BAF30_002baf30(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BAF30(); }
void fn_sub_2BAF90_002baf90(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BAF90(); }
void fn_sub_2BB050_002bb050(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BB050(); }
void fn_sub_2BB0B0_002bb0b0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BB0B0(); }
void fn_sub_2BB290_002bb290(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BB290(); }
void fn_sub_2BB2F0_002bb2f0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BB2F0(); }
void fn_sub_2BB3A0_002bb3a0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BB3A0(); }
void fn_sub_2BB580_002bb580(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BB580(); }
void fn_nullsub_14_002bb760(p3fes::EEContext& ctx) { bfx::Cpu(ctx).nullsub_14(); }
void fn_sub_2BB770_002bb770(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BB770(); }
void fn_sub_2BB9C0_002bb9c0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BB9C0(); }
void fn_sub_2BBAC0_002bbac0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BBAC0(); }
void fn_sub_2BBBC0_002bbbc0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BBBC0(); }
void fn_sub_2BBDC0_002bbdc0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BBDC0(); }
void fn_sub_2BBDF0_002bbdf0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BBDF0(); }
void fn_sub_2BBE00_002bbe00(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BBE00(); }
void fn_sub_2BBF80_002bbf80(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BBF80(); }
void fn_sub_2BBFA0_002bbfa0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BBFA0(); }
void fn_sub_2BC0E0_002bc0e0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BC0E0(); }
void fn_sub_2BC680_002bc680(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BC680(); }
void fn_sub_2BC7B0_002bc7b0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BC7B0(); }
void fn_sub_2BC7E0_002bc7e0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BC7E0(); }
void fn_sub_2BC830_002bc830(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BC830(); }
void fn_sub_2BC890_002bc890(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BC890(); }
void fn_sub_2BC910_002bc910(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BC910(); }
void fn_sub_2BC950_002bc950(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BC950(); }
void fn_sub_2BCDE0_002bcde0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BCDE0(); }
void fn_sub_2BCE10_002bce10(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BCE10(); }
void fn_sub_2BD060_002bd060(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BD060(); }
void fn_sub_2BD080_002bd080(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BD080(); }
void fn_sub_2BD210_002bd210(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BD210(); }
void fn_sub_2BD230_002bd230(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BD230(); }
void fn_sub_2BD2C0_002bd2c0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BD2C0(); }
void fn_sub_2BD2E0_002bd2e0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BD2E0(); }
void fn_sub_2BD460_002bd460(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BD460(); }
void fn_sub_2BD480_002bd480(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BD480(); }
void fn_sub_2BD590_002bd590(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BD590(); }
void fn_sub_2BD690_002bd690(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BD690(); }
void fn_sub_2BD780_002bd780(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BD780(); }
void fn_sub_2BD850_002bd850(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BD850(); }
void fn_sub_2BD8B0_002bd8b0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BD8B0(); }
void fn_sub_2BDBA0_002bdba0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BDBA0(); }
void fn_sub_2BDBD0_002bdbd0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BDBD0(); }
void fn_sub_2BDCD0_002bdcd0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BDCD0(); }
void fn_sub_2BDDD0_002bddd0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BDDD0(); }
void fn_sub_2BDE10_002bde10(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BDE10(); }
void fn_sub_2BDFB0_002bdfb0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BDFB0(); }
void fn_nullsub_100_002be2e0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).nullsub_100(); }
void fn_sub_2BE2F0_002be2f0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BE2F0(); }
void fn_sub_2BE390_002be390(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BE390(); }
void fn_sub_2BE580_002be580(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BE580(); }
void fn_sub_2BE5D0_002be5d0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BE5D0(); }
void fn_sub_2BE5F0_002be5f0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BE5F0(); }
void fn_sub_2BE610_002be610(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BE610(); }
void fn_sub_2BE620_002be620(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BE620(); }
void fn_sub_2BE720_002be720(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BE720(); }
void fn_nullsub_101_002be9d0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).nullsub_101(); }
void fn_sub_2BE9E0_002be9e0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BE9E0(); }
void fn_sub_2BEA80_002bea80(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BEA80(); }
void fn_sub_2BECC0_002becc0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BECC0(); }
void fn_btlCommand_UpdateBattleCommandCalcTask_002bef20(p3fes::EEContext& ctx) { bfx::Cpu(ctx).btlCommand_UpdateBattleCommandCalcTask(); }
void fn_btlCommand_UpdateBattleCommandDrawTask_002bf2b0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).btlCommand_UpdateBattleCommandDrawTask(); }
void fn_sub_2BF650_002bf650(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BF650(); }
void fn_nullsub_15_002bf970(p3fes::EEContext& ctx) { bfx::Cpu(ctx).nullsub_15(); }
void fn_nullsub_16_002bf980(p3fes::EEContext& ctx) { bfx::Cpu(ctx).nullsub_16(); }
void fn_nullsub_17_002bf990(p3fes::EEContext& ctx) { bfx::Cpu(ctx).nullsub_17(); }
void fn_nullsub_18_002bf9a0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).nullsub_18(); }
void fn_sub_2BF9B0_002bf9b0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BF9B0(); }
void fn_sub_2BFAB0_002bfab0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BFAB0(); }
void fn_sub_2BFAE0_002bfae0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BFAE0(); }
void fn_sub_2BFB20_002bfb20(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BFB20(); }
void fn_sub_2BFB50_002bfb50(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BFB50(); }
void fn_sub_2BFB90_002bfb90(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BFB90(); }
void fn_sub_2BFC00_002bfc00(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BFC00(); }
void fn_sub_2BFC50_002bfc50(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BFC50(); }
void fn_sub_2BFC70_002bfc70(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BFC70(); }
void fn_sub_2BFC90_002bfc90(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BFC90(); }
void fn_sub_2BFCB0_002bfcb0(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BFCB0(); }
void fn_sub_2BFF60_002bff60(p3fes::EEContext& ctx) { bfx::Cpu(ctx).sub_2BFF60(); }
}  // namespace p3fes::recomp_gen
