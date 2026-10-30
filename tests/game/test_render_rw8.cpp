// Pair tests of slice render_rw8 (game/src/render/render_rw8.cpp): RenderWare, eighth pass -- the RxPipeline core
// (create, lock, fragments, paths, find node, the unlock with its sort and cluster passes, the RxHeap), the PDS / PTank /
// Im3D pipe constructors, Rt2d objects and animation, image files, RtQuat, the palette quantiser. Every body runs against
// its recompiled body and tests/game/handgen_pairs.h compares the whole register file and cycles at every check point
// and at the return / stop, all 32 MiB of RAM (the dead stack included), the scratchpad, the BIOS window and the bus log;
// the stand-ins' call logs and heaps must be equal too (stand_ins.h). A sequence of calls can run as one pair in one
// stand-in world (wseq: a pipeline created, locked, given fragments, unlocked).
//   * a lock / unlock round trip of every live pipeline of the three snapshots, compared node by node with the live one;
//   * the PDS / PTank / Im3D constructors rebuilding the live pipelines, compared node by node;
//   * a pipeline built from scratch out of test node definitions: the topological order, the cluster slots, the entry
//     point, RxPipelineFindNodeByName, RxLockedPipeAddPath's refusals, the node limit;
//   * RtQuat against host math; Rt2d's object-list walks on built lists;
//   * every body on the snapshots with built records, and the random-world sweep (the p3fes_handgen skeleton).
// P3FES_HG_SEEDS sets the pairs per function of the random sweep, P3FES_HG_ONLY one function, P3FES_HG_TRACE traces.
// Every random draw is its own statement (argument evaluation order differs between MSVC and clang-cl).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/render_rw8.h"

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
void fn_sub_45EC20_0045ec20(EEContext&);  // generated body
void fn_sub_45EC20_0045ec20__recomp(EEContext&);  // recompiled
void fn_sub_45F580_0045f580(EEContext&);  // generated body
void fn_sub_45F580_0045f580__recomp(EEContext&);  // recompiled
void fn_sub_45F7D0_0045f7d0(EEContext&);  // generated body
void fn_sub_45F7D0_0045f7d0__recomp(EEContext&);  // recompiled
void fn_sub_46A600_0046a600(EEContext&);  // generated body
void fn_sub_46A600_0046a600__recomp(EEContext&);  // recompiled
void fn_RpPDSRegisterPipe_0046a830(EEContext&);  // generated body
void fn_RpPDSRegisterPipe_0046a830__recomp(EEContext&);  // recompiled
void fn_sub_46A8D0_0046a8d0(EEContext&);  // generated body
void fn_sub_46A8D0_0046a8d0__recomp(EEContext&);  // recompiled
void fn_PDSRegistryAddPipe_0046aa80(EEContext&);  // generated body
void fn_PDSRegistryAddPipe_0046aa80__recomp(EEContext&);  // recompiled
void fn_sub_46AC30_0046ac30(EEContext&);  // generated body
void fn_sub_46AC30_0046ac30__recomp(EEContext&);  // recompiled
void fn_RpPDSSkyMatPipeCreate_0046ad80(EEContext&);  // generated body
void fn_RpPDSSkyMatPipeCreate_0046ad80__recomp(EEContext&);  // recompiled
void fn_sub_46AFA0_0046afa0(EEContext&);  // generated body
void fn_sub_46AFA0_0046afa0__recomp(EEContext&);  // recompiled
void fn_sub_474BB0_00474bb0(EEContext&);  // generated body
void fn_sub_474BB0_00474bb0__recomp(EEContext&);  // recompiled
void fn_sub_474C60_00474c60(EEContext&);  // generated body
void fn_sub_474C60_00474c60__recomp(EEContext&);  // recompiled
void fn_rpSpr2dGenCreatePS2AllMatPipe_00478a70(EEContext&);  // generated body
void fn_rpSpr2dGenCreatePS2AllMatPipe_00478a70__recomp(EEContext&);  // recompiled
void fn_sub_479030_00479030(EEContext&);  // generated body
void fn_sub_479030_00479030__recomp(EEContext&);  // recompiled
void fn_rpSpr3dGenCreatePS2AllMatPipe_00479e50(EEContext&);  // generated body
void fn_rpSpr3dGenCreatePS2AllMatPipe_00479e50__recomp(EEContext&);  // recompiled
void fn_sub_47A3D0_0047a3d0(EEContext&);  // generated body
void fn_sub_47A3D0_0047a3d0__recomp(EEContext&);  // recompiled
void fn_sub_47AB70_0047ab70(EEContext&);  // generated body
void fn_sub_47AB70_0047ab70__recomp(EEContext&);  // recompiled
void fn_sub_47B1A0_0047b1a0(EEContext&);  // generated body
void fn_sub_47B1A0_0047b1a0__recomp(EEContext&);  // recompiled
void fn_sub_48F030_0048f030(EEContext&);  // generated body
void fn_sub_48F030_0048f030__recomp(EEContext&);  // recompiled
void fn_sub_48F580_0048f580(EEContext&);  // generated body
void fn_sub_48F580_0048f580__recomp(EEContext&);  // recompiled
void fn_sub_48FBD0_0048fbd0(EEContext&);  // generated body
void fn_sub_48FBD0_0048fbd0__recomp(EEContext&);  // recompiled
void fn_sub_499A80_00499a80(EEContext&);  // generated body
void fn_sub_499A80_00499a80__recomp(EEContext&);  // recompiled
void fn_sub_499AF0_00499af0(EEContext&);  // generated body
void fn_sub_499AF0_00499af0__recomp(EEContext&);  // recompiled
void fn_sub_49C680_0049c680(EEContext&);  // generated body
void fn_sub_49C680_0049c680__recomp(EEContext&);  // recompiled
void fn_sub_49C6C0_0049c6c0(EEContext&);  // generated body
void fn_sub_49C6C0_0049c6c0__recomp(EEContext&);  // recompiled
void fn_sub_49C810_0049c810(EEContext&);  // generated body
void fn_sub_49C810_0049c810__recomp(EEContext&);  // recompiled
void fn_sub_49C8C0_0049c8c0(EEContext&);  // generated body
void fn_sub_49C8C0_0049c8c0__recomp(EEContext&);  // recompiled
void fn_sub_49C9B0_0049c9b0(EEContext&);  // generated body
void fn_sub_49C9B0_0049c9b0__recomp(EEContext&);  // recompiled
void fn_sub_4A30D0_004a30d0(EEContext&);  // generated body
void fn_sub_4A30D0_004a30d0__recomp(EEContext&);  // recompiled
void fn_PS2AllMatPipelineNodeInit_004a3540(EEContext&);  // generated body
void fn_PS2AllMatPipelineNodeInit_004a3540__recomp(EEContext&);  // recompiled
void fn_sub_4A9A80_004a9a80(EEContext&);  // generated body
void fn_sub_4A9A80_004a9a80__recomp(EEContext&);  // recompiled
void fn_sub_4AC240_004ac240(EEContext&);  // generated body
void fn_sub_4AC240_004ac240__recomp(EEContext&);  // recompiled
void fn_sub_4AC410_004ac410(EEContext&);  // generated body
void fn_sub_4AC410_004ac410__recomp(EEContext&);  // recompiled
void fn_sub_4AC710_004ac710(EEContext&);  // generated body
void fn_sub_4AC710_004ac710__recomp(EEContext&);  // recompiled
void fn_sub_4AD480_004ad480(EEContext&);  // generated body
void fn_sub_4AD480_004ad480__recomp(EEContext&);  // recompiled
void fn_sub_4AD5B0_004ad5b0(EEContext&);  // generated body
void fn_sub_4AD5B0_004ad5b0__recomp(EEContext&);  // recompiled
void fn_sub_4AD700_004ad700(EEContext&);  // generated body
void fn_sub_4AD700_004ad700__recomp(EEContext&);  // recompiled
void fn_sub_4AD940_004ad940(EEContext&);  // generated body
void fn_sub_4AD940_004ad940__recomp(EEContext&);  // recompiled
void fn_sub_4ADC90_004adc90(EEContext&);  // generated body
void fn_sub_4ADC90_004adc90__recomp(EEContext&);  // recompiled
void fn_sub_4ADCC0_004adcc0(EEContext&);  // generated body
void fn_sub_4ADCC0_004adcc0__recomp(EEContext&);  // recompiled
void fn_sub_4AE150_004ae150(EEContext&);  // generated body
void fn_sub_4AE150_004ae150__recomp(EEContext&);  // recompiled
void fn_sub_4B0B10_004b0b10(EEContext&);  // generated body
void fn_sub_4B0B10_004b0b10__recomp(EEContext&);  // recompiled
void fn_sub_4B0FA0_004b0fa0(EEContext&);  // generated body
void fn_sub_4B0FA0_004b0fa0__recomp(EEContext&);  // recompiled
void fn_sub_4B1420_004b1420(EEContext&);  // generated body
void fn_sub_4B1420_004b1420__recomp(EEContext&);  // recompiled
void fn_sub_4B14C0_004b14c0(EEContext&);  // generated body
void fn_sub_4B14C0_004b14c0__recomp(EEContext&);  // recompiled
void fn_sub_4B1500_004b1500(EEContext&);  // generated body
void fn_sub_4B1500_004b1500__recomp(EEContext&);  // recompiled
void fn_sub_4B1700_004b1700(EEContext&);  // generated body
void fn_sub_4B1700_004b1700__recomp(EEContext&);  // recompiled
void fn_sub_4B1870_004b1870(EEContext&);  // generated body
void fn_sub_4B1870_004b1870__recomp(EEContext&);  // recompiled
void fn_sub_4B1D00_004b1d00(EEContext&);  // generated body
void fn_sub_4B1D00_004b1d00__recomp(EEContext&);  // recompiled
void fn_sub_4B22B0_004b22b0(EEContext&);  // generated body
void fn_sub_4B22B0_004b22b0__recomp(EEContext&);  // recompiled
void fn_sub_4B2300_004b2300(EEContext&);  // generated body
void fn_sub_4B2300_004b2300__recomp(EEContext&);  // recompiled
void fn_sub_4B2BF0_004b2bf0(EEContext&);  // generated body
void fn_sub_4B2BF0_004b2bf0__recomp(EEContext&);  // recompiled
void fn_sub_4B2C80_004b2c80(EEContext&);  // generated body
void fn_sub_4B2C80_004b2c80__recomp(EEContext&);  // recompiled
void fn_sub_4B4450_004b4450(EEContext&);  // generated body
void fn_sub_4B4450_004b4450__recomp(EEContext&);  // recompiled
void fn_sub_4B5270_004b5270(EEContext&);  // generated body
void fn_sub_4B5270_004b5270__recomp(EEContext&);  // recompiled
void fn_sub_4B5380_004b5380(EEContext&);  // generated body
void fn_sub_4B5380_004b5380__recomp(EEContext&);  // recompiled
void fn_sub_4B56D0_004b56d0(EEContext&);  // generated body
void fn_sub_4B56D0_004b56d0__recomp(EEContext&);  // recompiled
void fn_sub_4B5B50_004b5b50(EEContext&);  // generated body
void fn_sub_4B5B50_004b5b50__recomp(EEContext&);  // recompiled
void fn_sub_4B9840_004b9840(EEContext&);  // generated body
void fn_sub_4B9840_004b9840__recomp(EEContext&);  // recompiled
void fn_sub_4B9870_004b9870(EEContext&);  // generated body
void fn_sub_4B9870_004b9870__recomp(EEContext&);  // recompiled
void fn_sub_4B99A0_004b99a0(EEContext&);  // generated body
void fn_sub_4B99A0_004b99a0__recomp(EEContext&);  // recompiled
void fn_sub_4B9BA0_004b9ba0(EEContext&);  // generated body
void fn_sub_4B9BA0_004b9ba0__recomp(EEContext&);  // recompiled
void fn_sub_4B9D40_004b9d40(EEContext&);  // generated body
void fn_sub_4B9D40_004b9d40__recomp(EEContext&);  // recompiled
void fn_sub_4B9E00_004b9e00(EEContext&);  // generated body
void fn_sub_4B9E00_004b9e00__recomp(EEContext&);  // recompiled
void fn_sub_4BA2A0_004ba2a0(EEContext&);  // generated body
void fn_sub_4BA2A0_004ba2a0__recomp(EEContext&);  // recompiled
void fn_sub_4BAD50_004bad50(EEContext&);  // generated body
void fn_sub_4BAD50_004bad50__recomp(EEContext&);  // recompiled
void fn_sub_4BC830_004bc830(EEContext&);  // generated body
void fn_sub_4BC830_004bc830__recomp(EEContext&);  // recompiled
void fn_sub_4BCA00_004bca00(EEContext&);  // generated body
void fn_sub_4BCA00_004bca00__recomp(EEContext&);  // recompiled
void fn_sub_4BCAE0_004bcae0(EEContext&);  // generated body
void fn_sub_4BCAE0_004bcae0__recomp(EEContext&);  // recompiled
void fn_sub_4BCB20_004bcb20(EEContext&);  // generated body
void fn_sub_4BCB20_004bcb20__recomp(EEContext&);  // recompiled
void fn_sub_4BCB30_004bcb30(EEContext&);  // generated body
void fn_sub_4BCB30_004bcb30__recomp(EEContext&);  // recompiled
void fn_sub_4BCBF0_004bcbf0(EEContext&);  // generated body
void fn_sub_4BCBF0_004bcbf0__recomp(EEContext&);  // recompiled
void fn_sub_4BDB30_004bdb30(EEContext&);  // generated body
void fn_sub_4BDB30_004bdb30__recomp(EEContext&);  // recompiled
void fn_sub_4BDBB0_004bdbb0(EEContext&);  // generated body
void fn_sub_4BDBB0_004bdbb0__recomp(EEContext&);  // recompiled
void fn_sub_4BDC30_004bdc30(EEContext&);  // generated body
void fn_sub_4BDC30_004bdc30__recomp(EEContext&);  // recompiled
void fn_sub_4BDCB0_004bdcb0(EEContext&);  // generated body
void fn_sub_4BDCB0_004bdcb0__recomp(EEContext&);  // recompiled
void fn_sub_4BDDE0_004bdde0(EEContext&);  // generated body
void fn_sub_4BDDE0_004bdde0__recomp(EEContext&);  // recompiled
void fn_sub_4BE1E0_004be1e0(EEContext&);  // generated body
void fn_sub_4BE1E0_004be1e0__recomp(EEContext&);  // recompiled
void fn_sub_4BE310_004be310(EEContext&);  // generated body
void fn_sub_4BE310_004be310__recomp(EEContext&);  // recompiled
void fn_sub_4BE930_004be930(EEContext&);  // generated body
void fn_sub_4BE930_004be930__recomp(EEContext&);  // recompiled
void fn_sub_4D1900_004d1900(EEContext&);  // generated body
void fn_sub_4D1900_004d1900__recomp(EEContext&);  // recompiled
void fn_sub_4D1A50_004d1a50(EEContext&);  // generated body
void fn_sub_4D1A50_004d1a50__recomp(EEContext&);  // recompiled
void fn_sub_4D1C30_004d1c30(EEContext&);  // generated body
void fn_sub_4D1C30_004d1c30__recomp(EEContext&);  // recompiled
void fn_sub_4D1DF0_004d1df0(EEContext&);  // generated body
void fn_sub_4D1DF0_004d1df0__recomp(EEContext&);  // recompiled
void fn_sub_4D1F10_004d1f10(EEContext&);  // generated body
void fn_sub_4D1F10_004d1f10__recomp(EEContext&);  // recompiled
void fn_sub_4D2030_004d2030(EEContext&);  // generated body
void fn_sub_4D2030_004d2030__recomp(EEContext&);  // recompiled
void fn_sub_4D2130_004d2130(EEContext&);  // generated body
void fn_sub_4D2130_004d2130__recomp(EEContext&);  // recompiled
void fn_sub_4D22F0_004d22f0(EEContext&);  // generated body
void fn_sub_4D22F0_004d22f0__recomp(EEContext&);  // recompiled
void fn_sub_4D2730_004d2730(EEContext&);  // generated body
void fn_sub_4D2730_004d2730__recomp(EEContext&);  // recompiled
void fn_sub_4D2900_004d2900(EEContext&);  // generated body
void fn_sub_4D2900_004d2900__recomp(EEContext&);  // recompiled
void fn_sub_4D2B50_004d2b50(EEContext&);  // generated body
void fn_sub_4D2B50_004d2b50__recomp(EEContext&);  // recompiled
void fn_sub_4D2D60_004d2d60(EEContext&);  // generated body
void fn_sub_4D2D60_004d2d60__recomp(EEContext&);  // recompiled
void fn_sub_4D2ED0_004d2ed0(EEContext&);  // generated body
void fn_sub_4D2ED0_004d2ed0__recomp(EEContext&);  // recompiled
void fn_sub_4D3040_004d3040(EEContext&);  // generated body
void fn_sub_4D3040_004d3040__recomp(EEContext&);  // recompiled
void fn_sub_4D3120_004d3120(EEContext&);  // generated body
void fn_sub_4D3120_004d3120__recomp(EEContext&);  // recompiled
void fn_sub_4D3220_004d3220(EEContext&);  // generated body
void fn_sub_4D3220_004d3220__recomp(EEContext&);  // recompiled
void fn_sub_4D3300_004d3300(EEContext&);  // generated body
void fn_sub_4D3300_004d3300__recomp(EEContext&);  // recompiled
void fn_sub_4D3800_004d3800(EEContext&);  // generated body
void fn_sub_4D3800_004d3800__recomp(EEContext&);  // recompiled
void fn_sub_4D3FC0_004d3fc0(EEContext&);  // generated body
void fn_sub_4D3FC0_004d3fc0__recomp(EEContext&);  // recompiled
void fn_sub_4D40E0_004d40e0(EEContext&);  // generated body
void fn_sub_4D40E0_004d40e0__recomp(EEContext&);  // recompiled
void fn_sub_4D41E0_004d41e0(EEContext&);  // generated body
void fn_sub_4D41E0_004d41e0__recomp(EEContext&);  // recompiled
void fn_sub_4D8320_004d8320(EEContext&);  // generated body
void fn_sub_4D8320_004d8320__recomp(EEContext&);  // recompiled
void fn_sub_4F22B0_004f22b0(EEContext&);  // generated body
void fn_sub_4F22B0_004f22b0__recomp(EEContext&);  // recompiled
void fn_sub_4F2730_004f2730(EEContext&);  // generated body
void fn_sub_4F2730_004f2730__recomp(EEContext&);  // recompiled
void fn_sub_4F2790_004f2790(EEContext&);  // generated body
void fn_sub_4F2790_004f2790__recomp(EEContext&);  // recompiled
void fn_sub_4F2870_004f2870(EEContext&);  // generated body
void fn_sub_4F2870_004f2870__recomp(EEContext&);  // recompiled
void fn_sub_4F28A0_004f28a0(EEContext&);  // generated body
void fn_sub_4F28A0_004f28a0__recomp(EEContext&);  // recompiled
void fn_sub_4F28D0_004f28d0(EEContext&);  // generated body
void fn_sub_4F28D0_004f28d0__recomp(EEContext&);  // recompiled
void fn_sub_4F28F0_004f28f0(EEContext&);  // generated body
void fn_sub_4F28F0_004f28f0__recomp(EEContext&);  // recompiled
void fn_sub_4F2990_004f2990(EEContext&);  // generated body
void fn_sub_4F2990_004f2990__recomp(EEContext&);  // recompiled
void fn_sub_4F2A00_004f2a00(EEContext&);  // generated body
void fn_sub_4F2A00_004f2a00__recomp(EEContext&);  // recompiled
void fn_sub_4F2F70_004f2f70(EEContext&);  // generated body
void fn_sub_4F2F70_004f2f70__recomp(EEContext&);  // recompiled
void fn_sub_4F30E0_004f30e0(EEContext&);  // generated body
void fn_sub_4F30E0_004f30e0__recomp(EEContext&);  // recompiled
void fn_sub_4F31C0_004f31c0(EEContext&);  // generated body
void fn_sub_4F31C0_004f31c0__recomp(EEContext&);  // recompiled
void fn_sub_4F3260_004f3260(EEContext&);  // generated body
void fn_sub_4F3260_004f3260__recomp(EEContext&);  // recompiled
void fn_sub_4F3410_004f3410(EEContext&);  // generated body
void fn_sub_4F3410_004f3410__recomp(EEContext&);  // recompiled
void fn_sub_4F3680_004f3680(EEContext&);  // generated body
void fn_sub_4F3680_004f3680__recomp(EEContext&);  // recompiled
void fn_sub_4F3880_004f3880(EEContext&);  // generated body
void fn_sub_4F3880_004f3880__recomp(EEContext&);  // recompiled
void fn_sub_4F3970_004f3970(EEContext&);  // generated body
void fn_sub_4F3970_004f3970__recomp(EEContext&);  // recompiled
void fn_sub_4F3D60_004f3d60(EEContext&);  // generated body
void fn_sub_4F3D60_004f3d60__recomp(EEContext&);  // recompiled
void fn_sub_4F3F80_004f3f80(EEContext&);  // generated body
void fn_sub_4F3F80_004f3f80__recomp(EEContext&);  // recompiled
void fn_sub_4F4640_004f4640(EEContext&);  // generated body
void fn_sub_4F4640_004f4640__recomp(EEContext&);  // recompiled
void fn_sub_4F4830_004f4830(EEContext&);  // generated body
void fn_sub_4F4830_004f4830__recomp(EEContext&);  // recompiled
void fn_sub_4F4950_004f4950(EEContext&);  // generated body
void fn_sub_4F4950_004f4950__recomp(EEContext&);  // recompiled
void fn_sub_4F4C30_004f4c30(EEContext&);  // generated body
void fn_sub_4F4C30_004f4c30__recomp(EEContext&);  // recompiled
void fn_sub_4F4CF0_004f4cf0(EEContext&);  // generated body
void fn_sub_4F4CF0_004f4cf0__recomp(EEContext&);  // recompiled
void fn_sub_4F4DB0_004f4db0(EEContext&);  // generated body
void fn_sub_4F4DB0_004f4db0__recomp(EEContext&);  // recompiled
void fn_sub_4F4FE0_004f4fe0(EEContext&);  // generated body
void fn_sub_4F4FE0_004f4fe0__recomp(EEContext&);  // recompiled
void fn_sub_4F50A0_004f50a0(EEContext&);  // generated body
void fn_sub_4F50A0_004f50a0__recomp(EEContext&);  // recompiled
void fn_sub_4F5520_004f5520(EEContext&);  // generated body
void fn_sub_4F5520_004f5520__recomp(EEContext&);  // recompiled
void fn_sub_4F57F0_004f57f0(EEContext&);  // generated body
void fn_sub_4F57F0_004f57f0__recomp(EEContext&);  // recompiled
void fn_sub_4F5A90_004f5a90(EEContext&);  // generated body
void fn_sub_4F5A90_004f5a90__recomp(EEContext&);  // recompiled
void fn_sub_4F5B80_004f5b80(EEContext&);  // generated body
void fn_sub_4F5B80_004f5b80__recomp(EEContext&);  // recompiled
void fn_sub_4F5C50_004f5c50(EEContext&);  // generated body
void fn_sub_4F5C50_004f5c50__recomp(EEContext&);  // recompiled
void fn_sub_4F5D90_004f5d90(EEContext&);  // generated body
void fn_sub_4F5D90_004f5d90__recomp(EEContext&);  // recompiled
void fn_sub_4F6140_004f6140(EEContext&);  // generated body
void fn_sub_4F6140_004f6140__recomp(EEContext&);  // recompiled
void fn_sub_4F63D0_004f63d0(EEContext&);  // generated body
void fn_sub_4F63D0_004f63d0__recomp(EEContext&);  // recompiled
void fn_sub_4F64F0_004f64f0(EEContext&);  // generated body
void fn_sub_4F64F0_004f64f0__recomp(EEContext&);  // recompiled
void fn_sub_4F65B0_004f65b0(EEContext&);  // generated body
void fn_sub_4F65B0_004f65b0__recomp(EEContext&);  // recompiled
void fn_sub_4F67B0_004f67b0(EEContext&);  // generated body
void fn_sub_4F67B0_004f67b0__recomp(EEContext&);  // recompiled
void fn_sub_4F6970_004f6970(EEContext&);  // generated body
void fn_sub_4F6970_004f6970__recomp(EEContext&);  // recompiled
void fn_sub_4F6A10_004f6a10(EEContext&);  // generated body
void fn_sub_4F6A10_004f6a10__recomp(EEContext&);  // recompiled
void fn_sub_4F6B50_004f6b50(EEContext&);  // generated body
void fn_sub_4F6B50_004f6b50__recomp(EEContext&);  // recompiled
void fn_sub_4F6CE0_004f6ce0(EEContext&);  // generated body
void fn_sub_4F6CE0_004f6ce0__recomp(EEContext&);  // recompiled
void fn_sub_4F6F20_004f6f20(EEContext&);  // generated body
void fn_sub_4F6F20_004f6f20__recomp(EEContext&);  // recompiled
void fn_sub_4F7080_004f7080(EEContext&);  // generated body
void fn_sub_4F7080_004f7080__recomp(EEContext&);  // recompiled
void fn_sub_4F72C0_004f72c0(EEContext&);  // generated body
void fn_sub_4F72C0_004f72c0__recomp(EEContext&);  // recompiled
void fn_sub_4F72D0_004f72d0(EEContext&);  // generated body
void fn_sub_4F72D0_004f72d0__recomp(EEContext&);  // recompiled
void fn_sub_4F72E0_004f72e0(EEContext&);  // generated body
void fn_sub_4F72E0_004f72e0__recomp(EEContext&);  // recompiled
void fn_sub_4F72F0_004f72f0(EEContext&);  // generated body
void fn_sub_4F72F0_004f72f0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_45EC20", 0x45EC20, &recomp_gen::fn_sub_45EC20_0045ec20, &recomp_gen::fn_sub_45EC20_0045ec20__recomp},
    {"sub_45F580", 0x45F580, &recomp_gen::fn_sub_45F580_0045f580, &recomp_gen::fn_sub_45F580_0045f580__recomp},
    {"sub_45F7D0", 0x45F7D0, &recomp_gen::fn_sub_45F7D0_0045f7d0, &recomp_gen::fn_sub_45F7D0_0045f7d0__recomp},
    {"sub_46A600", 0x46A600, &recomp_gen::fn_sub_46A600_0046a600, &recomp_gen::fn_sub_46A600_0046a600__recomp},
    {"RpPDSRegisterPipe", 0x46A830, &recomp_gen::fn_RpPDSRegisterPipe_0046a830, &recomp_gen::fn_RpPDSRegisterPipe_0046a830__recomp},
    {"sub_46A8D0", 0x46A8D0, &recomp_gen::fn_sub_46A8D0_0046a8d0, &recomp_gen::fn_sub_46A8D0_0046a8d0__recomp},
    {"PDSRegistryAddPipe", 0x46AA80, &recomp_gen::fn_PDSRegistryAddPipe_0046aa80, &recomp_gen::fn_PDSRegistryAddPipe_0046aa80__recomp},
    {"sub_46AC30", 0x46AC30, &recomp_gen::fn_sub_46AC30_0046ac30, &recomp_gen::fn_sub_46AC30_0046ac30__recomp},
    {"RpPDSSkyMatPipeCreate", 0x46AD80, &recomp_gen::fn_RpPDSSkyMatPipeCreate_0046ad80, &recomp_gen::fn_RpPDSSkyMatPipeCreate_0046ad80__recomp},
    {"sub_46AFA0", 0x46AFA0, &recomp_gen::fn_sub_46AFA0_0046afa0, &recomp_gen::fn_sub_46AFA0_0046afa0__recomp},
    {"sub_474BB0", 0x474BB0, &recomp_gen::fn_sub_474BB0_00474bb0, &recomp_gen::fn_sub_474BB0_00474bb0__recomp},
    {"sub_474C60", 0x474C60, &recomp_gen::fn_sub_474C60_00474c60, &recomp_gen::fn_sub_474C60_00474c60__recomp},
    {"rpSpr2dGenCreatePS2AllMatPipe", 0x478A70, &recomp_gen::fn_rpSpr2dGenCreatePS2AllMatPipe_00478a70, &recomp_gen::fn_rpSpr2dGenCreatePS2AllMatPipe_00478a70__recomp},
    {"sub_479030", 0x479030, &recomp_gen::fn_sub_479030_00479030, &recomp_gen::fn_sub_479030_00479030__recomp},
    {"rpSpr3dGenCreatePS2AllMatPipe", 0x479E50, &recomp_gen::fn_rpSpr3dGenCreatePS2AllMatPipe_00479e50, &recomp_gen::fn_rpSpr3dGenCreatePS2AllMatPipe_00479e50__recomp},
    {"sub_47A3D0", 0x47A3D0, &recomp_gen::fn_sub_47A3D0_0047a3d0, &recomp_gen::fn_sub_47A3D0_0047a3d0__recomp},
    {"sub_47AB70", 0x47AB70, &recomp_gen::fn_sub_47AB70_0047ab70, &recomp_gen::fn_sub_47AB70_0047ab70__recomp},
    {"sub_47B1A0", 0x47B1A0, &recomp_gen::fn_sub_47B1A0_0047b1a0, &recomp_gen::fn_sub_47B1A0_0047b1a0__recomp},
    {"sub_48F030", 0x48F030, &recomp_gen::fn_sub_48F030_0048f030, &recomp_gen::fn_sub_48F030_0048f030__recomp},
    {"sub_48F580", 0x48F580, &recomp_gen::fn_sub_48F580_0048f580, &recomp_gen::fn_sub_48F580_0048f580__recomp},
    {"sub_48FBD0", 0x48FBD0, &recomp_gen::fn_sub_48FBD0_0048fbd0, &recomp_gen::fn_sub_48FBD0_0048fbd0__recomp},
    {"sub_499A80", 0x499A80, &recomp_gen::fn_sub_499A80_00499a80, &recomp_gen::fn_sub_499A80_00499a80__recomp},
    {"sub_499AF0", 0x499AF0, &recomp_gen::fn_sub_499AF0_00499af0, &recomp_gen::fn_sub_499AF0_00499af0__recomp},
    {"sub_49C680", 0x49C680, &recomp_gen::fn_sub_49C680_0049c680, &recomp_gen::fn_sub_49C680_0049c680__recomp},
    {"sub_49C6C0", 0x49C6C0, &recomp_gen::fn_sub_49C6C0_0049c6c0, &recomp_gen::fn_sub_49C6C0_0049c6c0__recomp},
    {"sub_49C810", 0x49C810, &recomp_gen::fn_sub_49C810_0049c810, &recomp_gen::fn_sub_49C810_0049c810__recomp},
    {"sub_49C8C0", 0x49C8C0, &recomp_gen::fn_sub_49C8C0_0049c8c0, &recomp_gen::fn_sub_49C8C0_0049c8c0__recomp},
    {"sub_49C9B0", 0x49C9B0, &recomp_gen::fn_sub_49C9B0_0049c9b0, &recomp_gen::fn_sub_49C9B0_0049c9b0__recomp},
    {"sub_4A30D0", 0x4A30D0, &recomp_gen::fn_sub_4A30D0_004a30d0, &recomp_gen::fn_sub_4A30D0_004a30d0__recomp},
    {"PS2AllMatPipelineNodeInit", 0x4A3540, &recomp_gen::fn_PS2AllMatPipelineNodeInit_004a3540, &recomp_gen::fn_PS2AllMatPipelineNodeInit_004a3540__recomp},
    {"sub_4A9A80", 0x4A9A80, &recomp_gen::fn_sub_4A9A80_004a9a80, &recomp_gen::fn_sub_4A9A80_004a9a80__recomp},
    {"sub_4AC240", 0x4AC240, &recomp_gen::fn_sub_4AC240_004ac240, &recomp_gen::fn_sub_4AC240_004ac240__recomp},
    {"sub_4AC410", 0x4AC410, &recomp_gen::fn_sub_4AC410_004ac410, &recomp_gen::fn_sub_4AC410_004ac410__recomp},
    {"sub_4AC710", 0x4AC710, &recomp_gen::fn_sub_4AC710_004ac710, &recomp_gen::fn_sub_4AC710_004ac710__recomp},
    {"sub_4AD480", 0x4AD480, &recomp_gen::fn_sub_4AD480_004ad480, &recomp_gen::fn_sub_4AD480_004ad480__recomp},
    {"sub_4AD5B0", 0x4AD5B0, &recomp_gen::fn_sub_4AD5B0_004ad5b0, &recomp_gen::fn_sub_4AD5B0_004ad5b0__recomp},
    {"sub_4AD700", 0x4AD700, &recomp_gen::fn_sub_4AD700_004ad700, &recomp_gen::fn_sub_4AD700_004ad700__recomp},
    {"sub_4AD940", 0x4AD940, &recomp_gen::fn_sub_4AD940_004ad940, &recomp_gen::fn_sub_4AD940_004ad940__recomp},
    {"sub_4ADC90", 0x4ADC90, &recomp_gen::fn_sub_4ADC90_004adc90, &recomp_gen::fn_sub_4ADC90_004adc90__recomp},
    {"sub_4ADCC0", 0x4ADCC0, &recomp_gen::fn_sub_4ADCC0_004adcc0, &recomp_gen::fn_sub_4ADCC0_004adcc0__recomp},
    {"sub_4AE150", 0x4AE150, &recomp_gen::fn_sub_4AE150_004ae150, &recomp_gen::fn_sub_4AE150_004ae150__recomp},
    {"sub_4B0B10", 0x4B0B10, &recomp_gen::fn_sub_4B0B10_004b0b10, &recomp_gen::fn_sub_4B0B10_004b0b10__recomp},
    {"sub_4B0FA0", 0x4B0FA0, &recomp_gen::fn_sub_4B0FA0_004b0fa0, &recomp_gen::fn_sub_4B0FA0_004b0fa0__recomp},
    {"sub_4B1420", 0x4B1420, &recomp_gen::fn_sub_4B1420_004b1420, &recomp_gen::fn_sub_4B1420_004b1420__recomp},
    {"sub_4B14C0", 0x4B14C0, &recomp_gen::fn_sub_4B14C0_004b14c0, &recomp_gen::fn_sub_4B14C0_004b14c0__recomp},
    {"sub_4B1500", 0x4B1500, &recomp_gen::fn_sub_4B1500_004b1500, &recomp_gen::fn_sub_4B1500_004b1500__recomp},
    {"sub_4B1700", 0x4B1700, &recomp_gen::fn_sub_4B1700_004b1700, &recomp_gen::fn_sub_4B1700_004b1700__recomp},
    {"sub_4B1870", 0x4B1870, &recomp_gen::fn_sub_4B1870_004b1870, &recomp_gen::fn_sub_4B1870_004b1870__recomp},
    {"sub_4B1D00", 0x4B1D00, &recomp_gen::fn_sub_4B1D00_004b1d00, &recomp_gen::fn_sub_4B1D00_004b1d00__recomp},
    {"sub_4B22B0", 0x4B22B0, &recomp_gen::fn_sub_4B22B0_004b22b0, &recomp_gen::fn_sub_4B22B0_004b22b0__recomp},
    {"sub_4B2300", 0x4B2300, &recomp_gen::fn_sub_4B2300_004b2300, &recomp_gen::fn_sub_4B2300_004b2300__recomp},
    {"sub_4B2BF0", 0x4B2BF0, &recomp_gen::fn_sub_4B2BF0_004b2bf0, &recomp_gen::fn_sub_4B2BF0_004b2bf0__recomp},
    {"sub_4B2C80", 0x4B2C80, &recomp_gen::fn_sub_4B2C80_004b2c80, &recomp_gen::fn_sub_4B2C80_004b2c80__recomp},
    {"sub_4B4450", 0x4B4450, &recomp_gen::fn_sub_4B4450_004b4450, &recomp_gen::fn_sub_4B4450_004b4450__recomp},
    {"sub_4B5270", 0x4B5270, &recomp_gen::fn_sub_4B5270_004b5270, &recomp_gen::fn_sub_4B5270_004b5270__recomp},
    {"sub_4B5380", 0x4B5380, &recomp_gen::fn_sub_4B5380_004b5380, &recomp_gen::fn_sub_4B5380_004b5380__recomp},
    {"sub_4B56D0", 0x4B56D0, &recomp_gen::fn_sub_4B56D0_004b56d0, &recomp_gen::fn_sub_4B56D0_004b56d0__recomp},
    {"sub_4B5B50", 0x4B5B50, &recomp_gen::fn_sub_4B5B50_004b5b50, &recomp_gen::fn_sub_4B5B50_004b5b50__recomp},
    {"sub_4B9840", 0x4B9840, &recomp_gen::fn_sub_4B9840_004b9840, &recomp_gen::fn_sub_4B9840_004b9840__recomp},
    {"sub_4B9870", 0x4B9870, &recomp_gen::fn_sub_4B9870_004b9870, &recomp_gen::fn_sub_4B9870_004b9870__recomp},
    {"sub_4B99A0", 0x4B99A0, &recomp_gen::fn_sub_4B99A0_004b99a0, &recomp_gen::fn_sub_4B99A0_004b99a0__recomp},
    {"sub_4B9BA0", 0x4B9BA0, &recomp_gen::fn_sub_4B9BA0_004b9ba0, &recomp_gen::fn_sub_4B9BA0_004b9ba0__recomp},
    {"sub_4B9D40", 0x4B9D40, &recomp_gen::fn_sub_4B9D40_004b9d40, &recomp_gen::fn_sub_4B9D40_004b9d40__recomp},
    {"sub_4B9E00", 0x4B9E00, &recomp_gen::fn_sub_4B9E00_004b9e00, &recomp_gen::fn_sub_4B9E00_004b9e00__recomp},
    {"sub_4BA2A0", 0x4BA2A0, &recomp_gen::fn_sub_4BA2A0_004ba2a0, &recomp_gen::fn_sub_4BA2A0_004ba2a0__recomp},
    {"sub_4BAD50", 0x4BAD50, &recomp_gen::fn_sub_4BAD50_004bad50, &recomp_gen::fn_sub_4BAD50_004bad50__recomp},
    {"sub_4BC830", 0x4BC830, &recomp_gen::fn_sub_4BC830_004bc830, &recomp_gen::fn_sub_4BC830_004bc830__recomp},
    {"sub_4BCA00", 0x4BCA00, &recomp_gen::fn_sub_4BCA00_004bca00, &recomp_gen::fn_sub_4BCA00_004bca00__recomp},
    {"sub_4BCAE0", 0x4BCAE0, &recomp_gen::fn_sub_4BCAE0_004bcae0, &recomp_gen::fn_sub_4BCAE0_004bcae0__recomp},
    {"sub_4BCB20", 0x4BCB20, &recomp_gen::fn_sub_4BCB20_004bcb20, &recomp_gen::fn_sub_4BCB20_004bcb20__recomp},
    {"sub_4BCB30", 0x4BCB30, &recomp_gen::fn_sub_4BCB30_004bcb30, &recomp_gen::fn_sub_4BCB30_004bcb30__recomp},
    {"sub_4BCBF0", 0x4BCBF0, &recomp_gen::fn_sub_4BCBF0_004bcbf0, &recomp_gen::fn_sub_4BCBF0_004bcbf0__recomp},
    {"sub_4BDB30", 0x4BDB30, &recomp_gen::fn_sub_4BDB30_004bdb30, &recomp_gen::fn_sub_4BDB30_004bdb30__recomp},
    {"sub_4BDBB0", 0x4BDBB0, &recomp_gen::fn_sub_4BDBB0_004bdbb0, &recomp_gen::fn_sub_4BDBB0_004bdbb0__recomp},
    {"sub_4BDC30", 0x4BDC30, &recomp_gen::fn_sub_4BDC30_004bdc30, &recomp_gen::fn_sub_4BDC30_004bdc30__recomp},
    {"sub_4BDCB0", 0x4BDCB0, &recomp_gen::fn_sub_4BDCB0_004bdcb0, &recomp_gen::fn_sub_4BDCB0_004bdcb0__recomp},
    {"sub_4BDDE0", 0x4BDDE0, &recomp_gen::fn_sub_4BDDE0_004bdde0, &recomp_gen::fn_sub_4BDDE0_004bdde0__recomp},
    {"sub_4BE1E0", 0x4BE1E0, &recomp_gen::fn_sub_4BE1E0_004be1e0, &recomp_gen::fn_sub_4BE1E0_004be1e0__recomp},
    {"sub_4BE310", 0x4BE310, &recomp_gen::fn_sub_4BE310_004be310, &recomp_gen::fn_sub_4BE310_004be310__recomp},
    {"sub_4BE930", 0x4BE930, &recomp_gen::fn_sub_4BE930_004be930, &recomp_gen::fn_sub_4BE930_004be930__recomp},
    {"sub_4D1900", 0x4D1900, &recomp_gen::fn_sub_4D1900_004d1900, &recomp_gen::fn_sub_4D1900_004d1900__recomp},
    {"sub_4D1A50", 0x4D1A50, &recomp_gen::fn_sub_4D1A50_004d1a50, &recomp_gen::fn_sub_4D1A50_004d1a50__recomp},
    {"sub_4D1C30", 0x4D1C30, &recomp_gen::fn_sub_4D1C30_004d1c30, &recomp_gen::fn_sub_4D1C30_004d1c30__recomp},
    {"sub_4D1DF0", 0x4D1DF0, &recomp_gen::fn_sub_4D1DF0_004d1df0, &recomp_gen::fn_sub_4D1DF0_004d1df0__recomp},
    {"sub_4D1F10", 0x4D1F10, &recomp_gen::fn_sub_4D1F10_004d1f10, &recomp_gen::fn_sub_4D1F10_004d1f10__recomp},
    {"sub_4D2030", 0x4D2030, &recomp_gen::fn_sub_4D2030_004d2030, &recomp_gen::fn_sub_4D2030_004d2030__recomp},
    {"sub_4D2130", 0x4D2130, &recomp_gen::fn_sub_4D2130_004d2130, &recomp_gen::fn_sub_4D2130_004d2130__recomp},
    {"sub_4D22F0", 0x4D22F0, &recomp_gen::fn_sub_4D22F0_004d22f0, &recomp_gen::fn_sub_4D22F0_004d22f0__recomp},
    {"sub_4D2730", 0x4D2730, &recomp_gen::fn_sub_4D2730_004d2730, &recomp_gen::fn_sub_4D2730_004d2730__recomp},
    {"sub_4D2900", 0x4D2900, &recomp_gen::fn_sub_4D2900_004d2900, &recomp_gen::fn_sub_4D2900_004d2900__recomp},
    {"sub_4D2B50", 0x4D2B50, &recomp_gen::fn_sub_4D2B50_004d2b50, &recomp_gen::fn_sub_4D2B50_004d2b50__recomp},
    {"sub_4D2D60", 0x4D2D60, &recomp_gen::fn_sub_4D2D60_004d2d60, &recomp_gen::fn_sub_4D2D60_004d2d60__recomp},
    {"sub_4D2ED0", 0x4D2ED0, &recomp_gen::fn_sub_4D2ED0_004d2ed0, &recomp_gen::fn_sub_4D2ED0_004d2ed0__recomp},
    {"sub_4D3040", 0x4D3040, &recomp_gen::fn_sub_4D3040_004d3040, &recomp_gen::fn_sub_4D3040_004d3040__recomp},
    {"sub_4D3120", 0x4D3120, &recomp_gen::fn_sub_4D3120_004d3120, &recomp_gen::fn_sub_4D3120_004d3120__recomp},
    {"sub_4D3220", 0x4D3220, &recomp_gen::fn_sub_4D3220_004d3220, &recomp_gen::fn_sub_4D3220_004d3220__recomp},
    {"sub_4D3300", 0x4D3300, &recomp_gen::fn_sub_4D3300_004d3300, &recomp_gen::fn_sub_4D3300_004d3300__recomp},
    {"sub_4D3800", 0x4D3800, &recomp_gen::fn_sub_4D3800_004d3800, &recomp_gen::fn_sub_4D3800_004d3800__recomp},
    {"sub_4D3FC0", 0x4D3FC0, &recomp_gen::fn_sub_4D3FC0_004d3fc0, &recomp_gen::fn_sub_4D3FC0_004d3fc0__recomp},
    {"sub_4D40E0", 0x4D40E0, &recomp_gen::fn_sub_4D40E0_004d40e0, &recomp_gen::fn_sub_4D40E0_004d40e0__recomp},
    {"sub_4D41E0", 0x4D41E0, &recomp_gen::fn_sub_4D41E0_004d41e0, &recomp_gen::fn_sub_4D41E0_004d41e0__recomp},
    {"sub_4D8320", 0x4D8320, &recomp_gen::fn_sub_4D8320_004d8320, &recomp_gen::fn_sub_4D8320_004d8320__recomp},
    {"sub_4F22B0", 0x4F22B0, &recomp_gen::fn_sub_4F22B0_004f22b0, &recomp_gen::fn_sub_4F22B0_004f22b0__recomp},
    {"sub_4F2730", 0x4F2730, &recomp_gen::fn_sub_4F2730_004f2730, &recomp_gen::fn_sub_4F2730_004f2730__recomp},
    {"sub_4F2790", 0x4F2790, &recomp_gen::fn_sub_4F2790_004f2790, &recomp_gen::fn_sub_4F2790_004f2790__recomp},
    {"sub_4F2870", 0x4F2870, &recomp_gen::fn_sub_4F2870_004f2870, &recomp_gen::fn_sub_4F2870_004f2870__recomp},
    {"sub_4F28A0", 0x4F28A0, &recomp_gen::fn_sub_4F28A0_004f28a0, &recomp_gen::fn_sub_4F28A0_004f28a0__recomp},
    {"sub_4F28D0", 0x4F28D0, &recomp_gen::fn_sub_4F28D0_004f28d0, &recomp_gen::fn_sub_4F28D0_004f28d0__recomp},
    {"sub_4F28F0", 0x4F28F0, &recomp_gen::fn_sub_4F28F0_004f28f0, &recomp_gen::fn_sub_4F28F0_004f28f0__recomp},
    {"sub_4F2990", 0x4F2990, &recomp_gen::fn_sub_4F2990_004f2990, &recomp_gen::fn_sub_4F2990_004f2990__recomp},
    {"sub_4F2A00", 0x4F2A00, &recomp_gen::fn_sub_4F2A00_004f2a00, &recomp_gen::fn_sub_4F2A00_004f2a00__recomp},
    {"sub_4F2F70", 0x4F2F70, &recomp_gen::fn_sub_4F2F70_004f2f70, &recomp_gen::fn_sub_4F2F70_004f2f70__recomp},
    {"sub_4F30E0", 0x4F30E0, &recomp_gen::fn_sub_4F30E0_004f30e0, &recomp_gen::fn_sub_4F30E0_004f30e0__recomp},
    {"sub_4F31C0", 0x4F31C0, &recomp_gen::fn_sub_4F31C0_004f31c0, &recomp_gen::fn_sub_4F31C0_004f31c0__recomp},
    {"sub_4F3260", 0x4F3260, &recomp_gen::fn_sub_4F3260_004f3260, &recomp_gen::fn_sub_4F3260_004f3260__recomp},
    {"sub_4F3410", 0x4F3410, &recomp_gen::fn_sub_4F3410_004f3410, &recomp_gen::fn_sub_4F3410_004f3410__recomp},
    {"sub_4F3680", 0x4F3680, &recomp_gen::fn_sub_4F3680_004f3680, &recomp_gen::fn_sub_4F3680_004f3680__recomp},
    {"sub_4F3880", 0x4F3880, &recomp_gen::fn_sub_4F3880_004f3880, &recomp_gen::fn_sub_4F3880_004f3880__recomp},
    {"sub_4F3970", 0x4F3970, &recomp_gen::fn_sub_4F3970_004f3970, &recomp_gen::fn_sub_4F3970_004f3970__recomp},
    {"sub_4F3D60", 0x4F3D60, &recomp_gen::fn_sub_4F3D60_004f3d60, &recomp_gen::fn_sub_4F3D60_004f3d60__recomp},
    {"sub_4F3F80", 0x4F3F80, &recomp_gen::fn_sub_4F3F80_004f3f80, &recomp_gen::fn_sub_4F3F80_004f3f80__recomp},
    {"sub_4F4640", 0x4F4640, &recomp_gen::fn_sub_4F4640_004f4640, &recomp_gen::fn_sub_4F4640_004f4640__recomp},
    {"sub_4F4830", 0x4F4830, &recomp_gen::fn_sub_4F4830_004f4830, &recomp_gen::fn_sub_4F4830_004f4830__recomp},
    {"sub_4F4950", 0x4F4950, &recomp_gen::fn_sub_4F4950_004f4950, &recomp_gen::fn_sub_4F4950_004f4950__recomp},
    {"sub_4F4C30", 0x4F4C30, &recomp_gen::fn_sub_4F4C30_004f4c30, &recomp_gen::fn_sub_4F4C30_004f4c30__recomp},
    {"sub_4F4CF0", 0x4F4CF0, &recomp_gen::fn_sub_4F4CF0_004f4cf0, &recomp_gen::fn_sub_4F4CF0_004f4cf0__recomp},
    {"sub_4F4DB0", 0x4F4DB0, &recomp_gen::fn_sub_4F4DB0_004f4db0, &recomp_gen::fn_sub_4F4DB0_004f4db0__recomp},
    {"sub_4F4FE0", 0x4F4FE0, &recomp_gen::fn_sub_4F4FE0_004f4fe0, &recomp_gen::fn_sub_4F4FE0_004f4fe0__recomp},
    {"sub_4F50A0", 0x4F50A0, &recomp_gen::fn_sub_4F50A0_004f50a0, &recomp_gen::fn_sub_4F50A0_004f50a0__recomp},
    {"sub_4F5520", 0x4F5520, &recomp_gen::fn_sub_4F5520_004f5520, &recomp_gen::fn_sub_4F5520_004f5520__recomp},
    {"sub_4F57F0", 0x4F57F0, &recomp_gen::fn_sub_4F57F0_004f57f0, &recomp_gen::fn_sub_4F57F0_004f57f0__recomp},
    {"sub_4F5A90", 0x4F5A90, &recomp_gen::fn_sub_4F5A90_004f5a90, &recomp_gen::fn_sub_4F5A90_004f5a90__recomp},
    {"sub_4F5B80", 0x4F5B80, &recomp_gen::fn_sub_4F5B80_004f5b80, &recomp_gen::fn_sub_4F5B80_004f5b80__recomp},
    {"sub_4F5C50", 0x4F5C50, &recomp_gen::fn_sub_4F5C50_004f5c50, &recomp_gen::fn_sub_4F5C50_004f5c50__recomp},
    {"sub_4F5D90", 0x4F5D90, &recomp_gen::fn_sub_4F5D90_004f5d90, &recomp_gen::fn_sub_4F5D90_004f5d90__recomp},
    {"sub_4F6140", 0x4F6140, &recomp_gen::fn_sub_4F6140_004f6140, &recomp_gen::fn_sub_4F6140_004f6140__recomp},
    {"sub_4F63D0", 0x4F63D0, &recomp_gen::fn_sub_4F63D0_004f63d0, &recomp_gen::fn_sub_4F63D0_004f63d0__recomp},
    {"sub_4F64F0", 0x4F64F0, &recomp_gen::fn_sub_4F64F0_004f64f0, &recomp_gen::fn_sub_4F64F0_004f64f0__recomp},
    {"sub_4F65B0", 0x4F65B0, &recomp_gen::fn_sub_4F65B0_004f65b0, &recomp_gen::fn_sub_4F65B0_004f65b0__recomp},
    {"sub_4F67B0", 0x4F67B0, &recomp_gen::fn_sub_4F67B0_004f67b0, &recomp_gen::fn_sub_4F67B0_004f67b0__recomp},
    {"sub_4F6970", 0x4F6970, &recomp_gen::fn_sub_4F6970_004f6970, &recomp_gen::fn_sub_4F6970_004f6970__recomp},
    {"sub_4F6A10", 0x4F6A10, &recomp_gen::fn_sub_4F6A10_004f6a10, &recomp_gen::fn_sub_4F6A10_004f6a10__recomp},
    {"sub_4F6B50", 0x4F6B50, &recomp_gen::fn_sub_4F6B50_004f6b50, &recomp_gen::fn_sub_4F6B50_004f6b50__recomp},
    {"sub_4F6CE0", 0x4F6CE0, &recomp_gen::fn_sub_4F6CE0_004f6ce0, &recomp_gen::fn_sub_4F6CE0_004f6ce0__recomp},
    {"sub_4F6F20", 0x4F6F20, &recomp_gen::fn_sub_4F6F20_004f6f20, &recomp_gen::fn_sub_4F6F20_004f6f20__recomp},
    {"sub_4F7080", 0x4F7080, &recomp_gen::fn_sub_4F7080_004f7080, &recomp_gen::fn_sub_4F7080_004f7080__recomp},
    {"sub_4F72C0", 0x4F72C0, &recomp_gen::fn_sub_4F72C0_004f72c0, &recomp_gen::fn_sub_4F72C0_004f72c0__recomp},
    {"sub_4F72D0", 0x4F72D0, &recomp_gen::fn_sub_4F72D0_004f72d0, &recomp_gen::fn_sub_4F72D0_004f72d0__recomp},
    {"sub_4F72E0", 0x4F72E0, &recomp_gen::fn_sub_4F72E0_004f72e0, &recomp_gen::fn_sub_4F72E0_004f72e0__recomp},
    {"sub_4F72F0", 0x4F72F0, &recomp_gen::fn_sub_4F72F0_004f72f0, &recomp_gen::fn_sub_4F72F0_004f72f0__recomp},
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

