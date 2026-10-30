// Pair tests for slice libs21 (ROFS front ends, MPV start-code copy, MWSFD finish, MWPLY accessors / setters): every
// hand body against its recompiled body, compared by tests/game/handgen_pairs.h -- the whole register file and cycle
// count at every check point and at the return / stop, all 32 MiB of RAM (the dead stack included), the scratchpad,
// the BIOS window and the bus log -- with the stand-in call logs equal. Worlds: random ones, the replay snapshots'
// RAM, live / unused / null players, the ROFS interface installed or not, and a disc movie's bytes; plus documented
// rules checked on the host.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/libs21.h"
#include "p3fes/game/libs5.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <memory>
#include <random>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_sceLibgcc32GetErxEntries_9_00565720(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_9_00565720__recomp(EEContext&);  // recompiled
void fn_sub_565788_00565788(EEContext&);  // generated body
void fn_sub_565788_00565788__recomp(EEContext&);  // recompiled
void fn_ROFS_Finish_00566320(EEContext&);  // generated body
void fn_ROFS_Finish_00566320__recomp(EEContext&);  // recompiled
void fn_ROFS_SetPfsFuncTbl_00566368(EEContext&);  // generated body
void fn_ROFS_SetPfsFuncTbl_00566368__recomp(EEContext&);  // recompiled
void fn_sub_566568_00566568(EEContext&);  // generated body
void fn_sub_566568_00566568__recomp(EEContext&);  // recompiled
void fn_ROFS_OpenRange_00566650(EEContext&);  // generated body
void fn_ROFS_OpenRange_00566650__recomp(EEContext&);  // recompiled
void fn_sub_566B88_00566b88(EEContext&);  // generated body
void fn_sub_566B88_00566b88__recomp(EEContext&);  // recompiled
void fn_sub_566D98_00566d98(EEContext&);  // generated body
void fn_sub_566D98_00566d98__recomp(EEContext&);  // recompiled
void fn_sub_566E18_00566e18(EEContext&);  // generated body
void fn_sub_566E18_00566e18__recomp(EEContext&);  // recompiled
void fn_sub_566E98_00566e98(EEContext&);  // generated body
void fn_sub_566E98_00566e98__recomp(EEContext&);  // recompiled
void fn_sub_578268_00578268(EEContext&);  // generated body
void fn_sub_578268_00578268__recomp(EEContext&);  // recompiled
void fn_sub_57FB20_0057fb20(EEContext&);  // generated body
void fn_sub_57FB20_0057fb20__recomp(EEContext&);  // recompiled
void fn___errno_12_00580010(EEContext&);  // generated body
void fn___errno_12_00580010__recomp(EEContext&);  // recompiled
void fn_sub_580020_00580020(EEContext&);  // generated body
void fn_sub_580020_00580020__recomp(EEContext&);  // recompiled
void fn_sub_580048_00580048(EEContext&);  // generated body
void fn_sub_580048_00580048__recomp(EEContext&);  // recompiled
void fn_sub_580068_00580068(EEContext&);  // generated body
void fn_sub_580068_00580068__recomp(EEContext&);  // recompiled
void fn_sub_5800B8_005800b8(EEContext&);  // generated body
void fn_sub_5800B8_005800b8__recomp(EEContext&);  // recompiled
void fn_sub_580170_00580170(EEContext&);  // generated body
void fn_sub_580170_00580170__recomp(EEContext&);  // recompiled
void fn_sub_5801D0_005801d0(EEContext&);  // generated body
void fn_sub_5801D0_005801d0__recomp(EEContext&);  // recompiled
void fn_sub_580200_00580200(EEContext&);  // generated body
void fn_sub_580200_00580200__recomp(EEContext&);  // recompiled
void fn_sub_580258_00580258(EEContext&);  // generated body
void fn_sub_580258_00580258__recomp(EEContext&);  // recompiled
void fn_sub_580498_00580498(EEContext&);  // generated body
void fn_sub_580498_00580498__recomp(EEContext&);  // recompiled
void fn_sub_5806D0_005806d0(EEContext&);  // generated body
void fn_sub_5806D0_005806d0__recomp(EEContext&);  // recompiled
void fn_sub_580878_00580878(EEContext&);  // generated body
void fn_sub_580878_00580878__recomp(EEContext&);  // recompiled
void fn_sub_580B10_00580b10(EEContext&);  // generated body
void fn_sub_580B10_00580b10__recomp(EEContext&);  // recompiled
void fn_sub_580B60_00580b60(EEContext&);  // generated body
void fn_sub_580B60_00580b60__recomp(EEContext&);  // recompiled
void fn_WTLS_set_table_0_00580e00(EEContext&);  // generated body
void fn_WTLS_set_table_0_00580e00__recomp(EEContext&);  // recompiled
void fn_sceInsockSetErrnoMode_0_00581050(EEContext&);  // generated body
void fn_sceInsockSetErrnoMode_0_00581050__recomp(EEContext&);  // recompiled
void fn_sceInsockGetErrnoMode_0_00581060(EEContext&);  // generated body
void fn_sceInsockGetErrnoMode_0_00581060__recomp(EEContext&);  // recompiled
void fn_sub_5810B8_005810b8(EEContext&);  // generated body
void fn_sub_5810B8_005810b8__recomp(EEContext&);  // recompiled
void fn_sub_581150_00581150(EEContext&);  // generated body
void fn_sub_581150_00581150__recomp(EEContext&);  // recompiled
void fn_sub_5811B0_005811b0(EEContext&);  // generated body
void fn_sub_5811B0_005811b0__recomp(EEContext&);  // recompiled
void fn_sub_581220_00581220(EEContext&);  // generated body
void fn_sub_581220_00581220__recomp(EEContext&);  // recompiled
void fn_sub_581350_00581350(EEContext&);  // generated body
void fn_sub_581350_00581350__recomp(EEContext&);  // recompiled
void fn_sub_5813F8_005813f8(EEContext&);  // generated body
void fn_sub_5813F8_005813f8__recomp(EEContext&);  // recompiled
void fn_sub_581480_00581480(EEContext&);  // generated body
void fn_sub_581480_00581480__recomp(EEContext&);  // recompiled
void fn_sub_5814B8_005814b8(EEContext&);  // generated body
void fn_sub_5814B8_005814b8__recomp(EEContext&);  // recompiled
void fn_sub_581510_00581510(EEContext&);  // generated body
void fn_sub_581510_00581510__recomp(EEContext&);  // recompiled
void fn_sub_581598_00581598(EEContext&);  // generated body
void fn_sub_581598_00581598__recomp(EEContext&);  // recompiled
void fn_sub_5815D0_005815d0(EEContext&);  // generated body
void fn_sub_5815D0_005815d0__recomp(EEContext&);  // recompiled
void fn_sub_5816B8_005816b8(EEContext&);  // generated body
void fn_sub_5816B8_005816b8__recomp(EEContext&);  // recompiled
void fn_sub_5816E8_005816e8(EEContext&);  // generated body
void fn_sub_5816E8_005816e8__recomp(EEContext&);  // recompiled
void fn_sub_581730_00581730(EEContext&);  // generated body
void fn_sub_581730_00581730__recomp(EEContext&);  // recompiled
void fn_sub_581748_00581748(EEContext&);  // generated body
void fn_sub_581748_00581748__recomp(EEContext&);  // recompiled
void fn___sceInsockHErrnoLoc_0_00581760(EEContext&);  // generated body
void fn___sceInsockHErrnoLoc_0_00581760__recomp(EEContext&);  // recompiled
void fn_sub_581778_00581778(EEContext&);  // generated body
void fn_sub_581778_00581778__recomp(EEContext&);  // recompiled
void fn_sub_5817B0_005817b0(EEContext&);  // generated body
void fn_sub_5817B0_005817b0__recomp(EEContext&);  // recompiled
void fn_sub_5817C0_005817c0(EEContext&);  // generated body
void fn_sub_5817C0_005817c0__recomp(EEContext&);  // recompiled
void fn_sub_5817C8_005817c8(EEContext&);  // generated body
void fn_sub_5817C8_005817c8__recomp(EEContext&);  // recompiled
void fn_sub_5818D8_005818d8(EEContext&);  // generated body
void fn_sub_5818D8_005818d8__recomp(EEContext&);  // recompiled
void fn_sub_581930_00581930(EEContext&);  // generated body
void fn_sub_581930_00581930__recomp(EEContext&);  // recompiled
void fn_sub_581A90_00581a90(EEContext&);  // generated body
void fn_sub_581A90_00581a90__recomp(EEContext&);  // recompiled
void fn_sub_581B38_00581b38(EEContext&);  // generated body
void fn_sub_581B38_00581b38__recomp(EEContext&);  // recompiled
void fn_sub_581BB0_00581bb0(EEContext&);  // generated body
void fn_sub_581BB0_00581bb0__recomp(EEContext&);  // recompiled
void fn_sub_581C08_00581c08(EEContext&);  // generated body
void fn_sub_581C08_00581c08__recomp(EEContext&);  // recompiled
void fn_sceInsockSetSendTimeout_0_00581c38(EEContext&);  // generated body
void fn_sceInsockSetSendTimeout_0_00581c38__recomp(EEContext&);  // recompiled
void fn_sub_581D08_00581d08(EEContext&);  // generated body
void fn_sub_581D08_00581d08__recomp(EEContext&);  // recompiled
void fn_sceInsockAbort_0_00581d38(EEContext&);  // generated body
void fn_sceInsockAbort_0_00581d38__recomp(EEContext&);  // recompiled
void fn_sub_581D68_00581d68(EEContext&);  // generated body
void fn_sub_581D68_00581d68__recomp(EEContext&);  // recompiled
void fn_sub_581DD8_00581dd8(EEContext&);  // generated body
void fn_sub_581DD8_00581dd8__recomp(EEContext&);  // recompiled
void fn_sub_581E58_00581e58(EEContext&);  // generated body
void fn_sub_581E58_00581e58__recomp(EEContext&);  // recompiled
void fn_sub_581EC8_00581ec8(EEContext&);  // generated body
void fn_sub_581EC8_00581ec8__recomp(EEContext&);  // recompiled
void fn_sub_581F48_00581f48(EEContext&);  // generated body
void fn_sub_581F48_00581f48__recomp(EEContext&);  // recompiled
void fn_sub_581F90_00581f90(EEContext&);  // generated body
void fn_sub_581F90_00581f90__recomp(EEContext&);  // recompiled
void fn_sub_581FD0_00581fd0(EEContext&);  // generated body
void fn_sub_581FD0_00581fd0__recomp(EEContext&);  // recompiled
void fn_sub_582008_00582008(EEContext&);  // generated body
void fn_sub_582008_00582008__recomp(EEContext&);  // recompiled
void fn_sub_582098_00582098(EEContext&);  // generated body
void fn_sub_582098_00582098__recomp(EEContext&);  // recompiled
void fn_sub_582168_00582168(EEContext&);  // generated body
void fn_sub_582168_00582168__recomp(EEContext&);  // recompiled
void fn_sub_582258_00582258(EEContext&);  // generated body
void fn_sub_582258_00582258__recomp(EEContext&);  // recompiled
void fn_sceInsockConnect_0_00582350(EEContext&);  // generated body
void fn_sceInsockConnect_0_00582350__recomp(EEContext&);  // recompiled
void fn_sub_5823A8_005823a8(EEContext&);  // generated body
void fn_sub_5823A8_005823a8__recomp(EEContext&);  // recompiled
void fn_sub_5823D8_005823d8(EEContext&);  // generated body
void fn_sub_5823D8_005823d8__recomp(EEContext&);  // recompiled
void fn_sub_582440_00582440(EEContext&);  // generated body
void fn_sub_582440_00582440__recomp(EEContext&);  // recompiled
void fn_sub_5824B0_005824b0(EEContext&);  // generated body
void fn_sub_5824B0_005824b0__recomp(EEContext&);  // recompiled
void fn_sub_582558_00582558(EEContext&);  // generated body
void fn_sub_582558_00582558__recomp(EEContext&);  // recompiled
void fn_sub_582578_00582578(EEContext&);  // generated body
void fn_sub_582578_00582578__recomp(EEContext&);  // recompiled
void fn_add_listen_0_00582598(EEContext&);  // generated body
void fn_add_listen_0_00582598__recomp(EEContext&);  // recompiled
void fn_sub_5825B8_005825b8(EEContext&);  // generated body
void fn_sub_5825B8_005825b8__recomp(EEContext&);  // recompiled
void fn_sub_5825D8_005825d8(EEContext&);  // generated body
void fn_sub_5825D8_005825d8__recomp(EEContext&);  // recompiled
void fn_sub_5825F8_005825f8(EEContext&);  // generated body
void fn_sub_5825F8_005825f8__recomp(EEContext&);  // recompiled
void fn_sub_582640_00582640(EEContext&);  // generated body
void fn_sub_582640_00582640__recomp(EEContext&);  // recompiled
void fn_sub_582688_00582688(EEContext&);  // generated body
void fn_sub_582688_00582688__recomp(EEContext&);  // recompiled
void fn_sub_5826D0_005826d0(EEContext&);  // generated body
void fn_sub_5826D0_005826d0__recomp(EEContext&);  // recompiled
void fn_sub_582718_00582718(EEContext&);  // generated body
void fn_sub_582718_00582718__recomp(EEContext&);  // recompiled
void fn_sub_582730_00582730(EEContext&);  // generated body
void fn_sub_582730_00582730__recomp(EEContext&);  // recompiled
void fn_sub_582770_00582770(EEContext&);  // generated body
void fn_sub_582770_00582770__recomp(EEContext&);  // recompiled
void fn_sub_582830_00582830(EEContext&);  // generated body
void fn_sub_582830_00582830__recomp(EEContext&);  // recompiled
void fn_sub_582D98_00582d98(EEContext&);  // generated body
void fn_sub_582D98_00582d98__recomp(EEContext&);  // recompiled
void fn_sub_582DB0_00582db0(EEContext&);  // generated body
void fn_sub_582DB0_00582db0__recomp(EEContext&);  // recompiled
void fn_sub_582DC8_00582dc8(EEContext&);  // generated body
void fn_sub_582DC8_00582dc8__recomp(EEContext&);  // recompiled
void fn_sub_582E78_00582e78(EEContext&);  // generated body
void fn_sub_582E78_00582e78__recomp(EEContext&);  // recompiled
void fn_sub_582F28_00582f28(EEContext&);  // generated body
void fn_sub_582F28_00582f28__recomp(EEContext&);  // recompiled
void fn_sub_5830D0_005830d0(EEContext&);  // generated body
void fn_sub_5830D0_005830d0__recomp(EEContext&);  // recompiled
void fn_sub_583238_00583238(EEContext&);  // generated body
void fn_sub_583238_00583238__recomp(EEContext&);  // recompiled
void fn_sub_5832A8_005832a8(EEContext&);  // generated body
void fn_sub_5832A8_005832a8__recomp(EEContext&);  // recompiled
void fn_sub_583308_00583308(EEContext&);  // generated body
void fn_sub_583308_00583308__recomp(EEContext&);  // recompiled
void fn_sub_583378_00583378(EEContext&);  // generated body
void fn_sub_583378_00583378__recomp(EEContext&);  // recompiled
void fn_sub_583550_00583550(EEContext&);  // generated body
void fn_sub_583550_00583550__recomp(EEContext&);  // recompiled
void fn_sub_583740_00583740(EEContext&);  // generated body
void fn_sub_583740_00583740__recomp(EEContext&);  // recompiled
void fn_sub_5838A8_005838a8(EEContext&);  // generated body
void fn_sub_5838A8_005838a8__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sceLibgcc32GetErxEntries_9", 0x565720, &recomp_gen::fn_sceLibgcc32GetErxEntries_9_00565720, &recomp_gen::fn_sceLibgcc32GetErxEntries_9_00565720__recomp},
    {"sub_565788", 0x565788, &recomp_gen::fn_sub_565788_00565788, &recomp_gen::fn_sub_565788_00565788__recomp},
    {"ROFS_Finish", 0x566320, &recomp_gen::fn_ROFS_Finish_00566320, &recomp_gen::fn_ROFS_Finish_00566320__recomp},
    {"ROFS_SetPfsFuncTbl", 0x566368, &recomp_gen::fn_ROFS_SetPfsFuncTbl_00566368, &recomp_gen::fn_ROFS_SetPfsFuncTbl_00566368__recomp},
    {"sub_566568", 0x566568, &recomp_gen::fn_sub_566568_00566568, &recomp_gen::fn_sub_566568_00566568__recomp},
    {"ROFS_OpenRange", 0x566650, &recomp_gen::fn_ROFS_OpenRange_00566650, &recomp_gen::fn_ROFS_OpenRange_00566650__recomp},
    {"sub_566B88", 0x566B88, &recomp_gen::fn_sub_566B88_00566b88, &recomp_gen::fn_sub_566B88_00566b88__recomp},
    {"sub_566D98", 0x566D98, &recomp_gen::fn_sub_566D98_00566d98, &recomp_gen::fn_sub_566D98_00566d98__recomp},
    {"sub_566E18", 0x566E18, &recomp_gen::fn_sub_566E18_00566e18, &recomp_gen::fn_sub_566E18_00566e18__recomp},
    {"sub_566E98", 0x566E98, &recomp_gen::fn_sub_566E98_00566e98, &recomp_gen::fn_sub_566E98_00566e98__recomp},
    {"sub_578268", 0x578268, &recomp_gen::fn_sub_578268_00578268, &recomp_gen::fn_sub_578268_00578268__recomp},
    {"sub_57FB20", 0x57FB20, &recomp_gen::fn_sub_57FB20_0057fb20, &recomp_gen::fn_sub_57FB20_0057fb20__recomp},
    {"__errno_12", 0x580010, &recomp_gen::fn___errno_12_00580010, &recomp_gen::fn___errno_12_00580010__recomp},
    {"sub_580020", 0x580020, &recomp_gen::fn_sub_580020_00580020, &recomp_gen::fn_sub_580020_00580020__recomp},
    {"sub_580048", 0x580048, &recomp_gen::fn_sub_580048_00580048, &recomp_gen::fn_sub_580048_00580048__recomp},
    {"sub_580068", 0x580068, &recomp_gen::fn_sub_580068_00580068, &recomp_gen::fn_sub_580068_00580068__recomp},
    {"sub_5800B8", 0x5800B8, &recomp_gen::fn_sub_5800B8_005800b8, &recomp_gen::fn_sub_5800B8_005800b8__recomp},
    {"sub_580170", 0x580170, &recomp_gen::fn_sub_580170_00580170, &recomp_gen::fn_sub_580170_00580170__recomp},
    {"sub_5801D0", 0x5801D0, &recomp_gen::fn_sub_5801D0_005801d0, &recomp_gen::fn_sub_5801D0_005801d0__recomp},
    {"sub_580200", 0x580200, &recomp_gen::fn_sub_580200_00580200, &recomp_gen::fn_sub_580200_00580200__recomp},
    {"sub_580258", 0x580258, &recomp_gen::fn_sub_580258_00580258, &recomp_gen::fn_sub_580258_00580258__recomp},
    {"sub_580498", 0x580498, &recomp_gen::fn_sub_580498_00580498, &recomp_gen::fn_sub_580498_00580498__recomp},
    {"sub_5806D0", 0x5806D0, &recomp_gen::fn_sub_5806D0_005806d0, &recomp_gen::fn_sub_5806D0_005806d0__recomp},
    {"sub_580878", 0x580878, &recomp_gen::fn_sub_580878_00580878, &recomp_gen::fn_sub_580878_00580878__recomp},
    {"sub_580B10", 0x580B10, &recomp_gen::fn_sub_580B10_00580b10, &recomp_gen::fn_sub_580B10_00580b10__recomp},
    {"sub_580B60", 0x580B60, &recomp_gen::fn_sub_580B60_00580b60, &recomp_gen::fn_sub_580B60_00580b60__recomp},
    {"WTLS_set_table_0", 0x580E00, &recomp_gen::fn_WTLS_set_table_0_00580e00, &recomp_gen::fn_WTLS_set_table_0_00580e00__recomp},
    {"sceInsockSetErrnoMode_0", 0x581050, &recomp_gen::fn_sceInsockSetErrnoMode_0_00581050, &recomp_gen::fn_sceInsockSetErrnoMode_0_00581050__recomp},
    {"sceInsockGetErrnoMode_0", 0x581060, &recomp_gen::fn_sceInsockGetErrnoMode_0_00581060, &recomp_gen::fn_sceInsockGetErrnoMode_0_00581060__recomp},
    {"sub_5810B8", 0x5810B8, &recomp_gen::fn_sub_5810B8_005810b8, &recomp_gen::fn_sub_5810B8_005810b8__recomp},
    {"sub_581150", 0x581150, &recomp_gen::fn_sub_581150_00581150, &recomp_gen::fn_sub_581150_00581150__recomp},
    {"sub_5811B0", 0x5811B0, &recomp_gen::fn_sub_5811B0_005811b0, &recomp_gen::fn_sub_5811B0_005811b0__recomp},
    {"sub_581220", 0x581220, &recomp_gen::fn_sub_581220_00581220, &recomp_gen::fn_sub_581220_00581220__recomp},
    {"sub_581350", 0x581350, &recomp_gen::fn_sub_581350_00581350, &recomp_gen::fn_sub_581350_00581350__recomp},
    {"sub_5813F8", 0x5813F8, &recomp_gen::fn_sub_5813F8_005813f8, &recomp_gen::fn_sub_5813F8_005813f8__recomp},
    {"sub_581480", 0x581480, &recomp_gen::fn_sub_581480_00581480, &recomp_gen::fn_sub_581480_00581480__recomp},
    {"sub_5814B8", 0x5814B8, &recomp_gen::fn_sub_5814B8_005814b8, &recomp_gen::fn_sub_5814B8_005814b8__recomp},
    {"sub_581510", 0x581510, &recomp_gen::fn_sub_581510_00581510, &recomp_gen::fn_sub_581510_00581510__recomp},
    {"sub_581598", 0x581598, &recomp_gen::fn_sub_581598_00581598, &recomp_gen::fn_sub_581598_00581598__recomp},
    {"sub_5815D0", 0x5815D0, &recomp_gen::fn_sub_5815D0_005815d0, &recomp_gen::fn_sub_5815D0_005815d0__recomp},
    {"sub_5816B8", 0x5816B8, &recomp_gen::fn_sub_5816B8_005816b8, &recomp_gen::fn_sub_5816B8_005816b8__recomp},
    {"sub_5816E8", 0x5816E8, &recomp_gen::fn_sub_5816E8_005816e8, &recomp_gen::fn_sub_5816E8_005816e8__recomp},
    {"sub_581730", 0x581730, &recomp_gen::fn_sub_581730_00581730, &recomp_gen::fn_sub_581730_00581730__recomp},
    {"sub_581748", 0x581748, &recomp_gen::fn_sub_581748_00581748, &recomp_gen::fn_sub_581748_00581748__recomp},
    {"__sceInsockHErrnoLoc_0", 0x581760, &recomp_gen::fn___sceInsockHErrnoLoc_0_00581760, &recomp_gen::fn___sceInsockHErrnoLoc_0_00581760__recomp},
    {"sub_581778", 0x581778, &recomp_gen::fn_sub_581778_00581778, &recomp_gen::fn_sub_581778_00581778__recomp},
    {"sub_5817B0", 0x5817B0, &recomp_gen::fn_sub_5817B0_005817b0, &recomp_gen::fn_sub_5817B0_005817b0__recomp},
    {"sub_5817C0", 0x5817C0, &recomp_gen::fn_sub_5817C0_005817c0, &recomp_gen::fn_sub_5817C0_005817c0__recomp},
    {"sub_5817C8", 0x5817C8, &recomp_gen::fn_sub_5817C8_005817c8, &recomp_gen::fn_sub_5817C8_005817c8__recomp},
    {"sub_5818D8", 0x5818D8, &recomp_gen::fn_sub_5818D8_005818d8, &recomp_gen::fn_sub_5818D8_005818d8__recomp},
    {"sub_581930", 0x581930, &recomp_gen::fn_sub_581930_00581930, &recomp_gen::fn_sub_581930_00581930__recomp},
    {"sub_581A90", 0x581A90, &recomp_gen::fn_sub_581A90_00581a90, &recomp_gen::fn_sub_581A90_00581a90__recomp},
    {"sub_581B38", 0x581B38, &recomp_gen::fn_sub_581B38_00581b38, &recomp_gen::fn_sub_581B38_00581b38__recomp},
    {"sub_581BB0", 0x581BB0, &recomp_gen::fn_sub_581BB0_00581bb0, &recomp_gen::fn_sub_581BB0_00581bb0__recomp},
    {"sub_581C08", 0x581C08, &recomp_gen::fn_sub_581C08_00581c08, &recomp_gen::fn_sub_581C08_00581c08__recomp},
    {"sceInsockSetSendTimeout_0", 0x581C38, &recomp_gen::fn_sceInsockSetSendTimeout_0_00581c38, &recomp_gen::fn_sceInsockSetSendTimeout_0_00581c38__recomp},
    {"sub_581D08", 0x581D08, &recomp_gen::fn_sub_581D08_00581d08, &recomp_gen::fn_sub_581D08_00581d08__recomp},
    {"sceInsockAbort_0", 0x581D38, &recomp_gen::fn_sceInsockAbort_0_00581d38, &recomp_gen::fn_sceInsockAbort_0_00581d38__recomp},
    {"sub_581D68", 0x581D68, &recomp_gen::fn_sub_581D68_00581d68, &recomp_gen::fn_sub_581D68_00581d68__recomp},
    {"sub_581DD8", 0x581DD8, &recomp_gen::fn_sub_581DD8_00581dd8, &recomp_gen::fn_sub_581DD8_00581dd8__recomp},
    {"sub_581E58", 0x581E58, &recomp_gen::fn_sub_581E58_00581e58, &recomp_gen::fn_sub_581E58_00581e58__recomp},
    {"sub_581EC8", 0x581EC8, &recomp_gen::fn_sub_581EC8_00581ec8, &recomp_gen::fn_sub_581EC8_00581ec8__recomp},
    {"sub_581F48", 0x581F48, &recomp_gen::fn_sub_581F48_00581f48, &recomp_gen::fn_sub_581F48_00581f48__recomp},
    {"sub_581F90", 0x581F90, &recomp_gen::fn_sub_581F90_00581f90, &recomp_gen::fn_sub_581F90_00581f90__recomp},
    {"sub_581FD0", 0x581FD0, &recomp_gen::fn_sub_581FD0_00581fd0, &recomp_gen::fn_sub_581FD0_00581fd0__recomp},
    {"sub_582008", 0x582008, &recomp_gen::fn_sub_582008_00582008, &recomp_gen::fn_sub_582008_00582008__recomp},
    {"sub_582098", 0x582098, &recomp_gen::fn_sub_582098_00582098, &recomp_gen::fn_sub_582098_00582098__recomp},
    {"sub_582168", 0x582168, &recomp_gen::fn_sub_582168_00582168, &recomp_gen::fn_sub_582168_00582168__recomp},
    {"sub_582258", 0x582258, &recomp_gen::fn_sub_582258_00582258, &recomp_gen::fn_sub_582258_00582258__recomp},
    {"sceInsockConnect_0", 0x582350, &recomp_gen::fn_sceInsockConnect_0_00582350, &recomp_gen::fn_sceInsockConnect_0_00582350__recomp},
    {"sub_5823A8", 0x5823A8, &recomp_gen::fn_sub_5823A8_005823a8, &recomp_gen::fn_sub_5823A8_005823a8__recomp},
    {"sub_5823D8", 0x5823D8, &recomp_gen::fn_sub_5823D8_005823d8, &recomp_gen::fn_sub_5823D8_005823d8__recomp},
    {"sub_582440", 0x582440, &recomp_gen::fn_sub_582440_00582440, &recomp_gen::fn_sub_582440_00582440__recomp},
    {"sub_5824B0", 0x5824B0, &recomp_gen::fn_sub_5824B0_005824b0, &recomp_gen::fn_sub_5824B0_005824b0__recomp},
    {"sub_582558", 0x582558, &recomp_gen::fn_sub_582558_00582558, &recomp_gen::fn_sub_582558_00582558__recomp},
    {"sub_582578", 0x582578, &recomp_gen::fn_sub_582578_00582578, &recomp_gen::fn_sub_582578_00582578__recomp},
    {"add_listen_0", 0x582598, &recomp_gen::fn_add_listen_0_00582598, &recomp_gen::fn_add_listen_0_00582598__recomp},
    {"sub_5825B8", 0x5825B8, &recomp_gen::fn_sub_5825B8_005825b8, &recomp_gen::fn_sub_5825B8_005825b8__recomp},
    {"sub_5825D8", 0x5825D8, &recomp_gen::fn_sub_5825D8_005825d8, &recomp_gen::fn_sub_5825D8_005825d8__recomp},
    {"sub_5825F8", 0x5825F8, &recomp_gen::fn_sub_5825F8_005825f8, &recomp_gen::fn_sub_5825F8_005825f8__recomp},
    {"sub_582640", 0x582640, &recomp_gen::fn_sub_582640_00582640, &recomp_gen::fn_sub_582640_00582640__recomp},
    {"sub_582688", 0x582688, &recomp_gen::fn_sub_582688_00582688, &recomp_gen::fn_sub_582688_00582688__recomp},
    {"sub_5826D0", 0x5826D0, &recomp_gen::fn_sub_5826D0_005826d0, &recomp_gen::fn_sub_5826D0_005826d0__recomp},
    {"sub_582718", 0x582718, &recomp_gen::fn_sub_582718_00582718, &recomp_gen::fn_sub_582718_00582718__recomp},
    {"sub_582730", 0x582730, &recomp_gen::fn_sub_582730_00582730, &recomp_gen::fn_sub_582730_00582730__recomp},
    {"sub_582770", 0x582770, &recomp_gen::fn_sub_582770_00582770, &recomp_gen::fn_sub_582770_00582770__recomp},
    {"sub_582830", 0x582830, &recomp_gen::fn_sub_582830_00582830, &recomp_gen::fn_sub_582830_00582830__recomp},
    {"sub_582D98", 0x582D98, &recomp_gen::fn_sub_582D98_00582d98, &recomp_gen::fn_sub_582D98_00582d98__recomp},
    {"sub_582DB0", 0x582DB0, &recomp_gen::fn_sub_582DB0_00582db0, &recomp_gen::fn_sub_582DB0_00582db0__recomp},
    {"sub_582DC8", 0x582DC8, &recomp_gen::fn_sub_582DC8_00582dc8, &recomp_gen::fn_sub_582DC8_00582dc8__recomp},
    {"sub_582E78", 0x582E78, &recomp_gen::fn_sub_582E78_00582e78, &recomp_gen::fn_sub_582E78_00582e78__recomp},
    {"sub_582F28", 0x582F28, &recomp_gen::fn_sub_582F28_00582f28, &recomp_gen::fn_sub_582F28_00582f28__recomp},
    {"sub_5830D0", 0x5830D0, &recomp_gen::fn_sub_5830D0_005830d0, &recomp_gen::fn_sub_5830D0_005830d0__recomp},
    {"sub_583238", 0x583238, &recomp_gen::fn_sub_583238_00583238, &recomp_gen::fn_sub_583238_00583238__recomp},
    {"sub_5832A8", 0x5832A8, &recomp_gen::fn_sub_5832A8_005832a8, &recomp_gen::fn_sub_5832A8_005832a8__recomp},
    {"sub_583308", 0x583308, &recomp_gen::fn_sub_583308_00583308, &recomp_gen::fn_sub_583308_00583308__recomp},
    {"sub_583378", 0x583378, &recomp_gen::fn_sub_583378_00583378, &recomp_gen::fn_sub_583378_00583378__recomp},
    {"sub_583550", 0x583550, &recomp_gen::fn_sub_583550_00583550, &recomp_gen::fn_sub_583550_00583550__recomp},
    {"sub_583740", 0x583740, &recomp_gen::fn_sub_583740_00583740, &recomp_gen::fn_sub_583740_00583740__recomp},
    {"sub_5838A8", 0x5838A8, &recomp_gen::fn_sub_5838A8_005838a8, &recomp_gen::fn_sub_5838A8_005838a8__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena. Random worlds fill all of it; the live worlds below lay a
// player (MWPLY handle) and its SFD / SFX / ADXT / loop-play records, a ROFS interface table and two output records
// into it.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 48;

constexpr u32 kPly = kWorld;              // the player (684 bytes)
constexpr u32 kSfx = kWorld + 0x1000u;    // its SFX handle
constexpr u32 kAdxt = kWorld + 0x1400u;   // its ADXT handle
constexpr u32 kLsc = kWorld + 0x1800u;    // its loop-play list
constexpr u32 kOut = kWorld + 0x2000u;    // an output record ($a1)
constexpr u32 kOut2 = kWorld + 0x2400u;   // another ($a2)
constexpr u32 kSjVt = kWorld + 0x2800u;   // an SJ object and its vtable (mwPlyStartMem's jalr)
constexpr u32 kRofsTbl = kWorld + 0x3800u;  // a ROFS interface (each slot a non-leaf body)
constexpr u32 kSfd = kWorld + 0x4000u;    // its SFD handle (records up to +13916)
constexpr u32 kRofsIf = 0x7B26F8u;        // the installed ROFS interface (0 = none)
constexpr u32 kMwsfdWork = 0x7B2F50u;     // MWSFD work: +52 the word sub_580020 / sub_580048 set / get
constexpr u32 kMwsfdInit = 0x7B2F48u;     // MWSFD init count (mwPlyFinish)
// A non-leaf body for the jalr calls: it spills $ra below the $sp it receives (the dead stack is compared).
constexpr u32 kNonLeaf = 0x580048u;
constexpr u32 kErr = 0x585590u;           // MWSFD error report (recorded)

u32 r32(Machine& m, u32 va) {
    u32 v = 0;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }

const Case& by_addr(u32 addr) {
    for (const Case& c : kCases)
        if (c.addr == addr) return c;
    FAIL("no case " << std::hex << addr);
    return kCases[0];
}

// Recorders for the callees the bodies meet that this build does not emit and no current packet claims (each is
// already stood in by another slice's test): the MWSFD error report, the SFD / SFX / LSC calls the accessors forward
// to, the player destroy / server start and the last-error setter. Each logs its call and returns 0; both bodies of a
// pair get a fresh set and their call logs must be equal. Callees libs14 / libs16 / libs17 claim are left alone: a
// pair meeting one stops there, identically, and no test below depends on that stop.
const u32 kRecorders[] = {kErr,      0x597968u, 0x599368u, 0x58C228u, 0x5994F0u, 0x55D668u, 0x5835F0u,
                          0x5837A0u, 0x53EC20u, 0x57DB58u, 0x57FC60u, 0x57C730u};
StandInWorld* g_si[2];
Fn g_fn[2];
bool g_set_f12 = false;
u32 g_f12 = 0;
void prime(EEContext& ctx) {
    if (g_set_f12) ctx.fpr[12] = g_f12;
}
void thunk0(EEContext& ctx) {
    StandInsScope s(g_si[0]->si);
    prime(ctx);
    g_fn[0](ctx);
}
void thunk1(EEContext& ctx) {
    StandInsScope s(g_si[1]->si);
    prime(ctx);
    g_fn[1](ctx);
}
// One pair with the recorders; `log` (when given) receives the hand body's call log.
hgp::Run spair(Machine& m, const Case& c, const Args& args, u32 seed, std::vector<StandInCall>* log = nullptr) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    for (StandInWorld* w : {wh.get(), wr.get()}) {
        w->si.clobber_scratch = true;
        for (u32 va : kRecorders) w->si.install_recorder(va, "recorded callee", 0, 3);
    }
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = c.hand;
    g_fn[1] = c.recomp;
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, c.name);
    expect_same_log(wh->si, wr->si, c.name);
    if (log) *log = wh->si.log;
    return r;
}
u64 v0_of(const hgp::Run& r) { return r.end.gpr[2].u64[0]; }
std::size_t errors_in(const std::vector<StandInCall>& log) {
    std::size_t n = 0;
    for (const StandInCall& c : log) n += c.va == kErr ? 1 : 0;
    return n;
}

