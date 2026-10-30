// Pair tests of slice ui4 (game/src/ui/ui4.cpp): the message manager, the panels, the text-tag handlers, the font leaves
// and the spr* layer. Every pair runs the hand body and its recompiled body from the same guest machine through
// tests/game/handgen_pairs.h -- the whole register file and the cycle count at every check point and at the return / stop,
// all 32 MiB of RAM (write-tracked), the scratchpad, the BIOS window, the bus log -- and, where a body allocates, prints
// or loads files, on two identical stand-in worlds (tests/game/stand_ins.h) whose call logs must match.
//
// Inputs: the p3fes_handgen random worlds for every function; the dorm replay snapshot's message slots (the text style
// setter on every slot with text lines; the open window of slot 19 drawn, moved, its panels released, and run through the
// "DrawMsgMng" / "CalcMsgMng" updates); the font system start and the message manager start on the ELF image with the
// file and heap stand-ins; the spr* file list on the stand-in heap; the text-tag handlers on a layout record; and
// documented-rule checks after every pair (list links, the tag parameter encoding, the fields each tag sets, the pop-in
// curve, the key map, the ring-buffer layout, the panel shading formula).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/ui4.h"

#include <algorithm>
#include <array>
#include <bit>
#include <cstdio>
#include <cstring>
#include <map>
#include <cstdlib>
#include <memory>
#include <random>
#include <string>
#include <tuple>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_sub_1120C0_001120c0(EEContext&);  // generated body
void fn_sub_1120C0_001120c0__recomp(EEContext&);  // recompiled
void fn_sprAddFile_00112370(EEContext&);  // generated body
void fn_sprAddFile_00112370__recomp(EEContext&);  // recompiled
void fn_sprSpriteDrawAll_001125d0(EEContext&);  // generated body
void fn_sprSpriteDrawAll_001125d0__recomp(EEContext&);  // recompiled
void fn_sub_3A2660_003a2660(EEContext&);  // generated body
void fn_sub_3A2660_003a2660__recomp(EEContext&);  // recompiled
void fn_sub_3A2900_003a2900(EEContext&);  // generated body
void fn_sub_3A2900_003a2900__recomp(EEContext&);  // recompiled
void fn_sub_3A2970_003a2970(EEContext&);  // generated body
void fn_sub_3A2970_003a2970__recomp(EEContext&);  // recompiled
void fn_sub_3A2B30_003a2b30(EEContext&);  // generated body
void fn_sub_3A2B30_003a2b30__recomp(EEContext&);  // recompiled
void fn_sub_3A3470_003a3470(EEContext&);  // generated body
void fn_sub_3A3470_003a3470__recomp(EEContext&);  // recompiled
void fn_sub_3A4220_003a4220(EEContext&);  // generated body
void fn_sub_3A4220_003a4220__recomp(EEContext&);  // recompiled
void fn_sub_3A4CE0_003a4ce0(EEContext&);  // generated body
void fn_sub_3A4CE0_003a4ce0__recomp(EEContext&);  // recompiled
void fn_sub_3A5210_003a5210(EEContext&);  // generated body
void fn_sub_3A5210_003a5210__recomp(EEContext&);  // recompiled
void fn_sub_3A52C0_003a52c0(EEContext&);  // generated body
void fn_sub_3A52C0_003a52c0__recomp(EEContext&);  // recompiled
void fn_sub_3A5540_003a5540(EEContext&);  // generated body
void fn_sub_3A5540_003a5540__recomp(EEContext&);  // recompiled
void fn_sub_3A6060_003a6060(EEContext&);  // generated body
void fn_sub_3A6060_003a6060__recomp(EEContext&);  // recompiled
void fn_sub_3A6B00_003a6b00(EEContext&);  // generated body
void fn_sub_3A6B00_003a6b00__recomp(EEContext&);  // recompiled
void fn_sub_3A6B90_003a6b90(EEContext&);  // generated body
void fn_sub_3A6B90_003a6b90__recomp(EEContext&);  // recompiled
void fn_sub_3A7940_003a7940(EEContext&);  // generated body
void fn_sub_3A7940_003a7940__recomp(EEContext&);  // recompiled
void fn_sub_3A7CB0_003a7cb0(EEContext&);  // generated body
void fn_sub_3A7CB0_003a7cb0__recomp(EEContext&);  // recompiled
void fn_sub_3A7D60_003a7d60(EEContext&);  // generated body
void fn_sub_3A7D60_003a7d60__recomp(EEContext&);  // recompiled
void fn_sub_3A7DD0_003a7dd0(EEContext&);  // generated body
void fn_sub_3A7DD0_003a7dd0__recomp(EEContext&);  // recompiled
void fn_sub_3A8080_003a8080(EEContext&);  // generated body
void fn_sub_3A8080_003a8080__recomp(EEContext&);  // recompiled
void fn_itfMesManagerDrawSprite_003a8170(EEContext&);  // generated body
void fn_itfMesManagerDrawSprite_003a8170__recomp(EEContext&);  // recompiled
void fn_sub_3A8260_003a8260(EEContext&);  // generated body
void fn_sub_3A8260_003a8260__recomp(EEContext&);  // recompiled
void fn_sub_3A8350_003a8350(EEContext&);  // generated body
void fn_sub_3A8350_003a8350__recomp(EEContext&);  // recompiled
void fn_sub_3A8440_003a8440(EEContext&);  // generated body
void fn_sub_3A8440_003a8440__recomp(EEContext&);  // recompiled
void fn_sub_3A84C0_003a84c0(EEContext&);  // generated body
void fn_sub_3A84C0_003a84c0__recomp(EEContext&);  // recompiled
void fn_sub_3A8530_003a8530(EEContext&);  // generated body
void fn_sub_3A8530_003a8530__recomp(EEContext&);  // recompiled
void fn_sub_3A8590_003a8590(EEContext&);  // generated body
void fn_sub_3A8590_003a8590__recomp(EEContext&);  // recompiled
void fn_sub_3A8600_003a8600(EEContext&);  // generated body
void fn_sub_3A8600_003a8600__recomp(EEContext&);  // recompiled
void fn_sub_3A8650_003a8650(EEContext&);  // generated body
void fn_sub_3A8650_003a8650__recomp(EEContext&);  // recompiled
void fn_itfMesManagerDrawSpriteEx_003a8710(EEContext&);  // generated body
void fn_itfMesManagerDrawSpriteEx_003a8710__recomp(EEContext&);  // recompiled
void fn_itfPnlRelease_003a8d60(EEContext&);  // generated body
void fn_itfPnlRelease_003a8d60__recomp(EEContext&);  // recompiled
void fn_itfPnlSetPosition_003a8dc0(EEContext&);  // generated body
void fn_itfPnlSetPosition_003a8dc0__recomp(EEContext&);  // recompiled
void fn_itfPnlSetColor_003a8fb0(EEContext&);  // generated body
void fn_itfPnlSetColor_003a8fb0__recomp(EEContext&);  // recompiled
void fn_sub_3A9080_003a9080(EEContext&);  // generated body
void fn_sub_3A9080_003a9080__recomp(EEContext&);  // recompiled
void fn_sub_3A90C0_003a90c0(EEContext&);  // generated body
void fn_sub_3A90C0_003a90c0__recomp(EEContext&);  // recompiled
void fn_sub_3A9E20_003a9e20(EEContext&);  // generated body
void fn_sub_3A9E20_003a9e20__recomp(EEContext&);  // recompiled
void fn_sub_3AA280_003aa280(EEContext&);  // generated body
void fn_sub_3AA280_003aa280__recomp(EEContext&);  // recompiled
void fn_sub_3AA2D0_003aa2d0(EEContext&);  // generated body
void fn_sub_3AA2D0_003aa2d0__recomp(EEContext&);  // recompiled
void fn_sub_3AB2A0_003ab2a0(EEContext&);  // generated body
void fn_sub_3AB2A0_003ab2a0__recomp(EEContext&);  // recompiled
void fn_sub_3AC230_003ac230(EEContext&);  // generated body
void fn_sub_3AC230_003ac230__recomp(EEContext&);  // recompiled
void fn_sub_3AC500_003ac500(EEContext&);  // generated body
void fn_sub_3AC500_003ac500__recomp(EEContext&);  // recompiled
void fn_sub_3AC590_003ac590(EEContext&);  // generated body
void fn_sub_3AC590_003ac590__recomp(EEContext&);  // recompiled
void fn_sub_3AC5A0_003ac5a0(EEContext&);  // generated body
void fn_sub_3AC5A0_003ac5a0__recomp(EEContext&);  // recompiled
void fn_sub_3AC600_003ac600(EEContext&);  // generated body
void fn_sub_3AC600_003ac600__recomp(EEContext&);  // recompiled
void fn_sub_3AC6C0_003ac6c0(EEContext&);  // generated body
void fn_sub_3AC6C0_003ac6c0__recomp(EEContext&);  // recompiled
void fn_sub_3AC6E0_003ac6e0(EEContext&);  // generated body
void fn_sub_3AC6E0_003ac6e0__recomp(EEContext&);  // recompiled
void fn_sub_3AC6F0_003ac6f0(EEContext&);  // generated body
void fn_sub_3AC6F0_003ac6f0__recomp(EEContext&);  // recompiled
void fn_sub_3AC750_003ac750(EEContext&);  // generated body
void fn_sub_3AC750_003ac750__recomp(EEContext&);  // recompiled
void fn_sub_3AC7B0_003ac7b0(EEContext&);  // generated body
void fn_sub_3AC7B0_003ac7b0__recomp(EEContext&);  // recompiled
void fn_sub_3AC7C0_003ac7c0(EEContext&);  // generated body
void fn_sub_3AC7C0_003ac7c0__recomp(EEContext&);  // recompiled
void fn_sub_3AC820_003ac820(EEContext&);  // generated body
void fn_sub_3AC820_003ac820__recomp(EEContext&);  // recompiled
void fn_sub_3AC890_003ac890(EEContext&);  // generated body
void fn_sub_3AC890_003ac890__recomp(EEContext&);  // recompiled
void fn_sub_3ACA30_003aca30(EEContext&);  // generated body
void fn_sub_3ACA30_003aca30__recomp(EEContext&);  // recompiled
void fn_sub_3ACA40_003aca40(EEContext&);  // generated body
void fn_sub_3ACA40_003aca40__recomp(EEContext&);  // recompiled
void fn_sub_3ACA50_003aca50(EEContext&);  // generated body
void fn_sub_3ACA50_003aca50__recomp(EEContext&);  // recompiled
void fn_sub_3ACA90_003aca90(EEContext&);  // generated body
void fn_sub_3ACA90_003aca90__recomp(EEContext&);  // recompiled
void fn_sub_3ACAB0_003acab0(EEContext&);  // generated body
void fn_sub_3ACAB0_003acab0__recomp(EEContext&);  // recompiled
void fn_sub_3ACB10_003acb10(EEContext&);  // generated body
void fn_sub_3ACB10_003acb10__recomp(EEContext&);  // recompiled
void fn_sub_3ACDA0_003acda0(EEContext&);  // generated body
void fn_sub_3ACDA0_003acda0__recomp(EEContext&);  // recompiled
void fn_sub_3ACF80_003acf80(EEContext&);  // generated body
void fn_sub_3ACF80_003acf80__recomp(EEContext&);  // recompiled
void fn_sub_3AD030_003ad030(EEContext&);  // generated body
void fn_sub_3AD030_003ad030__recomp(EEContext&);  // recompiled
void fn_sub_3AD130_003ad130(EEContext&);  // generated body
void fn_sub_3AD130_003ad130__recomp(EEContext&);  // recompiled
void fn_sub_3AD1B0_003ad1b0(EEContext&);  // generated body
void fn_sub_3AD1B0_003ad1b0__recomp(EEContext&);  // recompiled
void fn_sub_3AD2A0_003ad2a0(EEContext&);  // generated body
void fn_sub_3AD2A0_003ad2a0__recomp(EEContext&);  // recompiled
void fn_sub_3AD360_003ad360(EEContext&);  // generated body
void fn_sub_3AD360_003ad360__recomp(EEContext&);  // recompiled
void fn_sub_3AD380_003ad380(EEContext&);  // generated body
void fn_sub_3AD380_003ad380__recomp(EEContext&);  // recompiled
void fn_sub_3AD640_003ad640(EEContext&);  // generated body
void fn_sub_3AD640_003ad640__recomp(EEContext&);  // recompiled
void fn_sub_3AD860_003ad860(EEContext&);  // generated body
void fn_sub_3AD860_003ad860__recomp(EEContext&);  // recompiled
void fn_sub_3AD930_003ad930(EEContext&);  // generated body
void fn_sub_3AD930_003ad930__recomp(EEContext&);  // recompiled
void fn_sub_3ADA00_003ada00(EEContext&);  // generated body
void fn_sub_3ADA00_003ada00__recomp(EEContext&);  // recompiled
void fn_sub_3ADB00_003adb00(EEContext&);  // generated body
void fn_sub_3ADB00_003adb00__recomp(EEContext&);  // recompiled
void fn_sub_3ADD00_003add00(EEContext&);  // generated body
void fn_sub_3ADD00_003add00__recomp(EEContext&);  // recompiled
void fn_sub_3ADD30_003add30(EEContext&);  // generated body
void fn_sub_3ADD30_003add30__recomp(EEContext&);  // recompiled
void fn_sub_3ADE60_003ade60(EEContext&);  // generated body
void fn_sub_3ADE60_003ade60__recomp(EEContext&);  // recompiled
void fn_sub_3ADE70_003ade70(EEContext&);  // generated body
void fn_sub_3ADE70_003ade70__recomp(EEContext&);  // recompiled
void fn_sub_3ADF40_003adf40(EEContext&);  // generated body
void fn_sub_3ADF40_003adf40__recomp(EEContext&);  // recompiled
void fn_sub_3ADF50_003adf50(EEContext&);  // generated body
void fn_sub_3ADF50_003adf50__recomp(EEContext&);  // recompiled
void fn_sub_3ADF60_003adf60(EEContext&);  // generated body
void fn_sub_3ADF60_003adf60__recomp(EEContext&);  // recompiled
void fn_sub_3ADF70_003adf70(EEContext&);  // generated body
void fn_sub_3ADF70_003adf70__recomp(EEContext&);  // recompiled
void fn_sub_3AE140_003ae140(EEContext&);  // generated body
void fn_sub_3AE140_003ae140__recomp(EEContext&);  // recompiled
void fn_sub_3AE150_003ae150(EEContext&);  // generated body
void fn_sub_3AE150_003ae150__recomp(EEContext&);  // recompiled
void fn_sub_3AE160_003ae160(EEContext&);  // generated body
void fn_sub_3AE160_003ae160__recomp(EEContext&);  // recompiled
void fn_sub_3AE260_003ae260(EEContext&);  // generated body
void fn_sub_3AE260_003ae260__recomp(EEContext&);  // recompiled
void fn_sub_3AE360_003ae360(EEContext&);  // generated body
void fn_sub_3AE360_003ae360__recomp(EEContext&);  // recompiled
void fn_sub_3AE560_003ae560(EEContext&);  // generated body
void fn_sub_3AE560_003ae560__recomp(EEContext&);  // recompiled
void fn_sub_3AE650_003ae650(EEContext&);  // generated body
void fn_sub_3AE650_003ae650__recomp(EEContext&);  // recompiled
void fn_sub_3AE750_003ae750(EEContext&);  // generated body
void fn_sub_3AE750_003ae750__recomp(EEContext&);  // recompiled
void fn_sub_3AE820_003ae820(EEContext&);  // generated body
void fn_sub_3AE820_003ae820__recomp(EEContext&);  // recompiled
void fn_sub_3AE840_003ae840(EEContext&);  // generated body
void fn_sub_3AE840_003ae840__recomp(EEContext&);  // recompiled
void fn_sub_3AE850_003ae850(EEContext&);  // generated body
void fn_sub_3AE850_003ae850__recomp(EEContext&);  // recompiled
void fn_sub_3AE860_003ae860(EEContext&);  // generated body
void fn_sub_3AE860_003ae860__recomp(EEContext&);  // recompiled
void fn_sub_3AE870_003ae870(EEContext&);  // generated body
void fn_sub_3AE870_003ae870__recomp(EEContext&);  // recompiled
void fn_sub_3AE8D0_003ae8d0(EEContext&);  // generated body
void fn_sub_3AE8D0_003ae8d0__recomp(EEContext&);  // recompiled
void fn_sub_3AE930_003ae930(EEContext&);  // generated body
void fn_sub_3AE930_003ae930__recomp(EEContext&);  // recompiled
void fn_sub_3AE970_003ae970(EEContext&);  // generated body
void fn_sub_3AE970_003ae970__recomp(EEContext&);  // recompiled
void fn_sub_3AE9B0_003ae9b0(EEContext&);  // generated body
void fn_sub_3AE9B0_003ae9b0__recomp(EEContext&);  // recompiled
void fn_sub_3AEC20_003aec20(EEContext&);  // generated body
void fn_sub_3AEC20_003aec20__recomp(EEContext&);  // recompiled
void fn_sub_3AED10_003aed10(EEContext&);  // generated body
void fn_sub_3AED10_003aed10__recomp(EEContext&);  // recompiled
void fn_sub_3AEE00_003aee00(EEContext&);  // generated body
void fn_sub_3AEE00_003aee00__recomp(EEContext&);  // recompiled
void fn_sub_3AF520_003af520(EEContext&);  // generated body
void fn_sub_3AF520_003af520__recomp(EEContext&);  // recompiled
void fn_sub_3AF560_003af560(EEContext&);  // generated body
void fn_sub_3AF560_003af560__recomp(EEContext&);  // recompiled
void fn_frLoadFontData_Ptr_003af770(EEContext&);  // generated body
void fn_frLoadFontData_Ptr_003af770__recomp(EEContext&);  // recompiled
void fn_sub_3AFA40_003afa40(EEContext&);  // generated body
void fn_sub_3AFA40_003afa40__recomp(EEContext&);  // recompiled
void fn_sub_3AFC30_003afc30(EEContext&);  // generated body
void fn_sub_3AFC30_003afc30__recomp(EEContext&);  // recompiled
void fn_frFontPrintClutData_003aff50(EEContext&);  // generated body
void fn_frFontPrintClutData_003aff50__recomp(EEContext&);  // recompiled
void fn_sub_3AFFD0_003affd0(EEContext&);  // generated body
void fn_sub_3AFFD0_003affd0__recomp(EEContext&);  // recompiled
void fn_sub_3B0170_003b0170(EEContext&);  // generated body
void fn_sub_3B0170_003b0170__recomp(EEContext&);  // recompiled
void fn_frFontRegisterGlyphRaster_003b03a0(EEContext&);  // generated body
void fn_frFontRegisterGlyphRaster_003b03a0__recomp(EEContext&);  // recompiled
void fn_sub_3B1300_003b1300(EEContext&);  // generated body
void fn_sub_3B1300_003b1300__recomp(EEContext&);  // recompiled
void fn_sub_3B1330_003b1330(EEContext&);  // generated body
void fn_sub_3B1330_003b1330__recomp(EEContext&);  // recompiled
void fn_sub_3B18C0_003b18c0(EEContext&);  // generated body
void fn_sub_3B18C0_003b18c0__recomp(EEContext&);  // recompiled
void fn_frSetMessageFontStyle_003b19a0(EEContext&);  // generated body
void fn_frSetMessageFontStyle_003b19a0__recomp(EEContext&);  // recompiled
void fn_sub_3B2900_003b2900(EEContext&);  // generated body
void fn_sub_3B2900_003b2900__recomp(EEContext&);  // recompiled
void fn_sub_3B2940_003b2940(EEContext&);  // generated body
void fn_sub_3B2940_003b2940__recomp(EEContext&);  // recompiled
void fn_sub_3B2990_003b2990(EEContext&);  // generated body
void fn_sub_3B2990_003b2990__recomp(EEContext&);  // recompiled
void fn_sub_3B2C60_003b2c60(EEContext&);  // generated body
void fn_sub_3B2C60_003b2c60__recomp(EEContext&);  // recompiled
void fn_sub_3B3740_003b3740(EEContext&);  // generated body
void fn_sub_3B3740_003b3740__recomp(EEContext&);  // recompiled
void fn_frFontRasterFindOrAlloc_003b3d60(EEContext&);  // generated body
void fn_frFontRasterFindOrAlloc_003b3d60__recomp(EEContext&);  // recompiled
void fn_sub_3B44A0_003b44a0(EEContext&);  // generated body
void fn_sub_3B44A0_003b44a0__recomp(EEContext&);  // recompiled
void fn_sub_3B45F0_003b45f0(EEContext&);  // generated body
void fn_sub_3B45F0_003b45f0__recomp(EEContext&);  // recompiled
void fn_sub_3B4740_003b4740(EEContext&);  // generated body
void fn_sub_3B4740_003b4740__recomp(EEContext&);  // recompiled
void fn_sub_3B4A90_003b4a90(EEContext&);  // generated body
void fn_sub_3B4A90_003b4a90__recomp(EEContext&);  // recompiled
void fn_nullsub_119_003b4e90(EEContext&);  // generated body
void fn_nullsub_119_003b4e90__recomp(EEContext&);  // recompiled
void fn_nullsub_121_003b4ea0(EEContext&);  // generated body
void fn_nullsub_121_003b4ea0__recomp(EEContext&);  // recompiled
void fn_nullsub_116_003b4eb0(EEContext&);  // generated body
void fn_nullsub_116_003b4eb0__recomp(EEContext&);  // recompiled
void fn_nullsub_117_003b4ec0(EEContext&);  // generated body
void fn_nullsub_117_003b4ec0__recomp(EEContext&);  // recompiled
void fn_nullsub_118_003b4ed0(EEContext&);  // generated body
void fn_nullsub_118_003b4ed0__recomp(EEContext&);  // recompiled
void fn_frFontSystemStart_003b4ee0(EEContext&);  // generated body
void fn_frFontSystemStart_003b4ee0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_1120C0", 0x1120C0, &recomp_gen::fn_sub_1120C0_001120c0, &recomp_gen::fn_sub_1120C0_001120c0__recomp},
    {"sprAddFile", 0x112370, &recomp_gen::fn_sprAddFile_00112370, &recomp_gen::fn_sprAddFile_00112370__recomp},
    {"sprSpriteDrawAll", 0x1125D0, &recomp_gen::fn_sprSpriteDrawAll_001125d0, &recomp_gen::fn_sprSpriteDrawAll_001125d0__recomp},
    {"sub_3A2660", 0x3A2660, &recomp_gen::fn_sub_3A2660_003a2660, &recomp_gen::fn_sub_3A2660_003a2660__recomp},
    {"sub_3A2900", 0x3A2900, &recomp_gen::fn_sub_3A2900_003a2900, &recomp_gen::fn_sub_3A2900_003a2900__recomp},
    {"sub_3A2970", 0x3A2970, &recomp_gen::fn_sub_3A2970_003a2970, &recomp_gen::fn_sub_3A2970_003a2970__recomp},
    {"sub_3A2B30", 0x3A2B30, &recomp_gen::fn_sub_3A2B30_003a2b30, &recomp_gen::fn_sub_3A2B30_003a2b30__recomp},
    {"sub_3A3470", 0x3A3470, &recomp_gen::fn_sub_3A3470_003a3470, &recomp_gen::fn_sub_3A3470_003a3470__recomp},
    {"sub_3A4220", 0x3A4220, &recomp_gen::fn_sub_3A4220_003a4220, &recomp_gen::fn_sub_3A4220_003a4220__recomp},
    {"sub_3A4CE0", 0x3A4CE0, &recomp_gen::fn_sub_3A4CE0_003a4ce0, &recomp_gen::fn_sub_3A4CE0_003a4ce0__recomp},
    {"sub_3A5210", 0x3A5210, &recomp_gen::fn_sub_3A5210_003a5210, &recomp_gen::fn_sub_3A5210_003a5210__recomp},
    {"sub_3A52C0", 0x3A52C0, &recomp_gen::fn_sub_3A52C0_003a52c0, &recomp_gen::fn_sub_3A52C0_003a52c0__recomp},
    {"sub_3A5540", 0x3A5540, &recomp_gen::fn_sub_3A5540_003a5540, &recomp_gen::fn_sub_3A5540_003a5540__recomp},
    {"sub_3A6060", 0x3A6060, &recomp_gen::fn_sub_3A6060_003a6060, &recomp_gen::fn_sub_3A6060_003a6060__recomp},
    {"sub_3A6B00", 0x3A6B00, &recomp_gen::fn_sub_3A6B00_003a6b00, &recomp_gen::fn_sub_3A6B00_003a6b00__recomp},
    {"sub_3A6B90", 0x3A6B90, &recomp_gen::fn_sub_3A6B90_003a6b90, &recomp_gen::fn_sub_3A6B90_003a6b90__recomp},
    {"sub_3A7940", 0x3A7940, &recomp_gen::fn_sub_3A7940_003a7940, &recomp_gen::fn_sub_3A7940_003a7940__recomp},
    {"sub_3A7CB0", 0x3A7CB0, &recomp_gen::fn_sub_3A7CB0_003a7cb0, &recomp_gen::fn_sub_3A7CB0_003a7cb0__recomp},
    {"sub_3A7D60", 0x3A7D60, &recomp_gen::fn_sub_3A7D60_003a7d60, &recomp_gen::fn_sub_3A7D60_003a7d60__recomp},
    {"sub_3A7DD0", 0x3A7DD0, &recomp_gen::fn_sub_3A7DD0_003a7dd0, &recomp_gen::fn_sub_3A7DD0_003a7dd0__recomp},
    {"sub_3A8080", 0x3A8080, &recomp_gen::fn_sub_3A8080_003a8080, &recomp_gen::fn_sub_3A8080_003a8080__recomp},
    {"itfMesManagerDrawSprite", 0x3A8170, &recomp_gen::fn_itfMesManagerDrawSprite_003a8170, &recomp_gen::fn_itfMesManagerDrawSprite_003a8170__recomp},
    {"sub_3A8260", 0x3A8260, &recomp_gen::fn_sub_3A8260_003a8260, &recomp_gen::fn_sub_3A8260_003a8260__recomp},
    {"sub_3A8350", 0x3A8350, &recomp_gen::fn_sub_3A8350_003a8350, &recomp_gen::fn_sub_3A8350_003a8350__recomp},
    {"sub_3A8440", 0x3A8440, &recomp_gen::fn_sub_3A8440_003a8440, &recomp_gen::fn_sub_3A8440_003a8440__recomp},
    {"sub_3A84C0", 0x3A84C0, &recomp_gen::fn_sub_3A84C0_003a84c0, &recomp_gen::fn_sub_3A84C0_003a84c0__recomp},
    {"sub_3A8530", 0x3A8530, &recomp_gen::fn_sub_3A8530_003a8530, &recomp_gen::fn_sub_3A8530_003a8530__recomp},
    {"sub_3A8590", 0x3A8590, &recomp_gen::fn_sub_3A8590_003a8590, &recomp_gen::fn_sub_3A8590_003a8590__recomp},
    {"sub_3A8600", 0x3A8600, &recomp_gen::fn_sub_3A8600_003a8600, &recomp_gen::fn_sub_3A8600_003a8600__recomp},
    {"sub_3A8650", 0x3A8650, &recomp_gen::fn_sub_3A8650_003a8650, &recomp_gen::fn_sub_3A8650_003a8650__recomp},
    {"itfMesManagerDrawSpriteEx", 0x3A8710, &recomp_gen::fn_itfMesManagerDrawSpriteEx_003a8710, &recomp_gen::fn_itfMesManagerDrawSpriteEx_003a8710__recomp},
    {"itfPnlRelease", 0x3A8D60, &recomp_gen::fn_itfPnlRelease_003a8d60, &recomp_gen::fn_itfPnlRelease_003a8d60__recomp},
    {"itfPnlSetPosition", 0x3A8DC0, &recomp_gen::fn_itfPnlSetPosition_003a8dc0, &recomp_gen::fn_itfPnlSetPosition_003a8dc0__recomp},
    {"itfPnlSetColor", 0x3A8FB0, &recomp_gen::fn_itfPnlSetColor_003a8fb0, &recomp_gen::fn_itfPnlSetColor_003a8fb0__recomp},
    {"sub_3A9080", 0x3A9080, &recomp_gen::fn_sub_3A9080_003a9080, &recomp_gen::fn_sub_3A9080_003a9080__recomp},
    {"sub_3A90C0", 0x3A90C0, &recomp_gen::fn_sub_3A90C0_003a90c0, &recomp_gen::fn_sub_3A90C0_003a90c0__recomp},
    {"sub_3A9E20", 0x3A9E20, &recomp_gen::fn_sub_3A9E20_003a9e20, &recomp_gen::fn_sub_3A9E20_003a9e20__recomp},
    {"sub_3AA280", 0x3AA280, &recomp_gen::fn_sub_3AA280_003aa280, &recomp_gen::fn_sub_3AA280_003aa280__recomp},
    {"sub_3AA2D0", 0x3AA2D0, &recomp_gen::fn_sub_3AA2D0_003aa2d0, &recomp_gen::fn_sub_3AA2D0_003aa2d0__recomp},
    {"sub_3AB2A0", 0x3AB2A0, &recomp_gen::fn_sub_3AB2A0_003ab2a0, &recomp_gen::fn_sub_3AB2A0_003ab2a0__recomp},
    {"sub_3AC230", 0x3AC230, &recomp_gen::fn_sub_3AC230_003ac230, &recomp_gen::fn_sub_3AC230_003ac230__recomp},
    {"sub_3AC500", 0x3AC500, &recomp_gen::fn_sub_3AC500_003ac500, &recomp_gen::fn_sub_3AC500_003ac500__recomp},
    {"sub_3AC590", 0x3AC590, &recomp_gen::fn_sub_3AC590_003ac590, &recomp_gen::fn_sub_3AC590_003ac590__recomp},
    {"sub_3AC5A0", 0x3AC5A0, &recomp_gen::fn_sub_3AC5A0_003ac5a0, &recomp_gen::fn_sub_3AC5A0_003ac5a0__recomp},
    {"sub_3AC600", 0x3AC600, &recomp_gen::fn_sub_3AC600_003ac600, &recomp_gen::fn_sub_3AC600_003ac600__recomp},
    {"sub_3AC6C0", 0x3AC6C0, &recomp_gen::fn_sub_3AC6C0_003ac6c0, &recomp_gen::fn_sub_3AC6C0_003ac6c0__recomp},
    {"sub_3AC6E0", 0x3AC6E0, &recomp_gen::fn_sub_3AC6E0_003ac6e0, &recomp_gen::fn_sub_3AC6E0_003ac6e0__recomp},
    {"sub_3AC6F0", 0x3AC6F0, &recomp_gen::fn_sub_3AC6F0_003ac6f0, &recomp_gen::fn_sub_3AC6F0_003ac6f0__recomp},
    {"sub_3AC750", 0x3AC750, &recomp_gen::fn_sub_3AC750_003ac750, &recomp_gen::fn_sub_3AC750_003ac750__recomp},
    {"sub_3AC7B0", 0x3AC7B0, &recomp_gen::fn_sub_3AC7B0_003ac7b0, &recomp_gen::fn_sub_3AC7B0_003ac7b0__recomp},
    {"sub_3AC7C0", 0x3AC7C0, &recomp_gen::fn_sub_3AC7C0_003ac7c0, &recomp_gen::fn_sub_3AC7C0_003ac7c0__recomp},
    {"sub_3AC820", 0x3AC820, &recomp_gen::fn_sub_3AC820_003ac820, &recomp_gen::fn_sub_3AC820_003ac820__recomp},
    {"sub_3AC890", 0x3AC890, &recomp_gen::fn_sub_3AC890_003ac890, &recomp_gen::fn_sub_3AC890_003ac890__recomp},
    {"sub_3ACA30", 0x3ACA30, &recomp_gen::fn_sub_3ACA30_003aca30, &recomp_gen::fn_sub_3ACA30_003aca30__recomp},
    {"sub_3ACA40", 0x3ACA40, &recomp_gen::fn_sub_3ACA40_003aca40, &recomp_gen::fn_sub_3ACA40_003aca40__recomp},
    {"sub_3ACA50", 0x3ACA50, &recomp_gen::fn_sub_3ACA50_003aca50, &recomp_gen::fn_sub_3ACA50_003aca50__recomp},
    {"sub_3ACA90", 0x3ACA90, &recomp_gen::fn_sub_3ACA90_003aca90, &recomp_gen::fn_sub_3ACA90_003aca90__recomp},
    {"sub_3ACAB0", 0x3ACAB0, &recomp_gen::fn_sub_3ACAB0_003acab0, &recomp_gen::fn_sub_3ACAB0_003acab0__recomp},
    {"sub_3ACB10", 0x3ACB10, &recomp_gen::fn_sub_3ACB10_003acb10, &recomp_gen::fn_sub_3ACB10_003acb10__recomp},
    {"sub_3ACDA0", 0x3ACDA0, &recomp_gen::fn_sub_3ACDA0_003acda0, &recomp_gen::fn_sub_3ACDA0_003acda0__recomp},
    {"sub_3ACF80", 0x3ACF80, &recomp_gen::fn_sub_3ACF80_003acf80, &recomp_gen::fn_sub_3ACF80_003acf80__recomp},
    {"sub_3AD030", 0x3AD030, &recomp_gen::fn_sub_3AD030_003ad030, &recomp_gen::fn_sub_3AD030_003ad030__recomp},
    {"sub_3AD130", 0x3AD130, &recomp_gen::fn_sub_3AD130_003ad130, &recomp_gen::fn_sub_3AD130_003ad130__recomp},
    {"sub_3AD1B0", 0x3AD1B0, &recomp_gen::fn_sub_3AD1B0_003ad1b0, &recomp_gen::fn_sub_3AD1B0_003ad1b0__recomp},
    {"sub_3AD2A0", 0x3AD2A0, &recomp_gen::fn_sub_3AD2A0_003ad2a0, &recomp_gen::fn_sub_3AD2A0_003ad2a0__recomp},
    {"sub_3AD360", 0x3AD360, &recomp_gen::fn_sub_3AD360_003ad360, &recomp_gen::fn_sub_3AD360_003ad360__recomp},
    {"sub_3AD380", 0x3AD380, &recomp_gen::fn_sub_3AD380_003ad380, &recomp_gen::fn_sub_3AD380_003ad380__recomp},
    {"sub_3AD640", 0x3AD640, &recomp_gen::fn_sub_3AD640_003ad640, &recomp_gen::fn_sub_3AD640_003ad640__recomp},
    {"sub_3AD860", 0x3AD860, &recomp_gen::fn_sub_3AD860_003ad860, &recomp_gen::fn_sub_3AD860_003ad860__recomp},
    {"sub_3AD930", 0x3AD930, &recomp_gen::fn_sub_3AD930_003ad930, &recomp_gen::fn_sub_3AD930_003ad930__recomp},
    {"sub_3ADA00", 0x3ADA00, &recomp_gen::fn_sub_3ADA00_003ada00, &recomp_gen::fn_sub_3ADA00_003ada00__recomp},
    {"sub_3ADB00", 0x3ADB00, &recomp_gen::fn_sub_3ADB00_003adb00, &recomp_gen::fn_sub_3ADB00_003adb00__recomp},
    {"sub_3ADD00", 0x3ADD00, &recomp_gen::fn_sub_3ADD00_003add00, &recomp_gen::fn_sub_3ADD00_003add00__recomp},
    {"sub_3ADD30", 0x3ADD30, &recomp_gen::fn_sub_3ADD30_003add30, &recomp_gen::fn_sub_3ADD30_003add30__recomp},
    {"sub_3ADE60", 0x3ADE60, &recomp_gen::fn_sub_3ADE60_003ade60, &recomp_gen::fn_sub_3ADE60_003ade60__recomp},
    {"sub_3ADE70", 0x3ADE70, &recomp_gen::fn_sub_3ADE70_003ade70, &recomp_gen::fn_sub_3ADE70_003ade70__recomp},
    {"sub_3ADF40", 0x3ADF40, &recomp_gen::fn_sub_3ADF40_003adf40, &recomp_gen::fn_sub_3ADF40_003adf40__recomp},
    {"sub_3ADF50", 0x3ADF50, &recomp_gen::fn_sub_3ADF50_003adf50, &recomp_gen::fn_sub_3ADF50_003adf50__recomp},
    {"sub_3ADF60", 0x3ADF60, &recomp_gen::fn_sub_3ADF60_003adf60, &recomp_gen::fn_sub_3ADF60_003adf60__recomp},
    {"sub_3ADF70", 0x3ADF70, &recomp_gen::fn_sub_3ADF70_003adf70, &recomp_gen::fn_sub_3ADF70_003adf70__recomp},
    {"sub_3AE140", 0x3AE140, &recomp_gen::fn_sub_3AE140_003ae140, &recomp_gen::fn_sub_3AE140_003ae140__recomp},
    {"sub_3AE150", 0x3AE150, &recomp_gen::fn_sub_3AE150_003ae150, &recomp_gen::fn_sub_3AE150_003ae150__recomp},
    {"sub_3AE160", 0x3AE160, &recomp_gen::fn_sub_3AE160_003ae160, &recomp_gen::fn_sub_3AE160_003ae160__recomp},
    {"sub_3AE260", 0x3AE260, &recomp_gen::fn_sub_3AE260_003ae260, &recomp_gen::fn_sub_3AE260_003ae260__recomp},
    {"sub_3AE360", 0x3AE360, &recomp_gen::fn_sub_3AE360_003ae360, &recomp_gen::fn_sub_3AE360_003ae360__recomp},
    {"sub_3AE560", 0x3AE560, &recomp_gen::fn_sub_3AE560_003ae560, &recomp_gen::fn_sub_3AE560_003ae560__recomp},
    {"sub_3AE650", 0x3AE650, &recomp_gen::fn_sub_3AE650_003ae650, &recomp_gen::fn_sub_3AE650_003ae650__recomp},
    {"sub_3AE750", 0x3AE750, &recomp_gen::fn_sub_3AE750_003ae750, &recomp_gen::fn_sub_3AE750_003ae750__recomp},
    {"sub_3AE820", 0x3AE820, &recomp_gen::fn_sub_3AE820_003ae820, &recomp_gen::fn_sub_3AE820_003ae820__recomp},
    {"sub_3AE840", 0x3AE840, &recomp_gen::fn_sub_3AE840_003ae840, &recomp_gen::fn_sub_3AE840_003ae840__recomp},
    {"sub_3AE850", 0x3AE850, &recomp_gen::fn_sub_3AE850_003ae850, &recomp_gen::fn_sub_3AE850_003ae850__recomp},
    {"sub_3AE860", 0x3AE860, &recomp_gen::fn_sub_3AE860_003ae860, &recomp_gen::fn_sub_3AE860_003ae860__recomp},
    {"sub_3AE870", 0x3AE870, &recomp_gen::fn_sub_3AE870_003ae870, &recomp_gen::fn_sub_3AE870_003ae870__recomp},
    {"sub_3AE8D0", 0x3AE8D0, &recomp_gen::fn_sub_3AE8D0_003ae8d0, &recomp_gen::fn_sub_3AE8D0_003ae8d0__recomp},
    {"sub_3AE930", 0x3AE930, &recomp_gen::fn_sub_3AE930_003ae930, &recomp_gen::fn_sub_3AE930_003ae930__recomp},
    {"sub_3AE970", 0x3AE970, &recomp_gen::fn_sub_3AE970_003ae970, &recomp_gen::fn_sub_3AE970_003ae970__recomp},
    {"sub_3AE9B0", 0x3AE9B0, &recomp_gen::fn_sub_3AE9B0_003ae9b0, &recomp_gen::fn_sub_3AE9B0_003ae9b0__recomp},
    {"sub_3AEC20", 0x3AEC20, &recomp_gen::fn_sub_3AEC20_003aec20, &recomp_gen::fn_sub_3AEC20_003aec20__recomp},
    {"sub_3AED10", 0x3AED10, &recomp_gen::fn_sub_3AED10_003aed10, &recomp_gen::fn_sub_3AED10_003aed10__recomp},
    {"sub_3AEE00", 0x3AEE00, &recomp_gen::fn_sub_3AEE00_003aee00, &recomp_gen::fn_sub_3AEE00_003aee00__recomp},
    {"sub_3AF520", 0x3AF520, &recomp_gen::fn_sub_3AF520_003af520, &recomp_gen::fn_sub_3AF520_003af520__recomp},
    {"sub_3AF560", 0x3AF560, &recomp_gen::fn_sub_3AF560_003af560, &recomp_gen::fn_sub_3AF560_003af560__recomp},
    {"frLoadFontData_Ptr", 0x3AF770, &recomp_gen::fn_frLoadFontData_Ptr_003af770, &recomp_gen::fn_frLoadFontData_Ptr_003af770__recomp},
    {"sub_3AFA40", 0x3AFA40, &recomp_gen::fn_sub_3AFA40_003afa40, &recomp_gen::fn_sub_3AFA40_003afa40__recomp},
    {"sub_3AFC30", 0x3AFC30, &recomp_gen::fn_sub_3AFC30_003afc30, &recomp_gen::fn_sub_3AFC30_003afc30__recomp},
    {"frFontPrintClutData", 0x3AFF50, &recomp_gen::fn_frFontPrintClutData_003aff50, &recomp_gen::fn_frFontPrintClutData_003aff50__recomp},
    {"sub_3AFFD0", 0x3AFFD0, &recomp_gen::fn_sub_3AFFD0_003affd0, &recomp_gen::fn_sub_3AFFD0_003affd0__recomp},
    {"sub_3B0170", 0x3B0170, &recomp_gen::fn_sub_3B0170_003b0170, &recomp_gen::fn_sub_3B0170_003b0170__recomp},
    {"frFontRegisterGlyphRaster", 0x3B03A0, &recomp_gen::fn_frFontRegisterGlyphRaster_003b03a0, &recomp_gen::fn_frFontRegisterGlyphRaster_003b03a0__recomp},
    {"sub_3B1300", 0x3B1300, &recomp_gen::fn_sub_3B1300_003b1300, &recomp_gen::fn_sub_3B1300_003b1300__recomp},
    {"sub_3B1330", 0x3B1330, &recomp_gen::fn_sub_3B1330_003b1330, &recomp_gen::fn_sub_3B1330_003b1330__recomp},
    {"sub_3B18C0", 0x3B18C0, &recomp_gen::fn_sub_3B18C0_003b18c0, &recomp_gen::fn_sub_3B18C0_003b18c0__recomp},
    {"frSetMessageFontStyle", 0x3B19A0, &recomp_gen::fn_frSetMessageFontStyle_003b19a0, &recomp_gen::fn_frSetMessageFontStyle_003b19a0__recomp},
    {"sub_3B2900", 0x3B2900, &recomp_gen::fn_sub_3B2900_003b2900, &recomp_gen::fn_sub_3B2900_003b2900__recomp},
    {"sub_3B2940", 0x3B2940, &recomp_gen::fn_sub_3B2940_003b2940, &recomp_gen::fn_sub_3B2940_003b2940__recomp},
    {"sub_3B2990", 0x3B2990, &recomp_gen::fn_sub_3B2990_003b2990, &recomp_gen::fn_sub_3B2990_003b2990__recomp},
    {"sub_3B2C60", 0x3B2C60, &recomp_gen::fn_sub_3B2C60_003b2c60, &recomp_gen::fn_sub_3B2C60_003b2c60__recomp},
    {"sub_3B3740", 0x3B3740, &recomp_gen::fn_sub_3B3740_003b3740, &recomp_gen::fn_sub_3B3740_003b3740__recomp},
    {"frFontRasterFindOrAlloc", 0x3B3D60, &recomp_gen::fn_frFontRasterFindOrAlloc_003b3d60, &recomp_gen::fn_frFontRasterFindOrAlloc_003b3d60__recomp},
    {"sub_3B44A0", 0x3B44A0, &recomp_gen::fn_sub_3B44A0_003b44a0, &recomp_gen::fn_sub_3B44A0_003b44a0__recomp},
    {"sub_3B45F0", 0x3B45F0, &recomp_gen::fn_sub_3B45F0_003b45f0, &recomp_gen::fn_sub_3B45F0_003b45f0__recomp},
    {"sub_3B4740", 0x3B4740, &recomp_gen::fn_sub_3B4740_003b4740, &recomp_gen::fn_sub_3B4740_003b4740__recomp},
    {"sub_3B4A90", 0x3B4A90, &recomp_gen::fn_sub_3B4A90_003b4a90, &recomp_gen::fn_sub_3B4A90_003b4a90__recomp},
    {"nullsub_119", 0x3B4E90, &recomp_gen::fn_nullsub_119_003b4e90, &recomp_gen::fn_nullsub_119_003b4e90__recomp},
    {"nullsub_121", 0x3B4EA0, &recomp_gen::fn_nullsub_121_003b4ea0, &recomp_gen::fn_nullsub_121_003b4ea0__recomp},
    {"nullsub_116", 0x3B4EB0, &recomp_gen::fn_nullsub_116_003b4eb0, &recomp_gen::fn_nullsub_116_003b4eb0__recomp},
    {"nullsub_117", 0x3B4EC0, &recomp_gen::fn_nullsub_117_003b4ec0, &recomp_gen::fn_nullsub_117_003b4ec0__recomp},
    {"nullsub_118", 0x3B4ED0, &recomp_gen::fn_nullsub_118_003b4ed0, &recomp_gen::fn_nullsub_118_003b4ed0__recomp},
    {"frFontSystemStart", 0x3B4EE0, &recomp_gen::fn_frFontSystemStart_003b4ee0, &recomp_gen::fn_frFontSystemStart_003b4ee0__recomp},
};

