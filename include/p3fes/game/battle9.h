// The battle code, ninth pass (slice battle9; docs/ANALYSIS/21_battle.md): the boss-encounter scripts of
// 0x2F0580-0x2FB850 -- the per-encounter hooks the battle states call through their encounter switches, and the
// scene / done / formation / unit-init callbacks the hooks' tables and the event tasks point to. Every body comes from
// p3fes_handgen (register ABI: arguments in $a0.., the result in $v0) and is made readable on top of that: the record
// offsets are named (bcore:: from battle_core2.h for gBtl, btlAction, btlUnit and the btl packets; b9:: below for the
// boss work and this file's own readings) and each function's role is given. Names: functions.json's in code, ours in
// brackets in the comments (ADR-0009). Still-recompiled callees are reached through their gen:: entry points.
//
// The encounter id is the u16 at *(gBtl + 3004) + 8 (b9::kEncId). Ids 416..436 and 456 are the scripted boss
// encounters; the enemy (btlUnit +164) ids the hooks look for, by encounter:
//   424: 269 (the boss), 278..280 (its adds)       425: 264      426: 271      427: 272      429: 274
//   430: 294      431: 233      432: 234      434: 235..240 (six)      436: 241 / 242
//
// Groups:
//   * dispatch: sub_2FB690 (ENEMY_DEAD init: the boss's death scene by encounter), sub_2FACC0 (START init: the boss
//     archive's effect file played on the hero; 417 / 422 / 424 / 416 call their own starters), sub_2F7DC0 / sub_2F8460
//     (the encounter's BED handles at gBtl +2884.. bound / freed), sub_2F88C0 (the encounter's turn query), sub_2F8A40
//     (is this unit the encounter's boss), sub_2FAC80 (UNIT_CREATE: sub_29A690 [btlOrderSortBySide], then sub_29A470
//     [btlOrderMoveToFront] on the hero's action);
//   * formations (the 0x2FA240 table): the party's cells (a 3-row f32 {x, z} table and a u16[3] slot list per
//     encounter; the hero, party id 1, at a fixed cell) and the enemies' cells, through sub_2D2280 (cell) and
//     sub_27F650 (place);
//   * unit init (the 0x2F9C10 table): the boss unit's flags (0x100 | 0x40 | 0x80 / 0x400 / 0x2000),
//     sub_288F80(unit, n) and the boss work's first values;
//   * scenes: chains of btl packets (sub_27ED20 queues them; a packet's first wait condition names the id of the
//     packet it follows: kind 4 after the start, 5 after the end, 11 another of sub_27E530's kinds). Each "done"
//     callback (sub_2F0580 and kin) returns 1 while the action still owns queued packets (sub_27E390
//     [btlPacketFindByOwner]), then finishes the scene: kills / removes actions (sub_2D7890, sub_29A320), sets gBtl flag 0x2000000 and queues the three closing
//     packets (sub_29FA50 / sub_2A1080 / sub_2A16C0);
//   * camera shots: sub_2F6330 / sub_2F6510 (the boss camera callbacks: two {position, target} pairs per shot).
//
// THE BATTLE STATE A CO-OP SERVER WOULD OWN (additions to battle3.h .. battle7.h's lists)
//   * the boss work (gBtl +2884 .. +2912): the phase counter, the copied party member (432), the fade timers (436) --
//     all battle logic, drawn partly from datCalcRand (sub_2F2890's camera set, sub_2F5030's member pick): server side.
//   * the summons (sub_2F05F0: datUnitEcAddEnemy), the kills and removals of the done callbacks, the DatUnit id /
//     HP / SP rewrite of the Nyx arcana change (sub_2F3190): server logic. The packets, cameras and BED effects are
//     presentation.

#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/battle_core2.h"

