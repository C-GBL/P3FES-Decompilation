// Phase 5 slice libs4: CRI SVM, the rest of it: the lock-type getter, the error helpers, the version number text,
// the server table (8 server types x 6 slots: register, unregister, set, execute one, execute a type), the per-type
// execution counters, init / finish, the callback setters and the test-and-set (0x564878-0x5656F0).
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

// 0x00564878 sub_564878 -- 16 bytes; leaf frame (no stack)
// Count one up in the u16 at +2 of a record and return the new value (no caller in the binary). [svm_IncU16]
void sub_564878(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4};
    // 0x00564878
    enter(ctx, 4);  // entry check point + this block's cycles
    lhu(v0, a0, 2);
    v0 = addiu(v0, 1);
    sh(v0, a0, 2);
}

// 0x00564A08 sub_564A08 -- 24 bytes; frame 0x10: ra sp+0x0
// SVM lock of type 1000 (the general lock 0x564888 with the type the ADX setup does not use). [svm_LockType1000]
void sub_564A08(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564a08
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 1000;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564888_00564888(ctx);  // tail call
}

// 0x00564A80 sub_564A80 -- 24 bytes; frame 0x10: ra sp+0x0
// SVM unlock of type 1000. [svm_UnlockType1000]
void sub_564A80(EEContext& ctx) {
    using namespace hg;
    Gpr a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564a80
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 1000;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_5648E8_005648e8(ctx);  // tail call
}

// 0x00564A98 sub_564A98 -- 16 bytes; leaf frame (no stack)
// The outermost lock's type (0x7B2634). [svm_GetLockType]
void sub_564A98(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3};
    // 0x00564a98
    enter(ctx, 4);  // entry check point + this block's cycles
    v1 = 0x7B0000;
    v1 = addiu(v1, 9780);  // &0x7B2634
    lw(v0, v1, 0);  // 0x7B2634
}

// 0x00564BA0 sub_564BA0 -- 108 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// SVM error with two texts: strncpy (127) the first into the 128-byte buffer 0x7B2678, strncat (127) the second, then
//   the error callback (0x99A0B0 / its object 0x99A0B4) when one is set. [svm_CallErr2]
void sub_564BA0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00564ba0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    a2 = 127;
    sd(s0, sp, 0x0);
    s0 = 0x7B0000;
    s0 = addiu(s0, 9848);  // &0x7B2678
    sd(s1, sp, 0x8);
    s1 = a1;
    a1 = a0;
    sd(ra, sp, 0x10);
    a0 = s0;
    jal(ctx, 0x564BC4u, gen::fn_strncpy_00524828);
    a0 = s0;
    a1 = s1;
    a2 = 127;
    jal(ctx, 0x564BD4u, gen::fn_strncat_005244c0);
    v0 = 0x9A0000;
    v0 = addiu(v0, -24400);  // &0x99A0B0
    lw(v1, v0, 0);  // 0x99A0B0
    a1 = s0;
    if (v1 != 0) {
        // 0x00564bf0
        charge(ctx, 2);
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x564BF0u);  // $ra = the return address
        lw(a0, v0, 4);
        call_ptr(ctx, jt);
    }
    // 0x00564bf8 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(ra, sp, 0x10);
    sp = addiu(sp, 0x20);
}

// 0x00564C10 sub_564C10 -- 272 bytes; frame 0x30: s1 sp+0x8, ra sp+0x28, s0 sp+0x0, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20
// Number to text, as compiled: the digits of n (raw 0..9, no '0' added; at most 32) go into buf, then buf is
//   overwritten with the reversed text of the static buffer 0x999E00 (never written here: the digit loop writes buf,
//   so the reversal copies whatever 0x999E00 holds), at most len - 1 bytes, NUL-terminated. [svm_ItoA]
void sub_564C10(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00564c10
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x28);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s2, sp, 0x10);
    s2 = 0;
    sd(s3, sp, 0x18);
    s3 = a1;
    sd(s4, sp, 0x20);
    s4 = a2;
    v0 = slti(s2, 32);
    for (;;) {
        // 0x00564c40
        charge(ctx, 2);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = 0x9A0000;
        if (cc) {
            break;
        }
        // 0x00564c48
        charge(ctx, 15);
        a0 = s0;
        v0 = dsll32(s2, 0);
        v0 = dsra32(v0, 0);
        a1 = 10;
        s1 = addu(s3, v0);
        jal(ctx, 0x564C58u, gen::fn___moddi3_0052f6a0);
        a0 = s0;
        v0 = v0 & 0xFF;
        a1 = 10;
        sb(v0, s1, 0);
        s2 = daddiu(s2, 1);
        jal(ctx, 0x564C70u, gen::fn___divdi3_0052eeb0);
        s0 = v0;
        v0 = slti(s2, 32);
        if (s0 == 0) {
            goto L_00564c84_3;
        }
        backedge(ctx);
    }
