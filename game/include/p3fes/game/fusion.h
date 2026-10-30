// Phase 5 slice fusion: the Velvet Room persona fusion code of the facilities band 0x3C77A0-0x41BE44
// (docs/ANALYSIS/27_unmapped_bands.md §8, "Velvet Room fusion" 0x3D02E0-0x3DF49C: fclCombine.c 0x6A4648,
// fclCombineMisc.c 0x6A5F70, fclCombineList.c 0x6A6020). No replay route reaches the Velvet Room; the pair tests
// (tests/game/test_fusion.cpp) run these bodies on the real game tables (the ELF's .data and battle/PERSONA.TBL).
//
// The data the bodies work on (read from the instructions; names in brackets are proposals, not imported -- see
// symbols/deltas/fusion.sym):
//
//   persona table   PERSONA.TBL section 0, `*(gp - 18640)` = *0x7CE420: 14-byte records by persona id (0..255):
//                   +0 u16 flags (bit 0 / bit 1: never a fusion result -- the result searches skip them),
//                   +2 u8 arcana (1 Fool .. 22; 0 = none), +3 u8 base level, +12 u8 the accident base rate (%),
//                   +13 u8 an index into the word table 0x6A5630.
//   persona         the 52-byte persona instance the dat* layer builds from an id (sub_176680): +0 u16 flags,
//                   +2 u16 id, +4 u8 level, +12 u16 skills[8], +28 u8 stats[5] (St Ma En Ag Lu).
//   stock list      12 entries of 12 bytes (sub_3D5CD0 fills it from the hero's personas): +0 word 0,
//                   +4 the persona instance, +8 its persona-table record.
//   fusion result   84 bytes (sub_3D6AE0): +0 flags (bit 1 the result's level is above the hero's, bit 2 a
//                   special (recipe) fusion), +4 the 52-byte persona, +56 s8 stat deltas[5], +62 u16 the skills
//                   the fusion added[8].
//   arcana charts   22 x 22 bytes indexed [22 * lo + hi] (lo <= hi; arcana ids 1..21): the normal chart
//                   0x6A56B9 (two personas), the triangle charts 0x6A58E9 (the two lower personas) and 0x6A5AD9
//                   (that arcana with the highest persona). 0 = no result.
//   recipes         the special fusions: 5 categories (2..6 personas) at 0x6A5F40 = {u32 table, u32 count}[5];
//                   32-byte records: +0 u16 result, +8 u16 ingredients[8] (bits 0..9 the persona id -- or with
//                   bit 14 an arcana --, bit 15 "must be present"), +24 u16 skills[4] given to the result.
//   rules           0x6A5410: 67 x {u32 flag, s16 persona id, u16 mode}: mode bit 0 the persona needs the flag,
//                   bit 1 the flag enables it (sub_3D5BB0; the result searches inline the same walk).
//   the list menu   fclCombineList.c: a list object (nm_message.h) with +12 the slot count, +16 the selected
//                   count, +20 the row list, +24 the selected-persona array, +284 the stock list.
//
// The second batch -- the fclCombine root and tasks, the menu steps, the skill inheritance sub_3D74F0 (RwMalloc /
// RwFree through 0x960178 / 0x96017C), the list-menu builders and panels -- is in fusion_menu.h / fusion_menu.cpp
// (p3fes_handgen bodies with roles and comments on top).
//
// Kept recompiled (called through their generated entry points): the dat* persona layer (sub_176680 .. sub_176C80,
// sub_1749A0 .. sub_175130, the social-link readers sub_16DBA0 / sub_16DEB0 / sub_16E100), the facility element
// helpers above 0x3DF4A0 (sub_3DFAC0 .. sub_3E0680: shared with the shops), memset / memcpy, cosf / sinf,
// RpRandom sub_488F30, K_Assert sub_19D3F0 (`jr $ra` in retail: a failed check continues).
//
// Register contract (docs/PHASE5_AGENT_BRIEF.md, waves 6, 7 and 10): every check point can preempt the thread and
// the kernel then saves the whole register file in guest memory; callees spill what they receive and game code
// reads registers a callee left behind. So these bodies are register-faithful: at every check point, every call and
// every return each GPR (128 bits), HI/LO, FPR, ACC and FCR31 holds what the original holds there, and the
// prologues write the original spills. The bodies work on the guest registers directly (the Cpu view below, one
// named variable per register), with the data flow named in comments; the per-block virtual time follows the
// recompiled bodies (ADR-0013).
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"
#include "p3fes_recomp_rt.h"

