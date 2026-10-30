// The game root, the logo and the title screen (slice `title`), hand-decompiled from SLUS_216.21
// (docs/ANALYSIS/27_unmapped_bands.md section 4; queue docs/ANALYSIS/queue_bands.txt "slice title"): the source files
// op_root.c, gm_root.c, op_res.c, op_title.c, op_logo.c, op_menu.c and op_wait.c (their names are the K_Assert file
// strings 0x68EC48..0x68ED30). Phase 5 slice `title`; game/src/ui/title.cpp, pair tests tests/game/test_title.cpp.
//
// How it fits together. kwlnRootUpdateTask creates the "game root" task (gmRoot_CreateGameRootTask 0x2664C0, update
// gmRoot_UpdateGameRootTask = gmRoot_UpdateGameRootTask). Its step sub_266140 runs a three-state machine over the gm_root work
// (gp-18788): state 0 waits for the task +40 to end and creates the op root (sub_2663C0 -> sub_265C20: the "op" /
// "op draw" task pair, updates opRoot_UpdateOpTask = opRoot_UpdateOpTask and opRoot_UpdateOpDrawTask = opRoot_UpdateOpDrawTask), state 1
// starts the game once the op root is gone (new game / continue by the mode the title left in gp-18784; The Answer has
// its own start), state 2 counts counter 47 up every frame (unless flag 0x1418) and, when the game task ends, either
// restarts it (flag 0x1413, sub_266430) or returns to the title. The op root (gp-18792) is the 19-state machine sub_265030
// (opRootUpdate in topic 20: jump table 0x7B79D0): the logo (op_logo, gp-18752), the opening movie, the title (op_title,
// gp-18756) with its menu (op_menu, gp-18748: New Game / Load / ...), the "press start" wait screen (op_wait,
// gp-18744), the memory-card check (Y_McProc_CreateMcProcDrawTask) and the hand-over to the game (states 15..18). Every frame it then
// runs the resource loader (sub_266710, op_res gp-18780), the logo update, the title draw, the wait-screen update, the
// menu update and sub_271EC0. Each module keeps a pointer to its work in a $gp word, set by a "set work" function
// (which asserts the word was free) and cleared by a "clear work" function (which asserts it was set); every
// accessor asserts the work exists (K_Assert sub_19D3F0 is `jr ra` in retail, so a failed check continues).
//
// Names: as symbols/functions.json gives them now (sub_* except opMenuSetWork). Bracketed names are proposals (ours,
// from the instructions, the strings and the callers; the task updates' names are in symbols/deltas/bands.sym).
// Globals addressed through $gp are given with their gp offset ($gp = 0x7D2CF0, crt0) and absolute address.
//
// Every function here is register-faithful at each check point, call and return (docs/PHASE5_AGENT_BRIEF.md, the
// wave-6 / wave-7 lessons): the prologue spills go to the guest stack, every register the original writes holds the
// original's value whenever a callee, a check point or the caller can see it, the indirect calls of sub_269A10 run
// inside the original frame with the original $ra, and the integer division / FPU steps run through the runtime's
// EE operations in the compiled order (HI/LO, FCR31 and the FPRs end as the original leaves them).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace title {
inline constexpr u32 kGp = 0x7D2CF0u;
inline constexpr u32 gp_addr(s32 off) { return kGp + static_cast<u32>(off); }

// --- the module work pointers ($gp words) -----------------------------------------------------------------------------
inline constexpr s32 kGpOpToggle = -18796;    // u8 0x7CE384: alternates the two sub_10BC20 kinds of op state 4
inline constexpr s32 kGpOpRoot = -18792;      // 0x7CE388: op_root.c work (sub_265030's state machine)
inline constexpr s32 kGpGmRoot = -18788;      // 0x7CE38C: gm_root.c work (the "game root" task)
inline constexpr s32 kGpTitleMode = -18784;   // 0x7CE390: 1 = continue from a save (set by op state 12 / 7, sub_266660)
inline constexpr s32 kGpOpRes = -18780;       // 0x7CE394: op_res.c work (the title / logo resources)
inline constexpr s32 kGpOpTitle = -18756;     // 0x7CE3AC: op_title.c work
inline constexpr s32 kGpOpLogo = -18752;      // 0x7CE3B0: op_logo.c work
inline constexpr s32 kGpOpMenu = -18748;      // 0x7CE3B4: op_menu.c work
inline constexpr s32 kGpOpWait = -18744;      // 0x7CE3B8: op_wait.c work
inline constexpr s32 kGpMcResultA = -19700;   // 0x7CDFFC: the memory-card process result (cleared before the check)
inline constexpr s32 kGpMcResultB = -19684;   // 0x7CE00C
inline constexpr s32 kGpMovieSeen = -19672;   // 0x7CE018: 1 once the opening movie ran (op state 3)