void run_random(Machine& m, u32 seeds, const char* label) {
    const char* only = std::getenv("P3FES_HG_ONLY");  // one function by name (debugging)
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            if (trace) std::fprintf(stderr, "%s %s seed %u\n", label, c.name, seed);
            std::mt19937 rng{seed * 7919u + c.addr};
            hgp::random_world(m, kWorld, kWorldSize, rng);
            const Args args{hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize),
                            hgp::random_arg(rng, kWorld, kWorldSize), hgp::random_arg(rng, kWorld, kWorldSize)};
            stops += spair(m, c, args, seed).stopped ? 1 : 0;
        }
        const std::string summary = std::string(label) + " " + c.name + ": " + std::to_string(seeds) + " pairs, " +
                                    std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

// A live player: random bytes, then the fields the bodies read -- in use (+0 = 1), the SFD / ADXT / LSC / SFX handles,
// the creation parameters' first word (+8: 0, 1 or 2 = MPV), the AddInf SJ (+380) and record (+404), the read size
// (+456), the input SJ (+480) with a vtable whose slot +12 is a non-leaf body. The SFD handle's record pointer
// (+8060) goes to the LSC block so mwPlyGet{Audio,Video}ChInf read a real word.
void live_player(Machine& m, std::mt19937& rng, u32 kind) {
    hgp::random_world(m, kWorld, kWorldSize, rng);
    namespace ply = game::libs5::ply;
    w32(m, kPly + ply::kUsed, 1);
    w32(m, kPly + ply::kCprm, kind % 3);
    w32(m, kPly + ply::kSfd, kind % 5 == 4 ? 0 : kSfd);
    w32(m, kPly + ply::kAdxt, kind % 4 == 3 ? 0 : kAdxt);
    w32(m, kPly + ply::kLsc, kLsc);
    w32(m, kPly + ply::kSfx, kSfx);
    w32(m, kPly + ply::kAddInfSj, kind % 2 ? kSjVt : 0);
    w32(m, kPly + ply::kAddInf1, kind % 3 == 1 ? 1 : 0);
    w32(m, kPly + ply::kReadSize, 0x8000u + (rng() % 8) * 0x800u);
    w32(m, kPly + 480, kSjVt);
    w32(m, kSjVt, kSjVt + 0x40u);
    w32(m, kSjVt + 0x40u + 12, kNonLeaf);
    w32(m, kSfd + 8060, kLsc);
    w32(m, kLsc + 40, kind % 2 ? kAdxt : 0);
}

}  // namespace

