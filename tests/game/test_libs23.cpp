// Pair tests for slice libs23 (game/src/cri/libs23.cpp): every body against its recompiled body, compared by
// tests/game/handgen_pairs.h (the whole register file and cycle count at every check point and at the return / stop, all
// 32 MiB of RAM with the dead stack, the scratchpad, the BIOS window and the bus log). Worlds: random worlds; SFD handle
// worlds (a valid or invalid handle with its video-decoder work, frame records, video-input ring, header object, time
// record and transfer slot 8) with sprintf stood in; the same over the RAM of the replay snapshots and on any open SFD
// handle they hold; and documented rules on the host. A callee this build does not emit stops both runs at the same
// call (no test asserts such a stop).
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/libs23.h"

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
void fn_sub_58C138_0058c138(EEContext&);  // generated body
void fn_sub_58C138_0058c138__recomp(EEContext&);  // recompiled
void fn_sub_58C178_0058c178(EEContext&);  // generated body
void fn_sub_58C178_0058c178__recomp(EEContext&);  // recompiled
void fn_sub_58C180_0058c180(EEContext&);  // generated body
void fn_sub_58C180_0058c180__recomp(EEContext&);  // recompiled
void fn_sub_58C188_0058c188(EEContext&);  // generated body
void fn_sub_58C188_0058c188__recomp(EEContext&);  // recompiled
void fn_sub_58C190_0058c190(EEContext&);  // generated body
void fn_sub_58C190_0058c190__recomp(EEContext&);  // recompiled
void fn_sub_58E260_0058e260(EEContext&);  // generated body
void fn_sub_58E260_0058e260__recomp(EEContext&);  // recompiled
void fn_sub_58E400_0058e400(EEContext&);  // generated body
void fn_sub_58E400_0058e400__recomp(EEContext&);  // recompiled
void fn_sub_58E758_0058e758(EEContext&);  // generated body
void fn_sub_58E758_0058e758__recomp(EEContext&);  // recompiled
void fn_r_lock_def_free_7_0058ea40(EEContext&);  // generated body
void fn_r_lock_def_free_7_0058ea40__recomp(EEContext&);  // recompiled
void fn_sub_5930E0_005930e0(EEContext&);  // generated body
void fn_sub_5930E0_005930e0__recomp(EEContext&);  // recompiled
void fn_sub_5930E8_005930e8(EEContext&);  // generated body
void fn_sub_5930E8_005930e8__recomp(EEContext&);  // recompiled
void fn_sub_5930F0_005930f0(EEContext&);  // generated body
void fn_sub_5930F0_005930f0__recomp(EEContext&);  // recompiled
void fn_sub_5930F8_005930f8(EEContext&);  // generated body
void fn_sub_5930F8_005930f8__recomp(EEContext&);  // recompiled
void fn_sub_593100_00593100(EEContext&);  // generated body
void fn_sub_593100_00593100__recomp(EEContext&);  // recompiled
void fn_sub_593120_00593120(EEContext&);  // generated body
void fn_sub_593120_00593120__recomp(EEContext&);  // recompiled
void fn_sub_593598_00593598(EEContext&);  // generated body
void fn_sub_593598_00593598__recomp(EEContext&);  // recompiled
void fn_sub_593730_00593730(EEContext&);  // generated body
void fn_sub_593730_00593730__recomp(EEContext&);  // recompiled
void fn_sub_5937D0_005937d0(EEContext&);  // generated body
void fn_sub_5937D0_005937d0__recomp(EEContext&);  // recompiled
void fn_sub_594BD0_00594bd0(EEContext&);  // generated body
void fn_sub_594BD0_00594bd0__recomp(EEContext&);  // recompiled
void fn_sub_595770_00595770(EEContext&);  // generated body
void fn_sub_595770_00595770__recomp(EEContext&);  // recompiled
void fn_sub_595780_00595780(EEContext&);  // generated body
void fn_sub_595780_00595780__recomp(EEContext&);  // recompiled
void fn_nullsub_177_00595bb8(EEContext&);  // generated body
void fn_nullsub_177_00595bb8__recomp(EEContext&);  // recompiled
void fn_sub_595CB8_00595cb8(EEContext&);  // generated body
void fn_sub_595CB8_00595cb8__recomp(EEContext&);  // recompiled
void fn_sub_5979F8_005979f8(EEContext&);  // generated body
void fn_sub_5979F8_005979f8__recomp(EEContext&);  // recompiled
void fn_sub_598300_00598300(EEContext&);  // generated body
void fn_sub_598300_00598300__recomp(EEContext&);  // recompiled
void fn_sub_5984C8_005984c8(EEContext&);  // generated body
void fn_sub_5984C8_005984c8__recomp(EEContext&);  // recompiled
void fn_sub_598528_00598528(EEContext&);  // generated body
void fn_sub_598528_00598528__recomp(EEContext&);  // recompiled
void fn_sub_598588_00598588(EEContext&);  // generated body
void fn_sub_598588_00598588__recomp(EEContext&);  // recompiled
void fn_sub_598910_00598910(EEContext&);  // generated body
void fn_sub_598910_00598910__recomp(EEContext&);  // recompiled
void fn_sub_5989F0_005989f0(EEContext&);  // generated body
void fn_sub_5989F0_005989f0__recomp(EEContext&);  // recompiled
void fn_sub_598AE8_00598ae8(EEContext&);  // generated body
void fn_sub_598AE8_00598ae8__recomp(EEContext&);  // recompiled
void fn_sub_598C28_00598c28(EEContext&);  // generated body
void fn_sub_598C28_00598c28__recomp(EEContext&);  // recompiled
void fn_sub_599760_00599760(EEContext&);  // generated body
void fn_sub_599760_00599760__recomp(EEContext&);  // recompiled
void fn_sub_59A0D8_0059a0d8(EEContext&);  // generated body
void fn_sub_59A0D8_0059a0d8__recomp(EEContext&);  // recompiled
void fn_sub_59A188_0059a188(EEContext&);  // generated body
void fn_sub_59A188_0059a188__recomp(EEContext&);  // recompiled
void fn_sub_59A4A8_0059a4a8(EEContext&);  // generated body
void fn_sub_59A4A8_0059a4a8__recomp(EEContext&);  // recompiled
void fn_sub_59A9A0_0059a9a0(EEContext&);  // generated body
void fn_sub_59A9A0_0059a9a0__recomp(EEContext&);  // recompiled
void fn_sub_59AA48_0059aa48(EEContext&);  // generated body
void fn_sub_59AA48_0059aa48__recomp(EEContext&);  // recompiled
void fn_sub_59ADF8_0059adf8(EEContext&);  // generated body
void fn_sub_59ADF8_0059adf8__recomp(EEContext&);  // recompiled
void fn_sub_59AEF8_0059aef8(EEContext&);  // generated body
void fn_sub_59AEF8_0059aef8__recomp(EEContext&);  // recompiled
void fn_sub_59AF80_0059af80(EEContext&);  // generated body
void fn_sub_59AF80_0059af80__recomp(EEContext&);  // recompiled
void fn_sub_59C468_0059c468(EEContext&);  // generated body
void fn_sub_59C468_0059c468__recomp(EEContext&);  // recompiled
void fn_sub_59C7B8_0059c7b8(EEContext&);  // generated body
void fn_sub_59C7B8_0059c7b8__recomp(EEContext&);  // recompiled
void fn_sub_59C9F8_0059c9f8(EEContext&);  // generated body
void fn_sub_59C9F8_0059c9f8__recomp(EEContext&);  // recompiled
void fn_sub_59CC50_0059cc50(EEContext&);  // generated body
void fn_sub_59CC50_0059cc50__recomp(EEContext&);  // recompiled
void fn_sub_59CD00_0059cd00(EEContext&);  // generated body
void fn_sub_59CD00_0059cd00__recomp(EEContext&);  // recompiled
void fn_sub_59CEC8_0059cec8(EEContext&);  // generated body
void fn_sub_59CEC8_0059cec8__recomp(EEContext&);  // recompiled
void fn_sub_59CED0_0059ced0(EEContext&);  // generated body
void fn_sub_59CED0_0059ced0__recomp(EEContext&);  // recompiled
void fn_sub_59CED8_0059ced8(EEContext&);  // generated body
void fn_sub_59CED8_0059ced8__recomp(EEContext&);  // recompiled
void fn_sub_59CEE0_0059cee0(EEContext&);  // generated body
void fn_sub_59CEE0_0059cee0__recomp(EEContext&);  // recompiled
void fn_sub_59CEE8_0059cee8(EEContext&);  // generated body
void fn_sub_59CEE8_0059cee8__recomp(EEContext&);  // recompiled
void fn_sub_59CF08_0059cf08(EEContext&);  // generated body
void fn_sub_59CF08_0059cf08__recomp(EEContext&);  // recompiled
void fn_sub_59EAA8_0059eaa8(EEContext&);  // generated body
void fn_sub_59EAA8_0059eaa8__recomp(EEContext&);  // recompiled
void fn_sub_59EAD0_0059ead0(EEContext&);  // generated body
void fn_sub_59EAD0_0059ead0__recomp(EEContext&);  // recompiled
void fn_WTLS_set_table_2_0059fd70(EEContext&);  // generated body
void fn_WTLS_set_table_2_0059fd70__recomp(EEContext&);  // recompiled
void fn___errno_14_0059fd80(EEContext&);  // generated body
void fn___errno_14_0059fd80__recomp(EEContext&);  // recompiled
void fn_sub_59FDA0_0059fda0(EEContext&);  // generated body
void fn_sub_59FDA0_0059fda0__recomp(EEContext&);  // recompiled
void fn_sub_59FE58_0059fe58(EEContext&);  // generated body
void fn_sub_59FE58_0059fe58__recomp(EEContext&);  // recompiled
void fn_sub_5A0050_005a0050(EEContext&);  // generated body
void fn_sub_5A0050_005a0050__recomp(EEContext&);  // recompiled
void fn_sub_5A00D8_005a00d8(EEContext&);  // generated body
void fn_sub_5A00D8_005a00d8__recomp(EEContext&);  // recompiled
void fn_sub_5A04C0_005a04c0(EEContext&);  // generated body
void fn_sub_5A04C0_005a04c0__recomp(EEContext&);  // recompiled
void fn_sub_5A10F8_005a10f8(EEContext&);  // generated body
void fn_sub_5A10F8_005a10f8__recomp(EEContext&);  // recompiled
void fn_sub_5A1188_005a1188(EEContext&);  // generated body
void fn_sub_5A1188_005a1188__recomp(EEContext&);  // recompiled
void fn_sub_5A13C0_005a13c0(EEContext&);  // generated body
void fn_sub_5A13C0_005a13c0__recomp(EEContext&);  // recompiled
void fn_sub_5A1420_005a1420(EEContext&);  // generated body
void fn_sub_5A1420_005a1420__recomp(EEContext&);  // recompiled
void fn_sub_5A14B0_005a14b0(EEContext&);  // generated body
void fn_sub_5A14B0_005a14b0__recomp(EEContext&);  // recompiled
void fn_sub_5A1518_005a1518(EEContext&);  // generated body
void fn_sub_5A1518_005a1518__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_58C138", 0x58C138, &recomp_gen::fn_sub_58C138_0058c138, &recomp_gen::fn_sub_58C138_0058c138__recomp},
    {"sub_58C178", 0x58C178, &recomp_gen::fn_sub_58C178_0058c178, &recomp_gen::fn_sub_58C178_0058c178__recomp},
    {"sub_58C180", 0x58C180, &recomp_gen::fn_sub_58C180_0058c180, &recomp_gen::fn_sub_58C180_0058c180__recomp},
    {"sub_58C188", 0x58C188, &recomp_gen::fn_sub_58C188_0058c188, &recomp_gen::fn_sub_58C188_0058c188__recomp},
    {"sub_58C190", 0x58C190, &recomp_gen::fn_sub_58C190_0058c190, &recomp_gen::fn_sub_58C190_0058c190__recomp},
    {"sub_58E260", 0x58E260, &recomp_gen::fn_sub_58E260_0058e260, &recomp_gen::fn_sub_58E260_0058e260__recomp},
    {"sub_58E400", 0x58E400, &recomp_gen::fn_sub_58E400_0058e400, &recomp_gen::fn_sub_58E400_0058e400__recomp},
    {"sub_58E758", 0x58E758, &recomp_gen::fn_sub_58E758_0058e758, &recomp_gen::fn_sub_58E758_0058e758__recomp},
    {"r_lock_def_free_7", 0x58EA40, &recomp_gen::fn_r_lock_def_free_7_0058ea40, &recomp_gen::fn_r_lock_def_free_7_0058ea40__recomp},
    {"sub_5930E0", 0x5930E0, &recomp_gen::fn_sub_5930E0_005930e0, &recomp_gen::fn_sub_5930E0_005930e0__recomp},
    {"sub_5930E8", 0x5930E8, &recomp_gen::fn_sub_5930E8_005930e8, &recomp_gen::fn_sub_5930E8_005930e8__recomp},
    {"sub_5930F0", 0x5930F0, &recomp_gen::fn_sub_5930F0_005930f0, &recomp_gen::fn_sub_5930F0_005930f0__recomp},
    {"sub_5930F8", 0x5930F8, &recomp_gen::fn_sub_5930F8_005930f8, &recomp_gen::fn_sub_5930F8_005930f8__recomp},
    {"sub_593100", 0x593100, &recomp_gen::fn_sub_593100_00593100, &recomp_gen::fn_sub_593100_00593100__recomp},
    {"sub_593120", 0x593120, &recomp_gen::fn_sub_593120_00593120, &recomp_gen::fn_sub_593120_00593120__recomp},
    {"sub_593598", 0x593598, &recomp_gen::fn_sub_593598_00593598, &recomp_gen::fn_sub_593598_00593598__recomp},
    {"sub_593730", 0x593730, &recomp_gen::fn_sub_593730_00593730, &recomp_gen::fn_sub_593730_00593730__recomp},
    {"sub_5937D0", 0x5937D0, &recomp_gen::fn_sub_5937D0_005937d0, &recomp_gen::fn_sub_5937D0_005937d0__recomp},
    {"sub_594BD0", 0x594BD0, &recomp_gen::fn_sub_594BD0_00594bd0, &recomp_gen::fn_sub_594BD0_00594bd0__recomp},
    {"sub_595770", 0x595770, &recomp_gen::fn_sub_595770_00595770, &recomp_gen::fn_sub_595770_00595770__recomp},
    {"sub_595780", 0x595780, &recomp_gen::fn_sub_595780_00595780, &recomp_gen::fn_sub_595780_00595780__recomp},
    {"nullsub_177", 0x595BB8, &recomp_gen::fn_nullsub_177_00595bb8, &recomp_gen::fn_nullsub_177_00595bb8__recomp},
    {"sub_595CB8", 0x595CB8, &recomp_gen::fn_sub_595CB8_00595cb8, &recomp_gen::fn_sub_595CB8_00595cb8__recomp},
    {"sub_5979F8", 0x5979F8, &recomp_gen::fn_sub_5979F8_005979f8, &recomp_gen::fn_sub_5979F8_005979f8__recomp},
    {"sub_598300", 0x598300, &recomp_gen::fn_sub_598300_00598300, &recomp_gen::fn_sub_598300_00598300__recomp},
    {"sub_5984C8", 0x5984C8, &recomp_gen::fn_sub_5984C8_005984c8, &recomp_gen::fn_sub_5984C8_005984c8__recomp},
    {"sub_598528", 0x598528, &recomp_gen::fn_sub_598528_00598528, &recomp_gen::fn_sub_598528_00598528__recomp},
    {"sub_598588", 0x598588, &recomp_gen::fn_sub_598588_00598588, &recomp_gen::fn_sub_598588_00598588__recomp},
    {"sub_598910", 0x598910, &recomp_gen::fn_sub_598910_00598910, &recomp_gen::fn_sub_598910_00598910__recomp},
    {"sub_5989F0", 0x5989F0, &recomp_gen::fn_sub_5989F0_005989f0, &recomp_gen::fn_sub_5989F0_005989f0__recomp},
    {"sub_598AE8", 0x598AE8, &recomp_gen::fn_sub_598AE8_00598ae8, &recomp_gen::fn_sub_598AE8_00598ae8__recomp},
    {"sub_598C28", 0x598C28, &recomp_gen::fn_sub_598C28_00598c28, &recomp_gen::fn_sub_598C28_00598c28__recomp},
    {"sub_599760", 0x599760, &recomp_gen::fn_sub_599760_00599760, &recomp_gen::fn_sub_599760_00599760__recomp},
    {"sub_59A0D8", 0x59A0D8, &recomp_gen::fn_sub_59A0D8_0059a0d8, &recomp_gen::fn_sub_59A0D8_0059a0d8__recomp},
    {"sub_59A188", 0x59A188, &recomp_gen::fn_sub_59A188_0059a188, &recomp_gen::fn_sub_59A188_0059a188__recomp},
    {"sub_59A4A8", 0x59A4A8, &recomp_gen::fn_sub_59A4A8_0059a4a8, &recomp_gen::fn_sub_59A4A8_0059a4a8__recomp},
    {"sub_59A9A0", 0x59A9A0, &recomp_gen::fn_sub_59A9A0_0059a9a0, &recomp_gen::fn_sub_59A9A0_0059a9a0__recomp},
    {"sub_59AA48", 0x59AA48, &recomp_gen::fn_sub_59AA48_0059aa48, &recomp_gen::fn_sub_59AA48_0059aa48__recomp},
    {"sub_59ADF8", 0x59ADF8, &recomp_gen::fn_sub_59ADF8_0059adf8, &recomp_gen::fn_sub_59ADF8_0059adf8__recomp},
    {"sub_59AEF8", 0x59AEF8, &recomp_gen::fn_sub_59AEF8_0059aef8, &recomp_gen::fn_sub_59AEF8_0059aef8__recomp},
    {"sub_59AF80", 0x59AF80, &recomp_gen::fn_sub_59AF80_0059af80, &recomp_gen::fn_sub_59AF80_0059af80__recomp},
    {"sub_59C468", 0x59C468, &recomp_gen::fn_sub_59C468_0059c468, &recomp_gen::fn_sub_59C468_0059c468__recomp},
    {"sub_59C7B8", 0x59C7B8, &recomp_gen::fn_sub_59C7B8_0059c7b8, &recomp_gen::fn_sub_59C7B8_0059c7b8__recomp},
    {"sub_59C9F8", 0x59C9F8, &recomp_gen::fn_sub_59C9F8_0059c9f8, &recomp_gen::fn_sub_59C9F8_0059c9f8__recomp},
    {"sub_59CC50", 0x59CC50, &recomp_gen::fn_sub_59CC50_0059cc50, &recomp_gen::fn_sub_59CC50_0059cc50__recomp},
    {"sub_59CD00", 0x59CD00, &recomp_gen::fn_sub_59CD00_0059cd00, &recomp_gen::fn_sub_59CD00_0059cd00__recomp},
    {"sub_59CEC8", 0x59CEC8, &recomp_gen::fn_sub_59CEC8_0059cec8, &recomp_gen::fn_sub_59CEC8_0059cec8__recomp},
    {"sub_59CED0", 0x59CED0, &recomp_gen::fn_sub_59CED0_0059ced0, &recomp_gen::fn_sub_59CED0_0059ced0__recomp},
    {"sub_59CED8", 0x59CED8, &recomp_gen::fn_sub_59CED8_0059ced8, &recomp_gen::fn_sub_59CED8_0059ced8__recomp},
    {"sub_59CEE0", 0x59CEE0, &recomp_gen::fn_sub_59CEE0_0059cee0, &recomp_gen::fn_sub_59CEE0_0059cee0__recomp},
    {"sub_59CEE8", 0x59CEE8, &recomp_gen::fn_sub_59CEE8_0059cee8, &recomp_gen::fn_sub_59CEE8_0059cee8__recomp},
    {"sub_59CF08", 0x59CF08, &recomp_gen::fn_sub_59CF08_0059cf08, &recomp_gen::fn_sub_59CF08_0059cf08__recomp},
    {"sub_59EAA8", 0x59EAA8, &recomp_gen::fn_sub_59EAA8_0059eaa8, &recomp_gen::fn_sub_59EAA8_0059eaa8__recomp},
    {"sub_59EAD0", 0x59EAD0, &recomp_gen::fn_sub_59EAD0_0059ead0, &recomp_gen::fn_sub_59EAD0_0059ead0__recomp},
    {"WTLS_set_table_2", 0x59FD70, &recomp_gen::fn_WTLS_set_table_2_0059fd70, &recomp_gen::fn_WTLS_set_table_2_0059fd70__recomp},
    {"__errno_14", 0x59FD80, &recomp_gen::fn___errno_14_0059fd80, &recomp_gen::fn___errno_14_0059fd80__recomp},
    {"sub_59FDA0", 0x59FDA0, &recomp_gen::fn_sub_59FDA0_0059fda0, &recomp_gen::fn_sub_59FDA0_0059fda0__recomp},
    {"sub_59FE58", 0x59FE58, &recomp_gen::fn_sub_59FE58_0059fe58, &recomp_gen::fn_sub_59FE58_0059fe58__recomp},
    {"sub_5A0050", 0x5A0050, &recomp_gen::fn_sub_5A0050_005a0050, &recomp_gen::fn_sub_5A0050_005a0050__recomp},
    {"sub_5A00D8", 0x5A00D8, &recomp_gen::fn_sub_5A00D8_005a00d8, &recomp_gen::fn_sub_5A00D8_005a00d8__recomp},
    {"sub_5A04C0", 0x5A04C0, &recomp_gen::fn_sub_5A04C0_005a04c0, &recomp_gen::fn_sub_5A04C0_005a04c0__recomp},
    {"sub_5A10F8", 0x5A10F8, &recomp_gen::fn_sub_5A10F8_005a10f8, &recomp_gen::fn_sub_5A10F8_005a10f8__recomp},
    {"sub_5A1188", 0x5A1188, &recomp_gen::fn_sub_5A1188_005a1188, &recomp_gen::fn_sub_5A1188_005a1188__recomp},
    {"sub_5A13C0", 0x5A13C0, &recomp_gen::fn_sub_5A13C0_005a13c0, &recomp_gen::fn_sub_5A13C0_005a13c0__recomp},
    {"sub_5A1420", 0x5A1420, &recomp_gen::fn_sub_5A1420_005a1420, &recomp_gen::fn_sub_5A1420_005a1420__recomp},
    {"sub_5A14B0", 0x5A14B0, &recomp_gen::fn_sub_5A14B0_005a14b0, &recomp_gen::fn_sub_5A14B0_005a14b0__recomp},
    {"sub_5A1518", 0x5A1518, &recomp_gen::fn_sub_5A1518_005a1518, &recomp_gen::fn_sub_5A1518_005a1518__recomp},
};