namespace p3fes::game {

namespace fusion::detail {

namespace core = ee::core;

// --- R5900 integer results (32-bit operations sign-extend into the 64-bit register) ----------------------
constexpr u64 sx(u32 v) { return core::sext32(v); }
constexpr u64 si(s32 v) { return static_cast<u64>(static_cast<s64>(v)); }  // a negative immediate
constexpr s64 sgn(u64 v) { return static_cast<s64>(v); }                  // a register as a signed 64-bit value
constexpr u64 addu(u64 a, u64 b) { return core::add32(a, b); }
constexpr u64 addiu(u64 a, s32 i) { return core::add32i(a, i); }
constexpr u64 subu(u64 a, u64 b) { return core::sub32(a, b); }
constexpr u64 daddu(u64 a, u64 b) { return core::add64(a, b); }
constexpr u64 lui(u32 i) { return core::lui(i); }
constexpr u64 sll(u64 a, unsigned n) { return core::sll(a, n); }
constexpr u64 srl(u64 a, unsigned n) { return core::srl(a, n); }
constexpr u64 sra(u64 a, unsigned n) { return core::sra(a, n); }
constexpr u64 sllv(u64 a, u64 n) { return core::sllv(a, n); }
constexpr u64 dsll32(u64 a, unsigned n) { return core::dsll32(a, n); }
constexpr u64 dsrl32(u64 a, unsigned n) { return core::dsrl32(a, n); }
constexpr u64 dsra32(u64 a, unsigned n) { return core::dsra32(a, n); }
constexpr u64 slt(u64 a, u64 b) { return core::slt(a, b); }
constexpr u64 sltu(u64 a, u64 b) { return core::sltu(a, b); }
constexpr u64 slti(u64 a, s32 i) { return core::slti(a, i); }
constexpr u64 sltiu(u64 a, s32 i) { return core::sltiu(a, i); }
constexpr u32 w(u64 v) { return static_cast<u32>(v); }

// One GPR of the guest context. Reads go through volatile lvalues, and so does virtual time below (the wave-10 lesson
// of render_core3: MSVC 14.44 /O2 kept ctx.cycles in a host register across a call to a small helper that charges, and
// the helper's charges were lost). A volatile access is a compiler barrier under /volatile:ms and keeps every access
// real under clang-cl, so no guest state is cached across a helper or a call.
//
// Guest memory goes through the runtime's own load / store instructions (rt::lw .. rt::sq with $zero as the base and the
// address as the offset), so an access the original would fault on -- unaligned, unmapped -- stops the run the same way.
// A load is written `reg = lw(address)`: lw() names the access and the assignment performs it into that register.
enum class LoadKind : u8 { lw, lh, lhu, lb, lbu, ld };
struct Load {
    u64 addr;
    LoadKind kind;
};
inline s32 off_of(u64 addr) { return static_cast<s32>(static_cast<u32>(addr)); }

struct Gpr {
    EEContext& c;
    const unsigned r;
    operator u64() const noexcept { return static_cast<const volatile u64&>(c.gpr[r].u64[0]); }
    Gpr& operator=(u64 v) noexcept {
        core::set_gpr64(c, r, v);
        return *this;
    }
    Gpr& operator=(const Gpr& o) noexcept { return *this = static_cast<u64>(o); }
    Gpr& operator=(const Load& l) {
        const s32 off = off_of(l.addr);
        switch (l.kind) {
        case LoadKind::lw: rt::lw(c, r, GPR_ZERO, off); break;
        case LoadKind::lh: rt::lh(c, r, GPR_ZERO, off); break;
        case LoadKind::lhu: rt::lhu(c, r, GPR_ZERO, off); break;
        case LoadKind::lb: rt::lb(c, r, GPR_ZERO, off); break;
        case LoadKind::lbu: rt::lbu(c, r, GPR_ZERO, off); break;
        case LoadKind::ld: rt::ld(c, r, GPR_ZERO, off); break;
        }
        return *this;
    }
};

// FPR numbers.
enum : unsigned {
    F0, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15,
    F16, F17, F18, F19, F20, F21, F22, F23, F24, F25, F26, F27, F28, F29, F30, F31
};

// The guest machine as the bodies see it (src/facility/fusion.cpp derives the bodies from it).
class Cpu {
public:
    explicit Cpu(EEContext& ctx) noexcept : c(ctx) {}

