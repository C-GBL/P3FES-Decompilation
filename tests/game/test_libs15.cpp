// Pair tests for slice libs15 (CRI middleware: ADXT / ADXM, PS2RNA, ROFS / PFS, the MPEG-2 video header parsers,
// MWSFD / MWPLY, WTLS, the ADX stream input): every body against its recompiled body, compared by
// tests/game/handgen_pairs.h -- the whole register file and cycle count at every check point and at the return / stop,
// all 32 MiB of RAM, the scratchpad, the BIOS window and the bus log -- on random worlds, on the replay snapshots' RAM,
// on a disc movie's real MPEG-2 headers, and with documented-rule checks. Callees this build does not emit are recorders
// (both call logs compared) or, when another current packet claims them, stop both runs at the same call.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/libs15.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;
namespace L15 = p3fes::game::l15;

namespace p3fes::recomp_gen {
void fn_sub_53F2D8_0053f2d8(EEContext&);  // generated body
void fn_sub_53F2D8_0053f2d8__recomp(EEContext&);  // recompiled
void fn_sub_53F458_0053f458(EEContext&);  // generated body
void fn_sub_53F458_0053f458__recomp(EEContext&);  // recompiled
void fn_sub_53F548_0053f548(EEContext&);  // generated body
void fn_sub_53F548_0053f548__recomp(EEContext&);  // recompiled
void fn_sub_53F5B0_0053f5b0(EEContext&);  // generated body
void fn_sub_53F5B0_0053f5b0__recomp(EEContext&);  // recompiled
void fn_sub_53F768_0053f768(EEContext&);  // generated body
void fn_sub_53F768_0053f768__recomp(EEContext&);  // recompiled
void fn_sub_53FAC0_0053fac0(EEContext&);  // generated body
void fn_sub_53FAC0_0053fac0__recomp(EEContext&);  // recompiled
void fn_sub_53FAE8_0053fae8(EEContext&);  // generated body
void fn_sub_53FAE8_0053fae8__recomp(EEContext&);  // recompiled
void fn_adxm_safe_proc_0053fb00(EEContext&);  // generated body
void fn_adxm_safe_proc_0053fb00__recomp(EEContext&);  // recompiled
void fn_sub_53FB58_0053fb58(EEContext&);  // generated body
void fn_sub_53FB58_0053fb58__recomp(EEContext&);  // recompiled
void fn_sub_53FF20_0053ff20(EEContext&);  // generated body
void fn_sub_53FF20_0053ff20__recomp(EEContext&);  // recompiled
void fn_sub_560240_00560240(EEContext&);  // generated body
void fn_sub_560240_00560240__recomp(EEContext&);  // recompiled
void fn_sub_560378_00560378(EEContext&);  // generated body
void fn_sub_560378_00560378__recomp(EEContext&);  // recompiled
void fn_sub_5603D8_005603d8(EEContext&);  // generated body
void fn_sub_5603D8_005603d8__recomp(EEContext&);  // recompiled
void fn_sub_560448_00560448(EEContext&);  // generated body
void fn_sub_560448_00560448__recomp(EEContext&);  // recompiled
void fn_PS2RNA_StartPcmTrans_00560558(EEContext&);  // generated body
void fn_PS2RNA_StartPcmTrans_00560558__recomp(EEContext&);  // recompiled
void fn_PS2RNA_StopPcmTrans_005605e8(EEContext&);  // generated body
void fn_PS2RNA_StopPcmTrans_005605e8__recomp(EEContext&);  // recompiled
void fn_sub_560BE0_00560be0(EEContext&);  // generated body
void fn_sub_560BE0_00560be0__recomp(EEContext&);  // recompiled
void fn_sub_560C28_00560c28(EEContext&);  // generated body
void fn_sub_560C28_00560c28__recomp(EEContext&);  // recompiled
void fn_sub_5611E0_005611e0(EEContext&);  // generated body
void fn_sub_5611E0_005611e0__recomp(EEContext&);  // recompiled
void fn_sub_5615B0_005615b0(EEContext&);  // generated body
void fn_sub_5615B0_005615b0__recomp(EEContext&);  // recompiled
void fn_sub_561640_00561640(EEContext&);  // generated body
void fn_sub_561640_00561640__recomp(EEContext&);  // recompiled
void fn_sub_561688_00561688(EEContext&);  // generated body
void fn_sub_561688_00561688__recomp(EEContext&);  // recompiled
void fn_sub_5616C8_005616c8(EEContext&);  // generated body
void fn_sub_5616C8_005616c8__recomp(EEContext&);  // recompiled
void fn_sub_563E30_00563e30(EEContext&);  // generated body
void fn_sub_563E30_00563e30__recomp(EEContext&);  // recompiled
void fn_sub_564038_00564038(EEContext&);  // generated body
void fn_sub_564038_00564038__recomp(EEContext&);  // recompiled
void fn_sub_564320_00564320(EEContext&);  // generated body
void fn_sub_564320_00564320__recomp(EEContext&);  // recompiled
void fn_sub_564830_00564830(EEContext&);  // generated body
void fn_sub_564830_00564830__recomp(EEContext&);  // recompiled
void fn_pfsCvfsStopTr_005657b8(EEContext&);  // generated body
void fn_pfsCvfsStopTr_005657b8__recomp(EEContext&);  // recompiled
void fn_ROFS_DelVolume_00566488(EEContext&);  // generated body
void fn_ROFS_DelVolume_00566488__recomp(EEContext&);  // recompiled
void fn_ROFS_StopTr_00566750(EEContext&);  // generated body
void fn_ROFS_StopTr_00566750__recomp(EEContext&);  // recompiled
void fn_sub_566848_00566848(EEContext&);  // generated body
void fn_sub_566848_00566848__recomp(EEContext&);  // recompiled
void fn_sub_5668B8_005668b8(EEContext&);  // generated body
void fn_sub_5668B8_005668b8__recomp(EEContext&);  // recompiled
void fn_sub_566938_00566938(EEContext&);  // generated body
void fn_sub_566938_00566938__recomp(EEContext&);  // recompiled
void fn_ROFS_LoadDir_00566a58(EEContext&);  // generated body
void fn_ROFS_LoadDir_00566a58__recomp(EEContext&);  // recompiled
void fn_sub_566C20_00566c20(EEContext&);  // generated body
void fn_sub_566C20_00566c20__recomp(EEContext&);  // recompiled
void fn_sub_566CB8_00566cb8(EEContext&);  // generated body
void fn_sub_566CB8_00566cb8__recomp(EEContext&);  // recompiled
void fn_sub_566D28_00566d28(EEContext&);  // generated body
void fn_sub_566D28_00566d28__recomp(EEContext&);  // recompiled
void fn_sub_56A538_0056a538(EEContext&);  // generated body
void fn_sub_56A538_0056a538__recomp(EEContext&);  // recompiled
void fn_dcfTell_0056a5a0(EEContext&);  // generated body
void fn_dcfTell_0056a5a0__recomp(EEContext&);  // recompiled
void fn_dcfStopTr_0056a660(EEContext&);  // generated body
void fn_dcfStopTr_0056a660__recomp(EEContext&);  // recompiled
void fn_dcfReadBlk_0056a9e0(EEContext&);  // generated body
void fn_dcfReadBlk_0056a9e0__recomp(EEContext&);  // recompiled
void fn_dcfReadCda_0056aac0(EEContext&);  // generated body
void fn_dcfReadCda_0056aac0__recomp(EEContext&);  // recompiled
void fn_sub_56CA60_0056ca60(EEContext&);  // generated body
void fn_sub_56CA60_0056ca60__recomp(EEContext&);  // recompiled
void fn_sub_56CA80_0056ca80(EEContext&);  // generated body
void fn_sub_56CA80_0056ca80__recomp(EEContext&);  // recompiled
void fn_sub_56CA98_0056ca98(EEContext&);  // generated body
void fn_sub_56CA98_0056ca98__recomp(EEContext&);  // recompiled
void fn_sub_570240_00570240(EEContext&);  // generated body
void fn_sub_570240_00570240__recomp(EEContext&);  // recompiled
void fn_sub_5702F8_005702f8(EEContext&);  // generated body
void fn_sub_5702F8_005702f8__recomp(EEContext&);  // recompiled
void fn_sub_570348_00570348(EEContext&);  // generated body
void fn_sub_570348_00570348__recomp(EEContext&);  // recompiled
void fn_sub_5703C0_005703c0(EEContext&);  // generated body
void fn_sub_5703C0_005703c0__recomp(EEContext&);  // recompiled
void fn_sub_570B98_00570b98(EEContext&);  // generated body
void fn_sub_570B98_00570b98__recomp(EEContext&);  // recompiled
void fn_sub_570CB8_00570cb8(EEContext&);  // generated body
void fn_sub_570CB8_00570cb8__recomp(EEContext&);  // recompiled
void fn_sub_570ED0_00570ed0(EEContext&);  // generated body
void fn_sub_570ED0_00570ed0__recomp(EEContext&);  // recompiled
void fn_sub_571048_00571048(EEContext&);  // generated body
void fn_sub_571048_00571048__recomp(EEContext&);  // recompiled
void fn_sub_571088_00571088(EEContext&);  // generated body
void fn_sub_571088_00571088__recomp(EEContext&);  // recompiled
void fn_sub_574068_00574068(EEContext&);  // generated body
void fn_sub_574068_00574068__recomp(EEContext&);  // recompiled
void fn_sub_5745D0_005745d0(EEContext&);  // generated body
void fn_sub_5745D0_005745d0__recomp(EEContext&);  // recompiled
void fn_sub_578378_00578378(EEContext&);  // generated body
void fn_sub_578378_00578378__recomp(EEContext&);  // recompiled
void fn_sub_578820_00578820(EEContext&);  // generated body
void fn_sub_578820_00578820__recomp(EEContext&);  // recompiled
void fn_sub_582BF0_00582bf0(EEContext&);  // generated body
void fn_sub_582BF0_00582bf0__recomp(EEContext&);  // recompiled
void fn_sub_582C68_00582c68(EEContext&);  // generated body
void fn_sub_582C68_00582c68__recomp(EEContext&);  // recompiled
void fn_sub_582CD8_00582cd8(EEContext&);  // generated body
void fn_sub_582CD8_00582cd8__recomp(EEContext&);  // recompiled
void fn_sub_582D48_00582d48(EEContext&);  // generated body
void fn_sub_582D48_00582d48__recomp(EEContext&);  // recompiled
void fn_sub_583848_00583848(EEContext&);  // generated body
void fn_sub_583848_00583848__recomp(EEContext&);  // recompiled
void fn__get_peer_or_sock_name_0_005843e8(EEContext&);  // generated body
void fn__get_peer_or_sock_name_0_005843e8__recomp(EEContext&);  // recompiled
void fn_sub_584400_00584400(EEContext&);  // generated body
void fn_sub_584400_00584400__recomp(EEContext&);  // recompiled
void fn_sub_584558_00584558(EEContext&);  // generated body
void fn_sub_584558_00584558__recomp(EEContext&);  // recompiled
void fn_sub_584748_00584748(EEContext&);  // generated body
void fn_sub_584748_00584748__recomp(EEContext&);  // recompiled
void fn_sub_584760_00584760(EEContext&);  // generated body
void fn_sub_584760_00584760__recomp(EEContext&);  // recompiled
void fn_sub_5849D0_005849d0(EEContext&);  // generated body
void fn_sub_5849D0_005849d0__recomp(EEContext&);  // recompiled
void fn_sub_584AB0_00584ab0(EEContext&);  // generated body
void fn_sub_584AB0_00584ab0__recomp(EEContext&);  // recompiled
void fn_sub_584B78_00584b78(EEContext&);  // generated body
void fn_sub_584B78_00584b78__recomp(EEContext&);  // recompiled
void fn_sub_584BE0_00584be0(EEContext&);  // generated body
void fn_sub_584BE0_00584be0__recomp(EEContext&);  // recompiled
void fn_sub_584E68_00584e68(EEContext&);  // generated body
void fn_sub_584E68_00584e68__recomp(EEContext&);  // recompiled
void fn_sub_584EC8_00584ec8(EEContext&);  // generated body
void fn_sub_584EC8_00584ec8__recomp(EEContext&);  // recompiled
void fn_sub_585250_00585250(EEContext&);  // generated body
void fn_sub_585250_00585250__recomp(EEContext&);  // recompiled
void fn_sub_585340_00585340(EEContext&);  // generated body
void fn_sub_585340_00585340__recomp(EEContext&);  // recompiled
void fn_sub_585398_00585398(EEContext&);  // generated body
void fn_sub_585398_00585398__recomp(EEContext&);  // recompiled
void fn_sub_5853F0_005853f0(EEContext&);  // generated body
void fn_sub_5853F0_005853f0__recomp(EEContext&);  // recompiled
void fn_sub_585440_00585440(EEContext&);  // generated body
void fn_sub_585440_00585440__recomp(EEContext&);  // recompiled
void fn_sinl_11_00585658(EEContext&);  // generated body
void fn_sinl_11_00585658__recomp(EEContext&);  // recompiled
void fn_sub_586110_00586110(EEContext&);  // generated body
void fn_sub_586110_00586110__recomp(EEContext&);  // recompiled
void fn_sub_586300_00586300(EEContext&);  // generated body
void fn_sub_586300_00586300__recomp(EEContext&);  // recompiled
void fn_sub_586308_00586308(EEContext&);  // generated body
void fn_sub_586308_00586308__recomp(EEContext&);  // recompiled
void fn_sub_586450_00586450(EEContext&);  // generated body
void fn_sub_586450_00586450__recomp(EEContext&);  // recompiled
void fn_sub_586468_00586468(EEContext&);  // generated body
void fn_sub_586468_00586468__recomp(EEContext&);  // recompiled
void fn_sub_586628_00586628(EEContext&);  // generated body
void fn_sub_586628_00586628__recomp(EEContext&);  // recompiled
void fn_sub_5866C8_005866c8(EEContext&);  // generated body
void fn_sub_5866C8_005866c8__recomp(EEContext&);  // recompiled
void fn_sub_5866E8_005866e8(EEContext&);  // generated body
void fn_sub_5866E8_005866e8__recomp(EEContext&);  // recompiled
void fn_sub_586708_00586708(EEContext&);  // generated body
void fn_sub_586708_00586708__recomp(EEContext&);  // recompiled
void fn_sub_586728_00586728(EEContext&);  // generated body
void fn_sub_586728_00586728__recomp(EEContext&);  // recompiled
void fn_R_LOCK_DEF_w_lock_4_00586748(EEContext&);  // generated body
void fn_R_LOCK_DEF_w_lock_4_00586748__recomp(EEContext&);  // recompiled
void fn_sub_586C10_00586c10(EEContext&);  // generated body
void fn_sub_586C10_00586c10__recomp(EEContext&);  // recompiled
void fn_sub_586E78_00586e78(EEContext&);  // generated body
void fn_sub_586E78_00586e78__recomp(EEContext&);  // recompiled
void fn_sub_586F00_00586f00(EEContext&);  // generated body
void fn_sub_586F00_00586f00__recomp(EEContext&);  // recompiled
void fn_sub_587100_00587100(EEContext&);  // generated body
void fn_sub_587100_00587100__recomp(EEContext&);  // recompiled
void fn_sub_587FD8_00587fd8(EEContext&);  // generated body
void fn_sub_587FD8_00587fd8__recomp(EEContext&);  // recompiled
void fn_sub_588360_00588360(EEContext&);  // generated body
void fn_sub_588360_00588360__recomp(EEContext&);  // recompiled
void fn_sub_588568_00588568(EEContext&);  // generated body
void fn_sub_588568_00588568__recomp(EEContext&);  // recompiled
void fn_sub_588640_00588640(EEContext&);  // generated body
void fn_sub_588640_00588640__recomp(EEContext&);  // recompiled
void fn_sub_588698_00588698(EEContext&);  // generated body
void fn_sub_588698_00588698__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_53F2D8", 0x53F2D8, &recomp_gen::fn_sub_53F2D8_0053f2d8, &recomp_gen::fn_sub_53F2D8_0053f2d8__recomp},
    {"sub_53F458", 0x53F458, &recomp_gen::fn_sub_53F458_0053f458, &recomp_gen::fn_sub_53F458_0053f458__recomp},
    {"sub_53F548", 0x53F548, &recomp_gen::fn_sub_53F548_0053f548, &recomp_gen::fn_sub_53F548_0053f548__recomp},
    {"sub_53F5B0", 0x53F5B0, &recomp_gen::fn_sub_53F5B0_0053f5b0, &recomp_gen::fn_sub_53F5B0_0053f5b0__recomp},
    {"sub_53F768", 0x53F768, &recomp_gen::fn_sub_53F768_0053f768, &recomp_gen::fn_sub_53F768_0053f768__recomp},
    {"sub_53FAC0", 0x53FAC0, &recomp_gen::fn_sub_53FAC0_0053fac0, &recomp_gen::fn_sub_53FAC0_0053fac0__recomp},
    {"sub_53FAE8", 0x53FAE8, &recomp_gen::fn_sub_53FAE8_0053fae8, &recomp_gen::fn_sub_53FAE8_0053fae8__recomp},
    {"adxm_safe_proc", 0x53FB00, &recomp_gen::fn_adxm_safe_proc_0053fb00, &recomp_gen::fn_adxm_safe_proc_0053fb00__recomp},
    {"sub_53FB58", 0x53FB58, &recomp_gen::fn_sub_53FB58_0053fb58, &recomp_gen::fn_sub_53FB58_0053fb58__recomp},
    {"sub_53FF20", 0x53FF20, &recomp_gen::fn_sub_53FF20_0053ff20, &recomp_gen::fn_sub_53FF20_0053ff20__recomp},
    {"sub_560240", 0x560240, &recomp_gen::fn_sub_560240_00560240, &recomp_gen::fn_sub_560240_00560240__recomp},
    {"sub_560378", 0x560378, &recomp_gen::fn_sub_560378_00560378, &recomp_gen::fn_sub_560378_00560378__recomp},
    {"sub_5603D8", 0x5603D8, &recomp_gen::fn_sub_5603D8_005603d8, &recomp_gen::fn_sub_5603D8_005603d8__recomp},
    {"sub_560448", 0x560448, &recomp_gen::fn_sub_560448_00560448, &recomp_gen::fn_sub_560448_00560448__recomp},
    {"PS2RNA_StartPcmTrans", 0x560558, &recomp_gen::fn_PS2RNA_StartPcmTrans_00560558, &recomp_gen::fn_PS2RNA_StartPcmTrans_00560558__recomp},
    {"PS2RNA_StopPcmTrans", 0x5605E8, &recomp_gen::fn_PS2RNA_StopPcmTrans_005605e8, &recomp_gen::fn_PS2RNA_StopPcmTrans_005605e8__recomp},
    {"sub_560BE0", 0x560BE0, &recomp_gen::fn_sub_560BE0_00560be0, &recomp_gen::fn_sub_560BE0_00560be0__recomp},
    {"sub_560C28", 0x560C28, &recomp_gen::fn_sub_560C28_00560c28, &recomp_gen::fn_sub_560C28_00560c28__recomp},
    {"sub_5611E0", 0x5611E0, &recomp_gen::fn_sub_5611E0_005611e0, &recomp_gen::fn_sub_5611E0_005611e0__recomp},
    {"sub_5615B0", 0x5615B0, &recomp_gen::fn_sub_5615B0_005615b0, &recomp_gen::fn_sub_5615B0_005615b0__recomp},
    {"sub_561640", 0x561640, &recomp_gen::fn_sub_561640_00561640, &recomp_gen::fn_sub_561640_00561640__recomp},
    {"sub_561688", 0x561688, &recomp_gen::fn_sub_561688_00561688, &recomp_gen::fn_sub_561688_00561688__recomp},
    {"sub_5616C8", 0x5616C8, &recomp_gen::fn_sub_5616C8_005616c8, &recomp_gen::fn_sub_5616C8_005616c8__recomp},
    {"sub_563E30", 0x563E30, &recomp_gen::fn_sub_563E30_00563e30, &recomp_gen::fn_sub_563E30_00563e30__recomp},
    {"sub_564038", 0x564038, &recomp_gen::fn_sub_564038_00564038, &recomp_gen::fn_sub_564038_00564038__recomp},
    {"sub_564320", 0x564320, &recomp_gen::fn_sub_564320_00564320, &recomp_gen::fn_sub_564320_00564320__recomp},
    {"sub_564830", 0x564830, &recomp_gen::fn_sub_564830_00564830, &recomp_gen::fn_sub_564830_00564830__recomp},
    {"pfsCvfsStopTr", 0x5657B8, &recomp_gen::fn_pfsCvfsStopTr_005657b8, &recomp_gen::fn_pfsCvfsStopTr_005657b8__recomp},
    {"ROFS_DelVolume", 0x566488, &recomp_gen::fn_ROFS_DelVolume_00566488, &recomp_gen::fn_ROFS_DelVolume_00566488__recomp},
    {"ROFS_StopTr", 0x566750, &recomp_gen::fn_ROFS_StopTr_00566750, &recomp_gen::fn_ROFS_StopTr_00566750__recomp},
    {"sub_566848", 0x566848, &recomp_gen::fn_sub_566848_00566848, &recomp_gen::fn_sub_566848_00566848__recomp},
    {"sub_5668B8", 0x5668B8, &recomp_gen::fn_sub_5668B8_005668b8, &recomp_gen::fn_sub_5668B8_005668b8__recomp},
    {"sub_566938", 0x566938, &recomp_gen::fn_sub_566938_00566938, &recomp_gen::fn_sub_566938_00566938__recomp},
    {"ROFS_LoadDir", 0x566A58, &recomp_gen::fn_ROFS_LoadDir_00566a58, &recomp_gen::fn_ROFS_LoadDir_00566a58__recomp},
    {"sub_566C20", 0x566C20, &recomp_gen::fn_sub_566C20_00566c20, &recomp_gen::fn_sub_566C20_00566c20__recomp},
    {"sub_566CB8", 0x566CB8, &recomp_gen::fn_sub_566CB8_00566cb8, &recomp_gen::fn_sub_566CB8_00566cb8__recomp},
    {"sub_566D28", 0x566D28, &recomp_gen::fn_sub_566D28_00566d28, &recomp_gen::fn_sub_566D28_00566d28__recomp},
    {"sub_56A538", 0x56A538, &recomp_gen::fn_sub_56A538_0056a538, &recomp_gen::fn_sub_56A538_0056a538__recomp},
    {"dcfTell", 0x56A5A0, &recomp_gen::fn_dcfTell_0056a5a0, &recomp_gen::fn_dcfTell_0056a5a0__recomp},
    {"dcfStopTr", 0x56A660, &recomp_gen::fn_dcfStopTr_0056a660, &recomp_gen::fn_dcfStopTr_0056a660__recomp},
    {"dcfReadBlk", 0x56A9E0, &recomp_gen::fn_dcfReadBlk_0056a9e0, &recomp_gen::fn_dcfReadBlk_0056a9e0__recomp},
    {"dcfReadCda", 0x56AAC0, &recomp_gen::fn_dcfReadCda_0056aac0, &recomp_gen::fn_dcfReadCda_0056aac0__recomp},
    {"sub_56CA60", 0x56CA60, &recomp_gen::fn_sub_56CA60_0056ca60, &recomp_gen::fn_sub_56CA60_0056ca60__recomp},
    {"sub_56CA80", 0x56CA80, &recomp_gen::fn_sub_56CA80_0056ca80, &recomp_gen::fn_sub_56CA80_0056ca80__recomp},
    {"sub_56CA98", 0x56CA98, &recomp_gen::fn_sub_56CA98_0056ca98, &recomp_gen::fn_sub_56CA98_0056ca98__recomp},
    {"sub_570240", 0x570240, &recomp_gen::fn_sub_570240_00570240, &recomp_gen::fn_sub_570240_00570240__recomp},
    {"sub_5702F8", 0x5702F8, &recomp_gen::fn_sub_5702F8_005702f8, &recomp_gen::fn_sub_5702F8_005702f8__recomp},
    {"sub_570348", 0x570348, &recomp_gen::fn_sub_570348_00570348, &recomp_gen::fn_sub_570348_00570348__recomp},
    {"sub_5703C0", 0x5703C0, &recomp_gen::fn_sub_5703C0_005703c0, &recomp_gen::fn_sub_5703C0_005703c0__recomp},
    {"sub_570B98", 0x570B98, &recomp_gen::fn_sub_570B98_00570b98, &recomp_gen::fn_sub_570B98_00570b98__recomp},
    {"sub_570CB8", 0x570CB8, &recomp_gen::fn_sub_570CB8_00570cb8, &recomp_gen::fn_sub_570CB8_00570cb8__recomp},
    {"sub_570ED0", 0x570ED0, &recomp_gen::fn_sub_570ED0_00570ed0, &recomp_gen::fn_sub_570ED0_00570ed0__recomp},
    {"sub_571048", 0x571048, &recomp_gen::fn_sub_571048_00571048, &recomp_gen::fn_sub_571048_00571048__recomp},
    {"sub_571088", 0x571088, &recomp_gen::fn_sub_571088_00571088, &recomp_gen::fn_sub_571088_00571088__recomp},
    {"sub_574068", 0x574068, &recomp_gen::fn_sub_574068_00574068, &recomp_gen::fn_sub_574068_00574068__recomp},
    {"sub_5745D0", 0x5745D0, &recomp_gen::fn_sub_5745D0_005745d0, &recomp_gen::fn_sub_5745D0_005745d0__recomp},
    {"sub_578378", 0x578378, &recomp_gen::fn_sub_578378_00578378, &recomp_gen::fn_sub_578378_00578378__recomp},
    {"sub_578820", 0x578820, &recomp_gen::fn_sub_578820_00578820, &recomp_gen::fn_sub_578820_00578820__recomp},
    {"sub_582BF0", 0x582BF0, &recomp_gen::fn_sub_582BF0_00582bf0, &recomp_gen::fn_sub_582BF0_00582bf0__recomp},
    {"sub_582C68", 0x582C68, &recomp_gen::fn_sub_582C68_00582c68, &recomp_gen::fn_sub_582C68_00582c68__recomp},
    {"sub_582CD8", 0x582CD8, &recomp_gen::fn_sub_582CD8_00582cd8, &recomp_gen::fn_sub_582CD8_00582cd8__recomp},
    {"sub_582D48", 0x582D48, &recomp_gen::fn_sub_582D48_00582d48, &recomp_gen::fn_sub_582D48_00582d48__recomp},
    {"sub_583848", 0x583848, &recomp_gen::fn_sub_583848_00583848, &recomp_gen::fn_sub_583848_00583848__recomp},
    {"_get_peer_or_sock_name_0", 0x5843E8, &recomp_gen::fn__get_peer_or_sock_name_0_005843e8, &recomp_gen::fn__get_peer_or_sock_name_0_005843e8__recomp},
    {"sub_584400", 0x584400, &recomp_gen::fn_sub_584400_00584400, &recomp_gen::fn_sub_584400_00584400__recomp},
    {"sub_584558", 0x584558, &recomp_gen::fn_sub_584558_00584558, &recomp_gen::fn_sub_584558_00584558__recomp},
    {"sub_584748", 0x584748, &recomp_gen::fn_sub_584748_00584748, &recomp_gen::fn_sub_584748_00584748__recomp},
    {"sub_584760", 0x584760, &recomp_gen::fn_sub_584760_00584760, &recomp_gen::fn_sub_584760_00584760__recomp},
    {"sub_5849D0", 0x5849D0, &recomp_gen::fn_sub_5849D0_005849d0, &recomp_gen::fn_sub_5849D0_005849d0__recomp},
    {"sub_584AB0", 0x584AB0, &recomp_gen::fn_sub_584AB0_00584ab0, &recomp_gen::fn_sub_584AB0_00584ab0__recomp},
    {"sub_584B78", 0x584B78, &recomp_gen::fn_sub_584B78_00584b78, &recomp_gen::fn_sub_584B78_00584b78__recomp},
    {"sub_584BE0", 0x584BE0, &recomp_gen::fn_sub_584BE0_00584be0, &recomp_gen::fn_sub_584BE0_00584be0__recomp},
    {"sub_584E68", 0x584E68, &recomp_gen::fn_sub_584E68_00584e68, &recomp_gen::fn_sub_584E68_00584e68__recomp},
    {"sub_584EC8", 0x584EC8, &recomp_gen::fn_sub_584EC8_00584ec8, &recomp_gen::fn_sub_584EC8_00584ec8__recomp},
    {"sub_585250", 0x585250, &recomp_gen::fn_sub_585250_00585250, &recomp_gen::fn_sub_585250_00585250__recomp},
    {"sub_585340", 0x585340, &recomp_gen::fn_sub_585340_00585340, &recomp_gen::fn_sub_585340_00585340__recomp},
    {"sub_585398", 0x585398, &recomp_gen::fn_sub_585398_00585398, &recomp_gen::fn_sub_585398_00585398__recomp},
    {"sub_5853F0", 0x5853F0, &recomp_gen::fn_sub_5853F0_005853f0, &recomp_gen::fn_sub_5853F0_005853f0__recomp},
    {"sub_585440", 0x585440, &recomp_gen::fn_sub_585440_00585440, &recomp_gen::fn_sub_585440_00585440__recomp},
    {"sinl_11", 0x585658, &recomp_gen::fn_sinl_11_00585658, &recomp_gen::fn_sinl_11_00585658__recomp},
    {"sub_586110", 0x586110, &recomp_gen::fn_sub_586110_00586110, &recomp_gen::fn_sub_586110_00586110__recomp},
    {"sub_586300", 0x586300, &recomp_gen::fn_sub_586300_00586300, &recomp_gen::fn_sub_586300_00586300__recomp},
    {"sub_586308", 0x586308, &recomp_gen::fn_sub_586308_00586308, &recomp_gen::fn_sub_586308_00586308__recomp},
    {"sub_586450", 0x586450, &recomp_gen::fn_sub_586450_00586450, &recomp_gen::fn_sub_586450_00586450__recomp},
    {"sub_586468", 0x586468, &recomp_gen::fn_sub_586468_00586468, &recomp_gen::fn_sub_586468_00586468__recomp},
    {"sub_586628", 0x586628, &recomp_gen::fn_sub_586628_00586628, &recomp_gen::fn_sub_586628_00586628__recomp},
    {"sub_5866C8", 0x5866C8, &recomp_gen::fn_sub_5866C8_005866c8, &recomp_gen::fn_sub_5866C8_005866c8__recomp},
    {"sub_5866E8", 0x5866E8, &recomp_gen::fn_sub_5866E8_005866e8, &recomp_gen::fn_sub_5866E8_005866e8__recomp},
    {"sub_586708", 0x586708, &recomp_gen::fn_sub_586708_00586708, &recomp_gen::fn_sub_586708_00586708__recomp},
    {"sub_586728", 0x586728, &recomp_gen::fn_sub_586728_00586728, &recomp_gen::fn_sub_586728_00586728__recomp},
    {"R_LOCK_DEF_w_lock_4", 0x586748, &recomp_gen::fn_R_LOCK_DEF_w_lock_4_00586748, &recomp_gen::fn_R_LOCK_DEF_w_lock_4_00586748__recomp},
    {"sub_586C10", 0x586C10, &recomp_gen::fn_sub_586C10_00586c10, &recomp_gen::fn_sub_586C10_00586c10__recomp},
    {"sub_586E78", 0x586E78, &recomp_gen::fn_sub_586E78_00586e78, &recomp_gen::fn_sub_586E78_00586e78__recomp},
    {"sub_586F00", 0x586F00, &recomp_gen::fn_sub_586F00_00586f00, &recomp_gen::fn_sub_586F00_00586f00__recomp},
    {"sub_587100", 0x587100, &recomp_gen::fn_sub_587100_00587100, &recomp_gen::fn_sub_587100_00587100__recomp},
    {"sub_587FD8", 0x587FD8, &recomp_gen::fn_sub_587FD8_00587fd8, &recomp_gen::fn_sub_587FD8_00587fd8__recomp},
    {"sub_588360", 0x588360, &recomp_gen::fn_sub_588360_00588360, &recomp_gen::fn_sub_588360_00588360__recomp},
    {"sub_588568", 0x588568, &recomp_gen::fn_sub_588568_00588568, &recomp_gen::fn_sub_588568_00588568__recomp},
    {"sub_588640", 0x588640, &recomp_gen::fn_sub_588640_00588640, &recomp_gen::fn_sub_588640_00588640__recomp},
    {"sub_588698", 0x588698, &recomp_gen::fn_sub_588698_00588698, &recomp_gen::fn_sub_588698_00588698__recomp},
};
// The random world: 64 KiB of free RAM above the harness's arena, filled by hgp::random_world.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 48;