const Case& by_name(const char* n) {
    for (const Case& c : kCases)
        if (std::strcmp(c.name, n) == 0) return c;
    std::fprintf(stderr, "render_rw8 test: no case %s\n", n);
    std::abort();
}

// The RW globals the bodies read (render_rw5.h / render_rw8.h).
constexpr u32 kEngine = 0x960070u;
constexpr u32 kPdsRegistry = 0x95C44Cu;
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

// --- the pair on stand-in worlds -------------------------------------------------------------------------------------
// hgp::pair with a fresh stand-in world around each body (the heap behind the RW memory slots and the free-list entry
// points, printf / sprintf, the H_Cdvd layer); afterwards both worlds' call logs, live heap blocks and bad frees must be
// equal. Float arguments go in through g_fpr (set after the harness's randomised registers).
Fn g_body[2];
StandInWorld* g_world[2];
std::map<unsigned, float> g_fpr;
// A sequence of calls run as one body (both runs make the same calls in one stand-in world, so blocks allocated by
// one call stay live for the next): each step sets $a0..$a3 from its arguments, $a0 = the previous call's $v0 when
// chained (a pipeline created, locked, given a fragment, unlocked ...).
struct Step {
    const Case* c;
    Args a;
    bool chain = false;
    bool set_t = false;            // $t0..$t3 (arguments 5..8) from t, also on the first step
    std::array<u64, 4> t{};
};
std::vector<Step> g_seq;
void thunk(int k, EEContext& ctx) {
    StandInsScope s(g_world[k]->si);
    for (const auto& [r, f] : g_fpr) ctx.fpr[r] = fbits(f);
    if (g_seq.empty()) {
        g_body[k](ctx);
        return;
    }
    for (std::size_t i = 0; i < g_seq.size(); ++i) {
        const Step& st = g_seq[i];
        if (i > 0) {
            const u64 prev = ctx.gpr[GPR_V0].u64[0];
            for (int r = 0; r < 4; ++r) ctx.gpr[GPR_A0 + r].u64[0] = st.a[static_cast<std::size_t>(r)];
            if (st.chain) ctx.gpr[GPR_A0].u64[0] = prev;
        }
        if (st.set_t)
            for (int r = 0; r < 4; ++r) ctx.gpr[GPR_T0 + r].u64[0] = st.t[static_cast<std::size_t>(r)];
        (k == 0 ? st.c->hand : st.c->recomp)(ctx);
    }
}
void thunk_hand(EEContext& ctx) { thunk(0, ctx); }
void thunk_recomp(EEContext& ctx) { thunk(1, ctx); }