TEST_CASE("game(libs21): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    run_random(*m, env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds, "random");
}

// The same over the RAM of the replay snapshots: the real globals (the ROFS interface 0x7B26F8, the MWSFD work and its
// eight players at 0x7B2FBC, the insock / WTLS words), with random worlds for the pointer arguments.
TEST_CASE("game(libs21): every body equals its recompiled body on the replay snapshots") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    for (const char* dir : {"dorm_replay_4900", "b_5800", "climb_ref_17000"}) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.size() != EEMemory::kMainRamSize) {
            MESSAGE("SKIP: snapshot " << dir << " not found");
            continue;
        }
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        run_random(*m, 4u, dir);
    }
}

// Every MWPLY body on a live player, an unused one (+0 = 0) and a null handle, with the arguments its branches test
// (modes 0..3 and -1, the 128 KiB AddInf bound, output records); the float-argument bodies with fixed $f12 values.
TEST_CASE("game(libs21): the MWPLY bodies on live, unused and null players") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const u32 kNoHandle[] = {0x580010u, 0x580020u, 0x580048u, 0x580E00u, 0x581050u, 0x581060u, 0x581760u, 0x5810B8u,
                             0x582730u, 0x582770u};
    const u64 kA1[] = {0, 1, 2, 3, ~0ull, 0x1FFFFu, 0x20000u, sx(kOut)};
    u32 seed = 1;
    int pairs = 0;
    for (const Case& c : kCases) {
        if (c.addr < 0x580020u || std::find(std::begin(kNoHandle), std::end(kNoHandle), c.addr) != std::end(kNoHandle))
            continue;
        for (u32 kind = 0; kind < 12; ++kind) {
            std::mt19937 rng{kind * 131u + c.addr};
            live_player(*m, rng, kind);
            const u32 h = kind == 10 ? 0u : kPly;
            if (kind == 11) w32(*m, kPly, 0);
            const Args args{sx(h), kA1[kind % 8], kind % 2 ? sx(kOut2) : u64(kind), kind % 3 ? sx(kOut) : 7u};
            spair(*m, c, args, seed++);
            ++pairs;
        }
    }
    for (u32 addr : {0x582350u, 0x5824B0u}) {
        for (float f : {1.0f, 0.5f, 1.2345f, -0.25f, 0.0f, 2.0005f}) {
            std::mt19937 rng{addr};
            live_player(*m, rng, 0);
            w32(*m, kPly + 12, 0x123456u);
            std::memcpy(&g_f12, &f, 4);
            g_set_f12 = true;
            spair(*m, by_addr(addr), Args{sx(kPly), 0, 0, 0}, seed++);
            g_set_f12 = false;
            ++pairs;
        }
    }
    MESSAGE("live players: " << pairs << " pairs");
}

