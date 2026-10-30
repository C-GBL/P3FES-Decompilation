// Pair tests of slice render_rw4 (game/src/render/render_rw4.cpp): RenderWare, fourth pass -- frames, matrices, free
// lists, the resource arena, streams and chunk headers, the plugin registry, textures / dictionaries, rasters, the heap
// users earlier render slices skipped and the raster lock / blits. Every body runs against its recompiled body and
// tests/game/handgen_pairs.h compares the whole register file and cycles at every check point and at the return / stop,
// all 32 MiB of RAM (the dead stack included), the scratchpad, the BIOS window and the bus log.
//   * the random-world sweep (the p3fes_handgen skeleton): every function on random words;
//   * the snapshot sweep: every function on the live RenderWare state of the replay snapshots b_5800,
//     dorm_replay_4900, climb_ref_17000 (skipped when absent), on fresh stand-in worlds (stand_ins.h: the heap behind
//     the RW memory slots and the free-list entry points, printf, the H_Cdvd layer, recorders for the callees this
//     build does not emit), with arguments of the kinds each function takes; the stand-ins' call logs and heaps must
//     be equal too;
//   * documented rules on the real objects: the frame hierarchy (remove / add child on the battle snapshot's frames),
//     identity records from frame / matrix create, the multiply / determinant / rotation against the host's
//     arithmetic, the chunk-header reader and find-chunk on a real RMD file (BTL/MODEL/FACILITYP/FP000.RMD), the
//     free-list walk against the host's reading of the bitmaps, the resource arena's usage / flip / allocate / empty.
// P3FES_HG_SEEDS sets the pairs per function, P3FES_HG_ONLY one function, P3FES_HG_TRACE traces every pair.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/render_rw4.h"

#include <cmath>
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