// The random worlds of the first case: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 24;

// --- the pair runner of this file -------------------------------------------------------------------------------------
// hgp::pair (handgen_pairs.h: the whole register file and cycles at every check point and at the return / stop, all
// 32 MiB of RAM, the scratchpad, the BIOS window, the bus) through two trampolines that (a) set chosen FPRs after the
// random register file and (b) optionally give each body a fresh, identical stand-in world (stand_ins.h: the heap behind
// H_Malloc and the RW slots, printf / sprintf, the H_Cdvd layer over extracted/) whose call logs must match. The blocks a
// chain of pairs allocated stay reserved in the next worlds (`g_live`), so a chain sees one heap.
struct Tramp {
    Fn fn[2] = {};
    std::unique_ptr<StandInWorld> world[2];
    std::map<unsigned, u32> fpr;
    bool standins = false;
    std::vector<std::tuple<u32, std::string, u64>> recorders;  // not-emitted callees served by a recorder
};
Tramp g_t;
std::map<u32, u32> g_live;
int g_pairs = 0;

template <int K>
void tramp(EEContext& c) {
    for (const auto& [i, v] : g_t.fpr) c.fpr[i] = v;
    if (!g_t.standins) {
        g_t.fn[K](c);
        return;
    }
    g_t.world[K] = std::make_unique<StandInWorld>();
    for (const auto& [p, n] : g_live) g_t.world[K]->heap.reserve(p, n);
    install_standard(*g_t.world[K]);
    for (const auto& [va, name, v0] : g_t.recorders) g_t.world[K]->si.install_recorder(va, name, v0);
    StandInsScope scope(g_t.world[K]->si);
    g_t.fn[K](c);
}

