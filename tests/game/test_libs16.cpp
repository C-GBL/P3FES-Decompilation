// Pair tests for slice libs16 (CRI Sofdec, 0x5886B8-0x598D20): every body against its recompiled body, compared by
// tests/game/handgen_pairs.h -- the whole register file and cycle count at every check point and at the return /
// stop, all 32 MiB of RAM, the scratchpad, the BIOS window and the bus log -- on random worlds, on SFD handle worlds
// (libs13.h's handle, video-decoder work and frame records), on the replay snapshots' RAM, and a few documented-rule
// checks. Callees this build does not emit stop both runs at the same call.
#include "handgen_pairs.h"

#include "stand_ins.h"
#include "p3fes/game/libs16.h"
#include "p3fes/game/libs13.h"

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
void fn_sub_5886B8_005886b8(EEContext&);  // generated body
void fn_sub_5886B8_005886b8__recomp(EEContext&);  // recompiled
void fn_sub_5886D8_005886d8(EEContext&);  // generated body
void fn_sub_5886D8_005886d8__recomp(EEContext&);  // recompiled
void fn_sub_5886F8_005886f8(EEContext&);  // generated body
void fn_sub_5886F8_005886f8__recomp(EEContext&);  // recompiled
void fn_sub_588718_00588718(EEContext&);  // generated body
void fn_sub_588718_00588718__recomp(EEContext&);  // recompiled
void fn_sub_588738_00588738(EEContext&);  // generated body
void fn_sub_588738_00588738__recomp(EEContext&);  // recompiled
void fn_sub_589258_00589258(EEContext&);  // generated body
void fn_sub_589258_00589258__recomp(EEContext&);  // recompiled
void fn_sub_589F00_00589f00(EEContext&);  // generated body
void fn_sub_589F00_00589f00__recomp(EEContext&);  // recompiled
void fn_sub_58A080_0058a080(EEContext&);  // generated body
void fn_sub_58A080_0058a080__recomp(EEContext&);  // recompiled
void fn_sub_58A1C0_0058a1c0(EEContext&);  // generated body
void fn_sub_58A1C0_0058a1c0__recomp(EEContext&);  // recompiled
void fn_sub_58A3E8_0058a3e8(EEContext&);  // generated body
void fn_sub_58A3E8_0058a3e8__recomp(EEContext&);  // recompiled
void fn_sub_58A488_0058a488(EEContext&);  // generated body
void fn_sub_58A488_0058a488__recomp(EEContext&);  // recompiled
void fn_sub_58A538_0058a538(EEContext&);  // generated body
void fn_sub_58A538_0058a538__recomp(EEContext&);  // recompiled
void fn_sub_58A598_0058a598(EEContext&);  // generated body
void fn_sub_58A598_0058a598__recomp(EEContext&);  // recompiled
void fn_sub_58A5A0_0058a5a0(EEContext&);  // generated body
void fn_sub_58A5A0_0058a5a0__recomp(EEContext&);  // recompiled
void fn_sub_58A658_0058a658(EEContext&);  // generated body
void fn_sub_58A658_0058a658__recomp(EEContext&);  // recompiled
void fn_sub_58A740_0058a740(EEContext&);  // generated body
void fn_sub_58A740_0058a740__recomp(EEContext&);  // recompiled
void fn_sub_58A7D8_0058a7d8(EEContext&);  // generated body
void fn_sub_58A7D8_0058a7d8__recomp(EEContext&);  // recompiled
void fn_sub_58A8C8_0058a8c8(EEContext&);  // generated body
void fn_sub_58A8C8_0058a8c8__recomp(EEContext&);  // recompiled
void fn_sub_58A918_0058a918(EEContext&);  // generated body
void fn_sub_58A918_0058a918__recomp(EEContext&);  // recompiled
void fn_sub_58AA88_0058aa88(EEContext&);  // generated body
void fn_sub_58AA88_0058aa88__recomp(EEContext&);  // recompiled
void fn_sub_58B4A8_0058b4a8(EEContext&);  // generated body
void fn_sub_58B4A8_0058b4a8__recomp(EEContext&);  // recompiled
void fn_sub_58BD68_0058bd68(EEContext&);  // generated body
void fn_sub_58BD68_0058bd68__recomp(EEContext&);  // recompiled
void fn_cosl_12_0058c0a0(EEContext&);  // generated body
void fn_cosl_12_0058c0a0__recomp(EEContext&);  // recompiled
void fn_sub_58C0D8_0058c0d8(EEContext&);  // generated body
void fn_sub_58C0D8_0058c0d8__recomp(EEContext&);  // recompiled
void fn___env_unlock_11_0058c0f8(EEContext&);  // generated body
void fn___env_unlock_11_0058c0f8__recomp(EEContext&);  // recompiled
void fn_sub_58C198_0058c198(EEContext&);  // generated body
void fn_sub_58C198_0058c198__recomp(EEContext&);  // recompiled
void fn_sub_58C1B8_0058c1b8(EEContext&);  // generated body
void fn_sub_58C1B8_0058c1b8__recomp(EEContext&);  // recompiled
void fn_sub_58C1E0_0058c1e0(EEContext&);  // generated body
void fn_sub_58C1E0_0058c1e0__recomp(EEContext&);  // recompiled
void fn_sub_58C200_0058c200(EEContext&);  // generated body
void fn_sub_58C200_0058c200__recomp(EEContext&);  // recompiled
void fn_sub_58C220_0058c220(EEContext&);  // generated body
void fn_sub_58C220_0058c220__recomp(EEContext&);  // recompiled
void fn_r_lock_def_free_6_0058c380(EEContext&);  // generated body
void fn_r_lock_def_free_6_0058c380__recomp(EEContext&);  // recompiled
void fn_sub_58DF90_0058df90(EEContext&);  // generated body
void fn_sub_58DF90_0058df90__recomp(EEContext&);  // recompiled
void fn_sub_58E010_0058e010(EEContext&);  // generated body
void fn_sub_58E010_0058e010__recomp(EEContext&);  // recompiled
void fn_sub_58E018_0058e018(EEContext&);  // generated body
void fn_sub_58E018_0058e018__recomp(EEContext&);  // recompiled
void fn_sub_58E020_0058e020(EEContext&);  // generated body
void fn_sub_58E020_0058e020__recomp(EEContext&);  // recompiled
void fn_sub_58E028_0058e028(EEContext&);  // generated body
void fn_sub_58E028_0058e028__recomp(EEContext&);  // recompiled
void fn_sub_58E030_0058e030(EEContext&);  // generated body
void fn_sub_58E030_0058e030__recomp(EEContext&);  // recompiled
void fn_sub_58E050_0058e050(EEContext&);  // generated body
void fn_sub_58E050_0058e050__recomp(EEContext&);  // recompiled
void fn_sub_58E070_0058e070(EEContext&);  // generated body
void fn_sub_58E070_0058e070__recomp(EEContext&);  // recompiled
void fn_sub_58E090_0058e090(EEContext&);  // generated body
void fn_sub_58E090_0058e090__recomp(EEContext&);  // recompiled
void fn_sub_58E0B0_0058e0b0(EEContext&);  // generated body
void fn_sub_58E0B0_0058e0b0__recomp(EEContext&);  // recompiled
void fn_sub_58E160_0058e160(EEContext&);  // generated body
void fn_sub_58E160_0058e160__recomp(EEContext&);  // recompiled
void fn_sub_58E4A0_0058e4a0(EEContext&);  // generated body
void fn_sub_58E4A0_0058e4a0__recomp(EEContext&);  // recompiled
void fn_sub_58E6E8_0058e6e8(EEContext&);  // generated body
void fn_sub_58E6E8_0058e6e8__recomp(EEContext&);  // recompiled
void fn_sub_58FC30_0058fc30(EEContext&);  // generated body
void fn_sub_58FC30_0058fc30__recomp(EEContext&);  // recompiled
void fn_sub_58FD00_0058fd00(EEContext&);  // generated body
void fn_sub_58FD00_0058fd00__recomp(EEContext&);  // recompiled
void fn_sub_58FD60_0058fd60(EEContext&);  // generated body
void fn_sub_58FD60_0058fd60__recomp(EEContext&);  // recompiled
void fn_sub_590430_00590430(EEContext&);  // generated body
void fn_sub_590430_00590430__recomp(EEContext&);  // recompiled
void fn_sub_5905B0_005905b0(EEContext&);  // generated body
void fn_sub_5905B0_005905b0__recomp(EEContext&);  // recompiled
void fn_sub_590878_00590878(EEContext&);  // generated body
void fn_sub_590878_00590878__recomp(EEContext&);  // recompiled
void fn_sub_590A28_00590a28(EEContext&);  // generated body
void fn_sub_590A28_00590a28__recomp(EEContext&);  // recompiled
void fn_sub_591700_00591700(EEContext&);  // generated body
void fn_sub_591700_00591700__recomp(EEContext&);  // recompiled
void fn_sub_591808_00591808(EEContext&);  // generated body
void fn_sub_591808_00591808__recomp(EEContext&);  // recompiled
void fn_sub_5918A8_005918a8(EEContext&);  // generated body
void fn_sub_5918A8_005918a8__recomp(EEContext&);  // recompiled
void fn_sub_591988_00591988(EEContext&);  // generated body
void fn_sub_591988_00591988__recomp(EEContext&);  // recompiled
void fn_sub_591B00_00591b00(EEContext&);  // generated body
void fn_sub_591B00_00591b00__recomp(EEContext&);  // recompiled
void fn_sub_591C08_00591c08(EEContext&);  // generated body
void fn_sub_591C08_00591c08__recomp(EEContext&);  // recompiled
void fn_sub_5927D8_005927d8(EEContext&);  // generated body
void fn_sub_5927D8_005927d8__recomp(EEContext&);  // recompiled
void fn_sub_592938_00592938(EEContext&);  // generated body
void fn_sub_592938_00592938__recomp(EEContext&);  // recompiled
void fn_sub_592EF8_00592ef8(EEContext&);  // generated body
void fn_sub_592EF8_00592ef8__recomp(EEContext&);  // recompiled
void fn_sub_593608_00593608(EEContext&);  // generated body
void fn_sub_593608_00593608__recomp(EEContext&);  // recompiled
void fn_sub_5938C0_005938c0(EEContext&);  // generated body
void fn_sub_5938C0_005938c0__recomp(EEContext&);  // recompiled
void fn_sub_593948_00593948(EEContext&);  // generated body
void fn_sub_593948_00593948__recomp(EEContext&);  // recompiled
void fn_sub_593AA0_00593aa0(EEContext&);  // generated body
void fn_sub_593AA0_00593aa0__recomp(EEContext&);  // recompiled
void fn_sub_593AC8_00593ac8(EEContext&);  // generated body
void fn_sub_593AC8_00593ac8__recomp(EEContext&);  // recompiled
void fn_sub_593B10_00593b10(EEContext&);  // generated body
void fn_sub_593B10_00593b10__recomp(EEContext&);  // recompiled
void fn_sub_593BF8_00593bf8(EEContext&);  // generated body
void fn_sub_593BF8_00593bf8__recomp(EEContext&);  // recompiled
void fn_sub_593C58_00593c58(EEContext&);  // generated body
void fn_sub_593C58_00593c58__recomp(EEContext&);  // recompiled
void fn_sub_593CE8_00593ce8(EEContext&);  // generated body
void fn_sub_593CE8_00593ce8__recomp(EEContext&);  // recompiled
void fn_sub_593FD0_00593fd0(EEContext&);  // generated body
void fn_sub_593FD0_00593fd0__recomp(EEContext&);  // recompiled
void fn_sub_594B18_00594b18(EEContext&);  // generated body
void fn_sub_594B18_00594b18__recomp(EEContext&);  // recompiled
void fn_sub_594E50_00594e50(EEContext&);  // generated body
void fn_sub_594E50_00594e50__recomp(EEContext&);  // recompiled
void fn_sub_594E60_00594e60(EEContext&);  // generated body
void fn_sub_594E60_00594e60__recomp(EEContext&);  // recompiled
void fn_sub_594F68_00594f68(EEContext&);  // generated body
void fn_sub_594F68_00594f68__recomp(EEContext&);  // recompiled
void fn_sub_595788_00595788(EEContext&);  // generated body
void fn_sub_595788_00595788__recomp(EEContext&);  // recompiled
void fn_sub_5958F8_005958f8(EEContext&);  // generated body
void fn_sub_5958F8_005958f8__recomp(EEContext&);  // recompiled
void fn_sub_595A50_00595a50(EEContext&);  // generated body
void fn_sub_595A50_00595a50__recomp(EEContext&);  // recompiled
void fn_sub_595AC0_00595ac0(EEContext&);  // generated body
void fn_sub_595AC0_00595ac0__recomp(EEContext&);  // recompiled
void fn_sub_596340_00596340(EEContext&);  // generated body
void fn_sub_596340_00596340__recomp(EEContext&);  // recompiled
void fn_sub_5965E0_005965e0(EEContext&);  // generated body
void fn_sub_5965E0_005965e0__recomp(EEContext&);  // recompiled
void fn_sub_596818_00596818(EEContext&);  // generated body
void fn_sub_596818_00596818__recomp(EEContext&);  // recompiled
void fn_sub_596B28_00596b28(EEContext&);  // generated body
void fn_sub_596B28_00596b28__recomp(EEContext&);  // recompiled
void fn_sub_597168_00597168(EEContext&);  // generated body
void fn_sub_597168_00597168__recomp(EEContext&);  // recompiled
void fn_thread_leave_1_00597aa0(EEContext&);  // generated body
void fn_thread_leave_1_00597aa0__recomp(EEContext&);  // recompiled
void fn_sub_597B88_00597b88(EEContext&);  // generated body
void fn_sub_597B88_00597b88__recomp(EEContext&);  // recompiled
void fn_sub_597E98_00597e98(EEContext&);  // generated body
void fn_sub_597E98_00597e98__recomp(EEContext&);  // recompiled
void fn_sub_597F20_00597f20(EEContext&);  // generated body
void fn_sub_597F20_00597f20__recomp(EEContext&);  // recompiled
void fn_sub_598030_00598030(EEContext&);  // generated body
void fn_sub_598030_00598030__recomp(EEContext&);  // recompiled
void fn_sub_598140_00598140(EEContext&);  // generated body
void fn_sub_598140_00598140__recomp(EEContext&);  // recompiled
void fn_sub_5981D8_005981d8(EEContext&);  // generated body
void fn_sub_5981D8_005981d8__recomp(EEContext&);  // recompiled
void fn_sub_598348_00598348(EEContext&);  // generated body
void fn_sub_598348_00598348__recomp(EEContext&);  // recompiled
void fn_sub_5983B8_005983b8(EEContext&);  // generated body
void fn_sub_5983B8_005983b8__recomp(EEContext&);  // recompiled
void fn_sub_598470_00598470(EEContext&);  // generated body
void fn_sub_598470_00598470__recomp(EEContext&);  // recompiled
void fn_sub_598688_00598688(EEContext&);  // generated body
void fn_sub_598688_00598688__recomp(EEContext&);  // recompiled
void fn_sub_5987F0_005987f0(EEContext&);  // generated body
void fn_sub_5987F0_005987f0__recomp(EEContext&);  // recompiled
void fn_sub_598870_00598870(EEContext&);  // generated body
void fn_sub_598870_00598870__recomp(EEContext&);  // recompiled
void fn_sub_5988F0_005988f0(EEContext&);  // generated body
void fn_sub_5988F0_005988f0__recomp(EEContext&);  // recompiled
void fn_sub_598A90_00598a90(EEContext&);  // generated body
void fn_sub_598A90_00598a90__recomp(EEContext&);  // recompiled
void fn_sub_598B90_00598b90(EEContext&);  // generated body
void fn_sub_598B90_00598b90__recomp(EEContext&);  // recompiled
void fn_sub_598D20_00598d20(EEContext&);  // generated body
void fn_sub_598D20_00598d20__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_5886B8", 0x5886B8, &recomp_gen::fn_sub_5886B8_005886b8, &recomp_gen::fn_sub_5886B8_005886b8__recomp},
    {"sub_5886D8", 0x5886D8, &recomp_gen::fn_sub_5886D8_005886d8, &recomp_gen::fn_sub_5886D8_005886d8__recomp},
    {"sub_5886F8", 0x5886F8, &recomp_gen::fn_sub_5886F8_005886f8, &recomp_gen::fn_sub_5886F8_005886f8__recomp},
    {"sub_588718", 0x588718, &recomp_gen::fn_sub_588718_00588718, &recomp_gen::fn_sub_588718_00588718__recomp},
    {"sub_588738", 0x588738, &recomp_gen::fn_sub_588738_00588738, &recomp_gen::fn_sub_588738_00588738__recomp},
    {"sub_589258", 0x589258, &recomp_gen::fn_sub_589258_00589258, &recomp_gen::fn_sub_589258_00589258__recomp},
    {"sub_589F00", 0x589F00, &recomp_gen::fn_sub_589F00_00589f00, &recomp_gen::fn_sub_589F00_00589f00__recomp},
    {"sub_58A080", 0x58A080, &recomp_gen::fn_sub_58A080_0058a080, &recomp_gen::fn_sub_58A080_0058a080__recomp},
    {"sub_58A1C0", 0x58A1C0, &recomp_gen::fn_sub_58A1C0_0058a1c0, &recomp_gen::fn_sub_58A1C0_0058a1c0__recomp},
    {"sub_58A3E8", 0x58A3E8, &recomp_gen::fn_sub_58A3E8_0058a3e8, &recomp_gen::fn_sub_58A3E8_0058a3e8__recomp},
    {"sub_58A488", 0x58A488, &recomp_gen::fn_sub_58A488_0058a488, &recomp_gen::fn_sub_58A488_0058a488__recomp},
    {"sub_58A538", 0x58A538, &recomp_gen::fn_sub_58A538_0058a538, &recomp_gen::fn_sub_58A538_0058a538__recomp},
    {"sub_58A598", 0x58A598, &recomp_gen::fn_sub_58A598_0058a598, &recomp_gen::fn_sub_58A598_0058a598__recomp},
    {"sub_58A5A0", 0x58A5A0, &recomp_gen::fn_sub_58A5A0_0058a5a0, &recomp_gen::fn_sub_58A5A0_0058a5a0__recomp},
    {"sub_58A658", 0x58A658, &recomp_gen::fn_sub_58A658_0058a658, &recomp_gen::fn_sub_58A658_0058a658__recomp},
    {"sub_58A740", 0x58A740, &recomp_gen::fn_sub_58A740_0058a740, &recomp_gen::fn_sub_58A740_0058a740__recomp},
    {"sub_58A7D8", 0x58A7D8, &recomp_gen::fn_sub_58A7D8_0058a7d8, &recomp_gen::fn_sub_58A7D8_0058a7d8__recomp},
    {"sub_58A8C8", 0x58A8C8, &recomp_gen::fn_sub_58A8C8_0058a8c8, &recomp_gen::fn_sub_58A8C8_0058a8c8__recomp},
    {"sub_58A918", 0x58A918, &recomp_gen::fn_sub_58A918_0058a918, &recomp_gen::fn_sub_58A918_0058a918__recomp},
    {"sub_58AA88", 0x58AA88, &recomp_gen::fn_sub_58AA88_0058aa88, &recomp_gen::fn_sub_58AA88_0058aa88__recomp},
    {"sub_58B4A8", 0x58B4A8, &recomp_gen::fn_sub_58B4A8_0058b4a8, &recomp_gen::fn_sub_58B4A8_0058b4a8__recomp},
    {"sub_58BD68", 0x58BD68, &recomp_gen::fn_sub_58BD68_0058bd68, &recomp_gen::fn_sub_58BD68_0058bd68__recomp},
    {"cosl_12", 0x58C0A0, &recomp_gen::fn_cosl_12_0058c0a0, &recomp_gen::fn_cosl_12_0058c0a0__recomp},
    {"sub_58C0D8", 0x58C0D8, &recomp_gen::fn_sub_58C0D8_0058c0d8, &recomp_gen::fn_sub_58C0D8_0058c0d8__recomp},
    {"__env_unlock_11", 0x58C0F8, &recomp_gen::fn___env_unlock_11_0058c0f8, &recomp_gen::fn___env_unlock_11_0058c0f8__recomp},
    {"sub_58C198", 0x58C198, &recomp_gen::fn_sub_58C198_0058c198, &recomp_gen::fn_sub_58C198_0058c198__recomp},
    {"sub_58C1B8", 0x58C1B8, &recomp_gen::fn_sub_58C1B8_0058c1b8, &recomp_gen::fn_sub_58C1B8_0058c1b8__recomp},
    {"sub_58C1E0", 0x58C1E0, &recomp_gen::fn_sub_58C1E0_0058c1e0, &recomp_gen::fn_sub_58C1E0_0058c1e0__recomp},
    {"sub_58C200", 0x58C200, &recomp_gen::fn_sub_58C200_0058c200, &recomp_gen::fn_sub_58C200_0058c200__recomp},
    {"sub_58C220", 0x58C220, &recomp_gen::fn_sub_58C220_0058c220, &recomp_gen::fn_sub_58C220_0058c220__recomp},
    {"r_lock_def_free_6", 0x58C380, &recomp_gen::fn_r_lock_def_free_6_0058c380, &recomp_gen::fn_r_lock_def_free_6_0058c380__recomp},
    {"sub_58DF90", 0x58DF90, &recomp_gen::fn_sub_58DF90_0058df90, &recomp_gen::fn_sub_58DF90_0058df90__recomp},
    {"sub_58E010", 0x58E010, &recomp_gen::fn_sub_58E010_0058e010, &recomp_gen::fn_sub_58E010_0058e010__recomp},
    {"sub_58E018", 0x58E018, &recomp_gen::fn_sub_58E018_0058e018, &recomp_gen::fn_sub_58E018_0058e018__recomp},
    {"sub_58E020", 0x58E020, &recomp_gen::fn_sub_58E020_0058e020, &recomp_gen::fn_sub_58E020_0058e020__recomp},
    {"sub_58E028", 0x58E028, &recomp_gen::fn_sub_58E028_0058e028, &recomp_gen::fn_sub_58E028_0058e028__recomp},
    {"sub_58E030", 0x58E030, &recomp_gen::fn_sub_58E030_0058e030, &recomp_gen::fn_sub_58E030_0058e030__recomp},
    {"sub_58E050", 0x58E050, &recomp_gen::fn_sub_58E050_0058e050, &recomp_gen::fn_sub_58E050_0058e050__recomp},
    {"sub_58E070", 0x58E070, &recomp_gen::fn_sub_58E070_0058e070, &recomp_gen::fn_sub_58E070_0058e070__recomp},
    {"sub_58E090", 0x58E090, &recomp_gen::fn_sub_58E090_0058e090, &recomp_gen::fn_sub_58E090_0058e090__recomp},
    {"sub_58E0B0", 0x58E0B0, &recomp_gen::fn_sub_58E0B0_0058e0b0, &recomp_gen::fn_sub_58E0B0_0058e0b0__recomp},
    {"sub_58E160", 0x58E160, &recomp_gen::fn_sub_58E160_0058e160, &recomp_gen::fn_sub_58E160_0058e160__recomp},
    {"sub_58E4A0", 0x58E4A0, &recomp_gen::fn_sub_58E4A0_0058e4a0, &recomp_gen::fn_sub_58E4A0_0058e4a0__recomp},
    {"sub_58E6E8", 0x58E6E8, &recomp_gen::fn_sub_58E6E8_0058e6e8, &recomp_gen::fn_sub_58E6E8_0058e6e8__recomp},
    {"sub_58FC30", 0x58FC30, &recomp_gen::fn_sub_58FC30_0058fc30, &recomp_gen::fn_sub_58FC30_0058fc30__recomp},
    {"sub_58FD00", 0x58FD00, &recomp_gen::fn_sub_58FD00_0058fd00, &recomp_gen::fn_sub_58FD00_0058fd00__recomp},
    {"sub_58FD60", 0x58FD60, &recomp_gen::fn_sub_58FD60_0058fd60, &recomp_gen::fn_sub_58FD60_0058fd60__recomp},
    {"sub_590430", 0x590430, &recomp_gen::fn_sub_590430_00590430, &recomp_gen::fn_sub_590430_00590430__recomp},
    {"sub_5905B0", 0x5905B0, &recomp_gen::fn_sub_5905B0_005905b0, &recomp_gen::fn_sub_5905B0_005905b0__recomp},
    {"sub_590878", 0x590878, &recomp_gen::fn_sub_590878_00590878, &recomp_gen::fn_sub_590878_00590878__recomp},
    {"sub_590A28", 0x590A28, &recomp_gen::fn_sub_590A28_00590a28, &recomp_gen::fn_sub_590A28_00590a28__recomp},
    {"sub_591700", 0x591700, &recomp_gen::fn_sub_591700_00591700, &recomp_gen::fn_sub_591700_00591700__recomp},
    {"sub_591808", 0x591808, &recomp_gen::fn_sub_591808_00591808, &recomp_gen::fn_sub_591808_00591808__recomp},
    {"sub_5918A8", 0x5918A8, &recomp_gen::fn_sub_5918A8_005918a8, &recomp_gen::fn_sub_5918A8_005918a8__recomp},
    {"sub_591988", 0x591988, &recomp_gen::fn_sub_591988_00591988, &recomp_gen::fn_sub_591988_00591988__recomp},
    {"sub_591B00", 0x591B00, &recomp_gen::fn_sub_591B00_00591b00, &recomp_gen::fn_sub_591B00_00591b00__recomp},
    {"sub_591C08", 0x591C08, &recomp_gen::fn_sub_591C08_00591c08, &recomp_gen::fn_sub_591C08_00591c08__recomp},
    {"sub_5927D8", 0x5927D8, &recomp_gen::fn_sub_5927D8_005927d8, &recomp_gen::fn_sub_5927D8_005927d8__recomp},
    {"sub_592938", 0x592938, &recomp_gen::fn_sub_592938_00592938, &recomp_gen::fn_sub_592938_00592938__recomp},
    {"sub_592EF8", 0x592EF8, &recomp_gen::fn_sub_592EF8_00592ef8, &recomp_gen::fn_sub_592EF8_00592ef8__recomp},
    {"sub_593608", 0x593608, &recomp_gen::fn_sub_593608_00593608, &recomp_gen::fn_sub_593608_00593608__recomp},
    {"sub_5938C0", 0x5938C0, &recomp_gen::fn_sub_5938C0_005938c0, &recomp_gen::fn_sub_5938C0_005938c0__recomp},
    {"sub_593948", 0x593948, &recomp_gen::fn_sub_593948_00593948, &recomp_gen::fn_sub_593948_00593948__recomp},
    {"sub_593AA0", 0x593AA0, &recomp_gen::fn_sub_593AA0_00593aa0, &recomp_gen::fn_sub_593AA0_00593aa0__recomp},
    {"sub_593AC8", 0x593AC8, &recomp_gen::fn_sub_593AC8_00593ac8, &recomp_gen::fn_sub_593AC8_00593ac8__recomp},
    {"sub_593B10", 0x593B10, &recomp_gen::fn_sub_593B10_00593b10, &recomp_gen::fn_sub_593B10_00593b10__recomp},
    {"sub_593BF8", 0x593BF8, &recomp_gen::fn_sub_593BF8_00593bf8, &recomp_gen::fn_sub_593BF8_00593bf8__recomp},
    {"sub_593C58", 0x593C58, &recomp_gen::fn_sub_593C58_00593c58, &recomp_gen::fn_sub_593C58_00593c58__recomp},
    {"sub_593CE8", 0x593CE8, &recomp_gen::fn_sub_593CE8_00593ce8, &recomp_gen::fn_sub_593CE8_00593ce8__recomp},
    {"sub_593FD0", 0x593FD0, &recomp_gen::fn_sub_593FD0_00593fd0, &recomp_gen::fn_sub_593FD0_00593fd0__recomp},
    {"sub_594B18", 0x594B18, &recomp_gen::fn_sub_594B18_00594b18, &recomp_gen::fn_sub_594B18_00594b18__recomp},
    {"sub_594E50", 0x594E50, &recomp_gen::fn_sub_594E50_00594e50, &recomp_gen::fn_sub_594E50_00594e50__recomp},
    {"sub_594E60", 0x594E60, &recomp_gen::fn_sub_594E60_00594e60, &recomp_gen::fn_sub_594E60_00594e60__recomp},
    {"sub_594F68", 0x594F68, &recomp_gen::fn_sub_594F68_00594f68, &recomp_gen::fn_sub_594F68_00594f68__recomp},
    {"sub_595788", 0x595788, &recomp_gen::fn_sub_595788_00595788, &recomp_gen::fn_sub_595788_00595788__recomp},
    {"sub_5958F8", 0x5958F8, &recomp_gen::fn_sub_5958F8_005958f8, &recomp_gen::fn_sub_5958F8_005958f8__recomp},
    {"sub_595A50", 0x595A50, &recomp_gen::fn_sub_595A50_00595a50, &recomp_gen::fn_sub_595A50_00595a50__recomp},
    {"sub_595AC0", 0x595AC0, &recomp_gen::fn_sub_595AC0_00595ac0, &recomp_gen::fn_sub_595AC0_00595ac0__recomp},
    {"sub_596340", 0x596340, &recomp_gen::fn_sub_596340_00596340, &recomp_gen::fn_sub_596340_00596340__recomp},
    {"sub_5965E0", 0x5965E0, &recomp_gen::fn_sub_5965E0_005965e0, &recomp_gen::fn_sub_5965E0_005965e0__recomp},
    {"sub_596818", 0x596818, &recomp_gen::fn_sub_596818_00596818, &recomp_gen::fn_sub_596818_00596818__recomp},
    {"sub_596B28", 0x596B28, &recomp_gen::fn_sub_596B28_00596b28, &recomp_gen::fn_sub_596B28_00596b28__recomp},
    {"sub_597168", 0x597168, &recomp_gen::fn_sub_597168_00597168, &recomp_gen::fn_sub_597168_00597168__recomp},
    {"thread_leave_1", 0x597AA0, &recomp_gen::fn_thread_leave_1_00597aa0, &recomp_gen::fn_thread_leave_1_00597aa0__recomp},
    {"sub_597B88", 0x597B88, &recomp_gen::fn_sub_597B88_00597b88, &recomp_gen::fn_sub_597B88_00597b88__recomp},
    {"sub_597E98", 0x597E98, &recomp_gen::fn_sub_597E98_00597e98, &recomp_gen::fn_sub_597E98_00597e98__recomp},
    {"sub_597F20", 0x597F20, &recomp_gen::fn_sub_597F20_00597f20, &recomp_gen::fn_sub_597F20_00597f20__recomp},
    {"sub_598030", 0x598030, &recomp_gen::fn_sub_598030_00598030, &recomp_gen::fn_sub_598030_00598030__recomp},
    {"sub_598140", 0x598140, &recomp_gen::fn_sub_598140_00598140, &recomp_gen::fn_sub_598140_00598140__recomp},
    {"sub_5981D8", 0x5981D8, &recomp_gen::fn_sub_5981D8_005981d8, &recomp_gen::fn_sub_5981D8_005981d8__recomp},
    {"sub_598348", 0x598348, &recomp_gen::fn_sub_598348_00598348, &recomp_gen::fn_sub_598348_00598348__recomp},
    {"sub_5983B8", 0x5983B8, &recomp_gen::fn_sub_5983B8_005983b8, &recomp_gen::fn_sub_5983B8_005983b8__recomp},
    {"sub_598470", 0x598470, &recomp_gen::fn_sub_598470_00598470, &recomp_gen::fn_sub_598470_00598470__recomp},
    {"sub_598688", 0x598688, &recomp_gen::fn_sub_598688_00598688, &recomp_gen::fn_sub_598688_00598688__recomp},
    {"sub_5987F0", 0x5987F0, &recomp_gen::fn_sub_5987F0_005987f0, &recomp_gen::fn_sub_5987F0_005987f0__recomp},
    {"sub_598870", 0x598870, &recomp_gen::fn_sub_598870_00598870, &recomp_gen::fn_sub_598870_00598870__recomp},
    {"sub_5988F0", 0x5988F0, &recomp_gen::fn_sub_5988F0_005988f0, &recomp_gen::fn_sub_5988F0_005988f0__recomp},
    {"sub_598A90", 0x598A90, &recomp_gen::fn_sub_598A90_00598a90, &recomp_gen::fn_sub_598A90_00598a90__recomp},
    {"sub_598B90", 0x598B90, &recomp_gen::fn_sub_598B90_00598b90, &recomp_gen::fn_sub_598B90_00598b90__recomp},
    {"sub_598D20", 0x598D20, &recomp_gen::fn_sub_598D20_00598d20, &recomp_gen::fn_sub_598D20_00598d20__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena (TODO: the function's real structures).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(libs16): every body equals its recompiled body on random worlds") {
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

namespace L = p3fes::game::libs13;

// An SFD handle world (libs13.h's records): the handle at kHandle, its video-decoder work at handle + sfd::kVdecArea,
// 16 frame records with real states / times / shown marks, the header object, the timing record (+14000) and the
// video-input ring; every other word is one of the values the bodies compare against (statuses, API modes, picture
// types, param values, -1 / -2 / -3, the CRI audio vtable word 0x7C9D78, 44100, 1000) or a pointer into the world.
constexpr u32 kHandle = 0x01820000u;
constexpr u32 kHandleSpan = 0x10000u;
constexpr u32 kWork = kHandle + L::sfd::kVdecArea;
constexpr u32 kHdr = kHandle + 0xE000u;    // the header object
constexpr u32 kTiming = kHandle + 0xC000u;  // a timing record (sub_598348's 3544 bytes)

u32 enum_word(std::mt19937& rng) {
    static const u32 kValues[] = {0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 15u, 16u, 0xFFFFFFFFu, 0xFFFFFFFEu, 0xFFFFFFFDu,
                                  0xFFFFFFFCu, 0x7C9D78u, 44100u, 1000u, 108u, 2048u, 29970u, 0x7FFFFFFFu, 0x10000u};
    const u32 k = rng() % 8;
    if (k < 5) return kValues[rng() % (sizeof kValues / sizeof kValues[0])];
    if (k < 7) return kHandle + ((rng() % kHandleSpan) & ~3u);
    return rng() % 0x10000u;
}

void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
u32 r32(Machine& m, u32 va) {
    u32 v = 0;
    std::memcpy(&v, m.at(va), 4);
    return v;
}

void sfd_world(Machine& m, std::mt19937& rng) {
    for (u32 i = 0; i + 4 <= kHandleSpan; i += 4) w32(m, kHandle + i, enum_word(rng));
    w32(m, kHandle + L::sfd::kStat, rng() % 7);
    w32(m, kHandle + L::sfd::kReq, rng() % 7);
    w32(m, kHandle + L::sfd::kApiMode, rng() % 3);
    w32(m, kHandle + L::sfd::kVdecWork, kWork);
    w32(m, kHandle + L::sfd::kHdrObj, rng() % 3 == 0 ? 0u : (rng() % 2 ? kHdr : kTiming));
    w32(m, kWork + L::vdec::kFrameCount, rng() % 17);
    for (u32 i = 0; i < 16; ++i) {
        const u32 f = kWork + L::vdec::kFrames + L::frm::kSize * i;
        w32(m, f + L::frm::kState, rng() % 5);
        w32(m, f + L::frm::kTime, rng() % 8);
        w32(m, f + L::frm::kShown, rng() % 2 ? 0xFFFFFFFFu : rng() % 4);
    }
    w32(m, kWork + L::vdec::kIpu, rng() % 2);
}

// Recorders for callees this build does not emit and the bodies meet first, all already stood in by main's tests and
// claimed by no current packet: the SFD lock / unlock, the kernel semaphores, the video-input ring's DMA flush, the SJ
// chunk read / release and the two CRI copy / fill helpers. Each logs the call and returns $v0; both bodies of a pair
// get a fresh set and the two call logs must be equal. Every other callee runs (replaced) or stops both runs alike.
struct Rec {
    u32 va;
    const char* name;
    u64 v0;
};
const Rec kRecorders[] = {
    {0x58C100u, "sub_58C100 (lock)", 0},          {0x58C118u, "sub_58C118 (unlock)", 0},
    {0x503180u, "_sceSignalSema", 0},             {0x5031A0u, "_sceWaitSema", 0},
    {0x5944A8u, "sub_5944A8 (ring DMA)", 0},      {0x589018u, "sub_589018 (chunk read)", 0},
    {0x5890F0u, "sub_5890F0 (chunk release)", 0}, {0x575410u, "sub_575410 (copy)", 0},
    {0x575880u, "sub_575880 (fill)", 0},
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
hgp::Run spair(Machine& m, Fn hand, Fn recomp, const Args& args, u32 seed, const char* what) {
    auto wh = std::make_unique<StandInWorld>();
    auto wr = std::make_unique<StandInWorld>();
    for (StandInWorld* w : {wh.get(), wr.get()}) {
        w->si.clobber_scratch = true;
        for (const Rec& r : kRecorders) w->si.install_recorder(r.va, r.name, r.v0, 3);
    }
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, what);
    expect_same_log(wh->si, wr->si, what);
    return r;
}

u64 sfd_arg(std::mt19937& rng) {
    const u32 k = rng() % 8;
    if (k < 4) return sx(kHandle);
    if (k < 5) return sx(kWork + L::vdec::kFrames + L::frm::kSize * (rng() % 16));
    if (k < 6) return sx(kHandle + ((rng() % kHandleSpan) & ~15u));
    return sx(enum_word(rng));
}

void run_sfd_worlds(Machine& m, u32 seeds, const char* label) {
    const char* only = std::getenv("P3FES_HG_ONLY");
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            std::mt19937 rng{seed * 104729u + c.addr};
            sfd_world(m, rng);
            const Args args{sfd_arg(rng), sfd_arg(rng), sfd_arg(rng), sfd_arg(rng)};
            stops += spair(m, c.hand, c.recomp, args, seed, c.name).stopped ? 1 : 0;
        }
        const std::string summary = std::string(label) + " " + c.name + ": " + std::to_string(seeds) + " pairs, " + std::to_string(stops) + " stopped early";
        MESSAGE(summary);
    }
}

