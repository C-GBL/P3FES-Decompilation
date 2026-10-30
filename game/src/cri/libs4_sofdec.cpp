// Phase 5 slice libs4: CRI glue next to Sofdec: the CFT work pointer, the newlib lock stubs, the 8-bit palette
// expander, the 64-bit multiply compare, the callback table thunks of 0x7B292C-0x7B2978, the stream-info record of
// the reader at 0x56F888-0x56FEC0 (0x56DEC0-0x56FEC0).
// p3fes_handgen bodies (game/include/p3fes/game/hg_cpu.h); every statement, charge and check point is the
// generator's. Roles, proposed names and the record layouts: game/include/p3fes/game/libs4.h.
#include "p3fes/game/hg_cpu.h"
#include "p3fes/game/libs4.h"

namespace p3fes::recomp_gen {
void fn_CVMH_AnalyCvmHdr_0056b240(p3fes::EEContext&);
void fn_CVMH_AnalyZoneHdr_0056b300(p3fes::EEContext&);
void fn_PFSCVFS_GetPfsTbl_005658a8(p3fes::EEContext&);
void fn_RFHN_CreateDirhn_00565ac0(p3fes::EEContext&);
void fn_RFHN_CreateHnG_00565a20(p3fes::EEContext&);
void fn_RFHN_GetStatG_00565fe8(p3fes::EEContext&);
void fn_RFHN_IsUseImgHn_00565b18(p3fes::EEContext&);
void fn_RFHN_ReopenHn_00565a78(p3fes::EEContext&);
void fn_RFMAI_CopyStructCdDr_0056a348(p3fes::EEContext&);
void fn_RFMAI_CopyStructCdPt_0056a468(p3fes::EEContext&);
void fn_RFPFS_PfsLock_0056ab90(p3fes::EEContext&);
void fn_RFPFS_PfsWait_0056ab78(p3fes::EEContext&);
void fn_RFPFS_SetPfsTbl_0056ad28(p3fes::EEContext&);
void fn_ROCI_GetInterface_0056c888(p3fes::EEContext&);
void fn_ROFS_GetNumTr_00566050(p3fes::EEContext&);
void fn_ROFS_Seek_00565c10(p3fes::EEContext&);
void fn_ROFS_Tell_00565d78(p3fes::EEContext&);
void fn_RSU_Decipher_0056d900(p3fes::EEContext&);
void fn_RSU_GenerateFixedKey_0056d780(p3fes::EEContext&);
void fn_RSU_Init_0056d6e8(p3fes::EEContext&);
void fn_SVM_ExecSvrFs_00565420(p3fes::EEContext&);
void fn___divdi3_0052eeb0(p3fes::EEContext&);
void fn___env_lock_10_0056df30(p3fes::EEContext&);
void fn___env_lock_9_0056df18(p3fes::EEContext&);
void fn___env_unlock_8_0056df20(p3fes::EEContext&);
void fn___env_unlock_9_0056df38(p3fes::EEContext&);
void fn___errno_10_00569820(p3fes::EEContext&);
void fn___errno_11_0056f500(p3fes::EEContext&);
void fn___errno_4_005584f0(p3fes::EEContext&);
void fn___moddi3_0052f6a0(p3fes::EEContext&);
void fn___muldi3_0052ea78(p3fes::EEContext&);
void fn_atan2l_9_0056dd50(p3fes::EEContext&);
void fn_coshl_9_0056dd80(p3fes::EEContext&);
void fn_cosl_9_0056dd68(p3fes::EEContext&);
void fn_cvmh_AnalyCvmHdr_0056b028(p3fes::EEContext&);
void fn_cvmh_AnalyMainHdrCvm_0056ae20(p3fes::EEContext&);
void fn_cvmh_AnalyZoneHdr_0056b128(p3fes::EEContext&);
void fn_cvmh_GetSize_0056ad48(p3fes::EEContext&);
void fn_cvmh_GetZoneDataLoc_0056b0d0(p3fes::EEContext&);
void fn_logl_9_0056def8(p3fes::EEContext&);
void fn_memcpy_00521250(p3fes::EEContext&);
void fn_memset_00521408(p3fes::EEContext&);
void fn_powl_9_0056df28(p3fes::EEContext&);
void fn_r_lock_def_free_1_0056d4a0(p3fes::EEContext&);
void fn_r_lock_def_get_free_item_1_0056d4c0(p3fes::EEContext&);
void fn_rfhn_setHandle_00565970(p3fes::EEContext&);
void fn_rfmai_copyStructCdVd_0056a0a8(p3fes::EEContext&);
void fn_rfmai_decipherSectors_00569c00(p3fes::EEContext&);
void fn_rfmai_delVolume_00567430(p3fes::EEContext&);
void fn_rfmai_setCvmfInfo_005675c8(p3fes::EEContext&);
void fn_rsu_Decipher_0056d6c0(p3fes::EEContext&);
void fn_rsu_GenerateFixedKeyByCvmhdr_0056d358(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_14_0056d6d8(p3fes::EEContext&);
void fn_sceLibgcc32GetErxEntries_15_0056dec0(p3fes::EEContext&);
void fn_sinl_9_0056df40(p3fes::EEContext&);
void fn_sprintf_00523ac8(p3fes::EEContext&);
void fn_strlen_00524388(p3fes::EEContext&);
void fn_strncat_005244c0(p3fes::EEContext&);
void fn_strncpy_00524828(p3fes::EEContext&);
void fn_sub_564878_00564878(p3fes::EEContext&);
void fn_sub_564888_00564888(p3fes::EEContext&);
void fn_sub_5648E8_005648e8(p3fes::EEContext&);
void fn_sub_564978_00564978(p3fes::EEContext&);
void fn_sub_564990_00564990(p3fes::EEContext&);
void fn_sub_564A08_00564a08(p3fes::EEContext&);
void fn_sub_564A80_00564a80(p3fes::EEContext&);
void fn_sub_564A98_00564a98(p3fes::EEContext&);
void fn_sub_564B50_00564b50(p3fes::EEContext&);
void fn_sub_564BA0_00564ba0(p3fes::EEContext&);
void fn_sub_564C10_00564c10(p3fes::EEContext&);
void fn_sub_564D20_00564d20(p3fes::EEContext&);
void fn_sub_564DB8_00564db8(p3fes::EEContext&);
void fn_sub_564DD0_00564dd0(p3fes::EEContext&);
void fn_sub_564E38_00564e38(p3fes::EEContext&);
void fn_sub_564F38_00564f38(p3fes::EEContext&);
void fn_sub_564FD0_00564fd0(p3fes::EEContext&);
void fn_sub_564FE8_00564fe8(p3fes::EEContext&);
void fn_sub_565058_00565058(p3fes::EEContext&);
void fn_sub_565158_00565158(p3fes::EEContext&);
void fn_sub_5651B0_005651b0(p3fes::EEContext&);
void fn_sub_5651F0_005651f0(p3fes::EEContext&);
void fn_sub_565230_00565230(p3fes::EEContext&);
void fn_sub_565248_00565248(p3fes::EEContext&);
void fn_sub_565328_00565328(p3fes::EEContext&);
void fn_sub_5653C0_005653c0(p3fes::EEContext&);
void fn_sub_5653D8_005653d8(p3fes::EEContext&);
void fn_sub_5653F0_005653f0(p3fes::EEContext&);
void fn_sub_565408_00565408(p3fes::EEContext&);
void fn_sub_565438_00565438(p3fes::EEContext&);
void fn_sub_565450_00565450(p3fes::EEContext&);
void fn_sub_565468_00565468(p3fes::EEContext&);
void fn_sub_565480_00565480(p3fes::EEContext&);
void fn_sub_5654A8_005654a8(p3fes::EEContext&);
void fn_sub_565550_00565550(p3fes::EEContext&);
void fn_sub_565590_00565590(p3fes::EEContext&);
void fn_sub_5655E8_005655e8(p3fes::EEContext&);
void fn_sub_565678_00565678(p3fes::EEContext&);
void fn_sub_565690_00565690(p3fes::EEContext&);
void fn_sub_5656C0_005656c0(p3fes::EEContext&);
void fn_sub_5656F0_005656f0(p3fes::EEContext&);
void fn_sub_5660F0_005660f0(p3fes::EEContext&);
void fn_sub_5662C8_005662c8(p3fes::EEContext&);
void fn_sub_5669B8_005669b8(p3fes::EEContext&);
void fn_sub_568A78_00568a78(p3fes::EEContext&);
void fn_sub_569518_00569518(p3fes::EEContext&);
void fn_sub_569700_00569700(p3fes::EEContext&);
void fn_sub_569718_00569718(p3fes::EEContext&);
void fn_sub_569730_00569730(p3fes::EEContext&);
void fn_sub_569810_00569810(p3fes::EEContext&);
void fn_sub_569830_00569830(p3fes::EEContext&);
void fn_sub_569950_00569950(p3fes::EEContext&);
void fn_sub_569960_00569960(p3fes::EEContext&);
void fn_sub_569AF0_00569af0(p3fes::EEContext&);
void fn_sub_569B60_00569b60(p3fes::EEContext&);
void fn_sub_569BD0_00569bd0(p3fes::EEContext&);
void fn_sub_569BE8_00569be8(p3fes::EEContext&);
void fn_sub_569F40_00569f40(p3fes::EEContext&);
void fn_sub_569F60_00569f60(p3fes::EEContext&);
void fn_sub_56A040_0056a040(p3fes::EEContext&);
void fn_sub_56A4F8_0056a4f8(p3fes::EEContext&);
void fn_sub_56ABE0_0056abe0(p3fes::EEContext&);
void fn_sub_56ABF8_0056abf8(p3fes::EEContext&);
void fn_sub_56AC10_0056ac10(p3fes::EEContext&);
void fn_sub_56ADB8_0056adb8(p3fes::EEContext&);
void fn_sub_56ADE0_0056ade0(p3fes::EEContext&);
void fn_sub_56B3C0_0056b3c0(p3fes::EEContext&);
void fn_sub_56B528_0056b528(p3fes::EEContext&);
void fn_sub_56B690_0056b690(p3fes::EEContext&);
void fn_sub_56B6E0_0056b6e0(p3fes::EEContext&);
void fn_sub_56B918_0056b918(p3fes::EEContext&);
void fn_sub_56C878_0056c878(p3fes::EEContext&);
void fn_sub_56C8E0_0056c8e0(p3fes::EEContext&);
void fn_sub_56CA08_0056ca08(p3fes::EEContext&);
void fn_sub_56CA78_0056ca78(p3fes::EEContext&);
void fn_sub_56CDF0_0056cdf0(p3fes::EEContext&);
void fn_sub_56CE10_0056ce10(p3fes::EEContext&);
void fn_sub_56CE48_0056ce48(p3fes::EEContext&);
void fn_sub_56CE88_0056ce88(p3fes::EEContext&);
void fn_sub_56D040_0056d040(p3fes::EEContext&);
void fn_sub_56D0D0_0056d0d0(p3fes::EEContext&);
void fn_sub_56D108_0056d108(p3fes::EEContext&);
void fn_sub_56D140_0056d140(p3fes::EEContext&);
void fn_sub_56D180_0056d180(p3fes::EEContext&);
void fn_sub_56D1E8_0056d1e8(p3fes::EEContext&);
void fn_sub_56D248_0056d248(p3fes::EEContext&);
void fn_sub_56D2D0_0056d2d0(p3fes::EEContext&);
void fn_sub_56D3B0_0056d3b0(p3fes::EEContext&);
void fn_sub_56D508_0056d508(p3fes::EEContext&);
void fn_sub_56D740_0056d740(p3fes::EEContext&);
void fn_sub_56D828_0056d828(p3fes::EEContext&);
void fn_sub_56D850_0056d850(p3fes::EEContext&);
void fn_sub_56D898_0056d898(p3fes::EEContext&);
void fn_sub_56D968_0056d968(p3fes::EEContext&);
void fn_sub_56D9A8_0056d9a8(p3fes::EEContext&);
void fn_sub_56DA10_0056da10(p3fes::EEContext&);
void fn_sub_56DA78_0056da78(p3fes::EEContext&);
void fn_sub_56DAE0_0056dae0(p3fes::EEContext&);
void fn_sub_56DB48_0056db48(p3fes::EEContext&);
void fn_sub_56DBB0_0056dbb0(p3fes::EEContext&);
void fn_sub_56DC18_0056dc18(p3fes::EEContext&);
void fn_sub_56DC80_0056dc80(p3fes::EEContext&);
void fn_sub_56DCE8_0056dce8(p3fes::EEContext&);
void fn_sub_56DDC8_0056ddc8(p3fes::EEContext&);
void fn_sub_56DDF8_0056ddf8(p3fes::EEContext&);
void fn_sub_56DED0_0056ded0(p3fes::EEContext&);
void fn_sub_56F4B8_0056f4b8(p3fes::EEContext&);
void fn_sub_56F510_0056f510(p3fes::EEContext&);
void fn_sub_56F540_0056f540(p3fes::EEContext&);
void fn_sub_56F570_0056f570(p3fes::EEContext&);
void fn_sub_56F598_0056f598(p3fes::EEContext&);
void fn_sub_56F5C0_0056f5c0(p3fes::EEContext&);
void fn_sub_56F5F0_0056f5f0(p3fes::EEContext&);
void fn_sub_56F618_0056f618(p3fes::EEContext&);
void fn_sub_56F640_0056f640(p3fes::EEContext&);
void fn_sub_56F668_0056f668(p3fes::EEContext&);
void fn_sub_56F690_0056f690(p3fes::EEContext&);
void fn_sub_56F6B8_0056f6b8(p3fes::EEContext&);
void fn_sub_56F6E0_0056f6e0(p3fes::EEContext&);
void fn_sub_56F708_0056f708(p3fes::EEContext&);
void fn_sub_56F730_0056f730(p3fes::EEContext&);
void fn_sub_56F758_0056f758(p3fes::EEContext&);
void fn_sub_56F780_0056f780(p3fes::EEContext&);
void fn_sub_56F7B0_0056f7b0(p3fes::EEContext&);
void fn_sub_56F7D8_0056f7d8(p3fes::EEContext&);
void fn_sub_56F800_0056f800(p3fes::EEContext&);
void fn_sub_56F828_0056f828(p3fes::EEContext&);
void fn_sub_56F850_0056f850(p3fes::EEContext&);
void fn_sub_56F888_0056f888(p3fes::EEContext&);
void fn_sub_56F8F8_0056f8f8_at_0056f978(p3fes::EEContext&);
void fn_sub_56F9C8_0056f9c8(p3fes::EEContext&);
void fn_sub_56FA00_0056fa00(p3fes::EEContext&);
void fn_sub_56FAB8_0056fab8(p3fes::EEContext&);
void fn_sub_56FAC0_0056fac0(p3fes::EEContext&);
void fn_sub_56FBC0_0056fbc0(p3fes::EEContext&);
void fn_sub_56FC20_0056fc20(p3fes::EEContext&);
void fn_sub_56FCB0_0056fcb0(p3fes::EEContext&);
void fn_sub_56FD28_0056fd28(p3fes::EEContext&);
void fn_sub_56FD58_0056fd58(p3fes::EEContext&);
void fn_sub_56FDE0_0056fde0(p3fes::EEContext&);
void fn_sub_56FE08_0056fe08(p3fes::EEContext&);
void fn_sub_56FE18_0056fe18(p3fes::EEContext&);
void fn_sub_56FE40_0056fe40(p3fes::EEContext&);
void fn_sub_56FEC0_0056fec0(p3fes::EEContext&);
void fn_sub_570030_00570030(p3fes::EEContext&);
void fn_sub_5753E8_005753e8(p3fes::EEContext&);
void fn_sub_57AC68_0057ac68(p3fes::EEContext&);
void fn_sub_57AE90_0057ae90(p3fes::EEContext&);
}  // namespace p3fes::recomp_gen

namespace p3fes::game {

namespace gen = ::p3fes::recomp_gen;
using namespace libs4;

// 0x0056DEC0 sceLibgcc32GetErxEntries_15 -- 12 bytes; leaf frame (no stack)
// The address of CFT's global word 0x7B2920 (FLIRT name). [cft_GetWordAdr]
void sceLibgcc32GetErxEntries_15(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0056dec0
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    v0 = addiu(v0, 10528);  // &0x7B2920
}

// 0x0056DED0 sub_56DED0 -- 40 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Set CFT's global word (0x7B2920). [cft_SetWord]
void sub_56DED0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056ded0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(s0, sp, 0x0);
    sd(ra, sp, 0x8);
    s0 = a0;
    jal(ctx, 0x56DEDCu, gen::fn_sceLibgcc32GetErxEntries_15_0056dec0);
    sw(s0, v0, 0);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056DEF8 logl_9 -- 32 bytes; frame 0x10: ra sp+0x0
// CFT's global word (FLIRT name). [cft_GetWord]
void logl_9(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056def8
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x56DF00u, gen::fn_sceLibgcc32GetErxEntries_15_0056dec0);
    lw(v0, v0, 0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056DF18 __env_lock_9 -- 8 bytes; leaf frame (no stack)
// Empty lock stub (FLIRT name). [cft_Nop1]
void __env_lock_9(EEContext& ctx) {
    using namespace hg;
    // 0x0056df18
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0056DF20 __env_unlock_8 -- 8 bytes; leaf frame (no stack)
// Empty unlock stub (FLIRT name). [cft_Nop2]
void __env_unlock_8(EEContext& ctx) {
    using namespace hg;
    // 0x0056df20
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0056DF28 powl_9 -- 8 bytes; leaf frame (no stack)
// Empty stub (FLIRT name). [cft_Nop3]
void powl_9(EEContext& ctx) {
    using namespace hg;
    // 0x0056df28
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0056DF30 __env_lock_10 -- 8 bytes; leaf frame (no stack)
// Empty lock stub (FLIRT name). [cft_Nop4]
void __env_lock_10(EEContext& ctx) {
    using namespace hg;
    // 0x0056df30
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0056DF38 __env_unlock_9 -- 8 bytes; leaf frame (no stack)
// Empty unlock stub (FLIRT name). [cft_Nop5]
void __env_unlock_9(EEContext& ctx) {
    using namespace hg;
    // 0x0056df38
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0056DF40 sinl_9 -- 5492 bytes; leaf frame (no stack)
// CFT 8-bit to 32-bit block conversion: for each 16 x 16 block of the frame (width +16 / height +20 in pixels, the
//   destination +4 and its pitch in words +8), every fourth source byte indexes a 256-word table (the third
//   argument); unrolled 16 pixels x 16 rows (FLIRT name; no caller in the binary). [cft_ConvLut32]
// As compiled, the source pointer is advanced by one column of blocks ((height / 16) x 1024 bytes) before the first
//   block is read (test_libs4 checks the 16 x 16 case against a host model).
void sinl_9(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, t5{ctx, 13};
    // 0x0056df40
    enter(ctx, 15);  // entry check point + this block's cycles
    t1 = a1;
    t0 = a2;
    lw(v1, t1, 16);
    lw(a1, t1, 20);
    v0 = slti(v1, 0);
    a2 = addiu(v1, 15);
    if (v0 != 0) v1 = a2;
    v0 = slti(a1, 0);
    a3 = addiu(a1, 15);
    v1 = sra(v1, 4);
    if (v0 != 0) a1 = a3;
    lw(a3, a0, 0);
    a1 = sra(a1, 4);
    lw(t3, t1, 4);
    if (i64(v1) > 0) {
        // 0x0056df7c
        charge(ctx, 3);
        t4 = v1;
        t5 = sll(a1, 10);
        for (;;) {
            // 0x0056df88
            charge(ctx, 3);
            a2 = t3;
            a3 = addu(a3, t5);
            if (i64(a1) > 0) {
                // 0x0056df94
                charge(ctx, 1);
                t2 = a1;
                for (;;) {
                    // 0x0056df98
                    charge(ctx, 1346);
                    lbu(v0, a3, 0);
                    t2 = addiu(t2, -1);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 0);
                    lbu(v0, a3, 4);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 4);
                    lbu(v0, a3, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 8);
                    lbu(v0, a3, 12);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 12);
                    lbu(v0, a3, 16);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 16);
                    lbu(v0, a3, 20);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 20);
                    lbu(v0, a3, 24);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 24);
                    lbu(v0, a3, 28);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 28);
                    lbu(v0, a3, 32);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 32);
                    lbu(v0, a3, 36);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 36);
                    lbu(v0, a3, 40);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 40);
                    lbu(v0, a3, 44);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 44);
                    lbu(v0, a3, 48);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 48);
                    lbu(v0, a3, 52);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 52);
                    lbu(v0, a3, 56);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 56);
                    lbu(v0, a3, 60);
                    a3 = addiu(a3, 64);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 60);
                    lbu(v0, a3, 0);
                    lw(v1, t1, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    v1 = sll(v1, 2);
                    lw(a0, v0, 0);
                    a2 = addu(a2, v1);
                    sw(a0, a2, 0);
                    lbu(v0, a3, 4);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 4);
                    lbu(v0, a3, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 8);
                    lbu(v0, a3, 12);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 12);
                    lbu(v0, a3, 16);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 16);
                    lbu(v0, a3, 20);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 20);
                    lbu(v0, a3, 24);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 24);
                    lbu(v0, a3, 28);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 28);
                    lbu(v0, a3, 32);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 32);
                    lbu(v0, a3, 36);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 36);
                    lbu(v0, a3, 40);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 40);
                    lbu(v0, a3, 44);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 44);
                    lbu(v0, a3, 48);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 48);
                    lbu(v0, a3, 52);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 52);
                    lbu(v0, a3, 56);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 56);
                    lbu(v0, a3, 60);
                    a3 = addiu(a3, 64);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 60);
                    lbu(v0, a3, 0);
                    lw(v1, t1, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    v1 = sll(v1, 2);
                    lw(a0, v0, 0);
                    a2 = addu(a2, v1);
                    sw(a0, a2, 0);
                    lbu(v0, a3, 4);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 4);
                    lbu(v0, a3, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 8);
                    lbu(v0, a3, 12);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 12);
                    lbu(v0, a3, 16);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 16);
                    lbu(v0, a3, 20);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 20);
                    lbu(v0, a3, 24);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 24);
                    lbu(v0, a3, 28);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 28);
                    lbu(v0, a3, 32);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 32);
                    lbu(v0, a3, 36);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 36);
                    lbu(v0, a3, 40);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 40);
                    lbu(v0, a3, 44);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 44);
                    lbu(v0, a3, 48);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 48);
                    lbu(v0, a3, 52);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 52);
                    lbu(v0, a3, 56);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 56);
                    lbu(v0, a3, 60);
                    a3 = addiu(a3, 64);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 60);
                    lbu(v0, a3, 0);
                    lw(v1, t1, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    v1 = sll(v1, 2);
                    lw(a0, v0, 0);
                    a2 = addu(a2, v1);
                    sw(a0, a2, 0);
                    lbu(v0, a3, 4);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 4);
                    lbu(v0, a3, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 8);
                    lbu(v0, a3, 12);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 12);
                    lbu(v0, a3, 16);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 16);
                    lbu(v0, a3, 20);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 20);
                    lbu(v0, a3, 24);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 24);
                    lbu(v0, a3, 28);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 28);
                    lbu(v0, a3, 32);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 32);
                    lbu(v0, a3, 36);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 36);
                    lbu(v0, a3, 40);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 40);
                    lbu(v0, a3, 44);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 44);
                    lbu(v0, a3, 48);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 48);
                    lbu(v0, a3, 52);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 52);
                    lbu(v0, a3, 56);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 56);
                    lbu(v0, a3, 60);
                    a3 = addiu(a3, 64);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 60);
                    lbu(v0, a3, 0);
                    lw(v1, t1, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    v1 = sll(v1, 2);
                    lw(a0, v0, 0);
                    a2 = addu(a2, v1);
                    sw(a0, a2, 0);
                    lbu(v0, a3, 4);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 4);
                    lbu(v0, a3, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 8);
                    lbu(v0, a3, 12);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 12);
                    lbu(v0, a3, 16);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 16);
                    lbu(v0, a3, 20);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 20);
                    lbu(v0, a3, 24);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 24);
                    lbu(v0, a3, 28);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 28);
                    lbu(v0, a3, 32);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 32);
                    lbu(v0, a3, 36);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 36);
                    lbu(v0, a3, 40);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 40);
                    lbu(v0, a3, 44);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 44);
                    lbu(v0, a3, 48);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 48);
                    lbu(v0, a3, 52);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 52);
                    lbu(v0, a3, 56);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 56);
                    lbu(v0, a3, 60);
                    a3 = addiu(a3, 64);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 60);
                    lbu(v0, a3, 0);
                    lw(v1, t1, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    v1 = sll(v1, 2);
                    lw(a0, v0, 0);
                    a2 = addu(a2, v1);
                    sw(a0, a2, 0);
                    lbu(v0, a3, 4);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 4);
                    lbu(v0, a3, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 8);
                    lbu(v0, a3, 12);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 12);
                    lbu(v0, a3, 16);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 16);
                    lbu(v0, a3, 20);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 20);
                    lbu(v0, a3, 24);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 24);
                    lbu(v0, a3, 28);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 28);
                    lbu(v0, a3, 32);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 32);
                    lbu(v0, a3, 36);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 36);
                    lbu(v0, a3, 40);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 40);
                    lbu(v0, a3, 44);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 44);
                    lbu(v0, a3, 48);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 48);
                    lbu(v0, a3, 52);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 52);
                    lbu(v0, a3, 56);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 56);
                    lbu(v0, a3, 60);
                    a3 = addiu(a3, 64);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 60);
                    lbu(v0, a3, 0);
                    lw(v1, t1, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    v1 = sll(v1, 2);
                    lw(a0, v0, 0);
                    a2 = addu(a2, v1);
                    sw(a0, a2, 0);
                    lbu(v0, a3, 4);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 4);
                    lbu(v0, a3, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 8);
                    lbu(v0, a3, 12);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 12);
                    lbu(v0, a3, 16);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 16);
                    lbu(v0, a3, 20);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 20);
                    lbu(v0, a3, 24);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 24);
                    lbu(v0, a3, 28);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 28);
                    lbu(v0, a3, 32);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 32);
                    lbu(v0, a3, 36);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 36);
                    lbu(v0, a3, 40);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 40);
                    lbu(v0, a3, 44);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 44);
                    lbu(v0, a3, 48);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 48);
                    lbu(v0, a3, 52);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 52);
                    lbu(v0, a3, 56);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 56);
                    lbu(v0, a3, 60);
                    a3 = addiu(a3, 64);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 60);
                    lbu(v0, a3, 0);
                    lw(v1, t1, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    v1 = sll(v1, 2);
                    lw(a0, v0, 0);
                    a2 = addu(a2, v1);
                    sw(a0, a2, 0);
                    lbu(v0, a3, 4);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 4);
                    lbu(v0, a3, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 8);
                    lbu(v0, a3, 12);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 12);
                    lbu(v0, a3, 16);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 16);
                    lbu(v0, a3, 20);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 20);
                    lbu(v0, a3, 24);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 24);
                    lbu(v0, a3, 28);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 28);
                    lbu(v0, a3, 32);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 32);
                    lbu(v0, a3, 36);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 36);
                    lbu(v0, a3, 40);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 40);
                    lbu(v0, a3, 44);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 44);
                    lbu(v0, a3, 48);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 48);
                    lbu(v0, a3, 52);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 52);
                    lbu(v0, a3, 56);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 56);
                    lbu(v0, a3, 60);
                    a3 = addiu(a3, 64);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 60);
                    lbu(v0, a3, 0);
                    lw(v1, t1, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    v1 = sll(v1, 2);
                    lw(a0, v0, 0);
                    a2 = addu(a2, v1);
                    sw(a0, a2, 0);
                    lbu(v0, a3, 4);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 4);
                    lbu(v0, a3, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 8);
                    lbu(v0, a3, 12);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 12);
                    lbu(v0, a3, 16);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 16);
                    lbu(v0, a3, 20);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 20);
                    lbu(v0, a3, 24);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 24);
                    lbu(v0, a3, 28);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 28);
                    lbu(v0, a3, 32);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 32);
                    lbu(v0, a3, 36);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 36);
                    lbu(v0, a3, 40);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 40);
                    lbu(v0, a3, 44);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 44);
                    lbu(v0, a3, 48);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 48);
                    lbu(v0, a3, 52);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 52);
                    lbu(v0, a3, 56);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 56);
                    lbu(v0, a3, 60);
                    a3 = addiu(a3, 64);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 60);
                    lbu(v0, a3, 0);
                    lw(v1, t1, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    v1 = sll(v1, 2);
                    lw(a0, v0, 0);
                    a2 = addu(a2, v1);
                    sw(a0, a2, 0);
                    lbu(v0, a3, 4);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 4);
                    lbu(v0, a3, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 8);
                    lbu(v0, a3, 12);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 12);
                    lbu(v0, a3, 16);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 16);
                    lbu(v0, a3, 20);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 20);
                    lbu(v0, a3, 24);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 24);
                    lbu(v0, a3, 28);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 28);
                    lbu(v0, a3, 32);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 32);
                    lbu(v0, a3, 36);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 36);
                    lbu(v0, a3, 40);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 40);
                    lbu(v0, a3, 44);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 44);
                    lbu(v0, a3, 48);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 48);
                    lbu(v0, a3, 52);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 52);
                    lbu(v0, a3, 56);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 56);
                    lbu(v0, a3, 60);
                    a3 = addiu(a3, 64);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 60);
                    lbu(v0, a3, 0);
                    lw(v1, t1, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    v1 = sll(v1, 2);
                    lw(a0, v0, 0);
                    a2 = addu(a2, v1);
                    sw(a0, a2, 0);
                    lbu(v0, a3, 4);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 4);
                    lbu(v0, a3, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 8);
                    lbu(v0, a3, 12);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 12);
                    lbu(v0, a3, 16);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 16);
                    lbu(v0, a3, 20);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 20);
                    lbu(v0, a3, 24);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 24);
                    lbu(v0, a3, 28);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 28);
                    lbu(v0, a3, 32);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 32);
                    lbu(v0, a3, 36);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 36);
                    lbu(v0, a3, 40);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 40);
                    lbu(v0, a3, 44);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 44);
                    lbu(v0, a3, 48);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 48);
                    lbu(v0, a3, 52);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 52);
                    lbu(v0, a3, 56);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 56);
                    lbu(v0, a3, 60);
                    a3 = addiu(a3, 64);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 60);
                    lbu(v0, a3, 0);
                    lw(v1, t1, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    v1 = sll(v1, 2);
                    lw(a0, v0, 0);
                    a2 = addu(a2, v1);
                    sw(a0, a2, 0);
                    lbu(v0, a3, 4);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 4);
                    lbu(v0, a3, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 8);
                    lbu(v0, a3, 12);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 12);
                    lbu(v0, a3, 16);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 16);
                    lbu(v0, a3, 20);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 20);
                    lbu(v0, a3, 24);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 24);
                    lbu(v0, a3, 28);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 28);
                    lbu(v0, a3, 32);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 32);
                    lbu(v0, a3, 36);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 36);
                    lbu(v0, a3, 40);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 40);
                    lbu(v0, a3, 44);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 44);
                    lbu(v0, a3, 48);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 48);
                    lbu(v0, a3, 52);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 52);
                    lbu(v0, a3, 56);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 56);
                    lbu(v0, a3, 60);
                    a3 = addiu(a3, 64);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 60);
                    lbu(v0, a3, 0);
                    lw(v1, t1, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    v1 = sll(v1, 2);
                    lw(a0, v0, 0);
                    a2 = addu(a2, v1);
                    sw(a0, a2, 0);
                    lbu(v0, a3, 4);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 4);
                    lbu(v0, a3, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 8);
                    lbu(v0, a3, 12);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 12);
                    lbu(v0, a3, 16);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 16);
                    lbu(v0, a3, 20);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 20);
                    lbu(v0, a3, 24);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 24);
                    lbu(v0, a3, 28);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 28);
                    lbu(v0, a3, 32);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 32);
                    lbu(v0, a3, 36);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 36);
                    lbu(v0, a3, 40);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 40);
                    lbu(v0, a3, 44);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 44);
                    lbu(v0, a3, 48);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 48);
                    lbu(v0, a3, 52);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 52);
                    lbu(v0, a3, 56);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 56);
                    lbu(v0, a3, 60);
                    a3 = addiu(a3, 64);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 60);
                    lbu(v0, a3, 0);
                    lw(v1, t1, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    v1 = sll(v1, 2);
                    lw(a0, v0, 0);
                    a2 = addu(a2, v1);
                    sw(a0, a2, 0);
                    lbu(v0, a3, 4);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 4);
                    lbu(v0, a3, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 8);
                    lbu(v0, a3, 12);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 12);
                    lbu(v0, a3, 16);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 16);
                    lbu(v0, a3, 20);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 20);
                    lbu(v0, a3, 24);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 24);
                    lbu(v0, a3, 28);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 28);
                    lbu(v0, a3, 32);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 32);
                    lbu(v0, a3, 36);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 36);
                    lbu(v0, a3, 40);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 40);
                    lbu(v0, a3, 44);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 44);
                    lbu(v0, a3, 48);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 48);
                    lbu(v0, a3, 52);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 52);
                    lbu(v0, a3, 56);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 56);
                    lbu(v0, a3, 60);
                    a3 = addiu(a3, 64);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 60);
                    lbu(v0, a3, 0);
                    lw(v1, t1, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    v1 = sll(v1, 2);
                    lw(a0, v0, 0);
                    a2 = addu(a2, v1);
                    sw(a0, a2, 0);
                    lbu(v0, a3, 4);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 4);
                    lbu(v0, a3, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 8);
                    lbu(v0, a3, 12);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 12);
                    lbu(v0, a3, 16);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 16);
                    lbu(v0, a3, 20);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 20);
                    lbu(v0, a3, 24);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 24);
                    lbu(v0, a3, 28);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 28);
                    lbu(v0, a3, 32);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 32);
                    lbu(v0, a3, 36);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 36);
                    lbu(v0, a3, 40);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 40);
                    lbu(v0, a3, 44);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 44);
                    lbu(v0, a3, 48);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 48);
                    lbu(v0, a3, 52);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 52);
                    lbu(v0, a3, 56);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 56);
                    lbu(v0, a3, 60);
                    a3 = addiu(a3, 64);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 60);
                    lbu(v0, a3, 0);
                    lw(v1, t1, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    v1 = sll(v1, 2);
                    lw(a0, v0, 0);
                    a2 = addu(a2, v1);
                    sw(a0, a2, 0);
                    lbu(v0, a3, 4);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 4);
                    lbu(v0, a3, 8);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 8);
                    lbu(v0, a3, 12);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 12);
                    lbu(v0, a3, 16);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 16);
                    lbu(v0, a3, 20);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 20);
                    lbu(v0, a3, 24);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 24);
                    lbu(v0, a3, 28);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 28);
                    lbu(v0, a3, 32);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 32);
                    lbu(v0, a3, 36);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 36);
                    lbu(v0, a3, 40);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 40);
                    lbu(v0, a3, 44);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 44);
                    lbu(v0, a3, 48);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 48);
                    lbu(v0, a3, 52);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 52);
                    lbu(v0, a3, 56);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 56);
                    lbu(v0, a3, 60);
                    a3 = addiu(a3, 64);
                    v0 = sll(v0, 2);
                    v0 = addu(v0, t0);
                    lw(v1, v0, 0);
                    sw(v1, a2, 60);
                    lw(v0, t1, 8);
                    v0 = sll(v0, 2);
                    a2 = addu(a2, v0);
                    if (t2 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0056f4a0
            charge(ctx, 3);
            t4 = addiu(t4, -1);
            t3 = addiu(t3, 64);
            if (t4 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0056f4ac (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0056F4B8 sub_56F4B8 -- 68 bytes; leaf frame (no stack)
// Compare two fractions by 64-bit cross products (MMI mult1): a2 x a1 >= a0 x a3. [sfd_CmpRatio]
void sub_56F4B8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0056f4b8
    enter(ctx, 17);  // entry check point + this block's cycles
    mult(zero, a0, a3);
    mult1(zero, a2, a1);
    mflo(v0);
    mfhi(a0);
    v0 = dsll32(v0, 0);
    a0 = dsll32(a0, 0);
    v0 = dsrl32(v0, 0);
    mflo1(v1);
    a0 = a0 | v0;
    mfhi1(v0);
    v1 = dsll32(v1, 0);
    v0 = dsll32(v0, 0);
    v1 = dsrl32(v1, 0);
    v0 = v0 | v1;
    v0 = slt(v0, a0);
    v0 = v0 ^ 0x1;
}

// 0x0056F500 __errno_11 -- 12 bytes; leaf frame (no stack)
// A Sofdec global (0x7B2928). [sfd_GetGlobal]
void __errno_11(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x0056f500
    enter(ctx, 3);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    lw(v0, v1, 10536);  // 0x7B2928
}

// 0x0056F510 sub_56F510 -- 44 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x7B292C when set (else 0). [sfd_CallCb0]
void sub_56F510(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f510
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v1, 10540);  // 0x7B292C
    v0 = 0;
    sd(ra, sp, 0x0);
    if (v1 != 0) {
        // 0x0056f528
        charge(ctx, 2);
        jalr(ctx, 0x56F528u, v1.u());
    }
    // 0x0056f530 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056F540 sub_56F540 -- 44 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x7B2930 when set (else 0). [sfd_CallCb1]
void sub_56F540(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f540
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v1, 10544);  // 0x7B2930
    v0 = 0;
    sd(ra, sp, 0x0);
    if (v1 != 0) {
        // 0x0056f558
        charge(ctx, 2);
        jalr(ctx, 0x56F558u, v1.u());
    }
    // 0x0056f560 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056F570 sub_56F570 -- 40 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x7B2934 when set (else 0: the empty slot itself). [sfd_CallCb2]
void sub_56F570(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f570
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10548);  // 0x7B2934
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056f584
        charge(ctx, 2);
        jalr(ctx, 0x56F584u, v0.u());
    }
    // 0x0056f58c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056F598 sub_56F598 -- 40 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x7B2938 when set. [sfd_CallCb3]
void sub_56F598(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f598
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10552);  // 0x7B2938
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056f5ac
        charge(ctx, 2);
        jalr(ctx, 0x56F5ACu, v0.u());
    }
    // 0x0056f5b4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056F5C0 sub_56F5C0 -- 44 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x7B293C when set (else 0). [sfd_CallCb4]