const Case& by_name(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

struct Opt {
    std::map<unsigned, u64> gpr_in;  // $t0.. (arguments 5..8)
    std::map<unsigned, u32> fpr;     // $f12..
    bool standins = false;
    std::vector<std::tuple<u32, std::string, u64>> recorders;
};

hgp::Run ui_pair(Machine& m, const char* name, const Args& a, u32 seed, const char* what, const Opt& o = {}) {
    const Case& c = by_name(name);
    g_t.fn[0] = c.hand;
    g_t.fn[1] = c.recomp;
    g_t.fpr = o.fpr;
    g_t.standins = o.standins;
    g_t.recorders = o.recorders;
    HwCheck hw;
    hw.gpr_in = o.gpr_in;
    hgp::Run r = hgp::pair(m, &tramp<0>, &tramp<1>, a, seed, what, hw);
    if (o.standins && g_t.world[0] && g_t.world[1]) {
        expect_same_log(g_t.world[0]->si, g_t.world[1]->si, what);
        g_live = g_t.world[1]->heap.live();
    }
    ++g_pairs;
    if (r.stopped) MESSAGE(std::string(what) << ": both bodies stopped at " << hex64(r.stop_pc) << " (" << r.what << ")");
    return r;
}
u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
const StandIns& log_of() { return g_t.world[1]->si; }

// --- guest memory helpers ---------------------------------------------------------------------------------------------
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + (va & 0x1FFFFFFu), 4);
    return v;
}
u16 r16(const Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.mem.main_ram() + (va & 0x1FFFFFFu), 2);
    return v;
}
u8 r8(const Machine& m, u32 va) { return m.mem.main_ram()[va & 0x1FFFFFFu]; }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void wstr(Machine& m, u32 va, const std::string& s) { std::memcpy(m.at(va), s.c_str(), s.size() + 1); }
std::string gstr(const Machine& m, u32 va) { return m.str(va, 64); }
u32 fbits(float f) { return std::bit_cast<u32>(f); }

