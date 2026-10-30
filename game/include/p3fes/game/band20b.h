// Phase 5 slice band20b: the functions band20 left in 0x200000-0x23FFFF and 0x320000-0x32FFFF, and the open model
// band 0x310000-0x31FFFF (116 functions). game/src/battle/band20b_bcm.cpp (7), band20b_panel.cpp (22),
// band20b_shuffle.cpp (55), game/src/model/band20b_model.cpp (3), game/src/fx/band20b_fx.cpp (29); pair tests in
// tests/game/test_band20b.cpp.
//
// What is here (callers, K_Assert file strings, band20.h / battle_cmd_menu.h, the merged slices fx2 / fx_types /
// fx_layers / models):
//   bcm_main.c     the TACTICS list's open / decide steps and the two printf-debug previews of the skill / item window
//                  (records of battle_cmd_menu.h, namespace bcm).
//   bcm_panel.c    the command panel's tactics-list state (band20.h b20::kBcm*, plus kBcp* below).
//   baus_main.c    the auto-battle setting display's build and its digits; bpp_main.c the member-panel open / close /
//                  flash by party id; bsa_main.c the analysis panel's open; bse_main.c's accessors; bi_main.c the
//                  battle info pop-ups' per-frame update.
//   Shuffle Time   sfl_data.c tables, gc_model.c (the card model: update, matrix, lighting grid), sfl_res.c accessors,
//                  sfl_psel.c (the persona select: open, update, layout, draw, rows), gc_res.c lookups, sfl_ground.c
//                  (the ground's layout and its start / reset set-ups), sfl_panel.c's two starts.
//   0x31xxxx       a model's shadow pass, its weapon attachments, its motion / sound file request.
//   0x32xxxx       the effect manager's layer drawer and its seven draw tasks, effect-record / class-instance
//                  creation, copy and children, the class instance's update, the particle-system type updates and two
//                  scale slots.
//
// How chosen: a temporary first-call counter in every still-recompiled function of the bands (patched into
// recomp/generated of the gate tree, never committed) on the six routes: of the 116 taken, 46 run on some route (dorm 7,
// m1 7, battle 22, fusion 16, shop 7, the full climb 43; hottest: the layer drawer sub_321360, 207,053 calls; the shadow
// pass sub_3151D0, 51,326; the seven layer draw tasks, 29,561 each; the class instance's children / update, ~25,000;
// the battle info pop-ups, 12,253; the climb also opens the persona select and the TACTICS list). The other 70 are
// reachable only from screens the routes do not open (the analysis panel, the debug previews, the persona select's
// other states, the card model's set-ups, the effect copies). Left out: the functions other slices' tests
// stand in with recorders (test_shuffle 0x20B250 0x20C400 0x20C500 0x20E2C0 0x21A670 0x21A760 0x21A920 0x21AB80
// 0x23C280; test_field3_units / test_field3_event / test_models / test_events* / test_anim 0x313490 0x3138E0
// 0x314850 0x314D30 0x316E00 0x316F70 0x3170C0 0x319970 0x31AAD0 0x31B820 0x31C820 0x31E8D0 0x31EF80 0x324BD0
// 0x3252A0 0x325920; test_fx2 0x324160 0x329890 0x329A60 0x329BA0 0x32A770 0x32A890) and the three band20 trimmed
// for other tests' rules (0x20F570, 0x21BB60, 0x233E70). Callers of those may call them (the relaxed callee rule).
//
// The bodies come from p3fes_handgen and keep every register, frame slot, $ra link, cycle charge and check point of the
// recompiled body; the .cpp files add the names (a role per function, [proposed name] first), the named offsets below
// and band20.h's / battle_cmd_menu.h's (a constant replaces only a literal of its own value), the K_Assert(file, line)
// calls (`jr $ra` in retail: a failed check carries on) and the callees' roles.
//
// Co-op note (end-goal-engine-mmo): presentation only, as band20: these bodies read battle / party / persona state and
// write their own works, quads, font chains, effect records and model attachments. Two inputs matter for a faithful
// client: the persona select's release (sub_215FC0 state 2) removes a persona from the stock list it shows -- the stock
// change itself is made by its caller from sub_2174D0's list --, and sub_31E4D0 picks a character's motion file from the
// held weapon type and story flags, so a client must see the same equipment and flags.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace b20b {

