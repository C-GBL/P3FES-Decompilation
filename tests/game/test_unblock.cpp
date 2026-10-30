// Pair tests of slice unblock (game/src/unblock/unblock_*.cpp): the functions other slices' pair tests used to stand in
// with recorders. Every body against its recompiled body (tests/game/handgen_pairs.h: the whole register file and cycles
// at every check point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS window, the bus log), on
//   * random worlds: the p3fes_handgen sweep of all 104 bodies;
//   * random worlds on the stand-ins (stand_ins.h: the heap behind the RW slots and H_Malloc, printf / sprintf /
//     vsprintf, the H_Cdvd layer), every callee this build does not emit served by a recorder (found automatically), so
//     every body runs past its first call: whole RAM, the dead stack and every register at every check point compared,
//     and the stand-ins' call logs;
//   * documented rules on the host: the sprite-handle list (create at the tail / after a parent, unlink at the head /
//     middle / tail, the RW calloc / free calls), the debug text grid, the h_fade.c record, the facility request table's
//     bit fields, the NPC reset, and the C runtime against the host's own (fabs, isinf, isnan, strncmp's sign, cos /
//     sin within one ulp, __fixunssfdi and fptodp exactly, the double compare).
// Each random draw is its own statement (MSVC and clang-cl evaluate the arguments of one call in different orders).
#include "field6_util.h"

#include "p3fes/game/unblock.h"

#include <cmath>
#include <map>
#include <cstring>
#include <limits>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::f6t;