L_00564c8c:
    charge(ctx, 11);
    s2 = 0;
    s0 = addiu(v0, -25088);
    a0 = s0;
    jal(ctx, 0x564C94u, gen::fn_strlen_00524388);
    v1 = daddiu(s4, -1);
    v0 = dsll32(v0, 0);
    a1 = dsrl32(v0, 0);
    v0 = slt(a1, v1);
    if (v0 == 0) a1 = v1;
    if (i64(a1) > 0) {
        // 0x00564cb8
        charge(ctx, 2);
        a3 = s0;
        a2 = daddiu(a1, -1);
        for (;;) {
            // 0x00564cc0
            charge(ctx, 12);
            v0 = dsll32(a2, 0);
            v0 = dsra32(v0, 0);
            a2 = daddiu(a2, -1);
            v0 = addu(v0, a3);
            v1 = dsll32(s2, 0);
            v1 = dsra32(v1, 0);
            lbu(a0, v0, 0);
            s2 = daddiu(s2, 1);
            v1 = addu(s3, v1);
            v0 = slt(s2, a1);
            sb(a0, v1, 0);
            if (v0 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x00564cf0 (the shared epilogue, written out on this path)
    charge(ctx, 12);
    v0 = dsll32(s2, 0);
    v0 = dsra32(v0, 0);
    ld(s2, sp, 0x10);
    v0 = addu(s3, v0);
    ld(s3, sp, 0x18);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sb(zero, v0, 0);
    sp = addiu(sp, 0x30);
    return;
L_00564c84_3:
    charge(ctx, 2);
    sb(zero, s1, 0);
    v0 = 0x9A0000;
    goto L_00564c8c;
}

// 0x00564D20 sub_564D20 -- 152 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Version text "major minor": svm_ItoA of the first number, a space appended (strncat to len), svm_ItoA of the second
//   number after it with 4 - strlen as its length (no caller in the binary). [svm_ItoA2]
void sub_564D20(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564d20
    enter(ctx, 38);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a3;
    sd(s1, sp, 0x8);
    s1 = a2;
    sd(s2, sp, 0x10);
    s2 = a1;
    a2 = s0;
    s0 = dsll32(s0, 0);
    s0 = dsra32(s0, 0);
    sd(ra, sp, 0x18);
    a1 = s1;
    jal(ctx, 0x564D4Cu, gen::fn_sub_564C10_00564c10);
    a0 = s1;
    jal(ctx, 0x564D54u, gen::fn_strlen_00524388);
    a1 = 0x7C0000;
    s0 = subu(s0, v0);
    a1 = addiu(a1, 28096);  // &0x7C6DC0
    a2 = addiu(s0, -1);
    a0 = s1;
    jal(ctx, 0x564D6Cu, gen::fn_strncat_005244c0);
    a0 = s1;
    jal(ctx, 0x564D74u, gen::fn_strlen_00524388);
    a0 = s1;
    s1 = addu(s1, v0);
    jal(ctx, 0x564D80u, gen::fn_strlen_00524388);
    a2 = 4;
    ld(s0, sp, 0x0);
    a2 = subu(a2, v0);
    a0 = s2;
    a1 = s1;
    ld(s1, sp, 0x8);
    a2 = dsll32(a2, 0);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    a2 = dsrl32(a2, 0);
    sp = addiu(sp, 0x20);
    gen::fn_sub_564C10_00564c10(ctx);  // tail call
}

// 0x00564DB8 sub_564DB8 -- 24 bytes; frame 0x10: ra sp+0x0
// Register a server function with no name: SVM_SetCbSvr(type, function, object, 0). [svm_SetCbSvrNoName]
void sub_564DB8(EEContext& ctx) {
    using namespace hg;
    Gpr a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564db8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a3 = 0;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564DD0_00564dd0(ctx);  // tail call
}

// 0x00564DD0 sub_564DD0 -- 104 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, ra sp+0x20
// Register a server function (locked, type 1): svm_SetCbSvr; returns its slot id or -1. [SVM_SetCbSvr]
void sub_564DD0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564dd0
    enter(ctx, 26);  // entry check point + this block's cycles
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
    jal(ctx, 0x564DF4u, gen::fn_sub_564978_00564978);
    a0 = s0;
    a1 = s1;
    a2 = s2;
    a3 = s3;
    jal(ctx, 0x564E08u, gen::fn_sub_564E38_00564e38);
    s0 = v0;
    jal(ctx, 0x564E10u, gen::fn_sub_564990_00564990);
    ld(s1, sp, 0x8);
    v0 = s0;
    ld(s2, sp, 0x10);
    ld(s0, sp, 0x0);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00564E38 sub_564E38 -- 192 bytes; frame 0x10: ra sp+0x0
// Register a server function in the first free slot of a server type (0..7; 6 slots of {function, object, name} in
//   the table 0x999E20, 72 bytes per type); the name defaults to "Unknown". Errors (named by its text
//   '1051001:SVM_SetCbSvr:too many server function', '1071205:SVM_SetCbSvrId:illegal svtype'): -1. [svm_SetCbSvr]
void sub_564E38(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564e38
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = sltiu(a0, 8);
    sd(ra, sp, 0x0);
    if (v0 == 0) {
        // 0x00564e48
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 28104);  // "1071205:SVM_SetCbSvrId:illegal svtype"
        goto L_00564ee0;
    }
    // 0x00564e60
    charge(ctx, 12);
    v0 = sll(a0, 3);
    v1 = 0x7C0000;
    v0 = addu(v0, a0);
    t2 = addiu(v1, 28144);  // "Unknown"
    v0 = sll(v0, 3);
    t1 = 0;
    a0 = 0x9A0000;
    a0 = addiu(a0, -25056);  // &0x999E20
    a0 = addu(a0, v0);
    lw(v1, a0, 0);
    t0 = a0;
    if (v1 != 0) {
        // 0x00564e90
        charge(ctx, 2);
        t1 = addiu(t1, 1);
        for (;;) {
            // 0x00564e98
            charge(ctx, 4);
            a0 = addiu(a0, 12);
            v0 = slti(t1, 6);
            t0 = a0;
            if (v0 == 0) {
                break;
            }
            // 0x00564ea8
            charge(ctx, 5);
            lw(v0, a0, 0);
            if (v0 == 0) {
                goto L_00564ebc;
            }
            t1 = addiu(t1, 1);
            backedge(ctx);
        }
        goto L_00564ecc;
    }
L_00564ebc:
    charge(ctx, 3);
    sw(a1, a0, 0);
    sw(a2, a0, 4);
    if (a3 != 0) {
        backedge(ctx);
        // 0x00564e58
        charge(ctx, 2);
        sw(a3, t0, 8);
    } else {
        // 0x00564ec8
        charge(ctx, 1);
        sw(t2, a0, 8);
    }
L_00564ecc:
    charge(ctx, 3);
    v0 = 6;
    if (t1 != v0) {
        v0 = t1;
    } else {
        // 0x00564ed8
        charge(ctx, 2);
        a0 = 0x7C0000;
        a0 = addiu(a0, 28152);  // "1051001:SVM_SetCbSvr:too many server function"
    L_00564ee0:
        charge(ctx, 3);
        jal(ctx, 0x564EE0u, gen::fn_sub_564B50_00564b50);
        v0 = si(-1);
    }
    // 0x00564eec (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00564F38 sub_564F38 -- 148 bytes; frame 0x10: ra sp+0x0
// Unregister a server slot: clear {function, object, name} of (type, id); id >= 6 or type >= 8 is reported
//   ('1051002:SVM_DelCbSvr:illegal id', '1071206:SVM_SetCbSvrId:illegal svtype'). [svm_DelCbSvr]
void sub_564F38(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x00564f38
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a2 = a0;
    v0 = sltiu(a1, 6);
    sd(ra, sp, 0x0);
    v1 = sltiu(a2, 8);
    if (v0 == 0) {
        // 0x00564f50
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 28200);  // "1051002:SVM_DelCbSvr:illegal id"
        sp = addiu(sp, 0x10);
        gen::fn_sub_564B50_00564b50(ctx);  // tail call
        return;
    }
    // 0x00564f68
    charge(ctx, 2);
    cc = v1 != 0;  // the condition, before the delay slot changes it
    v1 = sll(a1, 1);
    if (!cc) {
        // 0x00564f70
        charge(ctx, 5);
        a0 = 0x7C0000;
        ld(ra, sp, 0x0);
        a0 = addiu(a0, 28232);  // "1071206:SVM_SetCbSvrId:illegal svtype"
        sp = addiu(sp, 0x10);
        gen::fn_sub_564B50_00564b50(ctx);  // tail call
        return;
    }
    // 0x00564f88
    charge(ctx, 17);
    a0 = sll(a2, 3);
    v1 = addu(v1, a1);
    a0 = addu(a0, a2);
    a0 = sll(a0, 3);
    v1 = sll(v1, 2);
    v0 = 0x9A0000;
    v1 = addu(v1, a0);
    v0 = addiu(v0, -25056);  // &0x999E20
    ld(ra, sp, 0x0);
    a1 = addu(v0, v1);
    a0 = addu(v1, v0);
    v0 = a1;
    sw(zero, a0, 0);
    sw(zero, v0, 4);
    sw(zero, a1, 8);
    sp = addiu(sp, 0x10);
}

// 0x00564FD0 sub_564FD0 -- 24 bytes; frame 0x10: ra sp+0x0
// Set a server slot with no name: SVM_SetCbSvrId(type, id, function, object, 0). [svm_SetCbSvrIdNoName]
void sub_564FD0(EEContext& ctx) {
    using namespace hg;
    Gpr t0{ctx, 8}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00564fd0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    t0 = 0;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_564FE8_00564fe8(ctx);  // tail call
}

// 0x00565058 sub_565058 -- 256 bytes; frame 0x30: s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s0 sp+0x0, ra sp+0x20
// Set server slot (type, id) to {function, object, name}: id >= 6 / type >= 8 are reported and nothing is stored; an
//   occupied slot is reported ('2100801:SVM_SetCbSvrId:over write callback function.') and still overwritten; the
//   name defaults to "Unknown" (named by its error texts). [svm_SetCbSvrId]
void sub_565058(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00565058
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    v0 = sltiu(a1, 6);
    sd(s1, sp, 0x8);
    s1 = t0;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s0, sp, 0x0);
    v1 = sltiu(a0, 8);
    sd(ra, sp, 0x20);
    if (v0 == 0) {
        // 0x00565088
        charge(ctx, 9);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 28272);  // "1071201:SVM_SetCbSvrId:illegal id"
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_564B50_00564b50(ctx);  // tail call
        return;
    }
    // 0x005650b0
    charge(ctx, 2);
    v0 = sll(a0, 3);
    if (v1 == 0) {
        // 0x005650b8
        charge(ctx, 9);
        a0 = 0x7C0000;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        a0 = addiu(a0, 28312);  // "1071202:SVM_SetCbSvrId:illegal svtype"
        ld(s2, sp, 0x10);
        ld(s3, sp, 0x18);
        ld(ra, sp, 0x20);
        sp = addiu(sp, 0x30);
        gen::fn_sub_564B50_00564b50(ctx);  // tail call
        return;
    }
    // 0x005650e0
    charge(ctx, 12);
    v1 = sll(a1, 1);
    v0 = addu(v0, a0);
    v1 = addu(v1, a1);
    v1 = sll(v1, 2);
    v0 = sll(v0, 3);
    v0 = addu(v0, v1);
    s0 = 0x9A0000;
    s0 = addiu(s0, -25056);  // &0x999E20
    s0 = addu(s0, v0);
    lw(v1, s0, 0);
    if (v1 == 0) {
        sw(s2, s0, 0);
    } else {
        // 0x00565110
        charge(ctx, 4);
        a0 = 0x7C0000;
        a0 = addiu(a0, 28352);  // "2100801:SVM_SetCbSvrId:over write callback function."
        jal(ctx, 0x565114u, gen::fn_sub_564B50_00564b50);
        sw(s2, s0, 0);
    }
    // 0x00565120
    charge(ctx, 2);
    sw(s3, s0, 4);
    if (s1 == 0) {
        // 0x00565130
        charge(ctx, 3);
        v0 = 0x7C0000;
        v0 = addiu(v0, 28144);  // "Unknown"
        sw(v0, s0, 8);
    } else {
        // 0x00565128
        charge(ctx, 2);
        sw(s1, s0, 8);
    }
    // 0x0056513c (the shared epilogue, written out on this path)
    charge(ctx, 7);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x00565158 sub_565158 -- 88 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Set the per-thread callback {function, object} of slot n in the table 0x99A060 (locked, type 1); the ADXM thread
