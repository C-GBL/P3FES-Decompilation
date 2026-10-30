// Pair tests of slice font2 (game/src/ui/font2.cpp): the font renderer and the sprite / cursor band. Every pair runs the
// hand body and its recompiled body from the same guest machine through tests/game/handgen_pairs.h -- the whole register
// file and the cycle count at every check point and at the return / stop, all 32 MiB of RAM (write-tracked), the
// scratchpad, the BIOS window, the bus log -- and, where a body allocates, prints or loads files, on two identical
// stand-in worlds (tests/game/stand_ins.h) whose call logs must match.
//
// Inputs: the p3fes_handgen random worlds for every function; the dorm replay snapshot's live font system (its styles,
// glyph rings, 256 raster slots of which 29 hold glyphs) for the glyph lists, the glyph cache (hits, misses, slot reuse,
// release over many strings and two colour sets), the layout loop, inserted strings, the reveal step, the immediate draw,
// slot allocation and a fresh slot pool; the ELF image with the file stand-ins for font/font0.fnt and the other three
// .FNT files from extracted/DATA/FONT (read at run time, never copied); pad / vibration / TMX / bust-up / sound / effect
// structures built in free RAM; the live task kernel of the snapshot for the effect task creators. Documented-rule
// checks: the style records against the .FNT header layout, every glyph decoded into a raster slot against a host
// decoder of the .FNT Huffman format (docs/ANALYSIS/20_menu_ui.md 5.3), hits / misses against the cached-glyph count,
// line widths against the glyph advances, the GS-list geometry, the pad edge / repeat / vibration rules, the TMX
// pixel and palette conversions.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/font2.h"

