// Phase 5 slice shops: the shop code of the facilities band (docs/ANALYSIS/27_unmapped_bands.md section 8,
// 0x3DF4A0-0x417158), 149 functions:
//
//   (1) the facility element library 0x3DF4A0-0x3E0680 that the fusion code (0x3D02E0-0x3DF49C) and the memory-card UI
//       share with the shops: element sets (an nm list whose nodes are animated sprites), their per-node animator, find /
//       start / for-each, the three template tables 0x6A6040 / 0x6A6510 / 0x6A66D0;
//   (2) fclShop.c: the shop's nm sequence (global 0x7CE688, 156-byte work record), its root state machine sub_3E6E80,
//       the shop tasks "fclShop" / "fclShopDraw" / "fclShopDraw2", the step records of the sequence (LOAD, ROOT, BUY,
//       SELL, TALK, MONEY, SUBTITLE, BG: 0x30-byte descriptors 0x6A6FC0.. {init, fini, update, draw, payload size, name})
//       and their openers / pollers, the element draw callback sub_3E6400;
//   (3) fclShopMisc.c: the per-shop data (record table 0x6AC9D0: 9 shop types x 36 bytes, a second set for the 'AGS_'
//       variant chosen by sub_17D800), lineup and message selection, money (clamped to 9,999,999), giving / taking
//       items, the buy / sell list rows (refresh, sort, sellable check), the ROOT menu row drawers, the background manager
//       tasks "fclShopDrawBGLow" / "fclShopDrawBGHighLow" / "fclShopDrawBGHighTop";
//   (4) fclDrawSprite.c: the facility sprite bank (global 0x7CE6A0) and its draws, the number string drawer;
//   (5) fclShopBGManager.c: background element handlers (animations, events that drive the MONEY / SUBTITLE / step
//       visibility) and the script COMM handlers that start a facility and wait for it (sub_40D410 / sub_40D490).
//
// Shop types (the work record's +0, the 'SHOP TYPE%d' of sub_3E0950, the load scripts of 0x6A6A90): 0 weapons
// (fcl_weapon.pak), 1 accessories (fcl_accessory.pak), 2 the pharmacy (fcl_drugstore.pak; the gate's shop route), 3 /
// 4 the antique shop, 5 souvenirs, 6 the lottery (msg_lot.bmd), 8 Elizabeth's requests (msg_quest.bmd); 7 has no load
// script (the script COMM handler starts the Velvet Room for 7 instead).
//
// The bodies are p3fes_handgen's (game/include/p3fes/game/hg_cpu.h); the names below are offsets for the bodies and the
// tests (game/src/facility/shops.cpp says which register holds which record).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