//   setup installs them. [svm_SetThrdCb]
void sub_565158(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00565158
    enter(ctx, 22);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    sd(ra, sp, 0x18);
    s2 = a2;
    jal(ctx, 0x565174u, gen::fn_sub_564978_00564978);
    v0 = 0x9A0000;
    s0 = sll(s0, 3);
    v0 = addiu(v0, -24480);  // &0x99A060
    ld(ra, sp, 0x18);
    v1 = addu(v0, s0);
    s0 = addu(s0, v0);
    sw(s1, s0, 0);
    sw(s2, v1, 4);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    sp = addiu(sp, 0x20);
    gen::fn_sub_564990_00564990(ctx);  // tail call
}

// 0x005651B0 sub_5651B0 -- 60 bytes; frame 0x10: ra sp+0x0
// Call the per-thread callback of slot n (0x99A060) with its object, when set. [svm_CallThrdCb]
void sub_5651B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x005651b0
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x9A0000;
    v0 = addiu(v0, -24480);  // &0x99A060
    a0 = sll(a0, 3);
    sd(ra, sp, 0x0);
    v1 = addu(v0, a0);
    a0 = addu(a0, v0);
    lw(v0, a0, 0);
    if (v0 == 0) {
        ld(ra, sp, 0x0);
    } else {
        // 0x005651d8
        charge(ctx, 3);
        jt = v0.u();  // the target, read before the delay slot
        link(ctx, 0x5651D8u);  // $ra = the return address
        lw(a0, v1, 4);
        call_ptr(ctx, jt);
        ld(ra, sp, 0x0);
    }
    // 0x005651e4 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x005651F0 sub_5651F0 -- 64 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, ra sp+0x10
