// Menu / UI layer 3 (game/include/p3fes/game/ui3.h), hand-decompiled from SLUS_216.21 (docs/ANALYSIS/20_menu_ui.md
// sections 2-3). Phase 5 slice `ui3`: these replace the recompiled bodies listed in game/replaced.txt;
// tests/game/test_ui3.cpp runs each against its __recomp body.
//
// How the camp menu runs through this file. The field event task creates "H_CampDraw" (H_Camp_CreateDrawTask); the kwln
// kernel calls H_Camp_UpdateDrawTask every frame. State 0 starts the loaders (the camp PAK / SPR setup task, the persona
// texture task, the flash-control task, the two side portraits), state 1 waits for the setup task and raises flag
// 0x1407 ("camp open", which slides the date HUD away, H_DayPartsPos_UpdateTask), state 2 creates the main list
// "H_CampRootDraw" (or fades the existing one back in) and state 3 polls its selection: Skill / Item / Persona / Equip /
// Status / S.Link / System open their screen task (states 19 / 17 / 11 / 5 / 9 / 13 / 15), whose finish (kwln state 3)
// brings the menu back to state 2; cancel (-2) closes the list and the menu ends once the list task is gone (state 4).
// H_Camp_UpdateRootDrawTask is the list: open animation (states 0-3, then 4 slide or 5 fade), the input state 6
// (cancel / confirm, up / down with wrap-around, S.Link skipped in The Answer), the close animations 7 / 8 / 9 and the
// confirm flash 10. The two side portraits (protagonist and persona, sub_121DE0 / sub_122710) are told which screen
// is current on every transition and pick their pose animation from (old screen, new screen).
//
// The date / time HUD ("H_DayPartsDraw" + "H_DayPartsPos", created by H_DayParts_CreateTask under the calendar task)
// runs on every field frame, so the dorm and M1 replays exercise H_DayPartsPos_UpdateTask and H_DayPartsDraw_UpdateTask.
//
// Virtual time per ADR-0013: every guest::enter / charge mirrors a `ctx.cycles += N` block of the recompiled body on
// the executed path, charged where the block starts (before its calls), and guest::backedge sits where the recompiled
// loop checks before jumping back.
//
// Register discipline (docs/PHASE5_AGENT_BRIEF.md, the wave-6 / wave-7 lessons). These functions are entered through
// `jalr` from the kwln task kernel or called by recompiled screens, and a check point may preempt the thread and save
// the whole register file into guest memory. So each one
//   * writes the original prologue spills (Frame: `sd ra`, `sq s0..`) and reloads them at the return;
//   * keeps in every register the original writes -- $at, $v0, $v1, $a0..$a3, $t0..$t3, $s0..$s7, $f0..$f3, $f12,
//     ACC -- the value the original has there at each call, each check point and the return (S(...) where the original
//     assigns it; a register the original leaves alone keeps what the caller or the last callee left);
//   * calls through the callee's generated entry point with $ra = the original link (jal), the indirect calls with
//     $v0 = the target and $ra = the `jalr` link (jalr_to), and runs the floating-point steps through the runtime's
//     EE FPU operations on the guest registers, in the compiled order (EE single precision, ACC, FCR31 flags);
//   * returns its result in $v0 through the shim; the void functions leave $v0 as their last step left it.
// gp-relative globals are read the way the original reads them, through the guest $gp.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 34 of the 46 functions here are p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: faults only 28, callee frames 5, frame/spills 1);
// the others are the hand-written versions the register discipline above describes. The 34 were made readable on
// 2026-10-22 (slice read_misc): the work records by ui3.h's names (kCamp*, kRoot*, kKani*, kHud*) plus the HUD
// position controller's (pos::), the globals as gp_off of their addresses, the jump / pose tables, pads, flags and
// float literals by name, named registers, block roles, and no goto left (the two camp state machines leave through
// a host `running` flag for their shared "0, keep running" block; the HUD's holiday chain uses `school` / `in`).
// Every guest statement, frame, link, cycle charge and check point is the generated body's, in its order on every
// path.
#include "p3fes/game/ui3.h"

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"

#include <utility>
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/misc_view.h"

namespace p3fes::recomp_gen {
// Callees (still recompiled, or replaced by this and other slices: always through their generated entry points).
void fn_kwlnTaskGetState_00195290(p3fes::EEContext&);        // (task) -> 0..3 (kwln_task)
void fn_datGetFlag_0016f190(p3fes::EEContext&);              // (id) (menu_ui)
void fn_datSetFlag_0016f1f0(p3fes::EEContext&);              // (id, on) (ui2)
void fn_sub_17D800_0017d800(p3fes::EEContext&);              // scenario mode: 1 = The Answer (ui2)
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);              // system sound (0, 0, 0, kind): the cursor SFX
void fn_sub_119F10_00119f10(p3fes::EEContext&);              // H_Camp_CreateCampSprSetupFileTask (task, 1)
void fn_sub_16C860_0016c860(p3fes::EEContext&);              // datGetPersonaId (1)
void fn_sub_11B2B0_0011b2b0(p3fes::EEContext&);              // H_Camp_CreatePersonaTexControlTask (task, persona)
void fn_sub_11F1B0_0011f1b0(p3fes::EEContext&);              // H_Camp_CreateFlashControlTask (task)
void fn_sub_122660_00122660(p3fes::EEContext&);              // H_Camp_CreatePcKaniControlTask (task)
void fn_datPersonaGetByPcId_00174800(p3fes::EEContext&);     // (1) (battle_data)
void fn_sub_123000_00123000(p3fes::EEContext&);              // H_Camp_CreatePersonaKaniControlTask (task, persona)
void fn_sub_11BA50_0011ba50(p3fes::EEContext&);              // this file
void fn_H_Camp_CreateRootDrawTask_0011bad0(p3fes::EEContext&);  // (task, flash, reopened)
void fn_H_Camp_GetRootSelection_0011b9a0(p3fes::EEContext&); // (root task) (ui2)
void fn_sub_11B9B0_0011b9b0(p3fes::EEContext&);              // this file
void fn_sub_11BA00_0011ba00(p3fes::EEContext&);              // this file
void fn_sub_11E380_0011e380(p3fes::EEContext&);              // flash control: start (flash, on)
void fn_sub_11E370_0011e370(p3fes::EEContext&);              // this file
void fn_sub_121DE0_00121de0(p3fes::EEContext&);              // this file
void fn_sub_122710_00122710(p3fes::EEContext&);              // this file
void fn_sub_130F20_00130f20(p3fes::EEContext&);              // H_Camp_CreateSoubi1DrawTask (task, prio, {x, y}, 1; $f12 z)
void fn_sub_123570_00123570(p3fes::EEContext&);              // H_Camp_CreatePcStatusRootTask (task, prio, 1)
void fn_sub_1336B0_001336b0(p3fes::EEContext&);              // H_Camp_CreateCampStatusPersonaDrawTask (task, prio, {x, y}, 1)
void fn_sub_136750_00136750(p3fes::EEContext&);              // H_Camp_CreateComuDrawTask (task, prio, {x, y})
void fn_sub_1548A0_001548a0(p3fes::EEContext&);              // H_Camp_CreateSystemMenuDrawTask (task, prio)
void fn_sub_14EE80_0014ee80(p3fes::EEContext&);              // H_Camp_CreateNewItemTask (task, prio)
void fn_sub_1617D0_001617d0(p3fes::EEContext&);              // H_Camp_CreateNewCampSkillDrawTask (task, prio)
void fn_sub_11C550_0011c550(p3fes::EEContext&);              // list: slide-in step (work; $f12)
void fn_sub_11CC80_0011cc80(p3fes::EEContext&);              // list: fade-in step
void fn_sub_11C880_0011c880(p3fes::EEContext&);              // list: slide-in draw
void fn_sub_11CFB0_0011cfb0(p3fes::EEContext&);              // list: confirm flash
void fn_sub_11D3A0_0011d3a0(p3fes::EEContext&);              // list: close fade start
void fn_sub_11D6D0_0011d6d0(p3fes::EEContext&);              // list: close fade draw
void fn_sub_11DDB0_0011ddb0(p3fes::EEContext&);              // list: hide draw
void fn_sub_11DFE0_0011dfe0(p3fes::EEContext&);              // list: the idle draw (cursor highlight)
void fn_sub_124370_00124370(p3fes::EEContext&);              // portrait pose draws
void fn_sub_124B30_00124b30(p3fes::EEContext&);
void fn_sub_125740_00125740(p3fes::EEContext&);
void fn_sub_125B40_00125b40(p3fes::EEContext&);
void fn_sub_129B30_00129b30(p3fes::EEContext&);              // status panel draws
void fn_sub_12A560_0012a560(p3fes::EEContext&);
void fn_sub_12AC60_0012ac60(p3fes::EEContext&);
void fn_sub_12B300_0012b300(p3fes::EEContext&);
void fn_sub_137580_00137580(p3fes::EEContext&);              // social-link panel draws
void fn_sub_1380E0_001380e0(p3fes::EEContext&);
void fn_sub_1387B0_001387b0(p3fes::EEContext&);
void fn_sub_139FC0_00139fc0(p3fes::EEContext&);              // social-link card draws
void fn_sub_13AFD0_0013afd0(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

using namespace ui3;
namespace rg = p3fes::recomp_gen;

// --- named immediates of the register-level (p3fes_handgen) bodies ----------------------------------------------
// ui3.h names the work records (kCamp*, kRoot*, kKani*, kHud*) and the globals; these are the rest, from the
// instructions that use them.
inline constexpr s32 kTaskWork = 60;        // KwlnTask: the work area (task.h kOffWork)
inline constexpr s32 kScreenPrio = 6334;    // the task priority every camp screen is created with
inline constexpr s32 kFlashUp = 16;         // the flash-control work: non-zero once the flash animation is up
inline constexpr s32 kHighlightY = 800;     // the list highlight record: its y (float)
inline constexpr u32 kItemTable = 0x5D80E4u;      // sub_13BCB0: u32[rows][10]
inline constexpr u32 kStrMoonSpr = 0x5E4190u;     // "camp/i_moon_00.spr"
inline constexpr u32 kClndMoonPhase = 0x5E38D0u;  // tbl_clndMoonPhase: one byte per day, 0x0E = full moon
inline constexpr u32 kRwRenderStateGet = 0x960094u;  // the RW engine's render-state get / set function pointers
inline constexpr u32 kRwRenderStateSet = 0x960090u;
inline constexpr s32 kRsState14 = 14;       // the render state the HUD saves, clears and restores
inline constexpr s32 kGpStrNo = -27696;     // $gp offset of "NO\n" (the hidden HUD's printf)
// The kani (side portrait) inner tables: the pose by the current screen, for the new screen named.
inline constexpr u32 kPcKaniFor1 = 0x7B5810u, kPcKaniFor2 = 0x7B57D0u, kPcKaniFor3 = 0x7B5790u,
                     kPcKaniFor4 = 0x7B5750u, kPcKaniFor9 = 0x7B5710u, kPcKaniFor13 = 0x7B56D0u;
inline constexpr u32 kPersonaKaniFor1 = 0x7B5A10u, kPersonaKaniFor2 = 0x7B59D0u, kPersonaKaniFor3 = 0x7B5990u,
                     kPersonaKaniFor4 = 0x7B5950u, kPersonaKaniFor9 = 0x7B5920u, kPersonaKaniFor13 = 0x7B58F0u;
// "H_DayPartsPos" (the HUD's slide-away controller) work
namespace pos {
inline constexpr s32 kFrames = 4;   // s32: frames left of the slide (10 per slide)
inline constexpr s32 kX = 8;        // f32: the x offset now (copied to gp-19704 every frame)
inline constexpr s32 kTarget = 16;  // f32: 400 away, 0 back
inline constexpr s32 kStart = 24;   // f32: the x offset the slide started from
inline constexpr s32 kAway = 32;    // u32: 1 while slid away
}  // namespace pos

// --- registers ---------------------------------------------------------------------------------------------------
constexpr unsigned kV0 = 2, kV1 = 3, kA0 = 4, kA1 = 5, kA2 = 6, kA3 = 7, kT0 = 8, kT1 = 9, kT2 = 10, kT3 = 11, kS0 = 16, kGP = 28;

u64 R(const EEContext& ctx, unsigned r) { return ee::core::gpr64(ctx, r); }
void S(EEContext& ctx, unsigned r, u64 v) { ee::core::set_gpr64(ctx, r, v); }
u64 sx(u32 v) { return ee::core::sext32(v); }
u32 a32(u64 v) { return static_cast<u32>(v); }

template <typename T> T ld(const EEContext& ctx, u64 va) { return guest::load<T>(ctx, a32(va)); }
template <typename T> void st(EEContext& ctx, u64 va, T v) { guest::store<T>(ctx, a32(va), v); }
// `lw rX, off(base)`: the word sign-extended, as the register holds it.
u64 lw(const EEContext& ctx, u64 base, s32 off) { return sx(ld<u32>(ctx, a32(base) + static_cast<u32>(off))); }
void sw(EEContext& ctx, u64 value, u64 base, s32 off) { st<u32>(ctx, a32(base) + static_cast<u32>(off), a32(value)); }
// `addiu rd, rs, imm` / `addu`: the 32-bit sum sign-extended.
u64 add32(u64 a, u64 b) { return sx(a32(a) + a32(b)); }
u64 addr(u64 base, s32 off) { return sx(a32(base) + static_cast<u32>(off)); }
// `sll rd, rt, sa`: the low word shifted, sign-extended.
u64 sll(u64 v, unsigned sa) { return sx(a32(v) << sa); }

// The gp-relative word at `off` (`lw rX, off(gp)` / `sw rX, off(gp)`).
u64 gpw(const EEContext& ctx, s32 off) { return lw(ctx, R(ctx, kGP), off); }
void set_gpw(EEContext& ctx, s32 off, u64 v) { sw(ctx, v, R(ctx, kGP), off); }

// `jal fn` with $ra = the original link (the value the generated body hands rt::jal); returns $v0.
u64 jal(EEContext& ctx, u32 link, guest::Fn fn) {
    rt::jal(ctx, link);
    fn(ctx);
    return R(ctx, kV0);
}

// The prologue `addiu sp, sp, -size; sd ra, ra_off(sp); sq s<n-1>..s0` (s_i at ra_off - 16 * (n - i)) and, on
// destruction, its epilogue (the reloads from the guest stack, `addiu sp, sp, size`).
class Frame {
public:
    Frame(EEContext& ctx, u32 size, u32 ra_off, unsigned nsaved) noexcept
        : ctx_(ctx), size_(size), ra_off_(ra_off), n_(nsaved) {
        rt::addiu(ctx_, GPR_SP, GPR_SP, -static_cast<s32>(size_));
        rt::sd(ctx_, GPR_RA, GPR_SP, static_cast<s32>(ra_off_));
        for (unsigned i = n_; i-- > 0;) rt::sq(ctx_, kS0 + i, GPR_SP, slot(i));
    }
    ~Frame() {
        rt::ld(ctx_, GPR_RA, GPR_SP, static_cast<s32>(ra_off_));
        for (unsigned i = n_; i-- > 0;) rt::lq(ctx_, kS0 + i, GPR_SP, slot(i));
        rt::addiu(ctx_, GPR_SP, GPR_SP, static_cast<s32>(size_));
    }
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;
    u64 at(u32 off) const noexcept { return addr(R(ctx_, GPR_SP), static_cast<s32>(off)); }  // `addiu rX, sp, off`

private:
    s32 slot(unsigned i) const noexcept { return static_cast<s32>(ra_off_ - 16u * (n_ - i)); }
    EEContext& ctx_;
    u32 size_, ra_off_;
    unsigned n_;
};

// The "wait for the poll task" COMM shape of sub_1681D0 / sub_169420 / sub_1885F0 / sub_188BE0:
//   addiu sp, -16; sd ra, 0(sp); lw a0, off(gp); jal kwlnTaskGetState; li v1, 3;
//   v0 == 3 ? (sw zero, off(gp); v0 = 1) : v0 = 0.
u64 poll_task_finished(EEContext& ctx, s32 gp_off, u32 link) {
    guest::enter(ctx, 8);
    Frame f(ctx, 16, 0, 0);
    S(ctx, kA0, gpw(ctx, gp_off));
    const u64 state = jal(ctx, link, &rg::fn_kwlnTaskGetState_00195290);
    S(ctx, kV1, 3);
    if (state == 3) {
        guest::charge(ctx, 4);
        set_gpw(ctx, gp_off, 0);
        S(ctx, kV0, 1);
    } else {
        guest::charge(ctx, 1);
        S(ctx, kV0, 0);
    }
    guest::charge(ctx, 4);
    return R(ctx, kV0);
}

}  // namespace

