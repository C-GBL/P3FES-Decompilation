// The battle task / state machine layer (game/include/p3fes/game/battle_task.h), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/21_battle.md sections 1.1-1.4). Phase 5 slice `battle_task`: these replace the recompiled bodies listed
// in game/replaced.txt; tests/game/test_battle_task.cpp runs each against its __recomp body.
//
// How a battle runs through this file. The root kwln task "battle" calls btlUpdateTask every frame; while gBtl's
// running bit is set it drives, in order, the camera / packet / main-state / action / order / effect / sound
// subsystems (btlMainUpdateState is the 20-row btlMain machine, btlActionUpdateAll the per-actor 36-row machines).
// The btlMain states here wait on the packet queues (sub_27E410 counts what is still queued: a state moves on only
// when every queued animation / message packet has run) and on the UI tasks, then return the next state number; the
// btlAction states do the same per actor (a walk finished -> attack / skill / summon, a formation change done ->
// START, the end of a turn -> END and back to STANDBY). btlMainUpdateStateAction fills the 68-byte result block when
// btlMainCheckBattleEnd has set the "battle over" flag and picks WIN / ENEMY DEAD / REVIVAL_MES / LOSE / FADE_OUT.
//
// Virtual time per ADR-0013: every guest::enter / charge mirrors a `ctx.cycles += N` block of the recompiled body on
// the executed path, charged where the block starts (before its calls), and guest::backedge sits where the recompiled
// loop checks before jumping back (the test-first loops check before every iteration).
//
// Register discipline (the wave-6 / wave-7 lessons of docs/PHASE5_AGENT_BRIEF.md). These functions run with their
// callees' frames below them and are entered through `jalr` from the state drivers, and a check point may preempt the
// thread and save the whole register file into guest memory. So each one
//   * writes the original prologue spills (Frame: `sd ra`, `sq s0..`) and reloads them at the return;
//   * keeps in every register the original writes -- $at, $v0, $v1, $a0..$a3, $s0..$s2 -- the value the original has
//     there at each call, each check point and the return (S(...) where the original assigns it; a register the
//     original leaves alone keeps what the caller or the last callee left);
//   * calls through the callee's generated entry point with $ra = the original link (jal), and the indirect calls
//     with $v0 = the target and $ra = the `jalr` link (jalr_to);
//   * returns its result in $v0 through the shim; the void functions leave $v0 as their last callee left it.
// The gBtl pointer is read the way the original reads it, `lw rX, -18692(gp)`, through the guest $gp.
//
// Faithfulness audit (2026-10-21, tools/ours/audit): 19 of the 79 functions here are now p3fes_handgen's register-
// faithful bodies (their hand versions differed from the original: faults only 11, callee frames 7, frame/spills 1);
// each keeps the notes of its earlier hand version above it. The others are the hand-written versions this header
// describes.
#include "p3fes/game/battle_task.h"

#include "p3fes/ee/core.h"
#include "p3fes/game/guest.h"
#include "p3fes/game/hg_cpu.h"

