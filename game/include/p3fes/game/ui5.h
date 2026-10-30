// The camp menu's screens, fifth UI pass (slice ui5), hand-decompiled from SLUS_216.21 (docs/ANALYSIS/20_menu_ui.md
// section 2): the camp root's loaders (the camp_all.pak sprite set-up task, the persona texture control), the main
// list's slide / fade tweens, the flash-control task (h_camp_flash_control: its dispatcher, the request and the 28
// screen-transition .anm players), the two side-portrait ("kani") control tasks, the Status screen (its root, the HP /
// SP / condition / sparkle / persona panel draws, the stat table and bars), the equipment screen's helpers (the
// backdrop, the number sprites, the equipment lists), the persona screen's picture loaders (CampPersonaDispCtl*), the
// social-link screen's files, pictures and card draws, the item screen's list builders and item use, the system /
// config menu's tweens and unlock test, the skill screen's skill use, the party-status screen a script opens
// (H_FRStatusDisp, H_FrStatusFlashDraw), the trade screen's task, every screen's task creator / destroy, and the camp
// PAK tween-record helpers sub_18B6D0 / sub_18BC10. Phase 5 slice `ui5`; game/src/ui/ui5.cpp, pair tests
// tests/game/test_ui5.cpp. ui3 has the camp root (H_Camp_UpdateDrawTask), the main list's update and the screens'
// draw dispatchers; this slice takes the screens' still-recompiled leaves and task plumbing around them.
//
// The bodies are p3fes_handgen's (hg_cpu.h): register for register, frame, spills, $ra links, cycle charges and check
// points as the recompiled code; this pass adds a role per function, the named offsets below (each equals the literal
// it replaces), and callee notes. Names: symbols/functions.json's; the proposed names in brackets are ours (from the
// task / file strings, the callers and the instructions; not in any delta).
//
// Records (offsets are byte offsets; the work block of a kwlnTask is at task +0x3C):
// * RW memory slots 0x960178 / 0x96017C / 0x960184 (RwMalloc / RwFree / RwCalloc): every work block here is
//   RwCalloc(1, size, 0x40000) and freed through RwFree by its destroy callback.
// * tween record (68 bytes, sub_18BC10; arrays from sub_18B6D0, run by sub_18B700): the camp screens' panel motions.
// * flash-control work (108 bytes, sub_11F1B0): state (the dispatcher's), step of the running player (999 = done),
//   the screen shown (+8), frame timer, done flag, ten .anm task slots, the .anm being loaded, two files at +100.
// * sprite set-up work (72 bytes, sub_119F10 / sub_1675E0): state, 14 sprite files, the pak, message flag, tweens.
// * persona texture control (276 bytes, sub_11B2B0) / persona picture (300 bytes, sub_1339A0): state, persona id,
//   file, texture, the texture build (sub_10C1A0 / sub_10C3A0), the formatted path.
// * side-portrait work (24 / 28 bytes): state, timer, screen, shown flag, pose (s16 at +20 / +24).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace ui5 {
namespace task {  // the task record
inline constexpr s32 kWork = 60;  // kwlnTask +0x3C: the work block
}  // namespace task
namespace rw {  // the RW memory function slots (absolute: v = 0x960000 + slot)
inline constexpr s32 kMallocSlot = 376;  // 0x960178: RwMalloc
inline constexpr s32 kFreeSlot = 380;  // 0x96017C: RwFree
inline constexpr s32 kCallocSlot = 388;  // 0x960184: RwCalloc
}  // namespace rw
namespace g {  // $gp-relative words ($gp = 0x7D2CF0; the address in the comment)
inline constexpr s32 kCampSetupTask = -19880;  // 0x7CDF48: the "H_CampSprSetupFile" task (one at a time)
inline constexpr s32 kCampTweens = -19876;  // 0x7CDF4C: the camp tween records (200)
inline constexpr s32 kCampFlashTask = -19872;  // 0x7CDF50: the flash-control task
inline constexpr s32 kCampPcKani = -19868;  // 0x7CDF54: the protagonist side-portrait task
inline constexpr s32 kCampPersonaKani = -19864;  // 0x7CDF58: the persona side-portrait task
inline constexpr s32 kCampRootTask = -19860;  // 0x7CDF5C: the main list task
inline constexpr s32 kPersonaTexTask = -19856;  // 0x7CDF60: the "CampPersonaTexControl" task
inline constexpr s32 kSparkleFrame = -19852;  // 0x7CDF64: the status sparkle cycle (0..99)
inline constexpr s32 kComuBustBuild = -19840;  // 0x7CDF70: the social-link bust-up build
inline constexpr s32 kComuArcanaBuild = -19836;  // 0x7CDF74: the social-link arcana picture build
inline constexpr s32 kScreenTaskC = -19828;  // 0x7CDF7C: a camp screen task polled by sub_16A6A0
inline constexpr s32 kTradeTask = -19824;  // 0x7CDF80: the "H_CampTradeDraw" task (ui3 kScreenTaskB)
inline constexpr s32 kFrStatusDispTask = -19820;  // 0x7CDF84: the "H_FRStatusDisp" task (ui3 kScreenTaskA)
inline constexpr s32 kFrStatusFlashTask = -19816;  // 0x7CDF88: the "H_FrStatusFlashDraw" task
inline constexpr s32 kSkillRibbonX = -19812;  // 0x7CDF8C: the skill screen ribbon x
inline constexpr s32 kItemRibbonX = -19808;  // 0x7CDF90: the item screen ribbon x
inline constexpr s32 kComuPulse = -19800;  // 0x7CDF98: the social-link picture pulse (0..19)
inline constexpr s32 kComuRibbonY = -19796;  // 0x7CDF9C: the social-link ribbon offset
inline constexpr s32 kStatusStripX = -19792;  // 0x7CDFA0: the status strip x
inline constexpr s32 kUnlockTable = -19768;  // 0x7CDFB8: the system menu's unlock table (12-byte rows)
}  // namespace g
namespace fl {  // flash-control work
inline constexpr s32 kState = 0;  // u32: the dispatcher state (sub_11EA20; odd = arm, even = run a player, 0 = idle)
inline constexpr s32 kStep = 4;  // u32: the running player's step; 999 = finished
inline constexpr s32 kScreen = 8;  // u32: the screen shown (0 = main list)
inline constexpr s32 kTimer = 12;  // u32: frame timer of a player
inline constexpr s32 kDone = 16;  // u32: 1 once the transition reached its target
inline constexpr s32 kAnmSlots = 20;  // u32[10]: the .anm tasks on screen (slot 0 = the main list)
inline constexpr s32 kAnm1 = 24;  // slot 1 (a screen)
inline constexpr s32 kAnm2 = 28;  // slot 2 (a sub-window)
inline constexpr s32 kLoading = 60;  // u32: the .anm being loaded (sub_111DD0)
inline constexpr s32 kLoading2 = 64;  // u32: cleared with it by the close players
}  // namespace fl
namespace tw {  // tween record (68 bytes)
inline constexpr s32 kExtraA = 0;  // u32: the 7th argument
inline constexpr s32 kActive = 4;  // u32: 1 = running
inline constexpr s32 kKind = 8;  // u32: 1st argument
inline constexpr s32 kMode = 12;  // u32: 2nd argument (0 fade in, 2 slide / fade out ...)
inline constexpr s32 kCurve = 16;  // u32: 3rd argument
inline constexpr s32 kExtraB = 20;  // u32: the 8th argument
inline constexpr s32 kFrame = 24;  // u32: the current frame (0 at start)
inline constexpr s32 kFirst = 28;  // u32: first frame
inline constexpr s32 kLast = 32;  // u32: last frame
inline constexpr s32 kZ = 36;  // f32: z ($f12)
inline constexpr s32 kFromX = 40;  // f32
inline constexpr s32 kFromY = 44;  // f32
inline constexpr s32 kToX = 48;  // f32
inline constexpr s32 kToY = 52;  // f32
}  // namespace tw
namespace sf {  // sprite set-up work
inline constexpr s32 kState = 0;  // u32: 0 wait for the pak, 1 wait for the files, 2 pak only, 3 loaded
inline constexpr s32 kFiles = 4;  // u32[14]: the sprite files (copied to 0x833B70 when ready)
inline constexpr s32 kPak = 60;  // u32: the camp PAK request
inline constexpr s32 kMessage = 64;  // u32: a message was opened (closed by the destroy)
inline constexpr s32 kTweens = 68;  // u32: the tween records (also gp-19876)
}  // namespace sf
namespace ptc {  // persona texture control work
inline constexpr s32 kState = 0;  // u32: 0 request, 1 wait file, 2 wait build, 3 idle
inline constexpr s32 kPersona = 4;  // u32: persona id (0 = none)
inline constexpr s32 kFile = 8;  // u32: the .tmx file request
inline constexpr s32 kTexture = 12;  // u32: the texture
inline constexpr s32 kBuild = 16;  // u32: the texture build
inline constexpr s32 kPath = 20;  // char[]: camp/persona/pst_%03X.tmx
}  // namespace ptc
namespace pdc {  // persona picture work
inline constexpr s32 kState = 0;  // u32
inline constexpr s32 kPersona = 4;  // u32
inline constexpr s32 kArg = 12;  // u32
inline constexpr s32 kZ = 16;  // f32
inline constexpr s32 kSlideStep = 20;  // f32
inline constexpr s32 kSlide = 24;  // f32: eases to 60.0
inline constexpr s32 kSlideY = 28;  // f32
inline constexpr s32 kBuild = 32;  // u32
inline constexpr s32 kFile = 36;  // u32
inline constexpr s32 kTexture = 40;  // u32
inline constexpr s32 kPath = 44;  // char[]
}  // namespace pdc
namespace kani {  // side-portrait work
inline constexpr s32 kState = 0;  // u32
inline constexpr s32 kTimer = 8;  // u32
inline constexpr s32 kScreen = 12;  // u32: the screen shown (ui3: kKaniScreen)
inline constexpr s32 kShown = 16;  // u32: 1 = on screen
}  // namespace kani
}  // namespace ui5

