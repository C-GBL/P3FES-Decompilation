// Pair tests for slice libs12 (the CRI Sofdec band 0x580588-0x58FF70; skeleton from p3fes_handgen). Every body
// against its recompiled body, compared by tests/game/handgen_pairs.h: the whole register file and cycle count at
// every check point and at the return / stop, all 32 MiB of RAM (the dead stack included), the scratchpad, the BIOS
// window, the bus log and the stand-ins' call logs. Worlds: random ones, then the boot movie's snapshot (a live MWSFD
// player with its SFD handle, stream records and transfer slots) and the dorm snapshot, each function on the record
// its role takes; then documented-rule checks on the host.
#include "handgen_pairs.h"
#include "stand_ins.h"

#include "p3fes/game/libs12.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <memory>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#ifndef P3FES_GAME_HAVE_GENERATED
#define P3FES_GAME_HAVE_GENERATED 0
#endif

#if P3FES_GAME_HAVE_GENERATED

using namespace p3fes;
using namespace p3fes::game_test;

namespace p3fes::recomp_gen {
void fn_sub_580588_00580588(EEContext&);  // generated body
void fn_sub_580588_00580588__recomp(EEContext&);  // recompiled
void fn_sub_580A98_00580a98(EEContext&);  // generated body
void fn_sub_580A98_00580a98__recomp(EEContext&);  // recompiled
void fn_sub_580C20_00580c20(EEContext&);  // generated body
void fn_sub_580C20_00580c20__recomp(EEContext&);  // recompiled
void fn_sub_580C38_00580c38(EEContext&);  // generated body
void fn_sub_580C38_00580c38__recomp(EEContext&);  // recompiled
void fn_sub_580C50_00580c50(EEContext&);  // generated body
void fn_sub_580C50_00580c50__recomp(EEContext&);  // recompiled
void fn_sub_580C68_00580c68(EEContext&);  // generated body
void fn_sub_580C68_00580c68__recomp(EEContext&);  // recompiled
void fn_sub_580C98_00580c98(EEContext&);  // generated body
void fn_sub_580C98_00580c98__recomp(EEContext&);  // recompiled
void fn_sub_581270_00581270(EEContext&);  // generated body
void fn_sub_581270_00581270__recomp(EEContext&);  // recompiled
void fn_sub_5812D8_005812d8(EEContext&);  // generated body
void fn_sub_5812D8_005812d8__recomp(EEContext&);  // recompiled
void fn_sub_581628_00581628(EEContext&);  // generated body
void fn_sub_581628_00581628__recomp(EEContext&);  // recompiled
void fn_sub_581660_00581660(EEContext&);  // generated body
void fn_sub_581660_00581660__recomp(EEContext&);  // recompiled
void fn__M_numpunct_facet__CQ24_STL8ios_base_005816e0(EEContext&);  // generated body
void fn__M_numpunct_facet__CQ24_STL8ios_base_005816e0__recomp(EEContext&);  // recompiled
void fn_sub_582040_00582040(EEContext&);  // generated body
void fn_sub_582040_00582040__recomp(EEContext&);  // recompiled
void fn_sub_582118_00582118(EEContext&);  // generated body
void fn_sub_582118_00582118__recomp(EEContext&);  // recompiled
void fn_sub_5827D8_005827d8(EEContext&);  // generated body
void fn_sub_5827D8_005827d8__recomp(EEContext&);  // recompiled
void fn_sub_582968_00582968(EEContext&);  // generated body
void fn_sub_582968_00582968__recomp(EEContext&);  // recompiled
void fn_sub_5829B8_005829b8(EEContext&);  // generated body
void fn_sub_5829B8_005829b8__recomp(EEContext&);  // recompiled
void fn_sub_582A58_00582a58(EEContext&);  // generated body
void fn_sub_582A58_00582a58__recomp(EEContext&);  // recompiled
void fn_sub_582AB8_00582ab8(EEContext&);  // generated body
void fn_sub_582AB8_00582ab8__recomp(EEContext&);  // recompiled
void fn_sub_582B88_00582b88(EEContext&);  // generated body
void fn_sub_582B88_00582b88__recomp(EEContext&);  // recompiled
void fn_sub_582B98_00582b98(EEContext&);  // generated body
void fn_sub_582B98_00582b98__recomp(EEContext&);  // recompiled
void fn_sub_582BA8_00582ba8(EEContext&);  // generated body
void fn_sub_582BA8_00582ba8__recomp(EEContext&);  // recompiled
void fn_sub_583058_00583058(EEContext&);  // generated body
void fn_sub_583058_00583058__recomp(EEContext&);  // recompiled
void fn_sub_584190_00584190(EEContext&);  // generated body
void fn_sub_584190_00584190__recomp(EEContext&);  // recompiled
void fn_sub_584230_00584230(EEContext&);  // generated body
void fn_sub_584230_00584230__recomp(EEContext&);  // recompiled
void fn_sub_584290_00584290(EEContext&);  // generated body
void fn_sub_584290_00584290__recomp(EEContext&);  // recompiled
void fn_sub_584338_00584338(EEContext&);  // generated body
void fn_sub_584338_00584338__recomp(EEContext&);  // recompiled
void fn_sub_584830_00584830(EEContext&);  // generated body
void fn_sub_584830_00584830__recomp(EEContext&);  // recompiled
void fn_sub_5849A0_005849a0(EEContext&);  // generated body
void fn_sub_5849A0_005849a0__recomp(EEContext&);  // recompiled
void fn_sceLibgcc32GetErxEntries_19_005851a0(EEContext&);  // generated body
void fn_sceLibgcc32GetErxEntries_19_005851a0__recomp(EEContext&);  // recompiled
void fn_sub_586490_00586490(EEContext&);  // generated body
void fn_sub_586490_00586490__recomp(EEContext&);  // recompiled
void fn_sub_586F20_00586f20(EEContext&);  // generated body
void fn_sub_586F20_00586f20__recomp(EEContext&);  // recompiled
void fn_sub_587218_00587218(EEContext&);  // generated body
void fn_sub_587218_00587218__recomp(EEContext&);  // recompiled
void fn_sub_588720_00588720(EEContext&);  // generated body
void fn_sub_588720_00588720__recomp(EEContext&);  // recompiled
void fn_sub_588740_00588740(EEContext&);  // generated body
void fn_sub_588740_00588740__recomp(EEContext&);  // recompiled
void fn_sub_588878_00588878(EEContext&);  // generated body
void fn_sub_588878_00588878__recomp(EEContext&);  // recompiled
void fn_sub_5888B8_005888b8(EEContext&);  // generated body
void fn_sub_5888B8_005888b8__recomp(EEContext&);  // recompiled
void fn_sub_588978_00588978(EEContext&);  // generated body
void fn_sub_588978_00588978__recomp(EEContext&);  // recompiled
void fn_sub_588A10_00588a10(EEContext&);  // generated body
void fn_sub_588A10_00588a10__recomp(EEContext&);  // recompiled
void fn_sub_588A50_00588a50(EEContext&);  // generated body
void fn_sub_588A50_00588a50__recomp(EEContext&);  // recompiled
void fn_sub_588AB8_00588ab8(EEContext&);  // generated body
void fn_sub_588AB8_00588ab8__recomp(EEContext&);  // recompiled
void fn_sub_588B70_00588b70(EEContext&);  // generated body
void fn_sub_588B70_00588b70__recomp(EEContext&);  // recompiled
void fn_sub_588C98_00588c98(EEContext&);  // generated body
void fn_sub_588C98_00588c98__recomp(EEContext&);  // recompiled
void fn_sub_588CE8_00588ce8(EEContext&);  // generated body
void fn_sub_588CE8_00588ce8__recomp(EEContext&);  // recompiled
void fn_sub_588D38_00588d38(EEContext&);  // generated body
void fn_sub_588D38_00588d38__recomp(EEContext&);  // recompiled
void fn_sub_588DE0_00588de0(EEContext&);  // generated body
void fn_sub_588DE0_00588de0__recomp(EEContext&);  // recompiled
void fn_sub_588E98_00588e98(EEContext&);  // generated body
void fn_sub_588E98_00588e98__recomp(EEContext&);  // recompiled
void fn_sub_588F38_00588f38(EEContext&);  // generated body
void fn_sub_588F38_00588f38__recomp(EEContext&);  // recompiled
void fn_sub_588F90_00588f90(EEContext&);  // generated body
void fn_sub_588F90_00588f90__recomp(EEContext&);  // recompiled
void fn_sub_589000_00589000(EEContext&);  // generated body
void fn_sub_589000_00589000__recomp(EEContext&);  // recompiled
void fn_sub_5890D8_005890d8(EEContext&);  // generated body
void fn_sub_5890D8_005890d8__recomp(EEContext&);  // recompiled
void fn_sub_5892E8_005892e8(EEContext&);  // generated body
void fn_sub_5892E8_005892e8__recomp(EEContext&);  // recompiled
void fn_sub_5893E0_005893e0(EEContext&);  // generated body
void fn_sub_5893E0_005893e0__recomp(EEContext&);  // recompiled
void fn_sub_589438_00589438(EEContext&);  // generated body
void fn_sub_589438_00589438__recomp(EEContext&);  // recompiled
void fn_sub_5894A8_005894a8(EEContext&);  // generated body
void fn_sub_5894A8_005894a8__recomp(EEContext&);  // recompiled
void fn_sub_589510_00589510(EEContext&);  // generated body
void fn_sub_589510_00589510__recomp(EEContext&);  // recompiled
void fn_sub_589530_00589530(EEContext&);  // generated body
void fn_sub_589530_00589530__recomp(EEContext&);  // recompiled
void fn_sub_589550_00589550(EEContext&);  // generated body
void fn_sub_589550_00589550__recomp(EEContext&);  // recompiled
void fn_sub_589650_00589650(EEContext&);  // generated body
void fn_sub_589650_00589650__recomp(EEContext&);  // recompiled
void fn_sub_589CF0_00589cf0(EEContext&);  // generated body
void fn_sub_589CF0_00589cf0__recomp(EEContext&);  // recompiled
void fn_sub_589D30_00589d30(EEContext&);  // generated body
void fn_sub_589D30_00589d30__recomp(EEContext&);  // recompiled
void fn_sub_589E38_00589e38(EEContext&);  // generated body
void fn_sub_589E38_00589e38__recomp(EEContext&);  // recompiled
void fn_sub_589EC8_00589ec8(EEContext&);  // generated body
void fn_sub_589EC8_00589ec8__recomp(EEContext&);  // recompiled
void fn_sub_589FD0_00589fd0(EEContext&);  // generated body
void fn_sub_589FD0_00589fd0__recomp(EEContext&);  // recompiled
void fn_sub_589FF0_00589ff0(EEContext&);  // generated body
void fn_sub_589FF0_00589ff0__recomp(EEContext&);  // recompiled
void fn_sub_58A038_0058a038(EEContext&);  // generated body
void fn_sub_58A038_0058a038__recomp(EEContext&);  // recompiled
void fn_sub_58AA20_0058aa20(EEContext&);  // generated body
void fn_sub_58AA20_0058aa20__recomp(EEContext&);  // recompiled
void fn_sub_58AB08_0058ab08(EEContext&);  // generated body
void fn_sub_58AB08_0058ab08__recomp(EEContext&);  // recompiled
void fn_sub_58ADA8_0058ada8(EEContext&);  // generated body
void fn_sub_58ADA8_0058ada8__recomp(EEContext&);  // recompiled
void fn_sub_58AE50_0058ae50(EEContext&);  // generated body
void fn_sub_58AE50_0058ae50__recomp(EEContext&);  // recompiled
void fn_sub_58AFA0_0058afa0(EEContext&);  // generated body
void fn_sub_58AFA0_0058afa0__recomp(EEContext&);  // recompiled
void fn_sub_58B168_0058b168(EEContext&);  // generated body
void fn_sub_58B168_0058b168__recomp(EEContext&);  // recompiled
void fn_sub_58B2D0_0058b2d0(EEContext&);  // generated body
void fn_sub_58B2D0_0058b2d0__recomp(EEContext&);  // recompiled
void fn_sub_58BC30_0058bc30(EEContext&);  // generated body
void fn_sub_58BC30_0058bc30__recomp(EEContext&);  // recompiled
void fn_sub_58BC98_0058bc98(EEContext&);  // generated body
void fn_sub_58BC98_0058bc98__recomp(EEContext&);  // recompiled
void fn_atan2l_12_0058c088(EEContext&);  // generated body
void fn_atan2l_12_0058c088__recomp(EEContext&);  // recompiled
void fn_coshl_12_0058c0b8(EEContext&);  // generated body
void fn_coshl_12_0058c0b8__recomp(EEContext&);  // recompiled
void fn___env_lock_12_0058c0f0(EEContext&);  // generated body
void fn___env_lock_12_0058c0f0__recomp(EEContext&);  // recompiled
void fn_sub_58C308_0058c308(EEContext&);  // generated body
void fn_sub_58C308_0058c308__recomp(EEContext&);  // recompiled
void fn_sub_58C378_0058c378(EEContext&);  // generated body
void fn_sub_58C378_0058c378__recomp(EEContext&);  // recompiled
void fn_r_lock_def_get_free_item_6_0058c3a0(EEContext&);  // generated body
void fn_r_lock_def_get_free_item_6_0058c3a0__recomp(EEContext&);  // recompiled
void fn_sub_58C430_0058c430(EEContext&);  // generated body
void fn_sub_58C430_0058c430__recomp(EEContext&);  // recompiled
void fn_sub_58C490_0058c490(EEContext&);  // generated body
void fn_sub_58C490_0058c490__recomp(EEContext&);  // recompiled
void fn_sub_58C588_0058c588(EEContext&);  // generated body
void fn_sub_58C588_0058c588__recomp(EEContext&);  // recompiled
void fn_sub_58C648_0058c648(EEContext&);  // generated body
void fn_sub_58C648_0058c648__recomp(EEContext&);  // recompiled
void fn_sub_58C6B0_0058c6b0(EEContext&);  // generated body
void fn_sub_58C6B0_0058c6b0__recomp(EEContext&);  // recompiled
void fn_sub_58C980_0058c980(EEContext&);  // generated body
void fn_sub_58C980_0058c980__recomp(EEContext&);  // recompiled
void fn_sub_58CB00_0058cb00(EEContext&);  // generated body
void fn_sub_58CB00_0058cb00__recomp(EEContext&);  // recompiled
void fn_sub_58CB28_0058cb28(EEContext&);  // generated body
void fn_sub_58CB28_0058cb28__recomp(EEContext&);  // recompiled
void fn_sub_58CD10_0058cd10(EEContext&);  // generated body
void fn_sub_58CD10_0058cd10__recomp(EEContext&);  // recompiled
void fn_sub_58CE80_0058ce80(EEContext&);  // generated body
void fn_sub_58CE80_0058ce80__recomp(EEContext&);  // recompiled
void fn_sub_58D058_0058d058(EEContext&);  // generated body
void fn_sub_58D058_0058d058__recomp(EEContext&);  // recompiled
void fn_sub_58D0E0_0058d0e0(EEContext&);  // generated body
void fn_sub_58D0E0_0058d0e0__recomp(EEContext&);  // recompiled
void fn_sub_58D180_0058d180(EEContext&);  // generated body
void fn_sub_58D180_0058d180__recomp(EEContext&);  // recompiled
void fn_sub_58D258_0058d258(EEContext&);  // generated body
void fn_sub_58D258_0058d258__recomp(EEContext&);  // recompiled
void fn_sub_58D370_0058d370(EEContext&);  // generated body
void fn_sub_58D370_0058d370__recomp(EEContext&);  // recompiled
void fn_sub_58D378_0058d378(EEContext&);  // generated body
void fn_sub_58D378_0058d378__recomp(EEContext&);  // recompiled
void fn_sub_58D508_0058d508(EEContext&);  // generated body
void fn_sub_58D508_0058d508__recomp(EEContext&);  // recompiled
void fn_sub_58D578_0058d578(EEContext&);  // generated body
void fn_sub_58D578_0058d578__recomp(EEContext&);  // recompiled
void fn_sub_58D600_0058d600(EEContext&);  // generated body
void fn_sub_58D600_0058d600__recomp(EEContext&);  // recompiled
void fn_sub_58D748_0058d748(EEContext&);  // generated body
void fn_sub_58D748_0058d748__recomp(EEContext&);  // recompiled
void fn_sub_58D798_0058d798(EEContext&);  // generated body
void fn_sub_58D798_0058d798__recomp(EEContext&);  // recompiled
void fn_sub_58D800_0058d800(EEContext&);  // generated body
void fn_sub_58D800_0058d800__recomp(EEContext&);  // recompiled
void fn_sub_58D858_0058d858(EEContext&);  // generated body
void fn_sub_58D858_0058d858__recomp(EEContext&);  // recompiled
void fn_sub_58D8E0_0058d8e0(EEContext&);  // generated body
void fn_sub_58D8E0_0058d8e0__recomp(EEContext&);  // recompiled
void fn_sub_58D950_0058d950(EEContext&);  // generated body
void fn_sub_58D950_0058d950__recomp(EEContext&);  // recompiled
void fn_sub_58D9B0_0058d9b0(EEContext&);  // generated body
void fn_sub_58D9B0_0058d9b0__recomp(EEContext&);  // recompiled
void fn_sub_58DA10_0058da10(EEContext&);  // generated body
void fn_sub_58DA10_0058da10__recomp(EEContext&);  // recompiled
void fn_sub_58DB08_0058db08(EEContext&);  // generated body
void fn_sub_58DB08_0058db08__recomp(EEContext&);  // recompiled
void fn_sub_58DBB8_0058dbb8(EEContext&);  // generated body
void fn_sub_58DBB8_0058dbb8__recomp(EEContext&);  // recompiled
void fn_sub_58DC50_0058dc50(EEContext&);  // generated body
void fn_sub_58DC50_0058dc50__recomp(EEContext&);  // recompiled
void fn_sub_58DD00_0058dd00(EEContext&);  // generated body
void fn_sub_58DD00_0058dd00__recomp(EEContext&);  // recompiled
void fn_sub_58DD08_0058dd08(EEContext&);  // generated body
void fn_sub_58DD08_0058dd08__recomp(EEContext&);  // recompiled
void fn_sub_58DDC0_0058ddc0(EEContext&);  // generated body
void fn_sub_58DDC0_0058ddc0__recomp(EEContext&);  // recompiled
void fn_sub_58DE40_0058de40(EEContext&);  // generated body
void fn_sub_58DE40_0058de40__recomp(EEContext&);  // recompiled
void fn_sub_58DF08_0058df08(EEContext&);  // generated body
void fn_sub_58DF08_0058df08__recomp(EEContext&);  // recompiled
void fn_sub_58DFA8_0058dfa8(EEContext&);  // generated body
void fn_sub_58DFA8_0058dfa8__recomp(EEContext&);  // recompiled
void fn_sub_58DFF8_0058dff8(EEContext&);  // generated body
void fn_sub_58DFF8_0058dff8__recomp(EEContext&);  // recompiled
void fn_sub_58E158_0058e158(EEContext&);  // generated body
void fn_sub_58E158_0058e158__recomp(EEContext&);  // recompiled
void fn_sub_58E200_0058e200(EEContext&);  // generated body
void fn_sub_58E200_0058e200__recomp(EEContext&);  // recompiled
void fn_sub_58E310_0058e310(EEContext&);  // generated body
void fn_sub_58E310_0058e310__recomp(EEContext&);  // recompiled
void fn_sub_58E530_0058e530(EEContext&);  // generated body
void fn_sub_58E530_0058e530__recomp(EEContext&);  // recompiled
void fn_sub_58E5E8_0058e5e8(EEContext&);  // generated body
void fn_sub_58E5E8_0058e5e8__recomp(EEContext&);  // recompiled
void fn_sub_58E670_0058e670(EEContext&);  // generated body
void fn_sub_58E670_0058e670__recomp(EEContext&);  // recompiled
void fn_sub_58E958_0058e958(EEContext&);  // generated body
void fn_sub_58E958_0058e958__recomp(EEContext&);  // recompiled
void fn_sub_58EA38_0058ea38(EEContext&);  // generated body
void fn_sub_58EA38_0058ea38__recomp(EEContext&);  // recompiled
void fn_r_lock_def_get_free_item_7_0058ea60(EEContext&);  // generated body
void fn_r_lock_def_get_free_item_7_0058ea60__recomp(EEContext&);  // recompiled
void fn_sub_58EB10_0058eb10(EEContext&);  // generated body
void fn_sub_58EB10_0058eb10__recomp(EEContext&);  // recompiled
void fn_sub_58EB80_0058eb80(EEContext&);  // generated body
void fn_sub_58EB80_0058eb80__recomp(EEContext&);  // recompiled
void fn_sub_58EC20_0058ec20(EEContext&);  // generated body
void fn_sub_58EC20_0058ec20__recomp(EEContext&);  // recompiled
void fn_sub_58EC38_0058ec38(EEContext&);  // generated body
void fn_sub_58EC38_0058ec38__recomp(EEContext&);  // recompiled
void fn_sub_58ECE8_0058ece8(EEContext&);  // generated body
void fn_sub_58ECE8_0058ece8__recomp(EEContext&);  // recompiled
void fn_sub_58ED48_0058ed48(EEContext&);  // generated body
void fn_sub_58ED48_0058ed48__recomp(EEContext&);  // recompiled
void fn_R_LOCK_DEF_w_lock_7_0058edb0(EEContext&);  // generated body
void fn_R_LOCK_DEF_w_lock_7_0058edb0__recomp(EEContext&);  // recompiled
void fn_sub_58EEC0_0058eec0(EEContext&);  // generated body
void fn_sub_58EEC0_0058eec0__recomp(EEContext&);  // recompiled
void fn_sub_58EF48_0058ef48(EEContext&);  // generated body
void fn_sub_58EF48_0058ef48__recomp(EEContext&);  // recompiled
void fn_sub_58EFD8_0058efd8(EEContext&);  // generated body
void fn_sub_58EFD8_0058efd8__recomp(EEContext&);  // recompiled
void fn_sub_58F058_0058f058(EEContext&);  // generated body
void fn_sub_58F058_0058f058__recomp(EEContext&);  // recompiled
void fn_sub_58F298_0058f298(EEContext&);  // generated body
void fn_sub_58F298_0058f298__recomp(EEContext&);  // recompiled
void fn_sub_58F458_0058f458(EEContext&);  // generated body
void fn_sub_58F458_0058f458__recomp(EEContext&);  // recompiled
void fn_sub_58F4C0_0058f4c0(EEContext&);  // generated body
void fn_sub_58F4C0_0058f4c0__recomp(EEContext&);  // recompiled
void fn_sub_58F548_0058f548(EEContext&);  // generated body
void fn_sub_58F548_0058f548__recomp(EEContext&);  // recompiled
void fn_sub_58F6A0_0058f6a0(EEContext&);  // generated body
void fn_sub_58F6A0_0058f6a0__recomp(EEContext&);  // recompiled
void fn_sub_58F808_0058f808(EEContext&);  // generated body
void fn_sub_58F808_0058f808__recomp(EEContext&);  // recompiled
void fn_sub_58FAD8_0058fad8(EEContext&);  // generated body
void fn_sub_58FAD8_0058fad8__recomp(EEContext&);  // recompiled
void fn_sub_58FE08_0058fe08(EEContext&);  // generated body
void fn_sub_58FE08_0058fe08__recomp(EEContext&);  // recompiled
void fn_sub_58FEC8_0058fec8(EEContext&);  // generated body
void fn_sub_58FEC8_0058fec8__recomp(EEContext&);  // recompiled
void fn_sub_58FF10_0058ff10(EEContext&);  // generated body
void fn_sub_58FF10_0058ff10__recomp(EEContext&);  // recompiled
void fn_sub_58FF58_0058ff58(EEContext&);  // generated body
void fn_sub_58FF58_0058ff58__recomp(EEContext&);  // recompiled
void fn_sub_58FF70_0058ff70(EEContext&);  // generated body
void fn_sub_58FF70_0058ff70__recomp(EEContext&);  // recompiled
}  // namespace p3fes::recomp_gen