namespace p3fes::recomp_gen {
// Still-recompiled callees (and the replaced ones of this and other slices, through their generated entry points).
void fn_sub_321120_00321120(p3fes::EEContext&);         // battle camera / device step (arg 2)
void fn_sub_2D1AC0_002d1ac0(p3fes::EEContext&);         // btlTarget per-frame update
void fn_sub_27F160_0027f160(p3fes::EEContext&);         // btlUnit pass (0 = before the states, 1 = after)
void fn_btlMainUpdateState_0029de80(p3fes::EEContext&); // the btlMain driver (battle_data)
void fn_btlActionUpdateAll_00299fb0(p3fes::EEContext&); // the btlAction driver (recompiled: RwFree)
void fn_sub_29AE40_0029ae40(p3fes::EEContext&);         // turn-order step
void fn_sub_29E420_0029e420(p3fes::EEContext&);         // camera step
void fn_sub_286540_00286540(p3fes::EEContext&);         // btlUnit models step
void fn_sub_2DB960_002db960(p3fes::EEContext&);         // sound step
void fn_nullsub_17_002bf990(p3fes::EEContext&);
void fn_sub_2A46E0_002a46e0(p3fes::EEContext&);         // effect step
void fn_nullsub_20_002e2f20(p3fes::EEContext&);
void fn_btlSupportTickTimers_002dcc40(p3fes::EEContext&);         // sound step 2
void fn_sub_27CE10_0027ce10(p3fes::EEContext&);         // this file
void fn_sub_27D020_0027d020(p3fes::EEContext&);         // the battle teardown
void fn_kwlnTaskGetTaskByName_00195340(p3fes::EEContext&);         // [kwlnTaskGetTaskByName] (kwln_task)
void fn_kwlnTaskDestroyWithHierarchy_00195020(p3fes::EEContext&);         // [kwlnTaskDestroyWithHierarchy] (kwln_task)
void fn_btlActionSetState_00299d60(p3fes::EEContext&);  // (action, state) (battle_data)
void fn_sub_281270_00281270(p3fes::EEContext&);         // btlUnit: still moving
void fn_sub_27F7C0_0027f7c0(p3fes::EEContext&);         // btlUnit position -> a 16-byte vector
void fn_sub_2822B0_002822b0(p3fes::EEContext&);         // a "move to" packet
void fn_sub_27ED20_0027ed20(p3fes::EEContext&);         // queue a packet (packet, queue)
void fn_sub_27E390_0027e390(p3fes::EEContext&);         // btlPacketFindFirstByActionUID (battle_data)
void fn_sub_27E470_0027e470(p3fes::EEContext&);         // this file
void fn_sub_2E4330_002e4330(p3fes::EEContext&);         // an end-of-turn event wanted
void fn_sub_1FDD40_001fdd40(p3fes::EEContext&);         // battle panel refresh
void fn_sub_2DCF80_002dcf80(p3fes::EEContext&);         // sound bank (bank, 0)
void fn_sub_2DCED0_002dced0(p3fes::EEContext&);         // sound (0)
void fn_btlBossSetup_002f6e00(p3fes::EEContext&);       // boss records / AI event procedures
void fn_sub_17B180_0017b180(p3fes::EEContext&);         // (1)
void fn_sub_29E390_0029e390(p3fes::EEContext&);         // scene load
void fn_sub_29E400_0029e400(p3fes::EEContext&);         // scene ready
void fn_sub_27E410_0027e410(p3fes::EEContext&);         // this file
void fn_sub_1A0410_001a0410(p3fes::EEContext&);         // (1)
void fn_sub_29DFC0_0029dfc0(p3fes::EEContext&);         // scene / camera setup
void fn_datGetFlag_0016f190(p3fes::EEContext&);         // (flag)
void fn_sub_2E2EC0_002e2ec0(p3fes::EEContext&);         // a setup packet (kind)
void fn_sub_2E2A10_002e2a10(p3fes::EEContext&);         // a packet
void fn_sub_2F9BC0_002f9bc0(p3fes::EEContext&);         // a packet
void fn_sub_2FF2D0_002ff2d0(p3fes::EEContext&);         // genus-ready byte (battle_data)
void fn_sub_2FACC0_002facc0(p3fes::EEContext&);         // the start hook
void fn_sub_1FECC0_001fecc0(p3fes::EEContext&);         // panel busy
void fn_sub_2E42C0_002e42c0(p3fes::EEContext&);         // event busy
void fn_sub_2E4290_002e4290(p3fes::EEContext&);         // (action) event busy
void fn_sub_29B040_0029b040(p3fes::EEContext&);         // this file
void fn_sub_1FDD20_001fdd20(p3fes::EEContext&);         // panel start
void fn_sub_29B070_0029b070(p3fes::EEContext&);         // this file
void fn_sub_1FF390_001ff390(p3fes::EEContext&);         // panel end 1
void fn_sub_1FF350_001ff350(p3fes::EEContext&);         // panel end 2
void fn_sub_29AD20_0029ad20(p3fes::EEContext&);         // this file
void fn_sub_2D4ED0_002d4ed0(p3fes::EEContext&);         // (action) -> 1: result flag 1
void fn_memset_00521408(p3fes::EEContext&);
void fn_datCalcIsDead_0030b5a0(p3fes::EEContext&);      // (unit, delta)
void fn_btlGetEncounterId_002d5550(p3fes::EEContext&);         // a result word
void fn_datCalcClearBadStatus_00300560(p3fes::EEContext&);  // (unit, bits)
void fn_sub_1F1AE0_001f1ae0(p3fes::EEContext&);         // the result screen (block) -> handle
void fn_sub_27D560_0027d560(p3fes::EEContext&);         // this file
void fn_sub_2FB690_002fb690(p3fes::EEContext&);         // the enemy-dead event
void fn_sub_2DB890_002db890(p3fes::EEContext&);         // a sound packet
void fn_sub_2DDBE0_002ddbe0(p3fes::EEContext&);         // victory sound
void fn_sub_1F1B20_001f1b20(p3fes::EEContext&);         // result: fade (handle)
void fn_sub_108570_00108570(p3fes::EEContext&);         // screen fade: reset
void fn_sub_108670_00108670(p3fes::EEContext&);         // screen fade: kind
void fn_sub_108680_00108680(p3fes::EEContext&);         // screen fade: colour
void fn_sub_1086A0_001086a0(p3fes::EEContext&);         // screen fade: start (frames)
void fn_sub_1F1B40_001f1b40(p3fes::EEContext&);         // result: fade busy (handle)
void fn_sub_108710_00108710(p3fes::EEContext&);         // screen fade: state
void fn_sub_29E3C0_0029e3c0(p3fes::EEContext&);         // scene release
void fn_sub_2BFC50_002bfc50(p3fes::EEContext&);         // (1)
void fn_sub_1F1B60_001f1b60(p3fes::EEContext&);         // result: open (handle)
void fn_sub_1F1F40_001f1f40(p3fes::EEContext&);         // result: field return wanted
void fn_sub_1B0710_001b0710(p3fes::EEContext&);         // the field return
void fn_sub_1F1B00_001f1b00(p3fes::EEContext&);         // result: busy (handle)
void fn_sub_1F1C20_001f1c20(p3fes::EEContext&);         // result: close (handle)
void fn_sub_1085C0_001085c0(p3fes::EEContext&);         // screen fade in
void fn_sub_27E4D0_0027e4d0(p3fes::EEContext&);         // this file
void fn_btlSupportIsBusy_002dba60(p3fes::EEContext&);         // sound busy
void fn_sub_2DCF10_002dcf10(p3fes::EEContext&);         // sound release
void fn_sub_10A4E0_0010a4e0(p3fes::EEContext&);         // a system sound (0, 0, 3, 0)
void fn_sub_2FF260_002ff260(p3fes::EEContext&);         // (0)
void fn_sub_3C72D0_003c72d0(p3fes::EEContext&);         // the yes/no window (setup)
void fn_msgWinRequestMessage_003c7430(p3fes::EEContext&);
void fn_msgWinSetType_003c7560(p3fes::EEContext&);
void fn_sub_3C74E0_003c74e0(p3fes::EEContext&);
void fn_sub_2B8D60_002b8d60(p3fes::EEContext&);         // a camera packet (3, 4095)
void fn_sub_2A3B40_002a3b40(p3fes::EEContext&);         // a message packet (0, 36)
void fn_sub_3C7B90_003c7b90(p3fes::EEContext&);         // the yes/no window (update)
void fn_sub_3C7850_003c7850(p3fes::EEContext&);         // still open
void fn_msgWinLastSelection_003c7610(p3fes::EEContext&);         // the answer
void fn_sub_1FF3B0_001ff3b0(p3fes::EEContext&);         // panel
void fn_btlCreate_0027ced0(p3fes::EEContext&);          // gBtl (RwHeapMalloc), the subsystems' init
void fn_kwlnTaskCreate_00194b20(p3fes::EEContext&);     // (parent, name, prio, update, $t0 destroy, $t1) (kwln_task)
void fn_bpRoot_CreateBattlePanelTasks_001fd630(p3fes::EEContext&);         // the battle panel task tree (parent)
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_btlMainSetState_0029de20(p3fes::EEContext&);    // (state) (battle_data)
void fn_sub_2BFC90_002bfc90(p3fes::EEContext&);         // a revival allowed
void fn_sub_300700_00300700(p3fes::EEContext&);         // [datCalcHasCounter] (unit, id) (battle_rest)
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace {

using namespace btl_task;
namespace rg = p3fes::recomp_gen;

// --- registers ---------------------------------------------------------------------------------------------------
constexpr unsigned kV0 = 2, kV1 = 3, kA0 = 4, kA1 = 5, kA2 = 6, kA3 = 7, kT0 = 8, kT1 = 9, kS0 = 16, kS1 = 17, kS2 = 18, kGP = 28;

u64 R(const EEContext& ctx, unsigned r) { return ee::core::gpr64(ctx, r); }
void S(EEContext& ctx, unsigned r, u64 v) { ee::core::set_gpr64(ctx, r, v); }
u64 sx(u32 v) { return ee::core::sext32(v); }
u32 a32(u64 v) { return static_cast<u32>(v); }

template <typename T> T ld(const EEContext& ctx, u64 va) { return guest::load<T>(ctx, a32(va)); }
template <typename T> void st(EEContext& ctx, u64 va, T v) { guest::store<T>(ctx, a32(va), v); }
// `lw rX, off(base)`: the word sign-extended, as the register holds it.
u64 lw(const EEContext& ctx, u64 base, u32 off) { return sx(ld<u32>(ctx, a32(base) + off)); }
u64 lhu(const EEContext& ctx, u64 base, u32 off) { return ld<u16>(ctx, a32(base) + off); }
u64 lbu(const EEContext& ctx, u64 base, u32 off) { return ld<u8>(ctx, a32(base) + off); }
// `addiu rd, rs, imm` on an address: the 32-bit sum sign-extended.
u64 addr(u64 base, s32 off) { return sx(a32(base) + static_cast<u32>(off)); }

// `lw rX, -18692(gp)`: the battle context gBtl, through the guest $gp as the original reads it.
u64 gbtl(const EEContext& ctx) { return lw(ctx, R(ctx, kGP), static_cast<u32>(kGBtlGpOffset)); }

// `jal fn` with $ra = the original link (the value the generated body hands rt::jal); returns $v0.
u64 jal(EEContext& ctx, u32 link, guest::Fn fn) {
    rt::jal(ctx, link);
    fn(ctx);
    return R(ctx, kV0);
}
// `lw v0, ...; jalr v0` at `link`: $v0 = the target (sign-extended), $ra = the link; returns $v0.
u64 jalr_to(EEContext& ctx, u32 link, u32 target) {
    S(ctx, kV0, sx(target));
    rt::jalr(ctx, GPR_RA, link);
    rt::lookup_func(target)(ctx);
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

}  // namespace

// =====================================================================================================================
// The root task
// =====================================================================================================================

// 0x27D1D0 btlStart(setup): the battle's entry (the field event task and btlScrCmd_CALL_BATTLE call it). btlCreate
// allocates gBtl; the root kwln task "battle" (name at gp-26600, prio 10, btlUpdateTask / btlDestroyTask) goes to
// gBtl+3352 with its three draw children -- "battle_draw_3d" (prio 0x821, btlUpdateDraw3DTask), "battle_draw_3d_front" (0x1049,
// btlUpdateDraw3DFrontTask), "battle_draw_2d" (0x106F, btlUpdateDraw2DTask) --, the panel task tree to gBtl+3372. With a 52-byte setup block it
// is copied to gBtl+2984, its field / room ids (+24 / +26) to gBtl+580 / +582, and the btlMain machine enters INIT (2);
// without one gBtl+2981 = 1 and it enters TEST (18), or MC (19) with flag 5147. gBtl+12 bit 0 (running) is set and the
// root task returned.
u64 btlStart(EEContext& ctx, u64 setup) {
    guest::enter(ctx, 64);
    Frame f(ctx, 48, 32, 2);
    S(ctx, kS1, setup);
    jal(ctx, 0x27d1e4u, &rg::fn_btlCreate_0027ced0);
    S(ctx, kA0, 0);
    S(ctx, kA1, addr(R(ctx, kGP), -26600));
    S(ctx, kA2, 10);
    S(ctx, kA3, 0x27CC30u);  // btlUpdateTask
    S(ctx, kT0, 0x27CDF0u);  // btlDestroyTask
    S(ctx, kT1, 0);
    const u64 root = jal(ctx, 0x27d20cu, &rg::fn_kwlnTaskCreate_00194b20);
    u64 g = gbtl(ctx);
    S(ctx, kV1, g);
    st<u32>(ctx, g + kRootChildTask, a32(root));
    struct Child {
        u32 name, prio, update, link;
    };
    static constexpr Child kChildren[3] = {{0x68F0B0u, 2081, 0x27CCF0u, 0x27d240u},
                                           {0x68F0D0u, 4169, 0x27CD70u, 0x27d26cu},
                                           {0x68F0C0u, 4207, 0x27CDA0u, 0x27d298u}};
    for (const Child& c : kChildren) {
        g = gbtl(ctx);
        S(ctx, kV0, g);
        S(ctx, kA0, lw(ctx, g, kRootChildTask));
        S(ctx, kA1, c.name);
        S(ctx, kA2, c.prio);
        S(ctx, kA3, c.update);
        S(ctx, kT0, 0);
        S(ctx, kT1, 0);
        jal(ctx, c.link, &rg::fn_kwlnTaskCreate_00194b20);
    }
    g = gbtl(ctx);
    S(ctx, kV0, g);
    S(ctx, kA0, lw(ctx, g, kRootChildTask));
    const u64 panel = jal(ctx, 0x27d2a8u, &rg::fn_bpRoot_CreateBattlePanelTasks_001fd630);
    g = gbtl(ctx);
    S(ctx, kV1, g);
    st<u32>(ctx, g + kEndTask, a32(panel));
    jal(ctx, 0x27d2b8u, &rg::fn_sub_1FF350_001ff350);
    g = gbtl(ctx);
    S(ctx, kV1, g);
    const u64 task = lw(ctx, g, kRootChildTask);
    S(ctx, kS0, task);
    if (setup != 0) {
        guest::charge(ctx, 18);
        st<u8>(ctx, g + kTestBattle, 0);
        const u64 g2 = gbtl(ctx);
        S(ctx, kV0, g2);
        S(ctx, kA0, addr(g2, kSetupBlock));
        S(ctx, kA1, setup);
        S(ctx, kA2, 52);
        jal(ctx, 0x27d2e4u, &rg::fn_memcpy_00521250);
        for (u32 k = 0; k < 2; ++k) {
            const u64 g3 = gbtl(ctx);
            S(ctx, kV1, g3);
            const u64 id = lhu(ctx, g3, kSetupBlock + 24 + 2 * k);
            S(ctx, kV0, id);
            st<u16>(ctx, g3 + kSetupField + 2 * k, static_cast<u16>(id));
        }
        S(ctx, kA0, 2);
        jal(ctx, 0x27d308u, &rg::fn_btlMainSetState_0029de20);
    } else {
        guest::charge(ctx, 7);
        S(ctx, kV0, 1);
        st<u8>(ctx, g + kTestBattle, 1);
        S(ctx, kA0, 5147);
        if (jal(ctx, 0x27d324u, &rg::fn_datGetFlag_0016f190) != 0) {
            guest::charge(ctx, 3);
            S(ctx, kA0, 19);
            jal(ctx, 0x27d34cu, &rg::fn_btlMainSetState_0029de20);
        } else {
            guest::charge(ctx, 5);
            S(ctx, kA0, 18);
            jal(ctx, 0x27d338u, &rg::fn_btlMainSetState_0029de20);
        }
    }
    guest::charge(ctx, 11);
    g = gbtl(ctx);
    S(ctx, kV1, g);
    st<u32>(ctx, g + kFlags, a32(lw(ctx, g, kFlags) | 1u));
    return task;
}

// 0x27D560 [btlCanRevive](): with gBtl+12 bit 0x800000 (revival offered) and sub_2BFC90(), whether the current actor's
// DatUnit has effect 4040 (sub_300700); else 0.
u64 sub_27D560(EEContext& ctx) {
    guest::enter(ctx, 8);
    Frame f(ctx, 16, 0, 0);
    const u64 fl = lw(ctx, gbtl(ctx), kFlags);
    S(ctx, kV1, fl);
    S(ctx, kV0, fl & 0x800000u);
    if ((fl & 0x800000u) == 0) {
        guest::charge(ctx, 3 + 4);
        return 0;
    }
    guest::charge(ctx, 4);
    if (jal(ctx, 0x27d58cu, &rg::fn_sub_2BFC90_002bfc90) == 0) {
        guest::charge(ctx, 3 + 4);
        return 0;
    }
    guest::charge(ctx, 7);
    const u64 unit = lw(ctx, lw(ctx, gbtl(ctx), kCurrentAction), kActUnit);
    S(ctx, kV0, unit);
    S(ctx, kA0, lw(ctx, unit, kUnitDat));
    S(ctx, kA1, 4040);
    const u64 r = jal(ctx, 0x27d5bcu, &rg::fn_sub_300700_00300700);
    guest::charge(ctx, 4);
    return r;
}

// 0x27CC30 btlUpdateTask(): the "battle" task's update callback. While gBtl+12 bit 0 (running) is set, the frame's
// battle work in its fixed order: camera/device step (2), target update, the btlUnit pre-pass, the btlMain state
// machine, every btlAction, the turn order, camera, unit models, sound, effects, sound, the btlUnit post-pass.
// Once the running bit is cleared (btlMainUpdateStateExit) it tears the child tasks down instead. Returns 0.
u64 btlUpdateTask(EEContext& ctx) {
    guest::enter(ctx, 7);
    Frame f(ctx, 16, 0, 0);
    const u64 running = lw(ctx, gbtl(ctx), kFlags) & 1u;
    S(ctx, kV0, running);
    if (running == 0) {
        guest::charge(ctx, 2);
        jal(ctx, 0x27ccd0u, &rg::fn_sub_27CE10_0027ce10);
    } else {
        guest::charge(ctx, 33);
        S(ctx, kA0, 2);
        jal(ctx, 0x27cc50u, &rg::fn_sub_321120_00321120);
        jal(ctx, 0x27cc58u, &rg::fn_sub_2D1AC0_002d1ac0);
        S(ctx, kA0, 0);
        jal(ctx, 0x27cc64u, &rg::fn_sub_27F160_0027f160);
        jal(ctx, 0x27cc6cu, &rg::fn_btlMainUpdateState_0029de80);
        jal(ctx, 0x27cc74u, &rg::fn_btlActionUpdateAll_00299fb0);
        jal(ctx, 0x27cc7cu, &rg::fn_sub_29AE40_0029ae40);
        jal(ctx, 0x27cc84u, &rg::fn_sub_29E420_0029e420);
        jal(ctx, 0x27cc8cu, &rg::fn_sub_286540_00286540);
        jal(ctx, 0x27cc94u, &rg::fn_sub_2DB960_002db960);
        jal(ctx, 0x27cc9cu, &rg::fn_nullsub_17_002bf990);
        jal(ctx, 0x27cca4u, &rg::fn_sub_2A46E0_002a46e0);
        jal(ctx, 0x27ccacu, &rg::fn_nullsub_20_002e2f20);
        jal(ctx, 0x27ccb4u, &rg::fn_btlSupportTickTimers_002dcc40);
        S(ctx, kA0, 1);
        jal(ctx, 0x27ccc0u, &rg::fn_sub_27F160_0027f160);
    }
    guest::charge(ctx, 5);
    return 0;
}

// 0x27CDF0 btlDestroyTask(): the destroy callback: the battle teardown sub_27D020.
void btlDestroyTask(EEContext& ctx) {
    guest::enter(ctx, 8);
    Frame f(ctx, 16, 0, 0);
    jal(ctx, 0x27cdf8u, &rg::fn_sub_27D020_0027d020);
}

// 0x27CE10 [btlDestroyRootChildren](): when the task named by the string at gp-26600 still exists, destroy the task
// gBtl+3352 with its whole hierarchy.
void sub_27CE10(EEContext& ctx) {
    guest::enter(ctx, 7);
    Frame f(ctx, 16, 0, 0);
    S(ctx, kA0, addr(R(ctx, kGP), -26600));
    if (jal(ctx, 0x27ce1cu, &rg::fn_kwlnTaskGetTaskByName_00195340) != 0) {
        guest::charge(ctx, 4);
        const u64 g = gbtl(ctx);
        S(ctx, kV0, g);
        S(ctx, kA0, lw(ctx, g, kRootChildTask));
        jal(ctx, 0x27ce34u, &rg::fn_kwlnTaskDestroyWithHierarchy_00195020);
    }
    guest::charge(ctx, 4);
}

// 0x27E410 [btlPacketCountAll](): the number of packets in the four queues (head gBtl+372 + 8 * q, next +124).
u64 sub_27E410(EEContext& ctx) {
    guest::enter(ctx, 5);
    const u64 g = gbtl(ctx);
    u32 count = 0;
    S(ctx, kV0, 0);
    S(ctx, kA1, 0);
    S(ctx, kA0, g);
    for (u32 q = 0;; ++q) {
        guest::charge(ctx, 3);
        S(ctx, kV1, q < 4 ? 1 : 0);
        if (q >= 4) break;
        guest::backedge(ctx);
        guest::charge(ctx, 5);
        u64 p = lw(ctx, g, kPacketQueues + 8 * q);
        S(ctx, kV1, p);
        for (;;) {
            guest::charge(ctx, 5);
            if (p == 0) break;
            guest::backedge(ctx);
            guest::charge(ctx, 2);
            S(ctx, kV0, sx(++count));
            p = lw(ctx, p, 124);
            S(ctx, kV1, p);
        }
        guest::charge(ctx, 1);
        S(ctx, kA1, q + 1);
    }
    guest::charge(ctx, 2);
    return sx(count);
}

// 0x27E470 [btlPacketCountOfType](type): the queued packets whose word +64 equals `type` (its low 16 bits; the word is
// compared as the sign-extended register, so a word with bit 31 set never matches).
u64 sub_27E470(EEContext& ctx, u64 type) {
    guest::enter(ctx, 6);
    const u64 g = gbtl(ctx);
    const u64 want = type & 0xFFFFu;
    u32 count = 0;
    S(ctx, kV0, 0);
    S(ctx, kA2, 0);
    S(ctx, kA1, g);
    S(ctx, kA0, want);
    for (u32 q = 0;; ++q) {
        guest::charge(ctx, 3);
        S(ctx, kV1, q < 4 ? 1 : 0);
        if (q >= 4) break;
        guest::backedge(ctx);
        guest::charge(ctx, 5);
        S(ctx, kV1, addr(g, static_cast<s32>(8 * q)));
        u64 p = lw(ctx, g, kPacketQueues + 8 * q);
        S(ctx, kA3, p);
        for (;;) {
            guest::charge(ctx, 2);
            if (p == 0) break;
            guest::backedge(ctx);
            guest::charge(ctx, 3);
            const u64 kind = lw(ctx, p, 64);
            S(ctx, kV1, kind);
            if (kind == want) {
                guest::charge(ctx, 1);
                S(ctx, kV0, sx(++count));
            }
            guest::charge(ctx, 1);
            p = lw(ctx, p, 124);
            S(ctx, kA3, p);
        }
        guest::charge(ctx, 1);
        S(ctx, kA2, q + 1);
    }
    guest::charge(ctx, 2);
    return sx(count);
}

// 0x27E4D0 [btlPacketMarkAll](): walking each queue from its head along +128 -- the *previous* link (sub_27ED20 appends
// at the tail), so in a well-formed queue only the head is visited --, a packet whose byte +71 has bit 0 gets bit 2
// there too (btlMainInitStateExit: the running packets are told to finish).
void sub_27E4D0(EEContext& ctx) {
    guest::enter(ctx, 3);
    S(ctx, kA1, 0);
    for (u32 q = 0;; ++q) {
        guest::charge(ctx, 3);
        S(ctx, kV1, q < 4 ? 1 : 0);
        if (q >= 4) break;
        guest::backedge(ctx);
        guest::charge(ctx, 6);
        S(ctx, kA0, sx(8 * q));
        const u64 g = gbtl(ctx);
        S(ctx, kV1, addr(g, static_cast<s32>(8 * q)));
        u64 p = lw(ctx, g, kPacketQueues + 8 * q);
        S(ctx, kA2, p);
        for (;;) {
            guest::charge(ctx, 2);
            if (p == 0) break;
            guest::backedge(ctx);
            guest::charge(ctx, 4);
            const u64 b = lbu(ctx, p, 71);
            S(ctx, kA0, b);
            S(ctx, kV1, b & 1u);
            if ((b & 1u) != 0) {
                guest::charge(ctx, 2);
                S(ctx, kV1, b | 4u);
                st<u8>(ctx, p + 71, static_cast<u8>(b | 4u));
            }
            guest::charge(ctx, 1);
            p = lw(ctx, p, 128);
            S(ctx, kA2, p);
        }
        guest::charge(ctx, 1);
        S(ctx, kA1, q + 1);
    }
    guest::charge(ctx, 2);
}

// =====================================================================================================================
// btlAction states (sBtlActionTbl 0x693410; the empty init / update slots are `jr ra` bodies)
// =====================================================================================================================

namespace {
void empty_state(EEContext& ctx) { guest::enter(ctx, 2); }
}  // namespace

void sub_28A990(EEContext& ctx) { empty_state(ctx); }
void sub_28A9A0(EEContext& ctx) { empty_state(ctx); }
void sub_28A9B0(EEContext& ctx) { empty_state(ctx); }
void sub_28D070(EEContext& ctx) { empty_state(ctx); }
void sub_28DBE0(EEContext& ctx) { empty_state(ctx); }
void sub_28EB40(EEContext& ctx) { empty_state(ctx); }
void sub_290BD0(EEContext& ctx) { empty_state(ctx); }
void sub_295150(EEContext& ctx) { empty_state(ctx); }
void sub_295B90(EEContext& ctx) { empty_state(ctx); }
void sub_295BF0(EEContext& ctx) { empty_state(ctx); }
void sub_296310(EEContext& ctx) { empty_state(ctx); }
void sub_296880(EEContext& ctx) { empty_state(ctx); }
void sub_297750(EEContext& ctx) { empty_state(ctx); }
void sub_2990F0(EEContext& ctx) { empty_state(ctx); }
void sub_299D20(EEContext& ctx) { empty_state(ctx); }

// 0x0028A9C0 sub_28A9C0 -- 88 bytes; frame 0x10: ra sp+0x0
// 0x28A9C0 [btlActionUpdateStateStandBy](action): an idle actor whose unit got the endure flag goes to ENDURE (22),
// one whose unit died to DEAD (33).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_28A9C0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lw, hg::sd;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0028a9c0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, 48);
    lw(a1, v1, 156);
    v1 = a1 & 0x10;
    if (v1 == 0) {
        // 0x0028a9f0
        charge(ctx, 3);
        v1 = a1 & 0x1;
        if (v1 != 0) {
            // 0x0028a9fc
            charge(ctx, 3);
            a1 = 33;
            jal(ctx, 0x28AA00u, gen::fn_btlActionSetState_00299d60);
        }
    } else {
        // 0x0028a9dc
        charge(ctx, 5);
        a1 = 22;
        jal(ctx, 0x28A9E0u, gen::fn_btlActionSetState_00299d60);
    }
    // 0x0028aa08 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0028B9C0 sub_28B9C0 -- 140 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// 0x28B9C0 [btlActionUpdateStateStartHome](action): once the unit stopped moving, queue a "move to" packet for the
// unit's current position (a 16-byte vector in the frame at sp+32), tagged with the action's uid, and return to the
// state in +20.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: frame/spills (own frame)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_28B9C0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0028b9c0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 48);
    jal(ctx, 0x28B9D4u, gen::fn_sub_281270_00281270);
    if (v0 == 0) {
        // 0x0028b9e4
        charge(ctx, 21);
        lw(a0, s0, 48);
        a1 = 0;
        a2 = 0;
        a3 = addiu(sp, 0x20);
        jal(ctx, 0x28B9F4u, gen::fn_sub_27F7C0_0027f7c0);
        lw(a0, s0, 48);
        a1 = addiu(sp, 0x20);
        a2 = 0;
        jal(ctx, 0x28BA08u, gen::fn_sub_2822B0_002822b0);
        a0 = v0;
        ld(v1, s0, 0);
        sd(v1, v0, 96);
        a1 = 1;
        jal(ctx, 0x28BA20u, gen::fn_sub_27ED20_0027ed20);
        a0 = s0;
        lhu(a1, s0, 20);
        jal(ctx, 0x28BA30u, gen::fn_btlActionSetState_00299d60);
    }
    // 0x0028ba38 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x0028BCA0 sub_28BCA0 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x28BCA0 [btlActionUpdateStateChangeFormation](action): when no packet of this action is queued any more, START (2).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_28BCA0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll, hg::dsll32, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0028bca0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    ld(a0, a0, 0);
    v0 = 0x3FFF0000;
    v0 = v0 | 0xFFFF;
    v1 = dsll32(v0, 0);
    v0 = 0xFFFF;
    v0 = dsll(v0, 16);
    v0 = v0 | 0xFFFF;
    a1 = v0 | v1;
    jal(ctx, 0x28BCD0u, gen::fn_sub_27E390_0027e390);
    if (v0 == 0) {
        // 0x0028bce0
        charge(ctx, 4);
        a0 = s0;
        a1 = 2;
        jal(ctx, 0x28BCE8u, gen::fn_btlActionSetState_00299d60);
    }
    // 0x0028bcf0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0028C9F0 sub_28C9F0 -- 16 bytes; leaf frame (no stack)
// 0x28C9F0 [btlActionInitStateAnalyze](action): +1156 = 1.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_28C9F0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4};
    // 0x0028c9f0
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 1;
    sw(v1, a0, 1156);
}

// 0x0028E740 sub_28E740 -- 168 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x28E740 / 0x28EA90 (one body twice): once the unit stopped moving, the action's move kind +108 picks the next state:
// 9 -> SUMMON (18), 3 or 2 -> SKILL (16), 1 -> ATTACK (15), anything else -> NON (0). `link1` / `link2`: the two jal
// links of the copy.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_28E740(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0028e740
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 48);
    jal(ctx, 0x28E754u, gen::fn_sub_281270_00281270);
    if (v0 == 0) {
        // 0x0028e764
        charge(ctx, 4);
        lhu(v1, s0, 108);
        v0 = 9;
        if (v1 == v0) {
            // 0x0028e7b8
            charge(ctx, 3);
            a1 = 18;
        } else {
            // 0x0028e774
            charge(ctx, 3);
            v0 = 3;
            if (v1 != v0) {
                // 0x0028e780
                charge(ctx, 3);
                v0 = 2;
                if (v1 == v0) {
                    goto L_0028e7ac;
                }
                // 0x0028e78c
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x0028e7a0
                    charge(ctx, 3);
                    a1 = 15;
                } else {
                    // 0x0028e798
                    charge(ctx, 2);
                    // 0x0028e7c4
                    charge(ctx, 1);
                    a1 = 0;
                }
                goto L_0028e7c8;
            }
        L_0028e7ac:
            charge(ctx, 3);
            a1 = 16;
        }
    L_0028e7c8:
        charge(ctx, 3);
        a0 = s0;
        jal(ctx, 0x28E7CCu, gen::fn_btlActionSetState_00299d60);
    }
    // 0x0028e7d4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0028EA90 sub_28EA90 -- 168 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x28E740 / 0x28EA90 (one body twice): once the unit stopped moving, the action's move kind +108 picks the next state:
