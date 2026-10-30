// Pair tests of slice fcl (game/src/facility/fcl_*.cpp): every hand body against its recompiled body.
//   1. Random worlds (tests/game/handgen_pairs.h): all 136 functions, the whole register file and cycles at every check
//      point and at the return / stop, all 32 MiB of RAM, the scratchpad, the BIOS window, the bus log.
//   2. nmlist: objects created on the stand-in heap (layout of nm_message.h), node removal from every position with
//      and without the cursor on it, clearing; null arguments.
//   3. MsgAssist on the snapshots' live work (extracted/_ours: dorm, battle, fusion, shop, climb): the masks, the owner,
//      requests appended / found / counted / purged, the twelve slots started / queued / stopped and out of range, and a
//      fresh "MsgAssist" task created on the stand-ins.
//   4. The facility message window (every handle / state / hidden combination, the selection poll), the font-tag
//      window placement (both branches), the persona-status accessors and draw tasks behind a task record, the persona
//      model created on the stand-ins with its accessors and colour fades, the g_data colour lookups.
//   5. The bank manager's slots on the snapshots with every flag pattern: find, request (hit / new node), the blocked
//      marks (game flag 5145 both ways), the conflict test.
//   6. The background element handlers: the shop snapshot's live elements, then every handler on its own area through
//      its start events, 60 frames, its end event and 60 frames (state carried from pair to pair) with its draw handler
//      each frame; the dispatchers over every part set, every part sub-handler, the fan drawer, the digit wrappers.
//   7. The fusion cut-in created on the fusion snapshot: the task set, script requests taken one by one, the resource
//      list built, the command runner run over each script until it ends, the handlers on hand-made active nodes, the
//      resource on-insert, the vertex buffer, the runner helpers and the destroy callback.
// Documented-rule checks on the results of both bodies in every part (layouts, counts, clamps, fades, the handler
// protocol 0 / 1 / 2, end events finishing, the fade timing, the slide targets of table 0x6AF9F0).
// P3FES_HG_SEEDS / P3FES_HG_ONLY / P3FES_HG_TRACE: pairs per function (random worlds), one function, a trace line per pair.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/fcl.h"

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
namespace fcl = p3fes::game::fcl;

