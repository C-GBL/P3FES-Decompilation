// Pair tests of slice render_rw5 (game/src/render/render_rw5.cpp): RenderWare, fifth pass -- cameras, lights,
// materials, the world's object ties and sector walks, clump / atomic / geometry helpers, the collision data, RwV3d,
// images, Im3D. Every body runs against its recompiled body and tests/game/handgen_pairs.h compares the whole register
// file and cycles at every check point and at the return / stop, all 32 MiB of RAM (the dead stack included), the
// scratchpad, the BIOS window and the bus log.
//   * the snapshot sweep: every function on the live RenderWare state of the replay snapshots b_5800,
//     dorm_replay_4900, climb_ref_17000 (skipped when absent) -- the live cameras (perspective and parallel), lights,
//     atomics, clumps, materials, frames, geometries, the world and its BSP sectors -- on fresh stand-in worlds
//     (stand_ins.h: the heap behind the RW memory slots and the free-list entry points, printf, the H_Cdvd layer, a
//     recorder for the walks' callback), with arguments of the kinds each function takes; the stand-ins' call logs and
//     heaps must be equal too;
//   * documented rules on the real objects: the camera sync's frustum (unit plane normals, corners inside all planes,
//     four corners on each plane, the closest-corner bytes, the frustum box) and its z range against the host's
//     arithmetic, the camera setters, the visible-sector list against the host's frustum test, the sector boxes against
//     a host walk of the BSP, light create / colour / the world's light lists, vectors and boxes against the host, the
//     collision block's stream round trip, material create and the material list;
//   * the random-world sweep (the p3fes_handgen skeleton), each function from a fresh ELF image.
// P3FES_HG_SEEDS sets the pairs per function, P3FES_HG_ONLY one function, P3FES_HG_TRACE traces every pair.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/render_rw5.h"

