// Phase 5 slice shuffle: Shuffle Time, the card minigame after a battle (docs/ANALYSIS/27_unmapped_bands.md section 3,
// the sfl_* / gc_* files of the battle-UI band 0x1EF500-0x26503C). No replay route reaches it (no snapshot holds a
// "shuffle root" task); tests/game/test_shuffle.cpp pairs every function with its recompiled body on structured
// shuffle worlds, on the replay snapshots and against documented rules.
//
// The bodies (game/src/battle/shuffle.cpp) come from p3fes_handgen and keep the original's registers, frame, spills,
// $ra links, cycle charges and check points (game/include/p3fes/game/hg_cpu.h); the readability pass names offsets and
// documents roles without changing an instruction. Every function keeps its symbols/functions.json name (all sub_*);
// [bracketed] names are proposals. Register ABI: arguments in $a0.. ($f12 for a float), the result in $v0.
//
// The records, by source file (K_Assert strings) and gp slot:
//   sfl_root.c  root work (gp-18964; the "shuffle root" task +60): +0 mode, +4 flags (0x1 result page, 0x80 ground
//               resources requested, 0x100 ground started, 0x1000 persona result), +8 state, +84 / +88 the request's
//               words, +228, +0xC0FC the trigger kind (468 / 469 / other).
//   sfl_result.c result work (gp-18960): +0 flags, +24, +28[8] / +60[8] the entry indices of kind 1 / kind 0 (counts
//               +13336 / +13340), +92 the entries (1,648 bytes each, {kind, a, b, ...}; count +13276, at most 8),
//               +13280 / +13296 two u16 id lists (counts +13312 / +13316).
//   gc_pose.c   pose manager (gp-18864): {head, tail}; a pose object: +0 prev, +4 next, +12 type, +20..+28 position
//               (three singles), +32 state (0..3), +36.
//   sfl_card.c  card work (gp-18844, 0x12890 bytes): +0 flags (0x1 set up, 0x2 dealt, 0x4 selecting, 0x8, 0x10 a
//               command running, 0x40 an animation running, 0x80, 0x100, 0x200 textures requested, 0x400 textures
//               in use, 0x800, 0x1000 random pick, 0x2000); +4 the 16 card records (4,708 bytes each); +0x1265C /
//   +0x12660 the
//               deal list's head / tail; +0x12664 the stack list (count +0x12684); +0x1267C the card count (the next
//               order); +0x12688 the command ring (36-byte entries {kind 0 swap / 1 close / 2 open, speed, cards...},
//               count +0x127A8); +0x127AC the selected order; +0x127B0 the speed; +0x127D4 / +0x12800 two pose
//               objects; +0x12870 the animation state; +0x12884 the random pick.
//               A card record: +0 flags (0x1, 0x2 inside a stack, 0x4 in use, 0x8 a stack, 0x10 spread, 0x20 marked by
//               a queued command, 0x80 has an effect, 0x100 pose objects live, 0x400), +4 kind (0 persona, 1 arcana,
//               2 blank), +8 persona id (u16) / arcana, +12 number, +16 order (among the top-level cards, or inside
//               its stack), +20 slot id, +24 its model, +4032 / +4036 prev / next in the deal list, +4040 the stack it
//               is in, +4044 / +4144 / +4244 / +4344 / +4456 / +4568 six pose objects, +4680 its effect, +4684 /
//               +4688 / +4692 the animation's kind / frame / length.
//   sfl_script.c script work (gp-18840): +0 flags (0x1 running, 0x2 waiting), +4 buffer, +8 pc, +12 write pointer,
//               +16 size, +20 the wait counter; the command table 0x68EAD0 ({handler, u16 argument bytes} x 9: END,
//               SWAP a b, WAIT n, CLOSE a b, OPEN n, wait until nothing is marked, START_ACT, SPEED n, run the act).
//   sfl_cursor.c cursor work (gp-18832): +0 flags, +4.. / +16.. / +28.. positions, +40 frame, +44 / +48 previous /
//               current order, +52 the blink counter, +3232 mode.
//   sfl_count.c count work (gp-18828): +0 flags (0x1 set up, 0x2 running), +4, +8, the digit quads +16 / +784.
//   sfl_psel2.c persona-select page (gp-18808): +0 flags (0x1, 0x2 open), +4 page, +8.
// Shuffle Time's trigger: game counters 57 (battles counted) and 56 (the limit, 24..28): sub_1F56B0 / sub_25B440.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