namespace p3fes::recomp_gen {
void fn_H_Cursor_CreateTask_001005b0(EEContext&);  // generated body
void fn_H_Cursor_CreateTask_001005b0__recomp(EEContext&);  // recompiled
void fn_sub_103C30_00103c30(EEContext&);  // generated body
void fn_sub_103C30_00103c30__recomp(EEContext&);  // recompiled
void fn_sub_103CB0_00103cb0(EEContext&);  // generated body
void fn_sub_103CB0_00103cb0__recomp(EEContext&);  // recompiled
void fn_sub_104D10_00104d10(EEContext&);  // generated body
void fn_sub_104D10_00104d10__recomp(EEContext&);  // recompiled
void fn_sub_1071B0_001071b0(EEContext&);  // generated body
void fn_sub_1071B0_001071b0__recomp(EEContext&);  // recompiled
void fn_sub_108570_00108570(EEContext&);  // generated body
void fn_sub_108570_00108570__recomp(EEContext&);  // recompiled
void fn_sub_1085C0_001085c0(EEContext&);  // generated body
void fn_sub_1085C0_001085c0__recomp(EEContext&);  // recompiled
void fn_sub_108670_00108670(EEContext&);  // generated body
void fn_sub_108670_00108670__recomp(EEContext&);  // recompiled
void fn_sub_1086A0_001086a0(EEContext&);  // generated body
void fn_sub_1086A0_001086a0__recomp(EEContext&);  // recompiled
void fn_sub_1086D0_001086d0(EEContext&);  // generated body
void fn_sub_1086D0_001086d0__recomp(EEContext&);  // recompiled
void fn_sub_108710_00108710(EEContext&);  // generated body
void fn_sub_108710_00108710__recomp(EEContext&);  // recompiled
void fn_sub_10A4E0_0010a4e0(EEContext&);  // generated body
void fn_sub_10A4E0_0010a4e0__recomp(EEContext&);  // recompiled
void fn_sub_10A770_0010a770(EEContext&);  // generated body
void fn_sub_10A770_0010a770__recomp(EEContext&);  // recompiled
void fn_sub_10BC20_0010bc20(EEContext&);  // generated body
void fn_sub_10BC20_0010bc20__recomp(EEContext&);  // recompiled
void fn_sub_10BDA0_0010bda0(EEContext&);  // generated body
void fn_sub_10BDA0_0010bda0__recomp(EEContext&);  // recompiled
void fn_sub_110F80_00110f80(EEContext&);  // generated body
void fn_sub_110F80_00110f80__recomp(EEContext&);  // recompiled
void fn_sub_1114B0_001114b0(EEContext&);  // generated body
void fn_sub_1114B0_001114b0__recomp(EEContext&);  // recompiled
void fn_sub_111500_00111500(EEContext&);  // generated body
void fn_sub_111500_00111500__recomp(EEContext&);  // recompiled
void fn_sub_111530_00111530(EEContext&);  // generated body
void fn_sub_111530_00111530__recomp(EEContext&);  // recompiled
void fn_sub_111580_00111580(EEContext&);  // generated body
void fn_sub_111580_00111580__recomp(EEContext&);  // recompiled
void fn_sub_111CA0_00111ca0(EEContext&);  // generated body
void fn_sub_111CA0_00111ca0__recomp(EEContext&);  // recompiled
void fn_sub_111F00_00111f00(EEContext&);  // generated body
void fn_sub_111F00_00111f00__recomp(EEContext&);  // recompiled
void fn_sub_111F10_00111f10(EEContext&);  // generated body
void fn_sub_111F10_00111f10__recomp(EEContext&);  // recompiled
void fn_sprCreateHandle_001158b0(EEContext&);  // generated body
void fn_sprCreateHandle_001158b0__recomp(EEContext&);  // recompiled
void fn_sub_115980_00115980(EEContext&);  // generated body
void fn_sub_115980_00115980__recomp(EEContext&);  // recompiled
void fn_sub_115DE0_00115de0(EEContext&);  // generated body
void fn_sub_115DE0_00115de0__recomp(EEContext&);  // recompiled
void fn_sub_16D2F0_0016d2f0(EEContext&);  // generated body
void fn_sub_16D2F0_0016d2f0__recomp(EEContext&);  // recompiled
void fn_sub_16DBC0_0016dbc0(EEContext&);  // generated body
void fn_sub_16DBC0_0016dbc0__recomp(EEContext&);  // recompiled
void fn_sub_250CF0_00250cf0(EEContext&);  // generated body
void fn_sub_250CF0_00250cf0__recomp(EEContext&);  // recompiled
void fn_sub_25F570_0025f570(EEContext&);  // generated body
void fn_sub_25F570_0025f570__recomp(EEContext&);  // recompiled
void fn_sub_2FF260_002ff260(EEContext&);  // generated body
void fn_sub_2FF260_002ff260__recomp(EEContext&);  // recompiled
void fn_sub_3580B0_003580b0(EEContext&);  // generated body
void fn_sub_3580B0_003580b0__recomp(EEContext&);  // recompiled
void fn_sub_37CF50_0037cf50(EEContext&);  // generated body
void fn_sub_37CF50_0037cf50__recomp(EEContext&);  // recompiled
void fn_sub_3B32D0_003b32d0(EEContext&);  // generated body
void fn_sub_3B32D0_003b32d0__recomp(EEContext&);  // recompiled
void fn_sub_3C7850_003c7850(EEContext&);  // generated body
void fn_sub_3C7850_003c7850__recomp(EEContext&);  // recompiled
void fn_sub_3C7C90_003c7c90(EEContext&);  // generated body
void fn_sub_3C7C90_003c7c90__recomp(EEContext&);  // recompiled
void fn_sub_3C83B0_003c83b0(EEContext&);  // generated body
void fn_sub_3C83B0_003c83b0__recomp(EEContext&);  // recompiled
void fn_sub_3CF120_003cf120(EEContext&);  // generated body
void fn_sub_3CF120_003cf120__recomp(EEContext&);  // recompiled
void fn_sub_3CF3A0_003cf3a0(EEContext&);  // generated body
void fn_sub_3CF3A0_003cf3a0__recomp(EEContext&);  // recompiled
void fn_sub_3CF440_003cf440(EEContext&);  // generated body
void fn_sub_3CF440_003cf440__recomp(EEContext&);  // recompiled
void fn_sub_3CF5D0_003cf5d0(EEContext&);  // generated body
void fn_sub_3CF5D0_003cf5d0__recomp(EEContext&);  // recompiled
void fn_sub_3EB9B0_003eb9b0(EEContext&);  // generated body
void fn_sub_3EB9B0_003eb9b0__recomp(EEContext&);  // recompiled
void fn_sub_3EC030_003ec030(EEContext&);  // generated body
void fn_sub_3EC030_003ec030__recomp(EEContext&);  // recompiled
void fn_sub_3ED380_003ed380(EEContext&);  // generated body
void fn_sub_3ED380_003ed380__recomp(EEContext&);  // recompiled
void fn_sub_3EE670_003ee670(EEContext&);  // generated body
void fn_sub_3EE670_003ee670__recomp(EEContext&);  // recompiled
void fn_sub_3EED50_003eed50(EEContext&);  // generated body
void fn_sub_3EED50_003eed50__recomp(EEContext&);  // recompiled
void fn_sub_3EF970_003ef970(EEContext&);  // generated body
void fn_sub_3EF970_003ef970__recomp(EEContext&);  // recompiled
void fn_sub_3F00B0_003f00b0(EEContext&);  // generated body
void fn_sub_3F00B0_003f00b0__recomp(EEContext&);  // recompiled
void fn_sub_3F04F0_003f04f0(EEContext&);  // generated body
void fn_sub_3F04F0_003f04f0__recomp(EEContext&);  // recompiled
void fn_sub_3F0AC0_003f0ac0(EEContext&);  // generated body
void fn_sub_3F0AC0_003f0ac0__recomp(EEContext&);  // recompiled
void fn_sub_3F0EC0_003f0ec0(EEContext&);  // generated body
void fn_sub_3F0EC0_003f0ec0__recomp(EEContext&);  // recompiled
void fn_sub_3F12A0_003f12a0(EEContext&);  // generated body
void fn_sub_3F12A0_003f12a0__recomp(EEContext&);  // recompiled
void fn_sub_3F1520_003f1520(EEContext&);  // generated body
void fn_sub_3F1520_003f1520__recomp(EEContext&);  // recompiled
void fn_sub_3F1690_003f1690(EEContext&);  // generated body
void fn_sub_3F1690_003f1690__recomp(EEContext&);  // recompiled
void fn_sub_3F5830_003f5830(EEContext&);  // generated body
void fn_sub_3F5830_003f5830__recomp(EEContext&);  // recompiled
void fn_sub_3F9E30_003f9e30(EEContext&);  // generated body
void fn_sub_3F9E30_003f9e30__recomp(EEContext&);  // recompiled
void fn_sub_3FD8A0_003fd8a0(EEContext&);  // generated body
void fn_sub_3FD8A0_003fd8a0__recomp(EEContext&);  // recompiled
void fn_sub_3FDF80_003fdf80(EEContext&);  // generated body
void fn_sub_3FDF80_003fdf80__recomp(EEContext&);  // recompiled
void fn_sub_3FE2B0_003fe2b0(EEContext&);  // generated body
void fn_sub_3FE2B0_003fe2b0__recomp(EEContext&);  // recompiled
void fn_sub_4003F0_004003f0(EEContext&);  // generated body
void fn_sub_4003F0_004003f0__recomp(EEContext&);  // recompiled
void fn_sub_400E90_00400e90(EEContext&);  // generated body
void fn_sub_400E90_00400e90__recomp(EEContext&);  // recompiled
void fn_sub_401890_00401890(EEContext&);  // generated body
void fn_sub_401890_00401890__recomp(EEContext&);  // recompiled
void fn_sub_401950_00401950(EEContext&);  // generated body
void fn_sub_401950_00401950__recomp(EEContext&);  // recompiled
void fn_sub_402480_00402480(EEContext&);  // generated body
void fn_sub_402480_00402480__recomp(EEContext&);  // recompiled
void fn_sub_403380_00403380(EEContext&);  // generated body
void fn_sub_403380_00403380__recomp(EEContext&);  // recompiled
void fn_sub_403520_00403520(EEContext&);  // generated body
void fn_sub_403520_00403520__recomp(EEContext&);  // recompiled
void fn_sub_403610_00403610(EEContext&);  // generated body
void fn_sub_403610_00403610__recomp(EEContext&);  // recompiled
void fn_sub_403740_00403740(EEContext&);  // generated body
void fn_sub_403740_00403740__recomp(EEContext&);  // recompiled
void fn_sub_403800_00403800(EEContext&);  // generated body
void fn_sub_403800_00403800__recomp(EEContext&);  // recompiled
void fn_sub_403830_00403830(EEContext&);  // generated body
void fn_sub_403830_00403830__recomp(EEContext&);  // recompiled
void fn_sub_403880_00403880(EEContext&);  // generated body
void fn_sub_403880_00403880__recomp(EEContext&);  // recompiled
void fn_sub_4038A0_004038a0(EEContext&);  // generated body
void fn_sub_4038A0_004038a0__recomp(EEContext&);  // recompiled
void fn_sub_403900_00403900(EEContext&);  // generated body
void fn_sub_403900_00403900__recomp(EEContext&);  // recompiled
void fn_sub_403920_00403920(EEContext&);  // generated body
void fn_sub_403920_00403920__recomp(EEContext&);  // recompiled
void fn_sub_40C170_0040c170(EEContext&);  // generated body
void fn_sub_40C170_0040c170__recomp(EEContext&);  // recompiled
void fn_sub_40C310_0040c310(EEContext&);  // generated body
void fn_sub_40C310_0040c310__recomp(EEContext&);  // recompiled
void fn_sub_40C490_0040c490(EEContext&);  // generated body
void fn_sub_40C490_0040c490__recomp(EEContext&);  // recompiled
void fn_sub_434F70_00434f70(EEContext&);  // generated body
void fn_sub_434F70_00434f70__recomp(EEContext&);  // recompiled
void fn_sub_45EC00_0045ec00(EEContext&);  // generated body
void fn_sub_45EC00_0045ec00__recomp(EEContext&);  // recompiled
void fn_sub_469A90_00469a90(EEContext&);  // generated body
void fn_sub_469A90_00469a90__recomp(EEContext&);  // recompiled
void fn_sub_474210_00474210(EEContext&);  // generated body
void fn_sub_474210_00474210__recomp(EEContext&);  // recompiled
void fn_sub_474640_00474640(EEContext&);  // generated body
void fn_sub_474640_00474640__recomp(EEContext&);  // recompiled
void fn_sub_4747F0_004747f0(EEContext&);  // generated body
void fn_sub_4747F0_004747f0__recomp(EEContext&);  // recompiled
void fn_sub_48D270_0048d270(EEContext&);  // generated body
void fn_sub_48D270_0048d270__recomp(EEContext&);  // recompiled
void fn_sub_491A80_00491a80(EEContext&);  // generated body
void fn_sub_491A80_00491a80__recomp(EEContext&);  // recompiled
void fn_sub_492D10_00492d10(EEContext&);  // generated body
void fn_sub_492D10_00492d10__recomp(EEContext&);  // recompiled
void fn_sub_494CC0_00494cc0(EEContext&);  // generated body
void fn_sub_494CC0_00494cc0__recomp(EEContext&);  // recompiled
void fn_sub_494D50_00494d50(EEContext&);  // generated body
void fn_sub_494D50_00494d50__recomp(EEContext&);  // recompiled
void fn_sub_4CA030_004ca030(EEContext&);  // generated body
void fn_sub_4CA030_004ca030__recomp(EEContext&);  // recompiled
void fn_sub_4D0BE0_004d0be0(EEContext&);  // generated body
void fn_sub_4D0BE0_004d0be0__recomp(EEContext&);  // recompiled
void fn_sub_4D1840_004d1840(EEContext&);  // generated body
void fn_sub_4D1840_004d1840__recomp(EEContext&);  // recompiled
void fn_sub_4E3E40_004e3e40(EEContext&);  // generated body
void fn_sub_4E3E40_004e3e40__recomp(EEContext&);  // recompiled
void fn_sub_4E3EC0_004e3ec0(EEContext&);  // generated body
void fn_sub_4E3EC0_004e3ec0__recomp(EEContext&);  // recompiled
void fn_sub_4E3F20_004e3f20(EEContext&);  // generated body
void fn_sub_4E3F20_004e3f20__recomp(EEContext&);  // recompiled
void fn_sub_4E3FC0_004e3fc0(EEContext&);  // generated body
void fn_sub_4E3FC0_004e3fc0__recomp(EEContext&);  // recompiled
void fn_sub_4E4020_004e4020(EEContext&);  // generated body
void fn_sub_4E4020_004e4020__recomp(EEContext&);  // recompiled
void fn_isinf_00523730(EEContext&);  // generated body
void fn_isinf_00523730__recomp(EEContext&);  // recompiled
void fn_isnan_00523778(EEContext&);  // generated body
void fn_isnan_00523778__recomp(EEContext&);  // recompiled
void fn_strncmp_00524670(EEContext&);  // generated body
void fn_strncmp_00524670__recomp(EEContext&);  // recompiled
void fn_cos_0052e038(EEContext&);  // generated body
void fn_cos_0052e038__recomp(EEContext&);  // recompiled
void fn_fabs_0052e118(EEContext&);  // generated body
void fn_fabs_0052e118__recomp(EEContext&);  // recompiled
void fn_sin_0052e328(EEContext&);  // generated body
void fn_sin_0052e328__recomp(EEContext&);  // recompiled
void fn___fixunssfdi_0052eda0(EEContext&);  // generated body
void fn___fixunssfdi_0052eda0__recomp(EEContext&);  // recompiled
void fn_fptodp_00530da0(EEContext&);  // generated body
void fn_fptodp_00530da0__recomp(EEContext&);  // recompiled
void fn_datSetFlag_0016f1f0(EEContext&);  // emitted / hand-written: the flag writer
void fn_datGetFlag_0016f190(EEContext&);  // the flag reader
}  // namespace p3fes::recomp_gen

