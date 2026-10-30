// Phase 5 slice libs22: CRI middleware 0x5838C0-0x58ACF0 (MWSFD player wrappers, the audio slave, SVM thunks, ADXSTM
// slots, the ADX stream input control, the SFD PCM ring and the MPEG audio header helpers; game/include/p3fes/game/
// libs22.h). Written from p3fes_handgen's faithful bodies (SLUS_216.21, symbols/): every body keeps the recompiled
// body's registers, frame, spills, $ra links, cycle charges and check points (hg_cpu.h); the slice adds a role comment
// per function and named offsets (l22::, l15::). tests/game/test_libs22.cpp pairs each body with its recompiled body.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs15.h"
#include "p3fes/game/libs22.h"

namespace p3fes::recomp_gen {
void fn_R_LOCK_DEF_add_4_005866a8(p3fes::EEContext&);
void fn_R_LOCK_DEF_add_4_005866a8_at_005866bc(p3fes::EEContext&);
void fn_R_LOCK_DEF_ctx_new_5_00587dc0(p3fes::EEContext&);
void fn_R_LOCK_DEF_lock_free_4_005865c0(p3fes::EEContext&);
void fn_R_LOCK_DEF_lock_new_5_00587f00_at_00587f50(p3fes::EEContext&);
void fn_WTLS_get_table_1_005851b0(p3fes::EEContext&);
void fn_WTLS_get_table_2_0059fd60(p3fes::EEContext&);
void fn_WTLS_set_table_1_005851c0(p3fes::EEContext&);
void fn__M_numpunct_facet__CQ24_STL8ios_base_005816e0(p3fes::EEContext&);
void fn___gthread_get_ee_key_use_0057f740(p3fes::EEContext&);
void fn__get_peer_or_sock_name_0_005843e8(p3fes::EEContext&);
void fn_coshl_11_00585498(p3fes::EEContext&);
void fn_ctime_00586298(p3fes::EEContext&);
void fn_hypotl_11_00585508(p3fes::EEContext&);
void fn_powl_11_00585640(p3fes::EEContext&);
void fn_r_lock_def_free_4_005863d8(p3fes::EEContext&);
void fn_r_lock_def_get_free_item_3_00585c90(p3fes::EEContext&);
void fn_rdbuf__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_0_005861f8(p3fes::EEContext&);
void fn_sinhl_11_00585670(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_sub_53EC20_0053ec20(p3fes::EEContext&);
void fn_sub_53ED00_0053ed00(p3fes::EEContext&);
void fn_sub_540570_00540570(p3fes::EEContext&);
void fn_sub_541D00_00541d00(p3fes::EEContext&);
void fn_sub_5460E0_005460e0(p3fes::EEContext&);
void fn_sub_546270_00546270(p3fes::EEContext&);
void fn_sub_5462E0_005462e0(p3fes::EEContext&);
void fn_sub_5463A8_005463a8(p3fes::EEContext&);
void fn_sub_546410_00546410(p3fes::EEContext&);
void fn_sub_546498_00546498(p3fes::EEContext&);
void fn_sub_546638_00546638(p3fes::EEContext&);
void fn_sub_546718_00546718(p3fes::EEContext&);
void fn_sub_547068_00547068(p3fes::EEContext&);
void fn_sub_548F40_00548f40(p3fes::EEContext&);
void fn_sub_54A710_0054a710(p3fes::EEContext&);
void fn_sub_54A880_0054a880(p3fes::EEContext&);
void fn_sub_55D668_0055d668(p3fes::EEContext&);
void fn_sub_55D790_0055d790(p3fes::EEContext&);
void fn_sub_55D918_0055d918(p3fes::EEContext&);
void fn_sub_55D9B0_0055d9b0(p3fes::EEContext&);
void fn_sub_55DAB0_0055dab0(p3fes::EEContext&);
void fn_sub_562388_00562388(p3fes::EEContext&);
void fn_sub_5649A8_005649a8(p3fes::EEContext&);
void fn_sub_5649C0_005649c0(p3fes::EEContext&);
void fn_sub_5649D8_005649d8(p3fes::EEContext&);
void fn_sub_5649F0_005649f0(p3fes::EEContext&);
void fn_sub_564A20_00564a20(p3fes::EEContext&);
void fn_sub_564A38_00564a38(p3fes::EEContext&);
void fn_sub_564A50_00564a50(p3fes::EEContext&);
void fn_sub_564A68_00564a68(p3fes::EEContext&);
void fn_sub_564DD0_00564dd0(p3fes::EEContext&);
void fn_sub_564EF8_00564ef8(p3fes::EEContext&);
void fn_sub_57BAF0_0057baf0(p3fes::EEContext&);
void fn_sub_581798_00581798(p3fes::EEContext&);
void fn_sub_582828_00582828(p3fes::EEContext&);
void fn_sub_582838_00582838_at_00582850(p3fes::EEContext&);
void fn_sub_583058_00583058(p3fes::EEContext&);
void fn_sub_5838C0_005838c0(p3fes::EEContext&);
void fn_sub_5838D8_005838d8(p3fes::EEContext&);
void fn_sub_5838F0_005838f0(p3fes::EEContext&);
void fn_sub_583940_00583940(p3fes::EEContext&);
void fn_sub_5839B8_005839b8(p3fes::EEContext&);
void fn_sub_583A08_00583a08(p3fes::EEContext&);
void fn_sub_583A78_00583a78(p3fes::EEContext&);
void fn_sub_583AC8_00583ac8(p3fes::EEContext&);
void fn_sub_583B18_00583b18(p3fes::EEContext&);
void fn_sub_583BB8_00583bb8(p3fes::EEContext&);
void fn_sub_583C58_00583c58(p3fes::EEContext&);
void fn_sub_583C70_00583c70(p3fes::EEContext&);
void fn_sub_583C88_00583c88(p3fes::EEContext&);
void fn_sub_583CA0_00583ca0(p3fes::EEContext&);
void fn_sub_583CB8_00583cb8(p3fes::EEContext&);
void fn_sub_583CD0_00583cd0(p3fes::EEContext&);
void fn_sub_583CE8_00583ce8(p3fes::EEContext&);
void fn_sub_583D58_00583d58(p3fes::EEContext&);
void fn_sub_583DB8_00583db8(p3fes::EEContext&);
void fn_sub_583DE8_00583de8(p3fes::EEContext&);
void fn_sub_583E58_00583e58(p3fes::EEContext&);
void fn_sub_583EB8_00583eb8(p3fes::EEContext&);
void fn_sub_583ED0_00583ed0(p3fes::EEContext&);
void fn_sub_583FB8_00583fb8(p3fes::EEContext&);
void fn_sub_583FD0_00583fd0(p3fes::EEContext&);
void fn_sub_583FE8_00583fe8(p3fes::EEContext&);
void fn_sub_584000_00584000(p3fes::EEContext&);
void fn_sub_584018_00584018(p3fes::EEContext&);
void fn_sub_584030_00584030(p3fes::EEContext&);
void fn_sub_584070_00584070(p3fes::EEContext&);
void fn_sub_584190_00584190(p3fes::EEContext&);
void fn_sub_584230_00584230(p3fes::EEContext&);
void fn_sub_584290_00584290(p3fes::EEContext&);
void fn_sub_584400_00584400(p3fes::EEContext&);
void fn_sub_5844C8_005844c8(p3fes::EEContext&);
void fn_sub_584558_00584558(p3fes::EEContext&);
void fn_sub_5845E0_005845e0(p3fes::EEContext&);
void fn_sub_584680_00584680(p3fes::EEContext&);
void fn_sub_584730_00584730(p3fes::EEContext&);
void fn_sub_584748_00584748(p3fes::EEContext&);
void fn_sub_584760_00584760(p3fes::EEContext&);
void fn_sub_584778_00584778(p3fes::EEContext&);
void fn_sub_584790_00584790(p3fes::EEContext&);
void fn_sub_584800_00584800(p3fes::EEContext&);
void fn_sub_5848D8_005848d8(p3fes::EEContext&);
void fn_sub_584928_00584928(p3fes::EEContext&);
void fn_sub_584950_00584950(p3fes::EEContext&);
void fn_sub_584978_00584978(p3fes::EEContext&);
void fn_sub_5849A0_005849a0(p3fes::EEContext&);
void fn_sub_5849D0_005849d0(p3fes::EEContext&);
void fn_sub_584A08_00584a08(p3fes::EEContext&);
void fn_sub_584AA0_00584aa0(p3fes::EEContext&);
void fn_sub_584AA8_00584aa8(p3fes::EEContext&);
void fn_sub_584AB0_00584ab0(p3fes::EEContext&);
void fn_sub_584B78_00584b78(p3fes::EEContext&);
void fn_sub_584BE0_00584be0(p3fes::EEContext&);
void fn_sub_584D98_00584d98(p3fes::EEContext&);
void fn_sub_584F30_00584f30(p3fes::EEContext&);
void fn_sub_5851D0_005851d0(p3fes::EEContext&);
void fn_sub_585268_00585268(p3fes::EEContext&);
void fn_sub_5852A0_005852a0(p3fes::EEContext&);
void fn_sub_5852C0_005852c0(p3fes::EEContext&);
void fn_sub_5854B8_005854b8(p3fes::EEContext&);
void fn_sub_5854D0_005854d0(p3fes::EEContext&);
void fn_sub_5854F0_005854f0(p3fes::EEContext&);
void fn_sub_585528_00585528(p3fes::EEContext&);
void fn_sub_585540_00585540(p3fes::EEContext&);
void fn_sub_585560_00585560(p3fes::EEContext&);
void fn_sub_585590_00585590(p3fes::EEContext&);
void fn_sub_585D38_00585d38(p3fes::EEContext&);
void fn_sub_585D50_00585d50(p3fes::EEContext&);
void fn_sub_585E08_00585e08(p3fes::EEContext&);
void fn_sub_585E70_00585e70(p3fes::EEContext&);
void fn_sub_5860B0_005860b0(p3fes::EEContext&);
void fn_sub_5860D0_005860d0(p3fes::EEContext&);
void fn_sub_586110_00586110(p3fes::EEContext&);
void fn_sub_586148_00586148(p3fes::EEContext&);
void fn_sub_586150_00586150(p3fes::EEContext&);
void fn_sub_586220_00586220(p3fes::EEContext&);
void fn_sub_5862B8_005862b8(p3fes::EEContext&);
void fn_sub_5862E8_005862e8(p3fes::EEContext&);
void fn_sub_5862F8_005862f8(p3fes::EEContext&);
void fn_sub_586338_00586338(p3fes::EEContext&);
void fn_sub_586420_00586420(p3fes::EEContext&);
void fn_sub_586490_00586490(p3fes::EEContext&);
void fn_sub_5864D8_005864d8(p3fes::EEContext&);
void fn_sub_5865E8_005865e8(p3fes::EEContext&);
void fn_sub_586688_00586688(p3fes::EEContext&);
void fn_sub_586898_00586898(p3fes::EEContext&);
void fn_sub_5876F0_005876f0(p3fes::EEContext&);
void fn_sub_587E10_00587e10(p3fes::EEContext&);
void fn_sub_587FD8_00587fd8(p3fes::EEContext&);
void fn_sub_588028_00588028(p3fes::EEContext&);
void fn_sub_588048_00588048(p3fes::EEContext&);
void fn_sub_588068_00588068(p3fes::EEContext&);
void fn_sub_588088_00588088(p3fes::EEContext&);
void fn_sub_5880A8_005880a8(p3fes::EEContext&);
void fn_sub_588138_00588138(p3fes::EEContext&);
void fn_sub_5883C0_005883c0(p3fes::EEContext&);
void fn_sub_588C10_00588c10(p3fes::EEContext&);
void fn_sub_588FD8_00588fd8(p3fes::EEContext&);
void fn_sub_589000_00589000(p3fes::EEContext&);
void fn_sub_589688_00589688(p3fes::EEContext&);
void fn_sub_589830_00589830(p3fes::EEContext&);
void fn_sub_589928_00589928(p3fes::EEContext&);
void fn_sub_589AD8_00589ad8(p3fes::EEContext&);
void fn_sub_589BC8_00589bc8(p3fes::EEContext&);
void fn_sub_589BD0_00589bd0(p3fes::EEContext&);
void fn_sub_589D58_00589d58(p3fes::EEContext&);
void fn_sub_58A290_0058a290(p3fes::EEContext&);
void fn_sub_58AC78_0058ac78(p3fes::EEContext&);
void fn_sub_58ACF0_0058acf0(p3fes::EEContext&);
void fn_sub_58AE50_0058ae50(p3fes::EEContext&);
void fn_sub_58BE40_0058be40(p3fes::EEContext&);
void fn_sub_58C060_0058c060(p3fes::EEContext&);
void fn_sub_58C100_0058c100(p3fes::EEContext&);
void fn_sub_58C118_0058c118(p3fes::EEContext&);
void fn_sub_58C228_0058c228(p3fes::EEContext&);
void fn_sub_5990A8_005990a8(p3fes::EEContext&);
void fn_sub_59A028_0059a028(p3fes::EEContext&);
void fn_sub_59BE98_0059be98(p3fes::EEContext&);
void fn_sub_59EF90_0059ef90(p3fes::EEContext&);
void fn_sub_59F008_0059f008(p3fes::EEContext&);
void fn_sub_59F080_0059f080(p3fes::EEContext&);
void fn_sub_59F0C8_0059f0c8(p3fes::EEContext&);
void fn_sub_59F6C8_0059f6c8(p3fes::EEContext&);
void fn_sub_59F7E8_0059f7e8(p3fes::EEContext&);
void fn_sub_59F8F8_0059f8f8(p3fes::EEContext&);
void fn_sub_59FD50_0059fd50(p3fes::EEContext&);
void fn_sub_59FEF8_0059fef8(p3fes::EEContext&);
void fn_sub_59FF60_0059ff60(p3fes::EEContext&);
void fn_sub_59FF78_0059ff78(p3fes::EEContext&);
void fn_sub_59FF98_0059ff98(p3fes::EEContext&);
void fn_sub_59FFB0_0059ffb0(p3fes::EEContext&);
void fn_sub_59FFC8_0059ffc8(p3fes::EEContext&);
void fn_sub_5A0008_005a0008(p3fes::EEContext&);
void fn_sub_5A0048_005a0048(p3fes::EEContext&);
void fn_sub_5A01B0_005a01b0(p3fes::EEContext&);
void fn_sub_5A0208_005a0208(p3fes::EEContext&);
void fn_sub_5A0220_005a0220(p3fes::EEContext&);
void fn_tie__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_00586138(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
namespace ply = ::p3fes::game::l22::ply;

// 0x005838C0 sub_5838C0 -- 24 bytes; frame 0x10: ra sp+0x0
// MWSFD SFX wrapper: sub_59FF60 on the player's SFX handle (+168) (tail call).
void sub_5838C0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005838c0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, ply::kSfx);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59FF60_0059ff60(ctx);  // tail call
}

// 0x005838D8 sub_5838D8 -- 24 bytes; leaf frame (no stack)
// Reads the pair at player +408 / +412: *$a2 = +412, *$a1 = +408 (both words of the record at +404).
void sub_5838D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x005838d8
    enter(ctx, 6);  // entry check point + this block's cycles
    a0 = addiu(a0, 404);
    lw(v0, a0, 8);
    lw(v1, a0, 4);
    sw(v0, a2, 0);
    sw(v1, a1, 0);
}