    EEContext& c;
    Gpr zero{c, 0}, at{c, 1}, v0{c, 2}, v1{c, 3}, a0{c, 4}, a1{c, 5}, a2{c, 6}, a3{c, 7};
    Gpr t0{c, 8}, t1{c, 9}, t2{c, 10}, t3{c, 11}, t4{c, 12}, t5{c, 13}, t6{c, 14}, t7{c, 15};
    Gpr s0{c, 16}, s1{c, 17}, s2{c, 18}, s3{c, 19}, s4{c, 20}, s5{c, 21}, s6{c, 22}, s7{c, 23};
    Gpr t8{c, 24}, t9{c, 25}, gp{c, 28}, sp{c, 29}, fp{c, 30}, ra{c, 31};

    // virtual time (enter / backedge are not noexcept: a check point's fatal event must unwind through the bodies)
    void enter(u64 n) {
        rt::check_events(c);
        charge(n);
    }
    void charge(u64 n) noexcept {
        volatile u64& t = c.cycles;
        t = t + n;
    }
    void backedge() { rt::check_events(c); }

    // loads / stores through the runtime's instructions (addresses are 32-bit; LQ / SQ force a quadword boundary)
    static Load lw(u64 a) noexcept { return {a, LoadKind::lw}; }
    static Load lh(u64 a) noexcept { return {a, LoadKind::lh}; }
    static Load lhu(u64 a) noexcept { return {a, LoadKind::lhu}; }
    static Load lb(u64 a) noexcept { return {a, LoadKind::lb}; }
    static Load lbu(u64 a) noexcept { return {a, LoadKind::lbu}; }
    static Load ld(u64 a) noexcept { return {a, LoadKind::ld}; }
    void lq(const Gpr& d, u64 a) { rt::lq(c, d.r, GPR_ZERO, off_of(a)); }
    void sw(u64 a, const Gpr& v) { rt::sw(c, v.r, GPR_ZERO, off_of(a)); }
    void sh(u64 a, const Gpr& v) { rt::sh(c, v.r, GPR_ZERO, off_of(a)); }
    void sb(u64 a, const Gpr& v) { rt::sb(c, v.r, GPR_ZERO, off_of(a)); }
    void sd(u64 a, const Gpr& v) { rt::sd(c, v.r, GPR_ZERO, off_of(a)); }
    void sq(u64 a, const Gpr& v) { rt::sq(c, v.r, GPR_ZERO, off_of(a)); }

    // FPU (the runtime's instruction semantics: EE singles, ACC, FCR31 flags)
    void lwc1(unsigned f, u64 a) { rt::lwc1(c, f, GPR_ZERO, off_of(a)); }
    void swc1(unsigned f, u64 a) { rt::swc1(c, f, GPR_ZERO, off_of(a)); }
    void mtc1(const Gpr& g, unsigned f) noexcept { rt::mtc1(c, g.r, f); }
    void mfc1(const Gpr& g, unsigned f) noexcept { rt::mfc1(c, g.r, f); }
    void mov_s(unsigned d, unsigned s) noexcept { rt::mov_s(c, d, s); }
    void add_s(unsigned d, unsigned s, unsigned t) noexcept { rt::add_s(c, d, s, t); }
    void sub_s(unsigned d, unsigned s, unsigned t) noexcept { rt::sub_s(c, d, s, t); }
    void mul_s(unsigned d, unsigned s, unsigned t) noexcept { rt::mul_s(c, d, s, t); }
    void div_s(unsigned d, unsigned s, unsigned t) noexcept { rt::div_s(c, d, s, t); }
    void adda_s(unsigned s, unsigned t) noexcept { rt::adda_s(c, s, t); }
    void madd_s(unsigned d, unsigned s, unsigned t) noexcept { rt::madd_s(c, d, s, t); }
    void msub_s(unsigned d, unsigned s, unsigned t) noexcept { rt::msub_s(c, d, s, t); }
    void cvt_s_w(unsigned d, unsigned s) noexcept { rt::cvt_s_w(c, d, s); }
    void cvt_w_s(unsigned d, unsigned s) noexcept { rt::cvt_w_s(c, d, s); }