const Case& find(const char* name) {
    for (const Case& c : kCases)
        if (std::string(c.name) == name) return c;
    FAIL("no case " << name);
    return kCases[0];
}

}  // namespace

TEST_CASE("game(libs16): every body equals its recompiled body on SFD handle worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");
    run_sfd_worlds(*m, env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : 32u, "sfd world");
}

// The same worlds over the RAM of the replay snapshots (real globals: the handle table 0x7B4774, the hook 0x7B47BC,
// the probe info 0x9A76F8.., the clock words); and, where a snapshot holds an open SFD handle, every body on it.
TEST_CASE("game(libs16): every body equals its recompiled body on the replay snapshots") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* kSnaps[] = {"dorm_replay_4900", "b_5800", "climb_ref_17000", "fusion_ref_6300", "shop_ref_4100"};
    for (const char* dir : kSnaps) {
        const std::vector<u8> snap = read_snapshot(dir);
        if (snap.size() != EEMemory::kMainRamSize) {
            MESSAGE("SKIP: snapshot " << dir << " not found");
            continue;
        }
        std::memcpy(m->mem.main_ram(), snap.data(), snap.size());
        run_sfd_worlds(*m, 4u, dir);
        std::vector<u32> handles;  // the open-handle table 0x7B4774[8] and the last checked handle 0x7B4568
        for (u32 i = 0; i <= 8; ++i) {
            u32 h = 0;
            std::memcpy(&h, snap.data() + (i < 8 ? 0x7B4774u + 4 * i : 0x7B4568u), 4);
            if (h != 0 && h < 0x01FF0000u && std::find(handles.begin(), handles.end(), h) == handles.end()) handles.push_back(h);
        }
        for (const u32 h : handles) {
            for (const Case& c : kCases) {
                std::memcpy(m->mem.main_ram(), snap.data(), snap.size());  // the live handle as the snapshot holds it
                for (u32 seed = 1; seed <= 4; ++seed) {
                    std::mt19937 rng{seed + c.addr};
                    const Args args{sx(h), rng() % 8, rng() % 8, rng() % 8};
                    spair(*m, c.hand, c.recomp, args, seed, c.name);
                }
            }
            const std::string note = std::string(dir) + ": open SFD handle " + hex64(h) + ", " + std::to_string((sizeof kCases / sizeof kCases[0]) * 4) + " pairs";
            MESSAGE(note);
        }
    }
}

