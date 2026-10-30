// Phase 5 slice band20: the open game code of 0x200000-0x23FFFF and the effect band at 0x324310-0x32E110 (158
// functions, 151,064 bytes). game/src/battle/band20_panel.cpp, band20_shuffle.cpp, band20_bcm.cpp, band20_result.cpp,
// game/src/fx/band20_fx.cpp; pair tests in tests/game/test_band20.cpp.
//
// What the bands are (callers, K_Assert file strings, docs/ANALYSIS/27_unmapped_bands.md section 3 / 6, the merged
// slices battle_cmd_menu, battle_panel, battle_ui3, shuffle, battle_result, fx_types, fx2):
//   0x200000-0x20FFFF  the battle UI's middle files: the tail of bcm_main.c (the command menu), baus_main.c (the
//                      auto-battle setting display over the units), sfl_data.c (Shuffle Time tables), gc_model.c (the
//                      card grid and positions), sfl_res.c (the Shuffle Time files), bpp_main.c (the party panel).
//   0x210000-0x21FFFF  the analysis panel's layout / draw (bsa band, 12.5 / 6.4 KB), sfl_psel.c (the persona select of
//                      Shuffle Time), gc_res.c (the card textures), bse_main.c, bp_res.c (the panel archive: sprite
//                      sets, heap blocks), bp_tex.c (sprite sets and rasters from image files), the start of bcm_panel.c.
//   0x220000-0x22FFFF  bcm_panel.c (the command panel: per-frame layout and draw, four sub-lists, their steps, the frame,
//                      the help line, the detail bar) and bpp_panel.c (each party member's panel: portrait, HP / SP
//                      digits and bars, the ailment icon and its animations).
//   0x230000-0x23FFFF  br_res.c / br_panel.c (the result screen's files and panel), bp_ifont.c (numbers in the sprite
//                      font), sfl_ground.c / sfl_panel.c (the Shuffle Time ground and panel), bi_main.c's work.
//   0x320000           the effect system's helpers next to the manager / layer tasks (fx_layers): the effect mesh and
//                      record destructors, the node tree's step / destroy / reset / position / rotation / scale / colour
//                      (each passes the change to the children through the class table 0x69BE20), the class instance's
//                      part setters and destructor, the 2D particle draw, VU0 maths helpers (camera space, screen projection, cubic, quaternion), the colour track, the
//                      particle-system scale slots.
//
// How chosen: a temporary first-call counter in every still-recompiled function of the bands (a scratch header patched
// into recomp/generated of the gate tree, never committed; the next emission removed it), on the battle route (116 of
// the 293 candidates run), the full Tartarus climb (205), fusion (58), dorm (19) and shop (27). Of the slice 85 run on
// the battle route and 144 on the climb (hottest: the colour track sub_32A120, 481,584 calls on the climb; the party
// panel's digits sub_22EB30, 48,952; the node position sub_325C10, 46,657), 146 on some route; the other 12 are callees
// the reached bodies need (the auto-battle layout, the persona select's close path, the ailment icon animation, the
// effect-record destructor). Leaf-first: every callee is replaced, emitted library code (K_Assert, libc, the RW and
// font layers, the effect maths of 0x357xxx) or in the slice.
//
// The module works. Each .c file keeps one work block behind a $gp slot (the table 0x7CE298 + 4k, as battle_ui3.h): a
// "register" function stores the block (most assert first that the slot is empty), every accessor asserts the slot is
// set (K_Assert(file, line): `jr $ra` in retail, so a bad state carries on and reads through 0). The resource modules
// (sfl_res.c, bp_res.c, br_res.c, gc_res.c) keep a "requested" and a "loaded" word: a request starts an H_Cdvd read and
// sets its requested bit; the module's update turns each loaded file into rasters (bp_tex.c sub_21EC40), sprite sets
// (sub_21C9F0) or RwMalloc copies, destroys the node and moves the bit to the loaded word; the release frees by the loaded
// bits.
//
// The 2D quads: 256-byte four-vertex strips filled by the battle_panel helpers (sub_21D3B0 page, sub_21D8E0 rectangle,
// sub_21D950 colour, sub_21E380 page + mode); a layout function places them every frame, a draw function sends each as two
// triangles through the RwIm2DRenderTriangle slot 0x96009C after RwRenderStateSet / RpSkyRenderStateSet.
//
// Co-op note (end-goal-engine-mmo): everything here is presentation: it reads the battle and party state (gBtl's acting
// unit, the party's HP / SP / ailments, the encounter) and writes only its own works, quads, font chains and effect
// nodes. A server never needs these bodies; a client runs them on the state the server sends. Two inputs matter for
// a faithful client: bpp_main.c follows the acting unit (sub_29AD20) to open the target panel, and the effect nodes are
// driven by the effect scripts the battle starts.
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace b20 {

// --- $gp slots (gp = 0x7D2CF0; the module works behind the table 0x7CE298 + 4k) ----------------------------------
inline constexpr s32 kGpBtlEnemyTbl = -18656; // 0X7CE410 gBtlEnemyTbl
inline constexpr s32 kGpBiMain = -18900;      // 0X7CE31C bi_main.c work (16 x 3,920-byte records)
inline constexpr s32 kGpSflPanel = -18904;    // 0X7CE318 sfl_panel.c work (the Shuffle Time panel)
inline constexpr s32 kGpSflGround = -18908;   // 0X7CE314 sfl_ground.c work (the Shuffle Time ground)
inline constexpr s32 kGpBrPanel = -18912;     // 0X7CE310 br_panel.c work (the result panel)
inline constexpr s32 kGpBrRes = -18916;       // 0X7CE30C br_res.c work (the result resources)
inline constexpr s32 kGpBcmPanel = -18920;    // 0X7CE308 bcm_panel.c work (the command panel)
inline constexpr s32 kGpBpRes = -18924;       // 0X7CE304 bp_res.c work (the panel resources)
inline constexpr s32 kGpBseMain = -18928;     // 0X7CE300 bse_main.c work
inline constexpr s32 kGpGcRes = -18932;       // 0X7CE2FC gc_res.c work (the card textures)
inline constexpr s32 kGpSflPsel = -18936;     // 0X7CE2F8 sfl_psel.c work (the Shuffle Time persona select)
inline constexpr s32 kGpBppMain = -18940;     // 0X7CE2F4 bpp_main.c work (the party panel)
inline constexpr s32 kGpSflRes = -18944;      // 0X7CE2F0 sfl_res.c work (the Shuffle Time resources)
inline constexpr s32 kGpBausMain = -18948;    // 0X7CE2EC baus_main.c work (the auto-battle setting display)

// --- bp_tex.c: a sprite set (sub_21C9F0; one RwMalloc block) ---------------------------------------------------------
inline constexpr s32 kSsPages = 4;            // u32: the page records (44 bytes each)
inline constexpr s32 kSsRasters = 8;          // u32: the rasters (one per image of the file)
inline constexpr s32 kSsRasterCount = 12;     // s32
inline constexpr s32 kSsPageCount = 16;       // s32

// --- a sprite set's 44-byte page record (sub_21CCA0(set, i)) ---------------------------------------------------------
inline constexpr s32 kSpSet = 0;              // u32: the set
inline constexpr s32 kSpRaster = 4;           // u32: the raster index (file +24)
inline constexpr s32 kSpFlags = 8;            // u32: (file +20)
inline constexpr s32 kSpW = 12;               // s32: width  = right - left
inline constexpr s32 kSpH = 16;               // s32: height = bottom - top
inline constexpr s32 kSpLeft = 20;            // s32: left (texels)
inline constexpr s32 kSpTop = 24;             // s32: top
inline constexpr s32 kSpRgba = 28;            // u8[4][4]: the four corner colours (file RGBA x 255 / 128)

// --- baus_main.c (kGpBausMain): the auto-battle setting display ------------------------------------------------------
inline constexpr s32 kBausFlags = 0;          // u32: bit 0 shown (sub_209540 draws)
inline constexpr s32 kBausEntries = 16;       // 1,056-byte entries, one per unit (kBausEntrySize)
inline constexpr s32 kBausCount = 10576;      // s32: entries in use

// --- sfl_res.c (kGpSflRes): the Shuffle Time files -------------------------------------------------------------------
inline constexpr s32 kSrRequested = 0;        // u32: bit 0 sfl_base.bin, 1 sfl_ground.bin, 2 sfl_effect.bin, 3 sfl_tutorial.bin, 4 i_change_per01.spr
inline constexpr s32 kSrLoaded = 4;           // u32: bit 0 ground, 1 base, 2 effect, 3 tutorial, 4 spr
inline constexpr s32 kSrGround = 8;           // u32[3]: the ground rasters (sub_20E800)
inline constexpr s32 kSrGround1 = 12;         // u32
inline constexpr s32 kSrGround2 = 16;         // u32
inline constexpr s32 kSrBase = 20;            // u32[5]: base archive files 0, 1, 2, 4, 12
inline constexpr s32 kSrBaseB = 40;           // u32[6]: base archive files 5..10 (sub_20E610)
inline constexpr s32 kSrEffect = 64;          // u32[6]: the effect archive's rasters
inline constexpr s32 kSrBaseBlock = 88;       // u32: base file 3, copied to the heap (sub_20E790)
inline constexpr s32 kSrTutorial = 92;        // u32[2]: the tutorial archive's two blocks
inline constexpr s32 kSrGroundNode = 100;     // u32: H_Cdvd node of sfl_ground.bin
inline constexpr s32 kSrBaseNode = 104;       // u32: node of sfl_base.bin
inline constexpr s32 kSrEffectNode = 108;     // u32: node of (AGS_)sfl_effect.bin
inline constexpr s32 kSrTutorialNode = 112;   // u32: node of sfl_tutorial.bin
inline constexpr s32 kSrSprNode = 116;        // u32: node of i_change_per01.spr
inline constexpr s32 kSrBaseBlocks = 120;     // u32[2]: base files 13 / 14 on the heap
inline constexpr s32 kSrSprSet = 128;         // u32: the sprite set of i_change_per01.spr

// --- bpp_main.c (kGpBppMain): the party panel ------------------------------------------------------------------------
inline constexpr s32 kBppFlags = 0;           // u32: bit 0 a target member shown, 1 the panels built, 2 the target panel open, 4 / 5 / 6 slide-out requests, 7 active
inline constexpr s32 kBppMembers = 16;        // 5,776-byte member records (BppMember)
inline constexpr s32 kBppCount = 23120;       // s32: member records in use
inline constexpr s32 kBppTargetUid = 23124;   // s32: uid (btlUnit DatUnit +168) of the member the target panel follows
inline constexpr s32 kBppTargetId = 23128;    // u16: its party id
inline constexpr s32 kBppSlide = 23132;       // s32: slide position 0..kBppSlideMax
inline constexpr s32 kBppSlideMax = 23136;    // s32: 2 * (members - 1) + 6

// --- a party panel member record (5,776 bytes from BppMain +16) ------------------------------------------------------
inline constexpr s32 kBmFlags = 0;            // u32
inline constexpr s32 kBmId = 4;               // s16: the party member id
inline constexpr s32 kBmHp = 16;              // u32: HP shown (-1 forces a refresh)
inline constexpr s32 kBmSp = 20;              // u32: SP shown
inline constexpr s32 kBmAilments = 24;        // u32: ailment bits shown (low 20 bits)
inline constexpr s32 kBmState = 28;           // u32: state shown (sub_16C920)
inline constexpr s32 kBmPanel = 32;           // the member's panel (BppPanel, bpp_panel.c)

// --- bpp_panel.c: a member's panel (BppMember +32) -------------------------------------------------------------------
inline constexpr s32 kBpnFlags = 0;           // u32: bit 0 open, 2 an ailment icon, 3 / 5 / 6 / 7 / 8 the open / close / flash animations, 9 tint
inline constexpr s32 kBpnId = 4;              // u16: the party member id
inline constexpr s32 kBpnPortrait = 16;       // quad: page 0 of the member's set
inline constexpr s32 kBpnFrame = 272;         // quads x4 (+272 / +528 / +784 / +1040): page 1 of the member's set
inline constexpr s32 kBpnX = 1296;            // f32: 100 at open, 476 after the layout (sub_20F3B0)
inline constexpr s32 kBpnY = 1300;            // f32: 100, then 4 + 100 * row
inline constexpr s32 kBpnBars = 1584;         // quads x2 (+1584 / +1840): page 10 of panel set 3
inline constexpr s32 kBpnIcon = 2096;         // s32: the ailment icon 0..10 (sub_22F1C0)
inline constexpr s32 kBpnHp = 2100;           // u32: HP of the digits
inline constexpr s32 kBpnMaxHp = 2104;        // u32
inline constexpr s32 kBpnSp = 2108;           // u32: SP of the digits
inline constexpr s32 kBpnMaxSp = 2112;        // u32
inline constexpr s32 kBpnOpenFrame = 2116;    // s32: open animation frame (0..16)
inline constexpr s32 kBpnFlashFrame = 2120;   // s32: flash animation frame (0..8)
inline constexpr s32 kBpnFadeFrame = 2124;    // s32: fade frame (0..20)
inline constexpr s32 kBpnScale = 2128;        // f32
inline constexpr s32 kBpnScale2 = 2132;       // f32
inline constexpr s32 kBpnHpDigits = 2144;     // quads x3: the HP digits (sub_22EA40)
inline constexpr s32 kBpnSpDigits = 2912;     // quads x3: the SP digits
inline constexpr s32 kBpnHpBar = 3680;        // Im2D quad: the HP bar (sub_22ECB0)
inline constexpr s32 kBpnSpBar = 3936;        // Im2D quad: the SP bar

// --- sfl_psel.c (kGpSflPsel) -----------------------------------------------------------------------------------------
inline constexpr s32 kPsFlags = 0;            // u32: bit 0 open, bit 3 the caption chain
inline constexpr s32 kPsCount = 12;           // s32: entries (2,320 bytes each, font chain at entry +2640)
inline constexpr s32 kPsCaption = 21200;      // u32: the caption's font chain

// --- gc_res.c (kGpGcRes): the card textures (battle_ui3.h names) -----------------------------------------------------
inline constexpr s32 kGrState = 0;            // u32: bit 2 the back texture requested (refcount +72)
inline constexpr s32 kGrResA = 4;             // u32: raster A (loaded bit 0)
inline constexpr s32 kGrResB = 8;             // u32: raster B, card/misc/w_c00.tmx (loaded bit 1)
inline constexpr s32 kGrLoaded = 12;          // u32: loaded mask
inline constexpr s32 kGrTableC = 32;          // u32[7]: (loaded bit 2)
inline constexpr s32 kGrTableD = 60;          // u32[2]: (loaded bit 3)
inline constexpr s32 kGrBackRefs = 72;        // s32: references to raster B
inline constexpr s32 kGrPairs = 76;           // 16 x 20-byte pair records {flags, a, b, raster, refs}
inline constexpr s32 kGrIds = 396;            // 16 x 16-byte id records {flags, u16 id, raster, refs}
inline constexpr s32 kGrSlots = 652;          // 32 x 292-byte load slots {flags, kind, node, ... +272 target kind, +276 index}

// --- bse_main.c (kGpBseMain) -----------------------------------------------------------------------------------------
inline constexpr s32 kBseFlags = 0;           // u32

// --- bp_res.c (kGpBpRes): the panel resources ------------------------------------------------------------------------
inline constexpr s32 kBrFlags = 0;            // u32: bit 0 the panel archive requested
inline constexpr s32 kBrLoaded = 4;           // u32: bit 0 the archive's sets, 0x10 / 0x20 / 0x40 the sets +56 / +60 / +64, 0x80 / 0x100 the extra blocks
inline constexpr s32 kBrNode = 8;             // u32: H_Cdvd node of (AGS_ / AGS2_)bp_all.bin
inline constexpr s32 kBrSets = 16;            // u32[7]: the panel sprite sets (sub_21C3F0)
inline constexpr s32 kBrIdSetRefs = 44;       // u32[3]
inline constexpr s32 kBrIdSets = 56;          // u32[3]: the sets of the ids in +72
inline constexpr s32 kBrIdCount = 68;         // s32
inline constexpr s32 kBrIds = 72;             // u32[3]: the party's persona-select ids (sub_16DD60)
inline constexpr s32 kBrBlocks = 84;          // u32[6]: archive files copied to the heap (+84 / +88 / +92 / +96 / +100 ...)

// --- bcm_panel.c (kGpBcmPanel): the command panel (battle_ui3.h names where they agree) ------------------------------
inline constexpr s32 kBcmFlags = 0;           // u32: bit 0 shown, 1 a sub-list, 3 a menu state, 4 the persona command hidden
inline constexpr s32 kBcmList = 4;            // u32: the sub-list kind (1, 2, 4, 8)
inline constexpr s32 kBcmQuadBase = 16;       // quad: page 16 (the panel)
inline constexpr s32 kBcmQuadA = 272;         // quad: page 27
inline constexpr s32 kBcmQuadB = 528;         // quad: page 28
inline constexpr s32 kBcmQuadC = 784;         // quad: page 14
inline constexpr s32 kBcmCmdFrames = 1040;    // quads x7: the commands' frames (page 17 usable / 65 not)
inline constexpr s32 kBcmCmdNames = 2832;     // quads x7: the commands' names (pages 20..26)
inline constexpr s32 kBcmCmdState = 4624;     // u32[7]: bit 0 the command is usable
inline constexpr s32 kBcmQuadCur = 4656;      // quad: the current command's page
inline constexpr s32 kBcmQuadPrev = 4912;     // quad: the previous command's page
inline constexpr s32 kBcmQuadD = 5168;        // quad: page 34
inline constexpr s32 kBcmScrollQuad = 14128;  // quad: the sub-list's scroll mark (page 29)
inline constexpr s32 kBcmState = 17968;       // u32: 1 / 2 / 8 cursor states, 3 a sub-list, 4 / 5 the menu states
inline constexpr s32 kBcmCur = 17972;         // u32: the current command
inline constexpr s32 kBcmPrev = 17976;        // u32: the previous one (-1)
inline constexpr s32 kBcmSub = 17980;         // u32: the sub-list state (1..4)
inline constexpr s32 kBcmSubPrev = 17984;     // u32
inline constexpr s32 kBcmSubStep = 17988;     // u32
inline constexpr s32 kBcmSubSel = 17992;      // s32
inline constexpr s32 kBcmTimer = 17996;       // u32: frames since the cursor moved
inline constexpr s32 kBcmSubTimer = 18000;    // u32
inline constexpr s32 kBcmMenuTimer = 18008;   // u32
inline constexpr s32 kBcmRowMarks = 24720;    // quads (272-byte stride): the rows' marks (page 41)
inline constexpr s32 kBcmRowTotal = 26064;    // s32: rows of the list
inline constexpr s32 kBcmRowTop = 26072;      // s32: the first row shown
inline constexpr s32 kBcmRowShown = 26076;    // s32: rows shown
inline constexpr s32 kBcmTabs = 26096;        // quads x3: the help tabs (pages 62..64)
inline constexpr s32 kBcmHelpChain = 26864;   // u32: the help line's font chain
inline constexpr s32 kBcmCursorPage = 26868;  // u32: the page (+32) of the cursor quad
inline constexpr s32 kBcmCursorOn = 26872;    // u32
inline constexpr s32 kBcmCursorQuad = 26880;  // quad
inline constexpr s32 kBcmDetailBar = 27136;   // quads x2: the detail bar (page 66)
inline constexpr s32 kBcmFade = 29204;        // f32: the panel's alpha 0..1

// --- br_res.c (kGpBrRes): the result resources -----------------------------------------------------------------------
inline constexpr s32 kBrrRequested = 0;       // u32: bit 2 br_lvh.bin
inline constexpr s32 kBrrLoaded = 4;          // u32: bit 0 / 1 the sets +28 / +32, 2 the blocks +36, 0x10 br_lvh, 0x20 the block +44, 0x40 the sets +48
inline constexpr s32 kBrrLvhNode = 20;        // u32: H_Cdvd node of (AGS_ / AGS2_)br_lvh.bin
inline constexpr s32 kBrrSetA = 28;           // u32: sprite set
inline constexpr s32 kBrrSetB = 32;           // u32: sprite set
inline constexpr s32 kBrrBlocks = 36;         // u32[2]: heap blocks
inline constexpr s32 kBrrBlock = 44;          // u32: heap block
inline constexpr s32 kBrrSets = 48;           // u32[2]: sprite sets
inline constexpr s32 kBrrLvhSets = 56;        // u32[4]: br_lvh's sprite sets
inline constexpr s32 kBrrLvhRasters = 72;     // u32[2]: br_lvh's rasters

// --- br_panel.c (kGpBrPanel) -----------------------------------------------------------------------------------------
inline constexpr s32 kBrpFlags = 0;           // u32

// --- sfl_ground.c (kGpSflGround) -------------------------------------------------------------------------------------
inline constexpr s32 kSgFlags = 0;            // u32: bit 0 shown, 2 the far quad set (sub_23D130), 0x20
inline constexpr s32 kSgFrame = 4;            // s32
inline constexpr s32 kSgMode = 12;            // s32
inline constexpr s32 kSgFarQuad = 17936;      // quad: ground raster 3
inline constexpr s32 kSgPose = 34688;         // the pose block of sub_2496E0

// --- sfl_panel.c (kGpSflPanel) ---------------------------------------------------------------------------------------
inline constexpr s32 kSpnFlags = 0;           // u32: bit 0 open, 1 animating, 3 held
inline constexpr s32 kSpnMode = 4;            // s32: 0 the 50-frame entry, 1 / 2 the 30-frame ones
inline constexpr s32 kSpnFrame = 8;           // s32: frames into the animation
inline constexpr s32 kSpnCount = 12;          // s32: the count shown (1..6)
inline constexpr s32 kSpnNumberQuad = 16;     // quad: base raster count - 1
inline constexpr s32 kSpnTitleQuad = 272;     // quad: ground raster 0 (174 x 32)

// --- bi_main.c (kGpBiMain) -------------------------------------------------------------------------------------------
inline constexpr s32 kBiRecords = 0;          // 16 x 3,920-byte records (flags at +0)

// --- the effect node (the tree sub_324BD0 builds; fx_types.h / fx_epl.h) ---------------------------------------------
inline constexpr s32 kEnMatrix = 0;           // vec4 x4: the world matrix rows (VU0)
inline constexpr s32 kEnRow1 = 16;            // vec4
inline constexpr s32 kEnRow2 = 32;            // vec4 (scaled by sub_325E40)
inline constexpr s32 kEnPos = 64;             // vec4: position
inline constexpr s32 kEnRot = 80;             // vec4: rotation (Euler)
inline constexpr s32 kEnScale = 96;           // f32: scale
inline constexpr s32 kEnColour = 100;         // u32: RGBA
inline constexpr s32 kEnMode = 104;           // u32: bit 2 / 3 / 4 / 5 / 6 / 7 / 8 billboard and inherit modes; bit 31 detached
inline constexpr s32 kEnScaleBase = 116;      // f32
inline constexpr s32 kEnStart = 128;          // s32: frame the child starts
inline constexpr s32 kEnFrame = 132;          // s32: frames run (child: bit 0 scaled, 1 done)
inline constexpr s32 kEnChild = 140;          // u32: first child
inline constexpr s32 kEnEffect = 144;         // u32: the child's effect record
inline constexpr s32 kEnChildFlags = 152;     // u32: bit 0 shared (not freed)
inline constexpr s32 kEnSibling = 172;        // u32: next sibling

// --- an effect record (the class instance and its two blocks) --------------------------------------------------------
inline constexpr s32 kErClass = 4;            // u16: the class (row 0x69BE20 + 52 * class)
inline constexpr s32 kErInstance = 8;         // u32: the class instance
inline constexpr s32 kErBlockA = 16;          // u32
inline constexpr s32 kErBlockAEnd = 20;       // u32
inline constexpr s32 kErBlockAMem = 24;       // u32: heap block (freed)
inline constexpr s32 kErBlockB = 32;          // u32
inline constexpr s32 kErBlockBEnd = 36;       // u32
inline constexpr s32 kErBlockBMem = 40;       // u32: heap block (freed)

// --- an effect mesh object -------------------------------------------------------------------------------------------
inline constexpr s32 kFmAtomic = 12;          // u32: RpAtomic
inline constexpr s32 kFmFrame = 16;           // u32: RwFrame
inline constexpr s32 kFmMaterialCount = 28;   // s16
inline constexpr s32 kFmMaterials = 40;       // u32: the materials

// --- a class instance with records, trees, models, particle system and mesh (sub_326740) -----------------------------
inline constexpr s32 kFiCount = 0;            // s32: child count when there is no particle system
inline constexpr s32 kFiOwns = 14;            // u8: bit 0 the particle system +76 is owned
inline constexpr s32 kFiNodes = 52;           // u32: the effect records
inline constexpr s32 kFiNodesMem = 56;        // u32: their heap block
inline constexpr s32 kFiTrees = 60;           // u32: the node trees
inline constexpr s32 kFiTreesMem = 64;        // u32: their heap block
inline constexpr s32 kFiModelA = 68;          // u32: (sub_322530 / sub_322660)
inline constexpr s32 kFiModelB = 72;          // u32: (sub_322DC0 / sub_322F20)
inline constexpr s32 kFiPsys = 76;            // u32: the particle system (sub_332070); +8 its count
inline constexpr s32 kFiMesh = 80;            // u32: the mesh (sub_3234F0 / sub_3237C0)
inline constexpr s32 kFiTexU = 84;            // f32: half the texture width / 16
inline constexpr s32 kFiTexV = 88;            // f32: half the texture height / 16
inline constexpr s32 kBausEntrySize = 1056;   // baus_main.c entry stride
inline constexpr s32 kBppMemberSize = 5776;   // bpp_main.c member record stride
inline constexpr s32 kQuadSize = 256;         // a 2D quad (four 64-byte vertices; battle_panel.h)
inline constexpr s32 kBiRecordSize = 3920;    // bi_main.c record stride
inline constexpr s32 kGcSlotSize = 292;       // gc_res.c load slot stride

}  // namespace b20