void sub_56F5C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f5c0
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v1, 10556);  // 0x7B293C
    v0 = 0;
    sd(ra, sp, 0x0);
    if (v1 != 0) {
        // 0x0056f5d8
        charge(ctx, 2);
        jalr(ctx, 0x56F5D8u, v1.u());
    }
    // 0x0056f5e0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056F5F0 sub_56F5F0 -- 40 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x7B2940 when set. [sfd_CallCb5]
void sub_56F5F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f5f0
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10560);  // 0x7B2940
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056f604
        charge(ctx, 2);
        jalr(ctx, 0x56F604u, v0.u());
    }
    // 0x0056f60c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056F618 sub_56F618 -- 40 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x7B2948 when set. [sfd_CallCb7]
void sub_56F618(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f618
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10568);  // 0x7B2948
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056f62c
        charge(ctx, 2);
        jalr(ctx, 0x56F62Cu, v0.u());
    }
    // 0x0056f634 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056F640 sub_56F640 -- 40 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x7B2944 when set. [sfd_CallCb6]
void sub_56F640(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f640
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10564);  // 0x7B2944
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056f654
        charge(ctx, 2);
        jalr(ctx, 0x56F654u, v0.u());
    }
    // 0x0056f65c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056F668 sub_56F668 -- 40 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x7B294C when set. [sfd_CallCb8]
