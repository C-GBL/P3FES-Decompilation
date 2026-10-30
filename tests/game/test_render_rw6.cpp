// Pair tests of slice render_rw6 (game/src/render/render_rw6.cpp): RenderWare, sixth pass -- the collision intersection
// tests, Rt2d, the RtFS manager, the sList helpers, the PS2AllMat node set-up, the engine's device requests. Every body
// runs against its recompiled body and tests/game/handgen_pairs.h compares the whole register file and cycles at every
// check point and at the return / stop, all 32 MiB of RAM (the dead stack included), the scratchpad, the BIOS window and
// the bus log; the stand-ins' call logs and heaps must be equal too (stand_ins.h).
//   * collision, on the real collision data of the replay snapshots (the field / dungeon geometries' collision trees of
//     dorm_replay_4900, climb_ref_17000, b_5800; the snapshots' worlds hold no triangles) and on worlds built around
//     those geometries: every line / sphere / box query pairs the hand and recompiled bodies, and the triangles the
//     callback receives must be the ones a host test finds (the host's line / triangle, sphere / triangle and
//     separating-axis box / triangle tests in double precision; a triangle within a small margin of the boundary may go
//     either way): the collision-tree walks report exactly what the all-triangles tests report, the world walks what
//     the geometry walks report, the atomic test what a host test in world space finds, the morph-target tests what
//     the host finds on the blended vertices; the two triangle tests against the host on random triangles;
//   * documented rules for the other groups: the sList growth / destroy / to-array / end, the error get, the engine
//     plugin offsets against the registry, the version, the device's standard answers, the PS2AllMat node set-up, the
//     RtFS lookups (exact / case-insensitive / prefix) and the stream adaptors, the Rt2d path segments (normals,
//     lengths, mitres) and point-inside test, the polygon corner / point-in-triangle classifications, the CTM
//     translate / scale;
//   * the random-world sweep (the p3fes_handgen skeleton).
// P3FES_HG_SEEDS sets the pairs per function of the random sweep, P3FES_HG_ONLY one function, P3FES_HG_TRACE traces.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/render_rw6.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
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

