// The camp menu's screens, second pass (slice ui6), hand-decompiled from SLUS_216.21 (docs/ANALYSIS/20_menu_ui.md
// section 2): the big draw and update bodies of the camp band 0x119AA0-0x16C470 that ui5 left (it took everything up to
// 1,200 bytes) and their in-band callers -- the main list's draws; the Status screen (its page, persona page, the HP /
// SP / social-stat / persona tables); the equipment screen; the persona screen; the social-link screen; the item screen
// (items, equipment and material pages, the target and persona choices); the system menu (config, help, fusion spells,
// requests, calendar, quit) and the title screen's config; the skill screen; the party-status screens a script opens;
// the equipment trade / drop screens. Phase 5 slice `ui6`; game/src/ui/ui6_{status,equip,comu,item,system,skill,
// party}.cpp, pair tests tests/game/test_ui6.cpp. ui3 has the camp root and the screens' draw dispatchers, ui5 the
// leaves, task creators / destroys, the flash-control task and the tween records.
//
// The bodies are p3fes_handgen's (hg_cpu.h): register for register, frame, spills, $ra links, cycle charges and check
// points as the recompiled code. This pass adds the role of every function (proposed names in brackets: ours, from the
// task / file strings, the callers and the instructions; not in any delta), the role of the jump-table cases,
// the record offsets below (each constant equals the literal it replaces: the script that applied them checks it), a
// note on the callees, the value of the float immediates, the meaning of the pad bits tested.
//
// How the screens work (every update below; ui5.h has the records it shares):
// * A screen is a kwlnTask whose work block (task +0x3C) starts with its state word (the equipment screen: +4); the
//   update is one jump table over the state and returns 0 (keep running) or -1 (finished, the parent destroys it).
// * Its panels are tween records (68 bytes, ui5::tw; arrays from sub_18B6D0): a layout function starts every record of
//   a page (sub_18BC10: from / to xy, mode 2, curve 1 in / 2 out, first / last frame), the update steps them each frame
//   (sub_18B700: 1 while the record is active) and draws each active record through the page's element draw (`element`
//   = the record's index: one panel, frame or list), and a page counts as arrived when every record's frame +24 equals
//   its last frame +32. A screen change waits for the flash-control task's transition (sub_11E380(flash, n) returns 1
//   once the n-th transition reached its target).
// * Input (20_menu_ui.md 4.1): 0x7E094E (gPadFlags) / 0x7E0958 carry a button on the frame it is pressed, 0x7E0952 /
//   0x7E095A also on the auto-repeat frames: the lists move on the second pair and wrap around (first <-> last) only on
//   the first. Bits as the screens use them: 0x40 confirm, 0x20 cancel, 0x80 a third action (the persona screen's
//   release, the item screen's equipment page), 0x1000 cursor - 1, 0x4000 cursor + 1, 0x2000 / 0x8000 the next /
//   previous page (R1 / L1 in the item screen; an option off / on in the config page), 0x8 / 0x4 the calendar's month.
//   The equipment screen's slot menu reads confirm / cancel on the repeat word and does not wrap; the config page's
//   last row (7) is "OK".
// * Sounds: sub_10A4E0(0, 0, 0, n): 0 cursor, 1 confirm, 2 cancel, 7 equip, 8 refused (as the screens use them).
#pragma once

#include "p3fes/ee_context.h"
#include "p3fes/game/ui5.h"

