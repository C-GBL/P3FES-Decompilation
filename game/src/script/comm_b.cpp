// BF script COMM handlers, sScrCommandTable indices 251-501 (game/include/p3fes/game/comm_b.h),
// hand-decompiled from SLUS_216.21 (docs/ANALYSIS/18_script_vm.md sections 2.4, 3).
// tests/game/test_script_comm_b.cpp runs each against its __recomp body.
//
// Virtual time (ADR-0013): guest::enter / charge / backedge mirror the `ctx.cycles += N` blocks and the
// check points of the recompiled bodies; a block is charged at its start, before the callees it contains
// run. Every callee -- the replaced scr accessors (script_ops.cpp), the replaced g_data / datCalc
// functions and the still-recompiled ones -- is entered through its generated symbol with the argument
// registers the original set; a register the original forwarded whole (`daddu $a0, $v0, $zero`) is
// forwarded whole. Each handler that opens a stack frame keeps it (guest::StackFrame) so its callees'
// frames land where they did. K_Assert sub_19D3F0 is `jr $ra` in retail: a failed check goes on.
// The caller-saved registers the original writes after its last call ($at, $v1, $a0..$a3: base
// pointers, scaled indices, compare constants, loop counters) are left as it leaves them, set at the
// same point of the path (the pair tests compare every GPR).
// Guest words addressed through $gp are the constants of comm_b.h (crt0's $gp = 0x7D2CF0).
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 46 of the 48 functions here are p3fes_handgen's register-faithful
// bodies (their hand versions differed from the original: frame/spills 44, $v0 2); sub_10BF40 and sub_2D1560 are the
// hand-written versions this header describes. Readability pass 2026-10-21 (slice read_script) over the 46: each
// function's role with its sScrCommandTable index (decimal and hex) and arguments, the $gp globals and the fields
// it touches by name (cb:: below: EventWork, the field descriptor, btlAction / btlUnit / DatUnit, gBtl, KwlnTask),
// the accessor calls labelled (`// arg 1 (int)`, `// the COMM result`), block roles, and sub_1C3FE0's goto as a loop
// break. Every guest statement, frame, spill, link, cycle charge and check point is the generated body's, in order.
#include "p3fes/game/comm_b.h"

#include "p3fes/ee/core.h"
#include "p3fes/ee/fpu.h"
#include "p3fes/game/guest.h"

#include <initializer_list>
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
void fn_sub_19D3F0_0019d3f0(p3fes::EEContext&);  // K_Assert(file, line)
// the COMM-side accessors (replaced: game/src/script/script_ops.cpp)
void fn_scrGetIntPara_0035ed20(p3fes::EEContext&);
void fn_scrGetFloatPara_0035ee60(p3fes::EEContext&);
void fn_scrSetIntReturnVal_0035f060(p3fes::EEContext&);
void fn_scrGetCmdTimer_0035f130(p3fes::EEContext&);
void fn_scrGetUserData_0035f160(p3fes::EEContext&);
// g_data / calendar (replaced: ui.cpp, ui2.cpp, battle_data.cpp) and still recompiled
void fn_sub_16F380_0016f380(p3fes::EEContext&);
void fn_sub_16F3E0_0016f3e0(p3fes::EEContext&);
void fn_sub_16CF40_0016cf40(p3fes::EEContext&);
void fn_sub_16CF90_0016cf90(p3fes::EEContext&);
void fn_sub_170760_00170760(p3fes::EEContext&);
void fn_sub_170860_00170860(p3fes::EEContext&);
void fn_sub_170620_00170620(p3fes::EEContext&);
void fn_datGetDaysSinceApr5_0016ef20(p3fes::EEContext&);
void fn_datGetTime_0016ef30(p3fes::EEContext&);
void fn_sub_16F160_0016f160(p3fes::EEContext&);
void fn_sub_16F170_0016f170(p3fes::EEContext&);
void fn_sub_16F180_0016f180(p3fes::EEContext&);
void fn_sub_177A40_00177a40(p3fes::EEContext&);
void fn_sub_177A90_00177a90(p3fes::EEContext&);
void fn_sub_17D800_0017d800(p3fes::EEContext&);
void fn_clndGetCurrentMoonPhase_00181b10(p3fes::EEContext&);
void fn_sub_16C6F0_0016c6f0(p3fes::EEContext&);
void fn_sub_16C740_0016c740(p3fes::EEContext&);
void fn_sub_16C790_0016c790(p3fes::EEContext&);
void fn_datGetAcademicLevel_00177280(p3fes::EEContext&);
void fn_datGetCharmLevel_001772f0(p3fes::EEContext&);
void fn_datGetCourageLevel_00177360(p3fes::EEContext&);
// battle (replaced: battle_unit.cpp, battle_data.cpp)
void fn_sub_2FF310_002ff310(p3fes::EEContext&);
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);
void fn_datCalcGetHp_002ffd70(p3fes::EEContext&);
void fn_datCalcRand_002ffbc0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

using namespace comm_b;
using guest::Fn;

template <typename T> T ld(const EEContext& ctx, u32 va) { return guest::load<T>(ctx, va); }
template <typename T> void st(EEContext& ctx, u32 va, T v) { guest::store<T>(ctx, va, v); }
u32 ldw(const EEContext& ctx, u32 va) { return guest::load<u32>(ctx, va); }

// The words and fields the register-view bodies address, as instruction immediates (`lw(v0, gp, cb::gp_btl)`).
// Layouts: EventWork / the field descriptor (types/script_event.h, field.h), btlAction / btlUnit / DatUnit
// (battle_task.h, types/unit.h), gBtl (types/battle_state.h), KwlnTask (task.h).
namespace cb {
// $gp-relative globals (crt0's $gp = 0x7D2CF0); the absolute values are comm_b.h's.
constexpr s32 gp_event_work = -19052;     // 0x7CE284 EventWork*
constexpr s32 gp_field_params = -17924;   // 0x7CE6EC FieldParams* (the record the 0x425xxx handlers fill)
constexpr s32 gp_btl = -18692;            // 0x7CE3EC gBtl
constexpr s32 gp_skill_tbl = -18680;      // 0x7CE3F8 gBtlSkillTbl: 44-byte SkillRecords, byte 0 bit 1 = valid
constexpr s32 gp_encount_tbl = -18504;    // 0x7CE4A8 gEncountTbl: 28-byte records
constexpr s32 gp_calendar_task = -19716;  // 0x7CDFEC the calendar KwlnTask*
constexpr s32 gp_saved_words = -19784;    // 0x7CDFA8 s16[4]
static_assert(static_cast<u32>(0x7D2CF0 + gp_event_work) == kEventWork &&
              static_cast<u32>(0x7D2CF0 + gp_field_params) == kFieldParams &&
              static_cast<u32>(0x7D2CF0 + gp_btl) == kBattleWork &&
              static_cast<u32>(0x7D2CF0 + gp_skill_tbl) == kBattleTable44 &&
              static_cast<u32>(0x7D2CF0 + gp_encount_tbl) == kBattleTable28 &&
              static_cast<u32>(0x7D2CF0 + gp_calendar_task) == kCalendarTask &&
              static_cast<u32>(0x7D2CF0 + gp_saved_words) == kSavedWords);
constexpr s32 ev_field = 0x11C;            // EventWork: the current field descriptor (kFieldFloorPtr)
constexpr s32 ev_296 = 0x128;              // EventWork: u8 +296 (COMM 278's result)
constexpr s32 fd_id = 2, fd_flags = 7, fd_word8 = 8;  // field descriptor: u16 field id, u8 flags, s32 +8
constexpr s32 act_id = 8;                  // btlAction: the u32 the scripts name a unit by
constexpr s32 act_flags2 = 26;             // btlAction: u16, bit 0 = a combatant
constexpr s32 act_unit = 48;               // btlAction: btlUnit*
constexpr s32 act_move_kind = 108;         // btlAction: u16 move kind (1 attack, 2/3 skill, 9 summon)
constexpr s32 act_move_arg = 110;          // btlAction: u16, the move's skill
constexpr s32 act_next = 1192;             // btlAction: the next action in gBtl's list
constexpr s32 unit_side = 162;             // btlUnit: u8, 0 party / 1 enemy
constexpr s32 unit_dat = 2604;             // btlUnit: DatUnit*
constexpr s32 dat_flags = 0, dat_base_id = 4;  // DatUnit: u16 flags, u16 base id
constexpr s32 btl_actions = 332;           // gBtl: the first btlAction (kActionList)
constexpr s32 btl_setup = 3004;            // gBtl: the encounter setup (kSetupEnemies); its u16 +8 indexes gEncountTbl
constexpr s32 btl_script_words = 3376;     // gBtl: s32[] the battle scripts' words (COMM 402 / 403)
constexpr s32 task_work = 60;              // KwlnTask::work
constexpr s32 gdata_words = 17632;         // g_data (0x836200) + 17632: s16[4] (kGdataWords)
static_assert(0x836200u + gdata_words == kGdataWords);
}  // namespace cb

}  // namespace