void sub_56F668(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f668
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10572);  // 0x7B294C
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056f67c
        charge(ctx, 2);
        jalr(ctx, 0x56F67Cu, v0.u());
    }
    // 0x0056f684 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056F690 sub_56F690 -- 40 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x7B2950 when set. [sfd_CallCb9]
void sub_56F690(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f690
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10576);  // 0x7B2950
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056f6a4
        charge(ctx, 2);
        jalr(ctx, 0x56F6A4u, v0.u());
    }
    // 0x0056f6ac (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056F6B8 sub_56F6B8 -- 40 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x7B2954 when set. [sfd_CallCb10]
void sub_56F6B8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f6b8
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10580);  // 0x7B2954
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056f6cc
        charge(ctx, 2);
        jalr(ctx, 0x56F6CCu, v0.u());
    }
    // 0x0056f6d4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056F6E0 sub_56F6E0 -- 40 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x7B2958 when set. [sfd_CallCb11]
void sub_56F6E0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f6e0
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10584);  // 0x7B2958
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056f6f4
        charge(ctx, 2);
        jalr(ctx, 0x56F6F4u, v0.u());
    }
    // 0x0056f6fc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056F708 sub_56F708 -- 40 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x7B295C when set. [sfd_CallCb12]
void sub_56F708(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f708
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10588);  // 0x7B295C
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056f71c
        charge(ctx, 2);
        jalr(ctx, 0x56F71Cu, v0.u());
    }
    // 0x0056f724 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056F730 sub_56F730 -- 40 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x7B2960 when set. [sfd_CallCb13]
