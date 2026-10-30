// Phase 5 slice field7, part 1 (game/src/field/field7_lbox.cpp): the debug widgets of the 0x1A2200-0x1A4CA0 band --
// the "ksk window" frame, the "ksk list box" of k_lbox.c with its items, the "color box", and the update / destroy
// pairs of the camera's debug point and cylinder tasks. Register-ABI bodies (arguments in $a0.., result in $v0);
// names are functions.json's, proposed names in brackets (ADR-0009: from this slice's own reading of the instructions,
// the strings and the callers -- the event editor sub_1E1850 / sub_1E3F10 / sub_1E4BC0 / sub_1E58D0 / sub_1E60B0 and the
// effect editor sub_3407E0 build their menus with these).
//
// A list box (68-byte work, task +60) keeps a doubly linked list of 556-byte items: id, kind (0 plain label, 1 string,
// 2 flag, 3 int, 4 float), the label, a string value, the int / float value with its range, a hex flag. Setting a
// value turns a plain item into its kind once (later setters on the same item do nothing). Every change re-lays the
// box out (sub_1A3C30): width = 12 px per character of the widest "label value" line + 4, height = 12 px per visible
// row + 4, and the window's rect follows (sub_1A23E0). The update sub_1A2A80 (cursor, value editing with the pad, the
// window) and the destroy sub_1A3A60 stay recompiled: sub_1A2A80 calls sub_1A2720 (soft-float double formatting,
// fptodp) and the stood-in getter sub_1A4510; sub_1A3A60 calls the RW destroy sub_494CC0. The window's update
// sub_1A1550 / destroy sub_1A2170 likewise (they call the stood-in sub_1A4600 / sub_494CC0).
#pragma once

#include "p3fes/ee_context.h"

namespace p3fes::game {

namespace f7::lbox {
inline constexpr int kTaskWork = 60;      // kwln task +60: the work block
// "ksk window" work (84 bytes)
inline constexpr int kWinState = 0;       // 0 build, 1..4 borders grow, 5 fade in, 6 open, 7 fade out, 8 done (-1)
inline constexpr int kWinVisible = 4;     // drawn when 1 (and the kwln 2-D band is on)
inline constexpr int kWinRect = 12;       // int x, y, w, h
inline constexpr int kWinFrameRgba = 28;  // the border colour
inline constexpr int kWinFillRgba = 32;   // the background colour (alpha +35 fades in)
inline constexpr int kWinClump = 36;      // the window's 2-D object: +24 geometry
inline constexpr int kWinBufSize = 68;    // (x / 8) * (y / 8) + 32
inline constexpr int kWinBuf = 72;        // a scratch buffer of that size
inline constexpr int kWinBufCur = 76;     // = kWinBuf at creation
inline constexpr int kWinWorkSize = 84;
// "ksk list box" work (68 bytes)
inline constexpr int kBoxWord4 = 4;
inline constexpr int kBoxStyle = 8;       // the frame colours sub_1A2A80 picks (1..3)
inline constexpr int kBoxX = 16;          // x, y, w, h: the window rect sub_1A23E0 takes
inline constexpr int kBoxY = 20;
inline constexpr int kBoxW = 24;
inline constexpr int kBoxH = 28;
inline constexpr int kBoxWindow = 40;     // the "ksk window" task
inline constexpr int kBoxTop = 44;        // the first visible item
inline constexpr int kBoxCursor = 48;     // the cursor row
inline constexpr int kBoxRows = 52;       // visible rows (10)
inline constexpr int kBoxCount = 56;      // items
inline constexpr int kBoxItems = 60;      // the first item
inline constexpr int kBoxNextId = 64;     // the next item's id
inline constexpr int kBoxWorkSize = 68;
// a list-box item (556 bytes)
inline constexpr int kItemId = 0;
inline constexpr int kItemKind = 4;       // 0 label, 1 string, 2 flag, 3 int, 4 float
inline constexpr int kItemLabel = 8;      // char[256]
inline constexpr int kItemText = 264;     // char[256]: the string value
inline constexpr int kItemValue = 520;    // int value (flag, int)
inline constexpr int kItemFloat = 524;    // float value
inline constexpr int kItemMin = 528;
inline constexpr int kItemMax = 532;
inline constexpr int kItemHex = 536;      // int shown in hex (two characters more)
inline constexpr int kItemWord540 = 540;
inline constexpr int kItemPrev = 548;
inline constexpr int kItemNext = 552;
inline constexpr int kItemSize = 556;
// the camera's debug point / cylinder tasks (field_big / field_lo hold their setters)
inline constexpr int kDbgOn = 0;
inline constexpr int kDbgPos = 4;         // vec3
inline constexpr int kDbgPointRgba = 16;  // the point's colour
inline constexpr int kDbgCylRadius = 16;  // the cylinder's radius (float)
inline constexpr int kDbgCylHeight = 20;  // and height
// "color box" work (12 bytes)
inline constexpr int kColorBoxTarget = 8;
inline constexpr int kColorBoxWorkSize = 12;
}  // namespace f7::lbox

void sub_1A2200(EEContext& ctx);  // [dbgKskWindowCreate](parent, rect, frame_rgba, fill_rgba) -> task / 0
void sub_1A2390(EEContext& ctx);  // [dbgKskWindowIsBusy](task) -> 1 while opening / closing, 0 in states 6 / 8
void sub_1A23D0(EEContext& ctx);  // [dbgKskWindowSetVisible](task, on)
void sub_1A23E0(EEContext& ctx);  // [dbgKskWindowSetRect](task, rect): rebuilds the geometry in state 6
void sub_1A3B10(EEContext& ctx);  // [dbgListBoxCreate](parent, x, y, style) -> task / 0
void sub_1A3BE0(EEContext& ctx);  // [dbgListBoxSetWord4](task, value)
void sub_1A3C30(EEContext& ctx);  // [dbgListBoxLayout](task)
void sub_1A3F20(EEContext& ctx);  // [dbgListBoxAddItem](task, label) -> id
void sub_1A4010(EEContext& ctx);  // [dbgListBoxGetLabel](task, id) -> label / 0
void sub_1A4050(EEContext& ctx);  // [dbgListBoxSetItemWord540](task, id, value)
void sub_1A4090(EEContext& ctx);  // [dbgListBoxSetString](task, id, text)
void sub_1A4110(EEContext& ctx);  // [dbgListBoxSetInt](task, id, value, min, max, hex)
void sub_1A41F0(EEContext& ctx);  // [dbgListBoxSetFlag](task, id, value)
void sub_1A4260(EEContext& ctx);  // [dbgListBoxSetFloat](task, id, value, min, max)
void sub_1A4380(EEContext& ctx);  // [dbgListBoxRemoveItem](task, id)
void sub_1A44A0(EEContext& ctx);  // [dbgListBoxClear](task)
void sub_1A4660(EEContext& ctx);  // [K_Draw_UpdatePointTask](task) -> 0
void sub_1A46C0(EEContext& ctx);  // [K_Draw_DestroyPointTask](task)
void sub_1A47E0(EEContext& ctx);  // [K_Draw_UpdateCylinderTask](task) -> 0
void sub_1A4830(EEContext& ctx);  // [K_Draw_DestroyCylinderTask](task)
void sub_1A4B40(EEContext& ctx);  // [dbgColorBoxDestroy](task)
void sub_1A4B70(EEContext& ctx);  // [dbgColorBoxCreate](parent, target) -> task / 0
void sub_1A4CA0(EEContext& ctx);  // [K_Draw_DestroyShapeTask](task)

}  // namespace p3fes::game