struct WPair {
    hgp::Run run;
    std::unique_ptr<StandInWorld> hand, recomp;
    u32 v0() const { return static_cast<u32>(run.end.gpr[GPR_V0].u64[0]); }
    u64 v0_64() const { return run.end.gpr[GPR_V0].u64[0]; }
    float f0() const {
        float f;
        std::memcpy(&f, &run.end.fpr[0], 4);
        return f;
    }
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
// The sequence as one pair (the first step's arguments are the pair's).
WPair wseq(Machine& m, const std::vector<Step>& steps, u32 seed, const WorldSetup& setup = install_standard) {
    g_seq = steps;
    WPair p = wpair(m, *steps.front().c, steps.front().a, seed, setup);
    g_seq.clear();
    return p;
}
Step step(const char* name, const Args& a = {0, 0, 0, 0}, bool chain = false) { return Step{&by_name(name), a, chain}; }
std::string hex(u32 v) {
    char b[16];
    std::snprintf(b, sizeof b, "0x%X", v);
    return b;
}


// =====================================================================================================================
// RxPipeline: reading a pipeline's shape from guest memory (render_rw8.h: rw8::pipe / pnode / nodedef)
// =====================================================================================================================
constexpr u32 kGpPipeline = 0x7CEB28u;  // the pipeline module: +0 the 52-byte pipeline free list, +56 the node limit
constexpr u32 kGpIm3d = 0x7CEB20u;      // the Im3D module: +28 the transform pipeline, +32.. the render pipelines
constexpr u32 kGpPTank = 0x7CE774u;     // PTank's engine block: the six pipelines' record

struct NodeShape {
    u32 def = 0;
    std::string name;
    std::vector<u32> outputs;
    std::vector<u8> priv;   // the private data (the definition's size)
    std::vector<u8> init;   // the initialisation data
    std::vector<u32> in_slots;  // input-to-cluster-slot map (one per cluster of interest)
};
struct PipeShape {
    bool ok = false;
    u32 locked = 0, nodes = 0, slots = 0, entry = 0, plugin = 0, plugin_data = 0, reqs = 0;
    std::vector<NodeShape> node;
};
PipeShape pipe_shape(Machine& m, u32 p) {
    PipeShape s;
    if (!in_ram(p, 52)) return s;
    s.locked = ld(m, p + 0);
    s.nodes = ld(m, p + 4);
    s.slots = ld(m, p + 12);
    s.reqs = ld(m, p + 24);
    s.entry = ld(m, p + 40);
    s.plugin = ld(m, p + 44);
    s.plugin_data = ld(m, p + 48);
    const u32 nodes = ld(m, p + 8);
    if (s.nodes > 64 || (s.nodes && !in_ram(nodes, 40 * s.nodes))) return s;
    for (u32 i = 0; i < s.nodes; ++i) {
        const u32 n = nodes + 40 * i;
        NodeShape ns;
        ns.def = ld(m, n);
        if (!in_ram(ns.def, 64)) return s;
        if (in_ram(ld(m, ns.def))) ns.name = lds(m, ld(m, ns.def));
        const u32 nout = ld(m, n + 4), outs = ld(m, n + 8);
        for (u32 k = 0; k < nout && in_ram(outs, 4 * nout) && k < 32; ++k) ns.outputs.push_back(ld(m, outs + 4 * k));
        const u32 psize = ld(m, ns.def + 52), priv = ld(m, n + 20);
        if (psize < 0x1000 && in_ram(priv, psize)) ns.priv.assign(m.at(priv), m.at(priv) + psize);
        const u32 isize = ld(m, n + 36), init = ld(m, n + 32);
        if (isize < 0x1000 && in_ram(init, isize)) ns.init.assign(m.at(init), m.at(init) + isize);
        const u32 ncl = ld(m, ns.def + 32), map = ld(m, n + 24);
        for (u32 k = 0; k < ncl && k < 32 && in_ram(map, 4 * ncl); ++k) ns.in_slots.push_back(ld(m, map + 4 * k));
        s.node.push_back(ns);
    }
    s.ok = true;
    return s;
}
// The first difference of two shapes ("" when equal). priv = false leaves the private data out.
std::string shape_diff(const PipeShape& a, const PipeShape& b, bool priv = true) {
    char buf[200];
    if (!a.ok || !b.ok) return "unreadable";
    if (a.locked != b.locked) return "locked";
    if (a.nodes != b.nodes) return "node count";
    if (a.slots != b.slots) return "cluster slots";
    if (a.entry != b.entry) return "entry point";
    if (a.plugin != b.plugin || a.plugin_data != b.plugin_data) return "plugin id / data";
    if (a.reqs != b.reqs) return "input requirements";
    for (std::size_t i = 0; i < a.node.size(); ++i) {
        const NodeShape &x = a.node[i], &y = b.node[i];
        std::snprintf(buf, sizeof buf, "node %u (%s): ", static_cast<unsigned>(i), x.name.c_str());
        if (x.def != y.def) return std::string(buf) + "definition";
        if (x.outputs != y.outputs) return std::string(buf) + "outputs";
        if (x.init != y.init) return std::string(buf) + "initialisation data";
        if (x.in_slots != y.in_slots) return std::string(buf) + "input slots";
        if (priv && x.priv != y.priv) return std::string(buf) + "private data";
    }
    return "";
}
std::string shape_text(const PipeShape& s) {
    std::string t = "nodes " + std::to_string(s.nodes) + " slots " + std::to_string(s.slots) + " entry " + std::to_string(s.entry) + ":";
    for (const NodeShape& n : s.node) {
        t += " [" + n.name + " out";
        for (u32 o : n.outputs) t += " " + std::to_string(static_cast<s32>(o));
        t += " priv " + std::to_string(n.priv.size()) + " init " + std::to_string(n.init.size()) + "]";
    }
    return t;
}

// The live pipelines of a snapshot: the PDS registry's (id, type, definition, pipe), PTank's six, the Im3D ones.
struct LivePipe {
    std::string what;
    u32 pipe = 0, def = 0, type = 0, id = 0;
};
std::vector<LivePipe> live_pipes(Machine& m) {
    std::vector<LivePipe> out;
    const u32 ents = ld(m, kPdsRegistry), count = ld(m, kPdsRegistry + 4);
    for (u32 i = 0; i < count && in_ram(ents, 20 * count); ++i) {
        const u32 e = ents + 20 * i;
        char b[48];
        std::snprintf(b, sizeof b, "PDS 0x%X", ld(m, e + 8));
        out.push_back({b, ld(m, e + 16), ld(m, e), ld(m, e + 12), ld(m, e + 8)});
    }
    const u32 pt = ld(m, kEngine + ld(m, kGpPTank));
    for (u32 k = 0; k < 6 && in_ram(pt, 24); ++k) out.push_back({"PTank +" + std::to_string(4 * k), ld(m, pt + 4 * k), 0, 0, 0});
    const u32 im = kEngine + ld(m, kGpIm3d);
    for (u32 k = 7; k <= 15; ++k) out.push_back({"Im3D +" + std::to_string(4 * k), ld(m, im + 4 * k), 0, 0, 0});
    std::vector<LivePipe> keep;
    std::set<u32> seen;
    for (const LivePipe& l : out)
        if (in_ram(l.pipe, 52) && seen.insert(l.pipe).second) keep.push_back(l);
    return keep;
}

/////////// The stand-in heap takes the snapshot's blocks a pipeline owns (its super block and the nodes' initialisation data),
// so the lock / unlock can grow (RwRealloc) or free them like retail's heap.
WorldSetup pipe_world(Machine& m, const std::vector<LivePipe>& lp) {
    std::vector<std::pair<u32, u32>> blocks;
    for (const LivePipe& l : lp) {
        const u32 sb = ld(m, l.pipe + 32), size = ld(m, l.pipe + 36);
        if (in_ram(sb, size) && size) blocks.push_back({sb, size});
        const u32 n = ld(m, l.pipe + 4), nodes = ld(m, l.pipe + 8);
        for (u32 i = 0; i < n && i < 64 && in_ram(nodes, 40 * n); ++i) {
            const u32 init = ld(m, nodes + 40 * i + 32), isize = ld(m, nodes + 40 * i + 36);
            if (in_ram(init, isize) && isize) blocks.push_back({init, isize});
        }
    }
    return [blocks](StandInWorld& w) {
        install_standard(w);
        for (const auto& [p, s] : blocks) w.heap.reserve(p, s);
    };
}
u32 priv_word(const NodeShape& n, u32 off) {
    u32 v = 0;
    if (off + 4 <= n.priv.size()) std::memcpy(&v, &n.priv[off], 4);
    return v;
}
// The private data equal but for the words listed (the PS2All node's +36 is a block of its own; +24 its material pipe).
bool priv_equal_but(const NodeShape& a, const NodeShape& b, std::initializer_list<u32> skip) {
    if (a.priv.size() != b.priv.size()) return false;
    for (u32 i = 0; i + 4 <= a.priv.size(); i += 4) {
        if (std::find(skip.begin(), skip.end(), i) != skip.end()) continue;
        if (priv_word(a, i) != priv_word(b, i)) return false;
    }
    return true;
}
constexpr u32 kPs2AllMatDefaultCode = 0x77F130u;  // the PS2AllMat node's default VU1 code array (32 entries)

// A lock and unlock of every live pipeline of the three snapshots (the PDS registry's, PTank's six, the Im3D
// transform), as one pair: the unlock returns the pipeline, unlocked, with every node, output, initialisation data and
// input-slot map as before and the same cluster-slot count and entry point; what the unlock does not keep is each node's
// private data -- the node's own initialisation runs again and leaves the definition's defaults (PS2AllMat: no
// callbacks, VIF offset 0x114, the default VU1 code array 0x77F130 x 32; PS2All: no callback, no material pipeline),
// which is why every pipe constructor sets its callbacks after the unlock. The lock alone marks the pipeline locked,
// clears each node's slot-cluster word (+12) and keeps everything else; a second lock is a no-op.
TEST_CASE("game(render_rw8): RxPipelineLock / RxLockedPipeUnlock round trip on every live pipeline") {
    int snaps = 0, pipes = 0;
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
        const std::vector<LivePipe> lp = live_pipes(m);
        CHECK(lp.size() >= 20u);
        const WorldSetup world = pipe_world(m, lp);
        u32 k = 0;
        for (const LivePipe& l : lp) {
            INFO(sn << " " << l.what << " pipe " << hex(l.pipe));
            restore(m, image);
            const PipeShape before = pipe_shape(m, l.pipe);
            REQUIRE(before.ok);
            CHECK(before.locked == 0u);
            // the lock alone
            const WPair a = wp(m, "sub_4F4640", {l.pipe, 0, 0, 0}, 310000u + snaps * 1000 + k++, world);
            CHECK_FALSE(a.run.stopped);
            CHECK(a.v0() == l.pipe);
            const PipeShape locked = pipe_shape(m, l.pipe);
            CHECK(locked.locked == 1u);
            CHECK(locked.nodes == before.nodes);
            for (u32 i = 0; i < before.nodes; ++i) {
                CHECK(ld(m, ld(m, l.pipe + 8) + 40 * i + 12) == 0u);
                CHECK(locked.node[i].def == before.node[i].def);
                CHECK(locked.node[i].init == before.node[i].init);
            }
            const WPair a2 = wp(m, "sub_4F4640", {l.pipe, 0, 0, 0}, 310000u + snaps * 1000 + k++, world);
            CHECK(a2.v0() == l.pipe);
            CHECK(shape_diff(locked, pipe_shape(m, l.pipe)) == "");
            // lock + unlock in one world
            restore(m, image);
            const WPair b = wseq(m, {step("sub_4F4640", {l.pipe, 0, 0, 0}), step("sub_4F3F80", {0, 0, 0, 0}, true)}, 320000u + snaps * 1000 + k++, world);
            CHECK_FALSE(b.run.stopped);
            CHECK(b.v0() == l.pipe);
            const PipeShape after = pipe_shape(m, l.pipe);
            CHECK(shape_diff(before, after, false) == "");
            for (const NodeShape& n : after.node) {
                if (n.name == "PS2AllMat.csl") {
                    for (u32 off = 0; off < 20; off += 4) CHECK(priv_word(n, off) == 0u);
                    CHECK(priv_word(n, 20) == 0x114u);
                    CHECK(priv_word(n, 24) == kPs2AllMatDefaultCode);
                    CHECK(priv_word(n, 28) == 32u);
                } else if (n.name == "PS2All.csl") {
                    CHECK(priv_word(n, 16) == 0u);
                    CHECK(priv_word(n, 24) == 0u);
                }
            }
            ++pipes;
        }
        // unlocking a pipeline that is not locked fails (error 52) and changes nothing; a null pipeline too
        restore(m, image);
        const PipeShape p0 = pipe_shape(m, lp.front().pipe);
        const WPair u = wp(m, "sub_4F3F80", {lp.front().pipe, 0, 0, 0}, 330000u + snaps, world);
        CHECK(u.v0() == 0u);
        CHECK(shape_diff(p0, pipe_shape(m, lp.front().pipe)) == "");
        CHECK(wp(m, "sub_4F3F80", {0, 0, 0, 0}, 331000u + snaps, world).v0() == 0u);
    }
    if (snaps) MESSAGE("lock / unlock: " << pipes << " live pipelines on " << snaps << " snapshots");
}