namespace p3fes::recomp_gen {
void fn_sub_4DE0A0_004de0a0(EEContext&);  // generated body
void fn_sub_4DE0A0_004de0a0__recomp(EEContext&);  // recompiled
void fn_sub_4E53E0_004e53e0(EEContext&);  // generated body
void fn_sub_4E53E0_004e53e0__recomp(EEContext&);  // recompiled
void fn_sub_4E6D60_004e6d60(EEContext&);  // generated body
void fn_sub_4E6D60_004e6d60__recomp(EEContext&);  // recompiled
void fn_sub_4E8610_004e8610(EEContext&);  // generated body
void fn_sub_4E8610_004e8610__recomp(EEContext&);  // recompiled
void fn_sub_4E4E90_004e4e90(EEContext&);  // generated body
void fn_sub_4E4E90_004e4e90__recomp(EEContext&);  // recompiled
void fn_sub_4EFA00_004efa00(EEContext&);  // generated body
void fn_sub_4EFA00_004efa00__recomp(EEContext&);  // recompiled
void fn_sub_4AB0E0_004ab0e0(EEContext&);  // generated body
void fn_sub_4AB0E0_004ab0e0__recomp(EEContext&);  // recompiled
void fn_sub_4C1E70_004c1e70(EEContext&);  // generated body
void fn_sub_4C1E70_004c1e70__recomp(EEContext&);  // recompiled
void fn_sub_4C47E0_004c47e0(EEContext&);  // generated body
void fn_sub_4C47E0_004c47e0__recomp(EEContext&);  // recompiled
void fn_sub_4C4930_004c4930(EEContext&);  // generated body
void fn_sub_4C4930_004c4930__recomp(EEContext&);  // recompiled
void fn_sub_4CBF20_004cbf20(EEContext&);  // generated body
void fn_sub_4CBF20_004cbf20__recomp(EEContext&);  // recompiled
void fn_sub_4CC1D0_004cc1d0(EEContext&);  // generated body
void fn_sub_4CC1D0_004cc1d0__recomp(EEContext&);  // recompiled
void fn_sub_4F61C0_004f61c0(EEContext&);  // generated body
void fn_sub_4F61C0_004f61c0__recomp(EEContext&);  // recompiled
void fn_sub_4933D0_004933d0(EEContext&);  // generated body
void fn_sub_4933D0_004933d0__recomp(EEContext&);  // recompiled
void fn_sub_495CF0_00495cf0(EEContext&);  // generated body
void fn_sub_495CF0_00495cf0__recomp(EEContext&);  // recompiled
void fn_sub_4967A0_004967a0(EEContext&);  // generated body
void fn_sub_4967A0_004967a0__recomp(EEContext&);  // recompiled
void fn_sub_4982B0_004982b0(EEContext&);  // generated body
void fn_sub_4982B0_004982b0__recomp(EEContext&);  // recompiled
void fn_sub_497600_00497600(EEContext&);  // generated body
void fn_sub_497600_00497600__recomp(EEContext&);  // recompiled
void fn_sub_498720_00498720(EEContext&);  // generated body
void fn_sub_498720_00498720__recomp(EEContext&);  // recompiled
void fn_sub_498E70_00498e70(EEContext&);  // generated body
void fn_sub_498E70_00498e70__recomp(EEContext&);  // recompiled
void fn_sub_49E5A0_0049e5a0(EEContext&);  // generated body
void fn_sub_49E5A0_0049e5a0__recomp(EEContext&);  // recompiled
void fn_sub_4A08F0_004a08f0(EEContext&);  // generated body
void fn_sub_4A08F0_004a08f0__recomp(EEContext&);  // recompiled
void fn_sub_4A0CE0_004a0ce0(EEContext&);  // generated body
void fn_sub_4A0CE0_004a0ce0__recomp(EEContext&);  // recompiled
void fn_sub_47BB40_0047bb40(EEContext&);  // generated body
void fn_sub_47BB40_0047bb40__recomp(EEContext&);  // recompiled
void fn_sub_47BE10_0047be10(EEContext&);  // generated body
void fn_sub_47BE10_0047be10__recomp(EEContext&);  // recompiled
void fn_sub_4CA9B0_004ca9b0(EEContext&);  // generated body
void fn_sub_4CA9B0_004ca9b0__recomp(EEContext&);  // recompiled
void fn_sub_4CAA50_004caa50(EEContext&);  // generated body
void fn_sub_4CAA50_004caa50__recomp(EEContext&);  // recompiled
void fn_sub_4CAB70_004cab70(EEContext&);  // generated body
void fn_sub_4CAB70_004cab70__recomp(EEContext&);  // recompiled
void fn_sub_4CACE0_004cace0(EEContext&);  // generated body
void fn_sub_4CACE0_004cace0__recomp(EEContext&);  // recompiled
void fn_sub_4CAD30_004cad30(EEContext&);  // generated body
void fn_sub_4CAD30_004cad30__recomp(EEContext&);  // recompiled
void fn_sub_4CAE40_004cae40(EEContext&);  // generated body
void fn_sub_4CAE40_004cae40__recomp(EEContext&);  // recompiled
void fn_sub_4CAF10_004caf10(EEContext&);  // generated body
void fn_sub_4CAF10_004caf10__recomp(EEContext&);  // recompiled
void fn_sub_4CAF80_004caf80(EEContext&);  // generated body
void fn_sub_4CAF80_004caf80__recomp(EEContext&);  // recompiled
void fn_sub_4CB050_004cb050(EEContext&);  // generated body
void fn_sub_4CB050_004cb050__recomp(EEContext&);  // recompiled
void fn_sub_4CB1B0_004cb1b0(EEContext&);  // generated body
void fn_sub_4CB1B0_004cb1b0__recomp(EEContext&);  // recompiled
void fn_sub_4CB270_004cb270(EEContext&);  // generated body
void fn_sub_4CB270_004cb270__recomp(EEContext&);  // recompiled
void fn_sub_4CB340_004cb340(EEContext&);  // generated body
void fn_sub_4CB340_004cb340__recomp(EEContext&);  // recompiled
void fn_sub_4CB350_004cb350(EEContext&);  // generated body
void fn_sub_4CB350_004cb350__recomp(EEContext&);  // recompiled
void fn_sub_4CB420_004cb420(EEContext&);  // generated body
void fn_sub_4CB420_004cb420__recomp(EEContext&);  // recompiled
void fn_sub_4CB590_004cb590(EEContext&);  // generated body
void fn_sub_4CB590_004cb590__recomp(EEContext&);  // recompiled
void fn_sub_4CB6E0_004cb6e0(EEContext&);  // generated body
void fn_sub_4CB6E0_004cb6e0__recomp(EEContext&);  // recompiled
void fn_sub_4CB750_004cb750(EEContext&);  // generated body
void fn_sub_4CB750_004cb750__recomp(EEContext&);  // recompiled
void fn_sub_4CB890_004cb890(EEContext&);  // generated body
void fn_sub_4CB890_004cb890__recomp(EEContext&);  // recompiled
void fn_sub_4CB930_004cb930(EEContext&);  // generated body
void fn_sub_4CB930_004cb930__recomp(EEContext&);  // recompiled
void fn_sub_4CB9F0_004cb9f0(EEContext&);  // generated body
void fn_sub_4CB9F0_004cb9f0__recomp(EEContext&);  // recompiled
void fn_sub_4CEFB0_004cefb0(EEContext&);  // generated body
void fn_sub_4CEFB0_004cefb0__recomp(EEContext&);  // recompiled
void fn_sub_4CF0A0_004cf0a0(EEContext&);  // generated body
void fn_sub_4CF0A0_004cf0a0__recomp(EEContext&);  // recompiled
void fn_sub_4CF1B0_004cf1b0(EEContext&);  // generated body
void fn_sub_4CF1B0_004cf1b0__recomp(EEContext&);  // recompiled
void fn_sub_4CF340_004cf340(EEContext&);  // generated body
void fn_sub_4CF340_004cf340__recomp(EEContext&);  // recompiled
void fn_sub_4C7CF0_004c7cf0(EEContext&);  // generated body
void fn_sub_4C7CF0_004c7cf0__recomp(EEContext&);  // recompiled
void fn_sub_4C7D00_004c7d00(EEContext&);  // generated body
void fn_sub_4C7D00_004c7d00__recomp(EEContext&);  // recompiled
void fn_sub_4C7D30_004c7d30(EEContext&);  // generated body
void fn_sub_4C7D30_004c7d30__recomp(EEContext&);  // recompiled
void fn_sub_4C7D80_004c7d80(EEContext&);  // generated body
void fn_sub_4C7D80_004c7d80__recomp(EEContext&);  // recompiled
void fn_sub_4C2200_004c2200(EEContext&);  // generated body
void fn_sub_4C2200_004c2200__recomp(EEContext&);  // recompiled
void fn_sub_4C2A30_004c2a30(EEContext&);  // generated body
void fn_sub_4C2A30_004c2a30__recomp(EEContext&);  // recompiled
void fn_sub_4C2A70_004c2a70(EEContext&);  // generated body
void fn_sub_4C2A70_004c2a70__recomp(EEContext&);  // recompiled
void fn_sub_4C2AC0_004c2ac0(EEContext&);  // generated body
void fn_sub_4C2AC0_004c2ac0__recomp(EEContext&);  // recompiled
void fn_sub_4C2B20_004c2b20(EEContext&);  // generated body
void fn_sub_4C2B20_004c2b20__recomp(EEContext&);  // recompiled
void fn_sub_4C2B90_004c2b90(EEContext&);  // generated body
void fn_sub_4C2B90_004c2b90__recomp(EEContext&);  // recompiled
void fn_sub_4C2C00_004c2c00(EEContext&);  // generated body
void fn_sub_4C2C00_004c2c00__recomp(EEContext&);  // recompiled
void fn_sub_4C2CC0_004c2cc0(EEContext&);  // generated body
void fn_sub_4C2CC0_004c2cc0__recomp(EEContext&);  // recompiled
void fn_sub_4C2CF0_004c2cf0(EEContext&);  // generated body
void fn_sub_4C2CF0_004c2cf0__recomp(EEContext&);  // recompiled
void fn_sub_4C2D20_004c2d20(EEContext&);  // generated body
void fn_sub_4C2D20_004c2d20__recomp(EEContext&);  // recompiled
void fn_sub_4C2F10_004c2f10(EEContext&);  // generated body
void fn_sub_4C2F10_004c2f10__recomp(EEContext&);  // recompiled
void fn_sub_4C2FC0_004c2fc0(EEContext&);  // generated body
void fn_sub_4C2FC0_004c2fc0__recomp(EEContext&);  // recompiled
void fn_sub_4C31B0_004c31b0(EEContext&);  // generated body
void fn_sub_4C31B0_004c31b0__recomp(EEContext&);  // recompiled
void fn_sub_4C3880_004c3880(EEContext&);  // generated body
void fn_sub_4C3880_004c3880__recomp(EEContext&);  // recompiled
void fn_sub_4C38C0_004c38c0(EEContext&);  // generated body
void fn_sub_4C38C0_004c38c0__recomp(EEContext&);  // recompiled
void fn_sub_4B91B0_004b91b0(EEContext&);  // generated body
void fn_sub_4B91B0_004b91b0__recomp(EEContext&);  // recompiled
void fn_sub_4C19F0_004c19f0(EEContext&);  // generated body
void fn_sub_4C19F0_004c19f0__recomp(EEContext&);  // recompiled
void fn_sub_4C3960_004c3960(EEContext&);  // generated body
void fn_sub_4C3960_004c3960__recomp(EEContext&);  // recompiled
void fn_sub_4C3970_004c3970(EEContext&);  // generated body
void fn_sub_4C3970_004c3970__recomp(EEContext&);  // recompiled
void fn_sub_4C3B50_004c3b50(EEContext&);  // generated body
void fn_sub_4C3B50_004c3b50__recomp(EEContext&);  // recompiled
void fn_sub_4C3B60_004c3b60(EEContext&);  // generated body
void fn_sub_4C3B60_004c3b60__recomp(EEContext&);  // recompiled
void fn_sub_4C3B70_004c3b70(EEContext&);  // generated body
void fn_sub_4C3B70_004c3b70__recomp(EEContext&);  // recompiled
void fn_sub_4C3C30_004c3c30(EEContext&);  // generated body
void fn_sub_4C3C30_004c3c30__recomp(EEContext&);  // recompiled
void fn_sub_4C4080_004c4080(EEContext&);  // generated body
void fn_sub_4C4080_004c4080__recomp(EEContext&);  // recompiled
void fn_sub_4C4200_004c4200(EEContext&);  // generated body
void fn_sub_4C4200_004c4200__recomp(EEContext&);  // recompiled
void fn_sub_4C43B0_004c43b0(EEContext&);  // generated body
void fn_sub_4C43B0_004c43b0__recomp(EEContext&);  // recompiled
void fn_sub_4C45F0_004c45f0(EEContext&);  // generated body
void fn_sub_4C45F0_004c45f0__recomp(EEContext&);  // recompiled
void fn_sub_4C46F0_004c46f0(EEContext&);  // generated body
void fn_sub_4C46F0_004c46f0__recomp(EEContext&);  // recompiled
void fn_sub_4C4750_004c4750(EEContext&);  // generated body
void fn_sub_4C4750_004c4750__recomp(EEContext&);  // recompiled
void fn_sub_4C4890_004c4890(EEContext&);  // generated body
void fn_sub_4C4890_004c4890__recomp(EEContext&);  // recompiled
void fn_RwResourcesSetArenaSize_004c4c00(EEContext&);  // generated body
void fn_RwResourcesSetArenaSize_004c4c00__recomp(EEContext&);  // recompiled
void fn_sub_4C4D20_004c4d20(EEContext&);  // generated body
void fn_sub_4C4D20_004c4d20__recomp(EEContext&);  // recompiled
void fn_sub_4C4D70_004c4d70(EEContext&);  // generated body
void fn_sub_4C4D70_004c4d70__recomp(EEContext&);  // recompiled
void fn_sub_4C6DF0_004c6df0(EEContext&);  // generated body
void fn_sub_4C6DF0_004c6df0__recomp(EEContext&);  // recompiled
void fn_sub_4C6E50_004c6e50(EEContext&);  // generated body
void fn_sub_4C6E50_004c6e50__recomp(EEContext&);  // recompiled
void fn_sub_4C12D0_004c12d0(EEContext&);  // generated body
void fn_sub_4C12D0_004c12d0__recomp(EEContext&);  // recompiled
void fn_sub_4C1450_004c1450(EEContext&);  // generated body
void fn_sub_4C1450_004c1450__recomp(EEContext&);  // recompiled
void fn_sub_4C15A0_004c15a0(EEContext&);  // generated body
void fn_sub_4C15A0_004c15a0__recomp(EEContext&);  // recompiled
void fn_sub_4C1600_004c1600(EEContext&);  // generated body
void fn_sub_4C1600_004c1600__recomp(EEContext&);  // recompiled
void fn_sub_4C1750_004c1750(EEContext&);  // generated body
void fn_sub_4C1750_004c1750__recomp(EEContext&);  // recompiled
void fn_sub_4C17F0_004c17f0(EEContext&);  // generated body
void fn_sub_4C17F0_004c17f0__recomp(EEContext&);  // recompiled
void fn_sub_4C1820_004c1820(EEContext&);  // generated body
void fn_sub_4C1820_004c1820__recomp(EEContext&);  // recompiled
void fn_sub_4C1850_004c1850(EEContext&);  // generated body
void fn_sub_4C1850_004c1850__recomp(EEContext&);  // recompiled
void fn_sub_4C18B0_004c18b0(EEContext&);  // generated body
void fn_sub_4C18B0_004c18b0__recomp(EEContext&);  // recompiled
void fn_sub_4C1910_004c1910(EEContext&);  // generated body
void fn_sub_4C1910_004c1910__recomp(EEContext&);  // recompiled
void fn_sub_4C1970_004c1970(EEContext&);  // generated body
void fn_sub_4C1970_004c1970__recomp(EEContext&);  // recompiled
void fn_sub_4C4EB0_004c4eb0(EEContext&);  // generated body
void fn_sub_4C4EB0_004c4eb0__recomp(EEContext&);  // recompiled
void fn_sub_4C4F30_004c4f30(EEContext&);  // generated body
void fn_sub_4C4F30_004c4f30__recomp(EEContext&);  // recompiled
void fn_sub_4C4F90_004c4f90(EEContext&);  // generated body
void fn_sub_4C4F90_004c4f90__recomp(EEContext&);  // recompiled
void fn_sub_4C5090_004c5090(EEContext&);  // generated body
void fn_sub_4C5090_004c5090__recomp(EEContext&);  // recompiled
void fn_sub_4C5140_004c5140(EEContext&);  // generated body
void fn_sub_4C5140_004c5140__recomp(EEContext&);  // recompiled
void fn_sub_4C5250_004c5250(EEContext&);  // generated body
void fn_sub_4C5250_004c5250__recomp(EEContext&);  // recompiled
void fn_sub_4C53F0_004c53f0(EEContext&);  // generated body
void fn_sub_4C53F0_004c53f0__recomp(EEContext&);  // recompiled
void fn_sub_4C5620_004c5620(EEContext&);  // generated body
void fn_sub_4C5620_004c5620__recomp(EEContext&);  // recompiled
void fn_sub_4C5780_004c5780(EEContext&);  // generated body
void fn_sub_4C5780_004c5780__recomp(EEContext&);  // recompiled
void fn_sub_4C58A0_004c58a0(EEContext&);  // generated body
void fn_sub_4C58A0_004c58a0__recomp(EEContext&);  // recompiled
void fn_sub_4C5A50_004c5a50(EEContext&);  // generated body
void fn_sub_4C5A50_004c5a50__recomp(EEContext&);  // recompiled
void fn_sub_4C5C30_004c5c30(EEContext&);  // generated body
void fn_sub_4C5C30_004c5c30__recomp(EEContext&);  // recompiled
void fn_sub_4C5CB0_004c5cb0(EEContext&);  // generated body
void fn_sub_4C5CB0_004c5cb0__recomp(EEContext&);  // recompiled
void fn_sub_4C5D30_004c5d30(EEContext&);  // generated body
void fn_sub_4C5D30_004c5d30__recomp(EEContext&);  // recompiled
void fn_sub_4C5EA0_004c5ea0(EEContext&);  // generated body
void fn_sub_4C5EA0_004c5ea0__recomp(EEContext&);  // recompiled
void fn_sub_4C5F70_004c5f70(EEContext&);  // generated body
void fn_sub_4C5F70_004c5f70__recomp(EEContext&);  // recompiled
void fn_sub_4C6000_004c6000(EEContext&);  // generated body
void fn_sub_4C6000_004c6000__recomp(EEContext&);  // recompiled
void fn_sub_4C6140_004c6140(EEContext&);  // generated body
void fn_sub_4C6140_004c6140__recomp(EEContext&);  // recompiled
void fn_sub_4C6150_004c6150(EEContext&);  // generated body
void fn_sub_4C6150_004c6150__recomp(EEContext&);  // recompiled
void fn_sub_4C6160_004c6160(EEContext&);  // generated body
void fn_sub_4C6160_004c6160__recomp(EEContext&);  // recompiled
void fn_sub_4C61B0_004c61b0(EEContext&);  // generated body
void fn_sub_4C61B0_004c61b0__recomp(EEContext&);  // recompiled
void fn_sub_4C64B0_004c64b0(EEContext&);  // generated body
void fn_sub_4C64B0_004c64b0__recomp(EEContext&);  // recompiled
void fn_sub_4C6560_004c6560(EEContext&);  // generated body
void fn_sub_4C6560_004c6560__recomp(EEContext&);  // recompiled
void fn_sub_4C65D0_004c65d0(EEContext&);  // generated body
void fn_sub_4C65D0_004c65d0__recomp(EEContext&);  // recompiled
void fn_sub_4D0C30_004d0c30(EEContext&);  // generated body
void fn_sub_4D0C30_004d0c30__recomp(EEContext&);  // recompiled
void fn_sub_4D0D10_004d0d10(EEContext&);  // generated body
void fn_sub_4D0D10_004d0d10__recomp(EEContext&);  // recompiled
void fn_sub_4D0DC0_004d0dc0(EEContext&);  // generated body
void fn_sub_4D0DC0_004d0dc0__recomp(EEContext&);  // recompiled
void fn_sub_4D0E40_004d0e40(EEContext&);  // generated body
void fn_sub_4D0E40_004d0e40__recomp(EEContext&);  // recompiled
void fn_sub_4D0F00_004d0f00(EEContext&);  // generated body
void fn_sub_4D0F00_004d0f00__recomp(EEContext&);  // recompiled
void fn_sub_4D1070_004d1070(EEContext&);  // generated body
void fn_sub_4D1070_004d1070__recomp(EEContext&);  // recompiled
void fn_sub_4D1110_004d1110(EEContext&);  // generated body
void fn_sub_4D1110_004d1110__recomp(EEContext&);  // recompiled
void fn_sub_4D1170_004d1170(EEContext&);  // generated body
void fn_sub_4D1170_004d1170__recomp(EEContext&);  // recompiled
void fn_sub_4D11F0_004d11f0(EEContext&);  // generated body
void fn_sub_4D11F0_004d11f0__recomp(EEContext&);  // recompiled
void fn_sub_4D1210_004d1210(EEContext&);  // generated body
void fn_sub_4D1210_004d1210__recomp(EEContext&);  // recompiled
void fn_sub_4D13B0_004d13b0(EEContext&);  // generated body
void fn_sub_4D13B0_004d13b0__recomp(EEContext&);  // recompiled
void fn_sub_4D1420_004d1420(EEContext&);  // generated body
void fn_sub_4D1420_004d1420__recomp(EEContext&);  // recompiled
void fn_sub_4D15E0_004d15e0(EEContext&);  // generated body
void fn_sub_4D15E0_004d15e0__recomp(EEContext&);  // recompiled
void fn_sub_4C81A0_004c81a0(EEContext&);  // generated body
void fn_sub_4C81A0_004c81a0__recomp(EEContext&);  // recompiled
void fn_sub_4C81D0_004c81d0(EEContext&);  // generated body
void fn_sub_4C81D0_004c81d0__recomp(EEContext&);  // recompiled
void fn_sub_4C8240_004c8240(EEContext&);  // generated body
void fn_sub_4C8240_004c8240__recomp(EEContext&);  // recompiled
void fn_sub_4C83C0_004c83c0(EEContext&);  // generated body
void fn_sub_4C83C0_004c83c0__recomp(EEContext&);  // recompiled
void fn_sub_4C8650_004c8650(EEContext&);  // generated body
void fn_sub_4C8650_004c8650__recomp(EEContext&);  // recompiled
void fn_sub_4C8680_004c8680(EEContext&);  // generated body
void fn_sub_4C8680_004c8680__recomp(EEContext&);  // recompiled
void fn_sub_4CDE40_004cde40(EEContext&);  // generated body
void fn_sub_4CDE40_004cde40__recomp(EEContext&);  // recompiled
void fn_sub_4CDE90_004cde90(EEContext&);  // generated body
void fn_sub_4CDE90_004cde90__recomp(EEContext&);  // recompiled
void fn_sub_4CDF00_004cdf00(EEContext&);  // generated body
void fn_sub_4CDF00_004cdf00__recomp(EEContext&);  // recompiled
void fn_sub_4CDF30_004cdf30(EEContext&);  // generated body
void fn_sub_4CDF30_004cdf30__recomp(EEContext&);  // recompiled
void fn_sub_4CDF80_004cdf80(EEContext&);  // generated body
void fn_sub_4CDF80_004cdf80__recomp(EEContext&);  // recompiled
void fn_sub_4CE0F0_004ce0f0(EEContext&);  // generated body
void fn_sub_4CE0F0_004ce0f0__recomp(EEContext&);  // recompiled
void fn_sub_4CE250_004ce250(EEContext&);  // generated body
void fn_sub_4CE250_004ce250__recomp(EEContext&);  // recompiled
void fn_sub_4CE2C0_004ce2c0(EEContext&);  // generated body
void fn_sub_4CE2C0_004ce2c0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_4DE0A0", 0x4DE0A0, &recomp_gen::fn_sub_4DE0A0_004de0a0, &recomp_gen::fn_sub_4DE0A0_004de0a0__recomp},
    {"sub_4E53E0", 0x4E53E0, &recomp_gen::fn_sub_4E53E0_004e53e0, &recomp_gen::fn_sub_4E53E0_004e53e0__recomp},
    {"sub_4E6D60", 0x4E6D60, &recomp_gen::fn_sub_4E6D60_004e6d60, &recomp_gen::fn_sub_4E6D60_004e6d60__recomp},
    {"sub_4E8610", 0x4E8610, &recomp_gen::fn_sub_4E8610_004e8610, &recomp_gen::fn_sub_4E8610_004e8610__recomp},
    {"sub_4E4E90", 0x4E4E90, &recomp_gen::fn_sub_4E4E90_004e4e90, &recomp_gen::fn_sub_4E4E90_004e4e90__recomp},
    {"sub_4EFA00", 0x4EFA00, &recomp_gen::fn_sub_4EFA00_004efa00, &recomp_gen::fn_sub_4EFA00_004efa00__recomp},
    {"sub_4AB0E0", 0x4AB0E0, &recomp_gen::fn_sub_4AB0E0_004ab0e0, &recomp_gen::fn_sub_4AB0E0_004ab0e0__recomp},
    {"sub_4C1E70", 0x4C1E70, &recomp_gen::fn_sub_4C1E70_004c1e70, &recomp_gen::fn_sub_4C1E70_004c1e70__recomp},
    {"sub_4C47E0", 0x4C47E0, &recomp_gen::fn_sub_4C47E0_004c47e0, &recomp_gen::fn_sub_4C47E0_004c47e0__recomp},
    {"sub_4C4930", 0x4C4930, &recomp_gen::fn_sub_4C4930_004c4930, &recomp_gen::fn_sub_4C4930_004c4930__recomp},
    {"sub_4CBF20", 0x4CBF20, &recomp_gen::fn_sub_4CBF20_004cbf20, &recomp_gen::fn_sub_4CBF20_004cbf20__recomp},
    {"sub_4CC1D0", 0x4CC1D0, &recomp_gen::fn_sub_4CC1D0_004cc1d0, &recomp_gen::fn_sub_4CC1D0_004cc1d0__recomp},
    {"sub_4F61C0", 0x4F61C0, &recomp_gen::fn_sub_4F61C0_004f61c0, &recomp_gen::fn_sub_4F61C0_004f61c0__recomp},
    {"sub_4933D0", 0x4933D0, &recomp_gen::fn_sub_4933D0_004933d0, &recomp_gen::fn_sub_4933D0_004933d0__recomp},
    {"sub_495CF0", 0x495CF0, &recomp_gen::fn_sub_495CF0_00495cf0, &recomp_gen::fn_sub_495CF0_00495cf0__recomp},
    {"sub_4967A0", 0x4967A0, &recomp_gen::fn_sub_4967A0_004967a0, &recomp_gen::fn_sub_4967A0_004967a0__recomp},
    {"sub_4982B0", 0x4982B0, &recomp_gen::fn_sub_4982B0_004982b0, &recomp_gen::fn_sub_4982B0_004982b0__recomp},
    {"sub_497600", 0x497600, &recomp_gen::fn_sub_497600_00497600, &recomp_gen::fn_sub_497600_00497600__recomp},
    {"sub_498720", 0x498720, &recomp_gen::fn_sub_498720_00498720, &recomp_gen::fn_sub_498720_00498720__recomp},
    {"sub_498E70", 0x498E70, &recomp_gen::fn_sub_498E70_00498e70, &recomp_gen::fn_sub_498E70_00498e70__recomp},
    {"sub_49E5A0", 0x49E5A0, &recomp_gen::fn_sub_49E5A0_0049e5a0, &recomp_gen::fn_sub_49E5A0_0049e5a0__recomp},
    {"sub_4A08F0", 0x4A08F0, &recomp_gen::fn_sub_4A08F0_004a08f0, &recomp_gen::fn_sub_4A08F0_004a08f0__recomp},
    {"sub_4A0CE0", 0x4A0CE0, &recomp_gen::fn_sub_4A0CE0_004a0ce0, &recomp_gen::fn_sub_4A0CE0_004a0ce0__recomp},
    {"sub_47BB40", 0x47BB40, &recomp_gen::fn_sub_47BB40_0047bb40, &recomp_gen::fn_sub_47BB40_0047bb40__recomp},
    {"sub_47BE10", 0x47BE10, &recomp_gen::fn_sub_47BE10_0047be10, &recomp_gen::fn_sub_47BE10_0047be10__recomp},
    {"sub_4CA9B0", 0x4CA9B0, &recomp_gen::fn_sub_4CA9B0_004ca9b0, &recomp_gen::fn_sub_4CA9B0_004ca9b0__recomp},
    {"sub_4CAA50", 0x4CAA50, &recomp_gen::fn_sub_4CAA50_004caa50, &recomp_gen::fn_sub_4CAA50_004caa50__recomp},
    {"sub_4CAB70", 0x4CAB70, &recomp_gen::fn_sub_4CAB70_004cab70, &recomp_gen::fn_sub_4CAB70_004cab70__recomp},
    {"sub_4CACE0", 0x4CACE0, &recomp_gen::fn_sub_4CACE0_004cace0, &recomp_gen::fn_sub_4CACE0_004cace0__recomp},
    {"sub_4CAD30", 0x4CAD30, &recomp_gen::fn_sub_4CAD30_004cad30, &recomp_gen::fn_sub_4CAD30_004cad30__recomp},
    {"sub_4CAE40", 0x4CAE40, &recomp_gen::fn_sub_4CAE40_004cae40, &recomp_gen::fn_sub_4CAE40_004cae40__recomp},
    {"sub_4CAF10", 0x4CAF10, &recomp_gen::fn_sub_4CAF10_004caf10, &recomp_gen::fn_sub_4CAF10_004caf10__recomp},
    {"sub_4CAF80", 0x4CAF80, &recomp_gen::fn_sub_4CAF80_004caf80, &recomp_gen::fn_sub_4CAF80_004caf80__recomp},
    {"sub_4CB050", 0x4CB050, &recomp_gen::fn_sub_4CB050_004cb050, &recomp_gen::fn_sub_4CB050_004cb050__recomp},
    {"sub_4CB1B0", 0x4CB1B0, &recomp_gen::fn_sub_4CB1B0_004cb1b0, &recomp_gen::fn_sub_4CB1B0_004cb1b0__recomp},
    {"sub_4CB270", 0x4CB270, &recomp_gen::fn_sub_4CB270_004cb270, &recomp_gen::fn_sub_4CB270_004cb270__recomp},
    {"sub_4CB340", 0x4CB340, &recomp_gen::fn_sub_4CB340_004cb340, &recomp_gen::fn_sub_4CB340_004cb340__recomp},
    {"sub_4CB350", 0x4CB350, &recomp_gen::fn_sub_4CB350_004cb350, &recomp_gen::fn_sub_4CB350_004cb350__recomp},
    {"sub_4CB420", 0x4CB420, &recomp_gen::fn_sub_4CB420_004cb420, &recomp_gen::fn_sub_4CB420_004cb420__recomp},
    {"sub_4CB590", 0x4CB590, &recomp_gen::fn_sub_4CB590_004cb590, &recomp_gen::fn_sub_4CB590_004cb590__recomp},
    {"sub_4CB6E0", 0x4CB6E0, &recomp_gen::fn_sub_4CB6E0_004cb6e0, &recomp_gen::fn_sub_4CB6E0_004cb6e0__recomp},
    {"sub_4CB750", 0x4CB750, &recomp_gen::fn_sub_4CB750_004cb750, &recomp_gen::fn_sub_4CB750_004cb750__recomp},
    {"sub_4CB890", 0x4CB890, &recomp_gen::fn_sub_4CB890_004cb890, &recomp_gen::fn_sub_4CB890_004cb890__recomp},
    {"sub_4CB930", 0x4CB930, &recomp_gen::fn_sub_4CB930_004cb930, &recomp_gen::fn_sub_4CB930_004cb930__recomp},
    {"sub_4CB9F0", 0x4CB9F0, &recomp_gen::fn_sub_4CB9F0_004cb9f0, &recomp_gen::fn_sub_4CB9F0_004cb9f0__recomp},
    {"sub_4CEFB0", 0x4CEFB0, &recomp_gen::fn_sub_4CEFB0_004cefb0, &recomp_gen::fn_sub_4CEFB0_004cefb0__recomp},
    {"sub_4CF0A0", 0x4CF0A0, &recomp_gen::fn_sub_4CF0A0_004cf0a0, &recomp_gen::fn_sub_4CF0A0_004cf0a0__recomp},
    {"sub_4CF1B0", 0x4CF1B0, &recomp_gen::fn_sub_4CF1B0_004cf1b0, &recomp_gen::fn_sub_4CF1B0_004cf1b0__recomp},
    {"sub_4CF340", 0x4CF340, &recomp_gen::fn_sub_4CF340_004cf340, &recomp_gen::fn_sub_4CF340_004cf340__recomp},
    {"sub_4C7CF0", 0x4C7CF0, &recomp_gen::fn_sub_4C7CF0_004c7cf0, &recomp_gen::fn_sub_4C7CF0_004c7cf0__recomp},
    {"sub_4C7D00", 0x4C7D00, &recomp_gen::fn_sub_4C7D00_004c7d00, &recomp_gen::fn_sub_4C7D00_004c7d00__recomp},
    {"sub_4C7D30", 0x4C7D30, &recomp_gen::fn_sub_4C7D30_004c7d30, &recomp_gen::fn_sub_4C7D30_004c7d30__recomp},
    {"sub_4C7D80", 0x4C7D80, &recomp_gen::fn_sub_4C7D80_004c7d80, &recomp_gen::fn_sub_4C7D80_004c7d80__recomp},
    {"sub_4C2200", 0x4C2200, &recomp_gen::fn_sub_4C2200_004c2200, &recomp_gen::fn_sub_4C2200_004c2200__recomp},
    {"sub_4C2A30", 0x4C2A30, &recomp_gen::fn_sub_4C2A30_004c2a30, &recomp_gen::fn_sub_4C2A30_004c2a30__recomp},
    {"sub_4C2A70", 0x4C2A70, &recomp_gen::fn_sub_4C2A70_004c2a70, &recomp_gen::fn_sub_4C2A70_004c2a70__recomp},
    {"sub_4C2AC0", 0x4C2AC0, &recomp_gen::fn_sub_4C2AC0_004c2ac0, &recomp_gen::fn_sub_4C2AC0_004c2ac0__recomp},
    {"sub_4C2B20", 0x4C2B20, &recomp_gen::fn_sub_4C2B20_004c2b20, &recomp_gen::fn_sub_4C2B20_004c2b20__recomp},
    {"sub_4C2B90", 0x4C2B90, &recomp_gen::fn_sub_4C2B90_004c2b90, &recomp_gen::fn_sub_4C2B90_004c2b90__recomp},
    {"sub_4C2C00", 0x4C2C00, &recomp_gen::fn_sub_4C2C00_004c2c00, &recomp_gen::fn_sub_4C2C00_004c2c00__recomp},
    {"sub_4C2CC0", 0x4C2CC0, &recomp_gen::fn_sub_4C2CC0_004c2cc0, &recomp_gen::fn_sub_4C2CC0_004c2cc0__recomp},
    {"sub_4C2CF0", 0x4C2CF0, &recomp_gen::fn_sub_4C2CF0_004c2cf0, &recomp_gen::fn_sub_4C2CF0_004c2cf0__recomp},
    {"sub_4C2D20", 0x4C2D20, &recomp_gen::fn_sub_4C2D20_004c2d20, &recomp_gen::fn_sub_4C2D20_004c2d20__recomp},
    {"sub_4C2F10", 0x4C2F10, &recomp_gen::fn_sub_4C2F10_004c2f10, &recomp_gen::fn_sub_4C2F10_004c2f10__recomp},
    {"sub_4C2FC0", 0x4C2FC0, &recomp_gen::fn_sub_4C2FC0_004c2fc0, &recomp_gen::fn_sub_4C2FC0_004c2fc0__recomp},
    {"sub_4C31B0", 0x4C31B0, &recomp_gen::fn_sub_4C31B0_004c31b0, &recomp_gen::fn_sub_4C31B0_004c31b0__recomp},
    {"sub_4C3880", 0x4C3880, &recomp_gen::fn_sub_4C3880_004c3880, &recomp_gen::fn_sub_4C3880_004c3880__recomp},
    {"sub_4C38C0", 0x4C38C0, &recomp_gen::fn_sub_4C38C0_004c38c0, &recomp_gen::fn_sub_4C38C0_004c38c0__recomp},
    {"sub_4B91B0", 0x4B91B0, &recomp_gen::fn_sub_4B91B0_004b91b0, &recomp_gen::fn_sub_4B91B0_004b91b0__recomp},
    {"sub_4C19F0", 0x4C19F0, &recomp_gen::fn_sub_4C19F0_004c19f0, &recomp_gen::fn_sub_4C19F0_004c19f0__recomp},
    {"sub_4C3960", 0x4C3960, &recomp_gen::fn_sub_4C3960_004c3960, &recomp_gen::fn_sub_4C3960_004c3960__recomp},
    {"sub_4C3970", 0x4C3970, &recomp_gen::fn_sub_4C3970_004c3970, &recomp_gen::fn_sub_4C3970_004c3970__recomp},
    {"sub_4C3B50", 0x4C3B50, &recomp_gen::fn_sub_4C3B50_004c3b50, &recomp_gen::fn_sub_4C3B50_004c3b50__recomp},
    {"sub_4C3B60", 0x4C3B60, &recomp_gen::fn_sub_4C3B60_004c3b60, &recomp_gen::fn_sub_4C3B60_004c3b60__recomp},
    {"sub_4C3B70", 0x4C3B70, &recomp_gen::fn_sub_4C3B70_004c3b70, &recomp_gen::fn_sub_4C3B70_004c3b70__recomp},
    {"sub_4C3C30", 0x4C3C30, &recomp_gen::fn_sub_4C3C30_004c3c30, &recomp_gen::fn_sub_4C3C30_004c3c30__recomp},
    {"sub_4C4080", 0x4C4080, &recomp_gen::fn_sub_4C4080_004c4080, &recomp_gen::fn_sub_4C4080_004c4080__recomp},
    {"sub_4C4200", 0x4C4200, &recomp_gen::fn_sub_4C4200_004c4200, &recomp_gen::fn_sub_4C4200_004c4200__recomp},
    {"sub_4C43B0", 0x4C43B0, &recomp_gen::fn_sub_4C43B0_004c43b0, &recomp_gen::fn_sub_4C43B0_004c43b0__recomp},
    {"sub_4C45F0", 0x4C45F0, &recomp_gen::fn_sub_4C45F0_004c45f0, &recomp_gen::fn_sub_4C45F0_004c45f0__recomp},
    {"sub_4C46F0", 0x4C46F0, &recomp_gen::fn_sub_4C46F0_004c46f0, &recomp_gen::fn_sub_4C46F0_004c46f0__recomp},
    {"sub_4C4750", 0x4C4750, &recomp_gen::fn_sub_4C4750_004c4750, &recomp_gen::fn_sub_4C4750_004c4750__recomp},
    {"sub_4C4890", 0x4C4890, &recomp_gen::fn_sub_4C4890_004c4890, &recomp_gen::fn_sub_4C4890_004c4890__recomp},
    {"RwResourcesSetArenaSize", 0x4C4C00, &recomp_gen::fn_RwResourcesSetArenaSize_004c4c00, &recomp_gen::fn_RwResourcesSetArenaSize_004c4c00__recomp},
    {"sub_4C4D20", 0x4C4D20, &recomp_gen::fn_sub_4C4D20_004c4d20, &recomp_gen::fn_sub_4C4D20_004c4d20__recomp},
    {"sub_4C4D70", 0x4C4D70, &recomp_gen::fn_sub_4C4D70_004c4d70, &recomp_gen::fn_sub_4C4D70_004c4d70__recomp},
    {"sub_4C6DF0", 0x4C6DF0, &recomp_gen::fn_sub_4C6DF0_004c6df0, &recomp_gen::fn_sub_4C6DF0_004c6df0__recomp},
    {"sub_4C6E50", 0x4C6E50, &recomp_gen::fn_sub_4C6E50_004c6e50, &recomp_gen::fn_sub_4C6E50_004c6e50__recomp},
    {"sub_4C12D0", 0x4C12D0, &recomp_gen::fn_sub_4C12D0_004c12d0, &recomp_gen::fn_sub_4C12D0_004c12d0__recomp},
    {"sub_4C1450", 0x4C1450, &recomp_gen::fn_sub_4C1450_004c1450, &recomp_gen::fn_sub_4C1450_004c1450__recomp},
    {"sub_4C15A0", 0x4C15A0, &recomp_gen::fn_sub_4C15A0_004c15a0, &recomp_gen::fn_sub_4C15A0_004c15a0__recomp},
    {"sub_4C1600", 0x4C1600, &recomp_gen::fn_sub_4C1600_004c1600, &recomp_gen::fn_sub_4C1600_004c1600__recomp},
    {"sub_4C1750", 0x4C1750, &recomp_gen::fn_sub_4C1750_004c1750, &recomp_gen::fn_sub_4C1750_004c1750__recomp},
    {"sub_4C17F0", 0x4C17F0, &recomp_gen::fn_sub_4C17F0_004c17f0, &recomp_gen::fn_sub_4C17F0_004c17f0__recomp},
    {"sub_4C1820", 0x4C1820, &recomp_gen::fn_sub_4C1820_004c1820, &recomp_gen::fn_sub_4C1820_004c1820__recomp},
    {"sub_4C1850", 0x4C1850, &recomp_gen::fn_sub_4C1850_004c1850, &recomp_gen::fn_sub_4C1850_004c1850__recomp},
    {"sub_4C18B0", 0x4C18B0, &recomp_gen::fn_sub_4C18B0_004c18b0, &recomp_gen::fn_sub_4C18B0_004c18b0__recomp},
    {"sub_4C1910", 0x4C1910, &recomp_gen::fn_sub_4C1910_004c1910, &recomp_gen::fn_sub_4C1910_004c1910__recomp},
    {"sub_4C1970", 0x4C1970, &recomp_gen::fn_sub_4C1970_004c1970, &recomp_gen::fn_sub_4C1970_004c1970__recomp},
    {"sub_4C4EB0", 0x4C4EB0, &recomp_gen::fn_sub_4C4EB0_004c4eb0, &recomp_gen::fn_sub_4C4EB0_004c4eb0__recomp},
    {"sub_4C4F30", 0x4C4F30, &recomp_gen::fn_sub_4C4F30_004c4f30, &recomp_gen::fn_sub_4C4F30_004c4f30__recomp},
    {"sub_4C4F90", 0x4C4F90, &recomp_gen::fn_sub_4C4F90_004c4f90, &recomp_gen::fn_sub_4C4F90_004c4f90__recomp},
    {"sub_4C5090", 0x4C5090, &recomp_gen::fn_sub_4C5090_004c5090, &recomp_gen::fn_sub_4C5090_004c5090__recomp},
    {"sub_4C5140", 0x4C5140, &recomp_gen::fn_sub_4C5140_004c5140, &recomp_gen::fn_sub_4C5140_004c5140__recomp},
    {"sub_4C5250", 0x4C5250, &recomp_gen::fn_sub_4C5250_004c5250, &recomp_gen::fn_sub_4C5250_004c5250__recomp},
    {"sub_4C53F0", 0x4C53F0, &recomp_gen::fn_sub_4C53F0_004c53f0, &recomp_gen::fn_sub_4C53F0_004c53f0__recomp},
    {"sub_4C5620", 0x4C5620, &recomp_gen::fn_sub_4C5620_004c5620, &recomp_gen::fn_sub_4C5620_004c5620__recomp},
    {"sub_4C5780", 0x4C5780, &recomp_gen::fn_sub_4C5780_004c5780, &recomp_gen::fn_sub_4C5780_004c5780__recomp},
    {"sub_4C58A0", 0x4C58A0, &recomp_gen::fn_sub_4C58A0_004c58a0, &recomp_gen::fn_sub_4C58A0_004c58a0__recomp},
    {"sub_4C5A50", 0x4C5A50, &recomp_gen::fn_sub_4C5A50_004c5a50, &recomp_gen::fn_sub_4C5A50_004c5a50__recomp},
    {"sub_4C5C30", 0x4C5C30, &recomp_gen::fn_sub_4C5C30_004c5c30, &recomp_gen::fn_sub_4C5C30_004c5c30__recomp},
    {"sub_4C5CB0", 0x4C5CB0, &recomp_gen::fn_sub_4C5CB0_004c5cb0, &recomp_gen::fn_sub_4C5CB0_004c5cb0__recomp},
    {"sub_4C5D30", 0x4C5D30, &recomp_gen::fn_sub_4C5D30_004c5d30, &recomp_gen::fn_sub_4C5D30_004c5d30__recomp},
    {"sub_4C5EA0", 0x4C5EA0, &recomp_gen::fn_sub_4C5EA0_004c5ea0, &recomp_gen::fn_sub_4C5EA0_004c5ea0__recomp},
    {"sub_4C5F70", 0x4C5F70, &recomp_gen::fn_sub_4C5F70_004c5f70, &recomp_gen::fn_sub_4C5F70_004c5f70__recomp},
    {"sub_4C6000", 0x4C6000, &recomp_gen::fn_sub_4C6000_004c6000, &recomp_gen::fn_sub_4C6000_004c6000__recomp},
    {"sub_4C6140", 0x4C6140, &recomp_gen::fn_sub_4C6140_004c6140, &recomp_gen::fn_sub_4C6140_004c6140__recomp},
    {"sub_4C6150", 0x4C6150, &recomp_gen::fn_sub_4C6150_004c6150, &recomp_gen::fn_sub_4C6150_004c6150__recomp},
    {"sub_4C6160", 0x4C6160, &recomp_gen::fn_sub_4C6160_004c6160, &recomp_gen::fn_sub_4C6160_004c6160__recomp},
    {"sub_4C61B0", 0x4C61B0, &recomp_gen::fn_sub_4C61B0_004c61b0, &recomp_gen::fn_sub_4C61B0_004c61b0__recomp},
    {"sub_4C64B0", 0x4C64B0, &recomp_gen::fn_sub_4C64B0_004c64b0, &recomp_gen::fn_sub_4C64B0_004c64b0__recomp},
    {"sub_4C6560", 0x4C6560, &recomp_gen::fn_sub_4C6560_004c6560, &recomp_gen::fn_sub_4C6560_004c6560__recomp},
    {"sub_4C65D0", 0x4C65D0, &recomp_gen::fn_sub_4C65D0_004c65d0, &recomp_gen::fn_sub_4C65D0_004c65d0__recomp},
    {"sub_4D0C30", 0x4D0C30, &recomp_gen::fn_sub_4D0C30_004d0c30, &recomp_gen::fn_sub_4D0C30_004d0c30__recomp},
    {"sub_4D0D10", 0x4D0D10, &recomp_gen::fn_sub_4D0D10_004d0d10, &recomp_gen::fn_sub_4D0D10_004d0d10__recomp},
    {"sub_4D0DC0", 0x4D0DC0, &recomp_gen::fn_sub_4D0DC0_004d0dc0, &recomp_gen::fn_sub_4D0DC0_004d0dc0__recomp},
    {"sub_4D0E40", 0x4D0E40, &recomp_gen::fn_sub_4D0E40_004d0e40, &recomp_gen::fn_sub_4D0E40_004d0e40__recomp},
    {"sub_4D0F00", 0x4D0F00, &recomp_gen::fn_sub_4D0F00_004d0f00, &recomp_gen::fn_sub_4D0F00_004d0f00__recomp},
    {"sub_4D1070", 0x4D1070, &recomp_gen::fn_sub_4D1070_004d1070, &recomp_gen::fn_sub_4D1070_004d1070__recomp},
    {"sub_4D1110", 0x4D1110, &recomp_gen::fn_sub_4D1110_004d1110, &recomp_gen::fn_sub_4D1110_004d1110__recomp},
    {"sub_4D1170", 0x4D1170, &recomp_gen::fn_sub_4D1170_004d1170, &recomp_gen::fn_sub_4D1170_004d1170__recomp},
    {"sub_4D11F0", 0x4D11F0, &recomp_gen::fn_sub_4D11F0_004d11f0, &recomp_gen::fn_sub_4D11F0_004d11f0__recomp},
    {"sub_4D1210", 0x4D1210, &recomp_gen::fn_sub_4D1210_004d1210, &recomp_gen::fn_sub_4D1210_004d1210__recomp},
    {"sub_4D13B0", 0x4D13B0, &recomp_gen::fn_sub_4D13B0_004d13b0, &recomp_gen::fn_sub_4D13B0_004d13b0__recomp},
    {"sub_4D1420", 0x4D1420, &recomp_gen::fn_sub_4D1420_004d1420, &recomp_gen::fn_sub_4D1420_004d1420__recomp},
    {"sub_4D15E0", 0x4D15E0, &recomp_gen::fn_sub_4D15E0_004d15e0, &recomp_gen::fn_sub_4D15E0_004d15e0__recomp},
    {"sub_4C81A0", 0x4C81A0, &recomp_gen::fn_sub_4C81A0_004c81a0, &recomp_gen::fn_sub_4C81A0_004c81a0__recomp},
    {"sub_4C81D0", 0x4C81D0, &recomp_gen::fn_sub_4C81D0_004c81d0, &recomp_gen::fn_sub_4C81D0_004c81d0__recomp},
    {"sub_4C8240", 0x4C8240, &recomp_gen::fn_sub_4C8240_004c8240, &recomp_gen::fn_sub_4C8240_004c8240__recomp},
    {"sub_4C83C0", 0x4C83C0, &recomp_gen::fn_sub_4C83C0_004c83c0, &recomp_gen::fn_sub_4C83C0_004c83c0__recomp},
    {"sub_4C8650", 0x4C8650, &recomp_gen::fn_sub_4C8650_004c8650, &recomp_gen::fn_sub_4C8650_004c8650__recomp},
    {"sub_4C8680", 0x4C8680, &recomp_gen::fn_sub_4C8680_004c8680, &recomp_gen::fn_sub_4C8680_004c8680__recomp},
    {"sub_4CDE40", 0x4CDE40, &recomp_gen::fn_sub_4CDE40_004cde40, &recomp_gen::fn_sub_4CDE40_004cde40__recomp},
    {"sub_4CDE90", 0x4CDE90, &recomp_gen::fn_sub_4CDE90_004cde90, &recomp_gen::fn_sub_4CDE90_004cde90__recomp},
    {"sub_4CDF00", 0x4CDF00, &recomp_gen::fn_sub_4CDF00_004cdf00, &recomp_gen::fn_sub_4CDF00_004cdf00__recomp},
    {"sub_4CDF30", 0x4CDF30, &recomp_gen::fn_sub_4CDF30_004cdf30, &recomp_gen::fn_sub_4CDF30_004cdf30__recomp},
    {"sub_4CDF80", 0x4CDF80, &recomp_gen::fn_sub_4CDF80_004cdf80, &recomp_gen::fn_sub_4CDF80_004cdf80__recomp},
    {"sub_4CE0F0", 0x4CE0F0, &recomp_gen::fn_sub_4CE0F0_004ce0f0, &recomp_gen::fn_sub_4CE0F0_004ce0f0__recomp},
    {"sub_4CE250", 0x4CE250, &recomp_gen::fn_sub_4CE250_004ce250, &recomp_gen::fn_sub_4CE250_004ce250__recomp},
    {"sub_4CE2C0", 0x4CE2C0, &recomp_gen::fn_sub_4CE2C0_004ce2c0, &recomp_gen::fn_sub_4CE2C0_004ce2c0__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena (the random-world sweep).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

// --- guest helpers ---------------------------------------------------------------------------------------------------
u32 ld(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void st(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void st16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void stf(Machine& m, u32 va, float f) { std::memcpy(m.at(va), &f, 4); }
float ldf(Machine& m, u32 va) {
    float f;
    std::memcpy(&f, m.at(va), 4);
    return f;
}
float frand(std::mt19937& rng, float lo, float hi) {
    return lo + (hi - lo) * static_cast<float>(rng() % 100001) / 100000.0f;
}
bool chance(std::mt19937& rng, unsigned pct) { return rng() % 100 < pct; }
template <class T>
T pick(std::mt19937& rng, const std::vector<T>& v, T fallback) {
    return v.empty() ? fallback : v[rng() % v.size()];
}

const Case& by_name(const char* n) {
    for (const Case& c : kCases)
        if (std::strcmp(c.name, n) == 0) return c;
    std::fprintf(stderr, "render_rw4 test: no case %s\n", n);
    std::abort();
}

// The RW globals the bodies read (render_rw4.h / spec): the engine instance and the modules' gp offset words.
constexpr u32 kEngine = 0x960070u;
constexpr u32 kGpMatrixOff = 0x7CE8D8u, kGpResOff = 0x7CE8F0u, kGpStreamOff = 0x7CE8F8u, kGpPluginFl = 0x7CE908u;
constexpr u32 kGpFrameOff = 0x7CE930u, kGpRasterOff = 0x7CE940u, kGpTextureOff = 0x7CE950u, kGpFlList = 0x7CE8E8u;
constexpr u32 kRegFrame = 0x77E670u, kRegCamera = 0x77E690u, kRegRaster = 0x77E6B0u, kRegTexture = 0x77E6D0u,
              kRegTexDict = 0x77E6F0u;
constexpr u32 kDirtyList = 0x96012Cu;
// Test data: free in the ELF's image and in every replay snapshot (below the stand-in heap 0x1C00000).
constexpr u32 kData = 0x01BC0000u;
constexpr u32 kDataSize = 0x00040000u;
// A function this build does not emit, served by a recorder returning 1: the callback of the walks.
constexpr u32 kCallback = 0x10A860u;

// The live entries of a free list (the used bits of each block, MSB first; sub_4C4200's entry address).
std::vector<u32> live_entries(Machine& m, u32 fl) {
    std::vector<u32> out;
    if (fl == 0 || fl >= EEMemory::kMainRamSize) return out;
    const u32 es = ld(m, fl), hs = ld(m, fl + 8), al = ld(m, fl + 12);
    if (al == 0 || hs > 64 || es == 0) return out;
    const u32 head = fl + 16;
    u32 b = ld(m, head);
    for (int nb = 0; b != head && b != 0 && b < EEMemory::kMainRamSize && nb < 256; ++nb, b = ld(m, b)) {
        const u32 base = (b + hs + al + 7) & ~(al - 1);
        for (u32 i = 0; i < hs; ++i) {
            const u8 bits = m.at(b + 8)[i];
            for (u32 k = 0; k < 8; ++k)
                if (bits & (0x80u >> k)) out.push_back(base + es * (8 * i + k));
        }
    }
    return out;
}
u32 used_bits(Machine& m, u32 fl) { return static_cast<u32>(live_entries(m, fl).size()); }

// Cuts both resource lists of the arena after `keep` entries and clears the kept entries' destroy notifications: the
// snapshots' entries all carry the PS2All instance-data release sub_49CC30, which waits for the DMA packets that still
// reference the data -- a wait no pair can end (both bodies run into the same runaway cut). The used bytes stay.
void trim_arena(Machine& m, u32 arena, u32 keep) {
    for (u32 head : {arena + 16, arena + 24}) {
        u32 e = ld(m, head), last = head;
        for (u32 n = 0; e != head && e != 0 && n < keep; ++n) st(m, e + 20, 0), last = e, e = ld(m, e);
        st(m, last, head);
        st(m, head + 4, last);
    }
}

// A geometry for the unlock path (sub_4933D0): no mesh yet, `tris` triangles over `mats` materials (8-byte triangles:
// three vertex indices and the material index; the material list {+0 the array}; a material: +0 its texture, +8 its
// pipeline), flags bit 0 = tri-strips. Returns the geometry.
u32 synthetic_geometry(Machine& m, std::mt19937& rng, u32 at, const std::vector<u32>& textures) {
    const u32 tris = 1 + rng() % 24, mats = 1 + rng() % 3, verts = 3 + rng() % 20;
    const u32 geo = at, tri = at + 0x100, matarr = at + 0x400, mat = at + 0x440;
    std::memset(m.at(at), 0, 0x600);
    st(m, geo + 8, rng() % 2);
    st(m, geo + 16, tris);
    st(m, geo + 32, matarr);
    st(m, geo + 36, mats);
    st(m, geo + 44, tri);
    for (u32 i = 0; i < mats; ++i) {
        st(m, matarr + 4 * i, mat + 32 * i);
        st(m, mat + 32 * i, textures.empty() || rng() % 3 == 0 ? 0u : textures[rng() % textures.size()]);
    }
    for (u32 i = 0; i < tris; ++i) {
        u16 a = static_cast<u16>(rng() % verts), b = static_cast<u16>(rng() % verts), c = static_cast<u16>(rng() % verts);
        if (rng() % 8 != 0) {  // mostly strip-friendly neighbours
            a = static_cast<u16>(i % verts), b = static_cast<u16>((i + 1) % verts), c = static_cast<u16>((i + 2) % verts);
        }
        st16(m, tri + 8 * i, a);
        st16(m, tri + 8 * i + 2, b);
        st16(m, tri + 8 * i + 4, c);
        st16(m, tri + 8 * i + 6, static_cast<u16>(rng() % mats));
    }
    return geo;
}

// What a snapshot holds that the bodies take as arguments.
struct Live {
    std::vector<u32> frames, children, roots, matrices, textures, dicts, rasters, resentries, freelists, plugin_ids;
    u32 frame_fl = 0, matrix_fl = 0, tex_fl = 0, dict_fl = 0, raster_fl = 0, arena = 0;
};
Live scan(Machine& m) {
    Live l;
    l.frame_fl = ld(m, kEngine + ld(m, kGpFrameOff));
    l.matrix_fl = ld(m, kEngine + ld(m, kGpMatrixOff));
    l.tex_fl = ld(m, kEngine + ld(m, kGpTextureOff) + 8);
    l.dict_fl = ld(m, kEngine + ld(m, kGpTextureOff) + 12);
    l.raster_fl = ld(m, kEngine + ld(m, kGpRasterOff) + 96);
    l.arena = kEngine + ld(m, kGpResOff);
    l.frames = live_entries(m, l.frame_fl);
    for (u32 f : l.frames) {
        if (ld(m, f + 4) != 0) l.children.push_back(f);
        else if (ld(m, f + 160) == f) l.roots.push_back(f);
    }
    l.matrices = live_entries(m, l.matrix_fl);
    l.textures = live_entries(m, l.tex_fl);
    l.dicts = live_entries(m, l.dict_fl);
    l.rasters = live_entries(m, l.raster_fl);
    for (u32 head : {l.arena + 16, l.arena + 24}) {
        u32 e = ld(m, head);
        for (int n = 0; e != head && e != 0 && n < 4096; ++n, e = ld(m, e)) l.resentries.push_back(e);
    }
    u32 p = ld(m, kGpFlList);
    for (int n = 0; p != kGpFlList && p != 0 && n < 256; ++n, p = ld(m, p)) l.freelists.push_back(p - 28);
    for (u32 reg : {kRegFrame, kRegRaster, kRegTexture, kRegTexDict})
        for (u32 e = ld(m, reg + 16), n = 0; e != 0 && n < 64; e = ld(m, e + 48), ++n) l.plugin_ids.push_back(ld(m, e + 8));
    return l;
}

// --- the pair on stand-in worlds -------------------------------------------------------------------------------------
// hgp::pair (handgen_pairs.h: the whole register file and cycles at every check point and at the return / stop, all
// 32 MiB of RAM, the scratchpad, the bus log) with a fresh stand-in world around each body (stand_ins.h: the heap
// behind the RW memory slots and the free-list entry points, printf / sprintf, the H_Cdvd layer, the recorders below);
// afterwards both worlds' call logs, live heap blocks and bad frees must be equal.
Fn g_body[2];
StandInWorld* g_world[2];
void thunk_hand(EEContext& ctx) {
    StandInsScope s(g_world[0]->si);
    g_body[0](ctx);
}
void thunk_recomp(EEContext& ctx) {
    StandInsScope s(g_world[1]->si);
    g_body[1](ctx);
}

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
    return p;
}

// The world: the standard stand-ins plus recorders for the callees this build leaves out (the RW file functions, the
// mipmap switches, the texture-by-name path, the engine-started check, the PS2 driver's device functions behind the
// standard-function table, the walks' callback).
WorldSetup rw_world(Machine& m, std::vector<std::pair<u32, u32>> blocks = {}) {
    return [&m, blocks = std::move(blocks)](StandInWorld& w) {
        install_standard(w);
        for (const auto& [p, s] : blocks) w.heap.reserve(p, s);
        w.si.install_recorder(kCallback, "callback (returns 1)", 1);
        w.si.install_recorder(0x4C0240u, "RW file open", 0);
        w.si.install_recorder(0x4C0370u, "RW file close", 0);
        w.si.install_recorder(0x4C0820u, "RW file handle check", static_cast<u64>(-1));
        w.si.install_recorder(0x4D0B60u, "mipmapping set", 1);
        w.si.install_recorder(0x4D0B80u, "mipmapping get", 0);
        w.si.install_recorder(0x4D0BA0u, "auto-mipmapping set", 1);
        w.si.install_recorder(0x4D0BC0u, "auto-mipmapping get", 0);
        w.si.install_recorder(0x4CA500u, "engine started", 1);
        w.si.install_recorder(0x4CD620u, "image copy", 0);
        w.si.install_recorder(0x4C5FC0u, "registry reset callback", 1);
        w.si.install(0x4D09D0u, "texture name compare", [&m](EEContext&, StandIns&, StandInCall& c) {
            const u32 tex = static_cast<u32>(c.args[0]), name = static_cast<u32>(c.args[1]);
            // (sub_4D1170 passes the texture's name: its link + 8)
            c.v0 = (tex < EEMemory::kMainRamSize - 64 && name < EEMemory::kMainRamSize - 64 &&
                    std::strncmp(reinterpret_cast<const char*>(m.at(tex)), reinterpret_cast<const char*>(m.at(name)), 32) == 0)
                       ? 1
                       : 0;
        });
        w.si.install(0x4D1260u, "texture by name", [&m, &w](EEContext&, StandIns&, StandInCall& c) {
            const u32 t = w.heap.alloc(96);
            std::memset(m.at(t), 0, 96);
            st(m, t + 84, 1);
            c.v0 = t;
            c.extra = 96;
        });
        w.si.install_recorder(0x4D84A0u, "raster format query", 0);
        w.si.install_recorder(0x4CF5C0u, "texture mip-name callback", 0);
        w.si.install(0x490810u, "atomic frame sync", [](EEContext&, StandIns&, StandInCall& c) { c.v0 = c.args[0]; });
        // the driver functions of the standard-function table that this build does not emit
        for (u32 va : {0x4DFCB0u, 0x4E96C0u, 0x4E97C0u, 0x4DB350u, 0x4DD2E0u, 0x4E9AA0u, 0x4EBFB0u, 0x4D9510u})
            w.si.install_recorder(va, "PS2 driver device function", 1);
    };
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

// A memory stream record over guest bytes (stream type 3, the access, position 0).
u32 mem_stream(Machine& m, u32 rec, u32 access, u32 start, u32 size) {
    std::memset(m.at(rec), 0, 36);
    st(m, rec + 0, 3);
    st(m, rec + 4, access);
    st(m, rec + 12, access == 3 ? size : 0);
    st(m, rec + 16, access == 2 ? 0 : size);
    st(m, rec + 20, access == 2 ? 0 : start);
    return rec;
}
// A chunk header in guest memory (the 3.1+ library id of version / build).
u32 libid(u32 version, u32 build) { return build | (((version - 0x30000u) & 0x3FF00u) << 14) | ((version & 0x3Fu) << 16); }
u32 put_chunk(Machine& m, u32 at, u32 type, u32 len, u32 version = 0x37002u, u32 build = 0x37u) {
    st(m, at, type);
    st(m, at + 4, len);
    st(m, at + 8, libid(version, build));
    return at + 12;
}

// The host's reading of a chunk header's library id (sub_4C1450's rule).
void decode_libid(u32 id, u32& version, u32& build) {
    if (id & 0xFFFF0000u) {
        version = (((id >> 14) & 0x3FF00u) + 0x30000u) | ((id >> 16) & 0x3Fu);
        build = id & 0xFFFFu;
    } else {
        version = id << 8;
        build = 0;
    }
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

}  // namespace

// =====================================================================================================================
// The snapshot sweep: every function on the live RenderWare state of the replay snapshots
// =====================================================================================================================
// Each pair starts from the snapshot image (frames, matrices, textures, dictionaries, rasters, free lists, the
// resource arena and the plugin registries live), with arguments of the kinds the function takes: live frames (roots
// and children), matrices (live or copies in the test area), textures, dictionaries, rasters, free lists, resEntries,
// registries with live objects, memory streams over chunk data, scratch records. The heap and the free-list entry points
// are the stand-ins'.
TEST_CASE("game(render_rw4): every body equals its recompiled body on the replay snapshots' live RenderWare state") {
    const char* const snaps[] = {"b_5800", "dorm_replay_4900", "climb_ref_17000"};
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const int per = env ? std::atoi(env) : 6;
    const char* only = std::getenv("P3FES_HG_ONLY");
    int pairs = 0, whole = 0, snapshots = 0;
    std::map<std::string, std::pair<int, std::string>> runs;  // whole runs per function, the last stop
    for (const char* sn : snaps) {
        std::vector<u8> image;
        auto mp = snapshot_machine(sn, image);
        if (!mp) {
            MESSAGE("SKIP: snapshot " << sn << " not found");
            continue;
        }
        ++snapshots;
        Machine& m = *mp;
        const Live live = scan(m);
        INFO("snapshot " << sn);
        REQUIRE(!live.frames.empty());
        MESSAGE(std::string(sn) << ": " << live.frames.size() << " frames (" << live.roots.size() << " roots), " << live.matrices.size()
                   << " matrices, " << live.textures.size() << " textures, " << live.dicts.size() << " dictionaries, "
                   << live.rasters.size() << " rasters, " << live.resentries.size() << " resEntries, " << live.freelists.size()
                   << " free lists");
        const WorldSetup world = rw_world(m);
        std::mt19937 rng{0x4F4C0000u + static_cast<u32>(snapshots)};
        for (const Case& c : kCases) {
            if (only && std::strcmp(only, c.name) != 0) continue;
            for (int k = 0; k < per; ++k) {
                std::memcpy(m.mem.main_ram(), image.data(), image.size());
                write_rw_slots(m);
                std::memset(m.at(kData), 0, kDataSize);
                const std::string n = c.name;
                const u32 scr = kData + 0x1000, scr2 = kData + 0x2000, buf = kData + 0x8000;
                for (u32 i = 0; i < 0x400; i += 4) st(m, kData + 0x3000 + i, rng() % 3 == 0 ? rng() : 0);
                auto fr = [&] { return pick(rng, live.frames, 0u); };
                auto mat = [&] { return pick(rng, live.matrices, fr() + 16); };
                auto mcopy = [&](u32 dst) {
                    std::memcpy(m.at(dst), m.at(mat()), 64);
                    return dst;
                };
                auto vec = [&](u32 at) {
                    for (int i = 0; i < 3; ++i) stf(m, at + 4 * i, frand(rng, -2.0f, 2.0f));
                    return at;
                };
                auto unit = [&](u32 at) {
                    const float x = frand(rng, -1, 1), y = frand(rng, -1, 1), z = frand(rng, -1, 1);
                    const float l = std::sqrt(x * x + y * y + z * z) + 1e-6f;
                    stf(m, at, x / l);
                    stf(m, at + 4, y / l);
                    stf(m, at + 8, z / l);
                    return at;
                };
                auto stream_over = [&](u32 rec, u32 data, u32 len) { return mem_stream(m, rec, 1, data, len); };
                // a small chunk stream: a struct chunk, an extension chunk with two plugin sub-chunks
                auto chunk_data = [&](u32 at) {
                    u32 p = put_chunk(m, at, 1, 16);
                    for (int i = 0; i < 4; ++i) st(m, p + 4 * i, rng() % 4);
                    p += 16;
                    p = put_chunk(m, p, 3, 2 * 12 + 8);
                    const u32 id1 = pick(rng, live.plugin_ids, 0x120u);
                    p = put_chunk(m, p, chance(rng, 50) ? id1 : 0x7777u, 4);
                    st(m, p, rng()), p += 4;
                    p = put_chunk(m, p, 0x7778u, 4);
                    st(m, p, rng()), p += 4;
                    return p - at;
                };
                Args a{rng(), rng(), rng(), rng()};
                HwCheck hw;
                const u32 reg = pick(rng, std::vector<u32>{kRegFrame, kRegRaster, kRegTexture, kRegTexDict}, kRegFrame);
                auto reg_obj = [&](u32 r) -> u32 {
                    if (r == kRegFrame) return fr();
                    if (r == kRegRaster) return pick(rng, live.rasters, fr());
                    if (r == kRegTexture) return pick(rng, live.textures, fr());
                    return pick(rng, live.dicts, fr());
                };
                // --- the argument kinds, by function ---
                if (n == "sub_4CA9B0") a = {kEngine, ld(m, kGpFrameOff), 0, 0};
                else if (n == "sub_4C2C00") a = {kEngine, ld(m, kGpMatrixOff), 0, 0};
                else if (n == "sub_4C46F0") a = {kEngine, ld(m, kGpResOff), 0, 0};
                else if (n == "sub_4C4EB0") a = {kEngine, ld(m, kGpStreamOff), 0, 0};
                else if (n == "sub_4D15E0") a = {kEngine, ld(m, kGpTextureOff), 0, 0};
                else if (n == "sub_4CE2C0") a = {kEngine, ld(m, kGpRasterOff), 0, 0};
                else if (n == "sub_4CAB70") a = {fr(), chance(rng, 50) ? 0u : fr(), 0, 0};
                else if (n == "sub_4CB350" || n == "sub_4CB420") {
                    // a child that is not the parent or one of its ancestors (a cycle would recurse without end)
                    const u32 par = fr();
                    u32 ch = pick(rng, live.children, fr());
                    auto ancestor = [&](u32 x) {
                        for (u32 q = par, d = 0; q != 0 && d < 64; q = ld(m, q + 4), ++d)
                            if (q == x) return true;
                        return false;
                    };
                    for (int tries = 0; tries < 16 && ancestor(ch); ++tries) ch = fr();
                    if (ancestor(ch)) ch = 0;
                    if (ch == 0) continue;
                    a = {par, ch, 0, 0};
                }
                else if (n == "sub_4CB590") a = {pick(rng, live.children, fr()), 0, 0, 0};
                else if (n == "sub_4CB6E0" || n == "sub_4D0DC0" || n == "sub_4C4200")
                    a = {n == "sub_4CB6E0" ? fr() : n == "sub_4D0DC0" ? pick(rng, live.dicts, fr()) : pick(rng, live.freelists, live.frame_fl),
                         kCallback, rng(), 0};
                else if (n == "sub_4CB890" || n == "sub_4C31B0") a = {n == "sub_4CB890" ? fr() : mcopy(scr), vec(scr2), rng() % 3, 0};
                else if (n == "sub_4C2FC0") a = {mcopy(scr), unit(scr2), rng() % 4, 0};
                else if (n == "sub_4CEFB0") a = {pick(rng, live.children, 0u), chance(rng, 50) ? 4u : 0u, 0, 0};
                else if (n == "sub_4CF0A0" || n == "sub_4CF1B0") a = {pick(rng, live.roots, fr()), 0, 0, 0};
                else if (n == "sub_4CAE40") a = {scr, 0, 0, 0};
                else if (n.rfind("sub_4CA", 0) == 0 || n.rfind("sub_4CB", 0) == 0) a = {fr(), fr(), 0, 0};
                else if (n == "sub_4C7D00" || n == "sub_4C81A0") a = {pick(rng, live.plugin_ids, 0x120u), kCallback, kCallback, kCallback};
                else if (n == "sub_4CB9F0" || n == "sub_4D13B0" || n == "sub_4CDF00") {
                    a = {rng() % 64, chance(rng, 50) ? pick(rng, live.plugin_ids, 0x120u) : 0x7700u + rng() % 16, 0, 0};
                    hw.gpr_in = {{GPR_T0, 0}};
                } else if (n == "sub_4C61B0") {
                    a = {reg, rng() % 64, chance(rng, 50) ? pick(rng, live.plugin_ids, 0x120u) : 0x7700u + rng() % 16, 0};
                    hw.gpr_in = {{GPR_T0, 0}, {GPR_T0 + 1, 0}};
                } else if (n == "sub_4C7D30") a = {scr, 0, 0, 0};
                else if (n == "sub_4C7D80") {
                    // a frame-list chunk: the struct chunk, count, 56-byte records (right, up, at, pos, parent index)
                    const u32 count = 1 + rng() % 5;
                    u32 p = put_chunk(m, buf, 1, 4 + 56 * count, chance(rng, 90) ? 0x37002u : 0x34000u);
                    st(m, p, count), p += 4;
                    for (u32 i = 0; i < count; ++i, p += 56) {
                        for (int f = 0; f < 12; ++f) stf(m, p + 4 * f, (f % 4 == f / 4) ? 1.0f : frand(rng, -0.01f, 0.01f));
                        st(m, p + 48, i == 0 ? 0xFFFFFFFFu : rng() % i);  // the parent index (an earlier frame)
                        st(m, p + 52, 0);
                    }
                    for (u32 i = 0; i < count; ++i) p = put_chunk(m, p, 3, 0);
                    a = {stream_over(scr2, buf, p - buf), scr, 0, 0};
                } else if (n == "sub_4C2200") a = {scr, mat(), mat(), 0};
                else if (n == "sub_4C2D20") a = {mcopy(scr), chance(rng, 50) ? 0u : scr2, 0, 0};
                else if (n == "sub_4C2F10" || n == "sub_4C2A70" || n == "sub_4C2AC0" || n == "sub_4C2B20") a = {mcopy(scr), 0, 0, 0};
                else if (n == "sub_4C3880") a = {mat(), 0, 0, 0};
                else if (n == "sub_4C2A30") a = {chance(rng, 50) ? 0u : 0x4C2200u, 0, 0, 0};
                else if (n == "sub_4C2CC0" || n == "sub_4C2CF0") a = {vec(scr), 0, 0, 0};
                else if (n == "sub_4C19F0") {
                    u32 p = put_chunk(m, buf, 1, 64, chance(rng, 90) ? 0x37002u : 0x40000u);
                    for (int f = 0; f < 12; ++f) stf(m, p + 4 * f, frand(rng, -1, 1));
                    st(m, p + 48, rng() % 4);
                    a = {stream_over(scr2, buf, chance(rng, 80) ? 12 + 52 : 12 + 20), chance(rng, 50) ? 0u : scr, 0, 0};
                } else if (n == "sub_4C3970" || n == "sub_4C3B50" || n == "sub_4C3B60") {
                    a = {1 + rng() % 200, 1 + rng() % 40, chance(rng, 30) ? 0u : (4u << (rng() % 3)), rng() % 3};
                    hw.gpr_in = {{GPR_T0, chance(rng, 50) ? 0u : scr}, {GPR_T0 + 1, 0x40000u}};
                } else if (n == "sub_4C3B70" || n == "sub_4C3C30" || n == "sub_4C4080")
                    a = {pick(rng, live.freelists, live.frame_fl), 0, 0, 0};
                else if (n == "sub_4C3960" || n == "sub_4C7CF0") a = {rng() % 2, 0, 0, 0};
                else if (n == "sub_4C45F0") a = {scr, chance(rng, 30) ? 0u : 0x400u + (rng() % 8) * 0x100u, 0, 0};
                else if (n == "sub_4C47E0") a = {pick(rng, live.resentries, scr), 0, 0, 0};
                else if (n == "sub_4C4930") {
                    a = {fr(), scr, 16 + rng() % 0x4000, 0};
                    hw.gpr_in = {};
                } else if (n == "RwResourcesSetArenaSize") {
                    trim_arena(m, live.arena, 8 + rng() % 24);
                    a = {0x1000u + (rng() % 64) * 0x1000u, 0, 0, 0};
                }
                else if (n == "sub_4C6DF0") a = {scr, rng() % 0x200, 0, 0};
                else if (n == "sub_4C12D0") {
                    st(m, scr, rng() % 30);
                    a = {scr, 0, 0, 0};
                } else if (n == "sub_4C1450" || n == "sub_4C1970" || n == "sub_4C1600" || n == "sub_4C5EA0" || n == "sub_4C5A50") {
                    const u32 len = chunk_data(buf);
                    const u32 s = stream_over(scr2, buf, chance(rng, 85) ? len : rng() % len);
                    if (n == "sub_4C1450") a = {s, scr, scr + 4, scr + 8};
                    else if (n == "sub_4C1970") a = {s, scr, 0, 0};
                    else if (n == "sub_4C1600") a = {s, chance(rng, 70) ? 3u : 1u + rng() % 8, scr, scr + 4};
                    else if (n == "sub_4C5EA0") a = {reg, s, 0, 0};
                    else {
                        // the extension chunk first: skip the struct chunk
                        st(m, s + 12, 28);
                        a = {reg, s, reg_obj(reg), 0};
                    }
                    if (n == "sub_4C1450") hw.gpr_in = {{GPR_T0, scr + 12}};
                } else if (n == "sub_4C15A0" || n == "sub_4C1750" || n == "sub_4C17F0" || n == "sub_4C1820" || n == "sub_4C53F0") {
                    const u32 s = mem_stream(m, scr2, 2 + rng() % 2, 0, 0);
                    if (chance(rng, 50)) {  // a stream that already has a buffer on the stand-in heap
                        st(m, s + 20, buf);
                        st(m, s + 16, 512);
                        st(m, s + 12, rng() % 512);
                    }
                    if (n == "sub_4C15A0") {
                        a = {s, rng() % 32, rng() % 0x1000, 0x35000u + rng() % 0x2003};
                        hw.gpr_in = {{GPR_T0, rng() % 0x100}};
                    } else a = {s, vec(scr), chance(rng, 70) ? 4u * (1 + rng() % 3) : rng() % 1200, 0};
                } else if (n == "sub_4C1850" || n == "sub_4C18B0" || n == "sub_4C1910" || n == "sub_4C5250" || n == "sub_4C5620") {
                    const u32 len = chunk_data(buf);
                    const u32 s = stream_over(scr2, buf, len);
                    st(m, s + 12, rng() % len);
                    a = {s, n == "sub_4C5620" ? rng() % (2 * len) : scr, rng() % 64, 0};
                    if (n == "sub_4C5620") a[1] = rng() % 64;
                } else if (n == "sub_4C5780") {
                    const u32 s = mem_stream(m, scr2, 1 + rng() % 3, buf, 64);
                    st(m, s + 32, 0);
                    a = {s, chance(rng, 50) ? 0u : scr, 0, 0};
                } else if (n == "sub_4C5090") {
                    st(m, scr2, buf);
                    st(m, scr2 + 4, 0x100);
                    a = {scr, rng() % 5, scr2, 0};
                } else if (n == "sub_4C5140") {
                    st(m, scr2, buf);
                    st(m, scr2 + 4, 0x100);
                    a = {scr, rng() % 2, 1 + rng() % 5, 1 + rng() % 3};
                    hw.gpr_in = {{GPR_T0, scr2}};
                } else if (n == "sub_4C4F90") a = {scr, rng() % 5, buf, 0};
                else if (n == "sub_4C58A0") {
                    st(m, scr2, buf);
                    st(m, scr2 + 4, 0x100);
                    a = {3, 1 + rng() % 3, scr2, 0};
                } else if (n == "sub_4C5C30") a = {reg, pick(rng, live.plugin_ids, 0x120u), reg_obj(reg), 0};
                else if (n == "sub_4C5CB0" || n == "sub_4C64B0" || n == "sub_4C6560") a = {reg, reg_obj(reg), 0, 0};
                else if (n == "sub_4C65D0") a = {reg, reg_obj(reg), reg_obj(reg), 0};
                else if (n == "sub_4C5D30") a = {reg, mem_stream(m, scr2, 2, 0, 0), reg_obj(reg), 0};
                else if (n == "sub_4D0D10" || n == "sub_4D11F0") a = {pick(rng, live.dicts, scr), 0, 0, 0};
                else if (n == "sub_4D0E40") a = {pick(rng, live.rasters, 0u), 0, 0, 0};
                else if (n == "sub_4D0F00" || n == "sub_4C81D0" || n == "sub_4C8650") a = {pick(rng, live.textures, scr), 0, 0, 0};
                else if (n == "sub_4D1070") {
                    const std::string nm = chance(rng, 70) ? "mask" + std::to_string(rng() % 100) : std::string(40, 'x');
                    m.put(scr, nm);
                    a = {pick(rng, live.textures, scr2), scr, 0, 0};
                } else if (n == "sub_4D1110") a = {pick(rng, live.dicts, scr), pick(rng, live.textures, scr2), 0, 0};
                else if (n == "sub_4D1170") {
                    const u32 t = pick(rng, live.textures, 0u);
                    if (t && chance(rng, 70)) std::memcpy(m.at(scr), m.at(t + 16), 32);
                    else m.put(scr, "no such texture");
                    a = {pick(rng, live.dicts, scr2), scr, 0, 0};
                } else if (n == "sub_4C8240") a = {pick(rng, live.textures, scr), mem_stream(m, scr2, 2, 0, 0), 0, 0};
                else if (n == "sub_4C83C0") {
                    u32 p = put_chunk(m, buf, 1, 4, chance(rng, 90) ? 0x37002u : 0x30000u);
                    st(m, p, rng() & 0x1FFFFu), p += 4;
                    p = put_chunk(m, p, 2, 16), m.put(p, "tex" + std::to_string(rng() % 10)), p += 16;
                    p = put_chunk(m, p, 2, 16), m.put(p, ""), p += 16;
                    p = put_chunk(m, p, 3, 0);
                    a = {stream_over(scr2, buf, p - buf), 0, 0, 0};
                } else if (n == "sub_4C8680") {
                    u32 p = put_chunk(m, buf, 1, 4, chance(rng, 90) ? 0x37002u : 0x30000u);
                    st16(m, p, static_cast<u16>(rng() % 2));
                    st16(m, p + 2, static_cast<u16>(rng() % 3));
                    p += 4;
                    p = put_chunk(m, p, 21, 0);
                    p = put_chunk(m, p, 3, 0);
                    a = {stream_over(scr2, buf, p - buf), 0, 0, 0};
                } else if (n.rfind("sub_4CDE", 0) == 0 || n.rfind("sub_4CDF", 0) == 0 || n == "sub_4E4E90")
                    a = {pick(rng, live.rasters, scr), rng() % 4, 0, 0};
                else if (n == "sub_4CE0F0") a = {u64{1} << (rng() % 9), u64{1} << (rng() % 9), u64{4} << (rng() % 4), (rng() % 8) | ((rng() % 8) << 8)};
                else if (n == "sub_4DE0A0") a = {scr, pick(rng, live.rasters, scr2), rng() % 8, 0};
                else if (n == "sub_4E53E0" || n == "sub_4E6D60" || n == "sub_4E8610") {
                    for (int i = 0; i < 4; ++i) stf(m, scr + 4 * i, frand(rng, 0, 512));
                    a = {pick(rng, live.rasters, scr2), pick(rng, live.rasters, scr2), scr, rng() % 4};
                } else if (n == "sub_4EFA00") a = {pick(rng, live.rasters, scr2), pick(rng, live.rasters, scr2), rng(), rng()};
                else if (n == "sub_4CBF20" || n == "sub_4CC1D0") {
                    for (u32 img : {scr, scr2}) {
                        std::memset(m.at(img), 0, 28);
                        st(m, img + 4, 1 + rng() % 16);
                        st(m, img + 8, 1 + rng() % 16);
                        st(m, img + 12, pick(rng, std::vector<u32>{4, 8, 32, 16}, 32u));
                    }
                    if (n == "sub_4CC1D0") {
                        // the image needs its pixels: give both 32-bit pixel blocks in the test area
                        st(m, scr2 + 4, ld(m, scr + 4));
                        if (chance(rng, 80)) st(m, scr2 + 8, ld(m, scr + 8));
                        st(m, scr + 12, 32), st(m, scr + 16, 4 * ld(m, scr + 4)), st(m, scr + 20, buf);
                        st(m, scr2 + 16, 4 * ld(m, scr2 + 4)), st(m, scr2 + 20, buf + 0x2000), st(m, scr2 + 24, buf + 0x3000);
                        for (u32 i = 0; i < 0x4000; i += 4) st(m, buf + i, rng());
                    }
                    a = {scr, scr2, 0, 0};
                } else if (n == "sub_4C1E70") {
                    st(m, scr, buf), st(m, scr + 4, rng() % 9), st(m, scr + 8, 8), st(m, scr + 12, 4 + 4 * (rng() % 4));
                    a = {scr, 0x30000u, 0, 0};
                } else if (n == "sub_4F61C0") {
                    st(m, scr + 12, buf), st(m, scr + 16, 32), st(m, scr + 20, chance(rng, 50) ? 32u : rng() % 32);
                    for (u32 i = 0; i < 32; ++i) st(m, buf + 8 * i + 4, scr2 + 16 * i);
                    a = {scr, 0, 0, 0};
                } else if (n == "sub_495CF0") {
                    st(m, scr, rng() % 4), st(m, scr + 4, rng() % 4), st(m, scr + 8, 0);
                    a = {scr, fr(), rng() % 100, rng() % 100};
                    hw.gpr_in = {{GPR_T0, rng() % 100}, {GPR_T0 + 1, rng() % 100}, {GPR_T0 + 2, rng() % 100}, {GPR_T0 + 3, rng() % 100}};
                } else if (n == "sub_4967A0") {
                    const u32 ntri = 1 + rng() % 12;
                    for (u32 i = 0; i < 3 * ntri; ++i) st16(m, buf + 2 * i, static_cast<u16>(chance(rng, 3) ? 0xFFFFu : rng() % 16));
                    st(m, scr, buf), st(m, scr + 4, 3 * ntri);
                    a = {scr, 0, 0, 0};
                } else if (n == "sub_49E5A0") {
                    if (chance(rng, 50)) {
                        st(m, scr, 0);
                    } else {
                        st(m, scr, scr2), st(m, scr2, 2);
                        st(m, scr2 + 4, pick(rng, live.resentries, 0u)), st(m, scr2 + 8, 0);
                    }
                    a = {scr, 1 + rng() % 6, 0, 0};
                } else if (n == "sub_4AB0E0") {
                    st(m, scr, chance(rng, 50) ? 0u : buf), st(m, scr + 4, chance(rng, 50) ? 0xFFFFFFFFu : 0u), st(m, scr + 20, rng());
                    a = {scr, 0, 0, 0};
                } else if (n == "sub_47BB40") {
                    a = {scr, rng() % 8, rng() % 4, 0};
                }
                else if (n == "sub_4C4D70" || n == "sub_4C4750" || n == "RwResourcesSetArenaSize") {
                    trim_arena(m, live.arena, 8 + rng() % 24);
                } else if (n == "sub_4933D0") {
                    a = {synthetic_geometry(m, rng, buf, live.textures), 0, 0, 0};
                } else if (n == "sub_498E70") {
                    // a build mesh {+0 capacity, +4 count, +8 20-byte records: indices, material at +8}
                    const u32 cnt = 1 + rng() % 16, rec = buf + 0x100;
                    st(m, scr, cnt), st(m, scr + 4, cnt), st(m, scr + 8, rec);
                    for (u32 i = 0; i < cnt; ++i) {
                        for (u32 k = 0; k < 3; ++k) st16(m, rec + 20 * i + 2 * k, static_cast<u16>(rng() % 12));
                        st(m, rec + 20 * i + 8, scr2 + 32 * (rng() % 3));
                    }
                    a = {scr, 0, 0, 0};
                } else if (n == "sub_4A08F0" || n == "sub_4A0CE0") {
                    // a PS2All object {+8 the object, +36 'use the arena'}; the object: type byte (0xFF = a world sector),
                    // +24 its geometry; the geometry's flags +8 (bit 25 = native)
                    const u32 obj = scr2, geo = scr2 + 0x100;
                    st(m, scr + 8, obj), st(m, scr + 36, chance(rng, 30) ? 1u : 0u);
                    m.at(obj)[0] = chance(rng, 30) ? 0xFFu : 1u;
                    st(m, obj + 24, geo), st(m, geo + 8, chance(rng, 50) ? 0x2000000u : 0u);
                    a = {scr, kData + 0x3800, 64 + rng() % 0x2000, 0};
                }
                // (the rest: the module closes, the getters, the PTank bodies: random words)
                if (std::getenv("P3FES_HG_TRACE")) std::fprintf(stderr, "%s %s pair %d a0=%08x a1=%08x\n", sn, c.name, k, static_cast<u32>(a[0]), static_cast<u32>(a[1]));
                const WPair p = wpair(m, c, a, 900000u + static_cast<u32>(pairs), world, hw);
                ++pairs;
                whole += p.run.stopped ? 0 : 1;
                auto& r = runs[c.name];
                r.first += p.run.stopped ? 0 : 1;
                if (p.run.stopped) r.second = p.run.what + " at " + hex64(p.run.stop_pc);
            }
        }
    }
    MESSAGE("snapshot pairs: " << pairs << " on " << snapshots << " snapshots, run whole " << whole);
    std::string never;
    for (const auto& [name, r] : runs)
        if (r.first == 0) never += name + " (" + r.second + ") ";
    if (!never.empty()) MESSAGE("never run whole on the snapshots: " << never);
}

// =====================================================================================================================
// Documented rules on the real objects (host checks of what the bodies left)
// =====================================================================================================================
TEST_CASE("game(render_rw4): the frame hierarchy rules on the battle snapshot's frames") {
    std::vector<u8> image;
    auto mp = snapshot_machine("b_5800", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot b_5800 not found");
        return;
    }
    Machine& m = *mp;
    const Live live = scan(m);
    REQUIRE(live.children.size() > 4);
    const WorldSetup world = rw_world(m);
    std::mt19937 rng{0x4CB590u};
    int checked = 0;
    for (int i = 0; i < 24; ++i) {
        std::memcpy(m.mem.main_ram(), image.data(), image.size());
        write_rw_slots(m);
        const u32 child = live.children[rng() % live.children.size()];
        const u32 parent = ld(m, child + 4);
        const bool was_listed = (m.at(child)[3] & 3) != 0;
        // sub_4CB590: the child is its own root, out of the parent's list, and its root joins the dirty list
        const WPair p = wpair(m, by_name("sub_4CB590"), {child, 0, 0, 0}, 777000u + i, world);
        REQUIRE(!p.run.stopped);
        CHECK(p.v0() == child);
        CHECK(ld(m, child + 4) == 0);
        CHECK(ld(m, child + 160) == child);
        CHECK((m.at(child)[3] & 0x0F) == 0x0F);
        if (!was_listed) CHECK(ld(m, kDirtyList) == child + 8);
        for (u32 c = ld(m, parent + 152), n = 0; c != 0 && n < 512; c = ld(m, c + 156), ++n) CHECK(c != child);
        // the subtree's frames now point at the child as their root
        for (u32 c = ld(m, child + 152), n = 0; c != 0 && n < 64; c = ld(m, c + 156), ++n) CHECK(ld(m, c + 160) == child);
        // sub_4CB420 puts it back at the head of the parent's list, with the parent's root
        const WPair q = wpair(m, by_name("sub_4CB420"), {parent, child, 0, 0}, 778000u + i, world);
        REQUIRE(!q.run.stopped);
        CHECK(ld(m, parent + 152) == child);
        CHECK(ld(m, child + 4) == parent);
        CHECK(ld(m, child + 160) == ld(m, parent + 160));
        ++checked;
    }
    MESSAGE("hierarchy checks: " << checked);
}

TEST_CASE("game(render_rw4): frame create / matrix create give identity records with flags 0x20003") {
    std::vector<u8> image;
    auto mp = snapshot_machine("b_5800", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot b_5800 not found");
        return;
    }
    Machine& m = *mp;
    const WorldSetup world = rw_world(m);
    for (int i = 0; i < 8; ++i) {
        std::memcpy(m.mem.main_ram(), image.data(), image.size());
        write_rw_slots(m);
        const WPair f = wpair(m, by_name("sub_4CAF10"), {0, 0, 0, 0}, 779000u + i, world);
        REQUIRE(!f.run.stopped);
        const u32 fr = f.v0();
        REQUIRE(fr != 0);
        CHECK(f.recomp->si.log.size() >= 1);
        CHECK(f.recomp->si.log[0].va == 0x4C3D10u);  // the frame free list (slot 0x960188)
        for (u32 mtx : {fr + 16, fr + 80}) {
            CHECK(ldf(m, mtx) == 1.0f);
            CHECK(ldf(m, mtx + 20) == 1.0f);
            CHECK(ldf(m, mtx + 40) == 1.0f);
            CHECK(ldf(m, mtx + 48) == 0.0f);
            CHECK(ld(m, mtx + 12) == 0x20003u);
        }
        CHECK(ld(m, fr + 160) == fr);
        CHECK(ld(m, fr + 144) == fr + 144);
        const WPair x = wpair(m, by_name("sub_4C38C0"), {0, 0, 0, 0}, 779100u + i, world);
        REQUIRE(!x.run.stopped);
        REQUIRE(x.v0() != 0);
        CHECK(ld(m, x.v0() + 12) == 0x20003u);
        CHECK(ldf(m, x.v0() + 40) == 1.0f);
    }
}

TEST_CASE("game(render_rw4): matrix multiply, determinant and rotation agree with the host's arithmetic") {
    std::vector<u8> image;
    auto mp = snapshot_machine("b_5800", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot b_5800 not found");
        return;
    }
    Machine& m = *mp;
    const WorldSetup world = rw_world(m);
    std::mt19937 rng{0x4C2200u};
    const u32 A = kData, B = kData + 0x100, D = kData + 0x200, AX = kData + 0x300;
    for (int i = 0; i < 40; ++i) {
        std::memset(m.at(kData), 0, 0x400);
        float a[16], b[16];
        for (int k = 0; k < 16; ++k) {
            a[k] = (k % 4 == 3) ? 0.0f : frand(rng, -2, 2);
            b[k] = (k % 4 == 3) ? 0.0f : frand(rng, -2, 2);
            stf(m, A + 4 * k, a[k]);
            stf(m, B + 4 * k, b[k]);
        }
        const WPair p = wpair(m, by_name("sub_4C2200"), {D, A, B, 0}, 780000u + i, world);
        for (int r = 0; r < 4; ++r)
            for (int col = 0; col < 3; ++col) {
                float want = (r == 3 ? b[12 + col] : 0.0f);
                for (int k = 0; k < 3; ++k) want += a[4 * r + k] * b[4 * k + col];
                CHECK(std::fabs(ldf(m, D + 16 * r + 4 * col) - want) < 1e-3f);
            }
        const WPair d = wpair(m, by_name("sub_4C2A70"), {A, 0, 0, 0}, 780100u + i, world);
        const float det = a[0] * (a[5] * a[10] - a[6] * a[9]) - a[1] * (a[4] * a[10] - a[6] * a[8]) + a[2] * (a[4] * a[9] - a[5] * a[8]);
        float got;
        std::memcpy(&got, &d.run.end.fpr[0], 4);
        CHECK(std::fabs(got - det) < 1e-2f);
        // rotate the identity about a unit axis by 90 degrees (replace): the axis stays, a perpendicular one turns
        for (int k = 0; k < 16; ++k) stf(m, A + 4 * k, (k == 0 || k == 5 || k == 10) ? 1.0f : 0.0f);
        st(m, A + 12, 0x20003u);
        stf(m, AX, 0.0f), stf(m, AX + 4, 0.0f), stf(m, AX + 8, 1.0f);
        HwCheck hw;
        hw.gpr_in = {};
        const WPair r = wpair(m, by_name("sub_4C31B0"), {A, AX, 0, 0}, 780200u + i, world, hw);
        CHECK(r.v0() == A);
        CHECK(ld(m, A + 12) == 3u);  // the rotation's flags: orthogonal + normal
    }
}

TEST_CASE("game(render_rw4): the chunk-header reader on a real RMD file (BTL/MODEL/FACILITYP/FP000.RMD)") {
    std::vector<u8> image;
    auto mp = snapshot_machine("b_5800", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot b_5800 not found");
        return;
    }
    Machine& m = *mp;
    const std::vector<u8> file = read_host_file(extracted_root() + "/BTL/MODEL/FACILITYP/FP000.RMD");
    if (file.size() < 64 || file.size() > kDataSize - 0x10000) {
        MESSAGE("SKIP: FP000.RMD not found");
        return;
    }
    const WorldSetup world = rw_world(m);
    const u32 S = kData, OUT = kData + 0x100, DATA = kData + 0x10000;
    std::memcpy(m.at(DATA), file.data(), file.size());
    // walk the top-level chunks: header, then skip the payload; the host decodes the same headers
    u32 off = 0;
    int chunks = 0;
    mem_stream(m, S, 1, DATA, static_cast<u32>(file.size()));
    while (off + 12 <= file.size() && chunks < 64) {
        u32 type, len, id;
        std::memcpy(&type, file.data() + off, 4);
        std::memcpy(&len, file.data() + off + 4, 4);
        std::memcpy(&id, file.data() + off + 8, 4);
        u32 ver, build;
        decode_libid(id, ver, build);
        HwCheck hw;
        hw.gpr_in = {{GPR_T0, OUT + 12}};
        const WPair p = wpair(m, by_name("sub_4C1450"), {S, OUT, OUT + 4, OUT + 8}, 781000u + chunks, world, hw);
        REQUIRE(!p.run.stopped);
        CHECK(p.v0() == 1);
        CHECK(ld(m, OUT) == type);
        CHECK(ld(m, OUT + 4) == len);
        CHECK(ld(m, OUT + 8) == ver);
        CHECK(ld(m, OUT + 12) == build);
        if (off + 12 + len > file.size()) break;
        const WPair s = wpair(m, by_name("sub_4C5620"), {S, len, 0, 0}, 782000u + chunks, world);
        CHECK(s.v0() == S);
        off += 12 + len;
        CHECK(ld(m, S + 12) == off);
        ++chunks;
    }
    MESSAGE("FP000.RMD: " << chunks << " top-level chunks read");
    CHECK(chunks >= 2);
    // find the texture dictionary (type 0x16) from the start; the payload length and version are the header's
    mem_stream(m, S, 1, DATA, static_cast<u32>(file.size()));
    const WPair f = wpair(m, by_name("sub_4C1600"), {S, 0x16, OUT, OUT + 4}, 783000u, world);
    if (f.v0() == 1) {
        u32 at = 0, type = 0, len = 0, id = 0;
        for (; at + 12 <= file.size(); at += 12 + len) {
            std::memcpy(&type, file.data() + at, 4);
            std::memcpy(&len, file.data() + at + 4, 4);
            std::memcpy(&id, file.data() + at + 8, 4);
            if (type == 0x16) break;
        }
        u32 ver, build;
        decode_libid(id, ver, build);
        CHECK(ld(m, OUT) == len);
        CHECK(ld(m, OUT + 4) == ver);
        CHECK(ld(m, S + 12) == at + 12);
        // the dictionary reader over the real chunk (the device's native read is the snapshot's driver function)
        const WPair d = wpair(m, by_name("sub_4C8680"), {S, 0, 0, 0}, 784000u, world);
        MESSAGE("texture dictionary read: " << (d.run.stopped ? "stopped at " + hex64(d.run.stop_pc) : "returned " + hex64(d.v0())));
    }
}

TEST_CASE("game(render_rw4): the free-list walk visits exactly the used entries (the host reads the same bitmaps)") {
    std::vector<u8> image;
    auto mp = snapshot_machine("b_5800", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot b_5800 not found");
        return;
    }
    Machine& m = *mp;
    const Live live = scan(m);
    const WorldSetup world = rw_world(m);
    int lists = 0;
    for (u32 fl : live.freelists) {
        std::memcpy(m.mem.main_ram(), image.data(), image.size());
        write_rw_slots(m);
        const std::vector<u32> used = live_entries(m, fl);
        const WPair p = wpair(m, by_name("sub_4C4200"), {fl, kCallback, 0x1234, 0}, 785000u + lists, world);
        if (p.run.stopped) continue;
        std::vector<u32> visited;
        for (const StandInCall& c : p.recomp->si.log)
            if (c.va == kCallback) {
                visited.push_back(static_cast<u32>(c.args[0]));
                CHECK(static_cast<u32>(c.args[1]) == 0x1234u);
            }
        CHECK(visited == used);
        ++lists;
    }
    MESSAGE("free lists walked: " << lists);
    CHECK(lists > 10);
}

TEST_CASE("game(render_rw4): the resource arena -- usage, the frame flip and allocate / free on the live arena") {
    std::vector<u8> image;
    auto mp = snapshot_machine("b_5800", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot b_5800 not found");
        return;
    }
    Machine& m = *mp;
    const Live live = scan(m);
    const WorldSetup world = rw_world(m);
    const u32 ar = live.arena;
    // usage = the evicted count + the sizes in this frame's list
    u32 want = ld(m, ar + 8);
    for (u32 head = ld(m, ar + 36), e = ld(m, head), n = 0; e != head && n < 4096; e = ld(m, e), ++n) want += ld(m, e + 8);
    const WPair u = wpair(m, by_name("sub_4C4D20"), {0, 0, 0, 0}, 786000u, world);
    CHECK(u.v0() == want);
    // the flip: the two list pointers swap and the evicted count is 0
    const u32 older = ld(m, ar + 32), current = ld(m, ar + 36);
    const WPair f = wpair(m, by_name("sub_4C4890"), {0, 0, 0, 0}, 786001u, world);
    CHECK(ld(m, ar + 32) == current);
    CHECK(ld(m, ar + 36) == older);
    CHECK(ld(m, ar + 8) == 0);
    CHECK(ld(m, older) == older);  // the new current list is empty
    // allocate entries until the arena evicts; every allocation is linked at the head of this frame's list
    std::mt19937 rng{0x4C4930u};
    int allocs = 0;
    for (int i = 0; i < 24; ++i) {
        const u32 owner_ref = kData + 4 * i;
        const WPair p = wpair(m, by_name("sub_4C4930"), {0x1234, owner_ref, 64 + rng() % 0x8000, 0}, 786100u + i, world);
        if (p.run.stopped) break;
        if (p.v0() != 0) {
            CHECK(ld(m, owner_ref) == p.v0());
            CHECK(ld(m, ld(m, ar + 36)) == p.v0());
            CHECK(ld(m, p.v0() + 12) == 0x1234u);
            ++allocs;
        }
    }
    MESSAGE("arena allocations: " << allocs);
    // empty the arena (cut to a few entries first): both lists are empty, nothing evicted
    trim_arena(m, ar, 16);
    const WPair e = wpair(m, by_name("sub_4C4D70"), {0, 0, 0, 0}, 786200u, world);
    CHECK(e.v0() == 1);
    CHECK(ld(m, ar + 16) == ar + 16);
    CHECK(ld(m, ar + 24) == ar + 24);
}

TEST_CASE("game(render_rw4): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
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

TEST_CASE("game(render_rw4): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
