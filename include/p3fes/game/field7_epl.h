// Phase 5 slice field7, part 2 (game/src/field/field7_epl.cpp): the field's EPL player tasks of k_epl.c,
// 0x1A8DB0-0x1A9760 -- "epl(kosaka)" (one EPL file played as a main effect node plus up to eight child nodes) and the
// queue of "epl delay(kosaka)". Register-ABI bodies (arguments in $a0.., result in $v0); names are functions.json's,
// proposed names in brackets (ADR-0009: from this slice's own reading of the instructions and the callers).
//
// "epl(kosaka)" -- created by sub_1A9080(parent, path, frames, cached) [K_FldEpl_CreateTask] with kwlnTaskCreate
// priority 20, update sub_1A8DB0, destroy sub_1A8FE0; 180-byte work from the RW calloc slot (0x960184):
//   state 0: the file -- cached (+12): H_Cdvd_CacheFindFile(path) and an effect node from it (sub_34FCD0); else wait
//            for the H_Cdvd request (+4) to load, make the node from the node's data (+272) and destroy the request;
//            then state 1. state 1: idle (callers set the next state: K_FldDungeon_UpdateTask starts the floor's
//            field/effect/DNG%02d.EPL with frames = -1, i.e. never ending). state 2: playing -- the main node (+16 on)
//            drawn on its layer (+28) until +24 reaches the frame count (+8), each live child likewise with its own
//            counter (+68[i]) and layer (+100[i]) and destroyed at the end; when the main node is off and no child
//            is left, back to state 1. state 3: the task ends (returns -1).
// "epl delay(kosaka)" -- sub_1A96C0(parent) [K_FldEpl_CreateDelayTask], created once per field root
// (k_Field_CreateFieldRootTask stores it at 0x869F70); update sub_1A9500 (left recompiled: it calls the stood-in
// EPL start sub_1A91B0 and the SFX sub_10A4E0), destroy sub_1A9690. sub_1A9760 queues up to eight requests
// (k_epl.c 608 asserts the count): id +16[i], position +48[i] (vec3), +144[i], +176[i].
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace f7::epl {
// "epl(kosaka)" work (180 bytes; sub_1A9080 allocates and fills it)
inline constexpr int kState = 0;          // 0 load, 1 idle, 2 playing, 3 end
inline constexpr int kRequest = 4;        // H_Cdvd node (or the caller's non-zero `cached` word)
inline constexpr int kFrames = 8;         // play length in frames (unsigned compare: -1 = forever)
inline constexpr int kCached = 12;        // 1: take the file from the H_Cdvd cache by name
inline constexpr int kMainOn = 16;        // the main node plays
inline constexpr int kMainNode = 20;      // the main effect node (sub_34FCD0)
inline constexpr int kMainFrame = 24;     // the main node's frame counter
inline constexpr int kMainLayer = 28;     // u16: the main node's draw layer
inline constexpr int kLiveChildren = 32;  // live child nodes
inline constexpr int kChildNodes = 36;    // [8] child effect nodes
inline constexpr int kChildFrames = 68;   // [8] child frame counters
inline constexpr int kChildLayers = 100;  // u16 [8] child draw layers
inline constexpr int kPath = 116;         // the EPL path (strcpy'd)
inline constexpr int kWorkSize = 180;
inline constexpr int kMaxChildren = 8;
// "epl delay(kosaka)" work (208 bytes)
inline constexpr int kDelayWait = 4;      // 20 at creation
inline constexpr int kDelayCount = 12;    // queued requests (< 8)
inline constexpr int kDelayId = 16;       // [8] the request's first word
inline constexpr int kDelayPos = 48;      // [8] vec3 (12-byte stride)
inline constexpr int kDelayArg3 = 144;    // [8]
inline constexpr int kDelayArg4 = 176;    // [8]
inline constexpr int kDelayWorkSize = 208;
inline constexpr int kTaskWork = 60;      // kwln task +60: the work block
}  // namespace f7::epl

void sub_1A8DB0(EEContext& ctx);  // [K_FldEpl_UpdateTask](task) -> 0, or -1 at state 3
void sub_1A8FE0(EEContext& ctx);  // [K_FldEpl_DestroyTask](task): destroys the child and main nodes, frees the work
void sub_1A9080(EEContext& ctx);  // [K_FldEpl_CreateTask](parent, path, frames, cached) -> task or 0
void sub_1A9330(EEContext& ctx);  // [K_FldEpl_SetMatrix](task, slot, matrix): slot < 0 = the main node
void sub_1A9470(EEContext& ctx);  // [K_FldEpl_Stop](task): destroys the children, stops the main node
void sub_1A9690(EEContext& ctx);  // [K_FldEpl_DestroyDelayTask](task): frees the work
void sub_1A96C0(EEContext& ctx);  // [K_FldEpl_CreateDelayTask](parent) -> task or 0
void sub_1A9760(EEContext& ctx);  // [K_FldEpl_QueueDelayed](task, id, pos, a3, a4)

}  // namespace p3fes::game