namespace p3fes::recomp_gen {
void fn_sub_45F930_0045f930(EEContext&);  // generated body
void fn_sub_45F930_0045f930__recomp(EEContext&);  // recompiled
void fn_sub_4606B0_004606b0(EEContext&);  // generated body
void fn_sub_4606B0_004606b0__recomp(EEContext&);  // recompiled
void fn_sub_460EC0_00460ec0(EEContext&);  // generated body
void fn_sub_460EC0_00460ec0__recomp(EEContext&);  // recompiled
void fn_sub_461900_00461900(EEContext&);  // generated body
void fn_sub_461900_00461900__recomp(EEContext&);  // recompiled
void fn_sub_461D00_00461d00(EEContext&);  // generated body
void fn_sub_461D00_00461d00__recomp(EEContext&);  // recompiled
void fn_sub_461EA0_00461ea0(EEContext&);  // generated body
void fn_sub_461EA0_00461ea0__recomp(EEContext&);  // recompiled
void fn_sub_462BB0_00462bb0(EEContext&);  // generated body
void fn_sub_462BB0_00462bb0__recomp(EEContext&);  // recompiled
void fn_sub_463490_00463490(EEContext&);  // generated body
void fn_sub_463490_00463490__recomp(EEContext&);  // recompiled
void fn_sub_463B20_00463b20(EEContext&);  // generated body
void fn_sub_463B20_00463b20__recomp(EEContext&);  // recompiled
void fn_sub_463F20_00463f20(EEContext&);  // generated body
void fn_sub_463F20_00463f20__recomp(EEContext&);  // recompiled
void fn_sub_4A38F0_004a38f0(EEContext&);  // generated body
void fn_sub_4A38F0_004a38f0__recomp(EEContext&);  // recompiled
void fn_sub_4A3A80_004a3a80(EEContext&);  // generated body
void fn_sub_4A3A80_004a3a80__recomp(EEContext&);  // recompiled
void fn_sub_4A3C10_004a3c10(EEContext&);  // generated body
void fn_sub_4A3C10_004a3c10__recomp(EEContext&);  // recompiled
void fn_sub_4A3D70_004a3d70(EEContext&);  // generated body
void fn_sub_4A3D70_004a3d70__recomp(EEContext&);  // recompiled
void fn_RxPipelineNodePS2AllMatSetVU1CodeArray_004a3db0(EEContext&);  // generated body
void fn_RxPipelineNodePS2AllMatSetVU1CodeArray_004a3db0__recomp(EEContext&);  // recompiled
void fn_sub_4A3E30_004a3e30(EEContext&);  // generated body
void fn_sub_4A3E30_004a3e30__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_0_004a3f10(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_0_004a3f10__recomp(EEContext&);  // recompiled
void fn_sub_4A4D50_004a4d50(EEContext&);  // generated body
void fn_sub_4A4D50_004a4d50__recomp(EEContext&);  // recompiled
void fn_sub_4A4DA0_004a4da0(EEContext&);  // generated body
void fn_sub_4A4DA0_004a4da0__recomp(EEContext&);  // recompiled
void fn_sub_4A4E40_004a4e40(EEContext&);  // generated body
void fn_sub_4A4E40_004a4e40__recomp(EEContext&);  // recompiled
void fn_sub_4A4EF0_004a4ef0(EEContext&);  // generated body
void fn_sub_4A4EF0_004a4ef0__recomp(EEContext&);  // recompiled
void fn_sub_4A4F90_004a4f90(EEContext&);  // generated body
void fn_sub_4A4F90_004a4f90__recomp(EEContext&);  // recompiled
void fn_sub_4A5080_004a5080(EEContext&);  // generated body
void fn_sub_4A5080_004a5080__recomp(EEContext&);  // recompiled
void fn_sub_4A5100_004a5100(EEContext&);  // generated body
void fn_sub_4A5100_004a5100__recomp(EEContext&);  // recompiled
void fn_sub_4A5200_004a5200(EEContext&);  // generated body
void fn_sub_4A5200_004a5200__recomp(EEContext&);  // recompiled
void fn_sub_4A5210_004a5210(EEContext&);  // generated body
void fn_sub_4A5210_004a5210__recomp(EEContext&);  // recompiled
void fn_sub_4A5290_004a5290(EEContext&);  // generated body
void fn_sub_4A5290_004a5290__recomp(EEContext&);  // recompiled
void fn_sub_4A52A0_004a52a0(EEContext&);  // generated body
void fn_sub_4A52A0_004a52a0__recomp(EEContext&);  // recompiled
void fn_sub_4A5320_004a5320(EEContext&);  // generated body
void fn_sub_4A5320_004a5320__recomp(EEContext&);  // recompiled
void fn_sub_4A5330_004a5330(EEContext&);  // generated body
void fn_sub_4A5330_004a5330__recomp(EEContext&);  // recompiled
void fn_sub_4A53B0_004a53b0(EEContext&);  // generated body
void fn_sub_4A53B0_004a53b0__recomp(EEContext&);  // recompiled
void fn_sub_4A5400_004a5400(EEContext&);  // generated body
void fn_sub_4A5400_004a5400__recomp(EEContext&);  // recompiled
void fn_sub_4A5540_004a5540(EEContext&);  // generated body
void fn_sub_4A5540_004a5540__recomp(EEContext&);  // recompiled
void fn_sub_4AA540_004aa540(EEContext&);  // generated body
void fn_sub_4AA540_004aa540__recomp(EEContext&);  // recompiled
void fn_sub_4AA620_004aa620(EEContext&);  // generated body
void fn_sub_4AA620_004aa620__recomp(EEContext&);  // recompiled
void fn_sub_4AA6C0_004aa6c0(EEContext&);  // generated body
void fn_sub_4AA6C0_004aa6c0__recomp(EEContext&);  // recompiled
void fn_sub_4AADA0_004aada0(EEContext&);  // generated body
void fn_sub_4AADA0_004aada0__recomp(EEContext&);  // recompiled
void fn_sub_4AAE00_004aae00(EEContext&);  // generated body
void fn_sub_4AAE00_004aae00__recomp(EEContext&);  // recompiled
void fn_sub_4AB170_004ab170(EEContext&);  // generated body
void fn_sub_4AB170_004ab170__recomp(EEContext&);  // recompiled
void fn_sub_4AB1B0_004ab1b0(EEContext&);  // generated body
void fn_sub_4AB1B0_004ab1b0__recomp(EEContext&);  // recompiled
void fn_sub_4AB2C0_004ab2c0(EEContext&);  // generated body
void fn_sub_4AB2C0_004ab2c0__recomp(EEContext&);  // recompiled
void fn_sub_4AB410_004ab410(EEContext&);  // generated body
void fn_sub_4AB410_004ab410__recomp(EEContext&);  // recompiled
void fn_sub_4AC120_004ac120(EEContext&);  // generated body
void fn_sub_4AC120_004ac120__recomp(EEContext&);  // recompiled
void fn_sub_4AC7F0_004ac7f0(EEContext&);  // generated body
void fn_sub_4AC7F0_004ac7f0__recomp(EEContext&);  // recompiled
void fn_sub_4AC860_004ac860(EEContext&);  // generated body
void fn_sub_4AC860_004ac860__recomp(EEContext&);  // recompiled
void fn_sub_4ACCC0_004accc0(EEContext&);  // generated body
void fn_sub_4ACCC0_004accc0__recomp(EEContext&);  // recompiled
void fn_sub_4ACE60_004ace60(EEContext&);  // generated body
void fn_sub_4ACE60_004ace60__recomp(EEContext&);  // recompiled
void fn_sub_4AD6A0_004ad6a0(EEContext&);  // generated body
void fn_sub_4AD6A0_004ad6a0__recomp(EEContext&);  // recompiled
void fn_sub_4ADB50_004adb50(EEContext&);  // generated body
void fn_sub_4ADB50_004adb50__recomp(EEContext&);  // recompiled
void fn_sub_4ADB80_004adb80(EEContext&);  // generated body
void fn_sub_4ADB80_004adb80__recomp(EEContext&);  // recompiled
void fn_sub_4ADC70_004adc70(EEContext&);  // generated body
void fn_sub_4ADC70_004adc70__recomp(EEContext&);  // recompiled
void fn_sub_4ADCA0_004adca0(EEContext&);  // generated body
void fn_sub_4ADCA0_004adca0__recomp(EEContext&);  // recompiled
void fn_sub_4ADDB0_004addb0(EEContext&);  // generated body
void fn_sub_4ADDB0_004addb0__recomp(EEContext&);  // recompiled
void fn_sub_4ADFD0_004adfd0(EEContext&);  // generated body
void fn_sub_4ADFD0_004adfd0__recomp(EEContext&);  // recompiled
void fn_sub_4AE010_004ae010(EEContext&);  // generated body
void fn_sub_4AE010_004ae010__recomp(EEContext&);  // recompiled
void fn_sub_4AE020_004ae020(EEContext&);  // generated body
void fn_sub_4AE020_004ae020__recomp(EEContext&);  // recompiled
void fn_sub_4AE1D0_004ae1d0(EEContext&);  // generated body
void fn_sub_4AE1D0_004ae1d0__recomp(EEContext&);  // recompiled
void fn_sub_4AE1E0_004ae1e0(EEContext&);  // generated body
void fn_sub_4AE1E0_004ae1e0__recomp(EEContext&);  // recompiled
void fn_sub_4AE1F0_004ae1f0(EEContext&);  // generated body
void fn_sub_4AE1F0_004ae1f0__recomp(EEContext&);  // recompiled
void fn_sub_4AE8F0_004ae8f0(EEContext&);  // generated body
void fn_sub_4AE8F0_004ae8f0__recomp(EEContext&);  // recompiled
void fn_sub_4AE900_004ae900(EEContext&);  // generated body
void fn_sub_4AE900_004ae900__recomp(EEContext&);  // recompiled
void fn_sub_4AEB60_004aeb60(EEContext&);  // generated body
void fn_sub_4AEB60_004aeb60__recomp(EEContext&);  // recompiled
void fn_sub_4AEF50_004aef50(EEContext&);  // generated body
void fn_sub_4AEF50_004aef50__recomp(EEContext&);  // recompiled
void fn_sub_4B0360_004b0360(EEContext&);  // generated body
void fn_sub_4B0360_004b0360__recomp(EEContext&);  // recompiled
void fn_sub_4B0430_004b0430(EEContext&);  // generated body
void fn_sub_4B0430_004b0430__recomp(EEContext&);  // recompiled
void fn_sub_4B0560_004b0560(EEContext&);  // generated body
void fn_sub_4B0560_004b0560__recomp(EEContext&);  // recompiled
void fn_sub_4B08C0_004b08c0(EEContext&);  // generated body
void fn_sub_4B08C0_004b08c0__recomp(EEContext&);  // recompiled
void fn_sub_4B0DF0_004b0df0(EEContext&);  // generated body
void fn_sub_4B0DF0_004b0df0__recomp(EEContext&);  // recompiled
void fn_sub_4B1050_004b1050(EEContext&);  // generated body
void fn_sub_4B1050_004b1050__recomp(EEContext&);  // recompiled
void fn_sub_4B1090_004b1090(EEContext&);  // generated body
void fn_sub_4B1090_004b1090__recomp(EEContext&);  // recompiled
void fn_rt2dPS2PipeOpen_004b1100(EEContext&);  // generated body
void fn_rt2dPS2PipeOpen_004b1100__recomp(EEContext&);  // recompiled
void fn_sub_4B11A0_004b11a0(EEContext&);  // generated body
void fn_sub_4B11A0_004b11a0__recomp(EEContext&);  // recompiled
void fn_sub_4B11F0_004b11f0(EEContext&);  // generated body
void fn_sub_4B11F0_004b11f0__recomp(EEContext&);  // recompiled
void fn_sub_4B1240_004b1240(EEContext&);  // generated body
void fn_sub_4B1240_004b1240__recomp(EEContext&);  // recompiled
void fn_sub_4B1990_004b1990(EEContext&);  // generated body
void fn_sub_4B1990_004b1990__recomp(EEContext&);  // recompiled
void fn_sub_4B1A30_004b1a30(EEContext&);  // generated body
void fn_sub_4B1A30_004b1a30__recomp(EEContext&);  // recompiled
void fn_sub_4B1A40_004b1a40(EEContext&);  // generated body
void fn_sub_4B1A40_004b1a40__recomp(EEContext&);  // recompiled
void fn_sub_4B1A80_004b1a80(EEContext&);  // generated body
void fn_sub_4B1A80_004b1a80__recomp(EEContext&);  // recompiled
void fn_sub_4B1AE0_004b1ae0(EEContext&);  // generated body
void fn_sub_4B1AE0_004b1ae0__recomp(EEContext&);  // recompiled
void fn_sub_4B1B00_004b1b00(EEContext&);  // generated body
void fn_sub_4B1B00_004b1b00__recomp(EEContext&);  // recompiled
void fn_sub_4B1B60_004b1b60(EEContext&);  // generated body
void fn_sub_4B1B60_004b1b60__recomp(EEContext&);  // recompiled
void fn_sub_4B1B90_004b1b90(EEContext&);  // generated body
void fn_sub_4B1B90_004b1b90__recomp(EEContext&);  // recompiled
void fn_sub_4B1C80_004b1c80(EEContext&);  // generated body
void fn_sub_4B1C80_004b1c80__recomp(EEContext&);  // recompiled
void fn_sub_4B2A90_004b2a90(EEContext&);  // generated body
void fn_sub_4B2A90_004b2a90__recomp(EEContext&);  // recompiled
void fn_sub_4B2B40_004b2b40(EEContext&);  // generated body
void fn_sub_4B2B40_004b2b40__recomp(EEContext&);  // recompiled
void fn_sub_4B2BA0_004b2ba0(EEContext&);  // generated body
void fn_sub_4B2BA0_004b2ba0__recomp(EEContext&);  // recompiled
void fn_sub_4B2BD0_004b2bd0(EEContext&);  // generated body
void fn_sub_4B2BD0_004b2bd0__recomp(EEContext&);  // recompiled
void fn_j__rwSListGetEntry_004b2c70(EEContext&);  // generated body
void fn_j__rwSListGetEntry_004b2c70__recomp(EEContext&);  // recompiled
void fn_sub_4B2E70_004b2e70(EEContext&);  // generated body
void fn_sub_4B2E70_004b2e70__recomp(EEContext&);  // recompiled
void fn_sub_4B3030_004b3030(EEContext&);  // generated body
void fn_sub_4B3030_004b3030__recomp(EEContext&);  // recompiled
void fn_sub_4B30A0_004b30a0(EEContext&);  // generated body
void fn_sub_4B30A0_004b30a0__recomp(EEContext&);  // recompiled
void fn_sub_4B3100_004b3100(EEContext&);  // generated body
void fn_sub_4B3100_004b3100__recomp(EEContext&);  // recompiled
void fn_sub_4B3490_004b3490(EEContext&);  // generated body
void fn_sub_4B3490_004b3490__recomp(EEContext&);  // recompiled
void fn_sub_4B34D0_004b34d0(EEContext&);  // generated body
void fn_sub_4B34D0_004b34d0__recomp(EEContext&);  // recompiled
void fn_sub_4B34E0_004b34e0(EEContext&);  // generated body
void fn_sub_4B34E0_004b34e0__recomp(EEContext&);  // recompiled
void fn_sub_4B3610_004b3610(EEContext&);  // generated body
void fn_sub_4B3610_004b3610__recomp(EEContext&);  // recompiled
void fn_sub_4B3700_004b3700(EEContext&);  // generated body
void fn_sub_4B3700_004b3700__recomp(EEContext&);  // recompiled
void fn_sub_4B3720_004b3720(EEContext&);  // generated body
void fn_sub_4B3720_004b3720__recomp(EEContext&);  // recompiled
void fn_sub_4B3790_004b3790(EEContext&);  // generated body
void fn_sub_4B3790_004b3790__recomp(EEContext&);  // recompiled
void fn_sub_4B39F0_004b39f0(EEContext&);  // generated body
void fn_sub_4B39F0_004b39f0__recomp(EEContext&);  // recompiled
void fn_sub_4B3DE0_004b3de0(EEContext&);  // generated body
void fn_sub_4B3DE0_004b3de0__recomp(EEContext&);  // recompiled
void fn_sub_4B3F50_004b3f50(EEContext&);  // generated body
void fn_sub_4B3F50_004b3f50__recomp(EEContext&);  // recompiled
void fn_sub_4B4090_004b4090(EEContext&);  // generated body
void fn_sub_4B4090_004b4090__recomp(EEContext&);  // recompiled
void fn_sub_4B40F0_004b40f0(EEContext&);  // generated body
void fn_sub_4B40F0_004b40f0__recomp(EEContext&);  // recompiled
void fn_sub_4B41B0_004b41b0(EEContext&);  // generated body
void fn_sub_4B41B0_004b41b0__recomp(EEContext&);  // recompiled
void fn_sub_4B4720_004b4720(EEContext&);  // generated body
void fn_sub_4B4720_004b4720__recomp(EEContext&);  // recompiled
void fn_sub_4B4810_004b4810(EEContext&);  // generated body
void fn_sub_4B4810_004b4810__recomp(EEContext&);  // recompiled
void fn_sub_4B4A60_004b4a60(EEContext&);  // generated body
void fn_sub_4B4A60_004b4a60__recomp(EEContext&);  // recompiled
void fn_sub_4B4A70_004b4a70(EEContext&);  // generated body
void fn_sub_4B4A70_004b4a70__recomp(EEContext&);  // recompiled
void fn_sub_4B4BA0_004b4ba0(EEContext&);  // generated body
void fn_sub_4B4BA0_004b4ba0__recomp(EEContext&);  // recompiled
void fn_sub_4B59B0_004b59b0(EEContext&);  // generated body
void fn_sub_4B59B0_004b59b0__recomp(EEContext&);  // recompiled
void fn_sub_4B6000_004b6000(EEContext&);  // generated body
void fn_sub_4B6000_004b6000__recomp(EEContext&);  // recompiled
void fn_sub_4B6190_004b6190(EEContext&);  // generated body
void fn_sub_4B6190_004b6190__recomp(EEContext&);  // recompiled
void fn_sub_4B6270_004b6270(EEContext&);  // generated body
void fn_sub_4B6270_004b6270__recomp(EEContext&);  // recompiled
void fn_sub_4B62A0_004b62a0(EEContext&);  // generated body
void fn_sub_4B62A0_004b62a0__recomp(EEContext&);  // recompiled
void fn_sub_4B6350_004b6350(EEContext&);  // generated body
void fn_sub_4B6350_004b6350__recomp(EEContext&);  // recompiled
void fn_sub_4B6500_004b6500(EEContext&);  // generated body
void fn_sub_4B6500_004b6500__recomp(EEContext&);  // recompiled
void fn_sub_4BAE00_004bae00(EEContext&);  // generated body
void fn_sub_4BAE00_004bae00__recomp(EEContext&);  // recompiled
void fn_sub_4BB5D0_004bb5d0(EEContext&);  // generated body
void fn_sub_4BB5D0_004bb5d0__recomp(EEContext&);  // recompiled
void fn_sub_4BF6E0_004bf6e0(EEContext&);  // generated body
void fn_sub_4BF6E0_004bf6e0__recomp(EEContext&);  // recompiled
void fn_sub_4BF7E0_004bf7e0(EEContext&);  // generated body
void fn_sub_4BF7E0_004bf7e0__recomp(EEContext&);  // recompiled
void fn_sub_4BF9E0_004bf9e0(EEContext&);  // generated body
void fn_sub_4BF9E0_004bf9e0__recomp(EEContext&);  // recompiled
void fn_sub_4BFA10_004bfa10(EEContext&);  // generated body
void fn_sub_4BFA10_004bfa10__recomp(EEContext&);  // recompiled
void fn_sub_4BFA70_004bfa70(EEContext&);  // generated body
void fn_sub_4BFA70_004bfa70__recomp(EEContext&);  // recompiled
void fn_sub_4BFB20_004bfb20(EEContext&);  // generated body
void fn_sub_4BFB20_004bfb20__recomp(EEContext&);  // recompiled
void fn_sub_4BFC20_004bfc20(EEContext&);  // generated body
void fn_sub_4BFC20_004bfc20__recomp(EEContext&);  // recompiled
void fn_sub_4BFC80_004bfc80(EEContext&);  // generated body
void fn_sub_4BFC80_004bfc80__recomp(EEContext&);  // recompiled
void fn_sub_4BFD50_004bfd50(EEContext&);  // generated body
void fn_sub_4BFD50_004bfd50__recomp(EEContext&);  // recompiled
void fn_sub_4BFDE0_004bfde0(EEContext&);  // generated body
void fn_sub_4BFDE0_004bfde0__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_1_004c0060(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_1_004c0060__recomp(EEContext&);  // recompiled
void fn_sub_4C0070_004c0070(EEContext&);  // generated body
void fn_sub_4C0070_004c0070__recomp(EEContext&);  // recompiled
void fn_sub_4C0230_004c0230(EEContext&);  // generated body
void fn_sub_4C0230_004c0230__recomp(EEContext&);  // recompiled
void fn_sub_4C03D0_004c03d0(EEContext&);  // generated body
void fn_sub_4C03D0_004c03d0__recomp(EEContext&);  // recompiled
void fn_sub_4C0420_004c0420(EEContext&);  // generated body
void fn_sub_4C0420_004c0420__recomp(EEContext&);  // recompiled
void fn_sub_4C0470_004c0470(EEContext&);  // generated body
void fn_sub_4C0470_004c0470__recomp(EEContext&);  // recompiled
void fn_sub_4C06B0_004c06b0(EEContext&);  // generated body
void fn_sub_4C06B0_004c06b0__recomp(EEContext&);  // recompiled
void fn_sub_4C0830_004c0830(EEContext&);  // generated body
void fn_sub_4C0830_004c0830__recomp(EEContext&);  // recompiled
void fn_sub_4C0870_004c0870(EEContext&);  // generated body
void fn_sub_4C0870_004c0870__recomp(EEContext&);  // recompiled
void fn_sub_4C0880_004c0880(EEContext&);  // generated body
void fn_sub_4C0880_004c0880__recomp(EEContext&);  // recompiled
void fn_sub_4C0F60_004c0f60(EEContext&);  // generated body
void fn_sub_4C0F60_004c0f60__recomp(EEContext&);  // recompiled
void fn_sub_4C0FD0_004c0fd0(EEContext&);  // generated body
void fn_sub_4C0FD0_004c0fd0__recomp(EEContext&);  // recompiled
void fn_sub_4C1BC0_004c1bc0(EEContext&);  // generated body
void fn_sub_4C1BC0_004c1bc0__recomp(EEContext&);  // recompiled
void fn_sub_4C1BE0_004c1be0(EEContext&);  // generated body
void fn_sub_4C1BE0_004c1be0__recomp(EEContext&);  // recompiled
void fn_sub_4C1C00_004c1c00(EEContext&);  // generated body
void fn_sub_4C1C00_004c1c00__recomp(EEContext&);  // recompiled
void fn_sub_4C1C30_004c1c30(EEContext&);  // generated body
void fn_sub_4C1C30_004c1c30__recomp(EEContext&);  // recompiled
void fn_sub_4C1CD0_004c1cd0(EEContext&);  // generated body
void fn_sub_4C1CD0_004c1cd0__recomp(EEContext&);  // recompiled
void fn_sub_4C1F70_004c1f70(EEContext&);  // generated body
void fn_sub_4C1F70_004c1f70__recomp(EEContext&);  // recompiled
void fn_sub_4C2080_004c2080(EEContext&);  // generated body
void fn_sub_4C2080_004c2080__recomp(EEContext&);  // recompiled
void fn_sub_4C20B0_004c20b0(EEContext&);  // generated body
void fn_sub_4C20B0_004c20b0__recomp(EEContext&);  // recompiled
void fn_sub_4C2130_004c2130(EEContext&);  // generated body
void fn_sub_4C2130_004c2130__recomp(EEContext&);  // recompiled
void fn_name__C9type_info_1_004c21d0(EEContext&);  // generated body
void fn_name__C9type_info_1_004c21d0__recomp(EEContext&);  // recompiled
void fn_sub_4C21E0_004c21e0(EEContext&);  // generated body
void fn_sub_4C21E0_004c21e0__recomp(EEContext&);  // recompiled
void fn_sub_4CA380_004ca380(EEContext&);  // generated body
void fn_sub_4CA380_004ca380__recomp(EEContext&);  // recompiled
void fn_sub_4CA3A0_004ca3a0(EEContext&);  // generated body
void fn_sub_4CA3A0_004ca3a0__recomp(EEContext&);  // recompiled
void fn__rwDeviceSystemRequest_004ca3e0(EEContext&);  // generated body
void fn__rwDeviceSystemRequest_004ca3e0__recomp(EEContext&);  // recompiled
void fn_sub_4CA510_004ca510(EEContext&);  // generated body
void fn_sub_4CA510_004ca510__recomp(EEContext&);  // recompiled
void fn_sub_4CA520_004ca520(EEContext&);  // generated body
void fn_sub_4CA520_004ca520__recomp(EEContext&);  // recompiled
void fn_sub_4CA550_004ca550(EEContext&);  // generated body
void fn_sub_4CA550_004ca550__recomp(EEContext&);  // recompiled
void fn_sub_4CA560_004ca560(EEContext&);  // generated body
void fn_sub_4CA560_004ca560__recomp(EEContext&);  // recompiled
void fn_sub_4CA5B0_004ca5b0(EEContext&);  // generated body
void fn_sub_4CA5B0_004ca5b0__recomp(EEContext&);  // recompiled
void fn_RwEngineSetVideoMode_004ca600(EEContext&);  // generated body
void fn_RwEngineSetVideoMode_004ca600__recomp(EEContext&);  // recompiled
void fn_sub_4F3EC0_004f3ec0(EEContext&);  // generated body
void fn_sub_4F3EC0_004f3ec0__recomp(EEContext&);  // recompiled
void fn_sub_4F3F70_004f3f70(EEContext&);  // generated body
void fn_sub_4F3F70_004f3f70__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_45F930", 0x45F930, &recomp_gen::fn_sub_45F930_0045f930, &recomp_gen::fn_sub_45F930_0045f930__recomp},
    {"sub_4606B0", 0x4606B0, &recomp_gen::fn_sub_4606B0_004606b0, &recomp_gen::fn_sub_4606B0_004606b0__recomp},
    {"sub_460EC0", 0x460EC0, &recomp_gen::fn_sub_460EC0_00460ec0, &recomp_gen::fn_sub_460EC0_00460ec0__recomp},
    {"sub_461900", 0x461900, &recomp_gen::fn_sub_461900_00461900, &recomp_gen::fn_sub_461900_00461900__recomp},
    {"sub_461D00", 0x461D00, &recomp_gen::fn_sub_461D00_00461d00, &recomp_gen::fn_sub_461D00_00461d00__recomp},
    {"sub_461EA0", 0x461EA0, &recomp_gen::fn_sub_461EA0_00461ea0, &recomp_gen::fn_sub_461EA0_00461ea0__recomp},
    {"sub_462BB0", 0x462BB0, &recomp_gen::fn_sub_462BB0_00462bb0, &recomp_gen::fn_sub_462BB0_00462bb0__recomp},
    {"sub_463490", 0x463490, &recomp_gen::fn_sub_463490_00463490, &recomp_gen::fn_sub_463490_00463490__recomp},
    {"sub_463B20", 0x463B20, &recomp_gen::fn_sub_463B20_00463b20, &recomp_gen::fn_sub_463B20_00463b20__recomp},
    {"sub_463F20", 0x463F20, &recomp_gen::fn_sub_463F20_00463f20, &recomp_gen::fn_sub_463F20_00463f20__recomp},
    {"sub_4A38F0", 0x4A38F0, &recomp_gen::fn_sub_4A38F0_004a38f0, &recomp_gen::fn_sub_4A38F0_004a38f0__recomp},
    {"sub_4A3A80", 0x4A3A80, &recomp_gen::fn_sub_4A3A80_004a3a80, &recomp_gen::fn_sub_4A3A80_004a3a80__recomp},
    {"sub_4A3C10", 0x4A3C10, &recomp_gen::fn_sub_4A3C10_004a3c10, &recomp_gen::fn_sub_4A3C10_004a3c10__recomp},
    {"sub_4A3D70", 0x4A3D70, &recomp_gen::fn_sub_4A3D70_004a3d70, &recomp_gen::fn_sub_4A3D70_004a3d70__recomp},
    {"RxPipelineNodePS2AllMatSetVU1CodeArray", 0x4A3DB0, &recomp_gen::fn_RxPipelineNodePS2AllMatSetVU1CodeArray_004a3db0, &recomp_gen::fn_RxPipelineNodePS2AllMatSetVU1CodeArray_004a3db0__recomp},
    {"sub_4A3E30", 0x4A3E30, &recomp_gen::fn_sub_4A3E30_004a3e30, &recomp_gen::fn_sub_4A3E30_004a3e30__recomp},
    {"sceLibgcc32GetErxEntries_0", 0x4A3F10, &recomp_gen::fn_sceLibgcc32GetErxEntries_0_004a3f10, &recomp_gen::fn_sceLibgcc32GetErxEntries_0_004a3f10__recomp},
    {"sub_4A4D50", 0x4A4D50, &recomp_gen::fn_sub_4A4D50_004a4d50, &recomp_gen::fn_sub_4A4D50_004a4d50__recomp},
    {"sub_4A4DA0", 0x4A4DA0, &recomp_gen::fn_sub_4A4DA0_004a4da0, &recomp_gen::fn_sub_4A4DA0_004a4da0__recomp},
    {"sub_4A4E40", 0x4A4E40, &recomp_gen::fn_sub_4A4E40_004a4e40, &recomp_gen::fn_sub_4A4E40_004a4e40__recomp},
    {"sub_4A4EF0", 0x4A4EF0, &recomp_gen::fn_sub_4A4EF0_004a4ef0, &recomp_gen::fn_sub_4A4EF0_004a4ef0__recomp},
    {"sub_4A4F90", 0x4A4F90, &recomp_gen::fn_sub_4A4F90_004a4f90, &recomp_gen::fn_sub_4A4F90_004a4f90__recomp},
    {"sub_4A5080", 0x4A5080, &recomp_gen::fn_sub_4A5080_004a5080, &recomp_gen::fn_sub_4A5080_004a5080__recomp},
    {"sub_4A5100", 0x4A5100, &recomp_gen::fn_sub_4A5100_004a5100, &recomp_gen::fn_sub_4A5100_004a5100__recomp},
    {"sub_4A5200", 0x4A5200, &recomp_gen::fn_sub_4A5200_004a5200, &recomp_gen::fn_sub_4A5200_004a5200__recomp},
    {"sub_4A5210", 0x4A5210, &recomp_gen::fn_sub_4A5210_004a5210, &recomp_gen::fn_sub_4A5210_004a5210__recomp},
    {"sub_4A5290", 0x4A5290, &recomp_gen::fn_sub_4A5290_004a5290, &recomp_gen::fn_sub_4A5290_004a5290__recomp},
    {"sub_4A52A0", 0x4A52A0, &recomp_gen::fn_sub_4A52A0_004a52a0, &recomp_gen::fn_sub_4A52A0_004a52a0__recomp},
    {"sub_4A5320", 0x4A5320, &recomp_gen::fn_sub_4A5320_004a5320, &recomp_gen::fn_sub_4A5320_004a5320__recomp},
    {"sub_4A5330", 0x4A5330, &recomp_gen::fn_sub_4A5330_004a5330, &recomp_gen::fn_sub_4A5330_004a5330__recomp},
    {"sub_4A53B0", 0x4A53B0, &recomp_gen::fn_sub_4A53B0_004a53b0, &recomp_gen::fn_sub_4A53B0_004a53b0__recomp},
    {"sub_4A5400", 0x4A5400, &recomp_gen::fn_sub_4A5400_004a5400, &recomp_gen::fn_sub_4A5400_004a5400__recomp},
    {"sub_4A5540", 0x4A5540, &recomp_gen::fn_sub_4A5540_004a5540, &recomp_gen::fn_sub_4A5540_004a5540__recomp},
    {"sub_4AA540", 0x4AA540, &recomp_gen::fn_sub_4AA540_004aa540, &recomp_gen::fn_sub_4AA540_004aa540__recomp},
    {"sub_4AA620", 0x4AA620, &recomp_gen::fn_sub_4AA620_004aa620, &recomp_gen::fn_sub_4AA620_004aa620__recomp},
    {"sub_4AA6C0", 0x4AA6C0, &recomp_gen::fn_sub_4AA6C0_004aa6c0, &recomp_gen::fn_sub_4AA6C0_004aa6c0__recomp},
    {"sub_4AADA0", 0x4AADA0, &recomp_gen::fn_sub_4AADA0_004aada0, &recomp_gen::fn_sub_4AADA0_004aada0__recomp},
    {"sub_4AAE00", 0x4AAE00, &recomp_gen::fn_sub_4AAE00_004aae00, &recomp_gen::fn_sub_4AAE00_004aae00__recomp},
    {"sub_4AB170", 0x4AB170, &recomp_gen::fn_sub_4AB170_004ab170, &recomp_gen::fn_sub_4AB170_004ab170__recomp},
    {"sub_4AB1B0", 0x4AB1B0, &recomp_gen::fn_sub_4AB1B0_004ab1b0, &recomp_gen::fn_sub_4AB1B0_004ab1b0__recomp},
    {"sub_4AB2C0", 0x4AB2C0, &recomp_gen::fn_sub_4AB2C0_004ab2c0, &recomp_gen::fn_sub_4AB2C0_004ab2c0__recomp},
    {"sub_4AB410", 0x4AB410, &recomp_gen::fn_sub_4AB410_004ab410, &recomp_gen::fn_sub_4AB410_004ab410__recomp},
    {"sub_4AC120", 0x4AC120, &recomp_gen::fn_sub_4AC120_004ac120, &recomp_gen::fn_sub_4AC120_004ac120__recomp},
    {"sub_4AC7F0", 0x4AC7F0, &recomp_gen::fn_sub_4AC7F0_004ac7f0, &recomp_gen::fn_sub_4AC7F0_004ac7f0__recomp},
    {"sub_4AC860", 0x4AC860, &recomp_gen::fn_sub_4AC860_004ac860, &recomp_gen::fn_sub_4AC860_004ac860__recomp},
    {"sub_4ACCC0", 0x4ACCC0, &recomp_gen::fn_sub_4ACCC0_004accc0, &recomp_gen::fn_sub_4ACCC0_004accc0__recomp},
    {"sub_4ACE60", 0x4ACE60, &recomp_gen::fn_sub_4ACE60_004ace60, &recomp_gen::fn_sub_4ACE60_004ace60__recomp},
    {"sub_4AD6A0", 0x4AD6A0, &recomp_gen::fn_sub_4AD6A0_004ad6a0, &recomp_gen::fn_sub_4AD6A0_004ad6a0__recomp},
    {"sub_4ADB50", 0x4ADB50, &recomp_gen::fn_sub_4ADB50_004adb50, &recomp_gen::fn_sub_4ADB50_004adb50__recomp},
    {"sub_4ADB80", 0x4ADB80, &recomp_gen::fn_sub_4ADB80_004adb80, &recomp_gen::fn_sub_4ADB80_004adb80__recomp},
    {"sub_4ADC70", 0x4ADC70, &recomp_gen::fn_sub_4ADC70_004adc70, &recomp_gen::fn_sub_4ADC70_004adc70__recomp},
    {"sub_4ADCA0", 0x4ADCA0, &recomp_gen::fn_sub_4ADCA0_004adca0, &recomp_gen::fn_sub_4ADCA0_004adca0__recomp},
    {"sub_4ADDB0", 0x4ADDB0, &recomp_gen::fn_sub_4ADDB0_004addb0, &recomp_gen::fn_sub_4ADDB0_004addb0__recomp},
    {"sub_4ADFD0", 0x4ADFD0, &recomp_gen::fn_sub_4ADFD0_004adfd0, &recomp_gen::fn_sub_4ADFD0_004adfd0__recomp},
    {"sub_4AE010", 0x4AE010, &recomp_gen::fn_sub_4AE010_004ae010, &recomp_gen::fn_sub_4AE010_004ae010__recomp},
    {"sub_4AE020", 0x4AE020, &recomp_gen::fn_sub_4AE020_004ae020, &recomp_gen::fn_sub_4AE020_004ae020__recomp},
    {"sub_4AE1D0", 0x4AE1D0, &recomp_gen::fn_sub_4AE1D0_004ae1d0, &recomp_gen::fn_sub_4AE1D0_004ae1d0__recomp},
    {"sub_4AE1E0", 0x4AE1E0, &recomp_gen::fn_sub_4AE1E0_004ae1e0, &recomp_gen::fn_sub_4AE1E0_004ae1e0__recomp},
    {"sub_4AE1F0", 0x4AE1F0, &recomp_gen::fn_sub_4AE1F0_004ae1f0, &recomp_gen::fn_sub_4AE1F0_004ae1f0__recomp},
    {"sub_4AE8F0", 0x4AE8F0, &recomp_gen::fn_sub_4AE8F0_004ae8f0, &recomp_gen::fn_sub_4AE8F0_004ae8f0__recomp},
    {"sub_4AE900", 0x4AE900, &recomp_gen::fn_sub_4AE900_004ae900, &recomp_gen::fn_sub_4AE900_004ae900__recomp},
    {"sub_4AEB60", 0x4AEB60, &recomp_gen::fn_sub_4AEB60_004aeb60, &recomp_gen::fn_sub_4AEB60_004aeb60__recomp},
    {"sub_4AEF50", 0x4AEF50, &recomp_gen::fn_sub_4AEF50_004aef50, &recomp_gen::fn_sub_4AEF50_004aef50__recomp},
    {"sub_4B0360", 0x4B0360, &recomp_gen::fn_sub_4B0360_004b0360, &recomp_gen::fn_sub_4B0360_004b0360__recomp},
    {"sub_4B0430", 0x4B0430, &recomp_gen::fn_sub_4B0430_004b0430, &recomp_gen::fn_sub_4B0430_004b0430__recomp},
    {"sub_4B0560", 0x4B0560, &recomp_gen::fn_sub_4B0560_004b0560, &recomp_gen::fn_sub_4B0560_004b0560__recomp},
    {"sub_4B08C0", 0x4B08C0, &recomp_gen::fn_sub_4B08C0_004b08c0, &recomp_gen::fn_sub_4B08C0_004b08c0__recomp},
    {"sub_4B0DF0", 0x4B0DF0, &recomp_gen::fn_sub_4B0DF0_004b0df0, &recomp_gen::fn_sub_4B0DF0_004b0df0__recomp},
    {"sub_4B1050", 0x4B1050, &recomp_gen::fn_sub_4B1050_004b1050, &recomp_gen::fn_sub_4B1050_004b1050__recomp},
    {"sub_4B1090", 0x4B1090, &recomp_gen::fn_sub_4B1090_004b1090, &recomp_gen::fn_sub_4B1090_004b1090__recomp},
    {"rt2dPS2PipeOpen", 0x4B1100, &recomp_gen::fn_rt2dPS2PipeOpen_004b1100, &recomp_gen::fn_rt2dPS2PipeOpen_004b1100__recomp},
    {"sub_4B11A0", 0x4B11A0, &recomp_gen::fn_sub_4B11A0_004b11a0, &recomp_gen::fn_sub_4B11A0_004b11a0__recomp},
    {"sub_4B11F0", 0x4B11F0, &recomp_gen::fn_sub_4B11F0_004b11f0, &recomp_gen::fn_sub_4B11F0_004b11f0__recomp},
    {"sub_4B1240", 0x4B1240, &recomp_gen::fn_sub_4B1240_004b1240, &recomp_gen::fn_sub_4B1240_004b1240__recomp},
    {"sub_4B1990", 0x4B1990, &recomp_gen::fn_sub_4B1990_004b1990, &recomp_gen::fn_sub_4B1990_004b1990__recomp},
    {"sub_4B1A30", 0x4B1A30, &recomp_gen::fn_sub_4B1A30_004b1a30, &recomp_gen::fn_sub_4B1A30_004b1a30__recomp},
    {"sub_4B1A40", 0x4B1A40, &recomp_gen::fn_sub_4B1A40_004b1a40, &recomp_gen::fn_sub_4B1A40_004b1a40__recomp},
    {"sub_4B1A80", 0x4B1A80, &recomp_gen::fn_sub_4B1A80_004b1a80, &recomp_gen::fn_sub_4B1A80_004b1a80__recomp},
    {"sub_4B1AE0", 0x4B1AE0, &recomp_gen::fn_sub_4B1AE0_004b1ae0, &recomp_gen::fn_sub_4B1AE0_004b1ae0__recomp},
    {"sub_4B1B00", 0x4B1B00, &recomp_gen::fn_sub_4B1B00_004b1b00, &recomp_gen::fn_sub_4B1B00_004b1b00__recomp},
    {"sub_4B1B60", 0x4B1B60, &recomp_gen::fn_sub_4B1B60_004b1b60, &recomp_gen::fn_sub_4B1B60_004b1b60__recomp},
    {"sub_4B1B90", 0x4B1B90, &recomp_gen::fn_sub_4B1B90_004b1b90, &recomp_gen::fn_sub_4B1B90_004b1b90__recomp},
    {"sub_4B1C80", 0x4B1C80, &recomp_gen::fn_sub_4B1C80_004b1c80, &recomp_gen::fn_sub_4B1C80_004b1c80__recomp},
    {"sub_4B2A90", 0x4B2A90, &recomp_gen::fn_sub_4B2A90_004b2a90, &recomp_gen::fn_sub_4B2A90_004b2a90__recomp},
    {"sub_4B2B40", 0x4B2B40, &recomp_gen::fn_sub_4B2B40_004b2b40, &recomp_gen::fn_sub_4B2B40_004b2b40__recomp},
    {"sub_4B2BA0", 0x4B2BA0, &recomp_gen::fn_sub_4B2BA0_004b2ba0, &recomp_gen::fn_sub_4B2BA0_004b2ba0__recomp},
    {"sub_4B2BD0", 0x4B2BD0, &recomp_gen::fn_sub_4B2BD0_004b2bd0, &recomp_gen::fn_sub_4B2BD0_004b2bd0__recomp},
    {"j__rwSListGetEntry", 0x4B2C70, &recomp_gen::fn_j__rwSListGetEntry_004b2c70, &recomp_gen::fn_j__rwSListGetEntry_004b2c70__recomp},
    {"sub_4B2E70", 0x4B2E70, &recomp_gen::fn_sub_4B2E70_004b2e70, &recomp_gen::fn_sub_4B2E70_004b2e70__recomp},
    {"sub_4B3030", 0x4B3030, &recomp_gen::fn_sub_4B3030_004b3030, &recomp_gen::fn_sub_4B3030_004b3030__recomp},
    {"sub_4B30A0", 0x4B30A0, &recomp_gen::fn_sub_4B30A0_004b30a0, &recomp_gen::fn_sub_4B30A0_004b30a0__recomp},
    {"sub_4B3100", 0x4B3100, &recomp_gen::fn_sub_4B3100_004b3100, &recomp_gen::fn_sub_4B3100_004b3100__recomp},
    {"sub_4B3490", 0x4B3490, &recomp_gen::fn_sub_4B3490_004b3490, &recomp_gen::fn_sub_4B3490_004b3490__recomp},
    {"sub_4B34D0", 0x4B34D0, &recomp_gen::fn_sub_4B34D0_004b34d0, &recomp_gen::fn_sub_4B34D0_004b34d0__recomp},
    {"sub_4B34E0", 0x4B34E0, &recomp_gen::fn_sub_4B34E0_004b34e0, &recomp_gen::fn_sub_4B34E0_004b34e0__recomp},
    {"sub_4B3610", 0x4B3610, &recomp_gen::fn_sub_4B3610_004b3610, &recomp_gen::fn_sub_4B3610_004b3610__recomp},
    {"sub_4B3700", 0x4B3700, &recomp_gen::fn_sub_4B3700_004b3700, &recomp_gen::fn_sub_4B3700_004b3700__recomp},
    {"sub_4B3720", 0x4B3720, &recomp_gen::fn_sub_4B3720_004b3720, &recomp_gen::fn_sub_4B3720_004b3720__recomp},
    {"sub_4B3790", 0x4B3790, &recomp_gen::fn_sub_4B3790_004b3790, &recomp_gen::fn_sub_4B3790_004b3790__recomp},
    {"sub_4B39F0", 0x4B39F0, &recomp_gen::fn_sub_4B39F0_004b39f0, &recomp_gen::fn_sub_4B39F0_004b39f0__recomp},
    {"sub_4B3DE0", 0x4B3DE0, &recomp_gen::fn_sub_4B3DE0_004b3de0, &recomp_gen::fn_sub_4B3DE0_004b3de0__recomp},
    {"sub_4B3F50", 0x4B3F50, &recomp_gen::fn_sub_4B3F50_004b3f50, &recomp_gen::fn_sub_4B3F50_004b3f50__recomp},
    {"sub_4B4090", 0x4B4090, &recomp_gen::fn_sub_4B4090_004b4090, &recomp_gen::fn_sub_4B4090_004b4090__recomp},
    {"sub_4B40F0", 0x4B40F0, &recomp_gen::fn_sub_4B40F0_004b40f0, &recomp_gen::fn_sub_4B40F0_004b40f0__recomp},
    {"sub_4B41B0", 0x4B41B0, &recomp_gen::fn_sub_4B41B0_004b41b0, &recomp_gen::fn_sub_4B41B0_004b41b0__recomp},
    {"sub_4B4720", 0x4B4720, &recomp_gen::fn_sub_4B4720_004b4720, &recomp_gen::fn_sub_4B4720_004b4720__recomp},
    {"sub_4B4810", 0x4B4810, &recomp_gen::fn_sub_4B4810_004b4810, &recomp_gen::fn_sub_4B4810_004b4810__recomp},
    {"sub_4B4A60", 0x4B4A60, &recomp_gen::fn_sub_4B4A60_004b4a60, &recomp_gen::fn_sub_4B4A60_004b4a60__recomp},
    {"sub_4B4A70", 0x4B4A70, &recomp_gen::fn_sub_4B4A70_004b4a70, &recomp_gen::fn_sub_4B4A70_004b4a70__recomp},
    {"sub_4B4BA0", 0x4B4BA0, &recomp_gen::fn_sub_4B4BA0_004b4ba0, &recomp_gen::fn_sub_4B4BA0_004b4ba0__recomp},
    {"sub_4B59B0", 0x4B59B0, &recomp_gen::fn_sub_4B59B0_004b59b0, &recomp_gen::fn_sub_4B59B0_004b59b0__recomp},
    {"sub_4B6000", 0x4B6000, &recomp_gen::fn_sub_4B6000_004b6000, &recomp_gen::fn_sub_4B6000_004b6000__recomp},
    {"sub_4B6190", 0x4B6190, &recomp_gen::fn_sub_4B6190_004b6190, &recomp_gen::fn_sub_4B6190_004b6190__recomp},
    {"sub_4B6270", 0x4B6270, &recomp_gen::fn_sub_4B6270_004b6270, &recomp_gen::fn_sub_4B6270_004b6270__recomp},
    {"sub_4B62A0", 0x4B62A0, &recomp_gen::fn_sub_4B62A0_004b62a0, &recomp_gen::fn_sub_4B62A0_004b62a0__recomp},
    {"sub_4B6350", 0x4B6350, &recomp_gen::fn_sub_4B6350_004b6350, &recomp_gen::fn_sub_4B6350_004b6350__recomp},
    {"sub_4B6500", 0x4B6500, &recomp_gen::fn_sub_4B6500_004b6500, &recomp_gen::fn_sub_4B6500_004b6500__recomp},
    {"sub_4BAE00", 0x4BAE00, &recomp_gen::fn_sub_4BAE00_004bae00, &recomp_gen::fn_sub_4BAE00_004bae00__recomp},
    {"sub_4BB5D0", 0x4BB5D0, &recomp_gen::fn_sub_4BB5D0_004bb5d0, &recomp_gen::fn_sub_4BB5D0_004bb5d0__recomp},
    {"sub_4BF6E0", 0x4BF6E0, &recomp_gen::fn_sub_4BF6E0_004bf6e0, &recomp_gen::fn_sub_4BF6E0_004bf6e0__recomp},
    {"sub_4BF7E0", 0x4BF7E0, &recomp_gen::fn_sub_4BF7E0_004bf7e0, &recomp_gen::fn_sub_4BF7E0_004bf7e0__recomp},
    {"sub_4BF9E0", 0x4BF9E0, &recomp_gen::fn_sub_4BF9E0_004bf9e0, &recomp_gen::fn_sub_4BF9E0_004bf9e0__recomp},
    {"sub_4BFA10", 0x4BFA10, &recomp_gen::fn_sub_4BFA10_004bfa10, &recomp_gen::fn_sub_4BFA10_004bfa10__recomp},
    {"sub_4BFA70", 0x4BFA70, &recomp_gen::fn_sub_4BFA70_004bfa70, &recomp_gen::fn_sub_4BFA70_004bfa70__recomp},
    {"sub_4BFB20", 0x4BFB20, &recomp_gen::fn_sub_4BFB20_004bfb20, &recomp_gen::fn_sub_4BFB20_004bfb20__recomp},
    {"sub_4BFC20", 0x4BFC20, &recomp_gen::fn_sub_4BFC20_004bfc20, &recomp_gen::fn_sub_4BFC20_004bfc20__recomp},
    {"sub_4BFC80", 0x4BFC80, &recomp_gen::fn_sub_4BFC80_004bfc80, &recomp_gen::fn_sub_4BFC80_004bfc80__recomp},
    {"sub_4BFD50", 0x4BFD50, &recomp_gen::fn_sub_4BFD50_004bfd50, &recomp_gen::fn_sub_4BFD50_004bfd50__recomp},
    {"sub_4BFDE0", 0x4BFDE0, &recomp_gen::fn_sub_4BFDE0_004bfde0, &recomp_gen::fn_sub_4BFDE0_004bfde0__recomp},
    {"sceLibgcc32GetErxEntries_1", 0x4C0060, &recomp_gen::fn_sceLibgcc32GetErxEntries_1_004c0060, &recomp_gen::fn_sceLibgcc32GetErxEntries_1_004c0060__recomp},
    {"sub_4C0070", 0x4C0070, &recomp_gen::fn_sub_4C0070_004c0070, &recomp_gen::fn_sub_4C0070_004c0070__recomp},
    {"sub_4C0230", 0x4C0230, &recomp_gen::fn_sub_4C0230_004c0230, &recomp_gen::fn_sub_4C0230_004c0230__recomp},
    {"sub_4C03D0", 0x4C03D0, &recomp_gen::fn_sub_4C03D0_004c03d0, &recomp_gen::fn_sub_4C03D0_004c03d0__recomp},
    {"sub_4C0420", 0x4C0420, &recomp_gen::fn_sub_4C0420_004c0420, &recomp_gen::fn_sub_4C0420_004c0420__recomp},
    {"sub_4C0470", 0x4C0470, &recomp_gen::fn_sub_4C0470_004c0470, &recomp_gen::fn_sub_4C0470_004c0470__recomp},
    {"sub_4C06B0", 0x4C06B0, &recomp_gen::fn_sub_4C06B0_004c06b0, &recomp_gen::fn_sub_4C06B0_004c06b0__recomp},
    {"sub_4C0830", 0x4C0830, &recomp_gen::fn_sub_4C0830_004c0830, &recomp_gen::fn_sub_4C0830_004c0830__recomp},
    {"sub_4C0870", 0x4C0870, &recomp_gen::fn_sub_4C0870_004c0870, &recomp_gen::fn_sub_4C0870_004c0870__recomp},
    {"sub_4C0880", 0x4C0880, &recomp_gen::fn_sub_4C0880_004c0880, &recomp_gen::fn_sub_4C0880_004c0880__recomp},
    {"sub_4C0F60", 0x4C0F60, &recomp_gen::fn_sub_4C0F60_004c0f60, &recomp_gen::fn_sub_4C0F60_004c0f60__recomp},
    {"sub_4C0FD0", 0x4C0FD0, &recomp_gen::fn_sub_4C0FD0_004c0fd0, &recomp_gen::fn_sub_4C0FD0_004c0fd0__recomp},
    {"sub_4C1BC0", 0x4C1BC0, &recomp_gen::fn_sub_4C1BC0_004c1bc0, &recomp_gen::fn_sub_4C1BC0_004c1bc0__recomp},
    {"sub_4C1BE0", 0x4C1BE0, &recomp_gen::fn_sub_4C1BE0_004c1be0, &recomp_gen::fn_sub_4C1BE0_004c1be0__recomp},
    {"sub_4C1C00", 0x4C1C00, &recomp_gen::fn_sub_4C1C00_004c1c00, &recomp_gen::fn_sub_4C1C00_004c1c00__recomp},
    {"sub_4C1C30", 0x4C1C30, &recomp_gen::fn_sub_4C1C30_004c1c30, &recomp_gen::fn_sub_4C1C30_004c1c30__recomp},
    {"sub_4C1CD0", 0x4C1CD0, &recomp_gen::fn_sub_4C1CD0_004c1cd0, &recomp_gen::fn_sub_4C1CD0_004c1cd0__recomp},
    {"sub_4C1F70", 0x4C1F70, &recomp_gen::fn_sub_4C1F70_004c1f70, &recomp_gen::fn_sub_4C1F70_004c1f70__recomp},
    {"sub_4C2080", 0x4C2080, &recomp_gen::fn_sub_4C2080_004c2080, &recomp_gen::fn_sub_4C2080_004c2080__recomp},
    {"sub_4C20B0", 0x4C20B0, &recomp_gen::fn_sub_4C20B0_004c20b0, &recomp_gen::fn_sub_4C20B0_004c20b0__recomp},
    {"sub_4C2130", 0x4C2130, &recomp_gen::fn_sub_4C2130_004c2130, &recomp_gen::fn_sub_4C2130_004c2130__recomp},
    {"name__C9type_info_1", 0x4C21D0, &recomp_gen::fn_name__C9type_info_1_004c21d0, &recomp_gen::fn_name__C9type_info_1_004c21d0__recomp},
    {"sub_4C21E0", 0x4C21E0, &recomp_gen::fn_sub_4C21E0_004c21e0, &recomp_gen::fn_sub_4C21E0_004c21e0__recomp},
    {"sub_4CA380", 0x4CA380, &recomp_gen::fn_sub_4CA380_004ca380, &recomp_gen::fn_sub_4CA380_004ca380__recomp},
    {"sub_4CA3A0", 0x4CA3A0, &recomp_gen::fn_sub_4CA3A0_004ca3a0, &recomp_gen::fn_sub_4CA3A0_004ca3a0__recomp},
    {"_rwDeviceSystemRequest", 0x4CA3E0, &recomp_gen::fn__rwDeviceSystemRequest_004ca3e0, &recomp_gen::fn__rwDeviceSystemRequest_004ca3e0__recomp},
    {"sub_4CA510", 0x4CA510, &recomp_gen::fn_sub_4CA510_004ca510, &recomp_gen::fn_sub_4CA510_004ca510__recomp},
    {"sub_4CA520", 0x4CA520, &recomp_gen::fn_sub_4CA520_004ca520, &recomp_gen::fn_sub_4CA520_004ca520__recomp},
    {"sub_4CA550", 0x4CA550, &recomp_gen::fn_sub_4CA550_004ca550, &recomp_gen::fn_sub_4CA550_004ca550__recomp},
    {"sub_4CA560", 0x4CA560, &recomp_gen::fn_sub_4CA560_004ca560, &recomp_gen::fn_sub_4CA560_004ca560__recomp},
    {"sub_4CA5B0", 0x4CA5B0, &recomp_gen::fn_sub_4CA5B0_004ca5b0, &recomp_gen::fn_sub_4CA5B0_004ca5b0__recomp},
    {"RwEngineSetVideoMode", 0x4CA600, &recomp_gen::fn_RwEngineSetVideoMode_004ca600, &recomp_gen::fn_RwEngineSetVideoMode_004ca600__recomp},
    {"sub_4F3EC0", 0x4F3EC0, &recomp_gen::fn_sub_4F3EC0_004f3ec0, &recomp_gen::fn_sub_4F3EC0_004f3ec0__recomp},
    {"sub_4F3F70", 0x4F3F70, &recomp_gen::fn_sub_4F3F70_004f3f70, &recomp_gen::fn_sub_4F3F70_004f3f70__recomp},
};

// The world of the random sweep: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

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
float ldf(Machine& m, u32 va) {
    float f;
    std::memcpy(&f, m.at(va), 4);
    return f;
}
void st(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void st16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void stf(Machine& m, u32 va, float f) { std::memcpy(m.at(va), &f, 4); }
void stv(Machine& m, u32 va, const double* v) {
    for (int i = 0; i < 3; ++i) stf(m, va + 4 * i, static_cast<float>(v[i]));
}
void sts(Machine& m, u32 va, const char* s) { std::memcpy(m.at(va), s, std::strlen(s) + 1); }
std::string lds(Machine& m, u32 va) { return reinterpret_cast<const char*>(m.at(va)); }
u32 fbits(float f) {
    u32 b;
    std::memcpy(&b, &f, 4);
    return b;
}
float frand(std::mt19937& rng, float lo, float hi) { return lo + (hi - lo) * static_cast<float>(rng() % 100001) / 100000.0f; }
bool chance(std::mt19937& rng, unsigned pct) { return rng() % 100 < pct; }
bool in_ram(u32 va, u32 len = 4) { return va != 0 && va < EEMemory::kMainRamSize - len; }

const Case& by_name(const char* n) {
    for (const Case& c : kCases)
        if (std::strcmp(c.name, n) == 0) return c;
    std::fprintf(stderr, "render_rw6 test: no case %s\n", n);
    std::abort();
}

// The RW globals the bodies read (render_rw5.h / render_rw6.h).
constexpr u32 kEngine = 0x960070u;
constexpr u32 kGpCollGeo = 0x7CE728u, kGpCollSector = 0x7CE72Cu, kGpAtomicModule = 0x7CE820u, kGpCameraModule = 0x7CE920u,
              kGpCamWorld = 0x7CE868u, kGpErrorModule = 0x7CE8D0u;
constexpr u32 kEngineRegistry = 0x77E630u;
// Test data: free in the ELF's image and in every replay snapshot (below the stand-in heap 0x1C00000).
constexpr u32 kData = 0x01BC0000u;
constexpr u32 kDataSize = 0x00040000u;
// Functions this build does not emit, served by stand-ins: the collision callback (and the other callbacks), the
// case-insensitive compare the RtFS device lookup calls through the engine's string slot.
constexpr u32 kCallback = 0x10A860u;
constexpr u32 kStrICmp = 0x4C7100u;

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

// --- the pair on stand-in worlds -------------------------------------------------------------------------------------
// hgp::pair with a fresh stand-in world around each body (the heap behind the RW memory slots and the free-list entry
// points, printf / sprintf, the H_Cdvd layer, the test's callbacks); afterwards both worlds' call logs, live heap blocks
// and bad frees must be equal. Float arguments go in through g_fpr (set after the harness's randomised registers).
Fn g_body[2];
StandInWorld* g_world[2];
std::map<unsigned, float> g_fpr;
void thunk(int k, EEContext& ctx) {
    StandInsScope s(g_world[k]->si);
    for (const auto& [r, f] : g_fpr) ctx.fpr[r] = fbits(f);
    g_body[k](ctx);
}
void thunk_hand(EEContext& ctx) { thunk(0, ctx); }
void thunk_recomp(EEContext& ctx) { thunk(1, ctx); }

// What the collision callback saw: the triangle's index (the collision triangle's +24) and the distance ($f12).
struct Hit {
    u32 index;
    float dist;
    bool operator==(const Hit& o) const { return index == o.index && fbits(dist) == fbits(o.dist); }
};
std::map<const StandIns*, std::vector<Hit>> g_hits;
int g_stop_after = 0;  // > 0: the callback returns 0 at that many hits (the walk must stop)

struct WPair {
    hgp::Run run;
    std::unique_ptr<StandInWorld> hand, recomp;
    std::vector<Hit> hits;  // the recompiled run's callback calls
    u32 v0() const { return static_cast<u32>(run.end.gpr[GPR_V0].u64[0]); }
};

WPair wpair(Machine& m, const Case& c, const Args& args, u32 seed, const WorldSetup& setup, const HwCheck& hw = {}) {
    WPair p;
    g_hits.clear();
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
    const auto& hh = g_hits[&p.hand->si];
    p.hits = g_hits[&p.recomp->si];
    CHECK(hh == p.hits);
    g_fpr.clear();
    return p;
}

// The collision world: the standard stand-ins and the callback, which records the triangle (argument `tri_arg`: 1 for
// the geometry walks, 2 for the world walks) and returns the intersection (go on) -- or 0 at g_stop_after hits.
WorldSetup coll_world(Machine& m, unsigned tri_arg) {
    return [&m, tri_arg](StandInWorld& w) {
        install_standard(w);
        w.si.install(kCallback, "collision callback", [&m, tri_arg](EEContext& ctx, StandIns& s, StandInCall& c) {
            auto& v = g_hits[&s];
            const u32 tri = static_cast<u32>(c.args[tri_arg]);
            float d;
            std::memcpy(&d, &ctx.fpr[12], 4);
            v.push_back({in_ram(tri + 24) ? ld(m, tri + 24) : 0xFFFFFFFFu, d});
            c.v0 = (g_stop_after > 0 && static_cast<int>(v.size()) >= g_stop_after) ? 0 : c.args[0];
        });
    };
}

// =====================================================================================================================
// Host geometry (double precision)
// =====================================================================================================================
using D3 = std::array<double, 3>;
D3 operator-(const D3& a, const D3& b) { return {a[0] - b[0], a[1] - b[1], a[2] - b[2]}; }
D3 operator+(const D3& a, const D3& b) { return {a[0] + b[0], a[1] + b[1], a[2] + b[2]}; }
D3 operator*(const D3& a, double s) { return {a[0] * s, a[1] * s, a[2] * s}; }
double dot(const D3& a, const D3& b) { return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]; }
D3 cross(const D3& a, const D3& b) { return {a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0]}; }
double len(const D3& a) { return std::sqrt(dot(a, a)); }
D3 rdv(Machine& m, u32 va) { return {ldf(m, va), ldf(m, va + 4), ldf(m, va + 8)}; }

enum Verdict { kMiss = 0, kHit = 1, kUnsure = 2 };

// The front-face line / triangle test of the bodies (det = e1 . (d x e2) > 0, the three edge conditions and the
// segment's [0, 1]), decided only with a margin of 1e-3 of det around every boundary.
int host_line(const D3& s, const D3& e, const D3& a, const D3& b, const D3& c) {
    const D3 d = e - s, e1 = b - a, e2 = c - a;
    const D3 p = cross(d, e2);
    const double det = dot(e1, p);
    const double scale = len(d) * len(e1) * len(e2) + 1e-30;
    if (det < -1e-4 * scale) return kMiss;
    if (det < 1e-4 * scale) return kUnsure;
    const D3 sa = s - a;
    const double u = dot(sa, p);
    const D3 q = cross(sa, e1);
    const double v = dot(d, q), t = dot(e2, q);
    const double mg = 1e-3 * det;
    auto inside = [&](double x, double lo, double hi) { return x > lo + mg && x < hi - mg; };
    auto outside = [&](double x, double lo, double hi) { return x < lo - mg || x > hi + mg; };
    if (outside(u, 0, det) || outside(v, 0, det) || outside(u + v, -1e300, det) || outside(t, 0, det)) return kMiss;
    if (inside(u, 0, det) && inside(v, 0, det) && inside(u + v, -1e300, det) && inside(t, 0, det)) return kHit;
    return kUnsure;
}

// The distance from p to the triangle (closest point, Ericson's regions).
double tri_dist(const D3& p, const D3& a, const D3& b, const D3& c) {
    const D3 ab = b - a, ac = c - a, ap = p - a;
    const double d1 = dot(ab, ap), d2 = dot(ac, ap);
    if (d1 <= 0 && d2 <= 0) return len(p - a);
    const D3 bp = p - b;
    const double d3 = dot(ab, bp), d4 = dot(ac, bp);
    if (d3 >= 0 && d4 <= d3) return len(p - b);
    const double vc = d1 * d4 - d3 * d2;
    if (vc <= 0 && d1 >= 0 && d3 <= 0) return len(p - (a + ab * (d1 / (d1 - d3))));
    const D3 cp = p - c;
    const double d5 = dot(ab, cp), d6 = dot(ac, cp);
    if (d6 >= 0 && d5 <= d6) return len(p - c);
    const double vb = d5 * d2 - d1 * d6;
    if (vb <= 0 && d2 >= 0 && d6 <= 0) return len(p - (a + ac * (d2 / (d2 - d6))));
    const double va = d3 * d6 - d5 * d4;
    if (va <= 0 && (d4 - d3) >= 0 && (d5 - d6) >= 0) return len(p - (b + (c - b) * ((d4 - d3) / ((d4 - d3) + (d5 - d6)))));
    const double den = 1.0 / (va + vb + vc);
    return len(p - (a + ab * (vb * den) + ac * (vc * den)));
}

// Any point of the triangle within the sphere (a degenerate triangle is left open: the body rejects a zero normal).
int host_sphere(const D3& ctr, double r, const D3& a, const D3& b, const D3& c) {
    const double area = len(cross(b - a, c - a));
    const double ext = std::max({len(b - a), len(c - a), len(c - b)});
    if (area < 1e-6 * ext * ext + 1e-12) return kUnsure;
    const double d = tri_dist(ctr, a, b, c);
    if (d < r * (1 - 1e-3) - 1e-6) return kHit;
    if (d > r * (1 + 1e-3) + 1e-6) return kMiss;
    return kUnsure;
}

// Box / triangle overlap by separating axes (the box's three axes, the face normal, the nine edge x axis directions).
int host_box(const D3& sup, const D3& inf, const D3& a, const D3& b, const D3& c) {
    const D3 ctr = (sup + inf) * 0.5, h = (sup - inf) * 0.5;
    const D3 v[3] = {a - ctr, b - ctr, c - ctr};
    const D3 e[3] = {v[1] - v[0], v[2] - v[1], v[0] - v[2]};
    std::vector<D3> axes = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, cross(e[0], e[1])};
    for (const D3& ed : e)
        for (const D3& ax : {D3{1, 0, 0}, D3{0, 1, 0}, D3{0, 0, 1}}) axes.push_back(cross(ed, ax));
    const double scale = len(sup - inf) + std::max({len(e[0]), len(e[1]), len(e[2])});
    double worst = -1e300;  // the largest normalised separation
    for (const D3& L : axes) {
        const double l = len(L);
        if (l < 1e-9 * scale * scale) continue;
        const double p0 = dot(v[0], L), p1 = dot(v[1], L), p2 = dot(v[2], L);
        const double rr = h[0] * std::fabs(L[0]) + h[1] * std::fabs(L[1]) + h[2] * std::fabs(L[2]);
        const double sep = std::max(std::min({p0, p1, p2}) - rr, -std::max({p0, p1, p2}) - rr) / l;
        worst = std::max(worst, sep);
    }
    if (worst > 1e-4 * scale) return kMiss;
    if (worst < -1e-4 * scale) return kHit;
    return kUnsure;
}