// Random worlds: 64 KiB of free RAM above the harness's arena.
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(libs23): every body equals its recompiled body on random worlds") {
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

namespace {

namespace L5 = p3fes::game::libs5;
namespace L13 = p3fes::game::libs13;
namespace L23 = p3fes::game::libs23;
namespace T1 = p3fes::game::tail1;

// An SFD handle world (game/include/p3fes/game/libs23.h, libs13.h, tail1.h): the handle at kHandle, valid (+72) most of
// the time, its video-decoder work at handle + sfd::kVdecArea with 16 frame records and the video-input ring, the
// header object (or none), the time record, the parameter words, transfer slot 8's stream and work; every other word
// is drawn from the values the bodies compare against or is a pointer into the world.
constexpr u32 kHandle = 0x01820000u;
constexpr u32 kHandleSpan = 0x10000u;
constexpr u32 kWork = kHandle + L13::sfd::kVdecArea;
constexpr u32 kHdr = kHandle + 0xE000u;        // the header object (beyond the handle's 0x37B0 bytes)
constexpr u32 kTrn8Work = kHandle + 0xC000u;   // transfer slot 8's work
constexpr u32 kOutRecs = kHandle + 5816u;      // the output records sub_593878 matches (+136 i)
constexpr u32 kRing = kWork + L13::vdec::kViBuf;

u32 enum_word(std::mt19937& rng) {
    static const u32 kValues[] = {0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 15u, 16u, 47u, 48u, 0xFFFFFFFFu, 0xFFFFFFFEu,
                                  63u, 64u, 512u, 1000u, 2048u, 24000u, 0x7FFFFFFFu};
    const u32 k = rng() % 8;
    if (k < 5) return kValues[rng() % (sizeof kValues / sizeof kValues[0])];
    if (k < 7) return kHandle + ((rng() % kHandleSpan) & ~3u);
    return rng() % 0x10000u;
}

void w8(Machine& m, u32 va, u8 v) { *m.at(va) = v; }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
u16 r16(Machine& m, u32 va) {
    u16 v = 0;
    std::memcpy(&v, m.at(va), 2);
    return v;
}
u32 r32(Machine& m, u32 va) {
    u32 v = 0;
    std::memcpy(&v, m.at(va), 4);
    return v;
}

void sfd_world(Machine& m, std::mt19937& rng) {
    for (u32 i = 0; i + 4 <= kHandleSpan; i += 4) w32(m, kHandle + i, enum_word(rng));
    w32(m, kHandle + T1::sfd::kHandleValid, rng() % 4 == 0 ? 0u : 1u + rng() % 6);
    w32(m, kHandle + L13::sfd::kReq, rng() % 7);
    w32(m, kHandle + T1::sfd::kHandleInfo, rng() % 2);
    w32(m, kHandle + L13::sfd::kVdecWork, kWork);
    w32(m, kHandle + L13::sfd::kHdrObj, rng() % 3 == 0 ? 0u : kHdr);
    w32(m, kHandle + L23::sfd::kTimeSrc, rng() % 3);
    w32(m, kHandle + L5::sfdh::kPara + L23::sfd::kParaClock, rng() % 2);
    w32(m, kHandle + L5::sfdh::kTrn8Work, kTrn8Work);
    w32(m, kHandle + L5::sfdh::kTrn8Stream, rng() % 3 == 0 ? 8u : rng() % 8);
    w32(m, kRing + L13::vibuf::kBytes, rng() % 5 == 0 ? 0u : 0x800u * (1 + rng() % 64));
    w32(m, kWork + L13::vdec::kFrameCount, rng() % 17);
    for (u32 i = 0; i < 16; ++i) w32(m, kWork + L13::vdec::kFrames + L13::frm::kSize * i + L13::frm::kState, rng() % 5);
}

u64 sfd_arg(std::mt19937& rng) {
    const u32 k = rng() % 8;
    if (k < 4) return sx(kHandle);
    if (k < 5) return sx(kOutRecs + 136u * (rng() % 16));
    if (k < 6) return sx(kHandle + ((rng() % kHandleSpan) & ~15u));
    return sx(enum_word(rng));
}

// Pairs with sprintf stood in (the only callee the bodies meet that this build does not emit and that no current packet
// takes; sub_5A1188 formats with it): both bodies get a fresh set and the two call logs must be equal.
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
hgp::Run spair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what, u64 t0) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    for (StandInWorld* w : {wh.get(), wr.get()}) install_sprintf(w->si);
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
    HwCheck hw;
    hw.gpr_in[GPR_T0] = t0;  // the fifth argument (sub_58E758, sub_594BD0, sub_59C7B8)
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, what, hw);
    expect_same_log(wh->si, wr->si, what);
    return r;
}