// The ROFS front ends with an interface installed (every slot a non-leaf body, reached through jalr) and without one
// (the ROFS error path, sub_569730); ROFS_Finish drops the interface.
TEST_CASE("game(libs21): the ROFS front ends with and without an interface") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    u32 seed = 100;
    for (const Case& c : kCases) {
        if (c.addr < 0x566320u || c.addr > 0x566E98u) continue;
        for (int with = 0; with < 2; ++with) {
            std::mt19937 rng{c.addr + static_cast<u32>(with)};
            hgp::random_world(*m, kWorld, kWorldSize, rng);
            for (u32 k = 0; k < 32; ++k) w32(*m, kRofsTbl + 4 * k, kNonLeaf);
            w32(*m, kRofsIf, with ? kRofsTbl : 0u);
            spair(*m, c, Args{sx(kOut), 3, sx(kOut2), 0}, seed++);
            if (c.addr == 0x566320u) CHECK(r32(*m, kRofsIf) == 0u);  // ROFS_Finish: no interface afterwards
        }
    }
    w32(*m, kRofsIf, 0);
}

// Documented rules on the host: the setters' fields and the getters' results, the 128 KiB AddInf bound, the timer
// channel range, the insock / WTLS / MWSFD words, mwPlyFinish's count, and the MPV start-code copy on a disc movie.
TEST_CASE("game(libs21): setters, getters, bounds and the start-code copy") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    std::mt19937 rng{21};
    std::vector<StandInCall> log;
    // mwPlyFxSetOutZscale / Get and SetOutZoffset / Get: the SFX handle's +40 / +44.
    for (const auto& [set, get, off] : {std::tuple{0x583238u, 0x5832A8u, 40u}, std::tuple{0x583308u, 0x583378u, 44u}}) {
        live_player(*m, rng, 0);
        spair(*m, by_addr(set), Args{sx(kPly), 0x1234u, 0, 0}, 1, &log);
        CHECK(r32(*m, kSfx + off) == 0x1234u);
        CHECK(errors_in(log) == 0);
        CHECK(v0_of(spair(*m, by_addr(get), Args{sx(kPly), 0, 0, 0}, 2, &log)) == 0x1234u);
        w32(*m, kPly, 0);  // unused: the error report and 0
        CHECK(v0_of(spair(*m, by_addr(get), Args{sx(kPly), 0, 0, 0}, 3, &log)) == 0u);
        CHECK(errors_in(log) == 1);
    }
    // mwPlySetSfxHn / mwPlyGetSfxHn2: +168.
    live_player(*m, rng, 0);
    spair(*m, by_addr(0x582830u), Args{sx(kPly), sx(kOut), 0, 0}, 4);
    CHECK(r32(*m, kPly + 168) == kOut);
    CHECK(v0_of(spair(*m, by_addr(0x5817C0u), Args{sx(kPly), 0, 0, 0}, 5)) == sx(kOut));
    // mwPlyAttachAddInfBuf: +392 / +396 always; a size under 0x20000 is reported once.
    for (u32 size : {0x1FFFFu, 0x20000u, 0x40000u}) {
        live_player(*m, rng, 0);
        spair(*m, by_addr(0x583740u), Args{sx(kPly), sx(kOut), size, 0}, 6, &log);
        CHECK(r32(*m, kPly + 392) == kOut);
        CHECK(r32(*m, kPly + 396) == size);
        CHECK(errors_in(log) == (size < 0x20000u ? 1u : 0u));
    }
    // mwPlySetTimerCh: -1, 0, 1 are taken (no report), others reported.
    for (const auto& [ch, bad] : {std::pair{~0ull, 0u}, std::pair{0ull, 0u}, std::pair{1ull, 0u}, std::pair{2ull, 1u},
                                  std::pair{sx(0xFFFFFFFEu), 1u}}) {
        spair(*m, by_addr(0x582730u), Args{ch, 0, 0, 0}, 7, &log);
        CHECK(errors_in(log) == bad);
    }
    // The insock errno mode, the WTLS table, the MWSFD work word +52.
    spair(*m, by_addr(0x581050u), Args{0x55u, 0, 0, 0}, 8);
    CHECK(r32(*m, 0x7B4534u) == 0x55u);
    CHECK(v0_of(spair(*m, by_addr(0x581060u), Args{0, 0, 0, 0}, 9)) == 0x55u);
    spair(*m, by_addr(0x580E00u), Args{sx(kOut), 0, 0, 0}, 10);
    CHECK(r32(*m, 0x7B452Cu) == kOut);
    spair(*m, by_addr(0x580020u), Args{0x77u, 0, 0, 0}, 11);
    CHECK(r32(*m, kMwsfdWork + 52) == 0x77u);
    CHECK(v0_of(spair(*m, by_addr(0x580048u), Args{0, 0, 0, 0}, 12)) == 0x77u);
    // mwPlyFinish: a count above 1 only drops it; at 1 every player in use is destroyed (the recorded sub_57DB58).
    w32(*m, kMwsfdInit, 3);
    spair(*m, by_addr(0x57FB20u), Args{0, 0, 0, 0}, 13, &log);
    CHECK(r32(*m, kMwsfdInit) == 2u);
    CHECK(log.empty());
    for (u32 i = 0; i < 8; ++i) w32(*m, kMwsfdWork + 108 + 684 * i, i % 3 == 0 ? 1u : 0u);
    w32(*m, kMwsfdInit, 1);
    spair(*m, by_addr(0x57FB20u), Args{0, 0, 0, 0}, 14, &log);
    CHECK(r32(*m, kMwsfdInit) == 0u);
    std::size_t destroyed = 0;
    for (const StandInCall& c : log) destroyed += c.va == 0x57DB58u ? 1 : 0;
    CHECK(destroyed == 3u);  // players 0, 3, 6

    // MPV start-code copy (sub_578268) on stretches of a disc movie: the copied bytes equal the source, and the
    // returned position is the end or just past a start code 00 00 01 xx.
    std::ifstream f(std::filesystem::path(extracted_root()) / "DATA" / "SFD" / "GAME_START.SFD", std::ios::binary);
    if (!f) {
        MESSAGE("SKIP: GAME_START.SFD not under extracted/DATA/SFD");
        return;
    }
    std::vector<u8> s(0x8000);
    f.read(reinterpret_cast<char*>(s.data()), static_cast<std::streamsize>(s.size()));
    s.resize(static_cast<std::size_t>(f.gcount()));
    REQUIRE(s.size() > 0x1000u);
    const u32 src = kWorld, dst = kWorld + 0x8000u;
    for (const u64 mask : {u64{0xFFFFFFFFu}, u64{0}, u64{4}, u64{0x10}}) {
        for (u32 at : {0u, 1u, 0x800u, 0x803u}) {
            std::memset(m->at(kWorld), 0, kWorldSize);
            std::memcpy(m->at(src), s.data(), 0x8000u);
            const u32 len = 0x300u;  // short: a long scan exceeds the runaway budget of a pair
            const hgp::Run r = spair(*m, by_addr(0x578268u), Args{sx(dst), sx(src + at), len, mask}, 15);
            const u32 end = static_cast<u32>(v0_of(r));
            INFO("mask " << mask << " at " << at << " stopped " << r.stopped << " " << r.what << " pc " << r.stop_pc);
            REQUIRE(end >= src + at);
            REQUIRE(end <= src + at + len);
            CHECK(std::memcmp(m->at(dst), m->at(src + at), end - (src + at)) == 0);
            if (end < src + at + len) {
                REQUIRE(end - (src + at) >= 4u);
                CHECK(s[end - src - 4] == 0);
                CHECK(s[end - src - 3] == 0);
                CHECK(s[end - src - 2] == 1);
            }
            if (mask == 0) CHECK(end == src + at + len);
        }
    }
}

#else

TEST_CASE("game(libs21): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