namespace p3fes::game {

namespace ui6 {
namespace task = ui5::task;  // kWork: the work block of a kwlnTask (+0x3C)
namespace rw = ui5::rw;      // the RW memory slots (0x960000 + kMallocSlot / kFreeSlot / kCallocSlot)
namespace tw {  // tween record (68 bytes; ui5::tw has the fields its start function writes)
using namespace ui5::tw;
inline constexpr s32 kX = 56;      // f32: the current x (the element draws read their position here)
inline constexpr s32 kY = 60;      // f32: the current y
inline constexpr s32 kAlpha = 64;  // u32: the current alpha (0..255; the draws take the low byte)
inline constexpr s32 kSize = 68;
}  // namespace tw
namespace g {  // $gp-relative words ($gp = 0x7D2CF0; the address in the comment); ui5::g has the camp ones
using namespace ui5::g;
inline constexpr s32 kComuCardScroll = -19844; // 0x7CDF6C: the card view's scroll counter (-200 on open, 0..448)
inline constexpr s32 kConfigFlag = -19832;     // 0x7CDF78: set to 1 by "H_ConfigMenuDraw" (sub_15B430)
inline constexpr s32 kItemSelected = -19804;   // 0x7CDF94: the item screen's selected item id (u16)
inline constexpr s32 kSkillTable = -18436;     // 0x7CE4EC: the skill name table (19-byte rows)
inline constexpr s32 kFloat7CADB4 = -32572;    // 0x7CADB4: a float constant of the .sdata (read by the request list)
inline constexpr s32 kWord7CB574 = -30588;     // 0x7CB574: a word of the .sdata read by the calendar draw
}  // namespace g
namespace pad {  // the pad words at 0x7E0000 + offset (20_menu_ui.md 4.1)
inline constexpr s32 kTrig = 0x94E;     // gPadFlags: buttons pressed this frame
inline constexpr s32 kRepeat = 0x952;   // pressed or auto-repeat
inline constexpr s32 kTrig2 = 0x958;    // pressed this frame (second source)
inline constexpr s32 kRepeat2 = 0x95A;  // pressed or auto-repeat (second source)
}  // namespace pad
namespace spr {  // sprite-file tables at 0x830000 + offset
constexpr s32 camp(int i) { return 0x3B70 + 4 * i; }    // 0x833B70[14]: the camp sprite files (ui5::sf::kFiles)
constexpr s32 screen(int i) { return 0x3A50 + 4 * i; }  // 0x833A50[3]: the open screen's files (item, skill, trade)
constexpr s32 comu(int i) { return 0x3B40 + 4 * i; }    // 0x833B40[11]: the social-link screen's files (camp_comu.pak)
inline constexpr s32 kComuPages = 0x3A60;               // 0x833A60: u16[8], the arcana pages shown (0-terminated)
inline constexpr s32 kComuCards = 0x3AD8;               // 0x833AD8: a card texture slot of the social-link screen
inline constexpr s32 kCurrentPersona = 0x6BA8;          // 0x836BA8: u16, the protagonist's current persona slot
}  // namespace spr
namespace root {  // the main list's work ("H_CampRootDraw", 44 bytes; ui3 / ui5)
inline constexpr s32 kTimer = 4;    // u32: the animation frame
inline constexpr s32 kCursor = 16;  // u32: the cursor row 0..6
inline constexpr s32 kStrip = 32;   // s32: the side strip's scroll (0..767)
inline constexpr s32 kArrived = 40; // u32: 1 once the cursor bar reached its row
}  // namespace root
namespace parts {  // "H_PcStatusParts00" (12 bytes)
inline constexpr s32 kState = 0;
inline constexpr s32 kMode = 4;     // s16: 0 wait, 1 fade in, 2 fade out
inline constexpr s32 kFrame = 6;    // s16: the fade's frame 0..8
}  // namespace parts
namespace sts {  // "H_CampStatusDraw" (the Status page, 72 bytes; ui5 sub_127B00)
inline constexpr s32 kState = 0;
inline constexpr s32 kAnswer = 28;   // s32: what the page answers its root (-1 none)
inline constexpr s32 kParts = 36;    // u32: the "H_PcStatusParts00" task
inline constexpr s32 kBuild = 60;    // u32: the texture build of the character picture
inline constexpr s32 kTexture = 64;  // u32: the built texture
inline constexpr s32 kSlide = 68;    // f32: the page's slide (starts at -20.0)
}  // namespace sts
namespace stp {  // "H_CampStatusPersonaDraw" of the Status screen (32 bytes; ui5 sub_128040)
inline constexpr s32 kState = 0;
inline constexpr s32 kAlpha = 12;    // s16: the table's fade 0..255
inline constexpr s32 kAnswer = 20;   // s32: the page's answer to the root (-1 none)
inline constexpr s32 kPicture = 28;  // u32: the persona picture task (sub_1339A0)
}  // namespace stp
namespace frp {  // "H_CampFrStatusPersonaDraw" (44 bytes; ui5 sub_167F40)
inline constexpr s32 kState = 0;
inline constexpr s32 kPc = 14;       // s16: the party member
}  // namespace frp
namespace equip {  // "H_CampSoubi1Draw" (the equipment screen, 708 bytes; ui5 sub_130F20)
inline constexpr s32 kPak = 0;              // u32: camp/camp_equip.pak
inline constexpr s32 kState = 4;            // u32: the state (this screen keeps it at +4)
inline constexpr s32 kPc = 18;              // s16: the party member
inline constexpr s32 kSlotsArrived = 24;    // u32: the slot panels' tweens all finished
inline constexpr s32 kSlot = 28;            // s16: the slot 0..3 (weapon, armour, boots, accessory)
inline constexpr s32 kCursor = 32;          // s32: the candidate cursor (row on the page)
inline constexpr s32 kScroll = 36;          // s32: the candidate list's first row
inline constexpr s32 kCandidates = 40;      // u16[300]: the stock indices the member may equip in the slot
inline constexpr s32 kCandidateTail = 640;  // the second output of sub_131090
inline constexpr s32 kCandidateCount = 684; // s32
inline constexpr s32 kFile0 = 688;          // u32: the two sprite files of the pak
inline constexpr s32 kFile1 = 692;
inline constexpr s32 kSlotTweens = 696;     // u32: 10 tween records (the slot menu)
inline constexpr s32 kListTweens = 700;     // u32: 10 tween records (the candidate list)
inline constexpr s32 kBackdrop = 704;       // u32: 1 tween record (the scrolling backdrop)
}  // namespace equip
namespace per {  // "H_CampStatusPersonaDraw" of the persona screen (108 bytes; ui5 sub_1336B0)
inline constexpr s32 kState = 0;
inline constexpr s32 kCursor = 4;       // s32: the row
inline constexpr s32 kPrevCursor = 12;  // s32: the row before the last move
inline constexpr s32 kIds = 26;         // u16[12]: the persona id of each row
inline constexpr s32 kSlots = 50;       // u16[12]: the stock slot of each row
inline constexpr s32 kCount = 74;       // s16: the rows
inline constexpr s32 kArrived = 76;     // u32: the list tweens all finished
inline constexpr s32 kPak = 80;         // u32: camp/camp_per.pak
inline constexpr s32 kPicture = 84;     // u32: the persona picture task (sub_1339A0)
inline constexpr s32 kFiles = 88;       // u32[3]: the pak's sprite files
inline constexpr s32 kFile1 = 92;
inline constexpr s32 kFile2 = 96;
inline constexpr s32 kTweens = 100;     // u32: 100 tween records (the list)
inline constexpr s32 kDetailTweens = 104;  // u32: 10 tween records (the detail view)
}  // namespace per
namespace comu {  // "H_CampComuDraw" (the social-link screen, 416 bytes; ui5 sub_136750)
inline constexpr s32 kState = 0;
inline constexpr s32 kCursor = 4;     // s32: the row on the page
inline constexpr s32 kScroll = 8;     // s32: the first row
inline constexpr s32 kLinks = 32;     // s32[]: the active links (-1 terminated)
inline constexpr s32 kHelpFile = 336; // u32: camp/comu/datComuHelp.bmd
}  // namespace comu
namespace item {  // "H_CampNewItem" (the item screen, 200 bytes; ui5 sub_14EE80)
inline constexpr s32 kState = 0;
inline constexpr s32 kTimer = 4;          // s32: the fade-in frame (state 2)
inline constexpr s32 kPak = 8;            // u32: camp/camp_item.pak
inline constexpr s32 kTargets = 12;       // s32[4]: the targets (1 = the protagonist, then the party)
inline constexpr s32 kTargetCount = 28;   // s32
inline constexpr s32 kPersonas = 32;      // s32[12]: the used stock slots
inline constexpr s32 kPersonaCount = 80;  // s32
inline constexpr s32 kTargetCursor = 84;  // s32: -2 = everyone
inline constexpr s32 kPersonaCursor = 88; // s32
inline constexpr s32 kTargetKind = 92;    // u16: the item's target kind (sub_17BB40; 3 = none)
inline constexpr s32 kRibbon = 96;        // a tween record inline (the ribbon): +100 active, +160 its alpha
inline constexpr s32 kRibbonActive = 100;
inline constexpr s32 kRibbonAlpha = 160;
inline constexpr s32 kItemList = 164;     // u32: the item list (2,424 bytes, ilist)
inline constexpr s32 kEquipList = 168;    // u32: the equipment list (11,632 bytes, elist)
inline constexpr s32 kMaterialList = 172; // u32: the material list (2,424 bytes, ilist)
inline constexpr s32 kFiles = 176;        // u32[3]: the pak's sprite files (copied to 0x833A50)
inline constexpr s32 kFile1 = 180;
inline constexpr s32 kFile2 = 184;
inline constexpr s32 kTweens = 188;       // u32: 80 tween records (the item page)
inline constexpr s32 kEquipTweens = 192;  // u32: 40 tween records (the equipment page)
inline constexpr s32 kMaterialTweens = 196;  // u32: 40 tween records (the material page)
}  // namespace item
namespace ilist {  // an item / material list (2,424 bytes)
inline constexpr s32 kEntries = 12;   // {s32 id, s32 count}[300]
inline constexpr s32 kCount = 2412;   // s32
inline constexpr s32 kCursor = 2416;  // s32: the row on the page (5 rows)
inline constexpr s32 kScroll = 2420;  // s32: the first row
}  // namespace ilist
namespace elist {  // an equipment list (11,632 bytes; ui5 sub_13CC90)
inline constexpr s32 kRows = 100;      // 36-byte rows [320]: +0 id, +4 stock index, +20 target bit, +24..+26 bytes
inline constexpr s32 kCount = 11620;   // s32
inline constexpr s32 kCursor = 11624;  // s32: the row on the page
inline constexpr s32 kScroll = 11628;  // s32: the first row
}  // namespace elist
namespace sys {  // "H_CampSystemMenuDraw" (380 bytes; ui5 sub_1548A0); "H_ConfigMenuDraw" shares the layout
inline constexpr s32 kState = 0;
inline constexpr s32 kCursor = 4;        // s32: the menu entry 0..5
inline constexpr s32 kMenuTweens = 12;   // u32: 10 tween records (the menu)
inline constexpr s32 kPageTweens = 16;   // u32: 100 tween records (the open page)
inline constexpr s32 kFiles = 20;        // u32[2]: camp_sys.pak's sprite files (the draws take &work[+20])
inline constexpr s32 kFile1 = 24;
inline constexpr s32 kBuild = 28;        // u32: the status texture build
inline constexpr s32 kTexture = 32;      // u32: the status texture
inline constexpr s32 kHelpFile = 36;     // u32: camp/datMixraidHelp.bmd (message 12)
inline constexpr s32 kQuestFile = 40;    // u32: facility/msg_quest.bmd (message 8)
inline constexpr s32 kPak = 44;          // u32: camp/camp_sys.pak
inline constexpr s32 kArrived = 48;      // u32: the page's tweens all finished (input enabled)
inline constexpr s32 kSpellScroll = 320; // s32: the fusion-spell list
inline constexpr s32 kSpellCursor = 324;
inline constexpr s32 kQuestCursor = 328; // s32: the request list
inline constexpr s32 kMonth = 332;       // s32: the calendar's month
inline constexpr s32 kDay = 336;         // s32: the calendar's day
inline constexpr s32 kConfigCursor = 340;
inline constexpr s32 kConfigValues = 344;  // s32[7]: the option values (flags 387..393; written back by "OK")
inline constexpr s32 kFade = 372;        // s32: the config screen's backdrop fade 0..10 ("H_ConfigMenuDraw")
inline constexpr s32 kQuitFade = 376;    // s32: the quit-to-title fade 0..10
}  // namespace sys
namespace skl {  // "H_NewCampSkillDraw" (the skill screen, 80 bytes; ui5 sub_1617D0)
inline constexpr s32 kState = 0;
inline constexpr s32 kTargetCursor = 24;  // s32: -2 = everyone
inline constexpr s32 kFiles = 28;         // u32[3]: camp_skil.pak's sprite files
inline constexpr s32 kFile1 = 32;
inline constexpr s32 kFile2 = 36;
inline constexpr s32 kList = 40;          // u32: the skill list (sub_15C840)
inline constexpr s32 kTargetKind = 44;    // u16: the skill's target kind (sub_17BB40)
inline constexpr s32 kPak = 48;           // u32: camp/camp_skil.pak
inline constexpr s32 kTweens = 56;        // u32: 60 tween records
inline constexpr s32 kTargetCount = 76;   // s32
}  // namespace skl
namespace pty {  // "H_CampPartyStatusDraw" (56 bytes; ui5 sub_166A50)
inline constexpr s32 kState = 0;
inline constexpr s32 kPc = 8;            // s32: the party member
inline constexpr s32 kSlot = 16;         // s32: the equipment slot
inline constexpr s32 kPak = 24;          // u32: camp/camp_fr%02d.pak
inline constexpr s32 kTexture = 28;      // u32: the character picture
inline constexpr s32 kFile0 = 32;        // u32: the pak's sprite files
inline constexpr s32 kFile1 = 36;
inline constexpr s32 kBuild = 40;        // u32: the picture's texture build
inline constexpr s32 kTweens = 44;       // u32: 10 tween records (the page)
inline constexpr s32 kListTweens = 48;   // u32: 10 tween records (the equipment list)
inline constexpr s32 kList = 52;         // u32: the equipment list (11,632 bytes, elist)
}  // namespace pty
}  // namespace ui6

// --- status (game/src/ui/ui6_status.cpp) -----------------------------------------------------------------------------
// [H_Camp_RootDrawList] (root work): draws the camp main list from the tween records at gp-19876: rows 0..6 (sub_115AD0
// of camp sprite file 4, row 5 greyed in The Answer), the cursor bar (record 10), the selection caption (record 11,
// sprite 7 + cursor), the date panel (record 12: the time-of-day icon from datGetTime -- holiday / Sunday variants
// through clndIsHolidayOrSunday --, the month and day as digits of sprite font 1, the weekday), the side panels (record
// 13) and the money (record 14: datGetMoney through sprintf + sub_40EB50).
void sub_11BBB0(EEContext& ctx);  // 0x11BBB0, 2464 bytes
// [H_Camp_RootDrawOpen] (root work, z in $f12): the main list's open animation frame: frames 16..21 fade the persona
// background (sub_114450 on the CampPersonaTexControl texture, gp-19856) and the black curtain in, frames 12..21 slide
// the frame sprite (camp file 2) in; then the list (sub_11BBB0).
void sub_11C880(EEContext& ctx);  // 0x11C880, 1024 bytes
// [H_Camp_RootDrawConfirm] (root work, z in $f12): the 22-frame confirm flash after a selection (state 0xA): the
// background fading out over 10 frames, the frame sprite, the scrolling side strip (+32 moving by 1, wrapping at 767 by
// -448, file 7 sprites 3 / 4) and the list.
void sub_11CFB0(EEContext& ctx);  // 0x11CFB0, 1004 bytes
// [H_Camp_RootDrawClose] (root work, z in $f12): the close animation (states 7 / 8): background alpha 255 - 255 * timer
// / 22, the frame sprite, the side strip and the list.
void sub_11D6D0(EEContext& ctx);  // 0x11D6D0, 936 bytes
// [H_Camp_RootDrawIdle] (root work): the side strip (+32 scrolling, file 7 sprites 3 / 4, drawn twice near the wrap)
// and the list -- the frame drawn when nothing animates.
void sub_11DDB0(EEContext& ctx);  // 0x11DDB0, 552 bytes
// [H_Camp_RootDrawInput] (root work, z in $f12): the input state's frame: the persona background, the frame sprite, the
// cursor bar easing to y 57 + 19 cursor (gp-19876 record 10 +60; +40 = 1 once it arrived), the side strip and the list.
void sub_11DFE0(EEContext& ctx);  // 0x11DFE0, 912 bytes
// [H_Camp_StatusDrawHp] (xy, pc, gauge, alpha): the HP block of a party member: the name (sub_177790 -> sprintf ->
// sub_3B32D0), the gauge (sub_113A30, `gauge` px), the frame (sprite 4 of camp file 8), the current HP (datGetPcHp) as
// up to three digits of sprite font 2 (sprite 11 + digit) and the maximum (datGetPcMaxHp) in colour 102.
void sub_1236A0(EEContext& ctx);  // 0x1236A0, 1232 bytes
// [H_Camp_StatusDrawPcPanelIn] (xy, pc, frame): a party member's status panel during its reveal: the frame sprite
// sliding in over 3 frames, then from frame 4 the level (datGetPcLevel, two digits of font 2), HP (sub_1236A0) and SP
// (sub_123B70) blocks with gauges 76 - 76 * cur / max, the condition icon (sub_123F80) and the sparkle ring
// (sub_124090), each with its own fade.
void sub_124370(EEContext& ctx);  // 0x124370, 1972 bytes
// [H_Camp_StatusDrawPcPanel] (xy, ?, pc, alpha): the same panel drawn at once: frame, level digits, HP / SP blocks with
// their gauges (76 - 76 * cur / max), condition icon, sparkle ring.
void sub_124B30(EEContext& ctx);  // 0x124B30, 708 bytes
// [H_Camp_UpdateStatusPartsTask] Update of a status sub-task ("H_PcStatusParts00", created by sub_1269A0 state 3):
// state 0 -> 1; mode +4 = 0 waits, 1 fades the backdrop in over 8 frames (+6 counter), 2 fades it out; draws the
// persona background, the frame strip and the camp file 1 / 12 decorations.
void sub_125D70(EEContext& ctx);  // 0x125D70, 2412 bytes
// [H_Camp_UpdateStatusDrawTask] Update of "H_CampStatusDraw" (the Status page; jump table 0x7B5B10): state 0 starts the
// texture build of camp/status/i_camp_hum_blue.tmx (The Answer: AGS_i_camp_hum_blue_03.tmx) into +60; 1 polls it (+64
// the texture); 2 waits for the flash transition 2; 3 closes the main list (sub_11D3A0), creates "H_PcStatusParts00"
// and sets the side portraits to screen 2; 4 is the input state: cancel (0x20) closes, R1 / L1 (0x2000 / 0x8000) answer
// "switch page" to the root (+12); 5 / 6 and 7 / 8 the two exits (-1). Every state draws the page (sub_1273B0, the 512
// x 1024 strips sub_126710).
void sub_1269A0(EEContext& ctx);  // 0x1269A0, 2564 bytes
// [H_Camp_StatusDrawSocial] (pc, xy, alpha): the protagonist's social stats: Academics / Charm / Courage rank sprites
// (datGetAcademicLevel / CharmLevel / CourageLevel of the points sub_16C6F0 / 16C740 / 16C790; camp file 9 sprites
// level - 1, + 6, + 13) with their frames, and the next-level exp (sub_16D2F0 through sprintf + sub_40EB50).
void sub_1273B0(EEContext& ctx);  // 0x1273B0, 1676 bytes
// [H_Camp_UpdateStatusPersonaDrawTask] Update of "H_CampStatusPersonaDraw" (the Status screen's persona page; jump
// table 0x7B5B40): state 0 waits for flash 3 and creates the persona picture (sub_1339A0 of datGetPcPersonaId(1)); 1
// waits for the flash, sets the side portraits to screen 3; 2 fades the table in (+12 by 10 to 255) and is the input
// state (cancel / page switch answered in +20); 3..5 fade out and return -1. Draws the persona picture (sub_133A80) and
// the status table (sub_128140 kinds 0 / 1 / 2).
void sub_127C00(EEContext& ctx);  // 0x127C00, 956 bytes
// [H_Camp_StatusDrawPersonaStats] (xy, bonus, persona, alpha): the five persona stats (St Ma En Ag Lu:
// datPersonaGetTotalStat(persona, i)) as two digits of sprite font 2, plus the bonus bytes +56..+60 of `bonus` when
// given.
void sub_128720(EEContext& ctx);  // 0x128720, 1308 bytes
// [H_Camp_StatusDrawPersonaBaseStats] (xy, bonus, persona, alpha): as sub_128720 with sub_173580 (the stat without
// equipment bonus) -- the facility screens' variant.
void sub_128C40(EEContext& ctx);  // 0x128C40, 1308 bytes
// [H_Camp_StatusDrawSkills] (xy, next, persona, alpha): the persona's eight skill slots in 2 x 4 cells (sprite 18 of
// camp file 8, the skill name through sprintf + sub_3B32D0, the element icon), the new skills of `next` (+62) marked;
// then the next-skill line (sub_1FC230 / sub_1FC3C0 / sub_1FB1F0).
void sub_1293B0(EEContext& ctx);  // 0x1293B0, 1912 bytes
// [H_Camp_StatusDrawPersonaPanelIn] (xy, persona, frame): the persona status panel's 20-frame reveal: the frame sliding
// in from +300 over 5 frames, the nine stat labels (sub_1281E0) appearing one per frame, resistances (sub_128480),
// stats (sub_128720), the five bars (handles of sprite 24 of camp file 10, scaled by the stat), the skills (sub_1293B0)
// and the next-exp text (sprintf of sub_173340 - sub_173330 through sub_40EB50), each faded by its frame.
void sub_129B30(EEContext& ctx);  // 0x129B30, 2600 bytes
// [H_Camp_StatusDrawPersonaPanelOut] (xy, persona, frame): the same panel sliding out (+300 * frame / 5) and fading
// over 5 frames.
void sub_12A560(EEContext& ctx);  // 0x12A560, 1788 bytes
// [H_Camp_StatusDrawPersonaPanel] (xy, persona, alpha): the persona status panel drawn at once: labels, frames,
// resistances, stats, the five stat bars, skills and next exp.
void sub_12AC60(EEContext& ctx);  // 0x12AC60, 1692 bytes
// [H_Camp_StatusDrawPersonaPanelPlain] (xy, persona, alpha): sub_12AC60 without the camp file 1 / 12 frame sprites (the
// variant drawn over another backdrop).
void sub_12B300(EEContext& ctx);  // 0x12B300, 1376 bytes
// [H_Camp_StatusDrawPersonaTable] (xy, bonus, persona, alpha): the persona table used by the persona screen and the
// facilities: labels, resistances, stats with the bonus bytes (sub_128720), the five bars with the gain bars
// (sub_129160 per stat), skills, next exp.
void sub_12B860(EEContext& ctx);  // 0x12B860, 1144 bytes
// [H_Camp_StatusDrawPersonaBaseTable] (xy, bonus, persona, alpha): sub_12B860 on the base stats (sub_128C40 /
// sub_173580).
void sub_12BFB0(EEContext& ctx);  // 0x12BFB0, 1144 bytes
// [H_Camp_DrawPersonaCard] (xy, bonus, persona, fade): the facility screens' persona card: the table (sub_12B860) at
// alpha 255 - fade, the frame (sprite 1 of camp file 8) and the arcana card (camp file 6, datPersonaGetArcana - 1) at
// +12 / +96, the level (sub_124E60) and the name (sub_124FD0).
void sub_133180(EEContext& ctx);  // 0x133180, 356 bytes
// [H_Camp_DrawPersonaBaseCard] (xy, bonus, persona, fade): sub_133180 on the base-stat table (sub_12BFB0).
void sub_133460(EEContext& ctx);  // 0x133460, 356 bytes
// [H_Camp_PersonaDrawElement] (tween, ?, element, ids, cursor, previous): one tween element of the persona screen's
// detail (jump table 0x7B5C80): 0 / 1 the persona table and panel of the selected (+cursor) or previous stock slot, the
// rest its frame sprites of camp file 13.
void sub_1345B0(EEContext& ctx);  // 0x1345B0, 836 bytes
// [H_Camp_PersonaRunDetailTweens] (tweens, ...): steps the 10 detail tween records (sub_18B700), draws each active one
// (sub_1345B0) and returns 1 when all reached their last frame.
void sub_134900(EEContext& ctx);  // 0x134900, 260 bytes
// [H_Camp_UpdateFrStatusPersonaDrawTask] Update of "H_CampFrStatusPersonaDraw" (the party-status screen's persona page;
// jump table 0x7B62C0): state 0 requests flash 2 (sub_1685E0) and creates a "CampPersonaDispCtlDraw" picture of the
// member's persona (+14); 1 sets the side portraits to screen 3; 2 draws the picture background and fades the persona
// panel in (sub_129B30 / sub_12AC60) -- cancel / page switch answered; 3..5 fade out (sub_12A560) and return -1.
void sub_167930(EEContext& ctx);  // 0x167930, 1412 bytes

// --- equip (game/src/ui/ui6_equip.cpp) -------------------------------------------------------------------------------
// [H_Camp_UpdateSoubi1DrawTask] Update of the equipment screen "H_CampSoubi1Draw" (jump table 0x7B5BC0, state at +4): 0
// waits for flash 15, allocates the three tween arrays (+696 / +700 / +704) and requests camp/camp_equip.pak (+0); 1
// takes its two sprite files (+688 / +692); 2 waits for them; 3 slides the five slot panels in; 4 is the slot menu
// (confirm 0x40 -> 7, cancel 0x20 -> 5, up / down move the slot +28 with wrap on a fresh press); 5 / 6 close (-1); 7
// waits for flash 16 and collects the candidates (sub_131090 into +40, count +684); 8 / 9 swap the panels; 0xA is the
// candidate list (H_Camp_MoveListCursor 5 rows, +36 scroll / +32 cursor): confirm equips (datSetEquipmentIdx) and
// rescales HP / SP to the new maxima (cur * newMax / oldMax), cancel goes back; 0xB / 0xC return to the slot menu.
// Every state draws the backdrop (sub_12DDC0) and the panels (sub_12DC20 / sub_12DCF0).
void sub_12C430(EEContext& ctx);  // 0x12C430, 6124 bytes
// [H_Camp_EquipRunSlotTweens] (equip work): steps the 10 slot-panel tweens (+696), draws each active one (sub_12E3B0)
// and returns 1 when all finished.
void sub_12DC20(EEContext& ctx);  // 0x12DC20, 208 bytes
// [H_Camp_EquipRunListTweens] (equip work): the same for the 10 candidate-list tweens (+700, sub_12F6D0).
void sub_12DCF0(EEContext& ctx);  // 0x12DCF0, 208 bytes
// [H_Camp_EquipDrawSlotPanel] (equip work, element, tween): one panel of the slot menu (jump table 0x7B5C00): elements
// 0..3 the weapon / armour / boots / accessory slots of the member (+18: the equipped entry's icon from its mask
// (sub_12DF50), name (datGetItemName), and power / accuracy / evasion / defence through sub_12E170, highlighted when it
// is the slot +28), the rest the frame, the member's HP / SP and the help line.
void sub_12E3B0(EEContext& ctx);  // 0x12E3B0, 4896 bytes
// [H_Camp_EquipDrawListPanel] (equip work, element, tween): one panel of the candidate list (jump table 0x7B5C20): the
// slot header, the five visible candidates (+40 from +36) with icon, name and the stat of the slot's kind, the cursor
// row, the comparison arrows of the selected candidate against the equipped item, the scroll marks.
void sub_12F6D0(EEContext& ctx);  // 0x12F6D0, 5988 bytes
// [H_Camp_UpdateCampStatusPersonaDrawTask] Update of the persona screen "H_CampStatusPersonaDraw" (jump table
// 0x7B5C40): 0 waits for flash 4, allocates the tweens (+100 x100, +104 x10), requests camp/camp_per.pak (+80) and
// lists the used stock slots (ids +26, slots +50, count +74; printf "stock ID = %d"); 1 takes its three sprite files
// and creates the persona picture (+84); 2 waits; 3 slides the rows in (y 73 + 29 row); 4 is the list (confirm -> 7
// detail, 0x80 -> 11 release, cancel -> 5; up / down with wrap on a fresh press, the picture follows the cursor through
// sub_133B80); 5 / 6 close; 7..10 the detail view (sub_134900) and back; 0xB..0xD release a persona (the active one
// refused with message 2, else message 1 yes / no -> sub_174C10, the list rebuilt); 0xE / 0xF make the selected persona
// the protagonist's (message 3 -> datPersonaSelectSlot, sub_11B370).
void sub_1311D0(EEContext& ctx);  // 0x1311D0, 8108 bytes
// [H_Camp_PersonaDrawRow] (tween, files, element, ids, cursor): one element of the persona list: 28 the header, 27 the
// frame, 1..13 a row (the persona name from datGetPersonaName, highlighted on the cursor), 14..26 its level digits
// (font 1 / font 2) and the "active" marks when it is the protagonist's persona; then the scrolling backdrop pair (+48
// moving by -1, wrapping at 750).
void sub_133E10(EEContext& ctx);  // 0x133E10, 1688 bytes
// [H_Camp_PersonaRunListTweens] (tweens, files, ids, cursor): steps the 100 list tweens, draws each active one
// (sub_133E10), returns 1 when all finished.
void sub_1344B0(EEContext& ctx);  // 0x1344B0, 244 bytes

// --- comu (game/src/ui/ui6_comu.cpp) ---------------------------------------------------------------------------------
// [H_Camp_UpdateComuDrawTask] Update of the social-link screen "H_CampComuDraw" (jump table 0x7B5D00): 0 waits for
// camp/comu/datComuHelp.bmd (+336, message 11) and builds the list of shown arcana pages into 0x833A60 from flags 336..
// / 26 / 343; 2 waits for flash 7, creates the file loader "H_CampComuFileSetup" and lists the active links
// (datComuIsActive) into +32; 3..5 slide in and are the input state (cancel -1, confirm -> 6, H_Camp_MoveListCursor
// over the links); 6 releases the pictures (textureDestroy); 7 / 8 wait for flash 8 and request the arcana and bust-up
// pictures (sub_135460 / sub_135120); 9 / 0xB the card view: the picture builds (sub_10C1A0 / sub_10C3A0 of
// off_5DB998[datComuGetArcana] and camp/commu/tim2_bustup/i_bust%02X_{a,b}.tmx). Draws through sub_136820 / sub_138E80.
void sub_1355C0(EEContext& ctx);  // 0x1355C0, 4080 bytes
// [H_Camp_ComuDrawLinkRow] (xy, link, selected, alpha): one social-link row: the rank (datComuGetRank; "MAX" sprites at
// 10, else the digit of font 1), the arcana icon (camp comu file 1, 2 * (0x5E3220[link] - 1) + 1), the partner's name
// (off_5D80E4[10 * link + rank] through sprintf + sub_3B2F90), the reversed / broken colouring (sub_172160 /
// sub_1717C0).
void sub_136A10(EEContext& ctx);  // 0x136A10, 2288 bytes
// [H_Camp_ComuDrawListIn] (xy, links, cursor, scroll, z, frame): the link list's reveal (from frame 23 the five row
// frames, each row easing in 3 frames after the previous), the ribbon (sub_1368A0), the rows (sub_136A10), the cards
// (sub_137300) and the cursor.
void sub_137580(EEContext& ctx);  // 0x137580, 2912 bytes
// [H_Camp_ComuDrawList] (xy, links, cursor, scroll, z, alpha): the link list drawn at once: five row frames, the
// ribbon, rows, cards, cursor.
void sub_1380E0(EEContext& ctx);  // 0x1380E0, 1740 bytes
// [H_Camp_ComuDrawListOut] (xy, links, cursor, scroll, z, alpha): the same list for the close fade (identical layout to
// sub_1380E0).
void sub_1387B0(EEContext& ctx);  // 0x1387B0, 1736 bytes
// [H_Camp_ComuDrawArcanaPage] (xy, page, row, alpha): the arcana page of the card view: page 29 lists the shown arcana
// (0x833A60, names sub_1775A0, the selected row highlighted), other pages the six text lines of 0x5DBB00 for that page.
void sub_139660(EEContext& ctx);  // 0x139660, 1888 bytes
// [H_Camp_ComuDrawCardIn] (xy, links, cursor, scroll, ?, frame): the card view's reveal: the black corner (sub_139DC0),
// the ribbon, the card and its pulse (sub_138EE0 / sub_1392D0) sliding in from frame 8 over 5 frames, the arcana
// picture (gp-19856 + ..., sub_1140D0), the rank block, the partner name and help lines (sub_3C7E20 / sub_3C7E50), the
// arcana page (sub_139660).
void sub_139FC0(EEContext& ctx);  // 0x139FC0, 4108 bytes
// [H_Camp_ComuDrawCard] (xy, links, cursor, scroll, ?, alpha): the card view drawn at once (the same parts as
// sub_139FC0 in place).
void sub_13AFD0(EEContext& ctx);  // 0x13AFD0, 3296 bytes

// --- item (game/src/ui/ui6_item.cpp) ---------------------------------------------------------------------------------
// [H_Camp_BuildTradeList] (list): builds the equipment trade list: the hero stock's held indices 0..299 sorted by item
// id (qsort / sub_131000), then the 20-entry equipment table (owner -1) as 36-byte rows from +100: id, its lowest
// target bit (sub_13C6A0), kind, the two flag bytes, the source (index + 4096), the stats of its kind (power /
// accuracy, evasion, defence).
void sub_13C780(EEContext& ctx);  // 0x13C780, 1288 bytes
// [H_Camp_ItemDrawEquipList] (xy, list, alpha): the equipment page's list: the scroll marks when the list has rows
// (+2905 words = the count), the five visible rows from the scroll (+11628) with icon (camp file 0, by the kind table),
// name, the owner marks and the stat digits (font 1), the cursor row (+11624) highlighted.
void sub_13D1A0(EEContext& ctx);  // 0x13D1A0, 5480 bytes
// [H_Camp_ItemDrawEquipList2] (xy, list, alpha): sub_13D1A0 at the trade layout (text 40 px higher, 14 px further
// right).
void sub_13E710(EEContext& ctx);  // 0x13E710, 5508 bytes
// [H_Camp_ItemDrawEquipDetail] (xy, list, alpha): the selected equipment row's detail: its kind icon (jump table
// 0x7B5EB0 on the row's kind: 0..5 -> sprite 0, 2, 4 ...), name and stat digits.
void sub_13FCA0(EEContext& ctx);  // 0x13FCA0, 2604 bytes
// [H_Camp_ItemDrawItemList] (xy, list, alpha): the item page's list: the scroll marks, the five visible rows (+2420
// scroll) with the item name (sub_17B100 -> sprintf -> sub_3B32D0) and the count as two digits of font 1, the cursor
// row (+2416) with sprite 27 of camp file 0.
void sub_1406D0(EEContext& ctx);  // 0x1406D0, 1880 bytes
// [H_Camp_ItemDrawMaterialList] (xy, list, alpha): sub_1406D0 for the material page (cursor sprite 29).
void sub_140E30(EEContext& ctx);  // 0x140E30, 1880 bytes
// [H_Camp_ItemOpenLayout] (item work): starts the item page's slide-in on the 80 tween records (+188): every panel from
// 50 px right of its place over frames 6..13.
void sub_141660(EEContext& ctx);  // 0x141660, 2376 bytes
// [H_Camp_ItemTargetOpenLayout] (item work): moves the item page's panels for the target choice (the list to x 110, the
// target panels in).
void sub_141FB0(EEContext& ctx);  // 0x141FB0, 2432 bytes
// [H_Camp_ItemTargetCloseLayout] (item work): moves the panels back from the target choice to the item list.
void sub_142930(EEContext& ctx);  // 0x142930, 2488 bytes
// [H_Camp_ItemCloseLayout] (item work): the item page's slide-out (every panel in place, mode 2 / curve 2 over 5
// frames).
void sub_1432F0(EEContext& ctx);  // 0x1432F0, 1800 bytes
// [H_Camp_ItemMoveTargetCursor] (item work, previous): moves the target highlight: the target rows (85 px apart from y
// 62) of the new cursor (+84) and of `previous` restart their tweens.
void sub_143A00(EEContext& ctx);  // 0x143A00, 1236 bytes
// [H_Camp_ItemPersonaOpenLayout] (item work): the panels for the persona choice (an item used on a persona: incense).
void sub_143EE0(EEContext& ctx);  // 0x143EE0, 2600 bytes
// [H_Camp_ItemPersonaCloseLayout] (item work): back from the persona choice.
void sub_144910(EEContext& ctx);  // 0x144910, 2624 bytes
// [H_Camp_ItemDrawElement] (tween, element, item work): one tween element of the item page (jump table 0x7B5F10): the
// page frames and tabs (camp file 0 sprites 43, 39, 33 ...), the item list (sub_1406D0), the selected item's
// description, the target panels (name, HP / SP digits and gauges, condition: sub_177790, datGetPcHp / MaxHp / Sp /
// MaxSp, sub_16C970 / datGetPcCondition), the persona panels (stats raised by the item: sub_17BF70 / sub_17BFA0 /
// sub_173580), the ribbon.
void sub_145520(EEContext& ctx);  // 0x145520, 4584 bytes
// [H_Camp_ItemPageLeftLayout] (item work): slides the item page out to the left (-100) for a page change.
void sub_146710(EEContext& ctx);  // 0x146710, 3548 bytes
// [H_Camp_ItemPageFromLeftLayout] (item work): slides the item page in from the left.
void sub_1474F0(EEContext& ctx);  // 0x1474F0, 3572 bytes
// [H_Camp_EquipPageCloseLayout] (item work): the equipment page's slide-out (the 40 records +192).
void sub_1482F0(EEContext& ctx);  // 0x1482F0, 1424 bytes
// [H_Camp_ItemDrawEquipElement] (tween, element, item work): one element of the equipment page: 32 / 31 frames, 20 the
// list (sub_13E710 of +168), 21 the detail, the rest frame sprites of camp files 0..2 and 13.
void sub_148880(EEContext& ctx);  // 0x148880, 900 bytes
// [H_Camp_EquipPageLeftLayout] (item work): slides the equipment page out to the left.
void sub_148C10(EEContext& ctx);  // 0x148C10, 2772 bytes
// [H_Camp_ItemPageRightLayout] (item work): slides the item page in from the right (+100).
void sub_1496F0(EEContext& ctx);  // 0x1496F0, 3488 bytes
// [H_Camp_ItemPageToRightLayout] (item work): slides the item page out to the right.
void sub_14A490(EEContext& ctx);  // 0x14A490, 3452 bytes
// [H_Camp_EquipPageFromLeftLayout] (item work): slides the equipment page in from the left.
void sub_14B210(EEContext& ctx);  // 0x14B210, 2764 bytes
// [H_Camp_MaterialPageCloseLayout] (item work): the material page's slide-out (the 40 records +196).
void sub_14BCE0(EEContext& ctx);  // 0x14BCE0, 1448 bytes
// [H_Camp_ItemDrawMaterialElement] (tween, element, item work): one element of the material page: 31 / 30 frames, 20
// the list (sub_140E30 of +172), 21 the detail, the rest frame sprites.
void sub_14C290(EEContext& ctx);  // 0x14C290, 812 bytes
// [H_Camp_UpdateNewItemTask] Update of the item screen "H_CampNewItem" (jump table 0x7B6040, 31 states): 0 takes
// camp_item.pak's three sprite files (+176.., copied to 0x833A50); 1 allocates the tweens (+188 x80, +192 / +196 x40)
// and the three lists (items +164, equipment +168, materials +172); 2 fades in over 8 frames; 3 waits for flash 9,
// fills the lists (items 4000..4223 of the hero stock, the equipment list, materials = flags 513..639 as ids
// 5001..5127), the targets (protagonist + party) and the persona slots; 4 is the item list: confirm on a usable item
// (record +4 of sub_170E90 is 0 or 2) -> 9 the persona choice when sub_17BBB0 has bit 4, else the target kind
// sub_17BB40 into +92 (3 = no target; non-zero = everyone, +84 = -2) and 6; cancel -> 5, R1 -> 16 equipment page, L1 ->
// 29 material page, else the list cursor; 5 closes (-1); 6..8 the target choice (sub_13BE50 uses the item; an item
// whose record +8 is 233 used in an explorable floor (K_FldDungeon_IsCurrentFloorExplorable) drops by one, sets flag
// 0x1417 and ends the menu); 9..11 the persona choice (stats raised up to 99); 16..24 the equipment page (sell /
// discard with message 6 when equipped); 25..30 the material page. Every state steps and draws its page's tweens
// (sub_145520 / sub_148880 / sub_14C290).
void sub_14C5C0(EEContext& ctx);  // 0x14C5C0, 10072 bytes

// --- system (game/src/ui/ui6_system.cpp) -----------------------------------------------------------------------------
// [H_Camp_UpdateSystemMenuDrawTask] Update of "H_CampSystemMenuDraw" (jump table 0x7B60E0): 0 waits for flash 6, builds
// the status texture (+28), allocates the tweens (+12 x10, +16 x100), requests camp/datMixraidHelp.bmd (+36),
// facility/msg_quest.bmd (+40) and camp/camp_sys.pak (+44); 1 / 2 load them (messages 12 / 8, sprite files +20 / +24)
// and slide in; 3 is the menu (entries 0..5: confirm -> 26 calendar, 21 quest list, 16 fusion-spell list, 11 help list,
// 6 config, 5 -> message 7 "return to title"; cancel -> 4; up / down with wrap, The Answer skipping entries); 4 / 5
// close; 6..10 the config page (values +344 from flags 387.., written back on confirm); 11..15, 16..20, 21..25 the
// three lists; 26..30 the calendar (+332 month, +336 day; L1 / R1 change the month); 31..33 quit to the title (flag
// 5149, the fade +376, sub_17F990 / sub_1BA8D0).
void sub_14F7D0(EEContext& ctx);  // 0x14F7D0, 20380 bytes
// [H_Camp_SystemDrawMenuElement] (tween, files, element, ...): one element of the system menu (jump table 0x7B6170): 0
// the scrolling background (two sub_1140D0 strips, +52 moving by -1, wrapping at -1000), 1 the six row frames, 2 the
// title, 3 the entries (The Answer's set greyed), the cursor and the status picture.
void sub_154970(EEContext& ctx);  // 0x154970, 1532 bytes
// [H_Camp_SystemRunMenuTweens] (tweens, files, texture, cursor): steps the menu's 10 tweens, draws each active one
// (sub_154970), returns 1 when all finished.
void sub_154F70(EEContext& ctx);  // 0x154F70, 244 bytes
// [H_Camp_SystemDrawHelpElement] (tween, files, element, table, count, scroll, cursor): one element of the help list:
// 99 the frame, 6 the header, 5 the eight visible rows of the text table off_5DA500 (sub_3B32D0, the cursor row
// highlighted), the scroll marks.
void sub_155070(EEContext& ctx);  // 0x155070, 1692 bytes
// [H_Camp_SystemRunHelpTweens] (tweens, files, ...): steps the help list's tweens and draws them (sub_155070); 1 when
// all finished.
void sub_155710(EEContext& ctx);  // 0x155710, 276 bytes
// [H_Camp_SystemDrawConfigElement] (tween, files, element, cursor, values): one element of the config page: 99 the
// frame with the page title (sprite 15 + cursor), 6 the eight option rows (sprites 140..150; the cursor row lit), the
// option values (on / off and the level marks of each option's value).
void sub_155830(EEContext& ctx);  // 0x155830, 2308 bytes
// [H_Camp_SystemRunConfigTweens] (tweens, files, cursor, values): steps the config page's tweens and draws them
// (sub_155830); 1 when all finished.
void sub_156140(EEContext& ctx);  // 0x156140, 244 bytes
// [H_Camp_SystemDrawSpellElement] (tween, files, element, scroll, cursor): one element of the fusion-spell list: 99 the
// frame, 6 the eight rows of skills 272 + scroll + i that flags 5072 + scroll + i unlocked (names from the skill table
// 0x7CE4EC, 19-byte rows), the cursor row tinted, the selected skill's section-2 record (sub_30C220) and the personas
// it needs (datGetPersonaName).
void sub_156240(EEContext& ctx);  // 0x156240, 3136 bytes
// [H_Camp_SystemRunSpellTweens] (tweens, files, scroll, cursor): steps the fusion-spell list's tweens and draws them
// (sub_156240); 1 when all finished.
void sub_156E80(EEContext& ctx);  // 0x156E80, 244 bytes
// [H_Camp_SystemDrawQuestElement] (tween, files, element, ...): one element of the quest (request) list: 99 the frame,
// 13 the selected request's detail (datBlock27Get, the request record sub_403880: the reward item's icon / name, the
// required items and their counts, the state marks), the list rows with their numbers (font 1 / 2) and state sprites.
void sub_156F80(EEContext& ctx);  // 0x156F80, 10616 bytes
// [H_Camp_SystemRunQuestTweens] (tweens, files, cursor): steps the quest list's tweens and draws them (sub_156F80); 1
// when all finished.
void sub_159900(EEContext& ctx);  // 0x159900, 228 bytes
// [H_Camp_SystemDrawCalendarElement] (tween, files, element, month, day): one element of the calendar: 99 the frame, 20
// the month grid (tbl_clndMonthLengths, weekdays through clndGetWeekDay / clndGetDaysSinceStartFromDate, the moon phase
// icons for days 29 / 6 / 14 ... of clndGetMoonPhase, holidays sub_17DB40, today's mark from clndGetCurrentMonth / Day,
// the event marks from sub_17AE30 and flags), the year "2009", the selected day's event text (strcpy / strcat,
// sub_3C3FE0).
void sub_1599F0(EEContext& ctx);  // 0x1599F0, 6456 bytes
// [H_Camp_SystemRunCalendarTweens] (tweens, files, month, day): steps the calendar's tweens and draws them
// (sub_1599F0); 1 when all finished.
void sub_15B330(EEContext& ctx);  // 0x15B330, 244 bytes
// [H_Camp_UpdateConfigMenuDrawTask] Update of "H_ConfigMenuDraw" (the title screen's config; jump table 0x7B61B0):
// every frame the backdrop sub_113A30 at alpha 255 * +372 / 10; 0 waits for its camp sprite set-up task (gp-19880) and
// builds the status texture; 1 / 2 load the files as sub_14F7D0 does; then the config page alone (sub_155830, the
// values of flags 387.., written back with datSetFlag on confirm, sub_103CB0 / sub_103C30 applying them) and the close.
void sub_15B430(EEContext& ctx);  // 0x15B430, 4140 bytes

// --- skill (game/src/ui/ui6_skill.cpp) -------------------------------------------------------------------------------
// [H_Camp_SkillBuildList] (list): builds the skill screen's list: every distinct skill of the used stock slots
// (datPersonaIsSlotUsed / datPersonaGetHeroPersona, eight skills each; datPersonaSelectSlot is called per slot, the
// current slot word_836BA8 read first) as 20-byte rows from +12 -- skill id, persona id, stock slot, HP cost, SP cost
// (sub_17B480 / sub_17B500 / sub_17B5B0) --, a skill two personas share kept with the one of higher Ma
// (datPersonaGetTotalStat(.., 1)); +2012 the count; then sorted: skills 192..255 first, the rest by id.
void sub_15C840(EEContext& ctx);  // 0x15C840, 1544 bytes
// [H_Camp_SkillDrawList] (xy, list, alpha): the skill list: the scroll marks (+2012 count), five visible rows from
// +2020 with the element icon (datSkillElementClass), the name (datGetSkillName -> sprintf -> sub_3B32D0) and the cost
// digits (font 1), the cursor row (+2016) highlighted.
void sub_15CE50(EEContext& ctx);  // 0x15CE50, 2692 bytes
// [H_Camp_SkillOpenLayout] (skill work): the skill page's slide-in on its 60 tweens (+56): the panels from 50 px right
// over frames 6..13, the target rows (85 px apart).
void sub_15DA70(EEContext& ctx);  // 0x15DA70, 1760 bytes
// [H_Camp_SkillCloseLayout] (skill work): the skill page's slide-out.
void sub_15E150(EEContext& ctx);  // 0x15E150, 1424 bytes
// [H_Camp_SkillTargetOpenLayout] (skill work): the panels for the target choice.
void sub_15E6E0(EEContext& ctx);  // 0x15E6E0, 1880 bytes
// [H_Camp_SkillMoveTargetCursor] (skill work, previous): moves the target highlight (rows 85 px apart from y 42) from
// `previous` to the cursor (+24).
void sub_15EE40(EEContext& ctx);  // 0x15EE40, 1244 bytes
// [H_Camp_SkillTargetCloseLayout] (skill work): back from the target choice.
void sub_15F320(EEContext& ctx);  // 0x15F320, 1896 bytes
// [H_Camp_SkillDrawElement] (tween, element, skill work): one tween element of the skill page: 52 / 51 / 50 frames, the
// list (sub_15CE50), the ribbon (sub_15D8E0), the caster's and the targets' panels (name, HP / SP digits and gauges,
// condition).
void sub_15FA90(EEContext& ctx);  // 0x15FA90, 3428 bytes
// [H_Camp_UpdateNewCampSkillDrawTask] Update of the skill screen "H_NewCampSkillDraw" (jump table 0x7B61E0): 0 / 1 fade
// the background in (8 frames) and close the main list (sub_11DA80); 2 takes camp_skil.pak's three sprite files
// (+28..); 3 waits for them, builds the skill list (+40, sub_15C840); 4 waits for flash 13 and slides in; 5 / 6 the
// list (confirm on a usable skill -> 8 target choice, cancel -> 7 close, -1); 8 / 9 the target choice: confirm casts
// (sub_15C520 when the target is near the hero (K_FldUnit_IsPcNearHero) and accepts the skill, sound 1) or refuses; 0xA
// back to the list. Steps and draws its tweens (sub_15FA90) every frame.
void sub_160800(EEContext& ctx);  // 0x160800, 3780 bytes
// [H_Camp_UpdateFrStatusRootTask] Update of "H_CampFrStatusRoot" (the party-status root a script opens for one member;
// jump table): creates the two side-portrait tasks ("h_camp_pc_kani_control" / "h_camp_persona_kani_control") and the
// status page (sub_166A50); state 1 waits for the flash (sub_1685D0), 2 swaps the status page and the persona page
// (sub_167F40) on the page answer, 3 recreates them, 5 waits for the page task's end (-1). Draws the frame sprite of
// camp file 11.
void sub_1618A0(EEContext& ctx);  // 0x1618A0, 1212 bytes

// --- party (game/src/ui/ui6_party.cpp) -------------------------------------------------------------------------------
// [H_Camp_PartyDrawElement] (tween, element, party work): one tween element of "H_CampPartyStatusDraw" (jump table
// 0x7B6210): 0 the character picture strips (sub_1140D0 of the texture +28, +52 scrolling to -1064), the frames, the
// four equipment slots (icon from the mask, name, the slot's stats through sub_12E170), the member's HP / SP and level.
void sub_161D90(EEContext& ctx);  // 0x161D90, 5532 bytes
// [H_Camp_PartyDrawEquipListElement] (tween, element, party work): one element of the party-status equipment list (as
// sub_12F6D0 for the member +8 and slot +16): slot header, candidates, cursor, comparison.
void sub_163330(EEContext& ctx);  // 0x163330, 5612 bytes
// [H_Camp_UpdatePartyStatusDrawTask] Update of "H_CampPartyStatusDraw" (jump table 0x7B6260): 0 waits for
// camp_fr%02d.pak (+24) and starts the character picture build (camp/chara/i_camp_hum_blue_%02d.tmx; The Answer: AGS_
// variants for members 1 / 3 / 9); 1 takes the texture (+28) and the sprite files, requests flash 1, allocates the
// tweens (+44); 2 slides in and sets the portraits to screen 2; 3 is the input state (confirm -> 9 equipment, cancel ->
// close, page switch); 4..7 the exits; 9..0xB the equipment list (+52 = an 11,632-byte list from sub_13C240; confirm
// equips through the equipment setters 0x16FEA0..0x170530), 0xC / 0xD back (RwFree of the list).
void sub_164920(EEContext& ctx);  // 0x164920, 8324 bytes
// [H_Camp_UpdatePartyStatusRootTask] Update of "H_CampPartyStatusRoot" (the party-status screen opened on the whole
// party; jump table 0x7B62A0): 0 lists the members present (flags 322..330 -> ids 2..) into +36 (+56 count); 1 waits
// for the flash; 2 / 3 switch between members and pages (sub_166A50 / sub_167F40 into +20); 5 / 6 wait for the page
// task, destroy the side portraits and recreate them. Draws the frame sprite of camp file 11 (twice).
void sub_166C70(EEContext& ctx);  // 0x166C70, 2356 bytes
// [H_Camp_UpdateTradeSubTask] Update of the equipment trade sub-task (jump table 0x7B6300): 0 takes the pak's two
// sprite files (+20 / +24, also 0x833A50 / 0x833A54) and starts a camp sprite set-up (sub_119F10(task, 1)); then the
// trade list (sub_13CF80 / sub_169110 draws) with H_Camp_MoveListCursor; confirm moves the selected equipment between
// the stock and the member (the 0x16F630..0x170530 setters, sub_177C10), a full stock shows a message.
void sub_168810(EEContext& ctx);  // 0x168810, 2096 bytes
// [H_Camp_TradeDrawList] (?, xy, list, alpha): the trade list over a dimmed screen: sub_21EA00(41), a 640 x 448
// rectangle (sub_113A30), sub_21EA00(40), then the list (sub_13D1A0) at +40 / +50.
void sub_169110(EEContext& ctx);  // 0x169110, 224 bytes
// [H_Camp_TradeDrawListDetail] (?, xy, detail, list, alpha): sub_169110 with the detail (sub_13FCA0) above the list
// (+80).
void sub_1691F0(EEContext& ctx);  // 0x1691F0, 320 bytes
// [H_Camp_UpdateTradeDrawTask] Update of "H_CampTradeDraw" (jump table 0x7B6320): 0 takes the pak's sprite files and
// its camp sprite set-up; 1 builds the trade list (sub_13C780) and the stock-over background
// (brItem_CreateStockOverBgTask); then the list (sub_169B90 draws, H_Camp_MoveListCursor): confirm asks (message) and
// moves the item (sub_16FEA0 and the stock setters), cancel ends.
void sub_169470(EEContext& ctx);  // 0x169470, 1648 bytes
// [H_Camp_TradeDraw] (trade work, xy, list, alpha): the trade screen: the two lists (sub_16A700, sub_16AF90) and the
// frame sprites (49 ...) of the trade file, with sub_21EA00 render-state switches between them.
void sub_169B90(EEContext& ctx);  // 0x169B90, 1172 bytes
// [H_Camp_OpenTradeDraw] COMM: the drop / trade screen for scrGetIntPara(0): member 1 merges every item 4000..4299 of
// the member's pouch (owner id + 256) into the hero stock (capped at 99), else moves the member's equipment entries
// back; then creates "H_CampTradeDraw" (update sub_169470) with camp/camp_drop.pak into gp-19828.
void sub_16A030(EEContext& ctx);  // 0x16A030, 1640 bytes
// [H_Camp_TradeDrawStock] (trade work, xy, list, alpha): the stock column of the trade screen: frames 68..70, the six
// visible rows with their owner marks, names (datGetItemName) and the cursor (+2906 words).
void sub_16A700(EEContext& ctx);  // 0x16A700, 2184 bytes
// [H_Camp_TradeDrawDetail] (trade work, xy, list, alpha): the detail column: frames 72..78, the selected row's stats
// (sprintf + sub_40EB50) and its help line (sub_3C7E20).
void sub_16AF90(EEContext& ctx);  // 0x16AF90, 2668 bytes
}  // namespace p3fes::game
