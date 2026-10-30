// Phase 5 slice libs12: the CRI Sofdec band 0x580588-0x58FF70 (150 functions; libs12.h has each one's role). The
// bodies started from p3fes_handgen (SLUS_216.21 and symbols/) and keep the recompiled body's registers, frame,
// spills, $ra links, cycle charges and check points (game/include/p3fes/game/hg_cpu.h); on top of that each carries
// its role and, where the binary prints it, a proposed name, and the loads and stores of the MWSFD player, the SFD
// stream records and the transfer slots use the named offsets of libs5.h / libs12.h (each equals the literal it
// replaced). Pair tests: tests/game/test_libs12.cpp.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs12.h"

namespace p3fes::recomp_gen {
void fn_R_LOCK_DEF_w_lock_7_0058edb0(p3fes::EEContext&);
void fn__M_numpunct_facet__CQ24_STL8ios_base_005816e0(p3fes::EEContext&);
void fn___env_lock_12_0058c0f0(p3fes::EEContext&);
void fn_atan2l_12_0058c088(p3fes::EEContext&);
void fn_coshl_12_0058c0b8(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_r_lock_def_get_free_item_6_0058c3a0(p3fes::EEContext&);
void fn_r_lock_def_get_free_item_7_0058ea60(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_19_005851a0(p3fes::EEContext&);
void fn_sub_53DD10_0053dd10(p3fes::EEContext&);
void fn_sub_547558_00547558(p3fes::EEContext&);
void fn_sub_54ABA8_0054aba8(p3fes::EEContext&);
void fn_sub_55D600_0055d600(p3fes::EEContext&);
void fn_sub_55D668_0055d668(p3fes::EEContext&);
void fn_sub_55DB58_0055db58(p3fes::EEContext&);
void fn_sub_561970_00561970(p3fes::EEContext&);
void fn_sub_562288_00562288(p3fes::EEContext&);
void fn_sub_562388_00562388(p3fes::EEContext&);
void fn_sub_575410_00575410(p3fes::EEContext&);
void fn_sub_575880_00575880(p3fes::EEContext&);
void fn_sub_5759B0_005759b0(p3fes::EEContext&);
void fn_sub_575A00_00575a00(p3fes::EEContext&);
void fn_sub_575A50_00575a50(p3fes::EEContext&);
void fn_sub_575AA0_00575aa0(p3fes::EEContext&);
void fn_sub_5776B0_005776b0(p3fes::EEContext&);
void fn_sub_5777F8_005777f8(p3fes::EEContext&);
void fn_sub_577860_00577860(p3fes::EEContext&);
void fn_sub_577910_00577910(p3fes::EEContext&);
void fn_sub_5779A8_005779a8(p3fes::EEContext&);
void fn_sub_577A38_00577a38(p3fes::EEContext&);
void fn_sub_577C68_00577c68(p3fes::EEContext&);
void fn_sub_577DD8_00577dd8(p3fes::EEContext&);
void fn_sub_577F78_00577f78(p3fes::EEContext&);
void fn_sub_577FC8_00577fc8(p3fes::EEContext&);
void fn_sub_578060_00578060(p3fes::EEContext&);
void fn_sub_578160_00578160(p3fes::EEContext&);
void fn_sub_579240_00579240(p3fes::EEContext&);
void fn_sub_5796D0_005796d0(p3fes::EEContext&);
void fn_sub_57AFA0_0057afa0(p3fes::EEContext&);
void fn_sub_57B648_0057b648(p3fes::EEContext&);
void fn_sub_57B760_0057b760(p3fes::EEContext&);
void fn_sub_57C730_0057c730(p3fes::EEContext&);
void fn_sub_57EC00_0057ec00(p3fes::EEContext&);
void fn_sub_57F058_0057f058(p3fes::EEContext&);
void fn_sub_580270_00580270(p3fes::EEContext&);
void fn_sub_580588_00580588(p3fes::EEContext&);
void fn_sub_580628_00580628(p3fes::EEContext&);
void fn_sub_580900_00580900(p3fes::EEContext&);
void fn_sub_5809B0_005809b0(p3fes::EEContext&);
void fn_sub_580A98_00580a98(p3fes::EEContext&);
void fn_sub_580C20_00580c20(p3fes::EEContext&);
void fn_sub_580C38_00580c38(p3fes::EEContext&);
void fn_sub_580C50_00580c50(p3fes::EEContext&);
void fn_sub_580C68_00580c68(p3fes::EEContext&);
void fn_sub_580C98_00580c98(p3fes::EEContext&);
void fn_sub_5811D0_005811d0(p3fes::EEContext&);
void fn_sub_581270_00581270(p3fes::EEContext&);
void fn_sub_5812D8_005812d8(p3fes::EEContext&);
void fn_sub_581628_00581628(p3fes::EEContext&);
void fn_sub_581660_00581660(p3fes::EEContext&);
void fn_sub_581798_00581798(p3fes::EEContext&);
void fn_sub_582040_00582040(p3fes::EEContext&);
void fn_sub_582118_00582118(p3fes::EEContext&);
void fn_sub_5827D8_005827d8(p3fes::EEContext&);
void fn_sub_582828_00582828(p3fes::EEContext&);
void fn_sub_582968_00582968(p3fes::EEContext&);
void fn_sub_5829B8_005829b8(p3fes::EEContext&);
void fn_sub_582A58_00582a58(p3fes::EEContext&);
void fn_sub_582AB8_00582ab8(p3fes::EEContext&);
void fn_sub_582B88_00582b88(p3fes::EEContext&);
void fn_sub_582B98_00582b98(p3fes::EEContext&);
void fn_sub_582BA8_00582ba8(p3fes::EEContext&);
void fn_sub_583058_00583058(p3fes::EEContext&);
void fn_sub_5840D0_005840d0(p3fes::EEContext&);
void fn_sub_584190_00584190(p3fes::EEContext&);
void fn_sub_584230_00584230(p3fes::EEContext&);
void fn_sub_584290_00584290(p3fes::EEContext&);
void fn_sub_584338_00584338(p3fes::EEContext&);
void fn_sub_584830_00584830(p3fes::EEContext&);
void fn_sub_5849A0_005849a0(p3fes::EEContext&);
void fn_sub_585590_00585590(p3fes::EEContext&);
void fn_sub_586490_00586490(p3fes::EEContext&);
void fn_sub_586F20_00586f20(p3fes::EEContext&);
void fn_sub_586FE0_00586fe0(p3fes::EEContext&);
void fn_sub_587218_00587218(p3fes::EEContext&);
void fn_sub_588138_00588138(p3fes::EEContext&);
void fn_sub_588168_00588168(p3fes::EEContext&);
void fn_sub_5881F8_005881f8(p3fes::EEContext&);
void fn_sub_588270_00588270(p3fes::EEContext&);
void fn_sub_5882F0_005882f0(p3fes::EEContext&);
void fn_sub_588720_00588720(p3fes::EEContext&);
void fn_sub_588740_00588740(p3fes::EEContext&);
void fn_sub_588878_00588878(p3fes::EEContext&);
void fn_sub_5888B8_005888b8(p3fes::EEContext&);
void fn_sub_588978_00588978(p3fes::EEContext&);
void fn_sub_588A10_00588a10(p3fes::EEContext&);
void fn_sub_588A50_00588a50(p3fes::EEContext&);
void fn_sub_588AB8_00588ab8(p3fes::EEContext&);
void fn_sub_588B70_00588b70(p3fes::EEContext&);
void fn_sub_588C98_00588c98(p3fes::EEContext&);
void fn_sub_588CE8_00588ce8(p3fes::EEContext&);
void fn_sub_588D38_00588d38(p3fes::EEContext&);
void fn_sub_588DE0_00588de0(p3fes::EEContext&);
void fn_sub_588E98_00588e98(p3fes::EEContext&);
void fn_sub_588F38_00588f38(p3fes::EEContext&);
void fn_sub_588F90_00588f90(p3fes::EEContext&);
void fn_sub_589000_00589000(p3fes::EEContext&);
void fn_sub_589018_00589018(p3fes::EEContext&);
void fn_sub_589018_00589018_at_00589030(p3fes::EEContext&);
void fn_sub_5890D8_005890d8(p3fes::EEContext&);
void fn_sub_5890F0_005890f0(p3fes::EEContext&);
void fn_sub_5890F0_005890f0_at_00589108(p3fes::EEContext&);
void fn_sub_5892E8_005892e8(p3fes::EEContext&);
void fn_sub_5893E0_005893e0(p3fes::EEContext&);
void fn_sub_589438_00589438(p3fes::EEContext&);
void fn_sub_5894A8_005894a8(p3fes::EEContext&);
void fn_sub_589510_00589510(p3fes::EEContext&);
void fn_sub_589530_00589530(p3fes::EEContext&);
void fn_sub_589550_00589550(p3fes::EEContext&);
void fn_sub_5895F0_005895f0(p3fes::EEContext&);
void fn_sub_589650_00589650(p3fes::EEContext&);
void fn_sub_589CB0_00589cb0(p3fes::EEContext&);
void fn_sub_589CD0_00589cd0(p3fes::EEContext&);
void fn_sub_589CF0_00589cf0(p3fes::EEContext&);
void fn_sub_589D10_00589d10(p3fes::EEContext&);
void fn_sub_589D30_00589d30(p3fes::EEContext&);
void fn_sub_589D80_00589d80(p3fes::EEContext&);
void fn_sub_589E38_00589e38(p3fes::EEContext&);
void fn_sub_589EC8_00589ec8(p3fes::EEContext&);
void fn_sub_589F38_00589f38(p3fes::EEContext&);
void fn_sub_589F70_00589f70(p3fes::EEContext&);
void fn_sub_589FD0_00589fd0(p3fes::EEContext&);
void fn_sub_589FF0_00589ff0(p3fes::EEContext&);
void fn_sub_58A038_0058a038(p3fes::EEContext&);
void fn_sub_58AA20_0058aa20(p3fes::EEContext&);
void fn_sub_58AB08_0058ab08(p3fes::EEContext&);
void fn_sub_58ABA0_0058aba0(p3fes::EEContext&);
void fn_sub_58ADA8_0058ada8(p3fes::EEContext&);
void fn_sub_58AE50_0058ae50(p3fes::EEContext&);
void fn_sub_58AF20_0058af20(p3fes::EEContext&);
void fn_sub_58AFA0_0058afa0(p3fes::EEContext&);
void fn_sub_58B108_0058b108(p3fes::EEContext&);
void fn_sub_58B168_0058b168(p3fes::EEContext&);
void fn_sub_58B220_0058b220(p3fes::EEContext&);
void fn_sub_58B278_0058b278(p3fes::EEContext&);
void fn_sub_58B2D0_0058b2d0(p3fes::EEContext&);
void fn_sub_58B398_0058b398(p3fes::EEContext&);
void fn_sub_58B560_0058b560(p3fes::EEContext&);
void fn_sub_58BB80_0058bb80(p3fes::EEContext&);
void fn_sub_58BBB0_0058bbb0(p3fes::EEContext&);
void fn_sub_58BBE8_0058bbe8(p3fes::EEContext&);
void fn_sub_58BC30_0058bc30(p3fes::EEContext&);
void fn_sub_58BC98_0058bc98(p3fes::EEContext&);
void fn_sub_58BD58_0058bd58(p3fes::EEContext&);
void fn_sub_58BE10_0058be10(p3fes::EEContext&);
void fn_sub_58BE40_0058be40(p3fes::EEContext&);
void fn_sub_58C060_0058c060(p3fes::EEContext&);
void fn_sub_58C100_0058c100(p3fes::EEContext&);
void fn_sub_58C118_0058c118(p3fes::EEContext&);
void fn_sub_58C308_0058c308(p3fes::EEContext&);
void fn_sub_58C378_0058c378(p3fes::EEContext&);
void fn_sub_58C430_0058c430(p3fes::EEContext&);
void fn_sub_58C490_0058c490(p3fes::EEContext&);
void fn_sub_58C588_0058c588(p3fes::EEContext&);
void fn_sub_58C648_0058c648(p3fes::EEContext&);
void fn_sub_58C6B0_0058c6b0(p3fes::EEContext&);
void fn_sub_58C980_0058c980(p3fes::EEContext&);
void fn_sub_58CA60_0058ca60(p3fes::EEContext&);
void fn_sub_58CAA0_0058caa0(p3fes::EEContext&);
void fn_sub_58CB00_0058cb00(p3fes::EEContext&);
void fn_sub_58CB28_0058cb28(p3fes::EEContext&);
void fn_sub_58CCA0_0058cca0(p3fes::EEContext&);
void fn_sub_58CD10_0058cd10(p3fes::EEContext&);
void fn_sub_58CE80_0058ce80(p3fes::EEContext&);
void fn_sub_58D058_0058d058(p3fes::EEContext&);
void fn_sub_58D0E0_0058d0e0(p3fes::EEContext&);
void fn_sub_58D180_0058d180(p3fes::EEContext&);
void fn_sub_58D258_0058d258(p3fes::EEContext&);
void fn_sub_58D300_0058d300(p3fes::EEContext&);
void fn_sub_58D370_0058d370(p3fes::EEContext&);
void fn_sub_58D378_0058d378(p3fes::EEContext&);
void fn_sub_58D508_0058d508(p3fes::EEContext&);
void fn_sub_58D578_0058d578(p3fes::EEContext&);
void fn_sub_58D5E8_0058d5e8(p3fes::EEContext&);
void fn_sub_58D600_0058d600(p3fes::EEContext&);
void fn_sub_58D748_0058d748(p3fes::EEContext&);
void fn_sub_58D798_0058d798(p3fes::EEContext&);
void fn_sub_58D800_0058d800(p3fes::EEContext&);
void fn_sub_58D858_0058d858(p3fes::EEContext&);
void fn_sub_58D8E0_0058d8e0(p3fes::EEContext&);
void fn_sub_58D950_0058d950(p3fes::EEContext&);
void fn_sub_58D9B0_0058d9b0(p3fes::EEContext&);
void fn_sub_58DA10_0058da10(p3fes::EEContext&);
void fn_sub_58DB08_0058db08(p3fes::EEContext&);
void fn_sub_58DBB8_0058dbb8(p3fes::EEContext&);
void fn_sub_58DC50_0058dc50(p3fes::EEContext&);
void fn_sub_58DD00_0058dd00(p3fes::EEContext&);
void fn_sub_58DD08_0058dd08(p3fes::EEContext&);
void fn_sub_58DDC0_0058ddc0(p3fes::EEContext&);
void fn_sub_58DE40_0058de40(p3fes::EEContext&);
void fn_sub_58DF08_0058df08(p3fes::EEContext&);
void fn_sub_58DFA8_0058dfa8(p3fes::EEContext&);
void fn_sub_58DFF8_0058dff8(p3fes::EEContext&);
void fn_sub_58E158_0058e158(p3fes::EEContext&);
void fn_sub_58E200_0058e200(p3fes::EEContext&);
void fn_sub_58E250_0058e250(p3fes::EEContext&);
void fn_sub_58E310_0058e310(p3fes::EEContext&);
void fn_sub_58E530_0058e530(p3fes::EEContext&);
void fn_sub_58E5E8_0058e5e8(p3fes::EEContext&);
void fn_sub_58E670_0058e670(p3fes::EEContext&);
void fn_sub_58E958_0058e958(p3fes::EEContext&);
void fn_sub_58EA38_0058ea38(p3fes::EEContext&);
void fn_sub_58EB10_0058eb10(p3fes::EEContext&);
void fn_sub_58EB80_0058eb80(p3fes::EEContext&);
void fn_sub_58EC20_0058ec20(p3fes::EEContext&);
void fn_sub_58EC38_0058ec38(p3fes::EEContext&);
void fn_sub_58ECE8_0058ece8(p3fes::EEContext&);
void fn_sub_58ED48_0058ed48(p3fes::EEContext&);
void fn_sub_58EEC0_0058eec0(p3fes::EEContext&);
void fn_sub_58EF48_0058ef48(p3fes::EEContext&);
void fn_sub_58EFB8_0058efb8(p3fes::EEContext&);
void fn_sub_58EFD8_0058efd8(p3fes::EEContext&);
void fn_sub_58F058_0058f058(p3fes::EEContext&);
void fn_sub_58F298_0058f298(p3fes::EEContext&);
void fn_sub_58F458_0058f458(p3fes::EEContext&);
void fn_sub_58F4C0_0058f4c0(p3fes::EEContext&);
void fn_sub_58F548_0058f548(p3fes::EEContext&);
void fn_sub_58F6A0_0058f6a0(p3fes::EEContext&);
void fn_sub_58F808_0058f808(p3fes::EEContext&);
void fn_sub_58FAD8_0058fad8(p3fes::EEContext&);
void fn_sub_58FB28_0058fb28(p3fes::EEContext&);
void fn_sub_58FBE0_0058fbe0(p3fes::EEContext&);
void fn_sub_58FE08_0058fe08(p3fes::EEContext&);
void fn_sub_58FEC8_0058fec8(p3fes::EEContext&);
void fn_sub_58FF10_0058ff10(p3fes::EEContext&);
void fn_sub_58FF58_0058ff58(p3fes::EEContext&);
void fn_sub_58FF70_0058ff70(p3fes::EEContext&);
void fn_sub_590008_00590008(p3fes::EEContext&);
void fn_sub_5915A8_005915a8(p3fes::EEContext&);
void fn_sub_591B18_00591b18(p3fes::EEContext&);
void fn_sub_591C80_00591c80(p3fes::EEContext&);
void fn_sub_5927D8_005927d8(p3fes::EEContext&);
void fn_sub_592958_00592958(p3fes::EEContext&);
void fn_sub_593948_00593948(p3fes::EEContext&);
void fn_sub_593958_00593958(p3fes::EEContext&);
void fn_sub_593968_00593968(p3fes::EEContext&);
void fn_sub_593978_00593978(p3fes::EEContext&);
void fn_sub_594B88_00594b88(p3fes::EEContext&);
void fn_sub_595138_00595138(p3fes::EEContext&);
void fn_sub_5951A8_005951a8(p3fes::EEContext&);
void fn_sub_595208_00595208(p3fes::EEContext&);
void fn_sub_5954E8_005954e8(p3fes::EEContext&);
void fn_sub_595718_00595718(p3fes::EEContext&);
void fn_sub_595B30_00595b30(p3fes::EEContext&);
void fn_sub_597E80_00597e80(p3fes::EEContext&);
void fn_sub_597FA0_00597fa0(p3fes::EEContext&);
void fn_sub_5982A0_005982a0(p3fes::EEContext&);
void fn_sub_599240_00599240(p3fes::EEContext&);
void fn_sub_599408_00599408(p3fes::EEContext&);
void fn_sub_599418_00599418(p3fes::EEContext&);
void fn_sub_5994F0_005994f0(p3fes::EEContext&);
void fn_sub_5997F8_005997f8(p3fes::EEContext&);
void fn_sub_59B4F0_0059b4f0(p3fes::EEContext&);
void fn_sub_59BC88_0059bc88(p3fes::EEContext&);
void fn_sub_59BCD0_0059bcd0(p3fes::EEContext&);
void fn_sub_59FA38_0059fa38(p3fes::EEContext&);
void fn_sub_59FDB8_0059fdb8(p3fes::EEContext&);
void fn_sub_59FEF8_0059fef8(p3fes::EEContext&);
void fn_sub_5A1380_005a1380(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
namespace ply = libs5::ply;     // the MWSFD player record (libs5.h)
namespace plyx = libs12::plyx;  // its SJ start words
namespace stm = libs12::stm;    // SFD handle stream records
namespace trn = libs12::trn;    // SFD handle transfer slots

// 0x00580588 sub_580588 -- 160 bytes; frame 0x10: ra sp+0x0
// Starts a player on an input SJ: handle check (E1122609), resets the player (sub_580628), stores the SJ (+444),
// status word +464 = 2, clears +468..+476, then sub_580270 and the play start sub_57C730 (tail call).
// [proposed name: mwPlyStartSj] (from the binary's own error / banner text; symbols/deltas/libs12.sym)
void sub_580588(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580588
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x005805a0
    charge(ctx, 10);
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x5805B4u, gen::fn_sub_581798_00581798);
    v1 = 1;
    a0 = s0;
    if (v0 != v1) {
        // 0x005805c8
        charge(ctx, 7);
        a0 = 0x7D0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, -30136);  // "E1122609 mwPlyStartSj: handle is invalid."
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    // 0x005805e8
    charge(ctx, 16);
    jal(ctx, 0x5805E8u, gen::fn_sub_580628_00580628);
    v0 = 2;
    sw(s1, s0, ply::kInputSj);
    a0 = s0;
    sw(v0, s0, plyx::kSjStat);
    sw(zero, s0, plyx::kSjW0);
    sw(zero, s0, plyx::kSjW1);
    link(ctx, 0x580608u);  // $ra first: the delay slot below depends on it
    sw(zero, s0, plyx::kSjW2);
    call(ctx, gen::fn_sub_580270_00580270);
    a0 = s0;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_57C730_0057c730(ctx);  // tail call
}

// 0x00580A98 sub_580A98 -- 120 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// Asks ADXF_GetFnameRangeEx (sub_53DD10) for the range of the player's file name (+420) into three stack words; on
// success marks a pending file start (+428 = 1) with the three words at +432..+440, else reports E211151.
void sub_580A98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580a98
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(ra, sp, 0x18);
    a0 = a1;
    a1 = a2;
    a3 = sp;
    lw(a2, s0, ply::kFname);
    t0 = addiu(sp, 0x4);
    t1 = addiu(sp, 0x8);
    jal(ctx, 0x580ABCu, gen::fn_sub_53DD10_0053dd10);
    a0 = 0x7D0000;
    a0 = addiu(a0, -29832);  // "E211151: ADXF_GetFnameRangeEx() faild."
    if (v0 != 0) {
        // 0x00580af8
        charge(ctx, 2);
        jal(ctx, 0x580AF8u, gen::fn_sub_585590_00585590);
    } else {
        // 0x00580ad0
        charge(ctx, 9);
        lw(v1, sp, 0x0);
        v0 = 1;
        lw(a0, sp, 0x4);
        lw(a1, sp, 0x8);
        sw(v0, s0, ply::kStartPend);
        sw(v1, s0, ply::kFileArg0);
        sw(a0, s0, ply::kFileArg1);
        sw(a1, s0, ply::kFileArg2);
    }
    // 0x00580b00 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00580C20 sub_580C20 -- 24 bytes; frame 0x10: ra sp+0x0
// Thunk: sub_588270 on the player's SFD handle (+60), as a tail call.
void sub_580C20(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580c20
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, ply::kSfd);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_588270_00588270(ctx);  // tail call
}

// 0x00580C38 sub_580C38 -- 24 bytes; frame 0x10: ra sp+0x0
// Thunk: sub_5882F0 on the player's SFD handle (+60), as a tail call.
void sub_580C38(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580c38
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, ply::kSfd);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5882F0_005882f0(ctx);  // tail call
}

// 0x00580C50 sub_580C50 -- 24 bytes; frame 0x10: ra sp+0x0
// Thunk: sub_588168 on the player's SFD handle (+60), as a tail call.
void sub_580C50(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580c50
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, ply::kSfd);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_588168_00588168(ctx);  // tail call
}

// 0x00580C68 sub_580C68 -- 24 bytes; frame 0x10: ra sp+0x0
// Thunk: sub_5881F8 on the player's SFD handle (+60), as a tail call.
void sub_580C68(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580c68
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a0, a0, ply::kSfd);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5881F8_005881f8(ctx);  // tail call
}

// 0x00580C98 sub_580C98 -- 60 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Resets the four MWSFD words 0x7B4528..0x7B4534 to 1, 0, 0, 0.
void sub_580C98(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00580c98
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00580e50
    charge(ctx, 10);
    a2 = 0x7B0000;
    v0 = 1;
    v1 = 0x7B0000;
    a0 = 0x7B0000;
    a1 = 0x7B0000;
    sw(v0, a2, 17704);  // 0x7B4528
    sw(zero, v1, 17708);  // 0x7B452C
    sw(zero, a0, 17712);  // 0x7B4530
    sw(zero, a1, 17716);  // 0x7B4534
}

// 0x00581270 sub_581270 -- 100 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Handle check (E202232, result 0); the dropped-frame count: the skipped decodes (sub_5812D8) plus sub_57F058's count.
// [proposed name: mwPlyGetNumDropFrm] (from the binary's own error / banner text; symbols/deltas/libs12.sym)
void sub_581270(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00581270
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x581280u, gen::fn_sub_581798_00581798);
    v1 = 1;
    a0 = s1;
    if (v0 == v1) {
        // 0x005812a8
        charge(ctx, 6);
        jal(ctx, 0x5812A8u, gen::fn_sub_5812D8_005812d8);
        a0 = s1;
        s0 = v0;
        jal(ctx, 0x5812B4u, gen::fn_sub_57F058_0057f058);
        v0 = addu(s0, v0);
    } else {
        // 0x00581294
        charge(ctx, 5);
        a0 = 0x7D0000;
        a0 = addiu(a0, -29528);  // "E202232: mwPlyGetNumDropFrm: handle is invalid."
        jal(ctx, 0x581298u, gen::fn_sub_585590_00585590);
        v0 = 0;
    }
    // 0x005812c0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x005812D8 sub_5812D8 -- 116 bytes; frame 0xC0: s0 sp+0xB0, ra sp+0xB8
// Handle check (E1122619, result 0); with the player's SFD handle (sub_5811D0) reads its statistics (sub_5994F0) to
// the stack and returns word 1 - word 4, else 0.
// [proposed name: mwPlyGetNumSkipDec] (from the binary's own error / banner text; symbols/deltas/libs12.sym)
void sub_5812D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005812d8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(s0, sp, 0xB0);
    sd(ra, sp, 0xB8);
    s0 = a0;
    jal(ctx, 0x5812E4u, gen::fn_sub_581798_00581798);
    v1 = 1;
    a0 = s0;
    if (v0 == v1) {
        // 0x00581310
        charge(ctx, 6);
        jal(ctx, 0x581310u, gen::fn_sub_5811D0_005811d0);
        v1 = v0;
        a1 = sp;
        a0 = v1;
        if (v1 != 0) {
            // 0x00581328
            charge(ctx, 5);
            jal(ctx, 0x581328u, gen::fn_sub_5994F0_005994f0);
            lw(v1, sp, 0x4);
            lw(v0, sp, 0x10);
            v0 = subu(v1, v0);
        }
    } else {
        // 0x005812f8
        charge(ctx, 5);
        a0 = 0x7D0000;
        a0 = addiu(a0, -29480);  // "E1122619: mwPlyGetNumSkipDec: handle is invalid."
        jal(ctx, 0x5812FCu, gen::fn_sub_585590_00585590);
        v0 = 0;
    }
    // 0x0058133c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0xB0);
    ld(ra, sp, 0xB8);
    sp = addiu(sp, 0xC0);
}

// 0x00581628 sub_581628 -- 56 bytes; frame 0x10: ra sp+0x0
// The player's SFD statistics: sub_5994F0(SFD handle, out) when the player has one (+60), else memset(out, 0, 168).
void sub_581628(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00581628
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, ply::kSfd);
    a0 = a1;
    if (v0 != 0) {
        // 0x00581650
        charge(ctx, 4);
        ld(ra, sp, 0x0);
        a0 = v0;
        sp = addiu(sp, 0x10);
        gen::fn_sub_5994F0_005994f0(ctx);  // tail call
        return;
    }
    // 0x0058163c
    charge(ctx, 5);
    ld(ra, sp, 0x0);
    a1 = 0;
    a2 = 168;
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x00581660 sub_581660 -- 44 bytes; frame 0x10: ra sp+0x0
// sub_599418 on the player's SFD handle (+60) when it has one.
void sub_581660(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00581660
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v0, a0, ply::kSfd);
    a0 = v0;
    if (v0 == 0) {
        // 0x00581680
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x00581674
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_599418_00599418(ctx);  // tail call
}

// 0x005816E0 _M_numpunct_facet__CQ24_STL8ios_base -- 8 bytes; leaf frame (no stack)
// Returns the player's word +64 (its ADXT player).
void _M_numpunct_facet__CQ24_STL8ios_base(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x005816e0
    enter(ctx, 2);  // entry check point + this block's cycles
    lw(v0, a0, ply::kAdxt);
}

// 0x00582040 sub_582040 -- 84 bytes; frame 0xC0: s0 sp+0xB0, ra sp+0xB8
// Handle check (E1122623, result 0); reads the statistics (sub_581628) to the stack and returns word 4.
// [proposed name: mwPlyGetNumSkipEmptyB] (from the binary's own error / banner text; symbols/deltas/libs12.sym)
void sub_582040(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00582040
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0xC0);
    sd(s0, sp, 0xB0);
    sd(ra, sp, 0xB8);
    s0 = a0;
    jal(ctx, 0x58204Cu, gen::fn_sub_581798_00581798);
    v1 = 1;
    a1 = sp;
    a0 = s0;
    if (v0 == v1) {
        // 0x00582078
        charge(ctx, 3);
        jal(ctx, 0x582078u, gen::fn_sub_581628_00581628);
        lw(v0, sp, 0x10);
    } else {
        // 0x00582064
        charge(ctx, 5);
        a0 = 0x7D0000;
        a0 = addiu(a0, -28424);  // "E1122623: mwPlyGetNumSkipEmptyB: handle is invalid."
        jal(ctx, 0x582068u, gen::fn_sub_585590_00585590);
        v0 = 0;
    }
    // 0x00582084 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0xB0);
    ld(ra, sp, 0xB8);
    sp = addiu(sp, 0xC0);
}

// 0x00582118 sub_582118 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Handle check (E1122624); returns the file input's SJ (+448).
// [proposed name: mwPlyGetInputSj] (from the binary's own error / banner text; symbols/deltas/libs12.sym)
void sub_582118(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00582118
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x582124u, gen::fn_sub_581798_00581798);
    a0 = 0x7D0000;
    v1 = 1;
    a0 = addiu(a0, -28312);  // "E1122624: mwPlyGetInputSj: handle is invalid."
    if (v0 == v1) {
        // 0x00582150
        charge(ctx, 1);
        lw(v0, s0, ply::kFileSj);
    } else {
        // 0x0058213c
        charge(ctx, 4);
        jal(ctx, 0x58213Cu, gen::fn_sub_585590_00585590);
        v0 = 0;
    }
    // 0x00582154 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005827D8 sub_5827D8 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: sub_59FA38.
void sub_5827D8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x005827d8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_59FA38_0059fa38(ctx);  // tail call
}