// The K_Assert file strings (`lui a0, 0x69; addiu a0, a0, off`).
inline constexpr u32 kFileOpRoot = 0x68EC48u;   // "op_root.c"
inline constexpr u32 kFileGmRoot = 0x68EC58u;   // "gm_root.c"
inline constexpr u32 kFileOpRes = 0x68EC78u;    // "op_res.c"
inline constexpr u32 kFileOpTitle = 0x68ED00u;  // "op_title.c"
inline constexpr u32 kFileOpLogo = 0x68ED10u;   // "op_logo.c"
inline constexpr u32 kFileOpMenu = 0x68ED20u;   // "op_menu.c"
inline constexpr u32 kFileOpWait = 0x68ED30u;   // "op_wait.c"

// --- the op root's work (gp-18792) --------------------------------------------------------------------------------
inline constexpr s32 kOpFlags = 0;           // bit 0 alive, 1 child +16 running, 2 child +24 running, 3 input lock
inline constexpr s32 kOpState = 4;           // 0..18 (jump table 0x7B79D0)
inline constexpr s32 kOpParent = 8;          // the "op" task (parent of everything it creates)
inline constexpr s32 kOpChild16 = 16;        // the memory-card process task (state 11)
inline constexpr s32 kOpChild20 = 20;        // the sub_10BC20 task of state 4
inline constexpr s32 kOpChild24 = 24;        // the sub_15C460 task (state 14)
inline constexpr s32 kOpChild28 = 28;        // the load / new-game task of state 13 / 18
inline constexpr s32 kOpCursor = 17696;      // the menu cursor (0..3 title menu, 0..1 continue menu)
inline constexpr s32 kOpIdle = 17700;        // idle frames (450 -> fade to the demo)
inline constexpr s32 kOpReturnState = 17704; // the state the idle fade returns to
inline constexpr s32 kOpMovieTask = 17708;   // the opening movie task (state 2 / 3)
inline constexpr u32 kOpJumpTable = 0x7B79D0u;
inline constexpr u32 kOpStates = 19;
inline constexpr u32 kOpIdleLimit = 450;

// --- the game root's work (gp-18788) -------------------------------------------------------------------------------
inline constexpr s32 kGmFlags = 0;     // bit 0 alive, 1 op root running (+12), 2 field running (+16)
inline constexpr s32 kGmState = 4;     // 0 create the op root, 1 start the game, 2 in game
inline constexpr s32 kGmParent = 8;
inline constexpr s32 kGmOpTask = 12;
inline constexpr s32 kGmGameTask = 16;
inline constexpr s32 kGmMode = 20;     // copy of gp-18784 when the op root ends
inline constexpr s32 kGmWaitTask = 40;
inline constexpr u32 kGmFlagReturnToTitle = 5139;  // 0x1413
inline constexpr u32 kGmFlagNoCount = 5144;        // 0x1418
inline constexpr u32 kGmSessionCounter = 47;

// --- the pad words (20_menu_ui.md section 4.1) ------------------------------------------------------------------------
inline constexpr u32 kPadButtons = 0x7E094Cu;
inline constexpr u32 kPadHeld = 0x7E094Eu;
inline constexpr u32 kPadPressed = 0x7E0952u;
inline constexpr u32 kPadPressed2 = 0x7E0956u;
inline constexpr u32 kPadRepeat = 0x7E095Au;
}  // namespace title

