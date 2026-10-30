// Pair tests of slice sweep5d (game/src/render/sweep5d.cpp): every body against its recompiled body on
//   * random worlds: the p3fes_handgen sweep;
//   * the packet's replay snapshots (b_5800, dorm_replay_4900, climb_ref_17000) with arguments drawn per function
//     (kKinds below): gBtl's real btlActions and its battle camera for the table callbacks and camera shots, cleared
//     records with small counts and linked sub-blocks for the pointer arguments, C strings, type-7 resource handles,
//     and the id ranges each body branches on (sub_2DA930's 463..471, sub_58C228's 188..255, encounter ids, ...);
//   * documented rules: sub_2DA930's gBtl+2580 kinds, sub_2DB8D0's gBtl reset, sub_4AE110 / sub_55DA48 / sub_59FEF8 on
//     their records.
// Compared by tests/game/handgen_pairs.h (hgp::pair) and stand_ins.h (run_pair_si): the whole register file and cycle
// count at every check point and at the return / stop, all 32 MiB of RAM (the dead stack included), the scratchpad,
// the BIOS window and the bus log.
#include "handgen_pairs.h"
#include "sweep2_util.h"

#include "p3fes/game/sweep5d.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
using namespace p3fes::game_test::s2t;


namespace p3fes::recomp_gen {
void fn_sub_1050E0_001050e0(EEContext&);  // generated body
void fn_sub_1050E0_001050e0__recomp(EEContext&);  // recompiled
void fn_sub_1A0D40_001a0d40(EEContext&);  // generated body
void fn_sub_1A0D40_001a0d40__recomp(EEContext&);  // recompiled
void fn_sub_1A11D0_001a11d0(EEContext&);  // generated body
void fn_sub_1A11D0_001a11d0__recomp(EEContext&);  // recompiled
void fn_sub_1A42F0_001a42f0(EEContext&);  // generated body
void fn_sub_1A42F0_001a42f0__recomp(EEContext&);  // recompiled
void fn_sub_1A46F0_001a46f0(EEContext&);  // generated body
void fn_sub_1A46F0_001a46f0__recomp(EEContext&);  // recompiled
void fn_sub_1A5CD0_001a5cd0(EEContext&);  // generated body
void fn_sub_1A5CD0_001a5cd0__recomp(EEContext&);  // recompiled
void fn_sub_1A62C0_001a62c0(EEContext&);  // generated body
void fn_sub_1A62C0_001a62c0__recomp(EEContext&);  // recompiled
void fn_sub_1A7020_001a7020(EEContext&);  // generated body
void fn_sub_1A7020_001a7020__recomp(EEContext&);  // recompiled
void fn_sub_1A7060_001a7060(EEContext&);  // generated body
void fn_sub_1A7060_001a7060__recomp(EEContext&);  // recompiled
void fn_sub_1A92D0_001a92d0(EEContext&);  // generated body
void fn_sub_1A92D0_001a92d0__recomp(EEContext&);  // recompiled
void fn_sub_20E2C0_0020e2c0(EEContext&);  // generated body
void fn_sub_20E2C0_0020e2c0__recomp(EEContext&);  // recompiled
void fn_sub_21A670_0021a670(EEContext&);  // generated body
void fn_sub_21A670_0021a670__recomp(EEContext&);  // recompiled
void fn_sub_21A760_0021a760(EEContext&);  // generated body
void fn_sub_21A760_0021a760__recomp(EEContext&);  // recompiled
void fn_sub_21A920_0021a920(EEContext&);  // generated body
void fn_sub_21A920_0021a920__recomp(EEContext&);  // recompiled
void fn_sub_23C280_0023c280(EEContext&);  // generated body
void fn_sub_23C280_0023c280__recomp(EEContext&);  // recompiled
void fn_sub_242720_00242720(EEContext&);  // generated body
void fn_sub_242720_00242720__recomp(EEContext&);  // recompiled
void fn_sub_255B20_00255b20(EEContext&);  // generated body
void fn_sub_255B20_00255b20__recomp(EEContext&);  // recompiled
void fn_brItem_CreateStockOverBgTask_0025f370(EEContext&);  // generated body
void fn_brItem_CreateStockOverBgTask_0025f370__recomp(EEContext&);  // recompiled
void fn_sub_267120_00267120(EEContext&);  // generated body
void fn_sub_267120_00267120__recomp(EEContext&);  // recompiled
void fn_sub_274030_00274030(EEContext&);  // generated body
void fn_sub_274030_00274030__recomp(EEContext&);  // recompiled
void fn_sub_2B6460_002b6460(EEContext&);  // generated body
void fn_sub_2B6460_002b6460__recomp(EEContext&);  // recompiled
void fn_sub_2BC2F0_002bc2f0(EEContext&);  // generated body
void fn_sub_2BC2F0_002bc2f0__recomp(EEContext&);  // recompiled
void fn_sub_2BC6D0_002bc6d0(EEContext&);  // generated body
void fn_sub_2BC6D0_002bc6d0__recomp(EEContext&);  // recompiled
void fn_sub_2D3D70_002d3d70(EEContext&);  // generated body
void fn_sub_2D3D70_002d3d70__recomp(EEContext&);  // recompiled
void fn_sub_2D8610_002d8610(EEContext&);  // generated body
void fn_sub_2D8610_002d8610__recomp(EEContext&);  // recompiled
void fn_sub_2D8780_002d8780(EEContext&);  // generated body
void fn_sub_2D8780_002d8780__recomp(EEContext&);  // recompiled
void fn_sub_2D87E0_002d87e0(EEContext&);  // generated body
void fn_sub_2D87E0_002d87e0__recomp(EEContext&);  // recompiled
void fn_sub_2D89E0_002d89e0(EEContext&);  // generated body
void fn_sub_2D89E0_002d89e0__recomp(EEContext&);  // recompiled
void fn_sub_2D8CF0_002d8cf0(EEContext&);  // generated body
void fn_sub_2D8CF0_002d8cf0__recomp(EEContext&);  // recompiled
void fn_sub_2D8DC0_002d8dc0(EEContext&);  // generated body
void fn_sub_2D8DC0_002d8dc0__recomp(EEContext&);  // recompiled
void fn_sub_2D8E80_002d8e80(EEContext&);  // generated body
void fn_sub_2D8E80_002d8e80__recomp(EEContext&);  // recompiled
void fn_sub_2D9B20_002d9b20(EEContext&);  // generated body
void fn_sub_2D9B20_002d9b20__recomp(EEContext&);  // recompiled
void fn_sub_2DA810_002da810(EEContext&);  // generated body
void fn_sub_2DA810_002da810__recomp(EEContext&);  // recompiled
void fn_sub_2DA930_002da930(EEContext&);  // generated body
void fn_sub_2DA930_002da930__recomp(EEContext&);  // recompiled
void fn_sub_2DB8D0_002db8d0(EEContext&);  // generated body
void fn_sub_2DB8D0_002db8d0__recomp(EEContext&);  // recompiled
void fn_sub_2DB980_002db980(EEContext&);  // generated body
void fn_sub_2DB980_002db980__recomp(EEContext&);  // recompiled
void fn_sub_2DCFB0_002dcfb0(EEContext&);  // generated body
void fn_sub_2DCFB0_002dcfb0__recomp(EEContext&);  // recompiled
void fn_sub_2DD9B0_002dd9b0(EEContext&);  // generated body
void fn_sub_2DD9B0_002dd9b0__recomp(EEContext&);  // recompiled
void fn_sub_2E2F30_002e2f30(EEContext&);  // generated body
void fn_sub_2E2F30_002e2f30__recomp(EEContext&);  // recompiled
void fn_sub_2E2F80_002e2f80(EEContext&);  // generated body
void fn_sub_2E2F80_002e2f80__recomp(EEContext&);  // recompiled
void fn_sub_2E6A20_002e6a20(EEContext&);  // generated body
void fn_sub_2E6A20_002e6a20__recomp(EEContext&);  // recompiled
void fn_sub_2E70B0_002e70b0(EEContext&);  // generated body
void fn_sub_2E70B0_002e70b0__recomp(EEContext&);  // recompiled
void fn_datUnitCreatePc_002ff340(EEContext&);  // generated body
void fn_datUnitCreatePc_002ff340__recomp(EEContext&);  // recompiled
void fn_datUnitCreateEc_002ff3e0(EEContext&);  // generated body
void fn_datUnitCreateEc_002ff3e0__recomp(EEContext&);  // recompiled
void fn_datUnitDestroyGenus_002ff760(EEContext&);  // generated body
void fn_datUnitDestroyGenus_002ff760__recomp(EEContext&);  // recompiled
void fn_sub_3170C0_003170c0(EEContext&);  // generated body
void fn_sub_3170C0_003170c0__recomp(EEContext&);  // recompiled
void fn_sub_31E8D0_0031e8d0(EEContext&);  // generated body
void fn_sub_31E8D0_0031e8d0__recomp(EEContext&);  // recompiled
void fn_sub_324160_00324160(EEContext&);  // generated body
void fn_sub_324160_00324160__recomp(EEContext&);  // recompiled
void fn_sub_3A4270_003a4270(EEContext&);  // generated body
void fn_sub_3A4270_003a4270__recomp(EEContext&);  // recompiled
void fn_sub_3B55B0_003b55b0(EEContext&);  // generated body
void fn_sub_3B55B0_003b55b0__recomp(EEContext&);  // recompiled
void fn_sub_3B64C0_003b64c0(EEContext&);  // generated body
void fn_sub_3B64C0_003b64c0__recomp(EEContext&);  // recompiled
void fn_sub_3B8310_003b8310(EEContext&);  // generated body
void fn_sub_3B8310_003b8310__recomp(EEContext&);  // recompiled
void fn_sub_3B8690_003b8690(EEContext&);  // generated body
void fn_sub_3B8690_003b8690__recomp(EEContext&);  // recompiled
void fn_sub_3B87F0_003b87f0(EEContext&);  // generated body
void fn_sub_3B87F0_003b87f0__recomp(EEContext&);  // recompiled
void fn_sub_3B89F0_003b89f0(EEContext&);  // generated body
void fn_sub_3B89F0_003b89f0__recomp(EEContext&);  // recompiled
void fn_sub_3B8E10_003b8e10(EEContext&);  // generated body
void fn_sub_3B8E10_003b8e10__recomp(EEContext&);  // recompiled
void fn_sub_3B8F30_003b8f30(EEContext&);  // generated body
void fn_sub_3B8F30_003b8f30__recomp(EEContext&);  // recompiled
void fn_sub_3B95A0_003b95a0(EEContext&);  // generated body
void fn_sub_3B95A0_003b95a0__recomp(EEContext&);  // recompiled
void fn_sub_3BB280_003bb280(EEContext&);  // generated body
void fn_sub_3BB280_003bb280__recomp(EEContext&);  // recompiled
void fn_sub_3BB400_003bb400(EEContext&);  // generated body
void fn_sub_3BB400_003bb400__recomp(EEContext&);  // recompiled
void fn_sub_3BD880_003bd880(EEContext&);  // generated body
void fn_sub_3BD880_003bd880__recomp(EEContext&);  // recompiled
void fn_sub_3BD8B0_003bd8b0(EEContext&);  // generated body
void fn_sub_3BD8B0_003bd8b0__recomp(EEContext&);  // recompiled
void fn_sub_3BE8E0_003be8e0(EEContext&);  // generated body
void fn_sub_3BE8E0_003be8e0__recomp(EEContext&);  // recompiled
void fn_sub_3C7E50_003c7e50(EEContext&);  // generated body
void fn_sub_3C7E50_003c7e50__recomp(EEContext&);  // recompiled
void fn_sub_3CB050_003cb050(EEContext&);  // generated body
void fn_sub_3CB050_003cb050__recomp(EEContext&);  // recompiled
void fn_sub_3E0A10_003e0a10(EEContext&);  // generated body
void fn_sub_3E0A10_003e0a10__recomp(EEContext&);  // recompiled
void fn_sub_3F4DE0_003f4de0(EEContext&);  // generated body
void fn_sub_3F4DE0_003f4de0__recomp(EEContext&);  // recompiled
void fn_sub_403970_00403970(EEContext&);  // generated body
void fn_sub_403970_00403970__recomp(EEContext&);  // recompiled
void fn_sub_404120_00404120(EEContext&);  // generated body
void fn_sub_404120_00404120__recomp(EEContext&);  // recompiled
void fn_sub_406CA0_00406ca0(EEContext&);  // generated body
void fn_sub_406CA0_00406ca0__recomp(EEContext&);  // recompiled
void fn_sub_40A7F0_0040a7f0(EEContext&);  // generated body
void fn_sub_40A7F0_0040a7f0__recomp(EEContext&);  // recompiled
void fn_sub_40C6F0_0040c6f0(EEContext&);  // generated body
void fn_sub_40C6F0_0040c6f0__recomp(EEContext&);  // recompiled
void fn_sub_40C9A0_0040c9a0(EEContext&);  // generated body
void fn_sub_40C9A0_0040c9a0__recomp(EEContext&);  // recompiled
void fn_sub_40CAD0_0040cad0(EEContext&);  // generated body
void fn_sub_40CAD0_0040cad0__recomp(EEContext&);  // recompiled
void fn_sub_40CC30_0040cc30(EEContext&);  // generated body
void fn_sub_40CC30_0040cc30__recomp(EEContext&);  // recompiled
void fn_sub_464020_00464020(EEContext&);  // generated body
void fn_sub_464020_00464020__recomp(EEContext&);  // recompiled
void fn_sub_4663D0_004663d0(EEContext&);  // generated body
void fn_sub_4663D0_004663d0__recomp(EEContext&);  // recompiled
void fn_sub_468DC0_00468dc0(EEContext&);  // generated body
void fn_sub_468DC0_00468dc0__recomp(EEContext&);  // recompiled
void fn_sub_469510_00469510(EEContext&);  // generated body
void fn_sub_469510_00469510__recomp(EEContext&);  // recompiled
void fn_sub_48DA30_0048da30(EEContext&);  // generated body
void fn_sub_48DA30_0048da30__recomp(EEContext&);  // recompiled
void fn_sub_48DAB0_0048dab0(EEContext&);  // generated body
void fn_sub_48DAB0_0048dab0__recomp(EEContext&);  // recompiled
void fn_sub_48EF80_0048ef80(EEContext&);  // generated body
void fn_sub_48EF80_0048ef80__recomp(EEContext&);  // recompiled
void fn_sub_4A9BF0_004a9bf0(EEContext&);  // generated body
void fn_sub_4A9BF0_004a9bf0__recomp(EEContext&);  // recompiled
void fn_sub_4A9D80_004a9d80(EEContext&);  // generated body
void fn_sub_4A9D80_004a9d80__recomp(EEContext&);  // recompiled
void fn_sub_4A9F20_004a9f20(EEContext&);  // generated body
void fn_sub_4A9F20_004a9f20__recomp(EEContext&);  // recompiled
void fn_sub_4AA390_004aa390(EEContext&);  // generated body
void fn_sub_4AA390_004aa390__recomp(EEContext&);  // recompiled
void fn_sub_4AA3D0_004aa3d0(EEContext&);  // generated body
void fn_sub_4AA3D0_004aa3d0__recomp(EEContext&);  // recompiled
void fn_sub_4AE060_004ae060(EEContext&);  // generated body
void fn_sub_4AE060_004ae060__recomp(EEContext&);  // recompiled
void fn_sub_4AE110_004ae110(EEContext&);  // generated body
void fn_sub_4AE110_004ae110__recomp(EEContext&);  // recompiled
void fn_sub_4B1A60_004b1a60(EEContext&);  // generated body
void fn_sub_4B1A60_004b1a60__recomp(EEContext&);  // recompiled
void fn_sub_4B1A70_004b1a70(EEContext&);  // generated body
void fn_sub_4B1A70_004b1a70__recomp(EEContext&);  // recompiled
void fn_sub_4B3CC0_004b3cc0(EEContext&);  // generated body
void fn_sub_4B3CC0_004b3cc0__recomp(EEContext&);  // recompiled
void fn_sub_4B45B0_004b45b0(EEContext&);  // generated body
void fn_sub_4B45B0_004b45b0__recomp(EEContext&);  // recompiled
void fn_sub_4B6980_004b6980(EEContext&);  // generated body
void fn_sub_4B6980_004b6980__recomp(EEContext&);  // recompiled
void fn_sub_4C0240_004c0240(EEContext&);  // generated body
void fn_sub_4C0240_004c0240__recomp(EEContext&);  // recompiled
void fn_sub_4C0370_004c0370(EEContext&);  // generated body
void fn_sub_4C0370_004c0370__recomp(EEContext&);  // recompiled
void fn_sub_4C3D10_004c3d10(EEContext&);  // generated body
void fn_sub_4C3D10_004c3d10__recomp(EEContext&);  // recompiled
void fn_sub_4CD620_004cd620(EEContext&);  // generated body
void fn_sub_4CD620_004cd620__recomp(EEContext&);  // recompiled
void fn_sub_4D0B60_004d0b60(EEContext&);  // generated body
void fn_sub_4D0B60_004d0b60__recomp(EEContext&);  // recompiled
void fn_sub_4D0B80_004d0b80(EEContext&);  // generated body
void fn_sub_4D0B80_004d0b80__recomp(EEContext&);  // recompiled
void fn_sub_4D0BA0_004d0ba0(EEContext&);  // generated body
void fn_sub_4D0BA0_004d0ba0__recomp(EEContext&);  // recompiled
void fn_sub_4D0BC0_004d0bc0(EEContext&);  // generated body
void fn_sub_4D0BC0_004d0bc0__recomp(EEContext&);  // recompiled
void fn_sub_4DFCB0_004dfcb0(EEContext&);  // generated body
void fn_sub_4DFCB0_004dfcb0__recomp(EEContext&);  // recompiled
void fn__sceMpegFlush_00501ae8(EEContext&);  // generated body
void fn__sceMpegFlush_00501ae8__recomp(EEContext&);  // recompiled
void fn_sceMc2FormatAsync_00513598(EEContext&);  // generated body
void fn_sceMc2FormatAsync_00513598__recomp(EEContext&);  // recompiled
void fn_sceMc2WriteFileAsync_00513cc8(EEContext&);  // generated body
void fn_sceMc2WriteFileAsync_00513cc8__recomp(EEContext&);  // recompiled
void fn_sceMc2CreateFileAsync_00513de8(EEContext&);  // generated body
void fn_sceMc2CreateFileAsync_00513de8__recomp(EEContext&);  // recompiled
void fn_sceMc2MkdirAsync_005140f8(EEContext&);  // generated body
void fn_sceMc2MkdirAsync_005140f8__recomp(EEContext&);  // recompiled
void fn__sceMcCoreWritePage_0051b8f0(EEContext&);  // generated body
void fn__sceMcCoreWritePage_0051b8f0__recomp(EEContext&);  // recompiled
void fn__fwalk_00520410(EEContext&);  // generated body
void fn__fwalk_00520410__recomp(EEContext&);  // recompiled
void fn___srefill_00523580(EEContext&);  // generated body
void fn___srefill_00523580__recomp(EEContext&);  // recompiled
void fn_sceInsockGetErrnoMode_00537780(EEContext&);  // generated body
void fn_sceInsockGetErrnoMode_00537780__recomp(EEContext&);  // recompiled
void fn_sub_53AFD8_0053afd8(EEContext&);  // generated body
void fn_sub_53AFD8_0053afd8__recomp(EEContext&);  // recompiled
void fn_sub_53EC20_0053ec20(EEContext&);  // generated body
void fn_sub_53EC20_0053ec20__recomp(EEContext&);  // recompiled
void fn_sub_547F30_00547f30(EEContext&);  // generated body
void fn_sub_547F30_00547f30__recomp(EEContext&);  // recompiled
void fn_sub_548FC8_00548fc8(EEContext&);  // generated body
void fn_sub_548FC8_00548fc8__recomp(EEContext&);  // recompiled
void fn_sub_549530_00549530(EEContext&);  // generated body
void fn_sub_549530_00549530__recomp(EEContext&);  // recompiled
void fn___env_lock_0_0054a630(EEContext&);  // generated body
void fn___env_lock_0_0054a630__recomp(EEContext&);  // recompiled
void fn_sub_54F708_0054f708(EEContext&);  // generated body
void fn_sub_54F708_0054f708__recomp(EEContext&);  // recompiled
void fn_sub_552BD0_00552bd0(EEContext&);  // generated body
void fn_sub_552BD0_00552bd0__recomp(EEContext&);  // recompiled
void fn_sub_553188_00553188(EEContext&);  // generated body
void fn_sub_553188_00553188__recomp(EEContext&);  // recompiled
void fn_sub_553230_00553230(EEContext&);  // generated body
void fn_sub_553230_00553230__recomp(EEContext&);  // recompiled
void fn_sub_55A1D0_0055a1d0(EEContext&);  // generated body
void fn_sub_55A1D0_0055a1d0__recomp(EEContext&);  // recompiled
void fn_dvCiStopTr_0055a638(EEContext&);  // generated body
void fn_dvCiStopTr_0055a638__recomp(EEContext&);  // recompiled
void fn_dvci_analysis_flist_0055ab80(EEContext&);  // generated body
void fn_dvci_analysis_flist_0055ab80__recomp(EEContext&);  // recompiled
void fn_sub_55B0F8_0055b0f8(EEContext&);  // generated body
void fn_sub_55B0F8_0055b0f8__recomp(EEContext&);  // recompiled
void fn_sub_55DA48_0055da48(EEContext&);  // generated body
void fn_sub_55DA48_0055da48__recomp(EEContext&);  // recompiled
void fn_sub_5835F0_005835f0(EEContext&);  // generated body
void fn_sub_5835F0_005835f0__recomp(EEContext&);  // recompiled
void fn_sub_5837A0_005837a0(EEContext&);  // generated body
void fn_sub_5837A0_005837a0__recomp(EEContext&);  // recompiled
void fn_sub_5876F0_005876f0(EEContext&);  // generated body
void fn_sub_5876F0_005876f0__recomp(EEContext&);  // recompiled
void fn_sub_589F70_00589f70(EEContext&);  // generated body
void fn_sub_589F70_00589f70__recomp(EEContext&);  // recompiled
void fn_sub_58C228_0058c228(EEContext&);  // generated body
void fn_sub_58C228_0058c228__recomp(EEContext&);  // recompiled
void fn_sub_595208_00595208(EEContext&);  // generated body
void fn_sub_595208_00595208__recomp(EEContext&);  // recompiled
void fn_sub_597968_00597968(EEContext&);  // generated body
void fn_sub_597968_00597968__recomp(EEContext&);  // recompiled
void fn_sub_599368_00599368(EEContext&);  // generated body
void fn_sub_599368_00599368__recomp(EEContext&);  // recompiled
void fn_sub_5994F0_005994f0(EEContext&);  // generated body
void fn_sub_5994F0_005994f0__recomp(EEContext&);  // recompiled
void fn_sub_59C8E0_0059c8e0(EEContext&);  // generated body
void fn_sub_59C8E0_0059c8e0__recomp(EEContext&);  // recompiled
void fn_sub_59FEF8_0059fef8(EEContext&);  // generated body
void fn_sub_59FEF8_0059fef8__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

const Case kCases[] = {
    {"sub_1050E0", 0x1050E0, &recomp_gen::fn_sub_1050E0_001050e0, &recomp_gen::fn_sub_1050E0_001050e0__recomp},
    {"sub_1A0D40", 0x1A0D40, &recomp_gen::fn_sub_1A0D40_001a0d40, &recomp_gen::fn_sub_1A0D40_001a0d40__recomp},
    {"sub_1A11D0", 0x1A11D0, &recomp_gen::fn_sub_1A11D0_001a11d0, &recomp_gen::fn_sub_1A11D0_001a11d0__recomp},
    {"sub_1A42F0", 0x1A42F0, &recomp_gen::fn_sub_1A42F0_001a42f0, &recomp_gen::fn_sub_1A42F0_001a42f0__recomp},
    {"sub_1A46F0", 0x1A46F0, &recomp_gen::fn_sub_1A46F0_001a46f0, &recomp_gen::fn_sub_1A46F0_001a46f0__recomp},
    {"sub_1A5CD0", 0x1A5CD0, &recomp_gen::fn_sub_1A5CD0_001a5cd0, &recomp_gen::fn_sub_1A5CD0_001a5cd0__recomp},
    {"sub_1A62C0", 0x1A62C0, &recomp_gen::fn_sub_1A62C0_001a62c0, &recomp_gen::fn_sub_1A62C0_001a62c0__recomp},
    {"sub_1A7020", 0x1A7020, &recomp_gen::fn_sub_1A7020_001a7020, &recomp_gen::fn_sub_1A7020_001a7020__recomp},
    {"sub_1A7060", 0x1A7060, &recomp_gen::fn_sub_1A7060_001a7060, &recomp_gen::fn_sub_1A7060_001a7060__recomp},
    {"sub_1A92D0", 0x1A92D0, &recomp_gen::fn_sub_1A92D0_001a92d0, &recomp_gen::fn_sub_1A92D0_001a92d0__recomp},
    {"sub_20E2C0", 0x20E2C0, &recomp_gen::fn_sub_20E2C0_0020e2c0, &recomp_gen::fn_sub_20E2C0_0020e2c0__recomp},
    {"sub_21A670", 0x21A670, &recomp_gen::fn_sub_21A670_0021a670, &recomp_gen::fn_sub_21A670_0021a670__recomp},
    {"sub_21A760", 0x21A760, &recomp_gen::fn_sub_21A760_0021a760, &recomp_gen::fn_sub_21A760_0021a760__recomp},
    {"sub_21A920", 0x21A920, &recomp_gen::fn_sub_21A920_0021a920, &recomp_gen::fn_sub_21A920_0021a920__recomp},
    {"sub_23C280", 0x23C280, &recomp_gen::fn_sub_23C280_0023c280, &recomp_gen::fn_sub_23C280_0023c280__recomp},
    {"sub_242720", 0x242720, &recomp_gen::fn_sub_242720_00242720, &recomp_gen::fn_sub_242720_00242720__recomp},
    {"sub_255B20", 0x255B20, &recomp_gen::fn_sub_255B20_00255b20, &recomp_gen::fn_sub_255B20_00255b20__recomp},
    {"brItem_CreateStockOverBgTask", 0x25F370, &recomp_gen::fn_brItem_CreateStockOverBgTask_0025f370, &recomp_gen::fn_brItem_CreateStockOverBgTask_0025f370__recomp},
    {"sub_267120", 0x267120, &recomp_gen::fn_sub_267120_00267120, &recomp_gen::fn_sub_267120_00267120__recomp},
    {"sub_274030", 0x274030, &recomp_gen::fn_sub_274030_00274030, &recomp_gen::fn_sub_274030_00274030__recomp},
    {"sub_2B6460", 0x2B6460, &recomp_gen::fn_sub_2B6460_002b6460, &recomp_gen::fn_sub_2B6460_002b6460__recomp},
    {"sub_2BC2F0", 0x2BC2F0, &recomp_gen::fn_sub_2BC2F0_002bc2f0, &recomp_gen::fn_sub_2BC2F0_002bc2f0__recomp},
    {"sub_2BC6D0", 0x2BC6D0, &recomp_gen::fn_sub_2BC6D0_002bc6d0, &recomp_gen::fn_sub_2BC6D0_002bc6d0__recomp},
    {"sub_2D3D70", 0x2D3D70, &recomp_gen::fn_sub_2D3D70_002d3d70, &recomp_gen::fn_sub_2D3D70_002d3d70__recomp},
    {"sub_2D8610", 0x2D8610, &recomp_gen::fn_sub_2D8610_002d8610, &recomp_gen::fn_sub_2D8610_002d8610__recomp},
    {"sub_2D8780", 0x2D8780, &recomp_gen::fn_sub_2D8780_002d8780, &recomp_gen::fn_sub_2D8780_002d8780__recomp},
    {"sub_2D87E0", 0x2D87E0, &recomp_gen::fn_sub_2D87E0_002d87e0, &recomp_gen::fn_sub_2D87E0_002d87e0__recomp},
    {"sub_2D89E0", 0x2D89E0, &recomp_gen::fn_sub_2D89E0_002d89e0, &recomp_gen::fn_sub_2D89E0_002d89e0__recomp},
    {"sub_2D8CF0", 0x2D8CF0, &recomp_gen::fn_sub_2D8CF0_002d8cf0, &recomp_gen::fn_sub_2D8CF0_002d8cf0__recomp},
    {"sub_2D8DC0", 0x2D8DC0, &recomp_gen::fn_sub_2D8DC0_002d8dc0, &recomp_gen::fn_sub_2D8DC0_002d8dc0__recomp},
    {"sub_2D8E80", 0x2D8E80, &recomp_gen::fn_sub_2D8E80_002d8e80, &recomp_gen::fn_sub_2D8E80_002d8e80__recomp},
    {"sub_2D9B20", 0x2D9B20, &recomp_gen::fn_sub_2D9B20_002d9b20, &recomp_gen::fn_sub_2D9B20_002d9b20__recomp},
    {"sub_2DA810", 0x2DA810, &recomp_gen::fn_sub_2DA810_002da810, &recomp_gen::fn_sub_2DA810_002da810__recomp},
    {"sub_2DA930", 0x2DA930, &recomp_gen::fn_sub_2DA930_002da930, &recomp_gen::fn_sub_2DA930_002da930__recomp},
    {"sub_2DB8D0", 0x2DB8D0, &recomp_gen::fn_sub_2DB8D0_002db8d0, &recomp_gen::fn_sub_2DB8D0_002db8d0__recomp},
    {"sub_2DB980", 0x2DB980, &recomp_gen::fn_sub_2DB980_002db980, &recomp_gen::fn_sub_2DB980_002db980__recomp},
    {"sub_2DCFB0", 0x2DCFB0, &recomp_gen::fn_sub_2DCFB0_002dcfb0, &recomp_gen::fn_sub_2DCFB0_002dcfb0__recomp},
    {"sub_2DD9B0", 0x2DD9B0, &recomp_gen::fn_sub_2DD9B0_002dd9b0, &recomp_gen::fn_sub_2DD9B0_002dd9b0__recomp},
    {"sub_2E2F30", 0x2E2F30, &recomp_gen::fn_sub_2E2F30_002e2f30, &recomp_gen::fn_sub_2E2F30_002e2f30__recomp},
    {"sub_2E2F80", 0x2E2F80, &recomp_gen::fn_sub_2E2F80_002e2f80, &recomp_gen::fn_sub_2E2F80_002e2f80__recomp},
    {"sub_2E6A20", 0x2E6A20, &recomp_gen::fn_sub_2E6A20_002e6a20, &recomp_gen::fn_sub_2E6A20_002e6a20__recomp},
    {"sub_2E70B0", 0x2E70B0, &recomp_gen::fn_sub_2E70B0_002e70b0, &recomp_gen::fn_sub_2E70B0_002e70b0__recomp},
    {"datUnitCreatePc", 0x2FF340, &recomp_gen::fn_datUnitCreatePc_002ff340, &recomp_gen::fn_datUnitCreatePc_002ff340__recomp},
    {"datUnitCreateEc", 0x2FF3E0, &recomp_gen::fn_datUnitCreateEc_002ff3e0, &recomp_gen::fn_datUnitCreateEc_002ff3e0__recomp},
    {"datUnitDestroyGenus", 0x2FF760, &recomp_gen::fn_datUnitDestroyGenus_002ff760, &recomp_gen::fn_datUnitDestroyGenus_002ff760__recomp},
    {"sub_3170C0", 0x3170C0, &recomp_gen::fn_sub_3170C0_003170c0, &recomp_gen::fn_sub_3170C0_003170c0__recomp},
    {"sub_31E8D0", 0x31E8D0, &recomp_gen::fn_sub_31E8D0_0031e8d0, &recomp_gen::fn_sub_31E8D0_0031e8d0__recomp},
    {"sub_324160", 0x324160, &recomp_gen::fn_sub_324160_00324160, &recomp_gen::fn_sub_324160_00324160__recomp},
    {"sub_3A4270", 0x3A4270, &recomp_gen::fn_sub_3A4270_003a4270, &recomp_gen::fn_sub_3A4270_003a4270__recomp},
    {"sub_3B55B0", 0x3B55B0, &recomp_gen::fn_sub_3B55B0_003b55b0, &recomp_gen::fn_sub_3B55B0_003b55b0__recomp},
    {"sub_3B64C0", 0x3B64C0, &recomp_gen::fn_sub_3B64C0_003b64c0, &recomp_gen::fn_sub_3B64C0_003b64c0__recomp},
    {"sub_3B8310", 0x3B8310, &recomp_gen::fn_sub_3B8310_003b8310, &recomp_gen::fn_sub_3B8310_003b8310__recomp},
    {"sub_3B8690", 0x3B8690, &recomp_gen::fn_sub_3B8690_003b8690, &recomp_gen::fn_sub_3B8690_003b8690__recomp},
    {"sub_3B87F0", 0x3B87F0, &recomp_gen::fn_sub_3B87F0_003b87f0, &recomp_gen::fn_sub_3B87F0_003b87f0__recomp},
    {"sub_3B89F0", 0x3B89F0, &recomp_gen::fn_sub_3B89F0_003b89f0, &recomp_gen::fn_sub_3B89F0_003b89f0__recomp},
    {"sub_3B8E10", 0x3B8E10, &recomp_gen::fn_sub_3B8E10_003b8e10, &recomp_gen::fn_sub_3B8E10_003b8e10__recomp},
    {"sub_3B8F30", 0x3B8F30, &recomp_gen::fn_sub_3B8F30_003b8f30, &recomp_gen::fn_sub_3B8F30_003b8f30__recomp},
    {"sub_3B95A0", 0x3B95A0, &recomp_gen::fn_sub_3B95A0_003b95a0, &recomp_gen::fn_sub_3B95A0_003b95a0__recomp},
    {"sub_3BB280", 0x3BB280, &recomp_gen::fn_sub_3BB280_003bb280, &recomp_gen::fn_sub_3BB280_003bb280__recomp},
    {"sub_3BB400", 0x3BB400, &recomp_gen::fn_sub_3BB400_003bb400, &recomp_gen::fn_sub_3BB400_003bb400__recomp},
    {"sub_3BD880", 0x3BD880, &recomp_gen::fn_sub_3BD880_003bd880, &recomp_gen::fn_sub_3BD880_003bd880__recomp},
    {"sub_3BD8B0", 0x3BD8B0, &recomp_gen::fn_sub_3BD8B0_003bd8b0, &recomp_gen::fn_sub_3BD8B0_003bd8b0__recomp},
    {"sub_3BE8E0", 0x3BE8E0, &recomp_gen::fn_sub_3BE8E0_003be8e0, &recomp_gen::fn_sub_3BE8E0_003be8e0__recomp},
    {"sub_3C7E50", 0x3C7E50, &recomp_gen::fn_sub_3C7E50_003c7e50, &recomp_gen::fn_sub_3C7E50_003c7e50__recomp},
    {"sub_3CB050", 0x3CB050, &recomp_gen::fn_sub_3CB050_003cb050, &recomp_gen::fn_sub_3CB050_003cb050__recomp},
    {"sub_3E0A10", 0x3E0A10, &recomp_gen::fn_sub_3E0A10_003e0a10, &recomp_gen::fn_sub_3E0A10_003e0a10__recomp},
    {"sub_3F4DE0", 0x3F4DE0, &recomp_gen::fn_sub_3F4DE0_003f4de0, &recomp_gen::fn_sub_3F4DE0_003f4de0__recomp},
    {"sub_403970", 0x403970, &recomp_gen::fn_sub_403970_00403970, &recomp_gen::fn_sub_403970_00403970__recomp},
    {"sub_404120", 0x404120, &recomp_gen::fn_sub_404120_00404120, &recomp_gen::fn_sub_404120_00404120__recomp},
    {"sub_406CA0", 0x406CA0, &recomp_gen::fn_sub_406CA0_00406ca0, &recomp_gen::fn_sub_406CA0_00406ca0__recomp},
    {"sub_40A7F0", 0x40A7F0, &recomp_gen::fn_sub_40A7F0_0040a7f0, &recomp_gen::fn_sub_40A7F0_0040a7f0__recomp},
    {"sub_40C6F0", 0x40C6F0, &recomp_gen::fn_sub_40C6F0_0040c6f0, &recomp_gen::fn_sub_40C6F0_0040c6f0__recomp},
    {"sub_40C9A0", 0x40C9A0, &recomp_gen::fn_sub_40C9A0_0040c9a0, &recomp_gen::fn_sub_40C9A0_0040c9a0__recomp},
    {"sub_40CAD0", 0x40CAD0, &recomp_gen::fn_sub_40CAD0_0040cad0, &recomp_gen::fn_sub_40CAD0_0040cad0__recomp},
    {"sub_40CC30", 0x40CC30, &recomp_gen::fn_sub_40CC30_0040cc30, &recomp_gen::fn_sub_40CC30_0040cc30__recomp},
    {"sub_464020", 0x464020, &recomp_gen::fn_sub_464020_00464020, &recomp_gen::fn_sub_464020_00464020__recomp},
    {"sub_4663D0", 0x4663D0, &recomp_gen::fn_sub_4663D0_004663d0, &recomp_gen::fn_sub_4663D0_004663d0__recomp},
    {"sub_468DC0", 0x468DC0, &recomp_gen::fn_sub_468DC0_00468dc0, &recomp_gen::fn_sub_468DC0_00468dc0__recomp},
    {"sub_469510", 0x469510, &recomp_gen::fn_sub_469510_00469510, &recomp_gen::fn_sub_469510_00469510__recomp},
    {"sub_48DA30", 0x48DA30, &recomp_gen::fn_sub_48DA30_0048da30, &recomp_gen::fn_sub_48DA30_0048da30__recomp},
    {"sub_48DAB0", 0x48DAB0, &recomp_gen::fn_sub_48DAB0_0048dab0, &recomp_gen::fn_sub_48DAB0_0048dab0__recomp},
    {"sub_48EF80", 0x48EF80, &recomp_gen::fn_sub_48EF80_0048ef80, &recomp_gen::fn_sub_48EF80_0048ef80__recomp},
    {"sub_4A9BF0", 0x4A9BF0, &recomp_gen::fn_sub_4A9BF0_004a9bf0, &recomp_gen::fn_sub_4A9BF0_004a9bf0__recomp},
    {"sub_4A9D80", 0x4A9D80, &recomp_gen::fn_sub_4A9D80_004a9d80, &recomp_gen::fn_sub_4A9D80_004a9d80__recomp},
    {"sub_4A9F20", 0x4A9F20, &recomp_gen::fn_sub_4A9F20_004a9f20, &recomp_gen::fn_sub_4A9F20_004a9f20__recomp},
    {"sub_4AA390", 0x4AA390, &recomp_gen::fn_sub_4AA390_004aa390, &recomp_gen::fn_sub_4AA390_004aa390__recomp},
    {"sub_4AA3D0", 0x4AA3D0, &recomp_gen::fn_sub_4AA3D0_004aa3d0, &recomp_gen::fn_sub_4AA3D0_004aa3d0__recomp},
    {"sub_4AE060", 0x4AE060, &recomp_gen::fn_sub_4AE060_004ae060, &recomp_gen::fn_sub_4AE060_004ae060__recomp},
    {"sub_4AE110", 0x4AE110, &recomp_gen::fn_sub_4AE110_004ae110, &recomp_gen::fn_sub_4AE110_004ae110__recomp},
    {"sub_4B1A60", 0x4B1A60, &recomp_gen::fn_sub_4B1A60_004b1a60, &recomp_gen::fn_sub_4B1A60_004b1a60__recomp},
    {"sub_4B1A70", 0x4B1A70, &recomp_gen::fn_sub_4B1A70_004b1a70, &recomp_gen::fn_sub_4B1A70_004b1a70__recomp},
    {"sub_4B3CC0", 0x4B3CC0, &recomp_gen::fn_sub_4B3CC0_004b3cc0, &recomp_gen::fn_sub_4B3CC0_004b3cc0__recomp},
    {"sub_4B45B0", 0x4B45B0, &recomp_gen::fn_sub_4B45B0_004b45b0, &recomp_gen::fn_sub_4B45B0_004b45b0__recomp},
    {"sub_4B6980", 0x4B6980, &recomp_gen::fn_sub_4B6980_004b6980, &recomp_gen::fn_sub_4B6980_004b6980__recomp},
    {"sub_4C0240", 0x4C0240, &recomp_gen::fn_sub_4C0240_004c0240, &recomp_gen::fn_sub_4C0240_004c0240__recomp},
    {"sub_4C0370", 0x4C0370, &recomp_gen::fn_sub_4C0370_004c0370, &recomp_gen::fn_sub_4C0370_004c0370__recomp},
    {"sub_4C3D10", 0x4C3D10, &recomp_gen::fn_sub_4C3D10_004c3d10, &recomp_gen::fn_sub_4C3D10_004c3d10__recomp},
    {"sub_4CD620", 0x4CD620, &recomp_gen::fn_sub_4CD620_004cd620, &recomp_gen::fn_sub_4CD620_004cd620__recomp},
    {"sub_4D0B60", 0x4D0B60, &recomp_gen::fn_sub_4D0B60_004d0b60, &recomp_gen::fn_sub_4D0B60_004d0b60__recomp},
    {"sub_4D0B80", 0x4D0B80, &recomp_gen::fn_sub_4D0B80_004d0b80, &recomp_gen::fn_sub_4D0B80_004d0b80__recomp},
    {"sub_4D0BA0", 0x4D0BA0, &recomp_gen::fn_sub_4D0BA0_004d0ba0, &recomp_gen::fn_sub_4D0BA0_004d0ba0__recomp},
    {"sub_4D0BC0", 0x4D0BC0, &recomp_gen::fn_sub_4D0BC0_004d0bc0, &recomp_gen::fn_sub_4D0BC0_004d0bc0__recomp},
    {"sub_4DFCB0", 0x4DFCB0, &recomp_gen::fn_sub_4DFCB0_004dfcb0, &recomp_gen::fn_sub_4DFCB0_004dfcb0__recomp},
    {"_sceMpegFlush", 0x501AE8, &recomp_gen::fn__sceMpegFlush_00501ae8, &recomp_gen::fn__sceMpegFlush_00501ae8__recomp},
    {"sceMc2FormatAsync", 0x513598, &recomp_gen::fn_sceMc2FormatAsync_00513598, &recomp_gen::fn_sceMc2FormatAsync_00513598__recomp},
    {"sceMc2WriteFileAsync", 0x513CC8, &recomp_gen::fn_sceMc2WriteFileAsync_00513cc8, &recomp_gen::fn_sceMc2WriteFileAsync_00513cc8__recomp},
    {"sceMc2CreateFileAsync", 0x513DE8, &recomp_gen::fn_sceMc2CreateFileAsync_00513de8, &recomp_gen::fn_sceMc2CreateFileAsync_00513de8__recomp},
    {"sceMc2MkdirAsync", 0x5140F8, &recomp_gen::fn_sceMc2MkdirAsync_005140f8, &recomp_gen::fn_sceMc2MkdirAsync_005140f8__recomp},
    {"_sceMcCoreWritePage", 0x51B8F0, &recomp_gen::fn__sceMcCoreWritePage_0051b8f0, &recomp_gen::fn__sceMcCoreWritePage_0051b8f0__recomp},
    {"_fwalk", 0x520410, &recomp_gen::fn__fwalk_00520410, &recomp_gen::fn__fwalk_00520410__recomp},
    {"__srefill", 0x523580, &recomp_gen::fn___srefill_00523580, &recomp_gen::fn___srefill_00523580__recomp},
    {"sceInsockGetErrnoMode", 0x537780, &recomp_gen::fn_sceInsockGetErrnoMode_00537780, &recomp_gen::fn_sceInsockGetErrnoMode_00537780__recomp},
    {"sub_53AFD8", 0x53AFD8, &recomp_gen::fn_sub_53AFD8_0053afd8, &recomp_gen::fn_sub_53AFD8_0053afd8__recomp},
    {"sub_53EC20", 0x53EC20, &recomp_gen::fn_sub_53EC20_0053ec20, &recomp_gen::fn_sub_53EC20_0053ec20__recomp},
    {"sub_547F30", 0x547F30, &recomp_gen::fn_sub_547F30_00547f30, &recomp_gen::fn_sub_547F30_00547f30__recomp},
    {"sub_548FC8", 0x548FC8, &recomp_gen::fn_sub_548FC8_00548fc8, &recomp_gen::fn_sub_548FC8_00548fc8__recomp},
    {"sub_549530", 0x549530, &recomp_gen::fn_sub_549530_00549530, &recomp_gen::fn_sub_549530_00549530__recomp},
    {"__env_lock_0", 0x54A630, &recomp_gen::fn___env_lock_0_0054a630, &recomp_gen::fn___env_lock_0_0054a630__recomp},
    {"sub_54F708", 0x54F708, &recomp_gen::fn_sub_54F708_0054f708, &recomp_gen::fn_sub_54F708_0054f708__recomp},
    {"sub_552BD0", 0x552BD0, &recomp_gen::fn_sub_552BD0_00552bd0, &recomp_gen::fn_sub_552BD0_00552bd0__recomp},
    {"sub_553188", 0x553188, &recomp_gen::fn_sub_553188_00553188, &recomp_gen::fn_sub_553188_00553188__recomp},
    {"sub_553230", 0x553230, &recomp_gen::fn_sub_553230_00553230, &recomp_gen::fn_sub_553230_00553230__recomp},
    {"sub_55A1D0", 0x55A1D0, &recomp_gen::fn_sub_55A1D0_0055a1d0, &recomp_gen::fn_sub_55A1D0_0055a1d0__recomp},
    {"dvCiStopTr", 0x55A638, &recomp_gen::fn_dvCiStopTr_0055a638, &recomp_gen::fn_dvCiStopTr_0055a638__recomp},
    {"dvci_analysis_flist", 0x55AB80, &recomp_gen::fn_dvci_analysis_flist_0055ab80, &recomp_gen::fn_dvci_analysis_flist_0055ab80__recomp},
    {"sub_55B0F8", 0x55B0F8, &recomp_gen::fn_sub_55B0F8_0055b0f8, &recomp_gen::fn_sub_55B0F8_0055b0f8__recomp},
    {"sub_55DA48", 0x55DA48, &recomp_gen::fn_sub_55DA48_0055da48, &recomp_gen::fn_sub_55DA48_0055da48__recomp},
    {"sub_5835F0", 0x5835F0, &recomp_gen::fn_sub_5835F0_005835f0, &recomp_gen::fn_sub_5835F0_005835f0__recomp},
    {"sub_5837A0", 0x5837A0, &recomp_gen::fn_sub_5837A0_005837a0, &recomp_gen::fn_sub_5837A0_005837a0__recomp},
    {"sub_5876F0", 0x5876F0, &recomp_gen::fn_sub_5876F0_005876f0, &recomp_gen::fn_sub_5876F0_005876f0__recomp},
    {"sub_589F70", 0x589F70, &recomp_gen::fn_sub_589F70_00589f70, &recomp_gen::fn_sub_589F70_00589f70__recomp},
    {"sub_58C228", 0x58C228, &recomp_gen::fn_sub_58C228_0058c228, &recomp_gen::fn_sub_58C228_0058c228__recomp},
    {"sub_595208", 0x595208, &recomp_gen::fn_sub_595208_00595208, &recomp_gen::fn_sub_595208_00595208__recomp},
    {"sub_597968", 0x597968, &recomp_gen::fn_sub_597968_00597968, &recomp_gen::fn_sub_597968_00597968__recomp},
    {"sub_599368", 0x599368, &recomp_gen::fn_sub_599368_00599368, &recomp_gen::fn_sub_599368_00599368__recomp},
    {"sub_5994F0", 0x5994F0, &recomp_gen::fn_sub_5994F0_005994f0, &recomp_gen::fn_sub_5994F0_005994f0__recomp},
    {"sub_59C8E0", 0x59C8E0, &recomp_gen::fn_sub_59C8E0_0059c8e0, &recomp_gen::fn_sub_59C8E0_0059c8e0__recomp},
    {"sub_59FEF8", 0x59FEF8, &recomp_gen::fn_sub_59FEF8_0059fef8, &recomp_gen::fn_sub_59FEF8_0059fef8__recomp},
};

// The argument kinds of each case ($a0..$a3, then $t0); a case not listed takes small integers. B a cleared 12 KiB block
// in the scratch area (small counts at +56 / +140, +60 / +64 pointing at cleared sub-blocks, a few small words), S a
// short C string, A a btlAction of gBtl's list, C the battle camera gBtl+32 aimed at a real action, H a type-7
// resource handle (7 << 10 | id), n 0..7, z 0 / 1, w 1 / 2, m -1..3, h -1..299, i 460..474 (sub_2DA930's ids), k
// 0..11, d 0..1099, l 0..31, e 0..399 (encounter ids), j 180..260 (sub_58C228's ids), c 16..79.
const std::map<std::string, const char*> kKinds = {
    {"sub_1050E0", "nnS"},  {"sub_1A46F0", "z"},    {"sub_1A92D0", "Bm"},
    {"sub_242720", "Bh"},   {"brItem_CreateStockOverBgTask", "zn"},           {"sub_2D8CF0", "A"},    {"sub_2D8DC0", "A"},
    {"sub_2D8E80", "Az"},   {"sub_2D89E0", "nk"},    {"sub_2D9B20", "A"},    {"sub_2DA810", "A"},    {"sub_2DA930", "ni"},
    {"sub_2DCFB0", "B"},    {"sub_2E6A20", "C"},     {"sub_2E70B0", "C"},    {"datUnitCreateEc", "e"},
    {"datUnitDestroyGenus", "B"},                    {"sub_3170C0", "BB"},   {"sub_31E8D0", "BwhBc"}, {"sub_324160", "B"},
    {"sub_3B64C0", "nBn"},  {"sub_3B8310", "Hz"},    {"sub_3B8690", "Hnn"},  {"sub_3B87F0", "HBnn"}, {"sub_3B89F0", "Hnn"},
    {"sub_3B8E10", "Hnnn"}, {"sub_3B8F30", "H"},     {"sub_3B95A0", "H"},    {"sub_3BB280", "H"},    {"sub_3BB400", "H"},
    {"sub_3BD8B0", "dnn"},  {"sub_3BE8E0", "ln"},    {"sub_3F4DE0", "nnnB"}, {"sub_404120", "nz"},   {"sub_406CA0", "nBB"},
    {"sub_40A7F0", "nBB"},  {"sub_40C9A0", "B"},     {"sub_40CAD0", "B"},    {"sub_40CC30", "nBB"},  {"sub_464020", "nBnn"},
    {"sub_4663D0", "B"},    {"sub_468DC0", "B"},     {"sub_469510", "Bn"},   {"sub_48DA30", "B"},    {"sub_48DAB0", "nwB"},
    {"sub_48EF80", "Bn"},   {"sub_4A9D80", "BBB"},   {"sub_4AE060", "B"},    {"sub_4AE110", "BB"},   {"sub_4B1A60", "B"},
    {"sub_4B1A70", "B"},    {"sub_4B3CC0", "B"},     {"sub_4B45B0", "zB"},   {"sub_4B6980", "B"},    {"sub_4C0240", "nS"},
    {"sub_4C0370", "B"},    {"sub_4C3D10", "B"},     {"sub_4CD620", "BB"},   {"_sceMpegFlush", "B"}, {"sceMc2WriteFileAsync", "nSnn"},
    {"sceMc2CreateFileAsync", "nS"},                 {"sceMc2MkdirAsync", "nS"}, {"_sceMcCoreWritePage", "zBnn"},
    {"_fwalk", "Bn"},       {"__srefill", "B"},      {"sub_53AFD8", "nnBc"}, {"sub_552BD0", "B"},    {"sub_553188", "B"},
    {"sub_553230", "Bk"},   {"sub_55A1D0", "B"},     {"dvCiStopTr", "B"},    {"dvci_analysis_flist", "BSnnn"},
    {"sub_55DA48", "Bn"},   {"sub_5835F0", "B"},     {"sub_5837A0", "B"},    {"sub_589F70", "B"},    {"sub_58C228", "Bjnnn"},
    {"sub_595208", "Bn"},   {"sub_597968", "B"},     {"sub_599368", "znB"},  {"sub_5994F0", "BB"},   {"sub_59C8E0", "BnBn"},
    {"sub_59FEF8", "BBB"},
};

const char* kinds_of(const char* name) {
    const auto it = kKinds.find(name);
    return it == kKinds.end() ? "nnnn" : it->second;
}

constexpr u32 kGBtl = 0x7CE3ECu;       // gBtl's slot ($gp - 18692)
constexpr u32 kActLinkNext = 1192;     // btlAction: the next action of gBtl+332's list (battle_core2.h)
constexpr u32 kActUnit = 48;           // btlAction: its btlUnit
constexpr u32 kCamera = 32;            // gBtl: the battle camera record (the shots' $a0)
constexpr u32 kCamAction = 224;        // camera: the btlAction it frames
constexpr u32 kString = kScratch + 0x3F000u;  // the S argument

struct Objects {
    u32 btl = 0;
    std::vector<u32> acts;
};

Objects objects_of(Machine& m) {
    Objects o;
    o.btl = r32(m, kGBtl);
    if (o.btl >= 0x100000u && o.btl < EEMemory::kMainRamSize) {
        for (u32 a = r32(m, o.btl + 332); a && a < EEMemory::kMainRamSize && o.acts.size() < 32; a = r32(m, a + kActLinkNext))
            if (r32(m, a + kActUnit) != 0) o.acts.push_back(a);
    } else {
        o.btl = 0;
    }
    return o;
}

bool needs_battle(const char* kinds) {
    for (const char* k = kinds; *k; ++k)
        if (*k == 'A' || *k == 'C') return true;
    return false;
}

// One argument of kind `k` (writes the world it needs); B blocks come from kScratch upwards.
u64 arg_of(Machine& m, char k, const Objects& o, std::mt19937& rng, u32& blk) {
    switch (k) {
    case 'A': return o.acts[rng() % o.acts.size()];
    case 'C': {
        const u32 cam = o.btl + kCamera;
        w32(m, cam + kCamAction, o.acts[rng() % o.acts.size()]);
        return cam;
    }
    case 'B': {
        const u32 b = kScratch + 0x4000u * blk++;
        std::memset(m.at(b), 0, 0x3000);
        w32(m, b + 56, 1 + rng() % 4);
        w32(m, b + 140, rng() % 6);
        w32(m, b + 60, b + 0x400);
        w32(m, b + 64, b + 0x800);
        w32(m, b + 20, rng() % 3);
        w32(m, b + 24, rng() % 64);
        w32(m, b + 0x800 + 56, 1 + rng() % 3);
        return b;
    }
    case 'S': {
        static const char* const strs[] = {"ab%dcd", "tex_rgba", "fe/sys.bin", "0123456789"};
        const char* s = strs[rng() % 4];
        std::memcpy(m.at(kString), s, std::strlen(s) + 1);
        return kString;
    }
    case 'H': return (7u << 10) | (rng() % 64);
    case 'z': return rng() % 2;
    case 'w': return 1 + rng() % 2;
    case 'm': return static_cast<u64>(static_cast<s64>(static_cast<int>(rng() % 5) - 1));
    case 'h': return static_cast<u64>(static_cast<s64>(static_cast<int>(rng() % 301) - 1));
    case 'i': return 460 + rng() % 15;
    case 'k': return rng() % 12;
    case 'd': return rng() % 1100;
    case 'l': return rng() % 32;
    case 'e': return rng() % 400;
    case 'j': return 180 + rng() % 81;
    case 'c': return 16 + rng() % 64;
    default: return rng() % 8;
    }
}

}  // namespace