namespace {

namespace rg = p3fes::recomp_gen;

const Case kCases[] = {
    {"H_Cursor_CreateTask", 0x1005B0, &recomp_gen::fn_H_Cursor_CreateTask_001005b0, &recomp_gen::fn_H_Cursor_CreateTask_001005b0__recomp},
    {"sub_103C30", 0x103C30, &recomp_gen::fn_sub_103C30_00103c30, &recomp_gen::fn_sub_103C30_00103c30__recomp},
    {"sub_103CB0", 0x103CB0, &recomp_gen::fn_sub_103CB0_00103cb0, &recomp_gen::fn_sub_103CB0_00103cb0__recomp},
    {"sub_104D10", 0x104D10, &recomp_gen::fn_sub_104D10_00104d10, &recomp_gen::fn_sub_104D10_00104d10__recomp},
    {"sub_1071B0", 0x1071B0, &recomp_gen::fn_sub_1071B0_001071b0, &recomp_gen::fn_sub_1071B0_001071b0__recomp},
    {"sub_108570", 0x108570, &recomp_gen::fn_sub_108570_00108570, &recomp_gen::fn_sub_108570_00108570__recomp},
    {"sub_1085C0", 0x1085C0, &recomp_gen::fn_sub_1085C0_001085c0, &recomp_gen::fn_sub_1085C0_001085c0__recomp},
    {"sub_108670", 0x108670, &recomp_gen::fn_sub_108670_00108670, &recomp_gen::fn_sub_108670_00108670__recomp},
    {"sub_1086A0", 0x1086A0, &recomp_gen::fn_sub_1086A0_001086a0, &recomp_gen::fn_sub_1086A0_001086a0__recomp},
    {"sub_1086D0", 0x1086D0, &recomp_gen::fn_sub_1086D0_001086d0, &recomp_gen::fn_sub_1086D0_001086d0__recomp},
    {"sub_108710", 0x108710, &recomp_gen::fn_sub_108710_00108710, &recomp_gen::fn_sub_108710_00108710__recomp},
    {"sub_10A4E0", 0x10A4E0, &recomp_gen::fn_sub_10A4E0_0010a4e0, &recomp_gen::fn_sub_10A4E0_0010a4e0__recomp},
    {"sub_10A770", 0x10A770, &recomp_gen::fn_sub_10A770_0010a770, &recomp_gen::fn_sub_10A770_0010a770__recomp},
    {"sub_10BC20", 0x10BC20, &recomp_gen::fn_sub_10BC20_0010bc20, &recomp_gen::fn_sub_10BC20_0010bc20__recomp},
    {"sub_10BDA0", 0x10BDA0, &recomp_gen::fn_sub_10BDA0_0010bda0, &recomp_gen::fn_sub_10BDA0_0010bda0__recomp},
    {"sub_110F80", 0x110F80, &recomp_gen::fn_sub_110F80_00110f80, &recomp_gen::fn_sub_110F80_00110f80__recomp},
    {"sub_1114B0", 0x1114B0, &recomp_gen::fn_sub_1114B0_001114b0, &recomp_gen::fn_sub_1114B0_001114b0__recomp},
    {"sub_111500", 0x111500, &recomp_gen::fn_sub_111500_00111500, &recomp_gen::fn_sub_111500_00111500__recomp},
    {"sub_111530", 0x111530, &recomp_gen::fn_sub_111530_00111530, &recomp_gen::fn_sub_111530_00111530__recomp},
    {"sub_111580", 0x111580, &recomp_gen::fn_sub_111580_00111580, &recomp_gen::fn_sub_111580_00111580__recomp},
    {"sub_111CA0", 0x111CA0, &recomp_gen::fn_sub_111CA0_00111ca0, &recomp_gen::fn_sub_111CA0_00111ca0__recomp},
    {"sub_111F00", 0x111F00, &recomp_gen::fn_sub_111F00_00111f00, &recomp_gen::fn_sub_111F00_00111f00__recomp},
    {"sub_111F10", 0x111F10, &recomp_gen::fn_sub_111F10_00111f10, &recomp_gen::fn_sub_111F10_00111f10__recomp},
    {"sprCreateHandle", 0x1158B0, &recomp_gen::fn_sprCreateHandle_001158b0, &recomp_gen::fn_sprCreateHandle_001158b0__recomp},
    {"sub_115980", 0x115980, &recomp_gen::fn_sub_115980_00115980, &recomp_gen::fn_sub_115980_00115980__recomp},
    {"sub_115DE0", 0x115DE0, &recomp_gen::fn_sub_115DE0_00115de0, &recomp_gen::fn_sub_115DE0_00115de0__recomp},
    {"sub_16D2F0", 0x16D2F0, &recomp_gen::fn_sub_16D2F0_0016d2f0, &recomp_gen::fn_sub_16D2F0_0016d2f0__recomp},
    {"sub_16DBC0", 0x16DBC0, &recomp_gen::fn_sub_16DBC0_0016dbc0, &recomp_gen::fn_sub_16DBC0_0016dbc0__recomp},
    {"sub_250CF0", 0x250CF0, &recomp_gen::fn_sub_250CF0_00250cf0, &recomp_gen::fn_sub_250CF0_00250cf0__recomp},
    {"sub_25F570", 0x25F570, &recomp_gen::fn_sub_25F570_0025f570, &recomp_gen::fn_sub_25F570_0025f570__recomp},
    {"sub_2FF260", 0x2FF260, &recomp_gen::fn_sub_2FF260_002ff260, &recomp_gen::fn_sub_2FF260_002ff260__recomp},
    {"sub_3580B0", 0x3580B0, &recomp_gen::fn_sub_3580B0_003580b0, &recomp_gen::fn_sub_3580B0_003580b0__recomp},
    {"sub_37CF50", 0x37CF50, &recomp_gen::fn_sub_37CF50_0037cf50, &recomp_gen::fn_sub_37CF50_0037cf50__recomp},
    {"sub_3B32D0", 0x3B32D0, &recomp_gen::fn_sub_3B32D0_003b32d0, &recomp_gen::fn_sub_3B32D0_003b32d0__recomp},
    {"sub_3C7850", 0x3C7850, &recomp_gen::fn_sub_3C7850_003c7850, &recomp_gen::fn_sub_3C7850_003c7850__recomp},
    {"sub_3C7C90", 0x3C7C90, &recomp_gen::fn_sub_3C7C90_003c7c90, &recomp_gen::fn_sub_3C7C90_003c7c90__recomp},
    {"sub_3C83B0", 0x3C83B0, &recomp_gen::fn_sub_3C83B0_003c83b0, &recomp_gen::fn_sub_3C83B0_003c83b0__recomp},
    {"sub_3CF120", 0x3CF120, &recomp_gen::fn_sub_3CF120_003cf120, &recomp_gen::fn_sub_3CF120_003cf120__recomp},
    {"sub_3CF3A0", 0x3CF3A0, &recomp_gen::fn_sub_3CF3A0_003cf3a0, &recomp_gen::fn_sub_3CF3A0_003cf3a0__recomp},
    {"sub_3CF440", 0x3CF440, &recomp_gen::fn_sub_3CF440_003cf440, &recomp_gen::fn_sub_3CF440_003cf440__recomp},
    {"sub_3CF5D0", 0x3CF5D0, &recomp_gen::fn_sub_3CF5D0_003cf5d0, &recomp_gen::fn_sub_3CF5D0_003cf5d0__recomp},
    {"sub_3EB9B0", 0x3EB9B0, &recomp_gen::fn_sub_3EB9B0_003eb9b0, &recomp_gen::fn_sub_3EB9B0_003eb9b0__recomp},
    {"sub_3EC030", 0x3EC030, &recomp_gen::fn_sub_3EC030_003ec030, &recomp_gen::fn_sub_3EC030_003ec030__recomp},
    {"sub_3ED380", 0x3ED380, &recomp_gen::fn_sub_3ED380_003ed380, &recomp_gen::fn_sub_3ED380_003ed380__recomp},
    {"sub_3EE670", 0x3EE670, &recomp_gen::fn_sub_3EE670_003ee670, &recomp_gen::fn_sub_3EE670_003ee670__recomp},
    {"sub_3EED50", 0x3EED50, &recomp_gen::fn_sub_3EED50_003eed50, &recomp_gen::fn_sub_3EED50_003eed50__recomp},
    {"sub_3EF970", 0x3EF970, &recomp_gen::fn_sub_3EF970_003ef970, &recomp_gen::fn_sub_3EF970_003ef970__recomp},
    {"sub_3F00B0", 0x3F00B0, &recomp_gen::fn_sub_3F00B0_003f00b0, &recomp_gen::fn_sub_3F00B0_003f00b0__recomp},
    {"sub_3F04F0", 0x3F04F0, &recomp_gen::fn_sub_3F04F0_003f04f0, &recomp_gen::fn_sub_3F04F0_003f04f0__recomp},
    {"sub_3F0AC0", 0x3F0AC0, &recomp_gen::fn_sub_3F0AC0_003f0ac0, &recomp_gen::fn_sub_3F0AC0_003f0ac0__recomp},
    {"sub_3F0EC0", 0x3F0EC0, &recomp_gen::fn_sub_3F0EC0_003f0ec0, &recomp_gen::fn_sub_3F0EC0_003f0ec0__recomp},
    {"sub_3F12A0", 0x3F12A0, &recomp_gen::fn_sub_3F12A0_003f12a0, &recomp_gen::fn_sub_3F12A0_003f12a0__recomp},
    {"sub_3F1520", 0x3F1520, &recomp_gen::fn_sub_3F1520_003f1520, &recomp_gen::fn_sub_3F1520_003f1520__recomp},
    {"sub_3F1690", 0x3F1690, &recomp_gen::fn_sub_3F1690_003f1690, &recomp_gen::fn_sub_3F1690_003f1690__recomp},
    {"sub_3F5830", 0x3F5830, &recomp_gen::fn_sub_3F5830_003f5830, &recomp_gen::fn_sub_3F5830_003f5830__recomp},
    {"sub_3F9E30", 0x3F9E30, &recomp_gen::fn_sub_3F9E30_003f9e30, &recomp_gen::fn_sub_3F9E30_003f9e30__recomp},
    {"sub_3FD8A0", 0x3FD8A0, &recomp_gen::fn_sub_3FD8A0_003fd8a0, &recomp_gen::fn_sub_3FD8A0_003fd8a0__recomp},
    {"sub_3FDF80", 0x3FDF80, &recomp_gen::fn_sub_3FDF80_003fdf80, &recomp_gen::fn_sub_3FDF80_003fdf80__recomp},
    {"sub_3FE2B0", 0x3FE2B0, &recomp_gen::fn_sub_3FE2B0_003fe2b0, &recomp_gen::fn_sub_3FE2B0_003fe2b0__recomp},
    {"sub_4003F0", 0x4003F0, &recomp_gen::fn_sub_4003F0_004003f0, &recomp_gen::fn_sub_4003F0_004003f0__recomp},
    {"sub_400E90", 0x400E90, &recomp_gen::fn_sub_400E90_00400e90, &recomp_gen::fn_sub_400E90_00400e90__recomp},
    {"sub_401890", 0x401890, &recomp_gen::fn_sub_401890_00401890, &recomp_gen::fn_sub_401890_00401890__recomp},
    {"sub_401950", 0x401950, &recomp_gen::fn_sub_401950_00401950, &recomp_gen::fn_sub_401950_00401950__recomp},
    {"sub_402480", 0x402480, &recomp_gen::fn_sub_402480_00402480, &recomp_gen::fn_sub_402480_00402480__recomp},
    {"sub_403380", 0x403380, &recomp_gen::fn_sub_403380_00403380, &recomp_gen::fn_sub_403380_00403380__recomp},
    {"sub_403520", 0x403520, &recomp_gen::fn_sub_403520_00403520, &recomp_gen::fn_sub_403520_00403520__recomp},
    {"sub_403610", 0x403610, &recomp_gen::fn_sub_403610_00403610, &recomp_gen::fn_sub_403610_00403610__recomp},
    {"sub_403740", 0x403740, &recomp_gen::fn_sub_403740_00403740, &recomp_gen::fn_sub_403740_00403740__recomp},
    {"sub_403800", 0x403800, &recomp_gen::fn_sub_403800_00403800, &recomp_gen::fn_sub_403800_00403800__recomp},
    {"sub_403830", 0x403830, &recomp_gen::fn_sub_403830_00403830, &recomp_gen::fn_sub_403830_00403830__recomp},
    {"sub_403880", 0x403880, &recomp_gen::fn_sub_403880_00403880, &recomp_gen::fn_sub_403880_00403880__recomp},
    {"sub_4038A0", 0x4038A0, &recomp_gen::fn_sub_4038A0_004038a0, &recomp_gen::fn_sub_4038A0_004038a0__recomp},
    {"sub_403900", 0x403900, &recomp_gen::fn_sub_403900_00403900, &recomp_gen::fn_sub_403900_00403900__recomp},
    {"sub_403920", 0x403920, &recomp_gen::fn_sub_403920_00403920, &recomp_gen::fn_sub_403920_00403920__recomp},
    {"sub_40C170", 0x40C170, &recomp_gen::fn_sub_40C170_0040c170, &recomp_gen::fn_sub_40C170_0040c170__recomp},
    {"sub_40C310", 0x40C310, &recomp_gen::fn_sub_40C310_0040c310, &recomp_gen::fn_sub_40C310_0040c310__recomp},
    {"sub_40C490", 0x40C490, &recomp_gen::fn_sub_40C490_0040c490, &recomp_gen::fn_sub_40C490_0040c490__recomp},
    {"sub_434F70", 0x434F70, &recomp_gen::fn_sub_434F70_00434f70, &recomp_gen::fn_sub_434F70_00434f70__recomp},
    {"sub_45EC00", 0x45EC00, &recomp_gen::fn_sub_45EC00_0045ec00, &recomp_gen::fn_sub_45EC00_0045ec00__recomp},
    {"sub_469A90", 0x469A90, &recomp_gen::fn_sub_469A90_00469a90, &recomp_gen::fn_sub_469A90_00469a90__recomp},
    {"sub_474210", 0x474210, &recomp_gen::fn_sub_474210_00474210, &recomp_gen::fn_sub_474210_00474210__recomp},
    {"sub_474640", 0x474640, &recomp_gen::fn_sub_474640_00474640, &recomp_gen::fn_sub_474640_00474640__recomp},
    {"sub_4747F0", 0x4747F0, &recomp_gen::fn_sub_4747F0_004747f0, &recomp_gen::fn_sub_4747F0_004747f0__recomp},
    {"sub_48D270", 0x48D270, &recomp_gen::fn_sub_48D270_0048d270, &recomp_gen::fn_sub_48D270_0048d270__recomp},
    {"sub_491A80", 0x491A80, &recomp_gen::fn_sub_491A80_00491a80, &recomp_gen::fn_sub_491A80_00491a80__recomp},
    {"sub_492D10", 0x492D10, &recomp_gen::fn_sub_492D10_00492d10, &recomp_gen::fn_sub_492D10_00492d10__recomp},
    {"sub_494CC0", 0x494CC0, &recomp_gen::fn_sub_494CC0_00494cc0, &recomp_gen::fn_sub_494CC0_00494cc0__recomp},
    {"sub_494D50", 0x494D50, &recomp_gen::fn_sub_494D50_00494d50, &recomp_gen::fn_sub_494D50_00494d50__recomp},
    {"sub_4CA030", 0x4CA030, &recomp_gen::fn_sub_4CA030_004ca030, &recomp_gen::fn_sub_4CA030_004ca030__recomp},
    {"sub_4D0BE0", 0x4D0BE0, &recomp_gen::fn_sub_4D0BE0_004d0be0, &recomp_gen::fn_sub_4D0BE0_004d0be0__recomp},
    {"sub_4D1840", 0x4D1840, &recomp_gen::fn_sub_4D1840_004d1840, &recomp_gen::fn_sub_4D1840_004d1840__recomp},
    {"sub_4E3E40", 0x4E3E40, &recomp_gen::fn_sub_4E3E40_004e3e40, &recomp_gen::fn_sub_4E3E40_004e3e40__recomp},
    {"sub_4E3EC0", 0x4E3EC0, &recomp_gen::fn_sub_4E3EC0_004e3ec0, &recomp_gen::fn_sub_4E3EC0_004e3ec0__recomp},
    {"sub_4E3F20", 0x4E3F20, &recomp_gen::fn_sub_4E3F20_004e3f20, &recomp_gen::fn_sub_4E3F20_004e3f20__recomp},
    {"sub_4E3FC0", 0x4E3FC0, &recomp_gen::fn_sub_4E3FC0_004e3fc0, &recomp_gen::fn_sub_4E3FC0_004e3fc0__recomp},
    {"sub_4E4020", 0x4E4020, &recomp_gen::fn_sub_4E4020_004e4020, &recomp_gen::fn_sub_4E4020_004e4020__recomp},
    {"isinf", 0x523730, &recomp_gen::fn_isinf_00523730, &recomp_gen::fn_isinf_00523730__recomp},
    {"isnan", 0x523778, &recomp_gen::fn_isnan_00523778, &recomp_gen::fn_isnan_00523778__recomp},
    {"strncmp", 0x524670, &recomp_gen::fn_strncmp_00524670, &recomp_gen::fn_strncmp_00524670__recomp},
    {"cos", 0x52E038, &recomp_gen::fn_cos_0052e038, &recomp_gen::fn_cos_0052e038__recomp},
    {"fabs", 0x52E118, &recomp_gen::fn_fabs_0052e118, &recomp_gen::fn_fabs_0052e118__recomp},
    {"sin", 0x52E328, &recomp_gen::fn_sin_0052e328, &recomp_gen::fn_sin_0052e328__recomp},
    {"__fixunssfdi", 0x52EDA0, &recomp_gen::fn___fixunssfdi_0052eda0, &recomp_gen::fn___fixunssfdi_0052eda0__recomp},
    {"fptodp", 0x530DA0, &recomp_gen::fn_fptodp_00530da0, &recomp_gen::fn_fptodp_00530da0__recomp},
};

const Case& fc(const char* name) { return find_case(kCases, name); }

constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 48;

// --- a body with chosen FPU arguments: both bodies of a pair go through the same trampoline --------------------------
struct Tramp {
    Fn fn[2] = {};
    std::map<unsigned, u32> fpr;
};
Tramp g_t;
template <int K>
void tramp(EEContext& c) {
    for (const auto& [i, v] : g_t.fpr) c.fpr[i] = v;
    g_t.fn[K](c);
}
hgp::Run pair_fpr(Machine& m, const char* name, const Args& a, std::map<unsigned, u32> fpr, u32 seed) {
    const Case& c = fc(name);
    g_t.fn[0] = c.hand;
    g_t.fn[1] = c.recomp;
    g_t.fpr = std::move(fpr);
    return hgp::pair(m, &tramp<0>, &tramp<1>, a, seed, name);
}
u32 fbits(f32 f) {
    u32 b;
    std::memcpy(&b, &f, 4);
    return b;
}
u64 dbits(double d) {
    u64 b;
    std::memcpy(&b, &d, 8);
    return b;
}
double dfrom(u64 b) {
    double d;
    std::memcpy(&d, &b, 8);
    return d;
}
u64 v0w(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }

std::unique_ptr<Machine> elf_machine() {
    auto m = std::make_unique<Machine>();
    if (m->load_elf(elf_path()) != nullptr) return nullptr;
    write_rw_slots(*m);
    return m;
}

// A pair on the stand-ins with every not-emitted callee served by a recorder (added on each missing-function stop and
// the pair run again from the same world).
SiPair si_pair(Machine& m, const Case& c, const Args& a, u32 seed, std::vector<u32>& absent, const std::function<void(Machine&)>& prepare) {
    for (int tries = 0;; ++tries) {
        prepare(m);
        try {
            const std::vector<u32> list = absent;
            return run_pair_si(m, c.hand, c.recomp, a, seed, c.name, whole_ram_check(), [list](StandInWorld& w) {
                install_field_world(w);
                for (u32 va : list) w.si.install_recorder(va, "absent", 0);
            });
        } catch (const rt_test::FatalEvent& e) {
            const std::size_t k = e.what.find("function at 0x");
            if (k == std::string::npos || tries >= 32) throw;
            absent.push_back(static_cast<u32>(std::stoul(e.what.substr(k + 12, 10), nullptr, 16)));
        }
    }
}

}  // namespace