// 0x00582968 sub_582968 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Creation-parameter check: sub_5829B8 on the parameter's word 12 compared with 1, then, when word 34 is set,
// sub_5A1380(word 34, word 35) compared with 1.
void sub_582968(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00582968
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(ra, sp, 0x8);
    link(ctx, 0x582978u);  // $ra first: the delay slot below depends on it
    lw(a1, s0, 48);
    call(ctx, gen::fn_sub_5829B8_005829b8);
    lw(v1, s0, 136);
    v0 = v0 ^ 0x1;
    a0 = v1;
    v0 = sltiu(v0, 1);
    if (v1 != 0) {
        // 0x00582994
        charge(ctx, 4);
        link(ctx, 0x582994u);  // $ra first: the delay slot below depends on it
        lw(a1, s0, 140);
        call(ctx, gen::fn_sub_5A1380_005a1380);
        v0 = v0 ^ 0x1;
        v0 = sltiu(v0, 1);
    }
    // 0x005829a4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x005829B8 sub_5829B8 -- 80 bytes; leaf frame (no stack)
// Entry (n mod 8, truncating division) of the 20-byte table at $a0 + 192: its word 2 when its word 0 is 1, else 0.
void sub_5829B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x005829b8
    enter(ctx, 17);  // entry check point + this block's cycles
    a2 = addiu(a1, 7);
    v0 = slti(a1, 0);
    v1 = a1;
    a3 = 1;
    if (v0 != 0) v1 = a2;
    v0 = 0;
    a2 = sra(v1, 3);
    a2 = sll(a2, 3);
    a2 = subu(a1, a2);
    v1 = sll(a2, 2);
    v1 = addu(v1, a2);
    v1 = sll(v1, 2);
    v1 = addiu(v1, 192);
    a1 = addu(a0, v1);
    lw(a0, a1, 0);
    v1 = a1;
    if (a0 == a3) {
        // 0x005829fc
        charge(ctx, 1);
        lw(v0, v1, 8);
    }
    // 0x00582a00 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00582A58 sub_582A58 -- 92 bytes; frame 0x10: ra sp+0x0
// Maps an MwsfdBufFmt value to 1, 2 or 3; any other value reports E201184.
void sub_582A58(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00582a58
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 2;
    sd(ra, sp, 0x0);
    a1 = sltiu(a0, 3);
    v1 = 2;
    if (a0 != v0) {
        // 0x00582a70
        charge(ctx, 2);
        if (a1 == 0) {
            v0 = 3;
            // 0x00582a88
            charge(ctx, 1);
            v1 = 3;
        } else {
            // 0x00582a78
            charge(ctx, 3);
            v0 = 1;
            v1 = 1;
        }
        // 0x00582a8c
        charge(ctx, 2);
        ld(ra, sp, 0x0);
        if (a0 != v0) {
            // 0x00582a94
            charge(ctx, 4);
            a0 = 0x7D0000;
            a0 = addiu(a0, -28024);  // "E201184 : MwsfdBufFmt value is invalid."
            jal(ctx, 0x582A98u, gen::fn_sub_585590_00585590);
            v1 = 3;
            goto L_00582aa4;
        }
        // 0x00582aa8 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        v0 = v1;
        sp = addiu(sp, 0x10);
        return;
    }
L_00582aa4:
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    // 0x00582aa8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    v0 = v1;
    sp = addiu(sp, 0x10);
}

// 0x00582AB8 sub_582AB8 -- 204 bytes; frame 0x40: s2 sp+0x30, s0 sp+0x20, s1 sp+0x28, ra sp+0x38
// Fills a frame description: words +68 / +72 from the source's words 3 / 4; format 3 splits the buffer in three planes
// (sub_57EC00) and stores Y, Cb, Cr plane records (+4, +20, +36; the chroma ones at half size), other formats one
// plane record.
void sub_582AB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00582ab8
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    t0 = a0;
    sd(s2, sp, 0x30);
    s2 = a1;
    sd(s0, sp, 0x20);
    v1 = 3;
    sd(s1, sp, 0x28);
    a0 = addiu(s2, 4);
    sd(ra, sp, 0x38);
    lw(s1, t0, 16);
    lw(t1, t0, 12);
    lw(v0, t0, 8);
    a2 = s1;
    a3 = s1;
    a1 = t1;
    sw(t1, s2, 68);
    sw(s1, s2, 72);
    if (v0 == v1) {
        // 0x00582b18
        charge(ctx, 22);
        lw(a0, t0, 0);
        a3 = sp;
        s0 = srl(s1, 31);
        jal(ctx, 0x582B20u, gen::fn_sub_57EC00_0057ec00);
        a0 = addiu(s2, 4);
        lw(a1, sp, 0x0);
        a3 = s1;
        lw(a2, sp, 0xC);
        s0 = addu(s1, s0);
        s0 = sra(s0, 1);
        jal(ctx, 0x582B3Cu, gen::fn_sub_582B98_00582b98);
        a0 = addiu(s2, 20);
        lw(a1, sp, 0x4);
        a3 = s0;
        link(ctx, 0x582B50u);  // $ra first: the delay slot below depends on it
        lw(a2, sp, 0x10);
        call(ctx, gen::fn_sub_582B98_00582b98);
        a0 = addiu(s2, 36);
        lw(a1, sp, 0x8);
        a3 = s0;
        link(ctx, 0x582B64u);  // $ra first: the delay slot below depends on it
        lw(a2, sp, 0x14);
        call(ctx, gen::fn_sub_582B98_00582b98);
        ld(s0, sp, 0x20);
    } else {
        // 0x00582b00
        charge(ctx, 5);
        lw(a1, t0, 0);
        a2 = t1;
        jal(ctx, 0x582B04u, gen::fn_sub_582B98_00582b98);
        ld(s0, sp, 0x20);
    }
    // 0x00582b70 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x00582B88 sub_582B88 -- 12 bytes; leaf frame (no stack)
// Copies the source's word +52 to the destination's word +76.
void sub_582B88(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00582b88
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v0, a0, 52);
    sw(v0, a1, 76);
}

// 0x00582B98 sub_582B98 -- 16 bytes; leaf frame (no stack)
// Stores a three-word plane record {a1, a2, a3} at $a0.
void sub_582B98(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00582b98
    enter(ctx, 4);  // entry check point + this block's cycles
    sw(a3, a0, 8);
    sw(a1, a0, 0);
    sw(a2, a0, 4);
}

// 0x00582BA8 sub_582BA8 -- 72 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// Reads two values of the SFX handle (+168) with sub_59FEF8 into the output's words 20 / 21 and clears words 22 / 23.
void sub_582BA8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00582ba8
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x10);
    s0 = a2;
    sd(ra, sp, 0x18);
    a1 = sp;
    a2 = addiu(sp, 0x4);
    link(ctx, 0x582BC0u);  // $ra first: the delay slot below depends on it
    lw(a0, a0, 168);
    call(ctx, gen::fn_sub_59FEF8_0059fef8);
    sw(zero, s0, 88);
    ld(ra, sp, 0x18);
    lw(v0, sp, 0x0);
    lw(v1, sp, 0x4);
    sw(v0, s0, 80);
    sw(v1, s0, 84);
    sw(zero, s0, 92);
    ld(s0, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00583058 sub_583058 -- 120 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Handle check (E2011915, result 0); the SFX composition mode of the player (sub_59FDB8 on sub_582828's handle), with
// 81 and 97 both reported as 65.
// [proposed name: mwPlyFxGetCompoMode] (from the binary's own error / banner text; symbols/deltas/libs12.sym)
void sub_583058(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00583058
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x583064u, gen::fn_sub_581798_00581798);
    v1 = 1;
    a0 = s0;
    if (v0 == v1) {
        // 0x00583090
        charge(ctx, 8);
        jal(ctx, 0x583090u, gen::fn_sub_582828_00582828);
        a0 = v0;
        jal(ctx, 0x583098u, gen::fn_sub_59FDB8_0059fdb8);
        v1 = v0;
        v0 = 81;
        a0 = 97;
        if (v1 != v0) {
            // 0x005830b0
            charge(ctx, 2);
            v0 = v1;
            if (v1 == a0) {
                goto L_005830b8;
            }
            // 0x005830c0 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(s0, sp, 0x0);
            ld(ra, sp, 0x8);
            sp = addiu(sp, 0x10);
            return;
        }
    L_005830b8:
        charge(ctx, 2);
        v1 = 65;
        v0 = v1;
    } else {
        // 0x00583078
        charge(ctx, 5);
        a0 = 0x7D0000;
        a0 = addiu(a0, -27472);  // "E2011915: mwPlyFxGetCompoMode: handle is invalid."
        jal(ctx, 0x58307Cu, gen::fn_sub_585590_00585590);
        v0 = 0;
    }
    // 0x005830c0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00584190 sub_584190 -- 156 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Handle check (E1122634); links the stream (sub_584830 1), starts on the file SJ (sub_580588 with +448), sub_580900,
// sub_55D600 on the LSC (+72), calls the input SJ's vtable +20 when there is one, the play start (sub_57C730) and
// clears +680.
// [proposed name: mwPlyStartSeamless] (from the binary's own error / banner text; symbols/deltas/libs12.sym)
void sub_584190(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584190
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x58419Cu, gen::fn_sub_581798_00581798);
    v1 = 1;
    a1 = 1;
    a0 = s0;
    if (v0 != v1) {
        // 0x005841b4
        charge(ctx, 6);
        a0 = 0x7D0000;
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        a0 = addiu(a0, -26392);  // "E1122634: mwPlyStartSeamless: handle is invalid."
        sp = addiu(sp, 0x10);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    // 0x005841d0
    charge(ctx, 12);
    jal(ctx, 0x5841D0u, gen::fn_sub_584830_00584830);
    a0 = s0;
    link(ctx, 0x5841DCu);  // $ra first: the delay slot below depends on it
    lw(a1, s0, ply::kFileSj);
    call(ctx, gen::fn_sub_580588_00580588);
    a0 = s0;
    jal(ctx, 0x5841E4u, gen::fn_sub_580900_00580900);
    link(ctx, 0x5841ECu);  // $ra first: the delay slot below depends on it
    lw(a0, s0, ply::kLsc);
    call(ctx, gen::fn_sub_55D600_0055d600);
    lw(v0, s0, ply::kInputSj);
    a0 = v0;
    if (v0 != 0) {
        // 0x00584200
        charge(ctx, 4);
        lw(v0, v0, 0);
        lw(v1, v0, 20);
        jalr(ctx, 0x584208u, v1.u());
    }
    // 0x00584210
    charge(ctx, 7);
    a0 = s0;
    jal(ctx, 0x584210u, gen::fn_sub_57C730_0057c730);
    sw(zero, s0, ply::kUnk680);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00584230 sub_584230 -- 96 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Handle check (E1122641); sets the loop flag $a1 on the player's LSC (+72) with sub_55DB58.
// [proposed name: mwPlySetLpFlg] (from the binary's own error / banner text; symbols/deltas/libs12.sym)
void sub_584230(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584230
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x584244u, gen::fn_sub_581798_00581798);
    a0 = 0x7D0000;
    v1 = 1;
    a0 = addiu(a0, -26336);  // "E1122641: mwPlySetLpFlg: handle is invalid."
    a1 = s0;
    if (v0 != v1) {
        // 0x00584260
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    // 0x00584278
    charge(ctx, 6);
    lw(a0, s1, ply::kLsc);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_55DB58_0055db58(ctx);  // tail call
}

// 0x00584290 sub_584290 -- 168 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Handle check (E1122630) and file name check (E10915A); sets the file name (sub_5809B0), resets the LSC (sub_55D668),
// enters the name (sub_5840D0 with +420), loop flag 1 (sub_584230) and the seamless start (sub_584190).
// [proposed name: mwPlyStartFnameLp] (from the binary's own error / banner text; symbols/deltas/libs12.sym)
void sub_584290(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584290
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x5842A4u, gen::fn_sub_581798_00581798);
    a0 = 0x7D0000;
    v1 = 1;
    a0 = addiu(a0, -26288);  // "E1122630: mwPlyStartFnameLp: handle is invalid."
    if (v0 != v1) {
        // 0x005842bc
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    // 0x005842d0
    charge(ctx, 2);
    a1 = s1;
    if (s1 == 0) {
        // 0x005842d8
        charge(ctx, 7);
        a0 = 0x7D0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, -26240);  // "E10915A: mwPlyStartFnameLp: fname is NULL."
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    // 0x005842f8
    charge(ctx, 16);
    a0 = s0;
    jal(ctx, 0x5842F8u, gen::fn_sub_5809B0_005809b0);
    link(ctx, 0x584300u);  // $ra first: the delay slot below depends on it
    lw(a0, s0, ply::kLsc);
    call(ctx, gen::fn_sub_55D668_0055d668);
    a0 = s0;
    link(ctx, 0x58430Cu);  // $ra first: the delay slot below depends on it
    lw(a1, s0, ply::kFname);
    call(ctx, gen::fn_sub_5840D0_005840d0);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x584318u, gen::fn_sub_584230_00584230);
    a0 = s0;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_584190_00584190(ctx);  // tail call
}

// 0x00584338 sub_584338 -- 176 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Handle check (E1122631); loop flag 0 (sub_584230), then a second handle check (E1122635) and the stream unlink
// (sub_584830 0).
// [proposed name: mwPlyReleaseLp] (from the binary's own error / banner text; symbols/deltas/libs12.sym)
void sub_584338(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584338
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x584344u, gen::fn_sub_581798_00581798);
    v1 = 1;
    a0 = s0;
    a1 = 0;
    if (v0 != v1) {
        // 0x0058435c
        charge(ctx, 6);
        a0 = 0x7D0000;
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        a0 = addiu(a0, -26192);  // "E1122631: mwPlyReleaseLp: handle is invalid."
        sp = addiu(sp, 0x10);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    // 0x00584378
    charge(ctx, 7);
    jal(ctx, 0x584378u, gen::fn_sub_584230_00584230);
    a0 = s0;
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00584398
    charge(ctx, 9);
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x5843A4u, gen::fn_sub_581798_00581798);
    v1 = 1;
    a0 = s0;
    a1 = 0;
    if (v0 == v1) {
        // 0x005843d8
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_sub_584830_00584830(ctx);  // tail call
        return;
    }
    // 0x005843bc
    charge(ctx, 6);
    a0 = 0x7D0000;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    a0 = addiu(a0, -26144);  // "E1122635: mwPlyReleaseSeamless: handle is invalid."
    sp = addiu(sp, 0x10);
    gen::fn_sub_585590_00585590(ctx);  // tail call
}

// 0x00584830 sub_584830 -- 168 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Handle check (E1122642); sets the link byte (+112) to $a1. Unlinking a linked player requests termination (+113 =
// 1); linking an unlinked one calls sub_589F70 on the SFD handle and reports E99072101 when it fails.
// [proposed name: mwPlyLinkStm] (from the binary's own error / banner text; symbols/deltas/libs12.sym)
void sub_584830(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00584830
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x584844u, gen::fn_sub_581798_00581798);
    v1 = v0;
    v0 = 1;
    a0 = 0x7D0000;
    a0 = addiu(a0, -25736);  // "E1122642: mwPlyLinkStm: handle is invalid."
    if (v1 != v0) {
        // 0x00584860
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_585590_00585590(ctx);  // tail call
        return;
    }
    // 0x00584878
    charge(ctx, 3);
    lb(v0, s0, ply::kLinkFlg);
    lw(a0, s0, ply::kSfd);
    if (v0 == v1) {
        // 0x00584884
        charge(ctx, 2);
        if (s1 == 0) {
            sb(v0, s0, ply::kTermReq);
        }
        // 0x0058488c
        charge(ctx, 1);
        lb(v0, s0, ply::kLinkFlg);
    }
    // 0x00584890
    charge(ctx, 2);
    if (v0 != 0) {
        sb(s1, s0, ply::kLinkFlg);
    } else {
        // 0x00584898
        charge(ctx, 3);
        v0 = 1;
        if (s1 != v0) {
            sb(s1, s0, ply::kLinkFlg);
        } else {
            // 0x005848a4
            charge(ctx, 5);
            jal(ctx, 0x5848A4u, gen::fn_sub_589F70_00589f70);
            a0 = 0x7D0000;
            a0 = addiu(a0, -25688);  // "E99072101 mwPlyLinkStm: can't link stream"
            if (v0 != 0) {
                // 0x005848b8
                charge(ctx, 2);
                jal(ctx, 0x5848B8u, gen::fn_sub_585590_00585590);
            }
            // 0x005848c0
            charge(ctx, 1);
            sb(s1, s0, ply::kLinkFlg);
        }
    }
    // 0x005848c4 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(ra, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    sp = addiu(sp, 0x20);
}

// 0x005849A0 sub_5849A0 -- 48 bytes; leaf frame (no stack)
// MWSFD's fixed buffer sizes: 149,988 / 40,000 / 2,048 into the three outputs; returns their sum.
void sub_5849A0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x005849a0
    enter(ctx, 12);  // entry check point + this block's cycles
    v0 = 0x20000;
    a3 = 2048;
    v0 = v0 | 0x49E4;
    v1 = 0x9C40;
    sw(v0, a0, 0);
    sw(v1, a1, 0);
    sw(a3, a2, 0);
    lw(v0, a0, 0);
    lw(v1, a1, 0);
    v0 = addu(v0, v1);
    v0 = addu(v0, a3);
}

// 0x005851A0 sceLibgcc32GetErxEntries_19 -- 12 bytes; leaf frame (no stack)
// Returns 0x7B4538, the address of the audio-slave interface pointer.
void sceLibgcc32GetErxEntries_19(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x005851a0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    v0 = addiu(v0, 17720);  // &0x7B4538
}

// 0x00586490 sub_586490 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: sub_547558.
void sub_586490(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00586490
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_547558_00547558(ctx);  // tail call
}

// 0x00586F20 sub_586F20 -- 192 bytes; frame 0x40: s3 sp+0x28, s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s4 sp+0x30, ra sp+0x38
// Data-referenced transfer callback (needs at least 288 bytes): sub_54ABA8 over the data; when that is 0 and
// sub_58BBB0 < 108, the length sub_586FE0 accepts; stores the count to *$a3, sub_586C10 into the work's (+8196)
// callback +60 and adds the count to the 64-bit total +2504.
void sub_586F20(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00586f20
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s3, sp, 0x28);
    s3 = a3;
    sd(s0, sp, 0x10);
    s0 = a2;
    sd(s1, sp, 0x18);
    s1 = a1;
    sd(s2, sp, 0x20);
    s2 = a0;
    sd(s4, sp, 0x30);
    v0 = slti(s0, 288);
    sd(ra, sp, 0x38);
    a2 = sp;
    sw(zero, s3, 0);
    a1 = s0;
    a0 = s1;
    lw(s4, s2, 8196);
    if (v0 == 0) {
        // 0x00586f68
        charge(ctx, 4);
        jal(ctx, 0x586F68u, gen::fn_sub_54ABA8_0054aba8);
        lw(a3, sp, 0x0);
        if (v0 == 0) {
            // 0x00586f78
            charge(ctx, 8);
            a0 = s2;
            jal(ctx, 0x586F78u, gen::fn_sub_58BBB0_0058bbb0);
            a3 = 0;
            v0 = slti(v0, 108);
            a2 = s0;
            a0 = s2;
            a1 = s1;
            if (v0 != 0) {
                // 0x00586f98
                charge(ctx, 3);
                jal(ctx, 0x586F98u, gen::fn_sub_586FE0_00586fe0);
                a3 = subu(v0, s1);
            }
        }
        // 0x00586fa4
        charge(ctx, 7);
        ld(v1, s2, 2504);
        v0 = 0x580000;
        v0 = addiu(v0, 27664);  // &sub_586C10
        sw(a3, s3, 0);
        v1 = a3 + v1;
        sw(v0, s4, 60);
        sd(v1, s2, 2504);
    }
    // 0x00586fc0 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x00587218 sub_587218 -- 80 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Words +12 / +16 of sub_588138's record into the two outputs; 0, or -1 when there is no record.