// The bodies (register ABI: arguments in $a0.., the result in $v0).
void sub_3DF4A0(EEContext& ctx);  // 0x3DF4A0
void sub_3DFAC0(EEContext& ctx);  // 0x3DFAC0
void sub_3DFAE0(EEContext& ctx);  // 0x3DFAE0
void sub_3DFEB0(EEContext& ctx);  // 0x3DFEB0
void sub_3DFF00(EEContext& ctx);  // 0x3DFF00
void sub_3DFF30(EEContext& ctx);  // 0x3DFF30
void sub_3DFF80(EEContext& ctx);  // 0x3DFF80
void sub_3DFFC0(EEContext& ctx);  // 0x3DFFC0
void sub_3E0080(EEContext& ctx);  // 0x3E0080
void sub_3E0260(EEContext& ctx);  // 0x3E0260
void sub_3E0330(EEContext& ctx);  // 0x3E0330
void sub_3E04E0(EEContext& ctx);  // 0x3E04E0
void sub_3E0650(EEContext& ctx);  // 0x3E0650
void sub_3E0680(EEContext& ctx);  // 0x3E0680
void sub_3E0700(EEContext& ctx);  // 0x3E0700
void fclShop_CreateShopDrawTasks(EEContext& ctx);  // 0x3E0780
void sub_3E0830(EEContext& ctx);  // 0x3E0830
void fclShop_UpdateShopDrawTask(EEContext& ctx);  // 0x3E0870
void fclShop_UpdateShopDraw2Task(EEContext& ctx);  // 0x3E08E0
void sub_3E0920(EEContext& ctx);  // 0x3E0920
void sub_3E0950(EEContext& ctx);  // 0x3E0950
void sub_3E0BB0(EEContext& ctx);  // 0x3E0BB0
void sub_3E0BC0(EEContext& ctx);  // 0x3E0BC0
void sub_3E6400(EEContext& ctx);  // 0x3E6400
void sub_3E6D40(EEContext& ctx);  // 0x3E6D40
void sub_3E6D70(EEContext& ctx);  // 0x3E6D70
void sub_3E6DC0(EEContext& ctx);  // 0x3E6DC0
void sub_3E6E80(EEContext& ctx);  // 0x3E6E80
void sub_3E86C0(EEContext& ctx);  // 0x3E86C0
void sub_3E8740(EEContext& ctx);  // 0x3E8740
void sub_3E87C0(EEContext& ctx);  // 0x3E87C0
void sub_3E8830(EEContext& ctx);  // 0x3E8830
void sub_3E8860(EEContext& ctx);  // 0x3E8860
void sub_3E8E10(EEContext& ctx);  // 0x3E8E10
void sub_3E8E20(EEContext& ctx);  // 0x3E8E20
void sub_3E8FF0(EEContext& ctx);  // 0x3E8FF0
void sub_3E90B0(EEContext& ctx);  // 0x3E90B0
void sub_3E94F0(EEContext& ctx);  // 0x3E94F0
void sub_3E96F0(EEContext& ctx);  // 0x3E96F0
void sub_3E9790(EEContext& ctx);  // 0x3E9790
void sub_3E97F0(EEContext& ctx);  // 0x3E97F0
void sub_3E98B0(EEContext& ctx);  // 0x3E98B0
void sub_3E9970(EEContext& ctx);  // 0x3E9970
void sub_3E9A90(EEContext& ctx);  // 0x3E9A90
void sub_3EA4D0(EEContext& ctx);  // 0x3EA4D0
void sub_3EA560(EEContext& ctx);  // 0x3EA560
void sub_3EA600(EEContext& ctx);  // 0x3EA600
void sub_3EA6B0(EEContext& ctx);  // 0x3EA6B0
void sub_3EA770(EEContext& ctx);  // 0x3EA770
void sub_3EA7E0(EEContext& ctx);  // 0x3EA7E0
void sub_3EAC40(EEContext& ctx);  // 0x3EAC40
void sub_3EACB0(EEContext& ctx);  // 0x3EACB0
void sub_3EE310(EEContext& ctx);  // 0x3EE310
void sub_3EE3D0(EEContext& ctx);  // 0x3EE3D0
void sub_3EE480(EEContext& ctx);  // 0x3EE480
void sub_3EE510(EEContext& ctx);  // 0x3EE510
void sub_3EE560(EEContext& ctx);  // 0x3EE560
void sub_3EE570(EEContext& ctx);  // 0x3EE570
void sub_3EE5F0(EEContext& ctx);  // 0x3EE5F0
void sub_3EEC60(EEContext& ctx);  // 0x3EEC60
void sub_3EED10(EEContext& ctx);  // 0x3EED10
void sub_3EED90(EEContext& ctx);  // 0x3EED90
void sub_3EEE10(EEContext& ctx);  // 0x3EEE10
void sub_3EFB40(EEContext& ctx);  // 0x3EFB40
void sub_3EFBC0(EEContext& ctx);  // 0x3EFBC0
void sub_3EFC60(EEContext& ctx);  // 0x3EFC60
void sub_3EFCA0(EEContext& ctx);  // 0x3EFCA0
void sub_3EFCE0(EEContext& ctx);  // 0x3EFCE0
void sub_3EFD70(EEContext& ctx);  // 0x3EFD70
void sub_3EFDE0(EEContext& ctx);  // 0x3EFDE0
void sub_3EFE60(EEContext& ctx);  // 0x3EFE60
void sub_3EFED0(EEContext& ctx);  // 0x3EFED0
void sub_3EFEF0(EEContext& ctx);  // 0x3EFEF0
void sub_3EFF00(EEContext& ctx);  // 0x3EFF00
void sub_3EFFF0(EEContext& ctx);  // 0x3EFFF0
void sub_3F0090(EEContext& ctx);  // 0x3F0090
void sub_3F00D0(EEContext& ctx);  // 0x3F00D0
void sub_3F01D0(EEContext& ctx);  // 0x3F01D0
void sub_3F0240(EEContext& ctx);  // 0x3F0240
void sub_3F0350(EEContext& ctx);  // 0x3F0350
void sub_3F03E0(EEContext& ctx);  // 0x3F03E0
void sub_3F06E0(EEContext& ctx);  // 0x3F06E0
void sub_3F0830(EEContext& ctx);  // 0x3F0830
void sub_3F0D60(EEContext& ctx);  // 0x3F0D60
void sub_3F10B0(EEContext& ctx);  // 0x3F10B0
void sub_3F1470(EEContext& ctx);  // 0x3F1470
void sub_3F15D0(EEContext& ctx);  // 0x3F15D0
void sub_3F1720(EEContext& ctx);  // 0x3F1720
void sub_3F1830(EEContext& ctx);  // 0x3F1830
void sub_3F1A10(EEContext& ctx);  // 0x3F1A10
void sub_3F2240(EEContext& ctx);  // 0x3F2240
void sub_3F2510(EEContext& ctx);  // 0x3F2510
void sub_3F2D60(EEContext& ctx);  // 0x3F2D60
void sub_3F2DC0(EEContext& ctx);  // 0x3F2DC0
void sub_3F3280(EEContext& ctx);  // 0x3F3280
void sub_3F3970(EEContext& ctx);  // 0x3F3970
void sub_3F3DC0(EEContext& ctx);  // 0x3F3DC0
void sub_3F3F00(EEContext& ctx);  // 0x3F3F00
void sub_3F7730(EEContext& ctx);  // 0x3F7730
void sub_3F98F0(EEContext& ctx);  // 0x3F98F0
void sub_3F99D0(EEContext& ctx);  // 0x3F99D0
void sub_3F9B20(EEContext& ctx);  // 0x3F9B20
void sub_3F9CB0(EEContext& ctx);  // 0x3F9CB0
void sub_3FA0D0(EEContext& ctx);  // 0x3FA0D0
void sub_3FA190(EEContext& ctx);  // 0x3FA190
void sub_3FA1B0(EEContext& ctx);  // 0x3FA1B0
void sub_3FA1E0(EEContext& ctx);  // 0x3FA1E0
void sub_3FB290(EEContext& ctx);  // 0x3FB290
void sub_3FBF20(EEContext& ctx);  // 0x3FBF20
void sub_3FC980(EEContext& ctx);  // 0x3FC980
void sub_3FFA20(EEContext& ctx);  // 0x3FFA20
void sub_3FFE00(EEContext& ctx);  // 0x3FFE00
void sub_400690(EEContext& ctx);  // 0x400690
void sub_400740(EEContext& ctx);  // 0x400740
void sub_400A90(EEContext& ctx);  // 0x400A90
void sub_400B90(EEContext& ctx);  // 0x400B90
void fclShopMisc_CreateShopDrawBGLowTasks(EEContext& ctx);  // 0x400D60
void sub_401170(EEContext& ctx);  // 0x401170
void fclShopMisc_UpdateShopDrawBGLowTask(EEContext& ctx);  // 0x401210
void fclShopMisc_UpdateShopDrawBGHighLowTask(EEContext& ctx);  // 0x4012C0
void fclShopMisc_UpdateShopDrawBGHighTopTask(EEContext& ctx);  // 0x401370
void sub_401420(EEContext& ctx);  // 0x401420
void sub_4014E0(EEContext& ctx);  // 0x4014E0
void sub_4015A0(EEContext& ctx);  // 0x4015A0
void sub_4015E0(EEContext& ctx);  // 0x4015E0
void sub_401600(EEContext& ctx);  // 0x401600
void sub_40D410(EEContext& ctx);  // 0x40D410
void sub_40D490(EEContext& ctx);  // 0x40D490
void sub_40D5E0(EEContext& ctx);  // 0x40D5E0
void sub_40D610(EEContext& ctx);  // 0x40D610
void sub_40E300(EEContext& ctx);  // 0x40E300
void sub_40E390(EEContext& ctx);  // 0x40E390
void sub_40E3C0(EEContext& ctx);  // 0x40E3C0
void sub_40E3F0(EEContext& ctx);  // 0x40E3F0
void sub_40E450(EEContext& ctx);  // 0x40E450
void sub_40E4F0(EEContext& ctx);  // 0x40E4F0
void sub_40E580(EEContext& ctx);  // 0x40E580
void sub_40E610(EEContext& ctx);  // 0x40E610
void sub_40E710(EEContext& ctx);  // 0x40E710
void sub_40EB50(EEContext& ctx);  // 0x40EB50
void sub_40EC20(EEContext& ctx);  // 0x40EC20
void sub_40EC50(EEContext& ctx);  // 0x40EC50
void sub_40EEF0(EEContext& ctx);  // 0x40EEF0
void sub_410D30(EEContext& ctx);  // 0x410D30
void sub_410E70(EEContext& ctx);  // 0x410E70
void sub_4110F0(EEContext& ctx);  // 0x4110F0
void sub_411190(EEContext& ctx);  // 0x411190
void sub_411340(EEContext& ctx);  // 0x411340
void sub_412580(EEContext& ctx);  // 0x412580