// 9 -> SUMMON (18), 3 or 2 -> SKILL (16), 1 -> ATTACK (15), anything else -> NON (0). `link1` / `link2`: the two jal
// links of the copy.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_28EA90(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0028ea90
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 48);
    jal(ctx, 0x28EAA4u, gen::fn_sub_281270_00281270);
    if (v0 == 0) {
        // 0x0028eab4
        charge(ctx, 4);
        lhu(v1, s0, 108);
        v0 = 9;
        if (v1 == v0) {
            // 0x0028eb08
            charge(ctx, 3);
            a1 = 18;
        } else {
            // 0x0028eac4
            charge(ctx, 3);
            v0 = 3;
            if (v1 != v0) {
                // 0x0028ead0
                charge(ctx, 3);
                v0 = 2;
                if (v1 == v0) {
                    goto L_0028eafc;
                }
                // 0x0028eadc
                charge(ctx, 3);
                v0 = 1;
                if (v1 == v0) {
                    // 0x0028eaf0
                    charge(ctx, 3);
                    a1 = 15;
                } else {
                    // 0x0028eae8
                    charge(ctx, 2);
                    // 0x0028eb14
                    charge(ctx, 1);
                    a1 = 0;
                }
                goto L_0028eb18;
            }
        L_0028eafc:
            charge(ctx, 3);
            a1 = 16;
        }
    L_0028eb18:
        charge(ctx, 3);
        a0 = s0;
        jal(ctx, 0x28EB1Cu, gen::fn_btlActionSetState_00299d60);
    }
    // 0x0028eb24 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00294D10 sub_294D10 -- 40 bytes; leaf frame (no stack)
// 0x294D10 [btlActionInitStateReinforce](action): the unit gets flag 8 (reinforced); gBtl+2566 bit 0 is cleared.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_294D10(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lhu, hg::lw, hg::sh, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, gp{ctx, 28};
    // 0x00294d10
    enter(ctx, 10);  // entry check point + this block's cycles
    lw(a0, a0, 48);
    lw(v1, a0, 156);
    v1 = v1 | 0x8;
    sw(v1, a0, 156);
    lw(a0, gp, -18692);  // 0x7CE3EC
    lhu(v1, a0, 2566);
    v1 = v1 & 0xFFFE;
    sh(v1, a0, 2566);
}

// 0x00295B20 sub_295B20 -- 104 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x295B20 [btlActionUpdateStateAssist](action): once no packet of type 1286 or 2048 is queued, set action flag 0x100
// and go to READY (12).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_295B20(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq, hg::sd, hg::sh, hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00295b20
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    a0 = 1286;
    jal(ctx, 0x295B34u, gen::fn_sub_27E470_0027e470);
    if (v0 == 0) {
        // 0x00295b44
        charge(ctx, 5);
        a0 = 2048;
        jal(ctx, 0x295B48u, gen::fn_sub_27E470_0027e470);
        if (v0 == 0) {
            // 0x00295b58
            charge(ctx, 7);
            lhu(v0, s0, 24);
            v0 = v0 | 0x100;
            sh(v0, s0, 24);
            a0 = s0;
            a1 = 12;
            jal(ctx, 0x295B6Cu, gen::fn_btlActionSetState_00299d60);
        }
    }
    // 0x00295b74 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00295BA0 sub_295BA0 -- 72 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x295BA0 [btlActionUpdateStateEvent](action): run the callback in +1184 (`jalr`, $a0 = the action); once it returns