// Set the error callback {function, object} (0x99A0B0 / 0x99A0B4; locked, type 1). [svm_SetErrCb]
void sub_5651F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005651f0
    enter(ctx, 16);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    sd(ra, sp, 0x10);
    s1 = a0;
    jal(ctx, 0x565204u, gen::fn_sub_564978_00564978);
    v0 = 0x9A0000;
    ld(ra, sp, 0x10);
    v0 = addiu(v0, -24400);  // &0x99A0B0
    sw(s0, v0, 4);  // 0x99A0B4
    sw(s1, v0, 0);  // 0x99A0B0
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    sp = addiu(sp, 0x20);
    gen::fn_sub_564990_00564990(ctx);  // tail call
}

// 0x00565230 sub_565230 -- 20 bytes; leaf frame (no stack)
// Set the lock callback {function, object} (0x99A0A0 / 0x99A0A4). [svm_SetLockCb]
void sub_565230(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00565230
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x9A0000;
    v0 = addiu(v0, -24416);  // &0x99A0A0
    sw(a1, v0, 4);  // 0x99A0A4
    sw(a0, v0, 0);  // 0x99A0A0
}

// 0x00565248 sub_565248 -- 20 bytes; leaf frame (no stack)
// Set the unlock callback {function, object} (0x99A0A8 / 0x99A0AC). [svm_SetUnlockCb]
void sub_565248(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00565248
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x9A0000;
    v0 = addiu(v0, -24408);  // &0x99A0A8
    sw(a1, v0, 4);  // 0x99A0AC
    sw(a0, v0, 0);  // 0x99A0A8
}

// 0x00565328 sub_565328 -- 148 bytes; frame 0x10: ra sp+0x0
// Execute one server slot (type, id): its function with its object; 0 when empty or out of range (reported:
//   '1071301:SVM_ExecSvrFuncId:illegal id', '1071302:...illegal svtype'). [SVM_ExecSvrFuncId]
void sub_565328(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x00565328
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = sltiu(a1, 6);
    sd(ra, sp, 0x0);
    v1 = sltiu(a0, 8);
    a2 = 0;
    if (v0 == 0) {
        // 0x00565340
        charge(ctx, 3);
        a0 = 0x7C0000;
        a0 = addiu(a0, 28408);  // "1071301:SVM_ExecSvrFuncId:illegal id"
        goto L_00565360;
    }
    // 0x00565350
    charge(ctx, 2);
    if (v1 != 0) {
        v0 = sll(a0, 3);
        // 0x00565370
        charge(ctx, 12);
        v1 = sll(a1, 1);
        v0 = addu(v0, a0);
        v1 = addu(v1, a1);
        v1 = sll(v1, 2);
        v0 = sll(v0, 3);
        v0 = addu(v0, v1);
        at = 0x9A0000;
        at = addiu(at, -25056);  // &0x999E20
        v0 = addu(at, v0);
        lw(v1, v0, 0);
        if (v1 == 0) {
            v0 = a2;
        } else {
            // 0x005653a0
            charge(ctx, 4);
            jt = v1.u();  // the target, read before the delay slot
            link(ctx, 0x5653A0u);  // $ra = the return address
            lw(a0, v0, 4);
            call_ptr(ctx, jt);
            a2 = v0;
            v0 = a2;
        }
    } else {
        // 0x00565358
        charge(ctx, 2);
        a0 = 0x7C0000;
        a0 = addiu(a0, 28448);  // "1071302:SVM_ExecSvrFuncId:illegal svtype"
    L_00565360:
        charge(ctx, 4);
        jal(ctx, 0x565360u, gen::fn_sub_564B50_00564b50);
        v0 = 0;
    }
    // 0x005653b0 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x005653C0 sub_5653C0 -- 220 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Execute server type 0: every set slot of the 6 in order, with the type's 'executing' flag (0x7B2658 + 4 x type) set
//   around each call; returns the OR of the results and counts the execution (0x7B2638 + 4 x type). Shares its body
//   (0x565260) with the other seven types. [svm_ExecSvrType0]
void sub_5653C0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005653c0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00565260
    charge(ctx, 22);
    v0 = sll(a0, 3);
    sp = addiu(sp, -0x40);
    v0 = addu(v0, a0);
    sd(s4, sp, 0x20);
    v0 = sll(v0, 3);
    sd(ra, sp, 0x30);
    s4 = sll(a0, 2);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = 0x7B0000;
    s1 = addiu(s1, 9816);  // &0x7B2658
    s1 = addu(s1, s4);
    sd(s2, sp, 0x10);
    s2 = 5;
    sd(s3, sp, 0x18);
    s3 = 0;
    sd(s5, sp, 0x28);
    s5 = 1;
    s0 = 0x9A0000;
    s0 = addiu(s0, -25056);  // &0x999E20
    s0 = addu(s0, v0);
    lw(v0, s0, 0);
    for (;;) {
        // 0x005652b8
        charge(ctx, 3);
        lw(a0, s0, 4);
        s0 = addiu(s0, 12);
        if (v0 != 0) {
            // 0x005652c4
            charge(ctx, 5);
            sw(s5, s1, 0);
            jalr(ctx, 0x5652C8u, v0.u());
            sw(zero, s1, 0);
            s3 = s3 | v0;
        }
        // 0x005652d8
        charge(ctx, 3);
        s2 = addiu(s2, -1);
        if (i64(s2) < 0) {
            break;
        }
        lw(v0, s0, 0);
        backedge(ctx);
    }
    // 0x005652e4
    charge(ctx, 16);
    a0 = 0x7B0000;
    a0 = addiu(a0, 9784);  // &0x7B2638
    a0 = addu(a0, s4);
    ld(s4, sp, 0x20);
    lw(v1, a0, 0);
    v0 = s3;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    v1 = addiu(v1, 1);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sw(v1, a0, 0);
    sp = addiu(sp, 0x40);
}

