// The battle UI band 0x1EF500-0x26503C and the battle band's UI part 0x271230-0x27BBA0, third pass (slice battle_ui3;
// docs/ANALYSIS/27_unmapped_bands.md section 3): the module works of the result / panel / command-menu / shuffle files
// and their leaves -- init ("register the work"), flag and lookup accessors, the panel / result sprite set-ups, the
// card-model geometry builders of gc_model.c, the shuffle data tables of sfl_data.c.
// game/src/battle/battle_ui3.cpp; the bodies come from p3fes_handgen (register ABI: arguments in $a0.., the result in
// $v0), made readable with the layouts below. Names: functions.json names in code; ours in brackets in the comments and
// in symbols/deltas/battle_ui3.sym (ADR-0009).
//
// The module works. Each .c file of the band keeps one work block behind a $gp slot (the table 0x7CE298 + 4k): an
// "init" function stores the block's address there (most assert first that the slot is still empty: K_Assert(file,
// line), `jr $ra` in retail, so a bad state carries on), and every accessor asserts the slot is set before it reads.
// The file each slot belongs to is the K_Assert string of its accessors (obs). Offsets are decimal, as the instructions
// give them.
//
// The 2D quads: 256-byte four-vertex strips (64-byte vertices) filled by the battle_panel helpers (battle_panel.h):
// sub_21D3B0(quad, page) takes a 44-byte page record of a sprite set -- sub_21CCA0(set, i) returns record i --,
// sub_21D8E0(quad, rect) sets x / y / w / h (four floats), sub_21D950(quad, rgba) the colour, sub_21E380(quad, page, m)
// the page with a mirror / colour mode m. The sprite sets come from the resource modules: bp_res.c's sub_21C3F0(i) (the
// panel), br_res.c's sub_233D70 / sub_234630 (the result screen).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace bui3 {

// --- $gp slots (gp = 0x7D2CF0) ------------------------------------------------------------------------------------------
inline constexpr s32 kGpSflRoot = -18964;     // 0x7CE2DC sfl_root.c work (the "shuffle root" task's)
inline constexpr s32 kGpSflRes = -18944;      // 0x7CE2F0 sfl_res.c: the shuffle resources
inline constexpr s32 kGpBppMain = -18940;     // 0x7CE2F4 bpp_main.c: the party panel
inline constexpr s32 kGpSflPsel = -18936;     // 0x7CE2F8 sfl_psel.c: the shuffle persona select
inline constexpr s32 kGpGcRes = -18932;       // 0x7CE2FC gc_res.c: the card textures and models
inline constexpr s32 kGpBseMain = -18928;     // 0x7CE300 bse_main.c
inline constexpr s32 kGpBpRes = -18924;       // 0x7CE304 bp_res.c: the panel resources (sprite sets)
inline constexpr s32 kGpBcmPanel = -18920;    // 0x7CE308 bcm_panel.c: the command panel drawing
inline constexpr s32 kGpSflGround = -18908;   // 0x7CE314 sfl_ground.c: the shuffle ground
inline constexpr s32 kGpSflPanel = -18904;    // 0x7CE318 sfl_panel.c
inline constexpr s32 kGpBpcMain = -18896;     // 0x7CE320 bpc_main.c: the persona-change sub-menu
inline constexpr s32 kGpBpmMain = -18892;     // 0x7CE324 bpm_main.c
inline constexpr s32 kGpBpeMain = -18888;     // 0x7CE328 bpe_main.c
inline constexpr s32 kGpBrpBirth = -18880;    // 0x7CE330 brp_birth.c: the persona birth on level-up (battle_result.h)
inline constexpr s32 kGpSflCamera = -18868;   // 0x7CE33C sfl_camera.c
inline constexpr s32 kGpGcPose = -18864;      // 0x7CE340 the card pose work (registered with sfl_camera's, 0x24DA00)
inline constexpr s32 kGpBpTut = -18860;       // 0x7CE344 bp_tut.c: the panel tutorial
inline constexpr s32 kGpBpTuta = -18856;      // 0x7CE348 bp_tuta.c
inline constexpr s32 kGpBpdMain = -18848;     // 0x7CE350 bpd_main.c: the panel dialog
inline constexpr s32 kGpBpRush = -18820;      // 0x7CE36C bp_rush.c: the all-out-attack prompt
inline constexpr s32 kGpFullQuad = -18808;    // 0x7CE378 a full-screen quad work (sub_260970; no K_Assert string)
inline constexpr s32 kGpBrHero = -18804;      // 0x7CE37C br_hero.c: the result's hero page
inline constexpr s32 kGpBrPersona = -18800;   // 0x7CE380 br_persona.c: the result's persona page
inline constexpr s32 kGpBrpSeq = -18736;      // 0x7CE3C0 brp_seq.c: the level-up sequence
inline constexpr s32 kGpBrLvpnl = -18728;     // 0x7CE3C8 br_lvpnl.c: the "level up" panel
inline constexpr s32 kGpBrpPersona = -18724;  // 0x7CE3CC brp_persona.c
inline constexpr s32 kGpBrpParam = -18720;    // 0x7CE3D0 brp_param.c: the parameter page
inline constexpr s32 kGpBpSelect = -18700;    // 0x7CE3E4 bp_select.c: the selection frame
inline constexpr s32 kGpSflPersona = -18696;  // 0x7CE3E8 sfl_persona.c
inline constexpr s32 kGpBtl = -18692;         // 0x7CE3EC gBtl
inline constexpr s32 kGpEncountTbl = -18504;  // 0x7CE4A8 gEncountTbl (28-byte records)
// f32 constants of the card geometry (values from the ELF)
inline constexpr s32 kGpCardHalfH = -31976;   // 0x7CB008  3.84f
inline constexpr s32 kGpCardNegHalfH = -31972;  // 0x7CB00C -3.84f
inline constexpr s32 kGpCardHalfW = -31968;   // 0x7CB010  2.3203125f
inline constexpr s32 kGpCardHalfH2 = -31964;  // 0x7CB014  3.15f
inline constexpr s32 kGpCardBackY = -31948;   // 0x7CB024 -3.84f
inline constexpr s32 kGpCardRowStep = -31944; // 0x7CB028  0.96f (the grid's row pitch)