// 0x005838F0 sub_5838F0 -- 76 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// MWSFD SFX wrapper: sub_59FEF8 on the player's SFX handle (+168) into two stack words, then *$a1 = the first, *$a2 = the second.
void sub_5838F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005838f0
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(s1, sp, 0x18);
    s1 = a2;
    sd(ra, sp, 0x20);
    a1 = sp;
    a2 = addiu(sp, 0x4);
    link(ctx, 0x583910u);  // $ra first: the delay slot below depends on it
    lw(a0, a0, ply::kSfx);
    call(ctx, gen::fn_sub_59FEF8_0059fef8);
    lw(v0, sp, 0x0);
    lw(v1, sp, 0x4);
    sw(v0, s0, 0);
    sw(v1, s1, 0);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00583940 sub_583940 -- 120 bytes; frame 0xD0: s0 sp+0xA0, s1 sp+0xA8, s2 sp+0xB0, s3 sp+0xB8, s4 sp+0xC0, ra sp+0xC8
// MWSFD SFX wrapper: sub_59FF78 on the player's SFX handle (+168) (sub_582828) with the 160-byte frame record the player fills on the stack (0x582850, a mid-body entry of sub_582838, with the player and $a1), passing $a2 / $a3 through.
void sub_583940(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583940
    enter(ctx, 30);  // entry check point + this block's cycles
    sp = addiu(sp, -0xD0);
    sd(s0, sp, 0xA0);
    s0 = a0;
    sd(s1, sp, 0xA8);
    sd(s2, sp, 0xB0);
    s2 = a1;
    sd(s3, sp, 0xB8);
    s3 = a2;
    sd(s4, sp, 0xC0);
    sd(ra, sp, 0xC8);
    s4 = a3;
    jal(ctx, 0x583968u, gen::fn_sub_582828_00582828);
    a2 = sp;
    a0 = s0;
    a1 = s2;
    s1 = v0;
    link(ctx, 0x58397Cu);
    gen::fn_sub_582838_00582838_at_00582850(ctx);
    a0 = s1;
    a2 = s3;
    a3 = s4;
    a1 = sp;
    jal(ctx, 0x583990u, gen::fn_sub_59FF78_0059ff78);
    ld(s0, sp, 0xA0);
    ld(s1, sp, 0xA8);
    ld(s2, sp, 0xB0);
    ld(s3, sp, 0xB8);
    ld(s4, sp, 0xC0);
    ld(ra, sp, 0xC8);
    sp = addiu(sp, 0xD0);
}

// 0x005839B8 sub_5839B8 -- 80 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// MWSFD SFX wrapper: sub_59FF98 on the player's SFX handle (+168) (sub_582828) with $a1, $a2 and ($a3 == 1).
void sub_5839B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005839b8
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a3;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x5839D4u, gen::fn_sub_582828_00582828);
    s0 = s0 ^ 0x1;
    ld(ra, sp, 0x18);
    a1 = s1;
    ld(s1, sp, 0x8);
    a2 = s2;
    ld(s2, sp, 0x10);
    a3 = sltiu(s0, 1);
    ld(s0, sp, 0x0);
    a0 = v0;
    sp = addiu(sp, 0x20);
    gen::fn_sub_59FF98_0059ff98(ctx);  // tail call
}

// 0x00583A08 sub_583A08 -- 112 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// MWSFD SFX wrapper: sub_59FFB0 on the player's SFX handle (+168) (sub_582828) into three stack words; *$a1 = the first, *$a2 = the
// second, *$a3 = the third when it is 1, else 0.
void sub_583A08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583a08
    enter(ctx, 28);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(s1, sp, 0x18);
    s1 = a3;
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x28);
    s2 = a2;
    jal(ctx, 0x583A24u, gen::fn_sub_582828_00582828);
    a0 = v0;
    a1 = sp;
    a2 = addiu(sp, 0x4);
    a3 = addiu(sp, 0x8);
    jal(ctx, 0x583A38u, gen::fn_sub_59FFB0_0059ffb0);
    lw(v0, sp, 0x8);
    lw(a0, sp, 0x0);
    v1 = v0 ^ 0x1;
    lw(a1, sp, 0x4);
    if (v1 != 0) v0 = 0;
    sw(a0, s0, 0);
    sw(v0, s1, 0);
    sw(a1, s2, 0);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00583A78 sub_583A78 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// MWSFD SFX wrapper: sub_59FFC8 on the player's SFX handle (+168) (sub_582828) with the low bytes of $a1, $a2, $a3.
void sub_583A78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583a78
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1 & 0xFF;
    sd(s1, sp, 0x8);
    s1 = a2 & 0xFF;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a3 & 0xFF;
    jal(ctx, 0x583A94u, gen::fn_sub_582828_00582828);
    ld(ra, sp, 0x18);
    a1 = s0;
    a2 = s1;
    ld(s1, sp, 0x8);
    a3 = s2;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    a0 = v0;
    sp = addiu(sp, 0x20);
    gen::fn_sub_59FFC8_0059ffc8(ctx);  // tail call
}

// 0x00583AC8 sub_583AC8 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// MWSFD SFX wrapper: sub_5A0008 on the player's SFX handle (+168) (sub_582828), $a1..$a3 passed through.
void sub_583AC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583ac8
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a3;
    jal(ctx, 0x583AE4u, gen::fn_sub_582828_00582828);
    ld(ra, sp, 0x18);
    a1 = s0;
    a2 = s1;
    ld(s1, sp, 0x8);
    a3 = s2;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    a0 = v0;
    sp = addiu(sp, 0x20);
    gen::fn_sub_5A0008_005a0008(ctx);  // tail call
}

// 0x00583B18 sub_583B18 -- 160 bytes; frame 0xC0: s1 sp+0xA8, s2 sp+0xB0, s0 sp+0xA0, ra sp+0xB8
// Handle check (sub_581798; on failure the error printer sub_585590 with E202283); a frame object with a null word +0 is refused (E202284, "getfrm is failed");
// else sub_59EF90 on the player's SFX handle (+168) with the 160-byte frame record the player fills on the stack (0x582850, a mid-body entry of sub_582838, with the player and $a1).
void sub_583B18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583b18
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(s1, sp, 0xA8);
    s1 = a0;
    sd(s2, sp, 0xB0);
    sd(s0, sp, 0xA0);
    sd(ra, sp, 0xB8);
    s2 = a1;
    jal(ctx, 0x583B30u, gen::fn_sub_581798_00581798);
    a0 = 0x7D0000;
    v1 = 1;
    a0 = addiu(a0, -26936);  // "E202283: MWSFD_MakeTblZ16: handle is invalid."
    if (v0 == v1) {
        // 0x00583b58
        charge(ctx, 3);
        lw(v0, s2, 0);
        if (v0 != 0) {
            // 0x00583b78
            charge(ctx, 11);
            a0 = s1;
            jal(ctx, 0x583B78u, gen::fn_sub_582828_00582828);
            a0 = s1;
            a1 = s2;
            a2 = sp;
            s0 = v0;
            link(ctx, 0x583B8Cu);
            gen::fn_sub_582838_00582838_at_00582850(ctx);
            a1 = sp;
            a0 = s0;
            jal(ctx, 0x583B98u, gen::fn_sub_59EF90_0059ef90);
            ld(s0, sp, 0xA0);
        } else {
            // 0x00583b64
            charge(ctx, 5);
            a0 = 0x7D0000;
            a0 = addiu(a0, -26888);  // "E202284: MWSFD_MakeTblZ16: getfrm is failed."
            jal(ctx, 0x583B68u, gen::fn_sub_585590_00585590);
            ld(s0, sp, 0xA0);
        }
    } else {
        // 0x00583b48
        charge(ctx, 4);
        jal(ctx, 0x583B48u, gen::fn_sub_585590_00585590);
        ld(s0, sp, 0xA0);
    }
    // 0x00583ba4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0xA8);
    ld(s2, sp, 0xB0);
    ld(ra, sp, 0xB8);
    sp = addiu(sp, 0xC0);
}

// 0x00583BB8 sub_583BB8 -- 160 bytes; frame 0xC0: s1 sp+0xA8, s2 sp+0xB0, s0 sp+0xA0, ra sp+0xB8
// Handle check (sub_581798; on failure the error printer sub_585590 with E202285); a frame object with a null word +0 is refused (E202286, "getfrm is failed");
// else sub_59F008 on the player's SFX handle (+168) with the 160-byte frame record the player fills on the stack (0x582850, a mid-body entry of sub_582838, with the player and $a1).
void sub_583BB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583bb8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(s1, sp, 0xA8);
    s1 = a0;
    sd(s2, sp, 0xB0);
    sd(s0, sp, 0xA0);
    sd(ra, sp, 0xB8);
    s2 = a1;
    jal(ctx, 0x583BD0u, gen::fn_sub_581798_00581798);
    a0 = 0x7D0000;
    v1 = 1;
    a0 = addiu(a0, -26840);  // "E202285: MWSFD_MakeTblZ32: handle is invalid."
    if (v0 == v1) {
        // 0x00583bf8
        charge(ctx, 3);
        lw(v0, s2, 0);
        if (v0 != 0) {
            // 0x00583c18
            charge(ctx, 11);
            a0 = s1;
            jal(ctx, 0x583C18u, gen::fn_sub_582828_00582828);
            a0 = s1;
            a1 = s2;
            a2 = sp;
            s0 = v0;
            link(ctx, 0x583C2Cu);
            gen::fn_sub_582838_00582838_at_00582850(ctx);
            a1 = sp;
            a0 = s0;
            jal(ctx, 0x583C38u, gen::fn_sub_59F008_0059f008);
            ld(s0, sp, 0xA0);
        } else {
            // 0x00583c04
            charge(ctx, 5);
            a0 = 0x7D0000;
            a0 = addiu(a0, -26792);  // "E202286: MWSFD_MakeTblZ32: getfrm is failed."
            jal(ctx, 0x583C08u, gen::fn_sub_585590_00585590);
            ld(s0, sp, 0xA0);
        }
    } else {
        // 0x00583be8
        charge(ctx, 4);
        jal(ctx, 0x583BE8u, gen::fn_sub_585590_00585590);
        ld(s0, sp, 0xA0);
    }
    // 0x00583c44 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0xA8);
    ld(s2, sp, 0xB0);
    ld(ra, sp, 0xB8);
    sp = addiu(sp, 0xC0);
}

