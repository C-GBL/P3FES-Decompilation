// The game-side draw layer (docs/ANALYSIS/22_rendering.md sections 1, 2 and 6): the kwln draw tasks that open and
// close a camera pass, clear Z and set the pass's render states, and the game functions that build screen-space
// RwIm2DVertex quads and hand them to RenderWare's Im2D device pointers (cursor, screen fades, debug rectangles,
// the day HUD's moon). Hand-decompiled from SLUS_216.21 (game/src/render/draw_layer.cpp); every RenderWare call
// stays a call into the recompiled RW band (or through its device pointers), exactly where the original made it.
//
// Names: the IDA name (since master update #4 the names of symbols/deltas/render_game.sym, or rendering.sym for the
// passes 22_rendering.md named; a few `sub_*` remain).
#pragma once

#include "p3fes/game/guest.h"
#include "p3fes/game/task.h"

#include <cstddef>

namespace p3fes::game {

namespace draw {

// --- RenderWare device globals the draw code reads (symbols/p3fes.sym) ---------------------------------------
constexpr u32 kIm2DNearScreenZ = 0x960088u;                // g_rwIm2DNearScreenZ: z of a vertex on the near plane
constexpr u32 kPfnRenderStateSet = 0x960090u;              // RwRenderStateSet(state, value)
constexpr u32 kPfnRenderStateGet = 0x960094u;              // RwRenderStateGet(state, &value)
constexpr u32 kPfnIm2DRenderTriangle = 0x96009Cu;          // RwIm2DRenderTriangle(verts, n, i0, i1, i2)
constexpr u32 kPfnIm2DRenderPrimitive = 0x9600A0u;         // RwIm2DRenderPrimitive(prim, verts, n)
constexpr u32 kPfnIm2DRenderIndexedPrimitive = 0x9600A4u;  // RwIm2DRenderIndexedPrimitive(prim, verts, n, idx, ni)

// RwRenderState (RenderWare 3.x numbering, the values the draw code passes).
enum RwRenderState : u32 {
    rwRENDERSTATETEXTURERASTER = 1,
    rwRENDERSTATETEXTUREADDRESS = 2,
    rwRENDERSTATEZTESTENABLE = 6,
    rwRENDERSTATESHADEMODE = 7,
    rwRENDERSTATEZWRITEENABLE = 8,
    rwRENDERSTATETEXTUREFILTER = 9,
    rwRENDERSTATESRCBLEND = 10,
    rwRENDERSTATEDESTBLEND = 11,
    rwRENDERSTATEVERTEXALPHAENABLE = 12,
    rwRENDERSTATEFOGENABLE = 14,
    rwRENDERSTATEFOGCOLOR = 15,
    rwRENDERSTATEFOGTYPE = 16,
};
// Values: rwSHADEMODEGOURAUD 2, rwFILTERLINEAR 2, rwBLENDSRCALPHA 5, rwBLENDINVSRCALPHA 6, rwBLENDONE 2,
// rwTEXTUREADDRESSCLAMP 3, rwTEXTUREADDRESSWRAP 1... (as passed); rwFOGTYPELINEAR 1.
// RwPrimitiveType: 2 polyline, 3 tri list, 4 tri strip, 5 tri fan.
constexpr u32 rwPRIMTYPEPOLYLINE = 2, rwPRIMTYPETRILIST = 3, rwPRIMTYPETRISTRIP = 4;

// RwCamera fields the draw code reads.
constexpr u32 kCameraBeginUpdate = 0x18;  // RwCameraBeginUpdate jumps through it
constexpr u32 kCameraNearPlane = 0x80;    // every screen vertex gets recipZ = 1 / nearPlane

// The PS2 RwIm2DVertex (64 bytes; RwIm2DVertexSet* writes these fields).
struct Im2DVertex {
    f32 x, y, z;    // +0x00 screen position, z = near screen z (minus a depth offset)
    u32 pad0c;      // +0x0C never written by the game
    f32 u, v;       // +0x10 texture coordinates
    f32 recip_z;    // +0x18 1 / camera near plane
    u32 pad1c;      // +0x1C
    f32 r, g, b, a; // +0x20 colour, 0..255 as floats
    u32 pad30[4];   // +0x30
};
static_assert(sizeof(Im2DVertex) == 64);
constexpr u32 kVtxX = 0x00, kVtxY = 0x04, kVtxZ = 0x08, kVtxU = 0x10, kVtxV = 0x14, kVtxRecipZ = 0x18, kVtxR = 0x20,
              kVtxG = 0x24, kVtxB = 0x28, kVtxA = 0x2C, kVtxSize = 0x40;
static_assert(offsetof(Im2DVertex, recip_z) == kVtxRecipZ && offsetof(Im2DVertex, a) == kVtxA);

// --- kwlnRoot.c globals ($gp-relative; gp = 0x7D2CF0 in retail) ------------------------------------------------
constexpr s32 kGpRootCamera = -19504;    // 0x7CE0C0: the main camera (sub_198590 returns it)
constexpr s32 kGpClearColour = -19400;   // 0x7CE128: the RwRGBA the Z clears pass (sub_1985A0 returns its address)
constexpr s32 kGpFogEnabled = -19484;    // 0x7CE0D4: 1 = the pass ends with the fog states below
constexpr s32 kGpFogRed = -19480;        // 0x7CE0D8 (low byte of each word)
constexpr s32 kGpFogGreen = -19476;
constexpr s32 kGpFogBlue = -19472;
constexpr s32 kGpFogAlpha = -19468;
// The screen fade (kwln "fade" task, sub_107060 and the three fade draws).
constexpr s32 kGpFadeState = -19956;     // s16: 0 start, 2 fading in, 3 held, 4 kill tasks and fade out, 5 fading out
constexpr s32 kGpFadeDuration = -19952;  // s16: frames
constexpr s32 kGpFadeCounter = -19948;   // s16: frames done, alpha = 255 * counter / duration
constexpr s32 kGpFadeActive = -19996;    // cleared when a fade-out reaches 0
constexpr s32 kGpFadeTaskA = -19992;     // tasks destroyed with their hierarchy when the fade goes to 3 / 4
constexpr s32 kGpFadeTaskB = -19988;
constexpr s32 kGpFadeColourR = -19960;   // u8 colour of the coloured fade (H_Fade_DrawColour)
constexpr s32 kGpFadeColourG = -19964;
constexpr s32 kGpFadeColourB = -19968;

}  // namespace draw

// --- camera passes (kwln root / pipe / battle draw tasks; each returns 0 = keep running) ------------------------
u32 kwlnRootUpdate2DDrawEndTask(EEContext& ctx);  // 0x198B20 "2D Draw End": RwCameraEndUpdate(main camera)
u32 kwlnRootUpdate3DOn2DZClearTask(EEContext& ctx);  // [kwlnRootUpdate3DOn2DZClearTask] "3D on 2D Zclear": RwCameraClear(cam, &colour, Z)
u32 kwlnRootUpdate3DOn2DDrawBeginTask(EEContext& ctx);  // [kwlnRootUpdate3DOn2DDrawBeginTask] BeginUpdate, kwln flags, Z test/write on
u32 kwlnRootUpdate3DOn2DDrawEndTask(EEContext& ctx);  // [kwlnRootUpdate3DOn2DDrawEndTask] fog states when enabled, EndUpdate
u32 kwlnRootUpdateEtcDrawBeginTask(EEContext& ctx);  // [kwlnRootUpdateEtcDrawBeginTask] Z clear, BeginUpdate, Z test/write on, fog off
u32 kwlnRootUpdateDrawEndTask(EEContext& ctx);  // 0x198FD0 Draw End: fog states when enabled, EndUpdate
u32 K_SPipe_Update3DDrwBeginTask(EEContext& ctx);  // [K_SPipe_Update3DDrwBeginTask] "3D Draw Begin": BeginUpdate, Z on, band check
u32 K_SPipe_Update3DDrwEndTask(EEContext& ctx);  // [K_SPipe_Update3DDrwEndTask] "3D Draw End": fog states, EndUpdate, flags
u32 kwlnRootUpdateShadowNodeCameraTask(EEContext& ctx);  // [kwlnRootUpdateShadowNodeCameraTask] "Shadow Node Camera": clear + shadow camera
u32 btlDrawMessagePass(EEContext& ctx);  // [btlDrawMessagePass] battle text pass: fog off around sub_27A3B0
u32 btlUpdateDraw3DTask(EEContext& ctx);  // [btlUpdateDraw3DTask] "battle draw 3d": effects, draw list, models
void H_MoonIcon_UpdateTask(EEContext& ctx);  // [register ABI] [H_MoonIcon_UpdateTask] the HUD moon icon: its pass, fade in / out

// --- Im2D builders ------------------------------------------------------------------------------------------
void H_Cursor_UpdateDrawTask(EEContext& ctx);  // [register ABI] 0x100230 the menu cursor quad (HCursorWork, ui.h)
void H_Fade_DrawBlue(EEContext& ctx);  // [H_Fade_DrawBlue] full-screen fade quad in (15, 31, 40), the fade state machine
void H_Fade_DrawWhite(EEContext& ctx);  // [H_Fade_DrawWhite] full-screen fade quad in (255, 255, 255)
void H_Fade_DrawColour(EEContext& ctx);  // [H_Fade_DrawColour] full-screen fade quad in the colour bytes at $gp-19960..
// Two textured 512 x 1024 strips at {x, y} (the packed floats of $a1), alpha $a2, z offset $f12; the pointer and
// alpha registers are copied whole into s-registers, so they are taken as the 64-bit register values.
void sub_126710(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
void dbgDrawRect(EEContext& ctx);  // [register ABI] [dbgDrawRect] red 512x512 outline when obj+1648 is set
void drawIm2DIndexedTriList(EEContext& ctx);  // [register ABI] [drawIm2DIndexedTriList] a {verts, idx, .., nverts, nidx} record
void sub_269F50(EEContext& ctx);  // battle panel: Z off, filter, raster of sub_266E50, two indexed triangles
// [btlDrawTexturedQuad] coloured textured quad, x/y/w/h/u/v in $f12..$f17, rgba and raster copied whole into s-regs.
void btlDrawTexturedQuad(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
void sub_422670(EEContext& ctx);  // [register ABI] a cursor-style quad task (work header +0..+15, vertices at +16)
void drawGradientQuad(EEContext& ctx);  // [register ABI] [drawGradientQuad] corners/z/recipZ in $f12..$f17
// 0x3B38F0 one text glyph as a textured quad (x in 1/16 px, y in 1/8 px, the font context, the text code, glyph
// width / height in px, rgba (r << 24 .. a), $f12 z offset); the 64-bit registers are copied whole into s-regs.
void frFontRasterDrawGlyph(EEContext& ctx);  // register ABI: arguments in $a0.., the result in $v0
void dbgPrintDrawScreen(EEContext& ctx);  // [dbgPrintDrawScreen] the 40 x 53 debug text grid at 0x7E1E30, then the overlays
void dbgPrintDrawStrings(EEContext& ctx);  // [dbgPrintDrawStrings] the positioned debug strings (list at gp-20008)
void dbgPrintDrawWindow(EEContext& ctx);  // [dbgPrintDrawWindow] the debug window: grey panel + lines of 0x7E0A30
// [H_MoonIcon_Draw] the HUD moon icon quad: rotated by angle_x, turned by angle_y (degrees), alpha.
void H_MoonIcon_Draw(EEContext& ctx, u64 angle_x, u64 angle_y, u64 alpha);

}  // namespace p3fes::game