#include <algorithm>
#include <array>
#include <bit>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <memory>
#include <random>
#include <set>
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
void fn_H_Cursor_DestroyDrawTask_00100580(EEContext&);  // generated body
void fn_H_Cursor_DestroyDrawTask_00100580__recomp(EEContext&);  // recompiled
void fn_nullsub_1_001007f0(EEContext&);  // generated body
void fn_nullsub_1_001007f0__recomp(EEContext&);  // recompiled
void fn_sub_103580_00103580(EEContext&);  // generated body
void fn_sub_103580_00103580__recomp(EEContext&);  // recompiled
void fn_sub_103650_00103650(EEContext&);  // generated body
void fn_sub_103650_00103650__recomp(EEContext&);  // recompiled
void fn_sub_1038D0_001038d0(EEContext&);  // generated body
void fn_sub_1038D0_001038d0__recomp(EEContext&);  // recompiled
void fn_sub_103990_00103990(EEContext&);  // generated body
void fn_sub_103990_00103990__recomp(EEContext&);  // recompiled
void fn_sub_103B10_00103b10(EEContext&);  // generated body
void fn_sub_103B10_00103b10__recomp(EEContext&);  // recompiled
void fn_sub_103CF0_00103cf0(EEContext&);  // generated body
void fn_sub_103CF0_00103cf0__recomp(EEContext&);  // recompiled
void fn_sub_1040F0_001040f0(EEContext&);  // generated body
void fn_sub_1040F0_001040f0__recomp(EEContext&);  // recompiled
void fn_sub_1042E0_001042e0(EEContext&);  // generated body
void fn_sub_1042E0_001042e0__recomp(EEContext&);  // recompiled
void fn_sub_1043B0_001043b0(EEContext&);  // generated body
void fn_sub_1043B0_001043b0__recomp(EEContext&);  // recompiled
void fn_sub_104EB0_00104eb0(EEContext&);  // generated body
void fn_sub_104EB0_00104eb0__recomp(EEContext&);  // recompiled
void fn_sub_104FD0_00104fd0(EEContext&);  // generated body
void fn_sub_104FD0_00104fd0__recomp(EEContext&);  // recompiled
void fn_sub_105210_00105210(EEContext&);  // generated body
void fn_sub_105210_00105210__recomp(EEContext&);  // recompiled
void fn_sub_105800_00105800(EEContext&);  // generated body
void fn_sub_105800_00105800__recomp(EEContext&);  // recompiled
void fn_sub_1058A0_001058a0(EEContext&);  // generated body
void fn_sub_1058A0_001058a0__recomp(EEContext&);  // recompiled
void fn_sub_106730_00106730(EEContext&);  // generated body
void fn_sub_106730_00106730__recomp(EEContext&);  // recompiled
void fn_sub_106860_00106860(EEContext&);  // generated body
void fn_sub_106860_00106860__recomp(EEContext&);  // recompiled
void fn_sub_106E90_00106e90(EEContext&);  // generated body
void fn_sub_106E90_00106e90__recomp(EEContext&);  // recompiled
void fn_sub_106EC0_00106ec0(EEContext&);  // generated body
void fn_sub_106EC0_00106ec0__recomp(EEContext&);  // recompiled
void fn_sub_106F30_00106f30(EEContext&);  // generated body
void fn_sub_106F30_00106f30__recomp(EEContext&);  // recompiled
void fn_sub_106F60_00106f60(EEContext&);  // generated body
void fn_sub_106F60_00106f60__recomp(EEContext&);  // recompiled
void fn_sub_106FB0_00106fb0(EEContext&);  // generated body
void fn_sub_106FB0_00106fb0__recomp(EEContext&);  // recompiled
void fn_sub_106FF0_00106ff0(EEContext&);  // generated body
void fn_sub_106FF0_00106ff0__recomp(EEContext&);  // recompiled
void fn_sub_107060_00107060(EEContext&);  // generated body
void fn_sub_107060_00107060__recomp(EEContext&);  // recompiled
void fn_sub_108680_00108680(EEContext&);  // generated body
void fn_sub_108680_00108680__recomp(EEContext&);  // recompiled
void fn_sub_108E50_00108e50(EEContext&);  // generated body
void fn_sub_108E50_00108e50__recomp(EEContext&);  // recompiled
void fn_sub_109040_00109040(EEContext&);  // generated body
void fn_sub_109040_00109040__recomp(EEContext&);  // recompiled
void fn_sub_109170_00109170(EEContext&);  // generated body
void fn_sub_109170_00109170__recomp(EEContext&);  // recompiled
void fn_sub_1099A0_001099a0(EEContext&);  // generated body
void fn_sub_1099A0_001099a0__recomp(EEContext&);  // recompiled
void fn_sub_10A500_0010a500(EEContext&);  // generated body
void fn_sub_10A500_0010a500__recomp(EEContext&);  // recompiled
void fn_sub_10A6D0_0010a6d0(EEContext&);  // generated body
void fn_sub_10A6D0_0010a6d0__recomp(EEContext&);  // recompiled
void fn_sub_10DD10_0010dd10(EEContext&);  // generated body
void fn_sub_10DD10_0010dd10__recomp(EEContext&);  // recompiled
void fn_sub_10DDC0_0010ddc0(EEContext&);  // generated body
void fn_sub_10DDC0_0010ddc0__recomp(EEContext&);  // recompiled
void fn_sub_10DE40_0010de40(EEContext&);  // generated body
void fn_sub_10DE40_0010de40__recomp(EEContext&);  // recompiled
void fn_sub_10DEE0_0010dee0(EEContext&);  // generated body
void fn_sub_10DEE0_0010dee0__recomp(EEContext&);  // recompiled
void fn_sub_10DF60_0010df60(EEContext&);  // generated body
void fn_sub_10DF60_0010df60__recomp(EEContext&);  // recompiled
void fn_sub_10E010_0010e010(EEContext&);  // generated body
void fn_sub_10E010_0010e010__recomp(EEContext&);  // recompiled
void fn_sub_10E0D0_0010e0d0(EEContext&);  // generated body
void fn_sub_10E0D0_0010e0d0__recomp(EEContext&);  // recompiled
void fn_sub_10E500_0010e500(EEContext&);  // generated body
void fn_sub_10E500_0010e500__recomp(EEContext&);  // recompiled
void fn_sub_10E5F0_0010e5f0(EEContext&);  // generated body
void fn_sub_10E5F0_0010e5f0__recomp(EEContext&);  // recompiled
void fn_sub_10EC50_0010ec50(EEContext&);  // generated body
void fn_sub_10EC50_0010ec50__recomp(EEContext&);  // recompiled
void fn_sub_10F6C0_0010f6c0(EEContext&);  // generated body
void fn_sub_10F6C0_0010f6c0__recomp(EEContext&);  // recompiled
void fn_sub_1102E0_001102e0(EEContext&);  // generated body
void fn_sub_1102E0_001102e0__recomp(EEContext&);  // recompiled
void fn_sub_1103E0_001103e0(EEContext&);  // generated body
void fn_sub_1103E0_001103e0__recomp(EEContext&);  // recompiled
void fn_sub_1104B0_001104b0(EEContext&);  // generated body
void fn_sub_1104B0_001104b0__recomp(EEContext&);  // recompiled
void fn_sub_1104D0_001104d0(EEContext&);  // generated body
void fn_sub_1104D0_001104d0__recomp(EEContext&);  // recompiled
void fn_sub_110510_00110510(EEContext&);  // generated body
void fn_sub_110510_00110510__recomp(EEContext&);  // recompiled
void fn_sub_1105D0_001105d0(EEContext&);  // generated body
void fn_sub_1105D0_001105d0__recomp(EEContext&);  // recompiled
void fn_sub_110620_00110620(EEContext&);  // generated body
void fn_sub_110620_00110620__recomp(EEContext&);  // recompiled
void fn_sub_110650_00110650(EEContext&);  // generated body
void fn_sub_110650_00110650__recomp(EEContext&);  // recompiled
void fn_sub_1107D0_001107d0(EEContext&);  // generated body
void fn_sub_1107D0_001107d0__recomp(EEContext&);  // recompiled
void fn_sub_110E70_00110e70(EEContext&);  // generated body
void fn_sub_110E70_00110e70__recomp(EEContext&);  // recompiled
void fn_sub_111150_00111150(EEContext&);  // generated body
void fn_sub_111150_00111150__recomp(EEContext&);  // recompiled
void fn_sub_111260_00111260(EEContext&);  // generated body
void fn_sub_111260_00111260__recomp(EEContext&);  // recompiled
void fn_sub_111380_00111380(EEContext&);  // generated body
void fn_sub_111380_00111380__recomp(EEContext&);  // recompiled
void fn_sub_111520_00111520(EEContext&);  // generated body
void fn_sub_111520_00111520__recomp(EEContext&);  // recompiled
void fn_sub_111570_00111570(EEContext&);  // generated body
void fn_sub_111570_00111570__recomp(EEContext&);  // recompiled
void fn_sub_1115B0_001115b0(EEContext&);  // generated body
void fn_sub_1115B0_001115b0__recomp(EEContext&);  // recompiled
void fn_sub_1115E0_001115e0(EEContext&);  // generated body
void fn_sub_1115E0_001115e0__recomp(EEContext&);  // recompiled
void fn_sub_111D60_00111d60(EEContext&);  // generated body
void fn_sub_111D60_00111d60__recomp(EEContext&);  // recompiled
void fn_sprFontInit_00111f50(EEContext&);  // generated body
void fn_sprFontInit_00111f50__recomp(EEContext&);  // recompiled
void fn_sub_115CD0_00115cd0(EEContext&);  // generated body
void fn_sub_115CD0_00115cd0__recomp(EEContext&);  // recompiled
void fn_sub_115F00_00115f00(EEContext&);  // generated body
void fn_sub_115F00_00115f00__recomp(EEContext&);  // recompiled
void fn_sub_1165C0_001165c0(EEContext&);  // generated body
void fn_sub_1165C0_001165c0__recomp(EEContext&);  // recompiled
void fn_sub_1166A0_001166a0(EEContext&);  // generated body
void fn_sub_1166A0_001166a0__recomp(EEContext&);  // recompiled
void fn_sub_116760_00116760(EEContext&);  // generated body
void fn_sub_116760_00116760__recomp(EEContext&);  // recompiled
void fn_sub_116780_00116780(EEContext&);  // generated body
void fn_sub_116780_00116780__recomp(EEContext&);  // recompiled
void fn_sub_1167A0_001167a0(EEContext&);  // generated body
void fn_sub_1167A0_001167a0__recomp(EEContext&);  // recompiled
void fn_sub_1167C0_001167c0(EEContext&);  // generated body
void fn_sub_1167C0_001167c0__recomp(EEContext&);  // recompiled
void fn_sub_1167F0_001167f0(EEContext&);  // generated body
void fn_sub_1167F0_001167f0__recomp(EEContext&);  // recompiled
void fn_sub_116CF0_00116cf0(EEContext&);  // generated body
void fn_sub_116CF0_00116cf0__recomp(EEContext&);  // recompiled
void fn_sub_116E20_00116e20(EEContext&);  // generated body
void fn_sub_116E20_00116e20__recomp(EEContext&);  // recompiled
void fn_sub_116ED0_00116ed0(EEContext&);  // generated body
void fn_sub_116ED0_00116ed0__recomp(EEContext&);  // recompiled
void fn_sub_116EF0_00116ef0(EEContext&);  // generated body
void fn_sub_116EF0_00116ef0__recomp(EEContext&);  // recompiled
void fn_sub_116F10_00116f10(EEContext&);  // generated body
void fn_sub_116F10_00116f10__recomp(EEContext&);  // recompiled
void fn_sub_116F20_00116f20(EEContext&);  // generated body
void fn_sub_116F20_00116f20__recomp(EEContext&);  // recompiled
void fn_sub_116F30_00116f30(EEContext&);  // generated body
void fn_sub_116F30_00116f30__recomp(EEContext&);  // recompiled
void fn_sub_116F50_00116f50(EEContext&);  // generated body
void fn_sub_116F50_00116f50__recomp(EEContext&);  // recompiled
void fn_sub_116F80_00116f80(EEContext&);  // generated body
void fn_sub_116F80_00116f80__recomp(EEContext&);  // recompiled
void fn_sub_117440_00117440(EEContext&);  // generated body
void fn_sub_117440_00117440__recomp(EEContext&);  // recompiled
void fn_sub_117470_00117470(EEContext&);  // generated body
void fn_sub_117470_00117470__recomp(EEContext&);  // recompiled
void fn_sub_117490_00117490(EEContext&);  // generated body
void fn_sub_117490_00117490__recomp(EEContext&);  // recompiled
void fn_sub_117540_00117540(EEContext&);  // generated body
void fn_sub_117540_00117540__recomp(EEContext&);  // recompiled
void fn_sub_1191C0_001191c0(EEContext&);  // generated body
void fn_sub_1191C0_001191c0__recomp(EEContext&);  // recompiled
void fn_sub_1192B0_001192b0(EEContext&);  // generated body
void fn_sub_1192B0_001192b0__recomp(EEContext&);  // recompiled
void fn_sub_119380_00119380(EEContext&);  // generated body
void fn_sub_119380_00119380__recomp(EEContext&);  // recompiled
void fn_sub_1193A0_001193a0(EEContext&);  // generated body
void fn_sub_1193A0_001193a0__recomp(EEContext&);  // recompiled
void fn_sub_1193C0_001193c0(EEContext&);  // generated body
void fn_sub_1193C0_001193c0__recomp(EEContext&);  // recompiled
void fn_sub_1193D0_001193d0(EEContext&);  // generated body
void fn_sub_1193D0_001193d0__recomp(EEContext&);  // recompiled
void fn_sub_119930_00119930(EEContext&);  // generated body
void fn_sub_119930_00119930__recomp(EEContext&);  // recompiled
void fn_sub_119960_00119960(EEContext&);  // generated body
void fn_sub_119960_00119960__recomp(EEContext&);  // recompiled
void fn_sub_3AE000_003ae000(EEContext&);  // generated body
void fn_sub_3AE000_003ae000__recomp(EEContext&);  // recompiled
void fn_sub_3AE420_003ae420(EEContext&);  // generated body
void fn_sub_3AE420_003ae420__recomp(EEContext&);  // recompiled
void fn_sub_3AEE20_003aee20(EEContext&);  // generated body
void fn_sub_3AEE20_003aee20__recomp(EEContext&);  // recompiled
void fn_sub_3AF110_003af110(EEContext&);  // generated body
void fn_sub_3AF110_003af110__recomp(EEContext&);  // recompiled
void fn_frInitFontTable_003af7a0(EEContext&);  // generated body
void fn_frInitFontTable_003af7a0__recomp(EEContext&);  // recompiled
void fn_frAddFontStyle_003afad0(EEContext&);  // generated body
void fn_frAddFontStyle_003afad0__recomp(EEContext&);  // recompiled
void fn_frLoadFontData_003afc70(EEContext&);  // generated body
void fn_frLoadFontData_003afc70__recomp(EEContext&);  // recompiled
void fn_frFreeFontStyles_003afe30(EEContext&);  // generated body
void fn_frFreeFontStyles_003afe30__recomp(EEContext&);  // recompiled
void fn_sub_3B0030_003b0030(EEContext&);  // generated body
void fn_sub_3B0030_003b0030__recomp(EEContext&);  // recompiled
void fn_frFontCacheGlyph_003b0430(EEContext&);  // generated body
void fn_frFontCacheGlyph_003b0430__recomp(EEContext&);  // recompiled
void fn_frFontBuildGlyphList_003b0970(EEContext&);  // generated body
void fn_frFontBuildGlyphList_003b0970__recomp(EEContext&);  // recompiled
void fn_sub_3B0F50_003b0f50(EEContext&);  // generated body
void fn_sub_3B0F50_003b0f50__recomp(EEContext&);  // recompiled
void fn_sub_3B1710_003b1710(EEContext&);  // generated body
void fn_sub_3B1710_003b1710__recomp(EEContext&);  // recompiled
void fn_sub_3B1D90_003b1d90(EEContext&);  // generated body
void fn_sub_3B1D90_003b1d90__recomp(EEContext&);  // recompiled
void fn_sub_3B2020_003b2020(EEContext&);  // generated body
void fn_sub_3B2020_003b2020__recomp(EEContext&);  // recompiled
void fn_sub_3B22A0_003b22a0(EEContext&);  // generated body
void fn_sub_3B22A0_003b22a0__recomp(EEContext&);  // recompiled
void fn_sub_3B2430_003b2430(EEContext&);  // generated body
void fn_sub_3B2430_003b2430__recomp(EEContext&);  // recompiled
void fn_frFontRasterCreate_003b35e0(EEContext&);  // generated body
void fn_frFontRasterCreate_003b35e0__recomp(EEContext&);  // recompiled
void fn_frFontRasterAllocSlot_003b3e60(EEContext&);  // generated body
void fn_frFontRasterAllocSlot_003b3e60__recomp(EEContext&);  // recompiled
void fn_frFontRasterCreate2_003b3f90(EEContext&);  // generated body
void fn_frFontRasterCreate2_003b3f90__recomp(EEContext&);  // recompiled
void fn_sub_3B41A0_003b41a0(EEContext&);  // generated body
void fn_sub_3B41A0_003b41a0__recomp(EEContext&);  // recompiled
void fn_sub_3B4D10_003b4d10(EEContext&);  // generated body
void fn_sub_3B4D10_003b4d10__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"H_Cursor_DestroyDrawTask", 0x100580, &recomp_gen::fn_H_Cursor_DestroyDrawTask_00100580, &recomp_gen::fn_H_Cursor_DestroyDrawTask_00100580__recomp},
    {"nullsub_1", 0x1007F0, &recomp_gen::fn_nullsub_1_001007f0, &recomp_gen::fn_nullsub_1_001007f0__recomp},
    {"sub_103580", 0x103580, &recomp_gen::fn_sub_103580_00103580, &recomp_gen::fn_sub_103580_00103580__recomp},
    {"sub_103650", 0x103650, &recomp_gen::fn_sub_103650_00103650, &recomp_gen::fn_sub_103650_00103650__recomp},
    {"sub_1038D0", 0x1038D0, &recomp_gen::fn_sub_1038D0_001038d0, &recomp_gen::fn_sub_1038D0_001038d0__recomp},
    {"sub_103990", 0x103990, &recomp_gen::fn_sub_103990_00103990, &recomp_gen::fn_sub_103990_00103990__recomp},
    {"sub_103B10", 0x103B10, &recomp_gen::fn_sub_103B10_00103b10, &recomp_gen::fn_sub_103B10_00103b10__recomp},
    {"sub_103CF0", 0x103CF0, &recomp_gen::fn_sub_103CF0_00103cf0, &recomp_gen::fn_sub_103CF0_00103cf0__recomp},
    {"sub_1040F0", 0x1040F0, &recomp_gen::fn_sub_1040F0_001040f0, &recomp_gen::fn_sub_1040F0_001040f0__recomp},
    {"sub_1042E0", 0x1042E0, &recomp_gen::fn_sub_1042E0_001042e0, &recomp_gen::fn_sub_1042E0_001042e0__recomp},
    {"sub_1043B0", 0x1043B0, &recomp_gen::fn_sub_1043B0_001043b0, &recomp_gen::fn_sub_1043B0_001043b0__recomp},
    {"sub_104EB0", 0x104EB0, &recomp_gen::fn_sub_104EB0_00104eb0, &recomp_gen::fn_sub_104EB0_00104eb0__recomp},
    {"sub_104FD0", 0x104FD0, &recomp_gen::fn_sub_104FD0_00104fd0, &recomp_gen::fn_sub_104FD0_00104fd0__recomp},
    {"sub_105210", 0x105210, &recomp_gen::fn_sub_105210_00105210, &recomp_gen::fn_sub_105210_00105210__recomp},
    {"sub_105800", 0x105800, &recomp_gen::fn_sub_105800_00105800, &recomp_gen::fn_sub_105800_00105800__recomp},
    {"sub_1058A0", 0x1058A0, &recomp_gen::fn_sub_1058A0_001058a0, &recomp_gen::fn_sub_1058A0_001058a0__recomp},
    {"sub_106730", 0x106730, &recomp_gen::fn_sub_106730_00106730, &recomp_gen::fn_sub_106730_00106730__recomp},
    {"sub_106860", 0x106860, &recomp_gen::fn_sub_106860_00106860, &recomp_gen::fn_sub_106860_00106860__recomp},
    {"sub_106E90", 0x106E90, &recomp_gen::fn_sub_106E90_00106e90, &recomp_gen::fn_sub_106E90_00106e90__recomp},
    {"sub_106EC0", 0x106EC0, &recomp_gen::fn_sub_106EC0_00106ec0, &recomp_gen::fn_sub_106EC0_00106ec0__recomp},
    {"sub_106F30", 0x106F30, &recomp_gen::fn_sub_106F30_00106f30, &recomp_gen::fn_sub_106F30_00106f30__recomp},
    {"sub_106F60", 0x106F60, &recomp_gen::fn_sub_106F60_00106f60, &recomp_gen::fn_sub_106F60_00106f60__recomp},
    {"sub_106FB0", 0x106FB0, &recomp_gen::fn_sub_106FB0_00106fb0, &recomp_gen::fn_sub_106FB0_00106fb0__recomp},
    {"sub_106FF0", 0x106FF0, &recomp_gen::fn_sub_106FF0_00106ff0, &recomp_gen::fn_sub_106FF0_00106ff0__recomp},
    {"sub_107060", 0x107060, &recomp_gen::fn_sub_107060_00107060, &recomp_gen::fn_sub_107060_00107060__recomp},
    {"sub_108680", 0x108680, &recomp_gen::fn_sub_108680_00108680, &recomp_gen::fn_sub_108680_00108680__recomp},
    {"sub_108E50", 0x108E50, &recomp_gen::fn_sub_108E50_00108e50, &recomp_gen::fn_sub_108E50_00108e50__recomp},
    {"sub_109040", 0x109040, &recomp_gen::fn_sub_109040_00109040, &recomp_gen::fn_sub_109040_00109040__recomp},
    {"sub_109170", 0x109170, &recomp_gen::fn_sub_109170_00109170, &recomp_gen::fn_sub_109170_00109170__recomp},
    {"sub_1099A0", 0x1099A0, &recomp_gen::fn_sub_1099A0_001099a0, &recomp_gen::fn_sub_1099A0_001099a0__recomp},
    {"sub_10A500", 0x10A500, &recomp_gen::fn_sub_10A500_0010a500, &recomp_gen::fn_sub_10A500_0010a500__recomp},
    {"sub_10A6D0", 0x10A6D0, &recomp_gen::fn_sub_10A6D0_0010a6d0, &recomp_gen::fn_sub_10A6D0_0010a6d0__recomp},
    {"sub_10DD10", 0x10DD10, &recomp_gen::fn_sub_10DD10_0010dd10, &recomp_gen::fn_sub_10DD10_0010dd10__recomp},
    {"sub_10DDC0", 0x10DDC0, &recomp_gen::fn_sub_10DDC0_0010ddc0, &recomp_gen::fn_sub_10DDC0_0010ddc0__recomp},
    {"sub_10DE40", 0x10DE40, &recomp_gen::fn_sub_10DE40_0010de40, &recomp_gen::fn_sub_10DE40_0010de40__recomp},
    {"sub_10DEE0", 0x10DEE0, &recomp_gen::fn_sub_10DEE0_0010dee0, &recomp_gen::fn_sub_10DEE0_0010dee0__recomp},
    {"sub_10DF60", 0x10DF60, &recomp_gen::fn_sub_10DF60_0010df60, &recomp_gen::fn_sub_10DF60_0010df60__recomp},
    {"sub_10E010", 0x10E010, &recomp_gen::fn_sub_10E010_0010e010, &recomp_gen::fn_sub_10E010_0010e010__recomp},
    {"sub_10E0D0", 0x10E0D0, &recomp_gen::fn_sub_10E0D0_0010e0d0, &recomp_gen::fn_sub_10E0D0_0010e0d0__recomp},
    {"sub_10E500", 0x10E500, &recomp_gen::fn_sub_10E500_0010e500, &recomp_gen::fn_sub_10E500_0010e500__recomp},
    {"sub_10E5F0", 0x10E5F0, &recomp_gen::fn_sub_10E5F0_0010e5f0, &recomp_gen::fn_sub_10E5F0_0010e5f0__recomp},
    {"sub_10EC50", 0x10EC50, &recomp_gen::fn_sub_10EC50_0010ec50, &recomp_gen::fn_sub_10EC50_0010ec50__recomp},
    {"sub_10F6C0", 0x10F6C0, &recomp_gen::fn_sub_10F6C0_0010f6c0, &recomp_gen::fn_sub_10F6C0_0010f6c0__recomp},
    {"sub_1102E0", 0x1102E0, &recomp_gen::fn_sub_1102E0_001102e0, &recomp_gen::fn_sub_1102E0_001102e0__recomp},
    {"sub_1103E0", 0x1103E0, &recomp_gen::fn_sub_1103E0_001103e0, &recomp_gen::fn_sub_1103E0_001103e0__recomp},
    {"sub_1104B0", 0x1104B0, &recomp_gen::fn_sub_1104B0_001104b0, &recomp_gen::fn_sub_1104B0_001104b0__recomp},
    {"sub_1104D0", 0x1104D0, &recomp_gen::fn_sub_1104D0_001104d0, &recomp_gen::fn_sub_1104D0_001104d0__recomp},
    {"sub_110510", 0x110510, &recomp_gen::fn_sub_110510_00110510, &recomp_gen::fn_sub_110510_00110510__recomp},
    {"sub_1105D0", 0x1105D0, &recomp_gen::fn_sub_1105D0_001105d0, &recomp_gen::fn_sub_1105D0_001105d0__recomp},
    {"sub_110620", 0x110620, &recomp_gen::fn_sub_110620_00110620, &recomp_gen::fn_sub_110620_00110620__recomp},
    {"sub_110650", 0x110650, &recomp_gen::fn_sub_110650_00110650, &recomp_gen::fn_sub_110650_00110650__recomp},
    {"sub_1107D0", 0x1107D0, &recomp_gen::fn_sub_1107D0_001107d0, &recomp_gen::fn_sub_1107D0_001107d0__recomp},
    {"sub_110E70", 0x110E70, &recomp_gen::fn_sub_110E70_00110e70, &recomp_gen::fn_sub_110E70_00110e70__recomp},
    {"sub_111150", 0x111150, &recomp_gen::fn_sub_111150_00111150, &recomp_gen::fn_sub_111150_00111150__recomp},
    {"sub_111260", 0x111260, &recomp_gen::fn_sub_111260_00111260, &recomp_gen::fn_sub_111260_00111260__recomp},
    {"sub_111380", 0x111380, &recomp_gen::fn_sub_111380_00111380, &recomp_gen::fn_sub_111380_00111380__recomp},
    {"sub_111520", 0x111520, &recomp_gen::fn_sub_111520_00111520, &recomp_gen::fn_sub_111520_00111520__recomp},
    {"sub_111570", 0x111570, &recomp_gen::fn_sub_111570_00111570, &recomp_gen::fn_sub_111570_00111570__recomp},
    {"sub_1115B0", 0x1115B0, &recomp_gen::fn_sub_1115B0_001115b0, &recomp_gen::fn_sub_1115B0_001115b0__recomp},
    {"sub_1115E0", 0x1115E0, &recomp_gen::fn_sub_1115E0_001115e0, &recomp_gen::fn_sub_1115E0_001115e0__recomp},
    {"sub_111D60", 0x111D60, &recomp_gen::fn_sub_111D60_00111d60, &recomp_gen::fn_sub_111D60_00111d60__recomp},
    {"sprFontInit", 0x111F50, &recomp_gen::fn_sprFontInit_00111f50, &recomp_gen::fn_sprFontInit_00111f50__recomp},
    {"sub_115CD0", 0x115CD0, &recomp_gen::fn_sub_115CD0_00115cd0, &recomp_gen::fn_sub_115CD0_00115cd0__recomp},
    {"sub_115F00", 0x115F00, &recomp_gen::fn_sub_115F00_00115f00, &recomp_gen::fn_sub_115F00_00115f00__recomp},
    {"sub_1165C0", 0x1165C0, &recomp_gen::fn_sub_1165C0_001165c0, &recomp_gen::fn_sub_1165C0_001165c0__recomp},
    {"sub_1166A0", 0x1166A0, &recomp_gen::fn_sub_1166A0_001166a0, &recomp_gen::fn_sub_1166A0_001166a0__recomp},
    {"sub_116760", 0x116760, &recomp_gen::fn_sub_116760_00116760, &recomp_gen::fn_sub_116760_00116760__recomp},
    {"sub_116780", 0x116780, &recomp_gen::fn_sub_116780_00116780, &recomp_gen::fn_sub_116780_00116780__recomp},
    {"sub_1167A0", 0x1167A0, &recomp_gen::fn_sub_1167A0_001167a0, &recomp_gen::fn_sub_1167A0_001167a0__recomp},
    {"sub_1167C0", 0x1167C0, &recomp_gen::fn_sub_1167C0_001167c0, &recomp_gen::fn_sub_1167C0_001167c0__recomp},
    {"sub_1167F0", 0x1167F0, &recomp_gen::fn_sub_1167F0_001167f0, &recomp_gen::fn_sub_1167F0_001167f0__recomp},
    {"sub_116CF0", 0x116CF0, &recomp_gen::fn_sub_116CF0_00116cf0, &recomp_gen::fn_sub_116CF0_00116cf0__recomp},
    {"sub_116E20", 0x116E20, &recomp_gen::fn_sub_116E20_00116e20, &recomp_gen::fn_sub_116E20_00116e20__recomp},
    {"sub_116ED0", 0x116ED0, &recomp_gen::fn_sub_116ED0_00116ed0, &recomp_gen::fn_sub_116ED0_00116ed0__recomp},
    {"sub_116EF0", 0x116EF0, &recomp_gen::fn_sub_116EF0_00116ef0, &recomp_gen::fn_sub_116EF0_00116ef0__recomp},
    {"sub_116F10", 0x116F10, &recomp_gen::fn_sub_116F10_00116f10, &recomp_gen::fn_sub_116F10_00116f10__recomp},
    {"sub_116F20", 0x116F20, &recomp_gen::fn_sub_116F20_00116f20, &recomp_gen::fn_sub_116F20_00116f20__recomp},
    {"sub_116F30", 0x116F30, &recomp_gen::fn_sub_116F30_00116f30, &recomp_gen::fn_sub_116F30_00116f30__recomp},
    {"sub_116F50", 0x116F50, &recomp_gen::fn_sub_116F50_00116f50, &recomp_gen::fn_sub_116F50_00116f50__recomp},
    {"sub_116F80", 0x116F80, &recomp_gen::fn_sub_116F80_00116f80, &recomp_gen::fn_sub_116F80_00116f80__recomp},
    {"sub_117440", 0x117440, &recomp_gen::fn_sub_117440_00117440, &recomp_gen::fn_sub_117440_00117440__recomp},
    {"sub_117470", 0x117470, &recomp_gen::fn_sub_117470_00117470, &recomp_gen::fn_sub_117470_00117470__recomp},
    {"sub_117490", 0x117490, &recomp_gen::fn_sub_117490_00117490, &recomp_gen::fn_sub_117490_00117490__recomp},
    {"sub_117540", 0x117540, &recomp_gen::fn_sub_117540_00117540, &recomp_gen::fn_sub_117540_00117540__recomp},
    {"sub_1191C0", 0x1191C0, &recomp_gen::fn_sub_1191C0_001191c0, &recomp_gen::fn_sub_1191C0_001191c0__recomp},
    {"sub_1192B0", 0x1192B0, &recomp_gen::fn_sub_1192B0_001192b0, &recomp_gen::fn_sub_1192B0_001192b0__recomp},
    {"sub_119380", 0x119380, &recomp_gen::fn_sub_119380_00119380, &recomp_gen::fn_sub_119380_00119380__recomp},
    {"sub_1193A0", 0x1193A0, &recomp_gen::fn_sub_1193A0_001193a0, &recomp_gen::fn_sub_1193A0_001193a0__recomp},
    {"sub_1193C0", 0x1193C0, &recomp_gen::fn_sub_1193C0_001193c0, &recomp_gen::fn_sub_1193C0_001193c0__recomp},
    {"sub_1193D0", 0x1193D0, &recomp_gen::fn_sub_1193D0_001193d0, &recomp_gen::fn_sub_1193D0_001193d0__recomp},
    {"sub_119930", 0x119930, &recomp_gen::fn_sub_119930_00119930, &recomp_gen::fn_sub_119930_00119930__recomp},
    {"sub_119960", 0x119960, &recomp_gen::fn_sub_119960_00119960, &recomp_gen::fn_sub_119960_00119960__recomp},
    {"sub_3AE000", 0x3AE000, &recomp_gen::fn_sub_3AE000_003ae000, &recomp_gen::fn_sub_3AE000_003ae000__recomp},
    {"sub_3AE420", 0x3AE420, &recomp_gen::fn_sub_3AE420_003ae420, &recomp_gen::fn_sub_3AE420_003ae420__recomp},
    {"sub_3AEE20", 0x3AEE20, &recomp_gen::fn_sub_3AEE20_003aee20, &recomp_gen::fn_sub_3AEE20_003aee20__recomp},
    {"sub_3AF110", 0x3AF110, &recomp_gen::fn_sub_3AF110_003af110, &recomp_gen::fn_sub_3AF110_003af110__recomp},
    {"frInitFontTable", 0x3AF7A0, &recomp_gen::fn_frInitFontTable_003af7a0, &recomp_gen::fn_frInitFontTable_003af7a0__recomp},
    {"frAddFontStyle", 0x3AFAD0, &recomp_gen::fn_frAddFontStyle_003afad0, &recomp_gen::fn_frAddFontStyle_003afad0__recomp},
    {"frLoadFontData", 0x3AFC70, &recomp_gen::fn_frLoadFontData_003afc70, &recomp_gen::fn_frLoadFontData_003afc70__recomp},
    {"frFreeFontStyles", 0x3AFE30, &recomp_gen::fn_frFreeFontStyles_003afe30, &recomp_gen::fn_frFreeFontStyles_003afe30__recomp},
    {"sub_3B0030", 0x3B0030, &recomp_gen::fn_sub_3B0030_003b0030, &recomp_gen::fn_sub_3B0030_003b0030__recomp},
    {"frFontCacheGlyph", 0x3B0430, &recomp_gen::fn_frFontCacheGlyph_003b0430, &recomp_gen::fn_frFontCacheGlyph_003b0430__recomp},
    {"frFontBuildGlyphList", 0x3B0970, &recomp_gen::fn_frFontBuildGlyphList_003b0970, &recomp_gen::fn_frFontBuildGlyphList_003b0970__recomp},
    {"sub_3B0F50", 0x3B0F50, &recomp_gen::fn_sub_3B0F50_003b0f50, &recomp_gen::fn_sub_3B0F50_003b0f50__recomp},
    {"sub_3B1710", 0x3B1710, &recomp_gen::fn_sub_3B1710_003b1710, &recomp_gen::fn_sub_3B1710_003b1710__recomp},
    {"sub_3B1D90", 0x3B1D90, &recomp_gen::fn_sub_3B1D90_003b1d90, &recomp_gen::fn_sub_3B1D90_003b1d90__recomp},
    {"sub_3B2020", 0x3B2020, &recomp_gen::fn_sub_3B2020_003b2020, &recomp_gen::fn_sub_3B2020_003b2020__recomp},
    {"sub_3B22A0", 0x3B22A0, &recomp_gen::fn_sub_3B22A0_003b22a0, &recomp_gen::fn_sub_3B22A0_003b22a0__recomp},
    {"sub_3B2430", 0x3B2430, &recomp_gen::fn_sub_3B2430_003b2430, &recomp_gen::fn_sub_3B2430_003b2430__recomp},
    {"frFontRasterCreate", 0x3B35E0, &recomp_gen::fn_frFontRasterCreate_003b35e0, &recomp_gen::fn_frFontRasterCreate_003b35e0__recomp},
    {"frFontRasterAllocSlot", 0x3B3E60, &recomp_gen::fn_frFontRasterAllocSlot_003b3e60, &recomp_gen::fn_frFontRasterAllocSlot_003b3e60__recomp},
    {"frFontRasterCreate2", 0x3B3F90, &recomp_gen::fn_frFontRasterCreate2_003b3f90, &recomp_gen::fn_frFontRasterCreate2_003b3f90__recomp},
    {"sub_3B41A0", 0x3B41A0, &recomp_gen::fn_sub_3B41A0_003b41a0, &recomp_gen::fn_sub_3B41A0_003b41a0__recomp},
    {"sub_3B4D10", 0x3B4D10, &recomp_gen::fn_sub_3B4D10_003b4d10, &recomp_gen::fn_sub_3B4D10_003b4d10__recomp},
};