TEST_CASE("game(sweep5d): every body equals its recompiled body on random worlds") {
    random_sweep(kCases, 0x01810000u, 0x10000u, 64);
}

// Every body on the packet's snapshots: arguments from the real structures (above), the snapshot restored between pairs.
// The pairs run on the stand-ins (every callee this build does not emit recorded); a pair whose original faults is run
// again as a plain pair, which compares the two stops.
TEST_CASE("game(sweep5d): every body on the replay snapshots with real structures") {
    struct Snap {
        const char* dir;
        u32 reps;
    };
    const Snap snaps[] = {{"b_5800", 4}, {"dorm_replay_4900", 2}, {"climb_ref_17000", 2}};
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    HwCheck hw;
    hw.gpr_mask = kAllGprs;
    int pairs = 0, stood = 0, stops = 0, used = 0;
    std::map<std::string, int> stop_of;
    for (const Snap& sn : snaps) {
        std::vector<u8> base;
        auto mp = real_machine(sn.dir, base);
        if (!mp) {
            MESSAGE("SKIP: no ELF or snapshot " << std::string(sn.dir));
            continue;
        }
        Machine& m = *mp;
        write_rw_slots(m);
        base.assign(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
        const Objects o = objects_of(m);
        ++used;
        MESSAGE(std::string(sn.dir) << ": gBtl " << hex64(o.btl) << ", " << o.acts.size() << " actions");
        const u32 reps = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : sn.reps;
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            const char* kinds = kinds_of(c.name);
            if (needs_battle(kinds) && (o.btl == 0 || o.acts.empty())) continue;
            for (u32 rep = 0; rep < reps; ++rep) {
                if (trace) std::fprintf(stderr, "%s %s rep %u\n", sn.dir, c.name, rep);
                const std::mt19937 rng0{rep * 104729u + c.addr + static_cast<u32>(used) * 7u};
                u64 a[5] = {};
                // the arguments and the world they need (the same draws after every reset)
                auto draw = [&](Machine& mm) {
                    std::mt19937 rng = rng0;
                    u32 blk = 0;
                    for (u64& x : a) x = rng() % 8;
                    for (std::size_t i = 0; i < 5 && kinds[i]; ++i) a[i] = arg_of(mm, kinds[i], o, rng, blk);
                    return rng();
                };
                const u32 seed = draw(m);
                ++pairs;
                try {
                    if (std::string(c.name) == "_sceMcCoreWritePage") {
                        // it resends until sceDbcSendData3 accepts (1) and reads the reply SyncDma returns: both stood in
                        run_case_w(m, base, kCases, c.name, Args{a[0], a[1], a[2], a[3]}, seed, [&](Machine& mm) { draw(mm); },
                                   [](StandInWorld& w) {
                                       if (!w.si.has(0x51D308u)) w.si.install_recorder(0x51D308u, "sceDbcSendData3", 1);
                                       if (!w.si.has(0x51AD10u)) w.si.install_recorder(0x51AD10u, "SyncDma", kScratch + 0x3E000u);
                                   });
                    } else {
                        run_case(m, base, kCases, c.name, Args{a[0], a[1], a[2], a[3]}, seed, [&](Machine& mm) { draw(mm); },
                                 0, {{GPR_T0, a[4]}});
                    }
                    ++stood;
                } catch (const rt_test::FatalEvent&) {
                    // a guest fault in the original: the plain pair compares the two stops
                    reset(m, base);
                    draw(m);
                    HwCheck h = hw;
                    h.gpr_in[GPR_T0] = a[4];
                    const hgp::Run r = hgp::pair(m, c.hand, c.recomp, Args{a[0], a[1], a[2], a[3]}, seed, c.name, h);
                    if (r.stopped) {
                        ++stops;
                        ++stop_of[std::string(c.name) + " (" + r.what.substr(0, 40) + " at " + hex64(r.stop_pc) + ")"];
                    }
                }
                reset(m, base);
            }
        }
    }
    std::string why;
    for (const auto& [k, n] : stop_of) why += " " + k + " x" + std::to_string(n) + ";";
    MESSAGE("snapshots: " << pairs << " pairs on " << used << " snapshot(s), " << stood << " on the stand-ins, " << stops
                          << " ended at a compared fault stop:" << why.substr(0, 1500));
}

