// Phase 5 slice battle_cmd_menu: the battle command menu, bcm_main.c (0x1FF890-0x208AC4; docs/ANALYSIS/27_unmapped_bands.md
// section 3, queue_bands.txt "slice battle_cmd_menu").
//
// What the file is. When a party member's turn comes, the battle panel opens the command menu: one work record (the
// "bcm work", 30,644 bytes, pointer at $gp-18952, set by sub_201730 and cleared by sub_201780) holds the state of every
// list the menu can show -- the top commands, the skill list, the item list, the persona list, the tactics list
// ("Act Freely" ... "Orgia Mode", 0x684F00) and the target list -- with, per list, the font lines (frFontBuildGlyphList
// nodes) that draw its entries. Each list has a builder (fills the lines, sets its "built" bit in +0) and a releaser
// (frees the lines through sub_3B0170, clears the bit); the menu's per-frame code (sub_1FFF40, a printf-heavy debug
// body, skip class) moves the cursors and calls the small queries here (the selected skill / item / persona id, the
// availability tests that grey out ATTACK / SKILL / ITEM / PERSONA, the "start command operation" bits in +12 and the
// debug ON/OFF switches in +30624).
//
// Register discipline (wave-7 rule, docs/PHASE5_AGENT_BRIEF.md): a check point may preempt the thread and the kernel
// then saves the WHOLE register file in guest memory; callees spill what they receive; callers read what a callee
// left behind. So these bodies are register-faithful at every check point, call and return: they run on bcm::Cpu (one
// variable per guest register; the loads and stores are the runtime's own instruction semantics, alignment faults
// included), write the original prologue spills, keep the original's register allocation and name the data flow in the
// comments and constants. Virtual time follows the recompiled bodies block by block (ADR-0013): every charge() is one
// `ctx.cycles += N` block (N = the block's instruction count), charged where the block starts (before its calls);
// backedge() sits on every backward branch, where the recompiled body checks.
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"
#include "p3fes_recomp_rt.h"

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line): `jr ra` in retail
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace bcm {

// --- globals --------------------------------------------------------------------------------------------------------
inline constexpr s32 kGpWork = -18952;          // the bcm work (0 while no menu exists)
inline constexpr s32 kGpBattle = -18692;        // the battle root (+336: the first btlUnit of the unit list)
inline constexpr s32 kGpSkillTable = -18680;    // the skill table, 44-byte rows (byte +1 bit 1: not usable in battle)
inline constexpr s32 kGpStrAllMembers = -26844; // "All Members"
inline constexpr s32 kGpStrSupport = -26848;    // "Support"
inline constexpr u32 kFileName = 0x00684F48u;   // "bcm_main.c", the K_Assert file argument
inline constexpr u32 kTacticNames = 0x00684F00u; // const char*[10]: "Act Freely" ... "Orgia Mode" (index tactic - 1)
inline constexpr u32 kAssertLineWork = 356;      // the line of every "work != NULL" assertion

// --- the bcm work ($gp-18952) ---------------------------------------------------------------------------------------
inline constexpr s32 kFlags = 0;            // u32: 1 active, 2 / 4 / 8 / 0x10 skill / item / persona / target lines built,
                                            //      0x20 a sub list open, 0x80 / 0x100 / 0x400 SKILL / ITEM / PERSONA
                                            //      greyed out, 0x200 no tactics rows, 0x1000 / 0x2000 tactic / analyze lines
                                            //      built, 0x4000 .. 0x200000 the support sides, 0x800000 help line built,
                                            //      0x20000000 suspended
inline constexpr s32 kFlags2 = 4;           // u32: 1 / 2 the skill / item window was closed (sub_208460), 4 the tactics
                                            //      were applied (sub_204AF0)
inline constexpr s32 kSelState = 8;         // u32
inline constexpr s32 kOperation = 12;       // u32: the commands that can be chosen (1 SKILL, 2 ITEM, 4 TACTICS, 8 PERSONA,
                                            //      0x10 / 0x20 / 0x40 the other top commands; sub_201880 lights their icons)
inline constexpr s32 kListKind = 16;        // u32: the open list (1 skill, 2 item, 3 persona, 4 targets, 6 analyze, 9 item
                                            //      preview, 10 / 11 tutorial)
inline constexpr s32 kMode = 32;            // u32: 0 / 1 / 2 (sub_1FF740 at creation; 2 = no tactics / support rows)
inline constexpr s32 kWord36 = 36;          // u32 (sub_2054C0)
inline constexpr s32 kSkills = 44;          // the skill list: {u32 flags (+40: 1 payable, 2 the sub_30C0C0 entry); u16 id}
                                            //      [<= 9], 8 bytes each; kSkills names the id
inline constexpr s32 kSkillCount = 112;     // u32
inline constexpr s32 kSkillLines = 120;     // u32 font lines [kSkillCount]
inline constexpr s32 kSkillTitle = 136;     // u32 font line of the open skill window (released with +0 bit 0x20)
inline constexpr s32 kItemLines = 140;      // u32 font lines [kItemLineCount] (4 rows)
inline constexpr s32 kItems = 156;          // s16 item ids [n]
inline constexpr s32 kItemLineCount = 604;  // u32
inline constexpr s32 kItemCount = 608;      // u32
inline constexpr s32 kItemTitle = 612;      // u32 font line
inline constexpr s32 kPersonas = 616;       // {u16 id; u16 pad; u32 level} [n], 8 bytes each: the persona list
inline constexpr s32 kPersonaLines = 712;   // u32 font lines [kPersonaLineCount]
inline constexpr s32 kPersonaLineCount = 728;  // u32 (at most 4)
inline constexpr s32 kPersonaCount = 732;   // u32
inline constexpr s32 kTargets = 736;        // 24-byte rows [n]: the tactics / target list (kTarget* fields)
inline constexpr s32 kTargetLines = 880;    // {u32 line, u32 line2} [kTargetLineCount], 8 bytes each
inline constexpr s32 kTargetCount = 936;    // u32
inline constexpr s32 kTargetLineCount = 940;   // u32 (at most 7)
inline constexpr s32 kTacticLines = 984;    // u32 font lines [kTacticLineCount]
inline constexpr s32 kTacticLineCount = 1024;  // u32
inline constexpr s32 kAnalyzeLines = 1044;  // u32 font lines [kAnalyzeLineCount]
inline constexpr s32 kAnalyzeLineCount = 1060; // u32
inline constexpr s32 kPanel = 1072;         // the command panel record (sub_21F0C0)
inline constexpr s32 kHelpText = 27936;     // u32 (copy of kHelpLine)
inline constexpr s32 kMsgHandles = 30608;   // u32 message handles [3] (itfMesMngDestroyHandle at teardown)
inline constexpr s32 kHelpLine = 30620;     // u32 font line of the help text (kBuiltHelp)
inline constexpr s32 kDebug = 30624;        // u32: debug switches that keep a command off (1, 2 SKILL, 4 ITEM, 8 PERSONA,
                                            //      0x10, 0x20, 0x40 TACTICS; "ATTACK : OFF" ... the printf debug bodies)
inline constexpr s32 kTitleLine = 30632;    // u32 font line (released by sub_206310 / sub_206EB0)
inline constexpr s32 kTitleLine2 = 30636;   // u32 font line (optional)
inline constexpr s32 kSupportState = 30640; // u32

// 24-byte target / tactic row at kTargets + 24 * i.
inline constexpr s32 kRowFlags = 0;         // u32: bit 0 used, bit 1 ...
inline constexpr s32 kRowKind = 4;          // u32: 0 "All Members", 1 a party member, 2 "Support"
inline constexpr s32 kRowUnit = 8;          // u32: the btlUnit
inline constexpr s32 kRowPcId = 12;         // s16: party member id
inline constexpr s32 kRowTactic = 16;       // u32: tactic 1..10 (7 = "Assign Target")
inline constexpr s32 kRowTarget = 20;       // u32

// --- R5900 integer results --------------------------------------------------------------------------------------------
namespace core = ee::core;
constexpr u64 sx(u32 v) { return core::sext32(v); }
constexpr u64 si(s32 v) { return static_cast<u64>(static_cast<s64>(v)); }  // a negative immediate (`li rX, -n`)
constexpr u64 addu(u64 a, u64 b) { return core::add32(a, b); }
constexpr u64 addiu(u64 a, s32 i) { return core::add32i(a, i); }
constexpr u64 subu(u64 a, u64 b) { return core::sub32(a, b); }
constexpr u64 lui(u32 i) { return core::lui(i); }
constexpr u64 sll(u64 a, unsigned n) { return core::sll(a, n); }
constexpr u64 srl(u64 a, unsigned n) { return core::srl(a, n); }
constexpr u64 sra(u64 a, unsigned n) { return core::sra(a, n); }
constexpr u64 dsll32(u64 a, unsigned n) { return core::dsll32(a, n); }
constexpr u64 dsra32(u64 a, unsigned n) { return core::dsra32(a, n); }
constexpr u64 slt(u64 a, u64 b) { return core::slt(a, b); }
constexpr u64 slti(u64 a, s32 i) { return core::slti(a, i); }
constexpr u64 sltu(u64 a, u64 b) { return core::sltu(a, b); }
constexpr u64 sltiu(u64 a, s32 i) { return core::sltiu(a, i); }
constexpr u64 andi(u64 a, u32 i) { return core::andi(a, i); }
constexpr u64 ori(u64 a, u32 i) { return core::ori(a, i); }
constexpr u64 xori(u64 a, u32 i) { return core::xori(a, i); }
constexpr u64 nor(u64 a, u64 b) { return ~(a | b); }
// `dsll32 rd, rs, 16; dsra32 rd, rd, 16` / `dsll32 ..., 24; dsra32 ..., 24`: the low half / byte sign-extended.
constexpr u64 sext_h(u64 a) { return dsra32(dsll32(a, 16), 16); }
constexpr u64 sext_b(u64 a) { return dsra32(dsll32(a, 24), 24); }

// One GPR of the guest context (64-bit writes keep bits 64..127, as every non-MMI EE instruction).
struct Gpr {
    EEContext& c;
    const unsigned r;
    operator u64() const noexcept { return c.gpr[r].u64[0]; }
    Gpr& operator=(u64 v) noexcept {
        core::set_gpr64(c, r, v);
        return *this;
    }
    Gpr& operator=(const Gpr& o) noexcept { return *this = static_cast<u64>(o); }
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

    // loads / stores: `op rt, off(base)` through the runtime's instruction semantics
    void lw(Gpr& d, const Gpr& b, s32 off) { rt::lw(c, d.r, b.r, off); }
    void lh(Gpr& d, const Gpr& b, s32 off) { rt::lh(c, d.r, b.r, off); }
    void lhu(Gpr& d, const Gpr& b, s32 off) { rt::lhu(c, d.r, b.r, off); }
    void lbu(Gpr& d, const Gpr& b, s32 off) { rt::lbu(c, d.r, b.r, off); }
    void sw(const Gpr& v, const Gpr& b, s32 off) { rt::sw(c, v.r, b.r, off); }
    void sh(const Gpr& v, const Gpr& b, s32 off) { rt::sh(c, v.r, b.r, off); }
    void sb(const Gpr& v, const Gpr& b, s32 off) { rt::sb(c, v.r, b.r, off); }
    void mtc1_zero(unsigned f) { rt::mtc1(c, 0, f); }  // `mtc1 zero, $fN`

    // The prologue `addiu sp, sp, -size; sd ra, 16n(sp); sq s(n-1) .. s0 at 16(n-1) .. 0` and its epilogue.
    void push(s32 size, unsigned n) {
        rt::addiu(c, 29, 29, -size);
        rt::sd(c, 31, 29, static_cast<s32>(16 * n));
        for (unsigned i = n; i-- > 0;) rt::sq(c, 16 + i, 29, static_cast<s32>(16 * i));
    }
    void pop(s32 size, unsigned n) {
        rt::ld(c, 31, 29, static_cast<s32>(16 * n));
        for (unsigned i = n; i-- > 0;) rt::lq(c, 16 + i, 29, static_cast<s32>(16 * i));
        rt::addiu(c, 29, 29, size);
    }

    // `jal fn` at pc ($ra = pc + 8; the delay slots here are all nops)
    void jal(u32 pc, rt::Fn fn) {
        rt::jal(c, pc);
        fn(c);
    }

    // `lui a0, 0x68; addiu a0, a0, 0x4F48; li a1, line; jal K_Assert` (the block's cycles are the caller's)
    void k_assert(u32 pc, u32 line) {
        a0 = sx(kFileName);
        a1 = line;
        jal(pc, &recomp_gen::fn_sub_19D3F0_0019d3f0);
    }
    // `lw r, -18952(gp); bnez r, 1f; nop; <K_Assert(file, 356)>; 1:` -- the opening "work != NULL" check of nearly
    // every function here. The load belongs to the caller's first block; the assertion block costs 5.
    void need_work(Gpr& r, u32 pc) {
        lw(r, gp, kGpWork);
        if (r == 0) {
            charge(5);
            k_assert(pc, kAssertLineWork);
        }
    }
    // A built-bit / state assertion: `<test>; bnez/beqz ..., 1f; nop; <K_Assert(file, line)>; 1:` (5 cycles).
    void check(bool ok, u32 pc, u32 line) {
        if (!ok) {
            charge(5);
            k_assert(pc, line);
        }
    }
};

}  // namespace bcm