// The random worlds of the first case: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 24;

constexpr u32 kGpReg = 0x7D2CF0u;
constexpr u32 kOut = 0x01F40000u;  // free in every snapshot and in the ELF image (stand_ins.h)

// --- font globals (font2.h: fnt::) -----------------------------------------------------------------------------------
constexpr u32 kStyles = 0x95ACF0u;        // sFrFontStyles[9], 32 bytes each
constexpr u32 kCachedGlyphs = 0x95AE10u;  // glyphs with a registered GS entry
constexpr u32 kGlyphNodes = 0x95AE14u;
constexpr u32 kLineNodes = 0x95AE18u;
constexpr u32 kStyleCdNodes = 0x95AE74u;
constexpr u32 kTagSlots = 0x95AC70u;
constexpr u32 kPoolWord = kGpReg - 0x46ACu;  // 0x7CE644: the raster-slot pool header
constexpr u32 kGlyphFlags = kGpReg - 0x57F0u;  // 0x7CD500
constexpr u32 kGslReady = kGpReg - 0x46A4u;    // 0x7CE64C
constexpr u32 kGslList = 0x95AEBCu;

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
    bool load = true;
    std::vector<std::tuple<u32, std::string, u64>> recorders;  // not-emitted callees served by a recorder
    std::vector<std::tuple<u32, std::string, StandInFn>> customs;  // not-emitted callees served by a custom stand-in
};
Tramp g_t;
std::map<u32, u32> g_live;
int g_pairs = 0;
int g_stops = 0;

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
    g_t.world[K]->cd.load = g_t.load;
    for (const auto& [va, name, v0] : g_t.recorders) g_t.world[K]->si.install_recorder(va, name, v0);
    for (const auto& [va, name, fn] : g_t.customs) g_t.world[K]->si.install(va, name, fn);
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
    bool load = true;
    std::vector<std::tuple<u32, std::string, u64>> recorders;
    std::vector<std::tuple<u32, std::string, StandInFn>> customs;
};