TEST_CASE("game(unblock): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, kWorld, kWorldSize, kSeeds);
}

TEST_CASE("game(unblock): every body equals its recompiled body on random worlds with the stand-ins") {
    auto mp = elf_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF at " << elf_path());
        return;
    }
    Machine& m = *mp;
    const char* only = std::getenv("P3FES_HG_ONLY");
    int pairs = 0, faults = 0;
    std::size_t calls = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        std::vector<u32> absent;
        for (u32 seed = 1; seed <= 6; ++seed) {
            std::mt19937 rng{seed * 104729u + c.addr};
            const u32 world_seed = rng();
            const u64 a0 = hgp::random_arg(rng, kWorld, kWorldSize);
            const u64 a1 = hgp::random_arg(rng, kWorld, kWorldSize);
            const u64 a2 = hgp::random_arg(rng, kWorld, kWorldSize);
            const u64 a3 = hgp::random_arg(rng, kWorld, kWorldSize);
            const auto world = [world_seed](Machine& mm) {
                std::mt19937 wr{world_seed};
                hgp::random_world(mm, kWorld, kWorldSize, wr);
            };
            bool fallback = false;
            try {
                const SiPair p = si_pair(m, c, {a0, a1, a2, a3}, seed, absent, world);
                calls += p.recomp->si.log.size();
            } catch (const rt_test::FatalEvent&) {
                fallback = true;  // a fault (an address error on a random pointer) stops the stand-in pair
            } catch (const std::exception&) {
                fallback = true;  // a poll of a recorder that never answers (the stand-in log's limit)
            }
            if (fallback) {
                // the same world paired with the stops compared instead (both bodies must stop at the same instruction
                // with the same registers and memory)
                world(m);
                hgp::pair(m, c.hand, c.recomp, {a0, a1, a2, a3}, seed, c.name);
                ++faults;
            }
            ++pairs;
        }
    }
    MESSAGE("stand-in sweep: " << pairs << " pairs (" << faults << " faulting worlds paired with their stops), " << calls << " stand-in calls");
    CHECK(pairs > 0);
}