// 0, go to the state in +1180.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_295BA0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::jalr, hg::ld, hg::lhu, hg::lq, hg::lw, hg::sd,
          hg::sq;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00295ba0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(v0, a0, 1184);
    jalr(ctx, 0x295BB4u, v0.u());
    if (v0 == 0) {
        // 0x00295bc4
        charge(ctx, 4);
        a0 = s0;
        lhu(a1, s0, 1180);
        jal(ctx, 0x295BCCu, gen::fn_btlActionSetState_00299d60);
    }
    // 0x00295bd4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00295F00 sub_295F00 -- 152 bytes; frame 0x10: ra sp+0x0
// 0x295F00 [btlActionInitStateEndure](action): clear the unit's endure flag (0x10); the endure skills mark the
// DatUnit's flags (572 -> 0x400, 571 -> 0x8); an action without a command goes on to STANDBY (1).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_295F00(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lw, hg::sd, hg::sh, hg::si, hg::sw;
    Gpr v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00295f00
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a2, a0, 48);
    lw(a1, a2, 156);
    v1 = si(-17);
    v1 = a1 & v1;
    sw(v1, a2, 156);
    lhu(a1, a0, 1120);
    v1 = 572;
    if (a1 == v1) {
        // 0x00295f5c
        charge(ctx, 5);
        lw(v1, a0, 48);
        lw(a1, v1, 2604);
        lhu(v1, a1, 0);
        v1 = v1 | 0x400;
        sh(v1, a1, 0);
    } else {
        // 0x00295f2c
        charge(ctx, 3);
        v1 = 571;
        if (a1 == v1) {
            // 0x00295f40
            charge(ctx, 7);
            lw(v1, a0, 48);
            lw(a1, v1, 2604);
            lhu(v1, a1, 0);
            v1 = v1 | 0x8;
            sh(v1, a1, 0);
        } else {
            // 0x00295f38
            charge(ctx, 2);
        }
    }
    // 0x00295f70
    charge(ctx, 3);
    lhu(v1, a0, 1120);
    if (v1 == 0) {
        // 0x00295f7c
        charge(ctx, 3);
        a1 = 1;
        jal(ctx, 0x295F80u, gen::fn_btlActionSetState_00299d60);
    }
    // 0x00295f88 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x002976D0 sub_2976D0 -- 128 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x2976D0 [btlActionUpdateStatePersona](action): when no packet of this action is queued any more, a party unit's
// action loses flag 0x400 and the action returns to the state in +20.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_2976D0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll, hg::dsll32, hg::enter, hg::jal, hg::lbu, hg::ld, hg::lhu, hg::lq,
          hg::lw, hg::sd, hg::sh, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x002976d0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    ld(a0, a0, 0);
    v0 = 0x3FFF0000;
    v0 = v0 | 0xFFFF;
    v1 = dsll32(v0, 0);
    v0 = 0xFFFF;
    v0 = dsll(v0, 16);
    v0 = v0 | 0xFFFF;
    a1 = v0 | v1;
    jal(ctx, 0x297700u, gen::fn_sub_27E390_0027e390);
    if (v0 == 0) {
        // 0x00297710
        charge(ctx, 4);
        lw(v0, s0, 48);
        lbu(v0, v0, 162);
        if (v0 == 0) {
            // 0x00297720
            charge(ctx, 3);
            lhu(v0, s0, 24);
            v0 = v0 & 0xFBFF;
            sh(v0, s0, 24);
        }
        // 0x0029772c
        charge(ctx, 4);
        a0 = s0;
        lhu(a1, s0, 20);
        jal(ctx, 0x297734u, gen::fn_btlActionSetState_00299d60);
    }
    // 0x0029773c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00299100 sub_299100 -- 100 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x299100 [btlActionUpdateStatePacket](action): when no packet of this action is queued any more, END (31).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_299100(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::dsll, hg::dsll32, hg::enter, hg::jal, hg::ld, hg::lq, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00299100
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    ld(a0, a0, 0);
    v0 = 0x3FFF0000;
    v0 = v0 | 0xFFFF;
    v1 = dsll32(v0, 0);
    v0 = 0xFFFF;
    v0 = dsll(v0, 16);
    v0 = v0 | 0xFFFF;
    a1 = v0 | v1;
    jal(ctx, 0x299130u, gen::fn_sub_27E390_0027e390);
    if (v0 == 0) {
        // 0x00299140
        charge(ctx, 4);
        a0 = s0;
        a1 = 31;
        jal(ctx, 0x299148u, gen::fn_btlActionSetState_00299d60);
    }
    // 0x00299150 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00299170 sub_299170 -- 252 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x299170 [btlActionInitStateEnd](action): the end of an actor's turn. Action flag 0x4000 asks gBtl for the end of the
// battle (gBtl+12 |= 0x400000, gBtl+24 |= 6), flag 0x200 the same with gBtl+24 |= 0x20; flag 0x100 is dropped. When
// sub_2E4330 wants an end-of-turn event, the EVENT state (20) runs the callback 0x2E43A0 and then goes to PACKET (31);
// otherwise the turn flags 0x3800 are cleared.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit: callee frames ($sp off / deeper stack)):
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_299170(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq, hg::lw, hg::sd, hg::sh,
          hg::sq, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, gp{ctx, 28}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00299170
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lhu(v0, a0, 24);
    v0 = v0 & 0x4000;
    if (v0 != 0) {
        // 0x00299190
        charge(ctx, 12);
        lw(a0, gp, -18692);  // 0x7CE3EC
        lw(v1, a0, 12);
        v0 = 0x400000;
        v0 = v1 | v0;
        sw(v0, a0, 12);
        lw(v1, gp, -18692);  // 0x7CE3EC
        lhu(v0, v1, 24);
        v0 = v0 | 0x6;
        sh(v0, v1, 24);
        lhu(v0, s0, 24);
        v0 = v0 & 0xBFFF;
        sh(v0, s0, 24);
    }
    // 0x002991c0
    charge(ctx, 7);
    lhu(v0, s0, 24);
    v0 = v0 & 0xFEFF;
    sh(v0, s0, 24);
    lhu(v0, s0, 24);
    v0 = v0 & 0x200;
    if (v0 != 0) {
        // 0x002991dc
        charge(ctx, 12);
        lw(a0, gp, -18692);  // 0x7CE3EC
        lw(v1, a0, 12);
        v0 = 0x400000;
        v0 = v1 | v0;
        sw(v0, a0, 12);
        lw(v1, gp, -18692);  // 0x7CE3EC
        lhu(v0, v1, 24);
        v0 = v0 | 0x20;
        sh(v0, v1, 24);
        lhu(v0, s0, 24);
        v0 = v0 & 0xFDFF;
        sh(v0, s0, 24);
    }
    // 0x0029920c
    charge(ctx, 5);
    a0 = s0;
    jal(ctx, 0x299210u, gen::fn_sub_2E4330_002e4330);
    if (v0 == 0) {
        // 0x0029924c
        charge(ctx, 3);
        lhu(v1, s0, 24);
        v1 = v1 & 0xC7FF;
        sh(v1, s0, 24);
    } else {
        // 0x00299220
        charge(ctx, 11);
        v0 = 0x2E0000;
        v0 = addiu(v0, 17312);  // &sub_2E43A0
        sw(v0, s0, 1184);
        v0 = 31;
        sh(v0, s0, 1180);
        a0 = s0;
        a1 = 20;
        jal(ctx, 0x29923Cu, gen::fn_btlActionSetState_00299d60);
    }
    // 0x00299258 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x00299760 sub_299760 -- 156 bytes; frame 0x30: ra sp+0x10, s0 sp+0x0 (sq)
// 0x299760 [btlActionUpdateStateEndHome](action): once the unit stopped moving, an action with +1156 == 1 queues the
// "move to" packet of the unit's current position (as START HOME does); then STANDBY (1).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_299760(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lq, hg::lw, hg::sd, hg::sq;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00299760
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a0, a0, 48);
    jal(ctx, 0x299774u, gen::fn_sub_281270_00281270);
    if (v0 == 0) {
        // 0x00299784
        charge(ctx, 4);
        lw(v1, s0, 1156);
        v0 = 1;
        if (v1 == v0) {
            // 0x00299794
            charge(ctx, 17);
            lw(a0, s0, 48);
            a1 = 0;
            a2 = 0;
            a3 = addiu(sp, 0x20);
            jal(ctx, 0x2997A4u, gen::fn_sub_27F7C0_0027f7c0);
            lw(a0, s0, 48);
            a1 = addiu(sp, 0x20);
            a2 = 0;
            jal(ctx, 0x2997B8u, gen::fn_sub_2822B0_002822b0);
            a0 = v0;
            ld(v1, s0, 0);
            sd(v1, v0, 96);
            a1 = 1;
            jal(ctx, 0x2997D0u, gen::fn_sub_27ED20_0027ed20);
        }
        // 0x002997d8
        charge(ctx, 4);
        a0 = s0;
        a1 = 1;
        jal(ctx, 0x2997E0u, gen::fn_btlActionSetState_00299d60);
    }
    // 0x002997e8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x30);
}

// 0x00299AA0 sub_299AA0 -- 84 bytes; frame 0x10: ra sp+0x0
// 0x299AA0 [btlActionInitStateExit](action): a combatant (+26 bit 0) whose unit is marked reinforced (8) loses the mark
// and the battle panel is refreshed.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_299AA0(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lw, hg::sd, hg::si, hg::sw;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00299aa0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lhu(v1, a0, 26);
    v1 = v1 & 0x1;
    if (v1 != 0) {
        // 0x00299ab8
        charge(ctx, 6);
        lw(v1, a0, 48);
        a1 = addiu(v1, 156);
        lw(a0, v1, 156);
        v1 = a0 & 0x8;
        if (v1 != 0) {
            // 0x00299ad0
            charge(ctx, 5);
            v0 = si(-9);
            v0 = a0 & v0;
            sw(v0, a1, 0);
            jal(ctx, 0x299ADCu, gen::fn_sub_1FDD40_001fdd40);
        }
    }
    // 0x00299ae4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x299D30 [btlActionUpdateStateTest](action): COMMAND (5).
void sub_299D30(EEContext& ctx, u64 action) {
    (void)action;  // passed on in $a0 untouched
    guest::enter(ctx, 9);
    Frame f(ctx, 16, 0, 0);
    S(ctx, kA1, 5);
    jal(ctx, 0x299d3cu, &rg::fn_btlActionSetState_00299d60);
}

// 0x00299DB0 btlActionSetStateWithDelay -- 116 bytes; frame 0x10: ra sp+0x0
// 0x299DB0 btlActionSetStateWithDelay(action, state, delay): with a delay (low 16 bits) the state is only recorded as
// pending (+14 / +18; btlActionUpdateAll counts +18 down); without one it is entered now, as btlActionSetState does:
// +14 = +18 = 0, +16 = the old state, +12 = state, +28 = 0, sBtlActionTbl[state].init(action) through `jalr`.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void btlActionSetStateWithDelay(EEContext& ctx) {
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jalr, hg::ld, hg::lhu, hg::lw, hg::sd, hg::sh,
          hg::sll, hg::sw;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00299db0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    v1 = a2 & 0xFFFF;
    if (v1 != 0) {
        // 0x00299e0c
        charge(ctx, 2);
        sh(a1, a0, 14);
        sh(a2, a0, 18);
    } else {
        // 0x00299dc4
        charge(ctx, 18);
        sh(zero, a0, 14);
        sh(zero, a0, 18);
        lhu(v0, a0, 12);
        sh(v0, a0, 16);
        sh(a1, a0, 12);
        sw(zero, a0, 28);
        v1 = a1 & 0xFFFF;
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v1 = sll(v0, 2);
        v0 = 0x690000;
        v0 = addiu(v0, 13328);  // &sBtlActionTbl
        v0 = addu(v0, v1);
        lw(v0, v0, 0);
        jalr(ctx, 0x299DFCu, v0.u());
    }
    // 0x00299e14 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// =====================================================================================================================
// The turn-order list
// =====================================================================================================================

// 0x29AD20 [btlOrderGetFirst](): the head of the next round's list (gBtl+644) when it has one, else this round's.
u64 sub_29AD20(EEContext& ctx) {
    guest::enter(ctx, 5);
    const u64 g = gbtl(ctx);
    S(ctx, kV1, g);
    u64 list = addr(g, kOrderListNext);
    if (lw(ctx, g, kOrderListNext) == 0) {
        guest::charge(ctx, 1);
        list = addr(g, kOrderList);
    }
    S(ctx, kA0, list);
    guest::charge(ctx, 3);
    return lw(ctx, list, 0);
}