void sub_56F730(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f730
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10592);  // 0x7B2960
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056f744
        charge(ctx, 2);
        jalr(ctx, 0x56F744u, v0.u());
    }
    // 0x0056f74c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056F758 sub_56F758 -- 40 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x7B2964 when set. [sfd_CallCb14]
void sub_56F758(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f758
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10596);  // 0x7B2964
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056f76c
        charge(ctx, 2);
        jalr(ctx, 0x56F76Cu, v0.u());
    }
    // 0x0056f774 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056F780 sub_56F780 -- 44 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x7B2968 when set (else 0). [sfd_CallCb15]
void sub_56F780(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f780
    enter(ctx, 6);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v1, 10600);  // 0x7B2968
    v0 = 0;
    sd(ra, sp, 0x0);
    if (v1 != 0) {
        // 0x0056f798
        charge(ctx, 2);
        jalr(ctx, 0x56F798u, v1.u());
    }
    // 0x0056f7a0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056F7B0 sub_56F7B0 -- 40 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x7B296C when set. [sfd_CallCb16]
void sub_56F7B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f7b0
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10604);  // 0x7B296C
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056f7c4
        charge(ctx, 2);
        jalr(ctx, 0x56F7C4u, v0.u());
    }
    // 0x0056f7cc (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056F7D8 sub_56F7D8 -- 40 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x7B2970 when set. [sfd_CallCb17]