// --- sfl_root.c: the "shuffle root" task's steps (root work = task +60 = gp-18964) -------------------------
// sub_1F30B0 (task) -> work+4 & 1: the root work's flag 0x1 (task +60 = the "shuffle root" work)
void sub_1F30B0(EEContext& ctx);
// sub_1F30D0 (task): destroys the "shuffle root" task and its children (kwlnTaskDestroyWithHierarchy); called by the
//   result screen when it takes the shuffle hand-off back [sflRootDestroy]
void sub_1F30D0(EEContext& ctx);
// sub_1F4650 (task, request): takes the shuffle request: request +12 / +16 -> work +88 / +84, request +4 (the trigger
//   kind) -> work +0xC0FC; kind 468 -> mode 0, kind 469 -> mode 1 when none of the hero's personas (sub_1756F0 /
//   sub_174A90) is persona 46, else 2; any other kind -> mode 2 (work +0)
void sub_1F4650(EEContext& ctx);
// sub_1F4910 (task) -> work+4 & 0x80: the ground resources requested (set by sub_1F48D0)
void sub_1F4910(EEContext& ctx);
// sub_1F4970 (task) -> work+4 & 0x100: the ground started (set by sub_1F4930)
void sub_1F4970(EEContext& ctx);
// sub_1F4990 () -> bool: kind 468 (work +0xC0FC) and work +228 == 0
void sub_1F4990(EEContext& ctx);
// sub_1F48D0 (task): requests battle/shuffle/sfl_ground.bin (sub_20E2C0) and sets work flag 0x80
void sub_1F48D0(EEContext& ctx);
// sub_1F4930 (task): starts the ground (sub_23C280) and sets work flag 0x100
void sub_1F4930(EEContext& ctx);
// sub_1F5510: ends a persona-card result: raises flag 5137 when work flag 0x1000 is set, passes every id of the
//   result's first u16 list (sub_1F9770) to sub_174B40, state 0, clears work flag 0x1
void sub_1F5510(EEContext& ctx);
// sub_1F5650: card state 4 (sub_259310) and root state 25
void sub_1F5650(EEContext& ctx);
// sub_1F56B0: counts a battle towards Shuffle Time: game counter 57 + 1, or, when it has reached counter 56, 57 = 0
//   and 56 = 24 + RpRandom() % 5 (the same re-arm as sub_25B440) [sflCountBattle]
void sub_1F56B0(EEContext& ctx);
// sub_1F5760 (persona id) -> bool: is the persona among the hero's personas (sub_1756F0 count, sub_174A90 entry +2)
void sub_1F5760(EEContext& ctx);

// --- sfl_result.c: the card result: the entries won, their id lists (gp-18960) -----------------------------
// sub_1F58F0 (work): sfl_result init: K_Assert when gp-18960 is already set, zeroes +0 / +13336 / +13340 / +13276,
//   gp-18960 = work
void sub_1F58F0(EEContext& ctx);
// sub_1F65E0 () -> flags & 1: the result work's flag 0x1
void sub_1F65E0(EEContext& ctx);
// sub_1F6D20 (card info {kind, a, b}): appends a result entry (1,648-byte records from +92; count +13276, < 8): the
//   three words, then its index in the kind's list (kind 1 -> +28[] / +13336, kind 0 -> +60[] / +13340, each < 8)
void sub_1F6D20(EEContext& ctx);
// sub_1F9630: empties the two entry lists (+13336, +13340)
void sub_1F9630(EEContext& ctx);
// sub_1F9680 (card info) -> bool: is there an entry of the same kind with the same id: kind 0 the u16 at +4, kind 1
//   the word at +4 or the word at +8
void sub_1F9680(EEContext& ctx);
// sub_1F9770 (out u16[], out count): copies the u16 list +13280 (count +13312)
void sub_1F9770(EEContext& ctx);
// sub_1F9800 (out u16[], out count): copies the u16 list +13296 (count +13316)
void sub_1F9800(EEContext& ctx);
// sub_1F9890 () -> word: the result work +24
void sub_1F9890(EEContext& ctx);