// 0x005653D8 sub_5653D8 -- 220 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Execute server type 1 (see type 0). [svm_ExecSvrType1]
void sub_5653D8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005653d8
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 1;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00565260
    charge(ctx, 22);
    v0 = sll(a0, 3);
    sp = addiu(sp, -0x40);
    v0 = addu(v0, a0);
    sd(s4, sp, 0x20);
    v0 = sll(v0, 3);
    sd(ra, sp, 0x30);
    s4 = sll(a0, 2);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = 0x7B0000;
    s1 = addiu(s1, 9816);  // &0x7B2658
    s1 = addu(s1, s4);
    sd(s2, sp, 0x10);
    s2 = 5;
    sd(s3, sp, 0x18);
    s3 = 0;
    sd(s5, sp, 0x28);
    s5 = 1;
    s0 = 0x9A0000;
    s0 = addiu(s0, -25056);  // &0x999E20
    s0 = addu(s0, v0);
    lw(v0, s0, 0);
    for (;;) {
        // 0x005652b8
        charge(ctx, 3);
        lw(a0, s0, 4);
        s0 = addiu(s0, 12);
        if (v0 != 0) {
            // 0x005652c4
            charge(ctx, 5);
            sw(s5, s1, 0);
            jalr(ctx, 0x5652C8u, v0.u());
            sw(zero, s1, 0);
            s3 = s3 | v0;
        }
        // 0x005652d8
        charge(ctx, 3);
        s2 = addiu(s2, -1);
        if (i64(s2) < 0) {
            break;
        }
        lw(v0, s0, 0);
        backedge(ctx);
    }
    // 0x005652e4
    charge(ctx, 16);
    a0 = 0x7B0000;
    a0 = addiu(a0, 9784);  // &0x7B2638
    a0 = addu(a0, s4);
    ld(s4, sp, 0x20);
    lw(v1, a0, 0);
    v0 = s3;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    v1 = addiu(v1, 1);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sw(v1, a0, 0);
    sp = addiu(sp, 0x40);
}

// 0x005653F0 sub_5653F0 -- 220 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Execute server type 2 (see type 0); adxm_vsync_proc runs it. [svm_ExecSvrType2]
void sub_5653F0(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005653f0
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 2;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00565260
    charge(ctx, 22);
    v0 = sll(a0, 3);
    sp = addiu(sp, -0x40);
    v0 = addu(v0, a0);
    sd(s4, sp, 0x20);
    v0 = sll(v0, 3);
    sd(ra, sp, 0x30);
    s4 = sll(a0, 2);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = 0x7B0000;
    s1 = addiu(s1, 9816);  // &0x7B2658
    s1 = addu(s1, s4);
    sd(s2, sp, 0x10);
    s2 = 5;
    sd(s3, sp, 0x18);
    s3 = 0;
    sd(s5, sp, 0x28);
    s5 = 1;
    s0 = 0x9A0000;
    s0 = addiu(s0, -25056);  // &0x999E20
    s0 = addu(s0, v0);
    lw(v0, s0, 0);
    for (;;) {
        // 0x005652b8
        charge(ctx, 3);
        lw(a0, s0, 4);
        s0 = addiu(s0, 12);
        if (v0 != 0) {
            // 0x005652c4
            charge(ctx, 5);
            sw(s5, s1, 0);
            jalr(ctx, 0x5652C8u, v0.u());
            sw(zero, s1, 0);
            s3 = s3 | v0;
        }
        // 0x005652d8
        charge(ctx, 3);
        s2 = addiu(s2, -1);
        if (i64(s2) < 0) {
            break;
        }
        lw(v0, s0, 0);
        backedge(ctx);
    }
    // 0x005652e4
    charge(ctx, 16);
    a0 = 0x7B0000;
    a0 = addiu(a0, 9784);  // &0x7B2638
    a0 = addu(a0, s4);
    ld(s4, sp, 0x20);
    lw(v1, a0, 0);
    v0 = s3;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    v1 = addiu(v1, 1);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sw(v1, a0, 0);
    sp = addiu(sp, 0x40);
}

// 0x00565408 sub_565408 -- 220 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Execute server type 3 (see type 0). [svm_ExecSvrType3]
void sub_565408(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00565408
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 3;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00565260
    charge(ctx, 22);
    v0 = sll(a0, 3);
    sp = addiu(sp, -0x40);
    v0 = addu(v0, a0);
    sd(s4, sp, 0x20);
    v0 = sll(v0, 3);
    sd(ra, sp, 0x30);
    s4 = sll(a0, 2);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = 0x7B0000;
    s1 = addiu(s1, 9816);  // &0x7B2658
    s1 = addu(s1, s4);
    sd(s2, sp, 0x10);
    s2 = 5;
    sd(s3, sp, 0x18);
    s3 = 0;
    sd(s5, sp, 0x28);
    s5 = 1;
    s0 = 0x9A0000;
    s0 = addiu(s0, -25056);  // &0x999E20
    s0 = addu(s0, v0);
    lw(v0, s0, 0);
    for (;;) {
        // 0x005652b8
        charge(ctx, 3);
        lw(a0, s0, 4);
        s0 = addiu(s0, 12);
        if (v0 != 0) {
            // 0x005652c4
            charge(ctx, 5);
            sw(s5, s1, 0);
            jalr(ctx, 0x5652C8u, v0.u());
            sw(zero, s1, 0);
            s3 = s3 | v0;
        }
        // 0x005652d8
        charge(ctx, 3);
        s2 = addiu(s2, -1);
        if (i64(s2) < 0) {
            break;
        }
        lw(v0, s0, 0);
        backedge(ctx);
    }
    // 0x005652e4
    charge(ctx, 16);
    a0 = 0x7B0000;
    a0 = addiu(a0, 9784);  // &0x7B2638
    a0 = addu(a0, s4);
    ld(s4, sp, 0x20);
    lw(v1, a0, 0);
    v0 = s3;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    v1 = addiu(v1, 1);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sw(v1, a0, 0);
    sp = addiu(sp, 0x40);
}