// 0x00583C58 sub_583C58 -- 32 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Stores $a1 in the SFX record's word +88 (player +168 -> +88). Two chunks (the tail at 0x5A0020).
void sub_583C58(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583c58
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, ply::kSfx);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x005a0020
    charge(ctx, 2);
    sw(a1, a0, 88);
}

// 0x00583C70 sub_583C70 -- 32 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Returns the SFX record's word +88 (player +168 -> +88). Two chunks (the tail at 0x5A0028).
void sub_583C70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583c70
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, ply::kSfx);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x005a0028
    charge(ctx, 2);
    lw(v0, a0, 88);
}

// 0x00583C88 sub_583C88 -- 32 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Stores $a1 in the SFX record's word +92 (player +168 -> +92). Two chunks (the tail at 0x5A0030).
void sub_583C88(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583c88
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, ply::kSfx);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x005a0030
    charge(ctx, 2);
    sw(a1, a0, 92);
}

// 0x00583CA0 sub_583CA0 -- 32 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Returns the SFX record's word +92 (player +168 -> +92). Two chunks (the tail at 0x5A0038).
void sub_583CA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583ca0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, ply::kSfx);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x005a0038
    charge(ctx, 2);
    lw(v0, a0, 92);
}

// 0x00583CB8 sub_583CB8 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: sub_59FD50 (sfx_SetCnvMode, the setting 0x7B4934).
void sub_583CB8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00583cb8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59FD50_0059fd50(ctx);  // tail call
}

// 0x00583CD0 sub_583CD0 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: WTLS_get_table_2 (0x59FD60), the matching SFX setting getter.
void sub_583CD0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00583cd0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_WTLS_get_table_2_0059fd60(ctx);  // tail call
}

// 0x00583CE8 sub_583CE8 -- 108 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Handle check (sub_581798; on failure the error printer sub_585590 with E304162, whose text says MWSFD_GetMaxAlpha); sub_5A01B0 on
// the player's SFX handle (+168) with $a1 (tail call).
void sub_583CE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583ce8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x583CFCu, gen::fn_sub_581798_00581798);
    v1 = 1;
    a0 = s0;
    if (v0 != v1) {
        // 0x00583d10
        charge(ctx, 7);
        a0 = 0x7D0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, -26744);  // "E304162: MWSFD_GetMaxAlpha: handle is invalid."
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    // 0x00583d30
    charge(ctx, 9);
    jal(ctx, 0x583D30u, gen::fn_sub_582828_00582828);
    a1 = s1;
    ld(s0, sp, 0x0);
    a0 = v0;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_5A01B0_005a01b0(ctx);  // tail call
}

// 0x00583D58 sub_583D58 -- 92 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Handle check (sub_581798; on failure the error printer sub_585590 with E304161, "MWSFD_GetMaxAlpha": returns 0); else sub_5A0208 on
// the player's SFX handle (+168) (tail call).
void sub_583D58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583d58
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x583D64u, gen::fn_sub_581798_00581798);
    v1 = 1;
    a0 = s0;
    if (v0 == v1) {
        // 0x00583d98
        charge(ctx, 7);
        jal(ctx, 0x583D98u, gen::fn_sub_582828_00582828);
        ld(s0, sp, 0x0);
        a0 = v0;
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_sub_5A0208_005a0208(ctx);  // tail call
        return;
    }
    // 0x00583d78
    charge(ctx, 8);
    a0 = 0x7D0000;
    a0 = addiu(a0, -26696);  // "E304161: MWSFD_GetMaxAlpha: handle is invalid."
    jal(ctx, 0x583D7Cu, gen::fn_sub_585590_00585590);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00583DB8 sub_583DB8 -- 56 bytes, 2 chunks; frame 0x10: s0 sp+0x0, ra sp+0x8
// Stores $a1 at +68 of the record the SFX handle points to at +36 (sub_582828 -> +36 -> +68). Two chunks.
void sub_583DB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583db8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a1;
    jal(ctx, 0x583DC4u, gen::fn_sub_582828_00582828);
    ld(ra, sp, 0x8);
    a1 = s0;
    ld(s0, sp, 0x0);
    a0 = v0;
    sp = addiu(sp, 0x10);
    // 0x0059fd90
    charge(ctx, 3);
    lw(v0, a0, 36);
    sw(a1, v0, 68);
}

// 0x00583DE8 sub_583DE8 -- 116 bytes, 2 chunks; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [proposed name: mwPlySetCnvBottomUp] Handle check (sub_581798; on failure the error printer sub_585590 with E404010); stores $a1 in
// the SFX handle's word +100. Two chunks (the tail at 0x5A0040).
void sub_583DE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583de8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x583DFCu, gen::fn_sub_581798_00581798);
    v1 = 1;
    a0 = s0;
    if (v0 != v1) {
        // 0x00583e10
        charge(ctx, 7);
        a0 = 0x7D0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, -26648);  // "E404010: mwPlySetCnvBottomUp: handle is invalid."
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    // 0x00583e30
    charge(ctx, 9);
    jal(ctx, 0x583E30u, gen::fn_sub_582828_00582828);
    a1 = s1;
    ld(s0, sp, 0x0);
    a0 = v0;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    // 0x005a0040
    charge(ctx, 2);
    sw(a1, a0, 100);
}

// 0x00583E58 sub_583E58 -- 92 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// [proposed name: mwPlyGetCnvBottomUp] Handle check (sub_581798; on failure the error printer sub_585590 with E404011: returns 0);
// else sub_5A0048 on the player's SFX handle (+168) (tail call).
void sub_583E58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583e58
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x583E64u, gen::fn_sub_581798_00581798);
    v1 = 1;
    a0 = s0;
    if (v0 == v1) {
        // 0x00583e98
        charge(ctx, 7);
        jal(ctx, 0x583E98u, gen::fn_sub_582828_00582828);
        ld(s0, sp, 0x0);
        a0 = v0;
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_sub_5A0048_005a0048(ctx);  // tail call
        return;
    }
    // 0x00583e78
    charge(ctx, 8);
    a0 = 0x7D0000;
    a0 = addiu(a0, -26592);  // "E404011: mwPlyGetCnvBottomUp: handle is invalid."
    jal(ctx, 0x583E7Cu, gen::fn_sub_585590_00585590);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00583EB8 sub_583EB8 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: sub_5A0220.
void sub_583EB8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00583eb8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5A0220_005a0220(ctx);  // tail call
}

// 0x00583ED0 sub_583ED0 -- 228 bytes; frame 0x10: ra sp+0x0
// Composes a frame through the SFX: with the player's SFX handle (+168), the $a1 object's words +12 / +16
// and the 160-byte frame record the player fills on the stack (0x582850, a mid-body entry of sub_582838, with the player and $a1): sub_59F6C8 (an 80-byte output
// record on the stack), sub_59F080 with $a3, then sub_59F0C8 on the two records.
void sub_583ED0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583ed0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a1;
    sd(ra, sp, 0x0);
    t0 = 0;
    t1 = 0;
    lw(t3, v0, 16);
    lw(t2, v0, 12);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00583ef8
    charge(ctx, 47);
    sp = addiu(sp, -0x140);
    sd(s1, sp, 0xF8);
    s1 = t0;
    sd(s2, sp, 0x100);
    s2 = t1;
    sd(s3, sp, 0x108);
    s3 = t2;
    sd(s4, sp, 0x110);
    s4 = t3;
    sd(s5, sp, 0x118);
    s5 = a2;
    sd(s6, sp, 0x120);
    a2 = sp;
    sd(s7, sp, 0x128);
    s7 = a3;
    sd(ra, sp, 0x130);
    sd(s0, sp, 0xF0);
    link(ctx, 0x583F3Cu);
    lw(s0, a0, ply::kSfx);
    gen::fn_sub_582838_00582838_at_00582850(ctx);
    s6 = addiu(sp, 0xA0);
    a1 = sp;
    t0 = s1;
    t1 = s2;
    t2 = s3;
    t3 = s4;
    a3 = s6;
    a2 = s5;
    a0 = s0;
    jal(ctx, 0x583F64u, gen::fn_sub_59F6C8_0059f6c8);
    a0 = s0;
    a1 = s7;
    jal(ctx, 0x583F70u, gen::fn_sub_59F080_0059f080);
    a0 = s0;
    a2 = s6;
    a1 = sp;
    jal(ctx, 0x583F80u, gen::fn_sub_59F0C8_0059f0c8);
    ld(s0, sp, 0xF0);
    ld(s1, sp, 0xF8);
    ld(s2, sp, 0x100);
    ld(s3, sp, 0x108);
    ld(s4, sp, 0x110);
    ld(s5, sp, 0x118);
    ld(s6, sp, 0x120);
    ld(s7, sp, 0x128);
    ld(ra, sp, 0x130);
    sp = addiu(sp, 0x140);
}

// 0x00583FB8 sub_583FB8 -- 32 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Stores $a1 in the SFX record's word +108 (player +168 -> +108). Two chunks.
void sub_583FB8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583fb8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, ply::kSfx);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0059f088
    charge(ctx, 2);
    sw(a1, a0, 108);
}

// 0x00583FD0 sub_583FD0 -- 36 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Stores $a1 at +24 of the record at SFX +48 (player +168 -> +48 -> +24). Two chunks.
void sub_583FD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583fd0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, ply::kSfx);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0059f090
    charge(ctx, 3);
    lw(v0, a0, 48);
    sw(a1, v0, 24);
}

// 0x00583FE8 sub_583FE8 -- 36 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Stores $a1 at +32 of the record at SFX +48 (player +168 -> +48 -> +32). Two chunks.
void sub_583FE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583fe8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, ply::kSfx);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0059f0a0
    charge(ctx, 3);
    lw(v0, a0, 48);
    sw(a1, v0, 32);
}

// 0x00584000 sub_584000 -- 36 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Stores $a1 at +28 of the record at SFX +48 (player +168 -> +48 -> +28). Two chunks.
void sub_584000(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584000
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, ply::kSfx);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0059f0b0
    charge(ctx, 3);
    lw(v0, a0, 48);
    sw(a1, v0, 28);
}

// 0x00584018 sub_584018 -- 32 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Stores $a1 in the SFX record's word +112 (player +168 -> +112). Two chunks.
void sub_584018(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584018
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, ply::kSfx);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0059f0c0
    charge(ctx, 2);
    sw(a1, a0, 112);
}

// 0x00584030 sub_584030 -- 64 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// sub_59F8F8 with the player's words +16 / +20, the composition mode
// (sub_583058) and three stack outputs.
void sub_584030(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584030
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x18);
    s0 = a0;
    jal(ctx, 0x58403Cu, gen::fn_sub_583058_00583058);
    lw(a1, s0, 20);
    a2 = v0;
    lw(a0, s0, 16);
    a3 = sp;
    t0 = addiu(sp, 0x4);
    t1 = addiu(sp, 0x8);
    jal(ctx, 0x584058u, gen::fn_sub_59F8F8_0059f8f8);
    ld(s0, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00584070 sub_584070 -- 96 bytes; frame 0x30: s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, ra sp+0x20, s1 sp+0x8
// sub_59F7E8 on the player's SFX handle (+168) with its words +16 / +20, the composition mode
// (sub_583058) and $a1 / $a2.
void sub_584070(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584070
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(ra, sp, 0x20);
    sd(s1, sp, 0x8);
    link(ctx, 0x584094u);  // $ra first: the delay slot below depends on it
    lw(s1, s0, ply::kSfx);
    call(ctx, gen::fn_sub_583058_00583058);
    ld(ra, sp, 0x20);
    t0 = s3;
    a0 = s1;
    ld(s1, sp, 0x8);
    lw(a1, s0, 16);
    t1 = s2;
    lw(a2, s0, 20);
    a3 = v0;
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    sp = addiu(sp, 0x30);
    gen::fn_sub_59F7E8_0059f7e8(ctx);  // tail call
}

// 0x005844C8 sub_5844C8 -- 144 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Handle check (sub_581798; on failure the error printer sub_585590 with E1122632); resets the play list (+72, sub_55D668), sets the range
// (sub_584400 with $a1, $a2), loop flag 1 (sub_584230) and the seamless start (sub_584190).
void sub_5844C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005844c8
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x5844E4u, gen::fn_sub_581798_00581798);
    a0 = 0x7D0000;
    v1 = 1;
    a0 = addiu(a0, -25984);  // "E1122632: mwPlyStartAfsLp: handle is invalid."
    if (v0 != v1) {
        // 0x005844fc
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    // 0x00584518
    charge(ctx, 16);
    link(ctx, 0x584518u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, ply::kList);
    call(ctx, gen::fn_sub_55D668_0055d668);
    a0 = s0;
    a2 = s2;
    a1 = s1;
    jal(ctx, 0x584528u, gen::fn_sub_584400_00584400);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x584534u, gen::fn_sub_584230_00584230);
    a0 = s0;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_584190_00584190(ctx);  // tail call
}