namespace p3fes::recomp_gen {
void fn_sub_16BC80_0016bc80(EEContext&);  // generated body
void fn_sub_16BC80_0016bc80__recomp(EEContext&);  // recompiled
void fn_sub_16BDB0_0016bdb0(EEContext&);  // generated body
void fn_sub_16BDB0_0016bdb0__recomp(EEContext&);  // recompiled
void fn_sub_20D650_0020d650(EEContext&);  // generated body
void fn_sub_20D650_0020d650__recomp(EEContext&);  // recompiled
void fn_sub_3C44D0_003c44d0(EEContext&);  // generated body
void fn_sub_3C44D0_003c44d0__recomp(EEContext&);  // recompiled
void fn_sub_3C49E0_003c49e0(EEContext&);  // generated body
void fn_sub_3C49E0_003c49e0__recomp(EEContext&);  // recompiled
void fn_sub_3C4A90_003c4a90(EEContext&);  // generated body
void fn_sub_3C4A90_003c4a90__recomp(EEContext&);  // recompiled
void fn_sub_3C78D0_003c78d0(EEContext&);  // generated body
void fn_sub_3C78D0_003c78d0__recomp(EEContext&);  // recompiled
void fn_sub_3C7D50_003c7d50(EEContext&);  // generated body
void fn_sub_3C7D50_003c7d50__recomp(EEContext&);  // recompiled
void fn_sub_3C7D60_003c7d60(EEContext&);  // generated body
void fn_sub_3C7D60_003c7d60__recomp(EEContext&);  // recompiled
void fn_sub_3C8400_003c8400(EEContext&);  // generated body
void fn_sub_3C8400_003c8400__recomp(EEContext&);  // recompiled
void fn_sub_3C8770_003c8770(EEContext&);  // generated body
void fn_sub_3C8770_003c8770__recomp(EEContext&);  // recompiled
void fn_sub_3C8810_003c8810(EEContext&);  // generated body
void fn_sub_3C8810_003c8810__recomp(EEContext&);  // recompiled
void fn_fclMisc_CreateMsgAssistTask_003c88d0(EEContext&);  // generated body
void fn_fclMisc_CreateMsgAssistTask_003c88d0__recomp(EEContext&);  // recompiled
void fn_sub_3C8D80_003c8d80(EEContext&);  // generated body
void fn_sub_3C8D80_003c8d80__recomp(EEContext&);  // recompiled
void fn_sub_3C8DA0_003c8da0(EEContext&);  // generated body
void fn_sub_3C8DA0_003c8da0__recomp(EEContext&);  // recompiled
void fn_sub_3C8DC0_003c8dc0(EEContext&);  // generated body
void fn_sub_3C8DC0_003c8dc0__recomp(EEContext&);  // recompiled
void fn_sub_3C8DD0_003c8dd0(EEContext&);  // generated body
void fn_sub_3C8DD0_003c8dd0__recomp(EEContext&);  // recompiled
void fn_sub_3C8DE0_003c8de0(EEContext&);  // generated body
void fn_sub_3C8DE0_003c8de0__recomp(EEContext&);  // recompiled
void fn_sub_3C8EA0_003c8ea0(EEContext&);  // generated body
void fn_sub_3C8EA0_003c8ea0__recomp(EEContext&);  // recompiled
void fn_sub_3C8EC0_003c8ec0(EEContext&);  // generated body
void fn_sub_3C8EC0_003c8ec0__recomp(EEContext&);  // recompiled
void fn_sub_3C8F20_003c8f20(EEContext&);  // generated body
void fn_sub_3C8F20_003c8f20__recomp(EEContext&);  // recompiled
void fn_sub_3C8F40_003c8f40(EEContext&);  // generated body
void fn_sub_3C8F40_003c8f40__recomp(EEContext&);  // recompiled
void fn_sub_3C9340_003c9340(EEContext&);  // generated body
void fn_sub_3C9340_003c9340__recomp(EEContext&);  // recompiled
void fn_sub_3C9570_003c9570(EEContext&);  // generated body
void fn_sub_3C9570_003c9570__recomp(EEContext&);  // recompiled
void fn_sub_3C9840_003c9840(EEContext&);  // generated body
void fn_sub_3C9840_003c9840__recomp(EEContext&);  // recompiled
void fn_sub_3C9B00_003c9b00(EEContext&);  // generated body
void fn_sub_3C9B00_003c9b00__recomp(EEContext&);  // recompiled
void fn_sub_3C9BA0_003c9ba0(EEContext&);  // generated body
void fn_sub_3C9BA0_003c9ba0__recomp(EEContext&);  // recompiled
void fn_sub_3C9C10_003c9c10(EEContext&);  // generated body
void fn_sub_3C9C10_003c9c10__recomp(EEContext&);  // recompiled
void fn_sub_3C9CD0_003c9cd0(EEContext&);  // generated body
void fn_sub_3C9CD0_003c9cd0__recomp(EEContext&);  // recompiled
void fn_sub_3C9D80_003c9d80(EEContext&);  // generated body
void fn_sub_3C9D80_003c9d80__recomp(EEContext&);  // recompiled
void fn_sub_3C9E00_003c9e00(EEContext&);  // generated body
void fn_sub_3C9E00_003c9e00__recomp(EEContext&);  // recompiled
void fn_sub_3C9E30_003c9e30(EEContext&);  // generated body
void fn_sub_3C9E30_003c9e30__recomp(EEContext&);  // recompiled
void fn_sub_3C9E70_003c9e70(EEContext&);  // generated body
void fn_sub_3C9E70_003c9e70__recomp(EEContext&);  // recompiled
void fn_sub_3C9EE0_003c9ee0(EEContext&);  // generated body
void fn_sub_3C9EE0_003c9ee0__recomp(EEContext&);  // recompiled
void fn_sub_3C9F10_003c9f10(EEContext&);  // generated body
void fn_sub_3C9F10_003c9f10__recomp(EEContext&);  // recompiled
void fn_sub_3C9F60_003c9f60(EEContext&);  // generated body
void fn_sub_3C9F60_003c9f60__recomp(EEContext&);  // recompiled
void fn_sub_3C9FB0_003c9fb0(EEContext&);  // generated body
void fn_sub_3C9FB0_003c9fb0__recomp(EEContext&);  // recompiled
void fn_fclMisc_UpdatePsStatusDrawLowTask_003ca610(EEContext&);  // generated body
void fn_fclMisc_UpdatePsStatusDrawLowTask_003ca610__recomp(EEContext&);  // recompiled
void fn_fclMisc_UpdatePsStatusDrawHighTask_003ca660(EEContext&);  // generated body
void fn_fclMisc_UpdatePsStatusDrawHighTask_003ca660__recomp(EEContext&);  // recompiled
void fn_nullsub_122_003ccc30(EEContext&);  // generated body
void fn_nullsub_122_003ccc30__recomp(EEContext&);  // recompiled
void fn_nullsub_123_003cd0a0(EEContext&);  // generated body
void fn_nullsub_123_003cd0a0__recomp(EEContext&);  // recompiled
void fn_nullsub_124_003cd590(EEContext&);  // generated body
void fn_nullsub_124_003cd590__recomp(EEContext&);  // recompiled
void fn_sub_3CDA60_003cda60(EEContext&);  // generated body
void fn_sub_3CDA60_003cda60__recomp(EEContext&);  // recompiled
void fn_sub_3CDBA0_003cdba0(EEContext&);  // generated body
void fn_sub_3CDBA0_003cdba0__recomp(EEContext&);  // recompiled
void fn_sub_3CDC80_003cdc80(EEContext&);  // generated body
void fn_sub_3CDC80_003cdc80__recomp(EEContext&);  // recompiled
void fn_sub_3CDCD0_003cdcd0(EEContext&);  // generated body
void fn_sub_3CDCD0_003cdcd0__recomp(EEContext&);  // recompiled
void fn_sub_3CDD80_003cdd80(EEContext&);  // generated body
void fn_sub_3CDD80_003cdd80__recomp(EEContext&);  // recompiled
void fn_sub_3CDE00_003cde00(EEContext&);  // generated body
void fn_sub_3CDE00_003cde00__recomp(EEContext&);  // recompiled
void fn_sub_3CDE70_003cde70(EEContext&);  // generated body
void fn_sub_3CDE70_003cde70__recomp(EEContext&);  // recompiled
void fn_sub_3CDEE0_003cdee0(EEContext&);  // generated body
void fn_sub_3CDEE0_003cdee0__recomp(EEContext&);  // recompiled
void fn_sub_3CDF40_003cdf40(EEContext&);  // generated body
void fn_sub_3CDF40_003cdf40__recomp(EEContext&);  // recompiled
void fn_sub_3CE060_003ce060(EEContext&);  // generated body
void fn_sub_3CE060_003ce060__recomp(EEContext&);  // recompiled
void fn_sub_3CE180_003ce180(EEContext&);  // generated body
void fn_sub_3CE180_003ce180__recomp(EEContext&);  // recompiled
void fn_sub_3CF520_003cf520(EEContext&);  // generated body
void fn_sub_3CF520_003cf520__recomp(EEContext&);  // recompiled
void fn_sub_3CF8F0_003cf8f0(EEContext&);  // generated body
void fn_sub_3CF8F0_003cf8f0__recomp(EEContext&);  // recompiled
void fn_sub_3CF960_003cf960(EEContext&);  // generated body
void fn_sub_3CF960_003cf960__recomp(EEContext&);  // recompiled
void fn_sub_3CFAC0_003cfac0(EEContext&);  // generated body
void fn_sub_3CFAC0_003cfac0__recomp(EEContext&);  // recompiled
void fn_sub_40D3B0_0040d3b0(EEContext&);  // generated body
void fn_sub_40D3B0_0040d3b0__recomp(EEContext&);  // recompiled
void fn_nullsub_67_0040d400(EEContext&);  // generated body
void fn_nullsub_67_0040d400__recomp(EEContext&);  // recompiled
void fn_sub_40D5B0_0040d5b0(EEContext&);  // generated body
void fn_sub_40D5B0_0040d5b0__recomp(EEContext&);  // recompiled
void fn_sub_40DCC0_0040dcc0(EEContext&);  // generated body
void fn_sub_40DCC0_0040dcc0__recomp(EEContext&);  // recompiled
void fn_sub_40EBC0_0040ebc0(EEContext&);  // generated body
void fn_sub_40EBC0_0040ebc0__recomp(EEContext&);  // recompiled
void fn_sub_40F030_0040f030(EEContext&);  // generated body
void fn_sub_40F030_0040f030__recomp(EEContext&);  // recompiled
void fn_sub_40F430_0040f430(EEContext&);  // generated body
void fn_sub_40F430_0040f430__recomp(EEContext&);  // recompiled
void fn_sub_40F5D0_0040f5d0(EEContext&);  // generated body
void fn_sub_40F5D0_0040f5d0__recomp(EEContext&);  // recompiled
void fn_sub_40FAB0_0040fab0(EEContext&);  // generated body
void fn_sub_40FAB0_0040fab0__recomp(EEContext&);  // recompiled
void fn_sub_40FB90_0040fb90(EEContext&);  // generated body
void fn_sub_40FB90_0040fb90__recomp(EEContext&);  // recompiled
void fn_sub_4101B0_004101b0(EEContext&);  // generated body
void fn_sub_4101B0_004101b0__recomp(EEContext&);  // recompiled
void fn_sub_4105E0_004105e0(EEContext&);  // generated body
void fn_sub_4105E0_004105e0__recomp(EEContext&);  // recompiled
void fn_sub_410A10_00410a10(EEContext&);  // generated body
void fn_sub_410A10_00410a10__recomp(EEContext&);  // recompiled
void fn_sub_4110E0_004110e0(EEContext&);  // generated body
void fn_sub_4110E0_004110e0__recomp(EEContext&);  // recompiled
void fn_sub_4113F0_004113f0(EEContext&);  // generated body
void fn_sub_4113F0_004113f0__recomp(EEContext&);  // recompiled
void fn_sub_411710_00411710(EEContext&);  // generated body
void fn_sub_411710_00411710__recomp(EEContext&);  // recompiled
void fn_sub_411790_00411790(EEContext&);  // generated body
void fn_sub_411790_00411790__recomp(EEContext&);  // recompiled
void fn_sub_4120A0_004120a0(EEContext&);  // generated body
void fn_sub_4120A0_004120a0__recomp(EEContext&);  // recompiled
void fn_sub_412610_00412610(EEContext&);  // generated body
void fn_sub_412610_00412610__recomp(EEContext&);  // recompiled
void fn_sub_412AF0_00412af0(EEContext&);  // generated body
void fn_sub_412AF0_00412af0__recomp(EEContext&);  // recompiled
void fn_sub_412BC0_00412bc0(EEContext&);  // generated body
void fn_sub_412BC0_00412bc0__recomp(EEContext&);  // recompiled
void fn_sub_413010_00413010(EEContext&);  // generated body
void fn_sub_413010_00413010__recomp(EEContext&);  // recompiled
void fn_sub_4131A0_004131a0(EEContext&);  // generated body
void fn_sub_4131A0_004131a0__recomp(EEContext&);  // recompiled
void fn_sub_413680_00413680(EEContext&);  // generated body
void fn_sub_413680_00413680__recomp(EEContext&);  // recompiled
void fn_sub_4138E0_004138e0(EEContext&);  // generated body
void fn_sub_4138E0_004138e0__recomp(EEContext&);  // recompiled
void fn_sub_413B10_00413b10(EEContext&);  // generated body
void fn_sub_413B10_00413b10__recomp(EEContext&);  // recompiled
void fn_sub_414100_00414100(EEContext&);  // generated body
void fn_sub_414100_00414100__recomp(EEContext&);  // recompiled
void fn_sub_4141E0_004141e0(EEContext&);  // generated body
void fn_sub_4141E0_004141e0__recomp(EEContext&);  // recompiled
void fn_sub_414280_00414280(EEContext&);  // generated body
void fn_sub_414280_00414280__recomp(EEContext&);  // recompiled
void fn_sub_414320_00414320(EEContext&);  // generated body
void fn_sub_414320_00414320__recomp(EEContext&);  // recompiled
void fn_sub_414500_00414500(EEContext&);  // generated body
void fn_sub_414500_00414500__recomp(EEContext&);  // recompiled
void fn_sub_4145F0_004145f0(EEContext&);  // generated body
void fn_sub_4145F0_004145f0__recomp(EEContext&);  // recompiled
void fn_sub_4146B0_004146b0(EEContext&);  // generated body
void fn_sub_4146B0_004146b0__recomp(EEContext&);  // recompiled
void fn_sub_4148B0_004148b0(EEContext&);  // generated body
void fn_sub_4148B0_004148b0__recomp(EEContext&);  // recompiled
void fn_sub_414950_00414950(EEContext&);  // generated body
void fn_sub_414950_00414950__recomp(EEContext&);  // recompiled
void fn_sub_4149F0_004149f0(EEContext&);  // generated body
void fn_sub_4149F0_004149f0__recomp(EEContext&);  // recompiled
void fn_sub_414AD0_00414ad0(EEContext&);  // generated body
void fn_sub_414AD0_00414ad0__recomp(EEContext&);  // recompiled
void fn_sub_414BD0_00414bd0(EEContext&);  // generated body
void fn_sub_414BD0_00414bd0__recomp(EEContext&);  // recompiled
void fn_sub_414C70_00414c70(EEContext&);  // generated body
void fn_sub_414C70_00414c70__recomp(EEContext&);  // recompiled
void fn_sub_414D70_00414d70(EEContext&);  // generated body
void fn_sub_414D70_00414d70__recomp(EEContext&);  // recompiled
void fn_sub_414E10_00414e10(EEContext&);  // generated body
void fn_sub_414E10_00414e10__recomp(EEContext&);  // recompiled
void fn_sub_414FE0_00414fe0(EEContext&);  // generated body
void fn_sub_414FE0_00414fe0__recomp(EEContext&);  // recompiled
void fn_sub_4154E0_004154e0(EEContext&);  // generated body
void fn_sub_4154E0_004154e0__recomp(EEContext&);  // recompiled
void fn_sub_415650_00415650(EEContext&);  // generated body
void fn_sub_415650_00415650__recomp(EEContext&);  // recompiled
void fn_sub_4157C0_004157c0(EEContext&);  // generated body
void fn_sub_4157C0_004157c0__recomp(EEContext&);  // recompiled
void fn_sub_415880_00415880(EEContext&);  // generated body
void fn_sub_415880_00415880__recomp(EEContext&);  // recompiled
void fn_sub_415A70_00415a70(EEContext&);  // generated body
void fn_sub_415A70_00415a70__recomp(EEContext&);  // recompiled
void fn_sub_415B30_00415b30(EEContext&);  // generated body
void fn_sub_415B30_00415b30__recomp(EEContext&);  // recompiled
void fn_sub_415B70_00415b70(EEContext&);  // generated body
void fn_sub_415B70_00415b70__recomp(EEContext&);  // recompiled
void fn_sub_415C30_00415c30(EEContext&);  // generated body
void fn_sub_415C30_00415c30__recomp(EEContext&);  // recompiled
void fn_sub_4167D0_004167d0(EEContext&);  // generated body
void fn_sub_4167D0_004167d0__recomp(EEContext&);  // recompiled
void fn_sub_416D20_00416d20(EEContext&);  // generated body
void fn_sub_416D20_00416d20__recomp(EEContext&);  // recompiled
void fn_sub_417030_00417030(EEContext&);  // generated body
void fn_sub_417030_00417030__recomp(EEContext&);  // recompiled
void fn_fclCmbEff_CreateCmbEffCalcTasks_00417160(EEContext&);  // generated body
void fn_fclCmbEff_CreateCmbEffCalcTasks_00417160__recomp(EEContext&);  // recompiled
void fn_sub_417330_00417330(EEContext&);  // generated body
void fn_sub_417330_00417330__recomp(EEContext&);  // recompiled
void fn_sub_417380_00417380(EEContext&);  // generated body
void fn_sub_417380_00417380__recomp(EEContext&);  // recompiled
void fn_sub_4173E0_004173e0(EEContext&);  // generated body
void fn_sub_4173E0_004173e0__recomp(EEContext&);  // recompiled
void fn_fclCmbEff_UpdateCmbEffDraw2DLowTask_004175e0(EEContext&);  // generated body
void fn_fclCmbEff_UpdateCmbEffDraw2DLowTask_004175e0__recomp(EEContext&);  // recompiled
void fn_fclCmbEff_UpdateCmbEffDrawSPTask_00417630(EEContext&);  // generated body
void fn_fclCmbEff_UpdateCmbEffDrawSPTask_00417630__recomp(EEContext&);  // recompiled
void fn_sub_417680_00417680(EEContext&);  // generated body
void fn_sub_417680_00417680__recomp(EEContext&);  // recompiled
void fn_sub_4176F0_004176f0(EEContext&);  // generated body
void fn_sub_4176F0_004176f0__recomp(EEContext&);  // recompiled
void fn_sub_4177E0_004177e0(EEContext&);  // generated body
void fn_sub_4177E0_004177e0__recomp(EEContext&);  // recompiled
void fn_sub_418030_00418030(EEContext&);  // generated body
void fn_sub_418030_00418030__recomp(EEContext&);  // recompiled
void fn_sub_4180A0_004180a0(EEContext&);  // generated body
void fn_sub_4180A0_004180a0__recomp(EEContext&);  // recompiled
void fn_sub_4180E0_004180e0(EEContext&);  // generated body
void fn_sub_4180E0_004180e0__recomp(EEContext&);  // recompiled
void fn_sub_418130_00418130(EEContext&);  // generated body
void fn_sub_418130_00418130__recomp(EEContext&);  // recompiled
void fn_sub_418340_00418340(EEContext&);  // generated body
void fn_sub_418340_00418340__recomp(EEContext&);  // recompiled
void fn_sub_419B00_00419b00(EEContext&);  // generated body
void fn_sub_419B00_00419b00__recomp(EEContext&);  // recompiled
void fn_sub_419B20_00419b20(EEContext&);  // generated body
void fn_sub_419B20_00419b20__recomp(EEContext&);  // recompiled
void fn_sub_419B40_00419b40(EEContext&);  // generated body
void fn_sub_419B40_00419b40__recomp(EEContext&);  // recompiled
void fn_sub_419C10_00419c10(EEContext&);  // generated body
void fn_sub_419C10_00419c10__recomp(EEContext&);  // recompiled
void fn_sub_41A2C0_0041a2c0(EEContext&);  // generated body
void fn_sub_41A2C0_0041a2c0__recomp(EEContext&);  // recompiled
void fn_sub_41A900_0041a900(EEContext&);  // generated body
void fn_sub_41A900_0041a900__recomp(EEContext&);  // recompiled
void fn_sub_41ADD0_0041add0(EEContext&);  // generated body
void fn_sub_41ADD0_0041add0__recomp(EEContext&);  // recompiled
void fn_sub_41B530_0041b530(EEContext&);  // generated body
void fn_sub_41B530_0041b530__recomp(EEContext&);  // recompiled
void fn_sub_41B550_0041b550(EEContext&);  // generated body
void fn_sub_41B550_0041b550__recomp(EEContext&);  // recompiled
void fn_sub_41B5C0_0041b5c0(EEContext&);  // generated body
void fn_sub_41B5C0_0041b5c0__recomp(EEContext&);  // recompiled
void fn_sub_41BA60_0041ba60(EEContext&);  // generated body
void fn_sub_41BA60_0041ba60__recomp(EEContext&);  // recompiled
void fn_sub_41BC90_0041bc90(EEContext&);  // generated body
void fn_sub_41BC90_0041bc90__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_16BC80", 0x16BC80, &recomp_gen::fn_sub_16BC80_0016bc80, &recomp_gen::fn_sub_16BC80_0016bc80__recomp},
    {"sub_16BDB0", 0x16BDB0, &recomp_gen::fn_sub_16BDB0_0016bdb0, &recomp_gen::fn_sub_16BDB0_0016bdb0__recomp},
    {"sub_20D650", 0x20D650, &recomp_gen::fn_sub_20D650_0020d650, &recomp_gen::fn_sub_20D650_0020d650__recomp},
    {"sub_3C44D0", 0x3C44D0, &recomp_gen::fn_sub_3C44D0_003c44d0, &recomp_gen::fn_sub_3C44D0_003c44d0__recomp},
    {"sub_3C49E0", 0x3C49E0, &recomp_gen::fn_sub_3C49E0_003c49e0, &recomp_gen::fn_sub_3C49E0_003c49e0__recomp},
    {"sub_3C4A90", 0x3C4A90, &recomp_gen::fn_sub_3C4A90_003c4a90, &recomp_gen::fn_sub_3C4A90_003c4a90__recomp},
    {"sub_3C78D0", 0x3C78D0, &recomp_gen::fn_sub_3C78D0_003c78d0, &recomp_gen::fn_sub_3C78D0_003c78d0__recomp},
    {"sub_3C7D50", 0x3C7D50, &recomp_gen::fn_sub_3C7D50_003c7d50, &recomp_gen::fn_sub_3C7D50_003c7d50__recomp},
    {"sub_3C7D60", 0x3C7D60, &recomp_gen::fn_sub_3C7D60_003c7d60, &recomp_gen::fn_sub_3C7D60_003c7d60__recomp},
    {"sub_3C8400", 0x3C8400, &recomp_gen::fn_sub_3C8400_003c8400, &recomp_gen::fn_sub_3C8400_003c8400__recomp},
    {"sub_3C8770", 0x3C8770, &recomp_gen::fn_sub_3C8770_003c8770, &recomp_gen::fn_sub_3C8770_003c8770__recomp},
    {"sub_3C8810", 0x3C8810, &recomp_gen::fn_sub_3C8810_003c8810, &recomp_gen::fn_sub_3C8810_003c8810__recomp},
    {"fclMisc_CreateMsgAssistTask", 0x3C88D0, &recomp_gen::fn_fclMisc_CreateMsgAssistTask_003c88d0, &recomp_gen::fn_fclMisc_CreateMsgAssistTask_003c88d0__recomp},
    {"sub_3C8D80", 0x3C8D80, &recomp_gen::fn_sub_3C8D80_003c8d80, &recomp_gen::fn_sub_3C8D80_003c8d80__recomp},
    {"sub_3C8DA0", 0x3C8DA0, &recomp_gen::fn_sub_3C8DA0_003c8da0, &recomp_gen::fn_sub_3C8DA0_003c8da0__recomp},
    {"sub_3C8DC0", 0x3C8DC0, &recomp_gen::fn_sub_3C8DC0_003c8dc0, &recomp_gen::fn_sub_3C8DC0_003c8dc0__recomp},
    {"sub_3C8DD0", 0x3C8DD0, &recomp_gen::fn_sub_3C8DD0_003c8dd0, &recomp_gen::fn_sub_3C8DD0_003c8dd0__recomp},
    {"sub_3C8DE0", 0x3C8DE0, &recomp_gen::fn_sub_3C8DE0_003c8de0, &recomp_gen::fn_sub_3C8DE0_003c8de0__recomp},
    {"sub_3C8EA0", 0x3C8EA0, &recomp_gen::fn_sub_3C8EA0_003c8ea0, &recomp_gen::fn_sub_3C8EA0_003c8ea0__recomp},
    {"sub_3C8EC0", 0x3C8EC0, &recomp_gen::fn_sub_3C8EC0_003c8ec0, &recomp_gen::fn_sub_3C8EC0_003c8ec0__recomp},
    {"sub_3C8F20", 0x3C8F20, &recomp_gen::fn_sub_3C8F20_003c8f20, &recomp_gen::fn_sub_3C8F20_003c8f20__recomp},
    {"sub_3C8F40", 0x3C8F40, &recomp_gen::fn_sub_3C8F40_003c8f40, &recomp_gen::fn_sub_3C8F40_003c8f40__recomp},
    {"sub_3C9340", 0x3C9340, &recomp_gen::fn_sub_3C9340_003c9340, &recomp_gen::fn_sub_3C9340_003c9340__recomp},
    {"sub_3C9570", 0x3C9570, &recomp_gen::fn_sub_3C9570_003c9570, &recomp_gen::fn_sub_3C9570_003c9570__recomp},
    {"sub_3C9840", 0x3C9840, &recomp_gen::fn_sub_3C9840_003c9840, &recomp_gen::fn_sub_3C9840_003c9840__recomp},
    {"sub_3C9B00", 0x3C9B00, &recomp_gen::fn_sub_3C9B00_003c9b00, &recomp_gen::fn_sub_3C9B00_003c9b00__recomp},
    {"sub_3C9BA0", 0x3C9BA0, &recomp_gen::fn_sub_3C9BA0_003c9ba0, &recomp_gen::fn_sub_3C9BA0_003c9ba0__recomp},
    {"sub_3C9C10", 0x3C9C10, &recomp_gen::fn_sub_3C9C10_003c9c10, &recomp_gen::fn_sub_3C9C10_003c9c10__recomp},
    {"sub_3C9CD0", 0x3C9CD0, &recomp_gen::fn_sub_3C9CD0_003c9cd0, &recomp_gen::fn_sub_3C9CD0_003c9cd0__recomp},
    {"sub_3C9D80", 0x3C9D80, &recomp_gen::fn_sub_3C9D80_003c9d80, &recomp_gen::fn_sub_3C9D80_003c9d80__recomp},
    {"sub_3C9E00", 0x3C9E00, &recomp_gen::fn_sub_3C9E00_003c9e00, &recomp_gen::fn_sub_3C9E00_003c9e00__recomp},
    {"sub_3C9E30", 0x3C9E30, &recomp_gen::fn_sub_3C9E30_003c9e30, &recomp_gen::fn_sub_3C9E30_003c9e30__recomp},
    {"sub_3C9E70", 0x3C9E70, &recomp_gen::fn_sub_3C9E70_003c9e70, &recomp_gen::fn_sub_3C9E70_003c9e70__recomp},
    {"sub_3C9EE0", 0x3C9EE0, &recomp_gen::fn_sub_3C9EE0_003c9ee0, &recomp_gen::fn_sub_3C9EE0_003c9ee0__recomp},
    {"sub_3C9F10", 0x3C9F10, &recomp_gen::fn_sub_3C9F10_003c9f10, &recomp_gen::fn_sub_3C9F10_003c9f10__recomp},
    {"sub_3C9F60", 0x3C9F60, &recomp_gen::fn_sub_3C9F60_003c9f60, &recomp_gen::fn_sub_3C9F60_003c9f60__recomp},
    {"sub_3C9FB0", 0x3C9FB0, &recomp_gen::fn_sub_3C9FB0_003c9fb0, &recomp_gen::fn_sub_3C9FB0_003c9fb0__recomp},
    {"fclMisc_UpdatePsStatusDrawLowTask", 0x3CA610, &recomp_gen::fn_fclMisc_UpdatePsStatusDrawLowTask_003ca610, &recomp_gen::fn_fclMisc_UpdatePsStatusDrawLowTask_003ca610__recomp},
    {"fclMisc_UpdatePsStatusDrawHighTask", 0x3CA660, &recomp_gen::fn_fclMisc_UpdatePsStatusDrawHighTask_003ca660, &recomp_gen::fn_fclMisc_UpdatePsStatusDrawHighTask_003ca660__recomp},
    {"nullsub_122", 0x3CCC30, &recomp_gen::fn_nullsub_122_003ccc30, &recomp_gen::fn_nullsub_122_003ccc30__recomp},
    {"nullsub_123", 0x3CD0A0, &recomp_gen::fn_nullsub_123_003cd0a0, &recomp_gen::fn_nullsub_123_003cd0a0__recomp},
    {"nullsub_124", 0x3CD590, &recomp_gen::fn_nullsub_124_003cd590, &recomp_gen::fn_nullsub_124_003cd590__recomp},
    {"sub_3CDA60", 0x3CDA60, &recomp_gen::fn_sub_3CDA60_003cda60, &recomp_gen::fn_sub_3CDA60_003cda60__recomp},
    {"sub_3CDBA0", 0x3CDBA0, &recomp_gen::fn_sub_3CDBA0_003cdba0, &recomp_gen::fn_sub_3CDBA0_003cdba0__recomp},
    {"sub_3CDC80", 0x3CDC80, &recomp_gen::fn_sub_3CDC80_003cdc80, &recomp_gen::fn_sub_3CDC80_003cdc80__recomp},
    {"sub_3CDCD0", 0x3CDCD0, &recomp_gen::fn_sub_3CDCD0_003cdcd0, &recomp_gen::fn_sub_3CDCD0_003cdcd0__recomp},
    {"sub_3CDD80", 0x3CDD80, &recomp_gen::fn_sub_3CDD80_003cdd80, &recomp_gen::fn_sub_3CDD80_003cdd80__recomp},
    {"sub_3CDE00", 0x3CDE00, &recomp_gen::fn_sub_3CDE00_003cde00, &recomp_gen::fn_sub_3CDE00_003cde00__recomp},
    {"sub_3CDE70", 0x3CDE70, &recomp_gen::fn_sub_3CDE70_003cde70, &recomp_gen::fn_sub_3CDE70_003cde70__recomp},
    {"sub_3CDEE0", 0x3CDEE0, &recomp_gen::fn_sub_3CDEE0_003cdee0, &recomp_gen::fn_sub_3CDEE0_003cdee0__recomp},
    {"sub_3CDF40", 0x3CDF40, &recomp_gen::fn_sub_3CDF40_003cdf40, &recomp_gen::fn_sub_3CDF40_003cdf40__recomp},
    {"sub_3CE060", 0x3CE060, &recomp_gen::fn_sub_3CE060_003ce060, &recomp_gen::fn_sub_3CE060_003ce060__recomp},
    {"sub_3CE180", 0x3CE180, &recomp_gen::fn_sub_3CE180_003ce180, &recomp_gen::fn_sub_3CE180_003ce180__recomp},
    {"sub_3CF520", 0x3CF520, &recomp_gen::fn_sub_3CF520_003cf520, &recomp_gen::fn_sub_3CF520_003cf520__recomp},
    {"sub_3CF8F0", 0x3CF8F0, &recomp_gen::fn_sub_3CF8F0_003cf8f0, &recomp_gen::fn_sub_3CF8F0_003cf8f0__recomp},
    {"sub_3CF960", 0x3CF960, &recomp_gen::fn_sub_3CF960_003cf960, &recomp_gen::fn_sub_3CF960_003cf960__recomp},
    {"sub_3CFAC0", 0x3CFAC0, &recomp_gen::fn_sub_3CFAC0_003cfac0, &recomp_gen::fn_sub_3CFAC0_003cfac0__recomp},
    {"sub_40D3B0", 0x40D3B0, &recomp_gen::fn_sub_40D3B0_0040d3b0, &recomp_gen::fn_sub_40D3B0_0040d3b0__recomp},
    {"nullsub_67", 0x40D400, &recomp_gen::fn_nullsub_67_0040d400, &recomp_gen::fn_nullsub_67_0040d400__recomp},
    {"sub_40D5B0", 0x40D5B0, &recomp_gen::fn_sub_40D5B0_0040d5b0, &recomp_gen::fn_sub_40D5B0_0040d5b0__recomp},
    {"sub_40DCC0", 0x40DCC0, &recomp_gen::fn_sub_40DCC0_0040dcc0, &recomp_gen::fn_sub_40DCC0_0040dcc0__recomp},
    {"sub_40EBC0", 0x40EBC0, &recomp_gen::fn_sub_40EBC0_0040ebc0, &recomp_gen::fn_sub_40EBC0_0040ebc0__recomp},
    {"sub_40F030", 0x40F030, &recomp_gen::fn_sub_40F030_0040f030, &recomp_gen::fn_sub_40F030_0040f030__recomp},
    {"sub_40F430", 0x40F430, &recomp_gen::fn_sub_40F430_0040f430, &recomp_gen::fn_sub_40F430_0040f430__recomp},
    {"sub_40F5D0", 0x40F5D0, &recomp_gen::fn_sub_40F5D0_0040f5d0, &recomp_gen::fn_sub_40F5D0_0040f5d0__recomp},
    {"sub_40FAB0", 0x40FAB0, &recomp_gen::fn_sub_40FAB0_0040fab0, &recomp_gen::fn_sub_40FAB0_0040fab0__recomp},
    {"sub_40FB90", 0x40FB90, &recomp_gen::fn_sub_40FB90_0040fb90, &recomp_gen::fn_sub_40FB90_0040fb90__recomp},
    {"sub_4101B0", 0x4101B0, &recomp_gen::fn_sub_4101B0_004101b0, &recomp_gen::fn_sub_4101B0_004101b0__recomp},
    {"sub_4105E0", 0x4105E0, &recomp_gen::fn_sub_4105E0_004105e0, &recomp_gen::fn_sub_4105E0_004105e0__recomp},
    {"sub_410A10", 0x410A10, &recomp_gen::fn_sub_410A10_00410a10, &recomp_gen::fn_sub_410A10_00410a10__recomp},
    {"sub_4110E0", 0x4110E0, &recomp_gen::fn_sub_4110E0_004110e0, &recomp_gen::fn_sub_4110E0_004110e0__recomp},
    {"sub_4113F0", 0x4113F0, &recomp_gen::fn_sub_4113F0_004113f0, &recomp_gen::fn_sub_4113F0_004113f0__recomp},
    {"sub_411710", 0x411710, &recomp_gen::fn_sub_411710_00411710, &recomp_gen::fn_sub_411710_00411710__recomp},
    {"sub_411790", 0x411790, &recomp_gen::fn_sub_411790_00411790, &recomp_gen::fn_sub_411790_00411790__recomp},
    {"sub_4120A0", 0x4120A0, &recomp_gen::fn_sub_4120A0_004120a0, &recomp_gen::fn_sub_4120A0_004120a0__recomp},
    {"sub_412610", 0x412610, &recomp_gen::fn_sub_412610_00412610, &recomp_gen::fn_sub_412610_00412610__recomp},
    {"sub_412AF0", 0x412AF0, &recomp_gen::fn_sub_412AF0_00412af0, &recomp_gen::fn_sub_412AF0_00412af0__recomp},
    {"sub_412BC0", 0x412BC0, &recomp_gen::fn_sub_412BC0_00412bc0, &recomp_gen::fn_sub_412BC0_00412bc0__recomp},
    {"sub_413010", 0x413010, &recomp_gen::fn_sub_413010_00413010, &recomp_gen::fn_sub_413010_00413010__recomp},
    {"sub_4131A0", 0x4131A0, &recomp_gen::fn_sub_4131A0_004131a0, &recomp_gen::fn_sub_4131A0_004131a0__recomp},
    {"sub_413680", 0x413680, &recomp_gen::fn_sub_413680_00413680, &recomp_gen::fn_sub_413680_00413680__recomp},
    {"sub_4138E0", 0x4138E0, &recomp_gen::fn_sub_4138E0_004138e0, &recomp_gen::fn_sub_4138E0_004138e0__recomp},
    {"sub_413B10", 0x413B10, &recomp_gen::fn_sub_413B10_00413b10, &recomp_gen::fn_sub_413B10_00413b10__recomp},
    {"sub_414100", 0x414100, &recomp_gen::fn_sub_414100_00414100, &recomp_gen::fn_sub_414100_00414100__recomp},
    {"sub_4141E0", 0x4141E0, &recomp_gen::fn_sub_4141E0_004141e0, &recomp_gen::fn_sub_4141E0_004141e0__recomp},
    {"sub_414280", 0x414280, &recomp_gen::fn_sub_414280_00414280, &recomp_gen::fn_sub_414280_00414280__recomp},
    {"sub_414320", 0x414320, &recomp_gen::fn_sub_414320_00414320, &recomp_gen::fn_sub_414320_00414320__recomp},
    {"sub_414500", 0x414500, &recomp_gen::fn_sub_414500_00414500, &recomp_gen::fn_sub_414500_00414500__recomp},
    {"sub_4145F0", 0x4145F0, &recomp_gen::fn_sub_4145F0_004145f0, &recomp_gen::fn_sub_4145F0_004145f0__recomp},
    {"sub_4146B0", 0x4146B0, &recomp_gen::fn_sub_4146B0_004146b0, &recomp_gen::fn_sub_4146B0_004146b0__recomp},
    {"sub_4148B0", 0x4148B0, &recomp_gen::fn_sub_4148B0_004148b0, &recomp_gen::fn_sub_4148B0_004148b0__recomp},
    {"sub_414950", 0x414950, &recomp_gen::fn_sub_414950_00414950, &recomp_gen::fn_sub_414950_00414950__recomp},
    {"sub_4149F0", 0x4149F0, &recomp_gen::fn_sub_4149F0_004149f0, &recomp_gen::fn_sub_4149F0_004149f0__recomp},
    {"sub_414AD0", 0x414AD0, &recomp_gen::fn_sub_414AD0_00414ad0, &recomp_gen::fn_sub_414AD0_00414ad0__recomp},
    {"sub_414BD0", 0x414BD0, &recomp_gen::fn_sub_414BD0_00414bd0, &recomp_gen::fn_sub_414BD0_00414bd0__recomp},
    {"sub_414C70", 0x414C70, &recomp_gen::fn_sub_414C70_00414c70, &recomp_gen::fn_sub_414C70_00414c70__recomp},
    {"sub_414D70", 0x414D70, &recomp_gen::fn_sub_414D70_00414d70, &recomp_gen::fn_sub_414D70_00414d70__recomp},
    {"sub_414E10", 0x414E10, &recomp_gen::fn_sub_414E10_00414e10, &recomp_gen::fn_sub_414E10_00414e10__recomp},
    {"sub_414FE0", 0x414FE0, &recomp_gen::fn_sub_414FE0_00414fe0, &recomp_gen::fn_sub_414FE0_00414fe0__recomp},
    {"sub_4154E0", 0x4154E0, &recomp_gen::fn_sub_4154E0_004154e0, &recomp_gen::fn_sub_4154E0_004154e0__recomp},
    {"sub_415650", 0x415650, &recomp_gen::fn_sub_415650_00415650, &recomp_gen::fn_sub_415650_00415650__recomp},
    {"sub_4157C0", 0x4157C0, &recomp_gen::fn_sub_4157C0_004157c0, &recomp_gen::fn_sub_4157C0_004157c0__recomp},
    {"sub_415880", 0x415880, &recomp_gen::fn_sub_415880_00415880, &recomp_gen::fn_sub_415880_00415880__recomp},
    {"sub_415A70", 0x415A70, &recomp_gen::fn_sub_415A70_00415a70, &recomp_gen::fn_sub_415A70_00415a70__recomp},
    {"sub_415B30", 0x415B30, &recomp_gen::fn_sub_415B30_00415b30, &recomp_gen::fn_sub_415B30_00415b30__recomp},
    {"sub_415B70", 0x415B70, &recomp_gen::fn_sub_415B70_00415b70, &recomp_gen::fn_sub_415B70_00415b70__recomp},
    {"sub_415C30", 0x415C30, &recomp_gen::fn_sub_415C30_00415c30, &recomp_gen::fn_sub_415C30_00415c30__recomp},
    {"sub_4167D0", 0x4167D0, &recomp_gen::fn_sub_4167D0_004167d0, &recomp_gen::fn_sub_4167D0_004167d0__recomp},
    {"sub_416D20", 0x416D20, &recomp_gen::fn_sub_416D20_00416d20, &recomp_gen::fn_sub_416D20_00416d20__recomp},
    {"sub_417030", 0x417030, &recomp_gen::fn_sub_417030_00417030, &recomp_gen::fn_sub_417030_00417030__recomp},
    {"fclCmbEff_CreateCmbEffCalcTasks", 0x417160, &recomp_gen::fn_fclCmbEff_CreateCmbEffCalcTasks_00417160, &recomp_gen::fn_fclCmbEff_CreateCmbEffCalcTasks_00417160__recomp},
    {"sub_417330", 0x417330, &recomp_gen::fn_sub_417330_00417330, &recomp_gen::fn_sub_417330_00417330__recomp},
    {"sub_417380", 0x417380, &recomp_gen::fn_sub_417380_00417380, &recomp_gen::fn_sub_417380_00417380__recomp},
    {"sub_4173E0", 0x4173E0, &recomp_gen::fn_sub_4173E0_004173e0, &recomp_gen::fn_sub_4173E0_004173e0__recomp},
    {"fclCmbEff_UpdateCmbEffDraw2DLowTask", 0x4175E0, &recomp_gen::fn_fclCmbEff_UpdateCmbEffDraw2DLowTask_004175e0, &recomp_gen::fn_fclCmbEff_UpdateCmbEffDraw2DLowTask_004175e0__recomp},
    {"fclCmbEff_UpdateCmbEffDrawSPTask", 0x417630, &recomp_gen::fn_fclCmbEff_UpdateCmbEffDrawSPTask_00417630, &recomp_gen::fn_fclCmbEff_UpdateCmbEffDrawSPTask_00417630__recomp},
    {"sub_417680", 0x417680, &recomp_gen::fn_sub_417680_00417680, &recomp_gen::fn_sub_417680_00417680__recomp},
    {"sub_4176F0", 0x4176F0, &recomp_gen::fn_sub_4176F0_004176f0, &recomp_gen::fn_sub_4176F0_004176f0__recomp},
    {"sub_4177E0", 0x4177E0, &recomp_gen::fn_sub_4177E0_004177e0, &recomp_gen::fn_sub_4177E0_004177e0__recomp},
    {"sub_418030", 0x418030, &recomp_gen::fn_sub_418030_00418030, &recomp_gen::fn_sub_418030_00418030__recomp},
    {"sub_4180A0", 0x4180A0, &recomp_gen::fn_sub_4180A0_004180a0, &recomp_gen::fn_sub_4180A0_004180a0__recomp},
    {"sub_4180E0", 0x4180E0, &recomp_gen::fn_sub_4180E0_004180e0, &recomp_gen::fn_sub_4180E0_004180e0__recomp},
    {"sub_418130", 0x418130, &recomp_gen::fn_sub_418130_00418130, &recomp_gen::fn_sub_418130_00418130__recomp},
    {"sub_418340", 0x418340, &recomp_gen::fn_sub_418340_00418340, &recomp_gen::fn_sub_418340_00418340__recomp},
    {"sub_419B00", 0x419B00, &recomp_gen::fn_sub_419B00_00419b00, &recomp_gen::fn_sub_419B00_00419b00__recomp},
    {"sub_419B20", 0x419B20, &recomp_gen::fn_sub_419B20_00419b20, &recomp_gen::fn_sub_419B20_00419b20__recomp},
    {"sub_419B40", 0x419B40, &recomp_gen::fn_sub_419B40_00419b40, &recomp_gen::fn_sub_419B40_00419b40__recomp},
    {"sub_419C10", 0x419C10, &recomp_gen::fn_sub_419C10_00419c10, &recomp_gen::fn_sub_419C10_00419c10__recomp},
    {"sub_41A2C0", 0x41A2C0, &recomp_gen::fn_sub_41A2C0_0041a2c0, &recomp_gen::fn_sub_41A2C0_0041a2c0__recomp},
    {"sub_41A900", 0x41A900, &recomp_gen::fn_sub_41A900_0041a900, &recomp_gen::fn_sub_41A900_0041a900__recomp},
    {"sub_41ADD0", 0x41ADD0, &recomp_gen::fn_sub_41ADD0_0041add0, &recomp_gen::fn_sub_41ADD0_0041add0__recomp},
    {"sub_41B530", 0x41B530, &recomp_gen::fn_sub_41B530_0041b530, &recomp_gen::fn_sub_41B530_0041b530__recomp},
    {"sub_41B550", 0x41B550, &recomp_gen::fn_sub_41B550_0041b550, &recomp_gen::fn_sub_41B550_0041b550__recomp},
    {"sub_41B5C0", 0x41B5C0, &recomp_gen::fn_sub_41B5C0_0041b5c0, &recomp_gen::fn_sub_41B5C0_0041b5c0__recomp},
    {"sub_41BA60", 0x41BA60, &recomp_gen::fn_sub_41BA60_0041ba60, &recomp_gen::fn_sub_41BA60_0041ba60__recomp},
    {"sub_41BC90", 0x41BC90, &recomp_gen::fn_sub_41BC90_0041bc90, &recomp_gen::fn_sub_41BC90_0041bc90__recomp},
};