#include <algorithm>
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
void fn_sub_45EC40_0045ec40(EEContext&);  // generated body
void fn_sub_45EC40_0045ec40__recomp(EEContext&);  // recompiled
void fn_sub_45EDC0_0045edc0(EEContext&);  // generated body
void fn_sub_45EDC0_0045edc0__recomp(EEContext&);  // recompiled
void fn_sub_45EDD0_0045edd0(EEContext&);  // generated body
void fn_sub_45EDD0_0045edd0__recomp(EEContext&);  // recompiled
void fn_sub_45EE00_0045ee00(EEContext&);  // generated body
void fn_sub_45EE00_0045ee00__recomp(EEContext&);  // recompiled
void fn_sub_45EFE0_0045efe0(EEContext&);  // generated body
void fn_sub_45EFE0_0045efe0__recomp(EEContext&);  // recompiled
void fn_sub_45F140_0045f140(EEContext&);  // generated body
void fn_sub_45F140_0045f140__recomp(EEContext&);  // recompiled
void fn_sub_45F490_0045f490(EEContext&);  // generated body
void fn_sub_45F490_0045f490__recomp(EEContext&);  // recompiled
void fn_sub_45F4C0_0045f4c0(EEContext&);  // generated body
void fn_sub_45F4C0_0045f4c0__recomp(EEContext&);  // recompiled
void fn_sub_45F4E0_0045f4e0(EEContext&);  // generated body
void fn_sub_45F4E0_0045f4e0__recomp(EEContext&);  // recompiled
void fn_sub_45F530_0045f530(EEContext&);  // generated body
void fn_sub_45F530_0045f530__recomp(EEContext&);  // recompiled
void fn_sub_45F540_0045f540(EEContext&);  // generated body
void fn_sub_45F540_0045f540__recomp(EEContext&);  // recompiled
void fn_sub_45F600_0045f600(EEContext&);  // generated body
void fn_sub_45F600_0045f600__recomp(EEContext&);  // recompiled
void fn_sub_45F7B0_0045f7b0(EEContext&);  // generated body
void fn_sub_45F7B0_0045f7b0__recomp(EEContext&);  // recompiled
void fn_sub_464280_00464280(EEContext&);  // generated body
void fn_sub_464280_00464280__recomp(EEContext&);  // recompiled
void fn_sub_490690_00490690(EEContext&);  // generated body
void fn_sub_490690_00490690__recomp(EEContext&);  // recompiled
void fn_sub_4906B0_004906b0(EEContext&);  // generated body
void fn_sub_4906B0_004906b0__recomp(EEContext&);  // recompiled
void fn_sub_4906F0_004906f0(EEContext&);  // generated body
void fn_sub_4906F0_004906f0__recomp(EEContext&);  // recompiled
void fn_sub_490770_00490770(EEContext&);  // generated body
void fn_sub_490770_00490770__recomp(EEContext&);  // recompiled
void fn_sub_4907E0_004907e0(EEContext&);  // generated body
void fn_sub_4907E0_004907e0__recomp(EEContext&);  // recompiled
void fn_sub_490CA0_00490ca0(EEContext&);  // generated body
void fn_sub_490CA0_00490ca0__recomp(EEContext&);  // recompiled
void fn_sub_490CC0_00490cc0(EEContext&);  // generated body
void fn_sub_490CC0_00490cc0__recomp(EEContext&);  // recompiled
void fn_sub_490CD0_00490cd0(EEContext&);  // generated body
void fn_sub_490CD0_00490cd0__recomp(EEContext&);  // recompiled
void fn_sub_490CF0_00490cf0(EEContext&);  // generated body
void fn_sub_490CF0_00490cf0__recomp(EEContext&);  // recompiled
void fn_sub_490D00_00490d00(EEContext&);  // generated body
void fn_sub_490D00_00490d00__recomp(EEContext&);  // recompiled
void fn_sub_491410_00491410(EEContext&);  // generated body
void fn_sub_491410_00491410__recomp(EEContext&);  // recompiled
void fn_sub_4914D0_004914d0(EEContext&);  // generated body
void fn_sub_4914D0_004914d0__recomp(EEContext&);  // recompiled
void fn_sub_4915C0_004915c0(EEContext&);  // generated body
void fn_sub_4915C0_004915c0__recomp(EEContext&);  // recompiled
void fn_sub_491760_00491760(EEContext&);  // generated body
void fn_sub_491760_00491760__recomp(EEContext&);  // recompiled
void fn_sub_4917F0_004917f0(EEContext&);  // generated body
void fn_sub_4917F0_004917f0__recomp(EEContext&);  // recompiled
void fn_sub_491DE0_00491de0(EEContext&);  // generated body
void fn_sub_491DE0_00491de0__recomp(EEContext&);  // recompiled
void fn_sub_491FF0_00491ff0(EEContext&);  // generated body
void fn_sub_491FF0_00491ff0__recomp(EEContext&);  // recompiled
void fn_sub_492020_00492020(EEContext&);  // generated body
void fn_sub_492020_00492020__recomp(EEContext&);  // recompiled
void fn_sub_492060_00492060(EEContext&);  // generated body
void fn_sub_492060_00492060__recomp(EEContext&);  // recompiled
void fn_sub_492C30_00492c30(EEContext&);  // generated body
void fn_sub_492C30_00492c30__recomp(EEContext&);  // recompiled
void fn_sub_492C60_00492c60(EEContext&);  // generated body
void fn_sub_492C60_00492c60__recomp(EEContext&);  // recompiled
void fn_sub_492C90_00492c90(EEContext&);  // generated body
void fn_sub_492C90_00492c90__recomp(EEContext&);  // recompiled
void fn_sub_492CC0_00492cc0(EEContext&);  // generated body
void fn_sub_492CC0_00492cc0__recomp(EEContext&);  // recompiled
void fn_sub_492CE0_00492ce0(EEContext&);  // generated body
void fn_sub_492CE0_00492ce0__recomp(EEContext&);  // recompiled
void fn_sub_492D00_00492d00(EEContext&);  // generated body
void fn_sub_492D00_00492d00__recomp(EEContext&);  // recompiled
void fn_sub_492DE0_00492de0(EEContext&);  // generated body
void fn_sub_492DE0_00492de0__recomp(EEContext&);  // recompiled
void fn_sub_492E00_00492e00(EEContext&);  // generated body
void fn_sub_492E00_00492e00__recomp(EEContext&);  // recompiled
void fn_sub_492E20_00492e20(EEContext&);  // generated body
void fn_sub_492E20_00492e20__recomp(EEContext&);  // recompiled
void fn_sub_492F80_00492f80(EEContext&);  // generated body
void fn_sub_492F80_00492f80__recomp(EEContext&);  // recompiled
void fn_sub_493210_00493210(EEContext&);  // generated body
void fn_sub_493210_00493210__recomp(EEContext&);  // recompiled
void fn_sub_493230_00493230(EEContext&);  // generated body
void fn_sub_493230_00493230__recomp(EEContext&);  // recompiled
void fn_sub_493B40_00493b40(EEContext&);  // generated body
void fn_sub_493B40_00493b40__recomp(EEContext&);  // recompiled
void fn_sub_493C50_00493c50(EEContext&);  // generated body
void fn_sub_493C50_00493c50__recomp(EEContext&);  // recompiled
void fn_sub_493C80_00493c80(EEContext&);  // generated body
void fn_sub_493C80_00493c80__recomp(EEContext&);  // recompiled
void fn_sub_494490_00494490(EEContext&);  // generated body
void fn_sub_494490_00494490__recomp(EEContext&);  // recompiled
void fn_sub_4944A0_004944a0(EEContext&);  // generated body
void fn_sub_4944A0_004944a0__recomp(EEContext&);  // recompiled
void fn_sub_4944B0_004944b0(EEContext&);  // generated body
void fn_sub_4944B0_004944b0__recomp(EEContext&);  // recompiled
void fn_sub_494520_00494520(EEContext&);  // generated body
void fn_sub_494520_00494520__recomp(EEContext&);  // recompiled
void fn_sub_494550_00494550(EEContext&);  // generated body
void fn_sub_494550_00494550__recomp(EEContext&);  // recompiled
void fn_sub_494760_00494760(EEContext&);  // generated body
void fn_sub_494760_00494760__recomp(EEContext&);  // recompiled
void fn_sub_4947C0_004947c0(EEContext&);  // generated body
void fn_sub_4947C0_004947c0__recomp(EEContext&);  // recompiled
void fn_sub_4948B0_004948b0(EEContext&);  // generated body
void fn_sub_4948B0_004948b0__recomp(EEContext&);  // recompiled
void fn_sub_494930_00494930(EEContext&);  // generated body
void fn_sub_494930_00494930__recomp(EEContext&);  // recompiled
void fn_sub_4949C0_004949c0(EEContext&);  // generated body
void fn_sub_4949C0_004949c0__recomp(EEContext&);  // recompiled
void fn_sub_494A40_00494a40(EEContext&);  // generated body
void fn_sub_494A40_00494a40__recomp(EEContext&);  // recompiled
void fn_sub_494AB0_00494ab0(EEContext&);  // generated body
void fn_sub_494AB0_00494ab0__recomp(EEContext&);  // recompiled
void fn_sub_494AE0_00494ae0(EEContext&);  // generated body
void fn_sub_494AE0_00494ae0__recomp(EEContext&);  // recompiled
void fn_sub_494B70_00494b70(EEContext&);  // generated body
void fn_sub_494B70_00494b70__recomp(EEContext&);  // recompiled
void fn_sub_494BE0_00494be0(EEContext&);  // generated body
void fn_sub_494BE0_00494be0__recomp(EEContext&);  // recompiled
void fn_sub_494DB0_00494db0(EEContext&);  // generated body
void fn_sub_494DB0_00494db0__recomp(EEContext&);  // recompiled
void fn_sub_494DE0_00494de0(EEContext&);  // generated body
void fn_sub_494DE0_00494de0__recomp(EEContext&);  // recompiled
void fn_sub_494E10_00494e10(EEContext&);  // generated body
void fn_sub_494E10_00494e10__recomp(EEContext&);  // recompiled
void fn_sub_495300_00495300(EEContext&);  // generated body
void fn_sub_495300_00495300__recomp(EEContext&);  // recompiled
void fn_sub_495340_00495340(EEContext&);  // generated body
void fn_sub_495340_00495340__recomp(EEContext&);  // recompiled
void fn_sub_495480_00495480(EEContext&);  // generated body
void fn_sub_495480_00495480__recomp(EEContext&);  // recompiled
void fn_sub_4959C0_004959c0(EEContext&);  // generated body
void fn_sub_4959C0_004959c0__recomp(EEContext&);  // recompiled
void fn_sub_4959E0_004959e0(EEContext&);  // generated body
void fn_sub_4959E0_004959e0__recomp(EEContext&);  // recompiled
void fn_sub_495A30_00495a30(EEContext&);  // generated body
void fn_sub_495A30_00495a30__recomp(EEContext&);  // recompiled
void fn_sub_495B10_00495b10(EEContext&);  // generated body
void fn_sub_495B10_00495b10__recomp(EEContext&);  // recompiled
void fn_sub_495C20_00495c20(EEContext&);  // generated body
void fn_sub_495C20_00495c20__recomp(EEContext&);  // recompiled
void fn_sub_495C80_00495c80(EEContext&);  // generated body
void fn_sub_495C80_00495c80__recomp(EEContext&);  // recompiled
void fn_sub_4991F0_004991f0(EEContext&);  // generated body
void fn_sub_4991F0_004991f0__recomp(EEContext&);  // recompiled
void fn_sub_499210_00499210(EEContext&);  // generated body
void fn_sub_499210_00499210__recomp(EEContext&);  // recompiled
void fn_sub_499250_00499250(EEContext&);  // generated body
void fn_sub_499250_00499250__recomp(EEContext&);  // recompiled
void fn_sub_499280_00499280(EEContext&);  // generated body
void fn_sub_499280_00499280__recomp(EEContext&);  // recompiled
void fn_sub_4992B0_004992b0(EEContext&);  // generated body
void fn_sub_4992B0_004992b0__recomp(EEContext&);  // recompiled
void fn_sub_4992D0_004992d0(EEContext&);  // generated body
void fn_sub_4992D0_004992d0__recomp(EEContext&);  // recompiled
void fn_sub_499400_00499400(EEContext&);  // generated body
void fn_sub_499400_00499400__recomp(EEContext&);  // recompiled
void fn_sub_499D30_00499d30(EEContext&);  // generated body
void fn_sub_499D30_00499d30__recomp(EEContext&);  // recompiled
void fn_sub_499E90_00499e90(EEContext&);  // generated body
void fn_sub_499E90_00499e90__recomp(EEContext&);  // recompiled
void fn_sub_499F40_00499f40(EEContext&);  // generated body
void fn_sub_499F40_00499f40__recomp(EEContext&);  // recompiled
void fn_sub_499FD0_00499fd0(EEContext&);  // generated body
void fn_sub_499FD0_00499fd0__recomp(EEContext&);  // recompiled
void fn_sub_49A080_0049a080(EEContext&);  // generated body
void fn_sub_49A080_0049a080__recomp(EEContext&);  // recompiled
void fn_sub_49A7C0_0049a7c0(EEContext&);  // generated body
void fn_sub_49A7C0_0049a7c0__recomp(EEContext&);  // recompiled
void fn_sub_49A920_0049a920(EEContext&);  // generated body
void fn_sub_49A920_0049a920__recomp(EEContext&);  // recompiled
void fn_sub_49A950_0049a950(EEContext&);  // generated body
void fn_sub_49A950_0049a950__recomp(EEContext&);  // recompiled
void fn_sub_49AAF0_0049aaf0(EEContext&);  // generated body
void fn_sub_49AAF0_0049aaf0__recomp(EEContext&);  // recompiled
void fn_sub_49ABF0_0049abf0(EEContext&);  // generated body
void fn_sub_49ABF0_0049abf0__recomp(EEContext&);  // recompiled
void fn_sub_49AC90_0049ac90(EEContext&);  // generated body
void fn_sub_49AC90_0049ac90__recomp(EEContext&);  // recompiled
void fn_sub_49ACD0_0049acd0(EEContext&);  // generated body
void fn_sub_49ACD0_0049acd0__recomp(EEContext&);  // recompiled
void fn_sub_49ACF0_0049acf0(EEContext&);  // generated body
void fn_sub_49ACF0_0049acf0__recomp(EEContext&);  // recompiled
void fn_sub_49AD80_0049ad80(EEContext&);  // generated body
void fn_sub_49AD80_0049ad80__recomp(EEContext&);  // recompiled
void fn_sub_49ADE0_0049ade0(EEContext&);  // generated body
void fn_sub_49ADE0_0049ade0__recomp(EEContext&);  // recompiled
void fn_sub_49AE30_0049ae30(EEContext&);  // generated body
void fn_sub_49AE30_0049ae30__recomp(EEContext&);  // recompiled
void fn_sub_49AEB0_0049aeb0(EEContext&);  // generated body
void fn_sub_49AEB0_0049aeb0__recomp(EEContext&);  // recompiled
void fn_sub_49AF20_0049af20(EEContext&);  // generated body
void fn_sub_49AF20_0049af20__recomp(EEContext&);  // recompiled
void fn_sub_49AFA0_0049afa0(EEContext&);  // generated body
void fn_sub_49AFA0_0049afa0__recomp(EEContext&);  // recompiled
void fn_sub_49B180_0049b180(EEContext&);  // generated body
void fn_sub_49B180_0049b180__recomp(EEContext&);  // recompiled
void fn_sub_49B290_0049b290(EEContext&);  // generated body
void fn_sub_49B290_0049b290__recomp(EEContext&);  // recompiled
void fn_sub_49B2D0_0049b2d0(EEContext&);  // generated body
void fn_sub_49B2D0_0049b2d0__recomp(EEContext&);  // recompiled
void fn_sub_49B2E0_0049b2e0(EEContext&);  // generated body
void fn_sub_49B2E0_0049b2e0__recomp(EEContext&);  // recompiled
void fn_sub_49B3C0_0049b3c0(EEContext&);  // generated body
void fn_sub_49B3C0_0049b3c0__recomp(EEContext&);  // recompiled
void fn_sub_49B430_0049b430(EEContext&);  // generated body
void fn_sub_49B430_0049b430__recomp(EEContext&);  // recompiled
void fn_sub_49B440_0049b440(EEContext&);  // generated body
void fn_sub_49B440_0049b440__recomp(EEContext&);  // recompiled
void fn_sub_49B730_0049b730(EEContext&);  // generated body
void fn_sub_49B730_0049b730__recomp(EEContext&);  // recompiled
void fn_sub_49B760_0049b760(EEContext&);  // generated body
void fn_sub_49B760_0049b760__recomp(EEContext&);  // recompiled
void fn_sub_49B7A0_0049b7a0(EEContext&);  // generated body
void fn_sub_49B7A0_0049b7a0__recomp(EEContext&);  // recompiled
void fn_sub_49B850_0049b850(EEContext&);  // generated body
void fn_sub_49B850_0049b850__recomp(EEContext&);  // recompiled
void fn_sub_49BBC0_0049bbc0(EEContext&);  // generated body
void fn_sub_49BBC0_0049bbc0__recomp(EEContext&);  // recompiled
void fn_sub_49BBF0_0049bbf0(EEContext&);  // generated body
void fn_sub_49BBF0_0049bbf0__recomp(EEContext&);  // recompiled
void fn_sub_49BC20_0049bc20(EEContext&);  // generated body
void fn_sub_49BC20_0049bc20__recomp(EEContext&);  // recompiled
void fn_sub_49C160_0049c160(EEContext&);  // generated body
void fn_sub_49C160_0049c160__recomp(EEContext&);  // recompiled
void fn_sub_49C1B0_0049c1b0(EEContext&);  // generated body
void fn_sub_49C1B0_0049c1b0__recomp(EEContext&);  // recompiled
void fn_sub_49C1E0_0049c1e0(EEContext&);  // generated body
void fn_sub_49C1E0_0049c1e0__recomp(EEContext&);  // recompiled
void fn_sub_49C230_0049c230(EEContext&);  // generated body
void fn_sub_49C230_0049c230__recomp(EEContext&);  // recompiled
void fn_sub_49C3D0_0049c3d0(EEContext&);  // generated body
void fn_sub_49C3D0_0049c3d0__recomp(EEContext&);  // recompiled
void fn_sub_49C480_0049c480(EEContext&);  // generated body
void fn_sub_49C480_0049c480__recomp(EEContext&);  // recompiled
void fn_sub_49C560_0049c560(EEContext&);  // generated body
void fn_sub_49C560_0049c560__recomp(EEContext&);  // recompiled
void fn_sub_49C5C0_0049c5c0(EEContext&);  // generated body
void fn_sub_49C5C0_0049c5c0__recomp(EEContext&);  // recompiled
void fn_sub_49C620_0049c620(EEContext&);  // generated body
void fn_sub_49C620_0049c620__recomp(EEContext&);  // recompiled
void fn_sub_49C790_0049c790(EEContext&);  // generated body
void fn_sub_49C790_0049c790__recomp(EEContext&);  // recompiled
void fn_sub_4C69F0_004c69f0(EEContext&);  // generated body
void fn_sub_4C69F0_004c69f0__recomp(EEContext&);  // recompiled
void fn_sub_4C6AC0_004c6ac0(EEContext&);  // generated body
void fn_sub_4C6AC0_004c6ac0__recomp(EEContext&);  // recompiled
void fn_sub_4C6AF0_004c6af0(EEContext&);  // generated body
void fn_sub_4C6AF0_004c6af0__recomp(EEContext&);  // recompiled
void fn_sub_4C6B20_004c6b20(EEContext&);  // generated body
void fn_sub_4C6B20_004c6b20__recomp(EEContext&);  // recompiled
void fn_sub_4C6C20_004c6c20(EEContext&);  // generated body
void fn_sub_4C6C20_004c6c20__recomp(EEContext&);  // recompiled
void fn_sub_4C6CA0_004c6ca0(EEContext&);  // generated body
void fn_sub_4C6CA0_004c6ca0__recomp(EEContext&);  // recompiled
void fn_sub_4C6CE0_004c6ce0(EEContext&);  // generated body
void fn_sub_4C6CE0_004c6ce0__recomp(EEContext&);  // recompiled
void fn_sub_4C7A50_004c7a50(EEContext&);  // generated body
void fn_sub_4C7A50_004c7a50__recomp(EEContext&);  // recompiled
void fn_sub_4C89A0_004c89a0(EEContext&);  // generated body
void fn_sub_4C89A0_004c89a0__recomp(EEContext&);  // recompiled
void fn_sub_4C8A60_004c8a60(EEContext&);  // generated body
void fn_sub_4C8A60_004c8a60__recomp(EEContext&);  // recompiled
void fn_sub_4C9270_004c9270(EEContext&);  // generated body
void fn_sub_4C9270_004c9270__recomp(EEContext&);  // recompiled
void fn_sub_4C9400_004c9400(EEContext&);  // generated body
void fn_sub_4C9400_004c9400__recomp(EEContext&);  // recompiled
void fn_sub_4C9940_004c9940(EEContext&);  // generated body
void fn_sub_4C9940_004c9940__recomp(EEContext&);  // recompiled
void fn_sub_4C9AD0_004c9ad0(EEContext&);  // generated body
void fn_sub_4C9AD0_004c9ad0__recomp(EEContext&);  // recompiled
void fn_CameraEndUpdate_004c9b40(EEContext&);  // generated body
void fn_CameraEndUpdate_004c9b40__recomp(EEContext&);  // recompiled
void fn_CameraBeginUpdate_004c9ba0(EEContext&);  // generated body
void fn_CameraBeginUpdate_004c9ba0__recomp(EEContext&);  // recompiled
void fn_sub_4C9C00_004c9c00(EEContext&);  // generated body
void fn_sub_4C9C00_004c9c00__recomp(EEContext&);  // recompiled
void fn_sub_4C9C70_004c9c70(EEContext&);  // generated body
void fn_sub_4C9C70_004c9c70__recomp(EEContext&);  // recompiled
void fn_sub_4C9D20_004c9d20(EEContext&);  // generated body
void fn_sub_4C9D20_004c9d20__recomp(EEContext&);  // recompiled
void fn_sub_4C9DB0_004c9db0(EEContext&);  // generated body
void fn_sub_4C9DB0_004c9db0__recomp(EEContext&);  // recompiled
void fn_sub_4C9F00_004c9f00(EEContext&);  // generated body
void fn_sub_4C9F00_004c9f00__recomp(EEContext&);  // recompiled
void fn_sub_4C9F90_004c9f90(EEContext&);  // generated body
void fn_sub_4C9F90_004c9f90__recomp(EEContext&);  // recompiled
void fn_sub_4CA000_004ca000(EEContext&);  // generated body
void fn_sub_4CA000_004ca000__recomp(EEContext&);  // recompiled
void fn_sub_4CA090_004ca090(EEContext&);  // generated body
void fn_sub_4CA090_004ca090__recomp(EEContext&);  // recompiled
void fn_sub_4CBC70_004cbc70(EEContext&);  // generated body
void fn_sub_4CBC70_004cbc70__recomp(EEContext&);  // recompiled
void fn_sub_4CBE00_004cbe00(EEContext&);  // generated body
void fn_sub_4CBE00_004cbe00__recomp(EEContext&);  // recompiled
void fn_sub_4CBEB0_004cbeb0(EEContext&);  // generated body
void fn_sub_4CBEB0_004cbeb0__recomp(EEContext&);  // recompiled
void fn_sub_4CC050_004cc050(EEContext&);  // generated body
void fn_sub_4CC050_004cc050__recomp(EEContext&);  // recompiled
void fn_sub_4CC6B0_004cc6b0(EEContext&);  // generated body
void fn_sub_4CC6B0_004cc6b0__recomp(EEContext&);  // recompiled
void fn_sub_4CD750_004cd750(EEContext&);  // generated body
void fn_sub_4CD750_004cd750__recomp(EEContext&);  // recompiled
void fn_sub_4D18C0_004d18c0(EEContext&);  // generated body
void fn_sub_4D18C0_004d18c0__recomp(EEContext&);  // recompiled
void fn_sub_4F23C0_004f23c0(EEContext&);  // generated body
void fn_sub_4F23C0_004f23c0__recomp(EEContext&);  // recompiled
void fn_sub_4F2430_004f2430(EEContext&);  // generated body
void fn_sub_4F2430_004f2430__recomp(EEContext&);  // recompiled
void fn_sub_4F28E0_004f28e0(EEContext&);  // generated body
void fn_sub_4F28E0_004f28e0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_45EC40", 0x45EC40, &recomp_gen::fn_sub_45EC40_0045ec40, &recomp_gen::fn_sub_45EC40_0045ec40__recomp},
    {"sub_45EDC0", 0x45EDC0, &recomp_gen::fn_sub_45EDC0_0045edc0, &recomp_gen::fn_sub_45EDC0_0045edc0__recomp},
    {"sub_45EDD0", 0x45EDD0, &recomp_gen::fn_sub_45EDD0_0045edd0, &recomp_gen::fn_sub_45EDD0_0045edd0__recomp},
    {"sub_45EE00", 0x45EE00, &recomp_gen::fn_sub_45EE00_0045ee00, &recomp_gen::fn_sub_45EE00_0045ee00__recomp},
    {"sub_45EFE0", 0x45EFE0, &recomp_gen::fn_sub_45EFE0_0045efe0, &recomp_gen::fn_sub_45EFE0_0045efe0__recomp},
    {"sub_45F140", 0x45F140, &recomp_gen::fn_sub_45F140_0045f140, &recomp_gen::fn_sub_45F140_0045f140__recomp},
    {"sub_45F490", 0x45F490, &recomp_gen::fn_sub_45F490_0045f490, &recomp_gen::fn_sub_45F490_0045f490__recomp},
    {"sub_45F4C0", 0x45F4C0, &recomp_gen::fn_sub_45F4C0_0045f4c0, &recomp_gen::fn_sub_45F4C0_0045f4c0__recomp},
    {"sub_45F4E0", 0x45F4E0, &recomp_gen::fn_sub_45F4E0_0045f4e0, &recomp_gen::fn_sub_45F4E0_0045f4e0__recomp},
    {"sub_45F530", 0x45F530, &recomp_gen::fn_sub_45F530_0045f530, &recomp_gen::fn_sub_45F530_0045f530__recomp},
    {"sub_45F540", 0x45F540, &recomp_gen::fn_sub_45F540_0045f540, &recomp_gen::fn_sub_45F540_0045f540__recomp},
    {"sub_45F600", 0x45F600, &recomp_gen::fn_sub_45F600_0045f600, &recomp_gen::fn_sub_45F600_0045f600__recomp},
    {"sub_45F7B0", 0x45F7B0, &recomp_gen::fn_sub_45F7B0_0045f7b0, &recomp_gen::fn_sub_45F7B0_0045f7b0__recomp},
    {"sub_464280", 0x464280, &recomp_gen::fn_sub_464280_00464280, &recomp_gen::fn_sub_464280_00464280__recomp},
    {"sub_490690", 0x490690, &recomp_gen::fn_sub_490690_00490690, &recomp_gen::fn_sub_490690_00490690__recomp},
    {"sub_4906B0", 0x4906B0, &recomp_gen::fn_sub_4906B0_004906b0, &recomp_gen::fn_sub_4906B0_004906b0__recomp},
    {"sub_4906F0", 0x4906F0, &recomp_gen::fn_sub_4906F0_004906f0, &recomp_gen::fn_sub_4906F0_004906f0__recomp},
    {"sub_490770", 0x490770, &recomp_gen::fn_sub_490770_00490770, &recomp_gen::fn_sub_490770_00490770__recomp},
    {"sub_4907E0", 0x4907E0, &recomp_gen::fn_sub_4907E0_004907e0, &recomp_gen::fn_sub_4907E0_004907e0__recomp},
    {"sub_490CA0", 0x490CA0, &recomp_gen::fn_sub_490CA0_00490ca0, &recomp_gen::fn_sub_490CA0_00490ca0__recomp},
    {"sub_490CC0", 0x490CC0, &recomp_gen::fn_sub_490CC0_00490cc0, &recomp_gen::fn_sub_490CC0_00490cc0__recomp},
    {"sub_490CD0", 0x490CD0, &recomp_gen::fn_sub_490CD0_00490cd0, &recomp_gen::fn_sub_490CD0_00490cd0__recomp},
    {"sub_490CF0", 0x490CF0, &recomp_gen::fn_sub_490CF0_00490cf0, &recomp_gen::fn_sub_490CF0_00490cf0__recomp},
    {"sub_490D00", 0x490D00, &recomp_gen::fn_sub_490D00_00490d00, &recomp_gen::fn_sub_490D00_00490d00__recomp},
    {"sub_491410", 0x491410, &recomp_gen::fn_sub_491410_00491410, &recomp_gen::fn_sub_491410_00491410__recomp},
    {"sub_4914D0", 0x4914D0, &recomp_gen::fn_sub_4914D0_004914d0, &recomp_gen::fn_sub_4914D0_004914d0__recomp},
    {"sub_4915C0", 0x4915C0, &recomp_gen::fn_sub_4915C0_004915c0, &recomp_gen::fn_sub_4915C0_004915c0__recomp},
    {"sub_491760", 0x491760, &recomp_gen::fn_sub_491760_00491760, &recomp_gen::fn_sub_491760_00491760__recomp},
    {"sub_4917F0", 0x4917F0, &recomp_gen::fn_sub_4917F0_004917f0, &recomp_gen::fn_sub_4917F0_004917f0__recomp},
    {"sub_491DE0", 0x491DE0, &recomp_gen::fn_sub_491DE0_00491de0, &recomp_gen::fn_sub_491DE0_00491de0__recomp},
    {"sub_491FF0", 0x491FF0, &recomp_gen::fn_sub_491FF0_00491ff0, &recomp_gen::fn_sub_491FF0_00491ff0__recomp},
    {"sub_492020", 0x492020, &recomp_gen::fn_sub_492020_00492020, &recomp_gen::fn_sub_492020_00492020__recomp},
    {"sub_492060", 0x492060, &recomp_gen::fn_sub_492060_00492060, &recomp_gen::fn_sub_492060_00492060__recomp},
    {"sub_492C30", 0x492C30, &recomp_gen::fn_sub_492C30_00492c30, &recomp_gen::fn_sub_492C30_00492c30__recomp},
    {"sub_492C60", 0x492C60, &recomp_gen::fn_sub_492C60_00492c60, &recomp_gen::fn_sub_492C60_00492c60__recomp},
    {"sub_492C90", 0x492C90, &recomp_gen::fn_sub_492C90_00492c90, &recomp_gen::fn_sub_492C90_00492c90__recomp},
    {"sub_492CC0", 0x492CC0, &recomp_gen::fn_sub_492CC0_00492cc0, &recomp_gen::fn_sub_492CC0_00492cc0__recomp},
    {"sub_492CE0", 0x492CE0, &recomp_gen::fn_sub_492CE0_00492ce0, &recomp_gen::fn_sub_492CE0_00492ce0__recomp},
    {"sub_492D00", 0x492D00, &recomp_gen::fn_sub_492D00_00492d00, &recomp_gen::fn_sub_492D00_00492d00__recomp},
    {"sub_492DE0", 0x492DE0, &recomp_gen::fn_sub_492DE0_00492de0, &recomp_gen::fn_sub_492DE0_00492de0__recomp},
    {"sub_492E00", 0x492E00, &recomp_gen::fn_sub_492E00_00492e00, &recomp_gen::fn_sub_492E00_00492e00__recomp},
    {"sub_492E20", 0x492E20, &recomp_gen::fn_sub_492E20_00492e20, &recomp_gen::fn_sub_492E20_00492e20__recomp},
    {"sub_492F80", 0x492F80, &recomp_gen::fn_sub_492F80_00492f80, &recomp_gen::fn_sub_492F80_00492f80__recomp},
    {"sub_493210", 0x493210, &recomp_gen::fn_sub_493210_00493210, &recomp_gen::fn_sub_493210_00493210__recomp},
    {"sub_493230", 0x493230, &recomp_gen::fn_sub_493230_00493230, &recomp_gen::fn_sub_493230_00493230__recomp},
    {"sub_493B40", 0x493B40, &recomp_gen::fn_sub_493B40_00493b40, &recomp_gen::fn_sub_493B40_00493b40__recomp},
    {"sub_493C50", 0x493C50, &recomp_gen::fn_sub_493C50_00493c50, &recomp_gen::fn_sub_493C50_00493c50__recomp},
    {"sub_493C80", 0x493C80, &recomp_gen::fn_sub_493C80_00493c80, &recomp_gen::fn_sub_493C80_00493c80__recomp},
    {"sub_494490", 0x494490, &recomp_gen::fn_sub_494490_00494490, &recomp_gen::fn_sub_494490_00494490__recomp},
    {"sub_4944A0", 0x4944A0, &recomp_gen::fn_sub_4944A0_004944a0, &recomp_gen::fn_sub_4944A0_004944a0__recomp},
    {"sub_4944B0", 0x4944B0, &recomp_gen::fn_sub_4944B0_004944b0, &recomp_gen::fn_sub_4944B0_004944b0__recomp},
    {"sub_494520", 0x494520, &recomp_gen::fn_sub_494520_00494520, &recomp_gen::fn_sub_494520_00494520__recomp},
    {"sub_494550", 0x494550, &recomp_gen::fn_sub_494550_00494550, &recomp_gen::fn_sub_494550_00494550__recomp},
    {"sub_494760", 0x494760, &recomp_gen::fn_sub_494760_00494760, &recomp_gen::fn_sub_494760_00494760__recomp},
    {"sub_4947C0", 0x4947C0, &recomp_gen::fn_sub_4947C0_004947c0, &recomp_gen::fn_sub_4947C0_004947c0__recomp},
    {"sub_4948B0", 0x4948B0, &recomp_gen::fn_sub_4948B0_004948b0, &recomp_gen::fn_sub_4948B0_004948b0__recomp},
    {"sub_494930", 0x494930, &recomp_gen::fn_sub_494930_00494930, &recomp_gen::fn_sub_494930_00494930__recomp},
    {"sub_4949C0", 0x4949C0, &recomp_gen::fn_sub_4949C0_004949c0, &recomp_gen::fn_sub_4949C0_004949c0__recomp},
    {"sub_494A40", 0x494A40, &recomp_gen::fn_sub_494A40_00494a40, &recomp_gen::fn_sub_494A40_00494a40__recomp},
    {"sub_494AB0", 0x494AB0, &recomp_gen::fn_sub_494AB0_00494ab0, &recomp_gen::fn_sub_494AB0_00494ab0__recomp},
    {"sub_494AE0", 0x494AE0, &recomp_gen::fn_sub_494AE0_00494ae0, &recomp_gen::fn_sub_494AE0_00494ae0__recomp},
    {"sub_494B70", 0x494B70, &recomp_gen::fn_sub_494B70_00494b70, &recomp_gen::fn_sub_494B70_00494b70__recomp},
    {"sub_494BE0", 0x494BE0, &recomp_gen::fn_sub_494BE0_00494be0, &recomp_gen::fn_sub_494BE0_00494be0__recomp},
    {"sub_494DB0", 0x494DB0, &recomp_gen::fn_sub_494DB0_00494db0, &recomp_gen::fn_sub_494DB0_00494db0__recomp},
    {"sub_494DE0", 0x494DE0, &recomp_gen::fn_sub_494DE0_00494de0, &recomp_gen::fn_sub_494DE0_00494de0__recomp},
    {"sub_494E10", 0x494E10, &recomp_gen::fn_sub_494E10_00494e10, &recomp_gen::fn_sub_494E10_00494e10__recomp},
    {"sub_495300", 0x495300, &recomp_gen::fn_sub_495300_00495300, &recomp_gen::fn_sub_495300_00495300__recomp},
    {"sub_495340", 0x495340, &recomp_gen::fn_sub_495340_00495340, &recomp_gen::fn_sub_495340_00495340__recomp},
    {"sub_495480", 0x495480, &recomp_gen::fn_sub_495480_00495480, &recomp_gen::fn_sub_495480_00495480__recomp},
    {"sub_4959C0", 0x4959C0, &recomp_gen::fn_sub_4959C0_004959c0, &recomp_gen::fn_sub_4959C0_004959c0__recomp},
    {"sub_4959E0", 0x4959E0, &recomp_gen::fn_sub_4959E0_004959e0, &recomp_gen::fn_sub_4959E0_004959e0__recomp},
    {"sub_495A30", 0x495A30, &recomp_gen::fn_sub_495A30_00495a30, &recomp_gen::fn_sub_495A30_00495a30__recomp},
    {"sub_495B10", 0x495B10, &recomp_gen::fn_sub_495B10_00495b10, &recomp_gen::fn_sub_495B10_00495b10__recomp},
    {"sub_495C20", 0x495C20, &recomp_gen::fn_sub_495C20_00495c20, &recomp_gen::fn_sub_495C20_00495c20__recomp},
    {"sub_495C80", 0x495C80, &recomp_gen::fn_sub_495C80_00495c80, &recomp_gen::fn_sub_495C80_00495c80__recomp},
    {"sub_4991F0", 0x4991F0, &recomp_gen::fn_sub_4991F0_004991f0, &recomp_gen::fn_sub_4991F0_004991f0__recomp},
    {"sub_499210", 0x499210, &recomp_gen::fn_sub_499210_00499210, &recomp_gen::fn_sub_499210_00499210__recomp},
    {"sub_499250", 0x499250, &recomp_gen::fn_sub_499250_00499250, &recomp_gen::fn_sub_499250_00499250__recomp},
    {"sub_499280", 0x499280, &recomp_gen::fn_sub_499280_00499280, &recomp_gen::fn_sub_499280_00499280__recomp},
    {"sub_4992B0", 0x4992B0, &recomp_gen::fn_sub_4992B0_004992b0, &recomp_gen::fn_sub_4992B0_004992b0__recomp},
    {"sub_4992D0", 0x4992D0, &recomp_gen::fn_sub_4992D0_004992d0, &recomp_gen::fn_sub_4992D0_004992d0__recomp},
    {"sub_499400", 0x499400, &recomp_gen::fn_sub_499400_00499400, &recomp_gen::fn_sub_499400_00499400__recomp},
    {"sub_499D30", 0x499D30, &recomp_gen::fn_sub_499D30_00499d30, &recomp_gen::fn_sub_499D30_00499d30__recomp},
    {"sub_499E90", 0x499E90, &recomp_gen::fn_sub_499E90_00499e90, &recomp_gen::fn_sub_499E90_00499e90__recomp},
    {"sub_499F40", 0x499F40, &recomp_gen::fn_sub_499F40_00499f40, &recomp_gen::fn_sub_499F40_00499f40__recomp},
    {"sub_499FD0", 0x499FD0, &recomp_gen::fn_sub_499FD0_00499fd0, &recomp_gen::fn_sub_499FD0_00499fd0__recomp},
    {"sub_49A080", 0x49A080, &recomp_gen::fn_sub_49A080_0049a080, &recomp_gen::fn_sub_49A080_0049a080__recomp},
    {"sub_49A7C0", 0x49A7C0, &recomp_gen::fn_sub_49A7C0_0049a7c0, &recomp_gen::fn_sub_49A7C0_0049a7c0__recomp},
    {"sub_49A920", 0x49A920, &recomp_gen::fn_sub_49A920_0049a920, &recomp_gen::fn_sub_49A920_0049a920__recomp},
    {"sub_49A950", 0x49A950, &recomp_gen::fn_sub_49A950_0049a950, &recomp_gen::fn_sub_49A950_0049a950__recomp},
    {"sub_49AAF0", 0x49AAF0, &recomp_gen::fn_sub_49AAF0_0049aaf0, &recomp_gen::fn_sub_49AAF0_0049aaf0__recomp},
    {"sub_49ABF0", 0x49ABF0, &recomp_gen::fn_sub_49ABF0_0049abf0, &recomp_gen::fn_sub_49ABF0_0049abf0__recomp},
    {"sub_49AC90", 0x49AC90, &recomp_gen::fn_sub_49AC90_0049ac90, &recomp_gen::fn_sub_49AC90_0049ac90__recomp},
    {"sub_49ACD0", 0x49ACD0, &recomp_gen::fn_sub_49ACD0_0049acd0, &recomp_gen::fn_sub_49ACD0_0049acd0__recomp},
    {"sub_49ACF0", 0x49ACF0, &recomp_gen::fn_sub_49ACF0_0049acf0, &recomp_gen::fn_sub_49ACF0_0049acf0__recomp},
    {"sub_49AD80", 0x49AD80, &recomp_gen::fn_sub_49AD80_0049ad80, &recomp_gen::fn_sub_49AD80_0049ad80__recomp},
    {"sub_49ADE0", 0x49ADE0, &recomp_gen::fn_sub_49ADE0_0049ade0, &recomp_gen::fn_sub_49ADE0_0049ade0__recomp},
    {"sub_49AE30", 0x49AE30, &recomp_gen::fn_sub_49AE30_0049ae30, &recomp_gen::fn_sub_49AE30_0049ae30__recomp},
    {"sub_49AEB0", 0x49AEB0, &recomp_gen::fn_sub_49AEB0_0049aeb0, &recomp_gen::fn_sub_49AEB0_0049aeb0__recomp},
    {"sub_49AF20", 0x49AF20, &recomp_gen::fn_sub_49AF20_0049af20, &recomp_gen::fn_sub_49AF20_0049af20__recomp},
    {"sub_49AFA0", 0x49AFA0, &recomp_gen::fn_sub_49AFA0_0049afa0, &recomp_gen::fn_sub_49AFA0_0049afa0__recomp},
    {"sub_49B180", 0x49B180, &recomp_gen::fn_sub_49B180_0049b180, &recomp_gen::fn_sub_49B180_0049b180__recomp},
    {"sub_49B290", 0x49B290, &recomp_gen::fn_sub_49B290_0049b290, &recomp_gen::fn_sub_49B290_0049b290__recomp},
    {"sub_49B2D0", 0x49B2D0, &recomp_gen::fn_sub_49B2D0_0049b2d0, &recomp_gen::fn_sub_49B2D0_0049b2d0__recomp},
    {"sub_49B2E0", 0x49B2E0, &recomp_gen::fn_sub_49B2E0_0049b2e0, &recomp_gen::fn_sub_49B2E0_0049b2e0__recomp},
    {"sub_49B3C0", 0x49B3C0, &recomp_gen::fn_sub_49B3C0_0049b3c0, &recomp_gen::fn_sub_49B3C0_0049b3c0__recomp},
    {"sub_49B430", 0x49B430, &recomp_gen::fn_sub_49B430_0049b430, &recomp_gen::fn_sub_49B430_0049b430__recomp},
    {"sub_49B440", 0x49B440, &recomp_gen::fn_sub_49B440_0049b440, &recomp_gen::fn_sub_49B440_0049b440__recomp},
    {"sub_49B730", 0x49B730, &recomp_gen::fn_sub_49B730_0049b730, &recomp_gen::fn_sub_49B730_0049b730__recomp},
    {"sub_49B760", 0x49B760, &recomp_gen::fn_sub_49B760_0049b760, &recomp_gen::fn_sub_49B760_0049b760__recomp},
    {"sub_49B7A0", 0x49B7A0, &recomp_gen::fn_sub_49B7A0_0049b7a0, &recomp_gen::fn_sub_49B7A0_0049b7a0__recomp},
    {"sub_49B850", 0x49B850, &recomp_gen::fn_sub_49B850_0049b850, &recomp_gen::fn_sub_49B850_0049b850__recomp},
    {"sub_49BBC0", 0x49BBC0, &recomp_gen::fn_sub_49BBC0_0049bbc0, &recomp_gen::fn_sub_49BBC0_0049bbc0__recomp},
    {"sub_49BBF0", 0x49BBF0, &recomp_gen::fn_sub_49BBF0_0049bbf0, &recomp_gen::fn_sub_49BBF0_0049bbf0__recomp},
    {"sub_49BC20", 0x49BC20, &recomp_gen::fn_sub_49BC20_0049bc20, &recomp_gen::fn_sub_49BC20_0049bc20__recomp},
    {"sub_49C160", 0x49C160, &recomp_gen::fn_sub_49C160_0049c160, &recomp_gen::fn_sub_49C160_0049c160__recomp},
    {"sub_49C1B0", 0x49C1B0, &recomp_gen::fn_sub_49C1B0_0049c1b0, &recomp_gen::fn_sub_49C1B0_0049c1b0__recomp},
    {"sub_49C1E0", 0x49C1E0, &recomp_gen::fn_sub_49C1E0_0049c1e0, &recomp_gen::fn_sub_49C1E0_0049c1e0__recomp},
    {"sub_49C230", 0x49C230, &recomp_gen::fn_sub_49C230_0049c230, &recomp_gen::fn_sub_49C230_0049c230__recomp},
    {"sub_49C3D0", 0x49C3D0, &recomp_gen::fn_sub_49C3D0_0049c3d0, &recomp_gen::fn_sub_49C3D0_0049c3d0__recomp},
    {"sub_49C480", 0x49C480, &recomp_gen::fn_sub_49C480_0049c480, &recomp_gen::fn_sub_49C480_0049c480__recomp},
    {"sub_49C560", 0x49C560, &recomp_gen::fn_sub_49C560_0049c560, &recomp_gen::fn_sub_49C560_0049c560__recomp},
    {"sub_49C5C0", 0x49C5C0, &recomp_gen::fn_sub_49C5C0_0049c5c0, &recomp_gen::fn_sub_49C5C0_0049c5c0__recomp},
    {"sub_49C620", 0x49C620, &recomp_gen::fn_sub_49C620_0049c620, &recomp_gen::fn_sub_49C620_0049c620__recomp},
    {"sub_49C790", 0x49C790, &recomp_gen::fn_sub_49C790_0049c790, &recomp_gen::fn_sub_49C790_0049c790__recomp},
    {"sub_4C69F0", 0x4C69F0, &recomp_gen::fn_sub_4C69F0_004c69f0, &recomp_gen::fn_sub_4C69F0_004c69f0__recomp},
    {"sub_4C6AC0", 0x4C6AC0, &recomp_gen::fn_sub_4C6AC0_004c6ac0, &recomp_gen::fn_sub_4C6AC0_004c6ac0__recomp},
    {"sub_4C6AF0", 0x4C6AF0, &recomp_gen::fn_sub_4C6AF0_004c6af0, &recomp_gen::fn_sub_4C6AF0_004c6af0__recomp},
    {"sub_4C6B20", 0x4C6B20, &recomp_gen::fn_sub_4C6B20_004c6b20, &recomp_gen::fn_sub_4C6B20_004c6b20__recomp},
    {"sub_4C6C20", 0x4C6C20, &recomp_gen::fn_sub_4C6C20_004c6c20, &recomp_gen::fn_sub_4C6C20_004c6c20__recomp},
    {"sub_4C6CA0", 0x4C6CA0, &recomp_gen::fn_sub_4C6CA0_004c6ca0, &recomp_gen::fn_sub_4C6CA0_004c6ca0__recomp},
    {"sub_4C6CE0", 0x4C6CE0, &recomp_gen::fn_sub_4C6CE0_004c6ce0, &recomp_gen::fn_sub_4C6CE0_004c6ce0__recomp},
    {"sub_4C7A50", 0x4C7A50, &recomp_gen::fn_sub_4C7A50_004c7a50, &recomp_gen::fn_sub_4C7A50_004c7a50__recomp},
    {"sub_4C89A0", 0x4C89A0, &recomp_gen::fn_sub_4C89A0_004c89a0, &recomp_gen::fn_sub_4C89A0_004c89a0__recomp},
    {"sub_4C8A60", 0x4C8A60, &recomp_gen::fn_sub_4C8A60_004c8a60, &recomp_gen::fn_sub_4C8A60_004c8a60__recomp},
    {"sub_4C9270", 0x4C9270, &recomp_gen::fn_sub_4C9270_004c9270, &recomp_gen::fn_sub_4C9270_004c9270__recomp},
    {"sub_4C9400", 0x4C9400, &recomp_gen::fn_sub_4C9400_004c9400, &recomp_gen::fn_sub_4C9400_004c9400__recomp},
    {"sub_4C9940", 0x4C9940, &recomp_gen::fn_sub_4C9940_004c9940, &recomp_gen::fn_sub_4C9940_004c9940__recomp},
    {"sub_4C9AD0", 0x4C9AD0, &recomp_gen::fn_sub_4C9AD0_004c9ad0, &recomp_gen::fn_sub_4C9AD0_004c9ad0__recomp},
    {"CameraEndUpdate", 0x4C9B40, &recomp_gen::fn_CameraEndUpdate_004c9b40, &recomp_gen::fn_CameraEndUpdate_004c9b40__recomp},
    {"CameraBeginUpdate", 0x4C9BA0, &recomp_gen::fn_CameraBeginUpdate_004c9ba0, &recomp_gen::fn_CameraBeginUpdate_004c9ba0__recomp},
    {"sub_4C9C00", 0x4C9C00, &recomp_gen::fn_sub_4C9C00_004c9c00, &recomp_gen::fn_sub_4C9C00_004c9c00__recomp},
    {"sub_4C9C70", 0x4C9C70, &recomp_gen::fn_sub_4C9C70_004c9c70, &recomp_gen::fn_sub_4C9C70_004c9c70__recomp},
    {"sub_4C9D20", 0x4C9D20, &recomp_gen::fn_sub_4C9D20_004c9d20, &recomp_gen::fn_sub_4C9D20_004c9d20__recomp},
    {"sub_4C9DB0", 0x4C9DB0, &recomp_gen::fn_sub_4C9DB0_004c9db0, &recomp_gen::fn_sub_4C9DB0_004c9db0__recomp},
    {"sub_4C9F00", 0x4C9F00, &recomp_gen::fn_sub_4C9F00_004c9f00, &recomp_gen::fn_sub_4C9F00_004c9f00__recomp},
    {"sub_4C9F90", 0x4C9F90, &recomp_gen::fn_sub_4C9F90_004c9f90, &recomp_gen::fn_sub_4C9F90_004c9f90__recomp},
    {"sub_4CA000", 0x4CA000, &recomp_gen::fn_sub_4CA000_004ca000, &recomp_gen::fn_sub_4CA000_004ca000__recomp},
    {"sub_4CA090", 0x4CA090, &recomp_gen::fn_sub_4CA090_004ca090, &recomp_gen::fn_sub_4CA090_004ca090__recomp},
    {"sub_4CBC70", 0x4CBC70, &recomp_gen::fn_sub_4CBC70_004cbc70, &recomp_gen::fn_sub_4CBC70_004cbc70__recomp},
    {"sub_4CBE00", 0x4CBE00, &recomp_gen::fn_sub_4CBE00_004cbe00, &recomp_gen::fn_sub_4CBE00_004cbe00__recomp},
    {"sub_4CBEB0", 0x4CBEB0, &recomp_gen::fn_sub_4CBEB0_004cbeb0, &recomp_gen::fn_sub_4CBEB0_004cbeb0__recomp},
    {"sub_4CC050", 0x4CC050, &recomp_gen::fn_sub_4CC050_004cc050, &recomp_gen::fn_sub_4CC050_004cc050__recomp},
    {"sub_4CC6B0", 0x4CC6B0, &recomp_gen::fn_sub_4CC6B0_004cc6b0, &recomp_gen::fn_sub_4CC6B0_004cc6b0__recomp},
    {"sub_4CD750", 0x4CD750, &recomp_gen::fn_sub_4CD750_004cd750, &recomp_gen::fn_sub_4CD750_004cd750__recomp},
    {"sub_4D18C0", 0x4D18C0, &recomp_gen::fn_sub_4D18C0_004d18c0, &recomp_gen::fn_sub_4D18C0_004d18c0__recomp},
    {"sub_4F23C0", 0x4F23C0, &recomp_gen::fn_sub_4F23C0_004f23c0, &recomp_gen::fn_sub_4F23C0_004f23c0__recomp},
    {"sub_4F2430", 0x4F2430, &recomp_gen::fn_sub_4F2430_004f2430, &recomp_gen::fn_sub_4F2430_004f2430__recomp},
    {"sub_4F28E0", 0x4F28E0, &recomp_gen::fn_sub_4F28E0_004f28e0, &recomp_gen::fn_sub_4F28E0_004f28e0__recomp},
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
bool in_ram(u32 va, u32 len = 4) { return va != 0 && va < EEMemory::kMainRamSize - len; }