constexpr u32 kGpReg = 0x7D2CF0u;
constexpr u32 kOut = 0x01F40000u;  // free in every snapshot (stand_ins.h) and in the ELF image

bool load_snapshot(Machine& m, const char* s, std::vector<u8>* keep = nullptr) {
    std::vector<u8> snap = read_snapshot(s);
    if (snap.size() != EEMemory::kMainRamSize) return false;
    std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
    if (keep) *keep = std::move(snap);
    return true;
}
u32 slot_handle(const Machine& m, u32 slot) { return r32(m, 0x959EECu + 52u * slot); }

}  // namespace

// =====================================================================================================================
// Every body on random worlds (the p3fes_handgen skeleton; the tests below carry the real inputs)
// =====================================================================================================================
TEST_CASE("game(ui4): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    int stops = 0, pairs = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
            ++pairs;
        }
    }
    MESSAGE("random worlds: " << pairs << " pairs, " << stops << " stopped early");
}

// =====================================================================================================================
// The spr* file list on the stand-in heap (documented rules after every pair)
// =====================================================================================================================
TEST_CASE("game(ui4): spr file list on the stand-in heap") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    write_rw_slots(m);
    g_live.clear();
    const u32 kFiles = kGpReg - 0x4DB0u;
    w32(m, kFiles, 0);
    wstr(m, kOut, "facility/i_mes_win01.spr");
    wstr(m, kOut + 0x40, "camp/font/i_font01a.spr");
    wstr(m, kOut + 0x80, "camp/font/i_font02a.spr");
    Opt si;
    si.standins = true;
    u32 seed = 1;
    // sprAddFile x3: appended in order, kind 0, the path copied, RwCalloc(1, 0x1C0, 0x40000)
    u32 f[3];
    for (u32 i = 0; i < 3; ++i) {
        f[i] = static_cast<u32>(v0_of(ui_pair(m, "sprAddFile", {sx(kOut + 0x40 * i), 0, 0, 0}, seed++, "sprAddFile", si)));
        REQUIRE(f[i] != 0);
        CHECK(log_of().calls_to(kRwSlotFns[3]) == 1);
        CHECK(log_of().log.back().args[0] == 1u);
        CHECK(log_of().log.back().args[1] == 0x1C0u);
        CHECK(log_of().log.back().args[2] == 0x40000u);
        CHECK(r16(m, f[i]) == 0);
        CHECK(r32(m, f[i] + 440) == 0);
        CHECK(r32(m, f[i] + 444) == (i == 0 ? 0u : f[i - 1]));
        if (i) CHECK(r32(m, f[i - 1] + 440) == f[i]);
    }
    CHECK(r32(m, kFiles) == f[0]);
    CHECK(gstr(m, f[0] + 2) == "facility/i_mes_win01.spr");
    CHECK(gstr(m, f[2] + 2) == "camp/font/i_font02a.spr");
}