constexpr u32 kWorld = 0x01810000u;  // the random worlds: 64 KiB of free RAM above the harness's arena
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 16;
constexpr u32 kOut = 0x01F40000u;  // free in every snapshot (above the stand-in heap) and in the ELF image

// --- the pair runner of this file -------------------------------------------------------------------------------------
// hgp::pair (handgen_pairs.h: the whole register file and cycles at every check point and at the return / stop, all
// 32 MiB of RAM, the scratchpad, the bus) through two trampolines that set chosen FPRs after the random register file
// and give each body its own stand-in world (stand_ins.h: the heap behind H_Malloc and the RW slots, printf / sprintf,
// the H_Cdvd layer, plus recorders for callees this test library does not emit). The two worlds' call logs must
// match. With `persist` the two worlds live on across pairs (a create followed by its accessors and updates).
struct Tramp {
    Fn fn[2] = {};
    std::unique_ptr<StandInWorld> world[2];
    std::map<unsigned, u32> fpr;
    bool standins = false;
    bool persist = false;
    WorldSetup setup;
};
Tramp g_t;
int g_pairs = 0;
std::map<std::string, int> g_stops;  // early stops by "function @ pc" (both bodies alike; reported, not failures)

template <int K>
void tramp(EEContext& c) {
    for (const auto& [i, v] : g_t.fpr) c.fpr[i] = v;
    if (!g_t.standins) {
        g_t.fn[K](c);
        return;
    }
    if (!g_t.persist || !g_t.world[K]) {
        g_t.world[K] = std::make_unique<StandInWorld>();
        install_standard(*g_t.world[K]);
        if (g_t.setup) g_t.setup(*g_t.world[K]);
    }
    g_t.world[K]->si.log.clear();
    StandInsScope scope(g_t.world[K]->si);
    g_t.fn[K](c);
}