// --- bcm_main.c work (battle_cmd_menu.h names the rest) ----------------------------------------------------------------
inline constexpr s32 kBmListKind = 28;          // u32: the list sub-state (1 target selection after "Assign Target")
inline constexpr s32 kBmPreviewMarks = 28976;   // u32: the preview's marks (bit 0 usable, 1 payable) / item title copy
inline constexpr s32 kBmPreviewValue = 28980;   // u32: the title chain / the stock count
inline constexpr s32 kBmPreviewSide = 28984;    // u32: 1 one target, 0 all
inline constexpr s32 kBmPreviewCost = 28988;    // u32: HP / SP cost of the previewed skill
inline constexpr s32 kBmSkillCursor = 30308;    // s32: the skill window's cursor (index into kSkills)
inline constexpr s32 kBmItemCursor = 30360;     // s32: the item window's cursor (index into kItems)
inline constexpr s32 kBmTargetCursor = 30464;   // s32: the selected target row (kTargets + 24 i)
inline constexpr s32 kBmTacticCursor = 30504;   // the tactics cursor block {top +4, row +12, shown +8, total +16}
inline constexpr s32 kBmTacticTop = 30508;      // s32
inline constexpr s32 kBmTacticShown = 30512;    // s32
inline constexpr s32 kBmTacticRow = 30516;      // s32: the row under the cursor
inline constexpr s32 kBmTacticTotal = 30520;    // s32

// --- bcm_panel.c work (band20.h b20::kBcm*) ------------------------------------------------------------------------------
inline constexpr s32 kBcpFrameA = 11824;        // quads: the tactics list frame, pages 30 / 31 / 32 / 33 (256 apart)
inline constexpr s32 kBcpFrameMirror = 12848;   // quads x2: pages 30 / 31 mirrored
inline constexpr s32 kBcpSeparators = 13360;    // quads x3: pages 38 / 39 / 38 mirrored
inline constexpr s32 kBcpRowBacks = 14384;      // quads: five row backgrounds (page 44), each with its mirror (512 apart)
inline constexpr s32 kBcpArrowUp = 17456;       // quad: page 37
inline constexpr s32 kBcpArrowDown = 17712;     // quad: page 37 mirrored
inline constexpr s32 kBcpSubList = 18016;       // the sub-list block (1,056-byte rows from +12)
inline constexpr s32 kBcpRowCount = 24680;      // s32: rows of the open list
inline constexpr s32 kBcpRowTop = 24684;        // s32

// --- bsa_main.c: the analysis panel (sub_20FE30's first argument) -------------------------------------------------------
inline constexpr s32 kBsaKind = 0;              // s32: 1 shows the skill names
inline constexpr s32 kBsaFlags = 4;             // u32: 1 open, 2 skills unknown, 4 HP unknown, 8 SP unknown, 0x10 affinities
                                                //      unknown, 0x20 level unknown, 0x40 fading, 0x80 the special enemy 294
inline constexpr s32 kBsaUnit = 8;              // u32: the unit (sub_1FF430)
inline constexpr s32 kBsaEnemyId = 12;          // u16
inline constexpr s32 kBsaNameChain = 16;        // u32: the enemy name's font chain
inline constexpr s32 kBsaSkillChains = 20;      // u32[8]
inline constexpr s32 kBsaSkillCount = 52;       // s32
inline constexpr s32 kBsaLevel = 19520;         // s32: gBtlEnemyTbl +3
inline constexpr s32 kBsaHp = 20048;            // s32: gBtlEnemyTbl +4
inline constexpr s32 kBsaSp = 21088;            // s32: gBtlEnemyTbl +6
inline constexpr s32 kBsaAffinity = 22128;      // s32[9]: 0 .. 4 the affinity marks, 5 normal
inline constexpr s32 kBsaElement = 24480;       // s32: the skill element (7 = none)
inline constexpr s32 kBsaFadeFrame = 42672;     // s32
inline constexpr s32 kBsaFadeMode = 42676;      // s32: 0 in, 1 out
inline constexpr s32 kBsaSkillPages = 42680;    // s16[8]