// The PDS pipe constructors rebuild the live registry pipelines: RpPDSSkyMatPipeCreate (type-1 entries, a PS2AllMat
// pipeline from the 132-byte material definition) and sub_46AFA0 (type-2 entries, a PS2All object pipeline from its
// 20-byte definition) give the live pipeline node for node, private data included (the PS2All node's +36 is a block of
// its own); the plugin id is 0x131 and the plugin data the definition's +4 (the registry then stores the entry's id).
// The engine open sub_46A600 on an unopened registry rebuilds every entry's pipe (type 2 linked to the new pipe of the
// entry its aux id names) and marks the registry built; RpPDSRegisterPipe adds a definition under a new id (built at
// once in a built registry) and refuses an id already there.
TEST_CASE("game(render_rw8): the PDS pipe constructors rebuild the live registry pipelines") {
    int snaps = 0, built = 0;
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
        const std::vector<LivePipe> lp = live_pipes(m);
        const WorldSetup world = pipe_world(m, lp);
        std::map<u32, PipeShape> live_by_id;
        std::map<u32, u32> pipe_by_id;
        u32 k = 0;
        for (const LivePipe& l : lp) {
            if (!l.def) continue;
            INFO(sn << " " << l.what);
            restore(m, image);
            const PipeShape live = pipe_shape(m, l.pipe);
            live_by_id[l.id] = live;
            pipe_by_id[l.id] = l.pipe;
            REQUIRE((l.type == 1 || l.type == 2));
            const WPair c = wp(m, l.type == 1 ? "RpPDSSkyMatPipeCreate" : "sub_46AFA0", {l.def, 0, 0, 0}, 340000u + snaps * 1000 + k++, world);
            CHECK_FALSE(c.run.stopped);
            const PipeShape fresh = pipe_shape(m, c.v0());
            REQUIRE(fresh.ok);
            CHECK(fresh.plugin == 0x131u);
            CHECK(fresh.plugin_data == ld(m, l.def + 4));
            const std::string d = shape_diff(live, fresh, false);
            CHECK((d == "" || d == "plugin id / data"));
            REQUIRE(fresh.node.size() == live.node.size());
            for (std::size_t i = 0; i < fresh.node.size(); ++i) {
                CHECK(fresh.node[i].def == live.node[i].def);
                CHECK(fresh.node[i].outputs == live.node[i].outputs);
                CHECK(fresh.node[i].init == live.node[i].init);
                CHECK(priv_equal_but(fresh.node[i], live.node[i], {36}));
                if (l.type == 2) {  // +36 points into the pipeline's own super block
                    const u32 v = priv_word(fresh.node[i], 36), sb = ld(m, c.v0() + 32);
                    CHECK(v >= sb);
                    CHECK(v < sb + ld(m, c.v0() + 36));
                }
            }
            ++built;
        }
        // the engine open on the unopened registry
        restore(m, image);
        st(m, 0x95C448u, 0);  // the open count
        st(m, kPdsRegistry + 12, 0);
        const WPair o = wp(m, "sub_46A600", {kEngine, 0, 0, 0}, 345000u + snaps, world);
        CHECK(o.v0() == kEngine);
        CHECK(ld(m, 0x95C448u) == 1u);
        CHECK(ld(m, kPdsRegistry + 12) == 1u);
        const u32 ents = ld(m, kPdsRegistry), count = ld(m, kPdsRegistry + 4);
        std::map<u32, u32> fresh_by_id;
        for (u32 i = 0; i < count; ++i) fresh_by_id[ld(m, ents + 20 * i + 8)] = ld(m, ents + 20 * i + 16);
        for (u32 i = 0; i < count; ++i) {
            const u32 e = ents + 20 * i, id = ld(m, e + 8), type = ld(m, e + 12), pipe = ld(m, e + 16);
            INFO(sn << " rebuilt entry " << hex(id));
            CHECK(pipe != pipe_by_id[id]);
            CHECK(o.recomp->heap.size_of(pipe) != 0u);
            const PipeShape fresh = pipe_shape(m, pipe);
            CHECK(fresh.plugin_data == id);
            CHECK(shape_diff(live_by_id[id], fresh, false) == "");
            for (std::size_t n = 0; n < fresh.node.size() && n < live_by_id[id].node.size(); ++n) {
                if (type == 2) {
                    CHECK(priv_equal_but(fresh.node[n], live_by_id[id].node[n], {24, 36}));
                    const u32 aux = ld(m, e + 4);
                    CHECK(priv_word(fresh.node[n], 24) == (aux ? fresh_by_id[aux] : 0u));
                } else {
                    CHECK(priv_equal_but(fresh.node[n], live_by_id[id].node[n], {}));
                }
            }
        }
        // RpPDSRegisterPipe: a copy of the first type-1 definition under a new id, then the same id again
        for (const LivePipe& l : lp) {
            if (l.type != 1) continue;
            restore(m, image);
            const u32 def = kData + 0x400;
            std::memcpy(m.at(def), m.at(l.def), 132);
            const u32 rec = kData + 0x500;
            st(m, rec + 0, def);
            st(m, rec + 4, 0);
            st(m, rec + 8, 0x7A7A0u);
            st(m, rec + 12, 1);
            const u32 n0 = ld(m, kPdsRegistry + 4);
            const WPair r = wp(m, "RpPDSRegisterPipe", {rec, 0, 0, 0}, 346000u + snaps, world);
            CHECK(r.v0() == rec);
            CHECK(ld(m, kPdsRegistry + 4) == n0 + 1);
            const u32 e = ld(m, kPdsRegistry) + 20 * n0;
            CHECK(ld(m, e) == def);
            CHECK(ld(m, e + 8) == 0x7A7A0u);
            const PipeShape fresh = pipe_shape(m, ld(m, e + 16));
            CHECK(fresh.plugin_data == 0x7A7A0u);
            CHECK(shape_diff(pipe_shape(m, l.pipe), fresh, false) == "plugin id / data");
            const WPair r2 = wp(m, "RpPDSRegisterPipe", {rec, 0, 0, 0}, 347000u + snaps, world);
            CHECK(ld(m, kPdsRegistry + 4) == n0 + 1);
            (void)r2;
            break;
        }
    }
    if (snaps) MESSAGE("PDS: " << built << " registry pipelines rebuilt and compared on " << snaps << " snapshots");
}