const Case& by_name(const char* n) {
    for (const Case& c : kCases)
        if (std::strcmp(c.name, n) == 0) return c;
    std::fprintf(stderr, "render_rw5 test: no case %s\n", n);
    std::abort();
}

// The RW globals the bodies read (render_rw5.h): the engine instance and the module / extension offset words.
constexpr u32 kEngine = 0x960070u;
constexpr u32 kGpCamera = 0x7CE920u, kGpLight = 0x7CE830u, kGpClump = 0x7CE820u, kGpMaterial = 0x7CE840u;
constexpr u32 kGpFrame = 0x7CE930u, kGpTexture = 0x7CE950u, kGpCamWorld = 0x7CE868u, kGpAtomWorld = 0x7CE86Cu;
constexpr u32 kGpLightWorld = 0x7CE874u, kGpWorldTies = 0x7CE878u, kGpCollGeo = 0x7CE728u, kGpCollSector = 0x7CE72Cu;
constexpr u32 kRegAtomic = 0x77DCE0u, kRegClump = 0x77DD00u, kRegGeometry = 0x77DD20u, kRegLight = 0x77DD40u,
              kRegMaterial = 0x77DD60u, kRegSector = 0x77DDB0u, kRegWorld = 0x77DDD0u, kRegCamera = 0x77E5E0u;