// --- op_root.c ---------------------------------------------------------------------------------------------------
void sub_265030(EEContext& ctx);                 // [opRoot_Update] the 19-state op root, then the per-frame modules
void sub_265B30(EEContext& ctx);                 // [opRoot_StartMemcardCheck] Y_McProc_CreateMcProcDrawTask -> +16, state 11
void sub_265BB0(EEContext& ctx);                 // [opRoot_StartLoadMenu] sub_15C460 -> +24, state 14
u64 opRoot_UpdateOpTask(EEContext& ctx);                  // opRoot_UpdateOpTask: 0 while alive, -1 once over
u64 opRoot_UpdateOpDrawTask(EEContext& ctx);                  // opRoot_UpdateOpDrawTask
void sub_265F80(EEContext& ctx);                 // [opRoot_EndTitle] leaves the title (states 8 / 9 / 17)
void sub_266060(EEContext& ctx);                 // [opRoot_BackToLogo] state 9
void sub_2660D0(EEContext& ctx);                 // [opRoot_BackToTitle] state 17
// --- gm_root.c ---------------------------------------------------------------------------------------------------
void sub_266140(EEContext& ctx);                 // [gmRoot_Update]
void sub_2663C0(EEContext& ctx);                 // [gmRoot_CreateOpRoot] state 1
void sub_266430(EEContext& ctx);                 // [gmRoot_RestartGame] state 2
u64 gmRoot_UpdateGameRootTask(EEContext& ctx);                  // gmRoot_UpdateGameRootTask: 0 while alive, -1 once over
void sub_266660(EEContext& ctx, u64 mode);       // [gmRoot_SetMode] gp-18784 = mode
// --- op_res.c ----------------------------------------------------------------------------------------------------
void sub_266670(EEContext& ctx);  // [register ABI] [opRes_SetWork]
void sub_266690(EEContext& ctx);                 // [opRes_ClearWork] releases what is loaded
u64 sub_266AE0(EEContext& ctx);                  // [opRes_IsTitleLoading] flags & 1
void sub_266B30(EEContext& ctx);                 // [opRes_ReleaseTitle] 14 textures + 1 image
u64 sub_266BF0(EEContext& ctx, u64 index);       // [opRes_GetTitleTexture] +12[index]
u64 sub_266C50(EEContext& ctx, u64 index);       // [opRes_GetTitleImage] +68[index]
u64 sub_266D70(EEContext& ctx);                  // [opRes_IsLogoLoading] flags & 2
void sub_266DC0(EEContext& ctx);                 // [opRes_ReleaseLogo] 2 textures
u64 sub_266E50(EEContext& ctx, u64 index);       // [opRes_GetLogoTexture] +76[index]
// --- op_title.c --------------------------------------------------------------------------------------------------
void sub_2673A0(EEContext& ctx);  // [register ABI] [opTitle_SetWork]
void sub_2673F0(EEContext& ctx);                 // [opTitle_ClearWork]
void sub_2692D0(EEContext& ctx);                 // [opTitle_Init] the sprites, 9 particles, 3 random seeds
void sub_2694B0(EEContext& ctx);                 // [opTitle_Stop] flags &= ~1
void sub_269500(EEContext& ctx);                 // [opTitle_ShowLogo] +4 = +8 = 0, flags |= 4
void sub_269550(EEContext& ctx);                 // [opTitle_ShowMenu] +4 = 0, +8 = 1, flags |= 4
void sub_2695B0(EEContext& ctx);                 // [opTitle_SkipFade] +4 = 200
u64 sub_269640(EEContext& ctx);                  // [opTitle_IsShowing] flags & 4
void sub_269A10(EEContext& ctx);  // [register ABI] [opTitle_ForEachGridPoint] calls visitor->fn per point
void sub_269C80(EEContext& ctx);                 // sinf($f12)
void sub_269CA0(EEContext& ctx);                 // cosf($f12)
// --- op_logo.c ---------------------------------------------------------------------------------------------------
void sub_269CC0(EEContext& ctx);  // [register ABI] [opLogo_SetWork]
void sub_269D10(EEContext& ctx);                 // [opLogo_ClearWork]
void sub_269D50(EEContext& ctx);                 // [opLogo_Update] the two logo fades
void sub_26A0F0(EEContext& ctx);                 // [opLogo_Init]
u64 sub_26A1E0(EEContext& ctx);                  // [opLogo_IsRunning] flags & 1
// --- op_menu.c ---------------------------------------------------------------------------------------------------
void opMenuSetWork(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
void sub_26A280(EEContext& ctx);                 // [opMenu_ClearWork]
void sub_26D430(EEContext& ctx);                 // [opMenu_Init] the two item lists (4 + 2 items)
void sub_26DA10(EEContext& ctx);                 // [opMenu_Stop]
void sub_26DA90(EEContext& ctx, u64 item);       // [opMenu_SelectTitleItem] list 1 (4 items, +2808)
void sub_26DB30(EEContext& ctx, u64 item);       // [opMenu_SelectContinueItem] list 2 (2 items, +6736)
void sub_26DBD0(EEContext& ctx);                 // [opMenu_ShowContinue] flags |= 0x20
void sub_26DC20(EEContext& ctx);                 // [opMenu_HideContinue] flags &= ~0x20
void sub_26DC70(EEContext& ctx);                 // [opMenu_Show] +2332 = 0, flags |= 4
u64 sub_26DCC0(EEContext& ctx);                  // [opMenu_IsFading] flags & 8
// --- op_wait.c ---------------------------------------------------------------------------------------------------
void sub_26DD10(EEContext& ctx);  // [register ABI] [opWait_SetWork]
void sub_26DD60(EEContext& ctx);                 // [opWait_ClearWork]
void sub_26DDC0(EEContext& ctx);                 // [opWait_Update] the animation counters, then the draw
void sub_26E780(EEContext& ctx);                 // [opWait_Init]
void sub_26EBF0(EEContext& ctx);                 // [opWait_Stop]
void sub_26EC50(EEContext& ctx);                 // [opWait_ShowStart] +8 = +4 = 0, flags |= 4
void sub_26ECA0(EEContext& ctx);                 // [opWait_CreateFades] two sub_269690 objects
void sub_26ED40(EEContext& ctx);                 // [opWait_DestroyFades]
void sub_26EDB0(EEContext& ctx);                 // [opWait_ShowPressStart] = sub_26EDD0
void sub_26EDD0(EEContext& ctx);                 // +8 = 0, +4 = 1, flags |= 4
u64 sub_26EE30(EEContext& ctx);                  // [opWait_IsShowing] flags & 4
u64 sub_26EE80(EEContext& ctx);                  // [opWait_IsFading] flags & 8

}  // namespace p3fes::game
