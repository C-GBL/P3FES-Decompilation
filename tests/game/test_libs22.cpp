// Pair tests for slice libs22 (game/src/cri/libs22.cpp). Every body against its recompiled body, compared by
// tests/game/handgen_pairs.h: the whole register file and cycle count at every check point and at the return / stop,
// all 32 MiB of RAM, the scratchpad, the BIOS window and the bus log. Worlds: random words; MWSFD player / SFD lane
// worlds (a player with its SFX handle, play list, SFD handle and slave record, an SFD handle whose lanes are PCM
// rings) with stand-ins for the not-emitted callees; the same over the replay snapshots plus every live player of the
// table 0x7B2FBC; and host rules (the slave interface, the player's slave words, the lane setup, the PCM ring's write /
// read areas, commits and their 0xFF000406 / 0xFF000407 / 0xFF000401 errors, the MPEG audio bit rate and frame size).
// Callees claimed by the libs14 / libs17 packets are not stood in: those pairs stop there for now, identically.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/libs22.h"

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
void fn_sub_5838C0_005838c0(EEContext&);  // generated body
void fn_sub_5838C0_005838c0__recomp(EEContext&);  // recompiled
void fn_sub_5838D8_005838d8(EEContext&);  // generated body
void fn_sub_5838D8_005838d8__recomp(EEContext&);  // recompiled
void fn_sub_5838F0_005838f0(EEContext&);  // generated body
void fn_sub_5838F0_005838f0__recomp(EEContext&);  // recompiled
void fn_sub_583940_00583940(EEContext&);  // generated body
void fn_sub_583940_00583940__recomp(EEContext&);  // recompiled
void fn_sub_5839B8_005839b8(EEContext&);  // generated body
void fn_sub_5839B8_005839b8__recomp(EEContext&);  // recompiled
void fn_sub_583A08_00583a08(EEContext&);  // generated body
void fn_sub_583A08_00583a08__recomp(EEContext&);  // recompiled
void fn_sub_583A78_00583a78(EEContext&);  // generated body
void fn_sub_583A78_00583a78__recomp(EEContext&);  // recompiled
void fn_sub_583AC8_00583ac8(EEContext&);  // generated body
void fn_sub_583AC8_00583ac8__recomp(EEContext&);  // recompiled
void fn_sub_583B18_00583b18(EEContext&);  // generated body
void fn_sub_583B18_00583b18__recomp(EEContext&);  // recompiled
void fn_sub_583BB8_00583bb8(EEContext&);  // generated body
void fn_sub_583BB8_00583bb8__recomp(EEContext&);  // recompiled
void fn_sub_583C58_00583c58(EEContext&);  // generated body
void fn_sub_583C58_00583c58__recomp(EEContext&);  // recompiled
void fn_sub_583C70_00583c70(EEContext&);  // generated body
void fn_sub_583C70_00583c70__recomp(EEContext&);  // recompiled
void fn_sub_583C88_00583c88(EEContext&);  // generated body
void fn_sub_583C88_00583c88__recomp(EEContext&);  // recompiled
void fn_sub_583CA0_00583ca0(EEContext&);  // generated body
void fn_sub_583CA0_00583ca0__recomp(EEContext&);  // recompiled
void fn_sub_583CB8_00583cb8(EEContext&);  // generated body
void fn_sub_583CB8_00583cb8__recomp(EEContext&);  // recompiled
void fn_sub_583CD0_00583cd0(EEContext&);  // generated body
void fn_sub_583CD0_00583cd0__recomp(EEContext&);  // recompiled
void fn_sub_583CE8_00583ce8(EEContext&);  // generated body
void fn_sub_583CE8_00583ce8__recomp(EEContext&);  // recompiled
void fn_sub_583D58_00583d58(EEContext&);  // generated body
void fn_sub_583D58_00583d58__recomp(EEContext&);  // recompiled
void fn_sub_583DB8_00583db8(EEContext&);  // generated body
void fn_sub_583DB8_00583db8__recomp(EEContext&);  // recompiled
void fn_sub_583DE8_00583de8(EEContext&);  // generated body
void fn_sub_583DE8_00583de8__recomp(EEContext&);  // recompiled
void fn_sub_583E58_00583e58(EEContext&);  // generated body
void fn_sub_583E58_00583e58__recomp(EEContext&);  // recompiled
void fn_sub_583EB8_00583eb8(EEContext&);  // generated body
void fn_sub_583EB8_00583eb8__recomp(EEContext&);  // recompiled
void fn_sub_583ED0_00583ed0(EEContext&);  // generated body
void fn_sub_583ED0_00583ed0__recomp(EEContext&);  // recompiled
void fn_sub_583FB8_00583fb8(EEContext&);  // generated body
void fn_sub_583FB8_00583fb8__recomp(EEContext&);  // recompiled
void fn_sub_583FD0_00583fd0(EEContext&);  // generated body
void fn_sub_583FD0_00583fd0__recomp(EEContext&);  // recompiled
void fn_sub_583FE8_00583fe8(EEContext&);  // generated body
void fn_sub_583FE8_00583fe8__recomp(EEContext&);  // recompiled
void fn_sub_584000_00584000(EEContext&);  // generated body
void fn_sub_584000_00584000__recomp(EEContext&);  // recompiled
void fn_sub_584018_00584018(EEContext&);  // generated body
void fn_sub_584018_00584018__recomp(EEContext&);  // recompiled
void fn_sub_584030_00584030(EEContext&);  // generated body
void fn_sub_584030_00584030__recomp(EEContext&);  // recompiled
void fn_sub_584070_00584070(EEContext&);  // generated body
void fn_sub_584070_00584070__recomp(EEContext&);  // recompiled
void fn_sub_5844C8_005844c8(EEContext&);  // generated body
void fn_sub_5844C8_005844c8__recomp(EEContext&);  // recompiled
void fn_sub_5845E0_005845e0(EEContext&);  // generated body
void fn_sub_5845E0_005845e0__recomp(EEContext&);  // recompiled
void fn_sub_584680_00584680(EEContext&);  // generated body
void fn_sub_584680_00584680__recomp(EEContext&);  // recompiled
void fn_sub_584730_00584730(EEContext&);  // generated body
void fn_sub_584730_00584730__recomp(EEContext&);  // recompiled
void fn_sub_584778_00584778(EEContext&);  // generated body
void fn_sub_584778_00584778__recomp(EEContext&);  // recompiled
void fn_sub_584790_00584790(EEContext&);  // generated body
void fn_sub_584790_00584790__recomp(EEContext&);  // recompiled
void fn_sub_584800_00584800(EEContext&);  // generated body
void fn_sub_584800_00584800__recomp(EEContext&);  // recompiled
void fn_sub_5848D8_005848d8(EEContext&);  // generated body
void fn_sub_5848D8_005848d8__recomp(EEContext&);  // recompiled
void fn_sub_584928_00584928(EEContext&);  // generated body
void fn_sub_584928_00584928__recomp(EEContext&);  // recompiled
void fn_sub_584950_00584950(EEContext&);  // generated body
void fn_sub_584950_00584950__recomp(EEContext&);  // recompiled
void fn_sub_584978_00584978(EEContext&);  // generated body
void fn_sub_584978_00584978__recomp(EEContext&);  // recompiled
void fn_sub_584A08_00584a08(EEContext&);  // generated body
void fn_sub_584A08_00584a08__recomp(EEContext&);  // recompiled
void fn_sub_584AA0_00584aa0(EEContext&);  // generated body
void fn_sub_584AA0_00584aa0__recomp(EEContext&);  // recompiled
void fn_sub_584AA8_00584aa8(EEContext&);  // generated body
void fn_sub_584AA8_00584aa8__recomp(EEContext&);  // recompiled
void fn_sub_584D98_00584d98(EEContext&);  // generated body
void fn_sub_584D98_00584d98__recomp(EEContext&);  // recompiled
void fn_sub_584F30_00584f30(EEContext&);  // generated body
void fn_sub_584F30_00584f30__recomp(EEContext&);  // recompiled
void fn_WTLS_set_table_1_005851c0(EEContext&);  // generated body
void fn_WTLS_set_table_1_005851c0__recomp(EEContext&);  // recompiled
void fn_sub_585268_00585268(EEContext&);  // generated body
void fn_sub_585268_00585268__recomp(EEContext&);  // recompiled
void fn_sub_5852A0_005852a0(EEContext&);  // generated body
void fn_sub_5852A0_005852a0__recomp(EEContext&);  // recompiled
void fn_sub_5852C0_005852c0(EEContext&);  // generated body
void fn_sub_5852C0_005852c0__recomp(EEContext&);  // recompiled
void fn_coshl_11_00585498(EEContext&);  // generated body
void fn_coshl_11_00585498__recomp(EEContext&);  // recompiled
void fn_sub_5854B8_005854b8(EEContext&);  // generated body
void fn_sub_5854B8_005854b8__recomp(EEContext&);  // recompiled
void fn_sub_5854D0_005854d0(EEContext&);  // generated body
void fn_sub_5854D0_005854d0__recomp(EEContext&);  // recompiled
void fn_sub_5854F0_005854f0(EEContext&);  // generated body
void fn_sub_5854F0_005854f0__recomp(EEContext&);  // recompiled
void fn_hypotl_11_00585508(EEContext&);  // generated body
void fn_hypotl_11_00585508__recomp(EEContext&);  // recompiled
void fn_sub_585528_00585528(EEContext&);  // generated body
void fn_sub_585528_00585528__recomp(EEContext&);  // recompiled
void fn_sub_585540_00585540(EEContext&);  // generated body
void fn_sub_585540_00585540__recomp(EEContext&);  // recompiled
void fn_sub_585560_00585560(EEContext&);  // generated body
void fn_sub_585560_00585560__recomp(EEContext&);  // recompiled
void fn_powl_11_00585640(EEContext&);  // generated body
void fn_powl_11_00585640__recomp(EEContext&);  // recompiled
void fn_sinhl_11_00585670(EEContext&);  // generated body
void fn_sinhl_11_00585670__recomp(EEContext&);  // recompiled
void fn_sub_585D38_00585d38(EEContext&);  // generated body
void fn_sub_585D38_00585d38__recomp(EEContext&);  // recompiled
void fn_sub_585D50_00585d50(EEContext&);  // generated body
void fn_sub_585D50_00585d50__recomp(EEContext&);  // recompiled
void fn_sub_585E08_00585e08(EEContext&);  // generated body
void fn_sub_585E08_00585e08__recomp(EEContext&);  // recompiled
void fn_sub_5860B0_005860b0(EEContext&);  // generated body
void fn_sub_5860B0_005860b0__recomp(EEContext&);  // recompiled
void fn_sub_5860D0_005860d0(EEContext&);  // generated body
void fn_sub_5860D0_005860d0__recomp(EEContext&);  // recompiled
void fn_sub_586148_00586148(EEContext&);  // generated body
void fn_sub_586148_00586148__recomp(EEContext&);  // recompiled
void fn_sub_586150_00586150(EEContext&);  // generated body
void fn_sub_586150_00586150__recomp(EEContext&);  // recompiled
void fn_rdbuf__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_0_005861f8(EEContext&);  // generated body
void fn_rdbuf__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_0_005861f8__recomp(EEContext&);  // recompiled
void fn_sub_586220_00586220(EEContext&);  // generated body
void fn_sub_586220_00586220__recomp(EEContext&);  // recompiled
void fn_ctime_00586298(EEContext&);  // generated body
void fn_ctime_00586298__recomp(EEContext&);  // recompiled
void fn_sub_5862B8_005862b8(EEContext&);  // generated body
void fn_sub_5862B8_005862b8__recomp(EEContext&);  // recompiled
void fn_sub_5862E8_005862e8(EEContext&);  // generated body
void fn_sub_5862E8_005862e8__recomp(EEContext&);  // recompiled
void fn_sub_5862F8_005862f8(EEContext&);  // generated body
void fn_sub_5862F8_005862f8__recomp(EEContext&);  // recompiled
void fn_sub_586338_00586338(EEContext&);  // generated body
void fn_sub_586338_00586338__recomp(EEContext&);  // recompiled
void fn_r_lock_def_free_4_005863d8(EEContext&);  // generated body
void fn_r_lock_def_free_4_005863d8__recomp(EEContext&);  // recompiled
void fn_sub_586420_00586420(EEContext&);  // generated body
void fn_sub_586420_00586420__recomp(EEContext&);  // recompiled
void fn_sub_5864D8_005864d8(EEContext&);  // generated body
void fn_sub_5864D8_005864d8__recomp(EEContext&);  // recompiled
void fn_sub_5865E8_005865e8(EEContext&);  // generated body
void fn_sub_5865E8_005865e8__recomp(EEContext&);  // recompiled
void fn_sub_586688_00586688(EEContext&);  // generated body
void fn_sub_586688_00586688__recomp(EEContext&);  // recompiled
void fn_sub_586898_00586898(EEContext&);  // generated body
void fn_sub_586898_00586898__recomp(EEContext&);  // recompiled
void fn_R_LOCK_DEF_ctx_new_5_00587dc0(EEContext&);  // generated body
void fn_R_LOCK_DEF_ctx_new_5_00587dc0__recomp(EEContext&);  // recompiled
void fn_sub_587E10_00587e10(EEContext&);  // generated body
void fn_sub_587E10_00587e10__recomp(EEContext&);  // recompiled
void fn_sub_588028_00588028(EEContext&);  // generated body
void fn_sub_588028_00588028__recomp(EEContext&);  // recompiled
void fn_sub_588048_00588048(EEContext&);  // generated body
void fn_sub_588048_00588048__recomp(EEContext&);  // recompiled
void fn_sub_588068_00588068(EEContext&);  // generated body
void fn_sub_588068_00588068__recomp(EEContext&);  // recompiled
void fn_sub_588088_00588088(EEContext&);  // generated body
void fn_sub_588088_00588088__recomp(EEContext&);  // recompiled
void fn_sub_5880A8_005880a8(EEContext&);  // generated body
void fn_sub_5880A8_005880a8__recomp(EEContext&);  // recompiled
void fn_sub_5883C0_005883c0(EEContext&);  // generated body
void fn_sub_5883C0_005883c0__recomp(EEContext&);  // recompiled
void fn_sub_588C10_00588c10(EEContext&);  // generated body
void fn_sub_588C10_00588c10__recomp(EEContext&);  // recompiled
void fn_sub_588FD8_00588fd8(EEContext&);  // generated body
void fn_sub_588FD8_00588fd8__recomp(EEContext&);  // recompiled
void fn_sub_589688_00589688(EEContext&);  // generated body
void fn_sub_589688_00589688__recomp(EEContext&);  // recompiled
void fn_sub_589830_00589830(EEContext&);  // generated body
void fn_sub_589830_00589830__recomp(EEContext&);  // recompiled
void fn_sub_589928_00589928(EEContext&);  // generated body
void fn_sub_589928_00589928__recomp(EEContext&);  // recompiled
void fn_sub_589AD8_00589ad8(EEContext&);  // generated body
void fn_sub_589AD8_00589ad8__recomp(EEContext&);  // recompiled
void fn_sub_589BC8_00589bc8(EEContext&);  // generated body
void fn_sub_589BC8_00589bc8__recomp(EEContext&);  // recompiled
void fn_sub_589BD0_00589bd0(EEContext&);  // generated body
void fn_sub_589BD0_00589bd0__recomp(EEContext&);  // recompiled
void fn_sub_589D58_00589d58(EEContext&);  // generated body
void fn_sub_589D58_00589d58__recomp(EEContext&);  // recompiled
void fn_sub_58A290_0058a290(EEContext&);  // generated body
void fn_sub_58A290_0058a290__recomp(EEContext&);  // recompiled
void fn_sub_58AC78_0058ac78(EEContext&);  // generated body
void fn_sub_58AC78_0058ac78__recomp(EEContext&);  // recompiled
void fn_sub_58ACF0_0058acf0(EEContext&);  // generated body
void fn_sub_58ACF0_0058acf0__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_5838C0", 0x5838C0, &recomp_gen::fn_sub_5838C0_005838c0, &recomp_gen::fn_sub_5838C0_005838c0__recomp},
    {"sub_5838D8", 0x5838D8, &recomp_gen::fn_sub_5838D8_005838d8, &recomp_gen::fn_sub_5838D8_005838d8__recomp},
    {"sub_5838F0", 0x5838F0, &recomp_gen::fn_sub_5838F0_005838f0, &recomp_gen::fn_sub_5838F0_005838f0__recomp},
    {"sub_583940", 0x583940, &recomp_gen::fn_sub_583940_00583940, &recomp_gen::fn_sub_583940_00583940__recomp},
    {"sub_5839B8", 0x5839B8, &recomp_gen::fn_sub_5839B8_005839b8, &recomp_gen::fn_sub_5839B8_005839b8__recomp},
    {"sub_583A08", 0x583A08, &recomp_gen::fn_sub_583A08_00583a08, &recomp_gen::fn_sub_583A08_00583a08__recomp},
    {"sub_583A78", 0x583A78, &recomp_gen::fn_sub_583A78_00583a78, &recomp_gen::fn_sub_583A78_00583a78__recomp},
    {"sub_583AC8", 0x583AC8, &recomp_gen::fn_sub_583AC8_00583ac8, &recomp_gen::fn_sub_583AC8_00583ac8__recomp},
    {"sub_583B18", 0x583B18, &recomp_gen::fn_sub_583B18_00583b18, &recomp_gen::fn_sub_583B18_00583b18__recomp},
    {"sub_583BB8", 0x583BB8, &recomp_gen::fn_sub_583BB8_00583bb8, &recomp_gen::fn_sub_583BB8_00583bb8__recomp},
    {"sub_583C58", 0x583C58, &recomp_gen::fn_sub_583C58_00583c58, &recomp_gen::fn_sub_583C58_00583c58__recomp},
    {"sub_583C70", 0x583C70, &recomp_gen::fn_sub_583C70_00583c70, &recomp_gen::fn_sub_583C70_00583c70__recomp},
    {"sub_583C88", 0x583C88, &recomp_gen::fn_sub_583C88_00583c88, &recomp_gen::fn_sub_583C88_00583c88__recomp},
    {"sub_583CA0", 0x583CA0, &recomp_gen::fn_sub_583CA0_00583ca0, &recomp_gen::fn_sub_583CA0_00583ca0__recomp},
    {"sub_583CB8", 0x583CB8, &recomp_gen::fn_sub_583CB8_00583cb8, &recomp_gen::fn_sub_583CB8_00583cb8__recomp},
    {"sub_583CD0", 0x583CD0, &recomp_gen::fn_sub_583CD0_00583cd0, &recomp_gen::fn_sub_583CD0_00583cd0__recomp},
    {"sub_583CE8", 0x583CE8, &recomp_gen::fn_sub_583CE8_00583ce8, &recomp_gen::fn_sub_583CE8_00583ce8__recomp},
    {"sub_583D58", 0x583D58, &recomp_gen::fn_sub_583D58_00583d58, &recomp_gen::fn_sub_583D58_00583d58__recomp},
    {"sub_583DB8", 0x583DB8, &recomp_gen::fn_sub_583DB8_00583db8, &recomp_gen::fn_sub_583DB8_00583db8__recomp},
    {"sub_583DE8", 0x583DE8, &recomp_gen::fn_sub_583DE8_00583de8, &recomp_gen::fn_sub_583DE8_00583de8__recomp},
    {"sub_583E58", 0x583E58, &recomp_gen::fn_sub_583E58_00583e58, &recomp_gen::fn_sub_583E58_00583e58__recomp},
    {"sub_583EB8", 0x583EB8, &recomp_gen::fn_sub_583EB8_00583eb8, &recomp_gen::fn_sub_583EB8_00583eb8__recomp},
    {"sub_583ED0", 0x583ED0, &recomp_gen::fn_sub_583ED0_00583ed0, &recomp_gen::fn_sub_583ED0_00583ed0__recomp},
    {"sub_583FB8", 0x583FB8, &recomp_gen::fn_sub_583FB8_00583fb8, &recomp_gen::fn_sub_583FB8_00583fb8__recomp},
    {"sub_583FD0", 0x583FD0, &recomp_gen::fn_sub_583FD0_00583fd0, &recomp_gen::fn_sub_583FD0_00583fd0__recomp},
    {"sub_583FE8", 0x583FE8, &recomp_gen::fn_sub_583FE8_00583fe8, &recomp_gen::fn_sub_583FE8_00583fe8__recomp},
    {"sub_584000", 0x584000, &recomp_gen::fn_sub_584000_00584000, &recomp_gen::fn_sub_584000_00584000__recomp},
    {"sub_584018", 0x584018, &recomp_gen::fn_sub_584018_00584018, &recomp_gen::fn_sub_584018_00584018__recomp},
    {"sub_584030", 0x584030, &recomp_gen::fn_sub_584030_00584030, &recomp_gen::fn_sub_584030_00584030__recomp},
    {"sub_584070", 0x584070, &recomp_gen::fn_sub_584070_00584070, &recomp_gen::fn_sub_584070_00584070__recomp},
    {"sub_5844C8", 0x5844C8, &recomp_gen::fn_sub_5844C8_005844c8, &recomp_gen::fn_sub_5844C8_005844c8__recomp},
    {"sub_5845E0", 0x5845E0, &recomp_gen::fn_sub_5845E0_005845e0, &recomp_gen::fn_sub_5845E0_005845e0__recomp},
    {"sub_584680", 0x584680, &recomp_gen::fn_sub_584680_00584680, &recomp_gen::fn_sub_584680_00584680__recomp},
    {"sub_584730", 0x584730, &recomp_gen::fn_sub_584730_00584730, &recomp_gen::fn_sub_584730_00584730__recomp},
    {"sub_584778", 0x584778, &recomp_gen::fn_sub_584778_00584778, &recomp_gen::fn_sub_584778_00584778__recomp},
    {"sub_584790", 0x584790, &recomp_gen::fn_sub_584790_00584790, &recomp_gen::fn_sub_584790_00584790__recomp},
    {"sub_584800", 0x584800, &recomp_gen::fn_sub_584800_00584800, &recomp_gen::fn_sub_584800_00584800__recomp},
    {"sub_5848D8", 0x5848D8, &recomp_gen::fn_sub_5848D8_005848d8, &recomp_gen::fn_sub_5848D8_005848d8__recomp},
    {"sub_584928", 0x584928, &recomp_gen::fn_sub_584928_00584928, &recomp_gen::fn_sub_584928_00584928__recomp},
    {"sub_584950", 0x584950, &recomp_gen::fn_sub_584950_00584950, &recomp_gen::fn_sub_584950_00584950__recomp},
    {"sub_584978", 0x584978, &recomp_gen::fn_sub_584978_00584978, &recomp_gen::fn_sub_584978_00584978__recomp},
    {"sub_584A08", 0x584A08, &recomp_gen::fn_sub_584A08_00584a08, &recomp_gen::fn_sub_584A08_00584a08__recomp},
    {"sub_584AA0", 0x584AA0, &recomp_gen::fn_sub_584AA0_00584aa0, &recomp_gen::fn_sub_584AA0_00584aa0__recomp},
    {"sub_584AA8", 0x584AA8, &recomp_gen::fn_sub_584AA8_00584aa8, &recomp_gen::fn_sub_584AA8_00584aa8__recomp},
    {"sub_584D98", 0x584D98, &recomp_gen::fn_sub_584D98_00584d98, &recomp_gen::fn_sub_584D98_00584d98__recomp},
    {"sub_584F30", 0x584F30, &recomp_gen::fn_sub_584F30_00584f30, &recomp_gen::fn_sub_584F30_00584f30__recomp},
    {"WTLS_set_table_1", 0x5851C0, &recomp_gen::fn_WTLS_set_table_1_005851c0, &recomp_gen::fn_WTLS_set_table_1_005851c0__recomp},
    {"sub_585268", 0x585268, &recomp_gen::fn_sub_585268_00585268, &recomp_gen::fn_sub_585268_00585268__recomp},
    {"sub_5852A0", 0x5852A0, &recomp_gen::fn_sub_5852A0_005852a0, &recomp_gen::fn_sub_5852A0_005852a0__recomp},
    {"sub_5852C0", 0x5852C0, &recomp_gen::fn_sub_5852C0_005852c0, &recomp_gen::fn_sub_5852C0_005852c0__recomp},
    {"coshl_11", 0x585498, &recomp_gen::fn_coshl_11_00585498, &recomp_gen::fn_coshl_11_00585498__recomp},
    {"sub_5854B8", 0x5854B8, &recomp_gen::fn_sub_5854B8_005854b8, &recomp_gen::fn_sub_5854B8_005854b8__recomp},
    {"sub_5854D0", 0x5854D0, &recomp_gen::fn_sub_5854D0_005854d0, &recomp_gen::fn_sub_5854D0_005854d0__recomp},
    {"sub_5854F0", 0x5854F0, &recomp_gen::fn_sub_5854F0_005854f0, &recomp_gen::fn_sub_5854F0_005854f0__recomp},
    {"hypotl_11", 0x585508, &recomp_gen::fn_hypotl_11_00585508, &recomp_gen::fn_hypotl_11_00585508__recomp},
    {"sub_585528", 0x585528, &recomp_gen::fn_sub_585528_00585528, &recomp_gen::fn_sub_585528_00585528__recomp},
    {"sub_585540", 0x585540, &recomp_gen::fn_sub_585540_00585540, &recomp_gen::fn_sub_585540_00585540__recomp},
    {"sub_585560", 0x585560, &recomp_gen::fn_sub_585560_00585560, &recomp_gen::fn_sub_585560_00585560__recomp},
    {"powl_11", 0x585640, &recomp_gen::fn_powl_11_00585640, &recomp_gen::fn_powl_11_00585640__recomp},
    {"sinhl_11", 0x585670, &recomp_gen::fn_sinhl_11_00585670, &recomp_gen::fn_sinhl_11_00585670__recomp},
    {"sub_585D38", 0x585D38, &recomp_gen::fn_sub_585D38_00585d38, &recomp_gen::fn_sub_585D38_00585d38__recomp},
    {"sub_585D50", 0x585D50, &recomp_gen::fn_sub_585D50_00585d50, &recomp_gen::fn_sub_585D50_00585d50__recomp},
    {"sub_585E08", 0x585E08, &recomp_gen::fn_sub_585E08_00585e08, &recomp_gen::fn_sub_585E08_00585e08__recomp},
    {"sub_5860B0", 0x5860B0, &recomp_gen::fn_sub_5860B0_005860b0, &recomp_gen::fn_sub_5860B0_005860b0__recomp},
    {"sub_5860D0", 0x5860D0, &recomp_gen::fn_sub_5860D0_005860d0, &recomp_gen::fn_sub_5860D0_005860d0__recomp},
    {"sub_586148", 0x586148, &recomp_gen::fn_sub_586148_00586148, &recomp_gen::fn_sub_586148_00586148__recomp},
    {"sub_586150", 0x586150, &recomp_gen::fn_sub_586150_00586150, &recomp_gen::fn_sub_586150_00586150__recomp},
    {"rdbuf__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_0", 0x5861F8, &recomp_gen::fn_rdbuf__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_0_005861f8, &recomp_gen::fn_rdbuf__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_0_005861f8__recomp},
    {"sub_586220", 0x586220, &recomp_gen::fn_sub_586220_00586220, &recomp_gen::fn_sub_586220_00586220__recomp},
    {"ctime", 0x586298, &recomp_gen::fn_ctime_00586298, &recomp_gen::fn_ctime_00586298__recomp},
    {"sub_5862B8", 0x5862B8, &recomp_gen::fn_sub_5862B8_005862b8, &recomp_gen::fn_sub_5862B8_005862b8__recomp},
    {"sub_5862E8", 0x5862E8, &recomp_gen::fn_sub_5862E8_005862e8, &recomp_gen::fn_sub_5862E8_005862e8__recomp},
    {"sub_5862F8", 0x5862F8, &recomp_gen::fn_sub_5862F8_005862f8, &recomp_gen::fn_sub_5862F8_005862f8__recomp},
    {"sub_586338", 0x586338, &recomp_gen::fn_sub_586338_00586338, &recomp_gen::fn_sub_586338_00586338__recomp},
    {"r_lock_def_free_4", 0x5863D8, &recomp_gen::fn_r_lock_def_free_4_005863d8, &recomp_gen::fn_r_lock_def_free_4_005863d8__recomp},
    {"sub_586420", 0x586420, &recomp_gen::fn_sub_586420_00586420, &recomp_gen::fn_sub_586420_00586420__recomp},
    {"sub_5864D8", 0x5864D8, &recomp_gen::fn_sub_5864D8_005864d8, &recomp_gen::fn_sub_5864D8_005864d8__recomp},
    {"sub_5865E8", 0x5865E8, &recomp_gen::fn_sub_5865E8_005865e8, &recomp_gen::fn_sub_5865E8_005865e8__recomp},
    {"sub_586688", 0x586688, &recomp_gen::fn_sub_586688_00586688, &recomp_gen::fn_sub_586688_00586688__recomp},
    {"sub_586898", 0x586898, &recomp_gen::fn_sub_586898_00586898, &recomp_gen::fn_sub_586898_00586898__recomp},
    {"R_LOCK_DEF_ctx_new_5", 0x587DC0, &recomp_gen::fn_R_LOCK_DEF_ctx_new_5_00587dc0, &recomp_gen::fn_R_LOCK_DEF_ctx_new_5_00587dc0__recomp},
    {"sub_587E10", 0x587E10, &recomp_gen::fn_sub_587E10_00587e10, &recomp_gen::fn_sub_587E10_00587e10__recomp},
    {"sub_588028", 0x588028, &recomp_gen::fn_sub_588028_00588028, &recomp_gen::fn_sub_588028_00588028__recomp},
    {"sub_588048", 0x588048, &recomp_gen::fn_sub_588048_00588048, &recomp_gen::fn_sub_588048_00588048__recomp},
    {"sub_588068", 0x588068, &recomp_gen::fn_sub_588068_00588068, &recomp_gen::fn_sub_588068_00588068__recomp},
    {"sub_588088", 0x588088, &recomp_gen::fn_sub_588088_00588088, &recomp_gen::fn_sub_588088_00588088__recomp},
    {"sub_5880A8", 0x5880A8, &recomp_gen::fn_sub_5880A8_005880a8, &recomp_gen::fn_sub_5880A8_005880a8__recomp},
    {"sub_5883C0", 0x5883C0, &recomp_gen::fn_sub_5883C0_005883c0, &recomp_gen::fn_sub_5883C0_005883c0__recomp},
    {"sub_588C10", 0x588C10, &recomp_gen::fn_sub_588C10_00588c10, &recomp_gen::fn_sub_588C10_00588c10__recomp},
    {"sub_588FD8", 0x588FD8, &recomp_gen::fn_sub_588FD8_00588fd8, &recomp_gen::fn_sub_588FD8_00588fd8__recomp},
    {"sub_589688", 0x589688, &recomp_gen::fn_sub_589688_00589688, &recomp_gen::fn_sub_589688_00589688__recomp},
    {"sub_589830", 0x589830, &recomp_gen::fn_sub_589830_00589830, &recomp_gen::fn_sub_589830_00589830__recomp},
    {"sub_589928", 0x589928, &recomp_gen::fn_sub_589928_00589928, &recomp_gen::fn_sub_589928_00589928__recomp},
    {"sub_589AD8", 0x589AD8, &recomp_gen::fn_sub_589AD8_00589ad8, &recomp_gen::fn_sub_589AD8_00589ad8__recomp},
    {"sub_589BC8", 0x589BC8, &recomp_gen::fn_sub_589BC8_00589bc8, &recomp_gen::fn_sub_589BC8_00589bc8__recomp},
    {"sub_589BD0", 0x589BD0, &recomp_gen::fn_sub_589BD0_00589bd0, &recomp_gen::fn_sub_589BD0_00589bd0__recomp},
    {"sub_589D58", 0x589D58, &recomp_gen::fn_sub_589D58_00589d58, &recomp_gen::fn_sub_589D58_00589d58__recomp},
    {"sub_58A290", 0x58A290, &recomp_gen::fn_sub_58A290_0058a290, &recomp_gen::fn_sub_58A290_0058a290__recomp},
    {"sub_58AC78", 0x58AC78, &recomp_gen::fn_sub_58AC78_0058ac78, &recomp_gen::fn_sub_58AC78_0058ac78__recomp},
    {"sub_58ACF0", 0x58ACF0, &recomp_gen::fn_sub_58ACF0_0058acf0, &recomp_gen::fn_sub_58ACF0_0058acf0__recomp},
};