// =====================================================================================================================
// Collision data of the snapshots
// =====================================================================================================================
// A one-morph-target geometry as the host reads it (rw6::geo, rw5::morph, rw6::tri).
struct Geo {
    u32 g = 0, coll = 0, verts = 0, tris = 0, ntri = 0, nverts = 0;
    std::vector<D3> v;
    std::vector<std::array<u16, 3>> t;
    D3 lo{}, hi{};
    double size() const { return len(hi - lo); }
};
bool read_geo(Machine& m, u32 g, Geo& out) {
    if (!in_ram(g, 128) || ld(m, g + 24) != 1) return false;
    const u32 morph = ld(m, g + 92);
    if (!in_ram(morph, 28)) return false;
    out = Geo{};
    out.g = g;
    out.coll = ld(m, g + ld(m, kGpCollGeo));
    out.ntri = ld(m, g + 16);
    out.nverts = ld(m, g + 20);
    out.verts = ld(m, morph + 20);
    out.tris = ld(m, g + 44);
    if (out.ntri == 0 || out.ntri > 20000 || out.nverts == 0 || out.nverts > 20000 || !in_ram(out.verts, 12 * out.nverts) ||
        !in_ram(out.tris, 8 * out.ntri))
        return false;
    out.lo = {1e30, 1e30, 1e30};
    out.hi = {-1e30, -1e30, -1e30};
    for (u32 i = 0; i < out.nverts; ++i) {
        out.v.push_back(rdv(m, out.verts + 12 * i));
        for (int k = 0; k < 3; ++k) out.lo[k] = std::min(out.lo[k], out.v.back()[k]), out.hi[k] = std::max(out.hi[k], out.v.back()[k]);
    }
    for (u32 i = 0; i < out.ntri; ++i) {
        const std::array<u16, 3> t{ld16(m, out.tris + 8 * i), ld16(m, out.tris + 8 * i + 2), ld16(m, out.tris + 8 * i + 4)};
        if (t[0] >= out.nverts || t[1] >= out.nverts || t[2] >= out.nverts) return false;
        out.t.push_back(t);
    }
    return true;
}