const Case& by_name(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

// Recorders for callees this test library does not emit (a stand-in is asked first by every such stub; an emitted or
// replaced callee runs for real). v0 = the value the paths below want.
WorldSetup recorders(std::vector<std::pair<u32, u64>> extra = {}) {
    return [extra](StandInWorld& w) {
        const std::pair<u32, const char*> names[] = {
            {0x3A2750u, "itfMesMngGetSelectWord84"}, {0x3A2830u, "itfMesMngGetSelection"}, {0x3A3E90u, "itfMesMngClearStateFlags"},
            {0x3A25F0u, "itfMesMngSetBusy"},         {0x3A3E10u, "itfMesMngSetStateFlags"}, {0x3A3CE0u, "itfMesMngSetTextPosition"},
            {0x3A8650u, "sub_3A8650"},               {0x3A6A80u, "itfMesMngSetWindowOffset"}, {0x3182D0u, "sub_3182D0"},
            {0x3174E0u, "sub_3174E0"},               {0x1158B0u, "sprCreateHandle (-> kOut + 0x3000)"},          {0x115980u, "sub_115980"},
            {0x40CC30u, "sub_40CC30"},               {0x41BF80u, "sub_41BF80"},               {0x41BAF0u, "sub_41BAF0"},
            {0x1052B0u, "sub_1052B0 (debug log)"}, {0x1127D0u, "sub_1127D0"},        {0x418230u, "sub_418230"},
            {0x416240u, "sub_416240"},               {0x4163F0u, "sub_4163F0"},               {0x4166D0u, "sub_4166D0"},
            {0x414770u, "sub_414770"},               {0x40D640u, "sub_40D640"},               {0x416B90u, "sub_416B90"}};
        for (const auto& [va, n] : names) w.si.install_recorder(va, n, va == 0x1158B0u ? kOut + 0x3000u : 0u);
        for (const auto& [va, v] : extra) w.si.install_recorder(va, "extra", v);
    };
}

struct Opt {
    std::map<unsigned, u64> gpr_in;  // $t0.. (arguments 5..8)
    std::map<unsigned, u32> fpr;     // $f12..
    bool standins = true;
    bool persist = false;
    WorldSetup setup = recorders();
};

hgp::Run fcl_pair(Machine& m, const char* name, const Args& a, u32 seed, const char* what, const Opt& o = {}) {
    const Case& c = by_name(name);
    g_t.fn[0] = c.hand;
    g_t.fn[1] = c.recomp;
    g_t.fpr = o.fpr;
    g_t.standins = o.standins;
    if (!o.persist) {
        g_t.world[0].reset();
        g_t.world[1].reset();
    }
    g_t.persist = o.persist;
    g_t.setup = o.setup;
    HwCheck hw;
    hw.gpr_in = o.gpr_in;
    if (std::getenv("P3FES_HG_TRACE")) std::fprintf(stderr, "%s (%s) seed %u\n", name, what, seed);
    hgp::Run r = hgp::pair(m, &tramp<0>, &tramp<1>, a, seed, what, hw);
    if (o.standins && g_t.world[0] && g_t.world[1]) expect_same_log(g_t.world[0]->si, g_t.world[1]->si, what);
    if (r.stopped) ++g_stops[std::string(name) + " @ " + hex64(r.stop_pc) + " (" + r.what.substr(0, 60) + ")"];
    ++g_pairs;
    return r;
}
// A persisted sequence starts from fresh stand-in worlds (a persisted pair otherwise reuses the last sequence's).
void fresh_worlds() {
    g_t.world[0].reset();
    g_t.world[1].reset();
}
u64 v0_of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
s32 v0s(const hgp::Run& r) { return static_cast<s32>(r.end.gpr[GPR_V0].u64[0]); }

// --- guest memory helpers ---------------------------------------------------------------------------------------------
// Host reads of guest RAM, masked to the 32 MiB (a value read back from a run that stopped early may be anything).
u32 ram_off(u32 va, u32 n) {
    const u32 a = va & 0x01FFFFFFu;
    return a + n <= EEMemory::kMainRamSize ? a : 0;
}
u32 r32(const Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.mem.main_ram() + ram_off(va, 4), 4);
    return v;
}
s16 r16(const Machine& m, u32 va) {
    s16 v;
    std::memcpy(&v, m.mem.main_ram() + ram_off(va, 2), 2);
    return v;
}
u8 r8(const Machine& m, u32 va) { return m.mem.main_ram()[ram_off(va, 1)]; }
float rf(const Machine& m, u32 va) {
    float v;
    std::memcpy(&v, m.mem.main_ram() + ram_off(va, 4), 4);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void w16(Machine& m, u32 va, u16 v) { std::memcpy(m.at(va), &v, 2); }
void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void wf(Machine& m, u32 va, float v) { std::memcpy(m.at(va), &v, 4); }
void zero(Machine& m, u32 va, u32 n) { std::memset(m.at(va), 0, n); }

// --- the replay snapshots ---------------------------------------------------------------------------------------------
// MsgAssist (0x7CE67C) and the bank manager (0x7CE680) are live in every snapshot (boot-time tasks); shop_ref_4100 has
// the shop open with its background manager 0x1544318 (two of this slice's handlers live: sub_40F030 curtains,
// sub_4120A0 slides), fusion_vr_5000 the fusion menu.
constexpr const char* kSnaps[] = {"dorm_replay_4900", "b_5800", "fusion_vr_5000", "shop_ref_4100", "climb_ref_17000"};

const std::vector<u8>& snapshot(const char* dir) {
    static std::map<std::string, std::vector<u8>> cache;
    auto it = cache.find(dir);
    if (it == cache.end()) it = cache.emplace(dir, read_snapshot(dir)).first;
    return it->second;
}
bool restore(Machine& m, const char* dir) {
    const std::vector<u8>& s = snapshot(dir);
    if (s.size() != EEMemory::kMainRamSize) return false;
    std::memcpy(m.mem.main_ram(), s.data(), s.size());
    return true;
}
std::unique_ptr<Machine> elf_machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    write_rw_slots(*m);
    return m;
}

}  // namespace