// The world: 64 KiB of free RAM above the harness's arena (TODO: the function's real structures).
constexpr u32 kWorld = 0x01810000u;
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 64;

}  // namespace

TEST_CASE("game(libs22): every body equals its recompiled body on random worlds") {
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

namespace L = p3fes::game::l22;

// A world of MWSFD players and SFD handles: the player at kPlayer (684 bytes, used word +0 = 1 or not), its SFX
// handle (+168), play list (+72), SFD handle (+60) and slave record (+640..+660) pointing into the world; an SFD handle
// at kSfd with its stream lanes (4880 + 116 x lane) set up as PCM rings; every other word one of the values the bodies
// compare against (0 / 1 / 2 / 3 / 18 / -1, ring sizes, the codes) or a pointer into the world.
constexpr u32 kPlayer = 0x01820000u;
constexpr u32 kSpan = 0x10000u;
constexpr u32 kSfd = kPlayer + 0x4000u;  // an SFD handle (lanes up to +4880 + 116 x 8)
constexpr u32 kSfx = kPlayer + 0x2000u;
constexpr u32 kObj = kPlayer + 0x3000u;  // a frame / target object
constexpr u32 kPcm = kPlayer + 0xA000u;  // ring buffers

u32 enum_word(std::mt19937& rng) {
    static const u32 kValues[] = {0u, 1u, 2u, 3u, 4u, 8u, 9u, 16u, 18u, 32u, 0xFFFFFFFFu, 0xFFFFFFFEu, 0x400u, 0x800u,
                                  0x1000u, 44100u, 48000u, 0x7FFFFFFFu, 0x80000000u};
    const u32 k = rng() % 8;
    if (k < 5) return kValues[rng() % (sizeof kValues / sizeof kValues[0])];
    if (k < 7) return kPlayer + ((rng() % kSpan) & ~3u);
    return rng() % 0x10000u;
}

void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }
u32 r32(Machine& m, u32 va) {
    u32 v = 0;
    std::memcpy(&v, m.at(va), 4);
    return v;
}