// 0x005845E0 sub_5845E0 -- 160 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// [proposed name: mwPlyStartFnameRangeLp] Handle check (sub_581798; on failure the error printer sub_585590 with E407024); resets
// the play list (+72, sub_55D668), enters the file name range (sub_584558 with $a1..$a3), loop flag 1
// (sub_584230) and the seamless start (sub_584190).
void sub_5845E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005845e0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    s3 = a3;
    jal(ctx, 0x584604u, gen::fn_sub_581798_00581798);
    a0 = 0x7D0000;
    v1 = 1;
    a0 = addiu(a0, -25880);  // "E407024: mwPlyStartFnameRangeLp: handle is invalid."
    if (v0 != v1) {
        // 0x0058461c
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    // 0x00584638
    charge(ctx, 18);
    link(ctx, 0x584638u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, ply::kList);
    call(ctx, gen::fn_sub_55D668_0055d668);
    a0 = s0;
    a2 = s2;
    a3 = s3;
    a1 = s1;
    jal(ctx, 0x58464Cu, gen::fn_sub_584558_00584558);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x584658u, gen::fn_sub_584230_00584230);
    a0 = s0;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_584190_00584190(ctx);  // tail call
}

// 0x00584680 sub_584680 -- 172 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// [proposed name: mwPlyGetSlFname] Handle check (sub_581798; on failure the error printer sub_585590 with E1122637: returns 0);
// stream numbers at or past the count (_get_peer_or_sock_name_0) give 0, a negative one prints E10821B
// ("Invalid value of stm_no") and gives 0; else entry sub_584748($a1) is resolved by sub_584760.
void sub_584680(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584680
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x584694u, gen::fn_sub_581798_00581798);
    v1 = 1;
    a0 = s1;
    if (v0 != v1) {
        // 0x005846a8
        charge(ctx, 5);
        a0 = 0x7D0000;
        a0 = addiu(a0, -25824);  // "E1122637: mwPlyGetSlFname: handle is invalid."
        jal(ctx, 0x5846ACu, gen::fn_sub_585590_00585590);
        v0 = 0;
        // 0x00584718 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x005846c0
    charge(ctx, 5);
    jal(ctx, 0x5846C0u, gen::fn__get_peer_or_sock_name_0_005843e8);
    v1 = slt(s0, v0);
    v0 = 0;
    if (v1 == 0) {
        // 0x00584718 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x005846d4
    charge(ctx, 2);
    a1 = s0;
    if (i64(s0) >= 0) {
        // 0x005846f0
        charge(ctx, 9);
        a0 = s1;
        jal(ctx, 0x5846F0u, gen::fn_sub_584748_00584748);
        a0 = s1;
        ld(s0, sp, 0x0);
        a1 = v0;
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_584760_00584760(ctx);  // tail call
        return;
    }
    // 0x005846dc
    charge(ctx, 5);
    a0 = 0x7D0000;
    a0 = addiu(a0, -25776);  // "E10821B : Invalid value of stm_no : %d"
    jal(ctx, 0x5846E0u, gen::fn_sub_585590_00585590);
    v0 = 0;
    // 0x00584718 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00584730 sub_584730 -- 24 bytes; frame 0x10: ra sp+0x0
// Thunk on the player's play list (+72): sub_55D790.
void sub_584730(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584730
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, ply::kList);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55D790_0055d790(ctx);  // tail call
}

// 0x00584778 sub_584778 -- 24 bytes; frame 0x10: ra sp+0x0
// Thunk on the player's play list (+72): sub_55D918.
void sub_584778(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584778
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, ply::kList);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55D918_0055d918(ctx);  // tail call
}

// 0x00584790 sub_584790 -- 24 bytes; frame 0x10: ra sp+0x0
// Thunk on the player's play list (+72): sub_55D9B0.
void sub_584790(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584790
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, ply::kList);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_55D9B0_0055d9b0(ctx);  // tail call
}

// 0x00584800 sub_584800 -- 44 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// sub_55DAB0 on the player's play list (+72); also stores the result in *$a1.
void sub_584800(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584800
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(ra, sp, 0x8);
    link(ctx, 0x584810u);  // $ra first: the delay slot below depends on it
    lw(a0, a0, ply::kList);
    call(ctx, gen::fn_sub_55DAB0_0055dab0);
    sw(v0, s0, 0);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005848D8 sub_5848D8 -- 76 bytes; frame 0x30: s0 sp+0x20, ra sp+0x28
// Builds a name: sprintf("%08x.%08x", $a1, ($a2 + 2047) >> 11) (the size in 2 KiB sectors)
// into a stack buffer, then sub_584290 (set the name and start) with it.
void sub_5848D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005848d8
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = a1;
    a3 = addiu(a2, 2047);
    a2 = v0;
    a1 = 0x7D0000;
    sd(s0, sp, 0x20);
    a3 = srl(a3, 11);
    a1 = addiu(a1, -25640);  // "%08x.%08x"
    s0 = a0;
    sd(ra, sp, 0x28);
    a0 = sp;
    jal(ctx, 0x584900u, gen::fn_sprintf_00523ac8);
    a1 = sp;
    a0 = s0;
    jal(ctx, 0x58490Cu, gen::fn_sub_584290_00584290);
    ld(s0, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00584928 sub_584928 -- 36 bytes; frame 0x20: ra sp+0x10
// MWSFD's fixed work sizes (sub_5849A0: 149,988 / 40,000 / 2,048) into three stack words; returns their sum.
void sub_584928(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584928
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a0 = sp;
    a1 = addiu(sp, 0x4);
    sd(ra, sp, 0x10);
    a2 = addiu(sp, 0x8);
    jal(ctx, 0x584938u, gen::fn_sub_5849A0_005849a0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00584950 sub_584950 -- 36 bytes; frame 0x20: ra sp+0x10
// Same as sub_584928: sub_5849A0's sum (149,988 + 40,000 + 2,048).
void sub_584950(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584950
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a0 = sp;
    a1 = addiu(sp, 0x4);
    sd(ra, sp, 0x10);
    a2 = addiu(sp, 0x8);
    jal(ctx, 0x584960u, gen::fn_sub_5849A0_005849a0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00584978 sub_584978 -- 36 bytes; frame 0x20: ra sp+0x10
// The other work-size table: sub_5849D0's sum (431,404 + 81,000 + 0x2000).
void sub_584978(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584978
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a0 = sp;
    a1 = addiu(sp, 0x4);
    sd(ra, sp, 0x10);
    a2 = addiu(sp, 0x8);
    jal(ctx, 0x584988u, gen::fn_sub_5849D0_005849d0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00584A08 sub_584A08 -- 148 bytes; frame 0x10: ra sp+0x0
// Moves the slave's SJ (+652) to a new target: detaches the old target (+656) from the SFD handle (+60) with
// sub_58C228(sfd, old + 192, 0, 0, 0), attaches $a1 + 192 with the SJ, and stores $a1 at +656.
void sub_584A08(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584a08
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00584a20
    charge(ctx, 31);
    sp = addiu(sp, -0x30);
    a2 = 0;
    sd(s0, sp, 0x0);
    s0 = addiu(a0, ply::kSlave);
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(ra, sp, 0x20);
    a3 = 0;
    sd(s1, sp, 0x8);
    t0 = 0;
    sd(s2, sp, 0x10);
    lw(s1, a0, ply::kSfd);
    lw(a1, s0, 16);
    lw(s2, s0, 12);
    a0 = s1;
    a1 = addiu(a1, 192);
    jal(ctx, 0x584A5Cu, gen::fn_sub_58C228_0058c228);
    a0 = s1;
    a1 = addiu(s3, 192);
    a2 = s2;
    a3 = 0;
    t0 = 0;
    jal(ctx, 0x584A74u, gen::fn_sub_58C228_0058c228);
    sw(s3, s0, 16);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00584AA0 sub_584AA0 -- 8 bytes; leaf frame (no stack)
// Returns the player's slave word +652 (the SJ that sub_584F30 creates).
void sub_584AA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00584aa0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, ply::kSlaveSj);
}

// 0x00584AA8 sub_584AA8 -- 8 bytes; leaf frame (no stack)
// Returns the player's slave word +660 (the core handle that sub_584F30 creates).
void sub_584AA8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00584aa8
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, ply::kSlaveCore);
}

// 0x00584D98 sub_584D98 -- 108 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// When the audio slave is active (sub_5851D0 == 1) and the slave interface (WTLS_get_table_1) has a hook at
// +32, calls it (jalr) with $a0's word +20, $a1 and $a2.
void sub_584D98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584d98
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x584DB4u, gen::fn_sub_5851D0_005851d0);
    v1 = 1;
    if (v0 != v1) {
        ld(s0, sp, 0x0);
    } else {
        // 0x00584dc8
        charge(ctx, 4);
        jal(ctx, 0x584DC8u, gen::fn_WTLS_get_table_1_005851b0);
        lw(a0, s0, 20);
        if (v0 != 0) {
            // 0x00584dd8
            charge(ctx, 3);
            lw(v0, v0, 32);
            a1 = s1;
            if (v0 != 0) {
                // 0x00584de4
                charge(ctx, 2);
                a2 = s2;
                jalr(ctx, 0x584DE4u, v0.u());
            }
        }
        // 0x00584dec
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x00584df0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00584F30 sub_584F30 -- 288 bytes; frame 0x50: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, s5 sp+0x38, ra sp+0x40
// Creates the player's audio slave (record at +640): with the slave interface (WTLS_get_table_1) set, resets
// (sub_584AB0), stores the work $a1, its size $a2 and the target $a3 at +644 / +648 / +656, asks the work sizes
// (sub_584B78);// a short size prints E303111. Creates the SJ (SJRBF_Create sub_562388, else E303112) at +652 and the core
// handle (sub_584BE0, else E303112) at +660, marks it used (+640 = 1) and attaches $a3 + 192 to the SFD
// handle (+60) with sub_58C228. Returns the core handle, or 0 (an error, or no interface).
void sub_584F30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584f30
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = a2;
    sd(s2, sp, 0x20);
    s2 = addiu(s0, ply::kSlave);
    sd(s3, sp, 0x28);
    s3 = a1;
    sd(s4, sp, 0x30);
    sd(s5, sp, 0x38);
    sd(ra, sp, 0x40);
    s4 = a3;
    jal(ctx, 0x584F60u, gen::fn_WTLS_get_table_1_005851b0);
    if (v0 == 0) {
        ld(s0, sp, 0x10);
    } else {
        // 0x00584f70
        charge(ctx, 14);
        jal(ctx, 0x584F70u, gen::fn_sub_584AB0_00584ab0);
        lw(s5, s0, ply::kSfd);
        sw(s1, s2, 8);
        a0 = sp;
        sw(s3, s2, 4);
        a1 = addiu(sp, 0x4);
        sw(s4, s2, 16);
        a2 = addiu(sp, 0x8);
        jal(ctx, 0x584F90u, gen::fn_sub_584B78_00584b78);
        a0 = 0x7D0000;
        v0 = slt(s1, v0);
        a0 = addiu(a0, -25624);  // "E303111: MWSST_Create: worksize is short."
        if (v0 == 0) {
            // 0x00584fa8
            charge(ctx, 8);
            lw(a0, sp, 0x0);
            lw(a1, sp, 0x4);
            lw(a2, sp, 0x8);
            a0 = addu(s3, a0);
            jal(ctx, 0x584FB4u, gen::fn_sub_562388_00562388);
            s1 = v0;
            a0 = s3;
            if (s1 == 0) {
                // 0x00584fc8
                charge(ctx, 3);
                a0 = 0x7D0000;
                a0 = addiu(a0, -25576);  // "E303112: MWSST_Create: can't create SJ."
                goto L_00585008;
            }
            // 0x00584fd8
            charge(ctx, 10);
            sw(s1, s2, 12);
            link(ctx, 0x584FDCu);  // $ra first: the delay slot below depends on it
            lw(a1, sp, 0x0);
            call(ctx, gen::fn_sub_584BE0_00584be0);
            a0 = s5;
            s0 = v0;
            a1 = addiu(s4, 192);
            a2 = s1;
            a3 = 0;
            t0 = 0;
            if (s0 == 0) {
                // 0x00585000
                charge(ctx, 2);
                a0 = 0x7D0000;
                a0 = addiu(a0, -25536);  // "E303112: MWSST_Create: can't create corehn."
                goto L_00585008;
            }
            // 0x00585018
            charge(ctx, 5);
            v0 = 1;
            sw(s0, s2, 20);
            link(ctx, 0x585020u);  // $ra first: the delay slot below depends on it
            sw(v0, s2, 0);
            call(ctx, gen::fn_sub_58C228_0058c228);
            v0 = s0;
            goto L_0058502c;
        }
    L_00585008:
        charge(ctx, 4);
        jal(ctx, 0x585008u, gen::fn_sub_585590_00585590);
        v0 = 0;
    L_0058502c:
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    }
    // 0x00585030 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x005851C0 WTLS_set_table_1 -- 12 bytes; leaf frame (no stack)
// [mwsfdSetSlaveIf] Stores $a0 as the audio slave interface 0x7B4538 (WTLS_get_table_1 reads it; FLIRT
// misname); $v0 keeps 0x7B0000.
void WTLS_set_table_1(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005851c0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sw(a0, v0, 17720);  // 0x7B4538
}

// 0x00585268 sub_585268 -- 56 bytes; frame 0x10: ra sp+0x0
// Registers $a0..$a2 as SVM server 0 (sub_564DD0(0, ..)) and keeps the slot id in 0x9A6EC0.
void sub_585268(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585268
    enter(ctx, 14);  // entry check point + this block's cycles
    v1 = a1;
    v0 = a0;
    sp = addiu(sp, -0x10);
    a3 = a2;
    a0 = 0;
    a1 = v0;
    sd(ra, sp, 0x0);
    a2 = v1;
    jal(ctx, 0x585284u, gen::fn_sub_564DD0_00564dd0);
    v1 = 0x9A0000;
    ld(ra, sp, 0x0);
    sw(v0, v1, 28352);  // 0x9A6EC0
    sp = addiu(sp, 0x10);
}

// 0x005852A0 sub_5852A0 -- 32 bytes; frame 0x10: ra sp+0x0
// Unregisters SVM server 0's slot 0x9A6EC0 (sub_564EF8(0, slot)).
void sub_5852A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005852a0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x9A0000;
    sd(ra, sp, 0x0);
    a0 = 0;
    lw(a1, v0, 28352);  // 0x9A6EC0
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564EF8_00564ef8(ctx);  // tail call
}

// 0x005852C0 sub_5852C0 -- 56 bytes; frame 0x10: ra sp+0x0
// Registers $a0..$a2 as SVM server 2 (sub_564DD0(2, ..)) and keeps the slot id in 0x9A6EC4.
void sub_5852C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005852c0
    enter(ctx, 14);  // entry check point + this block's cycles
    v1 = a1;
    v0 = a0;
    sp = addiu(sp, -0x10);
    a3 = a2;
    a0 = 2;
    a1 = v0;
    sd(ra, sp, 0x0);
    a2 = v1;
    jal(ctx, 0x5852DCu, gen::fn_sub_564DD0_00564dd0);
    v1 = 0x9A0000;
    ld(ra, sp, 0x0);
    sw(v0, v1, 28356);  // 0x9A6EC4
    sp = addiu(sp, 0x10);
}

// 0x00585498 coshl_11 -- 32 bytes; frame 0x10: ra sp+0x0
// SVM lock type 2 (sub_5649A8); returns 1 (FLIRT misname).
void coshl_11(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585498
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x5854A0u, gen::fn_sub_5649A8_005649a8);
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}

// 0x005854B8 sub_5854B8 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: SVM unlock type 2 (sub_564A20).
void sub_5854B8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005854b8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564A20_00564a20(ctx);  // tail call
}

// 0x005854D0 sub_5854D0 -- 32 bytes; frame 0x10: ra sp+0x0
// SVM lock (sub_5649C0); returns 1.
void sub_5854D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005854d0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x5854D8u, gen::fn_sub_5649C0_005649c0);
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}