// The live atomics (the clump / atomic module's atomic free list) and their geometries that carry a collision tree.
std::vector<u32> live_atomics(Machine& m) { return live_entries(m, ld(m, kEngine + ld(m, kGpAtomicModule))); }
std::vector<u32> collision_geometries(Machine& m, std::size_t max) {
    std::vector<u32> out;
    for (u32 a : live_atomics(m)) {
        const u32 g = ld(m, a + 24);
        Geo geo;
        if (std::find(out.begin(), out.end(), g) != out.end() || !read_geo(m, g, geo) || geo.coll == 0) continue;
        out.push_back(g);
        if (out.size() >= max) break;
    }
    return out;
}

// A random point on a random triangle (for queries that hit something).
D3 point_on(const Geo& g, std::mt19937& rng, u32* which = nullptr) {
    const u32 k = rng() % g.ntri;
    if (which) *which = k;
    double u = frand(rng, 0, 1), v = frand(rng, 0, 1);
    if (u + v > 1) u = 1 - u, v = 1 - v;
    const D3 &a = g.v[g.t[k][0]], &b = g.v[g.t[k][1]], &c = g.v[g.t[k][2]];
    return a + (b - a) * u + (c - a) * v;
}
D3 rand_dir(std::mt19937& rng) {
    for (;;) {
        const D3 d{frand(rng, -1, 1), frand(rng, -1, 1), frand(rng, -1, 1)};
        const double l = len(d);
        if (l > 0.1 && l <= 1) return d * (1 / l);
    }
}