// --- bse_main.c work -------------------------------------------------------------------------------------------------
inline constexpr s32 kBseResult = 8;            // s32

// --- bp_res.c work (band20.h b20::kBr*) --------------------------------------------------------------------------------
inline constexpr s32 kBprBlock104 = 104;        // u32: heap block (loaded bit 0)

// --- gc_model.c: a card model (sub_20AC90's argument) ----------------------------------------------------------------
inline constexpr s32 kGmFlags = 0;              // u32: bit 0 the life timer runs, 1 the shine, 3 the grid is lit
inline constexpr s32 kGmKind = 4;               // s32: 0 the face, 1 the glow, 2 the back
inline constexpr s32 kGmRot = 16;               // f32[4]: rotation quaternion
inline constexpr s32 kGmPos = 32;               // f32[3]: position
inline constexpr s32 kGmScale = 44;             // f32[3]
inline constexpr s32 kGmParent = 56;            // u32: parent RwFrame (0 none)
inline constexpr s32 kGmTime = 60;              // f32: animation time
inline constexpr s32 kGmRgba = 64;              // u8[4]: colour (+67 alpha)
inline constexpr s32 kGmLife = 68;              // s32: 16.16 frames
inline constexpr s32 kGmLifeMode = 72;          // s32: 0 ends after 30 frames
inline constexpr s32 kGmGrid = 220;             // u32: the lighting grid (sub_20CF20)
inline constexpr s32 kGmVerts = 224;            // the vertex block (sub_20C7B0)
inline constexpr s32 kGmShow = 368;             // u32: bit 0 the face, 1 the shine
inline constexpr s32 kGmGlow = 808;             // f32
inline constexpr s32 kGmGlowAlpha = 812;        // f32

// --- sfl_psel.c work (band20.h b20::kPs*) -------------------------------------------------------------------------------
inline constexpr s32 kPsTotal = 4;              // s32: entries in the list (16-byte entries from kPsEntries)
inline constexpr s32 kPsStock = 8;              // s32: personas in stock (sub_175410)
inline constexpr s32 kPsEntries = 16;           // {u32 flags (1 released, 2 from the compendium, 4 locked), u16 id,
                                                //  u32 arcana +8, u32 level +12} [kPsTotal]
inline constexpr s32 kPsRows = 336;             // 2,320-byte rows [8]: quads, the name chain at row +2304
inline constexpr s32 kPsCaptionRow = 18896;     // a row record for the caption
inline constexpr s32 kPsOrder = 21216;          // s32[20]: entry index of each list position
inline constexpr s32 kPsOrderCount = 21296;     // s32
inline constexpr s32 kPsState = 21300;          // s32: 0 browse, 1 / 3 / 4 a message, 2 the yes / no answer, 5 done, 6 closing
inline constexpr s32 kPsSubState = 21304;       // s32: state 0's status view 0..4
inline constexpr s32 kPsPanelQuads = 21312;     // quads x5: pages 49 / 50 / 56 / 57 / 51
inline constexpr s32 kPsQuad50 = 21568;         // quad
inline constexpr s32 kPsQuad56 = 21824;         // quad
inline constexpr s32 kPsQuad57 = 22080;         // quad
inline constexpr s32 kPsQuad51 = 22336;         // quad
inline constexpr s32 kPsCountDigits = 22592;    // quads x2: entries + 1
inline constexpr s32 kPsStockDigits = 23104;    // quads x2: the stock count
inline constexpr s32 kPsAlpha = 23616;          // f32: the list fade 0..1
inline constexpr s32 kPsFadeFrame = 23620;      // s32: 0..6
inline constexpr s32 kPsFadeIn = 23624;         // s32: 1 in, 0 out
inline constexpr s32 kPsCaptionAlpha = 23628;   // f32
inline constexpr s32 kPsCaptionFrame = 23632;   // s32: 0..3
inline constexpr s32 kPsCaptionIn = 23636;      // s32
inline constexpr s32 kPsCaptionEntry = 23640;   // s32: the caption's entry
inline constexpr s32 kPsCursor = 23644;         // the list cursor block of sub_24A260: {flags, top, shown, cursor, total}
inline constexpr s32 kPsTop = 23648;            // s32
inline constexpr s32 kPsShown = 23652;          // s32
inline constexpr s32 kPsCursorRow = 23656;      // s32: the entry position under the cursor
inline constexpr s32 kPsCursorTotal = 23660;    // s32
inline constexpr s32 kPsRowColours = 23664;     // u8[8][4]
inline constexpr s32 kPsBarTop = 23696;         // quad: page 30 (the scroll bar's top)
inline constexpr s32 kPsBarMid = 23952;         // quad: page 30 mirrored (stretched)
inline constexpr s32 kPsBarEnd = 24208;         // quad: page 31
inline constexpr s32 kPsThumb = 24464;          // quad: page 29
inline constexpr s32 kPsAnswer = 24720;         // s32: the status view's answer