// 0x005854F0 sub_5854F0 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: SVM unlock (sub_564A38).
void sub_5854F0(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005854f0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564A38_00564a38(ctx);  // tail call
}

// 0x00585508 hypotl_11 -- 32 bytes; frame 0x10: ra sp+0x0
// SVM lock (sub_5649D8); returns 1 (FLIRT misname).
void hypotl_11(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585508
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x585510u, gen::fn_sub_5649D8_005649d8);
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}

// 0x00585528 sub_585528 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: SVM unlock (sub_564A50).
void sub_585528(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00585528
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564A50_00564a50(ctx);  // tail call
}

// 0x00585540 sub_585540 -- 32 bytes; frame 0x10: ra sp+0x0
// SVM lock (sub_5649F0); returns 1.
void sub_585540(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585540
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x585548u, gen::fn_sub_5649F0_005649f0);
    ld(ra, sp, 0x0);
    v0 = 1;
    sp = addiu(sp, 0x10);
}

// 0x00585560 sub_585560 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: SVM unlock (sub_564A68).
void sub_585560(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00585560
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564A68_00564a68(ctx);  // tail call
}

// 0x00585640 powl_11 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: sub_540570 (FLIRT misname).
void powl_11(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00585640
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_540570_00540570(ctx);  // tail call
}

// 0x00585670 sinhl_11 -- 36 bytes; frame 0x10: ra sp+0x0
// Returns sub_5990A8() != 1 (FLIRT misname).
void sinhl_11(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585670
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x585678u, gen::fn_sub_5990A8_005990a8);
    v0 = v0 ^ 0x1;
    ld(ra, sp, 0x0);
    v0 = sltu(0, v0);
    sp = addiu(sp, 0x10);
}

// 0x00585D38 sub_585D38 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: the MWSFD vsync work (r_lock_def_get_free_item_3, 0x585C90).
void sub_585D38(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00585d38
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_r_lock_def_get_free_item_3_00585c90(ctx);  // tail call
}

// 0x00585D50 sub_585D50 -- 88 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Stores $a0..$a3 in the MWSFD work record (mwsfdGetWork, 0x7B2F50) at +64 / +68 / +72 / +76.
void sub_585D50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585d50
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a3;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    s3 = a2;
    jal(ctx, 0x585D74u, gen::fn___gthread_get_ee_key_use_0057f740);
    sw(s0, v0, 76);
    sw(s1, v0, 64);
    sw(s2, v0, 68);
    sw(s3, v0, 72);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00585E08 sub_585E08 -- 56 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Stores $a0 / $a1 in the MWSFD work record (0x7B2F50) at +80 / +84.
void sub_585E08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00585e08
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x585E1Cu, gen::fn___gthread_get_ee_key_use_0057f740);
    sw(s0, v0, 84);
    sw(s1, v0, 80);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005860B0 sub_5860B0 -- 32 bytes; frame 0x10: ra sp+0x0
// Runs the MWSFD vsync work (0x585C90) and returns 0.
void sub_5860B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005860b0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x5860B8u, gen::fn_r_lock_def_get_free_item_3_00585c90);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x005860D0 sub_5860D0 -- 24 bytes; frame 0x10: ra sp+0x0
// The MWSFD decode server (sub_585E70) with $a0 = 0 (tail call).
void sub_5860D0(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005860d0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_585E70_00585e70(ctx);  // tail call
}

// 0x00586148 sub_586148 -- 8 bytes; leaf frame (no stack)
// Returns the player's word +100.
void sub_586148(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00586148
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 100);
}

// 0x00586150 sub_586150 -- 100 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Handle check (sub_581798; on failure the error printer sub_585590 with E2011101: returns 0); else returns the player's 'in server' word
// (+96, tie__..., 0x586138) != 1.
void sub_586150(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586150
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x586160u, gen::fn_sub_581798_00581798);
    s1 = v0;
    v0 = 1;
    a0 = s0;
    if (s1 == v0) {
        // 0x00586190
        charge(ctx, 4);
        jal(ctx, 0x586190u, gen::fn_tie__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_00586138);
        v0 = v0 ^ s1;
        v0 = sltu(0, v0);
    } else {
        // 0x00586178
        charge(ctx, 5);
        a0 = 0x7D0000;
        a0 = addiu(a0, -25280);  // "E2011101: MWSFSVR_IsSvrBdrHndl: handle is invalid."
        jal(ctx, 0x58617Cu, gen::fn_sub_585590_00585590);
        v0 = 0;
    }
    // 0x005861a0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005861F8 rdbuf__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_0 -- 8 bytes; leaf frame (no stack)
// Returns the player's word +92 (FLIRT misname).
void rdbuf__CQ24_STLt9basic_ios2ZcZQ24_STLt11char_traits1Zc_0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005861f8
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, 92);
}

// 0x00586220 sub_586220 -- 36 bytes; frame 0x10: ra sp+0x0
// Returns sub_586110() != 1.
void sub_586220(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586220
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x586228u, gen::fn_sub_586110_00586110);
    v0 = v0 ^ 0x1;
    ld(ra, sp, 0x0);
    v0 = sltu(0, v0);
    sp = addiu(sp, 0x10);
}

// 0x00586298 ctime -- 32 bytes; frame 0x10: ra sp+0x0
// Stops the player's ADXT (+64, _M_numpunct_facet__..) with sfdAdxtStop (0x5865C0) (FLIRT misname).
void ctime(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586298
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x5862A0u, gen::fn__M_numpunct_facet__CQ24_STL8ios_base_005816e0);
    ld(ra, sp, 0x0);
    a0 = v0;
    sp = addiu(sp, 0x10);
    gen::fn_R_LOCK_DEF_lock_free_4_005865c0(ctx);  // tail call
}

// 0x005862B8 sub_5862B8 -- 44 bytes; frame 0x10: ra sp+0x0
// Returns sub_586490(the player's ADXT, +64) != 1.
void sub_5862B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005862b8
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x5862C0u, gen::fn__M_numpunct_facet__CQ24_STL8ios_base_005816e0);
    a0 = v0;
    jal(ctx, 0x5862C8u, gen::fn_sub_586490_00586490);
    v0 = v0 ^ 0x1;
    ld(ra, sp, 0x0);
    v0 = sltu(0, v0);
    sp = addiu(sp, 0x10);
}

// 0x005862E8 sub_5862E8 -- 8 bytes; leaf frame (no stack)
// Returns 0 (an empty method-table slot).
void sub_5862E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x005862e8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x005862F8 sub_5862F8 -- 8 bytes; leaf frame (no stack)
// Returns 0 (an empty method-table slot).
void sub_5862F8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x005862f8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00586338 sub_586338 -- 160 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ADXSTM seek: origin 0 seeks to $a1 sectors (sub_5463A8), 1 to the read position (sub_546410) + $a1, 2 to the
// byte size (sub_547068) in 2 KiB sectors (rounded up, signed) + $a1; other origins do nothing. Returns 0.
void sub_586338(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586338
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    if (a2 != 0) {
        // 0x00586368
        charge(ctx, 3);
        v0 = 1;
        if (a2 != v0) {
            v0 = 2;
            // 0x00586390
            charge(ctx, 2);
            if (a2 != v0) {
                ld(s0, sp, 0x0);
            } else {
                // 0x00586398
                charge(ctx, 11);
                jal(ctx, 0x586398u, gen::fn_sub_547068_00547068);
                a0 = s0;
                a1 = addiu(v0, 2047);
                v0 = addiu(v0, 4094);
                v1 = slti(a1, 0);
                if (v1 != 0) a1 = v0;
                a1 = sra(a1, 11);
                a1 = addu(a1, s1);
                jal(ctx, 0x5863B8u, gen::fn_sub_5463A8_005463a8);
                ld(s0, sp, 0x0);
            }
        } else {
            // 0x00586374
            charge(ctx, 7);
            jal(ctx, 0x586374u, gen::fn_sub_546410_00546410);
            a0 = s0;
            a1 = addu(v0, s1);
            jal(ctx, 0x586380u, gen::fn_sub_5463A8_005463a8);
            ld(s0, sp, 0x0);
        }
    } else {
        // 0x00586354
        charge(ctx, 4);
        jal(ctx, 0x586354u, gen::fn_sub_5463A8_005463a8);
        ld(s0, sp, 0x0);
    }
    // 0x005863c4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = 0;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005863D8 r_lock_def_free_4 -- 32 bytes; frame 0x10: ra sp+0x0
// ADXSTM release (sub_546498); returns 0 (FLIRT misname).
void r_lock_def_free_4(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005863d8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x5863E0u, gen::fn_sub_546498_00546498);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x00586420 sub_586420 -- 8 bytes; leaf frame (no stack)
// Does nothing (an empty method-table slot).
void sub_586420(EEContext& ctx) {
    using namespace hg;
    // 0x00586420
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x005864D8 sub_5864D8 -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// ADXSTM start: stop (sub_546270), set the file ($a0, $a1, 0, 0, 0xFFFFF: sub_5460E0), start (sub_546718 0xFFFFF).
void sub_5864D8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005864d8
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x5864ECu, gen::fn_sub_546270_00546270);
    t0 = 0xF0000;
    a0 = s1;
    a1 = s0;
    a2 = 0;
    a3 = 0;
    t0 = t0 | 0xFFFF;
    jal(ctx, 0x586508u, gen::fn_sub_5460E0_005460e0);
    a0 = s1;
    a1 = 0xF0000;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    a1 = a1 | 0xFFFF;
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_546718_00546718(ctx);  // tail call
}

