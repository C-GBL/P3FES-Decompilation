// Phase 5 slice battle_result: the battle result screen (docs/ANALYSIS/27_unmapped_bands.md section 3,
// docs/ANALYSIS/queue_bands.txt `# === slice battle_result`). The battle gate's route ends on it: the "battle result"
// task and its four "battle result draw" tasks are live in the battle snapshot at vblank 6150.
//
// The pieces, by source file (the K_Assert strings):
//   br_root.c   0x1EF500-0x1F2080  the root: brRoot_CreateBattleResultTasks (heap, kept) creates "battle result" (update brRoot_UpdateBattleResultTask,
//               printf, kept) and the four draws (sub_1F07A0 in queue_rendering.txt; sub_1F08C0 / sub_1F0900 /
//               sub_1F0940 here). The root's work
//               (task +60, also at gp-18968) holds the state word +12 the update switches on, the flag word +0 (0x1
//               finished; 0x4 / 0x8 / 0x20 the pages still to show, 7 / 9 / 8 in sub_1F0D70; 0x8000 the shuffle
//               hand-off with its task at +148; 0x200000 / 0x400000 the spoils panel / level-up page up), the load
//               words +4 / +8 (bit 2: the level resources requested / loaded), the dropped items +152 (8-byte records
//               {u16 item, s32 count at +4}, +176 of them), the experience +180 and its ratio +184, the lists +240 /
//               +264, +268 / +276 and +320 / +336 (u16 ids and their counts), and the experience block +10832..+10844.
//               Its steps are the small functions sub_1F0A60 .. sub_1F1F40.
//   br_friend.c 0x1F9D70-0x1FAEA0  the party members' rewards: the members' flags 4625..4633, the default equipment,
//               the best equipment after a level-up, the persona evolution of COMM 0x171 (sub_1FAEA0).
//   br_data.c   0x1FB130-0x1FC718  persona evolution and skill rows, the level-band table, the experience formula, the
//               follow-up damage of sub_1FC590.
//   br_res.c    0x2338D0-0x234820  the result resources (gp-18916): the load flags and the sprite file tables.
//   br_panel.c  0x234820-0x236390  the spoils panel (gp-18912).
//   bp_ifont.c  0x238FD0-0x239164  the panel's digit font.
//   brp_birth.c 0x24A870-0x24BA30  the persona birth on level-up (gp-18880); brp_res.c (gp-18876) its resources;
//               bai_main.c 0x24C100-0x24D104 (gp-18872) the AI-tactics banner of the same band.
// Every heap / printf / file-I/O function of these files stays recompiled (queue_bands.txt skip-class; the five
// H_Cdvd_Request loaders sub_2339D0, sub_233B20, sub_233C00, sub_24BE40, sub_24BF80 too).
//
// Register contract (docs/PHASE5_AGENT_BRIEF.md, waves 6 and 7): the task updates run through `jalr` from the kwln
// kernel, every check point can preempt the thread and the kernel then saves the whole register file in guest memory,
// and the callers read registers these functions leave behind. So the bodies are register-faithful: at every check
// point, every call and every return each GPR (128 bits), HI/LO, FPR, ACC and FCR31 holds what the original holds
// there, and the prologues write the original spills (and the stack buffers the original hands to callees). The
// bodies work on the guest registers directly (the Cpu view in src/battle/battle_result.cpp, one named variable per
// register, as render/ptank.cpp); the typed functions below load their arguments into $a0.. and return $v0 as the
// body leaves it.
//
// Names: every function keeps its symbols/functions.json name (all sub_*); a bracketed role is a proposal
// (symbols/deltas/bands.sym has the task names). The recompiled program's entry points (`fn_<name>_<addr8>`) are
// defined in src/battle/battle_result.cpp.
#pragma once

#include "p3fes/ee/core.h"
#include "p3fes/ee_context.h"