// 0x29AD50 [btlOrderGetCount](): gBtl+592.
u64 sub_29AD50(EEContext& ctx) {
    guest::enter(ctx, 4);
    return lw(ctx, gbtl(ctx), kOrderCount);
}

namespace {
// The common head of sub_29AD60 / sub_29ADA0: slot `index` (low 16 bits) of the order list, 0 past slot 11.
u64 order_slot(EEContext& ctx, u64 index) {
    guest::enter(ctx, 4);
    const u64 i = index & 0xFFFFu;
    S(ctx, kA0, i);
    if (i >= 12) {
        guest::charge(ctx, 3);
        return 0;
    }
    guest::charge(ctx, 4);
    const u64 g = gbtl(ctx);
    S(ctx, kV1, g);
    return lw(ctx, g, kOrderList + 4u * a32(i));
}
}  // namespace

// 0x29AD60 [btlOrderGetAction](index)
u64 sub_29AD60(EEContext& ctx, u64 index) {
    const u64 a = order_slot(ctx, index);
    guest::charge(ctx, 2);
    return a;
}

// 0x29ADA0 [btlOrderGetUnit](index): the btlUnit (+48) of that slot's action, or 0.
u64 sub_29ADA0(EEContext& ctx, u64 index) {
    const u64 a = order_slot(ctx, index);
    guest::charge(ctx, 2);
    u64 unit = 0;
    if (a != 0) {
        guest::charge(ctx, 1);
        unit = lw(ctx, a, kActUnit);
    } else {
        guest::charge(ctx, 3);
    }
    guest::charge(ctx, 2);
    return unit;
}

// 0x29ADF0 [btlOrderNextContains](action): 1 when one of the 12 slots of the next round's list holds `action` (the
// slot word sign-extended against the whole register), else 0.
u64 sub_29ADF0(EEContext& ctx, u64 action) {
    guest::enter(ctx, 5);
    u64 p = addr(gbtl(ctx), kOrderListNext);
    S(ctx, kA1, p);
    S(ctx, kV1, 0);
    for (u32 i = 0;; ++i) {
        guest::charge(ctx, 3);
        S(ctx, kV0, i < 12 ? 1 : 0);
        if (i >= 12) break;
        guest::backedge(ctx);
        guest::charge(ctx, 3);
        const u64 slot = lw(ctx, p, 0);
        S(ctx, kV0, slot);
        if (slot == action) {
            guest::charge(ctx, 3 + 2);
            return 1;
        }
        guest::charge(ctx, 2);
        p = addr(p, 4);
        S(ctx, kA1, p);
        S(ctx, kV1, i + 1);
    }
    guest::charge(ctx, 1 + 2);
    return 0;
}

// 0x29B090 [btlOrderReset](): memset(gBtl+584, 0, 108): the order flags, count and both 12-slot lists.
void sub_29B090(EEContext& ctx) {
    guest::enter(ctx, 12);
    Frame f(ctx, 16, 0, 0);
    const u64 g = gbtl(ctx);
    S(ctx, kV0, g);
    S(ctx, kA0, addr(g, kOrderFlags));
    S(ctx, kA1, 0);
    S(ctx, kA2, 108);
    jal(ctx, 0x29b0a8u, &rg::fn_memset_00521408);
}

// 0x29B040 [btlOrderActivate](): gBtl+584 |= 8, then |= 1.
void sub_29B040(EEContext& ctx) {
    guest::enter(ctx, 10);
    u64 g = gbtl(ctx);
    st<u16>(ctx, g + kOrderFlags, static_cast<u16>(lhu(ctx, g, kOrderFlags) | 8u));
    g = gbtl(ctx);
    const u64 v = lhu(ctx, g, kOrderFlags) | 1u;
    st<u16>(ctx, g + kOrderFlags, static_cast<u16>(v));
    S(ctx, kA0, g);
    S(ctx, kV1, v);
}

// 0x29B070 [btlOrderDeactivate](): gBtl+584 &= ~1.
void sub_29B070(EEContext& ctx) {
    guest::enter(ctx, 6);
    const u64 g = gbtl(ctx);
    const u64 v = lhu(ctx, g, kOrderFlags) & 0xFFFEu;
    st<u16>(ctx, g + kOrderFlags, static_cast<u16>(v));
    S(ctx, kA0, g);
    S(ctx, kV1, v);
}

// 0x0029B0C0 sub_29B0C0 -- 24 bytes; leaf frame (no stack)
// 0x29B0C0 [btlActionIsNotFlag4](action): (action+24 & 4) == 0.
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void sub_29B0C0(EEContext& ctx) {
    using hg::Gpr, hg::enter, hg::lhu, hg::sltu;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x0029b0c0
    enter(ctx, 6);  // entry check point + this block's cycles
    lhu(v0, a0, 24);
    v0 = v0 & 0x4;
    v0 = sltu(0, v0);
    v0 = v0 ^ 0x1;
}

// =====================================================================================================================
// btlMain states (0x693760)
// =====================================================================================================================

void btlMainInitStateNon(EEContext& ctx) { empty_state(ctx); }
void btlMainInitStateAction(EEContext& ctx) { empty_state(ctx); }
void btlMainInitStateLose(EEContext& ctx) { empty_state(ctx); }
void btlMainInitStateTest(EEContext& ctx) { empty_state(ctx); }
void btlMainInitStateMc(EEContext& ctx) { empty_state(ctx); }

// 0x29B0F0 btlMainUpdateStateNon(): stays (0).
u64 btlMainUpdateStateNon(EEContext& ctx) {
    guest::enter(ctx, 3);
    return 0;
}

// 0x29DE10 btlMainUpdateStateMc(): stays (0).
u64 btlMainUpdateStateMc(EEContext& ctx) {
    guest::enter(ctx, 3);
    return 0;
}

// 0x29B100 btlMainInitStateInit(): sound banks 3 and 4, sub_2DCED0(0), the boss setup, sub_17B180(1).
void btlMainInitStateInit(EEContext& ctx) {
    guest::enter(ctx, 22);
    Frame f(ctx, 16, 0, 0);
    S(ctx, kA0, 3);
    S(ctx, kA1, 0);
    jal(ctx, 0x29b110u, &rg::fn_sub_2DCF80_002dcf80);
    S(ctx, kA0, 4);
    S(ctx, kA1, 0);
    jal(ctx, 0x29b120u, &rg::fn_sub_2DCF80_002dcf80);
    S(ctx, kA0, 0);
    jal(ctx, 0x29b12cu, &rg::fn_sub_2DCED0_002dced0);
    jal(ctx, 0x29b134u, &rg::fn_btlBossSetup_002f6e00);
    S(ctx, kA0, 1);
    jal(ctx, 0x29b140u, &rg::fn_sub_17B180_0017b180);
}

// 0x29B160 btlMainUpdateStateInit(): straight on to SCENE_SET (3).
u64 btlMainUpdateStateInit(EEContext& ctx) {
    guest::enter(ctx, 3);
    return 3;
}

// 0x29B170 btlMainInitStateSceneSet(): start the scene load (sub_29E390).
void btlMainInitStateSceneSet(EEContext& ctx) {
    guest::enter(ctx, 8);
    Frame f(ctx, 16, 0, 0);
    jal(ctx, 0x29b178u, &rg::fn_sub_29E390_0029e390);
}

// 0x29B190 btlMainUpdateStateSceneSet(): once the scene is ready and no packet is queued: sub_1A0410(1), the scene
// setup sub_29DFC0, then three packets queued on queue 1 -- the setup packet of kind (flag 321 ? 0 : 1), a packet whose
// byte +0 = 4 and u64 +8 = the setup packet's +88, and sub_2F9BC0's -- and on to UNIT_CREATE (4). Otherwise 0.
u64 btlMainUpdateStateSceneSet(EEContext& ctx) {
    guest::enter(ctx, 7);
    Frame f(ctx, 32, 16, 1);
    u64 next = 0;
    if (jal(ctx, 0x29b19cu, &rg::fn_sub_29E400_0029e400) != 0) {
        guest::charge(ctx, 4);
        if (jal(ctx, 0x29b1acu, &rg::fn_sub_27E410_0027e410) == 0) {
            guest::charge(ctx, 10);
            S(ctx, kA0, 1);
            jal(ctx, 0x29b1c0u, &rg::fn_sub_1A0410_001a0410);
            jal(ctx, 0x29b1c8u, &rg::fn_sub_29DFC0_0029dfc0);
            S(ctx, kA0, 321);
            u64 kind;
            if (jal(ctx, 0x29b1d4u, &rg::fn_datGetFlag_0016f190) != 0) {
                guest::charge(ctx, 3);
                kind = 0;
            } else {
                guest::charge(ctx, 1);
                kind = 1;
            }
            S(ctx, kV0, kind);
            guest::charge(ctx, 27);
            S(ctx, kA0, kind & 0xFFFFu);
            const u64 setup = jal(ctx, 0x29b1f8u, &rg::fn_sub_2E2EC0_002e2ec0);
            S(ctx, kS0, setup);
            S(ctx, kA0, setup);
            S(ctx, kA1, 1);
            jal(ctx, 0x29b20cu, &rg::fn_sub_27ED20_0027ed20);
            const u64 p2 = jal(ctx, 0x29b214u, &rg::fn_sub_2E2A10_002e2a10);
            S(ctx, kA0, p2);
            st<u8>(ctx, p2, 4);
            const u64 word = ld<u64>(ctx, setup + 88);
            S(ctx, kV1, word);
            st<u64>(ctx, p2 + 8, word);
            S(ctx, kA1, 1);
            jal(ctx, 0x29b234u, &rg::fn_sub_27ED20_0027ed20);
            S(ctx, kA0, jal(ctx, 0x29b23cu, &rg::fn_sub_2F9BC0_002f9bc0));
            S(ctx, kA1, 1);
            jal(ctx, 0x29b24cu, &rg::fn_sub_27ED20_0027ed20);
            next = 4;
            guest::charge(ctx, 5);
            return next;
        }
    }
    guest::charge(ctx, 1 + 5);
    return next;
}

// 0x29C250 btlMainInitStateStart(): with gBtl+16 bit 0, the start hook: sub_2FF2D0(3), sub_2FACC0().
void btlMainInitStateStart(EEContext& ctx) {
    guest::enter(ctx, 7);
    Frame f(ctx, 16, 0, 0);
    const u64 hook = lw(ctx, gbtl(ctx), kFlags2) & 1u;
    S(ctx, kV1, hook);
    if (hook != 0) {
        guest::charge(ctx, 5);
        S(ctx, kA0, 3);
        jal(ctx, 0x29c270u, &rg::fn_sub_2FF2D0_002ff2d0);
        jal(ctx, 0x29c278u, &rg::fn_sub_2FACC0_002facc0);
    }
    guest::charge(ctx, 4);
}

// 0x29C290 btlMainUpdateStateStart(): when the panel, the packet queues, the event system and the current action's
// event are all idle: activate the turn order, start the panel, set gBtl+12 bit 0x800 (started) and go to ACTION (7).
u64 btlMainUpdateStateStart(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 16, 0, 0);
    if (jal(ctx, 0x29c298u, &rg::fn_sub_1FECC0_001fecc0) == 0) {
        guest::charge(ctx, 4);
        if (jal(ctx, 0x29c2a8u, &rg::fn_sub_27E410_0027e410) == 0) {
            guest::charge(ctx, 4);
            if (jal(ctx, 0x29c2b8u, &rg::fn_sub_2E42C0_002e42c0) == 0) {
                guest::charge(ctx, 6);
                const u64 g = gbtl(ctx);
                S(ctx, kV0, g);
                S(ctx, kA0, lw(ctx, g, kCurrentAction));
                if (jal(ctx, 0x29c2d0u, &rg::fn_sub_2E4290_002e4290) != 0) {
                    guest::charge(ctx, 3 + 4);
                    return 0;
                }
                guest::charge(ctx, 11);
                jal(ctx, 0x29c2ecu, &rg::fn_sub_29B040_0029b040);
                jal(ctx, 0x29c2f4u, &rg::fn_sub_1FDD20_001fdd20);
                const u64 g2 = gbtl(ctx);
                S(ctx, kV1, g2);
                st<u32>(ctx, g2 + kFlags, a32(lw(ctx, g2, kFlags) | 0x800u));
                guest::charge(ctx, 4);
                return 7;
            }
        }
    }
    guest::charge(ctx, 1 + 4);
    return 0;
}