// 0x00565420 SVM_ExecSvrFs -- 220 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Execute server type 4, the file-system servers (see type 0); adxm_fs_proc runs it. [SVM_ExecSvrFs]
void SVM_ExecSvrFs(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00565420
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 4;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00565260
    charge(ctx, 22);
    v0 = sll(a0, 3);
    sp = addiu(sp, -0x40);
    v0 = addu(v0, a0);
    sd(s4, sp, 0x20);
    v0 = sll(v0, 3);
    sd(ra, sp, 0x30);
    s4 = sll(a0, 2);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = 0x7B0000;
    s1 = addiu(s1, 9816);  // &0x7B2658
    s1 = addu(s1, s4);
    sd(s2, sp, 0x10);
    s2 = 5;
    sd(s3, sp, 0x18);
    s3 = 0;
    sd(s5, sp, 0x28);
    s5 = 1;
    s0 = 0x9A0000;
    s0 = addiu(s0, -25056);  // &0x999E20
    s0 = addu(s0, v0);
    lw(v0, s0, 0);
    for (;;) {
        // 0x005652b8
        charge(ctx, 3);
        lw(a0, s0, 4);
        s0 = addiu(s0, 12);
        if (v0 != 0) {
            // 0x005652c4
            charge(ctx, 5);
            sw(s5, s1, 0);
            jalr(ctx, 0x5652C8u, v0.u());
            sw(zero, s1, 0);
            s3 = s3 | v0;
        }
        // 0x005652d8
        charge(ctx, 3);
        s2 = addiu(s2, -1);
        if (i64(s2) < 0) {
            break;
        }
        lw(v0, s0, 0);
        backedge(ctx);
    }
    // 0x005652e4
    charge(ctx, 16);
    a0 = 0x7B0000;
    a0 = addiu(a0, 9784);  // &0x7B2638
    a0 = addu(a0, s4);
    ld(s4, sp, 0x20);
    lw(v1, a0, 0);
    v0 = s3;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    v1 = addiu(v1, 1);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sw(v1, a0, 0);
    sp = addiu(sp, 0x40);
}

// 0x00565438 sub_565438 -- 220 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Execute server type 5 (see type 0). [svm_ExecSvrType5]
void sub_565438(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00565438
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 5;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00565260
    charge(ctx, 22);
    v0 = sll(a0, 3);
    sp = addiu(sp, -0x40);
    v0 = addu(v0, a0);
    sd(s4, sp, 0x20);
    v0 = sll(v0, 3);
    sd(ra, sp, 0x30);
    s4 = sll(a0, 2);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = 0x7B0000;
    s1 = addiu(s1, 9816);  // &0x7B2658
    s1 = addu(s1, s4);
    sd(s2, sp, 0x10);
    s2 = 5;
    sd(s3, sp, 0x18);
    s3 = 0;
    sd(s5, sp, 0x28);
    s5 = 1;
    s0 = 0x9A0000;
    s0 = addiu(s0, -25056);  // &0x999E20
    s0 = addu(s0, v0);
    lw(v0, s0, 0);
    for (;;) {
        // 0x005652b8
        charge(ctx, 3);
        lw(a0, s0, 4);
        s0 = addiu(s0, 12);
        if (v0 != 0) {
            // 0x005652c4
            charge(ctx, 5);
            sw(s5, s1, 0);
            jalr(ctx, 0x5652C8u, v0.u());
            sw(zero, s1, 0);
            s3 = s3 | v0;
        }
        // 0x005652d8
        charge(ctx, 3);
        s2 = addiu(s2, -1);
        if (i64(s2) < 0) {
            break;
        }
        lw(v0, s0, 0);
        backedge(ctx);
    }
    // 0x005652e4
    charge(ctx, 16);
    a0 = 0x7B0000;
    a0 = addiu(a0, 9784);  // &0x7B2638
    a0 = addu(a0, s4);
    ld(s4, sp, 0x20);
    lw(v1, a0, 0);
    v0 = s3;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    v1 = addiu(v1, 1);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sw(v1, a0, 0);
    sp = addiu(sp, 0x40);
}

// 0x00565450 sub_565450 -- 220 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Execute server type 6 (see type 0); adxm_mwidle_proc runs it. [svm_ExecSvrType6]
void sub_565450(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00565450
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 6;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00565260
    charge(ctx, 22);
    v0 = sll(a0, 3);
    sp = addiu(sp, -0x40);
    v0 = addu(v0, a0);
    sd(s4, sp, 0x20);
    v0 = sll(v0, 3);
    sd(ra, sp, 0x30);
    s4 = sll(a0, 2);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = 0x7B0000;
    s1 = addiu(s1, 9816);  // &0x7B2658
    s1 = addu(s1, s4);
    sd(s2, sp, 0x10);
    s2 = 5;
    sd(s3, sp, 0x18);
    s3 = 0;
    sd(s5, sp, 0x28);
    s5 = 1;
    s0 = 0x9A0000;
    s0 = addiu(s0, -25056);  // &0x999E20
    s0 = addu(s0, v0);
    lw(v0, s0, 0);
    for (;;) {
        // 0x005652b8
        charge(ctx, 3);
        lw(a0, s0, 4);
        s0 = addiu(s0, 12);
        if (v0 != 0) {
            // 0x005652c4
            charge(ctx, 5);
            sw(s5, s1, 0);
            jalr(ctx, 0x5652C8u, v0.u());
            sw(zero, s1, 0);
            s3 = s3 | v0;
        }
        // 0x005652d8
        charge(ctx, 3);
        s2 = addiu(s2, -1);
        if (i64(s2) < 0) {
            break;
        }
        lw(v0, s0, 0);
        backedge(ctx);
    }
    // 0x005652e4
    charge(ctx, 16);
    a0 = 0x7B0000;
    a0 = addiu(a0, 9784);  // &0x7B2638
    a0 = addu(a0, s4);
    ld(s4, sp, 0x20);
    lw(v1, a0, 0);
    v0 = s3;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    v1 = addiu(v1, 1);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sw(v1, a0, 0);
    sp = addiu(sp, 0x40);
}