// =====================================================================================================================
// h_camp.c: the slot table and the camp root
// =====================================================================================================================

// 0x119A20 [H_Camp_ClearSlotTable]: zero the 14 words at 0x833B70 (kwlnInitMain at boot, the event menu sub_3C9FE0).
void sub_119A20(EEContext& ctx) {
    guest::enter(ctx, 5);
    S(ctx, kA1, 0);
    S(ctx, kA0, kCampSlotTable);
    for (;;) {
        guest::charge(ctx, 3);
        const bool more = static_cast<s64>(R(ctx, kA1)) < static_cast<s64>(kCampSlotCount);
        S(ctx, kV1, more ? 1 : 0);
        if (!more) break;
        guest::backedge(ctx);
        guest::charge(ctx, 4);
        S(ctx, kV1, add32(R(ctx, kA0), sll(R(ctx, kA1), 2)));
        sw(ctx, 0, R(ctx, kV1), 0);
        S(ctx, kA1, add32(R(ctx, kA1), 1));
    }
    guest::charge(ctx, 2);
}

// 0x00119A60 sub_119A60 -- 28 bytes; leaf frame (no stack)
// 0x119A60 [H_Camp_GetSlot](index): 0x833B70[index] (no bound check).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_119A60(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::lw, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00119a60
    enter(ctx, 7);  // entry check point + this block's cycles
    v1 = sll(a0, 2);
    mview::la(v0, kCampSlotTable);
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
}

// 0x00119A80 sub_119A80 -- 28 bytes; leaf frame (no stack)
// 0x119A80 [H_Camp_SetSlot](index, value): 0x833B70[index] = value.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_119A80(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::sll, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00119a80
    enter(ctx, 7);  // entry check point + this block's cycles
    a0 = sll(a0, 2);
    mview::la(v1, kCampSlotTable);
    v1 = addu(v1, a0);
    sw(a1, v1, 0);
}

