// Phase 5 slice field6, part comm (game/src/field/field6_comm.cpp): the field COMM handlers of k_command.c.
// Register ABI; every handler returns 1 = done / 0 = run again next frame in $v0.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

// sub_1C2010 0x1C2010 [K_Cmd_CALL_FIELD]:
//   COMM 0x021 (4 args: major, minor, entry, sub-id).
void sub_1C2010(EEContext& ctx);
// sub_1C20B0 0x1C20B0 [K_Cmd_CALL_FIELD_NO_NPC]:
//   COMM 0x1D3 (4 args). As COMM 0x021, after setting the scene record's NPC placement set (+20) to -1 (the
//   next field places no FBN set). 1.
void sub_1C20B0(EEContext& ctx);
// sub_1C2160 0x1C2160 [K_Cmd_CALL_EVENT]:
//   COMM 0x076 (3 args: the event's three ids).
void sub_1C2160(EEContext& ctx);
// sub_1C2240 0x1C2240 [K_Cmd_CALL_EVENT_EX]:
//   COMM 0x191 (4 args: the three ids, a value). As COMM 0x076 with sub_16E920(arg 3) first and, when done,
//   sub_171B50(arg 3).
void sub_1C2240(EEContext& ctx);
// sub_1C2340 0x1C2340 [K_Cmd_CALL_DUNGEON]:
//   COMM 0x078 (1 arg: the floor).
void sub_1C2340(EEContext& ctx);
// sub_1C23B0 0x1C23B0 [K_Cmd_CALL_DUNGEON_AT]:
//   COMM 0x128 (2 args: floor, entry). As COMM 0x078 with the entry, and the think task of every live party
//   unit (+364) gets kwlnTaskSetFlags. 1.
void sub_1C23B0(EEContext& ctx);
// sub_1C2480 0x1C2480 [K_Cmd_SKIP_TIME]:
//   COMM 0x0D6 (no args).
void sub_1C2480(EEContext& ctx);
// sub_1C2550 0x1C2550 [K_Cmd_REQ_SKIP]:
//   COMM 0x07A (no args): clndReqSkip (sub_17FA10). 1.
void sub_1C2550(EEContext& ctx);
// sub_1C2580 0x1C2580 [K_Cmd_NEXT_FLOOR]:
//   COMM 0x07E (no args): the party units flagged (sub_1D0270) and the dungeon moved to the next floor
//   (sub_1BFCC0 [K_FldDungeon_GoToNextFloor]). 1.
void sub_1C2580(EEContext& ctx);
// sub_1C25B0 0x1C25B0 [K_Cmd_BGM]:
//   COMM 0x00D (1 arg: the BGM id). Stops the field BGM (sub_1085C0) and, for a nonzero id, plays it
//   (sub_1086A0((s16)id)). 1.
void sub_1C25B0(EEContext& ctx);
// sub_1C2900 0x1C2900 [K_Cmd_RES_ANIM]:
//   COMM 0x089 (5 args: resource id, animation, loop, frames (float), unused float).
void sub_1C2900(EEContext& ctx);
// sub_1C2B80 0x1C2B80 [K_Cmd_RES_ANIM_END]:
//   COMM 0x0E9 (1 arg: resource id) -> 1 when the model's animation byte +238 is 1 (finished), else 0; 1 when
//   the resource is missing.
void sub_1C2B80(EEContext& ctx);
// sub_1C2C80 0x1C2C80 [K_Cmd_RES_SCALE]:
//   COMM 0x1DD (2 args: resource id, scale).
void sub_1C2C80(EEContext& ctx);
// sub_1C2DD0 0x1C2DD0 [K_Cmd_RES_SHADOW]:
//   COMM 0x1F5 (2 args: resource id, size). For an NPC (type 3) with a shadow object (+496):
//   sub_19C320(shadow, scrGetFloatPara(1)); types 10 and 1 ignore it; other types K_Assert (line 655). 1.
void sub_1C2DD0(EEContext& ctx);
// sub_1C37C0 0x1C37C0 [K_Cmd_CAMERA_TURN_TO_HERO]:
//   COMM 0x0D8 (2 args: degrees, frames): sub_1D6270 [K_FldCamera_CreateTurnToHero](0, frames, degrees). 1.
void sub_1C37C0(EEContext& ctx);
// sub_1C3820 0x1C3820 [K_Cmd_CAMERA_TURN_TO_ANGLE]:
//   COMM 0x0D9 (2 args: degrees, frames): sub_1D6630 [K_FldCamera_CreateTurnToAngle](0, frames, degrees). 1.
void sub_1C3820(EEContext& ctx);
// sub_1C3AD0 0x1C3AD0 [K_Cmd_REMOVE_CHEST]:
//   COMM 0x0E7 (no args): removes the special chest's box model (sub_1D22A0(gp 0x7CE284)). 1.
void sub_1C3AD0(EEContext& ctx);
// sub_1C3CD0 0x1C3CD0:
//   COMM 0x11C (2 args). sub_3C8DA0(1), sub_3C8DD0(the running script's +192), sub_3C8DE0(arg0, arg1, 0, 0)
//   (the 0x3C8xxx module's start). 1.
void sub_1C3CD0(EEContext& ctx);
// sub_1C3DC0 0x1C3DC0:
//   COMM 0x1E4 (no args): sub_3C8F70(), sub_3C8F20() (the same module's end). 1.
void sub_1C3DC0(EEContext& ctx);
// sub_1C4120 0x1C4120 [K_Cmd_RES_PLACE]:
//   COMM 0x138 (2 args: resource id, placement index).
void sub_1C4120(EEContext& ctx);
// sub_1C45E0 0x1C45E0 [K_Cmd_LOAD_MODEL]:
//   COMM 0x165 (2 args: major, minor) -> the model loaded from "field/rmd/m" + "%03d_" (major) + "%03d.RMD"
//   (minor), or "field/grmd/fobj" + "%03d.RMD" when major < 0 (paths built with strcpy / sprintf / strcat on
//   the stack): mdlModelCreateFromFile (sub_316B40)(4, minor, path, 0) -> scrSetIntReturnVal.
void sub_1C45E0(EEContext& ctx);
// sub_1C4700 0x1C4700 [K_Cmd_PLACE_MODEL]:
//   COMM 0x166 (2 args: model, object index) -> 0 while the model loads (sub_316F70 != 1; the return value is
//   0); when a field object 0x2800 | index already exists the model is destroyed (mdlModelDestroy) and 0
//   returned (as done); else a type-10 resource is made for it (sub_3B65D0) and, when the field's resources
//   hold the object's frame (sub_1B32F0 [K_Fldrc_FindFieldObjectFrame] over sField +4460 [+4456]), the model
//   takes that frame's matrix and scale (sub_1A5B30 / 1A5AA0 / 1A5BC0, sub_3B78B0), pose 0 / 8 frames; a frame
//   flagged 1 marks the resource (+272 = 1).
void sub_1C4700(EEContext& ctx);
// sub_1C48F0 0x1C48F0 [K_Cmd_MODEL_TO_RES]:
//   COMM 0x1EA (1 arg: model) -> 0 while it loads; then a resource of the type sub_1A5C50(10) gives
//   (sub_3B65D0) whose id is returned. 1 when made.
void sub_1C48F0(EEContext& ctx);
// sub_1C4990 0x1C4990 [K_Cmd_RES_SET_FLAG]:
//   COMM 0x167 (2 args: resource id, value): resource +272 = value when the resource exists. 1.
void sub_1C4990(EEContext& ctx);
// sub_1C4A00 0x1C4A00 [K_Cmd_LOAD_CHARA]:
//   COMM 0x139 (2 args: major, minor) -> the character model (sub_316E00(major, minor, 0)) as the return
//   value. 1.
void sub_1C4A00(EEContext& ctx);
// sub_1C4A60 0x1C4A60 [K_Cmd_CHARA_TO_RES]:
//   COMM 0x13A (2 args: model, index) -> 0 while it loads; then an NPC resource (sub_3B6270(sub_1A5C50(3),
//   index, model)) with a blob shadow (sub_317450(gp 0x7CE21C) at +492) whose id is returned. 1 when made.
void sub_1C4A60(EEContext& ctx);
// sub_1C4B30 0x1C4B30 [K_Cmd_RES_RADIUS]:
//   COMM 0x1AC (2 args: resource id, radius). Sets the frame controller's collision radius
//   (K_FldFrame_CtlSetSphereCollisRadius: type 3 +488, type 1 +480); an NPC's blob shadow (+492) is scaled to
//   (r, r, r) too. Other types K_Assert (line 1598). 1.
void sub_1C4B30(EEContext& ctx);
// sub_1C4C50 0x1C4C50 [K_Cmd_TRA_EST]:
//   COMM 0x13C (1 arg: mode). Runs the "TraEst" task (sub_1DC910 [K_TraEst_CreateTask](0, mode), kept as the
//   script's user data): 0 while it exists (kwlnTaskExists), then the user data is cleared and 1.
void sub_1C4C50(EEContext& ctx);
// sub_1C5340 0x1C5340:
//   COMM 0x168 (2 args: kind, value): sub_10A4E0(0, kind 3 -> 7, 2 -> 6, 1 -> 1, else 0, kind, value). 1.
void sub_1C5340(EEContext& ctx);
// sub_1C5400 0x1C5400:
//   COMM 0x183 (2 args: a, b): sub_10A4E0(1, 8, a, b). 1.
void sub_1C5400(EEContext& ctx);
// sub_1C54A0 0x1C54A0:
//   COMM 0x185 (1 arg): sub_1099D0(arg, 1) unless sub_1099A0() already returns it. 1.
void sub_1C54A0(EEContext& ctx);
// sub_1C5510 0x1C5510:
//   COMM 0x186 (1 arg): sub_108FD0((s16)arg). 1.
void sub_1C5510(EEContext& ctx);
// sub_1C5550 0x1C5550:
//   COMM 0x187 (2 args): sub_109040((s16)arg0, (s16)arg1). 1.
void sub_1C5550(EEContext& ctx);
// sub_1C55B0 0x1C55B0:
//   COMM 0x184 (1 arg: index): sub_10A370(4, 0x67F040 + 64 x index) (a 64-byte name from the table). 1.
void sub_1C55B0(EEContext& ctx);
// sub_1C56A0 0x1C56A0 [K_Cmd_COUNT_NPC]:
//   COMM 0x178 (no args) -> the number of NPC resources (type 3, sub_3B5D50(3) list) as the return value. 1.
void sub_1C56A0(EEContext& ctx);
// sub_1C5700 0x1C5700 [K_Cmd_NPC_RANK]:
//   COMM 0x179 (1 arg: n) -> for the n-th NPC resource: its model's u16 +214 / 50 + 1, 0 when it is above 500
//   (or no such NPC). 1.
void sub_1C5700(EEContext& ctx);
// sub_1C5870 0x1C5870:
//   COMM 0x18D (2 args: index, value): sub_3BB010(0x400 | (index & 0x3FF), value) (the type-1 resource of that
//   index). 1.
void sub_1C5870(EEContext& ctx);
// sub_1C5900 0x1C5900 [K_Cmd_PARTY_HIDE]:
//   COMM 0x1D5 (1 arg, unused). Hides the party for COMM 0x1D6: sub_1D1860(1) [K_FldUnit_SetPcVisible],
//   sub_1D1910, sub_1D1B60, sub_1D4180 [K_FldUnit_StopBadstatTasks], the damage EPL (sField +4608) stopped
//   (sub_1A9470), the re-create step gp 0x7CE278 = 0. 1.
void sub_1C5900(EEContext& ctx);
// sub_1C5980 0x1C5980 [K_Cmd_PARTY_RECREATE]:
//   COMM 0x1D6 (1 arg: character id). Re-creates the party, three frames' worth of steps in gp 0x7CE278:.
void sub_1C5980(EEContext& ctx);
// sub_1C5D30 0x1C5D30 [K_Cmd_DARK_HOUR_BEGIN]:
//   COMM 0x1E7 (no args). Resets gp 0x7CE274 / 0x7CE270; when the field event value is 0 (sub_45AF40
//   [fldEvtGetValue]) plays event voice 135 (sub_3952D0 [MT_Misc_PlayEventVoice](0, 135, 3)) and sets 0x7CE274
//   = 1. 1.
void sub_1C5D30(EEContext& ctx);
// sub_1C5D80 0x1C5D80 [K_Cmd_DARK_HOUR_WAIT]:
//   COMM 0x1E8 (no args) -> the return value 2 = the main field script restarted, 0 = still waiting.
void sub_1C5D80(EEContext& ctx);

}  // namespace p3fes::game