// The battle table callbacks on b_5800's gBtl: sub_2DA930 maps the ids 463..471 to gBtl+2580 (2, 3, 4, 5, 7, 8, 9, 10,
// 6) and leaves it for other ids; sub_2DB8D0 resets the block (+2580 = 6, +2588 = 0, +2592 = -1, +2596 = -1 (s16)).
TEST_CASE("game(sweep5d): the gBtl+2580 kind of sub_2DA930 and the reset of sub_2DB8D0") {
    std::vector<u8> base;
    auto mp = real_machine("b_5800", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or snapshot b_5800");
        return;
    }
    Machine& m = *mp;
    const u32 btl = r32(m, kGBtl);
    REQUIRE(btl != 0u);
    const struct {
        u32 id;
        u32 kind;
    } rows[] = {{463, 2}, {465, 4}, {467, 7}, {470, 10}, {471, 6}};
    for (const auto& r : rows) {
        run_case(m, base, kCases, "sub_2DA930", {0, r.id, 0, 0}, 900 + r.id, [&](Machine& mm) { w16(mm, btl + 2580, 0x55); });
        INFO("id " << r.id);
        CHECK(r16(m, btl + 2580) == r.kind);
    }
    run_case(m, base, kCases, "sub_2DA930", {0, 500, 0, 0}, 901, [&](Machine& mm) { w16(mm, btl + 2580, 0x55); });
    CHECK(r16(m, btl + 2580) == 0x55u);
    run_case(m, base, kCases, "sub_2DB8D0", {0, 0, 0, 0}, 902, [&](Machine& mm) {
        w16(mm, btl + 2580, 0x55);
        w32(mm, btl + 2588, 0x1234);
        w32(mm, btl + 2592, 7);
    });
    CHECK(r16(m, btl + 2580) == 6u);
    CHECK(r32(m, btl + 2588) == 0u);
    CHECK(r32(m, btl + 2592) == 0xFFFFFFFFu);
    CHECK(r16(m, btl + 2596) == 0xFFFFu);
}