void sub_56F7D8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f7d8
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10608);  // 0x7B2970
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056f7ec
        charge(ctx, 2);
        jalr(ctx, 0x56F7ECu, v0.u());
    }
    // 0x0056f7f4 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056F800 sub_56F800 -- 40 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x7B2974 when set. [sfd_CallCb18]
void sub_56F800(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f800
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10612);  // 0x7B2974
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056f814
        charge(ctx, 2);
        jalr(ctx, 0x56F814u, v0.u());
    }
    // 0x0056f81c (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056F828 sub_56F828 -- 40 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x7B2978 when set. [sfd_CallCb19]
void sub_56F828(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f828
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, 10616);  // 0x7B2978
    sd(ra, sp, 0x0);
    if (v0 != 0) {
        // 0x0056f83c
        charge(ctx, 2);
        jalr(ctx, 0x56F83Cu, v0.u());
    }
    // 0x0056f844 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056F850 sub_56F850 -- 56 bytes; frame 0x10: ra sp+0x0
// Clear five Sofdec globals (0x7B2980..0x7B2990). [sfd_ClrGlobals]
void sub_56F850(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f850
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0x7B0000;
    sd(ra, sp, 0x0);
    a0 = addiu(a0, 10624);  // &0x7B2980
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    // 0x0056f870
    charge(ctx, 6);
    sw(zero, a0, 16);
    sw(zero, a0, 0);
    sw(zero, a0, 4);
    sw(zero, a0, 8);
    sw(zero, a0, 12);
}