hgp::Run f2_pair(Machine& m, const char* name, const Args& a, u32 seed, const std::string& what, const Opt& o = {}) {
    const Case& c = by_name(name);
    g_t.fn[0] = c.hand;
    g_t.fn[1] = c.recomp;
    g_t.fpr = o.fpr;
    g_t.standins = o.standins;
    g_t.load = o.load;
    g_t.recorders = o.recorders;
    g_t.customs = o.customs;
    HwCheck hw;
    hw.gpr_in = o.gpr_in;
    hgp::Run r = hgp::pair(m, &tramp<0>, &tramp<1>, a, seed, what.c_str(), hw);
    if (o.standins && g_t.world[0] && g_t.world[1]) {
        expect_same_log(g_t.world[0]->si, g_t.world[1]->si, what.c_str());
        g_live = g_t.world[1]->heap.live();
    }
    ++g_pairs;
    if (r.stopped) {
        ++g_stops;
        MESSAGE(what << ": both bodies stopped at " << hex64(r.stop_pc) << " (" << r.what << ")");
    }
    return r;
}
u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
u32 v0w(const hgp::Run& r) { return static_cast<u32>(r.end.gpr[GPR_V0].u64[0]); }
const StandIns& log_of() { return g_t.world[1]->si; }

// --- guest memory helpers ---------------------------------------------------------------------------------------------
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + (va & 0x1FFFFFFu), 4);
    return v;
}
s32 rs32(const Machine& m, u32 va) { return static_cast<s32>(r32(m, va)); }
u16 r16(const Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.mem.main_ram() + (va & 0x1FFFFFFu), 2);
    return v;
}
u8 r8(const Machine& m, u32 va) { return m.mem.main_ram()[va & 0x1FFFFFFu]; }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void wbytes(Machine& m, u32 va, const std::string& s) { std::memcpy(m.at(va), s.data(), s.size()); *m.at(va + static_cast<u32>(s.size())) = 0; }
std::string gstr(const Machine& m, u32 va) { return m.str(va, 128); }
u32 fbits(float f) { return std::bit_cast<u32>(f); }

bool load_snapshot(Machine& m, const char* s, std::vector<u8>* keep = nullptr) {
    std::vector<u8> snap = read_snapshot(s);
    if (snap.size() != EEMemory::kMainRamSize) return false;
    std::memcpy(m.mem.main_ram(), snap.data(), snap.size());
    if (keep) *keep = std::move(snap);
    return true;
}

std::vector<u8> read_host_file(const std::string& path) {
    std::vector<u8> v;
    if (FILE* f = std::fopen(path.c_str(), "rb")) {
        std::fseek(f, 0, SEEK_END);
        const long n = std::ftell(f);
        std::fseek(f, 0, SEEK_SET);
        if (n > 0) {
            v.resize(static_cast<std::size_t>(n));
            if (std::fread(v.data(), 1, v.size(), f) != v.size()) v.clear();
        }
        std::fclose(f);
    }
    return v;
}

// --- a host reader of the .FNT format (docs/ANALYSIS/20_menu_ui.md 5.3), independent of the guest code -------------
struct Fnt {
    std::vector<u8> b;
    u32 le32(std::size_t o) const { return o + 4 <= b.size() ? u32(b[o]) | u32(b[o + 1]) << 8 | u32(b[o + 2]) << 16 | u32(b[o + 3]) << 24 : 0; }
    u16 le16(std::size_t o) const { return o + 2 <= b.size() ? static_cast<u16>(b[o] | b[o + 1] << 8) : 0; }
    u32 glyphs() const { return le16(0x0E); }
    // the offsets frAddFontStyle derives: width table, block 2, glyph table, Huffman block (from the image start)
    u32 tables() const { return le32(0) + (u32(b[0x0A]) << 6); }
    u32 widths() const { return tables() + 4; }
    u32 width_bytes() const { return le32(tables()); }
    u32 block2() const { return tables() + 4 + width_bytes() + 4; }
    u32 block2_bytes() const { return le32(tables() + 4 + width_bytes()); }
    u32 glyph_table() const { return b[0x16] ? block2() + block2_bytes() : tables(); }
    u32 huffman() const { return glyph_table() + 4 * glyphs(); }
    // one glyph's 4-bit bitmap: the bits offsets[g] .. offsets[g + 1] of the u16 stream (LSB first) walk the
    // dictionary from node 0 (bit 0 -> child0 at +2, bit 1 -> child1 at +4; a node whose child0 is 0 is a leaf, its
    // byte at +4)
    std::vector<u8> decode(u32 g) const {
        std::vector<u8> out;
        const u32 h = huffman();
        const u32 dict = h + le32(h);
        const u32 offs = dict + le32(h + 4);
        const u32 stream = offs + le32(h + 24);
        const u32 b0 = le32(offs + 4 * g), b1 = le32(offs + 4 * (g + 1));
        u32 node = dict;
        for (u32 p = b0; p < b1 || (p == b0 && b0 == b1); ++p) {
            const u32 bit = (le16(stream + 2 * (p >> 4)) >> (p & 15)) & 1u;
            node = dict + 6u * le16(node + 2 + 2 * bit);
            if (le16(node + 2) == 0) {
                out.push_back(b[node + 4]);
                node = dict;
            }
            if (b0 == b1) break;
        }
        return out;
    }
};
Fnt host_font(const char* name) { return Fnt{read_host_file(extracted_root() + "/DATA/FONT/" + name)}; }

// --- the font structures --------------------------------------------------------------------------------------------
std::vector<u32> line_glyphs(const Machine& m, u32 line) {
    std::vector<u32> g;
    for (u32 p = r32(m, line + 28); p != 0 && g.size() < 4096; p = r32(m, p + 40)) g.push_back(p);
    return g;
}
std::vector<u32> slot_list(const Machine& m, u32 head_off) {
    std::vector<u32> s;
    const u32 pool = r32(m, kPoolWord);
    for (u32 p = pool ? r32(m, pool + head_off) : 0; p != 0 && s.size() < 4096; p = r32(m, p + 24)) s.push_back(p);
    return s;
}
std::set<std::pair<u32, u32>> live_cache_keys(const Machine& m) {  // (glyph, colour set) of slots with a cache record
    std::set<std::pair<u32, u32>> k;
    for (u32 s : slot_list(m, 8))
        if (r32(m, s + 16) != 0) k.insert({r32(m, s + 4), r16(m, s + 8)});
    return k;
}

}  // namespace

// =====================================================================================================================
// Every body on random worlds (the p3fes_handgen skeleton; the cases below carry the real inputs)
// =====================================================================================================================
TEST_CASE("game(font2): every body equals its recompiled body on random worlds") {
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
// Glyph lists and the glyph cache on the dorm snapshot: hits, misses, slot reuse and release over many strings, the
// decoded glyphs checked against DATA/FONT/FONT0.FNT decoded on the host
// =====================================================================================================================
TEST_CASE("game(font2): glyph lists, the glyph cache and raster-slot reuse on the dorm snapshot") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    if (!load_snapshot(m, "dorm_replay_4900")) {
        MESSAGE("SKIP: no dorm_replay_4900 snapshot under extracted/_ours");
        return;
    }
    write_rw_slots(m);
    g_live.clear();
    const Fnt font = host_font("FONT0.FNT");
    const u32 fnt = r32(m, kStyles + 4);
    REQUIRE(fnt != 0);
    // documented rules on the live style table: style 0 is font/font0.fnt bound by frAddFontStyle; styles 1..5 are
    // copies (frLoadFontData), 6..8 unbound
    if (!font.b.empty()) {
        CHECK(std::memcmp(m.mem.main_ram() + (fnt & 0x1FFFFFFu), font.b.data(), font.b.size()) == 0);
        CHECK(r32(m, kStyles + 8) == font.width_bytes());
        CHECK(r32(m, kStyles + 16) == fnt + font.widths());
        CHECK(r32(m, kStyles + 20) == fnt + font.block2());
        CHECK(r32(m, kStyles + 24) == fnt + font.glyph_table());
        CHECK(r32(m, kStyles + 28) == fnt + font.huffman());
        CHECK(font.width_bytes() == 2 * font.glyphs());
    } else {
        MESSAGE("note: DATA/FONT/FONT0.FNT not found under extracted/: the file checks are skipped");
    }
    for (u32 s = 1; s < 6; ++s) CHECK(std::memcmp(m.at(kStyles), m.at(kStyles + 32 * s), 32) == 0);
    for (u32 s = 6; s < 9; ++s) CHECK(r32(m, kStyles + 32 * s + 28) == 0);

    const s32 cached0 = rs32(m, kCachedGlyphs), glyphs0 = rs32(m, kGlyphNodes), lines0 = rs32(m, kLineNodes);
    const std::size_t active0 = slot_list(m, 8).size(), free0 = slot_list(m, 16).size();
    MESSAGE("dorm snapshot font state: " << cached0 << " cached glyphs, " << active0 << " active / " << free0 << " free raster slots");
    Opt si;
    si.standins = true;
    si.gpr_in = {{GPR_T0, 0}};  // frFontBuildGlyphList: no line to append to
    u32 seed = 1000;
    // (each text brings at most a few glyphs the cache has not seen: a miss decodes and swizzles a glyph, ~2,000 check
    // points, and a pair is cut at 20,000 -- handgen_pairs.h)
    const std::vector<std::string> texts = {
        "Iwatodai Dormitory", "The Dark Hour", "Tartarus", "Persona 3 FES", "0123", "4567", "89", "Hello, world!",
        "MEMENTO MORI", "jumpy quartz glyphs", "Shadows: 12 / 34", "Velvet Room", "a", "",
        std::string("\x82\xA0\x82\xA2\x82\xA4", 6), std::string("\x83\x41\x83\x43", 4), std::string("A\x81\x40" "B", 4),
        std::string("\xEF\xFF", 2), "The quick brown fox jumps over the lazy dog", "!!11!!", "pqgyjQ descenders"};
    std::vector<u32> lines;
    int misses_total = 0, hits_total = 0, decoded_checked = 0;
    auto build = [&](const std::string& t, u32 colour, const std::string& what) -> u32 {
        wbytes(m, kOut, t);
        const auto before = live_cache_keys(m);
        const std::vector<u32> active_before = slot_list(m, 8);
        const std::size_t free_before = slot_list(m, 16).size();
        const s32 cached_before = rs32(m, kCachedGlyphs);
        const hgp::Run r = f2_pair(m, "frFontBuildGlyphList", {sx(kOut), 0, colour, 0}, seed++, what, si);
        if (r.stopped) return 0;
        const u32 line = v0w(r);
        REQUIRE(line != 0);
        const std::vector<u32> g = line_glyphs(m, line);
        // one glyph per character (two bytes from 0x80), the width is the sum of the (kerned) advances
        std::size_t chars = 0;
        for (std::size_t i = 0; i < t.size(); ++i, ++chars)
            if (static_cast<u8>(t[i]) >= 0x80) ++i;
        CHECK(g.size() == chars);
        CHECK(r32(m, line + 24) == chars);
        s32 sum = 0;
        std::set<std::pair<u32, u32>> keys;
        for (u32 n : g) {
            sum += rs32(m, n + 12);
            const u32 rec = r32(m, n + 28);
            REQUIRE(rec != 0);
            const u32 slot = r32(m, rec + 12);
            REQUIRE(slot != 0);
            CHECK(r32(m, slot + 16) == rec);                     // slot <-> cache record
            CHECK(r16(m, rec + 0) == (r32(m, slot + 4) & 0xFFFFu));  // the record names the slot's glyph
            CHECK((r32(m, slot) & 1u) == 1u);                    // in use
            CHECK(r16(m, slot + 8) == colour);                   // the palette of the asked colour set
            keys.insert({r32(m, slot + 4), r16(m, slot + 8)});
        }
        CHECK(rs32(m, line + 12) == sum);
        // misses = keys that had no live cache record before; each one is one more cached glyph
        int misses = 0;
        for (const auto& k : keys) misses += before.count(k) ? 0 : 1;
        CHECK(rs32(m, kCachedGlyphs) - cached_before == misses);
        misses_total += misses;
        hits_total += static_cast<int>(g.size()) - misses;
        // the slots newly taken from the free list hold the glyph decoded from the file
        const std::set<u32> was(active_before.begin(), active_before.end());
        std::size_t taken = 0;
        for (u32 s : slot_list(m, 8)) {
            if (was.count(s)) continue;
            ++taken;
            CHECK(r16(m, s + 10) == 1);  // ticks
            if (!font.b.empty()) {
                const std::vector<u8> ref = font.decode(r32(m, s + 4));
                CHECK(ref.size() == 512);
                CHECK(std::memcmp(m.at(r32(m, s + 12)), ref.data(), std::min<std::size_t>(ref.size(), 512)) == 0);
                ++decoded_checked;
            }
        }
        CHECK(free_before - slot_list(m, 16).size() == taken);
        CHECK(taken <= static_cast<std::size_t>(misses));
        return line;
    };
    // round 1: every text -- misses fill the cache
    for (std::size_t i = 0; i < texts.size(); ++i) {
        if (texts[i].empty()) continue;
        if (const u32 l = build(texts[i], 0, "build " + std::to_string(i))) lines.push_back(l);
    }
    const s32 cached1 = rs32(m, kCachedGlyphs);
    const std::size_t free1 = slot_list(m, 16).size();
    // round 2: the same texts again -- all hits: no new cached glyph, no slot taken
    for (std::size_t i = 0; i < texts.size(); ++i) {
        if (texts[i].empty()) continue;
        if (const u32 l = build(texts[i], 0, "again " + std::to_string(i))) lines.push_back(l);
    }
    CHECK(rs32(m, kCachedGlyphs) == cached1);
    CHECK(slot_list(m, 16).size() == free1);
    // another colour set is another key: new records and slots for the same glyphs
    if (const u32 l = build("Tartarus", 3, "colour set 3")) lines.push_back(l);
    // release every chain (sub_3B0030): the counters come back to the snapshot's, the released slots stay on the
    // active list without a record (aged out later by frFontRasterAgeSlots), the free list is untouched
    const std::size_t free_before_release = slot_list(m, 16).size();
    for (std::size_t i = lines.size(); i-- > 0;) {
        const hgp::Run r = f2_pair(m, "sub_3B0030", {sx(lines[i]), 0, 0, 0}, seed++, "release " + std::to_string(i), si);
        CHECK(v0_of(r) == 0);
    }
    CHECK(rs32(m, kCachedGlyphs) == cached0);
    CHECK(rs32(m, kGlyphNodes) == glyphs0);
    CHECK(rs32(m, kLineNodes) == lines0);
    CHECK(slot_list(m, 16).size() == free_before_release);
    int released = 0;
    for (u32 s : slot_list(m, 8)) released += r32(m, s + 16) == 0 ? 1 : 0;
    CHECK(static_cast<std::size_t>(released) == slot_list(m, 8).size() - static_cast<std::size_t>(cached0));
    // slot reuse: a text whose glyphs sit in released slots takes no slot -- only new cache records
    const std::size_t free_reuse = slot_list(m, 16).size();
    const u32 again = build("Velvet Room", 0, "reuse");
    CHECK(slot_list(m, 16).size() == free_reuse);
    if (again) f2_pair(m, "sub_3B0030", {sx(again), 0, 0, 0}, seed++, "release reuse", si);
    CHECK(rs32(m, kCachedGlyphs) == cached0);
    MESSAGE("glyph cache: " << misses_total << " misses, " << hits_total << " hits, " << decoded_checked
                            << " decoded glyphs equal to the host decode of FONT0.FNT");
}

