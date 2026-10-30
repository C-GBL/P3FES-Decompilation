// The battle result screen (game/include/p3fes/game/battle_result.h has the data flow;
// docs/ANALYSIS/27_unmapped_bands.md section 3), hand-decompiled from SLUS_216.21. Phase 5 slice `battle_result`: these
// replace the recompiled bodies listed in game/replaced.txt; tests/game/test_battle_result.cpp runs each against its
// __recomp body.
//
// Cycle model (ADR-0013): every charge() below is one `ctx.cycles += N` block of the recompiled body on the executed
// path, charged where the block starts (a block that ends in a `jal` is charged in full before the call); backedge()
// sits wherever the recompiled body has a check point on a backward jump (the loops, and the backward `goto`s of the
// compiler's block layout, kept as explicit check points). A `jr` through a jump table reads the table entry from the
// guest image and switches on the target, as the original does; an entry outside the table's cases tail-jumps through
// rt::lookup_func like the recompiled body.
//
// Registers: register-faithful (battle_result.h). Each body runs on a Cpu view of the guest context -- one named
// variable per GPR (64-bit writes keep bits 64..127, as the EE does; lq writes all 128), the FPU and HI/LO operations
// through the runtime's own instruction semantics, the prologue spills and epilogue reloads on the guest stack, the
// calls with $ra = the original link -- so every register holds at every check point, call and return what the
// original holds there. The compiled loop shapes are kept (a loop whose test block comes first checks before every
// iteration); structure offsets are named in the comments.
#include "p3fes/game/battle_result.h"

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"
#include "p3fes_recomp_rt.h"