// 0x29C340 btlMainUpdateStateAction(): the turn loop runs in the action states; this state only waits for gBtl+12 bit
// 0x80 (set by btlMainCheckBattleEnd). Then: the order is deactivated, the panel closed, and for a win / escape the
// result block gBtl+3036 is filled -- on a win its flag bit 0 from sub_2D4ED0(first actor) == 1, on an escape the block
// is zeroed --, the btlUnit list is walked: living units' DatUnit ids go to +3072[], the survivor and unit counts to
// +3080 / +3084, the rounds to +3100 and the total +3092 is divided by them, +3096 = btlGetEncounterId(); every unit's
// battle-only statuses (all but 0x80080) are cleared and the result screen is created (gBtl+3368). The next state:
// win -> ENEMY DEAD (11) with gBtl+16 bit 1, else WIN (10); lose -> REVIVAL_MES (8) when someone can revive, else LOSE
// (13); escape -> FADE_OUT (14); any other outcome -> 0 (stay).
u64 btlMainUpdateStateAction(EEContext& ctx) {
    guest::enter(ctx, 10);
    Frame f(ctx, 64, 48, 3);
    const u64 over = lw(ctx, gbtl(ctx), kFlags) & 0x80u;
    S(ctx, kV0, over);
    if (over == 0) {
        guest::charge(ctx, 1 + 7);
        return 0;
    }
    guest::charge(ctx, 11);
    jal(ctx, 0x29c368u, &rg::fn_sub_29B070_0029b070);
    jal(ctx, 0x29c370u, &rg::fn_sub_1FF390_001ff390);
    jal(ctx, 0x29c378u, &rg::fn_sub_1FF350_001ff350);
    u64 g = gbtl(ctx);
    S(ctx, kV1, g);
    u64 outcome = lhu(ctx, g, kOutcome);
    S(ctx, kA0, outcome);
    S(ctx, kV0, 2);

    if (outcome != 2) {  // (outcome 2 goes straight to L_0029C564)
        guest::charge(ctx, 3);
        S(ctx, kV0, 3);
        if (outcome != 3) {
            guest::charge(ctx, 3);
            S(ctx, kV0, 1);
            if (outcome != 1) {
                guest::charge(ctx, 2 + 1 + 7);  // no outcome: stay
                S(ctx, kV0, 0);
                return 0;
            }
        }
        // --- win or escape: the result block (L_0029C3B4) ---
        guest::charge(ctx, 3);
        S(ctx, kV0, 3);
        if (outcome != 3) {
            guest::charge(ctx, 8);
            S(ctx, kA0, jal(ctx, 0x29c3c0u, &rg::fn_sub_29AD20_0029ad20));
            const u64 r = jal(ctx, 0x29c3ccu, &rg::fn_sub_2D4ED0_002d4ed0);
            S(ctx, kV1, 1);
            if (r == 1) {
                guest::charge(ctx, 6);
                const u64 g2 = gbtl(ctx);
                S(ctx, kV1, g2);
                const u64 rf = lw(ctx, g2, kResult) | 1u;
                S(ctx, kV0, rf);
                st<u32>(ctx, g2 + kResult, a32(rf));
            }
        } else {
            guest::charge(ctx, 5);
            S(ctx, kA0, addr(g, kResult));
            S(ctx, kA1, 0);
            S(ctx, kA2, 68);
            jal(ctx, 0x29c404u, &rg::fn_memset_00521408);
        }
        // the survivors (L_0029C40C)
        guest::charge(ctx, 6);
        u32 units = 0, alive = 0;
        S(ctx, kS0, 0);
        S(ctx, kS1, 0);
        g = gbtl(ctx);
        S(ctx, kV0, g);
        u64 unit = lw(ctx, g, kUnitList);
        S(ctx, kS2, unit);
        for (;;) {
            guest::charge(ctx, 2);
            if (unit == 0) break;
            guest::backedge(ctx);
            guest::charge(ctx, 6);
            S(ctx, kA0, lw(ctx, unit, kUnitDat));
            S(ctx, kA1, 0);
            if (jal(ctx, 0x29c42cu, &rg::fn_datCalcIsDead_0030b5a0) != 0) {
                guest::charge(ctx, 4);
                S(ctx, kV0, sx(units + 1));
                units = (units + 1) & 0xFFFFu;
                S(ctx, kS0, units);
            } else {
                guest::charge(ctx, 11);
                const u64 id = lhu(ctx, lw(ctx, unit, kUnitDat), 2);
                S(ctx, kA0, id);
                S(ctx, kV1, sx(alive << 1));
                const u64 g3 = gbtl(ctx);
                st<u16>(ctx, a32(g3) + (alive << 1) + kResultIds, static_cast<u16>(id));
                alive = (alive + 1) & 0xFFFFu;
                S(ctx, kS1, alive);
                S(ctx, kV0, sx(units + 1));
                units = (units + 1) & 0xFFFFu;
                S(ctx, kS0, units);
            }
            guest::charge(ctx, 1);
            unit = lw(ctx, unit, kUnitNext);
            S(ctx, kS2, unit);
        }
        guest::charge(ctx, 13);
        st<u32>(ctx, gbtl(ctx) + kResultAlive, alive);
        st<u32>(ctx, gbtl(ctx) + kResultUnits, units);
        const u64 g4 = gbtl(ctx);
        const u64 rounds = lhu(ctx, g4, kRounds);
        st<u32>(ctx, g4 + kResultRounds, a32(rounds));
        const u64 g5 = gbtl(ctx);
        S(ctx, kA0, g5);
        S(ctx, kV1, rounds);
        S(ctx, kV0, rounds);
        if (rounds != 0) {
            guest::charge(ctx, 4);
            S(ctx, kV0, lw(ctx, g5, kResultTotal));
            rt::div(ctx, kV0, kV1);  // HI/LO as the original's `div` leaves them
            rt::mflo(ctx, kV0);
            st<u32>(ctx, g5 + kResultTotal, a32(R(ctx, kV0)));
        }
        guest::charge(ctx, 8);
        const u64 extra = jal(ctx, 0x29c4c8u, &rg::fn_btlGetEncounterId_002d5550);
        const u64 g6 = gbtl(ctx);
        S(ctx, kV1, g6);
        st<u32>(ctx, g6 + kResultExtra, a32(extra));
        g = gbtl(ctx);
        S(ctx, kV0, g);
        unit = lw(ctx, g, kUnitList);
        S(ctx, kS0, unit);
        for (;;) {  // battle-only statuses off
            guest::charge(ctx, 2);
            if (unit == 0) break;
            guest::backedge(ctx);
            guest::charge(ctx, 3);
            const u64 dat = lw(ctx, unit, kUnitDat);
            S(ctx, kA0, dat);
            if (dat != 0) {
                guest::charge(ctx, 4);
                S(ctx, kV0, 0xFFFFFFFFFFF70000ull);
                S(ctx, kA1, 0xFFFFFFFFFFF7FF7Full);
                jal(ctx, 0x29c4fcu, &rg::fn_datCalcClearBadStatus_00300560);
            }
            guest::charge(ctx, 1);
            unit = lw(ctx, unit, kUnitNext);
            S(ctx, kS0, unit);
        }
        guest::charge(ctx, 11);
        g = gbtl(ctx);
        S(ctx, kV0, g);
        S(ctx, kA0, addr(g, kResult));
        const u64 task = jal(ctx, 0x29c518u, &rg::fn_sub_1F1AE0_001f1ae0);
        st<u32>(ctx, gbtl(ctx) + kResultTask, a32(task));
        g = gbtl(ctx);
        S(ctx, kV1, g);
        outcome = lhu(ctx, g, kOutcome);
        S(ctx, kA0, outcome);
        S(ctx, kV0, 1);
        if (outcome == 1) {
            guest::charge(ctx, 4);
            u64 next;
            if ((lw(ctx, g, kFlags2) & 2u) != 0) {
                guest::charge(ctx, 3);
                next = 11;
            } else {
                guest::charge(ctx, 1);
                next = 10;
            }
            guest::charge(ctx, 2 + 7);
            return next;
        }
    }
    // L_0029C564: lose -> REVIVAL_MES / LOSE; anything else here -> FADE_OUT
    guest::charge(ctx, 3);
    S(ctx, kV0, 2);
    if (outcome == 2) {
        guest::charge(ctx, 4);
        u64 next;
        if (jal(ctx, 0x29c570u, &rg::fn_sub_27D560_0027d560) != 0) {
            guest::charge(ctx, 3);
            next = 8;
        } else {
            guest::charge(ctx, 1);
            next = 13;
        }
        guest::charge(ctx, 2 + 7);
        return next;
    }
    guest::charge(ctx, 3 + 7);
    return 14;
}

// 0x29CDE0 btlMainInitStateEnemyDead(): the enemy-dead event (sub_2FB690), gBtl+12 |= 0x80000.
void btlMainInitStateEnemyDead(EEContext& ctx) {
    guest::enter(ctx, 13);
    Frame f(ctx, 16, 0, 0);
    jal(ctx, 0x29cde8u, &rg::fn_sub_2FB690_002fb690);
    const u64 g = gbtl(ctx);
    S(ctx, kA1, g);
    const u64 old = lw(ctx, g, kFlags);
    S(ctx, kA0, old);
    S(ctx, kV1, old | 0x80000u);
    st<u32>(ctx, g + kFlags, a32(old | 0x80000u));
}

// 0x29CE20 btlMainUpdateStateEnemyDead(): once the queues are empty, clear gBtl+12 bit 0x80000 and go to FADE_OUT (14)
// when the battle is over (0x80), else back to ACTION (7).
u64 btlMainUpdateStateEnemyDead(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 16, 0, 0);
    if (jal(ctx, 0x29ce28u, &rg::fn_sub_27E410_0027e410) != 0) {
        guest::charge(ctx, 1 + 4);
        return 0;
    }
    guest::charge(ctx, 11);
    const u64 g = gbtl(ctx);
    S(ctx, kA0, g);
    const u64 old = lw(ctx, g, kFlags);
    S(ctx, kV1, old);
    st<u32>(ctx, g + kFlags, a32(old & 0xFFFFFFFFFFF7FFFFull));
    const bool over = (lw(ctx, gbtl(ctx), kFlags) & 0x80u) != 0;
    u64 next;
    if (over) {
        guest::charge(ctx, 3);
        next = 14;
    } else {
        guest::charge(ctx, 1);
        next = 7;
    }
    guest::charge(ctx, 2 + 4);
    return next;
}

// 0x0029D0D0 btlMainUpdateStateWin -- 276 bytes; frame 0x20: ra sp+0x10, s0 sp+0x0 (sq)
// 0x29D0D0 btlMainUpdateStateWin(st = &gBtl->state): after +12 + +14 frames in the state, a pad press (0x10 of the
// words 0x7E094C / 0x7E0956 or 0x40 of 0x7E094E / 0x7E0958) starts the victory sound once (+20 = 1: a sound packet with
// +74 = 12 on queue 1, sub_2DDBE0). Once the queues are empty and the sound started, or +12 + +16 frames passed:
// CONDITION (12).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void btlMainUpdateStateWin(EEContext& ctx) {
    namespace gen = ::p3fes::recomp_gen;
    using hg::Gpr, hg::addiu, hg::addu, hg::charge, hg::enter, hg::jal, hg::ld, hg::lhu, hg::lq, hg::lw, hg::sd,
          hg::sh, hg::slt, hg::sq, hg::sw;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0029d0d0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(ra, sp, 0x10);
    sq(s0, sp, 0x0);
    s0 = a0;
    lw(a1, a0, 8);
    lhu(v1, a0, 12);
    lhu(v0, a0, 14);
    v0 = addu(v1, v0);
    at = slt(v0, a1);
    if (at != 0) {
        // 0x0029d0fc
        charge(ctx, 3);
        lw(v0, s0, 20);
        if (v0 == 0) {
            // 0x0029d108
            charge(ctx, 5);
            v0 = 0x7E0000;
            lhu(v0, v0, 2380);  // 0x7E094C
            v0 = v0 & 0x10;
            if (v0 == 0) {
                // 0x0029d11c
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v0, v0, 2390);  // 0x7E0956
                v0 = v0 & 0x10;
                if (v0 != 0) {
                    goto L_0029d158;
                }
                // 0x0029d130
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v0, v0, 2382);  // gPadFlags
                v0 = v0 & 0x40;
                if (v0 != 0) {
                    goto L_0029d158;
                }
                // 0x0029d144
                charge(ctx, 5);
                v0 = 0x7E0000;
                lhu(v0, v0, 2392);  // 0x7E0958
                v0 = v0 & 0x40;
                if (v0 != 0) {
                    goto L_0029d158;
                }
                goto L_0029d188;
            }
        L_0029d158:
            charge(ctx, 12);
            jal(ctx, 0x29D158u, gen::fn_sub_2DB890_002db890);
            a0 = v0;
            v1 = 12;
            sh(v1, v0, 74);
            a1 = 1;
            jal(ctx, 0x29D170u, gen::fn_sub_27ED20_0027ed20);
            jal(ctx, 0x29D178u, gen::fn_sub_2DDBE0_002ddbe0);
            v0 = 1;
            sw(v0, s0, 20);
        }
    }