// 0x005865E8 sub_5865E8 -- 40 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// ADXSTM stop and wait (sub_546638), then close $a0 (sub_5462E0).
void sub_5865E8(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005865e8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5865F4u, gen::fn_sub_546638_00546638);
    ld(ra, sp, 0x8);
    a0 = s0;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5462E0_005462e0(ctx);  // tail call
}

// 0x00586688 sub_586688 -- 32 bytes; leaf frame (no stack)
// Header size query: *$a2 = 18; with 18 bytes or more ($a1) reads the first byte and enters R_LOCK_DEF_add_4
// (0x5866A8) with $v1 = 128; with fewer, R_LOCK_DEF_add_4's tail at 0x5866BC with $v0 = 0.
void sub_586688(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00586688
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 18;
    a1 = slti(a1, 18);
    sw(v0, a2, 0);
    a2 = a0;
    v0 = 0;
    if (a1 != 0) {
        gen::fn_R_LOCK_DEF_add_4_005866a8_at_005866bc(ctx);  // tail call
        return;
    }
    // 0x005866a0
    charge(ctx, 2);
    lbu(a0, a2, 0);
    v1 = 128;
    gen::fn_R_LOCK_DEF_add_4_005866a8(ctx);  // tail call
}

// 0x00586898 sub_586898 -- 40 bytes; frame 0x10: ra sp+0x0
// Decrements the counter 0x78FF88 (sub_541D00), then sub_53EC20; returns 0.
void sub_586898(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586898
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x5868A0u, gen::fn_sub_541D00_00541d00);
    jal(ctx, 0x5868A8u, gen::fn_sub_53EC20_0053ec20);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00587DC0 R_LOCK_DEF_ctx_new_5 -- 8 bytes; leaf frame (no stack)
// Returns 0 (an empty method-table slot; FLIRT misname).
void R_LOCK_DEF_ctx_new_5(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00587dc0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00587E10 sub_587E10 -- 240 bytes; frame 0x50: s4 sp+0x40, s0 sp+0x20, s1 sp+0x28, s2 sp+0x30, s3 sp+0x38, ra sp+0x48
// ADX stream input control ($a1): 0 clears the work's counter +48 and 1 keeps it, both then run the reset
// at 0x587F50; 2, when sub_5876F0 on the decoder (work +0) is nonzero, takes the sample rate (ADXT_GetSfreq
// sub_548F40), lets sub_587FD8 fill a count, adds it to +48 less what sub_54A710 returns for the sum,
// and queues {count, rate} into the object's ring at +4128 (sub_59BE98). Returns 0.
void sub_587E10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587e10
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    v1 = a1;
    sd(s4, sp, 0x40);
    s4 = a0;
    sd(s0, sp, 0x20);
    v0 = 1;
    sd(s1, sp, 0x28);
    sd(s2, sp, 0x30);
    sd(s3, sp, 0x38);
    sd(ra, sp, 0x48);
    lw(s3, s4, l15::adxs::kWork);
    lw(s2, s3, 0);
    if (v1 != v0) {
        // 0x00587e44
        charge(ctx, 2);
        if (v1 == 0) {
            sw(zero, s3, 48);
            // 0x00587e60
            charge(ctx, 1);
            a1 = 0;
            goto L_00587e64;
        }
        // 0x00587e4c
        charge(ctx, 3);
        v0 = 2;
        ld(s0, sp, 0x20);
        if (v1 == v0) {
            // 0x00587e78
            charge(ctx, 4);
            a0 = s2;
            jal(ctx, 0x587E78u, gen::fn_sub_5876F0_005876f0);
            ld(s0, sp, 0x20);
            if (v0 != 0) {
                // 0x00587e88
                charge(ctx, 22);
                a0 = s2;
                jal(ctx, 0x587E88u, gen::fn_sub_548F40_00548f40);
                a0 = s4;
                s1 = v0;
                a1 = addiu(sp, 0x10);
                a2 = s1;
                jal(ctx, 0x587E9Cu, gen::fn_sub_587FD8_00587fd8);
                lw(v0, s3, 48);
                lw(s0, sp, 0x10);
                a0 = s2;
                s0 = addu(s0, v0);
                a1 = s0;
                jal(ctx, 0x587EB4u, gen::fn_sub_54A710_0054a710);
                a0 = addiu(s4, 4128);
                s0 = subu(s0, v0);
                a1 = sp;
                sw(s0, s3, 48);
                sd(s1, sp, 0x8);
                lw(v0, sp, 0x10);
                link(ctx, 0x587ED4u);  // $ra first: the delay slot below depends on it
                sd(v0, sp, 0x0);
                call(ctx, gen::fn_sub_59BE98_0059be98);
                ld(s0, sp, 0x20);
            }
        L_00587ee0:
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x00587e58
            charge(ctx, 2);
            v0 = 0;
        }
        // 0x00587ee4 (the shared epilogue, written out on this path)
        charge(ctx, 7);
        ld(s1, sp, 0x28);
        ld(s2, sp, 0x30);
        ld(s3, sp, 0x38);
        ld(s4, sp, 0x40);
        ld(ra, sp, 0x48);
        sp = addiu(sp, 0x50);
        return;
    }
L_00587e64:
    charge(ctx, 4);
    link(ctx, 0x587E64u);
    gen::fn_R_LOCK_DEF_lock_new_5_00587f00_at_00587f50(ctx);
    ld(s0, sp, 0x20);
    goto L_00587ee0;
}