// --- the replaced functions (functions.json names; [proposed role]) ---------------------------------------------------
// Each reads its arguments from $a0.. as the original receives them and leaves its result in $v0 (register-faithful
// bodies: everything else they leave in the registers is what the original leaves).
// The record: creation, destruction, teardown
void sub_201730(EEContext& ctx);  // [bcmCreate] (work): clear the record, menu mode, command panel; $gp-18952 = work
void sub_201780(EEContext& ctx);  // [bcmDestroy] release every built list, destroy the command panel; $gp-18952 = 0
void sub_1FFC60(EEContext& ctx);  // [bcmTeardown] apply the tactics, stop changed support sides, release lists and message handles
// Top menu, transitions, drawing
void sub_201880(EEContext& ctx);  // [bcmRefreshTopMenu] command icons from the operation bits; help line from message handle +30608
void sub_201A50(EEContext& ctx);  // [bcmBackToTop] refresh, +0 |= 0x40, panel back to the top, sound; +16 = 0
void sub_201B50(EEContext& ctx);  // [bcmResume] +0 |= 1, then reopen the built lists' windows
void sub_201C30(EEContext& ctx);  // [bcmSuspend] +0 |= 0x20000000, then reopen
void sub_201D10(EEContext& ctx);  // [bcmDeactivate] +0 = (+0 & ~1) | 0x40, then reopen
void sub_201E00(EEContext& ctx);  // [bcmUnsuspend] +0 = (+0 & ~0x20000000) | 0x40, then reopen
void sub_2016B0(EEContext& ctx);  // [bcmDraw] top menu and sub window, unless a tutorial / preview is up (+16 = 9 / 10 / 11)
void sub_201AD0(EEContext& ctx);  // sub_208360
void sub_208460(EEContext& ctx);  // [bcmCloseSubWindow] close the open sub list's window, sound; +16 = 0
void sub_207E20(EEContext& ctx);  // [bcmOpenBossTutorial] tutorial page by boss encounter 466..469; +16 = 10
void sub_207F10(EEContext& ctx);  // [bcmOpenTutorial] tutorial page; +16 = 11
void sub_2078A0(EEContext& ctx);  // [bcmPreviewItem] preview the sub_30C0C0 item; +16 = 9
// Availability of the top commands
void sub_201EF0(EEContext& ctx);  // [bcmCheckSkillAvailable] a battle-usable skill -> +12 |= 1, else +0 |= 0x80
void sub_202C90(EEContext& ctx);  // [bcmCheckItemAvailable] a usable held item -> +12 |= 2, else +0 |= 0x100
void sub_203760(EEContext& ctx);  // [bcmCheckPersonaAvailable] another persona -> +12 |= 8, else +0 |= 0x400
void sub_2056A0(EEContext& ctx);  // +12 |= 0x20 unless debug +30624 & 1
void sub_205700(EEContext& ctx);  // +12 |= 0x10 unless debug +30624 & 0x10
void sub_205760(EEContext& ctx);  // +12 |= 0x40 unless debug +30624 & 0x20
// Skill list
void sub_202010(EEContext& ctx);  // [bcmOpenSkillList] collect the skills (costs, the sub_30C0C0 entry), place the cursor, open; +16 = 1
void sub_2024B0(EEContext& ctx);  // [bcmBuildSkillLines] one font line per skill; +0 |= 2
void sub_202A10(EEContext& ctx);  // [bcmRefreshSkillLines] rebuild the visible skill lines, help line
void sub_202BC0(EEContext& ctx);  // [bcmReleaseSkillLines] release them; +0 &= ~2
void sub_2025E0(EEContext& ctx);  // [bcmOpenSkillWindow] fill the panel rows, open the skill window
// Item list
void sub_202D70(EEContext& ctx);  // [bcmOpenItemList] collect the usable held items, place the cursor, open; +16 = 2
void sub_203030(EEContext& ctx);  // [bcmBuildItemLines] up to 4 item lines; +0 |= 4
void sub_203410(EEContext& ctx);  // [bcmRefreshItemLines] rebuild the visible item lines, help line
void sub_203360(EEContext& ctx);  // [bcmReleaseItemLines] release them; +0 &= ~4
void sub_2031C0(EEContext& ctx);  // [bcmOpenItemWindow] fill the panel rows, open the item window
// Persona list
void sub_203850(EEContext& ctx);  // [bcmOpenPersonaList] build, fill, open; +16 = 3
void sub_203990(EEContext& ctx);  // [bcmBuildPersonaLines] the current persona then the stock; +0 |= 8
void sub_203DE0(EEContext& ctx);  // [bcmRefreshPersonaLines] rebuild with the cursor / current colours
void sub_203B70(EEContext& ctx);  // [bcmReleasePersonaLines] release them; +0 &= ~8
void sub_203C30(EEContext& ctx);  // [bcmOpenPersonaWindow] place, fill the panel rows, open the persona window
// Tactics and target list
void sub_204000(EEContext& ctx);  // [bcmBuildTargetRows] "All Members", a row per member, "Support"; the support bits
void sub_204480(EEContext& ctx);  // [bcmOpenTargetList] place the remembered target, build the lines, fill, open; +16 = 4
void sub_204760(EEContext& ctx);  // [bcmBuildTargetLines] name + tactic lines per row; +0 |= 0x10
void sub_205000(EEContext& ctx);  // [bcmRefreshTargetLines] release and rebuild the visible rows
void sub_204BE0(EEContext& ctx);  // [bcmReleaseTargetLines] release them; +0 &= ~0x10
void sub_204CC0(EEContext& ctx);  // [bcmOpenTargetWindow] place / colour the rows, fill the panel, open the target window
void sub_205D60(EEContext& ctx);  // [bcmOpenTargetWindowAnalyze] the same without the refresh, then the analyze window
void sub_204AF0(EEContext& ctx);  // [bcmApplyTactics] each member row's tactic (and assigned target); +4 |= 4
void sub_206170(EEContext& ctx);  // [bcmRefreshTacticLines] rebuild the tactic names, help line
void sub_2060B0(EEContext& ctx);  // [bcmOpenTacticWindow] fill the panel rows, open the tactics window
void sub_206310(EEContext& ctx);  // [bcmReleaseTacticLines] release them; +0 &= ~0x1000
void sub_2065A0(EEContext& ctx);  // [bcmConfirmTactic] "Assign Target" for the row under the cursor (or every member)
// Analyze list
void sub_206740(EEContext& ctx);  // [bcmOpenAnalyzeList] the rows, cursor, lines, title, panel rows, open; +16 = 6
void sub_207010(EEContext& ctx);  // [bcmRefreshAnalyzeLines] rebuild the visible rows, help line
void sub_206EB0(EEContext& ctx);  // [bcmReleaseAnalyzeLines] release them; +0 &= ~0x2000
void sub_206F70(EEContext& ctx);  // [bcmOpenAnalyzeWindow] copy the lines into the panel, open
void sub_206E40(EEContext& ctx);  // [bcmOpenAnalyze] open the analyze window, sound; +24 = 9
void sub_207340(EEContext& ctx);  // [bcmConfirmAnalyzeRow] act on the analyze row under the cursor (scan / support / ...)
void sub_205410(EEContext& ctx);  // [bcmCloseSubList] close the open skill / item sub list; +0 &= ~0x20
// Help line
void sub_2082C0(EEContext& ctx);  // [bcmSetHelpLine] (line): +30620 = +27936 = line; +0 |= 0x800000
void sub_208360(EEContext& ctx);  // [bcmReleaseHelpLineChecked] assert, then sub_2083D0
void sub_2083D0(EEContext& ctx);  // [bcmReleaseHelpLine] release +30620; +0 &= ~0x800000
// Queries
void sub_201AF0(EEContext& ctx);  // [bcmIsActive] (+0 & 1) || (+0 & 0x20000000)
void sub_2053C0(EEContext& ctx);  // +0 & 0x20
void sub_2054C0(EEContext& ctx);  // the word +36
void sub_205500(EEContext& ctx);  // [bcmGetSelectedSkill] the skill id under the skill cursor
void sub_205550(EEContext& ctx);  // [bcmGetSelectedItem] the item id under the item cursor
void sub_2055A0(EEContext& ctx);  // [bcmGetSelectedPersona] the persona id under the persona cursor
void sub_2055F0(EEContext& ctx);  // [bcmIsSkillUsableInBattle] (skill) bit 1 of byte +1 of its 44-byte row; ids >= 464 -> 0
void sub_205650(EEContext& ctx);  // [bcmIsItemUsable] (item) the item record's +4 kind is 0 or 1
void sub_207930(EEContext& ctx);  // (item) its kind sub_17D2E0 != 12
void sub_207960(EEContext& ctx);  // (item) asserts its kind != 12, returns the kind
void sub_207F70(EEContext& ctx);  // +0 & 0x2000000
void sub_207FC0(EEContext& ctx);  // +0 & 0x4000000
void sub_208010(EEContext& ctx);  // sub_30C0C0() ? sub_249650(*result) : 0
void sub_208050(EEContext& ctx);  // [bcmIsBossFirstTime] encounters 466..469 while their flag 4871..4874 is clear
void sub_208130(EEContext& ctx);  // [bcmCanCallSupport] the navigator can be called (flags 223 / 4870, its status)
void sub_208720(EEContext& ctx);  // [bcmIsTopLevel] +16 == 0 && !(+0 & 0x20)
// Flags and debug switches
void sub_2085E0(EEContext& ctx);  // +0 |= 0x8000000
void sub_208630(EEContext& ctx);  // +0 &= ~0x8000000
void sub_208680(EEContext& ctx);  // +0 |= 0x10000000
void sub_2086D0(EEContext& ctx);  // +0 &= ~0x10000000
void sub_2079C0(EEContext& ctx);  // +30624 |= 1 ("ATTACK : OFF")
void sub_207A10(EEContext& ctx);  // +30624 |= 2
void sub_207A60(EEContext& ctx);  // +30624 |= 4
void sub_207AB0(EEContext& ctx);  // +30624 |= 8
void sub_207B00(EEContext& ctx);  // +30624 |= 0x10
void sub_207B50(EEContext& ctx);  // +30624 |= 0x20
void sub_207BA0(EEContext& ctx);  // +30624 |= 0x40
void sub_207BF0(EEContext& ctx);  // +30624 &= ~1
void sub_207C40(EEContext& ctx);  // +30624 &= ~2
void sub_207C90(EEContext& ctx);  // +30624 &= ~4
void sub_207CE0(EEContext& ctx);  // +30624 &= ~8
void sub_207D30(EEContext& ctx);  // +30624 &= ~0x10
void sub_207D80(EEContext& ctx);  // +30624 &= ~0x20
void sub_207DD0(EEContext& ctx);  // +30624 &= ~0x40
void sub_208570(EEContext& ctx);  // [bcmInitCursorRecord] (rec) +0 |= 4, colours cleared, alphas 0 / 5
// Navigator comments
void sub_208790(EEContext& ctx);  // [bcmNaviCommentRandomMember] on a random party-member row
void sub_208860(EEContext& ctx);  // [bcmNaviCommentMember] (pc id) the member's line (first time / again)

}  // namespace p3fes::game