// sprCreateHandle(parent, file, sprite) / sub_115980 (the release): the 52-byte handle comes from RwCalloc(1, 52,
// 0x40000) on the stand-in heap; with no parent it is appended at the tail of the list gp-19892 (0x7CDF3C), with one it
// is linked after it; the release unlinks it (the head when it has no previous one) and hands it to RwFree.
TEST_CASE("game(unblock): the sprite handle list -- create at the tail or after a parent, release anywhere") {
    auto mp = elf_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF at " << elf_path());
        return;
    }
    Machine& m = *mp;
    constexpr u32 kHead = 0x7CDF3Cu;
    namespace spr = game::ub::spr;
    std::mt19937 rng{0x1158B0u};
    int made = 0, released = 0;
    for (int it = 0; it < 40; ++it) {
        // a list of 0..4 handles built in scratch memory
        const u32 n = rng() % 5;
        const u32 base = kScratch + 0x100u * static_cast<u32>(it % 16);
        std::memset(m.at(base), 0, 0x100);
        u32 prev = 0;
        for (u32 i = 0; i < n; ++i) {
            const u32 h = base + 0x40u * i;
            w32(m, h + spr::kPrev, prev);
            if (prev) w32(m, prev + spr::kNext, h);
            prev = h;
        }
        w32(m, kHead, n ? base : 0u);
        const u32 file = kScratch + 0x2000u + 4u * (rng() % 64);
        const u32 sprite = rng() % 200;
        const bool with_parent = n != 0 && rng() % 3 == 0;
        const u32 parent = with_parent ? base + 0x40u * (rng() % n) : 0u;
        const SiPair p = run_pair_si(m, fc("sprCreateHandle").hand, fc("sprCreateHandle").recomp, {parent, file, sprite, 0},
                                     static_cast<u32>(it), "sprCreateHandle", whole_ram_check());
        const u32 h = static_cast<u32>(p.hw.recomp.base.v0);
        REQUIRE(p.recomp->si.calls_to(kRwSlotFns[3]) == 1);
        const StandInCall& c = p.recomp->si.log[0];
        CHECK(c.args[0] == 1u);
        CHECK(c.args[1] == static_cast<u64>(spr::kSize));
        CHECK(c.args[2] == 0x40000u);
        CHECK(h == static_cast<u32>(c.v0));
        CHECK(r32(m, h + spr::kFile) == file);
        CHECK(r32(m, h + spr::kSprite) == sprite);
        for (u32 k = 0; k < 3; ++k) CHECK(r8(m, h + spr::kRgb + k) == 0xFFu);
        if (with_parent) {
            CHECK(r32(m, parent + spr::kNext) == h);
            CHECK(r32(m, h + spr::kPrev) == parent);
        } else if (n == 0) {
            CHECK(r32(m, kHead) == h);
            CHECK(r32(m, h + spr::kPrev) == 0u);
        } else {
            const u32 tail = base + 0x40u * (n - 1);
            CHECK(r32(m, tail + spr::kNext) == h);
            CHECK(r32(m, h + spr::kPrev) == tail);
            CHECK(r32(m, kHead) == base);
        }
        ++made;
        // release one handle of the list (head, middle or tail), the list rebuilt first
        if (n == 0) continue;
        std::memset(m.at(base), 0, 0x100);
        prev = 0;
        for (u32 i = 0; i < n; ++i) {
            const u32 x = base + 0x40u * i;
            w32(m, x + spr::kPrev, prev);
            if (prev) w32(m, prev + spr::kNext, x);
            prev = x;
        }
        w32(m, kHead, base);
        const u32 victim_index = rng() % n;
        const u32 victim = base + 0x40u * victim_index;
        const SiPair q = run_pair_si(m, fc("sub_115980").hand, fc("sub_115980").recomp, {victim, 0, 0, 0},
                                     static_cast<u32>(1000 + it), "sub_115980", whole_ram_check());
        REQUIRE(q.recomp->si.calls_to(kRwSlotFns[1]) == 1);
        CHECK(static_cast<u32>(q.recomp->si.log[0].args[0]) == victim);
        const u32 before = victim_index ? victim - 0x40u : 0u;
        const u32 after = victim_index + 1 < n ? victim + 0x40u : 0u;
        if (before) CHECK(r32(m, before + spr::kNext) == after);
        else CHECK(r32(m, kHead) == after);
        if (after) CHECK(r32(m, after + spr::kPrev) == before);
        ++released;
    }
    MESSAGE("sprite handles: " << made << " made, " << released << " released");
}

