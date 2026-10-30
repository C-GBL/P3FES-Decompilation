// Phase 5 slice field6, part result (game/src/battle/field6_result.cpp): br_root.c, br_data.c, bp_root.c and
// bcm_main.c. Register ABI.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

// brRoot_CreateBattleResultTasks 0x1EF500:
//   (battle packet) -> the "battle result" task.
void brRoot_CreateBattleResultTasks(EEContext& ctx);
// brRoot_UpdateBattleResultTask 0x1EF7F0:
//   (task) -> 0.
void brRoot_UpdateBattleResultTask(EEContext& ctx);
// sub_1F07A0 0x1F07A0 [brRoot_UpdateDrawTask0]:
//   (task) -> 0.
void sub_1F07A0(EEContext& ctx);
// sub_1F0990 0x1F0990 [brRoot_Destroy]:
//   (task) the destroy body of the "battle result" task (called by sub_1F0970): closes the message windows
//   when a page used them (flags 4 / 8 / 0x20: sub_3C77A0), shuts the result modules down (sub_264DD0 .
void sub_1F0990(EEContext& ctx);
// sub_1F0AD0 0x1F0AD0 [brRoot_CopyPacket]:
//   (task, battle packet) copies the battle's outcome into the work: packet flag 1 -> work flag 2 (Shuffle
//   Time), the unit list ({u16 id, s32 value} x packet +28 -> +176 / +152..), +32 -> +180, units / dead units
//   (+44 / +48 -> +280 / +284, both printed: "num_unit %d", "num_unit_dead %d"), the dropped ids of packet
//   +36.
void sub_1F0AD0(EEContext& ctx);
// sub_1F13B0 0x1F13B0 [brRoot_ApplyExp]:
//   (task) The level-up pass: the hero gains the battle's exp (sub_16D560 / sub_16CEF0 with the level from the
//   exp table), "player lv %d -> %d" is printed, and a level change sets flag 8 and the level milestones 1 /
//   10 / 20 / 30 (flags 4620, 4621, 4609, 4610; flag 0x40000 when one is new).
void sub_1F13B0(EEContext& ctx);
// sub_1FB560 0x1FB560 [brDataPickShiftPersona]:
//   (persona id) -> the persona a level-up "shift" turns it into.
void sub_1FB560(EEContext& ctx);
// sub_1FBA70 0x1FBA70 [brDataPickDrop]:
//   (persona id) -> an item id: the drop list (br_data +36, 6-byte rows {u16 persona, u16 item, u8 percent})
//   is rolled in order (RpRandom() % 100 < percent; "dpeis num", "r<p", "hit" / "through"); without a hit, a
//   random item of the persona's arcana (sub_1FBCA0 count, K_Assert br_data.c 435 when 0; sub_1FBD50(arcana,
//   RpRandom() % n) +2).
void sub_1FBA70(EEContext& ctx);
// sub_1FC980 0x1FC980 [brDataListFieldSkills]:
//   (unit, out u16[], out count) lists the unit's persona skills usable on the field
//   (datCalcIsSkillUsableOnField, not blocked by sub_17B660) that are 192, 193 or 194 and would heal
//   (sub_17BE10's HP > 0, sub_17BB40 = 0); each candidate's "hp:%d, sp:%d, bad:%x" and the count ("num_skill")
//   are printed.
void sub_1FC980(EEContext& ctx);
// sub_1FCB30 0x1FCB30 [brDataListHealItems]:
//   (unit, out u32[], out count) lists the items of the unit's 12 slots (sub_1706C0 / sub_170670) that are
//   usable (sub_17B4E0 on the item record +8), would heal HP (sub_17BE10) and are 4001 or 4002; printf as
//   sub_1FC980 ("num_item").
void sub_1FCB30(EEContext& ctx);
// bpRoot_CreateBattlePanelTasks 0x1FD630:
//   (parent) -> the "battle panel" task: a 217,136-byte work (RwMalloc; +0 / +4 = 0), the task (update
//   bpRoot_UpdateBattlePanelTask, destroy sub_1FDBE0) with its "battle panel draw" child (priority 4207, +8),
//   kept in gp 0x7CE2E4; the panel modules are initialised at their work offsets (+30688, +32, +48960, +72112,
//   +114816, +114828, +114976, +177696, +207120, +208672, +208688, +208704, +209684, +209704, +209728,
//   +210512, +213424, +214752, +216832, +216848), then sub_20ED70 / sub_25CF20.
void bpRoot_CreateBattlePanelTasks(EEContext& ctx);
// sub_1FDC00 0x1FDC00 [bpRootDestroy]:
//   (task) the destroy body of the "battle panel" task (sub_1FDBE0): K_Assert (bp_root.c 386) when work flag
//   0x400 is still set, the panel modules shut down in reverse (sub_266F00 .
void sub_1FDC00(EEContext& ctx);
// sub_1FF890 0x1FF890 [bcmMainSetup]:
//   (no args) The command menu's set-up for a unit's turn (bcm_main.c; K_Assert 356 without the work gp
//   0x7CE2E8): prints the seven commands' state from the disable mask +30624 ("ATTACK : OFF" .
void sub_1FF890(EEContext& ctx);
// sub_1FFF40 0x1FFF40 [bcmMainUpdate]:
//   (no args) The command menu's per-frame update (bcm_main.c, called by bpRoot_UpdateBattlePanelTask): with
//   the work (gp 0x7CE2E8) and gBtl (gp 0x7CE3EC) it runs the menu's state machine (jump table at the first
//   switch: the command ring, the skill / item / persona / tactics sub-menus, the target selection, the
//   analyse view -- "enemy : %d", "analyze : ON/OFF" printed), the pad repeat (sub_10A4E0 sounds), the
//   sub-menu modules (sub_2BF850 .
void sub_1FFF40(EEContext& ctx);

}  // namespace p3fes::game