// --- gc_pose.c: the pose list leaves the cards use (pose manager gp-18864) ---------------------------------
// sub_24DA60 (pose): links a pose object at the tail of the pose list (+0 prev, +4 next; +8 / +16 cleared)
//   [gcPoseRegister]
void sub_24DA60(EEContext& ctx);
// sub_24DAF0 (pose): unlinks a pose object from the pose list, fixing head / tail [gcPoseUnregister]
void sub_24DAF0(EEContext& ctx);
// sub_24F960 (pose, out vec3): the pose's position +20..+28 (K_Assert unless type +12 is 0 and state +32 < 4)
//   [gcPoseGetPos]
void sub_24F960(EEContext& ctx);
// sub_24F9F0 (pose, vec3): sets the position of a type-0 pose in state 0 or 3 (else K_Assert) [gcPoseSetPos]
void sub_24F9F0(EEContext& ctx);
// sub_24FAF0 (pose, vec3): sets the position of a pose in state 0 or 1 (K_Assert from state 2) [gcPoseSetPos1]
void sub_24FAF0(EEContext& ctx);
// sub_24FDA0 (pose): type 1, state 0
void sub_24FDA0(EEContext& ctx);
// sub_24FE00 (pose): type 2, +36 = 3
void sub_24FE00(EEContext& ctx);