// =====================================================================================================================
// The message manager on a replay snapshot: real handles and text lines, the open window, the per-frame tasks
// =====================================================================================================================
TEST_CASE("game(ui4): message slots, the open window and the manager tasks on the dorm snapshot") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    std::vector<u8> snap;
    if (!load_snapshot(m, "dorm_replay_4900", &snap)) {
        MESSAGE("SKIP: no dorm_replay_4900 snapshot under extracted/_ours");
        return;
    }
    Opt si;
    si.standins = true;
    u32 seed = 100;
    std::vector<u32> slots;
    for (u32 s = r32(m, 0x959ED0u); s != 0 && slots.size() < 64; s = r32(m, s + 4)) slots.push_back(r32(m, s + 8));
    REQUIRE(!slots.empty());
    int styled = 0;
    // sub_3A5210 [itfMesMngSetTextStyleBySlot] on every slot with text lines: alpha and code of every line of the chain
    for (u32 slot : slots) {
        const u32 h = slot_handle(m, slot);
        const u32 line = r32(m, h + 48);
        if (line == 0) continue;
        Opt o = si;
        o.gpr_in = {{GPR_T0, 0x1234}};  // the line code
        const std::string what = "text style slot " + std::to_string(slot);
        const hgp::Run r = ui_pair(m, "sub_3A5210", {slot, 0, 2, 0x80}, seed++, what.c_str(), o);
        ++styled;
        if (r.stopped) continue;
        for (u32 l = line, n = 0; l != 0 && n < 64; l = r32(m, l + 36), ++n) CHECK(r8(m, l + 2) == 0x80);
    }
    // slot 19 holds the open dialogue of the dorm scene: its draws, then the per-frame tasks
    std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
    g_live.clear();
    const u32 h19 = slot_handle(m, 19);
    REQUIRE(h19 != 0);
    // not emitted here (other slices' tests stand them in): the sprite handle create / release and the panel move
    std::memset(m.at(kOut + 0xE00), 0, 0x40);
    si.recorders = {{0x1158B0u, "sprCreateHandle", sx(kOut + 0xE00)}, {0x115980u, "sprDestroyHandle", 0}, {0x3A8EA0u, "itfPnlMove", 0}};
    ui_pair(m, "itfMesManagerDrawSprite", {sx(h19), 0, 0, 0}, seed++, "cursor bar", si);
    ui_pair(m, "sub_3A8350", {sx(h19), 0, 0, 0}, seed++, "prompt sprite", si);
    ui_pair(m, "sub_3A8080", {sx(h19), 0, 0, 0}, seed++, "panels", si);
    ui_pair(m, "sub_3A84C0", {0, 0, 0, 0}, seed++, "DrawMsgMng", si);
    ui_pair(m, "sub_3A8440", {0, 0, 0, 0}, seed++, "CalcMsgMng", si);
    // sub_3A7940 [itfMesMngMoveWindowY]: the text y and every text line's y move by dy
    const u32 y0 = r32(m, h19 + 40), l0 = r32(m, h19 + 48);
    const u32 ly0 = l0 ? r32(m, l0 + 8) : 0;
    const hgp::Run mv = ui_pair(m, "sub_3A7940", {sx(h19), 16, 0, 0}, seed++, "move window", si);
    if (!mv.stopped) {
        CHECK(r32(m, h19 + 40) == y0 + 16);
        if (l0) CHECK(r32(m, l0 + 8) == ly0 + 16);
    }
    // sub_3A6B00 [itfMesMngReleasePanels]: the three panels gone, state bits 8-11 clear
    ui_pair(m, "sub_3A6B00", {sx(h19), 0, 0, 0}, seed++, "release panels", si);
    CHECK(r32(m, h19 + 168) == 0);
    CHECK(r32(m, h19 + 172) == 0);
    CHECK(r32(m, h19 + 176) == 0);
    CHECK((r32(m, h19) & 0xF00u) == 0);
    MESSAGE("dorm snapshot: " << slots.size() << " slots, " << styled << " with text lines styled");
}