// --- leaves ---------------------------------------------------------------------------------------------

// 0x001C3A10 sub_1C3A10 -- 84 bytes; frame 0x10: ra sp+0x0
// COMM 278 (0x116; no arguments; sScrCommandTable 0x7B92B0): with fd = EventWork->field, returns EventWork->u8[+296]
// when fd->id < 4000, else 0. Returns 1 (done). Blocks: 8; fd->id < 4000 -> 5, else 3; 5. $v1 = the EventWork,
// $at = the slti result.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1C3A10_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lhu, hg::lw, hg::sd, hg::slti;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c3a10
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, gp, cb::gp_event_work);  // EventWork* (0x7CE284)
    lw(v0, v1, cb::ev_field);  // EventWork::field (the current field descriptor)
    lhu(v0, v0, cb::fd_id);  // the field id
    at = slti(v0, 4000);  // field id < 4000
    if (at == 0) {
        // 0x001c3a44
        charge(ctx, 3);
        a0 = 0;
        jal(ctx, 0x1C3A48u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    } else {
        // 0x001c3a30
        charge(ctx, 5);
        lbu(a0, v1, cb::ev_296);  // EventWork->u8[+296]
        jal(ctx, 0x1C3A34u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    }
    // 0x001c3a50 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002CD8C0 sub_2CD8C0 -- 120 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 302 (0x12E; 1 argument): on the battle unit the script runs for (user data: a btlAction; ->unit->dat), sets
// DatUnit flag 0x10 when arg0 & 0xFFFF == 0 and clears it otherwise. Returns 1. Blocks: 12; set 7 / clear 5; 6.
// $v1 = the DatUnit.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_2CD8C0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq, hg::lw, hg::sd, hg::sh, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002cd8c0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x2CD8CCu, gen::fn_scrGetUserData_0035f160);
    s0 = v0;  // the btlAction the script runs for
    a0 = 0;
    jal(ctx, 0x2CD8DCu, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    v0 = v0 & 0xFFFF;
    if (v0 != 0) {  // arg0 != 0: clear DatUnit flag 0x10
        // 0x002cd90c
        charge(ctx, 5);
        lw(v0, s0, cb::act_unit);  // btlAction::unit (btlUnit*)
        lw(v1, v0, cb::unit_dat);  // btlUnit::dat (DatUnit*)
        lhu(v0, v1, 0);
        v0 = v0 & 0xFFEF;
        sh(v0, v1, 0);
    } else {  // arg0 == 0: set it
        // 0x002cd8f0
        charge(ctx, 7);
        lw(v0, s0, cb::act_unit);  // btlAction::unit (btlUnit*)
        lw(v1, v0, cb::unit_dat);  // btlUnit::dat (DatUnit*)
        lhu(v0, v1, 0);
        v0 = v0 | 0x10;
        sh(v0, v1, 0);
    }
    // 0x002cd920 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 1;  // done
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002CD940 sub_2CD940 -- 120 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 303 (0x12F; 1 argument): COMM 302 with DatUnit flag 0x20. Returns 1. Blocks: 12; set 7 / clear 5; 6.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_2CD940_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq, hg::lw, hg::sd, hg::sh, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002cd940
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x2CD94Cu, gen::fn_scrGetUserData_0035f160);
    s0 = v0;  // the btlAction the script runs for
    a0 = 0;
    jal(ctx, 0x2CD95Cu, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    v0 = v0 & 0xFFFF;
    if (v0 != 0) {  // arg0 != 0: clear DatUnit flag 0x20
        // 0x002cd98c
        charge(ctx, 5);
        lw(v0, s0, cb::act_unit);  // btlAction::unit (btlUnit*)
        lw(v1, v0, cb::unit_dat);  // btlUnit::dat (DatUnit*)
        lhu(v0, v1, 0);
        v0 = v0 & 0xFFDF;
        sh(v0, v1, 0);
    } else {  // arg0 == 0: set it
        // 0x002cd970
        charge(ctx, 7);
        lw(v0, s0, cb::act_unit);  // btlAction::unit (btlUnit*)
        lw(v1, v0, cb::unit_dat);  // btlUnit::dat (DatUnit*)
        lhu(v0, v1, 0);
        v0 = v0 | 0x20;
        sh(v0, v1, 0);
    }
    // 0x002cd9a0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 1;  // done
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001C3F60 sub_1C3F60 -- 48 bytes; frame 0x10: ra sp+0x0
// COMM 304 (0x130; no arguments): returns user->s32[+0], the length of the id list the user data holds (the
// field object the script runs for). Returns 1. One block of 12.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1C3F60_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c3f60
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1C3F68u, gen::fn_scrGetUserData_0035f160);
    lw(a0, v0, 0);  // user->s32[+0]: the id count
    jal(ctx, 0x1C3F74u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001C3F90 sub_1C3F90 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 305 (0x131; 1 argument): returns user->s32[+4 + 4 * arg0], entry arg0 of that id list (no bound check).
// Returns 1. One block of 20; the index is scaled with a 32-bit sll / addu ($v1 = 4 * index).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1C3F90_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sll, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c3f90
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x1C3FA0u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    s0 = v0;
    jal(ctx, 0x1C3FACu, gen::fn_scrGetUserData_0035f160);
    v1 = sll(s0, 2);
    v0 = addu(v1, v0);
    lw(a0, v0, 4);  // user->s32[+4 + 4 * arg0]
    jal(ctx, 0x1C3FC0u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001C3FE0 sub_1C3FE0 -- 148 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM 306 (0x132; 1 argument): returns 1 when arg0 is one of the user's ids (user->s32[+4 + 4i], i < user->s32[+0]),
// else 0. Returns 1. Blocks: 15; the test block (3, `slt $v1, $a1, $a0`) comes first and checks before every
// iteration; body 5, then a match -> 3 (found) or 1 (next); epilogue 10. The compare is on the whole sign-extended
// registers. Left behind: $a1 = i, $v1 = the matching word or 0 (the failed slt).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1C3FE0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::sll, hg::slt, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c3fe0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    Gpr &id = s0, &found = s1, &list = v0, &count = a0, &i = a1;
    a0 = 0;
    jal(ctx, 0x1C3FF4u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    id = v0;
    found = 0;
    jal(ctx, 0x1C4004u, gen::fn_scrGetUserData_0035f160);  // the id list: { s32 count; s32 ids[]; }
    i = 0;
    lw(count, list, 0);
    for (;;) {
        // 0x001c4040: for (i = 0; i < count; i++)
        charge(ctx, 3);
        v1 = slt(i, count);
        if (v1 == 0) {
            break;
        }
        backedge(ctx);
        // 0x001c401c
        charge(ctx, 5);
        v1 = sll(i, 2);
        v1 = addu(list, v1);
        lw(v1, v1, 4);
        if (v1 == id) {
            // 0x001c4030: ids[i] == arg0 -- found
            charge(ctx, 3);
            found = 1;
            break;
        }
        // 0x001c403c
        charge(ctx, 1);
        i = addiu(i, 1);
    }
    // 0x001c404c: return found
    charge(ctx, 10);
    a0 = found;
    jal(ctx, 0x1C4050u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001C4080 sub_1C4080 -- 160 bytes; frame 0x10: ra sp+0x0
// COMM 311 (0x137; 1 argument): r = the 448-byte record arg0 of 0x8717E8 (kFieldTable); returns *(u16*)r.+12 when
// both r.+0 and the pointer r.+12 are non-zero, else 0. Returns 1. Blocks: 16; +0 non-zero -> 6, +12 non-zero -> 1;
// 4; have -> 5; 8. The record offset is arg0 * 448 in 32 bits. Left behind: $v1 = (have != 0), $a1 = have,
// $a2 = the value.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1C4080_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lw, hg::sd, hg::sll,
          hg::sltu, hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c4080
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x1C408Cu, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    a2 = 0;
    a1 = 0;
    v1 = sll(v0, 3);  // a0 = arg0 * 448 (the record offset)
    v0 = subu(v1, v0);
    a0 = sll(v0, 6);
    v0 = 0x870000;
    v0 = addiu(v0, 6120);  // &0x8717E8 kFieldTable: r.+0
    v0 = addu(v0, a0);
    lw(v0, v0, 0);
    // have = r.+0 && r.+12
    if (v0 != 0) {
        // 0x001c40c0
        charge(ctx, 6);
        v0 = 0x870000;
        v0 = addiu(v0, 6132);  // &0x8717F4
        v0 = addu(v0, a0);
        lw(v0, v0, 0);
        if (v0 != 0) {
            // 0x001c40d8
            charge(ctx, 1);
            a1 = 1;
        }
    }
    // 0x001c40dc
    charge(ctx, 4);
    v1 = sltu(0, a1);  // have -> value = *(u16*)r.+12
    v0 = 1;
    if (v1 == v0) {
        // 0x001c40ec
        charge(ctx, 5);
        v0 = 0x870000;
        v0 = addiu(v0, 6132);  // &0x8717F4
        v0 = addu(v0, a0);
        lw(v0, v0, 0);
        lhu(a2, v0, 0);
    }
    // 0x001c4100
    charge(ctx, 8);
    a0 = a2 & 0xFFFF;  // value (0 without one)
    jal(ctx, 0x1C4104u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002CDA10 sub_2CDA10 -- 56 bytes; frame 0x10: ra sp+0x0
// COMM 318 (0x13E; no arguments): returns the base id (DatUnit u16 +4) of the battle unit the script runs for.
// Returns 1. One block of 14.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_2CDA10_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002cda10
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x2CDA18u, gen::fn_scrGetUserData_0035f160);
    lw(v0, v0, cb::act_unit);  // btlAction::unit (btlUnit*)
    lw(v0, v0, cb::unit_dat);  // btlUnit::dat (DatUnit*)
    lhu(a0, v0, cb::dat_base_id);  // DatUnit::base_id
    jal(ctx, 0x2CDA2Cu, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0016EB80 sub_16EB80 -- 96 bytes; leaf frame (no stack)
// COMM 326 (0x146; no arguments; a leaf without a frame): saves the four s16 words of g_data + 17632 (kGdataWords) to
// 0x7CDFA8 (kSavedWords). Returns 1. Blocks: 6; the test block 5 first (a check before every iteration), body 10;
// 3. Left behind: $a3 = 4 (the counter), $a0 = the last word, $a2 = 6 (its byte offset), the bases $a1 / $v1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_16EB80_regs(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lh, hg::sh,
          hg::sll, hg::slti;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x0016eb80
    enter(ctx, 6);  // entry check point + this block's cycles
    a3 = 0;
    a1 = 0x830000;
    a1 = addiu(a1, 25088);  // &0x836200 g_data (the words are at + 17632)
    v1 = addiu(gp, cb::gp_saved_words);  // &0x7CDFA8: s16[4]
    for (;;) {  // for (i = 0; (s16)i < 4; i++) saved[i] = gdata_words[i]
        // 0x0016ebc0
        charge(ctx, 5);
        v0 = dsll32(a3, 16);
        v0 = dsra32(v0, 16);
        v0 = slti(v0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0016eb98
        charge(ctx, 10);
        v0 = dsll32(a3, 16);
        v0 = dsra32(v0, 16);
        a2 = sll(v0, 1);
        v0 = addu(a1, a2);
        lh(a0, v0, cb::gdata_words);  // g_data + 17632: s16[4] (kGdataWords)
        v0 = addu(v1, a2);
        sh(a0, v0, 0);
        v0 = addiu(a3, 1);
        a3 = dsll32(v0, 16);
        a3 = dsra32(a3, 16);
    }
    // 0x0016ebd4
    charge(ctx, 3);
    v0 = 1;
}

// 0x0016EBE0 sub_16EBE0 -- 96 bytes; leaf frame (no stack)
// COMM 327 (0x147; no arguments; leaf): restores the four words: kGdataWords[i] = kSavedWords[i]. Returns 1.
// Blocks as COMM 326.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_16EBE0_regs(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::lh, hg::sh,
          hg::sll, hg::slti;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, gp{ctx, 28};
    // 0x0016ebe0
    enter(ctx, 6);  // entry check point + this block's cycles
    a3 = 0;
    a1 = addiu(gp, cb::gp_saved_words);  // &0x7CDFA8: s16[4]
    v1 = 0x830000;
    v1 = addiu(v1, 25088);  // &0x836200 g_data (the words are at + 17632)
    for (;;) {  // for (i = 0; (s16)i < 4; i++) gdata_words[i] = saved[i]
        // 0x0016ec20
        charge(ctx, 5);
        v0 = dsll32(a3, 16);
        v0 = dsra32(v0, 16);
        v0 = slti(v0, 4);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0016ebf8
        charge(ctx, 10);
        v0 = dsll32(a3, 16);
        v0 = dsra32(v0, 16);
        a2 = sll(v0, 1);
        v0 = addu(a1, a2);
        lh(a0, v0, 0);
        v0 = addu(v1, a2);
        sh(a0, v0, cb::gdata_words);  // g_data + 17632: s16[4] (kGdataWords)
        v0 = addiu(a3, 1);
        a3 = dsll32(v0, 16);
        a3 = dsra32(a3, 16);
    }
    // 0x0016ec34
    charge(ctx, 3);
    v0 = 1;
}

// 0x001C3950 sub_1C3950 -- 56 bytes; frame 0x10: ra sp+0x0
// COMM 361 (0x169; no arguments): returns bit 0 of the current field descriptor's flag byte (+7). Returns 1.
// One block of 14.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1C3950_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lw, hg::sd, hg::sltu;
    Gpr v0{ctx, 2}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c3950
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, cb::gp_event_work);  // EventWork* (0x7CE284)
    lw(v0, v0, cb::ev_field);  // EventWork::field (the current field descriptor)
    lbu(v0, v0, cb::fd_flags);  // the field descriptor's flags; bit 0
    v0 = v0 & 0x1;
    a0 = sltu(0, v0);
    jal(ctx, 0x1C396Cu, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004250B0 sub_4250B0 -- 48 bytes; frame 0x10: ra sp+0x0
// COMM 364 (0x16C; 1 argument): FieldParams->u8[+173] = arg0. Returns 1. One block of 12 ($v1 = FieldParams).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4250B0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lw, hg::sb, hg::sd;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004250b0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x4250BCu, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    lw(v1, gp, cb::gp_field_params);  // FieldParams* (0x7CE6EC)
    sb(v0, v1, 173);  // FieldParams->u8[+173] = arg0
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00425270 sub_425270 -- 48 bytes; frame 0x10: ra sp+0x0
// COMM 368 (0x170; 1 argument): FieldParams->u8[+174] = arg0. Returns 1. One block of 12.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_425270_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lw, hg::sb, hg::sd;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00425270
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x42527Cu, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    lw(v1, gp, cb::gp_field_params);  // FieldParams* (0x7CE6EC)
    sb(v0, v1, 174);  // FieldParams->u8[+174] = arg0
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004252A0 sub_4252A0 -- 48 bytes; frame 0x10: ra sp+0x0
// COMM 379 (0x17B; 1 argument): FieldParams->u8[+175] = arg0. Returns 1. One block of 12.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4252A0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lw, hg::sb, hg::sd;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004252a0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x4252ACu, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    lw(v1, gp, cb::gp_field_params);  // FieldParams* (0x7CE6EC)
    sb(v0, v1, 175);  // FieldParams->u8[+175] = arg0
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004250E0 sub_4250E0 -- 176 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM 365 (0x16D; 3 arguments): slot i = (s8)((s8)arg0 - 1) of FieldParams' 6-byte records at +124: u16 +124 = arg2,
// +126 = +128 = 0; and the byte +166 + i = (s8)arg1. Returns 1. One block of 44; FieldParams is reloaded before each
// store. Left behind: $a1 = the slot, $a0 = its byte offset (6 i), $v1 = the first record address.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4250E0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sb,
          hg::sd, hg::sh, hg::sll, hg::sq;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x004250e0
    enter(ctx, 44);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x4250F4u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    s1 = dsll32(v0, 24);
    s1 = dsra32(s1, 24);
    a0 = 1;
    jal(ctx, 0x425108u, gen::fn_scrGetIntPara_0035ed20);  // arg 1 (int)
    s0 = dsll32(v0, 24);
    s0 = dsra32(s0, 24);
    a0 = 2;
    jal(ctx, 0x42511Cu, gen::fn_scrGetIntPara_0035ed20);  // arg 2 (int)
    v1 = dsll32(s1, 24);
    v1 = dsra32(v1, 24);
    v1 = addiu(v1, -1);  // slot i = (s8)(arg0 - 1); a0 = 6 i
    a1 = dsll32(v1, 24);
    a1 = dsra32(a1, 24);
    v1 = sll(a1, 1);
    v1 = addu(v1, a1);
    a0 = sll(v1, 1);
    lw(v1, gp, cb::gp_field_params);  // FieldParams* (0x7CE6EC)
    v1 = addu(a0, v1);
    sh(v0, v1, 124);  // record i: u16 +124 = arg2
    lw(v0, gp, cb::gp_field_params);  // FieldParams* (0x7CE6EC)
    v0 = addu(a0, v0);
    sh(zero, v0, 126);  // u16 +126 = 0
    lw(v0, gp, cb::gp_field_params);  // FieldParams* (0x7CE6EC)
    v0 = addu(a0, v0);
    sh(zero, v0, 128);  // u16 +128 = 0
    lw(v0, gp, cb::gp_field_params);  // FieldParams* (0x7CE6EC)
    v0 = addu(a1, v0);
    sb(s0, v0, 166);  // u8 +166 + i = (s8)arg1
    v0 = 1;  // done
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00425190 sub_425190 -- 136 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 366 (0x16E; 2 arguments): when arg0 != 0 appends { u8 arg0 at +4, u16 arg1 at +6 } in the 4-byte entry
// FieldParams->s8[+160] (the entry count) and increments the count. Returns 1. Blocks: 8; arg0 != 0 (whole register)
// -> 20; 6.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_425190_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::lb, hg::ld, hg::lq, hg::lw, hg::sb,
          hg::sd, hg::sh, hg::sll, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00425190
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x4251A0u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    if (v0 != 0) {  // arg0 != 0: append { arg0, arg1 } as entry FieldParams->s8[+160]
        // 0x004251b0
        charge(ctx, 20);
        lw(s0, gp, cb::gp_field_params);  // FieldParams* (0x7CE6EC)
        a0 = 0;
        jal(ctx, 0x4251B8u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
        lb(v1, s0, 160);
        v1 = sll(v1, 2);
        v1 = addu(v1, s0);
        sb(v0, v1, 4);  // entry +4: u8 arg0
        lw(s0, gp, cb::gp_field_params);  // FieldParams* (0x7CE6EC)
        a0 = 1;
        jal(ctx, 0x4251D8u, gen::fn_scrGetIntPara_0035ed20);  // arg 1 (int)
        lb(v1, s0, 160);
        v1 = sll(v1, 2);
        v1 = addu(v1, s0);
        sh(v0, v1, 6);  // entry +6: u16 arg1
        lw(v1, gp, cb::gp_field_params);  // FieldParams* (0x7CE6EC)
        lb(v0, v1, 160);
        v0 = addiu(v0, 1);
        sb(v0, v1, 160);  // the entry count += 1
    }
    // 0x00425200 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = 1;  // done
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00425220 sub_425220 -- 68 bytes; frame 0x10: ra sp+0x0
// COMM 367 (0x16F; 2 arguments): FieldParams->u8[+164] = arg0, ->u16[+162] = arg1. Returns 1. One block of 17.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_425220_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lw, hg::sb, hg::sd, hg::sh;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00425220
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x42522Cu, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    lw(v1, gp, cb::gp_field_params);  // FieldParams* (0x7CE6EC)
    sb(v0, v1, 164);  // FieldParams->u8[+164] = arg0
    a0 = 1;
    jal(ctx, 0x425240u, gen::fn_scrGetIntPara_0035ed20);  // arg 1 (int)
    lw(v1, gp, cb::gp_field_params);  // FieldParams* (0x7CE6EC)
    sh(v0, v1, 162);  // FieldParams->u16[+162] = arg1
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002D0A30 sub_2D0A30 -- 144 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM 385 (0x181; 1 argument: a skill): asserts gBtlSkillTbl[arg0] is valid (byte 0 bit 1; K_Assert
// "btlAIScript.c" line 4491, a no-op), then makes the acting btlAction (user data) use it: move kind = 1, move arg =
// arg0. Returns 1. Blocks: 22; invalid -> 5 + K_Assert; 9. The record offset is arg0 * 44 in 32 bits.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_2D0A30_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::sh, hg::sll, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d0a30
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x2D0A40u, gen::fn_scrGetUserData_0035f160);
    s1 = v0;  // the acting btlAction
    a0 = 0;
    jal(ctx, 0x2D0A50u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    s0 = v0;
    v0 = sll(s0, 2);  // v1 = arg0 * 44: the skill's SkillRecord
    v0 = addu(v0, s0);
    v0 = sll(v0, 1);
    v0 = addu(v0, s0);
    v1 = sll(v0, 2);
    lw(v0, gp, cb::gp_skill_tbl);  // gBtlSkillTbl (0x7CE3F8: 44-byte SkillRecords)
    v0 = addu(v0, v1);
    lbu(v0, v0, 0);
    v0 = v0 & 0x2;  // byte 0 bit 1: a valid skill
    if (v0 == 0) {
        // 0x002d0a88
        charge(ctx, 5);
        a0 = 0x690000;
        a0 = addiu(a0, 30496);  // "btlAIScript.c"
        a1 = 4491;
        jal(ctx, 0x2D0A94u, gen::fn_sub_19D3F0_0019d3f0);  // K_Assert(file, line): a no-op in retail
    }
    // 0x002d0a9c (the shared epilogue, written out on this path)
    charge(ctx, 9);
    v0 = 1;
    sh(v0, s1, cb::act_move_kind);  // move kind 1
    sh(s0, s1, cb::act_move_arg);  // the skill
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x002D14D0 sub_2D14D0 -- 64 bytes; frame 0x10: ra sp+0x0
// COMM 402 (0x192; 1 argument): returns gBtl->script_words[arg0]. Returns 1. One block of 16.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_2D14D0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d14d0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x2D14DCu, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    lw(v1, gp, cb::gp_btl);  // gBtl (0x7CE3EC)
    v0 = sll(v0, 2);
    v0 = addu(v0, v1);
    lw(a0, v0, cb::btl_script_words);  // gBtl->script_words[i]
    jal(ctx, 0x2D14F4u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002D1510 sub_2D1510 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 403 (0x193; 2 arguments): gBtl->script_words[arg0] = arg1. Returns 1. One block of 20.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_2D1510_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sll, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d1510
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x2D1520u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    s0 = v0;
    a0 = 1;
    jal(ctx, 0x2D1530u, gen::fn_scrGetIntPara_0035ed20);  // arg 1 (int)
    lw(a0, gp, cb::gp_btl);  // gBtl (0x7CE3EC)
    v1 = sll(s0, 2);
    v1 = addu(v1, a0);
    sw(v0, v1, cb::btl_script_words);  // gBtl->script_words[i]
    v0 = 1;  // done
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002D0CB0 sub_2D0CB0 -- 80 bytes; frame 0x10: ra sp+0x0
// COMM 413 (0x19D; no arguments): returns 1 when the current encounter's gEncountTbl record (the u16 +8 of gBtl's
// setup, 28-byte records) has flag 0x20 in its first word, else 0. Returns 1. One block of 20.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_2D0CB0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lw, hg::sd, hg::sll, hg::sltu,
          hg::subu;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d0cb0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, cb::gp_btl);  // gBtl (0x7CE3EC)
    lw(v0, v0, cb::btl_setup);  // gBtl->setup (the encounter setup)
    lhu(v1, v0, 8);  // the encounter id; v1 = id * 28: its gEncountTbl record
    v0 = sll(v1, 3);
    v0 = subu(v0, v1);
    v1 = sll(v0, 2);
    lw(v0, gp, cb::gp_encount_tbl);  // gEncountTbl (0x7CE4A8: 28-byte records)
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
    v0 = v0 & 0x20;  // flag 0x20 of the record's first word
    a0 = sltu(0, v0);
    jal(ctx, 0x2D0CE4u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x004253D0 sub_4253D0 -- 168 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 415 (0x19F; 4 arguments): r = 0x86BE00 (kVec4Table) + 16 * (s16)arg0: s32 r+0 = arg1, f32 r+4 = (f32)arg2,
// f32 r+12 = (f32)arg3 (cvt.s.w through $f0, which keeps arg3). Returns 1. One block of 42.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_4253D0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::cvt_s_w, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld,
          hg::lq, hg::mtc1, hg::sd, hg::sll, hg::sq, hg::sw, hg::swc1;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x004253d0
    enter(ctx, 42);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x4253E0u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    v0 = dsll32(v0, 16);
    v0 = dsra32(v0, 16);
    s0 = sll(v0, 4);  // the record offset 16 * (s16)arg0
    a0 = 1;
    jal(ctx, 0x4253F8u, gen::fn_scrGetIntPara_0035ed20);  // arg 1 (int)
    v1 = 0x870000;
    v1 = addiu(v1, -16896);  // &0x86BE00 kVec4Table: s32 +0 = arg1
    v1 = addu(v1, s0);
    sw(v0, v1, 0);
    a0 = 2;
    jal(ctx, 0x425414u, gen::fn_scrGetIntPara_0035ed20);  // arg 2 (int)
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    v0 = 0x870000;
    v0 = addiu(v0, -16892);  // &0x86BE04: f32 +4 = (f32)arg2
    v0 = addu(v0, s0);
    swc1(f0, v0, 0);
    a0 = 3;
    jal(ctx, 0x42543Cu, gen::fn_scrGetIntPara_0035ed20);  // arg 3 (int)
    mtc1(v0, f0);
    cvt_s_w(f0, f0);
    v0 = 0x870000;
    v0 = addiu(v0, -16884);  // &0x86BE0C: f32 +12 = (f32)arg3
    v0 = addu(v0, s0);
    swc1(f0, v0, 0);
    v0 = 1;  // done
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001C3990 sub_1C3990 -- 68 bytes; frame 0x10: ra sp+0x0
// COMM 416 (0x1A0; no arguments): returns the current field descriptor's s32 +8 when its field id is 4021, else 0.
// Returns 1. Blocks: 9; id == 4021 -> 1; 7.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1C3990_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lw, hg::sd;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c3990
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, cb::gp_event_work);  // EventWork* (0x7CE284)
    a0 = 0;
    lw(a1, v0, cb::ev_field);  // EventWork::field (the current field descriptor)
    lhu(v1, a1, cb::fd_id);  // the field id
    v0 = kField4021;
    if (v1 == v0) {
        // 0x001c39b4
        charge(ctx, 1);
        lw(a0, a1, cb::fd_word8);  // field 4021: the descriptor's s32 +8
    }
    // 0x001c39b8
    charge(ctx, 7);
    jal(ctx, 0x1C39B8u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00424F10 sub_424F10 -- 112 bytes; frame 0x10: ra sp+0x0
// COMM 417 (0x1A1; no arguments): for the user data (a field object): 0 when its u16 +426 is 4021, else 1 when bit 0
// of its u16 +428 is set, else 2. Returns 1. Blocks: 8; == 4021 -> 3; else 4, then 3 or 1; 9.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_424F10_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lhu, hg::sd;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00424f10
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x424F18u, gen::fn_scrGetUserData_0035f160);
    lhu(a0, v0, 426);  // the field object's u16 +426
    v1 = kField4021;
    if (a0 != v1) {
        // 0x00424f3c
        charge(ctx, 4);
        lhu(v0, v0, 428);  // u16 +428, bit 0
        v0 = v0 & 0x1;
        if (v0 == 0) {
            // 0x00424f58
            charge(ctx, 1);
            v0 = 2;
        } else {
            // 0x00424f4c
            charge(ctx, 3);
            v0 = 1;
        }
    } else {
        // 0x00424f30
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00424f5c
    charge(ctx, 9);
    a0 = dsll32(v0, 16);
    a0 = dsra32(a0, 16);
    jal(ctx, 0x424F64u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

u32 sub_10BF40(EEContext& ctx) {
    // 0x10BF40, leaf: 3; no object -> 3 (1); else 4 (s16 +484 of its work == 0); 2.
    guest::enter(ctx, 3);
    const u32 task = ldw(ctx, kFieldTask);
    u32 done;
    if (task == 0) {
        guest::charge(ctx, 3);
        done = 1;
    } else {
        guest::charge(ctx, 4);
        done = ld<s16>(ctx, ldw(ctx, task + 60) + 484) == 0 ? 1u : 0u;
    }
    guest::charge(ctx, 2);
    return done;
}

u32 sub_2D1560(EEContext& ctx) {
    guest::enter(ctx, 3);  // 0x2D1560: leaf, return 1
    return 1;
}

// 0x002D0EF0 sub_2D0EF0 -- 148 bytes; frame 0x10: ra sp+0x0
// COMM 435 (0x1B3; 6 float arguments): two float triples into the battle work at 0x957170: args 0..2 -> 0x957170 /
// 174 / 178, args 3..5 -> 0x957150 / 154 / 158 (kBattleFloatsA, -0x20). Returns 1. One block of 37.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_2D0EF0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd, hg::swc1;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x002d0ef0
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x2D0EFCu, gen::fn_scrGetFloatPara_0035ee60);  // arg 0 (float)
    v0 = 0x950000;
    swc1(f0, v0, 29040);  // 0x957170
    a0 = 1;
    jal(ctx, 0x2D0F10u, gen::fn_scrGetFloatPara_0035ee60);  // arg 1 (float)
    v0 = 0x950000;
    swc1(f0, v0, 29044);  // 0x957174
    a0 = 2;
    jal(ctx, 0x2D0F24u, gen::fn_scrGetFloatPara_0035ee60);  // arg 2 (float)
    v0 = 0x950000;
    swc1(f0, v0, 29048);  // 0x957178
    a0 = 3;
    jal(ctx, 0x2D0F38u, gen::fn_scrGetFloatPara_0035ee60);  // arg 3 (float)
    v0 = 0x950000;
    swc1(f0, v0, 29008);  // 0x957150
    a0 = 4;
    jal(ctx, 0x2D0F4Cu, gen::fn_scrGetFloatPara_0035ee60);  // arg 4 (float)
    v0 = 0x950000;
    swc1(f0, v0, 29012);  // 0x957154
    a0 = 5;
    jal(ctx, 0x2D0F60u, gen::fn_scrGetFloatPara_0035ee60);  // arg 5 (float)
    v0 = 0x950000;
    swc1(f0, v0, 29016);  // 0x957158
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002D0F90 sub_2D0F90 -- 148 bytes; frame 0x10: ra sp+0x0
// COMM 436 (0x1B4; 6 float arguments): the same at 0x957160 (args 0..2) and 0x957140 (args 3..5) (kBattleFloatsB).
// Returns 1. One block of 37.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_2D0F90_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd, hg::swc1;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0};
    // 0x002d0f90
    enter(ctx, 37);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x2D0F9Cu, gen::fn_scrGetFloatPara_0035ee60);  // arg 0 (float)
    v0 = 0x950000;
    swc1(f0, v0, 29024);  // 0x957160
    a0 = 1;
    jal(ctx, 0x2D0FB0u, gen::fn_scrGetFloatPara_0035ee60);  // arg 1 (float)
    v0 = 0x950000;
    swc1(f0, v0, 29028);  // 0x957164
    a0 = 2;
    jal(ctx, 0x2D0FC4u, gen::fn_scrGetFloatPara_0035ee60);  // arg 2 (float)
    v0 = 0x950000;
    swc1(f0, v0, 29032);  // 0x957168
    a0 = 3;
    jal(ctx, 0x2D0FD8u, gen::fn_scrGetFloatPara_0035ee60);  // arg 3 (float)
    v0 = 0x950000;
    swc1(f0, v0, 28992);  // 0x957140
    a0 = 4;
    jal(ctx, 0x2D0FECu, gen::fn_scrGetFloatPara_0035ee60);  // arg 4 (float)
    v0 = 0x950000;
    swc1(f0, v0, 28996);  // 0x957144
    a0 = 5;
    jal(ctx, 0x2D1000u, gen::fn_scrGetFloatPara_0035ee60);  // arg 5 (float)
    v0 = 0x950000;
    swc1(f0, v0, 29000);  // 0x957148
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002CD9C0 sub_2CD9C0 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 493 (0x1ED; 2 arguments): on the acting btlAction (user data): u16 +128 = arg0, u8 +130 = arg1. Returns 1.
// One block of 20.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_2CD9C0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lq, hg::sb, hg::sd, hg::sh, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002cd9c0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    jal(ctx, 0x2CD9CCu, gen::fn_scrGetUserData_0035f160);
    s0 = v0;  // the acting btlAction
    a0 = 0;
    jal(ctx, 0x2CD9DCu, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    sh(v0, s0, 128);  // btlAction u16 +128 = arg0
    a0 = 1;
    jal(ctx, 0x2CD9ECu, gen::fn_scrGetIntPara_0035ed20);  // arg 1 (int)
    sb(v0, s0, 130);  // btlAction u8 +130 = arg1
    v0 = 1;  // done
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// --- one or two callees ------------------------------------------------------------------------------------

// 0x001C3C40 sub_1C3C40 -- 64 bytes; frame 0x10: ra sp+0x0
// COMM 276 (0x114; 1 argument): returns sub_16F380(arg0) [a g_data counter]. Returns 1. One block of 16; $v0 is
// forwarded whole.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1C3C40_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c3c40
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x1C3C4Cu, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    a0 = v0;
    jal(ctx, 0x1C3C58u, gen::fn_sub_16F380_0016f380);
    a0 = v0;
    jal(ctx, 0x1C3C64u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001C3C80 sub_1C3C80 -- 80 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 277 (0x115; 2 arguments): sub_16F3E0(arg0, arg1) [sets that counter]. No return value is set. Returns 1.
// One block of 20.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1C3C80_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c3c80
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x1C3C90u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    s0 = v0;
    a0 = 1;
    jal(ctx, 0x1C3CA0u, gen::fn_scrGetIntPara_0035ed20);  // arg 1 (int)
    a0 = s0;
    a1 = v0;
    jal(ctx, 0x1C3CB0u, gen::fn_sub_16F3E0_0016f3e0);
    v0 = 1;  // done
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001C2FF0 sub_1C2FF0 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 279 (0x117; 2 arguments): sub_16CF40((s16)arg0, (s16)arg1) [a character's u16 at +0 of its 868-byte record].
// Returns 1. One block of 22.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1C2FF0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c2ff0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x1C3000u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    s0 = v0;
    a0 = 1;
    jal(ctx, 0x1C3010u, gen::fn_scrGetIntPara_0035ed20);  // arg 1 (int)
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    a1 = dsll32(v0, 16);
    a1 = dsra32(a1, 16);
    jal(ctx, 0x1C3028u, gen::fn_sub_16CF40_0016cf40);
    v0 = 1;  // done
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001C30F0 sub_1C30F0 -- 88 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 280 (0x118; 2 arguments): sub_16CF90((s16)arg0, (s16)arg1). Returns 1. One block of 22.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1C30F0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c30f0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x1C3100u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    s0 = v0;
    a0 = 1;
    jal(ctx, 0x1C3110u, gen::fn_scrGetIntPara_0035ed20);  // arg 1 (int)
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    a1 = dsll32(v0, 16);
    a1 = dsra32(a1, 16);
    jal(ctx, 0x1C3128u, gen::fn_sub_16CF90_0016cf90);
    v0 = 1;  // done
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001C3590 sub_1C3590 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 282 (0x11A; 2 arguments): returns sub_170760((s16)arg0, (s16)arg1) & 0xFFFF. Returns 1. One block of 25.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1C3590_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c3590
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x1C35A0u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    s0 = v0;
    a0 = 1;
    jal(ctx, 0x1C35B0u, gen::fn_scrGetIntPara_0035ed20);  // arg 1 (int)
    a0 = dsll32(s0, 16);
    a0 = dsra32(a0, 16);
    a1 = dsll32(v0, 16);
    a1 = dsra32(a1, 16);
    jal(ctx, 0x1C35C8u, gen::fn_sub_170760_00170760);
    a0 = v0 & 0xFFFF;
    jal(ctx, 0x1C35D4u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001C3600 sub_1C3600 -- 132 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM 283 (0x11B; 3 arguments): sub_170860((s16)arg0, (s16)arg1, min(arg2, 99) & 0xFFFF). Returns 1. Blocks: 22;
// arg2 >= 100 (slti on the whole register) -> 1; 10.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1C3600_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd,
          hg::slti, hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c3600
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x1C3614u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    s1 = v0;
    a0 = 1;
    jal(ctx, 0x1C3624u, gen::fn_scrGetIntPara_0035ed20);  // arg 1 (int)
    s0 = v0;
    a0 = 2;
    jal(ctx, 0x1C3634u, gen::fn_scrGetIntPara_0035ed20);  // arg 2 (int)
    a0 = dsll32(s1, 16);
    a0 = dsra32(a0, 16);
    a1 = dsll32(s0, 16);
    a1 = dsra32(a1, 16);
    at = slti(v0, 100);  // arg2 >= 100 -> 99
    if (at == 0) {
        // 0x001c3658
        charge(ctx, 1);
        v0 = 99;
    }
    // 0x001c365c
    charge(ctx, 10);
    a2 = v0 & 0xFFFF;
    jal(ctx, 0x1C3660u, gen::fn_sub_170860_00170860);
    v0 = 1;  // done
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00181C20 clndScrCmd_TIME_SKIP -- 160 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM 295 (0x127; 1 argument: time slots to skip): t = datGetTime() + arg0, d = datGetDaysSinceApr5(); while t >= 9:
// t -= 9, d += 1; then the skip targets sub_16F160((s16)d), sub_16F170(t & 0xFF), sub_16F180(1). Returns 1.
// Blocks: 16; loop head 3 (t < 9 leaves), body 4 + the back-edge check; 17. Time and day count are 32-bit sums.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void clndScrCmd_TIME_SKIP_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld,
          hg::lq, hg::sd, hg::slti, hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00181c20
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x181C34u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    s0 = v0;  // t = arg0
    jal(ctx, 0x181C40u, gen::fn_datGetDaysSinceApr5_0016ef20);
    s1 = dsll32(v0, 16);  // d = (s16) days since April 5
    s1 = dsra32(s1, 16);
    jal(ctx, 0x181C50u, gen::fn_datGetTime_0016ef30);
    v0 = v0 & 0xFF;
    s0 = addu(v0, s0);  // t += the current time slot (u8)
    for (;;) {  // while (t >= 9) { t -= 9; d += 1; }
        // 0x00181c60
        charge(ctx, 3);
        at = slti(s0, 9);
        if (at != 0) {
            break;
        }
        // 0x00181c6c
        charge(ctx, 4);
        s0 = addiu(s0, -9);
        s1 = addiu(s1, 1);
        backedge(ctx);
    }
    // 0x00181c7c
    charge(ctx, 17);
    a0 = dsll32(s1, 16);  // the target day, slot and the skip flag
    a0 = dsra32(a0, 16);
    jal(ctx, 0x181C84u, gen::fn_sub_16F160_0016f160);
    a0 = s0 & 0xFF;
    jal(ctx, 0x181C90u, gen::fn_sub_16F170_0016f170);
    a0 = 1;
    jal(ctx, 0x181C9Cu, gen::fn_sub_16F180_0016f180);
    v0 = 1;  // done
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001C4D10 sub_1C4D10 -- 116 bytes; frame 0x30: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM 339 (0x153; 2 arguments): returns (sub_177A40(arg0 & 0xFFFF, arg1) != 0). Returns 1. Blocks: 18; non-zero
// -> 1; 10.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1C4D10_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c4d10
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    a0 = 0;
    jal(ctx, 0x1C4D28u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    s0 = v0 & 0xFFFF;
    a0 = 1;
    jal(ctx, 0x1C4D38u, gen::fn_scrGetIntPara_0035ed20);  // arg 1 (int)
    a0 = s0;
    a1 = v0;
    jal(ctx, 0x1C4D48u, gen::fn_sub_177A40_00177a40);
    if (v0 != 0) {
        // 0x001c4d58
        charge(ctx, 1);
        s1 = 1;
    }
    // 0x001c4d5c
    charge(ctx, 10);
    a0 = s1;
    jal(ctx, 0x1C4D60u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x001C4D90 sub_1C4D90 -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 340 (0x154; 2 arguments): returns sub_177A90(arg0 & 0xFFFF, arg1)->u8[+8]. Returns 1. One block of 23.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1C4D90_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lq, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c4d90
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x1C4DA0u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    s0 = v0 & 0xFFFF;
    a0 = 1;
    jal(ctx, 0x1C4DB0u, gen::fn_scrGetIntPara_0035ed20);  // arg 1 (int)
    a0 = s0;
    a1 = v0;
    jal(ctx, 0x1C4DC0u, gen::fn_sub_177A90_00177a90);
    lbu(a0, v0, 8);
    jal(ctx, 0x1C4DCCu, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x001C4DF0 sub_1C4DF0 -- 92 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 341 (0x155; 2 arguments): returns sub_177A90(arg0 & 0xFFFF, arg1)->u16[+0]. Returns 1. One block of 23.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1C4DF0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c4df0
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x1C4E00u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    s0 = v0 & 0xFFFF;
    a0 = 1;
    jal(ctx, 0x1C4E10u, gen::fn_scrGetIntPara_0035ed20);  // arg 1 (int)
    a0 = s0;
    a1 = v0;
    jal(ctx, 0x1C4E20u, gen::fn_sub_177A90_00177a90);
    lhu(a0, v0, 0);
    jal(ctx, 0x1C4E2Cu, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0017F990 sub_17F990 -- 124 bytes; frame 0x10: ra sp+0x0
// COMM 396 (0x18C; no arguments): when the calendar task exists, writes its work by scenario: The Answer
// (sub_17D800() != 0) -> +8 = 60, +0 = 8; The Journey -> +32 = 60, +0 = 24. Returns 1. Blocks: 5; no task -> 3;
// else 4 + sub_17D800, then 6 or 8; 1; 4. $v1 = the work pointer when there is a task.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_17F990_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017f990
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, gp, cb::gp_calendar_task);  // the calendar KwlnTask* (0x7CDFEC)
    if (v0 != 0) {  // the calendar task exists
        // 0x0017f9b0
        charge(ctx, 4);
        jal(ctx, 0x17F9B0u, gen::fn_sub_17D800_0017d800);
        if (v0 != 0) {  // The Answer: work +8 = 60, +0 = 8
            // 0x0017f9e0
            charge(ctx, 6);
            lw(v0, gp, cb::gp_calendar_task);  // the calendar KwlnTask* (0x7CDFEC)
            lw(v1, v0, cb::task_work);  // KwlnTask::work
            v0 = 60;
            sw(v0, v1, 8);
            v0 = 8;
            sw(v0, v1, 0);
        } else {  // The Journey: work +32 = 60, +0 = 24
            // 0x0017f9c0
            charge(ctx, 8);
            lw(v0, gp, cb::gp_calendar_task);  // the calendar KwlnTask* (0x7CDFEC)
            lw(v1, v0, cb::task_work);  // KwlnTask::work
            v0 = 60;
            sw(v0, v1, 32);
            v0 = 24;
            sw(v0, v1, 0);
        }
        // 0x0017f9f8
        charge(ctx, 1);
        v0 = 1;
    } else {
        // 0x0017f9a4
        charge(ctx, 3);
        v0 = 1;
    }
    // 0x0017f9fc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001C58D0 sub_1C58D0 -- 48 bytes; frame 0x10: ra sp+0x0
// COMM 398 (0x18E; no arguments): returns clndGetCurrentMoonPhase() & 0xFF. Returns 1. One block of 12.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1C58D0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c58d0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x1C58D8u, gen::fn_clndGetCurrentMoonPhase_00181b10);
    a0 = v0 & 0xFF;
    jal(ctx, 0x1C58E4u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x001C5E60 sub_1C5E60 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 489 (0x1E9; no arguments) [scrIsTheAnswer]: returns (sub_17D800() == 1), the scenario being The Answer.
// Returns 1. Blocks: 9; == 1 (whole register) -> 1; 9.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1C5E60_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c5e60
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = 0;
    jal(ctx, 0x1C5E70u, gen::fn_sub_17D800_0017d800);
    v1 = 1;
    if (v0 == v1) {  // sub_17D800() == 1: The Answer
        // 0x001c5e84
        charge(ctx, 1);
        s0 = v1;
    }
    // 0x001c5e88
    charge(ctx, 9);
    a0 = s0;
    jal(ctx, 0x1C5E8Cu, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0027D840 sub_27D840 -- 64 bytes; frame 0x10: ra sp+0x0
// COMM 451 (0x1C3; no arguments): a wait: 0 (run again) on the first frame (command timer <= 0), afterwards done
// once sub_2FF310() != 0. Blocks: 6; timer <= 0 -> 1; else 5; 4.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_27D840_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::i64, hg::jal, hg::ld, hg::sd, hg::sltu;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0027d840
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x27D848u, gen::fn_scrGetCmdTimer_0035f130);
    if (i64(v0) <= 0) {  // the first frame: run again next frame
        // 0x0027d86c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0027d858
        charge(ctx, 5);
        jal(ctx, 0x27D858u, gen::fn_sub_2FF310_002ff310);
        v0 = sltu(0, v0);  // done once sub_2FF310() != 0
    }
    // 0x0027d870 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002CE4E0 sub_2CE4E0 -- 224 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM 255 (0x0FF; no arguments): of the living enemy units (gBtl's action list: flags2 bits 0 and 3, unit side 1,
// !datCalcIsDead(dat, 0)), the one with the lowest HP (datCalcGetHp, u16, against a best of 0x0FFFFFFF): returns
// its action's id | 0x80000000. With none the id is read from address 8 (a null action), as retail does. Returns 1.
// Blocks: 12; the list walk tests first (2 + the back-edge check); per action 4, bit 0 -> 3, bit 3 -> 5 (side),
// alive -> 6 + datCalcIsDead, 8 + datCalcGetHp, lower -> 2; 1 (next); 13.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_2CE4E0_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lhu, hg::lq,
          hg::lui, hg::lw, hg::sd, hg::sltu, hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002ce4e0
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    v0 = 0xFFF0000;
    s0 = v0 | 0xFFFF;  // best HP 0x0FFFFFFF; s1 = the best action (none)
    lw(v0, gp, cb::gp_btl);  // gBtl (0x7CE3EC)
    lw(s2, v0, cb::btl_actions);  // for (s2 = gBtl->actions; s2; s2 = s2->next)
    for (;;) {
        // 0x002ce584
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002ce510
        charge(ctx, 4);
        lhu(v1, s2, cb::act_flags2);  // btlAction::flags2
        v0 = v1 & 0x1;  // flags2 bit 0 (a combatant), then bit 3
        if (v0 != 0) {
            // 0x002ce520
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 != 0) {
                // 0x002ce52c
                charge(ctx, 5);
                lw(a0, s2, cb::act_unit);  // btlAction::unit (btlUnit*)
                lbu(v1, a0, cb::unit_side);  // btlUnit::side (0 party, 1 enemy)
                v0 = 1;  // an enemy
                if (v1 == v0) {
                    // 0x002ce540
                    charge(ctx, 6);
                    lw(a0, a0, cb::unit_dat);  // btlUnit::dat (DatUnit*)
                    a1 = 0;  // datCalcIsDead(dat, 0)
                    jal(ctx, 0x2CE548u, gen::fn_datCalcIsDead_0030b5a0);
                    if (v0 == 0) {
                        // 0x002ce558
                        charge(ctx, 8);
                        lw(v0, s2, cb::act_unit);  // btlAction::unit (btlUnit*)
                        lw(a0, v0, cb::unit_dat);  // btlUnit::dat (DatUnit*)
                        jal(ctx, 0x2CE560u, gen::fn_datCalcGetHp_002ffd70);
                        v0 = v0 & 0xFFFF;
                        at = sltu(v0, s0);  // a lower HP: keep
                        if (at != 0) {
                            // 0x002ce578
                            charge(ctx, 2);
                            s1 = s2;
                            s0 = v0;
                        }
                    }
                }
            }
        }
        // 0x002ce580
        charge(ctx, 1);
        lw(s2, s2, cb::act_next);  // btlAction::next
    }
    // 0x002ce58c
    charge(ctx, 13);
    lw(v1, s1, cb::act_id);  // the best action's id | 0x80000000 (s1 == 0 reads address 8)
    v0 = lui(0x8000);
    a0 = v1 | v0;
    jal(ctx, 0x2CE598u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x002CFA40 sub_2CFA40 -- 220 bytes; frame 0x40: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM 320 (0x140; no arguments): COMM 255 for the party side (unit side 0): the living party member with the lowest
// HP, its id | 0x80000000. Returns 1. Blocks as COMM 255, with 4 for the side test.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_2CFA40_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::backedge, hg::charge, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lhu, hg::lq,
          hg::lui, hg::lw, hg::sd, hg::sltu, hg::sq;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002cfa40
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s1 = 0;
    v0 = 0xFFF0000;
    s0 = v0 | 0xFFFF;  // best HP 0x0FFFFFFF; s1 = the best action (none)
    lw(v0, gp, cb::gp_btl);  // gBtl (0x7CE3EC)
    lw(s2, v0, cb::btl_actions);  // for (s2 = gBtl->actions; s2; s2 = s2->next)
    for (;;) {
        // 0x002cfae0
        charge(ctx, 2);
        if (s2 == 0) {
            break;
        }
        backedge(ctx);
        // 0x002cfa70
        charge(ctx, 4);
        lhu(v1, s2, cb::act_flags2);  // btlAction::flags2
        v0 = v1 & 0x1;  // flags2 bit 0 (a combatant), then bit 3
        if (v0 != 0) {
            // 0x002cfa80
            charge(ctx, 3);
            v0 = v1 & 0x8;
            if (v0 != 0) {
                // 0x002cfa8c
                charge(ctx, 4);
                lw(v1, s2, cb::act_unit);  // btlAction::unit (btlUnit*)
                lbu(v0, v1, cb::unit_side);  // btlUnit::side (0 party, 1 enemy)
                if (v0 == 0) {  // a party member
                    // 0x002cfa9c
                    charge(ctx, 6);
                    lw(a0, v1, cb::unit_dat);  // btlUnit::dat (DatUnit*)
                    a1 = 0;  // datCalcIsDead(dat, 0)
                    jal(ctx, 0x2CFAA4u, gen::fn_datCalcIsDead_0030b5a0);
                    if (v0 == 0) {
                        // 0x002cfab4
                        charge(ctx, 8);
                        lw(v0, s2, cb::act_unit);  // btlAction::unit (btlUnit*)
                        lw(a0, v0, cb::unit_dat);  // btlUnit::dat (DatUnit*)
                        jal(ctx, 0x2CFABCu, gen::fn_datCalcGetHp_002ffd70);
                        v0 = v0 & 0xFFFF;
                        at = sltu(v0, s0);  // a lower HP: keep
                        if (at != 0) {
                            // 0x002cfad4
                            charge(ctx, 2);
                            s1 = s2;
                            s0 = v0;
                        }
                    }
                }
            }
        }
        // 0x002cfadc
        charge(ctx, 1);
        lw(s2, s2, cb::act_next);  // btlAction::next
    }
    // 0x002cfae8
    charge(ctx, 13);
    lw(v1, s1, cb::act_id);  // the best action's id | 0x80000000 (s1 == 0 reads address 8)
    v0 = lui(0x8000);
    a0 = v1 | v0;
    jal(ctx, 0x2CFAF4u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x001C3270 sub_1C3270 -- 252 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// COMM 483 (0x1E3; 2 arguments: character, stat): arg1 0 / 1 / 2 -> the academic / charm / courage level of
// character arg0's points (sub_16C6F0 / sub_16C740 / sub_16C790 -> datGet*Level), narrowed to s16; any other arg1 ->
// 0. Returns 1. Blocks: 14; == 2 -> 10; else 3, == 1 -> 12; else 2, == 0 -> 12; else 2; 8.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1C3270_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001c3270
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x1C3280u, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    s0 = v0;
    a0 = 1;
    jal(ctx, 0x1C3290u, gen::fn_scrGetIntPara_0035ed20);  // arg 1 (int)
    a0 = 0;
    v1 = 2;
    if (v0 == v1) {  // stat 2: courage
        // 0x001c3324
        charge(ctx, 10);
        a0 = dsll32(s0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x1C332Cu, gen::fn_sub_16C790_0016c790);
        a0 = dsll32(v0, 16);
        a0 = dsra32(a0, 16);
        jal(ctx, 0x1C333Cu, gen::fn_datGetCourageLevel_00177360);
        a0 = dsll32(v0, 16);
        a0 = dsra32(a0, 16);
    } else {
        // 0x001c32a8
        charge(ctx, 3);
        v1 = 1;
        if (v0 == v1) {  // stat 1: charm
            // 0x001c32f4
            charge(ctx, 12);
            a0 = dsll32(s0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x1C32FCu, gen::fn_sub_16C740_0016c740);
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
            jal(ctx, 0x1C330Cu, gen::fn_datGetCharmLevel_001772f0);
            a0 = dsll32(v0, 16);
            a0 = dsra32(a0, 16);
        } else {
            // 0x001c32b4
            charge(ctx, 2);
            if (v0 == 0) {  // stat 0: academics
                // 0x001c32c4
                charge(ctx, 12);
                a0 = dsll32(s0, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x1C32CCu, gen::fn_sub_16C6F0_0016c6f0);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
                jal(ctx, 0x1C32DCu, gen::fn_datGetAcademicLevel_00177280);
                a0 = dsll32(v0, 16);
                a0 = dsra32(a0, 16);
            } else {
                // 0x001c32bc
                charge(ctx, 2);
            }
        }
    }
    // 0x001c334c
    charge(ctx, 8);
    jal(ctx, 0x1C334Cu, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x002D1490 sub_2D1490 -- 64 bytes; frame 0x10: ra sp+0x0
// COMM 307 (0x133; 1 argument): returns datCalcRand(arg0). Returns 1. One block of 16; $v0 forwarded whole both
// times.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_2D1490_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::sd;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002d1490
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a0 = 0;
    jal(ctx, 0x2D149Cu, gen::fn_scrGetIntPara_0035ed20);  // arg 0 (int)
    a0 = v0;
    jal(ctx, 0x2D14A8u, gen::fn_datCalcRand_002ffbc0);
    a0 = v0;
    jal(ctx, 0x2D14B4u, gen::fn_scrSetIntReturnVal_0035f060);  // the COMM result
    v0 = 1;  // done
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0017FD30 sub_17FD30 -- 220 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// COMM 494 (0x1EE; no arguments): for characters 2..10 and slots 0..11, stores the s16 pair of row c, slot s of the
// .data table 0x5E3C20 (kSkillRowTable: 48-byte rows, row c at +48c - 96) into sub_170620(c, s)'s u16[0] / u16[1].
// Returns 1. Blocks: 10; both loops test first (3 + the back-edge check); outer body 9, inner body 19, outer step 1;
// epilogue 10.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_17FD30_regs(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld,
          hg::lh, hg::lq, hg::sd, hg::sh, hg::sll, hg::slti, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0017fd30
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(s4, sp, 0x40);
    sq(s3, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(s0, sp, 0x0);
    s2 = 2;  // for (c = 2; c < 11; c++)
    for (;;) {
        // 0x0017fdd8
        charge(ctx, 3);
        v0 = slti(s2, 11);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
        // 0x0017fd58
        charge(ctx, 9);
        s1 = 0;  // for (s = 0; s < 12; s++); s0 = 0x5E3C20 + 48 c (row c at s0 - 96)
        v0 = sll(s2, 1);
        v0 = addu(v0, s2);
        v1 = sll(v0, 4);
        v0 = 0x5E0000;
        v0 = addiu(v0, 15392);  // &0x5E3C20
        s0 = addu(v0, v1);
        for (;;) {
            // 0x0017fdc8
            charge(ctx, 3);
            v0 = slti(s1, 12);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
            // 0x0017fd7c
            charge(ctx, 19);
            v0 = sll(s1, 2);
            s4 = addu(s0, v0);
            lh(s3, s4, -96);  // sub_170620(c, s)->u16[0] = row[s].first
            a0 = dsll32(s2, 16);
            a0 = dsra32(a0, 16);
            a1 = dsll32(s1, 16);
            a1 = dsra32(a1, 16);
            jal(ctx, 0x17FD98u, gen::fn_sub_170620_00170620);
            sh(s3, v0, 0);
            lh(s3, s4, -94);  // sub_170620(c, s)->u16[1] = row[s].second
            a0 = dsll32(s2, 16);
            a0 = dsra32(a0, 16);
            a1 = dsll32(s1, 16);
            a1 = dsra32(a1, 16);
            jal(ctx, 0x17FDB8u, gen::fn_sub_170620_00170620);
            sh(s3, v0, 2);
            s1 = addiu(s1, 1);
        }
        // 0x0017fdd4
        charge(ctx, 1);
        s2 = addiu(s2, 1);
    }
    // 0x0017fde4
    charge(ctx, 10);
    v0 = 1;  // done
    ld(ra, sp, 0x50);
    lq(s4, sp, 0x40);
    lq(s3, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x60);
}

}  // namespace p3fes::game

// --- the recompiled program's entry points (signatures from recomp/generated/functions.h) ---------------
namespace p3fes::recomp_gen {

using namespace p3fes::game;

#define P3FES_COMM_B_SHIM(name, addr) \
    void fn_##name##_##addr(p3fes::EEContext& ctx) { guest::ret32(ctx, name(ctx)); }
P3FES_COMM_B_SHIM(sub_10BF40, 0010bf40)
P3FES_COMM_B_SHIM(sub_2D1560, 002d1560)
#undef P3FES_COMM_B_SHIM

}  // namespace p3fes::recomp_gen