// --- sfl_card.c: the cards: records, the deal list, stacks, the command ring, animations (gp-18844) --------
// sub_2534D0 (work): sfl_card init: clears the flags, the list, the counters and the 16 card records (slot id +20 =
//   i), speed +0x12880 = 256, gp-18844 = work [sflCardInit]
void sub_2534D0(EEContext& ctx);
// sub_253560: sfl_card shutdown: releases every card in use (sub_253600), gp-18844 = 0
void sub_253560(EEContext& ctx);
// sub_253600 (card): releases a card's objects: its effect (+4680, sub_34FCF0) when flag 0x80, its six pose objects
//   (sub_24DAF0) when flag 0x100; clears 0x100
void sub_253600(EEContext& ctx);
// sub_2536B0 (arcana, number): deals an arcana card: a free record (sub_255390) linked at the deal list's tail, flag
//   0x4, kind 1, the order = the card count, which grows
void sub_2536B0(EEContext& ctx);
// sub_2537F0 (persona id): deals a persona card (kind 0, u16 id at +8), as sub_2536B0
void sub_2537F0(EEContext& ctx);
// sub_253920: deals a blank card (kind 2), as sub_2536B0
void sub_253920(EEContext& ctx);
// sub_254B90: draws the cards: the leaf models of every top-level card (sub_256FA0), sorted far to near by their
//   distance from the camera (kwlnGetMainCamera, RwFrameGetLTM, RwV3dLength; a bubble sort on the guest frame), each
//   model drawn (sub_20B250)
void sub_254B90(EEContext& ctx);
// sub_254E10: requests the textures of every card in use that is no stack (kind 1: sub_21A920 arcana / number; kind 0:
//   sub_21AB80 persona id); work flags 0x400 | 0x200
void sub_254E10(EEContext& ctx);
// sub_254F20 () -> flags & 0x200: the textures requested
void sub_254F20(EEContext& ctx);
// sub_254F70: sets the cards up: every card of the deal list (sub_258630), +0x12680 = 0, the two work poses (+0x127D4,
//   +0x12800) reset, placed at the table 0x68EA30 position and registered; work flag 0x1
void sub_254F70(EEContext& ctx);
// sub_2550B0: unregisters the two work poses, clears work flag 0x1
void sub_2550B0(EEContext& ctx);
// sub_255130 () -> count: the number of top-level cards (sub_2554F0)
void sub_255130(EEContext& ctx);
// sub_255170 (card): card flag 0x1
void sub_255170(EEContext& ctx);
// sub_255190 (card): +4696 = 0, card flag 0x80
void sub_255190(EEContext& ctx);
// sub_2551B0 (card): card flag 0x400
void sub_2551B0(EEContext& ctx);
// sub_2551D0 (order a, order b): queues a SWAP: dumps the deal list (sub_257E20), marks both cards (flag 0x20,
//   K_Assert when marked already) and appends {kind 0, speed, card a, card b} to the command ring (+0x12688, 36-byte
//   entries, count +0x127A8)
void sub_2551D0(EEContext& ctx);
// sub_255390 () -> card: the first free card record (no flag 0x4; K_Assert when all 16 are used)
void sub_255390(EEContext& ctx);
// sub_255440 (order) -> card: the top-level card (no flag 0x2) with that order (K_Assert when none)
void sub_255440(EEContext& ctx);
// sub_2554F0 () -> count: counts the top-level cards of the deal list
void sub_2554F0(EEContext& ctx);
// sub_255570 (first, n): queues a CLOSE (gathers n cards into a stack): collects the top-level cards by order (fewer
//   than 7, K_Assert), marks the n from order `first`, appends {kind 1, speed, n, the n cards}
void sub_255570(EEContext& ctx);
// sub_255810 (stack index): queues an OPEN (spreads a stack): takes stack (count - 1 - index) out of the stack list
//   (+0x12664[], count +0x12684), marks its children (sub_259190), appends {kind 2, speed, stack}
void sub_255810(EEContext& ctx);
// sub_255F30 () -> flags & 0x10: a command running
void sub_255F30(EEContext& ctx);
// sub_255F80: starts the selection: selected order 0, work flag 0x4 on, 0x8 off
void sub_255F80(EEContext& ctx);
// sub_255FE0: ends the selection (work flag 0x4 off)
void sub_255FE0(EEContext& ctx);
// sub_256030 () -> card: the selected card (order +0x127AC)
void sub_256030(EEContext& ctx);
// sub_256110 (order) -> card: the top-level card with that order (a second copy of sub_255440)
void sub_256110(EEContext& ctx);
// sub_2561C0 (card) -> flags & 1: card flag 0x1
void sub_2561C0(EEContext& ctx);
// sub_2561D0 (card) -> flags & 0x80: card flag 0x80
void sub_2561D0(EEContext& ctx);
// sub_2561E0 ($f12 fade, card): fades a card's colour: each byte c of the colour at gp-26752 becomes (u8)((c - 255) *
//   fade + 255) on the guest frame, set on every leaf model of the card (sub_256F20, sub_20CC80)
void sub_2561E0(EEContext& ctx);
// sub_256430 () -> bool: any card of the deal list marked (flag 0x20)
void sub_256430(EEContext& ctx);
// sub_256F20 (card, out models[], out count): the leaf cards of a card (sub_256FA0) as model pointers (card +24)
void sub_256F20(EEContext& ctx);
// sub_256FA0 (card, out cards[], out count): flattens a stack: a card that is no stack (flag 0x8 clear) is its own
//   leaf; a stack's children (sub_259190) are walked depth-first on a guest-frame stack, the leaves stored in reverse;
//   count = the leaves when the stack has flag 0x10 (spread), else 1
void sub_256FA0(EEContext& ctx);
// sub_257D00 (out pos, column, row?, columns): a card slot's position: the screen x of the column (sub_20C660), y 184,
//   depth 90 unprojected (sub_20C500, sub_20C400), then y += 100
void sub_257D00(EEContext& ctx);
// sub_257D90 (out pos, a1): the centre slot's position: screen (320, 184), depth 200, then y += 100
void sub_257D90(EEContext& ctx);
// sub_257E20: debug dump of the deal list ("dump", each card's slot id and markers) through printf
void sub_257E20(EEContext& ctx);
// sub_257F10: starts the deal animation: every top-level card flips in over 12 frames (sub_250CF0 with the table
//   0x68EA90 axis, the angle gp-32184; anim kind 2), work flags 0x2 | 0x40, state +0x12870 = 0
void sub_257F10(EEContext& ctx);
// sub_258090: work flag 0x2000 on, then turns the selected card (sub_258140)
void sub_258090(EEContext& ctx);
// sub_2580E0: work flag 0x2000 off, then turns the selected card (sub_258140)
void sub_2580E0(EEContext& ctx);
// sub_258140: turns the selected card over (12 frames, the table 0x68EAA0 axis, anim kind 3), work flag 0x40 on, state
//   1, +0x12874 = 0, flag 0x2 off
void sub_258140(EEContext& ctx);
// sub_2582B0 () -> flags & 0x40: a card animation running
void sub_2582B0(EEContext& ctx);
// sub_258300: resets the cards: releases every card in use, the textures (sub_2593D0), the counters and the list; card
//   records free (slot id +20 = i)
void sub_258300(EEContext& ctx);
// sub_258490: work flag 0x8
void sub_258490(EEContext& ctx);
// sub_2584E0 (speed): the command speed (+0x127B0)
void sub_2584E0(EEContext& ctx);
// sub_258540 (order, out vec3): the position of the card with that order (its first pose, sub_24F960)
void sub_258540(EEContext& ctx);
// sub_258A50: plays the cursor sound (sub_10A4E0), state 2, work flags 0x40 | 0x80
void sub_258A50(EEContext& ctx);
// sub_258AF0 () -> flags & 0x80: work flag 0x80
void sub_258AF0(EEContext& ctx);
// sub_258F80 (stack card): breaks a stack up: its children (sub_259190) become top-level cards numbered after the
//   stack's order (later orders move up), placed at the stack's position; the stack card leaves the list and is
//   released (sub_253600); the card count grows by children - 1
void sub_258F80(EEContext& ctx);
// sub_259190 (parent, out cards[], out count): the children of a stack (flag 0x2, parent +4040): out[child order] =
//   child
void sub_259190(EEContext& ctx);
// sub_259250: state 3, work flags 0x40 | 0x100
void sub_259250(EEContext& ctx);
// sub_2592C0 () -> flags & 0x100: work flag 0x100
void sub_2592C0(EEContext& ctx);
// sub_259310: state 4, work flags 0x40 | 0x800
void sub_259310(EEContext& ctx);
// sub_259380 () -> flags & 0x800: work flag 0x800
void sub_259380(EEContext& ctx);
// sub_2593D0: releases the textures of every card in use that is no stack (kind 1: sub_21A670; kind 0: sub_21A760),
//   work flag 0x400 off
void sub_2593D0(EEContext& ctx);
// sub_2594C0: picks a random card (+0x12884 = RpRandom() % card count), starts the second work pose's 90-frame turn
//   (sub_250CF0), the sound (sub_10A4E0), state 5, work flags 0x40 | 0x1000
void sub_2594C0(EEContext& ctx);
// sub_2595C0 () -> flags & 0x1000: work flag 0x1000
void sub_2595C0(EEContext& ctx);