// One line per function: [proposed name] and role (the .cpp files have the detail).
// the battle panels (src/battle/band20_panel.cpp)
void sub_208AD0(EEContext& ctx);  // [bausMain_Register](work) baus_main.c:
void sub_208B20(EEContext& ctx);  // [bausMain_Unregister] clears the baus_main.c slot (sub_1FDC00, the panel teardown).
void sub_208F60(EEContext& ctx);  // [bausMain_Layout] lays out every unit's auto-battle entry:
void sub_209540(EEContext& ctx);  // [bausMain_Draw] the draw task's hook:
void sub_209A00(EEContext& ctx);  // [bausMain_SetDigits](quads, n, value, xy*, scale $f12)
void sub_20ED50(EEContext& ctx);  // [bppMain_Register](work) bpp_main.c:
void sub_20ED70(EEContext& ctx);  // [bppMain_Activate] sets flag bit 7 (the panel runs).
void sub_20EDC0(EEContext& ctx);  // [bppMain_Unregister] closes the member panels (sub_20F680) and clears the slot.
void sub_20EDF0(EEContext& ctx);  // [bppMain_Update]
void sub_20F260(EEContext& ctx);  // [bppMain_Draw] the draw task's hook:
void sub_20F3B0(EEContext& ctx);  // [bppMain_Build]
void sub_20F680(EEContext& ctx);  // [bppMain_Close] closes every member panel (sub_22C850), count 0, clears flag bit 1.
void sub_20F9A0(EEContext& ctx);  // [bppMain_RefreshMember](u16 id)
void sub_20FDD0(EEContext& ctx);  // [bppMain_ClearFlag40] clears flag bit 6 (a slide-out request).
void sub_20FE20(EEContext& ctx);  // [panel work +4 = 0] stores 0 at a0 +4 (bpRoot_CreateBattlePanelTasks).
void sub_210D90(EEContext& ctx);  // [bsaPanel_Layout](panel)
void sub_213E80(EEContext& ctx);  // [bsaPanel_Draw](panel) draws the analysis panel the layout above built:
void sub_215770(EEContext& ctx);  // [bsaPanel_Close](panel) destroys the panel's font chains (+16, and +20..
void sub_21B650(EEContext& ctx);  // [bseMain_Register](work) bse_main.c:
void sub_21B660(EEContext& ctx);  // [bseMain_Unregister] clears the bse_main.c slot.
void sub_21B920(EEContext& ctx);  // [bpRes_Register](work) bp_res.c:
void sub_21B940(EEContext& ctx);  // [bpRes_Request] requests the panel archive:
void sub_21BCB0(EEContext& ctx);  // [bpRes_Update] bp_res.c's loader:
void sub_21C5D0(EEContext& ctx);  // [bpRes_GetBlock88] the heap block +88 (asserts loaded bit 0, line 433).
void sub_21C640(EEContext& ctx);  // [bpRes_GetBlock84] the heap block +84 (line 441).
void sub_21C6B0(EEContext& ctx);  // [bpRes_GetBlock92] the heap block +92 (line 449).
void sub_21C790(EEContext& ctx);  // [bpRes_Forward](a) asserts the bp_res.c slot and returns sub_267370(a).
void sub_21C9F0(EEContext& ctx);  // [bpTex_CreateSpriteSet](file) -> set
void sub_21CC20(EEContext& ctx);  // [bpTex_DestroySpriteSet](set)
void sub_21EC40(EEContext& ctx);  // [bpTex_CreateRaster](image) -> RwRaster bp_tex.c:
void sub_22C720(EEContext& ctx);  // [bppPanel_Init](panel, u16 id) bpp_panel.c:
void sub_22C850(EEContext& ctx);  // [bppPanel_Close](panel) clears the panel's flags (K_Assert 435 if it is not open).
void sub_22C8A0(EEContext& ctx);  // [bppPanel_Layout](panel) one member panel's per-frame layout:
void sub_22DF10(EEContext& ctx);  // [bppPanel_Draw](panel) draws the member panel:
void sub_22E900(EEContext& ctx);  // [bppPanel_SetHp](panel, hp)
void sub_22E9A0(EEContext& ctx);  // [bppPanel_SetSp](panel, sp)
void sub_22EA40(EEContext& ctx);  // [bppPanel_SetDigitPages](quads, n)
void sub_22EB30(EEContext& ctx);  // [bppPanel_PlaceDigits](quads, n, xy*)
void sub_22ECB0(EEContext& ctx);  // [bppPanel_SetBar](im2d quad, page) fills a 4-vertex Im2D quad from a page:
void sub_22F1C0(EEContext& ctx);  // [bppPanel_SetAilment](panel, bits)
void sub_22F3B0(EEContext& ctx);  // [bppPanel_SetIconQuads](panel)
void sub_22FA80(EEContext& ctx);  // [bppPanel_LayoutAilment](panel) the ailment icons' animations (13 KB:
void sub_232EA0(EEContext& ctx);  // [bppPanel_DrawAilment](panel)
void sub_23F480(EEContext& ctx);  // [biMain_Register](work) bi_main.c:
void sub_23F500(EEContext& ctx);  // [biMain_Unregister] clears the bi_main.c slot (K_Assert 138 if it is empty).
// Shuffle Time (src/battle/band20_shuffle.cpp)
void sub_209C80(EEContext& ctx);  // [sflData_GetTableH] sfl_data.c:
void sub_209D40(EEContext& ctx);  // [sflData_CardSide](s16 *v) maps a card's side word:
void sub_209E80(EEContext& ctx);  // [sflData_GetTableI] returns the table 0x68DF60.
void sub_209E90(EEContext& ctx);  // [sflData_GetTableJ] returns the table 0x68E020.
void sub_20C660(EEContext& ctx);  // [gcModel_CardX](i, n) -> $f0 gc_model.c:
void sub_20C8D0(EEContext& ctx);  // [gcModel_Initialize] "gcm initialize":
void sub_20CC80(EEContext& ctx);  // [gcModel_SetColour](model, rgba*)
void sub_20D630(EEContext& ctx);  // [gcModel_SetScale](model, xyz*) copies three floats to model +44 / +48 / +52.
void sub_20D820(EEContext& ctx);  // [sflRes_Update] sfl_res.c's per-frame loader.
void sub_20E030(EEContext& ctx);  // [sflRes_Release] frees everything sfl_res.c loaded (by the loaded bits:
void sub_20E200(EEContext& ctx);  // [sflRes_RequestBase]
void sub_20E380(EEContext& ctx);  // [sflRes_IsGroundPending] returns requested & 2 (sfl_ground.bin not in yet).
void sub_20E3D0(EEContext& ctx);  // [sflRes_RequestEffect]
void sub_20E610(EEContext& ctx);  // [sflRes_GetBaseB](i)
void sub_20E790(EEContext& ctx);  // [sflRes_GetBaseBlock] the heap copy of base file 3 (+88).
void sub_20E800(EEContext& ctx);  // [sflRes_SetGround](file) takes sfl_ground.bin (a 3-entry table:
void sub_20EA80(EEContext& ctx);  // [sflRes_FreeTutorial]
void sub_20EB40(EEContext& ctx);  // [sflRes_RequestSpr]
void sub_20ECC0(EEContext& ctx);  // [sflRes_FreeSpr] destroys the i_change_per01.spr sprite set (+128);
void sub_215AA0(EEContext& ctx);  // [sflPsel_Unregister] sfl_psel.c:
void sub_216800(EEContext& ctx);  // [sflPsel_Close] closes the persona select:
void sub_2172C0(EEContext& ctx);  // [sflPsel_DestroyChains]
void sub_219B00(EEContext& ctx);  // [sflPsel_DestroyCaption] destroys the caption chain (+21200);
void sub_219D90(EEContext& ctx);  // [gcRes_Update] gc_res.c's loader:
void sub_21A120(EEContext& ctx);  // [gcRes_IsLoading] 1 while any load slot is busy (bit 0), else 0.
void sub_21A1B0(EEContext& ctx);  // [gcRes_Release]
void sub_21A840(EEContext& ctx);  // [gcRes_RequestBack]
void sub_21B4A0(EEContext& ctx);  // [gcRes_SetCards](file)
void sub_23B990(EEContext& ctx);  // [sflGround_Draw] sfl_ground.c:
void sub_23C350(EEContext& ctx);  // [sflGround_IsShown] returns flag bit 0.
void sub_23C520(EEContext& ctx);  // [sflGround_SetCardQuads](quads, pos*, dir*, scale*)
void sub_23C850(EEContext& ctx);  // [sflGround_SetCardColour](quads, rgba*) the colour of both quads.
void sub_23D0E0(EEContext& ctx);  // [sflGround_Flag20] returns flag bit 5.
void sub_23D130(EEContext& ctx);  // [sflGround_ShowFar]
void sub_23D1F0(EEContext& ctx);  // [sflGround_Flag4] returns flag bit 2.
void sub_23D7B0(EEContext& ctx);  // [sflPanel_Unregister] sfl_panel.c:
void sub_23D870(EEContext& ctx);  // [sflPanel_Close] clears bit 0 (K_Assert 163 if it is not open).
void sub_23D8F0(EEContext& ctx);  // [sflPanel_Update] advances the panel animation (mode 0:
void sub_23DAC0(EEContext& ctx);  // [sflPanel_Layout] lays out the Shuffle Time panel:
void sub_23E970(EEContext& ctx);  // [sflPanel_Draw] draws the Shuffle Time panel (sflRoot_UpdateShuffleRootDraw1Task).
void sub_23EE50(EEContext& ctx);  // [sflPanel_Start]
void sub_23F390(EEContext& ctx);  // [sflPanel_IsAnimating] returns flag bit 1.
void sub_23F3E0(EEContext& ctx);  // [sflPanel_Hold] sets flag bit 3.
void sub_23F430(EEContext& ctx);  // [sflPanel_Release] clears flag bit 3.
// the command panel (src/battle/band20_bcm.cpp)
void sub_21F0C0(EEContext& ctx);  // [bcmPanel_Register](work) bcm_panel.c:
void sub_21F140(EEContext& ctx);  // [bcmPanel_Unregister] clears the bcm_panel.c slot.
void sub_21F150(EEContext& ctx);  // [bcmPanel_Open](cmd) sets the panel up:
void sub_21F3C0(EEContext& ctx);  // [bcmPanel_Close] clears flag bit 0.
void sub_21F410(EEContext& ctx);  // [bcmPanel_Layout] the command panel's per-frame layout:
void sub_221B60(EEContext& ctx);  // [bcmPanel_Draw] draws what sub_21F410 laid out:
void sub_223290(EEContext& ctx);  // [bcmPanel_LayoutList3]
void sub_224150(EEContext& ctx);  // [bcmPanel_DrawList3] draws sub-list 3 (quads and font chains).
void sub_224940(EEContext& ctx);  // [bcmPanel_LayoutList4] lays out sub-list 4:
void sub_225040(EEContext& ctx);  // [bcmPanel_DrawList4] draws sub-list 4.
void sub_2255F0(EEContext& ctx);  // [bcmPanel_EnterMenu5] state 5:
void sub_225670(EEContext& ctx);  // [bcmPanel_LayoutScroll]
void sub_2257F0(EEContext& ctx);  // [bcmPanel_LayoutStep]
void sub_226040(EEContext& ctx);  // [bcmPanel_DrawStep] draws the step page.
void sub_2265D0(EEContext& ctx);  // [bcmPanel_LayoutFrame]
void sub_227800(EEContext& ctx);  // [bcmPanel_DrawFrame] draws the panel frame (jump table on the frame mode).
void sub_227F30(EEContext& ctx);  // [bcmPanel_LayoutGrid]
void sub_2289B0(EEContext& ctx);  // [bcmPanel_DrawGrid] draws the six-entry grid.
void sub_228E40(EEContext& ctx);  // [bcmPanel_LayoutList2] lays out sub-list 2:
void sub_229B40(EEContext& ctx);  // [bcmPanel_DrawList2] draws sub-list 2.
void sub_22A2B0(EEContext& ctx);  // [bcmPanel_LayoutList1] lays out sub-list 1 like sub-list 2 (K_Assert 4020).
void sub_22AE80(EEContext& ctx);  // [bcmPanel_DrawList1] draws sub-list 1.
void sub_22B530(EEContext& ctx);  // [bcmPanel_InMenu] returns flag bit 3.
void sub_22B630(EEContext& ctx);  // [bcmPanel_LayoutHelp] the three help tabs (pages 62..64;
void sub_22BCF0(EEContext& ctx);  // [bcmPanel_DrawHelp]
void sub_22C0A0(EEContext& ctx);  // [bcmPanel_ResetStep] sub-step 0.
void sub_22C2D0(EEContext& ctx);  // [bcmPanel_LayoutDetail]
// the result screen (src/battle/band20_result.cpp)
void sub_233C00(EEContext& ctx);  // [brRes_RequestLvh] br_res.c:
void sub_234070(EEContext& ctx);  // [brRes_Update] br_res.c's loader:
void sub_2350F0(EEContext& ctx);  // [brPanel_Draw] draws the result panel (sub_1F08C0 / sub_1F0900):
void sub_235F30(EEContext& ctx);  // [brPanel_SetDigitPages](quads, n, ...)
void sub_235FF0(EEContext& ctx);  // [brPanel_PlaceDigits](quads, n, value, style, xy*)
void sub_236390(EEContext& ctx);  // [brPanel_Layout] the result panel's layout:
void sub_238A50(EEContext& ctx);  // [bpIfont_PlaceLeft](quads, n, value, font, xy*) bp_ifont.c:
void sub_238BF0(EEContext& ctx);  // [bpIfont_PlaceRight](quads, n, value, font, xy*)
void sub_238DC0(EEContext& ctx);  // [bpIfont_PlaceCentred](quads, n, value, font, xy*)
// the effect system (src/fx/band20_fx.cpp)
void sub_324310(EEContext& ctx);  // [fxMesh_Destroy](mesh) destroys an effect mesh:
void sub_3243F0(EEContext& ctx);  // [fxMesh_SetTexture](mesh, texture) sets the texture on each material.
void sub_324510(EEContext& ctx);  // [fxMesh_SetTextureByName](mesh, name)
void sub_324740(EEContext& ctx);  // [fxEffect_Destroy](rec) destroys an effect record:
void sub_3247D0(EEContext& ctx);  // [fxEffect_FreeBlockA](rec)
void sub_324820(EEContext& ctx);  // [fxEffect_FreeBlockB](rec)
void sub_325500(EEContext& ctx);  // [fxNode_Step](node, out) one frame of a node tree (frames +132 > 0):
void sub_3257E0(EEContext& ctx);  // [fxNode_Destroy](node) destroys a node tree:
void sub_325B80(EEContext& ctx);  // [fxNode_Reset](node) class slot 7 on every child's instance;
void sub_325C10(EEContext& ctx);  // [fxNode_SetPosition](node, pos*)
void sub_325D60(EEContext& ctx);  // [fxNode_SetRotation](node, rot*)
void sub_325E40(EEContext& ctx);  // [fxNode_SetScale](node, scale $f12) stores the scale;
void sub_326030(EEContext& ctx);  // [fxNode_SetColour](node, rgba)
void sub_326280(EEContext& ctx);  // [fxNode_BillboardRotation](node, out) for mode bits 3 / 4:
void sub_3263B0(EEContext& ctx);  // [fxNode_FaceCamera](node, out) for mode bits 5 / 6:
void sub_326740(EEContext& ctx);  // [fxInst_Destroy](inst) destroys a class instance:
void sub_326C70(EEContext& ctx);  // [fxInst_SetPsys](inst, type, arg)
void sub_326CF0(EEContext& ctx);  // [fxInst_SetMesh](inst, n, kind) replaces the mesh:
void sub_326DB0(EEContext& ctx);  // [fxInst_SetTextureById](inst, id) the texture by id (sub_3210A0):
void sub_326E50(EEContext& ctx);  // [fxInst_SetTextureByName](inst, name)
void sub_326F00(EEContext& ctx);  // [fxInst_SetModelA](inst, arg) replaces model A (sub_322660 / sub_322530).
void sub_3271C0(EEContext& ctx);  // [fxInst_SetModelB](inst, arg) replaces model B (sub_322F20 / sub_322DC0).
void sub_3282E0(EEContext& ctx);  // [fxPsys_Draw2D](inst)
void sub_329800(EEContext& ctx);  // [fxCameraSpace](pos*, out)
void sub_3299B0(EEContext& ctx);  // [fxToScreen](pos*) -> vf10
void sub_329D60(EEContext& ctx);  // [fxCubic](p[4], t $f12, out) a cubic curve point from four control vectors (VU0;
void sub_329ED0(EEContext& ctx);  // [fxQuatFromMatrix](m) the quaternion of a rotation matrix (the trace method;
void sub_32A120(EEContext& ctx);  // [fxColourTrack](track, alpha*, t, length) -> RGBA samples a colour track:
void sub_32B990(EEContext& ctx);  // [fxPsysScaleA](psys, s $f12) a particle-system type's scale slot:
void sub_32C2B0(EEContext& ctx);  // [fxPsysScaleB](psys, s $f12) the same for another type's fields.
void sub_32CD70(EEContext& ctx);  // [fxPsysScaleC](psys, s $f12) the same for another type's fields.
void sub_32D7C0(EEContext& ctx);  // [fxPsysScaleD](psys, s $f12) the same for another type's fields.
void sub_32E110(EEContext& ctx);  // [fxPsysScaleE](psys, s $f12) the same for another type's fields.

}  // namespace p3fes::game