// --- the common work header -------------------------------------------------------------------------------------------
inline constexpr s32 kWkFlags = 0;            // u32: state bits (per module, below)
inline constexpr s32 kWkLoaded = 4;           // u32: the resource modules' "loaded" mask; the state of others

// --- gc_model.c: the card model (an argument; 0x209EA0 / 0x209F00 / 0x20A800) ------------------------------------------
inline constexpr s32 kGcmFlags = 0;           // u32: bit 3 the 68-vertex grid is set (sub_20CD50)
inline constexpr s32 kGcmKind = 4;            // u32: 0 (sub_209F00) or 1 (sub_20A800): which builder made it
inline constexpr s32 kGcmScale = 44;          // f32[3] = 1.0 at init
inline constexpr s32 kGcmColour = 64;         // u8[4] RGBA = 0xFF at init
inline constexpr s32 kGcmGrid = 220;          // u32: the 68-vertex grid (sub_20CDA0)
inline constexpr s32 kGcmQuad0 = 224;         // the first 4-vertex quad (36-byte vertices: xyz, RGBA, uv)
inline constexpr s32 kGcmParamA = 368;        // u32: kind 1's first parameter (sub_20C5F0)
inline constexpr s32 kGcmParamB = 372;        // u16 / u32: the card id (sub_20C590 kind 0) or the second parameter
inline constexpr s32 kGcmQuadSize = 144;      // 4 x 36
inline constexpr s32 kGcvXyz = 0, kGcvRgba = 12, kGcvUv = 28, kGcvSize = 36;  // a card vertex
inline constexpr s32 kGridVerts = 68;         // 9 rows of 8 / 7 vertices (sub_20CDA0's K_Assert)

// --- sfl_res.c (kGpSflRes) ------------------------------------------------------------------------------------------
inline constexpr s32 kSrBase = 8;             // u32[3]: the base files (loaded bit 0)
inline constexpr s32 kSrGround = 20;          // u32[]: the ground files (loaded bit 1)
inline constexpr s32 kSrEffect = 64;          // u32[]: the effect files (loaded bit 2)

