// Phase 5 slice field6, part fldrc (game/src/field/field6_fldrc.cpp): k_fldrc.c's loaders, the exit-table
// install and the transparent-wall control. Register ABI: arguments in $a0.., the result in $v0. Records:
// field6.h, field4.h.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

// sub_1C0190 0x1C0190 [K_FldDungeon_RequestScript]:
//   Requests the automatic dungeon's script: when the dungeon task (gp 0x7CE268) exists and its script copy
//   (work +52) is still empty, H_Cdvd_Request("field/script/dungeonat.bf", 0) -- "dungeonat_aegis.bf" in The
//   Answer (sub_17D800) -- and returns the request; else 0.
void sub_1C0190(EEContext& ctx);
// sub_1C0210 0x1C0210 [K_FldDungeon_TryLoadScript]:
//   (request) -> 1 when done: no dungeon task or no request -> 1; the request still loading -> 0; loaded ->
//   the script is copied into RwCalloc(1, size, 0x40000) at work +52 (size at +56), the request is destroyed,
//   1.
void sub_1C0210(EEContext& ctx);
// sub_1C02E0 0x1C02E0 [K_FldDungeon_FreeScript]:
//   Frees the dungeon script copy (work +52, RwFree through the slot 0x96017C) and clears the pointer; nothing
//   without the dungeon task or a copy. $v0 is left as the free returned (or untouched).
void sub_1C02E0(EEContext& ctx);
// sub_1C0330 0x1C0330 [K_FldDungeon_RequestBlockScript]:
//   (block set) -> H_Cdvd_Request of "field/script/dungeonat%02d.bf" ("dungeonat%02d_aegis.bf" in The Answer),
//   the 128-byte path built on the stack; the field root keeps it at root work +44 (Tartarus floors run their
//   block's script).
void sub_1C0330(EEContext& ctx);
// sub_1C03F0 0x1C03F0 [K_Fldrc_RequestBtlEffPack]:
//   Requests "field/btl_effect/btl_eff.pac" (H_Cdvd_Request(path, 1)) into gp 0x7CE258 unless the EPLs are
//   already made (sField +4596) or the request exists; returns the last call's $v0 (K_Field_Get's sField when
//   nothing is asked).
void sub_1C03F0(EEContext& ctx);
// sub_1C0440 0x1C0440 [K_Fldrc_TryCreateBtlEffEpls]:
//   (no args) -> 1 when the battle-effect EPLs are ready: no btl_eff.pac request -> 1; the pack still loading
//   -> 0; loaded -> every empty EPL slot of sField +4596.
void sub_1C0440(EEContext& ctx);
// sub_1C0740 0x1C0740 [K_Fldrc_TryReleaseBtlEffPack]:
//   (no args) -> 1 when the btl_eff.pac request may go: 0 while one of the ten EPLs (sField +4596 [10]) is not
//   ready (sub_1A9180 = 0); then the request (gp 0x7CE258) is destroyed and cleared; 1.
void sub_1C0740(EEContext& ctx);
// sub_1C07F0 0x1C07F0 [K_Fldrc_DestroyBtlEffEpls]:
//   Destroys the ten battle-effect EPL tasks (sField +4596 [10], kwlnTaskDestroyWithHierarchy) and clears the
//   slots. Callers: K_Field_DestroyFieldRootTask, sub_1BFAF0, the event task.
void sub_1C07F0(EEContext& ctx);
// sub_1C0920 0x1C0920:
//   (task) the destroy callback of an "atomic fade CTL" task: clears the atomic's fade-task word (+32 of the
//   fade target) and frees the 20-byte work (RwFree).
void sub_1C0920(EEContext& ctx);
// sub_1C0D30 0x1C0D30:
//   (task) the destroy callback of an "RMD fade CTL" task: clears the field object's fade-task word (scene
//   resource +264) and frees the 20-byte work (RwFree).
void sub_1C0D30(EEContext& ctx);
// sub_1C0D70 0x1C0D70 [K_FldWall_Update]:
//   (task) the update of the "trans wall CTL" task (sub_1C1F30): state 1 -> -1 (the kernel destroys the task);
//   else, in state 0, two rays from the camera eye +/- 100 x its right vector to the target unit's collision
//   sphere (centre lifted by radius + 60), skipped in field 24/50 or when the target sits at the eye:.
void sub_1C0D70(EEContext& ctx);
// sub_1C1E20 0x1C1E20 [K_FldWall_Destroy]:
//   (task) the destroy callback of the "trans wall CTL" task: every alive field object whose model alpha is 0
//   gets an "RMD fade CTL" task that restores it at once (1 step, 255.0), then the 524-byte work is freed
//   (RwFree).
void sub_1C1E20(EEContext& ctx);
// sub_1C1F30 0x1C1F30 [K_FldWall_Create]:
//   (parent, unit) -> the "trans wall CTL" task (priority 2109; update sub_1C0D70, destroy sub_1C1E20) over a
//   524-byte RwCalloc work with the target unit at +516, or 0 when the allocation fails.
void sub_1C1F30(EEContext& ctx);
// K_Fldrc_RequestFieldHitTableFile 0x1C7E70:
//   (major, minor) -> the exit-table request: the field's .pac resident (sub_1B0910) -> 1 (the table is its
//   member); else H_Cdvd_Request("field/table/h%03d_%03d.bin", 0) when H_Cdvd_FileExists says the file is
//   there, else 0.
void K_Fldrc_RequestFieldHitTableFile(EEContext& ctx);
// sub_1C7F20 0x1C7F20 [K_Fldrc_TryLoadFieldHitTable]:
//   (request) -> 1 when the exit table is installed: request 0 -> 1; .pac resident -> the member
//   "field/pack/h%03d_%03d.bin" of the scene record's ids from the H_Cdvd cache (H_Cdvd_CacheFindFile, size
//   into the stack word +0x7C) copied when found, 1; else 0 while loading, then copied and the request
//   destroyed, 1.
void sub_1C7F20(EEContext& ctx);
// sub_1CE960 0x1CE960 [K_FldUnit_FinishPcs]:
//   (no args) -> 1 when the party units are placed, 0 while something still loads.
void sub_1CE960(EEContext& ctx);

}  // namespace p3fes::game