// 0x0056F888 sub_56F888 -- 112 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Reader method: with a valid handle (0x5753E8 says 0) store {a1, a2} at +4; an invalid one goes to the shared error
//   tail 0x56F978. [sfdrd_SetCb]
void sub_56F888(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056f888
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a1;
    jal(ctx, 0x56F8A4u, gen::fn_sub_5753E8_005753e8);
    a1 = lui(0xFF03);
    s0 = addiu(s0, 4);
    a0 = 0;
    a1 = a1 | 0x203;
    if (v0 != 0) {
        // 0x0056f8c0
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_56F8F8_0056f8f8_at_0056f978(ctx);  // tail call
        return;
    }
    // 0x0056f8d8
    charge(ctx, 8);
    sw(s1, s0, 4);
    sw(s2, s0, 0);
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0056F9C8 sub_56F9C8 -- 52 bytes; frame 0x10: ra sp+0x0
// Store a flag at +8 and, when it is set, call the callback at +0 with its object +4. [sfdrd_SetFlagCall]
void sub_56F9C8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0056f9c8
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a1;
    sd(ra, sp, 0x0);
    sw(v0, a0, 8);
    if (v0 != 0) {
        // 0x0056f9dc
        charge(ctx, 3);
        lw(v0, a0, 0);
        if (v0 != 0) {
            // 0x0056f9e8
            charge(ctx, 2);
            jt = v0.u();  // the target, read before the delay slot
            link(ctx, 0x56F9E8u);  // $ra = the return address
            lw(a0, a0, 4);
            call_ptr(ctx, jt);
            goto L_0056f9f0;
        }
        ld(ra, sp, 0x0);
        // 0x0056f9f4 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_0056f9f0:
    charge(ctx, 1);
    ld(ra, sp, 0x0);
    // 0x0056f9f4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x0056FA00 sub_56FA00 -- 184 bytes; frame 0x30: s0 sp+0x0, s3 sp+0x18, s1 sp+0x8, s2 sp+0x10, ra sp+0x20
// Reader method: with a valid handle, read the stream (0x57AC68) while it gives data without the flags 0xCC and a
//   4-byte read (0x57AE90) succeeds; then the shared tail. [sfdrd_Skip]
void sub_56FA00(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056fa00
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s3, sp, 0x18);
    sd(s1, sp, 0x8);
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x20);
    s3 = a0;
    jal(ctx, 0x56FA1Cu, gen::fn_sub_5753E8_005753e8);
    ld(s1, sp, 0x8);
    if (v0 != 0) {
        // 0x0056fa2c
        charge(ctx, 9);
        a1 = lui(0xFF03);
        ld(s0, sp, 0x0);
        a0 = 0;
        ld(s2, sp, 0x10);
        a1 = a1 | 0x20A;
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_56F8F8_0056f8f8_at_0056f978(ctx);  // tail call
        return;
    }
    // 0x0056fa50
    charge(ctx, 4);
    s1 = lui(0xFF03);
    s2 = 4;
    s1 = s1 | 0x305;
    for (;;) {
        // 0x0056fa60
        charge(ctx, 7);
        a0 = s0;
        jal(ctx, 0x56FA60u, gen::fn_sub_57AC68_0057ac68);
        a0 = s0;
        a1 = 1;
        a2 = 4;
        v1 = v0 & 0xCC;
        if (v0 != 0) {
            // 0x0056fa7c
            charge(ctx, 2);
            if (v1 != 0) {
                s1 = 0;
            } else {
                // 0x0056fa84
                charge(ctx, 4);
                jal(ctx, 0x56FA84u, gen::fn_sub_57AE90_0057ae90);
                if (v0 == s2) {
                    backedge(ctx);
                    continue;
                }
            }
        }
        break;
    }
    // 0x0056fa94
    charge(ctx, 9);
    a0 = s3;
    ld(s3, sp, 0x18);
    a1 = s1;
    ld(s1, sp, 0x8);
    ld(s0, sp, 0x0);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
    gen::fn_sub_56F8F8_0056f8f8_at_0056f978(ctx);  // tail call
}