// ---- layouts (offsets in bytes; evidence: the functions named in each comment) --------------------------------------
namespace shop {

// nm lists (nmlist.c; the nm_message slice's names): the list header and its nodes.
constexpr s32 kListHead = 4;        // first node
constexpr s32 kListCursor = 12;     // the cursor node (menus)
constexpr s32 kListCount = 16;      // u16 node count
constexpr s32 kListObjPayload = 36; // the payload of the list object / sequence (nmObjPayloadWord12 reads its +12)
constexpr s32 kNodeNext = 16;       // next node
constexpr s32 kNodePayload = 20;    // the node's payload (an element, a step's state, a menu row)

// The shop work record (156 bytes: the payload of the shop sequence, sub_3E0950; nmObjPayloadWord12(0x7CE688)).
constexpr u32 kShopSeqGlobal = 0x7CE688u;  // the shop nm sequence (0 when no shop is open)
constexpr s32 kShopType = 0;          // shop type 0..8 (above)
constexpr s32 kShopState = 4;         // the root state machine's state (sub_3E6E80; 1 at creation)
constexpr s32 kShopFlags = 8;         // 4 the shop has a lineup (state 6, sub_3F0240; sub_3E6D70 reads it), 0x20 the
                                      // high layer is drawing (fclShop_UpdateShopDrawTask); 1, 2, 8, 0x10 are bits of
                                      // the root state machine (states 0x2A / 0x38, 0x0D / 0x3E, 0x0D / 0x1F, 0x12)
constexpr s32 kShopStepRoot = 16;     // the ROOT step (the top menu: buy / sell / talk / ...), sub_3E8E20
constexpr s32 kShopStepBuy = 20;      // the BUY step, sub_3E97F0
constexpr s32 kShopStepSell = 24;     // the SELL step, sub_3EA600
constexpr s32 kShopStepTalk = 28;     // the TALK step, sub_3EE310
constexpr s32 kShopStepBg = 64;       // the BG step (background manager), sub_3EFB40
constexpr s32 kShopStepMoney = 68;    // the MONEY step (the yen display), sub_3EE570
constexpr s32 kShopStepSubtitle = 72; // the SUBTITLE step, sub_3EED90
constexpr s32 kShopStepLoad = 76;     // the LOAD step (the shop type's load script), sub_3E86C0
constexpr s32 kShopPakNode = 88;      // the H_Cdvd node of "facility/%s" (load op 7)
constexpr s32 kShopPakData = 92;      // its data (node +272)
constexpr s32 kShopMsgSlots = 96;     // 2 x {H_Cdvd node, data} (load ops 3 / 4), 8 bytes each
constexpr s32 kShopTask = 128;        // the "fclShop" task
constexpr s32 kShopPsStatus = 132;    // the persona-status tasks (load op 1)
constexpr s32 kShopItemId = 138;      // u16 the item of the current request / purchase
constexpr s32 kShopAsked = 140;       // u16[4] party member requests already handled this visit
constexpr s32 kShopSubTask = 148;     // the task of state 0x3A (sub_3A2090)
constexpr s32 kShopElements = 152;    // the shop's element set (sub_3DFEB0)
constexpr s32 kShopWorkSize = 156;

// Sequence steps: the payload every step's callbacks get (via sub_3C5470 on the step node).
constexpr s32 kStepResult = 0;        // what the poller returns when the step ends
constexpr s32 kStepFlags = 4;         // 1 decided, 2 hidden / closing (the step-specific bits above)
constexpr s32 kStepPhase = 8;
constexpr s32 kStepNodeState = 20;    // on the step's node payload: flag 8 = finished (the pollers)

// LOAD step payload (0x60 bytes): the type's load script {ops, count} and the walk.
constexpr s32 kLoadType = 4;
constexpr s32 kLoadPhase = 8;         // 0 start the op, 1 wait for it
constexpr s32 kLoad76 = 76;           // cleared by the init
constexpr s32 kLoadScript = 80;       // -> {op records (8 bytes: u16 op, s8, s8, word), count}
constexpr s32 kLoadIndex = 84;

// A facility element (the payload of an element-set node; sub_3DF4A0, sub_3DFFC0, sub_3E6400).
constexpr s32 kElemNode = 4;          // back pointer to the node
constexpr s32 kElemFlags = 8;         // 2 use the arc path (state 3), 4 idle / done
constexpr s32 kElemState = 12;        // 0 new, 1 delay, 2 / 3 start eased / arc, 4 / 5 running, 6 done
constexpr s32 kElemId = 16;           // the element id the draw callback switches on
constexpr s32 kElemX = 20;            // s16 current position
constexpr s32 kElemY = 22;
constexpr s32 kElemX0 = 24;           // s16 start position
constexpr s32 kElemY0 = 26;
constexpr s32 kElemX1 = 28;           // s16 end position
constexpr s32 kElemY1 = 30;
constexpr s32 kElemScale = 32;        // s16 current value of the second eased pair
constexpr s32 kElemScale0 = 34;
constexpr s32 kElemScale1 = 36;
constexpr s32 kElemAlpha = 38;        // s16 current alpha (linear)
constexpr s32 kElemAlpha0 = 40;
constexpr s32 kElemAlpha1 = 42;
constexpr s32 kElemDelay = 44;        // s16 frames before the move starts
constexpr s32 kElemFrame = 46;        // u16 frames run
constexpr s32 kElemFrames = 48;       // u16 duration
constexpr s32 kElemExtra = 52;        // -> +56 (an extra area when the template asks for one)
constexpr s32 kElemTemplateSize = 28; // a template record (two per id: in, out)

// The background manager (fclShopMisc_CreateShopDrawBGLowTasks; the BG step's +8).
constexpr s32 kBgFlags = 0;           // 1 mode change pending, 2 loaded / idle, 4 a change during a change
constexpr s32 kBgList = 8;            // the element list (nodes: {flags, ?, entry, data})
constexpr s32 kBgTask = 12;           // "fclShopDrawBGLow" (the High tasks are its children)
constexpr s32 kBgScene = 16;          // the scene descriptor (off_6B1F30 + 16 * type): +8 entries (28 bytes), +12 count
constexpr s32 kBgMode = 24;           // the requested mode (-1 at creation)
constexpr s32 kBgShopType = 28;
constexpr s32 kBgEntryLayer = 20;     // on a scene entry: 0 low, 2 high-low, 3 the BG step's draw, 4 high-top
constexpr s32 kBgEntryDraw = 4;       // on a scene entry: the layer's draw handler
constexpr s32 kBgEntryLoad = 16;      // on a scene entry: the load handler (sub_4014E0 polls it)

// The facility sprite bank (global 0x7CE6A0, sub_40E450): {loaded, descriptor, handles, sprite table, ...}.
constexpr u32 kSpriteBankGlobal = 0x7CE6A0u;
constexpr u32 kSpriteBankArg = 0x7CE69Cu;
constexpr s32 kBankLoaded = 0;        // files turned into handles so far
constexpr s32 kBankDesc = 4;          // -> {file name table, file count, sprite table, ...}
constexpr s32 kBankHandles = 8;       // -> one sprite handle per file (the block's +20)
constexpr s32 kBankSprites = 12;      // -> 8-byte sprites {s8 file, -, s16 frame, s16 dx, s16 dy}
constexpr s32 kBankExtra = 16;

// Money: the yen counter is clamped to this (sub_3F15D0, the 9999999 of sub_3F3280 / sub_3F9CB0 sort keys).
constexpr s32 kYenMax = 9999999;

}  // namespace shop

}  // namespace p3fes::game