namespace {

struct Case {
    const char* name;
    u32 addr;
    Fn hand;
    Fn recomp;
};

const Case kCases[] = {
    {"sub_580588", 0x580588, &recomp_gen::fn_sub_580588_00580588, &recomp_gen::fn_sub_580588_00580588__recomp},
    {"sub_580A98", 0x580A98, &recomp_gen::fn_sub_580A98_00580a98, &recomp_gen::fn_sub_580A98_00580a98__recomp},
    {"sub_580C20", 0x580C20, &recomp_gen::fn_sub_580C20_00580c20, &recomp_gen::fn_sub_580C20_00580c20__recomp},
    {"sub_580C38", 0x580C38, &recomp_gen::fn_sub_580C38_00580c38, &recomp_gen::fn_sub_580C38_00580c38__recomp},
    {"sub_580C50", 0x580C50, &recomp_gen::fn_sub_580C50_00580c50, &recomp_gen::fn_sub_580C50_00580c50__recomp},
    {"sub_580C68", 0x580C68, &recomp_gen::fn_sub_580C68_00580c68, &recomp_gen::fn_sub_580C68_00580c68__recomp},
    {"sub_580C98", 0x580C98, &recomp_gen::fn_sub_580C98_00580c98, &recomp_gen::fn_sub_580C98_00580c98__recomp},
    {"sub_581270", 0x581270, &recomp_gen::fn_sub_581270_00581270, &recomp_gen::fn_sub_581270_00581270__recomp},
    {"sub_5812D8", 0x5812D8, &recomp_gen::fn_sub_5812D8_005812d8, &recomp_gen::fn_sub_5812D8_005812d8__recomp},
    {"sub_581628", 0x581628, &recomp_gen::fn_sub_581628_00581628, &recomp_gen::fn_sub_581628_00581628__recomp},
    {"sub_581660", 0x581660, &recomp_gen::fn_sub_581660_00581660, &recomp_gen::fn_sub_581660_00581660__recomp},
    {"_M_numpunct_facet__CQ24_STL8ios_base", 0x5816E0, &recomp_gen::fn__M_numpunct_facet__CQ24_STL8ios_base_005816e0, &recomp_gen::fn__M_numpunct_facet__CQ24_STL8ios_base_005816e0__recomp},
    {"sub_582040", 0x582040, &recomp_gen::fn_sub_582040_00582040, &recomp_gen::fn_sub_582040_00582040__recomp},
    {"sub_582118", 0x582118, &recomp_gen::fn_sub_582118_00582118, &recomp_gen::fn_sub_582118_00582118__recomp},
    {"sub_5827D8", 0x5827D8, &recomp_gen::fn_sub_5827D8_005827d8, &recomp_gen::fn_sub_5827D8_005827d8__recomp},
    {"sub_582968", 0x582968, &recomp_gen::fn_sub_582968_00582968, &recomp_gen::fn_sub_582968_00582968__recomp},
    {"sub_5829B8", 0x5829B8, &recomp_gen::fn_sub_5829B8_005829b8, &recomp_gen::fn_sub_5829B8_005829b8__recomp},
    {"sub_582A58", 0x582A58, &recomp_gen::fn_sub_582A58_00582a58, &recomp_gen::fn_sub_582A58_00582a58__recomp},
    {"sub_582AB8", 0x582AB8, &recomp_gen::fn_sub_582AB8_00582ab8, &recomp_gen::fn_sub_582AB8_00582ab8__recomp},
    {"sub_582B88", 0x582B88, &recomp_gen::fn_sub_582B88_00582b88, &recomp_gen::fn_sub_582B88_00582b88__recomp},
    {"sub_582B98", 0x582B98, &recomp_gen::fn_sub_582B98_00582b98, &recomp_gen::fn_sub_582B98_00582b98__recomp},
    {"sub_582BA8", 0x582BA8, &recomp_gen::fn_sub_582BA8_00582ba8, &recomp_gen::fn_sub_582BA8_00582ba8__recomp},
    {"sub_583058", 0x583058, &recomp_gen::fn_sub_583058_00583058, &recomp_gen::fn_sub_583058_00583058__recomp},
    {"sub_584190", 0x584190, &recomp_gen::fn_sub_584190_00584190, &recomp_gen::fn_sub_584190_00584190__recomp},
    {"sub_584230", 0x584230, &recomp_gen::fn_sub_584230_00584230, &recomp_gen::fn_sub_584230_00584230__recomp},
    {"sub_584290", 0x584290, &recomp_gen::fn_sub_584290_00584290, &recomp_gen::fn_sub_584290_00584290__recomp},
    {"sub_584338", 0x584338, &recomp_gen::fn_sub_584338_00584338, &recomp_gen::fn_sub_584338_00584338__recomp},
    {"sub_584830", 0x584830, &recomp_gen::fn_sub_584830_00584830, &recomp_gen::fn_sub_584830_00584830__recomp},
    {"sub_5849A0", 0x5849A0, &recomp_gen::fn_sub_5849A0_005849a0, &recomp_gen::fn_sub_5849A0_005849a0__recomp},
    {"sceLibgcc32GetErxEntries_19", 0x5851A0, &recomp_gen::fn_sceLibgcc32GetErxEntries_19_005851a0, &recomp_gen::fn_sceLibgcc32GetErxEntries_19_005851a0__recomp},
    {"sub_586490", 0x586490, &recomp_gen::fn_sub_586490_00586490, &recomp_gen::fn_sub_586490_00586490__recomp},
    {"sub_586F20", 0x586F20, &recomp_gen::fn_sub_586F20_00586f20, &recomp_gen::fn_sub_586F20_00586f20__recomp},
    {"sub_587218", 0x587218, &recomp_gen::fn_sub_587218_00587218, &recomp_gen::fn_sub_587218_00587218__recomp},
    {"sub_588720", 0x588720, &recomp_gen::fn_sub_588720_00588720, &recomp_gen::fn_sub_588720_00588720__recomp},
    {"sub_588740", 0x588740, &recomp_gen::fn_sub_588740_00588740, &recomp_gen::fn_sub_588740_00588740__recomp},
    {"sub_588878", 0x588878, &recomp_gen::fn_sub_588878_00588878, &recomp_gen::fn_sub_588878_00588878__recomp},
    {"sub_5888B8", 0x5888B8, &recomp_gen::fn_sub_5888B8_005888b8, &recomp_gen::fn_sub_5888B8_005888b8__recomp},
    {"sub_588978", 0x588978, &recomp_gen::fn_sub_588978_00588978, &recomp_gen::fn_sub_588978_00588978__recomp},
    {"sub_588A10", 0x588A10, &recomp_gen::fn_sub_588A10_00588a10, &recomp_gen::fn_sub_588A10_00588a10__recomp},
    {"sub_588A50", 0x588A50, &recomp_gen::fn_sub_588A50_00588a50, &recomp_gen::fn_sub_588A50_00588a50__recomp},
    {"sub_588AB8", 0x588AB8, &recomp_gen::fn_sub_588AB8_00588ab8, &recomp_gen::fn_sub_588AB8_00588ab8__recomp},
    {"sub_588B70", 0x588B70, &recomp_gen::fn_sub_588B70_00588b70, &recomp_gen::fn_sub_588B70_00588b70__recomp},
    {"sub_588C98", 0x588C98, &recomp_gen::fn_sub_588C98_00588c98, &recomp_gen::fn_sub_588C98_00588c98__recomp},
    {"sub_588CE8", 0x588CE8, &recomp_gen::fn_sub_588CE8_00588ce8, &recomp_gen::fn_sub_588CE8_00588ce8__recomp},
    {"sub_588D38", 0x588D38, &recomp_gen::fn_sub_588D38_00588d38, &recomp_gen::fn_sub_588D38_00588d38__recomp},
    {"sub_588DE0", 0x588DE0, &recomp_gen::fn_sub_588DE0_00588de0, &recomp_gen::fn_sub_588DE0_00588de0__recomp},
    {"sub_588E98", 0x588E98, &recomp_gen::fn_sub_588E98_00588e98, &recomp_gen::fn_sub_588E98_00588e98__recomp},
    {"sub_588F38", 0x588F38, &recomp_gen::fn_sub_588F38_00588f38, &recomp_gen::fn_sub_588F38_00588f38__recomp},
    {"sub_588F90", 0x588F90, &recomp_gen::fn_sub_588F90_00588f90, &recomp_gen::fn_sub_588F90_00588f90__recomp},
    {"sub_589000", 0x589000, &recomp_gen::fn_sub_589000_00589000, &recomp_gen::fn_sub_589000_00589000__recomp},
    {"sub_5890D8", 0x5890D8, &recomp_gen::fn_sub_5890D8_005890d8, &recomp_gen::fn_sub_5890D8_005890d8__recomp},
    {"sub_5892E8", 0x5892E8, &recomp_gen::fn_sub_5892E8_005892e8, &recomp_gen::fn_sub_5892E8_005892e8__recomp},
    {"sub_5893E0", 0x5893E0, &recomp_gen::fn_sub_5893E0_005893e0, &recomp_gen::fn_sub_5893E0_005893e0__recomp},
    {"sub_589438", 0x589438, &recomp_gen::fn_sub_589438_00589438, &recomp_gen::fn_sub_589438_00589438__recomp},
    {"sub_5894A8", 0x5894A8, &recomp_gen::fn_sub_5894A8_005894a8, &recomp_gen::fn_sub_5894A8_005894a8__recomp},
    {"sub_589510", 0x589510, &recomp_gen::fn_sub_589510_00589510, &recomp_gen::fn_sub_589510_00589510__recomp},
    {"sub_589530", 0x589530, &recomp_gen::fn_sub_589530_00589530, &recomp_gen::fn_sub_589530_00589530__recomp},
    {"sub_589550", 0x589550, &recomp_gen::fn_sub_589550_00589550, &recomp_gen::fn_sub_589550_00589550__recomp},
    {"sub_589650", 0x589650, &recomp_gen::fn_sub_589650_00589650, &recomp_gen::fn_sub_589650_00589650__recomp},
    {"sub_589CF0", 0x589CF0, &recomp_gen::fn_sub_589CF0_00589cf0, &recomp_gen::fn_sub_589CF0_00589cf0__recomp},
    {"sub_589D30", 0x589D30, &recomp_gen::fn_sub_589D30_00589d30, &recomp_gen::fn_sub_589D30_00589d30__recomp},
    {"sub_589E38", 0x589E38, &recomp_gen::fn_sub_589E38_00589e38, &recomp_gen::fn_sub_589E38_00589e38__recomp},
    {"sub_589EC8", 0x589EC8, &recomp_gen::fn_sub_589EC8_00589ec8, &recomp_gen::fn_sub_589EC8_00589ec8__recomp},
    {"sub_589FD0", 0x589FD0, &recomp_gen::fn_sub_589FD0_00589fd0, &recomp_gen::fn_sub_589FD0_00589fd0__recomp},
    {"sub_589FF0", 0x589FF0, &recomp_gen::fn_sub_589FF0_00589ff0, &recomp_gen::fn_sub_589FF0_00589ff0__recomp},
    {"sub_58A038", 0x58A038, &recomp_gen::fn_sub_58A038_0058a038, &recomp_gen::fn_sub_58A038_0058a038__recomp},
    {"sub_58AA20", 0x58AA20, &recomp_gen::fn_sub_58AA20_0058aa20, &recomp_gen::fn_sub_58AA20_0058aa20__recomp},
    {"sub_58AB08", 0x58AB08, &recomp_gen::fn_sub_58AB08_0058ab08, &recomp_gen::fn_sub_58AB08_0058ab08__recomp},
    {"sub_58ADA8", 0x58ADA8, &recomp_gen::fn_sub_58ADA8_0058ada8, &recomp_gen::fn_sub_58ADA8_0058ada8__recomp},
    {"sub_58AE50", 0x58AE50, &recomp_gen::fn_sub_58AE50_0058ae50, &recomp_gen::fn_sub_58AE50_0058ae50__recomp},
    {"sub_58AFA0", 0x58AFA0, &recomp_gen::fn_sub_58AFA0_0058afa0, &recomp_gen::fn_sub_58AFA0_0058afa0__recomp},
    {"sub_58B168", 0x58B168, &recomp_gen::fn_sub_58B168_0058b168, &recomp_gen::fn_sub_58B168_0058b168__recomp},
    {"sub_58B2D0", 0x58B2D0, &recomp_gen::fn_sub_58B2D0_0058b2d0, &recomp_gen::fn_sub_58B2D0_0058b2d0__recomp},
    {"sub_58BC30", 0x58BC30, &recomp_gen::fn_sub_58BC30_0058bc30, &recomp_gen::fn_sub_58BC30_0058bc30__recomp},
    {"sub_58BC98", 0x58BC98, &recomp_gen::fn_sub_58BC98_0058bc98, &recomp_gen::fn_sub_58BC98_0058bc98__recomp},
    {"atan2l_12", 0x58C088, &recomp_gen::fn_atan2l_12_0058c088, &recomp_gen::fn_atan2l_12_0058c088__recomp},
    {"coshl_12", 0x58C0B8, &recomp_gen::fn_coshl_12_0058c0b8, &recomp_gen::fn_coshl_12_0058c0b8__recomp},
    {"__env_lock_12", 0x58C0F0, &recomp_gen::fn___env_lock_12_0058c0f0, &recomp_gen::fn___env_lock_12_0058c0f0__recomp},
    {"sub_58C308", 0x58C308, &recomp_gen::fn_sub_58C308_0058c308, &recomp_gen::fn_sub_58C308_0058c308__recomp},
    {"sub_58C378", 0x58C378, &recomp_gen::fn_sub_58C378_0058c378, &recomp_gen::fn_sub_58C378_0058c378__recomp},
    {"r_lock_def_get_free_item_6", 0x58C3A0, &recomp_gen::fn_r_lock_def_get_free_item_6_0058c3a0, &recomp_gen::fn_r_lock_def_get_free_item_6_0058c3a0__recomp},
    {"sub_58C430", 0x58C430, &recomp_gen::fn_sub_58C430_0058c430, &recomp_gen::fn_sub_58C430_0058c430__recomp},
    {"sub_58C490", 0x58C490, &recomp_gen::fn_sub_58C490_0058c490, &recomp_gen::fn_sub_58C490_0058c490__recomp},
    {"sub_58C588", 0x58C588, &recomp_gen::fn_sub_58C588_0058c588, &recomp_gen::fn_sub_58C588_0058c588__recomp},
    {"sub_58C648", 0x58C648, &recomp_gen::fn_sub_58C648_0058c648, &recomp_gen::fn_sub_58C648_0058c648__recomp},
    {"sub_58C6B0", 0x58C6B0, &recomp_gen::fn_sub_58C6B0_0058c6b0, &recomp_gen::fn_sub_58C6B0_0058c6b0__recomp},
    {"sub_58C980", 0x58C980, &recomp_gen::fn_sub_58C980_0058c980, &recomp_gen::fn_sub_58C980_0058c980__recomp},
    {"sub_58CB00", 0x58CB00, &recomp_gen::fn_sub_58CB00_0058cb00, &recomp_gen::fn_sub_58CB00_0058cb00__recomp},
    {"sub_58CB28", 0x58CB28, &recomp_gen::fn_sub_58CB28_0058cb28, &recomp_gen::fn_sub_58CB28_0058cb28__recomp},
    {"sub_58CD10", 0x58CD10, &recomp_gen::fn_sub_58CD10_0058cd10, &recomp_gen::fn_sub_58CD10_0058cd10__recomp},
    {"sub_58CE80", 0x58CE80, &recomp_gen::fn_sub_58CE80_0058ce80, &recomp_gen::fn_sub_58CE80_0058ce80__recomp},
    {"sub_58D058", 0x58D058, &recomp_gen::fn_sub_58D058_0058d058, &recomp_gen::fn_sub_58D058_0058d058__recomp},
    {"sub_58D0E0", 0x58D0E0, &recomp_gen::fn_sub_58D0E0_0058d0e0, &recomp_gen::fn_sub_58D0E0_0058d0e0__recomp},
    {"sub_58D180", 0x58D180, &recomp_gen::fn_sub_58D180_0058d180, &recomp_gen::fn_sub_58D180_0058d180__recomp},
    {"sub_58D258", 0x58D258, &recomp_gen::fn_sub_58D258_0058d258, &recomp_gen::fn_sub_58D258_0058d258__recomp},
    {"sub_58D370", 0x58D370, &recomp_gen::fn_sub_58D370_0058d370, &recomp_gen::fn_sub_58D370_0058d370__recomp},
    {"sub_58D378", 0x58D378, &recomp_gen::fn_sub_58D378_0058d378, &recomp_gen::fn_sub_58D378_0058d378__recomp},
    {"sub_58D508", 0x58D508, &recomp_gen::fn_sub_58D508_0058d508, &recomp_gen::fn_sub_58D508_0058d508__recomp},
    {"sub_58D578", 0x58D578, &recomp_gen::fn_sub_58D578_0058d578, &recomp_gen::fn_sub_58D578_0058d578__recomp},
    {"sub_58D600", 0x58D600, &recomp_gen::fn_sub_58D600_0058d600, &recomp_gen::fn_sub_58D600_0058d600__recomp},
    {"sub_58D748", 0x58D748, &recomp_gen::fn_sub_58D748_0058d748, &recomp_gen::fn_sub_58D748_0058d748__recomp},
    {"sub_58D798", 0x58D798, &recomp_gen::fn_sub_58D798_0058d798, &recomp_gen::fn_sub_58D798_0058d798__recomp},
    {"sub_58D800", 0x58D800, &recomp_gen::fn_sub_58D800_0058d800, &recomp_gen::fn_sub_58D800_0058d800__recomp},
    {"sub_58D858", 0x58D858, &recomp_gen::fn_sub_58D858_0058d858, &recomp_gen::fn_sub_58D858_0058d858__recomp},
    {"sub_58D8E0", 0x58D8E0, &recomp_gen::fn_sub_58D8E0_0058d8e0, &recomp_gen::fn_sub_58D8E0_0058d8e0__recomp},
    {"sub_58D950", 0x58D950, &recomp_gen::fn_sub_58D950_0058d950, &recomp_gen::fn_sub_58D950_0058d950__recomp},
    {"sub_58D9B0", 0x58D9B0, &recomp_gen::fn_sub_58D9B0_0058d9b0, &recomp_gen::fn_sub_58D9B0_0058d9b0__recomp},
    {"sub_58DA10", 0x58DA10, &recomp_gen::fn_sub_58DA10_0058da10, &recomp_gen::fn_sub_58DA10_0058da10__recomp},
    {"sub_58DB08", 0x58DB08, &recomp_gen::fn_sub_58DB08_0058db08, &recomp_gen::fn_sub_58DB08_0058db08__recomp},
    {"sub_58DBB8", 0x58DBB8, &recomp_gen::fn_sub_58DBB8_0058dbb8, &recomp_gen::fn_sub_58DBB8_0058dbb8__recomp},
    {"sub_58DC50", 0x58DC50, &recomp_gen::fn_sub_58DC50_0058dc50, &recomp_gen::fn_sub_58DC50_0058dc50__recomp},
    {"sub_58DD00", 0x58DD00, &recomp_gen::fn_sub_58DD00_0058dd00, &recomp_gen::fn_sub_58DD00_0058dd00__recomp},
    {"sub_58DD08", 0x58DD08, &recomp_gen::fn_sub_58DD08_0058dd08, &recomp_gen::fn_sub_58DD08_0058dd08__recomp},
    {"sub_58DDC0", 0x58DDC0, &recomp_gen::fn_sub_58DDC0_0058ddc0, &recomp_gen::fn_sub_58DDC0_0058ddc0__recomp},
    {"sub_58DE40", 0x58DE40, &recomp_gen::fn_sub_58DE40_0058de40, &recomp_gen::fn_sub_58DE40_0058de40__recomp},
    {"sub_58DF08", 0x58DF08, &recomp_gen::fn_sub_58DF08_0058df08, &recomp_gen::fn_sub_58DF08_0058df08__recomp},
    {"sub_58DFA8", 0x58DFA8, &recomp_gen::fn_sub_58DFA8_0058dfa8, &recomp_gen::fn_sub_58DFA8_0058dfa8__recomp},
    {"sub_58DFF8", 0x58DFF8, &recomp_gen::fn_sub_58DFF8_0058dff8, &recomp_gen::fn_sub_58DFF8_0058dff8__recomp},
    {"sub_58E158", 0x58E158, &recomp_gen::fn_sub_58E158_0058e158, &recomp_gen::fn_sub_58E158_0058e158__recomp},
    {"sub_58E200", 0x58E200, &recomp_gen::fn_sub_58E200_0058e200, &recomp_gen::fn_sub_58E200_0058e200__recomp},
    {"sub_58E310", 0x58E310, &recomp_gen::fn_sub_58E310_0058e310, &recomp_gen::fn_sub_58E310_0058e310__recomp},
    {"sub_58E530", 0x58E530, &recomp_gen::fn_sub_58E530_0058e530, &recomp_gen::fn_sub_58E530_0058e530__recomp},
    {"sub_58E5E8", 0x58E5E8, &recomp_gen::fn_sub_58E5E8_0058e5e8, &recomp_gen::fn_sub_58E5E8_0058e5e8__recomp},
    {"sub_58E670", 0x58E670, &recomp_gen::fn_sub_58E670_0058e670, &recomp_gen::fn_sub_58E670_0058e670__recomp},
    {"sub_58E958", 0x58E958, &recomp_gen::fn_sub_58E958_0058e958, &recomp_gen::fn_sub_58E958_0058e958__recomp},
    {"sub_58EA38", 0x58EA38, &recomp_gen::fn_sub_58EA38_0058ea38, &recomp_gen::fn_sub_58EA38_0058ea38__recomp},
    {"r_lock_def_get_free_item_7", 0x58EA60, &recomp_gen::fn_r_lock_def_get_free_item_7_0058ea60, &recomp_gen::fn_r_lock_def_get_free_item_7_0058ea60__recomp},
    {"sub_58EB10", 0x58EB10, &recomp_gen::fn_sub_58EB10_0058eb10, &recomp_gen::fn_sub_58EB10_0058eb10__recomp},
    {"sub_58EB80", 0x58EB80, &recomp_gen::fn_sub_58EB80_0058eb80, &recomp_gen::fn_sub_58EB80_0058eb80__recomp},
    {"sub_58EC20", 0x58EC20, &recomp_gen::fn_sub_58EC20_0058ec20, &recomp_gen::fn_sub_58EC20_0058ec20__recomp},
    {"sub_58EC38", 0x58EC38, &recomp_gen::fn_sub_58EC38_0058ec38, &recomp_gen::fn_sub_58EC38_0058ec38__recomp},
    {"sub_58ECE8", 0x58ECE8, &recomp_gen::fn_sub_58ECE8_0058ece8, &recomp_gen::fn_sub_58ECE8_0058ece8__recomp},
    {"sub_58ED48", 0x58ED48, &recomp_gen::fn_sub_58ED48_0058ed48, &recomp_gen::fn_sub_58ED48_0058ed48__recomp},
    {"R_LOCK_DEF_w_lock_7", 0x58EDB0, &recomp_gen::fn_R_LOCK_DEF_w_lock_7_0058edb0, &recomp_gen::fn_R_LOCK_DEF_w_lock_7_0058edb0__recomp},
    {"sub_58EEC0", 0x58EEC0, &recomp_gen::fn_sub_58EEC0_0058eec0, &recomp_gen::fn_sub_58EEC0_0058eec0__recomp},
    {"sub_58EF48", 0x58EF48, &recomp_gen::fn_sub_58EF48_0058ef48, &recomp_gen::fn_sub_58EF48_0058ef48__recomp},
    {"sub_58EFD8", 0x58EFD8, &recomp_gen::fn_sub_58EFD8_0058efd8, &recomp_gen::fn_sub_58EFD8_0058efd8__recomp},
    {"sub_58F058", 0x58F058, &recomp_gen::fn_sub_58F058_0058f058, &recomp_gen::fn_sub_58F058_0058f058__recomp},
    {"sub_58F298", 0x58F298, &recomp_gen::fn_sub_58F298_0058f298, &recomp_gen::fn_sub_58F298_0058f298__recomp},
    {"sub_58F458", 0x58F458, &recomp_gen::fn_sub_58F458_0058f458, &recomp_gen::fn_sub_58F458_0058f458__recomp},
    {"sub_58F4C0", 0x58F4C0, &recomp_gen::fn_sub_58F4C0_0058f4c0, &recomp_gen::fn_sub_58F4C0_0058f4c0__recomp},
    {"sub_58F548", 0x58F548, &recomp_gen::fn_sub_58F548_0058f548, &recomp_gen::fn_sub_58F548_0058f548__recomp},
    {"sub_58F6A0", 0x58F6A0, &recomp_gen::fn_sub_58F6A0_0058f6a0, &recomp_gen::fn_sub_58F6A0_0058f6a0__recomp},
    {"sub_58F808", 0x58F808, &recomp_gen::fn_sub_58F808_0058f808, &recomp_gen::fn_sub_58F808_0058f808__recomp},
    {"sub_58FAD8", 0x58FAD8, &recomp_gen::fn_sub_58FAD8_0058fad8, &recomp_gen::fn_sub_58FAD8_0058fad8__recomp},
    {"sub_58FE08", 0x58FE08, &recomp_gen::fn_sub_58FE08_0058fe08, &recomp_gen::fn_sub_58FE08_0058fe08__recomp},
    {"sub_58FEC8", 0x58FEC8, &recomp_gen::fn_sub_58FEC8_0058fec8, &recomp_gen::fn_sub_58FEC8_0058fec8__recomp},
    {"sub_58FF10", 0x58FF10, &recomp_gen::fn_sub_58FF10_0058ff10, &recomp_gen::fn_sub_58FF10_0058ff10__recomp},
    {"sub_58FF58", 0x58FF58, &recomp_gen::fn_sub_58FF58_0058ff58, &recomp_gen::fn_sub_58FF58_0058ff58__recomp},
    {"sub_58FF70", 0x58FF70, &recomp_gen::fn_sub_58FF70_0058ff70, &recomp_gen::fn_sub_58FF70_0058ff70__recomp},
};

// ---- the world --------------------------------------------------------------------------------------------------
constexpr u32 kWorld = 0x01810000u;      // free RAM for random worlds and built records
constexpr u32 kWorldSize = 0x10000u;
constexpr u32 kSeeds = 24;
constexpr u32 kOut = 0x01820000u;        // out-parameter / built-record area (16 KiB)
constexpr u32 kPlayers = 0x7B2FBCu;      // MWSFD's 8 players (MWSFD work 0x7B2F50 + 108; libs5::ply)
constexpr u32 kPlySize = 684;
constexpr const char* kMovieSnap = "libs5_movie_860";  // the dorm route at vblank 860: the boot movie playing
namespace stm = game::libs12::stm;

const Case& by_addr(u32 a) {
    for (const Case& c : kCases)
        if (c.addr == a) return c;
    throw std::runtime_error("libs12: no case for an address");
}
u32 r32(Machine& m, u32 va) { u32 v; std::memcpy(&v, m.at(va), 4); return v; }
void w32(Machine& m, u32 va, u32 v) { std::memcpy(m.at(va), &v, 4); }

std::unique_ptr<Machine> machine() {
    auto m = std::make_unique<Machine>();
    if (const char* err = m->load_elf(elf_path())) {
        MESSAGE("SKIP: " << err);
        return nullptr;
    }
    return m;
}
std::vector<u8> snapshot(const char* dir) {
    std::vector<u8> snap = read_snapshot(dir);
    if (snap.size() != EEMemory::kMainRamSize) {
        MESSAGE("SKIP: snapshot " << dir << " not found");
        snap.clear();
    }
    return snap;
}
void restore(Machine& m, const std::vector<u8>& snap) { std::memcpy(m.mem.main_ram(), snap.data(), snap.size()); }

// ---- the stand-ins: the callees of this slice the test binary does not emit -------------------------------------
// Only the slice's own callees, and none another current packet claims (those stay recompiled and a pair stops there,
// identically). Recorders without scratch clobbering (both bodies are served alike; the runner compares the whole
// register file at each callee's entry check point, i.e. the call's arguments), returning `g_v0`. The stream flag
// accessors are served with their real effect on the SFD handle's stream records (stm::kInEnd / stm::kOutEnd), so
// the demux and video servers take their real paths on a live handle.
const u32 kRecorders[] = {
    0x53DD10u, 0x55D668u, 0x575410u, 0x575880u, 0x57C730u, 0x5840D0u, 0x585590u, 0x586FE0u, 0x588168u, 0x5881F8u,
    0x588270u, 0x5882F0u, 0x589018u, 0x5890F0u, 0x5895F0u, 0x589D80u, 0x589F38u, 0x589F70u, 0x58ABA0u, 0x58AF20u,
    0x58B398u, 0x58C100u, 0x58C118u, 0x58CA60u, 0x58CAA0u, 0x58CCA0u, 0x58D300u, 0x58D5E8u, 0x58EFB8u, 0x58FB28u,
    0x58FBE0u, 0x591B18u, 0x595208u, 0x599418u, 0x5994F0u, 0x59B4F0u, 0x59FA38u, 0x59FDB8u, 0x59FEF8u, 0x5A1380u};
constexpr u32 kStmSetInEnd = 0x589CB0u, kStmInEnd = 0x589CD0u, kStmOutEnd = 0x589D10u;
constexpr u32 kErr = 0x585590u;
u64 g_v0 = 0;
bool in_ram(u64 a) { return a < 0x01FFFF00u; }
u64 stm_word(u64 sfd, u64 n, s32 field) { return sfd + stm::kBase + stm::kStride * (n & 0xFF) + field; }
void install_drivers(StandIns& s) {
    s.clobber_scratch = false;
    for (u32 va : kRecorders) s.install_recorder(va, "driver", g_v0, 3);
    s.install(kStmInEnd, "stream_in_end", [](EEContext& ctx, StandIns&, StandInCall& c) {
        const u64 a = stm_word(c.args[0], c.args[1], stm::kInEnd);
        c.v0 = in_ram(a) ? sx(ctx.memory->read<u32>(static_cast<u32>(a))) : 0;
    }, 3);
    s.install(kStmOutEnd, "stream_out_end", [](EEContext& ctx, StandIns&, StandInCall& c) {
        const u64 a = stm_word(c.args[0], c.args[1], stm::kOutEnd);
        c.v0 = in_ram(a) ? sx(ctx.memory->read<u32>(static_cast<u32>(a))) : 0;
    }, 3);
    s.install(kStmSetInEnd, "stream_set_in_end", [](EEContext& ctx, StandIns&, StandInCall& c) {
        const u64 a = stm_word(c.args[0], c.args[1], stm::kInEnd);
        if (in_ram(a)) ctx.memory->write<u32>(static_cast<u32>(a), static_cast<u32>(c.args[2]));
        c.v0 = stm::kStride * (c.args[1] & 0xFF);
    }, 3);
}

// Each body runs with its own stand-in set (a thunk installs it around the body); the two call logs must be equal.
StandIns* g_si[2] = {nullptr, nullptr};
Fn g_fn[2] = {nullptr, nullptr};
void thunk0(EEContext& ctx) {
    StandInsScope s(*g_si[0]);
    g_fn[0](ctx);
}
void thunk1(EEContext& ctx) {
    StandInsScope s(*g_si[1]);
    g_fn[1](ctx);
}
void same_log(const StandIns& a, const StandIns& b, const char* what) {
    INFO(what);
    CHECK(a.log.size() == b.log.size());
    for (std::size_t i = 0; i < std::min(a.log.size(), b.log.size()); ++i) {
        if (!(a.log[i] == b.log[i])) {
            INFO("stand-in call " << i << " differs (callee " << std::hex << a.log[i].va << " / " << b.log[i].va << ")");
            CHECK(false);
            break;
        }
    }
}

std::map<std::string, int> g_pairs;
u32 g_seed = 1;
// One pair from the machine's current state (the recompiled run's memory stays), with the drivers stood in; `log`
// receives the hand body's call log.
hgp::Run pr(Machine& m, u32 addr, Args a, std::map<unsigned, u64> t = {}, StandIns* log = nullptr) {
    const Case& c = by_addr(addr);
    StandIns sh, sr;
    install_drivers(sh);
    install_drivers(sr);
    g_si[0] = &sh;
    g_si[1] = &sr;
    g_fn[0] = c.hand;
    g_fn[1] = c.recomp;
    HwCheck hw;
    hw.gpr_in = std::move(t);
    ++g_pairs[c.name];
    hgp::Run r = hgp::pair(m, &thunk0, &thunk1, a, g_seed++, c.name, hw);
    same_log(sh, sr, c.name);
    if (log) log->log = sh.log;
    return r;
}
// The same comparison on a long-lived BaseRange (write_tracker.h): the snapshot's 32 MiB stay the base and restore()
// copies back only the pages a pair wrote (instead of a 32 MiB copy per pair).
hgp::Run pr_base(Machine& m, BaseRange& ram, u32 addr, const Args& args, const HwCheck& hw) {
    const Case& c = by_addr(addr);
    StandIns sh, sr;
    install_drivers(sh);
    install_drivers(sr);
    g_si[0] = &sh;
    g_si[1] = &sr;
    g_fn[0] = c.hand;
    g_fn[1] = c.recomp;
    ++g_pairs[c.name];
    const u32 seed = g_seed++;
    const std::vector<u8> spr(m.mem.scratchpad(), m.mem.scratchpad() + 0x4000);
    ram.begin();
    hgp::Run h = hgp::run_one(m, &thunk0, args, seed, hw);
    std::vector<u8> bios_h;
    if (!hgp::bios_clean(m)) {
        bios_h.assign(m.mem.bios(), m.mem.bios() + EEMemory::kBiosSize);
        std::memset(m.mem.bios(), 0, EEMemory::kBiosSize);
    }
    ram.between();
    std::memcpy(m.mem.scratchpad(), spr.data(), spr.size());
    hgp::Run r = hgp::run_one(m, &thunk1, args, seed, hw);
    const bool bios_r = !hgp::bios_clean(m);
    INFO(c.name << " a0=" << std::hex << args[0] << " a1=" << args[1] << " a2=" << args[2] << " a3=" << args[3] << std::dec
                << " seed=" << seed << (r.stopped ? " (recomp stopped: " + r.what + ")" : std::string()));
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
        INFO("main RAM: first differing byte at " << std::hex << first);
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
    same_log(sh, sr, c.name);
    return r;
}
u64 v0of(const hgp::Run& r) { return r.end.gpr[GPR_V0].u64[0]; }
u64 prv(Machine& m, u32 addr, Args a, StandIns* log = nullptr) {
    const hgp::Run r = pr(m, addr, a, {}, log);
    INFO(by_addr(addr).name);
    CHECK_FALSE(r.stopped);
    return v0of(r);
}
bool called(const StandIns& log, u32 va) {
    return std::any_of(log.log.begin(), log.log.end(), [&](const auto& e) { return e.va == va; });
}

// What $a0 is for each function: the snapshot sweep's argument recipe.
enum class Arg { None, Ply, Sfd, Buf };
Arg arg_of(u32 a) {
    switch (a) {
    case 0x580588u: case 0x580A98u: case 0x580C20u: case 0x580C38u: case 0x580C50u: case 0x580C68u: case 0x581270u:
    case 0x5812D8u: case 0x581628u: case 0x581660u: case 0x5816E0u: case 0x582040u: case 0x582118u: case 0x583058u:
    case 0x584190u: case 0x584230u: case 0x584290u: case 0x584338u: case 0x584830u: case 0x582BA8u:
        return Arg::Ply;
    // records, buffers and SJ objects rather than an SFD handle
    case 0x588878u: case 0x588978u: case 0x588CE8u: case 0x588DE0u: case 0x588E98u: case 0x588F38u: case 0x5892E8u:
    case 0x5893E0u: case 0x589E38u: case 0x589EC8u: case 0x58AA20u: case 0x58AB08u: case 0x58ADA8u: case 0x58AE50u:
    case 0x58AFA0u: case 0x58BC30u: case 0x58BC98u: case 0x58C308u: case 0x58D258u: case 0x58E310u: case 0x58E958u:
    case 0x58F298u: case 0x58F458u: case 0x58F548u: case 0x58F6A0u:
        return Arg::Buf;
    default:
        break;
    }
    if (a >= 0x586F20u) return Arg::Sfd;
    return Arg::None;
}

}  // namespace