// 0x00565468 sub_565468 -- 220 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Execute server type 7 (see type 0). [svm_ExecSvrType7]
void sub_565468(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00565468
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 7;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00565260
    charge(ctx, 22);
    v0 = sll(a0, 3);
    sp = addiu(sp, -0x40);
    v0 = addu(v0, a0);
    sd(s4, sp, 0x20);
    v0 = sll(v0, 3);
    sd(ra, sp, 0x30);
    s4 = sll(a0, 2);
    sd(s0, sp, 0x0);
    sd(s1, sp, 0x8);
    s1 = 0x7B0000;
    s1 = addiu(s1, 9816);  // &0x7B2658
    s1 = addu(s1, s4);
    sd(s2, sp, 0x10);
    s2 = 5;
    sd(s3, sp, 0x18);
    s3 = 0;
    sd(s5, sp, 0x28);
    s5 = 1;
    s0 = 0x9A0000;
    s0 = addiu(s0, -25056);  // &0x999E20
    s0 = addu(s0, v0);
    lw(v0, s0, 0);
    for (;;) {
        // 0x005652b8
        charge(ctx, 3);
        lw(a0, s0, 4);
        s0 = addiu(s0, 12);
        if (v0 != 0) {
            // 0x005652c4
            charge(ctx, 5);
            sw(s5, s1, 0);
            jalr(ctx, 0x5652C8u, v0.u());
            sw(zero, s1, 0);
            s3 = s3 | v0;
        }
        // 0x005652d8
        charge(ctx, 3);
        s2 = addiu(s2, -1);
        if (i64(s2) < 0) {
            break;
        }
        lw(v0, s0, 0);
        backedge(ctx);
    }
    // 0x005652e4
    charge(ctx, 16);
    a0 = 0x7B0000;
    a0 = addiu(a0, 9784);  // &0x7B2638
    a0 = addu(a0, s4);
    ld(s4, sp, 0x20);
    lw(v1, a0, 0);
    v0 = s3;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    v1 = addiu(v1, 1);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s5, sp, 0x28);
    ld(ra, sp, 0x30);
    sw(v1, a0, 0);
    sp = addiu(sp, 0x40);
}