// Lane `lane` of the handle at `h` as a PCM ring of `cap` samples of `bits` bits (16 -> 2 bytes) from `base`, with the
// write / read indexes and totals given.
void ring(Machine& m, u32 h, u32 lane, u32 base, u32 cap, u32 bits, u32 widx, u32 ridx, u32 wtot, u32 rtot) {
    const u32 l = h + L::lane::kBase + L::lane::kSize * lane;
    w32(m, l + L::lane::kUsed, 1);
    const u32 r = l + L::lane::kRing;
    w32(m, r + 0, base);
    w32(m, r + 4, cap * ((bits + 7) / 8));
    w32(m, r + 12, bits);
    w32(m, r + 16, 1);
    w32(m, r + 20, base);
    w32(m, r + 24, base + cap * ((bits + 7) / 8));
    w32(m, r + 28, cap);
    w32(m, r + 32, widx);
    w32(m, r + 36, ridx);
    w32(m, r + 40, wtot);
    w32(m, r + 44, rtot);
}

void player_world(Machine& m, std::mt19937& rng) {
    for (u32 i = 0; i + 4 <= kSpan; i += 4) w32(m, kPlayer + i, enum_word(rng));
    w32(m, kPlayer + 0, rng() % 4 ? 1u : 0u);  // mwPlyIsValidHn: used word
    w32(m, kPlayer + L::ply::kSfx, kSfx);
    w32(m, kPlayer + L::ply::kSfd, kSfd);
    w32(m, kPlayer + L::ply::kSlaveTarget, kObj);
    w32(m, kObj, rng() % 3 ? kObj + 0x40 : 0u);  // the frame object's word +0 (sub_583B18: 0 = "getfrm is failed")
    for (u32 lane = 0; lane < 4; ++lane) {
        if (rng() % 4 == 0) continue;  // a lane left as random words (often unused)
        const u32 cap = 0x100u << (rng() % 3);
        ring(m, kSfd, lane, kPcm + 0x1000 * lane, cap, rng() % 2 ? 16u : 8u, rng() % cap, rng() % cap,
             rng() % (2 * cap), rng() % (2 * cap));
    }
}