// 0x00588028 sub_588028 -- 28 bytes; frame 0x10: ra sp+0x0
// Raises SFD error 0xFF000C03 on the handle (sub_58BE40, tail call): an unsupported slot of a method table.
void sub_588028(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588028
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0xC03;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x00588048 sub_588048 -- 28 bytes; frame 0x10: ra sp+0x0
// Raises SFD error 0xFF000C03 on the handle (sub_58BE40, tail call): a second slot of the same table.
void sub_588048(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588048
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0xC03;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x00588068 sub_588068 -- 28 bytes; frame 0x10: ra sp+0x0
// Raises SFD error 0xFF000C03 on the handle (sub_58BE40, tail call): a third slot of the same table.
void sub_588068(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588068
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0xC03;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x00588088 sub_588088 -- 28 bytes; frame 0x10: ra sp+0x0
// Raises SFD error 0xFF000C03 on the handle (sub_58BE40, tail call): a fourth slot of the same table.
void sub_588088(EEContext& ctx) {
    using namespace hg;
    Gpr a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588088
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = lui(0xFF00);
    sd(ra, sp, 0x0);
    a1 = a1 | 0xC03;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x005880A8 sub_5880A8 -- 140 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Starts the ADX stream's decoder once: with the audio format record (sub_588138) present, a decoder not yet
// started (work +52 == 0) and a format word +0, sets it up (sub_53ED00 with the record's +12 / +16 / +20),
// clears the time offset (sub_54A880 0), marks +52 = 1 and installs the step sub_587100 at +60. Returns 0.
void sub_5880A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005880a8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x5880B8u, gen::fn_sub_588138_00588138);
    a2 = v0;
    if (a2 == 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x005880cc
        charge(ctx, 5);
        lw(s0, s0, l15::adxs::kWork);
        v0 = 0;
        lw(v1, s0, 52);
        lw(s1, s0, 0);
        if (v1 == 0) {
            // 0x005880e0
            charge(ctx, 3);
            lw(v1, a2, 0);
            a0 = s1;
            if (v1 != 0) {
                // 0x005880ec
                charge(ctx, 13);
                lw(a3, a2, 20);
                lw(a1, a2, 12);
                link(ctx, 0x5880F4u);  // $ra first: the delay slot below depends on it
                lw(a2, a2, 16);
                call(ctx, gen::fn_sub_53ED00_0053ed00);
                a0 = s1;
                a1 = 0;
                jal(ctx, 0x588100u, gen::fn_sub_54A880_0054a880);
                v0 = 1;
                v1 = 0x580000;
                sw(v0, s0, 52);
                v1 = addiu(v1, 28928);  // &sub_587100
                v0 = 0;
                sw(v1, s0, 60);
            }
        }
        // 0x00588120
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    }
    // 0x00588124 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005883C0 sub_5883C0 -- 8 bytes; leaf frame (no stack)
// Returns 0 (an empty method-table slot).
void sub_5883C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x005883c0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00588C10 sub_588C10 -- 136 bytes; leaf frame (no stack)
// Sets up the PCM ring of SFD stream lane $a1 (SfdHandle + 4880 + 116 x lane, the record at lane +16): the
// buffer size (+20) split per channel when $a3 >= 2, sample bits $a2 (+28), channels $a3 (+32), $t0 (+24),
// the two channel bases (+36 = base, +40 = base + size) and the capacity in samples (+44 = size / bytes per
// sample; a zero divisor breaks). Returns the second base.
void sub_588C10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x00588c10
    enter(ctx, 18);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    t3 = a2;
    v0 = subu(v0, a1);
    v1 = addiu(t3, 7);
    v0 = sll(v0, 2);
    t2 = a3;
    v0 = addu(v0, a1);
    a2 = slti(v1, 0);
    v0 = sll(v0, 2);
    a3 = addiu(t3, 14);
    a0 = addu(a0, v0);
    if (a2 != 0) v1 = a3;
    a0 = addiu(a0, 4896);
    t1 = slti(t2, 2);
    a1 = sra(v1, 3);
    lw(v0, a0, 4);
    lw(a2, a0, 0);
    if (t1 == 0) {
        // 0x00588c58
        charge(ctx, 3);
        div(v0, t2);
        if (t2 == 0) {
            brk(ctx, 0x588C60u, 0x7u);
        }
        // 0x00588c64
        charge(ctx, 1);
        mflo(v0);
    }
    // 0x00588c68
    charge(ctx, 9);
    div(v0, a1);
    v0 = addu(a2, v0);
    sw(t3, a0, 12);
    sw(t2, a0, 16);
    sw(t0, a0, 8);
    sw(a2, a0, 20);
    sw(v0, a0, 24);
    if (a1 == 0) {
        brk(ctx, 0x588C88u, 0x7u);
    }
    // 0x00588c8c
    charge(ctx, 3);
    mflo(v1);
    sw(v1, a0, 28);
}

// 0x00588FD8 sub_588FD8 -- 36 bytes; leaf frame (no stack)
// *$a2 = the buffer size of SFD stream lane $a1 (lane +20); $v0 keeps 116 x lane.
void sub_588FD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00588fd8
    enter(ctx, 9);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    v0 = subu(v0, a1);
    v0 = sll(v0, 2);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    lw(v1, a0, 4900);
    sw(v1, a2, 0);
}

// 0x00589688 sub_589688 -- 424 bytes; frame 0x70: s5 sp+0x48, s0 sp+0x20, s1 sp+0x28, s2 sp+0x30, s3 sp+0x38, s4 sp+0x40, s6 sp+0x50, s7 sp+0x58, fp sp+0x60, ra sp+0x68
// The writable area of lane $a1's PCM ring into the 11-word record $a2 (0xFF000401 when the lane is unused,
// lane +4 == 0): under the SFD lock (sub_58C100 / sub_58C118) copies the format words, then, when the written
// total (+56) is below the read total (+60) + capacity, the first piece from the write index (+48) to the
// read index (+52) or the ring end, with 16-bit samples (bits +28 >= 9) at twice the offset, and the
// wrapped second piece; else empty. the second base (+40) is held in $a1 across
// the unlock call through a quadword spill (sq / lq). Returns 0.
void sub_589688(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00589688
    enter(ctx, 21);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    sp = addiu(sp, -0x70);
    v0 = subu(v0, a1);
    sd(s5, sp, 0x48);
    v0 = sll(v0, 2);
    sd(s0, sp, 0x20);
    v0 = addu(v0, a1);
    sd(s1, sp, 0x28);
    sd(s2, sp, 0x30);
    a3 = addiu(a0, 4880);
    sd(s3, sp, 0x38);
    v0 = sll(v0, 2);
    sd(s4, sp, 0x40);
    a3 = addu(a3, v0);
    sd(s6, sp, 0x50);
    sd(s7, sp, 0x58);
    sd(fp, sp, 0x60);
    sd(ra, sp, 0x68);
    lw(v1, a3, 4);
    s5 = a2;
    if (v1 != 0) {
        // 0x005896f0
        charge(ctx, 27);
        s0 = addiu(a3, 16);
        a0 = sp;
        jal(ctx, 0x5896F4u, gen::fn_sub_58C100_0058c100);
        lw(v0, s0, 8);
        a0 = sp;
        sw(v0, sp, 0x4);
        lw(a1, s0, 24);
        lw(s3, s0, 44);
        lw(s4, s0, 28);
        lw(s1, s0, 40);
        lw(s7, s0, 12);
        lw(s2, s0, 16);
        lw(fp, s0, 20);
        lw(s6, s0, 32);
        sq(a1, sp, 0x10);
        link(ctx, 0x58972Cu);  // $ra first: the delay slot below depends on it
        lw(s0, s0, 36);
        call(ctx, gen::fn_sub_58C118_0058c118);
        lw(v1, sp, 0x4);
        v0 = addu(s3, s4);
        v0 = slt(s1, v0);
        sw(s2, s5, 8);
        sw(v1, s5, 0);
        sw(s7, s5, 4);
        sw(s1, s5, 36);
        sw(s3, s5, 40);
        lq(a1, sp, 0x10);
        if (v0 == 0) {
            // 0x0058975c
            charge(ctx, 5);
            sw(zero, s5, 32);
            sw(zero, s5, 12);
            sw(zero, s5, 20);
            sw(zero, s5, 24);
            goto L_005897b4;
        }
        // 0x00589770
        charge(ctx, 3);
        v0 = slt(s6, s0);
        if (v0 == 0) {
            v0 = subu(s4, s6);
            // 0x005897c0
            charge(ctx, 4);
            v1 = slti(s7, 9);
            sw(v0, s5, 12);
            v0 = addu(fp, s6);
            if (v1 == 0) {
                // 0x005897d0
                charge(ctx, 2);
                v0 = sll(s6, 1);
                v0 = addu(fp, v0);
            }
            // 0x005897d8
            charge(ctx, 3);
            sw(v0, s5, 20);
            v0 = addu(a1, s6);
            if (v1 == 0) {
                // 0x005897e4
                charge(ctx, 2);
                v0 = sll(s6, 1);
                v0 = addu(a1, v0);
            }
            // 0x005897ec
            charge(ctx, 4);
            sw(a1, s5, 32);
            sw(v0, s5, 24);
            sw(s0, s5, 16);
            sw(fp, s5, 28);
        } else {
            // 0x0058977c
            charge(ctx, 5);
            v0 = subu(s0, s6);
            v1 = slti(s7, 9);
            sw(v0, s5, 12);
            v0 = addu(fp, s6);
            if (v1 == 0) {
                // 0x00589790
                charge(ctx, 2);
                v0 = sll(s6, 1);
                v0 = addu(fp, v0);
            }
            // 0x00589798
            charge(ctx, 3);
            sw(v0, s5, 20);
            v0 = addu(a1, s6);
            if (v1 == 0) {
                // 0x005897a4
                charge(ctx, 2);
                v0 = sll(s6, 1);
                v0 = addu(a1, v0);
            }
            // 0x005897ac
            charge(ctx, 2);
            sw(v0, s5, 24);
            sw(zero, s5, 32);
        L_005897b4:
            charge(ctx, 3);
            sw(zero, s5, 16);
            sw(zero, s5, 28);
        }
        // 0x005897fc
        charge(ctx, 2);
        v0 = 0;
        ld(s0, sp, 0x20);
    } else {
        // 0x005896dc
        charge(ctx, 5);
        a1 = lui(0xFF00);
        a1 = a1 | 0x401;
        jal(ctx, 0x5896E0u, gen::fn_sub_58BE40_0058be40);
        ld(s0, sp, 0x20);
    }
    // 0x00589804 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(s6, sp, 0x50);
    ld(s7, sp, 0x58);
    ld(fp, sp, 0x60);
    ld(ra, sp, 0x68);
    sp = addiu(sp, 0x70);
}

// 0x00589830 sub_589830 -- 244 bytes; frame 0x40: s2 sp+0x20, s1 sp+0x18, s3 sp+0x28, s0 sp+0x10, ra sp+0x30
// Commits $a2 written samples to lane $a1's PCM ring: the write index (+48) advances with wrap, the written
// total (+56) grows, and passing the read total + capacity raises 0xFF000406; sets the handle's +68 = 1
// (under the SFD lock). 0 samples do nothing; an unused lane raises 0xFF000401.
void sub_589830(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00589830
    enter(ctx, 18);  // entry check point + this block's cycles
    v1 = sll(a1, 3);
    sp = addiu(sp, -0x40);
    v1 = subu(v1, a1);
    sd(s2, sp, 0x20);
    v1 = sll(v1, 2);
    s2 = a0;
    v1 = addu(v1, a1);
    sd(s1, sp, 0x18);
    v1 = sll(v1, 2);
    s1 = a2;
    a2 = addiu(s2, 4880);
    sd(s3, sp, 0x28);
    sd(s0, sp, 0x10);
    v0 = 0;
    sd(ra, sp, 0x30);
    s3 = 0;
    a2 = addu(a2, v1);
    if (s1 != 0) {
        // 0x00589878
        charge(ctx, 3);
        lw(v0, a2, 4);
        if (v0 != 0) {
            s0 = addiu(a2, 16);
            // 0x00589898
            charge(ctx, 12);
            a0 = sp;
            jal(ctx, 0x589898u, gen::fn_sub_58C100_0058c100);
            a0 = s2;
            lw(v0, s0, 32);
            a1 = lui(0xFF00);
            lw(a2, s0, 28);
            a1 = a1 | 0x406;
            v0 = addu(v0, s1);
            v1 = slt(v0, a2);
            a3 = subu(v0, a2);
            sw(v0, s0, 32);
            if (v1 == 0) {
                // 0x005898c8
                charge(ctx, 1);
                sw(a3, s0, 32);
            }
            // 0x005898cc
            charge(ctx, 7);
            lw(v0, s0, 40);
            lw(v1, s0, 44);
            v0 = addu(v0, s1);
            v1 = addu(v1, a2);
            v1 = slt(v1, v0);
            sw(v0, s0, 40);
            if (v1 != 0) {
                // 0x005898e8
                charge(ctx, 3);
                jal(ctx, 0x5898E8u, gen::fn_sub_58BE40_0058be40);
                s3 = v0;
            }
            // 0x005898f4
            charge(ctx, 5);
            v0 = 1;
            a0 = sp;
            link(ctx, 0x5898FCu);  // $ra first: the delay slot below depends on it
            sw(v0, s2, 68);
            call(ctx, gen::fn_sub_58C118_0058c118);
            v0 = s3;
            goto L_00589908;
        }
        // 0x00589884
        charge(ctx, 5);
        a1 = lui(0xFF00);
        a1 = a1 | 0x401;
        jal(ctx, 0x589888u, gen::fn_sub_58BE40_0058be40);
        ld(s0, sp, 0x10);
        // 0x0058990c (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s1, sp, 0x18);
        ld(s2, sp, 0x20);
        ld(s3, sp, 0x28);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        return;
    }
L_00589908:
    charge(ctx, 1);
    ld(s0, sp, 0x10);
    // 0x0058990c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00589928 sub_589928 -- 432 bytes; frame 0x60: s5 sp+0x38, s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30, s6 sp+0x40, s7 sp+0x48, fp sp+0x50, ra sp+0x58
// The readable area of lane $a1's PCM ring into the 11-word record $a2 (0xFF000401 when the lane is unused):
// under the SFD lock copies the format words, then, when the read total (+60) is below the written total
// (+56), the first piece from the read index (+52) to the write index or the ring end (16-bit samples at
// twice the offset) and the wrapped second piece; else empty. Returns 0.
void sub_589928(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x00589928
    enter(ctx, 21);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    sp = addiu(sp, -0x60);
    v0 = subu(v0, a1);
    sd(s5, sp, 0x38);
    v0 = sll(v0, 2);
    sd(s0, sp, 0x10);
    v0 = addu(v0, a1);
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    a3 = addiu(a0, 4880);
    sd(s3, sp, 0x28);
    v0 = sll(v0, 2);
    sd(s4, sp, 0x30);
    a3 = addu(a3, v0);
    sd(s6, sp, 0x40);
    sd(s7, sp, 0x48);
    sd(fp, sp, 0x50);
    sd(ra, sp, 0x58);
    lw(v1, a3, 4);
    s5 = a2;
    if (v1 != 0) {
        // 0x00589990
        charge(ctx, 24);
        s0 = addiu(a3, 16);
        a0 = sp;
        jal(ctx, 0x589994u, gen::fn_sub_58C100_0058c100);
        lw(s4, s0, 8);
        lw(v0, s0, 28);
        a0 = sp;
        lw(s3, s0, 44);
        lw(s1, s0, 40);
        lw(s6, s0, 12);
        lw(s2, s0, 16);
        lw(s7, s0, 20);
        lw(fp, s0, 24);
        sw(v0, sp, 0x4);
        lw(v1, s0, 32);
        sw(v1, sp, 0x8);
        link(ctx, 0x5899CCu);  // $ra first: the delay slot below depends on it
        lw(s0, s0, 36);
        call(ctx, gen::fn_sub_58C118_0058c118);
        v0 = slt(s3, s1);
        sw(s4, s5, 0);
        sw(s2, s5, 8);
        sw(s6, s5, 4);
        sw(s1, s5, 36);
        sw(s3, s5, 40);
        if (v0 == 0) {
            // 0x005899f0
            charge(ctx, 5);
            sw(zero, s5, 32);
            sw(zero, s5, 12);
            sw(zero, s5, 20);
            sw(zero, s5, 24);
            goto L_00589a50;
        }
        // 0x00589a08
        charge(ctx, 4);
        lw(v1, sp, 0x8);
        v0 = slt(s0, v1);
        if (v0 == 0) {
            lw(v1, sp, 0x4);
            // 0x00589a60
            charge(ctx, 5);
            v0 = subu(v1, s0);
            v1 = slti(s6, 9);
            sw(v0, s5, 12);
            v0 = addu(s7, s0);
            if (v1 == 0) {
                // 0x00589a74
                charge(ctx, 2);
                v0 = sll(s0, 1);
                v0 = addu(s7, v0);
            }
            // 0x00589a7c
            charge(ctx, 3);
            sw(v0, s5, 20);
            v0 = addu(fp, s0);
            if (v1 == 0) {
                // 0x00589a88
                charge(ctx, 2);
                v0 = sll(s0, 1);
                v0 = addu(fp, v0);
            }
            // 0x00589a90
            charge(ctx, 5);
            sw(fp, s5, 32);
            sw(v0, s5, 24);
            lw(v0, sp, 0x8);
            sw(s7, s5, 28);
            sw(v0, s5, 16);
        } else {
            // 0x00589a18
            charge(ctx, 5);
            v0 = subu(v1, s0);
            v1 = slti(s6, 9);
            sw(v0, s5, 12);
            v0 = addu(s7, s0);
            if (v1 == 0) {
                // 0x00589a2c
                charge(ctx, 2);
                v0 = sll(s0, 1);
                v0 = addu(s7, v0);
            }
            // 0x00589a34
            charge(ctx, 3);
            sw(v0, s5, 20);
            v0 = addu(fp, s0);
            if (v1 == 0) {
                // 0x00589a40
                charge(ctx, 2);
                v0 = sll(s0, 1);
                v0 = addu(fp, v0);
            }
            // 0x00589a48
            charge(ctx, 2);
            sw(v0, s5, 24);
            sw(zero, s5, 32);
        L_00589a50:
            charge(ctx, 3);
            sw(zero, s5, 16);
            sw(zero, s5, 28);
        }
        // 0x00589aa4
        charge(ctx, 2);
        v0 = 0;
        ld(s0, sp, 0x10);
    } else {
        // 0x0058997c
        charge(ctx, 5);
        a1 = lui(0xFF00);
        a1 = a1 | 0x401;
        jal(ctx, 0x589980u, gen::fn_sub_58BE40_0058be40);
        ld(s0, sp, 0x10);
    }
    // 0x00589aac (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(s6, sp, 0x40);
    ld(s7, sp, 0x48);
    ld(fp, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
}

// 0x00589AD8 sub_589AD8 -- 240 bytes; frame 0x40: s2 sp+0x20, s1 sp+0x18, s3 sp+0x28, s0 sp+0x10, ra sp+0x30
// Commits $a2 read samples from lane $a1's PCM ring: the read index (+52) advances with wrap, the read total
// (+60) grows, and passing the written total raises 0xFF000407; sets the handle's +68 = 1 (under the SFD
// lock). 0 samples do nothing; an unused lane raises 0xFF000401.
void sub_589AD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00589ad8
    enter(ctx, 18);  // entry check point + this block's cycles
    v1 = sll(a1, 3);
    sp = addiu(sp, -0x40);
    v1 = subu(v1, a1);
    sd(s2, sp, 0x20);
    v1 = sll(v1, 2);
    s2 = a0;
    v1 = addu(v1, a1);
    sd(s1, sp, 0x18);
    v1 = sll(v1, 2);
    s1 = a2;
    a2 = addiu(s2, 4880);
    sd(s3, sp, 0x28);
    sd(s0, sp, 0x10);
    v0 = 0;
    sd(ra, sp, 0x30);
    s3 = 0;
    a2 = addu(a2, v1);
    if (s1 != 0) {
        // 0x00589b20
        charge(ctx, 3);
        lw(v0, a2, 4);
        if (v0 != 0) {
            s0 = addiu(a2, 16);
            // 0x00589b40
            charge(ctx, 12);
            a0 = sp;
            jal(ctx, 0x589B40u, gen::fn_sub_58C100_0058c100);
            a0 = s2;
            lw(v0, s0, 36);
            a1 = lui(0xFF00);
            lw(v1, s0, 28);
            a1 = a1 | 0x407;
            v0 = addu(v0, s1);
            a2 = subu(v0, v1);
            v1 = slt(v0, v1);
            sw(v0, s0, 36);
            if (v1 == 0) {
                // 0x00589b70
                charge(ctx, 1);
                sw(a2, s0, 36);
            }
            // 0x00589b74
            charge(ctx, 6);
            lw(v0, s0, 44);
            lw(v1, s0, 40);
            v0 = addu(v0, s1);
            v1 = slt(v1, v0);
            sw(v0, s0, 44);
            if (v1 != 0) {
                // 0x00589b8c
                charge(ctx, 3);
                jal(ctx, 0x589B8Cu, gen::fn_sub_58BE40_0058be40);
                s3 = v0;
            }
            // 0x00589b98
            charge(ctx, 5);
            v0 = 1;
            a0 = sp;
            link(ctx, 0x589BA0u);  // $ra first: the delay slot below depends on it
            sw(v0, s2, 68);
            call(ctx, gen::fn_sub_58C118_0058c118);
            v0 = s3;
            goto L_00589bac;
        }
        // 0x00589b2c
        charge(ctx, 5);
        a1 = lui(0xFF00);
        a1 = a1 | 0x401;
        jal(ctx, 0x589B30u, gen::fn_sub_58BE40_0058be40);
        ld(s0, sp, 0x10);
        // 0x00589bb0 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s1, sp, 0x18);
        ld(s2, sp, 0x20);
        ld(s3, sp, 0x28);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        return;
    }
L_00589bac:
    charge(ctx, 1);
    ld(s0, sp, 0x10);
    // 0x00589bb0 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00589BC8 sub_589BC8 -- 8 bytes; leaf frame (no stack)
// Returns 0 (an empty method-table slot).
void sub_589BC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x00589bc8
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x00589BD0 sub_589BD0 -- 16 bytes; leaf frame (no stack)
// Sets the handle's word +68 = 1 and returns 0.
void sub_589BD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00589bd0
    enter(ctx, 4);  // entry check point + this block's cycles
    v0 = 1;
    sw(v0, a0, 68);
    v0 = 0;
}

// 0x00589D58 sub_589D58 -- 40 bytes; frame 0x30: ra sp+0x20
// Lane-0 chunk read (sub_589000) into a stack record; returns its words +4 + +12.
void sub_589D58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00589d58
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    a2 = sp;
    jal(ctx, 0x589D60u, gen::fn_sub_589000_00589000);
    lw(v1, sp, 0x4);
    lw(v0, sp, 0xC);
    ld(ra, sp, 0x20);
    v0 = addu(v1, v0);
    sp = addiu(sp, 0x30);
}

// 0x0058A290 sub_58A290 -- 344 bytes; frame 0x60: s0 sp+0x10, s3 sp+0x28, s4 sp+0x30, s7 sp+0x48, s1 sp+0x18, s2 sp+0x20, s5 sp+0x38, s6 sp+0x40, fp sp+0x50, ra sp+0x58
// The audio time of an SFD handle (sub_59A028) with queued entries taken off: sfdCheckHandle (sub_58C060; an invalid
// handle raises 0xFF000162 on null), *$a3 = 0, the time (sub_59A028). When the handle's word +3732 is set
// and *$a2 != 1, walks back up to 32 entries of the ring at +3740 from index +3736 (under the SFD lock):
// criMulDiv(entry, *$a2, rate +3696) until *$a1 >= it, stores the index in *$a3 and *$a1 -= that (>= 0).
void sub_58A290(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0058a290
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s3, sp, 0x28);
    s3 = a1;
    sd(s4, sp, 0x30);
    s4 = a2;
    sd(s7, sp, 0x48);
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    sd(s5, sp, 0x38);
    sd(s6, sp, 0x40);
    sd(fp, sp, 0x50);
    sd(ra, sp, 0x58);
    s7 = a3;
    jal(ctx, 0x58A2C8u, gen::fn_sub_58C060_0058c060);
    a0 = 0;
    if (v0 == 0) {
        // 0x0058a2f0
        charge(ctx, 11);
        lw(s6, s0, 3696);
        s1 = addiu(s0, 3376);
        sw(zero, s7, 0);
        a0 = s0;
        a1 = s3;
        a2 = s4;
        jal(ctx, 0x58A304u, gen::fn_sub_59A028_0059a028);
        lw(v1, s1, 356);
        fp = v0;
        s2 = 0;
        if (v1 != 0) {
            // 0x0058a31c
            charge(ctx, 4);
            lw(a0, s4, 0);
            v1 = 1;
            cc = a0 == v1;  // the condition, before the delay slot changes it
            a0 = sp;
            if (!cc) {
                // 0x0058a32c
                charge(ctx, 5);
                s5 = addiu(s0, 3388);
                jal(ctx, 0x58A32Cu, gen::fn_sub_58C100_0058c100);
                lw(s0, s1, 360);
                s1 = 0;
                for (;;) {
                    // 0x0058a340
                    charge(ctx, 3);
                    v0 = slti(s1, 32);
                    s1 = addiu(s1, 1);
                    if (v0 != 0) {
                        // 0x0058a34c
                        charge(ctx, 18);
                        a0 = addiu(s0, 31);
                        v1 = slti(s0, 0);
                        v0 = s0;
                        lw(a1, s4, 0);
                        if (v1 != 0) v0 = a0;
                        a2 = s6;
                        v0 = sra(v0, 5);
                        v0 = sll(v0, 5);
                        v0 = subu(s0, v0);
                        v0 = sll(v0, 2);
                        v0 = addu(v0, s5);
                        link(ctx, 0x58A378u);  // $ra first: the delay slot below depends on it
                        lw(a0, v0, 352);
                        call(ctx, gen::fn_sub_57BAF0_0057baf0);
                        s2 = v0;
                        lw(v0, s3, 0);
                        v0 = slt(v0, s2);
                        if (v0 != 0) {
                            s0 = addiu(s0, -1);
                            backedge(ctx);
                            continue;
                        }
                    }
                    break;
                }
                // 0x0058a394
                charge(ctx, 9);
                sw(s0, s7, 0);
                a0 = sp;
                lw(v0, s3, 0);
                v0 = subu(v0, s2);
                v1 = slti(v0, 0);
                if (v1 != 0) v0 = 0;
                link(ctx, 0x58A3ACu);  // $ra first: the delay slot below depends on it
                sw(v0, s3, 0);
                call(ctx, gen::fn_sub_58C118_0058c118);
                v0 = fp;
            }
        }
        // 0x0058a3b8
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    } else {
        // 0x0058a2d8
        charge(ctx, 5);
        a1 = lui(0xFF00);
        a1 = a1 | 0x162;
        jal(ctx, 0x58A2DCu, gen::fn_sub_58BE40_0058be40);
        ld(s0, sp, 0x10);
    }
    // 0x0058a3bc (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(s6, sp, 0x40);
    ld(s7, sp, 0x48);
    ld(fp, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
}

// 0x0058AC78 sub_58AC78 -- 120 bytes; frame 0x20: ra sp+0x10
// MPEG audio bit rate: decodes the first header in ($a0, $a1) with sub_58AE50; returns 1000 x the kbit/s of
// the table 0x7C9E50[16 x layer + index] (32..448), or -1 for no header or a free / bad index.
void sub_58AC78(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058ac78
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = a0;
    a2 = a1;
    a1 = v0;
    sd(ra, sp, 0x10);
    a0 = sp;
    jal(ctx, 0x58AC8Cu, gen::fn_sub_58AE50_0058ae50);
    a1 = si(-1);
    if (v0 != 0) {
        // 0x0058aca8
        charge(ctx, 11);
        lbu(v1, sp, 0x0);
        v0 = si(-1);
        lbu(a0, sp, 0x2);
        v1 = sll(v1, 4);
        v1 = addu(v1, a0);
        v1 = sll(v1, 2);
        at = 0x7D0000;
        at = addu(at, v1);
        lw(v1, at, -25008);
        a0 = sll(v1, 5);
        if (v1 != a1) {
            // 0x0058acd4
            charge(ctx, 4);
            v0 = subu(a0, v1);
            v0 = sll(v0, 2);
            v0 = addu(v0, v1);
            v0 = sll(v0, 3);
        }
    } else {
        // 0x0058ac9c
        charge(ctx, 2);
        v0 = si(-1);
    }
    // 0x0058ace4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0058ACF0 sub_58ACF0 -- 180 bytes; frame 0x20: ra sp+0x10
// MPEG audio frame size in bytes: decodes the first header in ($a0, $a1) with sub_58AE50; returns
// 1000 x samples per frame (0x7C9F50[layer]: 1152 / 1152 / 384) x kbit/s / (8 x rate 0x7C9E40[index]:
// 44100 / 48000 / 32000), or -1. A zero rate breaks.
void sub_58ACF0(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058acf0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = a0;
    a2 = a1;
    a1 = v0;
    sd(ra, sp, 0x10);
    a0 = sp;
    jal(ctx, 0x58AD04u, gen::fn_sub_58AE50_0058ae50);
    a2 = si(-1);
    if (v0 != 0) {
        // 0x0058ad20
        charge(ctx, 11);
        lbu(v1, sp, 0x0);
        lbu(a0, sp, 0x2);
        a1 = sll(v1, 2);
        v1 = sll(v1, 4);
        v1 = addu(v1, a0);
        v1 = sll(v1, 2);
        at = 0x7D0000;
        at = addu(at, v1);
        lw(v1, at, -25008);
        v0 = si(-1);
        if (v1 != a2) {
            // 0x0058ad4c
            charge(ctx, 14);
            a0 = 0x7D0000;
            a0 = addu(a0, a1);
            lw(a0, a0, -24752);
            lbu(v0, sp, 0x3);
            mult(a0, a0, v1);
            v0 = sll(v0, 2);
            v1 = 0x7D0000;
            v1 = addu(v1, v0);
            lw(v1, v1, -25024);
            v0 = sll(a0, 5);
            v1 = sll(v1, 3);
            v0 = subu(v0, a0);
            if (v1 == 0) {
                brk(ctx, 0x58AD80u, 0x7u);
            }
            // 0x0058ad84
            charge(ctx, 5);
            v0 = sll(v0, 2);
            v0 = addu(v0, a0);
            v0 = sll(v0, 3);
            div(v0, v1);
            mflo(v0);
        }
    } else {
        // 0x0058ad14
        charge(ctx, 2);
        v0 = si(-1);
    }
    // 0x0058ad98 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

}  // namespace p3fes::game