// =====================================================================================================================
// The text layout: the layout loop, the line flush, inserted strings and tag slots, the reveal step and the immediate
// draw, on the dorm snapshot (layout records in free RAM)
// =====================================================================================================================
TEST_CASE("game(font2): the layout loop, inserted strings, the reveal step and the immediate draw") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    if (!load_snapshot(m, "dorm_replay_4900")) {
        MESSAGE("SKIP: no dorm_replay_4900 snapshot under extracted/_ours");
        return;
    }
    write_rw_slots(m);
    g_live.clear();
    Opt si;
    si.standins = true;
    u32 seed = 2000;
    const u32 kLay = kOut, kText = kOut + 0x100;
    const s32 cached0 = rs32(m, kCachedGlyphs), glyphs0 = rs32(m, kGlyphNodes), lines0 = rs32(m, kLineNodes);
    auto layout = [&](const std::string& t, u32 x, u32 y) {
        std::memset(m.at(kLay), 0, 0x30);
        wbytes(m, kText, t);
        w32(m, kLay + 0, x);
        w32(m, kLay + 4, y);
        w32(m, kLay + 8, 0x10 * 7);
        w8(m, kLay + 15, 0x80);
        w32(m, kLay + 16, kText);
        w8(m, kLay + 28, 1);
        w8(m, kLay + 29, 1);
        w16(m, kLay + 30, 0x1234);
    };
    // sub_3B2430 [frFontLayoutText]: plain text -> one line node at (x, y) with the code, alpha and z of the record
    std::vector<u32> chains;
    for (const std::string& t : {std::string("Hello"), std::string("Iwatodai Dormitory"), std::string("A B C")}) {
        layout(t, 0x123, 0x456);
        const hgp::Run r = f2_pair(m, "sub_3B2430", {sx(kLay), 0, 0, 0}, seed++, "layout " + t, si);
        if (r.stopped) continue;
        const u32 line = v0w(r);
        REQUIRE(line != 0);
        chains.push_back(line);
        CHECK(r32(m, kLay + 20) == line);
        CHECK(r16(m, line + 0) == 0x1234);
        CHECK(r8(m, line + 2) == 0x80);
        CHECK(rs32(m, line + 4) == 0x123);
        CHECK(rs32(m, line + 8) == 0x456);
        CHECK(r32(m, line + 20) == 7u);
        CHECK(line_glyphs(m, line).size() == t.size());
        CHECK((r16(m, kGlyphFlags) & 3u) == 2u);  // the layout phase ended
        CHECK(r8(m, kLay + 28) == 0);
        CHECK(r8(m, kLay + 29) == 0);
        // letter spacing -2 * size / 32 (style 0: size 32 -> -2) and the width recomputed with it
        CHECK(static_cast<s8>(r8(m, line + 3)) == -2);
        s32 w = 0;
        for (u32 g : line_glyphs(m, line)) w += rs32(m, g + 12) - 2;
        CHECK(rs32(m, line + 12) == w);
    }
    // sub_3B22A0 [frFontLayoutFlushLine]: a new-line request starts an empty line node with the record's code; a
    // pending position moves it
    if (!chains.empty()) {
        w8(m, kLay + 28, 1);
        w8(m, kLay + 29, 1);
        w32(m, kLay + 0, 0x40);
        w32(m, kLay + 4, 0x80);
        w16(m, kLay + 30, 0x0077);
        const u32 prev = r32(m, kLay + 20);
        const hgp::Run r = f2_pair(m, "sub_3B22A0", {sx(kLay), 0, 0, 0}, seed++, "flush line", si);
        if (!r.stopped) {
            const u32 line = r32(m, kLay + 20);
            CHECK(line != 0);
            CHECK(r8(m, kLay + 28) == 0);
            CHECK(r8(m, kLay + 29) == 0);
            if (line != prev) {
                CHECK(r16(m, line + 0) == 0x0077);
                CHECK(rs32(m, line + 4) == 0x40);
                CHECK(rs32(m, line + 8) == 0x80);
            }
        }
        // sub_3B2020 [frFontLayoutString] / sub_3B1D90 [frFontLayoutTagSlot]: inserted strings append glyphs
        const u32 cur = r32(m, kLay + 20);
        const std::size_t n0 = line_glyphs(m, cur).size();
        wbytes(m, kOut + 0x300, "Yukari");
        const hgp::Run s = f2_pair(m, "sub_3B2020", {sx(kOut + 0x300), sx(kLay), 0, 0}, seed++, "inserted string", si);
        if (!s.stopped) CHECK(line_glyphs(m, r32(m, kLay + 20)).size() == n0 + 6);
        const std::size_t n1 = line_glyphs(m, r32(m, kLay + 20)).size();
        wbytes(m, kOut + 0x340, "Junpei");
        const u32 saved = r32(m, kTagSlots + 4 * 5);
        w32(m, kTagSlots + 4 * 5, kOut + 0x340);
        const hgp::Run t = f2_pair(m, "sub_3B1D90", {5, sx(kLay), 0, 0}, seed++, "tag slot 5", si);
        if (!t.stopped) CHECK(line_glyphs(m, r32(m, kLay + 20)).size() == n1 + 6);
        w32(m, kTagSlots + 4 * 5, saved);
        // sub_3B1710 [frFontChainWaitDone]: no wait tag -> the summed glyph counts of the chain
        const u32 head = chains.front();
        w32(m, head + 44, head);
        w32(m, head + 40, 0);
        w32(m, head + 48, 0);
        const hgp::Run c = f2_pair(m, "sub_3B1710", {sx(head), 0, 0, 0}, seed++, "chain wait done", si);
        if (!c.stopped) CHECK(v0w(c) == r32(m, head + 24));
        // the same with a tick wait (F214) still running: 0
        w32(m, head + 48, 0xF214);
        w32(m, head + 60, 3);
        w32(m, head + 64, 0);
        const hgp::Run c2 = f2_pair(m, "sub_3B1710", {sx(head), 0, 0, 0}, seed++, "chain wait F214", si);
        if (!c2.stopped) CHECK(v0w(c2) == 0);
        w32(m, head + 48, 0);
        // sub_3B0F50 [frFontGlyphRevealStep]: a glyph after a fully shown one gains 32 * speed / (advance + spacing)
        const std::vector<u32> g = line_glyphs(m, head);
        if (g.size() >= 2) {
            w32(m, head + 36, 0);
            w32(m, head + 52, 0);
            w32(m, g[0] + 16, (r32(m, g[0] + 16) & 0xFFFFFF00u) | 0xFF);
            w32(m, g[1] + 16, r32(m, g[1] + 16) & 0xFFFFFF00u);
            w8(m, g[1] + 22, 0);
            const s32 adv = rs32(m, g[1] + 12) + static_cast<s8>(r8(m, head + 3));
            const hgp::Run rv = f2_pair(m, "sub_3B0F50", {sx(head), sx(g[1]), 0, 8}, seed++, "reveal step", si);
            if (!rv.stopped && adv > 0) {
                const int inc = static_cast<int>(static_cast<float>(32 * 8) / static_cast<float>(adv));
                CHECK(r8(m, g[1] + 16) == std::min(255, inc));
                CHECK(v0w(rv) == 0);
            }
            // speed 255 shows it at once
            w32(m, g[1] + 16, r32(m, g[1] + 16) & 0xFFFFFF00u);
            const hgp::Run rv2 = f2_pair(m, "sub_3B0F50", {sx(head), sx(g[1]), 0, 255}, seed++, "reveal at once", si);
            if (!rv2.stopped) CHECK(r8(m, g[1] + 16) == 0xFF);
        }
    }
    // release: the record's current line first -- the flushed line, whose +0x24 leads on to the layout line it was
    // joined to -- then the layouts not on that walk; every node goes back to its ring
    std::set<u32> walked;
    const u32 cur_line = r32(m, kLay + 20);
    for (u32 l = cur_line; l != 0 && walked.size() < 64; l = r32(m, l + 36)) walked.insert(l);
    if (cur_line) f2_pair(m, "sub_3B0030", {sx(cur_line), 0, 0, 0}, seed++, "release the current line", si);
    for (u32 l : chains)
        if (!walked.count(l)) f2_pair(m, "sub_3B0030", {sx(l), 0, 0, 0}, seed++, "release layout", si);
    CHECK(rs32(m, kCachedGlyphs) == cached0);
    CHECK(rs32(m, kGlyphNodes) == glyphs0);
    CHECK(rs32(m, kLineNodes) == lines0);
    MESSAGE("after the layout tests: " << rs32(m, kCachedGlyphs) - cached0 << " cached glyphs, " << rs32(m, kGlyphNodes) - glyphs0
                                       << " glyph nodes, " << rs32(m, kLineNodes) - lines0 << " line nodes more than the snapshot");
}