namespace p3fes::recomp_gen {
void fn_sub_108570_00108570(p3fes::EEContext&);
void fn_sub_1085C0_001085c0(p3fes::EEContext&);
void fn_sub_108670_00108670(p3fes::EEContext&);
void fn_sub_108710_00108710(p3fes::EEContext&);
void fn_sub_10A370_0010a370(p3fes::EEContext&);
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);
void fn_sprFontGetFile_001120a0(p3fes::EEContext&);
void fn_sub_16C470_0016c470(p3fes::EEContext&);
void fn_datGetEquipmentIdx_0016cb80(p3fes::EEContext&);
void fn_sub_16DA50_0016da50(p3fes::EEContext&);
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);
void fn_sub_16F630_0016f630(p3fes::EEContext&);
void fn_sub_170760_00170760(p3fes::EEContext&);
void fn_sub_170860_00170860(p3fes::EEContext&);
void fn_sub_170D60_00170d60(p3fes::EEContext&);
void fn_sub_170DA0_00170da0(p3fes::EEContext&);
void fn_sub_170DF0_00170df0(p3fes::EEContext&);
void fn_sub_170E40_00170e40(p3fes::EEContext&);
void fn_sub_171110_00171110(p3fes::EEContext&);
void fn_sub_171360_00171360(p3fes::EEContext&);
void fn_sub_171390_00171390(p3fes::EEContext&);
void fn_sub_173220_00173220(p3fes::EEContext&);
void fn_sub_173370_00173370(p3fes::EEContext&);
void fn_sub_173B00_00173b00(p3fes::EEContext&);
void fn_sub_173B60_00173b60(p3fes::EEContext&);
void fn_datPersonaGetByPcId_00174800(p3fes::EEContext&);
void fn_sub_174B40_00174b40(p3fes::EEContext&);
void fn_sub_174E20_00174e20(p3fes::EEContext&);
void fn_sub_175130_00175130(p3fes::EEContext&);
void fn_sub_175820_00175820(p3fes::EEContext&);
void fn_sub_175CA0_00175ca0(p3fes::EEContext&);
void fn_sub_176210_00176210(p3fes::EEContext&);
void fn_sub_1764B0_001764b0(p3fes::EEContext&);
void fn_sub_176840_00176840(p3fes::EEContext&);
void fn_sub_176A30_00176a30(p3fes::EEContext&);
void fn_sub_1770D0_001770d0(p3fes::EEContext&);
void fn_sub_177790_00177790(p3fes::EEContext&);
void fn_sub_177B90_00177b90(p3fes::EEContext&);
void fn_sub_177C50_00177c50(p3fes::EEContext&);
void fn_sub_177CA0_00177ca0(p3fes::EEContext&);
void fn_sub_177CE0_00177ce0(p3fes::EEContext&);
void fn_sub_177D10_00177d10(p3fes::EEContext&);
void fn_sub_17D790_0017d790(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_sub_182C50_00182c50(p3fes::EEContext&);
void fn_sub_1831E0_001831e0(p3fes::EEContext&);
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);
void fn_sub_198590_00198590(p3fes::EEContext&);
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line): `jr $ra` in retail
void fn_brRoot_CreateBattleResultTasks_001ef500(p3fes::EEContext&);
void fn_sub_1F0990_001f0990(p3fes::EEContext&);
void fn_sub_1F0C40_001f0c40(p3fes::EEContext&);  // (this file)
void fn_sub_1F0F40_001f0f40(p3fes::EEContext&);  // (this file)
void fn_sub_1F0FF0_001f0ff0(p3fes::EEContext&);  // (this file)
void fn_sub_1F1140_001f1140(p3fes::EEContext&);  // (this file)
void fn_sub_1F1240_001f1240(p3fes::EEContext&);  // (this file)
void fn_sub_1F13B0_001f13b0(p3fes::EEContext&);
void fn_sub_1F1C50_001f1c50(p3fes::EEContext&);  // (this file)
void fn_sub_1F1E90_001f1e90(p3fes::EEContext&);  // (this file)
void fn_sub_1F30D0_001f30d0(p3fes::EEContext&);
void fn_sub_1F30F0_001f30f0(p3fes::EEContext&);
void fn_sub_1F5810_001f5810(p3fes::EEContext&);
void fn_sub_1F9800_001f9800(p3fes::EEContext&);
void fn_sub_1F9890_001f9890(p3fes::EEContext&);
void fn_sub_1F9D70_001f9d70(p3fes::EEContext&);  // (this file)
void fn_sub_1F9E90_001f9e90(p3fes::EEContext&);
void fn_sub_1FB130_001fb130(p3fes::EEContext&);  // (this file)
void fn_sub_1FB3F0_001fb3f0(p3fes::EEContext&);  // (this file)
void fn_sub_1FB4B0_001fb4b0(p3fes::EEContext&);  // (this file)
void fn_sub_1FBDF0_001fbdf0(p3fes::EEContext&);  // (this file)
void fn_sub_1FC870_001fc870(p3fes::EEContext&);
void fn_sub_209F00_00209f00(p3fes::EEContext&);
void fn_sub_20A800_0020a800(p3fes::EEContext&);
void fn_sub_20AC90_0020ac90(p3fes::EEContext&);
void fn_sub_20B250_0020b250(p3fes::EEContext&);
void fn_sub_20C590_0020c590(p3fes::EEContext&);
void fn_sub_20C5F0_0020c5f0(p3fes::EEContext&);
void fn_sub_20CC80_0020cc80(p3fes::EEContext&);
void fn_sub_20CD50_0020cd50(p3fes::EEContext&);
void fn_sub_20D820_0020d820(p3fes::EEContext&);
void fn_sub_219D90_00219d90(p3fes::EEContext&);
void fn_sub_21A120_0021a120(p3fes::EEContext&);
void fn_sub_21A920_0021a920(p3fes::EEContext&);
void fn_sub_21AB80_0021ab80(p3fes::EEContext&);
void fn_sub_21C790_0021c790(p3fes::EEContext&);
void fn_sub_21C9F0_0021c9f0(p3fes::EEContext&);
void fn_sub_21CCA0_0021cca0(p3fes::EEContext&);
void fn_sub_21D3B0_0021d3b0(p3fes::EEContext&);
void fn_sub_21D890_0021d890(p3fes::EEContext&);
void fn_sub_21D8E0_0021d8e0(p3fes::EEContext&);
void fn_sub_21D950_0021d950(p3fes::EEContext&);
void fn_sub_21E380_0021e380(p3fes::EEContext&);
void fn_sub_21EA00_0021ea00(p3fes::EEContext&);
void fn_sub_21EAC0_0021eac0(p3fes::EEContext&);
void fn_sub_21EB80_0021eb80(p3fes::EEContext&);
void fn_sub_2339D0_002339d0(p3fes::EEContext&);
void fn_sub_233B20_00233b20(p3fes::EEContext&);
void fn_sub_233C00_00233c00(p3fes::EEContext&);
void fn_sub_234570_00234570(p3fes::EEContext&);  // (this file)
void fn_sub_234A00_00234a00(p3fes::EEContext&);  // (this file)
void fn_sub_2350F0_002350f0(p3fes::EEContext&);
void fn_sub_235F30_00235f30(p3fes::EEContext&);
void fn_sub_236280_00236280(p3fes::EEContext&);  // (this file)
void fn_sub_2362E0_002362e0(p3fes::EEContext&);  // (this file)
void fn_sub_236390_00236390(p3fes::EEContext&);
void fn_bpIfontDrawNumber_00238980(p3fes::EEContext&);
void fn_sub_2392D0_002392d0(p3fes::EEContext&);
void fn_sub_23B990_0023b990(p3fes::EEContext&);
void fn_sub_23D240_0023d240(p3fes::EEContext&);
void fn_sub_24BB30_0024bb30(p3fes::EEContext&);
void fn_sub_24BE40_0024be40(p3fes::EEContext&);
void fn_sub_24BED0_0024bed0(p3fes::EEContext&);  // (this file)
void fn_sub_24BF20_0024bf20(p3fes::EEContext&);  // (this file)
void fn_sub_24BF80_0024bf80(p3fes::EEContext&);
void fn_sub_24C040_0024c040(p3fes::EEContext&);  // (this file)
void fn_sub_24C090_0024c090(p3fes::EEContext&);  // (this file)
void fn_sub_262790_00262790(p3fes::EEContext&);
void fn_sub_2630E0_002630e0(p3fes::EEContext&);
void fn_sub_264F90_00264f90(p3fes::EEContext&);
void fn_sub_275A90_00275a90(p3fes::EEContext&);
void fn_sub_275CB0_00275cb0(p3fes::EEContext&);
void fn_sub_278550_00278550(p3fes::EEContext&);
void fn_datCalcAddHp_00300410(p3fes::EEContext&);
void fn_datCalcSetBadStatus_003004f0(p3fes::EEContext&);
void fn_datCalcClearBadStatus_00300560(p3fes::EEContext&);
void fn_datCalcDamage_00303130(p3fes::EEContext&);
void fn_sub_308930_00308930(p3fes::EEContext&);
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);
void fn_sub_34FCD0_0034fcd0(p3fes::EEContext&);
void fn_sub_34FCF0_0034fcf0(p3fes::EEContext&);
void fn_sub_34FD30_0034fd30(p3fes::EEContext&);
void fn_sub_34FD70_0034fd70(p3fes::EEContext&);
void fn_sub_34FDF0_0034fdf0(p3fes::EEContext&);
void fn_sub_34FF70_0034ff70(p3fes::EEContext&);
void fn_sub_34FF90_0034ff90(p3fes::EEContext&);
void fn_scrGetIntPara_0035ed20(p3fes::EEContext&);
void fn_sub_3B0170_003b0170(p3fes::EEContext&);
void fn_frFontBuildGlyphList_003b0970(p3fes::EEContext&);
void fn_frFontLineSetRgba_003b0e20(p3fes::EEContext&);
void fn_frFontSetDefaultGlyphFlags_003b0e70(p3fes::EEContext&);
void fn_frFontClearDefaultGlyphFlags_003b0e90(p3fes::EEContext&);
void fn_sub_3B2C60_003b2c60(p3fes::EEContext&);
void fn_sub_3C72D0_003c72d0(p3fes::EEContext&);
void fn_msgWinRequestMessage_003c7430(p3fes::EEContext&);
void fn_msgWinClose_003c7650(p3fes::EEContext&);
void fn_sub_3C77A0_003c77a0(p3fes::EEContext&);
void fn_sub_3C7850_003c7850(p3fes::EEContext&);
void fn_sub_3C7990_003c7990(p3fes::EEContext&);
void fn_sub_3C7BC0_003c7bc0(p3fes::EEContext&);
void fn_sub_3C7C20_003c7c20(p3fes::EEContext&);
void fn_sub_3CDA60_003cda60(p3fes::EEContext&);
void fn_sub_3CDBA0_003cdba0(p3fes::EEContext&);
void fn_sub_3CDC80_003cdc80(p3fes::EEContext&);
void fn_sub_3CDCD0_003cdcd0(p3fes::EEContext&);
void fn_sub_3CDE00_003cde00(p3fes::EEContext&);
void fn_sub_488F30_00488f30(p3fes::EEContext&);
void fn_sub_4BDDE0_004bdde0(p3fes::EEContext&);
void fn_sub_4C9D70_004c9d70(p3fes::EEContext&);
void fn_sub_4C9DB0_004c9db0(p3fes::EEContext&);
void fn_sub_4CB750_004cb750(p3fes::EEContext&);
void fn_sub_4CB890_004cb890(p3fes::EEContext&);
void fn_cosf_0052e6d8(p3fes::EEContext&);
void fn_sinf_0052e878(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {
namespace battle_result {
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
constexpr u64 dsll32(u64 a, unsigned n) { return core::dsll32(a, n); }
constexpr u64 dsra32(u64 a, unsigned n) { return core::dsra32(a, n); }
constexpr u64 slt(u64 a, u64 b) { return core::slt(a, b); }
constexpr u64 sltu(u64 a, u64 b) { return core::sltu(a, b); }
constexpr u64 slti(u64 a, s32 i) { return core::slti(a, i); }
constexpr u64 sltiu(u64 a, s32 i) { return core::sltiu(a, i); }
// The branch tests on whole 64-bit registers (bltz / blez).
constexpr bool ltz(u64 a) { return static_cast<s64>(a) < 0; }
constexpr bool lez(u64 a) { return static_cast<s64>(a) <= 0; }

// One GPR of the guest context (a 64-bit write keeps bits 64..127, as the EE does; lq writes all 128).
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

// The guest machine as the bodies see it: one named variable per register, the memory and FPU operations with the
// runtime's own semantics, the calls with the original links.
class Cpu {
public:
    explicit Cpu(EEContext& ctx) noexcept : c(ctx) {}

    EEContext& c;
    Gpr zero{c, 0}, at{c, 1}, v0{c, 2}, v1{c, 3}, a0{c, 4}, a1{c, 5}, a2{c, 6}, a3{c, 7};
    Gpr t0{c, 8}, t1{c, 9}, t2{c, 10}, t3{c, 11}, t4{c, 12}, t5{c, 13}, t6{c, 14}, t7{c, 15};
    Gpr s0{c, 16}, s1{c, 17}, s2{c, 18}, s3{c, 19}, s4{c, 20}, s5{c, 21}, s6{c, 22}, s7{c, 23};
    Gpr t8{c, 24}, t9{c, 25}, gp{c, 28}, sp{c, 29}, fp{c, 30}, ra{c, 31};

    // virtual time (ADR-0013); a check point may raise a fatal event that unwinds through the body
    void enter(u64 n) { guest::enter(c, n); }
    void charge(u64 n) noexcept { guest::charge(c, n); }
    void backedge() { guest::backedge(c); }

    // Loads and stores in the instruction's own form, `lw(rt, base, imm)` = `lw rt, imm(base)`, with the runtime's
    // semantics: the RAM / scratchpad / BIOS windows, the hardware bus, and the address-error / unmapped faults of
    // the recompiled body (a bad pointer stops both versions at the same instruction with the same registers).
    void lw(Gpr& d, const Gpr& b, s32 i) { rt::lw(c, d.r, b.r, i); }
    void lwu(Gpr& d, const Gpr& b, s32 i) { rt::lwu(c, d.r, b.r, i); }
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
    void madd_s(unsigned d, unsigned s, unsigned t) noexcept { rt::madd_s(c, d, s, t); }
    void c_eq_s(unsigned s, unsigned t) noexcept { rt::c_eq_s(c, s, t); }
    void c_lt_s(unsigned s, unsigned t) noexcept { rt::c_lt_s(c, s, t); }
    void c_le_s(unsigned s, unsigned t) noexcept { rt::c_le_s(c, s, t); }
    bool cop1_cond() const noexcept { return rt::cop1_cond(c); }

    // HI/LO
    void mult(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::mult(c, d.r, s.r, t.r); }
    void divu(const Gpr& s, const Gpr& t) noexcept { rt::divu(c, s.r, t.r); }
    void mfhi(Gpr& d) noexcept { rt::mfhi(c, d.r); }

    // `jal fn` at pc ($ra = pc + 8; the delay slot's instruction is written before the call)
    void jal(u32 pc, rt::Fn fn) {
        rt::jal(c, pc);
        fn(c);
    }
    // K_Assert(file, line) (sub_19D3F0, `jr $ra` in retail): $a0 = the source file name, $a1 = the line.
    void kassert(u32 pc, u32 file, u32 line) {
        a0 = lui((file + 0x8000u) >> 16);
        a0 = addiu(a0, static_cast<s16>(file & 0xFFFFu));
        a1 = line;
        jal(pc, gen::fn_sub_19D3F0_0019d3f0);
    }
    // --- the bodies (battle_result.h documents each) ---
    void sub_1F08C0();
    void sub_1F0900();
    void sub_1F0940();
    void sub_1F0970();
    void sub_1F0A60();
    void sub_1F0AB0();
    void sub_1F0C40();
    void sub_1F0D70();
    void sub_1F0EB0();
    void sub_1F0F40();
    void sub_1F0FD0();
    void sub_1F0FF0();
    void sub_1F10B0();
    void sub_1F10F0();
    void sub_1F1140();
    void sub_1F1210();
    void sub_1F1240();
    void sub_1F1AA0();
    void sub_1F1AE0();
    void sub_1F1B00();
    void sub_1F1B20();
    void sub_1F1B40();
    void sub_1F1B60();
    void sub_1F1C20();
    void sub_1F1C50();
    void sub_1F1C90();
    void sub_1F1DF0();
    void sub_1F1E90();
    void sub_1F1F40();
    void sub_1F9D70();
    void sub_1FA0D0();
    void sub_1FA4F0();
    void sub_1FAEA0();
    void sub_1FB130();
    void sub_1FB1B0();
    void sub_1FB1F0();
    void sub_1FB3F0();
    void sub_1FB4B0();
    void sub_1FBD50();
    void sub_1FBDF0();
    void sub_1FBFA0();
    void sub_1FC1F0();
    void sub_1FC230();
    void sub_1FC3C0();
    void sub_1FC590();
    void sub_2338D0();
    void sub_2338F0();
    void sub_233910();
    void sub_233930();
    void sub_233950();
    void sub_233960();
    void sub_233970();
    void sub_233AD0();
    void sub_233BB0();
    void sub_233D20();
    void sub_233D70();
    void sub_233DF0();
    void sub_234570();
    void sub_2345D0();
    void sub_234630();
    void sub_234690();
    void sub_2347E0();
    void sub_234820();
    void sub_234960();
    void sub_234A00();
    void sub_235010();
    void sub_2361D0();
    void sub_236280();
    void sub_2362E0();
    void sub_236340();
    void bpIfontSetDigitQuad();
    void sub_239140();
    void sub_24A870();
    void sub_24AA90();
    void sub_24AB10();
    void sub_24ABD0();
    void sub_24AC40();
    void sub_24ADF0();
    void sub_24B8A0();
    void sub_24B9E0();
    void sub_24BA30();
    void sub_24BED0();
    void sub_24BF20();
    void sub_24C040();
    void sub_24C090();
    void sub_24C100();
    void sub_24C110();
    void sub_24CF00();
    void sub_24D0C0();
};

// gp-relative globals of the result screen (`lw rX, off(gp)`).
constexpr s32 kGpExpRows = -18504;  // the experience rows (28-byte records, +0 bit 7: flat experience)
constexpr s32 kGpLevelGapScale = -18516;  // the level-gap scale table (21 singles, gap -10..+10)
constexpr s32 kGpEquipTable10 = -18568;  // member 10
constexpr s32 kGpEquipTable9 = -18572;  // member 9
constexpr s32 kGpEquipTable8 = -18576;  // member 8
constexpr s32 kGpEquipTable7 = -18580;  // member 7
constexpr s32 kGpEquipTable5 = -18584;  // member 5
constexpr s32 kGpEquipTable4 = -18588;  // member 4
constexpr s32 kGpEquipTable3 = -18592;  // member 3
// the equipment rows of party member 2 (10-byte rows {u8 level, pad, u16 item x 4}, the first one the default
// equipment; ended by a row of four zero items; members 3..5 and 7..10 follow)
constexpr s32 kGpEquipTable2 = -18596;
// the level band table walked by sub_1FBD50 (4-byte rows {u8 lo, u8 hi, u16}, a zero row ends it)
constexpr s32 kGpLevelBands = -18600;
constexpr s32 kGpSpecialSkillRows = -18624;  // the special personas' skill rows (622 B each, from id 192)
constexpr s32 kGpPersonaSkillRows = -18632;  // the persona skill rows (70-byte records)
constexpr s32 kGpPersonaLevels = -18640;  // the persona base levels (14-byte records, +3 the base level)
constexpr s32 kGpBai = -18872;  // the AI-tactics panel work (bai_main.c)
constexpr s32 kGpBrpRes = -18876;  // the persona-birth resource record (brp_res.c)
constexpr s32 kGpBrpBirth = -18880;  // the persona-birth work (brp_birth.c)
constexpr s32 kGpBrPanel = -18912;  // the result panel record (br_panel.c)
constexpr s32 kGpBrRes = -18916;  // the result resource record (br_res.c)
constexpr s32 kGpResult = -18968;  // the "battle result" root's work (br_root.c; sub_1F1C50 returns it)
constexpr s32 kGpScale2 = -31820;  // the experience scale of mode 2 (a single)
constexpr s32 kGpScale1 = -31824;  // the experience scale of mode 1 (a single)
constexpr s32 kGpScale4 = -32656;  // the experience scale of mode 4 (a single)
// The K_Assert file names (.rodata).
constexpr u32 kBrRootC = 0x684578;
constexpr u32 kBrFriendC = 0x684BA8;
constexpr u32 kBrDataC = 0x684C28;
constexpr u32 kBrResC = 0x68E6A0;
constexpr u32 kBrPanelC = 0x68E790;
constexpr u32 kBrpBirthC = 0x68E8E8;
constexpr u32 kBrpResC = 0x68E928;
constexpr u32 kBaiMainC = 0x68E980;

// =================================================================================================================
// br_root.c: the "battle result" root task's draw updates and page steps (work = task +60 = gp-18968)
// =================================================================================================================

// sub_1F08C0 [battle result draw 2]: update of a "battle result draw" task. When the root's flag word has 0x400000 (the
// level-up page is up, sub_1F1E90), draws the result panel (sub_2350F0); returns 0.
void Cpu::sub_1F08C0() {
    enter(8);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    lw(v0, a0, 60);
    lw(v1, v0, 0);
    v0 = lui(0x40);
    v0 = v1 & v0;
    if (v0 != 0) {
        charge(2);
        jal(0x1F08E0, gen::fn_sub_2350F0_002350f0);
    }
    charge(5);
    v0 = 0;
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_1F0900 [battle result draw 3]: the same panel draw (sub_2350F0) for the other case, flag 0x400000 clear -- the
// two draw tasks run at different priorities, so the panel is drawn above or below the level-up page; returns 0.
void Cpu::sub_1F0900() {
    enter(9);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    lw(v0, a0, 60);
    lw(v0, v0, 0);
    v1 = ~v0;
    v0 = lui(0x40);
    v0 = v1 & v0;
    if (v0 != 0) {
        charge(2);
        jal(0x1F0924, gen::fn_sub_2350F0_002350f0);
    }
    charge(5);
    v0 = 0;
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_1F0940 [battle result draw 4]: the result pages' two draws, sub_278550 then sub_275CB0; returns 0.
void Cpu::sub_1F0940() {
    enter(11);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    jal(0x1F0948, gen::fn_sub_278550_00278550);
    jal(0x1F0950, gen::fn_sub_275CB0_00275cb0);
    v0 = 0;
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_1F0970: forwards to sub_1F0990 (the root's shutdown: message windows, the persona-status screen, the result
// resources, the heap; kept recompiled).
void Cpu::sub_1F0970() {
    enter(8);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    jal(0x1F0978, gen::fn_sub_1F0990_001f0990);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_1F0A60: ends the shuffle-time hand-off: destroys the task at work +148 (sub_1F30D0), clears flag 0x8000 and +148.
void Cpu::sub_1F0A60() {
    enter(18);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    lw(s0, a0, 60);
    lw(a0, s0, 148);
    jal(0x1F0A74, gen::fn_sub_1F30D0_001f30d0);
    lw(a0, s0, 0);
    v1 = lui(0xFFFF);
    v1 = v1 | 0x7FFF;
    v1 = a0 & v1;
    sw(v1, s0, 0);
    sw(zero, s0, 148);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
    return;
}

// sub_1F0AB0: back to page 7 -- work +40 = 0, state +12 = 7.
void Cpu::sub_1F0AB0() {
    enter(6);
    lw(a0, a0, 60);
    sw(zero, a0, 40);
    v1 = 7;
    sw(v1, a0, 12);
    return;
}

// sub_1F0C40 [apply the spoils]: for each of the work's dropped items (+152, 8-byte records {u16 item, s32 count at
// +4}, +176 of them): a special item (sub_171360) goes to sub_171390; any other is added to the stock, stock(1, item) =
// min(stock + count, 99) (sub_170760 / sub_170860). Then every id of the +240 list (u16, +264 of them) goes to
// sub_174E20. Clears flag 0x1 and sets state 13.
void Cpu::sub_1F0C40() {
    enter(10);
    sp = addiu(sp, -80);
    sd(ra, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    lw(s1, a0, 60);
    s2 = 0;
    goto L_001f0ce8;
L_001f0c68:
    charge(8);
    v0 = sll(s2, 3);
    v0 = addu(s1, v0);
    s0 = addiu(v0, 152);
    lhu(a0, v0, 152);
    jal(0x1F0C78, gen::fn_sub_171360_00171360);
    if (v0 != 0) {
        charge(5);
        lhu(a0, s0, 0);
        jal(0x1F0C8C, gen::fn_sub_171390_00171390);
        goto L_001f0ce4;
    }
    charge(12);
    v0 = sll(s2, 3);
    s3 = addu(s1, v0);
    lh(a1, s0, 0);
    a0 = 1;
    jal(0x1F0CAC, gen::fn_sub_170760_00170760);
    v1 = v0 & 0xFFFF;
    lw(v0, s3, 156);
    v0 = addu(v1, v0);
    at = slti(v0, 100);
    if (at == 0) {
        charge(1);
        v0 = 99;
    }
    charge(5);
    lh(a1, s0, 0);
    a2 = v0 & 0xFFFF;
    a0 = 1;
    jal(0x1F0CDC, gen::fn_sub_170860_00170860);
L_001f0ce4:
    charge(1);
    s2 = addiu(s2, 1);
L_001f0ce8:
    charge(4);
    lw(v1, s1, 176);
    v1 = slt(s2, v1);
    if (v1 != 0) {
        backedge();
        goto L_001f0c68;
    }
    charge(3);
    s0 = 0;
    for (;;) {
        charge(4);
        lw(v1, s1, 264);
        v1 = slt(s0, v1);
        if (v1 == 0) {
            break;
        }
        backedge();
        charge(6);
        v0 = sll(s0, 1);
        v0 = addu(s1, v0);
        lhu(a0, v0, 240);
        jal(0x1F0D10, gen::fn_sub_174E20_00174e20);
        s0 = addiu(s0, 1);
    }
    charge(14);
    lw(a0, s1, 0);
    v1 = si(-2);
    v1 = a0 & v1;
    sw(v1, s1, 0);
    v1 = 13;
    sw(v1, s1, 12);
    ld(ra, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 80);
    return;
}

// sub_1F0D70 [next page]: from the state word +12 the first page whose flag is set, in the order 7 (flag 0x4, level-up:
// sub_1F1E90), 9 (0x8, sub_1F0F40), 8 (0x20, sub_1F1140), 12 (spoils, sub_1F0C40). Any other state K_Asserts (line
// 1410) and retries the same state -- a retail endless loop, kept.
void Cpu::sub_1F0D70() {
    enter(8);
    sp = addiu(sp, -64);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s2 = a0;
    lw(s0, a0, 60);
    lw(s1, s0, 12);
L_001f0d90:
    charge(3);
    v1 = 12;
    if (s1 != v1) {
        charge(3);
        a0 = 8;
        if (s1 != a0) {
            charge(3);
            v1 = 9;
            if (s1 != v1) {
                charge(3);
                v0 = 7;
                if (s1 != v0) {
                    charge(2);
                    goto L_001f0e6c;
                }
                charge(4);
                lw(v0, s0, 0);
                v0 = v0 & 0x4;
                if (v0 != 0) {
                    charge(5);
                    a0 = s2;
                    jal(0x1F0DDC, gen::fn_sub_1F1E90_001f1e90);
                    goto L_001f0e88;
                }
                charge(3);
                s1 = v1;
                backedge();
                goto L_001f0d90;
            }
            charge(4);
            lw(v0, s0, 0);
            v0 = v0 & 0x8;
            if (v0 != 0) {
                charge(5);
                a0 = s2;
                jal(0x1F0E0C, gen::fn_sub_1F0F40_001f0f40);
                goto L_001f0e88;
            }
            charge(3);
            s1 = a0;
            backedge();
            goto L_001f0d90;
        }
        charge(4);
        lw(v0, s0, 0);
        v0 = v0 & 0x20;
        if (v0 != 0) {
            charge(5);
            a0 = s2;
            jal(0x1F0E3C, gen::fn_sub_1F1140_001f1140);
            goto L_001f0e88;
        }
        charge(3);
        s1 = v1;
        backedge();
        goto L_001f0d90;
    }
    charge(5);
    a0 = s2;
    jal(0x1F0E5C, gen::fn_sub_1F0C40_001f0c40);
    goto L_001f0e88;
L_001f0e6c:
    charge(7);
    kassert(0x1F0E78, kBrRootC, 1410);
    backedge();
    goto L_001f0d90;
L_001f0e88:
    charge(7);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
    return;
}

// sub_1F0EB0: hands each id of the work's +320 list (u16, +336 of them) to sub_176840 with persona =
// datPersonaGetByPcId(6), then clears flag 0x400000.
void Cpu::sub_1F0EB0() {
    enter(13);
    sp = addiu(sp, -64);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    lw(s0, a0, 60);
    a0 = 6;
    jal(0x1F0ECC, gen::fn_datPersonaGetByPcId_00174800);
    s1 = v0;
    s2 = 0;
    for (;;) {
        charge(4);
        lw(v1, s0, 336);
        v1 = slt(s2, v1);
        if (v1 == 0) {
            break;
        }
        backedge();
        charge(7);
        v0 = sll(s2, 1);
        v0 = addu(s0, v0);
        a0 = s1;
        lhu(a1, v0, 320);
        jal(0x1F0EF4, gen::fn_sub_176840_00176840);
        s2 = addiu(s2, 1);
    }
    charge(12);
    lw(a0, s0, 0);
    v1 = lui(0xFFBF);
    v1 = v1 | 0xFFFF;
    v1 = a0 & v1;
    sw(v1, s0, 0);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
    return;
}

// sub_1F0F40 [page 9]: until the level resources are loaded (+8 bit 2) requests them once (K_Assert on +4 bit 2 already
// set; sub_233B20 loads battle/result/br_level.bin; +4 |= 4; +16 = 0); once loaded starts the level-up page
// (sub_1F0FF0). State 8 either way.
void Cpu::sub_1F0F40() {
    enter(9);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    lw(s0, a0, 60);
    lw(v0, s0, 8);
    v0 = ~v0;
    v0 = v0 & 0x4;
    if (v0 != 0) {
        charge(5);
        lw(v0, s0, 4);
        v0 = ~v0;
        v0 = v0 & 0x4;
        if (v0 == 0) {
            charge(5);
            kassert(0x1F0F84, kBrRootC, 1439);
        }
        charge(8);
        jal(0x1F0F8C, gen::fn_sub_233B20_00233b20);
        lw(v1, s0, 4);
        v1 = v1 | 0x4;
        sw(v1, s0, 4);
        sw(zero, s0, 16);
        goto L_001f0fb4;
    }
    charge(2);
    jal(0x1F0FAC, gen::fn_sub_1F0FF0_001f0ff0);
L_001f0fb4:
    charge(7);
    v1 = 8;
    sw(v1, s0, 12);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
    return;
}

// sub_1F0FD0: forwards to sub_2630E0.
void Cpu::sub_1F0FD0() {
    enter(8);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    jal(0x1F0FD8, gen::fn_sub_2630E0_002630e0);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_1F0FF0 [start the level-up page]: opens the message window (sub_3C7C20(0, level of member 1, 0), msgWinRequestMessage(2)),
// closes the panel (sub_2362E0), clears flags 0x200000 / 0x80000, runs sub_262790 and sub_275A90, sets flag 0x100000,
// plays SOUND2\EVENT\EVE_530.ADX (sub_10A370(3, name)) and sets +16 = 1.
void Cpu::sub_1F0FF0() {
    enter(48);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    jal(0x1F0FFC, gen::fn_sub_1F1C50_001f1c50);
    s0 = v0;
    a0 = 1;
    jal(0x1F100C, gen::fn_sub_16C470_0016c470);
    a1 = v0 & 0xFF;
    a0 = 0;
    a2 = 0;
    jal(0x1F1020, gen::fn_sub_3C7C20_003c7c20);
    a0 = 2;
    jal(0x1F102C, gen::fn_msgWinRequestMessage_003c7430);
    jal(0x1F1034, gen::fn_sub_2362E0_002362e0);
    lw(v1, s0, 0);
    v0 = lui(0xFFDF);
    v0 = v0 | 0xFFFF;
    v1 = v1 & v0;
    sw(v1, s0, 0);
    v0 = lui(0xFFF7);
    v0 = v0 | 0xFFFF;
    v0 = v1 & v0;
    sw(v0, s0, 0);
    jal(0x1F1060, gen::fn_sub_262790_00262790);
    jal(0x1F1068, gen::fn_sub_275A90_00275a90);
    lw(v1, s0, 0);
    v0 = lui(0x10);
    v0 = v1 | v0;
    sw(v0, s0, 0);
    a0 = 3;
    a1 = lui(0x68);
    a1 = addiu(a1, 17824);
    jal(0x1F108C, gen::fn_sub_10A370_0010a370);
    v1 = 1;
    sw(v1, s0, 16);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
    return;
}

// sub_1F10B0: msgWinRequestMessage(3) and +16 = 2 on the root's work.
void Cpu::sub_1F10B0() {
    enter(16);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    jal(0x1F10BC, gen::fn_sub_1F1C50_001f1c50);
    s0 = v0;
    a0 = 3;
    jal(0x1F10CC, gen::fn_msgWinRequestMessage_003c7430);
    v1 = 2;
    sw(v1, s0, 16);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
    return;
}

// sub_1F10F0: sub_108570(), sub_108670(2) and +16 = 4 on the root's work.
void Cpu::sub_1F10F0() {
    enter(18);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    jal(0x1F10FC, gen::fn_sub_1F1C50_001f1c50);
    s0 = v0;
    jal(0x1F1108, gen::fn_sub_108570_00108570);
    a0 = 2;
    jal(0x1F1114, gen::fn_sub_108670_00108670);
    v1 = 4;
    sw(v1, s0, 16);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
    return;
}

// sub_1F1140 [page 8]: as sub_1F0F40 with +20: requests the level resources once, else resets +196, opens the message
// window on the name of the +212 list's first id (sub_173220 -> sub_3C7BC0(0, name), msgWinRequestMessage(1)) and sets +20 = 1.
// State 12 either way.
void Cpu::sub_1F1140() {
    enter(9);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    lw(s0, a0, 60);
    lw(v0, s0, 8);
    v0 = ~v0;
    v0 = v0 & 0x4;
    if (v0 != 0) {
        charge(5);
        lw(v0, s0, 4);
        v0 = ~v0;
        v0 = v0 & 0x4;
        if (v0 == 0) {
            charge(5);
            kassert(0x1F1184, kBrRootC, 1509);
        }
        charge(8);
        jal(0x1F118C, gen::fn_sub_233B20_00233b20);
        lw(v1, s0, 4);
        v1 = v1 | 0x4;
        sw(v1, s0, 4);
        sw(zero, s0, 20);
        goto L_001f11ec;
    }
    charge(16);
    sw(zero, s0, 196);
    v0 = 0;
    v0 = sll(v0, 1);
    v0 = addu(v0, s0);
    lhu(a0, v0, 212);
    jal(0x1F11C0, gen::fn_sub_173220_00173220);
    a0 = 0;
    a1 = v0;
    jal(0x1F11D0, gen::fn_sub_3C7BC0_003c7bc0);
    a0 = 1;
    jal(0x1F11DC, gen::fn_msgWinRequestMessage_003c7430);
    v1 = 1;
    sw(v1, s0, 20);
L_001f11ec:
    charge(7);
    v1 = 12;
    sw(v1, s0, 12);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
    return;
}

// sub_1F1210: sub_264F90() then msgWinClose(1).
void Cpu::sub_1F1210() {
    enter(11);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    jal(0x1F1218, gen::fn_sub_264F90_00264f90);
    a0 = 1;
    jal(0x1F1224, gen::fn_msgWinClose_003c7650);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_1F1240 [the experience gauge]: the ratio +184 = +180 / +284 (flag 0x2 clear) or +180 * +10844 / 100 / +284 (set),
// as EE singles -- 0 stays 0, below 1.0 becomes 1, else the truncated value; then +10836 = +304, +10832 =
// sub_1FBDF0(level of member 1, +10836, +184, +10840, +284), sub_1F13B0 (the printf report, kept) and flag 0x20000.
void Cpu::sub_1F1240() {
    enter(12);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    lw(s0, a0, 60);
    lw(v0, s0, 0);
    v1 = ~v0;
    v0 = lui(0x2);
    v0 = v1 & v0;
    if (v0 == 0) {
        charge(5);
        kassert(0x1F127C, kBrRootC, 1539);
    }
    charge(5);
    lw(v0, s0, 0);
    v0 = ~v0;
    v0 = v0 & 0x2;
    if (v0 != 0) {
        charge(10);
        lwc1(F0, s0, 180);
        cvt_s_w(F1, F0);
        lwc1(F0, s0, 284);
        cvt_s_w(F0, F0);
        div_s(F1, F1, F0);
        goto L_001f12f0;
    }
    charge(12);
    lwc1(F0, s0, 180);
    cvt_s_w(F1, F0);
    lwc1(F0, s0, 10844);
    cvt_s_w(F0, F0);
    mul_s(F1, F1, F0);
    v0 = lui(0x42C8);
    mtc1(v0, F0);
    div_s(F1, F1, F0);
    lwc1(F0, s0, 284);
    cvt_s_w(F0, F0);
    div_s(F1, F1, F0);
L_001f12f0:
    charge(5);
    mtc1(zero, F0);
    c_eq_s(F0, F1);
    if (cop1_cond()) {
        charge(3);
        sw(zero, s0, 184);
        goto L_001f1348;
    }
    charge(6);
    v0 = lui(0x3F80);
    mtc1(v0, F0);
    c_lt_s(F1, F0);
    if (cop1_cond()) {
        charge(4);
        v0 = 1;
        sw(v0, s0, 184);
        goto L_001f1348;
    }
    charge(4);
    cvt_w_s(F0, F1);
    mfc1(v0, F0);
    sw(v0, s0, 184);
L_001f1348:
    charge(26);
    lw(v0, s0, 304);
    sw(v0, s0, 10836);
    a0 = 1;
    jal(0x1F1354, gen::fn_sub_16C470_0016c470);
    a0 = v0 & 0xFF;
    lw(a1, s0, 10836);
    lw(a2, s0, 184);
    lw(a3, s0, 10840);
    lw(t0, s0, 284);
    jal(0x1F1370, gen::fn_sub_1FBDF0_001fbdf0);
    sw(v0, s0, 10832);
    a0 = s1;
    jal(0x1F1380, gen::fn_sub_1F13B0_001f13b0);
    lw(a0, s0, 0);
    v1 = lui(0x2);
    v1 = a0 | v1;
    sw(v1, s0, 0);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
    return;
}

// sub_1F1AA0: sub_1F9800(work +240, work +264) and +10844 = sub_1F9890().
void Cpu::sub_1F1AA0() {
    enter(16);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    lw(s0, a0, 60);
    a0 = addiu(s0, 240);
    a1 = addiu(s0, 264);
    jal(0x1F1AB8, gen::fn_sub_1F9800_001f9800);
    jal(0x1F1AC0, gen::fn_sub_1F9890_001f9890);
    sw(v0, s0, 10844);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
    return;
}

// sub_1F1AE0: forwards to brRoot_CreateBattleResultTasks (creates the "battle result" task and its draw tasks; kept, heap).
void Cpu::sub_1F1AE0() {
    enter(8);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    jal(0x1F1AE8, gen::fn_brRoot_CreateBattleResultTasks_001ef500);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_1F1B00: the root's flag 0x1 (the result screen has finished).
void Cpu::sub_1F1B00() {
    enter(5);
    lw(v0, a0, 60);
    lw(v0, v0, 0);
    v0 = v0 & 0x1;
    return;
}

// sub_1F1B20: sets flag 0x2000.
void Cpu::sub_1F1B20() {
    enter(6);
    lw(a0, a0, 60);
    lw(v1, a0, 0);
    v1 = v1 | 0x2000;
    sw(v1, a0, 0);
    return;
}

// sub_1F1B40: the flag 0x2000.
void Cpu::sub_1F1B40() {
    enter(5);
    lw(v0, a0, 60);
    lw(v0, v0, 0);
    v0 = v0 & 0x2000;
    return;
}

// sub_1F1B60 [leave state 2]: K_Asserts state 2; with flag 0x2 starts the shuffle hand-off (sub_1F30F0(+148),
// sub_2339D0 loads br_base.bin, flag 0x8000, state 3), else +40 = 0 and state 7; then flags 0x40 and 0x1.
void Cpu::sub_1F1B60() {
    enter(10);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    lw(s0, a0, 60);
    lw(a0, s0, 12);
    v1 = 2;
    if (a0 != v1) {
        charge(5);
        kassert(0x1F1B94, kBrRootC, 1310);
    }
    charge(4);
    lw(v1, s0, 0);
    v1 = v1 & 0x2;
    if (v1 != 0) {
        charge(13);
        lw(s1, s1, 60);
        lw(a0, s1, 148);
        jal(0x1F1BB4, gen::fn_sub_1F30F0_001f30f0);
        jal(0x1F1BBC, gen::fn_sub_2339D0_002339d0);
        lw(v1, s1, 0);
        v1 = v1 | 0x8000;
        sw(v1, s1, 0);
        v1 = 3;
        sw(v1, s1, 12);
        goto L_001f1bf0;
    }
    charge(4);
    lw(a0, s1, 60);
    sw(zero, a0, 40);
    v1 = 7;
    sw(v1, a0, 12);
L_001f1bf0:
    charge(11);
    lw(v1, s0, 0);
    v1 = v1 | 0x40;
    sw(v1, s0, 0);
    v1 = v1 | 0x1;
    sw(v1, s0, 0);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
    return;
}

// sub_1F1C20 [destroy the result root]: clears gp-18968 and destroys the task with its children
// (kwlnTaskDestroyWithHierarchy).
void Cpu::sub_1F1C20() {
    enter(9);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    sw(zero, gp, kGpResult);
    jal(0x1F1C2C, gen::fn_kwlnTaskDestroyWithHierarchy_00195020);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_1F1C50 [the result work]: gp-18968 (K_Assert when 0, line 1877).
void Cpu::sub_1F1C50() {
    enter(5);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    lw(v0, gp, kGpResult);
    if (v0 == 0) {
        charge(5);
        kassert(0x1F1C70, kBrRootC, 1877);
    }
    charge(5);
    lw(v0, gp, kGpResult);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_1F1C90 [open the spoils panel]: sub_1F1240, then builds the panel's input record in its frame (sp + 64: flag word
// bit 0 = +10844 > 100, +40 the item count, +44 the experience result +10832, and per item {+4 special, +8 id, +12
// count} from +152), loads br_lvh.bin when flag 0x2 is clear and 0x8 set (sub_233C00), hands the record to sub_234A00,
// opens the panel (sub_236280) and sets flag 0x200000.
void Cpu::sub_1F1C90() {
    enter(17);
    sp = addiu(sp, -112);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    lw(s1, a0, 60);
    jal(0x1F1CA8, gen::fn_sub_1F1240_001f1240);
    sw(zero, sp, 64);
    lw(v0, s1, 10832);
    sw(v0, sp, 108);
    lw(v0, s1, 176);
    sw(v0, sp, 104);
    lw(v0, s1, 10844);
    at = slti(v0, 101);
    if (at == 0) {
        charge(3);
        v0 = 0;
        v0 = v0 | 0x1;
        sw(v0, sp, 64);
    }
    charge(3);
    s2 = 0;
    goto L_001f1d78;
L_001f1cec:
    charge(8);
    v0 = sll(s2, 3);
    v0 = addu(s1, v0);
    s0 = addiu(v0, 152);
    lhu(a0, v0, 152);
    jal(0x1F1CFC, gen::fn_sub_171360_00171360);
    if (v0 == 0) {
        charge(8);
        v0 = sll(s2, 1);
        v0 = addu(v0, s2);
        v0 = sll(v0, 2);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 64);
        sw(zero, v0, 4);
        goto L_001f1d48;
    }
    charge(7);
    v0 = sll(s2, 1);
    v0 = addu(v0, s2);
    v0 = sll(v0, 2);
    v0 = addu(v0, sp);
    v1 = addiu(v0, 64);
    v0 = 1;
    sw(v0, v1, 4);
L_001f1d48:
    charge(12);
    v0 = sll(s2, 3);
    a0 = addu(s1, v0);
    v0 = sll(s2, 1);
    v0 = addu(v0, s2);
    v0 = sll(v0, 2);
    v0 = addu(v0, sp);
    v1 = addiu(v0, 64);
    lhu(v0, s0, 0);
    sw(v0, v1, 8);
    lw(v0, a0, 156);
    sw(v0, v1, 12);
    s2 = addiu(s2, 1);
L_001f1d78:
    charge(4);
    lw(v0, s1, 176);
    v0 = slt(s2, v0);
    if (v0 != 0) {
        backedge();
        goto L_001f1cec;
    }
    charge(4);
    lw(v1, s1, 0);
    v0 = v1 & 0x2;
    if (v0 != 0) goto L_001f1dac;
    charge(3);
    v0 = v1 & 0x8;
    if (v0 == 0) goto L_001f1dac;
    charge(2);
    jal(0x1F1DA4, gen::fn_sub_233C00_00233c00);
L_001f1dac:
    charge(16);
    a0 = addiu(sp, 64);
    jal(0x1F1DB0, gen::fn_sub_234A00_00234a00);
    jal(0x1F1DB8, gen::fn_sub_236280_00236280);
    lw(a0, s1, 0);
    v1 = lui(0x20);
    v1 = a0 | v1;
    sw(v1, s1, 0);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 112);
    return;
}

// sub_1F1DF0: out_ids[0] = 1, out_ids[1 + i] = the root's +268 list (u16, +276 of them), *out_count = +276 + 1.
void Cpu::sub_1F1DF0() {
    enter(9);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    s0 = a1;
    lw(v1, gp, kGpResult);
    if (v1 == 0) {
        charge(5);
        kassert(0x1F1E20, kBrRootC, 1877);
    }
    charge(6);
    lw(a2, gp, kGpResult);
    v1 = 1;
    sh(v1, s1, 0);
    a3 = 0;
    for (;;) {
        charge(4);
        lw(a0, a2, 276);
        v1 = slt(a3, a0);
        if (v1 == 0) {
            break;
        }
        backedge();
        charge(6);
        a1 = sll(a3, 1);
        v1 = addu(a2, a1);
        lhu(a0, v1, 268);
        v1 = addu(s1, a1);
        sh(a0, v1, 2);
        a3 = addiu(a3, 1);
    }
    charge(8);
    v1 = addiu(a0, 1);
    sw(v1, s0, 0);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
    return;
}

// sub_1F1E90 [page 7, level-up]: K_Asserts +4 / +8 bit 2 clear, requests the level resources (sub_233B20), flag
// 0x400000, +4 |= 4, +56 = 0, state 9.
void Cpu::sub_1F1E90() {
    enter(9);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    lw(s0, a0, 60);
    lw(v0, s0, 4);
    v0 = ~v0;
    v0 = v0 & 0x4;
    if (v0 == 0) {
        charge(5);
        kassert(0x1F1EC0, kBrRootC, 1948);
    }
    charge(5);
    lw(v0, s0, 8);
    v0 = ~v0;
    v0 = v0 & 0x4;
    if (v0 == 0) {
        charge(5);
        kassert(0x1F1EE8, kBrRootC, 1949);
    }
    charge(17);
    jal(0x1F1EF0, gen::fn_sub_233B20_00233b20);
    lw(a0, s0, 0);
    v1 = lui(0x40);
    v1 = a0 | v1;
    sw(v1, s0, 0);
    lw(v1, s0, 4);
    v1 = v1 | 0x4;
    sw(v1, s0, 4);
    sw(zero, s0, 56);
    v1 = 9;
    sw(v1, s0, 12);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
    return;
}

// sub_1F1F40 [may the result end?]: with the shuffle hand-off running (flag 0x8000 and a task at +148) its answer
// (sub_1F5810 == 1); otherwise 1 when flag 0x20000 is set and none of 0x2C, else 0.
void Cpu::sub_1F1F40() {
    enter(6);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    lw(v0, gp, kGpResult);
    if (v0 == 0) {
        charge(5);
        kassert(0x1F1F64, kBrRootC, 1877);
    }
    charge(3);
    lw(s0, gp, kGpResult);
    if (s0 == 0) {
        charge(5);
        kassert(0x1F1F84, kBrRootC, 1877);
    }
    charge(5);
    lw(v1, gp, kGpResult);
    lw(v0, v1, 0);
    v0 = v0 & 0x8000;
    if (v0 == 0) {
        charge(3);
        a0 = 0;
        goto L_001f1fc8;
    }
    charge(3);
    lw(v0, v1, 148);
    if (v0 == 0) {
        charge(3);
        a0 = 0;
        goto L_001f1fc8;
    }
    charge(1);
    a0 = 1;
L_001f1fc8:
    charge(3);
    v0 = 1;
    if (a0 != v0) goto L_001f2040;
    charge(2);
    if (v1 == 0) {
        charge(5);
        kassert(0x1F1FE8, kBrRootC, 1877);
    }
    charge(5);
    lw(v1, gp, kGpResult);
    lw(v0, v1, 0);
    v0 = v0 & 0x8000;
    if (v0 == 0) {
        charge(3);
        v0 = 1;
        goto L_001f2030;
    }
    charge(3);
    lw(a0, v1, 148);
    if (a0 == 0) {
        charge(3);
        v0 = 1;
        goto L_001f2030;
    }
    charge(2);
    jal(0x1F2028, gen::fn_sub_1F5810_001f5810);
L_001f2030:
    charge(4);
    v0 = v0 ^ 0x1;
    v0 = sltiu(v0, 1);
    goto L_001f206c;
L_001f2040:
    charge(5);
    lw(v1, s0, 0);
    v0 = lui(0x2);
    v0 = v1 & v0;
    if (v0 != 0) {
        charge(5);
        v0 = v1 & 0x2C;
        v0 = sltu(zero, v0);
        v0 = v0 ^ 0x1;
        goto L_001f206c;
    }
    charge(1);
    v0 = 0;
L_001f206c:
    charge(5);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
    return;
}

// =================================================================================================================
// br_friend.c: the party members' rewards -- flags, default and best equipment, the persona evolution (COMM 0x171)
// =================================================================================================================

// sub_1F9D70 [the member's flag]: datSetFlag(4625..4633, 1) for party members 2..5 and 7..10 (jump table 0x7B70E0);
// members 0, 1, 6 and any other K_Assert (br_friend.c line 73).
void Cpu::sub_1F9D70() {
    enter(6);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    v0 = a0 & 0xFFFF;
    at = sltiu(v0, 11);
    if (at == 0) goto L_001f9e64;
    charge(7);
    v1 = lui(0x7B);
    v1 = addiu(v1, 28896);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    switch (v0.u()) {  // the entry of jump table 0x7B70E0
    case 0x1F9DA4: goto L_001f9da4;
    case 0x1F9DBC: goto L_001f9dbc;
    case 0x1F9DD4: goto L_001f9dd4;
    case 0x1F9DEC: goto L_001f9dec;
    case 0x1F9E04: goto L_001f9e04;
    case 0x1F9E1C: goto L_001f9e1c;
    case 0x1F9E34: goto L_001f9e34;
    case 0x1F9E4C: goto L_001f9e4c;
    case 0x1F9E64: goto L_001f9e64;
    default: rt::lookup_func(v0.u())(c); return;
    }
L_001f9da4:
    charge(6);
    a0 = 4625;
    a1 = 1;
    jal(0x1F9DAC, gen::fn_datSetFlag_0016f1f0);
    goto L_001f9e78;
L_001f9dbc:
    charge(6);
    a0 = 4626;
    a1 = 1;
    jal(0x1F9DC4, gen::fn_datSetFlag_0016f1f0);
    goto L_001f9e78;
L_001f9dd4:
    charge(6);
    a0 = 4627;
    a1 = 1;
    jal(0x1F9DDC, gen::fn_datSetFlag_0016f1f0);
    goto L_001f9e78;
L_001f9dec:
    charge(6);
    a0 = 4628;
    a1 = 1;
    jal(0x1F9DF4, gen::fn_datSetFlag_0016f1f0);
    goto L_001f9e78;
L_001f9e04:
    charge(6);
    a0 = 4630;
    a1 = 1;
    jal(0x1F9E0C, gen::fn_datSetFlag_0016f1f0);
    goto L_001f9e78;
L_001f9e1c:
    charge(6);
    a0 = 4631;
    a1 = 1;
    jal(0x1F9E24, gen::fn_datSetFlag_0016f1f0);
    goto L_001f9e78;
L_001f9e34:
    charge(6);
    a0 = 4632;
    a1 = 1;
    jal(0x1F9E3C, gen::fn_datSetFlag_0016f1f0);
    goto L_001f9e78;
L_001f9e4c:
    charge(6);
    a0 = 4633;
    a1 = 1;
    jal(0x1F9E54, gen::fn_datSetFlag_0016f1f0);
    goto L_001f9e78;
L_001f9e64:
    charge(5);
    kassert(0x1F9E70, kBrFriendC, 73);
L_001f9e78:
    charge(4);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_1FA0D0 [default equipment]: for party members 0..10 (jump tables 0x7B7170 / 0x7B7140): members 2..5 and 7..10
// equip the four items of their row (gp-18596..gp-18568: {u8 0, pad, u16 slot 0..3}; a nonzero first byte K_Asserts),
// member 6 the fixed items 254 / 1087 / 2081 / 3143; each item: sub_182C50(item, frame record), sub_1831E0(member,
// slot, record), sub_16DA50(member, slot, slot).
void Cpu::sub_1FA0D0() {
    enter(7);
    sp = addiu(sp, -80);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = 0;
    goto L_001fa424;
L_001fa0ec:
    charge(3);
    at = sltiu(s1, 11);
    if (at == 0) goto L_001fa420;
    charge(7);
    a0 = lui(0x7B);
    a0 = addiu(a0, 29040);
    v1 = sll(s1, 2);
    v1 = addu(v1, a0);
    lw(v1, v1, 0);
    switch (v1.u()) {  // the entry of jump table 0x7B7170
    case 0x1FA114: goto L_001fa114;
    case 0x1FA320: goto L_001fa320;
    case 0x1FA420: goto L_001fa420;
    default: rt::lookup_func(v1.u())(c); return;
    }
L_001fa114:
    charge(4);
    v1 = s1 & 0xFFFF;
    at = sltiu(v1, 11);
    if (at == 0) goto L_001fa1a0;
    charge(7);
    a0 = lui(0x7B);
    a0 = addiu(a0, 28992);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    lw(v1, v1, 0);
    switch (v1.u()) {  // the entry of jump table 0x7B7140
    case 0x1FA140: goto L_001fa140;
    case 0x1FA14C: goto L_001fa14c;
    case 0x1FA158: goto L_001fa158;
    case 0x1FA164: goto L_001fa164;
    case 0x1FA170: goto L_001fa170;
    case 0x1FA17C: goto L_001fa17c;
    case 0x1FA188: goto L_001fa188;
    case 0x1FA194: goto L_001fa194;
    case 0x1FA1A0: goto L_001fa1a0;
    default: rt::lookup_func(v1.u())(c); return;
    }
L_001fa140:
    charge(3);
    lw(s0, gp, kGpEquipTable2);
    goto L_001fa1b8;
L_001fa14c:
    charge(3);
    lw(s0, gp, kGpEquipTable3);
    goto L_001fa1b8;
L_001fa158:
    charge(3);
    lw(s0, gp, kGpEquipTable4);
    goto L_001fa1b8;
L_001fa164:
    charge(3);
    lw(s0, gp, kGpEquipTable5);
    goto L_001fa1b8;
L_001fa170:
    charge(3);
    lw(s0, gp, kGpEquipTable7);
    goto L_001fa1b8;
L_001fa17c:
    charge(3);
    lw(s0, gp, kGpEquipTable8);
    goto L_001fa1b8;
L_001fa188:
    charge(3);
    lw(s0, gp, kGpEquipTable9);
    goto L_001fa1b8;
L_001fa194:
    charge(3);
    lw(s0, gp, kGpEquipTable10);
    goto L_001fa1b8;
L_001fa1a0:
    charge(6);
    kassert(0x1FA1AC, kBrFriendC, 53);
    s0 = 0;
L_001fa1b8:
    charge(3);
    lbu(v1, s0, 0);
    if (v1 != 0) {
        charge(5);
        kassert(0x1FA1D0, kBrFriendC, 200);
    }
    charge(3);
    lhu(v1, s0, 2);
    if (v1 != 0) {
        charge(17);
        a0 = dsll32(v1, 16);
        a0 = dsra32(a0, 16);
        a1 = addiu(sp, 48);
        jal(0x1FA1F0, gen::fn_sub_182C50_00182c50);
        a0 = dsll32(s1, 16);
        a0 = dsra32(a0, 16);
        a1 = 0;
        a2 = addiu(sp, 48);
        jal(0x1FA208, gen::fn_sub_1831E0_001831e0);
        a0 = dsll32(s1, 16);
        a0 = dsra32(a0, 16);
        a1 = 0;
        a2 = 0;
        jal(0x1FA220, gen::fn_sub_16DA50_0016da50);
    }
    charge(3);
    lhu(v1, s0, 4);
    if (v1 != 0) {
        charge(17);
        a0 = dsll32(v1, 16);
        a0 = dsra32(a0, 16);
        a1 = addiu(sp, 48);
        jal(0x1FA240, gen::fn_sub_182C50_00182c50);
        a0 = dsll32(s1, 16);
        a0 = dsra32(a0, 16);
        a1 = 1;
        a2 = addiu(sp, 48);
        jal(0x1FA258, gen::fn_sub_1831E0_001831e0);
        a0 = dsll32(s1, 16);
        a0 = dsra32(a0, 16);
        a1 = 1;
        a2 = a1;
        jal(0x1FA270, gen::fn_sub_16DA50_0016da50);
    }
    charge(3);
    lhu(v1, s0, 6);
    if (v1 != 0) {
        charge(17);
        a0 = dsll32(v1, 16);
        a0 = dsra32(a0, 16);
        a1 = addiu(sp, 48);
        jal(0x1FA290, gen::fn_sub_182C50_00182c50);
        a0 = dsll32(s1, 16);
        a0 = dsra32(a0, 16);
        a1 = 2;
        a2 = addiu(sp, 48);
        jal(0x1FA2A8, gen::fn_sub_1831E0_001831e0);
        a0 = dsll32(s1, 16);
        a0 = dsra32(a0, 16);
        a1 = 2;
        a2 = a1;
        jal(0x1FA2C0, gen::fn_sub_16DA50_0016da50);
    }
    charge(3);
    lhu(v1, s0, 8);
    if (v1 == 0) goto L_001fa420;
    charge(19);
    a0 = dsll32(v1, 16);
    a0 = dsra32(a0, 16);
    a1 = addiu(sp, 48);
    jal(0x1FA2E0, gen::fn_sub_182C50_00182c50);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    a1 = 3;
    a2 = addiu(sp, 48);
    jal(0x1FA2F8, gen::fn_sub_1831E0_001831e0);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    a1 = 3;
    a2 = a1;
    jal(0x1FA310, gen::fn_sub_16DA50_0016da50);
    goto L_001fa420;
L_001fa320:
    charge(64);
    a0 = 254;
    a1 = addiu(sp, 48);
    jal(0x1FA328, gen::fn_sub_182C50_00182c50);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    a1 = 0;
    a2 = addiu(sp, 48);
    jal(0x1FA340, gen::fn_sub_1831E0_001831e0);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    a1 = 0;
    a2 = 0;
    jal(0x1FA358, gen::fn_sub_16DA50_0016da50);
    a0 = 1087;
    a1 = addiu(sp, 48);
    jal(0x1FA368, gen::fn_sub_182C50_00182c50);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    a1 = 1;
    a2 = addiu(sp, 48);
    jal(0x1FA380, gen::fn_sub_1831E0_001831e0);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    a1 = 1;
    a2 = a1;
    jal(0x1FA398, gen::fn_sub_16DA50_0016da50);
    a0 = 2081;
    a1 = addiu(sp, 48);
    jal(0x1FA3A8, gen::fn_sub_182C50_00182c50);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    a1 = 2;
    a2 = addiu(sp, 48);
    jal(0x1FA3C0, gen::fn_sub_1831E0_001831e0);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    a1 = 2;
    a2 = a1;
    jal(0x1FA3D8, gen::fn_sub_16DA50_0016da50);
    a0 = 3143;
    a1 = addiu(sp, 48);
    jal(0x1FA3E8, gen::fn_sub_182C50_00182c50);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    a1 = 3;
    a2 = addiu(sp, 48);
    jal(0x1FA400, gen::fn_sub_1831E0_001831e0);
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    a1 = 3;
    a2 = a1;
    jal(0x1FA418, gen::fn_sub_16DA50_0016da50);
L_001fa420:
    charge(1);
    s1 = addiu(s1, 1);
L_001fa424:
    charge(3);
    v1 = slti(s1, 11);
    if (v1 != 0) {
        backedge();
        goto L_001fa0ec;
    }
    charge(6);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 80);
    return;
}

// sub_1FA4F0 [best equipment after a level-up]: when the member's level (sub_16C470) is above the level last seen
// (sub_177D10): over the rows of the member's equipment table (jump tables 0x7B71D0 / 0x7B71A0, gp-18596..gp-18568) for
// the levels gained (sub_1FB3F0), keeps for each of the four slots the item with the highest value (+32 / +22 / +22 /
// +20 of the item's record, sub_170D60 / sub_170DA0 / sub_170DF0 / sub_170E40), starting from the item equipped now
// (datGetEquipmentIdx / sub_16F630); a better item is equipped (sub_182C50 into the frame record, then sub_1831E0 on
// the equipped index -- after sub_177CA0 / sub_177B90 / sub_177C50 when that slot was flagged -- or on the first free
// index). Any change sets the member's flag (sub_1F9D70); the new level is recorded (sub_177CE0). The 320-byte frame
// keeps the candidates and their values.
void Cpu::sub_1FA4F0() {
    enter(16);
    sp = addiu(sp, -320);
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
    s6 = a0;
    s1 = s6 & 0xFFFF;
    at = sltiu(s1, 11);
    if (at == 0) goto L_001fa54c;
    charge(7);
    v1 = lui(0x7B);
    v1 = addiu(v1, 29136);
    v0 = sll(s1, 2);
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    switch (v0.u()) {  // the entry of jump table 0x7B71D0
    case 0x1FA54C: goto L_001fa54c;
    case 0x1FA560: goto L_001fa560;
    default: rt::lookup_func(v0.u())(c); return;
    }
L_001fa54c:
    charge(5);
    kassert(0x1FA558, kBrFriendC, 310);
L_001fa560:
    charge(15);
    s0 = dsll32(s6, 16);
    s0 = dsra32(s0, 16);
    a0 = s0;
    jal(0x1FA56C, gen::fn_sub_16C470_0016c470);
    v0 = v0 & 0xFF;
    sw(v0, sp, 256);
    a0 = s1;
    jal(0x1FA580, gen::fn_sub_177D10_00177d10);
    s3 = v0;
    lw(v1, sp, 256);
    at = slt(s3, v1);
    if (at == 0) goto L_001fae68;
    charge(3);
    at = sltiu(s1, 11);
    if (at == 0) goto L_001fa624;
    charge(7);
    v1 = lui(0x7B);
    v1 = addiu(v1, 29088);
    v0 = sll(s1, 2);
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    switch (v0.u()) {  // the entry of jump table 0x7B71A0
    case 0x1FA5C4: goto L_001fa5c4;
    case 0x1FA5D0: goto L_001fa5d0;
    case 0x1FA5DC: goto L_001fa5dc;
    case 0x1FA5E8: goto L_001fa5e8;
    case 0x1FA5F4: goto L_001fa5f4;
    case 0x1FA600: goto L_001fa600;
    case 0x1FA60C: goto L_001fa60c;
    case 0x1FA618: goto L_001fa618;
    case 0x1FA624: goto L_001fa624;
    default: rt::lookup_func(v0.u())(c); return;
    }
L_001fa5c4:
    charge(3);
    lw(s2, gp, kGpEquipTable2);
    goto L_001fa63c;
L_001fa5d0:
    charge(3);
    lw(s2, gp, kGpEquipTable3);
    goto L_001fa63c;
L_001fa5dc:
    charge(3);
    lw(s2, gp, kGpEquipTable4);
    goto L_001fa63c;
L_001fa5e8:
    charge(3);
    lw(s2, gp, kGpEquipTable5);
    goto L_001fa63c;
L_001fa5f4:
    charge(3);
    lw(s2, gp, kGpEquipTable7);
    goto L_001fa63c;
L_001fa600:
    charge(3);
    lw(s2, gp, kGpEquipTable8);
    goto L_001fa63c;
L_001fa60c:
    charge(3);
    lw(s2, gp, kGpEquipTable9);
    goto L_001fa63c;
L_001fa618:
    charge(3);
    lw(s2, gp, kGpEquipTable10);
    goto L_001fa63c;
L_001fa624:
    charge(6);
    kassert(0x1FA630, kBrFriendC, 53);
    s2 = 0;
L_001fa63c:
    charge(24);
    lw(v0, sp, 256);
    a2 = subu(v0, s3);
    a0 = s2;
    a1 = s3;
    a3 = addiu(sp, 316);
    t0 = addiu(sp, 312);
    jal(0x1FA654, gen::fn_sub_1FB3F0_001fb3f0);
    lw(v1, sp, 316);
    v0 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = sll(v0, 1);
    s5 = addu(s2, v0);
    s3 = 0;
    s2 = 0;
    a0 = s0;
    a1 = 0;
    jal(0x1FA680, gen::fn_datGetEquipmentIdx_0016cb80);
    a1 = dsll32(v0, 16);
    a1 = dsra32(a1, 16);
    v0 = si(-1);
    if (a1 != v0) {
        charge(11);
        a0 = s0;
        jal(0x1FA6A0, gen::fn_sub_16F630_0016f630);
        s7 = v0 & 0xFFFF;
        a0 = dsll32(s7, 16);
        a0 = dsra32(a0, 16);
        jal(0x1FA6B4, gen::fn_sub_170D60_00170d60);
        lhu(v0, v0, 32);
        sw(v0, sp, 208);
        s3 = s3 | 0x1;
    }
    charge(9);
    a0 = s0;
    a1 = 1;
    jal(0x1FA6D0, gen::fn_datGetEquipmentIdx_0016cb80);
    a1 = dsll32(v0, 16);
    a1 = dsra32(a1, 16);
    v0 = si(-1);
    if (a1 != v0) {
        charge(11);
        a0 = s0;
        jal(0x1FA6F0, gen::fn_sub_16F630_0016f630);
        fp = v0 & 0xFFFF;
        a0 = dsll32(fp, 16);
        a0 = dsra32(a0, 16);
        jal(0x1FA704, gen::fn_sub_170DA0_00170da0);
        lhu(v0, v0, 22);
        sw(v0, sp, 192);
        s3 = s3 | 0x2;
    }
    charge(9);
    a0 = s0;
    a1 = 2;
    jal(0x1FA720, gen::fn_datGetEquipmentIdx_0016cb80);
    a1 = dsll32(v0, 16);
    a1 = dsra32(a1, 16);
    v0 = si(-1);
    if (a1 != v0) {
        charge(12);
        a0 = s0;
        jal(0x1FA740, gen::fn_sub_16F630_0016f630);
        sh(v0, sp, 240);
        v0 = dsll32(v0, 16);
        v0 = dsra32(v0, 16);
        a0 = v0;
        jal(0x1FA758, gen::fn_sub_170DF0_00170df0);
        lhu(v0, v0, 22);
        sw(v0, sp, 176);
        s3 = s3 | 0x4;
    }
    charge(9);
    a0 = s0;
    a1 = 3;
    jal(0x1FA774, gen::fn_datGetEquipmentIdx_0016cb80);
    a1 = dsll32(v0, 16);
    a1 = dsra32(a1, 16);
    v0 = si(-1);
    if (a1 != v0) {
        charge(12);
        a0 = s0;
        jal(0x1FA794, gen::fn_sub_16F630_0016f630);
        sh(v0, sp, 224);
        v0 = dsll32(v0, 16);
        v0 = dsra32(v0, 16);
        a0 = v0;
        jal(0x1FA7AC, gen::fn_sub_170E40_00170e40);
        lhu(v0, v0, 20);
        sw(v0, sp, 160);
        s3 = s3 | 0x8;
    }
    charge(4);
    s4 = s3;
    sw(zero, sp, 272);
    goto L_001fa970;
L_001fa7d0:
    charge(3);
    lhu(v0, s5, 2);
    if (lez(v0)) goto L_001fa830;
    charge(8);
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    jal(0x1FA7E4, gen::fn_sub_170D60_00170d60);
    lhu(v1, v0, 32);
    v0 = s4 & 0x1;
    if (v0 != 0) {
        charge(4);
        lw(v0, sp, 208);
        at = slt(v0, v1);
        if (at == 0) goto L_001fa830;
        charge(5);
        lhu(s7, s5, 2);
        sw(v1, sp, 208);
        s2 = s2 | 0x1;
        goto L_001fa830;
    }
    charge(4);
    lhu(s7, s5, 2);
    sw(v1, sp, 208);
    s4 = s4 | 0x1;
    s2 = s2 | 0x1;
L_001fa830:
    charge(3);
    lhu(v0, s5, 4);
    if (lez(v0)) goto L_001fa890;
    charge(8);
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    jal(0x1FA844, gen::fn_sub_170DA0_00170da0);
    lhu(v1, v0, 22);
    v0 = s4 & 0x2;
    if (v0 != 0) {
        charge(4);
        lw(v0, sp, 192);
        at = slt(v0, v1);
        if (at == 0) goto L_001fa890;
        charge(5);
        lhu(fp, s5, 4);
        sw(v1, sp, 192);
        s2 = s2 | 0x2;
        goto L_001fa890;
    }
    charge(4);
    lhu(fp, s5, 4);
    sw(v1, sp, 192);
    s4 = s4 | 0x2;
    s2 = s2 | 0x2;
L_001fa890:
    charge(3);
    lhu(v0, s5, 6);
    if (lez(v0)) goto L_001fa8f8;
    charge(8);
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    jal(0x1FA8A4, gen::fn_sub_170DF0_00170df0);
    lhu(v1, v0, 22);
    v0 = s4 & 0x4;
    if (v0 != 0) {
        charge(4);
        lw(v0, sp, 176);
        at = slt(v0, v1);
        if (at == 0) goto L_001fa8f8;
        charge(6);
        lhu(v0, s5, 6);
        sh(v0, sp, 240);
        sw(v1, sp, 176);
        s2 = s2 | 0x4;
        goto L_001fa8f8;
    }
    charge(5);
    lhu(v0, s5, 6);
    sh(v0, sp, 240);
    sw(v1, sp, 176);
    s4 = s4 | 0x4;
    s2 = s2 | 0x4;
L_001fa8f8:
    charge(3);
    lhu(v0, s5, 8);
    if (lez(v0)) goto L_001fa960;
    charge(8);
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    jal(0x1FA90C, gen::fn_sub_170E40_00170e40);
    lhu(v1, v0, 20);
    v0 = s4 & 0x8;
    if (v0 != 0) {
        charge(4);
        lw(v0, sp, 160);
        at = slt(v0, v1);
        if (at == 0) goto L_001fa960;
        charge(6);
        lhu(v0, s5, 8);
        sh(v0, sp, 224);
        sw(v1, sp, 160);
        s2 = s2 | 0x8;
        goto L_001fa960;
    }
    charge(5);
    lhu(v0, s5, 8);
    sh(v0, sp, 224);
    sw(v1, sp, 160);
    s4 = s4 | 0x8;
    s2 = s2 | 0x8;
L_001fa960:
    charge(4);
    lw(v0, sp, 272);
    v0 = addiu(v0, 1);
    sw(v0, sp, 272);
    s5 = addiu(s5, 10);
L_001fa970:
    charge(5);
    lw(v1, sp, 312);
    lw(v0, sp, 272);
    v0 = slt(v0, v1);
    if (v0 != 0) {
        backedge();
        goto L_001fa7d0;
    }
    charge(3);
    v0 = s2 & 0x1;
    if (v0 == 0) goto L_001faab4;
    charge(8);
    a0 = dsll32(s7, 16);
    a0 = dsra32(a0, 16);
    a1 = addiu(sp, 288);
    jal(0x1FA99C, gen::fn_sub_182C50_00182c50);
    v0 = s3 & 0x1;
    if (v0 != 0) {
        charge(12);
        a0 = s0;
        a1 = 0;
        jal(0x1FA9B8, gen::fn_datGetEquipmentIdx_0016cb80);
        s4 = dsll32(v0, 16);
        s4 = dsra32(s4, 16);
        a0 = s1;
        a1 = 0;
        jal(0x1FA9D0, gen::fn_sub_177CA0_00177ca0);
        if (v0 != 0) {
            charge(9);
            a0 = s6;
            a1 = 0;
            a2 = s4;
            jal(0x1FA9EC, gen::fn_sub_177B90_00177b90);
            a0 = s1;
            a1 = s4;
            jal(0x1FA9FC, gen::fn_sub_177C50_00177c50);
        }
        charge(8);
        a1 = dsll32(s4, 16);
        a1 = dsra32(a1, 16);
        a0 = s0;
        a2 = addiu(sp, 288);
        jal(0x1FAA14, gen::fn_sub_1831E0_001831e0);
        goto L_001faab4;
    }
    charge(9);
    a0 = s0;
    a1 = 0;
    jal(0x1FAA2C, gen::fn_datGetEquipmentIdx_0016cb80);
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-1);
    if (v1 != v0) {
        charge(5);
        kassert(0x1FAA54, kBrFriendC, 479);
    }
    charge(5);
    s4 = 0;
    s5 = dsll32(s0, 16);
    s5 = dsra32(s5, 16);
    for (;;) {
        charge(3);
        v0 = slti(s4, 4);
        if (v0 == 0) {
            break;
        }
        backedge();
        charge(7);
        a0 = s5;
        a1 = s4;
        jal(0x1FAA78, gen::fn_sub_16F630_0016f630);
        v0 = v0 & 0xFFFF;
        if (v0 == 0) goto L_001faa9c;
        charge(1);
        s4 = addiu(s4, 1);
    }
L_001faa9c:
    charge(6);
    a1 = dsll32(s4, 16);
    a1 = dsra32(a1, 16);
    a0 = s0;
    a2 = addiu(sp, 288);
    jal(0x1FAAAC, gen::fn_sub_1831E0_001831e0);
L_001faab4:
    charge(3);
    v0 = s2 & 0x2;
    if (v0 == 0) goto L_001fabe4;
    charge(8);
    a0 = dsll32(fp, 16);
    a0 = dsra32(a0, 16);
    a1 = addiu(sp, 288);
    jal(0x1FAACC, gen::fn_sub_182C50_00182c50);
    v0 = s3 & 0x2;
    if (v0 != 0) {
        charge(12);
        a0 = s0;
        a1 = 1;
        jal(0x1FAAE8, gen::fn_datGetEquipmentIdx_0016cb80);
        s4 = dsll32(v0, 16);
        s4 = dsra32(s4, 16);
        a0 = s1;
        a1 = 1;
        jal(0x1FAB00, gen::fn_sub_177CA0_00177ca0);
        if (v0 != 0) {
            charge(9);
            a0 = s6;
            a1 = 1;
            a2 = s4;
            jal(0x1FAB1C, gen::fn_sub_177B90_00177b90);
            a0 = s1;
            a1 = s4;
            jal(0x1FAB2C, gen::fn_sub_177C50_00177c50);
        }
        charge(8);
        a1 = dsll32(s4, 16);
        a1 = dsra32(a1, 16);
        a0 = s0;
        a2 = addiu(sp, 288);
        jal(0x1FAB44, gen::fn_sub_1831E0_001831e0);
        goto L_001fabe4;
    }
    charge(9);
    a0 = s0;
    a1 = 1;
    jal(0x1FAB5C, gen::fn_datGetEquipmentIdx_0016cb80);
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-1);
    if (v1 != v0) {
        charge(5);
        kassert(0x1FAB84, kBrFriendC, 503);
    }
    charge(5);
    s4 = 0;
    s5 = dsll32(s0, 16);
    s5 = dsra32(s5, 16);
    for (;;) {
        charge(3);
        v0 = slti(s4, 4);
        if (v0 == 0) {
            break;
        }
        backedge();
        charge(7);
        a0 = s5;
        a1 = s4;
        jal(0x1FABA8, gen::fn_sub_16F630_0016f630);
        v0 = v0 & 0xFFFF;
        if (v0 == 0) goto L_001fabcc;
        charge(1);
        s4 = addiu(s4, 1);
    }
L_001fabcc:
    charge(6);
    a1 = dsll32(s4, 16);
    a1 = dsra32(a1, 16);
    a0 = s0;
    a2 = addiu(sp, 288);
    jal(0x1FABDC, gen::fn_sub_1831E0_001831e0);
L_001fabe4:
    charge(3);
    v0 = s2 & 0x4;
    if (v0 == 0) goto L_001fad14;
    charge(8);
    lh(v0, sp, 240);
    a0 = v0;
    a1 = addiu(sp, 288);
    jal(0x1FABFC, gen::fn_sub_182C50_00182c50);
    v0 = s3 & 0x4;
    if (v0 != 0) {
        charge(12);
        a0 = s0;
        a1 = 2;
        jal(0x1FAC18, gen::fn_datGetEquipmentIdx_0016cb80);
        s4 = dsll32(v0, 16);
        s4 = dsra32(s4, 16);
        a0 = s1;
        a1 = 2;
        jal(0x1FAC30, gen::fn_sub_177CA0_00177ca0);
        if (v0 != 0) {
            charge(9);
            a0 = s6;
            a1 = 2;
            a2 = s4;
            jal(0x1FAC4C, gen::fn_sub_177B90_00177b90);
            a0 = s1;
            a1 = s4;
            jal(0x1FAC5C, gen::fn_sub_177C50_00177c50);
        }
        charge(8);
        a1 = dsll32(s4, 16);
        a1 = dsra32(a1, 16);
        a0 = s0;
        a2 = addiu(sp, 288);
        jal(0x1FAC74, gen::fn_sub_1831E0_001831e0);
        goto L_001fad14;
    }
    charge(9);
    a0 = s0;
    a1 = 2;
    jal(0x1FAC8C, gen::fn_datGetEquipmentIdx_0016cb80);
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-1);
    if (v1 != v0) {
        charge(5);
        kassert(0x1FACB4, kBrFriendC, 528);
    }
    charge(5);
    s4 = 0;
    s5 = dsll32(s0, 16);
    s5 = dsra32(s5, 16);
    for (;;) {
        charge(3);
        v0 = slti(s4, 4);
        if (v0 == 0) {
            break;
        }
        backedge();
        charge(7);
        a0 = s5;
        a1 = s4;
        jal(0x1FACD8, gen::fn_sub_16F630_0016f630);
        v0 = v0 & 0xFFFF;
        if (v0 == 0) goto L_001facfc;
        charge(1);
        s4 = addiu(s4, 1);
    }
L_001facfc:
    charge(6);
    a1 = dsll32(s4, 16);
    a1 = dsra32(a1, 16);
    a0 = s0;
    a2 = addiu(sp, 288);
    jal(0x1FAD0C, gen::fn_sub_1831E0_001831e0);
L_001fad14:
    charge(3);
    v0 = s2 & 0x8;
    if (v0 == 0) goto L_001fae44;
    charge(8);
    lh(v0, sp, 224);
    a0 = v0;
    a1 = addiu(sp, 288);
    jal(0x1FAD2C, gen::fn_sub_182C50_00182c50);
    v0 = s3 & 0x8;
    if (v0 != 0) {
        charge(12);
        a0 = s0;
        a1 = 3;
        jal(0x1FAD48, gen::fn_datGetEquipmentIdx_0016cb80);
        s3 = dsll32(v0, 16);
        s3 = dsra32(s3, 16);
        a0 = s1;
        a1 = 3;
        jal(0x1FAD60, gen::fn_sub_177CA0_00177ca0);
        if (v0 != 0) {
            charge(9);
            a0 = s6;
            a1 = 3;
            a2 = s3;
            jal(0x1FAD7C, gen::fn_sub_177B90_00177b90);
            a0 = s1;
            a1 = s3;
            jal(0x1FAD8C, gen::fn_sub_177C50_00177c50);
        }
        charge(8);
        a1 = dsll32(s3, 16);
        a1 = dsra32(a1, 16);
        a0 = s0;
        a2 = addiu(sp, 288);
        jal(0x1FADA4, gen::fn_sub_1831E0_001831e0);
        goto L_001fae44;
    }
    charge(9);
    a0 = s0;
    a1 = 3;
    jal(0x1FADBC, gen::fn_datGetEquipmentIdx_0016cb80);
    v1 = dsll32(v0, 16);
    v1 = dsra32(v1, 16);
    v0 = si(-1);
    if (v1 != v0) {
        charge(5);
        kassert(0x1FADE4, kBrFriendC, 553);
    }
    charge(5);
    s3 = 0;
    s4 = dsll32(s0, 16);
    s4 = dsra32(s4, 16);
    for (;;) {
        charge(3);
        v0 = slti(s3, 4);
        if (v0 == 0) {
            break;
        }
        backedge();
        charge(7);
        a0 = s4;
        a1 = s3;
        jal(0x1FAE08, gen::fn_sub_16F630_0016f630);
        v0 = v0 & 0xFFFF;
        if (v0 == 0) goto L_001fae2c;
        charge(1);
        s3 = addiu(s3, 1);
    }
L_001fae2c:
    charge(6);
    a1 = dsll32(s3, 16);
    a1 = dsra32(a1, 16);
    a0 = s0;
    a2 = addiu(sp, 288);
    jal(0x1FAE3C, gen::fn_sub_1831E0_001831e0);
L_001fae44:
    charge(2);
    if (s2 != 0) {
        charge(3);
        a0 = s6;
        jal(0x1FAE50, gen::fn_sub_1F9D70_001f9d70);
    }
    charge(4);
    a0 = s1;
    lw(a1, sp, 256);
    jal(0x1FAE60, gen::fn_sub_177CE0_00177ce0);
L_001fae68:
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
    sp = addiu(sp, 320);
    return;
}

// sub_1FAEA0 [COMM 0x171]: the script command that evolves a member's persona: member = int parameter 0; outside The
// Answer (sub_17D800) it keeps the persona's five bytes sub_173B00(persona, 0..4) in its frame (sp + 72); members 2..8
// (jump table 0x7B7200) whose persona is the pre-evolution id 192, 194, .. 204 evolve it to id + 1 (sub_1FB130); member
// 1 in The Answer with persona 195 runs sub_174E20(1) / sub_175130(1) / sub_174B40(195) instead; member 0 and others
// K_Assert (line 714). Outside The Answer the five bytes are written back (sub_173B60(member, k, byte)). Returns 1.
void Cpu::sub_1FAEA0() {
    enter(17);
    sp = addiu(sp, -80);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    a0 = 0;
    jal(0x1FAEB8, gen::fn_scrGetIntPara_0035ed20);
    s1 = v0 & 0xFFFF;
    a0 = s1;
    jal(0x1FAEC8, gen::fn_datPersonaGetByPcId_00174800);
    s0 = v0;
    jal(0x1FAED4, gen::fn_sub_17D800_0017d800);
    if (v0 != 0) goto L_001faf20;
    charge(2);
    if (s0 == 0) goto L_001faf20;
    charge(3);
    s2 = 0;
    for (;;) {
        charge(3);
        v0 = slti(s2, 5);
        if (v0 == 0) {
            break;
        }
        backedge();
        charge(7);
        a1 = s2 & 0xFFFF;
        a0 = s0;
        jal(0x1FAF00, gen::fn_sub_173B00_00173b00);
        v1 = addu(s2, sp);
        sb(v0, v1, 72);
        s2 = addiu(s2, 1);
    }
L_001faf20:
    charge(4);
    v0 = s1 & 0xFFFF;
    at = sltiu(v0, 9);
    if (at == 0) goto L_001fb0b0;
    charge(7);
    v1 = lui(0x7B);
    v1 = addiu(v1, 29184);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    switch (v0.u()) {  // the entry of jump table 0x7B7200
    case 0x1FAF4C: goto L_001faf4c;
    case 0x1FAF98: goto L_001faf98;
    case 0x1FAFC0: goto L_001fafc0;
    case 0x1FAFE8: goto L_001fafe8;
    case 0x1FB010: goto L_001fb010;
    case 0x1FB038: goto L_001fb038;
    case 0x1FB060: goto L_001fb060;
    case 0x1FB088: goto L_001fb088;
    case 0x1FB0B0: goto L_001fb0b0;
    default: rt::lookup_func(v0.u())(c); return;
    }
L_001faf4c:
    charge(4);
    jal(0x1FAF4C, gen::fn_sub_17D800_0017d800);
    if (v0 == 0) goto L_001fb0c4;
    charge(4);
    lhu(v1, s0, 2);
    v0 = 195;
    if (v1 != v0) goto L_001fb0c4;
    charge(11);
    a0 = 1;
    jal(0x1FAF70, gen::fn_sub_174E20_00174e20);
    a0 = 1;
    jal(0x1FAF7C, gen::fn_sub_175130_00175130);
    lhu(a0, s0, 2);
    jal(0x1FAF88, gen::fn_sub_174B40_00174b40);
    goto L_001fb0c4;
L_001faf98:
    charge(4);
    lhu(v1, s0, 2);
    v0 = 192;
    if (v1 != v0) goto L_001fb0c4;
    charge(6);
    a0 = s1;
    a1 = 193;
    jal(0x1FAFB0, gen::fn_sub_1FB130_001fb130);
    goto L_001fb0c4;
L_001fafc0:
    charge(4);
    lhu(v1, s0, 2);
    v0 = 194;
    if (v1 != v0) goto L_001fb0c4;
    charge(6);
    a0 = s1;
    a1 = 195;
    jal(0x1FAFD8, gen::fn_sub_1FB130_001fb130);
    goto L_001fb0c4;
L_001fafe8:
    charge(4);
    lhu(v1, s0, 2);
    v0 = 196;
    if (v1 != v0) goto L_001fb0c4;
    charge(6);
    a0 = s1;
    a1 = 197;
    jal(0x1FB000, gen::fn_sub_1FB130_001fb130);
    goto L_001fb0c4;
L_001fb010:
    charge(4);
    lhu(v1, s0, 2);
    v0 = 198;
    if (v1 != v0) goto L_001fb0c4;
    charge(6);
    a0 = s1;
    a1 = 199;
    jal(0x1FB028, gen::fn_sub_1FB130_001fb130);
    goto L_001fb0c4;
L_001fb038:
    charge(4);
    lhu(v1, s0, 2);
    v0 = 200;
    if (v1 != v0) goto L_001fb0c4;
    charge(6);
    a0 = s1;
    a1 = 201;
    jal(0x1FB050, gen::fn_sub_1FB130_001fb130);
    goto L_001fb0c4;
L_001fb060:
    charge(4);
    lhu(v1, s0, 2);
    v0 = 202;
    if (v1 != v0) goto L_001fb0c4;
    charge(6);
    a0 = s1;
    a1 = 203;
    jal(0x1FB078, gen::fn_sub_1FB130_001fb130);
    goto L_001fb0c4;
L_001fb088:
    charge(4);
    lhu(v1, s0, 2);
    v0 = 204;
    if (v1 != v0) goto L_001fb0c4;
    charge(6);
    a0 = s1;
    a1 = 205;
    jal(0x1FB0A0, gen::fn_sub_1FB130_001fb130);
    goto L_001fb0c4;
L_001fb0b0:
    charge(5);
    kassert(0x1FB0BC, kBrFriendC, 714);
L_001fb0c4:
    charge(4);
    jal(0x1FB0C4, gen::fn_sub_17D800_0017d800);
    if (v0 != 0) goto L_001fb110;
    charge(2);
    if (s0 == 0) goto L_001fb110;
    charge(3);
    s0 = 0;
    for (;;) {
        charge(3);
        v0 = slti(s0, 5);
        if (v0 == 0) {
            break;
        }
        backedge();
        charge(7);
        a1 = s0 & 0xFFFF;
        v0 = addu(s0, sp);
        lbu(a2, v0, 72);
        a0 = s1;
        jal(0x1FB0F8, gen::fn_sub_173B60_00173b60);
        s0 = addiu(s0, 1);
    }
L_001fb110:
    charge(8);
    v0 = 1;
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 80);
    return;
}

// =================================================================================================================
// br_data.c: persona evolution / skill rows, level bands, experience
// =================================================================================================================

// sub_1FB130 [evolve the member's persona]: keeps the old persona's level byte, sub_175820(member, new id), then
// sub_1F9E90(member, sub_176210(persona, old level)).
void Cpu::sub_1FB130() {
    enter(32);
    sp = addiu(sp, -64);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s2 = a0;
    s1 = a1;
    jal(0x1FB14C, gen::fn_datPersonaGetByPcId_00174800);
    lbu(s0, v0, 4);
    a0 = s2;
    a1 = s1;
    jal(0x1FB160, gen::fn_sub_175820_00175820);
    a0 = s2;
    jal(0x1FB16C, gen::fn_datPersonaGetByPcId_00174800);
    a1 = s0 & 0xFFFF;
    a0 = v0;
    jal(0x1FB17C, gen::fn_sub_176210_00176210);
    a0 = s2;
    a1 = v0;
    jal(0x1FB18C, gen::fn_sub_1F9E90_001f9e90);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
    return;
}

// sub_1FB1B0: sub_1770D0(persona id of the member, value).
void Cpu::sub_1FB1B0() {
    enter(15);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a1;
    jal(0x1FB1C0, gen::fn_datPersonaGetByPcId_00174800);
    lhu(a0, v0, 2);
    a1 = s0;
    jal(0x1FB1D0, gen::fn_sub_1770D0_001770d0);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
    return;
}

// sub_1FB1F0 [skills learned at the next levels]: the persona's skill row (special personas >= 192: gp-18624 + 622 *
// (id - 192) + 4, 32 entries; others gp-18632 + 70 * id + 6, 16 entries, from the base level gp-18640), the entries
// between its level and 99 (sub_1FB4B0), and of those the skills of kind 1 the persona does not have yet (sub_173370 /
// sub_176A30): up to 8 into out_skills (u16), the number into *out_count.
void Cpu::sub_1FB1F0() {
    enter(24);
    sp = addiu(sp, -144);
    sd(ra, sp, 112);
    sq(s6, sp, 96);
    sq(s5, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s4 = a0;
    s1 = a1;
    s0 = a2;
    jal(0x1FB220, gen::fn_sub_173370_00173370);
    s6 = v0;
    a0 = s4;
    jal(0x1FB230, gen::fn_sub_176A30_00176a30);
    s2 = v0;
    a0 = s4;
    jal(0x1FB240, gen::fn_sub_175CA0_00175ca0);
    if (v0 != 0) {
        charge(18);
        lhu(v0, s4, 2);
        v1 = addiu(v0, -192);
        v0 = 622;
        mult(v1, v1, v0);
        lw(v0, gp, kGpSpecialSkillRows);
        v0 = addu(v0, v1);
        s3 = addiu(v0, 4);
        lbu(a2, s4, 4);
        v0 = 99;
        a3 = subu(v0, a2);
        a0 = s3;
        a1 = 32;
        t0 = addiu(sp, 140);
        t1 = addiu(sp, 136);
        jal(0x1FB288, gen::fn_sub_1FB4B0_001fb4b0);
        goto L_001fb2f4;
    }
    charge(23);
    lhu(v1, s4, 2);
    v0 = sll(v1, 3);
    a1 = subu(v0, v1);
    v0 = sll(a1, 2);
    v0 = addu(a1, v0);
    v1 = sll(v0, 1);
    lw(v0, gp, kGpPersonaSkillRows);
    v0 = addu(v0, v1);
    s3 = addiu(v0, 6);
    lbu(a0, s4, 4);
    lw(v1, gp, kGpPersonaLevels);
    v0 = sll(a1, 1);
    v0 = addu(v0, v1);
    lbu(v0, v0, 3);
    a2 = subu(a0, v0);
    v0 = 99;
    a3 = subu(v0, a0);
    a0 = s3;
    a1 = 16;
    t0 = addiu(sp, 140);
    t1 = addiu(sp, 136);
    jal(0x1FB2EC, gen::fn_sub_1FB4B0_001fb4b0);
L_001fb2f4:
    charge(7);
    lw(v1, sp, 140);
    v1 = sll(v1, 2);
    s5 = addu(s3, v1);
    s3 = 0;
    s4 = 0;
    goto L_001fb3ac;
L_001fb310:
    charge(4);
    lb(a0, s5, 1);
    v1 = 1;
    if (a0 != v1) {
        charge(2);
        goto L_001fb398;
    }
    charge(3);
    a1 = 0;
    for (;;) {
        charge(3);
        v1 = slt(a1, s2);
        if (v1 == 0) {
            break;
        }
        backedge();
        charge(6);
        lhu(a0, s5, 2);
        v1 = sll(a1, 1);
        v1 = addu(s6, v1);
        lhu(v1, v1, 0);
        if (a0 == v1) goto L_001fb35c;
        charge(1);
        a1 = addiu(a1, 1);
    }
L_001fb35c:
    charge(2);
    if (a1 != s2) goto L_001fb398;
    charge(3);
    v1 = slti(s3, 8);
    if (v1 == 0) {
        charge(5);
        kassert(0x1FB37C, kBrDataC, 91);
    }
    charge(5);
    lhu(a0, s5, 2);
    v1 = sll(s3, 1);
    v1 = addu(s1, v1);
    sh(a0, v1, 0);
    s3 = addiu(s3, 1);
L_001fb398:
    charge(3);
    v1 = 8;
    if (s3 == v1) goto L_001fb3bc;
    charge(2);
    s4 = addiu(s4, 1);
    s5 = addiu(s5, 4);
L_001fb3ac:
    charge(4);
    lw(v1, sp, 136);
    v1 = slt(s4, v1);
    if (v1 != 0) {
        backedge();
        goto L_001fb310;
    }
L_001fb3bc:
    charge(12);
    sw(s3, s0, 0);
    ld(ra, sp, 112);
    lq(s6, sp, 96);
    lq(s5, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 144);
    return;
}

// sub_1FB3F0 [rows in a level range]: over 10-byte rows {u8 level, pad, u16 x4} ended by a row whose four words are
// zero: the first and the number of rows with level < row level <= level + gained (0, 0 when none).
void Cpu::sub_1FB3F0() {
    enter(4);
    t2 = addu(a1, a2);
    t4 = 0;
    t3 = 0;
    v1 = 1;
L_001fb400:
    charge(7);
    a2 = sll(t3, 2);
    a2 = addu(a2, t3);
    a2 = sll(a2, 1);
    t1 = addu(a0, a2);
    lhu(a2, t1, 2);
    if (a2 != 0) goto L_001fb440;
    charge(3);
    lhu(a2, t1, 4);
    if (a2 != 0) goto L_001fb440;
    charge(3);
    lhu(a2, t1, 6);
    if (a2 != 0) goto L_001fb440;
    charge(3);
    lhu(a2, t1, 8);
    if (a2 == 0) goto L_001fb47c;
L_001fb440:
    charge(4);
    lbu(a2, t1, 0);
    at = slt(a1, a2);
    if (at == 0) goto L_001fb470;
    charge(3);
    at = slt(t2, a2);
    if (at != 0) goto L_001fb470;
    charge(2);
    if (t4 == 0) {
        charge(2);
        t6 = t3;
        t4 = v1;
    }
    charge(1);
    t5 = t3;
L_001fb470:
    charge(3);
    t3 = addiu(t3, 1);
    backedge();
    goto L_001fb400;
L_001fb47c:
    charge(2);
    if (t4 != 0) {
        charge(6);
        sw(t6, a3, 0);
        v1 = addiu(t5, 1);
        v1 = subu(v1, t6);
        sw(v1, t0, 0);
        goto L_001fb4a4;
    }
    charge(2);
    sw(zero, a3, 0);
    sw(zero, t0, 0);
L_001fb4a4:
    charge(2);
    return;
}

// sub_1FB4B0 [skill rows in a level range]: over n 4-byte rows {u8 level, s8 kind, u16 skill} (a kind 0 ends them): the
// first row above level and the number up to level + range.
void Cpu::sub_1FB4B0() {
    enter(8);
    t3 = addu(a2, a3);
    t7 = 0;
    t5 = 0;
    t4 = 0;
    t8 = 0;
    a3 = 1;
    goto L_001fb520;
L_001fb4d0:
    charge(5);
    v1 = sll(t8, 2);
    t2 = addu(a0, v1);
    lb(v1, t2, 1);
    if (v1 == 0) goto L_001fb52c;
    charge(4);
    lbu(v1, t2, 0);
    at = slt(a2, v1);
    if (at == 0) goto L_001fb51c;
    charge(2);
    if (t5 == 0) {
        charge(3);
        t5 = a3;
        t7 = t8;
        t6 = t8;
    }
    charge(3);
    at = slt(t3, v1);
    if (at != 0) goto L_001fb51c;
    charge(2);
    t4 = a3;
    t6 = t8;
L_001fb51c:
    charge(1);
    t8 = addiu(t8, 1);
L_001fb520:
    charge(3);
    v1 = slt(t8, a1);
    if (v1 != 0) {
        backedge();
        goto L_001fb4d0;
    }
L_001fb52c:
    charge(2);
    if (t4 != 0) {
        charge(6);
        sw(t7, t0, 0);
        v1 = addiu(t6, 1);
        v1 = subu(v1, t7);
        sw(v1, t1, 0);
        goto L_001fb554;
    }
    charge(2);
    sw(t7, t0, 0);
    sw(zero, t1, 0);
L_001fb554:
    charge(2);
    return;
}

// sub_1FBD50 [level band]: the address of the nth (from 0) row of gp-18600 with lo <= level < hi (a row whose lo, hi
// and word are all zero ends the table: K_Assert, 0).
void Cpu::sub_1FBD50() {
    enter(5);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    lw(v0, gp, kGpLevelBands);
    a3 = 0;
    a2 = a0 & 0xFFFF;
L_001fbd64:
    charge(3);
    lbu(a0, v0, 0);
    if (a0 != 0) goto L_001fbd88;
    charge(3);
    lbu(v1, v0, 1);
    if (v1 != 0) goto L_001fbd88;
    charge(3);
    lhu(v1, v0, 2);
    if (v1 == 0) goto L_001fbdc4;
L_001fbd88:
    charge(3);
    v1 = slt(a2, a0);
    if (v1 != 0) goto L_001fbdb8;
    charge(4);
    lbu(v1, v0, 1);
    at = slt(a2, v1);
    if (at == 0) goto L_001fbdb8;
    charge(2);
    if (a3 == a1) {
        charge(2);
        goto L_001fbddc;
    }
    charge(1);
    a3 = addiu(a3, 1);
L_001fbdb8:
    charge(3);
    v0 = addiu(v0, 4);
    backedge();
    goto L_001fbd64;
L_001fbdc4:
    charge(6);
    kassert(0x1FBDD0, kBrDataC, 499);
    v0 = 0;
L_001fbddc:
    charge(4);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_1FBDF0 [experience]: exp * scale(mode) (mode 1/2/3/4: gp-31824 / gp-31820 / 1.0 / gp-32656; others K_Assert) when
// row gp-18504 + 28 * row has flag 0x80, else exp * gap(other_level - level, clamped to -10..10, gp-18516) * scale, as
// EE singles truncated; capped at 0xFFFF.
void Cpu::sub_1FBDF0() {
    enter(18);
    sp = addiu(sp, -96);
    sd(ra, sp, 80);
    sq(s3, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F20, sp, 0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    v0 = sll(a3, 3);
    v0 = subu(v0, a3);
    v1 = sll(v0, 2);
    lw(v0, gp, kGpExpRows);
    s0 = addu(v0, v1);
    v0 = 4;
    if (t0 != v0) {
        charge(3);
        v0 = 3;
        if (t0 != v0) {
            charge(3);
            v0 = 2;
            if (t0 != v0) {
                charge(3);
                v0 = 1;
                if (t0 != v0) {
                    charge(2);
                    goto L_001fbe98;
                }
                charge(3);
                lwc1(F20, gp, kGpScale1);
                goto L_001fbeac;
            }
            charge(3);
            lwc1(F20, gp, kGpScale2);
            goto L_001fbeac;
        }
        charge(4);
        v0 = lui(0x3F80);
        mtc1(v0, F20);
        goto L_001fbeac;
    }
    charge(3);
    lwc1(F20, gp, kGpScale4);
    goto L_001fbeac;
L_001fbe98:
    charge(5);
    kassert(0x1FBEA4, kBrDataC, 542);
L_001fbeac:
    charge(4);
    lw(v0, s0, 0);
    v0 = v0 & 0x80;
    if (v0 != 0) {
        charge(8);
        mtc1(s1, F0);
        cvt_s_w(F0, F0);
        mul_s(F0, F0, F20);
        cvt_w_s(F0, F0);
        mfc1(v0, F0);
        goto L_001fbf68;
    }
    charge(4);
    v1 = subu(s2, s3);
    v0 = slti(v1, 10);
    if (v0 == 0) {
        charge(3);
        s0 = 20;
        goto L_001fbf14;
    }
    charge(3);
    at = slti(v1, -9);
    if (at != 0) {
        charge(3);
        s0 = 0;
        goto L_001fbf14;
    }
    charge(1);
    s0 = addiu(v1, 10);
L_001fbf14:
    charge(2);
    if (!ltz(s0)) {
        charge(3);
        v0 = slti(s0, 21);
        if (v0 != 0) goto L_001fbf3c;
    }
    charge(5);
    kassert(0x1FBF34, kBrDataC, 523);
L_001fbf3c:
    charge(11);
    v1 = sll(s0, 2);
    lw(v0, gp, kGpLevelGapScale);
    v0 = addu(v0, v1);
    lwc1(F1, v0, 0);
    mtc1(s1, F0);
    cvt_s_w(F0, F0);
    mul_s(F0, F0, F1);
    mul_s(F0, F20, F0);
    cvt_w_s(F0, F0);
    mfc1(v0, F0);
L_001fbf68:
    charge(4);
    at = lui(0x1);
    at = slt(v0, at);
    if (at == 0) {
        charge(1);
        v0 = 0xFFFF;
    }
    charge(9);
    ld(ra, sp, 80);
    lq(s3, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 96);
    return;
}

// sub_1FBFA0 [experience with an item]: as sub_1FBDF0 with the item's factor (553 -> 0.25, 554 -> 0.5, 555 -> 1.0).
void Cpu::sub_1FBFA0() {
    enter(22);
    sp = addiu(sp, -112);
    sd(ra, sp, 96);
    sq(s4, sp, 80);
    sq(s3, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    s4 = a2;
    s3 = a3;
    s2 = t1;
    v0 = sll(t0, 3);
    v0 = subu(v0, t0);
    v1 = sll(v0, 2);
    lw(v0, gp, kGpExpRows);
    s0 = addu(v0, v1);
    v1 = subu(a1, a0);
    v0 = slti(v1, 10);
    if (v0 == 0) {
        charge(3);
        s1 = 20;
        goto L_001fc020;
    }
    charge(3);
    at = slti(v1, -9);
    if (at != 0) {
        charge(3);
        s1 = 0;
        goto L_001fc020;
    }
    charge(1);
    s1 = addiu(v1, 10);
L_001fc020:
    charge(2);
    if (!ltz(s1)) {
        charge(3);
        v0 = slti(s1, 21);
        if (v0 != 0) goto L_001fc048;
    }
    charge(5);
    kassert(0x1FC040, kBrDataC, 523);
L_001fc048:
    charge(9);
    v1 = sll(s1, 2);
    lw(v0, gp, kGpLevelGapScale);
    v0 = addu(v0, v1);
    lwc1(F20, v0, 0);
    mtc1(zero, F22);
    v1 = s3 & 0xFFFF;
    v0 = 553;
    if (v1 != v0) {
        charge(3);
        v0 = 554;
        if (v1 != v0) {
            charge(3);
            v0 = 555;
            if (v1 != v0) {
                charge(2);
                goto L_001fc0bc;
            }
            charge(4);
            v0 = lui(0x3F80);
            mtc1(v0, F22);
            goto L_001fc0d0;
        }
        charge(4);
        v0 = lui(0x3F00);
        mtc1(v0, F22);
        goto L_001fc0d0;
    }
    charge(4);
    v0 = lui(0x3E80);
    mtc1(v0, F22);
    goto L_001fc0d0;
L_001fc0bc:
    charge(5);
    kassert(0x1FC0C8, kBrDataC, 579);
L_001fc0d0:
    charge(3);
    v0 = 4;
    if (s2 != v0) {
        charge(3);
        v0 = 3;
        if (s2 != v0) {
            charge(3);
            v0 = 2;
            if (s2 != v0) {
                charge(3);
                v0 = 1;
                if (s2 != v0) {
                    charge(2);
                    goto L_001fc13c;
                }
                charge(3);
                lwc1(F21, gp, kGpScale1);
                goto L_001fc150;
            }
            charge(3);
            lwc1(F21, gp, kGpScale2);
            goto L_001fc150;
        }
        charge(4);
        v0 = lui(0x3F80);
        mtc1(v0, F21);
        goto L_001fc150;
    }
    charge(3);
    lwc1(F21, gp, kGpScale4);
    goto L_001fc150;
L_001fc13c:
    charge(5);
    kassert(0x1FC148, kBrDataC, 590);
L_001fc150:
    charge(4);
    lw(v0, s0, 0);
    v0 = v0 & 0x80;
    if (v0 != 0) {
        charge(9);
        mtc1(s4, F0);
        cvt_s_w(F0, F0);
        mul_s(F0, F0, F22);
        mul_s(F0, F21, F0);
        cvt_w_s(F0, F0);
        mfc1(v0, F0);
        goto L_001fc1a4;
    }
    charge(8);
    mtc1(s4, F0);
    cvt_s_w(F0, F0);
    mul_s(F0, F0, F20);
    mul_s(F0, F22, F0);
    mul_s(F0, F21, F0);
    cvt_w_s(F0, F0);
    mfc1(v0, F0);
L_001fc1a4:
    charge(4);
    at = lui(0x1);
    at = slt(v0, at);
    if (at == 0) {
        charge(1);
        v0 = 0xFFFF;
    }
    charge(12);
    ld(ra, sp, 96);
    lq(s4, sp, 80);
    lq(s3, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 112);
    return;
}

// sub_1FC1F0: sub_1764B0(persona of member 1, 24).
void Cpu::sub_1FC1F0() {
    enter(13);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    a0 = 1;
    jal(0x1FC1FC, gen::fn_datPersonaGetByPcId_00174800);
    a0 = v0;
    a1 = 24;
    jal(0x1FC20C, gen::fn_sub_1764B0_001764b0);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_1FC230 [has a skill to learn]: the scan of sub_1FB1F0 without the copy: whether some skill of kind 1 between the
// persona's level and 99 is not learnt yet.
void Cpu::sub_1FC230() {
    enter(19);
    sp = addiu(sp, -96);
    sd(ra, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s3 = a0;
    jal(0x1FC24C, gen::fn_sub_173370_00173370);
    s1 = v0;
    a0 = s3;
    jal(0x1FC25C, gen::fn_sub_176A30_00176a30);
    s0 = v0;
    a0 = s3;
    jal(0x1FC26C, gen::fn_sub_175CA0_00175ca0);
    if (v0 != 0) {
        charge(18);
        lhu(v0, s3, 2);
        v1 = addiu(v0, -192);
        v0 = 622;
        mult(v1, v1, v0);
        lw(v0, gp, kGpSpecialSkillRows);
        v0 = addu(v0, v1);
        s2 = addiu(v0, 4);
        lbu(a2, s3, 4);
        v0 = 99;
        a3 = subu(v0, a2);
        a0 = s2;
        a1 = 32;
        t0 = addiu(sp, 92);
        t1 = addiu(sp, 88);
        jal(0x1FC2B4, gen::fn_sub_1FB4B0_001fb4b0);
        goto L_001fc320;
    }
    charge(23);
    lhu(v1, s3, 2);
    v0 = sll(v1, 3);
    a1 = subu(v0, v1);
    v0 = sll(a1, 2);
    v0 = addu(a1, v0);
    v1 = sll(v0, 1);
    lw(v0, gp, kGpPersonaSkillRows);
    v0 = addu(v0, v1);
    s2 = addiu(v0, 6);
    lbu(a0, s3, 4);
    lw(v1, gp, kGpPersonaLevels);
    v0 = sll(a1, 1);
    v0 = addu(v0, v1);
    lbu(v0, v0, 3);
    a2 = subu(a0, v0);
    v0 = 99;
    a3 = subu(v0, a0);
    a0 = s2;
    a1 = 16;
    t0 = addiu(sp, 92);
    t1 = addiu(sp, 88);
    jal(0x1FC318, gen::fn_sub_1FB4B0_001fb4b0);
L_001fc320:
    charge(8);
    lw(v0, sp, 92);
    v0 = sll(v0, 2);
    t0 = addu(s2, v0);
    a3 = 0;
    lw(a1, sp, 88);
    a0 = 1;
    goto L_001fc390;
L_001fc340:
    charge(3);
    lb(v0, t0, 1);
    if (v0 != a0) goto L_001fc388;
    charge(3);
    a2 = 0;
    for (;;) {
        charge(3);
        v0 = slt(a2, s0);
        if (v0 == 0) {
            break;
        }
        backedge();
        charge(6);
        lhu(v1, t0, 2);
        v0 = sll(a2, 1);
        v0 = addu(s1, v0);
        lhu(v0, v0, 0);
        if (v1 == v0) goto L_001fc380;
        charge(1);
        a2 = addiu(a2, 1);
    }
L_001fc380:
    charge(2);
    if (a2 == s0) goto L_001fc39c;
L_001fc388:
    charge(2);
    a3 = addiu(a3, 1);
    t0 = addiu(t0, 4);
L_001fc390:
    charge(3);
    v0 = slt(a3, a1);
    if (v0 != 0) {
        backedge();
        goto L_001fc340;
    }
L_001fc39c:
    charge(9);
    v0 = slt(a3, a1);
    ld(ra, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 96);
    return;
}

// sub_1FC3C0 [level of the next skill]: the scan of sub_1FC230, returning the level of the row where it stopped (the
// row's level byte, plus the persona's base level gp-18640 for the ordinary personas).
void Cpu::sub_1FC3C0() {
    enter(19);
    sp = addiu(sp, -96);
    sd(ra, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s3 = a0;
    jal(0x1FC3DC, gen::fn_sub_173370_00173370);
    s1 = v0;
    a0 = s3;
    jal(0x1FC3EC, gen::fn_sub_176A30_00176a30);
    s0 = v0;
    a0 = s3;
    jal(0x1FC3FC, gen::fn_sub_175CA0_00175ca0);
    if (v0 != 0) {
        charge(18);
        lhu(v0, s3, 2);
        v1 = addiu(v0, -192);
        v0 = 622;
        mult(v1, v1, v0);
        lw(v0, gp, kGpSpecialSkillRows);
        v0 = addu(v0, v1);
        s2 = addiu(v0, 4);
        lbu(a2, s3, 4);
        v0 = 99;
        a3 = subu(v0, a2);
        a0 = s2;
        a1 = 32;
        t0 = addiu(sp, 92);
        t1 = addiu(sp, 88);
        jal(0x1FC444, gen::fn_sub_1FB4B0_001fb4b0);
        goto L_001fc4b0;
    }
    charge(23);
    lhu(v1, s3, 2);
    v0 = sll(v1, 3);
    a1 = subu(v0, v1);
    v0 = sll(a1, 2);
    v0 = addu(a1, v0);
    v1 = sll(v0, 1);
    lw(v0, gp, kGpPersonaSkillRows);
    v0 = addu(v0, v1);
    s2 = addiu(v0, 6);
    lbu(a0, s3, 4);
    lw(v1, gp, kGpPersonaLevels);
    v0 = sll(a1, 1);
    v0 = addu(v0, v1);
    lbu(v0, v0, 3);
    a2 = subu(a0, v0);
    v0 = 99;
    a3 = subu(v0, a0);
    a0 = s2;
    a1 = 16;
    t0 = addiu(sp, 92);
    t1 = addiu(sp, 88);
    jal(0x1FC4A8, gen::fn_sub_1FB4B0_001fb4b0);
L_001fc4b0:
    charge(8);
    lw(v0, sp, 92);
    v0 = sll(v0, 2);
    s2 = addu(s2, v0);
    a3 = 0;
    lw(a1, sp, 88);
    a0 = 1;
    goto L_001fc520;
L_001fc4d0:
    charge(3);
    lb(v0, s2, 1);
    if (v0 != a0) goto L_001fc518;
    charge(3);
    a2 = 0;
    for (;;) {
        charge(3);
        v0 = slt(a2, s0);
        if (v0 == 0) {
            break;
        }
        backedge();
        charge(6);
        lhu(v1, s2, 2);
        v0 = sll(a2, 1);
        v0 = addu(s1, v0);
        lhu(v0, v0, 0);
        if (v1 == v0) goto L_001fc510;
        charge(1);
        a2 = addiu(a2, 1);
    }
L_001fc510:
    charge(2);
    if (a2 == s0) goto L_001fc52c;
L_001fc518:
    charge(2);
    a3 = addiu(a3, 1);
    s2 = addiu(s2, 4);
L_001fc520:
    charge(3);
    v0 = slt(a3, a1);
    if (v0 != 0) {
        backedge();
        goto L_001fc4d0;
    }
L_001fc52c:
    charge(5);
    a0 = s3;
    jal(0x1FC530, gen::fn_sub_175CA0_00175ca0);
    if (v0 != 0) {
        charge(3);
        lbu(v0, s2, 0);
        goto L_001fc570;
    }
    charge(9);
    lhu(v1, s3, 2);
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 1);
    lw(v0, gp, kGpPersonaLevels);
    v0 = addu(v1, v0);
    lbu(v1, v0, 3);
    lbu(v0, s2, 0);
    v0 = addu(v0, v1);
L_001fc570:
    charge(8);
    ld(ra, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 96);
    return;
}

// sub_1FC590 [follow-up damage]: datCalcDamage of the unit's skill (sub_308930) on the target, scaled by 0.5 (unit flag
// 0x4) or 1.5, zeroed (flag 0x4) / tripled on an RpRandom() % 500 < 100 roll, added to the target's HP (datCalcAddHp);
// a target that dies (datCalcIsDead) gets sub_1FC870 when the unit's flag 0x4 is clear, bad status 0x80 cleared and
// 0x80000 set. Returns sub_1FC870's answer (or 0).
void Cpu::sub_1FC590() {
    enter(25);
    sp = addiu(sp, -80);
    sd(ra, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s3 = a0;
    s2 = a1;
    s1 = 0;
    jal(0x1FC5B4, gen::fn_sub_308930_00308930);
    a0 = v0 & 0xFFFF;
    a1 = s3;
    a2 = s2;
    a3 = 1;
    t0 = a3;
    t1 = a3;
    t2 = 0;
    t3 = a3;
    jal(0x1FC5DC, gen::fn_datCalcDamage_00303130);
    lhu(v1, s3, 0);
    v1 = v1 & 0x4;
    if (v1 != 0) {
        charge(16);
        v1 = lui(0x3F00);
        mtc1(v1, F1);
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
        mul_s(F0, F1, F0);
        cvt_w_s(F0, F0);
        mfc1(s0, F0);
        jal(0x1FC614, gen::fn_sub_488F30_00488f30);
        v1 = 500;
        divu(v0, v1);
        mfhi(v0);
        at = sltiu(v0, 100);
        if (at == 0) goto L_001fc688;
        charge(3);
        s0 = 0;
        goto L_001fc688;
    }
    charge(16);
    v1 = lui(0x3FC0);
    mtc1(v1, F1);
    mtc1(v0, F0);
    cvt_s_w(F0, F0);
    mul_s(F0, F1, F0);
    cvt_w_s(F0, F0);
    mfc1(s0, F0);
    jal(0x1FC660, gen::fn_sub_488F30_00488f30);
    v1 = 500;
    divu(v0, v1);
    mfhi(v0);
    at = sltiu(v0, 100);
    if (at == 0) goto L_001fc688;
    charge(2);
    v0 = sll(s0, 1);
    s0 = addu(v0, s0);
L_001fc688:
    charge(10);
    a0 = s2;
    a1 = s0;
    jal(0x1FC690, gen::fn_datCalcAddHp_00300410);
    a0 = s2;
    a1 = 0;
    jal(0x1FC6A0, gen::fn_datCalcIsDead_0030b5a0);
    if (v0 != 0) {
        charge(4);
        lhu(v0, s3, 0);
        v0 = v0 & 0x4;
        if (v0 == 0) {
            charge(5);
            a0 = s3;
            a1 = s2;
            jal(0x1FC6C8, gen::fn_sub_1FC870_001fc870);
            s1 = v0;
        }
        charge(8);
        a0 = s2;
        a1 = 128;
        jal(0x1FC6DC, gen::fn_datCalcClearBadStatus_00300560);
        a0 = s2;
        a1 = lui(0x8);
        jal(0x1FC6EC, gen::fn_datCalcSetBadStatus_003004f0);
    }
    charge(9);
    v0 = s1;
    ld(ra, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 80);
    return;
}

// =================================================================================================================
// br_res.c: the result resource record (gp-18916)
// =================================================================================================================

// sub_2338D0: res flag word |= 0x10.
void Cpu::sub_2338D0() {
    enter(5);
    lw(v1, a0, 0);
    v1 = v1 | 0x10;
    sw(v1, a0, 0);
    return;
}

// sub_2338F0: res +2116 = 0, flag word |= 0x20.
void Cpu::sub_2338F0() {
    enter(6);
    sw(zero, a0, 2116);
    lw(v1, a0, 0);
    v1 = v1 | 0x20;
    sw(v1, a0, 0);
    return;
}

// sub_233910: flag word |= 0x200.
void Cpu::sub_233910() {
    enter(5);
    lw(v1, a0, 0);
    v1 = v1 | 0x200;
    sw(v1, a0, 0);
    return;
}

// sub_233930: flag word &= ~0x200.
void Cpu::sub_233930() {
    enter(6);
    lw(a1, a0, 0);
    v1 = si(-513);
    v1 = a1 & v1;
    sw(v1, a0, 0);
    return;
}

// sub_233950: res +2128 = $f12.
void Cpu::sub_233950() {
    enter(3);
    swc1(F12, a0, 2128);
    return;
}

// sub_233960: res +2132 = $f12.
void Cpu::sub_233960() {
    enter(3);
    swc1(F12, a0, 2132);
    return;
}

// sub_233970 [br_res init]: K_Asserts that gp-18916 is free, clears res +0 / +4 / +8 and installs it at gp-18916.
void Cpu::sub_233970() {
    enter(7);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    lw(v1, gp, kGpBrRes);
    if (v1 != 0) {
        charge(5);
        kassert(0x233998, kBrResC, 88);
    }
    charge(9);
    sw(zero, s0, 0);
    sw(zero, s0, 4);
    sw(zero, s0, 8);
    sw(s0, gp, kGpBrRes);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
    return;
}

// sub_233AD0: br_res flag 0x1 (K_Assert when gp-18916 is 0).
void Cpu::sub_233AD0() {
    enter(5);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    lw(v0, gp, kGpBrRes);
    if (v0 == 0) {
        charge(5);
        kassert(0x233AF0, kBrResC, 82);
    }
    charge(7);
    lw(v0, gp, kGpBrRes);
    lw(v0, v0, 0);
    v0 = v0 & 0x1;
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_233BB0: br_res flag 0x2 (br_level.bin requested, sub_233B20).
void Cpu::sub_233BB0() {
    enter(5);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    lw(v0, gp, kGpBrRes);
    if (v0 == 0) {
        charge(5);
        kassert(0x233BD0, kBrResC, 82);
    }
    charge(7);
    lw(v0, gp, kGpBrRes);
    lw(v0, v0, 0);
    v0 = v0 & 0x2;
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_233D20: br_res flag 0x4.
void Cpu::sub_233D20() {
    enter(5);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    lw(v0, gp, kGpBrRes);
    if (v0 == 0) {
        charge(5);
        kassert(0x233D40, kBrResC, 82);
    }
    charge(7);
    lw(v0, gp, kGpBrRes);
    lw(v0, v0, 0);
    v0 = v0 & 0x4;
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_233D70: br_res +56 + 4 * i (K_Assert unless +4 has 0x10).
void Cpu::sub_233D70() {
    enter(8);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    lw(v0, gp, kGpBrRes);
    if (v0 == 0) {
        charge(5);
        kassert(0x233D9C, kBrResC, 82);
    }
    charge(5);
    lw(s0, gp, kGpBrRes);
    lw(v0, s0, 4);
    v0 = v0 & 0x10;
    if (v0 == 0) {
        charge(5);
        kassert(0x233DC4, kBrResC, 179);
    }
    charge(9);
    v0 = sll(s1, 2);
    v0 = addu(v0, s0);
    lw(v0, v0, 56);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
    return;
}

// sub_233DF0: br_res +72 + 4 * i (K_Assert unless +4 has 0x10).
void Cpu::sub_233DF0() {
    enter(8);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    lw(v0, gp, kGpBrRes);
    if (v0 == 0) {
        charge(5);
        kassert(0x233E1C, kBrResC, 82);
    }
    charge(5);
    lw(s0, gp, kGpBrRes);
    lw(v0, s0, 4);
    v0 = v0 & 0x10;
    if (v0 == 0) {
        charge(5);
        kassert(0x233E44, kBrResC, 186);
    }
    charge(9);
    v0 = sll(s1, 2);
    v0 = addu(v0, s0);
    lw(v0, v0, 72);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
    return;
}

// sub_234570 [result sprite file]: br_res +28 + 4 * i.
void Cpu::sub_234570() {
    enter(7);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    lw(v0, gp, kGpBrRes);
    if (v0 == 0) {
        charge(5);
        kassert(0x234598, kBrResC, 82);
    }
    charge(9);
    lw(v1, gp, kGpBrRes);
    v0 = sll(s0, 2);
    v0 = addu(v0, v1);
    lw(v0, v0, 28);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
    return;
}

// sub_2345D0: br_res +36 + 4 * i.
void Cpu::sub_2345D0() {
    enter(7);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    lw(v0, gp, kGpBrRes);
    if (v0 == 0) {
        charge(5);
        kassert(0x2345F8, kBrResC, 82);
    }
    charge(9);
    lw(v1, gp, kGpBrRes);
    v0 = sll(s0, 2);
    v0 = addu(v0, v1);
    lw(v0, v0, 36);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
    return;
}

// sub_234630: br_res +48 + 4 * i.
void Cpu::sub_234630() {
    enter(7);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    lw(v0, gp, kGpBrRes);
    if (v0 == 0) {
        charge(5);
        kassert(0x234658, kBrResC, 82);
    }
    charge(9);
    lw(v1, gp, kGpBrRes);
    v0 = sll(s0, 2);
    v0 = addu(v0, v1);
    lw(v0, v0, 48);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
    return;
}

// sub_234690: br_res +48 + 4 * i = sub_21C9F0(file), +4 |= 0x40.
void Cpu::sub_234690() {
    enter(10);
    sp = addiu(sp, -64);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s2 = a0;
    s1 = a1;
    lw(v0, gp, kGpBrRes);
    if (v0 == 0) {
        charge(5);
        kassert(0x2346C4, kBrResC, 82);
    }
    charge(17);
    lw(s0, gp, kGpBrRes);
    a0 = s1;
    jal(0x2346D4, gen::fn_sub_21C9F0_0021c9f0);
    v1 = sll(s2, 2);
    v1 = addu(v1, s0);
    sw(v0, v1, 48);
    lw(v1, s0, 4);
    v1 = v1 | 0x40;
    sw(v1, s0, 4);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
    return;
}

// sub_2347E0: br_res +44.
void Cpu::sub_2347E0() {
    enter(5);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    lw(v0, gp, kGpBrRes);
    if (v0 == 0) {
        charge(5);
        kassert(0x234800, kBrResC, 82);
    }
    charge(6);
    lw(v0, gp, kGpBrRes);
    lw(v0, v0, 44);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// =================================================================================================================
// br_panel.c: the spoils panel (gp-18912)
// =================================================================================================================

// sub_234820 [br_panel init]: clears the record (+0, +7504), builds the title line (+784: frFontBuildGlyphList of
// sub_177790(1) with the default glyph flags 1 / 2 swapped around it, colour 0xFFFFFF, sub_3B2C60 with $f12 =
// *(float*)0x960088 - sub_21EA00(40)), the {0, 0, 640, 448} rectangle at +9568 (sub_21D8E0, sub_21EAC0 with
// sub_21EA00(10), sub_21D950 with colour 255 / 255 / 255 / 0), +9824 = level of member 1, and installs the record at
// gp-18912.
void Cpu::sub_234820() {
    enter(80);
    sp = addiu(sp, -64);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    sw(zero, a0, 0);
    sw(zero, a0, 7504);
    a0 = 1;
    jal(0x23483C, gen::fn_frFontSetDefaultGlyphFlags_003b0e70);
    a0 = 2;
    jal(0x234848, gen::fn_frFontClearDefaultGlyphFlags_003b0e90);
    a0 = 1;
    jal(0x234854, gen::fn_sub_177790_00177790);
    a0 = v0;
    a1 = 1;
    a2 = 6;
    a3 = 0;
    t0 = 0;
    jal(0x234870, gen::fn_frFontBuildGlyphList_003b0970);
    sw(v0, s0, 784);
    a0 = 1;
    jal(0x234880, gen::fn_frFontClearDefaultGlyphFlags_003b0e90);
    a0 = 2;
    jal(0x23488C, gen::fn_frFontSetDefaultGlyphFlags_003b0e70);
    lw(a0, s0, 784);
    v0 = lui(0xFF);
    a1 = v0 | 0xFFFF;
    jal(0x2348A0, gen::fn_frFontLineSetRgba_003b0e20);
    a0 = 40;
    jal(0x2348AC, gen::fn_sub_21EA00_0021ea00);
    v0 = lui(0x96);
    lwc1(F1, v0, 136);
    sub_s(F12, F1, F0);
    lw(a0, s0, 784);
    jal(0x2348C4, gen::fn_sub_3B2C60_003b2c60);
    sw(zero, sp, 32);
    sw(zero, sp, 36);
    v0 = lui(0x4420);
    sw(v0, sp, 40);
    v0 = lui(0x43E0);
    sw(v0, sp, 44);
    a0 = addiu(s0, 9568);
    a1 = addiu(sp, 32);
    jal(0x2348EC, gen::fn_sub_21D8E0_0021d8e0);
    a0 = 10;
    jal(0x2348F8, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s0, 9568);
    mov_s(F12, F0);
    jal(0x234908, gen::fn_sub_21EAC0_0021eac0);
    v0 = 255;
    sb(v0, sp, 60);
    sb(v0, sp, 61);
    sb(v0, sp, 62);
    sb(zero, sp, 63);
    a0 = addiu(s0, 9568);
    a1 = addiu(sp, 60);
    jal(0x23492C, gen::fn_sub_21D950_0021d950);
    a0 = 1;
    jal(0x234938, gen::fn_sub_16C470_0016c470);
    v1 = v0 & 0xFF;
    sw(v1, s0, 9824);
    sw(s0, gp, kGpBrPanel);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
    return;
}

// sub_234960 [br_panel shutdown]: releases the title line (+784) and the +7504 item lines (+3628 + 1296 * i,
// sub_3B0170) and clears gp-18912.
void Cpu::sub_234960() {
    enter(7);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    lw(v0, gp, kGpBrPanel);
    if (v0 == 0) {
        charge(5);
        kassert(0x234988, kBrPanelC, 153);
    }
    charge(7);
    lw(s0, gp, kGpBrPanel);
    lw(a0, s0, 784);
    jal(0x234998, gen::fn_sub_3B0170_003b0170);
    s1 = 0;
    for (;;) {
        charge(4);
        lw(v1, s0, 7504);
        v1 = slt(s1, v1);
        if (v1 == 0) {
            break;
        }
        backedge();
        charge(10);
        v0 = sll(s1, 3);
        v1 = addu(v0, s1);
        v0 = sll(v1, 3);
        v0 = addu(v1, v0);
        v0 = sll(v0, 4);
        v0 = addu(s0, v0);
        lw(a0, v0, 3628);
        jal(0x2349C8, gen::fn_sub_3B0170_003b0170);
        s1 = addiu(s1, 1);
    }
    charge(7);
    sw(zero, gp, kGpBrPanel);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
    return;
}

// sub_234A00 [fill the spoils panel]: copies the record of sub_1F1C90 into the panel (flags 0x4 items / 0x8 bonus,
// +9828 the experience, the item rows at +3616 + 1296 * i), then lays out the panel sprites (sub_21CCA0 / sub_21D3B0
// with the result sprite files sub_234570(0/1)), the digits (bpIfontDrawNumber), and per item its name line
// (frFontBuildGlyphList of sub_171110) and count; ends with sub_236390.
void Cpu::sub_234A00() {
    enter(13);
    sp = addiu(sp, -128);
    sd(ra, sp, 112);
    sq(s6, sp, 96);
    sq(s5, sp, 80);
    sq(s4, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    lw(v0, gp, kGpBrPanel);
    if (v0 == 0) {
        charge(5);
        kassert(0x234A40, kBrPanelC, 153);
    }
    charge(12);
    lw(s1, gp, kGpBrPanel);
    lw(v1, s1, 0);
    v0 = si(-5);
    v1 = v1 & v0;
    sw(v1, s1, 0);
    v0 = si(-9);
    v0 = v1 & v0;
    sw(v0, s1, 0);
    lw(v0, s0, 0);
    v0 = v0 & 0x1;
    if (v0 != 0) {
        charge(3);
        lw(v0, s1, 0);
        v0 = v0 | 0x8;
        sw(v0, s1, 0);
    }
    charge(8);
    lw(v0, s0, 44);
    sw(v0, s1, 9828);
    sw(zero, s1, 9836);
    lw(v0, s0, 40);
    sw(v0, s1, 7504);
    a1 = 0;
    for (;;) {
        charge(4);
        lw(v0, s0, 40);
        v0 = slt(a1, v0);
        if (v0 == 0) {
            break;
        }
        backedge();
        charge(17);
        v0 = sll(a1, 1);
        v0 = addu(v0, a1);
        v0 = sll(v0, 2);
        a0 = addu(s0, v0);
        v0 = sll(a1, 3);
        v1 = addu(v0, a1);
        v0 = sll(v1, 3);
        v0 = addu(v1, v0);
        v0 = sll(v0, 4);
        v1 = addu(s1, v0);
        lw(v0, a0, 4);
        sw(v0, v1, 3616);
        lw(v0, a0, 8);
        sw(v0, v1, 3620);
        lw(v0, a0, 12);
        sw(v0, v1, 3624);
        a1 = addiu(a1, 1);
    }
    charge(3);
    lw(v0, s1, 7504);
    if (v0 != 0) {
        charge(3);
        lw(v0, s1, 0);
        v0 = v0 | 0x4;
        sw(v0, s1, 0);
    }
    charge(5);
    lw(v0, s1, 0);
    v0 = ~v0;
    v0 = v0 & 0x1;
    if (v0 == 0) {
        charge(5);
        kassert(0x234B30, kBrPanelC, 248);
    }
    charge(41);
    a0 = 0;
    jal(0x234B3C, gen::fn_sub_234570_00234570);
    s5 = v0;
    a0 = 1;
    jal(0x234B4C, gen::fn_sub_234570_00234570);
    s6 = v0;
    a0 = s5;
    a1 = 0;
    jal(0x234B60, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s1, 16);
    a1 = v0;
    jal(0x234B70, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s5;
    a1 = 5;
    jal(0x234B80, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s1, 272);
    a1 = v0;
    jal(0x234B90, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s5;
    a1 = 3;
    jal(0x234BA0, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s1, 528);
    a1 = v0;
    jal(0x234BB0, gen::fn_sub_21D3B0_0021d3b0);
    a0 = addiu(s1, 800);
    a1 = 2;
    lw(a2, s1, 9824);
    a3 = 1;
    jal(0x234BC8, gen::fn_bpIfontDrawNumber_00238980);
    s0 = 0;
    for (;;) {
        charge(3);
        v0 = slti(s0, 2);
        if (v0 == 0) {
            break;
        }
        backedge();
        charge(10);
        a0 = 40;
        jal(0x234BE0, gen::fn_sub_21EA00_0021ea00);
        v0 = sll(s0, 8);
        v0 = addu(s1, v0);
        a0 = addiu(v0, 800);
        mov_s(F12, F0);
        jal(0x234BF8, gen::fn_sub_21EAC0_0021eac0);
        s0 = addiu(s0, 1);
    }
    charge(9);
    a0 = addiu(s1, 1312);
    a1 = 7;
    lw(a2, s1, 9828);
    a3 = 0;
    jal(0x234C20, gen::fn_sub_235F30_00235f30);
    s0 = 0;
    for (;;) {
        charge(3);
        v0 = slti(s0, 7);
        if (v0 == 0) {
            break;
        }
        backedge();
        charge(10);
        a0 = 40;
        jal(0x234C38, gen::fn_sub_21EA00_0021ea00);
        v0 = sll(s0, 8);
        v0 = addu(s1, v0);
        a0 = addiu(v0, 1312);
        mov_s(F12, F0);
        jal(0x234C50, gen::fn_sub_21EAC0_0021eac0);
        s0 = addiu(s0, 1);
    }
    charge(26);
    a0 = s5;
    a1 = 2;
    jal(0x234C70, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s1, 3104);
    a1 = v0;
    jal(0x234C80, gen::fn_sub_21D3B0_0021d3b0);
    a0 = s5;
    a1 = 4;
    jal(0x234C90, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s1, 3360);
    a1 = v0;
    a2 = 1;
    jal(0x234CA4, gen::fn_sub_21E380_0021e380);
    a0 = 1;
    jal(0x234CB0, gen::fn_frFontSetDefaultGlyphFlags_003b0e70);
    a0 = 2;
    jal(0x234CBC, gen::fn_frFontClearDefaultGlyphFlags_003b0e90);
    s3 = 0;
    goto L_00234e48;
L_00234cd0:
    charge(56);
    v0 = sll(s3, 3);
    v1 = addu(v0, s3);
    v0 = sll(v1, 3);
    v0 = addu(v1, v0);
    v0 = sll(v0, 4);
    v0 = addu(s1, v0);
    s0 = addiu(v0, 3616);
    lh(a0, v0, 3620);
    a1 = 0;
    jal(0x234CF4, gen::fn_sub_171110_00171110);
    a0 = v0;
    a1 = 1;
    a2 = 6;
    a3 = 0;
    t0 = 0;
    jal(0x234D10, gen::fn_frFontBuildGlyphList_003b0970);
    s2 = v0;
    a0 = 40;
    jal(0x234D20, gen::fn_sub_21EA00_0021ea00);
    v0 = lui(0x96);
    lwc1(F1, v0, 136);
    sub_s(F12, F1, F0);
    a0 = s2;
    jal(0x234D38, gen::fn_sub_3B2C60_003b2c60);
    sw(s2, s0, 12);
    a0 = s5;
    a1 = 4;
    jal(0x234D4C, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s0, 16);
    a1 = v0;
    a2 = 1;
    jal(0x234D60, gen::fn_sub_21E380_0021e380);
    a0 = s5;
    a1 = 1;
    jal(0x234D70, gen::fn_sub_21CCA0_0021cca0);
    s2 = v0;
    a0 = addiu(s0, 272);
    a1 = s2;
    jal(0x234D84, gen::fn_sub_21D3B0_0021d3b0);
    a0 = addiu(s0, 528);
    a1 = 2;
    lw(a2, s0, 8);
    a3 = 1;
    jal(0x234D9C, gen::fn_sub_235F30_00235f30);
    s4 = 0;
    for (;;) {
        charge(3);
        v0 = slti(s4, 2);
        if (v0 == 0) {
            break;
        }
        backedge();
        charge(10);
        a0 = 40;
        jal(0x234DB4, gen::fn_sub_21EA00_0021ea00);
        v0 = sll(s4, 8);
        v0 = addu(s0, v0);
        a0 = addiu(v0, 528);
        mov_s(F12, F0);
        jal(0x234DCC, gen::fn_sub_21EAC0_0021eac0);
        s4 = addiu(s4, 1);
    }
    charge(4);
    lw(v1, s0, 0);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
            goto L_00234e34;
        }
        charge(7);
        a0 = s6;
        a1 = 10;
        jal(0x234E0C, gen::fn_sub_21CCA0_0021cca0);
        s2 = v0;
        goto L_00234e34;
    }
    charge(5);
    a0 = s6;
    a1 = 11;
    jal(0x234E28, gen::fn_sub_21CCA0_0021cca0);
    s2 = v0;
L_00234e34:
    charge(5);
    a0 = addiu(s0, 1040);
    a1 = s2;
    jal(0x234E3C, gen::fn_sub_21D3B0_0021d3b0);
    s3 = addiu(s3, 1);
L_00234e48:
    charge(4);
    lw(v0, s1, 7504);
    v0 = slt(s3, v0);
    if (v0 != 0) {
        backedge();
        goto L_00234cd0;
    }
    charge(25);
    a0 = 1;
    jal(0x234E5C, gen::fn_frFontClearDefaultGlyphFlags_003b0e90);
    a0 = 2;
    jal(0x234E68, gen::fn_frFontSetDefaultGlyphFlags_003b0e70);
    a0 = s5;
    a1 = 6;
    jal(0x234E78, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s1, 7520);
    a1 = v0;
    jal(0x234E88, gen::fn_sub_21D3B0_0021d3b0);
    a0 = 30;
    jal(0x234E94, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s1, 7520);
    mov_s(F12, F0);
    jal(0x234EA4, gen::fn_sub_21EAC0_0021eac0);
    lw(v0, s1, 0);
    v0 = v0 & 0x8;
    if (v0 != 0) {
        charge(6);
        a0 = s5;
        a1 = 10;
        jal(0x234EC4, gen::fn_sub_21CCA0_0021cca0);
        goto L_00234ee4;
    }
    charge(4);
    a0 = s5;
    a1 = 8;
    jal(0x234EDC, gen::fn_sub_21CCA0_0021cca0);
L_00234ee4:
    charge(72);
    a0 = addiu(s1, 8032);
    a1 = v0;
    jal(0x234EEC, gen::fn_sub_21D3B0_0021d3b0);
    a0 = 30;
    jal(0x234EF8, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s1, 8032);
    mov_s(F12, F0);
    jal(0x234F08, gen::fn_sub_21EAC0_0021eac0);
    a0 = s5;
    a1 = 9;
    jal(0x234F18, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s1, 7776);
    a1 = v0;
    jal(0x234F28, gen::fn_sub_21D3B0_0021d3b0);
    a0 = 30;
    jal(0x234F34, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s1, 7776);
    mov_s(F12, F0);
    jal(0x234F44, gen::fn_sub_21EAC0_0021eac0);
    a0 = s5;
    a1 = 7;
    jal(0x234F54, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s1, 8544);
    a1 = v0;
    jal(0x234F64, gen::fn_sub_21D3B0_0021d3b0);
    a0 = 30;
    jal(0x234F70, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s1, 8544);
    mov_s(F12, F0);
    jal(0x234F80, gen::fn_sub_21EAC0_0021eac0);
    a0 = s5;
    a1 = 9;
    jal(0x234F90, gen::fn_sub_21CCA0_0021cca0);
    a0 = addiu(s1, 8288);
    a1 = v0;
    jal(0x234FA0, gen::fn_sub_21D3B0_0021d3b0);
    a0 = 30;
    jal(0x234FAC, gen::fn_sub_21EA00_0021ea00);
    a0 = addiu(s1, 8288);
    mov_s(F12, F0);
    jal(0x234FBC, gen::fn_sub_21EAC0_0021eac0);
    jal(0x234FC4, gen::fn_sub_236390_00236390);
    lw(v1, s1, 0);
    v1 = v1 | 0x1;
    sw(v1, s1, 0);
    ld(ra, sp, 112);
    lq(s6, sp, 96);
    lq(s5, sp, 80);
    lq(s4, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 128);
    return;
}

// sub_235010 [panel step]: while the panel is open (flag 0x1) runs its open (kind 1) / close (kind 2) animation, +9832
// counting to 10 and then clearing flag 0x2, and draws it (sub_236390).
void Cpu::sub_235010() {
    enter(5);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    lw(v1, gp, kGpBrPanel);
    if (v1 == 0) {
        charge(5);
        kassert(0x235030, kBrPanelC, 153);
    }
    charge(6);
    lw(a1, gp, kGpBrPanel);
    lw(a0, a1, 0);
    v1 = ~a0;
    v1 = v1 & 0x1;
    if (v1 != 0) goto L_002350dc;
    charge(4);
    lw(v1, a1, 9836);
    v0 = 2;
    if (v1 != v0) {
        charge(3);
        v0 = 1;
        if (v1 != v0) {
            charge(2);
            goto L_002350d4;
        }
        charge(4);
        lw(v0, a1, 9832);
        at = slti(v0, 10);
        if (at != 0) {
            charge(4);
            v0 = addiu(v0, 1);
            sw(v0, a1, 9832);
            goto L_002350d4;
        }
        charge(5);
        v0 = si(-3);
        v0 = a0 & v0;
        sw(v0, a1, 0);
        goto L_002350d4;
    }
    charge(4);
    lw(v0, a1, 9832);
    at = slti(v0, 10);
    if (at != 0) {
        charge(4);
        v0 = addiu(v0, 1);
        sw(v0, a1, 9832);
        goto L_002350d4;
    }
    charge(3);
    v0 = si(-3);
    v0 = a0 & v0;
    sw(v0, a1, 0);
L_002350d4:
    charge(2);
    jal(0x2350D4, gen::fn_sub_236390_00236390);
L_002350dc:
    charge(4);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_2361D0: the panel cell of index for kind 0 (index + 13) or 1 (index) of result sprite file 1 (sub_21CCA0), set up
// on sprite (sub_21D3B0).
void Cpu::sub_2361D0() {
    enter(15);
    sp = addiu(sp, -80);
    sd(ra, sp, 64);
    sq(s3, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s3 = a0;
    s2 = a1;
    s1 = a2;
    a0 = 1;
    jal(0x2361F8, gen::fn_sub_234570_00234570);
    v1 = 1;
    if (s1 != v1) {
        charge(2);
        if (s1 != 0) {
            charge(2);
            goto L_0023624c;
        }
        charge(7);
        a1 = addiu(s2, 13);
        a0 = v0;
        jal(0x236224, gen::fn_sub_21CCA0_0021cca0);
        s0 = v0;
        goto L_0023624c;
    }
    charge(5);
    a0 = v0;
    a1 = s2;
    jal(0x236240, gen::fn_sub_21CCA0_0021cca0);
    s0 = v0;
L_0023624c:
    charge(12);
    a0 = s3;
    a1 = s0;
    jal(0x236254, gen::fn_sub_21D3B0_0021d3b0);
    ld(ra, sp, 64);
    lq(s3, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 80);
    return;
}

// sub_236280 [open the panel]: +9832 = 0, kind +9836 = 1, flag 0x2.
void Cpu::sub_236280() {
    enter(5);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    lw(v1, gp, kGpBrPanel);
    if (v1 == 0) {
        charge(5);
        kassert(0x2362A0, kBrPanelC, 153);
    }
    charge(11);
    lw(a0, gp, kGpBrPanel);
    sw(zero, a0, 9832);
    v1 = 1;
    sw(v1, a0, 9836);
    lw(v1, a0, 0);
    v1 = v1 | 0x2;
    sw(v1, a0, 0);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_2362E0 [close the panel]: +9832 = 0, kind +9836 = 2, flag 0x2.
void Cpu::sub_2362E0() {
    enter(5);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    lw(v1, gp, kGpBrPanel);
    if (v1 == 0) {
        charge(5);
        kassert(0x236300, kBrPanelC, 153);
    }
    charge(11);
    lw(a0, gp, kGpBrPanel);
    sw(zero, a0, 9832);
    v1 = 2;
    sw(v1, a0, 9836);
    lw(v1, a0, 0);
    v1 = v1 | 0x2;
    sw(v1, a0, 0);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_236340: the panel's flag 0x2 (animating).
void Cpu::sub_236340() {
    enter(5);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    lw(v0, gp, kGpBrPanel);
    if (v0 == 0) {
        charge(5);
        kassert(0x236360, kBrPanelC, 153);
    }
    charge(7);
    lw(v0, gp, kGpBrPanel);
    lw(v0, v0, 0);
    v0 = v0 & 0x2;
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// =================================================================================================================
// bp_ifont.c: the panel's digit font
// =================================================================================================================

// bpIfontSetDigitQuad: the four 64-byte vertices of a digit sprite (glyph digit + 11 of the font's SPR file,
// sprFontGetFile): +16 / +20 the UVs from the glyph rectangle over its texture's size, +24 q = 1 / (camera +128)
// (sub_198590), +8 = *(float*)0x960088, +32..+44 the colour 255.0 x 4.
void Cpu::bpIfontSetDigitQuad() {
    enter(91);
    sp = addiu(sp, -80);
    sd(ra, sp, 64);
    sq(s2, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F20, sp, 0);
    s0 = a0;
    s2 = a1;
    s1 = a2;
    jal(0x238FF4, gen::fn_sub_198590_00198590);
    v1 = lui(0x3F80);
    mtc1(v1, F1);
    lwc1(F0, v0, 128);
    div_s(F20, F1, F0);
    a0 = s1;
    jal(0x239018, gen::fn_sprFontGetFile_001120a0);
    v1 = addiu(s2, 11);
    a0 = sll(v1, 7);
    lw(v1, v0, 388);
    a0 = addu(v1, a0);
    lw(v1, a0, 20);
    v1 = sll(v1, 2);
    v1 = addu(v1, v0);
    lw(v1, v1, 260);
    lwc1(F0, v1, 12);
    lwc1(F1, a0, 84);
    cvt_s_w(F1, F1);
    cvt_s_w(F5, F0);
    div_s(F4, F1, F5);
    lwc1(F0, v1, 16);
    lwc1(F1, a0, 88);
    cvt_s_w(F2, F1);
    cvt_s_w(F1, F0);
    div_s(F3, F2, F1);
    lwc1(F0, a0, 92);
    cvt_s_w(F0, F0);
    div_s(F2, F0, F5);
    lwc1(F0, a0, 96);
    cvt_s_w(F0, F0);
    div_s(F1, F0, F1);
    swc1(F4, s0, 16);
    swc1(F3, s0, 20);
    swc1(F20, s0, 24);
    a0 = lui(0x96);
    a0 = addiu(a0, 136);
    lwc1(F0, a0, 0);
    swc1(F0, s0, 8);
    v1 = lui(0x437F);
    sw(v1, s0, 32);
    sw(v1, s0, 36);
    sw(v1, s0, 40);
    sw(v1, s0, 44);
    swc1(F2, s0, 80);
    swc1(F3, s0, 84);
    swc1(F20, s0, 88);
    lwc1(F0, a0, 0);
    swc1(F0, s0, 72);
    sw(v1, s0, 96);
    sw(v1, s0, 100);
    sw(v1, s0, 104);
    sw(v1, s0, 108);
    swc1(F2, s0, 144);
    swc1(F1, s0, 148);
    swc1(F20, s0, 152);
    lwc1(F0, a0, 0);
    swc1(F0, s0, 136);
    sw(v1, s0, 160);
    sw(v1, s0, 164);
    sw(v1, s0, 168);
    sw(v1, s0, 172);
    swc1(F4, s0, 208);
    swc1(F1, s0, 212);
    swc1(F20, s0, 216);
    lwc1(F0, a0, 0);
    swc1(F0, s0, 200);
    sw(v1, s0, 224);
    sw(v1, s0, 228);
    sw(v1, s0, 232);
    sw(v1, s0, 236);
    ld(ra, sp, 64);
    lq(s2, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 80);
    return;
}

// sub_239140: the font file's +260 (its texture table).
void Cpu::sub_239140() {
    enter(9);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    jal(0x239148, gen::fn_sprFontGetFile_001120a0);
    lw(v0, v0, 260);
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// =================================================================================================================
// brp_birth.c: the persona birth on level-up (gp-18880)
// =================================================================================================================

// sub_24A870 [persona birth: set up]: the camera (sub_198590; sub_4C9D70(camera, 100.0), sub_4C9DB0(camera, 1000.0);
// its frame through sub_4CB890(frame, 0x68E908 vector, 0) with $f12 = 180.0 and sub_4CB750(frame, 0x68E8F8 vector, 2)),
// the persona model for mode +0 (0: sub_209F00 + sub_20C590 with the persona id +12; 1: sub_20A800 + sub_20C5F0(0,
// 14)), sub_20CD50(model, +1564), the model's position / scale words, sub_1085C0, sub_23D240, +20 = 0, the effect of
// sub_24BF20(0) (sub_34FCD0 into +4044, sub_34FF90 with colour 255 x 4); flags 0x40 | 0x1, state +8 = 1.
void Cpu::sub_24A870() {
    enter(8);
    sp = addiu(sp, -96);
    sd(ra, sp, 48);
    sq(s2, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    lw(v0, gp, kGpBrpBirth);
    if (v0 == 0) {
        charge(5);
        kassert(0x24A89C, kBrpBirthC, 127);
    }
    charge(43);
    lw(s0, gp, kGpBrpBirth);
    v0 = lui(0x69);
    ld(v1, v0, -5896);
    v0 = lui(0x69);
    lwc1(F0, v0, -5888);
    sd(v1, sp, 80);
    swc1(F0, sp, 88);
    v0 = lui(0x69);
    ld(v1, v0, -5880);
    v0 = lui(0x69);
    lwc1(F0, v0, -5872);
    sd(v1, sp, 64);
    swc1(F0, sp, 72);
    jal(0x24A8D8, gen::fn_sub_198590_00198590);
    s2 = v0;
    v0 = lui(0x42C8);
    mtc1(v0, F12);
    a0 = s2;
    jal(0x24A8F0, gen::fn_sub_4C9D70_004c9d70);
    v0 = lui(0x447A);
    mtc1(v0, F12);
    a0 = s2;
    jal(0x24A904, gen::fn_sub_4C9DB0_004c9db0);
    lw(s2, s2, 4);
    v0 = lui(0x4334);
    mtc1(v0, F12);
    a0 = s2;
    a1 = addiu(sp, 64);
    a2 = 0;
    jal(0x24A924, gen::fn_sub_4CB890_004cb890);
    a0 = s2;
    a1 = addiu(sp, 80);
    a2 = 2;
    jal(0x24A938, gen::fn_sub_4CB750_004cb750);
    lw(v1, s0, 0);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
            goto L_0024a9ac;
        }
        charge(10);
        a0 = addiu(s0, 28);
        jal(0x24A964, gen::fn_sub_209F00_00209f00);
        s1 = addiu(s0, 28);
        a0 = s1;
        lhu(a1, s0, 12);
        jal(0x24A978, gen::fn_sub_20C590_0020c590);
        goto L_0024a9ac;
    }
    charge(9);
    a0 = addiu(s0, 28);
    jal(0x24A98C, gen::fn_sub_20A800_0020a800);
    s1 = addiu(s0, 28);
    a0 = s1;
    a1 = 0;
    a2 = 14;
    jal(0x24A9A4, gen::fn_sub_20C5F0_0020c5f0);
L_0024a9ac:
    charge(57);
    a0 = s1;
    a1 = addiu(s0, 1564);
    jal(0x24A9B4, gen::fn_sub_20CD50_0020cd50);
    v1 = lui(0x43FA);
    sw(v1, s0, 4016);
    v0 = lui(0x42C8);
    sw(v0, s0, 4020);
    sw(v1, s0, 4024);
    sw(zero, s1, 32);
    sw(v0, s1, 36);
    sw(zero, s1, 40);
    v0 = lui(0x3F80);
    sw(v0, s1, 28);
    sw(zero, s1, 16);
    sw(zero, s1, 20);
    sw(zero, s1, 24);
    v0 = lui(0x4120);
    sw(v0, s1, 44);
    sw(v0, s1, 48);
    sw(v0, s1, 52);
    jal(0x24AA00, gen::fn_sub_1085C0_001085c0);
    jal(0x24AA08, gen::fn_sub_23D240_0023d240);
    sw(zero, s0, 20);
    a0 = 0;
    jal(0x24AA18, gen::fn_sub_24BF20_0024bf20);
    a0 = v0;
    jal(0x24AA24, gen::fn_sub_34FCD0_0034fcd0);
    sw(v0, s0, 4044);
    lw(v0, s0, 4);
    v0 = v0 | 0x40;
    sw(v0, s0, 4);
    v0 = 255;
    sb(v0, sp, 92);
    sb(v0, sp, 93);
    sb(v0, sp, 94);
    sb(v0, sp, 95);
    lw(a0, s0, 4044);
    a1 = addiu(sp, 92);
    jal(0x24AA58, gen::fn_sub_34FF90_0034ff90);
    lw(v1, s0, 4);
    v1 = v1 | 0x1;
    sw(v1, s0, 4);
    v1 = 1;
    sw(v1, s0, 8);
    ld(ra, sp, 48);
    lq(s2, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 96);
    return;
}

// sub_24AA90 [persona birth: finish]: sub_108570, sub_108670(2), sub_1085C0, flag 0x1, state 8.
void Cpu::sub_24AA90() {
    enter(6);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    lw(v0, gp, kGpBrpBirth);
    if (v0 == 0) {
        charge(5);
        kassert(0x24AAB4, kBrpBirthC, 127);
    }
    charge(18);
    lw(s0, gp, kGpBrpBirth);
    jal(0x24AAC0, gen::fn_sub_108570_00108570);
    a0 = 2;
    jal(0x24AACC, gen::fn_sub_108670_00108670);
    jal(0x24AAD4, gen::fn_sub_1085C0_001085c0);
    lw(v1, s0, 4);
    v1 = v1 | 0x1;
    sw(v1, s0, 4);
    v1 = 8;
    sw(v1, s0, 8);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
    return;
}

// sub_24AB10 [persona birth: start]: +12 = id, the status screen (sub_3CDA60(0, 1) into +0x10000 - 15008, sub_3CDBA0
// with the id; flag 0x80), loads brp_birth.bin (sub_24BE40), sub_21AB80(id), mode +0 = 0, flag 0x2.
void Cpu::sub_24AB10() {
    enter(8);
    sp = addiu(sp, -48);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    lw(v0, gp, kGpBrpBirth);
    if (v0 == 0) {
        charge(5);
        kassert(0x24AB3C, kBrpBirthC, 127);
    }
    charge(33);
    lw(s0, gp, kGpBrpBirth);
    sh(s1, s0, 12);
    a0 = 0;
    a1 = 1;
    jal(0x24AB54, gen::fn_sub_3CDA60_003cda60);
    v1 = lui(0x1);
    v1 = addu(s0, v1);
    sw(v0, v1, -15008);
    lw(v0, s0, 4);
    v0 = v0 | 0x80;
    sw(v0, s0, 4);
    v0 = lui(0x1);
    v0 = addu(s0, v0);
    lw(a0, v0, -15008);
    lhu(a1, s0, 12);
    jal(0x24AB84, gen::fn_sub_3CDBA0_003cdba0);
    jal(0x24AB8C, gen::fn_sub_24BE40_0024be40);
    a0 = s1;
    jal(0x24AB98, gen::fn_sub_21AB80_0021ab80);
    sw(zero, s0, 0);
    lw(v1, s0, 4);
    v1 = v1 | 0x2;
    sw(v1, s0, 4);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 48);
    return;
}

// sub_24ABD0 [persona birth: start, mode 1]: loads brp_birth.bin, sub_21A920(0, 14), mode +0 = 1, flag 0x2.
void Cpu::sub_24ABD0() {
    enter(6);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    lw(v0, gp, kGpBrpBirth);
    if (v0 == 0) {
        charge(5);
        kassert(0x24ABF4, kBrpBirthC, 127);
    }
    charge(17);
    lw(s0, gp, kGpBrpBirth);
    jal(0x24AC00, gen::fn_sub_24BE40_0024be40);
    a0 = 0;
    a1 = 14;
    jal(0x24AC10, gen::fn_sub_21A920_0021a920);
    v1 = 1;
    sw(v1, s0, 0);
    lw(v1, s0, 4);
    v1 = v1 | 0x2;
    sw(v1, s0, 4);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
    return;
}

// sub_24AC40: the birth work's flag 0x2.
void Cpu::sub_24AC40() {
    enter(5);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    lw(v0, gp, kGpBrpBirth);
    if (v0 == 0) {
        charge(5);
        kassert(0x24AC60, kBrpBirthC, 127);
    }
    charge(7);
    lw(v0, gp, kGpBrpBirth);
    lw(v0, v0, 4);
    v0 = v0 & 0x2;
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_24ADF0 [persona birth: update]: the per-frame helpers (sub_24BB30, sub_20D820, sub_219D90); while loading (flag
// 0x2) waits for the status screen (sub_3CDC80 / sub_3CDCD0, flag 0x4), the model (sub_21A120, flag 0x8) and brp_res
// (sub_24BED0), then clears 0x2; then, while the state +8 is not 0, sub_2392D0 and the 12-state sequence of jump table
// 0x7B78C0 (the effect layers sub_34FCD0 / sub_34FDF0 / sub_34FF90 with the SFX sub_10A4E0, the message window with the
// persona's name sub_3C72D0 .. sub_3C77A0, the status screen sub_3CDBA0 / sub_3CDE00), with the inner switches of jump
// tables 0x7B7890 / 0x7B7860 (the model's orbit through sinf / cosf, sub_20CC80, sub_4BDDE0).
void Cpu::sub_24ADF0() {
    enter(10);
    sp = addiu(sp, -96);
    sd(ra, sp, 48);
    sq(s1, sp, 32);
    sq(s0, sp, 16);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    lw(v0, gp, kGpBrpBirth);
    if (v0 == 0) {
        charge(5);
        kassert(0x24AE24, kBrpBirthC, 127);
    }
    charge(17);
    lw(s0, gp, kGpBrpBirth);
    v0 = lui(0x69);
    ld(v1, v0, -5864);
    v0 = lui(0x69);
    lwc1(F0, v0, -5856);
    sd(v1, sp, 80);
    swc1(F0, sp, 88);
    jal(0x24AE48, gen::fn_sub_24BB30_0024bb30);
    jal(0x24AE50, gen::fn_sub_20D820_0020d820);
    jal(0x24AE58, gen::fn_sub_219D90_00219d90);
    lw(a1, s0, 4);
    v1 = a1 & 0x2;
    if (v1 == 0) goto L_0024afb8;
    charge(4);
    lw(a0, s0, 0);
    v1 = 1;
    if (a0 == v1) goto L_0024af5c;
    charge(2);
    if (a0 != 0) {
        charge(2);
        goto L_0024afb8;
    }
    charge(4);
    v1 = ~a1;
    v1 = v1 & 0x4;
    if (v1 != 0) {
        charge(7);
        v0 = lui(0x1);
        v0 = addu(s0, v0);
        lw(a0, v0, -15008);
        jal(0x24AEAC, gen::fn_sub_3CDC80_003cdc80);
        if (v0 != 0) goto L_0024afb8;
        charge(11);
        v0 = lui(0x1);
        v0 = addu(s0, v0);
        lw(a0, v0, -15008);
        a1 = 0;
        a2 = 0;
        a3 = 1;
        jal(0x24AED4, gen::fn_sub_3CDCD0_003cdcd0);
        lw(v1, s0, 4);
        v1 = v1 | 0x4;
        sw(v1, s0, 4);
    }
    charge(5);
    lw(v1, s0, 4);
    v1 = ~v1;
    v1 = v1 & 0x8;
    if (v1 == 0) goto L_0024af18;
    charge(4);
    jal(0x24AEFC, gen::fn_sub_21A120_0021a120);
    if (v0 != 0) goto L_0024af18;
    charge(3);
    lw(v1, s0, 4);
    v1 = v1 | 0x8;
    sw(v1, s0, 4);
L_0024af18:
    charge(4);
    lw(a0, s0, 4);
    v1 = a0 & 0x4;
    if (v1 == 0) goto L_0024afb8;
    charge(3);
    v1 = a0 & 0x8;
    if (v1 == 0) goto L_0024afb8;
    charge(4);
    jal(0x24AF34, gen::fn_sub_24BED0_0024bed0);
    if (v0 != 0) goto L_0024afb8;
    charge(6);
    lw(a0, s0, 4);
    v1 = si(-3);
    v1 = a0 & v1;
    sw(v1, s0, 4);
    goto L_0024afb8;
L_0024af5c:
    charge(4);
    v1 = ~a1;
    v1 = v1 & 0x8;
    if (v1 == 0) goto L_0024af88;
    charge(4);
    jal(0x24AF6C, gen::fn_sub_21A120_0021a120);
    if (v0 != 0) goto L_0024af88;
    charge(3);
    lw(v1, s0, 4);
    v1 = v1 | 0x8;
    sw(v1, s0, 4);
L_0024af88:
    charge(4);
    lw(v1, s0, 4);
    v1 = v1 & 0x8;
    if (v1 == 0) goto L_0024afb8;
    charge(4);
    jal(0x24AF98, gen::fn_sub_24BED0_0024bed0);
    if (v0 != 0) goto L_0024afb8;
    charge(4);
    lw(a0, s0, 4);
    v1 = si(-3);
    v1 = a0 & v1;
    sw(v1, s0, 4);
L_0024afb8:
    charge(3);
    lw(v1, s0, 8);
    if (v1 == 0) goto L_0024b874;
    charge(6);
    jal(0x24AFC4, gen::fn_sub_2392D0_002392d0);
    lw(v0, s0, 8);
    at = sltiu(v0, 12);
    if (at == 0) goto L_0024b548;
    charge(7);
    v1 = lui(0x7B);
    v1 = addiu(v1, 30912);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    switch (v0.u()) {  // the entry of jump table 0x7B78C0
    case 0x24AFF8: goto L_0024aff8;
    case 0x24B01C: goto L_0024b01c;
    case 0x24B050: goto L_0024b050;
    case 0x24B09C: goto L_0024b09c;
    case 0x24B224: goto L_0024b224;
    case 0x24B2E4: goto L_0024b2e4;
    case 0x24B3BC: goto L_0024b3bc;
    case 0x24B424: goto L_0024b424;
    case 0x24B474: goto L_0024b474;
    case 0x24B548: goto L_0024b548;
    default: rt::lookup_func(v0.u())(c); return;
    }
L_0024aff8:
    charge(4);
    jal(0x24AFF8, gen::fn_sub_108710_00108710);
    if (v0 == 0) goto L_0024b548;
    charge(5);
    sw(zero, s0, 16);
    v0 = 2;
    sw(v0, s0, 8);
    goto L_0024b548;
L_0024b01c:
    charge(4);
    lw(v0, s0, 16);
    at = slti(v0, 30);
    if (at != 0) {
        charge(4);
        v0 = addiu(v0, 1);
        sw(v0, s0, 16);
        goto L_0024b548;
    }
    charge(5);
    sw(zero, s0, 16);
    v0 = 3;
    sw(v0, s0, 8);
    goto L_0024b548;
L_0024b050:
    charge(4);
    lw(v0, s0, 16);
    at = slti(v0, 40);
    if (at != 0) {
        charge(4);
        v0 = addiu(v0, 1);
        sw(v0, s0, 16);
        goto L_0024b548;
    }
    charge(11);
    a0 = 1;
    a1 = 0;
    a2 = 8;
    a3 = 5;
    jal(0x24B080, gen::fn_sub_10A4E0_0010a4e0);
    sw(zero, s0, 16);
    v0 = 4;
    sw(v0, s0, 8);
    goto L_0024b548;
L_0024b09c:
    charge(4);
    lw(v0, s0, 16);
    at = slti(v0, 20);
    if (at == 0) goto L_0024b154;
    charge(23);
    v0 = addiu(v0, 1);
    sw(v0, s0, 16);
    v0 = 255;
    sb(v0, sp, 92);
    sb(zero, sp, 93);
    sb(zero, sp, 94);
    lwc1(F0, s0, 16);
    cvt_s_w(F0, F0);
    v0 = lui(0x437F);
    mtc1(v0, F2);
    mul_s(F1, F2, F0);
    v0 = lui(0x41A0);
    mtc1(v0, F0);
    div_s(F0, F1, F0);
    sub_s(F1, F2, F0);
    v0 = lui(0x4F00);
    mtc1(v0, F0);
    c_le_s(F0, F1);
    if (!cop1_cond()) {
        charge(6);
        cvt_w_s(F0, F1);
        mfc1(v1, F0);
        v1 = v1 & 0xFF;
        goto L_0024b138;
    }
    charge(6);
    sub_s(F0, F1, F0);
    cvt_w_s(F0, F0);
    mfc1(v1, F0);
    v0 = lui(0x8000);
    v1 = v1 | v0;
    v1 = v1 & 0xFF;
L_0024b138:
    charge(7);
    sb(v1, sp, 95);
    lw(a0, s0, 4044);
    a1 = addiu(sp, 92);
    jal(0x24B144, gen::fn_sub_34FF90_0034ff90);
    goto L_0024b548;
L_0024b154:
    charge(4);
    lw(v0, s0, 0);
    a0 = 1;
    if (v0 != a0) {
        charge(2);
        if (v0 != 0) {
            charge(2);
            goto L_0024b1fc;
        }
        charge(5);
        sw(zero, s0, 16);
        v0 = 5;
        sw(v0, s0, 8);
        goto L_0024b1fc;
    }
    charge(29);
    jal(0x24B188, gen::fn_sub_24BF20_0024bf20);
    a0 = v0;
    jal(0x24B194, gen::fn_sub_34FCD0_0034fcd0);
    sw(v0, s0, 4040);
    lw(v0, s0, 4);
    v0 = v0 | 0x20;
    sw(v0, s0, 4);
    sw(zero, sp, 64);
    v0 = lui(0x42C8);
    sw(v0, sp, 68);
    sw(zero, sp, 72);
    lw(a0, s0, 4040);
    a1 = addiu(sp, 64);
    jal(0x24B1C4, gen::fn_sub_34FDF0_0034fdf0);
    a0 = 1;
    a1 = 0;
    a2 = 8;
    a3 = 6;
    jal(0x24B1DC, gen::fn_sub_10A4E0_0010a4e0);
    lw(v1, s0, 4);
    v0 = si(-2);
    v0 = v1 & v0;
    sw(v0, s0, 4);
    v0 = 7;
    sw(v0, s0, 8);
L_0024b1fc:
    charge(10);
    sb(zero, sp, 92);
    sb(zero, sp, 93);
    sb(zero, sp, 94);
    sb(zero, sp, 95);
    lw(a0, s0, 4044);
    a1 = addiu(sp, 92);
    jal(0x24B214, gen::fn_sub_34FF90_0034ff90);
    goto L_0024b548;
L_0024b224:
    charge(4);
    lw(v0, s0, 16);
    at = slti(v0, 30);
    if (at != 0) {
        charge(4);
        v0 = addiu(v0, 1);
        sw(v0, s0, 16);
        goto L_0024b548;
    }
    charge(5);
    lw(v0, s0, 4);
    v0 = ~v0;
    v0 = v0 & 0x10;
    if (v0 == 0) {
        charge(5);
        kassert(0x24B264, kBrpBirthC, 447);
    }
    charge(30);
    a0 = 2;
    jal(0x24B270, gen::fn_sub_24BF20_0024bf20);
    a0 = v0;
    jal(0x24B27C, gen::fn_sub_34FCD0_0034fcd0);
    sw(v0, s0, 4036);
    lw(v0, s0, 4);
    v0 = v0 | 0x10;
    sw(v0, s0, 4);
    sw(zero, sp, 64);
    v0 = lui(0x42C8);
    sw(v0, sp, 68);
    v0 = lui(0xC3FA);
    sw(v0, sp, 72);
    lw(a0, s0, 4036);
    a1 = addiu(sp, 64);
    jal(0x24B2B0, gen::fn_sub_34FDF0_0034fdf0);
    a0 = 1;
    a1 = 0;
    a2 = 8;
    a3 = 6;
    jal(0x24B2C8, gen::fn_sub_10A4E0_0010a4e0);
    sw(zero, s0, 16);
    v0 = 6;
    sw(v0, s0, 8);
    goto L_0024b548;
L_0024b2e4:
    charge(4);
    lw(v1, s0, 16);
    v0 = 30;
    if (v1 == v0) {
        charge(11);
        v0 = lui(0x1);
        v0 = addu(s0, v0);
        lw(a0, v0, -15008);
        a1 = 1;
        jal(0x24B304, gen::fn_sub_3CDE00_003cde00);
        lw(v0, s0, 4);
        v0 = ~v0;
        v0 = v0 & 0x100;
        if (v0 == 0) {
            charge(5);
            kassert(0x24B32C, kBrpBirthC, 470);
        }
        charge(19);
        a0 = 3;
        jal(0x24B338, gen::fn_sub_24BF20_0024bf20);
        a0 = v0;
        jal(0x24B344, gen::fn_sub_34FCD0_0034fcd0);
        sw(v0, s0, 4048);
        lw(v0, s0, 4);
        v0 = v0 | 0x100;
        sw(v0, s0, 4);
        sw(zero, sp, 64);
        v0 = lui(0xC270);
        sw(v0, sp, 68);
        v0 = lui(0xC248);
        sw(v0, sp, 72);
        lw(a0, s0, 4048);
        a1 = addiu(sp, 64);
        jal(0x24B378, gen::fn_sub_34FDF0_0034fdf0);
    }
    charge(4);
    lw(v0, s0, 16);
    at = slti(v0, 60);
    if (at != 0) {
        charge(4);
        v0 = addiu(v0, 1);
        sw(v0, s0, 16);
        goto L_0024b548;
    }
    charge(7);
    sw(zero, s0, 16);
    jal(0x24B3A4, gen::fn_sub_24BF80_0024bf80);
    v0 = 10;
    sw(v0, s0, 8);
    goto L_0024b548;
L_0024b3bc:
    charge(4);
    jal(0x24B3BC, gen::fn_sub_24C040_0024c040);
    if (v0 != 0) goto L_0024b548;
    charge(22);
    jal(0x24B3CC, gen::fn_sub_24C090_0024c090);
    a0 = v0;
    jal(0x24B3D8, gen::fn_sub_3C72D0_003c72d0);
    lhu(a0, s0, 12);
    jal(0x24B3E4, gen::fn_sub_173220_00173220);
    a0 = 1;
    a1 = v0;
    jal(0x24B3F4, gen::fn_sub_3C7BC0_003c7bc0);
    lhu(a0, s0, 12);
    jal(0x24B400, gen::fn_sub_17D790_0017d790);
    a0 = v0;
    jal(0x24B40C, gen::fn_msgWinRequestMessage_003c7430);
    v0 = 11;
    sw(v0, s0, 8);
    goto L_0024b548;
L_0024b424:
    charge(7);
    a0 = 1;
    jal(0x24B428, gen::fn_sub_3C7990_003c7990);
    jal(0x24B430, gen::fn_sub_3C7850_003c7850);
    if (v0 != 0) goto L_0024b548;
    charge(13);
    a0 = 1;
    jal(0x24B444, gen::fn_msgWinClose_003c7650);
    jal(0x24B44C, gen::fn_sub_3C77A0_003c77a0);
    v0 = 7;
    sw(v0, s0, 8);
    lw(v1, s0, 4);
    v0 = si(-2);
    v0 = v1 & v0;
    sw(v0, s0, 4);
    goto L_0024b548;
L_0024b474:
    charge(4);
    jal(0x24B474, gen::fn_sub_108710_00108710);
    if (v0 == 0) goto L_0024b548;
    charge(4);
    lw(v0, s0, 4);
    v0 = v0 & 0x10;
    if (v0 != 0) {
        charge(7);
        lw(a0, s0, 4036);
        jal(0x24B498, gen::fn_sub_34FCF0_0034fcf0);
        lw(v1, s0, 4);
        v0 = si(-17);
        v0 = v1 & v0;
        sw(v0, s0, 4);
    }
    charge(4);
    lw(v0, s0, 4);
    v0 = v0 & 0x100;
    if (v0 != 0) {
        charge(7);
        lw(a0, s0, 4048);
        jal(0x24B4C4, gen::fn_sub_34FCF0_0034fcf0);
        lw(v1, s0, 4);
        v0 = si(-257);
        v0 = v1 & v0;
        sw(v0, s0, 4);
    }
    charge(4);
    lw(v0, s0, 4);
    v0 = v0 & 0x20;
    if (v0 != 0) {
        charge(7);
        lw(a0, s0, 4040);
        jal(0x24B4F0, gen::fn_sub_34FCF0_0034fcf0);
        lw(v1, s0, 4);
        v0 = si(-33);
        v0 = v1 & v0;
        sw(v0, s0, 4);
    }
    charge(4);
    lw(v0, s0, 4);
    v0 = v0 & 0x40;
    if (v0 != 0) {
        charge(7);
        lw(a0, s0, 4044);
        jal(0x24B51C, gen::fn_sub_34FCF0_0034fcf0);
        lw(v1, s0, 4);
        v0 = si(-65);
        v0 = v1 & v0;
        sw(v0, s0, 4);
    }
    charge(5);
    lw(v1, s0, 4);
    v0 = si(-2);
    v0 = v1 & v0;
    sw(v0, s0, 4);
    sw(zero, s0, 8);
L_0024b548:
    charge(5);
    s1 = addiu(s0, 28);
    lw(v0, s0, 8);
    at = sltiu(v0, 9);
    if (at == 0) goto L_0024b660;
    charge(7);
    v1 = lui(0x7B);
    v1 = addiu(v1, 30864);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    switch (v0.u()) {  // the entry of jump table 0x7B7890
    case 0x24B578: goto L_0024b578;
    case 0x24B584: goto L_0024b584;
    case 0x24B5B0: goto L_0024b5b0;
    case 0x24B5C0: goto L_0024b5c0;
    case 0x24B5F0: goto L_0024b5f0;
    case 0x24B62C: goto L_0024b62c;
    case 0x24B660: goto L_0024b660;
    default: rt::lookup_func(v0.u())(c); return;
    }
L_0024b578:
    charge(3);
    mtc1(zero, F21);
    goto L_0024b660;
L_0024b584:
    charge(11);
    lwc1(F0, s0, 16);
    cvt_s_w(F1, F0);
    v0 = lui(0x4220);
    mtc1(v0, F0);
    div_s(F21, F1, F0);
    goto L_0024b660;
L_0024b5b0:
    charge(4);
    v0 = lui(0x3F80);
    mtc1(v0, F21);
    goto L_0024b660;
L_0024b5c0:
    charge(12);
    lwc1(F0, s0, 16);
    cvt_s_w(F1, F0);
    v0 = lui(0x4270);
    mtc1(v0, F0);
    div_s(F1, F1, F0);
    v0 = lui(0x3F80);
    mtc1(v0, F0);
    sub_s(F21, F0, F1);
    goto L_0024b660;
L_0024b5f0:
    charge(4);
    lw(v1, s0, 0);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
            goto L_0024b660;
        }
        charge(3);
        mtc1(zero, F21);
        goto L_0024b660;
    }
    charge(4);
    v0 = lui(0x3F80);
    mtc1(v0, F21);
    goto L_0024b660;
L_0024b62c:
    charge(4);
    lw(v1, s0, 0);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
            goto L_0024b660;
        }
        charge(3);
        mtc1(zero, F21);
        goto L_0024b660;
    }
    charge(2);
    v0 = lui(0x3F80);
    mtc1(v0, F21);
L_0024b660:
    charge(69);
    lw(v0, s0, 20);
    v0 = addiu(v0, 1);
    sw(v0, s0, 20);
    lwc1(F0, s0, 20);
    cvt_s_w(F1, F0);
    v0 = lui(0x4248);
    mtc1(v0, F0);
    div_s(F0, F1, F0);
    neg_s(F1, F0);
    v0 = lui(0x4000);
    mtc1(v0, F0);
    mul_s(F1, F0, F1);
    lwc1(F0, gp, -32184);
    mul_s(F22, F0, F1);
    mov_s(F12, F22);
    jal(0x24B6A4, gen::fn_sinf_0052e878);
    v0 = lui(0xC396);
    mtc1(v0, F1);
    mul_s(F0, F1, F0);
    swc1(F0, s0, 4016);
    mov_s(F12, F22);
    jal(0x24B6C4, gen::fn_cosf_0052e6d8);
    v0 = lui(0xC396);
    mtc1(v0, F1);
    mul_s(F0, F1, F0);
    swc1(F0, s0, 4024);
    lwc1(F0, s0, 20);
    cvt_s_w(F1, F0);
    v0 = lui(0x41F0);
    mtc1(v0, F0);
    div_s(F1, F1, F0);
    v0 = lui(0x4000);
    mtc1(v0, F0);
    mul_s(F1, F0, F1);
    lwc1(F0, gp, -32184);
    mul_s(F12, F0, F1);
    jal(0x24B710, gen::fn_cosf_0052e6d8);
    v0 = lui(0x43C8);
    mtc1(v0, F3);
    v0 = lui(0x42C8);
    mtc1(v0, F2);
    mtc1(zero, F1);
    adda_s(F1, F2);
    madd_s(F0, F3, F0);
    swc1(F0, s0, 4020);
    v0 = 255;
    sb(v0, sp, 92);
    sb(v0, sp, 93);
    sb(v0, sp, 94);
    v0 = lui(0x437F);
    mtc1(v0, F0);
    mul_s(F1, F0, F21);
    v0 = lui(0x4F00);
    mtc1(v0, F0);
    c_le_s(F0, F1);
    if (!cop1_cond()) {
        charge(6);
        cvt_w_s(F0, F1);
        mfc1(v1, F0);
        v1 = v1 & 0xFF;
        goto L_0024b7a4;
    }
    charge(6);
    sub_s(F0, F1, F0);
    cvt_w_s(F0, F0);
    mfc1(v1, F0);
    v0 = lui(0x8000);
    v1 = v1 | v0;
    v1 = v1 & 0xFF;
L_0024b7a4:
    charge(9);
    sb(v1, sp, 95);
    a0 = s1;
    a1 = addiu(sp, 92);
    jal(0x24B7B0, gen::fn_sub_20CC80_0020cc80);
    lw(v0, s0, 8);
    at = sltiu(v0, 9);
    if (at == 0) goto L_0024b834;
    charge(7);
    v1 = lui(0x7B);
    v1 = addiu(v1, 30816);
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    switch (v0.u()) {  // the entry of jump table 0x7B7860
    case 0x24B7E4: goto L_0024b7e4;
    case 0x24B7F4: goto L_0024b7f4;
    case 0x24B830: goto L_0024b830;
    case 0x24B834: goto L_0024b834;
    default: rt::lookup_func(v0.u())(c); return;
    }
L_0024b7e4:
    charge(4);
    v0 = lui(0x4334);
    mtc1(v0, F20);
    goto L_0024b834;
L_0024b7f4:
    charge(15);
    lwc1(F0, s0, 16);
    cvt_s_w(F1, F0);
    v0 = lui(0x41A0);
    mtc1(v0, F0);
    div_s(F2, F1, F0);
    v0 = lui(0x4334);
    mtc1(v0, F1);
    v0 = lui(0x3F80);
    mtc1(v0, F0);
    sub_s(F0, F0, F2);
    mul_s(F20, F1, F0);
    goto L_0024b834;
L_0024b830:
    charge(1);
    mtc1(zero, F20);
L_0024b834:
    charge(10);
    a0 = addiu(s1, 16);
    a1 = addiu(sp, 80);
    mov_s(F12, F20);
    a2 = 0;
    jal(0x24B844, gen::fn_sub_4BDDE0_004bdde0);
    lw(v1, s0, 4);
    v1 = v1 & 0x80;
    if (v1 == 0) goto L_0024b874;
    charge(6);
    v0 = lui(0x1);
    v0 = addu(s0, v0);
    lw(a0, v0, -15008);
    lhu(a1, s0, 12);
    jal(0x24B86C, gen::fn_sub_3CDBA0_003cdba0);
L_0024b874:
    charge(9);
    ld(ra, sp, 48);
    lq(s1, sp, 32);
    lq(s0, sp, 16);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 96);
    return;
}

// sub_24B8A0 [persona birth: draw]: while the state +8 is not 0: sub_23B990, the model (flag 0x8: sub_20AC90 /
// sub_20B250 on +28) and the effect layers +4036 (flag 0x10), +4048 (0x100, sub_34FF70 with gp-32632 first), +4040
// (0x20), +4044 (0x40), each sub_34FD30 then sub_34FD70(layer, 5).
void Cpu::sub_24B8A0() {
    enter(6);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    lw(v1, gp, kGpBrpBirth);
    if (v1 == 0) {
        charge(5);
        kassert(0x24B8C4, kBrpBirthC, 127);
    }
    charge(4);
    lw(s0, gp, kGpBrpBirth);
    lw(v1, s0, 8);
    if (v1 == 0) goto L_0024b9cc;
    charge(6);
    jal(0x24B8DC, gen::fn_sub_23B990_0023b990);
    lw(v1, s0, 4);
    v1 = v1 & 0x8;
    if (v1 != 0) {
        charge(6);
        a0 = addiu(s0, 28);
        jal(0x24B8F8, gen::fn_sub_20AC90_0020ac90);
        a0 = addiu(s0, 28);
        jal(0x24B904, gen::fn_sub_20B250_0020b250);
    }
    charge(4);
    lw(v1, s0, 4);
    v1 = v1 & 0x10;
    if (v1 != 0) {
        charge(7);
        lw(a0, s0, 4036);
        jal(0x24B920, gen::fn_sub_34FD30_0034fd30);
        lw(a0, s0, 4036);
        a1 = 5;
        jal(0x24B930, gen::fn_sub_34FD70_0034fd70);
    }
    charge(4);
    lw(v1, s0, 4);
    v1 = v1 & 0x100;
    if (v1 != 0) {
        charge(11);
        lw(a0, s0, 4048);
        lwc1(F12, gp, -32632);
        jal(0x24B950, gen::fn_sub_34FF70_0034ff70);
        lw(a0, s0, 4048);
        jal(0x24B95C, gen::fn_sub_34FD30_0034fd30);
        lw(a0, s0, 4048);
        a1 = 5;
        jal(0x24B96C, gen::fn_sub_34FD70_0034fd70);
    }
    charge(4);
    lw(v1, s0, 4);
    v1 = v1 & 0x20;
    if (v1 != 0) {
        charge(7);
        lw(a0, s0, 4040);
        jal(0x24B988, gen::fn_sub_34FD30_0034fd30);
        lw(a0, s0, 4040);
        a1 = 5;
        jal(0x24B998, gen::fn_sub_34FD70_0034fd70);
    }
    charge(4);
    lw(v1, s0, 4);
    v1 = v1 & 0x40;
    if (v1 == 0) goto L_0024b9cc;
    charge(7);
    lw(a0, s0, 4044);
    jal(0x24B9B4, gen::fn_sub_34FD30_0034fd30);
    lw(a0, s0, 4044);
    a1 = 5;
    jal(0x24B9C4, gen::fn_sub_34FD70_0034fd70);
L_0024b9cc:
    charge(5);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
    return;
}

// sub_24B9E0: the birth work's flag 0x1.
void Cpu::sub_24B9E0() {
    enter(5);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    lw(v0, gp, kGpBrpBirth);
    if (v0 == 0) {
        charge(5);
        kassert(0x24BA00, kBrpBirthC, 127);
    }
    charge(7);
    lw(v0, gp, kGpBrpBirth);
    lw(v0, v0, 4);
    v0 = v0 & 0x1;
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// =================================================================================================================
// brp_res.c: the persona-birth resources (gp-18876)
// =================================================================================================================

// sub_24BA30 [brp_res init]: clears res +0 / +4 and installs it at gp-18876.
void Cpu::sub_24BA30() {
    enter(5);
    sw(zero, a0, 0);
    sw(zero, a0, 4);
    sw(a0, gp, kGpBrpRes);
    return;
}

// sub_24BED0: brp_res flag 0x1.
void Cpu::sub_24BED0() {
    enter(5);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    lw(v0, gp, kGpBrpRes);
    if (v0 == 0) {
        charge(5);
        kassert(0x24BEF0, kBrpResC, 57);
    }
    charge(7);
    lw(v0, gp, kGpBrpRes);
    lw(v0, v0, 0);
    v0 = v0 & 0x1;
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_24BF20: brp_res +16 + 4 * i.
void Cpu::sub_24BF20() {
    enter(7);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    s0 = a0;
    lw(v0, gp, kGpBrpRes);
    if (v0 == 0) {
        charge(5);
        kassert(0x24BF48, kBrpResC, 57);
    }
    charge(9);
    lw(v1, gp, kGpBrpRes);
    v0 = sll(s0, 2);
    v0 = addu(v0, v1);
    lw(v0, v0, 16);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
    return;
}

// sub_24C040: brp_res flag 0x2.
void Cpu::sub_24C040() {
    enter(5);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    lw(v0, gp, kGpBrpRes);
    if (v0 == 0) {
        charge(5);
        kassert(0x24C060, kBrpResC, 57);
    }
    charge(7);
    lw(v0, gp, kGpBrpRes);
    lw(v0, v0, 0);
    v0 = v0 & 0x2;
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

// sub_24C090: brp_res +32 (the message file; K_Assert unless +4 has 0x2).
void Cpu::sub_24C090() {
    enter(6);
    sp = addiu(sp, -32);
    sd(ra, sp, 16);
    sq(s0, sp, 0);
    lw(v0, gp, kGpBrpRes);
    if (v0 == 0) {
        charge(5);
        kassert(0x24C0B4, kBrpResC, 57);
    }
    charge(5);
    lw(s0, gp, kGpBrpRes);
    lw(v0, s0, 4);
    v0 = v0 & 0x2;
    if (v0 == 0) {
        charge(5);
        kassert(0x24C0DC, kBrpResC, 206);
    }
    charge(6);
    lw(v0, s0, 32);
    ld(ra, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 32);
    return;
}

// =================================================================================================================
// bai_main.c: the AI-tactics banner (gp-18872)
// =================================================================================================================

// sub_24C100 [bai init]: work +4 = 0 and installs it at gp-18872.
void Cpu::sub_24C100() {
    enter(4);
    sw(zero, a0, 4);
    sw(a0, gp, kGpBai);
    return;
}

// sub_24C110 [AI banner: step]: while shown (flag 0x1) counts the frame +12 to 60 (then clears the flag), plays the SFX
// sub_10A4E0(1, 0, 7, 5) at frame 14, and slides / fades the banner by phase (frames 0-9 hidden, 10-14 in, 15-41 shown,
// 42-49 out; the direction from the kind +0), drawing its three rectangles (sub_21D8E0 / sub_21D950 / sub_21D890).
void Cpu::sub_24C110() {
    enter(9);
    sp = addiu(sp, -112);
    sd(ra, sp, 32);
    sq(s0, sp, 16);
    swc1(F22, sp, 8);
    swc1(F21, sp, 4);
    swc1(F20, sp, 0);
    lw(v1, gp, kGpBai);
    if (v1 == 0) {
        charge(5);
        kassert(0x24C140, kBaiMainC, 55);
    }
    charge(6);
    lw(s0, gp, kGpBai);
    lw(a0, s0, 4);
    v1 = ~a0;
    v1 = v1 & 0x1;
    if (v1 != 0) goto L_0024cc78;
    charge(4);
    lw(v1, s0, 12);
    at = slti(v1, 60);
    if (at != 0) {
        charge(4);
        v0 = addiu(v1, 1);
        sw(v0, s0, 12);
        goto L_0024c194;
    }
    charge(5);
    v1 = si(-2);
    v1 = a0 & v1;
    sw(v1, s0, 4);
    goto L_0024cc78;
L_0024c194:
    charge(4);
    lw(v1, s0, 12);
    v0 = 14;
    if (v1 == v0) {
        charge(6);
        a0 = 1;
        a1 = 0;
        a2 = 7;
        a3 = 5;
        jal(0x24C1B4, gen::fn_sub_10A4E0_0010a4e0);
    }
    charge(4);
    lw(v1, s0, 0);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
            goto L_0024c204;
        }
        charge(6);
        v0 = lui(0x4270);
        mtc1(v0, F21);
        v0 = lui(0xC220);
        mtc1(v0, F20);
        goto L_0024c204;
    }
    charge(4);
    v0 = lui(0xC270);
    mtc1(v0, F21);
    v0 = lui(0x4220);
    mtc1(v0, F20);
L_0024c204:
    charge(4);
    lw(v0, s0, 12);
    at = slti(v0, 10);
    if (at != 0) {
        charge(6);
        mtc1(zero, F22);
        mov_s(F4, F22);
        mov_s(F1, F22);
        goto L_0024c328;
    }
    charge(3);
    at = slti(v0, 15);
    if (at != 0) {
        charge(16);
        v0 = addiu(v0, -10);
        mtc1(v0, F0);
        cvt_s_w(F1, F0);
        v0 = lui(0x40A0);
        mtc1(v0, F0);
        div_s(F22, F1, F0);
        v0 = lui(0x3F80);
        mtc1(v0, F0);
        sub_s(F0, F0, F22);
        mul_s(F4, F21, F0);
        mul_s(F1, F20, F0);
        goto L_0024c328;
    }
    charge(3);
    at = slti(v0, 42);
    if (at != 0) {
        charge(7);
        v0 = lui(0x3F80);
        mtc1(v0, F22);
        mtc1(zero, F4);
        mov_s(F1, F4);
        goto L_0024c328;
    }
    charge(3);
    at = slti(v0, 50);
    if (at != 0) {
        charge(27);
        v0 = addiu(v0, -42);
        mtc1(v0, F0);
        cvt_s_w(F1, F0);
        v0 = lui(0x4100);
        mtc1(v0, F0);
        div_s(F3, F1, F0);
        v0 = lui(0x3F80);
        mtc1(v0, F0);
        sub_s(F22, F0, F3);
        v0 = lui(0x4060);
        mtc1(v0, F1);
        neg_s(F0, F21);
        mul_s(F0, F1, F0);
        lwc1(F2, gp, kGpScale4);
        mul_s(F0, F2, F0);
        mul_s(F4, F0, F3);
        v0 = lui(0x4040);
        mtc1(v0, F1);
        neg_s(F0, F20);
        mul_s(F0, F1, F0);
        mul_s(F0, F2, F0);
        mul_s(F1, F0, F3);
        goto L_0024c328;
    }
    charge(4);
    mtc1(zero, F22);
    mov_s(F4, F22);
    mov_s(F1, F22);
L_0024c328:
    charge(14);
    v0 = lui(0x4352);
    mtc1(v0, F0);
    add_s(F0, F0, F4);
    swc1(F0, sp, 80);
    v0 = lui(0x4332);
    mtc1(v0, F0);
    add_s(F0, F0, F1);
    swc1(F0, sp, 84);
    lw(v1, s0, 0);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
            goto L_0024c3a4;
        }
        charge(9);
        v0 = 417;
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
        swc1(F0, sp, 88);
        v0 = lui(0x437A);
        sw(v0, sp, 92);
        goto L_0024c3a4;
    }
    charge(4);
    v0 = lui(0x43D6);
    sw(v0, sp, 88);
    v0 = lui(0x4380);
    sw(v0, sp, 92);
L_0024c3a4:
    charge(18);
    a0 = addiu(s0, 272);
    a1 = addiu(sp, 80);
    jal(0x24C3AC, gen::fn_sub_21D8E0_0021d8e0);
    v0 = 255;
    sb(v0, sp, 108);
    sb(v0, sp, 109);
    sb(v0, sp, 110);
    v0 = lui(0x437F);
    mtc1(v0, F0);
    mul_s(F1, F0, F22);
    v0 = lui(0x4F00);
    mtc1(v0, F0);
    c_le_s(F0, F1);
    if (!cop1_cond()) {
        charge(6);
        cvt_w_s(F0, F1);
        mfc1(v1, F0);
        v1 = v1 & 0xFF;
        goto L_0024c41c;
    }
    charge(6);
    sub_s(F0, F1, F0);
    cvt_w_s(F0, F0);
    mfc1(v1, F0);
    v0 = lui(0x8000);
    v1 = v1 | v0;
    v1 = v1 & 0xFF;
L_0024c41c:
    charge(9);
    sb(v1, sp, 111);
    a0 = addiu(s0, 272);
    a1 = addiu(sp, 108);
    jal(0x24C428, gen::fn_sub_21D950_0021d950);
    lw(v0, s0, 12);
    at = slti(v0, 10);
    if (at != 0) {
        charge(7);
        mtc1(zero, F20);
        v0 = lui(0x3F80);
        mtc1(v0, F21);
        mov_s(F6, F21);
        goto L_0024c534;
    }
    charge(3);
    at = slti(v0, 15);
    if (at != 0) {
        charge(18);
        v0 = addiu(v0, -10);
        mtc1(v0, F0);
        cvt_s_w(F1, F0);
        v0 = lui(0x40A0);
        mtc1(v0, F0);
        div_s(F20, F1, F0);
        v0 = lui(0x3F80);
        mtc1(v0, F21);
        lwc1(F2, gp, -32004);
        sub_s(F1, F21, F20);
        mtc1(zero, F0);
        adda_s(F0, F21);
        madd_s(F6, F2, F1);
        goto L_0024c534;
    }
    charge(3);
    at = slti(v0, 45);
    if (at != 0) {
        charge(7);
        v0 = lui(0x3F80);
        mtc1(v0, F21);
        mov_s(F20, F21);
        mov_s(F6, F21);
        goto L_0024c534;
    }
    charge(3);
    at = slti(v0, 55);
    if (at != 0) {
        charge(15);
        v0 = addiu(v0, -45);
        mtc1(v0, F0);
        cvt_s_w(F1, F0);
        v0 = lui(0x4120);
        mtc1(v0, F0);
        div_s(F0, F1, F0);
        v0 = lui(0x3F80);
        mtc1(v0, F21);
        sub_s(F20, F21, F0);
        mov_s(F6, F21);
        goto L_0024c534;
    }
    charge(5);
    mtc1(zero, F20);
    v0 = lui(0x3F80);
    mtc1(v0, F21);
    mov_s(F6, F21);
L_0024c534:
    charge(8);
    v0 = lui(0x4352);
    sw(v0, sp, 80);
    v0 = lui(0x4332);
    sw(v0, sp, 84);
    lw(v1, s0, 0);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
            goto L_0024c598;
        }
        charge(9);
        v0 = 417;
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
        swc1(F0, sp, 88);
        v0 = lui(0x437A);
        sw(v0, sp, 92);
        goto L_0024c598;
    }
    charge(4);
    v0 = lui(0x43D6);
    sw(v0, sp, 88);
    v0 = lui(0x4380);
    sw(v0, sp, 92);
L_0024c598:
    charge(26);
    lwc1(F5, sp, 80);
    swc1(F5, sp, 48);
    lwc1(F4, sp, 84);
    swc1(F4, sp, 52);
    lwc1(F3, sp, 88);
    add_s(F0, F5, F3);
    swc1(F0, sp, 56);
    swc1(F4, sp, 60);
    swc1(F0, sp, 64);
    lwc1(F2, sp, 92);
    add_s(F0, F4, F2);
    swc1(F0, sp, 68);
    swc1(F5, sp, 72);
    swc1(F0, sp, 76);
    v1 = 0;
    v0 = lui(0x4000);
    mtc1(v0, F1);
    div_s(F0, F3, F1);
    add_s(F3, F5, F0);
    div_s(F0, F2, F1);
    add_s(F1, F4, F0);
    for (;;) {
        charge(3);
        v0 = slti(v1, 4);
        if (v0 == 0) {
            break;
        }
        backedge();
        charge(10);
        v0 = sll(v1, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 48);
        lwc1(F0, v0, 0);
        sub_s(F0, F0, F3);
        swc1(F0, v0, 0);
        lwc1(F0, v0, 4);
        sub_s(F0, F0, F1);
        swc1(F0, v0, 4);
        v1 = addiu(v1, 1);
    }
    charge(3);
    v1 = 0;
    for (;;) {
        charge(3);
        v0 = slti(v1, 4);
        if (v0 == 0) {
            break;
        }
        backedge();
        charge(10);
        v0 = sll(v1, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 48);
        lwc1(F0, v0, 0);
        mul_s(F0, F0, F6);
        swc1(F0, v0, 0);
        lwc1(F0, v0, 4);
        mul_s(F0, F0, F6);
        swc1(F0, v0, 4);
        v1 = addiu(v1, 1);
    }
    charge(3);
    v1 = 0;
    for (;;) {
        charge(3);
        v0 = slti(v1, 4);
        if (v0 == 0) {
            break;
        }
        backedge();
        charge(10);
        v0 = sll(v1, 3);
        v0 = addu(v0, sp);
        v0 = addiu(v0, 48);
        lwc1(F0, v0, 0);
        add_s(F0, F0, F3);
        swc1(F0, v0, 0);
        lwc1(F0, v0, 4);
        add_s(F0, F0, F1);
        swc1(F0, v0, 4);
        v1 = addiu(v1, 1);
    }
    charge(18);
    a0 = addiu(s0, 528);
    a1 = addiu(sp, 48);
    jal(0x24C6BC, gen::fn_sub_21D890_0021d890);
    v0 = 255;
    sb(v0, sp, 108);
    sb(v0, sp, 109);
    sb(v0, sp, 110);
    v0 = lui(0x437F);
    mtc1(v0, F0);
    mul_s(F1, F0, F20);
    v0 = lui(0x4F00);
    mtc1(v0, F0);
    c_le_s(F0, F1);
    if (!cop1_cond()) {
        charge(6);
        cvt_w_s(F0, F1);
        mfc1(v1, F0);
        v1 = v1 & 0xFF;
        goto L_0024c72c;
    }
    charge(6);
    sub_s(F0, F1, F0);
    cvt_w_s(F0, F0);
    mfc1(v1, F0);
    v0 = lui(0x8000);
    v1 = v1 | v0;
    v1 = v1 & 0xFF;
L_0024c72c:
    charge(9);
    sb(v1, sp, 111);
    a0 = addiu(s0, 528);
    a1 = addiu(sp, 108);
    jal(0x24C738, gen::fn_sub_21D950_0021d950);
    lw(v0, s0, 12);
    at = slti(v0, 12);
    if (at != 0) {
        charge(12);
        mtc1(v0, F0);
        cvt_s_w(F1, F0);
        v0 = lui(0x4140);
        mtc1(v0, F0);
        div_s(F21, F1, F0);
        goto L_0024c7b8;
    }
    charge(3);
    at = slti(v0, 48);
    if (at != 0) {
        charge(2);
        goto L_0024c7b8;
    }
    charge(9);
    v0 = addiu(v0, -48);
    mtc1(v0, F0);
    cvt_s_w(F1, F0);
    v0 = lui(0x4140);
    mtc1(v0, F0);
    div_s(F0, F1, F0);
    sub_s(F21, F21, F0);
L_0024c7b8:
    charge(14);
    sw(zero, sp, 80);
    sw(zero, sp, 84);
    v0 = lui(0x4420);
    sw(v0, sp, 88);
    v0 = lui(0x43E0);
    sw(v0, sp, 92);
    a0 = addiu(s0, 16);
    a1 = addiu(sp, 80);
    jal(0x24C7D8, gen::fn_sub_21D8E0_0021d8e0);
    lw(v1, s0, 0);
    v0 = 1;
    if (v1 != v0) {
        charge(2);
        if (v1 != 0) {
            charge(2);
            goto L_0024c830;
        }
        charge(7);
        sb(zero, sp, 108);
        v0 = 17;
        sb(v0, sp, 109);
        v0 = 72;
        sb(v0, sp, 110);
        goto L_0024c830;
    }
    charge(5);
    v0 = 55;
    sb(v0, sp, 108);
    sb(zero, sp, 109);
    v0 = 3;
    sb(v0, sp, 110);
L_0024c830:
    charge(10);
    v0 = lui(0x4319);
    mtc1(v0, F0);
    mul_s(F1, F0, F21);
    v0 = lui(0x4F00);
    mtc1(v0, F0);
    c_le_s(F0, F1);
    if (!cop1_cond()) {
        charge(6);
        cvt_w_s(F0, F1);
        mfc1(v1, F0);
        v1 = v1 & 0xFF;
        goto L_0024c888;
    }
    charge(6);
    sub_s(F0, F1, F0);
    cvt_w_s(F0, F0);
    mfc1(v1, F0);
    v0 = lui(0x8000);
    v1 = v1 | v0;
    v1 = v1 & 0xFF;
L_0024c888:
    charge(19);
    sb(v1, sp, 111);
    a0 = addiu(s0, 16);
    a1 = addiu(sp, 108);
    jal(0x24C894, gen::fn_sub_21D950_0021d950);
    v1 = lui(0xC3B4);
    sw(v1, s0, 784);
    a1 = lui(0x43E0);
    sw(a1, s0, 788);
    a0 = lui(0x4420);
    sw(a0, s0, 848);
    v1 = lui(0x4314);
    sw(v1, s0, 852);
    sw(a0, s0, 912);
    sw(a1, s0, 916);
    lw(a0, s0, 0);
    v1 = 1;
    if (a0 != v1) {
        charge(2);
        if (a0 != 0) {
            charge(2);
            goto L_0024c918;
        }
        charge(7);
        sb(zero, sp, 108);
        v1 = 68;
        sb(v1, sp, 109);
        v1 = 200;
        sb(v1, sp, 110);
        goto L_0024c918;
    }
    charge(6);
    v1 = 45;
    sb(v1, sp, 108);
    v1 = 2;
    sb(v1, sp, 109);
    v1 = 8;
    sb(v1, sp, 110);
L_0024c918:
    charge(4);
    sb(zero, sp, 111);
    lbu(v1, sp, 108);
    if (!ltz(v1)) {
        charge(5);
        mtc1(v1, F0);
        cvt_s_w(F0, F0);
        goto L_0024c958;
    }
    charge(7);
    a0 = srl(v1, 1);
    v1 = v1 & 0x1;
    a0 = a0 | v1;
    mtc1(a0, F0);
    cvt_s_w(F0, F0);
    add_s(F0, F0, F0);
L_0024c958:
    charge(4);
    swc1(F0, s0, 816);
    lbu(v1, sp, 109);
    if (!ltz(v1)) {
        charge(5);
        mtc1(v1, F0);
        cvt_s_w(F0, F0);
        goto L_0024c998;
    }
    charge(7);
    a0 = srl(v1, 1);
    v1 = v1 & 0x1;
    a0 = a0 | v1;
    mtc1(a0, F0);
    cvt_s_w(F0, F0);
    add_s(F0, F0, F0);
L_0024c998:
    charge(4);
    swc1(F0, s0, 820);
    lbu(v1, sp, 110);
    if (!ltz(v1)) {
        charge(5);
        mtc1(v1, F0);
        cvt_s_w(F0, F0);
        goto L_0024c9d8;
    }
    charge(7);
    a0 = srl(v1, 1);
    v1 = v1 & 0x1;
    a0 = a0 | v1;
    mtc1(a0, F0);
    cvt_s_w(F0, F0);
    add_s(F0, F0, F0);
L_0024c9d8:
    charge(4);
    swc1(F0, s0, 824);
    lbu(v1, sp, 111);
    if (!ltz(v1)) {
        charge(5);
        mtc1(v1, F0);
        cvt_s_w(F0, F0);
        goto L_0024ca18;
    }
    charge(7);
    a0 = srl(v1, 1);
    v1 = v1 & 0x1;
    a0 = a0 | v1;
    mtc1(a0, F0);
    cvt_s_w(F0, F0);
    add_s(F0, F0, F0);
L_0024ca18:
    charge(4);
    swc1(F0, s0, 828);
    lbu(v1, sp, 108);
    if (!ltz(v1)) {
        charge(5);
        mtc1(v1, F0);
        cvt_s_w(F0, F0);
        goto L_0024ca58;
    }
    charge(7);
    a0 = srl(v1, 1);
    v1 = v1 & 0x1;
    a0 = a0 | v1;
    mtc1(a0, F0);
    cvt_s_w(F0, F0);
    add_s(F0, F0, F0);
L_0024ca58:
    charge(4);
    swc1(F0, s0, 880);
    lbu(v1, sp, 109);
    if (!ltz(v1)) {
        charge(5);
        mtc1(v1, F0);
        cvt_s_w(F0, F0);
        goto L_0024ca98;
    }
    charge(7);
    a0 = srl(v1, 1);
    v1 = v1 & 0x1;
    a0 = a0 | v1;
    mtc1(a0, F0);
    cvt_s_w(F0, F0);
    add_s(F0, F0, F0);
L_0024ca98:
    charge(4);
    swc1(F0, s0, 884);
    lbu(v1, sp, 110);
    if (!ltz(v1)) {
        charge(5);
        mtc1(v1, F0);
        cvt_s_w(F0, F0);
        goto L_0024cad8;
    }
    charge(7);
    a0 = srl(v1, 1);
    v1 = v1 & 0x1;
    a0 = a0 | v1;
    mtc1(a0, F0);
    cvt_s_w(F0, F0);
    add_s(F0, F0, F0);
L_0024cad8:
    charge(4);
    swc1(F0, s0, 888);
    lbu(v1, sp, 111);
    if (!ltz(v1)) {
        charge(5);
        mtc1(v1, F0);
        cvt_s_w(F0, F0);
        goto L_0024cb18;
    }
    charge(7);
    a0 = srl(v1, 1);
    v1 = v1 & 0x1;
    a0 = a0 | v1;
    mtc1(a0, F0);
    cvt_s_w(F0, F0);
    add_s(F0, F0, F0);
L_0024cb18:
    charge(11);
    swc1(F0, s0, 892);
    v1 = lui(0x437F);
    mtc1(v1, F0);
    mul_s(F1, F0, F21);
    v1 = lui(0x4F00);
    mtc1(v1, F0);
    c_le_s(F0, F1);
    if (!cop1_cond()) {
        charge(6);
        cvt_w_s(F0, F1);
        mfc1(a0, F0);
        a0 = a0 & 0xFF;
        goto L_0024cb74;
    }
    charge(6);
    sub_s(F0, F1, F0);
    cvt_w_s(F0, F0);
    mfc1(a0, F0);
    v1 = lui(0x8000);
    a0 = a0 | v1;
    a0 = a0 & 0xFF;
L_0024cb74:
    charge(4);
    sb(a0, sp, 111);
    lbu(v1, sp, 108);
    if (!ltz(v1)) {
        charge(5);
        mtc1(v1, F0);
        cvt_s_w(F0, F0);
        goto L_0024cbb4;
    }
    charge(7);
    a0 = srl(v1, 1);
    v1 = v1 & 0x1;
    a0 = a0 | v1;
    mtc1(a0, F0);
    cvt_s_w(F0, F0);
    add_s(F0, F0, F0);
L_0024cbb4:
    charge(4);
    swc1(F0, s0, 944);
    lbu(v1, sp, 109);
    if (!ltz(v1)) {
        charge(5);
        mtc1(v1, F0);
        cvt_s_w(F0, F0);
        goto L_0024cbf4;
    }
    charge(7);
    a0 = srl(v1, 1);
    v1 = v1 & 0x1;
    a0 = a0 | v1;
    mtc1(a0, F0);
    cvt_s_w(F0, F0);
    add_s(F0, F0, F0);
L_0024cbf4:
    charge(4);
    swc1(F0, s0, 948);
    lbu(v1, sp, 110);
    if (!ltz(v1)) {
        charge(5);
        mtc1(v1, F0);
        cvt_s_w(F0, F0);
        goto L_0024cc34;
    }
    charge(7);
    a0 = srl(v1, 1);
    v1 = v1 & 0x1;
    a0 = a0 | v1;
    mtc1(a0, F0);
    cvt_s_w(F0, F0);
    add_s(F0, F0, F0);
L_0024cc34:
    charge(4);
    swc1(F0, s0, 952);
    lbu(v1, sp, 111);
    if (!ltz(v1)) {
        charge(5);
        mtc1(v1, F0);
        cvt_s_w(F0, F0);
        goto L_0024cc74;
    }
    charge(7);
    a0 = srl(v1, 1);
    v1 = v1 & 0x1;
    a0 = a0 | v1;
    mtc1(a0, F0);
    cvt_s_w(F0, F0);
    add_s(F0, F0, F0);
L_0024cc74:
    charge(1);
    swc1(F0, s0, 956);
L_0024cc78:
    charge(8);
    ld(ra, sp, 32);
    lq(s0, sp, 16);
    lwc1(F22, sp, 8);
    lwc1(F21, sp, 4);
    lwc1(F20, sp, 0);
    sp = addiu(sp, 112);
    return;
}

// sub_24CF00 [AI banner: show]: the UV rectangle of kind 0 or 1 of the banner texture (sub_21C790(kind): +12 width, +16
// height) on the sprites +272 / +528 (sub_21EB80, depth 0 through sub_21EAC0, also +16), +792 = 0, kind +0, +8 = +12 =
// 0, flag 0x1.
void Cpu::sub_24CF00() {
    enter(8);
    sp = addiu(sp, -64);
    sd(ra, sp, 32);
    sq(s1, sp, 16);
    sq(s0, sp, 0);
    s1 = a0;
    lw(v0, gp, kGpBai);
    if (v0 == 0) {
        charge(5);
        kassert(0x24CF2C, kBaiMainC, 55);
    }
    charge(9);
    lw(s0, gp, kGpBai);
    a0 = s1;
    jal(0x24CF3C, gen::fn_sub_21C790_0021c790);
    lw(a0, v0, 12);
    lw(v1, v0, 16);
    v0 = 1;
    if (s1 != v0) {
        charge(2);
        if (s1 != 0) {
            charge(2);
            goto L_0024d028;
        }
        charge(27);
        v0 = lui(0x3F80);
        mtc1(v0, F3);
        mtc1(a0, F0);
        cvt_s_w(F2, F0);
        div_s(F0, F3, F2);
        swc1(F0, sp, 48);
        mtc1(v1, F0);
        cvt_s_w(F1, F0);
        div_s(F0, F3, F1);
        swc1(F0, sp, 52);
        v0 = 417;
        mtc1(v0, F0);
        cvt_s_w(F0, F0);
        div_s(F0, F0, F2);
        swc1(F0, sp, 56);
        v0 = lui(0x437A);
        mtc1(v0, F0);
        div_s(F0, F0, F1);
        swc1(F0, sp, 60);
        goto L_0024d028;
    }
    charge(21);
    mtc1(zero, F3);
    mtc1(a0, F0);
    cvt_s_w(F2, F0);
    div_s(F0, F3, F2);
    swc1(F0, sp, 48);
    mtc1(v1, F0);
    cvt_s_w(F1, F0);
    div_s(F0, F3, F1);
    swc1(F0, sp, 52);
    v0 = lui(0x43D6);
    mtc1(v0, F0);
    div_s(F0, F0, F2);
    swc1(F0, sp, 56);
    v0 = lui(0x4380);
    mtc1(v0, F0);
    div_s(F0, F0, F1);
    swc1(F0, sp, 60);
L_0024d028:
    charge(35);
    a0 = addiu(s0, 272);
    a1 = addiu(sp, 48);
    jal(0x24D030, gen::fn_sub_21EB80_0021eb80);
    mtc1(zero, F12);
    a0 = addiu(s0, 272);
    jal(0x24D040, gen::fn_sub_21EAC0_0021eac0);
    a0 = addiu(s0, 528);
    a1 = addiu(sp, 48);
    jal(0x24D050, gen::fn_sub_21EB80_0021eb80);
    mtc1(zero, F12);
    a0 = addiu(s0, 528);
    jal(0x24D060, gen::fn_sub_21EAC0_0021eac0);
    mtc1(zero, F12);
    a0 = addiu(s0, 16);
    jal(0x24D070, gen::fn_sub_21EAC0_0021eac0);
    sw(zero, s0, 792);
    sw(zero, s0, 792);
    sw(zero, s0, 792);
    sw(s1, s0, 0);
    sw(zero, s0, 8);
    sw(zero, s0, 12);
    lw(v1, s0, 4);
    v1 = v1 | 0x1;
    sw(v1, s0, 4);
    ld(ra, sp, 32);
    lq(s1, sp, 16);
    lq(s0, sp, 0);
    sp = addiu(sp, 64);
    return;
}

// sub_24D0C0: the AI panel's flag 0x1.
void Cpu::sub_24D0C0() {
    enter(5);
    sp = addiu(sp, -16);
    sd(ra, sp, 0);
    lw(v0, gp, kGpBai);
    if (v0 == 0) {
        charge(5);
        kassert(0x24D0E0, kBaiMainC, 55);
    }
    charge(7);
    lw(v0, gp, kGpBai);
    lw(v0, v0, 4);
    v0 = v0 & 0x1;
    ld(ra, sp, 0);
    sp = addiu(sp, 16);
    return;
}

}  // namespace
}  // namespace battle_result

u32 sub_1F08C0(EEContext& ctx, u32 task) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(task));
    battle_result::Cpu(ctx).sub_1F08C0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F0900(EEContext& ctx, u32 task) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(task));
    battle_result::Cpu(ctx).sub_1F0900();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F0940(EEContext& ctx, u32 task) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(task));
    battle_result::Cpu(ctx).sub_1F0940();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F0970(EEContext& ctx, u32 task) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(task));
    battle_result::Cpu(ctx).sub_1F0970();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F0A60(EEContext& ctx, u32 task) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(task));
    battle_result::Cpu(ctx).sub_1F0A60();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F0AB0(EEContext& ctx, u32 task) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(task));
    battle_result::Cpu(ctx).sub_1F0AB0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F0C40(EEContext& ctx, u32 task) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(task));
    battle_result::Cpu(ctx).sub_1F0C40();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F0D70(EEContext& ctx, u32 task) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(task));
    battle_result::Cpu(ctx).sub_1F0D70();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F0EB0(EEContext& ctx, u32 task) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(task));
    battle_result::Cpu(ctx).sub_1F0EB0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F0F40(EEContext& ctx, u32 task) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(task));
    battle_result::Cpu(ctx).sub_1F0F40();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F0FD0(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_1F0FD0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F0FF0(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_1F0FF0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F10B0(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_1F10B0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F10F0(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_1F10F0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F1140(EEContext& ctx, u32 task) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(task));
    battle_result::Cpu(ctx).sub_1F1140();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F1210(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_1F1210();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F1240(EEContext& ctx, u32 task) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(task));
    battle_result::Cpu(ctx).sub_1F1240();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F1AA0(EEContext& ctx, u32 task) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(task));
    battle_result::Cpu(ctx).sub_1F1AA0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F1AE0(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_1F1AE0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F1B00(EEContext& ctx, u32 task) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(task));
    battle_result::Cpu(ctx).sub_1F1B00();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F1B20(EEContext& ctx, u32 task) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(task));
    battle_result::Cpu(ctx).sub_1F1B20();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F1B40(EEContext& ctx, u32 task) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(task));
    battle_result::Cpu(ctx).sub_1F1B40();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F1B60(EEContext& ctx, u32 task) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(task));
    battle_result::Cpu(ctx).sub_1F1B60();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F1C20(EEContext& ctx, u32 task) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(task));
    battle_result::Cpu(ctx).sub_1F1C20();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F1C50(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_1F1C50();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F1C90(EEContext& ctx, u32 task) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(task));
    battle_result::Cpu(ctx).sub_1F1C90();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F1DF0(EEContext& ctx, u32 out_ids, u32 out_count) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(out_ids));
    ee::core::set_gpr64(ctx, GPR_A1, battle_result::sx(out_count));
    battle_result::Cpu(ctx).sub_1F1DF0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F1E90(EEContext& ctx, u32 task) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(task));
    battle_result::Cpu(ctx).sub_1F1E90();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F1F40(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_1F1F40();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1F9D70(EEContext& ctx, u32 member) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(member));
    battle_result::Cpu(ctx).sub_1F9D70();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1FA0D0(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_1FA0D0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1FA4F0(EEContext& ctx, u32 member) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(member));
    battle_result::Cpu(ctx).sub_1FA4F0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1FAEA0(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_1FAEA0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1FB130(EEContext& ctx, u32 member, u32 persona_id) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(member));
    ee::core::set_gpr64(ctx, GPR_A1, battle_result::sx(persona_id));
    battle_result::Cpu(ctx).sub_1FB130();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1FB1B0(EEContext& ctx, u32 member, u32 value) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(member));
    ee::core::set_gpr64(ctx, GPR_A1, battle_result::sx(value));
    battle_result::Cpu(ctx).sub_1FB1B0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1FB1F0(EEContext& ctx, u32 persona, u32 out_skills, u32 out_count) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(persona));
    ee::core::set_gpr64(ctx, GPR_A1, battle_result::sx(out_skills));
    ee::core::set_gpr64(ctx, GPR_A2, battle_result::sx(out_count));
    battle_result::Cpu(ctx).sub_1FB1F0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1FB3F0(EEContext& ctx, u32 rows, u32 level, u32 gained, u32 out_first, u32 out_count) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(rows));
    ee::core::set_gpr64(ctx, GPR_A1, battle_result::sx(level));
    ee::core::set_gpr64(ctx, GPR_A2, battle_result::sx(gained));
    ee::core::set_gpr64(ctx, GPR_A3, battle_result::sx(out_first));
    ee::core::set_gpr64(ctx, GPR_T0, battle_result::sx(out_count));
    battle_result::Cpu(ctx).sub_1FB3F0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1FB4B0(EEContext& ctx, u32 rows, u32 n, u32 level, u32 range, u32 out_first, u32 out_count) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(rows));
    ee::core::set_gpr64(ctx, GPR_A1, battle_result::sx(n));
    ee::core::set_gpr64(ctx, GPR_A2, battle_result::sx(level));
    ee::core::set_gpr64(ctx, GPR_A3, battle_result::sx(range));
    ee::core::set_gpr64(ctx, GPR_T0, battle_result::sx(out_first));
    ee::core::set_gpr64(ctx, GPR_T1, battle_result::sx(out_count));
    battle_result::Cpu(ctx).sub_1FB4B0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1FBD50(EEContext& ctx, u32 level, u32 nth) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(level));
    ee::core::set_gpr64(ctx, GPR_A1, battle_result::sx(nth));
    battle_result::Cpu(ctx).sub_1FBD50();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1FBDF0(EEContext& ctx, u32 level, u32 other_level, u32 exp, u32 row, u32 mode) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(level));
    ee::core::set_gpr64(ctx, GPR_A1, battle_result::sx(other_level));
    ee::core::set_gpr64(ctx, GPR_A2, battle_result::sx(exp));
    ee::core::set_gpr64(ctx, GPR_A3, battle_result::sx(row));
    ee::core::set_gpr64(ctx, GPR_T0, battle_result::sx(mode));
    battle_result::Cpu(ctx).sub_1FBDF0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1FBFA0(EEContext& ctx, u32 level, u32 other_level, u32 exp, u32 item, u32 row, u32 mode) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(level));
    ee::core::set_gpr64(ctx, GPR_A1, battle_result::sx(other_level));
    ee::core::set_gpr64(ctx, GPR_A2, battle_result::sx(exp));
    ee::core::set_gpr64(ctx, GPR_A3, battle_result::sx(item));
    ee::core::set_gpr64(ctx, GPR_T0, battle_result::sx(row));
    ee::core::set_gpr64(ctx, GPR_T1, battle_result::sx(mode));
    battle_result::Cpu(ctx).sub_1FBFA0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1FC1F0(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_1FC1F0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1FC230(EEContext& ctx, u32 persona) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(persona));
    battle_result::Cpu(ctx).sub_1FC230();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1FC3C0(EEContext& ctx, u32 persona) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(persona));
    battle_result::Cpu(ctx).sub_1FC3C0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_1FC590(EEContext& ctx, u32 unit, u32 target) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(unit));
    ee::core::set_gpr64(ctx, GPR_A1, battle_result::sx(target));
    battle_result::Cpu(ctx).sub_1FC590();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2338D0(EEContext& ctx, u32 res) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(res));
    battle_result::Cpu(ctx).sub_2338D0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2338F0(EEContext& ctx, u32 res) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(res));
    battle_result::Cpu(ctx).sub_2338F0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_233910(EEContext& ctx, u32 res) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(res));
    battle_result::Cpu(ctx).sub_233910();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_233930(EEContext& ctx, u32 res) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(res));
    battle_result::Cpu(ctx).sub_233930();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_233950(EEContext& ctx, u32 res) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(res));
    battle_result::Cpu(ctx).sub_233950();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_233960(EEContext& ctx, u32 res) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(res));
    battle_result::Cpu(ctx).sub_233960();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_233970(EEContext& ctx, u32 res) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(res));
    battle_result::Cpu(ctx).sub_233970();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_233AD0(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_233AD0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_233BB0(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_233BB0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_233D20(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_233D20();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_233D70(EEContext& ctx, u32 i) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(i));
    battle_result::Cpu(ctx).sub_233D70();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_233DF0(EEContext& ctx, u32 i) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(i));
    battle_result::Cpu(ctx).sub_233DF0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_234570(EEContext& ctx, u32 i) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(i));
    battle_result::Cpu(ctx).sub_234570();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2345D0(EEContext& ctx, u32 i) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(i));
    battle_result::Cpu(ctx).sub_2345D0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_234630(EEContext& ctx, u32 i) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(i));
    battle_result::Cpu(ctx).sub_234630();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_234690(EEContext& ctx, u32 i, u32 file) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(i));
    ee::core::set_gpr64(ctx, GPR_A1, battle_result::sx(file));
    battle_result::Cpu(ctx).sub_234690();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2347E0(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_2347E0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_234820(EEContext& ctx, u32 panel) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(panel));
    battle_result::Cpu(ctx).sub_234820();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_234960(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_234960();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_234A00(EEContext& ctx, u32 record) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(record));
    battle_result::Cpu(ctx).sub_234A00();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_235010(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_235010();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2361D0(EEContext& ctx, u32 sprite, u32 index, u32 kind) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(sprite));
    ee::core::set_gpr64(ctx, GPR_A1, battle_result::sx(index));
    ee::core::set_gpr64(ctx, GPR_A2, battle_result::sx(kind));
    battle_result::Cpu(ctx).sub_2361D0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_236280(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_236280();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_2362E0(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_2362E0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_236340(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_236340();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 bpIfontSetDigitQuad(EEContext& ctx, u32 quad, u32 digit, u32 font) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(quad));
    ee::core::set_gpr64(ctx, GPR_A1, battle_result::sx(digit));
    ee::core::set_gpr64(ctx, GPR_A2, battle_result::sx(font));
    battle_result::Cpu(ctx).bpIfontSetDigitQuad();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_239140(EEContext& ctx, u32 font) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(font));
    battle_result::Cpu(ctx).sub_239140();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_24A870(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_24A870();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_24AA90(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_24AA90();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_24AB10(EEContext& ctx, u32 persona_id) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(persona_id));
    battle_result::Cpu(ctx).sub_24AB10();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_24ABD0(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_24ABD0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_24AC40(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_24AC40();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_24ADF0(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_24ADF0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_24B8A0(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_24B8A0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_24B9E0(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_24B9E0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_24BA30(EEContext& ctx, u32 res) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(res));
    battle_result::Cpu(ctx).sub_24BA30();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_24BED0(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_24BED0();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_24BF20(EEContext& ctx, u32 i) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(i));
    battle_result::Cpu(ctx).sub_24BF20();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_24C040(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_24C040();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_24C090(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_24C090();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_24C100(EEContext& ctx, u32 work) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(work));
    battle_result::Cpu(ctx).sub_24C100();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_24C110(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_24C110();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_24CF00(EEContext& ctx, u32 kind) {
    ee::core::set_gpr64(ctx, GPR_A0, battle_result::sx(kind));
    battle_result::Cpu(ctx).sub_24CF00();
    return ee::core::gpr32(ctx, GPR_V0);
}
u32 sub_24D0C0(EEContext& ctx) {
    battle_result::Cpu(ctx).sub_24D0C0();
    return ee::core::gpr32(ctx, GPR_V0);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (the bodies read their arguments from the registers) ---------------
namespace p3fes::recomp_gen {
namespace br = ::p3fes::game::battle_result;

void fn_sub_1F08C0_001f08c0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F08C0(); }
void fn_sub_1F0900_001f0900(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F0900(); }
void fn_sub_1F0940_001f0940(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F0940(); }
void fn_sub_1F0970_001f0970(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F0970(); }
void fn_sub_1F0A60_001f0a60(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F0A60(); }
void fn_sub_1F0AB0_001f0ab0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F0AB0(); }
void fn_sub_1F0C40_001f0c40(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F0C40(); }
void fn_sub_1F0D70_001f0d70(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F0D70(); }
void fn_sub_1F0EB0_001f0eb0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F0EB0(); }
void fn_sub_1F0F40_001f0f40(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F0F40(); }
void fn_sub_1F0FD0_001f0fd0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F0FD0(); }
void fn_sub_1F0FF0_001f0ff0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F0FF0(); }
void fn_sub_1F10B0_001f10b0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F10B0(); }
void fn_sub_1F10F0_001f10f0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F10F0(); }
void fn_sub_1F1140_001f1140(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F1140(); }
void fn_sub_1F1210_001f1210(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F1210(); }
void fn_sub_1F1240_001f1240(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F1240(); }
void fn_sub_1F1AA0_001f1aa0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F1AA0(); }
void fn_sub_1F1AE0_001f1ae0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F1AE0(); }
void fn_sub_1F1B00_001f1b00(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F1B00(); }
void fn_sub_1F1B20_001f1b20(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F1B20(); }
void fn_sub_1F1B40_001f1b40(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F1B40(); }
void fn_sub_1F1B60_001f1b60(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F1B60(); }
void fn_sub_1F1C20_001f1c20(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F1C20(); }
void fn_sub_1F1C50_001f1c50(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F1C50(); }
void fn_sub_1F1C90_001f1c90(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F1C90(); }
void fn_sub_1F1DF0_001f1df0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F1DF0(); }
void fn_sub_1F1E90_001f1e90(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F1E90(); }
void fn_sub_1F1F40_001f1f40(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F1F40(); }
void fn_sub_1F9D70_001f9d70(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1F9D70(); }
void fn_sub_1FA0D0_001fa0d0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1FA0D0(); }
void fn_sub_1FA4F0_001fa4f0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1FA4F0(); }
void fn_sub_1FAEA0_001faea0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1FAEA0(); }
void fn_sub_1FB130_001fb130(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1FB130(); }
void fn_sub_1FB1B0_001fb1b0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1FB1B0(); }
void fn_sub_1FB1F0_001fb1f0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1FB1F0(); }
void fn_sub_1FB3F0_001fb3f0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1FB3F0(); }
void fn_sub_1FB4B0_001fb4b0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1FB4B0(); }
void fn_sub_1FBD50_001fbd50(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1FBD50(); }
void fn_sub_1FBDF0_001fbdf0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1FBDF0(); }
void fn_sub_1FBFA0_001fbfa0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1FBFA0(); }
void fn_sub_1FC1F0_001fc1f0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1FC1F0(); }
void fn_sub_1FC230_001fc230(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1FC230(); }
void fn_sub_1FC3C0_001fc3c0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1FC3C0(); }
void fn_sub_1FC590_001fc590(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_1FC590(); }
void fn_sub_2338D0_002338d0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_2338D0(); }
void fn_sub_2338F0_002338f0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_2338F0(); }
void fn_sub_233910_00233910(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_233910(); }
void fn_sub_233930_00233930(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_233930(); }
void fn_sub_233950_00233950(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_233950(); }
void fn_sub_233960_00233960(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_233960(); }
void fn_sub_233970_00233970(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_233970(); }
void fn_sub_233AD0_00233ad0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_233AD0(); }
void fn_sub_233BB0_00233bb0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_233BB0(); }
void fn_sub_233D20_00233d20(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_233D20(); }
void fn_sub_233D70_00233d70(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_233D70(); }
void fn_sub_233DF0_00233df0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_233DF0(); }
void fn_sub_234570_00234570(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_234570(); }
void fn_sub_2345D0_002345d0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_2345D0(); }
void fn_sub_234630_00234630(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_234630(); }
void fn_sub_234690_00234690(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_234690(); }
void fn_sub_2347E0_002347e0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_2347E0(); }
void fn_sub_234820_00234820(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_234820(); }
void fn_sub_234960_00234960(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_234960(); }
void fn_sub_234A00_00234a00(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_234A00(); }
void fn_sub_235010_00235010(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_235010(); }
void fn_sub_2361D0_002361d0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_2361D0(); }
void fn_sub_236280_00236280(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_236280(); }
void fn_sub_2362E0_002362e0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_2362E0(); }
void fn_sub_236340_00236340(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_236340(); }
void fn_bpIfontSetDigitQuad_00238fd0(p3fes::EEContext& ctx) { br::Cpu(ctx).bpIfontSetDigitQuad(); }
void fn_sub_239140_00239140(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_239140(); }
void fn_sub_24A870_0024a870(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_24A870(); }
void fn_sub_24AA90_0024aa90(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_24AA90(); }
void fn_sub_24AB10_0024ab10(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_24AB10(); }
void fn_sub_24ABD0_0024abd0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_24ABD0(); }
void fn_sub_24AC40_0024ac40(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_24AC40(); }
void fn_sub_24ADF0_0024adf0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_24ADF0(); }
void fn_sub_24B8A0_0024b8a0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_24B8A0(); }
void fn_sub_24B9E0_0024b9e0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_24B9E0(); }
void fn_sub_24BA30_0024ba30(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_24BA30(); }
void fn_sub_24BED0_0024bed0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_24BED0(); }
void fn_sub_24BF20_0024bf20(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_24BF20(); }
void fn_sub_24C040_0024c040(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_24C040(); }
void fn_sub_24C090_0024c090(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_24C090(); }
void fn_sub_24C100_0024c100(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_24C100(); }
void fn_sub_24C110_0024c110(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_24C110(); }
void fn_sub_24CF00_0024cf00(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_24CF00(); }
void fn_sub_24D0C0_0024d0c0(p3fes::EEContext& ctx) { br::Cpu(ctx).sub_24D0C0(); }

}  // namespace p3fes::recomp_gen