// 0x0011A050 H_Camp_UpdateDrawTask -- 1720 bytes; frame 0x40: ra sp+0x20, s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x11A050 H_Camp_UpdateDrawTask(task): the camp menu root, 21 states (jump table 0x7B5420; 7 and 8 are empty). Returns
// 0 to keep running, -1 when the menu is over (the list closed, or leaving the Item screen with flag 0x1417 set).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void H_Camp_UpdateDrawTask(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::mtc1,
          hg::sd, hg::si, hg::sll, hg::sltiu, hg::sq, hg::sw, hg::tail;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, camp{ctx, 16}, task{ctx, 17}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0011a050
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(ra, sp, 0x20);
    sq(task, sp, 0x10);
    sq(camp, sp, 0x0);
    task = a0;
    lw(camp, a0, kTaskWork);
    lw(v0, camp, kCampState);
    at = sltiu(v0, 21);
    bool running = false;  // leave through the "0, keep running" block
    if (at != 0) {
        // 0x0011a078
        charge(ctx, 7);
        mview::la(v1, kCampJumpTable);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x11A094u:  // table[0]
            // 0x0011a094
            charge(ctx, 3);
            lw(v0, gp, mview::gp_off(kCampSetupTask));
            if (v0 != 0) {
                // 0x0011a0ac
                charge(ctx, 5);
                lw(v0, v0, 60);
                lw(v1, v0, 0);
                v0 = 3;
                if (v1 != v0) {
                    // 0x0011a0cc
                    charge(ctx, 1);
                    v1 = 0;
                } else {
                    // 0x0011a0c0
                    charge(ctx, 3);
                    v1 = 1;
                }
            } else {
                // 0x0011a0a0
                charge(ctx, 3);
                v1 = si(-1);
            }
            // 0x0011a0d0
            charge(ctx, 3);
            v0 = si(-1);
            if (v1 == v0) {
                // 0x0011a0dc
                charge(ctx, 4);
                a0 = task;
                a1 = 1;
                jal(ctx, 0x11A0E4u, gen::fn_sub_119F10_00119f10);
            }
            // 0x0011a0ec
            charge(ctx, 31);
            a0 = 1;
            jal(ctx, 0x11A0F0u, gen::fn_sub_16C860_0016c860);
            a0 = task;
            a1 = v0;
            jal(ctx, 0x11A100u, gen::fn_sub_11B2B0_0011b2b0);
            a0 = task;
            jal(ctx, 0x11A10Cu, gen::fn_sub_11F1B0_0011f1b0);
            sw(v0, camp, kCampFlash);
            a0 = task;
            jal(ctx, 0x11A11Cu, gen::fn_sub_122660_00122660);
            sw(v0, gp, mview::gp_off(kCampPcKani));
            a0 = 1;
            jal(ctx, 0x11A12Cu, gen::fn_datPersonaGetByPcId_00174800);
            a0 = task;
            a1 = v0;
            jal(ctx, 0x11A13Cu, gen::fn_sub_123000_00123000);
            sw(v0, gp, mview::gp_off(kCampPersonaKani));
            lw(v0, camp, kCampFlash);
            sw(v0, gp, mview::gp_off(kCampFlashTask));
            sw(zero, gp, mview::gp_off(kCampCursor));
            sw(zero, camp, kCampReopen);
            v0 = 1;
            sw(v0, camp, kCampState);
            running = true;
            break;
        case 0x11A168u:  // table[1]
            // 0x0011a168
            charge(ctx, 3);
            lw(v0, gp, mview::gp_off(kCampSetupTask));
            if (v0 != 0) {
                // 0x0011a180
                charge(ctx, 5);
                lw(v0, v0, 60);
                lw(v1, v0, 0);
                v0 = 3;
                if (v1 != v0) {
                    // 0x0011a1a0
                    charge(ctx, 1);
                    v0 = 0;
                } else {
                    // 0x0011a194
                    charge(ctx, 3);
                    v0 = 1;
                }
            } else {
                // 0x0011a174
                charge(ctx, 3);
                v0 = si(-1);
            }
            // 0x0011a1a4
            charge(ctx, 3);
            a1 = 1;
            if (v0 == a1) {
                // 0x0011a1b0
                charge(ctx, 7);
                a0 = kHudFlagCampOpen;
                jal(ctx, 0x11A1B4u, gen::fn_datSetFlag_0016f1f0);
                v0 = 2;
                sw(v0, camp, kCampState);
            }
            running = true;
            break;
        case 0x11A1CCu:  // table[2]
            // 0x0011a1cc
            charge(ctx, 3);
            lw(v0, gp, mview::gp_off(kCampRootTask));
            if (v0 == 0) {
                // 0x0011a1ec
                charge(ctx, 5);
                lw(a1, camp, kCampFlash);
                lw(a2, camp, kCampReopen);
                jal(ctx, 0x11A1F4u, gen::fn_H_Camp_CreateRootDrawTask_0011bad0);
                sw(v0, gp, mview::gp_off(kCampRootTask));
            } else {
                // 0x0011a1d8
                charge(ctx, 5);
                a0 = v0;
                jal(ctx, 0x11A1DCu, gen::fn_sub_11BA50_0011ba50);
            }
            // 0x0011a200
            charge(ctx, 6);
            v0 = 1;
            sw(v0, camp, kCampReopen);
            v0 = 3;
            sw(v0, camp, kCampState);
            running = true;
            break;
        case 0x11A218u:  // table[3]
            // 0x0011a218
            charge(ctx, 6);
            lw(a0, gp, mview::gp_off(kCampRootTask));
            jal(ctx, 0x11A21Cu, gen::fn_H_Camp_GetRootSelection_0011b9a0);
            v1 = 6;
            if (v0 == v1) {
                // 0x0011a3d8
                charge(ctx, 8);
                sw(v1, gp, mview::gp_off(kCampCursor));
                lw(a0, gp, mview::gp_off(kCampRootTask));
                jal(ctx, 0x11A3E0u, gen::fn_sub_11BA00_0011ba00);
                v0 = 15;
                sw(v0, camp, kCampState);
            } else {
                // 0x0011a230
                charge(ctx, 3);
                v1 = 5;
                if (v0 == v1) {
                    // 0x0011a398
                    charge(ctx, 16);
                    sw(v1, gp, mview::gp_off(kCampCursor));
                    lw(a0, gp, mview::gp_off(kCampRootTask));
                    jal(ctx, 0x11A3A0u, gen::fn_sub_11BA00_0011ba00);
                    lw(a0, gp, mview::gp_off(kCampPcKani));
                    a1 = 7;
                    jal(ctx, 0x11A3B0u, gen::fn_sub_121DE0_00121de0);
                    lw(a0, gp, mview::gp_off(kCampPersonaKani));
                    a1 = 7;
                    jal(ctx, 0x11A3C0u, gen::fn_sub_122710_00122710);
                    v0 = 13;
                    sw(v0, camp, kCampState);
                } else {
                    // 0x0011a23c
                    charge(ctx, 3);
                    a1 = 4;
                    if (v0 == a1) {
                        // 0x0011a384
                        charge(ctx, 5);
                        sw(a1, gp, mview::gp_off(kCampCursor));
                        v0 = 9;
                        sw(v0, camp, kCampState);
                    } else {
                        // 0x0011a248
                        charge(ctx, 3);
                        v1 = 3;
                        if (v0 == v1) {
                            // 0x0011a344
                            charge(ctx, 16);
                            sw(v1, gp, mview::gp_off(kCampCursor));
                            lw(a0, gp, mview::gp_off(kCampPcKani));
                            a1 = 15;
                            jal(ctx, 0x11A350u, gen::fn_sub_121DE0_00121de0);
                            lw(a0, gp, mview::gp_off(kCampPersonaKani));
                            a1 = 15;
                            jal(ctx, 0x11A360u, gen::fn_sub_122710_00122710);
                            lw(a0, gp, mview::gp_off(kCampRootTask));
                            jal(ctx, 0x11A36Cu, gen::fn_sub_11BA00_0011ba00);
                            v0 = 5;
                            sw(v0, camp, kCampState);
                        } else {
                            // 0x0011a254
                            charge(ctx, 3);
                            v1 = 2;
                            if (v0 == v1) {
                                // 0x0011a308
                                charge(ctx, 15);
                                sw(v1, gp, mview::gp_off(kCampCursor));
                                lw(a0, gp, mview::gp_off(kCampPcKani));
                                jal(ctx, 0x11A310u, gen::fn_sub_121DE0_00121de0);
                                lw(a0, gp, mview::gp_off(kCampPersonaKani));
                                a1 = 4;
                                jal(ctx, 0x11A320u, gen::fn_sub_122710_00122710);
                                lw(a0, gp, mview::gp_off(kCampRootTask));
                                jal(ctx, 0x11A32Cu, gen::fn_sub_11BA00_0011ba00);
                                v0 = 11;
                                sw(v0, camp, kCampState);
                            } else {
                                // 0x0011a260
                                charge(ctx, 3);
                                v1 = 1;
                                if (v0 == v1) {
                                    // 0x0011a2f4
                                    charge(ctx, 5);
                                    sw(v1, gp, mview::gp_off(kCampCursor));
                                    v0 = 17;
                                    sw(v0, camp, kCampState);
                                } else {
                                    // 0x0011a26c
                                    charge(ctx, 2);
                                    if (v0 == 0) {
                                        // 0x0011a2e0
                                        charge(ctx, 5);
                                        sw(zero, gp, mview::gp_off(kCampCursor));
                                        v0 = 19;
                                        sw(v0, camp, kCampState);
                                    } else {
                                        // 0x0011a274
                                        charge(ctx, 3);
                                        v1 = si(-1);
                                        if (v0 != v1) {
                                            // 0x0011a280
                                            charge(ctx, 3);
                                            v1 = si(-2);
                                            if (v0 == v1) {
                                                // 0x0011a294
                                                charge(ctx, 19);
                                                lw(a0, gp, mview::gp_off(kCampRootTask));
                                                jal(ctx, 0x11A298u, gen::fn_sub_11B9B0_0011b9b0);
                                                lw(a0, camp, kCampFlash);
                                                a1 = 0;
                                                jal(ctx, 0x11A2A8u, gen::fn_sub_11E380_0011e380);
                                                lw(a0, gp, mview::gp_off(kCampPcKani));
                                                a1 = 0;
                                                jal(ctx, 0x11A2B8u, gen::fn_sub_121DE0_00121de0);
                                                lw(a0, gp, mview::gp_off(kCampPersonaKani));
                                                a1 = 0;
                                                jal(ctx, 0x11A2C8u, gen::fn_sub_122710_00122710);
                                                v0 = 4;
                                                sw(v0, camp, kCampState);
                                            } else {
                                                // 0x0011a28c
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
            running = true;
            break;
        case 0x11A3F8u:  // table[4]
            // 0x0011a3f8
            charge(ctx, 3);
            lw(v0, gp, mview::gp_off(kCampRootTask));
            if (v0 != 0) {
                running = true;
                break;
            }
            // 0x0011a404
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x11A410u:  // table[5]
            // 0x0011a410
            charge(ctx, 14);
            v0 = mview::flt(50.0f);
            sw(v0, sp, 0x38);
            sw(v0, sp, 0x3C);
            mtc1(zero, f12);
            a1 = kScreenPrio;
            ld(a2, sp, 0x38);
            a3 = 1;
            jal(ctx, 0x11A42Cu, gen::fn_sub_130F20_00130f20);
            sw(v0, camp, kCampEquipTask);
            v0 = 6;
            sw(v0, camp, kCampState);
            running = true;
            break;
        case 0x11A448u:  // table[6]
            // 0x0011a448
            charge(ctx, 6);
            lw(a0, camp, kCampEquipTask);
            jal(ctx, 0x11A44Cu, gen::fn_kwlnTaskGetState_00195290);
            v1 = 3;
            if (v0 == v1) {
                // 0x0011a460
                charge(ctx, 5);
                sw(zero, camp, kCampEquipTask);
                v0 = 2;
                sw(v0, camp, kCampState);
            }
            running = true;
            break;
        case 0x11A474u:  // table[9]
            // 0x0011a474
            charge(ctx, 9);
            a1 = kScreenPrio;
            a2 = 1;
            jal(ctx, 0x11A47Cu, gen::fn_sub_123570_00123570);
            sw(v0, camp, kCampEquipTask);
            v0 = 10;
            sw(v0, camp, kCampState);
            running = true;
            break;
        case 0x11A498u:  // table[10]
            // 0x0011a498
            charge(ctx, 6);
            lw(a0, camp, kCampEquipTask);
            jal(ctx, 0x11A49Cu, gen::fn_kwlnTaskGetState_00195290);
            v1 = 3;
            if (v0 == v1) {
                // 0x0011a4b0
                charge(ctx, 5);
                sw(zero, camp, kCampEquipTask);
                v0 = 2;
                sw(v0, camp, kCampState);
            }
            running = true;
            break;
        case 0x11A4C4u:  // table[11]
            // 0x0011a4c4
            charge(ctx, 13);
            v0 = mview::flt(50.0f);
            sw(v0, sp, 0x38);
            sw(v0, sp, 0x3C);
            a1 = kScreenPrio;
            ld(a2, sp, 0x38);
            a3 = 1;
            jal(ctx, 0x11A4DCu, gen::fn_sub_1336B0_001336b0);
            sw(v0, camp, kCampScreenTask);
            v0 = 12;
            sw(v0, camp, kCampState);
            running = true;
            break;
        case 0x11A4F8u:  // table[12]
            // 0x0011a4f8
            charge(ctx, 6);
            lw(a0, camp, kCampScreenTask);
            jal(ctx, 0x11A4FCu, gen::fn_kwlnTaskGetState_00195290);
            v1 = 3;
            if (v0 == v1) {
                // 0x0011a510
                charge(ctx, 7);
                sw(zero, camp, kCampScreenTask);
                v0 = 1;
                sw(v0, camp, kCampReturned);
                v0 = 2;
                sw(v0, camp, kCampState);
            }
            running = true;
            break;
        case 0x11A52Cu:  // table[13]
            // 0x0011a52c
            charge(ctx, 21);
            lw(a0, gp, mview::gp_off(kCampPcKani));
            a1 = 7;
            jal(ctx, 0x11A534u, gen::fn_sub_121DE0_00121de0);
            lw(a0, gp, mview::gp_off(kCampPersonaKani));
            a1 = 7;
            jal(ctx, 0x11A544u, gen::fn_sub_122710_00122710);
            v0 = mview::flt(50.0f);
            sw(v0, sp, 0x38);
            sw(v0, sp, 0x3C);
            a0 = task;
            a1 = kScreenPrio;
            ld(a2, sp, 0x38);
            jal(ctx, 0x11A564u, gen::fn_sub_136750_00136750);
            sw(v0, camp, kCampScreenTask);
            v0 = 14;
            sw(v0, camp, kCampState);
            running = true;
            break;
        case 0x11A580u:  // table[14]
            // 0x0011a580
            charge(ctx, 6);
            lw(a0, camp, kCampScreenTask);
            jal(ctx, 0x11A584u, gen::fn_kwlnTaskGetState_00195290);
            v1 = 3;
            if (v0 == v1) {
                // 0x0011a598
                charge(ctx, 7);
                sw(zero, camp, kCampScreenTask);
                v0 = 1;
                sw(v0, camp, kCampReturned);
                v0 = 2;
                sw(v0, camp, kCampState);
            }
            running = true;
            break;
        case 0x11A5B4u:  // table[15]
            // 0x0011a5b4
            charge(ctx, 17);
            lw(a0, gp, mview::gp_off(kCampPcKani));
            a1 = 6;
            jal(ctx, 0x11A5BCu, gen::fn_sub_121DE0_00121de0);
            lw(a0, gp, mview::gp_off(kCampPersonaKani));
            a1 = 6;
            jal(ctx, 0x11A5CCu, gen::fn_sub_122710_00122710);
            a0 = task;
            a1 = kScreenPrio;
            jal(ctx, 0x11A5DCu, gen::fn_sub_1548A0_001548a0);
            sw(v0, camp, kCampScreenTask);
            v0 = 16;
            sw(v0, camp, kCampState);
            running = true;
            break;
        case 0x11A5F8u:  // table[16]
            // 0x0011a5f8
            charge(ctx, 6);
            lw(a0, camp, kCampScreenTask);
            jal(ctx, 0x11A5FCu, gen::fn_kwlnTaskGetState_00195290);
            v1 = 3;
            if (v0 == v1) {
                // 0x0011a610
                charge(ctx, 7);
                sw(zero, camp, kCampScreenTask);
                v0 = 1;
                sw(v0, camp, kCampReturned);
                v0 = 2;
                sw(v0, camp, kCampState);
            }
            running = true;
            break;
        case 0x11A62Cu:  // table[17]
            // 0x0011a62c
            charge(ctx, 8);
            a1 = kScreenPrio;
            jal(ctx, 0x11A630u, gen::fn_sub_14EE80_0014ee80);
            sw(v0, camp, kCampScreenTask);
            v0 = 18;
            sw(v0, camp, kCampState);
            running = true;
            break;
        case 0x11A64Cu:  // table[18]
            // 0x0011a64c
            charge(ctx, 6);
            lw(a0, camp, kCampScreenTask);
            jal(ctx, 0x11A650u, gen::fn_kwlnTaskGetState_00195290);
            v1 = 3;
            if (v0 != v1) {
                running = true;
                break;
            }
            // 0x0011a664
            charge(ctx, 5);
            a0 = kFlagLeaveAfterItem;
            jal(ctx, 0x11A668u, gen::fn_datGetFlag_0016f190);
            if (v0 == 0) {
                // 0x0011a684
                charge(ctx, 7);
                sw(zero, camp, kCampScreenTask);
                v0 = 1;
                sw(v0, camp, kCampReturned);
                v0 = 2;
                sw(v0, camp, kCampState);
                running = true;
                break;
            }
            // 0x0011a678
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x11A6A0u:  // table[19]
            // 0x0011a6a0
            charge(ctx, 8);
            a1 = kScreenPrio;
            jal(ctx, 0x11A6A4u, gen::fn_sub_1617D0_001617d0);
            sw(v0, camp, kCampScreenTask);
            v0 = 20;
            sw(v0, camp, kCampState);
            running = true;
            break;
        case 0x11A6C0u:  // table[20]
            // 0x0011a6c0
            charge(ctx, 6);
            lw(a0, camp, kCampScreenTask);
            jal(ctx, 0x11A6C4u, gen::fn_kwlnTaskGetState_00195290);
            v1 = 3;
            if (v0 == v1) {
                // 0x0011a6d8
                charge(ctx, 5);
                sw(zero, camp, kCampScreenTask);
                v0 = 1;
                sw(v0, camp, kCampReturned);
                v0 = 2;
                sw(v0, camp, kCampState);
            }
            running = true;
            break;
        case 0x11A6ECu:  // table[7, 8]
            running = true;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    } else {
        running = true;  // a state outside the table: 0
    }
    if (running) {
        // 0x0011a6ec: 0, keep running
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x0011a6f0
    charge(ctx, 6);
    ld(ra, sp, 0x20);
    lq(task, sp, 0x10);
    lq(camp, sp, 0x0);
    sp = addiu(sp, 0x40);
}

// 0x0011B420 H_Camp_UpdateRootDrawTask -- 1404 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x11B420 H_Camp_UpdateRootDrawTask(task): the main list, 11 states (jump table 0x7B5480; 1 is empty). Returns 0, or
// -1 when a close animation has finished.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void H_Camp_UpdateRootDrawTask(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::adda_s, hg::addiu, hg::addu, hg::charge, hg::cvt_s_w, hg::enter, hg::i64, hg::jal,
          hg::ld, hg::lhu, hg::lq, hg::lw, hg::lwc1, hg::madd_s, hg::mtc1, hg::sd, hg::si, hg::sll, hg::slti,
          hg::sltiu, hg::sltu, hg::sq, hg::sw, hg::swc1, hg::tail;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, root{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2}, f3{ctx, 3}, f12{ctx, 12};
    // 0x0011b420
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(root, sp, 0x0);
    lw(root, a0, kTaskWork);
    lw(v0, root, kRootState);
    at = sltiu(v0, 11);
    bool running = false;  // leave through the "0, keep running" block
    if (at != 0) {
        // 0x0011b440
        charge(ctx, 7);
        mview::la(v1, kRootJumpTable);
        v0 = sll(v0, 2);
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        switch (v0.u()) {
        case 0x11B45Cu:  // table[0]
            // 0x0011b45c
            charge(ctx, 6);
            lw(v0, gp, mview::gp_off(kCampCursor));
            sw(v0, root, kRootCursor);
            v0 = 2;
            sw(v0, root, kRootState);
            running = true;
            break;
        case 0x11B474u:  // table[2]
            // 0x0011b474
            charge(ctx, 10);
            lw(a0, root, kRootFlash);
            a1 = 1;
            jal(ctx, 0x11B47Cu, gen::fn_sub_11E380_0011e380);
            v0 = 200;
            sw(v0, root, kRootOpenTimer);
            v0 = 3;
            sw(v0, root, kRootState);
            running = true;
            break;
        case 0x11B49Cu:  // table[3]
            // 0x0011b49c
            charge(ctx, 5);
            lw(a0, root, kRootFlash);
            jal(ctx, 0x11B4A0u, gen::fn_sub_11E370_0011e370);
            if (v0 != 0) {
                // 0x0011b4b0
                charge(ctx, 5);
                sw(zero, root, kRootFrames);
                lw(v1, root, kRootOpenMode);
                v0 = 1;
                if (v1 == v0) {
                    // 0x0011b4f8
                    charge(ctx, 7);
                    v0 = mview::flt(100.0f);
                    mtc1(v0, f12);
                    a0 = root;
                    jal(ctx, 0x11B504u, gen::fn_sub_11CC80_0011cc80);
                    v0 = 5;
                    sw(v0, root, kRootState);
                } else {
                    // 0x0011b4c4
                    charge(ctx, 2);
                    if (v1 == 0) {
                        // 0x0011b4d4
                        charge(ctx, 9);
                        v0 = mview::flt(100.0f);
                        mtc1(v0, f12);
                        a0 = root;
                        jal(ctx, 0x11B4E0u, gen::fn_sub_11C550_0011c550);
                        v0 = 4;
                        sw(v0, root, kRootState);
                    } else {
                        // 0x0011b4cc
                        charge(ctx, 2);
                    }
                }
                // 0x0011b514
                charge(ctx, 10);
                lw(a0, gp, mview::gp_off(kCampPcKani));
                a1 = 1;
                jal(ctx, 0x11B51Cu, gen::fn_sub_121DE0_00121de0);
                lw(a0, gp, mview::gp_off(kCampPersonaKani));
                a1 = 1;
                jal(ctx, 0x11B52Cu, gen::fn_sub_122710_00122710);
            }
            running = true;
            break;
        case 0x11B53Cu:  // table[4]
            // 0x0011b53c
            charge(ctx, 6);
            lw(v0, root, kRootFrames);
            v1 = addiu(v0, 1);
            sw(v1, root, kRootFrames);
            v0 = 21;
            if (v1 == v0) {
                // 0x0011b554
                charge(ctx, 2);
                v0 = 6;
                sw(v0, root, kRootState);
            }
            // 0x0011b55c
            charge(ctx, 7);
            v0 = mview::flt(100.0f);
            mtc1(v0, f12);
            a0 = root;
            jal(ctx, 0x11B568u, gen::fn_sub_11C880_0011c880);
            running = true;
            break;
        case 0x11B578u:  // table[5]
            // 0x0011b578
            charge(ctx, 6);
            lw(v0, root, kRootFrames);
            v1 = addiu(v0, 1);
            sw(v1, root, kRootFrames);
            v0 = 10;
            if (v1 == v0) {
                // 0x0011b590
                charge(ctx, 2);
                v0 = 6;
                sw(v0, root, kRootState);
            }
            // 0x0011b598
            charge(ctx, 7);
            v0 = mview::flt(110.0f);
            mtc1(v0, f12);
            a0 = root;
            jal(ctx, 0x11B5A4u, gen::fn_sub_11CFB0_0011cfb0);
            running = true;
            break;
        case 0x11B5B4u:  // table[7]
            // 0x0011b5b4
            charge(ctx, 5);
            lw(v0, root, kRootFrames);
            v0 = addiu(v0, -1);
            sw(v0, root, kRootFrames);
            if (v0 != 0) {
                // 0x0011b5c8
                charge(ctx, 7);
                v0 = mview::flt(100.0f);
                mtc1(v0, f12);
                a0 = root;
                jal(ctx, 0x11B5D4u, gen::fn_sub_11D6D0_0011d6d0);
                running = true;
                break;
            }
            // 0x0011b5e4
            charge(ctx, 3);
            v0 = si(-1);
            break;
        case 0x11B5F0u:  // table[8]
            // 0x0011b5f0
            charge(ctx, 5);
            lw(v0, root, kRootFrames);
            v0 = addiu(v0, -4);
            sw(v0, root, kRootFrames);
            if (i64(v0) > 0) {
                // 0x0011b604
                charge(ctx, 7);
                v0 = mview::flt(100.0f);
                mtc1(v0, f12);
                a0 = root;
                jal(ctx, 0x11B610u, gen::fn_sub_11D6D0_0011d6d0);
                running = true;
                break;
            }
            // 0x0011b620
            charge(ctx, 4);
            sw(zero, root, kRootFrames);
            v0 = si(-1);
            break;
        case 0x11B630u:  // table[9]
            // 0x0011b630
            charge(ctx, 6);
            lw(v0, root, kRootFrames);
            v0 = addiu(v0, 1);
            sw(v0, root, kRootFrames);
            at = slti(v0, 14);
            if (at != 0) {
                // 0x0011b648
                charge(ctx, 7);
                v0 = mview::flt(100.0f);
                mtc1(v0, f12);
                a0 = root;
                jal(ctx, 0x11B654u, gen::fn_sub_11DDB0_0011ddb0);
                running = true;
                break;
            }
            // 0x0011b664
            charge(ctx, 4);
            sw(zero, root, kRootFrames);
            v0 = si(-1);
            break;
        case 0x11B674u:  // table[6]
            // 0x0011b674
            charge(ctx, 5);
            v0 = mview::hi(kPadButtons);
            lhu(v1, v0, mview::lo(kPadButtons));
            v0 = v1 & 0x20;
            if (v0 == 0) {
                // 0x0011b6b8
                charge(ctx, 3);
                v0 = v1 & 0x40;
                if (v0 == 0) {
                    // 0x0011b6f4
                    charge(ctx, 3);
                    lw(v0, root, kRootInput);
                    if (v0 != 0) {
                        // 0x0011b700
                        charge(ctx, 6);
                        a0 = 1;
                        v0 = mview::hi(kPadButtons);
                        lhu(v1, v0, mview::lo(kPadPressed));
                        v0 = v1 & 0x4000;
                        if (v0 == 0) {
                            // 0x0011b718
                            charge(ctx, 5);
                            v0 = mview::hi(kPadButtons);
                            lhu(v0, v0, mview::lo(kPadRepeat));
                            v0 = v0 & 0x4000;
                            if (v0 == 0) {
                                // 0x0011b72c
                                charge(ctx, 1);
                                a0 = 0;
                            }
                        }
                        // 0x0011b730
                        charge(ctx, 2);
                        if (a0 == 0) {
                            // 0x0011b81c
                            charge(ctx, 4);
                            v0 = v1 & 0x1000;
                            v0 = sltu(0, v0);
                            if (v0 == 0) {
                                // 0x0011b82c
                                charge(ctx, 4);
                                v0 = mview::hi(kPadButtons);
                                lhu(v0, v0, mview::lo(kPadRepeat));
                                v0 = v0 & 0x1000;
                                v0 = sltu(0, v0);
                            }
                            // 0x0011b83c
                            charge(ctx, 2);
                            if (v0 != 0) {
                                // 0x0011b844
                                charge(ctx, 3);
                                lw(v0, root, kRootCursor);
                                if (v0 == 0) {
                                    // 0x0011b8b8
                                    charge(ctx, 6);
                                    v0 = mview::hi(kPadButtons);
                                    lhu(v0, v0, mview::lo(kPadHeld));
                                    v0 = v0 & 0x1000;
                                    v0 = sltu(0, v0);
                                    if (v0 == 0) {
                                        // 0x0011b8d0
                                        charge(ctx, 4);
                                        v0 = mview::hi(kPadButtons);
                                        lhu(v0, v0, mview::lo(kPadRepeatHeld));
                                        v0 = v0 & 0x1000;
                                        v0 = sltu(0, v0);
                                    }
                                    // 0x0011b8e0
                                    charge(ctx, 2);
                                    if (v0 != 0) {
                                        // 0x0011b8e8
                                        charge(ctx, 13);
                                        a0 = 0;
                                        a1 = 0;
                                        a2 = 0;
                                        a3 = 0;
                                        jal(ctx, 0x11B8F8u, gen::fn_sub_10A4E0_0010a4e0);
                                        v0 = 5;
                                        sw(v0, root, kRootMoveFlash);
                                        v0 = 6;
                                        sw(v0, root, kRootCursor);
                                        v0 = 1;
                                        sw(v0, root, kRootMoved);
                                        sw(zero, root, kRootInput);
                                    }
                                } else {
                                    // 0x0011b850
                                    charge(ctx, 18);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x11B860u, gen::fn_sub_10A4E0_0010a4e0);
                                    v0 = 5;
                                    sw(v0, root, kRootMoveFlash);
                                    v0 = 1;
                                    sw(v0, root, kRootMoved);
                                    sw(zero, root, kRootInput);
                                    lw(v0, root, kRootCursor);
                                    v0 = addiu(v0, -1);
                                    sw(v0, root, kRootCursor);
                                    jal(ctx, 0x11B888u, gen::fn_sub_17D800_0017d800);
                                    if (v0 != 0) {
                                        // 0x0011b898
                                        charge(ctx, 4);
                                        lw(v1, root, kRootCursor);
                                        v0 = 5;
                                        if (v1 == v0) {
                                            // 0x0011b8a8
                                            charge(ctx, 4);
                                            v0 = 4;
                                            sw(v0, root, kRootCursor);
                                        }
                                    }
                                }
                            }
                        } else {
                            // 0x0011b738
                            charge(ctx, 4);
                            lw(v1, root, kRootCursor);
                            v0 = 6;
                            if (v1 == v0) {
                                // 0x0011b7b0
                                charge(ctx, 6);
                                v0 = mview::hi(kPadButtons);
                                lhu(v0, v0, mview::lo(kPadHeld));
                                v0 = v0 & 0x4000;
                                v0 = sltu(0, v0);
                                if (v0 == 0) {
                                    // 0x0011b7c8
                                    charge(ctx, 4);
                                    v0 = mview::hi(kPadButtons);
                                    lhu(v0, v0, mview::lo(kPadRepeatHeld));
                                    v0 = v0 & 0x4000;
                                    v0 = sltu(0, v0);
                                }
                                // 0x0011b7d8
                                charge(ctx, 2);
                                if (v0 != 0) {
                                    // 0x0011b7e0
                                    charge(ctx, 15);
                                    a0 = 0;
                                    a1 = 0;
                                    a2 = 0;
                                    a3 = 0;
                                    jal(ctx, 0x11B7F0u, gen::fn_sub_10A4E0_0010a4e0);
                                    sw(zero, root, kRootCursor);
                                    v0 = 5;
                                    sw(v0, root, kRootMoveFlash);
                                    sw(zero, root, kRootCursor);
                                    v0 = 1;
                                    sw(v0, root, kRootMoved);
                                    sw(zero, root, kRootInput);
                                }
                            } else {
                                // 0x0011b748
                                charge(ctx, 15);
                                a0 = 0;
                                a1 = 0;
                                a2 = 0;
                                a3 = 0;
                                jal(ctx, 0x11B758u, gen::fn_sub_10A4E0_0010a4e0);
                                v0 = 5;
                                sw(v0, root, kRootMoveFlash);
                                lw(v0, root, kRootCursor);
                                v0 = addiu(v0, 1);
                                sw(v0, root, kRootCursor);
                                jal(ctx, 0x11B774u, gen::fn_sub_17D800_0017d800);
                                if (v0 != 0) {
                                    // 0x0011b784
                                    charge(ctx, 4);
                                    lw(v1, root, kRootCursor);
                                    v0 = 5;
                                    if (v1 == v0) {
                                        // 0x0011b794
                                        charge(ctx, 2);
                                        v0 = 6;
                                        sw(v0, root, kRootCursor);
                                    }
                                }
                                // 0x0011b79c
                                charge(ctx, 5);
                                v0 = 1;
                                sw(v0, root, kRootMoved);
                                sw(zero, root, kRootInput);
                            }
                        }
                        // 0x0011b91c
                        charge(ctx, 12);
                        lwc1(f0, root, kRootCursor);
                        cvt_s_w(f3, f0);
                        v0 = mview::flt(19.0f);
                        mtc1(v0, f2);
                        v0 = mview::flt(59.0f);
                        mtc1(v0, f1);
                        mtc1(zero, f0);
                        adda_s(f0, f1);
                        madd_s(f0, f2, f3);
                        lw(v0, gp, mview::gp_off(kCampHighlight));
                        swc1(f0, v0, kHighlightY);  // highlight y = 59 + 19 * cursor
                    }
                } else {
                    // 0x0011b6c4
                    charge(ctx, 12);
                    a0 = 0;
                    a1 = 0;
                    a2 = 0;
                    a3 = 1;
                    jal(ctx, 0x11B6D4u, gen::fn_sub_10A4E0_0010a4e0);
                    lw(v0, root, kRootCursor);
                    sw(v0, root, kRootSelection);
                    v0 = 10;
                    sw(v0, root, kRootState);
                }
            } else {
                // 0x0011b688
                charge(ctx, 12);
                a0 = 0;
                a1 = 0;
                a2 = 0;
                a3 = 2;
                jal(ctx, 0x11B698u, gen::fn_sub_10A4E0_0010a4e0);
                v0 = si(-2);
                sw(v0, root, kRootSelection);
                v0 = 10;
                sw(v0, root, kRootState);
            }
            // 0x0011b94c
            charge(ctx, 7);
            v0 = mview::flt(100.0f);
            mtc1(v0, f12);
            a0 = root;
            jal(ctx, 0x11B958u, gen::fn_sub_11DFE0_0011dfe0);
            running = true;
            break;
        case 0x11B968u:  // table[10]
            // 0x0011b968
            charge(ctx, 7);
            v0 = 22;
            sw(v0, root, kRootFrames);
            v0 = mview::flt(100.0f);
            mtc1(v0, f12);
            a0 = root;
            jal(ctx, 0x11B97Cu, gen::fn_sub_11CFB0_0011cfb0);
            running = true;
            break;
        case 0x11B984u:  // table[1]
            running = true;
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v0.u());
            return;
        }
    } else {
        running = true;  // a state outside the table: 0
    }
    if (running) {
        // 0x0011b984: 0, keep running
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x0011b988
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(root, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0011B9B0 sub_11B9B0 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x11B9B0 [H_Camp_RootClose](root task): the close fade (sub_11D3A0), state 7 with 22 frames.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_11B9B0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::mtc1, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, root{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0011b9b0
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(root, sp, 0x0);
    lw(root, a0, kTaskWork);
    v0 = mview::flt(100.0f);
    mtc1(v0, f12);
    a0 = root;
    jal(ctx, 0x11B9CCu, gen::fn_sub_11D3A0_0011d3a0);
    v1 = 7;
    sw(v1, root, kRootState);
    v1 = 22;
    sw(v1, root, kRootFrames);
    ld(ra, sp, 0x10);
    lq(root, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0011BA00 sub_11BA00 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x11BA00 [H_Camp_RootHide](root task): the same fade before a screen opens, state 8 (-4 per frame from 22).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_11BA00(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::mtc1, hg::sd, hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, root{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0011ba00
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(root, sp, 0x0);
    lw(root, a0, kTaskWork);
    v0 = mview::flt(100.0f);
    mtc1(v0, f12);
    a0 = root;
    jal(ctx, 0x11BA1Cu, gen::fn_sub_11D3A0_0011d3a0);
    v1 = 8;
    sw(v1, root, kRootState);
    v1 = 22;
    sw(v1, root, kRootFrames);
    ld(ra, sp, 0x10);
    lq(root, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0011BA50 sub_11BA50 -- 76 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x11BA50 [H_Camp_RootReopen](root task): fade the list back in (sub_11CC80), state 5 from frame 0, no selection (-1).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_11BA50(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::addiu, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::mtc1, hg::sd, hg::si, hg::sq,
          hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, root{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f12{ctx, 12};
    // 0x0011ba50
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(root, sp, 0x0);
    lw(root, a0, kTaskWork);
    v0 = mview::flt(100.0f);
    mtc1(v0, f12);
    a0 = root;
    jal(ctx, 0x11BA6Cu, gen::fn_sub_11CC80_0011cc80);
    v1 = 5;
    sw(v1, root, kRootState);
    sw(zero, root, kRootFrames);
    v1 = si(-1);
    sw(v1, root, kRootSelection);
    ld(ra, sp, 0x10);
    lq(root, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0011E370 sub_11E370 -- 16 bytes; leaf frame (no stack)
// 0x11E370 [H_Camp_FlashIsUp](flash task): its work +16 (non-zero once the flash animation is up).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_11E370(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0011e370
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, kTaskWork);
    lw(v0, v0, kFlashUp);
}

// =====================================================================================================================
// The side portraits ("kani"): the pose transition by (current screen +12, new screen)
// =====================================================================================================================

namespace {

// The pose / panel draw dispatchers: `addiu sp, -32; sd ra, 0(sp); sd <args>, (sp); ...; jal <by kind>; ld ra`.
// Each spills one or two argument registers into its frame first (the compiler's home slots), then picks a callee by a
// small kind argument and hands it the matching extra argument; an unknown kind calls nothing.

}  // namespace

// 0x00121DE0 sub_121DE0 -- 524 bytes; leaf frame (no stack)
// 0x121DE0 [H_Camp_PcKaniSetScreen](portrait task, screen) -> 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_121DE0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::lw, hg::sll, hg::sltiu, hg::sw, hg::tail;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00121de0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, kTaskWork);
    at = sltiu(a1, 17);
    if (at != 0) {
        // 0x00121df0
        charge(ctx, 7);
        mview::la(a0, kPcKaniOuterTable);
        v1 = sll(a1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x121E0Cu:  // table[0]
            // 0x00121e0c
            charge(ctx, 4);
            v1 = 11;
            sw(v1, v0, kKaniState);
            break;
        case 0x121E1Cu:  // table[1]
            // 0x00121e1c
            charge(ctx, 4);
            lw(v1, v0, kKaniScreen);
            at = sltiu(v1, 17);
            if (at != 0) {
                // 0x00121e2c
                charge(ctx, 7);
                mview::la(a0, kPcKaniFor1);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x121E48u:  // table[0]
                    // 0x00121e48
                    charge(ctx, 4);
                    v1 = 1;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x121E58u:  // table[3]
                    // 0x00121e58
                    charge(ctx, 4);
                    v1 = 9;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x121E68u:  // table[4, 6, 7, 8, 9, 11, 12, 13, 15, 16]
                    // 0x00121e68
                    charge(ctx, 4);
                    v1 = 9;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x121E78u:  // table[5]
                    // 0x00121e78
                    charge(ctx, 4);
                    v1 = 9;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x121FDCu:  // table[1, 2, 10, 14]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
            break;
        case 0x121E88u:  // table[2]
            // 0x00121e88
            charge(ctx, 4);
            lw(v1, v0, kKaniScreen);
            at = sltiu(v1, 14);
            if (at != 0) {
                // 0x00121e98
                charge(ctx, 7);
                mview::la(a0, kPcKaniFor2);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x121EB4u:  // table[0]
                    // 0x00121eb4
                    charge(ctx, 4);
                    v1 = 1;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x121EC4u:  // table[3]
                    // 0x00121ec4
                    charge(ctx, 4);
                    v1 = 7;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x121ED4u:  // table[4, 6, 7, 8, 9, 13]
                    // 0x00121ed4
                    charge(ctx, 4);
                    v1 = 9;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x121FDCu:  // table[1, 2, 5, 10, 11, 12]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
            break;
        case 0x121EE4u:  // table[3]
            // 0x00121ee4
            charge(ctx, 4);
            lw(v1, v0, kKaniScreen);
            at = sltiu(v1, 14);
            if (at != 0) {
                // 0x00121ef4
                charge(ctx, 7);
                mview::la(a0, kPcKaniFor3);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x121F10u:  // table[2]
                    // 0x00121f10
                    charge(ctx, 4);
                    v1 = 5;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x121FDCu:  // table[0, 1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
            break;
        case 0x121F20u:  // table[4, 5, 6, 7, 8, 15, 16]
            // 0x00121f20
            charge(ctx, 4);
            lw(v1, v0, kKaniScreen);
            at = sltiu(v1, 14);
            if (at != 0) {
                // 0x00121f30
                charge(ctx, 7);
                mview::la(a0, kPcKaniFor4);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x121F4Cu:  // table[1]
                    // 0x00121f4c
                    charge(ctx, 4);
                    v1 = 11;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x121F5Cu:  // table[2]
                    // 0x00121f5c
                    charge(ctx, 4);
                    v1 = 11;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x121FDCu:  // table[0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
            break;
        case 0x121F6Cu:  // table[9]
            // 0x00121f6c
            charge(ctx, 4);
            lw(v1, v0, kKaniScreen);
            at = sltiu(v1, 14);
            if (at != 0) {
                // 0x00121f7c
                charge(ctx, 7);
                mview::la(a0, kPcKaniFor9);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x121F98u:  // table[1]
                    // 0x00121f98
                    charge(ctx, 4);
                    v1 = 13;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x121FDCu:  // table[0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
            break;
        case 0x121FA8u:  // table[13]
            // 0x00121fa8
            charge(ctx, 4);
            lw(v1, v0, kKaniScreen);
            at = sltiu(v1, 14);
            if (at != 0) {
                // 0x00121fb8
                charge(ctx, 7);
                mview::la(a0, kPcKaniFor13);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x121FD4u:  // table[1]
                    // 0x00121fd4
                    charge(ctx, 2);
                    v1 = 13;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x121FDCu:  // table[0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
            break;
        case 0x121FDCu:  // table[10, 11, 12, 14]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x00121fdc (the shared epilogue, written out on this path)
    charge(ctx, 4);
    sw(a1, v0, kKaniScreen);
    v0 = 1;
}

// 0x00122710 sub_122710 -- 556 bytes; leaf frame (no stack)
// 0x122710 [H_Camp_PersonaKaniSetScreen](portrait task, screen) -> 1.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_122710(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::lw, hg::sll, hg::sltiu, hg::sw, hg::tail;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00122710
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, kTaskWork);
    at = sltiu(a1, 17);
    if (at != 0) {
        // 0x00122720
        charge(ctx, 7);
        mview::la(a0, kPersonaKaniOuterTable);
        v1 = sll(a1, 2);
        v1 = addu(v1, a0);
        lw(v1, v1, 0);
        switch (v1.u()) {
        case 0x12273Cu:  // table[0]
            // 0x0012273c
            charge(ctx, 4);
            v1 = 5;
            sw(v1, v0, kKaniState);
            break;
        case 0x12274Cu:  // table[1]
            // 0x0012274c
            charge(ctx, 4);
            lw(v1, v0, kKaniScreen);
            at = sltiu(v1, 17);
            if (at != 0) {
                // 0x0012275c
                charge(ctx, 7);
                mview::la(a0, kPersonaKaniFor1);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x122778u:  // table[0]
                    // 0x00122778
                    charge(ctx, 4);
                    v1 = 1;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x122788u:  // table[2]
                    // 0x00122788
                    charge(ctx, 4);
                    v1 = 3;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x122798u:  // table[3]
                    // 0x00122798
                    charge(ctx, 4);
                    v1 = 13;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x1227A8u:  // table[4, 5, 6, 7, 8, 9, 11, 12, 13, 15, 16]
                    // 0x001227a8
                    charge(ctx, 4);
                    v1 = 3;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x12292Cu:  // table[1, 10, 14]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
            break;
        case 0x1227B8u:  // table[2]
            // 0x001227b8
            charge(ctx, 4);
            lw(v1, v0, kKaniScreen);
            at = sltiu(v1, 14);
            if (at != 0) {
                // 0x001227c8
                charge(ctx, 7);
                mview::la(a0, kPersonaKaniFor2);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x1227E4u:  // table[1]
                    // 0x001227e4
                    charge(ctx, 4);
                    v1 = 5;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x1227F4u:  // table[3]
                    // 0x001227f4
                    charge(ctx, 4);
                    v1 = 11;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x122804u:  // table[4, 5, 6, 7, 8, 9, 13]
                    // 0x00122804
                    charge(ctx, 4);
                    v1 = 3;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x12292Cu:  // table[0, 2, 10, 11, 12]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
            break;
        case 0x122814u:  // table[3]
            // 0x00122814
            charge(ctx, 4);
            lw(v1, v0, kKaniScreen);
            at = sltiu(v1, 14);
            if (at != 0) {
                // 0x00122824
                charge(ctx, 7);
                mview::la(a0, kPersonaKaniFor3);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x122840u:  // table[2]
                    // 0x00122840
                    charge(ctx, 4);
                    v1 = 9;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x122850u:  // table[4, 6, 7, 8, 9, 13]
                    // 0x00122850
                    charge(ctx, 4);
                    v1 = 3;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x12292Cu:  // table[0, 1, 3, 5, 10, 11, 12]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
            break;
        case 0x122860u:  // table[4, 5, 6]
            // 0x00122860
            charge(ctx, 4);
            lw(v1, v0, kKaniScreen);
            at = sltiu(v1, 14);
            if (at != 0) {
                // 0x00122870
                charge(ctx, 7);
                mview::la(a0, kPersonaKaniFor4);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x12288Cu:  // table[1]
                    // 0x0012288c
                    charge(ctx, 4);
                    v1 = 5;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x12289Cu:  // table[2]
                    // 0x0012289c
                    charge(ctx, 4);
                    v1 = 5;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x1228ACu:  // table[3]
                    // 0x001228ac
                    charge(ctx, 4);
                    v1 = 5;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x12292Cu:  // table[0, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
            break;
        case 0x1228BCu:  // table[7, 8, 9, 15, 16]
            // 0x001228bc
            charge(ctx, 4);
            lw(v1, v0, kKaniScreen);
            at = sltiu(v1, 9);
            if (at != 0) {
                // 0x001228cc
                charge(ctx, 7);
                mview::la(a0, kPersonaKaniFor9);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x1228E8u:  // table[1]
                    // 0x001228e8
                    charge(ctx, 4);
                    v1 = 5;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x12292Cu:  // table[0, 2, 3, 4, 5, 6, 7, 8]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
            break;
        case 0x1228F8u:  // table[13]
            // 0x001228f8
            charge(ctx, 4);
            lw(v1, v0, kKaniScreen);
            at = sltiu(v1, 9);
            if (at != 0) {
                // 0x00122908
                charge(ctx, 7);
                mview::la(a0, kPersonaKaniFor13);
                v1 = sll(v1, 2);
                v1 = addu(v1, a0);
                lw(v1, v1, 0);
                switch (v1.u()) {
                case 0x122924u:  // table[1]
                    // 0x00122924
                    charge(ctx, 2);
                    v1 = 7;
                    sw(v1, v0, kKaniState);
                    break;
                case 0x12292Cu:  // table[0, 2, 3, 4, 5, 6, 7, 8]
                    break;
                default:  // not one of the table's targets: the dispatch table, as the recompiled body
                    tail(ctx, v1.u());
                    return;
                }
            }
            break;
        case 0x12292Cu:  // table[10, 11, 12, 14]
            break;
        default:  // not one of the table's targets: the dispatch table, as the recompiled body
            tail(ctx, v1.u());
            return;
        }
    }
    // 0x0012292c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    sw(a1, v0, kKaniScreen);
    v0 = 1;
}

// 0x123640 [H_Camp_PcKaniDrawPose]($a0, $a1, $a2, mode $a3, $t0, $t1): mode 0 -> sub_124370($a0, $a2, $t0, ...),
// mode 1 -> sub_124B30($a0, $a1, $a2, $t1, ...). $a0 / $a1 are spilled to the frame's home slots 16 / 24.
void sub_123640(EEContext& ctx) {
    guest::enter(ctx, 7);
    Frame f(ctx, 32, 0, 0);
    rt::sd(ctx, kA0, GPR_SP, 16);
    rt::sd(ctx, kA1, GPR_SP, 24);
    S(ctx, kV1, 1);
    const u64 mode = R(ctx, kA3);
    if (mode == 1) {
        guest::charge(ctx, 3);
        S(ctx, kA3, R(ctx, kT1));
        jal(ctx, 0x123688u, &rg::fn_sub_124B30_00124b30);
    } else {
        guest::charge(ctx, 2);
        if (mode == 0) {
            guest::charge(ctx, 6);
            S(ctx, kA1, R(ctx, kA2));
            S(ctx, kA2, R(ctx, kT0));
            jal(ctx, 0x123674u, &rg::fn_sub_124370_00124370);
        } else {
            guest::charge(ctx, 2);
        }
    }
    guest::charge(ctx, 4);
}

// 0x124E00 [H_Camp_PersonaKaniDrawPose]: the same shape over sub_125740 (mode 0) / sub_125B40 (mode 1).
void sub_124E00(EEContext& ctx) {
    guest::enter(ctx, 7);
    Frame f(ctx, 32, 0, 0);
    rt::sd(ctx, kA0, GPR_SP, 16);
    rt::sd(ctx, kA1, GPR_SP, 24);
    S(ctx, kV1, 1);
    const u64 mode = R(ctx, kA3);
    if (mode == 1) {
        guest::charge(ctx, 3);
        S(ctx, kA3, R(ctx, kT1));
        jal(ctx, 0x124e48u, &rg::fn_sub_125B40_00125b40);
    } else {
        guest::charge(ctx, 2);
        if (mode == 0) {
            guest::charge(ctx, 6);
            S(ctx, kA1, R(ctx, kA2));
            S(ctx, kA2, R(ctx, kT0));
            jal(ctx, 0x124e34u, &rg::fn_sub_125740_00125740);
        } else {
            guest::charge(ctx, 2);
        }
    }
    guest::charge(ctx, 4);
}

// 0x00127AB0 sub_127AB0 -- 20 bytes; leaf frame (no stack)
// sub_127AB0 [persona portrait: state 5]: work state = 5. The persona portrait task's work accessors (called by its
// update sub_1230C0).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_127AB0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00127ab0
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 5;
    lw(v1, a0, kTaskWork);
    sw(a1, v1, 0);
}

// 0x00127AD0 sub_127AD0 -- 20 bytes; leaf frame (no stack)
// sub_127AD0 [persona portrait: state 7]: work state = 7.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_127AD0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00127ad0
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 7;
    lw(v1, a0, kTaskWork);
    sw(a1, v1, 0);
}

// 0x00127AF0 sub_127AF0 -- 16 bytes; leaf frame (no stack)
// sub_127AF0 [persona portrait: work +28].
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_127AF0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00127af0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, kTaskWork);
    lw(v0, v0, 28);
}

// 0x00127FF0 sub_127FF0 -- 28 bytes; leaf frame (no stack)
// `lw a0, 60(a0); li v1, 255; sh v1, 12(a0); li v1, 3; sw v1, 0(a0)`: full alpha, state 3 (sub_127FF0 / sub_167EF0).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_127FF0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sh, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00127ff0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(a0, a0, kTaskWork);
    v1 = 255;
    sh(v1, a0, 12);
    v1 = 3;
    sw(v1, a0, 0);
}

// 0x00128010 sub_128010 -- 24 bytes; leaf frame (no stack)
// `lw a0, 60(a0); sh zero, 16(a0); li v1, 4; sw v1, 0(a0)`: restart the fade, state 4 (sub_128010 / sub_167F10).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_128010(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sh, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00128010
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kTaskWork);
    sh(zero, a0, 16);
    v1 = 4;
    sw(v1, a0, 0);
}

// 0x00128030 sub_128030 -- 16 bytes; leaf frame (no stack)
// sub_128030 [work +20] (the persona portrait task).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_128030(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00128030
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, kTaskWork);
    lw(v0, v0, 20);
}

// 0x128140 [H_Camp_StatusDrawPanel]($a0, $a1, kind $a2, $a3, $t0): kind 0 / 1 -> sub_129B30 / sub_12A560 with $a2 = $a3,
// kind 2 / 3 -> sub_12AC60 / sub_12B300 with $a2 = $t0. $a0 is spilled to the home slot 24.
void sub_128140(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 0, 0);
    rt::sd(ctx, kA0, GPR_SP, 24);
    S(ctx, kV1, 3);
    const u64 kind = R(ctx, kA2);
    if (kind == 3) {
        guest::charge(ctx, 3);
        S(ctx, kA2, R(ctx, kT0));
        jal(ctx, 0x1281c0u, &rg::fn_sub_12B300_0012b300);
    } else {
        guest::charge(ctx, 3);
        S(ctx, kV1, 2);
        if (kind == 2) {
            guest::charge(ctx, 5);
            S(ctx, kA2, R(ctx, kT0));
            jal(ctx, 0x1281acu, &rg::fn_sub_12AC60_0012ac60);
        } else {
            guest::charge(ctx, 3);
            S(ctx, kV1, 1);
            if (kind == 1) {
                guest::charge(ctx, 5);
                S(ctx, kA2, R(ctx, kA3));
                jal(ctx, 0x128198u, &rg::fn_sub_12A560_0012a560);
            } else {
                guest::charge(ctx, 2);
                if (kind == 0) {
                    guest::charge(ctx, 5);
                    S(ctx, kA2, R(ctx, kA3));
                    jal(ctx, 0x128184u, &rg::fn_sub_129B30_00129b30);
                } else {
                    guest::charge(ctx, 2);
                }
            }
        }
    }
    guest::charge(ctx, 4);
}

// =====================================================================================================================
// Persona / social-link / item screens
// =====================================================================================================================

// 0x00133B40 sub_133B40 -- 36 bytes; leaf frame (no stack)
// 0x133B40 [H_Camp_SetPersonaPage](task, value): the low byte of work +12 = value (the event menu fclMisc_UpdatePsStatusTask).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_133B40(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::si, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00133b40
    enter(ctx, 9);  // entry check point + this block's cycles
    lw(a2, a0, kTaskWork);
    lw(a0, a2, 12);
    v1 = si(-256);
    a0 = a0 & v1;
    v1 = a1 & 0xFF;
    v1 = a0 | v1;
    sw(v1, a2, 12);
}

// 0x00133B70 sub_133B70 -- 16 bytes; leaf frame (no stack)
// 0x133B70 [H_Camp_GetPersonaPage](task): work +12.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_133B70(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00133b70
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, kTaskWork);
    lw(v0, v0, 12);
}

// 0x136820 [H_Camp_ComuDrawPanel]($a0 .. $t0, kind $t1, $t2, $t3): kind 0 -> sub_137580 with $t1 = $t2, kind 1 / 2 ->
// sub_1380E0 / sub_1387B0 with $t1 = $t3. $a0 is spilled to the home slot 24.
void sub_136820(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 0, 0);
    rt::sd(ctx, kA0, GPR_SP, 24);
    S(ctx, kV1, 2);
    const u64 kind = R(ctx, kT1);
    if (kind == 2) {
        guest::charge(ctx, 3);
        S(ctx, kT1, R(ctx, kT3));
        jal(ctx, 0x136880u, &rg::fn_sub_1387B0_001387b0);
    } else {
        guest::charge(ctx, 3);
        S(ctx, kV1, 1);
        if (kind == 1) {
            guest::charge(ctx, 5);
            S(ctx, kT1, R(ctx, kT3));
            jal(ctx, 0x13686cu, &rg::fn_sub_1380E0_001380e0);
        } else {
            guest::charge(ctx, 2);
            if (kind == 0) {
                guest::charge(ctx, 5);
                S(ctx, kT1, R(ctx, kT2));
                jal(ctx, 0x136858u, &rg::fn_sub_137580_00137580);
            } else {
                guest::charge(ctx, 2);
            }
        }
    }
    guest::charge(ctx, 4);
}

// 0x138E80 [H_Camp_ComuDrawCard]($a0 .. $t1, kind $t2, $t3, stack args): kind 0 -> sub_139FC0 with $t2 = $t3 and $t3 =
// the caller's stack word 0, kind 1 -> sub_13AFD0 with $t2 = the caller's stack word 8. $a0 to the home slot 24.
void sub_138E80(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 32, 0, 0);
    rt::sd(ctx, kA0, GPR_SP, 24);
    S(ctx, kV1, 1);
    const u64 kind = R(ctx, kT2);
    if (kind == 1) {
        guest::charge(ctx, 3);
        rt::lw(ctx, kT2, GPR_SP, 40);
        jal(ctx, 0x138ec4u, &rg::fn_sub_13AFD0_0013afd0);
    } else {
        guest::charge(ctx, 2);
        if (kind == 0) {
            guest::charge(ctx, 6);
            S(ctx, kT2, R(ctx, kT3));
            rt::lw(ctx, kT3, GPR_SP, 32);
            jal(ctx, 0x138eb0u, &rg::fn_sub_139FC0_00139fc0);
        } else {
            guest::charge(ctx, 2);
        }
    }
    guest::charge(ctx, 4);
}

// 0x0013BCB0 sub_13BCB0 -- 44 bytes; leaf frame (no stack)
// 0x13BCB0 [H_Camp_ItemTableGet](row, col): the word 0x5D80E4[row * 10 + col] (sub_39F120's lookup).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_13BCB0(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::enter, hg::lw, hg::sll;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x0013bcb0
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = sll(a0, 2);
    v0 = addu(v0, a0);
    v1 = sll(v0, 3);
    mview::la(v0, kItemTable);
    v1 = addu(v0, v1);
    v0 = sll(a1, 2);
    v0 = addu(v0, v1);
    lw(v0, v0, 0);
}

// =====================================================================================================================
// Skill screen accessors and the script commands' task polls
// =====================================================================================================================

// 0x00166C00 sub_166C00 -- 44 bytes; leaf frame (no stack)
// 0x166C00 [H_Camp_SkillGetResult](task): work +12 once the state is 8 (done), else 0.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_166C00(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00166c00
    enter(ctx, 5);  // entry check point + this block's cycles
    lw(a0, a0, kTaskWork);
    lw(v1, a0, 0);
    v0 = 8;
    if (v1 != v0) {
        // 0x00166c20
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x00166c14
        charge(ctx, 3);
        lw(v0, a0, 12);
    }
    // 0x00166c24 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00166C30 sub_166C30 -- 20 bytes; leaf frame (no stack)
// The `li aN, k; lw v1, 60(a0); sw aN, 0(v1)` state setters (sub_127AB0, sub_166C30, sub_187EA0, ...).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_166C30(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00166c30
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 4;
    lw(v1, a0, kTaskWork);
    sw(a1, v1, 0);
}

// 0x00166C50 sub_166C50 -- 20 bytes; leaf frame (no stack)
// sub_166C50 [skill screen: state 6]: work state = 6.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_166C50(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00166c50
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 6;
    lw(v1, a0, kTaskWork);
    sw(a1, v1, 0);
}

// 0x00167EF0 sub_167EF0 -- 28 bytes; leaf frame (no stack)
// `lw a0, 60(a0); li v1, 255; sh v1, 12(a0); li v1, 3; sw v1, 0(a0)`: full alpha, state 3 (sub_127FF0 / sub_167EF0).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_167EF0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sh, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x00167ef0
    enter(ctx, 7);  // entry check point + this block's cycles
    lw(a0, a0, kTaskWork);
    v1 = 255;
    sh(v1, a0, 12);
    v1 = 3;
    sw(v1, a0, 0);
}

// 0x00167F10 sub_167F10 -- 24 bytes; leaf frame (no stack)
// `lw a0, 60(a0); sh zero, 16(a0); li v1, 4; sw v1, 0(a0)`: restart the fade, state 4 (sub_128010 / sub_167F10).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_167F10(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sh, hg::sw;
    Gpr zero{ctx, 0}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00167f10
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(a0, a0, kTaskWork);
    sh(zero, a0, 16);
    v1 = 4;
    sw(v1, a0, 0);
}

// 0x00167F30 sub_167F30 -- 16 bytes; leaf frame (no stack)
// sub_167F30 [work +20] (the skill screen task).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_167F30(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00167f30
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, kTaskWork);
    lw(v0, v0, 20);
}

// 0x1681D0 [COMM]: the screen task a script opened (gp-19820) finished -> forget it and return 1, else 0.
u64 sub_1681D0(EEContext& ctx) { return poll_task_finished(ctx, -19820, 0x1681dcu); }

// 0x001685B0 sub_1685B0 -- 24 bytes; leaf frame (no stack)
// 0x1685B0 [H_Camp_SkillIsIdle](task): work state == 2.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1685B0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sltiu;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001685b0
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v0, a0, kTaskWork);
    lw(v0, v0, 0);
    v0 = v0 ^ 0x2;
    v0 = sltiu(v0, 1);
}

// 0x001685D0 sub_1685D0 -- 16 bytes; leaf frame (no stack)
// sub_1685D0 [skill screen: work +8].
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1685D0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x001685d0
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, kTaskWork);
    lw(v0, v0, 8);
}