// Small record helpers on cleared blocks: sub_4AE110 copies 16 bytes to +144 and sets +8 bit 3; sub_55DA48 stores
// the minimum value (+20) only for 0 <= value <= +24; sub_59FEF8 hands out +24 / +28 when +20 is 1, else zeros.
TEST_CASE("game(sweep5d): sub_4AE110, sub_55DA48 and sub_59FEF8 on their records") {
    std::vector<u8> base;
    auto mp = real_machine("dorm_replay_4900", base);
    if (!mp) {
        MESSAGE("SKIP: no ELF or snapshot dorm_replay_4900");
        return;
    }
    Machine& m = *mp;
    const u32 R = kScratch, S = kScratch + 0x400, P = kScratch + 0x800, Q = kScratch + 0x810;
    auto clear = [&](Machine& mm) { std::memset(mm.at(kScratch), 0, 0x1000); };

    run_case(m, base, kCases, "sub_4AE110", {R, S, 0, 0}, 910, [&](Machine& mm) {
        clear(mm);
        w32(mm, R + 8, 0x11);
        for (u32 i = 0; i < 16; ++i) w8(mm, S + i, static_cast<u8>(0xA0 + i));
    });
    CHECK(r32(m, R + 8) == 0x19u);
    for (u32 i = 0; i < 16; ++i) CHECK(r8(m, R + 144 + i) == 0xA0u + i);

    for (const u32 v : {5u, 10u, 11u}) {
        run_case(m, base, kCases, "sub_55DA48", {R, v, 0, 0}, 920 + v, [&](Machine& mm) {
            clear(mm);
            w32(mm, R + 24, 10);
            w32(mm, R + 20, 3);
        });
        INFO("value " << v);
        CHECK(r32(m, R + 20) == (v <= 10 ? v : 3u));
    }

    for (const u32 state : {1u, 0u}) {
        run_case(m, base, kCases, "sub_59FEF8", {R, P, Q, 0}, 930 + state, [&](Machine& mm) {
            clear(mm);
            w32(mm, R + 20, state);
            w32(mm, R + 24, 0x1111);
            w32(mm, R + 28, 0x2222);
            w32(mm, P, 0xDEAD);
            w32(mm, Q, 0xBEEF);
        });
        INFO("state " << state);
        CHECK(r32(m, P) == (state == 1 ? 0x1111u : 0u));
        CHECK(r32(m, Q) == (state == 1 ? 0x2222u : 0u));
    }
}

#else

TEST_CASE("game(sweep5d): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