namespace p3fes::game {

namespace b9 {

// --- gBtl (bcore:: has the rest) -----------------------------------------------------------------------------------
inline constexpr s32 kBtlFlags24 = 24;        // u16: |= 7 at the end of the Nyx / boss-add scenes (meaning not read)
inline constexpr s32 kBtlPartyTail = bcore::kBtlUnitTail;      // u32: side 0's list tail (walk +2612 kUnPrev)
inline constexpr s32 kBtlEnemyTail = bcore::kBtlUnitTail + 8;  // u32: side 1's list tail
inline constexpr s32 kBtl2818 = 2818;         // u16: sub_2E30A0's first argument (sub_2F3A80's voice line)
inline constexpr s32 kBtlBossArchive = 2836;  // u32: the boss archive H_Cdvd_ArchiveGetFile reads (file 1, 456: 0)
inline constexpr s32 kBtl3240 = 3240;         // u32: sub_2BB2F0's first argument (sub_2F05F0's summon effect)
inline constexpr s32 kEncId = 8;              // u16 at *(gBtl + 3004) + 8: the encounter id
// the boss work: its words mean what the encounter's scripts make of them
inline constexpr s32 kBoss2884 = 2884;  // u32[4]: the encounter's BED handles (sub_2F7DC0) / 424: the listed actions
inline constexpr s32 kBoss2888 = 2888;  // u16 / u32: the phase counter (Nyx's arcana index, 274's stage) / a BED handle
inline constexpr s32 kBoss2892 = 2892;  // u32: a BED handle / the scene argument (sub_2F2450 copies the event's +32)
inline constexpr s32 kBoss2896 = 2896;  // u16: 424's listed-action count / 436: the fade mode / a BED handle
inline constexpr s32 kBoss2900 = 2900;  // u32 / u16: 432: the copied party id; 436: the fade countdown
inline constexpr s32 kBoss2902 = 2902;  // u16: 436: the fade length (frames)
inline constexpr s32 kBoss2904 = 2904;  // u32 / u16: 432: the copy's skill id (224..231); 436: the fade frame
inline constexpr s32 kBoss2908 = 2908;  // u16[11]: 432: copies by party id; sub_2F6510: the shot's skill (-1 used)
inline constexpr s32 kBoss2910 = 2910;  // u16: 432: the hero's copy count (= 1 at the start)
inline constexpr s32 kBoss2912 = 2912;  // u32: 1 once 424's navigator line ran
inline constexpr s32 kBoss2944 = 2944;  // u32: 1 once sub_2F6330's camera shot ran

// --- btlAction (bcore:: has the rest) --------------------------------------------------------------------------------
inline constexpr s32 kActTargets = 56;       // u32[]: the target actions (bcore::kActTarget's record)
inline constexpr s32 kActTargetCount = 106;  // u16: their count
inline constexpr s32 kActCmdKind = 108;      // u16: the command kind (2 = a skill)
inline constexpr s32 kActSkill = 110;        // u16: the command's skill id (343: the special that sub_2F39B0 checks)

// --- btl packet wait / end conditions (bcore::kPktStart / kPktEnd: 16-byte {u8 kind, u64 arg} pairs) -----------------
inline constexpr s32 kPktWaitKind0 = 0;   // u8: 4 after the named packet started, 5 after it ended (11 also used)
inline constexpr s32 kPktWaitId0 = 8;     // u64: the packet's id (+88)
inline constexpr s32 kPktWaitKind1 = 16;  // u8: the second start condition
inline constexpr s32 kPktWaitId1 = 24;    // u64
inline constexpr s32 kPktEndKind0 = 32;   // u8: the first end condition
inline constexpr s32 kPktEndId0 = 40;     // u64

}  // namespace b9

// The register-ABI bodies, by address (game/src/battle/battle9.cpp gives each one's role).
void sub_2F0580(EEContext& ctx);  // 0x2F0580 done: the summon scene
void sub_2F05F0(EEContext& ctx);  // 0x2F05F0 scene: the summon of three enemies
void sub_2F0E30(EEContext& ctx);  // 0x2F0E30 done (same as sub_2F0580)
void sub_2F0EA0(EEContext& ctx);  // 0x2F0EA0 scene: 424's listed actions
void sub_2F14A0(EEContext& ctx);  // 0x2F14A0 done: 424's listed actions killed
void sub_2F1680(EEContext& ctx);  // 0x2F1680 formation: 425 (enemy 264)
void sub_2F1810(EEContext& ctx);  // 0x2F1810 death scene: 425
void sub_2F19D0(EEContext& ctx);  // 0x2F19D0 formation: 426 (enemy 271)
void sub_2F1D40(EEContext& ctx);  // 0x2F1D40 death scene: 426
void sub_2F1F00(EEContext& ctx);  // 0x2F1F00 formation: 427 (enemy 272)
void sub_2F2090(EEContext& ctx);  // 0x2F2090 death scene: 427
void sub_2F2250(EEContext& ctx);  // 0x2F2250 formation: the hero at (150, 500), the enemies at (0, -500)
void sub_2F2450(EEContext& ctx);  // 0x2F2450 event start: sub_2F2550 / sub_2F2840
void sub_2F2490(EEContext& ctx);  // 0x2F2490 event start: sub_2F2890 / sub_2F2B40
void sub_2F2550(EEContext& ctx);  // 0x2F2550 scene: the enemy effect 102
void sub_2F2840(EEContext& ctx);  // 0x2F2840 done: 1 while packets remain
void sub_2F2890(EEContext& ctx);  // 0x2F2890 scene: the enemy effect 103
void sub_2F2B40(EEContext& ctx);  // 0x2F2B40 done: 1 while packets remain
void sub_2F2B90(EEContext& ctx);  // 0x2F2B90 scene: NYX_TAROT_CHANGE
void sub_2F3190(EEContext& ctx);  // 0x2F3190 done: the arcana change applied
void sub_2F3320(EEContext& ctx);  // 0x2F3320 scene: an enemy's exit with E1AC_99.ADX
void sub_2F3520(EEContext& ctx);  // 0x2F3520 done: the exiting action killed and removed
void sub_2F3670(EEContext& ctx);  // 0x2F3670 unit init: 429
void sub_2F3760(EEContext& ctx);  // 0x2F3760 formation: the hero at (0, 500), the enemies at (0, -500)
void sub_2F3840(EEContext& ctx);  // 0x2F3840 death scene: 429
void sub_2F39B0(EEContext& ctx);  // 0x2F39B0 action hook: 274's phase scene / skill 343's
void sub_2F3A80(EEContext& ctx);  // 0x2F3A80 scene: 274's phase attack
void sub_2F43A0(EEContext& ctx);  // 0x2F43A0 done: the turn order resumes
void sub_2F4410(EEContext& ctx);  // 0x2F4410 scene: skill 343 kills sub_29A1D0's action
void sub_2F4490(EEContext& ctx);  // 0x2F4490 unit init: 430 (enemy 294)
void sub_2F4540(EEContext& ctx);  // 0x2F4540 formation: 430
void sub_2F46D0(EEContext& ctx);  // 0x2F46D0 death scene: 430
void sub_2F4890(EEContext& ctx);  // 0x2F4890 unit init: 431 (enemy 233)
void sub_2F4950(EEContext& ctx);  // 0x2F4950 formation: 431
void sub_2F4A40(EEContext& ctx);  // 0x2F4A40 death scene: 431
void sub_2F4C00(EEContext& ctx);  // 0x2F4C00 unit init: 432 (enemy 234)
void sub_2F4CE0(EEContext& ctx);  // 0x2F4CE0 formation: 432
void sub_2F4E70(EEContext& ctx);  // 0x2F4E70 death scene: 432
void sub_2F5030(EEContext& ctx);  // 0x2F5030 432: the party member the boss copies next
void sub_2F5330(EEContext& ctx);  // 0x2F5330 unit init: 434 (enemies 235..240)
void sub_2F5490(EEContext& ctx);  // 0x2F5490 formation: 434
void sub_2F5660(EEContext& ctx);  // 0x2F5660 scene: one of 434's enemies leaves
void sub_2F5870(EEContext& ctx);  // 0x2F5870 done: the leaving action killed and removed
void sub_2F5980(EEContext& ctx);  // 0x2F5980 unit init: 436 (enemies 241 / 242)
void sub_2F5A70(EEContext& ctx);  // 0x2F5A70 formation: as sub_2F2250 (table 0x69A550)
void sub_2F5D80(EEContext& ctx);  // 0x2F5D80 436: enemy 242's fade, per frame of enemy 241
void sub_2F6120(EEContext& ctx);  // 0x2F6120 death scene: 436 (E1B4_99.ADX)
void sub_2F6330(EEContext& ctx);  // 0x2F6330 camera shot: on enemy 241
void sub_2F6510(EEContext& ctx);  // 0x2F6510 camera shot: by the shot's skill
void sub_2F6840(EEContext& ctx);  // 0x2F6840 scene: 436's enemy turn (242's fade armed)
void sub_2F6AB0(EEContext& ctx);  // 0x2F6AB0 done: 436's scene
void sub_2F7DC0(EEContext& ctx);  // 0x2F7DC0 the encounter's BED handles bound
void sub_2F8460(EEContext& ctx);  // 0x2F8460 the encounter's BED handles freed
void sub_2F88C0(EEContext& ctx);  // 0x2F88C0 the encounter's turn query
void sub_2F8A40(EEContext& ctx);  // 0x2F8A40 is this unit the encounter's boss
void sub_2FAC80(EEContext& ctx);  // 0x2FAC80 UNIT_CREATE hook
void sub_2FACC0(EEContext& ctx);  // 0x2FACC0 START hook
void sub_2FB690(EEContext& ctx);  // 0x2FB690 ENEMY_DEAD hook

}  // namespace p3fes::game