TEST_CASE("game(libs12): every body equals its recompiled body on random worlds") {
    auto m = machine();
    if (!m) return;
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
            const u64 a0 = hgp::random_arg(rng, kWorld, kWorldSize);
            const u64 a1 = hgp::random_arg(rng, kWorld, kWorldSize);
            const u64 a2 = hgp::random_arg(rng, kWorld, kWorldSize);
            const u64 a3 = hgp::random_arg(rng, kWorld, kWorldSize);
            g_v0 = seed & 3;  // the stood-in callees answer 0..3
            stops += pr(*m, c.addr, Args{a0, a1, a2, a3}).stopped ? 1 : 0;
            ++total;
        }
    }
    g_v0 = 0;
    MESSAGE(total << " pairs, " << stops << " stopped early (identically)");
}

// The boot movie's snapshot (dorm route, vblank 860) holds a live MWSFD player (#0, playing) with its SFD handle --
// its stream records, transfer slots, demux record and video decoder record -- and SJs; the dorm snapshot an
// initialised MWSFD with no player. Every function runs on them with the record its role takes (the live player, a
// free player, null; the SFD handle; an SJ, the handle or a free area for the buffer functions), second arguments
// from the stream indices and values its branches test, and the stood-in callees returning 0, 1 or -1; each pair
// starts from the snapshot.
TEST_CASE("game(libs12): every body on the live movie player, its SFD handle and the dorm MWSFD") {
    auto m = machine();
    if (!m) return;
    const char* only = std::getenv("P3FES_HG_ONLY");
    const bool trace = std::getenv("P3FES_HG_TRACE") != nullptr;
    int runs = 0, stops = 0;
    for (const char* dir : {kMovieSnap, "dorm_replay_4900"}) {
        const std::vector<u8> snap = snapshot(dir);
        if (snap.empty()) continue;
        restore(*m, snap);
        const u32 live = kPlayers;
        const u32 sfd = r32(*m, live + 60);
        const u32 sj = r32(*m, live + 444) ? r32(*m, live + 444) : r32(*m, live + 448);
        if (std::string(dir) == kMovieSnap) {
            REQUIRE(r32(*m, live) == 1u);      // in use
            REQUIRE(r32(*m, live + 4) == 2u);  // playing
            REQUIRE(sfd != 0u);
        }
        BaseRange base(m->mem.main_ram(), m->mem.main_ram() + EEMemory::kMainRamSize);
        for (const Case& c : kCases) {
            if (only && std::string(only) != c.name) continue;
            std::vector<u64> a0s;
            switch (arg_of(c.addr)) {
            case Arg::Ply: a0s = {live, live + kPlySize, 0}; break;
            case Arg::Sfd: a0s = {sfd ? sfd : kWorld}; break;
            case Arg::Buf: a0s = {sj ? sj : kOut, sfd ? sfd : kWorld, kOut}; break;
            case Arg::None: a0s = {0, 1, kOut}; break;
            }
            for (u64 a0 : a0s)
                for (u64 a1 : {0ull, 1ull, 2ull, 3ull, ~0ull})
                    for (u64 v : {0ull, 1ull, ~0ull}) {
                        g_v0 = v;
                        if (trace) std::fprintf(stderr, "%s %s a0 %llx a1 %llx v0 %llx\n", dir, c.name,
                                                (unsigned long long)a0, (unsigned long long)a1, (unsigned long long)v);
                        HwCheck hw;
                        hw.gpr_in = {{GPR_T0, kOut + 0x200}};
                        const hgp::Run r = pr_base(*m, base, c.addr, Args{a0, a1, kOut, kOut + 0x100}, hw);
                        base.restore();
                        ++runs;
                        stops += r.stopped ? 1 : 0;
                    }
        }
    }
    g_v0 = 0;
    MESSAGE(runs << " pairs from the snapshots, " << stops << " stopped identically");
}