// =====================================================================================================================
// 1. Every body on random worlds (the p3fes_handgen skeleton, fewer seeds: the cases below carry the real inputs)
// =====================================================================================================================
TEST_CASE("game(fcl): every body equals its recompiled body on random worlds") {
    auto m = elf_machine();
    if (!m) return;
    const char* env = std::getenv("P3FES_HG_SEEDS");
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
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
// 2. nmlist: object create on the stand-in heap, remove and clear on hand-built lists (documented layout rules)
// =====================================================================================================================
TEST_CASE("game(fcl): nmlist object create / remove / clear (documented rules)") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    u32 seed = 1000;
    // create: payload sizes and callbacks, the layout of nm_message.h
    for (const u32 size : {0u, 4u, 12u, 28u, 160u})
        for (int cb = 0; cb < 2; ++cb) {
            const u32 f1 = cb ? 0x418130u : 0, f2 = cb ? 0x418230u : 0, f3 = cb ? 0x4110E0u : 0;
            const hgp::Run r = fcl_pair(m, "sub_3C44D0", {size, f1, f2, f3}, ++seed, "nmListObjCreate");
            const u32 obj = static_cast<u32>(v0_of(r));
            REQUIRE(obj >= kStandInHeap);
            CHECK(r32(m, obj + fcl::kNmObjSize) == size);
            CHECK(r32(m, obj + fcl::kNmObjPayload) == (size ? obj + fcl::kNmObjHeaderSize : 0u));
            CHECK(r32(m, obj + fcl::kNmObjOnInsert) == (cb ? f1 : 0x3C4400u));
            CHECK(r32(m, obj + fcl::kNmObjOnRemove) == (cb ? f2 : 0x3C4410u));
            CHECK(r32(m, obj + fcl::kNmObjFilter) == (cb ? f3 : 0x3C4420u));
            CHECK(r16(m, obj + fcl::kNmObjCount) == 0);
        }
    // remove / clear: an object with n nodes {key, -, size, prev, next, payload} built in kOut, the default callbacks
    const u32 obj = kOut, nodes = kOut + 0x100;
    auto build = [&](int n, int cursor) {
        zero(m, kOut, 0x1000);
        w32(m, obj + fcl::kNmObjOnInsert, 0x3C4400u);
        w32(m, obj + fcl::kNmObjOnRemove, 0x3C4410u);
        w32(m, obj + fcl::kNmObjFilter, 0x3C4420u);
        for (int i = 0; i < n; ++i) {
            const u32 nd = nodes + 0x40 * i;
            w32(m, nd + 0, i + 1);
            w32(m, nd + fcl::kNmNodeSize, 0x30);
            w32(m, nd + 12, i ? nd - 0x40 : 0);
            w32(m, nd + fcl::kNmNodeNext, i + 1 < n ? nd + 0x40 : 0);
            w32(m, nd + fcl::kNmNodePayload, nd + 24);
            w32(m, nd + 24, 0xC0DE0000u + i);
        }
        w32(m, obj + fcl::kNmObjHead, n ? nodes : 0);
        w32(m, obj + 8, n ? nodes + 0x40 * (n - 1) : 0);
        w32(m, obj + fcl::kNmObjCursor, cursor >= 0 ? nodes + 0x40 * cursor : 0);
        w16(m, obj + fcl::kNmObjCount, static_cast<u16>(n));
    };
    for (int n = 1; n <= 4; ++n)
        for (int victim = 0; victim < n; ++victim)
            for (const int cursor : {-1, victim, 0}) {
                build(n, cursor);
                const u32 nd = nodes + 0x40 * victim;
                const u32 next = r32(m, nd + fcl::kNmNodeNext);
                const hgp::Run r = fcl_pair(m, "sub_3C49E0", {sx(obj), sx(obj + 4), sx(nd), 0}, ++seed, "nmListRemove");
                CHECK(r16(m, obj + fcl::kNmObjCount) == n - 1);
                for (u32 i = 0; i < 0x30; i += 4) CHECK(r32(m, nd + i) == 0u);  // cleared before the free
                if (cursor == victim) CHECK(r32(m, obj + fcl::kNmObjCursor) == static_cast<u32>(v0_of(r)));
                if (next) CHECK(static_cast<u32>(v0_of(r)) == next);
                // the remaining chain from the head skips the victim
                int count = 0;
                for (u32 p = r32(m, obj + fcl::kNmObjHead); p && count < 8; p = r32(m, p + fcl::kNmNodeNext)) {
                    CHECK(p != nd);
                    ++count;
                }
                CHECK(count == n - 1);
            }
    for (int n = 0; n <= 4; ++n) {
        build(n, n ? 0 : -1);
        fcl_pair(m, "sub_3C4A90", {sx(obj), sx(obj + 4), 0, 0}, ++seed, "nmListClear");
        CHECK(r32(m, obj + fcl::kNmObjHead) == 0u);
        CHECK(r32(m, obj + 8) == 0u);
        CHECK(r32(m, obj + fcl::kNmObjCursor) == 0u);
        CHECK(r16(m, obj + fcl::kNmObjCount) == 0);
        for (int i = 0; i < n; ++i) CHECK(r32(m, nodes + 0x40 * i + fcl::kNmNodePayload) == 0u);
    }
    build(2, 0);
    fcl_pair(m, "sub_3C4A90", {0, sx(obj + 4), 0, 0}, ++seed, "nmListClear null object");
    CHECK(r16(m, obj + fcl::kNmObjCount) == 2);  // untouched
    fcl_pair(m, "sub_3C4A90", {sx(obj), 0, 0, 0}, ++seed, "nmListClear null list");
}

// =====================================================================================================================
// 3. MsgAssist on the snapshots' live work; a fresh MsgAssist task on the stand-ins
// =====================================================================================================================
TEST_CASE("game(fcl): MsgAssist on the snapshots (documented rules)") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    u32 seed = 2000;
    int seen = 0;
    for (const char* dir : kSnaps) {
        if (!restore(m, dir)) {
            MESSAGE("SKIP: extracted/_ours/" << dir << " not found");
            continue;
        }
        const u32 work = r32(m, fcl::kMsgAssistSlot);
        if (!work) continue;
        ++seen;
        const u32 reqs = r32(m, work + fcl::kMaRequests);
        const u32 slots = r32(m, work + fcl::kMaSlotList);
        // the leaf accessors
        for (const char* fn : {"sub_3C8D80", "sub_3C8EA0", "sub_3C8F20", "sub_3C8F40"}) {
            restore(m, dir);
            fcl_pair(m, fn, {0, 0, 0, 0}, ++seed, fn);
        }
        restore(m, dir);
        CHECK(v0_of(fcl_pair(m, "sub_3C8D80", {0, 0, 0, 0}, ++seed, "slots idle")) == (r32(m, slots + fcl::kNmObjHead) == 0 ? 1u : 0u));
        for (const u32 v : {0u, 1u, 0x80u, 0xFFFFFFFFu}) {
            restore(m, dir);
            const u32 before = r32(m, work + fcl::kMaMask);
            fcl_pair(m, "sub_3C8DA0", {sx(v), 0, 0, 0}, ++seed, "or mask");
            CHECK(r32(m, work + fcl::kMaMask) == (before | v));
            fcl_pair(m, "sub_3C8DC0", {sx(v), 0, 0, 0}, ++seed, "set mask");
            CHECK(r32(m, work + fcl::kMaMask) == v);
        }
        // requests: owner, append, find, count, purge
        restore(m, dir);
        fcl_pair(m, "sub_3C8DD0", {sx(0x1234560u), 0, 0, 0}, ++seed, "set owner");
        CHECK(r32(m, work + fcl::kMaOwner) == 0x1234560u);
        Opt keep;
        keep.persist = true;
        fresh_worlds();
        const u16 count0 = static_cast<u16>(r16(m, reqs + fcl::kNmObjCount));
        for (u32 k = 0; k < 5; ++k) {
            fcl_pair(m, "sub_3C8DE0", {k + 1, 10 * k, 100 * k, sx(static_cast<u32>(-static_cast<s32>(k)))}, ++seed, "request", keep);
            CHECK(r16(m, reqs + fcl::kNmObjCount) == count0 + k + 1);
            const u32 tail = r32(m, reqs + 8);
            const u32 pl = r32(m, tail + fcl::kNmNodePayload);
            CHECK(r32(m, pl + fcl::kMaReqNode) == tail);
            CHECK(r32(m, pl + fcl::kMaReqKey) == k + 1);
            CHECK(r32(m, pl + fcl::kMaReqA) == 10 * k);
            CHECK(r32(m, pl + fcl::kMaReqB) == 100 * k);
            CHECK(r32(m, pl + fcl::kMaReqOwner) == 0x1234560u);
            CHECK(r16(m, pl + fcl::kMaReqC) == -static_cast<s32>(k));
        }
        for (u32 k = 0; k < 7; ++k)
            for (const u32 a : {10 * k, 10 * k + 1}) {
                const bool want = k < 5 && a == 10 * k;
                CHECK(v0_of(fcl_pair(m, "sub_3C8EC0", {k + 1, a, 0, 0}, ++seed, "has request", keep)) == (want ? 1u : 0u));
            }
        CHECK(v0_of(fcl_pair(m, "sub_3C8EA0", {0, 0, 0, 0}, ++seed, "request count", keep)) == count0 + 5u);
        fcl_pair(m, "sub_3C8810", {sx(work), 0, 0, 0}, ++seed, "purge", keep);  // no request is flagged 2: all go
        CHECK(r16(m, reqs + fcl::kNmObjCount) == 0);
        // with no owner, the request path asserts (K_Assert continues in retail) and records 0
        restore(m, dir);
        w32(m, work + fcl::kMaOwner, 0);
        fcl_pair(m, "sub_3C8DE0", {9, 9, 9, 9}, ++seed, "request without owner");
        // slots: start / queue / stop / out of range
        restore(m, dir);
        for (u32 s = 0; s < 14; ++s) {
            const u32 slot = work + fcl::kMaSlots + fcl::kMaSlotSize * (s < 12 ? s : 0);
            const u16 before = static_cast<u16>(r16(m, slots + fcl::kNmObjCount));
            const bool running = s < 12 && (r32(m, slot + fcl::kMaSlotFlags) & 2u);
            const hgp::Run r = fcl_pair(m, "sub_3C8400", {sx(work), s, 0, 0}, ++seed, "slot start", keep);
            if (s < 12) {
                CHECK(v0_of(r) == (running ? 0u : 1u));
                if (!running) {
                    CHECK(r16(m, slots + fcl::kNmObjCount) == before + 1);
                    CHECK(r32(m, slot + fcl::kMaSlotIndex) == s);
                    CHECK(v0_of(fcl_pair(m, "sub_3C8400", {sx(work), s, 0, 0}, ++seed, "slot start again", keep)) == 0u);
                }
            }
            if (s < 12) {
                fcl_pair(m, "sub_3C8770", {sx(work), s, 0, 0}, ++seed, "slot stop", keep);
                CHECK((r32(m, slot + fcl::kMaSlotFlags) & 4u) != 0u);
            }
        }
        fcl_pair(m, "sub_3C8810", {sx(work), 0, 0, 0}, ++seed, "purge slots", keep);
        fcl_pair(m, "sub_3C8F40", {0, 0, 0, 0}, ++seed, "purge all", keep);
        // a fresh MsgAssist task (heap and task kernel on the stand-ins)
        restore(m, dir);
        fresh_worlds();
        const hgp::Run c = fcl_pair(m, "fclMisc_CreateMsgAssistTask", {0, 0, 0, 0}, ++seed, "create MsgAssist", keep);
        const u32 nw = r32(m, fcl::kMsgAssistSlot);
        CHECK(nw != work);
        CHECK(nw >= kStandInHeap);
        CHECK(r32(m, nw + fcl::kMaFlags) == 1u);
        CHECK(r32(m, nw + fcl::kMaSlotList) >= kStandInHeap);
        CHECK(r32(m, nw + fcl::kMaRequests) + fcl::kNmObjHeaderSize == nw);  // the work is its own object's payload
        CHECK(r32(m, fcl::kMsgRecord) == 0xFFFFFFFFu);
        CHECK(r32(m, fcl::kMsgRecord + 8) == 0xFFFFFFFFu);
        CHECK(r8(m, fcl::kMsgRecord + 12) == 1);
        CHECK(v0_of(c) != 0u);  // the task
        fcl_pair(m, "sub_3C8D80", {0, 0, 0, 0}, ++seed, "fresh slots idle", keep);
        fcl_pair(m, "sub_3C8400", {sx(nw), 3, 0, 0}, ++seed, "fresh slot", keep);
    }
    MESSAGE("MsgAssist: " << seen << " snapshots, " << g_pairs << " pairs so far");
}