// --- bpp_main.c (kGpBppMain) ----------------------------------------------------------------------------------------
inline constexpr s32 kBppRecords = 16;        // 5,776-byte member records
inline constexpr s32 kBppRecordSize = 5776;
inline constexpr s32 kBppRecId = 4;           // u16 in a record (work + 20)
inline constexpr s32 kBppCount = 23120;       // s32 records in use

// --- gc_res.c (kGpGcRes) --------------------------------------------------------------------------------------------
inline constexpr s32 kGrState = 0;            // u32
inline constexpr s32 kGrResA = 4;             // u32: resource A (loaded bit 0 of +12)
inline constexpr s32 kGrResB = 8;             // u32: resource B (bit 1)
inline constexpr s32 kGrLoaded = 12;          // u32: loaded mask
inline constexpr s32 kGrTableC = 32;          // u32[]: (bit 2)
inline constexpr s32 kGrTableD = 60;          // u32[]: (bit 3)
inline constexpr s32 kGrPairs = 76;           // 16 x 20 bytes { flags, key a, key b, value, refs }
inline constexpr s32 kGrPairSize = 20;
inline constexpr s32 kGrPairCount = 16;
inline constexpr s32 kPrFlags = 76, kPrKeyA = 80, kPrKeyB = 84, kPrValue = 88, kPrRefs = 92;  // work + 20i + these
inline constexpr s32 kGrIds = 396;            // 16 x 16 bytes { flags, u16 id, value, refs }
inline constexpr s32 kGrIdSize = 16;
inline constexpr s32 kGiFlags = 396, kGiId = 400, kGiValue = 404, kGiRefs = 408;  // work + 16i + these
inline constexpr s32 kGrSlots = 652;          // 32 x 292-byte slots (flags at +0)
inline constexpr s32 kGrSlotSize = 292;

// --- bse_main.c (kGpBseMain) ----------------------------------------------------------------------------------------
inline constexpr s32 kBseArg = 4;             // u32: the value handed to sub_1FE510

// --- bp_res.c (kGpBpRes) --------------------------------------------------------------------------------------------
inline constexpr s32 kBrFlags = 0;            // u32: bit 0 loaded (sub_21BAB0), bit 2 the tutorial file (sub_21C860)
inline constexpr s32 kBrLoaded = 4;           // u32: bit 0 the sets of +36 / +56 / +96, bit 8 the three +120 blocks
inline constexpr s32 kBrSets = 16;            // u32[]: the panel sprite sets (sub_21C3F0)
inline constexpr s32 kBrSetOne = 36;          // u32: the set of id 1
inline constexpr s32 kBrIdSets = 56;          // u32[]: the set of each id in +72
inline constexpr s32 kBrIdCount = 68;         // s32
inline constexpr s32 kBrIds = 72;             // u32[]
inline constexpr s32 kBrMore = 96;            // u32[]
inline constexpr s32 kBrValue108 = 108;       // u32 (sub_21BB00)
inline constexpr s32 kBrBlocks = 120;         // u32[3]: heap blocks (freed by sub_21C930 through RwFree)

// --- bcm_panel.c (kGpBcmPanel) --------------------------------------------------------------------------------------
inline constexpr s32 kBcmFlags = 0;           // u32: bit 1 a sub-list is open
inline constexpr s32 kBcmList = 4;            // u32: the sub-list kind (1, 2, 4, 8)
inline constexpr s32 kBcmQuadCur = 4656;      // quad: the current command's page
inline constexpr s32 kBcmQuadPrev = 4912;     // quad: the previous command's page
inline constexpr s32 kBcmFrame = 5424;        // the frame quads of sub_226320 (5424 .. 8496)
inline constexpr s32 kBcmTitle = 16944;       // quad: the sub-list title
inline constexpr s32 kBcmTitle2 = 17200;      // quad: the same page, mode 1
inline constexpr s32 kBcmState = 17968;       // u32: 1 / 2 / 8 cursor states, 3 a sub-list
inline constexpr s32 kBcmCur = 17972;         // u32: the current command
inline constexpr s32 kBcmPrev = 17976;        // u32: the previous one
inline constexpr s32 kBcmSub = 17980;         // u32: the sub-list state (1..4)
inline constexpr s32 kBcmSubPrev = 17984;     // u32
inline constexpr s32 kBcmSubStep = 17988;     // u32
inline constexpr s32 kBcmSubSel = 17992;      // s32 (-1 = none)
inline constexpr s32 kBcmTimer = 17996;       // u32: frames since the cursor moved
inline constexpr s32 kBcmSubTimer = 18000;    // u32
inline constexpr s32 kBcmRows = 18016;        // the rows of a sub-list (stride by kind: 1,296 / 1,040 / 1,056 / 784)
inline constexpr s32 kBcmRowCount = 24688;    // s32
inline constexpr s32 kBcmCursorPage = 26868;  // u32: the page (+32) of the cursor quad
inline constexpr s32 kBcmCursorOn = 26872;    // u32
inline constexpr s32 kBcmCursorQuad = 26880;  // quad
inline constexpr s32 kBcmDetailNum2 = 27908;  // s32: the 2-digit number of the detail (sub_22C0E0)
inline constexpr s32 kBcmDetailKind = 27912;  // u32: 0 / 1 -> page 48 / 49 (sub_22BF60)
inline constexpr s32 kBcmDetailNum3 = 27916;  // s32: the 3-digit number of the detail (sub_22BF60)
inline constexpr s32 kBcmFrameMode = 29200;   // u32: 0..2 draw the full frame (sub_226320)