// Test data: free in the ELF's image and in every replay snapshot (below the stand-in heap 0x1C00000).
constexpr u32 kData = 0x01BC0000u;
constexpr u32 kDataSize = 0x00040000u;
// A function this build does not emit, served by a recorder returning 1: the callback of the walks.
constexpr u32 kCallback = 0x10A860u;

// The live entries of a free list (the used bits of each block, MSB first).
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

// The BSP of a world: its sectors (type < 0) and plane nodes, from the root (+28).
void bsp_walk(Machine& m, u32 node, std::vector<u32>& sectors, std::vector<u32>& planes, int depth = 0) {
    if (!in_ram(node, 136) || depth > 64) return;
    if (static_cast<s32>(ld(m, node)) < 0) {
        sectors.push_back(node);
        return;
    }
    planes.push_back(node);
    bsp_walk(m, ld(m, node + 8), sectors, planes, depth + 1);
    bsp_walk(m, ld(m, node + 12), sectors, planes, depth + 1);
}

// What a snapshot holds that the bodies take as arguments.
struct Live {
    std::vector<u32> cameras, lights, atomics, clumps, materials, frames, textures, geometries, sectors, planes, plugin_ids;
    u32 world = 0;
};
Live scan(Machine& m) {
    Live l;
    l.cameras = live_entries(m, ld(m, kEngine + ld(m, kGpCamera)));
    l.lights = live_entries(m, ld(m, kEngine + ld(m, kGpLight)));
    l.atomics = live_entries(m, ld(m, kEngine + ld(m, kGpClump)));
    l.clumps = live_entries(m, ld(m, kEngine + ld(m, kGpClump) + 4));
    l.materials = live_entries(m, ld(m, kEngine + ld(m, kGpMaterial)));
    l.frames = live_entries(m, ld(m, kEngine + ld(m, kGpFrame)));
    l.textures = live_entries(m, ld(m, kEngine + ld(m, kGpTexture) + 8));
    for (u32 a : l.atomics) {
        const u32 g = ld(m, a + 24);
        if (in_ram(g, 96) && std::find(l.geometries.begin(), l.geometries.end(), g) == l.geometries.end()) l.geometries.push_back(g);
    }
    for (u32 c : l.cameras)
        if (in_ram(ld(m, c + ld(m, kGpCamWorld) + 12))) l.world = ld(m, c + ld(m, kGpCamWorld) + 12);
    if (l.world) bsp_walk(m, ld(m, l.world + 28), l.sectors, l.planes);
    for (u32 reg : {kRegAtomic, kRegClump, kRegGeometry, kRegLight, kRegMaterial, kRegSector, kRegWorld, kRegCamera})
        for (u32 e = ld(m, reg + 16), n = 0; in_ram(e) && n < 64; e = ld(m, e + 48), ++n) l.plugin_ids.push_back(ld(m, e + 8));
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
    return p;
}

