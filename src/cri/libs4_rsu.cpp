// Phase 5 slice libs4: CRI RSU, the CVM descrambler: the CRC-style hash tables, the fixed-key generators (from a CVM
// header or a password), the per-sector key schedule and the eight byte-permutation rounds, the decipher entry
// points (0x56CDF0-0x56DCE8).
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

// 0x0056CDF0 sub_56CDF0 -- 8 bytes; leaf frame (no stack)
// RSU: 0 (an unused method). [rsu_Zero]
void sub_56CDF0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0056cdf0
    enter(ctx, 2);  // entry check point + this block's cycles
    v0 = 0;
}

// 0x0056CE10 sub_56CE10 -- 52 bytes; frame 0x10: ra sp+0x0
// Call RSU's error callback (0x7B28E4 / its object 0x7B28E8) with the text, when set; returns 0. [rsu_CallErr]
void sub_56CE10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    u32 jt = 0;    // a jump target read before its delay slot
    // 0x0056ce10
    enter(ctx, 6);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x10);
    lw(v1, v0, 10468);  // 0x7B28E4
    a1 = a0;
    sd(ra, sp, 0x0);
    if (v1 != 0) {
        // 0x0056ce28
        charge(ctx, 3);
        v0 = 0x7B0000;
        jt = v1.u();  // the target, read before the delay slot
        link(ctx, 0x56CE2Cu);  // $ra = the return address
        lw(a0, v0, 10472);
        call_ptr(ctx, jt);
    }
    // 0x0056ce34 (the shared epilogue, written out on this path)
    charge(ctx, 4);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x0056CE48 sub_56CE48 -- 28 bytes; leaf frame (no stack)
// Count RSU's table users (0x7B28E0) up. [rsu_InitTbl]
void sub_56CE48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4};
    // 0x0056ce48
    enter(ctx, 7);  // entry check point + this block's cycles
    a0 = 0x7B0000;
    v0 = 0;
    a0 = addiu(a0, 10464);  // &0x7B28E0
    lw(v1, a0, 0);  // 0x7B28E0
    v1 = addiu(v1, 1);
    sw(v1, a0, 0);  // 0x7B28E0
}