u32 r32(Machine& m, u32 va) {
    u32 v = 0;
    std::memcpy(&v, m.at(va), 4);
    return v;
}
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
void zero(Machine& m, u32 va, u32 n) { std::memset(m.at(va), 0, n); }

const Case& find(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

// Recorders for the callees the bodies meet that this build does not emit and no current packet claims: the IOP RPC
// (DTX_CallUrpc), the thread exit, the ADXT / MWSFD error reports, the ADXT stream / play-list calls, the AFS entry
// lookup, the socket-style stream calls of the ADX input. Each logs its call and returns $v0; both bodies of a pair get
// a fresh set and their call logs must be equal. (The callees libs14 / libs17 claim are left alone: a pair meeting one
// stops there, identically, until it is replaced.)
struct Rec {
    u32 va;
    const char* name;
    u64 v0;
};
const Rec kRecorders[] = {
    {0x559C10u, "DTX_CallUrpc", 0},     {0x502FA0u, "_sceExitDeleteThread", 0}, {0x53AE08u, "sub_53AE08 (ADXT error)", 0},
    {0x585590u, "sub_585590 (MWSFD error)", 0}, {0x55D668u, "sub_55D668", 0}, {0x55D7C0u, "sub_55D7C0", 3},
    {0x59C8E0u, "sub_59C8E0", 0},       {0x53DD10u, "sub_53DD10", 0},             {0x564EF8u, "sub_564EF8", 0},
    {0x549160u, "sceInsockListen_2", 0}, {0x549530u, "sub_549530", 0},            {0x54A630u, "__env_lock_0", 0},
};
StandInWorld* g_si[2];
Fn g_fn[2];
void thunk0(EEContext& ctx) {
    StandInsScope s(g_si[0]->si);
    g_fn[0](ctx);
}
void thunk1(EEContext& ctx) {
    StandInsScope s(g_si[1]->si);
    g_fn[1](ctx);
}
// One pair with the recorders; `log` (when given) receives the hand body's call log.
hgp::Run spair(Machine& m, const Case& c, const Args& args, u32 seed, std::vector<StandInCall>* log = nullptr) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    for (StandInWorld* w : {wh.get(), wr.get()}) {
        w->si.clobber_scratch = true;
        for (const Rec& r : kRecorders) w->si.install_recorder(r.va, r.name, r.v0, 3);
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
        const std::string summary = std::string(label) + " " + c.name + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

// --- the MPEG-2 video stream of a disc movie ------------------------------------------------------------------------
// The first `n` bytes of extracted/DATA/SFD/<name> (empty when absent).
std::vector<u8> sfd_head(const char* name, std::size_t n) {
    std::ifstream f(std::filesystem::path(extracted_root()) / "DATA" / "SFD" / name, std::ios::binary);
    if (!f) return {};
    std::vector<u8> out(n);
    f.read(reinterpret_cast<char*>(out.data()), static_cast<std::streamsize>(n));
    out.resize(static_cast<std::size_t>(f.gcount()));
    return out;
}
// The video start codes (00 00 01 xx with xx < 0xB9: the program-stream layer's own codes are 0xB9..0xFF).
std::vector<std::pair<u32, u8>> video_codes(const std::vector<u8>& s) {
    std::vector<std::pair<u32, u8>> out;
    for (u32 i = 0; i + 4 <= s.size(); ++i)
        if (s[i] == 0 && s[i + 1] == 0 && s[i + 2] == 1 && s[i + 3] < 0xB9) out.emplace_back(i, s[i + 3]);
    return out;
}
// Big-endian bits from a byte position.
u32 bits(const std::vector<u8>& s, u32 byte, u32 bit_off, u32 n) {
    u32 v = 0;
    for (u32 k = 0; k < n; ++k) {
        const u32 b = byte * 8 + bit_off + k;
        v = (v << 1) | ((s[b / 8] >> (7 - b % 8)) & 1u);
    }
    return v;
}

constexpr u32 kStream = 0x01820000u;  // the movie bytes (up to 256 KiB)
constexpr u32 kStreamMax = 0x40000u;
constexpr u32 kPar = 0x01810000u;     // the parser's work (0x2000 bytes, zeroed per header)

}  // namespace

TEST_CASE("game(libs15): every body equals its recompiled body on random worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");  // more (or fewer) pairs per function
    run_random(*m, env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : kSeeds, "random");
}

