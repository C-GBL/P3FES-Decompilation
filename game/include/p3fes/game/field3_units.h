// The field units of k_unit.c, third field pass (Phase 5 slice `field3`, part `units`; game/src/field/field3_units.cpp,
// pair tests tests/game/test_field3_units.cpp). p3fes_handgen bodies made readable: every function takes the guest
// register file (register ABI: arguments in $a0.., the result in $v0). Names: functions.json's; proposals in brackets.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

void K_FldUnit_CreateReaper(EEContext& ctx);  // 0x1CFC50 (-, position) -> the Reaper (encounter 506) unit or 0; 0 with flag 5141
void sub_1CFDD0(EEContext& ctx);  // 0x1CFDD0 [K_FldUnit_FinishShadow] (slot) -> 1 done / no shadow, 0 while its model loads; resource, tasks
void sub_1D00B0(EEContext& ctx);  // 0x1D00B0 [K_FldUnit_FinishAllShadows] -> 1 when all 24 are done
void sub_1D0110(EEContext& ctx);  // 0x1D0110 [K_FldUnit_Destroy] (unit): genus, resource, model, tasks, live count, buckets
void sub_1D0330(EEContext& ctx);  // 0x1D0330 [K_FldUnit_DestroyAllPc] sub_1D0110 on the 4 party units
void sub_1D0390(EEContext& ctx);  // 0x1D0390 [K_FldUnit_DestroyAllEc] sub_1D0110 on the 24 shadows
void sub_1D03F0(EEContext& ctx);  // 0x1D03F0 K_FldUnit_CreateAllPc (entry): the hero and the party members at the entry placement
void sub_1D0880(EEContext& ctx);  // 0x1D0880 [K_FldUnit_PickShadowPlacement] (index, wanted) -> a type-15 placement away from the party / shadows
void sub_1D0BC0(EEContext& ctx);  // 0x1D0BC0 [K_FldUnit_PickSpreadPlacements] (out[n], n): n placements spread from the hero and each other
void sub_1D0E50(EEContext& ctx);  // 0x1D0E50 [K_FldUnit_RecreatePcs] (skip_hero): the party units after a scene reload
void sub_1D1360(EEContext& ctx);  // 0x1D1360 [K_FldUnit_RecreateEcs] the shadows after a scene reload, then the buckets
void sub_1D1DB0(EEContext& ctx);  // 0x1D1DB0 [K_FldBox_CreateModel] (box, placement, resource id): the box model, shadow, cell; count + 1
void sub_1D1FA0(EEContext& ctx);  // 0x1D1FA0 [K_FldBox_PlaceAll] the floor's treasure boxes and their contents
void sub_1D2210(EEContext& ctx);  // 0x1D2210 [K_FldBox_RecreateModels] every placed box's model again, then the buckets
void sub_1D22A0(EEContext& ctx);  // 0x1D22A0 [K_FldBox_Remove] (box): resource freed, record cleared, count - 1, buckets
void sub_1D2300(EEContext& ctx);  // 0x1D2300 [K_FldBox_PickPlacement] (index, wanted) -> a type-16 placement away from the hero / boxes
void sub_1D2610(EEContext& ctx);  // 0x1D2610 [K_FldBox_PlaceSpecialChest] the type-17 chest 0x86E580 by the floor's percentage
void sub_1D2A10(EEContext& ctx);  // 0x1D2A10 [K_FldUnit_RebuildBuckets] the 4 x 4 proximity buckets 0x86B180 (shadows, boxes, special chest)
void sub_1D36C0(EEContext& ctx);  // 0x1D36C0 [K_Unit_DestroyEnemyPopScheduler] RwFree(task work)
void sub_1D36F0(EEContext& ctx);  // 0x1D36F0 [K_Unit_CreateEnemyPopScheduler] (parent) -> the "enemy pop scheduler" task; flag 5155 cleared
void sub_1D39C0(EEContext& ctx);  // 0x1D39C0 [K_Unit_ForceReaper] (scheduler task): the Reaper now, scheduler state 1
void sub_1D3A30(EEContext& ctx);  // 0x1D3A30 [K_FldUnit_UpdateMaterialAnimTask] the pulsing material colour of a kind-2 shadow
void sub_1D3C10(EEContext& ctx);  // 0x1D3C10 [K_FldUnit_DestroyMaterialAnimTask] RwFree(task work)
void sub_1D3C40(EEContext& ctx);  // 0x1D3C40 [K_FldUnit_CreateMaterialAnimTask] (parent, model) -> the "enemy material anim" task
void sub_1D3CE0(EEContext& ctx);  // 0x1D3CE0 [K_FldUnit_UpdateBadstatTask] bad status 0x80 on a party unit: tint, effect, HP loss per 2,400 units
void sub_1D40B0(EEContext& ctx);  // 0x1D40B0 [K_FldUnit_DestroyBadstatTask] RwFree(task work)
void sub_1D40E0(EEContext& ctx);  // 0x1D40E0 [K_FldUnit_CreateBadstatTask] (parent, unit) -> the "badstat CTL" task
void sub_1D4180(EEContext& ctx);  // 0x1D4180 [K_FldUnit_StopBadstatTasks] the party's badstat effects stopped, tasks destroyed
void sub_1D4290(EEContext& ctx);  // 0x1D4290 [K_FldTbl_LoadEnemyTable] field/table/enemy.bin (enemy_aegis.bin in The Answer), synchronous
void sub_1D4360(EEContext& ctx);  // 0x1D4360 [K_FldTbl_RequestEnemyTable] -> the request for the same file, or 0
void sub_1D43E0(EEContext& ctx);  // 0x1D43E0 [K_FldTbl_FinishEnemyTable] (request) -> 1 when loaded and copied
void sub_1D4460(EEContext& ctx);  // 0x1D4460 [K_FldFilter_BuildGrid] (camera): the 7 x 8 filter quads at 0x872240
void sub_1D4560(EEContext& ctx);  // 0x1D4560 [K_FldFilter_Load] field/FILTER.FLD into its buffer, then the grid
void sub_1D50C0(EEContext& ctx);  // 0x1D50C0 [K_FldFilter_Set] (filter, value, frames): the current filter and its fade

}  // namespace p3fes::game