// PTank's engine open (sub_474BB0) builds its six pipelines again (the 2D / 3D sprite PS2AllMat pipes and their PS2All
// object pipes, the tank pipe, the instancing one): each equals the snapshot's live pipeline of the same slot (the
// PS2All node's +36 a block of its own, +24 the new material pipe); the close (sub_474C60) destroys all six and frees
// the record. The Im3D transform pipeline ("FastIm3DTransform", sub_49C810) equals the live one.
TEST_CASE("game(render_rw8): PTank's and Im3D's pipe constructors rebuild the live pipelines") {
    int snaps = 0;
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
        const std::vector<LivePipe> lp = live_pipes(m);
        const WorldSetup world = pipe_world(m, lp);
        const u32 slot = kEngine + ld(m, kGpPTank);
        const u32 old = ld(m, slot);
        REQUIRE(in_ram(old, 24));
        std::array<PipeShape, 6> live;
        for (u32 i = 0; i < 6; ++i) live[i] = pipe_shape(m, ld(m, old + 4 * i));
        const WPair o = wp(m, "sub_474BB0", {kEngine, 0, 0, 0}, 350000u + snaps, world);
        CHECK(o.v0() == kEngine);
        const u32 rec = ld(m, slot);
        CHECK(rec != old);
        CHECK(o.recomp->heap.size_of(rec) == 32u);
        for (u32 i = 0; i < 6; ++i) {
            INFO(sn << " PTank pipe +" << 4 * i);
            const PipeShape fresh = pipe_shape(m, ld(m, rec + 4 * i));
            CHECK(shape_diff(live[i], fresh, false) == "");
            for (std::size_t n = 0; n < fresh.node.size() && n < live[i].node.size(); ++n)
                CHECK(priv_equal_but(fresh.node[n], live[i].node[n], {24, 36}));
        }
        // +8's material pipe is +4, +16's is +12 (the PS2All object pipes of the two sprite pipes)
        CHECK(priv_word(pipe_shape(m, ld(m, rec + 8)).node[0], 24) == ld(m, rec + 4));
        CHECK(priv_word(pipe_shape(m, ld(m, rec + 16)).node[0], 24) == ld(m, rec + 12));
        // the close destroys the six pipes and frees the record (in one world with the open)
        restore(m, image);
        const WPair c = wseq(m, {step("sub_474BB0", {kEngine, 0, 0, 0}), step("sub_474C60", {kEngine, 0, 0, 0})}, 351000u + snaps, world);
        CHECK(c.v0() == kEngine);
        CHECK(c.recomp->heap.size_of(ld(m, slot)) == 0u);
        // Im3D
        restore(m, image);
        const u32 im = kEngine + ld(m, kGpIm3d);
        const PipeShape live_t = pipe_shape(m, ld(m, im + 28));
        const WPair t = wp(m, "sub_49C810", {0, 0, 0, 0}, 352000u + snaps, world);
        const PipeShape fresh_t = pipe_shape(m, t.v0());
        CHECK(fresh_t.ok);
        CHECK(fresh_t.plugin == 1u);
        CHECK(shape_diff(live_t, fresh_t) == "");
    }
}