// Checks one query's reported triangles against the host's verdicts: every reported index valid and not a clear
// miss, every clear hit reported, no index twice. Counts into `stats` {hits, unsure, reported}.
template <class Classify>
void check_hits(const std::vector<Hit>& hits, u32 ntri, Classify classify, std::array<long, 3>& stats, const char* what) {
    std::vector<u8> seen(ntri, 0);
    for (const Hit& h : hits) {
        INFO(what << ": reported triangle " << h.index);
        REQUIRE(h.index < ntri);
        CHECK(seen[h.index] == 0);
        seen[h.index] = 1;
        CHECK(classify(h.index) != kMiss);
    }
    for (u32 i = 0; i < ntri; ++i) {
        const int v = classify(i);
        if (v == kHit) {
            INFO(what << ": triangle " << i << " is a clear hit but was not reported");
            CHECK(seen[i] == 1);
            ++stats[0];
        } else if (v == kUnsure)
            ++stats[1];
    }
    stats[2] += static_cast<long>(hits.size());
}
std::vector<u32> sorted_indices(const std::vector<Hit>& hits) {
    std::vector<u32> v;
    for (const Hit& h : hits) v.push_back(h.index);
    std::sort(v.begin(), v.end());
    return v;
}

}  // namespace

// =====================================================================================================================
// Collision: the geometry tests on the snapshots' collision geometries
// =====================================================================================================================
// For each geometry with a collision tree: lines through a random triangle and across the bounding box, spheres around
// points of the surface, each run through the tree walk (sub_461EA0 / sub_462BB0) and the all-triangles test
// (sub_461900 / sub_461D00), hand against recompiled. The tree walk must report the same triangles as the
// all-triangles test (the same tests, the tree only prunes), and both what the host's test finds. A tenth of the queries
// stop at the first hit (the callback returns 0): at most one call, in both bodies.
TEST_CASE("game(render_rw6): the geometry collision tests report the triangles the host finds (snapshot collision trees)") {
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const int per = env ? std::max(1, std::atoi(env) / 8) : 4;
    std::array<long, 3> line_stats{}, sphere_stats{};
    int geos = 0, pairs = 0, snapshots = 0;
    for (const char* sn : {"dorm_replay_4900", "climb_ref_17000", "b_5800"}) {
        std::vector<u8> image;
        auto mp = snapshot_machine(sn, image);
        if (!mp) {
            MESSAGE("SKIP: snapshot " << sn << " not found");
            continue;
        }
        ++snapshots;
        Machine& m = *mp;
        const std::vector<u32> gs = collision_geometries(m, 12);
        REQUIRE(!gs.empty());
        std::mt19937 rng{0x52574C00u + static_cast<u32>(snapshots)};
        for (u32 g : gs) {
            Geo geo;
            REQUIRE(read_geo(m, g, geo));
            ++geos;
            const double sz = std::max(geo.size(), 1e-3);
            for (int k = 0; k < per; ++k) {
                // --- a line: through a surface point (half the time) or across the box
                D3 s, e;
                if (chance(rng, 60)) {
                    // through a surface point, mostly against the face normal (the test only takes front faces)
                    u32 t = 0;
                    const D3 p = point_on(geo, rng, &t);
                    const D3 fn = cross(geo.v[geo.t[t][1]] - geo.v[geo.t[t][0]], geo.v[geo.t[t][2]] - geo.v[geo.t[t][0]]);
                    D3 d = rand_dir(rng);
                    if (len(fn) > 0 && chance(rng, 75)) {
                        d = fn * (-1 / len(fn)) + d * 0.6;
                        d = d * (1 / len(d));
                    }
                    s = p - d * (sz * frand(rng, 0.05f, 0.6f));
                    e = p + d * (sz * frand(rng, 0.05f, 0.6f));
                } else {
                    for (int i = 0; i < 3; ++i)
                        s[i] = frand(rng, static_cast<float>(geo.lo[i]), static_cast<float>(geo.hi[i])),
                        e[i] = frand(rng, static_cast<float>(geo.lo[i]), static_cast<float>(geo.hi[i]));
                }
                restore(m, image);
                const u32 line = kData + 0x100, isect = kData + 0x140;
                stv(m, line, s.data()), stv(m, line + 12, e.data());
                std::memcpy(m.at(isect), m.at(line), 24);
                st(m, isect + 24, 1);
                g_stop_after = chance(rng, 10) ? 1 : 0;
                HwCheck hw;
                hw.gpr_in = {{GPR_T0, kData + 0x200}};
                const WPair tree = wpair(m, by_name("sub_461EA0"), {g, line, isect, kCallback}, 600000u + pairs, coll_world(m, 1), hw);
                const WPair all = wpair(m, by_name("sub_461900"), {g, line, isect, kCallback}, 600001u + pairs, coll_world(m, 1), hw);
                pairs += 2;
                CHECK(!tree.run.stopped);
                CHECK(!all.run.stopped);
                if (g_stop_after) {
                    CHECK(tree.hits.size() <= 1);
                    CHECK(all.hits.size() <= 1);
                } else {
                    INFO(sn << " geometry " << hex64(g) << " line query " << k);
                    CHECK(sorted_indices(tree.hits) == sorted_indices(all.hits));
                    auto cls = [&](u32 i) {
                        return host_line(s, e, geo.v[geo.t[i][0]], geo.v[geo.t[i][1]], geo.v[geo.t[i][2]]);
                    };
                    check_hits(tree.hits, geo.ntri, cls, line_stats, "line (tree)");
                    for (const Hit& h : tree.hits) CHECK((h.dist >= -1e-4f && h.dist <= 1.0001f));
                }
                // --- a sphere around a surface point
                const D3 ctr = point_on(geo, rng) + rand_dir(rng) * (sz * frand(rng, 0.0f, 0.1f));
                const double r = sz * frand(rng, 0.01f, 0.25f);
                restore(m, image);
                const u32 sph = kData + 0x100;
                stv(m, sph, ctr.data()), stf(m, sph + 12, static_cast<float>(r));
                std::memcpy(m.at(isect), m.at(sph), 16);
                st(m, isect + 24, 3);
                g_stop_after = chance(rng, 10) ? 1 : 0;
                const WPair stree = wpair(m, by_name("sub_462BB0"), {g, sph, isect, kCallback}, 600002u + pairs, coll_world(m, 1), hw);
                const WPair sall = wpair(m, by_name("sub_461D00"), {g, sph, isect, kCallback}, 600003u + pairs, coll_world(m, 1), hw);
                pairs += 2;
                CHECK(!stree.run.stopped);
                CHECK(!sall.run.stopped);
                if (g_stop_after) {
                    CHECK(stree.hits.size() <= 1);
                    CHECK(sall.hits.size() <= 1);
                } else {
                    INFO(sn << " geometry " << hex64(g) << " sphere query " << k);
                    CHECK(sorted_indices(stree.hits) == sorted_indices(sall.hits));
                    auto cls = [&](u32 i) {
                        return host_sphere(ctr, r, geo.v[geo.t[i][0]], geo.v[geo.t[i][1]], geo.v[geo.t[i][2]]);
                    };
                    check_hits(stree.hits, geo.ntri, cls, sphere_stats, "sphere (tree)");
                    check_hits(sall.hits, geo.ntri, cls, sphere_stats, "sphere (all)");
                }
                g_stop_after = 0;
            }
        }
    }
    if (snapshots == 0) return;
    MESSAGE("geometry collision: " << geos << " geometries on " << snapshots << " snapshots, " << pairs << " pairs; lines: "
                                   << line_stats[2] << " triangles reported, " << line_stats[0] << " clear hits, " << line_stats[1]
                                   << " borderline; spheres: " << sphere_stats[2] << " reported, " << sphere_stats[0]
                                   << " clear hits, " << sphere_stats[1] << " borderline");
    CHECK(line_stats[0] > 0);
    CHECK(sphere_stats[0] > 0);
}

// The atomic's sphere test (sub_463F20) on live atomics with collision geometry: a sphere in world space near a
// transformed surface point; the body takes it into the atomic's space through the frame's LTM. With a rigid LTM the
// reported triangles must be the ones within the sphere in world space (the host transforms the vertices).
TEST_CASE("game(render_rw6): the atomic sphere test reports the triangles within the sphere in world space") {
    std::array<long, 3> stats{};
    int atoms = 0, rigid = 0, pairs = 0;
    for (const char* sn : {"dorm_replay_4900", "climb_ref_17000"}) {
        std::vector<u8> image;
        auto mp = snapshot_machine(sn, image);
        if (!mp) {
            MESSAGE("SKIP: snapshot " << sn << " not found");
            continue;
        }
        Machine& m = *mp;
        std::mt19937 rng{0x52574C40u};
        int taken = 0;
        for (u32 a : live_atomics(m)) {
            Geo geo;
            const u32 frame = ld(m, a + 4);
            if (!read_geo(m, ld(m, a + 24), geo) || !in_ram(frame, 160) || taken >= 16) continue;
            ++taken, ++atoms;
            for (int k = 0; k < 3; ++k) {
                restore(m, image);
                // the LTM the body will use (RwFrameGetLTM syncs a dirty hierarchy first): read it after the pair
                const D3 lp = point_on(geo, rng);
                const double sz = std::max(geo.size(), 1e-3);
                const D3 R{ldf(m, frame + 80), ldf(m, frame + 84), ldf(m, frame + 88)};
                const D3 U{ldf(m, frame + 96), ldf(m, frame + 100), ldf(m, frame + 104)};
                const D3 A{ldf(m, frame + 112), ldf(m, frame + 116), ldf(m, frame + 120)};
                const D3 P{ldf(m, frame + 128), ldf(m, frame + 132), ldf(m, frame + 136)};
                const D3 wp = R * lp[0] + U * lp[1] + A * lp[2] + P + rand_dir(rng) * (sz * frand(rng, 0.0f, 0.05f));
                const double r = sz * frand(rng, 0.02f, 0.2f);
                const u32 sph = kData + 0x100, isect = kData + 0x140;
                stv(m, sph, wp.data()), stf(m, sph + 12, static_cast<float>(r));
                std::memcpy(m.at(isect), m.at(sph), 16);
                st(m, isect + 24, 3);
                HwCheck hw;
                hw.gpr_in = {{GPR_T0, kData + 0x200}};
                const WPair p = wpair(m, by_name("sub_463F20"), {a, sph, isect, kCallback}, 610000u + pairs, coll_world(m, 1), hw);
                ++pairs;
                CHECK(!p.run.stopped);
                const D3 R2{ldf(m, frame + 80), ldf(m, frame + 84), ldf(m, frame + 88)};
                const D3 U2{ldf(m, frame + 96), ldf(m, frame + 100), ldf(m, frame + 104)};
                const D3 A2{ldf(m, frame + 112), ldf(m, frame + 116), ldf(m, frame + 120)};
                const D3 P2{ldf(m, frame + 128), ldf(m, frame + 132), ldf(m, frame + 136)};
                const bool ortho = std::fabs(len(R2) - 1) < 1e-3 && std::fabs(len(U2) - 1) < 1e-3 && std::fabs(len(A2) - 1) < 1e-3 &&
                                   std::fabs(dot(R2, U2)) < 1e-3 && std::fabs(dot(R2, A2)) < 1e-3 && std::fabs(dot(U2, A2)) < 1e-3;
                if (!ortho) continue;
                ++rigid;
                auto world = [&](const D3& v) { return R2 * v[0] + U2 * v[1] + A2 * v[2] + P2; };
                auto cls = [&](u32 i) {
                    return host_sphere(wp, r, world(geo.v[geo.t[i][0]]), world(geo.v[geo.t[i][1]]), world(geo.v[geo.t[i][2]]));
                };
                INFO(sn << " atomic " << hex64(a));
                check_hits(p.hits, geo.ntri, cls, stats, "atomic sphere");
            }
        }
    }
    if (atoms == 0) return;
    MESSAGE("atomic sphere test: " << atoms << " atomics, " << pairs << " pairs (" << rigid << " with a rigid LTM checked): "
                                   << stats[2] << " reported, " << stats[0] << " clear hits, " << stats[1] << " borderline");
    CHECK(stats[0] > 0);
}