// =====================================================================================================================
// A fresh system on the ELF image: the font system start and the message manager start (heap / file stand-ins)
// =====================================================================================================================
TEST_CASE("game(ui4): font system start and message manager start") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    write_rw_slots(m);
    g_live.clear();
    Opt si;
    si.standins = true;
    si.recorders = {{0x3CF120u, "sub_3CF120", sx(kOut + 0xF00)}};  // the facility record "fclBank" goes into
    u32 seed = 300;
    const hgp::Run start = ui_pair(m, "frFontSystemStart", {0, 0, 0, 0}, seed++, "frFontSystemStart", si);
    MESSAGE("frFontSystemStart: " << (start.stopped ? "stopped (" + start.what + ")" : std::string("returned")));
    if (!start.stopped) {
        const u32 f = r32(m, kGpReg - 0x469Cu);
        REQUIRE(f != 0);
        CHECK(gstr(m, f + 2) == "facility/i_mes_win01.spr");
    }
    ui_pair(m, "sub_3A4CE0", {0, 0, 0, 0}, seed++, "manager init", si);
    CHECK(r32(m, 0x959EC0u) == 0);
    CHECK(r32(m, 0x959ED0u) == 0);          // nothing in use
    CHECK(r32(m, 0x959ED8u) == 0x959EE0u);  // every slot free, slot 0 first
    for (u32 i = 0; i < 64; ++i) CHECK(r32(m, 0x959EE0u + 52 * i + 12) == 0);
}