const Case& find_case(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

u64 v0_of(const hgp::Run& r) { return r.end.gpr[2].u64[0]; }

void run_sfd_worlds(Machine& m, u32 seeds, const char* label) {
    const char* only = std::getenv("P3FES_HG_ONLY");
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            std::mt19937 rng{seed * 104729u + c.addr};
            sfd_world(m, rng);
            const Args args{sfd_arg(rng), sfd_arg(rng), sfd_arg(rng), sfd_arg(rng)};
            stops += spair(m, c.hand, c.recomp, args, seed, c.name, sfd_arg(rng)).stopped ? 1 : 0;
        }
        const std::string summary = std::string(label) + " " + c.name + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

}  // namespace

TEST_CASE("game(libs23): every body equals its recompiled body on SFD handle worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");
    run_sfd_worlds(*m, env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : 32u, "sfd world");
}

// The same worlds over the RAM of the replay snapshots (the real globals: the handle table 0x7B4774, the SFD work
// block, the saved frame-buffer configuration 0x9ACAF0, the errno word); and, where a snapshot holds an open SFD handle,
// every body on that handle as it is.
TEST_CASE("game(libs23): every body equals its recompiled body on the replay snapshots") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* kSnaps[] = {"dorm_replay_4900", "b_5800", "climb_ref_17000"};
    for (const char* dir : kSnaps) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.size() != EEMemory::kMainRamSize) {
            MESSAGE("SKIP: snapshot " << dir << " not found");
            continue;
        }
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        run_sfd_worlds(*m, 4u, dir);
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        std::vector<u32> handles;  // the open-handle table 0x7B4774[8] and the last checked handle 0x7B4568
        for (u32 i = 0; i <= 8; ++i) {
            u32 h = 0;
            std::memcpy(&h, snap.data() + (i < 8 ? T1::sfd::kHandles + 4 * i : T1::sfd::kLastHandle), 4);
            if (h != 0 && h < 0x01FF0000u && std::find(handles.begin(), handles.end(), h) == handles.end()) handles.push_back(h);
        }
        for (const u32 h : handles) {
            for (const Case& c : kCases) {
                std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
                for (u32 seed = 1; seed <= 2; ++seed) {
                    std::mt19937 rng{seed * 131u + c.addr};
                    const Args args{sx(h), rng() % 4, sx(kWorld + 0x100u * (rng() % 16)), sx(kWorld + 0x40u * (rng() % 64))};
                    spair(*m, c.hand, c.recomp, args, seed, c.name, sx(kWorld + 0x200u));
                }
            }
        }
        const std::string note = std::string(dir) + ": " + std::to_string(handles.size()) + " open SFD handles";
        MESSAGE(note);
    }
}