// Stand-ins for callees this build does not emit and the bodies meet, none claimed by a current packet: the CRI
// error printer, the SFD lock / unlock, the SJ attach, the play-list reset / thunk, the SVM server delete, the ADXSTM
// calls, sub_53EC20, the ADX decoder query, and sprintf (the text into the guest buffer); a custom one for the MPEG
// audio header decoder sub_58AF20 (a leaf: the fields of the four header bytes, per the instructions). Each logs the
// call; both bodies of a pair get a fresh set and the two call logs must be equal.
struct Rec {
    u32 va;
    const char* name;
    u64 v0;
};
const Rec kRecorders[] = {
    {0x585590u, "sub_585590 (error)", 0},       {0x58C100u, "sub_58C100 (lock)", 0},
    {0x58C118u, "sub_58C118 (unlock)", 0},      {0x58C228u, "sub_58C228 (SJ attach)", 0},
    {0x55D668u, "sub_55D668 (list reset)", 0},  {0x55D790u, "sub_55D790", 7},
    {0x564EF8u, "sub_564EF8 (SVM delete)", 0},  {0x5463A8u, "sub_5463A8 (ADXSTM seek)", 0},
    {0x546498u, "sub_546498 (ADXSTM release)", 0}, {0x5460E0u, "sub_5460E0 (ADXSTM set file)", 0},
    {0x546270u, "sub_546270 (ADXSTM stop)", 0}, {0x546718u, "sub_546718 (ADXSTM start)", 0},
    {0x53EC20u, "sub_53EC20", 0},               {0x5876F0u, "sub_5876F0 (decoder has data)", 1},
};
void mpeg_header(EEContext& ctx, StandIns&, StandInCall& call) {
    const u32 out = static_cast<u32>(call.args[0]), in = static_cast<u32>(call.args[1]);
    u8 b[4];
    for (u32 i = 0; i < 4; ++i) b[i] = ctx.memory->read<u8>(in + i);
    const u8 f[11] = {static_cast<u8>((b[1] >> 1) & 3), static_cast<u8>(b[1] & 1), static_cast<u8>(b[2] >> 4),
                      static_cast<u8>((b[2] >> 2) & 3), static_cast<u8>((b[2] & 2) != 0), static_cast<u8>(b[2] & 1),
                      static_cast<u8>(b[3] >> 6), static_cast<u8>((b[3] >> 4) & 3), static_cast<u8>((b[3] >> 3) & 1),
                      static_cast<u8>((b[3] >> 2) & 1), static_cast<u8>(b[3] & 3)};
    for (u32 i = 0; i < 11; ++i) ctx.memory->write<u8>(out + i, f[i]);
    call.v0 = b[3] >> 6;
}
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
        w->si.install(0x58AF20u, "sub_58AF20 (MPEG audio header)", &mpeg_header, 30);
        install_sprintf(w->si);
    }
    g_si[0] = wh.get();
    g_si[1] = wr.get();
    g_fn[0] = hand;
    g_fn[1] = recomp;
    const hgp::Run r = hgp::pair(m, &thunk0, &thunk1, args, seed, what);
    expect_same_log(wh->si, wr->si, what);
    return r;
}