// MWSFD's fixed sizes, the running offsets of the stream layout, the plane record, the 8-entry table lookup with
// C's truncating modulo, the two-part chunk offset and the buffer-format check.
TEST_CASE("game(libs12): the fixed sizes, the layout offsets and the small record helpers") {
    auto m = machine();
    if (!m) return;
    std::memset(m->at(kOut), 0, 0x400);
    CHECK(prv(*m, 0x5849A0u, {kOut, kOut + 4, kOut + 8, 0}) == 149988u + 40000u + 2048u);
    CHECK(r32(*m, kOut) == 149988u);
    CHECK(r32(*m, kOut + 4) == 40000u);
    CHECK(r32(*m, kOut + 8) == 2048u);

    const u32 sizes[8] = {0x100, 0x2000, 0, 0x40, 0x800, 0x10, 0x3000, 0x4};
    for (u32 i = 0; i < 8; ++i) w32(*m, kOut + 0x40 + 4 * i, sizes[i]);
    prv(*m, 0x588878u, {kOut, kOut + 0x40, 0x100000u, 0});
    u32 at = 0x100000u;
    for (u32 i = 0; i < 8; ++i) {
        CHECK(r32(*m, kOut + 4 * i) == at);
        at += sizes[i];
    }

    prv(*m, 0x582B98u, {kOut + 0x80, 0x1234u, 0x5678u, 0x9ABCu});
    CHECK(r32(*m, kOut + 0x80) == 0x1234u);
    CHECK(r32(*m, kOut + 0x84) == 0x5678u);
    CHECK(r32(*m, kOut + 0x88) == 0x9ABCu);

    // table of 20-byte entries at $a0 + 192: entry n mod 8 (truncating), its word 2 when its word 0 is 1
    std::memset(m->at(kOut), 0, 0x400);
    const u32 tab = kOut + 0x100;
    w32(*m, tab + 192 + 20 * 5, 1);
    w32(*m, tab + 192 + 20 * 5 + 8, 0x77);
    w32(*m, tab + 192 + 20 * 6 + 8, 0x66);  // word 0 not 1: not taken
    w32(*m, tab + 192 - 20 * 3, 1);         // n = -3 stays -3 (truncating modulo)
    w32(*m, tab + 192 - 20 * 3 + 8, 0x99);
    CHECK(prv(*m, 0x5829B8u, {tab, 5, 0, 0}) == 0x77u);
    CHECK(prv(*m, 0x5829B8u, {tab, 13, 0, 0}) == 0x77u);
    CHECK(prv(*m, 0x5829B8u, {tab, 6, 0, 0}) == 0u);
    CHECK(prv(*m, 0x5829B8u, {tab, ~2ull, 0, 0}) == 0x99u);

    // offset inside the two-part chunk {addr0, len0, addr1, len1}
    w32(*m, kOut, 0x1000);
    w32(*m, kOut + 4, 0x100);
    w32(*m, kOut + 8, 0x5000);
    w32(*m, kOut + 12, 0x80);
    CHECK(prv(*m, 0x58F458u, {kOut, 0x1010, 0, 0}) == 0x10u);
    CHECK(prv(*m, 0x58F458u, {kOut, 0x10FF, 0, 0}) == 0xFFu);
    CHECK(prv(*m, 0x58F458u, {kOut, 0x5004, 0, 0}) == 0x104u);
    CHECK(prv(*m, 0x58F458u, {kOut, 0x1100, 0, 0}) == 0u);
    CHECK(prv(*m, 0x58F458u, {kOut, 0x5080, 0, 0}) == 0u);

    // MwsfdBufFmt: 1, 2 and 3 pass; anything else reports E201184
    for (u64 f : {1ull, 2ull, 3ull}) {
        StandIns log;
        CHECK(prv(*m, 0x582A58u, {f, 0, 0, 0}, &log) == f);
        CHECK_FALSE(called(log, kErr));
    }
    for (u64 f : {0ull, 4ull, 9ull}) {
        StandIns log;
        prv(*m, 0x582A58u, {f, 0, 0, 0}, &log);
        CHECK(called(log, kErr));
    }
}