// The world walks on worlds built around a snapshot geometry: the live world record copied, its root either one sector
// holding the geometry's triangles, vertices and collision tree, or a plane whose left cell holds that sector (the
// plane beyond the geometry's box) and whose right cell is an empty sector. The line and sphere walks must report what
// the geometry walks report on the same data (sub_461EA0 / sub_462BB0), the box walk what the host's box test finds.
TEST_CASE("game(render_rw6): the world line / sphere / box walks on built worlds report what the geometry walks and the host find") {
    std::array<long, 3> box_stats{}, line_stats{}, sph_stats{};
    int worlds = 0, pairs = 0;
    for (const char* sn : {"dorm_replay_4900", "climb_ref_17000"}) {
        std::vector<u8> image;
        auto mp = snapshot_machine(sn, image);
        if (!mp) {
            MESSAGE("SKIP: snapshot " << sn << " not found");
            continue;
        }
        Machine& m = *mp;
        u32 live_world = 0, live_sector = 0;
        for (u32 c : live_entries(m, ld(m, kEngine + ld(m, kGpCameraModule)))) {
            const u32 w = ld(m, c + ld(m, kGpCamWorld) + 12);
            if (in_ram(w, 512)) live_world = w;
        }
        REQUIRE(live_world != 0);
        live_sector = ld(m, live_world + 28);
        REQUIRE(in_ram(live_sector, 256));
        std::mt19937 rng{0x52574C80u};
        for (u32 g : collision_geometries(m, 6)) {
            Geo geo;
            REQUIRE(read_geo(m, g, geo));
            const double sz = std::max(geo.size(), 1e-3);
            for (int k = 0; k < 4; ++k) {
                const bool split = k % 2 == 1;
                const u32 world = kData + 0x1000, sector = kData + 0x1400, empty = kData + 0x1600, plane = kData + 0x1800;
                auto build = [&] {
                    std::memcpy(m.at(world), m.at(live_world), 0x200);
                    std::memcpy(m.at(sector), m.at(live_sector), 0x100);
                    std::memcpy(m.at(empty), m.at(live_sector), 0x100);
                    for (u32 s : {sector, empty}) st(m, s, 0xFFFFFFFFu);
                    st(m, sector + 4, geo.tris), st(m, sector + 8, geo.verts), st16(m, sector + 132, static_cast<u16>(geo.ntri));
                    st(m, sector + ld(m, kGpCollSector), geo.coll);
                    st(m, empty + 4, 0), st(m, empty + 8, 0), st16(m, empty + 132, 0), st(m, empty + ld(m, kGpCollSector), 0);
                    if (split) {
                        const int axis = static_cast<int>(rng() % 3);
                        const float v = static_cast<float>(geo.hi[axis] + 0.01 * sz);
                        st(m, plane, 4u * static_cast<u32>(axis));
                        stf(m, plane + 4, v), stf(m, plane + 16, v), stf(m, plane + 20, v);
                        st(m, plane + 8, sector), st(m, plane + 12, empty);
                        st(m, world + 28, plane);
                    } else
                        st(m, world + 28, sector);
                };
                ++worlds;
                // --- the line walk against the geometry's tree walk
                D3 s, e;
                {
                    const D3 p = point_on(geo, rng), d = rand_dir(rng);
                    s = p - d * (sz * frand(rng, 0.05f, 0.5f));
                    e = p + d * (sz * frand(rng, 0.05f, 0.5f));
                }
                restore(m, image);
                build();
                const u32 isect = kData + 0x140, data = kData + 0x200;
                stv(m, isect, s.data()), stv(m, isect + 12, e.data()), st(m, isect + 24, 1);
                const WPair wl = wpair(m, by_name("sub_45F930"), {world, isect, kCallback, data}, 620000u + pairs, coll_world(m, 2));
                restore(m, image);
                stv(m, isect, s.data()), stv(m, isect + 12, e.data()), st(m, isect + 24, 1);
                HwCheck hw;
                hw.gpr_in = {{GPR_T0, data}};
                const WPair gl = wpair(m, by_name("sub_461EA0"), {g, isect, isect, kCallback}, 620001u + pairs, coll_world(m, 1), hw);
                pairs += 2;
                CHECK(!wl.run.stopped);
                {
                    INFO(sn << " geometry " << hex64(g) << " world line " << k << (split ? " (split)" : ""));
                    CHECK(sorted_indices(wl.hits) == sorted_indices(gl.hits));
                    auto cls = [&](u32 i) { return host_line(s, e, geo.v[geo.t[i][0]], geo.v[geo.t[i][1]], geo.v[geo.t[i][2]]); };
                    check_hits(wl.hits, geo.ntri, cls, line_stats, "world line");
                }
                // --- the sphere walk against the geometry's tree walk
                const D3 ctr = point_on(geo, rng);
                const double r = sz * frand(rng, 0.01f, 0.2f);
                restore(m, image);
                build();
                const u32 sph = kData + 0x100;
                stv(m, sph, ctr.data()), stf(m, sph + 12, static_cast<float>(r));
                std::memcpy(m.at(isect), m.at(sph), 16), st(m, isect + 24, 3);
                const WPair ws = wpair(m, by_name("sub_460EC0"), {world, sph, isect, kCallback}, 620002u + pairs, coll_world(m, 2), hw);
                restore(m, image);
                stv(m, sph, ctr.data()), stf(m, sph + 12, static_cast<float>(r));
                std::memcpy(m.at(isect), m.at(sph), 16), st(m, isect + 24, 3);
                const WPair gs = wpair(m, by_name("sub_462BB0"), {g, sph, isect, kCallback}, 620003u + pairs, coll_world(m, 1), hw);
                pairs += 2;
                CHECK(!ws.run.stopped);
                {
                    INFO(sn << " geometry " << hex64(g) << " world sphere " << k << (split ? " (split)" : ""));
                    CHECK(sorted_indices(ws.hits) == sorted_indices(gs.hits));
                    auto cls = [&](u32 i) { return host_sphere(ctr, r, geo.v[geo.t[i][0]], geo.v[geo.t[i][1]], geo.v[geo.t[i][2]]); };
                    check_hits(ws.hits, geo.ntri, cls, sph_stats, "world sphere");
                }
                // --- the box walk against the host's box test
                const D3 bc = point_on(geo, rng);
                D3 half;
                for (int i = 0; i < 3; ++i) half[i] = sz * frand(rng, 0.005f, 0.15f);
                const D3 sup = bc + half, inf = bc - half;
                restore(m, image);
                build();
                stv(m, isect, sup.data()), stv(m, isect + 12, inf.data()), st(m, isect + 24, 4);
                const WPair wb = wpair(m, by_name("sub_4606B0"), {world, isect, kCallback, data}, 620004u + pairs, coll_world(m, 2));
                ++pairs;
                CHECK(!wb.run.stopped);
                {
                    INFO(sn << " geometry " << hex64(g) << " world box " << k << (split ? " (split)" : ""));
                    auto cls = [&](u32 i) { return host_box(sup, inf, geo.v[geo.t[i][0]], geo.v[geo.t[i][1]], geo.v[geo.t[i][2]]); };
                    check_hits(wb.hits, geo.ntri, cls, box_stats, "world box");
                    for (const Hit& h : wb.hits) CHECK(h.dist == 0.0f);
                }
            }
        }
    }
    if (worlds == 0) return;
    MESSAGE("world walks: " << worlds << " built worlds, " << pairs << " pairs; lines " << line_stats[2] << " reported / "
                            << line_stats[0] << " clear hits; spheres " << sph_stats[2] << " / " << sph_stats[0] << "; boxes "
                            << box_stats[2] << " / " << box_stats[0] << " (" << box_stats[1] << " borderline)");
    CHECK(box_stats[0] > 0);
}

// The morph-target tests (sub_463490 line, sub_463B20 sphere) on a geometry built from a snapshot geometry with a second
// morph target (every vertex displaced); the interpolator {flags, start, end, time, recipTime, position}: the triangles
// must be the ones the host finds on the blended vertices (start + (end - start) x recipTime x position); with the start
// equal to the end, the same as the one-target tests.
TEST_CASE("game(render_rw6): the morph-target tests report the triangles of the blended vertices") {
    std::array<long, 3> stats{};
    int pairs = 0;
    std::vector<u8> image;
    auto mp = snapshot_machine("dorm_replay_4900", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot dorm_replay_4900 not found");
        return;
    }
    Machine& m = *mp;
    std::mt19937 rng{0x52574CC0u};
    for (u32 g0 : collision_geometries(m, 8)) {
        Geo geo;
        REQUIRE(read_geo(m, g0, geo));
        if (geo.nverts > 8000) continue;
        const double sz = std::max(geo.size(), 1e-3);
        // the displaced copy of the vertices (kept as floats the way the guest holds them)
        const D3 shift = rand_dir(rng) * (sz * 0.05);
        std::vector<D3> v1(geo.nverts);
        for (u32 i = 0; i < geo.nverts; ++i) {
            const D3 n = rand_dir(rng) * (sz * 0.01);
            for (int j = 0; j < 3; ++j) v1[i][j] = static_cast<float>(geo.v[i][j] + shift[j] + n[j]);
        }
        for (int k = 0; k < 4; ++k) {
            const bool same = k == 3;
            const float pos = same ? 0.0f : frand(rng, 0.0f, 1.0f);
            const u32 g = kData + 0x1000, morphs = kData + 0x1100, interp = kData + 0x1200, verts1 = kData + 0x10000;
            auto build = [&] {
                std::memcpy(m.at(g), m.at(g0), 0x80);
                st(m, g + 24, 2), st(m, g + 92, morphs);
                std::memcpy(m.at(morphs), m.at(ld(m, g0 + 92)), 28);
                std::memcpy(m.at(morphs + 28), m.at(ld(m, g0 + 92)), 28);
                st(m, morphs + 28 + 20, verts1);
                for (u32 i = 0; i < geo.nverts; ++i) stv(m, verts1 + 12 * i, v1[i].data());
                st(m, interp, 0), st16(m, interp + 4, 0), st16(m, interp + 6, same ? 0 : 1);
                stf(m, interp + 8, 0.0f), stf(m, interp + 12, 1.0f), stf(m, interp + 16, pos);
            };
            auto blended = [&](u32 vi) {
                if (same) return geo.v[vi];
                const float f = 1.0f * pos;
                D3 o;
                for (int j = 0; j < 3; ++j) {
                    const float a = static_cast<float>(geo.v[vi][j]), b = static_cast<float>(v1[vi][j]);
                    o[j] = (b - a) * f + a;
                }
                return o;
            };
            const D3 p = point_on(geo, rng), d = rand_dir(rng);
            const D3 s = p - d * (sz * frand(rng, 0.05f, 0.5f)), e = p + d * (sz * frand(rng, 0.05f, 0.5f));
            restore(m, image);
            build();
            const u32 line = kData + 0x100, isect = kData + 0x140, data = kData + 0x200;
            stv(m, line, s.data()), stv(m, line + 12, e.data());
            HwCheck hw;
            hw.gpr_in = {{GPR_T0, kCallback}, {GPR_T1, data}};
            const WPair ml = wpair(m, by_name("sub_463490"), {g, interp, line, isect}, 630000u + pairs, coll_world(m, 1), hw);
            ++pairs;
            CHECK(!ml.run.stopped);
            {
                INFO("geometry " << hex64(g0) << " morph line " << k << " position " << pos);
                auto cls = [&](u32 i) { return host_line(s, e, blended(geo.t[i][0]), blended(geo.t[i][1]), blended(geo.t[i][2])); };
                check_hits(ml.hits, geo.ntri, cls, stats, "morph line");
            }
            if (same) {
                restore(m, image);
                stv(m, line, s.data()), stv(m, line + 12, e.data());
                HwCheck h1;
                h1.gpr_in = {{GPR_T0, data}};
                const WPair one = wpair(m, by_name("sub_461900"), {g0, line, isect, kCallback}, 630100u + pairs, coll_world(m, 1), h1);
                CHECK(sorted_indices(one.hits) == sorted_indices(ml.hits));
            }
            const D3 ctr = point_on(geo, rng);
            const double r = sz * frand(rng, 0.01f, 0.2f);
            restore(m, image);
            build();
            const u32 sph = kData + 0x100;
            stv(m, sph, ctr.data()), stf(m, sph + 12, static_cast<float>(r));
            const WPair msph = wpair(m, by_name("sub_463B20"), {g, interp, sph, isect}, 630200u + pairs, coll_world(m, 1), hw);
            ++pairs;
            CHECK(!msph.run.stopped);
            {
                INFO("geometry " << hex64(g0) << " morph sphere " << k << " position " << pos);
                auto cls = [&](u32 i) { return host_sphere(ctr, r, blended(geo.t[i][0]), blended(geo.t[i][1]), blended(geo.t[i][2])); };
                check_hits(msph.hits, geo.ntri, cls, stats, "morph sphere");
            }
        }
    }
    MESSAGE("morph-target tests: " << pairs << " pairs, " << stats[2] << " reported, " << stats[0] << " clear hits, " << stats[1]
                                   << " borderline");
    CHECK(stats[0] > 0);
}

// The two triangle tests against the host on random triangles: sphere / triangle (sub_4BAE00: 1 when the triangle
// reaches into the sphere; on a hit the unit face normal and the negated plane distance of the centre) and box /
// triangle (sub_4BB5D0: the separating-axis overlap).
TEST_CASE("game(render_rw6): the sphere / triangle and box / triangle tests agree with the host") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    std::mt19937 rng{0x52574D00u};
    int sph_hit = 0, sph_miss = 0, box_hit = 0, box_miss = 0, pairs = 0;
    const u32 S = kData + 0x100, V = kData + 0x140, N = kData + 0x180, Dd = kData + 0x190;
    for (int k = 0; k < 600; ++k) {
        D3 v[3];
        for (D3& x : v)
            for (double& c : x) c = frand(rng, -10, 10);
        if (k % 7 == 0) v[2] = v[0] + (v[1] - v[0]) * 0.5;  // now and then a degenerate triangle
        const D3 ctr{frand(rng, -12, 12), frand(rng, -12, 12), frand(rng, -12, 12)};
        const double r = frand(rng, 0.1f, 8.0f);
        std::memset(m->at(kData), 0, 0x400);
        stv(*m, S, ctr.data()), stf(*m, S + 12, static_cast<float>(r));
        for (int i = 0; i < 3; ++i) stv(*m, V + 12 * i, v[i].data());
        HwCheck hw;
        hw.gpr_in = {{GPR_T0, N}, {GPR_T1, Dd}};
        const auto run = hgp::pair(*m, by_name("sub_4BAE00").hand, by_name("sub_4BAE00").recomp, {S, V, V + 12, V + 24}, 640000u + k,
                                   "sub_4BAE00", hw);
        ++pairs;
        const u32 got = static_cast<u32>(run.end.gpr[GPR_V0].u64[0]);
        const D3 fa = rdv(*m, V), fb = rdv(*m, V + 12), fc = rdv(*m, V + 24), fctr = rdv(*m, S);
        const int want = host_sphere(fctr, ldf(*m, S + 12), fa, fb, fc);
        INFO("sphere / triangle " << k << " want " << want << " got " << got);
        if (want != kUnsure) CHECK(got == static_cast<u32>(want));
        if (got == 1) {
            ++sph_hit;
            const D3 n = rdv(*m, N);
            const D3 fn = cross(fb - fa, fc - fa);
            const double ext = std::max({len(fb - fa), len(fc - fa), len(fc - fb)});
            if (len(fn) > 1e-3 * ext * ext) {  // (a degenerate triangle can pass on a vertex inside the sphere)
                CHECK(std::fabs(len(n) - 1) < 1e-4);
                CHECK(std::fabs(dot(n, fn)) > 0.999 * len(fn));
                CHECK(std::fabs(ldf(*m, Dd) - dot(fctr - fa, n)) < 1e-3 * (1 + r));
            }
        } else
            ++sph_miss;
        // the box
        D3 sup, inf;
        for (int i = 0; i < 3; ++i) {
            const double c = frand(rng, -12, 12), h = frand(rng, 0.1f, 6.0f);
            sup[i] = c + h, inf[i] = c - h;
        }
        stv(*m, S, sup.data()), stv(*m, S + 12, inf.data());
        const auto br = hgp::pair(*m, by_name("sub_4BB5D0").hand, by_name("sub_4BB5D0").recomp, {S, V, V + 12, V + 24}, 650000u + k,
                                  "sub_4BB5D0");
        ++pairs;
        const u32 bgot = static_cast<u32>(br.end.gpr[GPR_V0].u64[0]);
        const int bwant = host_box(rdv(*m, S), rdv(*m, S + 12), fa, fb, fc);
        INFO("box / triangle " << k << " want " << bwant << " got " << bgot);
        if (bwant != kUnsure) CHECK(bgot == static_cast<u32>(bwant));
        (bgot == 1 ? box_hit : box_miss)++;
    }
    MESSAGE("triangle tests: " << pairs << " pairs; sphere " << sph_hit << " hits / " << sph_miss << " misses, box " << box_hit
                               << " hits / " << box_miss << " misses");
    CHECK(sph_hit > 50);
    CHECK(box_hit > 50);
}