// A pipeline built from scratch out of four test node definitions with two clusters each (written into the test area):
// RxPipelineCreate, RxPipelineLock, RxLockedPipeAddFragment(N0, N1, N3) -- a chain, output 0 of each node to the next
// --, a second fragment (N2), then RxLockedPipeAddPath N0.out1 -> N2 and N2.out0 -> N3, and RxLockedPipeUnlock. The
// unlock sorts the nodes topologically (every output leads to a later node; N0 first, N3 last), counts the distinct
// clusters (the cluster-slot count, 2), makes N0 the entry point, maps each node's clusters of interest to slots, and
// counts each definition's use (+60). RxPipelineFindNodeByName then finds every node by its name (index out), from a
// start node onwards, and nothing for an unknown name (index -1); RxLockedPipeAddPath refuses a connected output, a
// node outside the pipeline and an unlocked pipeline; a fragment longer than the pipeline module's node limit fails.
struct TestNodes {
    u32 clusters[2];
    u32 defs[4];
};
TestNodes write_test_nodes(Machine& m, u32 base) {
    TestNodes t{};
    std::memset(m.at(base), 0, 0x1000);
    const char* cname[2] = {"TestPos", "TestCol"};
    for (u32 c = 0; c < 2; ++c) {
        const u32 cd = base + 16 * c, nm = base + 0x40 + 16 * c;
        sts(m, nm, cname[c]);
        st(m, cd + 0, nm);
        st(m, cd + 4, 16);  // default stride
        t.clusters[c] = cd;
    }
    const u32 nouts[4] = {2, 1, 1, 0};
    for (u32 i = 0; i < 4; ++i) {
        const u32 d = base + 0x100 + 64 * i, nm = base + 0x80 + 16 * i;
        char name[16];
        std::snprintf(name, sizeof name, "TestN%u.csl", i);
        sts(m, nm, name);
        const u32 refs = base + 0x300 + 32 * i, reqs = base + 0x400 + 16 * i, outs = base + 0x500 + 32 * i;
        for (u32 c = 0; c < 2; ++c) {
            st(m, refs + 12 * c, t.clusters[c]);
            st(m, reqs + 4 * c, i == 0 ? 0u : 2u);  // N0 wants nothing, the others take both clusters if present
        }
        for (u32 o = 0; o < nouts[i]; ++o) {
            const u32 os = outs + 12 * o, stat = base + 0x600 + 32 * i + 8 * o, oname = base + 0x700 + 32 * i + 16 * o;
            std::snprintf(name, sizeof name, "Out%u", o);
            sts(m, oname, name);
            st(m, os + 0, oname);
            st(m, os + 4, stat);
            st(m, os + 8, 0);  // all other clusters: no change
            st(m, stat + 0, i == 0 ? 1u : 0u);  // N0 makes both clusters valid, the others leave them
            st(m, stat + 4, i == 0 ? 1u : 0u);
        }
        st(m, d + 0, nm);
        st(m, d + 32, 2);
        st(m, d + 36, refs);
        st(m, d + 40, reqs);
        st(m, d + 44, nouts[i]);
        st(m, d + 48, outs);
        st(m, d + 52, 0);
        t.defs[i] = d;
    }
    return t;
}