    // HI/LO (pipe 0)
    void mult(Gpr& d, const Gpr& s, const Gpr& t) noexcept { rt::mult(c, d.r, s.r, t.r); }
    void div(const Gpr& s, const Gpr& t) noexcept { rt::div(c, s.r, t.r); }
    void divu(const Gpr& s, const Gpr& t) noexcept { rt::divu(c, s.r, t.r); }
    void mflo(Gpr& d) noexcept { rt::mflo(c, d.r); }
    void mfhi(Gpr& d) noexcept { rt::mfhi(c, d.r); }

    // calls: `jal fn` at pc ($ra = pc + 8; a delay slot's instruction is written before the call)
    void jal(u32 pc, rt::Fn fn) {
        rt::jal(c, pc);
        fn(c);
    }

    // the K_Assert(file, line) call of the band (`lui a0, 0x6A; addiu a0, a0, file; li a1, line; jal 0x19D3F0`):
    // `jr $ra` in retail, the failed check continues
    void k_assert(u32 file, u32 line, u32 pc);
    // the prologue / epilogue: `addiu sp, -size; sd ra, ra_off; sq s(n-1) .. sq s0` (s_i at s_base + 16 * i; n = 9
    // includes $fp as the ninth) and its reverse `ld ra; lq ..; addiu sp, size`
    void open_frame(u32 size, u32 ra_off, u32 s_base, unsigned n);
    void close_frame(u32 size, u32 ra_off, u32 s_base, unsigned n);
};

}  // namespace fusion::detail

// K_Assert file arguments and the tables.
constexpr u32 kCombineMiscFile = 0x6A5F70u;   // "fclCombineMisc.c"
constexpr u32 kCombineListFile = 0x6A6020u;   // "fclCombineList.c"
constexpr u32 kPersonaTablePtr = 0x7CE420u;   // gp - 18640: the persona table (PERSONA.TBL section 0)
constexpr u32 kNormalChart = 0x6A56B9u;       // [22 * lo + hi]
constexpr u32 kTriangleChart1 = 0x6A58E9u;
constexpr u32 kTriangleChart2 = 0x6A5AD9u;
constexpr u32 kRecipeCategories = 0x6A5F40u;  // {u32 table, u32 count}[5]
constexpr u32 kRecipeRules = 0x6A5410u;       // 67 x {u32 flag, s16 persona, u16 mode}
constexpr u32 kCombineRoot = 0x7CE684u;       // gp - 18028: the fclCombine sequence object

// --- the public entry points ---------------------------------------------------------------------------------------
// Each function keeps its symbols/functions.json name; the bracketed role is a proposal. They take their guest arguments
// as 64-bit register values and return $v0 (for the void ones, $v0 is whatever the original left). The recompiled
// program's entry points (`fn_<name>_<addr8>`) are defined in src/facility/fusion.cpp.

// [fclCombine.c] the sequence object and the menu step helpers
u64 sub_3D02E0(EEContext& ctx);                                  // [fclCombineGetRoot]: *(gp - 18028)
u64 sub_3D0600(EEContext& ctx);                                  // [fclCombineIsActive]: root != 0
u64 sub_3D21D0(EEContext& ctx);                                  // [fclCombineCallAll]: nmSequenceCallAll36(root), returns 0
u64 sub_3D25C0(EEContext& ctx, u64 work);                        // [fclCombineAddStep6]: step 6 of the 12-byte desc 0x6A4620
u64 sub_3D2640(EEContext& ctx, u64 work);                        // [fclCombineTakeStep40]: the step at +40 when done
u64 sub_3D26C0(EEContext& ctx, u64 obj, u64 node);               // [fclCombineStepClear]
u64 sub_3D2710(EEContext& ctx, u64 obj, u64 node);               // [fclCombineStepNop]
u64 sub_3D2C00(EEContext& ctx);                                  // returns 0
u64 sub_3D2DD0(EEContext& ctx, u64 obj, u64 node);               // [fclCombineStepNop2]
u64 sub_3D2EF0(EEContext& ctx);                                  // returns 0
u64 sub_3D3010(EEContext& ctx, u64 menu);                        // [fclCombineMenuClosed]
u64 sub_3D3280(EEContext& ctx, u64 menu);                        // [fclCombineMenuClose]
u64 sub_3D35C0(EEContext& ctx, u64 obj, u64 node);               // [fclCombineStepFree]
u64 sub_3D3B70(EEContext& ctx, u64 work, u64 arg);               // [fclCombineAddStep2]: step 2 of 0x6A4870
u64 sub_3D3C20(EEContext& ctx, u64 work);                        // [fclCombineTakeStep24]
u64 sub_3D3CA0(EEContext& ctx, u64 obj, u64 node);               // [fclCombineStepMarkDone]
// [fclCombineMisc.c] the fusion rules
u64 sub_3D5510(EEContext& ctx, u64 out, u64 recipe, u64 need, u64 stock);   // [fclCombineMatchRecipe]
u64 sub_3D5730(EEContext& ctx, u64 out, u64 category, u64 index, u64 stock); // [fclCombineGetRecipe]
u64 sub_3D5850(EEContext& ctx, u64 index);                       // [fclCombineTable6A5FC0]
u64 sub_3D58A0(EEContext& ctx);                                  // [-> sub_3C3F80]
u64 sub_3D58C0(EEContext& ctx, u64 link, u64 level);             // [fclCombineCalcPrice]: EE float formula
u64 sub_3D5A40(EEContext& ctx, u64 recipe, u64 need, u64 ids, u64 count, u64 found);  // [fclCombineRecipeMask]
u64 sub_3D5BB0(EEContext& ctx, u64 persona);                     // [fclCombineIsPersonaAvailable]
u64 sub_3D5C90(EEContext& ctx);                                  // [fclCombineGetScenarioWord]
u64 sub_3D5CD0(EEContext& ctx, u64 stock);                       // [fclCombineBuildStock]
u64 sub_3D5DC0(EEContext& ctx, u64 persona);                     // [fclCombineRankLetter]
u64 sub_3D5E60(EEContext& ctx, u64 p0, u64 p1, u64 p2);          // [fclCombineTriangleArcana]
u64 sub_3D6200(EEContext& ctx, u64 out, u64 category, u64 ids, u64 count);  // [fclCombineSpecial]
u64 sub_3D64A0(EEContext& ctx, u64 out, u64 id0, u64 id1);       // [fclCombineNormal]
u64 sub_3D6740(EEContext& ctx, u64 out, u64 p0, u64 p1, u64 p2); // [fclCombineTriangle]
u64 sub_3D6910(EEContext& ctx, u64 out, u64 kind, u64 personas); // [fclCombineByKind]
u64 sub_3D6AE0(EEContext& ctx, u64 result, u64 kind, u64 personas);  // [fclCombinePreview]
u64 sub_3D6C90(EEContext& ctx, u64 kind);                        // [fclCombineRollAccident]
u64 sub_3D6E60(EEContext& ctx, u64 result, u64 from);            // [fclCombineCopyAddedSkills]
u64 sub_3D6F80(EEContext& ctx, u64 result, u64 from, u64 exclude);   // [fclCombineAccidentRandom]
u64 sub_3D7180(EEContext& ctx);                                  // [fclCombineRoll50]
u64 sub_3D71D0(EEContext& ctx, u64 result, u64 from, u64 exclude);   // [fclCombineAccidentFool]
u64 sub_3D72F0(EEContext& ctx, u64 result);                      // [fclCombineRollBonus]
u64 sub_3D74B0(EEContext& ctx, u64 persona);                     // [fclCombineTable6A5630]
u64 sub_3D7A30(EEContext& ctx, u64 persona, u64 personas, u64 count);  // [fclCombineInherit]
u64 sub_3D7AC0(EEContext& ctx, u64 arcana, u64 level, u64 exclude);    // [fclCombineFindResultUp]
u64 sub_3D7DA0(EEContext& ctx, u64 arcana, u64 level, u64 exclude);    // [fclCombineFindResultDown]
u64 sub_3D8080(EEContext& ctx, u64 result, u64 personas, u64 count);   // [fclCombineCommit]
u64 sub_3D8230(EEContext& ctx, u64 result);                      // [fclCombineResultRegistered]
u64 sub_3D8260(EEContext& ctx, u64 stock, u64 first);            // [fclCombineNormalPartnerMask]
u64 sub_3D8370(EEContext& ctx, u64 stock, u64 first, u64 second);   // [fclCombineTrianglePartnerMask]
u64 sub_3D84C0(EEContext& ctx, u64 unused, u64 category);        // [fclCombineAnyRecipeAvailable]
u64 sub_3D8630(EEContext& ctx, u64 stock, u64 category);         // [fclCombineAnyRecipeInStock]
u64 sub_3D8830(EEContext& ctx, u64 category);                    // [fclCombineRecipeCount]
// [fclCombineList.c] the list menu
u64 sub_3D9C90(EEContext& ctx, u64 obj, u64 node);               // [fclCombineListRowFree]
u64 sub_3DA2A0(EEContext& ctx, u64 list);                        // [fclCombineListMarkTriangle]
u64 sub_3DA3A0(EEContext& ctx, u64 list);                        // [fclCombineListFree]
u64 sub_3DA3E0(EEContext& ctx, u64 list, u64 index);             // [fclCombineListGetSelected]
u64 sub_3DA470(EEContext& ctx, u64 list, u64 persona);           // [fclCombineListIsSelected]
u64 sub_3DA570(EEContext& ctx, u64 list);                        // [fclCombineListPreviewAll]
u64 sub_3DB580(EEContext& ctx, u64 list);                        // [fclCombineListDraw]
u64 sub_3DB5E0(EEContext& ctx, u64 list);                        // [fclCombineListRemoveFiltered]
u64 sub_3DC210(EEContext& ctx, u64 a0, u64 a1, u64 a2, u64 obj); // [fclCombineListRefresh2]
u64 sub_3DEB20(EEContext& ctx, u64 list);                        // [fclCombineListCopySelection]
u64 sub_3DEB80(EEContext& ctx, u64 a0, u64 a1, u64 a2, u64 obj); // [fclCombineListRefresh]
u64 sub_3DEC00(EEContext& ctx, u64 a0, u64 a1, u64 a2, u64 obj, u64 row);  // [fclCombineListDrawRow] (row in $t0)
u64 sub_3DECD0(EEContext& ctx, u64 owner);                       // [fclElemListCreate]
u64 sub_3DED40(EEContext& ctx, u64 elems);                       // [fclElemListDestroy]
u64 sub_3DED70(EEContext& ctx, u64 elems);                       // [fclElemListRemoveFiltered]
u64 sub_3DEE80(EEContext& ctx, u64 elems, u64 a1, u64 a2, u64 a3, u64 t0, u64 t1);  // [fclElemAdd]
u64 sub_3DEF10(EEContext& ctx, u64 n);                           // [fclElemSpacing]: 9 * (n + 1) from 2 on
u64 sub_3DEF40(EEContext& ctx, u64 width, u64 n, u64 i);         // [fclElemOffset]
u64 sub_3DEF80(EEContext& ctx, u64 elems);                       // [fclElemRestartAll]
u64 sub_3DF010(EEContext& ctx, u64 elems);                       // [fclElemAllDone]
u64 sub_3DF090(EEContext& ctx, u64 elems, u64 extra);            // [fclElemNew]
u64 sub_3DF100(EEContext& ctx, u64 elem, u64 desc);              // [fclElemSetParams]
u64 sub_3DF220(EEContext& ctx, u64 elem, u64 a1, u64 a2, u64 a3, u64 t0, u64 t1);   // [fclElemStart]

}  // namespace p3fes::game
