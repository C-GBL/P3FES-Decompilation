// Phase 5 slice battle_fx: the battle effect packets and the command effects, 0x2B7060-0x2C006C
// (docs/ANALYSIS/27_unmapped_bands.md section 2, docs/ANALYSIS/queue_bands.txt `# === slice battle_fx`). The battle
// gate's fight runs them through tables: packet callbacks, the BED position callbacks, the command lists.
//
// The pieces (game/src/battle/battle_fx.cpp has one comment per function):
//   * Effect packets. sub_27EC10(kind, payload size) (kept recompiled: it allocates through the RW heap pointer
//     0x960178) returns a packet whose payload sits at +144 (pointer at +120); a creator here fills the payload and
//     installs the callbacks: +104 start, +108 update (returns 1 to keep running, 0 when done), +112 end, +116 the
//     finished test. Kinds 0xB00..0xB04 move units (approach, keep apart, face the target, back home, scatter);
//     0x301 / 0x302 / 0x400 show a .BED effect on one or two units; 0x306..0x30A / 0x500..0x50D are battle events (the
//     screen fade, the HP / SP gauges, waits on the command-menu code). A start / end pair usually raises / drops the
//     unit's busy count (u16 +160 of the unit's model record).
//   * .BED effects. A BED header (1584 bytes: two 788-byte groups of 24-byte entries at +28) is bound to its file
//     (sub_2B90D0: each entry becomes an effect object, sub_324BD0 / sub_325920) and released again (sub_2B9220); an
//     effect instance (sub_2BA3A0 update / sub_2BA900 draw) places each entry through one of the 13 position callbacks
//     of table 0x696490 (`jalr`; sub_2B99D0 .. sub_2BA0D0, most of them funnelling into the solver sub_2B96F0) and
//     orients it (sub_2BA0F0, the jump table 0x7B7D00).
//   * Effect slots: a unit's pool of 48 slots (in-use mask +192) handing out the records gBtl's list +400 updates and
//     draws every frame (sub_2BB3A0: alpha fades, the instance / effect object / model of the slot).
//   * The command lists and tasks: the debug command lists "Attack" / "Skill" / "Item" / "Escape" / "Wait" (records
//     0x696E10.., each {s16 x, y, first, cursor, width, rows, count; init +16, input +20, draw +24, parent +32, child
//     +36}), and the tasks "battle_command_calc" (btlCommand_UpdateBattleCommandCalcTask) / "battle_command_draw" (btlCommand_UpdateBattleCommandDrawTask) that run them -- or,
//     outside the debug mode, take the choice of the real command menu (sub_1FDDF0 / sub_1FDF10, battle_cmd_menu) into
//     the acting unit's command words +108 / +110 / +112 / +116.
//   * The target lists (sub_2BFCB0 / sub_2BFF60, from SKILL.TBL gp-18680), the icon / colour of an affinity bit
//     (sub_2BBFA0 / sub_2BC0E0) and the HP / SP gauges' draw (sub_2BCE10 / sub_2BF9B0).
// gBtl is the battle work at gp-18692 (battle_calc2.h); a unit's model record holds its position +4..+12, scale +44,
// size +140 / +144, side +162 (0 the party, 1 the enemies), the BED pools +2556, the gauges +2564 / +2584, the stats
// record +2604 and the list links +2608 / +2612.
//
// Not taken (they stay recompiled): sub_2BAA20 (the 0x400 packet's start: loads the BED through H_Cdvd_Request) and
// sub_2BC420 (the 0x306 packet's start: H_Cdvd_Destroy) -- file I/O; and the slice's skip-class functions (printf: the
// formation sub_2B7060 / sub_2B71E0, sub_2BB6F0; the heap: sub_2B8F90 .. btlCommand_CreateBattleCommandCalcTasks, queue_bands.txt).
//
// Register contract (docs/PHASE5_AGENT_BRIEF.md, waves 6, 7 and 10): the packet callbacks, the position callbacks and
// the task updates run through `jalr`, every check point can preempt the thread (the kernel then saves the whole
// register file in guest memory), and callers read registers these functions leave behind. So the bodies are
// register-faithful: at every check point, call and return each GPR (128 bits), HI/LO, FPR, ACC and FCR31 holds what
// the original holds there, the prologues write the original spills and the stack buffers the original hands to its
// callees, and the `jalr`s keep the original frame and $ra. The bodies work on the guest registers directly (the Cpu
// view in src/battle/battle_fx.cpp, one named variable per register); the typed functions below load their arguments
// into $a0.. ($t0.. for the fifth and later) and return $v0 as the body leaves it.
//
// Names: every function keeps its symbols/functions.json name (sub_* / nullsub_*); a bracketed role is a proposal
// (symbols/deltas/bands.sym names the two tasks). The recompiled program's entry points (`fn_<name>_<addr8>`) are
// defined in src/battle/battle_fx.cpp.
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/ee_context.h"