// Documented rules on the host, from the instructions (both bodies run, compared, then the result checked).
TEST_CASE("game(libs16): field time, frame-state step, counter, entry ring and plane layout rules") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const u32 base = kHandle;
    // sub_5905B0: 90,000,000 x n / rate (64-bit product, __divdi3).
    {
        const Case& c = find("sub_5905B0");
        CHECK(hgp::pair(*m, c.hand, c.recomp, Args{3, 29970, 0, 0}, 1, c.name).end.gpr[2].u64[0] == 9009u);
        CHECK(hgp::pair(*m, c.hand, c.recomp, Args{100, 60000, 0, 0}, 2, c.name).end.gpr[2].u64[0] == 150000u);
    }
    // sub_593B10: 4 -> 2 (returns 2); anything else -> 0 (returns 4); a null pointer returns 4.
    {
        const Case& c = find("sub_593B10");
        const u32 p = base + 0x100;
        w32(*m, p, 4);
        CHECK(hgp::pair(*m, c.hand, c.recomp, Args{sx(p), 0, 0, 0}, 1, c.name).end.gpr[2].u64[0] == 2u);
        CHECK(r32(*m, p) == 2u);
        CHECK(hgp::pair(*m, c.hand, c.recomp, Args{sx(p), 0, 0, 0}, 2, c.name).end.gpr[2].u64[0] == 4u);
        CHECK(r32(*m, p) == 0u);
        CHECK(hgp::pair(*m, c.hand, c.recomp, Args{0, 0, 0, 0}, 3, c.name).end.gpr[2].u64[0] == 4u);
    }
    // sub_593FD0: returns the counter +92 and increments it.
    {
        const Case& c = find("sub_593FD0");
        const u32 r = base + 0x200;
        w32(*m, r + 92, 5);
        CHECK(hgp::pair(*m, c.hand, c.recomp, Args{sx(r), 0, 0, 0}, 1, c.name).end.gpr[2].u64[0] == 5u);
        CHECK(r32(*m, r + 92) == 6u);
    }
    // sub_597F20 / sub_598030: a ring over (buf + 3, 67 bytes) starts at the 8-aligned buffer with (67 - 5) / 16 = 3
    // entries; a push stores 16 bytes at the write index and counts it; the third push reports full and wraps the
    // write index, the fourth fails with -1.
    {
        const Case& init = find("sub_597F20");
        const Case& push = find("sub_598030");
        const u32 ring = base + 0x300, buf = base + 0x400, entry = base + 0x500, full = base + 0x510;
        hgp::pair(*m, init.hand, init.recomp, Args{sx(ring), sx(buf + 3), 67, 0}, 1, init.name);
        CHECK(r32(*m, ring + 0) == buf + 8);
        CHECK(r32(*m, ring + 4) == 3u);  // (67 - 5) / 16
        CHECK(r32(*m, ring + 8) == 0u);
        for (u32 i = 0; i < 4; ++i) w32(*m, entry + 4 * i, 0x11111111u * (i + 1));
        CHECK(hgp::pair(*m, push.hand, push.recomp, Args{sx(ring), sx(entry), sx(full), 0}, 1, push.name).end.gpr[2].u64[0] == 0u);
        CHECK(r32(*m, ring + 8) == 1u);
        CHECK(r32(*m, ring + 12) == 1u);
        CHECK(r32(*m, buf + 8 + 4) == 0x22222222u);
        CHECK(r32(*m, full) == 0u);
        hgp::pair(*m, push.hand, push.recomp, Args{sx(ring), sx(entry), sx(full), 0}, 2, push.name);
        hgp::pair(*m, push.hand, push.recomp, Args{sx(ring), sx(entry), sx(full), 0}, 3, push.name);
        CHECK(r32(*m, full) == 1u);
        CHECK(r32(*m, ring + 12) == 0u);  // the write index wrapped
        CHECK(hgp::pair(*m, push.hand, push.recomp, Args{sx(ring), sx(entry), sx(full), 0}, 4, push.name).end.gpr[2].u64[0] == ~u64{0});
    }
    // sub_58E4A0: a 320 x 240 picture: +8 = the base, +14 = the width in 64-pixel blocks x 64 (320), +0 = the base +
    // 1024 x (5 blocks x 15 macroblock rows).
    {
        const Case& c = find("sub_58E4A0");
        const u32 rec = base + 0x600, pic = 0x01000000u;
        hgp::pair(*m, c.hand, c.recomp, Args{sx(pic), 320, 240, sx(rec)}, 1, c.name);
        CHECK(r32(*m, rec + 8) == pic);
        u16 w = 0;
        std::memcpy(&w, m->at(rec + 14), 2);
        CHECK(w == 320u);
        CHECK(r32(*m, rec + 0) == pic + 75u * 1024u);
    }
}

#else

TEST_CASE("game(libs16): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