// 0x169420 [COMM]: the same poll for gp-19824.
u64 sub_169420(EEContext& ctx) { return poll_task_finished(ctx, -19824, 0x16942cu); }

// =====================================================================================================================
// The calendar's small task accessors
// =====================================================================================================================

// 0x00187EA0 sub_187EA0 -- 20 bytes; leaf frame (no stack)
// The `li aN, k; lw v1, 60(a0); sw aN, 0(v1)` state setters (sub_127AB0, sub_166C30, sub_187EA0, ...).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_187EA0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00187ea0
    enter(ctx, 5);  // entry check point + this block's cycles
    a1 = 3;
    lw(v1, a0, kTaskWork);
    sw(a1, v1, 0);
}

// 0x00188420 sub_188420 -- 24 bytes; leaf frame (no stack)
// 0x188420 [work +4 / +8 / +12 = a, b, c] (the day-change controller sub_181CC0).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_188420(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lw, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00188420
    enter(ctx, 6);  // entry check point + this block's cycles
    lw(v1, a0, kTaskWork);
    sw(a1, v1, 4);
    sw(a2, v1, 8);
    sw(a3, v1, 12);
}

// 0x188640 / 0x188660: `move v0, zero` (callbacks that never ask for anything).
u64 sub_188640(EEContext& ctx) {
    guest::enter(ctx, 3);
    S(ctx, kV0, 0);
    return 0;
}
u64 sub_188660(EEContext& ctx) {
    guest::enter(ctx, 3);
    S(ctx, kV0, 0);
    return 0;
}