// sub_104D10: vsprintf into its stack buffer, then the characters into the 53 x 40 grid 0x7E1E30 from column (int)x,
// row (int)y; '\n' goes back to the start column one row down; nothing at or past column 53 / row 40.
TEST_CASE("game(unblock): the debug text grid") {
    auto mp = elf_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF at " << elf_path());
        return;
    }
    Machine& m = *mp;
    constexpr u32 kGrid = 0x7E1E30u, kCols = 53, kRows = 40;
    constexpr u32 kFmt = kScratch + 0x3000u, kArg = kScratch + 0x3100u;
    const char* texts[] = {"HONPEN", "GOJITUDAN", "A\nBC\nDEF", "", "0123456789012345678901234567890123456789012345678901234567",
                           "line\n\n\nend"};
    int checked = 0;
    for (const char* text : texts)
        for (const auto& [x, y] : {std::pair<f32, f32>{0.0f, 0.0f}, {4.0f, 4.0f}, {50.0f, 2.0f}, {10.0f, 38.0f}, {52.0f, 39.0f},
                                   {53.0f, 1.0f}, {1.0f, 40.0f}}) {
            std::memset(m.at(kGrid), 0, kCols * kRows);
            std::memcpy(m.at(kFmt), "%s", 3);
            std::memset(m.at(kArg), 0, 0x100);
            std::memcpy(m.at(kArg), text, std::strlen(text));
            const u64 xy = (static_cast<u64>(fbits(y)) << 32) | fbits(x);
            const SiPair p = run_pair_si(m, fc("sub_104D10").hand, fc("sub_104D10").recomp, {xy, kFmt, kArg, 0},
                                         static_cast<u32>(checked), "sub_104D10", whole_ram_check());
            CHECK(p.recomp->si.calls_to(kVsprintf) == 1);
            // the host model of the grid
            std::vector<u8> want(kCols * kRows, 0);
            if (x < 53.0f && y < 40.0f) {
                s32 col = static_cast<s32>(x), row = static_cast<s32>(y);
                const s32 col0 = col;
                for (const char* s = text; *s && s - text < 256 && col < 53 && row < 40; ++s) {
                    if (*s == '\n') {
                        col = col0;
                        ++row;
                    } else {
                        want[static_cast<u32>(53 * row + col)] = static_cast<u8>(*s);
                        ++col;
                    }
                }
            }
            CHECK(std::memcmp(m.at(kGrid), want.data(), want.size()) == 0);
            ++checked;
        }
    MESSAGE("debug grid: " << checked << " prints");
}