// =====================================================================================================================
// 4. The facility message window, the font-tag window placement, the persona status and the persona model
// =====================================================================================================================
TEST_CASE("game(fcl): message window, persona status and persona model (documented rules)") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    u32 seed = 3000;
    const char* dir = "fusion_vr_5000";
    if (!restore(m, dir)) {
        MESSAGE("SKIP: extracted/_ours/" << dir << " not found");
        return;
    }
    const std::vector<u8> base(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    auto reset = [&] { std::memcpy(m.mem.main_ram(), base.data(), base.size()); };
    // the message window record (handle, state, hidden) in every combination; selection words from the recorders
    for (const u32 handle : {0xFFFFFFFFu, 0u, 0x12u})
        for (u8 st = 0; st < 3; ++st)
            for (u8 hid = 0; hid < 2; ++hid)
                for (const u64 sel : {sx(0xFFFFFFFFu), u64{0}, u64{2}}) {
                    reset();
                    w32(m, fcl::kMsgWin, handle);
                    w8(m, fcl::kMsgWin + fcl::kMsgWinState, st);
                    w8(m, fcl::kMsgWin + fcl::kMsgWinHidden, hid);
                    const Opt o{{}, {}, true, false, recorders({{0x3A2750u, sel}, {0x3A2830u, 5}})};
                    const hgp::Run s = fcl_pair(m, "sub_3C9340", {sx(fcl::kMsgWin), 0, 0, 0}, ++seed, "msgWin state", o);
                    const s32 want = static_cast<s32>(handle) < 0 ? 0 : (hid && st == 2) ? 0 : st;
                    CHECK(v0s(s) == want);
                    CHECK(v0_of(fcl_pair(m, "sub_3C7D50", {0, 0, 0, 0}, ++seed, "msgWin get", o)) == fcl::kMsgWin);
                    fcl_pair(m, "sub_3C78D0", {0, 0, 0, 0}, ++seed, "msgWin poll", o);

                }
    // the font-tag window placement: the tag parameters from recorders (-1 = default), both branches
    for (const u64 p2 : {sx(0xFFFFFFFFu), u64{200}})
        for (const u64 p3 : {u64{0}, u64{1}, u64{2}})
            for (const u64 p01 : {sx(0xFFFFFFFFu), u64{40}}) {
                reset();
                const Opt o{{}, {}, true, false,
                            recorders({{0x3AF380u, p2}, {0x3AF390u, p3}, {0x3AF360u, p01}, {0x3AF370u, p01}})};
                fcl_pair(m, "sub_3C9570", {sx(r32(m, fcl::kMsgWin)), 0, 0, 0}, ++seed, "window placement", o);
            }
    // the persona status accessors on a status work behind a hand-made task record (+0x3C = the work)
    const u32 task = kOut, work = kOut + 0x100;
    auto ps = [&](std::mt19937& rng) {
        reset();
        zero(m, kOut, 0x400);
        w32(m, task + 0x3C, work);
        for (u32 i = 0; i < 240; i += 4) w32(m, work + i, rng() % 3 ? rng() % 64 : rng());
    };
    std::mt19937 rng{77};
    const u32 rec = kOut + 0xA00;  // a 84-byte source record (outside the area ps() clears)
    for (u32 i = 0; i < 84; ++i) w8(m, rec + i, static_cast<u8>(i * 7));
    for (int it = 0; it < 24; ++it) {
        ps(rng);
        for (u32 i = 0; i < 84; ++i) w8(m, rec + i, static_cast<u8>(i * 7 + it));
        fcl_pair(m, "sub_3C9B00", {sx(task), it % 2 ? sx(rec) : 0, it % 3 ? sx(rec) : 0, 0}, ++seed, "psStatus set persona");
        if (it % 2) CHECK(std::memcmp(m.at(work + fcl::kPsPersona), m.at(rec), 52) == 0);
        ps(rng);
        fcl_pair(m, "sub_3C9BA0", {sx(task), sx(rec), 0, 0}, ++seed, "psStatus set record");
        ps(rng);
        const u32 flags0 = r32(m, work + fcl::kPsState);
        const s16 scroll0 = r16(m, work + fcl::kPsScroll);
        fcl_pair(m, "sub_3C9C10", {sx(task), sx(rec), sx(rec + 4), 0}, ++seed, "psStatus compare");
        CHECK((r32(m, work + fcl::kPsState) & 0x40u) != 0u);
        if (!(flags0 & 0x40u))
            CHECK(r16(m, work + fcl::kPsScroll) ==
                  static_cast<s16>(static_cast<s8>(r8(m, work + fcl::kPsPage)) * r16(m, work + fcl::kPsPageHeight)));
        else
            CHECK(r16(m, work + fcl::kPsScroll) == scroll0);
        const u32 v = rng() % 3 ? rng() % 8 : 0;
        ps(rng);
        fcl_pair(m, "sub_3C9CD0", {sx(task), v, 0, 0}, ++seed, "psStatus +24");
        CHECK(r32(m, work + fcl::kPsWord24) == v);
        fcl_pair(m, "sub_3C9D80", {sx(task), u64{1} << (it % 8), 0, 0}, ++seed, "psStatus state off");
        CHECK((r32(m, work + fcl::kPsState) & (1u << (it % 8))) == 0u);
        fcl_pair(m, "sub_3C9E00", {sx(task), v, 0, 0}, ++seed, "psStatus +234");
        const u8 count = static_cast<u8>(rng() % 6), page = static_cast<u8>(rng() % 9) - 2;
        fcl_pair(m, "sub_3C9E30", {sx(task), count, page, 0}, ++seed, "psStatus pages");
        CHECK(r8(m, work + fcl::kPsPageCount) == count);
        for (const s32 p : {-3, -1, 0, 1, 2, 5, 9}) {
            fcl_pair(m, "sub_3C9E70", {sx(task), sx(static_cast<u32>(p)), 0, 0}, ++seed, "psStatus set page");
            const s32 want = p < 0 ? 0 : (p >= static_cast<s8>(count) ? static_cast<s8>(count) - 1 : p);
            CHECK(static_cast<s8>(r8(m, work + fcl::kPsPage)) == static_cast<s8>(want));
            CHECK(static_cast<s8>(v0_of(fcl_pair(m, "sub_3C9EE0", {sx(task), 0, 0, 0}, ++seed, "psStatus get page"))) ==
                  static_cast<s8>(want));
        }
        fcl_pair(m, "sub_3C9F10", {sx(task), v, 0, 0}, ++seed, "psStatus speed A");
        CHECK(r16(m, work + fcl::kPsSpeedA) == static_cast<s16>(v ? v : 1));
        fcl_pair(m, "sub_3C9F60", {sx(task), v, 0, 0}, ++seed, "psStatus speed B");
        CHECK(r16(m, work + fcl::kPsSpeedB) == static_cast<s16>(v ? v : 1));
        fcl_pair(m, "sub_3C9FB0", {sx(task), 0, 0, 0}, ++seed, "psStatus page height");
        CHECK(r16(m, work + fcl::kPsPageHeight) == 15);
        // the draw tasks: the drawers (+224 / +228) are recorders at two not-emitted psStatus drawers
        for (u32 vis = 0; vis < 2; ++vis)
            for (u32 id = 0; id < 2; ++id) {
                ps(rng);
                w32(m, work + fcl::kPsState, vis);
                w16(m, work + fcl::kPsPersonaId, static_cast<u16>(id * 46));
                w32(m, work + fcl::kPsDrawLow, 0x3CB050u);
                w32(m, work + fcl::kPsDrawHigh, 0x3CB100u);
                const Opt o{{}, {}, true, false, recorders({{0x3CB050u, 0}, {0x3CB100u, 0}})};
                fcl_pair(m, "fclMisc_UpdatePsStatusDrawLowTask", {sx(task), 0, 0, 0}, ++seed, "psStatus draw low", o);
                CHECK(g_t.world[1]->si.calls_to(0x3CB050u) == (vis && id ? 1u : 0u));
                fcl_pair(m, "fclMisc_UpdatePsStatusDrawHighTask", {sx(task), 0, 0, 0}, ++seed, "psStatus draw high", o);
                CHECK(g_t.world[1]->si.calls_to(0x3CB100u) == (vis && id ? 1u : 0u));
            }
    }
    // the persona model: created on the stand-ins (g_data colours live in the snapshot), then every accessor
    reset();
    fresh_worlds();
    Opt keep{{}, {}, true, true, recorders()};
    const hgp::Run c = fcl_pair(m, "sub_3CDA60", {0, 0, 0, 0}, ++seed, "psModel create", keep);
    const u32 pmtask = static_cast<u32>(v0_of(c));
    REQUIRE(pmtask != 0u);
    const u32 pm = r32(m, pmtask + 0x3C);
    CHECK(r32(m, pm + fcl::kPmState) == 1u);
    CHECK(r16(m, pm + fcl::kPmPersona) == 0);
    CHECK(r32(m, pm + fcl::kPmColour) == r32(m, 0x7CD718u));
    {
        // colour A / B = the g_data colours of persona 0 (table 0, entry 0), byte / 255
        const u32 tab = r32(m, r32(m, 0x7CDFB0u) + 8);
        for (int k = 0; k < 2; ++k) {
            const u32 word = r32(m, tab + 20 + 4 * k);
            const u32 dst = pm + (k ? fcl::kPmColourB : fcl::kPmColourA);
            CHECK(rf(m, dst) == static_cast<float>((word >> 24) & 0xFF) / 255.0f);
            CHECK(rf(m, dst + 12) == static_cast<float>(word & 0xFF) / 255.0f);
        }
    }
    for (const char* fn : {"sub_3CDC80", "sub_3CDD80"}) fcl_pair(m, fn, {sx(pmtask), 0, 0, 0}, ++seed, fn, keep);
    fcl_pair(m, "sub_3CDCD0", {sx(pmtask), 1, 2, 3}, ++seed, "psModel anim (not ready)", keep);
    for (const u32 f : {1u, 4u, 0x80u}) {
        fcl_pair(m, "sub_3CDE00", {sx(pmtask), f, 0, 0}, ++seed, "psModel flags on", keep);
        CHECK((r32(m, pm + fcl::kPmFlags) & (f << 16)) == (f << 16));
        fcl_pair(m, "sub_3CDE70", {sx(pmtask), f, 0, 0}, ++seed, "psModel flags off", keep);
        CHECK((r32(m, pm + fcl::kPmFlags) & (f << 16)) == 0u);
    }
    fcl_pair(m, "sub_3CDEE0", {sx(pmtask), 0x1234, 0, 0}, ++seed, "psModel word0", keep);
    CHECK(static_cast<u16>(r16(m, pm + fcl::kPmWord0)) == 0x1234u);
    // set persona: not ready -> queued; ready -> reload (state 2) or destroy (id 0)
    fcl_pair(m, "sub_3CDBA0", {sx(pmtask), 46, 0, 0}, ++seed, "psModel persona (not ready)", keep);
    CHECK(r16(m, pm + fcl::kPmPending) == 46);
    w32(m, pm + fcl::kPmFlags, r32(m, pm + fcl::kPmFlags) | 1u);
    w32(m, pm + fcl::kPmModel, kOut + 0x800);
    zero(m, kOut + 0x800, 0x100);
    fcl_pair(m, "sub_3CDCD0", {sx(pmtask), 1, 2, 3}, ++seed, "psModel anim (ready)", keep);
    w8(m, kOut + 0x800 + fcl::kModelAnimState, 1);
    CHECK(v0_of(fcl_pair(m, "sub_3CDD80", {sx(pmtask), 0, 0, 0}, ++seed, "psModel anim done", keep)) == 1u);
    CHECK(v0_of(fcl_pair(m, "sub_3CDBA0", {sx(pmtask), 46, 0, 0}, ++seed, "psModel persona (ready)", keep)) == 1u);
    CHECK(r32(m, pm + fcl::kPmState) == 2u);
    CHECK((r32(m, pm + fcl::kPmFlags) & 1u) == 0u);
    CHECK(v0_of(fcl_pair(m, "sub_3CDBA0", {sx(pmtask), 46, 0, 0}, ++seed, "psModel same persona", keep)) == 0u);
    w32(m, pm + fcl::kPmFlags, r32(m, pm + fcl::kPmFlags) | 1u);
    CHECK(v0_of(fcl_pair(m, "sub_3CDBA0", {sx(pmtask), 0, 0, 0}, ++seed, "psModel persona 0", keep)) == 1u);
    CHECK(r32(m, pm + fcl::kPmModel) == 0u);  // destroyed (sub_3174E0)
    // fades: with frames the target / start pair, without frames the colour at once
    const u32 src = kOut + 0x900;
    for (u32 i = 0; i < 16; ++i) w8(m, src + i, static_cast<u8>(0x10 * i + 3));
    for (const u32 frames : {0u, 12u}) {
        const u32 old = r32(m, pm + fcl::kPmColour);
        fcl_pair(m, "sub_3CDF40", {sx(pmtask), sx(src), frames, 0}, ++seed, "psModel fade", keep);
        CHECK(r32(m, pm + fcl::kPmFadeTarget) == r32(m, src));
        CHECK(r32(m, pm + fcl::kPmFadeStart) == (frames ? old : r32(m, src)));
        CHECK(r32(m, pm + fcl::kPmColour) == (frames ? old : r32(m, src)));
        CHECK(static_cast<u16>(r16(m, pm + fcl::kPmFadeFrames)) == frames);
        for (const char* fn : {"sub_3CE060", "sub_3CE180"}) {
            for (u32 i = 0; i < 4; ++i) wf(m, src + 4 * i, 0.25f * static_cast<float>(i + frames));
            fcl_pair(m, fn, {sx(pmtask), sx(src), frames, 0}, ++seed, fn, keep);
        }
        CHECK(rf(m, pm + fcl::kPmFadeATarget + 4) == rf(m, src + 4));
        if (!frames) CHECK(rf(m, pm + fcl::kPmColourB + 8) == rf(m, src + 8));
    }
    // the g_data lookups directly, every table / entry of the first tables, and the small helpers
    reset();
    for (u32 t = 0; t < 2; ++t)  // the fusion snapshot's colour set has two tables
        for (u32 e = 0; e < 8; ++e)
            for (const char* fn : {"sub_16BC80", "sub_16BDB0"}) {
                fcl_pair(m, fn, {t, e, sx(kOut), 0}, ++seed, fn);
                const u32 word = r32(m, r32(m, r32(m, 0x7CDFB0u) + 16 * t + 8) + 32 * e + (fn[7] == 'C' ? 20 : 24));
                CHECK(rf(m, kOut + 4) == static_cast<float>((word >> 16) & 0xFF) / 255.0f);
            }
    w32(m, 0x7CDFB0u, 0);  // no colour set: K_Assert (continues) and reads through null, alike
    fcl_pair(m, "sub_16BC80", {0, 0, sx(kOut), 0}, ++seed, "g_data not loaded");
    for (u32 i = 0; i < 8; ++i) {
        fcl_pair(m, "sub_3C7D60", {i, 0, 0, 0}, ++seed, "table word");
        wf(m, kOut + 0x40, 1.5f * i);
        wf(m, kOut + 0x44, -2.0f);
        wf(m, kOut + 0x48, 3.25f);
        fcl_pair(m, "sub_20D650", {sx(kOut), sx(kOut + 0x40), 0, 0}, ++seed, "frame translation");
        CHECK(rf(m, kOut + 32) == 1.5f * i);
        CHECK(rf(m, kOut + 40) == 3.25f);
    }
    fcl_pair(m, "sub_3C9840", {0, 0, 0, 0}, ++seed, "return 0");
    for (const char* fn : {"nullsub_122", "nullsub_123", "nullsub_124", "nullsub_67", "sub_4110E0"})
        fcl_pair(m, fn, {1, 2, 3, 4}, ++seed, fn);
}

