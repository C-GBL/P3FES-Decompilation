// Pair tests for slice libs14 (game/src/cri/libs14.cpp): every body against its recompiled body, compared by
// tests/game/handgen_pairs.h -- the whole register file and cycle count at every check point and at the return / stop,
// all 32 MiB of RAM, the scratchpad, the BIOS window and the bus log -- on random worlds, on the replay snapshots'
// CRI state (ROFS work area, handles and volumes, the PS2RNA / SJX / SFD tables), and a few documented rules on leaf
// bodies. No stand-ins: a callee the test build does not emit ends both runs there, identically.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/libs14.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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
void fn_sub_53ED00_0053ed00(EEContext&);  // generated body
void fn_sub_53ED00_0053ed00__recomp(EEContext&);  // recompiled
void fn_sub_53F268_0053f268(EEContext&);  // generated body
void fn_sub_53F268_0053f268__recomp(EEContext&);  // recompiled
void fn_sub_53F298_0053f298(EEContext&);  // generated body
void fn_sub_53F298_0053f298__recomp(EEContext&);  // recompiled
void fn_PS2RNA_InitIopSnd_00560298(EEContext&);  // generated body
void fn_PS2RNA_InitIopSnd_00560298__recomp(EEContext&);  // recompiled
void fn_PS2RNA_Create_00560758(EEContext&);  // generated body
void fn_PS2RNA_Create_00560758__recomp(EEContext&);  // recompiled
void fn_sub_560AF8_00560af8(EEContext&);  // generated body
void fn_sub_560AF8_00560af8__recomp(EEContext&);  // recompiled
void fn_sub_560C88_00560c88(EEContext&);  // generated body
void fn_sub_560C88_00560c88__recomp(EEContext&);  // recompiled
void fn_sub_560D20_00560d20(EEContext&);  // generated body
void fn_sub_560D20_00560d20__recomp(EEContext&);  // recompiled
void fn_sub_560EB0_00560eb0(EEContext&);  // generated body
void fn_sub_560EB0_00560eb0__recomp(EEContext&);  // recompiled
void fn_sub_560F18_00560f18(EEContext&);  // generated body
void fn_sub_560F18_00560f18__recomp(EEContext&);  // recompiled
void fn_sub_560F78_00560f78(EEContext&);  // generated body
void fn_sub_560F78_00560f78__recomp(EEContext&);  // recompiled
void fn_PS2RNA_ExecServer_00561138(EEContext&);  // generated body
void fn_PS2RNA_ExecServer_00561138__recomp(EEContext&);  // recompiled
void fn_sub_561258_00561258(EEContext&);  // generated body
void fn_sub_561258_00561258__recomp(EEContext&);  // recompiled
void fn_sub_561390_00561390(EEContext&);  // generated body
void fn_sub_561390_00561390__recomp(EEContext&);  // recompiled
void fn_sub_561728_00561728(EEContext&);  // generated body
void fn_sub_561728_00561728__recomp(EEContext&);  // recompiled
void fn_sub_561740_00561740(EEContext&);  // generated body
void fn_sub_561740_00561740__recomp(EEContext&);  // recompiled
void fn_sub_563D20_00563d20(EEContext&);  // generated body
void fn_sub_563D20_00563d20__recomp(EEContext&);  // recompiled
void fn_sub_563E68_00563e68(EEContext&);  // generated body
void fn_sub_563E68_00563e68__recomp(EEContext&);  // recompiled
void fn_sub_563FE0_00563fe0(EEContext&);  // generated body
void fn_sub_563FE0_00563fe0__recomp(EEContext&);  // recompiled
void fn_sub_564218_00564218(EEContext&);  // generated body
void fn_sub_564218_00564218__recomp(EEContext&);  // recompiled
void fn_sub_5642D0_005642d0(EEContext&);  // generated body
void fn_sub_5642D0_005642d0__recomp(EEContext&);  // recompiled
void fn_sub_564360_00564360(EEContext&);  // generated body
void fn_sub_564360_00564360__recomp(EEContext&);  // recompiled
void fn_sub_564400_00564400(EEContext&);  // generated body
void fn_sub_564400_00564400__recomp(EEContext&);  // recompiled
void fn_sub_564510_00564510(EEContext&);  // generated body
void fn_sub_564510_00564510__recomp(EEContext&);  // recompiled
void fn_sub_564738_00564738(EEContext&);  // generated body
void fn_sub_564738_00564738__recomp(EEContext&);  // recompiled
void fn_pfsCvfsSeek_00565730(EEContext&);  // generated body
void fn_pfsCvfsSeek_00565730__recomp(EEContext&);  // recompiled
void fn_pfsCvfsReqRd_005657a0(EEContext&);  // generated body
void fn_pfsCvfsReqRd_005657a0__recomp(EEContext&);  // recompiled
void fn_pfsCvfsGetStat_005657d0(EEContext&);  // generated body
void fn_pfsCvfsGetStat_005657d0__recomp(EEContext&);  // recompiled
void fn_pfsCvfsGetSctLen_00565820(EEContext&);  // generated body
void fn_pfsCvfsGetSctLen_00565820__recomp(EEContext&);  // recompiled
void fn_pfsCvfsGetNumTr_00565838(EEContext&);  // generated body
void fn_pfsCvfsGetNumTr_00565838__recomp(EEContext&);  // recompiled
void fn_coshl_8_00565850(EEContext&);  // generated body
void fn_coshl_8_00565850__recomp(EEContext&);  // recompiled
void fn_pfsCvfsExecServer_00565888(EEContext&);  // generated body
void fn_pfsCvfsExecServer_00565888__recomp(EEContext&);  // recompiled
void fn_sub_565BC0_00565bc0(EEContext&);  // generated body
void fn_sub_565BC0_00565bc0__recomp(EEContext&);  // recompiled
void fn_RFHN_ReqRdG_00565e10(EEContext&);  // generated body
void fn_RFHN_ReqRdG_00565e10__recomp(EEContext&);  // recompiled
void fn_RFHN_StopTrG_00566180(EEContext&);  // generated body
void fn_RFHN_StopTrG_00566180__recomp(EEContext&);  // recompiled
void fn_RFIF_InitOvl_005662f0(EEContext&);  // generated body
void fn_RFIF_InitOvl_005662f0__recomp(EEContext&);  // recompiled
void fn_ROFS_AddVolume_005663d8(EEContext&);  // generated body
void fn_ROFS_AddVolume_005663d8__recomp(EEContext&);  // recompiled
void fn_sub_5664F8_005664f8(EEContext&);  // generated body
void fn_sub_5664F8_005664f8__recomp(EEContext&);  // recompiled
void fn_ROFS_Open_005665d0(EEContext&);  // generated body
void fn_ROFS_Open_005665d0__recomp(EEContext&);  // recompiled
void fn_ROFS_Close_005666e0(EEContext&);  // generated body
void fn_ROFS_Close_005666e0__recomp(EEContext&);  // recompiled
void fn_ROFS_ReqRd_00566708(EEContext&);  // generated body
void fn_ROFS_ReqRd_00566708__recomp(EEContext&);  // recompiled
void fn_ROFS_ExecServer_00566778(EEContext&);  // generated body
void fn_ROFS_ExecServer_00566778__recomp(EEContext&);  // recompiled
void fn_ROFS_GetStat_005667a8(EEContext&);  // generated body
void fn_ROFS_GetStat_005667a8__recomp(EEContext&);  // recompiled
void fn_ROFS_GetFileSiz_005667d0(EEContext&);  // generated body
void fn_ROFS_GetFileSiz_005667d0__recomp(EEContext&);  // recompiled
void fn_ROFS_GetVolumeInf_005669d8(EEContext&);  // generated body
void fn_ROFS_GetVolumeInf_005669d8__recomp(EEContext&);  // recompiled
void fn_ROFS_SetDir_00566b08(EEContext&);  // generated body
void fn_ROFS_SetDir_00566b08__recomp(EEContext&);  // recompiled
void fn_rfmai_isDvdRomAccess_00567478(EEContext&);  // generated body
void fn_rfmai_isDvdRomAccess_00567478__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_11_00567810(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_11_00567810__recomp(EEContext&);  // recompiled
void fn_ROFS_Init_00567820(EEContext&);  // generated body
void fn_ROFS_Init_00567820__recomp(EEContext&);  // recompiled
void fn_RFMAI_InitG_00567858(EEContext&);  // generated body
void fn_RFMAI_InitG_00567858__recomp(EEContext&);  // recompiled
void fn_sub_567BE0_00567be0(EEContext&);  // generated body
void fn_sub_567BE0_00567be0__recomp(EEContext&);  // recompiled
void fn_rfmai_updateHnStat_00568710(EEContext&);  // generated body
void fn_rfmai_updateHnStat_00568710__recomp(EEContext&);  // recompiled
void fn_sub_568AC0_00568ac0(EEContext&);  // generated body
void fn_sub_568AC0_00568ac0__recomp(EEContext&);  // recompiled
void fn_sub_568B80_00568b80(EEContext&);  // generated body
void fn_sub_568B80_00568b80__recomp(EEContext&);  // recompiled
void fn_RFMAI_ReadWG_00569538(EEContext&);  // generated body
void fn_RFMAI_ReadWG_00569538__recomp(EEContext&);  // recompiled
void fn_dcfInit_0056a530(EEContext&);  // generated body
void fn_dcfInit_0056a530__recomp(EEContext&);  // recompiled
void fn_dcfSeek_0056a540(EEContext&);  // generated body
void fn_dcfSeek_0056a540__recomp(EEContext&);  // recompiled
void fn_dcfReqRd_0056a600(EEContext&);  // generated body
void fn_dcfReqRd_0056a600__recomp(EEContext&);  // recompiled
void fn_dcfExecServer_0056a698(EEContext&);  // generated body
void fn_dcfExecServer_0056a698__recomp(EEContext&);  // recompiled
void fn_dcfGetStat_0056a6d0(EEContext&);  // generated body
void fn_dcfGetStat_0056a6d0__recomp(EEContext&);  // recompiled
void fn_dcfGetSctLen_0056a730(EEContext&);  // generated body
void fn_dcfGetSctLen_0056a730__recomp(EEContext&);  // recompiled
void fn_dcfGetNumTr_0056a790(EEContext&);  // generated body
void fn_dcfGetNumTr_0056a790__recomp(EEContext&);  // recompiled
void fn_sub_56A7F0_0056a7f0(EEContext&);  // generated body
void fn_sub_56A7F0_0056a7f0__recomp(EEContext&);  // recompiled
void fn_dcfReqRdBlk_0056a860(EEContext&);  // generated body
void fn_dcfReqRdBlk_0056a860__recomp(EEContext&);  // recompiled
void fn_dcfReqRdCda_0056aa98(EEContext&);  // generated body
void fn_dcfReqRdCda_0056aa98__recomp(EEContext&);  // recompiled
void fn_rfpfs_waitRdComplete_0056ac28(EEContext&);  // generated body
void fn_rfpfs_waitRdComplete_0056ac28__recomp(EEContext&);  // recompiled
void fn_rfpfs_parentSeek_0056acb8(EEContext&);  // generated body
void fn_rfpfs_parentSeek_0056acb8__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_12_0056ad38(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_12_0056ad38__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_13_0056c8b8(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_13_0056c8b8__recomp(EEContext&);  // recompiled
void fn_sub_56DDE0_0056dde0(EEContext&);  // generated body
void fn_sub_56DDE0_0056dde0__recomp(EEContext&);  // recompiled
void fn_sub_570248_00570248(EEContext&);  // generated body
void fn_sub_570248_00570248__recomp(EEContext&);  // recompiled
void fn_sub_5703B8_005703b8(EEContext&);  // generated body
void fn_sub_5703B8_005703b8__recomp(EEContext&);  // recompiled
void fn_sub_593140_00593140(EEContext&);  // generated body
void fn_sub_593140_00593140__recomp(EEContext&);  // recompiled
void fn_sub_593408_00593408(EEContext&);  // generated body
void fn_sub_593408_00593408__recomp(EEContext&);  // recompiled
void fn_sub_595868_00595868(EEContext&);  // generated body
void fn_sub_595868_00595868__recomp(EEContext&);  // recompiled
void fn_sub_5959E0_005959e0(EEContext&);  // generated body
void fn_sub_5959E0_005959e0__recomp(EEContext&);  // recompiled
void fn_sub_596760_00596760(EEContext&);  // generated body
void fn_sub_596760_00596760__recomp(EEContext&);  // recompiled
void fn_sub_596B68_00596b68(EEContext&);  // generated body
void fn_sub_596B68_00596b68__recomp(EEContext&);  // recompiled
void fn_sub_597878_00597878(EEContext&);  // generated body
void fn_sub_597878_00597878__recomp(EEContext&);  // recompiled
void fn_sub_5978E8_005978e8(EEContext&);  // generated body
void fn_sub_5978E8_005978e8__recomp(EEContext&);  // recompiled
void fn_sub_597A18_00597a18(EEContext&);  // generated body
void fn_sub_597A18_00597a18__recomp(EEContext&);  // recompiled
void fn_sub_5985F8_005985f8(EEContext&);  // generated body
void fn_sub_5985F8_005985f8__recomp(EEContext&);  // recompiled
void fn_sub_598980_00598980(EEContext&);  // generated body
void fn_sub_598980_00598980__recomp(EEContext&);  // recompiled
void fn_sub_599020_00599020(EEContext&);  // generated body
void fn_sub_599020_00599020__recomp(EEContext&);  // recompiled
void fn_sub_59A298_0059a298(EEContext&);  // generated body
void fn_sub_59A298_0059a298__recomp(EEContext&);  // recompiled
void fn_sub_59A600_0059a600(EEContext&);  // generated body
void fn_sub_59A600_0059a600__recomp(EEContext&);  // recompiled
void fn_sub_59AD40_0059ad40(EEContext&);  // generated body
void fn_sub_59AD40_0059ad40__recomp(EEContext&);  // recompiled
void fn_sub_59EC08_0059ec08(EEContext&);  // generated body
void fn_sub_59EC08_0059ec08__recomp(EEContext&);  // recompiled
void fn_sub_59EE18_0059ee18(EEContext&);  // generated body
void fn_sub_59EE18_0059ee18__recomp(EEContext&);  // recompiled
void fn_sub_59F320_0059f320(EEContext&);  // generated body
void fn_sub_59F320_0059f320__recomp(EEContext&);  // recompiled
void fn_sub_59F3D8_0059f3d8(EEContext&);  // generated body
void fn_sub_59F3D8_0059f3d8__recomp(EEContext&);  // recompiled
void fn_sub_59F8F8_0059f8f8(EEContext&);  // generated body
void fn_sub_59F8F8_0059f8f8__recomp(EEContext&);  // recompiled
void fn_sub_59F968_0059f968(EEContext&);  // generated body
void fn_sub_59F968_0059f968__recomp(EEContext&);  // recompiled
void fn_WTLS_get_table_2_0059fd60(EEContext&);  // generated body
void fn_WTLS_get_table_2_0059fd60__recomp(EEContext&);  // recompiled
void fn_sub_59FE50_0059fe50(EEContext&);  // generated body
void fn_sub_59FE50_0059fe50__recomp(EEContext&);  // recompiled
void fn_sub_59FFC8_0059ffc8(EEContext&);  // generated body
void fn_sub_59FFC8_0059ffc8__recomp(EEContext&);  // recompiled
void fn_sub_5A0048_005a0048(EEContext&);  // generated body
void fn_sub_5A0048_005a0048__recomp(EEContext&);  // recompiled
void fn_sub_5A04F0_005a04f0(EEContext&);  // generated body
void fn_sub_5A04F0_005a04f0__recomp(EEContext&);  // recompiled
void fn_sub_5A0BB0_005a0bb0(EEContext&);  // generated body
void fn_sub_5A0BB0_005a0bb0__recomp(EEContext&);  // recompiled
void fn_sub_5A10E8_005a10e8(EEContext&);  // generated body
void fn_sub_5A10E8_005a10e8__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_53ED00", 0x53ED00, &recomp_gen::fn_sub_53ED00_0053ed00, &recomp_gen::fn_sub_53ED00_0053ed00__recomp},
    {"sub_53F268", 0x53F268, &recomp_gen::fn_sub_53F268_0053f268, &recomp_gen::fn_sub_53F268_0053f268__recomp},
    {"sub_53F298", 0x53F298, &recomp_gen::fn_sub_53F298_0053f298, &recomp_gen::fn_sub_53F298_0053f298__recomp},
    {"PS2RNA_InitIopSnd", 0x560298, &recomp_gen::fn_PS2RNA_InitIopSnd_00560298, &recomp_gen::fn_PS2RNA_InitIopSnd_00560298__recomp},
    {"PS2RNA_Create", 0x560758, &recomp_gen::fn_PS2RNA_Create_00560758, &recomp_gen::fn_PS2RNA_Create_00560758__recomp},
    {"sub_560AF8", 0x560AF8, &recomp_gen::fn_sub_560AF8_00560af8, &recomp_gen::fn_sub_560AF8_00560af8__recomp},
    {"sub_560C88", 0x560C88, &recomp_gen::fn_sub_560C88_00560c88, &recomp_gen::fn_sub_560C88_00560c88__recomp},
    {"sub_560D20", 0x560D20, &recomp_gen::fn_sub_560D20_00560d20, &recomp_gen::fn_sub_560D20_00560d20__recomp},
    {"sub_560EB0", 0x560EB0, &recomp_gen::fn_sub_560EB0_00560eb0, &recomp_gen::fn_sub_560EB0_00560eb0__recomp},
    {"sub_560F18", 0x560F18, &recomp_gen::fn_sub_560F18_00560f18, &recomp_gen::fn_sub_560F18_00560f18__recomp},
    {"sub_560F78", 0x560F78, &recomp_gen::fn_sub_560F78_00560f78, &recomp_gen::fn_sub_560F78_00560f78__recomp},
    {"PS2RNA_ExecServer", 0x561138, &recomp_gen::fn_PS2RNA_ExecServer_00561138, &recomp_gen::fn_PS2RNA_ExecServer_00561138__recomp},
    {"sub_561258", 0x561258, &recomp_gen::fn_sub_561258_00561258, &recomp_gen::fn_sub_561258_00561258__recomp},
    {"sub_561390", 0x561390, &recomp_gen::fn_sub_561390_00561390, &recomp_gen::fn_sub_561390_00561390__recomp},
    {"sub_561728", 0x561728, &recomp_gen::fn_sub_561728_00561728, &recomp_gen::fn_sub_561728_00561728__recomp},
    {"sub_561740", 0x561740, &recomp_gen::fn_sub_561740_00561740, &recomp_gen::fn_sub_561740_00561740__recomp},
    {"sub_563D20", 0x563D20, &recomp_gen::fn_sub_563D20_00563d20, &recomp_gen::fn_sub_563D20_00563d20__recomp},
    {"sub_563E68", 0x563E68, &recomp_gen::fn_sub_563E68_00563e68, &recomp_gen::fn_sub_563E68_00563e68__recomp},
    {"sub_563FE0", 0x563FE0, &recomp_gen::fn_sub_563FE0_00563fe0, &recomp_gen::fn_sub_563FE0_00563fe0__recomp},
    {"sub_564218", 0x564218, &recomp_gen::fn_sub_564218_00564218, &recomp_gen::fn_sub_564218_00564218__recomp},
    {"sub_5642D0", 0x5642D0, &recomp_gen::fn_sub_5642D0_005642d0, &recomp_gen::fn_sub_5642D0_005642d0__recomp},
    {"sub_564360", 0x564360, &recomp_gen::fn_sub_564360_00564360, &recomp_gen::fn_sub_564360_00564360__recomp},
    {"sub_564400", 0x564400, &recomp_gen::fn_sub_564400_00564400, &recomp_gen::fn_sub_564400_00564400__recomp},
    {"sub_564510", 0x564510, &recomp_gen::fn_sub_564510_00564510, &recomp_gen::fn_sub_564510_00564510__recomp},
    {"sub_564738", 0x564738, &recomp_gen::fn_sub_564738_00564738, &recomp_gen::fn_sub_564738_00564738__recomp},
    {"pfsCvfsSeek", 0x565730, &recomp_gen::fn_pfsCvfsSeek_00565730, &recomp_gen::fn_pfsCvfsSeek_00565730__recomp},
    {"pfsCvfsReqRd", 0x5657A0, &recomp_gen::fn_pfsCvfsReqRd_005657a0, &recomp_gen::fn_pfsCvfsReqRd_005657a0__recomp},
    {"pfsCvfsGetStat", 0x5657D0, &recomp_gen::fn_pfsCvfsGetStat_005657d0, &recomp_gen::fn_pfsCvfsGetStat_005657d0__recomp},
    {"pfsCvfsGetSctLen", 0x565820, &recomp_gen::fn_pfsCvfsGetSctLen_00565820, &recomp_gen::fn_pfsCvfsGetSctLen_00565820__recomp},
    {"pfsCvfsGetNumTr", 0x565838, &recomp_gen::fn_pfsCvfsGetNumTr_00565838, &recomp_gen::fn_pfsCvfsGetNumTr_00565838__recomp},
    {"coshl_8", 0x565850, &recomp_gen::fn_coshl_8_00565850, &recomp_gen::fn_coshl_8_00565850__recomp},
    {"pfsCvfsExecServer", 0x565888, &recomp_gen::fn_pfsCvfsExecServer_00565888, &recomp_gen::fn_pfsCvfsExecServer_00565888__recomp},
    {"sub_565BC0", 0x565BC0, &recomp_gen::fn_sub_565BC0_00565bc0, &recomp_gen::fn_sub_565BC0_00565bc0__recomp},
    {"RFHN_ReqRdG", 0x565E10, &recomp_gen::fn_RFHN_ReqRdG_00565e10, &recomp_gen::fn_RFHN_ReqRdG_00565e10__recomp},
    {"RFHN_StopTrG", 0x566180, &recomp_gen::fn_RFHN_StopTrG_00566180, &recomp_gen::fn_RFHN_StopTrG_00566180__recomp},
    {"RFIF_InitOvl", 0x5662F0, &recomp_gen::fn_RFIF_InitOvl_005662f0, &recomp_gen::fn_RFIF_InitOvl_005662f0__recomp},
    {"ROFS_AddVolume", 0x5663D8, &recomp_gen::fn_ROFS_AddVolume_005663d8, &recomp_gen::fn_ROFS_AddVolume_005663d8__recomp},
    {"sub_5664F8", 0x5664F8, &recomp_gen::fn_sub_5664F8_005664f8, &recomp_gen::fn_sub_5664F8_005664f8__recomp},
    {"ROFS_Open", 0x5665D0, &recomp_gen::fn_ROFS_Open_005665d0, &recomp_gen::fn_ROFS_Open_005665d0__recomp},
    {"ROFS_Close", 0x5666E0, &recomp_gen::fn_ROFS_Close_005666e0, &recomp_gen::fn_ROFS_Close_005666e0__recomp},
    {"ROFS_ReqRd", 0x566708, &recomp_gen::fn_ROFS_ReqRd_00566708, &recomp_gen::fn_ROFS_ReqRd_00566708__recomp},
    {"ROFS_ExecServer", 0x566778, &recomp_gen::fn_ROFS_ExecServer_00566778, &recomp_gen::fn_ROFS_ExecServer_00566778__recomp},
    {"ROFS_GetStat", 0x5667A8, &recomp_gen::fn_ROFS_GetStat_005667a8, &recomp_gen::fn_ROFS_GetStat_005667a8__recomp},
    {"ROFS_GetFileSiz", 0x5667D0, &recomp_gen::fn_ROFS_GetFileSiz_005667d0, &recomp_gen::fn_ROFS_GetFileSiz_005667d0__recomp},
    {"ROFS_GetVolumeInf", 0x5669D8, &recomp_gen::fn_ROFS_GetVolumeInf_005669d8, &recomp_gen::fn_ROFS_GetVolumeInf_005669d8__recomp},
    {"ROFS_SetDir", 0x566B08, &recomp_gen::fn_ROFS_SetDir_00566b08, &recomp_gen::fn_ROFS_SetDir_00566b08__recomp},
    {"rfmai_isDvdRomAccess", 0x567478, &recomp_gen::fn_rfmai_isDvdRomAccess_00567478, &recomp_gen::fn_rfmai_isDvdRomAccess_00567478__recomp},
    {"sceLibgcc32GetErxEntries_11", 0x567810, &recomp_gen::fn_sceLibgcc32GetErxEntries_11_00567810, &recomp_gen::fn_sceLibgcc32GetErxEntries_11_00567810__recomp},
    {"ROFS_Init", 0x567820, &recomp_gen::fn_ROFS_Init_00567820, &recomp_gen::fn_ROFS_Init_00567820__recomp},
    {"RFMAI_InitG", 0x567858, &recomp_gen::fn_RFMAI_InitG_00567858, &recomp_gen::fn_RFMAI_InitG_00567858__recomp},
    {"sub_567BE0", 0x567BE0, &recomp_gen::fn_sub_567BE0_00567be0, &recomp_gen::fn_sub_567BE0_00567be0__recomp},
    {"rfmai_updateHnStat", 0x568710, &recomp_gen::fn_rfmai_updateHnStat_00568710, &recomp_gen::fn_rfmai_updateHnStat_00568710__recomp},
    {"sub_568AC0", 0x568AC0, &recomp_gen::fn_sub_568AC0_00568ac0, &recomp_gen::fn_sub_568AC0_00568ac0__recomp},
    {"sub_568B80", 0x568B80, &recomp_gen::fn_sub_568B80_00568b80, &recomp_gen::fn_sub_568B80_00568b80__recomp},
    {"RFMAI_ReadWG", 0x569538, &recomp_gen::fn_RFMAI_ReadWG_00569538, &recomp_gen::fn_RFMAI_ReadWG_00569538__recomp},
    {"dcfInit", 0x56A530, &recomp_gen::fn_dcfInit_0056a530, &recomp_gen::fn_dcfInit_0056a530__recomp},
    {"dcfSeek", 0x56A540, &recomp_gen::fn_dcfSeek_0056a540, &recomp_gen::fn_dcfSeek_0056a540__recomp},
    {"dcfReqRd", 0x56A600, &recomp_gen::fn_dcfReqRd_0056a600, &recomp_gen::fn_dcfReqRd_0056a600__recomp},
    {"dcfExecServer", 0x56A698, &recomp_gen::fn_dcfExecServer_0056a698, &recomp_gen::fn_dcfExecServer_0056a698__recomp},
    {"dcfGetStat", 0x56A6D0, &recomp_gen::fn_dcfGetStat_0056a6d0, &recomp_gen::fn_dcfGetStat_0056a6d0__recomp},
    {"dcfGetSctLen", 0x56A730, &recomp_gen::fn_dcfGetSctLen_0056a730, &recomp_gen::fn_dcfGetSctLen_0056a730__recomp},
    {"dcfGetNumTr", 0x56A790, &recomp_gen::fn_dcfGetNumTr_0056a790, &recomp_gen::fn_dcfGetNumTr_0056a790__recomp},
    {"sub_56A7F0", 0x56A7F0, &recomp_gen::fn_sub_56A7F0_0056a7f0, &recomp_gen::fn_sub_56A7F0_0056a7f0__recomp},
    {"dcfReqRdBlk", 0x56A860, &recomp_gen::fn_dcfReqRdBlk_0056a860, &recomp_gen::fn_dcfReqRdBlk_0056a860__recomp},
    {"dcfReqRdCda", 0x56AA98, &recomp_gen::fn_dcfReqRdCda_0056aa98, &recomp_gen::fn_dcfReqRdCda_0056aa98__recomp},
    {"rfpfs_waitRdComplete", 0x56AC28, &recomp_gen::fn_rfpfs_waitRdComplete_0056ac28, &recomp_gen::fn_rfpfs_waitRdComplete_0056ac28__recomp},
    {"rfpfs_parentSeek", 0x56ACB8, &recomp_gen::fn_rfpfs_parentSeek_0056acb8, &recomp_gen::fn_rfpfs_parentSeek_0056acb8__recomp},
    {"sceLibgcc32GetErxEntries_12", 0x56AD38, &recomp_gen::fn_sceLibgcc32GetErxEntries_12_0056ad38, &recomp_gen::fn_sceLibgcc32GetErxEntries_12_0056ad38__recomp},
    {"sceLibgcc32GetErxEntries_13", 0x56C8B8, &recomp_gen::fn_sceLibgcc32GetErxEntries_13_0056c8b8, &recomp_gen::fn_sceLibgcc32GetErxEntries_13_0056c8b8__recomp},
    {"sub_56DDE0", 0x56DDE0, &recomp_gen::fn_sub_56DDE0_0056dde0, &recomp_gen::fn_sub_56DDE0_0056dde0__recomp},
    {"sub_570248", 0x570248, &recomp_gen::fn_sub_570248_00570248, &recomp_gen::fn_sub_570248_00570248__recomp},
    {"sub_5703B8", 0x5703B8, &recomp_gen::fn_sub_5703B8_005703b8, &recomp_gen::fn_sub_5703B8_005703b8__recomp},
    {"sub_593140", 0x593140, &recomp_gen::fn_sub_593140_00593140, &recomp_gen::fn_sub_593140_00593140__recomp},
    {"sub_593408", 0x593408, &recomp_gen::fn_sub_593408_00593408, &recomp_gen::fn_sub_593408_00593408__recomp},
    {"sub_595868", 0x595868, &recomp_gen::fn_sub_595868_00595868, &recomp_gen::fn_sub_595868_00595868__recomp},
    {"sub_5959E0", 0x5959E0, &recomp_gen::fn_sub_5959E0_005959e0, &recomp_gen::fn_sub_5959E0_005959e0__recomp},
    {"sub_596760", 0x596760, &recomp_gen::fn_sub_596760_00596760, &recomp_gen::fn_sub_596760_00596760__recomp},
    {"sub_596B68", 0x596B68, &recomp_gen::fn_sub_596B68_00596b68, &recomp_gen::fn_sub_596B68_00596b68__recomp},
    {"sub_597878", 0x597878, &recomp_gen::fn_sub_597878_00597878, &recomp_gen::fn_sub_597878_00597878__recomp},
    {"sub_5978E8", 0x5978E8, &recomp_gen::fn_sub_5978E8_005978e8, &recomp_gen::fn_sub_5978E8_005978e8__recomp},
    {"sub_597A18", 0x597A18, &recomp_gen::fn_sub_597A18_00597a18, &recomp_gen::fn_sub_597A18_00597a18__recomp},
    {"sub_5985F8", 0x5985F8, &recomp_gen::fn_sub_5985F8_005985f8, &recomp_gen::fn_sub_5985F8_005985f8__recomp},
    {"sub_598980", 0x598980, &recomp_gen::fn_sub_598980_00598980, &recomp_gen::fn_sub_598980_00598980__recomp},
    {"sub_599020", 0x599020, &recomp_gen::fn_sub_599020_00599020, &recomp_gen::fn_sub_599020_00599020__recomp},
    {"sub_59A298", 0x59A298, &recomp_gen::fn_sub_59A298_0059a298, &recomp_gen::fn_sub_59A298_0059a298__recomp},
    {"sub_59A600", 0x59A600, &recomp_gen::fn_sub_59A600_0059a600, &recomp_gen::fn_sub_59A600_0059a600__recomp},
    {"sub_59AD40", 0x59AD40, &recomp_gen::fn_sub_59AD40_0059ad40, &recomp_gen::fn_sub_59AD40_0059ad40__recomp},
    {"sub_59EC08", 0x59EC08, &recomp_gen::fn_sub_59EC08_0059ec08, &recomp_gen::fn_sub_59EC08_0059ec08__recomp},
    {"sub_59EE18", 0x59EE18, &recomp_gen::fn_sub_59EE18_0059ee18, &recomp_gen::fn_sub_59EE18_0059ee18__recomp},
    {"sub_59F320", 0x59F320, &recomp_gen::fn_sub_59F320_0059f320, &recomp_gen::fn_sub_59F320_0059f320__recomp},
    {"sub_59F3D8", 0x59F3D8, &recomp_gen::fn_sub_59F3D8_0059f3d8, &recomp_gen::fn_sub_59F3D8_0059f3d8__recomp},
    {"sub_59F8F8", 0x59F8F8, &recomp_gen::fn_sub_59F8F8_0059f8f8, &recomp_gen::fn_sub_59F8F8_0059f8f8__recomp},
    {"sub_59F968", 0x59F968, &recomp_gen::fn_sub_59F968_0059f968, &recomp_gen::fn_sub_59F968_0059f968__recomp},
    {"WTLS_get_table_2", 0x59FD60, &recomp_gen::fn_WTLS_get_table_2_0059fd60, &recomp_gen::fn_WTLS_get_table_2_0059fd60__recomp},
    {"sub_59FE50", 0x59FE50, &recomp_gen::fn_sub_59FE50_0059fe50, &recomp_gen::fn_sub_59FE50_0059fe50__recomp},
    {"sub_59FFC8", 0x59FFC8, &recomp_gen::fn_sub_59FFC8_0059ffc8, &recomp_gen::fn_sub_59FFC8_0059ffc8__recomp},
    {"sub_5A0048", 0x5A0048, &recomp_gen::fn_sub_5A0048_005a0048, &recomp_gen::fn_sub_5A0048_005a0048__recomp},
    {"sub_5A04F0", 0x5A04F0, &recomp_gen::fn_sub_5A04F0_005a04f0, &recomp_gen::fn_sub_5A04F0_005a04f0__recomp},
    {"sub_5A0BB0", 0x5A0BB0, &recomp_gen::fn_sub_5A0BB0_005a0bb0, &recomp_gen::fn_sub_5A0BB0_005a0bb0__recomp},
    {"sub_5A10E8", 0x5A10E8, &recomp_gen::fn_sub_5A10E8_005a10e8, &recomp_gen::fn_sub_5A10E8_005a10e8__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena (random worlds), and a record / out area for the snapshot runs.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;
constexpr u32 kRec = 0x01820000u;  // a built record of small values / pointers back into it (8 KiB)
constexpr u32 kOut = 0x01822000u;  // out-parameters (8 KiB)
const char* const kSnaps[] = {"dorm_replay_4900", "b_5800", "climb_ref_17000", "fusion_ref_6300", "shop_ref_4100"};

// The game's CRI state the bodies read (symbols/ globals).
constexpr u32 kRofsWork = 0x7B2700u;    // g_rofs_work: the ROFS work area
constexpr u32 kRofsPfsTbl = 0x7B2808u;  // g_rofs_pfs_tbl
constexpr u32 kRnaTable = 0x7AB850u;    // PS2RNA handles, 16 x 100 bytes
constexpr u32 kSjxTable = 0x7B1AD0u;    // SJX entries, 32 x 20 bytes
constexpr u32 kSfdHandles = 0x7B4774u;  // the open SFD handles, 8 words

u32 r32(Machine& m, u32 va) {
    u32 v;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
bool ram_ptr(u32 p) { return p >= 0x100000u && p < 0x01FF0000u; }

const Case& by_name(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

// One pair on a long-lived BaseRange (write_tracker.h): the snapshot's 32 MiB stay the base and restore() copies back
// only the pages a pair wrote. The comparison is hgp::pair's.
hgp::Run pr_base(Machine& m, BaseRange& ram, const Case& c, const Args& args, u32 seed) {
    const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    ram.begin();
    hgp::Run h = hgp::run_one(m, c.hand, args, seed, {});
    std::vector<u8> bios_h;
    if (!hgp::bios_clean(m)) {
        bios_h.assign(m.mem.bios(), m.mem.bios() + EEMemory::kBiosSize);
        std::memset(m.mem.bios(), 0, EEMemory::kBiosSize);
    }
    ram.between();
    std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
    hgp::Run r = hgp::run_one(m, c.recomp, args, seed, {});
    const bool bios_r = !hgp::bios_clean(m);
    INFO(c.name << " a0=" << hex64(args[0]) << " a1=" << hex64(args[1]) << " a2=" << hex64(args[2]) << " a3=" << hex64(args[3])
                << " seed=" << seed << (r.stopped ? " (recomp stopped: " + r.what + " at " + hex64(r.stop_pc) + ")" : std::string()));
    CHECK(bios_r == !bios_h.empty());
    if (bios_r) std::memset(m.mem.bios(), 0, EEMemory::kBiosSize);
    CHECK(h.stopped == r.stopped);
    CHECK(h.stop_pc == r.stop_pc);
    CHECK(h.what == r.what);
    CHECK(h.syscalls == r.syscalls);
    CHECK(h.snaps.size() == r.snaps.size());
    for (std::size_t i = 0; i < std::min(h.snaps.size(), r.snaps.size()); ++i) {
        const std::string d = hgp::diff(h.snaps[i], r.snaps[i]);
        if (!d.empty()) {
            INFO("check point " << i << ": " << d);
            CHECK(false);
            break;
        }
    }
    {
        const std::string d = hgp::diff(h.end, r.end);
        INFO((r.stopped ? "at the stop: " : "at the return: ") << d);
        CHECK(d.empty());
    }
    if (const std::size_t first = ram.first_difference(); first != ram.size()) {
        INFO("main RAM: first differing byte at " << hex64(first));
        CHECK(false);
    }
    CHECK(h.spr == r.spr);
    CHECK(h.bus.size() == r.bus.size());
    for (std::size_t i = 0; i < std::min(h.bus.size(), r.bus.size()); ++i) {
        const auto &x = h.bus[i], &y = r.bus[i];
        if (x.write != y.write || x.bits != y.bits || x.pa != y.pa || x.lo != y.lo || x.hi != y.hi) {
            INFO("bus access " << i << " differs");
            CHECK(false);
            break;
        }
    }
    CHECK(h.vu_control == r.vu_control);
    return r;
}

// The records a snapshot holds for these bodies: the ROFS work area and its handles (60 bytes each from +4236) and
// volumes, the used PS2RNA and SJX slots (and slot 0 of each table), the open SFD handles; then the built record.
std::vector<u32> snapshot_records(Machine& m) {
    std::vector<u32> recs{0u, kRec};
    const auto add = [&](u32 p) {
        if (ram_ptr(p) && std::find(recs.begin(), recs.end(), p) == recs.end()) recs.push_back(p);
    };
    const u32 work = r32(m, kRofsWork);
    if (ram_ptr(work)) {
        add(work);
        const u32 handles = std::min(r32(m, work + 4), 6u);
        for (u32 i = 0; i < handles; ++i) add(work + 4236 + 60 * i);
        add(r32(m, work + 40));  // the volumes
    }
    add(r32(m, kRofsPfsTbl));
    add(kRnaTable);
    add(kSjxTable);
    for (u32 i = 1; i < 16; ++i)
        if (m.at(kRnaTable + 100 * i)[0] != 0) add(kRnaTable + 100 * i);
    for (u32 i = 1; i < 32; ++i)
        if (m.at(kSjxTable + 20 * i)[0] != 0) add(kSjxTable + 20 * i);
    for (u32 i = 0; i < 8; ++i) add(r32(m, kSfdHandles + 4 * i));
    return recs;
}

}  // namespace

TEST_CASE("game(libs14): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    const u32 seeds = env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds;
    const char* only = std::getenv("P3FES_HG_ONLY");     // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;  // name and seed of every pair on stderr
    int total = 0, stops = 0;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s seed %u\n", c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += hgp::pair(*m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
            ++total;
        }
    }
    MESSAGE(total << " pairs, " << stops << " stopped early (identically)");
}

// The replay snapshots hold the CRI modules as the game leaves them: ROFS initialised over the CVM image (g_rofs_work,
// its handles and volumes, the pfs / dcf tables), the PS2RNA and SJX tables, the SFD handle table. Every body runs on
// each snapshot with a0 from those records (and null, and a built record), a1 from the values its branches test
// (0, 1, 2, 3, 16, 48000, -1, an out pointer) and out pointers in a2 / a3; each pair starts from the snapshot.
TEST_CASE("game(libs14): every body on the replay snapshots' CRI state") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* only = std::getenv("P3FES_HG_ONLY");
    int runs = 0, stops = 0, snaps = 0;
    std::size_t records = 0;
    for (const char* dir : kSnaps) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.size() != EEMemory::kMainRamSize) {
            MESSAGE("SKIP: snapshot " << dir << " not found");
            continue;
        }
        ++snaps;
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        CHECK(ram_ptr(r32(*m, kRofsWork)));  // ROFS is up in every replay (ROFS_Init from kwlnInitMain)
        std::memset(m->at(kRec), 0, 0x4000);
        for (u32 i = 0; i < 0x2000; i += 4) w32(*m, kRec + i, (i / 4) % 5 == 0 ? kRec + ((i * 7) & 0x1FF0u) : (i / 4) % 7);
        const std::vector<u32> recs = snapshot_records(*m);
        records += recs.size();
        BaseRange base(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            u32 seed = 1;
            for (const u32 rec : recs)
                for (const u64 a1 : {0ull, 1ull, 2ull, 3ull, 16ull, 48000ull, ~0ull, u64{kOut}}) {
                    const hgp::Run r = pr_base(*m, base, c, Args{sx(rec), a1, sx(kOut + 0x100), sx(kOut + 0x200)}, seed++);
                    base.restore();
                    ++runs;
                    stops += r.stopped ? 1 : 0;
                }
        }
    }
    std::memset(m->mem.main_ram(), 0, EEMemory::kMainRamSize);
    MESSAGE(runs << " pairs from " << snaps << " snapshots (" << records << " records), " << stops << " stopped identically");
}