// h_fade.c's record 0x7CDE90: the fade-out start, the predicates, the duration clamp, the speed, the colour request
// (only while option flag 387 is set) and the reset.
TEST_CASE("game(unblock): the fade record (h_fade.c)") {
    auto mp = elf_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF at " << elf_path());
        return;
    }
    Machine& m = *mp;
    constexpr u32 kRec = 0x7CDE90u, kRunning = 0x7CDED4u, kPhase = 0x7CDEFCu, kDuration = 0x7CDF00u, kCounter = 0x7CDF04u,
                  kSpeed = 0x7CDF08u;
    std::mt19937 rng{0x7CDE90u};
    for (int it = 0; it < 64; ++it) {
        const u32 running = rng() % 2;
        const u16 phase = static_cast<u16>(rng() % 5);
        const u16 duration = static_cast<u16>(rng() % 60);
        const u16 counter = static_cast<u16>(rng() % 60);
        w32(m, kRunning, running);
        w16(m, kPhase, phase);
        w16(m, kDuration, duration);
        w16(m, kCounter, counter);
        w16(m, kSpeed, 0x55);
        CHECK(static_cast<u32>(v0w(hgp::pair(m, fc("sub_1086D0").hand, fc("sub_1086D0").recomp, {}, 1, "sub_1086D0"))) ==
              ((running && phase == 3) ? 1u : 0u));
        CHECK(static_cast<u32>(v0w(hgp::pair(m, fc("sub_108710").hand, fc("sub_108710").recomp, {}, 2, "sub_108710"))) ==
              ((!running || phase == 3) ? 1u : 0u));
        const s16 d = static_cast<s16>(rng() % 70);
        hgp::pair(m, fc("sub_1086A0").hand, fc("sub_1086A0").recomp, {static_cast<u64>(d), 0, 0, 0}, 3, "sub_1086A0");
        CHECK(rs16(m, kDuration) == d);
        CHECK(rs16(m, kCounter) == std::min<s16>(d, static_cast<s16>(counter)));
        const u16 s = static_cast<u16>(rng() % 16);
        hgp::pair(m, fc("sub_108670").hand, fc("sub_108670").recomp, {s, 0, 0, 0}, 4, "sub_108670");
        CHECK(r16(m, kSpeed) == s);
        // the fade-out start: only when none runs
        const hgp::Run st = hgp::pair(m, fc("sub_108570").hand, fc("sub_108570").recomp, {}, 5, "sub_108570");
        CHECK(static_cast<u32>(v0w(st)) == (running ? 0u : 1u));
        if (!running) {
            CHECK(r32(m, kRunning) == 1u);
            CHECK(r16(m, kDuration) == 15u);
            CHECK(r16(m, kPhase) == 0u);
            CHECK(r16(m, kSpeed) == 0u);
        } else {
            CHECK(r16(m, kSpeed) == s);
        }
        // the colour request, with option flag 387 on or off
        const u32 on = rng() % 2;
        hgp::run_one(m, &rg::fn_datSetFlag_0016f1f0, {387, on, 0, 0}, 1, HwCheck{});
        const bool enabled = (hgp::run_one(m, &rg::fn_datGetFlag_0016f190, {387, 0, 0, 0}, 1, HwCheck{}).end.gpr[GPR_V0].u64[0] & 0xFFFFFFFFu) == 1u;
        std::memset(m.at(kRec), 0xAA, 0x1C);
        const u16 c0 = static_cast<u16>(rng());
        const u16 c1 = static_cast<u16>(rng());
        const u16 c2 = static_cast<u16>(rng());
        const u16 c3 = static_cast<u16>(rng());
        hgp::pair(m, fc("sub_103C30").hand, fc("sub_103C30").recomp, {c0, c1, c2, c3}, 6, "sub_103C30");
        if (enabled) {
            CHECK(r16(m, kRec + 0) == 2u);
            CHECK(r16(m, kRec + 4) == c1);
            CHECK(r16(m, kRec + 8) == 0u);
            CHECK(r16(m, kRec + 12) == c3);
            CHECK(r16(m, kRec + 16) == c2);
            CHECK(r16(m, kRec + 20) == 0u);
            CHECK(r16(m, kRec + 24) == c0);
        } else {
            CHECK(r16(m, kRec + 0) == 0xAAAAu);
        }
        hgp::pair(m, fc("sub_103CB0").hand, fc("sub_103CB0").recomp, {}, 7, "sub_103CB0");
        CHECK(r16(m, kRec) == 1u);
        for (u32 off = 4; off <= 24; off += 4) CHECK(r16(m, kRec + off) == 0u);
        CHECK(r16(m, 0x7E09DEu) == 0u);
        CHECK(r16(m, 0x7E09E0u) == 0u);
    }
}

// The facility request table (64-byte records behind the pointer 0x7CD8F0): the accessors' fields and bit fields.
TEST_CASE("game(unblock): the request table accessors") {
    auto mp = elf_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF at " << elf_path());
        return;
    }
    Machine& m = *mp;
    constexpr u32 kTable = kScratch + 0x8000u;
    std::mt19937 rng{0x403740u};
    for (u32 i = 0; i < 64 * 64; i += 4) {
        const u32 v = rng();
        w32(m, kTable + i, v);
    }
    w32(m, 0x7CD8F0u, kTable);
    for (u32 id = 0; id < 64; ++id) {
        const u32 rec = kTable + 64 * id;
        auto call = [&](const char* fn, u64 a1 = 0) { return v0w(hgp::pair(m, fc(fn).hand, fc(fn).recomp, {id, a1, 0, 0}, id, fn)); };
        CHECK(static_cast<s64>(call("sub_403740")) == rs16(m, rec + 58));
        CHECK(static_cast<s64>(call("sub_403900")) == rs16(m, rec + 60));
        const s32 hi6 = static_cast<s32>(static_cast<u32>(r16(m, rec + 14)) << 20) >> 26;  // bits 6..11, signed
        const s32 lo6 = static_cast<s32>(static_cast<u32>(r8(m, rec + 14)) << 26) >> 26;   // bits 0..5, signed
        CHECK(static_cast<s64>(call("sub_403800")) == hi6);
        CHECK(static_cast<s64>(call("sub_403830")) == lo6);
        CHECK(static_cast<u32>(call("sub_403880")) == rec + 32);
        if (id % 3 == 0) w8(m, rec + 38, 3);
        CHECK(static_cast<u32>(call("sub_4038A0")) == (r8(m, rec + 38) == 3 ? r32(m, rec + 40) : 0u));
        if (id % 2 == 0) w8(m, rec + 26, 1);
        const s16 want = rs16(m, rec + 28);
        const s16 ask = id % 4 == 0 ? want : static_cast<s16>(want + 1);
        CHECK(call("sub_403920", static_cast<u64>(static_cast<s64>(ask))) == ((r8(m, rec + 26) == 1 && ask == want) ? 1u : 0u));
    }
}