// --- sfl_script.c: the shuffle script: command writer, runner and the nine command handlers (gp-18840) -----
// sub_259610 (work): sfl_script init: flags and the wait counter 0, gp-18840 = work
void sub_259610(EEContext& ctx);
// sub_259630: sfl_script shutdown: gp-18840 = 0
void sub_259630(EEContext& ctx);
// sub_259640: rewinds the script (pc = buffer) and starts it (flag 0x1)
void sub_259640(EEContext& ctx);
// sub_259690 (buffer, size): the script buffer: buffer, write pointer = buffer, size
void sub_259690(EEContext& ctx);
// sub_2596F0 () -> flags & 1: the script running
void sub_2596F0(EEContext& ctx);
// sub_259740: runs the script: while running, the command at pc (u16 op; table 0x68EAD0 {handler, u16 argument size})
//   is called with its arguments (aligned to 4) through jalr until a handler returns 0 (pc stays: the command runs
//   again next frame); else pc moves past it (aligned to 2)
void sub_259740(EEContext& ctx);
// sub_259850 (op, arguments): appends a command: u16 op, then (aligned to 4) the argument bytes the table gives
//   (memcpy), the write pointer aligned to 2; K_Assert when the buffer size is exceeded
void sub_259850(EEContext& ctx);
// sub_259970: writes END (op 0)
void sub_259970(EEContext& ctx);
// sub_2599C0 (a, b): writes SWAP a, b (op 1)
void sub_2599C0(EEContext& ctx);
// sub_259A60 (a, b): writes CLOSE a, b (op 3)
void sub_259A60(EEContext& ctx);
// sub_259B00 (n): writes WAIT n (op 2)
void sub_259B00(EEContext& ctx);
// sub_259B60 (n): writes OPEN n (op 4)
void sub_259B60(EEContext& ctx);
// sub_259BC0: writes op 5 (wait until no card is marked)
void sub_259BC0(EEContext& ctx);
// sub_259C10: writes START_ACT (op 6)
void sub_259C10(EEContext& ctx);
// sub_259C60 (speed): writes SPEED (op 7)
void sub_259C60(EEContext& ctx);
// sub_259CC0: writes op 8 (start the act and wait for it)
void sub_259CC0(EEContext& ctx);
// sub_259D10 (args) -> 0: END: "sfli: END", stops the script (flag 0x1 off)
void sub_259D10(EEContext& ctx);
// sub_259D80 (args) -> 1: SWAP: "sfli: SWAP %d, %d", queues the swap (sub_2551D0)
void sub_259D80(EEContext& ctx);
// sub_259E00 (args) -> bool: waits until no card is marked (sub_256430)
void sub_259E00(EEContext& ctx);
// sub_259E60 (args) -> 1: START_ACT: "sfli: START_ACT", starts the act (sub_257130)
void sub_259E60(EEContext& ctx);
// sub_259EA0 (args) -> 1: SPEED: the command speed (sub_2584E0)
void sub_259EA0(EEContext& ctx);
// sub_259ED0 (args) -> bool: starts the shuffle act once (sub_255B20, gp-18836 = 1) and returns 1 when it has finished
//   (sub_255F30 clear; gp-18836 = 0)
void sub_259ED0(EEContext& ctx);
// sub_259F40 (args) -> 1: CLOSE: "sfli: CLOSE %d, %d", gathers b cards from order a into a stack (sub_255570)
void sub_259F40(EEContext& ctx);
// sub_259FC0 (args) -> 1: OPEN: "sfli: OPEN %d", spreads stack n (sub_255810)
void sub_259FC0(EEContext& ctx);
// sub_25A030 (args) -> bool: WAIT n: on the first frame "sfli: WAIT %d" and the counter 0 (n == 0 ends at once), then
//   counts frames until n (flag 0x2 while waiting)
void sub_25A030(EEContext& ctx);