// Documented rules on the host, from the instructions (both bodies run and are compared, then the result checked).
// Only leaf bodies: nothing here depends on a callee's state.
TEST_CASE("game(libs14): hex-size, picture-size, frame-rate, work-size and seek rules") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const auto v0 = [](const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; };
    // sub_563D20: seven hex digits through the digit table 0x7B18F0 (the ELF's data).
    {
        const char text[] = "01A2F3C";
        std::memcpy(m->at(kWorld), text, 8);
        const Case& c = by_name("sub_563D20");
        const hgp::Run r = hgp::pair(*m, c.hand, c.recomp, Args{sx(kWorld), 0, 0, 0}, 1, c.name);
        CHECK_FALSE(r.stopped);
        CHECK(v0(r) == 0x01A2F3Cu);
    }
    // sub_570248: 720 x 480 (+ no extension bits), interlaced frame picture: columns 45, rows 2 * ((480 + 31) >> 5).
    {
        std::memset(m->at(kWorld), 0, 0x1000);
        w32(*m, kWorld + 4, 720);
        w32(*m, kWorld + 8, 480);
        w32(*m, kWorld + 72, 0);
        w32(*m, kWorld + 280, 3);
        const Case& c = by_name("sub_570248");
        CHECK_FALSE(hgp::pair(*m, c.hand, c.recomp, Args{sx(kWorld), 0, 0, 0}, 1, c.name).stopped);
        CHECK(r32(*m, kWorld + 4 * 177) == 720u);
        CHECK(r32(*m, kWorld + 4 * 179) == 45u);
        CHECK(r32(*m, kWorld + 4 * 180) == 30u);
        CHECK(r32(*m, kWorld + 4 * 237) == 720u);
        CHECK(r32(*m, kWorld + 4 * 238) == 480u);
        CHECK(r32(*m, kWorld + 4 * 240) == 240u);
        // progressive (+72 == 1): rows (h + 15) >> 4
        w32(*m, kWorld + 72, 1);
        hgp::pair(*m, c.hand, c.recomp, Args{sx(kWorld), 0, 0, 0}, 2, c.name);
        CHECK(r32(*m, kWorld + 4 * 180) == 30u);
    }
    // sub_59AD40: no rate index -> (0, 29970); index 1 -> (1000, 0x7CA2C0[1]).
    {
        std::memset(m->at(kWorld), 0, 0x1000);
        const Case& c = by_name("sub_59AD40");
        hgp::Run r = hgp::pair(*m, c.hand, c.recomp, Args{sx(kWorld), sx(kOut), sx(kOut + 4), 0}, 1, c.name);
        CHECK(v0(r) == 29970u);
        CHECK(r32(*m, kOut) == 0u);
        CHECK(r32(*m, kOut + 4) == 29970u);
        w32(*m, kWorld + 2336, 1);
        r = hgp::pair(*m, c.hand, c.recomp, Args{sx(kWorld), sx(kOut), sx(kOut + 4), 0}, 2, c.name);
        CHECK(r32(*m, kOut) == 1000u);
        CHECK(r32(*m, kOut + 4) == r32(*m, 0x7CA2C0u + 4));
    }
    // sub_59F8F8: format 0 -> two planes of w * h; 49 -> one; others none; returns 8h + 101 + the planes.
    {
        const Case& c = by_name("sub_59F8F8");
        for (const u32 fmt : {0u, 49u, 65u, 7u}) {
            const u32 planes = fmt == 49u ? 1u : (fmt == 7u ? 0u : 2u);
            const hgp::Run r = hgp::pair(*m, c.hand, c.recomp, Args{64, 32, fmt, sx(kOut)}, fmt + 1, c.name, [] {
                HwCheck hw;
                hw.gpr_in = {{8, kOut + 4}, {9, kOut + 8}};  // $t0 / $t1: the fifth and sixth arguments
                return hw;
            }());
            CHECK(r32(*m, kOut) == 8u * 32u + 8u);
            CHECK(v0(r) == 8u * 32u + 101u + planes * 64u * 32u);
        }
    }
    // rfpfs_parentSeek: a negative lba is refused with -100 before any seek.
    {
        const Case& c = by_name("rfpfs_parentSeek");
        const hgp::Run r = hgp::pair(*m, c.hand, c.recomp, Args{sx(kWorld), sx(0xFFFFFFFFu), 2048, 0}, 1, c.name);
        CHECK_FALSE(r.stopped);
        CHECK(v0(r) == sx(static_cast<u32>(-100)));
    }
    // sub_5A0BB0: 1 when either float is nonzero.
    {
        std::memset(m->at(kWorld), 0, 0x100);
        const Case& c = by_name("sub_5A0BB0");
        CHECK(v0(hgp::pair(*m, c.hand, c.recomp, Args{sx(kWorld), 0, 0, 0}, 1, c.name)) == 0u);
        const float one = 1.0f;
        std::memcpy(m->at(kWorld + 64), &one, 4);
        CHECK(v0(hgp::pair(*m, c.hand, c.recomp, Args{sx(kWorld), 0, 0, 0}, 2, c.name)) == 1u);
    }
}

#else

TEST_CASE("game(libs14): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