// sub_434F70 (the NPC globals' reset of the field battle set-up) on its own.
TEST_CASE("game(unblock): the NPC reset") {
    auto mp = elf_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF at " << elf_path());
        return;
    }
    Machine& m = *mp;
    std::vector<u32> absent;
    for (u32 flag = 0; flag < 2; ++flag) {
        hgp::run_one(m, &rg::fn_datSetFlag_0016f1f0, {5140, flag, 0, 0}, 1, HwCheck{});
        for (const u32 b : {0x7CE6BCu, 0x7CE6C0u, 0x7CE6C4u, 0x7CE6C8u, 0x7CE6E8u, 0x7CE6E9u, 0x7CE6EAu, 0x7CE6F0u}) w8(m, b, 0x5A);
        w16(m, 0x7CE6F4u, 0x1234);
        w8(m, 0x7CDB10u, 0);
        for (u32 k = 0; k < 8; ++k) w32(m, 0x86BE00u + 16 * k, 0xA5A5A5A5u);
        std::memset(m.at(0x95C110u), 0x5A, 256);
        const std::vector<u8> base(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        si_pair(m, fc("sub_434F70"), {}, flag, absent, [&base](Machine& mm) { reset(mm, base); });
        for (const u32 b : {0x7CE6BCu, 0x7CE6C0u, 0x7CE6C4u, 0x7CE6C8u, 0x7CE6E8u, 0x7CE6E9u, 0x7CE6EAu, 0x7CE6F0u}) CHECK(r8(m, b) == 0u);
        CHECK(r16(m, 0x7CE6F4u) == 0xFFFFu);
        CHECK(r8(m, 0x7CDB10u) == 1u);
        for (u32 k = 0; k < 8; ++k) CHECK(r32(m, 0x86BE00u + 16 * k) == 0u);
        u32 kept = 0;
        for (u32 k = 0; k < 256; ++k) kept += r8(m, 0x95C110u + k) == (flag ? 0x5Au : 0u) ? 1u : 0u;
        CHECK(kept == 256u);
    }
}

// The C runtime against the host: fabs / isinf / isnan exactly, strncmp's sign (aligned and unaligned strings), cos /
// sin within one ulp of the host's, __fixunssfdi and fptodp exactly, the double compare.
TEST_CASE("game(unblock): the C runtime against the host") {
    auto mp = elf_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF at " << elf_path());
        return;
    }
    Machine& m = *mp;
    std::mt19937 rng{0x52E038u};
    std::vector<double> ds = {0.0, -0.0, 1.0, -1.0, 0.5, 3.141592653589793, -2.718281828459045, 1e-300, -1e300, 1e308,
                              std::numeric_limits<double>::infinity(), -std::numeric_limits<double>::infinity(),
                              std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::denorm_min(), 4.9e-324};
    for (int i = 0; i < 200; ++i) {
        const u32 hi = rng();
        const u32 lo = rng();
        ds.push_back(dfrom((static_cast<u64>(hi) << 32) | lo));
    }
    int seed = 0;
    for (const double d : ds) {
        const u64 b = dbits(d);
        INFO("double " << hex64(b));
        CHECK(v0w(hgp::pair(m, fc("fabs").hand, fc("fabs").recomp, {b, 0, 0, 0}, ++seed, "fabs")) == (b & 0x7FFFFFFFFFFFFFFFull));
        CHECK(static_cast<u32>(v0w(hgp::pair(m, fc("isinf").hand, fc("isinf").recomp, {b, 0, 0, 0}, ++seed, "isinf"))) ==
              (std::isinf(d) ? 1u : 0u));
        CHECK(static_cast<u32>(v0w(hgp::pair(m, fc("isnan").hand, fc("isnan").recomp, {b, 0, 0, 0}, ++seed, "isnan"))) ==
              (std::isnan(d) ? 1u : 0u));
    }
    // cos / sin: |x| < pi/4 (the __kernel_cos / __kernel_sin path) and up to 1e6 (through __ieee754_rem_pio2, emitted for
    // this test), within one ulp of the host's
    for (int i = 0; i < 160; ++i) {
        const u32 r1 = rng();
        const double x = (static_cast<double>(r1) / 4294967296.0 - 0.5) * (i < 60 ? 1.56 : i < 120 ? 40.0 : 2e6);
        for (const char* fn : {"cos", "sin"}) {
            const hgp::Run r = hgp::pair(m, fc(fn).hand, fc(fn).recomp, {dbits(x), 0, 0, 0}, static_cast<u32>(++seed), fn);
            REQUIRE(!r.stopped);
            const double got = dfrom(v0w(r));
            const double want = std::string(fn) == "cos" ? std::cos(x) : std::sin(x);
            INFO(fn << "(" << x << ") = " << got << ", host " << want);
            CHECK((got == want || got == std::nextafter(want, 2.0) || got == std::nextafter(want, -2.0)));
        }
    }
    // the double compare sub_45EC00: a < b
    for (int i = 0; i + 1 < static_cast<int>(ds.size()); ++i) {
        const double a = ds[static_cast<std::size_t>(i)], b = ds[static_cast<std::size_t>(i) + 1];
        if (std::isnan(a) || std::isnan(b)) continue;
        CHECK(static_cast<u32>(v0w(hgp::pair(m, fc("sub_45EC00").hand, fc("sub_45EC00").recomp, {dbits(a), dbits(b), 0, 0}, ++seed,
                                             "sub_45EC00"))) == (a < b ? 1u : 0u));
    }
    // fptodp: float -> double exactly; __fixunssfdi: float -> u64, 0 below zero
    for (const f32 f : {0.0f, 1.0f, -1.0f, 0.5f, 1.5f, 3.0e-38f, 123456.789f, 4294967296.0f, 9.2233720e18f, 1.8446742e19f, -3.5f,
                        1e10f, 16777217.0f, 7.0f}) {
        INFO("float " << f);
        const hgp::Run d = pair_fpr(m, "fptodp", {}, {{12, fbits(f)}}, static_cast<u32>(++seed));
        CHECK(v0w(d) == dbits(static_cast<double>(f)));
        const hgp::Run u = pair_fpr(m, "__fixunssfdi", {}, {{12, fbits(f)}}, static_cast<u32>(++seed));
        CHECK(v0w(u) == (f <= 0.0f ? 0u : static_cast<u64>(f)));
    }
    // strncmp: the sign of the result against the host's, aligned (the word loop) and unaligned
    constexpr u32 kS1 = kScratch + 0x5000u, kS2 = kScratch + 0x5800u;
    for (int i = 0; i < 300; ++i) {
        std::memset(m.at(kS1), 0, 0x400);
        std::memset(m.at(kS2), 0, 0x400);
        const u32 len = rng() % 40;
        const u32 off1 = i % 3 == 0 ? 0u : rng() % 8;
        const u32 off2 = i % 3 == 0 ? 0u : rng() % 8;
        std::string a, b;
        for (u32 k = 0; k < len; ++k) a.push_back(static_cast<char>('a' + rng() % 3));
        b = a;
        if (!b.empty() && rng() % 2) b[rng() % b.size()] = static_cast<char>(0xE0 + rng() % 8);
        if (rng() % 4 == 0) b.resize(rng() % (b.size() + 1));
        std::memcpy(m.at(kS1 + off1), a.data(), a.size());
        std::memcpy(m.at(kS2 + off2), b.data(), b.size());
        const u32 n = rng() % 48;
        const s64 got = static_cast<s32>(static_cast<u32>(v0w(hgp::pair(m, fc("strncmp").hand, fc("strncmp").recomp,
                                                                       {kS1 + off1, kS2 + off2, n, 0}, static_cast<u32>(++seed), "strncmp"))));
        const int want = std::strncmp(reinterpret_cast<const char*>(m.at(kS1 + off1)), reinterpret_cast<const char*>(m.at(kS2 + off2)), n);
        INFO("strncmp(\"" << a << "\", \"" << b << "\", " << n << ")");
        CHECK((got < 0) == (want < 0));
        CHECK((got > 0) == (want > 0));
    }
}

#else

TEST_CASE("game(unblock): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