// --- sfl_ground.c work (band20.h b20::kSg*) ------------------------------------------------------------------------------
inline constexpr s32 kSgTimer8 = 8;             // s32
inline constexpr s32 kSgFloorQuad = 16;         // quad: base raster 0
inline constexpr s32 kSgSparkles = 3344;        // 304-byte sparkles [48] {flags, kind +4, quad +16, age +272, life +276,
                                                //  pos +280 / +284, target +288 / +292}
inline constexpr s32 kSgFullQuad = 18192;       // quad: effect raster 5
inline constexpr s32 kSgRings = 18448;          // 1,056-byte card rings [7] (quads +16, phase +1040, seed +1048)
inline constexpr s32 kSgBands = 25840;          // quads x6: effect raster 3
inline constexpr s32 kSgTimer = 27376;          // s32: 120 at the start
inline constexpr s32 kSgFloor = 27400;          // 64-byte vertices [9][11]

// --- sfl_panel.c work (band20.h b20::kSpn*) ------------------------------------------------------------------------------
inline constexpr s32 kSpnTitleQuads = 528;      // quads x2: effect raster 0
inline constexpr s32 kSpnNumberQuads = 1040;    // quads x3: effect raster 1

// --- bi_main.c: a battle info pop-up (3,920 bytes, band20.h b20::kBi*) ------------------------------------------------
inline constexpr s32 kBiKind = 4;               // s32: the pop-up kind (jump table)
inline constexpr s32 kBiAge = 784;              // s32: frames shown, up to 50
inline constexpr s32 kBiUnitId = 788;           // u16
inline constexpr s32 kBiCrossH = 3392;          // quad
inline constexpr s32 kBiCrossV = 3648;          // quad

// --- an effect definition (sub_324680 / sub_326510's argument) -------------------------------------------------------
inline constexpr s32 kFdClass = 4;              // u16: the class row (0x69BE20 + 52 class)
inline constexpr s32 kFdType = 12;              // u16: the particle-system type
inline constexpr s32 kFdKind = 28;              // u16: the instance kind (1 / 2 / 4 / 5 / 6 / 7)

// --- a class instance (band20.h b20::kFi*) ------------------------------------------------------------------------
inline constexpr s32 kFiFrame = 4;              // s32: -1 at creation
inline constexpr s32 kFiScale = 8;              // f32: 1.0 at creation
inline constexpr s32 kFiKind = 12;              // u16: the instance kind (sub_326510)