// 0x00565480 sub_565480 -- 40 bytes; leaf frame (no stack)
// Execution count of server type n (0x7B2638 + 4n) for n < 7, else 0. [svm_GetExecCount]
void sub_565480(EEContext& ctx) {
    using namespace hg;
    Gpr at{ctx, 1}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x00565480
    enter(ctx, 7);  // entry check point + this block's cycles
    v1 = sll(a0, 2);
    a0 = sltiu(a0, 7);
    at = 0x7B0000;
    at = addiu(at, 9784);  // &0x7B2638
    v1 = addu(at, v1);
    v0 = 0;
    if (a0 != 0) {
        // 0x0056549c
        charge(ctx, 1);
        lw(v0, v1, 0);
    }
    // 0x005654a0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x005654A8 sub_5654A8 -- 168 bytes; frame 0x10: ra sp+0x0
// SVM reset: the 8 'executing' flags (0x7B2658), the lock / unlock callbacks and the two at 0x99A0C0 / 0x99A0C8
//   (0x99A0A0, 0x99A0A8, 0x99A0C0, 0x99A0C8), six execution counters (0x7B2638..0x7B264C) and the test-and-set hook
//   (0x99A0B8) cleared. [svm_Reset]
void sub_5654A8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005654a8
    enter(ctx, 30);  // entry check point + this block's cycles
    a0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    a1 = 0;
    a0 = addiu(a0, 9816);  // &0x7B2658
    sd(ra, sp, 0x0);
    a2 = 32;
    jal(ctx, 0x5654BCu, gen::fn_memset_00521408);
    a0 = 0x9A0000;
    a0 = addiu(a0, -24416);  // &0x99A0A0
    a1 = 0;
    a2 = 8;
    jal(ctx, 0x5654D0u, gen::fn_memset_00521408);
    a0 = 0x9A0000;
    a0 = addiu(a0, -24408);  // &0x99A0A8
    a1 = 0;
    a2 = 8;
    jal(ctx, 0x5654E4u, gen::fn_memset_00521408);
    a0 = 0x9A0000;
    a0 = addiu(a0, -24384);  // &0x99A0C0
    a1 = 0;
    a2 = 8;
    jal(ctx, 0x5654F8u, gen::fn_memset_00521408);
    a0 = 0x9A0000;
    a0 = addiu(a0, -24376);  // &0x99A0C8
    a1 = 0;
    a2 = 8;
    jal(ctx, 0x56550Cu, gen::fn_memset_00521408);
    v1 = 0x7B0000;
    v1 = addiu(v1, 9784);  // &0x7B2638
    v0 = 5;
    for (;;) {
        // 0x00565520
        charge(ctx, 7);
        v0 = addiu(v0, -1);
        sw(zero, v1, 0);
        v1 = addiu(v1, 4);
        if (i64(v0) < 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0056553c
    charge(ctx, 5);
    ld(ra, sp, 0x0);
    v0 = 0x9A0000;
    sw(zero, v0, -24392);  // 0x99A0B8
    sp = addiu(sp, 0x10);
}

// 0x00565550 sub_565550 -- 64 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// SVM init (counted): the first call resets; returns the new count (0x7B262C). [svm_Init]
void sub_565550(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00565550
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x7B0000;
    sd(s0, sp, 0x0);
    s0 = addiu(v0, 9772);  // &0x7B262C
    lw(v1, s0, 0);  // 0x7B262C
    sd(ra, sp, 0x8);
    if (v1 == 0) {
        // 0x0056556c
        charge(ctx, 2);
        jal(ctx, 0x56556Cu, gen::fn_sub_5654A8_005654a8);
    }
    // 0x00565574 (the shared epilogue, written out on this path)
    charge(ctx, 7);
    lw(v0, s0, 0);
    ld(ra, sp, 0x8);
    v0 = addiu(v0, 1);
    sw(v0, s0, 0);
    ld(s0, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x00565590 sub_565590 -- 88 bytes; frame 0x10: ra sp+0x0
// SVM finish (counted): the last call resets and clears the error callback. [svm_Finish]
void sub_565590(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00565590
    enter(ctx, 10);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x7B0000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, 9772);  // &0x7B262C
    lw(v1, v0, 0);  // 0x7B262C
    v1 = addiu(v1, -1);
    sw(v1, v0, 0);  // 0x7B262C
    lw(a0, v0, 0);  // 0x7B262C
    ld(ra, sp, 0x0);
    if (a0 != 0) {
        // 0x005655e0
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x005655b8
    charge(ctx, 9);
    jal(ctx, 0x5655B8u, gen::fn_sub_5654A8_005654a8);
    a0 = 0x9A0000;
    ld(ra, sp, 0x0);
    a0 = addiu(a0, -24400);  // &0x99A0B0
    a1 = 0;
    a2 = 8;
    sp = addiu(sp, 0x10);
    gen::fn_memset_00521408(ctx);  // tail call
}

// 0x005655E8 sub_5655E8 -- 100 bytes; frame 0x10: s0 sp+0x0, ra sp+0x8
// Test-and-set: through the hook 0x99A0B8 when one is set, else (locked, type 1) set *flag = 1 and return whether it
//   was not 1 before. [svm_TestAndSet]
void sub_5655E8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    // 0x005655e8
    enter(ctx, 7);  // entry check point + this block's cycles
    v0 = 0x9A0000;
    sp = addiu(sp, -0x10);
    lw(v0, v0, -24392);  // 0x99A0B8
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(ra, sp, 0x8);
    if (v0 == 0) {
        // 0x00565618
        charge(ctx, 8);
        jal(ctx, 0x565618u, gen::fn_sub_564978_00564978);
        v1 = 1;
        lw(v0, s0, 0);
        sw(v1, s0, 0);
        v0 = v0 ^ 0x1;
        s0 = sltu(0, v0);
        jal(ctx, 0x565630u, gen::fn_sub_564990_00564990);
    } else {
        // 0x00565604
        charge(ctx, 4);
        jalr(ctx, 0x565604u, v0.u());
        s0 = v0;
    }
    // 0x00565638 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    v0 = s0;
    ld(s0, sp, 0x0);
    ld(ra, sp, 0x8);
    sp = addiu(sp, 0x10);
}

// 0x00565678 sub_565678 -- 60 bytes, 2 chunks; frame 0x10: ra sp+0x0
// Clear the test-and-set hook when none is set (returns 1), else 0 -- as compiled, a set hook is never cleared.
//   [svm_ClrTestAndSetHook]
void sub_565678(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x00565678
    enter(ctx, 6);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    a0 = 0;
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x00565650
    charge(ctx, 5);
    v0 = 0x9A0000;
    a1 = addiu(v0, -24392);  // &0x99A0B8
    lw(v1, a1, 0);  // 0x99A0B8
    v0 = 0;
    if (v1 == 0) {
        // 0x00565664
        charge(ctx, 2);
        sw(a0, a1, 0);
        v0 = 1;
    }
    // 0x0056566c (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x00565690 sub_565690 -- 20 bytes; leaf frame (no stack)
// Set the callback {function, object} (0x99A0C0 / 0x99A0C4). [svm_SetCbC0]
void sub_565690(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5};
    // 0x00565690
    enter(ctx, 5);  // entry check point + this block's cycles
    v0 = 0x9A0000;
    v0 = addiu(v0, -24384);  // &0x99A0C0
    sw(a1, v0, 4);  // 0x99A0C4
    sw(a0, v0, 0);  // 0x99A0C0
}

// 0x005656C0 sub_5656C0 -- 48 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x99A0C0 with its object, when set. [svm_CallCbC0]
void sub_5656C0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x005656c0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x9A0000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, -24384);  // &0x99A0C0
    lw(v1, v0, 0);  // 0x99A0C0
    if (v1 == 0) {
        ld(ra, sp, 0x0);
    } else {
        // 0x005656dc
        charge(ctx, 3);
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x5656DCu);  // $ra = the return address
        lw(a0, v0, 4);
        call_ptr(ctx, jt);
        ld(ra, sp, 0x0);
    }
    // 0x005656e8 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

// 0x005656F0 sub_5656F0 -- 48 bytes; frame 0x10: ra sp+0x0
// Call the callback 0x99A0C8 with its object, when set. [svm_CallCbC8]
void sub_5656F0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x005656f0
    enter(ctx, 7);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = 0x9A0000;
    sd(ra, sp, 0x0);
    v0 = addiu(v0, -24376);  // &0x99A0C8
    lw(v1, v0, 0);  // 0x99A0C8
    if (v1 == 0) {
        ld(ra, sp, 0x0);
    } else {
        // 0x0056570c
        charge(ctx, 3);
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x56570Cu);  // $ra = the return address
        lw(a0, v0, 4);
        call_ptr(ctx, jt);
        ld(ra, sp, 0x0);
    }
    // 0x00565718 (the shared epilogue, written out on this path)
    charge(ctx, 2);
    sp = addiu(sp, 0x10);
}

}  // namespace p3fes::game