// The world: the standard stand-ins plus a recorder for the walks' callback.
WorldSetup rw_world() {
    return [](StandInWorld& w) {
        install_standard(w);
        w.si.install_recorder(kCallback, "callback (returns 1)", 1);
        w.si.install_recorder(0x4CA500u, "engine started", 1);
        w.si.install(0x490810u, "atomic frame sync", [](EEContext&, StandIns&, StandInCall& c) { c.v0 = c.args[0]; });
        w.si.install(0x4906D0u, "clump destroy", [](EEContext&, StandIns&, StandInCall& c) { c.v0 = c.args[0]; });
        w.si.install(0x4906E0u, "atomic destroy", [](EEContext&, StandIns&, StandInCall& c) { c.v0 = c.args[0]; });
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

// A collision block in guest memory (render_rw5.h rw5::coll), `tris` / `splits` counts, a map when `map`.
u32 put_coll(Machine& m, std::mt19937& rng, u32 at, u32 tris, u32 splits, bool map) {
    std::memset(m.at(at), 0, 40 + 16 * splits + 2 * tris + 32);
    st(m, at + 0, map ? 1u : 0u);
    for (int i = 0; i < 6; ++i) stf(m, at + 4 + 4 * i, frand(rng, -100, 100));
    st16(m, at + 28, static_cast<u16>(tris));
    st16(m, at + 30, static_cast<u16>(splits));
    const u32 sp = (at + 40 + 15) & ~15u;
    st(m, at + 32, splits ? sp : 0u);
    for (u32 i = 0; i < 4 * splits; ++i) st(m, sp + 4 * i, rng());
    const u32 mp = (sp + 16 * splits + 1) & ~1u;
    st(m, at + 36, map ? mp : 0u);
    for (u32 i = 0; map && i < tris; ++i) st16(m, mp + 2 * i, static_cast<u16>(rng() % tris));
    return at;
}

// A world with a real BSP in the test area: the live world's record copied, its box replaced by `sup` / `inf`, a tree of
// 2^depth - 1 planes cutting the box on rotating axes at random fractions, and 2^depth sectors (copies of a live sector,
// empty tie lists, their boxes = their cells, as sub_499D30 computes them). Plane nodes: +0 the axis offset, +4 the plane,
// +8 / +12 the children, +16 / +20 the left / right bound (both the plane here). Returns the world; `sectors` gets the
// sectors.
u32 make_bsp_world(Machine& m, std::mt19937& rng, const Live& live, const float sup[3], const float inf[3], int depth,
                   std::vector<u32>& sectors) {
    const u32 world = kData + 0x10000, sec0 = kData + 0x11000, plane0 = kData + 0x18000;
    std::memcpy(m.at(world), m.at(live.world), 0x200);
    for (int j = 0; j < 3; ++j) stf(m, world + 80 + 4 * j, sup[j]), stf(m, world + 92 + 4 * j, inf[j]);
    sectors.clear();
    u32 next_sector = sec0, next_plane = plane0;
    std::function<u32(const float*, const float*, int, int)> build = [&](const float* hi, const float* lo, int d, int axis) -> u32 {
        if (d == 0) {
            const u32 s = next_sector;
            next_sector += 0x100;
            std::memcpy(m.at(s), m.at(live.sectors[0]), 0x100);
            st(m, s, 0xFFFFFFFFu);
            for (u32 h : {56u, 64u}) st(m, s + h, s + h), st(m, s + h + 4, s + h);
            for (int j = 0; j < 3; ++j) stf(m, s + 72 + 4 * j, hi[j]), stf(m, s + 84 + 4 * j, lo[j]);
            sectors.push_back(s);
            return s;
        }
        const u32 p = next_plane;
        next_plane += 0x20;
        const float v = lo[axis] + (hi[axis] - lo[axis]) * frand(rng, 0.25f, 0.75f);
        st(m, p, 4u * static_cast<u32>(axis));
        stf(m, p + 4, v), stf(m, p + 16, v), stf(m, p + 20, v);
        float lhi[3] = {hi[0], hi[1], hi[2]}, rlo[3] = {lo[0], lo[1], lo[2]};
        lhi[axis] = v, rlo[axis] = v;
        st(m, p + 8, build(lhi, lo, d - 1, (axis + 1) % 3));
        st(m, p + 12, build(hi, rlo, d - 1, (axis + 1) % 3));
        return p;
    };
    st(m, world + 28, build(sup, inf, depth, static_cast<int>(rng() % 3)));
    return world;
}

// The host's view of the camera's frustum after the sync (render_rw5.h rw5::camera / frustplane).
struct Plane {
    float n[3], d;
    u8 closest[3];
};
Plane read_plane(Machine& m, u32 cam, int k) {
    Plane p;
    const u32 a = cam + 148 + 20 * k;
    for (int i = 0; i < 3; ++i) p.n[i] = ldf(m, a + 4 * i), p.closest[i] = m.at(a + 16)[i];
    p.d = ldf(m, a + 12);
    return p;
}

}  // namespace

// =====================================================================================================================
// The snapshot sweep: every function on the live RenderWare state of the replay snapshots
// =====================================================================================================================
// Each pair starts from the snapshot image (the cameras, lights, atomics, clumps, materials, frames, geometries, the world
// and its BSP sectors live), with arguments of the kinds the function takes; the heap and the free-list entry points are
// the stand-ins'.
TEST_CASE("game(render_rw5): every body equals its recompiled body on the replay snapshots' live RenderWare state") {
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
        REQUIRE(!live.cameras.empty());
        REQUIRE(live.world != 0);
        MESSAGE(std::string(sn) << ": " << live.cameras.size() << " cameras, " << live.lights.size() << " lights, "
                   << live.atomics.size() << " atomics, " << live.clumps.size() << " clumps, " << live.materials.size()
                   << " materials, " << live.geometries.size() << " geometries, world " << hex64(live.world) << " with "
                   << live.sectors.size() << " sectors / " << live.planes.size() << " planes");
        const WorldSetup world = rw_world();
        std::mt19937 rng{0x52570000u + static_cast<u32>(snapshots)};
        for (const Case& c : kCases) {
            if (only && std::strcmp(only, c.name) != 0) continue;
            for (int k = 0; k < per; ++k) {
                std::memcpy(m.mem.main_ram(), image.data(), image.size());
                write_rw_slots(m);
                std::memset(m.at(kData), 0, kDataSize);
                const std::string n = c.name;
                const u32 scr = kData + 0x1000, scr2 = kData + 0x2000, scr3 = kData + 0x3000, buf = kData + 0x8000;
                auto cam = [&] { return pick(rng, live.cameras, scr); };
                auto lig = [&] { return pick(rng, live.lights, scr); };
                auto atm = [&] { return pick(rng, live.atomics, scr); };
                auto clp = [&] { return pick(rng, live.clumps, scr); };
                auto mat = [&] { return pick(rng, live.materials, scr); };
                auto geo = [&] { return pick(rng, live.geometries, scr); };
                auto sec = [&] { return pick(rng, live.sectors, scr); };
                auto frm = [&] { return pick(rng, live.frames, 0u); };
                auto vec = [&](u32 at, int count = 3, float r = 2.0f) {
                    for (int i = 0; i < count; ++i) stf(m, at + 4 * i, frand(rng, -r, r));
                    return at;
                };
                std::vector<u32> bsec;
                auto bspw = [&] {
                    float sup[3], inf[3];
                    for (int j = 0; j < 3; ++j) {
                        const float c0 = frand(rng, -500, 500), half = frand(rng, 50, 2000);
                        sup[j] = c0 + half, inf[j] = c0 - half;
                    }
                    return make_bsp_world(m, rng, live, sup, inf, 1 + static_cast<int>(rng() % 3), bsec);
                };
                auto pid = [&] { return chance(rng, 60) ? pick(rng, live.plugin_ids, 0x120u) : 0x7700u + rng() % 16; };
                Args a{rng(), rng(), rng(), rng()};
                HwCheck hw;
                // --- the argument kinds, by function ---
                // RpCollision
                if (n == "sub_45EC40") {
                    vec(scr, 6, 100);
                    a = {rng() % 64, rng() % 24, scr, rng() % 2};
                } else if (n == "sub_45EDC0") a = {chance(rng, 50) ? scr : 0u, 0, 0, 0};
                else if (n == "sub_45EDD0") a = {put_coll(m, rng, scr, rng() % 40, rng() % 16, chance(rng, 50)), 0, 0, 0};
                else if (n == "sub_45EE00") {
                    const u32 s = mem_stream(m, scr2, 2 + rng() % 2, 0, 0);
                    a = {put_coll(m, rng, scr, rng() % 40, rng() % 16, chance(rng, 50)), s, 0, 0};
                } else if (n == "sub_45EFE0") {
                    // a collision struct chunk: the 36-byte header record, the splits, the map
                    const u32 tris = rng() % 30, splits = rng() % 12, map = rng() % 2;
                    u32 p = put_chunk(m, buf, 1, 36 + 16 * splits + 2 * tris * map);
                    st(m, p, map), p += 4;
                    for (int i = 0; i < 6; ++i) stf(m, p, frand(rng, -50, 50)), p += 4;
                    st(m, p, tris), st(m, p + 4, splits), p += 8;
                    for (u32 i = 0; i < 4 * splits; ++i) st(m, p, rng()), p += 4;
                    for (u32 i = 0; map && i < tris; ++i) st16(m, p, static_cast<u16>(rng() % 30)), p += 2;
                    const u32 len = p - buf;
                    a = {mem_stream(m, scr2, 1, buf, chance(rng, 85) ? len : rng() % (len + 1)), 0, 0, 0};
                } else if (n == "sub_45F140") {
                    for (u32 i = 0; i < 0x400; i += 4) st(m, buf + i, chance(rng, 50) ? rng() % 8 : rng());
                    vec(scr3, 6, 100);
                    a = {mem_stream(m, scr2, 1, buf, 0x400), rng() % 16, rng() % 8, scr3};
                    hw.gpr_in = {{GPR_T0, scr}};
                } else if (n == "sub_45F490" || n == "sub_45F4C0" || n == "sub_45F7B0") a = {scr, 0, 0, 0};
                else if (n == "sub_45F4E0" || n == "sub_45F530" || n == "sub_45F540") {
                    if (chance(rng, 60)) st(m, scr + 16, put_coll(m, rng, scr2, rng() % 20, rng() % 8, chance(rng, 50)));
                    a = {scr, 16, 0, 0};
                } else if (n == "sub_45F600") {
                    // a version word; then (new) a collision chunk or (old) a count word and old-layout words
                    const bool fresh = chance(rng, 50);
                    st(m, buf, fresh ? 0x37002u : 0x34000u);
                    u32 p = buf + 4;
                    if (fresh) {
                        p = put_chunk(m, p, 44, 48);
                        p = put_chunk(m, p, 1, 36);
                        st(m, p, 0), p += 4;
                        for (int i = 0; i < 6; ++i) stf(m, p, frand(rng, -50, 50)), p += 4;
                        st(m, p, 0), st(m, p + 4, 0), p += 8;
                    } else {
                        st(m, p, rng() % 4), p += 4;
                        for (u32 i = 0; i < 64; ++i) st(m, p, rng() % 4), p += 4;
                    }
                    const u32 obj = chance(rng, 50) ? geo() : sec();
                    a = {mem_stream(m, scr2, 1, buf, p - buf), p - buf, obj, chance(rng, 50) ? ld(m, kGpCollGeo) : ld(m, kGpCollSector)};
                } else if (n == "sub_464280") a = {rng() % 24, 0, 0, 0};
                // RpAtomic / RpClump
                else if (n == "sub_4906F0" || n == "sub_4949C0") {
                    st(m, buf, rng()), st(m, buf + 4, rng());
                    a = {mem_stream(m, scr2, 1, buf, 8), chance(rng, 50) ? 8u : 4u, 0, 0};
                } else if (n == "sub_490770" || n == "sub_494A40")
                    a = {mem_stream(m, scr2, 2, 0, 0), 8, n == "sub_490770" ? atm() : mat(), 0};
                else if (n == "sub_4907E0" || n == "sub_49B180" || n == "sub_49B290" || n == "sub_49B2D0" || n == "sub_49B2E0" ||
                         n == "sub_49C230")
                    a = {atm(), 0, 0, 0};
                else if (n == "sub_494AB0" || n == "sub_494BE0") a = {mat(), 0, 0, 0};
                else if (n == "sub_490CA0" || n == "sub_490CC0" || n == "sub_4C89A0" ||
                         n == "sub_4C8A60" || n == "sub_4C9270" || n == "sub_4C9400" || n == "sub_4C9940" || n == "sub_4C9AD0" ||
                         n == "CameraEndUpdate" || n == "CameraBeginUpdate" || n == "sub_49AC90" || n == "sub_49ACD0" ||
                         n == "sub_49AD80" || n == "sub_49AE30" || n == "sub_4F28E0")
                    a = {cam(), 0, 0, 0};
                else if (n == "sub_490CD0" || n == "sub_490CF0" || n == "sub_490D00" || n == "sub_494490" || n == "sub_494760" ||
                         n == "sub_4944A0" || n == "sub_49B730" || n == "sub_49B7A0")
                    a = {lig(), 0, 0, 0};
                else if (n == "sub_49ADE0") a = {cam(), cam(), 0, 0};
                else if (n == "sub_49B760") a = {lig(), lig(), 0, 0};
                else if (n == "sub_491410" || n == "sub_4948B0" || n == "sub_494B70" || n == "sub_49ABF0" || n == "sub_4C9C00" ||
                         n == "sub_4959E0" || n == "sub_499210" || n == "sub_4CBC70")
                    a = {kEngine, 0, 0, 0};  // the module closes (the instance)
                else if (n == "sub_4914D0") a = {kEngine, ld(m, kGpClump), 0, 0};
                else if (n == "sub_494930") a = {kEngine, ld(m, kGpLight), 0, 0};
                else if (n == "sub_494AE0") a = {kEngine, ld(m, kGpMaterial), 0, 0};
                else if (n == "sub_49AAF0") a = {kEngine, ld(m, kGpWorldTies), 0, 0};
                else if (n == "sub_4C9C70") a = {kEngine, ld(m, kGpCamera), 0, 0};
                else if (n == "sub_495A30") a = {kEngine, 0x7F0u, 0, 0};
                else if (n == "sub_491760" || n == "sub_4917F0") a = {clp(), kCallback, rng(), 0};
                else if (n == "sub_491FF0") a = {clp(), atm(), 0, 0};
                else if (n == "sub_492020") a = {clp(), lig(), 0, 0};
                else if (n == "sub_492060") a = {clp(), cam(), 0, 0};
                else if (n == "sub_49B3C0" || n == "sub_49B430") a = {clp(), 0, 0, 0};
                // the plugin registries
                else if (n == "sub_492C30" || n == "sub_492C60" || n == "sub_493C50" || n == "sub_494520" || n == "sub_494DB0" ||
                         n == "sub_499250" || n == "sub_49A920" || n == "sub_4CA000") {
                    a = {4u * (rng() % 16), pid(), kCallback, kCallback};
                    hw.gpr_in = {{GPR_T0, chance(rng, 50) ? 0u : kCallback}};
                } else if (n == "sub_492C90" || n == "sub_493C80" || n == "sub_494550" || n == "sub_494DE0" || n == "sub_499280" ||
                           n == "sub_49A950")
                    a = {pid(), kCallback, kCallback, kCallback};
                else if (n == "sub_492CC0" || n == "sub_492CE0" || n == "sub_492D00" || n == "sub_494E10" || n == "sub_4992B0" ||
                         n == "sub_4992D0")
                    a = {pid(), kCallback, 0, 0};
                // RpGeometry, the material list
                else if (n == "sub_492E20") {
                    const u32 g = geo();
                    a = {in_ram(ld(m, g + 92)) ? ld(m, g + 92) : scr2, scr, 0, 0};
                } else if (n == "sub_492F80") {
                    // a small geometry: flags (normals / native), vertices, one or two morph targets or none
                    std::memset(m.at(scr), 0, 128);
                    st(m, scr + 8, (chance(rng, 50) ? 0x10u : 0u) | (chance(rng, 15) ? 0x1000000u : 0u));
                    st(m, scr + 20, rng() % 12);
                    st(m, scr + 24, rng() % 2);
                    a = {scr, 1 + rng() % 3, 0, 0};
                } else if (n == "sub_493210") a = {geo(), scr, rng() % 100, rng() % 100};
                else if (n == "sub_493230") {
                    std::memcpy(m.at(scr), m.at(geo()), 96);
                    st(m, scr + 32, 0), st(m, scr + 36, 0), st(m, scr + 40, 0);
                    a = {scr, scr2, chance(rng, 20) ? 0u : mat(), 0};
                } else if (n == "sub_493B40") a = {geo(), 0, 0, 0};
                else if (n == "sub_495300") a = {scr, 0, 0, 0};
                else if (n == "sub_495340" || n == "sub_495480") {
                    const u32 g = geo();
                    if (chance(rng, 50)) a = {g + 32, mat(), 0, 0};
                    else {
                        const u32 cnt = rng() % 22;
                        st(m, scr, cnt ? buf : 0u), st(m, scr + 4, cnt), st(m, scr + 8, cnt + rng() % 3);
                        for (u32 i = 0; i < cnt; ++i) st(m, buf + 4 * i, mat());
                        a = {scr, chance(rng, 50) && cnt ? ld(m, buf + 4 * (rng() % cnt)) : mat(), 0, 0};
                    }
                }
                // RpLight
                else if (n == "sub_4944B0") a = {lig(), vec(scr2, 4, 1.0f), 0, 0};
                else if (n == "sub_4947C0") a = {chance(rng, 50) ? 1u + rng() % 2 : 0x80u + rng() % 3, 0, 0, 0};
                // the mesh build
                else if (n == "sub_4959C0") a = {16 + rng() % 0x400, 0, 0, 0};
                else if (n == "sub_495B10") a = {rng() % 40, 0, 0, 0};
                else if (n == "sub_495C20") {
                    st(m, scr, 4), st(m, scr + 4, 0), st(m, scr + 8, chance(rng, 50) ? 0u : buf);
                    a = {scr, 0, 0, 0};
                } else if (n == "sub_495C80") {
                    for (int i = 0; i < 4; ++i) st(m, scr + 4 * i, chance(rng, 70) ? 0u : rng());
                    a = {scr, 0, 0, 0};
                }
                // world sectors
                else if (n == "sub_499400") {
                    const u32 s = sec(), ntri = ld16(m, s + 132);
                    st(m, scr, ntri + 4), st(m, scr + 4, 0), st(m, scr + 8, buf);
                    a = {live.world, scr, s, ld(m, live.world + 16) + 4u * ld16(m, s + 128)};
                } else if (n == "sub_499D30" || n == "sub_499FD0" || n == "sub_49A080") {
                    const u32 w = chance(rng, 60) ? bspw() : live.world;
                    if (n == "sub_49A080")
                        for (u32 s : w == live.world ? live.sectors : bsec)
                            if (chance(rng, 30)) st(m, s + 120, 0);
                    a = {w, 0, 0, 0};
                } else if (n == "sub_499E90") a = {rng(), rng(), 0, 0};
                else if (n == "sub_499F40") a = {rng() % 4, 0, 0, 0};
                else if (n == "sub_49A7C0") a = {live.world, kCallback, rng(), 0};
                // the world's object ties
                else if (n == "sub_49AEB0" || n == "sub_49AF20") {
                    // a tie linked in two two-element lists {head, tie}
                    const u32 t = scr, h1 = scr2, h2 = scr2 + 16;
                    st(m, t + 0, h1), st(m, t + 4, h1), st(m, h1, t), st(m, h1 + 4, t);
                    st(m, t + 12, h2), st(m, t + 16, h2), st(m, h2, t + 12), st(m, h2 + 4, t + 12);
                    st(m, t + 8, chance(rng, 80) ? atm() : 0u), st(m, t + 20, chance(rng, 80) ? sec() : 0u);
                    a = {t, 0, 0, 0};
                } else if (n == "sub_49AFA0") a = {chance(rng, 60) ? bspw() : live.world, atm(), 0, 0};
                else if (n == "sub_49B850" || n == "sub_49ACF0") {
                    // a camera synced first (its frustum), in the live world or in a world with a BSP around its frustum box
                    const u32 cm = cam();
                    wpair(m, by_name("sub_4C9AD0"), {cm, 0, 0, 0}, 905000u + static_cast<u32>(pairs), world);
                    u32 w = live.world;
                    if (chance(rng, 70)) {
                        float sup[3], inf[3];
                        for (int j = 0; j < 3; ++j) {
                            const float hi = ldf(m, cm + 268 + 4 * j), lo = ldf(m, cm + 280 + 4 * j), e = 0.5f * (hi - lo) + 1.0f;
                            sup[j] = hi + e * frand(rng, 0.0f, 1.0f), inf[j] = lo - e * frand(rng, 0.0f, 1.0f);
                        }
                        w = make_bsp_world(m, rng, live, sup, inf, 1 + static_cast<int>(rng() % 3), bsec);
                    }
                    st(m, cm + ld(m, kGpCamWorld) + 12, w);
                    a = {n == "sub_49B850" ? w : cm, cm, 0, 0};
                } else if (n == "sub_49B440") {
                    // a local light with a frame and a radius, in a world with a BSP (or the live world)
                    u32 l = lig();
                    for (u32 x : live.lights)
                        if (ld(m, x + 4) != 0 && chance(rng, 50)) l = x;
                    if (chance(rng, 80)) m.at(l)[1] = static_cast<u8>(0x80u | (rng() % 3));
                    stf(m, l + 20, frand(rng, 10, 1500));
                    st(m, l + ld(m, kGpLightWorld), chance(rng, 70) ? bspw() : live.world);
                    a = {l, 0, 0, 0};
                }
                else if (n == "sub_49BBC0" || n == "sub_49C1E0") a = {n == "sub_49BBC0" ? atm() : live.world, n == "sub_49BBC0" ? live.world : atm(), 0, 0};
                else if (n == "sub_49BBF0" || n == "sub_49C3D0") a = {n == "sub_49BBF0" ? lig() : live.world, n == "sub_49BBF0" ? live.world : lig(), 0, 0};
                else if (n == "sub_49BC20" || n == "sub_49C160") a = {n == "sub_49BC20" ? cam() : live.world, n == "sub_49BC20" ? live.world : cam(), 0, 0};
                else if (n == "sub_49C1B0") a = {live.world, cam(), 0, 0};
                else if (n == "sub_49C480") a = {live.world, lig(), 0, 0};
                else if (n == "sub_49C560" || n == "sub_49C5C0" || n == "sub_49C620" || n == "sub_4F23C0")
                    a = {chance(rng, 50) ? 0u : scr, 0, 0, 0};
                else if (n == "sub_4F2430") a = {chance(rng, 50) ? 0u : scr, rng() % 8, 0, 0};
                // RwV3d
                else if (n == "sub_4C69F0" || n == "sub_4C6B20") {
                    if (chance(rng, 15)) std::memset(m.at(scr2), 0, 12);
                    else vec(scr2, 3, 50.0f);
                    a = {scr, scr2, 0, 0};
                } else if (n == "sub_4C6AC0" || n == "sub_4C6AF0") a = {vec(scr2, 3, 50.0f), 0, 0, 0};
                else if (n == "sub_4C6C20" || n == "sub_4C6CA0") {
                    const u32 cnt = rng() % 8;
                    vec(scr2, 3 * static_cast<int>(cnt), 10.0f);
                    const u32 f = frm();
                    a = {scr, scr2, cnt, f ? f + 80 : scr3};
                } else if (n == "sub_4C7A50") {
                    const u32 cnt = 1 + rng() % 12;
                    vec(scr2, 3 * static_cast<int>(cnt), 100.0f);
                    a = {scr, scr2, cnt, 0};
                }
                // RwCamera
                else if (n == "sub_4C9D20" || n == "sub_4C9F90") a = {cam(), vec(scr2, 2, 1.0f), 0, 0};
                else if (n == "sub_4C9DB0") a = {cam(), 0, 0, 0};
                else if (n == "sub_4C9F00") a = {cam(), rng() % 4, 0, 0};
                else if (n == "sub_4D18C0") a = {chance(rng, 50) ? cam() : lig(), 0, 0, 0};
                // RwImage
                else if (n == "sub_4CBE00") a = {1 + rng() % 64, 1 + rng() % 64, pick(rng, std::vector<u32>{4, 8, 32}, 32u), 0};
                else if (n == "sub_4CBEB0" || n == "sub_4CC050") {
                    std::memset(m.at(scr), 0, 28);
                    st(m, scr, rng() % 2), st(m, scr + 20, chance(rng, 50) ? 0u : buf);
                    a = {scr, 0, 0, 0};
                } else if (n == "sub_4CD750") {
                    // an image chunk: struct chunk {width, height, depth, stride}, the pixels, the palette
                    const u32 w = 1 + rng() % 16, h = 1 + rng() % 16, d = pick(rng, std::vector<u32>{4, 8, 32}, 8u);
                    const u32 stride = (w * d + 7) / 8 + (chance(rng, 50) ? 4u : 0u);
                    u32 p = put_chunk(m, buf, 1, 16);
                    st(m, p, w), st(m, p + 4, h), st(m, p + 8, d), st(m, p + 12, stride), p += 16;
                    for (u32 i = 0; i < stride * h + (d < 9 ? (4u << d) : 0u); ++i) m.at(p)[0] = static_cast<u8>(rng()), ++p;
                    a = {mem_stream(m, scr2, 1, buf, p - buf), 0, 0, 0};
                }
                // (the rest: getters and trivial bodies on random words)
                if (std::getenv("P3FES_HG_TRACE")) std::fprintf(stderr, "%s %s pair %d a0=%08x a1=%08x\n", sn, c.name, k, static_cast<u32>(a[0]), static_cast<u32>(a[1]));
                const WPair p = wpair(m, c, a, 910000u + static_cast<u32>(pairs), world, hw);
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
// The camera sync on every live camera (perspective and parallel, climb_ref_17000 has both): each frustum plane is a unit
// normal, every corner lies inside all six planes, each plane passes through four corners, the closest-corner bytes
// follow the normal's signs, the frustum box is the corners' bounding box; the z scale / shift map the clip planes onto
// the device range narrowed by 1e-4 of itself.
TEST_CASE("game(render_rw5): the camera sync's frustum and z range agree with the host's geometry") {
    int cams = 0;
    for (const char* sn : {"climb_ref_17000", "b_5800", "dorm_replay_4900"}) {
        std::vector<u8> image;
        auto mp = snapshot_machine(sn, image);
        if (!mp) {
            MESSAGE("SKIP: snapshot " << sn << " not found");
            continue;
        }
        Machine& m = *mp;
        const Live live = scan(m);
        for (u32 c : live.cameras) {
            INFO(sn << " camera " << hex64(c));
            const WPair p = wpair(m, by_name("sub_4C9AD0"), {c, 0, 0, 0}, 920000u + static_cast<u32>(cams), rw_world());
            REQUIRE(!p.run.stopped);
            CHECK(p.v0() == c);
            ++cams;
            float corner[8][3];
            for (int i = 0; i < 8; ++i)
                for (int j = 0; j < 3; ++j) corner[i][j] = ldf(m, c + 292 + 12 * i + 4 * j);
            float scale = 0;
            for (int i = 0; i < 8; ++i)
                for (int j = 0; j < 3; ++j) scale = std::max(scale, std::fabs(corner[i][j]));
            const float eps = 1e-4f * std::max(1.0f, scale);
            for (int k = 0; k < 6; ++k) {
                const Plane pl = read_plane(m, c, k);
                const float len = std::sqrt(pl.n[0] * pl.n[0] + pl.n[1] * pl.n[1] + pl.n[2] * pl.n[2]);
                CHECK(std::fabs(len - 1.0f) < 1e-3f);
                int on = 0;
                for (int i = 0; i < 8; ++i) {
                    const float s = pl.n[0] * corner[i][0] + pl.n[1] * corner[i][1] + pl.n[2] * corner[i][2] - pl.d;
                    CHECK(s <= eps);
                    if (std::fabs(s) <= eps) ++on;
                }
                CHECK(on >= 4);
                for (int j = 0; j < 3; ++j) CHECK(pl.closest[j] == (std::signbit(pl.n[j]) ? 0 : 1));
            }
            for (int j = 0; j < 3; ++j) {
                float lo = corner[0][j], hi = corner[0][j];
                for (int i = 1; i < 8; ++i) lo = std::min(lo, corner[i][j]), hi = std::max(hi, corner[i][j]);
                CHECK(ldf(m, c + 268 + 4 * j) == hi);
                CHECK(ldf(m, c + 280 + 4 * j) == lo);
            }
            // the z range (sub_4C89A0)
            const WPair z = wpair(m, by_name("sub_4C89A0"), {c, 0, 0, 0}, 921000u + static_cast<u32>(cams), rw_world());
            CHECK(!z.run.stopped);
            const float nearp = ldf(m, c + 128), farp = ldf(m, c + 132), nz = ldf(m, 0x960088u), fz = ldf(m, 0x96008Cu);
            const bool parallel = ld(m, c + 20) == 2;
            const float lo = parallel ? nearp : 1.0f / nearp, hi = parallel ? farp : 1.0f / farp;
            const float margin = 1e-4f * (fz - nz), zs = ldf(m, c + 140), zt = ldf(m, c + 144);
            // (perspective: 1 / near - 1 / far is small, so the scale is large and the products cancel: the tolerance
            // follows the magnitudes of the terms)
            const float tol = 1e-5f * (std::fabs(zs * lo) + std::fabs(zs * hi) + std::fabs(zt)) + 1e-4f * std::max(1.0f, std::fabs(fz));
            CHECK(std::fabs(zs * lo + zt - (nz + margin)) < tol);
            CHECK(std::fabs(zs * hi + zt - (fz - margin)) < tol);
        }
    }
    MESSAGE("cameras synced: " << cams);
}

// The camera setters on a live camera: the stored values, the reciprocals of the view window, the projection check.
TEST_CASE("game(render_rw5): the camera setters store what they are given") {
    std::vector<u8> image;
    auto mp = snapshot_machine("b_5800", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot b_5800 not found");
        return;
    }
    Machine& m = *mp;
    const Live live = scan(m);
    REQUIRE(!live.cameras.empty());
    const u32 c = live.cameras[0], v = kData + 0x100;
    stf(m, v, 0.75f), stf(m, v + 4, 0.5f);
    wpair(m, by_name("sub_4C9F90"), {c, v, 0, 0}, 930000u, rw_world());
    CHECK(ldf(m, c + 104) == 0.75f);
    CHECK(ldf(m, c + 108) == 0.5f);
    CHECK(std::fabs(ldf(m, c + 112) - 1.0f / 0.75f) < 1e-6f);
    CHECK(ldf(m, c + 116) == 2.0f);
    stf(m, v, 0.25f), stf(m, v + 4, -0.125f);
    wpair(m, by_name("sub_4C9D20"), {c, v, 0, 0}, 930001u, rw_world());
    CHECK(ldf(m, c + 120) == 0.25f);
    CHECK(ldf(m, c + 124) == -0.125f);
    const WPair bad = wpair(m, by_name("sub_4C9F00"), {c, 3, 0, 0}, 930002u, rw_world());
    CHECK(bad.v0() == 0);
    CHECK(ld(m, c + 20) == 1);
    const WPair good = wpair(m, by_name("sub_4C9F00"), {c, 2, 0, 0}, 930003u, rw_world());
    CHECK(good.v0() == c);
    CHECK(ld(m, c + 20) == 2);
}

// The visible-sector list of each live camera, in its live world and in worlds with a BSP around its frustum box
// (make_bsp_world, 8 sectors): the host walks the same tree -- a plane's left side is entered when the frustum box's
// minimum on the plane's axis is below the plane, its right side when the maximum is above -- and keeps a reached sector
// unless a frustum plane has its box's closest corner outside (the walk's rule); the body's list must hold exactly the
// sectors the host keeps (sectors within a rounding margin of a plane are not judged).
TEST_CASE("game(render_rw5): the camera's visible-sector list equals the host's frustum walk") {
    int listed = 0, judged = 0;
    for (const char* sn : {"b_5800", "dorm_replay_4900", "climb_ref_17000"}) {
        std::vector<u8> image;
        auto mp = snapshot_machine(sn, image);
        if (!mp) continue;
        Machine& m = *mp;
        const Live live = scan(m);
        std::mt19937 rng{0x5EC7u};
        for (u32 c : live.cameras) {
            for (int t = 0; t < 9; ++t) {
                std::memcpy(m.mem.main_ram(), image.data(), image.size());
                write_rw_slots(m);
                const u32 ext = c + ld(m, kGpCamWorld);
                wpair(m, by_name("sub_4C9AD0"), {c, 0, 0, 0}, 940000u + static_cast<u32>(t), rw_world());
                std::vector<u32> sectors = live.sectors;
                u32 w = live.world;
                if (t > 0) {
                    float sup[3], inf[3];
                    for (int j = 0; j < 3; ++j) {
                        const float hi = ldf(m, c + 268 + 4 * j), lo = ldf(m, c + 280 + 4 * j), e = hi - lo + 1.0f;
                        sup[j] = hi + e * frand(rng, 0.0f, 1.0f), inf[j] = lo - e * frand(rng, 0.0f, 1.0f);
                    }
                    w = make_bsp_world(m, rng, live, sup, inf, 3, sectors);
                }
                st(m, ext + 12, w);
                const WPair p = wpair(m, by_name("sub_49B850"), {w, c, 0, 0}, 941000u + static_cast<u32>(t), rw_world());
                INFO(sn << " camera " << hex64(c) << " world " << t);
                REQUIRE(!p.run.stopped);
                const u32 count = ld(m, ext + 8), arr = ld(m, ext);
                std::vector<u32> got;
                for (u32 i = 0; i < count; ++i) got.push_back(ld(m, arr + 4 * i));
                // the host's walk
                float fsup[3], finf[3];
                for (int j = 0; j < 3; ++j) fsup[j] = ldf(m, c + 268 + 4 * j), finf[j] = ldf(m, c + 280 + 4 * j);
                std::vector<u32> reached;
                std::function<void(u32, int)> walk = [&](u32 node, int d) {
                    if (d > 32) return;
                    if (static_cast<s32>(ld(m, node)) < 0) {
                        reached.push_back(node);
                        return;
                    }
                    const u32 ax = ld(m, node) / 4;
                    if (finf[ax] < ldf(m, node + 16)) walk(ld(m, node + 8), d + 1);
                    if (fsup[ax] > ldf(m, node + 20)) walk(ld(m, node + 12), d + 1);
                };
                walk(ld(m, w + 28), 0);
                for (u32 s : sectors) {
                    const bool in_list = std::find(got.begin(), got.end(), s) != got.end();
                    const bool was_reached = std::find(reached.begin(), reached.end(), s) != reached.end();
                    float worst = -1e30f, scale = 1.0f;
                    for (int k = 0; k < 6; ++k) {
                        const Plane pl = read_plane(m, c, k);
                        float dot = 0;
                        for (int j = 0; j < 3; ++j) {
                            const float x = ldf(m, s + 72 + 12 * pl.closest[j] + 4 * j);
                            dot += pl.n[j] * x;
                            scale = std::max(scale, std::fabs(x));
                        }
                        worst = std::max(worst, dot - pl.d);
                    }
                    const float tol = 1e-4f * std::max(scale, 1.0f);
                    if (!was_reached || worst > tol) {
                        CHECK(!in_list);
                        ++judged;
                    } else if (worst < -tol) {
                        CHECK(in_list);
                        ++judged;
                    }
                }
                listed += static_cast<int>(count);
            }
        }
    }
    MESSAGE("sectors listed: " << listed << ", judged against the host: " << judged);
}

// The sector boxes from the BSP: sub_499D30 gives each sector its cell (the world's box cut by the planes on the way
// down) -- on the live worlds and on worlds with a 3-level BSP whose sector boxes were scrambled first; the host walks
// the same tree.
TEST_CASE("game(render_rw5): every sector's box is its BSP cell (host walk)") {
    int checked = 0;
    for (const char* sn : {"b_5800", "dorm_replay_4900", "climb_ref_17000"}) {
        std::vector<u8> image;
        auto mp = snapshot_machine(sn, image);
        if (!mp) continue;
        Machine& m = *mp;
        const Live live = scan(m);
        std::mt19937 rng{0xB5Bu};
        for (int t = 0; t < 6; ++t) {
            u32 w = live.world;
            if (t > 0) {
                std::vector<u32> sectors;
                float sup[3], inf[3];
                for (int j = 0; j < 3; ++j) {
                    const float c0 = frand(rng, -300, 300), half = frand(rng, 10, 900);
                    sup[j] = c0 + half, inf[j] = c0 - half;
                }
                w = make_bsp_world(m, rng, live, sup, inf, 1 + t % 3, sectors);
                for (u32 s : sectors)
                    for (int j = 0; j < 6; ++j) stf(m, s + 72 + 4 * j, frand(rng, -1e4f, 1e4f));
            }
            const WPair p = wpair(m, by_name("sub_499D30"), {w, 0, 0, 0}, 950000u + static_cast<u32>(t), rw_world());
            REQUIRE(!p.run.stopped);
            struct Cell {
                u32 node;
                float sup[3], inf[3];
            };
            std::vector<Cell> stack;
            Cell root{ld(m, w + 28), {}, {}};
            for (int j = 0; j < 3; ++j) root.sup[j] = ldf(m, w + 80 + 4 * j), root.inf[j] = ldf(m, w + 92 + 4 * j);
            stack.push_back(root);
            while (!stack.empty()) {
                Cell cl = stack.back();
                stack.pop_back();
                if (static_cast<s32>(ld(m, cl.node)) < 0) {
                    for (int j = 0; j < 3; ++j) {
                        CHECK(ldf(m, cl.node + 72 + 4 * j) == cl.sup[j]);
                        CHECK(ldf(m, cl.node + 84 + 4 * j) == cl.inf[j]);
                    }
                    ++checked;
                    continue;
                }
                const u32 axis = ld(m, cl.node) / 4;
                Cell left = cl, right = cl;
                left.node = ld(m, cl.node + 8);
                right.node = ld(m, cl.node + 12);
                left.sup[axis] = ldf(m, cl.node + 16);
                right.inf[axis] = ldf(m, cl.node + 20);
                stack.push_back(right);
                stack.push_back(left);
            }
        }
    }
    MESSAGE("sector boxes checked: " << checked);
}

// Lights: create gives the documented record; the colour setter's grey flag is (r == g == b); add / remove keep the
// world's light lists consistent.
TEST_CASE("game(render_rw5): light create, colour and the world's light lists") {
    std::vector<u8> image;
    auto mp = snapshot_machine("dorm_replay_4900", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot dorm_replay_4900 not found");
        return;
    }
    Machine& m = *mp;
    const Live live = scan(m);
    REQUIRE(!live.lights.empty());
    const WPair cr = wpair(m, by_name("sub_4947C0"), {0x81, 0, 0, 0}, 960000u, rw_world());
    const u32 l = cr.v0();
    REQUIRE(in_ram(l, 64));
    CHECK(m.at(l)[0] == 3);
    CHECK(m.at(l)[1] == 0x81);
    CHECK(m.at(l)[2] == 3);
    CHECK(m.at(l)[3] == 1);
    CHECK(ld(m, l + 4) == 0);
    // the sync: the world plugin's constructor (sub_49B730) saved the light's own (sub_4944A0) and installed sub_49B440
    CHECK(ld(m, l + 16) == 0x49B440u);
    CHECK(ld(m, l + ld(m, kGpLightWorld) + 4) == 0x4944A0u);
    for (int i = 0; i < 4; ++i) CHECK(ldf(m, l + 24 + 4 * i) == 1.0f);
    CHECK(ld(m, l + 44) == l + 44);
    CHECK(ld16(m, l + 60) == static_cast<u16>(ld16(m, 0x96007Au) - 1));
    const u32 col = kData + 0x100;
    const float cols[][4] = {{0.5f, 0.5f, 0.5f, 1}, {0.5f, 0.25f, 0.5f, 1}, {1, 1, 0.75f, 0.5f}, {0.2f, 0.2f, 0.2f, 0}};
    int k = 0;
    for (const auto& cc : cols) {
        for (int i = 0; i < 4; ++i) stf(m, col + 4 * i, cc[i]);
        const u32 li = live.lights[k % live.lights.size()];
        m.at(li)[3] = 0;
        wpair(m, by_name("sub_4944B0"), {li, col, 0, 0}, 960010u + static_cast<u32>(k++), rw_world());
        for (int i = 0; i < 4; ++i) CHECK(ldf(m, li + 24 + 4 * i) == cc[i]);
        CHECK(m.at(li)[3] == ((cc[0] == cc[1] && cc[0] == cc[2]) ? 1 : 0));
    }
    // remove a light from the world and add it back: it is in exactly one of the world's two lists afterwards
    for (u32 li : live.lights) {
        auto in_list = [&](u32 head) {
            int hits = 0;
            for (u32 e = ld(m, head), n = 0; e != head && in_ram(e) && n < 256; e = ld(m, e), ++n) hits += (e == li + 52) ? 1 : 0;
            return hits;
        };
        const u32 w = live.world;
        if (in_list(w + 52) + in_list(w + 60) != 1) continue;
        wpair(m, by_name("sub_49C480"), {w, li, 0, 0}, 960100u + li % 997, rw_world());
        CHECK(in_list(w + 52) + in_list(w + 60) == 0);
        CHECK(ld(m, li + ld(m, kGpLightWorld)) == 0);
        wpair(m, by_name("sub_49C3D0"), {w, li, 0, 0}, 960200u + li % 997, rw_world());
        CHECK(in_list(m.at(li)[1] < 0x80 ? w + 60 : w + 52) == 1);
        CHECK(ld(m, li + ld(m, kGpLightWorld)) == w);
    }
}

// Vectors and boxes against the host's float arithmetic.
TEST_CASE("game(render_rw5): vector normalize / length and the bounding box against the host") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    write_rw_slots(*m);
    std::mt19937 rng{777};
    const u32 src = kData + 0x100, dst = kData + 0x200, box = kData + 0x300, pts = kData + 0x400;
    for (int t = 0; t < 24; ++t) {
        float v[3];
        for (float& x : v) x = frand(rng, -40, 40);
        for (int i = 0; i < 3; ++i) stf(*m, src + 4 * i, v[i]);
        const float len = std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
        const WPair n = wpair(*m, by_name("sub_4C69F0"), {dst, src, 0, 0}, 970000u + t, rw_world());
        CHECK(std::fabs(n.f0() - len) < 1e-4f * len);
        for (int i = 0; i < 3; ++i) CHECK(std::fabs(ldf(*m, dst + 4 * i) - v[i] / len) < 1e-5f);
        const WPair l = wpair(*m, by_name("sub_4C6AC0"), {src, 0, 0, 0}, 970100u + t, rw_world());
        CHECK(std::fabs(l.f0() - len) < 1e-4f * len);
        const WPair l2 = wpair(*m, by_name("sub_4C6AF0"), {src, 0, 0, 0}, 970200u + t, rw_world());
        CHECK(std::fabs(l2.f0() - std::sqrt(v[0] * v[0] + v[1] * v[1])) < 1e-4f * len);
        const u32 cnt = 1 + rng() % 16;
        float lo[3] = {1e30f, 1e30f, 1e30f}, hi[3] = {-1e30f, -1e30f, -1e30f};
        for (u32 i = 0; i < cnt; ++i)
            for (int j = 0; j < 3; ++j) {
                const float x = frand(rng, -100, 100);
                stf(*m, pts + 12 * i + 4 * j, x);
                lo[j] = std::min(lo[j], x), hi[j] = std::max(hi[j], x);
            }
        wpair(*m, by_name("sub_4C7A50"), {box, pts, cnt, 0}, 970300u + t, rw_world());
        for (int j = 0; j < 3; ++j) CHECK(ldf(*m, box + 4 * j) == hi[j]);
        for (int j = 0; j < 3; ++j) CHECK(ldf(*m, box + 12 + 4 * j) == lo[j]);
    }
    // a zero vector: error 25 and a zero result
    std::memset(m->at(src), 0, 12);
    const WPair z = wpair(*m, by_name("sub_4C69F0"), {dst, src, 0, 0}, 970900u, rw_world());
    CHECK(z.f0() == 0.0f);
    for (int i = 0; i < 3; ++i) CHECK(ldf(*m, dst + 4 * i) == 0.0f);
}

// The collision block: write (sub_45EE00) then read (sub_45EFE0) gives the same header, splits and triangle map.
TEST_CASE("game(render_rw5): a collision block survives the stream write / read round trip") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    write_rw_slots(*m);
    std::mt19937 rng{4242};
    for (int t = 0; t < 12; ++t) {
        const u32 blk = kData + 0x100, srec = kData + 0x80;
        const u32 tris = rng() % 40, splits = rng() % 12;
        const bool map = rng() % 2;
        put_coll(*m, rng, blk, tris, splits, map);
        // write into a stream that already has a buffer (the stand-in heap is not involved)
        const u32 sbuf = kData + 0x4000;
        mem_stream(*m, srec, 2, 0, 0);
        st(*m, srec + 20, sbuf), st(*m, srec + 16, 0x2000), st(*m, srec + 12, 0);
        const WPair w = wpair(*m, by_name("sub_45EE00"), {blk, srec, 0, 0}, 980000u + t, rw_world());
        REQUIRE(w.v0() == blk);
        const u32 written = ld(*m, srec + 12);
        CHECK(written == 12 + 12 + 36 + 16 * splits + (map ? 2 * tris : 0u));
        CHECK(ld(*m, sbuf) == 44u);
        // read it back: skip the collision chunk header (the reader finds the struct chunk)
        const u32 rrec = kData + 0x40;
        mem_stream(*m, rrec, 1, sbuf + 12, written - 12);
        const WPair r = wpair(*m, by_name("sub_45EFE0"), {rrec, 0, 0, 0}, 981000u + t, rw_world());
        const u32 nb = r.v0();
        REQUIRE(in_ram(nb, 64));
        CHECK(ld(*m, nb) == ld(*m, blk));
        for (int i = 0; i < 6; ++i) CHECK(ld(*m, nb + 4 + 4 * i) == ld(*m, blk + 4 + 4 * i));
        CHECK(ld16(*m, nb + 28) == tris);
        CHECK(ld16(*m, nb + 30) == splits);
        if (splits) CHECK(std::memcmp(m->at(ld(*m, nb + 32)), m->at(ld(*m, blk + 32)), 16 * splits) == 0);
        if (map && tris) CHECK(std::memcmp(m->at(ld(*m, nb + 36)), m->at(ld(*m, blk + 36)), 2 * tris) == 0);
    }
}

// The material list and material create: indices, references, growth by 20, the documented defaults.
TEST_CASE("game(render_rw5): material create and the material list") {
    std::vector<u8> image;
    auto mp = snapshot_machine("b_5800", image);
    if (!mp) {
        MESSAGE("SKIP: snapshot b_5800 not found");
        return;
    }
    Machine& m = *mp;
    const Live live = scan(m);
    REQUIRE(live.materials.size() > 24);
    const WPair cr = wpair(m, by_name("sub_494BE0"), {0, 0, 0, 0}, 990000u, rw_world());
    const u32 mt = cr.v0();
    REQUIRE(in_ram(mt, 32));
    CHECK(ld(m, mt) == 0);
    CHECK(ld(m, mt + 4) == 0xFFFFFFFFu);
    CHECK(ld(m, mt + 8) == 0);
    for (int i = 0; i < 3; ++i) CHECK(ld(m, mt + 12 + 4 * i) == ld(m, 0x77DD78u + 4 * i));
    CHECK(ld16(m, mt + 24) == 1);
    // a list: append 24 materials (one growth past 20), find each, references counted
    const u32 list = kData + 0x100;
    wpair(m, by_name("sub_495300"), {list, 0, 0, 0}, 990001u, rw_world());
    std::vector<u16> refs;
    for (u32 i = 0; i < 24; ++i) refs.push_back(ld16(m, live.materials[i] + 24));
    for (u32 i = 0; i < 24; ++i) {
        // (the list's array lives on the stand-in heap of each pair: keep it across pairs by copying the world's heap)
        const WPair a = wpair(m, by_name("sub_495340"), {list, live.materials[i], 0, 0}, 990100u + i, [&](StandInWorld& w) {
            install_standard(w);
            if (ld(m, list)) w.heap.reserve(ld(m, list), 4 * ld(m, list + 8));
        });
        CHECK(a.v0() == i);
        CHECK(ld(m, list + 4) == i + 1);
        CHECK(ld(m, list + 8) == (i < 20 ? 20u : 40u));
        CHECK(ld16(m, live.materials[i] + 24) == static_cast<u16>(refs[i] + 1));
    }
    for (u32 i = 0; i < 24; ++i) {
        const WPair f = wpair(m, by_name("sub_495480"), {list, live.materials[i], 0, 0}, 990200u + i, rw_world());
        CHECK(f.v0() == i);
    }
    const WPair miss = wpair(m, by_name("sub_495480"), {list, live.materials[30], 0, 0}, 990300u, rw_world());
    CHECK(miss.v0() == 0xFFFFFFFFu);
}

// Every body against its recompiled body on random worlds (the p3fes_handgen sweep), each function from a fresh ELF
// image (the module opens / closes of earlier functions write the gp words the later ones read).
TEST_CASE("game(render_rw5): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const std::vector<u8> elf_image(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
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

TEST_CASE("game(render_rw5): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