namespace p3fes::game {


// --- unit movement packets (btlFormation.c's neighbours: kinds 0xB00..0xB04, payload at packet +120) -----------------
u32 sub_2B77C0(EEContext& ctx, u32 a0);  // [formation slot]
u32 sub_2B79E0(EEContext& ctx, u32 a0);  // [approach update]
u32 sub_2B7BD0(EEContext& ctx, u32 a0, u32 a1, u32 a2);  // [create approach]
u32 sub_2B7C50(EEContext& ctx, u32 a0);  // [spread update]
u32 sub_2B8900(EEContext& ctx, u32 a0, u32 a1, u32 a2);  // [create spread]
u32 sub_2B8970(EEContext& ctx, u32 a0);  // [face start]
u32 sub_2B8990(EEContext& ctx, u32 a0);  // [face update]
u32 sub_2B8B50(EEContext& ctx, u32 a0);  // [face end]
u32 sub_2B8B70(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3);  // [create face]
u32 sub_2B8C00(EEContext& ctx, u32 a0);  // [home update]
u32 sub_2B8D60(EEContext& ctx, u32 a0, u32 a1);  // [create home]
u32 sub_2B8DC0(EEContext& ctx, u32 a0);  // [scatter update]
u32 sub_2B8F40(EEContext& ctx, u32 a0);  // [create scatter]

// --- .BED effect data and effect instances (BED header: two 788-byte groups of 24-byte entries at +28, flags +1584,
// references +1586, the file +1588) -----------------------------------------------------------------------------------
u32 sub_2B90D0(EEContext& ctx, u32 a0, u32 a1);  // [bind BED]
u32 sub_2B9220(EEContext& ctx, u32 a0);  // [release BED]
u32 sub_2B9300(EEContext& ctx, u32 a0);  // [BED add reference]
u32 sub_2B9350(EEContext& ctx, u32 a0);  // [BED bound?]
u32 sub_2B9370(EEContext& ctx, u32 a0, u32 a1);  // [BED duration]
u32 sub_2B93C0(EEContext& ctx, u32 a0, u32 a1);  // [BED group word]
u32 sub_2B9590(EEContext& ctx, u32 a0);  // [unit size scale]
u32 sub_2B9600(EEContext& ctx, u32 a0);  // [copy matrix]
u32 sub_2B9640(EEContext& ctx, u32 a0);  // [instance flags]
u32 sub_2B96E0(EEContext& ctx, u32 a0, u32 a1);  // [BED set file]
u32 sub_2B96F0(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3);  // [place by entry]
u32 sub_2B99D0(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3);  // [place at owner]
u32 sub_2B9B00(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3);  // [place at bone]
u32 sub_2B9C00(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3);  // [place at bone (attachment 964)]
u32 sub_2B9D40(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3);  // [place at bone (attachment 952)]
u32 sub_2B9E80(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3);  // [place at centre]
u32 sub_2B9F30(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3);  // [place at own side]
u32 sub_2BA000(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3);  // [place at other side]
u32 sub_2BA0D0(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3);  // [place nowhere]
u32 sub_2BA0F0(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3);  // [orient by entry]
u32 sub_2BA3A0(EEContext& ctx, u32 a0);  // [instance update]
u32 sub_2BA900(EEContext& ctx, u32 a0);  // [instance draw]

// --- unit effect packets (kinds 0x400, 0x301, 0x302: an effect slot attached to one or two units) --------------------
u32 sub_2BAC00(EEContext& ctx, u32 a0, u32 a1, u32 a2);  // [create named effect]
u32 sub_2BACB0(EEContext& ctx, u32 a0);  // [unit effect start]
u32 sub_2BAD60(EEContext& ctx, u32 a0);  // [unit effect update]
u32 sub_2BAEC0(EEContext& ctx, u32 a0);  // [unit effect done?]
u32 sub_2BAF30(EEContext& ctx, u32 a0);  // [unit effect end]
u32 sub_2BAF90(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3, u32 t0);  // [create unit effect]
u32 sub_2BB050(EEContext& ctx, u32 a0);  // [unit effect 2 start]
u32 sub_2BB0B0(EEContext& ctx, u32 a0);  // [unit effect 2 update]
u32 sub_2BB290(EEContext& ctx, u32 a0);  // [unit effect 2 end]
u32 sub_2BB2F0(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3, u32 t0);  // [create unit effect 2]

// --- effect slots (gBtl's slot list +400, linked by +32; a unit's pool of 48 slots, in-use mask +192) ----------------
u32 sub_2BB3A0(EEContext& ctx);  // [update slots]
u32 sub_2BB580(EEContext& ctx, u32 a0);  // [reset slot]
u32 nullsub_14(EEContext& ctx);
u32 sub_2BB770(EEContext& ctx);  // [free all slots]
u32 sub_2BB9C0(EEContext& ctx, u32 a0);  // [alloc slot]
u32 sub_2BBAC0(EEContext& ctx, u32 a0, u32 a1);  // [free slot]
u32 sub_2BBBC0(EEContext& ctx, u32 a0);  // [slots hidden]
u32 sub_2BBDC0(EEContext& ctx, u32 a0, u32 a1);  // [set slot effect]
u32 sub_2BBDF0(EEContext& ctx, u32 a0);  // [slot effect]
u32 sub_2BBE00(EEContext& ctx, u32 a0);  // [refresh slot effect]
u32 sub_2BBF80(EEContext& ctx, u32 a0, u32 a1);  // [set slot alpha]
u32 sub_2BBFA0(EEContext& ctx, u32 a0);  // [affinity icon]

// --- battle event packets (kinds 0x306..0x30A, the HP / SP gauges 0x500 / 0x501, 0x504..0x50A) and the affinity
// colours -------------------------------------------------------------------------------------------------------------
u32 sub_2BC0E0(EEContext& ctx, u32 a0, u32 a1);  // [affinity colour]
u32 sub_2BC680(EEContext& ctx);  // [create 0x306]
u32 sub_2BC7B0(EEContext& ctx, u32 a0);  // [0x308 update]
u32 sub_2BC7E0(EEContext& ctx, u32 a0);  // [create 0x308]
u32 sub_2BC830(EEContext& ctx, u32 a0);  // [fade update]
u32 sub_2BC890(EEContext& ctx, u32 a0, u32 a1);  // [create fade]
u32 sub_2BC910(EEContext& ctx, u32 a0);  // [0x309 update]
u32 sub_2BC950(EEContext& ctx, u32 a0, u32 a1, u32 a2);  // [create 0x309]
u32 sub_2BCDE0(EEContext& ctx, u32 a0, u32 a1);  // [reset gauges]
u32 sub_2BCE10(EEContext& ctx, u32 a0, u32 a1, u32 a2);  // [draw gauge]
u32 sub_2BD060(EEContext& ctx, u32 a0);  // [gauge start]
u32 sub_2BD080(EEContext& ctx, u32 a0);  // [gauge update]
u32 sub_2BD210(EEContext& ctx, u32 a0);  // [gauge end]
u32 sub_2BD230(EEContext& ctx, u32 a0, u32 a1, u32 a2);  // [create gauge]
u32 sub_2BD2C0(EEContext& ctx, u32 a0);  // [gauges start]
u32 sub_2BD2E0(EEContext& ctx, u32 a0);  // [gauges update]
u32 sub_2BD460(EEContext& ctx, u32 a0);  // [gauges end]
u32 sub_2BD480(EEContext& ctx, u32 a0);  // [create gauges]
u32 sub_2BD590(EEContext& ctx, u32 a0, u32 a1);  // [create 0x504]
u32 sub_2BD690(EEContext& ctx, u32 a0, u32 a1);  // [create 0x505]
u32 sub_2BD780(EEContext& ctx, u32 a0, u32 a1);  // [create 0x507]
u32 sub_2BD850(EEContext& ctx, u32 a0, u32 a1);  // [create 0x506]
u32 sub_2BD8B0(EEContext& ctx, u32 a0);  // [pair start]
u32 sub_2BDBA0(EEContext& ctx, u32 a0);  // [pair end]
u32 sub_2BDBD0(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3, u32 t0, u32 t1, u32 t2, u32 t3);  // [create 0x50A]

// --- the command lists (the debug lists "Attack" / "Skill" / "Item" / "Escape" / "Wait": records 0x696E10.., table
// 0x696F30) and the "battle_command_calc" / "battle_command_draw" tasks -----------------------------------------------
u32 sub_2BDCD0(EEContext& ctx, u32 a0);  // [0x50B update]
u32 sub_2BDDD0(EEContext& ctx);  // [create 0x50B]
u32 sub_2BDE10(EEContext& ctx, u32 a0, u32 a1);  // [list skills]
u32 sub_2BDFB0(EEContext& ctx, u32 a0);  // [list input]
u32 nullsub_100(EEContext& ctx);
u32 sub_2BE2F0(EEContext& ctx);  // [root list input]
u32 sub_2BE390(EEContext& ctx, u32 a0, u32 a1, u32 a2);  // [root list draw]
u32 sub_2BE580(EEContext& ctx, u32 a0, u32 a1);  // [Attack]
u32 sub_2BE5D0(EEContext& ctx, u32 a0, u32 a1);  // [Escape]
u32 sub_2BE5F0(EEContext& ctx, u32 a0, u32 a1);  // [Wait]
u32 sub_2BE610(EEContext& ctx, u32 a0);  // [skill list init]
u32 sub_2BE620(EEContext& ctx, u32 a0, u32 a1);  // [skill list input]
u32 sub_2BE720(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3);  // [skill list draw]
u32 nullsub_101(EEContext& ctx);
u32 sub_2BE9E0(EEContext& ctx, u32 a0, u32 a1);  // [item list input]
u32 sub_2BEA80(EEContext& ctx, u32 a0, u32 a1, u32 a2);  // [item list draw]
u32 sub_2BECC0(EEContext& ctx);  // [command state]
u32 btlCommand_UpdateBattleCommandCalcTask(EEContext& ctx, u32 a0);  // [battle_command_calc]
u32 btlCommand_UpdateBattleCommandDrawTask(EEContext& ctx, u32 a0);  // [battle_command_draw]
u32 sub_2BF650(EEContext& ctx);  // [end command tasks]

// --- the remaining packet callbacks, the gauges' draw and the target lists -------------------------------------------
u32 nullsub_15(EEContext& ctx);
u32 nullsub_16(EEContext& ctx);
u32 nullsub_17(EEContext& ctx);
u32 nullsub_18(EEContext& ctx);
u32 sub_2BF9B0(EEContext& ctx);  // [draw gauges]
u32 sub_2BFAB0(EEContext& ctx);  // [0x50C update]
u32 sub_2BFAE0(EEContext& ctx);  // [create 0x50C]
u32 sub_2BFB20(EEContext& ctx);  // [0x50D update]
u32 sub_2BFB50(EEContext& ctx);  // [create 0x50D]
u32 sub_2BFB90(EEContext& ctx, u32 a0);  // [0x508 update]
u32 sub_2BFC00(EEContext& ctx);  // [create 0x508]
u32 sub_2BFC50(EEContext& ctx);
u32 sub_2BFC70(EEContext& ctx);
u32 sub_2BFC90(EEContext& ctx);
u32 sub_2BFCB0(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3, u32 t0);  // [target list]
u32 sub_2BFF60(EEContext& ctx, u32 a0, u32 a1, u32 a2, u32 a3);  // [skill targets]

}  // namespace p3fes::game
