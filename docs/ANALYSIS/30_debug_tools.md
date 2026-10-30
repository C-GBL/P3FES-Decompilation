# 30 — The developer tools left in retail: what they are, how they were reached, what they say about the records

_Research note, 2026-10-24 (no game or recompiler code changed). Sources: the readable bodies and headers of the events / events2 / events3 / field4 / field7 slices (`game/src/event/`, `game/src/field/`, `game/include/p3fes/game/`), the ELF `SLUS_216.21` (strings, pointer tables and descriptor rows read directly at the addresses given), the gitignored Hex-Rays reference `ida/pseudocode/` (read-only; the master database was not opened). Machine-readable result: **`tools/ours/debug_ui/debug_fields.json`**, checked by **`tools/ours/debug_ui/check_debug_fields.py`**; new type-recovery names in **`tools/ours/types/deltas/debug_ui.json`**. Tags: **obs** = read from the instructions or the ELF data; **inf** = our reading. Names: the developers' label strings are quoted as evidence; every field name is our own proposal (ADR-0009); no community names were used._

## 0. Headline

* **The retail ELF still carries a complete cutscene editor** (`mt_evtMenu.c`, 0x36FA80–0x385520 plus the action table of `mt_evtMain.c`): 41 menus in the 48-slot table `0x6A0270`, 48 actions in `0x69DE40`, a key list with 30 column kinds (`0x69E100`) laid out per unit type for 51 unit types (`0x69E1A0`, names `0x69F1B0`), 33 titled choice lists, 18 list-box tools applied live, a free debug camera, a bezier path editor, a function-curve shaper, a sprite editor and a project save. Every screen is a labelled UI over a real record (EvtWork, EvtUnit, EvtKey and the key's 48-byte extra record). (obs)
* **It also ships the field NPC placement editor** ("field editor", `sub_1E2370`): FREE CAMERA MODE / CREATE NPC / LIST NPC / CREATE POS / LIST POS / ALL CLEAR / SAVE, writing FBN files (`SAVEFILE = f%03d_%03d_%03d.FBN`). It is reached only from the cutscene editor's settings (FIELD EDIT). (obs)
* **The widgets are generic** (`k_lbox.c`): the "ksk list box" takes a table of 32-byte descriptors {label, kind, text, value, min, max, hex, flag}; retail has **20 such tables, 65 rows** — each row is a developer label with its type and range. (obs)
* **An unlabelled effect editor** sits in the draw callback of effect class 10 kind 9 (`sub_3407E0`), driven by a second pad word. (obs; "second pad" is inf)
* **Why nothing reaches them:** the only event viewer retail creates is `mtEvtMain_CreateZikkiPlayModeEventViewerTask`, whose first update sets `kFlagPlayMode` (EvtWork+4 bit 3); `sub_36E690` skips the whole debug-pad block (pause, seek, free camera, R2 = editor) while that bit is set. (obs)
* **What it gives the Inspector:** 294 fields in 13 records, 215 with a developer label, 215 that type recovery did not have (most of them the per-unit-type parameter block of EvtKey), with ranges, steps, units and enum labels; plus 154 menu rows, 65 list-box rows and 33 choice lists cross-referenced to those fields. The types delta names 25 fields (5 records, one new) with **0 new conflicts** (header agreement 2,525 → 2,541 found, 7 → 7 conflicting).

| tool | code | reached from | records it edits | labels |
|---|---|---|---|---|
| cutscene ("event") editor | `sub_36D5F0` step, menus `0x6A0270`, actions `0x69DE40` (events2 / events3) | R2 in a playing event, only when EvtWork+4 bit 3 is clear | EvtWork, EvtUnit, EvtKey (+ per-type views), EvtKey extra record, globals | menu titles, row strings, 30 column titles, 33 choice lists, 51 unit-type names |
| list-box tools of menu 26 | openers `sub_385BD0`..`sub_386A00`, applier `sub_373700` | the key menu / settings actions | the same, live (lights, bust-ups, effects, camera) | 16 descriptor tables `0x6A0350`..`0x6A09F0` |
| free debug camera | menu 26 kind 8, `sub_3625E0`, `sub_38A0C0` | position / camera tools | camera model 0x1E59, save slots 0x958830 / 0x958840 | none (the tool's box says END) |
| bezier path editor | menu 28 `sub_37D5D0`, `sub_37CFE0` | key menus (paths) | the path 0x958700 | BEZIER EDIT / BEZIER MAX |
| field editor (NPC placement) | `sub_1E2370`, `sub_1E1850`, `sub_1E3F10`, `sub_1E4BC0`, `sub_1E58D0`, `sub_1E60B0`, writer `sub_1E2430` / `sub_1E2BD0` | settings item 8 FIELD EDIT | FBN NPC / position records | 4 descriptor tables `0x683E10` / `0x684120` / `0x684220` / `0x684330` |
| ksk window / list box / color box | `sub_1A2200`.., `sub_1A3B10`.., `sub_1A4B70` (field7_lbox.h) | the tools above | DbgListBoxItem (556 B) | — |
| effect editor | `sub_3407E0` (class-10 kind-9 draw) | pad word 0x7E0982 while such an effect draws | the kind's 264-byte block | none |
| debug print | `h_dbgprt.c` (font2.h), `sub_1050E0` | every editor line (`sub_38A260`) | DbgPrintNode (280 B) | — |
| camera debug shapes | `K_Draw_UpdatePointTask` / `K_Draw_UpdateCylinderTask` | field camera setters | point / cylinder work | — |
| metrics overlay | EvtWork+140, "metrics draw" task (`sub_1A7020` / `sub_1A7060`) | L3 / L2 in a non-play event | — | TOTAL(%3.2fM) |

## 1. How the cutscene editor was reached, and why retail cannot (obs)

The event viewer task is the only owner of the editor. `sub_36E690` [evtStepPlay] runs every frame of a playing event. After applying the frame's keys it does:

* `gPadFlags & 0x200` (L3) toggles EvtWork+140 (metrics) — in play mode only when the gp word 0x7CE618 (`sub_39E6F0`) is 1.
* `gPadFlags & 1` (L2) toggles the "metrics draw" task — same play-mode condition.
* **only when EvtWork+4 bit 3 (`kFlagPlayMode`) is clear:** `gPadFlags & 2` (R2) sets bit 0 (paused) and returns `sub_36D5F0` [evtStepEditor]; otherwise the free camera follows the sticks (`sub_3625E0`), square drops the cursor model at the camera (`sub_362F20`), start toggles the pause (unless something holds the timeline), and while paused `sub_362390` seeks: L1 / R1 previous / next message key, left / right ±1 frame, up / down ±10, L2 + left / right ±100, select back to the start frame.

Retail's field root creates events only through `mtEvtMain_CreateZikkiPlayModeEventViewerTask` (0x36F3B0, "(ZikkiPlayMode)EventViewer"), and the viewer's first update writes `kFlags = kFlagPlayMode` (events2.h §START step 3). No retail path clears bit 3, so the editor block is dead code. "Zikki" (実機, "the actual machine") is the developers' own name for that retail play mode.

The field editor needs the cutscene editor: `sub_36D5F0` starts `sub_1E2370` ("field editor") when kFlagPmWait is set by settings item 8 ("FIELD EDIT GO?"). The effect editor is different: it lives in a shipped draw callback and only needs an effect of class 10 kind 9 on screen and input on the pad word 0x7E0982 (52 bytes after pad 1's pressed word 0x7E094E, so the second controller: inf). Whether any retail effect uses kind 9 was not checked.

## 2. The cutscene editor's machinery (obs; events3.h has the per-function details)

* **Menu stack.** EvtWork+144 holds up to 8 entries {s16 menu, s16 x, s16 y, s16}; +208 the depth, +212 the top menu. Every frame `sub_36D5F0` walks the stack and calls `sub_385860(menu, level, x, y, work)`, which stores the level's text size (100 − 10·level) and calls `0x6A0270[menu]`; only the top menu reads the pad. A null slot makes `sub_385860` return 0 ("stay"). Triangle backs out; an empty stack leaves the editor and restores the object camera.
* **Results.** 0 stay; 1 accept → `0x69DE40[menu](result, previous, work)`; −1 pop; other values go to the action (key list: −2 delete with "DELETE FRAME.OK?" YES / NO / YES ALL DELETE, −4 unit settings).
* **Edit fields.** Menus never write a record directly: the opener (the key-menu action `sub_369A20`, the settings action `sub_36CC30`) copies the record's fields into EvtWork's edit slots — kEdValue / Min / Max (+364..+372), kEdValueF and its range (+388..+396), kEdParams[12] (+408..+452), kEdCondition (+1924..+1930), kEdChoice (+280..+292) — and the menu's action copies them back (events2 setters `sub_366EB0`..`sub_368C10`). That one indirection is why every row maps to exactly one record offset (`debug_fields.json` `event_editor.menus[].rows[].target` / `via`).
* **Drawing.** `sub_36F900` draws a frame of 12-pixel cells and calls a header callback and a row callback; text goes through `sub_38A260` → `sub_1050E0`, a debug-print node with a scale (colour 4 = cursor, 5 = cursor of an inactive menu, 14 = labels, 0 = text).
* **Input** (the US build's logical bits on 0x7E094E / 0x7E0952 / 0x7E094C): 0x1000 up, 0x4000 down, 0x2000 right, 0x8000 left, 0x40 confirm ("RR" in the help lines), 0x20 cancel ("RD"), 0x80 square ("RL"), 0x10 triangle, 4 / 8 L1 / R1, 1 / 2 L2 / R2, 0x100 select, 0x800 start.

The menus (id: what it edits; the row-by-row data is in the JSON):

| id | title | edits | id | title | edits |
|---|---|---|---|---|---|
| 1 | (17-item settings, 0x69F900) | EvtWork | 27 | DIRECT MOVE | UNIT key, control 1 |
| 2 | (choice list) | kEdChoice | 28 | BEZIER EDIT | path 0x958700 |
| 3 | (name keyboard) | EvtWork+304 | 29 | ICON MENU | UNIT key, control 5 |
| 4 | (unit list) | EvtWork+356 | 30 | KOMA MENU | KOMA key |
| 5 | (key list) | the unit's keys | 31 | KUBI MENU | UNIT key, control 6 |
| 6 | FRAME CHANGE. | kEdValue (frames) | 32 | RANDOM JUNP MENU | RAN-JUMP key |
| 7 / 8 | VALUE CHANGE. | kEdValue / kEdValueF | 33 | CUSTOM EVENT  MENU | C-EVENT key (kinds 0/3/4/5) |
| 9 | [E%3d_%03d.PM1+2+3] | event number 0x7CCA68 / 0x7CCA6C | 34 | CONDITION JUMP  MENU | COND-JUMP key |
| 10 | (resource list) | LINK / RESID | 35 | ATTACH MODEL MENU | UNIT key, control 7 |
| 11 | (live edit) | TMX sprite editor | 36 | COMU LV RANDOM JUMP | COMULVJUMP key |
| 13 | MESSAGE MENU | MESSAGE key | 37 | PARAM UPDOWN MENU | C-EVENT key kind 2 |
| 14 | FLAG COMPARE MENU | key condition +8..+14 | 38 | COUNT JUMP MENU | CNT-JUMP key |
| 15 | (unit settings) | EvtUnit +32 / +34 / +36 | 39 | KYUJITU YAKUSOKU JUMP MENU | HOLY-JUMP key |
| 16 | MOTION CHANGE MENU | UNIT key, control 2 | 40 | FUNCTION CURVE MENU | CTL CAM key +48, curves 0x6A2AF0 |
| 17 | (model pick) | EvtUnit +34 / +36 | 41 | PRESENT MENU | C-EVENT key kind 6 |
| 23 | POS CHANGE MENU | UNIT key, control 3 | 42 | FIELD OBJ ANIM MENU | FIELDOBJ key, ANIM |
| 24 | CONTROL CAMERA MENU | (orphaned, see §7) | 43 | PRESENT AGERU MENU | C-EVENT key kind 7 |
| 25 | CHANGE ROT MENU | UNIT key, control 4 | 44 | DEBUG MENU | kEdParams[0] |
| 26 | (list-box tool) | 18 tool kinds | 45 | CARD EFFECT MENU | C-EVENT key kind 9 |
| | | | 46 / 47 | ASIOTO MENU / SPU SE MENU | footsteps / SPU_SE key |

**The key list.** Each unit type has a row of `0x69E1A0` (s16 count, then up to 10 column kinds); the 30 kinds have titles `0x69E100` (START LENG RANGE ALPHA SCALE HOKAN FOVY VOLUME NO END LINK SW MODE DAT SOFTEN_BIAS FADE PRE MESSAGE FLAG PARAM TMX INT CAMERA PARAM BUSTUP PARAM AMB EFFECT POS CAM UNIQ PARAM RESID) and widths `0x69E180`. `sub_3760A0` formats a key by the column kind *and* the unit type; `sub_369A20` opens the editor for a column with the key field, a range and a menu. Reading those two functions side by side gives the whole parameter block +16..+55 of EvtKey per unit type, which is what `debug_fields.json` `records.EvtKey.variants` holds (63 variants). Unit-settings columns (`0x69E420`, titles OFFSET / SLIGHT TYPE / PATH / IDX) exist for D3P, LIGHT, SLIGHT, BED, EPL and PACK-UNIT.

**Menu 26, the live tools.** The opener writes the tool kind to kEdValue, opens a ksk list box on a descriptor table and pushes menu 26; `sub_373700` reads the box every frame (`sub_1A41B0` ints, `sub_1A42F0` floats) and applies it: 0 bust-up LOAD (X / Y / BUPNO / FUKU / HYOUJOU), 2 FIELD NO, 3 PC CONTROL, **4 the SLIGHT light (AMB R/G/B, DIR R/G/B, DIR Y / X → `sub_38B550`)**, 6 / 7 / 15 P3EFF create / move / alpha, 8 the free camera (D-pad along the view and side axes, L1 / L2 height, R1 / R2 tilt, triangle ×5, select / start save / restore, L3 drops the cursor key's model at the camera, square snaps to the ground), 9 / 10 the CTL CAM eye or followed model, 11 COUNT IDX, 12 the KUBI target, 13 PADACT vibration, 14 ALPHA CHANGE, 16 SCALE CHANGE, 17 SPU SOUND; kinds 1, 5 and 18 have appliers but no opener.

## 3. What the editor tells us about the records (the five most useful findings first)

1. **EvtKey's parameter block is a union keyed by the unit type (and often by +16).** The 51 unit types (STAGE UNIT CAMERA D3P MESSAGE ADX_SE FADE QUAKE BLUR LIGHT SLIGHT SFOG FF BLUR2 MBLUR DBLUR FILTER MFILTER BED ADX_BGM MG1 MG2 FBOKASI RBLUR TMX RAIN EPL HBLUR PADACT MOVIE TIMEI RENDERTEX BISTA CTL CAM WAIT B_UP KOMA P3EFF JUMP KEYFREE RAN-JUMP C-EVENT COND-JUMP COND-ON COMULVJUMP CNT-JUMP HOLY-JUMP FIELDOBJ PACK-UNIT FIELDEFF SPU_SE) each give +16..+55 their own fields; UNIT / PACK-UNIT keys have 11 control types (DISP, POS CHANGE D, MOTION CHANGE, POS CHANGE, ROT CHANGE, ICON DISP, KUBI, MODEL ATTACH, ALPHA CHANGE, SHADOW ONOFF, SCALE CHANGE), C-EVENT keys 14 custom-event kinds, P3EFF keys 4 modes. Example — a character motion key (UNIT, control 2): +20 u32 {GROUP, MOTNO, LOOP, HOKAN 0..100}, +32 OFFSET, +34 TYPE (NORMAL / TABLE), +35 MOT2USE, +36 MOT2NO, +37 LOOP2, +38 HOKAN2, +40 SPEED 10..500, +42 SPEED2. An Inspector that shows one fixed layout for every key would mislabel almost every field; the variant table is the fix.
2. **Value ranges and units straight from the clamps.** Frames everywhere (lengths 0..10000, jump frames 0..30000 / 0..60000), CAMERA FOVY stored in radians and edited as degrees 1..180, motion speeds 10..500, interpolation 0..100 frames, alpha 0..255 (FF / BLUR SCALE −255..255), PADACT ZIKAN 0..3000 / TUYOSA 0..255 / ON / OFF ZIKAN 0..1000, sprite X / Y −500..1000 and ScaleW / ScaleH −10..10 in 0.01 steps, light colours 0..1 in 0.01 steps, light direction 0..359 degrees, FBN collision / shadow radius 0..300 (defaults 60 / 30), FIELD MAJOR / MINOR 0..255, ENV 0..10000. The list-box step rule (sub_1A2A80): left / right int 1 / float 0.01, L1 / R1 10 / 0.1, L2 / R2 100 / 1 (×10 after 150 frames held), values wrap.
3. **The event-wide settings fields get their real names.** EvtWork+60 / +64 FIELD MAJOR / MINOR NO, **+70 FBN NO** (the NPC placement set = the FBN's third number, MtScene+20) and **+72 ENV NO** (MtScene+22) — the headers called them field_arg70 / field_arg72; +68 PC CONTROL (FALSE / TRUE); +69 COUNT IDX / "USE COUNTER NO" 0..8; +74 EVENT SPUFILE LOAD (a halfword); +76 bit 0 LOAD VOICE, bit 1 MESSAGE TYPE (NORMAL / GAMEOVER), **bit 2 BATTLE BLUR** (the header reads bit 2 as "fade to the field on exit" — see §6).
4. **FBN NPC records, as the developers typed them** (list box 0x684120): +8 RESID 0..1023 (stored 0xC00 | id), +4 MAJOR ID 0..11, +6 MINOR ID 0..65535 ({4, 0xFFFF} = the VIRTUAL placeholder the schedule tables fill), +12 COLLIS RADIUS 0..300 (default 60), **+96 SHADOW TYPE 0..4 (default 3)**, **+100 SHADOW RADIUS 0..300 (default 30)**, plus the editor-only SEPARATE LIGHT flag. That is a complete Inspector for our own NPC placement, byte-compatible with the FBN writer.
5. **Enums for every MODE column.** 33 titled choice lists (HOKAN MODE, ON/OFF MODE, TRANS MODE NORMAL / ADD / SUB, FADE TYPE, ADX SE MODE PLAY / STOP CH0 / CH1, CONTROL TYPE PLAY / FADEIN / FADEOUT / TRANS / VOLDOWN / VOLUP / ALLSTOP, UNIT CONTROL TYPE, B-UP CONTROL LOAD / FADEOUT / KUCHI / MEPACHI, KOMA MODE, EFFECT MODE, PADACT, CONFIG DRAW STOP, TIMEI, SELECT, BISTA, PRIORITY HIGH / LOW, FADE MODE, END STOP, WAIT MODE, MESSAGE STOP, KEYFREE, CUSTOM EVENT (14), COND ON (KAZE / KAZEGIMI / HIROU / TUUJOU / KOUTYOU / ZEKKOUTYOU), FIELDOBJ DISP / ANIM, ...) — the editor's dropdowns can be these strings verbatim (with an English gloss), and the stored value is the list index.

Further findings:

* The key condition (+8..+14) is edited as four halfwords: type 0 Disable / 1 **LOCAL FLAG** / 2 **GLOBAL FLAG**, flag number 0..4999 (type 2) or 0..9 (type 1), value 0..1 / 0..10, bank **EVT FLAG / COMU FLAG / SYS FLAG** (the key list suffixes E / C / S). The player reads the low bytes of +12 / +14.
* EvtUnit+32 is labelled **OFFSET** and the key list's START column shows key frame + unit+32 (the header names it kHold).
* EvtUnit+34 is per type: SLIGHT "SLIGHT TYPE" (DISABLE / ALL / UNIT ALL, ≥ 3 = one model whose id is +36), D3P / BED / EPL "PATH" (PATH APPLY MODE SOUTAI / ZETTAI = relative / absolute), PACK-UNIT "IDX" −1..4; camera units use it as the camera mode.
* SLIGHT keys keep the HOKAN flag in **+4** (the name slot of other keys) and their light in the 48-byte record at +72: DIR R/G/B +0/+4/+8, DIR X +16, DIR Y +20, AMB R/G/B +32/+36/+40 (floats).
* TMX keys are sprites: BLEND +17 (SEMI / ADD / SUB), X / Y +20 / +22, RGBA +24..+27, ScaleW / ScaleH +28 / +32, PRIORITY +36.
* KOMA ("comic panel") keys: CHARA +20, FACE +22, FUKU +24 (hex), SYURUI +26, X / Y +28 / +30, TYPE DIRECT / REF +32, REFNO +34 (the bust-up table).
* PADACT is the controller vibration: ZIKAN, TUYOSA (strength), ON / OFF ZIKAN.
* The six-entry hero condition list (KAZE "cold", KAZEGIMI, HIROU "tired", TUUJOU "normal", KOUTYOU "good", ZEKKOUTYOU "great") drives COND-JUMP and COND-ON keys; PARAM UPDOWN names the 8 stats (GAKURYOKU, MIRYOKU, YUUKI, TIKARA, MA, TAI, SOKU, UN).

## 4. The ksk widgets (k_lbox.c; field7_lbox.h) (obs)

* **ksk window** (84-byte work): a fading frame with a border and fill colour; states build → borders grow → fade in → open → fade out.
* **ksk list box** (68-byte work, items 556 bytes): items {id, kind 0 label / 1 string / 2 flag / 3 int / 4 float, label[256], text[256], int value, float value, min, max, hex}; the box sizes itself to the widest "label value" line (12 px per character). `sub_1A3DC0` builds a box from a descriptor table of 32-byte rows {char *label, s32 kind, char *text, s32 value, s32 min, s32 max, s32 hex, s32 flag} (float items take value / min / max as ints). The 20 retail tables are in `debug_fields.json` `list_boxes` with what each row writes.
* **color box** (`sub_1A4B70`, 12-byte work): an RGBA editor on a 4-byte target, used by the effect editor (the list box `sub_1A4940` R / G / B / ALPHA).
* **debug shapes**: the camera's point task {on, pos, rgba} and cylinder task {on, pos, radius, height}.

These are exactly the widgets an Inspector needs (labelled int / float / flag / string rows with a range), so the descriptor format doubles as our own schema: `debug_fields.json` fields map 1:1 to descriptor rows.

## 5. The field editor, the effect editor and the print layer (obs)

* **Field editor** (`field4.h`; `sub_1E1850` main box `0x683E10`): CAMERA (FREE CAMERA MODE), CREATE NPC (STATIC → box `0x684120`; VIRTUAL → box `0x684220`, model {4, 0xFFFF}, radius 30, shadow 3 / 50), LIST NPC (`sub_1E4BC0`: MOVE NPC / DELETE NPC, the list "ResID=%04d Major=%d Minor=%03d"), CREATE POS (`0x684330`), LIST POS (`sub_1E60B0`: MOVE POS / DELETE POS), ALL CLEAR, SAVE ("SAVEFILE = f%03d_%03d_%03d.FBN", "saved.." / "failed.."), EXIT. The analog sticks move the new NPC's frame controller; `sub_1E2430` snapshots the scene's class-3 and class-8 resources into FBN records and `sub_1E2BD0` builds the file image (header magic 0x12345678, version 0x00010001, 112-byte NPC and 96-byte position records). The editor's task work is in the JSON as FieldEditorNpcWork.
* **Effect editor** (`sub_3407E0`, the draw slot of the class-10 kind row 9 at `0x69C94C`: {0x3402C0, 0x340600, 0x340790, 0x3406F0, 0x3407E0, 0x341BA0, size 264}): on the pad word 0x7E0982, up / down and left / right move two floats +164 / +168 (0.01 steps, kept ordered, at most 0.99), R1 / L1 / R2 / L2 open a color box on four RGBA words +172 / +176 / +180 / +184, square / triangle set the byte +196, select prints the four vectors ("%d: %f , %f , %f"); every change is mirrored into globals 0x957AA0.. / 0x957B44 / 0x957B48 / 0x957B64 so it survives the effect. No label strings.
* **Debug print** (`h_dbgprt.c`, font2.h): a 40 × 53 character screen at 0x7E1E30 and a queue of 280-byte nodes {next, x, f32 y, text, rgba} drawn with `font/size12/f11_001.tmx` (present on the disc: `DATA/FONT/SIZE12/F11_001.TMX`). `sub_1050E0` is the editor's variant with a scale (+272).
* **Project save** (`sub_38E860`, mt_evtLoadSave.c): opens the PM files of the menu-9 event number with mode "wb" through `sub_4C0240` ("save cut field", "save object table", "save rain data", "save path data", "save pm3 file").

## 6. Cross-reference with type recovery (tools/ours/types)

Counted by comparing `debug_fields.json` with `seeds.json` + every delta (before `debug_ui.json`) and with the recovered classes of a fresh `types_build.py` run.

| record | debug-UI fields | not in type recovery | named differently / conflicts |
|---|---|---|---|
| EvtKey (84 B) | 207 (7 common to every key + 200 in 63 variants) | 161 | +16 is `cmd` (u8) in the seeds, but a u16 / f32 / s8 field per unit type; +12 / +14 are edited as u16 (seeds: 1 byte, the player's reads) |
| EvtKeyExtra (48 B) | 9 | 9 | new record (SLIGHT light) |
| EvtUnit (156 B) | 6 | 1 (+52) | +32 OFFSET vs `hold`; +34 / +36 per-type meanings vs `cam_mode` / `cam_target` |
| EvtWork (2448 B) | 21 | 4 | +70 FBN NO / +72 ENV NO vs `field_arg70 / 72`; +69 USE COUNTER NO vs `comu_index`; +12 SET TOTAL FRAME vs `field12`; +76 bit 2 BATTLE BLUR vs "fade to the field" |
| FbnNpcRecord (112 B) | 6 | 2 (+96, +100) | +96 SHADOW TYPE vs field4.h "resource kind (v1.1; 3 before)" |
| FbnPosRecord (96 B) | 1 | 0 | — |
| FieldEditorNpcWork | 12 | 12 | new (no anchor) |
| DbgListBoxItemDesc (32 B) | 8 | 8 | new record, anchored on `sub_1A3DC0` arg 1 |
| DbgListBoxItem (556 B) | 6 | 0 | — |
| FxKobj10Kind9 (264 B) | 7 | 7 | new (no labels, no anchor) |
| DbgPrintNode / DbgShapePoint / DbgShapeCylinder | 11 | 11 | new (header-documented, not seeded) |

**Not conflicts but unions.** The recovered EvtKey class merges every unit type's view of +16..+55, so it reports one width set per offset (for example +28 width 4 because SLIGHT / TMX / P3EFF read floats there, while KOMA and RAN-JUMP read halfwords). 27 per-variant widths are absent from the merged class's width set and 22 variants give +16 a width other than the seeds' 1-byte `cmd`; they are the variant table's reason to exist, not errors. The types delta therefore adds only offsets with a single meaning.

**Conflicts with the headers worth a slice's attention** (the doc's evidence, nothing was changed):

1. `events.h` kHold (EvtUnit+32): the developers' label is OFFSET and the key list adds it to the key frame.
2. `events.h` work kMode bit 2 "fade to the field on exit": the settings menu labels bit 2 BATTLE BLUR ("BATTLE BLUR USE?"); the play step also tests bit 2 in its play-mode skip block (L1 + R1 held), so both readings may hold — check `sub_36E690`'s use.
3. `field4.h` FBN +96 "resource kind (v1.1; 3 before)": written from `sub_19C300(shadow)` and passed to `sub_3B6270` as the shadow type by the loader; the label SHADOW TYPE (default 3) explains the old constant.
4. `events.h` kCondType 1 "counter == value": labelled LOCAL FLAG (its number range 0..9 does fit a counter bank).
5. `events3.cpp` comment on `sub_373700` kind 4 "the model offset and rotation": the box is the SLIGHT light (AMB / DIR labels) applied with `sub_38B550` on the light model at EvtWork+528.
6. `events3.h` "MOTION CHANGE key +34..+37 u8 the second motion": +34 is TYPE (NORMAL / TABLE), the second motion is +35..+37 and +38.

**The delta** (`tools/ours/types/deltas/debug_ui.json`): EvtWork +32 / +34 / +74 / +304 / +360 / +560 / +564 / +2128 / +2132 / +2136 / +2141..+2143, EvtUnit +52, EvtKey +48 (func_curve), FbnNpcRecord +96 shadow_type / +100 shadow_radius, and the new DbgListBoxItemDesc (8 fields). `types_build.py` with the gate-test `p3fes_types.exe`: 377 records, 3,386 known fields, **2,541 found (was 2,525), 7 conflicting (was 7)**. The renames suggested in the table above are left to the owning slices (a delta field at an existing offset would also be shadowed by the alphabetically later `events*.json`).

## 7. Gaps and oddities in the shipped editor (obs)

* Slots 0, 12, 18–22 of `0x6A0270` are empty. **Menu 12** is still pushed by the MG1 / MG2 DAT column and **menu 21** by the TMX column; `sub_385860` returns 0 for a null slot, so the editor would sit on a menu that never reads the pad (inf). A placeholder `sub_385BA0` ("this is new menu func lid=%d", 6 data references) is not in the table.
* **Menu 24** (CONTROL CAMERA MENU) has a complete update / header / row / action but no push site in any readable body or in the decompiler output: orphaned. The CTL CAM key is edited through MODE / CAM / UNIQ PARAM instead.
* HBLUR's HOKAN column is drawn but the key menu's opener does not load its value (the opener's list lacks type 27).
* CHANGE ROT edits ROT X but the action stores only ROT Y (+20) and the length (+36).
* Tool kinds 1, 5 and 18 of menu 26 have appliers without openers.

## 8. Re-enabling the tools inside our editor, and what is missing

What our runtime would need to run the original tools in place (none of this was done here):

1. **Clear kFlagPlayMode.** A runtime hook on the viewer's first update (`sub_36F370` path) or on `sub_36E690` that clears EvtWork+4 bit 3 for an event the editor opened; R2 then enters `sub_36D5F0`. This needs no game-code change if done as a guest-memory write from the editor process, but the bit is re-read every frame, so it has to stay cleared.
2. **Pad input.** The editor reads the logical pad words 0x7E094C / 0x7E094E / 0x7E0952 and the sticks 0x7E095E..0x7E0961; the effect editor reads 0x7E0982. Our editor would inject these (the declined "input capture" tool is not required: the words can be written per frame).
3. **The debug font and print layer.** `dbgPrintInit` loads `font/size12/f11_001.tmx`; the queue is drawn by `dbgPrintDrawScreen` / `dbgPrintDrawStrings` (draw_layer.h); whether those draw calls are live in the retail frame was not checked here, so the editor's text may need them enabled too.
4. **Saving.** The project save writes PM files with mode "wb" (`sub_4C0240`) and the field editor builds an FBN image for a writer called through a function pointer; our runtime needs a writable host device for both, or our editor saves from guest memory itself (the records are documented).
5. **Missing pieces.** The empty menus 12 / 21 (MG and TMX resource editors), the orphaned menu 24, no labels for the effect editor, and the PM load / save paths depend on `E%3d_%03d.PM1/PM2/PM3` files that only exist inside the event packs.

The better reuse is data, not code: `debug_fields.json` gives the native editor (ADR-0015) the developer labels, ranges, steps, enums and variant selection for events, units, keys, FBN NPCs and positions, so its Inspector can present the same fields the Atlus tools did — with ranges enforced and the FBN / PM layouts written by our own code.

## 9. The JSON and the checker

`debug_fields.json` (schema `p3fes-debug-fields/1`):

* `records.<Name>`: `size`, `types_record` (the seeds name, or null), `doc`, `fields`, and for EvtKey / EvtKeyExtra `variants.<id>` = {`unit_types`, `unit_type_names`, optional `cmd` (EvtKey+16), `fields`}. A variant `X/Y` extends `X`. Each field: `off`, `size`, `type`, `name`, `label` (+ `label_addr`, `label_raw` when the string has padding), optional `unit`, `min`, `max`, `step` ([left/right, L1/R1, L2/R2]), `default`, `wrap`, `format`, `enum` ({values, addr | addrs | per_type}), `subfields` (bit ranges), `menu`, `note`, and `evidence`.
* `event_editor`: the menu / action tables, `key_columns` (30 kinds, the column list of every unit type), `unit_columns`, `menus` (41, each row with `target` "Record[variant]+off" and `via` = the EvtWork edit slot), `choice_lists` (33), `tools_menu26` (19 kinds).
* `list_boxes`: the 20 descriptor tables, each row with label, kind, value, min, max and the field it `writes`.
* `globals`: the event number pair, the bezier path, the function curves, the free-camera saves, the effect editor's pad word.

`python -I tools/ours/debug_ui/check_debug_fields.py` validates the schema and every evidence item: a readable body must contain a load / store at the field's offset with the field's width (symbolic offsets resolved from the game headers), a header line must contain the cited text and the offset, an `elf_fn` function must contain such an access in the ELF; with the ELF it also compares every label, enum string, choice item, unit-type name, menu-table entry and descriptor row with the binary, and resolves every menu-row / list-box cross-reference to a field. Current run: 13 records, 64 variants, 294 fields; 262 body accesses, 18 header lines, 15 ELF accesses, 521 labels, 346 enum / item strings, 65 descriptor rows, 179 cross-references — OK. The body check proves that the cited function touches that offset with that width; that the base register holds the record is the slice's reading (events2 / events3 comments), not something the checker can see.