// 0x1885F0 / 0x188BE0 [COMM]: the task polls for gp-19696 / gp-19692.
u64 sub_1885F0(EEContext& ctx) { return poll_task_finished(ctx, -19696, 0x1885fcu); }
u64 sub_188BE0(EEContext& ctx) { return poll_task_finished(ctx, -19692, 0x188becu); }

}  // namespace p3fes::game

namespace p3fes::recomp_gen {
void fn_sub_198590_00198590(p3fes::EEContext&);              // the current RW camera (gp-19504)
void fn_RwCameraBeginUpdate_004c9d10(p3fes::EEContext&);     // (camera): camera->+24 (tail jump)
void fn_RwCameraEndUpdate_004c9d00(p3fes::EEContext&);       // (camera): camera->+28
void fn_sprAddFile_00112370(p3fes::EEContext&);              // (path) -> sprite file handle
void fn_sprFileIsReady_00111f30(p3fes::EEContext&);          // (handle) -> state == 5
void fn_H_DayPartsDraw_DrawHud_001842c0(p3fes::EEContext&);  // (task, month, day, part, fade, frame, &extra)
void fn_printf_005225a8(p3fes::EEContext&);
void fn_sub_185880_00185880(p3fes::EEContext&);              // H_DayChgDraw_CreateTask (task, old m, old d, new m, new d)
void fn_sub_186960_00186960(p3fes::EEContext&);              // H_TimeChgDraw_CreateTask (task, old part, new part)
void fn_clndGetCurrentMonth_0017d920(p3fes::EEContext&);
void fn_clndGetCurrentDay_0017da40(p3fes::EEContext&);
void fn_datGetTime_0016ef30(p3fes::EEContext&);
void fn_clndGetDaysSinceStartFromDate_0017d8b0(p3fes::EEContext&);
void fn_sub_17DB40_0017db40(p3fes::EEContext&);              // clndIsHoliday (days) (ui2)
void fn_H_DayPartsDraw_SetDate_00184c80(p3fes::EEContext&);  // this file
void fn_sprDrawSpriteBasic_001159f0(p3fes::EEContext&);      // (list, file, sprite, flags; $f12 x, $f13 y, $f14 z)
void fn_sub_115BC0_00115bc0(p3fes::EEContext&);              // sprDrawSpriteBasic3: + r, g, b in $t0..$t2
void fn_sub_115CD0_00115cd0(p3fes::EEContext&);              // sprDrawSpriteBasic4: + r, g, b in $t0..$t2
void fn_sub_183840_00183840(p3fes::EEContext&);              // the HUD's moon / month / day digits
void fn_sub_183BE0_00183be0(p3fes::EEContext&);              // the HUD's weekday glyph
void fn_sub_183F60_00183f60(p3fes::EEContext&);              // the HUD's day-part name (alpha in $a1)
void fn_RpSkyRenderStateSet_004d7f60(p3fes::EEContext&);     // (state, value) (render_rw2)
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

// =====================================================================================================================
// The date / time HUD
// =====================================================================================================================

// 0x001832C0 H_DayPartsPos_UpdateTask -- 284 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x1832C0 H_DayPartsPos_UpdateTask(task): the HUD slide. Work: +4 frames left, +8 x (the result, also to gp-19704),
// +16 target x, +24 start x, +32 "shown". While shown, flag 0x141D or 0x1407 (camp open) starts the slide out to 400.0;
// while hidden, both clear starts the slide back to 0.0; 10 frames, x = start + (10 - left) * (target - start) / 10.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void H_DayPartsPos_UpdateTask(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::charge, hg::cvt_s_w, hg::div_s, hg::enter, hg::jal, hg::ld,
          hg::lq, hg::lw, hg::lwc1, hg::mtc1, hg::mul_s, hg::sd, hg::sq, hg::sub_s, hg::subu, hg::sw, hg::swc1;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, work{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f2{ctx, 2};
    // 0x001832c0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(work, sp, 0x0);
    lw(work, a0, kTaskWork);
    lw(v0, work, pos::kAway);
    if (v0 == 0) {
        // 0x00183328
        charge(ctx, 5);
        a0 = kHudFlagHidden;
        jal(ctx, 0x18332Cu, gen::fn_datGetFlag_0016f190);
        if (v0 == 0) {
            // 0x0018333c
            charge(ctx, 5);
            a0 = kHudFlagCampOpen;
            jal(ctx, 0x183340u, gen::fn_datGetFlag_0016f190);
            if (v0 == 0) {
                // 0x00183350: neither: slide back in to 0
                charge(ctx, 7);
                v0 = 1;
                sw(v0, work, pos::kAway);
                lwc1(f0, work, pos::kX);
                swc1(f0, work, pos::kStart);
                sw(zero, work, pos::kTarget);
                v0 = 10;
                sw(v0, work, pos::kFrames);
            }
        }
    } else {
        // 0x001832dc
        charge(ctx, 5);
        a0 = kHudFlagHidden;
        jal(ctx, 0x1832E0u, gen::fn_datGetFlag_0016f190);
        bool away = true;
        if (v0 == 0) {
            // 0x001832f0
            charge(ctx, 5);
            a0 = kHudFlagCampOpen;
            jal(ctx, 0x1832F4u, gen::fn_datGetFlag_0016f190);
            away = v0 != 0;
        }
        if (away) {
        // 0x00183304: hidden or the camp is open: slide away to 400
        charge(ctx, 9);
        sw(zero, work, pos::kAway);
        lwc1(f0, work, pos::kX);
        swc1(f0, work, pos::kStart);
        v0 = mview::flt(400.0f);
        sw(v0, work, pos::kTarget);
        v0 = 10;
        sw(v0, work, pos::kFrames);
        }
    }
    // 0x0018336c: frames-- while sliding
    charge(ctx, 3);
    lw(v0, work, pos::kFrames);
    if (v0 != 0) {
        // 0x00183378
        charge(ctx, 2);
        v0 = addiu(v0, -1);
        sw(v0, work, pos::kFrames);
    }
    // 0x00183380 (the shared epilogue, written out on this path)
    charge(ctx, 23);
    lwc1(f2, work, pos::kStart);
    lw(v1, work, pos::kFrames);
    v0 = 10;
    v0 = subu(v0, v1);
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, work, pos::kTarget);
    sub_s(f0, f0, f2);
    mul_s(f1, f1, f0);
    v0 = mview::flt(10.0f);
    mtc1(v0, f0);
    div_s(f0, f1, f0);
    add_s(f0, f2, f0);
    swc1(f0, work, pos::kX);
    swc1(f0, gp, mview::gp_off(kHudXOffset));
    v0 = 0;
    ld(ra, sp, 0x10);
    lq(work, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00183410 H_DayPartsDraw_UpdateTask -- 1068 bytes; frame 0x50: ra sp+0x30, s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x183410 H_DayPartsDraw_UpdateTask(task): the HUD draw task, 9 states (jump table 0x7B6600). Inside a camera update
// (RwCameraBeginUpdate / EndUpdate on sub_198590's camera) with render state 14 saved through RwRenderStateGet into the
// frame word 76 and set to 0, restored at the end: 0 load camp/i_moon_00.spr, 1 wait for it (-> gp-19712, fade 60),
// 2 draw (the fade counts up to 60) or print the "hidden" line, 3 nothing, 4 start the date-change strip, 5 wait for it,
// 6 draw and start the time-change animation, 7 draw while fading out (-6 per frame) until it ends, 8 fade back in
// (+20 per frame to 60, then state 2). States >= 2 do nothing while +4 (enabled) is clear. Frame counter +44 mod 360.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void H_DayPartsDraw_UpdateTask(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::div, hg::enter, hg::i64, hg::jal, hg::jalr, hg::ld, hg::lh,
          hg::lq, hg::lw, hg::mfhi, hg::sd, hg::sll, hg::slti, hg::sltiu, hg::sq, hg::sw, hg::tail;
    Gpr zero{ctx, 0}, at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, rs_set{ctx, 16}, hud{ctx, 17}, task{ctx, 18}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00183410
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(ra, sp, 0x30);
    sq(task, sp, 0x20);
    sq(hud, sp, 0x10);
    sq(rs_set, sp, 0x0);
    task = a0;
    lw(hud, a0, kTaskWork);
    jal(ctx, 0x18342Cu, gen::fn_sub_198590_00198590);
    a0 = v0;
    jal(ctx, 0x183438u, gen::fn_RwCameraBeginUpdate_004c9d10);
    if (v0 != 0) {
        // 0x00183454
        charge(ctx, 24);
        a0 = kRsState14;
        a1 = addiu(sp, 0x4C);
        v0 = mview::hi(kRwRenderStateGet);
        lw(v0, v0, mview::lo(kRwRenderStateGet));  // pfn_RwRenderStateGet
        jalr(ctx, 0x183464u, v0.u());
        mview::la(rs_set, kRwRenderStateSet);  // &pfn_RwRenderStateSet
        a0 = kRsState14;
        a1 = 0;
        lw(v0, rs_set, 0);  // pfn_RwRenderStateSet
        jalr(ctx, 0x183480u, v0.u());
        lw(v0, hud, kHudFrame);
        v1 = addiu(v0, 1);
        sw(v1, hud, kHudFrame);
        v0 = 360;
        div(v1, v0);
        mfhi(v0);
        sw(v0, hud, kHudFrame);
        lw(a0, hud, kHudState);
        v0 = slti(a0, 2);
        if (v0 == 0) {
            // 0x001834b4
            charge(ctx, 3);
            lw(v0, hud, kHudEnabled);
            if (v0 == 0) {
            // 0x001834c0: disabled: restore the render state, end the camera update, 0
            charge(ctx, 13);
            a0 = kRsState14;
            lw(a1, sp, 0x4C);
            lw(v0, rs_set, 0);
            jalr(ctx, 0x1834CCu, v0.u());
            jal(ctx, 0x1834D4u, gen::fn_sub_198590_00198590);
            a0 = v0;
            jal(ctx, 0x1834E0u, gen::fn_RwCameraEndUpdate_004c9d00);
            v0 = 0;
            // 0x00183820 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(ra, sp, 0x30);
            lq(task, sp, 0x20);
            lq(hud, sp, 0x10);
            lq(rs_set, sp, 0x0);
            sp = addiu(sp, 0x50);
            return;
            }
        }
        // 0x001834f4: the state machine
        charge(ctx, 3);
        at = sltiu(a0, 9);
        if (at != 0) {
            // 0x00183500
            charge(ctx, 7);
            mview::la(v1, kHudJumpTable);
            v0 = sll(a0, 2);
            v0 = addu(v0, v1);
            lw(v0, v0, 0);
            switch (v0.u()) {
            case 0x18351Cu:  // table[0]
                // 0x0018351c
                charge(ctx, 9);
                mview::la(a0, kStrMoonSpr);  // "camp/i_moon_00.spr"
                jal(ctx, 0x183524u, gen::fn_sprAddFile_00112370);
                sw(v0, hud, kHudSprFile);
                v0 = 1;
                sw(v0, hud, kHudState);
                break;
            case 0x183540u:  // table[1]
                // 0x00183540
                charge(ctx, 6);
                lw(a0, hud, kHudSprFile);
                jal(ctx, 0x183544u, gen::fn_sprFileIsReady_00111f30);
                v1 = 1;
                if (v0 == v1) {
                    // 0x00183558
                    charge(ctx, 8);
                    lw(v0, hud, kHudSprFile);
                    sw(v0, gp, mview::gp_off(kHudMoonFile));
                    v0 = 60;
                    sw(v0, hud, kHudFade);
                    v0 = 2;
                    sw(v0, hud, kHudState);
                }
                break;
            case 0x183578u:  // table[2]
                // 0x00183578
                charge(ctx, 7);
                a0 = kHudFlagDrawing;
                a1 = 0;
                jal(ctx, 0x183580u, gen::fn_datSetFlag_0016f1f0);
                lw(v0, hud, kHudVisible);
                if (v0 == 0) {
                    // 0x001835d8
                    charge(ctx, 5);
                    a0 = addiu(gp, kGpStrNo);  // "NO\n"
                    jal(ctx, 0x1835DCu, gen::fn_printf_005225a8);
                } else {
                    // 0x00183594
                    charge(ctx, 4);
                    lw(v0, hud, kHudFade);
                    at = slti(v0, 60);
                    if (at != 0) {
                        // 0x001835a4
                        charge(ctx, 2);
                        v0 = addiu(v0, 1);
                        sw(v0, hud, kHudFade);
                    }
                    // 0x001835ac
                    charge(ctx, 11);
                    a0 = task;
                    lw(a1, hud, kHudMonth);
                    lw(a2, hud, kHudDay);
                    lw(a3, hud, kHudPart);
                    lw(t0, hud, kHudFade);
                    lw(t1, hud, kHudFrame);
                    t2 = addiu(hud, kHudExtra);
                    jal(ctx, 0x1835C8u, gen::fn_H_DayPartsDraw_DrawHud_001842c0);
                }
                break;
            case 0x1835ECu:  // table[4]
                // 0x001835ec
                charge(ctx, 16);
                a0 = kHudFlagDrawing;
                a1 = 1;
                jal(ctx, 0x1835F4u, gen::fn_datSetFlag_0016f1f0);
                lh(a1, hud, kHudMonth);
                lh(a2, hud, kHudDay);
                lh(a3, hud, kHudNewMonth);
                lh(t0, hud, kHudNewDay);
                a0 = task;
                jal(ctx, 0x183610u, gen::fn_sub_185880_00185880);
                sw(v0, hud, kHudChild);
                v0 = 5;
                sw(v0, hud, kHudState);
                break;
            case 0x18362Cu:  // table[5]
                // 0x0018362c
                charge(ctx, 6);
                lw(a0, hud, kHudChild);
                jal(ctx, 0x183630u, gen::fn_kwlnTaskGetState_00195290);
                v1 = 3;
                if (v0 == v1) {
                    // 0x00183644
                    charge(ctx, 18);
                    v0 = 60;
                    sw(v0, hud, kHudFade);
                    lw(v0, hud, kHudNewMonth);
                    sw(v0, hud, kHudMonth);
                    lw(v0, hud, kHudNewDay);
                    sw(v0, hud, kHudDay);
                    lw(v0, hud, kHudNewPart);
                    sw(v0, hud, kHudPart);
                    v0 = 1;
                    sw(v0, hud, kHudVisible);
                    v0 = 2;
                    sw(v0, hud, kHudState);
                    a0 = kHudFlagChanging;
                    a1 = 0;
                    jal(ctx, 0x18367Cu, gen::fn_datSetFlag_0016f1f0);
                }
                break;
            case 0x18368Cu:  // table[6]
                // 0x0018368c
                charge(ctx, 23);
                a0 = kHudFlagDrawing;
                a1 = 1;
                jal(ctx, 0x183694u, gen::fn_datSetFlag_0016f1f0);
                a0 = task;
                lw(a1, hud, kHudMonth);
                lw(a2, hud, kHudDay);
                lw(a3, hud, kHudPart);
                lw(t0, hud, kHudFade);
                lw(t1, hud, kHudFrame);
                t2 = addiu(hud, kHudExtra);
                jal(ctx, 0x1836B8u, gen::fn_H_DayPartsDraw_DrawHud_001842c0);
                a0 = task;
                lw(a1, hud, kHudPart);
                lw(a2, hud, kHudNewPart);
                jal(ctx, 0x1836CCu, gen::fn_sub_186960_00186960);
                sw(v0, hud, kHudChild);
                v0 = 7;
                sw(v0, hud, kHudState);
                break;
            case 0x1836E8u:  // table[7]
                // 0x001836e8
                charge(ctx, 3);
                lw(v0, hud, kHudFade);
                if (v0 != 0) {
                    // 0x001836f4
                    charge(ctx, 4);
                    v0 = addiu(v0, -6);
                    sw(v0, hud, kHudFade);
                    if (i64(v0) < 0) {
                        // 0x00183704
                        charge(ctx, 1);
                        sw(zero, hud, kHudFade);
                    }
                }
                // 0x00183708
                charge(ctx, 15);
                a0 = task;
                lw(a1, hud, kHudMonth);
                lw(a2, hud, kHudDay);
                lw(a3, hud, kHudPart);
                lw(t0, hud, kHudFade);
                lw(t1, hud, kHudFrame);
                t2 = addiu(hud, kHudExtra);
                jal(ctx, 0x183724u, gen::fn_H_DayPartsDraw_DrawHud_001842c0);
                lw(a0, hud, kHudChild);
                jal(ctx, 0x183730u, gen::fn_kwlnTaskGetState_00195290);
                v1 = 3;
                if (v0 == v1) {
                    // 0x00183744
                    charge(ctx, 13);
                    sw(zero, hud, kHudFade);
                    lw(v0, hud, kHudNewMonth);
                    sw(v0, hud, kHudMonth);
                    lw(v0, hud, kHudNewDay);
                    sw(v0, hud, kHudDay);
                    lw(v0, hud, kHudNewPart);
                    sw(v0, hud, kHudPart);
                    v0 = 1;
                    sw(v0, hud, kHudVisible);
                    v0 = 8;
                    sw(v0, hud, kHudState);
                }
                break;
            case 0x183778u:  // table[8]
                // 0x00183778
                charge(ctx, 3);
                lw(v0, hud, kHudVisible);
                if (v0 != 0) {
                    // 0x00183784
                    charge(ctx, 4);
                    lw(v0, hud, kHudFade);
                    at = slti(v0, 60);
                    if (at == 0) {
                        // 0x001837b8
                        charge(ctx, 6);
                        a0 = kHudFlagChanging;
                        a1 = 0;
                        jal(ctx, 0x1837C0u, gen::fn_datSetFlag_0016f1f0);
                        v0 = 2;
                        sw(v0, hud, kHudState);
                    } else {
                        // 0x00183794
                        charge(ctx, 5);
                        v0 = addiu(v0, 20);
                        sw(v0, hud, kHudFade);
                        at = slti(v0, 61);
                        if (at == 0) {
                            // 0x001837a8
                            charge(ctx, 4);
                            v0 = 60;
                            sw(v0, hud, kHudFade);
                        }
                    }
                    // 0x001837d0
                    charge(ctx, 9);
                    a0 = task;
                    lw(a1, hud, kHudMonth);
                    lw(a2, hud, kHudDay);
                    lw(a3, hud, kHudPart);
                    lw(t0, hud, kHudFade);
                    lw(t1, hud, kHudFrame);
                    t2 = addiu(hud, kHudExtra);
                    jal(ctx, 0x1837ECu, gen::fn_H_DayPartsDraw_DrawHud_001842c0);
                }
                break;
            case 0x1837F4u:  // table[3]
                break;
            default:  // not one of the table's targets: the dispatch table, as the recompiled body
                tail(ctx, v0.u());
                return;
            }
        }
        // 0x001837f4
        charge(ctx, 11);
        a0 = kRsState14;
        lw(a1, sp, 0x4C);
        lw(v0, rs_set, 0);
        jalr(ctx, 0x183800u, v0.u());
        jal(ctx, 0x183808u, gen::fn_sub_198590_00198590);
        a0 = v0;
        jal(ctx, 0x183814u, gen::fn_RwCameraEndUpdate_004c9d00);
        v0 = 0;
    } else {
        // 0x00183448
        charge(ctx, 3);
        v0 = 0;
    }
    // 0x00183820 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(ra, sp, 0x30);
    lq(task, sp, 0x20);
    lq(hud, sp, 0x10);
    lq(rs_set, sp, 0x0);
    sp = addiu(sp, 0x50);
}

// 0x001842C0 H_DayPartsDraw_DrawHud -- 1476 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x1842C0 H_DayPartsDraw_DrawHud(task, month, day, part, fade, frame, &extra): one frame of the date / time HUD, every x
// plus the slide offset gp-19704. The panel (sprite 0x3A at 514, 23), the day-part band (0x39 at 390, -8; tinted
// (0x7C, 0xFF, 0x90) in the Dark Hour, part 8, else (0x4C, 0x9A, 0xFF)), the moon / date digits (sub_183840), the weekday
// (sub_183BE0), the day-part name with alpha (60 - fade) * 255 / 60 (sub_183F60); then, unless flag 0x1420, the moon
// countdown: the first i < 100 with tbl_clndMoonPhase[days + i] == 0x0E (full moon); when i != 0, the "Next" label
// (sprite 0x4C) and i as one or two digit sprites (0x23 + digit, tinted like the band) with additive blending. The
// sprites are drawn with the caller's $s5 as the list argument (never set here: sprDrawSpriteBasic ignores it); when no
// full moon is found the caller's $s1 is the count, as in the original.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void H_DayPartsDraw_DrawHud(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Fpr, hg::Gpr, hg::add_s, hg::addiu, hg::addu, hg::backedge, hg::charge, hg::cvt_s_w, hg::div,
          hg::enter, hg::jal, hg::jalr, hg::lbu, hg::ld, hg::lq, hg::lui, hg::lw, hg::lwc1, hg::mfhi, hg::mflo,
          hg::mtc1, hg::sd, hg::sll, hg::slti, hg::sq, hg::subu;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, hud{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, day{ctx, 19}, month{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    Fpr f0{ctx, 0}, f1{ctx, 1}, f12{ctx, 12}, f13{ctx, 13}, f14{ctx, 14};
    // 0x001842c0
    enter(ctx, 35);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x80);
    sq(s7, sp, 0x70);
    sq(s6, sp, 0x60);
    sq(s5, sp, 0x50);
    sq(month, sp, 0x40);
    sq(day, sp, 0x30);
    sq(s2, sp, 0x20);
    sq(s1, sp, 0x10);
    sq(hud, sp, 0x0);
    month = a1;
    day = a2;
    s2 = a3;
    s6 = t0;
    s7 = t2;
    lw(hud, a0, kTaskWork);
    v0 = 514;
    mtc1(v0, f0);
    cvt_s_w(f1, f0);
    lwc1(f0, gp, mview::gp_off(kHudXOffset));
    add_s(f12, f1, f0);
    v0 = mview::flt(23.0f);
    mtc1(v0, f13);
    v0 = mview::flt(50.0f);
    mtc1(v0, f14);
    a0 = s5;
    lw(a1, hud, kHudSprFile);
    a2 = 58;
    a3 = 0;
    jal(ctx, 0x184338u, gen::fn_sprDrawSpriteBasic_001159f0);
    v0 = 8;
    if (s2 != v0) {
        // 0x00184398
        charge(ctx, 17);
        v0 = mview::flt(390.0f);
        mtc1(v0, f1);
        lwc1(f0, gp, mview::gp_off(kHudXOffset));
        add_s(f12, f1, f0);
        v0 = lui(0xC100);
        mtc1(v0, f13);
        v0 = mview::flt(50.0f);
        mtc1(v0, f14);
        a0 = s5;
        lw(a1, hud, kHudSprFile);
        a2 = 57;
        a3 = 0;
        t0 = 76;
        t1 = 154;
        t2 = 255;
        jal(ctx, 0x1843D4u, gen::fn_sub_115BC0_00115bc0);
    } else {
        // 0x0018434c
        charge(ctx, 19);
        v0 = mview::flt(390.0f);
        mtc1(v0, f1);
        lwc1(f0, gp, mview::gp_off(kHudXOffset));
        add_s(f12, f1, f0);
        v0 = lui(0xC100);
        mtc1(v0, f13);
        v0 = mview::flt(50.0f);
        mtc1(v0, f14);
        a0 = s5;
        lw(a1, hud, kHudSprFile);
        a2 = 57;
        a3 = 0;
        t0 = 124;
        t1 = 255;
        t2 = 144;
        jal(ctx, 0x184388u, gen::fn_sub_115BC0_00115bc0);
    }
    // 0x001843dc
    charge(ctx, 36);
    mtc1(zero, f13);
    lw(a0, hud, kHudSprFile);
    lwc1(f12, gp, mview::gp_off(kHudXOffset));
    a1 = 0;
    a2 = month;
    a3 = day;
    t0 = s7;
    jal(ctx, 0x1843F8u, gen::fn_sub_183840_00183840);
    mtc1(zero, f13);
    lw(a0, hud, kHudSprFile);
    lwc1(f12, gp, mview::gp_off(kHudXOffset));
    a1 = 0;
    a2 = month;
    a3 = day;
    jal(ctx, 0x184418u, gen::fn_sub_183BE0_00183be0);
    mtc1(zero, f13);
    a0 = 60;
    v1 = subu(a0, s6);
    v0 = sll(v1, 8);
    v0 = subu(v0, v1);
    div(v0, a0);
    mflo(a1);
    lw(a0, hud, kHudSprFile);
    lwc1(f12, gp, mview::gp_off(kHudXOffset));
    a2 = month;
    a3 = day;
    t0 = s2;
    jal(ctx, 0x184450u, gen::fn_sub_183F60_00183f60);
    a0 = 5152;
    jal(ctx, 0x18445Cu, gen::fn_datGetFlag_0016f190);
    if (v0 == 0) {
        // 0x0018446c
        charge(ctx, 3);
        v0 = 8;
        if (s2 == v0) {
            // 0x0018448c
            charge(ctx, 3);
            s2 = 124;
            s6 = 255;
            s7 = 144;
        } else {
            // 0x00184478
            charge(ctx, 5);
            s2 = 74;
            s6 = 154;
            s7 = 255;
        }
        // 0x00184498
        charge(ctx, 11);
        a0 = month;
        a1 = day;
        jal(ctx, 0x1844A0u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
        a2 = 0;
        mview::la(v1, kClndMoonPhase);  // &tbl_clndMoonPhase
        a1 = addu(v1, v0);
        a0 = 14;
        for (;;) {
            // 0x001844e4
            charge(ctx, 3);
            v1 = slti(a2, 100);
            if (v1 == 0) {
                break;
            }
            backedge(ctx);
            // 0x001844c4
            charge(ctx, 4);
            v1 = addu(a1, a2);
            lbu(v1, v1, 0);
            if (v1 == a0) {
                // 0x001844d4: the next full moon is i days away
                charge(ctx, 3);
                s1 = a2;
                break;
            }
            // 0x001844e0
            charge(ctx, 1);
            a2 = addiu(a2, 1);
        }
        // 0x001844f0: i != 0 -> the "Next" label and the count
        charge(ctx, 2);
        if (s1 != 0) {
            // 0x001844f8
            charge(ctx, 3);
            v0 = slti(s1, 10);
            if (v0 != 0) {
                // 0x001846dc
                charge(ctx, 94);
                v0 = 514;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, gp, mview::gp_off(kHudXOffset));
                add_s(f12, f1, f0);
                v0 = mview::flt(66.0f);
                mtc1(v0, f13);
                v0 = mview::flt(50.0f);
                mtc1(v0, f14);
                a0 = s5;
                lw(a1, hud, kHudSprFile);
                a2 = 76;
                a3 = 0;
                jal(ctx, 0x184714u, gen::fn_sprDrawSpriteBasic_001159f0);
                mview::la(day, kRwRenderStateSet);  // &pfn_RwRenderStateSet
                a0 = 6;
                a1 = 1;
                lw(v0, day, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x184730u, v0.u());
                a0 = 7;
                a1 = 2;
                lw(v0, day, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x184744u, v0.u());
                a0 = 8;
                a1 = 1;
                lw(v0, day, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x184758u, v0.u());
                a0 = 9;
                a1 = 2;
                lw(v0, day, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x18476Cu, v0.u());
                a0 = 12;
                a1 = 1;
                lw(v0, day, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x184780u, v0.u());
                a0 = 11;
                a1 = 6;
                lw(v0, day, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x184794u, v0.u());
                a0 = 10;
                a1 = 5;
                lw(v0, day, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x1847A8u, v0.u());
                a0 = 2;
                a1 = 4;
                lw(v0, day, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x1847BCu, v0.u());
                a0 = 14;
                a1 = 0;
                lw(v0, day, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x1847D0u, v0.u());
                a0 = 2;
                a1 = 72;
                jal(ctx, 0x1847E0u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x1801;
                jal(ctx, 0x1847F4u, gen::fn_RpSkyRenderStateSet_004d7f60);
                v0 = 10;
                div(s1, v0);
                mfhi(v0);
                a2 = addiu(v0, 35);
                v0 = 571;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, gp, mview::gp_off(kHudXOffset));
                add_s(f12, f1, f0);
                v0 = mview::flt(67.0f);
                mtc1(v0, f13);
                t0 = s2 & 0xFF;
                t1 = s6 & 0xFF;
                t2 = s7 & 0xFF;
                v0 = mview::flt(50.0f);
                mtc1(v0, f14);
                a0 = s5;
                lw(a1, hud, kHudSprFile);
                a3 = 0;
                jal(ctx, 0x18484Cu, gen::fn_sub_115CD0_00115cd0);
            } else {
                // 0x00184504
                charge(ctx, 118);
                v0 = 497;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, gp, mview::gp_off(kHudXOffset));
                add_s(f12, f1, f0);
                v0 = mview::flt(66.0f);
                mtc1(v0, f13);
                v0 = mview::flt(50.0f);
                mtc1(v0, f14);
                a0 = s5;
                lw(a1, hud, kHudSprFile);
                a2 = 76;
                a3 = 0;
                jal(ctx, 0x18453Cu, gen::fn_sprDrawSpriteBasic_001159f0);
                mview::la(day, kRwRenderStateSet);  // &pfn_RwRenderStateSet
                a0 = 6;
                a1 = 1;
                lw(v0, day, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x184558u, v0.u());
                a0 = 7;
                a1 = 2;
                lw(v0, day, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x18456Cu, v0.u());
                a0 = 8;
                a1 = 1;
                lw(v0, day, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x184580u, v0.u());
                a0 = 9;
                a1 = 2;
                lw(v0, day, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x184594u, v0.u());
                a0 = 12;
                a1 = 1;
                lw(v0, day, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x1845A8u, v0.u());
                a0 = 11;
                a1 = 6;
                lw(v0, day, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x1845BCu, v0.u());
                a0 = 10;
                a1 = 5;
                lw(v0, day, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x1845D0u, v0.u());
                a0 = 2;
                a1 = 4;
                lw(v0, day, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x1845E4u, v0.u());
                a0 = 14;
                a1 = 0;
                lw(v0, day, 0);  // pfn_RwRenderStateSet
                jalr(ctx, 0x1845F8u, v0.u());
                a0 = 2;
                a1 = 72;
                jal(ctx, 0x184608u, gen::fn_RpSkyRenderStateSet_004d7f60);
                a0 = 3;
                v0 = 0x70000;
                a1 = v0 | 0x1801;
                jal(ctx, 0x18461Cu, gen::fn_RpSkyRenderStateSet_004d7f60);
                v0 = 10;
                div(s1, v0);
                mflo(v0);
                a2 = addiu(v0, 35);
                v0 = 554;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, gp, mview::gp_off(kHudXOffset));
                add_s(f12, f1, f0);
                v0 = mview::flt(67.0f);
                mtc1(v0, f13);
                t0 = s2 & 0xFF;
                t1 = s6 & 0xFF;
                t2 = s7 & 0xFF;
                v0 = mview::flt(50.0f);
                mtc1(v0, f14);
                a0 = s5;
                lw(a1, hud, kHudSprFile);
                a3 = 0;
                jal(ctx, 0x184674u, gen::fn_sub_115CD0_00115cd0);
                v0 = 10;
                div(s1, v0);
                mfhi(v0);
                a2 = addiu(v0, 35);
                v0 = 571;
                mtc1(v0, f0);
                cvt_s_w(f1, f0);
                lwc1(f0, gp, mview::gp_off(kHudXOffset));
                add_s(f12, f1, f0);
                v0 = mview::flt(67.0f);
                mtc1(v0, f13);
                t0 = s2 & 0xFF;
                t1 = s6 & 0xFF;
                t2 = s7 & 0xFF;
                v0 = mview::flt(50.0f);
                mtc1(v0, f14);
                a0 = s5;
                lw(a1, hud, kHudSprFile);
                a3 = 0;
                jal(ctx, 0x1846CCu, gen::fn_sub_115CD0_00115cd0);
            }
        }
    }
    // 0x00184854 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x80);
    lq(s7, sp, 0x70);
    lq(s6, sp, 0x60);
    lq(s5, sp, 0x50);
    lq(month, sp, 0x40);
    lq(day, sp, 0x30);
    lq(s2, sp, 0x20);
    lq(s1, sp, 0x10);
    lq(hud, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x001848F0 sub_1848F0 -- 912 bytes; frame 0x90: ra sp+0x80, s7 sp+0x70 (sq), s6 sp+0x60 (sq), s5 sp+0x50 (sq), s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x1848F0 [H_DayPartsDraw_ChangeDate](task, enabled): bring the HUD to the current date / day part. Disabled: just mark
// it dirty and steady. Flag 335: show the new date at once. Otherwise, a jump of 6 days or more resets the shown date
// first (H_DayPartsDraw_SetDate); on two holidays with both day parts in the school slots 2..5 only a changed date
// animates (the strip, state 4) and a changed part is taken silently; in every other case a changed date starts the
// strip (state 4, fade reset) and a changed part alone the time change (state 6), with flag 0x1410 raised; an
// unchanged date / part just shows the HUD (state 2, visible).
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void sub_1848F0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::slti, hg::sq, hg::subu, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, month{ctx, 16}, day{ctx, 17}, part{ctx, 18}, hud{ctx, 19}, days_now{ctx, 20}, enabled{ctx, 21}, days_shown{ctx, 22}, task{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x001848f0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x90);
    sd(ra, sp, 0x80);
    sq(task, sp, 0x70);
    sq(days_shown, sp, 0x60);
    sq(enabled, sp, 0x50);
    sq(days_now, sp, 0x40);
    sq(hud, sp, 0x30);
    sq(part, sp, 0x20);
    sq(day, sp, 0x10);
    sq(month, sp, 0x0);
    task = a0;
    enabled = a1;
    lw(hud, a0, kTaskWork);
    sw(enabled, hud, kHudEnabled);
    if (enabled == 0) {
        // 0x00184c30
        charge(ctx, 8);
        v0 = 1;
        sw(v0, hud, kHudDirty);
        v0 = 2;
        sw(v0, hud, kHudState);
        a0 = kHudFlagChanging;
        a1 = 0;
        jal(ctx, 0x184C48u, gen::fn_datSetFlag_0016f1f0);
    } else {
        // 0x00184930
        charge(ctx, 5);
        a0 = kFlagDateTablesHidden;
        jal(ctx, 0x184934u, gen::fn_datGetFlag_0016f190);
        if (v0 == 0) {
            // 0x00184984
            charge(ctx, 35);
            jal(ctx, 0x184984u, gen::fn_clndGetCurrentMonth_0017d920);
            month = dsll32(v0, 16);
            month = dsra32(month, 16);
            jal(ctx, 0x184994u, gen::fn_clndGetCurrentDay_0017da40);
            day = dsll32(v0, 16);
            day = dsra32(day, 16);
            jal(ctx, 0x1849A4u, gen::fn_datGetTime_0016ef30);
            v0 = v0 & 0xFF;
            part = dsll32(v0, 16);
            part = dsra32(part, 16);
            day = dsll32(day, 16);
            day = dsra32(day, 16);
            month = dsll32(month, 16);
            month = dsra32(month, 16);
            a0 = month;
            a1 = day;
            jal(ctx, 0x1849D0u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
            days_now = dsll32(v0, 16);
            days_now = dsra32(days_now, 16);
            lw(a0, hud, kHudMonth);
            lw(a1, hud, kHudDay);
            jal(ctx, 0x1849E8u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
            days_shown = dsll32(v0, 16);
            days_shown = dsra32(days_shown, 16);
            v0 = dsll32(days_now, 16);
            v0 = dsra32(v0, 16);
            v0 = subu(v0, days_shown);
            v0 = slti(v0, 6);
            if (v0 == 0) {
                // 0x00184a10
                charge(ctx, 4);
                a0 = task;
                a1 = enabled;
                jal(ctx, 0x184A18u, gen::fn_H_DayPartsDraw_SetDate_00184c80);
            }
            // 0x00184a20: both days holidays and both parts in the school slots 2..5?
            charge(ctx, 6);
            a0 = days_now;
            jal(ctx, 0x184A24u, gen::fn_sub_17DB40_0017db40);
            v1 = 1;
            bool school = false;
            if (v0 == v1) {
                // 0x00184a38
                charge(ctx, 6);
                a0 = days_shown;
                jal(ctx, 0x184A3Cu, gen::fn_sub_17DB40_0017db40);
                v1 = 1;
                if (v0 == v1) {
                    // 0x00184a50: the new part
                    charge(ctx, 5);
                    a1 = dsll32(part, 16);
                    a1 = dsra32(a1, 16);
                    v1 = 2;
                    bool in = a1 == v1;
                    if (!in) {
                        // 0x00184a64
                        charge(ctx, 3);
                        v1 = 3;
                        in = a1 == v1;
                        if (!in) {
                            // 0x00184a70
                            charge(ctx, 3);
                            v1 = 4;
                            in = a1 == v1;
                            if (!in) {
                                // 0x00184a7c
                                charge(ctx, 3);
                                v1 = 5;
                                in = a1 == v1;
                            }
                        }
                    }
                    if (in) {
                        // 0x00184a88: the shown part
                        charge(ctx, 4);
                        lw(a0, hud, kHudPart);
                        v1 = 2;
                        school = a0 == v1;
                        if (!school) {
                            // 0x00184a98
                            charge(ctx, 3);
                            v1 = 3;
                            school = a0 == v1;
                            if (!school) {
                                // 0x00184aa4
                                charge(ctx, 3);
                                v1 = 4;
                                school = a0 == v1;
                                if (!school) {
                                    // 0x00184ab0
                                    charge(ctx, 3);
                                    v1 = 5;
                                    school = a0 == v1;
                                }
                            }
                        }
                    }
                }
            }
            if (school) {
                // 0x00184abc: only a changed date animates
                charge(ctx, 3);
                lw(v1, hud, kHudMonth);
                if (v1 == month) {
                    // 0x00184ac8
                    charge(ctx, 3);
                    lw(v1, hud, kHudDay);
                    if (v1 == day) {
                        // 0x00184b18: the same date: take the part silently, show the HUD
                        charge(ctx, 13);
                        sw(month, hud, kHudMonth);
                        sw(day, hud, kHudDay);
                        sw(a1, hud, kHudPart);
                        v0 = 2;
                        sw(v0, hud, kHudState);
                        a0 = kHudFlagChanging;
                        a1 = 0;
                        jal(ctx, 0x184B34u, gen::fn_datSetFlag_0016f1f0);
                        v1 = 1;
                        sw(v1, hud, kHudVisible);
                        // 0x00184c50 (the shared epilogue, written out on this path)
                        charge(ctx, 12);
                        ld(ra, sp, 0x80);
                        lq(task, sp, 0x70);
                        lq(days_shown, sp, 0x60);
                        lq(enabled, sp, 0x50);
                        lq(days_now, sp, 0x40);
                        lq(hud, sp, 0x30);
                        lq(part, sp, 0x20);
                        lq(day, sp, 0x10);
                        lq(month, sp, 0x0);
                        sp = addiu(sp, 0x90);
                        return;
                    }
                }
                // 0x00184ad4: a changed date: the strip (state 4)
                charge(ctx, 17);
                v1 = 640;
                sw(v1, hud, kHudSlide);
                v1 = 1;
                sw(v1, hud, kHudDirty);
                lw(v1, hud, kHudMonth);
                sw(v1, hud, kHudOldMonth);
                lw(v1, hud, kHudDay);
                sw(v1, hud, kHudOldDay);
                lw(v1, hud, kHudPart);
                sw(v1, hud, kHudOldPart);
                sw(month, hud, kHudNewMonth);
                sw(day, hud, kHudNewDay);
                sw(a1, hud, kHudNewPart);
                v1 = 4;
                sw(v1, hud, kHudState);
                // 0x00184c50 (the shared epilogue, written out on this path)
                charge(ctx, 12);
                ld(ra, sp, 0x80);
                lq(task, sp, 0x70);
                lq(days_shown, sp, 0x60);
                lq(enabled, sp, 0x50);
                lq(days_now, sp, 0x40);
                lq(hud, sp, 0x30);
                lq(part, sp, 0x20);
                lq(day, sp, 0x10);
                lq(month, sp, 0x0);
                sp = addiu(sp, 0x90);
                return;
            }
            // 0x00184b4c: unchanged date and part -> show the HUD
            charge(ctx, 3);
            lw(v0, hud, kHudMonth);
            if (v0 == month) {
                // 0x00184b58
                charge(ctx, 3);
                lw(v0, hud, kHudDay);
                if (v0 == day) {
                    // 0x00184b64
                    charge(ctx, 5);
                    lw(v1, hud, kHudPart);
                    v0 = dsll32(part, 16);
                    v0 = dsra32(v0, 16);
                    if (v1 == v0) {
                        // 0x00184c08
                        charge(ctx, 10);
                        a0 = kHudFlagChanging;
                        a1 = 0;
                        jal(ctx, 0x184C10u, gen::fn_datSetFlag_0016f1f0);
                        v1 = 2;
                        sw(v1, hud, kHudState);
                        v1 = 1;
                        sw(v1, hud, kHudVisible);
                        // 0x00184c50 (the shared epilogue, written out on this path)
                        charge(ctx, 12);
                        ld(ra, sp, 0x80);
                        lq(task, sp, 0x70);
                        lq(days_shown, sp, 0x60);
                        lq(enabled, sp, 0x50);
                        lq(days_now, sp, 0x40);
                        lq(hud, sp, 0x30);
                        lq(part, sp, 0x20);
                        lq(day, sp, 0x10);
                        lq(month, sp, 0x0);
                        sp = addiu(sp, 0x90);
                        return;
                    }
                }
            }
            // 0x00184b78: a change: old = shown, new = current; a changed date -> the strip (state 4, fade reset), a
            // changed part alone -> the time change (state 6); flag 0x1410 raised
            charge(ctx, 19);
            v0 = 640;
            sw(v0, hud, kHudSlide);
            v0 = 1;
            sw(v0, hud, kHudDirty);
            lw(v0, hud, kHudMonth);
            sw(v0, hud, kHudOldMonth);
            lw(v0, hud, kHudDay);
            sw(v0, hud, kHudOldDay);
            lw(v0, hud, kHudPart);
            sw(v0, hud, kHudOldPart);
            sw(month, hud, kHudNewMonth);
            sw(day, hud, kHudNewDay);
            v0 = dsll32(part, 16);
            v0 = dsra32(v0, 16);
            sw(v0, hud, kHudNewPart);
            lw(v1, hud, kHudMonth);
            lw(v0, hud, kHudNewMonth);
            bool time_only = false;
            if (v1 == v0) {
                // 0x00184bc4
                charge(ctx, 4);
                lw(v1, hud, kHudDay);
                lw(v0, hud, kHudNewDay);
                if (v1 == v0) {
                    // 0x00184be8
                    charge(ctx, 2);
                    v0 = 6;
                    sw(v0, hud, kHudState);
                    time_only = true;
                }
            }
            if (!time_only) {
                // 0x00184bd4
                charge(ctx, 5);
                sw(zero, hud, kHudFade);
                v0 = 4;
                sw(v0, hud, kHudState);
            }
            // 0x00184bf0
            charge(ctx, 6);
            a0 = kHudFlagChanging;
            a1 = 1;
            jal(ctx, 0x184BF8u, gen::fn_datSetFlag_0016f1f0);
        } else {
            // 0x00184944
            charge(ctx, 16);
            a0 = kHudFlagChanging;
            a1 = 0;
            jal(ctx, 0x18494Cu, gen::fn_datSetFlag_0016f1f0);
            jal(ctx, 0x184954u, gen::fn_clndGetCurrentMonth_0017d920);
            sw(v0, hud, kHudMonth);
            jal(ctx, 0x184960u, gen::fn_clndGetCurrentDay_0017da40);
            sw(v0, hud, kHudDay);
            jal(ctx, 0x18496Cu, gen::fn_datGetTime_0016ef30);
            v1 = v0 & 0xFF;
            sw(v1, hud, kHudPart);
        }
    }
    // 0x00184c50 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(ra, sp, 0x80);
    lq(task, sp, 0x70);
    lq(days_shown, sp, 0x60);
    lq(enabled, sp, 0x50);
    lq(days_now, sp, 0x40);
    lq(hud, sp, 0x30);
    lq(part, sp, 0x20);
    lq(day, sp, 0x10);
    lq(month, sp, 0x0);
    sp = addiu(sp, 0x90);
}

// 0x00184C80 H_DayPartsDraw_SetDate -- 260 bytes; frame 0x60: ra sp+0x50, s4 sp+0x40 (sq), s3 sp+0x30 (sq), s2 sp+0x20 (sq), s1 sp+0x10 (sq), s0 sp+0x0 (sq)
// 0x184C80 H_DayPartsDraw_SetDate(task, enabled): show the current date and day part without an animation (state 2),
// clear flag 0x1410; enabled -> visible, else dirty. The two day counts it computes are not used.
// p3fes_handgen's register-faithful body, made readable (names, offsets, structure); the original's
// registers, frame, spills, links, cycle charges and check points are unchanged.
void H_DayPartsDraw_SetDate(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll32, hg::dsra32, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd,
          hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, month{ctx, 16}, hud{ctx, 17}, enabled{ctx, 18}, day{ctx, 19}, part{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00184c80
    enter(ctx, 48);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(ra, sp, 0x50);
    sq(part, sp, 0x40);
    sq(day, sp, 0x30);
    sq(enabled, sp, 0x20);
    sq(hud, sp, 0x10);
    sq(month, sp, 0x0);
    enabled = a1;
    lw(hud, a0, kTaskWork);
    sw(enabled, hud, kHudEnabled);
    jal(ctx, 0x184CA8u, gen::fn_clndGetCurrentMonth_0017d920);
    month = dsll32(v0, 16);
    month = dsra32(month, 16);
    jal(ctx, 0x184CB8u, gen::fn_clndGetCurrentDay_0017da40);
    day = dsll32(v0, 16);
    day = dsra32(day, 16);
    jal(ctx, 0x184CC8u, gen::fn_datGetTime_0016ef30);
    v0 = v0 & 0xFF;
    part = dsll32(v0, 16);
    part = dsra32(part, 16);
    day = dsll32(day, 16);
    day = dsra32(day, 16);
    month = dsll32(month, 16);
    month = dsra32(month, 16);
    a0 = month;
    a1 = day;
    jal(ctx, 0x184CF4u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
    lw(a0, hud, kHudMonth);
    lw(a1, hud, kHudDay);
    jal(ctx, 0x184D04u, gen::fn_clndGetDaysSinceStartFromDate_0017d8b0);
    sw(month, hud, kHudMonth);
    sw(day, hud, kHudDay);
    v0 = dsll32(part, 16);
    v0 = dsra32(v0, 16);
    sw(v0, hud, kHudPart);
    v0 = 2;
    sw(v0, hud, kHudState);
    a0 = kHudFlagChanging;
    a1 = 0;
    jal(ctx, 0x184D30u, gen::fn_datSetFlag_0016f1f0);
    if (enabled == 0) {
        // 0x00184d50
        charge(ctx, 4);
        v1 = 1;
        sw(v1, hud, kHudDirty);
        v1 = 2;
        sw(v1, hud, kHudState);
    } else {
        // 0x00184d40
        charge(ctx, 4);
        v1 = 1;
        sw(v1, hud, kHudVisible);
    }
    // 0x00184d60 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(ra, sp, 0x50);
    lq(part, sp, 0x40);
    lq(day, sp, 0x30);
    lq(enabled, sp, 0x20);
    lq(hud, sp, 0x10);
    lq(month, sp, 0x0);
    sp = addiu(sp, 0x60);
}

}  // namespace p3fes::game

// =====================================================================================================================
// Shims: the generated entry points of the replaced functions
// =====================================================================================================================
namespace p3fes::recomp_gen {
using namespace p3fes::game;
namespace {
void v0(p3fes::EEContext& ctx, u64 v) { ee::core::set_gpr64(ctx, GPR_V0, v); }
}  // namespace
void fn_sub_119A20_00119a20(p3fes::EEContext& ctx) { sub_119A20(ctx); }
void fn_sub_123640_00123640(p3fes::EEContext& ctx) { sub_123640(ctx); }
void fn_sub_124E00_00124e00(p3fes::EEContext& ctx) { sub_124E00(ctx); }
void fn_sub_128140_00128140(p3fes::EEContext& ctx) { sub_128140(ctx); }
void fn_sub_136820_00136820(p3fes::EEContext& ctx) { sub_136820(ctx); }
void fn_sub_138E80_00138e80(p3fes::EEContext& ctx) { sub_138E80(ctx); }
void fn_sub_1681D0_001681d0(p3fes::EEContext& ctx) { v0(ctx, sub_1681D0(ctx)); }
void fn_sub_169420_00169420(p3fes::EEContext& ctx) { v0(ctx, sub_169420(ctx)); }
void fn_sub_188640_00188640(p3fes::EEContext& ctx) { v0(ctx, sub_188640(ctx)); }
void fn_sub_188660_00188660(p3fes::EEContext& ctx) { v0(ctx, sub_188660(ctx)); }
void fn_sub_1885F0_001885f0(p3fes::EEContext& ctx) { v0(ctx, sub_1885F0(ctx)); }
void fn_sub_188BE0_00188be0(p3fes::EEContext& ctx) { v0(ctx, sub_188BE0(ctx)); }
}  // namespace p3fes::recomp_gen