// =====================================================================================================================
// The font table on the ELF image: font0.fnt through the file stand-ins, the style records against the file, the GS
// list and the raster-slot pool
// =====================================================================================================================
TEST_CASE("game(font2): the font table, the styles, the GS list and the raster-slot pool") {
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
    u32 seed = 3000;
    const Fnt font = host_font("FONT0.FNT");
    // frLoadFontData: font/font0.fnt requested once, bound as style 0, copied to styles 1..5, the scales cleared
    f2_pair(m, "frLoadFontData", {0, 0, 0, 0}, seed++, "frLoadFontData", si);
    const u32 node = r32(m, kStyleCdNodes);
    const u32 fnt = r32(m, kStyles + 4);
    CHECK(node != 0);
    if (!font.b.empty() && fnt != 0) {
        CHECK(std::memcmp(m.at(fnt), font.b.data(), font.b.size()) == 0);
        CHECK(r32(m, kStyles + 0) == fnt);  // the file argument: the style owns the image
        CHECK(r32(m, kStyles + 8) == font.width_bytes());
        CHECK(r32(m, kStyles + 12) == font.block2_bytes());
        CHECK(r32(m, kStyles + 16) == fnt + font.widths());
        CHECK(r32(m, kStyles + 20) == fnt + font.block2());
        CHECK(r32(m, kStyles + 24) == fnt + font.glyph_table());
        CHECK(r32(m, kStyles + 28) == fnt + font.huffman());
        for (u32 s = 1; s < 6; ++s) CHECK(std::memcmp(m.at(kStyles), m.at(kStyles + 32 * s), 32) == 0);
        bool printed = false;
        for (const StandInCall& c : log_of().log)
            if (c.text.find("font trans ADDR=") != std::string::npos) printed = true;
        CHECK(printed);
    } else {
        MESSAGE("note: font0.fnt not loaded (" << (font.b.empty() ? "no host file" : "no guest image") << ")");
    }
    CHECK(r32(m, kGpReg - 0x46B8u) == 0);
    CHECK(r32(m, kGpReg - 0x46B4u) == 0);
    // a second call: style 0 is bound -> the "abort2!!" print, no second request
    f2_pair(m, "frLoadFontData", {0, 0, 0, 0}, seed++, "frLoadFontData again", si);
    CHECK(r32(m, kStyleCdNodes) == node);
    // frAddFontStyle on the other three files (styles 6..8): the record layout of each header
    for (const auto& [name, style] : {std::pair<const char*, u32>{"FONT1.FNT", 6}, {"FONT2.FNT", 7}, {"FONT3.FNT", 8}}) {
        const Fnt f = host_font(name);
        if (f.b.empty()) continue;
        const u32 img = 0x01A00000u + 0x20000u * (style - 6);  // free in the ELF image, below the stand-in heap
        std::memcpy(m.at(img), f.b.data(), f.b.size());
        f2_pair(m, "frAddFontStyle", {style, sx(img), 0, 0}, seed++, std::string("frAddFontStyle ") + name, si);
        const u32 rec = kStyles + 32 * style;
        CHECK(r32(m, rec + 0) == 0);
        CHECK(r32(m, rec + 4) == img);
        CHECK(r32(m, rec + 8) == (f.b[0x16] ? f.width_bytes() : 0u));
        CHECK(r32(m, rec + 24) == img + f.glyph_table());
        CHECK(r32(m, rec + 28) == img + f.huffman());
        // the decoder of the glyph cache reads its glyphs: glyph 0 decodes to w * h / 2 bytes
        const std::vector<u8> g0 = f.decode(0);
        CHECK(g0.size() == static_cast<std::size_t>(f.le16(0x10)) * f.le16(0x12) / 2);
    }
    // frFreeFontStyles: style 0 drops its request and its words; the copies keep their Huffman word, every glyph
    // table word is cleared
    f2_pair(m, "frFreeFontStyles", {0, 0, 0, 0}, seed++, "frFreeFontStyles", si);
    CHECK(r32(m, kStyleCdNodes) == 0);
    CHECK(r32(m, kStyles + 0) == 0);
    CHECK(r32(m, kStyles + 28) == 0);
    for (u32 s = 0; s < 9; ++s) CHECK(r32(m, kStyles + 32 * s + 24) == 0);
    if (fnt) CHECK(r32(m, kStyles + 32 + 28) != 0);
    // sub_3B41A0 [fmGslInit]: 16 x 4 entries of 32 x 32 with 16-byte work records
    w8(m, kGslReady, 0);
    w32(m, kGslList, 0);
    const hgp::Run gi = f2_pair(m, "sub_3B41A0", {0, 16, 4, 32}, seed++, "fmGslInit", [&] {
        Opt o = si;
        o.gpr_in = {{GPR_T0, 32}, {GPR_T0 + 1, 16}};
        return o;
    }());
    if (!gi.stopped) {
        CHECK(v0w(gi) == 1);
        CHECK(r8(m, kGslReady) == 1);
        const u32 e0 = r32(m, kGslList);
        const u32 work = r32(m, 0x95AEA4u);
        REQUIRE(e0 != 0);
        CHECK(rs32(m, 0x95AEB4u) == 64);
        CHECK(rs32(m, 0x95AEB8u) == 64);
        CHECK(rs32(m, 0x95AEB0u) == 32 * 32 / 2);
        for (u32 i = 0; i < 64; ++i) {
            const u32 e = e0 + 32 * i;
            CHECK(r32(m, e + 0) == i);
            CHECK(rs32(m, e + 4) == static_cast<s32>(16 * (i % 16) * 32));
            CHECK(rs32(m, e + 8) == static_cast<s32>(16 * (i / 16) * 32));
            CHECK(rs32(m, e + 12) == rs32(m, e + 4) + 16 * 32);
            CHECK(rs32(m, e + 16) == rs32(m, e + 8) + 16 * 32);
            CHECK(r32(m, e + 20) == work + 16 * i);
            CHECK(r32(m, e + 28) == e0 + 32 * ((i + 1) % 64));  // circular, both ways
            CHECK(r32(m, e + 24) == e0 + 32 * ((i + 63) % 64));
        }
        // set up already: returns 0 and changes nothing
        const hgp::Run g2 = f2_pair(m, "sub_3B41A0", {0, 16, 4, 32}, seed++, "fmGslInit again", si);
        if (!g2.stopped) CHECK(v0w(g2) == 0);
    }
}

// =====================================================================================================================
// The raster-slot pool on the dorm snapshot (a fresh pool of 4 slots in place of the game's), and slot allocation
// =====================================================================================================================
TEST_CASE("game(font2): a raster-slot pool and its allocation on the dorm snapshot") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    if (!load_snapshot(m, "dorm_replay_4900")) {
        MESSAGE("SKIP: no dorm_replay_4900 snapshot under extracted/_ours");
        return;
    }
    write_rw_slots(m);
    g_live.clear();
    Opt si;
    si.standins = true;
    u32 seed = 4000;
    const Fnt font = host_font("FONT0.FNT");
    // frFontRasterAllocSlot on the game's pool: the free head moves to the active tail, the glyph is swizzled into its
    // raster and copied into the slot buffer, glyph / ticks / in-use set, the colour set stored (frFontRasterCreate2)
    if (!font.b.empty()) {
        for (u32 glyph : {33u, 100u, 327u, 503u}) {
            const std::vector<u8> bits = font.decode(glyph);
            REQUIRE(bits.size() == 512);
            std::memcpy(m.at(kOut + 0x1000), bits.data(), 512);
            const u32 head = slot_list(m, 16).front();
            const u32 cs = glyph % 4;
            const hgp::Run r = f2_pair(m, "frFontRasterAllocSlot", {glyph, sx(kOut + 0x1000), cs, 0}, seed++,
                                       "alloc slot glyph " + std::to_string(glyph), si);
            if (r.stopped) continue;
            CHECK(v0w(r) == head);
            CHECK(slot_list(m, 8).back() == head);
            CHECK(r32(m, head + 4) == glyph);
            CHECK(r16(m, head + 8) == cs);
            CHECK(r16(m, head + 10) == 1);
            CHECK((r32(m, head) & 1u) == 1u);
            CHECK(r32(m, head + 16) == 0);
            CHECK(std::memcmp(m.at(r32(m, head + 12)), bits.data(), 512) == 0);
        }
    }
    // frFontRasterCreate: a pool of 4 slots (the old pool word cleared first: one pool at a time)
    w32(m, kPoolWord, 0);
    const hgp::Run pc = f2_pair(m, "frFontRasterCreate", {4, 0, 0, 0}, seed++, "pool of 4", si);
    const u32 pool = r32(m, kPoolWord);
    REQUIRE(pool != 0);
    CHECK(rs32(m, pool + 0) == 4);
    CHECK(r32(m, pool + 4) == pool + 24);
    CHECK(r32(m, pool + 8) == 0);
    CHECK(r32(m, pool + 16) == pool + 24);
    const std::vector<u32> fr = slot_list(m, 16);
    if (!pc.stopped) {
        CHECK(fr.size() == 4);
        for (std::size_t i = 0; i < fr.size(); ++i) {
            CHECK(fr[i] == pool + 24 + 540 * static_cast<u32>(i));  // 28-byte slot + its 512-byte buffer
            CHECK(r32(m, fr[i] + 12) == fr[i] + 28);
            CHECK(r32(m, fr[i] + 20) != 0);  // its 32 x 32 raster
        }
        CHECK(r32(m, pool + 20) == fr.back());
    }
}

// =====================================================================================================================
// The pad layer: the button words, the auto-repeat and the vibration state machine (documented rules per frame)
// =====================================================================================================================
TEST_CASE("game(font2): the pad words, auto-repeat and vibration") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    u32 seed = 5000;
    const u32 rec0 = 0x7E09BCu;  // pad record of port 0 (54 bytes per port)
    // sub_103650 [H_Pad_UpdateButtonWords]: pressed = held & (held ^ previous); the stick as a d-pad
    struct Frame {
        u16 held;
        u8 sx, sy;
    };
    const Frame frames[] = {{0x0000, 0x80, 0x80}, {0x0040, 0x80, 0x80}, {0x0040, 0xC1, 0x80}, {0x1040, 0x3F, 0xFF},
                            {0x0000, 0x40, 0xC0}, {0xF0F0, 0x00, 0x00}, {0xFFFF, 0xFF, 0xFF}};
    u16 prev = 0, prev_stick = 0;
    for (const Frame& f : frames) {
        w16(m, rec0 + 4, prev);
        w16(m, rec0 + 0, f.held);
        w16(m, rec0 + 0x10, prev_stick);
        w8(m, rec0 + 0x12, f.sx);
        w8(m, rec0 + 0x13, f.sy);
        f2_pair(m, "sub_103650", {0, 0, 0, 0}, seed++, "button words");
        u16 stick = f.held & 0xF0;
        if (f.sx >= 0xC1) stick |= 0x2000;
        if (f.sx < 0x40) stick |= 0x8000;
        if (f.sy >= 0xC1) stick |= 0x4000;
        if (f.sy < 0x40) stick |= 0x1000;
        CHECK(r16(m, rec0 + 0x0A) == stick);
        CHECK(r16(m, rec0 + 2) == static_cast<u16>(f.held & (f.held ^ prev)));
        CHECK(r16(m, rec0 + 0x0C) == static_cast<u16>(stick & (stick ^ prev_stick)));
        prev = f.held;
        prev_stick = stick;
    }
    // sub_1038D0 [H_Pad_RepeatButton]: a press arms the counter with 7, holding counts down and repeats every 3
    std::memset(m.at(rec0), 0, 54);
    int repeats = 0;
    for (int frame = 0; frame < 16; ++frame) {
        w16(m, rec0 + 0, 0x0040);
        w16(m, rec0 + 2, frame == 0 ? 0x0040 : 0);
        w16(m, rec0 + 6, 0);
        f2_pair(m, "sub_1038D0", {0, 0x40, 8, 0}, seed++, "repeat frame " + std::to_string(frame));
        const u8 c = r8(m, rec0 + 0x16 + 8);
        if (frame == 0) CHECK(c == 7);
        if (r16(m, rec0 + 6) & 0x40) {
            ++repeats;
            CHECK(c == 3);
        }
    }
    CHECK(repeats == 3);  // frames 7, 10 and 13: the press arms 7, the first repeat after 7 frames, then every 3
    // sub_103B10 [H_Pad_UpdateVibration]: state 0 resets to 1; state 2 pulses on / off then falls back to 1
    w16(m, 0x7CDE90u, 0);
    f2_pair(m, "sub_103B10", {0, 0, 0, 0}, seed++, "vibration reset");
    CHECK(r16(m, 0x7CDE90u) == 1);
    CHECK(r16(m, 0x7E09DEu) == 0);
    w16(m, 0x7CDE90u, 2);
    w16(m, 0x7CDE94u, 0xC8);
    w16(m, 0x7CDE98u, 0);
    w16(m, 0x7CDE9Cu, 1);  // off frames
    w16(m, 0x7CDEA0u, 2);  // on frames
    w16(m, 0x7CDEA4u, 0);
    w16(m, 0x7CDEA8u, 6);  // pulse frames
    std::string seen;
    for (int frame = 0; frame < 9; ++frame) {
        f2_pair(m, "sub_103B10", {0, 0, 0, 0}, seed++, "vibration frame " + std::to_string(frame));
        seen += r16(m, 0x7E09DEu) ? '1' : '0';
        CHECK(r16(m, 0x7E09DEu) == r16(m, 0x7E09E0u));
    }
    CHECK(r16(m, 0x7CDE90u) == 1);
    // on 2 frames (+ the one that switches), off 1, ... six phase frames, then the state falls back to 1 (off)
    CHECK(seen == "111001100");
    // sub_103580 [H_Pad_UpdateAll] with the pad driver stood in: the edge words cleared, the analogue bytes centred
    for (u32 a : {0x7E09F2u, 0x7E09F4u, 0x7E09F8u, 0x7E09FCu, 0x7E09FEu}) w16(m, a, 0xFFFF);
    for (u32 a = 0x7E0A04u; a < 0x7E0A08u; ++a) w8(m, a, 0x11);
    Opt pd;
    pd.standins = true;
    pd.recorders = {{0x103110u, "H_Pad_UpdateWorkPad", 0}};
    f2_pair(m, "sub_103580", {0, 0, 0, 0}, seed++, "pad update", pd);
    CHECK(log_of().calls_to(0x103110u) == 2);
    for (u32 a : {0x7E09F2u, 0x7E09F4u, 0x7E09F8u, 0x7E09FCu, 0x7E09FEu}) CHECK(r16(m, a) == 0);
    for (u32 a = 0x7E0A04u; a < 0x7E0A08u; ++a) CHECK(r8(m, a) == 0x80);
}