// [H_Camp_UpdateCampSprSetupFileTask] Update of "H_CampSprSetupFile" (20_menu_ui.md 2.2 state 0).
void sub_119AA0(EEContext& ctx);  // 0x119AA0
// [H_Camp_DestroyCampSprSetupFileTask] Destroy of "H_CampSprSetupFile": releases the 14 sprite files (sub_1124B0),
// the pak (H_Cdvd_Destroy), the tween records (RwFree, and clears gp-19876), clears 0x833B70[0..13], frees the work,
// closes the message of +64 (sub_3C77A0, ...
void sub_119E00(EEContext& ctx);  // 0x119E00
// [H_Camp_CreateCampSprSetupFileTask] (parent, message): creates "H_CampSprSetupFile" (72-byte work, priority 6335)
// unless one exists (gp-19880), requests camp/camp_all2.pak in The Answer (sub_17D800() != 0) else camp/camp_all.pak
// into +60, keeps the message flag in +64 ...
void sub_119F10(EEContext& ctx);  // 0x119F10
// [H_Camp_DestroyDrawTask] Destroy of "H_CampDraw": forgets the side-portrait, flash and root-list tasks (gp-19868,
// -19864, -19872, -19860), clears flag 0x1407 (camp open, read by the date HUD) and frees the work.
void sub_11A710(EEContext& ctx);  // 0x11A710
// (parent): creates the camp menu root "H_CampDraw" (72-byte work, priority 6335, update H_Camp_UpdateDrawTask,
// destroy sub_11A710).
void H_Camp_CreateDrawTask(EEContext& ctx);  // 0x11A770
// [H_Camp_UpdateStatusSprSetupFileTask] Update of "H_CampStatusSprSetupFile" (created by sub_1675E0): as sub_119AA0
// for camp/camp_status.pak: its 8 entries become sprite files 1, 2, 7, 9..13 of the table; no tween records, no
// message.
void sub_11A8A0(EEContext& ctx);  // 0x11A8A0
// [H_Camp_DestroyStatusSprSetupFileTask] Destroy of "H_CampStatusSprSetupFile": as sub_119E00 without the message.
void sub_11AAE0(EEContext& ctx);  // 0x11AAE0
// [H_Camp_UpdatePersonaTexControlTask] Update of "CampPersonaTexControl": state 0 formats camp/persona/pst_%03X.tmx
// from the persona id (+4) into +20 and requests it (+8; id 0: straight to 3); 1: once loaded, starts the texture
// build sub_10C1A0(.., "h_camp.c", 1089) -> +16; ...
void sub_11B0B0(EEContext& ctx);  // 0x11B0B0
// [H_Camp_DestroyPersonaTexControlTask] Destroy of "CampPersonaTexControl": a build still running (+16) is handed to
// a "CampPersonaDispCtlFree" task (sub_133D30) that releases it when done; otherwise the file (+8) and the texture
// (+12, sub_4D0F00) are released.
void sub_11B210(EEContext& ctx);  // 0x11B210
// [H_Camp_CreatePersonaTexControlTask] (parent, persona id): creates "CampPersonaTexControl" (276-byte work,
// priority 6335), +4 = the id, gp-19856 = the task.
void sub_11B2B0(EEContext& ctx);  // 0x11B2B0
// [H_Camp_PersonaTexSetPersona] (persona id): when the id differs from the shown one, releases the current texture
// as sub_11B210 does and restarts the loader on the new id (state 0).
void sub_11B370(EEContext& ctx);  // 0x11B370
// [H_Camp_DestroyRootDrawTask] Destroy of "H_CampRootDraw": frees the work, gp-19860 = 0.
void sub_11BAA0(EEContext& ctx);  // 0x11BAA0
// (parent, flash task, open mode): creates the main list "H_CampRootDraw" (44-byte work, priority 6335, update
// H_Camp_UpdateRootDrawTask): +36 flash, +12 selection = -1 (none), +8 open mode.
void H_Camp_CreateRootDrawTask(EEContext& ctx);  // 0x11BAD0
// Empty hook called by the list draws (sub_11C880 and five others).
void nullsub_3(EEContext& ctx);  // 0x11BBA0
// [H_Camp_RootSlideIn] (root work): starts the main list's slide-in on the tween records at gp-19876 (sub_18BC10
// with mode 2, curve 1): records 0..6 = the seven rows from x 46 - 200 to 46 at y 59 + 19 i over frames i + 4 ..
void sub_11C550(EEContext& ctx);  // 0x11C550
// [H_Camp_RootFadeIn] (root work): the same records as sub_11C550 over frames 0..10 with mode 0 (fade in); the
// cursor bar's y 59 + 19 cursor through adda.s / madd.s.
void sub_11CC80(EEContext& ctx);  // 0x11CC80
// [H_Camp_RootFadeOut] (root work): the same records over frames 0..10, mode 0 / curve 2 (fade out) -- the close of
// the list (sub_11B9B0 / sub_11BA00).
void sub_11D3A0(EEContext& ctx);  // 0x11D3A0
// [H_Camp_RootFadeOut2] (root work): a copy of sub_11D3A0 used by the item and skill screens (the same records from
// the same input).
void sub_11DA80(EEContext& ctx);  // 0x11DA80
// [H_CampFlash_Request] (flash task, screen): when the flash task is idle (state 0) picks the transition for (the
// screen shown, +8; the requested one) through three jump tables -- the dispatcher state of sub_11EA20 -- or just
// raises the done flag (+16) when ...
void sub_11E380(EEContext& ctx);  // 0x11E380
// [H_CampFlash_UpdateTask] Update of "h_camp_flash_control" (jump table 0x7B55E0, 59 states): an odd state arms a
// transition (state + 1, done +16 = 0, step +4 = 0), an even state runs its player (sub_11F260 ..
void sub_11EA20(EEContext& ctx);  // 0x11EA20
// [H_CampFlash_DestroyTask] Destroy of "h_camp_flash_control": the two files +100 / +104, the work.
void sub_11F120(EEContext& ctx);  // 0x11F120
// [H_Camp_CreateFlashControlTask] (parent): creates "h_camp_flash_control" (108-byte work, priority 6335, update
// sub_11EA20), +8 = 0 (main list).
void sub_11F1B0(EEContext& ctx);  // 0x11F1B0
// Plays camp/main_all/if_c_mai01.anm (the main list): an anm already in slot 0 just draws; else load, start (24
// frames, sound 3), then it replaces slots 0..9.
void sub_11F260(EEContext& ctx);  // 0x11F260
// Plays camp/status/anm/if_c_sta01.anm into slot 1 (status screen open; 24 frames, sound 3).
void sub_11F400(EEContext& ctx);  // 0x11F400
// Plays camp/status/anm/if_c_sta07.anm into slot 1 (sound 5).
void sub_11F5C0(EEContext& ctx);  // 0x11F5C0
// Plays camp/status/anm/if_c_sta09.anm into slot 1.
void sub_11F760(EEContext& ctx);  // 0x11F760
// Closes a screen: moves the flash task before slot 0 (kwlnTaskMoveBefore), 10 frames drawing slots 1..9, then
// destroys them (sound 4).
void sub_11F900(EEContext& ctx);  // 0x11F900
// Closes a screen over 20 frames, then destroys slots 1..9 (sound 4).
void sub_11FAF0(EEContext& ctx);  // 0x11FAF0
// Plays camp/item/anm/i_c_ite01.anm into slot 1 until it ends (item screen open; sound 3).
void sub_11FCA0(EEContext& ctx);  // 0x11FCA0
// Plays camp/item/anm/i_c_ite02.anm into slot 2 (sound 5).
void sub_11FE50(EEContext& ctx);  // 0x11FE50
// Four frames of slots 1 and 2, then destroys slot 2 (item sub-window close).
void sub_11FFD0(EEContext& ctx);  // 0x11FFD0
// Plays camp/item/anm/i_c_ite03.anm.
void sub_120150(EEContext& ctx);  // 0x120150
// Plays camp/item/anm/i_c_ite08.anm.
void sub_1202B0(EEContext& ctx);  // 0x1202B0
// Plays camp/item/anm/i_c_ite06.anm.
void sub_120410(EEContext& ctx);  // 0x120410
// Plays camp/item/anm/i_c_ite05.anm.
void sub_120570(EEContext& ctx);  // 0x120570
// Plays camp/item/anm/i_c_ite04.anm.
void sub_1206D0(EEContext& ctx);  // 0x1206D0
// Plays camp/item/anm/i_c_ite07.anm.
void sub_120830(EEContext& ctx);  // 0x120830
// Plays camp/commu/anm/i_c_com01.anm (social-link screen open).
void sub_120990(EEContext& ctx);  // 0x120990
// Plays camp/commu/anm/i_c_com02.anm.
void sub_120B10(EEContext& ctx);  // 0x120B10
// Five frames of slot 1 with slot 2 moved before it, then destroys slots 2..9 (sound 4).
void sub_120CA0(EEContext& ctx);  // 0x120CA0
// Plays camp/skill/anm/if_c_skl01.anm (skill screen open).
void sub_120E20(EEContext& ctx);  // 0x120E20
// Plays camp/EQUIP/anm/if_c_equ01.anm (equipment screen open).
void sub_120FD0(EEContext& ctx);  // 0x120FD0
// Plays camp/skill/anm/if_c_skl02.anm.
void sub_121180(EEContext& ctx);  // 0x121180
// Plays camp/EQUIP/anm/if_c_equ02.anm.
void sub_121300(EEContext& ctx);  // 0x121300
// Four frames of slots 1 and 2, then destroys slot 2 (skill sub-window close).
void sub_121480(EEContext& ctx);  // 0x121480
// Four frames of slots 1 and 2, then destroys slot 2 (equipment sub-window close).
void sub_121600(EEContext& ctx);  // 0x121600
// Plays camp/persona/anm/if_c_per01.anm (persona screen open).
void sub_121780(EEContext& ctx);  // 0x121780
// Plays camp/persona/anm/if_c_per02.anm.
void sub_121930(EEContext& ctx);  // 0x121930
// Four frames of slots 1 and 2, then destroys slot 2 (persona sub-window close).
void sub_121AB0(EEContext& ctx);  // 0x121AB0
// Plays camp/system/anm/if_c_sys01.anm (system screen open).
void sub_121C30(EEContext& ctx);  // 0x121C30
// [H_Camp_UpdatePcKaniControlTask] Update of "h_camp_pc_kani_control" (the protagonist side portrait; jump table
// 0x7B58B0): every state draws the pose through sub_123640 at (30, 219) with the pose of +20; states 1/2 (21-frame
// pose change), 5/6 and 7/8 (8-frame slide out ...
void sub_121FF0(EEContext& ctx);  // 0x121FF0
// Destroy of "h_camp_pc_kani_control": frees the work.
void sub_122630(EEContext& ctx);  // 0x122630
// [H_Camp_CreatePcKaniControlTask] (parent): creates "h_camp_pc_kani_control" (24-byte work, priority 6337, update
// sub_121FF0): +12 screen 0, +20 pose 1.
void sub_122660(EEContext& ctx);  // 0x122660
// [H_Camp_UpdatePersonaKaniControlTask] Update of "h_camp_persona_kani_control" (the persona side portrait; jump
// table 0x7B5AB0): as sub_121FF0 for the persona of +16 (datPersonaGetByPcId when it changes), drawn through
// sub_124E00.
void sub_122940(EEContext& ctx);  // 0x122940
// Destroy of "h_camp_persona_kani_control": frees the work.
void sub_122FD0(EEContext& ctx);  // 0x122FD0
// [H_Camp_CreatePersonaKaniControlTask] (parent, persona): creates "h_camp_persona_kani_control" (28-byte work,
// priority 6337, update sub_122940): +12 screen 0, +16 persona, +24 pose 1.
void sub_123000(EEContext& ctx);  // 0x123000
// [H_Camp_UpdatePcStatusRootTask] Update of "H_CampPcStatusRoot" (the Status screen root): state 0 creates the
// status draw (sub_127B00, page 0) and starts the scrolling strip (gp-19792 = 320); 1 waits for the page's answer
// (sub_127AF0 / sub_128030): -1 closes (state ...
void sub_1230C0(EEContext& ctx);  // 0x1230C0
// Destroy of "H_CampPcStatusRoot": frees the work.
void sub_123540(EEContext& ctx);  // 0x123540
// [H_Camp_CreatePcStatusRootTask] (parent, priority, pc): creates "H_CampPcStatusRoot" (36-byte work, update
// sub_1230C0), +12 = the party member.
void sub_123570(EEContext& ctx);  // 0x123570
// (xy, pc, extra, alpha): the SP numbers of a party member: the frame (sprite 5 of 0x833B90), the current SP
// (sub_16C570, datGetPcSp) and the maximum (sub_16C670, datGetPcMaxSp) as up to three digits of sprite font 2
// (sprite 11 + digit; ...
void sub_123B70(EEContext& ctx);  // 0x123B70
// (xy, pc, alpha): the condition icon of a party member: sub_16C920 (0..5) -> sprite 11, 13, 12, 16, 14, 15 of
// 0x833B90, else 43 (jump table 0x7B5AF0).
void sub_123F80(EEContext& ctx);  // 0x123F80
// (xy, pc, z in $f12): the sparkle ring of a party member whose status byte (sub_16C970) has bit 0x80: 12 particles
// on a 100-frame cycle (gp-19852), each in its second half moving outward on a circle (sinf / cosf) and fading,
// sprites ...
void sub_124090(EEContext& ctx);  // 0x124090
// (xy, persona record, alpha): the persona level (+4) as one or two digits of sprite font 2.
void sub_124E60(EEContext& ctx);  // 0x124E60
// (xy, persona record, frame): the persona panel's 9-frame reveal from frame 15: the frame (sprite 1, sliding in),
// the arcana card (file 0x833B88, sprite sub_173280(id) - 1), the level digits and the name (sub_124FD0) with their
// own fades.
void sub_125740(EEContext& ctx);  // 0x125740
// (xy, ?, persona record, alpha): the persona panel drawn at once: frame, arcana, level, name (sub_124FD0).
void sub_125B40(EEContext& ctx);  // 0x125B40
// Destroy of a status-page task: frees the work.
void sub_1266E0(EEContext& ctx);  // 0x1266E0
// Destroy of "H_CampStatusDraw": the file +56, the texture +64 (sub_4D0F00), the work.
void sub_127A40(EEContext& ctx);  // 0x127A40
// [H_Camp_CreateStatusDrawTask] (parent, priority, xy, a, b): creates "H_CampStatusDraw" (72-byte work, update
// sub_1269A0): +4/+8 position, +14 / +16 the two arguments, +32 = 1; clears the flash task's done flag (flash work
// +16).
void sub_127B00(EEContext& ctx);  // 0x127B00
// Destroy of "H_CampStatusPersonaDraw": frees the work.
void sub_127FC0(EEContext& ctx);  // 0x127FC0
// [H_Camp_CreateStatusPersonaDrawTask] (parent, priority, xy, a, b): creates "H_CampStatusPersonaDraw" (32-byte
// work, update sub_127C00): +4/+8 position, +14 / +18 the two arguments, +24 = 1; clears the flash done flag.
void sub_128040(EEContext& ctx);  // 0x128040
// (xy, row 0..8, alpha): one label of the persona stat table: sprite row of 0x833B98 (jump table 0x7B5B60).
void sub_1281E0(EEContext& ctx);  // 0x1281E0
// (xy, persona, alpha): the nine resistance marks of a persona: for elements 0..6, 8, 9 the affinity word
// (sub_1733B0) -> sprite 13 (bit 26), 14 (25), 12 (24), 11 (28), 10 (27), else 15 of 0x833B98 (jump table 0x7B5B90).
void sub_128480(EEContext& ctx);  // 0x128480
// (xy, row, value, next, alpha): a stat bar: labels 20 / 21, the bar sprite 24 scaled to 227 * value / 99, and when
// `next` is non-zero the gain bar 16 after it.
void sub_129160(EEContext& ctx);  // 0x129160
// (xy, ?, persona, alpha): the persona status table: the nine labels (sub_1281E0), the resistances (sub_128480), the
// frame sprites, and the "next exp" text (sprintf of the level-99 string or of sub_173340 - sub_173330) drawn
// through ...
void sub_12BCE0(EEContext& ctx);  // 0x12BCE0
// (equip work): the equipment screen's scrolling backdrop: while its tween (work +704, sub_18B700) is active, sprite
// 29 of file +688 twice, 700 px apart, the scroll x (tween +48) moving by -1 and wrapping at -700.
void sub_12DDC0(EEContext& ctx);  // 0x12DDC0
// (bits): the index of the lowest set flag of an equipment mask: bits 0..7 and 8..15 -> 0..7, bit 16 -> 9, 17 -> 10,
// 18 -> 11, 19 / 20 -> 13, none -> 0.
void sub_12DF50(EEContext& ctx);  // 0x12DF50
// (file, first sprite, xy, z, r, g, b, alpha, value, digits): draws `value` with 1..3 digit sprites (first + digit),
// colour bytes +48..+50 of each handle; digits 3 forces the hundreds, 2 the tens.
void sub_12E170(EEContext& ctx);  // 0x12E170
// Destroy of "H_CampSoubi1Draw": the three tween / list blocks +696..+704 (RwFree), the two sprite files +688 /
// +692, the file +0, the work.
void sub_130E40(EEContext& ctx);  // 0x130E40
// [H_Camp_CreateSoubi1DrawTask] (parent, priority, xy, pc): creates the equipment screen "H_CampSoubi1Draw"
// (708-byte work, update sub_12C430): +8/+12 position, +18 the party member, +20 = 1.
void sub_130F20(EEContext& ctx);  // 0x130F20
// qsort comparator of equipment-stock indices (u16 pointers): by the item id of the hero stock entry (sub_16F630(1,
// index), datGetEquipmentItemId); -1 / 0 / 1.
void sub_131000(EEContext& ctx);  // 0x131000
// (out, ?, owner, kind): collects the indices 0..299 of the owner's equipment stock (sub_16F630) holding an item
// whose flags (sub_1712D0) have bit 0x20 (usable by the hero: 32 << (pc - 1)) and whose kind (sub_171250: id / 1000)
// is ...
void sub_131090(EEContext& ctx);  // 0x131090
// (xy, ?, persona, fade): the persona status page used by the facility screens: the table (sub_12BCE0), the frame,
// the arcana card, the level (sub_124E60) and the name (sub_124FD0) at alpha 255 - fade.
void sub_1332F0(EEContext& ctx);  // 0x1332F0
// Destroy of "H_CampStatusPersonaDraw" (persona screen): the three sprite files +88.., two blocks +100 / +104, the
// file +80, the work.
void sub_1335D0(EEContext& ctx);  // 0x1335D0
// [H_Camp_CreateCampStatusPersonaDrawTask] (parent, priority, xy, pc): creates the persona screen
// "H_CampStatusPersonaDraw" (108-byte work, update sub_1311D0): +16/+20 position, +24 the party member.
void sub_1336B0(EEContext& ctx);  // 0x1336B0
// [H_Camp_UpdatePersonaDispCtlDrawTask] Update of "CampPersonaDispCtlDraw" (a persona picture): as sub_11B0B0 with
// the build at +32, the file at +36, the texture at +40 and the path at +44 ("_h_camp_persona.c", 960); starting a
// load also sets the slide-in floats +20 / +24 / ...
void sub_133780(EEContext& ctx);  // 0x133780
// Destroy of "CampPersonaDispCtlDraw": as sub_11B210 on its offsets.
void sub_133900(EEContext& ctx);  // 0x133900
// [H_Camp_CreatePersonaDispCtlDrawTask] (parent, priority, persona, ?, z in $f12): creates "CampPersonaDispCtlDraw"
// (300-byte work): +4 persona, +12, +16 z.
void sub_1339A0(EEContext& ctx);  // 0x1339A0
// (task): draws the persona picture once loaded (state 3, persona set): the slide value +24 eases toward 60.0 by the
// growing step +20 (+5 per frame), then sub_114450(texture +12, .., 640, 640, +40).
void sub_133A80(EEContext& ctx);  // 0x133A80
// [H_Camp_PersonaDispCtlSetPersona] (task, persona, ?): when either value changed, releases the current picture as
// sub_133900 and restarts the loader.
void sub_133B80(EEContext& ctx);  // 0x133B80
// Update of "CampPersonaDispCtlFree": polls the texture build (sub_10C3A0); when done prints "*** RELEASE KEY",
// releases the texture (sub_4D0F00) and the file (H_Cdvd_Destroy) and returns -1; 0 while it runs.
void sub_133C40(EEContext& ctx);  // 0x133C40
// Destroy of "CampPersonaDispCtlFree": frees the work.
void sub_133D00(EEContext& ctx);  // 0x133D00
// [H_Camp_CreatePersonaDispCtlFreeTask] (build, file): creates a parentless "CampPersonaDispCtlFree" task (8-byte
// work: build, file) that waits for a texture build and releases it; prints "*** REQ KEY RELEASE".
void sub_133D30(EEContext& ctx);  // 0x133D30
// [H_Camp_UpdateComuFileTask] The social-link screen's file loader (jump table 0x7B5CA0): camp/camp_comu.pak -> 11
// sprite files (work +208.., then the table 0x833B40), camp/camp_card.pak -> 23 card texture builds (sub_10C1A0,
// "_h_camp_comu.c" 203) whose results go ...
void sub_134A10(EEContext& ctx);  // 0x134A10
// Destroy of the social-link file loader: the 23 card textures and 11 sprite files, any build still running handed
// to "CampPersonaDispCtlFree" tasks, the pak; frees the work.
void sub_134D80(EEContext& ctx);  // 0x134D80
// (comu task): requests the bust-up picture of the selected social link: releases the previous one (or hands its
// build to a "CampPersonaDispCtlFree" task), then camp/commu/tim2_bustup/i_bust%02X_{a,b}.tmx from the tables
// 0x833A60 / ...
void sub_135120(EEContext& ctx);  // 0x135120
// (comu task): the same for the arcana picture: releases the previous one, requests off_5DB998[sub_16DF30(link)]
// into +348.
void sub_135460(EEContext& ctx);  // 0x135460
// Destroy of "H_CampComuDraw": both pictures (or their builds), the help file +336, message 11 (sub_3C7DD0), the
// work.
void sub_1365B0(EEContext& ctx);  // 0x1365B0
// [H_Camp_CreateComuDrawTask] (parent, priority): creates the social-link screen "H_CampComuDraw" (416-byte work,
// update sub_1355C0) and requests camp/comu/datComuHelp.bmd into +336.
void sub_136750(EEContext& ctx);  // 0x136750
// (xy, alpha, z): the social-link screen's scrolling ribbon: sprite 1 of 0x833B40 twice (1006 px apart, vertical),
// the offset gp-19796 moving by -1 and wrapping at -1106.
void sub_1368A0(EEContext& ctx);  // 0x1368A0
// (xy, link, ?, ?, alpha): the card of a social link: its texture (0x833A80[table 0x5E3220[link] - 1]) through
// sub_114E70 / sub_1140D0, then the "max" / "reversed" / rank-10 overlay sprite.
void sub_137300(EEContext& ctx);  // 0x137300
// (xy, link, alpha): the rank block: two coloured bars (sub_115BC0; grey for sub_172160 / sub_1717C0 links, blue
// otherwise) and "MAX" (rank 10) or the rank digit of sprite font 1.
void sub_138EE0(EEContext& ctx);  // 0x138EE0
// (xy, ?, alpha, link): the bust-up picture with a 20-frame pulse (gp-19800) for the special links.
void sub_1392D0(EEContext& ctx);  // 0x1392D0
// (alpha): the item screen's scrolling ribbon: sprite 58 of 0x833A50 (twice near the wrap), x gp-19808 moving by -1,
// wrapping at -720.
void sub_13BCE0(EEContext& ctx);  // 0x13BCE0
// [H_Camp_ItemUseOnTarget] (item work, target): uses the selected item on the protagonist (0), the n-th party member
// (n) or everyone (-2): sub_17BC20 / sub_17B860 per member (skipping those sub_1C7CE0 rejects); when anything
// happened the stock count drops ...
void sub_13BE50(EEContext& ctx);  // 0x13BE50
// (list, pc, slot): builds the equipment candidate list of a member's slot: the equipped entry first
// (datGetEquipmentIdx(pc, slot)), then every held hero-stock entry the member may use (item flags bit 32 << (pc -
// 1), sub_1712D0) whose ...
void sub_13C240(EEContext& ctx);  // 0x13C240
// (id): the lowest set bit of an item's target / attribute word (sub_170ED0 by kind 0..3); 0 when none.
void sub_13C6A0(EEContext& ctx);  // 0x13C6A0
// (list): builds the equipment-stock list: every held entry of the hero stock (indices 0..299 with an item, ordered
// by item id through qsort / sub_131000) as a 36-byte row from +100: +0 item id, +4 stock index, +20 the lowest of
// the 21 ...
void sub_13CC90(EEContext& ctx);  // 0x13CC90
// (pc, list): builds a member's equipment list by slot (21 categories x 4 slots); +11620 = the count.
void sub_13CF80(EEContext& ctx);  // 0x13CF80
// (item work): after a stock change: rebuilds the list (sub_13CC90) and clamps the scroll (+11628) and cursor
// (+11624) to the new count (5 rows a page).
void sub_141590(EEContext& ctx);  // 0x141590
// (item work, row): restarts the highlight tweens of the cursor row and of row `row` (12 visible rows, y 61 + 29 i).
void sub_145350(EEContext& ctx);  // 0x145350
// Destroy of "H_CampNewItem": the three sprite files +176..
void sub_14ED20(EEContext& ctx);  // 0x14ED20
// [H_Camp_CreateNewItemTask] (parent, priority): creates the item screen "H_CampNewItem" (200-byte work, update
// sub_14C5C0), requests camp/camp_item.pak (+8), state 2.
void sub_14EE80(EEContext& ctx);  // 0x14EE80
// (system work): the system menu's slide-in tweens (eight panels, mode 2 / kind 1; the cursor at y 124 + 33 row).
void sub_14EF60(EEContext& ctx);  // 0x14EF60
// (system work): the system menu's slide-out tweens on the same records.
void sub_14F320(EEContext& ctx);  // 0x14F320
// (kind, id): whether an entry is unlocked: the table at gp-19768 (12-byte rows, 0-terminated: kind, id, flag) with
// datGetFlag, kind 3 / +8 == 19 always; then the 256 day-event records (sub_17AE30).
void sub_14F680(EEContext& ctx);  // 0x14F680
// Destroy of "H_CampSystemMenuDraw" / "H_ConfigMenuDraw": texture +32, sprite files +20 / +24, blocks +12 / +16,
// messages 8 and 12, the three files +36.., the work.
void sub_154770(EEContext& ctx);  // 0x154770
// [H_Camp_CreateSystemMenuDrawTask] (parent, priority): creates "H_CampSystemMenuDraw" (380-byte work, update
// sub_14F7D0); The Answer starts on entry 4.
void sub_1548A0(EEContext& ctx);  // 0x1548A0
// [H_Camp_CreateConfigMenuDrawTask] (parent): creates "H_ConfigMenuDraw" (the title screen's config, update
// sub_15B430) and its own camp sprite set-up (sub_119F10(task, 1)).
void sub_15C460(EEContext& ctx);  // 0x15C460
// [H_Camp_SkillUseOnTarget] (skill work, target): casts the selected healing skill from the camp (protagonist 0, the
// n-th member, everyone -2): sub_17B860 per member, then the caster pays the cost (HP / SP through sub_16CF40 /
// sub_16CF90).
void sub_15C520(EEContext& ctx);  // 0x15C520
// (xy, alpha, z): the skill screen's scrolling ribbon: sprite 12 of 0x833A50, x gp-19812 moving by -1, wrapping at
// -640.
void sub_15D8E0(EEContext& ctx);  // 0x15D8E0
// Destroy of "H_NewCampSkillDraw": blocks +56 / +40, the three sprite files +28..
void sub_1616D0(EEContext& ctx);  // 0x1616D0
// [H_Camp_CreateNewCampSkillDrawTask] (parent, priority): creates the skill screen "H_NewCampSkillDraw" (80-byte
// work, update sub_160800) and requests camp/camp_skil.pak (+48).
void sub_1617D0(EEContext& ctx);  // 0x1617D0
// Destroy of "H_CampFrStatusRoot": frees the work.
void sub_161D60(EEContext& ctx);  // 0x161D60
// Destroy of "H_CampPartyStatusDraw": texture +28, sprite files +32 / +36, the pak +24, blocks +44 / +48, the work.
void sub_1669B0(EEContext& ctx);  // 0x1669B0
// [H_Camp_CreatePartyStatusDrawTask] (parent, priority, member, ?, mode): creates "H_CampPartyStatusDraw" (56-byte
// work, update sub_164920) and requests the member's camp/camp_fr%02d.pak (The Answer: AGS_camp_fr03 for members 1 /
// 3, AGS_camp_fr09 for 9).
void sub_166A50(EEContext& ctx);  // 0x166A50
// Destroy of "H_CampPartyStatusRoot": frees the work.
void sub_1675B0(EEContext& ctx);  // 0x1675B0
// [H_Camp_UpdateFrStatusDispTask] Update of "H_FRStatusDisp" (the party-status screen a script opens): state 0 sets
// flag 0x1407, the camp_status.pak set-up ("H_CampStatusSprSetupFile") and the flash draw (sub_168770); 1 waits for
// both, then creates ...
void sub_1675E0(EEContext& ctx);  // 0x1675E0
// Destroy of "H_FRStatusDisp": gp-19816 = 0, flag 0x1407 cleared, the work freed.
void sub_1678E0(EEContext& ctx);  // 0x1678E0
// Destroy of "H_CampFrStatusPersonaDraw": frees the work.
void sub_167EC0(EEContext& ctx);  // 0x167EC0
// [H_Camp_CreateFrStatusPersonaDrawTask] (parent, priority, xy, a, b, c): creates "H_CampFrStatusPersonaDraw"
// (44-byte work, update sub_167930).
void sub_167F40(EEContext& ctx);  // 0x167F40
// COMM: opens the party-status screen of member scrGetIntPara(0) ("H_FRStatusDisp", mode 0) into gp-19820; returns
// 1.
void sub_168040(EEContext& ctx);  // 0x168040
// COMM: the same with mode 1 (the party-status root).
void sub_168100(EEContext& ctx);  // 0x168100
// [H_Camp_UpdateFrStatusFlashTask] Update of "H_FrStatusFlashDraw" (jump table 0x7B62E0): loads camp/anm_status.pak,
// then plays the nakama01 / 07 / 09 / equ_trade01 transitions chosen by sub_1685E0 (+12), keeps the shown .anm
// (+20), counts the close (+4).
void sub_168220(EEContext& ctx);  // 0x168220
// [H_Camp_FrStatusFlashRequest] (task, screen): picks the party-status transition for (shown screen +8, new screen)
// and sets the state / kind.
void sub_1685E0(EEContext& ctx);  // 0x1685E0
// Destroy of "H_FrStatusFlashDraw": the pak +16, the work.
void sub_168720(EEContext& ctx);  // 0x168720
// [H_Camp_CreateFrStatusFlashTask] (parent, priority): creates "H_FrStatusFlashDraw" (28-byte work, update
// sub_168220).
void sub_168770(EEContext& ctx);  // 0x168770
// Destroy of "H_CampTradeDraw": blocks +28 / +32, the two sprite files +20..
void sub_169040(EEContext& ctx);  // 0x169040
// COMM: opens the equipment trade screen "H_CampTradeDraw" for member scrGetIntPara(0) (camp_item.pak) into
// gp-19824; returns 1.
void sub_169330(EEContext& ctx);  // 0x169330
// Destroy of a trade sub-task: block +24, the two sprite files +16.., the file +12, the work.
void sub_169AE0(EEContext& ctx);  // 0x169AE0
// COMM: 1 when the task of gp-19828 is gone or finished (and forgets it), else 0.
void sub_16A6A0(EEContext& ctx);  // 0x16A6A0
// [H_Camp_AllocTweens] (count): RwCalloc(count, 68, 0x40000) -- an array of 68-byte tween records.
void sub_18B6D0(EEContext& ctx);  // 0x18B6D0
// [H_Camp_TweenStart] (record, kind, mode, curve, from xy, to xy, a, b, z in $f12, first frame, last frame): starts
// a tween record: +4 = 1 active, +8 kind, +12 mode, +16 curve, +40 / +48 from / to (two floats each), +0 / +20 the
// two extra words, +36 z, +28 ...
void sub_18BC10(EEContext& ctx);  // 0x18BC10

}  // namespace p3fes::game
