// Pair tests of slice render_rw9 (game/src/render/render_rw9.cpp): RenderWare, ninth pass -- the clump / atomic /
// geometry core and their streams, the material list, the world's create / destroy, RpMatFX's material effects, PTank's
// geometry set-up, Rt2d paths / shapes / scenes / maestro, the RtFS helpers, the memory module, RW strings and vector
// transforms, the image module (search path, formats, gamma, palettes) and the texture readers, and the sky driver's
// raster / texture formats, native stream readers, SkySystem, palette upload and texture cache. Every body runs
// against its recompiled body and tests/game/handgen_pairs.h compares the whole register file
// and cycles at every check point and at the return / stop, all 32 MiB of RAM (the dead stack included), the
// scratchpad, the BIOS window and the bus log; the stand-ins' call logs and heaps must be equal too (stand_ins.h).
//   * RpGeometryCreate's record layout for vertex / triangle counts and format flags, and its refusals; a create /
//     destroy round trip leaves no heap block behind;
//   * RpAtomicCreate's defaults; RpAtomicClone and RpClumpClone of every live atomic / clump of the snapshots: the
//     same geometry, one more reference per clone, a cloned frame hierarchy, the same atomic count;
//   * the image gamma tables against powf, the gamma correction of 32-bit images and 8-bit palettes, the palette
//     expansion of rwImageCopyPixels, the sky driver's CLUT layout and colour packing, its raster format rules;
//   * the RW string helpers against the host's, the vector transforms against host float math;
//   * every body on the three snapshots with built records, and the random-world sweep (the p3fes_handgen skeleton).
// P3FES_HG_SEEDS sets the pairs per function of the random sweep, P3FES_HG_ONLY one function, P3FES_HG_TRACE traces.
// Every random draw is its own statement (argument evaluation order differs between MSVC and clang-cl).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/render_rw9.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <memory>
#include <random>
#include <set>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_sub_467FD0_00467fd0(EEContext&);  // generated body
void fn_sub_467FD0_00467fd0__recomp(EEContext&);  // recompiled
void fn_sub_468560_00468560(EEContext&);  // generated body
void fn_sub_468560_00468560__recomp(EEContext&);  // recompiled
void fn_sub_468EA0_00468ea0(EEContext&);  // generated body
void fn_sub_468EA0_00468ea0__recomp(EEContext&);  // recompiled
void fn_sub_469770_00469770(EEContext&);  // generated body
void fn_sub_469770_00469770__recomp(EEContext&);  // recompiled
void fn_sub_469840_00469840(EEContext&);  // generated body
void fn_sub_469840_00469840__recomp(EEContext&);  // recompiled
void fn_sub_4734D0_004734d0(EEContext&);  // generated body
void fn_sub_4734D0_004734d0__recomp(EEContext&);  // recompiled
void fn_sub_474260_00474260(EEContext&);  // generated body
void fn_sub_474260_00474260__recomp(EEContext&);  // recompiled
void fn_sub_474630_00474630(EEContext&);  // generated body
void fn_sub_474630_00474630__recomp(EEContext&);  // recompiled
void fn_sub_474820_00474820(EEContext&);  // generated body
void fn_sub_474820_00474820__recomp(EEContext&);  // recompiled
void fn_sub_474F20_00474f20(EEContext&);  // generated body
void fn_sub_474F20_00474f20__recomp(EEContext&);  // recompiled
void fn_sub_475CB0_00475cb0(EEContext&);  // generated body
void fn_sub_475CB0_00475cb0__recomp(EEContext&);  // recompiled
void fn_sub_475D60_00475d60(EEContext&);  // generated body
void fn_sub_475D60_00475d60__recomp(EEContext&);  // recompiled
void fn_sub_478E80_00478e80(EEContext&);  // generated body
void fn_sub_478E80_00478e80__recomp(EEContext&);  // recompiled
void fn_sub_47A210_0047a210(EEContext&);  // generated body
void fn_sub_47A210_0047a210__recomp(EEContext&);  // recompiled
void fn_sub_490050_00490050(EEContext&);  // generated body
void fn_sub_490050_00490050__recomp(EEContext&);  // recompiled
void fn_sub_4908D0_004908d0(EEContext&);  // generated body
void fn_sub_4908D0_004908d0__recomp(EEContext&);  // recompiled
void fn_sub_490980_00490980(EEContext&);  // generated body
void fn_sub_490980_00490980__recomp(EEContext&);  // recompiled
void fn_sub_490D90_00490d90(EEContext&);  // generated body
void fn_sub_490D90_00490d90__recomp(EEContext&);  // recompiled
void fn_sub_490DC0_00490dc0(EEContext&);  // generated body
void fn_sub_490DC0_00490dc0__recomp(EEContext&);  // recompiled
void fn_sub_491880_00491880(EEContext&);  // generated body
void fn_sub_491880_00491880__recomp(EEContext&);  // recompiled
void fn_sub_4919B0_004919b0(EEContext&);  // generated body
void fn_sub_4919B0_004919b0__recomp(EEContext&);  // recompiled
void fn_sub_491B40_00491b40(EEContext&);  // generated body
void fn_sub_491B40_00491b40__recomp(EEContext&);  // recompiled
void fn_sub_491CC0_00491cc0(EEContext&);  // generated body
void fn_sub_491CC0_00491cc0__recomp(EEContext&);  // recompiled
void fn_sub_4920A0_004920a0(EEContext&);  // generated body
void fn_sub_4920A0_004920a0__recomp(EEContext&);  // recompiled
void fn_sub_492D50_00492d50(EEContext&);  // generated body
void fn_sub_492D50_00492d50__recomp(EEContext&);  // recompiled
void fn_sub_493710_00493710(EEContext&);  // generated body
void fn_sub_493710_00493710__recomp(EEContext&);  // recompiled
void fn_sub_493B60_00493b60(EEContext&);  // generated body
void fn_sub_493B60_00493b60__recomp(EEContext&);  // recompiled
void fn_sub_493CB0_00493cb0(EEContext&);  // generated body
void fn_sub_493CB0_00493cb0__recomp(EEContext&);  // recompiled
void fn_sub_495260_00495260(EEContext&);  // generated body
void fn_sub_495260_00495260__recomp(EEContext&);  // recompiled
void fn_sub_4954C0_004954c0(EEContext&);  // generated body
void fn_sub_4954C0_004954c0__recomp(EEContext&);  // recompiled
void fn_sub_49A290_0049a290(EEContext&);  // generated body
void fn_sub_49A290_0049a290__recomp(EEContext&);  // recompiled
void fn_sub_49A400_0049a400(EEContext&);  // generated body
void fn_sub_49A400_0049a400__recomp(EEContext&);  // recompiled
void fn_sub_49B3F0_0049b3f0(EEContext&);  // generated body
void fn_sub_49B3F0_0049b3f0__recomp(EEContext&);  // recompiled
void fn_sub_49E4F0_0049e4f0(EEContext&);  // generated body
void fn_sub_49E4F0_0049e4f0__recomp(EEContext&);  // recompiled
void fn_sub_4A4D60_004a4d60(EEContext&);  // generated body
void fn_sub_4A4D60_004a4d60__recomp(EEContext&);  // recompiled
void fn_sub_4A6630_004a6630(EEContext&);  // generated body
void fn_sub_4A6630_004a6630__recomp(EEContext&);  // recompiled
void fn_sub_4AA550_004aa550(EEContext&);  // generated body
void fn_sub_4AA550_004aa550__recomp(EEContext&);  // recompiled
void fn_sub_4AA5C0_004aa5c0(EEContext&);  // generated body
void fn_sub_4AA5C0_004aa5c0__recomp(EEContext&);  // recompiled
void fn_sub_4AB200_004ab200(EEContext&);  // generated body
void fn_sub_4AB200_004ab200__recomp(EEContext&);  // recompiled
void fn_sub_4AC570_004ac570(EEContext&);  // generated body
void fn_sub_4AC570_004ac570__recomp(EEContext&);  // recompiled
void fn_sub_4AC5F0_004ac5f0(EEContext&);  // generated body
void fn_sub_4AC5F0_004ac5f0__recomp(EEContext&);  // recompiled
void fn_sub_4AC870_004ac870(EEContext&);  // generated body
void fn_sub_4AC870_004ac870__recomp(EEContext&);  // recompiled
void fn_sub_4AC920_004ac920(EEContext&);  // generated body
void fn_sub_4AC920_004ac920__recomp(EEContext&);  // recompiled
void fn_sub_4ACB10_004acb10(EEContext&);  // generated body
void fn_sub_4ACB10_004acb10__recomp(EEContext&);  // recompiled
void fn_sub_4ADBD0_004adbd0(EEContext&);  // generated body
void fn_sub_4ADBD0_004adbd0__recomp(EEContext&);  // recompiled
void fn_sub_4ADE90_004ade90(EEContext&);  // generated body
void fn_sub_4ADE90_004ade90__recomp(EEContext&);  // recompiled
void fn_sub_4AE3B0_004ae3b0(EEContext&);  // generated body
void fn_sub_4AE3B0_004ae3b0__recomp(EEContext&);  // recompiled
void fn_sub_4AE5A0_004ae5a0(EEContext&);  // generated body
void fn_sub_4AE5A0_004ae5a0__recomp(EEContext&);  // recompiled
void fn_sub_4AE790_004ae790(EEContext&);  // generated body
void fn_sub_4AE790_004ae790__recomp(EEContext&);  // recompiled
void fn_sub_4AEBF0_004aebf0(EEContext&);  // generated body
void fn_sub_4AEBF0_004aebf0__recomp(EEContext&);  // recompiled
void fn_sub_4AEEA0_004aeea0(EEContext&);  // generated body
void fn_sub_4AEEA0_004aeea0__recomp(EEContext&);  // recompiled
void fn_sub_4AF130_004af130(EEContext&);  // generated body
void fn_sub_4AF130_004af130__recomp(EEContext&);  // recompiled
void fn_sub_4AF210_004af210(EEContext&);  // generated body
void fn_sub_4AF210_004af210__recomp(EEContext&);  // recompiled
void fn_sub_4AF340_004af340(EEContext&);  // generated body
void fn_sub_4AF340_004af340__recomp(EEContext&);  // recompiled
void fn_sub_4AF760_004af760(EEContext&);  // generated body
void fn_sub_4AF760_004af760__recomp(EEContext&);  // recompiled
void fn_sub_4AF940_004af940(EEContext&);  // generated body
void fn_sub_4AF940_004af940__recomp(EEContext&);  // recompiled
void fn_sub_4AFFE0_004affe0(EEContext&);  // generated body
void fn_sub_4AFFE0_004affe0__recomp(EEContext&);  // recompiled
void fn_sub_4B1290_004b1290(EEContext&);  // generated body
void fn_sub_4B1290_004b1290__recomp(EEContext&);  // recompiled
void fn_sub_4B1620_004b1620(EEContext&);  // generated body
void fn_sub_4B1620_004b1620__recomp(EEContext&);  // recompiled
void fn_sub_4B1BA0_004b1ba0(EEContext&);  // generated body
void fn_sub_4B1BA0_004b1ba0__recomp(EEContext&);  // recompiled
void fn_sub_4B26A0_004b26a0(EEContext&);  // generated body
void fn_sub_4B26A0_004b26a0__recomp(EEContext&);  // recompiled
void fn_sub_4B2810_004b2810(EEContext&);  // generated body
void fn_sub_4B2810_004b2810__recomp(EEContext&);  // recompiled
void fn_sub_4B2AD0_004b2ad0(EEContext&);  // generated body
void fn_sub_4B2AD0_004b2ad0__recomp(EEContext&);  // recompiled
void fn_sub_4B2BC0_004b2bc0(EEContext&);  // generated body
void fn_sub_4B2BC0_004b2bc0__recomp(EEContext&);  // recompiled
void fn_sub_4B2E20_004b2e20(EEContext&);  // generated body
void fn_sub_4B2E20_004b2e20__recomp(EEContext&);  // recompiled
void fn_sub_4B2F10_004b2f10(EEContext&);  // generated body
void fn_sub_4B2F10_004b2f10__recomp(EEContext&);  // recompiled
void fn_sub_4B3160_004b3160(EEContext&);  // generated body
void fn_sub_4B3160_004b3160__recomp(EEContext&);  // recompiled
void fn_sub_4B3440_004b3440(EEContext&);  // generated body
void fn_sub_4B3440_004b3440__recomp(EEContext&);  // recompiled
void fn_sub_4B3730_004b3730(EEContext&);  // generated body
void fn_sub_4B3730_004b3730__recomp(EEContext&);  // recompiled
void fn_sub_4B3900_004b3900(EEContext&);  // generated body
void fn_sub_4B3900_004b3900__recomp(EEContext&);  // recompiled
void fn_sub_4B3AC0_004b3ac0(EEContext&);  // generated body
void fn_sub_4B3AC0_004b3ac0__recomp(EEContext&);  // recompiled
void fn_sub_4B4230_004b4230(EEContext&);  // generated body
void fn_sub_4B4230_004b4230__recomp(EEContext&);  // recompiled
void fn_sub_4B42E0_004b42e0(EEContext&);  // generated body
void fn_sub_4B42E0_004b42e0__recomp(EEContext&);  // recompiled
void fn_sub_4B4410_004b4410(EEContext&);  // generated body
void fn_sub_4B4410_004b4410__recomp(EEContext&);  // recompiled
void fn_sub_4B4790_004b4790(EEContext&);  // generated body
void fn_sub_4B4790_004b4790__recomp(EEContext&);  // recompiled
void fn_sub_4B47D0_004b47d0(EEContext&);  // generated body
void fn_sub_4B47D0_004b47d0__recomp(EEContext&);  // recompiled
void fn_sub_4B4860_004b4860(EEContext&);  // generated body
void fn_sub_4B4860_004b4860__recomp(EEContext&);  // recompiled
void fn_sub_4B4CC0_004b4cc0(EEContext&);  // generated body
void fn_sub_4B4CC0_004b4cc0__recomp(EEContext&);  // recompiled
void fn_sub_4B4D70_004b4d70(EEContext&);  // generated body
void fn_sub_4B4D70_004b4d70__recomp(EEContext&);  // recompiled
void fn_sub_4B4EB0_004b4eb0(EEContext&);  // generated body
void fn_sub_4B4EB0_004b4eb0__recomp(EEContext&);  // recompiled
void fn_sub_4B5D80_004b5d80(EEContext&);  // generated body
void fn_sub_4B5D80_004b5d80__recomp(EEContext&);  // recompiled
void fn_sub_4B5EC0_004b5ec0(EEContext&);  // generated body
void fn_sub_4B5EC0_004b5ec0__recomp(EEContext&);  // recompiled
void fn_sub_4B6040_004b6040(EEContext&);  // generated body
void fn_sub_4B6040_004b6040__recomp(EEContext&);  // recompiled
void fn_sub_4B7630_004b7630(EEContext&);  // generated body
void fn_sub_4B7630_004b7630__recomp(EEContext&);  // recompiled
void fn_sub_4B7690_004b7690(EEContext&);  // generated body
void fn_sub_4B7690_004b7690__recomp(EEContext&);  // recompiled
void fn_RwFsInit_004bfbb0(EEContext&);  // generated body
void fn_RwFsInit_004bfbb0__recomp(EEContext&);  // recompiled
void fn_sub_4BFEA0_004bfea0(EEContext&);  // generated body
void fn_sub_4BFEA0_004bfea0__recomp(EEContext&);  // recompiled
void fn_sub_4C00F0_004c00f0(EEContext&);  // generated body
void fn_sub_4C00F0_004c00f0__recomp(EEContext&);  // recompiled
void fn_sub_4C06C0_004c06c0(EEContext&);  // generated body
void fn_sub_4C06C0_004c06c0__recomp(EEContext&);  // recompiled
void fn_j_malloc_004c4420(EEContext&);  // generated body
void fn_j_malloc_004c4420__recomp(EEContext&);  // recompiled
void fn_j_realloc_004c4430(EEContext&);  // generated body
void fn_j_realloc_004c4430__recomp(EEContext&);  // recompiled
void fn_j_calloc_004c4440(EEContext&);  // generated body
void fn_j_calloc_004c4440__recomp(EEContext&);  // recompiled
void fn_sub_4C4450_004c4450(EEContext&);  // generated body
void fn_sub_4C4450_004c4450__recomp(EEContext&);  // recompiled
void fn_sub_4C4570_004c4570(EEContext&);  // generated body
void fn_sub_4C4570_004c4570__recomp(EEContext&);  // recompiled
void fn_sub_4C6640_004c6640(EEContext&);  // generated body
void fn_sub_4C6640_004c6640__recomp(EEContext&);  // recompiled
void fn_sub_4C6700_004c6700(EEContext&);  // generated body
void fn_sub_4C6700_004c6700__recomp(EEContext&);  // recompiled
void fn_sub_4C67A0_004c67a0(EEContext&);  // generated body
void fn_sub_4C67A0_004c67a0__recomp(EEContext&);  // recompiled
void fn_sub_4C6840_004c6840(EEContext&);  // generated body
void fn_sub_4C6840_004c6840__recomp(EEContext&);  // recompiled
void fn_sub_4C68C0_004c68c0(EEContext&);  // generated body
void fn_sub_4C68C0_004c68c0__recomp(EEContext&);  // recompiled
void fn_sub_4C6D00_004c6d00(EEContext&);  // generated body
void fn_sub_4C6D00_004c6d00__recomp(EEContext&);  // recompiled
void fn_sub_4C7020_004c7020(EEContext&);  // generated body
void fn_sub_4C7020_004c7020__recomp(EEContext&);  // recompiled
void fn_sub_4C70A0_004c70a0(EEContext&);  // generated body
void fn_sub_4C70A0_004c70a0__recomp(EEContext&);  // recompiled
void fn_sub_4C71C0_004c71c0(EEContext&);  // generated body
void fn_sub_4C71C0_004c71c0__recomp(EEContext&);  // recompiled
void fn_sub_4C7208_004c7208(EEContext&);  // generated body
void fn_sub_4C7208_004c7208__recomp(EEContext&);  // recompiled
void fn_sub_4C7210_004c7210(EEContext&);  // generated body
void fn_sub_4C7210_004c7210__recomp(EEContext&);  // recompiled
void fn_sub_4C7258_004c7258(EEContext&);  // generated body
void fn_sub_4C7258_004c7258__recomp(EEContext&);  // recompiled
void fn_sub_4C7260_004c7260(EEContext&);  // generated body
void fn_sub_4C7260_004c7260__recomp(EEContext&);  // recompiled
void fn_sub_4C72A0_004c72a0(EEContext&);  // generated body
void fn_sub_4C72A0_004c72a0__recomp(EEContext&);  // recompiled
void fn_sub_4C7400_004c7400(EEContext&);  // generated body
void fn_sub_4C7400_004c7400__recomp(EEContext&);  // recompiled
void fn_sub_4C7410_004c7410(EEContext&);  // generated body
void fn_sub_4C7410_004c7410__recomp(EEContext&);  // recompiled
void fn_sub_4C7520_004c7520(EEContext&);  // generated body
void fn_sub_4C7520_004c7520__recomp(EEContext&);  // recompiled
void fn_sub_4C78A0_004c78a0(EEContext&);  // generated body
void fn_sub_4C78A0_004c78a0__recomp(EEContext&);  // recompiled
void fn_sub_4C79E0_004c79e0(EEContext&);  // generated body
void fn_sub_4C79E0_004c79e0__recomp(EEContext&);  // recompiled
void fn_sub_4C7B60_004c7b60(EEContext&);  // generated body
void fn_sub_4C7B60_004c7b60__recomp(EEContext&);  // recompiled
void fn_sub_4CA190_004ca190(EEContext&);  // generated body
void fn_sub_4CA190_004ca190__recomp(EEContext&);  // recompiled
void fn_sub_4CAAC0_004caac0(EEContext&);  // generated body
void fn_sub_4CAAC0_004caac0__recomp(EEContext&);  // recompiled
void fn_sub_4CBA20_004cba20(EEContext&);  // generated body
void fn_sub_4CBA20_004cba20__recomp(EEContext&);  // recompiled
void fn_sub_4CC5C0_004cc5c0(EEContext&);  // generated body
void fn_sub_4CC5C0_004cc5c0__recomp(EEContext&);  // recompiled
void fn_sub_4CC6D0_004cc6d0(EEContext&);  // generated body
void fn_sub_4CC6D0_004cc6d0__recomp(EEContext&);  // recompiled
void fn_sub_4CCA60_004cca60(EEContext&);  // generated body
void fn_sub_4CCA60_004cca60__recomp(EEContext&);  // recompiled
void fn_sub_4CCAC0_004ccac0(EEContext&);  // generated body
void fn_sub_4CCAC0_004ccac0__recomp(EEContext&);  // recompiled
void fn_sub_4CCC30_004ccc30(EEContext&);  // generated body
void fn_sub_4CCC30_004ccc30__recomp(EEContext&);  // recompiled
void fn_sub_4CCD20_004ccd20(EEContext&);  // generated body
void fn_sub_4CCD20_004ccd20__recomp(EEContext&);  // recompiled
void fn_sub_4CCD50_004ccd50(EEContext&);  // generated body
void fn_sub_4CCD50_004ccd50__recomp(EEContext&);  // recompiled
void fn_sub_4CCF10_004ccf10(EEContext&);  // generated body
void fn_sub_4CCF10_004ccf10__recomp(EEContext&);  // recompiled
void fn_sub_4CD260_004cd260(EEContext&);  // generated body
void fn_sub_4CD260_004cd260__recomp(EEContext&);  // recompiled
void fn_sub_4CD940_004cd940(EEContext&);  // generated body
void fn_sub_4CD940_004cd940__recomp(EEContext&);  // recompiled
void fn_sub_4CDB50_004cdb50(EEContext&);  // generated body
void fn_sub_4CDB50_004cdb50__recomp(EEContext&);  // recompiled
void fn_sub_4CEE30_004cee30(EEContext&);  // generated body
void fn_sub_4CEE30_004cee30__recomp(EEContext&);  // recompiled
void fn_sub_4CF690_004cf690(EEContext&);  // generated body
void fn_sub_4CF690_004cf690__recomp(EEContext&);  // recompiled
void fn_sub_4CF790_004cf790(EEContext&);  // generated body
void fn_sub_4CF790_004cf790__recomp(EEContext&);  // recompiled
void fn_sub_4CF9B0_004cf9b0(EEContext&);  // generated body
void fn_sub_4CF9B0_004cf9b0__recomp(EEContext&);  // recompiled
void fn_sub_4CFD30_004cfd30(EEContext&);  // generated body
void fn_sub_4CFD30_004cfd30__recomp(EEContext&);  // recompiled
void fn_sub_4D05F0_004d05f0(EEContext&);  // generated body
void fn_sub_4D05F0_004d05f0__recomp(EEContext&);  // recompiled
void fn_sub_4D0640_004d0640(EEContext&);  // generated body
void fn_sub_4D0640_004d0640__recomp(EEContext&);  // recompiled
void fn_sub_4D0AC0_004d0ac0(EEContext&);  // generated body
void fn_sub_4D0AC0_004d0ac0__recomp(EEContext&);  // recompiled
void fn_sub_4D11D0_004d11d0(EEContext&);  // generated body
void fn_sub_4D11D0_004d11d0__recomp(EEContext&);  // recompiled
void fn_RpSkySelectDeepZBuffer_004d82a0(EEContext&);  // generated body
void fn_RpSkySelectDeepZBuffer_004d82a0__recomp(EEContext&);  // recompiled
void fn_sub_4D8300_004d8300(EEContext&);  // generated body
void fn_sub_4D8300_004d8300__recomp(EEContext&);  // recompiled
void fn_sub_4D8310_004d8310(EEContext&);  // generated body
void fn_sub_4D8310_004d8310__recomp(EEContext&);  // recompiled
void fn_sub_4D83C0_004d83c0(EEContext&);  // generated body
void fn_sub_4D83C0_004d83c0__recomp(EEContext&);  // recompiled
void fn_sub_4D9520_004d9520(EEContext&);  // generated body
void fn_sub_4D9520_004d9520__recomp(EEContext&);  // recompiled
void fn_sub_4D9BC0_004d9bc0(EEContext&);  // generated body
void fn_sub_4D9BC0_004d9bc0__recomp(EEContext&);  // recompiled
void fn_sub_4DCEA0_004dcea0(EEContext&);  // generated body
void fn_sub_4DCEA0_004dcea0__recomp(EEContext&);  // recompiled
void fn_sub_4DF0E0_004df0e0(EEContext&);  // generated body
void fn_sub_4DF0E0_004df0e0__recomp(EEContext&);  // recompiled
void fn_sub_4DF3F0_004df3f0(EEContext&);  // generated body
void fn_sub_4DF3F0_004df3f0__recomp(EEContext&);  // recompiled
void fn_sub_4DF9D0_004df9d0(EEContext&);  // generated body
void fn_sub_4DF9D0_004df9d0__recomp(EEContext&);  // recompiled
void fn_sub_4DFCA0_004dfca0(EEContext&);  // generated body
void fn_sub_4DFCA0_004dfca0__recomp(EEContext&);  // recompiled
void fn_sub_4DFCC0_004dfcc0(EEContext&);  // generated body
void fn_sub_4DFCC0_004dfcc0__recomp(EEContext&);  // recompiled
void fn_sub_4E00E0_004e00e0(EEContext&);  // generated body
void fn_sub_4E00E0_004e00e0__recomp(EEContext&);  // recompiled
void fn_SkySystem_004e2b70(EEContext&);  // generated body
void fn_SkySystem_004e2b70__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_2_004e2f00(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_2_004e2f00__recomp(EEContext&);  // recompiled
void fn_sub_4E3090_004e3090(EEContext&);  // generated body
void fn_sub_4E3090_004e3090__recomp(EEContext&);  // recompiled
void fn_sub_4E3550_004e3550(EEContext&);  // generated body
void fn_sub_4E3550_004e3550__recomp(EEContext&);  // recompiled
void fn_sub_4E40B0_004e40b0(EEContext&);  // generated body
void fn_sub_4E40B0_004e40b0__recomp(EEContext&);  // recompiled
void fn_sub_4E4130_004e4130(EEContext&);  // generated body
void fn_sub_4E4130_004e4130__recomp(EEContext&);  // recompiled
void fn_sub_4E98A0_004e98a0(EEContext&);  // generated body
void fn_sub_4E98A0_004e98a0__recomp(EEContext&);  // recompiled
void fn_sub_4EAC00_004eac00(EEContext&);  // generated body
void fn_sub_4EAC00_004eac00__recomp(EEContext&);  // recompiled
void fn_sub_4EB8C0_004eb8c0(EEContext&);  // generated body
void fn_sub_4EB8C0_004eb8c0__recomp(EEContext&);  // recompiled
void fn_sub_4EEC10_004eec10(EEContext&);  // generated body
void fn_sub_4EEC10_004eec10__recomp(EEContext&);  // recompiled
void fn_sub_4EF1D0_004ef1d0(EEContext&);  // generated body
void fn_sub_4EF1D0_004ef1d0__recomp(EEContext&);  // recompiled
void fn_sub_4EF9F0_004ef9f0(EEContext&);  // generated body
void fn_sub_4EF9F0_004ef9f0__recomp(EEContext&);  // recompiled
void fn_sub_4F02E0_004f02e0(EEContext&);  // generated body
void fn_sub_4F02E0_004f02e0__recomp(EEContext&);  // recompiled
void fn_sub_4F0AD0_004f0ad0(EEContext&);  // generated body
void fn_sub_4F0AD0_004f0ad0__recomp(EEContext&);  // recompiled
void fn_sub_4F1E10_004f1e10(EEContext&);  // generated body
void fn_sub_4F1E10_004f1e10__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_467FD0", 0x467FD0, &recomp_gen::fn_sub_467FD0_00467fd0, &recomp_gen::fn_sub_467FD0_00467fd0__recomp},
    {"sub_468560", 0x468560, &recomp_gen::fn_sub_468560_00468560, &recomp_gen::fn_sub_468560_00468560__recomp},
    {"sub_468EA0", 0x468EA0, &recomp_gen::fn_sub_468EA0_00468ea0, &recomp_gen::fn_sub_468EA0_00468ea0__recomp},
    {"sub_469770", 0x469770, &recomp_gen::fn_sub_469770_00469770, &recomp_gen::fn_sub_469770_00469770__recomp},
    {"sub_469840", 0x469840, &recomp_gen::fn_sub_469840_00469840, &recomp_gen::fn_sub_469840_00469840__recomp},
    {"sub_4734D0", 0x4734D0, &recomp_gen::fn_sub_4734D0_004734d0, &recomp_gen::fn_sub_4734D0_004734d0__recomp},
    {"sub_474260", 0x474260, &recomp_gen::fn_sub_474260_00474260, &recomp_gen::fn_sub_474260_00474260__recomp},
    {"sub_474630", 0x474630, &recomp_gen::fn_sub_474630_00474630, &recomp_gen::fn_sub_474630_00474630__recomp},
    {"sub_474820", 0x474820, &recomp_gen::fn_sub_474820_00474820, &recomp_gen::fn_sub_474820_00474820__recomp},
    {"sub_474F20", 0x474F20, &recomp_gen::fn_sub_474F20_00474f20, &recomp_gen::fn_sub_474F20_00474f20__recomp},
    {"sub_475CB0", 0x475CB0, &recomp_gen::fn_sub_475CB0_00475cb0, &recomp_gen::fn_sub_475CB0_00475cb0__recomp},
    {"sub_475D60", 0x475D60, &recomp_gen::fn_sub_475D60_00475d60, &recomp_gen::fn_sub_475D60_00475d60__recomp},
    {"sub_478E80", 0x478E80, &recomp_gen::fn_sub_478E80_00478e80, &recomp_gen::fn_sub_478E80_00478e80__recomp},
    {"sub_47A210", 0x47A210, &recomp_gen::fn_sub_47A210_0047a210, &recomp_gen::fn_sub_47A210_0047a210__recomp},
    {"sub_490050", 0x490050, &recomp_gen::fn_sub_490050_00490050, &recomp_gen::fn_sub_490050_00490050__recomp},
    {"sub_4908D0", 0x4908D0, &recomp_gen::fn_sub_4908D0_004908d0, &recomp_gen::fn_sub_4908D0_004908d0__recomp},
    {"sub_490980", 0x490980, &recomp_gen::fn_sub_490980_00490980, &recomp_gen::fn_sub_490980_00490980__recomp},
    {"sub_490D90", 0x490D90, &recomp_gen::fn_sub_490D90_00490d90, &recomp_gen::fn_sub_490D90_00490d90__recomp},
    {"sub_490DC0", 0x490DC0, &recomp_gen::fn_sub_490DC0_00490dc0, &recomp_gen::fn_sub_490DC0_00490dc0__recomp},
    {"sub_491880", 0x491880, &recomp_gen::fn_sub_491880_00491880, &recomp_gen::fn_sub_491880_00491880__recomp},
    {"sub_4919B0", 0x4919B0, &recomp_gen::fn_sub_4919B0_004919b0, &recomp_gen::fn_sub_4919B0_004919b0__recomp},
    {"sub_491B40", 0x491B40, &recomp_gen::fn_sub_491B40_00491b40, &recomp_gen::fn_sub_491B40_00491b40__recomp},
    {"sub_491CC0", 0x491CC0, &recomp_gen::fn_sub_491CC0_00491cc0, &recomp_gen::fn_sub_491CC0_00491cc0__recomp},
    {"sub_4920A0", 0x4920A0, &recomp_gen::fn_sub_4920A0_004920a0, &recomp_gen::fn_sub_4920A0_004920a0__recomp},
    {"sub_492D50", 0x492D50, &recomp_gen::fn_sub_492D50_00492d50, &recomp_gen::fn_sub_492D50_00492d50__recomp},
    {"sub_493710", 0x493710, &recomp_gen::fn_sub_493710_00493710, &recomp_gen::fn_sub_493710_00493710__recomp},
    {"sub_493B60", 0x493B60, &recomp_gen::fn_sub_493B60_00493b60, &recomp_gen::fn_sub_493B60_00493b60__recomp},
    {"sub_493CB0", 0x493CB0, &recomp_gen::fn_sub_493CB0_00493cb0, &recomp_gen::fn_sub_493CB0_00493cb0__recomp},
    {"sub_495260", 0x495260, &recomp_gen::fn_sub_495260_00495260, &recomp_gen::fn_sub_495260_00495260__recomp},
    {"sub_4954C0", 0x4954C0, &recomp_gen::fn_sub_4954C0_004954c0, &recomp_gen::fn_sub_4954C0_004954c0__recomp},
    {"sub_49A290", 0x49A290, &recomp_gen::fn_sub_49A290_0049a290, &recomp_gen::fn_sub_49A290_0049a290__recomp},
    {"sub_49A400", 0x49A400, &recomp_gen::fn_sub_49A400_0049a400, &recomp_gen::fn_sub_49A400_0049a400__recomp},
    {"sub_49B3F0", 0x49B3F0, &recomp_gen::fn_sub_49B3F0_0049b3f0, &recomp_gen::fn_sub_49B3F0_0049b3f0__recomp},
    {"sub_49E4F0", 0x49E4F0, &recomp_gen::fn_sub_49E4F0_0049e4f0, &recomp_gen::fn_sub_49E4F0_0049e4f0__recomp},
    {"sub_4A4D60", 0x4A4D60, &recomp_gen::fn_sub_4A4D60_004a4d60, &recomp_gen::fn_sub_4A4D60_004a4d60__recomp},
    {"sub_4A6630", 0x4A6630, &recomp_gen::fn_sub_4A6630_004a6630, &recomp_gen::fn_sub_4A6630_004a6630__recomp},
    {"sub_4AA550", 0x4AA550, &recomp_gen::fn_sub_4AA550_004aa550, &recomp_gen::fn_sub_4AA550_004aa550__recomp},
    {"sub_4AA5C0", 0x4AA5C0, &recomp_gen::fn_sub_4AA5C0_004aa5c0, &recomp_gen::fn_sub_4AA5C0_004aa5c0__recomp},
    {"sub_4AB200", 0x4AB200, &recomp_gen::fn_sub_4AB200_004ab200, &recomp_gen::fn_sub_4AB200_004ab200__recomp},
    {"sub_4AC570", 0x4AC570, &recomp_gen::fn_sub_4AC570_004ac570, &recomp_gen::fn_sub_4AC570_004ac570__recomp},
    {"sub_4AC5F0", 0x4AC5F0, &recomp_gen::fn_sub_4AC5F0_004ac5f0, &recomp_gen::fn_sub_4AC5F0_004ac5f0__recomp},
    {"sub_4AC870", 0x4AC870, &recomp_gen::fn_sub_4AC870_004ac870, &recomp_gen::fn_sub_4AC870_004ac870__recomp},
    {"sub_4AC920", 0x4AC920, &recomp_gen::fn_sub_4AC920_004ac920, &recomp_gen::fn_sub_4AC920_004ac920__recomp},
    {"sub_4ACB10", 0x4ACB10, &recomp_gen::fn_sub_4ACB10_004acb10, &recomp_gen::fn_sub_4ACB10_004acb10__recomp},
    {"sub_4ADBD0", 0x4ADBD0, &recomp_gen::fn_sub_4ADBD0_004adbd0, &recomp_gen::fn_sub_4ADBD0_004adbd0__recomp},
    {"sub_4ADE90", 0x4ADE90, &recomp_gen::fn_sub_4ADE90_004ade90, &recomp_gen::fn_sub_4ADE90_004ade90__recomp},
    {"sub_4AE3B0", 0x4AE3B0, &recomp_gen::fn_sub_4AE3B0_004ae3b0, &recomp_gen::fn_sub_4AE3B0_004ae3b0__recomp},
    {"sub_4AE5A0", 0x4AE5A0, &recomp_gen::fn_sub_4AE5A0_004ae5a0, &recomp_gen::fn_sub_4AE5A0_004ae5a0__recomp},
    {"sub_4AE790", 0x4AE790, &recomp_gen::fn_sub_4AE790_004ae790, &recomp_gen::fn_sub_4AE790_004ae790__recomp},
    {"sub_4AEBF0", 0x4AEBF0, &recomp_gen::fn_sub_4AEBF0_004aebf0, &recomp_gen::fn_sub_4AEBF0_004aebf0__recomp},
    {"sub_4AEEA0", 0x4AEEA0, &recomp_gen::fn_sub_4AEEA0_004aeea0, &recomp_gen::fn_sub_4AEEA0_004aeea0__recomp},
    {"sub_4AF130", 0x4AF130, &recomp_gen::fn_sub_4AF130_004af130, &recomp_gen::fn_sub_4AF130_004af130__recomp},
    {"sub_4AF210", 0x4AF210, &recomp_gen::fn_sub_4AF210_004af210, &recomp_gen::fn_sub_4AF210_004af210__recomp},
    {"sub_4AF340", 0x4AF340, &recomp_gen::fn_sub_4AF340_004af340, &recomp_gen::fn_sub_4AF340_004af340__recomp},
    {"sub_4AF760", 0x4AF760, &recomp_gen::fn_sub_4AF760_004af760, &recomp_gen::fn_sub_4AF760_004af760__recomp},
    {"sub_4AF940", 0x4AF940, &recomp_gen::fn_sub_4AF940_004af940, &recomp_gen::fn_sub_4AF940_004af940__recomp},
    {"sub_4AFFE0", 0x4AFFE0, &recomp_gen::fn_sub_4AFFE0_004affe0, &recomp_gen::fn_sub_4AFFE0_004affe0__recomp},
    {"sub_4B1290", 0x4B1290, &recomp_gen::fn_sub_4B1290_004b1290, &recomp_gen::fn_sub_4B1290_004b1290__recomp},
    {"sub_4B1620", 0x4B1620, &recomp_gen::fn_sub_4B1620_004b1620, &recomp_gen::fn_sub_4B1620_004b1620__recomp},
    {"sub_4B1BA0", 0x4B1BA0, &recomp_gen::fn_sub_4B1BA0_004b1ba0, &recomp_gen::fn_sub_4B1BA0_004b1ba0__recomp},
    {"sub_4B26A0", 0x4B26A0, &recomp_gen::fn_sub_4B26A0_004b26a0, &recomp_gen::fn_sub_4B26A0_004b26a0__recomp},
    {"sub_4B2810", 0x4B2810, &recomp_gen::fn_sub_4B2810_004b2810, &recomp_gen::fn_sub_4B2810_004b2810__recomp},
    {"sub_4B2AD0", 0x4B2AD0, &recomp_gen::fn_sub_4B2AD0_004b2ad0, &recomp_gen::fn_sub_4B2AD0_004b2ad0__recomp},
    {"sub_4B2BC0", 0x4B2BC0, &recomp_gen::fn_sub_4B2BC0_004b2bc0, &recomp_gen::fn_sub_4B2BC0_004b2bc0__recomp},
    {"sub_4B2E20", 0x4B2E20, &recomp_gen::fn_sub_4B2E20_004b2e20, &recomp_gen::fn_sub_4B2E20_004b2e20__recomp},
    {"sub_4B2F10", 0x4B2F10, &recomp_gen::fn_sub_4B2F10_004b2f10, &recomp_gen::fn_sub_4B2F10_004b2f10__recomp},
    {"sub_4B3160", 0x4B3160, &recomp_gen::fn_sub_4B3160_004b3160, &recomp_gen::fn_sub_4B3160_004b3160__recomp},
    {"sub_4B3440", 0x4B3440, &recomp_gen::fn_sub_4B3440_004b3440, &recomp_gen::fn_sub_4B3440_004b3440__recomp},
    {"sub_4B3730", 0x4B3730, &recomp_gen::fn_sub_4B3730_004b3730, &recomp_gen::fn_sub_4B3730_004b3730__recomp},
    {"sub_4B3900", 0x4B3900, &recomp_gen::fn_sub_4B3900_004b3900, &recomp_gen::fn_sub_4B3900_004b3900__recomp},
    {"sub_4B3AC0", 0x4B3AC0, &recomp_gen::fn_sub_4B3AC0_004b3ac0, &recomp_gen::fn_sub_4B3AC0_004b3ac0__recomp},
    {"sub_4B4230", 0x4B4230, &recomp_gen::fn_sub_4B4230_004b4230, &recomp_gen::fn_sub_4B4230_004b4230__recomp},
    {"sub_4B42E0", 0x4B42E0, &recomp_gen::fn_sub_4B42E0_004b42e0, &recomp_gen::fn_sub_4B42E0_004b42e0__recomp},
    {"sub_4B4410", 0x4B4410, &recomp_gen::fn_sub_4B4410_004b4410, &recomp_gen::fn_sub_4B4410_004b4410__recomp},
    {"sub_4B4790", 0x4B4790, &recomp_gen::fn_sub_4B4790_004b4790, &recomp_gen::fn_sub_4B4790_004b4790__recomp},
    {"sub_4B47D0", 0x4B47D0, &recomp_gen::fn_sub_4B47D0_004b47d0, &recomp_gen::fn_sub_4B47D0_004b47d0__recomp},
    {"sub_4B4860", 0x4B4860, &recomp_gen::fn_sub_4B4860_004b4860, &recomp_gen::fn_sub_4B4860_004b4860__recomp},
    {"sub_4B4CC0", 0x4B4CC0, &recomp_gen::fn_sub_4B4CC0_004b4cc0, &recomp_gen::fn_sub_4B4CC0_004b4cc0__recomp},
    {"sub_4B4D70", 0x4B4D70, &recomp_gen::fn_sub_4B4D70_004b4d70, &recomp_gen::fn_sub_4B4D70_004b4d70__recomp},
    {"sub_4B4EB0", 0x4B4EB0, &recomp_gen::fn_sub_4B4EB0_004b4eb0, &recomp_gen::fn_sub_4B4EB0_004b4eb0__recomp},
    {"sub_4B5D80", 0x4B5D80, &recomp_gen::fn_sub_4B5D80_004b5d80, &recomp_gen::fn_sub_4B5D80_004b5d80__recomp},
    {"sub_4B5EC0", 0x4B5EC0, &recomp_gen::fn_sub_4B5EC0_004b5ec0, &recomp_gen::fn_sub_4B5EC0_004b5ec0__recomp},
    {"sub_4B6040", 0x4B6040, &recomp_gen::fn_sub_4B6040_004b6040, &recomp_gen::fn_sub_4B6040_004b6040__recomp},
    {"sub_4B7630", 0x4B7630, &recomp_gen::fn_sub_4B7630_004b7630, &recomp_gen::fn_sub_4B7630_004b7630__recomp},
    {"sub_4B7690", 0x4B7690, &recomp_gen::fn_sub_4B7690_004b7690, &recomp_gen::fn_sub_4B7690_004b7690__recomp},
    {"RwFsInit", 0x4BFBB0, &recomp_gen::fn_RwFsInit_004bfbb0, &recomp_gen::fn_RwFsInit_004bfbb0__recomp},
    {"sub_4BFEA0", 0x4BFEA0, &recomp_gen::fn_sub_4BFEA0_004bfea0, &recomp_gen::fn_sub_4BFEA0_004bfea0__recomp},
    {"sub_4C00F0", 0x4C00F0, &recomp_gen::fn_sub_4C00F0_004c00f0, &recomp_gen::fn_sub_4C00F0_004c00f0__recomp},
    {"sub_4C06C0", 0x4C06C0, &recomp_gen::fn_sub_4C06C0_004c06c0, &recomp_gen::fn_sub_4C06C0_004c06c0__recomp},
    {"j_malloc", 0x4C4420, &recomp_gen::fn_j_malloc_004c4420, &recomp_gen::fn_j_malloc_004c4420__recomp},
    {"j_realloc", 0x4C4430, &recomp_gen::fn_j_realloc_004c4430, &recomp_gen::fn_j_realloc_004c4430__recomp},
    {"j_calloc", 0x4C4440, &recomp_gen::fn_j_calloc_004c4440, &recomp_gen::fn_j_calloc_004c4440__recomp},
    {"sub_4C4450", 0x4C4450, &recomp_gen::fn_sub_4C4450_004c4450, &recomp_gen::fn_sub_4C4450_004c4450__recomp},
    {"sub_4C4570", 0x4C4570, &recomp_gen::fn_sub_4C4570_004c4570, &recomp_gen::fn_sub_4C4570_004c4570__recomp},
    {"sub_4C6640", 0x4C6640, &recomp_gen::fn_sub_4C6640_004c6640, &recomp_gen::fn_sub_4C6640_004c6640__recomp},
    {"sub_4C6700", 0x4C6700, &recomp_gen::fn_sub_4C6700_004c6700, &recomp_gen::fn_sub_4C6700_004c6700__recomp},
    {"sub_4C67A0", 0x4C67A0, &recomp_gen::fn_sub_4C67A0_004c67a0, &recomp_gen::fn_sub_4C67A0_004c67a0__recomp},
    {"sub_4C6840", 0x4C6840, &recomp_gen::fn_sub_4C6840_004c6840, &recomp_gen::fn_sub_4C6840_004c6840__recomp},
    {"sub_4C68C0", 0x4C68C0, &recomp_gen::fn_sub_4C68C0_004c68c0, &recomp_gen::fn_sub_4C68C0_004c68c0__recomp},
    {"sub_4C6D00", 0x4C6D00, &recomp_gen::fn_sub_4C6D00_004c6d00, &recomp_gen::fn_sub_4C6D00_004c6d00__recomp},
    {"sub_4C7020", 0x4C7020, &recomp_gen::fn_sub_4C7020_004c7020, &recomp_gen::fn_sub_4C7020_004c7020__recomp},
    {"sub_4C70A0", 0x4C70A0, &recomp_gen::fn_sub_4C70A0_004c70a0, &recomp_gen::fn_sub_4C70A0_004c70a0__recomp},
    {"sub_4C71C0", 0x4C71C0, &recomp_gen::fn_sub_4C71C0_004c71c0, &recomp_gen::fn_sub_4C71C0_004c71c0__recomp},
    {"sub_4C7208", 0x4C7208, &recomp_gen::fn_sub_4C7208_004c7208, &recomp_gen::fn_sub_4C7208_004c7208__recomp},
    {"sub_4C7210", 0x4C7210, &recomp_gen::fn_sub_4C7210_004c7210, &recomp_gen::fn_sub_4C7210_004c7210__recomp},
    {"sub_4C7258", 0x4C7258, &recomp_gen::fn_sub_4C7258_004c7258, &recomp_gen::fn_sub_4C7258_004c7258__recomp},
    {"sub_4C7260", 0x4C7260, &recomp_gen::fn_sub_4C7260_004c7260, &recomp_gen::fn_sub_4C7260_004c7260__recomp},
    {"sub_4C72A0", 0x4C72A0, &recomp_gen::fn_sub_4C72A0_004c72a0, &recomp_gen::fn_sub_4C72A0_004c72a0__recomp},
    {"sub_4C7400", 0x4C7400, &recomp_gen::fn_sub_4C7400_004c7400, &recomp_gen::fn_sub_4C7400_004c7400__recomp},
    {"sub_4C7410", 0x4C7410, &recomp_gen::fn_sub_4C7410_004c7410, &recomp_gen::fn_sub_4C7410_004c7410__recomp},
    {"sub_4C7520", 0x4C7520, &recomp_gen::fn_sub_4C7520_004c7520, &recomp_gen::fn_sub_4C7520_004c7520__recomp},
    {"sub_4C78A0", 0x4C78A0, &recomp_gen::fn_sub_4C78A0_004c78a0, &recomp_gen::fn_sub_4C78A0_004c78a0__recomp},
    {"sub_4C79E0", 0x4C79E0, &recomp_gen::fn_sub_4C79E0_004c79e0, &recomp_gen::fn_sub_4C79E0_004c79e0__recomp},
    {"sub_4C7B60", 0x4C7B60, &recomp_gen::fn_sub_4C7B60_004c7b60, &recomp_gen::fn_sub_4C7B60_004c7b60__recomp},
    {"sub_4CA190", 0x4CA190, &recomp_gen::fn_sub_4CA190_004ca190, &recomp_gen::fn_sub_4CA190_004ca190__recomp},
    {"sub_4CAAC0", 0x4CAAC0, &recomp_gen::fn_sub_4CAAC0_004caac0, &recomp_gen::fn_sub_4CAAC0_004caac0__recomp},
    {"sub_4CBA20", 0x4CBA20, &recomp_gen::fn_sub_4CBA20_004cba20, &recomp_gen::fn_sub_4CBA20_004cba20__recomp},
    {"sub_4CC5C0", 0x4CC5C0, &recomp_gen::fn_sub_4CC5C0_004cc5c0, &recomp_gen::fn_sub_4CC5C0_004cc5c0__recomp},
    {"sub_4CC6D0", 0x4CC6D0, &recomp_gen::fn_sub_4CC6D0_004cc6d0, &recomp_gen::fn_sub_4CC6D0_004cc6d0__recomp},
    {"sub_4CCA60", 0x4CCA60, &recomp_gen::fn_sub_4CCA60_004cca60, &recomp_gen::fn_sub_4CCA60_004cca60__recomp},
    {"sub_4CCAC0", 0x4CCAC0, &recomp_gen::fn_sub_4CCAC0_004ccac0, &recomp_gen::fn_sub_4CCAC0_004ccac0__recomp},
    {"sub_4CCC30", 0x4CCC30, &recomp_gen::fn_sub_4CCC30_004ccc30, &recomp_gen::fn_sub_4CCC30_004ccc30__recomp},
    {"sub_4CCD20", 0x4CCD20, &recomp_gen::fn_sub_4CCD20_004ccd20, &recomp_gen::fn_sub_4CCD20_004ccd20__recomp},
    {"sub_4CCD50", 0x4CCD50, &recomp_gen::fn_sub_4CCD50_004ccd50, &recomp_gen::fn_sub_4CCD50_004ccd50__recomp},
    {"sub_4CCF10", 0x4CCF10, &recomp_gen::fn_sub_4CCF10_004ccf10, &recomp_gen::fn_sub_4CCF10_004ccf10__recomp},
    {"sub_4CD260", 0x4CD260, &recomp_gen::fn_sub_4CD260_004cd260, &recomp_gen::fn_sub_4CD260_004cd260__recomp},
    {"sub_4CD940", 0x4CD940, &recomp_gen::fn_sub_4CD940_004cd940, &recomp_gen::fn_sub_4CD940_004cd940__recomp},
    {"sub_4CDB50", 0x4CDB50, &recomp_gen::fn_sub_4CDB50_004cdb50, &recomp_gen::fn_sub_4CDB50_004cdb50__recomp},
    {"sub_4CEE30", 0x4CEE30, &recomp_gen::fn_sub_4CEE30_004cee30, &recomp_gen::fn_sub_4CEE30_004cee30__recomp},
    {"sub_4CF690", 0x4CF690, &recomp_gen::fn_sub_4CF690_004cf690, &recomp_gen::fn_sub_4CF690_004cf690__recomp},
    {"sub_4CF790", 0x4CF790, &recomp_gen::fn_sub_4CF790_004cf790, &recomp_gen::fn_sub_4CF790_004cf790__recomp},
    {"sub_4CF9B0", 0x4CF9B0, &recomp_gen::fn_sub_4CF9B0_004cf9b0, &recomp_gen::fn_sub_4CF9B0_004cf9b0__recomp},
    {"sub_4CFD30", 0x4CFD30, &recomp_gen::fn_sub_4CFD30_004cfd30, &recomp_gen::fn_sub_4CFD30_004cfd30__recomp},
    {"sub_4D05F0", 0x4D05F0, &recomp_gen::fn_sub_4D05F0_004d05f0, &recomp_gen::fn_sub_4D05F0_004d05f0__recomp},
    {"sub_4D0640", 0x4D0640, &recomp_gen::fn_sub_4D0640_004d0640, &recomp_gen::fn_sub_4D0640_004d0640__recomp},
    {"sub_4D0AC0", 0x4D0AC0, &recomp_gen::fn_sub_4D0AC0_004d0ac0, &recomp_gen::fn_sub_4D0AC0_004d0ac0__recomp},
    {"sub_4D11D0", 0x4D11D0, &recomp_gen::fn_sub_4D11D0_004d11d0, &recomp_gen::fn_sub_4D11D0_004d11d0__recomp},
    {"RpSkySelectDeepZBuffer", 0x4D82A0, &recomp_gen::fn_RpSkySelectDeepZBuffer_004d82a0, &recomp_gen::fn_RpSkySelectDeepZBuffer_004d82a0__recomp},
    {"sub_4D8300", 0x4D8300, &recomp_gen::fn_sub_4D8300_004d8300, &recomp_gen::fn_sub_4D8300_004d8300__recomp},
    {"sub_4D8310", 0x4D8310, &recomp_gen::fn_sub_4D8310_004d8310, &recomp_gen::fn_sub_4D8310_004d8310__recomp},
    {"sub_4D83C0", 0x4D83C0, &recomp_gen::fn_sub_4D83C0_004d83c0, &recomp_gen::fn_sub_4D83C0_004d83c0__recomp},
    {"sub_4D9520", 0x4D9520, &recomp_gen::fn_sub_4D9520_004d9520, &recomp_gen::fn_sub_4D9520_004d9520__recomp},
    {"sub_4D9BC0", 0x4D9BC0, &recomp_gen::fn_sub_4D9BC0_004d9bc0, &recomp_gen::fn_sub_4D9BC0_004d9bc0__recomp},
    {"sub_4DCEA0", 0x4DCEA0, &recomp_gen::fn_sub_4DCEA0_004dcea0, &recomp_gen::fn_sub_4DCEA0_004dcea0__recomp},
    {"sub_4DF0E0", 0x4DF0E0, &recomp_gen::fn_sub_4DF0E0_004df0e0, &recomp_gen::fn_sub_4DF0E0_004df0e0__recomp},
    {"sub_4DF3F0", 0x4DF3F0, &recomp_gen::fn_sub_4DF3F0_004df3f0, &recomp_gen::fn_sub_4DF3F0_004df3f0__recomp},
    {"sub_4DF9D0", 0x4DF9D0, &recomp_gen::fn_sub_4DF9D0_004df9d0, &recomp_gen::fn_sub_4DF9D0_004df9d0__recomp},
    {"sub_4DFCA0", 0x4DFCA0, &recomp_gen::fn_sub_4DFCA0_004dfca0, &recomp_gen::fn_sub_4DFCA0_004dfca0__recomp},
    {"sub_4DFCC0", 0x4DFCC0, &recomp_gen::fn_sub_4DFCC0_004dfcc0, &recomp_gen::fn_sub_4DFCC0_004dfcc0__recomp},
    {"sub_4E00E0", 0x4E00E0, &recomp_gen::fn_sub_4E00E0_004e00e0, &recomp_gen::fn_sub_4E00E0_004e00e0__recomp},
    {"SkySystem", 0x4E2B70, &recomp_gen::fn_SkySystem_004e2b70, &recomp_gen::fn_SkySystem_004e2b70__recomp},
    {"sceLibgcc32GetErxEntries_2", 0x4E2F00, &recomp_gen::fn_sceLibgcc32GetErxEntries_2_004e2f00, &recomp_gen::fn_sceLibgcc32GetErxEntries_2_004e2f00__recomp},
    {"sub_4E3090", 0x4E3090, &recomp_gen::fn_sub_4E3090_004e3090, &recomp_gen::fn_sub_4E3090_004e3090__recomp},
    {"sub_4E3550", 0x4E3550, &recomp_gen::fn_sub_4E3550_004e3550, &recomp_gen::fn_sub_4E3550_004e3550__recomp},
    {"sub_4E40B0", 0x4E40B0, &recomp_gen::fn_sub_4E40B0_004e40b0, &recomp_gen::fn_sub_4E40B0_004e40b0__recomp},
    {"sub_4E4130", 0x4E4130, &recomp_gen::fn_sub_4E4130_004e4130, &recomp_gen::fn_sub_4E4130_004e4130__recomp},
    {"sub_4E98A0", 0x4E98A0, &recomp_gen::fn_sub_4E98A0_004e98a0, &recomp_gen::fn_sub_4E98A0_004e98a0__recomp},
    {"sub_4EAC00", 0x4EAC00, &recomp_gen::fn_sub_4EAC00_004eac00, &recomp_gen::fn_sub_4EAC00_004eac00__recomp},
    {"sub_4EB8C0", 0x4EB8C0, &recomp_gen::fn_sub_4EB8C0_004eb8c0, &recomp_gen::fn_sub_4EB8C0_004eb8c0__recomp},
    {"sub_4EEC10", 0x4EEC10, &recomp_gen::fn_sub_4EEC10_004eec10, &recomp_gen::fn_sub_4EEC10_004eec10__recomp},
    {"sub_4EF1D0", 0x4EF1D0, &recomp_gen::fn_sub_4EF1D0_004ef1d0, &recomp_gen::fn_sub_4EF1D0_004ef1d0__recomp},
    {"sub_4EF9F0", 0x4EF9F0, &recomp_gen::fn_sub_4EF9F0_004ef9f0, &recomp_gen::fn_sub_4EF9F0_004ef9f0__recomp},
    {"sub_4F02E0", 0x4F02E0, &recomp_gen::fn_sub_4F02E0_004f02e0, &recomp_gen::fn_sub_4F02E0_004f02e0__recomp},
    {"sub_4F0AD0", 0x4F0AD0, &recomp_gen::fn_sub_4F0AD0_004f0ad0, &recomp_gen::fn_sub_4F0AD0_004f0ad0__recomp},
    {"sub_4F1E10", 0x4F1E10, &recomp_gen::fn_sub_4F1E10_004f1e10, &recomp_gen::fn_sub_4F1E10_004f1e10__recomp},
};