// =====================================================================================================================
// 5. The bank manager's slots on the snapshots (documented rules)
// =====================================================================================================================
TEST_CASE("game(fcl): bank manager slots (documented rules)") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    u32 seed = 4000;
    for (const char* dir : kSnaps) {
        if (!restore(m, dir)) continue;
        const u32 mgr = r32(m, fcl::kBankSlot);
        if (!mgr) continue;
        const u32 slots = r32(m, mgr + fcl::kBankSlots) + 4;
        std::vector<u32> banks = {0, 1, 7, 0xFFFFFFFFu};
        for (int i = 0; i < 3; ++i) banks.push_back(r32(m, slots + fcl::kBankSlotStride * i + fcl::kBankSlotBank));
        // the flag patterns: active / loading / playing / stopped / group on each slot
        const u16 pats[] = {0, 1, 3, 9, 0xD, 0x109, 0x10D, 0x401};
        for (int p = 0; p < 8; ++p) {
            restore(m, dir);
            for (int i = 0; i < 3; ++i) w16(m, slots + fcl::kBankSlotStride * i, pats[(p + 3 * i) % 8]);
            const std::vector<u8> base(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
            for (const u32 b : banks) {
                const hgp::Run r = fcl_pair(m, "sub_3CF8F0", {sx(b), 0, 0, 0}, ++seed, "bank find");
                s32 want = -1;
                for (int i = 0; i < 3 && want < 0; ++i)
                    if ((static_cast<u16>(r16(m, slots + fcl::kBankSlotStride * i)) & 1u) &&
                        r32(m, slots + fcl::kBankSlotStride * i + fcl::kBankSlotBank) == b)
                        want = i;
                CHECK(v0s(r) == want);
                std::memcpy(m.mem.main_ram(), base.data(), base.size());
                const hgp::Run q = fcl_pair(m, "sub_3CF960", {sx(b), 0x5500, 0, 0}, ++seed, "bank request");
                if (want >= 0) {
                    CHECK(v0_of(q) == 0u);
                    CHECK((static_cast<u16>(r16(m, slots + fcl::kBankSlotStride * want)) & 0xFF00u) == 0x5500u);
                } else {
                    const u32 node = static_cast<u32>(v0_of(q));
                    REQUIRE(node != 0u);
                    const u32 pl = r32(m, node + fcl::kNmNodePayload);
                    CHECK(r32(m, pl + fcl::kBankSlotBank) == b);
                    CHECK(static_cast<u16>(r16(m, pl)) == 0x5503u);
                }
                std::memcpy(m.mem.main_ram(), base.data(), base.size());
            }
            for (const u32 flag5145 : {0u, 1u}) {
                std::memcpy(m.mem.main_ram(), base.data(), base.size());
                const Opt o{{}, {}, true, false, recorders({{0x16F190u, flag5145}})};
                fcl_pair(m, "sub_3CF520", {0, 0, 0, 0}, ++seed, "bank mark blocked", o);
            }
            for (int i = 0; i < 3; ++i) {
                std::memcpy(m.mem.main_ram(), base.data(), base.size());
                const hgp::Run r = fcl_pair(m, "sub_3CFAC0", {sx(slots + fcl::kBankSlotStride * i), 0, 0, 0}, ++seed, "bank conflict");
                // documented rule: 1 unless another active playing slot of the same group is not stopped
                const u16 me = static_cast<u16>(base[slots + fcl::kBankSlotStride * i] | base[slots + fcl::kBankSlotStride * i + 1] << 8);
                u64 want = 1;
                for (int j = 0; j < 3; ++j) {
                    if (j == i) continue;
                    const u32 sj = slots + fcl::kBankSlotStride * j;
                    const u16 f = static_cast<u16>(base[sj] | base[sj + 1] << 8);
                    if ((f & 1) && (f & 8) && (f & 0x100) == (me & 0x100) && !((f | 0x400) & 4)) want = 0;
                }
                CHECK(v0_of(r) == want);
            }
        }
    }
}

// =====================================================================================================================
// 6. The background element handlers: the shop snapshot's live elements, then every handler on its own area with its
//    start / end events over many frames (state persists from pair to pair), its draw handler each frame
// =====================================================================================================================
namespace {
struct BgCase {
    const char* handler;
    const char* draw;              // 0: none
    std::vector<u16> start_events;  // each a run: start, 60 frames, end event, 60 frames
    u16 end_event;
    bool ends_with_2;              // documented: the end event makes the handler return 2 within the run
};
}  // namespace

TEST_CASE("game(fcl): background element handlers over frames (documented rules)") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    u32 seed = 5000;
    const char* dir = "shop_ref_4100";
    if (!restore(m, dir)) {
        MESSAGE("SKIP: extracted/_ours/" << dir << " not found");
        return;
    }
    // a facility sprite bank (gp slot 0x7CE6A0, shops.h) with 256 sprites over four files: the shop's own bank has
    // fewer sprites than the ids these handlers draw (its tables end before them)
    {
        const u32 bank = kOut + 0x2000, handles = bank + 0x40, sprites = bank + 0x100, files = bank + 0x900;
        zero(m, bank, 0x1000);
        // the four sprite files: zeroed 0x100-byte records (sprCreateHandle, hand-written since slice unblock, puts the
        // file pointer into the handle that the draw sub_1127D0 reads; the old placeholders 0x100 + f were not records)
        for (u32 f = 0; f < 4; ++f) w32(m, handles + 4 * f, files + 0x100 * f);
        for (u32 i = 0; i < 256; ++i) {
            w8(m, sprites + 8 * i, static_cast<u8>(i % 4));
            w16(m, sprites + 8 * i + 2, static_cast<u16>(i));
            w16(m, sprites + 8 * i + 4, static_cast<u16>(i % 7));
            w16(m, sprites + 8 * i + 6, static_cast<u16>(i % 5));
        }
        w32(m, bank, 4);
        w32(m, bank + 8, handles);
        w32(m, bank + 12, sprites);
        w32(m, 0x7CE6A0u, bank);
    }
    const std::vector<u8> base(m.mem.main_ram(), m.mem.main_ram() + EEMemory::kMainRamSize);
    auto reset = [&] { std::memcpy(m.mem.main_ram(), base.data(), base.size()); };
    const u32 mgr = 0x1544318u;  // the shop's background manager (its +8 list holds the elements)
    const Opt draw_o{{}, {}, true, false, recorders()};
    // (a) the live elements: walk the manager's list; handlers / draws of this slice run on their real areas
    {
        int live = 0;
        const u32 obj = r32(m, mgr + 8);
        for (u32 node = obj ? r32(m, obj + fcl::kNmObjHead) : 0, k = 0; node && k < 64; node = r32(m, node + fcl::kNmNodeNext), ++k) {
            const u32 pl = r32(m, node + fcl::kNmNodePayload);
            const u32 entry = r32(m, pl + 8);
            for (const u32 fn : {r32(m, entry), r32(m, entry + 4)})
                for (const Case& c : kCases)
                    if (c.addr == fn) {
                        ++live;
                        for (int f = 0; f < 4; ++f) fcl_pair(m, c.name, {sx(mgr), sx(pl), 0, 0}, ++seed, "live element", draw_o);
                    }
        }
        CHECK(live >= 2);  // sub_40F030 / sub_40F430 (curtains) and sub_4120A0 (slides)
        MESSAGE("live background elements of this slice: " << live << " handler / draw entries");
    }
    // (b) every handler on its own area
    const u32 pl = kOut, area = kOut + 0x100, ev = kOut + 0x80;
    const BgCase cases[] = {
        {"sub_40F030", "sub_40F430", {1}, 4, true},       {"sub_40F5D0", "sub_40FAB0", {1}, 4, true},
        {"sub_40FB90", "sub_4101B0", {5, 6, 7}, 4, true}, {"sub_4105E0", "sub_410A10", {1, 5, 6}, 4, true},
        {"sub_4113F0", "sub_411710", {1}, 4, true},       {"sub_411790", nullptr, {5, 6, 7}, 10, false},
        {"sub_4120A0", nullptr, {1}, 4, true},            {"sub_412610", "sub_412AF0", {1}, 4, true},
        {"sub_412BC0", "sub_413010", {1, 5}, 4, true},    {"sub_4131A0", "sub_413680", {1}, 4, true},
        {"sub_4138E0", "sub_413B10", {5}, 10, true},      {"sub_414FE0", "sub_414E10", {5, 7, 9, 10, 12}, 11, false},
    };
    int ends = 0;
    for (const BgCase& bc : cases)
        for (const u16 start : bc.start_events) {
            reset();
            zero(m, kOut, 0x400);
            w32(m, pl + 8, 0x6B0724u);  // any entry: the handlers only read their area
            w32(m, pl + fcl::kBgNodeArea, area);
            fresh_worlds();
            Opt o{{}, {}, true, true, recorders()};
            std::vector<s32> rets;
            auto frame = [&](u16 event) {
                w16(m, ev + fcl::kBgEventId, event);
                rets.push_back(v0s(fcl_pair(m, bc.handler, {sx(mgr), sx(pl), event ? sx(ev) : 0, 0}, ++seed, bc.handler, o)));
                if (bc.draw) fcl_pair(m, bc.draw, {sx(mgr), sx(pl), 0, 0}, ++seed, bc.draw, o);
            };
            frame(start);
            for (int f = 0; f < 60; ++f) frame(0);
            const std::size_t mark = rets.size();
            frame(bc.end_event);
            for (int f = 0; f < 60; ++f) frame(0);
            bool two = false;
            for (std::size_t i = mark; i < rets.size(); ++i) two |= rets[i] == 2;
            if (bc.ends_with_2) {
                CHECK(two);
                ends += two;
            }
            for (const s32 v : rets) CHECK((v >= 0 && v <= 2));  // the handler protocol: 0 moving, 1 idle, 2 finished
        }
    MESSAGE("background handlers: " << ends << " end events seen finishing");
    // documented rules on the fade (sub_4138E0): event 5 -> 8 frames to alpha 255 (state 1); event 10 -> returns 2
    // on its 6th frame with alpha 0
    {
        reset();
        zero(m, kOut, 0x400);
        w32(m, pl + fcl::kBgNodeArea, area);
        fresh_worlds();
        Opt o{{}, {}, true, true, recorders()};
        w16(m, ev + fcl::kBgEventId, 5);
        fcl_pair(m, "sub_4138E0", {sx(mgr), sx(pl), sx(ev), 0}, ++seed, "fade in", o);
        for (int f = 1; f < 8; ++f) fcl_pair(m, "sub_4138E0", {sx(mgr), sx(pl), 0, 0}, ++seed, "fade in", o);
        CHECK(r16(m, area + 8) == 255);
        CHECK(r16(m, area) == 1);
        w16(m, ev + fcl::kBgEventId, 10);
        s32 last = 0;
        int n = 0;
        last = v0s(fcl_pair(m, "sub_4138E0", {sx(mgr), sx(pl), sx(ev), 0}, ++seed, "fade out", o));
        while (last != 2 && n < 20) {
            last = v0s(fcl_pair(m, "sub_4138E0", {sx(mgr), sx(pl), 0, 0}, ++seed, "fade out", o));
            ++n;
        }
        CHECK(last == 2);
        CHECK(n == 5);
        CHECK(r16(m, area + 8) == 0);
    }
    // documented rule on the slides (sub_40F5D0): once idle the five keys sit on the in-table's targets (0x6AF9F0 + 60)
    {
        reset();
        zero(m, kOut, 0x400);
        w32(m, pl + fcl::kBgNodeArea, area);
        fresh_worlds();
        Opt o{{}, {}, true, true, recorders()};
        w16(m, ev + fcl::kBgEventId, 1);
        s32 v = v0s(fcl_pair(m, "sub_40F5D0", {sx(mgr), sx(pl), sx(ev), 0}, ++seed, "slide in", o));
        for (int f = 0; f < 200 && v != 1; ++f) v = v0s(fcl_pair(m, "sub_40F5D0", {sx(mgr), sx(pl), 0, 0}, ++seed, "slide in", o));
        CHECK(v == 1);
        for (u32 i = 0; i < 5; ++i) {
            CHECK(r16(m, area + 12 * i) == r16(m, 0x6AF9F0u + 60 + 12 * i));
            CHECK(r16(m, area + 12 * i + 2) == r16(m, 0x6AF9F0u + 62 + 12 * i));
        }
    }
    // the dispatchers and their part sub-handlers, every part set
    for (const char* disp : {"sub_414E10", "sub_415C30", "sub_417030"})
        for (u32 set = 0; set < 10; ++set) {
            reset();
            zero(m, kOut, 0x400);
            w32(m, pl + fcl::kBgNodeArea, area);
            w32(m, area + 152, set);
            w32(m, area + 76, set % 2);  // sub_417030: one part list (+76 / 2 == 0; larger values read past its table)
            for (u32 i = 0; i < 6; ++i) {
                w16(m, area + 12 * i, static_cast<u16>(20 * i));
                w16(m, area + 12 * i + 2, static_cast<u16>(10 * i));
                w16(m, area + 12 * i + 4, static_cast<u16>(40 * i));
            }
            fcl_pair(m, disp, {sx(mgr), sx(pl), 0, 0}, ++seed, disp, draw_o);
        }
    for (const char* part : {"sub_414100", "sub_4141E0", "sub_414280", "sub_414320", "sub_414500", "sub_4145F0", "sub_4146B0",
                             "sub_4148B0", "sub_414950", "sub_4149F0", "sub_414AD0", "sub_414BD0", "sub_414C70", "sub_414D70",
                             "sub_4154E0", "sub_415650", "sub_4157C0", "sub_415880", "sub_415A70", "sub_415B30", "sub_415B70",
                             "sub_4167D0", "sub_416D20"})
        for (const u32 alpha : {0u, 128u, 255u}) {
            reset();
            zero(m, kOut, 0x400);
            w32(m, pl + fcl::kBgNodeArea, area);
            w8(m, area + 188 + 2, static_cast<u8>(4 + alpha % 9));  // the date panel's month / day
            w8(m, area + 188 + 3, static_cast<u8>(1 + alpha % 28));
            w8(m, area + 80 + 4, alpha == 128 ? 13 : 2);           // the status panel's records
            w16(m, area + 80 + 16, 123);
            w16(m, area + 160 + 18, 45);
            const Opt o{{{GPR_T0, 0}, {GPR_T0 + 1, alpha}}, {}, true, false, recorders()};
            fcl_pair(m, part, {sx(mgr), sx(pl), 100, 60}, ++seed, part, o);
        }
    // the fan drawer: both render-state paths, a few angles; the digit / number wrappers and the element-set walk
    for (const u64 states : {u64{0}, u64{1}})
        for (int k = 0; k < 4; ++k) {
            reset();
            const float a = 0.5f * k;
            u32 b0, b1;
            std::memcpy(&b0, &a, 4);
            const float d = 0.25f;
            std::memcpy(&b1, &d, 4);
            const Opt o{{{GPR_T0, 30}, {GPR_T0 + 1, 0x80FF4020u}, {GPR_T0 + 3, states}}, {{12, b1}, {13, b0}, {14, b0 + 1}, {15, b0 + 2}},
                        true, false, recorders()};
            fcl_pair(m, "sub_40DCC0", {320, 224, 50, 80}, ++seed, "fan", o);
        }
    for (u32 size = 0; size < 5; ++size) {
        reset();
        fcl_pair(m, "sub_40EBC0", {100, 50, 255, size}, ++seed, "digits", draw_o);
    }
    reset();
    fcl_pair(m, "sub_40D5B0", {100, 50, 255, 1}, ++seed, "number tail", draw_o);
    {
        reset();
        // sub_40D3B0: the element set of manager +36 -> +68 -> +8 (fabricated chain to an empty set)
        zero(m, kOut, 0x400);
        w32(m, kOut + 36, kOut + 0x40);
        w32(m, kOut + 0x40 + 68, kOut + 0x80);
        w32(m, kOut + 0x80 + 8, 0);
        fcl_pair(m, "sub_40D3B0", {1, 2, 3, sx(kOut)}, ++seed, "element walk", draw_o);
    }
}