// =====================================================================================================================
// Text-tag handlers on a layout record (documented rules: the parameter encoding, the fields each tag sets)
// =====================================================================================================================
TEST_CASE("game(ui4): text-tag handlers on a layout record") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const u32 kLay = kOut, kText = kOut + 0x100, kLine = kOut + 0x200, kFlags = kGpReg - 0x5808u;
    u32 seed = 500;
    // a layout whose text holds [tag hi, tag lo, b0, b1, b2, b3] with the read position on b0
    auto setup = [&](u8 lo, u8 b0, u8 b1, u8 b2, u8 b3) {
        std::memset(m.at(kLay), 0, 0x40);
        const u8 t[8] = {0xF3, lo, b0, b1, b2, b3, 0, 0};
        std::memcpy(m.at(kText), t, sizeof t);
        w32(m, kLay + 16, kText);
        w32(m, kLay + 20, kLine);
        w32(m, kLay + 24, 2);
        std::memset(m.at(kLine), 0, 0x44);
        w32(m, kFlags, 0);
    };
    auto param = [](u8 b0, u8 b1) { return static_cast<u32>((b0 - 1) & 0xFF) | (b1 == 0xFF ? 0u : static_cast<u32>((b1 - 1) & 0xFF)) << 8; };
    struct Byte {
        const char* fn;
        u8 tag;
        u32 off;
    };
    for (const Byte& b : {Byte{"sub_3AC5A0", 0x02, 13}, Byte{"sub_3AC6F0", 0x06, 12}, Byte{"sub_3AC750", 0x07, 15}, Byte{"sub_3AC7C0", 0x09, 14}}) {
        for (u8 v : {u8{1}, u8{5}, u8{0x80}, u8{0xFF}}) {
            setup(b.tag, v, 0xFF, 0, 0);
            const hgp::Run r = ui_pair(m, b.fn, {0xF300u | b.tag, sx(kLay), 0, 0}, seed++, b.fn);
            CHECK(v0_of(r) == 0);
            CHECK(r8(m, kLay + b.off) == static_cast<u8>(v - 1));
        }
    }
    // 0x12: alpha and line code; 0x3F: alpha 20, code 32
    setup(0x12, 0x81, 0xFF, 0x04, 0x02);
    ui_pair(m, "sub_3ACB10", {0xF312u, sx(kLay), 0, 0}, seed++, "tag 0x12");
    CHECK(r8(m, kLay + 15) == 0x80);
    CHECK(r16(m, kLay + 30) == param(0x04, 0x02));
    setup(0x3F, 0, 0, 0, 0);
    ui_pair(m, "sub_3AEE00", {0xF13Fu, sx(kLay), 0, 0}, seed++, "tag 0x3F");
    CHECK(r8(m, kLay + 15) == 20);
    CHECK(r16(m, kLay + 30) == 32);
    // 0x16: both parameters to 0x7CE628 / 0x7CE62C, tag flag 8
    for (const auto& [b0, b1, b2, b3] : {std::array<u8, 4>{0x10, 0x03, 0x01, 0xFF}, std::array<u8, 4>{0x01, 0xFF, 0x7F, 0x7F}}) {
        setup(0x16, b0, b1, b2, b3);
        ui_pair(m, "sub_3AD2A0", {0xF316u, sx(kLay), 0, 0}, seed++, "tag 0x16");
        CHECK(r32(m, kGpReg - 0x46C8u) == param(b0, b1));
        CHECK(r32(m, kGpReg - 0x46C4u) == param(b2, b3));
        CHECK((r32(m, kFlags) & 8u) != 0);
    }
    // 0x14 / 0x15 / 0x17: the waits on the current line (flag 388 is clear in the ELF image: 0x15 waits 35)
    for (u32 armed : {0u, 1u}) {
        setup(0x14, 0x0B, 0xFF, 0, 0);
        w32(m, kLine + 52, armed);
        ui_pair(m, "sub_3AD130", {0xF214u, sx(kLay), 0, 0}, seed++, "tag 0x14");
        CHECK(r32(m, kLine + 48) == 0xF214u);
        CHECK(r32(m, kLine + 56) == armed);
        CHECK(r32(m, kLine + 60) == 10);
        setup(0x15, 0x0B, 0xFF, 0, 0);
        w32(m, kLine + 52, armed);
        ui_pair(m, "sub_3AD1B0", {0xF215u, sx(kLay), 0, 0}, seed++, "tag 0x15");
        CHECK(r32(m, kLine + 60) == 35);
    }
    setup(0x17, 0, 0, 0, 0);
    ui_pair(m, "sub_3AD360", {0xF117u, sx(kLay), 0, 0}, seed++, "tag 0x17");
    CHECK(r32(m, kLine + 52) == 0xF117u);
    // 0x18: 0x7CE634 = 20 only for parameter 0
    w32(m, kGpReg - 0x46BCu, 5);
    setup(0x18, 0x02, 0xFF, 0, 0);
    ui_pair(m, "sub_3AD380", {0xF218u, sx(kLay), 0, 0}, seed++, "tag 0x18 (1)");
    CHECK(r32(m, kGpReg - 0x46BCu) == 5);
    setup(0x18, 0x01, 0xFF, 0, 0);
    ui_pair(m, "sub_3AD380", {0xF218u, sx(kLay), 0, 0}, seed++, "tag 0x18 (0)");
    CHECK(r32(m, kGpReg - 0x46BCu) == 20);
    // the stops: 0x04 (flag 1), 0x31 (flags 3); 0x10 sets 2 and continues
    setup(0x04, 0, 0, 0, 0);
    CHECK(v0_of(ui_pair(m, "sub_3AC6C0", {0xF104u, sx(kLay), 0, 0}, seed++, "tag 0x04")) == 1);
    CHECK(r32(m, kFlags) == 1);
    setup(0x31, 0, 0, 0, 0);
    CHECK(v0_of(ui_pair(m, "sub_3AE820", {0xF131u, sx(kLay), 0, 0}, seed++, "tag 0x31")) == 1);
    CHECK(r32(m, kFlags) == 3);
    setup(0x10, 0, 0, 0, 0);
    CHECK(v0_of(ui_pair(m, "sub_3ACA90", {0xF110u, sx(kLay), 0, 0}, seed++, "tag 0x10")) == 0);
    CHECK(r32(m, kFlags) == 2);
    // 0x2F: the text up to the next 10 (a tag's parameters skipped whole) into 0x95ABF0, NUL in place of the 10
    {
        std::memset(m.at(kLay), 0, 0x40);
        const u8 t[] = {'A', 'B', 0x80, 0x81, 'C', 0xF2, 0x0A, 0x02, 0x03, 'D', 10, 'Z', 0};
        std::memcpy(m.at(kText), t, sizeof t);
        w32(m, kLay + 16, kText);
        w32(m, kLay + 24, 0);
        w32(m, kFlags, 0);
        ui_pair(m, "sub_3AE650", {0xF12Fu, sx(kLay), 0, 0}, seed++, "tag 0x2F");
        CHECK(r32(m, kLay + 24) == 11);
        CHECK(std::memcmp(m.at(0x95ABF0u), t, 10) == 0);
        CHECK(r8(m, 0x95ABF0u + 10) == 0);
        CHECK((r32(m, kFlags) & 0x10u) != 0);
    }
    // the do-nothing handlers return 0 and leave the record
    for (const char* fn : {"sub_3AC6E0", "sub_3AC7B0", "sub_3ACA30", "sub_3ACA40", "sub_3ADD30", "sub_3ADE60", "sub_3ADF40", "sub_3ADF50",
                           "sub_3ADF60", "sub_3AE140", "sub_3AE150", "sub_3AE840", "sub_3AE850", "sub_3AE860"}) {
        setup(0x05, 0x10, 0x10, 0x10, 0x10);
        CHECK(v0_of(ui_pair(m, fn, {0xF305u, sx(kLay), 0, 0}, seed++, fn)) == 0);
        CHECK(r8(m, kLay + 13) == 0);
    }
}