u64 world_arg(std::mt19937& rng) {
    const u32 k = rng() % 10;
    if (k < 4) return sx(kPlayer);
    if (k < 5) return sx(kSfd);
    if (k < 6) return sx(kObj);
    if (k < 8) return rng() % 6;  // lanes, origins, counts
    return sx(enum_word(rng));
}

void run_player_worlds(Machine& m, u32 seeds, const char* label) {
    const char* only = std::getenv("P3FES_HG_ONLY");
    for (const Case& c : kCases) {
        if (only && std::string(only) != c.name) continue;
        int stops = 0;
        for (u32 seed = 1; seed <= seeds; ++seed) {
            std::mt19937 rng{seed * 104729u + c.addr};
            player_world(m, rng);
            const Args args{world_arg(rng), world_arg(rng), world_arg(rng), world_arg(rng)};
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

u64 v0_of(const hgp::Run& r) { return r.end.gpr[2].u64[0]; }

}  // namespace

TEST_CASE("game(libs22): every body equals its recompiled body on player / SFD lane worlds") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    const char* env = std::getenv("P3FES_HG_SEEDS");
    run_player_worlds(*m, env ? static_cast<u32>(std::strtoul(env, nullptr, 10)) : 32u, "player world");
}

// The same worlds over the RAM of the replay snapshots (real globals: the slave interface 0x7B4538, the MWSFD work
// 0x7B2F50, the SVM slots 0x9A6EC0 / 0x9A6EC4); and every body on each player in use in the table 0x7B2FBC (8 x 684)
// and on the players 0x7B451C / 0x7B4548 point to.
TEST_CASE("game(libs22): every body equals its recompiled body on the replay snapshots") {
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
        run_player_worlds(*m, 4u, dir);
        // The players: the table's used entries, and the players the globals 0x7B451C / 0x7B4548 point to.
        std::vector<u32> players;
        for (u32 i = 0; i < 10; ++i) {
            u32 p = 0x7B2FBCu + 684u * i, w = 0;
            if (i >= 8) {
                std::memcpy(&p, snap.data() + (i == 8 ? 0x7B451Cu : 0x7B4548u), 4);
                if (p == 0 || p >= 0x01FF0000u) continue;
            }
            std::memcpy(&w, snap.data() + p, 4);
            if (i < 8 && w != 1) continue;
            if (std::find(players.begin(), players.end(), p) == players.end()) players.push_back(p);
        }
        const int live = static_cast<int>(players.size());
        for (const u32 p : players) {
            for (const Case& c : kCases) {
                std::memcpy(m->mem.main_ram(), snap.data(), snap.size());  // the player as the snapshot holds it
                for (u32 seed = 1; seed <= 2; ++seed) {
                    std::mt19937 rng{seed + c.addr};
                    const Args args{sx(p), rng() % 4, rng() % 4, rng() % 4};
                    spair(*m, c.hand, c.recomp, args, seed, c.name);
                }
            }
        }
        const std::string note = std::string(dir) + ": " + std::to_string(live) + " players";
        MESSAGE(note);
    }
}