// =====================================================================================================================
// The TMX copiers, the bust-up records, the sound and fade leaves, the cut-in / effect task works and the sprite draws
// =====================================================================================================================
TEST_CASE("game(font2): TMX copiers, bust-up records, sound leaves, effect works and sprite draws") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    write_rw_slots(m);
    g_live.clear();
    u32 seed = 6000;
    // --- the TMX copiers on a 4 x 3 image (+4 w, +8 h, +0x10 stride, +0x14 pixels, +0x18 palette, +0xC depth) ---
    const u32 img = kOut, pix = kOut + 0x100, src = kOut + 0x400, pal = kOut + 0x800;
    auto image = [&](u32 w, u32 h, u32 stride, u32 depth) {
        std::memset(m.at(img), 0, 0x20);
        w32(m, img + 4, w);
        w32(m, img + 8, h);
        w32(m, img + 12, depth);
        w32(m, img + 16, stride);
        w32(m, img + 20, pix);
        w32(m, img + 24, pal);
        std::memset(m.at(pix), 0xEE, 0x200);
    };
    for (u32 i = 0; i < 0x300; ++i) w8(m, src + i, static_cast<u8>(i * 37 + 11));
    image(4, 3, 16, 32);
    f2_pair(m, "sub_10DD10", {sx(img), sx(src), 0, 0}, seed++, "copy 32");
    for (u32 y = 0; y < 3; ++y)
        for (u32 x = 0; x < 4; ++x) {
            const u32 s = src + 4 * (4 * y + x), d = pix + 16 * y + 4 * x;
            CHECK(r8(m, d) == r8(m, s));
            CHECK(r8(m, d + 2) == r8(m, s + 2));
            const u8 a = r8(m, s + 3);
            CHECK(r8(m, d + 3) == (a < 0x7F ? static_cast<u8>((255 * a) >> 7) : 0xFF));
        }
    image(4, 3, 16, 24);
    f2_pair(m, "sub_10DDC0", {sx(img), sx(src), 0, 0}, seed++, "copy 24");
    CHECK(r8(m, pix + 16 + 4 + 1) == r8(m, src + 3 * 5 + 1));
    CHECK(r8(m, pix + 3) == 0xFF);
    image(4, 3, 16, 16);
    f2_pair(m, "sub_10DE40", {sx(img), sx(src), 0, 0}, seed++, "copy 16");
    {
        const u16 p = r16(m, src + 2 * 5);
        CHECK(r8(m, pix + 16 + 4) == static_cast<u8>((p & 0x1F) << 3));
        CHECK(r8(m, pix + 16 + 5) == static_cast<u8>(((p >> 5) & 0x1F) << 3));
        CHECK(r8(m, pix + 16 + 6) == static_cast<u8>(((p >> 10) & 0x1F) << 3));
    }
    image(8, 2, 8, 4);
    f2_pair(m, "sub_10DEE0", {sx(img), sx(src), 0, 0}, seed++, "copy 4");
    CHECK(r8(m, pix + 8 + 2) == (r8(m, src + 5) & 0xF));
    CHECK(r8(m, pix + 8 + 3) == (r8(m, src + 5) >> 4));
    image(4, 3, 16, 4);
    f2_pair(m, "sub_10DF60", {sx(img), sx(src), 0, 0}, seed++, "palette 32");
    for (u32 i = 0; i < 16; ++i) {
        const u8 a = r8(m, src + 4 * i + 3);
        CHECK(r8(m, pal + 4 * i + 3) == (a < 0x7F ? static_cast<u8>((255 * a) / 128) : 0xFF));
    }
    std::vector<u8> before(m.at(pal), m.at(pal) + 1024);
    f2_pair(m, "sub_10E010", {sx(img), 8, 0, 0}, seed++, "palette CSM1 swap");
    for (u32 i = 0; i < 256; ++i) {
        const u32 k = i & 0x1F;
        const u32 from = (k >= 8 && k < 16) ? i + 8 : (k >= 16 && k < 24) ? i - 8 : i;
        CHECK(std::memcmp(m.at(pal + 4 * i), before.data() + 4 * from, 4) == 0);
    }
    // --- the bust-up record setters (record 1) ---
    const u32 bu = 0x7E2680u + 1648u;
    f2_pair(m, "sub_106E90", {1, 0x5A, 0, 0}, seed++, "bust alpha");
    CHECK(r8(m, bu + 0x523) == 0x5A);
    f2_pair(m, "sub_106EC0", {1, 7, 0, 0}, seed++, "bust fade");
    CHECK(r32(m, bu + 0x550) == 7);
    CHECK(r32(m, bu + 0x558) == 1);
    CHECK(r32(m, bu + 0x55C) == 2);
    CHECK(r32(m, bu + 0x560) == 0);
    f2_pair(m, "sub_106F30", {1, 3, 0, 0}, seed++, "bust +0x554");
    CHECK(r32(m, bu + 0x554) == 3);
    w16(m, bu, 3);
    f2_pair(m, "sub_106F60", {1, 9, 0, 0}, seed++, "bust pose");
    CHECK(r16(m, bu) == 4);
    CHECK(r16(m, bu + 2) == 9);
    f2_pair(m, "sub_106FB0", {1, 0x0000002000000010ull, 0, 0}, seed++, "bust pos");
    CHECK(r32(m, bu + 0xC) == 0x10);
    CHECK(r32(m, bu + 0x10) == 0x20);
    w16(m, bu, 3);
    CHECK(v0w(f2_pair(m, "sub_106FF0", {1, 0, 0, 0}, seed++, "bust ready")) == 1);
    w16(m, bu, 2);
    CHECK(v0w(f2_pair(m, "sub_106FF0", {1, 0, 0, 0}, seed++, "bust not ready")) == 0);
    f2_pair(m, "sub_105800", {0, 0, 0, 0}, seed++, "bust init");
    for (u32 r = 0; r < 3; ++r) CHECK(r16(m, 0x7E2680u + 1648 * r) == 0);
    // --- the sound / fade leaves ---
    for (u32 active : {0u, 1u}) {
        w32(m, 0x7E4430u, active);
        w16(m, 0x7E4438u, 0x2A);
        CHECK(static_cast<s32>(v0w(f2_pair(m, "sub_108E50", {0, 0, 0, 0}, seed++, "bgm id"))) == (active ? 0x2A : -1));
        CHECK(static_cast<s32>(v0w(f2_pair(m, "sub_1099A0", {0, 0, 0, 0}, seed++, "bgm id 2"))) == (active ? 0x2A : -1));
    }
    f2_pair(m, "sub_108680", {0x11, 0x22, 0x33, 0}, seed++, "fade colour");
    CHECK(r8(m, 0x7CDEF8u) == 0x11);
    CHECK(r8(m, 0x7CDEF4u) == 0x22);
    CHECK(r8(m, 0x7CDEF0u) == 0x33);
    // sub_10A500: channels 0, 1, 5 never busy; an active channel is busy unless its stream is in state 3
    for (u32 stat : {1u, 3u}) {
        Opt o;
        o.standins = true;
        o.recorders = {{0x54D148u, "ADXT_GetStat", stat}};
        for (u32 ch : {0u, 1u, 2u, 4u, 5u}) {
            w32(m, 0x7E4430u + 308 * ch, 1);
            w32(m, 0x7E4440u + 308 * ch, 0x1234);
            const u32 busy = v0w(f2_pair(m, "sub_10A500", {ch, 0, 0, 0}, seed++, "channel busy", o));
            const bool expect = !(ch == 0 || ch == 1 || ch == 5) && stat != 3;
            CHECK(busy == (expect ? 1u : 0u));
        }
    }
    // --- the effect / cut-in works (fake tasks: the work word +0x3C) ---
    const u32 task = kOut + 0x2000, work = kOut + 0x2100;
    std::memset(m.at(work), 0, 0x800);
    w32(m, task + 60, work);
    for (const auto& [fn, state, want] : {std::tuple<const char*, u32, u32>{"sub_116760", 3, 1}, {"sub_116760", 2, 0},
                                         {"sub_116ED0", 3, 1}, {"sub_119380", 3, 1}, {"sub_119380", 4, 0}}) {
        w32(m, work, state);
        CHECK(v0w(f2_pair(m, fn, {sx(task), 0, 0, 0}, seed++, fn)) == want);
    }
    for (const char* fn : {"sub_116780", "sub_116EF0", "sub_1193A0"}) {
        w32(m, work, 3);
        f2_pair(m, fn, {sx(task), 0, 0, 0}, seed++, fn);
        CHECK(r32(m, work) == 4);
    }
    for (const auto& [st, ok] : {std::pair<u32, u32>{2, 1}, {3, 0}}) {
        w32(m, work, st);
        CHECK(v0w(f2_pair(m, "sub_1104D0", {sx(task), 0, 0, 0}, seed++, "cut-in start")) == ok);
        CHECK(r32(m, work) == 3);
        CHECK(v0w(f2_pair(m, "sub_1104B0", {sx(task), 0, 0, 0}, seed++, "cut-in loaded")) == 1);
    }
    w32(m, work + 100, 49);
    CHECK(v0w(f2_pair(m, "sub_116F30", {sx(task), 0, 0, 0}, seed++, "past hit 49")) == 0);
    w32(m, work + 100, 50);
    CHECK(v0w(f2_pair(m, "sub_116F30", {sx(task), 0, 0, 0}, seed++, "past hit 50")) == 1);
    CHECK(v0w(f2_pair(m, "sub_116F20", {sx(task), 0, 0, 0}, seed++, "frame")) == 50);
    CHECK(v0w(f2_pair(m, "sub_116F10", {0, 0, 0, 0}, seed++, "length 1")) == 63);
    CHECK(v0w(f2_pair(m, "sub_1193C0", {0, 0, 0, 0}, seed++, "length 2")) == 40);
    w32(m, work + 104 + 8, 77);
    CHECK(v0w(f2_pair(m, "sub_1167C0", {sx(task), 2, 0, 0}, seed++, "effect 0 frame 2")) == 77);
    CHECK(v0w(f2_pair(m, "sub_1167C0", {sx(task), 0, 0, 0}, seed++, "effect 0 frame 0")) == 51);
    f2_pair(m, "sub_111520", {sx(task), 0x1F4, 0, 0}, seed++, "cut-in end frame");
    CHECK(r16(m, work + 210) == 0x1F4);
    f2_pair(m, "sub_111570", {sx(task), 2, 0, 0}, seed++, "cut-in blend");
    CHECK(r32(m, work + 772) == 2);
    f2_pair(m, "sub_110620", {sx(task), 3, 10, 20, }, seed++, "layer colour", [] {
        Opt o;
        o.gpr_in = {{GPR_T0, 30}};
        return o;
    }());
    CHECK(r16(m, work + 1008 + 6) == 10);
    CHECK(r16(m, work + 1088 + 6) == 20);
    CHECK(r16(m, work + 1168 + 6) == 30);
    const u32 ras = kOut + 0x3000;
    w32(m, ras + 80, 0xAABBCCDDu);
    f2_pair(m, "sub_1105D0", {sx(task), 5, sx(ras), 0}, seed++, "cut-in raster");
    CHECK(r32(m, work + 808 + 20) == ras);
    CHECK(r32(m, ras + 80) == 0xAABBCC02u);
    f2_pair(m, "sub_1105D0", {sx(task), 40, sx(ras), 0}, seed++, "cut-in raster 40 (ignored)");
    CHECK(r32(m, work + 808 + 160) == 0);
}