// The live handle: the stream record accessors read and write the 116-byte records at +4880; the player accessors
// read the live player and report a bad handle.
TEST_CASE("game(libs12): the stream record accessors and the player getters on the live movie handle") {
    auto m = machine();
    if (!m) return;
    const std::vector<u8> snap = snapshot(kMovieSnap);
    if (snap.empty()) return;
    restore(*m, snap);
    const u32 live = kPlayers;
    const u32 sfd = r32(*m, live + 60);
    REQUIRE(sfd != 0u);
    for (u32 n = 0; n < 4; ++n) {
        const u32 rec = sfd + stm::kBase + stm::kStride * n;
        CHECK(prv(*m, 0x589510u, {sfd, n, 0, 0}) == static_cast<u64>(sx(r32(*m, rec + stm::kBufSize))));
        CHECK(prv(*m, 0x589530u, {sfd, n, 0, 0}) == static_cast<u64>(sx(r32(*m, rec + stm::kCount))));
        prv(*m, 0x589CF0u, {sfd, n, 0x5A + n, 0});
        CHECK(r32(*m, rec + stm::kOutEnd) == 0x5A + n);
        const u32 count = r32(*m, rec + stm::kCount);
        prv(*m, 0x589650u, {sfd, n, 0x30, 0});
        CHECK(r32(*m, rec + stm::kCount) == (static_cast<s32>(count) >= 0 ? count + 0x30 : count));
        CHECK(prv(*m, 0x58CB00u, {sfd, 0, 0, 0}) ==
              sfd + 4896u + stm::kStride * r32(*m, sfd + game::libs12::trn::kDemuxIn));
    }
    // a negative count is left alone
    const u32 rec0 = sfd + stm::kBase;
    w32(*m, rec0 + stm::kCount, 0xFFFFFFFFu);
    prv(*m, 0x589650u, {sfd, 0, 0x30, 0});
    CHECK(r32(*m, rec0 + stm::kCount) == 0xFFFFFFFFu);

    CHECK(prv(*m, 0x5816E0u, {live, 0, 0, 0}) == static_cast<u64>(sx(r32(*m, live + 64))));
    {
        StandIns log;
        CHECK(prv(*m, 0x582118u, {live, 0, 0, 0}, &log) == static_cast<u64>(sx(r32(*m, live + 448))));
        CHECK_FALSE(called(log, kErr));
    }
    {
        StandIns log;
        prv(*m, 0x582118u, {live + kPlySize, 0, 0, 0}, &log);  // a free player: a bad handle
        CHECK(called(log, kErr));
    }
    // the link byte: linking an unlinked player asks SFD (sub_589F70); unlinking a linked one requests termination
    restore(*m, snap);
    m->at(live + 112)[0] = 0;
    g_v0 = 0;
    {
        StandIns log;
        prv(*m, 0x584830u, {live, 1, 0, 0}, &log);
        CHECK(called(log, 0x589F70u));
        CHECK_FALSE(called(log, kErr));
        CHECK(m->at(live + 112)[0] == 1);
    }
    m->at(live + 113)[0] = 0;
    prv(*m, 0x584830u, {live, 0, 0, 0});
    CHECK(m->at(live + 112)[0] == 0);
    CHECK(m->at(live + 113)[0] == 1);
    g_v0 = 0;
    MESSAGE("libs12 pairs: " << g_pairs.size() << " functions");
}

#else

TEST_CASE("game(libs12): no recompiled code in this build") { MESSAGE("SKIP: built without P3FES_RT_EXEC_ELF"); }

#endif