// --- sfl_cursor.c: the selection cursor (gp-18832) and the Shuffle Time counters ---------------------------
// sub_25AA70: cursor mode 3, +40 = 0, flag 0x2 (moving)
void sub_25AA70(EEContext& ctx);
// sub_25B300 (order): moves the cursor from its card (+48) to the card `order` (positions sub_258540 -> +4 / +16,
//   start +28 = +4), mode 0, then updates it (sub_25AAD0)
void sub_25B300(EEContext& ctx);
// sub_25B3B0 (order): moves the cursor to the card `order` in mode 1 (the target position -> +28), then updates it
void sub_25B3B0(EEContext& ctx);
// sub_25B440: arms the Shuffle Time counters: game counter 57 = 0, 56 = 24 + RpRandom() % 5 (called by
//   kwlnInitGameData / kwlnInitGameData2) [sflCountReset]
void sub_25B440(EEContext& ctx);

// --- sfl_count.c: the countdown digits (gp-18828) ----------------------------------------------------------
// sub_25B4A0 (work): sfl_count init: flags 0, gp-18828 = work
void sub_25B4A0(EEContext& ctx);
// sub_25B4B0: sfl_count shutdown: gp-18828 = 0
void sub_25B4B0(EEContext& ctx);
// sub_25B4F0: sets up the three digit sprites: each sprite's uv rect from the shuffle sprite's size (sub_20E610 i:
//   0/w, 0/h, w/w, h/h on the guest frame) into the two quads +16 + 256 i and +784 + 256 i (sub_21EB80); +4 = +8 = 0,
//   flag 0x1 on, 0x2 off
void sub_25B4F0(EEContext& ctx);
// sub_25B5F0: starts the count: +8 = 0, flag 0x2
void sub_25B5F0(EEContext& ctx);
// sub_25B640 () -> flags & 1: the count set up
void sub_25B640(EEContext& ctx);

// --- sfl_psel2.c: the persona-select page (gp-18808) -------------------------------------------------------
// sub_260A10: sfl_psel2 shutdown: gp-18808 = 0
void sub_260A10(EEContext& ctx);
// sub_260BD0: flag 0x1 off
void sub_260BD0(EEContext& ctx);
// sub_260C20: opens page 0 (+4 = 0, +8 = 0, flag 0x2)
void sub_260C20(EEContext& ctx);
// sub_260C70: opens page 1 (+4 = 1, +8 = 0, flag 0x2)
void sub_260C70(EEContext& ctx);
// sub_260CD0 () -> flags & 2: a page open
void sub_260CD0(EEContext& ctx);

}  // namespace p3fes::game