// =====================================================================================================================
// sList, error, engine
// =====================================================================================================================
// sLists in the test area with their data in the stand-in heap: n new entries at the end (growth by n + a quarter of the
// capacity when they do not fit, through RwRealloc, the old entries kept), the drop, the end pointer, the data getter,
// destroy (RwFree of the data when there is a capacity, then of the record), to-array (the data back, the record freed).
TEST_CASE("game(render_rw6): the sList helpers follow the sList rules") {
    std::vector<u8> image;
    auto mp = snapshot_machine("b_5800", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot b_5800 not found");
        return;
    }
    Machine& m = *mp;
    std::mt19937 rng{0x52574D40u};
    int checks = 0;
    for (int k = 0; k < 48; ++k) {
        const u32 es = std::vector<u32>{4, 8, 12, 16, 24, 60}[rng() % 6];
        const u32 cap = rng() % 12, cnt = cap ? rng() % (cap + 1) : 0;
        const u32 n = 1 + rng() % 6;
        const u32 rec = kData + 0x100;
        u32 data = 0;
        auto setup = [&](StandInWorld& w) {
            install_standard(w);
            data = cap ? w.heap.alloc(cap * es) : 0;
            st(m, rec, data), st(m, rec + 4, cnt), st(m, rec + 8, cap), st(m, rec + 12, es);
            for (u32 i = 0; i < cap * es; i += 4) st(m, data + i, 0xA5000000u + i);
        };
        restore(m, image);
        const WPair g = wpair(m, by_name("sub_4C1F70"), {rec, n, 0x30190, 0}, 660000u + k, setup);
        const bool grow = cnt + n >= cap;
        const u32 ncap = grow ? cap + cap / 4 + n : cap;
        CHECK(ld(m, rec + 4) == cnt + n);
        CHECK(ld(m, rec + 8) == ncap);
        CHECK(g.recomp->si.calls_to(0x103F50u) == (grow ? 1u : 0u));
        const u32 nd = ld(m, rec);
        CHECK(g.v0() == nd + cnt * es);
        for (u32 i = 0; i < cnt * es; i += 4) CHECK(ld(m, nd + i) == 0xA5000000u + i);
        // the end, the data, the drop
        CHECK(wpair(m, by_name("sub_4C21E0"), {rec, 0, 0, 0}, 661000u + k, install_standard).v0() == nd + (cnt + n) * es);
        CHECK(wpair(m, by_name("name__C9type_info_1"), {rec, 0, 0, 0}, 662000u + k, install_standard).v0() == nd);
        wpair(m, by_name("sub_4C2080"), {rec, n, 0, 0}, 663000u + k, install_standard);
        CHECK(ld(m, rec + 4) == cnt);
        // destroy / to-array on the original record
        restore(m, image);
        const WPair d = wpair(m, by_name("sub_4C20B0"), {rec, 0, 0, 0}, 664000u + k, setup);
        CHECK(d.v0() == 1);
        CHECK(d.recomp->si.calls_to(0x104280u) == (data && cap ? 2u : 1u));
        restore(m, image);
        const WPair t = wpair(m, by_name("sub_4C2130"), {rec, 0, 0, 0}, 665000u + k, setup);
        CHECK(t.v0() == (cnt ? data : 0u));
        CHECK(t.recomp->si.calls_to(0x104280u) == (cnt == 0 && data ? 2u : 1u));
        ++checks;
    }
    MESSAGE("sList rules: " << checks << " lists");
}

// The error module (RwErrorGet copies the last error and clears it), the engine's plugin offsets against its registry
// (every registered engine plugin; an unknown id -1), the version, and the device requests: the standard answers of a
// declining device for requests 13..18, the video-mode queries through the device's system function.
TEST_CASE("game(render_rw6): the error get, the engine plugin offsets, the version and the device requests") {
    std::vector<u8> image;
    auto mp = snapshot_machine("dorm_replay_4900", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot dorm_replay_4900 not found");
        return;
    }
    Machine& m = *mp;
    restore(m, image);
    const u32 err = kEngine + ld(m, kGpErrorModule);
    st(m, err, 0x11D), st(m, err + 4, 0x80000013u);
    const WPair g = wpair(m, by_name("sub_4C1CD0"), {kData + 0x100, 0, 0, 0}, 670000u, install_standard);
    CHECK(g.v0() == kData + 0x100);
    CHECK(ld(m, kData + 0x100) == 0x11Du);
    CHECK(ld(m, kData + 0x104) == 0x80000013u);
    CHECK(ld(m, err) == 0u);
    CHECK(ld(m, err + 4) == 0x80000000u);
    // the plugin offsets
    int plugins = 0;
    for (u32 e = ld(m, kEngineRegistry + 16), n = 0; in_ram(e, 56) && n < 64; e = ld(m, e + 48), ++n) {
        const u32 id = ld(m, e + 8);
        u32 want = 0xFFFFFFFFu;  // the first entry with that id
        for (u32 f = ld(m, kEngineRegistry + 16); in_ram(f, 56); f = ld(m, f + 48))
            if (ld(m, f + 8) == id) {
                want = ld(m, f);
                break;
            }
        CHECK(wpair(m, by_name("sub_4CA550"), {id, 0, 0, 0}, 671000u + n, install_standard).v0() == want);
        ++plugins;
    }
    CHECK(plugins > 10);
    CHECK(wpair(m, by_name("sub_4CA550"), {0x7777, 0, 0, 0}, 671900u, install_standard).v0() == 0xFFFFFFFFu);
    CHECK(wpair(m, by_name("sub_4CA510"), {0, 0, 0, 0}, 672000u, install_standard).v0() == 0x37002u);
    // the device's standard answers: a device whose system function declines (or accepts) everything
    for (u32 accept : {0u, 1u})
        for (u32 req = 0; req < 20; ++req)
            for (u32 num : {0u, 1u}) {
                restore(m, image);
                const u32 dev = kData + 0x100, out = kData + 0x140;
                st(m, dev + 4, kCallback);
                st(m, out, 0xDEADBEEFu);
                auto setup = [accept](StandInWorld& w) {
                    install_standard(w);
                    w.si.install_recorder(kCallback, "device system function", accept);
                };
                const WPair p = wpair(m, by_name("_rwDeviceSystemRequest"), {dev, req, out, 0}, 673000u + req * 4 + num * 2 + accept,
                                      setup, HwCheck{{}, {}, {}, {{GPR_T0, num}}});
                INFO("request " << req << " number " << num << " accept " << accept);
                if (accept) {
                    CHECK(p.v0() == 1);
                    CHECK(ld(m, out) == 0xDEADBEEFu);
                    continue;
                }
                const bool std_ok = req == 13 || req == 15 || req == 17 || req == 18 || ((req == 14 || req == 16) && num == 0);
                CHECK(p.v0() == (std_ok ? 1u : 0u));
                if (req == 13) CHECK(ld(m, out) == 1u);
                if (req == 15) CHECK(ld(m, out) == 0u);
                if (req == 14 && num == 0) CHECK(lds(m, out) == "Only rendering sub system");
            }
    // the video-mode queries through the engine's device (its system function stood in)
    for (u32 ok : {0u, 1u}) {
        restore(m, image);
        st(m, 0x960084u, kCallback);
        auto setup = [ok, &m](StandInWorld& w) {
            install_standard(w);
            w.si.install(kCallback, "device system function", [ok, &m](EEContext&, StandIns&, StandInCall& c) {
                if (ok && c.args[0] == 10) st(m, static_cast<u32>(c.args[1]), 3);
                c.v0 = ok;
            });
        };
        CHECK(wpair(m, by_name("sub_4CA5B0"), {0, 0, 0, 0}, 674000u + ok, setup).v0() == (ok ? 3u : 0xFFFFFFFFu));
        CHECK(wpair(m, by_name("sub_4CA560"), {kData + 0x100, 2, 0, 0}, 674100u + ok, setup).v0() == (ok ? kData + 0x100 : 0u));
        CHECK(wpair(m, by_name("RwEngineSetVideoMode"), {2, 0, 0, 0}, 674200u + ok, setup).v0() == ok);
    }
    MESSAGE("engine: " << plugins << " engine plugins looked up");
}

// =====================================================================================================================
// PS2AllMat
// =====================================================================================================================
// A pipeline node with private data in the test area: the five callbacks (types 2..4 refuse 0, another type fails), the
// VU1 code array (0: the default array 0x77F130 of 32), the VIF offset; the batch set-ups create the 64-byte
// initialisation data on first use (RwMalloc) and refuse a second primitive kind.
TEST_CASE("game(render_rw6): the PS2AllMat node set-up stores what it is given") {
    std::vector<u8> image;
    auto mp = snapshot_machine("b_5800", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot b_5800 not found");
        return;
    }
    Machine& m = *mp;
    const u32 node = kData + 0x100, priv = kData + 0x180;
    auto fresh = [&] {
        restore(m, image);
        st(m, node + 20, priv);
    };
    for (u32 type = 0; type <= 6; ++type)
        for (u32 f : {0u, 0x123450u}) {
            fresh();
            const WPair p = wpair(m, by_name("sub_4A3E30"), {node, type, f, 0}, 680000u + type * 2 + (f != 0), install_standard);
            const bool ok = type >= 1 && type <= 5 && (f != 0 || type == 1 || type == 5);
            INFO("callback type " << type << " fn " << f);
            CHECK(p.v0() == (ok ? node : 0u));
            if (ok) CHECK(ld(m, priv + 4 * (type - 1)) == f);
        }
    fresh();
    CHECK(wpair(m, by_name("RxPipelineNodePS2AllMatSetVU1CodeArray"), {node, 0, 0, 0}, 681000u, install_standard).v0() == node);
    CHECK(ld(m, priv + 24) == 0x77F130u);
    CHECK(ld(m, priv + 28) == 32u);
    CHECK(wpair(m, by_name("RxPipelineNodePS2AllMatSetVU1CodeArray"), {node, 0x5000, 7, 0}, 681001u, install_standard).v0() == node);
    CHECK(ld(m, priv + 24) == 0x5000u);
    CHECK(ld(m, priv + 28) == 7u);
    CHECK(wpair(m, by_name("RxPipelineNodePS2AllMatSetVU1CodeArray"), {node, 0x5000, 0, 0}, 681002u, install_standard).v0() == 0u);
    CHECK(wpair(m, by_name("sub_4A3D70"), {node, 0x40, 0, 0}, 681003u, install_standard).v0() == node);
    CHECK(ld(m, priv + 20) == 0x40u);
    CHECK(wpair(m, by_name("sub_4A3D70"), {0, 0x40, 0, 0}, 681004u, install_standard).v0() == 0u);
    // the batches: first use creates the initialisation data
    std::mt19937 rng{0x52574D80u};
    for (int k = 0; k < 24; ++k) {
        fresh();
        const u32 stride = 1 + rng() % 8, verts = 3 + rng() % 60, tris = 1 + rng() % 30;
        const int kind = static_cast<int>(rng() % 3);
        const char* fn = kind == 0 ? "sub_4A38F0" : kind == 1 ? "sub_4A3A80" : "sub_4A3C10";
        const WPair p = wpair(m, by_name(fn), {node, stride, verts, tris}, 682000u + k, install_standard);
        INFO(fn << " stride " << stride << " vertices " << verts << " count " << tris);
        CHECK(p.v0() == node);
        const u32 init = ld(m, node + 32);
        REQUIRE(in_ram(init, 64));
        CHECK(ld(m, node + 36) == 64u);
        CHECK(ld(m, init + 56) == stride);
        CHECK(ld(m, init + 60) == (kind == 0 ? 3u : kind == 1 ? 12u : 16u));
        const u32 want52 = kind == 0 ? stride * 3 * tris : kind == 1 ? stride * 2 * tris : stride * verts;
        const u32 want48 = kind == 2 ? 69u * 4u : verts * stride;
        CHECK(ld(m, init + 52) == want52);
        CHECK(ld(m, init + 48) == want48);
        // another kind on the same node is refused, the same kind accepted
        const char* other = kind == 0 ? "sub_4A3A80" : "sub_4A38F0";
        CHECK(wpair(m, by_name(other), {node, stride, verts, tris}, 683000u + k, install_standard).v0() == 0u);
        CHECK(wpair(m, by_name(fn), {node, stride, verts, tris}, 684000u + k, install_standard).v0() == node);
    }
    fresh();
    CHECK(wpair(m, by_name("sub_4A38F0"), {node, 4, 2, 5}, 685000u, install_standard).v0() == 0u);  // fewer than 3 vertices
}

// =====================================================================================================================
// RtFS
// =====================================================================================================================
// The snapshots' three registered file systems (hdd, pak, hst): the lookup by name (strcmp), the name check, the device
// lookup (case-insensitive, the compare stood in), the device prefix skip; the stream adaptors through a file's file
// system (read / write: size x count bytes, the result / size; seek: whence 0 / 1 / 2 -> mode 1 / 2 / 3; eof); the
// generic file system's creation and registration.
TEST_CASE("game(render_rw6): the RtFS lookups, adaptors and the generic file system") {
    std::vector<u8> image;
    auto mp = snapshot_machine("dorm_replay_4900", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot dorm_replay_4900 not found");
        return;
    }
    Machine& m = *mp;
    restore(m, image);
    std::map<std::string, u32> fs;
    for (u32 f = ld(m, 0x95FF10u); in_ram(f, 100); f = ld(m, f)) fs[lds(m, f + 80)] = f;
    REQUIRE(fs.size() == 3u);
    auto world = [&m](StandInWorld& w) {
        install_standard(w);
        w.si.install(kStrICmp, "stricmp", [&m](EEContext&, StandIns&, StandInCall& c) {
            std::string a = lds(m, static_cast<u32>(c.args[0])), b = lds(m, static_cast<u32>(c.args[1]));
            for (auto& ch : a) ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            for (auto& ch : b) ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
            c.v0 = a == b ? 0 : 1;
        });
        w.si.install(kCallback, "file operation", [](EEContext&, StandIns&, StandInCall& c) { c.v0 = c.args[2] / 2; });
    };
    u32 seed = 690000u;
    const u32 str = kData + 0x100;
    for (const char* q : {"hdd", "pak", "hst", "xyz", "PAK"}) {
        restore(m, image);
        sts(m, str, q);
        const u32 want = fs.count(q) ? fs[q] : 0u;
        CHECK(wpair(m, by_name("sub_4BFD50"), {str, 0, 0, 0}, seed++, world).v0() == want);
        CHECK(wpair(m, by_name("sub_4BFDE0"), {str, 0, 0, 0}, seed++, world).v0() == (want ? 1u : 0u));
    }
    for (const char* q : {"PAK:", "hdd:", "Hst:", "cd0:"}) {
        restore(m, image);
        sts(m, str, q);
        std::string low = q;
        for (auto& ch : low) ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        const u32 want = fs.count(low.substr(0, 3)) ? fs[low.substr(0, 3)] : 0u;
        INFO("device " << q);
        CHECK(wpair(m, by_name("sub_4C0070"), {str, 0, 0, 0}, seed++, world).v0() == want);
    }
    for (const char* q : {"hdd:data/file.bin", "nodevice", "a:b:c"}) {
        restore(m, image);
        sts(m, str, q);
        const char* colon = std::strchr(q, ':');
        CHECK(wpair(m, by_name("sub_4BF7E0"), {str, 0, 0, 0}, seed++, world).v0() == str + (colon ? static_cast<u32>(colon - q) + 1 : 0u));
    }
    // the adaptors on a file whose file system's operations are stood in (the stand-in returns half the byte count)
    const u32 file = kData + 0x200, ops = kData + 0x300, buf = kData + 0x400;
    auto files = [&] {
        restore(m, image);
        st(m, file + 80, ops);
        for (u32 o : {48u, 52u, 56u, 68u}) st(m, ops + o, kCallback);
    };
    files();
    CHECK(wpair(m, by_name("sub_4C03D0"), {buf, 4, 10, file}, seed++, world).v0() == 5u);  // (4 x 10) / 2 / 4
    files();
    CHECK(wpair(m, by_name("sub_4C0420"), {buf, 2, 7, file}, seed++, world).v0() == 3u);   // (2 x 7) / 2 / 2
    for (u32 whence = 0; whence < 4; ++whence) {
        files();
        const WPair p = wpair(m, by_name("sub_4C0470"), {file, 100, whence, 0}, seed++, world);
        CHECK(p.v0() == (whence < 3 ? 0u : 0xFFFFFFFFu));
        CHECK(p.recomp->si.calls_to(kCallback) == (whence < 3 ? 1u : 0u));
        if (whence < 3) CHECK(p.recomp->si.log.back().args[3] == whence + 1);
    }
    files();
    st(m, file + 48, 1);
    wpair(m, by_name("sub_4C0470"), {file, 0, 0, 0}, seed++, world);
    CHECK(ld(m, file + 64) == 4u);
    CHECK(ld(m, file + 56) == 3u);
    // eof: position -1 or past the length
    for (const auto& [pos, length] : std::vector<std::pair<long long, long long>>{{-1, 10}, {5, 10}, {10, 10}, {12, 10}}) {
        files();
        std::memcpy(m.at(file), &length, 8), std::memcpy(m.at(file + 16), &pos, 8);
        CHECK(wpair(m, by_name("sub_4BF9E0"), {file, 0, 0, 0}, seed++, world).v0() == ((pos == -1 || pos >= length) ? 1u : 0u));
    }
    // the generic file system: created (not registered), then registered
    restore(m, image);
    const u32 area = kData + 0x1000, name = kData + 0x100, dev = kData + 0x120;
    sts(m, name, "tst"), sts(m, dev, "tst:");
    HwCheck hw;
    hw.gpr_in = {{GPR_T0, name}};
    const WPair c = wpair(m, by_name("sub_4C0FD0"), {3, area, 0x200, dev}, seed++, world, hw);
    const u32 rec = c.v0();
    REQUIRE(in_ram(rec, 92));
    CHECK(ld(m, rec + 20) == 0x4C0830u);
    CHECK(ld(m, rec + 4) == 3u);
    CHECK(ld(m, rec + 8) == 2u);
    CHECK(lds(m, rec + 80) == "tst");
    CHECK(lds(m, ld(m, rec + 12)) == "tst:");
    const u32 arr = ld(m, rec + 88);
    for (u32 i = 0; i < 3; ++i) {
        CHECK(ld(m, arr + 112 * i + 80) == rec);
        CHECK(ld(m, arr + 112 * i + 104) == area + 0x200 * i);
        CHECK(ld(m, arr + 112 * i + 108) == 0x200u);
        CHECK(ld(m, arr + 112 * i + 56) == 1u);
    }
    CHECK(ld(m, 0x95FF10u) == fs["hdd"]);  // not registered by the creation
    const u32 count = ld(m, 0x95FF18u);
    CHECK(wpair(m, by_name("sub_4BFC80"), {rec, 0, 0, 0}, seed++, world).v0() == 1u);
    CHECK(ld(m, 0x95FF10u) == rec);
    CHECK(ld(m, rec) == fs["hdd"]);
    CHECK(ld(m, 0x95FF18u) == count + 1);
    // the same name again: created 0
    sts(m, name, "pak");
    CHECK(wpair(m, by_name("sub_4C0FD0"), {3, area, 0x200, dev}, seed++, world, hw).v0() == 0u);
}