void sub_587218(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00587218
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a2;
    jal(ctx, 0x58722Cu, gen::fn_sub_588138_00588138);
    v1 = v0;
    v0 = si(-1);
    if (v1 != 0) {
        // 0x00587240
        charge(ctx, 5);
        lw(a0, v1, 12);
        v0 = 0;
        sw(a0, s0, 0);
        lw(v1, v1, 16);
        sw(v1, s1, 0);
    }
    // 0x00587254 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00588720 sub_588720 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: sub_589E38 (the SJ class uuids).
void sub_588720(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x00588720
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_589E38_00589e38(ctx);  // tail call
}

// 0x00588740 sub_588740 -- 312 bytes; frame 0x50: s0 sp+0x20, s1 sp+0x28, s2 sp+0x30, s3 sp+0x38, ra sp+0x40
// Lays out an SFD handle's streams from its creation record: the eight buffer offsets (sub_588878), streams 0..2
// (sub_5888B8: residue of the first size, 2048, 0), stream 3 (sub_588AB8), then sub_588B70 / sub_588C98; stops at the
// first error.
void sub_588740(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588740
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x20);
    s0 = a2;
    sd(s1, sp, 0x28);
    s1 = addiu(s0, 8);
    sd(s2, sp, 0x30);
    s2 = a1;
    sd(s3, sp, 0x38);
    s3 = a0;
    sd(ra, sp, 0x40);
    a1 = s1;
    a0 = sp;
    link(ctx, 0x588770u);  // $ra first: the delay slot below depends on it
    lw(a2, s0, 4);
    call(ctx, gen::fn_sub_588878_00588878);
    lw(v1, s1, 0);
    lw(v0, s0, 40);
    a0 = s2;
    a1 = sp;
    a2 = s1;
    div(v1, v0);
    a3 = 0;
    if (v0 == 0) {
        brk(ctx, 0x588798u, 0x7u);
    }
    // 0x0058879c
    charge(ctx, 9);
    mfhi(t0);
    jal(ctx, 0x5887A0u, gen::fn_sub_5888B8_005888b8);
    a0 = s2;
    a1 = sp;
    a2 = s1;
    a3 = 1;
    t0 = 2048;
    if (v0 == 0) {
        // 0x005887c0
        charge(ctx, 4);
        jal(ctx, 0x5887C0u, gen::fn_sub_5888B8_005888b8);
        if (v0 == 0) {
            // 0x005887d0
            charge(ctx, 11);
            a0 = s2;
            a1 = sp;
            a3 = 2;
            t0 = 0;
            a2 = s1;
            jal(ctx, 0x5887E0u, gen::fn_sub_5888B8_005888b8);
            a0 = s3;
            t0 = 3;
            a3 = s1;
            a1 = s2;
            if (v0 == 0) {
                // 0x005887fc
                charge(ctx, 24);
                a2 = sp;
                jal(ctx, 0x5887FCu, gen::fn_sub_588AB8_00588ab8);
                a0 = s2;
                a1 = sp;
                a2 = s1;
                a3 = 4;
                jal(ctx, 0x588810u, gen::fn_sub_588B70_00588b70);
                a0 = s3;
                a2 = sp;
                t0 = 5;
                a1 = s2;
                a3 = s1;
                jal(ctx, 0x588828u, gen::fn_sub_588AB8_00588ab8);
                a0 = s2;
                a1 = sp;
                a2 = s1;
                a3 = 6;
                jal(ctx, 0x58883Cu, gen::fn_sub_588B70_00588b70);
                a0 = s2;
                a1 = sp;
                a2 = s1;
                a3 = 7;
                jal(ctx, 0x588850u, gen::fn_sub_588C98_00588c98);
                v0 = 0;
            }
            goto L_0058885c;
        }
        ld(s0, sp, 0x20);
        // 0x00588860 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s1, sp, 0x28);
        ld(s2, sp, 0x30);
        ld(s3, sp, 0x38);
        ld(ra, sp, 0x40);
        sp = addiu(sp, 0x50);
        return;
    }
L_0058885c:
    charge(ctx, 1);
    ld(s0, sp, 0x20);
    // 0x00588860 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x00588878 sub_588878 -- 60 bytes; leaf frame (no stack)
// Running offsets: out[i] = base + the sum of the first i of eight sizes.
void sub_588878(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9};
    // 0x00588878
    enter(ctx, 4);  // entry check point + this block's cycles
    t1 = a0;
    t0 = a1;
    a3 = 0;
    for (;;) {
        // 0x00588888
        charge(ctx, 9);
        v0 = sll(a3, 2);
        a3 = addiu(a3, 1);
        v1 = addu(v0, t0);
        v0 = addu(v0, t1);
        lw(a0, v1, 0);
        a1 = slti(a3, 8);
        sw(a2, v0, 0);
        a2 = addu(a2, a0);
        if (a1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x005888ac
    charge(ctx, 2);
}

// 0x005888B8 sub_5888B8 -- 188 bytes; frame 0x50: s0 sp+0x20, s1 sp+0x28, s2 sp+0x30, s3 sp+0x38, ra sp+0x40
// Sets up stream n (116-byte record): with a size, a memory SJ over its buffer (sub_588978), the chunk descriptor
// (sub_588E98, flag 1) and the header as type 5 (owns its SJ); without, the header as type 4 (waits for an SJ).
void sub_5888B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005888b8
    enter(ctx, 21);  // entry check point + this block's cycles
    v0 = sll(a3, 3);
    sp = addiu(sp, -0x50);
    v0 = subu(v0, a3);
    t1 = sll(a3, 2);
    sd(s0, sp, 0x20);
    v0 = sll(v0, 2);
    sd(s1, sp, 0x28);
    a2 = addu(a2, t1);
    sd(s2, sp, 0x30);
    v0 = addu(v0, a3);
    sd(s3, sp, 0x38);
    v0 = sll(v0, 2);
    sd(ra, sp, 0x40);
    s0 = addu(a0, v0);
    a3 = t0;
    a1 = addu(a1, t1);
    lw(v1, a2, 0);
    a0 = sp;
    s1 = addiu(s0, 16);
    a2 = v1;
    if (v1 == 0) {
        // 0x0058890c
        charge(ctx, 3);
        s3 = 0;
        s2 = 4;
        goto L_00588944;
    }
    // 0x00588918
    charge(ctx, 9);
    lw(a1, a1, 0);
    s3 = 1;
    s2 = 5;
    jal(ctx, 0x588920u, gen::fn_sub_588978_00588978);
    a2 = s0;
    a0 = s1;
    a1 = sp;
    a3 = 1;
    if (v0 == 0) {
        // 0x0058893c
        charge(ctx, 2);
        jal(ctx, 0x58893Cu, gen::fn_sub_588E98_00588e98);
    L_00588944:
        charge(ctx, 5);
        a0 = s0;
        a1 = s2;
        a2 = s3;
        jal(ctx, 0x58894Cu, gen::fn_sub_588CE8_00588ce8);
        v0 = 0;
    }
    // 0x00588958 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x00588978 sub_588978 -- 148 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Memory SJ over a buffer: record {0, sj, addr, size - offset, offset, 0}; the SJ from sub_562388; error -16776180 (no
// room) or -16776182 (no SJ) through sub_58BE40.
void sub_588978(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588978
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    v0 = subu(a2, a3);
    a2 = a3;
    a1 = lui(0xFF00);
    sd(ra, sp, 0x8);
    a0 = 0;
    a1 = a1 | 0x40C;
    sw(zero, s0, 0);
    sw(v1, s0, 8);
    sw(v0, s0, 12);
    if (i64(v0) <= 0) {
        // 0x005889b0
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x005889c0
    charge(ctx, 10);
    sw(a3, s0, 16);
    a0 = v1;
    sw(zero, s0, 20);
    a1 = v0;
    jal(ctx, 0x5889CCu, gen::fn_sub_562388_00562388);
    a0 = 0;
    a1 = lui(0xFF00);
    sw(v0, s0, 4);
    a1 = a1 | 0x40A;
    if (v0 != 0) {
        // 0x005889f8
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        v0 = 0;
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005889e8
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x00588A10 sub_588A10 -- 60 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Destroys the SJs of streams 0, 1, 2 (sub_588A50).
void sub_588A10(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588a10
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x588A20u, gen::fn_sub_588A50_00588a50);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x588A2Cu, gen::fn_sub_588A50_00588a50);
    a0 = s0;
    ld(ra, sp, 0x8);
    a1 = 2;
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_588A50_00588a50(ctx);  // tail call
}

// 0x00588A50 sub_588A50 -- 104 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Stream n of type 5: destroys its SJ (vtable +12) and clears the pointer.
void sub_588A50(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588a50
    enter(ctx, 14);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    sp = addiu(sp, -0x10);
    v0 = subu(v0, a1);
    sd(s0, sp, 0x0);
    v0 = sll(v0, 2);
    sd(ra, sp, 0x8);
    v0 = addu(v0, a1);
    a0 = addiu(a0, stm::kBase);
    v0 = sll(v0, 2);
    a2 = 5;
    a0 = addu(a0, v0);
    lw(v1, a0, 0);
    s0 = addiu(a0, 16);
    if (v1 == a2) {
        // 0x00588a88
        charge(ctx, 3);
        lw(v0, s0, 4);
        a0 = v0;
        if (v0 != 0) {
            // 0x00588a94
            charge(ctx, 5);
            lw(v0, v0, 0);
            lw(v1, v0, 12);
            jalr(ctx, 0x588A9Cu, v1.u());
            sw(zero, s0, 4);
        }
    }
    // 0x00588aa8 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00588AB8 sub_588AB8 -- 184 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Sets up stream n as a ring of type 1 over the handle's buffers (+5808, +7848): the record, then fifteen 16-byte
// descriptors.
void sub_588AB8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588ab8
    enter(ctx, 32);  // entry check point + this block's cycles
    v0 = sll(t0, 3);
    sp = addiu(sp, -0x30);
    v0 = subu(v0, t0);
    v1 = sll(t0, 2);
    sd(s0, sp, 0x0);
    v0 = sll(v0, 2);
    sd(s1, sp, 0x8);
    s1 = addu(a2, v1);
    sd(s2, sp, 0x10);
    s2 = addu(a3, v1);
    sd(s3, sp, 0x18);
    s3 = a0;
    sd(ra, sp, 0x20);
    v0 = addu(v0, t0);
    v0 = sll(v0, 2);
    lw(a0, s2, 0);
    s0 = addu(a1, v0);
    a1 = 1;
    a2 = sltu(0, a0);
    a0 = s0;
    jal(ctx, 0x588B04u, gen::fn_sub_588CE8_00588ce8);
    lw(v1, s1, 0);
    lw(a0, s2, 0);
    s0 = addiu(s0, 16);
    v0 = addiu(s3, 5808);
    s3 = addiu(s3, 7848);
    sw(v1, s0, 0);
    sw(a0, s0, 4);
    sw(zero, s0, 8);
    sw(zero, s0, 12);
    sw(v0, s0, 16);
    v0 = 15;
    for (;;) {
        // 0x00588b38
        charge(ctx, 7);
        v0 = addiu(v0, -1);
        sw(zero, s3, 0);
        s3 = addiu(s3, -136);
        if (i64(v0) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00588b54
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00588B70 sub_588B70 -- 160 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Sets up stream n as type 2: the record, its address / size and cleared counters.
void sub_588B70(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588b70
    enter(ctx, 40);  // entry check point + this block's cycles
    v0 = sll(a3, 3);
    sp = addiu(sp, -0x20);
    v0 = subu(v0, a3);
    v1 = sll(a3, 2);
    sd(s0, sp, 0x0);
    v0 = sll(v0, 2);
    sd(s1, sp, 0x8);
    s1 = addu(a1, v1);
    sd(s2, sp, 0x10);
    s2 = addu(a2, v1);
    sd(ra, sp, 0x18);
    v0 = addu(v0, a3);
    v0 = sll(v0, 2);
    a1 = 2;
    lw(a2, s2, 0);
    s0 = addu(a0, v0);
    a0 = s0;
    s0 = addiu(s0, 16);
    a2 = sltu(0, a2);
    jal(ctx, 0x588BB8u, gen::fn_sub_588CE8_00588ce8);
    lw(v0, s1, 0);
    lw(v1, s2, 0);
    sw(v0, s0, 0);
    sw(v1, s0, 4);
    sw(zero, s0, 44);
    sw(zero, s0, 8);
    sw(zero, s0, 12);
    sw(zero, s0, 16);
    sw(zero, s0, 20);
    sw(zero, s0, 24);
    sw(zero, s0, 28);
    sw(zero, s0, 32);
    sw(zero, s0, 36);
    sw(zero, s0, 40);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00588C98 sub_588C98 -- 120 bytes, 2 chunks; frame 0x10: s0 sp+0x0, ra sp+0x8
// Sets up stream n as type 3: the record and two cleared 16-byte descriptors.
void sub_588C98(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588c98
    enter(ctx, 19);  // entry check point + this block's cycles
    v0 = sll(a3, 3);
    sp = addiu(sp, -0x10);
    v0 = subu(v0, a3);
    sd(s0, sp, 0x0);
    v0 = sll(v0, 2);
    a1 = 3;
    v0 = addu(v0, a3);
    a2 = 1;
    v0 = sll(v0, 2);
    sd(ra, sp, 0x8);
    s0 = addu(a0, v0);
    a0 = s0;
    s0 = addiu(s0, 16);
    jal(ctx, 0x588CC8u, gen::fn_sub_588CE8_00588ce8);
    a0 = s0;
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x00588d08
    charge(ctx, 2);
    v0 = 2;
    for (;;) {
        // 0x00588d10
        charge(ctx, 7);
        v0 = addiu(v0, -1);
        sw(zero, a0, 0);
        sw(zero, a0, 4);
        sw(zero, a0, 8);
        sw(zero, a0, 12);
        a0 = addiu(a0, 16);
        if (i64(v0) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x00588d2c
    charge(ctx, 2);
}

// 0x00588CE8 sub_588CE8 -- 32 bytes; leaf frame (no stack)
// Stream record header: type, flag, words 2 / 3 cleared, words 19 / 20 = 9.
void sub_588CE8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00588ce8
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = 9;
    sw(a1, a0, 0);
    sw(v0, a0, 80);
    sw(a2, a0, 4);
    sw(zero, a0, 8);
    sw(zero, a0, 12);
    sw(v0, a0, 76);
}

// 0x00588D38 sub_588D38 -- 280 bytes, 2 chunks; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Attaches an input SJ to an SFD handle: checks the parameter (sub_588DE0, error -16776184); picks stream 0, 1 or 2 by
// the handle's kind (sub_59BCD0 1 / 2 / 3); the stream must be type 4 (error -16776183); then its chunk (sub_588E98).
void sub_588D38(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588d38
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x10);
    a0 = s1;
    jal(ctx, 0x588D50u, gen::fn_sub_588DE0_00588de0);
    a0 = s0;
    a1 = 1;
    if (v0 != 0) {
        // 0x00588d64
        charge(ctx, 7);
        a1 = lui(0xFF00);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a1 = a1 | 0x408;
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00588d80
    charge(ctx, 6);
    a0 = s0;
    jal(ctx, 0x588D80u, gen::fn_sub_59BCD0_0059bcd0);
    a0 = s0;
    a1 = 2;
    a2 = 0;
    if (v0 == 0) {
        // 0x00588d98
        charge(ctx, 6);
        jal(ctx, 0x588D98u, gen::fn_sub_59BCD0_0059bcd0);
        a0 = s0;
        a1 = 3;
        a2 = 1;
        if (v0 == 0) {
            // 0x00588db0
            charge(ctx, 6);
            jal(ctx, 0x588DB0u, gen::fn_sub_59BCD0_0059bcd0);
            v1 = 2;
            a2 = 0;
            if (v0 != 0) a2 = v1;
            a0 = s0;
        }
    }
    // 0x00588dc8
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    a1 = s1;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    // 0x00588e28
    charge(ctx, 15);
    v0 = sll(a2, 3);
    sp = addiu(sp, -0x10);
    v0 = subu(v0, a2);
    sd(ra, sp, 0x0);
    v0 = sll(v0, 2);
    v1 = addiu(a0, stm::kBase);
    v0 = addu(v0, a2);
    a3 = 4;
    v0 = sll(v0, 2);
    t0 = a1;
    v1 = addu(v1, v0);
    lw(v0, v1, 0);
    a2 = v1;
    v1 = addiu(v1, 16);
    if (v0 != a3) {
        // 0x00588e64
        charge(ctx, 5);
        a1 = lui(0xFF00);
        ld(ra, sp, 0x0);
        a1 = a1 | 0x409;
        sp = addiu(sp, 0x10);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x00588e78
    charge(ctx, 8);
    lw(a3, t0, 4);
    a0 = v1;
    a3 = sltu(0, a3);
    jal(ctx, 0x588E80u, gen::fn_sub_588E98_00588e98);
    v0 = 0;
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00588DE0 sub_588DE0 -- 68 bytes; leaf frame (no stack)
// Validates an SJ attach parameter: 0 when word 1 is set and either word 0 is set, or word 2 is set with word 3 > 0
// and word 5 <= 0; -1 otherwise.
void sub_588DE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00588de0
    enter(ctx, 3);  // entry check point + this block's cycles
    lw(v1, a0, 4);
    v0 = si(-1);
    if (v1 != 0) {
        // 0x00588dec
        charge(ctx, 3);
        lw(v0, a0, 0);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x00588df8
            charge(ctx, 3);
            lw(v1, a0, 8);
            v0 = si(-1);
            if (v1 != 0) {
                // 0x00588e04
                charge(ctx, 3);
                lw(v1, a0, 12);
                if (i64(v1) > 0) {
                    // 0x00588e10
                    charge(ctx, 3);
                    lw(v1, a0, 20);
                    if (i64(v1) <= 0) {
                        v0 = 0;
                    }
                }
            }
        }
    }
    // 0x00588e1c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00588E98 sub_588E98 -- 160 bytes; frame 0x40: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, ra sp+0x30
// Under the SFD lock (sub_58C100 / sub_58C118): sets the flag word, copies the 24-byte source descriptor, clears the
// pair at +24 and the words +32 / +36, and sub_597E80 on +40.
void sub_588E98(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00588e98
    enter(ctx, 40);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = a3;
    sd(s2, sp, 0x20);
    s2 = a2;
    a0 = sp;
    sd(s3, sp, 0x28);
    sd(ra, sp, 0x30);
    s3 = a1;
    jal(ctx, 0x588EC0u, gen::fn_sub_58C100_0058c100);
    sw(s1, s2, 4);
    a0 = addiu(s0, 24);
    ldl(v0, s3, 7);
    ldr(v0, s3, 0);
    ldl(v1, s3, 15);
    ldr(v1, s3, 8);
    ldl(a1, s3, 23);
    ldr(a1, s3, 16);
    sdl(v0, s0, 7);
    sdr(v0, s0, 0);
    sdl(v1, s0, 15);
    sdr(v1, s0, 8);
    sdl(a1, s0, 23);
    link(ctx, 0x588EFCu);  // $ra first: the delay slot below depends on it
    sdr(a1, s0, 16);
    call(ctx, gen::fn_sub_588F38_00588f38);
    sw(zero, s0, 32);
    sw(zero, s0, 36);
    a0 = addiu(s0, 40);
    jal(ctx, 0x588F0Cu, gen::fn_sub_597E80_00597e80);
    a0 = sp;
    jal(ctx, 0x588F14u, gen::fn_sub_58C118_0058c118);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x00588F38 sub_588F38 -- 12 bytes; leaf frame (no stack)
// Clears two words.
void sub_588F38(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4};
    // 0x00588f38
    enter(ctx, 3);  // entry check point + this block's cycles
    sw(zero, a0, 4);
    sw(zero, a0, 0);
}

// 0x00588F90 sub_588F90 -- 72 bytes; leaf frame (no stack)
// Copies the 16-byte descriptor j of stream n (+4896 + 116n + 16j) to the output.
void sub_588F90(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x00588f90
    enter(ctx, 18);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    a2 = sll(a2, 4);
    v0 = subu(v0, a1);
    v0 = sll(v0, 2);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    a0 = addiu(a0, stm::kBase + stm::kDesc);
    a0 = addu(a0, a2);
    ldl(v0, a0, 7);
    ldr(v0, a0, 0);
    ldl(v1, a0, 15);
    ldr(v1, a0, 8);
    sdl(v0, a3, 7);
    sdr(v0, a3, 0);
    sdl(v1, a3, 15);
    sdr(v1, a3, 8);
}

// 0x00589000 sub_589000 -- 24 bytes; frame 0x10: ra sp+0x0
// Chunk read with lane 0: $a3 = 0, then sub_589018 entered past its prologue (0x589030).
void sub_589000(EEContext& ctx) {
    using namespace hg;
    Gpr a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00589000
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a3 = 0;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_589018_00589018_at_00589030(ctx);  // tail call
}

// 0x005890D8 sub_5890D8 -- 24 bytes; frame 0x10: ra sp+0x0
// Chunk release with lane 0: $a3 = 0, then sub_5890F0 entered past its prologue (0x589108).
void sub_5890D8(EEContext& ctx) {
    using namespace hg;
    Gpr a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005890d8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a3 = 0;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5890F0_005890f0_at_00589108(ctx);  // tail call
}

// 0x005892E8 sub_5892E8 -- 244 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// Moves the data of an SJ into two chunks: reads the free amount (vtable +36), takes a chunk (+24); when it is short,
// takes a second one and puts it back (+28); puts the first back (+28).
void sub_5892E8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005892e8
    enter(ctx, 31);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a3;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    lw(v1, s0, 0);
    lw(v0, v1, 36);
    s3 = a2;
    jalr(ctx, 0x589318u, v0.u());
    a2 = 0x7FFF0000;
    s4 = v0;
    lw(v0, s0, 0);
    a0 = s0;
    a1 = s2;
    lw(v1, v0, 24);
    a2 = a2 | 0xFFFF;
    a3 = s3;
    jalr(ctx, 0x58933Cu, v1.u());
    a0 = s0;
    lw(v0, s3, 4);
    a2 = 0x7FFF0000;
    a1 = s2;
    a2 = a2 | 0xFFFF;
    v0 = slt(v0, s4);
    a3 = s1;
    if (v0 == 0) {
        // 0x00589398
        charge(ctx, 3);
        sw(zero, s1, 4);
        sw(zero, s1, 0);
        lw(v1, s0, 0);
    } else {
        // 0x00589364
        charge(ctx, 12);
        lw(v0, s0, 0);
        lw(v1, v0, 24);
        jalr(ctx, 0x58936Cu, v1.u());
        lw(a1, s0, 0);
        a2 = s1;
        a0 = s0;
        lw(v0, a1, 28);
        a1 = s2;
        jalr(ctx, 0x589384u, v0.u());
        lw(v1, s0, 0);
    }
    // 0x005893a4
    charge(ctx, 14);
    a0 = s0;
    a1 = s2;
    lw(v0, v1, 28);
    a2 = s3;
    jalr(ctx, 0x5893B0u, v0.u());
    v0 = s4;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x005893E0 sub_5893E0 -- 88 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// Takes a chunk from an SJ lane (+24) and puts it to the other lane (+32).
void sub_5893E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005893e0
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = sltiu(a1, 1);
    sd(ra, sp, 0x20);
    lw(v1, s0, 0);
    lw(v0, v1, 24);
    a3 = sp;
    jalr(ctx, 0x589400u, v0.u());
    lw(v1, s0, 0);
    a0 = s0;
    a1 = s1;
    lw(v0, v1, 32);
    a2 = sp;
    jalr(ctx, 0x589418u, v0.u());
    lw(v0, sp, 0x4);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00589438 sub_589438 -- 112 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// Reads stream n's two words +40 / +44 (4920) under the SFD lock.
void sub_589438(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00589438
    enter(ctx, 28);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    sp = addiu(sp, -0x30);
    v0 = subu(v0, a1);
    sd(s0, sp, 0x10);
    v0 = sll(v0, 2);
    sd(s1, sp, 0x18);
    v0 = addu(v0, a1);
    sd(s2, sp, 0x20);
    v0 = sll(v0, 2);
    s1 = a2;
    s0 = addu(a0, v0);
    a0 = sp;
    s0 = addiu(s0, stm::kBase + stm::kPos);
    sd(ra, sp, 0x28);
    s2 = a3;
    jal(ctx, 0x589470u, gen::fn_sub_58C100_0058c100);
    lw(v1, s0, 0);
    a0 = sp;
    sw(v1, s1, 0);
    lw(v0, s0, 4);
    link(ctx, 0x589488u);  // $ra first: the delay slot below depends on it
    sw(v0, s2, 0);
    call(ctx, gen::fn_sub_58C118_0058c118);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x005894A8 sub_5894A8 -- 104 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// Writes stream n's two words +40 / +44 (4920) under the SFD lock.
void sub_5894A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005894a8
    enter(ctx, 26);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    sp = addiu(sp, -0x30);
    v0 = subu(v0, a1);
    sd(s0, sp, 0x10);
    v0 = sll(v0, 2);
    sd(s1, sp, 0x18);
    v0 = addu(v0, a1);
    sd(s2, sp, 0x20);
    v0 = sll(v0, 2);
    s1 = a3;
    s0 = addu(a0, v0);
    a0 = sp;
    s2 = a2;
    sd(ra, sp, 0x28);
    s0 = addiu(s0, stm::kBase + stm::kPos);
    jal(ctx, 0x5894E0u, gen::fn_sub_58C100_0058c100);
    sw(s1, s0, 4);
    a0 = sp;
    link(ctx, 0x5894F0u);  // $ra first: the delay slot below depends on it
    sw(s2, s0, 0);
    call(ctx, gen::fn_sub_58C118_0058c118);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00589510 sub_589510 -- 32 bytes; leaf frame (no stack)
// Stream n's word +28 (4908).
void sub_589510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00589510
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    v0 = subu(v0, a1);
    v0 = sll(v0, 2);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    lw(v0, a0, stm::kBase + stm::kBufSize);
}

// 0x00589530 sub_589530 -- 32 bytes; leaf frame (no stack)
// Stream n's word +52 (4932).
void sub_589530(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00589530
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    v0 = subu(v0, a1);
    v0 = sll(v0, 2);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    lw(v0, a0, stm::kBase + stm::kCount);
}

// 0x00589550 sub_589550 -- 156 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// Stream n's available amount under the SFD lock: word +48, or when it is 0 and +52 is set, +52 plus the SJ's amount
// (vtable +36, lane 1); a negative sum gives 0x7FFFFFFF.
void sub_589550(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00589550
    enter(ctx, 17);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    sp = addiu(sp, -0x30);
    v0 = subu(v0, a1);
    sd(s0, sp, 0x10);
    v0 = sll(v0, 2);
    sd(s1, sp, 0x18);
    v0 = addu(v0, a1);
    sd(s2, sp, 0x20);
    v0 = sll(v0, 2);
    sd(ra, sp, 0x28);
    v1 = addu(a0, v0);
    a0 = sp;
    s0 = addiu(v1, stm::kBase + stm::kDesc);
    jal(ctx, 0x589580u, gen::fn_sub_58C100_0058c100);
    lw(s1, s0, 32);
    lw(s2, s0, 36);
    if (s1 == 0) {
        // 0x00589594
        charge(ctx, 2);
        v0 = 0x7FFF0000;
        if (s2 != 0) {
            // 0x0058959c
            charge(ctx, 7);
            lw(v0, s0, 4);
            lw(v1, v0, 0);
            a0 = v0;
            lw(v0, v1, 36);
            a1 = 1;
            jalr(ctx, 0x5895ACu, v0.u());
            s1 = addu(s2, v0);
            goto L_005895b8;
        }
        goto L_005895bc;
    }
L_005895b8:
    charge(ctx, 1);
    v0 = 0x7FFF0000;
L_005895bc:
    charge(ctx, 12);
    v1 = slti(s1, 0);
    v0 = v0 | 0xFFFF;
    a0 = sp;
    if (v1 != 0) s1 = v0;
    jal(ctx, 0x5895C8u, gen::fn_sub_58C118_0058c118);
    ld(s0, sp, 0x10);
    v0 = s1;
    ld(s2, sp, 0x20);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x00589650 sub_589650 -- 52 bytes; leaf frame (no stack)
// Adds $a2 to stream n's counter +52 when it is not negative.
void sub_589650(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00589650
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    v0 = subu(v0, a1);
    v0 = sll(v0, 2);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    a0 = addiu(a0, stm::kBase + stm::kDesc);
    lw(v0, a0, 36);
    v1 = addu(v0, a2);
    if (i64(v0) >= 0) {
        // 0x00589678
        charge(ctx, 1);
        sw(v1, a0, 36);
    }
    // 0x0058967c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00589CF0 sub_589CF0 -- 32 bytes; leaf frame (no stack)
// Sets stream n's word +12 (4892, the end flag).
void sub_589CF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x00589cf0
    enter(ctx, 8);  // entry check point + this block's cycles
    v0 = sll(a1, 3);
    v0 = subu(v0, a1);
    v0 = sll(v0, 2);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    sw(a2, a0, stm::kBase + stm::kOutEnd);
}

// 0x00589D30 sub_589D30 -- 40 bytes; frame 0x30: ra sp+0x20
// Chunk of stream n (sub_589018): returns its end, word 1 + word 3.
void sub_589D30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00589d30
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(ra, sp, 0x20);
    a2 = sp;
    jal(ctx, 0x589D38u, gen::fn_sub_589018_00589018);
    lw(v1, sp, 0x4);
    lw(v0, sp, 0xC);
    ld(ra, sp, 0x20);
    v0 = addu(v1, v0);
    sp = addiu(sp, 0x30);
}

// 0x00589E38 sub_589E38 -- 144 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// Records the class uuids of the memory SJ (sub_562388) and the ring SJ (sub_561970): builds one of each on the stack,
// reads its uuid (vtable +16) to 0x9A6EF0 / 0x9A6EF4 and destroys it (+12).
void sub_589E38(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00589e38
    enter(ctx, 36);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 0;
    a0 = sp;
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x18);
    a1 = 8;
    jal(ctx, 0x589E4Cu, gen::fn_sub_562388_00562388);
    s0 = v0;
    lw(v1, s0, 0);
    lw(v0, v1, 16);
    a0 = s0;
    jalr(ctx, 0x589E60u, v0.u());
    v1 = 0x9A0000;
    sw(v0, v1, 28400);  // 0x9A6EF0
    lw(v0, s0, 0);
    lw(v1, v0, 12);
    a0 = s0;
    jalr(ctx, 0x589E78u, v1.u());
    a1 = 8;
    a0 = sp;
    jal(ctx, 0x589E84u, gen::fn_sub_561970_00561970);
    s0 = v0;
    lw(v1, s0, 0);
    lw(v0, v1, 16);
    a0 = s0;
    jalr(ctx, 0x589E98u, v0.u());
    v1 = 0x9A0000;
    sw(v0, v1, 28404);  // 0x9A6EF4
    lw(v0, s0, 0);
    lw(v1, v0, 12);
    a0 = s0;
    jalr(ctx, 0x589EB0u, v1.u());
    ld(s0, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x00589EC8 sub_589EC8 -- 52 bytes; frame 0x10: ra sp+0x0
// 1 when an SJ's uuid (vtable +16) equals the memory SJ's (0x9A6EF0).
void sub_589EC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00589ec8
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(v1, a0, 0);
    lw(v0, v1, 16);
    jalr(ctx, 0x589ED8u, v0.u());
    v1 = 0x9A0000;
    lw(a0, v1, 28400);  // 0x9A6EF0
    ld(ra, sp, 0x0);
    v0 = v0 ^ a0;
    v0 = sltiu(v0, 1);
    sp = addiu(sp, 0x10);
}

// 0x00589FD0 sub_589FD0 -- 32 bytes; frame 0x10: ra sp+0x0
// 1 when the SFD parameter 49 is set (sub_599408).
void sub_589FD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00589fd0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    a1 = 49;
    jal(ctx, 0x589FD8u, gen::fn_sub_599408_00599408);
    ld(ra, sp, 0x0);
    v0 = sltu(0, v0);
    sp = addiu(sp, 0x10);
}

// 0x00589FF0 sub_589FF0 -- 72 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// 1 when the SFD parameter 49 or 56 is set.
void sub_589FF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00589ff0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 49;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x58A000u, gen::fn_sub_599408_00599408);
    a0 = s0;
    a1 = 56;
    if (v0 == 0) {
        // 0x0058a014
        charge(ctx, 4);
        jal(ctx, 0x58A014u, gen::fn_sub_599408_00599408);
        ld(s0, sp, 0x0);
        if (v0 != 0) {
            goto L_0058a024;
        }
        // 0x0058a02c (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_0058a024:
    charge(ctx, 2);
    v0 = 1;
    ld(s0, sp, 0x0);
    // 0x0058a02c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0058A038 sub_58A038 -- 72 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// 1 when the SFD parameter 49 or 57 is set.
void sub_58A038(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058a038
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 49;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x58A048u, gen::fn_sub_599408_00599408);
    a0 = s0;
    a1 = 57;
    if (v0 == 0) {
        // 0x0058a05c
        charge(ctx, 4);
        jal(ctx, 0x58A05Cu, gen::fn_sub_599408_00599408);
        ld(s0, sp, 0x0);
        if (v0 != 0) {
            goto L_0058a06c;
        }
        // 0x0058a074 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_0058a06c:
    charge(ctx, 2);
    v0 = 1;
    ld(s0, sp, 0x0);
    // 0x0058a074 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0058AA20 sub_58AA20 -- 104 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, s2 sp+0x10, ra sp+0x18
// Finds a 32-bit code (sub_5776B0 at each byte) in a buffer of n bytes; its address, or 0 when fewer than 4 bytes
// remain.
void sub_58AA20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058aa20
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a1;
    v0 = slti(s1, 4);
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x18);
    s0 = a0;
    if (v0 == 0) {
        for (;;) {
            // 0x0058aa48
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x58AA48u, gen::fn_sub_5776B0_005776b0);
            s1 = addiu(s1, -1);
            if (v0 == s2) {
                goto L_0058aa58_2;
            }
            // 0x0058aa60
            charge(ctx, 3);
            v0 = slti(s1, 4);
            s0 = addiu(s0, 1);
            if (v0 != 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0058aa6c
    charge(ctx, 1);
    v0 = 0;
    // 0x0058aa70 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    return;
L_0058aa58_2:
    charge(ctx, 2);
    v0 = s0;
    // 0x0058aa70 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0058AB08 sub_58AB08 -- 148 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// 1 when sub_58ABA0 matches at any of the offsets 0, 2, 1, 3 of the buffer.
void sub_58AB08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058ab08
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x58AB24u, gen::fn_sub_58ABA0_0058aba0);
    a0 = addiu(s0, 2);
    a1 = addiu(s1, -2);
    a2 = s2;
    if (v0 == 0) {
        // 0x0058ab3c
        charge(ctx, 4);
        jal(ctx, 0x58AB3Cu, gen::fn_sub_58ABA0_0058aba0);
        if (v0 != 0) {
            v0 = 1;
        } else {
            // 0x0058ab4c
            charge(ctx, 8);
            a0 = addiu(s0, 1);
            a1 = addiu(s1, -1);
            a2 = s2;
            jal(ctx, 0x58AB54u, gen::fn_sub_58ABA0_0058aba0);
            a0 = addiu(s0, 3);
            a1 = addiu(s1, -3);
            a2 = s2;
            if (v0 != 0) {
                goto L_0058ab6c;
            }
            // 0x0058ab78
            charge(ctx, 3);
            jal(ctx, 0x58AB78u, gen::fn_sub_58ABA0_0058aba0);
            v0 = sltu(0, v0);
        }
        // 0x0058ab84 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_0058ab6c:
    charge(ctx, 2);
    v0 = 1;
    // 0x0058ab84 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0058ADA8 sub_58ADA8 -- 164 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// Reads an audio frame header (sub_58AE50) to the stack; when found, stores its rate and mode from the tables 0x7C9E30
// / 0x7C9E40 to the output (+40 / +44), clears +12 and keeps the header in 0x7B4558..0x7B4563.
void sub_58ADA8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058ada8
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = a0;
    v1 = a1;
    a1 = v0;
    sd(s0, sp, 0x10);
    s0 = a2;
    a0 = sp;
    sd(ra, sp, 0x18);
    a2 = v1;
    jal(ctx, 0x58ADC8u, gen::fn_sub_58AE50_0058ae50);
    lbu(a0, sp, 0x6);
    if (v0 != 0) {
        // 0x0058add8
        charge(ctx, 25);
        v0 = 1;
        lbu(a1, sp, 0x3);
        a0 = sll(a0, 2);
        sw(zero, s0, 12);
        v1 = 0x7D0000;
        v1 = addu(v1, a0);
        lbu(v1, v1, -25040);
        a1 = sll(a1, 2);
        sb(v1, s0, 40);
        v1 = 0x7B0000;
        a0 = 0x7D0000;
        a0 = addu(a0, a1);
        lw(a0, a0, -25024);
        sw(a0, s0, 44);
        a3 = addiu(v1, 17752);  // &0x7B4558
        ldl(a0, sp, 0x7);
        ldr(a0, sp, 0x0);
        lb(a1, sp, 0x8);
        lb(a2, sp, 0x9);
        sdl(a0, a3, 7);  // 0x7B455F
        sdr(a0, a3, 0);  // 0x7B4558
        sb(a1, a3, 8);  // 0x7B4560
        sb(a2, a3, 9);  // 0x7B4561
        lb(a0, sp, 0xA);
        sb(a0, a3, 10);  // 0x7B4562
    }
    // 0x0058ae3c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0058AE50 sub_58AE50 -- 208 bytes; frame 0x40: s2 sp+0x10, s0 sp+0x0, s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, s5 sp+0x28, s6 sp+0x30, ra sp+0x38
// Scans a buffer (at least 4 bytes) for an audio sync word 0xFF Fx, decoding each candidate (sub_58AF20) until a valid
// header is found.
void sub_58AE50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058ae50
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s2, sp, 0x10);
    s2 = a2;
    v0 = slti(s2, 4);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s3, sp, 0x18);
    s0 = a1;
    sd(s4, sp, 0x20);
    sd(s5, sp, 0x28);
    sd(s6, sp, 0x30);
    sd(ra, sp, 0x38);
    if (v0 == 0) {
        // 0x0058ae88
        charge(ctx, 4);
        s6 = 255;
        s5 = 248;
        s4 = 15;
        s3 = 3;
        for (;;) {
            // 0x0058ae98
            charge(ctx, 3);
            lbu(v0, s0, 0);
            if (v0 != s6) {
                s2 = addiu(s2, -1);
            } else {
                // 0x0058aea4
                charge(ctx, 4);
                lbu(v0, s0, 1);
                v0 = v0 & 0xF8;
                if (v0 != s5) {
                    s2 = addiu(s2, -1);
                    goto L_0058aee8;
                }
                // 0x0058aeb4
                charge(ctx, 6);
                a1 = s0;
                a0 = s1;
                jal(ctx, 0x58AEB8u, gen::fn_sub_58AF20_0058af20);
                lbu(v0, s1, 0);
                if (v0 == 0) {
                    s2 = addiu(s2, -1);
                    goto L_0058aee8;
                }
                // 0x0058aecc
                charge(ctx, 3);
                lbu(v0, s1, 2);
                if (v0 == s4) {
                    s2 = addiu(s2, -1);
                    goto L_0058aee8;
                }
                // 0x0058aed8
                charge(ctx, 3);
                lbu(v1, s1, 3);
                v0 = s0;
                if (v1 == s3) {
                    // 0x0058aee4
                    charge(ctx, 1);
                    s2 = addiu(s2, -1);
                    goto L_0058aee8;
                }
                break;
            }
        L_0058aee8:
            charge(ctx, 3);
            v0 = slti(s2, 4);
            s0 = addiu(s0, 1);
            if (v0 != 0) {
                goto L_0058aef4;
            }
            backedge(ctx);
        }
        // 0x0058aef8 (the shared epilogue, written out on this path)
        charge(ctx, 10);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(s6, sp, 0x30);
        ld(ra, sp, 0x38);
        sp = addiu(sp, 0x40);
        return;
    }
L_0058aef4:
    charge(ctx, 1);
    v0 = 0;
    // 0x0058aef8 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x0058AFA0 sub_58AFA0 -- 356 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// Walks the 0x40 markers of a buffer (sub_578160), reading each marker's mode nibbles, and records what it finds in
// the output; 1 when the buffer is used up.
void sub_58AFA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0058afa0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x28);
    if (i64(s0) > 0) {
        // 0x0058afcc
        charge(ctx, 5);
        v0 = 0x7D0000;
        v1 = 0x7D0000;
        s3 = addiu(v0, -25080);  // &0x7C9E08
        s4 = addiu(v1, -24528);  // &0x7CA030
        a0 = s1;
        for (;;) {
            // 0x0058afe0
            charge(ctx, 6);
            a1 = s0;
            a2 = 64;
            jal(ctx, 0x58AFE4u, gen::fn_sub_578160_00578160);
            a1 = v0;
            a0 = subu(a1, s1);
            if (a1 == 0) {
                break;
            }
            // 0x0058aff8
            charge(ctx, 17);
            lbu(a2, a1, 7);
            a0 = addiu(a0, 1);
            s0 = subu(s0, a0);
            s1 = addu(s1, a0);
            v1 = srl(a2, 4);
            a2 = a2 & 0xF;
            v0 = addiu(a2, 255);
            lbu(t4, a1, 11);
            v0 = v0 & 0xFF;
            lbu(a3, a1, 10);
            v0 = sltiu(v0, 8);
            lbu(t0, a1, 4);
            lbu(a0, a1, 5);
            lbu(t1, a1, 6);
            lbu(t2, a1, 8);
            lbu(t3, a1, 9);
            if (v1 != 0) {
                // 0x0058b03c
                charge(ctx, 2);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = srl(a3, 5);
                if (cc) {
                    goto L_0058b0d8;
                }
                // 0x0058b044
                charge(ctx, 4);
                v0 = v0 & 0x1;
                v0 = v0 & 0xFF;
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = a0 & 0xF;
                if (cc) {
                    goto L_0058b0d8;
                }
                goto L_0058b054_6;
            }
        L_0058b0d8:
            charge(ctx, 2);
            a0 = s1;
            if (i64(s0) <= 0) {
                goto L_0058b0e0;
            }
            backedge(ctx);
        }
        // 0x0058b0e4 (the shared epilogue, written out on this path)
        charge(ctx, 8);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        return;
    }
L_0058b0e0:
    charge(ctx, 1);
    v0 = 1;
    // 0x0058b0e4 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
    return;
L_0058b054_6:
    charge(ctx, 9);
    a0 = srl(a0, 4);
    v1 = sll(t0, 4);
    v0 = sll(v0, 8);
    lw(a1, s2, 28);
    v1 = v1 | a0;
    v0 = v0 | t1;
    sw(v1, s2, 20);
    sw(v0, s2, 24);
    if (a1 == 0) {
        // 0x0058b078
        charge(ctx, 11);
        v0 = sll(t3, 2);
        v1 = sll(t2, 10);
        v1 = v1 | v0;
        a0 = srl(a3, 6);
        v1 = v1 | a0;
        v0 = sll(v1, 1);
        v0 = addu(v0, v1);
        v0 = sll(v0, 3);
        v0 = addu(v0, v1);
        v0 = sll(v0, 1);
        sw(v0, s2, 28);
    }
    // 0x0058b0a4
    charge(ctx, 12);
    v1 = sll(a2, 2);
    v0 = a3 & 0x1F;
    v1 = addu(v1, s3);
    v0 = sll(v0, 5);
    a0 = srl(t4, 3);
    lw(a1, v1, 0);
    v0 = v0 | a0;
    sw(s4, s2, 8);
    v0 = sll(v0, 11);
    sw(a1, s2, 32);
    sw(v0, s2, 36);
    goto L_0058b0e0;
}

// 0x0058B168 sub_58B168 -- 184 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Private-stream packet: for type 2 checks the header (sub_58B220) and skips it, then hands the payload to sub_58B2D0;
// the flag output tells the caller to skip the 18-byte header.
void sub_58B168(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058b168
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v1 = 2;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a3;
    sd(s2, sp, 0x10);
    s2 = t0;
    s0 = addiu(s0, -6);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    s1 = addiu(s1, 6);
    s3 = a0;
    a0 = s0;
    sw(zero, s2, 0);
    v0 = 0;
    if (a1 == v1) {
        // 0x0058b1ac
        charge(ctx, 4);
        jal(ctx, 0x58B1ACu, gen::fn_sub_58B220_0058b220);
        if (v0 != 0) {
            s0 = addiu(s0, -12);
        } else {
            // 0x0058b1bc
            charge(ctx, 6);
            s0 = addiu(s0, -2);
            s1 = addiu(s1, 2);
            a0 = s0;
            jal(ctx, 0x58B1C4u, gen::fn_sub_58B220_0058b220);
            s0 = addiu(s0, -12);
            if (v0 != 0) {
                goto L_0058b1d4;
            }
            // 0x0058b204 (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(s0, sp, 0x0);
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(ra, sp, 0x20);
            sp = addiu(sp, 0x30);
            return;
        }
    L_0058b1d4:
        charge(ctx, 8);
        s1 = addiu(s1, 12);
        a0 = s0;
        a1 = s1;
        jal(ctx, 0x58B1DCu, gen::fn_sub_58B278_0058b278);
        a0 = s3;
        a1 = s0;
        a2 = s1;
        if (v0 != 0) {
            // 0x0058b1f4
            charge(ctx, 4);
            jal(ctx, 0x58B1F4u, gen::fn_sub_58B2D0_0058b2d0);
            sw(v0, s2, 0);
            v0 = 1;
        }
    }
    // 0x0058b204 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0058B2D0 sub_58B2D0 -- 196 bytes; frame 0x30: s1 sp+0x8, s4 sp+0x20, s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, ra sp+0x28
// Calls the user callback of parameter 75 with parameter 76 and the data, then copies up to 2048 bytes to the handle's
// record (+268, memcpy) with its length (+264) and sub_58B560.
void sub_58B2D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058b2d0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s4, sp, 0x20);
    s4 = a1;
    a1 = 75;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x28);
    s3 = addiu(s1, 120);
    jal(ctx, 0x58B2FCu, gen::fn_sub_599408_00599408);
    a0 = s1;
    a1 = 76;
    s0 = v0;
    jal(ctx, 0x58B30Cu, gen::fn_sub_599408_00599408);
    a0 = v0;
    a1 = s4;
    a2 = s2;
    if (s0 != 0) {
        // 0x0058b324
        charge(ctx, 2);
        jalr(ctx, 0x58B324u, s0.u());
    }
    // 0x0058b32c
    charge(ctx, 3);
    lw(v1, s3, 0);
    v0 = 0;
    if (v1 == 0) {
        // 0x0058b338
        charge(ctx, 15);
        v0 = slti(s2, 2049);
        s0 = 2048;
        if (v0 != 0) s0 = s2;
        a1 = s4;
        a2 = s0;
        a0 = addiu(s1, 268);
        jal(ctx, 0x58B34Cu, gen::fn_sub_575410_00575410);
        sw(s0, s3, 144);
        a0 = s3;
        jal(ctx, 0x58B358u, gen::fn_sub_58B560_0058b560);
        a0 = s1;
        jal(ctx, 0x58B360u, gen::fn_sub_58BB80_0058bb80);
        a0 = s1;
        jal(ctx, 0x58B368u, gen::fn_sub_58B398_0058b398);
        v0 = 1;
    }
    // 0x0058b374 (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0058BC30 sub_58BC30 -- 104 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// SFD library init: banner text pointer (0x9A8198), the work size 14,256 (0x7B4794), the per-module init chain
// (atan2l_12, sub_58BC98, coshl_12, __env_lock_12).
// [proposed name: SFD_Init] (from the binary's own error / banner text; symbols/deltas/libs12.sym)
void sub_58BC30(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058bc30
    enter(ctx, 17);  // entry check point + this block's cycles
    v1 = 0x9B0000;
    v0 = 0x7D0000;
    sp = addiu(sp, -0x10);
    v1 = addiu(v1, -32360);  // &0x9A8198
    v0 = addiu(v0, -24736);  // "\nCRI SFD/PS2EE Ver.1.958 Build:Mar  1 2005 10:53:48\n"
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    a1 = 0x7B0000;
    sw(v0, v1, 0);  // 0x9A8198
    s0 = a0;
    a0 = 14256;
    link(ctx, 0x58BC5Cu);  // $ra first: the delay slot below depends on it
    sw(a0, a1, 18324);
    call(ctx, gen::fn_atan2l_12_0058c088);
    a0 = s0;
    jal(ctx, 0x58BC64u, gen::fn_sub_58BC98_0058bc98);
    if (v0 != 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0058bc74
        charge(ctx, 6);
        jal(ctx, 0x58BC74u, gen::fn_coshl_12_0058c0b8);
        jal(ctx, 0x58BC7Cu, gen::fn___env_lock_12_0058c0f0);
        v0 = 0;
        ld(s0, sp, 0x0);
    }
    // 0x0058bc8c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0058BC98 sub_58BC98 -- 192 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Clears and fills the SFD library work (0x7B4570: memset 137 words, memcpy 400 bytes from 0x7CA100), keeps the init
// arguments, the sub-inits (sub_58BE10, sub_5997F8, sub_588720, sub_58BD58) and clears the eight handle slots.
void sub_58BC98(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058bc98
    enter(ctx, 32);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 0;
    sd(s0, sp, 0x0);
    s0 = 0x7B0000;
    s0 = addiu(s0, 17776);  // &0x7B4570
    sd(s1, sp, 0x8);
    a2 = 137;
    s1 = a0;
    sd(ra, sp, 0x10);
    a0 = s0;
    jal(ctx, 0x58BCBCu, gen::fn_sub_575880_00575880);
    a1 = 0x7D0000;
    a2 = 400;
    a1 = addiu(a1, -24320);  // &0x7CA100
    a0 = s0;
    jal(ctx, 0x58BCD0u, gen::fn_sub_575410_00575410);
    ldl(v0, s1, 7);
    ldr(v0, s1, 0);
    sdl(v0, s0, 407);  // 0x7B4707
    sdr(v0, s0, 400);  // 0x7B4700
    sw(zero, s0, 408);  // 0x7B4708
    a0 = addiu(s0, 412);  // &0x7B470C
    jal(ctx, 0x58BCECu, gen::fn_sub_58BE10_0058be10);
    a0 = addiu(s0, 432);  // &0x7B4720
    link(ctx, 0x58BCF8u);  // $ra first: the delay slot below depends on it
    lw(a1, s1, 4);
    call(ctx, gen::fn_sub_5997F8_005997f8);
    a0 = addiu(s0, 444);  // &0x7B472C
    jal(ctx, 0x58BD00u, gen::fn_sub_588720_00588720);
    a0 = s0;
    jal(ctx, 0x58BD08u, gen::fn_sub_58BD58_0058bd58);
    v0 = 7;
    s0 = addiu(s0, 544);  // &0x7B4790
    for (;;) {
        // 0x0058bd18
        charge(ctx, 7);
        v0 = addiu(v0, -1);
        sw(zero, s0, 0);
        s0 = addiu(s0, -4);
        if (i64(v0) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0058bd34
    charge(ctx, 9);
    lw(a1, s1, 0);
    a0 = 0x7B0000;
    a0 = addiu(a0, 18224);  // &0x7B4730
    jal(ctx, 0x58BD3Cu, gen::fn_sub_59B4F0_0059b4f0);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0058C088 atan2l_12 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: sub_562288.
void atan2l_12(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0058c088
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_562288_00562288(ctx);  // tail call
}

// 0x0058C0B8 coshl_12 -- 28 bytes; frame 0x10: ra sp+0x0
// sub_595B30, then sub_58B108.
void coshl_12(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0058c0b8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x58C0C0u, gen::fn_sub_595B30_00595b30);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58B108_0058b108(ctx);  // tail call
}

// 0x0058C0F0 __env_lock_12 -- 8 bytes; leaf frame (no stack)
// Does nothing.
void __env_lock_12(EEContext& ctx) {
    using namespace hg;
    // 0x0058c0f0
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0058C308 sub_58C308 -- 112 bytes; frame 0x10: ra sp+0x0
// Transfer module init: spins when sub_58C378 reports (never), registers the module with sub_577A38(8, 0x9A81A0),
// error -16773887; clears 0x7B4798.
void sub_58C308(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058c308
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x58C310u, gen::fn_sub_58C378_0058c378);
    a1 = 0x9B0000;
    if (v0 != 0) {
        for (;;) {
            // 0x0058c320
            charge(ctx, 7);
            backedge(ctx);
        }
    }
    // 0x0058c340
    charge(ctx, 5);
    a0 = 8;
    a1 = addiu(a1, -32352);
    jal(ctx, 0x58C344u, gen::fn_sub_577A38_00577a38);
    ld(ra, sp, 0x0);
    if (v0 == 0) {
        // 0x0058c368
        charge(ctx, 4);
        v1 = 0x7B0000;
        sw(zero, v1, 18328);  // 0x7B4798
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0058c354
    charge(ctx, 5);
    a1 = lui(0xFF00);
    a0 = 0;
    a1 = a1 | 0xD01;
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0058C378 sub_58C378 -- 8 bytes; leaf frame (no stack)
// Returns nothing (an empty check the caller tests).
void sub_58C378(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0058c378
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0058C3A0 r_lock_def_get_free_item_6 -- 140 bytes; frame 0x10: ra sp+0x0
// Per-handle demux server: returns 0 when every output stream has ended (sub_58D578); else reads the input
// (sub_58C430), demuxes it (sub_58C490) and with status 2 (+72) runs the header steps (sub_58D800).
void r_lock_def_get_free_item_6(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058c3a0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0058c3b8
    charge(ctx, 9);
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s0 = a0;
    jal(ctx, 0x58C3C8u, gen::fn_sub_58D578_0058d578);
    v1 = 1;
    a0 = s0;
    if (v0 != v1) {
        // 0x0058c3e8
        charge(ctx, 9);
        jal(ctx, 0x58C3E8u, gen::fn_sub_58C430_0058c430);
        a0 = s0;
        jal(ctx, 0x58C3F0u, gen::fn_sub_58C490_0058c490);
        lw(v1, s0, 72);
        s1 = v0;
        v0 = 2;
        a0 = s0;
        if (v1 == v0) {
            // 0x0058c40c
            charge(ctx, 2);
            jal(ctx, 0x58C40Cu, gen::fn_sub_58D800_0058d800);
        }
        // 0x0058c414
        charge(ctx, 1);
        v0 = s1;
    } else {
        // 0x0058c3dc
        charge(ctx, 2);
        v0 = 0;
    }
    // 0x0058c418 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0058C430 sub_58C430 -- 92 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x18, s2 sp+0x10
// Feeds the demux object (*(+8060)) with the parameters 85 / 86 (sub_5759B0).
void sub_58C430(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058c430
    enter(ctx, 23);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 85;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x18);
    sd(s2, sp, 0x10);
    lw(v0, s0, trn::kDemuxWork);
    link(ctx, 0x58C450u);  // $ra first: the delay slot below depends on it
    lw(s2, v0, 0);
    call(ctx, gen::fn_sub_599408_00599408);
    a0 = s0;
    a1 = 86;
    s1 = v0;
    jal(ctx, 0x58C460u, gen::fn_sub_599408_00599408);
    ld(s0, sp, 0x0);
    a0 = s2;
    a1 = s1;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    a2 = v0;
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_5759B0_005759b0(ctx);  // tail call
}

// 0x0058C490 sub_58C490 -- 248 bytes; frame 0x60: s0 sp+0x20, s1 sp+0x28, s2 sp+0x30, s3 sp+0x38, s4 sp+0x40, s5 sp+0x48, ra sp+0x50
// Demux loop: takes the input chunk (sub_58C588), splits it into packets (sub_58C6B0), releases what was used
// (sub_58C648) and counts the bytes (sub_58DDC0), until no data or an error.
void sub_58C490(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058c490
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s0, sp, 0x20);
    s0 = 0;
    sd(s1, sp, 0x28);
    s1 = a0;
    sd(s2, sp, 0x30);
    s2 = 0;
    sd(s3, sp, 0x38);
    s3 = 0;
    sd(s4, sp, 0x40);
    s4 = 0x7FFF0000;
    sd(s5, sp, 0x48);
    s4 = s4 | 0xFFFE;
    sd(ra, sp, 0x50);
    lw(s5, s1, 40);
    for (;;) {
        // 0x0058c4f4
        charge(ctx, 3);
        v0 = slt(s4, s2);
        a0 = s1;
        if (v0 == 0) {
            // 0x0058c500
            charge(ctx, 10);
            a3 = s5;
            t0 = addiu(sp, 0x8);
            a1 = sp;
            a2 = addiu(sp, 0x4);
            jal(ctx, 0x58C50Cu, gen::fn_sub_58C588_0058c588);
            a0 = s1;
            s0 = v0;
            a3 = addiu(sp, 0xC);
            t0 = addiu(sp, 0x10);
            if (s0 == 0) {
                // 0x0058c528
                charge(ctx, 7);
                lw(a1, sp, 0x0);
                lw(a2, sp, 0x4);
                link(ctx, 0x58C530u);  // $ra first: the delay slot below depends on it
                lw(t1, sp, 0x8);
                call(ctx, gen::fn_sub_58C6B0_0058c6b0);
                s0 = v0;
                a0 = s1;
                if (s0 != 0) {
                    goto L_0058c550;
                }
                // 0x0058c544
                charge(ctx, 3);
                lw(a1, sp, 0xC);
                if (a1 == 0) {
                    goto L_0058c550;
                }
                backedge(ctx);
                // 0x0058c4d0
                charge(ctx, 5);
                jal(ctx, 0x58C4D0u, gen::fn_sub_58C648_0058c648);
                s0 = v0;
                a0 = s1;
                if (s0 == 0) {
                    // 0x0058c4e4
                    charge(ctx, 4);
                    lw(v0, sp, 0x10);
                    lw(v1, sp, 0xC);
                    s3 = addu(s3, v0);
                    s2 = addu(s2, v1);
                    continue;
                }
            }
        }
        break;
    }
L_0058c554:
    charge(ctx, 13);
    a1 = s2;
    a2 = s3;
    jal(ctx, 0x58C558u, gen::fn_sub_58DDC0_0058ddc0);
    v0 = s0;
    ld(s1, sp, 0x28);
    ld(s0, sp, 0x20);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(ra, sp, 0x50);
    sp = addiu(sp, 0x60);
    return;
L_0058c550:
    charge(ctx, 1);
    a0 = s1;
    goto L_0058c554;
}

// 0x0058C588 sub_58C588 -- 192 bytes; frame 0x50: s0 sp+0x20, s1 sp+0x28, s2 sp+0x30, s3 sp+0x38, ra sp+0x40
// Input chunk of the demux (sub_589018 on the input stream +8068): its address, length and end; data shorter than 2048
// bytes waits unless the input ended.
void sub_58C588(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0058c588
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x20);
    s0 = a0;
    sd(s1, sp, 0x28);
    s1 = a2;
    sd(s2, sp, 0x30);
    s2 = t0;
    sd(s3, sp, 0x38);
    s3 = a1;
    sd(ra, sp, 0x40);
    a2 = sp;
    link(ctx, 0x58C5B4u);  // $ra first: the delay slot below depends on it
    lw(a1, s0, trn::kDemuxIn);
    call(ctx, gen::fn_sub_589018_00589018);
    if (v0 != 0) {
        ld(s0, sp, 0x20);
    } else {
        // 0x0058c5c4
        charge(ctx, 11);
        lw(v0, sp, 0x4);
        lw(v1, sp, 0xC);
        sw(v0, s1, 0);
        v1 = addu(v0, v1);
        lw(a1, sp, 0x0);
        sw(v1, s2, 0);
        sw(a1, s3, 0);
        lw(a2, s1, 0);
        v0 = slti(a2, 2048);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = 0;
        if (!cc) {
            // 0x0058c5f0
            charge(ctx, 3);
            lw(v0, s0, 14252);
            cc = a1 == v0;  // the condition, before the delay slot changes it
            v0 = 0;
            if (!cc) {
                // 0x0058c5fc
                charge(ctx, 4);
                lw(v0, s0, 14248);
                v0 = v0 & 0x7FF;
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = 0;
                if (!cc) {
                    // 0x0058c60c
                    charge(ctx, 3);
                    lw(v0, s0, 14240);
                    lw(a0, s0, 14244);
                    if (v0 != 0) {
                        // 0x0058c618
                        charge(ctx, 2);
                        jalr(ctx, 0x58C618u, v0.u());
                    }
                    // 0x0058c620
                    charge(ctx, 3);
                    lw(v0, s3, 0);
                    sw(v0, s0, 14252);
                    v0 = 0;
                }
            }
        }
        // 0x0058c62c
        charge(ctx, 1);
        ld(s0, sp, 0x20);
    }
    // 0x0058c630 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x0058C648 sub_58C648 -- 76 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Releases n bytes of the input stream (sub_5890F0) and adds them to the input total +14248.
void sub_58C648(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058c648
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    a2 = s1;
    link(ctx, 0x58C664u);  // $ra first: the delay slot below depends on it
    lw(a1, s0, trn::kDemuxIn);
    call(ctx, gen::fn_sub_5890F0_005890f0);
    if (v0 != 0) {
        ld(s0, sp, 0x0);
    } else {
        // 0x0058c674
        charge(ctx, 4);
        lw(v1, s0, 14248);
        v1 = addu(v1, s1);
        sw(v1, s0, 14248);
        ld(s0, sp, 0x0);
    }
    // 0x0058c684 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0058C6B0 sub_58C6B0 -- 720 bytes; frame 0x70: s2 sp+0x30, s5 sp+0x48, s1 sp+0x28, s6 sp+0x50, s7 sp+0x58, s0 sp+0x20, s3 sp+0x38, s4 sp+0x40, fp sp+0x60, ra sp+0x68
// Demuxes one packet of the input: the start code (sub_5776B0), the pack / system headers (sub_58D600), the packet
// search (sub_58C980 / sub_58CB28) and the hand-over to the outputs.
void sub_58C6B0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0058c6b0
    enter(ctx, 25);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s2, sp, 0x30);
    s2 = t0;
    sd(s5, sp, 0x48);
    s5 = a3;
    sd(s1, sp, 0x28);
    s1 = a0;
    sd(s6, sp, 0x50);
    s6 = a2;
    sd(s7, sp, 0x58);
    s7 = a1;
    sd(s0, sp, 0x20);
    a3 = t1;
    sd(s3, sp, 0x38);
    sd(s4, sp, 0x40);
    sd(fp, sp, 0x60);
    sd(ra, sp, 0x68);
    sw(zero, s5, 0);
    sw(zero, s2, 0);
    lw(s3, s1, trn::kDemuxWork);
    sw(zero, sp, 0x14);
    link(ctx, 0x58C704u);  // $ra first: the delay slot below depends on it
    lw(s4, s3, 0);
    call(ctx, gen::fn_sub_58D600_0058d600);
    if (v0 == 0) {
        ld(s0, sp, 0x20);
    } else {
        // 0x0058c714
        charge(ctx, 3);
        v0 = slti(s6, 4);
        if (v0 != 0) {
            fp = 0;
        } else {
            // 0x0058c720
            charge(ctx, 3);
            a0 = s7;
            jal(ctx, 0x58C720u, gen::fn_sub_5776B0_005776b0);
            fp = v0;
        }
        // 0x0058c72c
        charge(ctx, 30);
        a1 = 87;
        a0 = s1;
        jal(ctx, 0x58C730u, gen::fn_sub_599408_00599408);
        a0 = s1;
        a1 = 88;
        s0 = v0;
        jal(ctx, 0x58C740u, gen::fn_sub_599408_00599408);
        a0 = s4;
        a2 = v0;
        a1 = s0;
        jal(ctx, 0x58C750u, gen::fn_sub_575A00_00575a00);
        a0 = s1;
        a1 = 91;
        jal(ctx, 0x58C75Cu, gen::fn_sub_599408_00599408);
        a0 = s1;
        a1 = 92;
        s0 = v0;
        jal(ctx, 0x58C76Cu, gen::fn_sub_599408_00599408);
        a0 = s4;
        a1 = s0;
        a2 = v0;
        jal(ctx, 0x58C77Cu, gen::fn_sub_575A50_00575a50);
        a0 = s4;
        a1 = s7;
        a2 = s6;
        a3 = sp;
        t0 = addiu(sp, 0x4);
        jal(ctx, 0x58C794u, gen::fn_sub_575AA0_00575aa0);
        a0 = s1;
        if (v0 != 0) {
            // 0x0058c7a4
            charge(ctx, 4);
            a1 = lui(0xFF00);
            a1 = a1 | 0xD03;
            jal(ctx, 0x58C7A8u, gen::fn_sub_58BE40_0058be40);
            sw(v0, sp, 0x14);
        }
        // 0x0058c7b4
        charge(ctx, 5);
        lw(s0, sp, 0x4);
        v0 = 0x20000;
        v0 = s0 & v0;
        a1 = s4;
        if (v0 != 0) {
            // 0x0058c7c8
            charge(ctx, 5);
            a0 = s1;
            a2 = s7;
            a3 = s6;
            jal(ctx, 0x58C7D0u, gen::fn_sub_58DD08_0058dd08);
            lw(s0, sp, 0x4);
        }
        // 0x0058c7dc
        charge(ctx, 3);
        v0 = 0x80000;
        if (s0 == v0) {
            // 0x0058c7e8
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x58C7E8u, gen::fn_sub_589FD0_00589fd0);
            if (v0 != 0) {
                // 0x0058c7f8
                charge(ctx, 5);
                a0 = s1;
                jal(ctx, 0x58C7F8u, gen::fn_sub_58D5E8_0058d5e8);
                v0 = 2048;
                sw(v0, s5, 0);
                goto L_0058c948;
            }
            lw(v0, sp, 0x4);
            // 0x0058c810
            charge(ctx, 2);
            if (v0 != s0) {
                goto L_0058c830;
            }
            // 0x0058c818
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x58C818u, gen::fn_sub_589FF0_00589ff0);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = 2048;
            if (cc) {
                goto L_0058c830;
            }
            // 0x0058c828
            charge(ctx, 2);
            sw(v0, s5, 0);
        L_0058c948:
            charge(ctx, 1);
            sw(v0, s3, 344);
        L_0058c94c:
            charge(ctx, 1);
            lw(v0, sp, 0x14);
        L_0058c950:
            charge(ctx, 1);
            ld(s0, sp, 0x20);
            // 0x0058c954 (the shared epilogue, written out on this path)
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
            return;
        }
    L_0058c830:
        charge(ctx, 2);
        lw(v0, sp, 0x4);
        if (fp != 0) {
            // 0x0058c8b8
            charge(ctx, 4);
            v1 = 0x40000;
            v0 = v0 & v1;
            if (v0 != 0) {
                lw(a1, sp, 0x0);
                // 0x0058c908
                charge(ctx, 11);
                a0 = s1;
                a3 = addiu(sp, 0xC);
                t0 = addiu(sp, 0x10);
                a2 = subu(s6, a1);
                a1 = addu(s7, a1);
                jal(ctx, 0x58C918u, gen::fn_sub_58CB28_0058cb28);
                v1 = 1;
                sw(v0, sp, 0x14);
                lw(v0, sp, 0x10);
                cc = v0 != v1;  // the condition, before the delay slot changes it
                v0 = si(-1);
                if (!cc) {
                    // 0x0058c934
                    charge(ctx, 5);
                    lw(v0, sp, 0x0);
                    lw(v1, sp, 0xC);
                    v0 = addu(v0, v1);
                    sw(v0, s5, 0);
                    v0 = si(-1);
                }
                goto L_0058c948;
            }
            // 0x0058c8c8
            charge(ctx, 6);
            a0 = s1;
            a1 = addiu(sp, 0x8);
            jal(ctx, 0x58C8CCu, gen::fn_sub_58D798_0058d798);
            lw(v0, sp, 0x8);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            lw(v0, sp, 0x14);
            if (!cc) {
                // 0x0058c8e0
                charge(ctx, 4);
                lw(v0, s1, 40);
                v0 = slt(v0, s6);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                lw(v0, sp, 0x14);
                if (!cc) {
                    // 0x0058c8f0
                    charge(ctx, 3);
                    lw(v0, sp, 0x0);
                    if (i64(v0) <= 0) {
                        v0 = 1;
                    }
                    // 0x0058c8fc
                    charge(ctx, 3);
                    sw(v0, s5, 0);
                    sw(v0, s2, 0);
                    goto L_0058c94c;
                }
            }
            goto L_0058c950;
        }
        // 0x0058c838
        charge(ctx, 10);
        a1 = s7;
        a2 = s6;
        a0 = s1;
        a3 = s2;
        jal(ctx, 0x58C844u, gen::fn_sub_58C980_0058c980);
        lw(v0, s2, 0);
        sw(v0, s5, 0);
        lw(a1, s2, 0);
        lw(v0, sp, 0x14);
        if (i64(a1) <= 0) {
            goto L_0058c950;
        }
        // 0x0058c860
        charge(ctx, 3);
        lw(v1, s3, 344);
        ld(s0, sp, 0x20);
        if (i64(v1) >= 0) {
            // 0x0058c86c
            charge(ctx, 4);
            lw(a0, s1, 40);
            v0 = slt(v1, a0);
            a2 = addu(v1, a1);
            if (v0 == 0) {
                // 0x0058c87c
                charge(ctx, 2);
                v0 = addu(v1, a1);
                goto L_0058c948;
            }
            // 0x0058c888
            charge(ctx, 3);
            v0 = slt(a0, a2);
            if (v0 != 0) {
                // 0x0058c894
                charge(ctx, 6);
                v1 = subu(a0, v1);
                v1 = subu(a1, v1);
                sw(v1, s2, 0);
                lw(v0, s1, 40);
                v0 = addu(v0, v1);
                goto L_0058c948;
            }
            sw(a2, s3, 344);
            // 0x0058c8b0
            charge(ctx, 2);
            sw(zero, s2, 0);
            goto L_0058c94c;
        }
    }
    // 0x0058c954 (the shared epilogue, written out on this path)
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

// 0x0058C980 sub_58C980 -- 220 bytes; frame 0x40: s3 sp+0x18, s0 sp+0x0, s1 sp+0x8, s5 sp+0x28, s2 sp+0x10, s4 sp+0x20, ra sp+0x30
// Finds the next pack start in the input: at the expected position (sub_58CA60) or by a byte scan (sub_58CAA0);
// returns the position.
void sub_58C980(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058c980
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    sd(s5, sp, 0x28);
    s5 = a0;
    sd(s2, sp, 0x10);
    sd(s4, sp, 0x20);
    sd(ra, sp, 0x30);
    sw(zero, s3, 0);
    lw(s2, s5, 40);
    v0 = addiu(s2, 3);
    v0 = slt(s0, v0);
    s1 = a1;
    if (v0 == 0) {
        // 0x0058c9c4
        charge(ctx, 5);
        a0 = s1;
        a1 = s2;
        jal(ctx, 0x58C9C8u, gen::fn_sub_58CA60_0058ca60);
        if (v0 == 0) {
            goto L_0058c9d8;
        }
        sw(s2, s3, 0);
        // 0x0058ca38 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        return;
    }
L_0058c9d8:
    charge(ctx, 3);
    v0 = slti(s0, 4);
    s2 = 0;
    if (v0 == 0) {
        // 0x0058c9e4
        charge(ctx, 1);
        s4 = 0xD0000;
        for (;;) {
            // 0x0058c9e8
            charge(ctx, 6);
            a0 = s1;
            s1 = addiu(s1, 1);
            jal(ctx, 0x58C9ECu, gen::fn_sub_5776B0_005776b0);
            v0 = v0 & s4;
            if (v0 == 0) {
                // 0x0058ca00
                charge(ctx, 4);
                s0 = addiu(s0, -1);
                v0 = slti(s0, 4);
                s2 = addiu(s2, 1);
                if (v0 != 0) {
                    goto L_0058ca10;
                }
                backedge(ctx);
                continue;
            }
            sw(s2, s3, 0);
            break;
        }
        // 0x0058ca38 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(ra, sp, 0x30);
        sp = addiu(sp, 0x40);
        return;
    }
L_0058ca10:
    charge(ctx, 4);
    v0 = addiu(s0, -1);
    v0 = sltiu(v0, 3);
    if (v0 == 0) {
        sw(s2, s3, 0);
    } else {
        // 0x0058ca20
        charge(ctx, 6);
        a0 = s5;
        a1 = addu(s1, s0);
        jal(ctx, 0x58CA24u, gen::fn_sub_58CAA0_0058caa0);
        v1 = addu(s2, s0);
        if (v0 != 0) s2 = v1;
        sw(s2, s3, 0);
    }
    // 0x0058ca38 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0058CB00 sub_58CB00 -- 40 bytes; leaf frame (no stack)
// Address of the demux input stream's record: $a0 + 4896 + 116 * (+8068).
void sub_58CB00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0058cb00
    enter(ctx, 10);  // entry check point + this block's cycles
    v0 = a0;
    lw(a0, v0, trn::kDemuxIn);
    v1 = sll(a0, 3);
    v1 = subu(v1, a0);
    v1 = sll(v1, 2);
    v1 = addu(v1, a0);
    v1 = sll(v1, 2);
    v0 = addu(v0, v1);
    v0 = addiu(v0, stm::kBase + stm::kDesc);
}

// 0x0058CB28 sub_58CB28 -- 376 bytes; frame 0x80: s3 sp+0x48, s4 sp+0x50, s2 sp+0x40, s5 sp+0x58, s6 sp+0x60, s7 sp+0x68, s0 sp+0x30, s1 sp+0x38, ra sp+0x70
// Parses one packet with the demux object (sub_5779A8, errors -16773882 / -16773874) and hands its payload to its
// output (sub_58CCA0).
void sub_58CB28(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058cb28
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(s3, sp, 0x48);
    s3 = t0;
    sd(s4, sp, 0x50);
    s4 = a3;
    sd(s2, sp, 0x40);
    s2 = a0;
    sd(s5, sp, 0x58);
    s5 = a2;
    sd(s6, sp, 0x60);
    s6 = 0;
    sd(s7, sp, 0x68);
    s7 = a1;
    sd(s0, sp, 0x30);
    a1 = sp;
    sd(s1, sp, 0x38);
    sd(ra, sp, 0x70);
    sw(zero, s4, 0);
    sw(zero, s3, 0);
    lw(s1, s2, trn::kDemuxWork);
    link(ctx, 0x58CB78u);  // $ra first: the delay slot below depends on it
    lw(a0, s1, 0);
    call(ctx, gen::fn_sub_5779A8_005779a8);
    a0 = s2;
    if (v0 != 0) {
        // 0x0058cb88
        charge(ctx, 4);
        a1 = lui(0xFF00);
        a1 = a1 | 0xD06;
        jal(ctx, 0x58CB8Cu, gen::fn_sub_58BE40_0058be40);
        s6 = v0;
    }
    // 0x0058cb98
    charge(ctx, 6);
    lw(s0, sp, 0x24);
    lw(a3, sp, 0x10);
    lw(v1, sp, 0x14);
    lw(a1, sp, 0x18);
    ld(t0, sp, 0x0);
    if (i64(s0) >= 0) {
        // 0x0058cbc8
        charge(ctx, 2);
        if (s0 != 0) {
            v0 = slt(s5, s0);
            // 0x0058cbe8
            charge(ctx, 2);
            if (v0 == 0) {
                v0 = sll(a3, 2);
                // 0x0058cc08
                charge(ctx, 4);
                v0 = addu(v0, s1);
                lw(a0, v0, -688);
                if (a0 == 0) {
                    v1 = sll(v1, 2);
                    // 0x0058cc38
                    charge(ctx, 8);
                    a0 = s2;
                    v0 = 0x7D0000;
                    v0 = addu(v0, v1);
                    lw(v0, v0, -24544);
                    a2 = s7;
                    a3 = s0;
                    jalr(ctx, 0x58CC4Cu, v0.u());
                    sw(v0, s3, 0);
                } else {
                    // 0x0058cc18
                    charge(ctx, 7);
                    lw(a2, s1, 340);
                    t0 = s7;
                    lw(a1, s1, 336);
                    t1 = s0;
                    jal(ctx, 0x58CC24u, gen::fn_sub_58CCA0_0058cca0);
                    sw(v0, s3, 0);
                }
                // 0x0058cc58
                charge(ctx, 3);
                lw(t0, s3, 0);
                v0 = 1;
                if (t0 != 0) {
                    // 0x0058cc64
                    charge(ctx, 2);
                    if (t0 != v0) {
                        s6 = t0;
                    } else {
                        // 0x0058cc6c
                        charge(ctx, 1);
                        sw(s0, s4, 0);
                    }
                }
                // 0x0058cc70
                charge(ctx, 1);
                v0 = s6;
            } else {
                // 0x0058cbf0
                charge(ctx, 5);
                a0 = s2;
                a1 = 0;
                jal(ctx, 0x58CBF4u, gen::fn_sub_58D798_0058d798);
                v0 = 0;
            }
        } else {
            // 0x0058cbd0
            charge(ctx, 5);
            v0 = 1;
            sw(zero, s4, 0);
            sw(v0, s3, 0);
            v0 = 0;
        }
        // 0x0058cc74
        charge(ctx, 1);
        ld(s0, sp, 0x30);
    } else {
        // 0x0058cbb0
        charge(ctx, 6);
        a1 = lui(0xFF00);
        a0 = s2;
        a1 = a1 | 0xD0E;
        jal(ctx, 0x58CBB8u, gen::fn_sub_58BE40_0058be40);
        ld(s0, sp, 0x30);
    }
    // 0x0058cc78 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s1, sp, 0x38);
    ld(s2, sp, 0x40);
    ld(s3, sp, 0x48);
    ld(s4, sp, 0x50);
    ld(s5, sp, 0x58);
    ld(s6, sp, 0x60);
    ld(s7, sp, 0x68);
    ld(ra, sp, 0x70);
    sp = addiu(sp, 0x80);
}

// 0x0058CD10 sub_58CD10 -- 368 bytes; frame 0x50: s1 sp+0x8, s3 sp+0x18, s5 sp+0x28, s7 sp+0x38, fp sp+0x40, s0 sp+0x0, s2 sp+0x10, s4 sp+0x20, s6 sp+0x30, ra sp+0x48
// Data-referenced audio packet handler: needs parameter 6; keeps the first time stamps, the parameters 30 / 55 and the
// chunk write (sub_58D378).
void sub_58CD10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    // 0x0058cd10
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s1, sp, 0x8);
    s1 = a1;
    a1 = 6;
    sd(s3, sp, 0x18);
    sd(s5, sp, 0x28);
    s5 = a0;
    sd(s7, sp, 0x38);
    s7 = a2;
    sd(fp, sp, 0x40);
    fp = a3;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(s4, sp, 0x20);
    sd(s6, sp, 0x30);
    sd(ra, sp, 0x48);
    s3 = t0;
    jal(ctx, 0x58CD50u, gen::fn_sub_599408_00599408);
    s6 = addiu(s5, trn::kDemux);
    if (v0 == 0) {
        // 0x0058cd60
        charge(ctx, 2);
        v0 = 1;
        // 0x0058ce50 (the shared epilogue, written out on this path)
        charge(ctx, 12);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(s6, sp, 0x30);
        ld(s7, sp, 0x38);
        ld(fp, sp, 0x40);
        ld(ra, sp, 0x48);
        sp = addiu(sp, 0x50);
        return;
    }
    // 0x0058cd68
    charge(ctx, 5);
    s2 = si(-1);
    lw(s0, s6, 8);
    lw(v0, s0, 56);
    if (v0 == s2) {
        sw(s1, s0, 56);
    }
    // 0x0058cd7c
    charge(ctx, 3);
    lw(v0, s0, 48);
    if (v0 == s2) {
        sw(s1, s0, 48);
    }
    // 0x0058cd88
    charge(ctx, 6);
    a0 = s5;
    a1 = 30;
    jal(ctx, 0x58CD8Cu, gen::fn_sub_599408_00599408);
    s4 = v0;
    a0 = s5;
    if (s4 != s2) {
        // 0x0058cda0
        charge(ctx, 4);
        a1 = 55;
        jal(ctx, 0x58CDA0u, gen::fn_sub_599408_00599408);
        if (v0 == 0) {
            lw(v0, s0, 48);
            // 0x0058cdc8
            charge(ctx, 2);
            if (s1 == v0) {
                // 0x0058cdd0
                charge(ctx, 1);
                sw(s4, s0, 56);
                goto L_0058cdd4;
            }
            lw(v1, s0, 56);
        } else {
            // 0x0058cdb0
            charge(ctx, 4);
            lw(v0, s0, 40);
            v0 = slt(s1, v0);
            if (v0 != 0) {
                sw(s4, s0, 56);
                goto L_0058cdd4;
            }
            // 0x0058cdc0
            charge(ctx, 2);
            lw(v1, s0, 56);
        }
        goto L_0058cdd8;
    }
L_0058cdd4:
    charge(ctx, 1);
    lw(v1, s0, 56);
L_0058cdd8:
    charge(ctx, 3);
    v0 = 1;
    sw(s1, s0, 40);
    if (v1 != s1) {
        // 0x0058ce50 (the shared epilogue, written out on this path)
        charge(ctx, 12);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(s4, sp, 0x20);
        ld(s5, sp, 0x28);
        ld(s6, sp, 0x30);
        ld(s7, sp, 0x38);
        ld(fp, sp, 0x40);
        ld(ra, sp, 0x48);
        sp = addiu(sp, 0x50);
        return;
    }
    // 0x0058cde4
    charge(ctx, 2);
    if (i64(s3) < 0) {
        lw(a1, s6, 24);
    } else {
        // 0x0058cdec
        charge(ctx, 9);
        ld(v0, s0, 16);
        ld(v1, s0, 24);
        a0 = slt(s3, v0);
        a1 = slt(s3, v1);
        if (a0 != 0) v0 = s3;
        if (a1 != 0) v1 = s3;
        sd(v0, s0, 16);
        sd(v1, s0, 24);
        lw(a1, s6, 24);
    }
    // 0x0058ce10
    charge(ctx, 16);
    a0 = s5;
    a2 = s7;
    ld(s7, sp, 0x38);
    a3 = fp;
    ld(fp, sp, 0x40);
    t0 = s3;
    ld(s3, sp, 0x18);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
    gen::fn_sub_58D378_0058d378(ctx);  // tail call
}

// 0x0058CE80 sub_58CE80 -- 472 bytes; frame 0x50: s6 sp+0x30, s1 sp+0x8, s3 sp+0x18, s4 sp+0x20, fp sp+0x40, s0 sp+0x0, s2 sp+0x10, s5 sp+0x28, s7 sp+0x38, ra sp+0x48
// Data-referenced video packet handler: needs parameter 5; keeps the first time stamps (sub_58D058), the parameters 29
// / ... and the chunk write (sub_58D378).
void sub_58CE80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0058ce80
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s6, sp, 0x30);
    s6 = a1;
    a1 = 5;
    sd(s1, sp, 0x8);
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s4, sp, 0x20);
    s4 = a2;
    sd(fp, sp, 0x40);
    fp = t0;
    sd(s0, sp, 0x0);
    sd(s2, sp, 0x10);
    sd(s5, sp, 0x28);
    sd(s7, sp, 0x38);
    sd(ra, sp, 0x48);
    s1 = a0;
    jal(ctx, 0x58CEC0u, gen::fn_sub_599408_00599408);
    s7 = addiu(s1, trn::kDemux);
    if (v0 != 0) {
        // 0x0058ced8
        charge(ctx, 5);
        s5 = si(-1);
        lw(s0, s7, 8);
        lw(v0, s0, 52);
        if (v0 != s5) {
            lw(v0, s0, 44);
        } else {
            // 0x0058ceec
            charge(ctx, 5);
            a0 = s1;
            a1 = s6;
            jal(ctx, 0x58CEF0u, gen::fn_sub_58D058_0058d058);
            sw(v0, s0, 52);
            lw(v0, s0, 44);
        }
        // 0x0058cf00
        charge(ctx, 2);
        if (v0 == s5) {
            sw(s6, s0, 44);
        }
        // 0x0058cf08
        charge(ctx, 6);
        a0 = s1;
        a1 = 29;
        jal(ctx, 0x58CF0Cu, gen::fn_sub_599408_00599408);
        s2 = v0;
        a0 = s1;
        if (s2 == s5) {
            // 0x0058cfb0
            charge(ctx, 1);
            lw(a0, s0, 52);
        L_0058cfb4:
            charge(ctx, 1);
            sw(s6, s0, 36);
        } else {
            // 0x0058cf20
            charge(ctx, 4);
            a1 = 55;
            jal(ctx, 0x58CF20u, gen::fn_sub_599408_00599408);
            if (v0 == 0) {
                lw(v0, s0, 44);
                // 0x0058cf48
                charge(ctx, 2);
                lw(a0, s0, 52);
                if (s6 != v0) {
                    goto L_0058cfb4;
                }
            L_0058cf50:
                charge(ctx, 2);
                v0 = slti(s3, 4);
                if (a0 == s2) {
                    goto L_0058cfb4;
                }
                // 0x0058cf58
                charge(ctx, 2);
                if (v0 != 0) {
                    sw(s6, s0, 36);
                } else {
                    // 0x0058cf60
                    charge(ctx, 3);
                    lb(v0, s4, 0);
                    if (v0 != 0) {
                        sw(s6, s0, 36);
                    } else {
                        // 0x0058cf6c
                        charge(ctx, 3);
                        lb(v0, s4, 1);
                        if (v0 != 0) {
                            sw(s6, s0, 36);
                        } else {
                            // 0x0058cf78
                            charge(ctx, 4);
                            lbu(v1, s4, 2);
                            v0 = 1;
                            if (v1 == v0) {
                                // 0x0058cf88
                                charge(ctx, 4);
                                lbu(v1, s4, 3);
                                v0 = 179;
                                cc = v1 == v0;  // the condition, before the delay slot changes it
                                v0 = 184;
                                if (!cc) {
                                    // 0x0058cf98
                                    charge(ctx, 2);
                                    if (v1 == v0) {
                                        goto L_0058cfa0;
                                    }
                                    sw(s6, s0, 36);
                                    goto L_0058cfb8;
                                }
                            L_0058cfa0:
                                charge(ctx, 3);
                                sw(s2, s0, 52);
                                a0 = s2;
                                goto L_0058cfb4;
                            }
                            sw(s6, s0, 36);
                        }
                    }
                }
            } else {
                // 0x0058cf30
                charge(ctx, 4);
                lw(v0, s0, 36);
                v0 = slt(s6, v0);
                lw(a0, s0, 52);
                if (v0 != 0) {
                    goto L_0058cf50;
                }
                // 0x0058cf40
                charge(ctx, 2);
                sw(s6, s0, 36);
            }
        }
    L_0058cfb8:
        charge(ctx, 2);
        v0 = 1;
        if (a0 == s6) {
            // 0x0058cfc0
            charge(ctx, 7);
            a2 = s3;
            a0 = s1;
            a1 = s4;
            jal(ctx, 0x58CFC8u, gen::fn_sub_595138_00595138);
            s3 = v0;
            v0 = 0;
            if (i64(s3) > 0) {
                // 0x0058cfdc
                charge(ctx, 10);
                lw(a1, s7, 20);
                t0 = fp;
                a0 = s1;
                a2 = s4;
                a3 = s3;
                jal(ctx, 0x58CFECu, gen::fn_sub_58D378_0058d378);
                s0 = v0;
                v0 = 1;
                a0 = s1;
                if (s0 == v0) {
                    // 0x0058d018
                    charge(ctx, 4);
                    a1 = s4;
                    a2 = s3;
                    jal(ctx, 0x58D01Cu, gen::fn_sub_5954E8_005954e8);
                    v0 = s0;
                } else {
                    // 0x0058d004
                    charge(ctx, 4);
                    a1 = s3;
                    jal(ctx, 0x58D004u, gen::fn_sub_5951A8_005951a8);
                    v0 = s0;
                }
            }
        }
    } else {
        // 0x0058ced0
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x0058d028 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(s5, sp, 0x28);
    ld(s6, sp, 0x30);
    ld(s7, sp, 0x38);
    ld(fp, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
}

// 0x0058D058 sub_58D058 -- 132 bytes; frame 0x30: s1 sp+0x18, s0 sp+0x10, s2 sp+0x20, ra sp+0x28
// Video time base by parameter 59: mode 2 uses the stream's picture counts (sub_58DB08); other modes keep $a1.
void sub_58D058(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058d058
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x18);
    s1 = a1;
    a1 = 59;
    sd(s0, sp, 0x10);
    sd(s2, sp, 0x20);
    sd(ra, sp, 0x28);
    s2 = a0;
    jal(ctx, 0x58D074u, gen::fn_sub_599408_00599408);
    s0 = v0;
    v0 = s1;
    v1 = 1;
    a0 = slti(s0, 2);
    if (s0 != v1) {
        // 0x0058d090
        charge(ctx, 2);
        if (a0 == 0) {
            // 0x0058d098
            charge(ctx, 3);
            v0 = 2;
            if (s0 != v0) {
                v0 = s1;
            } else {
                // 0x0058d0a4
                charge(ctx, 8);
                a0 = s2;
                a1 = sp;
                a2 = addiu(sp, 0x4);
                jal(ctx, 0x58D0ACu, gen::fn_sub_58DB08_0058db08);
                v0 = s0;
                lw(v1, sp, 0x4);
                v1 = slti(v1, 2);
                if (v1 != 0) v0 = s1;
            }
            goto L_0058d0c4;
        }
        ld(s0, sp, 0x10);
        // 0x0058d0c8 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x18);
        ld(s2, sp, 0x20);
        ld(ra, sp, 0x28);
        sp = addiu(sp, 0x30);
        return;
    }
L_0058d0c4:
    charge(ctx, 1);
    ld(s0, sp, 0x10);
    // 0x0058d0c8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0058D0E0 sub_58D0E0 -- 156 bytes; frame 0x40: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, ra sp+0x30
// Data-referenced private-stream handler: a private packet (sub_58B168) is consumed (sub_58E158) with the rest written
// after its 18-byte header; other data goes to sub_58D180.
void sub_58D0E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058d0e0
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    t0 = sp;
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s2, sp, 0x20);
    s2 = a2;
    sd(s3, sp, 0x28);
    s3 = a3;
    sd(ra, sp, 0x30);
    s0 = a1;
    jal(ctx, 0x58D108u, gen::fn_sub_58B168_0058b168);
    a0 = s1;
    a1 = s0;
    a2 = s2;
    a3 = s3;
    if (v0 == 0) {
        // 0x0058d158
        charge(ctx, 2);
        a0 = s1;
        jal(ctx, 0x58D158u, gen::fn_sub_58D180_0058d180);
    } else {
        // 0x0058d124
        charge(ctx, 8);
        jal(ctx, 0x58D124u, gen::fn_sub_58E158_0058e158);
        a2 = addiu(s2, -18);
        lw(v0, sp, 0x0);
        a1 = 0;
        a0 = s1;
        a3 = addiu(s3, 18);
        if (v0 != 0) {
            // 0x0058d144
            charge(ctx, 2);
            jal(ctx, 0x58D144u, gen::fn_sub_58D180_0058d180);
        }
        // 0x0058d14c
        charge(ctx, 2);
        v0 = 1;
    }
    // 0x0058d160 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0058D180 sub_58D180 -- 216 bytes; frame 0x50: s0 sp+0x10, s1 sp+0x18, s3 sp+0x28, s5 sp+0x38, s2 sp+0x20, s4 sp+0x30, ra sp+0x40
// Writes packet data to the output stream +8080 (unless it is 8): its descriptor (sub_588F90), the SJ write
// (sub_58D258), then the vtable put calls.
void sub_58D180(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058d180
    enter(ctx, 19);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    t0 = 8;
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(s1, sp, 0x18);
    s1 = a3;
    sd(s3, sp, 0x28);
    s3 = a2;
    sd(s5, sp, 0x38);
    s5 = a0;
    sd(s2, sp, 0x20);
    a2 = s0;
    sd(s4, sp, 0x30);
    a3 = sp;
    sd(ra, sp, 0x40);
    v0 = 1;
    lw(v1, s5, trn::kDemuxOut2);
    a1 = v1;
    if (v1 != t0) {
        // 0x0058d1cc
        charge(ctx, 11);
        jal(ctx, 0x58D1CCu, gen::fn_sub_588F90_00588f90);
        a1 = s3;
        lw(v1, sp, 0x0);
        a2 = s1;
        lw(s2, sp, 0x4);
        v0 = 1;
        a0 = v1;
        lw(s3, sp, 0x8);
        lw(s4, sp, 0xC);
        if (v1 != 0) {
            // 0x0058d1f8
            charge(ctx, 6);
            jal(ctx, 0x58D1F8u, gen::fn_sub_58D258_0058d258);
            s1 = v0;
            v0 = 1;
            if (s1 != v0) {
                v0 = s1;
            } else {
                // 0x0058d210
                charge(ctx, 2);
                a0 = s5;
                if (s2 != 0) {
                    // 0x0058d218
                    charge(ctx, 2);
                    a1 = s0;
                    jalr(ctx, 0x58D218u, s2.u());
                }
                // 0x0058d220
                charge(ctx, 2);
                a0 = s4;
                if (s3 != 0) {
                    // 0x0058d228
                    charge(ctx, 2);
                    a1 = s0;
                    jalr(ctx, 0x58D228u, s3.u());
                }
                // 0x0058d230
                charge(ctx, 1);
                v0 = s1;
            }
        }
    }
    // 0x0058d234 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x0058D258 sub_58D258 -- 168 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Writes n bytes into an SJ when it has room (vtable +36): sub_58D300 for the first part and the wrap; a short second
// write counts in 0x7B4798; 1 when written.
void sub_58D258(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058d258
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(ra, sp, 0x18);
    lw(v1, s2, 0);
    lw(v0, v1, 36);
    a1 = 0;
    jalr(ctx, 0x58D280u, v0.u());
    a0 = s2;
    v1 = slt(v0, s0);
    v0 = 0;
    a1 = s1;
    a2 = s0;
    if (v1 == 0) {
        // 0x0058d2a0
        charge(ctx, 5);
        jal(ctx, 0x58D2A0u, gen::fn_sub_58D300_0058d300);
        v1 = v0;
        s0 = subu(s0, v1);
        if (v1 != 0) {
            // 0x0058d2b4
            charge(ctx, 2);
            s1 = addu(s1, v1);
            if (i64(s0) > 0) {
                // 0x0058d2bc
                charge(ctx, 7);
                a0 = s2;
                a1 = s1;
                a2 = s0;
                jal(ctx, 0x58D2C4u, gen::fn_sub_58D300_0058d300);
                v1 = 0x7B0000;
                v1 = addiu(v1, 18328);  // &0x7B4798
                if (v0 != s0) {
                    // 0x0058d2d8
                    charge(ctx, 3);
                    lw(v0, v1, 0);
                    v0 = addiu(v0, 1);
                    sw(v0, v1, 0);
                }
            }
            // 0x0058d2e4
            charge(ctx, 1);
            v0 = 1;
        }
    }
    // 0x0058d2e8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0058D370 sub_58D370 -- 8 bytes; leaf frame (no stack)
// Returns nothing (data-referenced no-op handler).
void sub_58D370(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0058d370
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 1;
}

// 0x0058D378 sub_58D378 -- 400 bytes; frame 0xA0: s5 sp+0x78, s0 sp+0x50, s2 sp+0x60, s4 sp+0x70, s6 sp+0x80, s1 sp+0x58, s3 sp+0x68, s7 sp+0x88, fp sp+0x90, ra sp+0x98
// Writes a packet into a stream chunk (sub_589000) by mode: 1 / 2 with the time stamp checks, copies through memcpy
// (sub_575410) and the release (sub_5890D8).
void sub_58D378(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0058d378
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0xA0);
    sd(s5, sp, 0x78);
    s5 = a2;
    a2 = sp;
    sd(s0, sp, 0x50);
    sd(s2, sp, 0x60);
    s2 = t0;
    sd(s4, sp, 0x70);
    s4 = a0;
    sd(s6, sp, 0x80);
    s6 = a1;
    sd(s1, sp, 0x58);
    sd(s3, sp, 0x68);
    sd(s7, sp, 0x88);
    sd(fp, sp, 0x90);
    sd(ra, sp, 0x98);
    s0 = a3;
    jal(ctx, 0x58D3B8u, gen::fn_sub_589000_00589000);
    if (v0 != 0) {
        ld(s0, sp, 0x50);
    } else {
        // 0x0058d3c8
        charge(ctx, 8);
        lw(s1, sp, 0x4);
        lw(v1, sp, 0xC);
        lw(s3, sp, 0x0);
        v1 = addu(s1, v1);
        lw(s7, sp, 0x8);
        v1 = slt(v1, s0);
        lw(fp, sp, 0x14);
        if (v1 == 0) {
            // 0x0058d3e8
            charge(ctx, 3);
            v0 = 1;
            if (s6 != v0) {
                v0 = 2;
                // 0x0058d440
                charge(ctx, 2);
                cc = s6 != v0;  // the condition, before the delay slot changes it
                v0 = slt(s1, s0);
                if (cc) {
                L_0058d484:
                    charge(ctx, 2);
                    a0 = s3;
                    if (v0 != 0) {
                        // 0x0058d4a0
                        charge(ctx, 8);
                        a1 = s5;
                        a2 = s1;
                        jal(ctx, 0x58D4A4u, gen::fn_sub_575410_00575410);
                        a0 = s7;
                        a1 = addu(s5, s1);
                        a2 = subu(s0, s1);
                        jal(ctx, 0x58D4B4u, gen::fn_sub_575410_00575410);
                        a0 = s4;
                    } else {
                        // 0x0058d48c
                        charge(ctx, 5);
                        a1 = s5;
                        a2 = s0;
                        jal(ctx, 0x58D490u, gen::fn_sub_575410_00575410);
                        a0 = s4;
                    }
                    // 0x0058d4c0
                    charge(ctx, 6);
                    a1 = s6;
                    a2 = s0;
                    a3 = fp;
                    jal(ctx, 0x58D4C8u, gen::fn_sub_5890D8_005890d8);
                    v1 = 1;
                    if (v0 == 0) v0 = v1;
                } else {
                    // 0x0058d448
                    charge(ctx, 4);
                    v0 = 0x7B0000;
                    lw(v0, v0, 18356);  // 0x7B47B4
                    a0 = addiu(s4, 4832);
                    if (v0 == 0) {
                    L_0058d480:
                        charge(ctx, 1);
                        v0 = slt(s1, s0);
                        goto L_0058d484;
                    }
                    // 0x0058d458
                    charge(ctx, 7);
                    sd(s2, sp, 0x30);
                    sw(s0, sp, 0x38);
                    a1 = addiu(sp, 0x30);
                    jalr(ctx, 0x58D460u, v0.u());
                    v1 = si(-1);
                    if (v0 != v1) {
                        v0 = slt(s1, s0);
                        goto L_0058d484;
                    }
                    // 0x0058d474
                    charge(ctx, 2);
                    v0 = 0;
                }
                goto L_0058d4d8;
            }
            // 0x0058d3f4
            charge(ctx, 2);
            a0 = s4;
            if (i64(s2) < 0) {
                goto L_0058d480;
            }
            // 0x0058d3fc
            charge(ctx, 4);
            a1 = 1;
            jal(ctx, 0x58D3FCu, gen::fn_sub_5982A0_005982a0);
            if (v0 != 0) {
                v0 = 0;
                goto L_0058d4d8;
            }
            // 0x0058d40c
            charge(ctx, 10);
            a0 = s4;
            a1 = 1;
            a2 = addiu(sp, 0x20);
            a3 = addiu(sp, 0x40);
            sd(s2, sp, 0x20);
            sw(s3, sp, 0x28);
            link(ctx, 0x58D424u);  // $ra first: the delay slot below depends on it
            sw(s0, sp, 0x2C);
            call(ctx, gen::fn_sub_597FA0_00597fa0);
            if (v0 == 0) {
                v0 = slt(s1, s0);
                goto L_0058d484;
            }
            // 0x0058d434
            charge(ctx, 2);
            ld(s0, sp, 0x50);
            // 0x0058d4dc (the shared epilogue, written out on this path)
            charge(ctx, 11);
            ld(s1, sp, 0x58);
            ld(s2, sp, 0x60);
            ld(s3, sp, 0x68);
            ld(s4, sp, 0x70);
            ld(s5, sp, 0x78);
            ld(s6, sp, 0x80);
            ld(s7, sp, 0x88);
            ld(fp, sp, 0x90);
            ld(ra, sp, 0x98);
            sp = addiu(sp, 0xA0);
            return;
        }
    L_0058d4d8:
        charge(ctx, 1);
        ld(s0, sp, 0x50);
    }
    // 0x0058d4dc (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(s1, sp, 0x58);
    ld(s2, sp, 0x60);
    ld(s3, sp, 0x68);
    ld(s4, sp, 0x70);
    ld(s5, sp, 0x78);
    ld(s6, sp, 0x80);
    ld(s7, sp, 0x88);
    ld(fp, sp, 0x90);
    ld(ra, sp, 0x98);
    sp = addiu(sp, 0xA0);
}

// 0x0058D508 sub_58D508 -- 108 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Marks the three output streams (+8076, +8072, +8080) ended (sub_589CF0 1) and calls sub_595208.
void sub_58D508(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058d508
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 1;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = addiu(s0, trn::kDemux);
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(ra, sp, 0x18);
    link(ctx, 0x58D52Cu);  // $ra first: the delay slot below depends on it
    lw(a1, s1, 24);
    call(ctx, gen::fn_sub_589CF0_00589cf0);
    a0 = s0;
    lw(a1, s1, 20);
    a2 = 1;
    jal(ctx, 0x58D53Cu, gen::fn_sub_589CF0_00589cf0);
    a0 = s0;
    lw(a1, s1, 28);
    a2 = 1;
    jal(ctx, 0x58D54Cu, gen::fn_sub_589CF0_00589cf0);
    a0 = s0;
    a1 = s2;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_595208_00595208(ctx);  // tail call
}

// 0x0058D578 sub_58D578 -- 108 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// 1 when all three output streams have ended (sub_589D10 ANDed).
void sub_58D578(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058d578
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = addiu(s0, trn::kDemux);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    link(ctx, 0x58D598u);  // $ra first: the delay slot below depends on it
    lw(a1, s1, 24);
    call(ctx, gen::fn_sub_589D10_00589d10);
    a0 = s0;
    lw(a1, s1, 20);
    s2 = v0;
    jal(ctx, 0x58D5A8u, gen::fn_sub_589D10_00589d10);
    a0 = s0;
    lw(a1, s1, 28);
    s3 = v0;
    s2 = s2 & s3;
    jal(ctx, 0x58D5BCu, gen::fn_sub_589D10_00589d10);
    v0 = s2 & v0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0058D600 sub_58D600 -- 324 bytes; frame 0x50: s0 sp+0x10, s2 sp+0x20, s5 sp+0x38, s6 sp+0x40, s1 sp+0x18, s3 sp+0x28, s4 sp+0x30, ra sp+0x48
// Pack / end code handling of the demux: the code (sub_5776B0); 0x1BA keeps the input position (sub_589530); the end
// code ends the outputs (sub_58D508 / sub_58D798) when allowed (sub_58D748).
void sub_58D600(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058d600
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x10);
    sd(s2, sp, 0x20);
    s2 = a0;
    sd(s5, sp, 0x38);
    s5 = a2;
    sd(s6, sp, 0x40);
    s6 = a3;
    sd(s1, sp, 0x18);
    s0 = addiu(s2, trn::kDemux);
    sd(s3, sp, 0x28);
    v0 = slti(s5, 4);
    sd(s4, sp, 0x30);
    a0 = a1;
    sd(ra, sp, 0x48);
    lw(s4, s0, 8);
    lw(s3, s0, 16);
    if (v0 != 0) {
        // 0x0058d6a0
        charge(ctx, 1);
        s1 = 0;
    L_0058d6a4:
        charge(ctx, 1);
        a0 = s2;
    } else {
        // 0x0058d648
        charge(ctx, 6);
        jal(ctx, 0x58D648u, gen::fn_sub_5776B0_005776b0);
        s1 = v0;
        v0 = 0x80000;
        if (s1 == v0) {
            // 0x0058d660
            charge(ctx, 3);
            lw(v0, s0, 32);
            if (i64(v0) >= 0) {
                v0 = 1;
            } else {
                // 0x0058d66c
                charge(ctx, 6);
                a1 = s3;
                a0 = s2;
                jal(ctx, 0x58D670u, gen::fn_sub_589530_00589530);
                v0 = addiu(v0, 4);
                sw(v0, s0, 32);
                v0 = 1;
            }
            // 0x0058d684
            charge(ctx, 2);
            sw(v0, s4, 60);
            goto L_0058d6a4;
        }
        // 0x0058d690
        charge(ctx, 2);
        if (s1 != 0) {
            sw(zero, s4, 60);
            goto L_0058d6a4;
        }
        // 0x0058d698
        charge(ctx, 2);
        a0 = s2;
    }
    // 0x0058d6a8
    charge(ctx, 4);
    a1 = s1;
    jal(ctx, 0x58D6A8u, gen::fn_sub_58D748_0058d748);
    a0 = s2;
    if (v0 == 0) {
        // 0x0058d6c8
        charge(ctx, 3);
        v0 = slti(s6, 4);
        v1 = slti(s5, 64);
        if (v0 != 0) {
            // 0x0058d6d4
            charge(ctx, 6);
            a0 = s2;
            a1 = sp;
            jal(ctx, 0x58D6D8u, gen::fn_sub_58D798_0058d798);
            lw(v1, sp, 0x0);
            v0 = 0;
            if (v1 == 0) {
                // 0x0058d6ec
                charge(ctx, 1);
                v1 = slti(s5, 64);
                goto L_0058d6f0;
            }
            // 0x0058d71c (the shared epilogue, written out on this path)
            charge(ctx, 10);
            ld(s0, sp, 0x10);
            ld(s1, sp, 0x18);
            ld(s2, sp, 0x20);
            ld(s3, sp, 0x28);
            ld(s4, sp, 0x30);
            ld(s5, sp, 0x38);
            ld(s6, sp, 0x40);
            ld(ra, sp, 0x48);
            sp = addiu(sp, 0x50);
            return;
        }
    L_0058d6f0:
        charge(ctx, 2);
        v0 = 1;
        if (v1 != 0) {
            // 0x0058d6f8
            charge(ctx, 3);
            v0 = 0x10000;
            v1 = 0x40000;
            if (s1 != v0) {
                // 0x0058d704
                charge(ctx, 2);
                v0 = 1;
                if (s1 == v1) {
                    goto L_0058d70c;
                }
                // 0x0058d71c (the shared epilogue, written out on this path)
                charge(ctx, 10);
                ld(s0, sp, 0x10);
                ld(s1, sp, 0x18);
                ld(s2, sp, 0x20);
                ld(s3, sp, 0x28);
                ld(s4, sp, 0x30);
                ld(s5, sp, 0x38);
                ld(s6, sp, 0x40);
                ld(ra, sp, 0x48);
                sp = addiu(sp, 0x50);
                return;
            }
        L_0058d70c:
            charge(ctx, 4);
            a0 = s2;
            a1 = 0;
            jal(ctx, 0x58D710u, gen::fn_sub_58D798_0058d798);
            v0 = 0;
        }
    } else {
        // 0x0058d6b8
        charge(ctx, 4);
        a1 = 1;
        jal(ctx, 0x58D6B8u, gen::fn_sub_58D508_0058d508);
        v0 = 0;
    }
    // 0x0058d71c (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(s6, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
}

// 0x0058D748 sub_58D748 -- 80 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// 1 when the code is the end code (0x80000) and neither parameter 49 (sub_589FD0) nor 49 / 56 (sub_589FF0) is set.
void sub_58D748(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058d748
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x80000;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    v0 = 0;
    if (a1 == v1) {
        // 0x0058d764
        charge(ctx, 4);
        jal(ctx, 0x58D764u, gen::fn_sub_589FD0_00589fd0);
        a0 = s0;
        if (v0 == 0) {
            // 0x0058d774
            charge(ctx, 4);
            jal(ctx, 0x58D774u, gen::fn_sub_589FF0_00589ff0);
            if (v0 != 0) {
                goto L_0058d784;
            }
            v0 = 1;
            // 0x0058d788 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(s0, sp, 0x0);
            ld(ra, sp, 0x8);
            sp = addiu(sp, 0x10);
            return;
        }
    L_0058d784:
        charge(ctx, 1);
        v0 = 0;
    }
    // 0x0058d788 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0058D798 sub_58D798 -- 104 bytes; frame 0x20: s0 sp+0x0, s2 sp+0x10, s1 sp+0x8, ra sp+0x18
// When the input stream ended (sub_589D10), ends the outputs (sub_58D508 with the demux's word +60) and reports 1
// through the optional output.
void sub_58D798(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058d798
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(s1, sp, 0x8);
    v0 = addiu(s0, trn::kDemux);
    sd(ra, sp, 0x18);
    lw(a1, v0, 16);
    link(ctx, 0x58D7BCu);  // $ra first: the delay slot below depends on it
    lw(s1, v0, 8);
    call(ctx, gen::fn_sub_589D10_00589d10);
    a1 = 0;
    v1 = 1;
    a0 = s0;
    if (v0 == v1) {
        // 0x0058d7d4
        charge(ctx, 3);
        link(ctx, 0x58D7D4u);  // $ra first: the delay slot below depends on it
        lw(a1, s1, 60);
        call(ctx, gen::fn_sub_58D508_0058d508);
        a1 = 1;
    }
    // 0x0058d7e0
    charge(ctx, 2);
    if (s2 != 0) {
        sw(a1, s2, 0);
    }
    // 0x0058d7e8
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0058D800 sub_58D800 -- 84 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// The status-2 steps of the demux: picture counts (sub_58DB08), the start check (sub_58D858), the header (sub_58DBB8),
// the end check (sub_58DA10), the time (sub_58DC50) and sub_58DD00.
void sub_58D800(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058d800
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x10);
    s0 = a0;
    a1 = sp;
    sd(ra, sp, 0x18);
    a2 = addiu(sp, 0x4);
    jal(ctx, 0x58D814u, gen::fn_sub_58DB08_0058db08);
    a0 = s0;
    jal(ctx, 0x58D81Cu, gen::fn_sub_58D858_0058d858);
    a0 = s0;
    jal(ctx, 0x58D824u, gen::fn_sub_58DBB8_0058dbb8);
    a0 = s0;
    jal(ctx, 0x58D82Cu, gen::fn_sub_58DA10_0058da10);
    a0 = s0;
    jal(ctx, 0x58D834u, gen::fn_sub_58DC50_0058dc50);
    a0 = s0;
    jal(ctx, 0x58D83Cu, gen::fn_sub_58DD00_0058dd00);
    ld(s0, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0058D858 sub_58D858 -- 136 bytes; frame 0x20: s1 sp+0x8, s2 sp+0x10, s0 sp+0x0, ra sp+0x18
// Unless an output already reports input end (sub_58D8E0), when the input stream has its end flag and enough data is
// buffered (sub_58D9B0), marks the outputs (sub_58D950 1).
void sub_58D858(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058d858
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x18);
    s2 = 1;
    jal(ctx, 0x58D870u, gen::fn_sub_58D8E0_0058d8e0);
    a0 = s1;
    if (v0 == s2) {
        // 0x0058d8c8 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0058d880
    charge(ctx, 6);
    lw(s0, s1, trn::kDemuxIn);
    a1 = s0;
    jal(ctx, 0x58D884u, gen::fn_sub_589CD0_00589cd0);
    a0 = s1;
    a1 = s0;
    if (v0 != s2) {
        // 0x0058d8c8 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0058d898
    charge(ctx, 4);
    jal(ctx, 0x58D898u, gen::fn_sub_58D9B0_0058d9b0);
    a0 = s1;
    if (v0 == 0) {
        // 0x0058d8c8 (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0058d8a8
    charge(ctx, 7);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    a1 = 1;
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_58D950_0058d950(ctx);  // tail call
}

// 0x0058D8E0 sub_58D8E0 -- 108 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// 1 when any of the three output streams has its input end flag (sub_589CD0 ORed).
void sub_58D8E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058d8e0
    enter(ctx, 27);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = addiu(s0, trn::kDemux);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    link(ctx, 0x58D900u);  // $ra first: the delay slot below depends on it
    lw(a1, s1, 24);
    call(ctx, gen::fn_sub_589CD0_00589cd0);
    a0 = s0;
    lw(a1, s1, 20);
    s2 = v0;
    jal(ctx, 0x58D910u, gen::fn_sub_589CD0_00589cd0);
    a0 = s0;
    lw(a1, s1, 28);
    s3 = v0;
    s2 = s2 | s3;
    jal(ctx, 0x58D924u, gen::fn_sub_589CD0_00589cd0);
    v0 = s2 | v0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0058D950 sub_58D950 -- 96 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Sets the input end flag of the three output streams to $a1 (sub_589CB0).
void sub_58D950(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058d950
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = addiu(s0, trn::kDemux);
    sd(s2, sp, 0x10);
    s2 = a1;
    sd(ra, sp, 0x18);
    a2 = s2;
    link(ctx, 0x58D974u);  // $ra first: the delay slot below depends on it
    lw(a1, s1, 24);
    call(ctx, gen::fn_sub_589CB0_00589cb0);
    a0 = s0;
    lw(a1, s1, 20);
    a2 = s2;
    jal(ctx, 0x58D984u, gen::fn_sub_589CB0_00589cb0);
    a0 = s0;
    lw(a1, s1, 28);
    a2 = s2;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_589CB0_00589cb0(ctx);  // tail call
}

// 0x0058D9B0 sub_58D9B0 -- 96 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Enough buffered: the target (+8, else the stream's +12, else the parameter +2660) capped by +2660, against stream
// 0's available amount (sub_589550).
void sub_58D9B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058d9b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x58D9BCu, gen::fn_sub_58CB00_0058cb00);
    lw(a2, s0, 8);
    a0 = s0;
    s0 = addiu(s0, 2572);
    a1 = 0;
    lw(a3, s0, 88);
    if (i64(a2) <= 0) {
        // 0x0058d9dc
        charge(ctx, 1);
        lw(a2, v0, 12);
    }
    // 0x0058d9e0
    charge(ctx, 12);
    v0 = slt(0, a2);
    if (v0 == 0) a2 = a3;
    v1 = slt(a2, a3);
    s0 = a2;
    if (v1 == 0) s0 = a3;
    jal(ctx, 0x58D9F0u, gen::fn_sub_589550_00589550);
    v0 = slt(v0, s0);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    v0 = sltiu(v0, 1);
    sp = addiu(sp, 0x10);
}

// 0x0058DA10 sub_58DA10 -- 244 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// End handling of the prepare step: with parameters 79 / 80, a drained stream 2 (sub_589550) and no demux data, sets
// parameter 6 off (sub_599240) when sub_59BC88(6); then the video side.
void sub_58DA10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058da10
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a1 = 6;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    link(ctx, 0x58DA28u);  // $ra first: the delay slot below depends on it
    lw(s1, s0, trn::kDemuxWork);
    call(ctx, gen::fn_sub_599408_00599408);
    a0 = s0;
    if (v0 != 0) {
        // 0x0058da38
        charge(ctx, 4);
        a1 = 80;
        jal(ctx, 0x58DA38u, gen::fn_sub_599408_00599408);
        a0 = s0;
        if (v0 == 0) {
            goto L_0058da80;
        }
        // 0x0058da48
        charge(ctx, 4);
        a1 = 2;
        jal(ctx, 0x58DA48u, gen::fn_sub_589550_00589550);
        a0 = s0;
        if (v0 == 0) {
            // 0x0058da58
            charge(ctx, 3);
            lw(v0, s1, 8);
            if (v0 == 0) {
                // 0x0058da64
                charge(ctx, 4);
                a1 = 6;
                jal(ctx, 0x58DA64u, gen::fn_sub_59BC88_0059bc88);
                a0 = s0;
                if (v0 != 0) {
                    // 0x0058da74
                    charge(ctx, 3);
                    a1 = 6;
                    a2 = 0;
                    jal(ctx, 0x58DA78u, gen::fn_sub_599240_00599240);
                }
                goto L_0058da80;
            }
        }
        goto L_0058da84;
    }
L_0058da80:
    charge(ctx, 1);
    a0 = s0;
L_0058da84:
    charge(ctx, 4);
    a1 = 5;
    jal(ctx, 0x58DA84u, gen::fn_sub_599408_00599408);
    a0 = s0;
    if (v0 != 0) {
        // 0x0058da94
        charge(ctx, 4);
        a1 = 79;
        jal(ctx, 0x58DA94u, gen::fn_sub_599408_00599408);
        a0 = s0;
        if (v0 == 0) {
            goto L_0058daf0;
        }
        // 0x0058daa4
        charge(ctx, 4);
        a1 = 1;
        jal(ctx, 0x58DAA4u, gen::fn_sub_589550_00589550);
        if (v0 != 0) {
            ld(s0, sp, 0x0);
            // 0x0058daf4 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x10);
            sp = addiu(sp, 0x20);
            return;
        }
        // 0x0058dab4
        charge(ctx, 3);
        lw(v0, s1, 4);
        if (v0 != 0) {
            ld(s0, sp, 0x0);
            // 0x0058daf4 (the shared epilogue, written out on this path)
            charge(ctx, 4);
            ld(s1, sp, 0x8);
            ld(ra, sp, 0x10);
            sp = addiu(sp, 0x20);
            return;
        }
        // 0x0058dac0
        charge(ctx, 5);
        a0 = s0;
        a1 = 7;
        jal(ctx, 0x58DAC4u, gen::fn_sub_59BC88_0059bc88);
        a0 = s0;
        if (v0 == 0) {
            goto L_0058daf0;
        }
        // 0x0058dad4
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a1 = 5;
        ld(ra, sp, 0x10);
        a2 = 0;
        sp = addiu(sp, 0x20);
        gen::fn_sub_599240_00599240(ctx);  // tail call
        return;
    }
L_0058daf0:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0058daf4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0058DB08 sub_58DB08 -- 176 bytes; frame 0x60: s0 sp+0x20, s1 sp+0x28, s2 sp+0x30, s5 sp+0x48, s6 sp+0x50, s3 sp+0x38, s4 sp+0x40, ra sp+0x58
// Largest values over the demux object's streams (sub_577860 for each): the two maxima into the outputs.
void sub_58DB08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058db08
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s0, sp, 0x20);
    s0 = 0;
    sd(s1, sp, 0x28);
    s1 = 0;
    sd(s2, sp, 0x30);
    s2 = 0;
    sd(s5, sp, 0x48);
    s5 = a1;
    sd(s6, sp, 0x50);
    s6 = a2;
    sd(s3, sp, 0x38);
    sd(s4, sp, 0x40);
    sd(ra, sp, 0x58);
    lw(s3, a0, trn::kDemuxWork);
    lw(s4, s3, 0);
    for (;;) {
        // 0x0058db48
        charge(ctx, 13);
        a2 = s0;
        s0 = addiu(s0, 1);
        a0 = s4;
        a1 = sp;
        jal(ctx, 0x58DB54u, gen::fn_sub_577860_00577860);
        a2 = slti(s0, 3);
        lw(a0, sp, 0x8);
        lw(a1, sp, 0xC);
        v0 = slt(a0, s2);
        v1 = slt(a1, s1);
        if (v0 == 0) s2 = a0;
        if (v1 == 0) s1 = a1;
        if (a2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0058db7c
    charge(ctx, 15);
    sw(s1, s3, 4);
    sw(s2, s3, 8);
    sw(s2, s5, 0);
    ld(s0, sp, 0x20);
    lw(v0, s3, 4);
    ld(s1, sp, 0x28);
    sw(v0, s6, 0);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(s6, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
}

// 0x0058DBB8 sub_58DBB8 -- 152 bytes; frame 0x50: s1 sp+0x38, s0 sp+0x30, s2 sp+0x40, ra sp+0x48
// Copies the demux object's header values (sub_5777F8, sub_577860 1) into the handle's header record (+2316) where
// they are known (> 0 / not -1).
void sub_58DBB8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058dbb8
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s1, sp, 0x38);
    s1 = addiu(a0, 2316);
    sd(s0, sp, 0x30);
    a1 = sp;
    sd(s2, sp, 0x40);
    sd(ra, sp, 0x48);
    lw(s2, a0, trn::kDemuxWork);
    lw(s0, s2, 0);
    a0 = s0;
    jal(ctx, 0x58DBDCu, gen::fn_sub_5777F8_005777f8);
    a0 = s0;
    lw(v0, sp, 0xC);
    a1 = addiu(sp, 0x10);
    a2 = 1;
    if (i64(v0) > 0) {
        // 0x0058dbf8
        charge(ctx, 1);
        sw(v0, s1, 24);
    }
    // 0x0058dbfc
    charge(ctx, 6);
    jal(ctx, 0x58DBFCu, gen::fn_sub_577860_00577860);
    v1 = si(-1);
    lw(v0, sp, 0x20);
    if (v0 != v1) {
        sw(v0, s1, 28);
    }
    // 0x0058dc14
    charge(ctx, 3);
    lw(v0, s1, 36);
    if (v0 != v1) {
        lw(v0, s1, 40);
    } else {
        // 0x0058dc20
        charge(ctx, 3);
        lw(v0, s2, 8);
        sw(v0, s1, 36);
        lw(v0, s1, 40);
    }
    // 0x0058dc2c
    charge(ctx, 2);
    ld(s0, sp, 0x30);
    if (v0 == v1) {
        // 0x0058dc34
        charge(ctx, 2);
        lw(v0, s2, 4);
        sw(v0, s1, 40);
    }
    // 0x0058dc3c (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x38);
    ld(s2, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
}

// 0x0058DC50 sub_58DC50 -- 176 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Time of the header object (sub_58E200): when the demux has a time (+24 of its object), the 64-bit offset (+3720) and
// the start-time words.
void sub_58DC50(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058dc50
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x58DC5Cu, gen::fn_sub_58E200_0058e200);
    a1 = v0;
    v0 = si(-1);
    v0 = dsrl(v0, 1);
    a3 = addiu(s0, 3376);
    if (a1 != 0) {
        // 0x0058dc78
        charge(ctx, 4);
        lw(a2, s0, trn::kDemuxWork);
        ld(a0, a2, 24);
        t0 = addiu(s0, 2316);
        if (a0 != v0) {
            // 0x0058dc88
            charge(ctx, 5);
            ld(v0, a1, 32);
            lw(v1, a1, 0);
            v0 = a0 - v0;
            sd(v0, a3, 344);
            if (v1 == 0) {
                // 0x0058dc9c
                charge(ctx, 21);
                lw(v1, t0, 24);
                ld(a0, a3, 336);
                v0 = sll(v1, 1);
                v0 = addu(v0, v1);
                sd(a0, a1, 24);
                v0 = sll(v0, 3);
                v0 = addu(v0, v1);
                ld(v1, a2, 16);
                v0 = sll(v0, 1);
                sw(v0, a1, 4);
                sd(v1, a1, 32);
                lw(a0, t0, 28);
                sw(a0, a1, 8);
                lw(v0, a2, 4);
                sw(v0, a1, 12);
                lw(v1, a2, 8);
                sw(v1, a1, 16);
                lw(v0, a2, 44);
                sw(v0, a1, 40);
                lw(v1, a2, 48);
                sw(v1, a1, 44);
            }
        }
    }
    // 0x0058dcf0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0058DD00 sub_58DD00 -- 8 bytes; leaf frame (no stack)
// Does nothing.
void sub_58DD00(EEContext& ctx) {
    using namespace hg;
    // 0x0058dd00
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0058DD08 sub_58DD08 -- 184 bytes; frame 0x50: s0 sp+0x20, s1 sp+0x28, s2 sp+0x30, s3 sp+0x38, ra sp+0x40
// Copies up to 176 bytes of the packet's private data (sub_577910) into the header object's record (sub_58E200 + 48)
// when it is free.
void sub_58DD08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058dd08
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s0, sp, 0x20);
    sd(s1, sp, 0x28);
    s1 = a1;
    sd(s2, sp, 0x30);
    s2 = a2;
    sd(s3, sp, 0x38);
    sd(ra, sp, 0x40);
    s3 = a3;
    jal(ctx, 0x58DD28u, gen::fn_sub_58E200_0058e200);
    s0 = v0;
    if (s0 == 0) {
        ld(s0, sp, 0x20);
    } else {
        // 0x0058dd3c
        charge(ctx, 3);
        lw(v0, s0, 0);
        if (v0 != 0) {
            ld(s0, sp, 0x20);
        } else {
            // 0x0058dd48
            charge(ctx, 13);
            a0 = s1;
            a1 = sp;
            jal(ctx, 0x58DD4Cu, gen::fn_sub_577910_00577910);
            a1 = s2;
            a3 = s3;
            v0 = 176;
            v1 = slti(a3, 177);
            lw(a0, sp, 0xC);
            if (v1 == 0) a3 = v0;
            v1 = addiu(s0, 48);
            a2 = a3;
            v0 = v1;
            if (i64(a0) > 0) {
                // 0x0058dd7c
                charge(ctx, 2);
                sw(a3, v1, 352);
                goto L_0058dd9c;
            }
            // 0x0058dd88
            charge(ctx, 3);
            lw(v0, sp, 0x8);
            if (i64(v0) <= 0) {
                ld(s0, sp, 0x20);
            } else {
                // 0x0058dd94
                charge(ctx, 2);
                sw(a3, v1, 356);
                v0 = addiu(s0, 224);
            L_0058dd9c:
                charge(ctx, 3);
                a0 = v0;
                jal(ctx, 0x58DD9Cu, gen::fn_sub_575410_00575410);
                ld(s0, sp, 0x20);
            }
        }
    }
    // 0x0058dda8 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(ra, sp, 0x40);
    sp = addiu(sp, 0x50);
}

// 0x0058DDC0 sub_58DDC0 -- 124 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, ra sp+0x28
// When the handle has an input SJ (+4900), adds its chunk sizes (sub_589D80 / sub_589F38) to the 64-bit totals +2440 /
// +2448 / +2456.
void sub_58DDC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058ddc0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = a2;
    sd(s2, sp, 0x20);
    s2 = a1;
    sd(ra, sp, 0x28);
    a2 = addiu(sp, 0x4);
    a1 = sp;
    lw(v0, s0, stm::kBase + stm::kSj);
    a0 = v0;
    if (v0 != 0) {
        // 0x0058ddf4
        charge(ctx, 12);
        jal(ctx, 0x58DDF4u, gen::fn_sub_589D80_00589d80);
        ld(a0, s0, 2440);
        link(ctx, 0x58DE00u);  // $ra first: the delay slot below depends on it
        lw(a1, sp, 0x0);
        call(ctx, gen::fn_sub_589F38_00589f38);
        ld(v1, s0, 2448);
        ld(a0, s0, 2456);
        v1 = s2 + v1;
        sd(v0, s0, 2440);
        a0 = s1 + a0;
        sd(v1, s0, 2448);
        sd(a0, s0, 2456);
    }
    // 0x0058de24 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0058DE40 sub_58DE40 -- 196 bytes; frame 0x20: s0 sp+0x0, s2 sp+0x10, s1 sp+0x8, ra sp+0x18
// Data-referenced demux create: the demux record at +8600 (+8060 points to it), cleared (sub_58DF08); the demux object
// (sub_577DD8, error -16773880) with the packet callback sub_58DF90 (sub_577C68, error -16773879 after the destroy).
void sub_58DE40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058de40
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    s2 = addiu(s0, 8600);
    sd(s1, sp, 0x8);
    a0 = s2;
    sd(ra, sp, 0x18);
    link(ctx, 0x58DE60u);  // $ra first: the delay slot below depends on it
    sw(s2, s0, trn::kDemuxWork);
    call(ctx, gen::fn_sub_58DF08_0058df08);
    jal(ctx, 0x58DE68u, gen::fn_sub_577DD8_00577dd8);
    s1 = v0;
    a1 = lui(0xFF00);
    a2 = s0;
    a0 = s1;
    a1 = a1 | 0xD08;
    if (s1 == 0) {
        // 0x0058de88
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        a0 = 0;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x0058dea8
    charge(ctx, 5);
    a1 = 0x590000;
    a1 = addiu(a1, -8304);  // &sub_58DF90
    jal(ctx, 0x58DEACu, gen::fn_sub_577C68_00577c68);
    a0 = s1;
    if (v0 == 0) {
        // 0x0058dee8
        charge(ctx, 7);
        sw(s1, s2, 0);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0058debc
    charge(ctx, 11);
    jal(ctx, 0x58DEBCu, gen::fn_sub_58DFF8_0058dff8);
    a1 = lui(0xFF00);
    ld(s0, sp, 0x0);
    a0 = 0;
    ld(s1, sp, 0x8);
    a1 = a1 | 0xD09;
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0058DF08 sub_58DF08 -- 136 bytes; leaf frame (no stack)
// Clears a demux record: the time words to INT_MAX / INT64_MAX, the stamp words to -1, 67 output slots cleared.
void sub_58DF08(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0058df08
    enter(ctx, 22);  // entry check point + this block's cycles
    v0 = 0x7FFF0000;
    a1 = a0;
    v1 = si(-1);
    v0 = v0 | 0xFFFF;
    a0 = si(-1);
    a0 = dsrl(a0, 1);
    sw(v0, a1, 40);
    sd(a0, a1, 24);
    a3 = 67;
    sw(v1, a1, 56);
    a2 = addiu(a1, 332);
    sw(zero, a1, 0);
    sw(zero, a1, 4);
    sw(zero, a1, 8);
    sd(a0, a1, 16);
    sw(zero, a1, 32);
    sw(v0, a1, 36);
    sw(v1, a1, 44);
    sw(v1, a1, 48);
    sw(v1, a1, 52);
    sw(zero, a1, 60);
    for (;;) {
        // 0x0058df60
        charge(ctx, 7);
        a3 = addiu(a3, -1);
        sw(zero, a2, 0);
        a2 = addiu(a2, -4);
        if (i64(a3) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0058df7c
    charge(ctx, 5);
    v0 = si(-1);
    sw(zero, a1, 336);
    sw(v0, a1, 344);
    sw(zero, a1, 340);
}

// 0x0058DFA8 sub_58DFA8 -- 80 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Data-referenced demux destroy: sub_58DFF8 on the demux object; error -16773878.
void sub_58DFA8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058dfa8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v0, s0, trn::kDemuxWork);
    link(ctx, 0x58DFBCu);  // $ra first: the delay slot below depends on it
    lw(a0, v0, 0);
    call(ctx, gen::fn_sub_58DFF8_0058dff8);
    a1 = lui(0xFF00);
    a0 = s0;
    if (v0 == 0) {
        // 0x0058dfe8
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0058dfd0
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    a1 = a1 | 0xD0A;
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0058DFF8 sub_58DFF8 -- 20 bytes; frame 0x10: ra sp+0x0
// Thunk: sub_577F78.
void sub_58DFF8(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0058dff8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_577F78_00577f78(ctx);  // tail call
}

// 0x0058E158 sub_58E158 -- 8 bytes; leaf frame (no stack)
// Does nothing.
void sub_58E158(EEContext& ctx) {
    using namespace hg;
    // 0x0058e158
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0058E200 sub_58E200 -- 76 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// The header object's record (+14000, record at +2208) when there is one and sub_58E250 is not positive; else 0.
void sub_58E200(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058e200
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    lw(v1, s0, 14000);
    v0 = 0;
    if (v1 != 0) {
        // 0x0058e21c
        charge(ctx, 4);
        jal(ctx, 0x58E21Cu, gen::fn_sub_58E250_0058e250);
        if (i64(v0) <= 0) {
            lw(v0, s0, 14000);
            // 0x0058e238
            charge(ctx, 1);
            v0 = addiu(v0, 2208);
        } else {
            // 0x0058e22c
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x0058e23c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0058E310 sub_58E310 -- 240 bytes; leaf frame (no stack)
// Keeps a 32-byte configuration at 0x9ACAF0 (clearing 0x9ACB10 and its word +16), the two buffer addresses of $a1
// rounded up to 64 bytes at 0x9ACB18, and the first n (configuration word +28) of $a2 rounded up to 64 at 0x9ACB20,
// zeros after.
void sub_58E310(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11};
    // 0x0058e310
    enter(ctx, 28);  // entry check point + this block's cycles
    v0 = 0x9B0000;
    t1 = a0;
    v0 = addiu(v0, -13584);  // &0x9ACAF0
    v1 = 0x9B0000;
    ldl(a0, t1, 7);
    ldr(a0, t1, 0);
    ldl(a3, t1, 15);
    ldr(a3, t1, 8);
    ldl(t0, t1, 23);
    ldr(t0, t1, 16);
    ldl(t2, t1, 31);
    ldr(t2, t1, 24);
    sdl(a0, v0, 7);  // 0x9ACAF7
    sdr(a0, v0, 0);  // 0x9ACAF0
    sdl(a3, v0, 15);  // 0x9ACAFF
    sdr(a3, v0, 8);  // 0x9ACAF8
    sdl(t0, v0, 23);  // 0x9ACB07
    sdr(t0, v0, 16);  // 0x9ACB00
    sdl(t2, v0, 31);  // 0x9ACB0F
    sdr(t2, v0, 24);  // 0x9ACB08
    lw(a0, t1, 32);
    t3 = addiu(v1, -13544);  // &0x9ACB18
    sw(a0, v0, 32);  // 0x9ACB10
    t0 = a1;
    sw(zero, v0, 32);  // 0x9ACB10
    a3 = 0;
    sw(zero, v0, 16);  // 0x9ACB00
    t2 = si(-64);
    for (;;) {
        // 0x0058e380
        charge(ctx, 10);
        a0 = sll(a3, 2);
        a3 = addiu(a3, 1);
        v1 = addu(a0, t0);
        a0 = addu(a0, t3);
        lw(v0, v1, 0);
        a1 = slti(a3, 2);
        v0 = addiu(v0, 63);
        v0 = v0 & t2;
        sw(v0, a0, 0);
        if (a1 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0058e3a8
    charge(ctx, 6);
    v0 = 0x9B0000;
    lw(a0, t1, 28);
    a1 = addiu(v0, -13536);  // &0x9ACB20
    a3 = 0;
    t2 = si(-64);
    t1 = 0;
    for (;;) {
        // 0x0058e3c0
        charge(ctx, 4);
        v0 = slt(a3, a0);
        a3 = addiu(a3, 1);
        t0 = slti(a3, 16);
        if (v0 == 0) {
            // 0x0058e3e8
            charge(ctx, 1);
            sw(zero, a1, 0);
        } else {
            // 0x0058e3d0
            charge(ctx, 6);
            v1 = addu(t1, a2);
            lw(v0, v1, 0);
            v0 = addiu(v0, 63);
            v0 = v0 & t2;
            sw(v0, a1, 0);
        }
        // 0x0058e3ec
        charge(ctx, 3);
        a1 = addiu(a1, 4);
        t1 = addiu(t1, 4);
        if (t0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0058e3f8
    charge(ctx, 2);
}

// 0x0058E530 sub_58E530 -- 184 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Sets a video decoder option: optional handle check (sub_58C060, error -16776831), decoder of the handle (*(+8128))
// or 0, value $a2 (none for option 5) through sub_57B648; error -16773358.
void sub_58E530(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058e530
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v1 = 0;
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x18);
    if (s0 != 0) {
        // 0x0058e558
        charge(ctx, 5);
        jal(ctx, 0x58E558u, gen::fn_sub_58C060_0058c060);
        a1 = lui(0xFF00);
        a0 = 0;
        if (v0 == 0) {
            // 0x0058e588
            charge(ctx, 2);
            lw(v0, s0, trn::kVideoWork);
            lw(v1, v0, 0);
            goto L_0058e590;
        }
        // 0x0058e56c
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        a1 = a1 | 0x181;
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
L_0058e590:
    charge(ctx, 9);
    v0 = s1 ^ 0x5;
    a2 = 0;
    a0 = v1;
    a1 = s1;
    if (v0 != 0) a2 = s2;
    jal(ctx, 0x58E5A0u, gen::fn_sub_57B648_0057b648);
    a1 = lui(0xFF00);
    a0 = s0;
    if (v0 == 0) {
        // 0x0058e5d0
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0058e5b4
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    a1 = a1 | 0xF12;
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0058E5E8 sub_58E5E8 -- 136 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Sets up to 16 words of the video decoder's table (sub_57B648 per word) when the handle has a decoder.
void sub_58E5E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058e5e8
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    lw(v1, a0, trn::kVideoWork);
    lw(s3, v1, 0);
    v0 = 0;
    if (s3 != 0) {
        // 0x0058e610
        charge(ctx, 6);
        s0 = srl(a2, 2);
        v1 = 16;
        v0 = sltiu(s0, 17);
        if (v0 == 0) s0 = v1;
        s2 = 0;
        if (s0 != 0) {
            // 0x0058e628
            charge(ctx, 2);
            s1 = a1;
            a1 = s2;
            for (;;) {
                // 0x0058e630
                charge(ctx, 8);
                s2 = addiu(s2, 1);
                a2 = s1;
                s1 = addiu(s1, 4);
                a0 = s3;
                jal(ctx, 0x58E63Cu, gen::fn_sub_57B760_0057b760);
                v1 = slt(s2, s0);
                a1 = s2;
                if (v1 == 0) {
                    break;
                }
                backedge(ctx);
            }
        }
        // 0x0058e650
        charge(ctx, 1);
        v0 = s0;
    }
    // 0x0058e654 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0058E670 sub_58E670 -- 116 bytes; frame 0x30: s3 sp+0x18, s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x20
// Sets n option values from an array on the video decoder (sub_57B648 per value) when there is one.
void sub_58E670(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058e670
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s3, sp, 0x18);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    lw(v0, a0, trn::kVideoWork);
    lw(s2, v0, 0);
    s3 = a2;
    if (s2 != 0) {
        // 0x0058e698
        charge(ctx, 2);
        s1 = 0;
        if (i64(s3) > 0) {
            // 0x0058e6a0
            charge(ctx, 2);
            s0 = a1;
            lw(a2, s0, 0);
            for (;;) {
                // 0x0058e6a8
                charge(ctx, 8);
                s0 = addiu(s0, 4);
                a1 = s1;
                s1 = addiu(s1, 1);
                a0 = s2;
                jal(ctx, 0x58E6B4u, gen::fn_sub_57B648_0057b648);
                v1 = slt(s1, s3);
                if (v1 == 0) {
                    break;
                }
                lw(a2, s0, 0);
                backedge(ctx);
            }
        }
    }
    // 0x0058e6c8 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0058E958 sub_58E958 -- 220 bytes; frame 0x10: ra sp+0x0
// Video module init: sub_594B88, spins when sub_58EA38 reports (never), registers with sub_57AFA0(8, 0x9A89B0) (error
// -16773357 or -16773375).
void sub_58E958(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058e958
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x58E960u, gen::fn_sub_594B88_00594b88);
    jal(ctx, 0x58E968u, gen::fn_sub_58EA38_0058ea38);
    a1 = 0x9B0000;
    if (v0 != 0) {
        for (;;) {
            // 0x0058e978
            charge(ctx, 7);
            backedge(ctx);
        }
    }
    // 0x0058e998
    charge(ctx, 6);
    a0 = 8;
    a1 = addiu(a1, -30288);
    jal(ctx, 0x58E99Cu, gen::fn_sub_57AFA0_0057afa0);
    a0 = v0;
    ld(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x0058e9b0
        charge(ctx, 11);
        v0 = lui(0xFF03);
        v1 = lui(0xFF00);
        v0 = v0 | 0xFF05;
        a1 = lui(0xFF00);
        v0 = a0 ^ v0;
        a0 = 0;
        v1 = v1 | 0xF01;
        a1 = a1 | 0xF13;
        if (v0 != 0) a1 = v1;
        sp = addiu(sp, 0x10);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x0058e9e0
    charge(ctx, 21);
    a0 = 0x9B0000;
    a1 = 0;
    a0 = addiu(a0, -13584);  // &0x9ACAF0
    a2 = 36;
    jal(ctx, 0x58E9ECu, gen::fn_memset_00521408);
    a0 = 0x9B0000;
    a0 = addiu(a0, -13544);  // &0x9ACB18
    a1 = 0;
    a2 = 8;
    jal(ctx, 0x58EA00u, gen::fn_memset_00521408);
    a0 = 0x9B0000;
    a0 = addiu(a0, -13536);  // &0x9ACB20
    a1 = 0;
    a2 = 64;
    jal(ctx, 0x58EA14u, gen::fn_memset_00521408);
    v1 = 0x7B0000;
    ld(ra, sp, 0x0);
    v0 = 0;
    sw(zero, v1, 18336);  // 0x7B47A0
    sp = addiu(sp, 0x10);
}

// 0x0058EA38 sub_58EA38 -- 8 bytes; leaf frame (no stack)
// Returns nothing (an empty check the caller tests).
void sub_58EA38(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0058ea38
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0058EA60 r_lock_def_get_free_item_7 -- 172 bytes; frame 0x10: ra sp+0x0
// Per-handle video decode server: with parameter 5, unless the output ended (sub_58EC20): the options (sub_58EB10),
// the header step (sub_58EB80 with status 2, +72), the decode loop (sub_58EFD8), the end check (sub_58EC38) and
// sub_58EEC0.
void r_lock_def_get_free_item_7(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058ea60
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0058ea78
    charge(ctx, 9);
    sp = addiu(sp, -0x20);
    a1 = 5;
    sd(s1, sp, 0x8);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x58EA8Cu, gen::fn_sub_599408_00599408);
    a0 = s1;
    if (v0 != 0) {
        // 0x0058ea9c
        charge(ctx, 5);
        jal(ctx, 0x58EA9Cu, gen::fn_sub_58EC20_0058ec20);
        v1 = 1;
        a0 = s1;
        if (v0 != v1) {
            // 0x0058eab8
            charge(ctx, 6);
            jal(ctx, 0x58EAB8u, gen::fn_sub_58EB10_0058eb10);
            v1 = 2;
            lw(v0, s1, 72);
            a0 = s1;
            if (v0 == v1) {
                // 0x0058ead0
                charge(ctx, 2);
                jal(ctx, 0x58EAD0u, gen::fn_sub_58EB80_0058eb80);
            }
            // 0x0058ead8
            charge(ctx, 8);
            a0 = s1;
            jal(ctx, 0x58EAD8u, gen::fn_sub_58EFD8_0058efd8);
            a0 = s1;
            s0 = v0;
            jal(ctx, 0x58EAE4u, gen::fn_sub_58EC38_0058ec38);
            a0 = s1;
            jal(ctx, 0x58EAECu, gen::fn_sub_58EEC0_0058eec0);
            v0 = s0;
        } else {
            // 0x0058eab0
            charge(ctx, 2);
            v0 = 0;
        }
    }
    // 0x0058eaf8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0058EB10 sub_58EB10 -- 112 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// With parameter 28: the video decoder option 5 from sub_58BBE8's sign (sub_58E530).
void sub_58EB10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058eb10
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 28;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x58EB20u, gen::fn_sub_599408_00599408);
    a0 = s0;
    if (v0 == 0) {
        // 0x0058eb70
        charge(ctx, 1);
        ld(s0, sp, 0x0);
        // 0x0058eb74 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0058eb30
    charge(ctx, 7);
    jal(ctx, 0x58EB30u, gen::fn_sub_58BBE8_0058bbe8);
    a2 = 1;
    v1 = v0;
    a0 = s0;
    a1 = 5;
    if (v1 != 0) {
        // 0x0058eb4c
        charge(ctx, 2);
        a2 = 0;
        if (i64(v1) > 0) {
            goto L_0058eb60;
        }
        // 0x0058eb54
        charge(ctx, 3);
        v0 = si(-1);
        ld(s0, sp, 0x0);
        if (v1 != v0) {
            goto L_0058eb60;
        }
        // 0x0058eb74 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_0058eb60:
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
    gen::fn_sub_58E530_0058e530(ctx);  // tail call
}

// 0x0058EB80 sub_58EB80 -- 156 bytes; frame 0x40: s0 sp+0x20, s1 sp+0x28, s2 sp+0x30, ra sp+0x38
// Status 2: with the parameters 93 / 94 and a sequence-header record of 192 (+120 of the decoder), reads the header
// (sub_5796D0) into the handle.
void sub_58EB80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058eb80
    enter(ctx, 18);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    a1 = 93;
    sd(s0, sp, 0x20);
    s0 = a0;
    sd(s1, sp, 0x28);
    sd(s2, sp, 0x30);
    sd(ra, sp, 0x38);
    lw(s1, s0, trn::kVideoWork);
    link(ctx, 0x58EBA0u);  // $ra first: the delay slot below depends on it
    lw(s2, s1, 0);
    call(ctx, gen::fn_sub_599408_00599408);
    a0 = s0;
    a1 = 94;
    link(ctx, 0x58EBB0u);  // $ra first: the delay slot below depends on it
    sw(v0, sp, 0x0);
    call(ctx, gen::fn_sub_599408_00599408);
    v1 = v0;
    lw(v0, sp, 0x0);
    sw(v1, sp, 0x4);
    if (v0 != 0) {
        // 0x0058ebc8
        charge(ctx, 2);
        v0 = 192;
        if (v1 == 0) {
            goto L_0058ec04;
        }
        // 0x0058ebd0
        charge(ctx, 3);
        lw(v1, s1, 120);
        if (v1 != v0) {
            ld(s0, sp, 0x20);
        } else {
            // 0x0058ebdc
            charge(ctx, 6);
            a0 = s2;
            a1 = sp;
            a2 = addiu(sp, 0x10);
            jal(ctx, 0x58EBE4u, gen::fn_sub_5796D0_005796d0);
            ld(s0, sp, 0x20);
            if (v0 == 0) {
                // 0x0058ebf4
                charge(ctx, 4);
                v0 = 200;
                v1 = 2;
                sw(v0, s1, 120);
                sw(v1, s1, 116);
                goto L_0058ec04;
            }
        }
        // 0x0058ec08 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x28);
        ld(s2, sp, 0x30);
        ld(ra, sp, 0x38);
        sp = addiu(sp, 0x40);
        return;
    }
L_0058ec04:
    charge(ctx, 1);
    ld(s0, sp, 0x20);
    // 0x0058ec08 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x0058EC20 sub_58EC20 -- 24 bytes; frame 0x10: ra sp+0x0
// The video output stream's end flag (sub_589D10 on +8140).
void sub_58EC20(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058ec20
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a1, a0, trn::kVideoOut);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_589D10_00589d10(ctx);  // tail call
}

// 0x0058EC38 sub_58EC38 -- 208 bytes, 2 chunks; frame 0x30: s1 sp+0x8, s3 sp+0x18, s0 sp+0x0, s2 sp+0x10, ra sp+0x20
// When the input stream ended (sub_589CD0 +8136) and decoding is done (sub_58ECE8), sets the output's input end
// (sub_589CB0 1) and the end time.
void sub_58EC38(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0058ec38
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s3, sp, 0x18);
    s3 = 1;
    sd(s0, sp, 0x0);
    v0 = addiu(s1, trn::kVideo);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    lw(s2, v0, 20);
    lw(s0, v0, 16);
    a1 = s2;
    jal(ctx, 0x58EC64u, gen::fn_sub_589CD0_00589cd0);
    a0 = s1;
    a1 = s0;
    if (v0 != s3) {
        // 0x0058ec78
        charge(ctx, 4);
        jal(ctx, 0x58EC78u, gen::fn_sub_589CD0_00589cd0);
        if (v0 != s3) {
            ld(s0, sp, 0x0);
            // 0x0058eccc (the shared epilogue, written out on this path)
            charge(ctx, 6);
            ld(s1, sp, 0x8);
            ld(s2, sp, 0x10);
            ld(s3, sp, 0x18);
            ld(ra, sp, 0x20);
            sp = addiu(sp, 0x30);
            return;
        }
        // 0x0058ec88
        charge(ctx, 4);
        a0 = s1;
        jal(ctx, 0x58EC88u, gen::fn_sub_58ECE8_0058ece8);
        a0 = s1;
        if (v0 == 0) {
            goto L_0058ecc8;
        }
        // 0x0058ec98
        charge(ctx, 11);
        a1 = s2;
        a2 = 1;
        jal(ctx, 0x58EC9Cu, gen::fn_sub_589CB0_00589cb0);
        a0 = s1;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        // 0x0058ee98
        charge(ctx, 6);
        a0 = addiu(a0, 3656);
        v0 = 0x7FFF0000;
        lw(v1, a0, 36);
        v0 = v0 | 0xFFFF;
        cc = v1 == v0;  // the condition, before the delay slot changes it
        v0 = 1;
        if (!cc) {
            // 0x0058eeb0
            charge(ctx, 1);
            sw(v0, a0, 0);
        }
        // 0x0058eeb4 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_0058ecc8:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0058eccc (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0058ECE8 sub_58ECE8 -- 92 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Decoding done: sub_593958, or the frame check (sub_58ED48) and the buffer check (R_LOCK_DEF_w_lock_7).
void sub_58ECE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058ece8
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x58ECF4u, gen::fn_sub_593958_00593958);
    a0 = s0;
    if (v0 == 0) {
        // 0x0058ed04
        charge(ctx, 4);
        jal(ctx, 0x58ED04u, gen::fn_sub_58ED48_0058ed48);
        a0 = s0;
        if (v0 == 0) {
            // 0x0058ed30
            charge(ctx, 1);
            v0 = 0;
        } else {
            // 0x0058ed14
            charge(ctx, 4);
            jal(ctx, 0x58ED14u, gen::fn_R_LOCK_DEF_w_lock_7_0058edb0);
            if (v0 != 0) {
                goto L_0058ed24;
            }
            v0 = 0;
        }
        // 0x0058ed34 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s0, sp, 0x0);
        ld(ra, sp, 0x8);
        sp = addiu(sp, 0x10);
        return;
    }
L_0058ed24:
    charge(ctx, 2);
    v0 = 1;
    // 0x0058ed34 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x0058ED48 sub_58ED48 -- 104 bytes; frame 0x20: s1 sp+0x8, s0 sp+0x0, ra sp+0x10
// Enough pictures decoded: the target (+2664, else +44, capped by +44) against sub_593978 (plus +2408 in mode 2).
void sub_58ED48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0058ed48
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x10);
    lw(s0, s1, 2664);
    lw(v0, s1, 44);
    v1 = nor(0, s0);
    if (v1 == 0) s0 = v0;
    a1 = slt(v0, s0);
    if (a1 != 0) s0 = v0;
    jal(ctx, 0x58ED70u, gen::fn_sub_593978_00593978);
    lw(v1, s1, 88);
    a1 = v0;
    v0 = 2;
    cc = v1 != v0;  // the condition, before the delay slot changes it
    v0 = slt(a1, s0);
    if (!cc) {
        // 0x0058ed8c
        charge(ctx, 3);
        lw(v0, s1, 2408);
        a1 = addu(a1, v0);
        v0 = slt(a1, s0);
    }
    // 0x0058ed98 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    v0 = sltiu(v0, 1);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0058EDB0 R_LOCK_DEF_w_lock_7 -- 228 bytes; frame 0x40: s0 sp+0x10, s2 sp+0x20, s1 sp+0x18, s3 sp+0x28, ra sp+0x30
// Buffer check of the video input: input end (sub_58FF58), decoder state (+120 / +244), the stream amounts (sub_589510
// / sub_589550).
void R_LOCK_DEF_w_lock_7(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058edb0
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x10);
    sd(s2, sp, 0x20);
    s2 = a0;
    sd(s1, sp, 0x18);
    s0 = addiu(s2, 120);
    sd(s3, sp, 0x28);
    sd(ra, sp, 0x30);
    lw(s3, s2, trn::kVideoWork);
    link(ctx, 0x58EDD4u);  // $ra first: the delay slot below depends on it
    lw(s1, s3, 0);
    call(ctx, gen::fn_sub_58FF58_0058ff58);
    v1 = 1;
    if (v0 == v1) {
        ld(s0, sp, 0x10);
    } else {
        // 0x0058ede8
        charge(ctx, 3);
        lw(v0, s0, 0);
        a0 = s1;
        if (v0 != 0) {
            // 0x0058edf4
            charge(ctx, 3);
            lw(v1, s0, 124);
            v0 = 1;
            if (v1 != 0) {
                // 0x0058ee00
                charge(ctx, 1);
                a0 = s1;
                goto L_0058ee04;
            }
            goto L_0058ee78;
        }
    L_0058ee04:
        charge(ctx, 9);
        a1 = sp;
        jal(ctx, 0x58EE04u, gen::fn_sub_579240_00579240);
        a0 = s2;
        v1 = 0x30000;
        lw(a2, sp, 0x0);
        v1 = v1 | 0xFFFF;
        a1 = 1;
        v0 = 1;
        if (a2 != v1) {
            // 0x0058ee28
            charge(ctx, 8);
            jal(ctx, 0x58EE28u, gen::fn_sub_589550_00589550);
            a0 = s2;
            lw(v1, s3, 276);
            a1 = 1;
            a2 = slt(v0, v1);
            v0 = 1;
            if (a2 != 0) {
                // 0x0058ee48
                charge(ctx, 12);
                jal(ctx, 0x58EE48u, gen::fn_sub_59BCD0_0059bcd0);
                a0 = s2;
                s1 = sltiu(v0, 1);
                a1 = s1;
                jal(ctx, 0x58EE58u, gen::fn_sub_589550_00589550);
                a0 = s2;
                a1 = s1;
                s0 = v0;
                jal(ctx, 0x58EE68u, gen::fn_sub_589510_00589510);
                s0 = slt(s0, v0);
                v0 = sltiu(s0, 1);
            }
        }
    L_0058ee78:
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    }
    // 0x0058ee7c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0058EEC0 sub_58EEC0 -- 132 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Pictures done (sub_593978, sub_58EF48): sets the end state (sub_58EFB8 1) and, without +2384, parameter 5 off
// (sub_599240).
void sub_58EEC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058eec0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = addiu(s0, 2384);
    jal(ctx, 0x58EED4u, gen::fn_sub_593978_00593978);
    v1 = si(-1);
    a1 = v0;
    a0 = s0;
    if (v0 != v1) {
        // 0x0058eeec
        charge(ctx, 4);
        jal(ctx, 0x58EEECu, gen::fn_sub_58EF48_0058ef48);
        if (v0 != 0) {
            goto L_0058eefc;
        }
        ld(s0, sp, 0x0);
        // 0x0058ef34 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_0058eefc:
    charge(ctx, 8);
    a0 = s0;
    a1 = 1;
    jal(ctx, 0x58EF00u, gen::fn_sub_58EFB8_0058efb8);
    a0 = s0;
    lw(v0, s1, 0);
    a1 = 5;
    a2 = 0;
    if (v0 == 0) {
        // 0x0058ef1c
        charge(ctx, 5);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_599240_00599240(ctx);  // tail call
        return;
    }
    // 0x0058ef30
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0058ef34 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0058EF48 sub_58EF48 -- 108 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Decode finished: sub_593958, and in mode 1 the picture counter +2412 below +2408.
void sub_58EF48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0058ef48
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x58EF5Cu, gen::fn_sub_593958_00593958);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = 0;
    if (!cc) {
        // 0x0058ef6c
        charge(ctx, 2);
        v0 = 1;
        if (s1 == 0) {
            goto L_0058efa0;
        }
        // 0x0058ef74
        charge(ctx, 3);
        lw(v1, s0, 88);
        if (v1 != v0) {
            v0 = 0;
            goto L_0058efa0;
        }
        // 0x0058ef80
        charge(ctx, 2);
        if (s1 != v1) {
            v0 = 0;
            goto L_0058efa0;
        }
        // 0x0058ef88
        charge(ctx, 5);
        lw(v1, s0, 2412);
        lw(a0, s0, 2408);
        v1 = slt(v1, a0);
        ld(s0, sp, 0x0);
        if (v1 == 0) {
            // 0x0058ef9c
            charge(ctx, 1);
            v0 = 0;
            goto L_0058efa0;
        }
        // 0x0058efa4 (the shared epilogue, written out on this path)
        charge(ctx, 4);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        return;
    }
L_0058efa0:
    charge(ctx, 1);
    ld(s0, sp, 0x0);
    // 0x0058efa4 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0058EFD8 sub_58EFD8 -- 124 bytes; frame 0x30: s0 sp+0x10, ra sp+0x20, s1 sp+0x18
// Decode loop: the next picture (sub_58F058) and its decode (sub_58F808) until an error or nothing more, then
// sub_592958.
void sub_58EFD8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058efd8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x20);
    sd(s1, sp, 0x18);
    s1 = a0;
    a0 = s1;
    for (;;) {
        // 0x0058eff0
        charge(ctx, 8);
        a1 = sp;
        a2 = addiu(sp, 0x4);
        a3 = addiu(sp, 0x8);
        jal(ctx, 0x58EFF8u, gen::fn_sub_58F058_0058f058);
        a0 = s1;
        s0 = v0;
        t0 = addiu(sp, 0xC);
        if (s0 == 0) {
            // 0x0058f010
            charge(ctx, 7);
            lw(a1, sp, 0x0);
            lw(a2, sp, 0x4);
            link(ctx, 0x58F018u);  // $ra first: the delay slot below depends on it
            lw(a3, sp, 0x8);
            call(ctx, gen::fn_sub_58F808_0058f808);
            s0 = v0;
            lw(v0, sp, 0xC);
            if (s0 == 0) {
                // 0x0058f02c
                charge(ctx, 2);
                if (v0 != 0) {
                    a0 = s1;
                    backedge(ctx);
                    continue;
                }
            }
        }
        break;
    }
    // 0x0058f034
    charge(ctx, 8);
    a0 = s1;
    jal(ctx, 0x58F034u, gen::fn_sub_592958_00592958);
    v0 = s0;
    ld(s1, sp, 0x18);
    ld(s0, sp, 0x10);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0058F058 sub_58F058 -- 576 bytes; frame 0x60: s1 sp+0x38, s2 sp+0x40, s3 sp+0x48, s4 sp+0x50, s0 sp+0x30, ra sp+0x58
// Finds the next picture in the video input chunk (sub_589018): start codes (sub_58F548 206 etc.), the picture header
// (sub_58F298), the GOP / sequence codes and the position fix-ups (sub_589438 / sub_5894A8 / sub_58F458 / sub_58F4C0).
void sub_58F058(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0058f058
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x60);
    sd(s1, sp, 0x38);
    s1 = a0;
    sd(s2, sp, 0x40);
    s2 = a2;
    sd(s3, sp, 0x48);
    s3 = a1;
    sd(s4, sp, 0x50);
    s4 = a3;
    sd(s0, sp, 0x30);
    a2 = sp;
    sd(ra, sp, 0x58);
    sw(zero, s3, 0);
    lw(s0, s1, trn::kVideoIn);
    sw(zero, s2, 0);
    sw(zero, s4, 0);
    a1 = s0;
    jal(ctx, 0x58F098u, gen::fn_sub_589018_00589018);
    if (v0 != 0) {
        ld(s0, sp, 0x30);
    } else {
        // 0x0058f0a8
        charge(ctx, 3);
        lw(v1, sp, 0x4);
        a1 = 206;
        if (v1 != 0) {
            // 0x0058f0b4
            charge(ctx, 7);
            a0 = sp;
            a2 = addiu(sp, 0x20);
            jal(ctx, 0x58F0B8u, gen::fn_sub_58F548_0058f548);
            a1 = v0;
            lw(v0, sp, 0x0);
            lw(v1, sp, 0x20);
            if (a1 != v0) {
                // 0x0058f0d0
                charge(ctx, 2);
                lw(v1, sp, 0xC);
                if (a1 == 0) {
                    // 0x0058f0e8
                    charge(ctx, 6);
                    lw(v0, sp, 0x4);
                    v0 = addu(v0, v1);
                    v0 = addiu(v0, -3);
                    v1 = slti(v0, 0);
                    if (v1 != 0) v0 = 0;
                    sw(v0, s3, 0);
                } else {
                    // 0x0058f0d8
                    charge(ctx, 4);
                    a0 = sp;
                    jal(ctx, 0x58F0D8u, gen::fn_sub_58F458_0058f458);
                    sw(v0, s3, 0);
                }
                // 0x0058f100
                charge(ctx, 3);
                lw(v0, s3, 0);
                cc = i64(v0) <= 0;  // the condition, before the delay slot changes it
                v0 = 0;
                if (!cc) {
                    // 0x0058f10c
                    charge(ctx, 3);
                    v0 = 1;
                    sw(v0, s4, 0);
                    goto L_0058f274;
                }
                goto L_0058f278;
            }
            // 0x0058f118
            charge(ctx, 6);
            v0 = 4;
            sw(v0, s3, 0);
            v0 = 0;
            a0 = v1 & 0x80;
            sw(v1, s2, 0);
            if (a0 != 0) {
                goto L_0058f278;
            }
            // 0x0058f130
            charge(ctx, 11);
            a1 = s0;
            a2 = addiu(sp, 0x24);
            a0 = s1;
            a3 = addiu(sp, 0x28);
            jal(ctx, 0x58F13Cu, gen::fn_sub_589438_00589438);
            lw(a1, sp, 0x20);
            a0 = sp;
            link(ctx, 0x58F14Cu);  // $ra first: the delay slot below depends on it
            lw(a2, sp, 0x24);
            call(ctx, gen::fn_sub_58F298_0058f298);
            lw(v1, sp, 0xC);
            if (v0 != 0) {
                // 0x0058f15c
                charge(ctx, 2);
                sw(zero, sp, 0x24);
                if (v1 != 0) {
                    // 0x0058f178
                    charge(ctx, 2);
                    lw(v0, sp, 0x8);
                    v1 = addu(v0, v1);
                } else {
                    // 0x0058f164
                    charge(ctx, 4);
                    lw(v1, sp, 0x0);
                    lw(v0, sp, 0x4);
                    v1 = addu(v1, v0);
                }
                // 0x0058f180
                charge(ctx, 3);
                lw(v0, sp, 0x28);
                a0 = sp;
                if (v0 != v1) {
                    // 0x0058f18c
                    charge(ctx, 10);
                    a1 = 204;
                    a2 = addiu(sp, 0x2C);
                    link(ctx, 0x58F194u);  // $ra first: the delay slot below depends on it
                    sw(v1, sp, 0x28);
                    call(ctx, gen::fn_sub_58F6A0_0058f6a0);
                    a0 = s1;
                    lw(a3, sp, 0x28);
                    a1 = s0;
                    a2 = v0;
                    link(ctx, 0x58F1ACu);  // $ra first: the delay slot below depends on it
                    sw(v0, sp, 0x24);
                    call(ctx, gen::fn_sub_5894A8_005894a8);
                }
            }
            // 0x0058f1b4
            charge(ctx, 3);
            lw(a0, sp, 0x24);
            if (a0 != 0) {
                // 0x0058f1c0
                charge(ctx, 7);
                jal(ctx, 0x58F1C0u, gen::fn_sub_577FC8_00577fc8);
                a0 = v0;
                v0 = 8;
                v1 = a0;
                sw(a0, sp, 0x2C);
                if (v1 != v0) {
                    // 0x0058f1dc
                    charge(ctx, 3);
                    v0 = slti(v1, 9);
                    cc = v0 == 0;  // the condition, before the delay slot changes it
                    v0 = 64;
                    if (cc) {
                        goto L_0058f260;
                    }
                    // 0x0058f1e8
                    charge(ctx, 3);
                    v0 = 4;
                    cc = v1 == v0;  // the condition, before the delay slot changes it
                    lw(v0, sp, 0x24);
                    if (!cc) {
                        // 0x0058f1f4
                        charge(ctx, 2);
                        a1 = v0;
                        goto L_0058f268;
                    }
                    // 0x0058f218
                    charge(ctx, 4);
                    lw(v0, sp, 0x20);
                    v0 = v0 & 0x48;
                    a1 = 4;
                    if (v0 == 0) {
                        goto L_0058f260;
                    }
                    // 0x0058f228
                    charge(ctx, 1);
                    a0 = sp;
                    goto L_0058f22c;
                }
                // 0x0058f200
                charge(ctx, 4);
                lw(v0, sp, 0x20);
                v0 = v0 & 0x40;
                a1 = 8;
                if (v0 == 0) {
                L_0058f260:
                    charge(ctx, 2);
                    lw(v0, sp, 0x24);
                    a1 = v0;
                L_0058f268:
                    charge(ctx, 3);
                    a0 = sp;
                    jal(ctx, 0x58F268u, gen::fn_sub_58F458_0058f458);
                    sw(v0, s3, 0);
                L_0058f274:
                    charge(ctx, 1);
                    v0 = 0;
                    goto L_0058f278;
                }
                // 0x0058f210
                charge(ctx, 2);
                a0 = sp;
            L_0058f22c:
                charge(ctx, 5);
                a2 = addiu(sp, 0x20);
                jal(ctx, 0x58F22Cu, gen::fn_sub_58F548_0058f548);
                a1 = v0;
                if (a1 == 0) {
                    goto L_0058f24c;
                }
                // 0x0058f240
                charge(ctx, 3);
                lw(v0, sp, 0x24);
                cc = a1 != v0;  // the condition, before the delay slot changes it
                a1 = v0;
                if (cc) {
                    goto L_0058f268;
                }
                goto L_0058f24c;
            }
        L_0058f24c:
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x58F24Cu, gen::fn_sub_58F4C0_0058f4c0);
            ld(s0, sp, 0x30);
            // 0x0058f27c (the shared epilogue, written out on this path)
            charge(ctx, 7);
            ld(s1, sp, 0x38);
            ld(s2, sp, 0x40);
            ld(s3, sp, 0x48);
            ld(s4, sp, 0x50);
            ld(ra, sp, 0x58);
            sp = addiu(sp, 0x60);
            return;
        }
    L_0058f278:
        charge(ctx, 1);
        ld(s0, sp, 0x30);
    }
    // 0x0058f27c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s1, sp, 0x38);
    ld(s2, sp, 0x40);
    ld(s3, sp, 0x48);
    ld(s4, sp, 0x50);
    ld(ra, sp, 0x58);
    sp = addiu(sp, 0x60);
}

// 0x0058F298 sub_58F298 -- 444 bytes; frame 0x40: s1 sp+0x28, s2 sp+0x30, s0 sp+0x20, ra sp+0x38
// Moves the video input position to a found code across the two parts of the chunk.
void sub_58F298(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0058f298
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = 1;
    sd(s1, sp, 0x28);
    s1 = a2;
    sd(s2, sp, 0x30);
    s2 = a0;
    sd(s0, sp, 0x20);
    sd(ra, sp, 0x38);
    sw(a1, sp, 0x10);
    if (s1 != 0) {
        // 0x0058f2c0
        charge(ctx, 3);
        lw(a0, s2, 0);
        if (s1 != a0) {
            // 0x0058f2cc
            charge(ctx, 3);
            v0 = sltu(a0, s1);
            cc = v0 == 0;  // the condition, before the delay slot changes it
            v0 = sltu(s1, a0);
            if (!cc) {
                // 0x0058f2d8
                charge(ctx, 4);
                v1 = subu(s1, a0);
                v1 = slti(v1, 4);
                v0 = 1;
                if (v1 != 0) {
                    goto L_0058f43c;
                }
                // 0x0058f2e8
                charge(ctx, 1);
                v0 = sltu(s1, a0);
                goto L_0058f2ec;
            }
        L_0058f2ec:
            charge(ctx, 2);
            if (v0 != 0) {
                lw(v1, s2, 8);
            } else {
                // 0x0058f2f4
                charge(ctx, 5);
                lw(v0, s2, 4);
                v0 = addu(a0, v0);
                v1 = sltu(s1, v0);
                if (v1 == 0) {
                    lw(v1, s2, 8);
                    goto L_0058f358;
                }
                // 0x0058f308
                charge(ctx, 4);
                v0 = subu(s1, v0);
                s0 = addiu(v0, 4);
                if (i64(s0) > 0) {
                    // 0x0058f318
                    charge(ctx, 4);
                    lw(v1, s2, 12);
                    v1 = slt(v1, s0);
                    v0 = 1;
                    if (v1 != 0) {
                        goto L_0058f43c;
                    }
                    // 0x0058f328
                    charge(ctx, 12);
                    a2 = 4;
                    a0 = sp;
                    a2 = subu(a2, s0);
                    a1 = s1;
                    jal(ctx, 0x58F334u, gen::fn_memcpy_00521250);
                    lw(a1, s2, 8);
                    a0 = subu(sp, s0);
                    a2 = s0;
                    a0 = addiu(a0, 4);
                    jal(ctx, 0x58F348u, gen::fn_memcpy_00521250);
                    goto L_0058f398;
                }
            L_0058f388:
                charge(ctx, 4);
                lwl(v0, s1, 3);
                lwr(v0, s1, 0);
                swl(v0, sp, 0x3);
                swr(v0, sp, 0x0);
            L_0058f398:
                charge(ctx, 6);
                a0 = sp;
                jal(ctx, 0x58F398u, gen::fn_sub_577FC8_00577fc8);
                v1 = v0;
                v0 = 8;
                cc = v1 == v0;  // the condition, before the delay slot changes it
                v0 = slti(v1, 9);
                if (cc) {
                    // 0x0058f3e8
                    charge(ctx, 4);
                    lw(v0, sp, 0x10);
                    v0 = v0 & 0x40;
                    a0 = s2;
                    if (v0 == 0) {
                    L_0058f438:
                        charge(ctx, 1);
                        v0 = 0;
                    } else {
                        // 0x0058f3f8
                        charge(ctx, 2);
                        a1 = 8;
                    L_0058f414:
                        charge(ctx, 4);
                        a2 = addiu(sp, 0x10);
                        jal(ctx, 0x58F414u, gen::fn_sub_58F548_0058f548);
                        if (v0 == 0) {
                            v0 = 1;
                        } else {
                            // 0x0058f424
                            charge(ctx, 2);
                            if (v0 != s1) {
                                v0 = 0;
                            } else {
                                // 0x0058f42c
                                charge(ctx, 2);
                                v0 = 1;
                            }
                        }
                    }
                    goto L_0058f43c;
                }
                // 0x0058f3b0
                charge(ctx, 2);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = 64;
                if (cc) {
                    // 0x0058f3d0
                    charge(ctx, 2);
                    cc = v1 == v0;  // the condition, before the delay slot changes it
                    v0 = 128;
                    if (cc) {
                        goto L_0058f438;
                    }
                    // 0x0058f3d8
                    charge(ctx, 2);
                    cc = v1 == v0;  // the condition, before the delay slot changes it
                    v0 = 1;
                    if (cc) {
                        goto L_0058f438;
                    }
                    // 0x0058f3e0
                    charge(ctx, 2);
                    ld(s0, sp, 0x20);
                } else {
                    // 0x0058f3b8
                    charge(ctx, 3);
                    v0 = 4;
                    cc = v1 == v0;  // the condition, before the delay slot changes it
                    v0 = 1;
                    if (cc) {
                        // 0x0058f400
                        charge(ctx, 4);
                        lw(v0, sp, 0x10);
                        v0 = v0 & 0x48;
                        a0 = s2;
                        if (v0 == 0) {
                            goto L_0058f438;
                        }
                        // 0x0058f410
                        charge(ctx, 1);
                        a1 = 4;
                        goto L_0058f414;
                    }
                    // 0x0058f3c4
                    charge(ctx, 2);
                    ld(s0, sp, 0x20);
                }
                // 0x0058f440 (the shared epilogue, written out on this path)
                charge(ctx, 5);
                ld(s1, sp, 0x28);
                ld(s2, sp, 0x30);
                ld(ra, sp, 0x38);
                sp = addiu(sp, 0x40);
                return;
            }
        L_0058f358:
            charge(ctx, 3);
            v0 = sltu(s1, v1);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = 1;
            if (cc) {
                goto L_0058f43c;
            }
            // 0x0058f364
            charge(ctx, 5);
            lw(v0, s2, 12);
            v0 = addu(v1, v0);
            v1 = sltu(s1, v0);
            if (v1 == 0) {
                v0 = 1;
                goto L_0058f43c;
            }
            // 0x0058f378
            charge(ctx, 4);
            v1 = subu(s1, v0);
            s0 = addiu(v1, 4);
            v0 = 1;
            if (i64(s0) > 0) {
                goto L_0058f43c;
            }
            goto L_0058f388;
        }
        ld(s0, sp, 0x20);
        // 0x0058f440 (the shared epilogue, written out on this path)
        charge(ctx, 5);
        ld(s1, sp, 0x28);
        ld(s2, sp, 0x30);
        ld(ra, sp, 0x38);
        sp = addiu(sp, 0x40);
        return;
    }
L_0058f43c:
    charge(ctx, 1);
    ld(s0, sp, 0x20);
    // 0x0058f440 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x0058F458 sub_58F458 -- 100 bytes; leaf frame (no stack)
// Offset of an address inside the two-part chunk {addr0, len0, addr1, len1}: from the first part, or len0 + the offset
// in the second; 0 when outside.
void sub_58F458(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0058f458
    enter(ctx, 6);  // entry check point + this block's cycles
    a3 = a0;
    a2 = a1;
    lw(v1, a3, 0);
    v0 = sltu(a2, v1);
    a0 = subu(a2, v1);
    if (v0 == 0) {
        // 0x0058f470
        charge(ctx, 5);
        lw(v0, a3, 4);
        v0 = addu(v1, v0);
        v0 = sltu(a2, v0);
        if (v0 == 0) {
            goto L_0058f484;
        }
        // 0x0058f4b4 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        v0 = a0;
        return;
    }
L_0058f484:
    charge(ctx, 4);
    lw(a1, a3, 8);
    v0 = sltu(a2, a1);
    a0 = 0;
    if (v0 == 0) {
        // 0x0058f494
        charge(ctx, 5);
        lw(v0, a3, 12);
        v0 = addu(a1, v0);
        v0 = sltu(a2, v0);
        if (v0 != 0) {
            // 0x0058f4a8
            charge(ctx, 3);
            lw(v1, a3, 4);
            v0 = subu(a2, a1);
            a0 = addu(v0, v1);
        }
    }
    // 0x0058f4b4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    v0 = a0;
}

// 0x0058F4C0 sub_58F4C0 -- 136 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// The video input's free amount (sub_589510 - sub_589D30) against the minimum (+40): error -16773348 when below.
void sub_58F4C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058f4c0
    enter(ctx, 21);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    lw(s2, s0, trn::kVideoIn);
    a1 = s2;
    jal(ctx, 0x58F4DCu, gen::fn_sub_589510_00589510);
    a0 = s0;
    a1 = s2;
    s1 = v0;
    jal(ctx, 0x58F4ECu, gen::fn_sub_589D30_00589d30);
    a0 = s0;
    lw(v1, s0, 40);
    s1 = subu(s1, v0);
    a1 = lui(0xFF00);
    v0 = 0;
    s1 = slt(s1, v1);
    a1 = a1 | 0xF1C;
    if (s1 == 0) {
        // 0x0058f530
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0058f514
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

// 0x0058F548 sub_58F548 -- 340 bytes; frame 0x50: s1 sp+0x18, s2 sp+0x20, s5 sp+0x38, s6 sp+0x40, s0 sp+0x10, s3 sp+0x28, s4 sp+0x30, ra sp+0x48
// Searches a start code across the two-part chunk (sub_578160 on each part and on the 3-byte seam); its address and
// the part through *$a2.
void sub_58F548(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058f548
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s1, sp, 0x18);
    sd(s2, sp, 0x20);
    s2 = a0;
    sd(s5, sp, 0x38);
    s5 = a1;
    sd(s6, sp, 0x40);
    s6 = a2;
    sd(s0, sp, 0x10);
    a2 = s5;
    sd(s3, sp, 0x28);
    sd(s4, sp, 0x30);
    sd(ra, sp, 0x48);
    sw(zero, s6, 0);
    lw(a1, s2, 4);
    link(ctx, 0x58F584u);  // $ra first: the delay slot below depends on it
    lw(a0, s2, 0);
    call(ctx, gen::fn_sub_578160_00578160);
    s1 = v0;
    if (s1 != 0) {
        // 0x0058f598
        charge(ctx, 2);
        goto L_0058f664;
    }
    lw(a3, s2, 12);
    // 0x0058f5b8
    charge(ctx, 2);
    v1 = 3;
    if (a3 == 0) {
    L_0058f674:
        charge(ctx, 1);
        ld(s0, sp, 0x10);
    } else {
        // 0x0058f5c0
        charge(ctx, 23);
        lw(s3, s2, 4);
        lw(a1, s2, 0);
        s0 = v1;
        a2 = s3;
        v0 = slti(s3, 4);
        if (v0 == 0) s3 = v1;
        v0 = slti(a3, 4);
        a1 = addu(a1, a2);
        a2 = s3;
        if (v0 != 0) s0 = a3;
        a0 = sp;
        a1 = subu(a1, s3);
        s4 = 0;
        jal(ctx, 0x58F5F0u, gen::fn_memcpy_00521250);
        lw(a1, s2, 8);
        a2 = s0;
        s0 = addu(s3, s0);
        a0 = addu(sp, s3);
        s0 = addiu(s0, -3);
        jal(ctx, 0x58F608u, gen::fn_memcpy_00521250);
        v0 = slt(s1, s0);
        if (v0 == 0) {
            lw(a1, s2, 12);
        } else {
            // 0x0058f61c
            charge(ctx, 1);
            for (;;) {
                // 0x0058f620
                charge(ctx, 6);
                a0 = addu(sp, s4);
                jal(ctx, 0x58F620u, gen::fn_sub_577FC8_00577fc8);
                a2 = v0;
                v0 = a2 & s5;
                if (v0 != 0) {
                    lw(v1, s2, 4);
                    backedge(ctx);
                    goto L_0058f5a0;
                }
                // 0x0058f638
                charge(ctx, 4);
                s4 = addiu(s4, 1);
                v0 = slt(s4, s0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            // 0x0058f648
            charge(ctx, 1);
            lw(a1, s2, 12);
        }
        // 0x0058f64c
        charge(ctx, 6);
        a2 = s5;
        link(ctx, 0x58F650u);  // $ra first: the delay slot below depends on it
        lw(a0, s2, 8);
        call(ctx, gen::fn_sub_578160_00578160);
        s1 = v0;
        if (s1 != 0) {
        L_0058f664:
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x58F664u, gen::fn_sub_577FC8_00577fc8);
            sw(v0, s6, 0);
            v0 = s1;
            goto L_0058f674;
        }
        ld(s0, sp, 0x10);
    }
    // 0x0058f678 (the shared epilogue, written out on this path)
    charge(ctx, 9);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(s5, sp, 0x38);
    ld(s6, sp, 0x40);
    ld(ra, sp, 0x48);
    sp = addiu(sp, 0x50);
    return;
L_0058f5a0:
    charge(ctx, 6);
    lw(v0, s2, 0);
    sw(a2, s6, 0);
    v0 = addu(v0, v1);
    v0 = subu(v0, s3);
    v0 = addu(v0, s4);
    goto L_0058f674;
}

// 0x0058F6A0 sub_58F6A0 -- 356 bytes; frame 0x50: s2 sp+0x20, s5 sp+0x38, s6 sp+0x40, s0 sp+0x10, s1 sp+0x18, s3 sp+0x28, s4 sp+0x30, ra sp+0x48
// Searches backwards for a start code across the two-part chunk (sub_578060).
void sub_58F6A0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058f6a0
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x50);
    sd(s2, sp, 0x20);
    s2 = a0;
    sd(s5, sp, 0x38);
    sd(s6, sp, 0x40);
    s6 = a2;
    sd(s0, sp, 0x10);
    sd(s1, sp, 0x18);
    sd(s3, sp, 0x28);
    sd(s4, sp, 0x30);
    sd(ra, sp, 0x48);
    sw(zero, s6, 0);
    lw(v0, s2, 12);
    s5 = a1;
    if (v0 != 0) {
        // 0x0058f6dc
        charge(ctx, 8);
        lw(a0, s2, 8);
        a1 = v0;
        a2 = s5;
        a0 = addu(a0, v0);
        jal(ctx, 0x58F6E8u, gen::fn_sub_578060_00578060);
        s1 = v0;
        if (s1 != 0) {
            // 0x0058f6fc
            charge(ctx, 2);
            goto L_0058f7cc;
        }
        lw(s3, s2, 4);
        // 0x0058f720
        charge(ctx, 23);
        a3 = 3;
        lw(s0, s2, 12);
        a0 = sp;
        lw(a1, s2, 0);
        v1 = s3;
        v0 = slti(s3, 4);
        s4 = 0;
        if (v0 == 0) s3 = a3;
        v0 = slti(s0, 4);
        a1 = addu(a1, v1);
        if (v0 == 0) s0 = a3;
        a2 = s3;
        a1 = subu(a1, s3);
        jal(ctx, 0x58F750u, gen::fn_memcpy_00521250);
        lw(a1, s2, 8);
        a2 = s0;
        s0 = addu(s3, s0);
        a0 = addu(sp, s3);
        s0 = addiu(s0, -3);
        jal(ctx, 0x58F768u, gen::fn_memcpy_00521250);
        v0 = slt(s1, s0);
        if (v0 != 0) {
            // 0x0058f77c
            charge(ctx, 1);
            for (;;) {
                // 0x0058f780
                charge(ctx, 6);
                a0 = addu(sp, s4);
                jal(ctx, 0x58F780u, gen::fn_sub_577FC8_00577fc8);
                a2 = v0;
                v0 = a2 & s5;
                if (v0 != 0) {
                    lw(v1, s2, 4);
                    backedge(ctx);
                    goto L_0058f708;
                }
                // 0x0058f798
                charge(ctx, 4);
                s4 = addiu(s4, 1);
                v0 = slt(s4, s0);
                if (v0 == 0) {
                    break;
                }
                backedge(ctx);
            }
            goto L_0058f7a8;
        }
        lw(v0, s2, 4);
    L_0058f7ac:
        charge(ctx, 8);
        a2 = s5;
        lw(a0, s2, 0);
        a1 = v0;
        a0 = addu(a0, v0);
        jal(ctx, 0x58F7B8u, gen::fn_sub_578060_00578060);
        s1 = v0;
        if (s1 == 0) {
            ld(s0, sp, 0x10);
        } else {
        L_0058f7cc:
            charge(ctx, 4);
            a0 = s1;
            jal(ctx, 0x58F7CCu, gen::fn_sub_577FC8_00577fc8);
            sw(v0, s6, 0);
            v0 = s1;
        L_0058f7dc:
            charge(ctx, 1);
            ld(s0, sp, 0x10);
        }
        // 0x0058f7e0 (the shared epilogue, written out on this path)
        charge(ctx, 9);
        ld(s1, sp, 0x18);
        ld(s2, sp, 0x20);
        ld(s3, sp, 0x28);
        ld(s4, sp, 0x30);
        ld(s5, sp, 0x38);
        ld(s6, sp, 0x40);
        ld(ra, sp, 0x48);
        sp = addiu(sp, 0x50);
        return;
    }
L_0058f7a8:
    charge(ctx, 1);
    lw(v0, s2, 4);
    goto L_0058f7ac;
L_0058f708:
    charge(ctx, 6);
    lw(v0, s2, 0);
    sw(a2, s6, 0);
    v0 = addu(v0, v1);
    v0 = subu(v0, s3);
    v0 = addu(v0, s4);
    goto L_0058f7dc;
}

// 0x0058F808 sub_58F808 -- 720 bytes; frame 0x70: s5 sp+0x48, s0 sp+0x20, s1 sp+0x28, s4 sp+0x40, s6 sp+0x50, s7 sp+0x58, s2 sp+0x30, s3 sp+0x38, ra sp+0x60
// Decodes one picture: skips when sub_595718; with the input ended (sub_58FF58) ends (sub_593948); else the picture
// header, the decode calls (sub_58FB28 / sub_58FBE0 / sub_590008 / ...) and the input release.
void sub_58F808(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0058f808
    enter(ctx, 24);  // entry check point + this block's cycles
    sp = addiu(sp, -0x70);
    sd(s5, sp, 0x48);
    s5 = t0;
    sd(s0, sp, 0x20);
    s0 = a0;
    sd(s1, sp, 0x28);
    s1 = a2;
    sd(s4, sp, 0x40);
    s4 = addiu(s0, 2384);
    sd(s6, sp, 0x50);
    s6 = a1;
    sd(s7, sp, 0x58);
    s7 = a3;
    sd(s2, sp, 0x30);
    v0 = addiu(s0, trn::kVideo);
    sd(s3, sp, 0x38);
    sd(ra, sp, 0x60);
    sw(zero, s5, 0);
    lw(s2, v0, 16);
    lw(s3, v0, 8);
    link(ctx, 0x58F858u);  // $ra first: the delay slot below depends on it
    sw(zero, s4, 40);
    call(ctx, gen::fn_sub_595718_00595718);
    if (v0 != 0) {
        lw(v1, s3, 120);
        // 0x0058f8a0
        charge(ctx, 3);
        v0 = 204;
        if (v1 != v0) {
            s1 = s1 & 0xCC;
        } else {
            // 0x0058f8ac
            charge(ctx, 3);
            lw(v0, s3, 368);
            a1 = s2;
            if (v0 == 0) {
                // 0x0058f8b8
                charge(ctx, 1);
                s1 = s1 & 0xCC;
                goto L_0058f8bc;
            }
            goto L_0058f8c0;
        }
    L_0058f8bc:
        charge(ctx, 1);
        a1 = s2;
    L_0058f8c0:
        charge(ctx, 6);
        a0 = s0;
        a2 = addiu(sp, 0x10);
        jal(ctx, 0x58F8C4u, gen::fn_sub_5895F0_005895f0);
        s2 = v0;
        lw(v1, sp, 0x10);
        if (s2 != 0) {
            // 0x0058f8d8
            charge(ctx, 2);
            v0 = 0;
            goto L_0058faac;
        }
        // 0x0058f8e0
        charge(ctx, 2);
        if (v1 == 0) {
            ld(s0, sp, 0x20);
        } else {
            // 0x0058f8e8
            charge(ctx, 3);
            v0 = s1 & 0xC8;
            a0 = s0;
            if (v0 != 0) {
                // 0x0058f8f4
                charge(ctx, 2);
                a1 = 1;
                jal(ctx, 0x58F8F4u, gen::fn_sub_593968_00593968);
            }
            // 0x0058f8fc
            charge(ctx, 3);
            v0 = 128;
            if (s1 == v0) {
                // 0x0058f908
                charge(ctx, 6);
                a0 = s0;
                jal(ctx, 0x58F908u, gen::fn_sub_58FB28_0058fb28);
                a0 = s0;
                jal(ctx, 0x58F910u, gen::fn_sub_589FD0_00589fd0);
                lw(a1, sp, 0x10);
                if (v0 != 0) {
                    // 0x0058f920
                    charge(ctx, 4);
                    a0 = s0;
                    jal(ctx, 0x58F920u, gen::fn_sub_58FBE0_0058fbe0);
                    if (v0 == 0) {
                        // 0x0058f930
                        charge(ctx, 2);
                        v0 = 1;
                        goto L_0058faa4;
                    }
                    v0 = s2;
                    goto L_0058faac;
                }
                // 0x0058f938
                charge(ctx, 4);
                a0 = s0;
                jal(ctx, 0x58F938u, gen::fn_sub_58A038_0058a038);
                lw(a1, sp, 0x10);
                if (v0 == 0) {
                    goto L_0058f958;
                }
                // 0x0058f948
                charge(ctx, 4);
                a0 = s0;
                jal(ctx, 0x58F948u, gen::fn_sub_58FE08_0058fe08);
                v0 = 1;
            L_0058faa4:
                charge(ctx, 1);
                sw(v0, s5, 0);
            L_0058faa8:
                charge(ctx, 1);
                v0 = s2;
            L_0058faac:
                charge(ctx, 1);
                ld(s0, sp, 0x20);
                // 0x0058fab0 (the shared epilogue, written out on this path)
                charge(ctx, 10);
                ld(s1, sp, 0x28);
                ld(s2, sp, 0x30);
                ld(s3, sp, 0x38);
                ld(s4, sp, 0x40);
                ld(s5, sp, 0x48);
                ld(s6, sp, 0x50);
                ld(s7, sp, 0x58);
                ld(ra, sp, 0x60);
                sp = addiu(sp, 0x70);
                return;
            }
        L_0058f958:
            charge(ctx, 2);
            v0 = s1 & 0x4C;
            if (s7 == 0) {
                // 0x0058f960
                charge(ctx, 6);
                a0 = s0;
                a1 = s6;
                a2 = s1;
                jal(ctx, 0x58F968u, gen::fn_sub_58FF10_0058ff10);
                if (v0 != 0) {
                    // 0x0058f978
                    charge(ctx, 4);
                    a0 = s0;
                    jal(ctx, 0x58F978u, gen::fn_sub_593948_00593948);
                    v0 = s2;
                    goto L_0058faac;
                }
                v0 = slti(s6, 5);
                // 0x0058f988
                charge(ctx, 2);
                cc = v0 == 0;  // the condition, before the delay slot changes it
                v0 = s1 & 0x4C;
                if (cc) {
                    goto L_0058f9a0;
                }
                // 0x0058f990
                charge(ctx, 3);
                v0 = 1;
                sw(v0, s4, 40);
                goto L_0058faa8;
            }
        L_0058f9a0:
            charge(ctx, 2);
            a1 = sp;
            if (v0 == 0) {
                // 0x0058fa28
                charge(ctx, 3);
                v0 = s1 & 0x2;
                a0 = s0;
                if (v0 == 0) {
                    // 0x0058fa80
                    charge(ctx, 3);
                    v0 = 128;
                    lw(a1, sp, 0x10);
                    if (s1 == v0) {
                        goto L_0058faa8;
                    }
                    // 0x0058fa8c
                    charge(ctx, 5);
                    a0 = s0;
                    a2 = 204;
                    jal(ctx, 0x58FA90u, gen::fn_sub_5927D8_005927d8);
                    cc = i64(v0) <= 0;  // the condition, before the delay slot changes it
                    v0 = s2;
                    if (!cc) {
                    L_0058faa0:
                        charge(ctx, 1);
                        v0 = 1;
                        goto L_0058faa4;
                    }
                } else {
                    // 0x0058fa34
                    charge(ctx, 7);
                    a1 = sp;
                    jal(ctx, 0x58FA34u, gen::fn_sub_58FAD8_0058fad8);
                    a0 = s0;
                    a1 = sp;
                    jal(ctx, 0x58FA40u, gen::fn_sub_5915A8_005915a8);
                    lw(a1, sp, 0x10);
                    if (v0 == 0) {
                        // 0x0058fa70
                        charge(ctx, 4);
                        a0 = s0;
                        jal(ctx, 0x58FA70u, gen::fn_sub_591C80_00591c80);
                        s2 = v0;
                        goto L_0058faa8;
                    }
                    // 0x0058fa50
                    charge(ctx, 5);
                    a0 = s0;
                    jal(ctx, 0x58FA50u, gen::fn_sub_591B18_00591b18);
                    s2 = v0;
                    if (s2 == 0) {
                        // 0x0058fa64
                        charge(ctx, 2);
                        v0 = 1;
                        goto L_0058faa4;
                    }
                    v0 = s2;
                }
                goto L_0058faac;
            }
            // 0x0058f9a8
            charge(ctx, 11);
            a0 = s0;
            jal(ctx, 0x58F9A8u, gen::fn_sub_58FAD8_0058fad8);
            a0 = s0;
            lw(a2, sp, 0x10);
            a1 = sp;
            a3 = s1;
            t0 = addiu(sp, 0x14);
            jal(ctx, 0x58F9C0u, gen::fn_sub_590008_00590008);
            s2 = v0;
            if (s2 == 0) {
                // 0x0058f9d4
                charge(ctx, 3);
                lw(v0, sp, 0x14);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = 64;
                if (!cc) {
                    // 0x0058f9e0
                    charge(ctx, 4);
                    lw(v0, s3, 120);
                    v0 = s1 & v0;
                    cc = v0 == 0;  // the condition, before the delay slot changes it
                    v0 = 204;
                    if (!cc) {
                        // 0x0058f9f0
                        charge(ctx, 1);
                        sw(v0, s3, 120);
                    }
                    // 0x0058f9f4
                    charge(ctx, 3);
                    v0 = 1;
                    sw(v0, s3, 368);
                    v0 = 64;
                }
                // 0x0058fa00
                charge(ctx, 2);
                cc = s1 != v0;  // the condition, before the delay slot changes it
                v0 = 1;
                if (!cc) {
                    // 0x0058fa08
                    charge(ctx, 4);
                    lw(v1, sp, 0x14);
                    v0 = si(-2);
                    cc = v1 != v0;  // the condition, before the delay slot changes it
                    v0 = 1;
                    if (!cc) {
                        // 0x0058fa18
                        charge(ctx, 3);
                        v0 = 192;
                        sw(v0, s3, 120);
                        goto L_0058faa0;
                    }
                }
                goto L_0058faa4;
            }
            ld(s0, sp, 0x20);
        }
    } else {
        // 0x0058f868
        charge(ctx, 5);
        a0 = s0;
        jal(ctx, 0x58F868u, gen::fn_sub_58FF58_0058ff58);
        v1 = 1;
        if (v0 == v1) {
            // 0x0058f87c
            charge(ctx, 4);
            a0 = s0;
            jal(ctx, 0x58F87Cu, gen::fn_sub_593948_00593948);
            v0 = 0;
            goto L_0058faac;
        }
        sw(v1, s4, 40);
        // 0x0058f890
        charge(ctx, 4);
        a0 = s0;
        jal(ctx, 0x58F890u, gen::fn_sub_58F4C0_0058f4c0);
        ld(s0, sp, 0x20);
    }
    // 0x0058fab0 (the shared epilogue, written out on this path)
    charge(ctx, 10);
    ld(s1, sp, 0x28);
    ld(s2, sp, 0x30);
    ld(s3, sp, 0x38);
    ld(s4, sp, 0x40);
    ld(s5, sp, 0x48);
    ld(s6, sp, 0x50);
    ld(s7, sp, 0x58);
    ld(ra, sp, 0x60);
    sp = addiu(sp, 0x70);
}

// 0x0058FAD8 sub_58FAD8 -- 76 bytes; frame 0x30: s0 sp+0x20, ra sp+0x28
// The video input chunk (sub_589018 on +8136): its first two words into the output, zeros on an error.
void sub_58FAD8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058fad8
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x20);
    s0 = a1;
    sd(ra, sp, 0x28);
    a2 = sp;
    link(ctx, 0x58FAECu);  // $ra first: the delay slot below depends on it
    lw(a1, a0, trn::kVideoIn);
    call(ctx, gen::fn_sub_589018_00589018);
    lw(v1, sp, 0x0);
    if (v0 == 0) {
        // 0x0058fb08
        charge(ctx, 3);
        lw(v0, sp, 0x4);
        sw(v1, s0, 0);
        sw(v0, s0, 4);
    } else {
        // 0x0058fafc
        charge(ctx, 3);
        sw(zero, s0, 4);
        sw(zero, s0, 0);
    }
    // 0x0058fb14 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s0, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0058FE08 sub_58FE08 -- 188 bytes; frame 0x40: s0 sp+0x10, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, ra sp+0x30
// Skips start-code words of an SJ: reads 4 bytes (vtable +24); while the code is 0x80 (sub_577FC8) puts them back used
// (+32) and counts them (sub_58FEC8); otherwise returns the chunk (+28).
void sub_58FE08(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058fe08
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(s1, sp, 0x18);
    s1 = a0;
    sd(s2, sp, 0x20);
    s2 = 128;
    sd(s3, sp, 0x28);
    s3 = 4;
    sd(ra, sp, 0x30);
    for (;;) {
        // 0x0058fe58
        charge(ctx, 10);
        lw(v0, s0, 0);
        a0 = s0;
        a1 = 1;
        a2 = 4;
        lw(v1, v0, 24);
        a3 = sp;
        jalr(ctx, 0x58FE6Cu, v1.u());
        lw(v0, sp, 0x4);
        if (v0 == s3) {
            // 0x0058fe80
            charge(ctx, 4);
            link(ctx, 0x58FE80u);  // $ra first: the delay slot below depends on it
            lw(a0, sp, 0x0);
            call(ctx, gen::fn_sub_577FC8_00577fc8);
            a0 = s0;
            if (v0 != s2) {
                goto L_0058fe90_4;
            }
            backedge(ctx);
            // 0x0058fe38
            charge(ctx, 8);
            lw(v1, s0, 0);
            a1 = 0;
            lw(v0, v1, 32);
            a2 = sp;
            jalr(ctx, 0x58FE44u, v0.u());
            a0 = s1;
            a1 = 4;
            jal(ctx, 0x58FE50u, gen::fn_sub_58FEC8_0058fec8);
            continue;
        }
        lw(v1, s0, 0);
        break;
    }
L_0058fe94:
    charge(ctx, 12);
    a0 = s0;
    a1 = 1;
    lw(v0, v1, 28);
    a2 = sp;
    jalr(ctx, 0x58FEA0u, v0.u());
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
    return;
L_0058fe90_4:
    charge(ctx, 1);
    lw(v1, s0, 0);
    goto L_0058fe94;
}

// 0x0058FEC8 sub_58FEC8 -- 68 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Counts n consumed bytes: the video input stream's counter (sub_589650 on +8136) and the 64-bit total +2472.
void sub_58FEC8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058fec8
    enter(ctx, 17);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(ra, sp, 0x10);
    a2 = s1;
    link(ctx, 0x58FEE4u);  // $ra first: the delay slot below depends on it
    lw(a1, s0, trn::kVideoIn);
    call(ctx, gen::fn_sub_589650_00589650);
    ld(v0, s0, 2472);
    ld(ra, sp, 0x10);
    v0 = s1 + v0;
    ld(s1, sp, 0x8);
    sd(v0, s0, 2472);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x20);
}

// 0x0058FF10 sub_58FF10 -- 68 bytes; frame 0x10: ra sp+0x0
// Continue check of the decode loop: 1 for the code 128, or for a small result (< 5) unless the input ended
// (sub_58FF58); else 0.
void sub_58FF10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058ff10
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 128;
    sd(ra, sp, 0x0);
    a1 = slti(a1, 5);
    v0 = 1;
    if (a2 != v1) {
        // 0x0058ff28
        charge(ctx, 2);
        if (a1 == 0) {
            v0 = 0;
            goto L_0058ff48;
        }
        // 0x0058ff30
        charge(ctx, 5);
        jal(ctx, 0x58FF30u, gen::fn_sub_58FF58_0058ff58);
        v1 = 1;
        ld(ra, sp, 0x0);
        if (v0 != v1) {
            // 0x0058ff44
            charge(ctx, 1);
            v0 = 0;
            goto L_0058ff48;
        }
        // 0x0058ff4c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_0058ff48:
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    // 0x0058ff4c (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x0058FF58 sub_58FF58 -- 24 bytes; frame 0x10: ra sp+0x0
// The video input stream's end flag (sub_589D10 on +8136).
void sub_58FF58(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0058ff58
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    lw(a1, a0, trn::kVideoIn);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_589D10_00589d10(ctx);  // tail call
}

// 0x0058FF70 sub_58FF70 -- 148 bytes; frame 0x10: ra sp+0x0
// Maps a decoder result to an SFD error (sub_58BE40): -2 is fine with data left, 0 is fine, -1 / -3 and others report.
void sub_58FF70(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0058ff70
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = a1;
    v0 = si(-2);
    sd(ra, sp, 0x0);
    t0 = a0;
    if (v1 == v0) {
        // 0x0058ffb8
        charge(ctx, 2);
        v0 = 0;
        if (i64(a2) <= 0) {
            // 0x0058ffc0
            charge(ctx, 3);
            ld(ra, sp, 0x0);
            sp = addiu(sp, 0x10);
            gen::fn_sub_58BE40_0058be40(ctx);  // tail call
            return;
        }
    L_0058fff8:
        charge(ctx, 1);
        ld(ra, sp, 0x0);
        // 0x0058fffc (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0058ff88
    charge(ctx, 3);
    v0 = slti(v1, -1);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    v0 = si(-3);
    if (!cc) {
        // 0x0058ff94
        charge(ctx, 2);
        ld(ra, sp, 0x0);
        if (v1 != v0) {
            // 0x0058ff9c
            charge(ctx, 2);
            a0 = t0;
            goto L_0058ffec;
        }
        // 0x0058ffd0
        charge(ctx, 2);
        v0 = 0;
        if (i64(a2) > 0) {
            goto L_0058fff8;
        }
        // 0x0058ffd8
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        gen::fn_sub_58BE40_0058be40(ctx);  // tail call
        return;
    }
    // 0x0058ffa8
    charge(ctx, 2);
    ld(ra, sp, 0x0);
    if (v1 == 0) {
        // 0x0058ffb0
        charge(ctx, 2);
        v0 = 0;
        // 0x0058fffc (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0058ffe8
    charge(ctx, 1);
    a0 = t0;
L_0058ffec:
    charge(ctx, 3);
    a1 = a3;
    sp = addiu(sp, 0x10);
    gen::fn_sub_58BE40_0058be40(ctx);  // tail call
}

}  // namespace p3fes::game