// =====================================================================================================================
// The cut-in / persona-effect task creators and the one-shot sprite draws on the dorm snapshot (a live task kernel,
// the stand-in heap behind RwCalloc / RwFree, sprintf on the stand-ins)
// =====================================================================================================================
TEST_CASE("game(font2): effect task creators and one-shot sprite draws on the dorm snapshot") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    if (!load_snapshot(m, "dorm_replay_4900")) {
        MESSAGE("SKIP: no dorm_replay_4900 snapshot under extracted/_ours");
        return;
    }
    write_rw_slots(m);
    g_live.clear();
    u32 seed = 7000;
    Opt si;
    si.standins = true;
    struct Creator {
        const char* fn;
        u32 size;
        Args args;
    };
    const u32 parent = 0;
    for (const Creator& c : {Creator{"sub_111150", 788, {parent, 0x0004000300020001ull, 0, 0}},
                             Creator{"sub_111260", 788, {parent, 0x0004000300020001ull, 0x55, 0}},
                             Creator{"sub_111380", 788, {parent, 6000, 0x0004000300020001ull, 0x66}},
                             Creator{"sub_1166A0", 2740, {parent, 9, 3, 0}}, Creator{"sub_116E20", 1852, {parent, 4, 0, 0}},
                             Creator{"sub_117490", 88, {parent, 0x77, 0, 0}}, Creator{"sub_119960", 88, {parent, 0x12, 0x34, 0}},
                             Creator{"sub_1103E0", 1260, {parent, 6336, 0x99, 3}}}) {
        const hgp::Run r = f2_pair(m, c.fn, c.args, seed++, c.fn, si);
        if (r.stopped) continue;
        // RwCalloc(1, size, 0x40000) for the work
        bool found = false;
        for (const StandInCall& call : log_of().log)
            if (call.va == kRwSlotFns[3] && call.args[0] == 1u && call.args[1] == c.size && call.args[2] == 0x40000u) found = true;
        CHECK(found);
        const u32 t = v0w(r);
        if (t == 0) continue;
        const u32 w = r32(m, t + 60);
        REQUIRE(w != 0);
        const std::string name = c.fn;
        if (name == "sub_111150" || name == "sub_111260" || name == "sub_111380") {
            CHECK(r16(m, w + 168) == 1);
            CHECK(r16(m, w + 174) == 4);
            CHECK(gstr(m, w + 252) == "battle/cutin/c01_23" + std::string("04.cpk"));
            CHECK(gstr(m, w + 508) == "battle/cutin/");
            CHECK(r32(m, w + 784) == (name == "sub_111150" ? 1u : 0u));
            if (name != "sub_111150") CHECK(r32(m, w + 200) == (name == "sub_111260" ? 0x55u : 0x66u));
            if (name == "sub_111380") CHECK(r32(m, w + 780) == 6000);
        } else if (name == "sub_1166A0") {
            CHECK(r32(m, w + 4) == 9);
            CHECK(r32(m, w + 8) == 3);
        } else if (name == "sub_116E20") {
            CHECK(r32(m, w + 4) == 4);
        } else if (name == "sub_117490") {
            CHECK(r32(m, w + 16) == 0x77);
        } else if (name == "sub_119960") {
            CHECK(r32(m, w + 4) == 0x12);
            CHECK(r32(m, w + 84) == 0x34);
        } else if (name == "sub_1103E0") {
            CHECK(r32(m, w + 4) == 0x99);
            CHECK(r32(m, w + 1248) == 3);
        }
    }
    // sub_115CD0 [sprDrawSpriteBasic4]: a handle made by sprCreateHandle (hand-written since slice unblock: it runs, so the
    // handle is the 52-byte block it takes through the RW calloc slot -- one such call -- with the caller's $a1 / $a2 as
    // its file / sprite words, linked at the tail of the sprite-handle list 0x7CDF3C), its fields from the arguments,
    // drawn, unlinked and freed.
    // (sub_115DE0, its scaled twin, stays recompiled: test_ui6 stands it in.)
    const u32 file = r32(m, kGpReg - 0x469Cu);  // facility/i_mes_win01.spr (frFontSystemStart)
    constexpr u32 kSprHandles = 0x7CDF3Cu;      // the sprite-handle list head
    for (const char* fn : {"sub_115CD0"}) {
        const u32 head0 = r32(m, kSprHandles);
        Opt o = si;
        const bool five = std::string(fn) == "sub_115DE0";
        if (five) o.gpr_in = {{GPR_T0, 0x01}, {GPR_T0 + 1, 0x10}, {GPR_T0 + 2, 0x20}, {GPR_T0 + 3, 0x30}};
        else o.gpr_in = {{GPR_T0, 0x10}, {GPR_T0 + 1, 0x20}, {GPR_T0 + 2, 0x30}};
        o.fpr = {{12, fbits(64.0f)}, {13, fbits(48.0f)}, {14, fbits(3.0f)}};
        const hgp::Run r = f2_pair(m, fn, {sx(file), 0x10, 0, five ? 0x0800u : 0x01u}, seed++, fn, o);
        if (r.stopped) continue;
        // sprCreateHandle's block: RwCalloc(1, 52, 0x40000), the only calloc of the run
        u32 h = 0, made = 0;
        for (const StandInCall& c : log_of().log)
            if (c.va == kRwSlotFns[3]) {
                ++made;
                CHECK(c.args[0] == 1u);
                CHECK(c.args[1] == 52u);
                CHECK(c.args[2] == 0x40000u);
                h = static_cast<u32>(c.v0);
            }
        CHECK(made == 1u);
        REQUIRE(h != 0u);
        // sprCreateHandle(0, $a1, $a2) with sub_115CD0's own $a1 / $a2 (0x10 and 0 here): the handle's file / sprite words
        CHECK(r32(m, h + 8) == 0x10u);
        CHECK(r32(m, h + 12) == 0u);
        CHECK(r32(m, kSprHandles) == head0);  // unlinked again after the draw
        CHECK(r32(m, h + 16) == fbits(64.0f));
        CHECK(r32(m, h + 20) == fbits(48.0f));
        CHECK(r32(m, h + 44) == fbits(3.0f));
        CHECK(r8(m, h + 24) == 0x01);
        CHECK(r8(m, h + 48) == 0x10);
        CHECK(r8(m, h + 49) == 0x20);
        CHECK(r8(m, h + 50) == 0x30);
        if (five) {
            CHECK(r16(m, h + 40) == 0x0800);
            CHECK(r16(m, h + 42) == 0x0800);
        }
        bool freed = false;
        for (const StandInCall& c : log_of().log)
            if (c.va == kRwSlotFns[1] && static_cast<u32>(c.args[0]) == h) freed = true;
        CHECK(freed);
    }
}

// =====================================================================================================================
// The debug print queue, the bust-up request / release, the sprite fonts and a TMX image from extracted/DATA/FONT
// =====================================================================================================================
TEST_CASE("game(font2): debug print queue, bust-up request, sprite fonts and a TMX image") {
    auto mp = std::make_unique<Machine>();
    Machine& m = *mp;
    if (const char* err = m.load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    write_rw_slots(m);
    g_live.clear();
    u32 seed = 8000;
    Opt si;
    si.standins = true;
    // sub_1040F0 [H_ChkMem_GetHooks]: the hook table the RW memory slots point into
    const hgp::Run hk = f2_pair(m, "sub_1040F0", {0, 0, 0, 0}, seed++, "memory hooks");
    CHECK(v0w(hk) == 0x7E0A20u);
    for (u32 i = 0; i < 4; ++i) CHECK(r32(m, 0x7E0A20u + 4 * i) == kRwSlotFns[i]);
    // sub_104FD0 / sub_104EB0 [dbgPrintF / dbgPrintColourF]: 280-byte nodes appended at the list's tail
    const u32 list = 0x7CDEC8u;
    w32(m, list, 0);
    wbytes(m, kOut, "HP %d");
    wbytes(m, kOut + 0x40, "%s/%s");
    wbytes(m, kOut + 0x80, "Yukari");
    wbytes(m, kOut + 0xC0, "Junpei");
    const u64 xy = static_cast<u64>(fbits(48.0f)) << 32 | 16u;
    f2_pair(m, "sub_104FD0", {xy, sx(kOut), 42, 0}, seed++, "dbgPrintF", si);
    const u32 n0 = r32(m, list);
    REQUIRE(n0 != 0);
    CHECK(gstr(m, n0 + 16) == "HP 42");
    CHECK(r32(m, n0 + 4) == 16u);
    CHECK(r32(m, n0 + 8) == fbits(48.0f));
    CHECK(r32(m, n0 + 276) == 0xFFFFFFFFu);
    CHECK(r32(m, n0 + 0) == 0);
    f2_pair(m, "sub_104EB0", {xy, 0x11223344u, sx(kOut + 0x40), sx(kOut + 0x80)}, seed++, "dbgPrintColourF", [&] {
        Opt o = si;
        o.gpr_in = {{GPR_T0, kOut + 0xC0}};
        return o;
    }());
    const u32 n1 = r32(m, n0);
    REQUIRE(n1 != 0);
    CHECK(gstr(m, n1 + 16) == "Yukari/Junpei");
    CHECK(r32(m, n1 + 276) == 0x11223344u);
    // sub_1043B0 [dbgPrintClear]: both nodes freed, the list empty, the 2,120-byte screen all spaces
    f2_pair(m, "sub_1043B0", {0, 0, 0, 0}, seed++, "dbgPrintClear", si);
    CHECK(r32(m, list) == 0);
    CHECK(log_of().calls_to(kRwSlotFns[1]) == 2);
    bool spaces = true;
    for (u32 i = 0; i < 2120; ++i) spaces = spaces && r8(m, 0x7E1E30u + i) == ' ';
    CHECK(spaces);
    // sub_106860 [H_ChrDsp_Request] and sub_106730 [H_ChrDsp_Release] on bust-up record 0 (file loading off: the
    // request stays pending)
    {
        Opt o = si;
        o.load = false;
        const u32 rec = 0x7E2680u;
        f2_pair(m, "sub_106860", {0, 1, 3, 2}, seed++, "bust-up request", o);
        CHECK(r16(m, rec) == 1);
        CHECK(r16(m, rec + 4) == 1);
        CHECK(r16(m, rec + 8) == 3);
        CHECK(r16(m, rec + 10) == 2);
        CHECK(r32(m, rec + 0x528) != 0);  // the request
        CHECK(gstr(m, rec + 0x568).rfind("bustup/", 0) == 0);
        CHECK(r32(m, rec + 0x520) == 0xFFFFFFFFu);
        CHECK(r32(m, rec + 0x52C) == fbits(1.0f));
        CHECK(r32(m, rec + 0x530) == fbits(1.0f));
        CHECK(r32(m, rec + 0x564) == 1);
        MESSAGE("bust-up 1/3/2 -> " << gstr(m, rec + 0x568));
        f2_pair(m, "sub_106730", {0, 0, 0, 0}, seed++, "bust-up release", o);
        CHECK(r16(m, rec) == 0);
        CHECK(r32(m, rec + 0x528) == 0);
        bool printed = false;
        for (const StandInCall& c : log_of().log) printed = printed || c.text == "!!! RELEASE CHAR 0\n";
        CHECK(printed);
    }
    // sprFontInit: the three sprite fonts of camp/font through the file stand-ins, registered in sSprFontFiles
    {
        // sprFileHandleUpdate (not emitted here; ui4 left it recompiled for other tests) stood in: the file is ready
        Opt o = si;
        o.customs = {{0x112110u, "sprFileHandleUpdate", [](EEContext& ctx, StandIns&, StandInCall& c) {
                          const u16 ready = 5;
                          std::memcpy(ctx.memory->main_ram() + (static_cast<u32>(c.args[0]) & 0x1FFFFFFu), &ready, 2);
                          c.v0 = 0;
                      }}};
        const hgp::Run r = f2_pair(m, "sprFontInit", {0, 0, 0, 0}, seed++, "sprFontInit", o);
        if (!r.stopped) {
            const char* names[3] = {"camp/font/i_font01a.spr", "camp/font/i_font02a.spr", "camp/font/i_font02b.spr"};
            for (u32 i = 0; i < 3; ++i) {
                const u32 f = r32(m, 0x833A40u + 4 * i);
                REQUIRE(f != 0);
                CHECK(gstr(m, f + 2) == names[i]);
                CHECK(r16(m, f) == 5);  // loaded
            }
        }
    }
    // sub_10E0D0 [uttmxImageFromTmx] on DATA/FONT/FSU_00.TMX (256 x 256 PSMT4 with a 16-entry PSMCT32 palette; its
    // header patched to 64 x 16 in guest memory so the unpack stays under the pair's 20,000 check points):
    // the image made by the hand-written RwImageCreate / RwImageAllocatePixels (render_rw4 / render_rw5) on the dorm
    // snapshot's live RW image module, the memory on the stand-in heap; the palette and the 4-bit unpack checked against
    // the file
    const std::vector<u8> tmx = read_host_file(extracted_root() + "/DATA/FONT/FSU_00.TMX");
    if (tmx.size() == 64 + 64 + 256 * 128 && load_snapshot(m, "dorm_replay_4900")) {
        write_rw_slots(m);
        g_live.clear();
        const u32 data = 0x01A00000u;
        std::memcpy(m.at(data), tmx.data(), tmx.size());
        w16(m, data + 18, 64);
        w16(m, data + 20, 16);
        const hgp::Run r = f2_pair(m, "sub_10E0D0", {sx(data), 0, 0, 0}, seed++, "TMX -> image", si);
        if (!r.stopped) {
            const u32 image = v0w(r);
            REQUIRE(image != 0);
            CHECK(r32(m, image + 4) == 64);
            CHECK(r32(m, image + 8) == 16);
            CHECK(r32(m, image + 12) == 4);
            const u32 pix = r32(m, image + 20), pal = r32(m, image + 24), stride = r32(m, image + 16);
            REQUIRE(pix != 0);
            REQUIRE(pal != 0);
            for (u32 i = 0; i < 16; ++i) {
                CHECK(std::memcmp(m.at(pal + 4 * i), tmx.data() + 64 + 4 * i, 3) == 0);
                const u8 a = tmx[64 + 4 * i + 3];
                CHECK(r8(m, pal + 4 * i + 3) == (a < 0x7F ? static_cast<u8>((255 * a) / 128) : 0xFF));
            }
            int bad = 0;
            for (u32 y = 0; y < 16; ++y)
                for (u32 x = 0; x < 32; ++x) {
                    const u8 b = tmx[128 + 32 * y + x];
                    bad += r8(m, pix + stride * y + 2 * x) != (b & 0xF);
                    bad += r8(m, pix + stride * y + 2 * x + 1) != (b >> 4);
                }
            CHECK(bad == 0);
        }
    } else {
        MESSAGE("note: DATA/FONT/FSU_00.TMX (or the dorm snapshot) not found: the TMX check is skipped");
    }
}

TEST_CASE("game(font2): pair count") { MESSAGE("font2 pairs run (outside the random-world case): " << g_pairs << ", " << g_stops << " stopped early in both bodies"); }

#else

TEST_CASE("game(font2): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