// The same over the RAM of the replay snapshots: the real globals (the PS2RNA mode / count words 0x7A93F8 / 0x7A93F0
// and PCM flags, the ROFS interface 0x7B26F8 and g_rofs_pfs_tbl 0x7B2808, the ADXM thread words 0x788680.., the WTLS
// table), with random worlds for the pointer arguments.
TEST_CASE("game(libs15): every body equals its recompiled body on the replay snapshots") {
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

// The MPEG-2 header parsers on two disc movies' real headers (GAME_START.SFD: MPEG-1, no extensions; P3CTOP.SFD:
// MPEG-2 with extensions): each start code at its parser (sequence 0xB3, GOP 0xB8, picture 0x00, extension 0xB5,
// user data 0xB2, the first slice 0x01) over a zeroed work, with the header kind, the counters and the first fields
// checked against the bytes.
TEST_CASE("game(libs15): the MPEG-2 header parsers on disc movies' headers") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    for (const char* movie : {"GAME_START.SFD", "P3CTOP.SFD"}) {
        const std::vector<u8> s = sfd_head(movie, kStreamMax);
        if (s.size() < 0x10000u) {
            MESSAGE("SKIP: " << std::string(movie) << " not under extracted/DATA/SFD");
            continue;
        }
        std::memcpy(m->at(kStream), s.data(), s.size());
        const auto codes = video_codes(s);
        std::map<u8, int> seen;
        for (const auto& [off, code] : codes) {
            if (off + 64 > s.size()) break;
            const char* fn = code == 0xB3 ? "sub_5703C0" : code == 0xB8 ? "sub_574068" : code == 0x00 ? "sub_5745D0"
                           : code == 0xB5 ? "sub_571088" : code == 0xB2 ? "sub_570CB8" : code == 0x01 ? "sub_578378" : nullptr;
            if (!fn || seen[code] >= 6) continue;
            const int n = seen[code]++;
            const Case& c = find(fn);
            INFO(std::string(movie) << ": " << fn << " at stream offset " << off);
            zero(*m, kPar, 0x2000);
            const u32 at = kStream + off;
            if (code == 0x01) {  // both slice readers take the stream pointer first
                spair(*m, c, Args{sx(at), sx(kPar), 0, 0}, 1 + n);
                spair(*m, find("sub_578820"), Args{sx(at), sx(kPar), 0, 0}, 1 + n);
                continue;
            }
            const hgp::Run r = spair(*m, c, Args{sx(kPar), sx(at), 0, 0}, 1 + n);
            if (r.stopped) continue;
            const u32 next = static_cast<u32>(v0_of(r));
            CHECK(next > at);  // the address after the header
            switch (code) {
                case 0xB3:
                    CHECK(r32(*m, kPar + L15::m2v::kHdrKind) == 1u);
                    CHECK(r32(*m, kPar + 352 + 4) == bits(s, off + 4, 0, 12));  // horizontal_size_value
                    break;
                case 0xB8: CHECK(r32(*m, kPar + L15::m2v::kHdrKind) == 2u); break;
                case 0x00: CHECK(r32(*m, kPar + L15::m2v::kHdrKind) == 3u); break;
                case 0xB5:
                    CHECK(r32(*m, kPar + 416) == bits(s, off + 4, 0, 4));  // extension_start_code_identifier
                    CHECK(r32(*m, kPar + 1532) == 1u);
                    break;
                case 0xB2: CHECK(r32(*m, kPar + 1528) == 1u); break;
                default: break;
            }
        }
        MESSAGE(std::string(movie) << " headers: seq " << seen[0xB3] << ", gop " << seen[0xB8] << ", picture " << seen[0x00]
                                << ", ext " << seen[0xB5] << ", user " << seen[0xB2] << ", slice " << seen[0x01]);
        CHECK(seen[0xB3] > 0);
        CHECK(seen[0x00] > 0);
    }
}