// --- br_lvpnl.c (kGpBrLvpnl) ----------------------------------------------------------------------------------------
inline constexpr s32 kLvFlags = 0;            // u32: bit 0 shown, 1 animating, 2 held, 3 (sub_276870)
inline constexpr s32 kLvQuads = 16;           // six quads: +16, +272, +528, +784, +1040, +1296
inline constexpr s32 kLvFrame = 1552;         // s32: frames into the animation
inline constexpr s32 kLvMode = 1556;          // u32: 0 the long fade (36 frames), 1 the short (33)

// --- brp_seq.c (kGpBrpSeq) ------------------------------------------------------------------------------------------
inline constexpr s32 kBsFlags = 0;            // u32: bit 0, bit 1 (asserted by sub_273980), 0x40 the birth draw
inline constexpr s32 kBsStep = 16;            // u32
inline constexpr s32 kBsMsgState = 24;        // u32
inline constexpr s32 kBsState = 116;          // u32
inline constexpr s32 kBsIndex = 432;          // s32: the entry being shown
inline constexpr s32 kBsCount = 448;          // s32: entries
inline constexpr s32 kBsEntries = 452;        // 8-byte entries { u16 id, (pad), s32 value @+4 }

// --- brp_param.c (kGpBrpParam) --------------------------------------------------------------------------------------
inline constexpr s32 kBpFlags = 0;            // u32: bits 2 / 4 / 5 / 6
inline constexpr s32 kBpMember = 1824;        // per-member stride of +2192 / +2720 / +2724
inline constexpr s32 kBpMemA = 2192, kBpMemB = 2720, kBpMemC = 2724;
inline constexpr s32 kBpValue = 14128;        // u32
inline constexpr s32 kBpNumber = 14132;       // u32: the number shown in the +14160 digits
inline constexpr s32 kBpTimerA = 14140;       // u32
inline constexpr s32 kBpTimerB = 14148;       // u32
inline constexpr s32 kBpDigits = 14160;       // bpIfontDrawNumber target
inline constexpr s32 kBpPairA = 15200, kBpPairB = 15204;

// --- bp_select.c (kGpBpSelect) --------------------------------------------------------------------------------------
inline constexpr s32 kSelFlags = 0;           // u32: bit 0 active, bit 1 closing
inline constexpr s32 kSelQuad = 16;           // quad
inline constexpr s32 kSelFrame = 272;         // s32: fade frames, 0..20
inline constexpr s32 kSelX = 276, kSelY = 280;  // f32
inline constexpr s32 kSelFadeFrames = 20;

}  // namespace bui3