L_0029d188:
    charge(ctx, 4);
    jal(ctx, 0x29D188u, gen::fn_sub_27E410_0027e410);
    if (v0 == 0) {
        // 0x0029d198
        charge(ctx, 3);
        lw(v0, s0, 20);
        if (v0 == 0) {
            // 0x0029d1a4
            charge(ctx, 7);
            lw(a0, s0, 8);
            lhu(v1, s0, 12);
            lhu(v0, s0, 16);
            v0 = addu(v1, v0);
            v0 = slt(a0, v0);
            if (v0 != 0) {
                goto L_0029d1cc;
            }
            goto L_0029d1c0;
        }
    L_0029d1c0:
        charge(ctx, 3);
        v0 = 12;
        // 0x0029d1d0 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(ra, sp, 0x10);
        lq(s0, sp, 0x0);
        sp = addiu(sp, 0x20);
        return;
    }
L_0029d1cc:
    charge(ctx, 1);
    v0 = 0;
    // 0x0029d1d0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    lq(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x29D6E0 btlMainUpdateStateCondition(): once the queues are empty, FADE_OUT (14).
u64 btlMainUpdateStateCondition(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 16, 0, 0);
    if (jal(ctx, 0x29d6e8u, &rg::fn_sub_27E410_0027e410) != 0) {
        guest::charge(ctx, 1 + 4);
        return 0;
    }
    guest::charge(ctx, 3 + 4);
    return 14;
}

// 0x0029D730 btlMainUpdateStateLose -- 40 bytes; leaf frame (no stack)
// 0x29D730 btlMainUpdateStateLose(st = &gBtl->state): after 31 frames, FADE_OUT (14).
// Register-faithful since 2026-10-21 (faithfulness audit, tools/ours/audit):
// it found: faults only (differs only on runs that stop).
// p3fes_handgen's body, statement for statement the original's; the notes above come from the earlier hand version.
void btlMainUpdateStateLose(EEContext& ctx) {
    using hg::Gpr, hg::charge, hg::enter, hg::lw, hg::slti;
    Gpr at{ctx, 1}, v0{ctx, 2}, a0{ctx, 4};
    // 0x0029d730
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v0, a0, 8);
    at = slti(v0, 31);
    if (at != 0) {
        // 0x0029d74c
        charge(ctx, 1);
        v0 = 0;
    } else {
        // 0x0029d740
        charge(ctx, 3);
        v0 = 14;
    }
    // 0x0029d750 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x29D760 btlMainInitStateFadeOut(): gBtl+12 loses 0x800 (started). A lost battle fades the screen (sub_108570, kind 8,
// colour 0/0/0, 30 frames); otherwise, when the result screen is wanted (0x400), the result screen's fade.
void btlMainInitStateFadeOut(EEContext& ctx) {
    guest::enter(ctx, 12);
    Frame f(ctx, 16, 0, 0);
    u64 g = gbtl(ctx);
    S(ctx, kA1, g);
    const u64 old = lw(ctx, g, kFlags);
    st<u32>(ctx, g + kFlags, a32(old & sx(static_cast<u32>(-2049))));
    g = gbtl(ctx);
    S(ctx, kA1, g);
    const u64 outcome = lhu(ctx, g, kOutcome);
    S(ctx, kA0, outcome);
    S(ctx, kV1, 2);
    if (outcome == 2) {
        guest::charge(ctx, 13);
        jal(ctx, 0x29d7b4u, &rg::fn_sub_108570_00108570);
        S(ctx, kA0, 8);
        jal(ctx, 0x29d7c0u, &rg::fn_sub_108670_00108670);
        S(ctx, kA0, 0);
        S(ctx, kA1, 0);
        S(ctx, kA2, 0);
        jal(ctx, 0x29d7d4u, &rg::fn_sub_108680_00108680);
        S(ctx, kA0, 30);
        jal(ctx, 0x29d7e0u, &rg::fn_sub_1086A0_001086a0);
    } else {
        guest::charge(ctx, 4);
        const u64 wanted = lw(ctx, g, kFlags) & 0x400u;
        S(ctx, kV1, wanted);
        if (wanted != 0) {
            guest::charge(ctx, 5);
            S(ctx, kA0, lw(ctx, g, kResultTask));
            jal(ctx, 0x29d7a4u, &rg::fn_sub_1F1B20_001f1b20);
        }
    }
    guest::charge(ctx, 4);
}

// 0x29D800 btlMainUpdateStateFadeOut(): END (15) once the fade is over (lose: the screen fade's state 1; else the
// result screen's fade no longer busy).
u64 btlMainUpdateStateFadeOut(EEContext& ctx) {
    guest::enter(ctx, 7);
    Frame f(ctx, 16, 0, 0);
    const u64 g = gbtl(ctx);
    S(ctx, kA0, g);
    const u64 outcome = lhu(ctx, g, kOutcome);
    S(ctx, kV1, outcome);
    S(ctx, kV0, 2);
    bool done;
    if (outcome == 2) {
        guest::charge(ctx, 5);
        const u64 s = jal(ctx, 0x29d83cu, &rg::fn_sub_108710_00108710);
        S(ctx, kV1, 1);
        done = s == 1;
    } else {
        guest::charge(ctx, 5);
        S(ctx, kA0, lw(ctx, g, kResultTask));
        done = jal(ctx, 0x29d820u, &rg::fn_sub_1F1B40_001f1b40) == 0;
    }
    if (done) {
        guest::charge(ctx, 3 + 4);
        return 15;
    }
    guest::charge(ctx, 1 + 4);
    return 0;
}

// 0x29DB60 btlMainUpdateStateEnd(): once every action is gone: release the scene, destroy the task gBtl+3372 with its
// hierarchy, sub_2BFC50(1); then RESULT (16) when the result screen is wanted and the battle was not lost, else EXIT
// (17).
u64 btlMainUpdateStateEnd(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 16, 0, 0);
    const u64 head = lw(ctx, gbtl(ctx), kActionList);
    S(ctx, kV0, head);
    if (head != 0) {
        guest::charge(ctx, 3 + 4);
        return 0;
    }
    guest::charge(ctx, 14);
    jal(ctx, 0x29db84u, &rg::fn_sub_29E3C0_0029e3c0);
    const u64 g = gbtl(ctx);
    S(ctx, kV0, g);
    S(ctx, kA0, lw(ctx, g, kEndTask));
    jal(ctx, 0x29db94u, &rg::fn_kwlnTaskDestroyWithHierarchy_00195020);
    S(ctx, kA0, 1);
    jal(ctx, 0x29dba0u, &rg::fn_sub_2BFC50_002bfc50);
    const u64 g2 = gbtl(ctx);
    S(ctx, kV1, g2);
    const u64 wanted = lw(ctx, g2, kFlags) & 0x400u;
    S(ctx, kV0, wanted);
    if (wanted != 0) {
        guest::charge(ctx, 4);
        const u64 outcome = lhu(ctx, g2, kOutcome);
        S(ctx, kV1, outcome);
        S(ctx, kV0, 2);
        if (outcome != 2) {
            guest::charge(ctx, 3 + 4);
            return 16;
        }
    }
    guest::charge(ctx, 1 + 4);
    return 17;
}

// 0x29DBF0 btlMainInitStateResult(): open the result screen (sub_1F1B60(gBtl+3368)).
void btlMainInitStateResult(EEContext& ctx) {
    guest::enter(ctx, 10);
    Frame f(ctx, 16, 0, 0);
    const u64 g = gbtl(ctx);
    S(ctx, kV0, g);
    S(ctx, kA0, lw(ctx, g, kResultTask));
    jal(ctx, 0x29dc00u, &rg::fn_sub_1F1B60_001f1b60);
}

// 0x29DC20 btlMainUpdateStateResult(): the field return starts once (gBtl+12 bit 0x8000000) as soon as the result screen
// asks for it; when the result screen is done it is closed (gBtl+3368 = 0), a test battle with the result wanted fades
// back in, and EXIT (17) follows. Otherwise 0.
u64 btlMainUpdateStateResult(EEContext& ctx) {
    guest::enter(ctx, 8);
    Frame f(ctx, 16, 0, 0);
    u64 g = gbtl(ctx);
    const u64 fl = lw(ctx, g, kFlags);
    S(ctx, kV1, fl);
    S(ctx, kV0, fl & 0x8000000u);
    if ((fl & 0x8000000u) == 0) {
        guest::charge(ctx, 5);
        const u64 r = jal(ctx, 0x29dc40u, &rg::fn_sub_1F1F40_001f1f40);
        S(ctx, kV1, 1);
        if (r == 1) {
            guest::charge(ctx, 7);
            jal(ctx, 0x29dc54u, &rg::fn_sub_1B0710_001b0710);
            g = gbtl(ctx);
            S(ctx, kA0, g);
            const u64 old = lw(ctx, g, kFlags);
            S(ctx, kV1, old);
            S(ctx, kV0, old | 0x8000000u);
            st<u32>(ctx, g + kFlags, a32(old | 0x8000000u));
        }
    }
    guest::charge(ctx, 6);
    g = gbtl(ctx);
    S(ctx, kV0, g);
    S(ctx, kA0, lw(ctx, g, kResultTask));
    if (jal(ctx, 0x29dc78u, &rg::fn_sub_1F1B00_001f1b00) != 0) {
        guest::charge(ctx, 3 + 4);
        return 0;
    }
    guest::charge(ctx, 11);
    g = gbtl(ctx);
    S(ctx, kV0, g);
    S(ctx, kA0, lw(ctx, g, kResultTask));
    jal(ctx, 0x29dc9cu, &rg::fn_sub_1F1C20_001f1c20);
    g = gbtl(ctx);
    S(ctx, kV0, g);
    st<u32>(ctx, g + kResultTask, 0);
    g = gbtl(ctx);
    S(ctx, kA0, g);
    const u64 test = lbu(ctx, g, kTestBattle);
    S(ctx, kV1, test);
    S(ctx, kV0, 1);
    if (test == 1) {
        guest::charge(ctx, 4);
        const u64 wanted = lw(ctx, g, kFlags) & 0x400u;
        S(ctx, kV0, wanted);
        if (wanted != 0) {
            guest::charge(ctx, 2);
            jal(ctx, 0x29dcd0u, &rg::fn_sub_1085C0_001085c0);
        }
    }
    guest::charge(ctx, 1 + 4);
    return 17;
}

// 0x29DCF0 btlMainInitStateExit(): tell the running packets to finish; start the field return once (0x8000000).
void btlMainInitStateExit(EEContext& ctx) {
    guest::enter(ctx, 10);
    Frame f(ctx, 16, 0, 0);
    jal(ctx, 0x29dcf8u, &rg::fn_sub_27E4D0_0027e4d0);
    u64 g = gbtl(ctx);
    S(ctx, kV1, g);
    u64 fl = lw(ctx, g, kFlags);
    S(ctx, kA0, fl);
    S(ctx, kV1, fl & 0x8000000u);
    if ((fl & 0x8000000u) == 0) {
        guest::charge(ctx, 7);
        jal(ctx, 0x29dd18u, &rg::fn_sub_1B0710_001b0710);
        g = gbtl(ctx);
        S(ctx, kA1, g);
        fl = lw(ctx, g, kFlags);
        S(ctx, kA0, fl);
        S(ctx, kV1, fl | 0x8000000u);
        st<u32>(ctx, g + kFlags, a32(fl | 0x8000000u));
    }
    guest::charge(ctx, 4);
}

// 0x29DD50 btlMainUpdateStateExit(): once the queues are empty and the sound idle, release the sound and clear gBtl+12
// bit 0 (running): the next btlUpdateTask tears the battle tree down. Always 0.
u64 btlMainUpdateStateExit(EEContext& ctx) {
    guest::enter(ctx, 6);
    Frame f(ctx, 16, 0, 0);
    if (jal(ctx, 0x29dd58u, &rg::fn_sub_27E410_0027e410) == 0) {
        guest::charge(ctx, 4);
        if (jal(ctx, 0x29dd68u, &rg::fn_btlSupportIsBusy_002dba60) == 0) {
            guest::charge(ctx, 7);
            jal(ctx, 0x29dd78u, &rg::fn_sub_2DCF10_002dcf10);
            const u64 g = gbtl(ctx);
            S(ctx, kA0, g);
            const u64 old = lw(ctx, g, kFlags);
            S(ctx, kV1, old);
            st<u32>(ctx, g + kFlags, a32(old & sx(static_cast<u32>(-2))));
        }
    }
    guest::charge(ctx, 5);
    return 0;
}

// 0x29DDC0 btlMainUpdateStateTest(): a system sound (0, 0, 3, 0), sub_2FF260(0), then INIT (2).
u64 btlMainUpdateStateTest(EEContext& ctx) {
    guest::enter(ctx, 16);
    Frame f(ctx, 16, 0, 0);
    S(ctx, kA0, 0);
    S(ctx, kA1, 0);
    S(ctx, kA2, 3);
    S(ctx, kA3, 0);
    jal(ctx, 0x29ddd8u, &rg::fn_sub_10A4E0_0010a4e0);
    S(ctx, kA0, 0);
    jal(ctx, 0x29dde4u, &rg::fn_sub_2FF260_002ff260);
    return 2;
}