// The world of the random sweep: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 32;

// --- guest helpers ---------------------------------------------------------------------------------------------------
u32 ld(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
u16 ld16(Machine& m, u32 va) {
    u16 v;
    std::memcpy(&v, m.at(va), 2);
    return v;
}
u8 ld8(Machine& m, u32 va) { return *m.at(va); }
float ldf(Machine& m, u32 va) {
    float f;
    std::memcpy(&f, m.at(va), 4);
    return f;
}
void st(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void stf(Machine& m, u32 va, float f) { std::memcpy(m.at(va), &f, 4); }
void sts(Machine& m, u32 va, const char* s) { std::memcpy(m.at(va), s, std::strlen(s) + 1); }
std::string lds(Machine& m, u32 va) { return reinterpret_cast<const char*>(m.at(va)); }
u32 fbits(float f) {
    u32 b;
    std::memcpy(&b, &f, 4);
    return b;
}
float frand(std::mt19937& rng, float lo, float hi) {
    const u32 r = rng() % 100001;
    return lo + (hi - lo) * static_cast<float>(r) / 100000.0f;
}
bool in_ram(u32 va, u32 len = 4) { return va != 0 && va < EEMemory::kMainRamSize - len; }

bool has_case(const char* n) {
    for (const Case& c : kCases)
        if (std::strcmp(c.name, n) == 0) return true;
    return false;
}
const Case& by_name(const char* n) {
    for (const Case& c : kCases)
        if (std::strcmp(c.name, n) == 0) return c;
    std::fprintf(stderr, "render_rw9 test: no case %s\n", n);
    std::abort();
}

// The RW globals the bodies read.
constexpr u32 kEngine = 0x960070u;
constexpr u32 kGpClump = 0x7CE820u;      // the atomic free list (+0) and the clump free list (+4) at engine + this
constexpr u32 kGpImage = 0x7CE938u;      // the image module's block at engine + this (+12 gamma table, +268 inverse)
constexpr u32 kRegGeometry = 0x77DD20u;  // the geometry plugin registry (+0 the extended record size)
// Test data: free in the ELF's image and in every replay snapshot (below the stand-in heap 0x1C00000).
constexpr u32 kData = 0x01BC0000u;
constexpr u32 kDataSize = 0x00040000u;
// A function this build does not emit, served by a recorder (callbacks the bodies call through pointers).
constexpr u32 kCallback = 0x10A860u;

std::unique_ptr<Machine> snapshot_machine(const char* dir, std::vector<u8>& image) {
    auto m = std::make_unique<Machine>();
    if (m->load_elf(elf_path()) != nullptr) return nullptr;
    image = read_snapshot(dir);
    if (image.empty()) return nullptr;
    std::memcpy(m->mem.main_ram(), image.data(), image.size());
    write_rw_slots(*m);
    return m;
}
void restore(Machine& m, const std::vector<u8>& image) {
    std::memcpy(m.mem.main_ram(), image.data(), image.size());
    write_rw_slots(m);
    std::memset(m.at(kData), 0, kDataSize);
}

// The live entries of an RW free list (the used bits of each block, MSB first).
std::vector<u32> live_entries(Machine& m, u32 fl) {
    std::vector<u32> out;
    if (!in_ram(fl, 64)) return out;
    const u32 es = ld(m, fl), hs = ld(m, fl + 8), al = ld(m, fl + 12);
    if (al == 0 || hs > 64 || es == 0) return out;
    const u32 head = fl + 16;
    u32 b = ld(m, head);
    for (int nb = 0; b != head && in_ram(b) && nb < 256; ++nb, b = ld(m, b)) {
        const u32 base = (b + hs + al + 7) & ~(al - 1);
        for (u32 i = 0; i < hs; ++i) {
            const u8 bits = m.at(b + 8)[i];
            for (u32 k = 0; k < 8; ++k)
                if (bits & (0x80u >> k)) out.push_back(base + es * (8 * i + k));
        }
    }
    return out;
}
// A clump's atomics: its list head at +8, each atomic linked at +64.
std::vector<u32> clump_atomics(Machine& m, u32 clump) {
    std::vector<u32> out;
    const u32 head = clump + 8;
    for (u32 e = ld(m, head), n = 0; e != head && in_ram(e, 4) && n < 256; e = ld(m, e), ++n) out.push_back(e - 64);
    return out;
}
u32 frame_root(Machine& m, u32 frame) {
    for (int n = 0; n < 64 && in_ram(frame, 164); ++n) {
        const u32 parent = ld(m, frame + 4);
        if (!in_ram(parent, 164)) return frame;
        frame = parent;
    }
    return frame;
}

// --- the pair on stand-in worlds -------------------------------------------------------------------------------------
// hgp::pair with a fresh stand-in world around each body (the heap behind the RW memory slots and the free-list entry
// points, printf / sprintf, the H_Cdvd layer); afterwards both worlds' call logs, live heap blocks and bad frees must be
// equal. Float arguments go in through g_fpr (set after the harness's randomised registers). A sequence of calls can run
// as one body (both runs make the same calls in one stand-in world): each step sets $a0..$a3, $a0 = the previous call's
// $v0 when chained.
Fn g_body[2];
StandInWorld* g_world[2];
std::map<unsigned, float> g_fpr;
struct Step {
    const Case* c;
    Args a;
    bool chain = false;
};
std::vector<Step> g_seq;
std::vector<u32> g_seq_v0;  // each step's $v0 (the recompiled run's, written by the second run)
void thunk(int k, EEContext& ctx) {
    StandInsScope s(g_world[k]->si);
    for (const auto& [r, f] : g_fpr) ctx.fpr[r] = fbits(f);
    if (g_seq.empty()) {
        g_body[k](ctx);
        return;
    }
    g_seq_v0.clear();
    for (std::size_t i = 0; i < g_seq.size(); ++i) {
        const Step& st = g_seq[i];
        if (i > 0) {
            const u64 prev = ctx.gpr[GPR_V0].u64[0];
            for (int r = 0; r < 4; ++r) ctx.gpr[GPR_A0 + r].u64[0] = st.a[static_cast<std::size_t>(r)];
            if (st.chain) ctx.gpr[GPR_A0].u64[0] = prev;
        }
        (k == 0 ? st.c->hand : st.c->recomp)(ctx);
        g_seq_v0.push_back(static_cast<u32>(ctx.gpr[GPR_V0].u64[0]));
    }
}
void thunk_hand(EEContext& ctx) { thunk(0, ctx); }
void thunk_recomp(EEContext& ctx) { thunk(1, ctx); }

struct WPair {
    hgp::Run run;
    std::unique_ptr<StandInWorld> hand, recomp;
    u32 v0() const { return static_cast<u32>(run.end.gpr[GPR_V0].u64[0]); }
};

WPair wpair(Machine& m, const Case& c, const Args& args, u32 seed, const WorldSetup& setup, const HwCheck& hw = {}) {
    WPair p;
    p.hand = std::make_unique<StandInWorld>();
    p.recomp = std::make_unique<StandInWorld>();
    setup(*p.hand);
    setup(*p.recomp);
    g_body[0] = c.hand;
    g_body[1] = c.recomp;
    g_world[0] = p.hand.get();
    g_world[1] = p.recomp.get();
    p.run = hgp::pair(m, thunk_hand, thunk_recomp, args, seed, c.name, hw);
    expect_same_log(p.hand->si, p.recomp->si, c.name);
    CHECK(p.hand->heap.live() == p.recomp->heap.live());
    CHECK(p.hand->heap.bad_frees == p.recomp->heap.bad_frees);
    g_fpr.clear();
    return p;
}
WPair wp(Machine& m, const char* name, const Args& args, u32 seed, const WorldSetup& setup = install_standard, const HwCheck& hw = {}) {
    return wpair(m, by_name(name), args, seed, setup, hw);
}
WPair wseq(Machine& m, const std::vector<Step>& steps, u32 seed, const WorldSetup& setup = install_standard) {
    g_seq = steps;
    WPair p = wpair(m, *steps.front().c, steps.front().a, seed, setup);
    g_seq.clear();
    return p;
}
Step step(const char* name, const Args& a = {0, 0, 0, 0}, bool chain = false) { return Step{&by_name(name), a, chain}; }

// =====================================================================================================================
// RpGeometryCreate / RpGeometryDestroy
// =====================================================================================================================
// The record (render_rw9.h rw9::geometry): type 8, one reference, the counts, the texture-coordinate set count from the
// flags (bits 16..23, else 2 for 0x80, 1 for 0x04), the stored flags (0x7B kept, 0x04 / 0x80 from the set count, the
// native / extra bits 0x0F000000 kept), and -- unless native (0x01000000) -- the arrays laid out after the plugin-extended
// record (its size is the registry's first word): the pre-lit colours (flag 0x08), each UV set, the triangles, every
// triangle's material index -1; one morph target. 65536 vertices or more are refused.
TEST_CASE("game(render_rw9): RpGeometryCreate lays out the geometry; a destroy frees it all") {
    std::vector<u8> image;
    auto mp = snapshot_machine("b_5800", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot b_5800 not found");
        return;
    }
    Machine& m = *mp;
    std::mt19937 rng{0x47454F4Du};
    int made = 0, refused = 0, rounds = 0;
    const u32 flag_choices[] = {0x0u, 0x04u, 0x08u, 0x0Cu, 0x10u, 0x20u, 0x40u, 0x80u, 0x88u, 0x2Cu, 0x7Bu, 0x00030000u,
                                0x00050008u, 0x00080000u, 0x01000000u, 0x01000008u, 0x02000004u};
    for (int k = 0; k < 64; ++k) {
        restore(m, image);
        u32 nv = rng() % 300;
        const u32 nt = rng() % 400;
        const u32 pick = rng() % (sizeof flag_choices / sizeof flag_choices[0]);
        const u32 flags = flag_choices[pick];
        if (k % 16 == 15) nv = 0x10000u + rng() % 8;  // refused
        const WPair p = wp(m, "sub_493710", {nv, nt, flags, 0}, 610000u + static_cast<u32>(k));
        CHECK_FALSE(p.run.stopped);
        const u32 g = p.v0();
        if (nv >= 0x10000u) {
            CHECK(g == 0u);
            ++refused;
            continue;
        }
        REQUIRE(in_ram(g, 96));
        ++made;
        u32 sets = (flags >> 16) & 0xFFu;
        if (sets == 0) sets = (flags & 0x80u) ? 2u : (flags & 0x04u) ? 1u : 0u;
        const u32 setbits = sets == 1 ? 4u : sets >= 2 ? 0x80u : 0u;
        CHECK(ld8(m, g) == 8u);
        CHECK(ld16(m, g + 14) == 1u);
        CHECK(ld(m, g + 16) == nt);
        CHECK(ld(m, g + 20) == nv);
        CHECK(ld(m, g + 24) == 1u);  // one morph target
        CHECK(ld(m, g + 28) == sets);
        CHECK(ld(m, g + 8) == ((flags & 0x7Bu) | setbits | (flags & 0x0F000000u)));
        if (flags & 0x01000000u) {
            CHECK(ld(m, g + 44) == 0u);
            CHECK(ld(m, g + 48) == 0u);
            continue;
        }
        u32 at = g + ld(m, kRegGeometry);
        if ((flags & 0x08u) && nv) {
            CHECK(ld(m, g + 48) == at);
            at += 4 * nv;
        } else {
            CHECK(ld(m, g + 48) == 0u);
        }
        for (u32 s = 0; s < sets && nv; ++s) {
            CHECK(ld(m, g + 52 + 4 * s) == at);
            at += 8 * nv;
        }
        if (nt) {
            CHECK(ld(m, g + 44) == at);
            for (u32 t = 0; t < nt; ++t) CHECK(ld16(m, at + 8 * t + 6) == 0xFFFFu);
        } else {
            CHECK(ld(m, g + 44) == 0u);
        }
    }
    // create then destroy in one stand-in world: every block the create took is freed again
    for (int k = 0; k < 16; ++k) {
        restore(m, image);
        const u32 nv = 1 + rng() % 120;
        const u32 nt = rng() % 200;
        const u32 pick = rng() % (sizeof flag_choices / sizeof flag_choices[0]);
        const u32 flags = flag_choices[pick];
        const WPair p = wseq(m, {step("sub_493710", {nv, nt, flags, 0}), step("sub_493B60", {0, 0, 0, 0}, true)}, 611000u + static_cast<u32>(k));
        CHECK_FALSE(p.run.stopped);
        CHECK(p.v0() == 1u);
        CHECK(p.recomp->heap.live().empty());
        ++rounds;
    }
    MESSAGE("RpGeometryCreate: " << made << " geometries checked, " << refused << " refusals, " << rounds << " create / destroy rounds");
}

// =====================================================================================================================
// RpAtomicCreate, RpAtomicClone, RpClumpClone on the live objects
// =====================================================================================================================
// The new atomic: type 1, flags 5 (collision test | render), private flags 1, no frame / geometry / clump, the default
// render callback 0x490860, the interpolator flags 3 with times 1.0, the world-sector list empty (pointing at itself).
TEST_CASE("game(render_rw9): RpAtomicCreate's defaults; RpAtomicClone and RpClumpClone of every live atomic and clump") {
    int atoms = 0, clumps = 0, snaps = 0;
    for (const char* sn : {"dorm_replay_4900", "b_5800", "climb_ref_17000"}) {
        std::vector<u8> image;
        auto mp = snapshot_machine(sn, image);
        if (!mp) {
            MESSAGE("SKIP: snapshot " << sn << " not found");
            continue;
        }
        ++snaps;
        Machine& m = *mp;
        restore(m, image);
        {
            const WPair p = wp(m, "sub_491880", {0, 0, 0, 0}, 620000u + static_cast<u32>(snaps));
            CHECK_FALSE(p.run.stopped);
            const u32 a = p.v0();
            REQUIRE(in_ram(a, 112));
            CHECK(ld8(m, a) == 1u);
            CHECK(ld8(m, a + 2) == 5u);
            CHECK(ld8(m, a + 3) == 1u);
            CHECK(ld(m, a + 4) == 0u);
            CHECK(ld(m, a + 24) == 0u);
            CHECK(ld(m, a + 60) == 0u);
            CHECK(ld(m, a + 72) == 0x490860u);
            CHECK(ld(m, a + 76) == 3u);
            CHECK(ld(m, a + 84) == 0x3F800000u);
            CHECK(ld(m, a + 88) == 0x3F800000u);
            CHECK(ld(m, a + 100) == a + 100);
            CHECK(ld(m, a + 104) == a + 100);
        }
        const std::vector<u32> atomics = live_entries(m, ld(m, kEngine + ld(m, kGpClump)));
        const std::vector<u32> clist = live_entries(m, ld(m, kEngine + ld(m, kGpClump) + 4));
        // RpAtomicClone: the clone shares the geometry (one more reference), the flags, the sphere, the callbacks
        int n = 0;
        for (u32 a : atomics) {
            if (n >= 24) break;
            const u32 g = ld(m, a + 24);
            if (!in_ram(g, 96)) continue;
            restore(m, image);
            const u16 refs = ld16(m, g + 14);
            const WPair p = wp(m, "sub_491B40", {a, 0, 0, 0}, 621000u + static_cast<u32>(atoms));
            CHECK_FALSE(p.run.stopped);
            const u32 c = p.v0();
            REQUIRE(in_ram(c, 112));
            CHECK(ld(m, c + 24) == g);
            CHECK(ld16(m, g + 14) == static_cast<u16>(refs + 1));
            CHECK(ld8(m, c + 2) == ld8(m, a + 2));
            CHECK(ld(m, c + 72) == ld(m, a + 72));
            CHECK(ld(m, c + 108) == ld(m, a + 108));
            for (u32 o = 28; o <= 40; o += 4) CHECK(ld(m, c + o) == ld(m, a + o));
            CHECK(ld(m, c + 4) == 0u);  // no frame: the clone is not attached
            ++atoms;
            ++n;
        }
        // RpClumpClone: as many atomics, each sharing its original's geometry, on a cloned frame hierarchy
        n = 0;
        for (u32 cl : clist) {
            if (n >= 12) break;
            const std::vector<u32> orig = clump_atomics(m, cl);
            if (!in_ram(ld(m, cl + 4), 164)) continue;
            restore(m, image);
            std::map<u32, int> uses;
            std::map<u32, u16> refs;
            for (u32 a : orig) {
                const u32 g = ld(m, a + 24);
                if (in_ram(g, 96)) {
                    ++uses[g];
                    refs[g] = ld16(m, g + 14);
                }
            }
            const WPair p = wp(m, "sub_491CC0", {cl, 0, 0, 0}, 622000u + static_cast<u32>(clumps));
            CHECK_FALSE(p.run.stopped);
            const u32 c = p.v0();
            if (c == 0) continue;
            REQUIRE(in_ram(c, 48));
            const std::vector<u32> cloned = clump_atomics(m, c);
            CHECK(cloned.size() == orig.size());
            CHECK(ld(m, c + 4) != ld(m, cl + 4));
            for (const auto& [g, k] : uses) CHECK(ld16(m, g + 14) == static_cast<u16>(refs[g] + k));
            for (u32 a : cloned) {
                CHECK(ld(m, a + 60) == c);
                if (in_ram(ld(m, a + 4), 164)) CHECK(frame_root(m, ld(m, a + 4)) == frame_root(m, ld(m, c + 4)));
            }
            ++clumps;
            ++n;
        }
    }
    if (snaps) MESSAGE("RpAtomicClone: " << atoms << " live atomics, RpClumpClone: " << clumps << " live clumps on " << snaps << " snapshots");
}

// =====================================================================================================================
// The image module: gamma tables, gamma correction, palette expansion
// =====================================================================================================================
TEST_CASE("game(render_rw9): the image gamma tables, gamma correction and palette expansion against the host") {
    std::vector<u8> image;
    auto mp = snapshot_machine("dorm_replay_4900", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot dorm_replay_4900 not found");
        return;
    }
    Machine& m = *mp;
    std::mt19937 rng{0x47414D41u};
    int tables = 0, images = 0, copies = 0;
    // RwImageSetGamma: +12[i] = 255 * (i / 255)^(1/g) + 0.5, +268[i] = 255 * (i / 255)^g + 0.5, entry 0 = 0
    for (float g : {1.0f, 0.5f, 0.8f, 1.2f, 1.6f, 2.2f, 3.0f}) {
        restore(m, image);
        g_fpr[12] = g;
        const WPair p = wp(m, "sub_4CDB50", {0, 0, 0, 0}, 630000u + static_cast<u32>(tables));
        CHECK_FALSE(p.run.stopped);
        CHECK(p.v0() == 1u);
        const u32 mod = kEngine + ld(m, kGpImage);
        CHECK(ldf(m, mod + 524) == g);
        CHECK(ld8(m, mod + 12) == 0u);
        CHECK(ld8(m, mod + 268) == 0u);
        int off = 0;
        for (int i = 1; i < 256; ++i) {
            const int e1 = static_cast<int>(255.0f * std::pow(static_cast<float>(i) / 255.0f, 1.0f / g) + 0.5f);
            const int e2 = static_cast<int>(255.0f * std::pow(static_cast<float>(i) / 255.0f, g) + 0.5f);
            off += std::abs(static_cast<int>(ld8(m, mod + 12 + i)) - e1) > 1 ? 1 : 0;
            off += std::abs(static_cast<int>(ld8(m, mod + 268 + i)) - e2) > 1 ? 1 : 0;
        }
        CHECK(off == 0);
        ++tables;
    }
    // RwImageGammaCorrect: 32-bit pixels through +12 (alpha kept), a 4 / 8-bit image's palette likewise
    for (int k = 0; k < 24; ++k) {
        restore(m, image);
        const u32 mod = kEngine + ld(m, kGpImage);
        const u32 img = kData + 0x100, pix = kData + 0x1000, pal = kData + 0x8000;
        const u32 depth = k % 3 == 0 ? 8u : k % 3 == 1 ? 4u : 32u;
        const u32 w = 1 + rng() % 24, h = 1 + rng() % 12;
        st(m, img + 0, 0);
        st(m, img + 4, w);
        st(m, img + 8, h);
        st(m, img + 12, depth);
        st(m, img + 16, depth == 32 ? 4 * w : w);
        st(m, img + 20, pix);
        st(m, img + 24, depth == 32 ? 0u : pal);
        for (u32 i = 0; i < 0x2000; ++i) {
            const u8 b = static_cast<u8>(rng());
            m.at(pix)[i] = b;
        }
        for (u32 i = 0; i < 1024; ++i) {
            const u8 b = static_cast<u8>(rng());
            m.at(pal)[i] = b;
        }
        const std::vector<u8> before(m.at(kData), m.at(kData) + 0x9000);
        const WPair p = wp(m, "sub_4CD940", {img, 0, 0, 0}, 631000u + static_cast<u32>(k));
        CHECK_FALSE(p.run.stopped);
        CHECK(p.v0() == img);
        const u8* gt = m.at(mod + 12);
        if (depth == 32) {
            for (u32 y = 0; y < h; ++y)
                for (u32 x = 0; x < w; ++x) {
                    const u32 o = pix - kData + y * 4 * w + 4 * x;
                    for (u32 c = 0; c < 3; ++c) CHECK(m.at(kData)[o + c] == gt[before[o + c]]);
                    CHECK(m.at(kData)[o + 3] == before[o + 3]);
                }
        } else {
            for (u32 i = 0; i < (1u << depth); ++i) {
                const u32 o = pal - kData + 4 * i;
                for (u32 c = 0; c < 3; ++c) CHECK(m.at(kData)[o + c] == gt[before[o + c]]);
                CHECK(m.at(kData)[o + 3] == before[o + 3]);
            }
            CHECK((ld(m, img) & 2u) == 2u);
        }
        ++images;
    }
    // rwImageCopyPixels: an 8-bit image into a 32-bit one of the same size expands through the palette
    for (int k = 0; k < 16; ++k) {
        restore(m, image);
        const u32 dst = kData + 0x100, src = kData + 0x200, dpix = kData + 0x1000, spix = kData + 0x6000, pal = kData + 0x8000;
        const u32 w = 1 + rng() % 30, h = 1 + rng() % 10;
        st(m, dst + 4, w), st(m, dst + 8, h), st(m, dst + 12, 32), st(m, dst + 16, 4 * w), st(m, dst + 20, dpix), st(m, dst + 24, 0);
        st(m, src + 4, w), st(m, src + 8, h), st(m, src + 12, 8), st(m, src + 16, w), st(m, src + 20, spix), st(m, src + 24, pal);
        for (u32 i = 0; i < w * h; ++i) {
            const u8 b = static_cast<u8>(rng());
            m.at(spix)[i] = b;
        }
        for (u32 i = 0; i < 1024; ++i) {
            const u8 b = static_cast<u8>(rng());
            m.at(pal)[i] = b;
        }
        const WPair p = wp(m, "sub_4CD260", {dst, src, 0, 0}, 632000u + static_cast<u32>(k));
        CHECK_FALSE(p.run.stopped);
        CHECK(p.v0() == 1u);
        for (u32 y = 0; y < h; ++y)
            for (u32 x = 0; x < w; ++x) CHECK(ld(m, dpix + 4 * (y * w + x)) == ld(m, pal + 4 * m.at(spix)[y * w + x]));
        ++copies;
    }
    MESSAGE("image module: " << tables << " gamma tables, " << images << " gamma-corrected images, " << copies << " palette copies");
}

// =====================================================================================================================
// The sky driver: the GS CLUT layout and colour packing, the raster format rules
// =====================================================================================================================
// skyRasterWritePalette: a 256-entry palette is stored swizzled (entry i at (i & 0xE7) | table[(i >> 3) & 3], the table
// 0x7BCF60 swapping the middle 8-entry groups of each 32), a 16-entry one in order; 32-bit CLUT entries keep RGB and
// halve the alpha (0x80 = opaque on the GS: (a * 0x808081) & 0xFF000000), 16-bit ones are 1555.
TEST_CASE("game(render_rw9): the sky driver's CLUT layout and colour packing; its raster format rules") {
    std::vector<u8> image;
    auto mp = snapshot_machine("dorm_replay_4900", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot dorm_replay_4900 not found");
        return;
    }
    Machine& m = *mp;
    std::mt19937 rng{0x434C5554u};
    int palettes = 0, formats = 0;
    const u32 swz[4] = {ld(m, 0x7BCF60u), ld(m, 0x7BCF64u), ld(m, 0x7BCF68u), ld(m, 0x7BCF6Cu)};
    for (int k = 0; k < 32; ++k) {
        restore(m, image);
        const u32 ras = kData + 0x100, pal = kData + 0x1000, src = kData + 0x3000;
        const u8 fmts[4] = {0x25, 0x20, 0x45, 0x40};  // 8-bit 32 / 16-bit CLUT, 4-bit 32 / 16-bit CLUT
        const u8 fmt = fmts[k % 4];
        std::memset(m.at(ras), 0, 64);
        st(m, ras + 8, pal);
        m.at(ras)[35] = fmt;
        for (u32 i = 0; i < 1024; ++i) {
            const u8 b = static_cast<u8>(rng());
            m.at(src)[i] = b;
        }
        const WPair p = wp(m, "sub_4EAC00", {ras, src, 0, 0}, 640000u + static_cast<u32>(k));
        CHECK_FALSE(p.run.stopped);
        const bool big = (fmt & 0x60) == 0x20;
        const bool c32 = (fmt & 0x0F) == 5;
        const u32 n = big ? 256u : 16u;
        for (u32 i = 0; i < n; ++i) {
            const u32 j = big ? ((i & 0xE7u) | swz[(i >> 3) & 3]) : i;
            const u8* s = m.at(src + 4 * j);
            if (c32) {
                const u32 want = s[0] | (s[1] << 8) | (s[2] << 16) | ((s[3] * 0x808081u) & 0xFF000000u);
                CHECK(ld(m, pal + 4 * i) == want);
            } else {
                const u32 want = ((s[3] << 8) & 0x8000u) | (s[0] >> 3) | ((s[2] << 7) & 0x7C00u) | ((s[1] << 2) & 0x3E0u);
                CHECK(ld16(m, pal + 2 * i) == want);
            }
        }
        ++palettes;
    }
    // skyRasterValidateFormat: a texture raster without format bits gets them from its depth
    struct F {
        u32 depth, flags;
        u8 want;
    };
    const F cases[] = {{16, 0x04, 0x01}, {32, 0x04, 0x05}, {24, 0x04, 0x06}, {8, 0x04, 0x21}, {4, 0x04, 0x41}};
    for (const F& f : cases) {
        restore(m, image);
        const u32 ras = kData + 0x100;
        std::memset(m.at(ras), 0, 64);
        st(m, ras + 20, f.depth);
        const WPair p = wp(m, "sub_4D9520", {0, ras, f.flags, 0}, 641000u + static_cast<u32>(formats));
        CHECK_FALSE(p.run.stopped);
        CHECK(p.v0() == 1u);
        CHECK(ld8(m, ras + 35) == f.want);
        CHECK(ld8(m, ras + 32) == (f.flags & 7u));
        ++formats;
    }
    MESSAGE("sky driver: " << palettes << " palettes, " << formats << " format rules");
}

// =====================================================================================================================
// RW strings and the vector transforms
// =====================================================================================================================
// (On a snapshot: the string chunk size calls strlen through the RW string function table 0x960164, which the engine
// fills at start-up -- the ELF image leaves it 0.)
TEST_CASE("game(render_rw9): the RW string helpers and the default vector transforms against the host") {
    std::vector<u8> image;
    auto mp = snapshot_machine("dorm_replay_4900", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot dorm_replay_4900 not found");
        return;
    }
    Machine& m = *mp;
    std::mt19937 rng{0x53545253u};
    int strings = 0, vectors = 0;
    const char* samples[] = {"", "a", "Hello, World!", "texture/PC_HAIR01.TXD", "MiXeD_Case-123", "c:\\data\\x.bmp",
                             "pak:model/item.rmd", "\\abs", "zZ", "no colon here"};
    for (const char* s : samples) {
        for (int k = 0; k < 2; ++k) {
            const u32 at = kData + 0x100;
            sts(m, at, s);
            std::string up(s), lo(s);
            for (char& c : up) c = static_cast<char>(c >= 'a' && c <= 'z' ? c - 32 : c);
            for (char& c : lo) c = static_cast<char>(c >= 'A' && c <= 'Z' ? c + 32 : c);
            {
                const WPair p = wp(m, "sub_4C71C0", {at, 0, 0, 0}, 650000u + static_cast<u32>(strings));
                CHECK(lds(m, at) == up);
                CHECK(p.v0() == at);
            }
            sts(m, at, s);
            {
                const WPair p = wp(m, "sub_4C7210", {at, 0, 0, 0}, 651000u + static_cast<u32>(strings));
                CHECK(lds(m, at) == lo);
                CHECK(p.v0() == at);
            }
            sts(m, at, s);
            const char ch = k == 0 ? 'a' : ':';
            {
                const WPair p = wp(m, "sub_4C7260", {at, static_cast<u32>(ch), 0, 0}, 652000u + static_cast<u32>(strings));
                const char* h = std::strchr(s, ch);
                CHECK(p.v0() == (h && *s ? at + static_cast<u32>(h - s) : 0u));
            }
            {
                const WPair p = wp(m, "sub_4C72A0", {at, static_cast<u32>(ch), 0, 0}, 653000u + static_cast<u32>(strings));
                const char* h = std::strrchr(s, ch);
                CHECK(p.v0() == (h && *s ? at + static_cast<u32>(h - s) : 0u));
            }
            {
                const WPair p = wp(m, "sub_4C7410", {at, 0, 0, 0}, 654000u + static_cast<u32>(strings));
                CHECK(p.v0() == ((static_cast<u32>(std::strlen(s)) + 4u) & ~3u));
            }
            ++strings;
        }
    }
    // the default transforms: points = rotation + translation, vectors = rotation only (row vectors, RW's layout:
    // right +0, up +16, at +32, pos +48)
    for (int k = 0; k < 24; ++k) {
        const u32 mat = kData + 0x100, src = kData + 0x200, dst = kData + 0x400;
        float M[16];
        for (float& f : M) f = frand(rng, -4.0f, 4.0f);
        for (int i = 0; i < 16; ++i) stf(m, mat + 4 * static_cast<u32>(i), M[i]);
        const u32 n = 1 + rng() % 8;
        std::vector<float> v(3 * n);
        for (float& f : v) f = frand(rng, -10.0f, 10.0f);
        for (u32 i = 0; i < 3 * n; ++i) stf(m, src + 4 * i, v[i]);
        const bool points = k % 2 == 0;
        const WPair p = wp(m, points ? "sub_4C6640" : "sub_4C67A0", {dst, src, n, mat}, 655000u + static_cast<u32>(k));
        CHECK(p.v0() == dst);
        for (u32 i = 0; i < n; ++i)
            for (u32 c = 0; c < 3; ++c) {
                float want = v[3 * i] * M[c] + v[3 * i + 1] * M[4 + c] + v[3 * i + 2] * M[8 + c];
                if (points) want += M[12 + c];
                const float got = ldf(m, dst + 4 * (3 * i + c));
                CHECK(std::fabs(got - want) <= 1e-3f * (1.0f + std::fabs(want)));
            }
        ++vectors;
    }
    MESSAGE("strings: " << strings << " samples, transforms: " << vectors << " batches");
}

// =====================================================================================================================
// Built inputs for the pointer-following walks; SkySystem's requests
// =====================================================================================================================
// frameSetRoot on built frame trees (child +152, sibling +156): every frame of the tree gets the root at +160.
// rt2dPathMakeSList on built chains of paths (node array +0 / count +4, next +20): every path of the chain is turned
// into its sList form (+4 = -1) with the nodes copied. SkySystem's queries: 1 / 8 / 9 nothing, 5 the mode count 90,
// 10 the current mode, 19 1024, 22 the halfword 6, 6 a video mode's record, an unknown request 0.
TEST_CASE("game(render_rw9): the frame-root and path walks on built inputs; SkySystem's queries") {
    std::vector<u8> image;
    auto mp = snapshot_machine("dorm_replay_4900", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot dorm_replay_4900 not found");
        return;
    }
    Machine& m = *mp;
    std::mt19937 rng{0x46524D45u};
    int trees = 0, chains = 0, queries = 0;
    for (int k = 0; k < 24 && has_case("sub_4CAAC0"); ++k) {
        restore(m, image);
        const u32 n = 1 + rng() % 40;
        std::vector<u32> fr(n);
        for (u32 i = 0; i < n; ++i) {
            fr[i] = kData + 0x100 + 192 * i;
            std::memset(m.at(fr[i]), 0, 192);
        }
        for (u32 i = 1; i < n; ++i) {  // attach i under a random earlier frame, at the head of its child list
            const u32 parent = fr[rng() % i];
            st(m, fr[i] + 156, ld(m, parent + 152));
            st(m, parent + 152, fr[i]);
            st(m, fr[i] + 4, parent);
        }
        const u32 root = kData + 0x20000;
        const WPair p = wp(m, "sub_4CAAC0", {fr[0], root, 0, 0}, 660000u + static_cast<u32>(k));
        CHECK_FALSE(p.run.stopped);
        for (u32 f : fr) CHECK(ld(m, f + 160) == root);
        ++trees;
    }
    for (int k = 0; k < 24 && has_case("sub_4AC5F0"); ++k) {
        restore(m, image);
        const u32 n = 1 + rng() % 5;
        std::vector<u32> path(n), counts(n);
        for (u32 i = 0; i < n; ++i) path[i] = kData + 0x100 + 32 * i;
        auto setup = [&m, &path, &counts, n](StandInWorld& w) {
            install_standard(w);
            for (u32 i = 0; i < n; ++i) {
                std::memset(m.at(path[i]), 0, 28);
                counts[i] = i == 0 ? 1u + i : (i * 3) % 5;
                const u32 nodes = w.heap.alloc(24 * (counts[i] + 1));
                for (u32 b = 0; b < 24 * counts[i]; b += 4) st(m, nodes + b, 0x1000u * (i + 1) + b);
                st(m, path[i], nodes);
                st(m, path[i] + 4, counts[i]);
                st(m, path[i] + 20, i + 1 < n ? path[i + 1] : 0);
            }
        };
        const WPair p = wp(m, "sub_4AC5F0", {path[0], 0, 0, 0}, 661000u + static_cast<u32>(k), setup);
        CHECK_FALSE(p.run.stopped);
        CHECK(p.v0() == path[0]);
        for (u32 i = 0; i < n; ++i) CHECK(ld(m, path[i] + 4) == 0xFFFFFFFFu);
        ++chains;
    }
    if (has_case("SkySystem")) {
        struct Q {
            u32 req, a3;
            u32 v0;
        };
        const Q qs[] = {{1, 0, 1}, {8, 0, 1}, {9, 0, 1}, {5, 0, 1}, {10, 0, 1}, {19, 0, 1}, {22, 0, 1}, {6, 3, 1}, {6, 90, 0},
                        {30, 0, 0}};
        for (const Q& q : qs) {
            restore(m, image);
            const u32 out = kData + 0x100;
            std::memset(m.at(out), 0xEE, 64);
            const WPair p = wp(m, "SkySystem", {q.req, out, 0, q.a3}, 662000u + static_cast<u32>(queries));
            CHECK_FALSE(p.run.stopped);
            CHECK(p.v0() == q.v0);
            if (q.req == 5) CHECK(ld(m, out) == 90u);
            if (q.req == 19) CHECK(ld(m, out) == 1024u);
            if (q.req == 22) CHECK(ld16(m, out) == 6u);
            if (q.req == 6 && q.v0) CHECK(ld(m, out) == ld(m, 0x77E710u + 24 * q.a3));
            ++queries;
        }
    }
    MESSAGE("walks: " << trees << " frame trees, " << chains << " path chains; SkySystem: " << queries << " queries");
}

// =====================================================================================================================
// Rt2d on built objects: the destroy dispatch, a scene's destroy, the path moveto, a path body read without nodes
// =====================================================================================================================
// rt2dObjectDestroyByType: an unknown type returns 0 and touches nothing; a shape (type 2) releases its representation
// (one reference less) and, without an atomic or colour array, returns 1. Rt2dSceneDestroy walks the 272-byte children
// of its child sList until one fails (an unknown type), destroys the sList and returns the scene to its free list.
// Rt2dPathMoveto on a fresh path (rt2dPathCreate, the path free list of the snapshot): the first call appends a moveto
// node; the second, the path having a node, chains a new sub-path, makes it current and appends there. rt2dPathStreamRead-
// Body with a header of 0 nodes: count 0, the closed / flat flags and the inset from the header, the path its own current.
TEST_CASE("game(render_rw9): Rt2d objects, scenes and paths on built inputs") {
    std::vector<u8> image;
    auto mp = snapshot_machine("dorm_replay_4900", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot dorm_replay_4900 not found");
        return;
    }
    Machine& m = *mp;
    std::mt19937 rng{0x52543244u};
    int objs = 0, scenes = 0, paths = 0, bodies = 0;
    for (int k = 0; k < 16 && has_case("sub_4ADBD0"); ++k) {
        restore(m, image);
        const u32 obj = kData + 0x100, rep = kData + 0x400;
        std::memset(m.at(obj), 0, 272);
        std::memset(m.at(rep), 0, 16);
        const u32 kinds[4] = {0, 5, 6, 2};
        const u32 type = kinds[k % 4];
        st(m, obj, type);
        st(m, rep + 4, 2 + rng() % 5);
        st(m, obj + 176, rep);
        const u32 refs = ld(m, rep + 4);
        const WPair p = wp(m, "sub_4ADBD0", {obj, 0, 0, 0}, 670000u + static_cast<u32>(k));
        CHECK_FALSE(p.run.stopped);
        CHECK(p.v0() == (type == 2 ? 1u : 0u));
        CHECK(ld(m, rep + 4) == (type == 2 ? refs - 1 : refs));
        ++objs;
    }
    for (int k = 0; k < 12 && has_case("sub_4AE5A0"); ++k) {
        restore(m, image);
        const u32 n = rng() % 4;
        const u32 bad = rng() % (n + 1);  // the first child of an unknown type (n: none)
        auto setup = [&m, n, bad](StandInWorld& w) {
            install_standard(w);
            const u32 scene = w.heap.alloc(272), list = w.heap.alloc(16), kids = w.heap.alloc(272 * (n + 1)), rep = w.heap.alloc(16);
            std::memset(m.at(scene), 0, 272);
            std::memset(m.at(kids), 0, 272 * (n + 1));
            std::memset(m.at(rep), 0, 16);
            st(m, rep + 4, 100);
            st(m, list, kids), st(m, list + 4, n), st(m, list + 8, 272), st(m, list + 12, n + 1);
            for (u32 i = 0; i < n; ++i) {
                st(m, kids + 272 * i, i == bad ? 9u : 2u);
                st(m, kids + 272 * i + 176, rep);
            }
            st(m, scene, 1);
            st(m, scene + 176, list);
            st(m, scene + 180, n);
            st(m, kData + 0x10, scene);
            st(m, kData + 0x14, rep);
        };
        StandInWorld probe;
        setup(probe);
        const u32 scene = ld(m, kData + 0x10), rep = ld(m, kData + 0x14);
        const WPair p = wp(m, "sub_4AE5A0", {scene, 0, 0, 0}, 671000u + static_cast<u32>(k), setup);
        CHECK_FALSE(p.run.stopped);
        CHECK(p.v0() == (bad >= n ? 1u : 0u));
        CHECK(ld(m, rep + 4) == 100u - std::min(bad, n));  // each shape before the failing child released its reference
        ++scenes;
    }
    for (int k = 0; k < 8 && has_case("sub_4AB200") && has_case("sub_4AC570"); ++k) {
        restore(m, image);
        g_fpr[12] = frand(rng, -50.0f, 50.0f);
        g_fpr[13] = frand(rng, -50.0f, 50.0f);
        const WPair p = wseq(m, {step("sub_4AC570"), step("sub_4AB200", {0, 0, 0, 0}, true), step("sub_4AB200", {0, 0, 0, 0}, true)},
                             672000u + static_cast<u32>(k));
        CHECK_FALSE(p.run.stopped);
        REQUIRE(g_seq_v0.size() == 3);
        const u32 path = g_seq_v0[0];
        REQUIRE(in_ram(path, 28));
        CHECK(g_seq_v0[1] == path);
        CHECK(g_seq_v0[2] == path);
        const u32 sub = ld(m, path + 24);
        CHECK(sub != path);
        REQUIRE(in_ram(sub, 28));
        CHECK(ld(m, path + 20) == sub);
        CHECK(ld(m, sub + 4) == 0xFFFFFFFFu);
        CHECK(ld(m, ld(m, path) + 4) == 1u);  // one node in each sList
        CHECK(ld(m, ld(m, sub) + 4) == 1u);
        ++paths;
    }
    for (int k = 0; k < 8 && has_case("sub_4AC920"); ++k) {
        restore(m, image);
        const u32 path = kData + 0x100, hdr = kData + 0x200;
        std::memset(m.at(path), 0, 28);
        const u32 flags = static_cast<u32>(k) & 3u;
        st(m, hdr, 1), st(m, hdr + 4, 0), st(m, hdr + 8, flags), stf(m, hdr + 12, 0.25f * static_cast<float>(k));
        const WPair p = wp(m, "sub_4AC920", {path, hdr, 0, 0}, 673000u + static_cast<u32>(k));
        CHECK_FALSE(p.run.stopped);
        if (p.v0() == path) {
            CHECK(ld(m, path + 4) == 0u);
            CHECK(ld(m, path + 8) == (flags & 1u));
            CHECK(ld(m, path + 12) == ((flags >> 1) & 1u));
            CHECK(ld(m, path + 16) == ld(m, hdr + 12));
            CHECK(ld(m, path + 24) == path);
        }
        ++bodies;
    }
    // rt2dMaestroAnimRewind: a stopped animation (flag 1) is left alone unless forced
    int rewinds = 0;
    for (int k = 0; k < 6 && has_case("sub_4B4EB0"); ++k) {
        restore(m, image);
        const u32 maestro = kData + 0x100, anim = kData + 0x400;
        std::memset(m.at(maestro), 0, 96);
        std::memset(m.at(anim), 0, 60);
        st(m, anim, 1u | (static_cast<u32>(k) << 4));
        stf(m, anim + 12, 0.5f * static_cast<float>(k));
        const std::vector<u8> before(m.at(kData), m.at(kData) + 0x1000);
        const WPair p = wp(m, "sub_4B4EB0", {maestro, anim, 0, 0}, 674000u + static_cast<u32>(k));
        CHECK_FALSE(p.run.stopped);
        CHECK(p.v0() == maestro);
        CHECK(std::memcmp(before.data(), m.at(kData), 0x1000) == 0);
        ++rewinds;
    }
    MESSAGE("Rt2d: " << objs << " objects, " << scenes << " scenes, " << paths << " path movetos, " << bodies << " path bodies, "
                     << rewinds << " rewinds");
}

// =====================================================================================================================
// Every body on the snapshots with built records, then the random-world sweep
// =====================================================================================================================
// Functions whose soup / random runs would only recurse through cycles a soup offers or start the whole device: they run
// in the tests above (or not at all on random input).
const std::set<u32> kNoSoup = {0x4E2B70u, 0x4AC5F0u, 0x4CAAC0u, 0x4AB200u, 0x4AC920u, 0x4ACB10u, 0x4ADBD0u, 0x4ADE90u, 0x4AE5A0u, 0x4AEBF0u, 0x4AEEA0u, 0x4B4EB0u};
// ... and of those, the ones the random worlds (all RW slots 0, a 64 KiB world of random words) cannot bound either.
const std::set<u32> kNoRandom = {0x4E2B70u, 0x4AC5F0u, 0x4CAAC0u, 0x4AB200u, 0x4AC920u, 0x4ADBD0u, 0x4AE5A0u, 0x4B4EB0u};

TEST_CASE("game(render_rw9): every body equals its recompiled body on the snapshots with built records") {
    int pairs = 0, whole = 0, snapshots = 0;
    std::map<std::string, int> runs;
    for (const char* sn : {"b_5800", "dorm_replay_4900", "climb_ref_17000"}) {
        std::vector<u8> image;
        auto mp = snapshot_machine(sn, image);
        if (!mp) {
            MESSAGE("SKIP: snapshot " << sn << " not found");
            continue;
        }
        ++snapshots;
        Machine& m = *mp;
        std::mt19937 rng{0x52573900u + static_cast<u32>(snapshots)};
        restore(m, image);
        std::vector<u32> live = live_entries(m, ld(m, kEngine + ld(m, kGpClump)));
        const std::vector<u32> cl = live_entries(m, ld(m, kEngine + ld(m, kGpClump) + 4));
        live.insert(live.end(), cl.begin(), cl.end());
        for (const Case& c : kCases) {
            if (kNoSoup.count(c.addr)) continue;
            for (int k = 0; k < 8; ++k) {
                restore(m, image);
                const u32 soup = kData + 0x1000;
                const u32 seed = rng();
                auto setup = [&m, seed, &live](StandInWorld& w) {
                    install_standard(w);
                    w.si.install_recorder(kCallback, "callback (returns 0)", 0);
                    std::mt19937 r{seed};
                    for (u32 i = 0; i < 0x2000; i += 4) {
                        const u32 kind = r() % 8;
                        u32 v;
                        if (kind < 3) {
                            const u32 off = r() % 0x2000;
                            v = soup + (off & ~15u);
                        } else if (kind < 5) {
                            v = r() % 8;
                        } else if (kind < 6 && !live.empty()) {
                            const u32 j = r() % static_cast<u32>(live.size());
                            v = live[j];
                        } else {
                            v = r() % 3 == 0 ? 0xFFFFFFFFu : 0;
                        }
                        st(m, soup + i, v);
                    }
                };
                Args a{};
                for (int i = 0; i < 4; ++i) {
                    const u32 pick = rng() % 4;
                    const u32 off = rng() % 0x2000;
                    a[static_cast<std::size_t>(i)] = pick < 2 ? soup + (off & ~15u) : pick == 2 ? off % 6 : kEngine;
                }
                const u32 t0off = rng() % 0x2000;
                const WPair p = wpair(m, c, a, 690000u + static_cast<u32>(pairs), setup,
                                      HwCheck{{}, {}, {}, {{GPR_T0, soup + (t0off & ~15u)}, {GPR_T1, soup + 0x600}}});
                ++pairs;
                whole += p.run.stopped ? 0 : 1;
                runs[c.name] += p.run.stopped ? 0 : 1;
            }
        }
    }
    if (snapshots == 0) return;
    MESSAGE("built-record pairs: " << pairs << " on " << snapshots << " snapshots, run whole " << whole);
    std::string never;
    for (const auto& [name, r] : runs)
        if (r == 0) never += name + " ";
    if (!never.empty()) MESSAGE("never run whole there: " << never);
}

// Every body against its recompiled body on random worlds (the p3fes_handgen sweep), each function from a fresh ELF
// image (the module opens / closes of earlier functions write the words later ones read).
TEST_CASE("game(render_rw9): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const std::vector<u8> elf_image(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        if (kNoRandom.count(c.addr)) continue;
        std::memcpy(m->mem.main_ram(), elf_image.data(), elf_image.size());
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            Args args{};
            for (std::size_t i = 0; i < 4; ++i) args[i] = hgp::random_arg(rng, kWorld, kWorldSize);
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
        const std::string summary = std::string(c.name) + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

}  // namespace

#else

TEST_CASE("game(render_rw9): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