// 0x0056FAB8 sub_56FAB8 -- 8 bytes; leaf frame (no stack)
// Reader method: nothing. [sfdrd_Nop]
void sub_56FAB8(EEContext& ctx) {
    using namespace hg;
    // 0x0056fab8
    enter(ctx, 2);  // entry check point + this block's cycles
}

// 0x0056FAC0 sub_56FAC0 -- 256 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Reader method: copy the 128-byte stream info (+88) out, 32 bytes per step (two loops by alignment). [sfdrd_GetInfo]
void sub_56FAC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056fac0
    enter(ctx, 9);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x56FAD4u, gen::fn_sub_5753E8_005753e8);
    a0 = 0;
    if (v0 != 0) {
        // 0x0056fae4
        charge(ctx, 7);
        a1 = lui(0xFF03);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x10);
        a1 = a1 | 0x20C;
        sp = addiu(sp, 0x20);
        gen::fn_sub_56F8F8_0056f8f8_at_0056f978(ctx);  // tail call
        return;
    }
    // 0x0056fb00
    charge(ctx, 6);
    a1 = s1;
    v1 = addiu(s0, 88);
    v0 = v1 | a1;
    v0 = v0 & 0x7;
    a0 = addiu(s0, 216);
    if (v0 == 0) {
        for (;;) {
            // 0x0056fb78
            charge(ctx, 13);
            ld(v0, v1, 0);
            ld(a2, v1, 8);
            ld(a3, v1, 16);
            ld(t0, v1, 24);
            sd(v0, a1, 0);
            sd(a2, a1, 8);
            sd(a3, a1, 16);
            sd(t0, a1, 24);
            v1 = addiu(v1, 32);
            a1 = addiu(a1, 32);
            if (v1 == a0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0056fbac
        charge(ctx, 1);
        ld(s0, sp, 0x0);
    } else {
        for (;;) {
            // 0x0056fb18
            charge(ctx, 21);
            ldl(v0, v1, 7);
            ldr(v0, v1, 0);
            ldl(a2, v1, 15);
            ldr(a2, v1, 8);
            ldl(a3, v1, 23);
            ldr(a3, v1, 16);
            ldl(t0, v1, 31);
            ldr(t0, v1, 24);
            sdl(v0, a1, 7);
            sdr(v0, a1, 0);
            sdl(a2, a1, 15);
            sdr(a2, a1, 8);
            sdl(a3, a1, 23);
            sdr(a3, a1, 16);
            sdl(t0, a1, 31);
            sdr(t0, a1, 24);
            v1 = addiu(v1, 32);
            a1 = addiu(a1, 32);
            if (v1 == a0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0056fb6c
        charge(ctx, 2);
        ld(s0, sp, 0x0);
    }
    // 0x0056fbb0 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0056FBC0 sub_56FBC0 -- 92 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Reader method: a word of the reader (+352 + 724) out. [sfdrd_GetWord1]
void sub_56FBC0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056fbc0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = addiu(a0, 352);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a1;
    jal(ctx, 0x56FBD4u, gen::fn_sub_5753E8_005753e8);
    a1 = lui(0xFF03);
    a0 = 0;
    if (v0 == 0) {
        // 0x0056fc00
        charge(ctx, 7);
        lw(v0, s0, 724);
        ld(ra, sp, 0x10);
        sw(v0, s1, 0);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0056fbe8
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    a1 = a1 | 0x20D;
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_56F8F8_0056f8f8_at_0056f978(ctx);  // tail call
}

// 0x0056FC20 sub_56FC20 -- 144 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Reader method: the size in bytes ((+352 + 728) << 11), a word (+352 + 228) and -1 out; returns -1. [sfdrd_GetSize]
void sub_56FC20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056fc20
    enter(ctx, 15);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x0);
    s0 = addiu(a0, 352);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    sd(ra, sp, 0x20);
    s3 = a3;
    jal(ctx, 0x56FC44u, gen::fn_sub_5753E8_005753e8);
    a1 = lui(0xFF03);
    a0 = 0;
    a1 = a1 | 0x20F;
    if (v0 != 0) {
        // 0x0056fc5c
        charge(ctx, 7);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_56F8F8_0056f8f8_at_0056f978(ctx);  // tail call
        return;
    }
    // 0x0056fc78
    charge(ctx, 14);
    lw(v0, s0, 728);
    ld(ra, sp, 0x20);
    v0 = sll(v0, 11);
    sw(v0, s1, 0);
    v0 = si(-1);
    ld(s1, sp, 0x8);
    lw(v1, s0, 228);
    ld(s0, sp, 0x0);
    sw(v1, s2, 0);
    sw(v0, s3, 0);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    sp = addiu(sp, 0x30);
}

// 0x0056FCB0 sub_56FCB0 -- 120 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Reader method: two words (+352 + 208 / 212) out. [sfdrd_GetWord2]
void sub_56FCB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056fcb0
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = addiu(a0, 352);
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x56FCCCu, gen::fn_sub_5753E8_005753e8);
    a1 = lui(0xFF03);
    a0 = 0;
    a1 = a1 | 0x20E;
    if (v0 != 0) {
        // 0x0056fce4
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_56F8F8_0056f8f8_at_0056f978(ctx);  // tail call
        return;
    }
    // 0x0056fd00
    charge(ctx, 10);
    lw(v0, s0, 208);
    ld(ra, sp, 0x18);
    sw(v0, s1, 0);
    ld(s1, sp, 0x8);
    lw(v1, s0, 212);
    ld(s0, sp, 0x0);
    sw(v1, s2, 0);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0056FD28 sub_56FD28 -- 44 bytes; leaf frame (no stack)
// Count down by 32 from 31 until negative (returns -1). [sfd_Spin]
void sub_56FD28(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0056fd28
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 63;
    v0 = addiu(v0, -32);
    for (;;) {
        // 0x0056fd30
        charge(ctx, 7);
        if (i64(v0) < 0) {
            break;
        }
        v0 = addiu(v0, -32);
        backedge(ctx);
    }
    // 0x0056fd4c
    charge(ctx, 2);
}

// 0x0056FD58 sub_56FD58 -- 132 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Reset the reader's 1328-byte state at +352 and its defaults (255 marks, 1 flags). [sfdrd_Reset]
void sub_56FD58(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056fd58
    enter(ctx, 33);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a1 = 0;
    sd(s0, sp, 0x0);
    s0 = addiu(a0, 352);
    a0 = s0;
    sd(ra, sp, 0x8);
    a2 = 1328;
    jal(ctx, 0x56FD70u, gen::fn_memset_00521408);
    v0 = 255;
    v1 = 1;
    sw(v1, s0, 212);
    sw(v0, s0, 124);
    sw(zero, s0, 1316);
    sw(v1, s0, 76);
    sw(zero, s0, 112);
    sw(v0, s0, 116);
    sw(v0, s0, 120);
    sw(zero, s0, 1136);
    sw(zero, s0, 1140);
    sw(zero, s0, 1144);
    sw(zero, s0, 1148);
    sw(zero, s0, 1152);
    sw(zero, s0, 1156);
    sw(zero, s0, 1164);
    sw(zero, s0, 968);
    sw(zero, s0, 1280);
    sw(zero, s0, 1284);
    sw(zero, s0, 1300);
    sw(zero, s0, 208);
    ld(ra, sp, 0x8);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056FDE0 sub_56FDE0 -- 36 bytes; leaf frame (no stack)
// Store {a2, a3, a4} in the reader's 12-byte entry n at +280. [sfdrd_SetEntry]
void sub_56FDE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x0056fde0
    enter(ctx, 9);  // entry check point + this block's cycles
    v0 = sll(a1, 1);
    v0 = addu(v0, a1);
    v0 = sll(v0, 2);
    a0 = addu(a0, v0);
    a0 = addiu(a0, 280);
    sw(t0, a0, 8);
    sw(a2, a0, 0);
    sw(a3, a0, 4);
}

// 0x0056FE08 sub_56FE08 -- 16 bytes; leaf frame (no stack)
// Store {a1, a2} at +328. [sfdrd_SetPair]
void sub_56FE08(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0056fe08
    enter(ctx, 4);  // entry check point + this block's cycles
    a0 = addiu(a0, 328);
    sw(a2, a0, 4);
    sw(a1, a0, 0);
}

// 0x0056FE18 sub_56FE18 -- 40 bytes; leaf frame (no stack)
// Get the words at +328 and +336 into the given pointers (each optional). [sfdrd_GetPair]
void sub_56FE18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0056fe18
    enter(ctx, 2);  // entry check point + this block's cycles
    a0 = addiu(a0, 328);
    if (a1 != 0) {
        // 0x0056fe20
        charge(ctx, 2);
        lw(v0, a0, 0);
        sw(v0, a1, 0);
    }
    // 0x0056fe28
    charge(ctx, 2);
    if (a2 != 0) {
        // 0x0056fe30
        charge(ctx, 2);
        lw(v0, a0, 8);
        sw(v0, a2, 0);
    }
    // 0x0056fe38 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0056FE40 sub_56FE40 -- 124 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Reader method: with a valid handle, 0x570030; on success build the stream info. [sfdrd_Open]
void sub_56FE40(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056fe40
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x56FE54u, gen::fn_sub_5753E8_005753e8);
    a0 = 0;
    a1 = s0;
    if (v0 != 0) {
        // 0x0056fe68
        charge(ctx, 7);
        a1 = lui(0xFF03);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a1 = a1 | 0x20C;
        ld(ra, sp, 0x10);
        sp = addiu(sp, 0x20);
        gen::fn_sub_56F8F8_0056f8f8_at_0056f978(ctx);  // tail call
        return;
    }
    // 0x0056fe88
    charge(ctx, 5);
    a0 = s1;
    jal(ctx, 0x56FE88u, gen::fn_sub_570030_00570030);
    s0 = v0;
    a0 = s1;
    if (s0 == 0) {
        // 0x0056fe9c
        charge(ctx, 2);
        jal(ctx, 0x56FE9Cu, gen::fn_sub_56FEC0_0056fec0);
    }
    // 0x0056fea4 (the shared epilogue, written out on this path)
    charge(ctx, 6);
    v0 = s0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x0056FEC0 sub_56FEC0 -- 364 bytes; leaf frame (no stack)
// Build the 108-byte stream info (+88) from the reader's state (+352): sizes, counts, a format byte from the table
//   0x7C78C0. [sfdrd_MakeInfo]
void sub_56FEC0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8};
    // 0x0056fec0
    enter(ctx, 91);  // entry check point + this block's cycles
    v1 = addiu(a0, 352);
    a0 = addiu(a0, 88);
    lw(a1, v1, 708);
    a3 = 1;
    sw(zero, a0, 64);
    sw(a1, a0, 0);
    lw(v0, v1, 712);
    sw(v0, a0, 4);
    lw(a1, v1, 716);
    sw(a1, a0, 8);
    lw(v0, v1, 720);
    sw(v0, a0, 12);
    lw(a1, v1, 220);
    lw(v0, v1, 16);
    sw(a1, a0, 20);
    sw(v0, a0, 16);
    lw(a1, v1, 188);
    lw(a2, v1, 224);
    sw(a1, a0, 28);
    sw(a2, a0, 24);
    lw(v0, v1, 192);
    sw(v0, a0, 32);
    lw(a1, v1, 196);
    sw(a1, a0, 36);
    lw(v0, v1, 200);
    sw(v0, a0, 40);
    lw(a1, v1, 204);
    sw(a1, a0, 44);
    lw(v0, v1, 1184);
    sw(v0, a0, 48);
    lw(a1, v1, 1168);
    sw(a1, a0, 52);
    lw(v0, v1, 280);
    lw(a1, v1, 76);
    sw(v0, a0, 56);
    sw(a1, a0, 60);
    sw(a3, a0, 68);
    lw(v0, v1, 724);
    sw(v0, a0, 72);
    lw(a1, v1, 728);
    sw(a1, a0, 76);
    lw(v0, v1, 72);
    lw(a1, v1, 308);
    lhu(a3, v1, 128);
    v0 = sll(v0, 1);
    lhu(t0, v1, 132);
    v0 = addu(v0, a1);
    lw(a2, v1, 284);
    v0 = sll(v0, 1);
    sh(a3, a0, 80);
    sh(t0, a0, 82);
    v0 = addu(v0, a2);
    a1 = 0x7C0000;
    a1 = addu(a1, v0);
    lbu(a1, a1, 30912);
    sb(a1, a0, 84);
    lbu(v0, v1, 316);
    sb(v0, a0, 85);
    lbu(a1, v1, 284);
    sb(a1, a0, 86);
    lbu(v0, v1, 308);
    sb(v0, a0, 87);
    lbu(a1, v1, 964);
    sb(a1, a0, 88);
    lbu(v0, v1, 12);
    sb(v0, a0, 89);
    lbu(a1, v1, 32);
    sb(a1, a0, 90);
    lbu(v0, v1, 100);
    sb(v0, a0, 91);
    lbu(a1, v1, 104);
    sb(a1, a0, 92);
    lbu(v0, v1, 68);
    sb(v0, a0, 93);
    lbu(a1, v1, 72);
    sb(a1, a0, 94);
    lbu(v0, v1, 96);
    sb(v0, a0, 95);
    lbu(a1, v1, 108);
    sb(a1, a0, 96);
    lbu(v0, v1, 112);
    sb(v0, a0, 97);
    lbu(a1, v1, 116);
    sb(a1, a0, 98);
    lbu(v0, v1, 120);
    sb(v0, a0, 99);
    lbu(a1, v1, 124);
    sb(a1, a0, 100);
    lw(v0, v1, 1296);
    sw(v0, a0, 104);
}

}  // namespace p3fes::game