// --- a model (sub_31C1D0's argument) ---------------------------------------------------------------------------------
inline constexpr s32 kMdlAlpha = 211;           // u8: the model's alpha
inline constexpr s32 kMdlKind = 212;            // u16: 1 a character
inline constexpr s32 kMdlCharacter = 214;       // s16: the party member id
inline constexpr s32 kMdlShadowFlags = 904;     // u8: 1 / 0x20 the light source, 2 follow the light, 4 straight down
inline constexpr s32 kMdlShadowRot = 908;       // f32[4]: the shadow's current light quaternion
inline constexpr s32 kMdlShadowSquash = 924;    // f32
inline constexpr s32 kMdlShadowSquashTo = 928;  // f32
inline constexpr s32 kMdlShadowSquashStep = 932;// f32
inline constexpr s32 kMdlShadowAlpha = 936;     // u8: eased towards +937 by +938 a frame
inline constexpr s32 kMdlShadowAlphaTo = 937;   // u8
inline constexpr s32 kMdlShadowAlphaStep = 938; // u8
inline constexpr s32 kMdlShadowMinTurn = 940;   // f32: 1.0 jumps to the light at once
inline constexpr s32 kMdlShadowTurnRate = 944;  // f32: the largest turn a frame (radians)

}  // namespace b20b