// =====================================================================================================================
// 7. The fusion cut-in: created on the fusion snapshot (heap / task kernel stand-ins), a script request taken, the
//    resource list built, the command runner run over its script frames, the handlers on their own, the destroy
// =====================================================================================================================
TEST_CASE("game(fcl): the fusion cut-in task and its command runner (documented rules)") {
    auto mp = elf_machine();
    if (!mp) return;
    Machine& m = *mp;
    u32 seed = 6000;
    const char* dir = "fusion_vr_5000";
    if (!restore(m, dir)) {
        MESSAGE("SKIP: extracted/_ours/" << dir << " not found");
        return;
    }
    // the command handlers of table 0x6B30A0 this library does not emit: recorders returning 1 (done)
    std::vector<std::pair<u32, u64>> handlers;
    for (u32 i = 0; i < 29; ++i) {
        const u32 h = r32(m, fcl::kCeHandlerTable + 4 * i);
        bool mine = false;
        for (const Case& k : kCases) mine |= k.addr == h;
        if (h && !mine) handlers.emplace_back(h, 1);
    }
    // and the rest of fclCombineEffect.c this slice leaves recompiled (the loader, the 3D / scene / voice commands)
    for (const u32 va : {0x4178C0u, 0x418230u, 0x418390u, 0x418510u, 0x418880u, 0x418C10u, 0x418C70u, 0x419050u, 0x4195F0u, 0x419730u,
                         0x419790u, 0x4198F0u, 0x419A30u, 0x419A70u, 0x419B80u, 0x419F20u, 0x41A310u, 0x41A3F0u, 0x41A730u, 0x41ABC0u,
                         0x41AE20u, 0x41AFF0u, 0x41B810u, 0x41B950u})
        handlers.emplace_back(va, 1);
    fresh_worlds();
    Opt keep{{}, {}, true, true, recorders(handlers)};
    const u32 params = kOut;
    for (u32 i = 0; i < 24; ++i) w8(m, params + i, static_cast<u8>(i + 1));
    const hgp::Run c = fcl_pair(m, "fclCmbEff_CreateCmbEffCalcTasks", {sx(params), 0, 0, 0}, ++seed, "cut-in create", keep);
    const u32 calc = static_cast<u32>(v0_of(c));
    REQUIRE(calc != 0u);
    const u32 work = r32(m, calc + 0x3C);
    REQUIRE(work != 0u);
    CHECK(std::memcmp(m.at(work + fcl::kCeParams), m.at(params), 24) == 0);
    for (const s32 off : {fcl::kCeDrawTask, fcl::kCeDraw3DTask, fcl::kCeDraw2DTask, fcl::kCeDrawSPTask, fcl::kCePsModel, fcl::kCeRunner,
                          fcl::kCeRequests})
        CHECK(r32(m, work + off) != 0u);
    CHECK((r32(m, work + fcl::kCeFlags) & 2u) != 0u);  // loading
    CHECK(r32(m, work + fcl::kCeCamera) == r32(m, r32(m, 0x7CE0C0u) + 4));
    CHECK(v0_of(fcl_pair(m, "sub_4173E0", {sx(calc), 0, 0, 0}, ++seed, "psModel task", keep)) == r32(m, work + fcl::kCePsModel));
    CHECK(v0_of(fcl_pair(m, "sub_417380", {sx(calc), 0, 0, 0}, ++seed, "busy (loading)", keep)) == 1u);
    CHECK(v0_of(fcl_pair(m, "sub_41B530", {sx(work), 0, 0, 0}, ++seed, "no request", keep)) == 0u);
    // the script table 0x6B2AA0: {commands, count} entries; request the first few
    const u32 nscripts = 4;
    for (u32 id = 0; id < nscripts; ++id) fcl_pair(m, "sub_417330", {sx(calc), id, 0, 0}, ++seed, "request", keep);
    CHECK(v0_of(fcl_pair(m, "sub_41B530", {sx(work), 0, 0, 0}, ++seed, "has request", keep)) == 1u);
    w32(m, work + fcl::kCeFlags, 0);
    CHECK(v0_of(fcl_pair(m, "sub_417380", {sx(calc), 0, 0, 0}, ++seed, "busy (request)", keep)) == 1u);
    fcl_pair(m, "sub_4177E0", {sx(work), 0, 0, 0}, ++seed, "load resources", keep);
    {
        const u32 res = r32(m, work + fcl::kCeResources);
        REQUIRE(res != 0u);
        CHECK(r16(m, r32(m, res + fcl::kCeResObj) + fcl::kNmObjCount) == 16);  // the 16 entries of table 0x6B2CF0
    }
    fcl_pair(m, "sub_4176F0", {sx(work), 99, 0, 0}, ++seed, "add resource (no name)", keep);
    w32(m, kOut + 0x40, 0x41424344u);
    w32(m, kOut + 0x44, 0);
    fcl_pair(m, "sub_4176F0", {sx(work), 98, sx(kOut + 0x40), 0}, ++seed, "add resource (name)", keep);
    for (u32 id = 0; id < nscripts; ++id) {
        fcl_pair(m, "sub_41B550", {sx(work), 0, 0, 0}, ++seed, "take request", keep);
        const u32 script = r32(m, work + fcl::kCeScript);
        CHECK(script == fcl::kCeScriptTable + 8 * id);
        CHECK(r32(m, r32(m, work + fcl::kCeRunner) + fcl::kRunFrame) == 0u);
        // run the script's frames (handlers this library does not emit are recorders returning 1)
        int frames = 0;
        u64 done = 0;
        while (!done && frames < 400) {
            done = v0_of(fcl_pair(m, "sub_41B5C0", {sx(work), sx(script), 0, 0}, ++seed, "run script", keep));
            fcl_pair(m, "fclCmbEff_UpdateCmbEffDraw2DLowTask", {sx(r32(m, work + fcl::kCeDraw2DTask)), 0, 0, 0}, ++seed, "draw 2D", keep);
            fcl_pair(m, "fclCmbEff_UpdateCmbEffDrawSPTask", {sx(r32(m, work + fcl::kCeDrawSPTask)), 0, 0, 0}, ++seed, "draw SP", keep);
            ++frames;
        }
        MESSAGE("cut-in script " << id << ": " << frames << " frames, ended " << done);
        if (done) CHECK(r32(m, work + fcl::kCeScript) == 0u);
    }
    CHECK(v0_of(fcl_pair(m, "sub_41B530", {sx(work), 0, 0, 0}, ++seed, "requests consumed", keep)) == 0u);
    fcl_pair(m, "sub_41BA60", {sx(work), 0, 0, 0}, ++seed, "draw 2D resources", keep);
    // the handlers on hand-made active nodes {command, resource, handler}
    const u32 act = kOut + 0x200, cmd = kOut + 0x280, resp = kOut + 0x300, objs = kOut + 0x340;
    for (int variant = 0; variant < 6; ++variant) {
        zero(m, act, 0x200);
        w32(m, act + fcl::kActCommand, cmd);
        w32(m, act + fcl::kActResource, resp);
        w8(m, cmd + fcl::kCmdOp, variant % 2 ? 64 : 3);
        w8(m, cmd + fcl::kCmdSubOp, variant % 3 == 0 ? 3 : 1);
        w32(m, cmd + fcl::kCmdArg12, 0x80FF2040u + variant);
        w32(m, cmd + fcl::kCmdArg16, static_cast<u32>(variant % 3) | (static_cast<u32>(variant) << 16));
        w32(m, cmd + fcl::kCmdArg20, static_cast<u32>(4 * variant));
        w32(m, resp + fcl::kResBuffer, objs);
        w32(m, objs + 4, static_cast<u32>(variant % 4));  // object count
        for (u32 i = 0; i < 4; ++i) {
            w32(m, objs + 8 + 4 * i, kOut + 0x380 + 16 * i);
            w32(m, kOut + 0x380 + 16 * i + 8, kOut + 0x400 + 64 * i);  // each object's frame
            w16(m, kOut + 0x380 + 16 * i, static_cast<u16>(0xFF));
        }
        for (const char* h : {"sub_418340", "sub_419B00", "sub_419B20", "sub_419B40", "sub_419C10", "sub_41A2C0", "sub_41ADD0"})
            fcl_pair(m, h, {sx(work), sx(act), 0, 0}, ++seed, h, keep);
        for (int f = 0; f < 7; ++f) fcl_pair(m, "sub_41A900", {sx(work), sx(act), 0, 0}, ++seed, "ring", keep);
        CHECK(r32(m, act + fcl::kActTimer) == 7u);
    }
    for (u32 kind = 3; kind <= 7; ++kind) {
        zero(m, kOut + 0x600, 0x40);
        w32(m, kOut + 0x600, kind);
        w32(m, kOut + 0x600 + fcl::kNmNodePayload, kOut + 0x620);
        fcl_pair(m, "sub_418130", {0, sx(kOut + 0x600), 0, 0}, ++seed, "resource on-insert", keep);
        CHECK((r32(m, kOut + 0x620 + fcl::kResBuffer) != 0u) == (kind >= 4 && kind <= 6));
    }
    // the vertex buffer: positions / uvs / colours from a hand-made strip
    for (u32 n = 1; n <= 4; ++n) {
        for (u32 i = 0; i < n; ++i) {
            wf(m, kOut + 0x700 + 12 * i, 1.0f * i);
            wf(m, kOut + 0x704 + 12 * i, 2.0f);
            wf(m, kOut + 0x708 + 12 * i, -1.0f);
            wf(m, kOut + 0x740 + 8 * i, 0.5f);
            wf(m, kOut + 0x744 + 8 * i, 0.25f * i);
            w32(m, kOut + 0x780 + 4 * i, 0x11223344u + i);
        }
        const Opt o{{{GPR_T0, 0x1234u}}, {}, true, true, recorders()};
        const u32 vb = static_cast<u32>(v0_of(fcl_pair(m, "sub_41BC90", {sx(kOut + 0x700), sx(kOut + 0x740), sx(kOut + 0x780), n}, ++seed, "vertex buffer", o)));
        REQUIRE(vb != 0u);
        CHECK(r32(m, vb + 8) == n);
        CHECK(r32(m, vb + 12) == 0x1234u);
        const u32 v = r32(m, vb + 4);
        CHECK(v == vb + 20);
        for (u32 i = 0; i < n; ++i) {
            CHECK(rf(m, v + 36 * i) == 1.0f * i);
            CHECK(rf(m, v + 36 * i + 32) == 0.25f * i);
            CHECK(r32(m, v + 36 * i + 12) == 0x11223344u + i);
        }
    }
    // the destroy callback and the runner helpers on the live work
    fcl_pair(m, "sub_4180E0", {sx(r32(m, work + fcl::kCeRunner)), 5, 0, 0}, ++seed, "runner add", keep);
    fcl_pair(m, "sub_417680", {sx(calc), 0, 0, 0}, ++seed, "cut-in destroy", keep);
    const u32 runner = static_cast<u32>(v0_of(fcl_pair(m, "sub_418030", {0, 0, 0, 0}, ++seed, "runner create", keep)));
    CHECK(r32(m, runner + fcl::kRunResList) != 0u);
    CHECK(r32(m, runner + fcl::kRunActive) != 0u);
    fcl_pair(m, "sub_4180A0", {sx(runner), 0, 0, 0}, ++seed, "runner destroy", keep);
}

TEST_CASE("game(fcl): pair count and early stops") {
    MESSAGE("fcl pairs run (outside the random-world case): " << g_pairs);
    for (const auto& [k, n] : g_stops) MESSAGE("  stopped early (both bodies alike): " << k << " x" << n);
}

#else

TEST_CASE("game(fcl): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