// One line per function: [proposed name] and role (the .cpp has the detail).
// sfl_data.c: the shuffle data tables
void sub_209D00(EEContext& ctx);  // [sflData_GetTableA] the table 0x68CDE0 (The Answer, sub_17D800) or 0x68CA80
void sub_209DC0(EEContext& ctx);  // [sflData_GetTableB] 0x68D140
void sub_209DD0(EEContext& ctx);  // [sflData_GetTableC] 0x68D910 (The Answer) or 0x68D8F0
void sub_209E10(EEContext& ctx);  // [sflData_GetTableD] 0x68D930
void sub_209E20(EEContext& ctx);  // [sflData_GetTableE] 0x68DE20 (The Answer) or 0x68DD20
void sub_209E60(EEContext& ctx);  // [sflData_GetTableF] 0x68DF20
void sub_209E70(EEContext& ctx);  // [sflData_GetTableG] 0x68DF30
// gc_model.c: the card model
void sub_209EA0(EEContext& ctx);  // [gcModel_InitHeader](model)
void sub_209F00(EEContext& ctx);  // [gcModel_Init0](model): kind 0 and its quads
void sub_20A800(EEContext& ctx);  // [gcModel_Init1](model): kind 1 and its quads
void sub_20C590(EEContext& ctx);  // [gcModel_SetCardId](model, u16 id): kind 0 only
void sub_20C5F0(EEContext& ctx);  // [gcModel_SetParams](model, a, b): kind 1 only
void sub_20C7B0(EEContext& ctx);  // [gcModel_InitQuad](quad): a white card quad
void sub_20CCC0(EEContext& ctx);  // [gcModel_SetQuadColour](quad, rgba*)
void sub_20CD50(EEContext& ctx);  // [gcModel_SetGrid](model, grid)
void sub_20CDA0(EEContext& ctx);  // [gcModel_BuildGrid](grid): the 68-vertex card grid
// sfl_res.c
void sub_20D7D0(EEContext& ctx);  // [sflRes_Register](work)
void sub_20DFE0(EEContext& ctx);  // [sflRes_IsBusy] flags & 1
void sub_20E4C0(EEContext& ctx);  // [sflRes_Flag4] flags & 4
void sub_20E510(EEContext& ctx);  // [sflRes_GetGround](i)
void sub_20E590(EEContext& ctx);  // [sflRes_GetBase](i)
void sub_20E690(EEContext& ctx);  // [sflRes_GetEffect](i)
void sub_20EC00(EEContext& ctx);  // [sflRes_Flag10] flags & 0x10
// bpp_main.c
void sub_20F720(EEContext& ctx);  // [bppMain_FindMember](u16 id) -> record
void sub_20FC40(EEContext& ctx);  // [bppMain_SetFlag10]
void sub_20FC90(EEContext& ctx);  // [bppMain_ClearFlag10]
void sub_20FD80(EEContext& ctx);  // [bppMain_SetFlag40]
void sub_215A50(EEContext& ctx);  // [sflPsel_Register](work)
void sub_215830(EEContext& ctx);  // [bsaMain_GetKindPage](kind 1..23) -> page record of panel set 2
// gc_res.c
void sub_219C90(EEContext& ctx);  // [gcRes_Register](work)
void sub_21A3A0(EEContext& ctx);  // [gcRes_GetResA]
void sub_21A410(EEContext& ctx);  // [gcRes_GetResB]
void sub_21A480(EEContext& ctx);  // [gcRes_GetPairValue](a, b)
void sub_21A590(EEContext& ctx);  // [gcRes_GetIdValue](u16 id)
void sub_21AC90(EEContext& ctx);  // [gcRes_HasPair](a, b)
void sub_21AE30(EEContext& ctx);  // [gcRes_RefPair](a, b)
void sub_21AF30(EEContext& ctx);  // [gcRes_FreePairSlot]
void sub_21AFE0(EEContext& ctx);  // [gcRes_HasId](u16 id)
void sub_21B150(EEContext& ctx);  // [gcRes_FreeIdSlot]
void sub_21B1F0(EEContext& ctx);  // [gcRes_RefId](u16 id)
void sub_21B2D0(EEContext& ctx);  // [gcRes_FreeSlot] -> the first free 292-byte slot
void sub_21B3A0(EEContext& ctx);  // [gcRes_GetTableC](i)
void sub_21B420(EEContext& ctx);  // [gcRes_GetTableD](i)
void sub_21B670(EEContext& ctx);  // [bseMain_Start](v)
// bp_res.c
void sub_21BAB0(EEContext& ctx);  // [bpRes_IsLoaded]
void sub_21BB00(EEContext& ctx);  // [bpRes_SetValue108](v)
void sub_21BB50(EEContext& ctx);  // returns 0
void sub_21C3F0(EEContext& ctx);  // [bpRes_GetSet](i) -> panel sprite set
void sub_21C450(EEContext& ctx);  // [bpRes_GetSetById](u16 id)
void sub_21C550(EEContext& ctx);  // [bpRes_GetMore](i)
void nullsub_11(EEContext& ctx);  // empty
void sub_21C860(EEContext& ctx);  // [bpRes_IsTutorialLoaded]
void sub_21C8B0(EEContext& ctx);  // [bpRes_GetBlock](i)
void sub_21C930(EEContext& ctx);  // [bpRes_FreeBlocks]
// bcm_panel.c
void sub_2226F0(EEContext& ctx);  // [bcmPanel_MoveCursor1](cmd)
void sub_2227B0(EEContext& ctx);  // [bcmPanel_MoveCursor2](cmd)
void sub_222870(EEContext& ctx);  // [bcmPanel_ResetCursor]
void sub_222930(EEContext& ctx);  // [bcmPanel_OpenList1]
void sub_222A60(EEContext& ctx);  // [bcmPanel_OpenList2]
void sub_222B90(EEContext& ctx);  // [bcmPanel_SetRows2]
void sub_222D60(EEContext& ctx);  // [bcmPanel_SetRows1]
void sub_222ED0(EEContext& ctx);  // [bcmPanel_CloseList]
void sub_222FA0(EEContext& ctx);  // [bcmPanel_OpenList4]
void sub_2230E0(EEContext& ctx);  // [bcmPanel_SetRows4]
void sub_224660(EEContext& ctx);  // [bcmPanel_OpenList8]
void sub_224860(EEContext& ctx);  // [bcmPanel_SetRows8]
void sub_226320(EEContext& ctx);  // [bcmPanel_SetFrame]
void sub_22B4E0(EEContext& ctx);  // [bcmPanel_IsListOpen]
void sub_22B580(EEContext& ctx);  // [bcmPanel_SetHeader]
void sub_22BF60(EEContext& ctx);  // [bcmPanel_OpenDetail2]
void sub_22C0E0(EEContext& ctx);  // [bcmPanel_OpenDetail1]
void sub_22C210(EEContext& ctx);  // [bcmPanel_SetDetailFrame]
// bpp_panel.c
void sub_22E780(EEContext& ctx);  // [bppPanel_SetIcon](member, kind 0..5)
void sub_22E850(EEContext& ctx);  // [bppPanel_IconPage](kind 1..5) -> page index
void sub_2337E0(EEContext& ctx);  // [bppPanel_Open](member)
void sub_233850(EEContext& ctx);  // [bppPanel_Close](member)
// sfl_ground.c / sfl_panel.c / the sub-menus
void sub_239170(EEContext& ctx);  // [sflGround_Register](work): the ground's quad index list
void sub_23D7A0(EEContext& ctx);  // [sflPanel_Register](work)
void sub_23D7F0(EEContext& ctx);  // [sflPanel_Start]
void sub_245E00(EEContext& ctx);  // [bpcMain_SetFlag80]
void sub_245E50(EEContext& ctx);  // [bpcMain_ClearFlag80]
void sub_249130(EEContext& ctx);  // [bpmMain_IsActive]
void sub_249600(EEContext& ctx);  // [bpeMain_IsActive]
void sub_249650(EEContext& ctx);  // [bpList_IsLocked](u16 id): !datGetFlag(id + 4800)
void sub_249680(EEContext& ctx);  // [object +1540 = 0]
void sub_24A180(EEContext& ctx);  // [draw an object's model when +1540 bit 0]
void sub_24A7F0(EEContext& ctx);  // [brpBirth_CreateWork]
void sub_24D110(EEContext& ctx);  // [sflCamera_Register](work)
void sub_24DA00(EEContext& ctx);  // [gcPose_Register](work)
// bp_tut.c / bp_tuta.c / bpd_main.c
void sub_2519D0(EEContext& ctx);  // [bpTut_IsActive]
void sub_251E10(EEContext& ctx);  // [bpTuta_Start]
void sub_251E80(EEContext& ctx);  // [bpTuta_IsActive]
void sub_253410(EEContext& ctx);  // [bpdMain_Start]
void sub_25CDB0(EEContext& ctx);  // [frFontChain_MoveLastTo](chain, x, y)
void sub_25CE30(EEContext& ctx);  // [frFontChain_CentreLastAt](chain, x, y)
// bp_rush.c
void sub_25D760(EEContext& ctx);  // [bpRush_SetFlag20]
void sub_25D7B0(EEContext& ctx);  // [bpRush_ClearFlag20]
void sub_25D800(EEContext& ctx);  // [bpRush_SetFlag40]
void sub_25D850(EEContext& ctx);  // [bpRush_ClearFlag40]
// the result pages
void sub_260900(EEContext& ctx);  // [entry width](obj, i)
void sub_260920(EEContext& ctx);  // [entry height](obj, i)
void sub_260940(EEContext& ctx);  // [entry's mapped value](obj, i)
void sub_260970(EEContext& ctx);  // [FullQuad_Register](work)
void sub_2626E0(EEContext& ctx);  // [brHero_Register](work)
void sub_264CA0(EEContext& ctx);  // [brHero_StatPage](stat 0..5) -> page record
void sub_264D80(EEContext& ctx);  // [brPersona_Register](work)
void sub_272330(EEContext& ctx);  // [brpSeq_Register](work)
void sub_2737A0(EEContext& ctx);  // [brpSeq_DrawBirth]
void sub_273980(EEContext& ctx);  // [brpSeq_EndStep]
void sub_273E10(EEContext& ctx);  // [brpSeq_RequestMessage]
void sub_274D40(EEContext& ctx);  // [brpSeq_HasEntry]
void sub_274D90(EEContext& ctx);  // [brpSeq_EntryId]
void sub_274E10(EEContext& ctx);  // [brpSeq_EntryValue]
void sub_274E90(EEContext& ctx);  // [brpSeq_EntriesAfter]
void sub_275A70(EEContext& ctx);  // [brLvpnl_Register](work)
void sub_275A90(EEContext& ctx);  // [brLvpnl_Show]
void sub_275BC0(EEContext& ctx);  // [brLvpnl_Update]
void sub_2760F0(EEContext& ctx);  // [brLvpnl_Layout]
void sub_276870(EEContext& ctx);  // [brLvpnl_SetFlag8]
void sub_276910(EEContext& ctx);  // [brpPersona_Register](work)
void sub_276CC0(EEContext& ctx);  // [brpPersona_Flag8]
void sub_276D10(EEContext& ctx);  // [brpParam_Register](work)
void sub_279450(EEContext& ctx);  // [brpParam_SetNumber](n)
void sub_2794C0(EEContext& ctx);  // [brpParam_SetValue](v)
void sub_279510(EEContext& ctx);  // [brpParam_SetMemberA](member, v)
void sub_279580(EEContext& ctx);  // [brpParam_SetMemberB](member, v)
void sub_2795F0(EEContext& ctx);  // [brpParam_SetMemberC](member, v)
void sub_2796B0(EEContext& ctx);  // [brpParam_StartA]
void sub_279700(EEContext& ctx);  // [brpParam_IsA]
void sub_279750(EEContext& ctx);  // [brpParam_StartB]
void sub_2797A0(EEContext& ctx);  // [brpParam_IsB]
void sub_2797F0(EEContext& ctx);  // [brpParam_SetFlag20]
void sub_279840(EEContext& ctx);  // [brpParam_ClearFlag20]
void sub_279890(EEContext& ctx);  // [brpParam_SetPair](a, b)
void sub_2798F0(EEContext& ctx);  // [brpParam_SetFlag40]
// bp_select.c / sfl_persona.c / the command calc
void sub_27B610(EEContext& ctx);  // [bpSelect_Update]
void sub_27B6C0(EEContext& ctx);  // [bpSelect_Layout]
void sub_27BB50(EEContext& ctx);  // [sflPersona_Register](work)
void sub_2C1CE0(EEContext& ctx);  // [btlCommand_CheckUsable](action): no bad status 0x80271, no flag 0x80, the encounter allows it
void sub_1F5810(EEContext& ctx);  // [sflRoot_IsIdle](task)
void sub_209C00(EEContext& ctx);  // [panel set 1 page 46, sub_21CCE0]

}  // namespace p3fes::game