namespace p3fes::game {


// --- br_root.c: the "battle result" root task's draw updates and page steps (work = task +60 = gp-18968) -------------
u32 sub_1F08C0(EEContext& ctx, u32 task);  // [battle result draw 2]
u32 sub_1F0900(EEContext& ctx, u32 task);  // [battle result draw 3]
u32 sub_1F0940(EEContext& ctx, u32 task);  // [battle result draw 4]
u32 sub_1F0970(EEContext& ctx, u32 task);
u32 sub_1F0A60(EEContext& ctx, u32 task);
u32 sub_1F0AB0(EEContext& ctx, u32 task);
u32 sub_1F0C40(EEContext& ctx, u32 task);  // [apply the spoils]
u32 sub_1F0D70(EEContext& ctx, u32 task);  // [next page]
u32 sub_1F0EB0(EEContext& ctx, u32 task);
u32 sub_1F0F40(EEContext& ctx, u32 task);  // [page 9]
u32 sub_1F0FD0(EEContext& ctx);
u32 sub_1F0FF0(EEContext& ctx);  // [start the level-up page]
u32 sub_1F10B0(EEContext& ctx);
u32 sub_1F10F0(EEContext& ctx);
u32 sub_1F1140(EEContext& ctx, u32 task);  // [page 8]
u32 sub_1F1210(EEContext& ctx);
u32 sub_1F1240(EEContext& ctx, u32 task);  // [the experience gauge]
u32 sub_1F1AA0(EEContext& ctx, u32 task);
u32 sub_1F1AE0(EEContext& ctx);
u32 sub_1F1B00(EEContext& ctx, u32 task);
u32 sub_1F1B20(EEContext& ctx, u32 task);
u32 sub_1F1B40(EEContext& ctx, u32 task);
u32 sub_1F1B60(EEContext& ctx, u32 task);  // [leave state 2]
u32 sub_1F1C20(EEContext& ctx, u32 task);  // [destroy the result root]
u32 sub_1F1C50(EEContext& ctx);  // [the result work]
u32 sub_1F1C90(EEContext& ctx, u32 task);  // [open the spoils panel]
u32 sub_1F1DF0(EEContext& ctx, u32 out_ids, u32 out_count);
u32 sub_1F1E90(EEContext& ctx, u32 task);  // [page 7, level-up]
u32 sub_1F1F40(EEContext& ctx);  // [may the result end?]

// --- br_friend.c: the party members' rewards -- flags, default and best equipment, the persona evolution (COMM 0x171) 
u32 sub_1F9D70(EEContext& ctx, u32 member);  // [the member's flag]
u32 sub_1FA0D0(EEContext& ctx);  // [default equipment]
u32 sub_1FA4F0(EEContext& ctx, u32 member);  // [best equipment after a level-up]
u32 sub_1FAEA0(EEContext& ctx);  // [COMM 0x171]

// --- br_data.c: persona evolution / skill rows, level bands, experience ----------------------------------------------
u32 sub_1FB130(EEContext& ctx, u32 member, u32 persona_id);  // [evolve the member's persona]
u32 sub_1FB1B0(EEContext& ctx, u32 member, u32 value);
u32 sub_1FB1F0(EEContext& ctx, u32 persona, u32 out_skills, u32 out_count);  // [skills learned at the next levels]
// [rows in a level range]
u32 sub_1FB3F0(EEContext& ctx, u32 rows, u32 level, u32 gained, u32 out_first, u32 out_count);
// [skill rows in a level range]
u32 sub_1FB4B0(EEContext& ctx, u32 rows, u32 n, u32 level, u32 range, u32 out_first, u32 out_count);
u32 sub_1FBD50(EEContext& ctx, u32 level, u32 nth);  // [level band]
u32 sub_1FBDF0(EEContext& ctx, u32 level, u32 other_level, u32 exp, u32 row, u32 mode);  // [experience]
// [experience with an item]
u32 sub_1FBFA0(EEContext& ctx, u32 level, u32 other_level, u32 exp, u32 item, u32 row, u32 mode);
u32 sub_1FC1F0(EEContext& ctx);
u32 sub_1FC230(EEContext& ctx, u32 persona);  // [has a skill to learn]
u32 sub_1FC3C0(EEContext& ctx, u32 persona);  // [level of the next skill]
u32 sub_1FC590(EEContext& ctx, u32 unit, u32 target);  // [follow-up damage]

// --- br_res.c: the result resource record (gp-18916) -----------------------------------------------------------------
u32 sub_2338D0(EEContext& ctx, u32 res);
u32 sub_2338F0(EEContext& ctx, u32 res);
u32 sub_233910(EEContext& ctx, u32 res);
u32 sub_233930(EEContext& ctx, u32 res);
u32 sub_233950(EEContext& ctx, u32 res);
u32 sub_233960(EEContext& ctx, u32 res);
u32 sub_233970(EEContext& ctx, u32 res);  // [br_res init]
u32 sub_233AD0(EEContext& ctx);
u32 sub_233BB0(EEContext& ctx);
u32 sub_233D20(EEContext& ctx);
u32 sub_233D70(EEContext& ctx, u32 i);
u32 sub_233DF0(EEContext& ctx, u32 i);
u32 sub_234570(EEContext& ctx, u32 i);  // [result sprite file]
u32 sub_2345D0(EEContext& ctx, u32 i);
u32 sub_234630(EEContext& ctx, u32 i);
u32 sub_234690(EEContext& ctx, u32 i, u32 file);
u32 sub_2347E0(EEContext& ctx);

// --- br_panel.c: the spoils panel (gp-18912) -------------------------------------------------------------------------
u32 sub_234820(EEContext& ctx, u32 panel);  // [br_panel init]
u32 sub_234960(EEContext& ctx);  // [br_panel shutdown]
u32 sub_234A00(EEContext& ctx, u32 record);  // [fill the spoils panel]
u32 sub_235010(EEContext& ctx);  // [panel step]
u32 sub_2361D0(EEContext& ctx, u32 sprite, u32 index, u32 kind);
u32 sub_236280(EEContext& ctx);  // [open the panel]
u32 sub_2362E0(EEContext& ctx);  // [close the panel]
u32 sub_236340(EEContext& ctx);

// --- bp_ifont.c: the panel's digit font ------------------------------------------------------------------------------
u32 bpIfontSetDigitQuad(EEContext& ctx, u32 quad, u32 digit, u32 font);
u32 sub_239140(EEContext& ctx, u32 font);

// --- brp_birth.c: the persona birth on level-up (gp-18880) -----------------------------------------------------------
u32 sub_24A870(EEContext& ctx);
u32 sub_24AA90(EEContext& ctx);
u32 sub_24AB10(EEContext& ctx, u32 persona_id);
u32 sub_24ABD0(EEContext& ctx);
u32 sub_24AC40(EEContext& ctx);
u32 sub_24ADF0(EEContext& ctx);
u32 sub_24B8A0(EEContext& ctx);
u32 sub_24B9E0(EEContext& ctx);

// --- brp_res.c: the persona-birth resources (gp-18876) ---------------------------------------------------------------
u32 sub_24BA30(EEContext& ctx, u32 res);  // [brp_res init]
u32 sub_24BED0(EEContext& ctx);
u32 sub_24BF20(EEContext& ctx, u32 i);
u32 sub_24C040(EEContext& ctx);
u32 sub_24C090(EEContext& ctx);

// --- bai_main.c: the AI-tactics banner (gp-18872) --------------------------------------------------------------------
u32 sub_24C100(EEContext& ctx, u32 work);  // [bai init]
u32 sub_24C110(EEContext& ctx);
u32 sub_24CF00(EEContext& ctx, u32 kind);
u32 sub_24D0C0(EEContext& ctx);

}  // namespace p3fes::game