// One line per function: [proposed name] and role (the .cpp files have the detail).
// bcm_main.c / bcm_panel.c (src/battle/band20b_bcm.cpp)
void sub_202830(EEContext& ctx);  // [bcmMain_DebugSkillPreview] the skill window's preview line (debug path)
void sub_203630(EEContext& ctx);  // [bcmMain_DebugItemPreview] the item window's preview line (debug path)
void sub_2057C0(EEContext& ctx);  // [bcmMain_StartTacticsList] opens the TACTICS list
void sub_2063F0(EEContext& ctx);  // [bcmMain_DecideTactic] stores the chosen tactic / starts "Assign Target"
void sub_2254A0(EEContext& ctx);  // [bcmPanel_OpenTacticsList] the command panel's tactics-list state
void sub_227D10(EEContext& ctx);  // [bcmPanel_BuildListFrame] the tactics list's frame quads
void sub_22C1D0(EEContext& ctx);  // [bcmPanel_ResetSubStep] sub-step 0
// the battle panels (src/battle/band20b_panel.cpp)
void sub_208B30(EEContext& ctx);  // [bausMain_Build] the auto-battle setting display's entries and quads
void sub_2094F0(EEContext& ctx);  // [bausMain_Hide] clears flag bit 0
void sub_209940(EEContext& ctx);  // [bausMain_SetNumber](quads, n, value) digit pages, last digit first
void sub_209BA0(EEContext& ctx);  // [bausMain_SetDigit](quad, digit) panel set 1 page 46 + digit
void sub_20F7D0(EEContext& ctx);  // [bppMain_OpenMemberPanel](u16 id)
void sub_20F8B0(EEContext& ctx);  // [bppMain_CloseMemberPanel](u16 id)
void sub_20FA80(EEContext& ctx);  // [bppMain_FlashMember](u16 id)
void sub_20FB60(EEContext& ctx);  // [bppMain_StopFlashMember](u16 id)
void sub_20FCE0(EEContext& ctx);  // [bppMain_SetFlag20]
void sub_20FD30(EEContext& ctx);  // [bppMain_ClearFlag20]
void sub_20FE30(EEContext& ctx);  // [bsaPanel_Open](panel, kind, unit) the analysis panel of an enemy
void sub_210D60(EEContext& ctx);  // [bsaPanel_StartClose](panel)
void sub_215A30(EEContext& ctx);  // [bsaPanel_IsOpen](panel)
void sub_215A40(EEContext& ctx);  // [bsaPanel_IsFading](panel)
void sub_21B6F0(EEContext& ctx);  // [bseMain_IsBusy]
void sub_21B740(EEContext& ctx);  // [bseMain_IsDone]
void sub_21B7C0(EEContext& ctx);  // [bseMain_GetResult]
void sub_21B830(EEContext& ctx);  // [bseMain_Finish]
void sub_21C720(EEContext& ctx);  // [bpRes_GetBlock104]
void sub_233790(EEContext& ctx);  // [bppPanel_StartOpenAnim](panel) flag bit 3
void sub_2337B0(EEContext& ctx);  // [bppPanel_StartCloseAnim](panel)
void sub_23F540(EEContext& ctx);  // [biMain_Update] the battle info pop-ups' frame
// Shuffle Time (src/battle/band20b_shuffle.cpp)
void sub_209C40(EEContext& ctx);  // [sflData_GetTableK]
void sub_209CC0(EEContext& ctx);  // [sflData_GetTableL]
void sub_20AB30(EEContext& ctx);  // [gcModel_InitBack](model)
void nullsub_66(EEContext& ctx);  // an empty hook (jr $ra)
void sub_20AC90(EEContext& ctx);  // [gcModel_Update](model)
void sub_20C320(EEContext& ctx);  // [gcModel_ToScreenDepth](z, xy*, out*)
void sub_20C7A0(EEContext& ctx);  // [gcModel_SetParent](model, frame)
void sub_20CA90(EEContext& ctx);  // [gcModel_BuildMatrix](matrix, model)
void sub_20CF20(EEContext& ctx);  // [gcModel_LightGrid](grid, model)
void sub_20D670(EEContext& ctx);  // [gcModel_GetPosition](model, out*)
void sub_20D690(EEContext& ctx);  // [gcModel_SetRotation](model, quat*)
void sub_20D6C0(EEContext& ctx);  // [gcModel_ShowFront](model)
void sub_20D710(EEContext& ctx);  // [gcModel_ShowShine](model)
void sub_20D770(EEContext& ctx);  // [gcModel_SetGlow](model, v)
void sub_20E710(EEContext& ctx);  // [sflRes_GetBaseBlock2](i)
void sub_20E8F0(EEContext& ctx);  // [sflRes_RequestTutorial]
void sub_20E9B0(EEContext& ctx);  // [sflRes_IsTutorialRequested]
void sub_20EA00(EEContext& ctx);  // [sflRes_GetTutorialBlock](i)
void sub_20EC50(EEContext& ctx);  // [sflRes_GetSprSet]
void sub_215B00(EEContext& ctx);  // [sflPsel_Open]
void sub_215FC0(EEContext& ctx);  // [sflPsel_Update]
void sub_2168A0(EEContext& ctx);  // [sflPsel_IsRunning]
void sub_2168F0(EEContext& ctx);  // [sflPsel_Draw]
void sub_2170C0(EEContext& ctx);  // [sflPsel_BuildRowChains]
void sub_217350(EEContext& ctx);  // [sflPsel_RebuildRowChains]
void sub_217410(EEContext& ctx);  // [sflPsel_GetKept](ids*, count*)
void sub_2174D0(EEContext& ctx);  // [sflPsel_GetReleased](ids*, count*)
void sub_217590(EEContext& ctx);  // [sflPsel_AddEntry](u16 id)
void sub_217610(EEContext& ctx);  // [sflPsel_SetRowQuads]
void sub_217780(EEContext& ctx);  // [sflPsel_Layout]
void sub_2180B0(EEContext& ctx);  // [sflPsel_ArcanaPage](arcana) -> page
void sub_218250(EEContext& ctx);  // [sflPsel_SetNumber](quads, n, value)
void sub_218310(EEContext& ctx);  // [sflPsel_SetDigit](quad, digit)
void sub_218370(EEContext& ctx);  // [sflPsel_PlaceNumberL](quads, n, value, xy*) 27 px digits, centred
void sub_218570(EEContext& ctx);  // [sflPsel_PlaceNumberS](quads, n, value, xy*) 19 px digits, centred
void sub_2187B0(EEContext& ctx);  // [sflPsel_FadeIn]
void sub_218810(EEContext& ctx);  // [sflPsel_SetRowPages](row, entry, lit)
void sub_218B20(EEContext& ctx);  // [sflPsel_LayoutRow](row, entry, lit, xy*)
void sub_219370(EEContext& ctx);  // [sflPsel_DrawRow](row, entry, lit)
void sub_219970(EEContext& ctx);  // [sflPsel_OpenCaption]
void sub_219AB0(EEContext& ctx);  // [sflPsel_CloseCaption]
void sub_219B90(EEContext& ctx);  // [sflPsel_AskRelease]
void sub_21AD40(EEContext& ctx);  // [gcRes_FindPair](a, b)
void sub_21B080(EEContext& ctx);  // [gcRes_FindId](u16 id)
void sub_239280(EEContext& ctx);  // [sflGround_Unregister]
void sub_2392D0(EEContext& ctx);  // [sflGround_Layout]
void sub_23C3A0(EEContext& ctx);  // [sflGround_SetBannerQuads](quads)
void sub_23CA10(EEContext& ctx);  // [sflGround_StartA]
void sub_23CD50(EEContext& ctx);  // [sflGround_IsShown2]
void sub_23CDA0(EEContext& ctx);  // [sflGround_StartB]
void sub_23D240(EEContext& ctx);  // [sflGround_Reset]
void sub_23D2A0(EEContext& ctx);  // [sflGround_InitSparkles]
void sub_23D650(EEContext& ctx);  // [sflGround_InitFloor]
void sub_23F010(EEContext& ctx);  // [sflPanel_StartA]
void sub_23F1D0(EEContext& ctx);  // [sflPanel_StartB]
// the model band (src/model/band20b_model.cpp)
void sub_3151D0(EEContext& ctx);  // [mdlDrawShadow](model)
void sub_31C1D0(EEContext& ctx);  // [mdlAttachWeapons](model) -> 1 for a character
void sub_31E4D0(EEContext& ctx);  // [mdlRequestMotionFile](slot*, kind, id)
// the effect system (src/fx/band20b_fx.cpp)
void sub_321360(EEContext& ctx);  // [effMng_DrawLayer](u16 layer)
void sub_321B00(EEContext& ctx);  // [effMng_DrawLayer0Task]
void sub_321C50(EEContext& ctx);  // [effMng_DrawLayer1Task]
void sub_321CE0(EEContext& ctx);  // [effMng_DrawLayer3Task]
void sub_321D40(EEContext& ctx);  // [effMng_DrawLayer4Task]
void sub_321E50(EEContext& ctx);  // [effMng_DrawLayer6Task]
void sub_321EB0(EEContext& ctx);  // [effMng_DrawLayer7Task]
void sub_324470(EEContext& ctx);  // [fxMesh_SetIdentity](mesh)
void sub_324680(EEContext& ctx);  // [fxEffect_CreateFromDef](def)
void sub_324870(EEContext& ctx);  // [fxEffect_Clone](rec)
void sub_3257A0(EEContext& ctx);  // [fxNode_StepAndDraw](node)
void sub_326490(EEContext& ctx);  // [fxInst_Create](n)
void sub_326510(EEContext& ctx);  // [fxInst_CreateFromDef](def)
void sub_3268C0(EEContext& ctx);  // [fxInst_Clone](inst)
void sub_3269E0(EEContext& ctx);  // [fxInst_CopyKind](dst, src)
void sub_326F60(EEContext& ctx);  // [fxInst_SetEffects](inst, def)
void sub_327090(EEContext& ctx);  // [fxInst_SetTrees](inst, def)
void sub_327250(EEContext& ctx);  // [fxInst_StepChildren](inst)
void sub_3275D0(EEContext& ctx);  // [fxInst_Update](inst, alpha)
void sub_32AF30(EEContext& ctx);  // [fxPsysUpdateA](psys)
void sub_32BA30(EEContext& ctx);  // [fxPsysUpdateB](psys)
void sub_32C340(EEContext& ctx);  // [fxPsysUpdateC](psys)
void sub_32CE10(EEContext& ctx);  // [fxPsysUpdateD](psys)
void sub_32D840(EEContext& ctx);  // [fxPsysUpdateE](psys)
void sub_32E1A0(EEContext& ctx);  // [fxPsysUpdateF](psys)
void sub_32EAB0(EEContext& ctx);  // [fxPsysScaleF](psys, s)
void sub_32EB40(EEContext& ctx);  // [fxPsysUpdateG](psys)
void sub_32F8B0(EEContext& ctx);  // [fxPsysScaleG](psys, s)
void sub_32F910(EEContext& ctx);  // [fxPsysUpdateH](psys)

}  // namespace p3fes::game