// 0x29DF40 btlMainSetStateNon(): state = NON (1), frames = 0, the NON row's init through `jalr` ($a0 = &gBtl->state),
// then the pending state cleared.
void btlMainSetStateNon(EEContext& ctx) {
    guest::enter(ctx, 25);
    Frame f(ctx, 16, 0, 0);
    S(ctx, kV1, 1);
    st<u32>(ctx, gbtl(ctx) + kMainState, 1);
    st<u32>(ctx, gbtl(ctx) + kMainFrames, 0);
    const u64 g = gbtl(ctx);
    S(ctx, kA0, addr(g, kMainState));
    const u32 s = ld<u32>(ctx, g + kMainState);
    S(ctx, kV1, sx((s * 3u) << 2));
    jalr_to(ctx, 0x29df84u, ld<u32>(ctx, kMainStateTbl + ((s * 3u) << 2)));
    const u64 g2 = gbtl(ctx);
    S(ctx, kV1, g2);
    st<u32>(ctx, g2 + kMainPending, 0);
}

// 0x29C5D0 btlMainInitStateRevivalMes(): the "revive?" question: the yes/no window (setup 0x6935C0), a camera packet
// (3, 4095) tagged with the current action's uid and message 36 queued on queue 0.
void btlMainInitStateRevivalMes(EEContext& ctx) {
    guest::enter(ctx, 41);
    Frame f(ctx, 32, 16, 1);
    const u64 cur = lw(ctx, gbtl(ctx), kCurrentAction);
    S(ctx, kV0, gbtl(ctx));
    S(ctx, kS0, cur);
    S(ctx, kA0, 0x6935C0u);
    jal(ctx, 0x29c5ecu, &rg::fn_sub_3C72D0_003c72d0);
    S(ctx, kA0, 1);
    jal(ctx, 0x29c5f8u, &rg::fn_msgWinRequestMessage_003c7430);
    S(ctx, kA0, 0);
    jal(ctx, 0x29c604u, &rg::fn_msgWinSetType_003c7560);
    S(ctx, kA0, 0);
    jal(ctx, 0x29c610u, &rg::fn_sub_3C74E0_003c74e0);
    S(ctx, kA0, 3);
    S(ctx, kA1, 4095);
    const u64 cam = jal(ctx, 0x29c620u, &rg::fn_sub_2B8D60_002b8d60);
    S(ctx, kA0, cam);
    const u64 uid = ld<u64>(ctx, cur + kActUid);
    S(ctx, kV1, uid);
    st<u64>(ctx, cam + 96, uid);
    S(ctx, kA1, 0);
    jal(ctx, 0x29c638u, &rg::fn_sub_27ED20_0027ed20);
    S(ctx, kA0, 0);
    S(ctx, kA1, 36);
    S(ctx, kA0, jal(ctx, 0x29c648u, &rg::fn_sub_2A3B40_002a3b40));
    S(ctx, kA1, 0);
    jal(ctx, 0x29c658u, &rg::fn_sub_27ED20_0027ed20);
}

// 0x29C680 btlMainUpdateStateRevivalMes(): while the window is open, 0; on "yes" (answer 0) the panel step and REVIVAL
// (9); on "no" gBtl+12 loses 0x800000 and the battle goes back to ACTION (7).
u64 btlMainUpdateStateRevivalMes(EEContext& ctx) {
    guest::enter(ctx, 8);
    Frame f(ctx, 16, 0, 0);
    jal(ctx, 0x29c688u, &rg::fn_sub_3C7B90_003c7b90);
    if (jal(ctx, 0x29c690u, &rg::fn_sub_3C7850_003c7850) != 0) {
        guest::charge(ctx, 1 + 4);
        return 0;
    }
    guest::charge(ctx, 4);
    if (jal(ctx, 0x29c6a0u, &rg::fn_msgWinLastSelection_003c7610) == 0) {
        guest::charge(ctx, 5);
        jal(ctx, 0x29c6b0u, &rg::fn_sub_1FF3B0_001ff3b0);
        guest::charge(ctx, 4);
        return 9;
    }
    guest::charge(ctx, 9);
    const u64 g = gbtl(ctx);
    S(ctx, kA0, g);
    const u64 old = lw(ctx, g, kFlags);
    S(ctx, kV1, old);
    st<u32>(ctx, g + kFlags, a32(old & 0xFFFFFFFFFF7FFFFFull));
    guest::charge(ctx, 4);
    return 7;
}

}  // namespace p3fes::game

// --- the recompiled program's entry points ---------------------------------------------------------------------
// Arguments are the whole 64-bit registers; results go to $v0. The void functions leave $v0 as their bodies left it.
namespace p3fes::recomp_gen {
using namespace p3fes::game;
namespace {
u64 a(const p3fes::EEContext& ctx, unsigned i) { return ee::core::gpr64(ctx, GPR_A0 + i); }
void v0(p3fes::EEContext& ctx, u64 v) { ee::core::set_gpr64(ctx, GPR_V0, v); }
}  // namespace
void fn_btlStart_0027d1d0(p3fes::EEContext& ctx) { v0(ctx, btlStart(ctx, a(ctx, 0))); }
void fn_sub_27D560_0027d560(p3fes::EEContext& ctx) { v0(ctx, sub_27D560(ctx)); }
void fn_sub_29B090_0029b090(p3fes::EEContext& ctx) { sub_29B090(ctx); }
void fn_btlUpdateTask_0027cc30(p3fes::EEContext& ctx) { v0(ctx, btlUpdateTask(ctx)); }
void fn_btlDestroyTask_0027cdf0(p3fes::EEContext& ctx) { btlDestroyTask(ctx); }
void fn_sub_27CE10_0027ce10(p3fes::EEContext& ctx) { sub_27CE10(ctx); }
void fn_sub_27E410_0027e410(p3fes::EEContext& ctx) { v0(ctx, sub_27E410(ctx)); }
void fn_sub_27E470_0027e470(p3fes::EEContext& ctx) { v0(ctx, sub_27E470(ctx, a(ctx, 0))); }
void fn_sub_27E4D0_0027e4d0(p3fes::EEContext& ctx) { sub_27E4D0(ctx); }
void fn_sub_28A990_0028a990(p3fes::EEContext& ctx) { sub_28A990(ctx); }
void fn_sub_28A9A0_0028a9a0(p3fes::EEContext& ctx) { sub_28A9A0(ctx); }
void fn_sub_28A9B0_0028a9b0(p3fes::EEContext& ctx) { sub_28A9B0(ctx); }
void fn_sub_28D070_0028d070(p3fes::EEContext& ctx) { sub_28D070(ctx); }
void fn_sub_28DBE0_0028dbe0(p3fes::EEContext& ctx) { sub_28DBE0(ctx); }
void fn_sub_28EB40_0028eb40(p3fes::EEContext& ctx) { sub_28EB40(ctx); }
void fn_sub_290BD0_00290bd0(p3fes::EEContext& ctx) { sub_290BD0(ctx); }
void fn_sub_295150_00295150(p3fes::EEContext& ctx) { sub_295150(ctx); }
void fn_sub_295B90_00295b90(p3fes::EEContext& ctx) { sub_295B90(ctx); }
void fn_sub_295BF0_00295bf0(p3fes::EEContext& ctx) { sub_295BF0(ctx); }
void fn_sub_296310_00296310(p3fes::EEContext& ctx) { sub_296310(ctx); }
void fn_sub_296880_00296880(p3fes::EEContext& ctx) { sub_296880(ctx); }
void fn_sub_297750_00297750(p3fes::EEContext& ctx) { sub_297750(ctx); }
void fn_sub_2990F0_002990f0(p3fes::EEContext& ctx) { sub_2990F0(ctx); }
void fn_sub_299D20_00299d20(p3fes::EEContext& ctx) { sub_299D20(ctx); }
void fn_sub_299D30_00299d30(p3fes::EEContext& ctx) { sub_299D30(ctx, a(ctx, 0)); }
void fn_sub_29AD20_0029ad20(p3fes::EEContext& ctx) { v0(ctx, sub_29AD20(ctx)); }
void fn_sub_29AD50_0029ad50(p3fes::EEContext& ctx) { v0(ctx, sub_29AD50(ctx)); }
void fn_sub_29AD60_0029ad60(p3fes::EEContext& ctx) { v0(ctx, sub_29AD60(ctx, a(ctx, 0))); }
void fn_sub_29ADA0_0029ada0(p3fes::EEContext& ctx) { v0(ctx, sub_29ADA0(ctx, a(ctx, 0))); }
void fn_sub_29ADF0_0029adf0(p3fes::EEContext& ctx) { v0(ctx, sub_29ADF0(ctx, a(ctx, 0))); }
void fn_sub_29B040_0029b040(p3fes::EEContext& ctx) { sub_29B040(ctx); }
void fn_sub_29B070_0029b070(p3fes::EEContext& ctx) { sub_29B070(ctx); }
void fn_btlMainInitStateNon_0029b0e0(p3fes::EEContext& ctx) { btlMainInitStateNon(ctx); }
void fn_btlMainUpdateStateNon_0029b0f0(p3fes::EEContext& ctx) { v0(ctx, btlMainUpdateStateNon(ctx)); }
void fn_btlMainInitStateInit_0029b100(p3fes::EEContext& ctx) { btlMainInitStateInit(ctx); }
void fn_btlMainUpdateStateInit_0029b160(p3fes::EEContext& ctx) { v0(ctx, btlMainUpdateStateInit(ctx)); }
void fn_btlMainInitStateSceneSet_0029b170(p3fes::EEContext& ctx) { btlMainInitStateSceneSet(ctx); }
void fn_btlMainUpdateStateSceneSet_0029b190(p3fes::EEContext& ctx) { v0(ctx, btlMainUpdateStateSceneSet(ctx)); }
void fn_btlMainInitStateStart_0029c250(p3fes::EEContext& ctx) { btlMainInitStateStart(ctx); }
void fn_btlMainUpdateStateStart_0029c290(p3fes::EEContext& ctx) { v0(ctx, btlMainUpdateStateStart(ctx)); }
void fn_btlMainInitStateAction_0029c330(p3fes::EEContext& ctx) { btlMainInitStateAction(ctx); }
void fn_btlMainUpdateStateAction_0029c340(p3fes::EEContext& ctx) { v0(ctx, btlMainUpdateStateAction(ctx)); }
void fn_btlMainInitStateRevivalMes_0029c5d0(p3fes::EEContext& ctx) { btlMainInitStateRevivalMes(ctx); }
void fn_btlMainUpdateStateRevivalMes_0029c680(p3fes::EEContext& ctx) { v0(ctx, btlMainUpdateStateRevivalMes(ctx)); }
void fn_btlMainInitStateEnemyDead_0029cde0(p3fes::EEContext& ctx) { btlMainInitStateEnemyDead(ctx); }
void fn_btlMainUpdateStateEnemyDead_0029ce20(p3fes::EEContext& ctx) { v0(ctx, btlMainUpdateStateEnemyDead(ctx)); }
void fn_btlMainUpdateStateCondition_0029d6e0(p3fes::EEContext& ctx) { v0(ctx, btlMainUpdateStateCondition(ctx)); }
void fn_btlMainInitStateLose_0029d720(p3fes::EEContext& ctx) { btlMainInitStateLose(ctx); }
void fn_btlMainInitStateFadeOut_0029d760(p3fes::EEContext& ctx) { btlMainInitStateFadeOut(ctx); }
void fn_btlMainUpdateStateFadeOut_0029d800(p3fes::EEContext& ctx) { v0(ctx, btlMainUpdateStateFadeOut(ctx)); }
void fn_btlMainUpdateStateEnd_0029db60(p3fes::EEContext& ctx) { v0(ctx, btlMainUpdateStateEnd(ctx)); }
void fn_btlMainInitStateResult_0029dbf0(p3fes::EEContext& ctx) { btlMainInitStateResult(ctx); }
void fn_btlMainUpdateStateResult_0029dc20(p3fes::EEContext& ctx) { v0(ctx, btlMainUpdateStateResult(ctx)); }
void fn_btlMainInitStateExit_0029dcf0(p3fes::EEContext& ctx) { btlMainInitStateExit(ctx); }
void fn_btlMainUpdateStateExit_0029dd50(p3fes::EEContext& ctx) { v0(ctx, btlMainUpdateStateExit(ctx)); }
void fn_btlMainInitStateTest_0029ddb0(p3fes::EEContext& ctx) { btlMainInitStateTest(ctx); }
void fn_btlMainUpdateStateTest_0029ddc0(p3fes::EEContext& ctx) { v0(ctx, btlMainUpdateStateTest(ctx)); }
void fn_btlMainInitStateMc_0029de00(p3fes::EEContext& ctx) { btlMainInitStateMc(ctx); }
void fn_btlMainUpdateStateMc_0029de10(p3fes::EEContext& ctx) { v0(ctx, btlMainUpdateStateMc(ctx)); }
void fn_btlMainSetStateNon_0029df40(p3fes::EEContext& ctx) { btlMainSetStateNon(ctx); }
}  // namespace p3fes::recomp_gen