// =====================================================================================================================
// Leaves with documented results: the window pop-in curve, the key map, the ring buffer, the panel shading, line z
// =====================================================================================================================
TEST_CASE("game(ui4): window pop-in, key map, ring buffer, panel shading and line z") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    u32 seed = 700;
    // sub_3A7DD0: the y offset follows {0, -32, -12, 6, -4, 0}; frame 5 ends the pop-in
    const s16 curve[6] = {0, -32, -12, 6, -4, 0};
    const u32 h = kOut;
    std::memset(m.at(h), 0, 488);
    w8(m, h + 468, 1);
    for (int f = 0; f < 6; ++f) {
        ui_pair(m, "sub_3A7DD0", {sx(h), 0, 0, 0}, seed++, "pop-in");
        const int frame = f + 1 < 5 ? f + 1 : 5;
        CHECK(static_cast<s16>(r16(m, h + 472)) == frame);
        if (f + 1 <= 5) CHECK(static_cast<s16>(r16(m, h + 474)) == curve[f + 1]);
        CHECK(static_cast<s16>(r16(m, h + 470)) == (f + 1 >= 5 ? 1 : 0));
    }
    w8(m, h + 468, 0);  // inactive: nothing moves
    w16(m, h + 470, 0);
    w16(m, h + 472, 2);
    ui_pair(m, "sub_3A7DD0", {sx(h), 0, 0, 0}, seed++, "pop-in inactive");
    CHECK(r16(m, h + 472) == 2);
    // sub_3A7D60: the value of the first pair whose pad bit is held
    const u32 k = kOut + 0x400;
    std::memset(m.at(k), 0, 0x80);
    w16(m, k + 38, 3);
    const u16 bits[3] = {4, 6, 12}, vals[3] = {7, 8, 9};
    for (int i = 0; i < 3; ++i) {
        w16(m, k + 40 + 4 * i, bits[i]);
        w16(m, k + 42 + 4 * i, vals[i]);
    }
    for (const auto& [pad, want] : {std::pair<u16, s64>{u16{0}, -1}, {u16{1 << 6}, 8}, {u16{(1 << 12) | (1 << 6)}, 8}, {u16{1 << 12}, 9}, {u16{1 << 4}, 7}}) {
        w16(m, 0x7E094Eu, pad);
        CHECK(static_cast<s64>(v0_of(ui_pair(m, "sub_3A7D60", {sx(k), 0, 0, 0}, seed++, "key map"))) == want);
    }
    // sub_3B45F0 [rbInitRingBuf] (24-byte records, 5 of them) and sub_3B4740 [rbDestroy] on the stand-in heap
    write_rw_slots(m);
    g_live.clear();
    Opt si;
    si.standins = true;
    const u32 first = static_cast<u32>(v0_of(ui_pair(m, "sub_3B45F0", {24, 5, 0, 0}, seed++, "ring create", si)));
    const u32 block = first - 4;
    CHECK(log_of().log.back().args[0] == (24u + 8u) * 6u + 4u);
    CHECK(r32(m, block) == block);
    for (u32 i = 0; i <= 5; ++i) {
        const u32 rec = first + i * 32;
        CHECK(r32(m, rec) == i);
        CHECK(r32(m, rec + 4) == (i < 5 ? rec + 32 : first));
    }
    CHECK(v0_of(ui_pair(m, "sub_3B4740", {sx(first), 0, 0, 0}, seed++, "ring destroy", si)) == 1);
    CHECK(log_of().log.back().args[0] == block);
    // sub_3B4A90 [itfPnlShadeColours]: min(c * factor, 0xFF0000) >> 16 per channel, the alpha copied
    const u32 dst = kOut + 0x800, tbl = kOut + 0x900;
    const u32 fac[2][3] = {{0x10000, 0x8000, 0x18000}, {0x4000, 0x20000, 0x0}};
    for (int i = 0; i < 2; ++i)
        for (int c = 0; c < 3; ++c) w32(m, tbl + 16 * i + 4 * c, fac[i][c]);
    Opt sh;
    sh.gpr_in = {{GPR_T0, 0x80}, {GPR_T1, sx(tbl)}, {GPR_T2, 2}};
    ui_pair(m, "sub_3B4A90", {sx(dst), 200, 100, 180}, seed++, "shade", sh);
    const u32 rgb[3] = {200, 100, 180};
    for (int i = 0; i < 2; ++i) {
        for (int c = 0; c < 3; ++c) {
            const u64 v = std::min<u64>(static_cast<u64>(rgb[c]) * fac[i][c], 0xFF0000u) >> 16;
            CHECK(r32(m, dst + 16 * i + 4 * c) == v);
        }
        CHECK(r32(m, dst + 16 * i + 12) == 0x80);
    }
    // sub_3B2C60 [frFontLineSetZ]
    Opt z;
    z.fpr = {{12, fbits(12.5f)}};
    ui_pair(m, "sub_3B2C60", {sx(kOut + 0xA00), 0, 0, 0}, seed++, "line z", z);
    CHECK(r32(m, kOut + 0xA00 + 20) == fbits(12.5f));
}

TEST_CASE("game(ui4): pair count") { MESSAGE("ui4 pairs run (outside the random-world case): " << g_pairs); }

#else

TEST_CASE("game(ui4): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