// 0x0056CE88 sub_56CE88 -- 436 bytes; frame 0x30: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, s3 sp+0x18, s4 sp+0x20, ra sp+0x28
// Three 16-bit hashes of a byte string over the 1024 primes at 0x7C11B8: each starts at a seed (prime 256, 512, 768)
//   and steps h = prime[(h x prime[128 + byte]) mod 1024] (signed bytes); 0 and nothing hashed for no string with n
//   <= 0. [rsu_Hash3]
// The 'no string' early out only applies when n <= 0 too: a null string with n > 0 is read.
void sub_56CE88(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056ce88
    enter(ctx, 15);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x30);
    lw(v1, v0, 10464);  // 0x7B28E0
    sd(s0, sp, 0x0);
    s0 = a1;
    sd(s1, sp, 0x8);
    s1 = a0;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(s3, sp, 0x18);
    s3 = a3;
    sd(s4, sp, 0x20);
    s4 = t0;
    sd(ra, sp, 0x28);
    if (v1 == 0) {
        // 0x0056cec4
        charge(ctx, 2);
        jal(ctx, 0x56CEC4u, gen::fn_sub_56CE48_0056ce48);
    }
    // 0x0056cecc
    charge(ctx, 4);
    sh(zero, s2, 0);
    sh(zero, s3, 0);
    sh(zero, s4, 0);
    if (s1 == 0) {
        // 0x0056cedc
        charge(ctx, 2);
        v0 = 0;
        if (i64(s0) > 0) {
            goto L_0056cee4;
        }
        // 0x0056d01c (the shared epilogue, written out on this path)
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
L_0056cee4:
    charge(ctx, 5);
    t3 = 0x7C0000;
    a3 = 0;
    v0 = addiu(t3, 4536);  // &0x7C11B8
    lh(t2, v0, 512);  // 0x7C13B8
    if (i64(s0) > 0) {
        // 0x0056cef8
        charge(ctx, 2);
        t0 = v0;
        for (;;) {
            // 0x0056cf00
            charge(ctx, 19);
            v1 = addu(s1, a3);
            a3 = addiu(a3, 1);
            lb(v0, v1, 0);
            a2 = slt(a3, s0);
            v0 = sll(v0, 1);
            v0 = addu(v0, t0);
            lh(v1, v0, 256);
            mult(v1, t2, v1);
            a1 = addiu(v1, 1023);
            a0 = slti(v1, 0);
            v0 = v1;
            if (a0 != 0) v0 = a1;
            v0 = sra(v0, 10);
            v0 = sll(v0, 10);
            v1 = subu(v1, v0);
            v1 = sll(v1, 1);
            v1 = addu(v1, t0);
            lh(t2, v1, 0);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
        }
        // 0x0056cf4c
        charge(ctx, 2);
        v0 = addiu(t3, 4536);
        a3 = 0;
    }
    // 0x0056cf54
    charge(ctx, 2);
    lh(t0, v0, 1024);
    if (i64(s0) > 0) {
        // 0x0056cf5c
        charge(ctx, 1);
        t1 = v0;
        for (;;) {
            // 0x0056cf60
            charge(ctx, 19);
            v1 = addu(s1, a3);
            a3 = addiu(a3, 1);
            lb(v0, v1, 0);
            a2 = slt(a3, s0);
            v0 = sll(v0, 1);
            v0 = addu(v0, t1);
            lh(v1, v0, 256);
            mult(v1, t0, v1);
            a1 = addiu(v1, 1023);
            a0 = slti(v1, 0);
            v0 = v1;
            if (a0 != 0) v0 = a1;
            v0 = sra(v0, 10);
            v0 = sll(v0, 10);
            v1 = subu(v1, v0);
            v1 = sll(v1, 1);
            v1 = addu(v1, t1);
            lh(t0, v1, 0);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0056cfac
    charge(ctx, 4);
    v0 = addiu(t3, 4536);
    a3 = 0;
    lh(a0, v0, 1536);
    if (i64(s0) > 0) {
        // 0x0056cfbc
        charge(ctx, 1);
        t1 = v0;
        for (;;) {
            // 0x0056cfc0
            charge(ctx, 19);
            v1 = addu(s1, a3);
            a3 = addiu(a3, 1);
            lb(v0, v1, 0);
            a2 = slt(a3, s0);
            v0 = sll(v0, 1);
            v0 = addu(v0, t1);
            lh(v1, v0, 256);
            mult(v1, a0, v1);
            a0 = slti(v1, 0);
            a1 = addiu(v1, 1023);
            v0 = v1;
            if (a0 != 0) v0 = a1;
            v0 = sra(v0, 10);
            v0 = sll(v0, 10);
            v1 = subu(v1, v0);
            v1 = sll(v1, 1);
            v1 = addu(v1, t1);
            lh(a0, v1, 0);
            if (a2 == 0) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0056d00c
    charge(ctx, 4);
    sh(t2, s2, 0);
    v0 = 0;
    sh(t0, s3, 0);
    sh(a0, s4, 0);
    // 0x0056d01c (the shared epilogue, written out on this path)
    charge(ctx, 8);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(s3, sp, 0x18);
    ld(s4, sp, 0x20);
    ld(ra, sp, 0x28);
    sp = addiu(sp, 0x30);
}

// 0x0056D040 sub_56D040 -- 108 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// The three hashes of "CRI-MW". [rsu_HashCriMw]
void sub_56D040(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056d040
    enter(ctx, 11);  // entry check point + this block's cycles
    v0 = 0x7B0000;
    sp = addiu(sp, -0x20);
    lw(v1, v0, 10464);  // 0x7B28E0
    sd(s0, sp, 0x0);
    s0 = a0;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a2;
    sd(ra, sp, 0x18);
    if (v1 == 0) {
        // 0x0056d06c
        charge(ctx, 2);
        jal(ctx, 0x56D06Cu, gen::fn_sub_56CE48_0056ce48);
    }
    // 0x0056d074
    charge(ctx, 14);
    a0 = 0x7C0000;
    a2 = s0;
    a3 = s1;
    t0 = s2;
    a0 = addiu(a0, 30624);  // "CRI-MW"
    a1 = 6;
    jal(ctx, 0x56D088u, gen::fn_sub_56CE88_0056ce88);
    v0 = 0;
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0056D0D0 sub_56D0D0 -- 52 bytes; leaf frame (no stack)
// Store a u16 big-endian (2 bytes). [rsu_PutBe16]
void sub_56D0D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0056d0d0
    enter(ctx, 4);  // entry check point + this block's cycles
    a0 = a0 & 0xFFFF;
    a1 = addiu(a1, 1);
    a2 = 2;
    v1 = 0;
    for (;;) {
        // 0x0056d0e0
        charge(ctx, 7);
        v0 = srav(a0, v1);
        v1 = addiu(v1, 8);
        a2 = addiu(a2, -1);
        sb(v0, a1, 0);
        a1 = addiu(a1, -1);
        if (i64(a2) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0056d0fc
    charge(ctx, 2);
}

// 0x0056D108 sub_56D108 -- 52 bytes; leaf frame (no stack)
// Store a u32 big-endian (4 bytes). [rsu_PutBe32]
void sub_56D108(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0056d108
    enter(ctx, 4);  // entry check point + this block's cycles
    a1 = addiu(a1, 3);
    a2 = 4;
    v1 = 0;
    for (;;) {
        // 0x0056d118
        charge(ctx, 7);
        v0 = srlv(a0, v1);
        v1 = addiu(v1, 8);
        a2 = addiu(a2, -1);
        sb(v0, a1, 0);
        a1 = addiu(a1, -1);
        if (i64(a2) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0056d134
    charge(ctx, 2);
}

// 0x0056D140 sub_56D140 -- 60 bytes; leaf frame (no stack)
// Read a big-endian u32 (the CVM header's flags word) into a word. [rsu_GetBe32]
void sub_56D140(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0056d140
    enter(ctx, 15);  // entry check point + this block's cycles
    lw(a2, a0, 0);
    sw(a2, a1, 0);
    v1 = srl(a2, 8);
    a0 = srl(a2, 8);
    a2 = srl(a2, 24);
    lbu(v0, a1, 0);
    v1 = v1 & 0xFF;
    a0 = a0 & 0xFF00;
    v1 = sll(v1, 16);
    v0 = sll(v0, 24);
    a0 = a0 | v1;
    v0 = v0 | a2;
    v0 = v0 | a0;
    sw(v0, a1, 0);
}

// 0x0056D180 sub_56D180 -- 100 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// Find the scramble key strings of a CVM header: flag 0x10 of the big-endian word at +48 set -> {+37, +32} (two
//   4-byte strings), else none. [rsu_GetKeyStr]
void sub_56D180(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056d180
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    s1 = a1;
    a0 = addiu(s0, 48);
    sd(ra, sp, 0x20);
    a1 = sp;
    jal(ctx, 0x56D19Cu, gen::fn_sub_56D140_0056d140);
    lw(v0, sp, 0x0);
    v1 = addiu(s0, 37);
    v0 = v0 & 0x10;
    s0 = addiu(s0, 32);
    if (v0 == 0) {
        // 0x0056d1c8
        charge(ctx, 2);
        sw(zero, s1, 4);
        sw(zero, s1, 0);
    } else {
        // 0x0056d1b8
        charge(ctx, 3);
        sw(s0, s1, 4);
        sw(v1, s1, 0);
    }
    // 0x0056d1d0 (the shared epilogue, written out on this path)
    charge(ctx, 5);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0056D1E8 sub_56D1E8 -- 96 bytes; leaf frame (no stack)
// Interleave the two key strings into the 8-byte key (pairs of bytes; zeros without them). [rsu_MixKeyStr]
void sub_56D1E8(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0056d1e8
    enter(ctx, 4);  // entry check point + this block's cycles
    lw(v1, a0, 4);
    a2 = 8;
    lw(a0, a0, 0);
    for (;;) {
        // 0x0056d1f8
        charge(ctx, 2);
        if (a0 == 0) {
            sb(zero, a1, 0);
        } else {
            // 0x0056d200
            charge(ctx, 2);
            if (v1 == 0) {
                // 0x0056d208
                charge(ctx, 1);
                sb(zero, a1, 0);
                goto L_0056d20c;
            }
            lbu(v0, a0, 0);
            // 0x0056d218
            charge(ctx, 8);
            a0 = addiu(a0, 1);
            a2 = addiu(a2, -2);
            sb(v0, a1, 0);
            a1 = addiu(a1, 1);
            lbu(v0, v1, 0);
            v1 = addiu(v1, 1);
            sb(v0, a1, 0);
            a1 = addiu(a1, 1);
            goto L_0056d238;
        }
    L_0056d20c:
        charge(ctx, 3);
        a1 = addiu(a1, 1);
        a2 = addiu(a2, -1);
    L_0056d238:
        charge(ctx, 2);
        if (i64(a2) <= 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0056d240
    charge(ctx, 2);
}

// 0x0056D248 sub_56D248 -- 132 bytes; frame 0x40: s0 sp+0x10, ra sp+0x38, s1 sp+0x18, s2 sp+0x20, s3 sp+0x28, s4 sp+0x30
// Hash the 8-byte key in place, 2 bytes at a time (rsu_Hash3's first hash, stored big-endian). [rsu_HashKey]
void sub_56D248(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056d248
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    sd(s0, sp, 0x10);
    sd(ra, sp, 0x38);
    sd(s1, sp, 0x18);
    s1 = 0;
    sd(s2, sp, 0x20);
    s2 = a0;
    sd(s3, sp, 0x28);
    s3 = addiu(sp, 0x4);
    sd(s4, sp, 0x30);
    s4 = addiu(sp, 0x2);
    s0 = addu(s2, s1);
    for (;;) {
        // 0x0056d278
        charge(ctx, 13);
        s1 = addiu(s1, 2);
        a0 = s0;
        a1 = 2;
        a2 = sp;
        a3 = s4;
        t0 = s3;
        jal(ctx, 0x56D28Cu, gen::fn_sub_56CE88_0056ce88);
        a1 = s0;
        link(ctx, 0x56D298u);  // $ra first: the delay slot below depends on it
        lhu(a0, sp, 0x0);
        call(ctx, gen::fn_sub_56D0D0_0056d0d0);
        v0 = slti(s1, 8);
        s0 = addu(s2, s1);
        if (v0 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0056d2ac
    charge(ctx, 8);
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(s2, sp, 0x20);
    ld(s3, sp, 0x28);
    ld(s4, sp, 0x30);
    ld(ra, sp, 0x38);
    sp = addiu(sp, 0x40);
}

// 0x0056D2D0 sub_56D2D0 -- 136 bytes; frame 0x40: s0 sp+0x20, s1 sp+0x28, ra sp+0x30
// A sector's round key: the sector number x 0x100001 big-endian, its three hashes; round = hash 1 mod 9, the other
//   two stored big-endian as the 4-byte mask. [rsu_SectorKey]
void sub_56D2D0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056d2d0
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x40);
    v0 = sll(a0, 20);
    sd(s0, sp, 0x20);
    s0 = a1;
    a0 = addu(v0, a0);
    a1 = sp;
    sd(s1, sp, 0x28);
    sd(ra, sp, 0x30);
    s1 = a2;
    jal(ctx, 0x56D2F0u, gen::fn_sub_56D108_0056d108);
    a0 = sp;
    a2 = addiu(sp, 0x10);
    a3 = addiu(sp, 0x12);
    t0 = addiu(sp, 0x14);
    a1 = 4;
    jal(ctx, 0x56D308u, gen::fn_sub_56CE88_0056ce88);
    v1 = 9;
    lh(a2, sp, 0x10);
    if (v1 == 0) {
        brk(ctx, 0x56D31Cu, 0x7u);
    }
    // 0x0056d320
    charge(ctx, 14);
    lhu(a0, sp, 0x12);
    a1 = s0;
    div(a2, v1);
    mfhi(v0);
    link(ctx, 0x56D330u);  // $ra first: the delay slot below depends on it
    sw(v0, s1, 0);
    call(ctx, gen::fn_sub_56D0D0_0056d0d0);
    a1 = addiu(s0, 2);
    link(ctx, 0x56D33Cu);  // $ra first: the delay slot below depends on it
    lhu(a0, sp, 0x14);
    call(ctx, gen::fn_sub_56D0D0_0056d0d0);
    ld(s0, sp, 0x20);
    ld(s1, sp, 0x28);
    ld(ra, sp, 0x30);
    sp = addiu(sp, 0x40);
}

// 0x0056D358 rsu_GenerateFixedKeyByCvmhdr -- 84 bytes; frame 0x20: s0 sp+0x10, ra sp+0x18
// Fixed key from a CVM header: the key strings mixed, hashed when both exist. [rsu_GenerateFixedKeyByCvmhdr]
void rsu_GenerateFixedKeyByCvmhdr(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, s0{ctx, 16}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0056d358
    enter(ctx, 12);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    sd(s0, sp, 0x10);
    s0 = a1;
    sd(ra, sp, 0x18);
    a1 = sp;
    jal(ctx, 0x56D368u, gen::fn_sub_56D180_0056d180);
    a1 = s0;
    a0 = sp;
    jal(ctx, 0x56D374u, gen::fn_sub_56D1E8_0056d1e8);
    lw(v0, sp, 0x0);
    cc = v0 == 0;  // the condition, before the delay slot changes it
    lw(v0, sp, 0x4);
    if (!cc) {
        // 0x0056d388
        charge(ctx, 2);
        if (v0 != 0) {
            // 0x0056d390
            charge(ctx, 2);
            a0 = s0;
            jal(ctx, 0x56D390u, gen::fn_sub_56D248_0056d248);
            goto L_0056d398;
        }
        ld(s0, sp, 0x10);
        // 0x0056d39c (the shared epilogue, written out on this path)
        charge(ctx, 4);
        v0 = 0;
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
L_0056d398:
    charge(ctx, 1);
    ld(s0, sp, 0x10);
    // 0x0056d39c (the shared epilogue, written out on this path)
    charge(ctx, 4);
    v0 = 0;
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0056D3B0 sub_56D3B0 -- 240 bytes; frame 0x30: s0 sp+0x10, s1 sp+0x18, ra sp+0x20
// Fixed key from a password: a checksum of the text (each byte times the running sum plus the rest), x 0x100001
//   big-endian, its bytes interleaved, hashed. [rsu_GenerateFixedKeyByPwd]
void sub_56D3B0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, s0{ctx, 16}, s1{ctx, 17}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0056d3b0
    enter(ctx, 11);  // entry check point + this block's cycles
    sp = addiu(sp, -0x30);
    sd(s0, sp, 0x10);
    s0 = a0;
    sd(s1, sp, 0x18);
    sd(ra, sp, 0x20);
    s1 = a1;
    jal(ctx, 0x56D3C4u, gen::fn_strlen_00524388);
    a0 = v0;
    v1 = 0;
    t0 = 0;
    if (i64(a0) > 0) {
        // 0x0056d3dc
        charge(ctx, 1);
        v0 = addu(s0, v1);
        for (;;) {
            // 0x0056d3e0
            charge(ctx, 7);
            a3 = addiu(v1, 1);
            lb(a1, v0, 0);
            v1 = slt(a3, a0);
            a2 = a3;
            v0 = addu(t0, a1);
            mult(t0, v0, a1);
            if (v1 != 0) {
                // 0x0056d3fc
                charge(ctx, 1);
                for (;;) {
                    // 0x0056d400
                    charge(ctx, 7);
                    v0 = addu(s0, a3);
                    a3 = addiu(a3, 1);
                    lb(a1, v0, 0);
                    v1 = slt(a3, a0);
                    t0 = addu(t0, a1);
                    if (v1 == 0) {
                        break;
                    }
                    backedge(ctx);
                }
            }
            // 0x0056d41c
            charge(ctx, 4);
            v1 = a2;
            v0 = slt(v1, a0);
            cc = v0 != 0;  // the condition, before the delay slot changes it
            v0 = addu(s0, v1);
            if (!cc) {
                break;
            }
            backedge(ctx);
        }
    }
    // 0x0056d42c
    charge(ctx, 7);
    a0 = sll(t0, 20);
    a1 = sp;
    a0 = addu(t0, a0);
    jal(ctx, 0x56D434u, gen::fn_sub_56D108_0056d108);
    a3 = 0;
    t1 = 3;
    t0 = s1;
    for (;;) {
        // 0x0056d448
        charge(ctx, 14);
        v0 = srl(a3, 31);
        v0 = addu(a3, v0);
        a3 = addiu(a3, 2);
        v0 = sra(v0, 1);
        a2 = slti(a3, 8);
        v1 = subu(t1, v0);
        a0 = addu(sp, v0);
        a1 = addu(sp, v1);
        lbu(v0, a0, 0);
        lbu(v1, a1, 0);
        sb(v0, t0, 0);
        sb(v1, t0, 1);
        t0 = addiu(t0, 2);
        if (a2 == 0) {
            break;
        }
        backedge(ctx);
    }
    // 0x0056d480
    charge(ctx, 8);
    a0 = s1;
    jal(ctx, 0x56D480u, gen::fn_sub_56D248_0056d248);
    v0 = 0;
    ld(s0, sp, 0x10);
    ld(s1, sp, 0x18);
    ld(ra, sp, 0x20);
    sp = addiu(sp, 0x30);
}

// 0x0056D4A0 r_lock_def_free_1 -- 32 bytes; frame 0x10: ra sp+0x0
// Round key of a sector (the round and the 4-byte mask). [rsu_GetRoundKey]
void r_lock_def_free_1(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056d4a0
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x56D4A8u, gen::fn_sub_56D2D0_0056d2d0);
    ld(ra, sp, 0x0);
    v0 = 0;
    sp = addiu(sp, 0x10);
}

// 0x0056D4C0 r_lock_def_get_free_item_1 -- 68 bytes; frame 0x10: ra sp+0x0
// Run permutation round n (< 9) of the table 0x7B28F0 on 8 key bytes with the mask; -1000 otherwise. [rsu_Round]
void r_lock_def_get_free_item_1(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a2{ctx, 6}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056d4c0
    enter(ctx, 8);  // entry check point + this block's cycles
    v1 = a2;
    a2 = a3;
    sp = addiu(sp, -0x10);
    a3 = sll(v1, 2);
    v1 = sltiu(v1, 9);
    sd(ra, sp, 0x0);
    v0 = si(-1000);
    if (v1 != 0) {
        // 0x0056d4e0
        charge(ctx, 6);
        v0 = 0x7B0000;
        v0 = addu(v0, a3);
        lw(v0, v0, 10480);
        jalr(ctx, 0x56D4ECu, v0.u());
        v0 = 0;
    }
    // 0x0056d4f8 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056D508 sub_56D508 -- 440 bytes; frame 0x80: s0 sp+0x30, s1 sp+0x38, s4 sp+0x50, s5 sp+0x58, s2 sp+0x40, s3 sp+0x48, s6 sp+0x60, s7 sp+0x68, fp sp+0x70, ra sp+0x78
// Decipher a buffer: for each sector (size a multiple of the block, the block a multiple of the key size) and each
//   8-byte block, the sector's round key, the round on the fixed key, the block XORed with the result; an all-zero
//   key leaves the data; -100 on bad sizes. [rsu_DecipherBuf]
void sub_56D508(EEContext& ctx) {
    using namespace hg;
    Gpr zero{ctx, 0}, v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, s3{ctx, 19}, s4{ctx, 20}, s5{ctx, 21}, s6{ctx, 22}, s7{ctx, 23}, sp{ctx, 29}, fp{ctx, 30}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0056d508
    enter(ctx, 20);  // entry check point + this block's cycles
    sp = addiu(sp, -0x80);
    sd(s0, sp, 0x30);
    s0 = a2;
    sd(s1, sp, 0x38);
    s1 = t1;
    div(s0, s1);
    sd(s4, sp, 0x50);
    sd(s5, sp, 0x58);
    s5 = t0;
    sd(s2, sp, 0x40);
    s4 = a1;
    sd(s3, sp, 0x48);
    sd(s6, sp, 0x60);
    sd(s7, sp, 0x68);
    sd(fp, sp, 0x70);
    sd(ra, sp, 0x78);
    sw(a0, sp, 0x24);
    sw(a3, sp, 0x28);
    if (s1 == 0) {
        brk(ctx, 0x56D554u, 0x7u);
    }
    // 0x0056d558
    charge(ctx, 3);
    mfhi(v0);
    cc = v0 != 0;  // the condition, before the delay slot changes it
    v0 = si(-100);
    if (!cc) {
        // 0x0056d564
        charge(ctx, 3);
        div(s4, s0);
        if (s0 == 0) {
            brk(ctx, 0x56D56Cu, 0x7u);
        }
        // 0x0056d570
        charge(ctx, 3);
        mfhi(v0);
        cc = v0 != 0;  // the condition, before the delay slot changes it
        v0 = si(-100);
        if (cc) {
            goto L_0056d690;
        }
        // 0x0056d57c
        charge(ctx, 2);
        if (s5 == 0) {
            ld(s0, sp, 0x30);
        } else {
            // 0x0056d584
            charge(ctx, 2);
            a0 = s5;
            if (s1 != 0) {
                // 0x0056d598
                charge(ctx, 4);
                a1 = s1;
                jal(ctx, 0x56D598u, gen::fn_sub_56D968_0056d968);
                cc = v0 != 0;  // the condition, before the delay slot changes it
                v0 = 0;
                if (!cc) {
                    // 0x0056d5a8
                    charge(ctx, 3);
                    div(s4, s0);
                    if (s0 == 0) {
                        brk(ctx, 0x56D5B0u, 0x7u);
                    }
                    // 0x0056d5b4
                    charge(ctx, 3);
                    mflo(v0);
                    fp = 0;
                    if (i64(v0) > 0) {
                        // 0x0056d5c0
                        charge(ctx, 2);
                        sw(zero, sp, 0x2C);
                        for (;;) {
                            // 0x0056d5c8
                            charge(ctx, 3);
                            lbu(t1, s5, 5);
                            s3 = 0;
                            if (i64(s0) > 0) {
                                // 0x0056d5d4
                                charge(ctx, 7);
                                lw(v0, sp, 0x28);
                                s6 = addiu(sp, 0x10);
                                lw(v1, sp, 0x2C);
                                s7 = addu(v0, fp);
                                lw(v0, sp, 0x24);
                                s2 = addu(v1, v0);
                                for (;;) {
                                    // 0x0056d5f0
                                    charge(ctx, 13);
                                    mult(a0, t1, s7);
                                    a2 = addiu(sp, 0x20);
                                    a1 = sp;
                                    jal(ctx, 0x56D5F8u, gen::fn_sub_56D828_0056d828);
                                    a0 = s5;
                                    lw(a2, sp, 0x20);
                                    a1 = sp;
                                    a3 = s6;
                                    jal(ctx, 0x56D60Cu, gen::fn_sub_56D850_0056d850);
                                    t0 = 0;
                                    lw(v0, sp, 0x20);
                                    t1 = addu(v0, s3);
                                    if (i64(s1) > 0) {
                                        // 0x0056d624
                                        charge(ctx, 1);
                                        t2 = s6;
                                        for (;;) {
                                            // 0x0056d628
                                            charge(ctx, 11);
                                            a3 = addu(s2, t0);
                                            a1 = addu(t2, t0);
                                            lbu(v1, a1, 0);
                                            t0 = addiu(t0, 1);
                                            lbu(v0, a3, 0);
                                            a2 = slt(t0, s1);
                                            a0 = v1 & 0xFF;
                                            v0 = v0 ^ v1;
                                            mult(t1, t1, a0);
                                            sb(v0, a3, 0);
                                            if (a2 == 0) {
                                                break;
                                            }
                                            backedge(ctx);
                                        }
                                    }
                                    // 0x0056d654
                                    charge(ctx, 4);
                                    s3 = addu(s3, s1);
                                    v0 = slt(s3, s0);
                                    s2 = addu(s2, s1);
                                    if (v0 == 0) {
                                        break;
                                    }
                                    backedge(ctx);
                                }
                            }
                            // 0x0056d664
                            charge(ctx, 3);
                            div(s4, s0);
                            if (s0 == 0) {
                                brk(ctx, 0x56D66Cu, 0x7u);
                            }
                            // 0x0056d670
                            charge(ctx, 7);
                            lw(v1, sp, 0x2C);
                            fp = addiu(fp, 0x1);
                            v1 = addu(v1, s0);
                            mflo(v0);
                            v0 = slt(fp, v0);
                            sw(v1, sp, 0x2C);
                            if (v0 == 0) {
                                break;
                            }
                            backedge(ctx);
                        }
                    }
                    // 0x0056d68c
                    charge(ctx, 1);
                    v0 = 0;
                }
                goto L_0056d690;
            }
            // 0x0056d58c
            charge(ctx, 2);
            ld(s0, sp, 0x30);
        }
        // 0x0056d694 (the shared epilogue, written out on this path)
        charge(ctx, 11);
        ld(s1, sp, 0x38);
        ld(s2, sp, 0x40);
        ld(s3, sp, 0x48);
        ld(s4, sp, 0x50);
        ld(s5, sp, 0x58);
        ld(s6, sp, 0x60);
        ld(s7, sp, 0x68);
        ld(fp, sp, 0x70);
        ld(ra, sp, 0x78);
        sp = addiu(sp, 0x80);
        return;
    }
L_0056d690:
    charge(ctx, 1);
    ld(s0, sp, 0x30);
    // 0x0056d694 (the shared epilogue, written out on this path)
    charge(ctx, 11);
    ld(s1, sp, 0x38);
    ld(s2, sp, 0x40);
    ld(s3, sp, 0x48);
    ld(s4, sp, 0x50);
    ld(s5, sp, 0x58);
    ld(s6, sp, 0x60);
    ld(s7, sp, 0x68);
    ld(fp, sp, 0x70);
    ld(ra, sp, 0x78);
    sp = addiu(sp, 0x80);
}

// 0x0056D6C0 rsu_Decipher -- 20 bytes; frame 0x10: ra sp+0x0
// Decipher (internal entry). [rsu_Decipher]
void rsu_Decipher(EEContext& ctx) {
    using namespace hg;
    Gpr sp{ctx, 29}, ra{ctx, 31};
    // 0x0056d6c0
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_56D508_0056d508(ctx);  // tail call
}

// 0x0056D6D8 sceLibgcc32GetErxEntries_14 -- 12 bytes; leaf frame (no stack)
// RSU's version text (FLIRT name; not a libgcc function). [rsu_GetVersion]
void sceLibgcc32GetErxEntries_14(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2};
    // 0x0056d6d8
    enter(ctx, 3);  // entry check point + this block's cycles
    v0 = 0x7C0000;
    v0 = addiu(v0, 30632);  // "\nRSU Ver.1.10 Build:Mar  2 2005 11:31:01\n"
}

// 0x0056D6E8 RSU_Init -- 84 bytes; frame 0x10: ra sp+0x0
// RSU init (counted): the version text noted (0x99B248), the tables counted on the first call. [RSU_Init]
void RSU_Init(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056d6e8
    enter(ctx, 14);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    sd(ra, sp, 0x0);
    jal(ctx, 0x56D6F0u, gen::fn_sceLibgcc32GetErxEntries_14_0056d6d8);
    a0 = 0x7B0000;
    a1 = 0x9A0000;
    a0 = addiu(a0, 10476);  // &0x7B28EC
    a1 = addiu(a1, -19896);  // &0x99B248
    lw(v1, a0, 0);  // 0x7B28EC
    a2 = 1;
    sw(v0, a1, 0);  // 0x99B248
    v1 = addiu(v1, 1);
    sw(v1, a0, 0);  // 0x7B28EC
    if (v1 != a2) {
        // 0x0056d730
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0056d720
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    gen::fn_sub_56CE48_0056ce48(ctx);  // tail call
}

// 0x0056D740 sub_56D740 -- 88 bytes, 2 chunks; frame 0x10: ra sp+0x0
// RSU finish (counted): the last call drops the tables' user. [rsu_Finish]
void sub_56D740(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056d740
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v1 = 0x7B0000;
    sd(ra, sp, 0x0);
    v1 = addiu(v1, 10476);  // &0x7B28EC
    lw(v0, v1, 0);  // 0x7B28EC
    v0 = addiu(v0, -1);
    sw(v0, v1, 0);  // 0x7B28EC
    if (v0 != 0) {
        // 0x0056d770
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
    // 0x0056d760
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
    backedge(ctx);
    // 0x0056ce68
    charge(ctx, 7);
    a0 = 0x7B0000;
    v0 = 0;
    a0 = addiu(a0, 10464);  // &0x7B28E0
    lw(v1, a0, 0);  // 0x7B28E0
    v1 = addiu(v1, -1);
    sw(v1, a0, 0);  // 0x7B28E0
}

// 0x0056D780 RSU_GenerateFixedKey -- 164 bytes; frame 0x20: s0 sp+0x0, s1 sp+0x8, s2 sp+0x10, ra sp+0x18
// Generate the fixed key into 8 bytes (cleared first): from a password when one is given, else from the CVM header;
//   neither -100. [RSU_GenerateFixedKey]
void RSU_GenerateFixedKey(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, s0{ctx, 16}, s1{ctx, 17}, s2{ctx, 18}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056d780
    enter(ctx, 13);  // entry check point + this block's cycles
    sp = addiu(sp, -0x20);
    v0 = si(-100);
    sd(s0, sp, 0x0);
    s0 = a2;
    sd(s1, sp, 0x8);
    s1 = a1;
    sd(s2, sp, 0x10);
    s2 = a0;
    sd(ra, sp, 0x18);
    a2 = 8;
    a0 = s0;
    a1 = 0;
    if (s0 == 0) {
        // 0x0056d80c (the shared epilogue, written out on this path)
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        return;
    }
    // 0x0056d7b4
    charge(ctx, 5);
    jal(ctx, 0x56D7B4u, gen::fn_memset_00521408);
    a1 = s0;
    a0 = s1;
    if (s1 != 0) {
        // 0x0056d7c8
        charge(ctx, 6);
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(s2, sp, 0x10);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_sub_56D3B0_0056d3b0(ctx);  // tail call
        return;
    }
    // 0x0056d7e0
    charge(ctx, 2);
    a0 = s2;
    if (s2 != 0) {
        // 0x0056d7e8
        charge(ctx, 7);
        ld(s2, sp, 0x10);
        a1 = s0;
        ld(s0, sp, 0x0);
        ld(s1, sp, 0x8);
        ld(ra, sp, 0x18);
        sp = addiu(sp, 0x20);
        gen::fn_rsu_GenerateFixedKeyByCvmhdr_0056d358(ctx);  // tail call
        return;
    }
    // 0x0056d808
    charge(ctx, 1);
    v0 = si(-100);
    // 0x0056d80c (the shared epilogue, written out on this path)
    charge(ctx, 6);
    ld(s0, sp, 0x0);
    ld(s1, sp, 0x8);
    ld(s2, sp, 0x10);
    ld(ra, sp, 0x18);
    sp = addiu(sp, 0x20);
}

// 0x0056D828 sub_56D828 -- 36 bytes; frame 0x10: ra sp+0x0
// Round key with a check (-100 without the output). [rsu_GetRoundKeyChk]
void sub_56D828(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, a1{ctx, 5}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056d828
    enter(ctx, 4);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = si(-100);
    sd(ra, sp, 0x0);
    if (a1 != 0) {
        // 0x0056d838
        charge(ctx, 2);
        jal(ctx, 0x56D838u, gen::fn_r_lock_def_free_1_0056d4a0);
    }
    // 0x0056d840 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056D850 sub_56D850 -- 68 bytes; frame 0x10: ra sp+0x0
// Round with checks (-100 without key, mask or output). [rsu_RoundChk]
void sub_56D850(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a3{ctx, 7}, sp{ctx, 29}, ra{ctx, 31};
    bool cc = false;  // a branch condition read before its delay slot
    // 0x0056d850
    enter(ctx, 5);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a1;
    sd(ra, sp, 0x0);
    v1 = a3;
    if (a0 != 0) {
        // 0x0056d864
        charge(ctx, 2);
        cc = v0 == 0;  // the condition, before the delay slot changes it
        v0 = si(-100);
        if (!cc) {
            // 0x0056d86c
            charge(ctx, 2);
            if (v1 == 0) {
                goto L_0056d874;
            }
            // 0x0056d880
            charge(ctx, 2);
            jal(ctx, 0x56D880u, gen::fn_r_lock_def_get_free_item_1_0056d4c0);
        }
        // 0x0056d888 (the shared epilogue, written out on this path)
        charge(ctx, 3);
        ld(ra, sp, 0x0);
        sp = addiu(sp, 0x10);
        return;
    }
L_0056d874:
    charge(ctx, 2);
    v0 = si(-100);
    // 0x0056d888 (the shared epilogue, written out on this path)
    charge(ctx, 3);
    ld(ra, sp, 0x0);
    sp = addiu(sp, 0x10);
}

// 0x0056D898 sub_56D898 -- 100 bytes; frame 0x10: ra sp+0x0
// Decipher with argument checks (-100); no caller in the binary. [rsu_DecipherChk]
void sub_56D898(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056d898
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a1;
    sd(ra, sp, 0x0);
    v1 = a2;
    t2 = a3;
    t3 = t0;
    t4 = t1;
    if (a0 != 0) {
        // 0x0056d8b8
        charge(ctx, 2);
        if (i64(v0) < 0) {
            v0 = si(-100);
        L_0056d8f0:
            charge(ctx, 1);
            ld(ra, sp, 0x0);
        } else {
            // 0x0056d8c0
            charge(ctx, 2);
            v0 = si(-100);
            if (i64(v1) < 0) {
                goto L_0056d8f0;
            }
            // 0x0056d8c8
            charge(ctx, 2);
            if (i64(t2) < 0) {
                goto L_0056d8f0;
            }
            // 0x0056d8d0
            charge(ctx, 2);
            ld(ra, sp, 0x0);
            if (t3 != 0) {
                // 0x0056d8d8
                charge(ctx, 2);
                if (i64(t4) < 0) {
                    goto L_0056d8e0;
                }
                // 0x0056d8e8
                charge(ctx, 2);
                jal(ctx, 0x56D8E8u, gen::fn_sub_56D508_0056d508);
                goto L_0056d8f0;
            }
        }
        // 0x0056d8f4 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_0056d8e0:
    charge(ctx, 2);
    v0 = si(-100);
    goto L_0056d8f0;
}

// 0x0056D900 RSU_Decipher -- 100 bytes; frame 0x10: ra sp+0x0
// Decipher with argument checks: buffer, size >= 0, sector size >= 0, sector >= 0, key, key size >= 0; else -100.
//   [RSU_Decipher]
void RSU_Decipher(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7}, t0{ctx, 8}, t1{ctx, 9}, t2{ctx, 10}, t3{ctx, 11}, t4{ctx, 12}, sp{ctx, 29}, ra{ctx, 31};
    // 0x0056d900
    enter(ctx, 8);  // entry check point + this block's cycles
    sp = addiu(sp, -0x10);
    v0 = a1;
    sd(ra, sp, 0x0);
    v1 = a2;
    t2 = a3;
    t3 = t0;
    t4 = t1;
    if (a0 != 0) {
        // 0x0056d920
        charge(ctx, 2);
        if (i64(v0) < 0) {
            v0 = si(-100);
        L_0056d958:
            charge(ctx, 1);
            ld(ra, sp, 0x0);
        } else {
            // 0x0056d928
            charge(ctx, 2);
            v0 = si(-100);
            if (i64(v1) < 0) {
                goto L_0056d958;
            }
            // 0x0056d930
            charge(ctx, 2);
            if (i64(t2) < 0) {
                goto L_0056d958;
            }
            // 0x0056d938
            charge(ctx, 2);
            ld(ra, sp, 0x0);
            if (t3 != 0) {
                // 0x0056d940
                charge(ctx, 2);
                if (i64(t4) < 0) {
                    goto L_0056d948;
                }
                // 0x0056d950
                charge(ctx, 2);
                jal(ctx, 0x56D950u, gen::fn_rsu_Decipher_0056d6c0);
                goto L_0056d958;
            }
        }
        // 0x0056d95c (the shared epilogue, written out on this path)
        charge(ctx, 2);
        sp = addiu(sp, 0x10);
        return;
    }
L_0056d948:
    charge(ctx, 2);
    v0 = si(-100);
    goto L_0056d958;
}

// 0x0056D968 sub_56D968 -- 64 bytes; leaf frame (no stack)
// Is a key all zero (1) or not (0). [rsu_IsZeroKey]
void sub_56D968(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0056d968
    enter(ctx, 2);  // entry check point + this block's cycles
    a3 = 0;
    if (i64(a1) > 0) {
        // 0x0056d970
        charge(ctx, 2);
        v0 = addu(a0, a3);
        for (;;) {
            // 0x0056d978
            charge(ctx, 5);
            a3 = addiu(a3, 1);
            lbu(v1, v0, 0);
            v0 = 0;
            a2 = slt(a3, a1);
            if (v1 != 0) {
                break;
            }
            // 0x0056d98c
            charge(ctx, 4);
            if (a2 == 0) {
                goto L_0056d99c;
            }
            v0 = addu(a0, a3);
            backedge(ctx);
        }
        // 0x0056d9a0 (the shared epilogue, written out on this path)
        charge(ctx, 2);
        return;
    }
L_0056d99c:
    charge(ctx, 1);
    v0 = 1;
    // 0x0056d9a0 (the shared epilogue, written out on this path)
    charge(ctx, 2);
}

// 0x0056D9A8 sub_56D9A8 -- 100 bytes; leaf frame (no stack)
// Permutation round 0: 8 key bytes reordered, four of them XORed with the mask. [rsu_Round0]
void sub_56D9A8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0056d9a8
    enter(ctx, 25);  // entry check point + this block's cycles
    lbu(v1, a1, 0);
    lbu(v0, a0, 3);
    v0 = v0 ^ v1;
    sb(v0, a2, 0);
    lbu(v1, a0, 0);
    sb(v1, a2, 1);
    lbu(v1, a1, 3);
    lbu(v0, a0, 7);
    v0 = v0 ^ v1;
    sb(v0, a2, 2);
    lbu(v1, a0, 4);
    sb(v1, a2, 3);
    lbu(a3, a0, 1);
    sb(a3, a2, 4);
    lbu(v1, a1, 2);
    lbu(v0, a0, 6);
    v0 = v0 ^ v1;
    sb(v0, a2, 5);
    lbu(v1, a0, 2);
    sb(v1, a2, 6);
    lbu(v0, a0, 5);
    lbu(v1, a1, 1);
    v0 = v0 ^ v1;
    sb(v0, a2, 7);
}

// 0x0056DA10 sub_56DA10 -- 100 bytes; leaf frame (no stack)
// Permutation round 1 (XOR). [rsu_Round1]
void sub_56DA10(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0056da10
    enter(ctx, 25);  // entry check point + this block's cycles
    lbu(v1, a1, 1);
    lbu(v0, a0, 2);
    v0 = v0 ^ v1;
    sb(v0, a2, 0);
    lbu(v1, a0, 7);
    sb(v1, a2, 1);
    lbu(a3, a0, 5);
    sb(a3, a2, 2);
    lbu(v1, a1, 2);
    lbu(v0, a0, 3);
    v0 = v0 ^ v1;
    sb(v0, a2, 3);
    lbu(v0, a1, 0);
    lbu(v1, a0, 0);
    v1 = v1 ^ v0;
    sb(v1, a2, 4);
    lbu(v0, a0, 6);
    sb(v0, a2, 5);
    lbu(v1, a0, 4);
    sb(v1, a2, 6);
    lbu(v0, a0, 1);
    lbu(v1, a1, 3);
    v0 = v0 ^ v1;
    sb(v0, a2, 7);
}

// 0x0056DA78 sub_56DA78 -- 100 bytes; leaf frame (no stack)
// Permutation round 2 (XOR). [rsu_Round2]
void sub_56DA78(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0056da78
    enter(ctx, 25);  // entry check point + this block's cycles
    lbu(v1, a0, 1);
    sb(v1, a2, 0);
    lbu(v1, a1, 2);
    lbu(v0, a0, 7);
    v0 = v0 ^ v1;
    sb(v0, a2, 1);
    lbu(v1, a0, 6);
    sb(v1, a2, 2);
    lbu(v1, a1, 1);
    lbu(v0, a0, 2);
    v0 = v0 ^ v1;
    sb(v0, a2, 3);
    lbu(v0, a1, 3);
    lbu(v1, a0, 5);
    v1 = v1 ^ v0;
    sb(v1, a2, 4);
    lbu(v0, a0, 3);
    sb(v0, a2, 5);
    lbu(v1, a1, 0);
    lbu(v0, a0, 0);
    v0 = v0 ^ v1;
    sb(v0, a2, 6);
    lbu(v1, a0, 4);
    sb(v1, a2, 7);
}

// 0x0056DAE0 sub_56DAE0 -- 100 bytes; leaf frame (no stack)
// Permutation round 3 (addition). [rsu_Round3]
void sub_56DAE0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0056dae0
    enter(ctx, 25);  // entry check point + this block's cycles
    lbu(v1, a1, 2);
    lbu(v0, a0, 3);
    v0 = addu(v0, v1);
    sb(v0, a2, 0);
    lbu(v1, a0, 6);
    sb(v1, a2, 1);
    lbu(v0, a0, 0);
    sb(v0, a2, 2);
    lbu(v1, a0, 2);
    sb(v1, a2, 3);
    lbu(v1, a1, 0);
    lbu(v0, a0, 4);
    v0 = addu(v0, v1);
    sb(v0, a2, 4);
    lbu(v0, a1, 1);
    lbu(v1, a0, 1);
    v1 = addu(v1, v0);
    sb(v1, a2, 5);
    lbu(a3, a0, 7);
    sb(a3, a2, 6);
    lbu(v0, a0, 5);
    lbu(v1, a1, 3);
    v0 = addu(v0, v1);
    sb(v0, a2, 7);
}

// 0x0056DB48 sub_56DB48 -- 100 bytes; leaf frame (no stack)
// Permutation round 4 (addition). [rsu_Round4]
void sub_56DB48(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0056db48
    enter(ctx, 25);  // entry check point + this block's cycles
    lbu(v1, a0, 7);
    sb(v1, a2, 0);
    lbu(v1, a1, 3);
    lbu(v0, a0, 0);
    v0 = addu(v0, v1);
    sb(v0, a2, 1);
    lbu(v0, a1, 0);
    lbu(v1, a0, 2);
    v1 = addu(v1, v0);
    sb(v1, a2, 2);
    lbu(v1, a1, 1);
    lbu(v0, a0, 6);
    v0 = addu(v0, v1);
    sb(v0, a2, 3);
    lbu(v1, a0, 4);
    sb(v1, a2, 4);
    lbu(v0, a0, 3);
    sb(v0, a2, 5);
    lbu(v1, a0, 5);
    sb(v1, a2, 6);
    lbu(v0, a0, 1);
    lbu(v1, a1, 2);
    v0 = addu(v0, v1);
    sb(v0, a2, 7);
}

// 0x0056DBB0 sub_56DBB0 -- 100 bytes; leaf frame (no stack)
// Permutation round 5 (addition). [rsu_Round5]
void sub_56DBB0(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0056dbb0
    enter(ctx, 25);  // entry check point + this block's cycles
    lbu(v1, a0, 2);
    sb(v1, a2, 0);
    lbu(v1, a1, 2);
    lbu(v0, a0, 3);
    v0 = addu(v0, v1);
    sb(v0, a2, 1);
    lbu(v1, a0, 6);
    sb(v1, a2, 2);
    lbu(v1, a1, 0);
    lbu(v0, a0, 7);
    v0 = addu(v0, v1);
    sb(v0, a2, 3);
    lbu(v1, a0, 0);
    sb(v1, a2, 4);
    lbu(v1, a1, 1);
    lbu(v0, a0, 1);
    v0 = addu(v0, v1);
    sb(v0, a2, 5);
    lbu(v1, a0, 4);
    sb(v1, a2, 6);
    lbu(v0, a0, 5);
    lbu(v1, a1, 3);
    v0 = addu(v0, v1);
    sb(v0, a2, 7);
}

// 0x0056DC18 sub_56DC18 -- 100 bytes; leaf frame (no stack)
// Permutation round 6 (addition and XOR). [rsu_Round6]
void sub_56DC18(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0056dc18
    enter(ctx, 25);  // entry check point + this block's cycles
    lbu(v1, a1, 0);
    lbu(v0, a0, 3);
    v0 = addu(v0, v1);
    sb(v0, a2, 0);
    lbu(v1, a0, 7);
    sb(v1, a2, 1);
    lbu(v1, a1, 1);
    lbu(v0, a0, 2);
    v0 = v0 ^ v1;
    sb(v0, a2, 2);
    lbu(v1, a0, 6);
    sb(v1, a2, 3);
    lbu(a3, a0, 1);
    sb(a3, a2, 4);
    lbu(v1, a1, 2);
    lbu(v0, a0, 5);
    v0 = v0 ^ v1;
    sb(v0, a2, 5);
    lbu(v1, a0, 0);
    sb(v1, a2, 6);
    lbu(v0, a0, 4);
    lbu(v1, a1, 3);
    v0 = addu(v0, v1);
    sb(v0, a2, 7);
}

// 0x0056DC80 sub_56DC80 -- 100 bytes; leaf frame (no stack)
// Permutation round 7 (XOR and addition). [rsu_Round7]
void sub_56DC80(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6}, a3{ctx, 7};
    // 0x0056dc80
    enter(ctx, 25);  // entry check point + this block's cycles
    lbu(v1, a0, 7);
    sb(v1, a2, 0);
    lbu(v1, a1, 3);
    lbu(v0, a0, 4);
    v0 = v0 ^ v1;
    sb(v0, a2, 1);
    lbu(v1, a0, 3);
    sb(v1, a2, 2);
    lbu(v1, a1, 2);
    lbu(v0, a0, 1);
    v0 = addu(v0, v1);
    sb(v0, a2, 3);
    lbu(v1, a0, 0);
    sb(v1, a2, 4);
    lbu(a3, a0, 2);
    sb(a3, a2, 5);
    lbu(v1, a1, 1);
    lbu(v0, a0, 5);
    v0 = addu(v0, v1);
    sb(v0, a2, 6);
    lbu(v1, a0, 6);
    lbu(v0, a1, 0);
    v1 = v1 ^ v0;
    sb(v1, a2, 7);
}

// 0x0056DCE8 sub_56DCE8 -- 100 bytes; leaf frame (no stack)
// Permutation round 8 (XOR and addition). [rsu_Round8]
void sub_56DCE8(EEContext& ctx) {
    using namespace hg;
    Gpr v0{ctx, 2}, v1{ctx, 3}, a0{ctx, 4}, a1{ctx, 5}, a2{ctx, 6};
    // 0x0056dce8
    enter(ctx, 25);  // entry check point + this block's cycles
    lbu(v1, a0, 3);
    sb(v1, a2, 0);
    lbu(v1, a1, 1);
    lbu(v0, a0, 0);
    v0 = v0 ^ v1;
    sb(v0, a2, 1);
    lbu(v1, a0, 6);
    sb(v1, a2, 2);
    lbu(v1, a1, 0);
    lbu(v0, a0, 4);
    v0 = addu(v0, v1);
    sb(v0, a2, 3);
    lbu(v0, a1, 3);
    lbu(v1, a0, 2);
    v1 = v1 ^ v0;
    sb(v1, a2, 4);
    lbu(v0, a0, 7);
    sb(v0, a2, 5);
    lbu(v1, a0, 1);
    sb(v1, a2, 6);
    lbu(v0, a0, 5);
    lbu(v1, a1, 2);
    v0 = addu(v0, v1);
    sb(v0, a2, 7);
}

}  // namespace p3fes::game