// =====================================================================================================================
// Rt2d
// =====================================================================================================================
// Paths built in the test area (the segment sList in the stand-in heap): Rt2dPathLineto appends a type-1 segment with
// the unit normal (dy, -dx) / length of the new edge and the running length, and turns the previous point's normal into
// the mitre (n0 + n1) / (n0 . (n0 + n1)) once the sub-path has two points; Rt2dPathCurveto appends three type-2
// points (the first with the mitre) and clears the sub-path's flat flag; the even-odd point-inside test on random
// polygons; the polygon corner side and the point-in-triangle classification against the host; Rt2dCTMTranslate /
// Rt2dCTMScale on the live CTM.
TEST_CASE("game(render_rw6): the Rt2d path segments, point-inside test, polygon classifications and CTM") {
    std::vector<u8> image;
    auto mp = snapshot_machine("b_5800", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot b_5800 not found");
        return;
    }
    Machine& m = *mp;
    std::mt19937 rng{0x52574DC0u};
    const u32 path = kData + 0x100, sl = kData + 0x140;
    struct Seg {
        u32 type;
        float x, y, nx, ny, d;
    };
    for (int k = 0; k < 24; ++k) {
        const u32 n0 = 1 + rng() % 4;  // points already in the sub-path
        std::vector<Seg> segs;
        for (u32 i = 0; i < n0; ++i) segs.push_back({i ? 1u : 0u, frand(rng, -50, 50), frand(rng, -50, 50), frand(rng, -1, 1), frand(rng, -1, 1), frand(rng, 0, 100)});
        const u32 cap = n0 + static_cast<u32>(rng() % 3);
        auto setup = [&](StandInWorld& w) {
            install_standard(w);
            const u32 data = w.heap.alloc(24 * cap);
            st(m, sl, data), st(m, sl + 4, n0), st(m, sl + 8, cap), st(m, sl + 12, 24);
            for (u32 i = 0; i < n0; ++i) {
                const Seg& s = segs[i];
                st(m, data + 24 * i, s.type), stf(m, data + 24 * i + 4, s.x), stf(m, data + 24 * i + 8, s.y);
                stf(m, data + 24 * i + 12, s.nx), stf(m, data + 24 * i + 16, s.ny), stf(m, data + 24 * i + 20, s.d);
            }
            st(m, path, sl), st(m, path + 4, 0xFFFFFFFFu), st(m, path + 8, 0), st(m, path + 12, 1), st(m, path + 20, 0), st(m, path + 24, path);
        };
        const bool curve = k % 3 == 2;
        float px[3], py[3];
        for (int i = 0; i < 3; ++i) px[i] = frand(rng, -50, 50), py[i] = frand(rng, -50, 50);
        restore(m, image);
        if (curve) {
            for (int i = 0; i < 3; ++i) g_fpr[12 + 2 * i] = px[i], g_fpr[13 + 2 * i] = py[i];
        } else
            g_fpr[12] = px[0], g_fpr[13] = py[0];
        const WPair p = wpair(m, by_name(curve ? "sub_4AB410" : "sub_4AB2C0"), {path, 0, 0, 0}, 700000u + k, setup);
        CHECK(p.v0() == path);
        const u32 data = ld(m, sl);
        const u32 added = curve ? 3u : 1u;
        CHECK(ld(m, sl + 4) == n0 + added);
        Seg prev = segs.back();
        for (u32 i = 0; i < added; ++i) {
            const u32 at = data + 24 * (n0 + i);
            const double dx = px[i] - prev.x, dy = py[i] - prev.y, l = std::sqrt(dx * dx + dy * dy);
            const double nx = dy / l, ny = -dx / l;
            INFO((curve ? "curve" : "line") << " " << k << " point " << i);
            CHECK(ld(m, at) == (curve ? 2u : 1u));
            CHECK(ldf(m, at + 4) == px[i]);
            CHECK(ldf(m, at + 8) == py[i]);
            CHECK(std::fabs(ldf(m, at + 12) - nx) < 1e-4);
            CHECK(std::fabs(ldf(m, at + 16) - ny) < 1e-4);
            CHECK(std::fabs(ldf(m, at + 20) - (prev.d + l)) < 1e-3 * (1 + prev.d + l));
            if (i == 0) {
                const u32 pa = data + 24 * (n0 - 1);
                double mx = nx, my = ny;
                if (n0 >= 2) {
                    const double sx = prev.nx + nx, sy = prev.ny + ny, dd = prev.nx * sx + prev.ny * sy;
                    mx = sx / dd, my = sy / dd;
                }
                if (std::fabs(mx) < 1e3 && std::fabs(my) < 1e3) {
                    CHECK(std::fabs(ldf(m, pa + 12) - mx) < 1e-3 * (1 + std::fabs(mx)));
                    CHECK(std::fabs(ldf(m, pa + 16) - my) < 1e-3 * (1 + std::fabs(my)));
                }
            }
            prev = {0, px[i], py[i], static_cast<float>(nx), static_cast<float>(ny), ldf(m, at + 20)};
        }
        if (curve) CHECK(ld(m, path + 12) == 0u);
    }
    // the point-inside test: random polygons (closed: the first point repeated), points away from every edge
    int inside = 0, outside = 0;
    for (int k = 0; k < 40; ++k) {
        const u32 np = 3 + rng() % 7;
        std::vector<std::array<float, 2>> pts;
        for (u32 i = 0; i < np; ++i) {
            const double a = 6.2831853 * i / np + frand(rng, -0.3f, 0.3f), r = frand(rng, 5, 40);
            pts.push_back({static_cast<float>(r * std::cos(a)), static_cast<float>(r * std::sin(a))});
        }
        if (k % 4 == 0) std::swap(pts[0], pts[np / 2]);  // a self-intersecting one now and then
        pts.push_back(pts[0]);
        const float qx = frand(rng, -45, 45), qy = frand(rng, -45, 45);
        // the host's even-odd count with the bodies' rule (y in (min, max], crossing right of the point)
        int cross = 0;
        bool near = false;
        for (u32 i = 0; i + 1 < pts.size(); ++i) {
            const double x0 = pts[i][0], y0 = pts[i][1], x1 = pts[i + 1][0], y1 = pts[i + 1][1];
            if (std::fabs(qy - y0) < 1e-3 || std::fabs(qy - y1) < 1e-3) near = true;
            if (qy > std::min(y0, y1) && qy <= std::max(y0, y1) && y0 != y1) {
                const double xc = x0 + (qy - y0) * (x1 - x0) / (y1 - y0);
                if (std::fabs(qx - xc) < 1e-3) near = true;
                if (qx <= xc) ++cross;
            }
        }
        if (near) continue;
        restore(m, image);
        const u32 pt = kData + 0x100, ppath = kData + 0x140, psl = kData + 0x180;
        const bool own_count = chance(rng, 50);
        auto setup = [&](StandInWorld& w) {
            install_standard(w);
            const u32 data = w.heap.alloc(24 * static_cast<u32>(pts.size()));
            for (u32 i = 0; i < pts.size(); ++i) st(m, data + 24 * i, 1), stf(m, data + 24 * i + 4, pts[i][0]), stf(m, data + 24 * i + 8, pts[i][1]);
            st(m, psl, data), st(m, psl + 4, static_cast<u32>(pts.size())), st(m, psl + 8, static_cast<u32>(pts.size())), st(m, psl + 12, 24);
            st(m, ppath, psl), st(m, ppath + 4, own_count ? static_cast<u32>(pts.size()) : 0xFFFFFFFFu);
            stf(m, pt, qx), stf(m, pt + 4, qy);
        };
        const WPair p = wpair(m, by_name(k % 2 ? "sub_4ACE60" : "sub_4ACCC0"), {pt, ppath, 0, 0}, 710000u + k, setup);
        INFO("polygon " << k << " point " << qx << ", " << qy);
        CHECK(p.v0() == static_cast<u32>(cross & 1));
        (cross & 1 ? inside : outside)++;
    }
    CHECK(inside > 0);
    CHECK(outside > 0);
    // the polygon classifications
    for (int k = 0; k < 40; ++k) {
        restore(m, image);
        const u32 poly = kData + 0x100, P = kData + 0x200, vr = kData + 0x300;
        double x[4], y[4];
        for (int i = 0; i < 4; ++i) {
            x[i] = frand(rng, -20, 20), y[i] = frand(rng, -20, 20);
            stf(m, P + 8 * i, static_cast<float>(x[i])), stf(m, P + 8 * i + 4, static_cast<float>(y[i]));
            st(m, vr + 8 * i + 4, static_cast<u32>(i));
            x[i] = ldf(m, P + 8 * i), y[i] = ldf(m, P + 8 * i + 4);
        }
        st(m, poly + 16, P);
        auto side = [&](int a, int b, int c) {
            const double n0 = y[c] - y[b], n1 = x[b] - x[c], l = std::sqrt(n0 * n0 + n1 * n1);
            const double s = ((y[b] - y[a]) * n1 + (x[b] - x[a]) * n0) / l;
            return std::fabs(s) < 1e-3 ? 0 : s > 0 ? 1 : 2;
        };
        const WPair p = wpair(m, by_name("sub_4B0430"), {poly, vr, vr + 8, vr + 16}, 720000u + k, install_standard);
        const int want = side(0, 1, 2);
        if (want) CHECK(p.v0() == static_cast<u32>(want));
        HwCheck h4;
        h4.gpr_in = {{GPR_T0, vr + 16}};
        const WPair t = wpair(m, by_name("sub_4B0560"), {poly, vr + 24, vr, vr + 8}, 721000u + k, install_standard, h4);
        const int s1 = side(3, 0, 1), s2 = side(3, 1, 2), s3 = side(3, 2, 0);
        if (s1 && s2 && s3) CHECK(t.v0() == ((s1 & s2 & s3) == 1 ? 8u : 16u));
    }
    // the CTM translate / scale (pre-concatenated) on the live top matrix
    restore(m, image);
    const u32 ctm = ld(m, 0x95EDF0u + 4 * ld(m, 0x95EE70u));
    REQUIRE(in_ram(ctm, 64));
    for (int k = 0; k < 8; ++k) {
        restore(m, image);
        const D3 R = rdv(m, ctm), U = rdv(m, ctm + 16), A = rdv(m, ctm + 32), P = rdv(m, ctm + 48);
        const float tx = frand(rng, -10, 10), ty = frand(rng, -10, 10);
        g_fpr[12] = tx, g_fpr[13] = ty;
        const bool scale = k % 2 == 1;
        CHECK(wpair(m, by_name(scale ? "sub_4AADA0" : "sub_4AAE00"), {0, 0, 0, 0}, 730000u + k, install_standard).v0() == 1u);
        if (scale) {
            CHECK(len(rdv(m, ctm) - R * tx) < 1e-3 * (1 + len(R)));
            CHECK(len(rdv(m, ctm + 16) - U * ty) < 1e-3 * (1 + len(U)));
            CHECK(len(rdv(m, ctm + 32) - A) < 1e-4 * (1 + len(A)));
        } else
            CHECK(len(rdv(m, ctm + 48) - (P + R * tx + U * ty)) < 1e-3 * (1 + len(P)));
        CHECK(ld(m, 0x95EF50u) == 0u);
        CHECK(ld(m, 0x95EF64u) == 0u);
    }
}

// =====================================================================================================================
// The other bodies on the snapshots, with built records
// =====================================================================================================================
// Every non-collision body on the snapshot images with arguments drawn from a soup of records built in the test area:
// sLists with heap data (entry sizes 4..272), records whose words point at those sLists, at each other or hold small
// values, strings, a node with private / initialisation data -- so the walks, getters and destroys run past their first
// test. 12 pairs a function a snapshot.
TEST_CASE("game(render_rw6): every other body equals its recompiled body on the snapshots with built records") {
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
        std::mt19937 rng{0x52574E00u + static_cast<u32>(snapshots)};
        for (const Case& c : kCases) {
            if (c.addr < 0x464000 || (c.addr >= 0x4BAE00 && c.addr < 0x4BF000)) continue;  // the collision group has its own tests
            for (int k = 0; k < 12; ++k) {
                restore(m, image);
                const u32 soup = kData + 0x1000, lists = kData + 0x8000, strs = kData + 0x9000;
                std::vector<u32> sls;
                const u32 seed = rng();
                auto setup = [&m, soup, lists, strs, seed, &sls](StandInWorld& w) {
                    install_standard(w);
                    w.si.install_recorder(kCallback, "callback (returns 0)", 0);
                    w.si.install(kStrICmp, "stricmp", [](EEContext&, StandIns&, StandInCall& cc) { cc.v0 = cc.args[0] == cc.args[1] ? 0 : 1; });
                    std::mt19937 r{seed};
                    sls.clear();
                    for (u32 i = 0; i < 16; ++i) {
                        const u32 es = std::vector<u32>{4, 8, 12, 16, 24, 60, 272}[r() % 7];
                        const u32 cap = r() % 8, cnt = cap ? r() % (cap + 1) : 0;
                        const u32 data = cap ? w.heap.alloc(cap * es) : 0;
                        const u32 rec = lists + 16 * i;
                        st(m, rec, data), st(m, rec + 4, cnt), st(m, rec + 8, cap), st(m, rec + 12, es);
                        for (u32 j = 0; j < cap * es; j += 4) st(m, data + j, r() % 3 == 0 ? lists + 16 * (r() % 16) : r() % 4);
                        sls.push_back(rec);
                    }
                    for (u32 i = 0; i < 0x1000; i += 4) {
                        const u32 kind = r() % 8;
                        st(m, soup + i, kind < 3 ? sls[r() % sls.size()] : kind < 5 ? soup + ((r() % 0x1000) & ~15u) : kind < 6 ? 0xFFFFFFFFu : r() % 8);
                    }
                    sts(m, strs, "pak:dir/file"), sts(m, strs + 32, "hdd");
                };
                const u32 pick = rng() % 4;
                const Args a{pick == 0 ? soup + ((rng() % 0x1000) & ~15u) : pick == 1 ? lists + 16 * (rng() % 16) : pick == 2 ? strs : rng() % 6,
                             rng() % 3 == 0 ? kCallback : rng() % 3 == 1 ? soup + ((rng() % 0x1000) & ~15u) : rng() % 6,
                             rng() % 2 ? soup + ((rng() % 0x1000) & ~15u) : rng() % 6, rng() % 2 ? soup + 0x800 : rng() % 6};
                const WPair p = wpair(m, c, a, 740000u + static_cast<u32>(pairs), setup, HwCheck{{}, {}, {}, {{GPR_T0, soup + 0x400}, {GPR_T1, soup + 0x600}}});
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
TEST_CASE("game(render_rw6): every body equals its recompiled body on random worlds") {
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
        std::memcpy(m->mem.main_ram(), elf_image.data(), elf_image.size());
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
        const std::string summary = std::string(c.name) + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

#else

TEST_CASE("game(render_rw6): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