// Documented rules on the host, from the instructions (both bodies run, compared, then the result checked).
TEST_CASE("game(libs22): slave interface, player record, PCM ring and MPEG audio header rules") {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return;
    }
    for (u32 i = 0; i < kSpan; i += 4) w32(*m, kPlayer + i, 0);
    // WTLS_set_table_1: stores $a0 in 0x7B4538; $v0 keeps 0x7B0000.
    {
        const Case& c = find("WTLS_set_table_1");
        CHECK(v0_of(spair(*m, c.hand, c.recomp, Args{sx(kObj), 0, 0, 0}, 1, c.name)) == 0x7B0000u);
        CHECK(r32(*m, 0x7B4538u) == kObj);
    }
    // sub_5838D8: *$a1 = player +408, *$a2 = player +412.
    {
        const Case& c = find("sub_5838D8");
        w32(*m, kPlayer + 408, 0x1234u);
        w32(*m, kPlayer + 412, 0x5678u);
        spair(*m, c.hand, c.recomp, Args{sx(kPlayer), sx(kObj), sx(kObj + 4), 0}, 1, c.name);
        CHECK(r32(*m, kObj) == 0x1234u);
        CHECK(r32(*m, kObj + 4) == 0x5678u);
    }
    // sub_584AA0 / sub_584AA8: the slave's SJ (+652) and core handle (+660).
    {
        w32(*m, kPlayer + L::ply::kSlaveSj, 0x11u);
        w32(*m, kPlayer + L::ply::kSlaveCore, 0x22u);
        const Case& sj = find("sub_584AA0");
        const Case& core = find("sub_584AA8");
        CHECK(v0_of(spair(*m, sj.hand, sj.recomp, Args{sx(kPlayer), 0, 0, 0}, 1, sj.name)) == 0x11u);
        CHECK(v0_of(spair(*m, core.hand, core.recomp, Args{sx(kPlayer), 0, 0, 0}, 1, core.name)) == 0x22u);
    }
    // sub_588C10: lane 1, a 0x1000-byte buffer, 16-bit stereo: per channel 0x800 bytes = 0x400 samples.
    {
        const Case& c = find("sub_588C10");
        const u32 l = kSfd + L::lane::kBase + L::lane::kSize * 1 + L::lane::kRing;
        w32(*m, l + 0, kPcm);
        w32(*m, l + 4, 0x1000u);
        CHECK(v0_of(spair(*m, c.hand, c.recomp, Args{sx(kSfd), 1, 16, 2}, 1, c.name)) == kPcm + 0x800u);
        CHECK(r32(*m, l + 12) == 16u);
        CHECK(r32(*m, l + 16) == 2u);
        CHECK(r32(*m, l + 20) == kPcm);
        CHECK(r32(*m, l + 24) == kPcm + 0x800u);
        CHECK(r32(*m, l + 28) == 0x400u);
        const Case& sz = find("sub_588FD8");
        CHECK(v0_of(spair(*m, sz.hand, sz.recomp, Args{sx(kSfd), 1, sx(kObj), 0}, 1, sz.name)) == 116u);
        CHECK(r32(*m, kObj) == 0x1000u);
    }
    // The PCM ring of lane 2 (0x400 8-bit samples): write 0x300, read 0x100, then a write of 0x300 overflows (0xFF000406)
    // and a read past the written total underflows (0xFF000407); an unused lane raises 0xFF000401.
    {
        const Case& wa = find("sub_589688");
        const Case& wc = find("sub_589830");
        const Case& ra = find("sub_589928");
        const Case& rc = find("sub_589AD8");
        const u32 base = kPcm + 0x2000u, rec = kObj + 0x100u;
        const u32 r = kSfd + L::lane::kBase + L::lane::kSize * 2 + L::lane::kRing;
        ring(*m, kSfd, 2, base, 0x400u, 8u, 0, 0, 0, 0);
        CHECK(v0_of(spair(*m, wa.hand, wa.recomp, Args{sx(kSfd), 2, sx(rec), 0}, 1, wa.name)) == 0u);
        CHECK(r32(*m, rec + 12) == 0x400u);  // one piece: the whole ring
        CHECK(r32(*m, rec + 16) == 0u);
        CHECK(r32(*m, rec + 20) == base);
        CHECK(v0_of(spair(*m, ra.hand, ra.recomp, Args{sx(kSfd), 2, sx(rec), 0}, 1, ra.name)) == 0u);
        CHECK(r32(*m, rec + 12) == 0u);  // nothing to read
        CHECK(v0_of(spair(*m, wc.hand, wc.recomp, Args{sx(kSfd), 2, 0x300, 0}, 1, wc.name)) == 0u);
        CHECK(r32(*m, r + 32) == 0x300u);
        CHECK(r32(*m, r + 40) == 0x300u);
        CHECK(r32(*m, kSfd + 68) == 1u);
        CHECK(v0_of(spair(*m, ra.hand, ra.recomp, Args{sx(kSfd), 2, sx(rec), 0}, 2, ra.name)) == 0u);
        CHECK(r32(*m, rec + 12) == 0x300u);
        CHECK(r32(*m, rec + 20) == base);
        CHECK(v0_of(spair(*m, rc.hand, rc.recomp, Args{sx(kSfd), 2, 0x100, 0}, 1, rc.name)) == 0u);
        CHECK(r32(*m, r + 36) == 0x100u);
        CHECK(r32(*m, r + 44) == 0x100u);
        CHECK(v0_of(spair(*m, wa.hand, wa.recomp, Args{sx(kSfd), 2, sx(rec), 0}, 2, wa.name)) == 0u);
        CHECK(r32(*m, rec + 12) == 0x100u);  // from the write index 0x300 to the ring end
        CHECK(r32(*m, rec + 16) == 0x100u);  // then the wrapped piece up to the read index
        CHECK(v0_of(spair(*m, wc.hand, wc.recomp, Args{sx(kSfd), 2, 0x300, 0}, 2, wc.name)) == sx(0xFF000406u));
        CHECK(r32(*m, r + 32) == 0x200u);  // the write index wrapped
        CHECK(v0_of(spair(*m, rc.hand, rc.recomp, Args{sx(kSfd), 2, 0x600, 0}, 2, rc.name)) == sx(0xFF000407u));
        w32(*m, kSfd + L::lane::kBase + L::lane::kSize * 5 + L::lane::kUsed, 0);
        CHECK(v0_of(spair(*m, wc.hand, wc.recomp, Args{sx(kSfd), 5, 1, 0}, 3, wc.name)) == sx(0xFF000401u));
        CHECK(v0_of(spair(*m, rc.hand, rc.recomp, Args{sx(kSfd), 5, 0, 0}, 3, rc.name)) == 0u);  // 0 samples: nothing
    }
    // sub_58AC78 / sub_58ACF0 on the MPEG-1 Layer III header FF FB 90 64 (128 kbit/s, 44100 Hz): 128000 bit/s and
    // 1000 x 1152 x 128 / (8 x 44100) = 417 bytes; FF FB F0 64 (bit-rate index 15) gives -1.
    {
        const Case& br = find("sub_58AC78");
        const Case& fs = find("sub_58ACF0");
        const u32 buf = kObj + 0x200u;
        const u8 hdr[8] = {0xFF, 0xFB, 0x90, 0x64, 0, 0, 0, 0};
        std::memcpy(m->at(buf), hdr, sizeof hdr);
        CHECK(v0_of(spair(*m, br.hand, br.recomp, Args{sx(buf), 8, 0, 0}, 1, br.name)) == 128000u);
        CHECK(v0_of(spair(*m, fs.hand, fs.recomp, Args{sx(buf), 8, 0, 0}, 1, fs.name)) == 417u);
        m->at(buf)[2] = 0xF0;
        CHECK(v0_of(spair(*m, br.hand, br.recomp, Args{sx(buf), 8, 0, 0}, 2, br.name)) == ~u64{0});
        CHECK(v0_of(spair(*m, fs.hand, fs.recomp, Args{sx(buf), 8, 0, 0}, 2, fs.name)) == ~u64{0});
    }
}

#else

TEST_CASE("game(libs22): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