TEST_CASE("game(render_rw8): a pipeline built from scratch -- create, lock, fragments, paths, unlock, find node by name") {
    std::vector<u8> image;
    auto mp = snapshot_machine("b_5800", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot b_5800 not found");
        return;
    }
    Machine& m = *mp;
    restore(m, image);
    const u32 base = kData + 0x2000, first = kData + 0x3800, first2 = kData + 0x3810;
    const TestNodes tn = write_test_nodes(m, base);
    const std::vector<u8> built_image(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    // create, lock, two fragments
    Step frag1 = step("sub_4F4950", {0, first, tn.defs[0], tn.defs[1]}, true);
    frag1.set_t = true;
    frag1.t = {tn.defs[3], 0, 0, 0};
    Step frag2 = step("sub_4F4950", {0, first2, tn.defs[2], 0}, true);
    frag2.set_t = true;
    const WPair a = wseq(m, {step("sub_4F2F70"), step("sub_4F4640", {0, 0, 0, 0}, true), frag1, frag2}, 360000u);
    CHECK_FALSE(a.run.stopped);
    const u32 pipe = a.v0();
    REQUIRE(in_ram(pipe, 52));
    CHECK(ld(m, pipe) == 1u);
    CHECK(ld(m, pipe + 4) == 4u);
    CHECK(ld(m, first) == 0u);
    CHECK(ld(m, first2) == 3u);
    const u32 nodes = ld(m, pipe + 8);
    const u32 order0[4] = {tn.defs[0], tn.defs[1], tn.defs[3], tn.defs[2]};
    for (u32 i = 0; i < 4; ++i) CHECK(ld(m, nodes + 40 * i) == order0[i]);
    // the chain: N0.out0 -> 1, N1.out0 -> 2; the rest unconnected
    CHECK(ld(m, ld(m, nodes + 8)) == 1u);
    CHECK(ld(m, ld(m, nodes + 8) + 4) == 0xFFFFFFFFu);
    CHECK(ld(m, ld(m, nodes + 40 + 8)) == 2u);
    CHECK(ld(m, ld(m, nodes + 120 + 8)) == 0xFFFFFFFFu);
    // RxLockedPipeAddPath, then the unlock, in a world that owns the pipeline's blocks
    const std::vector<u8> locked_image(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    const WorldSetup world = pipe_world(m, {LivePipe{"built", pipe, 0, 0, 0}});
    const u32 out01 = ld(m, nodes + 8) + 4, out20 = ld(m, nodes + 120 + 8);
    const WPair b = wseq(m, {step("sub_4F4C30", {pipe, out01, nodes + 120, 0}), step("sub_4F4C30", {pipe, out20, nodes + 80, 0}),
                             step("sub_4F3F80", {pipe, 0, 0, 0})}, 361000u, world);
    CHECK_FALSE(b.run.stopped);
    CHECK(b.v0() == pipe);
    const PipeShape s = pipe_shape(m, pipe);
    REQUIRE(s.ok);
    CHECK(s.locked == 0u);
    CHECK(s.nodes == 4u);
    CHECK(s.slots == 2u);
    CHECK(s.entry == 0u);
    CHECK(s.node.front().def == tn.defs[0]);
    CHECK(s.node.back().def == tn.defs[3]);
    std::set<u32> defs;
    for (u32 i = 0; i < 4; ++i) {
        INFO("node " << i << " " << s.node[i].name);
        defs.insert(s.node[i].def);
        for (u32 o : s.node[i].outputs) CHECK((o == 0xFFFFFFFFu || (o > i && o < 4)));
        CHECK(s.node[i].in_slots.size() == 2u);
        for (u32 v : s.node[i].in_slots) CHECK(v < 2u);
        CHECK(ld(m, s.node[i].def + 60) == 1u);  // one use of each definition
    }
    CHECK(defs.size() == 4u);
    MESSAGE("built pipeline after the unlock: " << shape_text(s));
    // RxPipelineFindNodeByName on the unlocked pipeline
    const u32 idx = kData + 0x3820;
    const u32 nodes2 = ld(m, pipe + 8);  // the unlock moved the nodes into its new super block
    for (u32 i = 0; i < 4; ++i) {
        const u32 want = nodes2 + 40 * i;
        const WPair f = wp(m, "sub_4F4830", {pipe, ld(m, s.node[i].def), 0, idx}, 362000u + i, world);
        CHECK(f.v0() == want);
        CHECK(ld(m, idx) == i);
        const WPair g = wp(m, "sub_4F4830", {pipe, ld(m, s.node[i].def), want, idx}, 362100u + i, world);  // after itself: none
        CHECK(g.v0() == 0u);
        CHECK(ld(m, idx) == 0xFFFFFFFFu);
    }
    sts(m, kData + 0x3830, "NoSuchNode.csl");
    CHECK(wp(m, "sub_4F4830", {pipe, kData + 0x3830, 0, idx}, 362200u, world).v0() == 0u);
    CHECK(ld(m, idx) == 0xFFFFFFFFu);
    CHECK(wp(m, "sub_4F4830", {0, kData + 0x3830, 0, idx}, 362201u, world).v0() == 0u);
    // RxLockedPipeAddPath's refusals: an unlocked pipeline, a connected output, a node outside the pipeline
    CHECK(wp(m, "sub_4F4C30", {pipe, ld(m, nodes + 8) + 4, nodes + 80, 0}, 363000u, world).v0() == 0u);
    std::memcpy(m.mem.main_ram(), locked_image.data(), locked_image.size());
    CHECK(wp(m, "sub_4F4C30", {pipe, ld(m, nodes + 8), nodes + 120, 0}, 363001u, world).v0() == 0u);   // out0 connected
    CHECK(wp(m, "sub_4F4C30", {pipe, ld(m, nodes + 8) + 4, nodes + 4, 0}, 363002u, world).v0() == 0u);  // not a node start
    CHECK(wp(m, "sub_4F4C30", {pipe, ld(m, nodes + 8) + 4, nodes + 160, 0}, 363003u, world).v0() == 0u); // past the last node
    CHECK(wp(m, "sub_4F4C30", {pipe, ld(m, nodes + 8) + 4, nodes + 120, 0}, 363004u, world).v0() == pipe);
    CHECK(ld(m, ld(m, nodes + 8) + 4) == 3u);
    // a fragment beyond the node limit (the module's +56) fails with nothing added
    std::memcpy(m.mem.main_ram(), built_image.data(), built_image.size());
    const u32 limit = ld(m, kEngine + ld(m, kGpPipeline) + 56);
    MESSAGE("the pipeline module's node limit: " << limit);
    {
        // four definitions with the limit lowered to 3: refused (error 42), nothing added
        st(m, kEngine + ld(m, kGpPipeline) + 56, 3);
        Step fr = step("sub_4F4950", {0, first, tn.defs[3], tn.defs[3]}, true);
        fr.set_t = true;
        fr.t = {tn.defs[3], tn.defs[3], 0, 0};
        const WPair c = wseq(m, {step("sub_4F2F70"), step("sub_4F4640", {0, 0, 0, 0}, true), fr}, 364000u);
        CHECK(c.v0() == 0u);
    }
}

// =====================================================================================================================
// RtQuat against host math
// =====================================================================================================================
struct Q {
    double x, y, z, w;
};
Q qmul(const Q& a, const Q& b) {  // Hamilton product a * b
    return {a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y, a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
            a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w, a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z};
}
Q rand_unit_q(std::mt19937& rng) {
    Q q;
    double n;
    do {
        q.x = frand(rng, -1.0f, 1.0f);
        q.y = frand(rng, -1.0f, 1.0f);
        q.z = frand(rng, -1.0f, 1.0f);
        q.w = frand(rng, -1.0f, 1.0f);
        n = std::sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
    } while (n < 0.1);
    return {q.x / n, q.y / n, q.z / n, q.w / n};
}
void st_q(Machine& m, u32 va, const Q& q) {
    stf(m, va, static_cast<float>(q.x));
    stf(m, va + 4, static_cast<float>(q.y));
    stf(m, va + 8, static_cast<float>(q.z));
    stf(m, va + 12, static_cast<float>(q.w));
}
Q ld_q(Machine& m, u32 va) { return {ldf(m, va), ldf(m, va + 4), ldf(m, va + 8), ldf(m, va + 12)}; }
// v' = q v q* (the rotation a unit quaternion stands for)
void qrot(const Q& q, const double v[3], double out[3]) {
    const Q p{v[0], v[1], v[2], 0}, c{-q.x, -q.y, -q.z, q.w};
    const Q r = qmul(qmul(q, p), c);
    out[0] = r.x, out[1] = r.y, out[2] = r.z;
}
// The RwMatrix of a unit quaternion: right / up / at rows (each 16 bytes) the images of the unit axes under q.
void st_matrix_of(Machine& m, u32 va, const Q& q) {
    std::memset(m.at(va), 0, 64);
    const double axes[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
    for (u32 r = 0; r < 3; ++r) {
        double o[3];
        qrot(q, axes[r], o);
        for (u32 c = 0; c < 3; ++c) stf(m, va + 16 * r + 4 * c, static_cast<float>(o[c]));
    }
}
bool near_q(const Q& a, const Q& b, double tol) {
    const double d1 = std::fabs(a.x - b.x) + std::fabs(a.y - b.y) + std::fabs(a.z - b.z) + std::fabs(a.w - b.w);
    const double d2 = std::fabs(a.x + b.x) + std::fabs(a.y + b.y) + std::fabs(a.z + b.z) + std::fabs(a.w + b.w);
    return std::min(d1, d2) < tol;
}
std::unique_ptr<Machine> elf_machine() {
    auto m = std::make_unique<Machine>();
    if (m->load_elf(elf_path()) != nullptr) return nullptr;
    write_rw_slots(*m);
    return m;
}

// RtQuatConvertFromMatrix gives back the quaternion of a rotation matrix (up to sign) -- each of the four branches
// (positive trace, x / y / z dominant) is reached; null arguments give 0. RtQuatTransformVectors rotates vectors as
// q v q* does. RtQuatRotate replaces a quaternion by the axis-angle one (degrees, the axis normalised: cos / sin of the
// half angle) or concatenates it before / after (the two orders differ and are q_axis * q and q * q_axis). The slerp
// cache holds the angle between the two (+32), a 'nearly equal' flag (+36: |dot| >= 0.99999) and the start / end
// quaternions (the end turned to the start's hemisphere), both divided by sin(angle) unless nearly equal. An invalid
// combine type leaves the quaternion unchanged.
TEST_CASE("game(render_rw8): RtQuat -- from a matrix, transform vectors, rotate, the slerp cache") {
    auto mp = elf_machine();
    if (!mp) {
        MESSAGE("SKIP: no ELF");
        return;
    }
    Machine& m = *mp;
    const std::vector<u8> image(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    std::mt19937 rng{0x51554154u};
    const u32 qa = kData + 0x100, mat = kData + 0x200, vin = kData + 0x400, vout = kData + 0x600, axis = kData + 0x800,
              cache = kData + 0x900, qb = kData + 0x180;
    std::set<int> branches;
    int conv = 0, vecs = 0, rots = 0, slerps = 0;
    for (int k = 0; k < 96; ++k) {
        std::memcpy(m.mem.main_ram(), image.data(), image.size());
        Q q = rand_unit_q(rng);
        if (k < 4) {  // the four branches for sure: rotations of 180 degrees about x / y / z make the trace -1
            const double ax[4][3] = {{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
            q = k == 0 ? Q{0, 0, 0, 1} : Q{ax[k][0], ax[k][1], ax[k][2], 0};
        }
        st_matrix_of(m, mat, q);
        const double tr = ldf(m, mat) + ldf(m, mat + 20) + ldf(m, mat + 40);
        branches.insert(tr > 0 ? 0 : (ldf(m, mat) >= ldf(m, mat + 20) && ldf(m, mat) >= ldf(m, mat + 40)) ? 1 : ldf(m, mat + 20) >= ldf(m, mat + 40) ? 2 : 3);
        const WPair c = wp(m, "sub_4BDCB0", {qa, mat, 0, 0}, 370000u + static_cast<u32>(k));
        CHECK(c.v0() == 1u);
        CHECK(near_q(ld_q(m, qa), q, 1e-4));
        ++conv;
        // transform vectors
        const u32 n = 1 + rng() % 8;
        std::vector<std::array<double, 3>> in(n);
        for (u32 i = 0; i < n; ++i)
            for (u32 j = 0; j < 3; ++j) {
                const float f = frand(rng, -10.0f, 10.0f);
                in[i][j] = f;
                stf(m, vin + 12 * i + 4 * j, f);
            }
        st_q(m, qb, q);
        wp(m, "sub_4BE1E0", {vout, vin, n, qb}, 371000u + static_cast<u32>(k));
        for (u32 i = 0; i < n; ++i) {
            double o[3];
            qrot(q, in[i].data(), o);
            for (u32 j = 0; j < 3; ++j) CHECK(std::fabs(ldf(m, vout + 12 * i + 4 * j) - o[j]) < 1e-3);
            ++vecs;
        }
        // rotate: replace, pre, post
        double av[3];
        for (double& a : av) a = frand(rng, -2.0f, 2.0f);
        const double an = std::sqrt(av[0] * av[0] + av[1] * av[1] + av[2] * av[2]);
        if (an < 0.1) continue;
        for (u32 j = 0; j < 3; ++j) stf(m, axis + 4 * j, static_cast<float>(av[j]));
        const float deg = frand(rng, -360.0f, 360.0f);
        const double h = deg * 3.14159265358979 / 360.0;
        const Q qa_axis{std::sin(h) * av[0] / an, std::sin(h) * av[1] / an, std::sin(h) * av[2] / an, std::cos(h)};
        st_q(m, qa, q);
        g_fpr[12] = deg;
        const WPair r0 = wp(m, "sub_4BDDE0", {qa, axis, 0, 0}, 372000u + static_cast<u32>(k));
        CHECK(r0.v0() == qa);
        CHECK(near_q(ld_q(m, qa), qa_axis, 1e-3));
        Q got[2];
        for (u32 op = 1; op <= 2; ++op) {
            st_q(m, qa, q);
            g_fpr[12] = deg;
            wp(m, "sub_4BDDE0", {qa, axis, op, 0}, 372500u + static_cast<u32>(k) * 4 + op);
            got[op - 1] = ld_q(m, qa);
        }
        const Q left = qmul(qa_axis, q), right = qmul(q, qa_axis);
        const bool a_left = near_q(got[0], left, 2e-3), a_right = near_q(got[0], right, 2e-3);
        const bool b_left = near_q(got[1], left, 2e-3), b_right = near_q(got[1], right, 2e-3);
        CHECK((a_left || a_right));
        CHECK((b_left || b_right));
        if (!near_q(left, right, 1e-2)) CHECK(a_left != b_left);
        ++rots;
        // an invalid combine type leaves the quaternion and returns 0 ('Invalid combination type')
        st_q(m, qa, q);
        g_fpr[12] = deg;
        const WPair bad = wp(m, "sub_4BDDE0", {qa, axis, 3, 0}, 373000u + static_cast<u32>(k));
        if (!bad.run.stopped) CHECK(near_q(ld_q(m, qa), q, 1e-6));
        // the slerp cache
        const Q to = rand_unit_q(rng);
        st_q(m, qa, q);
        st_q(m, qb, to);
        wp(m, "sub_4BE310", {qa, qb, cache, 0}, 374000u + static_cast<u32>(k));
        const double dot = q.x * to.x + q.y * to.y + q.z * to.z + q.w * to.w;
        const Q from_c = ld_q(m, cache), to_c = ld_q(m, cache + 16);
        const double omega = std::acos(std::min(1.0, std::fabs(dot)));
        CHECK(std::fabs(ldf(m, cache + 32) - omega) < 2e-3);
        const u32 lin = ld(m, cache + 36);
        CHECK(lin == (std::fabs(dot) >= 0.99999 ? 1u : 0u));
        const double sc = lin ? 1.0 : 1.0 / std::sin(omega), sgn = dot < 0 ? -1.0 : 1.0;
        const double tol = 1e-3 * sc;
        CHECK(std::fabs(from_c.x - sc * q.x) + std::fabs(from_c.y - sc * q.y) + std::fabs(from_c.z - sc * q.z) + std::fabs(from_c.w - sc * q.w) < tol);
        CHECK(std::fabs(to_c.x - sc * sgn * to.x) + std::fabs(to_c.y - sc * sgn * to.y) + std::fabs(to_c.z - sc * sgn * to.z) + std::fabs(to_c.w - sc * sgn * to.w) < tol);
        ++slerps;
    }
    CHECK(branches.size() == 4u);
    CHECK(wp(m, "sub_4BDCB0", {0, mat, 0, 0}, 375000u).v0() == 0u);
    CHECK(wp(m, "sub_4BDCB0", {qa, 0, 0, 0}, 375001u).v0() == 0u);
    MESSAGE("RtQuat: " << conv << " matrices, " << vecs << " vectors, " << rots << " rotations, " << slerps << " slerp caches");
}

// =====================================================================================================================
// Built inputs for the recursive walks, then the sweeps
// =====================================================================================================================
// The recursive functions: those that walk a depth argument get it small in the sweeps (index of the argument); those
// that follow pointers (lists, parent chains, the sort's placement, the requirement removal, the ear clipping, the
// plane-sector reader) recurse through any cycle a soup offers, so they run on built inputs below or inside the
// pipeline tests (the topological sort's placement sub_4F3970 runs in every unlock).
const std::map<u32, int> kDepthArg = {{0x4D2130u, 3}, {0x4D2730u, 2}, {0x4D2900u, 2}, {0x4D2ED0u, 2},
                                      {0x4D3040u, 1}, {0x4D3120u, 3}, {0x4D3220u, 2}, {0x4D40E0u, 2}};
const std::set<u32> kNoSoup = {0x4AC240u, 0x4AC410u, 0x4AC710u, 0x4B5270u, 0x4F3970u, 0x4F4DB0u, 0x4B0B10u, 0x48FBD0u};

// Rt2d's object-list walks on built lists of one to six 24-byte records (+0 the string slot, +4 its count or -1 for an
// sList, +20 the next record): the clear frees every slot (RwFree, or the sList destroyed) and zeroes the record; the
// flatten turns the leading sList slots into their arrays with the counts (it stops at the first plain slot); the
// compact runs through the same lists.
TEST_CASE("game(render_rw8): Rt2d's object-list walks on built lists") {
    std::vector<u8> image;
    auto mp = snapshot_machine("b_5800", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot b_5800 not found");
        return;
    }
    Machine& m = *mp;
    std::mt19937 rng{0x4C495354u};
    int lists = 0;
    for (int k = 0; k < 48; ++k) {
        restore(m, image);
        const u32 n = 1 + rng() % 6;
        std::vector<u32> kinds(n);
        for (u32& v : kinds) v = rng() % 3;  // 0 empty, 1 an allocated string, 2 an sList
        const u32 base = kData + 0x1000;
        for (u32 i = 0; i < n; ++i) {
            const u32 r = base + 32 * i;
            std::memset(m.at(r), 0, 32);
            st(m, r + 20, i + 1 < n ? r + 32 : 0);
        }
        auto setup = [&m, kinds, n](StandInWorld& w) {
            install_standard(w);
            for (u32 i = 0; i < n; ++i) {
                const u32 r = base + 32 * i;
                if (kinds[i] == 1) {
                    st(m, r, w.heap.alloc(32));
                    st(m, r + 4, 32);
                } else if (kinds[i] == 2) {
                    const u32 s = w.heap.alloc(16), d = w.heap.alloc(48);
                    st(m, s, d), st(m, s + 4, 1 + i % 3), st(m, s + 8, 4), st(m, s + 12, 12);
                    st(m, r, s);
                    st(m, r + 4, 0xFFFFFFFFu);
                }
            }
        };
        const char* fn = k % 3 == 0 ? "sub_4AC410" : k % 3 == 1 ? "sub_4AC710" : "sub_4AC240";
        const WPair p = wp(m, fn, {base, 0, 0, 0}, 380000u + static_cast<u32>(k), setup);
        CHECK_FALSE(p.run.stopped);
        if (k % 3 == 0) {
            for (u32 i = 0; i < n; ++i) {
                CHECK(ld(m, base + 32 * i) == 0u);
                CHECK(ld(m, base + 32 * i + 4) == 0u);
            }
        } else if (k % 3 == 1) {
            // the walk goes down the list only while the records are sList slots
            bool run = true;
            for (u32 i = 0; i < n; ++i) {
                run = run && kinds[i] == 2;
                if (kinds[i] == 2) CHECK(ld(m, base + 32 * i + 4) == (run ? 1 + i % 3 : 0xFFFFFFFFu));
            }
        }
        ++lists;
    }
    MESSAGE("object-list walks: " << lists << " built lists");
}

// Every body on the three snapshots with built records: a soup of words pointing into itself, at small values and at
// the snapshot's live pipelines, arguments drawn from the soup, small values and the live engine block.
TEST_CASE("game(render_rw8): every body equals its recompiled body on the snapshots with built records") {
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
        std::mt19937 rng{0x52573800u + static_cast<u32>(snapshots)};
        restore(m, image);
        std::vector<u32> live;
        for (const LivePipe& l : live_pipes(m)) live.push_back(l.pipe);
        for (const Case& c : kCases) {
            if (kNoSoup.count(c.addr)) continue;
            for (int k = 0; k < 10; ++k) {
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
                const auto d = kDepthArg.find(c.addr);
                if (d != kDepthArg.end()) {
                    const u32 depth = rng() % 4;
                    a[static_cast<std::size_t>(d->second)] = depth;
                }
                const u32 t0off = rng() % 0x2000;
                const WPair p = wpair(m, c, a, 390000u + static_cast<u32>(pairs), setup, HwCheck{{}, {}, {}, {{GPR_T0, soup + (t0off & ~15u)}, {GPR_T1, soup + 0x600}}});
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
TEST_CASE("game(render_rw8): every body equals its recompiled body on random worlds") {
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
        if (kNoSoup.count(c.addr)) continue;
        std::memcpy(m->mem.main_ram(), elf_image.data(), elf_image.size());
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            Args args{};
            for (std::size_t i = 0; i < 4; ++i) args[i] = hgp::random_arg(rng, kWorld, kWorldSize);
            const auto d = kDepthArg.find(c.addr);
            if (d != kDepthArg.end()) {
                const u32 depth = rng() % 4;
                args[static_cast<std::size_t>(d->second)] = depth;
            }
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
        const std::string summary = std::string(c.name) + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

}  // namespace

#else

TEST_CASE("game(render_rw8): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