// Documented rules on the host, from the instructions (both bodies run and are compared, then the result checked).
TEST_CASE("game(libs15): picture attribute maps, intra-DC setup, ADX header probe, RNA PCM flags and pitch rules") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const u32 b = kWorld;
    zero(*m, b, kWorldSize);
    std::vector<StandInCall> log;
    // sub_582C68 / sub_582CD8 / sub_582D48: valid codes map to themselves; others report and give 3 / 1 / 1.
    for (u32 v : {1u, 2u, 3u, 0u, 7u}) {
        w32(*m, b + 136, v);
        w32(*m, b + 140, v);
        CHECK(v0_of(spair(*m, find("sub_582C68"), Args{sx(b), 0, 0, 0}, v, &log)) == ((v >= 1 && v <= 3) ? v : 3u));
        CHECK(log.size() == ((v >= 1 && v <= 3) ? 0u : 1u));
        CHECK(v0_of(spair(*m, find("sub_582CD8"), Args{sx(b), 0, 0, 0}, v, &log)) == ((v >= 1 && v <= 3) ? v : 1u));
        CHECK(v0_of(spair(*m, find("sub_582D48"), Args{v, 0, 0, 0}, v, &log)) == (v <= 1 ? v : 1u));
        CHECK(log.size() == (v <= 1 ? 0u : 1u));
    }
    // sub_570348: DC reset 128 << p and multiplier 8 >> p; a frame picture clears the parity pair, a field toggles it.
    for (u32 p = 0; p < 4; ++p) {
        w32(*m, b + L15::m2v::kIntraDcPrec, p);
        w32(*m, b + L15::m2v::kPicStruct, p == 3 ? 3u : 1u);
        w32(*m, b + 968, 5);
        w32(*m, b + 964, 9);
        CHECK(v0_of(spair(*m, find("sub_570348"), Args{sx(b), 0, 0, 0}, p + 1)) == 4u * p);
        CHECK(r32(*m, b + L15::m2v::kDcReset) == (128u << p));
        CHECK(r32(*m, b + L15::m2v::kDcMult) == (8u >> p));
        CHECK(r32(*m, b + 968) == (p == 3 ? 0u : 6u));
        CHECK(r32(*m, b + 964) == (p == 3 ? 0u : 1u));
    }
    // sub_5702F8: mode 1 for the flag word or a field picture, else 3 / 2 by +308.
    {
        const Case& c = find("sub_5702F8");
        const struct {
            u32 flag, pic, w308, mode, v0;
        } rows[] = {{1, 3, 0, 1, 1}, {0, 1, 0, 1, 1}, {0, 2, 1, 1, 1}, {0, 3, 1, 3, 3}, {0, 3, 0, 2, 3}};
        u32 seed = 1;
        for (const auto& row : rows) {
            w32(*m, b + L15::m2v::kMode1, row.flag);
            w32(*m, b + L15::m2v::kPicStruct, row.pic);
            w32(*m, b + 308, row.w308);
            CHECK(v0_of(spair(*m, c, Args{sx(b), 0, 0, 0}, seed++)) == row.v0);
            CHECK(r32(*m, b + L15::m2v::kDecMode) == row.mode);
        }
    }
    // sub_571048: appends min(n, capacity - used) bytes.
    {
        const u32 buf = b + 0x2000, src = b + 0x3000;
        for (u32 i = 0; i < 16; ++i) m->at(src)[i] = static_cast<u8>(0xA0 + i);
        w32(*m, b + 328, buf);
        w32(*m, b + 332, 10);
        w32(*m, b + 336, 4);
        spair(*m, find("sub_571048"), Args{sx(b), sx(src), 16, 0}, 1);
        CHECK(r32(*m, b + 336) == 10u);
        CHECK(m->at(buf + 4)[0] == 0xA0);
        CHECK(m->at(buf + 9)[0] == 0xA5);
        CHECK(m->at(buf + 10)[0] == 0);
    }
    // sub_5849D0: the three work sizes and their sum.
    {
        const hgp::Run r = spair(*m, find("sub_5849D0"), Args{sx(b), sx(b + 4), sx(b + 8), 0}, 1);
        CHECK(v0_of(r) == 431404u + 81000u + 0x2000u);
        CHECK(r32(*m, b) == 431404u);
        CHECK(r32(*m, b + 4) == 81000u);
        CHECK(r32(*m, b + 8) == 0x2000u);
    }
    // sub_586628: an ADX header is 0x80 0x00 .. "(c)CRI" at +282 and needs 288 bytes.
    {
        const u32 h = b + 0x4000, need = b + 0x5000;
        zero(*m, h, 0x200);
        m->at(h)[0] = 0x80;
        std::memcpy(m->at(h + 282), "(c)CRI", 6);
        const Case& c = find("sub_586628");
        CHECK(v0_of(spair(*m, c, Args{sx(h), 288, sx(need), 0}, 1)) == 1u);
        CHECK(r32(*m, need) == 288u);
        CHECK(v0_of(spair(*m, c, Args{sx(h), 287, sx(need), 0}, 2)) == 0u);
        m->at(h + 283)[0] = 'C';
        CHECK(v0_of(spair(*m, c, Args{sx(h), 288, sx(need), 0}, 3)) == 0u);
    }
    // PS2RNA_StartPcmTrans / StopPcmTrans: command 16 / 17 once per change of the channel's flag 0x7A9430[ch].
    {
        w32(*m, 0x7A93F8u, 0);  // the guard off
        w32(*m, 0x7A9430u, 0);
        w32(*m, 0x7A9434u, 0);
        spair(*m, find("PS2RNA_StartPcmTrans"), Args{1, 0, 0, 0}, 1, &log);
        CHECK(r32(*m, 0x7A9434u) == 1u);
        REQUIRE(log.size() == 1u);
        CHECK(log[0].args[0] == 16u);
        spair(*m, find("PS2RNA_StartPcmTrans"), Args{1, 0, 0, 0}, 2, &log);
        CHECK(log.empty());
        spair(*m, find("PS2RNA_StartPcmTrans"), Args{2, 0, 0, 0}, 3, &log);
        CHECK(log.empty());
        spair(*m, find("PS2RNA_StopPcmTrans"), Args{1, 0, 0, 0}, 4, &log);
        CHECK(r32(*m, 0x7A9434u) == 0u);
        REQUIRE(log.size() == 1u);
        CHECK(log[0].args[0] == 17u);
        w32(*m, 0x7A93F8u, 1);  // the guard on, no count: nothing happens
        w32(*m, 0x7A93F0u, 0);
        spair(*m, find("PS2RNA_StartPcmTrans"), Args{0, 0, 0, 0}, 5, &log);
        CHECK(log.empty());
        CHECK(r32(*m, 0x7A9430u) == 0u);
    }
    // R_LOCK_DEF_w_lock_4: speed 2000 (twice normal) is +1200 cents = (12, 0); 1000 is (0, 0).
    {
        const u32 h = b + 0x6000, work = b + 0x6100;
        w32(*m, h + L15::adxs::kWork, work);
        w32(*m, work, 0x1234u);
        const Case& c = find("R_LOCK_DEF_w_lock_4");
        spair(*m, c, Args{sx(h), 2000, 0, 0}, 1, &log);
        REQUIRE(log.size() == 1u);  // logf is hand-written (it runs); the log holds __env_lock_0
        CHECK(log.back().args[0] == 0x1234u);
        // the float product truncates: 1200 cents, or 1199 when the single-precision log lands a hair low
        const s64 cents = static_cast<s64>(log.back().args[1]) * 100 + static_cast<s64>(log.back().args[2]);
        CHECK((cents == 1200 || cents == 1199));
        spair(*m, c, Args{sx(h), 1000, 0, 0}, 2, &log);
        REQUIRE(!log.empty());
        CHECK(log.back().args[1] == 0u);
        CHECK(log.back().args[2] == 0u);
    }
}

#else

TEST_CASE("game(libs15): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
