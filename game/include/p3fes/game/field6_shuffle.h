// Phase 5 slice field6, part shuffle (game/src/battle/field6_shuffle.cpp): sfl_root.c and sfl_result.c. Register
// ABI.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

// sflRoot_CreateShuffleRootTasks 0x1F2080:
//   (request) -> the "shuffle root" task: a 172,576-byte work (RwMalloc, gp 0x7CE2DC; +4 / +20 = 0), the task
//   (update sflRoot_UpdateShuffleRootTask, destroy sub_1F2FD0) and its children "shuffle root draw 0"
//   (priority 4207, +12) and "draw 1" (6310, +16); the camera (sub_198590 / sub_4C9F90), the card / ground /
//   pose / script / cursor / count / persona modules initialised (sub_219C90 .
void sflRoot_CreateShuffleRootTasks(EEContext& ctx);
// sflRoot_UpdateShuffleRootTask 0x1F2300:
//   (task) -> 0.
void sflRoot_UpdateShuffleRootTask(EEContext& ctx);
// sflRoot_UpdateShuffleRootDraw0Task 0x1F2F50:
//   (task) -> 0: the ground draw (sub_23B990).
void sflRoot_UpdateShuffleRootDraw0Task(EEContext& ctx);
// sflRoot_UpdateShuffleRootDraw1Task 0x1F2F80:
//   (task) -> 0: the 2D draws -- sub_254B90, sub_25BBF0, sub_25A440, the result's cards (sub_1F64C0),
//   sub_2168F0, sub_23E970.
void sflRoot_UpdateShuffleRootDraw1Task(EEContext& ctx);
// sub_1F2FD0 0x1F2FD0 [sflRootDestroyCallback]:
//   (task) the destroy callback of the "shuffle root" task: tail-calls sub_1F2FF0.
void sub_1F2FD0(EEContext& ctx);
// sub_1F2FF0 0x1F2FF0 [sflRootDestroy]:
//   (task) shuts Shuffle Time down: the modules in reverse (sub_27BBA0, sub_25B4B0, the result sub_1F5950, ..
//   sub_20E030), the message windows (sub_3C77A0), the work freed (RwFree) and gp 0x7CE2DC = 0.
void sub_1F2FF0(EEContext& ctx);
// sub_1F30F0 0x1F30F0 [sflRootSetupCamera]:
//   (task) the card table's camera set-up: the field camera (sub_198590 / sub_4C9D70), sub_21A840, root work
//   +228 = 0, the two pose objects +49204 / +49304 at (0, 100, 0) and (0, 100, 200) (sub_24FD10 / sub_24F9F0 /
//   sub_24DA60 / sub_24F090), the camera pose +48936 between them (sub_24D8D0 .
void sub_1F30F0(EEContext& ctx);
// sub_1F3270 0x1F3270 [sflRootBuildDeal]:
//   (task) builds the deal: the card counts and rates of the hero's level band (sub_209E10 .
void sub_1F3270(EEContext& ctx);
// sub_1F4750 0x1F4750 [sflRootShowPick]:
//   (task) the pick's message: by the picked card's kind (sub_256030 +4) -- 2 blank: message 4 and the sound
//   (sub_10A4E0(1, 15, 6, 11)); 1 arcana: the arcana's name and its effect text (0x684610[card +8]) in message
//   0; 0 persona: message 2 + sound when it is a penalty card (sub_2561C0), else the persona's name with
//   message 3 (already owned, sub_1F5760) or 1.
void sub_1F4750(EEContext& ctx);
// sub_1F4A00 0x1F4A00 [sflRootBuildShuffle]:
//   (no args) builds the shuffle command script (K_Assert sfl_root.c 254 without the root work): root +4 |=
//   0x20, the hero's persona refreshed (sub_173660 / sub_1732F0), the script buffer at +125328 (1,024 bytes,
//   sub_259690); from the level band's rates (6-byte rows of sub_209E80 [+130388] and 3-byte rows of
//   sub_209E90 [+130392]) the counts of swaps / closes / outs / acts are rolled (RpRandom, soft double fptodp
//   for the printf'd "%f" values: "swap", "close", "out", "act", "cnt_act", "max_act", "val_act") and written
//   as SWAP / CLOSE / OPEN / WAIT / SPEED / START_ACT commands (sub_259B00 .
void sub_1F4A00(EEContext& ctx);
// sub_1F53A0 0x1F53A0 [sflRootGoResult]:
//   (no args) after the pick: from states 17 / 21 (others K_Assert sfl_root.c 2371) -- a blank card (flag
//   0x1000) shows its message (sub_1F54A0, state 24); else the result starts (sfl_result's sub_1F59B0) and
//   state 22.
void sub_1F53A0(EEContext& ctx);
// sub_1F54A0 0x1F54A0 [sflRootBlankMessage]:
//   (no args) the blank-card message 50 with its sound (sub_10A4E0(1, 15, 6, 12)); root state 24.
void sub_1F54A0(EEContext& ctx);
// sub_1F55E0 0x1F55E0 [sflRootStopShuffle]:
//   (no args) stops the shuffle: sub_255F80, sub_25A7D0, sub_23F3E0, sub_25B4F0; root state 11.
void sub_1F55E0(EEContext& ctx);
// sub_1F5950 0x1F5950 [sflResultDestroy]:
//   (no args) sfl_result's shutdown (K_Assert sfl_result.c 140 without the work, gp 0x7CE2E0): the pages
//   released (sub_1F98D0), the result script released (scrReleaseScript(+13508)), the slot cleared.
void sub_1F5950(EEContext& ctx);
// sub_1F59B0 0x1F59B0 [sflResultStart]:
//   (no args) starts the result: flags 1 | 2, +16 = 0, +24 = 100, +13504 = 0, the result script loaded from
//   the embedded BF 0x684850 (sub_35BD20 -> +13508); mode +8 = (kind-1 count +13340 + kind-0 count +13336 >=
//   2).
void sub_1F59B0(EEContext& ctx);
// sub_1F5B20 0x1F5B20 [sflResultUpdate]:
//   (no args) the result's per-frame update (K_Assert sfl_result.c 140): flag 2 is a one-frame delay; with
//   flag 1: the 30-frame card fades (flag 0x100: +13516 = 256 x t or 256 x (1 - t) by +13512, +13520 the
//   frame; flag 0x200: the reward card's move +13524..+13532), then the result step +4 (jump table 0x7B6EC0):
//   the pages (sub_1F6630 / sub_1F6A60 / sub_1F6E80), the message windows, the field pack release (sub_1B07D0
//   / sub_1B0840), the persona list (sub_1F7170 / sub_1F9100 / sub_1F7030 / sub_1F70D0), the reward
//   (sub_1F9C60, sub_34FCF0, the roll sub_1F7210) and the end (scrForceTraceCode, sub_20CC80 .
void sub_1F5B20(EEContext& ctx);
// sub_1F64C0 0x1F64C0 [sflResultDrawCards]:
//   (no args) draws the result cards in mode 1 when flags 1 and 0x400 are set: the kind-1 entries (+60
//   [+13340]) then the kind-0 entries (+28 [+13336]), each entry's card at entry +104 (sub_20B250).
void sub_1F64C0(EEContext& ctx);
// sub_1F6630 0x1F6630 [sflResultBuildLists]:
//   (no args) builds the result lists (K_Assert sfl_result.c 140): clears the counters +13312..+13332; the
//   kind-1 (persona) entries go to the "new personas" list +13296 when the stock has room (sub_1756F0 + n <=
//   sub_175410; K_Assert 626 for more than 8), else flag 0x10 (stock full); flag 8 when there are any; the
//   kind-0 (arcana) entries are applied (sub_209F00 / sub_20C590 / sub_20A800 / sub_20C5F0) and their cards
//   placed (sub_20D630 / sub_4BDDE0 / sub_20D690 / sub_24FD80 ..); then the first page (sub_1F6A60).
void sub_1F6630(EEContext& ctx);
// sub_1F6A60 0x1F6A60 [sflResultNextPage]:
//   (no args) picks the next result page from step +4 (jump table 0x7B6EF0), falling through the empty ones: 1
//   the new personas (flag 8: sub_1F99F0), 2 the stock-full notice (flag 0x10 -> step 3), 4 / 5 the persona
//   lists (sub_1F7030 / sub_1F70D0), the reward (sub_1F9A80), the end (sub_3C77A0, sub_1831E0,
//   scrForceTraceCode, the help message sub_20E790 / sub_3C72D0).
void sub_1F6A60(EEContext& ctx);
// sub_1F6E80 0x1F6E80 [sflResultShowPersona]:
//   (no args) shows new persona +13324: in mode 1 the entries' cards line up at x = 320 + 220 (i - current), y
//   = 184 (sub_20C500 / sub_20C400, the FPU accumulator), their effects follow (sub_2508C0, z + 100); the
//   persona's name in message 9; flag 0x40 on the last one; the sound (sub_10A4E0(1, 0, 6, 10)).
void sub_1F6E80(EEContext& ctx);
// sub_1F7030 0x1F7030 [sflResultShowListA]:
//   (no args) message 14 with the hero's name (sub_1775A0(1)) and the persona of list +13280 [+13328]; step 5.
void sub_1F7030(EEContext& ctx);
// sub_1F70D0 0x1F70D0 [sflResultShowListB]:
//   (no args) message 16 with the hero's name and the persona of list +13296 [+13332]; step 6.
void sub_1F70D0(EEContext& ctx);
// sub_1F7170 0x1F7170 [sflResultRegisterPersonas]:
//   (no args) registers every kind-1 entry's persona (sub_217590(entry +96)) and sub_215B00; step 4.
void sub_1F7170(EEContext& ctx);
// sub_1F7210 0x1F7210 [sflResultRollReward]:
//   (no args) the reward roll of an arcana card (K_Assert sfl_result.c 140; five jump tables): by the card's
//   suit -- sword (a weapon), coin (money), wand (an item), cup (healing / social stats) -- and its rank,
//   rolls RpRandom against the rate tables (sub_209C40 .
void sub_1F7210(EEContext& ctx);
// sub_1F9100 0x1F9100 [sflResultCommitPersonas]:
//   (no args) commits the result's persona lists: sub_217410(+13296, +13316), sub_2174D0(+13280, +13312),
//   sub_216800().
void sub_1F9100(EEContext& ctx);
// sub_1F9170 0x1F9170 [sflCardCondition]:
//   (condition row) -> 1 when one of the 13 conditions of row n of sub_209D00's table (26-byte rows, a byte
//   per condition) holds: 0 / 1 the hero's / a member's HP below max (sub_16C4F0 < sub_16C5F0; members from
//   sub_1F1DF0), 2 / 3 SP below max (sub_16C570 / sub_16C670), 4 / 5 a bad status (sub_16C970 & 0x80), 7 / 8
//   status 3..5 (sub_16C920), 9 / 10 not status 1 / 2, 11 / 12 not status 2; else 0.
void sub_1F9170(EEContext& ctx);
// sub_1F98D0 0x1F98D0 [sflResultRelease]:
//   (no args) releases what sub_1F59B0 requested when flag 0x80: mode 1 frees every entry's texture
//   (sub_21A670 / sub_21A760), mode 0 rebuilds the lists (sub_1F6630); the flag is cleared.
void sub_1F98D0(EEContext& ctx);
// sub_1F99F0 0x1F99F0 [sflResultPageNewPersonas]:
//   (no args) the new-personas page: +13324 = 0, in mode 1 the card fade-in (+13512..+13520, flag 0x100), the
//   first persona shown (sub_1F6E80); step 2.
void sub_1F99F0(EEContext& ctx);
// sub_1F9A80 0x1F9A80 [sflResultPageReward]:
//   (no args) the reward page: in mode 1 the kind-0 cards are scaled (10, 10, 10), lined up at x = 320 + 220
//   i, y = 184, z + 100, turned (sub_4BDDE0 / sub_20D690), the reward move reset (+13524..+13532, flag 0x200)
//   and, with personas shown, the fade-out (+13512 = 1, flag 0x100); the roll (sub_1F7210); step 7.
void sub_1F9A80(EEContext& ctx);
// sub_1F9C60 0x1F9C60 [sflResultSetupRewardEffect]:
//   (no args) sets up the reward effect object +13536: colour (-1 x 4), sub_34FF70, position (0, 120, 200),
//   sub_34FE30, sub_34FD30, sub_34FD70(.., 7).
void sub_1F9C60(EEContext& ctx);

}  // namespace p3fes::game