// Documented rules, from the instructions (both bodies run and are compared, then the result is checked). Only results
// that hold whatever the callees are (replaced or recompiled) are checked.
TEST_CASE("game(libs23): stubs, globals, time codes, frame layout, handle words and tag rules") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const auto run = [&](const char* name, const Args& a, u64 t0 = 0) {
        const Case& c = find_case(name);
        return spair(*m, c.hand, c.recomp, a, 1, c.name, t0);
    };
    const u32 w = kWorld;
    std::memset(m->at(w), 0, kWorldSize);
    // The stubs return 0; sub_595780 the sceMpeg record's size.
    for (const char* n : {"sub_58C138", "sub_58C178", "sub_58C180", "sub_58C188", "sub_58C190", "sub_5930E0", "sub_5930E8",
                          "sub_5930F0", "sub_5930F8", "sub_59C9F8", "sub_59CC50", "sub_59CD00", "sub_59CEC8", "sub_59CED0",
                          "sub_59CED8", "sub_59CEE0"})
        CHECK(v0_of(run(n, Args{7, 7, 7, 7})) == 0u);
    CHECK(v0_of(run("sub_595780", Args{})) == 72u);
    run("nullsub_177", Args{});
    // Globals: sub_59C468 stores its two arguments; WTLS_set_table_2 / __errno_14 set and read 0x7B491C.
    run("sub_59C468", Args{0x11u, 0x22u, 0, 0});
    CHECK(r32(*m, L23::kPairA) == 0x11u);
    CHECK(r32(*m, L23::kPairB) == 0x22u);
    run("WTLS_set_table_2", Args{0xABCDu, 0, 0, 0});
    CHECK(r32(*m, L23::kErrno) == 0xABCDu);
    CHECK(v0_of(run("__errno_14", Args{})) == 0xABCDu);
    // Stepping record: pointer += step x (count - 1), step negated and returned.
    w32(*m, w + L23::step::kPtr, 0x1000u);
    w32(*m, w + L23::step::kCount, 5);
    w32(*m, w + L23::step::kStep, 16);
    CHECK(v0_of(run("sub_59EAA8", Args{sx(w), 0, 0, 0})) == sx(0xFFFFFFF0u));
    CHECK(r32(*m, w + L23::step::kPtr) == 0x1040u);
    CHECK(v0_of(run("sub_59EAD0", Args{sx(w), 0, 0, 0})) == 16u);
    CHECK(r32(*m, w + L23::step::kPtr) == 0x1000u);
    // Plane pitches: Y = the even part (toward zero), Cb / Cr half of it.
    run("sub_5A00D8", Args{sx(w + 0x40), 101, 0, 0});
    CHECK(r32(*m, w + 0x40 + L23::planes::kYPitch) == 100u);
    CHECK(r32(*m, w + 0x40 + L23::planes::kCbPitch) == 50u);
    CHECK(r32(*m, w + 0x40 + L23::planes::kCrPitch) == 50u);
    run("sub_5A00D8", Args{sx(w + 0x40), sx(0xFFFFFFF9u), 0, 0});  // -7
    CHECK(r32(*m, w + 0x40 + L23::planes::kYPitch) == 0xFFFFFFFAu);
    CHECK(r32(*m, w + 0x40 + L23::planes::kCbPitch) == 0xFFFFFFFDu);
    // sub_5A04C0: the pair +12 / +16 when +8 is 1, else zeros.
    w32(*m, w + 0x80 + 8, 1);
    w32(*m, w + 0x80 + 12, 0x33u);
    w32(*m, w + 0x80 + 16, 0x44u);
    run("sub_5A04C0", Args{sx(w + 0x80), sx(w + 0xA0), sx(w + 0xA4), 0});
    CHECK(r32(*m, w + 0xA0) == 0x33u);
    CHECK(r32(*m, w + 0xA4) == 0x44u);
    w32(*m, w + 0x80 + 8, 2);
    run("sub_5A04C0", Args{sx(w + 0x80), sx(w + 0xA0), sx(w + 0xA4), 0});
    CHECK(r32(*m, w + 0xA0) == 0u);
    CHECK(r32(*m, w + 0xA4) == 0u);
    // Record words through +36: sub_59FDA0 sets +72 of it, sub_5A10F8 reads +4 of it; sub_59FE58 reads +52.
    w32(*m, w + 0xC0 + 36, w + 0x100);
    w32(*m, w + 0xC0 + 52, 0x55u);
    w32(*m, w + 0x104, 0x66u);
    run("sub_59FDA0", Args{sx(w + 0xC0), 0x77u, 0, 0});
    CHECK(r32(*m, w + 0x100 + 72) == 0x77u);
    CHECK(v0_of(run("sub_5A10F8", Args{sx(w + 0xC0), 0, 0, 0})) == 0x66u);
    CHECK(v0_of(run("sub_59FE58", Args{sx(w + 0xC0), 0, 0, 0})) == 0x55u);
    // 23.976 drop-frame time code 1:12:30:05 (+1 extra, 1 field): (86,292 + 1,438 x 12 + 2 x (12 x 30 + 1) + 5 + 1) x
    // 1,000 + 500 = 104,276,500 into *a2; *a3 = a0.
    const u32 tc = w + 0x200;
    w32(*m, tc + 8, 1);
    w32(*m, tc + 12, 12);
    w32(*m, tc + 16, 30);
    w32(*m, tc + 20, 5);
    w32(*m, tc + 24, 1);
    w32(*m, tc + 28, 0x00010000u);  // s16 +30 = 1
    run("sub_59AA48", Args{24000u, sx(tc), sx(w + 0x240), sx(w + 0x244)});
    CHECK(r32(*m, w + 0x240) == 104276500u);
    CHECK(r32(*m, w + 0x244) == 24000u);
    // Frame-buffer layout of 640 x 448 at 0x100000: pitches 640 / 320, 28 macroblock rows.
    const u32 cfg = w + 0x300;
    w32(*m, cfg + L23::fbcfg::kWidth, 640);
    w32(*m, cfg + L23::fbcfg::kHeight, 448);
    w32(*m, cfg + L23::fbcfg::kBase, 0x100000u);
    run("sub_58E400", Args{sx(cfg), sx(w + 0x340), 0, 0});
    CHECK(r16(*m, w + 0x340 + 14) == 640u);
    CHECK(r16(*m, w + 0x340 + 12) == 320u);
    CHECK(r32(*m, w + 0x340 + 8) == 0x100000u);
    CHECK(r32(*m, w + 0x340 + 0) == 0x100000u + 10u * 28u * 1024u);
    CHECK(r32(*m, w + 0x340 + 4) == 0x100000u + 10u * 28u * 1024u + 5u * 28u * 512u);
    // sub_58E260 keeps the configuration at 0x9ACAF0 with +16 / +32 rounded up to 64 and clears the areas after it.
    w32(*m, cfg + L23::fbcfg::kSize16, 100);
    w32(*m, cfg + L23::fbcfg::kBase, 0x100001u);
    std::memset(m->at(L23::fbcfg::kClear8), 0xEE, 8 + 64);
    run("sub_58E260", Args{sx(cfg), 0, 0, 0});
    CHECK(r32(*m, L23::fbcfg::kGlobal + L23::fbcfg::kWidth) == 640u);
    CHECK(r32(*m, L23::fbcfg::kGlobal + L23::fbcfg::kSize16) == 128u);
    CHECK(r32(*m, L23::fbcfg::kGlobal + L23::fbcfg::kBase) == 0x100040u);
    CHECK(r32(*m, L23::fbcfg::kClear8 + 4) == 0u);
    CHECK(r32(*m, L23::fbcfg::kClear64 + 60) == 0u);

    // Handle words (a valid handle: +72 non-zero).
    std::mt19937 rng{23};
    sfd_world(*m, rng);
    const u32 h = kHandle;
    w32(*m, h + T1::sfd::kHandleValid, 3);
    w32(*m, h + L13::sfd::kHdrObj, kHdr);
    run("sub_5984C8", Args{sx(h), 0x1234u, 0, 0});
    CHECK(r32(*m, kHdr + L23::hdr::kUserWord) == 0x1234u);
    // sub_599760: the header-sector copy (+268) and its size (+264) once a header was parsed (+120), else zeros.
    w32(*m, h + T1::sfd::kHandleInfo, 1);
    w32(*m, h + 264, 77);
    CHECK(v0_of(run("sub_599760", Args{sx(h), sx(w + 0x400), sx(w + 0x404), 0})) == 0u);
    CHECK(r32(*m, w + 0x400) == h + 268);
    CHECK(r32(*m, w + 0x404) == 77u);
    w32(*m, h + T1::sfd::kHandleInfo, 0);
    run("sub_599760", Args{sx(h), sx(w + 0x400), sx(w + 0x404), 0});
    CHECK(r32(*m, w + 0x400) == 0u);
    CHECK(r32(*m, w + 0x404) == 0u);
    // sub_59A4A8 / sub_59AEF8: the time record's counters and pair, the time-updated mark.
    const u32 trec = h + L5::sfdh::kTimeRec;
    w32(*m, trec + L23::sfd::kTimeTick, 9);
    w32(*m, h + L5::sfdh::kTimeUpd, 0);
    run("sub_59A4A8", Args{sx(h), 0, 0, 0});
    CHECK(r32(*m, trec + L23::sfd::kTimeTick) == 10u);
    CHECK(r32(*m, h + L5::sfdh::kTimeUpd) == 1u);
    w32(*m, trec + L23::sfd::kTimeSet, 4);
    w32(*m, h + L5::sfdh::kTimeUpd, 0);
    run("sub_59AEF8", Args{sx(h), 0x51u, 0x52u, 0});
    CHECK(r32(*m, trec + L23::sfd::kTimeSet) == 5u);
    CHECK(r32(*m, trec + L23::sfd::kTimeSetA) == 0x51u);
    CHECK(r32(*m, trec + L23::sfd::kTimeSetB) == 0x52u);
    CHECK(r32(*m, h + L5::sfdh::kTimeUpd) == 1u);
    // The handle's frame-lock total goes up / down by one, found frame or not, and is returned.
    w32(*m, h + L23::sfd::kFrameLocks, 6);
    CHECK(v0_of(run("sub_593730", Args{sx(h), sx(kOutRecs), 0, 0})) == 7u);
    CHECK(r32(*m, h + L23::sfd::kFrameLocks) == 7u);
    CHECK(v0_of(run("sub_5937D0", Args{sx(h), sx(kOutRecs), 0, 0})) == 6u);
    CHECK(r32(*m, h + L23::sfd::kFrameLocks) == 6u);
    // An invalid handle (+72 = 0) leaves the header object's word alone (the error path).
    w32(*m, h + T1::sfd::kHandleValid, 0);
    run("sub_5984C8", Args{sx(h), 0x9999u, 0, 0});
    CHECK(r32(*m, kHdr + L23::hdr::kUserWord) == 0x1234u);

    // SUD tags: "<SUDPS_><000013>" then the number "02" at +16, three index characters, "\n".
    const u32 tag = w + 0x600;
    std::memset(m->at(tag), 0, 64);
    std::memset(m->at(w + 0x680), 0, 16);  // the three indices sub_5A1218 picks with
    run("sub_5A1188", Args{sx(tag), 0, sx(w + 0x680), 0});
    CHECK(std::memcmp(m->at(tag), "<SUDPS_><000013>02", 18) == 0);
    CHECK(*m->at(tag + 21) == '\n');
    // The tag's number (+16) is at least 2 here, so bytes +20 / +21 / +22 decide.
    w8(*m, tag + 20, 'I');
    w8(*m, tag + 21, 'P');
    w8(*m, tag + 22, 'A');
    CHECK(v0_of(run("sub_5A13C0", Args{sx(tag), 0, 0, 0})) == 1u);
    CHECK(v0_of(run("sub_5A1420", Args{sx(tag), 0, 0, 0})) == 1u);
    CHECK(v0_of(run("sub_5A14B0", Args{sx(tag), 0, 0, 0})) == 0u);
    w8(*m, tag + 20, 'X');
    w8(*m, tag + 21, 'I');
    w8(*m, tag + 22, 'B');
    CHECK(v0_of(run("sub_5A13C0", Args{sx(tag), 0, 0, 0})) == 0u);
    CHECK(v0_of(run("sub_5A1420", Args{sx(tag), 0, 0, 0})) == 2u);
    CHECK(v0_of(run("sub_5A14B0", Args{sx(tag), 0, 0, 0})) == 1u);
    w8(*m, tag + 21, 'Z');
    CHECK(v0_of(run("sub_5A1420", Args{sx(tag), 0, 0, 0})) == 0u);
    // A null tag or a negative length gives 0.
    for (const char* n : {"sub_5A13C0", "sub_5A1420", "sub_5A14B0", "sub_5A1518"}) {
        CHECK(v0_of(run(n, Args{0, 0, 0, 0})) == 0u);
        CHECK(v0_of(run(n, Args{sx(tag), sx(0xFFFFFFFFu), 0, 0})) == 0u);
    }
}

#else

TEST_CASE("game(libs23): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
